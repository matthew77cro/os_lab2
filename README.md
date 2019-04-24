# os_lab2

<!-- saved from url=(0067)http://zemris.fer.hr/predmeti/os/pripreme/upute/visezadacnirad.html -->

<h1><span style="text-transform: uppercase">Višezadaćni rad</span></h1>


<div class="MsoNormal" align="center" style="text-align:center">

<h3 style="text-align: left"> Upute za laboratorijske vježbe</h3>


<hr size="1" width="100%" align="center">

</div>


<p>Višezadaćni rad moguće je ostvariti s pomoću više procesa ili s pomoću više 
dretvi.</p>


<h2>1. Ostvarenje višezadaćnog rada s pomoću više procesa</h2>

<p>Program je skup instrukcija i podataka koji se nalaze u datoteci na disku. U
opisu datoteke ona je opisana kao izvršna i njen sadržaj je organiziran prema
pravilima jezgre. Sve dok sadržaj datoteke odgovara pravilima i dok je označena
kao izvršna, program može biti pokrenut. Kako bi se pokrenuo novi program prvo
treba (pozivom jezgre) stvoriti novi proces koji je okolina u kojem se izvršava
program.</p>

<p>Proces se sastoji od tri segmenta: segment instrukcija, segment korisničkih
podataka i segment sustavskih podataka. Program inicijalizira segment
instrukcija i korisničke podatke. Nakon inicijalizacije više nema čvste veze
između procesa i programa koji on izvodi. Proces dobiva sredstva (više
spremnika, datoteke, itd.) koji nisu prisutni u samom programu, mijenja podatke,
itd. Iz jednog programa može se inicijalizirati više procesa koji se paralelno
izvode.</p>

<h3>Sustavski poziv <i>fork</i></h3>

<p>Sustavskim pozivom <i>fork</i> zahtijeva se stvaranje novog procesa iz 
postojećeg. Kada
proces koji se trenutno izvodi pokrene novi proces, pokrenuti proces postaje
"dijete" procesa "roditelja" koji ga je pokrenuo. Dijete
dobija kopije segmenta instrukcija i segmenta podataka roditelja. U stvari, budući
da se segment instrukcija najčešće ne mijenja, jezgra može uštediti vrijeme i
memoriju tako da postavi taj segment kao zajednički za oba procesa (sve dok ga
jedan od njih ne odluči inicijalizirati novim programom, tj. pokrenuti drugi 
program primjerice naredbom <i>exec</i>). Također, dijete
nasljeđuje većinu sustavskih podataka roditelja.</p>

<pre>int fork(void);</pre>

<p style="tab-stops:45.8pt 91.6pt 137.4pt 183.2pt 229.0pt 274.8pt 320.6pt 366.4pt 412.2pt 458.0pt 503.8pt 549.6pt 595.4pt 641.2pt 687.0pt 732.8pt">U
ovaj sustavski poziv ulazi jedan proces, a iz njega izlaze dva odvojena procesa
("dijete" i "roditelj") koji dobivaju svaki svoju povratnu
vrijednost. Proces dijete dobiva rezultat 0, a roditelj dobiva identifikacijski
broj procesa djeteta. Ako dođe do greške, vraćena vrijednost je -1, a dijete
nije ni stvoreno. <i>fork</i> nema nikakvih argumenata, pa programer ne može
biti odgovoran za grešku već je ona rezultat nemogućnosti jezgre da kreira novi
proces zbog nedostatka nekog od potrebnih sredstava.</p>

<p style="tab-stops:45.8pt 91.6pt 137.4pt 183.2pt 229.0pt 274.8pt 320.6pt 366.4pt 412.2pt 458.0pt 503.8pt 549.6pt 595.4pt 641.2pt 687.0pt 732.8pt">Dijete
nasljeđuje većinu atributa iz segmenta sustavskih podataka kao što su aktualni
direktorij, prioritet ili identifikacijski broj korisnika. Manje je atributa
koji se ne nasljeđuju:</p>

<ul type="disc">
 <li class="MsoNormal" style="mso-margin-top-alt:auto;mso-margin-bottom-alt:auto;
     mso-list:l1 level1 lfo3;tab-stops:list 36.0pt">Identifikacijski brojevi
     procesa djeteta i roditelja su različiti, jer su to različiti procesi.</li>
 <li class="MsoNormal" style="mso-margin-top-alt:auto;mso-margin-bottom-alt:auto;
     mso-list:l1 level1 lfo3;tab-stops:list 36.0pt">Proces dijete dobiva kopije
     otvorenih opisnika datoteka (<i>file descriptor</i>) od roditelja. Dakle
     to nisu isti opisnici datoteka, tj. procesi ih ne dijele. Međutim, procesi
     dijele kazaljke položaja u datotekama (<i>file pointer</i>). Ako jedan
     proces namjesti kazaljku položaja na određeno mjesto u datoteci, drugi
     proces će također čitati odnosno pisati od tog mjesta. Za razliku od toga,
     ako dijete zatvori svoj opisnik datoteke, to nema veze s roditeljevim opisnikom
     datoteke.</li>
 <li class="MsoNormal" style="mso-margin-top-alt:auto;mso-margin-bottom-alt:auto;
     mso-list:l1 level1 lfo3;tab-stops:list 36.0pt">Vrijeme izvođenja procesa
     djeteta je postavljeno na nula.</li>
</ul>

<p style="tab-stops:45.8pt 91.6pt 137.4pt 183.2pt 229.0pt 274.8pt 320.6pt 366.4pt 412.2pt 458.0pt 503.8pt 549.6pt 595.4pt 641.2pt 687.0pt 732.8pt">Dijete
se može inicijalizirati novim programom (poziv <i>exec</i>) ili izvoditi
poseban dio već prisutnog programa, dok roditelj može čekati da dijete završi
ili paralelno raditi nešto drugo. Osnovni oblik upotrebe sustavskog poziva <i>fork
</i>izgleda ovako:</p>

<pre><b><font color="#0000FF">if (fork() </font><font color="#009933">== 0) {</font></b></pre><pre><b><font color="#FF0000"><span style="mso-spacerun: yes">&nbsp;&nbsp; </span><i>posao procesa djeteta</i></font></b></pre><pre><b><font color="#FF0000"><span style="mso-spacerun: yes">&nbsp;&nbsp; </span>exit(0);</font></b></pre><pre><b><font color="#0000FF">}</font></b></pre><pre><b><font color="#0000FF"><i>nastavak rada procesa roditelja (ili ništa);</i></font></b></pre><pre><b><font color="#0000FF">wait(NULL);</font></b></pre>
<p><b><font color="#0000FF">Plavo</font></b> - izvodi proces roditelj, <b>
<font color="#009933">zeleno</font></b> - izvode oba procesa (provjera povratne 
vrijednosti fork()-a), <font color="#FF0000"><b>crveno</b></font> - izvodi 
proces djeteta.</p>

<h3 style="tab-stops:45.8pt 91.6pt 137.4pt 183.2pt 229.0pt 274.8pt 320.6pt 366.4pt 412.2pt 458.0pt 503.8pt 549.6pt 595.4pt 641.2pt 687.0pt 732.8pt">Sustavski
pozivi <i>exit,</i> <i>wait <font color="#FF0000">i getpid</font></i></h3>

<pre>void exit(int status) ;</pre>

<p style="tab-stops:45.8pt 91.6pt 137.4pt 183.2pt 229.0pt 274.8pt 320.6pt 366.4pt 412.2pt 458.0pt 503.8pt 549.6pt 595.4pt 641.2pt 687.0pt 732.8pt">
Poziv <i>exit </i>završava
izvođenje procesa koji poziva tu funkciju. Prije završetka, uredno se
zatvaraju sve otvorene datoteke. Ne vraća nikakvu vrijednost jer iza njega nema
nastavka procesa. Za <i>status</i> se obično stavlja 0 ako proces normalno
završava, a 1 inače. Roditelj procesa koji završava pozivom <i>exit</i> prima
njegov <i>status</i> preko sustavskog poziva <i>wait</i>.</p>

