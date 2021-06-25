<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	linux/arch/alpha/kernel/core_lca.c
 *
 * Written by David Mosberger (davidm@cs.arizona.edu) with some code
 * taken from Dave Rusling's (david.rusling@reo.mts.dec.com) 32-bit
 * bios code.
 *
 * Code common to all LCA core logic chips.
 */

#घोषणा __EXTERN_INLINE अंतरभूत
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/core_lca.h>
#अघोषित __EXTERN_INLINE

#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/tty.h>

#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/irq_regs.h>
#समावेश <यंत्र/smp.h>

#समावेश "proto.h"
#समावेश "pci_impl.h"


/*
 * BIOS32-style PCI पूर्णांकerface:
 */

/*
 * Machine check reasons.  Defined according to PALcode sources
 * (osf.h and platक्रमm.h).
 */
#घोषणा MCHK_K_TPERR		0x0080
#घोषणा MCHK_K_TCPERR		0x0082
#घोषणा MCHK_K_HERR		0x0084
#घोषणा MCHK_K_ECC_C		0x0086
#घोषणा MCHK_K_ECC_NC		0x0088
#घोषणा MCHK_K_UNKNOWN		0x008A
#घोषणा MCHK_K_CACKSOFT		0x008C
#घोषणा MCHK_K_BUGCHECK		0x008E
#घोषणा MCHK_K_OS_BUGCHECK	0x0090
#घोषणा MCHK_K_DCPERR		0x0092
#घोषणा MCHK_K_ICPERR		0x0094


/*
 * Platक्रमm-specअगरic machine-check reasons:
 */
#घोषणा MCHK_K_SIO_SERR		0x204	/* all platक्रमms so far */
#घोषणा MCHK_K_SIO_IOCHK	0x206	/* all platक्रमms so far */
#घोषणा MCHK_K_DCSR		0x208	/* all but Noname */


/*
 * Given a bus, device, and function number, compute resulting
 * configuration space address and setup the LCA_IOC_CONF रेजिस्टर
 * accordingly.  It is thereक्रमe not safe to have concurrent
 * invocations to configuration space access routines, but there
 * really shouldn't be any need क्रम this.
 *
 * Type 0:
 *
 *  3 3|3 3 2 2|2 2 2 2|2 2 2 2|1 1 1 1|1 1 1 1|1 1 
 *  3 2|1 0 9 8|7 6 5 4|3 2 1 0|9 8 7 6|5 4 3 2|1 0 9 8|7 6 5 4|3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * | | | | | | | | | | | | | | | | | | | | | | | |F|F|F|R|R|R|R|R|R|0|0|
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 *	31:11	Device select bit.
 * 	10:8	Function number
 * 	 7:2	Register number
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
	     अचिन्हित दीर्घ *pci_addr)
अणु
	अचिन्हित दीर्घ addr;
	u8 bus = pbus->number;

	अगर (bus == 0) अणु
		पूर्णांक device = device_fn >> 3;
		पूर्णांक func = device_fn & 0x7;

		/* Type 0 configuration cycle.  */

		अगर (device > 12) अणु
			वापस -1;
		पूर्ण

		*(vulp)LCA_IOC_CONF = 0;
		addr = (1 << (11 + device)) | (func << 8) | where;
	पूर्ण अन्यथा अणु
		/* Type 1 configuration cycle.  */
		*(vulp)LCA_IOC_CONF = 1;
		addr = (bus << 16) | (device_fn << 8) | where;
	पूर्ण
	*pci_addr = addr;
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक
conf_पढ़ो(अचिन्हित दीर्घ addr)
अणु
	अचिन्हित दीर्घ flags, code, stat0;
	अचिन्हित पूर्णांक value;

	local_irq_save(flags);

	/* Reset status रेजिस्टर to aव्योम losing errors.  */
	stat0 = *(vulp)LCA_IOC_STAT0;
	*(vulp)LCA_IOC_STAT0 = stat0;
	mb();

	/* Access configuration space.  */
	value = *(vuip)addr;
	draina();

	stat0 = *(vulp)LCA_IOC_STAT0;
	अगर (stat0 & LCA_IOC_STAT0_ERR) अणु
		code = ((stat0 >> LCA_IOC_STAT0_CODE_SHIFT)
			& LCA_IOC_STAT0_CODE_MASK);
		अगर (code != 1) अणु
			prपूर्णांकk("lca.c:conf_read: got stat0=%lx\n", stat0);
		पूर्ण

		/* Reset error status.  */
		*(vulp)LCA_IOC_STAT0 = stat0;
		mb();

		/* Reset machine check.  */
		wrmces(0x7);

		value = 0xffffffff;
	पूर्ण
	local_irq_restore(flags);
	वापस value;
