The example in this file can be executed through a command prompt by running:

    make && make program

Edit the Makefile with both the PORT and name of the file you're making. The lowest-numbered port that fits /dev/tty.usbmodem* is the programmer port. The other one[s] are for serial connection.

Make sure your Pololu AVR CC++ Library is installed by following the instructions [here](http://www.pololu.com/docs/0J51/5.3).



TODO: This should also work straight from the Arduino IDE using AVRISPv2 (maybe even AVRISP mk II), without needing to touch a Makefile.
