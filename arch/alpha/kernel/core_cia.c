<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	linux/arch/alpha/kernel/core_cia.c
 *
 * Written by David A Rusling (david.rusling@reo.mts.dec.com).
 * December 1995.
 *
 *	Copyright (C) 1995  David A Rusling
 *	Copyright (C) 1997, 1998  Jay Estabrook
 *	Copyright (C) 1998, 1999, 2000  Riअक्षरd Henderson
 *
 * Code common to all CIA core logic chips.
 */

#घोषणा __EXTERN_INLINE अंतरभूत
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/core_cia.h>
#अघोषित __EXTERN_INLINE

#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/sched.h>
#समावेश <linux/init.h>
#समावेश <linux/memblock.h>

#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/mce.h>

#समावेश "proto.h"
#समावेश "pci_impl.h"


/*
 * NOTE: Herein lie back-to-back mb inकाष्ठाions.  They are magic. 
 * One plausible explanation is that the i/o controller करोes not properly
 * handle the प्रणाली transaction.  Another involves timing.  Ho hum.
 */

#घोषणा DEBUG_CONFIG 0
#अगर DEBUG_CONFIG
# define DBGC(args)	prपूर्णांकk args
#अन्यथा
# define DBGC(args)
#पूर्ण_अगर

#घोषणा vip	अस्थिर पूर्णांक  *

/*
 * Given a bus, device, and function number, compute resulting
 * configuration space address.  It is thereक्रमe not safe to have
 * concurrent invocations to configuration space access routines, but
 * there really shouldn't be any need क्रम this.
 *
 * Type 0:
 *
 *  3 3|3 3 2 2|2 2 2 2|2 2 2 2|1 1 1 1|1 1 1 1|1 1 
 *  3 2|1 0 9 8|7 6 5 4|3 2 1 0|9 8 7 6|5 4 3 2|1 0 9 8|7 6 5 4|3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * | | |D|D|D|D|D|D|D|D|D|D|D|D|D|D|D|D|D|D|D|D|D|F|F|F|R|R|R|R|R|R|0|0|
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
mk_conf_addr(काष्ठा pci_bus *bus_dev, अचिन्हित पूर्णांक device_fn, पूर्णांक where,
	     अचिन्हित दीर्घ *pci_addr, अचिन्हित अक्षर *type1)
अणु
	u8 bus = bus_dev->number;

	*type1 = (bus != 0);
	*pci_addr = (bus << 16) | (device_fn << 8) | where;

	DBGC(("mk_conf_addr(bus=%d ,device_fn=0x%x, where=0x%x,"
	      " returning address 0x%p\n"
	      bus, device_fn, where, *pci_addr));

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक
conf_पढ़ो(अचिन्हित दीर्घ addr, अचिन्हित अक्षर type1)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक stat0, value;
	पूर्णांक cia_cfg = 0;

	DBGC(("conf_read(addr=0x%lx, type1=%d) ", addr, type1));
	local_irq_save(flags);

	/* Reset status रेजिस्टर to aव्योम losing errors.  */
	stat0 = *(vip)CIA_IOC_CIA_ERR;
	*(vip)CIA_IOC_CIA_ERR = stat0;
	mb();
	*(vip)CIA_IOC_CIA_ERR; /* re-पढ़ो to क्रमce ग_लिखो */

	/* If Type1 access, must set CIA CFG. */
	अगर (type1) अणु
		cia_cfg = *(vip)CIA_IOC_CFG;
		*(vip)CIA_IOC_CFG = (cia_cfg & ~3) | 1;
		mb();
		*(vip)CIA_IOC_CFG;
	पूर्ण

	mb();
	draina();
	mcheck_expected(0) = 1;
	mcheck_taken(0) = 0;
	mb();

	/* Access configuration space.  */
	value = *(vip)addr;
	mb();
	mb();  /* magic */
	अगर (mcheck_taken(0)) अणु
		mcheck_taken(0) = 0;
		value = 0xffffffff;
		mb();
	पूर्ण
	mcheck_expected(0) = 0;
	mb();

	/* If Type1 access, must reset IOC CFG so normal IO space ops work.  */
	अगर (type1) अणु
		*(vip)CIA_IOC_CFG = cia_cfg;
		mb();
		*(vip)CIA_IOC_CFG;
	पूर्ण

	local_irq_restore(flags);
	DBGC(("done\n"));

	वापस value;
पूर्ण

अटल व्योम
conf_ग_लिखो(अचिन्हित दीर्घ addr, अचिन्हित पूर्णांक value, अचिन्हित अक्षर type1)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक stat0, cia_cfg = 0;

	DBGC(("conf_write(addr=0x%lx, type1=%d) ", addr, type1));
	local_irq_save(flags);

	/* Reset status रेजिस्टर to aव्योम losing errors.  */
	stat0 = *(vip)CIA_IOC_CIA_ERR;
	*(vip)CIA_IOC_CIA_ERR = stat0;
	mb();
	*(vip)CIA_IOC_CIA_ERR; /* re-पढ़ो to क्रमce ग_लिखो */

	/* If Type1 access, must set CIA CFG.  */
	अगर (type1) अणु
		cia_cfg = *(vip)CIA_IOC_CFG;
		*(vip)CIA_IOC_CFG = (cia_cfg & ~3) | 1;
		mb();
		*(vip)CIA_IOC_CFG;
	पूर्ण

	mb();
	draina();
	mcheck_expected(0) = 1;
	mcheck_taken(0) = 0;
	mb();

	/* Access configuration space.  */
	*(vip)addr = value;
	mb();
	*(vip)addr; /* पढ़ो back to क्रमce the ग_लिखो */

	mcheck_expected(0) = 0;
	mb();

	/* If Type1 access, must reset IOC CFG so normal IO space ops work.  */
	अगर (type1) अणु
		*(vip)CIA_IOC_CFG = cia_cfg;
		mb();
		*(vip)CIA_IOC_CFG;
	पूर्ण

	local_irq_restore(flags);
	DBGC(("done\n"));
पूर्ण

अटल पूर्णांक 
cia_पढ़ो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक where, पूर्णांक size,
		u32 *value)
अणु
	अचिन्हित दीर्घ addr, pci_addr;
	दीर्घ mask;
	अचिन्हित अक्षर type1;
	पूर्णांक shअगरt;

	अगर (mk_conf_addr(bus, devfn, where, &pci_addr, &type1))
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	mask = (size - 1) * 8;
	shअगरt = (where & 3) * 8;
	addr = (pci_addr << 5) + mask + CIA_CONF;
	*value = conf_पढ़ो(addr, type1) >> (shअगरt);
	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक 
