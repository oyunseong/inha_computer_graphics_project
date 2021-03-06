#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <vector>

#include <GL/glut.h>
#include <GL/GL.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_stdinc.h>
#include "bmpfuncs.h"

#define CURRENT_WIDTH 1500
#define CURRENT_HEIGHT 800
#define OBJNUMBER 20
#define VERTEXNUM 20000
#define DIST 50
#define MOVEMENT_SPEED 2
#define MOVE_COORDINATE 8
#define RADIAN_TRANSF M_PI/180
#define TARGET_X 0
#define TARGET_Y 5.7
#define TARGET_Z 100

#define SHOOT_SOUND "Sound/sound.wav"
#define WALK_SOUND "Sound/walk.wav"
#define BACKGROUND_SOUND "Sound/background.wav"
#define RELOAD_SOUND "Sound/reload.wav"
#define NOTBULLET_SOUND "Sound/notbullet.wav"
#define SWAP_SOUND "Sound/swap.wav"

/* texture_cube_map */
#define GL_NORMAL_MAP				0x8511
#define GL_REFLECTION_MAP			0x8512
#define GL_TEXTURE_CUBE_MAP			0x8513
#define GL_TEXTURE_BINDING_CUBE_MAP		0x8514
#define GL_TEXTURE_CUBE_MAP_POSITIVE_X		0x8515
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_X		0x8516
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Y		0x8517
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y		0x8518
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Z		0x8519
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z		0x851A
#define GL_PROXY_TEXTURE_CUBE_MAP		0x851B
#define GL_MAX_CUBE_MAP_TEXTURE_SIZE		0x851C

/*
 * OpenGL 1.2
 */
#define GL_CLAMP_TO_EDGE			0x812F
#define GL_TEXTURE_WRAP_R			0x8072

using namespace std;

bool student_number_on = false;
bool prev_rotate_m = false;
bool rotate_m = false;
bool upper_rotate_on = false;
bool upper_rotate_off = false;
bool upper_rotate_r_on = false;
bool upper_rotate_r_off = false;
bool upper_upper_bottom_trans_on = false;
bool upper_upper_bottom_trans_off = false;
bool shoot = false;
bool hit = false;
bool hittrans = false;
bool bullettrans = false;
bool bulletcover = false;
bool handleon = false;
bool handleoff = false;
bool shoulderon = false;
bool shoulderoff = false;
bool caseon = false;
bool caseoff = false;
bool shouldertrans_1 = false;
bool shouldertrans_2 = false;
bool casebutton = false;
bool game_mode = false;
bool walk_mode = false;
bool left_state = false;
bool right_state = false;
bool tartget_hit = false;
bool blending = false;
bool warning = false;
bool background_sound = false;

float R_Angle = 0;
float Prev_R_Angle = 0;
float U_Angle = 0;
float UR_Angle = 0;
float UI_Trans = 0;
float CA_Trans = 0;
float HA_Trans = 0;
float H_Angle = 0;
float S_Angle = 0;
float H_Trans = 0;
float B_Trans = 0;
float B_Angle = 0;
float BC_Trans_1 = 3;
float BC_Trans_2 = -1;
float BC_Angle = 0;
float S_Trans = 0;
float C_Trans = 0;
float T_Trans_X = 0;
float T_Trans_Z = 0;
float T_Rotate = 0;
float temp = 0.0;

double preViewX = 0.0;
double preViewY = 0.0;
double preViewZ = 0.0;
double viewX = 0.0;
double viewY = 0.0;
double viewZ = 0.0;
double preAimX = 0.0;
double preAimY = 0.0;
double preAimZ = 0.0;
double aimX = 0;
double aimY = 5.7;
double aimZ = -8;
double targetX = 0.0;
double targetY = 6.5;
double aimzoneZ = 18.5;
double theta = 0.0;
double radianpi = 0.0;
double diffX = 0.0;
double diffY = 0.0;
double mouse_rotationX = 0.0;
double mouse_rotationY = 0.0;
double angleUnit = 2 * (M_PI / 180);
double mouse_sensitivity = 1.0;
double disdif = 0.0;
double hitx_dif = 0.0;


/*
0. ???? ???? ??
1. ???? ???? ??
2. ???? ??
3. ?????? ???? ????
4. ???? ?????? 
5. ??????
6. ????
7. ???????? ???? ????
8. ??????
9. ????
10. ?????? ?????? ???????? ????
11. ??????
12. ????
13. ???? ???? ???? ( ???? )
14. ????
15. ????
16. ???????? ???? ??????
17. ?????? ????
18. ?????? ?? (18 - 17 ????)
19. ?????? ?? ????
*/


