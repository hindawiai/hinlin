<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Atheros AR71XX/AR724X/AR913X specअगरic prom routines
 *
 *  Copyright (C) 2015 Laurent Fasnacht <l@libres.ch>
 *  Copyright (C) 2008-2010 Gabor Juhos <juhosg@खोलोwrt.org>
 *  Copyright (C) 2008 Imre Kaloz <kaloz@खोलोwrt.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/माला.स>
#समावेश <linux/initrd.h>

#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/fw/fw.h>

#समावेश "common.h"

व्योम __init prom_init(व्योम)
अणु
	fw_init_cmdline();

#अगर_घोषित CONFIG_BLK_DEV_INITRD
	/* Read the initrd address from the firmware environment */
	initrd_start = fw_दो_पर्याl("initrd_start");
	अगर (initrd_start) अणु
		initrd_start = KSEG0ADDR(initrd_start);
		initrd_end = initrd_start + fw_दो_पर्याl("initrd_size");
	पूर्ण
#पूर्ण_अगर
पूर्ण
