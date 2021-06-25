<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *    Filename: cfag12864b-example.c
 *     Version: 0.1.0
 * Description: cfag12864b LCD userspace example program
 *
 *      Author: Copyright (C) Miguel Ojeda <ojeda@kernel.org>
 *        Date: 2006-10-31
 */

/*
 * ------------------------
 * start of cfag12864b code
 * ------------------------
 */

#समावेश <माला.स>
#समावेश <fcntl.h>
#समावेश <unistd.h>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/mman.h>

#घोषणा CFAG12864B_WIDTH		(128)
#घोषणा CFAG12864B_HEIGHT		(64)
#घोषणा CFAG12864B_SIZE			(128 * 64 / 8)
#घोषणा CFAG12864B_BPB			(8)
#घोषणा CFAG12864B_ADDRESS(x, y)	((y) * CFAG12864B_WIDTH / \
					CFAG12864B_BPB + (x) / CFAG12864B_BPB)
#घोषणा CFAG12864B_BIT(n)		(((अचिन्हित अक्षर) 1) << (n))

#अघोषित CFAG12864B_DOCHECK
#अगर_घोषित CFAG12864B_DOCHECK
	#घोषणा CFAG12864B_CHECK(x, y)		((x) < CFAG12864B_WIDTH && \
						(y) < CFAG12864B_HEIGHT)
#अन्यथा
	#घोषणा CFAG12864B_CHECK(x, y)		(1)
#पूर्ण_अगर

पूर्णांक cfag12864b_fd;
अचिन्हित अक्षर * cfag12864b_mem;
अचिन्हित अक्षर cfag12864b_buffer[CFAG12864B_SIZE];

/*
 * init a cfag12864b framebuffer device
 *
 * No error:       वापस = 0
 * Unable to खोलो: वापस = -1
 * Unable to mmap: वापस = -2
 */
अटल पूर्णांक cfag12864b_init(अक्षर *path)
अणु
	cfag12864b_fd = खोलो(path, O_RDWR);
	अगर (cfag12864b_fd == -1)
		वापस -1;

	cfag12864b_mem = mmap(0, CFAG12864B_SIZE, PROT_READ | PROT_WRITE,
		MAP_SHARED, cfag12864b_fd, 0);
	अगर (cfag12864b_mem == MAP_FAILED) अणु
		बंद(cfag12864b_fd);
		वापस -2;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * निकास a cfag12864b framebuffer device
 */
अटल व्योम cfag12864b_निकास(व्योम)
अणु
	munmap(cfag12864b_mem, CFAG12864B_SIZE);
	बंद(cfag12864b_fd);
पूर्ण

/*
 * set (x, y) pixel
 */
अटल व्योम cfag12864b_set(अचिन्हित अक्षर x, अचिन्हित अक्षर y)
अणु
	अगर (CFAG12864B_CHECK(x, y))
		cfag12864b_buffer[CFAG12864B_ADDRESS(x, y)] |=
			CFAG12864B_BIT(x % CFAG12864B_BPB);
पूर्ण

/*
 * unset (x, y) pixel
 */
अटल व्योम cfag12864b_unset(अचिन्हित अक्षर x, अचिन्हित अक्षर y)
अणु
	अगर (CFAG12864B_CHECK(x, y))
		cfag12864b_buffer[CFAG12864B_ADDRESS(x, y)] &=
			~CFAG12864B_BIT(x % CFAG12864B_BPB);
पूर्ण

/*
 * is set (x, y) pixel?
 *
 * Pixel off: वापस = 0
 * Pixel on:  वापस = 1
 */
अटल अचिन्हित अक्षर cfag12864b_isset(अचिन्हित अक्षर x, अचिन्हित अक्षर y)
अणु
	अगर (CFAG12864B_CHECK(x, y))
		अगर (cfag12864b_buffer[CFAG12864B_ADDRESS(x, y)] &
			CFAG12864B_BIT(x % CFAG12864B_BPB))
			वापस 1;

	वापस 0;
पूर्ण

/*
 * not (x, y) pixel
 */
अटल व्योम cfag12864b_not(अचिन्हित अक्षर x, अचिन्हित अक्षर y)
अणु
	अगर (cfag12864b_isset(x, y))
		cfag12864b_unset(x, y);
	अन्यथा
		cfag12864b_set(x, y);
पूर्ण

/*
 * fill (set all pixels)
 */
अटल व्योम cfag12864b_fill(व्योम)
अणु
	अचिन्हित लघु i;

	क्रम (i = 0; i < CFAG12864B_SIZE; i++)
		cfag12864b_buffer[i] = 0xFF;
