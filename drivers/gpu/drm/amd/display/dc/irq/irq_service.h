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

#अगर_अघोषित __DAL_IRQ_SERVICE_H__
#घोषणा __DAL_IRQ_SERVICE_H__

#समावेश "include/irq_service_interface.h"

#समावेश "irq_types.h"

काष्ठा irq_service;
काष्ठा irq_source_info;

काष्ठा irq_source_info_funcs अणु
	bool (*set)(
		काष्ठा irq_service *irq_service,
		स्थिर काष्ठा irq_source_info *info,
		bool enable);
	bool (*ack)(
		काष्ठा irq_service *irq_service,
		स्थिर काष्ठा irq_source_info *info);
पूर्ण;

काष्ठा irq_source_info अणु
	uपूर्णांक32_t src_id;
	uपूर्णांक32_t ext_id;
	uपूर्णांक32_t enable_reg;
	uपूर्णांक32_t enable_mask;
	uपूर्णांक32_t enable_value[2];
	uपूर्णांक32_t ack_reg;
	uपूर्णांक32_t ack_mask;
	uपूर्णांक32_t ack_value;
	uपूर्णांक32_t status_reg;
	स्थिर काष्ठा irq_source_info_funcs *funcs;
पूर्ण;

काष्ठा irq_service_funcs अणु
	क्रमागत dc_irq_source (*to_dal_irq_source)(
			काष्ठा irq_service *irq_service,
			uपूर्णांक32_t src_id,
			uपूर्णांक32_t ext_id);
पूर्ण;

काष्ठा irq_service अणु
	काष्ठा dc_context *ctx;
	स्थिर काष्ठा irq_source_info *info;
	स्थिर काष्ठा irq_service_funcs *funcs;
पूर्ण;

व्योम dal_irq_service_स्थिरruct(
	काष्ठा irq_service *irq_service,
	काष्ठा irq_service_init_data *init_data);

व्योम dal_irq_service_ack_generic(
	काष्ठा irq_service *irq_service,
	स्थिर काष्ठा irq_source_info *info);

व्योम dal_irq_service_set_generic(
	काष्ठा irq_service *irq_service,
	स्थिर काष्ठा irq_source_info *info,
	bool enable);

#पूर्ण_अगर
