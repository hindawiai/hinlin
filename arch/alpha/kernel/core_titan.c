<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	linux/arch/alpha/kernel/core_titan.c
 *
 * Code common to all TITAN core logic chips.
 */

#घोषणा __EXTERN_INLINE अंतरभूत
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/core_titan.h>
#अघोषित __EXTERN_INLINE

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/sched.h>
#समावेश <linux/init.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/memblock.h>

#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/vga.h>

#समावेश "proto.h"
#समावेश "pci_impl.h"

/* Save Titan configuration data as the console had it set up.  */

काष्ठा
अणु
	अचिन्हित दीर्घ wsba[4];
	अचिन्हित दीर्घ wsm[4];
	अचिन्हित दीर्घ tba[4];
पूर्ण saved_config[4] __attribute__((common));

/*
 * Is PChip 1 present? No need to query it more than once.
 */
अटल पूर्णांक titan_pchip1_present;

/*
 * BIOS32-style PCI पूर्णांकerface:
 */

#घोषणा DEBUG_CONFIG 0

#अगर DEBUG_CONFIG
# define DBG_CFG(args)	prपूर्णांकk args
#अन्यथा
# define DBG_CFG(args)
#पूर्ण_अगर


/*
 * Routines to access TIG रेजिस्टरs.
 */
अटल अंतरभूत अस्थिर अचिन्हित दीर्घ *
mk_tig_addr(पूर्णांक offset)
अणु
	वापस (अस्थिर अचिन्हित दीर्घ *)(TITAN_TIG_SPACE + (offset << 6));
पूर्ण

अटल अंतरभूत u8 
titan_पढ़ो_tig(पूर्णांक offset, u8 value)
अणु
	अस्थिर अचिन्हित दीर्घ *tig_addr = mk_tig_addr(offset);
	वापस (u8)(*tig_addr & 0xff);
पूर्ण

अटल अंतरभूत व्योम 
titan_ग_लिखो_tig(पूर्णांक offset, u8 value)
अणु
	अस्थिर अचिन्हित दीर्घ *tig_addr = mk_tig_addr(offset);
	*tig_addr = (अचिन्हित दीर्घ)value;
पूर्ण


/*
 * Given a bus, device, and function number, compute resulting
 * configuration space address
 * accordingly.  It is thereक्रमe not safe to have concurrent
 * invocations to configuration space access routines, but there
 * really shouldn't be any need क्रम this.
 *
 * Note that all config space accesses use Type 1 address क्रमmat.
 *
 * Note also that type 1 is determined by non-zero bus number.
 *
 * Type 1:
 *
 *  3 3|3 3 2 2|2 2 2 2|2 2 2 2|1 1 1 1|1 1 1 1|1 1 
 *  3 2|1 0 9 8|7 6 5 4|3 2 1 0|9 8 7 6|5 4 3 2|1 0 9 8|7 6 5 4|3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * | | | | | | | | | | |B|B|B|B|B|B|B|B|D|D|D|D|D|F|F|F|R|R|R|R|R|R|0|1|
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 *	31:24	reserved
 *	23:16	bus number (8 bits = 128 possible buses)
 *	15:11	Device number (5 bits)
 *	10:8	function number
 *	 7:2	रेजिस्टर number
 *  
 * Notes:
 *	The function number selects which function of a multi-function device 
 *	(e.g., SCSI and Ethernet).
 * 
 *	The रेजिस्टर selects a DWORD (32 bit) रेजिस्टर offset.  Hence it
 *	करोesn't get shअगरted by 2 bits as we want to "drop" the bottom two
 *	bits.
 */

अटल पूर्णांक
mk_conf_addr(काष्ठा pci_bus *pbus, अचिन्हित पूर्णांक device_fn, पूर्णांक where,
	     अचिन्हित दीर्घ *pci_addr, अचिन्हित अक्षर *type1)
