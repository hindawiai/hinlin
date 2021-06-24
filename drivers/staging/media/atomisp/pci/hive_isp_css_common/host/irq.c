<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2010-2015, Intel Corporation.
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

#समावेश "assert_support.h"
#समावेश "irq.h"

#अगर_अघोषित __INLINE_GP_DEVICE__
#घोषणा __INLINE_GP_DEVICE__
#पूर्ण_अगर
#समावेश "gp_device.h"	/* _REG_GP_IRQ_REQUEST_ADDR */

अटल अंतरभूत व्योम irq_रुको_क्रम_ग_लिखो_complete(
    स्थिर irq_ID_t		ID);

अटल अंतरभूत bool any_irq_channel_enabled(
    स्थिर irq_ID_t				ID);

अटल अंतरभूत irq_ID_t virq_get_irq_id(स्थिर क्रमागत virq_id irq_ID,
				       अचिन्हित पूर्णांक *channel_ID);

#अगर_अघोषित __INLINE_IRQ__
#समावेश "irq_private.h"
#पूर्ण_अगर /* __INLINE_IRQ__ */

अटल अचिन्हित लघु IRQ_N_CHANNEL[N_IRQ_ID] = अणु
	IRQ0_ID_N_CHANNEL,
	IRQ1_ID_N_CHANNEL,
	IRQ2_ID_N_CHANNEL,
	IRQ3_ID_N_CHANNEL
पूर्ण;

अटल अचिन्हित लघु IRQ_N_ID_OFFSET[N_IRQ_ID + 1] = अणु
	IRQ0_ID_OFFSET,
	IRQ1_ID_OFFSET,
	IRQ2_ID_OFFSET,
	IRQ3_ID_OFFSET,
	IRQ_END_OFFSET
पूर्ण;

अटल क्रमागत virq_id IRQ_NESTING_ID[N_IRQ_ID] = अणु
	N_virq_id,
	virq_अगरmt,
	virq_isys,
	virq_isel
पूर्ण;

व्योम irq_clear_all(
    स्थिर irq_ID_t				ID)
अणु
	hrt_data	mask = 0xFFFFFFFF;

	निश्चित(ID < N_IRQ_ID);
	निश्चित(IRQ_N_CHANNEL[ID] <= HRT_DATA_WIDTH);

	अगर (IRQ_N_CHANNEL[ID] < HRT_DATA_WIDTH) अणु
		mask = ~((~(hrt_data)0) >> IRQ_N_CHANNEL[ID]);
	पूर्ण

	irq_reg_store(ID,
		      _HRT_IRQ_CONTROLLER_CLEAR_REG_IDX, mask);
	वापस;
पूर्ण

/*
 * Do we want the user to be able to set the संकेतling method ?
 */
व्योम irq_enable_channel(
    स्थिर irq_ID_t				ID,
    स्थिर अचिन्हित पूर्णांक			irq_id)
अणु
	अचिन्हित पूर्णांक mask = irq_reg_load(ID,
					 _HRT_IRQ_CONTROLLER_MASK_REG_IDX);
	अचिन्हित पूर्णांक enable = irq_reg_load(ID,
					   _HRT_IRQ_CONTROLLER_ENABLE_REG_IDX);
	अचिन्हित पूर्णांक edge_in = irq_reg_load(ID,
					    _HRT_IRQ_CONTROLLER_EDGE_REG_IDX);
	अचिन्हित पूर्णांक me = 1U << irq_id;

	निश्चित(ID < N_IRQ_ID);
	निश्चित(irq_id < IRQ_N_CHANNEL[ID]);

	mask |= me;
	enable |= me;
	edge_in |= me;	/* rising edge */

	/* to aव्योम mishaps configuration must follow the following order */

	/* mask this पूर्णांकerrupt */
	irq_reg_store(ID,
		      _HRT_IRQ_CONTROLLER_MASK_REG_IDX, mask & ~me);
	/* rising edge at input */
	irq_reg_store(ID,
		      _HRT_IRQ_CONTROLLER_EDGE_REG_IDX, edge_in);
	/* enable पूर्णांकerrupt to output */
	irq_reg_store(ID,
		      _HRT_IRQ_CONTROLLER_ENABLE_REG_IDX, enable);
	/* clear current irq only */
	irq_reg_store(ID,
		      _HRT_IRQ_CONTROLLER_CLEAR_REG_IDX, me);
	/* unmask पूर्णांकerrupt from input */
	irq_reg_store(ID,
		      _HRT_IRQ_CONTROLLER_MASK_REG_IDX, mask);

	irq_रुको_क्रम_ग_लिखो_complete(ID);

	वापस;
