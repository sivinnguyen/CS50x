SELECT people.name
FROM people
JOIN stars ON stars.person_id = people.id
WHERE stars.movie_id IN (
SELECT movies.id
FROM people
JOIN stars ON stars.person_id = people.id
JOIN movies ON stars.movie_id = movies.id
WHERE people.name = 'Kevin Bacon' AND people.birth = 1958
) AND stars.person_id NOT IN (
SELECT id
FROM people
WHERE name = 'Kevin Bacon' AND birth = 1958
) GROUP BY people.id;