पूर्ण

/*
 * clear (unset all pixels)
 */
अटल व्योम cfag12864b_clear(व्योम)
अणु
	अचिन्हित लघु i;

	क्रम (i = 0; i < CFAG12864B_SIZE; i++)
		cfag12864b_buffer[i] = 0;
पूर्ण

/*
 * क्रमmat a [128*64] matrix
 *
 * Pixel off: src[i] = 0
 * Pixel on:  src[i] > 0
 */
अटल व्योम cfag12864b_क्रमmat(अचिन्हित अक्षर * matrix)
अणु
	अचिन्हित अक्षर i, j, n;

	क्रम (i = 0; i < CFAG12864B_HEIGHT; i++)
	क्रम (j = 0; j < CFAG12864B_WIDTH / CFAG12864B_BPB; j++) अणु
		cfag12864b_buffer[i * CFAG12864B_WIDTH / CFAG12864B_BPB +
			j] = 0;
		क्रम (n = 0; n < CFAG12864B_BPB; n++)
			अगर (matrix[i * CFAG12864B_WIDTH +
				j * CFAG12864B_BPB + n])
				cfag12864b_buffer[i * CFAG12864B_WIDTH /
					CFAG12864B_BPB + j] |=
					CFAG12864B_BIT(n);
	पूर्ण
पूर्ण

/*
 * blit buffer to lcd
 */
अटल व्योम cfag12864b_blit(व्योम)
अणु
	स_नकल(cfag12864b_mem, cfag12864b_buffer, CFAG12864B_SIZE);
पूर्ण

/*
 * ----------------------
 * end of cfag12864b code
 * ----------------------
 */

#समावेश <मानकपन.स>

#घोषणा EXAMPLES	6

अटल व्योम example(अचिन्हित अक्षर n)
अणु
	अचिन्हित लघु i, j;
	अचिन्हित अक्षर matrix[CFAG12864B_WIDTH * CFAG12864B_HEIGHT];

	अगर (n > EXAMPLES)
		वापस;

	म_लिखो("Example %i/%i - ", n, EXAMPLES);

	चयन (n) अणु
	हाल 1:
		म_लिखो("Draw points setting bits");
		cfag12864b_clear();
		क्रम (i = 0; i < CFAG12864B_WIDTH; i += 2)
			क्रम (j = 0; j < CFAG12864B_HEIGHT; j += 2)
				cfag12864b_set(i, j);
		अवरोध;

	हाल 2:
		म_लिखो("Clear the LCD");
		cfag12864b_clear();
		अवरोध;

	हाल 3:
		म_लिखो("Draw rows formatting a [128*64] matrix");
		स_रखो(matrix, 0, CFAG12864B_WIDTH * CFAG12864B_HEIGHT);
		क्रम (i = 0; i < CFAG12864B_WIDTH; i++)
			क्रम (j = 0; j < CFAG12864B_HEIGHT; j += 2)
				matrix[j * CFAG12864B_WIDTH + i] = 1;
		cfag12864b_क्रमmat(matrix);
		अवरोध;

	हाल 4:
		म_लिखो("Fill the lcd");
		cfag12864b_fill();
		अवरोध;

	हाल 5:
		म_लिखो("Draw columns unsetting bits");
		क्रम (i = 0; i < CFAG12864B_WIDTH; i += 2)
			क्रम (j = 0; j < CFAG12864B_HEIGHT; j++)
				cfag12864b_unset(i, j);
		अवरोध;

	हाल 6:
		म_लिखो("Do negative not-ing all bits");
		क्रम (i = 0; i < CFAG12864B_WIDTH; i++)
			क्रम (j = 0; j < CFAG12864B_HEIGHT; j ++)
				cfag12864b_not(i, j);
		अवरोध;
	पूर्ण

	माला_दो(" - [Press Enter]");
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	अचिन्हित अक्षर n;

	अगर (argc != 2) अणु
		म_लिखो(
			"Syntax:  %s fbdev\n"
			"Usually: /dev/fb0, /dev/fb1...\n", argv[0]);
		वापस -1;
	पूर्ण

	अगर (cfag12864b_init(argv[1])) अणु
		म_लिखो("Can't init %s fbdev\n", argv[1]);
		वापस -2;
	पूर्ण

	क्रम (n = 1; n <= EXAMPLES; n++) अणु
		example(n);
		cfag12864b_blit();
		जबतक (अक्षर_लो() != '\n');
	पूर्ण

	cfag12864b_निकास();

	वापस 0;
पूर्ण