char filename0[255] = "modeling/cover_left.obj";	
char filename1[255] = "modeling/cover_right.obj";
char filename2[255] = "modeling/K1.obj";
char filename3[255] = "modeling/case_button_right.obj";
char filename4[255] = "modeling/inner_bottom_handle.obj";
char filename5[255] = "modeling/bullet_case.obj";
char filename6[255] = "modeling/under.obj";
char filename7[255] = "modeling/shoulder.obj";
char filename8[255] = "modeling/inner_top.obj";
char filename9[255] = "modeling/inner_bottom.obj";
char filename10[255] = "modeling/under_hit.obj";
char filename11[255] = "modeling/under_trigger.obj";
char filename12[255] = "modeling/inner_bullet_inner.obj";
char filename13[255] = "modeling/inner_bullet_outter.obj";
char filename14[255] = "modeling/inner_bullet_inner.obj";
char filename15[255] = "modeling/inner_bullet_outter.obj";
char filename16[255] = "modeling/shoulder_bar.obj";
char filename17[255] = "modeling/under_handle.obj";
char filename18[255] = "modeling/under_1.obj";
char filename19[255] = "modeling/case_bullet.obj";

int bullet_count = 30;
int total_bullet = 90;
int a_nX, a_nY;
int g_nX, g_nY;
int bullet_unit = 30;
int score = 0;

int f_num[OBJNUMBER];
int object_number = 0;

int f1[OBJNUMBER][VERTEXNUM];
int f2[OBJNUMBER][VERTEXNUM];
int f3[OBJNUMBER][VERTEXNUM];
int f4[OBJNUMBER][VERTEXNUM];

float nvx[OBJNUMBER][VERTEXNUM];
float nvy[OBJNUMBER][VERTEXNUM];
float nvz[OBJNUMBER][VERTEXNUM];
float vx[OBJNUMBER][VERTEXNUM];
float vy[OBJNUMBER][VERTEXNUM];
float vz[OBJNUMBER][VERTEXNUM];

GLuint texName[10];

GLuint skyboxTex;
//The music that will be played
Mix_Chunk* sBack = NULL;

//The sound effects that will be used
Mix_Chunk* gGun = NULL;
Mix_Chunk* sWalk = NULL;
Mix_Chunk* sReload = NULL;
Mix_Chunk* sSwap = NULL;
Mix_Chunk* sNotbullet = NULL;

Mix_Chunk* gHigh = NULL;
Mix_Chunk* gMedium = NULL;
Mix_Chunk* gLow = NULL;

void init(void);
void idle(void);
void resize(int width, int height);
void camera_eye(void);
void draw(void);
void draw_string(void* font, const char* str, float x_position, float y_position, float red, float green, float blue);
void draw_skybox(float size);
void file_load(void);
void keyboard(unsigned char key, int x, int y);
void specialkey(int key, int x, int y);
void mouse(int button, int state, int x, int y);
void motion(int x, int y);
void passivemotion(int x, int y);
void obj_file_load(char* fname);
void draw_obj(void);
void mappingTexture(void);

int main(int argc, char* argv[]) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(CURRENT_WIDTH, CURRENT_HEIGHT);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("12171804_oys");
	init();
	std::cout << "Mini SuddenAttack Game!!"<<endl;
	std::cout << "???? : W A S D"<<endl;
	std::cout << "number 1: ???? ???? ???? "<<endl;
	std::cout << "number 2: ???? "<<endl;
	std::cout << "number 3: ???????? ???? ???? "<<endl;
	std::cout << "number 4: ?????? ???? "<<endl;
	std::cout << "number 5: ?????????? "<<endl;
	std::cout << "number r: ???? "<<endl;
	std::cout << "number I/o: ???? ?????? "<<endl;
	std::cout << "number [,]: ?????? ???? "<<endl;
	std::cout << "???????? selection???? ?????? : ???? ???? "<<endl;
	std::cout << "?????? ?????? : Game Mode"<<endl;
	std::cout << "Game Mode R : ????"<<endl;
	std::cout << "Game Mode M : ???????? on"<<endl;
	std::cout << "Game Mode n : ???????? off"<<endl;

	glutReshapeFunc(resize);
	glutDisplayFunc(draw);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialkey);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutPassiveMotionFunc(passivemotion);
	glutIdleFunc(idle);

	glutMainLoop();

	return 0;
}


void init(void) {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClearDepth(1.0f);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glFrontFace(GL_CCW);
	glEnable(GL_LIGHTING);

	GLfloat ambientLight[] = { 0.25f, 0.25f, 0.25f, 1.0f };
	GLfloat diffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat light_position[] = { 10, 0, 0, 1.0f };
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHT0);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);

	glMateriali(GL_FRONT, GL_SHININESS, 64);

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	file_load();

	camera_eye();

	mappingTexture();

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	//Load WAV
	gGun = Mix_LoadWAV(SHOOT_SOUND);
	sWalk = Mix_LoadWAV(WALK_SOUND);
	sBack = Mix_LoadWAV(BACKGROUND_SOUND);
	sNotbullet = Mix_LoadWAV(NOTBULLET_SOUND);
	sReload = Mix_LoadWAV(RELOAD_SOUND);
	sSwap = Mix_LoadWAV(SWAP_SOUND);

	glLoadIdentity();
}