अणु
	काष्ठा pci_controller *hose = pbus->sysdata;
	अचिन्हित दीर्घ addr;
	u8 bus = pbus->number;

	DBG_CFG(("mk_conf_addr(bus=%d ,device_fn=0x%x, where=0x%x, "
		 "pci_addr=0x%p, type1=0x%p)\n",
		 bus, device_fn, where, pci_addr, type1));

	अगर (!pbus->parent) /* No parent means peer PCI bus. */
		bus = 0;
        *type1 = (bus != 0);

        addr = (bus << 16) | (device_fn << 8) | where;
	addr |= hose->config_space_base;
		
	*pci_addr = addr;
	DBG_CFG(("mk_conf_addr: returning pci_addr 0x%lx\n", addr));
	वापस 0;
पूर्ण

अटल पूर्णांक
titan_पढ़ो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक where,
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
titan_ग_लिखो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक where,
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

काष्ठा pci_ops titan_pci_ops = 
अणु
	.पढ़ो =		titan_पढ़ो_config,
	.ग_लिखो =	titan_ग_लिखो_config,
पूर्ण;


व्योम
titan_pci_tbi(काष्ठा pci_controller *hose, dma_addr_t start, dma_addr_t end)
अणु
	titan_pachip *pachip = 
	  (hose->index & 1) ? TITAN_pachip1 : TITAN_pachip0;
	titan_pachip_port *port;
	अस्थिर अचिन्हित दीर्घ *csr;
	अचिन्हित दीर्घ value;

	/* Get the right hose.  */
	port = &pachip->g_port;
	अगर (hose->index & 2) 
		port = &pachip->a_port;

	/* We can invalidate up to 8 tlb entries in a go.  The flush
	   matches against <31:16> in the pci address.  
	   Note that gtlbi* and atlbi* are in the same place in the g_port
	   and a_port, respectively, so the g_port offset can be used
	   even अगर hose is an a_port */
	csr = &port->port_specअगरic.g.gtlbia.csr;
	अगर (((start ^ end) & 0xffff0000) == 0)
		csr = &port->port_specअगरic.g.gtlbiv.csr;

	/* For TBIA, it करोesn't matter what value we ग_लिखो.  For TBI, 
	   it's the shअगरted tag bits.  */
	value = (start & 0xffff0000) >> 12;

	wmb();
	*csr = value;
	mb();
	*csr;
पूर्ण

अटल पूर्णांक
titan_query_agp(titan_pachip_port *port)
अणु
	जोड़ TPAchipPCTL pctl;

	/* set up APCTL */
	pctl.pctl_q_whole = port->pctl.csr;

	वापस pctl.pctl_r_bits.apctl_v_agp_present;

पूर्ण

