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

#अगर_अघोषित __DAL_IRQ_SERVICE_INTERFACE_H__
#घोषणा __DAL_IRQ_SERVICE_INTERFACE_H__

काष्ठा irq_service_init_data अणु
	काष्ठा dc_context *ctx;
पूर्ण;

काष्ठा irq_service;

व्योम dal_irq_service_destroy(काष्ठा irq_service **irq_service);

bool dal_irq_service_set(
	काष्ठा irq_service *irq_service,
	क्रमागत dc_irq_source source,
	bool enable);

bool dal_irq_service_ack(
	काष्ठा irq_service *irq_service,
	क्रमागत dc_irq_source source);

क्रमागत dc_irq_source dal_irq_service_to_irq_source(
		काष्ठा irq_service *irq_service,
		uपूर्णांक32_t src_id,
		uपूर्णांक32_t ext_id);

#पूर्ण_अगर
