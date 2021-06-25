<शैली गुरु>
/*
 * Copyright 2012-15 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: AMD
 *
 */

#समावेश <linux/slab.h>

#समावेश "dm_services.h"

#समावेश "include/logger_interface.h"

#समावेश "irq_service_dce120.h"
#समावेश "../dce110/irq_service_dce110.h"

#समावेश "dce/dce_12_0_offset.h"
#समावेश "dce/dce_12_0_sh_mask.h"
#समावेश "soc15_hw_ip.h"
#समावेश "vega10_ip_offset.h"

#समावेश "ivsrcid/ivsrcid_vislands30.h"

अटल bool hpd_ack(
	काष्ठा irq_service *irq_service,
	स्थिर काष्ठा irq_source_info *info)
अणु
	uपूर्णांक32_t addr = info->status_reg;
	uपूर्णांक32_t value = dm_पढ़ो_reg(irq_service->ctx, addr);
	uपूर्णांक32_t current_status =
		get_reg_field_value(
			value,
			HPD0_DC_HPD_INT_STATUS,
			DC_HPD_SENSE_DELAYED);

	dal_irq_service_ack_generic(irq_service, info);

	value = dm_पढ़ो_reg(irq_service->ctx, info->enable_reg);

	set_reg_field_value(
		value,
		current_status ? 0 : 1,
		HPD0_DC_HPD_INT_CONTROL,
		DC_HPD_INT_POLARITY);

	dm_ग_लिखो_reg(irq_service->ctx, info->enable_reg, value);

	वापस true;
पूर्ण

अटल स्थिर काष्ठा irq_source_info_funcs hpd_irq_info_funcs = अणु
	.set = शून्य,
	.ack = hpd_ack
पूर्ण;

अटल स्थिर काष्ठा irq_source_info_funcs hpd_rx_irq_info_funcs = अणु
	.set = शून्य,
	.ack = शून्य
पूर्ण;

अटल स्थिर काष्ठा irq_source_info_funcs pflip_irq_info_funcs = अणु
	.set = शून्य,
	.ack = शून्य
पूर्ण;

अटल स्थिर काष्ठा irq_source_info_funcs vblank_irq_info_funcs = अणु
	.set = dce110_vblank_set,
	.ack = शून्य
पूर्ण;

अटल स्थिर काष्ठा irq_source_info_funcs vupdate_irq_info_funcs = अणु
	.set = शून्य,
	.ack = शून्य
पूर्ण;

#घोषणा BASE_INNER(seg) \
	DCE_BASE__INST0_SEG ## seg

#घोषणा BASE(seg) \
	BASE_INNER(seg)

