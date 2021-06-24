<शैली गुरु>
/*
 * Copyright 2020 Mauro Rossi <issor.oruam@gmail.com>
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

#समावेश "irq_service_dce60.h"
#समावेश "../dce110/irq_service_dce110.h"

#समावेश "dce/dce_6_0_d.h"
#समावेश "dce/dce_6_0_sh_mask.h"

#समावेश "ivsrcid/ivsrcid_vislands30.h"

#घोषणा VISLANDS30_IV_SRCID_D1_VBLANK                        1
#घोषणा VISLANDS30_IV_SRCID_D2_VBLANK                        2
#घोषणा VISLANDS30_IV_SRCID_D3_VBLANK                        3
#घोषणा VISLANDS30_IV_SRCID_D4_VBLANK                        4
#घोषणा VISLANDS30_IV_SRCID_D5_VBLANK                        5
#घोषणा VISLANDS30_IV_SRCID_D6_VBLANK                        6

#समावेश "dc_types.h"

अटल bool hpd_ack(
	काष्ठा irq_service *irq_service,
	स्थिर काष्ठा irq_source_info *info)
अणु
	uपूर्णांक32_t addr = info->status_reg;
	uपूर्णांक32_t value = dm_पढ़ो_reg(irq_service->ctx, addr);
	uपूर्णांक32_t current_status =
		get_reg_field_value(
			value,
			DC_HPD1_INT_STATUS,
			DC_HPD1_SENSE_DELAYED);

	dal_irq_service_ack_generic(irq_service, info);

	value = dm_पढ़ो_reg(irq_service->ctx, info->enable_reg);

	set_reg_field_value(
		value,
		current_status ? 0 : 1,
		DC_HPD1_INT_CONTROL,
		DC_HPD1_INT_POLARITY);

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

अटल स्थिर काष्ठा irq_source_info_funcs vblank_irq_info_funcs_dce60 = अणु
	.set = शून्य,
	.ack = शून्य
पूर्ण;

#घोषणा hpd_पूर्णांक_entry(reg_num)\
	[DC_IRQ_SOURCE_INVALID + reg_num] = अणु\
		.enable_reg = mmDC_HPD ## reg_num ## _INT_CONTROL,\
		.enable_mask = DC_HPD1_INT_CONTROL__DC_HPD1_INT_EN_MASK,\
		.enable_value = अणु\
			DC_HPD1_INT_CONTROL__DC_HPD1_INT_EN_MASK,\
			~DC_HPD1_INT_CONTROL__DC_HPD1_INT_EN_MASK\
		पूर्ण,\
		.ack_reg = mmDC_HPD ## reg_num ## _INT_CONTROL,\
		.ack_mask = DC_HPD1_INT_CONTROL__DC_HPD1_INT_ACK_MASK,\
		.ack_value = DC_HPD1_INT_CONTROL__DC_HPD1_INT_ACK_MASK,\
		.status_reg = mmDC_HPD ## reg_num ## _INT_STATUS,\
		.funcs = &hpd_irq_info_funcs\
	पूर्ण

#घोषणा hpd_rx_पूर्णांक_entry(reg_num)\
	[DC_IRQ_SOURCE_HPD6 + reg_num] = अणु\
		.enable_reg = mmDC_HPD ## reg_num ## _INT_CONTROL,\
		.enable_mask = DC_HPD1_INT_CONTROL__DC_HPD1_RX_INT_EN_MASK,\
		.enable_value = अणु\
				DC_HPD1_INT_CONTROL__DC_HPD1_RX_INT_EN_MASK,\
			~DC_HPD1_INT_CONTROL__DC_HPD1_RX_INT_EN_MASK पूर्ण,\
		.ack_reg = mmDC_HPD ## reg_num ## _INT_CONTROL,\
		.ack_mask = DC_HPD1_INT_CONTROL__DC_HPD1_RX_INT_ACK_MASK,\
		.ack_value = DC_HPD1_INT_CONTROL__DC_HPD1_RX_INT_ACK_MASK,\
		.status_reg = mmDC_HPD ## reg_num ## _INT_STATUS,\
		.funcs = &hpd_rx_irq_info_funcs\
	पूर्ण

#घोषणा pflip_पूर्णांक_entry(reg_num)\
	[DC_IRQ_SOURCE_PFLIP1 + reg_num] = अणु\
		.enable_reg = mmDCP ## reg_num ## _GRPH_INTERRUPT_CONTROL,\
		.enable_mask =\
		GRPH_INTERRUPT_CONTROL__GRPH_PFLIP_INT_MASK_MASK,\
		.enable_value = अणु\
			GRPH_INTERRUPT_CONTROL__GRPH_PFLIP_INT_MASK_MASK,\
			~GRPH_INTERRUPT_CONTROL__GRPH_PFLIP_INT_MASK_MASKपूर्ण,\
		.ack_reg = mmDCP ## reg_num ## _GRPH_INTERRUPT_STATUS,\
		.ack_mask = GRPH_INTERRUPT_STATUS__GRPH_PFLIP_INT_CLEAR_MASK,\
		.ack_value = GRPH_INTERRUPT_STATUS__GRPH_PFLIP_INT_CLEAR_MASK,\
		.status_reg = mmDCP ## reg_num ##_GRPH_INTERRUPT_STATUS,\
		.funcs = &pflip_irq_info_funcs\
 	पूर्ण

#घोषणा vupdate_पूर्णांक_entry(reg_num)\
	[DC_IRQ_SOURCE_VUPDATE1 + reg_num] = अणु\
		.enable_reg = mmCRTC ## reg_num ## _CRTC_INTERRUPT_CONTROL,\
		.enable_mask =\
		CRTC_INTERRUPT_CONTROL__CRTC_V_UPDATE_INT_MSK_MASK,\
		.enable_value = अणु\
			CRTC_INTERRUPT_CONTROL__CRTC_V_UPDATE_INT_MSK_MASK,\
			~CRTC_INTERRUPT_CONTROL__CRTC_V_UPDATE_INT_MSK_MASKपूर्ण,\
		.ack_reg = mmCRTC ## reg_num ## _CRTC_V_UPDATE_INT_STATUS,\
		.ack_mask =\
		CRTC_V_UPDATE_INT_STATUS__CRTC_V_UPDATE_INT_CLEAR_MASK,\
		.ack_value =\
		CRTC_V_UPDATE_INT_STATUS__CRTC_V_UPDATE_INT_CLEAR_MASK,\
		.funcs = &vblank_irq_info_funcs\
	पूर्ण

#घोषणा vblank_पूर्णांक_entry(reg_num)\
	[DC_IRQ_SOURCE_VBLANK1 + reg_num] = अणु\
		.enable_reg = mmLB ## reg_num ## _INT_MASK,\
		.enable_mask =\
			INT_MASK__VBLANK_INT_MASK,\
		.enable_value = अणु\
			INT_MASK__VBLANK_INT_MASK,\
			~INT_MASK__VBLANK_INT_MASKपूर्ण,\
		.ack_reg = mmLB ## reg_num ## _VBLANK_STATUS,\
		.ack_mask =\
		VBLANK_STATUS__VBLANK_ACK_MASK,\
		.ack_value =\
		VBLANK_STATUS__VBLANK_ACK_MASK,\
		.funcs = &vblank_irq_info_funcs_dce60\
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
irq_source_info_dce60[DAL_IRQ_SOURCES_NUMBER] = अणु
	[DC_IRQ_SOURCE_INVALID] = dummy_irq_entry(),
	hpd_पूर्णांक_entry(1),
	hpd_पूर्णांक_entry(2),
	hpd_पूर्णांक_entry(3),
	hpd_पूर्णांक_entry(4),
	hpd_पूर्णांक_entry(5),
	hpd_पूर्णांक_entry(6),
	hpd_rx_पूर्णांक_entry(1),
	hpd_rx_पूर्णांक_entry(2),
	hpd_rx_पूर्णांक_entry(3),
	hpd_rx_पूर्णांक_entry(4),
	hpd_rx_पूर्णांक_entry(5),
	hpd_rx_पूर्णांक_entry(6),
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

क्रमागत dc_irq_source to_dal_irq_source_dce60(
		काष्ठा irq_service *irq_service,
		uपूर्णांक32_t src_id,
		uपूर्णांक32_t ext_id)
अणु
	चयन (src_id) अणु
	हाल VISLANDS30_IV_SRCID_D1_VBLANK:
		वापस DC_IRQ_SOURCE_VBLANK1;
	हाल VISLANDS30_IV_SRCID_D2_VBLANK:
		वापस DC_IRQ_SOURCE_VBLANK2;
	हाल VISLANDS30_IV_SRCID_D3_VBLANK:
		वापस DC_IRQ_SOURCE_VBLANK3;
	हाल VISLANDS30_IV_SRCID_D4_VBLANK:
		वापस DC_IRQ_SOURCE_VBLANK4;
	हाल VISLANDS30_IV_SRCID_D5_VBLANK:
		वापस DC_IRQ_SOURCE_VBLANK5;
	हाल VISLANDS30_IV_SRCID_D6_VBLANK:
		वापस DC_IRQ_SOURCE_VBLANK6;
	हाल VISLANDS30_IV_SRCID_D1_V_UPDATE_INT:
		वापस DC_IRQ_SOURCE_VUPDATE1;
	हाल VISLANDS30_IV_SRCID_D2_V_UPDATE_INT:
		वापस DC_IRQ_SOURCE_VUPDATE2;
	हाल VISLANDS30_IV_SRCID_D3_V_UPDATE_INT:
		वापस DC_IRQ_SOURCE_VUPDATE3;
	हाल VISLANDS30_IV_SRCID_D4_V_UPDATE_INT:
		वापस DC_IRQ_SOURCE_VUPDATE4;
	हाल VISLANDS30_IV_SRCID_D5_V_UPDATE_INT:
		वापस DC_IRQ_SOURCE_VUPDATE5;
	हाल VISLANDS30_IV_SRCID_D6_V_UPDATE_INT:
		वापस DC_IRQ_SOURCE_VUPDATE6;
	हाल VISLANDS30_IV_SRCID_D1_GRPH_PFLIP:
		वापस DC_IRQ_SOURCE_PFLIP1;
	हाल VISLANDS30_IV_SRCID_D2_GRPH_PFLIP:
		वापस DC_IRQ_SOURCE_PFLIP2;
	हाल VISLANDS30_IV_SRCID_D3_GRPH_PFLIP:
		वापस DC_IRQ_SOURCE_PFLIP3;
	हाल VISLANDS30_IV_SRCID_D4_GRPH_PFLIP:
		वापस DC_IRQ_SOURCE_PFLIP4;
	हाल VISLANDS30_IV_SRCID_D5_GRPH_PFLIP:
		वापस DC_IRQ_SOURCE_PFLIP5;
	हाल VISLANDS30_IV_SRCID_D6_GRPH_PFLIP:
		वापस DC_IRQ_SOURCE_PFLIP6;

	हाल VISLANDS30_IV_SRCID_HOTPLUG_DETECT_A:
		/* generic src_id क्रम all HPD and HPDRX पूर्णांकerrupts */
		चयन (ext_id) अणु
		हाल VISLANDS30_IV_EXTID_HOTPLUG_DETECT_A:
			वापस DC_IRQ_SOURCE_HPD1;
		हाल VISLANDS30_IV_EXTID_HOTPLUG_DETECT_B:
			वापस DC_IRQ_SOURCE_HPD2;
		हाल VISLANDS30_IV_EXTID_HOTPLUG_DETECT_C:
			वापस DC_IRQ_SOURCE_HPD3;
		हाल VISLANDS30_IV_EXTID_HOTPLUG_DETECT_D:
			वापस DC_IRQ_SOURCE_HPD4;
		हाल VISLANDS30_IV_EXTID_HOTPLUG_DETECT_E:
			वापस DC_IRQ_SOURCE_HPD5;
		हाल VISLANDS30_IV_EXTID_HOTPLUG_DETECT_F:
			वापस DC_IRQ_SOURCE_HPD6;
		हाल VISLANDS30_IV_EXTID_HPD_RX_A:
			वापस DC_IRQ_SOURCE_HPD1RX;
		हाल VISLANDS30_IV_EXTID_HPD_RX_B:
			वापस DC_IRQ_SOURCE_HPD2RX;
		हाल VISLANDS30_IV_EXTID_HPD_RX_C:
			वापस DC_IRQ_SOURCE_HPD3RX;
		हाल VISLANDS30_IV_EXTID_HPD_RX_D:
			वापस DC_IRQ_SOURCE_HPD4RX;
		हाल VISLANDS30_IV_EXTID_HPD_RX_E:
			वापस DC_IRQ_SOURCE_HPD5RX;
		हाल VISLANDS30_IV_EXTID_HPD_RX_F:
			वापस DC_IRQ_SOURCE_HPD6RX;
		शेष:
			वापस DC_IRQ_SOURCE_INVALID;
		पूर्ण
		अवरोध;

	शेष:
		वापस DC_IRQ_SOURCE_INVALID;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा irq_service_funcs irq_service_funcs_dce60 = अणु
		.to_dal_irq_source = to_dal_irq_source_dce60
पूर्ण;

अटल व्योम dce60_irq_स्थिरruct(
	काष्ठा irq_service *irq_service,
	काष्ठा irq_service_init_data *init_data)
अणु
	dal_irq_service_स्थिरruct(irq_service, init_data);

	irq_service->info = irq_source_info_dce60;
	irq_service->funcs = &irq_service_funcs_dce60;
पूर्ण

काष्ठा irq_service *dal_irq_service_dce60_create(
	काष्ठा irq_service_init_data *init_data)
अणु
	काष्ठा irq_service *irq_service = kzalloc(माप(*irq_service),
						  GFP_KERNEL);

	अगर (!irq_service)
		वापस शून्य;

	dce60_irq_स्थिरruct(irq_service, init_data);
	वापस irq_service;
पूर्ण


