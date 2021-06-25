<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/module.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/पन.स>

/*
 * Copy data from IO memory space to "real" memory space.
 * This needs to be optimized.
 */
व्योम स_नकल_fromio(व्योम *to, स्थिर अस्थिर व्योम __iomem *from, दीर्घ count)
अणु
	अक्षर *dst = to;

	जबतक (count) अणु
		count--;
		*dst++ = पढ़ोb(from++);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(स_नकल_fromio);

/*
 * Copy data from "real" memory space to IO memory space.
 * This needs to be optimized.
 */
व्योम स_नकल_toio(अस्थिर व्योम __iomem *to, स्थिर व्योम *from, दीर्घ count)
अणु
	स्थिर अक्षर *src = from;

	जबतक (count) अणु
		count--;
		ग_लिखोb(*src++, to++);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(स_नकल_toio);

/*
 * "memset" on IO memory space.
 * This needs to be optimized.
 */
व्योम स_रखो_io(अस्थिर व्योम __iomem *dst, पूर्णांक c, दीर्घ count)
अणु
	अचिन्हित अक्षर ch = (अक्षर)(c & 0xff);

	जबतक (count) अणु
		count--;
		ग_लिखोb(ch, dst);
		dst++;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(स_रखो_io);
