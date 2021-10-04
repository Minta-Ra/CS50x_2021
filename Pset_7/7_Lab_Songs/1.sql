-- In 1.sql, write a SQL query to list the names of all songs in the database.

    -- Your query should output a table with a single column for the name of each song.


SELECT name FROM songs;


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