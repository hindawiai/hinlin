<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2000, 2001, 2002, 2003 Broadcom Corporation
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/linkage.h>
#समावेश <linux/mm.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/memblock.h>
#समावेश <linux/pm.h>
#समावेश <linux/smp.h>

#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/reboot.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/sibyte/board.h>
#समावेश <यंत्र/smp-ops.h>

#समावेश <यंत्र/fw/cfe/cfe_api.h>
#समावेश <यंत्र/fw/cfe/cfe_error.h>

/* Max ram addressable in 32-bit segments */
#अगर_घोषित CONFIG_64BIT
#घोषणा MAX_RAM_SIZE (~0ULL)
#अन्यथा
#अगर_घोषित CONFIG_HIGHMEM
#अगर_घोषित CONFIG_PHYS_ADDR_T_64BIT
#घोषणा MAX_RAM_SIZE (~0ULL)
#अन्यथा
#घोषणा MAX_RAM_SIZE (0xffffffffULL)
#पूर्ण_अगर
#अन्यथा
#घोषणा MAX_RAM_SIZE (0x1fffffffULL)
#पूर्ण_अगर
#पूर्ण_अगर

#घोषणा SIBYTE_MAX_MEM_REGIONS 8
phys_addr_t board_mem_region_addrs[SIBYTE_MAX_MEM_REGIONS];
phys_addr_t board_mem_region_sizes[SIBYTE_MAX_MEM_REGIONS];
अचिन्हित पूर्णांक board_mem_region_count;

पूर्णांक cfe_cons_handle;

#अगर_घोषित CONFIG_BLK_DEV_INITRD
बाह्य अचिन्हित दीर्घ initrd_start, initrd_end;
#पूर्ण_अगर

अटल व्योम __noवापस cfe_linux_निकास(व्योम *arg)
अणु
	पूर्णांक warm = *(पूर्णांक *)arg;

	अगर (smp_processor_id()) अणु
		अटल पूर्णांक reboot_smp;

		/* Don't repeat the process from another CPU */
		अगर (!reboot_smp) अणु
			/* Get CPU 0 to करो the cfe_निकास */
			reboot_smp = 1;
			smp_call_function(cfe_linux_निकास, arg, 0);
		पूर्ण
	पूर्ण अन्यथा अणु
		prपूर्णांकk("Passing control back to CFE...\n");
		cfe_निकास(warm, 0);
		prपूर्णांकk("cfe_exit returned??\n");
	पूर्ण
	जबतक (1);
पूर्ण

अटल व्योम __noवापस cfe_linux_restart(अक्षर *command)
अणु
	अटल स्थिर पूर्णांक zero;

	cfe_linux_निकास((व्योम *)&zero);
पूर्ण

अटल व्योम __noवापस cfe_linux_halt(व्योम)
अणु
	अटल स्थिर पूर्णांक one = 1;

	cfe_linux_निकास((व्योम *)&one);
पूर्ण

अटल __init व्योम prom_meminit(व्योम)
अणु
	u64 addr, size, type; /* regardless of PHYS_ADDR_T_64BIT */
	पूर्णांक mem_flags = 0;
	अचिन्हित पूर्णांक idx;
	पूर्णांक rd_flag;
#अगर_घोषित CONFIG_BLK_DEV_INITRD
	अचिन्हित दीर्घ initrd_pstart;
	अचिन्हित दीर्घ initrd_pend;

	initrd_pstart = CPHYSADDR(initrd_start);
	initrd_pend = CPHYSADDR(initrd_end);
	अगर (initrd_start &&
	    ((initrd_pstart > MAX_RAM_SIZE)
	     || (initrd_pend > MAX_RAM_SIZE))) अणु
		panic("initrd out of addressable memory");
	पूर्ण

#पूर्ण_अगर /* INITRD */

	क्रम (idx = 0; cfe_क्रमागतmem(idx, mem_flags, &addr, &size, &type) != CFE_ERR_NOMORE;
	     idx++) अणु
		rd_flag = 0;
		अगर (type == CFE_MI_AVAILABLE) अणु
			/*
			 * See अगर this block contains (any portion of) the
			 * ramdisk
			 */
