<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <दो_स्मृति.h>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <समय.स>
#समावेश "utils.h"

#घोषणा SIZE 256
#घोषणा ITERATIONS 1000
#घोषणा ITERATIONS_BENCH 100000

पूर्णांक test_म_माप(स्थिर व्योम *s);

/* test all offsets and lengths */
अटल व्योम test_one(अक्षर *s)
अणु
	अचिन्हित दीर्घ offset;

	क्रम (offset = 0; offset < SIZE; offset++) अणु
		पूर्णांक x, y;
		अचिन्हित दीर्घ i;

		y = म_माप(s + offset);
		x = test_म_माप(s + offset);

		अगर (x != y) अणु
			म_लिखो("strlen() returned %d, should have returned %d (%p offset %ld)\n", x, y, s, offset);

			क्रम (i = offset; i < SIZE; i++)
				म_लिखो("%02x ", s[i]);
			म_लिखो("\n");
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम bench_test(अक्षर *s)
अणु
	काष्ठा बारpec ts_start, ts_end;
	पूर्णांक i;

	घड़ी_समय_लो(CLOCK_MONOTONIC, &ts_start);

	क्रम (i = 0; i < ITERATIONS_BENCH; i++)
		test_म_माप(s);

	घड़ी_समय_लो(CLOCK_MONOTONIC, &ts_end);

	म_लिखो("len %3.3d : time = %.6f\n", test_म_माप(s), ts_end.tv_sec - ts_start.tv_sec + (ts_end.tv_nsec - ts_start.tv_nsec) / 1e9);
पूर्ण

अटल पूर्णांक testहाल(व्योम)
अणु
	अक्षर *s;
	अचिन्हित दीर्घ i;

	s = memalign(128, SIZE);
	अगर (!s) अणु
		लिखो_त्रुटि("memalign");
		निकास(1);
	पूर्ण

	बेक्रमom(1);

	स_रखो(s, 0, SIZE);
	क्रम (i = 0; i < SIZE; i++) अणु
		अक्षर c;

		करो अणु
			c = अक्रमom() & 0x7f;
		पूर्ण जबतक (!c);
		s[i] = c;
		test_one(s);
	पूर्ण

	क्रम (i = 0; i < ITERATIONS; i++) अणु
		अचिन्हित दीर्घ j;

		क्रम (j = 0; j < SIZE; j++) अणु
			अक्षर c;

			करो अणु
				c = अक्रमom() & 0x7f;
			पूर्ण जबतक (!c);
			s[j] = c;
		पूर्ण
		क्रम (j = 0; j < माप(दीर्घ); j++) अणु
			s[SIZE - 1 - j] = 0;
			test_one(s);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < SIZE; i++) अणु
		अक्षर c;

		करो अणु
			c = अक्रमom() & 0x7f;
		पूर्ण जबतक (!c);
		s[i] = c;
	पूर्ण

	bench_test(s);

	s[16] = 0;
	bench_test(s);

	s[8] = 0;
	bench_test(s);

	s[4] = 0;
	bench_test(s);

	s[3] = 0;
	bench_test(s);

	s[2] = 0;
	bench_test(s);

	s[1] = 0;
	bench_test(s);

	वापस 0;
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	वापस test_harness(testहाल, "strlen");
पूर्ण