पूर्ण

व्योम irq_enable_pulse(
    स्थिर irq_ID_t	ID,
    bool			pulse)
अणु
	अचिन्हित पूर्णांक edge_out = 0x0;

	अगर (pulse) अणु
		edge_out = 0xffffffff;
	पूर्ण
	/* output is given as edge, not pulse */
	irq_reg_store(ID,
		      _HRT_IRQ_CONTROLLER_EDGE_NOT_PULSE_REG_IDX, edge_out);
	वापस;
पूर्ण

व्योम irq_disable_channel(
    स्थिर irq_ID_t				ID,
    स्थिर अचिन्हित पूर्णांक			irq_id)
अणु
	अचिन्हित पूर्णांक mask = irq_reg_load(ID,
					 _HRT_IRQ_CONTROLLER_MASK_REG_IDX);
	अचिन्हित पूर्णांक enable = irq_reg_load(ID,
					   _HRT_IRQ_CONTROLLER_ENABLE_REG_IDX);
	अचिन्हित पूर्णांक me = 1U << irq_id;

	निश्चित(ID < N_IRQ_ID);
	निश्चित(irq_id < IRQ_N_CHANNEL[ID]);

	mask &= ~me;
	enable &= ~me;

	/* enable पूर्णांकerrupt to output */
	irq_reg_store(ID,
		      _HRT_IRQ_CONTROLLER_ENABLE_REG_IDX, enable);
	/* unmask पूर्णांकerrupt from input */
	irq_reg_store(ID,
		      _HRT_IRQ_CONTROLLER_MASK_REG_IDX, mask);
	/* clear current irq only */
	irq_reg_store(ID,
		      _HRT_IRQ_CONTROLLER_CLEAR_REG_IDX, me);

	irq_रुको_क्रम_ग_लिखो_complete(ID);

	वापस;
पूर्ण

क्रमागत hrt_isp_css_irq_status irq_get_channel_id(
    स्थिर irq_ID_t				ID,
    अचिन्हित पूर्णांक				*irq_id)
अणु
	अचिन्हित पूर्णांक irq_status = irq_reg_load(ID,
					       _HRT_IRQ_CONTROLLER_STATUS_REG_IDX);
	अचिन्हित पूर्णांक idx;
	क्रमागत hrt_isp_css_irq_status status = hrt_isp_css_irq_status_success;

	निश्चित(ID < N_IRQ_ID);
	निश्चित(irq_id);

	/* find the first irq bit */
	क्रम (idx = 0; idx < IRQ_N_CHANNEL[ID]; idx++) अणु
		अगर (irq_status & (1U << idx))
			अवरोध;
	पूर्ण
	अगर (idx == IRQ_N_CHANNEL[ID])
		वापस hrt_isp_css_irq_status_error;

	/* now check whether there are more bits set */
	अगर (irq_status != (1U << idx))
		status = hrt_isp_css_irq_status_more_irqs;

	irq_reg_store(ID,
		      _HRT_IRQ_CONTROLLER_CLEAR_REG_IDX, 1U << idx);

	irq_रुको_क्रम_ग_लिखो_complete(ID);

	अगर (irq_id)
		*irq_id = (अचिन्हित पूर्णांक)idx;

	वापस status;
पूर्ण

अटल स्थिर hrt_address IRQ_REQUEST_ADDR[N_IRQ_SW_CHANNEL_ID] = अणु
	_REG_GP_IRQ_REQUEST0_ADDR,
	_REG_GP_IRQ_REQUEST1_ADDR
पूर्ण;

व्योम irq_उठाओ(
    स्थिर irq_ID_t				ID,
    स्थिर irq_sw_channel_id_t	irq_id)
अणु
	hrt_address		addr;

	OP___निश्चित(ID == IRQ0_ID);
	OP___निश्चित(IRQ_BASE[ID] != (hrt_address)-1);
	OP___निश्चित(irq_id < N_IRQ_SW_CHANNEL_ID);

	(व्योम)ID;

	addr = IRQ_REQUEST_ADDR[irq_id];
	/* The SW IRQ pins are remapped to offset zero */
	gp_device_reg_store(GP_DEVICE0_ID,
			    (अचिन्हित पूर्णांक)addr, 1);
	gp_device_reg_store(GP_DEVICE0_ID,
			    (अचिन्हित पूर्णांक)addr, 0);
	वापस;
पूर्ण

व्योम irq_controller_get_state(स्थिर irq_ID_t ID,
			      काष्ठा irq_controller_state *state)
