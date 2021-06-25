<शैली गुरु>
/*
 *  linux/arch/m68k/amiga/config.c
 *
 *  Copyright (C) 1993 Hamish Macकरोnald
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

/*
 * Miscellaneous Amiga stuff
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/tty.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/console.h>
#समावेश <linux/rtc.h>
#समावेश <linux/init.h>
#समावेश <linux/vt_kern.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/zorro.h>
#समावेश <linux/module.h>
#समावेश <linux/keyboard.h>

#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/bootinfo-amiga.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/amigahw.h>
#समावेश <यंत्र/amigaपूर्णांकs.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/पन.स>

अटल अचिन्हित दीर्घ amiga_model;

अचिन्हित दीर्घ amiga_eघड़ी;
EXPORT_SYMBOL(amiga_eघड़ी);

अचिन्हित दीर्घ amiga_colorघड़ी;
EXPORT_SYMBOL(amiga_colorघड़ी);

अचिन्हित दीर्घ amiga_chipset;
EXPORT_SYMBOL(amiga_chipset);

अचिन्हित अक्षर amiga_vblank;
EXPORT_SYMBOL(amiga_vblank);

अटल अचिन्हित अक्षर amiga_psfreq;

काष्ठा amiga_hw_present amiga_hw_present;
EXPORT_SYMBOL(amiga_hw_present);

अटल अक्षर s_a500[] __initdata = "A500";
अटल अक्षर s_a500p[] __initdata = "A500+";
अटल अक्षर s_a600[] __initdata = "A600";
अटल अक्षर s_a1000[] __initdata = "A1000";
अटल अक्षर s_a1200[] __initdata = "A1200";
अटल अक्षर s_a2000[] __initdata = "A2000";
अटल अक्षर s_a2500[] __initdata = "A2500";
अटल अक्षर s_a3000[] __initdata = "A3000";
अटल अक्षर s_a3000t[] __initdata = "A3000T";
अटल अक्षर s_a3000p[] __initdata = "A3000+";
अटल अक्षर s_a4000[] __initdata = "A4000";
अटल अक्षर s_a4000t[] __initdata = "A4000T";
अटल अक्षर s_cdtv[] __initdata = "CDTV";
अटल अक्षर s_cd32[] __initdata = "CD32";
अटल अक्षर s_draco[] __initdata = "Draco";
अटल अक्षर *amiga_models[] __initdata = अणु
	[AMI_500-AMI_500]	= s_a500,
	[AMI_500PLUS-AMI_500]	= s_a500p,
	[AMI_600-AMI_500]	= s_a600,
	[AMI_1000-AMI_500]	= s_a1000,
	[AMI_1200-AMI_500]	= s_a1200,
	[AMI_2000-AMI_500]	= s_a2000,
	[AMI_2500-AMI_500]	= s_a2500,
	[AMI_3000-AMI_500]	= s_a3000,
	[AMI_3000T-AMI_500]	= s_a3000t,
	[AMI_3000PLUS-AMI_500]	= s_a3000p,
	[AMI_4000-AMI_500]	= s_a4000,
	[AMI_4000T-AMI_500]	= s_a4000t,
	[AMI_CDTV-AMI_500]	= s_cdtv,
	[AMI_CD32-AMI_500]	= s_cd32,
	[AMI_DRACO-AMI_500]	= s_draco,
पूर्ण;

अटल अक्षर amiga_model_name[13] = "Amiga ";

अटल व्योम amiga_sched_init(व्योम);
अटल व्योम amiga_get_model(अक्षर *model);
अटल व्योम amiga_get_hardware_list(काष्ठा seq_file *m);
बाह्य व्योम amiga_mksound(अचिन्हित पूर्णांक count, अचिन्हित पूर्णांक ticks);
अटल व्योम amiga_reset(व्योम);
बाह्य व्योम amiga_init_sound(व्योम);
अटल व्योम amiga_mem_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *b,
				    अचिन्हित पूर्णांक count);
#अगर_घोषित CONFIG_HEARTBEAT
अटल व्योम amiga_heartbeat(पूर्णांक on);
#पूर्ण_अगर

अटल काष्ठा console amiga_console_driver = अणु
	.name	= "debug",
	.flags	= CON_PRINTBUFFER,
	.index	= -1,
पूर्ण;


    /*
     *  Motherboard Resources present in all Amiga models
     */

अटल काष्ठा अणु
	काष्ठा resource _ciab, _ciaa, _custom, _kickstart;
