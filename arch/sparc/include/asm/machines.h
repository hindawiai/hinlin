<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * machines.h:  Defines क्रम taking apart the machine type value in the
 *              idprom and determining the kind of machine we are on.
 *
 * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)
 */
#अगर_अघोषित _SPARC_MACHINES_H
#घोषणा _SPARC_MACHINES_H

काष्ठा Sun_Machine_Models अणु
	अक्षर *name;
	अचिन्हित अक्षर id_machtype;
पूर्ण;

/* The machine type in the idprom area looks like this:
 *
 * ---------------
 * | ARCH | MACH |
 * ---------------
 *  7    4 3    0
 *
 * The ARCH field determines the architecture line (sun4m, etc).
 * The MACH field determines the machine make within that architecture.
 */

#घोषणा SM_ARCH_MASK  0xf0
#घोषणा  M_LEON       0x30
#घोषणा SM_SUN4M      0x70
#घोषणा SM_SUN4M_OBP  0x80

#घोषणा SM_TYP_MASK   0x0f

/* Leon machines */
#घोषणा M_LEON3_SOC   0x02    /* Leon3 SoC */

/* Sun4m machines, these predate the OpenBoot.  These values only mean
 * something अगर the value in the ARCH field is SM_SUN4M, अगर it is
 * SM_SUN4M_OBP then you have the following situation:
 * 1) You either have a sun4d, a sun4e, or a recently made sun4m.
 * 2) You have to consult OpenBoot to determine which machine this is.
 */
#घोषणा SM_4M_SS60    0x01    /* Sun4m SparcSystem 600                  */
#घोषणा SM_4M_SS50    0x02    /* Sun4m SparcStation 10                  */
#घोषणा SM_4M_SS40    0x03    /* Sun4m SparcStation 5                   */

/* Sun4d machines -- N/A */
/* Sun4e machines -- N/A */
/* Sun4u machines -- N/A */

#पूर्ण_अगर /* !(_SPARC_MACHINES_H) */
