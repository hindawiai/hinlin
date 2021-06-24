<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * (c) Copyright 2006, 2007 Hewlett-Packard Development Company, L.P.
 *	Bjorn Helgaas <bjorn.helgaas@hp.com>
 */

#समावेश <linux/compiler.h>
#समावेश <linux/module.h>
#समावेश <linux/efi.h>
#समावेश <linux/पन.स>
#समावेश <linux/mm.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/meminit.h>

अटल अंतरभूत व्योम __iomem *
__ioremap_uc(अचिन्हित दीर्घ phys_addr)
अणु
	वापस (व्योम __iomem *) (__IA64_UNCACHED_OFFSET | phys_addr);
पूर्ण

व्योम __iomem *
early_ioremap (अचिन्हित दीर्घ phys_addr, अचिन्हित दीर्घ size)
अणु
	u64 attr;
	attr = kern_mem_attribute(phys_addr, size);
	अगर (attr & EFI_MEMORY_WB)
		वापस (व्योम __iomem *) phys_to_virt(phys_addr);
	वापस __ioremap_uc(phys_addr);
पूर्ण

व्योम __iomem *
ioremap (अचिन्हित दीर्घ phys_addr, अचिन्हित दीर्घ size)
अणु
	व्योम __iomem *addr;
	काष्ठा vm_काष्ठा *area;
	अचिन्हित दीर्घ offset;
	pgprot_t prot;
	u64 attr;
	अचिन्हित दीर्घ gran_base, gran_size;
	अचिन्हित दीर्घ page_base;

	/*
	 * For things in kern_memmap, we must use the same attribute
	 * as the rest of the kernel.  For more details, see
	 * Documentation/ia64/aliasing.rst.
	 */
	attr = kern_mem_attribute(phys_addr, size);
	अगर (attr & EFI_MEMORY_WB)
		वापस (व्योम __iomem *) phys_to_virt(phys_addr);
	अन्यथा अगर (attr & EFI_MEMORY_UC)
		वापस __ioremap_uc(phys_addr);

	/*
	 * Some chipsets करोn't support UC access to memory.  If
	 * WB is supported क्रम the whole granule, we prefer that.
	 */
	gran_base = GRANULEROUNDDOWN(phys_addr);
	gran_size = GRANULEROUNDUP(phys_addr + size) - gran_base;
	अगर (efi_mem_attribute(gran_base, gran_size) & EFI_MEMORY_WB)
		वापस (व्योम __iomem *) phys_to_virt(phys_addr);

	/*
	 * WB is not supported क्रम the whole granule, so we can't use
	 * the region 7 identity mapping.  If we can safely cover the
	 * area with kernel page table mappings, we can use those
	 * instead.
	 */
	page_base = phys_addr & PAGE_MASK;
	size = PAGE_ALIGN(phys_addr + size) - page_base;
	अगर (efi_mem_attribute(page_base, size) & EFI_MEMORY_WB) अणु
		prot = PAGE_KERNEL;

		/*
		 * Mappings have to be page-aligned
		 */
		offset = phys_addr & ~PAGE_MASK;
		phys_addr &= PAGE_MASK;

		/*
		 * Ok, go क्रम it..
		 */
		area = get_vm_area(size, VM_IOREMAP);
		अगर (!area)
			वापस शून्य;

		area->phys_addr = phys_addr;
		addr = (व्योम __iomem *) area->addr;
		अगर (ioremap_page_range((अचिन्हित दीर्घ) addr,
				(अचिन्हित दीर्घ) addr + size, phys_addr, prot)) अणु
			vunmap((व्योम __क्रमce *) addr);
			वापस शून्य;
		पूर्ण

		वापस (व्योम __iomem *) (offset + (अक्षर __iomem *)addr);
	पूर्ण

	वापस __ioremap_uc(phys_addr);
पूर्ण
EXPORT_SYMBOL(ioremap);

व्योम __iomem *
ioremap_uc(अचिन्हित दीर्घ phys_addr, अचिन्हित दीर्घ size)
अणु
	अगर (kern_mem_attribute(phys_addr, size) & EFI_MEMORY_WB)
		वापस शून्य;

	वापस __ioremap_uc(phys_addr);
पूर्ण
EXPORT_SYMBOL(ioremap_uc);

व्योम
early_iounmap (अस्थिर व्योम __iomem *addr, अचिन्हित दीर्घ size)
अणु
पूर्ण

व्योम
iounmap (अस्थिर व्योम __iomem *addr)
अणु
	अगर (REGION_NUMBER(addr) == RGN_GATE)
		vunmap((व्योम *) ((अचिन्हित दीर्घ) addr & PAGE_MASK));
पूर्ण
EXPORT_SYMBOL(iounmap);
