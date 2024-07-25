2.13inch E-Paper Display V2 from seengreat:www.seengreat.com
 =======================================
# Instructions
## Product Overview
This product is a 2.13-inch ink screen expansion module, based on the Raspberry Pi 40PIN interface design and suitable for Raspberry Pi series motherboards. We provide C and Python version demo codes for Raspberry Pi, and reserve the SPI control interface for easy access to Arduino, STM32 and other main control boards. We also provide Arduino, STM32, ESP32 version demo codes, which can realize picture display, English and digital character display, and point, line, rectangle, circle drawing.<br>
## Product parameters
|Size	|65mm(Length)*30mm(width)|
|-----------|-------------------------------|
|Pixels|	250 x 122|
|Display Color|	monochrome|
|Voltage Translator|	TXS0108EPWR|
|Signal interface|	SPI|
|Supply voltage|	3.3V/5V|
|LCD display area|	23.7046mm (W)* 48.55mm (H)|
|Partial Refresh|	0.3S  (4-wire SPI status)|
|Global Refresh|	2S (4-wire SPI status)|
## Product dimensions
65mm(Length)*30mm(width)<br>
# Usage
All the demo codes provided by this product are based on the 4-wire SPI mode, so the BS selection switch on the back of the board is set to "0" by default. <br>
## Raspberry Pi demo codes usage
Since the bookworm system no longer supports the wiringpi library, the example program for this system uses the lgpio library, and for the bullseye system, the wiringpi library version of the example program can be used.<br>
### Raspberry Pi Platform Interface Definition
The example program in the Raspberry Pi motherboard uses the wiringPi pin definitions. The definition of the connection with the Raspberry Pi motherboard is shown in the following table：<br>
|E-Ink display 	|Pin function	|BCM	|WiringPi|
|----------------------|----------------------|-----------|----------|
|VCC|	5V|	3.3V|	3.3V|
|GND|	GND|	GND|	GND|
|BUSY|	P5|	24|	5|
|RSTN|	P0|	17|	0|
|D/C |	P6|	25|	6|
|SDA|	P_MOSI|	10|	12|
|SCL|	P_SCK|	11|	14|
|CSB|	P_CE0|	8|	10|
### Demo Codes Usage	
#### Wiringpi library installation
sudo apt-get install wiringpi<br>
   wget https://project-downloads.drogon.net/wiringpi-latest.deb  # Version 4B upgrade of Raspberry Pi<br>
   sudo dpkg -i wiringpi-latest.deb<br>
   gpio -v # If version 2.52 appears, the installation is successful<br>
#For the Bullseye branch system, use the following command:<br>
git clone https://github.com/WiringPi/WiringPi<br>
cd WiringPi<br>
./build<br>
gpio -v<br>
#Running gpio - v will result in version 2.70. If it does not appear, it indicates an installation error<br>
If the error prompt "ImportError: No module named 'wiringpi'" appears when running the python version of the sample program, run the following command<br>
#For Python 2. x version<br>
pip install wiringpi<br>
 
#For Python version 3. X<br>
pip3 install wiringpi<br>
Note: If the installation fails, you can try the following compilation and installation:<br>
git clone --recursive https://github.com/WiringPi/WiringPi-Python.git<br>
Note: The -- recursive option can automatically pull the submodule, otherwise you need to download it manually.<br>
Enter the WiringPi Python folder you just downloaded, enter the following command, compile and install:<br>
#For Python 2. x version<br>
sudo python setup.py install <br>
#For Python version 3. X<br>
sudo python3 setup.py install<br>
If the following error occurs:<br>
"Error:Building this module requires either that swig is installed<br>
        (e.g.,'sudo apt install swig') or that wiringpi_wrap.c from the<br>
        source distribution (on pypi) is available."<br>
