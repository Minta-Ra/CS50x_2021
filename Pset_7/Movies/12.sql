-- In 12.sql, write a SQL query to list the titles of all movies in which both Johnny Depp and Helena Bonham Carter starred.

    -- Your query should output a table with a single column for the title of each movie.
    -- You may assume that there is only one person in the database with the name Johnny Depp.
    -- You may assume that there is only one person in the database with the name Helena Bonham Carter.


SELECT movies.title FROM people
JOIN stars ON people.id = stars.person_id
JOIN movies ON stars.movie_id = movies.id
WHERE people.name = "Johnny Depp"
INTERSECT
SELECT movies.title FROM people
JOIN stars ON people.id = stars.person_id
JOIN movies ON stars.movie_id = movies.id
WHERE people.name = "Helena Bonham Carter";


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
-- CREATE TABLE people (
--                 id INTEGER,
--                 name TEXT NOT NULL,
--                 birth NUMERIC,
--                 PRIMARY KEY(id)
--             );