-- In 4.sql, write a SQL query that lists the names of any songs that have danceability, energy, and valence greater than 0.75.

    -- Your query should output a table with a single column for the name of each song.


SELECT name FROM songs WHERE danceability > 0.75 AND energy > 0.75 AND valence > 0.75;


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