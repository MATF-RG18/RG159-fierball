# RG159-headball
Headball

Headball je igrica radjena u C++ gde 2 igraca koji se naizgled nalaze u 3d prostoru, igraju 2d igru u kojoj imaju pomeranje levo, desno i skok i pokusavaju pobede.
Pobednik je onaj igrac koji prvi dodje do 3 gola, ili ima vise golova kad istekne vreme. Ako je nereseno kada istekne vreme, pobednik je onaj igrac koji prvi sledeci postigne gol.

Instrukcije za koriscenje:
	g - pocetak igre
	s - stopiranje igre
	ESC - izlazak iz igre
	
	Igrac 1:
		F1 - levo, F3 - desno, F2 - skok
	Igrac 2:
		levo <- - levo, desno -> - desno, gore - skok
	
	Za promenu tajmera i trajanja igre, adaptirati SecsDefault i MsecsDefault u Helpers.h
