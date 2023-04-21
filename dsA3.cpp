/*
*  FILE							: dsA3.cpp
*  PROJECT					: SENG1050 - Mini1
*  PROGRAMMER		: Zijia (Alex) Cao
*  FIRST VERSION		: 2021-08-10
*  DECRIPTION				:
*  The funcition in this file is used to use multimap to record song information
*/

#include <stdio.h>
#include <iostream>
#include <string>
#include <map>
#include <corecrt_malloc.h>

using namespace std;

#define NUMBER_OF_SONGS 2
#define ASSUME_MAX_LENGTH 31

int getNum(void);

struct songInfo
{
	string artistInfo = { 0 };
	string titleInfo = { 0 };
	int rating = 0;
};

int main() {

	//creat two mulitimap
	typedef multimap<int, songInfo> song1;
	typedef multimap<string, songInfo> song2;
	song1 songsSortByRating;
	song2 songsSortByArtistInfo;

	bool isRatingUpdated = false;
	bool inputCheck = false;
	char* p = NULL;

	for (int i = 0; i < NUMBER_OF_SONGS; i++) {

		char artistInfo1[ASSUME_MAX_LENGTH] = { 0 };
		char titleInfo1[ASSUME_MAX_LENGTH] = { 0 };
		int rating = 0;

		printf("Please enter the artist of the song:");
		fgets(artistInfo1, ASSUME_MAX_LENGTH, stdin);
		//remove \n
		p = strchr(artistInfo1, '\n');
		if (p != NULL) {
			*p = '\0';
		}

		printf("Please enter the title of the song.");
		fgets(titleInfo1, ASSUME_MAX_LENGTH, stdin);
		//remove \n
		p = strchr(titleInfo1, '\n');
		if (p != NULL) {
			*p = '\0';
		}

		//save info as string
		string artistInfo = { 0 };
		string titleInfo = { 0 };
		artistInfo = artistInfo1;
		titleInfo = titleInfo1;

		printf("Please enter the rating of the song.");
		rating = getNum();


		for (int a = 0; a < artistInfo.length(); a++) {
			if (artistInfo[a] == '.') {
				printf("invalid artist!\n");
				inputCheck = false;
			}
		}

		for (int a = 0; a < titleInfo.length(); a++) {
			if (titleInfo[a] == '.') {
				printf("invalid title!\n");
				inputCheck = false;
			}
		}

		if (!(0 < rating && rating <= 5)) {
			printf("invalid rating!\n");
			inputCheck = false;
		}

		if (inputCheck == false) {
			i--;
		}

		songInfo s1 = { artistInfo ,titleInfo,rating };

		songsSortByArtistInfo.insert(pair<string, songInfo>(artistInfo, s1));
		songsSortByRating.insert(pair<int, songInfo>(rating, s1));

		inputCheck = true;

	}

	while (isRatingUpdated == false) {

		string artistInfo = { 0 };
		string titleInfo = { 0 };
		int rating = 0;

		int i = 1;
		printf("\nprintSongInfo\n");
		printf("------------------------------------------Sort by rating--------------------------------------\n");
		for (song1::const_iterator it = songsSortByRating.begin(), end = songsSortByRating.end(); it != end; ++it)
		{
			printf("The artist of No.%02d song is: %-35s. The Title is: %-35s. And rating is %i\n", i, it->second.artistInfo.c_str(), it->second.titleInfo.c_str(), it->second.rating);
			i++;
		}
		printf("------------------------------------------Sort by artist--------------------------------------\n");
		i = 1;
		for (song2::const_iterator it = songsSortByArtistInfo.begin(), end = songsSortByArtistInfo.end(); it != end; ++it)
		{
			printf("The artist of No.%02d song is: %-35s. The Title is: %-35s. And rating is %i\n", i, it->second.artistInfo.c_str(), it->second.titleInfo.c_str(), it->second.rating);
			i++;
		}

		while (inputCheck == true) {

			char artistInfo1[ASSUME_MAX_LENGTH] = { 0 };
			char titleInfo1[ASSUME_MAX_LENGTH] = { 0 };
			rating = 0;

			printf("\nPlease enter the artist of the song for search:  ");
			fgets(artistInfo1, ASSUME_MAX_LENGTH, stdin);
			p = strchr(artistInfo1, '\n');
			if (p != NULL) {
				*p = '\0';
			}

			printf("Please enter the title of the song for search:   ");
			fgets(titleInfo1, ASSUME_MAX_LENGTH, stdin);
			p = strchr(titleInfo1, '\n');
			if (p != NULL) {
				*p = '\0';
			}

			printf("Please enter the rating of the song for search:   ");
			rating = getNum();

			artistInfo = { 0 };
			titleInfo = { 0 };

			artistInfo = artistInfo1;
			titleInfo = titleInfo1;

			inputCheck = false;

			for (int a = 0; a < artistInfo.length(); a++) {
				if (artistInfo[a] == '.') {
					printf("invalid artist!\n");
					inputCheck = true;
				}
			}

			for (int a = 0; a < titleInfo.length(); a++) {
				if (titleInfo[a] == '.') {
					printf("invalid title!\n");
					inputCheck = true;
				}
			}

			if (!(0 < rating && rating <= 5)) {
				printf("invalid rating!\n");
				inputCheck = true;
			}
		}

		int newRating = 0;
		inputCheck = true;

		for (song2::const_iterator it = songsSortByArtistInfo.begin(), end = songsSortByArtistInfo.end(); it != end;)
		{
			if (it->second.artistInfo == artistInfo && it->second.titleInfo == titleInfo && it->second.rating == rating) {
				
				while (inputCheck== true) {

					printf("Please enter the NEW rating of the song.");
					newRating = getNum();

					if (!(0 < newRating && newRating <= 5)) {

						printf("invalid rating!\n");
						inputCheck = true;

					}
					else inputCheck = false;
				}

				if (newRating == it->second.rating) {
					//do nothing
				}
				else {

					songInfo s2 = { artistInfo ,titleInfo ,newRating };
					songsSortByArtistInfo.insert(pair<string, songInfo>(artistInfo, s2));

					songsSortByArtistInfo.erase(it++);
					isRatingUpdated = true;
				}
				break;
			}
			else ++it;
		}
		
	}

	int i = 1;
	printf("\nprintSongInfo\n");
	printf("------------------------------------------Sort by rating--------------------------------------\n");
	for (song1::const_iterator it = songsSortByRating.begin(), end = songsSortByRating.end(); it != end; ++it)
	{
		printf("The artist of No.%02d song is: %-35s. The Title is: %-35s. And rating is %i\n", i, it->second.artistInfo.c_str(), it->second.titleInfo.c_str(), it->second.rating);
		i++;
	}
	printf("------------------------------------------Sort by artist--------------------------------------\n");
	i = 1;
	for (song2::const_iterator it = songsSortByArtistInfo.begin(), end = songsSortByArtistInfo.end(); it != end; ++it)
	{
		printf("The artist of No.%02d song is: %-35s. The Title is: %-35s. And rating is %i\n", i, it->second.artistInfo.c_str(), it->second.titleInfo.c_str(), it->second.rating);
		i++;
	}

	return 0;
}

/*
*Function:		getNum()
*Description:	This function will get the user input
*Parameters:	void
*Returns:		int number: the number input by user
*/
#pragma warning(disable: 4996)
int getNum(void)
{
	/* the array is 121 bytes in size; we'll see in a later lecture how we can
	improve this code */
	char record[121] = { 0 }; /* record stores the string */
	int number = 0;
	/* NOTE to student: indent and brace this function consistent with your
   others */
   /* use fgets() to get a string from the keyboard */
	fgets(record, 121, stdin);
	/* extract the number from the string; sscanf() returns a number
	* corresponding with the number of items it found in the string */
	if (sscanf(record, "%d", &number) != 1)
	{
		/* if the user did not enter a number recognizable by
		* the system, set number to -1 */
		number = -1;
	}
	return number;
}