<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/पन.स>
#समावेश <ioremap.h>

व्योम __iomem *ioremap_prot(phys_addr_t offset, अचिन्हित दीर्घ size,
		अचिन्हित दीर्घ prot_val)
अणु
	अचिन्हित दीर्घ flags = prot_val & _CACHE_MASK;
	u64 base = (flags == _CACHE_UNCACHED ? IO_BASE : UNCAC_BASE);
	व्योम __iomem *addr;

	addr = plat_ioremap(offset, size, flags);
	अगर (!addr)
		addr = (व्योम __iomem *)(अचिन्हित दीर्घ)(base + offset);
	वापस addr;
पूर्ण
EXPORT_SYMBOL(ioremap_prot);

व्योम iounmap(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	plat_iounmap(addr);
पूर्ण
EXPORT_SYMBOL(iounmap);