अणु
	निश्चित(ID < N_IRQ_ID);
	निश्चित(state);

	state->irq_edge = irq_reg_load(ID,
				       _HRT_IRQ_CONTROLLER_EDGE_REG_IDX);
	state->irq_mask = irq_reg_load(ID,
				       _HRT_IRQ_CONTROLLER_MASK_REG_IDX);
	state->irq_status = irq_reg_load(ID,
					 _HRT_IRQ_CONTROLLER_STATUS_REG_IDX);
	state->irq_enable = irq_reg_load(ID,
					 _HRT_IRQ_CONTROLLER_ENABLE_REG_IDX);
	state->irq_level_not_pulse = irq_reg_load(ID,
				     _HRT_IRQ_CONTROLLER_EDGE_NOT_PULSE_REG_IDX);
	वापस;
पूर्ण

bool any_virq_संकेत(व्योम)
अणु
	अचिन्हित पूर्णांक irq_status = irq_reg_load(IRQ0_ID,
					       _HRT_IRQ_CONTROLLER_STATUS_REG_IDX);

	वापस (irq_status != 0);
पूर्ण

व्योम cnd_virq_enable_channel(
    स्थिर क्रमागत virq_id				irq_ID,
    स्थिर bool					en)
अणु
	irq_ID_t		i;
	अचिन्हित पूर्णांक	channel_ID;
	irq_ID_t		ID = virq_get_irq_id(irq_ID, &channel_ID);

	निश्चित(ID < N_IRQ_ID);

	क्रम (i = IRQ1_ID; i < N_IRQ_ID; i++) अणु
		/* It is not allowed to enable the pin of a nested IRQ directly */
		निश्चित(irq_ID != IRQ_NESTING_ID[i]);
	पूर्ण

	अगर (en) अणु
		irq_enable_channel(ID, channel_ID);
		अगर (IRQ_NESTING_ID[ID] != N_virq_id) अणु
			/* Single level nesting, otherwise we'd need to recurse */
			irq_enable_channel(IRQ0_ID, IRQ_NESTING_ID[ID]);
		पूर्ण
	पूर्ण अन्यथा अणु
		irq_disable_channel(ID, channel_ID);
		अगर ((IRQ_NESTING_ID[ID] != N_virq_id) && !any_irq_channel_enabled(ID)) अणु
			/* Only disable the top अगर the nested ones are empty */
			irq_disable_channel(IRQ0_ID, IRQ_NESTING_ID[ID]);
		पूर्ण
	पूर्ण
	वापस;
पूर्ण

व्योम virq_clear_all(व्योम)
अणु
	irq_ID_t	irq_id;

	क्रम (irq_id = (irq_ID_t)0; irq_id < N_IRQ_ID; irq_id++) अणु
		irq_clear_all(irq_id);
	पूर्ण
	वापस;
पूर्ण

क्रमागत hrt_isp_css_irq_status
virq_get_channel_संकेतs(काष्ठा virq_info *irq_info)
अणु
	क्रमागत hrt_isp_css_irq_status irq_status = hrt_isp_css_irq_status_error;
	irq_ID_t ID;

	निश्चित(irq_info);

	क्रम (ID = (irq_ID_t)0 ; ID < N_IRQ_ID; ID++) अणु
		अगर (any_irq_channel_enabled(ID)) अणु
			hrt_data	irq_data = irq_reg_load(ID,
							    _HRT_IRQ_CONTROLLER_STATUS_REG_IDX);

			अगर (irq_data != 0) अणु
				/* The error condition is an IRQ pulse received with no IRQ status written */
				irq_status = hrt_isp_css_irq_status_success;
			पूर्ण

			irq_info->irq_status_reg[ID] |= irq_data;

			irq_reg_store(ID,
				      _HRT_IRQ_CONTROLLER_CLEAR_REG_IDX, irq_data);

			irq_रुको_क्रम_ग_लिखो_complete(ID);
		पूर्ण
	पूर्ण

	वापस irq_status;
पूर्ण

व्योम virq_clear_info(काष्ठा virq_info *irq_info)
अणु
	irq_ID_t ID;

	निश्चित(irq_info);

	क्रम (ID = (irq_ID_t)0 ; ID < N_IRQ_ID; ID++) अणु
		irq_info->irq_status_reg[ID] = 0;
	पूर्ण
	वापस;
पूर्ण

क्रमागत hrt_isp_css_irq_status virq_get_channel_id(
    क्रमागत virq_id					*irq_id)