#अगर_घोषित CONFIG_BLK_DEV_INITRD
			अगर (initrd_start) अणु
				अगर ((initrd_pstart > addr) &&
				    (initrd_pstart < (addr + size))) अणु
					memblock_add(addr,
						     initrd_pstart - addr);
					rd_flag = 1;
				पूर्ण
				अगर ((initrd_pend > addr) &&
				    (initrd_pend < (addr + size))) अणु
					memblock_add(initrd_pend,
						(addr + size) - initrd_pend);
					rd_flag = 1;
				पूर्ण
			पूर्ण
#पूर्ण_अगर
			अगर (!rd_flag) अणु
				अगर (addr > MAX_RAM_SIZE)
					जारी;
				अगर (addr+size > MAX_RAM_SIZE)
					size = MAX_RAM_SIZE - (addr+size) + 1;
				/*
				 * स_नकल/__copy_user prefetch, which
				 * will cause a bus error क्रम
				 * KSEG/KUSEG addrs not backed by RAM.
				 * Hence, reserve some padding क्रम the
				 * prefetch distance.
				 */
				अगर (size > 512)
					size -= 512;
				memblock_add(addr, size);
			पूर्ण
			board_mem_region_addrs[board_mem_region_count] = addr;
			board_mem_region_sizes[board_mem_region_count] = size;
			board_mem_region_count++;
			अगर (board_mem_region_count ==
			    SIBYTE_MAX_MEM_REGIONS) अणु
				/*
				 * Too many regions.  Need to configure more
				 */
				जबतक(1);
			पूर्ण
		पूर्ण
	पूर्ण
#अगर_घोषित CONFIG_BLK_DEV_INITRD
	अगर (initrd_start) अणु
		memblock_add(initrd_pstart, initrd_pend - initrd_pstart);
		memblock_reserve(initrd_pstart, initrd_pend - initrd_pstart);
	पूर्ण
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_BLK_DEV_INITRD
अटल पूर्णांक __init initrd_setup(अक्षर *str)
अणु
	अक्षर rdarg[64];
	पूर्णांक idx;
	अक्षर *पंचांगp, *endptr;
	अचिन्हित दीर्घ initrd_size;

	/* Make a copy of the initrd argument so we can smash it up here */
	क्रम (idx = 0; idx < माप(rdarg)-1; idx++) अणु
		अगर (!str[idx] || (str[idx] == ' ')) अवरोध;
		rdarg[idx] = str[idx];
	पूर्ण

	rdarg[idx] = 0;
	str = rdarg;

	/*
	 *Initrd location comes in the क्रमm "<hex size of ramdisk in bytes>@<location in memory>"
	 *  e.g. initrd=3abfd@80010000.	 This is set up by the loader.
	 */
	क्रम (पंचांगp = str; *पंचांगp != '@'; पंचांगp++) अणु
		अगर (!*पंचांगp) अणु
			जाओ fail;
		पूर्ण
	पूर्ण
	*पंचांगp = 0;
	पंचांगp++;
	अगर (!*पंचांगp) अणु
		जाओ fail;
	पूर्ण
	initrd_size = simple_म_से_अदीर्घ(str, &endptr, 16);
	अगर (*endptr) अणु
		*(पंचांगp-1) = '@';
		जाओ fail;
	पूर्ण
	*(पंचांगp-1) = '@';
	initrd_start = simple_म_से_अदीर्घ(पंचांगp, &endptr, 16);
	अगर (*endptr) अणु
		जाओ fail;
	पूर्ण
	initrd_end = initrd_start + initrd_size;
	prपूर्णांकk("Found initrd of %lx@%lx\n", initrd_size, initrd_start);
	वापस 1;
 fail:
	prपूर्णांकk("Bad initrd argument.  Disabling initrd\n");
	initrd_start = 0;
	initrd_end = 0;
	वापस 1;
पूर्ण

#पूर्ण_अगर

बाह्य स्थिर काष्ठा plat_smp_ops sb_smp_ops;
बाह्य स्थिर काष्ठा plat_smp_ops bcm1480_smp_ops;

/*
 * prom_init is called just after the cpu type is determined, from setup_arch()
 */
