<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * misc.c:  Miscellaneous prom functions that करोn't beदीर्घ
 *          anywhere अन्यथा.
 *
 * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)
 * Copyright (C) 1996,1997 Jakub Jelinek (jj@sunsite.mff.cuni.cz)
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>

#समावेश <यंत्र/खोलोprom.h>
#समावेश <यंत्र/oplib.h>
#समावेश <यंत्र/ldc.h>

अटल पूर्णांक prom_service_exists(स्थिर अक्षर *service_name)
अणु
	अचिन्हित दीर्घ args[5];

	args[0] = (अचिन्हित दीर्घ) "test";
	args[1] = 1;
	args[2] = 1;
	args[3] = (अचिन्हित दीर्घ) service_name;
	args[4] = (अचिन्हित दीर्घ) -1;

	p1275_cmd_direct(args);

	अगर (args[4])
		वापस 0;
	वापस 1;
पूर्ण

व्योम prom_sun4v_guest_soft_state(व्योम)
अणु
	स्थिर अक्षर *svc = "SUNW,soft-state-supported";
	अचिन्हित दीर्घ args[3];

	अगर (!prom_service_exists(svc))
		वापस;
	args[0] = (अचिन्हित दीर्घ) svc;
	args[1] = 0;
	args[2] = 0;
	p1275_cmd_direct(args);
पूर्ण

/* Reset and reboot the machine with the command 'bcommand'. */
व्योम prom_reboot(स्थिर अक्षर *bcommand)
अणु
	अचिन्हित दीर्घ args[4];

#अगर_घोषित CONFIG_SUN_LDOMS
	अगर (lकरोm_करोमुख्यing_enabled)
		lकरोm_reboot(bcommand);
#पूर्ण_अगर
	args[0] = (अचिन्हित दीर्घ) "boot";
	args[1] = 1;
	args[2] = 0;
	args[3] = (अचिन्हित दीर्घ) bcommand;

	p1275_cmd_direct(args);
पूर्ण

/* Forth evaluate the expression contained in 'fstring'. */
व्योम prom_feval(स्थिर अक्षर *fstring)
अणु
	अचिन्हित दीर्घ args[5];

	अगर (!fstring || fstring[0] == 0)
		वापस;
	args[0] = (अचिन्हित दीर्घ) "interpret";
	args[1] = 1;
	args[2] = 1;
	args[3] = (अचिन्हित दीर्घ) fstring;
	args[4] = (अचिन्हित दीर्घ) -1;

	p1275_cmd_direct(args);
पूर्ण
EXPORT_SYMBOL(prom_feval);

/* Drop पूर्णांकo the prom, with the chance to जारी with the 'go'
 * prom command.
 */
व्योम prom_cmdline(व्योम)
अणु
	अचिन्हित दीर्घ args[3];
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);

#अगर_घोषित CONFIG_SMP
	smp_capture();
#पूर्ण_अगर

	args[0] = (अचिन्हित दीर्घ) "enter";
	args[1] = 0;
	args[2] = 0;

	p1275_cmd_direct(args);

#अगर_घोषित CONFIG_SMP
	smp_release();
#पूर्ण_अगर

	local_irq_restore(flags);
पूर्ण

/* Drop पूर्णांकo the prom, but completely terminate the program.
 * No chance of continuing.
 */
व्योम notrace prom_halt(व्योम)
अणु
	अचिन्हित दीर्घ args[3];

#अगर_घोषित CONFIG_SUN_LDOMS
	अगर (lकरोm_करोमुख्यing_enabled)
		lकरोm_घातer_off();
#पूर्ण_अगर
again:
	args[0] = (अचिन्हित दीर्घ) "exit";
	args[1] = 0;
	args[2] = 0;
	p1275_cmd_direct(args);
	जाओ again; /* PROM is out to get me -DaveM */
पूर्ण

