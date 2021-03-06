USE master;

IF EXISTS(select * from sys.databases where name='NewDatabase')
DROP DATABASE NewDatabase

CREATE DATABASE NewDatabase;
GO

USE NewDatabase;
GO

CREATE SCHEMA sales;
GO

CREATE TABLE sales.Orders (OrderNum INT NULL);

BACKUP DATABASE NewDatabase
TO DISK = 'E:\DB_Backup.Bak';
GO

USE master;
GO

DROP DATABASE NewDatabase;
GO

RESTORE DATABASE NewDatabase
FROM Disk = 'E:\DB_Backup.Bak';
GO
