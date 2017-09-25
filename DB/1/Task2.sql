USE AdventureWorks2012

SELECT COUNT(*) as DepartmentCount FROM HumanResources.Department WHERE GroupName = 'Executive General and Administration'
GO

SELECT TOP 5 BusinessEntityID, JobTitle, Gender, BirthDate FROM HumanResources.Employee ORDER BY BirthDate DESC;
GO

SELECT BusinessEntityID, JobTitle, Gender, HireDate, Replace(LoginID, 'adventure-works', 'adventure-works2012') as LoginID FROM HumanResources.Employee WHERE Gender = 'F' AND DATEPART(DW, HireDate) = 3