cia_ग_लिखो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक where, पूर्णांक size,
		 u32 value)
अणु
	अचिन्हित दीर्घ addr, pci_addr;
	दीर्घ mask;
	अचिन्हित अक्षर type1;

	अगर (mk_conf_addr(bus, devfn, where, &pci_addr, &type1))
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	mask = (size - 1) * 8;
	addr = (pci_addr << 5) + mask + CIA_CONF;
	conf_ग_लिखो(addr, value << ((where & 3) * 8), type1);
	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

काष्ठा pci_ops cia_pci_ops = 
अणु
	.पढ़ो = 	cia_पढ़ो_config,
	.ग_लिखो =	cia_ग_लिखो_config,
पूर्ण;

/*
 * CIA Pass 1 and PYXIS Pass 1 and 2 have a broken scatter-gather tlb.
 * It cannot be invalidated.  Rather than hard code the pass numbers,
 * actually try the tbia to see अगर it works.
 */

व्योम
cia_pci_tbi(काष्ठा pci_controller *hose, dma_addr_t start, dma_addr_t end)
अणु
	wmb();
	*(vip)CIA_IOC_PCI_TBIA = 3;	/* Flush all locked and unlocked.  */
	mb();
	*(vip)CIA_IOC_PCI_TBIA;
पूर्ण

/*
 * On PYXIS, even अगर the tbia works, we cannot use it. It effectively locks
 * the chip (as well as direct ग_लिखो to the tag रेजिस्टरs) अगर there is a
 * SG DMA operation in progress. This is true at least क्रम PYXIS rev. 1,
 * so always use the method below.
 */
/*
 * This is the method NT and NetBSD use.
 *
 * Allocate mappings, and put the chip पूर्णांकo DMA loopback mode to पढ़ो a
 * garbage page.  This works by causing TLB misses, causing old entries to
 * be purged to make room क्रम the new entries coming in क्रम the garbage page.
 */

#घोषणा CIA_BROKEN_TBIA_BASE	0x30000000
#घोषणा CIA_BROKEN_TBIA_SIZE	1024

/* Always called with पूर्णांकerrupts disabled */
व्योम
cia_pci_tbi_try2(काष्ठा pci_controller *hose,
		 dma_addr_t start, dma_addr_t end)
अणु
	व्योम __iomem *bus_addr;
	पूर्णांक ctrl;

	/* Put the chip पूर्णांकo PCI loopback mode.  */
	mb();
	ctrl = *(vip)CIA_IOC_CIA_CTRL;
	*(vip)CIA_IOC_CIA_CTRL = ctrl | CIA_CTRL_PCI_LOOP_EN;
	mb();
	*(vip)CIA_IOC_CIA_CTRL;
	mb();

	/* Read from PCI dense memory space at TBI_ADDR, skipping 32k on
	   each पढ़ो.  This क्रमces SG TLB misses.  NetBSD claims that the
	   TLB entries are not quite LRU, meaning that we need to पढ़ो more
	   बार than there are actual tags.  The 2117x करोcs claim strict
	   round-robin.  Oh well, we've come this far...  */
	/* Even better - as seen on the PYXIS rev 1 the TLB tags 0-3 can
	   be filled by the TLB misses *only once* after being invalidated
	   (by tbia or direct ग_लिखो). Next misses won't update them even
	   though the lock bits are cleared. Tags 4-7 are "quite LRU" though,
	   so use them and पढ़ो at winकरोw 3 base exactly 4 बार. Reading
	   more someबार makes the chip crazy.  -ink */

	bus_addr = cia_ioremap(CIA_BROKEN_TBIA_BASE, 32768 * 4);

	cia_पढ़ोl(bus_addr + 0x00000);
	cia_पढ़ोl(bus_addr + 0x08000);
	cia_पढ़ोl(bus_addr + 0x10000);
	cia_पढ़ोl(bus_addr + 0x18000);

	cia_iounmap(bus_addr);

	/* Restore normal PCI operation.  */
	mb();
	*(vip)CIA_IOC_CIA_CTRL = ctrl;
	mb();
	*(vip)CIA_IOC_CIA_CTRL;
	mb();
पूर्ण

अटल अंतरभूत व्योम
cia_prepare_tbia_workaround(पूर्णांक winकरोw)
अणु
	अचिन्हित दीर्घ *ppte, pte;
	दीर्घ i;

	/* Use minimal 1K map. */
	ppte = memblock_alloc(CIA_BROKEN_TBIA_SIZE, 32768);
	अगर (!ppte)
		panic("%s: Failed to allocate %u bytes align=0x%x\n",
		      __func__, CIA_BROKEN_TBIA_SIZE, 32768);
	pte = (virt_to_phys(ppte) >> (PAGE_SHIFT - 1)) | 1;

	क्रम (i = 0; i < CIA_BROKEN_TBIA_SIZE / माप(अचिन्हित दीर्घ); ++i)
		ppte[i] = pte;

	*(vip)CIA_IOC_PCI_Wn_BASE(winकरोw) = CIA_BROKEN_TBIA_BASE | 3;
	*(vip)CIA_IOC_PCI_Wn_MASK(winकरोw)
	  = (CIA_BROKEN_TBIA_SIZE*1024 - 1) & 0xfff00000;
	*(vip)CIA_IOC_PCI_Tn_BASE(winकरोw) = virt_to_phys(ppte) >> 2;
पूर्ण

