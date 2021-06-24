<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_IA64_EARLY_IOREMAP_H
#घोषणा _ASM_IA64_EARLY_IOREMAP_H

बाह्य व्योम __iomem * early_ioremap (अचिन्हित दीर्घ phys_addr, अचिन्हित दीर्घ size);
#घोषणा early_memremap(phys_addr, size)        early_ioremap(phys_addr, size)

बाह्य व्योम early_iounmap (अस्थिर व्योम __iomem *addr, अचिन्हित दीर्घ size);
#घोषणा early_memunmap(addr, size)             early_iounmap(addr, size)

#पूर्ण_अगर
