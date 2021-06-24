<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright 2007 Jon Loeliger, Freescale Semiconductor, Inc.
 */

#अगर_अघोषित SRCPOS_H
#घोषणा SRCPOS_H

#समावेश <मानकपन.स>
#समावेश <stdbool.h>
#समावेश "util.h"

काष्ठा srcfile_state अणु
	खाता *f;
	अक्षर *name;
	अक्षर *dir;
	पूर्णांक lineno, colno;
	काष्ठा srcfile_state *prev;
पूर्ण;

बाह्य खाता *depfile; /* = शून्य */
बाह्य काष्ठा srcfile_state *current_srcfile; /* = शून्य */

/**
 * Open a source file.
 *
 * If the source file is a relative pathname, then it is searched क्रम in the
 * current directory (the directory of the last source file पढ़ो) and after
 * that in the search path.
 *
 * We work through the search path in order from the first path specअगरied to
 * the last.
 *
 * If the file is not found, then this function करोes not वापस, but calls
 * die().
 *
 * @param fname		Filename to search
 * @param fullnamep	If non-शून्य, it is set to the allocated filename of the
 *			file that was खोलोed. The caller is then responsible
 *			क्रम मुक्तing the poपूर्णांकer.
 * @वापस poपूर्णांकer to खोलोed खाता
 */
खाता *srcfile_relative_खोलो(स्थिर अक्षर *fname, अक्षर **fullnamep);

व्योम srcfile_push(स्थिर अक्षर *fname);
bool srcfile_pop(व्योम);

/**
 * Add a new directory to the search path क्रम input files
 *
 * The new path is added at the end of the list.
 *
 * @param स_नाम	Directory to add
 */
व्योम srcfile_add_search_path(स्थिर अक्षर *स_नाम);

काष्ठा srcpos अणु
    पूर्णांक first_line;
    पूर्णांक first_column;
    पूर्णांक last_line;
    पूर्णांक last_column;
    काष्ठा srcfile_state *file;
    काष्ठा srcpos *next;
पूर्ण;

#घोषणा YYLTYPE काष्ठा srcpos

#घोषणा YYLLOC_DEFAULT(Current, Rhs, N)						\
	करो अणु									\
		अगर (N) अणु							\
			(Current).first_line = YYRHSLOC(Rhs, 1).first_line;	\
			(Current).first_column = YYRHSLOC(Rhs, 1).first_column;	\
			(Current).last_line = YYRHSLOC(Rhs, N).last_line;	\
			(Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
			(Current).file = YYRHSLOC(Rhs, N).file;			\
		पूर्ण अन्यथा अणु							\
			(Current).first_line = (Current).last_line =		\
				YYRHSLOC(Rhs, 0).last_line;			\
			(Current).first_column = (Current).last_column =	\
				YYRHSLOC(Rhs, 0).last_column;			\
			(Current).file = YYRHSLOC (Rhs, 0).file;		\
		पूर्ण								\
		(Current).next = शून्य;						\
	पूर्ण जबतक (0)


बाह्य व्योम srcpos_update(काष्ठा srcpos *pos, स्थिर अक्षर *text, पूर्णांक len);
बाह्य काष्ठा srcpos *srcpos_copy(काष्ठा srcpos *pos);
बाह्य काष्ठा srcpos *srcpos_extend(काष्ठा srcpos *new_srcpos,
				    काष्ठा srcpos *old_srcpos);
बाह्य अक्षर *srcpos_string(काष्ठा srcpos *pos);
बाह्य अक्षर *srcpos_string_first(काष्ठा srcpos *pos, पूर्णांक level);
बाह्य अक्षर *srcpos_string_last(काष्ठा srcpos *pos, पूर्णांक level);


बाह्य व्योम PRINTF(3, 0) srcpos_verror(काष्ठा srcpos *pos, स्थिर अक्षर *prefix,
					स्थिर अक्षर *fmt, बहु_सूची va);
बाह्य व्योम PRINTF(3, 4) srcpos_error(काष्ठा srcpos *pos, स्थिर अक्षर *prefix,
				      स्थिर अक्षर *fmt, ...);

बाह्य व्योम srcpos_set_line(अक्षर *f, पूर्णांक l);

#पूर्ण_अगर /* SRCPOS_H */
