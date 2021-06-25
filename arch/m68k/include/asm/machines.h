<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * machines.h:  Defines क्रम taking apart the machine type value in the
 *              idprom and determining the kind of machine we are on.
 *
 * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)
 * Sun3/3x models added by David Monro (davidm@psrg.cs.usyd.edu.au)
 */
#अगर_अघोषित _SPARC_MACHINES_H
#घोषणा _SPARC_MACHINES_H

काष्ठा Sun_Machine_Models अणु
	अक्षर *name;
	अचिन्हित अक्षर id_machtype;
पूर्ण;

/* Current number of machines we know about that has an IDPROM
 * machtype entry including one entry क्रम the 0x80 OBP machines.
 */
// reduced aदीर्घ with table in arch/m68k/sun3/idprom.c
// sun3 port करोesn't need to know about sparc machines.
//#घोषणा NUM_SUN_MACHINES   23
#घोषणा NUM_SUN_MACHINES  8

/* The machine type in the idprom area looks like this:
 *
 * ---------------
 * | ARCH | MACH |
 * ---------------
 *  7    4 3    0
 *
 * The ARCH field determines the architecture line (sun4, sun4c, etc).
 * The MACH field determines the machine make within that architecture.
 */

#घोषणा SM_ARCH_MASK  0xf0
#घोषणा SM_SUN3       0x10
#घोषणा SM_SUN4       0x20
#घोषणा SM_SUN3X      0x40
#घोषणा SM_SUN4C      0x50
#घोषणा SM_SUN4M      0x70
#घोषणा SM_SUN4M_OBP  0x80

#घोषणा SM_TYP_MASK   0x0f
/* Sun3 machines */
#घोषणा SM_3_160      0x01    /* Sun 3/160 series */
#घोषणा SM_3_50       0x02    /* Sun 3/50 series */
#घोषणा SM_3_260      0x03    /* Sun 3/260 series */
#घोषणा SM_3_110      0x04    /* Sun 3/110 series */
#घोषणा SM_3_60       0x07    /* Sun 3/60 series */
#घोषणा SM_3_E        0x08    /* Sun 3/E series */

/* Sun3x machines */
#घोषणा SM_3_460      0x01    /* Sun 3/460 (460,470,480) series */
#घोषणा SM_3_80       0x02    /* Sun 3/80 series */

/* Sun4 machines */
#घोषणा SM_4_260      0x01    /* Sun 4/200 series */
#घोषणा SM_4_110      0x02    /* Sun 4/100 series */
#घोषणा SM_4_330      0x03    /* Sun 4/300 series */
#घोषणा SM_4_470      0x04    /* Sun 4/400 series */

/* Sun4c machines                Full Name              - PROM NAME */
#घोषणा SM_4C_SS1     0x01    /* Sun4c SparcStation 1   - Sun 4/60  */
#घोषणा SM_4C_IPC     0x02    /* Sun4c SparcStation IPC - Sun 4/40  */
#घोषणा SM_4C_SS1PLUS 0x03    /* Sun4c SparcStation 1+  - Sun 4/65  */
#घोषणा SM_4C_SLC     0x04    /* Sun4c SparcStation SLC - Sun 4/20  */
#घोषणा SM_4C_SS2     0x05    /* Sun4c SparcStation 2   - Sun 4/75  */
#घोषणा SM_4C_ELC     0x06    /* Sun4c SparcStation ELC - Sun 4/25  */
#घोषणा SM_4C_IPX     0x07    /* Sun4c SparcStation IPX - Sun 4/50  */

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