पूर्ण mb_resources = अणु
	._ciab = अणु
		.name = "CIA B", .start = 0x00bfd000, .end = 0x00bfdfff
	पूर्ण,
	._ciaa = अणु
		.name = "CIA A", .start = 0x00bfe000, .end = 0x00bfefff
	पूर्ण,
	._custom = अणु
		.name = "Custom I/O", .start = 0x00dff000, .end = 0x00dfffff
	पूर्ण,
	._kickstart = अणु
		.name = "Kickstart ROM", .start = 0x00f80000, .end = 0x00ffffff
	पूर्ण
पूर्ण;

अटल काष्ठा resource ram_resource[NUM_MEMINFO];


    /*
     *  Parse an Amiga-specअगरic record in the bootinfo
     */

पूर्णांक __init amiga_parse_bootinfo(स्थिर काष्ठा bi_record *record)
अणु
	पूर्णांक unknown = 0;
	स्थिर व्योम *data = record->data;

	चयन (be16_to_cpu(record->tag)) अणु
	हाल BI_AMIGA_MODEL:
		amiga_model = be32_to_cpup(data);
		अवरोध;

	हाल BI_AMIGA_ECLOCK:
		amiga_eघड़ी = be32_to_cpup(data);
		अवरोध;

	हाल BI_AMIGA_CHIPSET:
		amiga_chipset = be32_to_cpup(data);
		अवरोध;

	हाल BI_AMIGA_CHIP_SIZE:
		amiga_chip_size = be32_to_cpup(data);
		अवरोध;

	हाल BI_AMIGA_VBLANK:
		amiga_vblank = *(स्थिर __u8 *)data;
		अवरोध;

	हाल BI_AMIGA_PSFREQ:
		amiga_psfreq = *(स्थिर __u8 *)data;
		अवरोध;

	हाल BI_AMIGA_AUTOCON:
#अगर_घोषित CONFIG_ZORRO
		अगर (zorro_num_स्वतःcon < ZORRO_NUM_AUTO) अणु
			स्थिर काष्ठा ConfigDev *cd = data;
			काष्ठा zorro_dev_init *dev = &zorro_स्वतःcon_init[zorro_num_स्वतःcon++];
			dev->rom = cd->cd_Rom;
			dev->slotaddr = be16_to_cpu(cd->cd_SlotAddr);
			dev->slotsize = be16_to_cpu(cd->cd_SlotSize);
			dev->boardaddr = be32_to_cpu(cd->cd_BoardAddr);
			dev->boardsize = be32_to_cpu(cd->cd_BoardSize);
		पूर्ण अन्यथा
			pr_warn("amiga_parse_bootinfo: too many AutoConfig devices\n");
#पूर्ण_अगर /* CONFIG_ZORRO */
		अवरोध;

	हाल BI_AMIGA_SERPER:
		/* serial port period: ignored here */
		अवरोध;

	शेष:
		unknown = 1;
	पूर्ण
	वापस unknown;
पूर्ण

    /*
     *  Identअगरy builtin hardware
     */

