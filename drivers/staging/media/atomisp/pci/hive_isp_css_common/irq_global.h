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

#अगर_अघोषित __IRQ_GLOBAL_H_INCLUDED__
#घोषणा __IRQ_GLOBAL_H_INCLUDED__

#समावेश <प्रणाली_local.h>

#घोषणा IS_IRQ_VERSION_2
#घोषणा IS_IRQ_MAP_VERSION_2

/* We cannot include the (hrt host ID) file defining the "CSS_RECEIVER" property without side effects */
#अगर_अघोषित HAS_NO_RX
#समावेश "irq_types_hrt.h"
#पूर्ण_अगर

/* The IRQ is not mapped unअगरormly on its related पूर्णांकerfaces */
#घोषणा	IRQ_SW_CHANNEL_OFFSET	hrt_isp_css_irq_sw_pin_0

प्रकार क्रमागत अणु
	IRQ_SW_CHANNEL0_ID = hrt_isp_css_irq_sw_pin_0 - IRQ_SW_CHANNEL_OFFSET,
	IRQ_SW_CHANNEL1_ID = hrt_isp_css_irq_sw_pin_1 - IRQ_SW_CHANNEL_OFFSET,
	N_IRQ_SW_CHANNEL_ID
पूर्ण irq_sw_channel_id_t;

#पूर्ण_अगर /* __IRQ_GLOBAL_H_INCLUDED__ */