पूर्ण

अटल व्योम
conf_ग_लिखो(अचिन्हित दीर्घ addr, अचिन्हित पूर्णांक value)
अणु
	अचिन्हित दीर्घ flags, code, stat0;

	local_irq_save(flags);	/* aव्योम getting hit by machine check */

	/* Reset status रेजिस्टर to aव्योम losing errors.  */
	stat0 = *(vulp)LCA_IOC_STAT0;
	*(vulp)LCA_IOC_STAT0 = stat0;
	mb();

	/* Access configuration space.  */
	*(vuip)addr = value;
	draina();

	stat0 = *(vulp)LCA_IOC_STAT0;
	अगर (stat0 & LCA_IOC_STAT0_ERR) अणु
		code = ((stat0 >> LCA_IOC_STAT0_CODE_SHIFT)
			& LCA_IOC_STAT0_CODE_MASK);
		अगर (code != 1) अणु
			prपूर्णांकk("lca.c:conf_write: got stat0=%lx\n", stat0);
		पूर्ण

		/* Reset error status.  */
		*(vulp)LCA_IOC_STAT0 = stat0;
		mb();

		/* Reset machine check. */
		wrmces(0x7);
	पूर्ण
	local_irq_restore(flags);
पूर्ण

अटल पूर्णांक
lca_पढ़ो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक where,
		पूर्णांक size, u32 *value)
अणु
	अचिन्हित दीर्घ addr, pci_addr;
	दीर्घ mask;
	पूर्णांक shअगरt;

	अगर (mk_conf_addr(bus, devfn, where, &pci_addr))
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	shअगरt = (where & 3) * 8;
	mask = (size - 1) * 8;
	addr = (pci_addr << 5) + mask + LCA_CONF;
	*value = conf_पढ़ो(addr) >> (shअगरt);
	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक 
lca_ग_लिखो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक where, पूर्णांक size,
		 u32 value)
अणु
	अचिन्हित दीर्घ addr, pci_addr;
	दीर्घ mask;

	अगर (mk_conf_addr(bus, devfn, where, &pci_addr))
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	mask = (size - 1) * 8;
	addr = (pci_addr << 5) + mask + LCA_CONF;
	conf_ग_लिखो(addr, value << ((where & 3) * 8));
	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

काष्ठा pci_ops lca_pci_ops = 
अणु
	.पढ़ो =		lca_पढ़ो_config,
	.ग_लिखो =	lca_ग_लिखो_config,
पूर्ण;

व्योम
lca_pci_tbi(काष्ठा pci_controller *hose, dma_addr_t start, dma_addr_t end)
अणु
	wmb();
	*(vulp)LCA_IOC_TBIA = 0;
	mb();
पूर्ण

