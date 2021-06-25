<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	linux/arch/alpha/kernel/core_marvel.c
 *
 * Code common to all Marvel based प्रणालीs.
 */

#घोषणा __EXTERN_INLINE अंतरभूत
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/core_marvel.h>
#अघोषित __EXTERN_INLINE

#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/sched.h>
#समावेश <linux/init.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/mc146818rtc.h>
#समावेश <linux/rtc.h>
#समावेश <linux/module.h>
#समावेश <linux/memblock.h>

#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/gct.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/vga.h>

#समावेश "proto.h"
#समावेश "pci_impl.h"


/*
 * Debug helpers
 */
#घोषणा DEBUG_CONFIG 0

#अगर DEBUG_CONFIG
# define DBG_CFG(args) prपूर्णांकk args
#अन्यथा
# define DBG_CFG(args)
#पूर्ण_अगर


/*
 * Private data
 */
अटल काष्ठा io7 *io7_head = शून्य;


/*
 * Helper functions
 */
अटल अचिन्हित दीर्घ __attribute__ ((unused))
पढ़ो_ev7_csr(पूर्णांक pe, अचिन्हित दीर्घ offset)
अणु
	ev7_csr *ev7csr = EV7_CSR_KERN(pe, offset);
	अचिन्हित दीर्घ q;

	mb();
	q = ev7csr->csr;
	mb();

	वापस q;
पूर्ण

अटल व्योम __attribute__ ((unused))
ग_लिखो_ev7_csr(पूर्णांक pe, अचिन्हित दीर्घ offset, अचिन्हित दीर्घ q)
अणु
	ev7_csr *ev7csr = EV7_CSR_KERN(pe, offset);

	mb();
	ev7csr->csr = q;
	mb();
पूर्ण

अटल अक्षर * __init
mk_resource_name(पूर्णांक pe, पूर्णांक port, अक्षर *str)
अणु
	अक्षर पंचांगp[80];
	अक्षर *name;
	
	प्र_लिखो(पंचांगp, "PCI %s PE %d PORT %d", str, pe, port);
	name = memblock_alloc(म_माप(पंचांगp) + 1, SMP_CACHE_BYTES);
	अगर (!name)
		panic("%s: Failed to allocate %zu bytes\n", __func__,
		      म_माप(पंचांगp) + 1);
	म_नकल(name, पंचांगp);

	वापस name;
पूर्ण

अंतरभूत काष्ठा io7 *
marvel_next_io7(काष्ठा io7 *prev)
अणु
	वापस (prev ? prev->next : io7_head);
पूर्ण

काष्ठा io7 *
marvel_find_io7(पूर्णांक pe)
अणु
	काष्ठा io7 *io7;

	क्रम (io7 = io7_head; io7 && io7->pe != pe; io7 = io7->next)
		जारी;

	वापस io7;
पूर्ण

अटल काष्ठा io7 * __init
alloc_io7(अचिन्हित पूर्णांक pe)
अणु
	काष्ठा io7 *io7;
	काष्ठा io7 *insp;
	पूर्णांक h;

	अगर (marvel_find_io7(pe)) अणु
		prपूर्णांकk(KERN_WARNING "IO7 at PE %d already allocated!\n", pe);
		वापस शून्य;
	पूर्ण

	io7 = memblock_alloc(माप(*io7), SMP_CACHE_BYTES);
	अगर (!io7)
		panic("%s: Failed to allocate %zu bytes\n", __func__,
		      माप(*io7));
	io7->pe = pe;
	raw_spin_lock_init(&io7->irq_lock);

	क्रम (h = 0; h < 4; h++) अणु
		io7->ports[h].io7 = io7;
		io7->ports[h].port = h;
		io7->ports[h].enabled = 0; /* शेष to disabled */
	पूर्ण

	/*
	 * Insert in pe sorted order.
	 */
	अगर (शून्य == io7_head)			/* empty list */
		io7_head = io7;	
	अन्यथा अगर (io7_head->pe > io7->pe) अणु	/* insert at head */
		io7->next = io7_head;
		io7_head = io7;
	पूर्ण अन्यथा अणु				/* insert at position */
		क्रम (insp = io7_head; insp; insp = insp->next) अणु
			अगर (insp->pe == io7->pe) अणु
				prपूर्णांकk(KERN_ERR "Too many IO7s at PE %d\n", 
				       io7->pe);
				वापस शून्य;
			पूर्ण

			अगर (शून्य == insp->next || 
			    insp->next->pe > io7->pe) अणु /* insert here */
				io7->next = insp->next;
				insp->next = io7;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (शून्य == insp) अणु /* couldn't insert ?!? */
			prपूर्णांकk(KERN_WARNING "Failed to insert IO7 at PE %d "
			       " - adding at head of list\n", io7->pe);
			io7->next = io7_head;
			io7_head = io7;
		पूर्ण
	पूर्ण
	
	वापस io7;