<pre>int wait(int *statusp) ;</pre>

<p style="tab-stops:45.8pt 91.6pt 137.4pt 183.2pt 229.0pt 274.8pt 320.6pt 366.4pt 412.2pt 458.0pt 503.8pt 549.6pt 595.4pt 641.2pt 687.0pt 732.8pt">Ovaj
sustavski poziv čeka da neki od procesa djece završi (ili bude zaustavljen za
vrijeme praćenja), 
<span class="Apple-style-span" style="color: rgb(0, 0, 0); font-family: arial, sans-serif; font-size: 13px; font-style: normal; font-variant: normal; font-weight: normal; letter-spacing: normal; line-height: normal; orphans: 2; text-align: -webkit-auto; text-indent: 0px; text-transform: none; white-space: normal; widows: 2; word-spacing: 0px; -webkit-text-decorations-in-effect: none; -webkit-text-size-adjust: auto; -webkit-text-stroke-width: 0px; background-color: rgb(255, 255, 255); ">
s tim da se ne može definirati na koji proces treba čekati (dočekuje se prvi 
proces dijete koji završi)</span>. 
Funkcija vraća
identifikacijski broj procesa djeteta koji je završio i sprema njegov status
(16 bitova) u cijeli broj na koji pokazuje <i>statusp</i>, osim ako je taj
argument <tt><span style="font-size:10.0pt;font-family:&quot;Courier New&quot;">NULL</span></tt>.
U tom slučaju se status završenog procesa gubi. U slučaju greške (djece nema,
ili je čekanje prekinuto primitkom signala) rezultat je ­1.</p>

<p style="tab-stops:45.8pt 91.6pt 137.4pt 183.2pt 229.0pt 274.8pt 320.6pt 366.4pt 412.2pt 458.0pt 503.8pt 549.6pt 595.4pt 641.2pt 687.0pt 732.8pt">Postoje
tri načina kako može završiti proces: pozivom <i>exit</i>, primitkom signala
ili padom sustava (nestanak napajanja ili slično). Na koji je način proces
završio možemo pročitati iz statusa na koji pokazuje <i>statusp</i> osim ako se
radi o trećem slučaju (vidi <tt><span style="font-size:10.0pt;font-family:&quot;Courier New&quot;">man
wait</span></tt>).</p>

<p style="tab-stops:45.8pt 91.6pt 137.4pt 183.2pt 229.0pt 274.8pt 320.6pt 366.4pt 412.2pt 458.0pt 503.8pt 549.6pt 595.4pt 641.2pt 687.0pt 732.8pt">Ako
proces roditelj završi prije svog procesa djeteta, djetetu se dodjeljuje novi
roditelj - proces <i>init</i> s identifikacijskim brojem 1. <i>init</i> je
važan prilikom pokretanja sustava, a u kasnijem radu većinom izvodi <i>wait</i>
i tako "prikuplja izgubljenu djecu" kada završe.</p>

<p style="tab-stops:45.8pt 91.6pt 137.4pt 183.2pt 229.0pt 274.8pt 320.6pt 366.4pt 412.2pt 458.0pt 503.8pt 549.6pt 595.4pt 641.2pt 687.0pt 732.8pt">Ako
proces dijete završi, a roditelj ga ne čeka sa <i>wait</i>, on postaje
proces-zombi (<i>zombie</i>). Otpuštaju se njegovi segmenti u radnom spremniku, ali se
zadržavaju njegovi podaci u tablici procesa. Oni su potrebni sve dok roditelj
ne izvede <i>wait</i> kada proces-zombi nestaje. Ako roditelj završi, a da nije
pozvao <i>wait</i>, proces-zombi dobiva novog roditelja (<i>init</i>) koji će
ga prikupiti sa <i>wait</i>.</p>

<pre style="tab-stops: 45.8pt 91.6pt 137.4pt 183.2pt 229.0pt 274.8pt 320.6pt 366.4pt 412.2pt 458.0pt 503.8pt 549.6pt 595.4pt 641.2pt 687.0pt 732.8pt; font-size: 10.0pt; font-family: Courier New; margin-left: 0cm; margin-right: 0cm; margin-top: 0cm; margin-bottom: .0001pt"><font color="#FF0000">pid_t getpid() ;</font></pre>

<p style="tab-stops:45.8pt 91.6pt 137.4pt 183.2pt 229.0pt 274.8pt 320.6pt 366.4pt 412.2pt 458.0pt 503.8pt 549.6pt 595.4pt 641.2pt 687.0pt 732.8pt">
<font color="#FF0000">Poziv <i>getpid </i>vraća identifikacijski broj procesa 
(PID).</font></p>

<p style="tab-stops:45.8pt 91.6pt 137.4pt 183.2pt 229.0pt 274.8pt 320.6pt 366.4pt 412.2pt 458.0pt 503.8pt 549.6pt 595.4pt 641.2pt 687.0pt 732.8pt">&nbsp;</p>

<h3 style="tab-stops:45.8pt 91.6pt 137.4pt 183.2pt 229.0pt 274.8pt 320.6pt 366.4pt 412.2pt 458.0pt 503.8pt 549.6pt 595.4pt 641.2pt 687.0pt 732.8pt">Pokretanje
paralelnih procesa</h3>

<p style="tab-stops:45.8pt 91.6pt 137.4pt 183.2pt 229.0pt 274.8pt 320.6pt 366.4pt 412.2pt 458.0pt 503.8pt 549.6pt 595.4pt 641.2pt 687.0pt 732.8pt">U
ovoj vježbi trebat će pokrenuti više procesa tako da rade paralelno. To se može
izvesti s dvije petlje. U prvoj se stvaraju procesi djeca pozivom <i>fork</i>
a svako dijete poziva odgovarajuću funkciju. Iza poziva funkcije treba se
nalaziti <i>exit</i> jer samo roditelj nastavlja izvršavanje petlje. Nakon
izlaska iz prve petlje, roditelj poziva <i>wait</i> toliko puta koliko je
procesa djece stvorio.</p>

<pre>for (i = 0; i &lt; N; i++)</pre><pre><span style="mso-spacerun: yes">&nbsp;&nbsp; switch</span> (fork()) {</pre><pre>   case 0:</pre><pre><span style="mso-spacerun: yes">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </span><i>funkcija koja obavlja posao djeteta</i> <b>i</b></pre><pre><span style="mso-spacerun: yes">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </span>exit(0);</pre><pre>   case -1:</pre><pre>      <i>ispis poruke o nemogućnosti stvaranja procesa;
</i>   dafault:
      <i>nastavak posla roditelja;</i></pre><pre><span style="mso-spacerun: yes">&nbsp;&nbsp; </span>}</pre><pre>&nbsp;</pre><pre>while (i--)<span style="mso-spacerun: yes"> </span>wait (NULL);</pre>

<h3 style="tab-stops:45.8pt 91.6pt 137.4pt 183.2pt 229.0pt 274.8pt 320.6pt 366.4pt 412.2pt 458.0pt 503.8pt 549.6pt 595.4pt 641.2pt 687.0pt 732.8pt">
<a name="ZAJEDNICKI_ADRESNI_PROSTOR">ZAJEDNIČKI
ADRESNI PROSTOR</a></h3>