व्योम __init
lca_init_arch(व्योम)
अणु
	काष्ठा pci_controller *hose;

	/*
	 * Create our single hose.
	 */

	pci_isa_hose = hose = alloc_pci_controller();
	hose->io_space = &ioport_resource;
	hose->mem_space = &iomem_resource;
	hose->index = 0;

	hose->sparse_mem_base = LCA_SPARSE_MEM - IDENT_ADDR;
	hose->dense_mem_base = LCA_DENSE_MEM - IDENT_ADDR;
	hose->sparse_io_base = LCA_IO - IDENT_ADDR;
	hose->dense_io_base = 0;

	/*
	 * Set up the PCI to मुख्य memory translation winकरोws.
	 *
	 * Mimic the SRM settings क्रम the direct-map winकरोw.
	 *   Winकरोw 0 is scatter-gather 8MB at 8MB (क्रम isa).
	 *   Winकरोw 1 is direct access 1GB at 1GB.
	 *
	 * Note that we करो not try to save any of the DMA winकरोw CSRs
	 * beक्रमe setting them, since we cannot पढ़ो those CSRs on LCA.
	 */
	hose->sg_isa = iommu_arena_new(hose, 0x00800000, 0x00800000,
				       SMP_CACHE_BYTES);
	hose->sg_pci = शून्य;
	__direct_map_base = 0x40000000;
	__direct_map_size = 0x40000000;

	*(vulp)LCA_IOC_W_BASE0 = hose->sg_isa->dma_base | (3UL << 32);
	*(vulp)LCA_IOC_W_MASK0 = (hose->sg_isa->size - 1) & 0xfff00000;
	*(vulp)LCA_IOC_T_BASE0 = virt_to_phys(hose->sg_isa->ptes);

	*(vulp)LCA_IOC_W_BASE1 = __direct_map_base | (2UL << 32);
	*(vulp)LCA_IOC_W_MASK1 = (__direct_map_size - 1) & 0xfff00000;
	*(vulp)LCA_IOC_T_BASE1 = 0;

	*(vulp)LCA_IOC_TB_ENA = 0x80;

	lca_pci_tbi(hose, 0, -1);

	/*
	 * Disable PCI parity क्रम now.  The NCR53c810 chip has
	 * troubles meeting the PCI spec which results in
	 * data parity errors.
	 */
	*(vulp)LCA_IOC_PAR_DIS = 1UL<<5;

	/*
	 * Finally, set up क्रम restoring the correct HAE अगर using SRM.
	 * Again, since we cannot पढ़ो many of the CSRs on the LCA,
	 * one of which happens to be the HAE, we save the value that
	 * the SRM will expect...
	 */
	अगर (alpha_using_srm)
		srm_hae = 0x80000000UL;
पूर्ण

/*
 * Constants used during machine-check handling.  I suppose these
 * could be moved पूर्णांकo lca.h but I करोn't see much reason why anybody
 * अन्यथा would want to use them.
 */

#घोषणा ESR_EAV		(1UL<< 0)	/* error address valid */
#घोषणा ESR_CEE		(1UL<< 1)	/* correctable error */
#घोषणा ESR_UEE		(1UL<< 2)	/* uncorrectable error */
#घोषणा ESR_WRE		(1UL<< 3)	/* ग_लिखो-error */
#घोषणा ESR_SOR		(1UL<< 4)	/* error source */
#घोषणा ESR_CTE		(1UL<< 7)	/* cache-tag error */
#घोषणा ESR_MSE		(1UL<< 9)	/* multiple soft errors */
#घोषणा ESR_MHE		(1UL<<10)	/* multiple hard errors */
#घोषणा ESR_NXM		(1UL<<12)	/* non-existent memory */

#घोषणा IOC_ERR		(  1<<4)	/* ioc logs an error */
#घोषणा IOC_CMD_SHIFT	0
#घोषणा IOC_CMD		(0xf<<IOC_CMD_SHIFT)
#घोषणा IOC_CODE_SHIFT	8
#घोषणा IOC_CODE	(0xf<<IOC_CODE_SHIFT)
#घोषणा IOC_LOST	(  1<<5)
#घोषणा IOC_P_NBR	((__u32) ~((1<<13) - 1))

अटल व्योम
mem_error(अचिन्हित दीर्घ esr, अचिन्हित दीर्घ ear)
अणु
	prपूर्णांकk("    %s %s error to %s occurred at address %x\n",
	       ((esr & ESR_CEE) ? "Correctable" :
		(esr & ESR_UEE) ? "Uncorrectable" : "A"),
	       (esr & ESR_WRE) ? "write" : "read",
	       (esr & ESR_SOR) ? "memory" : "b-cache",
	       (अचिन्हित) (ear & 0x1ffffff8));
	अगर (esr & ESR_CTE) अणु
		prपूर्णांकk("    A b-cache tag parity error was detected.\n");
	पूर्ण
	अगर (esr & ESR_MSE) अणु
		prपूर्णांकk("    Several other correctable errors occurred.\n");
	पूर्ण
	अगर (esr & ESR_MHE) अणु
		prपूर्णांकk("    Several other uncorrectable errors occurred.\n");
	पूर्ण
	अगर (esr & ESR_NXM) अणु
		prपूर्णांकk("    Attempted to access non-existent memory.\n");
	पूर्ण
