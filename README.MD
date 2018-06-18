# SimpleCurl Adaptation of Wikipedia Golf
## By Thomas Reichman
### November 5, 2015

As defined by Wikipedia, *Wikipedia Golf* is a game where the premise is as follows:
>Players (one or more) start on the same randomly selected article and must navigate to another pre-selected article (home) only clicking links within the current article. The goal is to arrive at the home article in the fewest number of clicks (articles) or the least time. 
			[Wikipedia - Wiki Game] (https://en.wikipedia.org/wiki/Wikipedia:Wiki_Game)

The game is compatible with any website, even outside of wikipedia.org. The search algorithm [Breadth-First Search](https://en.wikipedia.org/wiki/Breadth-first_search). The number of levels to search through is customizable, as well as the keyword to search for.

To run this game, you must compile the game from source by using 'make'. The game may require this command to be added to your path. This creates the executable file 'GetURL'. Then, from any CLI, execute GetURL with the following arguments, each separated by a space:

1. The URL to start the game at.
2. The levels of depth to search through (for each linked article). It is reccommended to use 2 or less, as the running time increases exponentially based on this value.
3. The keyword(s) to search through. If you want to search for more than one word, place your keywords inside of quotation marks. (You may do this even if you are searching for only one keyword as well, but it is not neccessary)

Example usage:

`GetURL https://en.wikipedia.org/Main_Page 2 "Kansas"`

`GetURL https://en.wikipedia.org/wiki/Luser 2 "leet"`

This searches the article for the Main Page of Wikipedia for the keyword Kansas. It also searches contained URLs linked in the source code of the page using Breadth-First Search with a depth of 2.

In the second example, "leet" is found in the article "Internet Slang", which is linked to by the starting "Luser" article, even though "leet" isn't mentioned in the "Luser" article.

~~Please see an old commit from Thursday afternoon for a better version of the program.~~

In class, we discussed how one of the last commits I made last night accidentally screwed things up because of a simple bug/feature in Sublime that caused an increment variable to be moved (ctrl+shift+up/down arrows). Unfortunately, it seems like the bug occurred before then. As a result, I still think a commit from Thursday afternoon around the time we were in your office (close to 2PM) had more filling functionality for B level, particularly with the printing of the path (that "while" loop you wrote out on paper). However, the current version I am commiting now has some proper parts of A level (taking in everything from the CLI). I hate to make you grade two different versions, but I'm not sure which one is closer to being perfect, as I haven't had much time to review the code since last night. In the mean time, I have committed some extra comments to help make the code a bit more readable. 

If you want to discuss the differences sometime (perhaps Monday?), that's fine as well - I don't want to make you grade two different projects and then try to decide which one works better.

Sorry for the trouble.