अटल व्योम __init amiga_identअगरy(व्योम)
अणु
	/* Fill in some शेष values, अगर necessary */
	अगर (amiga_eघड़ी == 0)
		amiga_eघड़ी = 709379;

	स_रखो(&amiga_hw_present, 0, माप(amiga_hw_present));

	pr_info("Amiga hardware found: ");
	अगर (amiga_model >= AMI_500 && amiga_model <= AMI_DRACO) अणु
		pr_cont("[%s] ", amiga_models[amiga_model-AMI_500]);
		म_जोड़ो(amiga_model_name, amiga_models[amiga_model-AMI_500]);
	पूर्ण

	चयन (amiga_model) अणु
	हाल AMI_UNKNOWN:
		अवरोध;

	हाल AMI_600:
	हाल AMI_1200:
		AMIGAHW_SET(A1200_IDE);
		AMIGAHW_SET(PCMCIA);
		fallthrough;
	हाल AMI_500:
	हाल AMI_500PLUS:
	हाल AMI_1000:
	हाल AMI_2000:
	हाल AMI_2500:
		AMIGAHW_SET(A2000_CLK);	/* Is this correct क्रम all models? */
		अवरोध;

	हाल AMI_3000:
	हाल AMI_3000T:
		AMIGAHW_SET(AMBER_FF);
		AMIGAHW_SET(MAGIC_REKICK);
		fallthrough;
	हाल AMI_3000PLUS:
		AMIGAHW_SET(A3000_SCSI);
		AMIGAHW_SET(A3000_CLK);
		AMIGAHW_SET(ZORRO3);
		अवरोध;

	हाल AMI_4000T:
		AMIGAHW_SET(A4000_SCSI);
		fallthrough;
	हाल AMI_4000:
		AMIGAHW_SET(A4000_IDE);
		AMIGAHW_SET(A3000_CLK);
		AMIGAHW_SET(ZORRO3);
		अवरोध;

	हाल AMI_CDTV:
	हाल AMI_CD32:
		AMIGAHW_SET(CD_ROM);
		AMIGAHW_SET(A2000_CLK);             /* Is this correct? */
		अवरोध;

	हाल AMI_DRACO:
		panic("No support for Draco yet");

	शेष:
		panic("Unknown Amiga Model");
	पूर्ण

	AMIGAHW_SET(AMI_VIDEO);
	AMIGAHW_SET(AMI_BLITTER);
	AMIGAHW_SET(AMI_AUDIO);
	AMIGAHW_SET(AMI_FLOPPY);
	AMIGAHW_SET(AMI_KEYBOARD);
	AMIGAHW_SET(AMI_MOUSE);
	AMIGAHW_SET(AMI_SERIAL);
	AMIGAHW_SET(AMI_PARALLEL);
	AMIGAHW_SET(CHIP_RAM);
	AMIGAHW_SET(PAULA);

	चयन (amiga_chipset) अणु
	हाल CS_OCS:
	हाल CS_ECS:
	हाल CS_AGA:
		चयन (amiga_custom.deniseid & 0xf) अणु
		हाल 0x0c:
			AMIGAHW_SET(DENISE_HR);
			अवरोध;
		हाल 0x08:
			AMIGAHW_SET(LISA);
			अवरोध;
		शेष:
			AMIGAHW_SET(DENISE);
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण
	चयन ((amiga_custom.vposr>>8) & 0x7f) अणु
	हाल 0x00:
		AMIGAHW_SET(AGNUS_PAL);
		अवरोध;
	हाल 0x10:
		AMIGAHW_SET(AGNUS_NTSC);
		अवरोध;
	हाल 0x20:
	हाल 0x21:
		AMIGAHW_SET(AGNUS_HR_PAL);
		अवरोध;
	हाल 0x30:
	हाल 0x31:
		AMIGAHW_SET(AGNUS_HR_NTSC);
		अवरोध;
	हाल 0x22:
	हाल 0x23:
		AMIGAHW_SET(ALICE_PAL);
		अवरोध;
	हाल 0x32:
	हाल 0x33:
		AMIGAHW_SET(ALICE_NTSC);
		अवरोध;
	पूर्ण
	AMIGAHW_SET(ZORRO);

#घोषणा AMIGAHW_ANNOUNCE(name, str)		\
	अगर (AMIGAHW_PRESENT(name))		\
		pr_cont(str)

	AMIGAHW_ANNOUNCE(AMI_VIDEO, "VIDEO ");
	AMIGAHW_ANNOUNCE(AMI_BLITTER, "BLITTER ");
	AMIGAHW_ANNOUNCE(AMBER_FF, "AMBER_FF ");
	AMIGAHW_ANNOUNCE(AMI_AUDIO, "AUDIO ");
	AMIGAHW_ANNOUNCE(AMI_FLOPPY, "FLOPPY ");
	AMIGAHW_ANNOUNCE(A3000_SCSI, "A3000_SCSI ");
	AMIGAHW_ANNOUNCE(A4000_SCSI, "A4000_SCSI ");
	AMIGAHW_ANNOUNCE(A1200_IDE, "A1200_IDE ");
	AMIGAHW_ANNOUNCE(A4000_IDE, "A4000_IDE ");
	AMIGAHW_ANNOUNCE(CD_ROM, "CD_ROM ");
	AMIGAHW_ANNOUNCE(AMI_KEYBOARD, "KEYBOARD ");
	AMIGAHW_ANNOUNCE(AMI_MOUSE, "MOUSE ");
	AMIGAHW_ANNOUNCE(AMI_SERIAL, "SERIAL ");
	AMIGAHW_ANNOUNCE(AMI_PARALLEL, "PARALLEL ");
	AMIGAHW_ANNOUNCE(A2000_CLK, "A2000_CLK ");
	AMIGAHW_ANNOUNCE(A3000_CLK, "A3000_CLK ");
	AMIGAHW_ANNOUNCE(CHIP_RAM, "CHIP_RAM ");
	AMIGAHW_ANNOUNCE(PAULA, "PAULA ");
	AMIGAHW_ANNOUNCE(DENISE, "DENISE ");
	AMIGAHW_ANNOUNCE(DENISE_HR, "DENISE_HR ");
	AMIGAHW_ANNOUNCE(LISA, "LISA ");
	AMIGAHW_ANNOUNCE(AGNUS_PAL, "AGNUS_PAL ");
	AMIGAHW_ANNOUNCE(AGNUS_NTSC, "AGNUS_NTSC ");
	AMIGAHW_ANNOUNCE(AGNUS_HR_PAL, "AGNUS_HR_PAL ");
	AMIGAHW_ANNOUNCE(AGNUS_HR_NTSC, "AGNUS_HR_NTSC ");
	AMIGAHW_ANNOUNCE(ALICE_PAL, "ALICE_PAL ");
	AMIGAHW_ANNOUNCE(ALICE_NTSC, "ALICE_NTSC ");
	AMIGAHW_ANNOUNCE(MAGIC_REKICK, "MAGIC_REKICK ");
	AMIGAHW_ANNOUNCE(PCMCIA, "PCMCIA ");
	अगर (AMIGAHW_PRESENT(ZORRO))
		pr_cont("ZORRO%s ", AMIGAHW_PRESENT(ZORRO3) ? "3" : "");
	pr_cont("\n");

