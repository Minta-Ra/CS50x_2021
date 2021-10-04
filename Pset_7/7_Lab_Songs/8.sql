-- In 8.sql, write a SQL query that lists the names of the songs that feature other artists.

    -- Songs that feature other artists will include “feat.” in the name of the song.
    -- Your query should output a table with a single column for the name of each song.


SELECT name FROM songs WHERE name LIKE "%feat.%";


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