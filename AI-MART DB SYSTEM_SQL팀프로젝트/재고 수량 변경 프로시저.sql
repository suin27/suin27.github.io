--��� ���� ����(����) ���ν���
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
SELECT count(*) �����üũ  into chk_num FROM product WHERE mid=p_mid AND pid = p_pid;
    if chk_num =0 then
        dbms_output.put_line('��ǰ��ȣ�� ���� ����ڰ� ��ġ���� �ʽ��ϴ�');
    end if;
DBMS_OUTPUT.PUT_LINE('----------------------------------------');
DBMS_OUTPUT.PUT_LINE('            ��� ���� ����');
DBMS_OUTPUT.PUT_LINE('----------------------------------------');
dbms_output.put_line(v_name || ' �����ڴ� �ݰ����ϴ�!');
dbms_output.put_line(p_name || '��ǰ�� ������ �����մϴ�.');
dbms_output.put_line('���� �� ���� : '|| p_cnt );
dbms_output.put_line('���� �� ���� : '|| p_pnum);
dbms_output.put_line('-------------------------------');
update product set pnum=p_pnum where pid=p_pid;
EXCEPTION
    WHEN others THEN
        dbms_output.put_line('DB���� �߻�');
END;
/
--��� ���� ����(����) ���ν��� ��� ����
execute update_cnt('CL001','1001',25);