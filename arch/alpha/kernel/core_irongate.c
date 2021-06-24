<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	linux/arch/alpha/kernel/core_irongate.c
 *
 * Based on code written by David A. Rusling (david.rusling@reo.mts.dec.com).
 *
 *	Copyright (C) 1999 Alpha Processor, Inc.,
 *		(David Daniel, Stig Telfer, Soohoon Lee)
 *
 * Code common to all IRONGATE core logic chips.
 */

#घोषणा __EXTERN_INLINE अंतरभूत
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/core_irongate.h>
#अघोषित __EXTERN_INLINE

#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/sched.h>
#समावेश <linux/init.h>
#समावेश <linux/initrd.h>
#समावेश <linux/memblock.h>

#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/tlbflush.h>

#समावेश "proto.h"
#समावेश "pci_impl.h"

/*
 * BIOS32-style PCI पूर्णांकerface:
 */

#घोषणा DEBUG_CONFIG 0

#अगर DEBUG_CONFIG
# define DBG_CFG(args)	prपूर्णांकk args
#अन्यथा
# define DBG_CFG(args)
#पूर्ण_अगर

igcsr32 *IronECC;

/*
 * Given a bus, device, and function number, compute resulting
 * configuration space address accordingly.  It is thereक्रमe not safe
 * to have concurrent invocations to configuration space access
 * routines, but there really shouldn't be any need क्रम this.
 *
 *	addr[31:24]		reserved
 *	addr[23:16]		bus number (8 bits = 128 possible buses)
 *	addr[15:11]		Device number (5 bits)
 *	addr[10: 8]		function number
 *	addr[ 7: 2]		रेजिस्टर number
 *
 * For IRONGATE:
 *    अगर (bus = addr[23:16]) == 0
 *    then
 *	  type 0 config cycle:
 *	      addr_on_pci[31:11] = id selection क्रम device = addr[15:11]
 *	      addr_on_pci[10: 2] = addr[10: 2] ???
 *	      addr_on_pci[ 1: 0] = 00
 *    अन्यथा
 *	  type 1 config cycle (pass on with no decoding):
 *	      addr_on_pci[31:24] = 0
 *	      addr_on_pci[23: 2] = addr[23: 2]
 *	      addr_on_pci[ 1: 0] = 01
 *    fi
 *
 * Notes:
 *	The function number selects which function of a multi-function device
 *	(e.g., SCSI and Ethernet).
 *
 *	The रेजिस्टर selects a DWORD (32 bit) रेजिस्टर offset.	Hence it
 *	करोesn't get shअगरted by 2 bits as we want to "drop" the bottom two
 *	bits.
 */

अटल पूर्णांक
mk_conf_addr(काष्ठा pci_bus *pbus, अचिन्हित पूर्णांक device_fn, पूर्णांक where,
	     अचिन्हित दीर्घ *pci_addr, अचिन्हित अक्षर *type1)
अणु
	अचिन्हित दीर्घ addr;
	u8 bus = pbus->number;

	DBG_CFG(("mk_conf_addr(bus=%d ,device_fn=0x%x, where=0x%x, "
		 "pci_addr=0x%p, type1=0x%p)\n",
		 bus, device_fn, where, pci_addr, type1));

	*type1 = (bus != 0);

	addr = (bus << 16) | (device_fn << 8) | where;
	addr |= IRONGATE_CONF;

	*pci_addr = addr;
	DBG_CFG(("mk_conf_addr: returning pci_addr 0x%lx\n", addr));
	वापस 0;
पूर्ण

अटल पूर्णांक
irongate_पढ़ो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक where,
		     पूर्णांक size, u32 *value)
अणु
	अचिन्हित दीर्घ addr;
	अचिन्हित अक्षर type1;

	अगर (mk_conf_addr(bus, devfn, where, &addr, &type1))
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	चयन (size) अणु
	हाल 1:
		*value = __kernel_ldbu(*(vucp)addr);
		अवरोध;
	हाल 2:
		*value = __kernel_ldwu(*(vusp)addr);
		अवरोध;
	हाल 4:
		*value = *(vuip)addr;
		अवरोध;
	पूर्ण

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक
irongate_ग_लिखो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक where,
		      पूर्णांक size, u32 value)
