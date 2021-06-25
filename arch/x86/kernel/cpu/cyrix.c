<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <यंत्र/dma.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/processor-cyrix.h>
#समावेश <यंत्र/processor-flags.h>
#समावेश <linux/समयr.h>
#समावेश <यंत्र/pci-direct.h>
#समावेश <यंत्र/tsc.h>
#समावेश <यंत्र/cpufeature.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/घड़ी.h>

#समावेश "cpu.h"

/*
 * Read NSC/Cyrix DEVID रेजिस्टरs (सूची) to get more detailed info. about the CPU
 */
अटल व्योम __करो_cyrix_devid(अचिन्हित अक्षर *dir0, अचिन्हित अक्षर *dir1)
अणु
	अचिन्हित अक्षर ccr2, ccr3;

	/* we test क्रम DEVID by checking whether CCR3 is writable */
	ccr3 = getCx86(CX86_CCR3);
	setCx86(CX86_CCR3, ccr3 ^ 0x80);
	getCx86(0xc0);   /* dummy to change bus */

	अगर (getCx86(CX86_CCR3) == ccr3) अणु       /* no DEVID regs. */
		ccr2 = getCx86(CX86_CCR2);
		setCx86(CX86_CCR2, ccr2 ^ 0x04);
		getCx86(0xc0);  /* dummy */

		अगर (getCx86(CX86_CCR2) == ccr2) /* old Cx486SLC/DLC */
			*dir0 = 0xfd;
		अन्यथा अणु                          /* Cx486S A step */
			setCx86(CX86_CCR2, ccr2);
			*dir0 = 0xfe;
		पूर्ण
	पूर्ण अन्यथा अणु
		setCx86(CX86_CCR3, ccr3);  /* restore CCR3 */

		/* पढ़ो सूची0 and सूची1 CPU रेजिस्टरs */
		*dir0 = getCx86(CX86_सूची0);
		*dir1 = getCx86(CX86_सूची1);
	पूर्ण
पूर्ण

अटल व्योम करो_cyrix_devid(अचिन्हित अक्षर *dir0, अचिन्हित अक्षर *dir1)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	__करो_cyrix_devid(dir0, dir1);
	local_irq_restore(flags);
पूर्ण
/*
 * Cx86_dir0_msb is a HACK needed by check_cx686_cpuid/slop in bugs.h in
 * order to identअगरy the Cyrix CPU model after we're out of setup.c
 *
 * Actually since bugs.h करोesn't even reference this perhaps someone should
 * fix the करोcumentation ???
 */
अटल अचिन्हित अक्षर Cx86_dir0_msb = 0;

अटल स्थिर अक्षर Cx86_model[][9] = अणु
	"Cx486", "Cx486", "5x86 ", "6x86", "MediaGX ", "6x86MX ",
	"M II ", "Unknown"
पूर्ण;
अटल स्थिर अक्षर Cx486_name[][5] = अणु
	"SLC", "DLC", "SLC2", "DLC2", "SRx", "DRx",
	"SRx2", "DRx2"
पूर्ण;
अटल स्थिर अक्षर Cx486S_name[][4] = अणु
	"S", "S2", "Se", "S2e"
पूर्ण;
अटल स्थिर अक्षर Cx486D_name[][4] = अणु
	"DX", "DX2", "?", "?", "?", "DX4"
पूर्ण;
अटल अक्षर Cx86_cb[] = "?.5x Core/Bus Clock";
अटल स्थिर अक्षर cyrix_model_mult1[] = "12??43";
अटल स्थिर अक्षर cyrix_model_mult2[] = "12233445";

/*
 * Reset the slow-loop (SLOP) bit on the 686(L) which is set by some old
 * BIOSes क्रम compatibility with DOS games.  This makes the udelay loop
 * work correctly, and improves perक्रमmance.
 *
 * FIXME: our newer udelay uses the tsc. We करोn't need to frob with SLOP
 */

