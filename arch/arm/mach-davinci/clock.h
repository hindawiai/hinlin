<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * TI DaVinci घड़ी definitions
 *
 * Copyright (C) 2006-2007 Texas Instruments.
 * Copyright (C) 2008-2009 Deep Root Systems, LLC
 */

#अगर_अघोषित __ARCH_ARM_DAVINCI_CLOCK_H
#घोषणा __ARCH_ARM_DAVINCI_CLOCK_H

/* PLL/Reset रेजिस्टर offsets */
#घोषणा PLLCTL          0x100
#घोषणा PLLCTL_PLLEN    BIT(0)
#घोषणा PLLCTL_PLLPWRDN	BIT(1)
#घोषणा PLLCTL_PLLRST	BIT(3)
#घोषणा PLLCTL_PLLDIS	BIT(4)
#घोषणा PLLCTL_PLLENSRC	BIT(5)
#घोषणा PLLCTL_CLKMODE  BIT(8)

#घोषणा PLLM		0x110
#घोषणा PLLM_PLLM_MASK  0xff

#घोषणा PREDIV          0x114
#घोषणा PLLDIV1         0x118
#घोषणा PLLDIV2         0x11c
#घोषणा PLLDIV3         0x120
#घोषणा POSTDIV         0x128
#घोषणा BPDIV           0x12c
#घोषणा PLLCMD		0x138
#घोषणा PLLSTAT		0x13c
#घोषणा PLLALNCTL	0x140
#घोषणा PLLDCHANGE	0x144
#घोषणा PLLCKEN		0x148
#घोषणा PLLCKSTAT	0x14c
#घोषणा PLLSYSTAT	0x150
#घोषणा PLLDIV4         0x160
#घोषणा PLLDIV5         0x164
#घोषणा PLLDIV6         0x168
#घोषणा PLLDIV7         0x16c
#घोषणा PLLDIV8         0x170
#घोषणा PLLDIV9         0x174
#घोषणा PLLDIV_EN       BIT(15)
#घोषणा PLLDIV_RATIO_MASK 0x1f

/*
 * OMAP-L138 प्रणाली reference guide recommends a रुको क्रम 4 OSCIN/CLKIN
 * cycles to ensure that the PLLC has चयनed to bypass mode. Delay of 1us
 * ensures we are good क्रम all > 4MHz OSCIN/CLKIN inमाला_दो. Typically the input
 * is ~25MHz. Units are micro seconds.
 */
#घोषणा PLL_BYPASS_TIME		1
/* From OMAP-L138 datasheet table 6-4. Units are micro seconds */
#घोषणा PLL_RESET_TIME		1
/*
 * From OMAP-L138 datasheet table 6-4; assuming preभाग = 1, वर्ग_मूल(pllm) = 4
 * Units are micro seconds.
 */
#घोषणा PLL_LOCK_TIME		20

#पूर्ण_अगर
