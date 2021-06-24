<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * पन.स - DesignWare USB3 DRD IO Header
 *
 * Copyright (C) 2010-2011 Texas Instruments Incorporated - https://www.ti.com
 *
 * Authors: Felipe Balbi <balbi@ti.com>,
 *	    Sebastian Andrzej Siewior <bigeasy@linutronix.de>
 */

#अगर_अघोषित __DRIVERS_USB_DWC3_IO_H
#घोषणा __DRIVERS_USB_DWC3_IO_H

#समावेश <linux/पन.स>
#समावेश "trace.h"
#समावेश "debug.h"
#समावेश "core.h"

अटल अंतरभूत u32 dwc3_पढ़ोl(व्योम __iomem *base, u32 offset)
अणु
	u32 value;

	/*
	 * We requested the mem region starting from the Globals address
	 * space, see dwc3_probe in core.c.
	 * However, the offsets are given starting from xHCI address space.
	 */
	value = पढ़ोl(base + offset - DWC3_GLOBALS_REGS_START);

	/*
	 * When tracing we want to make it easy to find the correct address on
	 * करोcumentation, so we revert it back to the proper addresses, the
	 * same way they are described on SNPS करोcumentation
	 */
	trace_dwc3_पढ़ोl(base - DWC3_GLOBALS_REGS_START, offset, value);

	वापस value;
पूर्ण

अटल अंतरभूत व्योम dwc3_ग_लिखोl(व्योम __iomem *base, u32 offset, u32 value)
अणु
	/*
	 * We requested the mem region starting from the Globals address
	 * space, see dwc3_probe in core.c.
	 * However, the offsets are given starting from xHCI address space.
	 */
	ग_लिखोl(value, base + offset - DWC3_GLOBALS_REGS_START);

	/*
	 * When tracing we want to make it easy to find the correct address on
	 * करोcumentation, so we revert it back to the proper addresses, the
	 * same way they are described on SNPS करोcumentation
	 */
	trace_dwc3_ग_लिखोl(base - DWC3_GLOBALS_REGS_START, offset, value);
पूर्ण

#पूर्ण_अगर /* __DRIVERS_USB_DWC3_IO_H */