अटल व्योम check_cx686_slop(काष्ठा cpuinfo_x86 *c)
अणु
	अचिन्हित दीर्घ flags;

	अगर (Cx86_dir0_msb == 3) अणु
		अचिन्हित अक्षर ccr3, ccr5;

		local_irq_save(flags);
		ccr3 = getCx86(CX86_CCR3);
		setCx86(CX86_CCR3, (ccr3 & 0x0f) | 0x10); /* enable MAPEN */
		ccr5 = getCx86(CX86_CCR5);
		अगर (ccr5 & 2)
			setCx86(CX86_CCR5, ccr5 & 0xfd);  /* reset SLOP */
		setCx86(CX86_CCR3, ccr3);                 /* disable MAPEN */
		local_irq_restore(flags);

		अगर (ccr5 & 2) अणु /* possible wrong calibration करोne */
			pr_info("Recalibrating delay loop with SLOP bit reset\n");
			calibrate_delay();
			c->loops_per_jअगरfy = loops_per_jअगरfy;
		पूर्ण
	पूर्ण
पूर्ण


अटल व्योम set_cx86_reorder(व्योम)
अणु
	u8 ccr3;

	pr_info("Enable Memory access reorder on Cyrix/NSC processor.\n");
	ccr3 = getCx86(CX86_CCR3);
	setCx86(CX86_CCR3, (ccr3 & 0x0f) | 0x10); /* enable MAPEN */

	/* Load/Store Serialize to mem access disable (=reorder it) */
	setCx86(CX86_PCR0, getCx86(CX86_PCR0) & ~0x80);
	/* set load/store serialize from 1GB to 4GB */
	ccr3 |= 0xe0;
	setCx86(CX86_CCR3, ccr3);
पूर्ण

अटल व्योम set_cx86_memwb(व्योम)
अणु
	pr_info("Enable Memory-Write-back mode on Cyrix/NSC processor.\n");

	/* CCR2 bit 2: unlock NW bit */
	setCx86(CX86_CCR2, getCx86(CX86_CCR2) & ~0x04);
	/* set 'Not Write-through' */
	ग_लिखो_cr0(पढ़ो_cr0() | X86_CR0_NW);
	/* CCR2 bit 2: lock NW bit and set WT1 */
	setCx86(CX86_CCR2, getCx86(CX86_CCR2) | 0x14);
पूर्ण

/*
 *	Configure later MediaGX and/or Geode processor.
 */

