SELECT name from people, stars, movies
WHERE people.id = stars.person_id
AND stars.movie_id = movies.id
AND people.name != "Kevin Bacon"
AND movies.title IN
(SELECT title FROM people, stars, movies
WHERE people.id = stars.person_id
AND stars.movie_id = movies.id
AND people.name = "Kevin Bacon"
AND people.birth = 1958)
;