<शैली गुरु>
/*
 * Copyright 2015 Advanced Micro Devices, Inc.
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
 */

#अगर_अघोषित _PP_INTERRUPT_H_
#घोषणा _PP_INTERRUPT_H_

क्रमागत amd_thermal_irq अणु
	AMD_THERMAL_IRQ_LOW_TO_HIGH = 0,
	AMD_THERMAL_IRQ_HIGH_TO_LOW,

	AMD_THERMAL_IRQ_LAST
पूर्ण;

/* The type of the पूर्णांकerrupt callback functions in PowerPlay */
प्रकार पूर्णांक (*irq_handler_func_t)(व्योम *निजी_data,
				अचिन्हित src_id, स्थिर uपूर्णांक32_t *iv_entry);

/* Event Manager action chain list inक्रमmation */
काष्ठा pp_पूर्णांकerrupt_registration_info अणु
	irq_handler_func_t call_back; /* Poपूर्णांकer to callback function */
	व्योम *context;                   /* Poपूर्णांकer to callback function context */
	uपूर्णांक32_t src_id;               /* Registered पूर्णांकerrupt id */
	स्थिर uपूर्णांक32_t *iv_entry;
पूर्ण;

#पूर्ण_अगर /* _PP_INTERRUPT_H_ */