<p style="tab-stops:45.8pt 91.6pt 137.4pt 183.2pt 229.0pt 274.8pt 320.6pt 366.4pt 412.2pt 458.0pt 503.8pt 549.6pt 595.4pt 641.2pt 687.0pt 732.8pt">Nakon
stvaranja novog procesa sa <i>fork</i>, procesi roditelj i dijete dijele
segment s podacima koji se sastoji od stranica. Sve dok je stranica
nepromjenjena oba procesa je mogu čitati. Ali čim jedan proces pokuša pisati na
stranicu procesi dobiva odvojene kopije podataka. Tada niti globalne varijable
nisu zajedničke za sve procese, pa ako jedan proces promjeni neku varijablu
drugi to neće primijetiti. To je jedan od razloga za korištenje zajedničkog
spremnika. Varijable koja trebaju biti zajedničke za sve procese moraju se
nalaziti u zajedničkom spremniku kojeg prethodno treba zauzeti.</p>

<p style="tab-stops:45.8pt 91.6pt 137.4pt 183.2pt 229.0pt 274.8pt 320.6pt 366.4pt 412.2pt 458.0pt 503.8pt 549.6pt 595.4pt 641.2pt 687.0pt 732.8pt">Zajednički
spremnički prostor je najbrži način komunikacije među procesima. Isti
spremnik je
priključen adresnim prostorima dva ili više procesa. Čim je nešto upisano u
zajednički spremnik, istog trenutka je dostupno svim procesima koji imaju
priključen taj dio zajedničkog spremnika na svoj adresni prostor. Za
sinkronizaciju čitanja i pisanja u zajednički spremnik mogu se upotrijebiti
semafori, poruke ili posebni algoritmi.</p>

<p style="tab-stops:45.8pt 91.6pt 137.4pt 183.2pt 229.0pt 274.8pt 320.6pt 366.4pt 412.2pt 458.0pt 503.8pt 549.6pt 595.4pt 641.2pt 687.0pt 732.8pt">Blok
zajedničkog spremnika se kraće naziva segment. Može biti više zajedničkih
segmenata koji su zajednički za različte kombinacije aktivnih procesa. Svaki
proces može pristupiti k više segmenata. Segment je prvo stvoren izvan adresnog
prostora bilo kojeg procesa, a svaki proces koji želi pristupiti segmentu
izvršava sustavski poziv kojim ga veže na svoj adresni prostor. Broj segmenata
je određen sklopovskim ograničenjima, a veličina segmenta može također biti
ograničena.</p>

<h3 style="tab-stops:45.8pt 91.6pt 137.4pt 183.2pt 229.0pt 274.8pt 320.6pt 366.4pt 412.2pt 458.0pt 503.8pt 549.6pt 595.4pt 641.2pt 687.0pt 732.8pt">Sustavski
pozivi za stvaranje i rad sa zajedničkim spremnikom</h3>

<pre>typedef key_t int;</pre><pre>int shmget(key_t key, int size, int flags) ;</pre>

<p style="tab-stops:45.8pt 91.6pt 137.4pt 183.2pt 229.0pt 274.8pt 320.6pt 366.4pt 412.2pt 458.0pt 503.8pt 549.6pt 595.4pt 641.2pt 687.0pt 732.8pt">Ovaj
sustavski poziv pretvara ključ (<i>key</i>) nekog segmenta zajedničkog
spremnika u njegov identifikacijski broj ili stvara novi segment. Novi segment duljine
barem <i>size</i> bajtova će biti stvoren ako se kao ključ upotrijebi <tt><span style="font-size:10.0pt;font-family:&quot;Courier New&quot;">IPC_PRIVATE</span></tt>. U
devet najnižih bitova <i>flags</i> se stavljaju dozvole pristupa (na primjer,
oktalni broj 0600 znači da korisnik može čitati i pisati, a grupa i ostali ne
mogu). <i>shmget</i> vraća identifikacijski broj segmenta koji je potreban u <i>shmat</i>
ili -1 u slučaju greške.</p>

<p style="tab-stops:45.8pt 91.6pt 137.4pt 183.2pt 229.0pt 274.8pt 320.6pt 366.4pt 412.2pt 458.0pt 503.8pt 549.6pt 595.4pt 641.2pt 687.0pt 732.8pt">Proces
veže segment na svoj adresni prostor sa <i>shmat</i>:</p>

<pre>char *shmat(int segid, char *addr, int flags) ;</pre>

<p style="tab-stops:45.8pt 91.6pt 137.4pt 183.2pt 229.0pt 274.8pt 320.6pt 366.4pt 412.2pt 458.0pt 503.8pt 549.6pt 595.4pt 641.2pt 687.0pt 732.8pt">Ako
segment treba vezati na određenu adresu treba je staviti u <i>addr</i>, a ako
je <i>addr</i> jednako <tt><span style="font-size:10.0pt;font-family:&quot;Courier New&quot;">NULL</span></tt>
jezgra će sama odabrati adresu (moguće ako se kasnije ne koristi dinamičko
zauzimanje spremnika s <i>malloc</i> ili slično). <i>flags</i> također najčešće
može biti 0. <i>segid</i> je identifikacijski broj segmenta dobijen pozivom <i>shmget</i>.<i>
shmat </i>vraća kazaljku na zajednički adresni prostor duljine tražene u shmget ili -1
ako dođe do greške. Dohvaćanje i spremanje podataka u segmente obavlja se na
uobičajen način.</p>

<p style="tab-stops:45.8pt 91.6pt 137.4pt 183.2pt 229.0pt 274.8pt 320.6pt 366.4pt 412.2pt 458.0pt 503.8pt 549.6pt 595.4pt 641.2pt 687.0pt 732.8pt">Segment
se može otpustiti sustavskim pozivom <i>shmdt</i>:</p>

<pre>int shmdt(char *addr) ;</pre>

<p style="tab-stops:45.8pt 91.6pt 137.4pt 183.2pt 229.0pt 274.8pt 320.6pt 366.4pt 412.2pt 458.0pt 503.8pt 549.6pt 595.4pt 641.2pt 687.0pt 732.8pt">Zajednički
spremnički prostor ostaje nedirnut i može mu se opet pristupiti tako da se
ponovno veže na adresni prostor procesa, iako je moguće da pri tome dobije drugu
adresu u njegovom adresnom prostoru. <i>addr</i> je adresa segmenta dobivena
pozivom <i>shmat</i>.</p>

<p style="tab-stops:45.8pt 91.6pt 137.4pt 183.2pt 229.0pt 274.8pt 320.6pt 366.4pt 412.2pt 458.0pt 503.8pt 549.6pt 595.4pt 641.2pt 687.0pt 732.8pt">Uništavanje
segmenta zajedničke memorije izvodi se sustavskim pozivom <i>shmctl</i>:</p>

<pre>int shmctl(int segid, int cmd, struct shmid_ds *sbuf) ;</pre>

<p style="tab-stops:45.8pt 91.6pt 137.4pt 183.2pt 229.0pt 274.8pt 320.6pt 366.4pt 412.2pt 458.0pt 503.8pt 549.6pt 595.4pt 641.2pt 687.0pt 732.8pt">Za
uništavanje segmenta treba za <i>segid</i> staviti identifikacijski broj
dobiven sa <i>shmget</i>, <i>cmd</i> treba biti <tt><span style="font-size:
10.0pt;font-family:&quot;Courier New&quot;">IPC_RMID</span></tt>, a <i>sbuf</i> može biti
<tt><span style="font-size:10.0pt;font-family:&quot;Courier New&quot;">NULL</span></tt>.
Greška je uništiti segment koji nije otpušten iz adresnog prostora svih procesa
koji su ga koristili. <i>shmctl</i>, kao i<i> shmdt</i> vraća 0 ako je sve u
redu, a -1 u slučaju greške. (Detaljnije o ovim pozivima u: <tt><span style="font-size:10.0pt;font-family:&quot;Courier New&quot;">man shmget</span></tt>, <tt><span style="font-size:10.0pt;font-family:&quot;Courier New&quot;">man shmop</span></tt>, <tt><span style="font-size:10.0pt;font-family:&quot;Courier New&quot;">man shmctl</span></tt>)</p>