पूर्ण

व्योम
io7_clear_errors(काष्ठा io7 *io7)
अणु
	io7_port7_csrs *p7csrs;
	io7_ioport_csrs *csrs;
	पूर्णांक port;


	/*
	 * First the IO ports.
	 */
	क्रम (port = 0; port < 4; port++) अणु
		csrs = IO7_CSRS_KERN(io7->pe, port);

		csrs->POx_ERR_SUM.csr = -1UL;
		csrs->POx_TLB_ERR.csr = -1UL;
		csrs->POx_SPL_COMPLT.csr = -1UL;
		csrs->POx_TRANS_SUM.csr = -1UL;
	पूर्ण

	/*
	 * Then the common ones.
	 */
	p7csrs = IO7_PORT7_CSRS_KERN(io7->pe);

	p7csrs->PO7_ERROR_SUM.csr = -1UL;
	p7csrs->PO7_UNCRR_SYM.csr = -1UL;
	p7csrs->PO7_CRRCT_SYM.csr = -1UL;
पूर्ण


/*
 * IO7 PCI, PCI/X, AGP configuration.
 */
अटल व्योम __init
io7_init_hose(काष्ठा io7 *io7, पूर्णांक port)
अणु
	अटल पूर्णांक hose_index = 0;

	काष्ठा pci_controller *hose = alloc_pci_controller();
	काष्ठा io7_port *io7_port = &io7->ports[port];
	io7_ioport_csrs *csrs = IO7_CSRS_KERN(io7->pe, port);
	पूर्णांक i;

	hose->index = hose_index++;	/* arbitrary */
	
	/*
	 * We करोn't have an isa or legacy hose, but glibc expects to be
	 * able to use the bus == 0 / dev == 0 क्रमm of the iobase syscall
	 * to determine inक्रमmation about the i/o प्रणाली. Since XFree86 
	 * relies on glibc's determination to tell whether or not to use
	 * sparse access, we need to poपूर्णांक the pci_isa_hose at a real hose
	 * so at least that determination is correct.
	 */
	अगर (hose->index == 0)
		pci_isa_hose = hose;

	io7_port->csrs = csrs;
	io7_port->hose = hose;
	hose->sysdata = io7_port;

	hose->io_space = alloc_resource();
	hose->mem_space = alloc_resource();

	/*
	 * Base addresses क्रम userland consumption. Since these are going
	 * to be mapped, they are pure physical addresses.
	 */
	hose->sparse_mem_base = hose->sparse_io_base = 0;
	hose->dense_mem_base = IO7_MEM_PHYS(io7->pe, port);
	hose->dense_io_base = IO7_IO_PHYS(io7->pe, port);

	/*
	 * Base addresses and resource ranges क्रम kernel consumption.
	 */
	hose->config_space_base = (अचिन्हित दीर्घ)IO7_CONF_KERN(io7->pe, port);

	hose->io_space->start = (अचिन्हित दीर्घ)IO7_IO_KERN(io7->pe, port);
	hose->io_space->end = hose->io_space->start + IO7_IO_SPACE - 1;
	hose->io_space->name = mk_resource_name(io7->pe, port, "IO");
	hose->io_space->flags = IORESOURCE_IO;

	hose->mem_space->start = (अचिन्हित दीर्घ)IO7_MEM_KERN(io7->pe, port);
	hose->mem_space->end = hose->mem_space->start + IO7_MEM_SPACE - 1;
	hose->mem_space->name = mk_resource_name(io7->pe, port, "MEM");
	hose->mem_space->flags = IORESOURCE_MEM;

	अगर (request_resource(&ioport_resource, hose->io_space) < 0)
		prपूर्णांकk(KERN_ERR "Failed to request IO on hose %d\n", 
		       hose->index);
	अगर (request_resource(&iomem_resource, hose->mem_space) < 0)
		prपूर्णांकk(KERN_ERR "Failed to request MEM on hose %d\n", 
		       hose->index);

	/*
	 * Save the existing DMA winकरोw settings क्रम later restoration.
	 */
	क्रम (i = 0; i < 4; i++) अणु
		io7_port->saved_wbase[i] = csrs->POx_WBASE[i].csr;
		io7_port->saved_wmask[i] = csrs->POx_WMASK[i].csr;
		io7_port->saved_tbase[i] = csrs->POx_TBASE[i].csr;
	पूर्ण

	/*
	 * Set up the PCI to मुख्य memory translation winकरोws.
	 *
	 * Winकरोw 0 is scatter-gather 8MB at 8MB
	 * Winकरोw 1 is direct access 1GB at 2GB
	 * Winकरोw 2 is scatter-gather (up-to) 1GB at 3GB
	 * Winकरोw 3 is disabled
	 */

	/*
	 * TBIA beक्रमe modअगरying winकरोws.
	 */
	marvel_pci_tbi(hose, 0, -1);

	/*
	 * Set up winकरोw 0 क्रम scatter-gather 8MB at 8MB.
	 */
	hose->sg_isa = iommu_arena_new_node(marvel_cpuid_to_nid(io7->pe),
					    hose, 0x00800000, 0x00800000, 0);
	hose->sg_isa->align_entry = 8;	/* cache line boundary */
	csrs->POx_WBASE[0].csr = 
		hose->sg_isa->dma_base | wbase_m_ena | wbase_m_sg;
	csrs->POx_WMASK[0].csr = (hose->sg_isa->size - 1) & wbase_m_addr;
	csrs->POx_TBASE[0].csr = virt_to_phys(hose->sg_isa->ptes);

	/*
	 * Set up winकरोw 1 क्रम direct-mapped 1GB at 2GB.
	 */
	csrs->POx_WBASE[1].csr = __direct_map_base | wbase_m_ena;
	csrs->POx_WMASK[1].csr = (__direct_map_size - 1) & wbase_m_addr;
	csrs->POx_TBASE[1].csr = 0;

	/*
	 * Set up winकरोw 2 क्रम scatter-gather (up-to) 1GB at 3GB.
	 */
	hose->sg_pci = iommu_arena_new_node(marvel_cpuid_to_nid(io7->pe),
					    hose, 0xc0000000, 0x40000000, 0);
	hose->sg_pci->align_entry = 8;	/* cache line boundary */
	csrs->POx_WBASE[2].csr = 
		hose->sg_pci->dma_base | wbase_m_ena | wbase_m_sg;
	csrs->POx_WMASK[2].csr = (hose->sg_pci->size - 1) & wbase_m_addr;
	csrs->POx_TBASE[2].csr = virt_to_phys(hose->sg_pci->ptes);

	/*
	 * Disable winकरोw 3.
	 */
	csrs->POx_WBASE[3].csr = 0;

	/*
	 * Make sure that the AGP Monster Winकरोw is disabled.
	 */
	csrs->POx_CTRL.csr &= ~(1UL << 61);

