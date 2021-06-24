<शैली गुरु>
/*
 *  linux/arch/m68k/sun3/config.c
 *
 *  Copyright (C) 1996,1997 Pekka Pietikअणुinen
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/tty.h>
#समावेश <linux/console.h>
#समावेश <linux/init.h>
#समावेश <linux/memblock.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <यंत्र/oplib.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/contregs.h>
#समावेश <यंत्र/movs.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/sun3-head.h>
#समावेश <यंत्र/sun3mmu.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/machines.h>
#समावेश <यंत्र/idprom.h>
#समावेश <यंत्र/पूर्णांकersil.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/segment.h>
#समावेश <यंत्र/sun3पूर्णांकs.h>

अक्षर sun3_reserved_pmeg[SUN3_PMEGS_NUM];

अटल व्योम sun3_sched_init(व्योम);
बाह्य व्योम sun3_get_model (अक्षर* model);
बाह्य पूर्णांक sun3_hwclk(पूर्णांक set, काष्ठा rtc_समय *t);

अस्थिर अक्षर* घड़ी_va;
बाह्य अचिन्हित दीर्घ availmem;
अचिन्हित दीर्घ num_pages;

अटल व्योम sun3_get_hardware_list(काष्ठा seq_file *m)
अणु
	seq_म_लिखो(m, "PROM Revision:\t%s\n", romvec->pv_monid);
पूर्ण

व्योम __init sun3_init(व्योम)
अणु
	अचिन्हित अक्षर enable_रेजिस्टर;
	पूर्णांक i;

	m68k_machtype= MACH_SUN3;
	m68k_cputype = CPU_68020;
	m68k_fputype = FPU_68881; /* mc68881 actually */
	m68k_mmutype = MMU_SUN3;
	घड़ी_va    =          (अक्षर *) 0xfe06000;	/* dark  */
	sun3_पूर्णांकreg = (अचिन्हित अक्षर *) 0xfe0a000;	/* magic */
	sun3_disable_पूर्णांकerrupts();

	prom_init((व्योम *)LINUX_OPPROM_BEGVM);

	GET_CONTROL_BYTE(AC_SENABLE,enable_रेजिस्टर);
	enable_रेजिस्टर |= 0x50; /* Enable FPU */
	SET_CONTROL_BYTE(AC_SENABLE,enable_रेजिस्टर);
	GET_CONTROL_BYTE(AC_SENABLE,enable_रेजिस्टर);

	/* This code looks suspicious, because it करोesn't subtract
           memory beदीर्घing to the kernel from the available space */


	स_रखो(sun3_reserved_pmeg, 0, माप(sun3_reserved_pmeg));

	/* Reserve important PMEGS */
	/* FIXME: These should be probed instead of hardcoded */

	क्रम (i=0; i<8; i++)		/* Kernel PMEGs */
		sun3_reserved_pmeg[i] = 1;

	sun3_reserved_pmeg[247] = 1;	/* ROM mapping  */
	sun3_reserved_pmeg[248] = 1;	/* AMD Ethernet */
	sun3_reserved_pmeg[251] = 1;	/* VB area      */
	sun3_reserved_pmeg[254] = 1;	/* मुख्य I/O     */

	sun3_reserved_pmeg[249] = 1;
	sun3_reserved_pmeg[252] = 1;
	sun3_reserved_pmeg[253] = 1;
	set_fs(KERNEL_DS);
पूर्ण

/* Without this, Bad Things happen when something calls arch_reset. */
अटल व्योम sun3_reboot (व्योम)
अणु
	prom_reboot ("vmlinux");
पूर्ण

अटल व्योम sun3_halt (व्योम)
अणु
	prom_halt ();
पूर्ण

/* sun3 booपंचांगem allocation */

अटल व्योम __init sun3_booपंचांगem_alloc(अचिन्हित दीर्घ memory_start,
				      अचिन्हित दीर्घ memory_end)
अणु
	अचिन्हित दीर्घ start_page;

	/* align start/end to page boundaries */
	memory_start = ((memory_start + (PAGE_SIZE-1)) & PAGE_MASK);
	memory_end = memory_end & PAGE_MASK;

	start_page = __pa(memory_start) >> PAGE_SHIFT;
	max_pfn = num_pages = __pa(memory_end) >> PAGE_SHIFT;

	high_memory = (व्योम *)memory_end;
	availmem = memory_start;

	m68k_setup_node(0);