<h3 style="tab-stops:45.8pt 91.6pt 137.4pt 183.2pt 229.0pt 274.8pt 320.6pt 366.4pt 412.2pt 458.0pt 503.8pt 549.6pt 595.4pt 641.2pt 687.0pt 732.8pt">Struktura
programa sa paralelnim procesima i zajedničkim spremnikom</h3>

<pre><i>definiranje kazaljki na zajedničke varijable</i></pre><pre></pre><pre>proces <b>k</b></pre><pre><span style="mso-spacerun: yes">&nbsp;&nbsp; </span><u>početak</u></pre><pre><span style="mso-spacerun: yes">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </span><i>proces koji koristi zajedničke varijable</i></pre><pre><span style="mso-spacerun: yes">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </span>...</pre><pre><span style="mso-spacerun: yes">&nbsp;&nbsp; </span><u>kraj</u></pre><pre>...</pre><pre></pre><pre>glavni program</pre><pre><span style="mso-spacerun: yes">&nbsp;&nbsp; </span><u>početak</u></pre><pre><span style="mso-spacerun: yes">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </span>zauzimanje zajedničke memorije</pre><pre><span style="mso-spacerun: yes">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </span>pokretanje paralelnih procesa</pre><pre><span style="mso-spacerun: yes">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </span>oslobađanje zauzete zajedničke memorije</pre><pre><span style="mso-spacerun: yes">&nbsp;&nbsp; </span><u>kraj</u></pre>

<p style="tab-stops:45.8pt 91.6pt 137.4pt 183.2pt 229.0pt 274.8pt 320.6pt 366.4pt 412.2pt 458.0pt 503.8pt 549.6pt 595.4pt 641.2pt 687.0pt 732.8pt"><b>VAŽNO</b>:
Varijablama u zajedničkom spremniku se nužno pristupa korištenjem kazaljki.</p>

<h3 style="tab-stops:45.8pt 91.6pt 137.4pt 183.2pt 229.0pt 274.8pt 320.6pt 366.4pt 412.2pt 458.0pt 503.8pt 549.6pt 595.4pt 641.2pt 687.0pt 732.8pt">Primjer
programa sa paralelnim procesima i zajedničkim spremnikom</h3>

<p style="tab-stops:45.8pt 91.6pt 137.4pt 183.2pt 229.0pt 274.8pt 320.6pt 366.4pt 412.2pt 458.0pt 503.8pt 549.6pt 595.4pt 641.2pt 687.0pt 732.8pt">Ovo
je trivijalan primjer korištenja zajedničkog spremnika. Koristi se jedna
cjelobrojna zajednička varijabla. Stvaraju se dva paralelna procesa, od kojih
jedan upisuje vrijednost (različitu od 0) u tu varijablu, a drugi čeka da ona
bude upisana.</p>

<pre>#include &lt;stdio.h&gt;</pre>
<pre>#include &lt;signal.h&gt;</pre><pre>#include &lt;sys/types.h&gt;</pre><pre>#include &lt;sys/ipc.h&gt;</pre><pre>#include &lt;sys/shm.h&gt;</pre><pre></pre>
<pre style="tab-stops: 45.8pt 91.6pt 137.4pt 183.2pt 229.0pt 274.8pt 320.6pt 366.4pt 412.2pt 458.0pt 503.8pt 549.6pt 595.4pt 641.2pt 687.0pt 732.8pt; font-size: 10.0pt; font-family: Courier New; margin-left: 0cm; margin-right: 0cm; margin-top: 0cm; margin-bottom: .0001pt">int Id;<span style="mso-spacerun: yes">&nbsp;</span>/* <i>identifikacijski broj segmenta</i> */</pre><pre>int *ZajednickaVarijabla;</pre><pre>&nbsp;</pre>
<pre>void Pisac(int i)
{</pre><pre><span style="mso-spacerun: yes">&nbsp;&nbsp; </span>*ZajednickaVarijabla = i;</pre><pre>}</pre><pre></pre><pre>void Citac(void)
{</pre><pre><span style="mso-spacerun: yes">&nbsp;&nbsp; </span>int i;</pre><pre></pre><pre><span style="mso-spacerun: yes">&nbsp;&nbsp; </span>do {</pre><pre><span style="mso-spacerun: yes">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </span>i = *ZajednickaVarijabla;</pre>
<pre>      printf("Procitano %d\n", i);</pre>
<pre>      sleep(1);</pre><pre><span style="mso-spacerun: yes">&nbsp;&nbsp; </span>} while (i == 0);</pre><pre></pre><pre><span style="mso-spacerun: yes">&nbsp;&nbsp; </span>printf("Procitano je: %d\n", i);</pre><pre>}</pre><pre>void brisi(int sig)
{</pre>
<pre style="tab-stops: 45.8pt 91.6pt 137.4pt 183.2pt 229.0pt 274.8pt 320.6pt 366.4pt 412.2pt 458.0pt 503.8pt 549.6pt 595.4pt 641.2pt 687.0pt 732.8pt; font-size: 10.0pt; font-family: Courier New; margin-left: 0cm; margin-right: 0cm; margin-top: 0cm; margin-bottom: .0001pt"><span style="mso-spacerun: yes">&nbsp;&nbsp; </span>/* <i>oslobađanje zajedničke memorije</i> */</pre>
<pre style="tab-stops: 45.8pt 91.6pt 137.4pt 183.2pt 229.0pt 274.8pt 320.6pt 366.4pt 412.2pt 458.0pt 503.8pt 549.6pt 595.4pt 641.2pt 687.0pt 732.8pt; font-size: 10.0pt; font-family: Courier New; margin-left: 0cm; margin-right: 0cm; margin-top: 0cm; margin-bottom: .0001pt"><span style="mso-spacerun: yes">&nbsp;&nbsp; </span>(void) shmdt((char *) ZajednickaVarijabla);</pre>
<pre style="tab-stops: 45.8pt 91.6pt 137.4pt 183.2pt 229.0pt 274.8pt 320.6pt 366.4pt 412.2pt 458.0pt 503.8pt 549.6pt 595.4pt 641.2pt 687.0pt 732.8pt; font-size: 10.0pt; font-family: Courier New; margin-left: 0cm; margin-right: 0cm; margin-top: 0cm; margin-bottom: .0001pt"><span style="mso-spacerun: yes">&nbsp;&nbsp; </span>(void) shmctl(Id, IPC_RMID, NULL);</pre>
<pre style="tab-stops: 45.8pt 91.6pt 137.4pt 183.2pt 229.0pt 274.8pt 320.6pt 366.4pt 412.2pt 458.0pt 503.8pt 549.6pt 595.4pt 641.2pt 687.0pt 732.8pt; font-size: 10.0pt; font-family: Courier New; margin-left: 0cm; margin-right: 0cm; margin-top: 0cm; margin-bottom: .0001pt"><span style="mso-spacerun: yes">&nbsp;&nbsp; </span>exit(0);</pre>
<pre style="tab-stops: 45.8pt 91.6pt 137.4pt 183.2pt 229.0pt 274.8pt 320.6pt 366.4pt 412.2pt 458.0pt 503.8pt 549.6pt 595.4pt 641.2pt 687.0pt 732.8pt; font-size: 10.0pt; font-family: Courier New; margin-left: 0cm; margin-right: 0cm; margin-top: 0cm; margin-bottom: .0001pt"></pre>
<pre>}</pre>
<pre>int main(void)
{</pre><pre><span style="mso-spacerun: yes">&nbsp;&nbsp; </span>/* <i>zauzimanje zajedničke memorije</i> */</pre><pre><span style="mso-spacerun: yes">&nbsp;&nbsp; </span>Id = shmget(IPC_PRIVATE, sizeof(int), 0600);</pre>
<pre>&nbsp;</pre>
<pre><span style="mso-spacerun: yes">&nbsp;&nbsp; </span>if (Id == -1)</pre><pre><span style="mso-spacerun: yes">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </span>exit(1);<span style="mso-spacerun: yes">&nbsp; </span>/* <i>greška - nema zajedničke memorije</i> */</pre><pre>&nbsp;</pre>
<pre style="tab-stops: 45.8pt 91.6pt 137.4pt 183.2pt 229.0pt 274.8pt 320.6pt 366.4pt 412.2pt 458.0pt 503.8pt 549.6pt 595.4pt 641.2pt 687.0pt 732.8pt; font-size: 10.0pt; font-family: Courier New; margin-left: 0cm; margin-right: 0cm; margin-top: 0cm; margin-bottom: .0001pt"><span style="mso-spacerun: yes">&nbsp;&nbsp; </span>ZajednickaVarijabla = (int *) shmat(Id, NULL, 0);</pre>
<pre style="tab-stops: 45.8pt 91.6pt 137.4pt 183.2pt 229.0pt 274.8pt 320.6pt 366.4pt 412.2pt 458.0pt 503.8pt 549.6pt 595.4pt 641.2pt 687.0pt 732.8pt; font-size: 10.0pt; font-family: Courier New; margin-left: 0cm; margin-right: 0cm; margin-top: 0cm; margin-bottom: .0001pt"><span style="mso-spacerun: yes">&nbsp;&nbsp; *</span>ZajednickaVarijabla = 0;</pre>
<pre>   sigset(SIGINT, brisi);//u slučaju prekida briši memoriju</pre>
<pre>&nbsp;</pre>
<pre style="tab-stops: 45.8pt 91.6pt 137.4pt 183.2pt 229.0pt 274.8pt 320.6pt 366.4pt 412.2pt 458.0pt 503.8pt 549.6pt 595.4pt 641.2pt 687.0pt 732.8pt; font-size: 10.0pt; font-family: Courier New; margin-left: 0cm; margin-right: 0cm; margin-top: 0cm; margin-bottom: .0001pt"><span style="mso-spacerun: yes">&nbsp;&nbsp; </span>/* <i>pokretanje paralelnih procesa</i> */</pre>
<pre><span style="mso-spacerun: yes">&nbsp;&nbsp; </span>if (fork() == 0) {</pre><pre><span style="mso-spacerun: yes">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </span>Citac();</pre><pre><span style="mso-spacerun: yes">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </span>exit(0);</pre><pre><span style="mso-spacerun: yes">&nbsp;&nbsp; </span>}</pre>
<pre><span style="mso-spacerun: yes">&nbsp;&nbsp; </span>if (fork() == 0) {</pre>
<pre style="tab-stops: 45.8pt 91.6pt 137.4pt 183.2pt 229.0pt 274.8pt 320.6pt 366.4pt 412.2pt 458.0pt 503.8pt 549.6pt 595.4pt 641.2pt 687.0pt 732.8pt; font-size: 10.0pt; font-family: Courier New; margin-left: 0cm; margin-right: 0cm; margin-top: 0cm; margin-bottom: .0001pt">      sleep(5);</pre><pre><span style="mso-spacerun: yes">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </span>Pisac(123);</pre><pre><span style="mso-spacerun: yes">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </span>exit(0);</pre><pre><span style="mso-spacerun: yes">&nbsp;&nbsp; </span>}</pre><pre><span style="mso-spacerun: yes">&nbsp;&nbsp; </span>(void) wait(NULL);</pre><pre><span style="mso-spacerun: yes">&nbsp;&nbsp; </span>(void) wait(NULL);</pre>
<pre>   brisi(0);</pre><pre></pre><pre>&nbsp;</pre>
<pre><span style="mso-spacerun: yes">&nbsp;&nbsp; return 0</span>;</pre><pre>}</pre>

