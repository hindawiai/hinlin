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

#अगर_अघोषित __DAL_IRQ_SERVICE_DCE110_H__
#घोषणा __DAL_IRQ_SERVICE_DCE110_H__

#समावेश "../irq_service.h"

काष्ठा irq_service *dal_irq_service_dce110_create(
	काष्ठा irq_service_init_data *init_data);

क्रमागत dc_irq_source to_dal_irq_source_dce110(
		काष्ठा irq_service *irq_service,
		uपूर्णांक32_t src_id,
		uपूर्णांक32_t ext_id);

bool dal_irq_service_dummy_set(
	काष्ठा irq_service *irq_service,
	स्थिर काष्ठा irq_source_info *info,
	bool enable);

bool dal_irq_service_dummy_ack(
	काष्ठा irq_service *irq_service,
	स्थिर काष्ठा irq_source_info *info);

bool dce110_vblank_set(
	काष्ठा irq_service *irq_service,
	स्थिर काष्ठा irq_source_info *info,
	bool enable);

#पूर्ण_अगर
