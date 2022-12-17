# Structuur beschrijving

1. Arduino_Swift : bevat de software voor ATTiny84 en ATTiny85/45
2. dplayer_swift_v3.1 : Bevat de kicad 6.0 schema en PCB ontwerp files
3. KiCad_Arduino_Nano_DFPlayer_footprints-master : Bevat het ontwerp voor de DFPlayer kicad footprint.

# Bron verwijzingen:

## Arduino libraries voor dfplayer 
### DFPlayer - A Mini MP3 Player For Arduino

> DFPlayer - A Mini MP3 Player For Arduino
> https://www.dfrobot.com/index.php?route=product/product&product_id=1121
>
> This example shows the all the function of library for DFPlayer.
>
> Created 2016-12-07
> By [Angelo qiao](Angelo.qiao@dfrobot.com)
> 
> GNU Lesser General Public License.
> See <http://www.gnu.org/licenses/> for details.
> All above must be included in any redistribution
> 
> Notice and Trouble shooting
> 
> 1.Connection and Diagram can be found here
> https://www.dfrobot.com/wiki/index.php/DFPlayer_Mini_SKU:DFR0299#Connection_Diagram
> 2.This code is tested on Arduino Uno, Leonardo, Mega boards.

## Kicad footprint design. (deze heb je nodig voor de kicad PCB, dus eerst deze footprint opladen in de kicad footprint library)
### KiCad_Arduino_Nano_DFPlayer_footprints
> Footprints for Arduino Nano and DFPlayer MP3 player because I had to make them. 
>
> (I actually use a 32 pin socket to hold the nano to the board. eBay: 32 pin dip IC socket. 2x16.)
>
> There are already components out there for both, but I couldnt find a footprint.
>
> How
> * Add to your library directory.
> * Example: C:\Program Files\KiCad\share\kicad\library
> * Add library to Cvpcb app. Preferences->footprint libraries-> append with wizard
