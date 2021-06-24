<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * PQ2/mpc8260 board-specअगरic stuff
 *
 * A collection of काष्ठाures, addresses, and values associated with
 * the Freescale MPC8260ADS/MPC8266ADS-PCI boards.
 * Copied from the RPX-Classic and SBS8260 stuff.
 *
 * Author: Vitaly Bordug <vbordug@ru.mvista.com>
 *
 * Originally written by Dan Malek क्रम Motorola MPC8260 family
 *
 * Copyright (c) 2001 Dan Malek <dan@embeddedalley.com>
 * Copyright (c) 2006 MontaVista Software, Inc.
 */

#अगर_घोषित __KERNEL__
#अगर_अघोषित __MACH_ADS8260_DEFS
#घोषणा __MACH_ADS8260_DEFS

#समावेश <linux/seq_file.h>

/* The ADS8260 has 16, 32-bit wide control/status रेजिस्टरs, accessed
 * only on word boundaries.
 * Not all are used (yet), or are पूर्णांकeresting to us (yet).
 */

/* Things of पूर्णांकerest in the CSR.
 */
#घोषणा BCSR0_LED0		((uपूर्णांक)0x02000000)      /* 0 == on */
#घोषणा BCSR0_LED1		((uपूर्णांक)0x01000000)      /* 0 == on */
#घोषणा BCSR1_FETHIEN		((uपूर्णांक)0x08000000)      /* 0 == enable*/
#घोषणा BCSR1_FETH_RST		((uपूर्णांक)0x04000000)      /* 0 == reset */
#घोषणा BCSR1_RS232_EN1		((uपूर्णांक)0x02000000)      /* 0 ==enable */
#घोषणा BCSR1_RS232_EN2		((uपूर्णांक)0x01000000)      /* 0 ==enable */
#घोषणा BCSR3_FETHIEN2		((uपूर्णांक)0x10000000)      /* 0 == enable*/
#घोषणा BCSR3_FETH2_RST		((uपूर्णांक)0x80000000)      /* 0 == reset */

#पूर्ण_अगर /* __MACH_ADS8260_DEFS */
#पूर्ण_अगर /* __KERNEL__ */
