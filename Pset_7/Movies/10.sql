-- In 10.sql, write a SQL query to list the names of all people who have directed a movie that received a rating of at least 9.0.

    -- Your query should output a table with a single column for the name of each person.
    -- If a person directed more than one movie that received a rating of at least 9.0, they should only appear in your results once.


SELECT DISTINCT name FROM people
-- get only directors from people
JOIN directors ON people.id = directors.person_id
-- get only movies by those directors
JOIN movies ON directors.movie_id = movies.id
-- get ratings of all the movies
JOIN ratings ON movies.id = ratings.movie_id
-- get only movies >= 9
WHERE ratings.rating >= 9.0;


-- CREATE TABLE movies (
--                     id INTEGER,
--                     title TEXT NOT NULL,
--                     year NUMERIC,
--                     PRIMARY KEY(id)
--                 );
-- CREATE TABLE directors (
--                 movie_id INTEGER NOT NULL,
--                 person_id INTEGER NOT NULL,
--                 FOREIGN KEY(movie_id) REFERENCES movies(id),
--                 FOREIGN KEY(person_id) REFERENCES people(id)
--             );
-- CREATE TABLE ratings (
--                 movie_id INTEGER NOT NULL,
--                 rating REAL NOT NULL,
--                 votes INTEGER NOT NULL,
--                 FOREIGN KEY(movie_id) REFERENCES movies(id)
--             );
-- CREATE TABLE people (
--                 id INTEGER,
--                 name TEXT NOT NULL,
--                 birth NUMERIC,
--                 PRIMARY KEY(id)
--             );