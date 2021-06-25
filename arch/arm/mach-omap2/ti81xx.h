<शैली गुरु>
/*
 * This file contains the address data क्रम various TI81XX modules.
 *
 * Copyright (C) 2010 Texas Instruments, Inc. - https://www.ti.com/
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#अगर_अघोषित __ASM_ARCH_TI81XX_H
#घोषणा __ASM_ARCH_TI81XX_H

#घोषणा L4_SLOW_TI81XX_BASE	0x48000000

#घोषणा TI81XX_SCM_BASE		0x48140000
#घोषणा TI81XX_CTRL_BASE	TI81XX_SCM_BASE
#घोषणा TI81XX_PRCM_BASE	0x48180000

/*
 * Adjust TAP रेजिस्टर base such that omap3_check_revision accesses the correct
 * TI81XX रेजिस्टर क्रम checking device ID (it adds 0x204 to tap base जबतक
 * TI81XX DEVICE ID रेजिस्टर is at offset 0x600 from control base).
 */
#घोषणा TI81XX_TAP_BASE		(TI81XX_CTRL_BASE + \
				 TI81XX_CONTROL_DEVICE_ID - 0x204)


#घोषणा TI81XX_ARM_INTC_BASE	0x48200000

#पूर्ण_अगर /* __ASM_ARCH_TI81XX_H */