अटल व्योम __init
titan_init_one_pachip_port(titan_pachip_port *port, पूर्णांक index)
अणु
	काष्ठा pci_controller *hose;

	hose = alloc_pci_controller();
	अगर (index == 0)
		pci_isa_hose = hose;
	hose->io_space = alloc_resource();
	hose->mem_space = alloc_resource();

	/*
	 * This is क्रम userland consumption.  The 40-bit PIO bias that we 
	 * use in the kernel through KSEG करोesn't work in the page table 
	 * based user mappings. (43-bit KSEG sign extends the physical
	 * address from bit 40 to hit the I/O bit - mapped addresses करोn't).
	 * So make sure we get the 43-bit PIO bias.  
	 */
	hose->sparse_mem_base = 0;
	hose->sparse_io_base = 0;
	hose->dense_mem_base
	  = (TITAN_MEM(index) & 0xffffffffffUL) | 0x80000000000UL;
	hose->dense_io_base
	  = (TITAN_IO(index) & 0xffffffffffUL) | 0x80000000000UL;

	hose->config_space_base = TITAN_CONF(index);
	hose->index = index;

	hose->io_space->start = TITAN_IO(index) - TITAN_IO_BIAS;
	hose->io_space->end = hose->io_space->start + TITAN_IO_SPACE - 1;
	hose->io_space->name = pci_io_names[index];
	hose->io_space->flags = IORESOURCE_IO;

	hose->mem_space->start = TITAN_MEM(index) - TITAN_MEM_BIAS;
	hose->mem_space->end = hose->mem_space->start + 0xffffffff;
	hose->mem_space->name = pci_mem_names[index];
	hose->mem_space->flags = IORESOURCE_MEM;

	अगर (request_resource(&ioport_resource, hose->io_space) < 0)
		prपूर्णांकk(KERN_ERR "Failed to request IO on hose %d\n", index);
	अगर (request_resource(&iomem_resource, hose->mem_space) < 0)
		prपूर्णांकk(KERN_ERR "Failed to request MEM on hose %d\n", index);

	/*
	 * Save the existing PCI winकरोw translations.  SRM will 
	 * need them when we go to reboot.
	 */
	saved_config[index].wsba[0] = port->wsba[0].csr;
	saved_config[index].wsm[0]  = port->wsm[0].csr;
	saved_config[index].tba[0]  = port->tba[0].csr;

	saved_config[index].wsba[1] = port->wsba[1].csr;
	saved_config[index].wsm[1]  = port->wsm[1].csr;
	saved_config[index].tba[1]  = port->tba[1].csr;

	saved_config[index].wsba[2] = port->wsba[2].csr;
	saved_config[index].wsm[2]  = port->wsm[2].csr;
	saved_config[index].tba[2]  = port->tba[2].csr;

	saved_config[index].wsba[3] = port->wsba[3].csr;
	saved_config[index].wsm[3]  = port->wsm[3].csr;
	saved_config[index].tba[3]  = port->tba[3].csr;

	/*
	 * Set up the PCI to मुख्य memory translation winकरोws.
	 *
	 * Note: Winकरोw 3 on Titan is Scatter-Gather ONLY.
	 *
	 * Winकरोw 0 is scatter-gather 8MB at 8MB (क्रम isa)
	 * Winकरोw 1 is direct access 1GB at 2GB
	 * Winकरोw 2 is scatter-gather 1GB at 3GB
	 */
	hose->sg_isa = iommu_arena_new(hose, 0x00800000, 0x00800000,
				       SMP_CACHE_BYTES);
	hose->sg_isa->align_entry = 8; /* 64KB क्रम ISA */

	hose->sg_pci = iommu_arena_new(hose, 0xc0000000, 0x40000000,
				       SMP_CACHE_BYTES);
	hose->sg_pci->align_entry = 4; /* Titan caches 4 PTEs at a समय */

	port->wsba[0].csr = hose->sg_isa->dma_base | 3;
	port->wsm[0].csr  = (hose->sg_isa->size - 1) & 0xfff00000;
	port->tba[0].csr  = virt_to_phys(hose->sg_isa->ptes);

	port->wsba[1].csr = __direct_map_base | 1;
	port->wsm[1].csr  = (__direct_map_size - 1) & 0xfff00000;
	port->tba[1].csr  = 0;

	port->wsba[2].csr = hose->sg_pci->dma_base | 3;
	port->wsm[2].csr  = (hose->sg_pci->size - 1) & 0xfff00000;
	port->tba[2].csr  = virt_to_phys(hose->sg_pci->ptes);

	port->wsba[3].csr = 0;

	/* Enable the Monster Winकरोw to make DAC pci64 possible.  */
	port->pctl.csr |= pctl_m_mwin;

	/*
	 * If it's an AGP port, initialize agplastwr.
	 */
	अगर (titan_query_agp(port)) 
		port->port_specअगरic.a.agplastwr.csr = __direct_map_base;

	titan_pci_tbi(hose, 0, -1);
पूर्ण

अटल व्योम __init
titan_init_pachips(titan_pachip *pachip0, titan_pachip *pachip1)
अणु
	titan_pchip1_present = TITAN_cchip->csc.csr & 1L<<14;

	/* Init the ports in hose order... */
	titan_init_one_pachip_port(&pachip0->g_port, 0);	/* hose 0 */
	अगर (titan_pchip1_present)
		titan_init_one_pachip_port(&pachip1->g_port, 1);/* hose 1 */
	titan_init_one_pachip_port(&pachip0->a_port, 2);	/* hose 2 */
	अगर (titan_pchip1_present)
		titan_init_one_pachip_port(&pachip1->a_port, 3);/* hose 3 */
पूर्ण

