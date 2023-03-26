--구현한 5개의 테이블 소개 및 칼럼 소개.
select * from product;
select * from customer;
select * from call;
select * from delivery;
select * from manager;

--구현한 3개의 뷰 소개및 내용 소개.
select * from delivery_status;
select * from dname_view;
select * from manager_status;

--한 제품을 예시로 주문 추가시 주문칼럼의 증가와 주문한 재고 수량 변동을 소개.
select* from product where pid='6001';
INSERT INTO call VALUES ('CALL089', 'cus080', '6001', 1, 0, sysdate, sysdate+5);
UPDATE product SET pnum = pnum - 1 WHERE pid = '6001';
select * from call;
select* from product where pid='6001';

--위에 주문 추가의 반대. 주문감소 와 재고 변동 소개
update product set pnum=pnum +(select cnt from call where callid='CALL089')
where pid=(select pid from call where callid='CALL089');
delete from call where callid='CALL089';
select * from call;
select * from poduct where pid='6001';
--검색 추가 삭제 수정 시연.
--검색 추가 삭제 수정을 구현하다 보니 하나의 기능에 여러개의 쿼리가 필요한 경우가 발생.
--ex) 주문 추가의 경우 주문한 제품의 수량 변동이 필요, 주문 테이블에 새로운 주문 행 추가 필요. 밑 안내 문구 필요성.
--이에 따른 5개의 프로시저 구현과 그 소개.

SET serveroutput ON;

--한명의 관리자가 자신이 담당해서 관리하는 제품만 확인하고 싶을때 사용.
EXECUTE manager_info('CL001');

--주문한 고객이 주문취소를 하는 경우.
EXECUTE delete_order('CALL003'); -- 주문테이블에서 원하는 행 삭제와 더불어 그에 따른 제품의 재고 수량 변동(증가)
select * from call; -- 제대로 주문이 취소되고 삭제되었는지 확인및 보여줌.

--고객이 새로운 주문을 할때 (물건을 구입할때
execute new_call('CALL063','cus065','6002',1);--주문 테이블에서 한행 추가와 더불어 그에 따른 제품의 재고 수량 변동(감소)
select * from call;

--배달현황, 손님이 자신이 주문한 주문의 현재 상태를 나타냄. ex) 주문한 제품명과 수량 배달 담당자 이름과 예상 배달 완료 날짜.
execute delivery_info('CALL001');
execute delivery_info('CALL002');

--총결제 금액 확인및 업데이트 용
execute call_cprice_info('CALL012');
select ca.callid, pr.pname, ca.cnt, ca.total from call ca inner join product pr on ca.pid=pr.pid ;

execute update_cnt('CL001','1001',25);