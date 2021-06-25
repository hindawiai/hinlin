<शैली गुरु>
/*
 *  linux/arch/m68k/atari/config.c
 *
 *  Copyright (C) 1994 Bjoern Brauel
 *
 *  5/2/94 Roman Hodek:
 *    Added setting of समय_adj to get a better घड़ी.
 *
 *  5/14/94 Roman Hodek:
 *    gettod() क्रम TT
 *
 *  5/15/94 Roman Hodek:
 *    hard_reset_now() क्रम Atari (and others?)
 *
 *  94/12/30 Andreas Schwab:
 *    atari_sched_init fixed to get precise घड़ी.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

/*
 * Miscellaneous atari stuff
 */

#समावेश <linux/types.h>
#समावेश <linux/mm.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/console.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/ioport.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/usb/isp116x.h>
#समावेश <linux/vt_kern.h>
#समावेश <linux/module.h>

#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/bootinfo-atari.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/atarihw.h>
#समावेश <यंत्र/atariपूर्णांकs.h>
#समावेश <यंत्र/atari_stram.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/hwtest.h>
#समावेश <यंत्र/पन.स>

u_दीर्घ atari_mch_cookie;
EXPORT_SYMBOL(atari_mch_cookie);

u_दीर्घ atari_mch_type;
EXPORT_SYMBOL(atari_mch_type);

काष्ठा atari_hw_present atari_hw_present;
EXPORT_SYMBOL(atari_hw_present);

u_दीर्घ atari_चयनes;
EXPORT_SYMBOL(atari_चयनes);

पूर्णांक atari_करोnt_touch_floppy_select;
EXPORT_SYMBOL(atari_करोnt_touch_floppy_select);

पूर्णांक atari_rtc_year_offset;

/* local function prototypes */
अटल व्योम atari_reset(व्योम);
अटल व्योम atari_get_model(अक्षर *model);
अटल व्योम atari_get_hardware_list(काष्ठा seq_file *m);

/* atari specअगरic irq functions */
बाह्य व्योम atari_init_IRQ (व्योम);
बाह्य व्योम atari_mksound(अचिन्हित पूर्णांक count, अचिन्हित पूर्णांक ticks);
#अगर_घोषित CONFIG_HEARTBEAT
अटल व्योम atari_heartbeat(पूर्णांक on);
#पूर्ण_अगर

/* atari specअगरic समयr functions (in समय.c) */
बाह्य व्योम atari_sched_init(व्योम);
बाह्य पूर्णांक atari_mste_hwclk (पूर्णांक, काष्ठा rtc_समय *);
बाह्य पूर्णांक atari_tt_hwclk (पूर्णांक, काष्ठा rtc_समय *);

/* ++roman: This is a more elaborate test क्रम an SCC chip, since the plain
 * Medusa board generates DTACK at the SCC's standard addresses, but a SCC
 * board in the Medusa is possible. Also, the addresses where the ST_ESCC
 * resides generate DTACK without the chip, too.
 * The method is to ग_लिखो values पूर्णांकo the पूर्णांकerrupt vector रेजिस्टर, that
 * should be पढ़ोable without trouble (from channel A!).
 */

अटल पूर्णांक __init scc_test(अस्थिर अक्षर *ctla)
अणु
	अगर (!hwreg_present(ctla))
		वापस 0;
	MFPDELAY();

	*ctla = 2;
	MFPDELAY();
	*ctla = 0x40;
	MFPDELAY();

	*ctla = 2;
	MFPDELAY();
	अगर (*ctla != 0x40)
		वापस 0;
	MFPDELAY();

	*ctla = 2;
	MFPDELAY();
	*ctla = 0x60;
	MFPDELAY();

	*ctla = 2;
	MFPDELAY();
	अगर (*ctla != 0x60)
		वापस 0;

	वापस 1;
पूर्ण


    /*
     *  Parse an Atari-specअगरic record in the bootinfo
     */

पूर्णांक __init atari_parse_bootinfo(स्थिर काष्ठा bi_record *record)
अणु
	पूर्णांक unknown = 0;
	स्थिर व्योम *data = record->data;

	चयन (be16_to_cpu(record->tag)) अणु
	हाल BI_ATARI_MCH_COOKIE:
		atari_mch_cookie = be32_to_cpup(data);
		अवरोध;
	हाल BI_ATARI_MCH_TYPE:
		atari_mch_type = be32_to_cpup(data);
		अवरोध;
	शेष:
		unknown = 1;
		अवरोध;
	पूर्ण
	वापस unknown;
पूर्ण