अणु
	अचिन्हित दीर्घ addr;
	अचिन्हित अक्षर type1;

	अगर (mk_conf_addr(bus, devfn, where, &addr, &type1))
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	चयन (size) अणु
	हाल 1:
		__kernel_stb(value, *(vucp)addr);
		mb();
		__kernel_ldbu(*(vucp)addr);
		अवरोध;
	हाल 2:
		__kernel_stw(value, *(vusp)addr);
		mb();
		__kernel_ldwu(*(vusp)addr);
		अवरोध;
	हाल 4:
		*(vuip)addr = value;
		mb();
		*(vuip)addr;
		अवरोध;
	पूर्ण

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

काष्ठा pci_ops irongate_pci_ops =
अणु
	.पढ़ो =		irongate_पढ़ो_config,
	.ग_लिखो =	irongate_ग_लिखो_config,
पूर्ण;

पूर्णांक
irongate_pci_clr_err(व्योम)
अणु
	अचिन्हित पूर्णांक nmi_ctl=0;
	अचिन्हित पूर्णांक IRONGATE_jd;

again:
	IRONGATE_jd = IRONGATE0->stat_cmd;
	prपूर्णांकk("Iron stat_cmd %x\n", IRONGATE_jd);
	IRONGATE0->stat_cmd = IRONGATE_jd; /* ग_लिखो again clears error bits */
	mb();
	IRONGATE_jd = IRONGATE0->stat_cmd;  /* re-पढ़ो to क्रमce ग_लिखो */

	IRONGATE_jd = *IronECC;
	prपूर्णांकk("Iron ECC %x\n", IRONGATE_jd);
	*IronECC = IRONGATE_jd; /* ग_लिखो again clears error bits */
	mb();
	IRONGATE_jd = *IronECC;  /* re-पढ़ो to क्रमce ग_लिखो */

	/* Clear ALI NMI */
        nmi_ctl = inb(0x61);
        nmi_ctl |= 0x0c;
        outb(nmi_ctl, 0x61);
        nmi_ctl &= ~0x0c;
        outb(nmi_ctl, 0x61);

	IRONGATE_jd = *IronECC;
	अगर (IRONGATE_jd & 0x300) जाओ again;

	वापस 0;
पूर्ण

#घोषणा IRONGATE_3GB 0xc0000000UL

/* On Albacore (aka UP1500) with 4Gb of RAM we have to reserve some
   memory क्रम PCI. At this poपूर्णांक we just reserve memory above 3Gb. Most
   of this memory will be मुक्तd after PCI setup is करोne. */
अटल व्योम __init
albacore_init_arch(व्योम)
अणु
	अचिन्हित दीर्घ memtop = max_low_pfn << PAGE_SHIFT;
	अचिन्हित दीर्घ pci_mem = (memtop + 0x1000000UL) & ~0xffffffUL;
	काष्ठा percpu_काष्ठा *cpu;
	पूर्णांक pal_rev, pal_var;

	cpu = (काष्ठा percpu_काष्ठा*)((अक्षर*)hwrpb + hwrpb->processor_offset);
	pal_rev = cpu->pal_revision & 0xffff;
	pal_var = (cpu->pal_revision >> 16) & 0xff;

	/* Consoles earlier than A5.6-18 (OSF PALcode v1.62-2) set up
	   the CPU incorrectly (leave speculative stores enabled),
	   which causes memory corruption under certain conditions.
	   Issue a warning क्रम such consoles. */
	अगर (alpha_using_srm &&
	    (pal_rev < 0x13e ||	(pal_rev == 0x13e && pal_var < 2)))
		prपूर्णांकk(KERN_WARNING "WARNING! Upgrade to SRM A5.6-19 "
				    "or later\n");

	अगर (pci_mem > IRONGATE_3GB)
		pci_mem = IRONGATE_3GB;
	IRONGATE0->pci_mem = pci_mem;
	alpha_mv.min_mem_address = pci_mem;
	अगर (memtop > pci_mem) अणु