#अघोषित AMIGAHW_ANNOUNCE
पूर्ण


अटल अचिन्हित दीर्घ amiga_अक्रमom_get_entropy(व्योम)
अणु
	/* VPOSR/VHPOSR provide at least 17 bits of data changing at 1.79 MHz */
	वापस *(अचिन्हित दीर्घ *)&amiga_custom.vposr;
पूर्ण


    /*
     *  Setup the Amiga configuration info
     */

व्योम __init config_amiga(व्योम)
अणु
	पूर्णांक i;

	amiga_identअगरy();

	/* Yuk, we करोn't have PCI memory */
	iomem_resource.name = "Memory";
	क्रम (i = 0; i < 4; i++)
		request_resource(&iomem_resource, &((काष्ठा resource *)&mb_resources)[i]);

	mach_sched_init      = amiga_sched_init;
	mach_init_IRQ        = amiga_init_IRQ;
	mach_get_model       = amiga_get_model;
	mach_get_hardware_list = amiga_get_hardware_list;
	mach_reset           = amiga_reset;
#अगर IS_ENABLED(CONFIG_INPUT_M68K_BEEP)
	mach_beep            = amiga_mksound;
#पूर्ण_अगर

#अगर_घोषित CONFIG_HEARTBEAT
	mach_heartbeat = amiga_heartbeat;
#पूर्ण_अगर

	mach_अक्रमom_get_entropy = amiga_अक्रमom_get_entropy;

	/* Fill in the घड़ी value (based on the 700 kHz E-Clock) */
	amiga_colorघड़ी = 5*amiga_eघड़ी;	/* 3.5 MHz */

	/* clear all DMA bits */
	amiga_custom.dmacon = DMAF_ALL;
	/* ensure that the DMA master bit is set */
	amiga_custom.dmacon = DMAF_SETCLR | DMAF_MASTER;

	/* करोn't use Z2 RAM as प्रणाली memory on Z3 capable machines */
	अगर (AMIGAHW_PRESENT(ZORRO3)) अणु
		पूर्णांक i, j;
		u32 disabled_z2mem = 0;

		क्रम (i = 0; i < m68k_num_memory; i++) अणु
			अगर (m68k_memory[i].addr < 16*1024*1024) अणु
				अगर (i == 0) अणु
					/* करोn't cut off the branch we're sitting on */
					pr_warn("Warning: kernel runs in Zorro II memory\n");
					जारी;
				पूर्ण
				disabled_z2mem += m68k_memory[i].size;
				m68k_num_memory--;
				क्रम (j = i; j < m68k_num_memory; j++)
					m68k_memory[j] = m68k_memory[j+1];
				i--;
			पूर्ण
		पूर्ण
		अगर (disabled_z2mem)
			pr_info("%dK of Zorro II memory will not be used as system memory\n",
				disabled_z2mem>>10);
	पूर्ण

	/* request all RAM */
	क्रम (i = 0; i < m68k_num_memory; i++) अणु
		ram_resource[i].name =
			(m68k_memory[i].addr >= 0x01000000) ? "32-bit Fast RAM" :
			(m68k_memory[i].addr < 0x00c00000) ? "16-bit Fast RAM" :
			"16-bit Slow RAM";
		ram_resource[i].start = m68k_memory[i].addr;
		ram_resource[i].end = m68k_memory[i].addr+m68k_memory[i].size-1;
		request_resource(&iomem_resource, &ram_resource[i]);
	पूर्ण

	/* initialize chipram allocator */
	amiga_chip_init();

	/* our beloved beeper */
	अगर (AMIGAHW_PRESENT(AMI_AUDIO))
		amiga_init_sound();

	/*
	 * अगर it is an A3000, set the magic bit that क्रमces
	 * a hard rekick
	 */
	अगर (AMIGAHW_PRESENT(MAGIC_REKICK))
		*(अचिन्हित अक्षर *)ZTWO_VADDR(0xde0002) |= 0x80;