/* Parse the Atari-specअगरic चयनes= option. */
अटल पूर्णांक __init atari_चयनes_setup(अक्षर *str)
अणु
	अक्षर चयनes[COMMAND_LINE_SIZE];
	अक्षर *p;
	पूर्णांक ovsc_shअगरt;
	अक्षर *args = चयनes;

	अगर (!MACH_IS_ATARI)
		वापस 0;

	/* copy string to local array, strsep works deकाष्ठाively... */
	म_नकल(चयनes, str);
	atari_चयनes = 0;

	/* parse the options */
	जबतक ((p = strsep(&args, ",")) != शून्य) अणु
		अगर (!*p)
			जारी;
		ovsc_shअगरt = 0;
		अगर (म_भेदन(p, "ov_", 3) == 0) अणु
			p += 3;
			ovsc_shअगरt = ATARI_SWITCH_OVSC_SHIFT;
		पूर्ण

		अगर (म_भेद(p, "ikbd") == 0) अणु
			/* RTS line of IKBD ACIA */
			atari_चयनes |= ATARI_SWITCH_IKBD << ovsc_shअगरt;
		पूर्ण अन्यथा अगर (म_भेद(p, "midi") == 0) अणु
			/* RTS line of MIDI ACIA */
			atari_चयनes |= ATARI_SWITCH_MIDI << ovsc_shअगरt;
		पूर्ण अन्यथा अगर (म_भेद(p, "snd6") == 0) अणु
			atari_चयनes |= ATARI_SWITCH_SND6 << ovsc_shअगरt;
		पूर्ण अन्यथा अगर (म_भेद(p, "snd7") == 0) अणु
			atari_चयनes |= ATARI_SWITCH_SND7 << ovsc_shअगरt;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

early_param("switches", atari_चयनes_setup);


    /*
     *  Setup the Atari configuration info
     */

व्योम __init config_atari(व्योम)
अणु
	अचिन्हित लघु tos_version;

	स_रखो(&atari_hw_present, 0, माप(atari_hw_present));

	/* Change size of I/O space from 64KB to 4GB. */
	ioport_resource.end  = 0xFFFFFFFF;

	mach_sched_init      = atari_sched_init;
	mach_init_IRQ        = atari_init_IRQ;
	mach_get_model	 = atari_get_model;
	mach_get_hardware_list = atari_get_hardware_list;
	mach_reset           = atari_reset;
#अगर IS_ENABLED(CONFIG_INPUT_M68K_BEEP)
	mach_beep          = atari_mksound;
#पूर्ण_अगर
#अगर_घोषित CONFIG_HEARTBEAT
	mach_heartbeat = atari_heartbeat;