#अगर 1
	prपूर्णांकk("FIXME: disabling master aborts\n");
	csrs->POx_MSK_HEI.csr &= ~(3UL << 14);
#पूर्ण_अगर
	/*
	 * TBIA after modअगरying winकरोws.
	 */
	marvel_pci_tbi(hose, 0, -1);
पूर्ण

अटल व्योम __init
marvel_init_io7(काष्ठा io7 *io7)
अणु
	पूर्णांक i;

	prपूर्णांकk("Initializing IO7 at PID %d\n", io7->pe);

	/*
	 * Get the Port 7 CSR poपूर्णांकer.
	 */
	io7->csrs = IO7_PORT7_CSRS_KERN(io7->pe);

	/*
	 * Init this IO7's hoses.
	 */
	क्रम (i = 0; i < IO7_NUM_PORTS; i++) अणु
		io7_ioport_csrs *csrs = IO7_CSRS_KERN(io7->pe, i);
		अगर (csrs->POx_CACHE_CTL.csr == 8) अणु
			io7->ports[i].enabled = 1;
			io7_init_hose(io7, i);
		पूर्ण
	पूर्ण
पूर्ण

व्योम __init
marvel_io7_present(gct6_node *node)
अणु
	पूर्णांक pe;

	अगर (node->type != GCT_TYPE_HOSE ||
	    node->subtype != GCT_SUBTYPE_IO_PORT_MODULE) 
		वापस;

	pe = (node->id >> 8) & 0xff;
	prपूर्णांकk("Found an IO7 at PID %d\n", pe);

	alloc_io7(pe);
पूर्ण

