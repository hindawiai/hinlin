<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	linux/arch/alpha/kernel/core_tsunami.c
 *
 * Based on code written by David A. Rusling (david.rusling@reo.mts.dec.com).
 *
 * Code common to all TSUNAMI core logic chips.
 */

#घोषणा __EXTERN_INLINE अंतरभूत
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/core_tsunami.h>
#अघोषित __EXTERN_INLINE

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/sched.h>
#समावेश <linux/init.h>
#समावेश <linux/memblock.h>

#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/vga.h>

#समावेश "proto.h"
#समावेश "pci_impl.h"

/* Save Tsunami configuration data as the console had it set up.  */

काष्ठा 
अणु
	अचिन्हित दीर्घ wsba[4];
	अचिन्हित दीर्घ wsm[4];
	अचिन्हित दीर्घ tba[4];
पूर्ण saved_config[2] __attribute__((common));

/*
 * NOTE: Herein lie back-to-back mb inकाष्ठाions.  They are magic. 
 * One plausible explanation is that the I/O controller करोes not properly
 * handle the प्रणाली transaction.  Another involves timing.  Ho hum.
 */

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
tsunami_पढ़ो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक where,
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
tsunami_ग_लिखो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक where,
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

काष्ठा pci_ops tsunami_pci_ops = 
अणु
	.पढ़ो =		tsunami_पढ़ो_config,
	.ग_लिखो = 	tsunami_ग_लिखो_config,
पूर्ण;

व्योम
tsunami_pci_tbi(काष्ठा pci_controller *hose, dma_addr_t start, dma_addr_t end)
अणु
	tsunami_pchip *pchip = hose->index ? TSUNAMI_pchip1 : TSUNAMI_pchip0;
	अस्थिर अचिन्हित दीर्घ *csr;
	अचिन्हित दीर्घ value;

	/* We can invalidate up to 8 tlb entries in a go.  The flush
	   matches against <31:16> in the pci address.  */
	csr = &pchip->tlbia.csr;
	अगर (((start ^ end) & 0xffff0000) == 0)
		csr = &pchip->tlbiv.csr;

	/* For TBIA, it करोesn't matter what value we ग_लिखो.  For TBI, 
	   it's the shअगरted tag bits.  */
	value = (start & 0xffff0000) >> 12;

	*csr = value;
	mb();
	*csr;
पूर्ण

#अगर_घोषित NXM_MACHINE_CHECKS_ON_TSUNAMI
अटल दीर्घ __init
tsunami_probe_पढ़ो(अस्थिर अचिन्हित दीर्घ *vaddr)
अणु
	दीर्घ करोnt_care, probe_result;
	पूर्णांक cpu = smp_processor_id();
	पूर्णांक s = swpipl(IPL_MCHECK - 1);

	mcheck_taken(cpu) = 0;
	mcheck_expected(cpu) = 1;
	mb();
	करोnt_care = *vaddr;
	draina();
	mcheck_expected(cpu) = 0;
	probe_result = !mcheck_taken(cpu);
	mcheck_taken(cpu) = 0;
	setipl(s);

	prपूर्णांकk("dont_care == 0x%lx\n", करोnt_care);

	वापस probe_result;
पूर्ण

अटल दीर्घ __init
tsunami_probe_ग_लिखो(अस्थिर अचिन्हित दीर्घ *vaddr)
अणु
	दीर्घ true_contents, probe_result = 1;

	TSUNAMI_cchip->misc.csr |= (1L << 28); /* clear NXM... */
	true_contents = *vaddr;
	*vaddr = 0;
	draina();
	अगर (TSUNAMI_cchip->misc.csr & (1L << 28)) अणु
		पूर्णांक source = (TSUNAMI_cchip->misc.csr >> 29) & 7;
		TSUNAMI_cchip->misc.csr |= (1L << 28); /* ...and unlock NXS. */
		probe_result = 0;
		prपूर्णांकk("tsunami_probe_write: unit %d at 0x%016lx\n", source,
		       (अचिन्हित दीर्घ)vaddr);
	पूर्ण
	अगर (probe_result)
		*vaddr = true_contents;
	वापस probe_result;