पूर्ण

अटल व्योम
ioc_error(__u32 stat0, __u32 stat1)
अणु
	अटल स्थिर अक्षर * स्थिर pci_cmd[] = अणु
		"Interrupt Acknowledge", "Special", "I/O Read", "I/O Write",
		"Rsvd 1", "Rsvd 2", "Memory Read", "Memory Write", "Rsvd3",
		"Rsvd4", "Configuration Read", "Configuration Write",
		"Memory Read Multiple", "Dual Address", "Memory Read Line",
		"Memory Write and Invalidate"
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर err_name[] = अणु
		"exceeded retry limit", "no device", "bad data parity",
		"target abort", "bad address parity", "page table read error",
		"invalid page", "data error"
	पूर्ण;
	अचिन्हित code = (stat0 & IOC_CODE) >> IOC_CODE_SHIFT;
	अचिन्हित cmd  = (stat0 & IOC_CMD)  >> IOC_CMD_SHIFT;

	prपूर्णांकk("    %s initiated PCI %s cycle to address %x"
	       " failed due to %s.\n",
	       code > 3 ? "PCI" : "CPU", pci_cmd[cmd], stat1, err_name[code]);

	अगर (code == 5 || code == 6) अणु
		prपूर्णांकk("    (Error occurred at PCI memory address %x.)\n",
		       (stat0 & ~IOC_P_NBR));
	पूर्ण
	अगर (stat0 & IOC_LOST) अणु
		prपूर्णांकk("    Other PCI errors occurred simultaneously.\n");
	पूर्ण
पूर्ण

व्योम
lca_machine_check(अचिन्हित दीर्घ vector, अचिन्हित दीर्घ la_ptr)
अणु
	स्थिर अक्षर * reason;
	जोड़ el_lca el;

	el.c = (काष्ठा el_common *) la_ptr;

	wrmces(rdmces());	/* reset machine check pending flag */

	prपूर्णांकk(KERN_CRIT "LCA machine check: vector=%#lx pc=%#lx code=%#x\n",
	       vector, get_irq_regs()->pc, (अचिन्हित पूर्णांक) el.c->code);

	/*
	 * The first quadword after the common header always seems to
	 * be the machine check reason---करोn't know why this isn't
	 * part of the common header instead.  In the हाल of a दीर्घ
	 * logout frame, the upper 32 bits is the machine check
	 * revision level, which we ignore क्रम now.
	 */
	चयन ((अचिन्हित पूर्णांक) el.c->code) अणु
	हाल MCHK_K_TPERR:	reason = "tag parity error"; अवरोध;
	हाल MCHK_K_TCPERR:	reason = "tag control parity error"; अवरोध;
	हाल MCHK_K_HERR:	reason = "access to non-existent memory"; अवरोध;
	हाल MCHK_K_ECC_C:	reason = "correctable ECC error"; अवरोध;
	हाल MCHK_K_ECC_NC:	reason = "non-correctable ECC error"; अवरोध;
	हाल MCHK_K_CACKSOFT:	reason = "MCHK_K_CACKSOFT"; अवरोध;
	हाल MCHK_K_BUGCHECK:	reason = "illegal exception in PAL mode"; अवरोध;
	हाल MCHK_K_OS_BUGCHECK: reason = "callsys in kernel mode"; अवरोध;
	हाल MCHK_K_DCPERR:	reason = "d-cache parity error"; अवरोध;
	हाल MCHK_K_ICPERR:	reason = "i-cache parity error"; अवरोध;
	हाल MCHK_K_SIO_SERR:	reason = "SIO SERR occurred on PCI bus"; अवरोध;
	हाल MCHK_K_SIO_IOCHK:	reason = "SIO IOCHK occurred on ISA bus"; अवरोध;
	हाल MCHK_K_DCSR:	reason = "MCHK_K_DCSR"; अवरोध;
	हाल MCHK_K_UNKNOWN:
	शेष:		reason = "unknown"; अवरोध;
	पूर्ण

	चयन (el.c->size) अणु
	हाल माप(काष्ठा el_lca_mcheck_लघु):
		prपूर्णांकk(KERN_CRIT
		       "  Reason: %s (short frame%s, dc_stat=%#lx):\n",
		       reason, el.c->retry ? ", retryable" : "",
		       el.s->dc_stat);
		अगर (el.s->esr & ESR_EAV) अणु
			mem_error(el.s->esr, el.s->ear);
		पूर्ण
		अगर (el.s->ioc_stat0 & IOC_ERR) अणु
			ioc_error(el.s->ioc_stat0, el.s->ioc_stat1);
		पूर्ण
		अवरोध;

	हाल माप(काष्ठा el_lca_mcheck_दीर्घ):
		prपूर्णांकk(KERN_CRIT "  Reason: %s (long frame%s):\n",
		       reason, el.c->retry ? ", retryable" : "");
		prपूर्णांकk(KERN_CRIT
		       "    reason: %#lx  exc_addr: %#lx  dc_stat: %#lx\n", 
		       el.l->pt[0], el.l->exc_addr, el.l->dc_stat);
		prपूर्णांकk(KERN_CRIT "    car: %#lx\n", el.l->car);
		अगर (el.l->esr & ESR_EAV) अणु
			mem_error(el.l->esr, el.l->ear);
		पूर्ण
		अगर (el.l->ioc_stat0 & IOC_ERR) अणु
			ioc_error(el.l->ioc_stat0, el.l->ioc_stat1);
		पूर्ण
		अवरोध;

	शेष:
		prपूर्णांकk(KERN_CRIT "  Unknown errorlog size %d\n", el.c->size);
	पूर्ण

	/* Dump the logout area to give all info.  */
