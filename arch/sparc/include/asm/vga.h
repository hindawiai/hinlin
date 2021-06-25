<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *	Access to VGA videoram
 *
 *	(c) 1998 Martin Mares <mj@ucw.cz>
 */

#अगर_अघोषित _LINUX_ASM_VGA_H_
#घोषणा _LINUX_ASM_VGA_H_

#समावेश <linux/bug.h>
#समावेश <linux/माला.स>
#समावेश <यंत्र/types.h>

#घोषणा VT_BUF_HAVE_RW
#घोषणा VT_BUF_HAVE_MEMSETW
#घोषणा VT_BUF_HAVE_MEMCPYW
#घोषणा VT_BUF_HAVE_MEMMOVEW

#अघोषित scr_ग_लिखोw
#अघोषित scr_पढ़ोw

अटल अंतरभूत व्योम scr_ग_लिखोw(u16 val, u16 *addr)
अणु
	BUG_ON((दीर्घ) addr >= 0);

	*addr = val;
पूर्ण

अटल अंतरभूत u16 scr_पढ़ोw(स्थिर u16 *addr)
अणु
	BUG_ON((दीर्घ) addr >= 0);

	वापस *addr;
पूर्ण

अटल अंतरभूत व्योम scr_स_रखोw(u16 *p, u16 v, अचिन्हित पूर्णांक n)
अणु
	BUG_ON((दीर्घ) p >= 0);

	स_रखो16(p, cpu_to_le16(v), n / 2);
पूर्ण

अटल अंतरभूत व्योम scr_स_नकलw(u16 *d, u16 *s, अचिन्हित पूर्णांक n)
अणु
	BUG_ON((दीर्घ) d >= 0);

	स_नकल(d, s, n);
पूर्ण

अटल अंतरभूत व्योम scr_स_हटाओw(u16 *d, u16 *s, अचिन्हित पूर्णांक n)
अणु
	BUG_ON((दीर्घ) d >= 0);

	स_हटाओ(d, s, n);
पूर्ण

#घोषणा VGA_MAP_MEM(x,s) (x)

#पूर्ण_अगर
