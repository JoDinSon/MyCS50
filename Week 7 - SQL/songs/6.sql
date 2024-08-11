SELECT name FROM songs WHERE artist_id = (SELECT id FROM artists WHERE name = "Post Malone");
-- selects all songs of the Artist Post Malone