#अगर_घोषित CONFIG_BLK_DEV_INITRD
		बाह्य अचिन्हित दीर्घ initrd_start, initrd_end;
		बाह्य व्योम *move_initrd(अचिन्हित दीर्घ);

		/* Move the initrd out of the way. */
		अगर (initrd_end && __pa(initrd_end) > pci_mem) अणु
			अचिन्हित दीर्घ size;

			size = initrd_end - initrd_start;
			memblock_मुक्त(__pa(initrd_start), PAGE_ALIGN(size));
			अगर (!move_initrd(pci_mem))
				prपूर्णांकk("irongate_init_arch: initrd too big "
				       "(%ldK)\ndisabling initrd\n",
				       size / 1024);
		पूर्ण
#पूर्ण_अगर
		memblock_reserve(pci_mem, memtop - pci_mem);
		prपूर्णांकk("irongate_init_arch: temporarily reserving "
			"region %08lx-%08lx for PCI\n", pci_mem, memtop - 1);
	पूर्ण
पूर्ण

अटल व्योम __init
irongate_setup_agp(व्योम)
अणु
	/* Disable the GART winकरोw. AGPGART करोesn't work due to yet
	   unresolved memory coherency issues... */
	IRONGATE0->agpva = IRONGATE0->agpva & ~0xf;
	alpha_agpgart_size = 0;
पूर्ण

व्योम __init
irongate_init_arch(व्योम)
अणु
	काष्ठा pci_controller *hose;
	पूर्णांक amd761 = (IRONGATE0->dev_venकरोr >> 16) > 0x7006;	/* Albacore? */

	IronECC = amd761 ? &IRONGATE0->bacsr54_eccms761 : &IRONGATE0->dramms;

	irongate_pci_clr_err();

	अगर (amd761)
		albacore_init_arch();

	irongate_setup_agp();

	/*
	 * Create our single hose.
	 */

	pci_isa_hose = hose = alloc_pci_controller();
	hose->io_space = &ioport_resource;
	hose->mem_space = &iomem_resource;
	hose->index = 0;

	/* This is क्रम userland consumption.  For some reason, the 40-bit
	   PIO bias that we use in the kernel through KSEG didn't work क्रम
	   the page table based user mappings.  So make sure we get the
	   43-bit PIO bias.  */
	hose->sparse_mem_base = 0;
	hose->sparse_io_base = 0;
	hose->dense_mem_base
	  = (IRONGATE_MEM & 0xffffffffffUL) | 0x80000000000UL;
	hose->dense_io_base
	  = (IRONGATE_IO & 0xffffffffffUL) | 0x80000000000UL;

	hose->sg_isa = hose->sg_pci = शून्य;
	__direct_map_base = 0;
	__direct_map_size = 0xffffffff;
पूर्ण

/*
 * IO map and AGP support
 */
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/agp_backend.h>
#समावेश <linux/agpgart.h>
#समावेश <linux/export.h>

#घोषणा GET_PAGE_सूची_OFF(addr) (addr >> 22)
#घोषणा GET_PAGE_सूची_IDX(addr) (GET_PAGE_सूची_OFF(addr))

#घोषणा GET_GATT_OFF(addr) ((addr & 0x003ff000) >> 12) 
#घोषणा GET_GATT(addr) (gatt_pages[GET_PAGE_सूची_IDX(addr)])