void mappingTexture(void) {
	glEnable(GL_TEXTURE_2D);

	// ?? ????
	glGenTextures(5, texName);
	glBindTexture(GL_TEXTURE_2D, texName[0]);
	SDL_Surface* image = IMG_Load("Texture/metal2.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, texName[1]);
	image = IMG_Load("Texture/gun1.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	/* ?????? */
	glBindTexture(GL_TEXTURE_2D, texName[2]);
	image = IMG_Load("Texture/target_face.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	/* ???? */
	glBindTexture(GL_TEXTURE_2D, texName[3]);
	image = IMG_Load("Texture/metal5.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	/* ?????? */
	glBindTexture(GL_TEXTURE_2D, texName[4]);
	image = IMG_Load("Texture/metal6.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// ?? 
	glGenTextures(1, &skyboxTex);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTex);
	SDL_Surface* img0 = IMG_Load("Texture/forward1.bmp");	// ??????
	SDL_Surface* img1 = IMG_Load("Texture/forward1.bmp");	// ????
	SDL_Surface* img2 = IMG_Load("Texture/forward1.bmp");	// ??
	SDL_Surface* img3 = IMG_Load("Texture/ground.bmp");	// ????
	SDL_Surface* img4 = IMG_Load("Texture/forward1.bmp");	// ??
	SDL_Surface* img5 = IMG_Load("Texture/forward1.bmp");	// ??

	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, img0->w, img0->h, 0, GL_RGB, GL_UNSIGNED_BYTE, img0->pixels);	// ??????
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, img1->w, img1->h, 0, GL_RGB, GL_UNSIGNED_BYTE, img1->pixels);	// ????
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, img2->w, img2->h, 0, GL_RGB, GL_UNSIGNED_BYTE, img2->pixels);	// ??
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, img3->w, img3->h, 0, GL_RGB, GL_UNSIGNED_BYTE, img3->pixels);	// ????
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, img4->w, img4->h, 0, GL_RGB, GL_UNSIGNED_BYTE, img4->pixels);	// ??
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, img5->w, img5->h, 0, GL_RGB, GL_UNSIGNED_BYTE, img5->pixels);	// ??

	glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTex);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void file_load(void) {
	obj_file_load(filename0);
	obj_file_load(filename1);
	obj_file_load(filename2);
	obj_file_load(filename3);
	obj_file_load(filename4);
	obj_file_load(filename5);
	obj_file_load(filename6);
	obj_file_load(filename7);
	obj_file_load(filename8);
	obj_file_load(filename9);
	obj_file_load(filename10);
	obj_file_load(filename11);
	obj_file_load(filename12);
	obj_file_load(filename13);
	obj_file_load(filename14);
	obj_file_load(filename15);
	obj_file_load(filename16);
	obj_file_load(filename17);
	obj_file_load(filename18);
	obj_file_load(filename19);
}

void resize(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (float)width / (float)height, 1, 500);
	glMatrixMode(GL_MODELVIEW);
}

void idle(void) {
	if (rotate_m) {
		R_Angle += 0.5;
		if (R_Angle > 360) R_Angle -= 360;
	}

	if (upper_rotate_on) {
		if (U_Angle <= 60) U_Angle += 0.5;
		else {
			upper_rotate_r_on = false;
		}
	}
	if (upper_rotate_off) {
		if (U_Angle > 0) U_Angle -= 0.5;
		else {
			upper_rotate_off = false;
		}
	}

	if (upper_rotate_r_on) {
		if (UR_Angle >= -60) UR_Angle -= 0.5;
		else {
			upper_upper_bottom_trans_on = true;
			casebutton = true;
			shoulderon = true;
			caseon = true;
		}
	}
	if (upper_rotate_r_off) {
		if (UR_Angle < 0) UR_Angle += 0.5;
		else {
			upper_rotate_off = true;
			upper_rotate_r_off = false;
		}
	}

	if (upper_upper_bottom_trans_on) {
		if (UI_Trans >= -5) UI_Trans -= 0.17f;
		else {
			handleon = true;
		}
	}

	if (shoulderon) {
		if (S_Trans >= -7) S_Trans -= 0.17f;
	}
	if (shoulderoff) {
		if (S_Trans < 0) S_Trans += 0.17f;
		else shoulderoff = false;
	}

	if (upper_upper_bottom_trans_off) {
		if (UI_Trans < -5) UI_Trans += 0.17f;
		else {
			handleoff = true;
			upper_upper_bottom_trans_off = false;
			casebutton = false;
			shoulderoff = true;
			caseoff = true;
		}
	}

	if (handleon) {
		if (HA_Trans >= -3) HA_Trans -= 0.17f;
		else {
			if (UI_Trans >= -13) UI_Trans -= 0.17f;
		}
	}
	if (handleoff) {
		if (HA_Trans < 0) HA_Trans += 0.17f;
		else {
			if (UI_Trans < 0) UI_Trans += 0.17f;
			else {
				upper_rotate_r_off = true;
				handleoff = false;
			}
		}
	}

	if (caseon) {
		if (CA_Trans >= -4) CA_Trans -= 0.17f;
	}
	if (caseoff) {
		if (CA_Trans < 0) CA_Trans += 0.17f;
		else caseoff = false;
	}

	// ?????? ???? 
	if (hit) {
		if (H_Angle <= 90) H_Angle += 4;
		else {
			Mix_PlayChannel(-1, gGun, 0);
			hit = false;
			hittrans = true;
			bullettrans = true;
		}
	}
	else {
		if (H_Angle > 0) H_Angle -= 4;
	}


	if (shoot) {
		// number key 2?? 
		if (S_Angle <= 25) S_Angle += 1;
		else {
			shoot = false;
			hit = true;
		}
	}
	else {
		if (S_Angle > 0) S_Angle -= 1;
	}

	if (hittrans) {
		if (H_Trans >= -4) {
			H_Trans -= 0.17f;
			BC_Trans_1 -= 0.17f;
		}
		else {
			hittrans = false;
			bulletcover = true;
		}
	}
	else {
		if (H_Trans < 0) {
			H_Trans += 0.17f;
			BC_Trans_2 += 0.17f;
		}
		else {
			BC_Trans_2 = -1;
		}
	}

	if (bullettrans) {
		if (B_Trans <= 200) B_Trans += 3.5;
		else {
			B_Trans = 0;
			BC_Trans_1 = 3;
			bullettrans = false;
		}
	}

	if (bullettrans) {
		if (B_Angle <= 270 && (B_Trans >= 25)) B_Angle += 5;
		else B_Angle = 0;
	}
	else B_Angle = 0;

	if (bulletcover) {
		if (BC_Angle <= 90) BC_Angle += 3;
		else {
			BC_Angle = 0;
			bulletcover = false;
		}
	}

	if (shouldertrans_1) {
		if (S_Trans <= 4) S_Trans += 0.1f;
	}
	else {
		if (shouldertrans_2) {
			if (S_Trans <= 8) S_Trans += 0.1f;
		}
		else {
			if (S_Trans > 0) S_Trans -= 0.1f;
		}
	}

	if (casebutton) {
		if (C_Trans >= -4) C_Trans -= 0.1f;
	}
	else {
		if (C_Trans < 0) C_Trans += 0.1f;
	}

	if (tartget_hit) {
		if (T_Rotate >= -90) { 
			T_Rotate -= 10; 
		}
		else { 
			tartget_hit = false; 
		}
	}
	else {
		if (T_Rotate < 0) T_Rotate += 3;
	}
	glutPostRedisplay();
}

