USE db_h5
GO
 
-- 1. Feladat, a) megoldás
SELECT *
  FROM Vevo
  where Orszag NOT IN (SELECT DISTINCT Orszag FROM Szallito)
  ORDER BY VezetekNev, KeresztNev
 
  -- 1. Feladat, b) megoldás
WITH speciorszag AS (
    SELECT Orszag
    FROM Vevo
    WHERE Orszag NOT IN (SELECT DISTINCT Orszag FROM Szallito)
)
SELECT *
  FROM Vevo
  WHERE Orszag IN (SELECT * FROM speciorszag)
  ORDER BY VezetekNev, KeresztNev
 
-- 2. Feladat
SELECT Telepules, COUNT(DISTINCT VevoID) AS VevokSzama, COUNT(DISTINCT TermekID) AS TermekekSzama
  FROM MegrendelesSor
  JOIN Megrendeles ON Megrendeles.ID = MegrendelesSor.MegrendelesID
  JOIN Vevo ON Vevo.ID = Megrendeles.VevoID
  GROUP BY Telepules
  ORDER BY COUNT(DISTINCT VevoID) DESC, COUNT(DISTINCT TermekID)
 
-- 3. Feladat
SELECT AVG(EgysegAR) AS NemKifutottBefottesAtlagar
  FROM Termek
  WHERE Csomagolas LIKE '%jar%'
  AND Kifutott = 0
 
-- 4. Feladat
WITH FaxNelkuliSzallito AS (
    SELECT *
    FROM Szallito
    WHERE Fax = '' OR Fax IS NULL
)
SELECT *
  FROM Termek
  JOIN FaxNelkuliSzallito on FaxNelkuliSzallito.ID = Termek.SzallitoID
  WHERE EgysegAr < (SELECT AVG(EgysegAr) FROM Termek)
 
-- 5. Feladat
SELECT 'Vevo' AS Pozicio, VezetekNev + ' ' + KeresztNev AS Nev, Telepules, Orszag, Telefon
  FROM Vevo
UNION
SELECT 'Szallito' AS Pozicio, Kapcsolattarto AS Nev, Telepules, Orszag, Telefon
  FROM Szallito
ORDER BY Telepules, Nev
 
-- 6. Feladat
SELECT *
  INTO egyet
  FROM (
        SELECT Megnevezes
          FROM MegrendelesSor
          JOIN Termek ON Termek.ID = MegrendelesSor.TermekID
          WHERE Mennyiseg = 1
        ) AS Egyesek
 
-- 7. Feladat
CREATE VIEW vevo2014 AS
SELECT DISTINCT Vevo.*
FROM MegrendelesSor
JOIN Megrendeles ON Megrendeles.ID = MegrendelesSor.MegrendelesID
JOIN Vevo ON Vevo.ID = Megrendeles.VevoID
WHERE TermekID = (
                SELECT TOP 1 TermekID
                  FROM MegrendelesSor
                  JOIN Megrendeles ON Megrendeles.ID = MegrendelesSor.MegrendelesID
                  WHERE YEAR(Datum) = 2014
                  GROUP BY TermekID
                  ORDER BY SUM(Osszeg)
                )
 
-- 8. Feladat
CREATE TABLE Termekek (
    TermekID INT IDENTITY(1,1) PRIMARY KEY,
    Megnevezes VARCHAR(50) UNIQUE NOT NULL,
    Ar REAL NOT NULL CHECK(Ar > 0),
    Csomagolas VARCHAR(30) NOT NULL,
)
GO

INSERT INTO Termekek (Megnevezes, Ar, Csomagolas)
SELECT Megnevezes, EgysegAr
    , CASE
        WHEN Csomagolas LIKE ('%box%') THEN 'box ' + Csomagolas
        WHEN Csomagolas LIKE ('%jar%') THEN 'üveg ' + Csomagolas
        WHEN Csomagolas LIKE ('%bottle%') THEN 'Üveg ' + Csomagolas
		ELSE Csomagolas
      END AS Csomagolas
  FROM Termek
  WHERE Kifutott = 0
 
-- 9. Feladat
UPDATE Termekek
  SET Ar = Ar *
      CASE
        WHEN Csomagolas LIKE ('%box%') THEN 1.1
        WHEN Csomagolas LIKE ('%üveg%') THEN 1.2
		ELSE 1
      END
  WHERE Megnevezes NOT LIKE ('Q%') OR Megnevezes NOT LIKE ('__a%')
 
-- *(1-4) Feladat
WITH HaviBevetel AS (
SELECT DISTINCT YEAR(Datum) AS Ev, MONTH(Datum) AS Honap, TermekID, EgysegAr * Mennyiseg AS Bevetel
  FROM MegrendelesSor
  JOIN Megrendeles ON Megrendeles.ID = MegrendelesSor.MegrendelesID
)
, HaviSum AS (
SELECT Ev, Honap, TermekID, SUM(Bevetel) AS SumBevetel
  FROM HaviBevetel
  GROUP BY Ev, Honap, TermekID
)
SELECT *
  FROM HaviSum AS h
  JOIN Termek ON Termek.ID = h.TermekID
  WHERE SumBevetel = (SELECT MAX(SumBevetel)
		  FROM HaviSum AS hs
		  WHERE h.Ev = hs.Ev
		  AND h.Honap = hs.Honap
		)