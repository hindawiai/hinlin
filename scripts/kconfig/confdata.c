<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2002 Roman Zippel <zippel@linux-m68k.org>
 */

#समावेश <sys/mman.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/types.h>
#समावेश <प्रकार.स>
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <सीमा.स>
#समावेश <मानकतर्क.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <समय.स>
#समावेश <unistd.h>

#समावेश "lkc.h"

/* वापस true अगर 'path' exists, false otherwise */
अटल bool is_present(स्थिर अक्षर *path)
अणु
	काष्ठा stat st;

	वापस !stat(path, &st);
पूर्ण

/* वापस true अगर 'path' exists and it is a directory, false otherwise */
अटल bool is_dir(स्थिर अक्षर *path)
अणु
	काष्ठा stat st;

	अगर (stat(path, &st))
		वापस false;

	वापस S_ISसूची(st.st_mode);
पूर्ण

/* वापस true अगर the given two files are the same, false otherwise */
अटल bool is_same(स्थिर अक्षर *file1, स्थिर अक्षर *file2)
अणु
	पूर्णांक fd1, fd2;
	काष्ठा stat st1, st2;
	व्योम *map1, *map2;
	bool ret = false;

	fd1 = खोलो(file1, O_RDONLY);
	अगर (fd1 < 0)
		वापस ret;

	fd2 = खोलो(file2, O_RDONLY);
	अगर (fd2 < 0)
		जाओ बंद1;

	ret = ख_स्थिति(fd1, &st1);
	अगर (ret)
		जाओ बंद2;
	ret = ख_स्थिति(fd2, &st2);
	अगर (ret)
		जाओ बंद2;

	अगर (st1.st_size != st2.st_size)
		जाओ बंद2;

	map1 = mmap(शून्य, st1.st_size, PROT_READ, MAP_PRIVATE, fd1, 0);
	अगर (map1 == MAP_FAILED)
		जाओ बंद2;

	map2 = mmap(शून्य, st2.st_size, PROT_READ, MAP_PRIVATE, fd2, 0);
	अगर (map2 == MAP_FAILED)
		जाओ बंद2;

	अगर (bcmp(map1, map2, st1.st_size))
		जाओ बंद2;

	ret = true;
बंद2:
	बंद(fd2);
बंद1:
	बंद(fd1);

	वापस ret;
पूर्ण

/*
 * Create the parent directory of the given path.
 *
 * For example, अगर 'include/config/auto.conf' is given, create 'include/config'.
 */
अटल पूर्णांक make_parent_dir(स्थिर अक्षर *path)
अणु
	अक्षर पंचांगp[PATH_MAX + 1];
	अक्षर *p;

	म_नकलन(पंचांगp, path, माप(पंचांगp));
	पंचांगp[माप(पंचांगp) - 1] = 0;

	/* Remove the base name. Just वापस अगर nothing is left */
	p = म_खोजप(पंचांगp, '/');
	अगर (!p)
		वापस 0;
	*(p + 1) = 0;

	/* Just in हाल it is an असलolute path */
	p = पंचांगp;
	जबतक (*p == '/')
		p++;

	जबतक ((p = म_अक्षर(p, '/'))) अणु
		*p = 0;

		/* skip अगर the directory exists */
		अगर (!is_dir(पंचांगp) && सूची_गढ़ो(पंचांगp, 0755))
			वापस -1;

		*p = '/';
		जबतक (*p == '/')
			p++;
	पूर्ण

	वापस 0;
पूर्ण

अटल अक्षर depfile_path[PATH_MAX];
अटल माप_प्रकार depfile_prefix_len;

