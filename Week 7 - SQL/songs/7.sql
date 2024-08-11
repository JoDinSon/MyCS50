SELECT avg(energy) FROM songs WHERE artist_id = (SELECT id FROM artists WHERE name = "Drake");
-- returns average energy of all songs of the artist Drake