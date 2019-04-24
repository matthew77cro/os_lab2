# os_lab2


<!-- saved from url=(0086)http://zemris.fer.hr/predmeti/os/pripreme/z4_simulacija_dinamicko_rasporedjivanje.html -->
<html><head><meta http-equiv="Content-Type" content="text/html; charset=windows-1250">

<title>Simulacija dinamičkog raspoređivanja spremnika</title>

</head><body style=""><h1>Simulacija dinamičkog raspoređivanja spremnika</h1>


<div class="MsoNormal" align="center" style="text-align:center">

<hr size="1" width="100%" align="center">

</div>


<h2>ZADATAK</h2>

<p>Simulirati postupak dinamičkog raspoređivanja spremnika. Ispisati kada se 
zahtjev ne može poslužiti. Omogućiti "prikupljanje otpada", tj. zaustavljanje 
programa i preslagivanje spremnika.</p>
<p>Primjerice, programu se prilikom pokretanja zadaje veličina spremnika, a on 
na svojem početku ispiše sadržaj (praznog) spremnika (<b>nije nužno da ispis 
izgleda ovako</b>):</p>
<pre>&gt; ./simulacija 50
12345678901234567890123456789012345678901234567890
--------------------------------------------------</pre>
<p>Nakon toga program čeka da se pritisne tipka Z pa potom generira zahtjev za 
spremnikom s identifikacijskim brojem 0 (brojevi zahtjeva se dodjeljuju redom) i 
slučajne veličine (primjerice 4). Ispis primjerice može izgledati ovako:</p>
<pre>Novi zahtjev 0 za 4 spremnička mjesta

12345678901234567890123456789012345678901234567890
0000----------------------------------------------</pre>
<p>Nakon pritiska tipke Z još jednom generira se primjerice novi zahtjev za 5 
spremničkih lokacija:</p>
<pre>Novi zahtjev 1 za 5 spremnička mjesta  

12345678901234567890123456789012345678901234567890
000011111-----------------------------------------</pre>
<p>Neka se primjerice nakon toga generira novi zahtjev za 2 spremničke lokacije:</p>
<pre>Novi zahtjev 2 za 2 spremnička mjesta  

12345678901234567890123456789012345678901234567890
00001111122---------------------------------------</pre>
<p>Pritiskom na tipku O oslobađa se spremnik:</p>
<pre>Koji zahtjev treba osloboditi?
1
Oslobađa se zahtjev 1  

12345678901234567890123456789012345678901234567890
0000-----22---------------------------------------</pre>
<p>Neka se primjerice nakon toga generira novi zahtjev za 3 spremničke lokacije 
koje se dodjeljuju u prvu slobodnu najmanju rupu:</p>
<pre>Novi zahtjev 3 za 3 spremnička mjesta  

12345678901234567890123456789012345678901234567890
0000333--22---------------------------------------</pre>
<p>itd.</p>
<p>Ispis stanja spremnika je proizvoljan. Ovo je bio samo primjer ispisa i tijeka 
programa. </p>
<p>Simulacija dinamičkog raspoređivanja spremnika može se odvijati na 
proizvoljan način uz uvjet da se poštuju pravila dinamičkog raspoređivanja 
(dodjeljuje se prva najmanja slobodna rupa, a prilikom oslobađanja rupe se 
spajaju). Nadalje, zahtjevi i trajanje obrade mogu se generirati nasumično pa u 
tom slučaju ne treba čekati da se pritisne neka tipka. </p>
<p>&nbsp;</p>




</body></html>