अटल व्योम __init
verअगरy_tb_operation(व्योम)
अणु
	अटल पूर्णांक page[PAGE_SIZE/4]
		__attribute__((aligned(PAGE_SIZE)))
		__initdata = अणु 0 पूर्ण;

	काष्ठा pci_iommu_arena *arena = pci_isa_hose->sg_isa;
	पूर्णांक ctrl, addr0, tag0, pte0, data0;
	पूर्णांक temp, use_tbia_try2 = 0;
	व्योम __iomem *bus_addr;

	/* pyxis -- tbia is broken */
	अगर (pci_isa_hose->dense_io_base)
		use_tbia_try2 = 1;

	/* Put the chip पूर्णांकo PCI loopback mode.  */
	mb();
	ctrl = *(vip)CIA_IOC_CIA_CTRL;
	*(vip)CIA_IOC_CIA_CTRL = ctrl | CIA_CTRL_PCI_LOOP_EN;
	mb();
	*(vip)CIA_IOC_CIA_CTRL;
	mb();

	/* Write a valid entry directly पूर्णांकo the TLB रेजिस्टरs.  */

	addr0 = arena->dma_base;
	tag0 = addr0 | 1;
	pte0 = (virt_to_phys(page) >> (PAGE_SHIFT - 1)) | 1;

	*(vip)CIA_IOC_TB_TAGn(0) = tag0;
	*(vip)CIA_IOC_TB_TAGn(1) = 0;
	*(vip)CIA_IOC_TB_TAGn(2) = 0;
	*(vip)CIA_IOC_TB_TAGn(3) = 0;
	*(vip)CIA_IOC_TB_TAGn(4) = 0;
	*(vip)CIA_IOC_TB_TAGn(5) = 0;
	*(vip)CIA_IOC_TB_TAGn(6) = 0;
	*(vip)CIA_IOC_TB_TAGn(7) = 0;
	*(vip)CIA_IOC_TBn_PAGEm(0,0) = pte0;
	*(vip)CIA_IOC_TBn_PAGEm(0,1) = 0;
	*(vip)CIA_IOC_TBn_PAGEm(0,2) = 0;
	*(vip)CIA_IOC_TBn_PAGEm(0,3) = 0;
	mb();

	/* Get a usable bus address */
	bus_addr = cia_ioremap(addr0, 8*PAGE_SIZE);

	/* First, verअगरy we can पढ़ो back what we've written.  If
	   this fails, we can't be sure of any of the other testing
	   we're going to करो, so bail.  */
	/* ??? Actually, we could करो the work with machine checks.
	   By passing this रेजिस्टर update test, we pretty much
	   guarantee that cia_pci_tbi_try1 works.  If this test
	   fails, cia_pci_tbi_try2 might still work.  */

	temp = *(vip)CIA_IOC_TB_TAGn(0);
	अगर (temp != tag0) अणु
		prपूर्णांकk("pci: failed tb register update test "
		       "(tag0 %#x != %#x)\n", temp, tag0);
		जाओ failed;
	पूर्ण
	temp = *(vip)CIA_IOC_TB_TAGn(1);
	अगर (temp != 0) अणु
		prपूर्णांकk("pci: failed tb register update test "
		       "(tag1 %#x != 0)\n", temp);
		जाओ failed;
	पूर्ण
	temp = *(vip)CIA_IOC_TBn_PAGEm(0,0);
	अगर (temp != pte0) अणु
		prपूर्णांकk("pci: failed tb register update test "
		       "(pte0 %#x != %#x)\n", temp, pte0);
		जाओ failed;
	पूर्ण
	prपूर्णांकk("pci: passed tb register update test\n");

	/* Second, verअगरy we can actually करो I/O through this entry.  */

	data0 = 0xdeadbeef;
	page[0] = data0;
	mcheck_expected(0) = 1;
	mcheck_taken(0) = 0;
	mb();
	temp = cia_पढ़ोl(bus_addr);
	mb();
	mcheck_expected(0) = 0;
	mb();
	अगर (mcheck_taken(0)) अणु
		prपूर्णांकk("pci: failed sg loopback i/o read test (mcheck)\n");
		जाओ failed;
	पूर्ण
	अगर (temp != data0) अणु
		prपूर्णांकk("pci: failed sg loopback i/o read test "
		       "(%#x != %#x)\n", temp, data0);
		जाओ failed;
	पूर्ण
	prपूर्णांकk("pci: passed sg loopback i/o read test\n");

	/* Third, try to invalidate the TLB.  */

	अगर (! use_tbia_try2) अणु
		cia_pci_tbi(arena->hose, 0, -1);
		temp = *(vip)CIA_IOC_TB_TAGn(0);
		अगर (temp & 1) अणु
			use_tbia_try2 = 1;
			prपूर्णांकk("pci: failed tbia test; workaround available\n");
		पूर्ण अन्यथा अणु
			prपूर्णांकk("pci: passed tbia test\n");
		पूर्ण
	पूर्ण

	/* Fourth, verअगरy the TLB snoops the EV5's caches when
	   करोing a tlb fill.  */

	data0 = 0x5adda15e;
	page[0] = data0;
	arena->ptes[4] = pte0;
	mcheck_expected(0) = 1;
	mcheck_taken(0) = 0;
	mb();
	temp = cia_पढ़ोl(bus_addr + 4*PAGE_SIZE);
	mb();
	mcheck_expected(0) = 0;
	mb();
	अगर (mcheck_taken(0)) अणु
		prपूर्णांकk("pci: failed pte write cache snoop test (mcheck)\n");
		जाओ failed;
	पूर्ण
	अगर (temp != data0) अणु
		prपूर्णांकk("pci: failed pte write cache snoop test "
		       "(%#x != %#x)\n", temp, data0);
		जाओ failed;
	पूर्ण
	prपूर्णांकk("pci: passed pte write cache snoop test\n");

	/* Fअगरth, verअगरy that a previously invalid PTE entry माला_लो
	   filled from the page table.  */

	data0 = 0xabcdef12;
	page[0] = data0;
	arena->ptes[5] = pte0;
	mcheck_expected(0) = 1;
	mcheck_taken(0) = 0;
	mb();
	temp = cia_पढ़ोl(bus_addr + 5*PAGE_SIZE);
	mb();
	mcheck_expected(0) = 0;
	mb();
	अगर (mcheck_taken(0)) अणु
		prपूर्णांकk("pci: failed valid tag invalid pte reload test "
		       "(mcheck; workaround available)\n");
		/* Work around this bug by aligning new allocations
		   on 4 page boundaries.  */
		arena->align_entry = 4;
	पूर्ण अन्यथा अगर (temp != data0) अणु
		prपूर्णांकk("pci: failed valid tag invalid pte reload test "
		       "(%#x != %#x)\n", temp, data0);
		जाओ failed;
	पूर्ण अन्यथा अणु
		prपूर्णांकk("pci: passed valid tag invalid pte reload test\n");
	पूर्ण

	/* Sixth, verअगरy machine checks are working.  Test invalid
	   pte under the same valid tag as we used above.  */

	mcheck_expected(0) = 1;
	mcheck_taken(0) = 0;
	mb();
	temp = cia_पढ़ोl(bus_addr + 6*PAGE_SIZE);
	mb();
	mcheck_expected(0) = 0;
	mb();
	prपूर्णांकk("pci: %s pci machine check test\n",
	       mcheck_taken(0) ? "passed" : "failed");

	/* Clean up after the tests.  */
	arena->ptes[4] = 0;
	arena->ptes[5] = 0;

	अगर (use_tbia_try2) अणु
		alpha_mv.mv_pci_tbi = cia_pci_tbi_try2;

		/* Tags 0-3 must be disabled अगर we use this workaraund. */
		wmb();
		*(vip)CIA_IOC_TB_TAGn(0) = 2;
		*(vip)CIA_IOC_TB_TAGn(1) = 2;
		*(vip)CIA_IOC_TB_TAGn(2) = 2;
		*(vip)CIA_IOC_TB_TAGn(3) = 2;

		prपूर्णांकk("pci: tbia workaround enabled\n");
	पूर्ण
	alpha_mv.mv_pci_tbi(arena->hose, 0, -1);

