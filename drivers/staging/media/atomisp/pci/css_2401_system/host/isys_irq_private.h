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

#अगर_अघोषित __ISYS_IRQ_PRIVATE_H__
#घोषणा __ISYS_IRQ_PRIVATE_H__

#समावेश "isys_irq_global.h"
#समावेश "isys_irq_local.h"

#अगर defined(ISP2401)

/* -------------------------------------------------------+
 |             Native command पूर्णांकerface (NCI)             |
 + -------------------------------------------------------*/

/**
* @brief Get the isys irq status.
* Refer to "isys_irq.h" क्रम details.
*/
व्योम isys_irqc_state_get(
    स्थिर isys_irq_ID_t	isys_irqc_id,
    isys_irqc_state_t *state)
अणु
	state->edge     = isys_irqc_reg_load(isys_irqc_id, ISYS_IRQ_EDGE_REG_IDX);
	state->mask     = isys_irqc_reg_load(isys_irqc_id, ISYS_IRQ_MASK_REG_IDX);
	state->status   = isys_irqc_reg_load(isys_irqc_id, ISYS_IRQ_STATUS_REG_IDX);
	state->enable   = isys_irqc_reg_load(isys_irqc_id, ISYS_IRQ_ENABLE_REG_IDX);
	state->level_no = isys_irqc_reg_load(isys_irqc_id, ISYS_IRQ_LEVEL_NO_REG_IDX);
	/*
	** Invalid to पढ़ो/load from ग_लिखो-only रेजिस्टर 'clear'
	** state->clear = isys_irqc_reg_load(isys_irqc_id, ISYS_IRQ_CLEAR_REG_IDX);
	*/
पूर्ण

/**
* @brief Dump the isys irq status.
* Refer to "isys_irq.h" क्रम details.
*/
व्योम isys_irqc_state_dump(
    स्थिर isys_irq_ID_t	isys_irqc_id,
    स्थिर isys_irqc_state_t *state)
अणु
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
			    "isys irq controller id %d\n\tstatus:0x%x\n\tedge:0x%x\n\tmask:0x%x\n\tenable:0x%x\n\tlevel_not_pulse:0x%x\n",
			    isys_irqc_id,
			    state->status, state->edge, state->mask, state->enable, state->level_no);
पूर्ण

/* end of NCI */

/* -------------------------------------------------------+
 |              Device level पूर्णांकerface (DLI)              |
 + -------------------------------------------------------*/

/* Support functions */
व्योम isys_irqc_reg_store(
    स्थिर isys_irq_ID_t	isys_irqc_id,
    स्थिर अचिन्हित पूर्णांक	reg_idx,
    स्थिर hrt_data	value)
अणु
	अचिन्हित पूर्णांक reg_addr;

	निश्चित(isys_irqc_id < N_ISYS_IRQ_ID);
	निश्चित(reg_idx <= ISYS_IRQ_LEVEL_NO_REG_IDX);

	reg_addr = ISYS_IRQ_BASE[isys_irqc_id] + (reg_idx * माप(hrt_data));
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
			    "isys irq store at addr(0x%x) val(%u)\n", reg_addr, (अचिन्हित पूर्णांक)value);

	ia_css_device_store_uपूर्णांक32(reg_addr, value);
पूर्ण

hrt_data isys_irqc_reg_load(
    स्थिर isys_irq_ID_t	isys_irqc_id,
    स्थिर अचिन्हित पूर्णांक	reg_idx)
अणु
	अचिन्हित पूर्णांक reg_addr;
	hrt_data value;

	निश्चित(isys_irqc_id < N_ISYS_IRQ_ID);
	निश्चित(reg_idx <= ISYS_IRQ_LEVEL_NO_REG_IDX);

	reg_addr = ISYS_IRQ_BASE[isys_irqc_id] + (reg_idx * माप(hrt_data));
	value = ia_css_device_load_uपूर्णांक32(reg_addr);
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
			    "isys irq load from addr(0x%x) val(%u)\n", reg_addr, (अचिन्हित पूर्णांक)value);

	वापस value;
पूर्ण

/* end of DLI */

#पूर्ण_अगर /* defined(ISP2401) */

#पूर्ण_अगर	/* __ISYS_IRQ_PRIVATE_H__ */
