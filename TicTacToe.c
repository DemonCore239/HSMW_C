#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*****************************************************
  Dateiname: TicTacToe.c
  Beschreibung: Dieses Programm implementiert das Spiel
  Drei-Gewinnt. Neben einem Spielfeld, wird auch die 
  Spiellogik implementiert. 
  
  Achtung: Unbedingter Suchfaktor!!! 
 *****************************************************/


// Fuegen Sie hier die globalen Datenfelder und Variablen ein.
// ...

#define LEER '-'
int size = 10;
char feld[1];

// Fuegen Sie bitte an dieser Stelle die Funktionsdeklaration der
// drei Unterprogramme ein. Achtung! Noch kein Funktionskörper 
// lediglich die Schnittstelle der Funktion ist anzugeben 
// ...

void ausgeben (int spielzug){
    int n = 0;
    printf("\n");
    for (int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            printf("[%c]",feld[n]);
            n++;
        }
        printf("\n");
    }
    
}
int gewonnen (int spielzug){
bool bol_ret[2*size+2];
int int_n = 0;
int int_m = 0;

    for (int i=0; i<size; i++) {
        bol_ret[int_m] = (LEER != feld[int_n]);
        bol_ret[int_m+size] = (LEER != feld[i]);
        for (int j=0; j<size-1; j++) {
            bol_ret[int_m] = bol_ret[int_m] * (feld[int_n+i+j-1]==feld[int_n+i+j]);
            bol_ret[int_m+size] = bol_ret[int_m+size] * (feld[i+j*size]==feld[i+(j+1)*size]);
        }
        int_n = int_n + size;
        int_m++;
        
    }
    
    bol_ret[2*size] = (LEER != feld[0]);
    bol_ret[2*size+1] = (LEER != feld[size-1]);

    for (int i=0; i<size-1; i++){
        bol_ret[2*size] = bol_ret[2*size] * (feld[i * (size+1)]==feld[(i + 1) * (size + 1)]);
        bol_ret[2*size+1] = bol_ret[2*size+1] * (feld[(i+1) * (size-1)]==feld[(i + 2) * (size-1)]);
    }
    
    int int_size = sizeof bol_ret / sizeof bol_ret[0];
    
    for (int k=0; k<int_size; k++)
        if (bol_ret[k])
            return true;
    
    return false;
}


void resetSpielfeld(){
    for (int i=0; i<size*size; i++)
        feld[i] = LEER;
}



/* Hauptroutine */
int main(void){

    char beenden;
    int  eingabe = -1;
    int  zugcomputer = -1;
    int  ende = 0;
    int  spielzug = 0;
 
    resetSpielfeld();
    
	printf("\n");
	printf("Willkommen! Sie möchten gern eine Runde Tic-Tac-Toe spielen ? \n");
	printf("Dann geht es jetzt los! \n");			
	printf("\n");
	printf("Ihr Zeichen lautet  \"X\". Das Zeichen des Computers lautet \"O\".\n");
		
 
	do
	{
		// Spielplan am Anfang genau einmal ausgeben (leeres Spielfeld)
	    ausgeben(spielzug);		
			
	
		while (!ende)
		{	
			 
		    
			printf("\nWählen Sie ein Feld aus. Geben Sie eine Zahl zwischen 1 und %i ein:\n", size*size);
			
				
			// Eingabe des Nutzers entgegen nehmen
		  	do{
				scanf("%i",&eingabe);
				// eingabe ist eine Zahl zwischen 1 und 9
				// für das Feld benötigen wir aber einen Wert zwischen 0 .. 8 - Arrayindex
				eingabe--; 
			
			}while ((eingabe < 1 && eingabe > 9) || feld[eingabe]!=LEER);	
			
						
				
			// Nächster Spielzug hat begonnen
			spielzug++;
			
			// Status des Spielplans anpassen und Feld markieren
			feld[eingabe] = 'X'; 		
			// Zeige den Zwischenstand an, nachdem der Spieler seinen
			// Zug beende hat
			ausgeben(spielzug);		
			
	 			
			// Prüfen ob Spiel damit beendet/gewonnen ist und gegebenenfalls abbrechen	
			ende = gewonnen(spielzug);
			
			if (ende) 
				puts("Das Ende ist nah");
			
			if (!ende) 
			{				
				// Zug des Computers
				// Hier kommt die unschlagbare Strategie des Computergegners. Er rät eine
				// Zahl zwischen 0 und 8. Anschließend wird geprüft, ob dieses Spielfeld 
				// noch unbesetzt ist und mit dem Wert belegt. Sollte das Feld bereits 
				// besetzt sein, dann wird einfach eine neue Zufallszahl bestimmt.
				do {
					// Die Funktion rand() stammt aus der Standard C-Bibliothek <stdlib>
					// Sie liefert einen Wert zwischen 0 und RAND_MAX zurück. Für gewönlich
					// hat die Konstante RAND_MAX den Wert 32767. Mittels Modulo können
					// wir den Ausgabebereich auf 0..8 reduziert.
					zugcomputer = rand() % 9; // liefert eine Zufallszahl zwischen 0 und 8 zurück
				}
				while (feld[zugcomputer]!=LEER);
				
				
				// Status des Spielplans anpassen und Feld markieren
				feld[zugcomputer] = 'O'; 
				
				spielzug++;
				
				ausgeben(spielzug);
				
				ende = gewonnen(spielzug);
			}
			
		} // Ende while-Schleife 

			
	    puts("Spiel beendet!\n");
		puts("Möchten Sie noch einmal spielen (J/N)?");
		
	    fflush(stdin);
		// Achtung!!! zwei getchar() werden hier benoetigt. 
		// Begruendung: Da zuvor ein \n ausgeführt wurde, geht 
		// getchar() sonst über das Einlesen hinweg, ohne beenden 
		// mit einem Wert zu versorgen.
		getchar();
		beenden = getchar();
		printf("Wert von beenden %c",beenden);
		ende = 0;
		spielzug = 0;
		resetSpielfeld();
    }
	while(beenden != 'N' && beenden != 'n'); // Programm verlassen?
 
}

