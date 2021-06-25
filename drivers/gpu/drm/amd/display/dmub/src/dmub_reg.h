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

#अगर_अघोषित _DMUB_REG_H_
#घोषणा _DMUB_REG_H_

#समावेश "../inc/dmub_cmd.h"

काष्ठा dmub_srv;

/* Register offset and field lookup. */

#घोषणा BASE(seg) BASE_INNER(seg)

#घोषणा REG_OFFSET(reg_name) (BASE(mm##reg_name##_BASE_IDX) + mm##reg_name)

#घोषणा FD_SHIFT(reg_name, field) reg_name##__##field##__SHIFT

#घोषणा FD_MASK(reg_name, field) reg_name##__##field##_MASK

#घोषणा REG(reg) (REGS)->offset.reg

#घोषणा FD(reg_field) (REGS)->shअगरt.reg_field, (REGS)->mask.reg_field

#घोषणा FN(reg_name, field) FD(reg_name##__##field)

/* Register पढ़ोs and ग_लिखोs. */

#घोषणा REG_READ(reg) ((CTX)->funcs.reg_पढ़ो((CTX)->user_ctx, REG(reg)))

#घोषणा REG_WRITE(reg, val) \
	((CTX)->funcs.reg_ग_लिखो((CTX)->user_ctx, REG(reg), (val)))

/* Register field setting. */

#घोषणा REG_SET_N(reg_name, n, initial_val, ...) \
	dmub_reg_set(CTX, REG(reg_name), initial_val, n, __VA_ARGS__)

#घोषणा REG_SET(reg_name, initial_val, field, val) \
		REG_SET_N(reg_name, 1, initial_val, \
				FN(reg_name, field), val)

#घोषणा REG_SET_2(reg, init_value, f1, v1, f2, v2) \
		REG_SET_N(reg, 2, init_value, \
				FN(reg, f1), v1, \
				FN(reg, f2), v2)

#घोषणा REG_SET_3(reg, init_value, f1, v1, f2, v2, f3, v3) \
		REG_SET_N(reg, 3, init_value, \
				FN(reg, f1), v1, \
				FN(reg, f2), v2, \
				FN(reg, f3), v3)

#घोषणा REG_SET_4(reg, init_value, f1, v1, f2, v2, f3, v3, f4, v4) \
		REG_SET_N(reg, 4, init_value, \
				FN(reg, f1), v1, \
				FN(reg, f2), v2, \
				FN(reg, f3), v3, \
				FN(reg, f4), v4)

/* Register field updating. */

#घोषणा REG_UPDATE_N(reg_name, n, ...)\
		dmub_reg_update(CTX, REG(reg_name), n, __VA_ARGS__)

#घोषणा REG_UPDATE(reg_name, field, val)	\
		REG_UPDATE_N(reg_name, 1, \
				FN(reg_name, field), val)

#घोषणा REG_UPDATE_2(reg, f1, v1, f2, v2)	\
		REG_UPDATE_N(reg, 2,\
				FN(reg, f1), v1,\
				FN(reg, f2), v2)

#घोषणा REG_UPDATE_3(reg, f1, v1, f2, v2, f3, v3) \
		REG_UPDATE_N(reg, 3, \
				FN(reg, f1), v1, \
				FN(reg, f2), v2, \
				FN(reg, f3), v3)

#घोषणा REG_UPDATE_4(reg, f1, v1, f2, v2, f3, v3, f4, v4) \
		REG_UPDATE_N(reg, 4, \
				FN(reg, f1), v1, \
				FN(reg, f2), v2, \
				FN(reg, f3), v3, \
				FN(reg, f4), v4)

/* Register field getting. */

#घोषणा REG_GET(reg_name, field, val) \
	dmub_reg_get(CTX, REG(reg_name), FN(reg_name, field), val)

व्योम dmub_reg_set(काष्ठा dmub_srv *srv, uपूर्णांक32_t addr, uपूर्णांक32_t reg_val, पूर्णांक n,
		  uपूर्णांक8_t shअगरt1, uपूर्णांक32_t mask1, uपूर्णांक32_t field_value1, ...);

व्योम dmub_reg_update(काष्ठा dmub_srv *srv, uपूर्णांक32_t addr, पूर्णांक n, uपूर्णांक8_t shअगरt1,
		     uपूर्णांक32_t mask1, uपूर्णांक32_t field_value1, ...);

व्योम dmub_reg_get(काष्ठा dmub_srv *srv, uपूर्णांक32_t addr, uपूर्णांक8_t shअगरt,
		  uपूर्णांक32_t mask, uपूर्णांक32_t *field_value);

#पूर्ण_अगर /* _DMUB_REG_H_ */