अटल व्योम __init
marvel_find_console_vga_hose(व्योम)
अणु
#अगर_घोषित CONFIG_VGA_HOSE
	u64 *pu64 = (u64 *)((u64)hwrpb + hwrpb->ctbt_offset);

	अगर (pu64[7] == 3) अणु	/* TERM_TYPE == graphics */
		काष्ठा pci_controller *hose = शून्य;
		पूर्णांक h = (pu64[30] >> 24) & 0xff; /* TERM_OUT_LOC, hose # */
		काष्ठा io7 *io7;
		पूर्णांक pid, port;

		/* FIXME - encoding is going to have to change क्रम Marvel
		 *         since hose will be able to overflow a byte...
		 *         need to fix this decode when the console 
		 *         changes its encoding
		 */
		prपूर्णांकk("console graphics is on hose %d (console)\n", h);

		/*
		 * The console's hose numbering is:
		 *
		 *	hose<n:2>: PID
		 *	hose<1:0>: PORT
		 *
		 * We need to find the hose at that pid and port
		 */
		pid = h >> 2;
		port = h & 3;
		अगर ((io7 = marvel_find_io7(pid)))
			hose = io7->ports[port].hose;

		अगर (hose) अणु
			prपूर्णांकk("Console graphics on hose %d\n", hose->index);
			pci_vga_hose = hose;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
पूर्ण

gct6_search_काष्ठा gct_wanted_node_list[] __initdata = अणु
	अणु GCT_TYPE_HOSE, GCT_SUBTYPE_IO_PORT_MODULE, marvel_io7_present पूर्ण,
	अणु 0, 0, शून्य पूर्ण
पूर्ण;

/*
 * In हाल the GCT is not complete, let the user specअगरy PIDs with IO7s
 * at boot समय. Syntax is 'io7=a,b,c,...,n' where a-n are the PIDs (decimal)
 * where IO7s are connected
 */
अटल पूर्णांक __init
marvel_specअगरy_io7(अक्षर *str)
अणु
	अचिन्हित दीर्घ pid;
	काष्ठा io7 *io7;
	अक्षर *pअक्षर;

	करो अणु
		pid = simple_म_से_अदीर्घ(str, &pअक्षर, 0);
		अगर (pअक्षर != str) अणु
			prपूर्णांकk("User-specified IO7 at PID %lu\n", pid);
			io7 = alloc_io7(pid);
			अगर (io7) marvel_init_io7(io7);
		पूर्ण

		अगर (pअक्षर == str) pअक्षर++;
		str = pअक्षर;
	पूर्ण जबतक(*str);

	वापस 1;
पूर्ण
__setup("io7=", marvel_specअगरy_io7);

व्योम __init
marvel_init_arch(व्योम)
अणु
	काष्ठा io7 *io7;

	/* With multiple PCI busses, we play with I/O as physical addrs.  */
	ioport_resource.end = ~0UL;

	/* PCI DMA Direct Mapping is 1GB at 2GB.  */
	__direct_map_base = 0x80000000;
	__direct_map_size = 0x40000000;

	/* Parse the config tree.  */
	gct6_find_nodes(GCT_NODE_PTR(0), gct_wanted_node_list);

	/* Init the io7s.  */
	क्रम (io7 = शून्य; शून्य != (io7 = marvel_next_io7(io7)); ) 
		marvel_init_io7(io7);

	/* Check क्रम graphic console location (अगर any).  */
	marvel_find_console_vga_hose();
पूर्ण

व्योम
marvel_समाप्त_arch(पूर्णांक mode)
अणु
पूर्ण


/*
 * PCI Configuration Space access functions
 *
 * Configuration space addresses have the following क्रमmat:
 *
 * 	|2 2 2 2|1 1 1 1|1 1 1 1|1 1 
 * 	|3 2 1 0|9 8 7 6|5 4 3 2|1 0 9 8|7 6 5 4|3 2 1 0
 * 	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * 	|B|B|B|B|B|B|B|B|D|D|D|D|D|F|F|F|R|R|R|R|R|R|R|R|
 * 	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 *	 n:24	reserved क्रम hose base
 *	23:16	bus number (8 bits = 128 possible buses)
 *	15:11	Device number (5 bits)
 *	10:8	function number
 *	 7:2	रेजिस्टर number
 *  
 * Notes:
 *	IO7 determines whether to use a type 0 or type 1 config cycle
 *	based on the bus number. Thereक्रमe the bus number must be set 
 *	to 0 क्रम the root bus on any hose.
 *	
 *	The function number selects which function of a multi-function device 
 *	(e.g., SCSI and Ethernet).
 * 
 */

अटल अंतरभूत अचिन्हित दीर्घ
build_conf_addr(काष्ठा pci_controller *hose, u8 bus, 
		अचिन्हित पूर्णांक devfn, पूर्णांक where)
