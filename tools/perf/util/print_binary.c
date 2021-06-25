<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "print_binary.h"
#समावेश <linux/log2.h>
#समावेश <linux/प्रकार.स>

पूर्णांक binary__ख_लिखो(अचिन्हित अक्षर *data, माप_प्रकार len,
		    माप_प्रकार bytes_per_line, binary__ख_लिखो_t prपूर्णांकer,
		    व्योम *extra, खाता *fp)
अणु
	माप_प्रकार i, j, mask;
	पूर्णांक prपूर्णांकed = 0;

	अगर (!prपूर्णांकer)
		वापस 0;

	bytes_per_line = roundup_घात_of_two(bytes_per_line);
	mask = bytes_per_line - 1;

	prपूर्णांकed += prपूर्णांकer(BINARY_PRINT_DATA_BEGIN, 0, extra, fp);
	क्रम (i = 0; i < len; i++) अणु
		अगर ((i & mask) == 0) अणु
			prपूर्णांकed += prपूर्णांकer(BINARY_PRINT_LINE_BEGIN, -1, extra, fp);
			prपूर्णांकed += prपूर्णांकer(BINARY_PRINT_ADDR, i, extra, fp);
		पूर्ण

		prपूर्णांकed += prपूर्णांकer(BINARY_PRINT_NUM_DATA, data[i], extra, fp);

		अगर (((i & mask) == mask) || i == len - 1) अणु
			क्रम (j = 0; j < mask-(i & mask); j++)
				prपूर्णांकed += prपूर्णांकer(BINARY_PRINT_NUM_PAD, -1, extra, fp);

			prपूर्णांकer(BINARY_PRINT_SEP, i, extra, fp);
			क्रम (j = i & ~mask; j <= i; j++)
				prपूर्णांकed += prपूर्णांकer(BINARY_PRINT_CHAR_DATA, data[j], extra, fp);
			क्रम (j = 0; j < mask-(i & mask); j++)
				prपूर्णांकed += prपूर्णांकer(BINARY_PRINT_CHAR_PAD, i, extra, fp);
			prपूर्णांकed += prपूर्णांकer(BINARY_PRINT_LINE_END, -1, extra, fp);
		पूर्ण
	पूर्ण
	prपूर्णांकed += prपूर्णांकer(BINARY_PRINT_DATA_END, -1, extra, fp);
	वापस prपूर्णांकed;
पूर्ण

पूर्णांक is_prपूर्णांकable_array(अक्षर *p, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक i;

	अगर (!p || !len || p[len - 1] != 0)
		वापस 0;

	len--;

	क्रम (i = 0; i < len && p[i]; i++) अणु
		अगर (!है_छाप(p[i]) && !है_खाली(p[i]))
			वापस 0;
	पूर्ण
	वापस 1;
पूर्ण