पूर्ण


व्योम __init config_sun3(व्योम)
अणु
	अचिन्हित दीर्घ memory_start, memory_end;

	pr_info("ARCH: SUN3\n");
	idprom_init();

	/* Subtract kernel memory from available memory */

        mach_sched_init      =  sun3_sched_init;
        mach_init_IRQ        =  sun3_init_IRQ;
        mach_reset           =  sun3_reboot;
	mach_get_model	     =  sun3_get_model;
	mach_hwclk           =  sun3_hwclk;
	mach_halt	     =  sun3_halt;
	mach_get_hardware_list = sun3_get_hardware_list;

	memory_start = ((((अचिन्हित दीर्घ)_end) + 0x2000) & ~0x1fff);
// PROM seems to want the last couple of physical pages. --m
	memory_end   = *(romvec->pv_sun3mem) + PAGE_OFFSET - 2*PAGE_SIZE;

	m68k_num_memory=1;
        m68k_memory[0].size=*(romvec->pv_sun3mem);

	sun3_booपंचांगem_alloc(memory_start, memory_end);
पूर्ण

अटल व्योम __init sun3_sched_init(व्योम)
अणु
	sun3_disable_पूर्णांकerrupts();
        पूर्णांकersil_घड़ी->cmd_reg=(INTERSIL_RUN|INTERSIL_INT_DISABLE|INTERSIL_24H_MODE);
        पूर्णांकersil_घड़ी->पूर्णांक_reg=INTERSIL_HZ_100_MASK;
	पूर्णांकersil_clear();
        sun3_enable_irq(5);
        पूर्णांकersil_घड़ी->cmd_reg=(INTERSIL_RUN|INTERSIL_INT_ENABLE|INTERSIL_24H_MODE);
        sun3_enable_पूर्णांकerrupts();
        पूर्णांकersil_clear();
पूर्ण

#अगर IS_ENABLED(CONFIG_SUN3_SCSI)

अटल स्थिर काष्ठा resource sun3_scsi_vme_rsrc[] __initस्थिर = अणु
	अणु
		.flags = IORESOURCE_IRQ,
		.start = SUN3_VEC_VMESCSI0,
		.end   = SUN3_VEC_VMESCSI0,
	पूर्ण, अणु
		.flags = IORESOURCE_MEM,
		.start = 0xff200000,
		.end   = 0xff200021,
	पूर्ण, अणु
		.flags = IORESOURCE_IRQ,
		.start = SUN3_VEC_VMESCSI1,
		.end   = SUN3_VEC_VMESCSI1,
	पूर्ण, अणु
		.flags = IORESOURCE_MEM,
		.start = 0xff204000,
		.end   = 0xff204021,
	पूर्ण,
पूर्ण;

/*
 * Int: level 2 स्वतःvector
 * IO: type 1, base 0x00140000, 5 bits phys space: A<4..0>
 */
अटल स्थिर काष्ठा resource sun3_scsi_rsrc[] __initस्थिर = अणु
	अणु
		.flags = IORESOURCE_IRQ,
		.start = 2,
		.end   = 2,
	पूर्ण, अणु
		.flags = IORESOURCE_MEM,
		.start = 0x00140000,
		.end   = 0x0014001f,
	पूर्ण,
पूर्ण;

पूर्णांक __init sun3_platक्रमm_init(व्योम)
अणु
	चयन (idprom->id_machtype) अणु
	हाल SM_SUN3 | SM_3_160:
	हाल SM_SUN3 | SM_3_260:
		platक्रमm_device_रेजिस्टर_simple("sun3_scsi_vme", -1,
			sun3_scsi_vme_rsrc, ARRAY_SIZE(sun3_scsi_vme_rsrc));
		अवरोध;
	हाल SM_SUN3 | SM_3_50:
	हाल SM_SUN3 | SM_3_60:
		platक्रमm_device_रेजिस्टर_simple("sun3_scsi", -1,
			sun3_scsi_rsrc, ARRAY_SIZE(sun3_scsi_rsrc));
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

arch_initcall(sun3_platक्रमm_init);

#पूर्ण_अगर