निकास:
	/* unmap the bus addr */
	cia_iounmap(bus_addr);

	/* Restore normal PCI operation.  */
	mb();
	*(vip)CIA_IOC_CIA_CTRL = ctrl;
	mb();
	*(vip)CIA_IOC_CIA_CTRL;
	mb();
	वापस;

failed:
	prपूर्णांकk("pci: disabling sg translation window\n");
	*(vip)CIA_IOC_PCI_W0_BASE = 0;
	*(vip)CIA_IOC_PCI_W1_BASE = 0;
	pci_isa_hose->sg_isa = शून्य;
	alpha_mv.mv_pci_tbi = शून्य;
	जाओ निकास;
पूर्ण

#अगर defined(ALPHA_RESTORE_SRM_SETUP)
/* Save CIA configuration data as the console had it set up.  */
काष्ठा 
अणु
    अचिन्हित पूर्णांक hae_mem;
    अचिन्हित पूर्णांक hae_io;
    अचिन्हित पूर्णांक pci_dac_offset;
    अचिन्हित पूर्णांक err_mask;
    अचिन्हित पूर्णांक cia_ctrl;
    अचिन्हित पूर्णांक cia_cnfg;
    काष्ठा अणु
	अचिन्हित पूर्णांक w_base;
	अचिन्हित पूर्णांक w_mask;
	अचिन्हित पूर्णांक t_base;
    पूर्ण winकरोw[4];
पूर्ण saved_config __attribute((common));

व्योम
cia_save_srm_settings(पूर्णांक is_pyxis)
अणु
	पूर्णांक i;

	/* Save some important रेजिस्टरs. */
	saved_config.err_mask       = *(vip)CIA_IOC_ERR_MASK;
	saved_config.cia_ctrl       = *(vip)CIA_IOC_CIA_CTRL;
	saved_config.hae_mem        = *(vip)CIA_IOC_HAE_MEM;
	saved_config.hae_io         = *(vip)CIA_IOC_HAE_IO;
	saved_config.pci_dac_offset = *(vip)CIA_IOC_PCI_W_DAC;

	अगर (is_pyxis)
	    saved_config.cia_cnfg   = *(vip)CIA_IOC_CIA_CNFG;
	अन्यथा
	    saved_config.cia_cnfg   = 0;

	/* Save DMA winकरोws configuration. */
	क्रम (i = 0; i < 4; i++) अणु
	    saved_config.winकरोw[i].w_base = *(vip)CIA_IOC_PCI_Wn_BASE(i);
	    saved_config.winकरोw[i].w_mask = *(vip)CIA_IOC_PCI_Wn_MASK(i);
	    saved_config.winकरोw[i].t_base = *(vip)CIA_IOC_PCI_Tn_BASE(i);
	पूर्ण
	mb();
पूर्ण

व्योम
cia_restore_srm_settings(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 4; i++) अणु
	    *(vip)CIA_IOC_PCI_Wn_BASE(i) = saved_config.winकरोw[i].w_base;
	    *(vip)CIA_IOC_PCI_Wn_MASK(i) = saved_config.winकरोw[i].w_mask;
	    *(vip)CIA_IOC_PCI_Tn_BASE(i) = saved_config.winकरोw[i].t_base;
	पूर्ण

	*(vip)CIA_IOC_HAE_MEM   = saved_config.hae_mem;
	*(vip)CIA_IOC_HAE_IO    = saved_config.hae_io;
	*(vip)CIA_IOC_PCI_W_DAC = saved_config.pci_dac_offset;	
	*(vip)CIA_IOC_ERR_MASK  = saved_config.err_mask;
	*(vip)CIA_IOC_CIA_CTRL  = saved_config.cia_ctrl;

	अगर (saved_config.cia_cnfg) /* Must be pyxis. */
	    *(vip)CIA_IOC_CIA_CNFG  = saved_config.cia_cnfg;

	mb();
पूर्ण
#अन्यथा /* ALPHA_RESTORE_SRM_SETUP */
#घोषणा cia_save_srm_settings(p)	करो अणुपूर्ण जबतक (0)
#घोषणा cia_restore_srm_settings()	करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर /* ALPHA_RESTORE_SRM_SETUP */


