-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Read crime scene reports: July 28th 2020, Chamberlin Street
SELECT description
FROM crime_scene_reports
WHERE year = 2020 AND month = 7 AND day = 28
AND street = 'Chamberlin Street';

-- Read interview transcript of witnesses: 3 withnesses, courthouse mentioning
SELECT name, transcript
FROM interviews
WHERE year = 2020 AND month = 7 AND day = 28
AND transcript LIKE '%courthouse%';

-- Ruth: courthouse parking lot, 10 minutes within, drive away
SELECT hour, minute, license_plate, activity
FROM courthouse_security_logs
WHERE year = 2020 AND month = 7 AND day = 28
AND hour = 10 AND minute BETWEEN 15 AND 25
AND activity = 'exit';

-- Eugene: early morning, ATM on Fifer Street, money withdrawing
SELECT account_number, amount, transaction_type, atm_location
FROM atm_transactions
WHERE year = 2020 AND month = 7 AND day = 28
AND transaction_type = 'withdraw'
AND atm_location = 'Fifer Street';

-- Raymond: called someone, less than a minute, take the earliest flight out of Fiftyville tomorrow
SELECT caller, receiver, duration
FROM phone_calls
WHERE year = 2020 AND month = 7 AND day = 28
AND duration < 60;

-- Passengers are going to leave Fiftyville on July 29
SELECT name
FROM people
WHERE passport_number IN (
    SELECT passport_number
    FROM passengers
    WHERE flight_id IN (
        SELECT flights.id
        FROM flights
        JOIN airports ON airports.id = flights.origin_airport_id
        WHERE airports.city = 'Fiftyville'
        AND flights.year = 2020 AND flights.month = 7 AND flights.day = 29
        -- the earliest flight out
        ORDER BY hour ASC, minute ASC
        LIMIT 1
    )
);

-- Combine things together, the THIEF is
SELECT *
FROM people
WHERE license_plate IN (
    SELECT license_plate
    FROM courthouse_security_logs
    WHERE year = 2020 AND month = 7 AND day = 28
    AND hour = 10 AND minute BETWEEN 15 AND 25
    AND activity = 'exit')
AND id IN (
    SELECT bank_accounts.person_id
    FROM bank_accounts
    JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
    WHERE atm_transactions.year = 2020 AND atm_transactions.month = 7 AND atm_transactions.day = 28
    AND atm_transactions.transaction_type = 'withdraw'
    AND atm_transactions.atm_location = 'Fifer Street')
AND people.phone_number IN (
    SELECT caller
    FROM phone_calls
    WHERE year = 2020 AND month = 7 AND day = 28
    AND duration < 60)
AND people.passport_number IN (
    SELECT passport_number
    FROM passengers
    WHERE flight_id IN (
        SELECT flights.id
        FROM flights
        JOIN airports ON airports.id = flights.origin_airport_id
        WHERE airports.city = 'Fiftyville'
        AND flights.year = 2020 AND flights.month = 7 AND flights.day = 29
        ORDER BY hour ASC, minute ASC
        LIMIT 1
    )
);

-- The thief ESCAPED TO
SELECT *
FROM airports
WHERE id IN (
    SELECT flights.destination_airport_id
    FROM flights
    JOIN passengers ON passengers.flight_id = flights.id
    WHERE passengers.passport_number = 5773159633
    AND flights.year = 2020 AND flights.month = 7 AND flights.day = 29
);

-- The ACCOMPLICE is
SELECT *
FROM people
WHERE phone_number IN (
    SELECT receiver
    FROM phone_calls
    WHERE year = 2020 AND month = 7 AND day = 28
    AND duration < 60 AND caller = '(367) 555-5533'
);
