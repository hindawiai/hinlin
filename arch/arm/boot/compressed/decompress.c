<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा _LINUX_STRING_H_

#समावेश <linux/compiler.h>	/* क्रम अंतरभूत */
#समावेश <linux/types.h>	/* क्रम माप_प्रकार */
#समावेश <linux/मानकघोष.स>	/* क्रम शून्य */
#समावेश <linux/linkage.h>
#समावेश <यंत्र/माला.स>
#समावेश "misc.h"

#घोषणा STATIC अटल
#घोषणा STATIC_RW_DATA	/* non-अटल please */

/* Diagnostic functions */
#अगर_घोषित DEBUG
#  define Assert(cond,msg) अणुअगर(!(cond)) error(msg);पूर्ण
#  define Trace(x) ख_लिखो x
#  define Tracev(x) अणुअगर (verbose) ख_लिखो x ;पूर्ण
#  define Tracevv(x) अणुअगर (verbose>1) ख_लिखो x ;पूर्ण
#  define Tracec(c,x) अणुअगर (verbose && (c)) ख_लिखो x ;पूर्ण
#  define Tracecv(c,x) अणुअगर (verbose>1 && (c)) ख_लिखो x ;पूर्ण
#अन्यथा
#  define Assert(cond,msg)
#  define Trace(x)
#  define Tracev(x)
#  define Tracevv(x)
#  define Tracec(c,x)
#  define Tracecv(c,x)
#पूर्ण_अगर

/* Not needed, but used in some headers pulled in by decompressors */
बाह्य अक्षर * म_माला(स्थिर अक्षर * s1, स्थिर अक्षर *s2);
बाह्य माप_प्रकार म_माप(स्थिर अक्षर *s);
बाह्य पूर्णांक स_भेद(स्थिर व्योम *cs, स्थिर व्योम *ct, माप_प्रकार count);
बाह्य अक्षर * म_अक्षरnul(स्थिर अक्षर *, पूर्णांक);

#अगर_घोषित CONFIG_KERNEL_GZIP
#समावेश "../../../../lib/decompress_inflate.c"
#पूर्ण_अगर

#अगर_घोषित CONFIG_KERNEL_LZO
#समावेश "../../../../lib/decompress_unlzo.c"
#पूर्ण_अगर

#अगर_घोषित CONFIG_KERNEL_LZMA
#समावेश "../../../../lib/decompress_unlzma.c"
#पूर्ण_अगर

#अगर_घोषित CONFIG_KERNEL_XZ
#घोषणा स_हटाओ स_हटाओ
#घोषणा स_नकल स_नकल
#समावेश "../../../../lib/decompress_unxz.c"
#पूर्ण_अगर

#अगर_घोषित CONFIG_KERNEL_LZ4
#समावेश "../../../../lib/decompress_unlz4.c"
#पूर्ण_अगर

पूर्णांक करो_decompress(u8 *input, पूर्णांक len, u8 *output, व्योम (*error)(अक्षर *x))
अणु
	वापस __decompress(input, len, शून्य, शून्य, output, 0, शून्य, error);
पूर्ण
