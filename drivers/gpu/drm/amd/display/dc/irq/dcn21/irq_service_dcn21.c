<शैली गुरु>
/*
 * Copyright 2018 Advanced Micro Devices, Inc.
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

#समावेश "../dce110/irq_service_dce110.h"

#समावेश "dcn/dcn_2_1_0_offset.h"
#समावेश "dcn/dcn_2_1_0_sh_mask.h"
#समावेश "renoir_ip_offset.h"


#समावेश "irq_service_dcn21.h"

#समावेश "ivsrcid/dcn/irqsrcs_dcn_1_0.h"

क्रमागत dc_irq_source to_dal_irq_source_dcn21(
		काष्ठा irq_service *irq_service,
		uपूर्णांक32_t src_id,
		uपूर्णांक32_t ext_id)
अणु
	चयन (src_id) अणु
	हाल DCN_1_0__SRCID__DC_D1_OTG_VSTARTUP:
		वापस DC_IRQ_SOURCE_VBLANK1;
	हाल DCN_1_0__SRCID__DC_D2_OTG_VSTARTUP:
		वापस DC_IRQ_SOURCE_VBLANK2;
	हाल DCN_1_0__SRCID__DC_D3_OTG_VSTARTUP:
		वापस DC_IRQ_SOURCE_VBLANK3;
	हाल DCN_1_0__SRCID__DC_D4_OTG_VSTARTUP:
		वापस DC_IRQ_SOURCE_VBLANK4;
	हाल DCN_1_0__SRCID__DC_D5_OTG_VSTARTUP:
		वापस DC_IRQ_SOURCE_VBLANK5;
	हाल DCN_1_0__SRCID__DC_D6_OTG_VSTARTUP:
		वापस DC_IRQ_SOURCE_VBLANK6;
	हाल DCN_1_0__SRCID__DMCUB_OUTBOX_HIGH_PRIORITY_READY_INT:
		वापस DC_IRQ_SOURCE_DMCUB_OUTBOX0;
	हाल DCN_1_0__SRCID__OTG1_VERTICAL_INTERRUPT0_CONTROL:
		वापस DC_IRQ_SOURCE_DC1_VLINE0;
	हाल DCN_1_0__SRCID__OTG2_VERTICAL_INTERRUPT0_CONTROL:
		वापस DC_IRQ_SOURCE_DC2_VLINE0;
	हाल DCN_1_0__SRCID__OTG3_VERTICAL_INTERRUPT0_CONTROL:
		वापस DC_IRQ_SOURCE_DC3_VLINE0;
	हाल DCN_1_0__SRCID__OTG4_VERTICAL_INTERRUPT0_CONTROL:
		वापस DC_IRQ_SOURCE_DC4_VLINE0;
	हाल DCN_1_0__SRCID__OTG5_VERTICAL_INTERRUPT0_CONTROL:
		वापस DC_IRQ_SOURCE_DC5_VLINE0;
	हाल DCN_1_0__SRCID__OTG6_VERTICAL_INTERRUPT0_CONTROL:
		वापस DC_IRQ_SOURCE_DC6_VLINE0;
	हाल DCN_1_0__SRCID__HUBP0_FLIP_INTERRUPT:
		वापस DC_IRQ_SOURCE_PFLIP1;
	हाल DCN_1_0__SRCID__HUBP1_FLIP_INTERRUPT:
		वापस DC_IRQ_SOURCE_PFLIP2;
	हाल DCN_1_0__SRCID__HUBP2_FLIP_INTERRUPT:
		वापस DC_IRQ_SOURCE_PFLIP3;
	हाल DCN_1_0__SRCID__HUBP3_FLIP_INTERRUPT:
		वापस DC_IRQ_SOURCE_PFLIP4;
	हाल DCN_1_0__SRCID__HUBP4_FLIP_INTERRUPT:
		वापस DC_IRQ_SOURCE_PFLIP5;
	हाल DCN_1_0__SRCID__HUBP5_FLIP_INTERRUPT:
		वापस DC_IRQ_SOURCE_PFLIP6;
	हाल DCN_1_0__SRCID__OTG0_IHC_V_UPDATE_NO_LOCK_INTERRUPT:
		वापस DC_IRQ_SOURCE_VUPDATE1;
	हाल DCN_1_0__SRCID__OTG1_IHC_V_UPDATE_NO_LOCK_INTERRUPT:
		वापस DC_IRQ_SOURCE_VUPDATE2;
	हाल DCN_1_0__SRCID__OTG2_IHC_V_UPDATE_NO_LOCK_INTERRUPT:
		वापस DC_IRQ_SOURCE_VUPDATE3;
	हाल DCN_1_0__SRCID__OTG3_IHC_V_UPDATE_NO_LOCK_INTERRUPT:
		वापस DC_IRQ_SOURCE_VUPDATE4;
	हाल DCN_1_0__SRCID__OTG4_IHC_V_UPDATE_NO_LOCK_INTERRUPT:
		वापस DC_IRQ_SOURCE_VUPDATE5;
	हाल DCN_1_0__SRCID__OTG5_IHC_V_UPDATE_NO_LOCK_INTERRUPT:
		वापस DC_IRQ_SOURCE_VUPDATE6;

	हाल DCN_1_0__SRCID__DC_HPD1_INT:
		/* generic src_id क्रम all HPD and HPDRX पूर्णांकerrupts */
		चयन (ext_id) अणु
		हाल DCN_1_0__CTXID__DC_HPD1_INT:
			वापस DC_IRQ_SOURCE_HPD1;
		हाल DCN_1_0__CTXID__DC_HPD2_INT:
			वापस DC_IRQ_SOURCE_HPD2;
		हाल DCN_1_0__CTXID__DC_HPD3_INT:
			वापस DC_IRQ_SOURCE_HPD3;
		हाल DCN_1_0__CTXID__DC_HPD4_INT:
			वापस DC_IRQ_SOURCE_HPD4;
		हाल DCN_1_0__CTXID__DC_HPD5_INT:
			वापस DC_IRQ_SOURCE_HPD5;
		हाल DCN_1_0__CTXID__DC_HPD6_INT:
			वापस DC_IRQ_SOURCE_HPD6;
		हाल DCN_1_0__CTXID__DC_HPD1_RX_INT:
			वापस DC_IRQ_SOURCE_HPD1RX;
		हाल DCN_1_0__CTXID__DC_HPD2_RX_INT:
			वापस DC_IRQ_SOURCE_HPD2RX;
		हाल DCN_1_0__CTXID__DC_HPD3_RX_INT:
			वापस DC_IRQ_SOURCE_HPD3RX;
		हाल DCN_1_0__CTXID__DC_HPD4_RX_INT:
			वापस DC_IRQ_SOURCE_HPD4RX;
		हाल DCN_1_0__CTXID__DC_HPD5_RX_INT:
			वापस DC_IRQ_SOURCE_HPD5RX;
		हाल DCN_1_0__CTXID__DC_HPD6_RX_INT:
			वापस DC_IRQ_SOURCE_HPD6RX;
		शेष:
			वापस DC_IRQ_SOURCE_INVALID;
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
	वापस DC_IRQ_SOURCE_INVALID;
