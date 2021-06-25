<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* Generate kernel symbol version hashes.
   Copyright 1996, 1997 Linux International.

   New implementation contributed by Riअक्षरd Henderson <rth@tamu.edu>
   Based on original work by Bjorn Ekwall <bj0rn@blox.se>

   This file is part of the Linux modutils.

 */

#अगर_अघोषित MODUTILS_GENKSYMS_H
#घोषणा MODUTILS_GENKSYMS_H 1

#समावेश <मानकपन.स>

क्रमागत symbol_type अणु
	SYM_NORMAL, SYM_TYPEDEF, SYM_ENUM, SYM_STRUCT, SYM_UNION,
	SYM_ENUM_CONST
पूर्ण;

क्रमागत symbol_status अणु
	STATUS_UNCHANGED, STATUS_DEFINED, STATUS_MODIFIED
पूर्ण;

काष्ठा string_list अणु
	काष्ठा string_list *next;
	क्रमागत symbol_type tag;
	पूर्णांक in_source_file;
	अक्षर *string;
पूर्ण;

काष्ठा symbol अणु
	काष्ठा symbol *hash_next;
	स्थिर अक्षर *name;
	क्रमागत symbol_type type;
	काष्ठा string_list *defn;
	काष्ठा symbol *expansion_trail;
	काष्ठा symbol *visited;
	पूर्णांक is_बाह्य;
	पूर्णांक is_declared;
	क्रमागत symbol_status status;
	पूर्णांक is_override;
पूर्ण;

प्रकार काष्ठा string_list **yystype;
#घोषणा YYSTYPE yystype

बाह्य पूर्णांक cur_line;
बाह्य अक्षर *cur_filename;
बाह्य पूर्णांक in_source_file;

काष्ठा symbol *find_symbol(स्थिर अक्षर *name, क्रमागत symbol_type ns, पूर्णांक exact);
काष्ठा symbol *add_symbol(स्थिर अक्षर *name, क्रमागत symbol_type type,
			  काष्ठा string_list *defn, पूर्णांक is_बाह्य);
व्योम export_symbol(स्थिर अक्षर *);

व्योम मुक्त_node(काष्ठा string_list *list);
व्योम मुक्त_list(काष्ठा string_list *s, काष्ठा string_list *e);
काष्ठा string_list *copy_node(काष्ठा string_list *);
काष्ठा string_list *copy_list_range(काष्ठा string_list *start,
				    काष्ठा string_list *end);

पूर्णांक yylex(व्योम);
पूर्णांक yyparse(व्योम);

व्योम error_with_pos(स्थिर अक्षर *, ...) __attribute__ ((क्रमmat(म_लिखो, 1, 2)));

/*----------------------------------------------------------------------*/
#घोषणा xदो_स्मृति(size) (अणु व्योम *__ptr = दो_स्मृति(size);		\
	अगर(!__ptr && size != 0) अणु				\
		ख_लिखो(मानक_त्रुटि, "out of memory\n");		\
		निकास(1);					\
	पूर्ण							\
	__ptr; पूर्ण)
#घोषणा xstrdup(str)  (अणु अक्षर *__str = strdup(str);		\
	अगर (!__str) अणु						\
		ख_लिखो(मानक_त्रुटि, "out of memory\n");		\
		निकास(1);					\
	पूर्ण							\
	__str; पूर्ण)

#पूर्ण_अगर				/* genksyms.h */
