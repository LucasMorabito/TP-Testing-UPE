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

void registrarUsuario(struct usuario *);
int validarNombreCompleto(struct usuario *);
int validarEmail(char *email);
int validarContrasena(struct usuario *);
int compararContrasena(struct usuario *);
void creacionCuenta();
void iniciarSesionUsuario();

int main() {
	int opcion = 0;
	struct usuario usuarios;
	
	do {
		printf("\nIngrese una opcion: \n");
		printf("Recuerde: Al Seleccionar 1 opcion tiene 3 intentos\nSi se equivoca 3 veces se reiniciara el registro\n");
		printf("1. Registrarse\n");
		printf("2. Iniciar sesion\n");
		printf("0. Salir\n");
		printf("Opcion seleccionada: ");
		fflush(stdin);
		scanf("%d", &opcion);
		
		switch (opcion) {
		case 1:
			registrarUsuario(&usuarios);
			break;
		case 2:
			iniciarSesionUsuario();
			break;
		case 0:
			printf("Saliendo del programa...\n");
			break;
		default:
			printf("Opcion invalida. Ingrese otra opcion.\n");
		}
	} while (opcion != 0);
	
	return 0;
}

void registrarUsuario(struct usuario *usuarios) {
	int repetirRegistro;
    int erroresTemp = 0;
    int validacionExitosa = 0;
	int totalErrores = 0;
	int registroCompleto = 0;

	do {
		printf("Registro del usuario\n");
		
		totalErrores = 0;
		registroCompleto = 0;
		
		while (totalErrores < 3 && !registroCompleto) {
			
			while (!validacionExitosa && totalErrores < 3) {
				printf("Ingrese su nombre y apellido\n");
				scanf(" %[^\n]", usuarios->nombreCompleto);
				erroresTemp = 0;
				if (validarNombreCompleto(usuarios) && erroresTemp == 0) {
					validacionExitosa = 1;
				} else {
					totalErrores++;
				}
			}
			
			if (totalErrores >= 3) {
				registroCompleto = 0;
			} else {
				validacionExitosa = 0;
				while (!validacionExitosa && totalErrores < 3) {
					printf("Ingrese su edad\n");
					scanf("%d", &usuarios->edad);
					if (usuarios->edad < 18) {
						printf("El usuario es menor de edad. Ingrese nuevamente.\n");
						totalErrores++;
					} else if (usuarios->edad > 80) {
						printf("El usuario es mayor a 80 años. Supera la edad maxima. Ingrese nuevamente.\n");
						totalErrores++;
					} else {
						validacionExitosa = 1;
					}
				}
				
				if (totalErrores >= 3) {
					registroCompleto = 0;
				} else {
					validacionExitosa = 0;
					while (!validacionExitosa && totalErrores < 3) {
						printf("Ingrese su email\n");
						scanf(" %[^\n]", usuarios->email);
						erroresTemp = 0;
						if (validarEmail(usuarios->email) && erroresTemp == 0) {
							validacionExitosa = 1;
						} else {
							printf("Email no valido. Ingrese un email valido (ej: nombre@dominio.com)\n");
							totalErrores++;
						}
					}
					
					if (totalErrores >= 3) {
						registroCompleto = 0;
					} else {
						validacionExitosa = 0;
						while (!validacionExitosa && totalErrores < 3) {
							printf("Ingrese su contrasena\n");
							scanf(" %[^\n]", usuarios->contrasena);
							erroresTemp = 0;
							if (validarContrasena(usuarios) && erroresTemp == 0) {
								validacionExitosa = 1;
							} else {
								totalErrores++;
							}
						}
						
						if (totalErrores >= 3) {
							registroCompleto = 0;
						} else {
							validacionExitosa = 0;
							while (!validacionExitosa && totalErrores < 3) {
								printf("Ingrese nuevamente su contrasena\n");
								scanf(" %[^\n]", usuarios->contrasena2);
								erroresTemp = 0;
								if (compararContrasena(usuarios) && erroresTemp == 0) {
									validacionExitosa = 1;
									printf("\nRegistro completado exitosamente con %d errores.\n", totalErrores);
									registroCompleto = 1;
								} else {
									printf("Las contrasenas no coinciden. Ingrese nuevamente.\n");
									totalErrores++;
								}
							}
						}
					}
				}
			}
		}
		
		
		if (totalErrores >= 3) {
			printf("\nDemasiados errores (%d). El registro volvera a comenzar.\n\n", totalErrores);
			repetirRegistro = 1;
		} else {
			repetirRegistro = 0;
		}
		
	} while (repetirRegistro);
	
	creacionCuenta();
}

int validarNombreCompleto(struct usuario *usuarios) {
	int i = 0;      //1
	int contador = 0;
	
	if (strlen(usuarios->nombreCompleto) <= 3) { //2
		printf("Nombre invalido. Ingrese minimo 3 caracteres.\n"); //3
		return 0; //3
	} else if (strlen(usuarios->nombreCompleto) >= 50) { //4
		printf("Nombre invalido. Ingrese menos de 50 caracteres.\n");//5
		return 0;//5
	}
	
	for (i = 0; usuarios->nombreCompleto[i] != '\0'; i++) {//6 - 7 - 8
		if (usuarios->nombreCompleto[i] == ' ') { //9
			contador++;//10
		}
	}
	
	if (contador == 0) { //11
		printf("Nombre invalido. Ingrese minimo un espacio.\n");//12
		return 0;//12
	}
	
	for (i = 0; usuarios->nombreCompleto[i] != '\0'; i++) {//13 - 14 - 15
		if (!(isalpha(usuarios->nombreCompleto[i]) || isspace(usuarios->nombreCompleto[i]))) { //16 - 17
			printf("Nombre invalido. Ingrese solo letras.\n");//18
			//18
			return 0;//18
		}
	}
	return 1; //19
}

int validarEmail(char *email) {
	int i = 0, arroba = 0, punto = 0; //1
	int posicionArroba = -1, posicionPunto = -1;
    char c = 0;
	
	while (email[i] != '\0') {//2
		c = email[i];//3
		
		
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
		printf("contrasena invalida: debe tener al menos 8 caracteres.\n");
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
			printf("contrasena invalida: no puede contener espacios.\n");
			//14
			return 0;
		} else {//15
			tieneEspecial = 1;//16
		}
	}
	
	if (!tieneMayus || !tieneMinus || !tieneNum || !tieneEspecial) {//17-18-19-20
		printf("contrasena invalida: debe contener al menos una mayuscula, una "
			   "minuscula, un numero y un caracter especial.\n");
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

void creacionCuenta() {
	int opcion;
	
	printf("Elija un tipo de cuenta\n");
	printf("1. Cuenta corriente\n");
	printf("2. Caja de ahorro\n");
	scanf("%d", &opcion);
	
	switch (opcion) {
	case 1:
		printf("Se creo la cuenta corriente correctamente\n");
		break;
	case 2:
		printf("Se creo la caja de ahorro correctamente\n");
		break;
	default:
		printf("Opcion invalida. Ingrese una opcion correctamente.\n");
	}
}

void iniciarSesionUsuario() {
	printf("sesion iniciada correctamente\n");
}