अटल व्योम __init
करो_init_arch(पूर्णांक is_pyxis)
अणु
	काष्ठा pci_controller *hose;
	पूर्णांक temp, cia_rev, tbia_winकरोw;

	cia_rev = *(vip)CIA_IOC_CIA_REV & CIA_REV_MASK;
	prपूर्णांकk("pci: cia revision %d%s\n",
	       cia_rev, is_pyxis ? " (pyxis)" : "");

	अगर (alpha_using_srm)
		cia_save_srm_settings(is_pyxis);

	/* Set up error reporting.  */
	temp = *(vip)CIA_IOC_ERR_MASK;
	temp &= ~(CIA_ERR_CPU_PE | CIA_ERR_MEM_NEM | CIA_ERR_PA_PTE_INV
		  | CIA_ERR_RCVD_MAS_ABT | CIA_ERR_RCVD_TAR_ABT);
	*(vip)CIA_IOC_ERR_MASK = temp;

	/* Clear all currently pending errors.  */
	temp = *(vip)CIA_IOC_CIA_ERR;
	*(vip)CIA_IOC_CIA_ERR = temp;

	/* Turn on mchecks.  */
	temp = *(vip)CIA_IOC_CIA_CTRL;
	temp |= CIA_CTRL_FILL_ERR_EN | CIA_CTRL_MCHK_ERR_EN;
	*(vip)CIA_IOC_CIA_CTRL = temp;

	/* Clear the CFG रेजिस्टर, which माला_लो used क्रम PCI config space
	   accesses.  That is the way we want to use it, and we करो not
	   want to depend on what ARC or SRM might have left behind.  */
	*(vip)CIA_IOC_CFG = 0;
 
	/* Zero the HAEs.  */
	*(vip)CIA_IOC_HAE_MEM = 0;
	*(vip)CIA_IOC_HAE_IO = 0;

	/* For PYXIS, we always use BWX bus and i/o accesses.  To that end,
	   make sure they're enabled on the controller.  At the same समय,
	   enable the monster winकरोw.  */
	अगर (is_pyxis) अणु
		temp = *(vip)CIA_IOC_CIA_CNFG;
		temp |= CIA_CNFG_IOA_BWEN | CIA_CNFG_PCI_MWEN;
		*(vip)CIA_IOC_CIA_CNFG = temp;
	पूर्ण

	/* Synchronize with all previous changes.  */
	mb();
	*(vip)CIA_IOC_CIA_REV;

	/*
	 * Create our single hose.
	 */

	pci_isa_hose = hose = alloc_pci_controller();
	hose->io_space = &ioport_resource;
	hose->mem_space = &iomem_resource;
	hose->index = 0;

	अगर (! is_pyxis) अणु
		काष्ठा resource *hae_mem = alloc_resource();
		hose->mem_space = hae_mem;

		hae_mem->start = 0;
		hae_mem->end = CIA_MEM_R1_MASK;
		hae_mem->name = pci_hae0_name;
		hae_mem->flags = IORESOURCE_MEM;

		अगर (request_resource(&iomem_resource, hae_mem) < 0)
			prपूर्णांकk(KERN_ERR "Failed to request HAE_MEM\n");

		hose->sparse_mem_base = CIA_SPARSE_MEM - IDENT_ADDR;
		hose->dense_mem_base = CIA_DENSE_MEM - IDENT_ADDR;
		hose->sparse_io_base = CIA_IO - IDENT_ADDR;
		hose->dense_io_base = 0;
	पूर्ण अन्यथा अणु
		hose->sparse_mem_base = 0;
		hose->dense_mem_base = CIA_BW_MEM - IDENT_ADDR;
		hose->sparse_io_base = 0;
		hose->dense_io_base = CIA_BW_IO - IDENT_ADDR;
	पूर्ण

	/*
	 * Set up the PCI to मुख्य memory translation winकरोws.
	 *
	 * Winकरोw 0 is S/G 8MB at 8MB (क्रम isa)
	 * Winकरोw 1 is S/G 1MB at 768MB (क्रम tbia) (unused क्रम CIA rev 1)
	 * Winकरोw 2 is direct access 2GB at 2GB
	 * Winकरोw 3 is DAC access 4GB at 8GB (or S/G क्रम tbia अगर CIA rev 1)
	 *
	 * ??? NetBSD hपूर्णांकs that page tables must be aligned to 32K,
	 * possibly due to a hardware bug.  This is over-aligned
	 * from the 8K alignment one would expect क्रम an 8MB winकरोw. 
	 * No description of what revisions affected.
	 */

	hose->sg_pci = शून्य;
	hose->sg_isa = iommu_arena_new(hose, 0x00800000, 0x00800000, 32768);

	__direct_map_base = 0x80000000;
	__direct_map_size = 0x80000000;

	*(vip)CIA_IOC_PCI_W0_BASE = hose->sg_isa->dma_base | 3;
	*(vip)CIA_IOC_PCI_W0_MASK = (hose->sg_isa->size - 1) & 0xfff00000;
	*(vip)CIA_IOC_PCI_T0_BASE = virt_to_phys(hose->sg_isa->ptes) >> 2;

	*(vip)CIA_IOC_PCI_W2_BASE = __direct_map_base | 1;
	*(vip)CIA_IOC_PCI_W2_MASK = (__direct_map_size - 1) & 0xfff00000;
	*(vip)CIA_IOC_PCI_T2_BASE = 0 >> 2;

	/* On PYXIS we have the monster winकरोw, selected by bit 40, so
	   there is no need क्रम winकरोw3 to be enabled.

	   On CIA, we करोn't have true arbitrary addressing -- bits <39:32>
	   are compared against W_DAC.  We can, however, directly map 4GB,
	   which is better than beक्रमe.  However, due to assumptions made
	   अन्यथाwhere, we should not claim that we support DAC unless that
	   4GB covers all of physical memory.

	   On CIA rev 1, apparently W1 and W2 can't be used क्रम SG. 
	   At least, there are reports that it करोesn't work क्रम Alcor. 
	   In that हाल, we have no choice but to use W3 क्रम the TBIA 
	   workaround, which means we can't use DAC at all. */ 

	tbia_winकरोw = 1;
	अगर (is_pyxis) अणु
		*(vip)CIA_IOC_PCI_W3_BASE = 0;
	पूर्ण अन्यथा अगर (cia_rev == 1) अणु
		*(vip)CIA_IOC_PCI_W1_BASE = 0;
		tbia_winकरोw = 3;
	पूर्ण अन्यथा अगर (max_low_pfn > (0x100000000UL >> PAGE_SHIFT)) अणु
		*(vip)CIA_IOC_PCI_W3_BASE = 0;
	पूर्ण अन्यथा अणु
		*(vip)CIA_IOC_PCI_W3_BASE = 0x00000000 | 1 | 8;
		*(vip)CIA_IOC_PCI_W3_MASK = 0xfff00000;
		*(vip)CIA_IOC_PCI_T3_BASE = 0 >> 2;

		alpha_mv.pci_dac_offset = 0x200000000UL;
		*(vip)CIA_IOC_PCI_W_DAC = alpha_mv.pci_dac_offset >> 32;
	पूर्ण

	/* Prepare workaround क्रम apparently broken tbia. */
	cia_prepare_tbia_workaround(tbia_winकरोw);
पूर्ण

व्योम __init
cia_init_arch(व्योम)
अणु
	करो_init_arch(0);
पूर्ण

व्योम __init
pyxis_init_arch(व्योम)
अणु
	/* On pyxis machines we can precisely calculate the
	   CPU घड़ी frequency using pyxis real समय counter.
	   It's especially useful क्रम SX164 with broken RTC.

	   Both CPU and chipset are driven by the single 16.666M
	   or 16.667M crystal oscillator. PYXIS_RT_COUNT घड़ी is
	   66.66 MHz. -ink */

	अचिन्हित पूर्णांक cc0, cc1;
	अचिन्हित दीर्घ pyxis_cc;

	__यंत्र__ __अस्थिर__ ("rpcc %0" : "=r"(cc0));
	pyxis_cc = *(vulp)PYXIS_RT_COUNT;
	करो अणु पूर्ण जबतक(*(vulp)PYXIS_RT_COUNT - pyxis_cc < 4096);
	__यंत्र__ __अस्थिर__ ("rpcc %0" : "=r"(cc1));
	cc1 -= cc0;
	hwrpb->cycle_freq = ((cc1 >> 11) * 100000000UL) / 3;
	hwrpb_update_checksum(hwrpb);

	करो_init_arch(1);
पूर्ण

व्योम
cia_समाप्त_arch(पूर्णांक mode)
अणु
	अगर (alpha_using_srm)
		cia_restore_srm_settings();
पूर्ण

व्योम __init
cia_init_pci(व्योम)
अणु
	/* Must delay this from init_arch, as we need machine checks.  */
	verअगरy_tb_operation();
	common_init_pci();