अणु
	अचिन्हित पूर्णांक irq_status = irq_reg_load(IRQ0_ID,
					       _HRT_IRQ_CONTROLLER_STATUS_REG_IDX);
	अचिन्हित पूर्णांक idx;
	क्रमागत hrt_isp_css_irq_status status = hrt_isp_css_irq_status_success;
	irq_ID_t ID;

	निश्चित(irq_id);

	/* find the first irq bit on device 0 */
	क्रम (idx = 0; idx < IRQ_N_CHANNEL[IRQ0_ID]; idx++) अणु
		अगर (irq_status & (1U << idx))
			अवरोध;
	पूर्ण

	अगर (idx == IRQ_N_CHANNEL[IRQ0_ID]) अणु
		वापस hrt_isp_css_irq_status_error;
	पूर्ण

	/* Check whether there are more bits set on device 0 */
	अगर (irq_status != (1U << idx)) अणु
		status = hrt_isp_css_irq_status_more_irqs;
	पूर्ण

	/* Check whether we have an IRQ on one of the nested devices */
	क्रम (ID = N_IRQ_ID - 1 ; ID > (irq_ID_t)0; ID--) अणु
		अगर (IRQ_NESTING_ID[ID] == (क्रमागत virq_id)idx) अणु
			अवरोध;
		पूर्ण
	पूर्ण

	/* If we have a nested IRQ, load that state, discard the device 0 state */
	अगर (ID != IRQ0_ID) अणु
		irq_status = irq_reg_load(ID,
					  _HRT_IRQ_CONTROLLER_STATUS_REG_IDX);
		/* find the first irq bit on device "id" */
		क्रम (idx = 0; idx < IRQ_N_CHANNEL[ID]; idx++) अणु
			अगर (irq_status & (1U << idx))
				अवरोध;
		पूर्ण

		अगर (idx == IRQ_N_CHANNEL[ID]) अणु
			वापस hrt_isp_css_irq_status_error;
		पूर्ण

		/* Alternatively check whether there are more bits set on this device */
		अगर (irq_status != (1U << idx)) अणु
			status = hrt_isp_css_irq_status_more_irqs;
		पूर्ण अन्यथा अणु
			/* If this device is empty, clear the state on device 0 */
			irq_reg_store(IRQ0_ID,
				      _HRT_IRQ_CONTROLLER_CLEAR_REG_IDX, 1U << IRQ_NESTING_ID[ID]);
		पूर्ण
	पूर्ण /* अगर (ID != IRQ0_ID) */

	/* Here we proceed to clear the IRQ on detected device, अगर no nested IRQ, this is device 0 */
	irq_reg_store(ID,
		      _HRT_IRQ_CONTROLLER_CLEAR_REG_IDX, 1U << idx);

	irq_रुको_क्रम_ग_लिखो_complete(ID);

	idx += IRQ_N_ID_OFFSET[ID];
	अगर (irq_id)
		*irq_id = (क्रमागत virq_id)idx;

	वापस status;
पूर्ण

अटल अंतरभूत व्योम irq_रुको_क्रम_ग_लिखो_complete(
    स्थिर irq_ID_t		ID)
अणु
	निश्चित(ID < N_IRQ_ID);
	निश्चित(IRQ_BASE[ID] != (hrt_address)-1);
	(व्योम)ia_css_device_load_uपूर्णांक32(IRQ_BASE[ID] +
					_HRT_IRQ_CONTROLLER_ENABLE_REG_IDX * माप(hrt_data));
पूर्ण

अटल अंतरभूत bool any_irq_channel_enabled(
    स्थिर irq_ID_t				ID)
अणु
	hrt_data	en_reg;

	निश्चित(ID < N_IRQ_ID);

	en_reg = irq_reg_load(ID,
			      _HRT_IRQ_CONTROLLER_ENABLE_REG_IDX);

	वापस (en_reg != 0);
पूर्ण

अटल अंतरभूत irq_ID_t virq_get_irq_id(
    स्थिर क्रमागत virq_id		irq_ID,
    अचिन्हित पूर्णांक		*channel_ID)
अणु
	irq_ID_t ID;

	निश्चित(channel_ID);

	क्रम (ID = (irq_ID_t)0 ; ID < N_IRQ_ID; ID++) अणु
		अगर (irq_ID < IRQ_N_ID_OFFSET[ID + 1]) अणु
			अवरोध;
		पूर्ण
	पूर्ण

	*channel_ID = (अचिन्हित पूर्णांक)irq_ID - IRQ_N_ID_OFFSET[ID];

	वापस ID;
पूर्ण
