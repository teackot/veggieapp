CREATE DATABASE veggieapp;
USE veggieapp;
CREATE TABLE product (id int IDENTITY PRIMARY KEY, name varchar(30), cat_id varchar(30));

INSERT INTO product
VALUES
    ('Apple', 'Fruits'),
    ('Potato', 'Vegetables'),
    ('Cucumber', 'Vegetables');

INSERT INTO product
VALUES
    ('Cabbage', 'Vegetables');

INSERT INTO product
VALUES
    ('Orange', 'Fruits');