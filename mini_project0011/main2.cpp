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

#define CURRENT_WIDTH 500
#define CURRENT_HEIGHT 500
#define OBJNUMBER 20
#define VERTEXNUM 20000
#define DIST 50
#define MOVEMENT_SPEED 2
#define MOVE_COORDINATE 8
#define RADIAN_TRANSF M_PI/180
#define TARGET_X 0
#define TARGET_Y 5.7
#define TARGET_Z 100

#define SHOOT_SOUND "/Sound/sound.wav"

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
double aimzoneX = 0.0;
double aimzoneY = 6.5;
double aimzoneZ = 18.5;
double theta = 0.0;
double radianpi = 0.0;
double difX = 0.0;
double difY = 0.0;
double mouse_rotationX = 0.0;
double mouse_rotationY = 0.0;
double angleUnit = 2 * (M_PI / 180);
double mouse_sensitivity = 1.0;
double disdif = 0.0;
double hitx_dif = 0.0;

char filename0[255] = "modeling/cover_1.obj";
char filename1[255] = "modeling/cover_2.obj";
char filename2[255] = "modeling/K1A.obj";
char filename3[255] = "modeling/case_button.obj";
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

int g_nX, g_nY;
int a_nX, a_nY;
int bullet_unit = 30;
int bullet_count = 30;
int total_bullet = 150;

int f_num[OBJNUMBER];
int object_number = 0;

float vx[OBJNUMBER][VERTEXNUM];
float vy[OBJNUMBER][VERTEXNUM];
float vz[OBJNUMBER][VERTEXNUM];
float nvx[OBJNUMBER][VERTEXNUM];
float nvy[OBJNUMBER][VERTEXNUM];
float nvz[OBJNUMBER][VERTEXNUM];

int f1[OBJNUMBER][VERTEXNUM];
int f2[OBJNUMBER][VERTEXNUM];
int f3[OBJNUMBER][VERTEXNUM];
int f4[OBJNUMBER][VERTEXNUM];

GLuint texName[3];
GLuint skyboxTex;
//The music that will be played
Mix_Music* gMusic = NULL;

//The sound effects that will be used
Mix_Chunk* gGun = NULL;
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
void do_sound(void);
void my_audio_callback(void* userdata, Uint8* stream, int len);
void keyboard(unsigned char key, int x, int y);
void specialkey(int key, int x, int y);
void mouse(int button, int state, int x, int y);
void motion(int x, int y);
void passivemotion(int x, int y);
void obj_file_load(char* fname);
void draw_obj(void);

