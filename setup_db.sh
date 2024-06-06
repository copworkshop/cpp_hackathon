#!/bin/bash

# Update package lists
sudo apt-get update

# Install MySQL Server
sudo apt-get install -y mysql-server

# Start MySQL service
sudo service mysql start
sudo service mysql status
# Create a new MySQL database
mysql -u root -e "CREATE DATABASE mydatabase;"

# Create a new table in the database
mysql -u root -e "
    USE mydatabase;
    CREATE TABLE inventory (
        id INT AUTO_INCREMENT PRIMARY KEY,
        name VARCHAR(255),
        sellby INT,
        value INT
    );
"

# Insert records into the table
mysql -u root -e "
    USE mydatabase;
    INSERT INTO inventory (name, sellby, value) VALUES
    ('Polka Dot Begonia', 5, 30),
    ('Gardening Workshop', 15, 20),
    ('White Monstera', 7, 80),
    ('Orchid', 10, 50),
    ('Cactus', 6, 10);
"