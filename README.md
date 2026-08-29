# Présentation du Projet : Alarme sans fil ESP32

Ce projet est une alarme sans fil maison, simple et efficace, qui utilise deux cartes ESP32 qui communiquent directement par ondes radio (avec le protocole ESP-NOW, donc sans avoir besoin de routeur ou de Wi-Fi). Pour faire propre, tous les boîtiers sont imprimés en 3D.

## Le capteur (l'émetteur)

Du côté de la porte ou de l'ouvrant à surveiller, on a branché un capteur **IGT 202** (sur la broche 4). Il s'agit d'un matériel professionnel de haute qualité, initialement conçu pour des environnements industriels exigeants afin d'assurer une détection ultra-fiable. Le gros avantage, c'est que le système est modulable : on pourra rajouter facilement d'autres capteurs IGT par la suite. Dès que la porte s'ouvre, l'émetteur prévient instantanément le récepteur.

## La centrale (le récepteur)

C'est le boîtier principal qui gère les alertes. Il est équipé de :

* Un écran OLED (sur les broches 21 et 22) pour afficher l'état du système.
* Un **joystick** (sur la broche 27) à la place d'un simple bouton, ce qui permet de descendre dans le menu facilement si on rajoute des capteurs pour naviguer entre chaque capteur.
* Un buzzer (sur la broche 23) pour faire du bruit en cas d'alerte.

Quand l'alarme sonne, il suffit d'utiliser le joystick pour couper le son, armer ou désarmer le système, ou même passer en mode veille prolongée (Deep Sleep) en maintenant le joystick poussé pendant 5 secondes.

## L'alimentation

Pour alimenter le récepteur de façon autonome, on utilise une cellule Li-ion de qualité supérieure, récupérée sur une batterie 3S issue d'un ordinateur portable Dell haut de gamme. Cette cellule est associée à un petit module de charge de type TP4056 pour assurer sa recharge en toute sécurité et protéger efficacement la batterie.
<video src="videoalarme.mp4" controls width="100%"></video>
https://github.com/user-attachments/assets/6d409567-70d1-4393-a8a0-c140a70f6708
