CREATE DATABASE veggieapp
GO
USE veggieapp
GO
CREATE TABLE product (id int IDENTITY PRIMARY KEY, name varchar(30), cat_id varchar(30));

INSERT INTO product
VALUES
    ('Яблоко', 'Фрукты'),
    ('Картофель', 'Овощи'),
    ('Огурец', 'Овощи');
