# Wikipedia Race Solver

This app is meant to find the shortest sequence of links between any 2 Wikipedia articles to beat the 'Wiki Race' game.
<br> Details for the game are [here](https://en.wikipedia.org/wiki/Wikipedia:Wikirace).

The code is contained in the `src` folder. An example of how to use the Wikipedia class is in the `main.cpp` file. The tests can be found in the `tests` folder. The Wikipedia dataset is in the `data` folder and the documents, including the written report are in the `documents` folder.

To run our code, run make `make exec` and then `./bin/exec`. An example of how to pass input data to the Wikipedia class and use its output data is found in `main.cpp`. To run the test suite, run `make tests` and `./bin/tests`. We wrote tests for every major method of class, running them both on a subset of the actual Wikipedia dataset as well as our own small Adjacency List as a sanity check.

Our presentation can be found [here](https://drive.google.com/file/d/1n8D5IMmt-jI0TvTj4KiHzZH-NBaPOnG_/view?usp=sharing)
