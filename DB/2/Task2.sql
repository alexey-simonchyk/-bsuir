USE NewDatabase;
GO

CREATE TABLE dbo.PersonPhone(
	[BusinessEntityID] [int] NOT NULL,
	[PhoneNumber] [nvarchar](50) NOT NULL,
	[PhoneNumberTypeID] [int] NOT NULL,
	[ModifiedDate] [datetime] NOT NULL
)
GO

ALTER TABLE dbo.PersonPhone ADD PRIMARY KEY(BusinessEntityID, PhoneNumber);
ALTER TABLE dbo.PersonPhone ADD PostalCode nvarchar(15) CONSTRAINT check_Letters CHECK (PostalCode NOT LIKE '[A-Za-z]');
ALTER TABLE dbo.PersonPhone ADD CONSTRAINT df_postal_code DEFAULT '0' for PostalCode;

INSERT INTO dbo.PersonPhone (BusinessEntityID, PhoneNumber, PhoneNumberTypeID, ModifiedDate)
	SELECT a.BusinessEntityID, a.PhoneNumber, a.PhoneNumberTypeID, a.ModifiedDate 
	FROM AdventureWorks2012.Person.PersonPhone a
	INNER JOIN AdventureWorks2012.Person.PhoneNumberType t 
	ON t.PhoneNumberTypeID = a.PhoneNumberTypeID 
WHERE t.Name LIKE 'Cell';

ALTER TABLE dbo.PersonPhone ALTER COLUMN PhoneNumberTypeID bigint null;