व्योम __init
titan_init_arch(व्योम)
अणु
#अगर 0
	prपूर्णांकk("%s: titan_init_arch()\n", __func__);
	prपूर्णांकk("%s: CChip registers:\n", __func__);
	prपूर्णांकk("%s: CSR_CSC 0x%lx\n", __func__, TITAN_cchip->csc.csr);
	prपूर्णांकk("%s: CSR_MTR 0x%lx\n", __func__, TITAN_cchip->mtr.csr);
	prपूर्णांकk("%s: CSR_MISC 0x%lx\n", __func__, TITAN_cchip->misc.csr);
	prपूर्णांकk("%s: CSR_DIM0 0x%lx\n", __func__, TITAN_cchip->dim0.csr);
	prपूर्णांकk("%s: CSR_DIM1 0x%lx\n", __func__, TITAN_cchip->dim1.csr);
	prपूर्णांकk("%s: CSR_DIR0 0x%lx\n", __func__, TITAN_cchip->dir0.csr);
	prपूर्णांकk("%s: CSR_DIR1 0x%lx\n", __func__, TITAN_cchip->dir1.csr);
	prपूर्णांकk("%s: CSR_DRIR 0x%lx\n", __func__, TITAN_cchip->drir.csr);

	prपूर्णांकk("%s: DChip registers:\n", __func__);
	prपूर्णांकk("%s: CSR_DSC 0x%lx\n", __func__, TITAN_dchip->dsc.csr);
	prपूर्णांकk("%s: CSR_STR 0x%lx\n", __func__, TITAN_dchip->str.csr);
	prपूर्णांकk("%s: CSR_DREV 0x%lx\n", __func__, TITAN_dchip->drev.csr);
#पूर्ण_अगर

	boot_cpuid = __hard_smp_processor_id();

	/* With multiple PCI busses, we play with I/O as physical addrs.  */
	ioport_resource.end = ~0UL;
	iomem_resource.end = ~0UL;

	/* PCI DMA Direct Mapping is 1GB at 2GB.  */
	__direct_map_base = 0x80000000;
	__direct_map_size = 0x40000000;

	/* Init the PA chip(s).  */
	titan_init_pachips(TITAN_pachip0, TITAN_pachip1);

	/* Check क्रम graphic console location (अगर any).  */
	find_console_vga_hose();
पूर्ण

अटल व्योम
titan_समाप्त_one_pachip_port(titan_pachip_port *port, पूर्णांक index)
अणु
	port->wsba[0].csr = saved_config[index].wsba[0];
	port->wsm[0].csr  = saved_config[index].wsm[0];
	port->tba[0].csr  = saved_config[index].tba[0];

	port->wsba[1].csr = saved_config[index].wsba[1];
	port->wsm[1].csr  = saved_config[index].wsm[1];
	port->tba[1].csr  = saved_config[index].tba[1];

	port->wsba[2].csr = saved_config[index].wsba[2];
	port->wsm[2].csr  = saved_config[index].wsm[2];
	port->tba[2].csr  = saved_config[index].tba[2];

	port->wsba[3].csr = saved_config[index].wsba[3];
	port->wsm[3].csr  = saved_config[index].wsm[3];
	port->tba[3].csr  = saved_config[index].tba[3];
पूर्ण

अटल व्योम
titan_समाप्त_pachips(titan_pachip *pachip0, titan_pachip *pachip1)
अणु
	अगर (titan_pchip1_present) अणु
		titan_समाप्त_one_pachip_port(&pachip1->g_port, 1);
		titan_समाप्त_one_pachip_port(&pachip1->a_port, 3);
	पूर्ण
	titan_समाप्त_one_pachip_port(&pachip0->g_port, 0);
	titan_समाप्त_one_pachip_port(&pachip0->a_port, 2);
पूर्ण

व्योम
titan_समाप्त_arch(पूर्णांक mode)
अणु
	titan_समाप्त_pachips(TITAN_pachip0, TITAN_pachip1);
पूर्ण


/*
 * IO map support.
 */

व्योम __iomem *
titan_ioporपंचांगap(अचिन्हित दीर्घ addr)
अणु
	FIXUP_IOADDR_VGA(addr);
	वापस (व्योम __iomem *)(addr + TITAN_IO_BIAS);
पूर्ण