पूर्ण

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
	.set = शून्य,
	.ack = शून्य
पूर्ण;

अटल स्थिर काष्ठा irq_source_info_funcs vupdate_no_lock_irq_info_funcs = अणु
	.set = शून्य,
	.ack = शून्य
पूर्ण;

अटल स्थिर काष्ठा irq_source_info_funcs dmub_trace_irq_info_funcs = अणु
	.set = शून्य,
	.ack = शून्य
पूर्ण;

अटल स्थिर काष्ठा irq_source_info_funcs vline0_irq_info_funcs = अणु
	.set = शून्य,
	.ack = शून्य
पूर्ण;

#अघोषित BASE_INNER
#घोषणा BASE_INNER(seg) DMU_BASE__INST0_SEG ## seg

/* compile समय expand base address. */
#घोषणा BASE(seg) \
	BASE_INNER(seg)


#घोषणा SRI(reg_name, block, id)\
	BASE(mm ## block ## id ## _ ## reg_name ## _BASE_IDX) + \
			mm ## block ## id ## _ ## reg_name

#घोषणा SRI_DMUB(reg_name)\
	BASE(mm ## reg_name ## _BASE_IDX) + \
			mm ## reg_name

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

#घोषणा IRQ_REG_ENTRY_DMUB(reg1, mask1, reg2, mask2)\
	.enable_reg = SRI_DMUB(reg1),\
	.enable_mask = \
		reg1 ## __ ## mask1 ## _MASK,\
	.enable_value = अणु\
		reg1 ## __ ## mask1 ## _MASK,\
		~reg1 ## __ ## mask1 ## _MASK \
	पूर्ण,\
	.ack_reg = SRI_DMUB(reg2),\
	.ack_mask = \
		reg2 ## __ ## mask2 ## _MASK,\
	.ack_value = \
		reg2 ## __ ## mask2 ## _MASK \

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
		IRQ_REG_ENTRY(HUBPREQ, reg_num,\
			DCSURF_SURFACE_FLIP_INTERRUPT, SURFACE_FLIP_INT_MASK,\
			DCSURF_SURFACE_FLIP_INTERRUPT, SURFACE_FLIP_CLEAR),\
		.funcs = &pflip_irq_info_funcs\
	पूर्ण

#घोषणा vupdate_पूर्णांक_entry(reg_num)\
	[DC_IRQ_SOURCE_VUPDATE1 + reg_num] = अणु\
		IRQ_REG_ENTRY(OTG, reg_num,\
			OTG_GLOBAL_SYNC_STATUS, VUPDATE_INT_EN,\
			OTG_GLOBAL_SYNC_STATUS, VUPDATE_EVENT_CLEAR),\
		.funcs = &vblank_irq_info_funcs\
	पूर्ण

/* vupdate_no_lock_पूर्णांक_entry maps to DC_IRQ_SOURCE_VUPDATEx, to match semantic
 * of DCE's DC_IRQ_SOURCE_VUPDATEx.
 */
#घोषणा vupdate_no_lock_पूर्णांक_entry(reg_num)\
	[DC_IRQ_SOURCE_VUPDATE1 + reg_num] = अणु\
		IRQ_REG_ENTRY(OTG, reg_num,\
			OTG_GLOBAL_SYNC_STATUS, VUPDATE_NO_LOCK_INT_EN,\
			OTG_GLOBAL_SYNC_STATUS, VUPDATE_NO_LOCK_EVENT_CLEAR),\
		.funcs = &vupdate_no_lock_irq_info_funcs\
	पूर्ण

#घोषणा vblank_पूर्णांक_entry(reg_num)\
	[DC_IRQ_SOURCE_VBLANK1 + reg_num] = अणु\
		IRQ_REG_ENTRY(OTG, reg_num,\
			OTG_GLOBAL_SYNC_STATUS, VSTARTUP_INT_EN,\
			OTG_GLOBAL_SYNC_STATUS, VSTARTUP_EVENT_CLEAR),\
		.funcs = &vblank_irq_info_funcs\
	पूर्ण

#घोषणा vline0_पूर्णांक_entry(reg_num)\
	[DC_IRQ_SOURCE_DC1_VLINE0 + reg_num] = अणु\
		IRQ_REG_ENTRY(OTG, reg_num,\
			OTG_VERTICAL_INTERRUPT0_CONTROL, OTG_VERTICAL_INTERRUPT0_INT_ENABLE,\
			OTG_VERTICAL_INTERRUPT0_CONTROL, OTG_VERTICAL_INTERRUPT0_CLEAR),\
		.funcs = &vline0_irq_info_funcs\
	पूर्ण

#घोषणा dmub_trace_पूर्णांक_entry()\
	[DC_IRQ_SOURCE_DMCUB_OUTBOX0] = अणु\
		IRQ_REG_ENTRY_DMUB(DMCUB_INTERRUPT_ENABLE, DMCUB_OUTBOX0_READY_INT_EN,\
			DMCUB_INTERRUPT_ACK, DMCUB_OUTBOX0_READY_INT_ACK),\
		.funcs = &dmub_trace_irq_info_funcs\
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
irq_source_info_dcn21[DAL_IRQ_SOURCES_NUMBER] = अणु
	[DC_IRQ_SOURCE_INVALID] = dummy_irq_entry(),
	hpd_पूर्णांक_entry(0),
	hpd_पूर्णांक_entry(1),
	hpd_पूर्णांक_entry(2),
	hpd_पूर्णांक_entry(3),
	hpd_पूर्णांक_entry(4),
	hpd_rx_पूर्णांक_entry(0),
	hpd_rx_पूर्णांक_entry(1),
	hpd_rx_पूर्णांक_entry(2),
	hpd_rx_पूर्णांक_entry(3),
	hpd_rx_पूर्णांक_entry(4),
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
	[DC_IRQ_SOURCE_PFLIP5] = dummy_irq_entry(),
	[DC_IRQ_SOURCE_PFLIP6] = dummy_irq_entry(),
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
	vupdate_no_lock_पूर्णांक_entry(0),
	vupdate_no_lock_पूर्णांक_entry(1),
	vupdate_no_lock_पूर्णांक_entry(2),
	vupdate_no_lock_पूर्णांक_entry(3),
	vupdate_no_lock_पूर्णांक_entry(4),
	vupdate_no_lock_पूर्णांक_entry(5),
	vblank_पूर्णांक_entry(0),
	vblank_पूर्णांक_entry(1),
	vblank_पूर्णांक_entry(2),
	vblank_पूर्णांक_entry(3),
	vblank_पूर्णांक_entry(4),
	vblank_पूर्णांक_entry(5),
	vline0_पूर्णांक_entry(0),
	vline0_पूर्णांक_entry(1),
	vline0_पूर्णांक_entry(2),
	vline0_पूर्णांक_entry(3),
	vline0_पूर्णांक_entry(4),
	vline0_पूर्णांक_entry(5),
	dmub_trace_पूर्णांक_entry(),
पूर्ण;

अटल स्थिर काष्ठा irq_service_funcs irq_service_funcs_dcn21 = अणु
		.to_dal_irq_source = to_dal_irq_source_dcn21
पूर्ण;

अटल व्योम dcn21_irq_स्थिरruct(
	काष्ठा irq_service *irq_service,
	काष्ठा irq_service_init_data *init_data)
अणु
	dal_irq_service_स्थिरruct(irq_service, init_data);

	irq_service->info = irq_source_info_dcn21;
	irq_service->funcs = &irq_service_funcs_dcn21;
पूर्ण

काष्ठा irq_service *dal_irq_service_dcn21_create(
	काष्ठा irq_service_init_data *init_data)
अणु
	काष्ठा irq_service *irq_service = kzalloc(माप(*irq_service),
						  GFP_KERNEL);

	अगर (!irq_service)
		वापस शून्य;

	dcn21_irq_स्थिरruct(irq_service, init_data);
	वापस irq_service;
पूर्ण