<p style="tab-stops:36.0pt">Ako se segment zajedničkog spremnika ne uništi,
zajednički adresni prostor ostaje trajno zauzet i nakon završetka svih procesa koji
ga koriste, pa čak i nakon što korisnik koji ga je stvorio napusti računalo <tt><span style="font-size:10.0pt;font-family:&quot;Courier New&quot;">(logout</span></tt>). </p>
<p style="tab-stops:36.0pt"><b>Ukoliko se koristi zajedničko računalo</b> za više korisnika i budući
je broj segmenata ograničen, to ubrzo može izazvati nemogućnost rada programa
koji koriste zajednički spremnik. (Isto vrijedi i za ostala sredstva za
međuprocesnu komunikaciju: skupove semafora i redove poruka.) Podaci o
upotrijebljenim sredstvima za međuprocesnu komunikaciju mogu se dobiti
naredbom: <i>ipcs</i>. Naredbom <i>ipcrm</i> mogu se uništavati pojedina sredstva
(vidi: <i> man ipcrm, man ipcs</i>). Za lakše uništavanje zaostalih segmenata
zajedničkog spremnika (kao i skupova semafora i redova poruka) može poslužiti
jednostavan program <i>brisi</i>:</p>

<pre><tt><a name="Brisanje memorije"></a>#include &lt;stdio.h&gt;</tt></pre><pre><tt>#include &lt;sys/types.h&gt;</tt></pre><pre><tt>#include &lt;sys/ipc.h&gt;</tt></pre><pre><tt>#include &lt;sys/shm.h&gt;</tt></pre><pre><tt>#include &lt;sys/sem.h&gt;</tt></pre><pre><tt>#include &lt;sys/msg.h&gt;</tt></pre><pre><tt>#include &lt;values.h&gt;</tt></pre><pre></pre><pre><tt>
int main ( void ) </tt></pre><pre><tt>{</tt></pre><pre><tt><span style="mso-spacerun: yes">&nbsp;&nbsp; </span>int i;</tt></pre><pre></pre><pre><tt><span style="mso-spacerun: yes">&nbsp;&nbsp; </span>for (i = 1; i &lt; MAXLONG; i++) {</tt></pre><pre><tt><span style="mso-spacerun: yes">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </span>if (shmctl(i, IPC_RMID, NULL) != -1)</tt></pre><pre><tt><span style="mso-spacerun: yes">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </span>printf("Obrisao zajednicku memoriju %d\n", i); </tt></pre><pre><tt><span style="mso-spacerun: yes">
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>if (semctl(i, 0, IPC_RMID, 0) != -1)</tt></pre><pre><tt><span style="mso-spacerun: yes">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </span>printf("Obrisao skup semafora %d\n", i); </tt></pre><pre><tt><span style="mso-spacerun: yes">
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>if (msgctl(i, IPC_RMID, NULL) != -1)</tt></pre><pre><tt><span style="mso-spacerun: yes">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </span>printf("Obrisao red poruka %d\n", i); </tt></pre><pre><tt><span style="mso-spacerun: yes">&nbsp;&nbsp;&nbsp;</span>}</tt></pre><pre></pre><pre><tt><span style="mso-spacerun: yes">&nbsp;&nbsp; </span>return 0;</tt></pre><pre><tt>}</tt></pre>
<p><span style="" lang="HR"><font size="3">U svaki program uključiti 
mogućnost prijevremenog izlaska iz programa (ctrl+C) na način kao što je to 
ostvareno u prvoj vježbi, s tim da prekidna rutina briše zauzete sustavske 
resurse (semafore i zajednički spremnik) prije no što program završi.</font></span></p>

<font size="5">

