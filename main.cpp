#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Book
{
public:
    int bookID;
    string title;
    string author;
    string genre;

    Book() {}
    Book(int id, string t, string a, string g)
        : bookID(id), title(t), author(a), genre(g) {}
};

class User
{
public:
    int userID;
    string name;

    User() {}
    User(int id, string n) : userID(id), name(n) {}
};

unordered_map<int, Book> bookTable;
unordered_map<int, User> userTable;
unordered_map<int, vector<pair<int, double>>> userRatings;
unordered_map<string, vector<int>> genreIndex;
unordered_map<int, vector<double>> bookRatings;

void addUser(int userID, string name)
{
    userTable[userID] = User(userID, name);
}

void addBook(int bookID, string title, string author, string genre)
{
    bookTable[bookID] = Book(bookID, title, author, genre);
    genreIndex[genre].push_back(bookID);
}

void addRating(int userID, int bookID, double rating)
{
    if (userTable.find(userID) == userTable.end())
    {
        cout << "User does not exist\n";
        return;
    }
    if (bookTable.find(bookID) == bookTable.end())
    {
        cout << "Book does not exist\n";
        return;
    }

    userRatings[userID].push_back({bookID, rating});
    bookRatings[bookID].push_back(rating);
}

string getFavoriteGenre(int userID)
{
    unordered_map<string, int> genreCount;

    for (auto &r : userRatings[userID])
    {
        int bookID = r.first;
        string genre = bookTable[bookID].genre;
        genreCount[genre]++;
    }

    string favGenre = "";
    int maxCount = 0;

    for (auto &g : genreCount)
    {
        if (g.second > maxCount)
        {
            maxCount = g.second;
            favGenre = g.first;
        }
    }
    return favGenre;
}

double getAverageRating(int bookID)
{
    double sum = 0;
    for (double r : bookRatings[bookID])
        sum += r;
    return sum / bookRatings[bookID].size();
}

vector<int> recommendBooks(int userID)
{
    vector<pair<int, double>> scoredBooks;
    string favGenre = getFavoriteGenre(userID);

    for (int bookID : genreIndex[favGenre])
    {
        bool alreadyRated = false;

        for (auto &r : userRatings[userID])
        {
            if (r.first == bookID)
            {
                alreadyRated = true;
                break;
            }
        }

        if (!alreadyRated)
        {
            double avg = getAverageRating(bookID);
            scoredBooks.push_back({bookID, avg});
        }
    }

    sort(scoredBooks.begin(), scoredBooks.end(),
         [](const pair<int, double> &a, const pair<int, double> &b)
         {
             return a.second > b.second;
         });

    vector<int> recommendations;
    for (auto &b : scoredBooks)
        recommendations.push_back(b.first);

    return recommendations;
}

void showRecommendations(int userID)
{
    auto recs = recommendBooks(userID);

    if (recs.empty())
    {
        cout << "No recommendations available yet.\n";
        return;
    }

    cout << "\nRecommended Books for " << userTable[userID].name << ":\n";
    for (int bookID : recs)
    {
        cout << "- " << bookTable[bookID].title
             << " (Avg Rating: " << getAverageRating(bookID) << ")\n";
    }
}

int main()
{
    // Preloaded Users
    addUser(1, "Fatima");
    addUser(2, "Ali");
    addUser(3, "Ayesha");
    addUser(4, "Ahmed");
    addUser(5, "Sara");
    addUser(6, "Umar");
    addUser(7, "Hira");
    addUser(8, "Zain");
    addUser(9, "Noor");
    addUser(10, "Hassan");

    // Preloaded Books
    addBook(101, "Atomic Habits", "James Clear", "Self-Help");
    addBook(102, "Harry Potter", "J.K. Rowling", "Fantasy");
    addBook(103, "Deep Work", "Cal Newport", "Self-Help");
    addBook(104, "The Hobbit", "J.R.R. Tolkien", "Fantasy");
    addBook(105, "Clean Code", "Robert C. Martin", "Programming");
    addBook(106, "Ikigai", "Hector Garcia", "Self-Help");
    addBook(107, "Think Like a Monk", "Jay Shetty", "Self-Help");
    addBook(108, "1984", "George Orwell", "Fiction");
    addBook(109, "The Alchemist", "Paulo Coelho", "Fiction");
    addBook(110, "Python Crash Course", "Eric Matthes", "Programming");
    addBook(111, "C++ Primer", "Lippman", "Programming");
    addBook(112, "The Power of Habit", "Charles Duhigg", "Self-Help");
    addBook(113, "Percy Jackson", "Rick Riordan", "Fantasy");
    addBook(114, "Rich Dad Poor Dad", "Robert Kiyosaki", "Self-Help");
    addBook(115, "Clean Architecture", "Robert C. Martin", "Programming");

    // Preloaded Ratings
    addRating(1, 101, 5.0);
    addRating(1, 103, 4.5);
    addRating(2, 102, 5.0);
    addRating(3, 104, 4.0);
    addRating(4, 108, 4.5);
    addRating(4, 109, 5.0);

    addRating(5, 106, 4.0);
    addRating(5, 112, 4.5);

    addRating(6, 110, 5.0);
    addRating(6, 111, 4.5);

    addRating(7, 113, 5.0);
    addRating(7, 102, 4.5);

    addRating(8, 114, 4.0);
    addRating(8, 101, 4.5);

    addRating(9, 115, 5.0);
    addRating(9, 105, 4.5);

    addRating(10, 107, 4.5);
    addRating(10, 112, 5.0);

    int choice;
    do
    {
        cout << "\n===== BOOK RECOMMENDATION SYSTEM =====\n";
        cout << "1. Show Recommendations\n";
        cout << "2. Add Rating\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            int uid;
            cout << "Enter User ID: ";
            cin >> uid;

            if (userTable.find(uid) == userTable.end())
            {
                cout << "Invalid User ID\n";
            }
            else
            {
                showRecommendations(uid);
            }
        }

        else if (choice == 2)
        {
            int uid, bid;
            double rating;

            cout << "Enter User ID: ";
            cin >> uid;
            cout << "Enter Book ID: ";
            cin >> bid;
            cout << "Enter Rating (0–5): ";
            cin >> rating;

            addRating(uid, bid, rating);
            cout << "Rating added successfully.\n";
        }

    } while (choice != 3);

    cout << "Exiting system...\n";
    return 0;
}