व्योम prom_halt_घातer_off(व्योम)
अणु
	अचिन्हित दीर्घ args[3];

#अगर_घोषित CONFIG_SUN_LDOMS
	अगर (lकरोm_करोमुख्यing_enabled)
		lकरोm_घातer_off();
#पूर्ण_अगर
	args[0] = (अचिन्हित दीर्घ) "SUNW,power-off";
	args[1] = 0;
	args[2] = 0;
	p1275_cmd_direct(args);

	/* अगर nothing अन्यथा helps, we just halt */
	prom_halt();
पूर्ण

/* Get the idprom and stuff it पूर्णांकo buffer 'idbuf'.  Returns the
 * क्रमmat type.  'num_bytes' is the number of bytes that your idbuf
 * has space क्रम.  Returns 0xff on error.
 */
अचिन्हित अक्षर prom_get_idprom(अक्षर *idbuf, पूर्णांक num_bytes)
अणु
	पूर्णांक len;

	len = prom_getproplen(prom_root_node, "idprom");
	अगर ((len >num_bytes) || (len == -1))
		वापस 0xff;
	अगर (!prom_getproperty(prom_root_node, "idprom", idbuf, num_bytes))
		वापस idbuf[0];

	वापस 0xff;
पूर्ण

पूर्णांक prom_get_mmu_ihandle(व्योम)
अणु
	phandle node;
	पूर्णांक ret;

	अगर (prom_mmu_ihandle_cache != 0)
		वापस prom_mmu_ihandle_cache;

	node = prom_finddevice(prom_chosen_path);
	ret = prom_getपूर्णांक(node, prom_mmu_name);
	अगर (ret == -1 || ret == 0)
		prom_mmu_ihandle_cache = -1;
	अन्यथा
		prom_mmu_ihandle_cache = ret;

	वापस ret;
पूर्ण

अटल पूर्णांक prom_get_memory_ihandle(व्योम)
अणु
	अटल पूर्णांक memory_ihandle_cache;
	phandle node;
	पूर्णांक ret;

	अगर (memory_ihandle_cache != 0)
		वापस memory_ihandle_cache;

	node = prom_finddevice("/chosen");
	ret = prom_getपूर्णांक(node, "memory");
	अगर (ret == -1 || ret == 0)
		memory_ihandle_cache = -1;
	अन्यथा
		memory_ihandle_cache = ret;

	वापस ret;
पूर्ण

/* Load explicit I/D TLB entries. */
अटल दीर्घ tlb_load(स्थिर अक्षर *type, अचिन्हित दीर्घ index,
		     अचिन्हित दीर्घ tte_data, अचिन्हित दीर्घ vaddr)
अणु
	अचिन्हित दीर्घ args[9];

	args[0] = (अचिन्हित दीर्घ) prom_callmethod_name;
	args[1] = 5;
	args[2] = 1;
	args[3] = (अचिन्हित दीर्घ) type;
	args[4] = (अचिन्हित पूर्णांक) prom_get_mmu_ihandle();
	args[5] = vaddr;
	args[6] = tte_data;
	args[7] = index;
	args[8] = (अचिन्हित दीर्घ) -1;

	p1275_cmd_direct(args);

	वापस (दीर्घ) args[8];
पूर्ण

दीर्घ prom_itlb_load(अचिन्हित दीर्घ index,
		    अचिन्हित दीर्घ tte_data,
		    अचिन्हित दीर्घ vaddr)
अणु
	वापस tlb_load("SUNW,itlb-load", index, tte_data, vaddr);
पूर्ण

दीर्घ prom_dtlb_load(अचिन्हित दीर्घ index,
		    अचिन्हित दीर्घ tte_data,
		    अचिन्हित दीर्घ vaddr)
अणु
	वापस tlb_load("SUNW,dtlb-load", index, tte_data, vaddr);
पूर्ण

