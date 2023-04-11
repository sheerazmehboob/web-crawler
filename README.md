<h1 align="center">Multi-Threaded Web-Crawler</h1>

<h2>Introduction</h2>
<hr />
<p>This is a web crawler program implemented in C++ that can extract links from a webpage and crawl those links to a specified depth. The program uses multithreading and semaphores to speed up the crawling process.</p>

<h2>Features</h2>
<hr />
<ul>
    <li>Multithreading and semaphores for faster crawling.</li>
    <li>Extracts links from a webpage and crawls them recursively.</li>
    <li>Stops crawling at a specified depth.</li>
    <li>Writes extracted links to a file.</li>
    <li>Uses regular expressions to extract links from HTML code.</li>
</ul>

<h2>Pre-Requisites</h2>
<hr />
<ul>
    <li>C++ compiler</li>
    <li>The "libcurl" library</li>
    <li>The "regex" library</li>
</ul>

<h2>How To Run?</h2>
<hr />
<ol>
    <li>Clone the repository to your local machine.</li>
    <li>Install the necessary libraries.</li>
    <li>Compile the code using the C++ compiler.</li>
    <li>Run the executable file.</li>
</ol>

<h2>Code Structure</h2>
<hr />
<p>The code is structured into several functions, each handling a specific task. Here is a brief explanation of each function:</p>
<ol>
    <li>Download_Page(): Function to download a web page and save it in a file.</li>
    <li>Extract_Links_From_File(): Function to extract links from a file containing HTML source code.</li>
    <li>Contains(): Function to check if an element is present in a list.</li>
    <li>Crawl(): Recursive function to crawl a web page and its links up to a certain depth.</li>
    <li>main(): Initializes semaphore and Creates threads to crawl different web pages.</li>
</ol>

<h2>Snapshots</h2>
<hr />

![webCrawler-1](https://user-images.githubusercontent.com/96474143/231255434-15223110-c5ba-4dfe-86ab-d5a31f6ddd7b.png)

![webCrawler-2](https://user-images.githubusercontent.com/96474143/231255465-0488f3e2-81aa-4f21-a730-ba0ffe0e53b6.png)
