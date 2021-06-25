<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2015 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Exynos SROMC रेजिस्टर definitions
 */

#अगर_अघोषित __EXYNOS_SROM_H
#घोषणा __EXYNOS_SROM_H __खाता__

#घोषणा EXYNOS_SROMREG(x)		(x)

#घोषणा EXYNOS_SROM_BW		EXYNOS_SROMREG(0x0)
#घोषणा EXYNOS_SROM_BC0		EXYNOS_SROMREG(0x4)
#घोषणा EXYNOS_SROM_BC1		EXYNOS_SROMREG(0x8)
#घोषणा EXYNOS_SROM_BC2		EXYNOS_SROMREG(0xc)
#घोषणा EXYNOS_SROM_BC3		EXYNOS_SROMREG(0x10)
#घोषणा EXYNOS_SROM_BC4		EXYNOS_SROMREG(0x14)
#घोषणा EXYNOS_SROM_BC5		EXYNOS_SROMREG(0x18)

/* one रेजिस्टर BW holds 4 x 4-bit packed settings क्रम NCS0 - NCS3 */

#घोषणा EXYNOS_SROM_BW__DATAWIDTH__SHIFT	0
#घोषणा EXYNOS_SROM_BW__ADDRMODE__SHIFT		1
#घोषणा EXYNOS_SROM_BW__WAITENABLE__SHIFT	2
#घोषणा EXYNOS_SROM_BW__BYTEENABLE__SHIFT	3

#घोषणा EXYNOS_SROM_BW__CS_MASK			0xf

#घोषणा EXYNOS_SROM_BW__NCS0__SHIFT		0
#घोषणा EXYNOS_SROM_BW__NCS1__SHIFT		4
#घोषणा EXYNOS_SROM_BW__NCS2__SHIFT		8
#घोषणा EXYNOS_SROM_BW__NCS3__SHIFT		12
#घोषणा EXYNOS_SROM_BW__NCS4__SHIFT		16
#घोषणा EXYNOS_SROM_BW__NCS5__SHIFT		20

/* applies to same to BCS0 - BCS3 */

#घोषणा EXYNOS_SROM_BCX__PMC__SHIFT		0
#घोषणा EXYNOS_SROM_BCX__TACP__SHIFT		4
#घोषणा EXYNOS_SROM_BCX__TCAH__SHIFT		8
#घोषणा EXYNOS_SROM_BCX__TCOH__SHIFT		12
#घोषणा EXYNOS_SROM_BCX__TACC__SHIFT		16
#घोषणा EXYNOS_SROM_BCX__TCOS__SHIFT		24
#घोषणा EXYNOS_SROM_BCX__TACS__SHIFT		28

#पूर्ण_अगर /* __EXYNOS_SROM_H */