#पूर्ण_अगर

	/* Set चयनes as requested by the user */
	अगर (atari_चयनes & ATARI_SWITCH_IKBD)
		acia.key_ctrl = ACIA_DIV64 | ACIA_D8N1S | ACIA_RHTID;
	अगर (atari_चयनes & ATARI_SWITCH_MIDI)
		acia.mid_ctrl = ACIA_DIV16 | ACIA_D8N1S | ACIA_RHTID;
	अगर (atari_चयनes & (ATARI_SWITCH_SND6|ATARI_SWITCH_SND7)) अणु
		sound_ym.rd_data_reg_sel = 14;
		sound_ym.wd_data = sound_ym.rd_data_reg_sel |
				   ((atari_चयनes&ATARI_SWITCH_SND6) ? 0x40 : 0) |
				   ((atari_चयनes&ATARI_SWITCH_SND7) ? 0x80 : 0);
	पूर्ण

	/* ++bjoern:
	 * Determine hardware present
	 */

	pr_info("Atari hardware found:");
	अगर (MACH_IS_MEDUSA) अणु
		/* There's no Atari video hardware on the Medusa, but all the
		 * addresses below generate a DTACK so no bus error occurs! */
	पूर्ण अन्यथा अगर (hwreg_present(f030_xreg)) अणु
		ATARIHW_SET(VIDEL_SHIFTER);
		pr_cont(" VIDEL");
		/* This is a temporary hack: If there is Falcon video
		 * hardware, we assume that the ST-DMA serves SCSI instead of
		 * ACSI. In the future, there should be a better method क्रम
		 * this...
		 */
		ATARIHW_SET(ST_SCSI);
		pr_cont(" STDMA-SCSI");
	पूर्ण अन्यथा अगर (hwreg_present(tt_palette)) अणु
		ATARIHW_SET(TT_SHIFTER);
		pr_cont(" TT_SHIFTER");
	पूर्ण अन्यथा अगर (hwreg_present(&shअगरter_st.bas_hi)) अणु
		अगर (hwreg_present(&shअगरter_st.bas_lo) &&
		    (shअगरter_st.bas_lo = 0x0aau, shअगरter_st.bas_lo == 0x0aau)) अणु
			ATARIHW_SET(EXTD_SHIFTER);
			pr_cont(" EXTD_SHIFTER");
		पूर्ण अन्यथा अणु
			ATARIHW_SET(STND_SHIFTER);
			pr_cont(" STND_SHIFTER");
		पूर्ण
	पूर्ण
	अगर (hwreg_present(&st_mfp.par_dt_reg)) अणु
		ATARIHW_SET(ST_MFP);
		pr_cont(" ST_MFP");
	पूर्ण
	अगर (hwreg_present(&tt_mfp.par_dt_reg)) अणु
		ATARIHW_SET(TT_MFP);
		pr_cont(" TT_MFP");
	पूर्ण
	अगर (hwreg_present(&tt_scsi_dma.dma_addr_hi)) अणु
		ATARIHW_SET(SCSI_DMA);
		pr_cont(" TT_SCSI_DMA");
	पूर्ण
	/*
	 * The ST-DMA address रेजिस्टरs aren't पढ़ोable
	 * on all Medusas, so the test below may fail
	 */
	अगर (MACH_IS_MEDUSA ||
	    (hwreg_present(&st_dma.dma_vhi) &&
	     (st_dma.dma_vhi = 0x55) && (st_dma.dma_hi = 0xaa) &&
	     st_dma.dma_vhi == 0x55 && st_dma.dma_hi == 0xaa &&
	     (st_dma.dma_vhi = 0xaa) && (st_dma.dma_hi = 0x55) &&
	     st_dma.dma_vhi == 0xaa && st_dma.dma_hi == 0x55)) अणु
		ATARIHW_SET(EXTD_DMA);
		pr_cont(" EXTD_DMA");
	पूर्ण
	अगर (hwreg_present(&tt_scsi.scsi_data)) अणु
		ATARIHW_SET(TT_SCSI);
		pr_cont(" TT_SCSI");
	पूर्ण
	अगर (hwreg_present(&sound_ym.rd_data_reg_sel)) अणु
		ATARIHW_SET(YM_2149);
		pr_cont(" YM2149");
	पूर्ण
	अगर (!MACH_IS_MEDUSA && hwreg_present(&tt_dmasnd.ctrl)) अणु
		ATARIHW_SET(PCM_8BIT);
		pr_cont(" PCM");
	पूर्ण
	अगर (hwreg_present(&falcon_codec.unused5)) अणु
		ATARIHW_SET(CODEC);
		pr_cont(" CODEC");
	पूर्ण
	अगर (hwreg_present(&dsp56k_host_पूर्णांकerface.icr)) अणु
		ATARIHW_SET(DSP56K);
		pr_cont(" DSP56K");
	पूर्ण
	अगर (hwreg_present(&tt_scc_dma.dma_ctrl) &&
#अगर 0
	    /* This test sucks! Who knows some better? */
	    (tt_scc_dma.dma_ctrl = 0x01, (tt_scc_dma.dma_ctrl & 1) == 1) &&
	    (tt_scc_dma.dma_ctrl = 0x00, (tt_scc_dma.dma_ctrl & 1) == 0)
#अन्यथा
	    !MACH_IS_MEDUSA
#पूर्ण_अगर
	    ) अणु
		ATARIHW_SET(SCC_DMA);
		pr_cont(" SCC_DMA");
	पूर्ण
	अगर (scc_test(&atari_scc.cha_a_ctrl)) अणु
		ATARIHW_SET(SCC);
		pr_cont(" SCC");
	पूर्ण
	अगर (scc_test(&st_escc.cha_b_ctrl)) अणु
		ATARIHW_SET(ST_ESCC);
		pr_cont(" ST_ESCC");
	पूर्ण
	अगर (hwreg_present(&tt_scu.sys_mask)) अणु
		ATARIHW_SET(SCU);
		/* Assume a VME bus अगर there's a SCU */
		ATARIHW_SET(VME);
		pr_cont(" VME SCU");
	पूर्ण
	अगर (hwreg_present((व्योम *)(0xffff9210))) अणु
		ATARIHW_SET(ANALOG_JOY);
		pr_cont(" ANALOG_JOY");
	पूर्ण
	अगर (hwreg_present(blitter.halftone)) अणु
		ATARIHW_SET(BLITTER);
		pr_cont(" BLITTER");
	पूर्ण
	अगर (hwreg_present((व्योम *)0xfff00039)) अणु
		ATARIHW_SET(IDE);
		pr_cont(" IDE");
	पूर्ण
#अगर 1 /* This maybe wrong */
	अगर (!MACH_IS_MEDUSA && hwreg_present(&tt_microwire.data) &&
	    hwreg_present(&tt_microwire.mask) &&
	    (tt_microwire.mask = 0x7ff,
	     udelay(1),
	     tt_microwire.data = MW_LM1992_PSG_HIGH | MW_LM1992_ADDR,
	     udelay(1),
	     tt_microwire.data != 0)) अणु
		ATARIHW_SET(MICROWIRE);
		जबतक (tt_microwire.mask != 0x7ff)
			;
		pr_cont(" MICROWIRE");
	पूर्ण