अणु
	वापस (hose->config_space_base | (bus << 16) | (devfn << 8) | where);
पूर्ण

अटल अचिन्हित दीर्घ
mk_conf_addr(काष्ठा pci_bus *pbus, अचिन्हित पूर्णांक devfn, पूर्णांक where)
अणु
	काष्ठा pci_controller *hose = pbus->sysdata;
	काष्ठा io7_port *io7_port;
	अचिन्हित दीर्घ addr = 0;
	u8 bus = pbus->number;

	अगर (!hose)
		वापस addr;

	/* Check क्रम enabled.  */
	io7_port = hose->sysdata;
	अगर (!io7_port->enabled)
		वापस addr;

	अगर (!pbus->parent) अणु /* No parent means peer PCI bus. */
		/* Don't support idsel > 20 on primary bus.  */
		अगर (devfn >= PCI_DEVFN(21, 0))
			वापस addr;
		bus = 0;
	पूर्ण

	addr = build_conf_addr(hose, bus, devfn, where);

	DBG_CFG(("mk_conf_addr: returning pci_addr 0x%lx\n", addr));
	वापस addr;
पूर्ण

अटल पूर्णांक
marvel_पढ़ो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक where,
		   पूर्णांक size, u32 *value)
अणु
	अचिन्हित दीर्घ addr;
	
	अगर (0 == (addr = mk_conf_addr(bus, devfn, where)))
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	चयन(size) अणु
	हाल 1:	
		*value = __kernel_ldbu(*(vucp)addr);
		अवरोध;
	हाल 2:	
		*value = __kernel_ldwu(*(vusp)addr);
		अवरोध;
	हाल 4:	
		*value = *(vuip)addr;
		अवरोध;
	शेष:
		वापस PCIBIOS_FUNC_NOT_SUPPORTED;
	पूर्ण

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक
marvel_ग_लिखो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक where,
		    पूर्णांक size, u32 value)
अणु
	अचिन्हित दीर्घ addr;
	
	अगर (0 == (addr = mk_conf_addr(bus, devfn, where)))
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
	शेष:
		वापस PCIBIOS_FUNC_NOT_SUPPORTED;
	पूर्ण

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

काष्ठा pci_ops marvel_pci_ops =
अणु
	.पढ़ो =		marvel_पढ़ो_config,
	.ग_लिखो = 	marvel_ग_लिखो_config,
पूर्ण;


/*
 * Other PCI helper functions.
 */
व्योम
marvel_pci_tbi(काष्ठा pci_controller *hose, dma_addr_t start, dma_addr_t end)
अणु
	io7_ioport_csrs *csrs = ((काष्ठा io7_port *)hose->sysdata)->csrs;

	wmb();
	csrs->POx_SG_TBIA.csr = 0;
	mb();
	csrs->POx_SG_TBIA.csr;
पूर्ण



/*
 * RTC Support
 */
काष्ठा marvel_rtc_access_info अणु
	अचिन्हित दीर्घ function;
	अचिन्हित दीर्घ index;
	अचिन्हित दीर्घ data;
पूर्ण;

अटल व्योम
__marvel_access_rtc(व्योम *info)
अणु
	काष्ठा marvel_rtc_access_info *rtc_access = info;

	रेजिस्टर अचिन्हित दीर्घ __r0 __यंत्र__("$0");
	रेजिस्टर अचिन्हित दीर्घ __r16 __यंत्र__("$16") = rtc_access->function;
	रेजिस्टर अचिन्हित दीर्घ __r17 __यंत्र__("$17") = rtc_access->index;
	रेजिस्टर अचिन्हित दीर्घ __r18 __यंत्र__("$18") = rtc_access->data;
	
	__यंत्र__ __अस्थिर__(
		"call_pal %4 # cserve rtc"
		: "=r"(__r16), "=r"(__r17), "=r"(__r18), "=r"(__r0)
		: "i"(PAL_cserve), "0"(__r16), "1"(__r17), "2"(__r18)
		: "$1", "$22", "$23", "$24", "$25");

	rtc_access->data = __r0;
पूर्ण

