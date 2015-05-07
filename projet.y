%{
#include "hpdf.h"
#include "hpdf_image.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>	
#define T 1024
	
HPDF_Doc mon_document;
HPDF_Page page[20];
HPDF_Image image;
HPDF_Rect misenpage;
/*Variable pour avoir la position : par defaut (0,0)*/	
HPDF_Point Position;
HPDF_Point CurrentPosition;
HPDF_TextAlignment   align;
HPDF_UINT *len;

int HPDF_i = 0;
int decl = 45;
int Style = 0;

/* Les tilles pas defaut de chaque type de token */
int HPDFTailleTxt = 11, cmp_txt=0;
int HPDFTailleSec = 17, cmp_sec=0;
int HPDFTailleSsec = 13, cmp_ssec=0;
int HPDFTailleTitrEnv = 13, cmp_titenv=0;
int HPDFTailleTxtEnv = 11, cmp_txtenv=0;
int HPDF_mypage = 0;	
int HPDF_EnvTitBol = 0;

int tabmat = 0;
int HPDF_IndicS = 0;
int HPDF_IndicSs = 0;
int HPDF_titres[T];
int HPDF_Ntitre = 0;
int HPDF_NumSs = 0;
char HPDF_Npage[T][T];
int HPDF_CmptePg = 0;
char HPDF_Temp[T];
char HPDF_Temp1[T];
char HPDF_StockS[T][T];
char HPDF_StockSs[T][T];
char HPDF_ConstrEnv[T];
char HPDF_ConstTitrEnt[T];
	 

	
typedef struct HPDFSTRUCT  {
char sec[2]; 	char ssec[2]; 	char numerote[2];
char def[2];	char lem[2];	char note[2];
char page[2];
} HPDFStruct ;

	
HPDFStruct HPDFMyStruct;

	
/* Utiliser une fonction de creation de page pour pouvoir : 
*	- Changer de font une seule fois et pas a chaque fois 
*	- Chnager de direction de la page HPDF_PAGE_PORTRAIT (Normal) ou HPDF_PAGE_LANDSCAPE(Mode paysage)
*	- Chnager de taille de police 
*	- Chnager l'espacement entre caractère une seule fois (a la creationde la page) => SetTextLeading
*/
void HPDF_NouvellePage() {
/*Fermer le texte de la page précédente */
HPDF_Page_EndText (page[HPDF_mypage]);
/*Incrémenter le nombre de page*/
HPDF_mypage++;
/*Ajouter une page au document*/
page[HPDF_mypage] = HPDF_AddPage (mon_document);
if (!page[HPDF_mypage]) {
	printf("Error handler !\n");
}
/*Définir la forme de la page*/
HPDF_Page_SetSize (page[HPDF_mypage], HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
/*Définir l'espacement*/
HPDF_Page_SetTextLeading (page[HPDF_mypage], 22);
/*Définir le style de la page*/
HPDF_Page_SetFontAndSize (page[HPDF_mypage], HPDF_GetFont (mon_document, "Times-Roman", "WinAnsiEncoding") , 11);
/*Récuperer la position*/
Position = HPDF_Page_GetCurrentTextPos(page[HPDF_mypage]);
HPDF_Page_BeginText (page[HPDF_mypage]);
HPDFMyStruct.page[0]++;
HPDF_Page_TextRect (page[HPDF_mypage],  misenpage.left, Position.y + 35, misenpage.right, misenpage.top,HPDFMyStruct.page, HPDF_TALIGN_CENTER, NULL);
HPDF_Page_EndText (page[HPDF_mypage]);
HPDF_Page_BeginText (page[HPDF_mypage]);
}


/*	- La fonction suivante est disponible sur le site officiel de la bibliotheque http://libharu.sourceforge.net 
*	- Création de l'objet image
*	- Chargement de l'image en (png ou jpeg) => Load
*	- Dessiner l'image dans le PDF => Draw
*/

draw_image (HPDF_Doc     pdf,const char  *filename,float x, float y, const char  *text)
{
#ifdef __WIN32__
const char* FILE_SEPARATOR = "\\";
#else
const char* FILE_SEPARATOR = "/";
#endif
char filename1[255];

HPDF_Page page = HPDF_GetCurrentPage (pdf);
HPDF_Image image;

strcpy(filename1, "projet");
strcat(filename1, FILE_SEPARATOR);
strcat(filename1, filename);

image = HPDF_LoadPngImageFromFile (pdf, filename1);

/* Draw image to the canvas. */
HPDF_Page_DrawImage (page, image, x, y, HPDF_Image_GetWidth (image),HPDF_Image_GetHeight (image));

/* Print the text. */
HPDF_Page_BeginText (page);
HPDF_Page_SetTextLeading (page, 16);
HPDF_Page_MoveTextPos (page, x, y);
HPDF_Page_ShowTextNextLine (page, filename);
HPDF_Page_ShowTextNextLine (page, text);
HPDF_Page_EndText (page);
}

%}

%union {
char	        *CHAINE;
}	

%token AUTRES
%token SEC 
%token SSEC
%token ENV
%token ENDENV
%token MATAILLE
%token TABMAT
%token FINLIGNE
%token BLANCS
%token COMMENTAIRE
%token ECHAPPER
%token BOOLEAN
%token STRONG
%token ENTIER
%token IMAGE

%type<CHAINE> ENTIER TABMAT MATAILLE ENDENV ENV SSEC SEC AUTRES

%left AUTRES COMMENTAIRE FINLIGNE  BLANCS ECHAPPER  IMAGE

%%
Entree	: prog
|
; 

prog	: FINLIGNE prog 
|	COMMENTAIRE prog
|	corp  Entree
;

corp	: tabmat corp 
|	taille corp
|	image corp
|	nouvelleLigne corp
|	COMMENTAIRE corp
|	BLANCS corp
|	ligne {	
Position = HPDF_Page_GetCurrentTextPos(page[HPDF_mypage]);
if(Position.y > 1 && Position.y < 100 ){	
HPDF_NouvellePage();
}

											
HPDF_Page_SetFontAndSize (page[HPDF_mypage], HPDF_GetFont (mon_document, "Times-Roman", "WinAnsiEncoding") , HPDFTailleTxt);
Position = HPDF_Page_GetCurrentTextPos(page[HPDF_mypage]);
											
if (Position.y == 0) {
HPDF_Page_TextRect (page[HPDF_mypage],  misenpage.left, misenpage.bottom, misenpage.right, misenpage.top, HPDF_Temp, HPDF_TALIGN_JUSTIFY, NULL);
Position = HPDF_Page_GetCurrentTextPos(page[HPDF_mypage]);
}else {
	if(HPDF_Temp[0] != 0){
	HPDF_Page_TextRect (page[HPDF_mypage],  misenpage.left, Position.y - 18, misenpage.right, misenpage.top,
	HPDF_Temp, HPDF_TALIGN_JUSTIFY, NULL);
}}memset (HPDF_Temp, 0, T);HPDF_i = 0;} corp


|  section	{ 	
Position = HPDF_Page_GetCurrentTextPos(page[HPDF_mypage]);
if(Position.y > 1 && Position.y < 100){	
	HPDF_NouvellePage();
}

												
HPDF_Page_SetFontAndSize (page[HPDF_mypage], HPDF_GetFont (mon_document, "Times-Bold", "WinAnsiEncoding") , HPDFTailleSec);
Position = HPDF_Page_GetCurrentTextPos(page[HPDF_mypage]);	
if (Position.y == 0) {
	HPDF_Page_TextRect (page[HPDF_mypage],  misenpage.left, misenpage.bottom, misenpage.right, misenpage.top,HPDF_Temp, HPDF_TALIGN_LEFT, NULL);
}else {
HPDF_Page_TextRect (page[HPDF_mypage],  misenpage.left, Position.y - 28, misenpage.right, misenpage.top,HPDF_Temp, HPDF_TALIGN_LEFT, NULL);
}
strcpy(HPDF_StockS[HPDF_IndicS], HPDF_Temp);
memset (HPDF_Temp, 0, T);HPDF_IndicS++;HPDF_i = 0;
sprintf(HPDF_Npage[HPDF_CmptePg], "%d", HPDF_mypage);
HPDF_CmptePg++;
} corp

|  ssection { 
Position = HPDF_Page_GetCurrentTextPos(page[HPDF_mypage]);
if(Position.y > 1 && Position.y < 100){	
HPDF_NouvellePage();
}

												
HPDF_Page_SetFontAndSize (page[HPDF_mypage], HPDF_GetFont (mon_document, "Times-Italic", "WinAnsiEncoding") , HPDFTailleSsec);
Position = HPDF_Page_GetCurrentTextPos(page[HPDF_mypage]);
												
if (Position.y == 0) {
HPDF_Page_TextRect (page[HPDF_mypage],  misenpage.left, misenpage.bottom, misenpage.right, misenpage.top,HPDF_Temp, HPDF_TALIGN_LEFT, NULL);
}else {
HPDF_Page_TextRect (page[HPDF_mypage],  misenpage.left, Position.y - 30, misenpage.right, misenpage.top,HPDF_Temp, HPDF_TALIGN_LEFT, NULL);
}
strcpy(HPDF_StockSs[HPDF_IndicSs], HPDF_Temp);
memset (HPDF_Temp, 0, T);
HPDF_IndicSs++;
HPDF_i = 0;

sprintf(HPDF_Npage[HPDF_CmptePg], "%d", HPDF_mypage);
HPDF_CmptePg++;} 	corp
			
|	envir corp
|
;

nouvelleLigne	:	'\n'	{	Position = HPDF_Page_GetCurrentTextPos(page[HPDF_mypage]);
HPDF_Page_SetFontAndSize (page[HPDF_mypage], HPDF_GetFont (mon_document, "Times-Roman", "WinAnsiEncoding") , HPDFTailleSsec);
Position = HPDF_Page_GetCurrentTextPos(page[HPDF_mypage]);
													
HPDF_Page_TextRect (page[HPDF_mypage],  misenpage.left, Position.y - 12, misenpage.right, misenpage.top," ", HPDF_TALIGN_LEFT, NULL);
};
/*Table des matière*/
tabmat	:	TABMAT	'{' ligne  {	  
if(HPDF_Temp=="true") {tabmat = 0; } else { tabmat = 1;}
memset (HPDF_Temp, 0, T);
HPDF_i = 0;
}
;
/*Traitement des taille de chaque token*/
taille		:	MATAILLE { 

if(!(strcmp ($1,"\\taillesec"))) {
	cmp_sec = 1; 
} 	else if (!(strcmp ($1,"\\taillessec"))) {
	cmp_ssec = 1;
} 	else if (!(strcmp ($1,"\\tailletxt"))) {
	cmp_txt = 1;
} else if (!(strcmp ($1,"\\tailleenvi"))) {
	cmp_titenv = 1;
} else if (!(strcmp ($1,"\\tailleenvicont"))) {
	cmp_txtenv = 1;

}
}	'{'  ENTIER   {   int curr= 0; 
if(cmp_sec==1) { 
	sscanf($1,"%d",&curr); 
	HPDFTailleSec = curr; cmp_sec=0;
} 	else if (cmp_ssec==1) {
		sscanf($1,"%d",&curr);
	HPDFTailleSsec = curr; cmp_ssec=0;;
} 		else if (cmp_txt==1) {
sscanf($1,"%d",&curr);
	HPDFTailleTxt = curr; cmp_txt=0;
} else if (cmp_titenv==1) {
sscanf($1,"%d",&curr);
	HPDFTailleTitrEnv = curr; cmp_titenv=0;
} else if (cmp_txtenv==1) {
sscanf($1,"%d",&curr);
	HPDFTailleTxtEnv = curr; cmp_txtenv=0;
} 
 } '}' FINLIGNE   
;

ligne	:	lettre
|	echapper lettre
|	BLANCS lettre
;

lettre	:	debLettre finLettre
|	FINLIGNE
|	'}'
;

debLettre	: AUTRES { /*Récuperer la valuer de la chaine insérer */  HPDF_Temp[HPDF_i] = *$1; HPDF_i++; }
;

finLettre	:	lettre
|	echapper lettre
|	COMMENTAIRE
|	BLANCS {strcat(HPDF_Temp," ");HPDF_i++;} lettre
|
;

section		:	SEC {	
HPDFMyStruct.sec[0]++;						
strcat(HPDF_Temp, HPDFMyStruct.sec);
strcat(HPDF_Temp, ". : ");
HPDF_i = strlen(HPDF_Temp);
} sectionend
;

sectionend	:	'{'	ligne	reste
|	reste
;

ssection	:	SSEC	{	
if(HPDFMyStruct.numerote[0] != HPDFMyStruct.sec[0]){
HPDFMyStruct.ssec[0] = '0';
}
HPDFMyStruct.ssec[0]++;
strcat(HPDF_Temp, HPDFMyStruct.sec);
strcat(HPDF_Temp, ". ");
strcat(HPDF_Temp, HPDFMyStruct.ssec);
strcat(HPDF_Temp, ". : ");
HPDF_i = strlen(HPDF_Temp);
HPDFMyStruct.numerote[0] = HPDFMyStruct.sec[0];
HPDF_Ntitre = atof(HPDFMyStruct.sec);
HPDF_NumSs = atof(HPDFMyStruct.ssec);
HPDF_titres[HPDF_Ntitre] = HPDF_NumSs;
} ssectionend
;

ssectionend	:	'{'	ligne 	reste
|	reste
;

reste	:	FINLIGNE
|	COMMENTAIRE 
;


echapper	:	ECHAPPER {strcat(HPDF_Temp,"%");HPDF_i++;} echapperend
;

echapperend	:	echapper
|
;



envir			:	debutenv	{	
Position = HPDF_Page_GetCurrentTextPos(page[HPDF_mypage]);
if(Position.y > 1 && Position.y < 100){	
HPDF_NouvellePage();
}
								
HPDF_Page_SetFontAndSize (page[HPDF_mypage], HPDF_GetFont (mon_document, "Times-Roman", "WinAnsiEncoding") , HPDFTailleTitrEnv);
Position = HPDF_Page_GetCurrentTextPos(page[HPDF_mypage]);

strcat(HPDF_ConstTitrEnt, HPDF_ConstrEnv);
if(HPDF_EnvTitBol) {
strcat(HPDF_ConstTitrEnt," [");
strcat(HPDF_ConstTitrEnt, HPDF_Temp);
}else {
strcat(HPDF_ConstTitrEnt," :");
strcat(HPDF_ConstTitrEnt, HPDF_Temp);
}
if(HPDF_EnvTitBol) {
strcat(HPDF_ConstTitrEnt,"]***");
}else {
strcat(HPDF_ConstTitrEnt,"***");
}
if (Position.y == 0) {
HPDF_Page_TextRect (page[HPDF_mypage],  misenpage.left, misenpage.bottom, misenpage.right, misenpage.top,HPDF_ConstTitrEnt, HPDF_TALIGN_LEFT, NULL);
}else {

HPDF_Page_TextRect (page[HPDF_mypage],  misenpage.left, Position.y - 20, misenpage.right, misenpage.top,HPDF_ConstTitrEnt, HPDF_TALIGN_LEFT, NULL);

}
memset (HPDF_Temp, 0, T);HPDF_i = 0;
memset (HPDF_ConstTitrEnt, 0, T); memset (HPDF_ConstrEnv, 0, T);
}
txtEnv 	
;
			
debutenv	:	ENV	{	

if(!(strcmp ($1,"\\def"))) {
HPDFMyStruct.def[0]++;
strcat(HPDF_ConstrEnv, "*** Definition ");
strcat(HPDF_ConstrEnv, HPDFMyStruct.def);
}else if(!(strcmp ($1,"\\lem"))) {
HPDFMyStruct.lem[0]++;
strcat(HPDF_ConstrEnv, "*** Lemme ");
strcat(HPDF_ConstrEnv, HPDFMyStruct.lem);
}else if(!(strcmp ($1,"\\note"))) {
HPDFMyStruct.note[0]++;
strcat(HPDF_ConstrEnv, "*** Note ");
strcat(HPDF_ConstrEnv, HPDFMyStruct.note);
}	
} 
findenv
;


findenv	:	'{'	ligne reste2
|	FINLIGNE	{HPDF_EnvTitBol = 0;}
|	COMMENTAIRE	{HPDF_EnvTitBol = 0;}
;

reste2	:	FINLIGNE {HPDF_EnvTitBol = 1;}
|	COMMENTAIRE {HPDF_EnvTitBol = 1;}
;
txtEnv		:	corpenv ENDENV	{	
Position = HPDF_Page_GetCurrentTextPos(page[HPDF_mypage]);
if(Position.y > 1 && Position.y < 100){	
HPDF_NouvellePage();
}
										
HPDF_Page_SetFontAndSize (page[HPDF_mypage], HPDF_GetFont (mon_document, "Times-Roman", "WinAnsiEncoding") , HPDFTailleTitrEnv);
Position = HPDF_Page_GetCurrentTextPos(page[HPDF_mypage]);
if (Position.y == 0) {
HPDF_Page_TextRect (page[HPDF_mypage],  misenpage.left, misenpage.bottom, misenpage.right, misenpage.top,
"*****Fin*****", HPDF_TALIGN_LEFT, NULL);
}else {
HPDF_Page_TextRect (page[HPDF_mypage],  misenpage.left, Position.y - 12, misenpage.right, misenpage.top,"*****Fin*****", HPDF_TALIGN_LEFT, NULL);
}	}
;
 
corpenv	:	ligne	{ 	
Position = HPDF_Page_GetCurrentTextPos(page[HPDF_mypage]);
if(Position.y > 1 && Position.y < 100){	
HPDF_NouvellePage();
}
/*Insertion de tabulation de debut de ligne*/
strcat(HPDF_Temp1,"        ");
strcat(HPDF_Temp1, HPDF_Temp);
/*Définitiondu style pour le texte de l'environnement*/							
HPDF_Page_SetFontAndSize (page[HPDF_mypage], HPDF_GetFont (mon_document, "Times-Roman", "WinAnsiEncoding") , HPDFTailleTxtEnv);
Position = HPDF_Page_GetCurrentTextPos(page[HPDF_mypage]);
if(HPDF_Temp[0] != '\0'){
if (Position.y == 0) {
HPDF_Page_TextRect (page[HPDF_mypage],  misenpage.left, misenpage.bottom, misenpage.right, misenpage.top,
HPDF_Temp1, HPDF_TALIGN_JUSTIFY, NULL);
}else {
HPDF_Page_TextRect (page[HPDF_mypage],  misenpage.left, Position.y - 12, misenpage.right, misenpage.top,HPDF_Temp1, HPDF_TALIGN_JUSTIFY, NULL);
}
memset (HPDF_Temp, 0, T);
memset (HPDF_Temp1, 0, T);
HPDF_i = 0;
}}   finenv
|	COMMENTAIRE	corpenv
;
	
finenv:	FINLIGNE	corpenv
|	corpenv
|
;

image			: IMAGE {
		  
/* Perment de dessiner une image */
draw_image (mon_document, "rouen.png", 400, HPDF_Page_GetHeight (page[HPDF_mypage]) - 350, "Mon univ");
/*Creation de l'objet image */
image = HPDF_LoadPngImageFromFile (mon_document , "rouen.png");
double  iw = HPDF_Image_GetWidth (image);
double  ih = HPDF_Image_GetHeight (image);
double   x = 100;
double   y = HPDF_Page_GetHeight (page[HPDF_mypage]) - 100;
/* Perment de dessiner une image */
HPDF_Page_DrawImage (page[HPDF_mypage], image, x, y,  iw, ih);
}
;

%%
#include "lex.yy.c"


