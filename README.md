# AZA Projekt 1

Počas chatovania na horách sa Jakubko rozhodol, že pôjde na veľkú túru. Presnejšie na čo najväčšiu túru. Pomôžte mu ju naplánovať!

Mapka okolia chaty je matica čísiel C s M riadkami a N stĺpcami. Čísla v jednotlivých bunkách matice symbolizujú nadmorskú výšku prislúchajúcej časti terénu. Túra je definovaná ako postupnosť P buniek matice, pre ktorú platí:

Bunky P_i a P_i+1 sa dotýkajú jednou hranou.
Existuje také k, že P_i-1 <= P_i pre i <= k a P_i-1 >= P i pre i > k Inými slovami, postupnosť hodnôt buniek P je najprv neklesajúca, a potom nerastúca.
Žiadna bunka matice sa v P nevyskytuje viac ako jeden krát.
Vašou úlohou je vypočítať dĺžku najdlhšej túry, ktorá sa dá v teréne prejsť (iba v rámci danej mapky, lebo Jakubko nemôže ísť mimo mapy, aby sa nestratil).

Na prvom riadku vstupu sa nachádza jediné celé číslo T (1 <= T <= 10), označujúce počet rôznych máp, ktoré budú nasledovať. Opis každej mapy je trochu nezvyčajný. Celá matica je charakterizovaná vždy len jedným riadkom vstupu, ktorý obsahuje tri celé čísla S, M a N oddelené jednou medzerou (1 <= S < 65537, 1 <= M, N <= 40). Čísla M a N označujú počet riadkov a stĺpcov matice, S je nultý člen postupnosti A, ktorá po riadkoch vyjadruje hodnoty čísiel v jednotlivých bunkách matice. Maticu teda vytvoríme napríklad takto (začíname prvým členom postupnosti A):


    for i := 1 to M do

      for j := 1 to N do
    
        matica[i,j]:= A((i-1)*N+j);
    
Kde matica[i,j] je bunka v i-tom riadku a j-tom stĺpci. Rekurentná formula A, ktorá je pre všetky vstupy rovnaká, má tvar (mod je zvyšok po delení):

A(0) = S

A(N) = (A(N - 1) * 75) mod 65537
Výstup má obsahovať P riadkov, na každom z nich jediné číslo - dĺžku najdlhšej túry pre danú maticu.

Ukážka vstupu:
1

47 4 4

Výstup pre ukážkový vstup:

10
