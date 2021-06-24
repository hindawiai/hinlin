<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * init.c: PROM library initialisation code.
 *
 * Copyright (C) 1998 Harald Koerfgen
 * Copyright (C) 2002, 2004  Maciej W. Rozycki
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/linkage.h>
#समावेश <linux/smp.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>

#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/cpu-type.h>
#समावेश <यंत्र/processor.h>

#समावेश <यंत्र/dec/prom.h>


पूर्णांक (*__rex_bootinit)(व्योम);
पूर्णांक (*__rex_bootपढ़ो)(व्योम);
पूर्णांक (*__rex_getbiपंचांगap)(memmap *);
अचिन्हित दीर्घ *(*__rex_slot_address)(पूर्णांक);
व्योम *(*__rex_gettcinfo)(व्योम);
पूर्णांक (*__rex_माला_लोysid)(व्योम);
व्योम (*__rex_clear_cache)(व्योम);

पूर्णांक (*__prom_अक्षर_लो)(व्योम);
अक्षर *(*__prom_दो_पर्या)(अक्षर *);
पूर्णांक (*__prom_म_लिखो)(अक्षर *, ...);

पूर्णांक (*__pmax_खोलो)(अक्षर*, पूर्णांक);
पूर्णांक (*__pmax_lseek)(पूर्णांक, दीर्घ, पूर्णांक);
पूर्णांक (*__pmax_पढ़ो)(पूर्णांक, व्योम *, पूर्णांक);
पूर्णांक (*__pmax_बंद)(पूर्णांक);


/*
 * Detect which PROM the DECSTATION has, and set the callback vectors
 * appropriately.
 */
व्योम __init which_prom(s32 magic, s32 *prom_vec)
अणु
	/*
	 * No sign of the REX PROM's magic number means we assume a non-REX
	 * machine (i.e. we're on a DS2100/3100, DS5100 or DS5000/2xx)
	 */
	अगर (prom_is_rex(magic)) अणु
		/*
		 * Set up prom असलtraction काष्ठाure with REX entry poपूर्णांकs.
		 */
		__rex_bootinit =
			(व्योम *)(दीर्घ)*(prom_vec + REX_PROM_BOOTINIT);
		__rex_bootपढ़ो =
			(व्योम *)(दीर्घ)*(prom_vec + REX_PROM_BOOTREAD);
		__rex_getbiपंचांगap =
			(व्योम *)(दीर्घ)*(prom_vec + REX_PROM_GETBITMAP);
		__prom_अक्षर_लो =
			(व्योम *)(दीर्घ)*(prom_vec + REX_PROM_GETCHAR);
		__prom_दो_पर्या =
			(व्योम *)(दीर्घ)*(prom_vec + REX_PROM_GETENV);
		__rex_माला_लोysid =
			(व्योम *)(दीर्घ)*(prom_vec + REX_PROM_GETSYSID);
		__rex_gettcinfo =
			(व्योम *)(दीर्घ)*(prom_vec + REX_PROM_GETTCINFO);
		__prom_म_लिखो =
			(व्योम *)(दीर्घ)*(prom_vec + REX_PROM_PRINTF);
		__rex_slot_address =
			(व्योम *)(दीर्घ)*(prom_vec + REX_PROM_SLOTADDR);
		__rex_clear_cache =
			(व्योम *)(दीर्घ)*(prom_vec + REX_PROM_CLEARCACHE);
	पूर्ण अन्यथा अणु
		/*
		 * Set up prom असलtraction काष्ठाure with non-REX entry poपूर्णांकs.
		 */
		__prom_अक्षर_लो = (व्योम *)PMAX_PROM_GETCHAR;
		__prom_दो_पर्या = (व्योम *)PMAX_PROM_GETENV;
		__prom_म_लिखो = (व्योम *)PMAX_PROM_PRINTF;
		__pmax_खोलो = (व्योम *)PMAX_PROM_OPEN;
		__pmax_lseek = (व्योम *)PMAX_PROM_LSEEK;
		__pmax_पढ़ो = (व्योम *)PMAX_PROM_READ;
		__pmax_बंद = (व्योम *)PMAX_PROM_CLOSE;
	पूर्ण
पूर्ण

व्योम __init prom_init(व्योम)
अणु
	बाह्य व्योम dec_machine_halt(व्योम);
	अटल स्थिर अक्षर cpu_msg[] __initस्थिर =
		"Sorry, this kernel is compiled for a wrong CPU type!\n";
	s32 argc = fw_arg0;
	s32 *argv = (व्योम *)fw_arg1;
	u32 magic = fw_arg2;
	s32 *prom_vec = (व्योम *)fw_arg3;

	/*
	 * Determine which PROM we have
	 * (and thereक्रमe which machine we're on!)
	 */
	which_prom(magic, prom_vec);

	अगर (prom_is_rex(magic))
		rex_clear_cache();

	/* Register the early console.  */
	रेजिस्टर_prom_console();

	/* Were we compiled with the right CPU option? */
#अगर defined(CONFIG_CPU_R3000)
	अगर ((current_cpu_type() == CPU_R4000SC) ||
	    (current_cpu_type() == CPU_R4400SC)) अणु
		अटल स्थिर अक्षर r4k_msg[] __initस्थिर =
			"Please recompile with \"CONFIG_CPU_R4x00 = y\".\n";
		prपूर्णांकk(cpu_msg);
		prपूर्णांकk(r4k_msg);
		dec_machine_halt();
	पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_CPU_R4X00)
	अगर ((current_cpu_type() == CPU_R3000) ||
	    (current_cpu_type() == CPU_R3000A)) अणु
		अटल स्थिर अक्षर r3k_msg[] __initस्थिर =
			"Please recompile with \"CONFIG_CPU_R3000 = y\".\n";
		prपूर्णांकk(cpu_msg);
		prपूर्णांकk(r3k_msg);
		dec_machine_halt();
	पूर्ण
#पूर्ण_अगर

	prom_meminit(magic);
	prom_identअगरy_arch(magic);
	prom_init_cmdline(argc, argv, magic);
पूर्ण
