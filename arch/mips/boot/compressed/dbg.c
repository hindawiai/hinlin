<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * MIPS-specअगरic debug support क्रम pre-boot environment
 *
 * NOTE: अ_दो() is board specअगरic, अगर your board have a 16550 compatible uart,
 * please select SYS_SUPPORTS_ZBOOT_UART16550 क्रम your machine. othewise, you
 * need to implement your own अ_दो().
 */
#समावेश <linux/compiler.h>
#समावेश <linux/types.h>

व्योम __weak अ_दो(अक्षर c)
अणु
पूर्ण

व्योम माला_दो(स्थिर अक्षर *s)
अणु
	अक्षर c;
	जबतक ((c = *s++) != '\0') अणु
		अ_दो(c);
		अगर (c == '\n')
			अ_दो('\r');
	पूर्ण
पूर्ण

व्योम puthex(अचिन्हित दीर्घ दीर्घ val)
अणु

	अचिन्हित अक्षर buf[10];
	पूर्णांक i;
	क्रम (i = 7; i >= 0; i--) अणु
		buf[i] = "0123456789ABCDEF"[val & 0x0F];
		val >>= 4;
	पूर्ण
	buf[8] = '\0';
	माला_दो(buf);
पूर्ण
