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

#समावेश "include/irq_service_interface.h"
#समावेश "include/logger_interface.h"

#समावेश "dce110/irq_service_dce110.h"

#अगर defined(CONFIG_DRM_AMD_DC_SI)
#समावेश "dce60/irq_service_dce60.h"
#पूर्ण_अगर

#समावेश "dce80/irq_service_dce80.h"

#समावेश "dce120/irq_service_dce120.h"


#अगर defined(CONFIG_DRM_AMD_DC_DCN)
#समावेश "dcn10/irq_service_dcn10.h"
#पूर्ण_अगर

#समावेश "reg_helper.h"
#समावेश "irq_service.h"



#घोषणा CTX \
		irq_service->ctx
#घोषणा DC_LOGGER \
	irq_service->ctx->logger

व्योम dal_irq_service_स्थिरruct(
	काष्ठा irq_service *irq_service,
	काष्ठा irq_service_init_data *init_data)
अणु
	अगर (!init_data || !init_data->ctx) अणु
		BREAK_TO_DEBUGGER();
		वापस;
	पूर्ण

	irq_service->ctx = init_data->ctx;
पूर्ण

व्योम dal_irq_service_destroy(काष्ठा irq_service **irq_service)
अणु
	अगर (!irq_service || !*irq_service) अणु
		BREAK_TO_DEBUGGER();
		वापस;
	पूर्ण

	kमुक्त(*irq_service);

	*irq_service = शून्य;
पूर्ण

अटल स्थिर काष्ठा irq_source_info *find_irq_source_info(
	काष्ठा irq_service *irq_service,
	क्रमागत dc_irq_source source)
अणु
	अगर (source >= DAL_IRQ_SOURCES_NUMBER || source < DC_IRQ_SOURCE_INVALID)
		वापस शून्य;

	वापस &irq_service->info[source];
पूर्ण

व्योम dal_irq_service_set_generic(
	काष्ठा irq_service *irq_service,
	स्थिर काष्ठा irq_source_info *info,
	bool enable)
अणु
	uपूर्णांक32_t addr = info->enable_reg;
	uपूर्णांक32_t value = dm_पढ़ो_reg(irq_service->ctx, addr);

	value = (value & ~info->enable_mask) |
		(info->enable_value[enable ? 0 : 1] & info->enable_mask);
	dm_ग_लिखो_reg(irq_service->ctx, addr, value);
पूर्ण

bool dal_irq_service_set(
	काष्ठा irq_service *irq_service,
	क्रमागत dc_irq_source source,
	bool enable)
अणु
	स्थिर काष्ठा irq_source_info *info =
		find_irq_source_info(irq_service, source);

	अगर (!info) अणु
		DC_LOG_ERROR("%s: cannot find irq info table entry for %d\n",
			__func__,
			source);
		वापस false;
	पूर्ण

	dal_irq_service_ack(irq_service, source);

	अगर (info->funcs->set)
		वापस info->funcs->set(irq_service, info, enable);

	dal_irq_service_set_generic(irq_service, info, enable);

	वापस true;
पूर्ण

व्योम dal_irq_service_ack_generic(
	काष्ठा irq_service *irq_service,
	स्थिर काष्ठा irq_source_info *info)
अणु
	uपूर्णांक32_t addr = info->ack_reg;
	uपूर्णांक32_t value = dm_पढ़ो_reg(irq_service->ctx, addr);

	value = (value & ~info->ack_mask) |
		(info->ack_value & info->ack_mask);
	dm_ग_लिखो_reg(irq_service->ctx, addr, value);
पूर्ण

bool dal_irq_service_ack(
	काष्ठा irq_service *irq_service,
	क्रमागत dc_irq_source source)
अणु
	स्थिर काष्ठा irq_source_info *info =
		find_irq_source_info(irq_service, source);

	अगर (!info) अणु
		DC_LOG_ERROR("%s: cannot find irq info table entry for %d\n",
			__func__,
			source);
		वापस false;
	पूर्ण

	अगर (info->funcs->ack)
		वापस info->funcs->ack(irq_service, info);

	dal_irq_service_ack_generic(irq_service, info);

	वापस true;
पूर्ण

क्रमागत dc_irq_source dal_irq_service_to_irq_source(
		काष्ठा irq_service *irq_service,
		uपूर्णांक32_t src_id,
		uपूर्णांक32_t ext_id)
अणु
	वापस irq_service->funcs->to_dal_irq_source(
		irq_service,
		src_id,
		ext_id);
पूर्ण