int main(int argc, char* argv[]) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(CURRENT_WIDTH, CURRENT_HEIGHT);
	glutInitWindowPosition(300, 300);
	glutCreateWindow("Maple_FPS");
	init();

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

	camera_eye();

	glEnable(GL_TEXTURE_2D);
	glGenTextures(3, texName);
	glBindTexture(GL_TEXTURE_2D, texName[0]);

	int imageWidth, imageHeight, channels;
	//uchar* image2 = readImageData("Texture/CIDER_S.bmp", &imageWidth, &imageHeight, &channels);
	//cout <<"test value : "<< imageHeight << endl;
	//if (image2 == nullptr) 
		//cout << "image2 is nullptr" << endl;

	SDL_Surface* image = IMG_Load("Texture/ground_stone1.jpg");	// 이미지를 가져와 메인 CPU에 할당한다.
	//if (image == nullptr) cout << "image is nullptr" << endl; return;

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
	//glTexImage2D(GL_TEXTURE_2D, 0, 3, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, texName[1]);
	image = IMG_Load("/Texture/gun1.jpg");
	//image2 = readImageData("D:/mini/Texture/metal5.jpg", &imageWidth, &imageHeight, &channels);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
	//glTexImage2D(GL_TEXTURE_2D, 0, 3, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, texName[2]);
	image = IMG_Load("/Texture/gold1.jpg");
	//image2 = readImageData("D:/mini/Texture/metal5.jpg", &imageWidth, &imageHeight, &channels);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
	//glTexImage2D(GL_TEXTURE_2D, 0, 3, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glGenTextures(1, &skyboxTex);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTex);
	//uchar* img0 = readImageData("/Texture/background2.jpg", &imageWidth, &imageHeight, &channels);
	//uchar* img1 = readImageData("/Texture/background1.jpg", &imageWidth, &imageHeight, &channels);
	//uchar* img2 = readImageData("/Texture/background1.jpg", &imageWidth, &imageHeight, &channels); // UP
	//uchar* img3 = readImageData("/Texture/background6.jpg", &imageWidth, &imageHeight, &channels); // DOWN
	//uchar* img4 = readImageData("/Texture/background1.jpg", &imageWidth, &imageHeight, &channels);
	//uchar* img5 = readImageData("/Texture/background3.jpg", &imageWidth, &imageHeight, &channels);

	SDL_Surface* img0 = IMG_Load("/Texture/nature_trees1.jpg");
	SDL_Surface* img1 = IMG_Load("/Texture/nature_trees1.jpg");
	SDL_Surface* img2 = IMG_Load("/Texture/nature_trees1.jpg"); // UP
	SDL_Surface* img3 = IMG_Load("/Texture/ground_stone1.jpg"); // DOWN
	SDL_Surface* img4 = IMG_Load("/Texture/nature_trees1.jpg");
	SDL_Surface* img5 = IMG_Load("/Texture/nature_trees1.jpg");

	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, img0->w, img0->h, 0, GL_RGB, GL_UNSIGNED_BYTE, img0->pixels);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, img1->w, img1->h, 0, GL_RGB, GL_UNSIGNED_BYTE, img1->pixels);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, img2->w, img2->h, 0, GL_RGB, GL_UNSIGNED_BYTE, img2->pixels);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, img3->w, img3->h, 0, GL_RGB, GL_UNSIGNED_BYTE, img3->pixels);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, img4->w, img4->h, 0, GL_RGB, GL_UNSIGNED_BYTE, img4->pixels);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, img5->w, img5->h, 0, GL_RGB, GL_UNSIGNED_BYTE, img5->pixels);

	glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTex);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//Initialize SDL
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

	//Initialize SDL_mixer
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	//Load WAV
	gGun = Mix_LoadWAV(SHOOT_SOUND);

	glLoadIdentity();
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
			upper_rotate_r_on = true;
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
		if (B_Angle <= 270 && (B_Trans >= 25)) B_Angle += 3;
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
		if (T_Rotate >= -90) T_Rotate -= 3;
		else tartget_hit = false;
	}
	else {
		if (T_Rotate < 0) T_Rotate += 3;
	}
	glutPostRedisplay();
}

void camera_eye() {
	if (theta > 2 * M_PI) theta -= 2 * M_PI;
	if (theta <= 0) theta += 2 * M_PI;
	if (radianpi > 2 * M_PI) radianpi -= 2 * M_PI;
	if (radianpi <= 0) radianpi += 2 * M_PI;
	viewX = (DIST + disdif) * cos(theta) * cos(radianpi);
	viewY = (DIST + disdif) * sin(theta);
	viewZ = (DIST + disdif) * cos(theta) * sin(radianpi);
}

