--�����Ȳ �� ����
create view delivery_status as
select ca.callid "�ֹ� ��ȣ",
cu.cname "�޴� ���",
pr.pname ����,
ca.cnt "�ֹ� ����",
de.dname ��޿�,
ca.finishdate "��ۿϷ� ��¥"from
call ca ,customer cu, delivery de , product pr where
ca.cid=cu.cid and
cu.caddr=de.darea and
ca.pid=pr.pid
order by callid asc;

--������ ��� ��Ȳ �� ����
create  view MANAGER_STATUS
as 
    select
    mname "������ �̸�",
    pname ��繰��,
    pexp �������,
    pnum ������ 
    from manager natural join product ;
    
--��ۿ� ��Ȳ �� ����
create view dname_view
as
select
de.dname ��޿�,
cu.cname "�޴� ���",
ca.finishdate ��۳�¥,
pr.pname ����
from
call ca ,customer cu, delivery de , product pr
where
ca.cid=cu.cid and
cu.caddr=de.darea and
ca.pid=pr.pid
order by ��۳�¥ asc;