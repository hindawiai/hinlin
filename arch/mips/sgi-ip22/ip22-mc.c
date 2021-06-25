<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ip22-mc.c: Routines क्रम manipulating SGI Memory Controller.
 *
 * Copyright (C) 1996 David S. Miller (davem@davemloft.net)
 * Copyright (C) 1999 Andrew R. Baker (andrewb@uab.edu) - Indigo2 changes
 * Copyright (C) 2003 Ladislav Michl  (ladis@linux-mips.org)
 * Copyright (C) 2004 Peter Fuerst    (pf@net.alphadv.de) - IP28
 */

#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/memblock.h>
#समावेश <linux/spinlock.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/sgialib.h>
#समावेश <यंत्र/sgi/mc.h>
#समावेश <यंत्र/sgi/hpc3.h>
#समावेश <यंत्र/sgi/ip22.h>

काष्ठा sgimc_regs *sgimc;

EXPORT_SYMBOL(sgimc);

अटल अंतरभूत अचिन्हित दीर्घ get_bank_addr(अचिन्हित पूर्णांक memconfig)
अणु
	वापस (memconfig & SGIMC_MCONFIG_BASEADDR) << ((sgimc->प्रणालीid & SGIMC_SYSID_MASKREV) >= 5 ? 24 : 22);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ get_bank_size(अचिन्हित पूर्णांक memconfig)
अणु
	वापस ((memconfig & SGIMC_MCONFIG_RMASK) + 0x0100) << ((sgimc->प्रणालीid & SGIMC_SYSID_MASKREV) >= 5 ? 16 : 14);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक get_bank_config(पूर्णांक bank)
अणु
	अचिन्हित पूर्णांक res = bank > 1 ? sgimc->mconfig1 : sgimc->mconfig0;
	वापस bank % 2 ? res & 0xffff : res >> 16;
पूर्ण

#अगर defined(CONFIG_SGI_IP28) || defined(CONFIG_32BIT)
अटल व्योम __init probe_memory(व्योम)
अणु
	/* prom detects all usable memory */
पूर्ण
#अन्यथा
/*
 * Detect installed memory, which PROM misses
 */
अटल व्योम __init probe_memory(व्योम)
अणु
	अचिन्हित दीर्घ addr, size;
	पूर्णांक i;

	prपूर्णांकk(KERN_INFO "MC: Probing memory configuration:\n");
	क्रम (i = 0; i < 4; i++) अणु
		अचिन्हित पूर्णांक पंचांगp = get_bank_config(i);
		अगर (!(पंचांगp & SGIMC_MCONFIG_BVALID))
			जारी;

		size = get_bank_size(पंचांगp);
		addr = get_bank_addr(पंचांगp);
		prपूर्णांकk(KERN_INFO " bank%d: %3ldM @ %08lx\n",
			i, size / 1024 / 1024, addr);

		अगर (addr >= SGIMC_SEG1_BADDR)
			memblock_add(addr, size);
	पूर्ण
पूर्ण
#पूर्ण_अगर

व्योम __init sgimc_init(व्योम)
अणु
	u32 पंचांगp;

	/* ioremap can't fail */
	sgimc = (काष्ठा sgimc_regs *)
		ioremap(SGIMC_BASE, माप(काष्ठा sgimc_regs));

	prपूर्णांकk(KERN_INFO "MC: SGI memory controller Revision %d\n",
	       (पूर्णांक) sgimc->प्रणालीid & SGIMC_SYSID_MASKREV);

	/* Place the MC पूर्णांकo a known state.  This must be करोne beक्रमe
	 * पूर्णांकerrupts are first enabled etc.
	 */

	/* Step 0: Make sure we turn off the watchकरोg in हाल it's
	 *	   still running (which might be the हाल after a
	 *	   soft reboot).
	 */
	पंचांगp = sgimc->cpuctrl0;
	पंचांगp &= ~SGIMC_CCTRL0_WDOG;
	sgimc->cpuctrl0 = पंचांगp;

	/* Step 1: The CPU/GIO error status रेजिस्टरs will not latch
	 *	   up a new error status until the रेजिस्टर has been
	 *	   cleared by the cpu.	These status रेजिस्टरs are
	 *	   cleared by writing any value to them.
	 */
	sgimc->cstat = sgimc->gstat = 0;

	/* Step 2: Enable all parity checking in cpu control रेजिस्टर
	 *	   zero.
	 */
	/* करोn't touch parity settings क्रम IP28 */
	पंचांगp = sgimc->cpuctrl0;
#अगर_अघोषित CONFIG_SGI_IP28
	पंचांगp |= SGIMC_CCTRL0_EPERRGIO | SGIMC_CCTRL0_EPERRMEM;
