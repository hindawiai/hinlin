<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *	include/यंत्र-mips/mach-tx39xx/ioremap.h
 */
#अगर_अघोषित __ASM_MACH_TX39XX_IOREMAP_H
#घोषणा __ASM_MACH_TX39XX_IOREMAP_H

#समावेश <linux/types.h>

अटल अंतरभूत व्योम __iomem *plat_ioremap(phys_addr_t offset, अचिन्हित दीर्घ size,
	अचिन्हित दीर्घ flags)
अणु
#घोषणा TXX9_सूचीECTMAP_BASE	0xff000000ul
	अगर (offset >= TXX9_सूचीECTMAP_BASE &&
	    offset < TXX9_सूचीECTMAP_BASE + 0xff0000)
		वापस (व्योम __iomem *)offset;
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक plat_iounmap(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	वापस (अचिन्हित दीर्घ)addr >= TXX9_सूचीECTMAP_BASE;
पूर्ण

#पूर्ण_अगर /* __ASM_MACH_TX39XX_IOREMAP_H */
