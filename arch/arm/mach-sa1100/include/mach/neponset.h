<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * arch/arm/mach-sa1100/include/mach/neponset.h
 *
 * Created 2000/06/05 by Nicolas Pitre <nico@fluxnic.net>
 *
 * This file contains the hardware specअगरic definitions क्रम Assabet
 * Only include this file from SA1100-specअगरic files.
 *
 * 2000/05/23 John Dorsey <john+@cs.cmu.edu>
 *      Definitions क्रम Neponset added.
 */
#अगर_अघोषित __ASM_ARCH_NEPONSET_H
#घोषणा __ASM_ARCH_NEPONSET_H

/*
 * Neponset definitions: 
 */
#घोषणा NCR_GP01_OFF		(1<<0)
#घोषणा NCR_TP_PWR_EN		(1<<1)
#घोषणा NCR_MS_PWR_EN		(1<<2)
#घोषणा NCR_ENET_OSC_EN		(1<<3)
#घोषणा NCR_SPI_KB_WK_UP	(1<<4)
#घोषणा NCR_A0VPP		(1<<5)
#घोषणा NCR_A1VPP		(1<<6)

व्योम neponset_ncr_frob(अचिन्हित पूर्णांक, अचिन्हित पूर्णांक);
#घोषणा neponset_ncr_set(v)	neponset_ncr_frob(0, v)
#घोषणा neponset_ncr_clear(v)	neponset_ncr_frob(v, 0)

#पूर्ण_अगर
