#HOW TO START
  
### KUDOS TO TEXANE, THANKS!!!  
git clone https://github.com/texane/stlink stlink.git
cd stlink
make
sudo cp build/Release/st-* /usr/local/bin
#install udev rules
sudo cp etc/udev/rules.d/49-stlinkv* /etc/udev/rules.d/
sudo restart udev