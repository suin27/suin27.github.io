--������ 5���� ���̺� �Ұ� �� Į�� �Ұ�.
select * from product;
select * from customer;
select * from call;
select * from delivery;
select * from manager;

--������ 3���� �� �Ұ��� ���� �Ұ�.
select * from delivery_status;
select * from dname_view;
select * from manager_status;

--�� ��ǰ�� ���÷� �ֹ� �߰��� �ֹ�Į���� ������ �ֹ��� ��� ���� ������ �Ұ�.
select* from product where pid='6001';
INSERT INTO call VALUES ('CALL089', 'cus080', '6001', 1, 0, sysdate, sysdate+5);
UPDATE product SET pnum = pnum - 1 WHERE pid = '6001';
select * from call;
select* from product where pid='6001';

--���� �ֹ� �߰��� �ݴ�. �ֹ����� �� ��� ���� �Ұ�
update product set pnum=pnum +(select cnt from call where callid='CALL089')
where pid=(select pid from call where callid='CALL089');
delete from call where callid='CALL089';
select * from call;
select * from poduct where pid='6001';
--�˻� �߰� ���� ���� �ÿ�.
--�˻� �߰� ���� ������ �����ϴ� ���� �ϳ��� ��ɿ� �������� ������ �ʿ��� ��찡 �߻�.
--ex) �ֹ� �߰��� ��� �ֹ��� ��ǰ�� ���� ������ �ʿ�, �ֹ� ���̺� ���ο� �ֹ� �� �߰� �ʿ�. �� �ȳ� ���� �ʿ伺.
--�̿� ���� 5���� ���ν��� ������ �� �Ұ�.

SET serveroutput ON;

--�Ѹ��� �����ڰ� �ڽ��� ����ؼ� �����ϴ� ��ǰ�� Ȯ���ϰ� ������ ���.
EXECUTE manager_info('CL001');

--�ֹ��� ���� �ֹ���Ҹ� �ϴ� ���.
EXECUTE delete_order('CALL003'); -- �ֹ����̺��� ���ϴ� �� ������ ���Ҿ� �׿� ���� ��ǰ�� ��� ���� ����(����)
select * from call; -- ����� �ֹ��� ��ҵǰ� �����Ǿ����� Ȯ�ι� ������.

--���� ���ο� �ֹ��� �Ҷ� (������ �����Ҷ�
execute new_call('CALL063','cus065','6002',1);--�ֹ� ���̺��� ���� �߰��� ���Ҿ� �׿� ���� ��ǰ�� ��� ���� ����(����)
select * from call;

--�����Ȳ, �մ��� �ڽ��� �ֹ��� �ֹ��� ���� ���¸� ��Ÿ��. ex) �ֹ��� ��ǰ��� ���� ��� ����� �̸��� ���� ��� �Ϸ� ��¥.
execute delivery_info('CALL001');
execute delivery_info('CALL002');

--�Ѱ��� �ݾ� Ȯ�ι� ������Ʈ ��
execute call_cprice_info('CALL012');
select ca.callid, pr.pname, ca.cnt, ca.total from call ca inner join product pr on ca.pid=pr.pid ;

execute update_cnt('CL001','1001',25);