अटल व्योम geode_configure(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	u8 ccr3;
	local_irq_save(flags);

	/* Suspend on halt घातer saving and enable #SUSP pin */
	setCx86(CX86_CCR2, getCx86(CX86_CCR2) | 0x88);

	ccr3 = getCx86(CX86_CCR3);
	setCx86(CX86_CCR3, (ccr3 & 0x0f) | 0x10);	/* enable MAPEN */


	/* FPU fast, DTE cache, Mem bypass */
	setCx86(CX86_CCR4, getCx86(CX86_CCR4) | 0x38);
	setCx86(CX86_CCR3, ccr3);			/* disable MAPEN */

	set_cx86_memwb();
	set_cx86_reorder();

	local_irq_restore(flags);
पूर्ण

अटल व्योम early_init_cyrix(काष्ठा cpuinfo_x86 *c)
अणु
	अचिन्हित अक्षर dir0, dir0_msn, dir1 = 0;

	__करो_cyrix_devid(&dir0, &dir1);
	dir0_msn = dir0 >> 4; /* identअगरies CPU "family"   */

	चयन (dir0_msn) अणु
	हाल 3: /* 6x86/6x86L */
		/* Emulate MTRRs using Cyrix's ARRs. */
		set_cpu_cap(c, X86_FEATURE_CYRIX_ARR);
		अवरोध;
	हाल 5: /* 6x86MX/M II */
		/* Emulate MTRRs using Cyrix's ARRs. */
		set_cpu_cap(c, X86_FEATURE_CYRIX_ARR);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम init_cyrix(काष्ठा cpuinfo_x86 *c)
अणु
	अचिन्हित अक्षर dir0, dir0_msn, dir0_lsn, dir1 = 0;
	अक्षर *buf = c->x86_model_id;
	स्थिर अक्षर *p = शून्य;

	/*
	 * Bit 31 in normal CPUID used क्रम nonstandard 3DNow ID;
	 * 3DNow is IDd by bit 31 in extended CPUID (1*32+31) anyway
	 */
	clear_cpu_cap(c, 0*32+31);

	/* Cyrix used bit 24 in extended (AMD) CPUID क्रम Cyrix MMX extensions */
	अगर (test_cpu_cap(c, 1*32+24)) अणु
		clear_cpu_cap(c, 1*32+24);
		set_cpu_cap(c, X86_FEATURE_CXMMX);
	पूर्ण

	करो_cyrix_devid(&dir0, &dir1);

	check_cx686_slop(c);

	Cx86_dir0_msb = dir0_msn = dir0 >> 4; /* identअगरies CPU "family"   */
	dir0_lsn = dir0 & 0xf;                /* model or घड़ी multiplier */

	/* common हाल step number/rev -- exceptions handled below */
	c->x86_model = (dir1 >> 4) + 1;
	c->x86_stepping = dir1 & 0xf;

	/* Now cook; the original recipe is by Channing Corn, from Cyrix.
	 * We करो the same thing क्रम each generation: we work out
	 * the model, multiplier and stepping.  Black magic included,
	 * to make the silicon step/rev numbers match the prपूर्णांकed ones.
	 */

	चयन (dir0_msn) अणु
		अचिन्हित अक्षर पंचांगp;

	हाल 0: /* Cx486SLC/DLC/SRx/DRx */
		p = Cx486_name[dir0_lsn & 7];
		अवरोध;

	हाल 1: /* Cx486S/DX/DX2/DX4 */
		p = (dir0_lsn & 8) ? Cx486D_name[dir0_lsn & 5]
			: Cx486S_name[dir0_lsn & 3];
		अवरोध;

	हाल 2: /* 5x86 */
		Cx86_cb[2] = cyrix_model_mult1[dir0_lsn & 5];
		p = Cx86_cb+2;
		अवरोध;

	हाल 3: /* 6x86/6x86L */
		Cx86_cb[1] = ' ';
		Cx86_cb[2] = cyrix_model_mult1[dir0_lsn & 5];
		अगर (dir1 > 0x21) अणु /* 686L */
			Cx86_cb[0] = 'L';
			p = Cx86_cb;
			(c->x86_model)++;
		पूर्ण अन्यथा             /* 686 */
			p = Cx86_cb+1;
		/* Emulate MTRRs using Cyrix's ARRs. */
		set_cpu_cap(c, X86_FEATURE_CYRIX_ARR);
		/* 6x86's contain this bug */
		set_cpu_bug(c, X86_BUG_COMA);
		अवरोध;

	हाल 4: /* MediaGX/GXm or Geode GXM/GXLV/GX1 */
	हाल 11: /* GX1 with inverted Device ID */
#अगर_घोषित CONFIG_PCI
	अणु
		u32 venकरोr, device;
		/*
		 * It isn't really a PCI quirk directly, but the cure is the
		 * same. The MediaGX has deep magic SMM stuff that handles the
		 * SB emulation. It throws away the fअगरo on disable_dma() which
		 * is wrong and ruins the audio.
		 *
		 *  Bug2: VSA1 has a wrap bug so that using maximum sized DMA
		 *  causes bad things. According to NatSemi VSA2 has another
		 *  bug to करो with 'hlt'. I've not seen any boards using VSA2
		 *  and X करोesn't seem to support it either so who cares 8).
		 *  VSA1 we work around however.
		 */

		pr_info("Working around Cyrix MediaGX virtual DMA bugs.\n");
		isa_dma_bridge_buggy = 2;

		/* We करो this beक्रमe the PCI layer is running. However we
		   are safe here as we know the bridge must be a Cyrix
		   companion and must be present */
		venकरोr = पढ़ो_pci_config_16(0, 0, 0x12, PCI_VENDOR_ID);
		device = पढ़ो_pci_config_16(0, 0, 0x12, PCI_DEVICE_ID);

		/*
		 *  The 5510/5520 companion chips have a funky PIT.
		 */
		अगर (venकरोr == PCI_VENDOR_ID_CYRIX &&
			(device == PCI_DEVICE_ID_CYRIX_5510 ||
					device == PCI_DEVICE_ID_CYRIX_5520))
			mark_tsc_unstable("cyrix 5510/5520 detected");
	पूर्ण
#पूर्ण_अगर
		c->x86_cache_size = 16;	/* Yep 16K पूर्णांकegrated cache that's it */

		/* GXm supports extended cpuid levels 'ala' AMD */
		अगर (c->cpuid_level == 2) अणु
			/* Enable cxMMX extensions (GX1 Datasheet 54) */
			setCx86(CX86_CCR7, getCx86(CX86_CCR7) | 1);

			/*
			 * GXm : 0x30 ... 0x5f GXm  datasheet 51
			 * GXlv: 0x6x          GXlv datasheet 54
			 *  ?  : 0x7x
			 * GX1 : 0x8x          GX1  datasheet 56
			 */
			अगर ((0x30 <= dir1 && dir1 <= 0x6f) ||
					(0x80 <= dir1 && dir1 <= 0x8f))
				geode_configure();
			वापस;
		पूर्ण अन्यथा अणु /* MediaGX */
			Cx86_cb[2] = (dir0_lsn & 1) ? '3' : '4';
			p = Cx86_cb+2;
			c->x86_model = (dir1 & 0x20) ? 1 : 2;
		पूर्ण
		अवरोध;

	हाल 5: /* 6x86MX/M II */
		अगर (dir1 > 7) अणु
			dir0_msn++;  /* M II */
			/* Enable MMX extensions (App note 108) */
			setCx86(CX86_CCR7, getCx86(CX86_CCR7)|1);
		पूर्ण अन्यथा अणु
			/* A 6x86MX - it has the bug. */
			set_cpu_bug(c, X86_BUG_COMA);
		पूर्ण
		पंचांगp = (!(dir0_lsn & 7) || dir0_lsn & 1) ? 2 : 0;
		Cx86_cb[पंचांगp] = cyrix_model_mult2[dir0_lsn & 7];
		p = Cx86_cb+पंचांगp;
		अगर (((dir1 & 0x0f) > 4) || ((dir1 & 0xf0) == 0x20))
			(c->x86_model)++;
		/* Emulate MTRRs using Cyrix's ARRs. */
		set_cpu_cap(c, X86_FEATURE_CYRIX_ARR);
		अवरोध;

	हाल 0xf:  /* Cyrix 486 without DEVID रेजिस्टरs */
		चयन (dir0_lsn) अणु
		हाल 0xd:  /* either a 486SLC or DLC w/o DEVID */
			dir0_msn = 0;
			p = Cx486_name[!!boot_cpu_has(X86_FEATURE_FPU)];
			अवरोध;

		हाल 0xe:  /* a 486S A step */
			dir0_msn = 0;
			p = Cx486S_name[0];
			अवरोध;
		पूर्ण
		अवरोध;

	शेष:  /* unknown (shouldn't happen, we know everyone ;-) */
		dir0_msn = 7;
		अवरोध;
	पूर्ण
	म_नकल(buf, Cx86_model[dir0_msn & 7]);
	अगर (p)
		म_जोड़ो(buf, p);
	वापस;
पूर्ण

/*
 * Handle National Semiconductor bअक्रमed processors
 */
अटल व्योम init_nsc(काष्ठा cpuinfo_x86 *c)
अणु
	/*
	 * There may be GX1 processors in the wild that are bअक्रमed
	 * NSC and not Cyrix.
	 *
	 * This function only handles the GX processor, and kicks every
	 * thing अन्यथा to the Cyrix init function above - that should
	 * cover any processors that might have been bअक्रमed dअगरferently
	 * after NSC acquired Cyrix.
	 *
	 * If this अवरोधs your GX1 horribly, please e-mail
	 * info-linux@ldcmail.amd.com to tell us.
	 */

	/* Handle the GX (Formally known as the GX2) */

	अगर (c->x86 == 5 && c->x86_model == 5)
		cpu_detect_cache_sizes(c);
	अन्यथा
		init_cyrix(c);
पूर्ण

/*
 * Cyrix CPUs without cpuid or with cpuid not yet enabled can be detected
 * by the fact that they preserve the flags across the भागision of 5/2.
 * PII and PPro exhibit this behavior too, but they have cpuid available.
 */

/*
 * Perक्रमm the Cyrix 5/2 test. A Cyrix won't change
 * the flags, जबतक other 486 chips will.
 */
अटल अंतरभूत पूर्णांक test_cyrix_52भाग(व्योम)
अणु
	अचिन्हित पूर्णांक test;

	__यंत्र__ __अस्थिर__(
	     "sahf\n\t"		/* clear flags (%eax = 0x0005) */
	     "div %b2\n\t"	/* भागide 5 by 2 */
	     "lahf"		/* store flags पूर्णांकo %ah */
	     : "=a" (test)
	     : "0" (5), "q" (2)
	     : "cc");

	/* AH is 0x02 on Cyrix after the भागide.. */
	वापस (अचिन्हित अक्षर) (test >> 8) == 0x02;
पूर्ण

अटल व्योम cyrix_identअगरy(काष्ठा cpuinfo_x86 *c)
अणु
	/* Detect Cyrix with disabled CPUID */
	अगर (c->x86 == 4 && test_cyrix_52भाग()) अणु
		अचिन्हित अक्षर dir0, dir1;

		म_नकल(c->x86_venकरोr_id, "CyrixInstead");
		c->x86_venकरोr = X86_VENDOR_CYRIX;

		/* Actually enable cpuid on the older cyrix */

		/* Retrieve CPU revisions */

		करो_cyrix_devid(&dir0, &dir1);

		dir0 >>= 4;

		/* Check it is an affected model */

		अगर (dir0 == 5 || dir0 == 3) अणु
			अचिन्हित अक्षर ccr3;
			अचिन्हित दीर्घ flags;
			pr_info("Enabling CPUID on Cyrix processor.\n");
			local_irq_save(flags);
			ccr3 = getCx86(CX86_CCR3);
			/* enable MAPEN  */
			setCx86(CX86_CCR3, (ccr3 & 0x0f) | 0x10);
			/* enable cpuid  */
			setCx86(CX86_CCR4, getCx86(CX86_CCR4) | 0x80);
			/* disable MAPEN */
			setCx86(CX86_CCR3, ccr3);
			local_irq_restore(flags);
		पूर्ण
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा cpu_dev cyrix_cpu_dev = अणु
	.c_venकरोr	= "Cyrix",
	.c_ident	= अणु "CyrixInstead" पूर्ण,
	.c_early_init	= early_init_cyrix,
	.c_init		= init_cyrix,
	.c_identअगरy	= cyrix_identअगरy,
	.c_x86_venकरोr	= X86_VENDOR_CYRIX,
पूर्ण;

cpu_dev_रेजिस्टर(cyrix_cpu_dev);

अटल स्थिर काष्ठा cpu_dev nsc_cpu_dev = अणु
	.c_venकरोr	= "NSC",
	.c_ident	= अणु "Geode by NSC" पूर्ण,
	.c_init		= init_nsc,
	.c_x86_venकरोr	= X86_VENDOR_NSC,
पूर्ण;

cpu_dev_रेजिस्टर(nsc_cpu_dev);