पूर्ण

अटल u64 amiga_पढ़ो_clk(काष्ठा घड़ीsource *cs);

अटल काष्ठा घड़ीsource amiga_clk = अणु
	.name   = "ciab",
	.rating = 250,
	.पढ़ो   = amiga_पढ़ो_clk,
	.mask   = CLOCKSOURCE_MASK(32),
	.flags  = CLOCK_SOURCE_IS_CONTINUOUS,
पूर्ण;

अटल अचिन्हित लघु jअगरfy_ticks;
अटल u32 clk_total, clk_offset;

अटल irqवापस_t ciab_समयr_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	clk_total += jअगरfy_ticks;
	clk_offset = 0;
	legacy_समयr_tick(1);
	समयr_heartbeat();

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम __init amiga_sched_init(व्योम)
अणु
	अटल काष्ठा resource sched_res = अणु
		.name = "timer", .start = 0x00bfd400, .end = 0x00bfd5ff,
	पूर्ण;
	jअगरfy_ticks = DIV_ROUND_CLOSEST(amiga_eघड़ी, HZ);

	अगर (request_resource(&mb_resources._ciab, &sched_res))
		pr_warn("Cannot allocate ciab.ta{lo,hi}\n");
	ciab.cra &= 0xC0;   /* turn off समयr A, continuous mode, from Eclk */
	ciab.talo = jअगरfy_ticks % 256;
	ciab.tahi = jअगरfy_ticks / 256;

	/* install पूर्णांकerrupt service routine क्रम CIAB Timer A
	 *
	 * Please करोn't change this to use ciaa, as it पूर्णांकerferes with the
	 * SCSI code. We'll have to take a look at this later
	 */
	अगर (request_irq(IRQ_AMIGA_CIAB_TA, ciab_समयr_handler, IRQF_TIMER,
			"timer", शून्य))
		pr_err("Couldn't register timer interrupt\n");
	/* start समयr */
	ciab.cra |= 0x11;

	घड़ीsource_रेजिस्टर_hz(&amiga_clk, amiga_eघड़ी);
पूर्ण

अटल u64 amiga_पढ़ो_clk(काष्ठा घड़ीsource *cs)
अणु
	अचिन्हित लघु hi, lo, hi2;
	अचिन्हित दीर्घ flags;
	u32 ticks;

	local_irq_save(flags);

	/* पढ़ो CIA B समयr A current value */
	hi  = ciab.tahi;
	lo  = ciab.talo;
	hi2 = ciab.tahi;

	अगर (hi != hi2) अणु
		lo = ciab.talo;
		hi = hi2;
	पूर्ण

	ticks = hi << 8 | lo;

	अगर (ticks > jअगरfy_ticks / 2)
		/* check क्रम pending पूर्णांकerrupt */
		अगर (cia_set_irq(&ciab_base, 0) & CIA_ICR_TA)
			clk_offset = jअगरfy_ticks;

	ticks = jअगरfy_ticks - ticks;
	ticks += clk_offset + clk_total;

	local_irq_restore(flags);

	वापस ticks;
पूर्ण

अटल व्योम amiga_reset(व्योम)  __noवापस;

