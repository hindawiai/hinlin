<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_STRING_HELPERS_H_
#घोषणा _LINUX_STRING_HELPERS_H_

#समावेश <linux/प्रकार.स>
#समावेश <linux/types.h>

काष्ठा file;
काष्ठा task_काष्ठा;

/* Descriptions of the types of units to
 * prपूर्णांक in */
क्रमागत string_size_units अणु
	STRING_UNITS_10,	/* use घातers of 10^3 (standard SI) */
	STRING_UNITS_2,		/* use binary घातers of 2^10 */
पूर्ण;

व्योम string_get_size(u64 size, u64 blk_size, क्रमागत string_size_units units,
		     अक्षर *buf, पूर्णांक len);

#घोषणा UNESCAPE_SPACE		0x01
#घोषणा UNESCAPE_OCTAL		0x02
#घोषणा UNESCAPE_HEX		0x04
#घोषणा UNESCAPE_SPECIAL	0x08
#घोषणा UNESCAPE_ANY		\
	(UNESCAPE_SPACE | UNESCAPE_OCTAL | UNESCAPE_HEX | UNESCAPE_SPECIAL)

पूर्णांक string_unescape(अक्षर *src, अक्षर *dst, माप_प्रकार size, अचिन्हित पूर्णांक flags);

अटल अंतरभूत पूर्णांक string_unescape_inplace(अक्षर *buf, अचिन्हित पूर्णांक flags)
अणु
	वापस string_unescape(buf, buf, 0, flags);
पूर्ण

अटल अंतरभूत पूर्णांक string_unescape_any(अक्षर *src, अक्षर *dst, माप_प्रकार size)
अणु
	वापस string_unescape(src, dst, size, UNESCAPE_ANY);
पूर्ण

अटल अंतरभूत पूर्णांक string_unescape_any_inplace(अक्षर *buf)
अणु
	वापस string_unescape_any(buf, buf, 0);
पूर्ण

#घोषणा ESCAPE_SPACE		0x01
#घोषणा ESCAPE_SPECIAL		0x02
#घोषणा ESCAPE_शून्य		0x04
#घोषणा ESCAPE_OCTAL		0x08
#घोषणा ESCAPE_ANY		\
	(ESCAPE_SPACE | ESCAPE_OCTAL | ESCAPE_SPECIAL | ESCAPE_शून्य)
#घोषणा ESCAPE_NP		0x10
#घोषणा ESCAPE_ANY_NP		(ESCAPE_ANY | ESCAPE_NP)
#घोषणा ESCAPE_HEX		0x20

पूर्णांक string_escape_mem(स्थिर अक्षर *src, माप_प्रकार isz, अक्षर *dst, माप_प्रकार osz,
		अचिन्हित पूर्णांक flags, स्थिर अक्षर *only);

पूर्णांक string_escape_mem_ascii(स्थिर अक्षर *src, माप_प्रकार isz, अक्षर *dst,
					माप_प्रकार osz);

अटल अंतरभूत पूर्णांक string_escape_mem_any_np(स्थिर अक्षर *src, माप_प्रकार isz,
		अक्षर *dst, माप_प्रकार osz, स्थिर अक्षर *only)
अणु
	वापस string_escape_mem(src, isz, dst, osz, ESCAPE_ANY_NP, only);
पूर्ण

अटल अंतरभूत पूर्णांक string_escape_str(स्थिर अक्षर *src, अक्षर *dst, माप_प्रकार sz,
		अचिन्हित पूर्णांक flags, स्थिर अक्षर *only)
अणु
	वापस string_escape_mem(src, म_माप(src), dst, sz, flags, only);
पूर्ण

अटल अंतरभूत पूर्णांक string_escape_str_any_np(स्थिर अक्षर *src, अक्षर *dst,
		माप_प्रकार sz, स्थिर अक्षर *only)
अणु
	वापस string_escape_str(src, dst, sz, ESCAPE_ANY_NP, only);
पूर्ण

अटल अंतरभूत व्योम string_upper(अक्षर *dst, स्थिर अक्षर *src)
अणु
	करो अणु
		*dst++ = बड़े(*src);
	पूर्ण जबतक (*src++);
पूर्ण

अटल अंतरभूत व्योम string_lower(अक्षर *dst, स्थिर अक्षर *src)
अणु
	करो अणु
		*dst++ = छोटे(*src);
	पूर्ण जबतक (*src++);
पूर्ण

अक्षर *kstrdup_quotable(स्थिर अक्षर *src, gfp_t gfp);
अक्षर *kstrdup_quotable_cmdline(काष्ठा task_काष्ठा *task, gfp_t gfp);
अक्षर *kstrdup_quotable_file(काष्ठा file *file, gfp_t gfp);

व्योम kमुक्त_strarray(अक्षर **array, माप_प्रकार n);

#पूर्ण_अगर
