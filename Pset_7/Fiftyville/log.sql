-- Keep a log of any SQL queries you execute as you solve the mystery.

-- All you know is that the theft took place on July 28, 2020 and that it took place on Chamberlin Street.

------------------------------------------------------------------------------------------------------------------------------
-- ADDITIONAL INFORMATION

-- Determine who the thief is
SELECT description FROM crime_scene_reports WHERE year = 2020 AND month = 7 AND day = 28 AND street = "Chamberlin Street";
-- Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse.
-- Interviews were conducted today with three witnesses who were present at the time — each of their interview transcripts mentions the courthouse.


SELECT name FROM interviews
WHERE year = 2020 AND month = 7 AND day = 28 AND transcript LIKE "%courthouse%"
-- witnesses: Ruth, Eugene, Raymond


SELECT activity, license_plate FROM courthouse_security_logs
WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 20;
-- exit | 5P2BI95
-- exit | 94KL13X
-- exit | 6P58WS2
-- exit | 4328GD8

------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------
-- FIND A THIEF

SELECT name FROM people

WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs
WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 20
)
-- Patrick
-- Amber
-- Danielle
-- Ernest


-- SELECT name, id, phone_number, passport_number FROM people
-- WHERE license_plate = "5P2BI95" OR license_plate = "94KL13X" OR license_plate = "6P58WS2" OR license_plate = "4328GD8";

-- Patrick | 221103 | (725) 555-4692 | 2963008352
-- Amber | 243696 | (301) 555-4174 | 7526138472
-- Danielle | 467400 | (389) 555-5198 | 8496433585
-- Ernest | 686048 | (367) 555-5533 | 5773159633


-- QUERY ATM TRANSACTIONS
AND people.id IN (
SELECT DISTINCT person_id FROM bank_accounts
JOIN people ON bank_accounts.person_id = people.id
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
WHERE atm_transactions.year = 2020 AND atm_transactions.month = 7 AND atm_transactions.day = 28
AND people.id = 221103 OR people.id = 243696 OR people.id = 467400 OR people.id = 686048
)
-- person_id, bank_accounts.account_number
-- 243696 | 56171033
-- 467400 | 28500762
-- 686048 | 49610011


-- SELECT DISTINCT transaction_type, atm_location FROM atm_transactions
-- WHERE year = 2020 AND month = 7 AND day = 28 AND account_number = 49610011 OR account_number = 28500762 OR account_number = 56171033;

-- deposit | Fifer Street
-- deposit | Blumberg Boulevard
-- withdraw | Fifer Street
-- deposit | Daboin Sanchez Drive
-- withdraw | Blumberg Boulevard
-- withdraw | Daboin Sanchez Drive
-- withdraw | Humphrey Lane
-- withdraw | Carvalho Road

-- QUERY PHONE CALLS
AND people.phone_number IN (
SELECT caller FROM phone_calls
WHERE year = 2020 AND month = 7 AND day = 28
AND duration < 60
)

-- QUERY PASSENGER LIST
AND people.passport_number IN (
SELECT passport_number from passengers
WHERE flight_id IN (SELECT id FROM flights WHERE year = 2020 AND month = 7)
);

----------------------------
-- name
-- Ernest
----------------------------

------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------
-- WHERE THE THIEF ESCAPED TO

-- When Ernest traveled recently?
SELECT flight_id FROM passengers
WHERE passport_number = "5773159633"
-- 36

SELECT year, month, day FROM flights
WHERE id = 36;
-- 2020 | 7 | 29


SELECT city FROM airports
WHERE id IN (SELECT destination_airport_id FROM flights
WHERE year = 2020 AND month = 7 AND day = 29
ORDER BY hour, minute ASC LIMIT 1);

----------------------------
-- city
-- London
----------------------------

------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------
-- IDENTIFY WHO THE THIEF'S ACCOMPLICE WAS WHO HELPED THEM ESCAPE TOWN

-- SELECT duration FROM phone_calls
-- WHERE year = 2020 AND month = 7 AND day = 28
-- AND caller = (SELECT phone_number FROM people WHERE name = "Ernest");

-- duration
-- 45
-- 120
-- 241
-- 75


SELECT name FROM people
WHERE phone_number IN (SELECT receiver FROM phone_calls
WHERE year = 2020 AND month = 7 AND day = 28
AND caller = (SELECT phone_number FROM people WHERE name = "Ernest") AND duration < 60);

----------------------------
-- name
-- Berthold
----------------------------