<b><hr><h2 align="left">2. Višedretvenost</h2>
</b></font><p align="JUSTIFY">Povijest višedretvenog programiranja počinje 60-tih, dok se njihova implementacija na UNIX sustavima pojavljuje sredinom 80-tih godina, a na ostalim sustavima nešto kasnije. Ideja višedretvenog programiranja jest u tome da se program sastoji od više jedinica koje se samostalno mogu izvoditi. Programer ne mora brinuti o redoslijedu njihova izvođenja, već to obavlja sam operacijski sustav. Štoviše, ukoliko je to višeprocesorski sustav, onda se neke jedinice-dretve mogu izvoditi istovremeno. 
Komunikacija među dretvama je jednostavna i brža u odnosu na komunikaciju među procesima, jer se obavlja preko zajedničkog adresnog prostora, te se može obaviti bez uplitanja operacijskog sustava. </p>
<p align="CENTER"><img border="0" src="./Višezadaćni rad_files/viseza2.gif"></p>
<i>
<b><p align="center">Slika: Arhitektura višedretvenog sustava</p>
</b></i>
<p align="JUSTIFY">Operacijski sustav za koji su predviđene ove laboratorijske 
vježbe jest UNIX sustav koji podržava POSIX dretve. Gornja slika prikazuje 
primjere procesa s jednom, dvije, tri, dvije i četiri dretve. Uobičajeno je da 
operacijski sustav raspoređuje dretve na raspoložive procesore te se u gornjoj 
slici svaka dretva vidi i u operacijskom sustavu, tj. svakoj dretvi pripada 
virtualni procesor, na slici označen s LWP (Light Weight Process).<br>
Neki sustavi dozvoljavaju i djelomično upravljanje dretvama u procesima, pa tako 
broj dretvi u procesu može biti i veći nego što operacijski sustav vidi 
(pogledati poziv thr_create u Solarisu i pojmove "bound" i "unbound" dretve; "<a href="http://en.wikipedia.org/wiki/Fiber_(computer_science)">fiber</a>"-i 
na Win* i sl.).</p><font size="4">
<b>
<p align="JUSTIFY">Funkcije za rukovanje dretvama</p>
</b>
<p align="JUSTIFY">U nastavku su objašnjene funkcije po POSIX standardu (pogledati <font face="Courier New" size="2">man threads</font>).</p>
<b><i>
<p align="JUSTIFY">Stvaranje dretvi</p>
</i>
</b></font><p align="JUSTIFY">Sve dretve, osim prve, inicijalne, koja nastaje stvaranjem procesa, nastaju pozivom 
<font face="Courier New" size="2"> pthread_create:</font></p>
<font face="Courier New" size="2">
<div align="justify">
  <pre><font size="2">   int pthread<i>_</i>create(pthread<i>_</i>t *thread, const pthread<i>_</i>attr<i>_</i>t *attr,</font></pre>
</div>
<div align="justify">
  <pre><font size="2">                      void *(*start<i>_</i>routine)(void *), void *arg);</font></pre>
</div></font>
<p align="JUSTIFY"><font face="Courier New" size="2">thread</font> je kazaljka na mjesto u memoriji gdje se sprema<font face="Courier New" size="2">
id </font>novostvorene dretve<font size="2" face="Courier New">. attr</font> 
je adresa strukture koja sadrži podatke o atributima s kojima se želi stvoriti 
dretvu. Ako se za attr postavi <font face="Courier New" size="2">NULL</font> onda se uzimaju pretpostavljene vrijednosti 
(dovoljno dobre za lab. vježbe). <font size="3"><font face="Courier New" size="2">start_routine</font> 
predstavlja pokazivač na početnu funkciju koju će novostvorena dretva imati kao 
početnu (npr. kao što glavna dretva ima funkciju <font face="Courier New" size="2">main</font>).
<font face="Courier New" size="2">arg</font> je adresa parametra koji se prenosi dretvi 
(može biti </font>NULL<font size="3"> ako se ništa ne prenosi). Budući da 
se može prenijeti samo jedan parametar u slučaju potrebe prijenosa više 
parametara oni se pohranjuju u strukturu te se šalje pokazivač na tu struktru.</font></p>
<font size="4"><i><b><p align="JUSTIFY">Završetak rada dretve</p>
</b></i></font><p align="JUSTIFY">Normalan završetak dretve jest njen izlazak iz prve, inicijalne funkcije, ili pozivom funkcije <font face="Courier New" size="2">
pthread_exit</font>: </p>
<p align="JUSTIFY">
<font face="Courier New" size="2">int pthread_exit(void *status);</font></p><font face="Courier New" size="2">
</font><p align="JUSTIFY"><font face="Courier New" size="2"><font face="Courier New" size="2">status</font></font> je kazaljka na stanje sa kojim dretva završava. </p>
<p align="JUSTIFY">Dretva čeka na završetak druge dretve pozivom funkcije
<font face="Courier New" size="2">pthread_join</font>:</p>
<p align="JUSTIFY">
<font face="Courier New" size="2">int pthread_join( pthread_t cekana_dr, void **stanje);
</font></p>
<p align="JUSTIFY">
<font face="Courier New" size="2">cekana_dr</font> je identifikacijski broj dretve na čiji se kraj čeka 
(<i>thr_join</i>). <font face="Courier New" size="2">stanje</font> je kazaljka na kazaljku izlaznog statusa dočekane dretve. Funkcija
<font face="Courier New" size="2">pthread_join</font> zaustavlja izvođenje pozivajuće dretve sve dok određena dretva ne završi sa radom. Nakon ispravnog završetka funkcija vraća nulu.</p>
<p align="JUSTIFY">Normalni završetak višedretvenog programa zbiva se kada sve dretve završe
s radom, odnosno, kada prva, početna dretva izađe iz prve funkcije (<i>main</i>)<i>.</i> Prijevremeni završetak zbiva se pozivom funkcije <i>exit</i> od strane bilo koje dretve, ili pak nekim vanjskim signalom (<font face="Courier New" size="2">SIGKILL</font>, <font face="Courier New" size="2">SIGSEGV</font>, <font face="Courier New" size="2">SIGINT</font>, <font face="Courier New" size="2">SIGTERM</font>, ...).</p>
<p align="JUSTIFY"><font face="Times New Roman" size="3">Primjer jednog 
višedretvenog programa koji koristi istu varijablu:</font></p>
<font size="4">
<div align="justify">
  <pre>#include &lt;stdio.h&gt;
#include &lt;pthread.h&gt;

int ZajednickaVarijabla;

void *Pisac(void *x)
{
   ZajednickaVarijabla = *((int*)x);
}

void *Citac(void *x)
{
   int i;

   do {
      i = ZajednickaVarijabla;
      printf("Procitano %d\n", i);</pre>
  <pre style="tab-stops: 45.8pt 91.6pt 137.4pt 183.2pt 229.0pt 274.8pt 320.6pt 366.4pt 412.2pt 458.0pt 503.8pt 549.6pt 595.4pt 641.2pt 687.0pt 732.8pt; font-size: 10.0pt; font-family: Courier New; margin-left: 0cm; margin-right: 0cm; margin-top: 0cm; margin-bottom: .0001pt">      sleep(1);</pre>
  <pre>   } while (i == 0);

   printf("Procitano je: %d\n", i);
}

