<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * PROM library initialisation code.
 *
 * Copyright (C) 1996 David S. Miller (davem@davemloft.net)
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>

#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/sgialib.h>
#समावेश <यंत्र/smp-ops.h>

#अघोषित DEBUG_PROM_INIT

/* Master romvec पूर्णांकerface. */
काष्ठा linux_romvec *romvec;

#अगर defined(CONFIG_64BIT) && defined(CONFIG_FW_ARC32)
/* stack क्रम calling 32bit ARC prom */
u64 o32_stk[4096];
#पूर्ण_अगर

व्योम __init prom_init(व्योम)
अणु
	PSYSTEM_PARAMETER_BLOCK pb = PROMBLOCK;

	romvec = ROMVECTOR;

	अगर (pb->magic != 0x53435241) अणु
		prपूर्णांकk(KERN_CRIT "Aieee, bad prom vector magic %08lx\n",
		       (अचिन्हित दीर्घ) pb->magic);
		जबतक(1)
			;
	पूर्ण

	prom_init_cmdline(fw_arg0, (LONG *)fw_arg1);
	prom_identअगरy_arch();
	prपूर्णांकk(KERN_INFO "PROMLIB: ARC firmware Version %d Revision %d\n",
	       pb->ver, pb->rev);
	prom_meminit();

#अगर_घोषित DEBUG_PROM_INIT
	pr_info("Press a key to reboot\n");
	ArcRead(0, &c, 1, &cnt);
	ArcEnterInteractiveMode();
#पूर्ण_अगर
पूर्ण