#पूर्ण_अगर
	अगर (hwreg_present(&tt_rtc.regsel)) अणु
		ATARIHW_SET(TT_CLK);
		pr_cont(" TT_CLK");
		mach_hwclk = atari_tt_hwclk;
	पूर्ण
	अगर (hwreg_present(&mste_rtc.sec_ones)) अणु
		ATARIHW_SET(MSTE_CLK);
		pr_cont(" MSTE_CLK");
		mach_hwclk = atari_mste_hwclk;
	पूर्ण
	अगर (!MACH_IS_MEDUSA && hwreg_present(&dma_wd.fdc_speed) &&
	    hwreg_ग_लिखो(&dma_wd.fdc_speed, 0)) अणु
		ATARIHW_SET(FDCSPEED);
		pr_cont(" FDC_SPEED");
	पूर्ण
	अगर (!ATARIHW_PRESENT(ST_SCSI)) अणु
		ATARIHW_SET(ACSI);
		pr_cont(" ACSI");
	पूर्ण
	pr_cont("\n");

	अगर (CPU_IS_040_OR_060)
		/* Now it seems to be safe to turn of the tt0 transparent
		 * translation (the one that must not be turned off in
		 * head.S...)
		 */
		यंत्र अस्थिर ("\n"
			"	moveq	#0,%%d0\n"
			"	.chip	68040\n"
			"	movec	%%d0,%%itt0\n"
			"	movec	%%d0,%%dtt0\n"
			"	.chip	68k"
			: /* no outमाला_दो */
			: /* no inमाला_दो */
			: "d0");

	/* allocator क्रम memory that must reside in st-ram */
	atari_stram_init();

	/* Set up a mapping क्रम the VMEbus address region:
	 *
	 * VME is either at phys. 0xfexxxxxx (TT) or 0xa00000..0xdfffff
	 * (MegaSTE) In both हालs, the whole 16 MB chunk is mapped at
	 * 0xfe000000 virt., because this can be करोne with a single
	 * transparent translation. On the 68040, lots of often unused
	 * page tables would be needed otherwise. On a MegaSTE or similar,
	 * the highest byte is stripped off by hardware due to the 24 bit
	 * design of the bus.
	 */

	अगर (CPU_IS_020_OR_030) अणु
		अचिन्हित दीर्घ tt1_val;
		tt1_val = 0xfe008543;	/* Translate 0xfexxxxxx, enable, cache
					 * inhibit, पढ़ो and ग_लिखो, FDC mask = 3,
					 * FDC val = 4 -> Supervisor only */
		यंत्र अस्थिर ("\n"
			"	.chip	68030\n"
			"	pmove	%0,%/tt1\n"
			"	.chip	68k"
			: : "m" (tt1_val));
	पूर्ण अन्यथा अणु
	        यंत्र अस्थिर ("\n"
			"	.chip	68040\n"
			"	movec	%0,%%itt1\n"
			"	movec	%0,%%dtt1\n"
			"	.chip	68k"
			:
			: "d" (0xfe00a040));	/* Translate 0xfexxxxxx, enable,
						 * supervisor only, non-cacheable/
						 * serialized, writable */

	पूर्ण

	/* Fetch tos version at Physical 2 */
	/*
	 * We my not be able to access this address अगर the kernel is
	 * loaded to st ram, since the first page is unmapped.  On the
	 * Medusa this is always the हाल and there is nothing we can करो
	 * about this, so we just assume the smaller offset.  For the TT
	 * we use the fact that in head.S we have set up a mapping
	 * 0xFFxxxxxx -> 0x00xxxxxx, so that the first 16MB is accessible
	 * in the last 16MB of the address space.
	 */
	tos_version = (MACH_IS_MEDUSA) ?
			0xfff : *(अचिन्हित लघु *)0xff000002;
	atari_rtc_year_offset = (tos_version < 0x306) ? 70 : 68;
पूर्ण

#अगर_घोषित CONFIG_HEARTBEAT
अटल व्योम atari_heartbeat(पूर्णांक on)
अणु
	अचिन्हित अक्षर पंचांगp;
	अचिन्हित दीर्घ flags;

	अगर (atari_करोnt_touch_floppy_select)
		वापस;

	local_irq_save(flags);
	sound_ym.rd_data_reg_sel = 14;	/* Select PSG Port A */
	पंचांगp = sound_ym.rd_data_reg_sel;
	sound_ym.wd_data = on ? (पंचांगp & ~0x02) : (पंचांगp | 0x02);
	local_irq_restore(flags);
पूर्ण
#पूर्ण_अगर

