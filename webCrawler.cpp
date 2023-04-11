// Adding Necessary Libraries
#include <bits/stdc++.h>
#include <curl/curl.h>
#include <stdio.h>
#include <regex>
#include <thread>
#include <semaphore.h>
#include <chrono>
using namespace std;


// Initializing semaphore for synchronization between threads
sem_t s;	

// Maintain a list of visited URLs to avoid revisiting them
list<string> Visited;	

// Function to download a page given its URL and save it to a file
void Download_Page(const char *Page_URL, const char *FileName)
{
  // Initialize a CURL easy handle
	CURL *easyhandle = curl_easy_init();	
  
  // Set the URL to be downloaded using the easy handle
	curl_easy_setopt(easyhandle, CURLOPT_URL, Page_URL);	
  // Open a file to write the downloaded data to
	FILE *file = fopen("Links.txt", "w");	

  // Set the file handle to write the downloaded data to file
	curl_easy_setopt(easyhandle, CURLOPT_WRITEDATA, file);	
  // Perform the download using the easy handle
	curl_easy_perform(easyhandle);	

  // Clean up the easy handle and close the file handle
	curl_easy_cleanup(easyhandle);	
  // Close the file
	fclose(file);	
}

// Function to extract links from a file containing HTML code
list<string> Extract_Links_From_File(string FileName)
{
	string Link;

	// Read the contents of the file into a string
	ifstream ReadLink;
	ReadLink.open(FileName);
	while (!ReadLink.eof())
	{
		if (ReadLink.eof()) break;
		char ch;
		ReadLink.get(ch);
		Link.push_back(ch);
	}

	ReadLink.close();

	// Define a regular expression to match links in the HTML code
	static
	const regex hl_regex("<a href=\"(.*?)\">", regex_constants::icase);

	list<string> Links;
	// Use the regular expression to extract links from the HTML code and store them in a list
	copy(sregex_token_iterator(Link.begin(), Link.end(), hl_regex, 1), sregex_token_iterator(), back_inserter(Links));

	// Clean up the extracted links by removing any unnecessary characters
	list<string> CleanLinks;
	for (list<string>::iterator i = Links.begin(); i != Links.end(); ++i)
	{
		string Junk_Link = *i;
		string Temp = "";
		for (int j = 0; j < Junk_Link.length(); j++)
		{
			if (Junk_Link[j] == ' ' || Junk_Link[j] == 34) break;
			Temp.push_back(Junk_Link[j]);
		}

		// Check if the cleaned up link is a valid URL and add it to the list of cleaned up links
		if (regex_match(Temp, regex("((http|https)://)(www.)?[a-zA-Z0-9@:%._\\+~#?&//=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%._\\+~#?&//=]*)")))
		{
			CleanLinks.push_back(Temp);
		}
	}

	// Clear the original list of links and return the cleaned up list
	Links.clear();
	return CleanLinks;
}

// Function to check if a URL is already present in the list of visited URLs
bool Contains(const list<string> &List, string x)
{
	if (find(List.begin(), List.end(), x) != List.end())
		return 1;
	else
		return 0;
}

void Crawl(const char *url, const char *FileName, int depth, int ID)
{
	// If the depth is less than or equal to zero, return
	if (depth <= 0)
		return;

	// If the URL has already been visited, return
	if (Contains(Visited, url) == 1)
		return;
	else
	{
		string str = url;
		Visited.push_back(str);
	}

	// Wait for semaphore to be available before page download
	sem_wait(&s);
	cout << "\t\tThread ID : " << ID << endl;
	cout << "Extracted Link : " << url << endl;

	// Download the page and extract links from it
	Download_Page(url, "Links.txt");
	list<string> Links = Extract_Links_From_File("Links.txt");

	// Release semaphore after page downloading is done
	sem_post(&s);
	// Crawl all the extracted links recursively
	for (string i: Links)
	{
		this_thread::sleep_for(chrono::milliseconds(10));
		const char *CurrentlyCrwal = i.c_str();
		if (Contains(Visited, CurrentlyCrwal) == 0)
		{
			Crawl(CurrentlyCrwal, FileName, depth - 1, ID);
		}
	}
}

int main()
{
  // Initialize the semaphore
	sem_init(&s, 0, 1);

  // Turn off synchronization with stdio for faster I/O
	ios_base::sync_with_stdio(NULL);
	cin.tie(NULL);	

	// Create three threads to crawl three different URLs
	thread t1(Crawl, "https://www.geeksforgeeks.org/mutex-vs-semaphore/", "Links.txt", 3, 1);
	thread t2(Crawl, "https://stackoverflow.com/questions/5620235/cpp-regular-expression-to-validate-url", "Links.txt", 3, 2);
	thread t3(Crawl, "https://stackoverflow.com/questions/7432100/how-to-get-integer-thread-id-in-c11", "Links.txt", 3, 3);

	// Wait for all threads to finish
	t1.join();
	t2.join();
	t3.join();
}