अटल u8
__marvel_rtc_io(u8 b, अचिन्हित दीर्घ addr, पूर्णांक ग_लिखो)
अणु
	अटल u8 index = 0;

	काष्ठा marvel_rtc_access_info rtc_access;
	u8 ret = 0;

	चयन(addr) अणु
	हाल 0x70:					/* RTC_PORT(0) */
		अगर (ग_लिखो) index = b;
		ret = index;
		अवरोध;

	हाल 0x71:					/* RTC_PORT(1) */
		rtc_access.index = index;
		rtc_access.data = bcd2bin(b);
		rtc_access.function = 0x48 + !ग_लिखो;	/* GET/PUT_TOY */

		__marvel_access_rtc(&rtc_access);

		ret = bin2bcd(rtc_access.data);
		अवरोध;

	शेष:
		prपूर्णांकk(KERN_WARNING "Illegal RTC port %lx\n", addr);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण


/*
 * IO map support.
 */
व्योम __iomem *
marvel_ioremap(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ size)
अणु
	काष्ठा pci_controller *hose;
	अचिन्हित दीर्घ baddr, last;
	काष्ठा vm_काष्ठा *area;
	अचिन्हित दीर्घ vaddr;
	अचिन्हित दीर्घ *ptes;
	अचिन्हित दीर्घ pfn;

	/*
	 * Adjust the address.
	 */ 
	FIXUP_MEMADDR_VGA(addr);

	/*
	 * Find the hose.
	 */
	क्रम (hose = hose_head; hose; hose = hose->next) अणु
		अगर ((addr >> 32) == (hose->mem_space->start >> 32))
			अवरोध; 
	पूर्ण
	अगर (!hose)
		वापस शून्य;

	/*
	 * We have the hose - calculate the bus limits.
	 */
	baddr = addr - hose->mem_space->start;
	last = baddr + size - 1;

	/*
	 * Is it direct-mapped?
	 */
	अगर ((baddr >= __direct_map_base) && 
	    ((baddr + size - 1) < __direct_map_base + __direct_map_size)) अणु
		addr = IDENT_ADDR | (baddr - __direct_map_base);
		वापस (व्योम __iomem *) addr;
	पूर्ण

	/* 
	 * Check the scatter-gather arena.
	 */
	अगर (hose->sg_pci &&
	    baddr >= (अचिन्हित दीर्घ)hose->sg_pci->dma_base &&
	    last < (अचिन्हित दीर्घ)hose->sg_pci->dma_base + hose->sg_pci->size) अणु

		/*
		 * Adjust the limits (mappings must be page aligned)
		 */
		baddr -= hose->sg_pci->dma_base;
		last -= hose->sg_pci->dma_base;
		baddr &= PAGE_MASK;
		size = PAGE_ALIGN(last) - baddr;

		/*
		 * Map it.
		 */
		area = get_vm_area(size, VM_IOREMAP);
		अगर (!area)
			वापस शून्य;

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
				prपूर्णांकk("FAILED to map...\n");
				vमुक्त(area->addr);
				वापस शून्य;
			पूर्ण
		पूर्ण

		flush_tlb_all();

		vaddr = (अचिन्हित दीर्घ)area->addr + (addr & ~PAGE_MASK);

		वापस (व्योम __iomem *) vaddr;
	पूर्ण

	/* Assume it was alपढ़ोy a reasonable address */
	vaddr = baddr + hose->mem_space->start;
	वापस (व्योम __iomem *) vaddr;
पूर्ण

व्योम
marvel_iounmap(अस्थिर व्योम __iomem *xaddr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ) xaddr;
	अगर (addr >= VMALLOC_START)
		vमुक्त((व्योम *)(PAGE_MASK & addr)); 
पूर्ण

पूर्णांक
marvel_is_mmio(स्थिर अस्थिर व्योम __iomem *xaddr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ) xaddr;

	अगर (addr >= VMALLOC_START)
		वापस 1;
	अन्यथा
		वापस (addr & 0xFF000000UL) == 0;
पूर्ण

#घोषणा __marvel_is_port_kbd(a)	(((a) == 0x60) || ((a) == 0x64))
#घोषणा __marvel_is_port_rtc(a)	(((a) == 0x70) || ((a) == 0x71))

व्योम __iomem *marvel_ioporपंचांगap (अचिन्हित दीर्घ addr)
अणु
	FIXUP_IOADDR_VGA(addr);
	वापस (व्योम __iomem *)addr;
पूर्ण

अचिन्हित पूर्णांक
marvel_ioपढ़ो8(स्थिर व्योम __iomem *xaddr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ) xaddr;
	अगर (__marvel_is_port_kbd(addr))
		वापस 0;
	अन्यथा अगर (__marvel_is_port_rtc(addr))
		वापस __marvel_rtc_io(0, addr, 0);
	अन्यथा अगर (marvel_is_ioaddr(addr))
		वापस __kernel_ldbu(*(vucp)addr);
	अन्यथा
		/* this should catch other legacy addresses
		   that would normally fail on MARVEL,
		   because there really is nothing there...
		*/
		वापस ~0;
