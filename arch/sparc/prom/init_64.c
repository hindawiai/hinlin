<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * init.c:  Initialize पूर्णांकernal variables used by the PROM
 *          library functions.
 *
 * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)
 * Copyright (C) 1996,1997 Jakub Jelinek (jj@sunsite.mff.cuni.cz)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/माला.स>
#समावेश <linux/प्रकार.स>

#समावेश <यंत्र/खोलोprom.h>
#समावेश <यंत्र/oplib.h>

/* OBP version string. */
अक्षर prom_version[80];

/* The root node of the prom device tree. */
पूर्णांक prom_मानक_निकास;
phandle prom_chosen_node;

/* You must call prom_init() beक्रमe you attempt to use any of the
 * routines in the prom library.
 * It माला_लो passed the poपूर्णांकer to the PROM vector.
 */

बाह्य व्योम prom_cअगर_init(व्योम *);

व्योम __init prom_init(व्योम *cअगर_handler)
अणु
	phandle node;

	prom_cअगर_init(cअगर_handler);

	prom_chosen_node = prom_finddevice(prom_chosen_path);
	अगर (!prom_chosen_node || (s32)prom_chosen_node == -1)
		prom_halt();

	prom_मानक_निकास = prom_getपूर्णांक(prom_chosen_node, "stdout");

	node = prom_finddevice("/openprom");
	अगर (!node || (s32)node == -1)
		prom_halt();

	prom_माला_लोtring(node, "version", prom_version, माप(prom_version));

	prom_म_लिखो("\n");
पूर्ण

व्योम __init prom_init_report(व्योम)
अणु
	prपूर्णांकk("PROMLIB: Sun IEEE Boot Prom '%s'\n", prom_version);
	prपूर्णांकk("PROMLIB: Root node compatible: %s\n", prom_root_compatible);
पूर्ण
