<शैली गुरु>
/*
 * "Optimize" a list of dependencies as spit out by gcc -MD
 * क्रम the kernel build
 * ===========================================================================
 *
 * Author       Kai Germaschewski
 * Copyright    2002 by Kai Germaschewski  <kai.germaschewski@gmx.de>
 *
 * This software may be used and distributed according to the terms
 * of the GNU General Public License, incorporated herein by reference.
 *
 *
 * Introduction:
 *
 * gcc produces a very nice and correct list of dependencies which
 * tells make when to remake a file.
 *
 * To use this list as-is however has the drawback that भवly
 * every file in the kernel includes स्वतःconf.h.
 *
 * If the user re-runs make *config, स्वतःconf.h will be
 * regenerated.  make notices that and will rebuild every file which
 * includes स्वतःconf.h, i.e. basically all files. This is extremely
 * annoying अगर the user just changed CONFIG_HIS_DRIVER from n to m.
 *
 * So we play the same trick that "mkdep" played beक्रमe. We replace
 * the dependency on स्वतःconf.h by a dependency on every config
 * option which is mentioned in any of the listed prerequisites.
 *
 * kconfig populates a tree in include/config/ with an empty file
 * क्रम each config symbol and when the configuration is updated
 * the files representing changed config options are touched
 * which then let make pick up the changes and the files that use
 * the config symbols are rebuilt.
 *
 * So अगर the user changes his CONFIG_HIS_DRIVER option, only the objects
 * which depend on "include/config/HIS_DRIVER" will be rebuilt,
 * so most likely only his driver ;-)
 *
 * The idea above dates, by the way, back to Michael E Chastain, AFAIK.
 *
 * So to get dependencies right, there are two issues:
 * o अगर any of the files the compiler पढ़ो changed, we need to rebuild
 * o अगर the command line given to the compile the file changed, we
 *   better rebuild as well.
 *
 * The क्रमmer is handled by using the -MD output, the later by saving
 * the command line used to compile the old object and comparing it
 * to the one we would now use.
 *
 * Again, also this idea is pretty old and has been discussed on
 * kbuild-devel a दीर्घ समय ago. I करोn't have a sensibly working
 * पूर्णांकernet connection right now, so I rather करोn't mention names
 * without द्विगुन checking.
 *
 * This code here has been based partially based on mkdep.c, which
 * says the following about its history:
 *
 *   Copyright abanकरोned, Michael Chastain, <mailto:mec@shout.net>.
 *   This is a C version of syncdep.pl by Werner Almesberger.
 *
 *
 * It is invoked as
 *
 *   fixdep <depfile> <target> <cmdline>
 *
 * and will पढ़ो the dependency file <depfile>
 *
 * The transक्रमmed dependency snipped is written to मानक_निकास.
 *
 * It first generates a line
 *
 *   cmd_<target> = <cmdline>
 *
 * and then basically copies the .<target>.d file to मानक_निकास, in the
 * process filtering out the dependency on स्वतःconf.h and adding
 * dependencies on include/config/MY_OPTION क्रम every
 * CONFIG_MY_OPTION encountered in any of the prerequisites.
 *
 * We करोn't even try to really parse the header files, but
 * merely grep, i.e. अगर CONFIG_FOO is mentioned in a comment, it will
 * be picked up as well. It's not a problem with respect to
 * correctness, since that can only give too many dependencies, thus
 * we cannot miss a rebuild. Since people tend to not mention totally
 * unrelated CONFIG_ options all over the place, it's not an
 * efficiency problem either.
 *
 * (Note: it'd be easy to port over the complete mkdep state machine,
 *  but I करोn't think the added complनिकासy is worth it)
 */

#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <unistd.h>
#समावेश <fcntl.h>
#समावेश <माला.स>
#समावेश <मानकतर्क.स>
#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश <प्रकार.स>

अटल व्योम usage(व्योम)
अणु
	ख_लिखो(मानक_त्रुटि, "Usage: fixdep <depfile> <target> <cmdline>\n");
	निकास(1);
पूर्ण

/*
 * In the पूर्णांकended usage of this program, the मानक_निकास is redirected to .*.cmd
 * files. The वापस value of म_लिखो() must be checked to catch any error,
 * e.g. "No space left on device".
 */
