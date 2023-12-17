CREATE DATABASE veggieapp
GO
USE veggieapp;

CREATE TABLE product (
    id int IDENTITY PRIMARY KEY,
    name nvarchar(30),
    cat_id nvarchar(30),
    img varchar(MAX),
    delivery_date date
);

INSERT INTO product
VALUES
    (N'Яблоки', N'Фрукты', 'img/apples.jpg', '1970-01-01'),
    (N'Картофель', N'Овощи', 'img/dummy.jpg', '1970-01-01'),
    (N'Огурцы', N'Овощи', 'img/dummy.jpg', '1970-01-01'),
    (N'Капуста', N'Овощи', 'img/dummy.jpg', '1970-01-01'),
    (N'Апельсин', N'Фрукты', 'img/dummy.jpg', '1970-01-01');