पूर्ण
#अन्यथा
#घोषणा tsunami_probe_पढ़ो(ADDR) 1
#पूर्ण_अगर /* NXM_MACHINE_CHECKS_ON_TSUNAMI */

अटल व्योम __init
tsunami_init_one_pchip(tsunami_pchip *pchip, पूर्णांक index)
अणु
	काष्ठा pci_controller *hose;

	अगर (tsunami_probe_पढ़ो(&pchip->pctl.csr) == 0)
		वापस;

	hose = alloc_pci_controller();
	अगर (index == 0)
		pci_isa_hose = hose;
	hose->io_space = alloc_resource();
	hose->mem_space = alloc_resource();

	/* This is क्रम userland consumption.  For some reason, the 40-bit
	   PIO bias that we use in the kernel through KSEG didn't work क्रम
	   the page table based user mappings.  So make sure we get the
	   43-bit PIO bias.  */
	hose->sparse_mem_base = 0;
	hose->sparse_io_base = 0;
	hose->dense_mem_base
	  = (TSUNAMI_MEM(index) & 0xffffffffffL) | 0x80000000000L;
	hose->dense_io_base
	  = (TSUNAMI_IO(index) & 0xffffffffffL) | 0x80000000000L;

	hose->config_space_base = TSUNAMI_CONF(index);
	hose->index = index;

	hose->io_space->start = TSUNAMI_IO(index) - TSUNAMI_IO_BIAS;
	hose->io_space->end = hose->io_space->start + TSUNAMI_IO_SPACE - 1;
	hose->io_space->name = pci_io_names[index];
	hose->io_space->flags = IORESOURCE_IO;

	hose->mem_space->start = TSUNAMI_MEM(index) - TSUNAMI_MEM_BIAS;
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

	saved_config[index].wsba[0] = pchip->wsba[0].csr;
	saved_config[index].wsm[0] = pchip->wsm[0].csr;
	saved_config[index].tba[0] = pchip->tba[0].csr;

	saved_config[index].wsba[1] = pchip->wsba[1].csr;
	saved_config[index].wsm[1] = pchip->wsm[1].csr;
	saved_config[index].tba[1] = pchip->tba[1].csr;

	saved_config[index].wsba[2] = pchip->wsba[2].csr;
	saved_config[index].wsm[2] = pchip->wsm[2].csr;
	saved_config[index].tba[2] = pchip->tba[2].csr;

	saved_config[index].wsba[3] = pchip->wsba[3].csr;
	saved_config[index].wsm[3] = pchip->wsm[3].csr;
	saved_config[index].tba[3] = pchip->tba[3].csr;

	/*
	 * Set up the PCI to मुख्य memory translation winकरोws.
	 *
	 * Note: Winकरोw 3 is scatter-gather only
	 * 
	 * Winकरोw 0 is scatter-gather 8MB at 8MB (क्रम isa)
	 * Winकरोw 1 is scatter-gather (up to) 1GB at 1GB
	 * Winकरोw 2 is direct access 2GB at 2GB
	 *
	 * NOTE: we need the align_entry settings क्रम Acer devices on ES40,
	 * specअगरically floppy and IDE when memory is larger than 2GB.
	 */
	hose->sg_isa = iommu_arena_new(hose, 0x00800000, 0x00800000,
				       SMP_CACHE_BYTES);
	/* Initially set क्रम 4 PTEs, but will be overridden to 64K क्रम ISA. */
        hose->sg_isa->align_entry = 4;

	hose->sg_pci = iommu_arena_new(hose, 0x40000000,
				       size_क्रम_memory(0x40000000),
				       SMP_CACHE_BYTES);
        hose->sg_pci->align_entry = 4; /* Tsunami caches 4 PTEs at a समय */

	__direct_map_base = 0x80000000;
	__direct_map_size = 0x80000000;

	pchip->wsba[0].csr = hose->sg_isa->dma_base | 3;
	pchip->wsm[0].csr  = (hose->sg_isa->size - 1) & 0xfff00000;
	pchip->tba[0].csr  = virt_to_phys(hose->sg_isa->ptes);

	pchip->wsba[1].csr = hose->sg_pci->dma_base | 3;
	pchip->wsm[1].csr  = (hose->sg_pci->size - 1) & 0xfff00000;
	pchip->tba[1].csr  = virt_to_phys(hose->sg_pci->ptes);

	pchip->wsba[2].csr = 0x80000000 | 1;
	pchip->wsm[2].csr  = (0x80000000 - 1) & 0xfff00000;
	pchip->tba[2].csr  = 0;

	pchip->wsba[3].csr = 0;

	/* Enable the Monster Winकरोw to make DAC pci64 possible. */
	pchip->pctl.csr |= pctl_m_mwin;

	tsunami_pci_tbi(hose, 0, -1);
