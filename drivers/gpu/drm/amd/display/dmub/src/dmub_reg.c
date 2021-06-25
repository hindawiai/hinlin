<शैली गुरु>
/*
 * Copyright 2019 Advanced Micro Devices, Inc.
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

#समावेश "dmub_reg.h"
#समावेश "../dmub_srv.h"

काष्ठा dmub_reg_value_masks अणु
	uपूर्णांक32_t value;
	uपूर्णांक32_t mask;
पूर्ण;

अटल अंतरभूत व्योम
set_reg_field_value_masks(काष्ठा dmub_reg_value_masks *field_value_mask,
			  uपूर्णांक32_t value, uपूर्णांक32_t mask, uपूर्णांक8_t shअगरt)
अणु
	field_value_mask->value =
		(field_value_mask->value & ~mask) | (mask & (value << shअगरt));
	field_value_mask->mask = field_value_mask->mask | mask;
पूर्ण

अटल व्योम set_reg_field_values(काष्ठा dmub_reg_value_masks *field_value_mask,
				 uपूर्णांक32_t addr, पूर्णांक n, uपूर्णांक8_t shअगरt1,
				 uपूर्णांक32_t mask1, uपूर्णांक32_t field_value1,
				 बहु_सूची ap)
अणु
	uपूर्णांक32_t shअगरt, mask, field_value;
	पूर्णांक i = 1;

	/* gather all bits value/mask getting updated in this रेजिस्टर */
	set_reg_field_value_masks(field_value_mask, field_value1, mask1,
				  shअगरt1);

	जबतक (i < n) अणु
		shअगरt = बहु_तर्क(ap, uपूर्णांक32_t);
		mask = बहु_तर्क(ap, uपूर्णांक32_t);
		field_value = बहु_तर्क(ap, uपूर्णांक32_t);

		set_reg_field_value_masks(field_value_mask, field_value, mask,
					  shअगरt);
		i++;
	पूर्ण
पूर्ण

अटल अंतरभूत uपूर्णांक32_t get_reg_field_value_ex(uपूर्णांक32_t reg_value, uपूर्णांक32_t mask,
					      uपूर्णांक8_t shअगरt)
अणु
	वापस (mask & reg_value) >> shअगरt;
पूर्ण

व्योम dmub_reg_update(काष्ठा dmub_srv *srv, uपूर्णांक32_t addr, पूर्णांक n, uपूर्णांक8_t shअगरt1,
		     uपूर्णांक32_t mask1, uपूर्णांक32_t field_value1, ...)
अणु
	काष्ठा dmub_reg_value_masks field_value_mask = अणु 0 पूर्ण;
	uपूर्णांक32_t reg_val;
	बहु_सूची ap;

	बहु_शुरू(ap, field_value1);
	set_reg_field_values(&field_value_mask, addr, n, shअगरt1, mask1,
			     field_value1, ap);
	बहु_पूर्ण(ap);

	reg_val = srv->funcs.reg_पढ़ो(srv->user_ctx, addr);
	reg_val = (reg_val & ~field_value_mask.mask) | field_value_mask.value;
	srv->funcs.reg_ग_लिखो(srv->user_ctx, addr, reg_val);
पूर्ण

व्योम dmub_reg_set(काष्ठा dmub_srv *srv, uपूर्णांक32_t addr, uपूर्णांक32_t reg_val, पूर्णांक n,
		  uपूर्णांक8_t shअगरt1, uपूर्णांक32_t mask1, uपूर्णांक32_t field_value1, ...)
अणु
	काष्ठा dmub_reg_value_masks field_value_mask = अणु 0 पूर्ण;
	बहु_सूची ap;

	बहु_शुरू(ap, field_value1);
	set_reg_field_values(&field_value_mask, addr, n, shअगरt1, mask1,
			     field_value1, ap);
	बहु_पूर्ण(ap);

	reg_val = (reg_val & ~field_value_mask.mask) | field_value_mask.value;
	srv->funcs.reg_ग_लिखो(srv->user_ctx, addr, reg_val);
पूर्ण

व्योम dmub_reg_get(काष्ठा dmub_srv *srv, uपूर्णांक32_t addr, uपूर्णांक8_t shअगरt,
		  uपूर्णांक32_t mask, uपूर्णांक32_t *field_value)
अणु
	uपूर्णांक32_t reg_val = srv->funcs.reg_पढ़ो(srv->user_ctx, addr);
	*field_value = get_reg_field_value_ex(reg_val, mask, shअगरt);
पूर्ण
