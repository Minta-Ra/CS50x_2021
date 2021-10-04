-- In 7.sql, write a SQL query that returns the average energy of songs that are by Drake.

    -- Your query should output a table with a single column and a single row containing the average energy.
    -- You should not make any assumptions about what Drake’s artist_id is.


SELECT AVG(energy) FROM songs WHERE artist_id = (SELECT id FROM artists WHERE name = "Drake");


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