// ?????? ???? 
void camera_eye() {
	if (theta > 2 * M_PI) theta -= 2 * M_PI;
	if (theta <= 0) theta += 2 * M_PI;
	if (radianpi > 2 * M_PI) radianpi -= 2 * M_PI;
	if (radianpi <= 0) radianpi += 2 * M_PI;
	viewX = (DIST + disdif) * cos(theta) * cos(radianpi);	//DIST = 50
	viewY = (DIST + disdif) * sin(theta);
	viewZ = (DIST + disdif) * cos(theta) * sin(radianpi);
	std::cout << "viewX, viewY,viewZ : " << "(" << viewX << ", " << viewY << ", " << viewZ << ")" << endl;
}

// 
void draw(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	char str[20];
	char scoreStr[20];
	sprintf(str, "Bullet : %d/%d", bullet_count, total_bullet);
	if (game_mode) {
		draw_string(GLUT_BITMAP_TIMES_ROMAN_24, str, 2, 4, 1.0f, 0.0f, 0.0f);
	}

	sprintf(scoreStr, "score : %d", score);
	if (game_mode)
	{
		draw_string(GLUT_BITMAP_TIMES_ROMAN_24, scoreStr, 3, 4, 0.0f, 0.0f, 1.0f);
	}

	if (warning) draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "Hurry up and reload it!", -0.7f, 3.0f, 1.0f, 0.0f, 0.0f);

	if ((0 <= theta && theta < M_PI / 2) || (3 * M_PI / 2 < theta && theta <= 2 * M_PI)) {
		if (game_mode) {
			gluLookAt(viewX, viewY, viewZ, aimX + diffX, aimY + diffY, aimZ + 1, 0, 1, 0);
		}
		else {
			gluLookAt(viewX, viewY, viewZ, 0, 0, 0, 0, 1, 0);
		}
	}
	else {
		gluLookAt(viewX, viewY, viewZ, 0, 0, 0, 0, -1, 0);

	}

	if (game_mode) draw_skybox(200);
	//cout << "aim_mode : " << aim_mode << endl;

	// ?????? 
	glPushMatrix();
	GLUquadric* quadric = gluNewQuadric();
	glTranslatef(TARGET_X, -9.3f, TARGET_Z);
	glRotatef(-T_Rotate, 1, 0, 0); // ?????? hits?? ???? 90?? ?????????? ??????
	
	if (game_mode) {
		// ???? ????
		glTranslatef(TARGET_X, 9.3f + TARGET_Y, 0);

		// ????
		glutSolidSphere(10, 50, 10);

		glBegin(GL_POLYGON);
		// ??
		glVertex3f(4, -2, -4);
		glVertex3f(4, -15,-4);
		glVertex3f(4, -15, 4);
		glVertex3f(4, -2, 4);

		// ??
		glVertex3f(-4, -2, -4);
		glVertex3f(-4, -15,-4);
		glVertex3f(-4, -15, 4);
		glVertex3f(-4, -2, 4);

		// ??
		glVertex3f(-4, -2, -4);	
		glVertex3f(-4, -15, -4);	
		glVertex3f(4, -15, -4);	
		glVertex3f(4, -2, -4);	

		// ??
		glVertex3f(-4, -2, 4);
		glVertex3f(-4, -15, 4);
		glVertex3f(4, -15, 4);
		glVertex3f(4, -2, 4);

		glEnd();
	}
	glPopMatrix();

	draw_obj();

	glFlush();
	glutSwapBuffers();
}

