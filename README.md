 write a pthreads program that will simulate 5 epochs in an online game world. The world consists of four continents (numbered 0 - 3). There are three types of players. The first two are user generated players - type A and type H. The second type of player is a machine generated dragon. The following rules apply:

1. When players log on they are not given a choice which continent they will play in. Main should create four threads (one per continent). Main handles reading in player data and storing it in a global queue. The continents get players from the queue as needed, but at the beginning of the game main will choose 5 consecutive players with the first 5 going to continent 0, the second 5 to continent 1, etc.

2. There can be no more than 5 players per continent...well, 5 players and a dragon. 

3. At the end of an epoch, the first two living players on each continent will be magically transported to the next continent. This is a circular shift, so players on continent 3 will go to continent 0. (I recommend keeping a queue of players for each continent)

4. New players can be allowed into the game only at the end of an epoch. So at the end of an epoch after the removal of dead bodies and transportation of other players, if a continent doesn't have 5 players, then it will get the next however many needed players from the global queue.

5. A player will fight players of a different type. The rules of engagement are as follows:
a. Players always fight in groups
b. Players are involved in at most one fight each epoch
c. Players can be killed by opposing players. It requires two team members to kill one opponent. Examples:
Num A's before     Num H's before      Num A's after     Num H's after
5	            0                	5                	0
4	            1                	4	                0
3	            2                	3	                1
2	            3	                1	                3
1	            4	                0	                4
0	            5	                0	                5

6. There is always a dragon roaming around the world somewhere. Dragons roam counter to players...i.e., a dragon will move from 3 to 2 to 1 to 0 to 3.

7. Players cannot kill the dragon. 

8. Dragons eat players...their preference is the type A players, but given no other choice, they will eat type H players. While a dragon can go a LONG time without eating...certainly longer than 5 epochs...they prefer to eat one player per epoch. However, they like to have dinner and a show, and since players tend to run away when they see a dragon, the dragon will always wait until the fighting is done before picking out his dinner.

9. Players are killed either by opponents or by the dragon in a first in first out manner.

10. At the end of each epoch, main should print out what the world looks like. i.e., which players are on which continent and who is in the queue waiting.

11. When players die, they must go to the end of the global play queue. It is the responsibility of the continent to update the play queue at the end of an epoch.

12. There is a global world that contains four lists, one for each continent. A list must be long enough to contain players and a possible dragon. At the end of an epoch, each continent must update its list and the global queue before updating the lists of the neighboring continent can begin. After which time extra players can be taken from the global queue. And all this needs to be done before main can print stuff out. Adding players to a continent, whether by transportation or retrieval from the global queue, requires players to be added to the end of the continent's list.

13. Player data will be stored in a file called "players.dat" and will be a string of A's and H's followed by a D and a number between 0 and 3. For instance
AHHHAAHAAAAAHD2
would mean players 1,5,6,8,9,10,11, and 12 were A's
players 2,3,4,7, and 13 were H's
and the Dragon starts on continent 2

Of course this would mean that there were 5 players on continent 0, 5 players on continent 1, and 3 players and a dragon on continent 2...which won't happen because there will be at least 20 players in the file.

There will be no more than 30 players besides the dragon in players.dat, so a global queue of length 30 should work. :-)
14. Players have a number and a type associated with them, so when main prints out the world, the number and type should be listed for each player in each location. In the example in #13, player number 1 is type A and number 2 is type H, etc.


I highly recommend doing one small piece at a time. In fact, I so highly recommend it that I will give points as follows:
1. main reads in the player data, sets up the world, prints the initial world, creates the threads, joins the threads, and prints out the world. 5 points
2. main reads in the player data, sets up the world, prints the initial world, creates the threads, the threads fight one round, let the dragon eat, and remove dead bodies from their queue, main joins the threads and prints out the world. 5 points
3. #2 with the addition of the threads put dead bodies back into the global queue. 6 points
4. #3 with the addition of the threads transport players. 7 points
5. #4 with the addition of the threads transport the dragon. 8 points
6. #5 with the addition of the threads get extra players if needed. 8 points
7. #6 with the addition of the threads do 2 epochs with main printing after each epoch. 8 points
8. The full blown program. 3 points
By the way, you only need one thread function.


AHAHAHAAHHAAAAHHAAHAHHHHHHHHAAD2
Sample runs with the above input data for a program satisfying each of the above point steps can be found at:
step 1 only
through step 2 
through step 3 
through step 4 
through step 5 
through step 6 
through step 7 
through step 8 

Side note: My program was exactly 300 lines of code a whole lot of which were {'s and }'s, and it took me nearly 3 hours to write it - although I was purposefully going slowly and carefully. Since I knew what I was doing and could easily debug mistakes, and since I usually only take about 15 to 30 minutes to do a program I assign, you might want to get started if you haven't already. :-) 
One possible sample run of one epoch with the following input file:
AHAHAHAAHHAAAAHHAAHAHHHHHHHHAAD2
is shown below. Sample runs for the above input file are shown for 
Initial Setup:
Player		Type		Continent
1		A		0
2		H		0
3		A		0
4		H		0
5		A		0
6		H		1
7		A		1
8		A		1
9		H		1
10		H		1
11		A		2
12		A		2
13		A		2
14		A		2
15		H		2
Dragon				2
16		H		3
17		A		3
18		A		3
19		H		3
20		A		3
21		H		queue
22		H		queue
23		H		queue
24		H		queue
25		H		queue
26		H		queue
27		H		queue
28		H		queue
29		A		queue
30		A		queue

The World After One Epoch:
Player		Type		Continent
4		H		0
5		A		0
17		A		0
18		A		0
22		H		0
9		H		1
10		H		1
1		A		1
3		A		1
25		H		1
Dragon				1
14		A		2
6		H		2
8		A		2
23		H		2
24		H		2
19		H		3
20		A		3
12		A		3
13		A		3
21		H		3
26		H		queue
27		H		queue
28		H		queue
29		A		queue
30		A		queue
2		H		queue
7		A		queue
15		H		queue
11		A		queue
16		H		queue