void draw(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	char str[20];
	sprintf(str, "bullet : %d/%d", bullet_count, total_bullet);
	if (game_mode) {
		draw_string(GLUT_BITMAP_TIMES_ROMAN_24, str, 2, 4, 1.0f, 0.0f, 0.0f);
	}

	if (warning) draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "Reload!", -0.7f, 3.0f, 1.0f, 0.0f, 0.0f);

	if ((0 <= theta && theta < M_PI / 2) || (3 * M_PI / 2 < theta && theta <= 2 * M_PI)) {
		if (game_mode) {
			gluLookAt(viewX, viewY, viewZ, aimX + difX, aimY + difY, aimZ + 1, 0, 1, 0);
		}
		else {
			gluLookAt(viewX, viewY, viewZ, 0, 0, 0, 0, 1, 0);
		}
	}
	else {
		gluLookAt(viewX, viewY, viewZ, 0, 0, 0, 0, -1, 0);

	}

	if (game_mode) draw_skybox(250);
	//cout << "aim_mode : " << aim_mode << endl;

	glPushMatrix();
	GLUquadric* quadric = gluNewQuadric();
	glTranslatef(TARGET_X, -9.3f, TARGET_Z);
	glRotatef(T_Rotate, 1, 0, 0);
	if (game_mode) {
		glTranslatef(TARGET_X, 9.3 + TARGET_Y, 0);
		gluDisk(quadric, 0, 2, 30, 30);
		glBegin(GL_POLYGON);
		glVertex3f(-4, -2, 0);
		glVertex3f(-4, -15, 0);
		glVertex3f(4, -15, 0);
		glVertex3f(4, -2, 0);
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

void draw_skybox(float size) {
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_CUBE_MAP);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTex);

	glBegin(GL_QUADS);
	glTexCoord3d(1.0, -1.0, -1.0); glVertex3f(size, -9.3f, -size);
	glTexCoord3d(1.0, -1.0, 1.0); glVertex3f(size, -9.3f, size);
	glTexCoord3d(1.0, 1.0, 1.0); glVertex3f(size, -9.3f + size, size);
	glTexCoord3d(1.0, 1.0, -1.0); glVertex3f(size, -9.3f + size, -size);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord3d(-1.0, -1.0, -1.0); glVertex3f(-size, -9.3f, -size);
	glTexCoord3d(-1.0, -1.0, 1.0); glVertex3f(-size, -9.3f, size);
	glTexCoord3d(-1.0, 1.0, 1.0); glVertex3f(-size, -9.3f + size, size);
	glTexCoord3d(-1.0, 1.0, -1.0); glVertex3f(-size, -9.3f + size, -size);
	glEnd();

	glBegin(GL_QUADS); // UP
	glTexCoord3d(-1.0, 1.0, -1.0); glVertex3f(-size, size - 9.3f, -size);
	glTexCoord3d(-1.0, 1.0, 1.0); glVertex3f(-size, size - 9.3f, size);
	glTexCoord3d(1.0, 1.0, 1.0); glVertex3f(size, size - 9.3f, size);
	glTexCoord3d(1.0, 1.0, -1.0); glVertex3f(size, size - 9.3f, -size);
	glEnd();

	glBegin(GL_QUADS); //DOWN
	glTexCoord3d(-1.0, -1.0, -1.0); glVertex3f(-size, -9.3f, -size);
	glTexCoord3d(-1.0, -1.0, 1.0); glVertex3f(-size, -9.3f, size);
	glTexCoord3d(1.0, -1.0, 1.0); glVertex3f(size, -9.3f, size);
	glTexCoord3d(1.0, -1.0, -1.0); glVertex3f(size, -9.3f, -size);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord3d(-1.0, -1.0, +1.0); glVertex3f(-size, -9.3f, size);
	glTexCoord3d(-1.0, 1.0, 1.0); glVertex3f(-size, -9.3f + size, size);
	glTexCoord3d(1.0, 1.0, 1.0); glVertex3f(size, -9.3f + size, size);
	glTexCoord3d(1.0, -1.0, 1.0); glVertex3f(size, -9.3f, size);
	glEnd();

	glBegin(GL_QUADS);
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
			upper_rotate_on = false;
			upper_rotate_r_on = false;
			upper_upper_bottom_trans_on = false;
			handleon = false;
			shoulderon = false;
			caseon = false;
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
		if (game_mode) {
			if ((total_bullet + bullet_count) >= 30) {
				total_bullet -= (bullet_unit - bullet_count);
				bullet_count = 30;
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
	case 'r':
		if (game_mode) {
			if ((total_bullet + bullet_count) >= 30) {
				total_bullet -= (bullet_unit - bullet_count);
				bullet_count = 30;
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
		if (game_mode) {
			aimZ += MOVEMENT_SPEED;
			viewZ += MOVEMENT_SPEED;
			T_Trans_Z += MOVEMENT_SPEED;
		}
		break;
	case 'w':
		if (game_mode) {
			aimZ += MOVEMENT_SPEED;
			viewZ += MOVEMENT_SPEED;
			T_Trans_Z += MOVEMENT_SPEED;
		}
		break;
	case 'S':
		if (game_mode) {
			aimZ -= MOVEMENT_SPEED;
			viewZ -= MOVEMENT_SPEED;
			T_Trans_Z -= MOVEMENT_SPEED;
		}
		break;
	case 's':
		if (game_mode) {
			aimZ -= MOVEMENT_SPEED;
			viewZ -= MOVEMENT_SPEED;
			T_Trans_Z -= MOVEMENT_SPEED;
		}
		break;
	case 'A':
		if (game_mode) {
			aimX += MOVEMENT_SPEED;
			viewX += MOVEMENT_SPEED;
			T_Trans_X += MOVEMENT_SPEED;
			hitx_dif += MOVE_COORDINATE;
		}
		break;
	case 'a':
		if (game_mode) {
			aimX += MOVEMENT_SPEED;
			viewX += MOVEMENT_SPEED;
			T_Trans_X += MOVEMENT_SPEED;
			hitx_dif += MOVE_COORDINATE;
		}
		break;
	case 'D':
		if (game_mode) {
			aimX -= MOVEMENT_SPEED;
			viewX -= MOVEMENT_SPEED;
			T_Trans_X -= MOVEMENT_SPEED;
			hitx_dif -= MOVE_COORDINATE;
		}
		break;
	case 'd':
		if (game_mode) {
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
		if (game_mode) mouse_sensitivity += 0.01f;
		break;
	case '[':
		if (game_mode) mouse_sensitivity -= 0.01f;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void specialkey(int key, int x, int y) {
	if (key == 100) {
		printf("← pressed\n");
	}
	else if (key == 101)
	{
		printf("↑ pressed\n");
	}
	else if (key == 101) {
		printf("→ pressed\n");
	}
	else if (key == 102) {
		printf("← pressed\n");
	}
	else if (key == 103) {
		printf("↓ pressed\n");
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

void mouse(int button, int state, int x, int y) {
	y = CURRENT_HEIGHT - y;
	if (game_mode) {
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			if (bullet_count > 0) {
				Mix_PlayChannel(-1, gGun, 0);
				double hitx = (aimzoneX + (26.512) * difX - viewX) * (TARGET_Z - viewZ) / (aimzoneZ - viewZ) + viewX;
				double hity = (aimzoneY + (26.512) * difY - viewY) * (TARGET_Z - viewZ) / (aimzoneZ - viewZ) + viewY;
				if ((aimzoneX + difX) - viewX != 0) {
					if (-4 < (hitx + hitx_dif) && (hitx + hitx_dif) < 4) tartget_hit = true;
				}
				else if ((aimzoneY + difY) - viewY != 0) {
					if (-8.3 <= hity && hity <= 7.7) tartget_hit = true;
				}
				bullet_count--;
				if (bullet_count == 0) warning = true;
				else warning = false;
			}
		}
		else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
			game_mode = false;
			viewX = preViewX;
			viewY = preViewY;
			viewZ = preViewZ;
			aimX = preAimX;
			aimY = preAimY;
			aimZ = preAimZ;
			T_Trans_X = 0;
			T_Trans_Z = 0;
			hitx_dif = 0;
			R_Angle = Prev_R_Angle;
			if (prev_rotate_m) rotate_m = true;
		}
	}
	else {
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			g_nX = x;
			g_nY = y;
			left_state = true;
		}
		else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
			left_state = false;
		}
		else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
			game_mode = true;
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
			total_bullet = 150;
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
	if (game_mode == false && left_state) {
		radianpi += (x - g_nX) * RADIAN_TRANSF;
		theta -= (y - g_nY) * RADIAN_TRANSF;
		g_nX = x;
		g_nY = y;
		camera_eye();
	}
	glutPostRedisplay();
}

void passivemotion(int x, int y) {
	y = CURRENT_HEIGHT - y;
	if (game_mode) {
		mouse_rotationX = -((x - a_nX) / 25.0f) * mouse_sensitivity;
		mouse_rotationY = -((y - a_nY) / 25.0f) * mouse_sensitivity;
		difX = sin(mouse_rotationX * RADIAN_TRANSF);
		difY = sin(-mouse_rotationY * RADIAN_TRANSF);
	}
	glutPostRedisplay();
}

void obj_file_load(char* fname) {
	FILE* fp;
	float x;
	float y;
	float z;
	int i, j, u;
	i = 0; j = 0; u = 0;

	fp = fopen(fname, "r");
	if (!fp) {
		printf("can't open file %s\n", fname);
		exit(1);
	}
	while (!(feof(fp))) {
		char lineHeader[128];
		fscanf(fp, "%s", lineHeader);
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
			u++;
			int a, b;
			fscanf(fp, "%d//%d", &a, &b);
			f1[object_number][u] = a;
			fscanf(fp, "%d//%d", &a, &b);
			f2[object_number][u] = a;
			fscanf(fp, "%d//%d", &a, &b);
			f3[object_number][u] = a;
			f4[object_number][u] = b;
		}
	}
	f_num[object_number] = u;
	object_number++;
}

void draw_obj() {
	glRotatef(R_Angle, 0, 1, 0);
	for (int m = 0; m < object_number; m++) {
		glPushMatrix();
		if (game_mode) {
			glTranslatef(T_Trans_X, 0, T_Trans_Z);
			glTranslatef(viewX - T_Trans_X, viewY, viewZ - T_Trans_Z);
			glRotatef(mouse_rotationX, 0, 1, 0);
			glRotatef(mouse_rotationY, 1, 0, 0);
			glTranslatef(-viewX + T_Trans_X, -viewY, -viewZ + T_Trans_Z);
		}
		else {
			if (m == 7 || m == 16) {
				glTranslatef(0, 0, S_Trans);
			}
			if (m == 10) {
				glTranslatef(0, 0.8, 0);
				glRotatef(H_Angle, 0, 0, 0);
				glTranslatef(0, -0.8, 0);
			}
			if (m == 11) {
				glTranslatef(0, 0.8, -1.7);
				glRotatef(S_Angle, 0, 0, 0);
				glTranslatef(0, -0.8, 1.7);
			}
			if (m == 4 || m == 9) {
				glTranslatef(0, 0, H_Trans);
			}
			if (m == 5 || m == 19) {
				glTranslatef(0, C_Trans, 0);
			}
			if (blending) {
				if (m == 0 || m == 1 || m == 2 || m == 8) {
					glEnable(GL_BLEND);
					glDisable(GL_DEPTH_TEST);
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					glColor4f(1.0f, 1.0f, 1.0f, 0.1f);
				}
				else {
					glDisable(GL_BLEND);
					glEnable(GL_DEPTH_TEST);
				}
			}
			else {
				glEnable(GL_DEPTH_TEST);
				glDisable(GL_BLEND);
			}
			if (m == 0 || m == 1 || m == 2 || m == 4 || m == 8 || m == 9 || m == 12 || m == 13 || m == 14 || m == 15) {
				glTranslatef(0, 3, 4.6);
				glRotatef(U_Angle, 1, 0, 0);
				glTranslatef(0, -3, -4.6);
				glRotatef(UR_Angle, 1, 0, 0);
				if (m == 0) {
					glTranslatef(-CA_Trans, 0, 0);
				}
				if (m == 1) {
					glTranslatef(CA_Trans, 0, 0);
				}
				if (m == 8 || m == 9) {
					glTranslatef(0, 0, UI_Trans);
				}
				if (m == 4) {
					if (UI_Trans >= -5) {
						temp = UI_Trans;
					}
					glTranslatef(0, 0, temp);
					glTranslatef(HA_Trans, 0, 0);
				}
				if (m == 12) {
					glTranslatef(0, 0, BC_Trans_1 + B_Trans);
					if (sin(B_Angle * RADIAN_TRANSF) < 0) {
						glTranslatef(0, 3 * sin(B_Angle * RADIAN_TRANSF), 0);
					}
					else {
						glTranslatef(0, sin(B_Angle * RADIAN_TRANSF), 0);
					}
				}
				if (m == 13) {
					glTranslatef(0, 0, BC_Trans_1);
					glTranslatef(0, -5, 0);
					glRotatef(BC_Angle, 0, 0, 1);
					glTranslatef(0, 5, 0);
				}
				if (m == 14 || m == 15) {
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
		if (m == 0 || m == 1 || m == 4) glBindTexture(GL_TEXTURE_2D, texName[1]);
		else if (m == 7 || m == 17 || m == 18) glBindTexture(GL_TEXTURE_2D, texName[1]);
		else if (m == 12 || m == 13 || m == 14 || m == 15 || m == 19) glBindTexture(GL_TEXTURE_2D, texName[2]);
		else glBindTexture(GL_TEXTURE_2D, texName[0]);
		glBegin(GL_TRIANGLES);
		for (int n = 0; n < f_num[m]; n++) {
			glNormal3f(nvx[m][f4[m][n]], nvy[m][f4[m][n]], nvz[m][f4[m][n]]);
			glTexCoord2f(0, 0);
			glVertex3f(vx[m][f1[m][n]], vy[m][f1[m][n]], vz[m][f1[m][n]]);

			glNormal3f(nvx[m][f4[m][n]], nvy[m][f4[m][n]], nvz[m][f4[m][n]]);
			glTexCoord2f(0, 1);
			glVertex3f(vx[m][f2[m][n]], vy[m][f2[m][n]], vz[m][f2[m][n]]);

			glNormal3f(nvx[m][f4[m][n]], nvy[m][f4[m][n]], nvz[m][f4[m][n]]);
			glTexCoord2f(0.5, 0.5);
			glVertex3f(vx[m][f3[m][n]], vy[m][f3[m][n]], vz[m][f3[m][n]]);
		}
		glEnd();
		glPopMatrix();
	}
}
