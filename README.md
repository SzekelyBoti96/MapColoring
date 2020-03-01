Térképszinezés: adott n ország a térképen, adott számú színnel, hogyan lehet kiszínezni úgy a térképet, hogy a szomszédos országok ne legyenek egyforma színűek.

Amit megvalósitottam az a nyers Backtrack-módszere.
A program az egy állómányból olvassa ki az adatokat, ezek az országok száma, a kapcsolatok számát és az országok szomszédjait.

A bemenetben az első paraméter a csúcsok száma, azaz az országok száma, a második pedig maga az élek száma, azaz a szomszédsági viszonya az országoknak. Ezek után következnek az országok közti kapcsolatok. 
Pl. hogyha x ország szomszédos y országgak akkor a szomszédsági viszonyuk a bemeneti állómányba úgy lesz beolvasva hogy: x y
x szimbólizálja az első országot és y a második országot, közöttük pedig egy SPACE fehér karakter hogy látható legyen a programnak a két ország közti kapcsolatot.