#घोषणा SRI(reg_name, block, id)\
	BASE(mm ## block ## id ## _ ## reg_name ## _BASE_IDX) + \
			mm ## block ## id ## _ ## reg_name


#घोषणा IRQ_REG_ENTRY(block, reg_num, reg1, mask1, reg2, mask2)\
	.enable_reg = SRI(reg1, block, reg_num),\
	.enable_mask = \
		block ## reg_num ## _ ## reg1 ## __ ## mask1 ## _MASK,\
	.enable_value = अणु\
		block ## reg_num ## _ ## reg1 ## __ ## mask1 ## _MASK,\
		~block ## reg_num ## _ ## reg1 ## __ ## mask1 ## _MASK \
	पूर्ण,\
	.ack_reg = SRI(reg2, block, reg_num),\
	.ack_mask = \
		block ## reg_num ## _ ## reg2 ## __ ## mask2 ## _MASK,\
	.ack_value = \
		block ## reg_num ## _ ## reg2 ## __ ## mask2 ## _MASK \

#घोषणा hpd_पूर्णांक_entry(reg_num)\
	[DC_IRQ_SOURCE_HPD1 + reg_num] = अणु\
		IRQ_REG_ENTRY(HPD, reg_num,\
			DC_HPD_INT_CONTROL, DC_HPD_INT_EN,\
			DC_HPD_INT_CONTROL, DC_HPD_INT_ACK),\
		.status_reg = SRI(DC_HPD_INT_STATUS, HPD, reg_num),\
		.funcs = &hpd_irq_info_funcs\
	पूर्ण

#घोषणा hpd_rx_पूर्णांक_entry(reg_num)\
	[DC_IRQ_SOURCE_HPD1RX + reg_num] = अणु\
		IRQ_REG_ENTRY(HPD, reg_num,\
			DC_HPD_INT_CONTROL, DC_HPD_RX_INT_EN,\
			DC_HPD_INT_CONTROL, DC_HPD_RX_INT_ACK),\
		.status_reg = SRI(DC_HPD_INT_STATUS, HPD, reg_num),\
		.funcs = &hpd_rx_irq_info_funcs\
	पूर्ण
#घोषणा pflip_पूर्णांक_entry(reg_num)\
	[DC_IRQ_SOURCE_PFLIP1 + reg_num] = अणु\
		IRQ_REG_ENTRY(DCP, reg_num, \
			GRPH_INTERRUPT_CONTROL, GRPH_PFLIP_INT_MASK, \
			GRPH_INTERRUPT_STATUS, GRPH_PFLIP_INT_CLEAR),\
		.status_reg = SRI(GRPH_INTERRUPT_STATUS, DCP, reg_num),\
		.funcs = &pflip_irq_info_funcs\
	पूर्ण

#घोषणा vupdate_पूर्णांक_entry(reg_num)\
	[DC_IRQ_SOURCE_VUPDATE1 + reg_num] = अणु\
		IRQ_REG_ENTRY(CRTC, reg_num,\
			CRTC_INTERRUPT_CONTROL, CRTC_V_UPDATE_INT_MSK,\
			CRTC_V_UPDATE_INT_STATUS, CRTC_V_UPDATE_INT_CLEAR),\
		.funcs = &vupdate_irq_info_funcs\
	पूर्ण

#घोषणा vblank_पूर्णांक_entry(reg_num)\
	[DC_IRQ_SOURCE_VBLANK1 + reg_num] = अणु\
		IRQ_REG_ENTRY(CRTC, reg_num,\
				CRTC_VERTICAL_INTERRUPT0_CONTROL, CRTC_VERTICAL_INTERRUPT0_INT_ENABLE,\
				CRTC_VERTICAL_INTERRUPT0_CONTROL, CRTC_VERTICAL_INTERRUPT0_CLEAR),\
		.funcs = &vblank_irq_info_funcs,\
		.src_id = VISLANDS30_IV_SRCID_D1_VERTICAL_INTERRUPT0 + reg_num\
	पूर्ण

#घोषणा dummy_irq_entry() \
	अणु\
		.funcs = &dummy_irq_info_funcs\
	पूर्ण

#घोषणा i2c_पूर्णांक_entry(reg_num) \
	[DC_IRQ_SOURCE_I2C_DDC ## reg_num] = dummy_irq_entry()

#घोषणा dp_sink_पूर्णांक_entry(reg_num) \
	[DC_IRQ_SOURCE_DPSINK ## reg_num] = dummy_irq_entry()

#घोषणा gpio_pad_पूर्णांक_entry(reg_num) \
	[DC_IRQ_SOURCE_GPIOPAD ## reg_num] = dummy_irq_entry()

#घोषणा dc_underflow_पूर्णांक_entry(reg_num) \
	[DC_IRQ_SOURCE_DC ## reg_num ## UNDERFLOW] = dummy_irq_entry()

अटल स्थिर काष्ठा irq_source_info_funcs dummy_irq_info_funcs = अणु
	.set = dal_irq_service_dummy_set,
	.ack = dal_irq_service_dummy_ack
पूर्ण;

अटल स्थिर काष्ठा irq_source_info
irq_source_info_dce120[DAL_IRQ_SOURCES_NUMBER] = अणु
	[DC_IRQ_SOURCE_INVALID] = dummy_irq_entry(),
	hpd_पूर्णांक_entry(0),
	hpd_पूर्णांक_entry(1),
	hpd_पूर्णांक_entry(2),
	hpd_पूर्णांक_entry(3),
	hpd_पूर्णांक_entry(4),
	hpd_पूर्णांक_entry(5),
	hpd_rx_पूर्णांक_entry(0),
	hpd_rx_पूर्णांक_entry(1),
	hpd_rx_पूर्णांक_entry(2),
	hpd_rx_पूर्णांक_entry(3),
	hpd_rx_पूर्णांक_entry(4),
	hpd_rx_पूर्णांक_entry(5),
	i2c_पूर्णांक_entry(1),
	i2c_पूर्णांक_entry(2),
	i2c_पूर्णांक_entry(3),
	i2c_पूर्णांक_entry(4),
	i2c_पूर्णांक_entry(5),
	i2c_पूर्णांक_entry(6),
	dp_sink_पूर्णांक_entry(1),
	dp_sink_पूर्णांक_entry(2),
	dp_sink_पूर्णांक_entry(3),
	dp_sink_पूर्णांक_entry(4),
	dp_sink_पूर्णांक_entry(5),
	dp_sink_पूर्णांक_entry(6),
	[DC_IRQ_SOURCE_TIMER] = dummy_irq_entry(),
	pflip_पूर्णांक_entry(0),
	pflip_पूर्णांक_entry(1),
	pflip_पूर्णांक_entry(2),
	pflip_पूर्णांक_entry(3),
	pflip_पूर्णांक_entry(4),
	pflip_पूर्णांक_entry(5),
	[DC_IRQ_SOURCE_PFLIP_UNDERLAY0] = dummy_irq_entry(),
	gpio_pad_पूर्णांक_entry(0),
	gpio_pad_पूर्णांक_entry(1),
	gpio_pad_पूर्णांक_entry(2),
	gpio_pad_पूर्णांक_entry(3),
	gpio_pad_पूर्णांक_entry(4),
	gpio_pad_पूर्णांक_entry(5),
	gpio_pad_पूर्णांक_entry(6),
	gpio_pad_पूर्णांक_entry(7),
	gpio_pad_पूर्णांक_entry(8),
	gpio_pad_पूर्णांक_entry(9),
	gpio_pad_पूर्णांक_entry(10),
	gpio_pad_पूर्णांक_entry(11),
	gpio_pad_पूर्णांक_entry(12),
	gpio_pad_पूर्णांक_entry(13),
	gpio_pad_पूर्णांक_entry(14),
	gpio_pad_पूर्णांक_entry(15),
	gpio_pad_पूर्णांक_entry(16),
	gpio_pad_पूर्णांक_entry(17),
	gpio_pad_पूर्णांक_entry(18),
	gpio_pad_पूर्णांक_entry(19),
	gpio_pad_पूर्णांक_entry(20),
	gpio_pad_पूर्णांक_entry(21),
	gpio_pad_पूर्णांक_entry(22),
	gpio_pad_पूर्णांक_entry(23),
	gpio_pad_पूर्णांक_entry(24),
	gpio_pad_पूर्णांक_entry(25),
	gpio_pad_पूर्णांक_entry(26),
	gpio_pad_पूर्णांक_entry(27),
	gpio_pad_पूर्णांक_entry(28),
	gpio_pad_पूर्णांक_entry(29),
	gpio_pad_पूर्णांक_entry(30),
	dc_underflow_पूर्णांक_entry(1),
	dc_underflow_पूर्णांक_entry(2),
	dc_underflow_पूर्णांक_entry(3),
	dc_underflow_पूर्णांक_entry(4),
	dc_underflow_पूर्णांक_entry(5),
	dc_underflow_पूर्णांक_entry(6),
	[DC_IRQ_SOURCE_DMCU_SCP] = dummy_irq_entry(),
	[DC_IRQ_SOURCE_VBIOS_SW] = dummy_irq_entry(),
	vupdate_पूर्णांक_entry(0),
	vupdate_पूर्णांक_entry(1),
	vupdate_पूर्णांक_entry(2),
	vupdate_पूर्णांक_entry(3),
	vupdate_पूर्णांक_entry(4),
	vupdate_पूर्णांक_entry(5),
	vblank_पूर्णांक_entry(0),
	vblank_पूर्णांक_entry(1),
	vblank_पूर्णांक_entry(2),
	vblank_पूर्णांक_entry(3),
	vblank_पूर्णांक_entry(4),
	vblank_पूर्णांक_entry(5),
पूर्ण;

अटल स्थिर काष्ठा irq_service_funcs irq_service_funcs_dce120 = अणु
		.to_dal_irq_source = to_dal_irq_source_dce110
पूर्ण;

अटल व्योम dce120_irq_स्थिरruct(
	काष्ठा irq_service *irq_service,
	काष्ठा irq_service_init_data *init_data)
अणु
	dal_irq_service_स्थिरruct(irq_service, init_data);

	irq_service->info = irq_source_info_dce120;
	irq_service->funcs = &irq_service_funcs_dce120;
पूर्ण

काष्ठा irq_service *dal_irq_service_dce120_create(
	काष्ठा irq_service_init_data *init_data)
अणु
	काष्ठा irq_service *irq_service = kzalloc(माप(*irq_service),
						  GFP_KERNEL);

	अगर (!irq_service)
		वापस शून्य;

	dce120_irq_स्थिरruct(irq_service, init_data);
	वापस irq_service;
पूर्ण