पूर्ण

अटल अंतरभूत व्योम
cia_pci_clr_err(व्योम)
अणु
	पूर्णांक jd;

	jd = *(vip)CIA_IOC_CIA_ERR;
	*(vip)CIA_IOC_CIA_ERR = jd;
	mb();
	*(vip)CIA_IOC_CIA_ERR;		/* re-पढ़ो to क्रमce ग_लिखो.  */
पूर्ण

#अगर_घोषित CONFIG_VERBOSE_MCHECK
अटल व्योम
cia_decode_pci_error(काष्ठा el_CIA_sysdata_mcheck *cia, स्थिर अक्षर *msg)
अणु
	अटल स्थिर अक्षर * स्थिर pci_cmd_desc[16] = अणु
		"Interrupt Acknowledge", "Special Cycle", "I/O Read",
		"I/O Write", "Reserved 0x4", "Reserved 0x5", "Memory Read",
		"Memory Write", "Reserved 0x8", "Reserved 0x9",
		"Configuration Read", "Configuration Write",
		"Memory Read Multiple", "Dual Address Cycle",
		"Memory Read Line", "Memory Write and Invalidate"
	पूर्ण;

	अगर (cia->cia_err & (CIA_ERR_COR_ERR
			    | CIA_ERR_UN_COR_ERR
			    | CIA_ERR_MEM_NEM
			    | CIA_ERR_PA_PTE_INV)) अणु
		अटल स्थिर अक्षर * स्थिर winकरोw_desc[6] = अणु
			"No window active", "Window 0 hit", "Window 1 hit",
			"Window 2 hit", "Window 3 hit", "Monster window hit"
		पूर्ण;

		स्थिर अक्षर *winकरोw;
		स्थिर अक्षर *cmd;
		अचिन्हित दीर्घ addr, पंचांगp;
		पूर्णांक lock, dac;
	
		cmd = pci_cmd_desc[cia->pci_err0 & 0x7];
		lock = (cia->pci_err0 >> 4) & 1;
		dac = (cia->pci_err0 >> 5) & 1;

		पंचांगp = (cia->pci_err0 >> 8) & 0x1F;
		पंचांगp = ffs(पंचांगp);
		winकरोw = winकरोw_desc[पंचांगp];

		addr = cia->pci_err1;
		अगर (dac) अणु
			पंचांगp = *(vip)CIA_IOC_PCI_W_DAC & 0xFFUL;
			addr |= पंचांगp << 32;
		पूर्ण

		prपूर्णांकk(KERN_CRIT "CIA machine check: %s\n", msg);
		prपूर्णांकk(KERN_CRIT "  DMA command: %s\n", cmd);
		prपूर्णांकk(KERN_CRIT "  PCI address: %#010lx\n", addr);
		prपूर्णांकk(KERN_CRIT "  %s, Lock: %d, DAC: %d\n",
		       winकरोw, lock, dac);
	पूर्ण अन्यथा अगर (cia->cia_err & (CIA_ERR_PERR
				   | CIA_ERR_PCI_ADDR_PE
				   | CIA_ERR_RCVD_MAS_ABT
				   | CIA_ERR_RCVD_TAR_ABT
				   | CIA_ERR_IOA_TIMEOUT)) अणु
		अटल स्थिर अक्षर * स्थिर master_st_desc[16] = अणु
			"Idle", "Drive bus", "Address step cycle",
			"Address cycle", "Data cycle", "Last read data cycle",
			"Last write data cycle", "Read stop cycle",
			"Write stop cycle", "Read turnaround cycle",
			"Write turnaround cycle", "Reserved 0xB",
			"Reserved 0xC", "Reserved 0xD", "Reserved 0xE",
			"Unknown state"
		पूर्ण;
		अटल स्थिर अक्षर * स्थिर target_st_desc[16] = अणु
			"Idle", "Busy", "Read data cycle", "Write data cycle",
			"Read stop cycle", "Write stop cycle",
			"Read turnaround cycle", "Write turnaround cycle",
			"Read wait cycle", "Write wait cycle",
			"Reserved 0xA", "Reserved 0xB", "Reserved 0xC",
			"Reserved 0xD", "Reserved 0xE", "Unknown state"
		पूर्ण;

		स्थिर अक्षर *cmd;
		स्थिर अक्षर *master, *target;
		अचिन्हित दीर्घ addr, पंचांगp;
		पूर्णांक dac;

		master = master_st_desc[(cia->pci_err0 >> 16) & 0xF];
		target = target_st_desc[(cia->pci_err0 >> 20) & 0xF];
		cmd = pci_cmd_desc[(cia->pci_err0 >> 24) & 0xF];
		dac = (cia->pci_err0 >> 28) & 1;

		addr = cia->pci_err2;
		अगर (dac) अणु
			पंचांगp = *(अस्थिर पूर्णांक *)CIA_IOC_PCI_W_DAC & 0xFFUL;
			addr |= पंचांगp << 32;
		पूर्ण

		prपूर्णांकk(KERN_CRIT "CIA machine check: %s\n", msg);
		prपूर्णांकk(KERN_CRIT "  PCI command: %s\n", cmd);
		prपूर्णांकk(KERN_CRIT "  Master state: %s, Target state: %s\n",
		       master, target);
		prपूर्णांकk(KERN_CRIT "  PCI address: %#010lx, DAC: %d\n",
		       addr, dac);
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_CRIT "CIA machine check: %s\n", msg);
		prपूर्णांकk(KERN_CRIT "  Unknown PCI error\n");
		prपूर्णांकk(KERN_CRIT "  PCI_ERR0 = %#08lx", cia->pci_err0);
		prपूर्णांकk(KERN_CRIT "  PCI_ERR1 = %#08lx", cia->pci_err1);
		prपूर्णांकk(KERN_CRIT "  PCI_ERR2 = %#08lx", cia->pci_err2);
	पूर्ण
पूर्ण