व्योम __iomem *
titan_ioremap(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ size)
अणु
	पूर्णांक h = (addr & TITAN_HOSE_MASK) >> TITAN_HOSE_SHIFT;
	अचिन्हित दीर्घ baddr = addr & ~TITAN_HOSE_MASK;
	अचिन्हित दीर्घ last = baddr + size - 1;
	काष्ठा pci_controller *hose;	
	काष्ठा vm_काष्ठा *area;
	अचिन्हित दीर्घ vaddr;
	अचिन्हित दीर्घ *ptes;
	अचिन्हित दीर्घ pfn;

#अगर_घोषित CONFIG_VGA_HOSE
	/*
	 * Adjust the address and hose, अगर necessary.
	 */ 
	अगर (pci_vga_hose && __is_mem_vga(addr)) अणु
		h = pci_vga_hose->index;
		addr += pci_vga_hose->mem_space->start;
	पूर्ण
#पूर्ण_अगर

	/*
	 * Find the hose.
	 */
	क्रम (hose = hose_head; hose; hose = hose->next)
		अगर (hose->index == h)
			अवरोध;
	अगर (!hose)
		वापस शून्य;

	/*
	 * Is it direct-mapped?
	 */
	अगर ((baddr >= __direct_map_base) && 
	    ((baddr + size - 1) < __direct_map_base + __direct_map_size)) अणु
		vaddr = addr - __direct_map_base + TITAN_MEM_BIAS;
		वापस (व्योम __iomem *) vaddr;
	पूर्ण

	/* 
	 * Check the scatter-gather arena.
	 */
	अगर (hose->sg_pci &&
	    baddr >= (अचिन्हित दीर्घ)hose->sg_pci->dma_base &&
	    last < (अचिन्हित दीर्घ)hose->sg_pci->dma_base + hose->sg_pci->size)अणु

		/*
		 * Adjust the limits (mappings must be page aligned)
		 */
		baddr -= hose->sg_pci->dma_base;
		last -= hose->sg_pci->dma_base;
		baddr &= PAGE_MASK;
		size = PAGE_ALIGN(last) - baddr;

		/*
		 * Map it
		 */
		area = get_vm_area(size, VM_IOREMAP);
		अगर (!area) अणु
			prपूर्णांकk("ioremap failed... no vm_area...\n");
			वापस शून्य;
		पूर्ण

		ptes = hose->sg_pci->ptes;
		क्रम (vaddr = (अचिन्हित दीर्घ)area->addr; 
		    baddr <= last; 
		    baddr += PAGE_SIZE, vaddr += PAGE_SIZE) अणु
			pfn = ptes[baddr >> PAGE_SHIFT];
			अगर (!(pfn & 1)) अणु
				prपूर्णांकk("ioremap failed... pte not valid...\n");
				vमुक्त(area->addr);
				वापस शून्य;
			पूर्ण
			pfn >>= 1;	/* make it a true pfn */
			
			अगर (__alpha_remap_area_pages(vaddr,
						     pfn << PAGE_SHIFT, 
						     PAGE_SIZE, 0)) अणु
				prपूर्णांकk("FAILED to remap_area_pages...\n");
				vमुक्त(area->addr);
				वापस शून्य;
			पूर्ण
		पूर्ण

		flush_tlb_all();

		vaddr = (अचिन्हित दीर्घ)area->addr + (addr & ~PAGE_MASK);
		वापस (व्योम __iomem *) vaddr;
	पूर्ण

	/* Assume a legacy (पढ़ो: VGA) address, and वापस appropriately. */
	वापस (व्योम __iomem *)(addr + TITAN_MEM_BIAS);
पूर्ण

व्योम
titan_iounmap(अस्थिर व्योम __iomem *xaddr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ) xaddr;
	अगर (addr >= VMALLOC_START)
		vमुक्त((व्योम *)(PAGE_MASK & addr)); 
पूर्ण

पूर्णांक
titan_is_mmio(स्थिर अस्थिर व्योम __iomem *xaddr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ) xaddr;

	अगर (addr >= VMALLOC_START)
		वापस 1;
	अन्यथा
		वापस (addr & 0x100000000UL) == 0;
पूर्ण

#अगर_अघोषित CONFIG_ALPHA_GENERIC
EXPORT_SYMBOL(titan_ioporपंचांगap);
EXPORT_SYMBOL(titan_ioremap);
EXPORT_SYMBOL(titan_iounmap);
EXPORT_SYMBOL(titan_is_mmio);
#पूर्ण_अगर