void draw_string(void* font, const char* str, float x_position, float y_position, float red, float green, float blue)
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	GLfloat emission[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat emission_off[] = { 0.0, 0.0, 0.0, 1.0 };

	gluOrtho2D(-5, 5, -5, 5);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);

	glColor3f(red, green, blue);
	glRasterPos3f(x_position, y_position, 0);
	for (unsigned int i = 0; i < strlen(str); i++)
		glutBitmapCharacter(font, str[i]);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission_off);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopAttrib();
}

// ?? 
void draw_skybox(float size) {
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_CUBE_MAP);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTex);

	glBegin(GL_QUADS);	//??
	glTexCoord3d(1.0, -1.0, -1.0); glVertex3f(size, -9.3f, -size);
	glTexCoord3d(1.0, -1.0, 1.0); glVertex3f(size, -9.3f, size);
	glTexCoord3d(1.0, 1.0, 1.0); glVertex3f(size, -9.3f + size, size);
	glTexCoord3d(1.0, 1.0, -1.0); glVertex3f(size, -9.3f + size, -size);
	glEnd();

	glBegin(GL_QUADS);	//?? 
	glTexCoord3d(-1.0, -1.0, -1.0); glVertex3f(-size, -9.3f, -size);
	glTexCoord3d(-1.0, -1.0, 1.0); glVertex3f(-size, -9.3f, size);
	glTexCoord3d(-1.0, 1.0, 1.0); glVertex3f(-size, -9.3f + size, size);
	glTexCoord3d(-1.0, 1.0, -1.0); glVertex3f(-size, -9.3f + size, -size);
	glEnd();

	glBegin(GL_QUADS); // ????
	glTexCoord3d(-1.0, 1.0, -1.0); glVertex3f(-size, size - 9.3f, -size);
	glTexCoord3d(-1.0, 1.0, 1.0); glVertex3f(-size, size - 9.3f, size);
	glTexCoord3d(1.0, 1.0, 1.0); glVertex3f(size, size - 9.3f, size);
	glTexCoord3d(1.0, 1.0, -1.0); glVertex3f(size, size - 9.3f, -size);
	glEnd();

	glBegin(GL_QUADS); // ??????
	glTexCoord3d(-1.0, -1.0, -1.0); glVertex3f(-size, -9.3f, -size);
	glTexCoord3d(-1.0, -1.0, 1.0); glVertex3f(-size, -9.3f, size);
	glTexCoord3d(1.0, -1.0, 1.0); glVertex3f(size, -9.3f, size);
	glTexCoord3d(1.0, -1.0, -1.0); glVertex3f(size, -9.3f, -size);
	glEnd();

	glBegin(GL_QUADS);	// ??
	glTexCoord3d(-1.0, -1.0, +1.0); glVertex3f(-size, -9.3f, size);
	glTexCoord3d(-1.0, 1.0, 1.0); glVertex3f(-size, -9.3f + size, size);
	glTexCoord3d(1.0, 1.0, 1.0); glVertex3f(size, -9.3f + size, size);
	glTexCoord3d(1.0, -1.0, 1.0); glVertex3f(size, -9.3f, size);
	glEnd();

	glBegin(GL_QUADS);	// ??
	glTexCoord3d(-1.0, -1.0, -1.0); glVertex3f(-size, -9.3f, -size);
	glTexCoord3d(-1.0, 1.0, -1.0); glVertex3f(-size, -9.3f + size, -size);
	glTexCoord3d(1.0, 1.0, -1.0); glVertex3f(size, -9.3f + size, -size);
	glTexCoord3d(1.0, -1.0, -1.0); glVertex3f(size, -9.4f, -size);
	glEnd();

	glPopAttrib();
}

