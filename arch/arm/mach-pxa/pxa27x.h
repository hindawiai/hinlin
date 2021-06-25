<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __MACH_PXA27x_H
#घोषणा __MACH_PXA27x_H

#समावेश <linux/suspend.h>
#समावेश <mach/hardware.h>
#समावेश <mach/pxa2xx-regs.h>
#समावेश "mfp-pxa27x.h"
#समावेश <mach/irqs.h>

#घोषणा ARB_CNTRL	__REG(0x48000048)  /* Arbiter Control Register */

#घोषणा ARB_DMA_SLV_PARK	(1<<31)	   /* Be parked with DMA slave when idle */
#घोषणा ARB_CI_PARK		(1<<30)	   /* Be parked with Camera Interface when idle */
#घोषणा ARB_EX_MEM_PARK 	(1<<29)	   /* Be parked with बाह्यal MEMC when idle */
#घोषणा ARB_INT_MEM_PARK	(1<<28)	   /* Be parked with पूर्णांकernal MEMC when idle */
#घोषणा ARB_USB_PARK		(1<<27)	   /* Be parked with USB when idle */
#घोषणा ARB_LCD_PARK		(1<<26)	   /* Be parked with LCD when idle */
#घोषणा ARB_DMA_PARK		(1<<25)	   /* Be parked with DMA when idle */
#घोषणा ARB_CORE_PARK		(1<<24)	   /* Be parked with core when idle */
#घोषणा ARB_LOCK_FLAG		(1<<23)	   /* Only Locking masters gain access to the bus */

बाह्य पूर्णांक pxa27x_set_pwrmode(अचिन्हित पूर्णांक mode);
बाह्य व्योम pxa27x_cpu_pm_enter(suspend_state_t state);

#पूर्ण_अगर /* __MACH_PXA27x_H */