पूर्णांक prom_map(पूर्णांक mode, अचिन्हित दीर्घ size,
	     अचिन्हित दीर्घ vaddr, अचिन्हित दीर्घ paddr)
अणु
	अचिन्हित दीर्घ args[11];
	पूर्णांक ret;

	args[0] = (अचिन्हित दीर्घ) prom_callmethod_name;
	args[1] = 7;
	args[2] = 1;
	args[3] = (अचिन्हित दीर्घ) prom_map_name;
	args[4] = (अचिन्हित पूर्णांक) prom_get_mmu_ihandle();
	args[5] = (अचिन्हित पूर्णांक) mode;
	args[6] = size;
	args[7] = vaddr;
	args[8] = 0;
	args[9] = paddr;
	args[10] = (अचिन्हित दीर्घ) -1;

	p1275_cmd_direct(args);

	ret = (पूर्णांक) args[10];
	अगर (ret == 0)
		ret = -1;
	वापस ret;
पूर्ण

व्योम prom_unmap(अचिन्हित दीर्घ size, अचिन्हित दीर्घ vaddr)
अणु
	अचिन्हित दीर्घ args[7];

	args[0] = (अचिन्हित दीर्घ) prom_callmethod_name;
	args[1] = 4;
	args[2] = 0;
	args[3] = (अचिन्हित दीर्घ) prom_unmap_name;
	args[4] = (अचिन्हित पूर्णांक) prom_get_mmu_ihandle();
	args[5] = size;
	args[6] = vaddr;

	p1275_cmd_direct(args);
पूर्ण

/* Set aside physical memory which is not touched or modअगरied
 * across soft resets.
 */
पूर्णांक prom_retain(स्थिर अक्षर *name, अचिन्हित दीर्घ size,
		अचिन्हित दीर्घ align, अचिन्हित दीर्घ *paddr)
अणु
	अचिन्हित दीर्घ args[11];

	args[0] = (अचिन्हित दीर्घ) prom_callmethod_name;
	args[1] = 5;
	args[2] = 3;
	args[3] = (अचिन्हित दीर्घ) "SUNW,retain";
	args[4] = (अचिन्हित पूर्णांक) prom_get_memory_ihandle();
	args[5] = align;
	args[6] = size;
	args[7] = (अचिन्हित दीर्घ) name;
	args[8] = (अचिन्हित दीर्घ) -1;
	args[9] = (अचिन्हित दीर्घ) -1;
	args[10] = (अचिन्हित दीर्घ) -1;

	p1275_cmd_direct(args);

	अगर (args[8])
		वापस (पूर्णांक) args[8];

	/* Next we get "phys_high" then "phys_low".  On 64-bit
	 * the phys_high cell is करोn't care since the phys_low
	 * cell has the full value.
	 */
	*paddr = args[10];

	वापस 0;
पूर्ण

/* Get "Unumber" string क्रम the SIMM at the given
 * memory address.  Usually this will be of the क्रमm
 * "Uxxxx" where xxxx is a decimal number which is
 * etched पूर्णांकo the motherboard next to the SIMM slot
 * in question.
 */
पूर्णांक prom_getunumber(पूर्णांक syndrome_code,
		    अचिन्हित दीर्घ phys_addr,
		    अक्षर *buf, पूर्णांक buflen)
अणु
	अचिन्हित दीर्घ args[12];

	args[0] = (अचिन्हित दीर्घ) prom_callmethod_name;
	args[1] = 7;
	args[2] = 2;
	args[3] = (अचिन्हित दीर्घ) "SUNW,get-unumber";
	args[4] = (अचिन्हित पूर्णांक) prom_get_memory_ihandle();
	args[5] = buflen;
	args[6] = (अचिन्हित दीर्घ) buf;
	args[7] = 0;
	args[8] = phys_addr;
	args[9] = (अचिन्हित पूर्णांक) syndrome_code;
	args[10] = (अचिन्हित दीर्घ) -1;
	args[11] = (अचिन्हित दीर्घ) -1;

	p1275_cmd_direct(args);

	वापस (पूर्णांक) args[10];
