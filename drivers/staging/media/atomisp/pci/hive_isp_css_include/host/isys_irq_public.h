<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
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

#अगर_अघोषित __ISYS_IRQ_PUBLIC_H__
#घोषणा __ISYS_IRQ_PUBLIC_H__

#समावेश "isys_irq_global.h"
#समावेश "isys_irq_local.h"

#अगर defined(ISP2401)

व्योम isys_irqc_state_get(स्थिर isys_irq_ID_t	isys_irqc_id,
			 isys_irqc_state_t	*state);

व्योम isys_irqc_state_dump(स्थिर isys_irq_ID_t	isys_irqc_id,
			  स्थिर isys_irqc_state_t *state);

व्योम isys_irqc_reg_store(स्थिर isys_irq_ID_t	isys_irqc_id,
			 स्थिर अचिन्हित पूर्णांक	reg_idx,
			 स्थिर hrt_data		value);

hrt_data isys_irqc_reg_load(स्थिर isys_irq_ID_t	isys_irqc_id,
			    स्थिर अचिन्हित पूर्णांक	reg_idx);

व्योम isys_irqc_status_enable(स्थिर isys_irq_ID_t isys_irqc_id);

#पूर्ण_अगर /* defined(ISP2401) */

#पूर्ण_अगर	/* __ISYS_IRQ_PUBLIC_H__ */
