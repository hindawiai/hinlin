<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *	Access to VGA videoram
 *
 *	(c) 1998 Martin Mares <mj@ucw.cz>
 */

#अगर_अघोषित _LINUX_ASM_VGA_H_
#घोषणा _LINUX_ASM_VGA_H_

#समावेश <यंत्र/पन.स>

#घोषणा VT_BUF_HAVE_RW
#घोषणा VT_BUF_HAVE_MEMSETW
#घोषणा VT_BUF_HAVE_MEMCPYW

अटल अंतरभूत व्योम scr_ग_लिखोw(u16 val, अस्थिर u16 *addr)
अणु
	अगर (__is_ioaddr(addr))
		__raw_ग_लिखोw(val, (अस्थिर u16 __iomem *) addr);
	अन्यथा
		*addr = val;
पूर्ण

अटल अंतरभूत u16 scr_पढ़ोw(अस्थिर स्थिर u16 *addr)
अणु
	अगर (__is_ioaddr(addr))
		वापस __raw_पढ़ोw((अस्थिर स्थिर u16 __iomem *) addr);
	अन्यथा
		वापस *addr;
पूर्ण

अटल अंतरभूत व्योम scr_स_रखोw(u16 *s, u16 c, अचिन्हित पूर्णांक count)
अणु
	अगर (__is_ioaddr(s))
		स_रखोw_io((u16 __iomem *) s, c, count);
	अन्यथा
		स_रखो16(s, c, count / 2);
पूर्ण

/* Do not trust that the usage will be correct; analyze the arguments.  */
बाह्य व्योम scr_स_नकलw(u16 *d, स्थिर u16 *s, अचिन्हित पूर्णांक count);

/* ??? These are currently only used क्रम करोwnloading अक्षरacter sets.  As
   such, they करोn't need memory barriers.  Is this all they are पूर्णांकended
   to be used क्रम?  */
#घोषणा vga_पढ़ोb(a)	पढ़ोb((u8 __iomem *)(a))
#घोषणा vga_ग_लिखोb(v,a)	ग_लिखोb(v, (u8 __iomem *)(a))

#अगर_घोषित CONFIG_VGA_HOSE
#समावेश <linux/ioport.h>
#समावेश <linux/pci.h>

बाह्य काष्ठा pci_controller *pci_vga_hose;

# define __is_port_vga(a)       \
	(((a) >= 0x3b0) && ((a) < 0x3e0) && \
	 ((a) != 0x3b3) && ((a) != 0x3d3))

# define __is_mem_vga(a) \
	(((a) >= 0xa0000) && ((a) <= 0xc0000))

# define FIXUP_IOADDR_VGA(a) करो अणु                       \
	अगर (pci_vga_hose && __is_port_vga(a))     \
		(a) += pci_vga_hose->io_space->start;	  \
 पूर्ण जबतक(0)

# define FIXUP_MEMADDR_VGA(a) करो अणु                       \
	अगर (pci_vga_hose && __is_mem_vga(a))     \
		(a) += pci_vga_hose->mem_space->start; \
 पूर्ण जबतक(0)

#अन्यथा /* CONFIG_VGA_HOSE */
# define pci_vga_hose 0
# define __is_port_vga(a) 0
# define __is_mem_vga(a) 0
# define FIXUP_IOADDR_VGA(a)
# define FIXUP_MEMADDR_VGA(a)
#पूर्ण_अगर /* CONFIG_VGA_HOSE */

#घोषणा VGA_MAP_MEM(x,s)	((अचिन्हित दीर्घ) ioremap(x, s))

#पूर्ण_अगर
