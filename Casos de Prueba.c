#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct usuario {
	char nombreCompleto[50];
	char email[40];
	char contrasena[100];
	char contrasena2[100];
	int edad;
};


int validarNombreCompleto(struct usuario *);
int validarEmail(char *email);
int validarContrasena(struct usuario *);
int compararContrasena(struct usuario *);

void test_validarNombreCompleto();
void test_validarEmail();
void test_validarContrasena();
void test_compararContrasena();

int main() {
	
	test_validarNombreCompleto();
	test_validarEmail();
	test_validarContrasena();
	test_compararContrasena();
	
	return 0; 
}



int validarNombreCompleto(struct usuario *usuarios) {
	int i = 0;      
	int contador = 0;
	
	if (strlen(usuarios->nombreCompleto) <= 3) {
		return 0; 
	} else if (strlen(usuarios->nombreCompleto) >= 50) {
		return 0; 
	}
	
	for (i = 0; usuarios->nombreCompleto[i] != '\0'; i++) {
		if (usuarios->nombreCompleto[i] == ' ') {
			contador++;
		}
	}
	
	if (contador == 0) {
		return 0; 
	}
	
	for (i = 0; usuarios->nombreCompleto[i] != '\0'; i++) {
		if (!(isalpha(usuarios->nombreCompleto[i]) || isspace(usuarios->nombreCompleto[i]))) {
			return 0;
		}
	}
	return 1; 
}

int validarEmail(char *email) {
	int i = 0, arroba = 0, punto = 0; //1
	int posicionArroba = -1, posicionPunto = -1;
	
	while (email[i] != '\0') {//2
		char c = email[i];//3
		
		
		if (!(isalpha(c) || isdigit(c) || c == '@' 
			  || c == '.' )) { // 4-5-6-7
			
			return 0;//8
		}
		
		if (c == '@') {//9
			if (arroba == 0) {//10
				arroba = 1;//11
				posicionArroba = i;
			} else {//12
				
				return 0;//13
			}
		}
		
		if (c == '.') {//14
			if (arroba && punto == 0) {//15-16
				punto = 1;//17
				posicionPunto = i;
			}
		}
		
		i++;//18
	}
	
	if (!arroba || !punto || posicionArroba == 0 ||
		posicionPunto < posicionArroba + 4) {//19-20-21-22
		
		
		return 0;//23
	}
	
	int longitudDominio = posicionPunto - posicionArroba - 1;//24
	int longitudExtension = i - posicionPunto - 1;
	
	if (longitudDominio < 3 || longitudExtension < 2 || 
		longitudExtension > 3) {//25-26-27
		
		
		return 0;//28
	}
	return 1;//29
}

int validarContrasena(struct usuario *usuarios) {
	int i = 0;
	int tieneMayus = 0;
	int tieneMinus = 0; //1
	int tieneNum = 0;
	int tieneEspecial = 0;
	
	if (strlen(usuarios->contrasena) < 8) {//2
		//printf("contrasena invalida: debe tener al menos 8 caracteres.\n");
		//3
		return 0;
	}
	
	for (i = 0; usuarios->contrasena[i] != '\0'; i++) {//4-5-6
		if (isupper(usuarios->contrasena[i])) {//7
			tieneMayus = 1;//8
		} else if (islower(usuarios->contrasena[i])) {//9
			tieneMinus = 1;//10
		} else if (isdigit(usuarios->contrasena[i])) {//11
			tieneNum = 1;//12
		} else if (isspace(usuarios->contrasena[i])) {//13
			//printf("contrasena invalida: no puede contener espacios.\n");
			//14
			return 0;
		} else {//15
			tieneEspecial = 1;//16
		}
	}
	
	if (!tieneMayus || !tieneMinus || !tieneNum || !tieneEspecial) {//17-18-19-20
		//printf("contrasena invalida: debe contener al menos una mayuscula, una "
		//	   "minuscula, un numero y un caracter especial.\n");
		//21
		return 0;
	}
	
	return 1;//22
}

int compararContrasena(struct usuario *usuarios) {
	if (strcmp(usuarios->contrasena, usuarios->contrasena2) != 0) {//1
		return 0;//2
	}
	return 1;//3
}