/* ++roman:
 *
 * This function करोes a reset on machines that lack the ability to
 * निश्चित the processor's _RESET संकेत somehow via hardware. It is
 * based on the fact that you can find the initial SP and PC values
 * after a reset at physical addresses 0 and 4. This works pretty well
 * क्रम Atari machines, since the lowest 8 bytes of physical memory are
 * really ROM (mapped by hardware). For other 680x0 machines: करोn't
 * know अगर it works...
 *
 * To get the values at addresses 0 and 4, the MMU better is turned
 * off first. After that, we have to jump पूर्णांकo physical address space
 * (the PC beक्रमe the pmove statement poपूर्णांकs to the भव address of
 * the code). Getting that physical address is not hard, but the code
 * becomes a bit complex since I've tried to ensure that the jump
 * statement after the pmove is in the cache alपढ़ोy (otherwise the
 * processor can't fetch it!). For that, the code first jumps to the
 * jump statement with the (भव) address of the pmove section in
 * an address रेजिस्टर . The jump statement is surely in the cache
 * now. After that, that physical address of the reset code is loaded
 * पूर्णांकo the same address रेजिस्टर, pmove is करोne and the same jump
 * statements goes to the reset code. Since there are not many
 * statements between the two jumps, I hope it stays in the cache.
 *
 * The C code makes heavy use of the GCC features that you can get the
 * address of a C label. No hope to compile this with another compiler
 * than GCC!
 */

/* ++andreas: no need क्रम complicated code, just depend on prefetch */

अटल व्योम atari_reset(व्योम)
अणु
	दीर्घ tc_val = 0;
	दीर्घ reset_addr;

	/*
	 * On the Medusa, phys. 0x4 may contain garbage because it's no
	 * ROM.  See above क्रम explanation why we cannot use PTOV(4).
	 */
	reset_addr = MACH_IS_MEDUSA || MACH_IS_AB40 ? 0xe00030 :
		     *(अचिन्हित दीर्घ *) 0xff000004;

	/* reset ACIA क्रम चयन off OverScan, अगर it's active */
	अगर (atari_चयनes & ATARI_SWITCH_OVSC_IKBD)
		acia.key_ctrl = ACIA_RESET;
	अगर (atari_चयनes & ATARI_SWITCH_OVSC_MIDI)
		acia.mid_ctrl = ACIA_RESET;

	/* processor independent: turn off पूर्णांकerrupts and reset the VBR;
	 * the caches must be left enabled, अन्यथा prefetching the final jump
	 * inकाष्ठाion करोesn't work.
	 */
	local_irq_disable();
	यंत्र अस्थिर ("movec	%0,%%vbr"
			: : "d" (0));

	अगर (CPU_IS_040_OR_060) अणु
		अचिन्हित दीर्घ jmp_addr040 = virt_to_phys(&&jmp_addr_label040);
		अगर (CPU_IS_060) अणु
			/* 68060: clear PCR to turn off superscalar operation */
			यंत्र अस्थिर ("\n"
				"	.chip 68060\n"
				"	movec %0,%%pcr\n"
				"	.chip 68k"
				: : "d" (0));
		पूर्ण

		यंत्र अस्थिर ("\n"
			"	move.l	%0,%%d0\n"
			"	and.l	#0xff000000,%%d0\n"
			"	or.w	#0xe020,%%d0\n"   /* map 16 MB, enable, cacheable */
			"	.chip	68040\n"
			"	movec	%%d0,%%itt0\n"
			"	movec	%%d0,%%dtt0\n"
			"	.chip	68k\n"
			"	jmp	%0@"
			: : "a" (jmp_addr040)
			: "d0");
	jmp_addr_label040:
		यंत्र अस्थिर ("\n"
			"	moveq	#0,%%d0\n"
			"	nop\n"
			"	.chip	68040\n"
			"	cinva	%%bc\n"
			"	nop\n"
			"	pflusha\n"
			"	nop\n"
			"	movec	%%d0,%%tc\n"
			"	nop\n"
			/* the following setup of transparent translations is needed on the
			 * Afterburner040 to successfully reboot. Other machines shouldn't
			 * care about a dअगरferent tt regs setup, they also didn't care in
			 * the past that the regs weren't turned off. */
			"	move.l	#0xffc000,%%d0\n" /* whole insn space cacheable */
			"	movec	%%d0,%%itt0\n"
			"	movec	%%d0,%%itt1\n"
			"	or.w	#0x40,%/d0\n" /* whole data space non-cacheable/ser. */
			"	movec	%%d0,%%dtt0\n"
			"	movec	%%d0,%%dtt1\n"
			"	.chip	68k\n"
			"	jmp	%0@"
			: /* no outमाला_दो */
			: "a" (reset_addr)
			: "d0");
	पूर्ण अन्यथा
		यंत्र अस्थिर ("\n"
			"	pmove	%0,%%tc\n"
			"	jmp	%1@"
			: /* no outमाला_दो */
			: "m" (tc_val), "a" (reset_addr));
पूर्ण