पूर्ण

व्योम
marvel_ioग_लिखो8(u8 b, व्योम __iomem *xaddr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ) xaddr;
	अगर (__marvel_is_port_kbd(addr))
		वापस;
	अन्यथा अगर (__marvel_is_port_rtc(addr)) 
		__marvel_rtc_io(b, addr, 1);
	अन्यथा अगर (marvel_is_ioaddr(addr))
		__kernel_stb(b, *(vucp)addr);
पूर्ण

#अगर_अघोषित CONFIG_ALPHA_GENERIC
EXPORT_SYMBOL(marvel_ioremap);
EXPORT_SYMBOL(marvel_iounmap);
EXPORT_SYMBOL(marvel_is_mmio);
EXPORT_SYMBOL(marvel_ioporपंचांगap);
EXPORT_SYMBOL(marvel_ioपढ़ो8);
EXPORT_SYMBOL(marvel_ioग_लिखो8);
#पूर्ण_अगर

/*
 * NUMA Support
 */
/**********
 * FIXME - क्रम now each cpu is a node by itself 
 *              -- no real support क्रम striped mode 
 **********
 */
पूर्णांक
marvel_pa_to_nid(अचिन्हित दीर्घ pa)
अणु
	पूर्णांक cpuid;

	अगर ((pa >> 43) & 1) 	/* I/O */ 
		cpuid = (~(pa >> 35) & 0xff);
	अन्यथा			/* mem */
		cpuid = ((pa >> 34) & 0x3) | ((pa >> (37 - 2)) & (0x1f << 2));

	वापस marvel_cpuid_to_nid(cpuid);
पूर्ण

पूर्णांक
marvel_cpuid_to_nid(पूर्णांक cpuid)
अणु
	वापस cpuid;
पूर्ण

अचिन्हित दीर्घ
marvel_node_mem_start(पूर्णांक nid)
अणु
	अचिन्हित दीर्घ pa;

	pa = (nid & 0x3) | ((nid & (0x1f << 2)) << 1);
	pa <<= 34;

	वापस pa;
पूर्ण

अचिन्हित दीर्घ
marvel_node_mem_size(पूर्णांक nid)
अणु
	वापस 16UL * 1024 * 1024 * 1024; /* 16GB */
पूर्ण


/* 
 * AGP GART Support.
 */
#समावेश <linux/agp_backend.h>
#समावेश <यंत्र/agp_backend.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>

काष्ठा marvel_agp_aperture अणु
	काष्ठा pci_iommu_arena *arena;
	दीर्घ pg_start;
	दीर्घ pg_count;
पूर्ण;

अटल पूर्णांक
marvel_agp_setup(alpha_agp_info *agp)
अणु
	काष्ठा marvel_agp_aperture *aper;

	अगर (!alpha_agpgart_size)
		वापस -ENOMEM;

	aper = kदो_स्मृति(माप(*aper), GFP_KERNEL);
	अगर (aper == शून्य) वापस -ENOMEM;

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
marvel_agp_cleanup(alpha_agp_info *agp)
अणु
	काष्ठा marvel_agp_aperture *aper = agp->aperture.sysdata;
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
marvel_agp_configure(alpha_agp_info *agp)
अणु
	io7_ioport_csrs *csrs = ((काष्ठा io7_port *)agp->hose->sysdata)->csrs;
	काष्ठा io7 *io7 = ((काष्ठा io7_port *)agp->hose->sysdata)->io7;
	अचिन्हित पूर्णांक new_rate = 0;
	अचिन्हित दीर्घ agp_pll;

	/*
	 * Check the requested mode against the PLL setting.
	 * The agpgart_be code has not programmed the card yet,
	 * so we can still tweak mode here.
	 */
	agp_pll = io7->csrs->POx_RST[IO7_AGP_PORT].csr;
	चयन(IO7_PLL_RNGB(agp_pll)) अणु
	हाल 0x4:				/* 2x only */
		/* 
		 * The PLL is only programmed क्रम 2x, so adjust the
		 * rate to 2x, अगर necessary.
		 */
		अगर (agp->mode.bits.rate != 2) 
			new_rate = 2;
		अवरोध;

	हाल 0x6:				/* 1x / 4x */
		/*
		 * The PLL is programmed क्रम 1x or 4x.  Don't go faster
		 * than requested, so अगर the requested rate is 2x, use 1x.
		 */
		अगर (agp->mode.bits.rate == 2) 
			new_rate = 1;
		अवरोध;

	शेष:				/* ??????? */
		/*
		 * Don't know what this PLL setting is, take the requested
		 * rate, but warn the user.
		 */
		prपूर्णांकk("%s: unknown PLL setting RNGB=%lx (PLL6_CTL=%016lx)\n",
		       __func__, IO7_PLL_RNGB(agp_pll), agp_pll);
		अवरोध;
	पूर्ण

	/*
	 * Set the new rate, अगर necessary.
	 */
	अगर (new_rate) अणु
		prपूर्णांकk("Requested AGP Rate %dX not compatible "
		       "with PLL setting - using %dX\n",
		       agp->mode.bits.rate,
		       new_rate);

		agp->mode.bits.rate = new_rate;
	पूर्ण
		
	prपूर्णांकk("Enabling AGP on hose %d: %dX%s RQ %d\n", 
	       agp->hose->index, agp->mode.bits.rate, 
	       agp->mode.bits.sba ? " - SBA" : "", agp->mode.bits.rq);

	csrs->AGP_CMD.csr = agp->mode.lw;

	वापस 0;