void test_validarNombreCompleto() {
	struct usuario testUser;
	
	strcpy(testUser.nombreCompleto, "Ju");
	printf("Test 1 - Nombre invalido (menor a 3 caracteres): ");
	if (!validarNombreCompleto(&testUser)) {
		printf("Exitoso (esperado)\n");
	} else {
		printf("Fallido\n");
	}
	
	strcpy(testUser.nombreCompleto, "Juan Carlos Pedro De La Mar De Las Buenas Bibras Paz");
	printf("Test 2 - Nombre invalido (mayor a 50 caracteres): ");
	if (!validarNombreCompleto(&testUser)) {
		printf("Exitoso (esperado)\n");
	} else {
		printf("Fallido\n");
	}
	
	strcpy(testUser.nombreCompleto, "JuanPerez");
	printf("Test 3 - Nombre invalido (longitud valida pero sin espacios): ");
	if (!validarNombreCompleto(&testUser)) {
		printf("Exitoso (esperado)\n");
	} else {
		printf("Fallido\n");
	}
	
	strcpy(testUser.nombreCompleto, "Ana");
	printf("Test 4 - Nombre invalido (Nombre exacto de 3 caracteres): ");
	if (!validarNombreCompleto(&testUser)) {
		printf("Exitoso (esperado)\n");
	} else {
		printf("Fallido\n");
	}
	
	strcpy(testUser.nombreCompleto, "Juan Carlos Pedro De La Mar De Las Buenas Bibras Paz");
	printf("Test 5 - Nombre invalido (Nombre exacto con 50 caracteres): ");
	if (!validarNombreCompleto(&testUser)) {
		printf("Exitoso (esperado)\n");
	} else {
		printf("Fallido\n");
	}
	
	strcpy(testUser.nombreCompleto, "Juan2 Perez");
	printf("Test 6 - Nombre invalido (contiene numero): ");
	if (!validarNombreCompleto(&testUser)) {
		printf("Exitoso (esperado)\n");
	} else {
		printf("Fallido\n");
	}
	
	strcpy(testUser.nombreCompleto, "Juan@Perez");
	printf("Test 7 - Nombre invalido (contiene caracter especial): ");
	if (!validarNombreCompleto(&testUser)) {
		printf("Exitoso (esperado)\n");
	} else {
		printf("Fallido\n");
	}
	
	strcpy(testUser.nombreCompleto, " ");
	printf("Test 8 - Nombre invalido (solo espacios): ");
	if (!validarNombreCompleto(&testUser)) {
		printf("Exitoso (esperado)\n");
	} else {
		printf("Fallido\n");
	}
	
	strcpy(testUser.nombreCompleto, "Juan Perez");
	printf("Test 9 - Nombre valido: ");
	if (validarNombreCompleto(&testUser)) {
		printf("Exitoso (esperado)\n");
	} else {
		printf("Fallido\n");
	}
}


void test_validarEmail() {
	printf("Test 10 - Email invalido (numeros en el dominio): ");
	if (validarEmail("nombre@domi21o.com") == 1) {
		printf("Exitoso\n");
	} else {
		printf("Fallido\n");
	}
	printf("Test 11 - Email invalido (caracter especial no permitido): ");
	if (validarEmail("usuario%&$@dominio.com") == 0) {
		printf("Exitoso (esperado)\n");
	} else {
		printf("Fallido\n");
	}
	
	printf("Test 12 - Email invalido (mas de un @): ");
	if (validarEmail("usuario@dominio@otro.com") == 0) {
		printf("Exitoso (esperado)\n");
	} else {
		printf("Fallido\n");
	}
	
	printf("Test 13 - Email invalido (punto antes del @): ");
	if (validarEmail("usuario.dominio@com") == 0) {
		printf("Exitoso (esperado)\n");
	} else {
		printf("Fallido\n");
	}
	
	printf("Test 14 - Email invalido (arroba al inicio): ");
	if (validarEmail("@dominio.com") == 0) {
		printf("Exitoso (esperado)\n");
	} else {
		printf("Fallido\n");
	}
	
	printf("Test 15 - Email invalido (falta punto despues del @): ");
	if (validarEmail("usuario@dominiocom") == 0) {
		printf("Exitoso (esperado)\n");
	} else {
		printf("Fallido\n");
	}
	
	printf("Test 16 - Email invalido (dominio menor a 3 letras): ");
	if (validarEmail("usuario@ab.com") == 0) {
		printf("Exitoso (esperado)\n");
	} else {
		printf("Fallido\n");
	}
	
	printf("Test 17 - Email invalido (extension menor a 2 letras): ");
	if (validarEmail("usuario@dominio.c") == 0) {
		printf("Exitoso (esperado)\n");
	} else {
		printf("Fallido\n");
	}
	
	printf("Test 18 - Email invalido (extension mayor a 3 letras): ");
	if (validarEmail("usuario@dominio.comm") == 0) {
		printf("Exitoso (esperado)\n");
	} else {
		printf("Fallido\n");
	}
	
	printf("Test 19 - Email invalido (termina en punto): ");
	if (validarEmail("usuario@dominio.") == 0) {
		printf("Exitoso (esperado)\n");
	} else {
		printf("Fallido\n");
	}
	
	printf("Test 20 - Email invalido (sin dominio entre @ y .): ");
	if (validarEmail("usuario@.com") == 0) {
		printf("Exitoso (esperado)\n");
	} else {
		printf("Fallido\n");
	}
	
	printf("Test 21 - Email invalido (caracter especial en dominio): ");
	if (validarEmail("usuario@g#s.com") == 0) {
		printf("Exitoso (esperado)\n");
	} else {
		printf("Fallido\n");
	}
	
	printf("Test 22 - Email invalido (caracter especial en extension): ");
	if (validarEmail("usuario@dominio.c%m") == 0) {
		printf("Exitoso (esperado)\n");
	} else {
		printf("Fallido\n");
	}
	
	printf("Test 23 - Email valido (extension de 3 letras): ");
	if (validarEmail("usuario@dominio.org") == 1) {
		printf("Exitoso\n");
	} else {
		printf("Fallido\n");
	}
	
	printf("Test 24 - Email valido (extension de 2 letras): ");
	if (validarEmail("usuario@dominio.ar") == 1) {
		printf("Exitoso\n");
	} else {
		printf("Fallido\n");
	}
	
	printf("Test 25 - Email invalido (todo valido pero doble punto): ");
	if (validarEmail("usuario@dominio..com") == 0) {
		printf("Exitoso (esperado)\n");
	} else {
		printf("Fallido\n");
	}
}

