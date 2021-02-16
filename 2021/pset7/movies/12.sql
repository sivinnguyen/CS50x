-- Or uses INTERSECT instead of "AND IN"
SELECT movies.title
FROM stars
JOIN people ON stars.person_id = people.id
JOIN movies On stars.movie_id = movies.id
WHERE people.name = 'Johnny Depp' AND movies.title IN (
SELECT movies.title
FROM stars
JOIN people ON stars.person_id = people.id
JOIN movies On stars.movie_id = movies.id
WHERE people.name = 'Helena Bonham Carter'
);