व्योम __iomem *
irongate_ioremap(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ size)
अणु
	काष्ठा vm_काष्ठा *area;
	अचिन्हित दीर्घ vaddr;
	अचिन्हित दीर्घ baddr, last;
	u32 *mmio_regs, *gatt_pages, *cur_gatt, pte;
	अचिन्हित दीर्घ gart_bus_addr;

	अगर (!alpha_agpgart_size)
		वापस (व्योम __iomem *)(addr + IRONGATE_MEM);

	gart_bus_addr = (अचिन्हित दीर्घ)IRONGATE0->bar0 &
			PCI_BASE_ADDRESS_MEM_MASK; 

	/* 
	 * Check क्रम within the AGP aperture...
	 */
	करो अणु
		/*
		 * Check the AGP area
		 */
		अगर (addr >= gart_bus_addr && addr + size - 1 < 
		    gart_bus_addr + alpha_agpgart_size)
			अवरोध;

		/*
		 * Not found - assume legacy ioremap
		 */
		वापस (व्योम __iomem *)(addr + IRONGATE_MEM);
	पूर्ण जबतक(0);

	mmio_regs = (u32 *)(((अचिन्हित दीर्घ)IRONGATE0->bar1 &
			PCI_BASE_ADDRESS_MEM_MASK) + IRONGATE_MEM);

	gatt_pages = (u32 *)(phys_to_virt(mmio_regs[1])); /* FIXME */

	/*
	 * Adjust the limits (mappings must be page aligned)
	 */
	अगर (addr & ~PAGE_MASK) अणु
		prपूर्णांकk("AGP ioremap failed... addr not page aligned (0x%lx)\n",
		       addr);
		वापस (व्योम __iomem *)(addr + IRONGATE_MEM);
	पूर्ण
	last = addr + size - 1;
	size = PAGE_ALIGN(last) - addr;

#अगर 0
	prपूर्णांकk("irongate_ioremap(0x%lx, 0x%lx)\n", addr, size);
	prपूर्णांकk("irongate_ioremap:  gart_bus_addr  0x%lx\n", gart_bus_addr);
	prपूर्णांकk("irongate_ioremap:  gart_aper_size 0x%lx\n", gart_aper_size);
	prपूर्णांकk("irongate_ioremap:  mmio_regs      %p\n", mmio_regs);
	prपूर्णांकk("irongate_ioremap:  gatt_pages     %p\n", gatt_pages);
	
	क्रम(baddr = addr; baddr <= last; baddr += PAGE_SIZE)
	अणु
		cur_gatt = phys_to_virt(GET_GATT(baddr) & ~1);
		pte = cur_gatt[GET_GATT_OFF(baddr)] & ~1;
		prपूर्णांकk("irongate_ioremap:  cur_gatt %p pte 0x%x\n",
		       cur_gatt, pte);
	पूर्ण
#पूर्ण_अगर

	/*
	 * Map it
	 */
	area = get_vm_area(size, VM_IOREMAP);
	अगर (!area) वापस शून्य;

	क्रम(baddr = addr, vaddr = (अचिन्हित दीर्घ)area->addr; 
	    baddr <= last; 
	    baddr += PAGE_SIZE, vaddr += PAGE_SIZE)
	अणु
		cur_gatt = phys_to_virt(GET_GATT(baddr) & ~1);
		pte = cur_gatt[GET_GATT_OFF(baddr)] & ~1;

		अगर (__alpha_remap_area_pages(vaddr,
					     pte, PAGE_SIZE, 0)) अणु
			prपूर्णांकk("AGP ioremap: FAILED to map...\n");
			vमुक्त(area->addr);
			वापस शून्य;
		पूर्ण
	पूर्ण

	flush_tlb_all();

	vaddr = (अचिन्हित दीर्घ)area->addr + (addr & ~PAGE_MASK);
#अगर 0
	prपूर्णांकk("irongate_ioremap(0x%lx, 0x%lx) returning 0x%lx\n",
	       addr, size, vaddr);
#पूर्ण_अगर
	वापस (व्योम __iomem *)vaddr;
पूर्ण
EXPORT_SYMBOL(irongate_ioremap);

व्योम
irongate_iounmap(अस्थिर व्योम __iomem *xaddr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ) xaddr;
	अगर (((दीर्घ)addr >> 41) == -2)
		वापस;	/* kseg map, nothing to करो */
	अगर (addr)
		वापस vमुक्त((व्योम *)(PAGE_MASK & addr)); 
पूर्ण
EXPORT_SYMBOL(irongate_iounmap);