void test_validarContrasena() {
	struct usuario testUser;
	
	
	strcpy(testUser.contrasena, "?aB567!");
	printf("Test 26 - contrasena invalida (menos de 8 caracteres): ");
	if (validarContrasena(&testUser) == 0) {
		printf("Exitoso (esperado)\n");
	} else {
		printf("Fallido\n");
	}
	
	
	strcpy(testUser.contrasena, "1234567 8!");
	printf("Test 27 - contrasena invalida (contiene espacios): ");
	if (validarContrasena(&testUser) == 0) {
		printf("Exitoso (esperado)\n");
	} else {
		printf("Fallido\n");
	}
	
	
	strcpy(testUser.contrasena, "cesar123?!");
	printf("Test 28 - contrasena invalida (sin mayuscula): ");
	if (validarContrasena(&testUser) == 0) {
		printf("Exitoso (esperado)\n");
	} else {
		printf("Fallido\n");
	}
	
	
	strcpy(testUser.contrasena, "CESAR123?");
	printf("Test 29 - contrasena invalida (sin minuscula): ");
	if (validarContrasena(&testUser) == 0) {
		printf("Exitoso (esperado)\n");
	} else {
		printf("Fallido\n");
	}
	
	
	strcpy(testUser.contrasena, "CesarCesar?!");
	printf("Test 30 - contrasena invalida (sin numero): ");
	if (validarContrasena(&testUser) == 0) {
		printf("Exitoso (esperado)\n");
	} else {
		printf("Fallido\n");
	}
	
	
	strcpy(testUser.contrasena, "Cesar21esar");
	printf("Test 31 - contrasena invalida (sin caracter especial): ");
	if (validarContrasena(&testUser) == 0) {
		printf("Exitoso (esperado)\n");
	} else {
		printf("Fallido\n");
	}
	
	strcpy(testUser.contrasena, "CesarCesar");
	printf("Test 32 - contrasena invalida (contiene solo letras): ");
	if (validarContrasena(&testUser) == 0) {
		printf("Exitoso (esperado)\n");
	} else {
		printf("Fallido\n");
	}
	
	strcpy(testUser.contrasena, "124?!?1r");
	printf("Test 33 - contrasena invalida (contiene solo caracteres y numeros): ");
	if (validarContrasena(&testUser) == 0) {
		printf("Exitoso (esperado)\n");
	} else {
		printf("Fallido\n");
	}
	
	strcpy(testUser.contrasena, "12345678");
	printf("Test 34 - contrasena invalida (contiene solo numeros): ");
	if (validarContrasena(&testUser) == 0) {
		printf("Exitoso (esperado)\n");
	} else {
		printf("Fallido\n");
	}
	
	strcpy(testUser.contrasena, "?!%&&##%#");
	printf("Test 35 - contrasena invalida (contiene solo caracteres especiales): ");
	if (validarContrasena(&testUser) == 0) {
		printf("Exitoso (esperado)\n");
	} else {
		printf("Fallido\n");
	}
	
	strcpy(testUser.contrasena, "CESAR12345");
	printf("Test 36 - contrasena invalida (contiene solo mayusculas y numeros): ");
	if (validarContrasena(&testUser) == 0) {
		printf("Exitoso (esperado)\n");
	} else {
		printf("Fallido\n");
	}
	
	
	strcpy(testUser.contrasena, "Cesar?4545!");
	printf("Test 37 - contrasena valida: ");
	if (validarContrasena(&testUser) == 1) {
		printf("Exitoso\n");
	} else {
		printf("Fallido\n");
	}
}

void test_compararContrasena() {
	struct usuario testUser;
	
	strcpy(testUser.contrasena, "Cesar45s?!");
	strcpy(testUser.contrasena2, "Cesar45s?!");
	printf("Test 38 - contrasenas validas: ");
	if (compararContrasena(&testUser) == 1) {
		printf("Exitoso\n");
	} else {
		printf("Fallido\n");
	}
	
	strcpy(testUser.contrasena2, "Cesar5858!");
	printf("Test 39 - contrasenas no coinciden: ");
	if (compararContrasena(&testUser) == 0) {
		printf("Exitoso (esperado)\n");
	} else {
		printf("Fallido\n");
	}
}
