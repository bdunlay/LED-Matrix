Copyright © 2012 Brian Dunlay

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


This code represents the driver for a hardware LED display.

The display I intend to drive initially is an 8x8 LED Matrix. All anodes are connected in parallel to their corresponding row and all cathodes are connected in parallel to their corresponding column. Each of the 8 rows and each of the 8 columns is connected to a shift register pin (2 8-bit SRs),  and those SRs are controlled by an AVR2313A microcontroller.

This multiplexing allows me to control individually the LEDs of any given row simply by putting bits into the column SR and selecting one row to illuminate in the row SR. If we iterate over all rows and manipulate the data in the column SR, the display will update quick enough to give the illusion of a solid image of up to 64 LEDs being displayed. 

The refresh rate is controlled by an interrupt timer which triggers every 1ms. I intend to map some known characters and images in the ROM of the AVR to an 8 bit char, allowing me to display a 64-bit image with only a single char. 

I also intend to extend this driver to be remotely manipulated via UART. This will allow it to be integrated into future projects without the need to update the firmware of the AVR driving this display. 

Contact me on Twitter: @_i3d