<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * init.c:  Initialize पूर्णांकernal variables used by the PROM
 *          library functions.
 *
 * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)
 * Copyright (C) 1998 Jakub Jelinek (jj@sunsite.mff.cuni.cz)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>

#समावेश <यंत्र/खोलोprom.h>
#समावेश <यंत्र/oplib.h>

काष्ठा linux_romvec *romvec;
EXPORT_SYMBOL(romvec);

क्रमागत prom_major_version prom_vers;
अचिन्हित पूर्णांक prom_rev, prom_prev;

/* The root node of the prom device tree. */
phandle prom_root_node;
EXPORT_SYMBOL(prom_root_node);

/* Poपूर्णांकer to the device tree operations काष्ठाure. */
काष्ठा linux_nodeops *prom_nodeops;

/* You must call prom_init() beक्रमe you attempt to use any of the
 * routines in the prom library.
 * It माला_लो passed the poपूर्णांकer to the PROM vector.
 */

व्योम __init prom_init(काष्ठा linux_romvec *rp)
अणु
	romvec = rp;

	चयन(romvec->pv_romvers) अणु
	हाल 0:
		prom_vers = PROM_V0;
		अवरोध;
	हाल 2:
		prom_vers = PROM_V2;
		अवरोध;
	हाल 3:
		prom_vers = PROM_V3;
		अवरोध;
	शेष:
		prom_म_लिखो("PROMLIB: Bad PROM version %d\n",
			    romvec->pv_romvers);
		prom_halt();
		अवरोध;
	पूर्ण

	prom_rev = romvec->pv_plugin_revision;
	prom_prev = romvec->pv_prपूर्णांकrev;
	prom_nodeops = romvec->pv_nodeops;

	prom_root_node = prom_माला_लोibling(0);
	अगर ((prom_root_node == 0) || ((s32)prom_root_node == -1))
		prom_halt();

	अगर((((अचिन्हित दीर्घ) prom_nodeops) == 0) || 
	   (((अचिन्हित दीर्घ) prom_nodeops) == -1))
		prom_halt();

	prom_meminit();

	prom_ranges_init();

	prपूर्णांकk("PROMLIB: Sun Boot Prom Version %d Revision %d\n",
	       romvec->pv_romvers, prom_rev);

	/* Initialization successful. */
पूर्ण
