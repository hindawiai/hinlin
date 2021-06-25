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

#अगर_अघोषित __DAL_IRQ_TYPES_H__
#घोषणा __DAL_IRQ_TYPES_H__

#समावेश "os_types.h"

काष्ठा dc_context;

प्रकार व्योम (*पूर्णांकerrupt_handler)(व्योम *);

प्रकार व्योम *irq_handler_idx;
#घोषणा DAL_INVALID_IRQ_HANDLER_IDX शून्य

/* The order of the IRQ sources is important and MUST match the one's
of base driver */
क्रमागत dc_irq_source अणु
	/* Use as mask to specअगरy invalid irq source */
	DC_IRQ_SOURCE_INVALID = 0,

	DC_IRQ_SOURCE_HPD1,
	DC_IRQ_SOURCE_HPD2,
	DC_IRQ_SOURCE_HPD3,
	DC_IRQ_SOURCE_HPD4,
	DC_IRQ_SOURCE_HPD5,
	DC_IRQ_SOURCE_HPD6,

	DC_IRQ_SOURCE_HPD1RX,
	DC_IRQ_SOURCE_HPD2RX,
	DC_IRQ_SOURCE_HPD3RX,
	DC_IRQ_SOURCE_HPD4RX,
	DC_IRQ_SOURCE_HPD5RX,
	DC_IRQ_SOURCE_HPD6RX,

	DC_IRQ_SOURCE_I2C_DDC1,
	DC_IRQ_SOURCE_I2C_DDC2,
	DC_IRQ_SOURCE_I2C_DDC3,
	DC_IRQ_SOURCE_I2C_DDC4,
	DC_IRQ_SOURCE_I2C_DDC5,
	DC_IRQ_SOURCE_I2C_DDC6,

	DC_IRQ_SOURCE_DPSINK1,
	DC_IRQ_SOURCE_DPSINK2,
	DC_IRQ_SOURCE_DPSINK3,
	DC_IRQ_SOURCE_DPSINK4,
	DC_IRQ_SOURCE_DPSINK5,
	DC_IRQ_SOURCE_DPSINK6,

	DC_IRQ_SOURCE_TIMER,

	DC_IRQ_SOURCE_PFLIP_FIRST,
	DC_IRQ_SOURCE_PFLIP1 = DC_IRQ_SOURCE_PFLIP_FIRST,
	DC_IRQ_SOURCE_PFLIP2,
	DC_IRQ_SOURCE_PFLIP3,
	DC_IRQ_SOURCE_PFLIP4,
	DC_IRQ_SOURCE_PFLIP5,
	DC_IRQ_SOURCE_PFLIP6,
	DC_IRQ_SOURCE_PFLIP_UNDERLAY0,
	DC_IRQ_SOURCE_PFLIP_LAST = DC_IRQ_SOURCE_PFLIP_UNDERLAY0,

	DC_IRQ_SOURCE_GPIOPAD0,
	DC_IRQ_SOURCE_GPIOPAD1,
	DC_IRQ_SOURCE_GPIOPAD2,
	DC_IRQ_SOURCE_GPIOPAD3,
	DC_IRQ_SOURCE_GPIOPAD4,
	DC_IRQ_SOURCE_GPIOPAD5,
	DC_IRQ_SOURCE_GPIOPAD6,
	DC_IRQ_SOURCE_GPIOPAD7,
	DC_IRQ_SOURCE_GPIOPAD8,
	DC_IRQ_SOURCE_GPIOPAD9,
	DC_IRQ_SOURCE_GPIOPAD10,
	DC_IRQ_SOURCE_GPIOPAD11,
	DC_IRQ_SOURCE_GPIOPAD12,
	DC_IRQ_SOURCE_GPIOPAD13,
	DC_IRQ_SOURCE_GPIOPAD14,
	DC_IRQ_SOURCE_GPIOPAD15,
	DC_IRQ_SOURCE_GPIOPAD16,
	DC_IRQ_SOURCE_GPIOPAD17,
	DC_IRQ_SOURCE_GPIOPAD18,
	DC_IRQ_SOURCE_GPIOPAD19,
	DC_IRQ_SOURCE_GPIOPAD20,
	DC_IRQ_SOURCE_GPIOPAD21,
	DC_IRQ_SOURCE_GPIOPAD22,
	DC_IRQ_SOURCE_GPIOPAD23,
	DC_IRQ_SOURCE_GPIOPAD24,
	DC_IRQ_SOURCE_GPIOPAD25,
	DC_IRQ_SOURCE_GPIOPAD26,
	DC_IRQ_SOURCE_GPIOPAD27,
	DC_IRQ_SOURCE_GPIOPAD28,
	DC_IRQ_SOURCE_GPIOPAD29,
	DC_IRQ_SOURCE_GPIOPAD30,

	DC_IRQ_SOURCE_DC1UNDERFLOW,
	DC_IRQ_SOURCE_DC2UNDERFLOW,
	DC_IRQ_SOURCE_DC3UNDERFLOW,
	DC_IRQ_SOURCE_DC4UNDERFLOW,
	DC_IRQ_SOURCE_DC5UNDERFLOW,
	DC_IRQ_SOURCE_DC6UNDERFLOW,

	DC_IRQ_SOURCE_DMCU_SCP,
	DC_IRQ_SOURCE_VBIOS_SW,

	DC_IRQ_SOURCE_VUPDATE1,
	DC_IRQ_SOURCE_VUPDATE2,
	DC_IRQ_SOURCE_VUPDATE3,
	DC_IRQ_SOURCE_VUPDATE4,
	DC_IRQ_SOURCE_VUPDATE5,
	DC_IRQ_SOURCE_VUPDATE6,

	DC_IRQ_SOURCE_VBLANK1,
	DC_IRQ_SOURCE_VBLANK2,
	DC_IRQ_SOURCE_VBLANK3,
	DC_IRQ_SOURCE_VBLANK4,
	DC_IRQ_SOURCE_VBLANK5,
	DC_IRQ_SOURCE_VBLANK6,

	DC_IRQ_SOURCE_DC1_VLINE0,
	DC_IRQ_SOURCE_DC2_VLINE0,
	DC_IRQ_SOURCE_DC3_VLINE0,
	DC_IRQ_SOURCE_DC4_VLINE0,
	DC_IRQ_SOURCE_DC5_VLINE0,
	DC_IRQ_SOURCE_DC6_VLINE0,

	DC_IRQ_SOURCE_DC1_VLINE1,
	DC_IRQ_SOURCE_DC2_VLINE1,
	DC_IRQ_SOURCE_DC3_VLINE1,
	DC_IRQ_SOURCE_DC4_VLINE1,
	DC_IRQ_SOURCE_DC5_VLINE1,
	DC_IRQ_SOURCE_DC6_VLINE1,
	DC_IRQ_DMCUB_OUTBOX1,
	DC_IRQ_SOURCE_DMCUB_OUTBOX0,

	DAL_IRQ_SOURCES_NUMBER
