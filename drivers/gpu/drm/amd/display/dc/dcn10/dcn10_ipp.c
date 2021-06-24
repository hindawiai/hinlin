<शैली गुरु>
/*
 * Copyright 2017 Advanced Micro Devices, Inc.
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
#समावेश "dcn10_ipp.h"
#समावेश "reg_helper.h"

#घोषणा REG(reg) \
	(ippn10->regs->reg)

#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	ippn10->ipp_shअगरt->field_name, ippn10->ipp_mask->field_name

#घोषणा CTX \
	ippn10->base.ctx

/*****************************************/
/* Conकाष्ठाor, Deकाष्ठाor               */
/*****************************************/

अटल व्योम dcn10_ipp_destroy(काष्ठा input_pixel_processor **ipp)
अणु
	kमुक्त(TO_DCN10_IPP(*ipp));
	*ipp = शून्य;
पूर्ण

अटल स्थिर काष्ठा ipp_funcs dcn10_ipp_funcs = अणु
	.ipp_destroy			= dcn10_ipp_destroy
पूर्ण;

अटल स्थिर काष्ठा ipp_funcs dcn20_ipp_funcs = अणु
	.ipp_destroy			= dcn10_ipp_destroy
पूर्ण;

व्योम dcn10_ipp_स्थिरruct(
	काष्ठा dcn10_ipp *ippn10,
	काष्ठा dc_context *ctx,
	पूर्णांक inst,
	स्थिर काष्ठा dcn10_ipp_रेजिस्टरs *regs,
	स्थिर काष्ठा dcn10_ipp_shअगरt *ipp_shअगरt,
	स्थिर काष्ठा dcn10_ipp_mask *ipp_mask)
अणु
	ippn10->base.ctx = ctx;
	ippn10->base.inst = inst;
	ippn10->base.funcs = &dcn10_ipp_funcs;

	ippn10->regs = regs;
	ippn10->ipp_shअगरt = ipp_shअगरt;
	ippn10->ipp_mask = ipp_mask;
पूर्ण

व्योम dcn20_ipp_स्थिरruct(
	काष्ठा dcn10_ipp *ippn10,
	काष्ठा dc_context *ctx,
	पूर्णांक inst,
	स्थिर काष्ठा dcn10_ipp_रेजिस्टरs *regs,
	स्थिर काष्ठा dcn10_ipp_shअगरt *ipp_shअगरt,
	स्थिर काष्ठा dcn10_ipp_mask *ipp_mask)
अणु
	ippn10->base.ctx = ctx;
	ippn10->base.inst = inst;
	ippn10->base.funcs = &dcn20_ipp_funcs;

	ippn10->regs = regs;
	ippn10->ipp_shअगरt = ipp_shअगरt;
	ippn10->ipp_mask = ipp_mask;
पूर्ण
