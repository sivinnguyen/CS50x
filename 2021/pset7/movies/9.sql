-- DISTINC prevents people with same name from display, uses "GROUP BY" instead
SELECT people.name
FROM stars
JOIN people ON stars.person_id = people.id
JOIN movies On stars.movie_id = movies.id
WHERE movies.year = 2004
GROUP BY people.id
ORDER BY people.birth;