अटल व्योम amiga_reset(व्योम)
अणु
	अचिन्हित दीर्घ jmp_addr040 = virt_to_phys(&&jmp_addr_label040);
	अचिन्हित दीर्घ jmp_addr = virt_to_phys(&&jmp_addr_label);

	local_irq_disable();
	अगर (CPU_IS_040_OR_060)
		/* Setup transparent translation रेजिस्टरs क्रम mapping
		 * of 16 MB kernel segment beक्रमe disabling translation
		 */
		यंत्र अस्थिर ("\n"
			"	move.l	%0,%%d0\n"
			"	and.l	#0xff000000,%%d0\n"
			"	or.w	#0xe020,%%d0\n"   /* map 16 MB, enable, cacheable */
			"	.chip	68040\n"
			"	movec	%%d0,%%itt0\n"
			"	movec	%%d0,%%dtt0\n"
			"	.chip	68k\n"
			"	jmp	%0@\n"
			: /* no outमाला_दो */
			: "a" (jmp_addr040)
			: "d0");
	अन्यथा
		/* क्रम 680[23]0, just disable translation and jump to the physical
		 * address of the label
		 */
		यंत्र अस्थिर ("\n"
			"	pmove	%%tc,%@\n"
			"	bclr	#7,%@\n"
			"	pmove	%@,%%tc\n"
			"	jmp	%0@\n"
			: /* no outमाला_दो */
			: "a" (jmp_addr));
jmp_addr_label040:
	/* disable translation on '040 now */
	यंत्र अस्थिर ("\n"
		"	moveq	#0,%%d0\n"
		"	.chip	68040\n"
		"	movec	%%d0,%%tc\n"	/* disable MMU */
		"	.chip	68k\n"
		: /* no outमाला_दो */
		: /* no inमाला_दो */
		: "d0");

	jmp_addr_label:
	/* pickup reset address from AmigaOS ROM, reset devices and jump
	 * to reset address
	 */
	यंत्र अस्थिर ("\n"
		"	move.w	#0x2700,%sr\n"
		"	lea	0x01000000,%a0\n"
		"	sub.l	%a0@(-0x14),%a0\n"
		"	move.l	%a0@(4),%a0\n"
		"	subq.l	#2,%a0\n"
		"	jra	1f\n"
		/* align on a दीर्घword boundary */
		"	" __ALIGN_STR "\n"
		"1:\n"
		"	reset\n"
		"	jmp   %a0@");

	क्रम (;;)
		;
पूर्ण


    /*
     *  Debugging
     */

#घोषणा SAVEKMSG_MAXMEM		128*1024

#घोषणा SAVEKMSG_MAGIC1		0x53415645	/* 'SAVE' */
#घोषणा SAVEKMSG_MAGIC2		0x4B4D5347	/* 'KMSG' */

काष्ठा savekmsg अणु
	अचिन्हित दीर्घ magic1;		/* SAVEKMSG_MAGIC1 */
	अचिन्हित दीर्घ magic2;		/* SAVEKMSG_MAGIC2 */
	अचिन्हित दीर्घ magicptr;		/* address of magic1 */
	अचिन्हित दीर्घ size;
	अक्षर data[];
पूर्ण;

अटल काष्ठा savekmsg *savekmsg;

अटल व्योम amiga_mem_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s,
				    अचिन्हित पूर्णांक count)
अणु
	अगर (savekmsg->size + count <= SAVEKMSG_MAXMEM-माप(काष्ठा savekmsg)) अणु
		स_नकल(savekmsg->data + savekmsg->size, s, count);
		savekmsg->size += count;
	पूर्ण
पूर्ण

अटल पूर्णांक __init amiga_savekmsg_setup(अक्षर *arg)
अणु
	bool रेजिस्टरed;

	अगर (!MACH_IS_AMIGA || म_भेद(arg, "mem"))
		वापस 0;

	अगर (amiga_chip_size < SAVEKMSG_MAXMEM) अणु
		pr_err("Not enough chipram for debugging\n");
		वापस -ENOMEM;
	पूर्ण

	/* Just steal the block, the chipram allocator isn't functional yet */
	amiga_chip_size -= SAVEKMSG_MAXMEM;
	savekmsg = ZTWO_VADDR(CHIP_PHYSADDR + amiga_chip_size);
	savekmsg->magic1 = SAVEKMSG_MAGIC1;
	savekmsg->magic2 = SAVEKMSG_MAGIC2;
	savekmsg->magicptr = ZTWO_PADDR(savekmsg);
	savekmsg->size = 0;

	रेजिस्टरed = !!amiga_console_driver.ग_लिखो;
	amiga_console_driver.ग_लिखो = amiga_mem_console_ग_लिखो;
	अगर (!रेजिस्टरed)
		रेजिस्टर_console(&amiga_console_driver);
	वापस 0;