अटल व्योम atari_get_model(अक्षर *model)
अणु
	म_नकल(model, "Atari ");
	चयन (atari_mch_cookie >> 16) अणु
	हाल ATARI_MCH_ST:
		अगर (ATARIHW_PRESENT(MSTE_CLK))
			म_जोड़ो(model, "Mega ST");
		अन्यथा
			म_जोड़ो(model, "ST");
		अवरोध;
	हाल ATARI_MCH_STE:
		अगर (MACH_IS_MSTE)
			म_जोड़ो(model, "Mega STE");
		अन्यथा
			म_जोड़ो(model, "STE");
		अवरोध;
	हाल ATARI_MCH_TT:
		अगर (MACH_IS_MEDUSA)
			/* Medusa has TT _MCH cookie */
			म_जोड़ो(model, "Medusa");
		अन्यथा
			म_जोड़ो(model, "TT");
		अवरोध;
	हाल ATARI_MCH_FALCON:
		म_जोड़ो(model, "Falcon");
		अगर (MACH_IS_AB40)
			म_जोड़ो(model, " (with Afterburner040)");
		अवरोध;
	शेष:
		प्र_लिखो(model + म_माप(model), "(unknown mach cookie 0x%lx)",
			atari_mch_cookie);
		अवरोध;
	पूर्ण
पूर्ण


अटल व्योम atari_get_hardware_list(काष्ठा seq_file *m)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < m68k_num_memory; i++)
		seq_म_लिखो(m, "\t%3ld MB at 0x%08lx (%s)\n",
				m68k_memory[i].size >> 20, m68k_memory[i].addr,
				(m68k_memory[i].addr & 0xff000000 ?
				 "alternate RAM" : "ST-RAM"));

#घोषणा ATARIHW_ANNOUNCE(name, str)			\
	अगर (ATARIHW_PRESENT(name))			\
		seq_म_लिखो(m, "\t%s\n", str)

	seq_माला_दो(m, "Detected hardware:\n");
	ATARIHW_ANNOUNCE(STND_SHIFTER, "ST Shifter");
	ATARIHW_ANNOUNCE(EXTD_SHIFTER, "STe Shifter");
	ATARIHW_ANNOUNCE(TT_SHIFTER, "TT Shifter");
	ATARIHW_ANNOUNCE(VIDEL_SHIFTER, "Falcon Shifter");
	ATARIHW_ANNOUNCE(YM_2149, "Programmable Sound Generator");
	ATARIHW_ANNOUNCE(PCM_8BIT, "PCM 8 Bit Sound");
	ATARIHW_ANNOUNCE(CODEC, "CODEC Sound");
	ATARIHW_ANNOUNCE(TT_SCSI, "SCSI Controller NCR5380 (TT style)");
	ATARIHW_ANNOUNCE(ST_SCSI, "SCSI Controller NCR5380 (Falcon style)");
	ATARIHW_ANNOUNCE(ACSI, "ACSI Interface");
	ATARIHW_ANNOUNCE(IDE, "IDE Interface");
	ATARIHW_ANNOUNCE(FDCSPEED, "8/16 Mhz Switch for FDC");
	ATARIHW_ANNOUNCE(ST_MFP, "Multi Function Peripheral MFP 68901");
	ATARIHW_ANNOUNCE(TT_MFP, "Second Multi Function Peripheral MFP 68901");
	ATARIHW_ANNOUNCE(SCC, "Serial Communications Controller SCC 8530");
	ATARIHW_ANNOUNCE(ST_ESCC, "Extended Serial Communications Controller SCC 85230");
	ATARIHW_ANNOUNCE(ANALOG_JOY, "Paddle Interface");
	ATARIHW_ANNOUNCE(MICROWIRE, "MICROWIRE(tm) Interface");
	ATARIHW_ANNOUNCE(STND_DMA, "DMA Controller (24 bit)");
	ATARIHW_ANNOUNCE(EXTD_DMA, "DMA Controller (32 bit)");
	ATARIHW_ANNOUNCE(SCSI_DMA, "DMA Controller for NCR5380");
	ATARIHW_ANNOUNCE(SCC_DMA, "DMA Controller for SCC");
	ATARIHW_ANNOUNCE(TT_CLK, "Clock Chip MC146818A");
	ATARIHW_ANNOUNCE(MSTE_CLK, "Clock Chip RP5C15");
	ATARIHW_ANNOUNCE(SCU, "System Control Unit");
	ATARIHW_ANNOUNCE(BLITTER, "Blitter");
	ATARIHW_ANNOUNCE(VME, "VME Bus");
	ATARIHW_ANNOUNCE(DSP56K, "DSP56001 processor");
पूर्ण

/*
 * MSch: initial platक्रमm device support क्रम Atari,
 * required क्रम EtherNAT/EtherNEC/NetUSBee drivers
 */

#अगर defined(CONFIG_ATARI_ETHERNAT) || defined(CONFIG_ATARI_ETHERNEC)
अटल व्योम isp1160_delay(काष्ठा device *dev, पूर्णांक delay)
अणु
	ndelay(delay);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_ATARI_ETHERNAT
/*
 * EtherNAT: SMC91C111 Ethernet chipset, handled by smc91x driver
 */

#घोषणा ATARI_ETHERNAT_IRQ		140

