<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *	Access to VGA videoram
 *
 *	(c) 1998 Martin Mares <mj@ucw.cz>
 */
#अगर_अघोषित _ASM_VGA_H
#घोषणा _ASM_VGA_H

#समावेश <linux/माला.स>
#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/byteorder.h>

/*
 *	On the PC, we can just recalculate addresses and then
 *	access the videoram directly without any black magic.
 */

#घोषणा VGA_MAP_MEM(x, s)	CKSEG1ADDR(0x10000000L + (अचिन्हित दीर्घ)(x))

#घोषणा vga_पढ़ोb(x)	(*(x))
#घोषणा vga_ग_लिखोb(x, y)	(*(y) = (x))

#घोषणा VT_BUF_HAVE_RW
/*
 *  These are only needed क्रम supporting VGA or MDA text mode, which use little
 *  endian byte ordering.
 *  In other हालs, we can optimize by using native byte ordering and
 *  <linux/vt_buffer.h> has alपढ़ोy करोne the right job क्रम us.
 */

#अघोषित scr_ग_लिखोw
#अघोषित scr_पढ़ोw

अटल अंतरभूत व्योम scr_ग_लिखोw(u16 val, अस्थिर u16 *addr)
अणु
	*addr = cpu_to_le16(val);
पूर्ण

अटल अंतरभूत u16 scr_पढ़ोw(अस्थिर स्थिर u16 *addr)
अणु
	वापस le16_to_cpu(*addr);
पूर्ण

अटल अंतरभूत व्योम scr_स_रखोw(u16 *s, u16 v, अचिन्हित पूर्णांक count)
अणु
	स_रखो16(s, cpu_to_le16(v), count / 2);
पूर्ण

#घोषणा scr_स_नकलw(d, s, c) स_नकल(d, s, c)
#घोषणा scr_स_हटाओw(d, s, c) स_हटाओ(d, s, c)
#घोषणा VT_BUF_HAVE_MEMCPYW
#घोषणा VT_BUF_HAVE_MEMMOVEW
#घोषणा VT_BUF_HAVE_MEMSETW

#पूर्ण_अगर /* _ASM_VGA_H */
