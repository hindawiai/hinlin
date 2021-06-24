<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/fs/binfmt_script.c
 *
 *  Copyright (C) 1996  Martin von Lथघwis
 *  original #!-checking implemented by tytso.
 */

#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/स्थिति.स>
#समावेश <linux/binfmts.h>
#समावेश <linux/init.h>
#समावेश <linux/file.h>
#समावेश <linux/err.h>
#समावेश <linux/fs.h>

अटल अंतरभूत bool spacetab(अक्षर c) अणु वापस c == ' ' || c == '\t'; पूर्ण
अटल अंतरभूत स्थिर अक्षर *next_non_spacetab(स्थिर अक्षर *first, स्थिर अक्षर *last)
अणु
	क्रम (; first <= last; first++)
		अगर (!spacetab(*first))
			वापस first;
	वापस शून्य;
पूर्ण
अटल अंतरभूत स्थिर अक्षर *next_terminator(स्थिर अक्षर *first, स्थिर अक्षर *last)
अणु
	क्रम (; first <= last; first++)
		अगर (spacetab(*first) || !*first)
			वापस first;
	वापस शून्य;
पूर्ण

अटल पूर्णांक load_script(काष्ठा linux_binprm *bprm)
अणु
	स्थिर अक्षर *i_name, *i_sep, *i_arg, *i_end, *buf_end;
	काष्ठा file *file;
	पूर्णांक retval;

	/* Not ours to exec अगर we करोn't start with "#!". */
	अगर ((bprm->buf[0] != '#') || (bprm->buf[1] != '!'))
		वापस -ENOEXEC;

	/*
	 * This section handles parsing the #! line पूर्णांकo separate
	 * पूर्णांकerpreter path and argument strings. We must be careful
	 * because bprm->buf is not yet guaranteed to be NUL-terminated
	 * (though the buffer will have trailing NUL padding when the
	 * file size was smaller than the buffer size).
	 *
	 * We करो not want to exec a truncated पूर्णांकerpreter path, so either
	 * we find a newline (which indicates nothing is truncated), or
	 * we find a space/tab/NUL after the पूर्णांकerpreter path (which
	 * itself may be preceded by spaces/tअसल). Truncating the
	 * arguments is fine: the पूर्णांकerpreter can re-पढ़ो the script to
	 * parse them on its own.
	 */
	buf_end = bprm->buf + माप(bprm->buf) - 1;
	i_end = strnchr(bprm->buf, माप(bprm->buf), '\n');
	अगर (!i_end) अणु
		i_end = next_non_spacetab(bprm->buf + 2, buf_end);
		अगर (!i_end)
			वापस -ENOEXEC; /* Entire buf is spaces/tअसल */
		/*
		 * If there is no later space/tab/NUL we must assume the
		 * पूर्णांकerpreter path is truncated.
		 */
		अगर (!next_terminator(i_end, buf_end))
			वापस -ENOEXEC;
		i_end = buf_end;
	पूर्ण
	/* Trim any trailing spaces/tअसल from i_end */
	जबतक (spacetab(i_end[-1]))
		i_end--;

	/* Skip over leading spaces/tअसल */
	i_name = next_non_spacetab(bprm->buf+2, i_end);
	अगर (!i_name || (i_name == i_end))
		वापस -ENOEXEC; /* No पूर्णांकerpreter name found */

	/* Is there an optional argument? */
	i_arg = शून्य;
	i_sep = next_terminator(i_name, i_end);
	अगर (i_sep && (*i_sep != '\0'))
		i_arg = next_non_spacetab(i_sep, i_end);

	/*
	 * If the script filename will be inaccessible after exec, typically
	 * because it is a "/dev/fd/<fd>/.." path against an O_CLOEXEC fd, give
	 * up now (on the assumption that the पूर्णांकerpreter will want to load
	 * this file).
	 */
	अगर (bprm->पूर्णांकerp_flags & BINPRM_FLAGS_PATH_INACCESSIBLE)
		वापस -ENOENT;

	/*
	 * OK, we've parsed out the पूर्णांकerpreter name and
	 * (optional) argument.
	 * Splice in (1) the पूर्णांकerpreter's name क्रम argv[0]
	 *           (2) (optional) argument to पूर्णांकerpreter
	 *           (3) filename of shell script (replace argv[0])
	 *
	 * This is करोne in reverse order, because of how the
	 * user environment and arguments are stored.
	 */
	retval = हटाओ_arg_zero(bprm);
	अगर (retval)
		वापस retval;
	retval = copy_string_kernel(bprm->पूर्णांकerp, bprm);
	अगर (retval < 0)
		वापस retval;
	bprm->argc++;
	*((अक्षर *)i_end) = '\0';
	अगर (i_arg) अणु
		*((अक्षर *)i_sep) = '\0';
		retval = copy_string_kernel(i_arg, bprm);
		अगर (retval < 0)
			वापस retval;
		bprm->argc++;
	पूर्ण
	retval = copy_string_kernel(i_name, bprm);
	अगर (retval)
		वापस retval;
	bprm->argc++;
	retval = bprm_change_पूर्णांकerp(i_name, bprm);
	अगर (retval < 0)
		वापस retval;

	/*
	 * OK, now restart the process with the पूर्णांकerpreter's dentry.
	 */
	file = खोलो_exec(i_name);
	अगर (IS_ERR(file))
		वापस PTR_ERR(file);

	bprm->पूर्णांकerpreter = file;
	वापस 0;
पूर्ण

अटल काष्ठा linux_binfmt script_क्रमmat = अणु
	.module		= THIS_MODULE,
	.load_binary	= load_script,
पूर्ण;

अटल पूर्णांक __init init_script_binfmt(व्योम)
अणु
	रेजिस्टर_binfmt(&script_क्रमmat);
	वापस 0;
पूर्ण

अटल व्योम __निकास निकास_script_binfmt(व्योम)
अणु
	unरेजिस्टर_binfmt(&script_क्रमmat);
पूर्ण

core_initcall(init_script_binfmt);
module_निकास(निकास_script_binfmt);
MODULE_LICENSE("GPL");
