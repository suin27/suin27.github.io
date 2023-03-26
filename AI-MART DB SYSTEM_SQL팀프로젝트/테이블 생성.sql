-- ���̺� ������ ���踦 ����Ͽ� �� ���� �����ص� ������ �߻����� �ʰ� ���ĵǾ����ϴ�.
-- manager Table Create SQL
CREATE TABLE manager
(
    mid      VARCHAR2(20)    NOT NULL, 
    mname    VARCHAR2(20)    NOT NULL, 
    mteam    VARCHAR2(30)    NOT NULL, 
     PRIMARY KEY (mid)
)
/
COMMENT ON TABLE manager IS '������'
/
COMMENT ON COLUMN manager.mid IS '�����ڹ�ȣ'
/
COMMENT ON COLUMN manager.mname IS '�������̸�'
/
COMMENT ON COLUMN manager.mteam IS '�Ҽ�'
/
-- customer Table Create SQL
CREATE TABLE customer
(
    cid      VARCHAR2(20)    NOT NULL, 
    cpay     VARCHAR2(20)    NOT NULL, 
    cname    VARCHAR2(20)    NOT NULL, 
    caddr    VARCHAR2(20)    NOT NULL, 
    ctel     VARCHAR2(20)    NOT NULL, 
    cjoin    VARCHAR2(20)    NOT NULL, 
     PRIMARY KEY (cid)
)
/
COMMENT ON TABLE customer IS '�䱸��(�մ�)'
/

COMMENT ON COLUMN customer.cid IS 'ȸ����ȣ'
/

COMMENT ON COLUMN customer.cpay IS '�������'
/

COMMENT ON COLUMN customer.cname IS '�̸�'
/

COMMENT ON COLUMN customer.caddr IS '�ּ�'
/

COMMENT ON COLUMN customer.ctel IS '�޴�����ȣ'
/

COMMENT ON COLUMN customer.cjoin IS '������'
/
-- product Table Create SQL
CREATE TABLE product
(
    pid       VARCHAR2(20)    NOT NULL, 
    pname     VARCHAR2(20)    NOT NULL, 
    ppro      VARCHAR2(20)    NOT NULL, 
    pexp      NUMBER          NULL, 
    pcate     VARCHAR2(20)    NOT NULL, 
    psize     VARCHAR2(20)    NOT NULL, 
    pnum      NUMBER          NOT NULL, 
    pprice    NUMBER          NOT NULL, 
    pmaker    VARCHAR2(20)    NOT NULL, 
    mid       VARCHAR2(20)    NOT NULL, 
     PRIMARY KEY (pid)
)
/
COMMENT ON TABLE product IS '��ǰ'
/
COMMENT ON COLUMN product.pid IS '����ȣ'
/
COMMENT ON COLUMN product.pname IS '�����̸�'
/
COMMENT ON COLUMN product.ppro IS '����⵵'
/
COMMENT ON COLUMN product.pexp IS '�������'
/
COMMENT ON COLUMN product.pcate IS 'ī�װ�'
/
COMMENT ON COLUMN product.psize IS 'ũ������'
/
COMMENT ON COLUMN product.pnum IS '������'
/
COMMENT ON COLUMN product.pprice IS '�ݾ�'
/
COMMENT ON COLUMN product.pmaker IS '������'
/
COMMENT ON COLUMN product.mid IS '�����ڹ�ȣ'
/
ALTER TABLE product
    ADD CONSTRAINT FK_product_mid_manager_mid FOREIGN KEY (mid)
        REFERENCES manager (mid)  
/
-- call Table Create SQL
CREATE TABLE call
(
    callid        VARCHAR2(20)    NOT NULL, 
    cid           VARCHAR2(20)    NOT NULL, 
    pid           VARCHAR2(20)    NOT NULL, 
    cnt           NUMBER          NOT NULL, 
    total         NUMBER          NOT NULL, 
    calldate      VARCHAR2(20)    NOT NULL, 
    finishdate    VARCHAR2(20)    NOT NULL, 
     PRIMARY KEY (cid, pid)
)
/
COMMENT ON TABLE call IS '�ֹ�'
/
COMMENT ON COLUMN call.callid IS '�ֹ���ȣ'
/
COMMENT ON COLUMN call.cid IS 'ȸ����ȣ'
/
COMMENT ON COLUMN call.pid IS '����ȣ'
/
COMMENT ON COLUMN call.cnt IS '�ֹ�����'
/
COMMENT ON COLUMN call.total IS '�� �����ݾ�'
/
COMMENT ON COLUMN call.calldate IS '�ֹ���¥'
/
COMMENT ON COLUMN call.finishdate IS '������¥'
/
CREATE UNIQUE INDEX UQ_call_1
    ON call(callid)
/
ALTER TABLE call
    ADD CONSTRAINT FK_call_cid_customer_cid FOREIGN KEY (cid)
        REFERENCES customer (cid)
/
ALTER TABLE call
    ADD CONSTRAINT FK_call_pid_product_pid FOREIGN KEY (pid)
        REFERENCES product (pid)  
/
-- delivery Table Create SQL
CREATE TABLE delivery
(
    dname    VARCHAR2(20)    NOT NULL, 
    did      VARCHAR2(20)    NOT NULL, 
    darea    VARCHAR2(20)    NOT NULL, 
    dream    VARCHAR2(20)    NOT NULL, 
     PRIMARY KEY (dname)
)
/
COMMENT ON TABLE delivery IS '���޿�(��۾�ü)'
/
COMMENT ON COLUMN delivery.dname IS '���޿��̸�'
/
COMMENT ON COLUMN delivery.did IS '���޿���ȣ'
/
COMMENT ON COLUMN delivery.darea IS '��籸��'
/
COMMENT ON COLUMN delivery.dream IS '�Ҽ�'
/


