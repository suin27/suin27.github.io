--재고 수량 수정(변경) 프로시저
CREATE OR REPLACE PROCEDURE update_cnt (
    p_mid in product.mid%TYPE,
    p_pid in product.pid%type,
    p_pnum in product.pnum%type
) IS
chk_num number;
p_name VARCHAR2(20);
v_name varchar2(20);
p_cnt number;
BEGIN
select pnum into p_cnt from product where pid=p_pid;
select mname into v_name from manager WHERE mid=p_mid;
select pname into p_name from product WHERE mid=p_mid AND pid = p_pid;
SELECT count(*) 담당자체크  into chk_num FROM product WHERE mid=p_mid AND pid = p_pid;
    if chk_num =0 then
        dbms_output.put_line('제품번호와 관리 담당자가 일치하지 않습니다');
    end if;
DBMS_OUTPUT.PUT_LINE('----------------------------------------');
DBMS_OUTPUT.PUT_LINE('            재고 수량 수정');
DBMS_OUTPUT.PUT_LINE('----------------------------------------');
dbms_output.put_line(v_name || ' 관리자님 반갑습니다!');
dbms_output.put_line(p_name || '제품의 수량을 변경합니다.');
dbms_output.put_line('변경 전 수량 : '|| p_cnt );
dbms_output.put_line('변경 후 수량 : '|| p_pnum);
dbms_output.put_line('-------------------------------');
update product set pnum=p_pnum where pid=p_pid;
EXCEPTION
    WHEN others THEN
        dbms_output.put_line('DB에러 발생');
END;
/
--재고 수량 변경(수정) 프로시저 사용 예시
execute update_cnt('CL001','1001',25);