/*
 * AGP GART Support.
 */
#समावेश <linux/agp_backend.h>
#समावेश <यंत्र/agp_backend.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>

काष्ठा titan_agp_aperture अणु
	काष्ठा pci_iommu_arena *arena;
	दीर्घ pg_start;
	दीर्घ pg_count;
पूर्ण;

अटल पूर्णांक
titan_agp_setup(alpha_agp_info *agp)
अणु
	काष्ठा titan_agp_aperture *aper;

	अगर (!alpha_agpgart_size)
		वापस -ENOMEM;

	aper = kदो_स्मृति(माप(काष्ठा titan_agp_aperture), GFP_KERNEL);
	अगर (aper == शून्य)
		वापस -ENOMEM;

	aper->arena = agp->hose->sg_pci;
	aper->pg_count = alpha_agpgart_size / PAGE_SIZE;
	aper->pg_start = iommu_reserve(aper->arena, aper->pg_count,
				       aper->pg_count - 1);
	अगर (aper->pg_start < 0) अणु
		prपूर्णांकk(KERN_ERR "Failed to reserve AGP memory\n");
		kमुक्त(aper);
		वापस -ENOMEM;
	पूर्ण

	agp->aperture.bus_base = 
		aper->arena->dma_base + aper->pg_start * PAGE_SIZE;
	agp->aperture.size = aper->pg_count * PAGE_SIZE;
	agp->aperture.sysdata = aper;

	वापस 0;
पूर्ण

अटल व्योम
titan_agp_cleanup(alpha_agp_info *agp)
अणु
	काष्ठा titan_agp_aperture *aper = agp->aperture.sysdata;
	पूर्णांक status;

	status = iommu_release(aper->arena, aper->pg_start, aper->pg_count);
	अगर (status == -EBUSY) अणु
		prपूर्णांकk(KERN_WARNING 
		       "Attempted to release bound AGP memory - unbinding\n");
		iommu_unbind(aper->arena, aper->pg_start, aper->pg_count);
		status = iommu_release(aper->arena, aper->pg_start, 
				       aper->pg_count);
	पूर्ण
	अगर (status < 0)
		prपूर्णांकk(KERN_ERR "Failed to release AGP memory\n");

	kमुक्त(aper);
	kमुक्त(agp);
पूर्ण

अटल पूर्णांक
titan_agp_configure(alpha_agp_info *agp)
अणु
	जोड़ TPAchipPCTL pctl;
	titan_pachip_port *port = agp->निजी;
	pctl.pctl_q_whole = port->pctl.csr;

	/* Side-Band Addressing? */
	pctl.pctl_r_bits.apctl_v_agp_sba_en = agp->mode.bits.sba;

	/* AGP Rate? */
	pctl.pctl_r_bits.apctl_v_agp_rate = 0;		/* 1x */
	अगर (agp->mode.bits.rate & 2) 
		pctl.pctl_r_bits.apctl_v_agp_rate = 1;	/* 2x */
#अगर 0
	अगर (agp->mode.bits.rate & 4) 
		pctl.pctl_r_bits.apctl_v_agp_rate = 2;	/* 4x */
#पूर्ण_अगर
	
	/* RQ Depth? */
	pctl.pctl_r_bits.apctl_v_agp_hp_rd = 2;
	pctl.pctl_r_bits.apctl_v_agp_lp_rd = 7;

	/*
	 * AGP Enable.
	 */
	pctl.pctl_r_bits.apctl_v_agp_en = agp->mode.bits.enable;

	/* Tell the user.  */
	prपूर्णांकk("Enabling AGP: %dX%s\n", 
	       1 << pctl.pctl_r_bits.apctl_v_agp_rate,
	       pctl.pctl_r_bits.apctl_v_agp_sba_en ? " - SBA" : "");
	       
	/* Write it.  */
	port->pctl.csr = pctl.pctl_q_whole;
	
	/* And रुको at least 5000 66MHz cycles (per Titan spec).  */
	udelay(100);

	वापस 0;
पूर्ण

