import sqlite3

connection = sqlite3.connect("movies.db")
cursor = connection.cursor()

# sq1 = cursor.execute("SELECT title FROM movies WHERE year = 2008;").fetchmany(5)
# sq2 = cursor.execute("SELECT birth FROM people WHERE name = 'Emma Stone'").fetchall()
# sq3 = cursor.execute("SELECT title FROM movies WHERE year >= 2018 ORDER BY title ASC").fetchmany(10)

print("\n")
for item in sq3:
    print(item)
print("\n")