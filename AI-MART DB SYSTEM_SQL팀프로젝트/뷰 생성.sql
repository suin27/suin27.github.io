--배송현황 뷰 생성
create view delivery_status as
select ca.callid "주문 번호",
cu.cname "받는 사람",
pr.pname 물건,
ca.cnt "주문 수량",
de.dname 배달원,
ca.finishdate "배송완료 날짜"from
call ca ,customer cu, delivery de , product pr where
ca.cid=cu.cid and
cu.caddr=de.darea and
ca.pid=pr.pid
order by callid asc;

--관라지 재고 현황 뷰 생성
create  view MANAGER_STATUS
as 
    select
    mname "관리자 이름",
    pname 담당물건,
    pexp 유통기한,
    pnum 재고수량 
    from manager natural join product ;
    
--배송원 현황 뷰 생성
create view dname_view
as
select
de.dname 배달원,
cu.cname "받는 사람",
ca.finishdate 배송날짜,
pr.pname 물건
from
call ca ,customer cu, delivery de , product pr
where
ca.cid=cu.cid and
cu.caddr=de.darea and
ca.pid=pr.pid
order by 배송날짜 asc;