पूर्ण;

क्रमागत irq_type
अणु
	IRQ_TYPE_PFLIP = DC_IRQ_SOURCE_PFLIP1,
	IRQ_TYPE_VUPDATE = DC_IRQ_SOURCE_VUPDATE1,
	IRQ_TYPE_VBLANK = DC_IRQ_SOURCE_VBLANK1,
	IRQ_TYPE_VLINE0 = DC_IRQ_SOURCE_DC1_VLINE0,
पूर्ण;

#घोषणा DAL_VALID_IRQ_SRC_NUM(src) \
	((src) <= DAL_IRQ_SOURCES_NUMBER && (src) > DC_IRQ_SOURCE_INVALID)

/* Number of Page Flip IRQ Sources. */
#घोषणा DAL_PFLIP_IRQ_SRC_NUM \
	(DC_IRQ_SOURCE_PFLIP_LAST - DC_IRQ_SOURCE_PFLIP_FIRST + 1)

/* the number of contexts may be expanded in the future based on needs */
क्रमागत dc_पूर्णांकerrupt_context अणु
	INTERRUPT_LOW_IRQ_CONTEXT = 0,
	INTERRUPT_HIGH_IRQ_CONTEXT,
	INTERRUPT_CONTEXT_NUMBER
पूर्ण;

क्रमागत dc_पूर्णांकerrupt_porlarity अणु
	INTERRUPT_POLARITY_DEFAULT = 0,
	INTERRUPT_POLARITY_LOW = INTERRUPT_POLARITY_DEFAULT,
	INTERRUPT_POLARITY_HIGH,
	INTERRUPT_POLARITY_BOTH
पूर्ण;

#घोषणा DC_DECODE_INTERRUPT_POLARITY(पूर्णांक_polarity) \
	(पूर्णांक_polarity == INTERRUPT_POLARITY_LOW) ? "Low" : \
	(पूर्णांक_polarity == INTERRUPT_POLARITY_HIGH) ? "High" : \
	(पूर्णांक_polarity == INTERRUPT_POLARITY_BOTH) ? "Both" : "Invalid"

काष्ठा dc_समयr_पूर्णांकerrupt_params अणु
	uपूर्णांक32_t micro_sec_पूर्णांकerval;
	क्रमागत dc_पूर्णांकerrupt_context पूर्णांक_context;
पूर्ण;

काष्ठा dc_पूर्णांकerrupt_params अणु
	/* The polarity *change* which will trigger an पूर्णांकerrupt.
	 * If 'requested_polarity == INTERRUPT_POLARITY_BOTH', then
	 * 'current_polarity' must be initialised. */
	क्रमागत dc_पूर्णांकerrupt_porlarity requested_polarity;
	/* If 'requested_polarity == INTERRUPT_POLARITY_BOTH',
	 * 'current_polarity' should contain the current state, which means
	 * the पूर्णांकerrupt will be triggered when state changes from what is,
	 * in 'current_polarity'. */
	क्रमागत dc_पूर्णांकerrupt_porlarity current_polarity;
	क्रमागत dc_irq_source irq_source;
	क्रमागत dc_पूर्णांकerrupt_context पूर्णांक_context;
पूर्ण;

#पूर्ण_अगर
