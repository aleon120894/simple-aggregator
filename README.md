* `CMakeLists.txt`:  The CMake build file.
* `include/`:  Contains the header files (`.h`) for the project.
* `src/`:  Contains the source files (`.cpp`) for the project.

## Dependencies

* C++ compiler (e.g., GCC, Clang)
* CMake (build system)
* Standard C++ Library

## Building the Project

1.  **Clone the repository:**

    ```bash
    git clone <repository_url>
    cd simple_aggregator
    ```

2.  **Create a build directory:**

    ```bash
    mkdir build
    cd build
    ```

3.  **Configure the project with CMake:**

    ```bash
    cmake ..
    ```

4.  **Build the project:**

    ```bash
    make
    ```

    This will create an executable file named `simple_aggregator` in the `build` directory.

## Running the Application

1.  **Navigate to the `build` directory:**

    ```bash
    cd build
    ```

2.  **Run the executable:**

    ```bash
    ./simple_aggregator
    ```

    The application will display a menu with the following options:

    ```
    News Aggregator Menu
    1. Get All News
    2. Filter News by Keyword
    3. Exit
    Enter your choice:
    ```

3.  **Follow the menu instructions:**

    * **Option 1:** Fetches news from the defined sources and displays all the news items.
    * **Option 2:** Prompts for a keyword, filters the fetched news based on the keyword, and displays the filtered news items.  You must fetch the news first (option 1) before you can filter it.
    * **Option 3:** Exits the application.

## Code Overview

### Key Classes and Functions

* **`NewsItem` Class:**
    * Defined in `include/newsitem.h` and `src/newsitem.cpp`.
    * Represents a single news item with attributes like title, description, link, and publication date.

* **`fetchNews` Function:**
    * Defined in `include/newsfetcher.h` and `src/newsfetcher.cpp`.
    * Fetches news items from a given source (currently, the source is hardcoded for demonstration).
    * Returns a `std::vector<NewsItem>` containing the fetched news.

* **`filterNews` Function:**
    * Defined in `include/newsfilter.h` and `src/newsfilter.cpp`.
    * Filters a vector of `NewsItem` objects based on a given search term.
    * Performs a case-insensitive search in the title and description of the news items.
    * Returns a `std::vector<NewsItem>` containing the filtered news.

* **`displayNews` Function:**
    * Defined in `include/newsdisplay.h` and `src/newsdisplay.cpp`.
    * Displays the news items in a user-friendly format.

* **`utils::toLower` Function:**
    * Defined in `include/utils.h` and `src/utils.cpp`.
    * Converts a string to lowercase.  Used for case-insensitive filtering.

* **`main` Function:**
    * Located in `src/main.cpp`.
    * The entry point of the application.
    * Handles the main program logic, including:
        * Fetching news from sources
        * Displaying the menu
        * Getting user input
        * Calling the `filterNews` and `displayNews` functions

### Threading

The application uses `std::thread` to fetch news from multiple sources concurrently in the `getNewsFromSources` function. This (in theory) can improve performance by fetching news from different sources in parallel.  A mutex (`std::mutex`) is used to protect the shared `allNews` vector from race conditions when multiple threads are adding news items.  A condition variable (`std::condition_variable`) is used to signal when all threads have finished fetching news.

## Future Improvements

* **Implement actual news fetching:** Instead of the placeholder `fetchNews` function, implement actual web scraping or use a news API to fetch data from real news sources.
* **Add more news sources:** Extend the application to support more news sources.
* **Improve error handling:** Add more robust error handling, especially in the `fetchNews` function (e.g., handle network errors, invalid URLs, and malformed data).
* **Add more filtering options:** Implement more sophisticated filtering options (e.g., filter by date, source, category).
* **Implement a better user interface:** A command-line interface is functional, but a graphical user interface (GUI) or a web interface would provide a better user experience.
* **Implement pagination:** If the number of news items is very large, implement pagination to display the news in smaller chunks.
* **Add a configuration file:** Use a configuration file to store settings such as news sources, API keys, and display options.
* **Implement logging:** Add a logging mechanism to record events, errors, and debugging information.
* **Unit tests:** Write unit tests to ensure the correctness of the code, especially the `filterNews` and `fetchNews` functions.
* **Refactor NewsItem:** The NewsItem struct in newsfetcher.cpp is missing initializers for source, description, link, and pubDate.

## Conclusion

This simple news aggregator provides a basic framework for fetching, filtering, and displaying news.  It demonstrates several important C++ concepts and can be extended in many ways to create a more sophisticated and useful application.
