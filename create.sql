CREATE DATABASE veggieapp;
USE veggieapp;
CREATE TABLE product (id int IDENTITY PRIMARY KEY, name nvarchar(30), cat_id nvarchar(30));

INSERT INTO product
VALUES
    (N'Яблоки', N'Фрукты'),
    (N'Картофель', N'Овощи'),
    (N'Огурцы', N'Овощи'),
    (N'Капуста', N'Овощи'),
    (N'Апельсин', N'Фрукты');
