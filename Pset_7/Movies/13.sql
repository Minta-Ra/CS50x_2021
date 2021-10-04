-- In 13.sql, write a SQL query to list the names of all people who starred in a movie in which Kevin Bacon also starred.

    -- Your query should output a table with a single column for the name of each person.
    -- There may be multiple people named Kevin Bacon in the database. Be sure to only select the Kevin Bacon born in 1958.
    -- Kevin Bacon himself should not be included in the resulting list.


SELECT DISTINCT name FROM people
JOIN stars ON people.id = stars.person_id
JOIN movies ON stars.movie_id = movies.id
WHERE movies.title IN
(SELECT DISTINCT movies.title FROM people
JOIN stars ON people.id = stars.person_id
JOIN movies ON stars.movie_id = movies.id
WHERE people.name = "Kevin Bacon" AND people.birth = 1958)
AND people.name != "Kevin Bacon";


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