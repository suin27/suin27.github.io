-- 테이블 순서는 관계를 고려하여 한 번에 실행해도 에러가 발생하지 않게 정렬되었습니다.
-- manager Table Create SQL
CREATE TABLE manager
(
    mid      VARCHAR2(20)    NOT NULL, 
    mname    VARCHAR2(20)    NOT NULL, 
    mteam    VARCHAR2(30)    NOT NULL, 
     PRIMARY KEY (mid)
)
/
COMMENT ON TABLE manager IS '관리자'
/
COMMENT ON COLUMN manager.mid IS '관리자번호'
/
COMMENT ON COLUMN manager.mname IS '관리자이름'
/
COMMENT ON COLUMN manager.mteam IS '소속'
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
COMMENT ON TABLE customer IS '요구자(손님)'
/

COMMENT ON COLUMN customer.cid IS '회원번호'
/

COMMENT ON COLUMN customer.cpay IS '결제방식'
/

COMMENT ON COLUMN customer.cname IS '이름'
/

COMMENT ON COLUMN customer.caddr IS '주소'
/

COMMENT ON COLUMN customer.ctel IS '휴대폰번호'
/

COMMENT ON COLUMN customer.cjoin IS '가입일'
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
COMMENT ON TABLE product IS '제품'
/
COMMENT ON COLUMN product.pid IS '재고번호'
/
COMMENT ON COLUMN product.pname IS '물건이름'
/
COMMENT ON COLUMN product.ppro IS '생산년도'
/
COMMENT ON COLUMN product.pexp IS '유통기한'
/
COMMENT ON COLUMN product.pcate IS '카테고리'
/
COMMENT ON COLUMN product.psize IS '크기유형'
/
COMMENT ON COLUMN product.pnum IS '재고수량'
/
COMMENT ON COLUMN product.pprice IS '금액'
/
COMMENT ON COLUMN product.pmaker IS '제조사'
/
COMMENT ON COLUMN product.mid IS '관리자번호'
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
COMMENT ON TABLE call IS '주문'
/
COMMENT ON COLUMN call.callid IS '주문번호'
/
COMMENT ON COLUMN call.cid IS '회원번호'
/
COMMENT ON COLUMN call.pid IS '재고번호'
/
COMMENT ON COLUMN call.cnt IS '주문수량'
/
COMMENT ON COLUMN call.total IS '총 결제금액'
/
COMMENT ON COLUMN call.calldate IS '주문날짜'
/
COMMENT ON COLUMN call.finishdate IS '도착날짜'
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
COMMENT ON TABLE delivery IS '전달원(배송업체)'
/
COMMENT ON COLUMN delivery.dname IS '전달원이름'
/
COMMENT ON COLUMN delivery.did IS '전달원번호'
/
COMMENT ON COLUMN delivery.darea IS '담당구역'
/
COMMENT ON COLUMN delivery.dream IS '소속'
/


