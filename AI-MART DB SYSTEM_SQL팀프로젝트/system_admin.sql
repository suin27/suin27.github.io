ALTER SESSION SET "_ORACLE_SCRIPT"=true;

--���� / ��� ���� ->  test / 1234
create user test identified by qwer;

-- ���� ���� �ο�
grant connect, resource to test;

-- ���̺����̽� ��� ���� �ο�
alter user test quota unlimited on users;