पूर्ण

early_param("debug", amiga_savekmsg_setup);

अटल व्योम amiga_serial_अ_दो(अक्षर c)
अणु
	amiga_custom.serdat = (अचिन्हित अक्षर)c | 0x100;
	जबतक (!(amiga_custom.serdatr & 0x2000))
		;
पूर्ण

अटल व्योम amiga_serial_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s,
				       अचिन्हित पूर्णांक count)
अणु
	जबतक (count--) अणु
		अगर (*s == '\n')
			amiga_serial_अ_दो('\r');
		amiga_serial_अ_दो(*s++);
	पूर्ण
पूर्ण

#अगर 0
व्योम amiga_serial_माला_दो(स्थिर अक्षर *s)
अणु
	amiga_serial_console_ग_लिखो(शून्य, s, म_माप(s));
पूर्ण

पूर्णांक amiga_serial_console_रुको_key(काष्ठा console *co)
अणु
	पूर्णांक ch;

	जबतक (!(amiga_custom.पूर्णांकreqr & IF_RBF))
		barrier();
	ch = amiga_custom.serdatr & 0xff;
	/* clear the पूर्णांकerrupt, so that another अक्षरacter can be पढ़ो */
	amiga_custom.पूर्णांकreq = IF_RBF;
	वापस ch;
पूर्ण

व्योम amiga_serial_माला_लो(काष्ठा console *co, अक्षर *s, पूर्णांक len)
अणु
	पूर्णांक ch, cnt = 0;

	जबतक (1) अणु
		ch = amiga_serial_console_रुको_key(co);

		/* Check क्रम backspace. */
		अगर (ch == 8 || ch == 127) अणु
			अगर (cnt == 0) अणु
				amiga_serial_अ_दो('\007');
				जारी;
			पूर्ण
			cnt--;
			amiga_serial_माला_दो("\010 \010");
			जारी;
		पूर्ण

		/* Check क्रम enter. */
		अगर (ch == 10 || ch == 13)
			अवरोध;

		/* See अगर line is too दीर्घ. */
		अगर (cnt >= len + 1) अणु
			amiga_serial_अ_दो(7);
			cnt--;
			जारी;
		पूर्ण

		/* Store and echo अक्षरacter. */
		s[cnt++] = ch;
		amiga_serial_अ_दो(ch);
	पूर्ण
	/* Prपूर्णांक enter. */
	amiga_serial_माला_दो("\r\n");
	s[cnt] = 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init amiga_debug_setup(अक्षर *arg)
अणु
	bool रेजिस्टरed;

	अगर (!MACH_IS_AMIGA || म_भेद(arg, "ser"))
		वापस 0;

	/* no initialization required (?) */
	रेजिस्टरed = !!amiga_console_driver.ग_लिखो;
	amiga_console_driver.ग_लिखो = amiga_serial_console_ग_लिखो;
	अगर (!रेजिस्टरed)
		रेजिस्टर_console(&amiga_console_driver);
	वापस 0;
पूर्ण

early_param("debug", amiga_debug_setup);

#अगर_घोषित CONFIG_HEARTBEAT
अटल व्योम amiga_heartbeat(पूर्णांक on)
अणु
	अगर (on)
		ciaa.pra &= ~2;
	अन्यथा
		ciaa.pra |= 2;
पूर्ण
#पूर्ण_अगर

    /*
     *  Amiga specअगरic parts of /proc
     */

अटल व्योम amiga_get_model(अक्षर *model)
अणु
	म_नकल(model, amiga_model_name);
पूर्ण


अटल व्योम amiga_get_hardware_list(काष्ठा seq_file *m)
अणु
	अगर (AMIGAHW_PRESENT(CHIP_RAM))
		seq_म_लिखो(m, "Chip RAM:\t%ldK\n", amiga_chip_size>>10);
	seq_म_लिखो(m, "PS Freq:\t%dHz\nEClock Freq:\t%ldHz\n",
			amiga_psfreq, amiga_eघड़ी);
	अगर (AMIGAHW_PRESENT(AMI_VIDEO)) अणु
		अक्षर *type;
		चयन (amiga_chipset) अणु
		हाल CS_OCS:
			type = "OCS";
			अवरोध;
		हाल CS_ECS:
			type = "ECS";
			अवरोध;
		हाल CS_AGA:
			type = "AGA";
			अवरोध;
		शेष:
			type = "Old or Unknown";
			अवरोध;
		पूर्ण
		seq_म_लिखो(m, "Graphics:\t%s\n", type);
	पूर्ण

