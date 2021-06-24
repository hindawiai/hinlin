<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_VGA_H_
#घोषणा _ASM_POWERPC_VGA_H_

#अगर_घोषित __KERNEL__

/*
 *	Access to VGA videoram
 *
 *	(c) 1998 Martin Mares <mj@ucw.cz>
 */


#समावेश <यंत्र/पन.स>


#अगर defined(CONFIG_VGA_CONSOLE) || defined(CONFIG_MDA_CONSOLE)

#घोषणा VT_BUF_HAVE_RW
/*
 *  These are only needed क्रम supporting VGA or MDA text mode, which use little
 *  endian byte ordering.
 *  In other हालs, we can optimize by using native byte ordering and
 *  <linux/vt_buffer.h> has alपढ़ोy करोne the right job क्रम us.
 */

अटल अंतरभूत व्योम scr_ग_लिखोw(u16 val, अस्थिर u16 *addr)
अणु
	*addr = cpu_to_le16(val);
पूर्ण

अटल अंतरभूत u16 scr_पढ़ोw(अस्थिर स्थिर u16 *addr)
अणु
	वापस le16_to_cpu(*addr);
पूर्ण

#घोषणा VT_BUF_HAVE_MEMSETW
अटल अंतरभूत व्योम scr_स_रखोw(u16 *s, u16 v, अचिन्हित पूर्णांक n)
अणु
	स_रखो16(s, cpu_to_le16(v), n / 2);
पूर्ण

#घोषणा VT_BUF_HAVE_MEMCPYW
#घोषणा VT_BUF_HAVE_MEMMOVEW
#घोषणा scr_स_नकलw	स_नकल
#घोषणा scr_स_हटाओw	स_हटाओ

#पूर्ण_अगर /* !CONFIG_VGA_CONSOLE && !CONFIG_MDA_CONSOLE */

#अगर_घोषित __घातerpc64__
#घोषणा VGA_MAP_MEM(x,s) ((अचिन्हित दीर्घ) ioremap((x), s))
#अन्यथा
#घोषणा VGA_MAP_MEM(x,s) (x)
#पूर्ण_अगर

#घोषणा vga_पढ़ोb(x) (*(x))
#घोषणा vga_ग_लिखोb(x,y) (*(y) = (x))

#पूर्ण_अगर	/* __KERNEL__ */
#पूर्ण_अगर	/* _ASM_POWERPC_VGA_H_ */