पूर्ण


व्योम __iomem *
tsunami_ioporपंचांगap(अचिन्हित दीर्घ addr)
अणु
	FIXUP_IOADDR_VGA(addr);
	वापस (व्योम __iomem *)(addr + TSUNAMI_IO_BIAS);
पूर्ण

व्योम __iomem *
tsunami_ioremap(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ size)
अणु
	FIXUP_MEMADDR_VGA(addr);
	वापस (व्योम __iomem *)(addr + TSUNAMI_MEM_BIAS);
पूर्ण

#अगर_अघोषित CONFIG_ALPHA_GENERIC
EXPORT_SYMBOL(tsunami_ioporपंचांगap);
EXPORT_SYMBOL(tsunami_ioremap);
#पूर्ण_अगर

व्योम __init
tsunami_init_arch(व्योम)
अणु
#अगर_घोषित NXM_MACHINE_CHECKS_ON_TSUNAMI
	अचिन्हित दीर्घ पंचांगp;
	
	/* Ho hum.. init_arch is called beक्रमe init_IRQ, but we need to be
	   able to handle machine checks.  So install the handler now.  */
	wrent(entInt, 0);

	/* NXMs just करोn't matter to Tsunami--unless they make it
	   choke completely. */
	पंचांगp = (अचिन्हित दीर्घ)(TSUNAMI_cchip - 1);
	prपूर्णांकk("%s: probing bogus address:  0x%016lx\n", __func__, bogus_addr);
	prपूर्णांकk("\tprobe %s\n",
	       tsunami_probe_ग_लिखो((अचिन्हित दीर्घ *)bogus_addr)
	       ? "succeeded" : "failed");
#पूर्ण_अगर /* NXM_MACHINE_CHECKS_ON_TSUNAMI */

#अगर 0
	prपूर्णांकk("%s: CChip registers:\n", __func__);
	prपूर्णांकk("%s: CSR_CSC 0x%lx\n", __func__, TSUNAMI_cchip->csc.csr);
	prपूर्णांकk("%s: CSR_MTR 0x%lx\n", __func__, TSUNAMI_cchip.mtr.csr);
	prपूर्णांकk("%s: CSR_MISC 0x%lx\n", __func__, TSUNAMI_cchip->misc.csr);
	prपूर्णांकk("%s: CSR_DIM0 0x%lx\n", __func__, TSUNAMI_cchip->dim0.csr);
	prपूर्णांकk("%s: CSR_DIM1 0x%lx\n", __func__, TSUNAMI_cchip->dim1.csr);
	prपूर्णांकk("%s: CSR_DIR0 0x%lx\n", __func__, TSUNAMI_cchip->dir0.csr);
	prपूर्णांकk("%s: CSR_DIR1 0x%lx\n", __func__, TSUNAMI_cchip->dir1.csr);
	prपूर्णांकk("%s: CSR_DRIR 0x%lx\n", __func__, TSUNAMI_cchip->drir.csr);

	prपूर्णांकk("%s: DChip registers:\n");
	prपूर्णांकk("%s: CSR_DSC 0x%lx\n", __func__, TSUNAMI_dchip->dsc.csr);
	prपूर्णांकk("%s: CSR_STR 0x%lx\n", __func__, TSUNAMI_dchip->str.csr);
	prपूर्णांकk("%s: CSR_DREV 0x%lx\n", __func__, TSUNAMI_dchip->drev.csr);