void keyboard(unsigned char key, int x, int y) {
	printf("%c pressed\n", key);
	switch (key) {
	case '1':
		if (upper_rotate_on) {
			handleon = false;
			shoulderon = false;
			caseon = false;
			upper_rotate_on = false;
			upper_rotate_r_on = false;
			upper_upper_bottom_trans_on = false;
			upper_upper_bottom_trans_off = true;
		}
		else {
			upper_rotate_on = true;
		}
		break;
	case '2':
		if (shoot) {
			shoot = false;
		}
		else {
			shoot = true;
		}
		break;
	case '3':
		if (shouldertrans_1) {
			shouldertrans_2 = true;
			shouldertrans_1 = false;
		}
		else if (shouldertrans_2) {
			shouldertrans_2 = false;
		}
		else {
			shouldertrans_1 = true;
		}
		break;
	case '4':
		if (casebutton) {
			casebutton = false;
		}
		else {
			casebutton = true;
		}
		break;
	case '5':
		if (blending) {
			blending = false;
		}
		else {
			blending = true;
		}
		break;
	case 'R':
	case 'r':
		if (game_mode) {
			if ((total_bullet + bullet_count) >= 30) {
				total_bullet -= (bullet_unit - bullet_count);
				bullet_count = 30;
				Mix_PlayChannel(-1, sReload, 0);
			}
			else if ((total_bullet + bullet_count) > 0) {
				bullet_count = total_bullet + bullet_count;
				total_bullet = 0;
			}
			warning = false;
		}
		else {
			if (rotate_m) {
				rotate_m = false;
			}
			else {
				rotate_m = true;
			}
		}
		break;
	case 'W':
	case 'w':
		if (game_mode) {
			Mix_PlayChannel(-1, sWalk, 0);
			aimZ += MOVEMENT_SPEED;
			viewZ += MOVEMENT_SPEED;
			T_Trans_Z += MOVEMENT_SPEED;
		}
		break;
	case 'S':
	case 's':
		if (game_mode) {
			Mix_PlayChannel(-1, sWalk, 0);
			aimZ -= MOVEMENT_SPEED;
			viewZ -= MOVEMENT_SPEED;
			T_Trans_Z -= MOVEMENT_SPEED;
		}
		break;
	case 'A':
	case 'a':
		if (game_mode) {
			Mix_PlayChannel(-1, sWalk, 0);
			aimX += MOVEMENT_SPEED;
			viewX += MOVEMENT_SPEED;
			T_Trans_X += MOVEMENT_SPEED;
			hitx_dif += MOVE_COORDINATE;
		}
		break;
	case 'D':
	case 'd':
		if (game_mode) {
			Mix_PlayChannel(-1, sWalk, 0);
			aimX -= MOVEMENT_SPEED;
			viewX -= MOVEMENT_SPEED;
			T_Trans_X -= MOVEMENT_SPEED;
			hitx_dif -= MOVE_COORDINATE;
		}
		break;
	case 'I':
		if (!game_mode) {
			disdif -= 1;
			camera_eye();
		}
		break;
	case 'i':
		if (!game_mode) {
			disdif -= 1;
			camera_eye();
		}
		break;
	case 'O':
		if (!game_mode) {
			disdif += 1;
			camera_eye();
		}
		break;
	case 'o':
		if (!game_mode) {
			disdif += 1;
			camera_eye();
		}
		break;
	case ']':
		if (game_mode)
		{
			if(mouse_sensitivity >0) mouse_sensitivity += 1.0f;
		}
		break;
	case '[':
		if (game_mode)
		{
			if (mouse_sensitivity > 0) mouse_sensitivity -= 1.0f;
			else if (mouse_sensitivity == 0) mouse_sensitivity = 1;
		}
		break;
	case 'm':
		if (game_mode) {
			background_sound = true;
			Mix_PlayChannel(-1, sBack, 0);
		}
		break;
	case 'n':
		background_sound = false;
		Mix_FreeChunk(sBack);
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void specialkey(int key, int x, int y) {
	if (key == 100) {
		printf("?? pressed\n");
	}
	else if (key == 101)
	{
		printf("?? pressed\n");
	}
	else if (key == 101) {
		printf("?? pressed\n");
	}
	else if (key == 102) {
		printf("?? pressed\n");
	}
	else if (key == 103) {
		printf("?? pressed\n");
	}
	printf("%d pressed\n", key);
	if (!game_mode) {
		switch (key) {
		case GLUT_KEY_LEFT:
			radianpi += angleUnit;
			break;
		case GLUT_KEY_RIGHT:
			radianpi -= angleUnit;
			break;
		case GLUT_KEY_UP:
			theta += angleUnit;
			break;
		case GLUT_KEY_DOWN:
			theta -= angleUnit;
			break;
		default:
			break;
		}
		camera_eye();
	}
	glutPostRedisplay();
}

int xp= -8;
int xm =8;
void mouse(int button, int state, int x, int y) {
	y = CURRENT_HEIGHT - y;
	// ???? ?????? ?? 
	if (game_mode) {
		// ?????? ?? 
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			if (bullet_count > 0) {
				Mix_PlayChannel(-1, gGun, 0);	// ???? ????
				double hitx = (targetX + (26.512) * diffX - viewX) * (TARGET_Z - viewZ) / (aimzoneZ - viewZ) + viewX;
				double hity = (targetY + (26.512) * diffY - viewY) * (TARGET_Z - viewZ) / (aimzoneZ - viewZ) + viewY;
				if ((targetX + diffX) - viewX != 0) {
					if (-4 < (hitx + hitx_dif) && (hitx + hitx_dif) < 4) {
						tartget_hit = true;
						score++;
					}
				}
				// ???? ?? 
				else if ((targetY + diffY) - viewY != 0) {
					if (xp <= hity && hity <= xm) tartget_hit = true;
				}
				bullet_count--;	// ???? -1 
				if (bullet_count == 0) { 
					warning = true; 
					Mix_PlayChannel(-1, sNotbullet, 0);
				}
				else warning = false;
			}
		}
		// ?????????? ?? ?? ?????????? ????
		else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
			game_mode = false;
			aimX = preAimX;
			aimY = preAimY;
			aimZ = preAimZ;
			viewX = preViewX;
			viewY = preViewY;
			viewZ = preViewZ;
			T_Trans_X = 0;
			T_Trans_Z = 0;
			hitx_dif = 0;
			R_Angle = Prev_R_Angle;
			score = 0;
			if (prev_rotate_m) rotate_m = true;
		}
	}
	// ???????? 
	else {
		// ?????? ?? 
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			g_nX = x;
			g_nY = y;
			left_state = true;
		}
		// ?????? ?? ??
		else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
			left_state = false;
		}
		else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
			game_mode = true;
			Mix_PlayChannel(-1, sSwap, 0);
			preViewX = viewX;
			preViewY = viewY;
			preViewZ = viewZ;
			viewX = aimX;
			viewY = aimY;
			viewZ = aimZ;
			preAimX = aimX;
			preAimY = aimY;
			preAimZ = aimZ;
			Prev_R_Angle = R_Angle;
			total_bullet = 90;
			bullet_count = 30;
			R_Angle = 0;
			if (rotate_m) {
				rotate_m = false;
				prev_rotate_m = true;
			}
			a_nX = x;
			a_nY = y;
		}
	}
	glutPostRedisplay();
}

