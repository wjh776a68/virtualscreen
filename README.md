# virtualscreen
An header file uses to drawing simply shapes and characters in console mode.

-------------------  assist function  -----------------------------------------------------------------------

int char2int(char);               //using to force char character into int character in the painting zone
char int2char(int);               //using to force int character into char character in the painting zone
int axis2array(DRAW *&,int x,int y);  //return the coordinate (x,y) into the underlabel of an array

-------------------  create or destroy the painting zone  ---------------------------------------------------

DRAW* drawstart(int, int);        //open an drawing arena
void drawclose(DRAW *);           //destroy an drawing arena, free the memory
void drawclean(DRAW *&);          //clean the drawing arena ( turn into blank)

-------------------  add character into the painting zone  --------------------------------------------------

void addpixel(DRAW *&,int x, int y,int value); //insert a int value into the arena with point (x,y) (unrecommend,please use addpixels() instead)
void addpixels(DRAW*&,int x,int y,int value);            //insert a line string (mulpity number characters) into the arena with start point (x,y)
void addpixelc(DRAW *&,int x, int y,char character);         //insert a char character into the arena with point (x,y)
void addline(DRAW *&,int x1,int y1,int x2,int y2);         //insert a line into the arena with start point (x1,y1) and end point (x2,y2)

------------------   print the painting zone   --------------------------------------------------------------

void drawchar(DRAW *&dp);                       //print the drawing arena with acsii encode
void draw(DRAW *&dp);                           //redirect to drawsmart()
void drawsmart(DRAW *&dp);                      //print the drawing arena smartly. (recommend)
void drawint(DRAW *&dp);                        // print the drawing arena with int number.