#अगर_घोषित CONFIG_VERBOSE_MCHECK
	अगर (alpha_verbose_mcheck > 1) अणु
		अचिन्हित दीर्घ * ptr = (अचिन्हित दीर्घ *) la_ptr;
		दीर्घ i;
		क्रम (i = 0; i < el.c->size / माप(दीर्घ); i += 2) अणु
			prपूर्णांकk(KERN_CRIT " +%8lx %016lx %016lx\n",
			       i*माप(दीर्घ), ptr[i], ptr[i+1]);
		पूर्ण
	पूर्ण
#पूर्ण_अगर /* CONFIG_VERBOSE_MCHECK */
पूर्ण

/*
 * The following routines are needed to support the SPEED changing
 * necessary to successfully manage the thermal problem on the AlphaBook1.
 */

व्योम
lca_घड़ी_prपूर्णांक(व्योम)
अणु
        दीर्घ    pmr_reg;

        pmr_reg = LCA_READ_PMR;

        prपूर्णांकk("Status of clock control:\n");
        prपूर्णांकk("\tPrimary clock divisor\t0x%lx\n", LCA_GET_PRIMARY(pmr_reg));
        prपूर्णांकk("\tOverride clock divisor\t0x%lx\n", LCA_GET_OVERRIDE(pmr_reg));
        prपूर्णांकk("\tInterrupt override is %s\n",
	       (pmr_reg & LCA_PMR_INTO) ? "on" : "off"); 
        prपूर्णांकk("\tDMA override is %s\n",
	       (pmr_reg & LCA_PMR_DMAO) ? "on" : "off"); 

पूर्ण

पूर्णांक
lca_get_घड़ी(व्योम)
अणु
        दीर्घ    pmr_reg;

        pmr_reg = LCA_READ_PMR;
        वापस(LCA_GET_PRIMARY(pmr_reg));

पूर्ण

व्योम
lca_घड़ी_fiddle(पूर्णांक भागisor)
अणु
        दीर्घ    pmr_reg;

        pmr_reg = LCA_READ_PMR;
        LCA_SET_PRIMARY_CLOCK(pmr_reg, भागisor);
	/* lca_norm_घड़ी = भागisor; */
        LCA_WRITE_PMR(pmr_reg);
        mb();
पूर्ण