void motion(int x, int y) {
	y = CURRENT_HEIGHT - y;
	// ???????? 
	if (game_mode == false && left_state) {
		radianpi += (x - g_nX) * RADIAN_TRANSF;
		theta -= (y - g_nY) * RADIAN_TRANSF;
		g_nX = x;
		g_nY = y;
		camera_eye();
	}
	glutPostRedisplay();
}

/* https://jvm-gaming.org/t/calculating-theta-of-what/41412 */
// ?????? ???? 
void passivemotion(int x, int y) {
	y = CURRENT_HEIGHT - y;
	//???????? 
	if (game_mode) {
		mouse_rotationX = -((x - a_nX) / 25.0f) * mouse_sensitivity;
		mouse_rotationY = -((y - a_nY) / 25.0f) * mouse_sensitivity;
		// ?????? ?????? ???? ???? ???? 
		diffX = tan(mouse_rotationX * RADIAN_TRANSF);
		diffY = tan(-mouse_rotationY * RADIAN_TRANSF);
	}
	glutPostRedisplay();
}


/* ???? ???? : http://www.opengl-tutorial.org/kr/beginners-tutorials/tutorial-7-model-loading/ */
void obj_file_load(char* fname) {
	FILE* fp;
	float x;
	float y;
	float z;
	int i, j, k;
	i = 0; j = 0; k = 0;

	// ???? ???? ???? ?? 
	fp = fopen(fname, "r");
	if (!fp) {
		printf("Impossible to open the file %s\n", fname);
		exit(1);
	}
	while (!(feof(fp))) {
		char lineHeader[128];
		fscanf(fp, "%s", lineHeader);	// ?????? ?????? ?????? ????????.
		if (strcmp(lineHeader, "v") == 0) {
			i++;
			fscanf(fp, "%f", &x);
			fscanf(fp, "%f", &y);
			fscanf(fp, "%f", &z);
			vx[object_number][i] = x;
			vy[object_number][i] = y;
			vz[object_number][i] = z;
			
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			j++;
			fscanf(fp, "%f", &x);
			fscanf(fp, "%f", &y);
			fscanf(fp, "%f", &z);
			nvx[object_number][j] = x;
			nvy[object_number][j] = y;
			nvz[object_number][j] = z;
			
		}
		else if (strcmp(lineHeader, "f") == 0) {
			int a, b;
			k++;
			fscanf(fp, "%d//%d", &a, &b);
			f1[object_number][k] = a;
			fscanf(fp, "%d//%d", &a, &b);
			f2[object_number][k] = a;
			fscanf(fp, "%d//%d", &a, &b);
			f3[object_number][k] = a;
			f4[object_number][k] = b;
			
		}
	}
	f_num[object_number] = k;
	object_number++;
}

/*
0. ???? ???? ??
1. ???? ???? ??
2. ???? ??
3. ?????? ???? ????
4. ???? ??????
5. ??????
6. ????
7. ???????? ???? ????
8. ??????
9. ????
10. ?????? ?????? ???????? ????
11. ??????
12. ????
13. ???? ???? ???? ( ???? )
14. ????
15. ????
16. ???????? ???? ??????
17. ?????? ????
18. ?????? ?? (18 - 17 ????)
19. ?????? ?? ????
*/

