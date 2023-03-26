SET serveroutput ON;

--관리자 현황 프로시저_커서
CREATE OR REPLACE PROCEDURE manager_info (
    p_mid in manager.mid%TYPE
) IS
v_mid manager.mid%type;
v_mname manager.mname%type;
chk_num number;
BEGIN
select mid into v_mid from manager where mid = p_mid;
select mname into v_mname from manager where mid = p_mid;

DBMS_OUTPUT.PUT_LINE('------------------------------------------');
dbms_output.put_line('현재 접속하신 관리자 번호는 ' || v_mid || ' 입니다.');
dbms_output.put_line(v_mname || ' 관리자님 반갑습니다!');
dbms_output.put_line('아래는 관리자님이 관리하시는 품목들입니다.');
DBMS_OUTPUT.PUT_LINE('------------------------------------------');
    for cur_mag in (
        SELECT ma.mid 관리자번호, ma.mname 관리자명, pr.pname 재고이름, pr.pnum 재고수량
        FROM manager ma, product pr WHERE ma.mid = pr.mid AND ma.mid = p_mid
    )
    loop
        dbms_output.put_line(' 재고 이름    : ' || cur_mag.재고이름);
        dbms_output.put_line(' 재고 수량    : ' || cur_mag.재고수량);
DBMS_OUTPUT.PUT_LINE('------------------------------------------');
    end loop;
    SELECT count(*) 관리자체크  into chk_num FROM manager ma, product pr WHERE ma.mid = pr.mid AND ma.mid = p_mid;
    if chk_num =0 then
        dbms_output.put_line('등록되지 않은 관리자 id : ' || p_mid);
        dbms_output.put_line('올바른 관리자 번호로 검색해주십시오.');
    end if;
EXCEPTION
    WHEN others THEN
        dbms_output.put_line('DB에러 발생');
END;
/
--취소(환불) 프로시저 생성
CREATE OR REPLACE PROCEDURE delete_order(
callid2 call.callid%type
)
is
v_callid call.callid%type;
v_cname customer.cname%type;
v_pname product.pname%type;
v_cnt call.cnt%type;
v_dname delivery.dname%type;
v_price product.pprice%type;
v_pay customer.cpay%type;
v_date call.finishdate%type;
begin
select ca.callid,cu.cname,pr.pname, ca.cnt,de.dname,pr.pprice,cu.cpay,ca.finishdate
into v_callid,v_cname,v_pname,v_cnt,v_dname,v_price,v_pay,v_date
from call ca ,customer cu, delivery de , product pr
where ca.cid=cu.cid and cu.caddr=de.darea and ca.pid=pr.pid and callid2 = ca.callid;

update product set pnum=pnum +(select cnt from call where callid=callid2)
where pid=(select pid from call where callid=callid2);

delete from call where callid=callid2;

DBMS_OUTPUT.PUT_LINE('[AI 마트] 환불 완료 안내');
DBMS_OUTPUT.PUT_LINE(v_cname ||' 님의 환불요청이 정상적으로 처리 되었습니다.');
DBMS_OUTPUT.PUT_LINE( '환불 요청일 : '|| v_date);
DBMS_OUTPUT.PUT_LINE('========================================');
DBMS_OUTPUT.PUT_LINE( '주문/환불 번호 : '|| callid2);
DBMS_OUTPUT.PUT_LINE( '제품명 : '|| v_pname);
DBMS_OUTPUT.PUT_LINE( '환불 수량 : '|| v_cnt);
DBMS_OUTPUT.PUT_LINE( '환불 금액 : '|| v_price*v_cnt);
DBMS_OUTPUT.PUT_LINE( '환불 방식 : '|| v_pay);
DBMS_OUTPUT.PUT_LINE('========================================');

end;
/
--배송현황 프로시저

create or replace procedure delivery_info
(p_callid call.callid%type)
is 
v_callid call.callid%type;
v_cname customer.cname%type;
v_pname product.pname%type;
v_cnt call.cnt%type;
v_dname delivery.dname%type;
v_finishdate call.finishdate%type;
begin
select ca.callid,cu.cname,pr.pname, ca.cnt,de.dname,ca.finishdate
into v_callid,v_cname,v_pname,v_cnt,v_dname,v_finishdate
from call ca ,customer cu, delivery de , product pr
where ca.cid=cu.cid and cu.caddr=de.darea and ca.pid=pr.pid and p_callid = callid;
DBMS_OUTPUT.PUT_LINE('--------------------------------');
DBMS_OUTPUT.PUT_LINE(v_cname ||' 고객님 배송 정보 입니다.');
DBMS_OUTPUT.PUT_LINE('--------------------------------');
dbms_output.put_line('고객님의 소중한 ' || v_pname || '(이/가) ' || v_finishdate ||' 기한 내 배송 될 예정입니다.');
DBMS_OUTPUT.PUT_LINE(' ');
dbms_output.put_line('----------주문 상세 내역----------');
dbms_output.put_line('    주문번호     : ' || v_callid);
dbms_output.put_line('     상품명      : ' || v_pname);
dbms_output.put_line('    주문수량     : ' || v_cnt);
dbms_output.put_line('   전달원이름    : ' || v_dname);
dbms_output.put_line(' 배송완료 예정일 : ' || v_finishdate);

