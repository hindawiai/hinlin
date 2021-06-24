<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Helper function क्रम splitting a string पूर्णांकo an argv-like array.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>

अटल पूर्णांक count_argc(स्थिर अक्षर *str)
अणु
	पूर्णांक count = 0;
	bool was_space;

	क्रम (was_space = true; *str; str++) अणु
		अगर (है_खाली(*str)) अणु
			was_space = true;
		पूर्ण अन्यथा अगर (was_space) अणु
			was_space = false;
			count++;
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
	argv--;
	kमुक्त(argv[0]);
	kमुक्त(argv);
पूर्ण
EXPORT_SYMBOL(argv_मुक्त);

/**
 * argv_split - split a string at whitespace, वापसing an argv
 * @gfp: the GFP mask used to allocate memory
 * @str: the string to be split
 * @argcp: वापसed argument count
 *
 * Returns an array of poपूर्णांकers to strings which are split out from
 * @str.  This is perक्रमmed by strictly splitting on white-space; no
 * quote processing is perक्रमmed.  Multiple whitespace अक्षरacters are
 * considered to be a single argument separator.  The वापसed array
 * is always शून्य-terminated.  Returns शून्य on memory allocation
 * failure.
 *
 * The source string at `str' may be undergoing concurrent alteration via
 * userspace sysctl activity (at least).  The argv_split() implementation
 * attempts to handle this gracefully by taking a local copy to work on.
 */
अक्षर **argv_split(gfp_t gfp, स्थिर अक्षर *str, पूर्णांक *argcp)
अणु
	अक्षर *argv_str;
	bool was_space;
	अक्षर **argv, **argv_ret;
	पूर्णांक argc;

	argv_str = kstrndup(str, KMALLOC_MAX_SIZE - 1, gfp);
	अगर (!argv_str)
		वापस शून्य;

	argc = count_argc(argv_str);
	argv = kदो_स्मृति_array(argc + 2, माप(*argv), gfp);
	अगर (!argv) अणु
		kमुक्त(argv_str);
		वापस शून्य;
	पूर्ण

	*argv = argv_str;
	argv_ret = ++argv;
	क्रम (was_space = true; *argv_str; argv_str++) अणु
		अगर (है_खाली(*argv_str)) अणु
			was_space = true;
			*argv_str = 0;
		पूर्ण अन्यथा अगर (was_space) अणु
			was_space = false;
			*argv++ = argv_str;
		पूर्ण
	पूर्ण
	*argv = शून्य;

	अगर (argcp)
		*argcp = argc;
	वापस argv_ret;
पूर्ण
EXPORT_SYMBOL(argv_split);