// ???????? ???? draw
void draw_obj() {
	glRotatef(R_Angle, 0, 1, 0);
	for (int object = 0; object < object_number; object++) {
		glPushMatrix();
		if (game_mode) {
			glTranslatef(T_Trans_X, 0, T_Trans_Z);
			glTranslatef(viewX - T_Trans_X-5 , viewY, viewZ - T_Trans_Z+3);	// 1???? ?? ???? ????
			glRotatef(mouse_rotationY, 1, 0, 0);
			glRotatef(mouse_rotationX, 0, 1, 0);
			glTranslatef(-viewX + T_Trans_X, -viewY, -viewZ + T_Trans_Z);	// ?? ????
		}
		else {
			// ????????
			if (object == 7 || object == 16) {
				glTranslatef(0, 0, S_Trans);
			}
			// ??????
			if (object == 11) {
				glTranslatef(0, 0.8, -1.7);
				glRotatef(S_Angle, 0, 0, 0);
				glTranslatef(0, -0.8, 1.7);
			}
			// ?????? ????
			if (object == 10) {
				glTranslatef(0, 0.8, 0);
				glRotatef(H_Angle, 0, 0, 0);
				glTranslatef(0, -0.8, 0);
			}
			// ???? ?????? ????
			if (object == 4 || object == 9) {
				glTranslatef(0, 0, H_Trans);
			}
			// ??????, ?????? ?? ????
			if (object == 5 || object == 19) {
				glTranslatef(0, C_Trans, 0);
			}
			if (blending) {
				// ????????, ???? ??, ??????
				if (object == 0 || object == 1 || object == 2 || object == 8 || object == 5 || object == 6 || object == 7 || object == 16 || object == 17 || object ==  18) {
					// ?????? ???? ??????
					glEnable(GL_BLEND);
					glDisable(GL_DEPTH_TEST);
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	// ?????? ????
					glColor4f(1.0f, 1.0f, 1.0f, 0.1f);
				}
				else {
					glDisable(GL_BLEND);
					glEnable(GL_DEPTH_TEST);
				}
			}
			else {
				// ?????? ???? ???? 
				glEnable(GL_DEPTH_TEST);
				glDisable(GL_BLEND);
			}
			if (object == 0 || object == 1 || object == 2 || object == 4 || object == 8 || object == 9 || object == 12 || object == 13 || object == 14 || object == 15) {
				glTranslatef(0, 3, 4.6);
				glRotatef(U_Angle, 1, 0, 0);
				glTranslatef(0, -3, -4.6);
				glRotatef(UR_Angle, 1, 0, 0);
				if (object == 0) {
					glTranslatef(-CA_Trans, 0, 0);
				}
				if (object == 1) {
					glTranslatef(CA_Trans, 0, 0);
				}
				if (object == 8 || object == 9) {
					glTranslatef(0, 0, UI_Trans);
				}
				if (object == 4) {
					if (UI_Trans >= -5) {
						temp = UI_Trans;
					}
					glTranslatef(0, 0, temp);
					glTranslatef(HA_Trans, 0, 0);
				}
				if (object == 12) {
					glTranslatef(0, 0, BC_Trans_1 + B_Trans);
					if (sin(B_Angle * RADIAN_TRANSF) < 0) {
						glTranslatef(0, 6 * sin(B_Angle * RADIAN_TRANSF), 0);
					}
					else { // ???? ????
						glTranslatef(0, sin(B_Angle * RADIAN_TRANSF), 0);
					}
				}
				if (object == 13) {
					glTranslatef(0, 0, BC_Trans_1);
					glTranslatef(0, -5, 0);
					glRotatef(BC_Angle, 0, 0, 1);
					glTranslatef(0, 5, 0);
				}
				if (object == 14 || object == 15) {
					if (!hittrans && BC_Trans_1 < 4) {
						glTranslatef(0, 0, BC_Trans_2);
					}
					else {
						glPopMatrix();
						continue;
					}
				}
			}
		}
		// ???? ??????, ????
		if (object == 0 || object == 1 || object == 4) {
			glBindTexture(GL_TEXTURE_2D, texName[1]);
		}
		// ?????? ????????
		else if
			(object == 7 || object == 17 || object == 18) {
			glBindTexture(GL_TEXTURE_2D, texName[1]);
		}
		// ????
		else if (object == 12 || object == 13 || object == 14 || object == 15 || object == 19) {
			glBindTexture(GL_TEXTURE_2D, texName[3]); 
		}
		else if (object == 5)
		{
			glBindTexture(GL_TEXTURE_2D, texName[4]);
		}
		else {
			glBindTexture(GL_TEXTURE_2D, texName[0]);
		}
		glBegin(GL_TRIANGLES);
		for (int n = 0; n < f_num[object]; n++) {
			glNormal3f(nvx[object][f4[object][n]], nvy[object][f4[object][n]], nvz[object][f4[object][n]]);
			glTexCoord2f(0, 0);
			glVertex3f(vx[object][f1[object][n]], vy[object][f1[object][n]], vz[object][f1[object][n]]);

			glNormal3f(nvx[object][f4[object][n]], nvy[object][f4[object][n]], nvz[object][f4[object][n]]);
			glTexCoord2f(0, 1);
			glVertex3f(vx[object][f2[object][n]], vy[object][f2[object][n]], vz[object][f2[object][n]]);

			glNormal3f(nvx[object][f4[object][n]], nvy[object][f4[object][n]], nvz[object][f4[object][n]]);
			glTexCoord2f(0.5, 0.5);
			glVertex3f(vx[object][f3[object][n]], vy[object][f3[object][n]], vz[object][f3[object][n]]);
		}
		glEnd();
		glPopMatrix();
	}
}
