<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *   Application Subप्रणाली Power Management Unit
 */

#अगर_अघोषित __ASM_MACH_REGS_APMU_H
#घोषणा __ASM_MACH_REGS_APMU_H

#समावेश "addr-map.h"

#घोषणा APMU_FNCLK_EN	(1 << 4)
#घोषणा APMU_AXICLK_EN	(1 << 3)
#घोषणा APMU_FNRST_DIS	(1 << 1)
#घोषणा APMU_AXIRST_DIS	(1 << 0)

/* Wake Clear Register */
#घोषणा APMU_WAKE_CLR	APMU_REG(0x07c)

#घोषणा APMU_PXA168_KP_WAKE_CLR		(1 << 7)
#घोषणा APMU_PXA168_CFI_WAKE_CLR	(1 << 6)
#घोषणा APMU_PXA168_XD_WAKE_CLR		(1 << 5)
#घोषणा APMU_PXA168_MSP_WAKE_CLR	(1 << 4)
#घोषणा APMU_PXA168_SD4_WAKE_CLR	(1 << 3)
#घोषणा APMU_PXA168_SD3_WAKE_CLR	(1 << 2)
#घोषणा APMU_PXA168_SD2_WAKE_CLR	(1 << 1)
#घोषणा APMU_PXA168_SD1_WAKE_CLR	(1 << 0)

#पूर्ण_अगर /* __ASM_MACH_REGS_APMU_H */
