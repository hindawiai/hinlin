<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Helper function क्रम splitting a string पूर्णांकo an argv-like array.
 */

#समावेश <मानककोष.स>
#समावेश <linux/kernel.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/माला.स>

अटल स्थिर अक्षर *skip_arg(स्थिर अक्षर *cp)
अणु
	जबतक (*cp && !है_खाली(*cp))
		cp++;

	वापस cp;
पूर्ण

अटल पूर्णांक count_argc(स्थिर अक्षर *str)
अणु
	पूर्णांक count = 0;

	जबतक (*str) अणु
		str = skip_spaces(str);
		अगर (*str) अणु
			count++;
			str = skip_arg(str);
		पूर्ण
	पूर्ण

	वापस count;
पूर्ण

/**
 * argv_मुक्त - मुक्त an argv
 * @argv - the argument vector to be मुक्तd
 *
 * Frees an argv and the strings it poपूर्णांकs to.
 */
व्योम argv_मुक्त(अक्षर **argv)
अणु
	अक्षर **p;
	क्रम (p = argv; *p; p++) अणु
		मुक्त(*p);
		*p = शून्य;
	पूर्ण

	मुक्त(argv);
पूर्ण

/**
 * argv_split - split a string at whitespace, वापसing an argv
 * @str: the string to be split
 * @argcp: वापसed argument count
 *
 * Returns an array of poपूर्णांकers to strings which are split out from
 * @str.  This is perक्रमmed by strictly splitting on white-space; no
 * quote processing is perक्रमmed.  Multiple whitespace अक्षरacters are
 * considered to be a single argument separator.  The वापसed array
 * is always शून्य-terminated.  Returns शून्य on memory allocation
 * failure.
 */
अक्षर **argv_split(स्थिर अक्षर *str, पूर्णांक *argcp)
अणु
	पूर्णांक argc = count_argc(str);
	अक्षर **argv = सुस्मृति(argc + 1, माप(*argv));
	अक्षर **argvp;

	अगर (argv == शून्य)
		जाओ out;

	अगर (argcp)
		*argcp = argc;

	argvp = argv;

	जबतक (*str) अणु
		str = skip_spaces(str);

		अगर (*str) अणु
			स्थिर अक्षर *p = str;
			अक्षर *t;

			str = skip_arg(str);

			t = strndup(p, str-p);
			अगर (t == शून्य)
				जाओ fail;
			*argvp++ = t;
		पूर्ण
	पूर्ण
	*argvp = शून्य;

out:
	वापस argv;

fail:
	argv_मुक्त(argv);
	वापस शून्य;
पूर्ण