व्योम __init prom_init(व्योम)
अणु
	uपूर्णांक64_t cfe_ept, cfe_handle;
	अचिन्हित पूर्णांक cfe_eptseal;
	पूर्णांक argc = fw_arg0;
	अक्षर **envp = (अक्षर **) fw_arg2;
	पूर्णांक *prom_vec = (पूर्णांक *) fw_arg3;

	_machine_restart   = cfe_linux_restart;
	_machine_halt	   = cfe_linux_halt;
	pm_घातer_off = cfe_linux_halt;

	/*
	 * Check अगर a loader was used; अगर NOT, the 4 arguments are
	 * what CFE gives us (handle, 0, EPT and EPTSEAL)
	 */
	अगर (argc < 0) अणु
		cfe_handle = (uपूर्णांक64_t)(दीर्घ)argc;
		cfe_ept = (दीर्घ)envp;
		cfe_eptseal = (uपूर्णांक32_t)(अचिन्हित दीर्घ)prom_vec;
	पूर्ण अन्यथा अणु
		अगर ((पूर्णांक32_t)(दीर्घ)prom_vec < 0) अणु
			/*
			 * Old loader; all it gives us is the handle,
			 * so use the "known" entrypoपूर्णांक and assume
			 * the seal.
			 */
			cfe_handle = (uपूर्णांक64_t)(दीर्घ)prom_vec;
			cfe_ept = (uपूर्णांक64_t)((पूर्णांक32_t)0x9fc00500);
			cfe_eptseal = CFE_EPTSEAL;
		पूर्ण अन्यथा अणु
			/*
			 * Newer loaders bundle the handle/ept/eptseal
			 * Note: prom_vec is in the loader's useg
			 * which is still alive in the TLB.
			 */
			cfe_handle = (uपूर्णांक64_t)((पूर्णांक32_t *)prom_vec)[0];
			cfe_ept = (uपूर्णांक64_t)((पूर्णांक32_t *)prom_vec)[2];
			cfe_eptseal = (अचिन्हित पूर्णांक)((uपूर्णांक32_t *)prom_vec)[3];
		पूर्ण
	पूर्ण
	अगर (cfe_eptseal != CFE_EPTSEAL) अणु
		/* too early क्रम panic to करो any good */
		prपूर्णांकk("CFE's entrypoint seal doesn't match. Spinning.");
		जबतक (1) ;
	पूर्ण
	cfe_init(cfe_handle, cfe_ept);
	/*
	 * Get the handle क्रम (at least) prom_अक्षर_दो, possibly क्रम
	 * boot console
	 */
	cfe_cons_handle = cfe_माला_लोtdhandle(CFE_STDHANDLE_CONSOLE);
	अगर (cfe_दो_पर्या("LINUX_CMDLINE", arcs_cmdline, COMMAND_LINE_SIZE) < 0) अणु
		अगर (argc >= 0) अणु
			/* The loader should have set the command line */
			/* too early क्रम panic to करो any good */
			prपूर्णांकk("LINUX_CMDLINE not defined in cfe.");
			जबतक (1) ;
		पूर्ण
	पूर्ण

#अगर_घोषित CONFIG_BLK_DEV_INITRD
	अणु
		अक्षर *ptr;
		/* Need to find out early whether we've got an initrd.	So scan
		   the list looking now */
		क्रम (ptr = arcs_cmdline; *ptr; ptr++) अणु
			जबतक (*ptr == ' ') अणु
				ptr++;
			पूर्ण
			अगर (!म_भेदन(ptr, "initrd=", 7)) अणु
				initrd_setup(ptr+7);
				अवरोध;
			पूर्ण अन्यथा अणु
				जबतक (*ptr && (*ptr != ' ')) अणु
					ptr++;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
#पूर्ण_अगर /* CONFIG_BLK_DEV_INITRD */

	/* Not sure this is needed, but it's the safe way. */
	arcs_cmdline[COMMAND_LINE_SIZE-1] = 0;

	prom_meminit();

#अगर defined(CONFIG_SIBYTE_BCM112X) || defined(CONFIG_SIBYTE_SB1250)
	रेजिस्टर_smp_ops(&sb_smp_ops);
#पूर्ण_अगर
#अगर defined(CONFIG_SIBYTE_BCM1x55) || defined(CONFIG_SIBYTE_BCM1x80)
	रेजिस्टर_smp_ops(&bcm1480_smp_ops);
#पूर्ण_अगर
पूर्ण

व्योम prom_अक्षर_दो(अक्षर c)
अणु
	पूर्णांक ret;

	जबतक ((ret = cfe_ग_लिखो(cfe_cons_handle, &c, 1)) == 0)
		;
पूर्ण
