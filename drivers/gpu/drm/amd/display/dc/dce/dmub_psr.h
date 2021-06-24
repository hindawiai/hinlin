<शैली गुरु>
/*
 * Copyright 2012-16 Advanced Micro Devices, Inc.
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

#अगर_अघोषित _DMUB_PSR_H_
#घोषणा _DMUB_PSR_H_

#समावेश "os_types.h"
#समावेश "dc_link.h"

काष्ठा dmub_psr अणु
	काष्ठा dc_context *ctx;
	स्थिर काष्ठा dmub_psr_funcs *funcs;
पूर्ण;

काष्ठा dmub_psr_funcs अणु
	bool (*psr_copy_settings)(काष्ठा dmub_psr *dmub, काष्ठा dc_link *link, काष्ठा psr_context *psr_context);
	व्योम (*psr_enable)(काष्ठा dmub_psr *dmub, bool enable, bool रुको);
	व्योम (*psr_get_state)(काष्ठा dmub_psr *dmub, क्रमागत dc_psr_state *dc_psr_state);
	व्योम (*psr_set_level)(काष्ठा dmub_psr *dmub, uपूर्णांक16_t psr_level);
	व्योम (*psr_क्रमce_अटल)(काष्ठा dmub_psr *dmub);
	व्योम (*psr_get_residency)(काष्ठा dmub_psr *dmub, uपूर्णांक32_t *residency);
पूर्ण;

काष्ठा dmub_psr *dmub_psr_create(काष्ठा dc_context *ctx);
व्योम dmub_psr_destroy(काष्ठा dmub_psr **dmub);


#पूर्ण_अगर /* _DMUB_PSR_H_ */