पूर्ण

अटल पूर्णांक 
marvel_agp_bind_memory(alpha_agp_info *agp, off_t pg_start, काष्ठा agp_memory *mem)
अणु
	काष्ठा marvel_agp_aperture *aper = agp->aperture.sysdata;
	वापस iommu_bind(aper->arena, aper->pg_start + pg_start, 
			  mem->page_count, mem->pages);
पूर्ण

अटल पूर्णांक 
marvel_agp_unbind_memory(alpha_agp_info *agp, off_t pg_start, काष्ठा agp_memory *mem)
अणु
	काष्ठा marvel_agp_aperture *aper = agp->aperture.sysdata;
	वापस iommu_unbind(aper->arena, aper->pg_start + pg_start,
			    mem->page_count);
पूर्ण

अटल अचिन्हित दीर्घ
marvel_agp_translate(alpha_agp_info *agp, dma_addr_t addr)
अणु
	काष्ठा marvel_agp_aperture *aper = agp->aperture.sysdata;
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

काष्ठा alpha_agp_ops marvel_agp_ops =
अणु
	.setup		= marvel_agp_setup,
	.cleanup	= marvel_agp_cleanup,
	.configure	= marvel_agp_configure,
	.bind		= marvel_agp_bind_memory,
	.unbind		= marvel_agp_unbind_memory,
	.translate	= marvel_agp_translate
पूर्ण;

alpha_agp_info *
marvel_agp_info(व्योम)
अणु
	काष्ठा pci_controller *hose;
	io7_ioport_csrs *csrs;
	alpha_agp_info *agp;
	काष्ठा io7 *io7;

	/*
	 * Find the first IO7 with an AGP card.
	 *
	 * FIXME -- there should be a better way (we want to be able to
	 * specअगरy and what अगर the agp card is not video???)
	 */
	hose = शून्य;
	क्रम (io7 = शून्य; (io7 = marvel_next_io7(io7)) != शून्य; ) अणु
		काष्ठा pci_controller *h;
		vuip addr;

		अगर (!io7->ports[IO7_AGP_PORT].enabled)
			जारी;

		h = io7->ports[IO7_AGP_PORT].hose;
		addr = (vuip)build_conf_addr(h, 0, PCI_DEVFN(5, 0), 0);

		अगर (*addr != 0xffffffffu) अणु
			hose = h;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!hose || !hose->sg_pci)
		वापस शून्य;

	prपूर्णांकk("MARVEL - using hose %d as AGP\n", hose->index);

	/* 
	 * Get the csrs from the hose.
	 */
	csrs = ((काष्ठा io7_port *)hose->sysdata)->csrs;

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
	agp->निजी = शून्य;
	agp->ops = &marvel_agp_ops;

	/*
	 * Aperture - not configured until ops.setup().
	 */
	agp->aperture.bus_base = 0;
	agp->aperture.size = 0;
	agp->aperture.sysdata = शून्य;

	/*
	 * Capabilities.
	 *
	 * NOTE: IO7 reports through AGP_STAT that it can support a पढ़ो queue
	 *       depth of 17 (rq = 0x10). It actually only supports a depth of
	 * 	 16 (rq = 0xf).
	 */
	agp->capability.lw = csrs->AGP_STAT.csr;
	agp->capability.bits.rq = 0xf;
	
	/*
	 * Mode.
	 */
	agp->mode.lw = csrs->AGP_CMD.csr;

	वापस agp;
पूर्ण