int main(void)
{
   int i;</pre>
  <pre>   pthread_t thr_id[2];

   ZajednickaVarijabla = 0;
   i=123;

   /* pokretanje dretvi */
   if (pthread_create(&amp;thr_id[0], NULL, Citac, NULL) != 0) {
      printf("Greska pri stvaranju dretve!\n");
      exit(1);
   }
   sleep(5);
   if (pthread_create(&amp;thr_id[1], NULL, Pisac, &amp;i) != 0) {
      printf("Greska pri stvaranju dretve!\n");
      exit(1);
   }

   pthread_join(thr_id[0], NULL);
   pthread_join(thr_id[1], NULL);

   return 0;
}</pre><p align="JUSTIFY">Identifikacijski broj dretve moguće je dobiti pozivom funkcije <font face="Courier New" size="2">
pthread_self</font>: </p>
<p align="JUSTIFY">
<font face="Courier New" size="2">pthread_t pthread_self(void);</font></p>
</div>
<i><p align="JUSTIFY">Napomene</p>
</i></font><p align="JUSTIFY">
<span lang="EN-GB" style="font-family: Times New Roman; font-style: normal; font-variant: normal; font-weight: normal; letter-spacing: normal; line-height: normal; orphans: auto; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: 1; word-spacing: 0px; -webkit-text-stroke-width: 0px; color: red">
<ins datetime="2015-10-27T09:05"><font size="3">Prilikom prevođenja potrebno je 
postaviti zastavicu</font><span class="Apple-converted-space"><font size="3">&nbsp;</font></span></ins></span><span style="color: rgb(0, 0, 0); font-family: Times New Roman; font-style: normal; font-variant: normal; font-weight: normal; letter-spacing: normal; line-height: normal; orphans: auto; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: 1; word-spacing: 0px; -webkit-text-stroke-width: 0px"><i><span lang="EN-GB" style="font-family: Courier New; color: red"><ins datetime="2015-10-27T09:05"><font size="2">-pthread</font></ins></span></i></span><span lang="EN-GB" style="font-family: Times New Roman; font-style: normal; font-variant: normal; font-weight: normal; letter-spacing: normal; line-height: normal; orphans: auto; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: 1; word-spacing: 0px; -webkit-text-stroke-width: 0px; color: red"><ins datetime="2015-10-27T09:05"><span class="Apple-converted-space"><font size="3">&nbsp;</font></span><font size="3">koja 
ukazuje<span class="Apple-converted-space">&nbsp;</span>na<span class="Apple-converted-space">&nbsp;</span>to 
da se korist</font></ins><font size="3"><ins datetime="2015-10-27T09:06">i</ins><ins datetime="2015-10-27T09:05"><span class="Apple-converted-space">&nbsp;</span>višedretven</ins><ins datetime="2015-10-27T09:06">i 
program</ins></font><ins datetime="2015-10-27T09:05"><font size="3"><span class="Apple-converted-space">&nbsp;</span>(npr.</font><span class="Apple-converted-space"><font size="3">&nbsp;</font></span></ins></span><span lang="EN-GB" style="font-style: normal; font-variant: normal; font-weight: normal; letter-spacing: normal; line-height: normal; orphans: auto; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: 1; word-spacing: 0px; -webkit-text-stroke-width: 0px; font-family: Courier New; color: red"><ins datetime="2015-10-27T09:05"><font size="2">gcc</font><font size="2"> 
-</font></ins><font size="2"><ins datetime="2015-10-27T09:06">p</ins></font><ins datetime="2015-10-27T09:05"><font size="2">thread</font><font size="2"> 
prvi.c -o prvi</font></ins></span><span lang="EN-GB" style="font-family: Times New Roman; font-style: normal; font-variant: normal; font-weight: normal; letter-spacing: normal; line-height: normal; orphans: auto; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: 1; word-spacing: 0px; -webkit-text-stroke-width: 0px; color: red"><ins datetime="2015-10-27T09:05"><font size="3">)</font></ins></span><font color="#FF0000">.</font></p>
<p align="JUSTIFY">(U inačici UNIX operacijskog sustava <i>Solaris</i> prilikom prevođenja potrebno je postaviti zastavicu <font face="Courier New" size="2">-D_REENTRANT</font> koja ukazuje na to da se koriste višedretvene inačice upotrijebljenih funkcija, ako takve postoje, te zastavicu -<i>lpthread </i>
, npr. <font face="Courier New" size="2">
gcc -D_REENTRANT -lpthread prvi.c -o prvi</font>.)</p>
<p align="JUSTIFY">Stranice (manual) POSIX dretvi u kojima su detaljno opisane 
funkcije za rad s dretvama <font face="Courier New" size="2"> <i>pthread</i>: 
<a href="http://zemris.fer.hr/predmeti/os/pripreme/upute/pthread/pthread.htm">pthread</a>,
<a href="http://zemris.fer.hr/predmeti/os/pripreme/upute/pthread/pthread_create.htm">pthread_create</a>, 
<a href="http://zemris.fer.hr/predmeti/os/pripreme/upute/pthread/pthread_exit.htm">pthread_exit</a>, 
<a href="http://zemris.fer.hr/predmeti/os/pripreme/upute/pthread/pthread_detach.htm">pthread_detach</a>, 
<a href="http://zemris.fer.hr/predmeti/os/pripreme/upute/pthread/pthread_join.htm">pthread_join</a>, 
<a href="http://zemris.fer.hr/predmeti/os/pripreme/upute/pthread/pthread_mutex_init.htm">pthread_mutex_init</a>, 
<a href="http://zemris.fer.hr/predmeti/os/pripreme/upute/pthread/pthread_mutex_lock.htm">pthread_mutex_lock</a>, 
<a href="http://zemris.fer.hr/predmeti/os/pripreme/upute/pthread/pthread_mutex_unlock.htm">pthread_mutex_unlock</a>, 
<a href="http://zemris.fer.hr/predmeti/os/pripreme/upute/pthread/pthread_mutex_destroy.htm">pthread_mutex_destroy</a>, 
<a href="http://zemris.fer.hr/predmeti/os/pripreme/upute/pthread/pthread_cond_init.htm">pthread_cond_init</a>, 
<a href="http://zemris.fer.hr/predmeti/os/pripreme/upute/pthread/pthread_cond_wait.htm">pthread_cond_wait</a>, 
<a href="http://zemris.fer.hr/predmeti/os/pripreme/upute/pthread/pthread_cond_signal.htm">pthread_cond_signal</a>, 
<a href="http://zemris.fer.hr/predmeti/os/pripreme/upute/pthread/sem_init.htm">sem_init</a>, <a href="http://zemris.fer.hr/predmeti/os/pripreme/upute/pthread/sem_wait.htm">sem_wait</a>,
<a href="http://zemris.fer.hr/predmeti/os/pripreme/upute/pthread/sem_post.htm">sem_post</a>, <a href="http://zemris.fer.hr/predmeti/os/pripreme/upute/pthread/sem_destroy.htm">sem_destroy</a>...</font></p>

<hr>
<p style="tab-stops:36.0pt"><u><b>Win32</b></u></p>
<p style="tab-stops:36.0pt">Stvaranje procesa pod Win32 obavlja se funkcijom
<a href="http://msdn.microsoft.com/library/default.asp?url=/library/en-us/dllproc/base/createprocess.asp">
CreateProcess</a>(). <a href="http://zemris.fer.hr/predmeti/os/pripreme/upute/misc/winprocesi.c">Primjer.</a></p>
<p style="tab-stops:36.0pt">Zajednička memorija ostvaruje se pomoću funkcija
<a href="http://msdn2.microsoft.com/en-us/library/aa366537.aspx">CreateFileMapping</a> i
<a href="http://msdn2.microsoft.com/en-us/library/aa366761.aspx">MapViewOfFile</a>. <a href="http://zemris.fer.hr/predmeti/os/pripreme/upute/misc/Unix2Win.htm#Windows_example:_shared_memory">
Primjer</a></p>
<p style="tab-stops:36.0pt">Stvaranje dretvi pod Win32 obavlja se funkcijom
<a href="http://msdn.microsoft.com/library/default.asp?url=/library/en-us/dllproc/base/createthread.asp">
CreateThread</a>(). <a href="http://zemris.fer.hr/predmeti/os/pripreme/upute/misc/windretve.c">Primjer.</a></p>

<h2><b>Dekkerov postupak međusobnog isključivanja</b></h2><p>Uz pomoć Dekkerovog 
algoritma moguće je sinkronizirati dvije dretve ili dva procesa koji primjerice 
izgledaju ovako:</p>

<pre><u>proces</u> proc(<b>i</b>){&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; /* <b>i</b>&nbsp; [0,1] */
   ponavljaj{
   &nbsp;&nbsp; <b>uđi u kritični odsječak</b>
      K.O.;
    &nbsp; <b>izađi iz kritičnog odsječka
</b>      N.K.O.;
   }dok je zadovoljen(uvjet);
}</pre>
<h3><b>Dekkerov algoritam:</b></h3>

