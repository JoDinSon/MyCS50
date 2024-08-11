SELECT * FROM shows;
UPDATE shows SET title = "How I Met Your Mother" WHERE title = "How i met your mother";
UPDATE shows SET title = "The Office" WHERE title LIKE "The Office";
-- Befehl hat mehrere shows in der liste zu the office geändert... Lieber erst mal mit SELECT ausprobieren was ich bekomme

SELECT * FROM shows WHERE title LIKE "The Office";
-- Es gab einfach schon vorher mehrere "The Office".
UPDATE shows SET title = "The Office" WHERE title LIKE "The Office";
-- Verbessert eine Version von the Office aber nicht "thevoffice";

UPDATE shows SET title = "The Office" WHERE title LIKE "The%Office";
-- Dieser Befehl aktualisiert alle "The Office" in die korrekte Schreibweise