/* touch depfile क्रम symbol 'name' */
अटल पूर्णांक conf_touch_dep(स्थिर अक्षर *name)
अणु
	पूर्णांक fd, ret;
	अक्षर *d;

	/* check overflow: prefix + name + '\0' must fit in buffer. */
	अगर (depfile_prefix_len + म_माप(name) + 1 > माप(depfile_path))
		वापस -1;

	d = depfile_path + depfile_prefix_len;
	म_नकल(d, name);

	/* Assume directory path alपढ़ोy exists. */
	fd = खोलो(depfile_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	अगर (fd == -1) अणु
		अगर (त्रुटि_सं != ENOENT)
			वापस -1;

		ret = make_parent_dir(depfile_path);
		अगर (ret)
			वापस ret;

		/* Try it again. */
		fd = खोलो(depfile_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		अगर (fd == -1)
			वापस -1;
	पूर्ण
	बंद(fd);

	वापस 0;
पूर्ण

काष्ठा conf_prपूर्णांकer अणु
	व्योम (*prपूर्णांक_symbol)(खाता *, काष्ठा symbol *, स्थिर अक्षर *, व्योम *);
	व्योम (*prपूर्णांक_comment)(खाता *, स्थिर अक्षर *, व्योम *);
पूर्ण;

अटल व्योम conf_warning(स्थिर अक्षर *fmt, ...)
	__attribute__ ((क्रमmat (म_लिखो, 1, 2)));

अटल व्योम conf_message(स्थिर अक्षर *fmt, ...)
	__attribute__ ((क्रमmat (म_लिखो, 1, 2)));

अटल स्थिर अक्षर *conf_filename;
अटल पूर्णांक conf_lineno, conf_warnings;

अटल व्योम conf_warning(स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची ap;
	बहु_शुरू(ap, fmt);
	ख_लिखो(मानक_त्रुटि, "%s:%d:warning: ", conf_filename, conf_lineno);
	भख_लिखो(मानक_त्रुटि, fmt, ap);
	ख_लिखो(मानक_त्रुटि, "\n");
	बहु_पूर्ण(ap);
	conf_warnings++;
पूर्ण

अटल व्योम conf_शेष_message_callback(स्थिर अक्षर *s)
अणु
	म_लिखो("#\n# ");
	म_लिखो("%s", s);
	म_लिखो("\n#\n");
पूर्ण

अटल व्योम (*conf_message_callback)(स्थिर अक्षर *s) =
	conf_शेष_message_callback;
व्योम conf_set_message_callback(व्योम (*fn)(स्थिर अक्षर *s))
अणु
	conf_message_callback = fn;
पूर्ण

अटल व्योम conf_message(स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची ap;
	अक्षर buf[4096];

	अगर (!conf_message_callback)
		वापस;

	बहु_शुरू(ap, fmt);

	vsnम_लिखो(buf, माप(buf), fmt, ap);
	conf_message_callback(buf);
	बहु_पूर्ण(ap);
पूर्ण

स्थिर अक्षर *conf_get_configname(व्योम)
अणु
	अक्षर *name = दो_पर्या("KCONFIG_CONFIG");

	वापस name ? name : ".config";
पूर्ण

अटल स्थिर अक्षर *conf_get_स्वतःconfig_name(व्योम)
अणु
	अक्षर *name = दो_पर्या("KCONFIG_AUTOCONFIG");

	वापस name ? name : "include/config/auto.conf";
पूर्ण

अटल पूर्णांक conf_set_sym_val(काष्ठा symbol *sym, पूर्णांक def, पूर्णांक def_flags, अक्षर *p)
अणु
	अक्षर *p2;

	चयन (sym->type) अणु
	हाल S_TRISTATE:
		अगर (p[0] == 'm') अणु
			sym->def[def].tri = mod;
			sym->flags |= def_flags;
			अवरोध;
		पूर्ण
		/* fall through */
	हाल S_BOOLEAN:
		अगर (p[0] == 'y') अणु
			sym->def[def].tri = yes;
			sym->flags |= def_flags;
			अवरोध;
		पूर्ण
		अगर (p[0] == 'n') अणु
			sym->def[def].tri = no;
			sym->flags |= def_flags;
			अवरोध;
		पूर्ण
		अगर (def != S_DEF_AUTO)
			conf_warning("symbol value '%s' invalid for %s",
				     p, sym->name);
		वापस 1;
	हाल S_STRING:
		अगर (*p++ != '"')
			अवरोध;
		क्रम (p2 = p; (p2 = strpbrk(p2, "\"\\")); p2++) अणु
			अगर (*p2 == '"') अणु
				*p2 = 0;
				अवरोध;
			पूर्ण
			स_हटाओ(p2, p2 + 1, म_माप(p2));
		पूर्ण
		अगर (!p2) अणु
			अगर (def != S_DEF_AUTO)
				conf_warning("invalid string found");
			वापस 1;
		पूर्ण
		/* fall through */
	हाल S_INT:
	हाल S_HEX:
		अगर (sym_string_valid(sym, p)) अणु
			sym->def[def].val = xstrdup(p);
			sym->flags |= def_flags;
		पूर्ण अन्यथा अणु
			अगर (def != S_DEF_AUTO)
				conf_warning("symbol value '%s' invalid for %s",
					     p, sym->name);
			वापस 1;
		पूर्ण
		अवरोध;
	शेष:
		;
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा LINE_GROWTH 16
अटल पूर्णांक add_byte(पूर्णांक c, अक्षर **lineptr, माप_प्रकार slen, माप_प्रकार *n)
अणु
	अक्षर *nline;
	माप_प्रकार new_size = slen + 1;
	अगर (new_size > *n) अणु
		new_size += LINE_GROWTH - 1;
		new_size *= 2;
		nline = xपुनः_स्मृति(*lineptr, new_size);
		अगर (!nline)
			वापस -1;

		*lineptr = nline;
		*n = new_size;
	पूर्ण

	(*lineptr)[slen] = c;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार compat_getline(अक्षर **lineptr, माप_प्रकार *n, खाता *stream)
अणु
	अक्षर *line = *lineptr;
	माप_प्रकार slen = 0;

	क्रम (;;) अणु
		पूर्णांक c = अ_लो(stream);

		चयन (c) अणु
		हाल '\n':
			अगर (add_byte(c, &line, slen, n) < 0)
				जाओ e_out;
			slen++;
			/* fall through */
		हाल खातापूर्ण:
			अगर (add_byte('\0', &line, slen, n) < 0)
				जाओ e_out;
			*lineptr = line;
			अगर (slen == 0)
				वापस -1;
			वापस slen;
		शेष:
			अगर (add_byte(c, &line, slen, n) < 0)
				जाओ e_out;
			slen++;
		पूर्ण
	पूर्ण

e_out:
	line[slen-1] = '\0';
	*lineptr = line;
	वापस -1;
पूर्ण

पूर्णांक conf_पढ़ो_simple(स्थिर अक्षर *name, पूर्णांक def)
अणु
	खाता *in = शून्य;
	अक्षर   *line = शून्य;
	माप_प्रकार  line_asize = 0;
	अक्षर *p, *p2;
	काष्ठा symbol *sym;
	पूर्णांक i, def_flags;

	अगर (name) अणु
		in = zconf_ख_खोलो(name);
	पूर्ण अन्यथा अणु
		अक्षर *env;

		name = conf_get_configname();
		in = zconf_ख_खोलो(name);
		अगर (in)
			जाओ load;
		conf_set_changed(true);

		env = दो_पर्या("KCONFIG_DEFCONFIG_LIST");
		अगर (!env)
			वापस 1;

		जबतक (1) अणु
			bool is_last;

			जबतक (है_खाली(*env))
				env++;

			अगर (!*env)
				अवरोध;

			p = env;
			जबतक (*p && !है_खाली(*p))
				p++;

			is_last = (*p == '\0');

			*p = '\0';

			in = zconf_ख_खोलो(env);
			अगर (in) अणु
				conf_message("using defaults found in %s",
					     env);
				जाओ load;
			पूर्ण

			अगर (is_last)
				अवरोध;

			env = p + 1;
		पूर्ण
	पूर्ण
	अगर (!in)
		वापस 1;

load:
	conf_filename = name;
	conf_lineno = 0;
	conf_warnings = 0;

	def_flags = SYMBOL_DEF << def;
	क्रम_all_symbols(i, sym) अणु
		sym->flags |= SYMBOL_CHANGED;
		sym->flags &= ~(def_flags|SYMBOL_VALID);
		अगर (sym_is_choice(sym))
			sym->flags |= def_flags;
		चयन (sym->type) अणु
		हाल S_INT:
		हाल S_HEX:
		हाल S_STRING:
			अगर (sym->def[def].val)
				मुक्त(sym->def[def].val);
			/* fall through */
		शेष:
			sym->def[def].val = शून्य;
			sym->def[def].tri = no;
		पूर्ण
	पूर्ण

	जबतक (compat_getline(&line, &line_asize, in) != -1) अणु
		conf_lineno++;
		sym = शून्य;
		अगर (line[0] == '#') अणु
			अगर (स_भेद(line + 2, CONFIG_, म_माप(CONFIG_)))
				जारी;
			p = म_अक्षर(line + 2 + म_माप(CONFIG_), ' ');
			अगर (!p)
				जारी;
			*p++ = 0;
			अगर (म_भेदन(p, "is not set", 10))
				जारी;
			अगर (def == S_DEF_USER) अणु
				sym = sym_find(line + 2 + म_माप(CONFIG_));
				अगर (!sym) अणु
					conf_set_changed(true);
					जारी;
				पूर्ण
			पूर्ण अन्यथा अणु
				sym = sym_lookup(line + 2 + म_माप(CONFIG_), 0);
				अगर (sym->type == S_UNKNOWN)
					sym->type = S_BOOLEAN;
			पूर्ण
			अगर (sym->flags & def_flags) अणु
				conf_warning("override: reassigning to symbol %s", sym->name);
			पूर्ण
			चयन (sym->type) अणु
			हाल S_BOOLEAN:
			हाल S_TRISTATE:
				sym->def[def].tri = no;
				sym->flags |= def_flags;
				अवरोध;
			शेष:
				;
			पूर्ण
		पूर्ण अन्यथा अगर (स_भेद(line, CONFIG_, म_माप(CONFIG_)) == 0) अणु
			p = म_अक्षर(line + म_माप(CONFIG_), '=');
			अगर (!p)
				जारी;
			*p++ = 0;
			p2 = म_अक्षर(p, '\n');
			अगर (p2) अणु
				*p2-- = 0;
				अगर (*p2 == '\r')
					*p2 = 0;
			पूर्ण

			sym = sym_find(line + म_माप(CONFIG_));
			अगर (!sym) अणु
				अगर (def == S_DEF_AUTO)
					/*
					 * Reading from include/config/स्वतः.conf
					 * If CONFIG_FOO previously existed in
					 * स्वतः.conf but it is missing now,
					 * include/config/FOO must be touched.
					 */
					conf_touch_dep(line + म_माप(CONFIG_));
				अन्यथा
					conf_set_changed(true);
				जारी;
			पूर्ण

			अगर (sym->flags & def_flags) अणु
				conf_warning("override: reassigning to symbol %s", sym->name);
			पूर्ण
			अगर (conf_set_sym_val(sym, def, def_flags, p))
				जारी;
		पूर्ण अन्यथा अणु
			अगर (line[0] != '\r' && line[0] != '\n')
				conf_warning("unexpected data: %.*s",
					     (पूर्णांक)म_खोज(line, "\r\n"), line);

			जारी;
		पूर्ण

		अगर (sym && sym_is_choice_value(sym)) अणु
			काष्ठा symbol *cs = prop_get_symbol(sym_get_choice_prop(sym));
			चयन (sym->def[def].tri) अणु
			हाल no:
				अवरोध;
			हाल mod:
				अगर (cs->def[def].tri == yes) अणु
					conf_warning("%s creates inconsistent choice state", sym->name);
					cs->flags &= ~def_flags;
				पूर्ण
				अवरोध;
			हाल yes:
				अगर (cs->def[def].tri != no)
					conf_warning("override: %s changes choice state", sym->name);
				cs->def[def].val = sym;
				अवरोध;
			पूर्ण
			cs->def[def].tri = EXPR_OR(cs->def[def].tri, sym->def[def].tri);
		पूर्ण
	पूर्ण
	मुक्त(line);
	ख_बंद(in);
	वापस 0;
पूर्ण

पूर्णांक conf_पढ़ो(स्थिर अक्षर *name)
अणु
	काष्ठा symbol *sym;
	पूर्णांक conf_unsaved = 0;
	पूर्णांक i;

	conf_set_changed(false);

	अगर (conf_पढ़ो_simple(name, S_DEF_USER)) अणु
		sym_calc_value(modules_sym);
		वापस 1;
	पूर्ण

	sym_calc_value(modules_sym);

	क्रम_all_symbols(i, sym) अणु
		sym_calc_value(sym);
		अगर (sym_is_choice(sym) || (sym->flags & SYMBOL_NO_WRITE))
			जारी;
		अगर (sym_has_value(sym) && (sym->flags & SYMBOL_WRITE)) अणु
			/* check that calculated value agrees with saved value */
			चयन (sym->type) अणु
			हाल S_BOOLEAN:
			हाल S_TRISTATE:
				अगर (sym->def[S_DEF_USER].tri == sym_get_tristate_value(sym))
					जारी;
				अवरोध;
			शेष:
				अगर (!म_भेद(sym->curr.val, sym->def[S_DEF_USER].val))
					जारी;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अगर (!sym_has_value(sym) && !(sym->flags & SYMBOL_WRITE))
			/* no previous value and not saved */
			जारी;
		conf_unsaved++;
		/* maybe prपूर्णांक value in verbose mode... */
	पूर्ण

	क्रम_all_symbols(i, sym) अणु
		अगर (sym_has_value(sym) && !sym_is_choice_value(sym)) अणु
			/* Reset values of generates values, so they'll appear
			 * as new, अगर they should become visible, but that
			 * करोesn't quite work अगर the Kconfig and the saved
			 * configuration disagree.
			 */
			अगर (sym->visible == no && !conf_unsaved)
				sym->flags &= ~SYMBOL_DEF_USER;
			चयन (sym->type) अणु
			हाल S_STRING:
			हाल S_INT:
			हाल S_HEX:
				/* Reset a string value अगर it's out of range */
				अगर (sym_string_within_range(sym, sym->def[S_DEF_USER].val))
					अवरोध;
				sym->flags &= ~(SYMBOL_VALID|SYMBOL_DEF_USER);
				conf_unsaved++;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (conf_warnings || conf_unsaved)
		conf_set_changed(true);

	वापस 0;
पूर्ण

/*
 * Kconfig configuration prपूर्णांकer
 *
 * This prपूर्णांकer is used when generating the resulting configuration after
 * kconfig invocation and `defconfig' files. Unset symbol might be omitted by
 * passing a non-शून्य argument to the prपूर्णांकer.
 *
 */
अटल व्योम
kconfig_prपूर्णांक_symbol(खाता *fp, काष्ठा symbol *sym, स्थिर अक्षर *value, व्योम *arg)
अणु

	चयन (sym->type) अणु
	हाल S_BOOLEAN:
	हाल S_TRISTATE:
		अगर (*value == 'n') अणु
			bool skip_unset = (arg != शून्य);

			अगर (!skip_unset)
				ख_लिखो(fp, "# %s%s is not set\n",
				    CONFIG_, sym->name);
			वापस;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	ख_लिखो(fp, "%s%s=%s\n", CONFIG_, sym->name, value);
पूर्ण

अटल व्योम
kconfig_prपूर्णांक_comment(खाता *fp, स्थिर अक्षर *value, व्योम *arg)
अणु
	स्थिर अक्षर *p = value;
	माप_प्रकार l;

	क्रम (;;) अणु
		l = म_खोज(p, "\n");
		ख_लिखो(fp, "#");
		अगर (l) अणु
			ख_लिखो(fp, " ");
			xख_डालो(p, l, 1, fp);
			p += l;
		पूर्ण
		ख_लिखो(fp, "\n");
		अगर (*p++ == '\0')
			अवरोध;
	पूर्ण
पूर्ण

अटल काष्ठा conf_prपूर्णांकer kconfig_prपूर्णांकer_cb =
अणु
	.prपूर्णांक_symbol = kconfig_prपूर्णांक_symbol,
	.prपूर्णांक_comment = kconfig_prपूर्णांक_comment,
पूर्ण;

/*
 * Header prपूर्णांकer
 *
 * This prपूर्णांकer is used when generating the `include/generated/स्वतःconf.h' file.
 */
अटल व्योम
header_prपूर्णांक_symbol(खाता *fp, काष्ठा symbol *sym, स्थिर अक्षर *value, व्योम *arg)
अणु

	चयन (sym->type) अणु
	हाल S_BOOLEAN:
	हाल S_TRISTATE: अणु
		स्थिर अक्षर *suffix = "";

		चयन (*value) अणु
		हाल 'n':
			अवरोध;
		हाल 'm':
			suffix = "_MODULE";
			/* fall through */
		शेष:
			ख_लिखो(fp, "#define %s%s%s 1\n",
			    CONFIG_, sym->name, suffix);
		पूर्ण
		अवरोध;
	पूर्ण
	हाल S_HEX: अणु
		स्थिर अक्षर *prefix = "";

		अगर (value[0] != '0' || (value[1] != 'x' && value[1] != 'X'))
			prefix = "0x";
		ख_लिखो(fp, "#define %s%s %s%s\n",
		    CONFIG_, sym->name, prefix, value);
		अवरोध;
	पूर्ण
	हाल S_STRING:
	हाल S_INT:
		ख_लिखो(fp, "#define %s%s %s\n",
		    CONFIG_, sym->name, value);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

पूर्ण

अटल व्योम
header_prपूर्णांक_comment(खाता *fp, स्थिर अक्षर *value, व्योम *arg)
अणु
	स्थिर अक्षर *p = value;
	माप_प्रकार l;

	ख_लिखो(fp, "/*\n");
	क्रम (;;) अणु
		l = म_खोज(p, "\n");
		ख_लिखो(fp, " *");
		अगर (l) अणु
			ख_लिखो(fp, " ");
			xख_डालो(p, l, 1, fp);
			p += l;
		पूर्ण
		ख_लिखो(fp, "\n");
		अगर (*p++ == '\0')
			अवरोध;
	पूर्ण
	ख_लिखो(fp, " */\n");
पूर्ण

अटल काष्ठा conf_prपूर्णांकer header_prपूर्णांकer_cb =
अणु
	.prपूर्णांक_symbol = header_prपूर्णांक_symbol,
	.prपूर्णांक_comment = header_prपूर्णांक_comment,
पूर्ण;

अटल व्योम conf_ग_लिखो_symbol(खाता *fp, काष्ठा symbol *sym,
			      काष्ठा conf_prपूर्णांकer *prपूर्णांकer, व्योम *prपूर्णांकer_arg)
अणु
	स्थिर अक्षर *str;

	चयन (sym->type) अणु
	हाल S_UNKNOWN:
		अवरोध;
	हाल S_STRING:
		str = sym_get_string_value(sym);
		str = sym_escape_string_value(str);
		prपूर्णांकer->prपूर्णांक_symbol(fp, sym, str, prपूर्णांकer_arg);
		मुक्त((व्योम *)str);
		अवरोध;
	शेष:
		str = sym_get_string_value(sym);
		prपूर्णांकer->prपूर्णांक_symbol(fp, sym, str, prपूर्णांकer_arg);
	पूर्ण
पूर्ण

अटल व्योम
conf_ग_लिखो_heading(खाता *fp, काष्ठा conf_prपूर्णांकer *prपूर्णांकer, व्योम *prपूर्णांकer_arg)
अणु
	अक्षर buf[256];

	snम_लिखो(buf, माप(buf),
	    "\n"
	    "Automatically generated file; DO NOT EDIT.\n"
	    "%s\n",
	    rooपंचांगenu.prompt->text);

	prपूर्णांकer->prपूर्णांक_comment(fp, buf, prपूर्णांकer_arg);
पूर्ण

/*
 * Write out a minimal config.
 * All values that has शेष values are skipped as this is redundant.
 */
पूर्णांक conf_ग_लिखो_defconfig(स्थिर अक्षर *filename)
अणु
	काष्ठा symbol *sym;
	काष्ठा menu *menu;
	खाता *out;

	out = ख_खोलो(filename, "w");
	अगर (!out)
		वापस 1;

	sym_clear_all_valid();

	/* Traverse all menus to find all relevant symbols */
	menu = rooपंचांगenu.list;

	जबतक (menu != शून्य)
	अणु
		sym = menu->sym;
		अगर (sym == शून्य) अणु
			अगर (!menu_is_visible(menu))
				जाओ next_menu;
		पूर्ण अन्यथा अगर (!sym_is_choice(sym)) अणु
			sym_calc_value(sym);
			अगर (!(sym->flags & SYMBOL_WRITE))
				जाओ next_menu;
			sym->flags &= ~SYMBOL_WRITE;
			/* If we cannot change the symbol - skip */
			अगर (!sym_is_changeable(sym))
				जाओ next_menu;
			/* If symbol equals to शेष value - skip */
			अगर (म_भेद(sym_get_string_value(sym), sym_get_string_शेष(sym)) == 0)
				जाओ next_menu;

			/*
			 * If symbol is a choice value and equals to the
			 * शेष क्रम a choice - skip.
			 * But only अगर value is bool and equal to "y" and
			 * choice is not "optional".
			 * (If choice is "optional" then all values can be "n")
			 */
			अगर (sym_is_choice_value(sym)) अणु
				काष्ठा symbol *cs;
				काष्ठा symbol *ds;

				cs = prop_get_symbol(sym_get_choice_prop(sym));
				ds = sym_choice_शेष(cs);
				अगर (!sym_is_optional(cs) && sym == ds) अणु
					अगर ((sym->type == S_BOOLEAN) &&
					    sym_get_tristate_value(sym) == yes)
						जाओ next_menu;
				पूर्ण
			पूर्ण
			conf_ग_लिखो_symbol(out, sym, &kconfig_prपूर्णांकer_cb, शून्य);
		पूर्ण
next_menu:
		अगर (menu->list != शून्य) अणु
			menu = menu->list;
		पूर्ण
		अन्यथा अगर (menu->next != शून्य) अणु
			menu = menu->next;
		पूर्ण अन्यथा अणु
			जबतक ((menu = menu->parent)) अणु
				अगर (menu->next != शून्य) अणु
					menu = menu->next;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	ख_बंद(out);
	वापस 0;
पूर्ण

पूर्णांक conf_ग_लिखो(स्थिर अक्षर *name)
अणु
	खाता *out;
	काष्ठा symbol *sym;
	काष्ठा menu *menu;
	स्थिर अक्षर *str;
	अक्षर क्षणिकe[PATH_MAX + 1], oldname[PATH_MAX + 1];
	अक्षर *env;
	पूर्णांक i;
	bool need_newline = false;

	अगर (!name)
		name = conf_get_configname();

	अगर (!*name) अणु
		ख_लिखो(मानक_त्रुटि, "config name is empty\n");
		वापस -1;
	पूर्ण

	अगर (is_dir(name)) अणु
		ख_लिखो(मानक_त्रुटि, "%s: Is a directory\n", name);
		वापस -1;
	पूर्ण

	अगर (make_parent_dir(name))
		वापस -1;

	env = दो_पर्या("KCONFIG_OVERWRITECONFIG");
	अगर (env && *env) अणु
		*क्षणिकe = 0;
		out = ख_खोलो(name, "w");
	पूर्ण अन्यथा अणु
		snम_लिखो(क्षणिकe, माप(क्षणिकe), "%s.%d.tmp",
			 name, (पूर्णांक)getpid());
		out = ख_खोलो(क्षणिकe, "w");
	पूर्ण
	अगर (!out)
		वापस 1;

	conf_ग_लिखो_heading(out, &kconfig_prपूर्णांकer_cb, शून्य);

	अगर (!conf_get_changed())
		sym_clear_all_valid();

	menu = rooपंचांगenu.list;
	जबतक (menu) अणु
		sym = menu->sym;
		अगर (!sym) अणु
			अगर (!menu_is_visible(menu))
				जाओ next;
			str = menu_get_prompt(menu);
			ख_लिखो(out, "\n"
				     "#\n"
				     "# %s\n"
				     "#\n", str);
			need_newline = false;
		पूर्ण अन्यथा अगर (!(sym->flags & SYMBOL_CHOICE) &&
			   !(sym->flags & SYMBOL_WRITTEN)) अणु
			sym_calc_value(sym);
			अगर (!(sym->flags & SYMBOL_WRITE))
				जाओ next;
			अगर (need_newline) अणु
				ख_लिखो(out, "\n");
				need_newline = false;
			पूर्ण
			sym->flags |= SYMBOL_WRITTEN;
			conf_ग_लिखो_symbol(out, sym, &kconfig_prपूर्णांकer_cb, शून्य);
		पूर्ण

next:
		अगर (menu->list) अणु
			menu = menu->list;
			जारी;
		पूर्ण
		अगर (menu->next)
			menu = menu->next;
		अन्यथा जबतक ((menu = menu->parent)) अणु
			अगर (!menu->sym && menu_is_visible(menu) &&
			    menu != &rooपंचांगenu) अणु
				str = menu_get_prompt(menu);
				ख_लिखो(out, "# end of %s\n", str);
				need_newline = true;
			पूर्ण
			अगर (menu->next) अणु
				menu = menu->next;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	ख_बंद(out);

	क्रम_all_symbols(i, sym)
		sym->flags &= ~SYMBOL_WRITTEN;

	अगर (*क्षणिकe) अणु
		अगर (is_same(name, क्षणिकe)) अणु
			conf_message("No change to %s", name);
			unlink(क्षणिकe);
			conf_set_changed(false);
			वापस 0;
		पूर्ण

		snम_लिखो(oldname, माप(oldname), "%s.old", name);
		नाम(name, oldname);
		अगर (नाम(क्षणिकe, name))
			वापस 1;
	पूर्ण

	conf_message("configuration written to %s", name);

	conf_set_changed(false);

	वापस 0;
पूर्ण

/* ग_लिखो a dependency file as used by kbuild to track dependencies */
अटल पूर्णांक conf_ग_लिखो_dep(स्थिर अक्षर *name)
अणु
	काष्ठा file *file;
	खाता *out;

	out = ख_खोलो("..config.tmp", "w");
	अगर (!out)
		वापस 1;
	ख_लिखो(out, "deps_config := \\\n");
	क्रम (file = file_list; file; file = file->next) अणु
		अगर (file->next)
			ख_लिखो(out, "\t%s \\\n", file->name);
		अन्यथा
			ख_लिखो(out, "\t%s\n", file->name);
	पूर्ण
	ख_लिखो(out, "\n%s: \\\n"
		     "\t$(deps_config)\n\n", conf_get_स्वतःconfig_name());

	env_ग_लिखो_dep(out, conf_get_स्वतःconfig_name());

	ख_लिखो(out, "\n$(deps_config): ;\n");
	ख_बंद(out);

	अगर (make_parent_dir(name))
		वापस 1;
	नाम("..config.tmp", name);
	वापस 0;
पूर्ण

अटल पूर्णांक conf_touch_deps(व्योम)
अणु
	स्थिर अक्षर *name;
	काष्ठा symbol *sym;
	पूर्णांक res, i;

	म_नकल(depfile_path, "include/config/");
	depfile_prefix_len = म_माप(depfile_path);

	name = conf_get_स्वतःconfig_name();
	conf_पढ़ो_simple(name, S_DEF_AUTO);
	sym_calc_value(modules_sym);

	क्रम_all_symbols(i, sym) अणु
		sym_calc_value(sym);
		अगर ((sym->flags & SYMBOL_NO_WRITE) || !sym->name)
			जारी;
		अगर (sym->flags & SYMBOL_WRITE) अणु
			अगर (sym->flags & SYMBOL_DEF_AUTO) अणु
				/*
				 * symbol has old and new value,
				 * so compare them...
				 */
				चयन (sym->type) अणु
				हाल S_BOOLEAN:
				हाल S_TRISTATE:
					अगर (sym_get_tristate_value(sym) ==
					    sym->def[S_DEF_AUTO].tri)
						जारी;
					अवरोध;
				हाल S_STRING:
				हाल S_HEX:
				हाल S_INT:
					अगर (!म_भेद(sym_get_string_value(sym),
						    sym->def[S_DEF_AUTO].val))
						जारी;
					अवरोध;
				शेष:
					अवरोध;
				पूर्ण
			पूर्ण अन्यथा अणु
				/*
				 * If there is no old value, only 'no' (unset)
				 * is allowed as new value.
				 */
				चयन (sym->type) अणु
				हाल S_BOOLEAN:
				हाल S_TRISTATE:
					अगर (sym_get_tristate_value(sym) == no)
						जारी;
					अवरोध;
				शेष:
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अगर (!(sym->flags & SYMBOL_DEF_AUTO))
			/* There is neither an old nor a new value. */
			जारी;
		/* अन्यथा
		 *	There is an old value, but no new value ('no' (unset)
		 *	isn't saved in स्वतः.conf, so the old value is always
		 *	dअगरferent from 'no').
		 */

		res = conf_touch_dep(sym->name);
		अगर (res)
			वापस res;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक conf_ग_लिखो_स्वतःconf(पूर्णांक overग_लिखो)
अणु
	काष्ठा symbol *sym;
	स्थिर अक्षर *name;
	स्थिर अक्षर *स्वतःconf_name = conf_get_स्वतःconfig_name();
	खाता *out, *out_h;
	पूर्णांक i;

	अगर (!overग_लिखो && is_present(स्वतःconf_name))
		वापस 0;

	conf_ग_लिखो_dep("include/config/auto.conf.cmd");

	अगर (conf_touch_deps())
		वापस 1;

	out = ख_खोलो(".tmpconfig", "w");
	अगर (!out)
		वापस 1;

	out_h = ख_खोलो(".tmpconfig.h", "w");
	अगर (!out_h) अणु
		ख_बंद(out);
		वापस 1;
	पूर्ण

	conf_ग_लिखो_heading(out, &kconfig_prपूर्णांकer_cb, शून्य);
	conf_ग_लिखो_heading(out_h, &header_prपूर्णांकer_cb, शून्य);

	क्रम_all_symbols(i, sym) अणु
		sym_calc_value(sym);
		अगर (!(sym->flags & SYMBOL_WRITE) || !sym->name)
			जारी;

		/* ग_लिखो symbols to स्वतः.conf and स्वतःconf.h */
		conf_ग_लिखो_symbol(out, sym, &kconfig_prपूर्णांकer_cb, (व्योम *)1);
		conf_ग_लिखो_symbol(out_h, sym, &header_prपूर्णांकer_cb, शून्य);
	पूर्ण
	ख_बंद(out);
	ख_बंद(out_h);

	name = दो_पर्या("KCONFIG_AUTOHEADER");
	अगर (!name)
		name = "include/generated/autoconf.h";
	अगर (make_parent_dir(name))
		वापस 1;
	अगर (नाम(".tmpconfig.h", name))
		वापस 1;

	अगर (make_parent_dir(स्वतःconf_name))
		वापस 1;
	/*
	 * This must be the last step, kbuild has a dependency on स्वतः.conf
	 * and this marks the successful completion of the previous steps.
	 */
	अगर (नाम(".tmpconfig", स्वतःconf_name))
		वापस 1;

	वापस 0;
पूर्ण

अटल bool conf_changed;
अटल व्योम (*conf_changed_callback)(व्योम);

व्योम conf_set_changed(bool val)
अणु
	अगर (conf_changed_callback && conf_changed != val)
		conf_changed_callback();

	conf_changed = val;
पूर्ण

bool conf_get_changed(व्योम)
अणु
	वापस conf_changed;
पूर्ण

व्योम conf_set_changed_callback(व्योम (*fn)(व्योम))
अणु
	conf_changed_callback = fn;
पूर्ण

व्योम set_all_choice_values(काष्ठा symbol *csym)
अणु
	काष्ठा property *prop;
	काष्ठा symbol *sym;
	काष्ठा expr *e;

	prop = sym_get_choice_prop(csym);

	/*
	 * Set all non-assinged choice values to no
	 */
	expr_list_क्रम_each_sym(prop->expr, e, sym) अणु
		अगर (!sym_has_value(sym))
			sym->def[S_DEF_USER].tri = no;
	पूर्ण
	csym->flags |= SYMBOL_DEF_USER;
	/* clear VALID to get value calculated */
	csym->flags &= ~(SYMBOL_VALID | SYMBOL_NEED_SET_CHOICE_VALUES);
पूर्ण