#पूर्ण_अगर
	पंचांगp |= SGIMC_CCTRL0_R4KNOCHKPARR;
	sgimc->cpuctrl0 = पंचांगp;

	/* Step 3: Setup the MC ग_लिखो buffer depth, this is controlled
	 *	   in cpu control रेजिस्टर 1 in the lower 4 bits.
	 */
	पंचांगp = sgimc->cpuctrl1;
	पंचांगp &= ~0xf;
	पंचांगp |= 0xd;
	sgimc->cpuctrl1 = पंचांगp;

	/* Step 4: Initialize the RPSS भागider रेजिस्टर to run as fast
	 *	   as it can correctly operate.	 The रेजिस्टर is laid
	 *	   out as follows:
	 *
	 *	   ----------------------------------------
	 *	   |  RESERVED	|   INCREMENT	| DIVIDER |
	 *	   ----------------------------------------
	 *	    31	      16 15	       8 7	 0
	 *
	 *	   DIVIDER determines how often a 'tick' happens,
	 *	   INCREMENT determines by how the RPSS increment
	 *	   रेजिस्टरs value increases at each 'tick'. Thus,
	 *	   क्रम IP22 we get INCREMENT=1, DIVIDER=1 == 0x101
	 */
	sgimc->भागider = 0x101;

	/* Step 5: Initialize GIO64 arbitrator configuration रेजिस्टर.
	 *
	 * NOTE: HPC init code in sgihpc_init() must run beक्रमe us because
	 *	 we need to know Guiness vs. FullHouse and the board
	 *	 revision on this machine. You have been warned.
	 */

	/* First the basic invariants across all GIO64 implementations. */
	पंचांगp = sgimc->giopar & SGIMC_GIOPAR_GFX64; /* keep gfx 64bit settings */
	पंचांगp |= SGIMC_GIOPAR_HPC64;	/* All 1st HPC's पूर्णांकerface at 64bits */
	पंचांगp |= SGIMC_GIOPAR_ONEBUS;	/* Only one physical GIO bus exists */

	अगर (ip22_is_fullhouse()) अणु
		/* Fullhouse specअगरic settings. */
		अगर (SGIOC_SYSID_BOARDREV(sgioc->sysid) < 2) अणु
			पंचांगp |= SGIMC_GIOPAR_HPC264;	/* 2nd HPC at 64bits */
			पंचांगp |= SGIMC_GIOPAR_PLINEEXP0;	/* exp0 pipelines */
			पंचांगp |= SGIMC_GIOPAR_MASTEREXP1; /* exp1 masters */
			पंचांगp |= SGIMC_GIOPAR_RTIMEEXP0;	/* exp0 is realसमय */
		पूर्ण अन्यथा अणु
			पंचांगp |= SGIMC_GIOPAR_HPC264;	/* 2nd HPC 64bits */
			पंचांगp |= SGIMC_GIOPAR_PLINEEXP0;	/* exp[01] pipelined */
			पंचांगp |= SGIMC_GIOPAR_PLINEEXP1;
			पंचांगp |= SGIMC_GIOPAR_MASTEREISA; /* EISA masters */
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Guiness specअगरic settings. */
		पंचांगp |= SGIMC_GIOPAR_EISA64;	/* MC talks to EISA at 64bits */
		पंचांगp |= SGIMC_GIOPAR_MASTEREISA; /* EISA bus can act as master */
	पूर्ण
	sgimc->giopar = पंचांगp;	/* poof */

	probe_memory();
पूर्ण

#अगर_घोषित CONFIG_SGI_IP28
व्योम __init prom_cleanup(व्योम)
अणु
	u32 mconfig1;
	अचिन्हित दीर्घ flags;
	spinlock_t lock;

	/*
	 * because ARCS accesses memory uncached we रुको until ARCS
	 * isn't needed any दीर्घer, beक्रमe we चयन from slow to
	 * normal mode
	 */
	spin_lock_irqsave(&lock, flags);
	mconfig1 = sgimc->mconfig1;
	/* map ECC रेजिस्टर */
	sgimc->mconfig1 = (mconfig1 & 0xffff0000) | 0x2060;
	iob();
	/* चयन to normal mode */
	*(अचिन्हित दीर्घ *)PHYS_TO_XKSEG_UNCACHED(0x60000000) = 0;
	iob();
	/* reduce WR_COL */
	sgimc->cmacc = (sgimc->cmacc & ~0xf) | 4;
	iob();
	/* restore old config */
	sgimc->mconfig1 = mconfig1;
	iob();
	spin_unlock_irqrestore(&lock, flags);
पूर्ण
#पूर्ण_अगर