#घोषणा AMIGAHW_ANNOUNCE(name, str)			\
	अगर (AMIGAHW_PRESENT(name))			\
		seq_म_लिखो (m, "\t%s\n", str)

	seq_माला_दो(m, "Detected hardware:\n");
	AMIGAHW_ANNOUNCE(AMI_VIDEO, "Amiga Video");
	AMIGAHW_ANNOUNCE(AMI_BLITTER, "Blitter");
	AMIGAHW_ANNOUNCE(AMBER_FF, "Amber Flicker Fixer");
	AMIGAHW_ANNOUNCE(AMI_AUDIO, "Amiga Audio");
	AMIGAHW_ANNOUNCE(AMI_FLOPPY, "Floppy Controller");
	AMIGAHW_ANNOUNCE(A3000_SCSI, "SCSI Controller WD33C93 (A3000 style)");
	AMIGAHW_ANNOUNCE(A4000_SCSI, "SCSI Controller NCR53C710 (A4000T style)");
	AMIGAHW_ANNOUNCE(A1200_IDE, "IDE Interface (A1200 style)");
	AMIGAHW_ANNOUNCE(A4000_IDE, "IDE Interface (A4000 style)");
	AMIGAHW_ANNOUNCE(CD_ROM, "Internal CD ROM drive");
	AMIGAHW_ANNOUNCE(AMI_KEYBOARD, "Keyboard");
	AMIGAHW_ANNOUNCE(AMI_MOUSE, "Mouse Port");
	AMIGAHW_ANNOUNCE(AMI_SERIAL, "Serial Port");
	AMIGAHW_ANNOUNCE(AMI_PARALLEL, "Parallel Port");
	AMIGAHW_ANNOUNCE(A2000_CLK, "Hardware Clock (A2000 style)");
	AMIGAHW_ANNOUNCE(A3000_CLK, "Hardware Clock (A3000 style)");
	AMIGAHW_ANNOUNCE(CHIP_RAM, "Chip RAM");
	AMIGAHW_ANNOUNCE(PAULA, "Paula 8364");
	AMIGAHW_ANNOUNCE(DENISE, "Denise 8362");
	AMIGAHW_ANNOUNCE(DENISE_HR, "Denise 8373");
	AMIGAHW_ANNOUNCE(LISA, "Lisa 8375");
	AMIGAHW_ANNOUNCE(AGNUS_PAL, "Normal/Fat PAL Agnus 8367/8371");
	AMIGAHW_ANNOUNCE(AGNUS_NTSC, "Normal/Fat NTSC Agnus 8361/8370");
	AMIGAHW_ANNOUNCE(AGNUS_HR_PAL, "Fat Hires PAL Agnus 8372");
	AMIGAHW_ANNOUNCE(AGNUS_HR_NTSC, "Fat Hires NTSC Agnus 8372");
	AMIGAHW_ANNOUNCE(ALICE_PAL, "PAL Alice 8374");
	AMIGAHW_ANNOUNCE(ALICE_NTSC, "NTSC Alice 8374");
	AMIGAHW_ANNOUNCE(MAGIC_REKICK, "Magic Hard Rekick");
	AMIGAHW_ANNOUNCE(PCMCIA, "PCMCIA Slot");
#अगर_घोषित CONFIG_ZORRO
	अगर (AMIGAHW_PRESENT(ZORRO))
		seq_म_लिखो(m, "\tZorro II%s AutoConfig: %d Expansion "
				"Device%s\n",
				AMIGAHW_PRESENT(ZORRO3) ? "I" : "",
				zorro_num_स्वतःcon, zorro_num_स्वतःcon == 1 ? "" : "s");
#पूर्ण_अगर /* CONFIG_ZORRO */

#अघोषित AMIGAHW_ANNOUNCE
पूर्ण

/*
 * The Amiga keyboard driver needs key_maps, but we cannot export it in
 * drivers/अक्षर/defkeymap.c, as it is स्वतःgenerated
 */
#अगर_घोषित CONFIG_HW_CONSOLE
EXPORT_SYMBOL_GPL(key_maps);
#पूर्ण_अगर
