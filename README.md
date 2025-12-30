

# 📚 Book Recommendation System (C++)

A console-based **Book Recommendation System** developed in **C++** using **Object-Oriented Programming** and **STL containers**.
The system recommends books to users based on their **rating history and preferred genres**.

---

## 🚀 Features

* Add and manage users and books
* Store and process user ratings
* Automatically detect a user’s favorite genre
* Recommend unrated books from that genre
* Rank recommendations using average book ratings
* Simple menu-driven console interface

---

## 🛠️ Technologies & Concepts

* C++
* Object-Oriented Programming (Classes & Objects)
* STL (`unordered_map`, `vector`, `pair`)
* Sorting with `std::sort`

---

## ⚙️ Recommendation Logic

1. The system analyzes the user’s past ratings to determine their favorite genre.
2. Books from that genre which the user has not rated are selected.
3. These books are sorted based on their average ratings and displayed as recommendations.

---

## ▶️ How to Run

```bash
g++ main.cpp -o book_recommender
./book_recommender
```

---

## ✅ Purpose

This project demonstrates the practical use of **associative arrays, STL, and OOP** in building a simple recommendation system.