अटल व्योम xम_लिखो(स्थिर अक्षर *क्रमmat, ...)
अणु
	बहु_सूची ap;
	पूर्णांक ret;

	बहु_शुरू(ap, क्रमmat);
	ret = भ_लिखो(क्रमmat, ap);
	अगर (ret < 0) अणु
		लिखो_त्रुटि("fixdep");
		निकास(1);
	पूर्ण
	बहु_पूर्ण(ap);
पूर्ण

काष्ठा item अणु
	काष्ठा item	*next;
	अचिन्हित पूर्णांक	len;
	अचिन्हित पूर्णांक	hash;
	अक्षर		name[];
पूर्ण;

#घोषणा HASHSZ 256
अटल काष्ठा item *hashtab[HASHSZ];

अटल अचिन्हित पूर्णांक strhash(स्थिर अक्षर *str, अचिन्हित पूर्णांक sz)
अणु
	/* fnv32 hash */
	अचिन्हित पूर्णांक i, hash = 2166136261U;

	क्रम (i = 0; i < sz; i++)
		hash = (hash ^ str[i]) * 0x01000193;
	वापस hash;
पूर्ण

/*
 * Lookup a value in the configuration string.
 */
अटल पूर्णांक is_defined_config(स्थिर अक्षर *name, पूर्णांक len, अचिन्हित पूर्णांक hash)
अणु
	काष्ठा item *aux;

	क्रम (aux = hashtab[hash % HASHSZ]; aux; aux = aux->next) अणु
		अगर (aux->hash == hash && aux->len == len &&
		    स_भेद(aux->name, name, len) == 0)
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Add a new value to the configuration string.
 */
अटल व्योम define_config(स्थिर अक्षर *name, पूर्णांक len, अचिन्हित पूर्णांक hash)
अणु
	काष्ठा item *aux = दो_स्मृति(माप(*aux) + len);

	अगर (!aux) अणु
		लिखो_त्रुटि("fixdep:malloc");
		निकास(1);
	पूर्ण
	स_नकल(aux->name, name, len);
	aux->len = len;
	aux->hash = hash;
	aux->next = hashtab[hash % HASHSZ];
	hashtab[hash % HASHSZ] = aux;
पूर्ण

/*
 * Record the use of a CONFIG_* word.
 */
अटल व्योम use_config(स्थिर अक्षर *m, पूर्णांक slen)
अणु
	अचिन्हित पूर्णांक hash = strhash(m, slen);

	अगर (is_defined_config(m, slen, hash))
	    वापस;

	define_config(m, slen, hash);
	/* Prपूर्णांक out a dependency path from a symbol name. */
	xम_लिखो("    $(wildcard include/config/%.*s) \\\n", slen, m);
पूर्ण

/* test अगर s ends in sub */
अटल पूर्णांक str_ends_with(स्थिर अक्षर *s, पूर्णांक slen, स्थिर अक्षर *sub)
अणु
	पूर्णांक sublen = म_माप(sub);

	अगर (sublen > slen)
		वापस 0;

	वापस !स_भेद(s + slen - sublen, sub, sublen);
पूर्ण

अटल व्योम parse_config_file(स्थिर अक्षर *p)
अणु
	स्थिर अक्षर *q, *r;
	स्थिर अक्षर *start = p;

	जबतक ((p = म_माला(p, "CONFIG_"))) अणु
		अगर (p > start && (है_अक्षर_अंक(p[-1]) || p[-1] == '_')) अणु
			p += 7;
			जारी;
		पूर्ण
		p += 7;
		q = p;
		जबतक (है_अक्षर_अंक(*q) || *q == '_')
			q++;
		अगर (str_ends_with(p, q - p, "_MODULE"))
			r = q - 7;
		अन्यथा
			r = q;
		अगर (r > p)
			use_config(p, r - p);
		p = q;
	पूर्ण
पूर्ण