At this time, enter the command sudo apt install swig to install swig. After that, compile and install sudo python3 setup.py install. If a message similar to the following appears, the installation is successful.<br>
"ges<br>
Adding wiringpi 2.60.0 to easy-install.pth file<br>
Installed /usr/local/lib/python3.7/dist-packages/wiringpi-2.60.0-py3.7-linux-armv7<br>
Processing dependencies for wiringpi==2.60.0<br>
Finished processing dependencies for wiringpi==2.60.0"<br>
#### lgpio library installation
wget https://github.com/joan2937/lg/archive/master.zip<br>
unzip master.zip<br>
cd lg-master<br>
make<br>
sudo make install<br>
#### Open SPI interface
sudo raspi-config<br>
Enable SPI interface:<br>
Interfacing Options > SPI > Yes<br>
To view enabled SPI devices:<br>
ls /dev/spi * # The following will be printed: "/dev/spidev0.0" and "/dev/spidev0.1"<br>
#### Installation of python library
The demo codes uses the python 3 environment. To run the python demo codes, you need to install the pil, numpy, and spiderv libraries. Enter the following commands in order to install:<br>
sudo apt-get install python3-pil<br>
sudo apt-get install python3-numpy<br>
sudo apt-get install python3-pip<br>
sudo pip3 install spidev<br>
#### C version demo codes
Enter2.13inch E-Paper Display\demo codes\raspberry_pi\c directory<br>
sudo make clean<br>
sudo make<br>
sudo ./main<br>
After entering the above command, you can observe the E-Ink display.<br>
#### python Version demo codes
Enter 2.13inch E-Paper Display\demo codes\raspberry_pi\python directory<br>
python3 gui_demo.py<br>
After entering the above command, you can observe the E-Ink display.<br>
## Arduino Demo Codes Usage
### Hardware interface configuration description
the wiring definition between Arduino Mega and ink screen:<br>
|E-Ink display	|Arduino Mega|
|----------------------|--------|
|VCC|	5V|
|GND|	GND|
|CS|	D53|
|CLK|	D52|
|MOSI|	D51|
|DC|	D8|
|RST|	D9|
|BUSY|	D10|

the wiring definition between Arduino UNO and ink screen:<br>
|E-Ink display	|Arduino UNO|
|----------------------|--------|
|VCC	|5V|
|GND	|GND|
|CS	|D11|
|CLK	|D12|
|MOSI	|D13|
|DC	|D10|
|RST	|D9|
|BUSY	|D8|
### Demo Codes Usage
Open the \demo codes\Arduino_MEGA_2.13_V2\Arduino_MEGA_2.13_V2.ino or \demo codes\Arduino_UNO_2.13_V2\Arduino_UNO_2.13_V2.ino with Arduino IDE Click Verify to verify the project file, and then transfer it to the module to observe the E-Ink display.<br>
## STM32 Demo Codes Usage
### Hardware interface configuration description
|E-Ink display|	STM32|
|----------------------|-------|
|VCC|	3.3V|
|GND|	GND|
|CS|	PB12|
|CLK|	PB13|
|MOSI|	PB15|
|DC|	PA8|
|RST|	PA11|
|BUSY|	PA12|
### Demo Codes Usage
Open the demo codes in directory 2.13inch E-Paper Display\demo codes\STM32 with Keil uVision5 software, compile it correctly, download it to the module, and observe the E-Ink display.<br>

##  ESP32 Demo Codes Usage
The ESP32 module used in this example program is ESP32-WROOM-32E.<br>

### Hardware interface configuration description:<br>
|E-Ink display	|ESP32|
|----------------------|-------|
|VCC	|3.3V|
|GND	|GND|
|CS	|IO27|
|CLK	|IO18|
|MOSI	|IO23|
|DC	|IO14|
|RST	|IO33|
|BUSY	|IO13|
### Demo Codes Usage
Open the demo codes in directory \demo codes\Arduino_ESP32_2.13_V2\ with Arduino IDE Click Verify to verify the project file, and then transfer it to the module to observe the E-Ink display.<br>
