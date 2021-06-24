<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * debug.c - NTFS kernel debug support. Part of the Linux-NTFS project.
 *
 * Copyright (c) 2001-2004 Anton Altaparmakov
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश "debug.h"

/**
 * __ntfs_warning - output a warning to the syslog
 * @function:	name of function outputting the warning
 * @sb:		super block of mounted ntfs fileप्रणाली
 * @fmt:	warning string containing क्रमmat specअगरications
 * @...:	a variable number of arguments specअगरied in @fmt
 *
 * Outमाला_दो a warning to the syslog क्रम the mounted ntfs fileप्रणाली described
 * by @sb.
 *
 * @fmt and the corresponding @... is म_लिखो style क्रमmat string containing
 * the warning string and the corresponding क्रमmat arguments, respectively.
 *
 * @function is the name of the function from which __ntfs_warning is being
 * called.
 *
 * Note, you should be using debug.h::ntfs_warning(@sb, @fmt, @...) instead
 * as this provides the @function parameter स्वतःmatically.
 */
व्योम __ntfs_warning(स्थिर अक्षर *function, स्थिर काष्ठा super_block *sb,
		स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;
	पूर्णांक flen = 0;

#अगर_अघोषित DEBUG
	अगर (!prपूर्णांकk_ratelimit())
		वापस;
#पूर्ण_अगर
	अगर (function)
		flen = म_माप(function);
	बहु_शुरू(args, fmt);
	vaf.fmt = fmt;
	vaf.va = &args;
	अगर (sb)
		pr_warn("(device %s): %s(): %pV\n",
			sb->s_id, flen ? function : "", &vaf);
	अन्यथा
		pr_warn("%s(): %pV\n", flen ? function : "", &vaf);
	बहु_पूर्ण(args);
पूर्ण

/**
 * __ntfs_error - output an error to the syslog
 * @function:	name of function outputting the error
 * @sb:		super block of mounted ntfs fileप्रणाली
 * @fmt:	error string containing क्रमmat specअगरications
 * @...:	a variable number of arguments specअगरied in @fmt
 *
 * Outमाला_दो an error to the syslog क्रम the mounted ntfs fileप्रणाली described
 * by @sb.
 *
 * @fmt and the corresponding @... is म_लिखो style क्रमmat string containing
 * the error string and the corresponding क्रमmat arguments, respectively.
 *
 * @function is the name of the function from which __ntfs_error is being
 * called.
 *
 * Note, you should be using debug.h::ntfs_error(@sb, @fmt, @...) instead
 * as this provides the @function parameter स्वतःmatically.
 */
व्योम __ntfs_error(स्थिर अक्षर *function, स्थिर काष्ठा super_block *sb,
		स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;
	पूर्णांक flen = 0;

#अगर_अघोषित DEBUG
	अगर (!prपूर्णांकk_ratelimit())
		वापस;
#पूर्ण_अगर
	अगर (function)
		flen = म_माप(function);
	बहु_शुरू(args, fmt);
	vaf.fmt = fmt;
	vaf.va = &args;
	अगर (sb)
		pr_err("(device %s): %s(): %pV\n",
		       sb->s_id, flen ? function : "", &vaf);
	अन्यथा
		pr_err("%s(): %pV\n", flen ? function : "", &vaf);
	बहु_पूर्ण(args);
पूर्ण

#अगर_घोषित DEBUG

/* If 1, output debug messages, and अगर 0, करोn't. */
पूर्णांक debug_msgs = 0;

व्योम __ntfs_debug(स्थिर अक्षर *file, पूर्णांक line, स्थिर अक्षर *function,
		स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;
	पूर्णांक flen = 0;

	अगर (!debug_msgs)
		वापस;
	अगर (function)
		flen = म_माप(function);
	बहु_शुरू(args, fmt);
	vaf.fmt = fmt;
	vaf.va = &args;
	pr_debug("(%s, %d): %s(): %pV", file, line, flen ? function : "", &vaf);
	बहु_पूर्ण(args);
पूर्ण

/* Dump a runlist. Caller has to provide synchronisation क्रम @rl. */
व्योम ntfs_debug_dump_runlist(स्थिर runlist_element *rl)
अणु
	पूर्णांक i;
	स्थिर अक्षर *lcn_str[5] = अणु "LCN_HOLE         ", "LCN_RL_NOT_MAPPED",
				   "LCN_ENOENT       ", "LCN_unknown      " पूर्ण;

	अगर (!debug_msgs)
		वापस;
	pr_debug("Dumping runlist (values in hex):\n");
	अगर (!rl) अणु
		pr_debug("Run list not present.\n");
		वापस;
	पूर्ण
	pr_debug("VCN              LCN               Run length\n");
	क्रम (i = 0; ; i++) अणु
		LCN lcn = (rl + i)->lcn;

		अगर (lcn < (LCN)0) अणु
			पूर्णांक index = -lcn - 1;

			अगर (index > -LCN_ENOENT - 1)
				index = 3;
			pr_debug("%-16Lx %s %-16Lx%s\n",
					(दीर्घ दीर्घ)(rl + i)->vcn, lcn_str[index],
					(दीर्घ दीर्घ)(rl + i)->length,
					(rl + i)->length ? "" :
						" (runlist end)");
		पूर्ण अन्यथा
			pr_debug("%-16Lx %-16Lx  %-16Lx%s\n",
					(दीर्घ दीर्घ)(rl + i)->vcn,
					(दीर्घ दीर्घ)(rl + i)->lcn,
					(दीर्घ दीर्घ)(rl + i)->length,
					(rl + i)->length ? "" :
						" (runlist end)");
		अगर (!(rl + i)->length)
			अवरोध;
	पूर्ण
पूर्ण

#पूर्ण_अगर
