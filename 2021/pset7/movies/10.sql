SELECT people.name
FROM directors
JOIN people ON directors.person_id = people.id
JOIN movies On directors.movie_id = movies.id
JOIN ratings ON directors.movie_id = ratings.movie_id
WHERE ratings.rating >= 9.0
GROUP BY people.id;