<pre><u>zajedničke varijable</u>: PRAVO, ZASTAVICA[0..1]
&nbsp;<o:p></o:p>
<u>funkcija</u> uđi_u_kritični_odsječak(i,j)
{
   ZASTAVICA[i] = 1
  &nbsp;<u>dok je</u> ZASTAVICA[j]&lt;&gt;0 <u>čini</u> {
      <u>ako je</u> PRAVO==j <u>onda</u> {
         ZASTAVICA[i] = 0
         <u>dok je</u> PRAVO==j <u>čini</u> {
            <u>ništa</u>
         }
         ZASTAVICA[i] = 1
      }
   }
}
&nbsp;
<u>funkcija</u> izađi_iz_kritičnog_odsječka(i,j)
{
   PRAVO = j
   ZASTAVICA[i] = 0
}</pre>
<p style=""><b>Dodatne upute:</b></p>
<p><font color="#FF0000">Ako se program rješava s procesima tada treba zajedničke varijable tako organizirati da se prostor za njih zauzme odjednom i podijeli među njima. Ovo je nužno zbog ograničenog broja segmenata i velikog broja korisnika.</font></p><p>Ovisno o opterećenju računala i broju procesa koji se pokreću, a da bi se vidjele razlike prilikom izvođenja programa može 
se usporiti izvršavanje programa sa:</p>

<pre>sleep(1);</pre><p>na kraju kritičnog odsječka (K.O.).</p>

<p><b><a href="http://zemris.fer.hr/predmeti/os/pripreme/z2_Lamport.html#Problem">Problemi zbog izvođenja instrukcija 
"preko reda"</a></b></p>

<h2>Lamportov<b> postupak međusobnog isključivanja</b></h2><p>Uz pomoć 
Lamportovog algoritma moguće je sinkronizirati dvije ili više dretvi, odnosno 
dva ili više procesa koji primjerice mogu izgledaju ovako:</p>

<pre><u>proces</u> proc(<b>i</b>){&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; /* <b>i</b>&nbsp; [0..n] */
   ponavljaj{
   &nbsp;&nbsp; <b>uđi u kritični odsječak;</b>
      K.O.;
    &nbsp; <b>izađi iz kritičnog odsječka;
</b>      N.K.O.;
   }dok je zadovoljen(uvjet);
}</pre>
<h3>Lamportov<b> algoritam:</b></h3>

<pre style="margin: 0cm 0cm 0.0001pt; font-size: 10pt; font-family: Courier New;"><u>zajedničke varijable</u>: ULAZ[0..<b>n</b>-1], BROJ[0..<b>n</b>-1]</pre>
<pre><u>funkcija</u> uđi_u_kritični_odsječak(i)
{
&nbsp;&nbsp; ULAZ[<b>i</b>] = 1;
&nbsp;&nbsp; BROJ[<b>i</b>] = <b>max</b>(BROJ[0],...,BROJ[<b>n</b>-1]) + 1;
&nbsp;&nbsp; ULAZ[<b>i</b>] = 0;

&nbsp;&nbsp; <u>za</u> <b>j</b> = 0 <u>do</u> <b>n</b>-1 <u>čini</u>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; <u>dok je</u> ULAZ[<b>j</b>] &lt;&gt; 0 <u>čini</u>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; <u>ništa;</u>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; <u>dok je</u> BROJ[j] &lt;&gt; 0 &amp;&amp; (BROJ[j] &lt; BROJ[i] || (BROJ[j] == BROJ[i] &amp;&amp; j &lt; i)) <u>čini</u>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; <u>ništa;
</u>}
&nbsp;
<u>funkcija</u> izađi_iz_kritičnog_odsječka(i)
{
   BROJ[<b>i</b>] = 0;
}</pre>
<p style=""><b>Dodatne upute:</b></p>
<p><font color="#FF0000">Ako se program rješava s procesima tada treba zajedničke varijable tako organizirati da se prostor za njih zauzme odjednom i podijeli među njima. Ovo je nužno zbog ograničenog broja segmenata i velikog broja korisnika.</font></p>

<p>Ovisno o opterećenju računala i broju procesa koji se pokreću, a da bi se vidjele razlike prilikom izvođenja programa može 
se usporiti izvršavanje programa sa:</p>

<pre>sleep(1);</pre><p>na kraju kritičnog odsječka (K.O.).</p>

<p><b><a name="Problem"></a>Problemi zbog izvođenja instrukcija "preko reda"</b></p>
<p>Za ispravan rad Dekkerovog, Petersonovog i Lamportovog algoritma 
pretpostavlja se da se instrukcije programa izvode zadanim redoslijedom. Međutim, 
neki procesori, kako bi ubrzali izvođenje programa, dozvoljavaju izvođenje 
instrukcija i "preko reda" (engl. <i>out-of-order</i>). Takvo ponašanje može 
uzrokovati greške u algoritmu međusobnog isključivanja.</p>
<p>Primjerice, prilikom izvođenja Lampotovog algoritma može se dogoditi da se 
sljedeći niz instrukcija ne izvodi zadanim redoslijedom.</p>
<pre>1:   ULAZ[i] = 1;
2:   BROJ[i] = max(BROJ[0],...,BROJ[n-1]) + 1;
3:   ULAZ[i] = 0;</pre>
<p>Procesor koji omogućuje izvođenje instrukcija "preko reda" bi nakon prve 
linije koda mogao ustanoviti da su instrukcije u drugoj i trećoj liniji 
međusobno nezavisne i mogao bi ih izvesti proizvoljnim redosljedom, npr. liniju 
3 prije linije 2 (razlog za to može biti&nbsp; da se element
<font face="Courier New">ULAZ[i]</font> nalazi u priručnom spremniku, a
<font face="Courier New">BROJ[i]</font> ne). U tom se slučaju ne radi više o 
Lamportovom algoritmu.</p>
<p>Kako bi se izbjeglo proizvoljno izvođenje instrukcija može se jezičnom 
procesoru naznačiti da je pristup spornim varijablama točno određen programskim 
kodom na način da se varijabla proglasi tipom podataka <font face="Courier New">
atomic</font>:</p>
<p><font face="Courier New">#include <span lang="en-us">&lt;</span>stdatomic.h<span lang="en-us">&gt;<br>
atomic_int ULAZ[N], BROJ[N];</span></font></p>
<p>&nbsp;</p>
<pre>&nbsp;</pre>

<h2>Nedjeljiva operacija <i>Ispitaj i postavi (TAS)</i></h2>
<p>Programski prevoditelj gcc pruža mogućnost izvođenja
<a href="https://gcc.gnu.org/onlinedocs/gcc/_005f_005fatomic-Builtins.html">
nedjeljivih (atomic) funkcija</a>.<br>
Jedna od takvih funkcija je <i>Ispitaj i postavi (engl. Test And Set, TAS)</i>:</p>
<p><font face="Courier New" size="2">bool&nbsp;<b>__atomic_test_and_set</b>&nbsp;(void *ptr, int memorder);</font></p>
<p>koja služi za sinkronizaciju kritičnih odsječaka. <br>
Za poziv navedene funkcije nije potrebno uključiniti nikakvu dodatnu biblioteku, 
već je dovoljno na početku programa definirati makro funkciju. <br>
Primjerice, ako makro funkciju nazovemo <i>TAS</i>, tada će definicija te 
funkcije glasiti ovako:</p>
<pre>#define TAS(ZASTAVICA) __atomic_test_and_set (&amp;ZASTAVICA, __ATOMIC_SEQ_CST)</pre>
<p>Potom se navedena makro funkcija koristi u programu primjerice ovako:</p>
<pre>char zastavica = 0; //globalna varijabla ili zajednička kod procesa </pre>
<pre>while ( TAS(zastavica) != 0 )   &nbsp;; // radno čekanje </pre>