#पूर्ण_अगर
	/* With multiple PCI busses, we play with I/O as physical addrs.  */
	ioport_resource.end = ~0UL;

	/* Find how many hoses we have, and initialize them.  TSUNAMI
	   and TYPHOON can have 2, but might only have 1 (DS10).  */

	tsunami_init_one_pchip(TSUNAMI_pchip0, 0);
	अगर (TSUNAMI_cchip->csc.csr & 1L<<14)
		tsunami_init_one_pchip(TSUNAMI_pchip1, 1);

	/* Check क्रम graphic console location (अगर any).  */
	find_console_vga_hose();
पूर्ण

अटल व्योम
tsunami_समाप्त_one_pchip(tsunami_pchip *pchip, पूर्णांक index)
अणु
	pchip->wsba[0].csr = saved_config[index].wsba[0];
	pchip->wsm[0].csr = saved_config[index].wsm[0];
	pchip->tba[0].csr = saved_config[index].tba[0];

	pchip->wsba[1].csr = saved_config[index].wsba[1];
	pchip->wsm[1].csr = saved_config[index].wsm[1];
	pchip->tba[1].csr = saved_config[index].tba[1];

	pchip->wsba[2].csr = saved_config[index].wsba[2];
	pchip->wsm[2].csr = saved_config[index].wsm[2];
	pchip->tba[2].csr = saved_config[index].tba[2];

	pchip->wsba[3].csr = saved_config[index].wsba[3];
	pchip->wsm[3].csr = saved_config[index].wsm[3];
	pchip->tba[3].csr = saved_config[index].tba[3];
पूर्ण

व्योम
tsunami_समाप्त_arch(पूर्णांक mode)
अणु
	tsunami_समाप्त_one_pchip(TSUNAMI_pchip0, 0);
	अगर (TSUNAMI_cchip->csc.csr & 1L<<14)
		tsunami_समाप्त_one_pchip(TSUNAMI_pchip1, 1);
पूर्ण

अटल अंतरभूत व्योम
tsunami_pci_clr_err_1(tsunami_pchip *pchip)
अणु
	pchip->लिखो_त्रुटि.csr;
	pchip->लिखो_त्रुटि.csr = 0x040;
	mb();
	pchip->लिखो_त्रुटि.csr;
पूर्ण

अटल अंतरभूत व्योम
tsunami_pci_clr_err(व्योम)
अणु
	tsunami_pci_clr_err_1(TSUNAMI_pchip0);

	/* TSUNAMI and TYPHOON can have 2, but might only have 1 (DS10) */
	अगर (TSUNAMI_cchip->csc.csr & 1L<<14)
		tsunami_pci_clr_err_1(TSUNAMI_pchip1);
पूर्ण

व्योम
tsunami_machine_check(अचिन्हित दीर्घ vector, अचिन्हित दीर्घ la_ptr)
अणु
	/* Clear error beक्रमe any reporting.  */
	mb();
	mb();  /* magic */
	draina();
	tsunami_pci_clr_err();
	wrmces(0x7);
	mb();

	process_mcheck_info(vector, la_ptr, "TSUNAMI",
			    mcheck_expected(smp_processor_id()));
पूर्ण
