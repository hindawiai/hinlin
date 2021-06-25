<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <sys/types.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश "symbol.h"

#समावेश "demangle-java.h"

#समावेश <linux/प्रकार.स>
#समावेश <linux/kernel.h>

क्रमागत अणु
	MODE_PREFIX = 0,
	MODE_CLASS  = 1,
	MODE_FUNC   = 2,
	MODE_TYPE   = 3,
	MODE_CTYPE  = 4, /* class arg */
पूर्ण;

#घोषणा BASE_ENT(c, n)	[c - 'A']=n
अटल स्थिर अक्षर *base_types['Z' - 'A' + 1] = अणु
	BASE_ENT('B', "byte" ),
	BASE_ENT('C', "char" ),
	BASE_ENT('D', "double" ),
	BASE_ENT('F', "float" ),
	BASE_ENT('I', "int" ),
	BASE_ENT('J', "long" ),
	BASE_ENT('S', "short" ),
	BASE_ENT('Z', "boolean" ),
पूर्ण;

/*
 * demangle Java symbol between str and end positions and stores
 * up to maxlen अक्षरacters पूर्णांकo buf. The parser starts in mode.
 *
 * Use MODE_PREFIX to process entire prototype till end position
 * Use MODE_TYPE to process वापस type अगर str starts on वापस type अक्षर
 *
 *  Return:
 *	success: buf
 *	error  : शून्य
 */
अटल अक्षर *
__demangle_java_sym(स्थिर अक्षर *str, स्थिर अक्षर *end, अक्षर *buf, पूर्णांक maxlen, पूर्णांक mode)
अणु
	पूर्णांक rlen = 0;
	पूर्णांक array = 0;
	पूर्णांक narg = 0;
	स्थिर अक्षर *q;

	अगर (!end)
		end = str + म_माप(str);

	क्रम (q = str; q != end; q++) अणु

		अगर (rlen == (maxlen - 1))
			अवरोध;

		चयन (*q) अणु
		हाल 'L':
			अगर (mode == MODE_PREFIX || mode == MODE_TYPE) अणु
				अगर (mode == MODE_TYPE) अणु
					अगर (narg)
						rlen += scnम_लिखो(buf + rlen, maxlen - rlen, ", ");
					narg++;
				पूर्ण
				अगर (mode == MODE_PREFIX)
					mode = MODE_CLASS;
				अन्यथा
					mode = MODE_CTYPE;
			पूर्ण अन्यथा
				buf[rlen++] = *q;
			अवरोध;
		हाल 'B':
		हाल 'C':
		हाल 'D':
		हाल 'F':
		हाल 'I':
		हाल 'J':
		हाल 'S':
		हाल 'Z':
			अगर (mode == MODE_TYPE) अणु
				अगर (narg)
					rlen += scnम_लिखो(buf + rlen, maxlen - rlen, ", ");
				rlen += scnम_लिखो(buf + rlen, maxlen - rlen, "%s", base_types[*q - 'A']);
				जबतक (array--)
					rlen += scnम_लिखो(buf + rlen, maxlen - rlen, "[]");
				array = 0;
				narg++;
			पूर्ण अन्यथा
				buf[rlen++] = *q;
			अवरोध;
		हाल 'V':
			अगर (mode == MODE_TYPE) अणु
				rlen += scnम_लिखो(buf + rlen, maxlen - rlen, "void");
				जबतक (array--)
					rlen += scnम_लिखो(buf + rlen, maxlen - rlen, "[]");
				array = 0;
			पूर्ण अन्यथा
				buf[rlen++] = *q;
			अवरोध;
		हाल '[':
			अगर (mode != MODE_TYPE)
				जाओ error;
			array++;
			अवरोध;
		हाल '(':
			अगर (mode != MODE_FUNC)
				जाओ error;
			buf[rlen++] = *q;
			mode = MODE_TYPE;
			अवरोध;
		हाल ')':
			अगर (mode != MODE_TYPE)
				जाओ error;
			buf[rlen++] = *q;
			narg = 0;
			अवरोध;
		हाल ';':
			अगर (mode != MODE_CLASS && mode != MODE_CTYPE)
				जाओ error;
			/* safe because at least one other अक्षर to process */
			अगर (है_अक्षर(*(q + 1)) && mode == MODE_CLASS)
				rlen += scnम_लिखो(buf + rlen, maxlen - rlen, ".");
			अगर (mode == MODE_CLASS)
				mode = MODE_FUNC;
			अन्यथा अगर (mode == MODE_CTYPE)
				mode = MODE_TYPE;
			अवरोध;
		हाल '/':
			अगर (mode != MODE_CLASS && mode != MODE_CTYPE)
				जाओ error;
			rlen += scnम_लिखो(buf + rlen, maxlen - rlen, ".");
			अवरोध;
		शेष :
			buf[rlen++] = *q;
		पूर्ण
	पूर्ण
	buf[rlen] = '\0';
	वापस buf;
error:
	वापस शून्य;
पूर्ण

/*
 * Demangle Java function signature (खोलोJDK, not GCJ)
 * input:
 * 	str: string to parse. String is not modअगरied
 *    flags: combination of JAVA_DEMANGLE_* flags to modअगरy demangling
 * वापस:
 *	अगर input can be demangled, then a newly allocated string is वापसed.
 *	अगर input cannot be demangled, then शून्य is वापसed
 *
 * Note: caller is responsible क्रम मुक्तing demangled string
 */
अक्षर *
java_demangle_sym(स्थिर अक्षर *str, पूर्णांक flags)
अणु
	अक्षर *buf, *ptr;
	अक्षर *p;
	माप_प्रकार len, l1 = 0;

	अगर (!str)
		वापस शून्य;

	/* find start of वापस type */
	p = म_खोजप(str, ')');
	अगर (!p)
		वापस शून्य;

	/*
	 * expansion factor estimated to 3x
	 */
	len = म_माप(str) * 3 + 1;
	buf = दो_स्मृति(len);
	अगर (!buf)
		वापस शून्य;

	buf[0] = '\0';
	अगर (!(flags & JAVA_DEMANGLE_NORET)) अणु
		/*
		 * get वापस type first
		 */
		ptr = __demangle_java_sym(p + 1, शून्य, buf, len, MODE_TYPE);
		अगर (!ptr)
			जाओ error;

		/* add space between वापस type and function prototype */
		l1 = म_माप(buf);
		buf[l1++] = ' ';
	पूर्ण

	/* process function up to वापस type */
	ptr = __demangle_java_sym(str, p + 1, buf + l1, len - l1, MODE_PREFIX);
	अगर (!ptr)
		जाओ error;

	वापस buf;
error:
	मुक्त(buf);
	वापस शून्य;
पूर्ण