अटल व्योम *पढ़ो_file(स्थिर अक्षर *filename)
अणु
	काष्ठा stat st;
	पूर्णांक fd;
	अक्षर *buf;

	fd = खोलो(filename, O_RDONLY);
	अगर (fd < 0) अणु
		ख_लिखो(मानक_त्रुटि, "fixdep: error opening file: ");
		लिखो_त्रुटि(filename);
		निकास(2);
	पूर्ण
	अगर (ख_स्थिति(fd, &st) < 0) अणु
		ख_लिखो(मानक_त्रुटि, "fixdep: error fstat'ing file: ");
		लिखो_त्रुटि(filename);
		निकास(2);
	पूर्ण
	buf = दो_स्मृति(st.st_size + 1);
	अगर (!buf) अणु
		लिखो_त्रुटि("fixdep: malloc");
		निकास(2);
	पूर्ण
	अगर (पढ़ो(fd, buf, st.st_size) != st.st_size) अणु
		लिखो_त्रुटि("fixdep: read");
		निकास(2);
	पूर्ण
	buf[st.st_size] = '\0';
	बंद(fd);

	वापस buf;
पूर्ण

/* Ignore certain dependencies */
अटल पूर्णांक is_ignored_file(स्थिर अक्षर *s, पूर्णांक len)
अणु
	वापस str_ends_with(s, len, "include/generated/autoconf.h") ||
	       str_ends_with(s, len, "include/generated/autoksyms.h");
पूर्ण

/*
 * Important: The below generated source_foo.o and deps_foo.o variable
 * assignments are parsed not only by make, but also by the rather simple
 * parser in scripts/mod/sumversion.c.
 */
अटल व्योम parse_dep_file(अक्षर *m, स्थिर अक्षर *target)
अणु
	अक्षर *p;
	पूर्णांक is_last, is_target;
	पूर्णांक saw_any_target = 0;
	पूर्णांक is_first_dep = 0;
	व्योम *buf;

	जबतक (1) अणु
		/* Skip any "white space" */
		जबतक (*m == ' ' || *m == '\\' || *m == '\n')
			m++;

		अगर (!*m)
			अवरोध;

		/* Find next "white space" */
		p = m;
		जबतक (*p && *p != ' ' && *p != '\\' && *p != '\n')
			p++;
		is_last = (*p == '\0');
		/* Is the token we found a target name? */
		is_target = (*(p-1) == ':');
		/* Don't ग_लिखो any target names पूर्णांकo the dependency file */
		अगर (is_target) अणु
			/* The /next/ file is the first dependency */
			is_first_dep = 1;
		पूर्ण अन्यथा अगर (!is_ignored_file(m, p - m)) अणु
			*p = '\0';

			/*
			 * Do not list the source file as dependency, so that
			 * kbuild is not confused अगर a .c file is rewritten
			 * पूर्णांकo .S or vice versa. Storing it in source_* is
			 * needed क्रम modpost to compute srcversions.
			 */
			अगर (is_first_dep) अणु
				/*
				 * If processing the concatenation of multiple
				 * dependency files, only process the first
				 * target name, which will be the original
				 * source name, and ignore any other target
				 * names, which will be पूर्णांकermediate temporary
				 * files.
				 */
				अगर (!saw_any_target) अणु
					saw_any_target = 1;
					xम_लिखो("source_%s := %s\n\n",
						target, m);
					xम_लिखो("deps_%s := \\\n", target);
				पूर्ण
				is_first_dep = 0;
			पूर्ण अन्यथा अणु
				xम_लिखो("  %s \\\n", m);
			पूर्ण

			buf = पढ़ो_file(m);
			parse_config_file(buf);
			मुक्त(buf);
		पूर्ण

		अगर (is_last)
			अवरोध;

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

	xम_लिखो("\n%s: $(deps_%s)\n\n", target, target);
	xम_लिखो("$(deps_%s):\n", target);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	स्थिर अक्षर *depfile, *target, *cmdline;
	व्योम *buf;

	अगर (argc != 4)
		usage();

	depfile = argv[1];
	target = argv[2];
	cmdline = argv[3];

	xम_लिखो("cmd_%s := %s\n\n", target, cmdline);

	buf = पढ़ो_file(depfile);
	parse_dep_file(buf, target);
	मुक्त(buf);

	वापस 0;
पूर्ण
