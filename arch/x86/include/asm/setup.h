<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_SETUP_H
#घोषणा _ASM_X86_SETUP_H

#समावेश <uapi/यंत्र/setup.h>

#घोषणा COMMAND_LINE_SIZE 2048

#समावेश <linux/linkage.h>
#समावेश <यंत्र/page_types.h>

#अगर_घोषित __i386__

#समावेश <linux/pfn.h>
/*
 * Reserved space क्रम vदो_स्मृति and iomap - defined in यंत्र/page.h
 */
#घोषणा MAXMEM_PFN	PFN_DOWN(MAXMEM)
#घोषणा MAX_NONPAE_PFN	(1 << 20)

#पूर्ण_अगर /* __i386__ */

#घोषणा PARAM_SIZE 4096		/* माप(काष्ठा boot_params) */

#घोषणा OLD_CL_MAGIC		0xA33F
#घोषणा OLD_CL_ADDRESS		0x020	/* Relative to real mode data */
#घोषणा NEW_CL_POINTER		0x228	/* Relative to real mode data */

#अगर_अघोषित __ASSEMBLY__
#समावेश <यंत्र/bootparam.h>
#समावेश <यंत्र/x86_init.h>

बाह्य u64 relocated_ramdisk;

/* Interrupt control क्रम vSMPowered x86_64 प्रणालीs */
#अगर_घोषित CONFIG_X86_64
व्योम vsmp_init(व्योम);
#अन्यथा
अटल अंतरभूत व्योम vsmp_init(व्योम) अणु पूर्ण
#पूर्ण_अगर

काष्ठा pt_regs;

व्योम setup_bios_corruption_check(व्योम);
व्योम early_platक्रमm_quirks(व्योम);

बाह्य अचिन्हित दीर्घ saved_video_mode;

बाह्य व्योम reserve_standard_io_resources(व्योम);
बाह्य व्योम i386_reserve_resources(व्योम);
बाह्य अचिन्हित दीर्घ __startup_64(अचिन्हित दीर्घ physaddr, काष्ठा boot_params *bp);
बाह्य अचिन्हित दीर्घ __startup_secondary_64(व्योम);
बाह्य व्योम startup_64_setup_env(अचिन्हित दीर्घ physbase);
बाह्य व्योम early_setup_idt(व्योम);
बाह्य व्योम __init करो_early_exception(काष्ठा pt_regs *regs, पूर्णांक trapnr);

#अगर_घोषित CONFIG_X86_INTEL_MID
बाह्य व्योम x86_पूर्णांकel_mid_early_setup(व्योम);
#अन्यथा
अटल अंतरभूत व्योम x86_पूर्णांकel_mid_early_setup(व्योम) अणु पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_X86_INTEL_CE
बाह्य व्योम x86_ce4100_early_setup(व्योम);
#अन्यथा
अटल अंतरभूत व्योम x86_ce4100_early_setup(व्योम) अणु पूर्ण
#पूर्ण_अगर

#अगर_अघोषित _SETUP

#समावेश <यंत्र/espfix.h>
#समावेश <linux/kernel.h>

/*
 * This is set up by the setup-routine at boot-समय
 */
बाह्य काष्ठा boot_params boot_params;
बाह्य अक्षर _text[];

अटल अंतरभूत bool kaslr_enabled(व्योम)
अणु
	वापस IS_ENABLED(CONFIG_RANDOMIZE_MEMORY) &&
		!!(boot_params.hdr.loadflags & KASLR_FLAG);
पूर्ण

/*
 * Apply no अक्रमomization अगर KASLR was disabled at boot or अगर KASAN
 * is enabled. KASAN shaकरोw mappings rely on regions being PGD aligned.
 */
अटल अंतरभूत bool kaslr_memory_enabled(व्योम)
अणु
	वापस kaslr_enabled() && !IS_ENABLED(CONFIG_KASAN);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ kaslr_offset(व्योम)
अणु
	वापस (अचिन्हित दीर्घ)&_text - __START_KERNEL;
पूर्ण

/*
 * Do NOT EVER look at the BIOS memory size location.
 * It करोes not work on many machines.
 */
#घोषणा LOWMEMSIZE()	(0x9f000)

/* exceedingly early brk-like allocator */
बाह्य अचिन्हित दीर्घ _brk_end;
व्योम *extend_brk(माप_प्रकार size, माप_प्रकार align);

/*
 * Reserve space in the brk section.  The name must be unique within
 * the file, and somewhat descriptive.  The size is in bytes.  Must be
 * used at file scope.
 *
 * (This uses a temp function to wrap the यंत्र so we can pass it the
 * size parameter; otherwise we wouldn't be able to.  We can't use a
 * "section" attribute on a normal variable because it always ends up
 * being @progbits, which ends up allocating space in the vmlinux
 * executable.)
 */
#घोषणा RESERVE_BRK(name,sz)						\
	अटल व्योम __section(".discard.text") __used notrace		\
	__brk_reservation_fn_##name##__(व्योम) अणु				\
		यंत्र अस्थिर (						\
			".pushsection .brk_reservation,\"aw\",@nobits;" \
			".brk." #name ":"				\
			" 1:.skip %c0;"					\
			" .size .brk." #name ", . - 1b;"		\
			" .popsection"					\
			: : "i" (sz));					\
	पूर्ण

बाह्य व्योम probe_roms(व्योम);
#अगर_घोषित __i386__

यंत्रlinkage व्योम __init i386_start_kernel(व्योम);

#अन्यथा
यंत्रlinkage व्योम __init x86_64_start_kernel(अक्षर *real_mode);
यंत्रlinkage व्योम __init x86_64_start_reservations(अक्षर *real_mode_data);

#पूर्ण_अगर /* __i386__ */
#पूर्ण_अगर /* _SETUP */
#अन्यथा
#घोषणा RESERVE_BRK(name,sz)				\
	.pushsection .brk_reservation,"aw",@nobits;	\
.brk.name:						\
1:	.skip sz;					\
	.size .brk.name,.-1b;				\
	.popsection
#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* _ASM_X86_SETUP_H */
