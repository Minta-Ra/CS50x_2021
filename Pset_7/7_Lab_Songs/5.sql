-- In 5.sql, write a SQL query that returns the average energy of all the songs.

    -- Your query should output a table with a single column and a single row containing the average energy.


SELECT AVG(energy) FROM songs;


-- CREATE TABLE songs (
--     id INTEGER,
--     name TEXT,
--     artist_id INTEGER,
--     danceability REAL,
--     energy REAL,
--     key INTEGER,
--     loudness REAL,
--     speechiness REAL,
--     valence REAL,
--     tempo REAL,
--     duration_ms INTEGER
-- );
-- CREATE TABLE artists (
--     id INTEGER,
--     name TEXT
-- );