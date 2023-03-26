ALTER SESSION SET "_ORACLE_SCRIPT"=true;

--계정 / 비번 생성 ->  test / 1234
create user test identified by qwer;

-- 접속 권한 부여
grant connect, resource to test;

-- 테이블스페이스 사용 권한 부여
alter user test quota unlimited on users;
