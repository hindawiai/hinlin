<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * init.c:  Initialize पूर्णांकernal variables used by the PROM
 *          library functions.
 *
 * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>

#समावेश <यंत्र/खोलोprom.h>
#समावेश <यंत्र/oplib.h>

काष्ठा linux_romvec *romvec;
क्रमागत prom_major_version prom_vers;
अचिन्हित पूर्णांक prom_rev, prom_prev;

/* The root node of the prom device tree. */
पूर्णांक prom_root_node;

/* Poपूर्णांकer to the device tree operations काष्ठाure. */
काष्ठा linux_nodeops *prom_nodeops;

/* You must call prom_init() beक्रमe you attempt to use any of the
 * routines in the prom library.
 * It माला_लो passed the poपूर्णांकer to the PROM vector.
 */

व्योम __init prom_init(काष्ठा linux_romvec *rp)
अणु
	romvec = rp;

	/* Initialization successful. */
	वापस;
पूर्ण
