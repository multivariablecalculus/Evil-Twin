# Evil-Twin
Yes, Evil Twin attacks are not all that common and require a bit of expertise in the field of IoT, but anyone can do just fine with them. Since I am a low-life creature, I learnt Evil-Twin from YT and a bit of networking theory from a book. Now, Evil-Twin is a type of 2-step deauth attack which disconnects a client from a server and creates another "fake" server or "evil-twin" server which acts as the control panel of the attacker, and the bait for the victim. Just when the victim tries to connect to the fake server, he will enter the credentials, which will be redirected to the attacker, and the victim will be deauthenticated, i.e. they will be logged off, and won't be able to connect to any network for a while. Concluding; the attacker has the SSID, passkey and IPv4, IPv6, DNS and might have MAC and the victim is done for, even though they will be able to connect to the network after a while.

Some cool guys/girls might call it a DoS attack, but I prefer not to call it that since it is done on a private server or a private network rather than a public server.

It requires an ESP8266 NodeMCU module or an ESP32 NodeMCU module. I used the ESP8266 module for all the programs, so if you use my code, you also need an ESP8266 module; naturally, you require either the Arduino IDE for the code editing, or you can use https://app.arduino.cc as per your needs.

Cheers, fellow wcoders!
