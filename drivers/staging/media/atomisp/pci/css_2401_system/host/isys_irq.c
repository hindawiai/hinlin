<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2015, Intel Corporation.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 */

#समावेश <प्रणाली_local.h>
#समावेश "device_access.h"
#समावेश "assert_support.h"
#समावेश "ia_css_debug.h"
#समावेश "isys_irq.h"

#अगर_अघोषित __INLINE_ISYS2401_IRQ__
/*
 * Include definitions क्रम isys irq निजी functions. isys_irq.h includes
 * declarations of these functions by including isys_irq_खुला.h.
 */
#समावेश "isys_irq_private.h"
#पूर्ण_अगर

/* Public पूर्णांकerface */
व्योम isys_irqc_status_enable(स्थिर isys_irq_ID_t	isys_irqc_id)
अणु
	निश्चित(isys_irqc_id < N_ISYS_IRQ_ID);

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "Setting irq mask for port %u\n",
			    isys_irqc_id);
	isys_irqc_reg_store(isys_irqc_id, ISYS_IRQ_MASK_REG_IDX,
			    ISYS_IRQ_MASK_REG_VALUE);
	isys_irqc_reg_store(isys_irqc_id, ISYS_IRQ_CLEAR_REG_IDX,
			    ISYS_IRQ_CLEAR_REG_VALUE);
	isys_irqc_reg_store(isys_irqc_id, ISYS_IRQ_ENABLE_REG_IDX,
			    ISYS_IRQ_ENABLE_REG_VALUE);
पूर्ण