exception 
when others then dbms_output.put_line ('에러 발생');
end;
/
--주문 추가및 재고수량 감소 프로시저
CREATE OR REPLACE PROCEDURE new_call (
    prc_callid call.callid%type,
    prc_cid customer.cid%type,
    prc_pid product.pid%type,
    prc_pnum product.pnum%TYPE
) IS
    prc_cname customer.cname%TYPE;
    prc_pname product.pname%TYPE;
	prc_caddr customer.caddr%TYPE;
    p_total number;
BEGIN
INSERT INTO call VALUES (prc_callid, prc_cid, prc_pid, prc_pnum, 0, sysdate, sysdate+5);
select cname into prc_cname from customer where cid = prc_cid;
select pname into prc_pname from product where pid=prc_pid;
select caddr into prc_caddr from  customer where cid=prc_cid;
UPDATE call SET total = cnt * (select pprice from product where pid=call.pid) WHERE callid=prc_callid;
select total into p_total from call where callid=prc_callid;
DBMS_OUTPUT.PUT_LINE('------------------------------------------------------');
DBMS_OUTPUT.PUT_LINE(prc_cname  ||' 고객님 주문이 정상적으로 완료되었습니다.');
DBMS_OUTPUT.PUT_LINE('------------------------------------------------------');
DBMS_OUTPUT.PUT_LINE( '주문 번호 : '|| prc_callid);
DBMS_OUTPUT.PUT_LINE( '배송지 정보 : '|| prc_caddr);
DBMS_OUTPUT.PUT_LINE( '제품명 : '|| prc_pname);
DBMS_OUTPUT.PUT_LINE( '주문 수량 : '|| prc_pnum);
DBMS_OUTPUT.PUT_LINE( '총 결제금액은 ' || p_total ||'원 입니다.');
UPDATE product
SET pnum = pnum - prc_pnum
WHERE pid = prc_pid;
END;
/
--총결제 금액 보여주는 프로시저
-- 영수증 프로시저
create or replace procedure call_cprice_info
(p_callid call.callid%type)
is
p_price product.pprice%type;
p_cnt call.cnt%type;
p_pname product.pname%type;
p_cpay customer.cpay%type;
begin
    select p.pprice, c.cnt, p.pname, cu.cpay
    into p_price, p_cnt, p_pname, p_cpay
    from product p, call c, customer cu
    where c.pid=p.pid and c.callid=p_callid and c.cid = cu.cid;
    DBMS_OUTPUT.PUT_LINE('===========================================');
    DBMS_OUTPUT.PUT_LINE('             AI마트 동대구역점');
    DBMS_OUTPUT.PUT_LINE('===========================================');
    DBMS_OUTPUT.PUT_LINE('         주문 번호   : ' || p_callid ||'');
    DBMS_OUTPUT.PUT_LINE('           상품명    : ' || p_pname ||'');
    DBMS_OUTPUT.PUT_LINE('            단가     : ' || p_price ||' ');
    DBMS_OUTPUT.PUT_LINE('            수량     : ' || p_cnt ||' ');
    DBMS_OUTPUT.PUT_LINE('      결제 대상 금액 : ' || p_price*p_cnt ||'원');
    DBMS_OUTPUT.PUT_LINE('===========================================');
    DBMS_OUTPUT.PUT_LINE('         결제 방식   : ' || p_cpay );
    DBMS_OUTPUT.PUT_LINE('===========================================');
exception 
when others then dbms_output.put_line ('에러 발생');
end;
/

create or replace procedure call_cprice_info2
is 
begin
    UPDATE call SET total = cnt * (select pprice from product where pid=call.pid);
exception 
when others then dbms_output.put_line ('에러 발생');
end;
/
execute call_cprice_info2();

--이건 그냥 잘되나 확인하는 문구
SET serveroutput ON;
EXECUTE manager_info('CL001');

SET serveroutput on;
EXECUTE delete_order('CALL001');
EXECUTE delete_order('CALL002');


execute delivery_info('CALL001');
execute delivery_info('CALL002');

execute call_cprice_info('CALL020');
execute new_call('CALL045','cus054','6006',1);