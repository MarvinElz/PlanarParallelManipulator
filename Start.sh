#!bin/bash

echo "Starte Main"
lxterminal --title="Main" -e sudo ./main &

echo "Starte Motor A"
lxterminal --title="Motor A" -e sudo ./motor -A &

echo "Starte Encoder A"
lxterminal --title="Encoder A" -e sudo ./encoder -A &

#echo "Starte Motor B"
#lxterminal --title="Motor B" -e sudo ./motor -B &

#echo "Starte Encoder B"
#lxterminal  --title="Encoder B" -e sudo ./encoder -B &

echo "Starte GUI"
lxterminal --title="GUI" -e sudo ./qtCreator/Steuerung/build-Steuerung-Kit-Debug/Steuerung &