अटल व्योम
cia_decode_mem_error(काष्ठा el_CIA_sysdata_mcheck *cia, स्थिर अक्षर *msg)
अणु
	अचिन्हित दीर्घ mem_port_addr;
	अचिन्हित दीर्घ mem_port_mask;
	स्थिर अक्षर *mem_port_cmd;
	स्थिर अक्षर *seq_state;
	स्थिर अक्षर *set_select;
	अचिन्हित दीर्घ पंचांगp;

	/* If this is a DMA command, also decode the PCI bits.  */
	अगर ((cia->mem_err1 >> 20) & 1)
		cia_decode_pci_error(cia, msg);
	अन्यथा
		prपूर्णांकk(KERN_CRIT "CIA machine check: %s\n", msg);

	mem_port_addr = cia->mem_err0 & 0xfffffff0;
	mem_port_addr |= (cia->mem_err1 & 0x83UL) << 32;

	mem_port_mask = (cia->mem_err1 >> 12) & 0xF;

	पंचांगp = (cia->mem_err1 >> 8) & 0xF;
	पंचांगp |= ((cia->mem_err1 >> 20) & 1) << 4;
	अगर ((पंचांगp & 0x1E) == 0x06)
		mem_port_cmd = "WRITE BLOCK or WRITE BLOCK LOCK";
	अन्यथा अगर ((पंचांगp & 0x1C) == 0x08)
		mem_port_cmd = "READ MISS or READ MISS MODIFY";
	अन्यथा अगर (पंचांगp == 0x1C)
		mem_port_cmd = "BC VICTIM";
	अन्यथा अगर ((पंचांगp & 0x1E) == 0x0E)
		mem_port_cmd = "READ MISS MODIFY";
	अन्यथा अगर ((पंचांगp & 0x1C) == 0x18)
		mem_port_cmd = "DMA READ or DMA READ MODIFY";
	अन्यथा अगर ((पंचांगp & 0x1E) == 0x12)
		mem_port_cmd = "DMA WRITE";
	अन्यथा
		mem_port_cmd = "Unknown";

	पंचांगp = (cia->mem_err1 >> 16) & 0xF;
	चयन (पंचांगp) अणु
	हाल 0x0:
		seq_state = "Idle";
		अवरोध;
	हाल 0x1:
		seq_state = "DMA READ or DMA WRITE";
		अवरोध;
	हाल 0x2: हाल 0x3:
		seq_state = "READ MISS (or READ MISS MODIFY) with victim";
		अवरोध;
	हाल 0x4: हाल 0x5: हाल 0x6:
		seq_state = "READ MISS (or READ MISS MODIFY) with no victim";
		अवरोध;
	हाल 0x8: हाल 0x9: हाल 0xB:
		seq_state = "Refresh";
		अवरोध;
	हाल 0xC:
		seq_state = "Idle, waiting for DMA pending read";
		अवरोध;
	हाल 0xE: हाल 0xF:
		seq_state = "Idle, ras precharge";
		अवरोध;
	शेष:
		seq_state = "Unknown";
		अवरोध;
	पूर्ण

	पंचांगp = (cia->mem_err1 >> 24) & 0x1F;
	चयन (पंचांगp) अणु
	हाल 0x00: set_select = "Set 0 selected"; अवरोध;
	हाल 0x01: set_select = "Set 1 selected"; अवरोध;
	हाल 0x02: set_select = "Set 2 selected"; अवरोध;
	हाल 0x03: set_select = "Set 3 selected"; अवरोध;
	हाल 0x04: set_select = "Set 4 selected"; अवरोध;
	हाल 0x05: set_select = "Set 5 selected"; अवरोध;
	हाल 0x06: set_select = "Set 6 selected"; अवरोध;
	हाल 0x07: set_select = "Set 7 selected"; अवरोध;
	हाल 0x08: set_select = "Set 8 selected"; अवरोध;
	हाल 0x09: set_select = "Set 9 selected"; अवरोध;
	हाल 0x0A: set_select = "Set A selected"; अवरोध;
	हाल 0x0B: set_select = "Set B selected"; अवरोध;
	हाल 0x0C: set_select = "Set C selected"; अवरोध;
	हाल 0x0D: set_select = "Set D selected"; अवरोध;
	हाल 0x0E: set_select = "Set E selected"; अवरोध;
	हाल 0x0F: set_select = "Set F selected"; अवरोध;
	हाल 0x10: set_select = "No set selected"; अवरोध;
	हाल 0x1F: set_select = "Refresh cycle"; अवरोध;
	शेष:   set_select = "Unknown"; अवरोध;
	पूर्ण

	prपूर्णांकk(KERN_CRIT "  Memory port command: %s\n", mem_port_cmd);
	prपूर्णांकk(KERN_CRIT "  Memory port address: %#010lx, mask: %#lx\n",
	       mem_port_addr, mem_port_mask);
	prपूर्णांकk(KERN_CRIT "  Memory sequencer state: %s\n", seq_state);
	prपूर्णांकk(KERN_CRIT "  Memory set: %s\n", set_select);
पूर्ण

अटल व्योम
cia_decode_ecc_error(काष्ठा el_CIA_sysdata_mcheck *cia, स्थिर अक्षर *msg)
अणु
	दीर्घ syn;
	दीर्घ i;
	स्थिर अक्षर *fmt;

	cia_decode_mem_error(cia, msg);

	syn = cia->cia_syn & 0xff;
	अगर (syn == (syn & -syn)) अणु
		fmt = KERN_CRIT "  ECC syndrome %#x -- check bit %d\n";
		i = ffs(syn) - 1;
	पूर्ण अन्यथा अणु
		अटल अचिन्हित अक्षर स्थिर data_bit[64] = अणु
			0xCE, 0xCB, 0xD3, 0xD5,
			0xD6, 0xD9, 0xDA, 0xDC,
			0x23, 0x25, 0x26, 0x29,
			0x2A, 0x2C, 0x31, 0x34,
			0x0E, 0x0B, 0x13, 0x15,
			0x16, 0x19, 0x1A, 0x1C,
			0xE3, 0xE5, 0xE6, 0xE9,
			0xEA, 0xEC, 0xF1, 0xF4,
			0x4F, 0x4A, 0x52, 0x54,
			0x57, 0x58, 0x5B, 0x5D,
			0xA2, 0xA4, 0xA7, 0xA8,
			0xAB, 0xAD, 0xB0, 0xB5,
			0x8F, 0x8A, 0x92, 0x94,
			0x97, 0x98, 0x9B, 0x9D,
			0x62, 0x64, 0x67, 0x68,
			0x6B, 0x6D, 0x70, 0x75
		पूर्ण;

		क्रम (i = 0; i < 64; ++i)
			अगर (data_bit[i] == syn)
				अवरोध;

		अगर (i < 64)
			fmt = KERN_CRIT "  ECC syndrome %#x -- data bit %d\n";
		अन्यथा
			fmt = KERN_CRIT "  ECC syndrome %#x -- unknown bit\n";
	पूर्ण

	prपूर्णांकk (fmt, syn, i);
पूर्ण

