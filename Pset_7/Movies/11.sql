-- In 11.sql, write a SQL query to list the titles of the five highest rated movies (in order) that Chadwick Boseman starred in, starting with the highest rated.

    -- Your query should output a table with a single column for the title of each movie.
    -- You may assume that there is only one person in the database with the name Chadwick Boseman.


SELECT movies.title FROM people
-- get only stars from people
JOIN stars ON people.id = stars.person_id
-- get only movies by stars
JOIN movies ON stars.movie_id = movies.id
-- get ratings of those movies
JOIN ratings ON movies.id = ratings.movie_id
-- movies that Chadwick Boseman starred
WHERE people.name = "Chadwick Boseman"
ORDER BY rating DESC
-- only 5 highest rated movies
LIMIT 5;


-- CREATE TABLE movies (
--                     id INTEGER,
--                     title TEXT NOT NULL,
--                     year NUMERIC,
--                     PRIMARY KEY(id)
--                 );
-- CREATE TABLE stars (
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