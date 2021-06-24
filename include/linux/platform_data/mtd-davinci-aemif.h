<शैली गुरु>
/*
 * TI DaVinci AEMIF support
 *
 * Copyright 2010 (C) Texas Instruments, Inc. https://www.ti.com/
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2. This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 */
#अगर_अघोषित _MACH_DAVINCI_AEMIF_H
#घोषणा _MACH_DAVINCI_AEMIF_H

#समावेश <linux/platक्रमm_device.h>

#घोषणा NRCSR_OFFSET		0x00
#घोषणा AWCCR_OFFSET		0x04
#घोषणा A1CR_OFFSET		0x10

#घोषणा ACR_ASIZE_MASK		0x3
#घोषणा ACR_EW_MASK		BIT(30)
#घोषणा ACR_SS_MASK		BIT(31)

/* All timings in nanoseconds */
काष्ठा davinci_aemअगर_timing अणु
	u8	wsetup;
	u8	wstrobe;
	u8	whold;

	u8	rsetup;
	u8	rstrobe;
	u8	rhold;

	u8	ta;
पूर्ण;

#पूर्ण_अगर
