CREATE DATABASE veggieapp
GO
USE veggieapp;

CREATE TABLE category (
    id int IDENTITY PRIMARY KEY,
    name nvarchar(30)
);

INSERT INTO category
VALUES
    (N'Фрукты'),
    (N'Овощи'),
    (N'Грибы');

CREATE TABLE product (
    id int IDENTITY PRIMARY KEY,
    name nvarchar(30),
    cat_id int,
    img varchar(MAX),
    delivery_date date,

    CONSTRAINT FK_product_category FOREIGN KEY (cat_id)
    REFERENCES category (id)
);

INSERT INTO product
VALUES
    (N'Яблоки', 1, 'img/apples.jpg', '1970-01-01'),
    (N'Картофель', 2, 'img/dummy.jpg', '1970-01-01'),
    (N'Огурцы', 2, 'img/dummy.jpg', '1970-01-01'),
    (N'Апельсины', 1, 'img/dummy.jpg', '1970-01-01'),
    (N'Лисички', 3, 'img/dummy.jpg', '1970-01-01');