अटल काष्ठा resource smc91x_resources[] = अणु
	[0] = अणु
		.name	= "smc91x-regs",
		.start	= ATARI_ETHERNAT_PHYS_ADDR,
		.end	= ATARI_ETHERNAT_PHYS_ADDR + 0xfffff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.name	= "smc91x-irq",
		.start	= ATARI_ETHERNAT_IRQ,
		.end	= ATARI_ETHERNAT_IRQ,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device smc91x_device = अणु
	.name		= "smc91x",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(smc91x_resources),
	.resource	= smc91x_resources,
पूर्ण;

/*
 * ISP 1160 - using the isp116x-hcd module
 */

#घोषणा ATARI_USB_PHYS_ADDR	0x80000012
#घोषणा ATARI_USB_IRQ		139

अटल काष्ठा resource isp1160_resources[] = अणु
	[0] = अणु
		.name	= "isp1160-data",
		.start	= ATARI_USB_PHYS_ADDR,
		.end	= ATARI_USB_PHYS_ADDR + 0x1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.name	= "isp1160-regs",
		.start	= ATARI_USB_PHYS_ADDR + 0x4,
		.end	= ATARI_USB_PHYS_ADDR + 0x5,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[2] = अणु
		.name	= "isp1160-irq",
		.start	= ATARI_USB_IRQ,
		.end	= ATARI_USB_IRQ,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

/* (DataBusWidth16|AnalogOCEnable|DREQOutputPolarity|DownstreamPort15KRSel ) */
अटल काष्ठा isp116x_platक्रमm_data isp1160_platक्रमm_data = अणु
	/* Enable पूर्णांकernal resistors on करोwnstream ports */
	.sel15Kres		= 1,
	/* On-chip overcurrent protection */
	.oc_enable		= 1,
	/* INT output polarity */
	.पूर्णांक_act_high		= 1,
	/* INT edge or level triggered */
	.पूर्णांक_edge_triggered	= 0,

	/* WAKEUP pin connected - NOT SUPPORTED  */
	/* .remote_wakeup_connected = 0, */
	/* Wakeup by devices on usb bus enabled */
	.remote_wakeup_enable	= 0,
	.delay			= isp1160_delay,
पूर्ण;

अटल काष्ठा platक्रमm_device isp1160_device = अणु
	.name		= "isp116x-hcd",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(isp1160_resources),
	.resource	= isp1160_resources,
	.dev			= अणु
		.platक्रमm_data	= &isp1160_platक्रमm_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device *atari_ethernat_devices[] __initdata = अणु
	&smc91x_device,
	&isp1160_device
पूर्ण;
#पूर्ण_अगर /* CONFIG_ATARI_ETHERNAT */

#अगर_घोषित CONFIG_ATARI_ETHERNEC
/*
 * EtherNEC: RTL8019 (NE2000 compatible) Ethernet chipset,
 * handled by ne.c driver
 */

#घोषणा ATARI_ETHERNEC_PHYS_ADDR	0xfffa0000
#घोषणा ATARI_ETHERNEC_BASE		0x300
#घोषणा ATARI_ETHERNEC_IRQ		IRQ_MFP_TIMER1

अटल काष्ठा resource rtl8019_resources[] = अणु
	[0] = अणु
		.name	= "rtl8019-regs",
		.start	= ATARI_ETHERNEC_BASE,
		.end	= ATARI_ETHERNEC_BASE + 0x20 - 1,
		.flags	= IORESOURCE_IO,
	पूर्ण,
	[1] = अणु
		.name	= "rtl8019-irq",
		.start	= ATARI_ETHERNEC_IRQ,
		.end	= ATARI_ETHERNEC_IRQ,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device rtl8019_device = अणु
	.name		= "ne",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(rtl8019_resources),
	.resource	= rtl8019_resources,
पूर्ण;

/*
 * NetUSBee: ISP1160 USB host adapter via ROM-port adapter
 */

#घोषणा ATARI_NETUSBEE_PHYS_ADDR	0xfffa8000
#घोषणा ATARI_NETUSBEE_BASE		0x340
#घोषणा ATARI_NETUSBEE_IRQ		IRQ_MFP_TIMER2

अटल काष्ठा resource netusbee_resources[] = अणु
	[0] = अणु
		.name	= "isp1160-data",
		.start	= ATARI_NETUSBEE_BASE,
		.end	= ATARI_NETUSBEE_BASE + 0x1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.name	= "isp1160-regs",
		.start	= ATARI_NETUSBEE_BASE + 0x20,
		.end	= ATARI_NETUSBEE_BASE + 0x21,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[2] = अणु
		.name	= "isp1160-irq",
		.start	= ATARI_NETUSBEE_IRQ,
		.end	= ATARI_NETUSBEE_IRQ,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

