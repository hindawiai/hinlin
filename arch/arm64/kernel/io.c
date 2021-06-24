<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Based on arch/arm/kernel/io.c
 *
 * Copyright (C) 2012 ARM Ltd.
 */

#समावेश <linux/export.h>
#समावेश <linux/types.h>
#समावेश <linux/पन.स>

/*
 * Copy data from IO memory space to "real" memory space.
 */
व्योम __स_नकल_fromio(व्योम *to, स्थिर अस्थिर व्योम __iomem *from, माप_प्रकार count)
अणु
	जबतक (count && !IS_ALIGNED((अचिन्हित दीर्घ)from, 8)) अणु
		*(u8 *)to = __raw_पढ़ोb(from);
		from++;
		to++;
		count--;
	पूर्ण

	जबतक (count >= 8) अणु
		*(u64 *)to = __raw_पढ़ोq(from);
		from += 8;
		to += 8;
		count -= 8;
	पूर्ण

	जबतक (count) अणु
		*(u8 *)to = __raw_पढ़ोb(from);
		from++;
		to++;
		count--;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(__स_नकल_fromio);

/*
 * Copy data from "real" memory space to IO memory space.
 */
व्योम __स_नकल_toio(अस्थिर व्योम __iomem *to, स्थिर व्योम *from, माप_प्रकार count)
अणु
	जबतक (count && !IS_ALIGNED((अचिन्हित दीर्घ)to, 8)) अणु
		__raw_ग_लिखोb(*(u8 *)from, to);
		from++;
		to++;
		count--;
	पूर्ण

	जबतक (count >= 8) अणु
		__raw_ग_लिखोq(*(u64 *)from, to);
		from += 8;
		to += 8;
		count -= 8;
	पूर्ण

	जबतक (count) अणु
		__raw_ग_लिखोb(*(u8 *)from, to);
		from++;
		to++;
		count--;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(__स_नकल_toio);

/*
 * "memset" on IO memory space.
 */
व्योम __स_रखो_io(अस्थिर व्योम __iomem *dst, पूर्णांक c, माप_प्रकार count)
अणु
	u64 qc = (u8)c;

	qc |= qc << 8;
	qc |= qc << 16;
	qc |= qc << 32;

	जबतक (count && !IS_ALIGNED((अचिन्हित दीर्घ)dst, 8)) अणु
		__raw_ग_लिखोb(c, dst);
		dst++;
		count--;
	पूर्ण

	जबतक (count >= 8) अणु
		__raw_ग_लिखोq(qc, dst);
		dst += 8;
		count -= 8;
	पूर्ण

	जबतक (count) अणु
		__raw_ग_लिखोb(c, dst);
		dst++;
		count--;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(__स_रखो_io);