अटल पूर्णांक 
titan_agp_bind_memory(alpha_agp_info *agp, off_t pg_start, काष्ठा agp_memory *mem)
अणु
	काष्ठा titan_agp_aperture *aper = agp->aperture.sysdata;
	वापस iommu_bind(aper->arena, aper->pg_start + pg_start, 
			  mem->page_count, mem->pages);
पूर्ण

अटल पूर्णांक 
titan_agp_unbind_memory(alpha_agp_info *agp, off_t pg_start, काष्ठा agp_memory *mem)
अणु
	काष्ठा titan_agp_aperture *aper = agp->aperture.sysdata;
	वापस iommu_unbind(aper->arena, aper->pg_start + pg_start,
			    mem->page_count);
पूर्ण

अटल अचिन्हित दीर्घ
titan_agp_translate(alpha_agp_info *agp, dma_addr_t addr)
अणु
	काष्ठा titan_agp_aperture *aper = agp->aperture.sysdata;
	अचिन्हित दीर्घ baddr = addr - aper->arena->dma_base;
	अचिन्हित दीर्घ pte;

	अगर (addr < agp->aperture.bus_base ||
	    addr >= agp->aperture.bus_base + agp->aperture.size) अणु
		prपूर्णांकk("%s: addr out of range\n", __func__);
		वापस -EINVAL;
	पूर्ण

	pte = aper->arena->ptes[baddr >> PAGE_SHIFT];
	अगर (!(pte & 1)) अणु
		prपूर्णांकk("%s: pte not valid\n", __func__);
		वापस -EINVAL;
	पूर्ण

	वापस (pte >> 1) << PAGE_SHIFT;
पूर्ण

काष्ठा alpha_agp_ops titan_agp_ops =
अणु
	.setup		= titan_agp_setup,
	.cleanup	= titan_agp_cleanup,
	.configure	= titan_agp_configure,
	.bind		= titan_agp_bind_memory,
	.unbind		= titan_agp_unbind_memory,
	.translate	= titan_agp_translate
पूर्ण;

alpha_agp_info *
titan_agp_info(व्योम)
अणु
	alpha_agp_info *agp;
	काष्ठा pci_controller *hose;
	titan_pachip_port *port;
	पूर्णांक hosक्रमागत = -1;
	जोड़ TPAchipPCTL pctl;

	/*
	 * Find the AGP port.
	 */
	port = &TITAN_pachip0->a_port;
	अगर (titan_query_agp(port))
		hosक्रमागत = 2;
	अगर (hosक्रमागत < 0 && 
	    titan_pchip1_present &&
	    titan_query_agp(port = &TITAN_pachip1->a_port)) 
		hosक्रमागत = 3;
	
	/*
	 * Find the hose the port is on.
	 */
	क्रम (hose = hose_head; hose; hose = hose->next)
		अगर (hose->index == hosक्रमागत)
			अवरोध;

	अगर (!hose || !hose->sg_pci)
		वापस शून्य;

	/*
	 * Allocate the info काष्ठाure.
	 */
	agp = kदो_स्मृति(माप(*agp), GFP_KERNEL);
	अगर (!agp)
		वापस शून्य;

	/*
	 * Fill it in.
	 */
	agp->hose = hose;
	agp->निजी = port;
	agp->ops = &titan_agp_ops;

	/*
	 * Aperture - not configured until ops.setup().
	 *
	 * FIXME - should we go ahead and allocate it here?
	 */
	agp->aperture.bus_base = 0;
	agp->aperture.size = 0;
	agp->aperture.sysdata = शून्य;

	/*
	 * Capabilities.
	 */
	agp->capability.lw = 0;
	agp->capability.bits.rate = 3; 	/* 2x, 1x */
	agp->capability.bits.sba = 1;
	agp->capability.bits.rq = 7;	/* 8 - 1 */

	/*
	 * Mode.
	 */
	pctl.pctl_q_whole = port->pctl.csr;
	agp->mode.lw = 0;
	agp->mode.bits.rate = 1 << pctl.pctl_r_bits.apctl_v_agp_rate;
	agp->mode.bits.sba = pctl.pctl_r_bits.apctl_v_agp_sba_en;
	agp->mode.bits.rq = 7;	/* RQ Depth? */
	agp->mode.bits.enable = pctl.pctl_r_bits.apctl_v_agp_en;

	वापस agp;
पूर्ण