/* (DataBusWidth16|AnalogOCEnable|DREQOutputPolarity|DownstreamPort15KRSel ) */
अटल काष्ठा isp116x_platक्रमm_data netusbee_platक्रमm_data = अणु
	/* Enable पूर्णांकernal resistors on करोwnstream ports */
	.sel15Kres		= 1,
	/* On-chip overcurrent protection */
	.oc_enable		= 1,
	/* INT output polarity */
	.पूर्णांक_act_high		= 1,
	/* INT edge or level triggered */
	.पूर्णांक_edge_triggered	= 0,

	/* WAKEUP pin connected - NOT SUPPORTED  */
	/* .remote_wakeup_connected = 0, */
	/* Wakeup by devices on usb bus enabled */
	.remote_wakeup_enable	= 0,
	.delay			= isp1160_delay,
पूर्ण;

अटल काष्ठा platक्रमm_device netusbee_device = अणु
	.name		= "isp116x-hcd",
	.id		= 1,
	.num_resources	= ARRAY_SIZE(netusbee_resources),
	.resource	= netusbee_resources,
	.dev			= अणु
		.platक्रमm_data	= &netusbee_platक्रमm_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device *atari_netusbee_devices[] __initdata = अणु
	&rtl8019_device,
	&netusbee_device
पूर्ण;
#पूर्ण_अगर /* CONFIG_ATARI_ETHERNEC */

#अगर IS_ENABLED(CONFIG_ATARI_SCSI)
अटल स्थिर काष्ठा resource atari_scsi_st_rsrc[] __initस्थिर = अणु
	अणु
		.flags = IORESOURCE_IRQ,
		.start = IRQ_MFP_FSCSI,
		.end   = IRQ_MFP_FSCSI,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource atari_scsi_tt_rsrc[] __initस्थिर = अणु
	अणु
		.flags = IORESOURCE_IRQ,
		.start = IRQ_TT_MFP_SCSI,
		.end   = IRQ_TT_MFP_SCSI,
	पूर्ण,
पूर्ण;
#पूर्ण_अगर

/*
 * Falcon IDE पूर्णांकerface
 */

#घोषणा FALCON_IDE_BASE	0xfff00000

अटल स्थिर काष्ठा resource atari_falconide_rsrc[] __initस्थिर = अणु
	अणु
		.flags = IORESOURCE_MEM,
		.start = FALCON_IDE_BASE,
		.end   = FALCON_IDE_BASE + 0x39,
	पूर्ण,
	अणु
		.flags = IORESOURCE_IRQ,
		.start = IRQ_MFP_FSCSI,
		.end   = IRQ_MFP_FSCSI,
	पूर्ण,
पूर्ण;

पूर्णांक __init atari_platक्रमm_init(व्योम)
अणु
	काष्ठा platक्रमm_device *pdev;
	पूर्णांक rv = 0;

	अगर (!MACH_IS_ATARI)
		वापस -ENODEV;

#अगर_घोषित CONFIG_ATARI_ETHERNAT
	अणु
		अचिन्हित अक्षर *enatc_virt;
		enatc_virt = (अचिन्हित अक्षर *)ioremap((ATARI_ETHERNAT_PHYS_ADDR+0x23), 0xf);
		अगर (hwreg_present(enatc_virt)) अणु
			rv = platक्रमm_add_devices(atari_ethernat_devices,
						ARRAY_SIZE(atari_ethernat_devices));
		पूर्ण
		iounmap(enatc_virt);
	पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_ATARI_ETHERNEC
	अणु
		पूर्णांक error;
		अचिन्हित अक्षर *enec_virt;
		enec_virt = (अचिन्हित अक्षर *)ioremap((ATARI_ETHERNEC_PHYS_ADDR), 0xf);
		अगर (hwreg_present(enec_virt)) अणु
			error = platक्रमm_add_devices(atari_netusbee_devices,
						ARRAY_SIZE(atari_netusbee_devices));
			अगर (error && !rv)
				rv = error;
		पूर्ण
		iounmap(enec_virt);
	पूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_ATARI_SCSI)
	अगर (ATARIHW_PRESENT(ST_SCSI))
		platक्रमm_device_रेजिस्टर_simple("atari_scsi", -1,
			atari_scsi_st_rsrc, ARRAY_SIZE(atari_scsi_st_rsrc));
	अन्यथा अगर (ATARIHW_PRESENT(TT_SCSI))
		platक्रमm_device_रेजिस्टर_simple("atari_scsi", -1,
			atari_scsi_tt_rsrc, ARRAY_SIZE(atari_scsi_tt_rsrc));
#पूर्ण_अगर

	अगर (ATARIHW_PRESENT(IDE)) अणु
		pdev = platक्रमm_device_रेजिस्टर_simple("atari-falcon-ide", -1,
			atari_falconide_rsrc, ARRAY_SIZE(atari_falconide_rsrc));
		अगर (IS_ERR(pdev))
			rv = PTR_ERR(pdev);
	पूर्ण

	वापस rv;
पूर्ण

arch_initcall(atari_platक्रमm_init);
