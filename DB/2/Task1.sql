USE AdventureWorks2012;
GO

SELECT E.BusinessEntityID, E.JobTitle, B.RateChangeDate as LastRateDate
FROM HumanResources.Employee E 
INNER JOIN (
	SELECT MAX(RateChangeDate) as RateChangeDate, BusinessEntityID 
	FROM HumanResources.EmployeePayHistory
	GROUP BY BusinessEntityID
) B ON E.BusinessEntityID = B.BusinessEntityID;
GO

SELECT E.BusinessEntityID, E.JobTitle, dep.Name as DepName, EH.StartDate, EH.EndDate, EH.Years
FROM HumanResources.Employee E
INNER JOIN (
	SELECT DATEDIFF(year, StartDate, ISNULL(EndDate, GETDATE())) as Years, BusinessEntityID, DepartmentID, StartDate, EndDate
	FROM HumanResources.EmployeeDepartmentHistory
) EH
ON EH.BusinessEntityID = E.BusinessEntityID
INNER JOIN HumanResources.Department dep on EH.DepartmentID = dep.DepartmentID
GO

SELECT 
	E.BusinessEntityID, E.JobTitle,
	dep.Name as DepName, dep.GroupName,
	CASE CHARINDEX(' ', dep.GroupName, 1)
		WHEN 0 THEN dep.GroupName
		ELSE SUBSTRING(dep.GroupName, 1, CHARINDEX(' ', dep.GroupName, 1) - 1)
	END as DepGroup
FROM HumanResources.Employee E
INNER JOIN HumanResources.EmployeeDepartmentHistory EH
ON EH.BusinessEntityID = E.BusinessEntityID AND EH.EndDate IS NULL
INNER JOIN HumanResources.Department dep on EH.DepartmentID = dep.DepartmentID
GO
