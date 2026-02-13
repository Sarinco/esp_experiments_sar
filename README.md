## ESP32 Experiment


Don't forget to install & activate esp-idf & export to path
```
alias get_esp32='export PATH="$PATH:$HOME/esp/xtensa-esp32-elf/bin"'
alias get_idf='. $HOME/esp/esp-idf/export.sh'
```

command to activate it once it's done :
```
get_esp32
get_idf
```

unlocking usb ports for arch : 

```
sudo usermod -a -G uucp $USER
```

configuring esp idf and commands that go with it : 
```
https://espressif-docs.readthedocs-hosted.com/projects/esp-idf/en/stable/get-started/index.html#get-started-connect
```



### commands to run and build project

```
idf.py build
idf.py -p $(USB_PORT) flash monitor 
```

ctrl+] to close the monitoring
