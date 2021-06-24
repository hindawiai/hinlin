<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * "Optimize" a list of dependencies as spit out by gcc -MD
 * क्रम the build framework.
 *
 * Original author:
 *   Copyright    2002 by Kai Germaschewski  <kai.germaschewski@gmx.de>
 *
 * This code has been borrowed from kbuild's fixdep (scripts/basic/fixdep.c),
 * Please check it क्रम detailed explanation. This fixdep borow only the
 * base transक्रमmation of dependecies without the CONFIG mangle.
 */

#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/mman.h>
#समावेश <unistd.h>
#समावेश <fcntl.h>
#समावेश <माला.स>
#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश <सीमा.स>

अक्षर *target;
अक्षर *depfile;
अक्षर *cmdline;

अटल व्योम usage(व्योम)
अणु
	ख_लिखो(मानक_त्रुटि, "Usage: fixdep <depfile> <target> <cmdline>\n");
	निकास(1);
पूर्ण

/*
 * Prपूर्णांक out the commandline prefixed with cmd_<target filename> :=
 */
अटल व्योम prपूर्णांक_cmdline(व्योम)
अणु
	म_लिखो("cmd_%s := %s\n\n", target, cmdline);
पूर्ण

/*
 * Important: The below generated source_foo.o and deps_foo.o variable
 * assignments are parsed not only by make, but also by the rather simple
 * parser in scripts/mod/sumversion.c.
 */
अटल व्योम parse_dep_file(व्योम *map, माप_प्रकार len)
अणु
	अक्षर *m = map;
	अक्षर *end = m + len;
	अक्षर *p;
	अक्षर s[PATH_MAX];
	पूर्णांक is_target, has_target = 0;
	पूर्णांक saw_any_target = 0;
	पूर्णांक is_first_dep = 0;

	जबतक (m < end) अणु
		/* Skip any "white space" */
		जबतक (m < end && (*m == ' ' || *m == '\\' || *m == '\n'))
			m++;
		/* Find next "white space" */
		p = m;
		जबतक (p < end && *p != ' ' && *p != '\\' && *p != '\n')
			p++;
		/* Is the token we found a target name? */
		is_target = (*(p-1) == ':');
		/* Don't ग_लिखो any target names पूर्णांकo the dependency file */
		अगर (is_target) अणु
			/* The /next/ file is the first dependency */
			is_first_dep = 1;
			has_target = 1;
		पूर्ण अन्यथा अगर (has_target) अणु
			/* Save this token/filename */
			स_नकल(s, m, p-m);
			s[p - m] = 0;

			/*
			 * Do not list the source file as dependency,
			 * so that kbuild is not confused अगर a .c file
			 * is rewritten पूर्णांकo .S or vice versa. Storing
			 * it in source_* is needed क्रम modpost to
			 * compute srcversions.
			 */
			अगर (is_first_dep) अणु
				/*
				 * If processing the concatenation of
				 * multiple dependency files, only
				 * process the first target name, which
				 * will be the original source name,
				 * and ignore any other target names,
				 * which will be पूर्णांकermediate temporary
				 * files.
				 */
				अगर (!saw_any_target) अणु
					saw_any_target = 1;
					म_लिखो("source_%s := %s\n\n",
						target, s);
					म_लिखो("deps_%s := \\\n",
						target);
				पूर्ण
				is_first_dep = 0;
			पूर्ण अन्यथा
				म_लिखो("  %s \\\n", s);
		पूर्ण
		/*
		 * Start searching क्रम next token immediately after the first
		 * "whitespace" अक्षरacter that follows this token.
		 */
		m = p + 1;
	पूर्ण

	अगर (!saw_any_target) अणु
		ख_लिखो(मानक_त्रुटि, "fixdep: parse error; no targets found\n");
		निकास(1);
	पूर्ण

	म_लिखो("\n%s: $(deps_%s)\n\n", target, target);
	म_लिखो("$(deps_%s):\n", target);
पूर्ण

अटल व्योम prपूर्णांक_deps(व्योम)
अणु
	काष्ठा stat st;
	पूर्णांक fd;
	व्योम *map;

	fd = खोलो(depfile, O_RDONLY);
	अगर (fd < 0) अणु
		ख_लिखो(मानक_त्रुटि, "fixdep: error opening depfile: ");
		लिखो_त्रुटि(depfile);
		निकास(2);
	पूर्ण
	अगर (ख_स्थिति(fd, &st) < 0) अणु
		ख_लिखो(मानक_त्रुटि, "fixdep: error fstat'ing depfile: ");
		लिखो_त्रुटि(depfile);
		निकास(2);
	पूर्ण
	अगर (st.st_size == 0) अणु
		ख_लिखो(मानक_त्रुटि, "fixdep: %s is empty\n", depfile);
		बंद(fd);
		वापस;
	पूर्ण
	map = mmap(शून्य, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	अगर ((दीर्घ) map == -1) अणु
		लिखो_त्रुटि("fixdep: mmap");
		बंद(fd);
		वापस;
	पूर्ण

	parse_dep_file(map, st.st_size);

	munmap(map, st.st_size);

	बंद(fd);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	अगर (argc != 4)
		usage();

	depfile = argv[1];
	target  = argv[2];
	cmdline = argv[3];

	prपूर्णांक_cmdline();
	prपूर्णांक_deps();

	वापस 0;
पूर्ण