अटल व्योम
cia_decode_parity_error(काष्ठा el_CIA_sysdata_mcheck *cia)
अणु
	अटल स्थिर अक्षर * स्थिर cmd_desc[16] = अणु
		"NOP", "LOCK", "FETCH", "FETCH_M", "MEMORY BARRIER",
		"SET DIRTY", "WRITE BLOCK", "WRITE BLOCK LOCK",
		"READ MISS0", "READ MISS1", "READ MISS MOD0",
		"READ MISS MOD1", "BCACHE VICTIM", "Spare",
		"READ MISS MOD STC0", "READ MISS MOD STC1"
	पूर्ण;

	अचिन्हित दीर्घ addr;
	अचिन्हित दीर्घ mask;
	स्थिर अक्षर *cmd;
	पूर्णांक par;

	addr = cia->cpu_err0 & 0xfffffff0;
	addr |= (cia->cpu_err1 & 0x83UL) << 32;
	cmd = cmd_desc[(cia->cpu_err1 >> 8) & 0xF];
	mask = (cia->cpu_err1 >> 12) & 0xF;
	par = (cia->cpu_err1 >> 21) & 1;

	prपूर्णांकk(KERN_CRIT "CIA machine check: System bus parity error\n");
	prपूर्णांकk(KERN_CRIT "  Command: %s, Parity bit: %d\n", cmd, par);
	prपूर्णांकk(KERN_CRIT "  Address: %#010lx, Mask: %#lx\n", addr, mask);
पूर्ण
#पूर्ण_अगर /* CONFIG_VERBOSE_MCHECK */


अटल पूर्णांक
cia_decode_mchk(अचिन्हित दीर्घ la_ptr)
अणु
	काष्ठा el_common *com;
	काष्ठा el_CIA_sysdata_mcheck *cia;

	com = (व्योम *)la_ptr;
	cia = (व्योम *)(la_ptr + com->sys_offset);

	अगर ((cia->cia_err & CIA_ERR_VALID) == 0)
		वापस 0;

#अगर_घोषित CONFIG_VERBOSE_MCHECK
	अगर (!alpha_verbose_mcheck)
		वापस 1;

	चयन (ffs(cia->cia_err & 0xfff) - 1) अणु
	हाल 0: /* CIA_ERR_COR_ERR */
		cia_decode_ecc_error(cia, "Corrected ECC error");
		अवरोध;
	हाल 1: /* CIA_ERR_UN_COR_ERR */
		cia_decode_ecc_error(cia, "Uncorrected ECC error");
		अवरोध;
	हाल 2: /* CIA_ERR_CPU_PE */
		cia_decode_parity_error(cia);
		अवरोध;
	हाल 3: /* CIA_ERR_MEM_NEM */
		cia_decode_mem_error(cia, "Access to nonexistent memory");
		अवरोध;
	हाल 4: /* CIA_ERR_PCI_SERR */
		cia_decode_pci_error(cia, "PCI bus system error");
		अवरोध;
	हाल 5: /* CIA_ERR_PERR */
		cia_decode_pci_error(cia, "PCI data parity error");
		अवरोध;
	हाल 6: /* CIA_ERR_PCI_ADDR_PE */
		cia_decode_pci_error(cia, "PCI address parity error");
		अवरोध;
	हाल 7: /* CIA_ERR_RCVD_MAS_ABT */
		cia_decode_pci_error(cia, "PCI master abort");
		अवरोध;
	हाल 8: /* CIA_ERR_RCVD_TAR_ABT */
		cia_decode_pci_error(cia, "PCI target abort");
		अवरोध;
	हाल 9: /* CIA_ERR_PA_PTE_INV */
		cia_decode_pci_error(cia, "PCI invalid PTE");
		अवरोध;
	हाल 10: /* CIA_ERR_FROM_WRT_ERR */
		cia_decode_mem_error(cia, "Write to flash ROM attempted");
		अवरोध;
	हाल 11: /* CIA_ERR_IOA_TIMEOUT */
		cia_decode_pci_error(cia, "I/O timeout");
		अवरोध;
	पूर्ण

	अगर (cia->cia_err & CIA_ERR_LOST_CORR_ERR)
		prपूर्णांकk(KERN_CRIT "CIA lost machine check: "
		       "Correctable ECC error\n");
	अगर (cia->cia_err & CIA_ERR_LOST_UN_CORR_ERR)
		prपूर्णांकk(KERN_CRIT "CIA lost machine check: "
		       "Uncorrectable ECC error\n");
	अगर (cia->cia_err & CIA_ERR_LOST_CPU_PE)
		prपूर्णांकk(KERN_CRIT "CIA lost machine check: "
		       "System bus parity error\n");
	अगर (cia->cia_err & CIA_ERR_LOST_MEM_NEM)
		prपूर्णांकk(KERN_CRIT "CIA lost machine check: "
		       "Access to nonexistent memory\n");
	अगर (cia->cia_err & CIA_ERR_LOST_PERR)
		prपूर्णांकk(KERN_CRIT "CIA lost machine check: "
		       "PCI data parity error\n");
	अगर (cia->cia_err & CIA_ERR_LOST_PCI_ADDR_PE)
		prपूर्णांकk(KERN_CRIT "CIA lost machine check: "
		       "PCI address parity error\n");
	अगर (cia->cia_err & CIA_ERR_LOST_RCVD_MAS_ABT)
		prपूर्णांकk(KERN_CRIT "CIA lost machine check: "
		       "PCI master abort\n");
	अगर (cia->cia_err & CIA_ERR_LOST_RCVD_TAR_ABT)
		prपूर्णांकk(KERN_CRIT "CIA lost machine check: "
		       "PCI target abort\n");
	अगर (cia->cia_err & CIA_ERR_LOST_PA_PTE_INV)
		prपूर्णांकk(KERN_CRIT "CIA lost machine check: "
		       "PCI invalid PTE\n");
	अगर (cia->cia_err & CIA_ERR_LOST_FROM_WRT_ERR)
		prपूर्णांकk(KERN_CRIT "CIA lost machine check: "
		       "Write to flash ROM attempted\n");
	अगर (cia->cia_err & CIA_ERR_LOST_IOA_TIMEOUT)
		prपूर्णांकk(KERN_CRIT "CIA lost machine check: "
		       "I/O timeout\n");
#पूर्ण_अगर /* CONFIG_VERBOSE_MCHECK */

	वापस 1;
पूर्ण

व्योम
cia_machine_check(अचिन्हित दीर्घ vector, अचिन्हित दीर्घ la_ptr)
अणु
	पूर्णांक expected;

	/* Clear the error beक्रमe any reporting.  */
	mb();
	mb();  /* magic */
	draina();
	cia_pci_clr_err();
	wrmces(rdmces());	/* reset machine check pending flag.  */
	mb();

	expected = mcheck_expected(0);
	अगर (!expected && vector == 0x660)
		expected = cia_decode_mchk(la_ptr);
	process_mcheck_info(vector, la_ptr, "CIA", expected);
पूर्ण
