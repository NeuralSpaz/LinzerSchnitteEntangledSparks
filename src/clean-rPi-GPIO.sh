
cd RaspberryPi-GPIO/src
make clean
cd ../..
pwd
#gcc -Wall  midi2rds.c i2c_bitbang.c -o midi2rds -Igpio/include -Lgpio/library -lrpigpio -lasound