पूर्ण

/* Power management extensions. */
व्योम prom_sleepself(व्योम)
अणु
	अचिन्हित दीर्घ args[3];

	args[0] = (अचिन्हित दीर्घ) "SUNW,sleep-self";
	args[1] = 0;
	args[2] = 0;
	p1275_cmd_direct(args);
पूर्ण

पूर्णांक prom_sleepप्रणाली(व्योम)
अणु
	अचिन्हित दीर्घ args[4];

	args[0] = (अचिन्हित दीर्घ) "SUNW,sleep-system";
	args[1] = 0;
	args[2] = 1;
	args[3] = (अचिन्हित दीर्घ) -1;
	p1275_cmd_direct(args);

	वापस (पूर्णांक) args[3];
पूर्ण

पूर्णांक prom_wakeupप्रणाली(व्योम)
अणु
	अचिन्हित दीर्घ args[4];

	args[0] = (अचिन्हित दीर्घ) "SUNW,wakeup-system";
	args[1] = 0;
	args[2] = 1;
	args[3] = (अचिन्हित दीर्घ) -1;
	p1275_cmd_direct(args);

	वापस (पूर्णांक) args[3];
पूर्ण

#अगर_घोषित CONFIG_SMP
व्योम prom_startcpu(पूर्णांक cpunode, अचिन्हित दीर्घ pc, अचिन्हित दीर्घ arg)
अणु
	अचिन्हित दीर्घ args[6];

	args[0] = (अचिन्हित दीर्घ) "SUNW,start-cpu";
	args[1] = 3;
	args[2] = 0;
	args[3] = (अचिन्हित पूर्णांक) cpunode;
	args[4] = pc;
	args[5] = arg;
	p1275_cmd_direct(args);
पूर्ण

व्योम prom_startcpu_cpuid(पूर्णांक cpuid, अचिन्हित दीर्घ pc, अचिन्हित दीर्घ arg)
अणु
	अचिन्हित दीर्घ args[6];

	args[0] = (अचिन्हित दीर्घ) "SUNW,start-cpu-by-cpuid";
	args[1] = 3;
	args[2] = 0;
	args[3] = (अचिन्हित पूर्णांक) cpuid;
	args[4] = pc;
	args[5] = arg;
	p1275_cmd_direct(args);
पूर्ण

व्योम prom_stopcpu_cpuid(पूर्णांक cpuid)
अणु
	अचिन्हित दीर्घ args[4];

	args[0] = (अचिन्हित दीर्घ) "SUNW,stop-cpu-by-cpuid";
	args[1] = 1;
	args[2] = 0;
	args[3] = (अचिन्हित पूर्णांक) cpuid;
	p1275_cmd_direct(args);
पूर्ण

व्योम prom_stopself(व्योम)
अणु
	अचिन्हित दीर्घ args[3];

	args[0] = (अचिन्हित दीर्घ) "SUNW,stop-self";
	args[1] = 0;
	args[2] = 0;
	p1275_cmd_direct(args);
पूर्ण

व्योम prom_idleself(व्योम)
अणु
	अचिन्हित दीर्घ args[3];

	args[0] = (अचिन्हित दीर्घ) "SUNW,idle-self";
	args[1] = 0;
	args[2] = 0;
	p1275_cmd_direct(args);
पूर्ण

व्योम prom_resumecpu(पूर्णांक cpunode)
अणु
	अचिन्हित दीर्घ args[4];

	args[0] = (अचिन्हित दीर्घ) "SUNW,resume-cpu";
	args[1] = 1;
	args[2] = 0;
	args[3] = (अचिन्हित पूर्णांक) cpunode;
	p1275_cmd_direct(args);
पूर्ण
#पूर्ण_अगर
