<शैली गुरु>
/*
 * Copyright 2016 Advanced Micro Devices, Inc.
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
 */

#अगर_अघोषित DRIVERS_GPU_DRM_AMD_DC_DEV_DC_INC_REG_HELPER_H_
#घोषणा DRIVERS_GPU_DRM_AMD_DC_DEV_DC_INC_REG_HELPER_H_

#समावेश "dm_services.h"

/* macro क्रम रेजिस्टर पढ़ो/ग_लिखो
 * user of macro need to define
 *
 * CTX ==> macro to ptr to dc_context
 *    eg. aud110->base.ctx
 *
 * REG ==> macro to location of रेजिस्टर offset
 *    eg. aud110->regs->reg
 */
#घोषणा REG_READ(reg_name) \
		dm_पढ़ो_reg(CTX, REG(reg_name))

#घोषणा REG_WRITE(reg_name, value) \
		dm_ग_लिखो_reg(CTX, REG(reg_name), value)

#अगर_घोषित REG_SET
#अघोषित REG_SET
#पूर्ण_अगर

#अगर_घोषित REG_GET
#अघोषित REG_GET
#पूर्ण_अगर

/* macro to set रेजिस्टर fields. */
#घोषणा REG_SET_N(reg_name, n, initial_val, ...)	\
		generic_reg_set_ex(CTX, \
				REG(reg_name), \
				initial_val, \
				n, __VA_ARGS__)

#घोषणा FN(reg_name, field) \
	FD(reg_name##__##field)

#घोषणा REG_SET(reg_name, initial_val, field, val)	\
		REG_SET_N(reg_name, 1, initial_val, \
				FN(reg_name, field), val)

#घोषणा REG_SET_2(reg, init_value, f1, v1, f2, v2)	\
		REG_SET_N(reg, 2, init_value, \
				FN(reg, f1), v1,\
				FN(reg, f2), v2)

#घोषणा REG_SET_3(reg, init_value, f1, v1, f2, v2, f3, v3)	\
		REG_SET_N(reg, 3, init_value, \
				FN(reg, f1), v1,\
				FN(reg, f2), v2,\
				FN(reg, f3), v3)

#घोषणा REG_SET_4(reg, init_value, f1, v1, f2, v2, f3, v3, f4, v4)	\
		REG_SET_N(reg, 4, init_value, \
				FN(reg, f1), v1,\
				FN(reg, f2), v2,\
				FN(reg, f3), v3,\
				FN(reg, f4), v4)

#घोषणा REG_SET_5(reg, init_value, f1, v1, f2, v2, f3, v3, f4, v4,	\
		f5, v5)	\
		REG_SET_N(reg, 5, init_value, \
				FN(reg, f1), v1,\
				FN(reg, f2), v2,\
				FN(reg, f3), v3,\
				FN(reg, f4), v4,\
				FN(reg, f5), v5)

#घोषणा REG_SET_6(reg, init_value, f1, v1, f2, v2, f3, v3, f4, v4,	\
		f5, v5, f6, v6)	\
		REG_SET_N(reg, 6, init_value, \
				FN(reg, f1), v1,\
				FN(reg, f2), v2,\
				FN(reg, f3), v3,\
				FN(reg, f4), v4,\
				FN(reg, f5), v5,\
				FN(reg, f6), v6)

#घोषणा REG_SET_7(reg, init_value, f1, v1, f2, v2, f3, v3, f4, v4,	\
		f5, v5, f6, v6, f7, v7)	\
		REG_SET_N(reg, 7, init_value, \
				FN(reg, f1), v1,\
				FN(reg, f2), v2,\
				FN(reg, f3), v3,\
				FN(reg, f4), v4,\
				FN(reg, f5), v5,\
				FN(reg, f6), v6,\
				FN(reg, f7), v7)

#घोषणा REG_SET_8(reg, init_value, f1, v1, f2, v2, f3, v3, f4, v4,	\
		f5, v5, f6, v6, f7, v7, f8, v8)	\
		REG_SET_N(reg, 8, init_value, \
				FN(reg, f1), v1,\
				FN(reg, f2), v2,\
				FN(reg, f3), v3,\
				FN(reg, f4), v4,\
				FN(reg, f5), v5,\
				FN(reg, f6), v6,\
				FN(reg, f7), v7,\
				FN(reg, f8), v8)

#घोषणा REG_SET_9(reg, init_value, f1, v1, f2, v2, f3, v3, f4, v4, f5, \
		v5, f6, v6, f7, v7, f8, v8, f9, v9)	\
		REG_SET_N(reg, 9, init_value, \
				FN(reg, f1), v1,\
				FN(reg, f2), v2, \
				FN(reg, f3), v3, \
				FN(reg, f4), v4, \
				FN(reg, f5), v5, \
				FN(reg, f6), v6, \
				FN(reg, f7), v7, \
				FN(reg, f8), v8, \
				FN(reg, f9), v9)

#घोषणा REG_SET_10(reg, init_value, f1, v1, f2, v2, f3, v3, f4, v4, f5, \
		v5, f6, v6, f7, v7, f8, v8, f9, v9, f10, v10)	\
		REG_SET_N(reg, 10, init_value, \
				FN(reg, f1), v1,\
				FN(reg, f2), v2, \
				FN(reg, f3), v3, \
				FN(reg, f4), v4, \
				FN(reg, f5), v5, \
				FN(reg, f6), v6, \
				FN(reg, f7), v7, \
				FN(reg, f8), v8, \
				FN(reg, f9), v9, \
				FN(reg, f10), v10)

/* macro to get रेजिस्टर fields
 * पढ़ो given रेजिस्टर and fill in field value in output parameter */
#घोषणा REG_GET(reg_name, field, val)	\
		generic_reg_get(CTX, REG(reg_name), \
				FN(reg_name, field), val)

#घोषणा REG_GET_2(reg_name, f1, v1, f2, v2)	\
		generic_reg_get2(CTX, REG(reg_name), \
				FN(reg_name, f1), v1, \
				FN(reg_name, f2), v2)

#घोषणा REG_GET_3(reg_name, f1, v1, f2, v2, f3, v3)	\
		generic_reg_get3(CTX, REG(reg_name), \
				FN(reg_name, f1), v1, \
				FN(reg_name, f2), v2, \
				FN(reg_name, f3), v3)

#घोषणा REG_GET_4(reg_name, f1, v1, f2, v2, f3, v3, f4, v4)	\
		generic_reg_get4(CTX, REG(reg_name), \
				FN(reg_name, f1), v1, \
				FN(reg_name, f2), v2, \
				FN(reg_name, f3), v3, \
				FN(reg_name, f4), v4)

#घोषणा REG_GET_5(reg_name, f1, v1, f2, v2, f3, v3, f4, v4, f5, v5)	\
		generic_reg_get5(CTX, REG(reg_name), \
				FN(reg_name, f1), v1, \
				FN(reg_name, f2), v2, \
				FN(reg_name, f3), v3, \
				FN(reg_name, f4), v4, \
				FN(reg_name, f5), v5)

#घोषणा REG_GET_6(reg_name, f1, v1, f2, v2, f3, v3, f4, v4, f5, v5, f6, v6)	\
		generic_reg_get6(CTX, REG(reg_name), \
				FN(reg_name, f1), v1, \
				FN(reg_name, f2), v2, \
				FN(reg_name, f3), v3, \
				FN(reg_name, f4), v4, \
				FN(reg_name, f5), v5, \
				FN(reg_name, f6), v6)

#घोषणा REG_GET_7(reg_name, f1, v1, f2, v2, f3, v3, f4, v4, f5, v5, f6, v6, f7, v7)	\
		generic_reg_get7(CTX, REG(reg_name), \
				FN(reg_name, f1), v1, \
				FN(reg_name, f2), v2, \
				FN(reg_name, f3), v3, \
				FN(reg_name, f4), v4, \
				FN(reg_name, f5), v5, \
				FN(reg_name, f6), v6, \
				FN(reg_name, f7), v7)

#घोषणा REG_GET_8(reg_name, f1, v1, f2, v2, f3, v3, f4, v4, f5, v5, f6, v6, f7, v7, f8, v8)	\
		generic_reg_get8(CTX, REG(reg_name), \
				FN(reg_name, f1), v1, \
				FN(reg_name, f2), v2, \
				FN(reg_name, f3), v3, \
				FN(reg_name, f4), v4, \
				FN(reg_name, f5), v5, \
				FN(reg_name, f6), v6, \
				FN(reg_name, f7), v7, \
				FN(reg_name, f8), v8)

/* macro to poll and रुको क्रम a रेजिस्टर field to पढ़ो back given value */

#घोषणा REG_WAIT(reg_name, field, val, delay_between_poll_us, max_try)	\
		generic_reg_रुको(CTX, \
				REG(reg_name), FN(reg_name, field), val,\
				delay_between_poll_us, max_try, __func__, __LINE__)

/* macro to update (पढ़ो, modअगरy, ग_लिखो) रेजिस्टर fields
 */
#घोषणा REG_UPDATE_N(reg_name, n, ...)	\
		generic_reg_update_ex(CTX, \
				REG(reg_name), \
				n, __VA_ARGS__)

#घोषणा REG_UPDATE(reg_name, field, val)	\
		REG_UPDATE_N(reg_name, 1, \
				FN(reg_name, field), val)

#घोषणा REG_UPDATE_2(reg, f1, v1, f2, v2)	\
		REG_UPDATE_N(reg, 2,\
				FN(reg, f1), v1,\
				FN(reg, f2), v2)

#घोषणा REG_UPDATE_3(reg, f1, v1, f2, v2, f3, v3)	\
		REG_UPDATE_N(reg, 3, \
				FN(reg, f1), v1,\
				FN(reg, f2), v2, \
				FN(reg, f3), v3)

#घोषणा REG_UPDATE_4(reg, f1, v1, f2, v2, f3, v3, f4, v4)	\
		REG_UPDATE_N(reg, 4, \
				FN(reg, f1), v1,\
				FN(reg, f2), v2, \
				FN(reg, f3), v3, \
				FN(reg, f4), v4)

#घोषणा REG_UPDATE_5(reg, f1, v1, f2, v2, f3, v3, f4, v4, f5, v5)	\
		REG_UPDATE_N(reg, 5, \
				FN(reg, f1), v1,\
				FN(reg, f2), v2, \
				FN(reg, f3), v3, \
				FN(reg, f4), v4, \
				FN(reg, f5), v5)

#घोषणा REG_UPDATE_6(reg, f1, v1, f2, v2, f3, v3, f4, v4, f5, v5, f6, v6)	\
		REG_UPDATE_N(reg, 6, \
				FN(reg, f1), v1,\
				FN(reg, f2), v2, \
				FN(reg, f3), v3, \
				FN(reg, f4), v4, \
				FN(reg, f5), v5, \
				FN(reg, f6), v6)

#घोषणा REG_UPDATE_7(reg, f1, v1, f2, v2, f3, v3, f4, v4, f5, v5, f6, v6, f7, v7)	\
		REG_UPDATE_N(reg, 7, \
				FN(reg, f1), v1,\
				FN(reg, f2), v2, \
				FN(reg, f3), v3, \
				FN(reg, f4), v4, \
				FN(reg, f5), v5, \
				FN(reg, f6), v6, \
				FN(reg, f7), v7)

#घोषणा REG_UPDATE_8(reg, f1, v1, f2, v2, f3, v3, f4, v4, f5, v5, f6, v6, f7, v7, f8, v8)	\
		REG_UPDATE_N(reg, 8, \
				FN(reg, f1), v1,\
				FN(reg, f2), v2, \
				FN(reg, f3), v3, \
				FN(reg, f4), v4, \
				FN(reg, f5), v5, \
				FN(reg, f6), v6, \
				FN(reg, f7), v7, \
				FN(reg, f8), v8)

#घोषणा REG_UPDATE_9(reg, f1, v1, f2, v2, f3, v3, f4, v4, f5, v5, f6, v6, f7, v7, f8, v8, f9, v9)	\
		REG_UPDATE_N(reg, 9, \
				FN(reg, f1), v1,\
				FN(reg, f2), v2, \
				FN(reg, f3), v3, \
				FN(reg, f4), v4, \
				FN(reg, f5), v5, \
				FN(reg, f6), v6, \
				FN(reg, f7), v7, \
				FN(reg, f8), v8, \
				FN(reg, f9), v9)

#घोषणा REG_UPDATE_10(reg, f1, v1, f2, v2, f3, v3, f4, v4, f5, v5, f6, v6, f7, v7, f8, v8, f9, v9, f10, v10)\
		REG_UPDATE_N(reg, 10, \
				FN(reg, f1), v1,\
				FN(reg, f2), v2, \
				FN(reg, f3), v3, \
				FN(reg, f4), v4, \
				FN(reg, f5), v5, \
				FN(reg, f6), v6, \
				FN(reg, f7), v7, \
				FN(reg, f8), v8, \
				FN(reg, f9), v9, \
				FN(reg, f10), v10)

#घोषणा REG_UPDATE_14(reg, f1, v1, f2, v2, f3, v3, f4, v4, f5, v5, f6, v6, f7, v7, f8, v8, f9, v9, f10,\
		v10, f11, v11, f12, v12, f13, v13, f14, v14)\
		REG_UPDATE_N(reg, 14, \
				FN(reg, f1), v1,\
				FN(reg, f2), v2, \
				FN(reg, f3), v3, \
				FN(reg, f4), v4, \
				FN(reg, f5), v5, \
				FN(reg, f6), v6, \
				FN(reg, f7), v7, \
				FN(reg, f8), v8, \
				FN(reg, f9), v9, \
				FN(reg, f10), v10, \
				FN(reg, f11), v11, \
				FN(reg, f12), v12, \
				FN(reg, f13), v13, \
				FN(reg, f14), v14)

#घोषणा REG_UPDATE_19(reg, f1, v1, f2, v2, f3, v3, f4, v4, f5, v5, f6, v6, f7, v7, f8, v8, f9, v9, f10,\
		v10, f11, v11, f12, v12, f13, v13, f14, v14, f15, v15, f16, v16, f17, v17, f18, v18, f19, v19)\
		REG_UPDATE_N(reg, 19, \
				FN(reg, f1), v1,\
				FN(reg, f2), v2, \
				FN(reg, f3), v3, \
				FN(reg, f4), v4, \
				FN(reg, f5), v5, \
				FN(reg, f6), v6, \
				FN(reg, f7), v7, \
				FN(reg, f8), v8, \
				FN(reg, f9), v9, \
				FN(reg, f10), v10, \
				FN(reg, f11), v11, \
				FN(reg, f12), v12, \
				FN(reg, f13), v13, \
				FN(reg, f14), v14, \
				FN(reg, f15), v15, \
				FN(reg, f16), v16, \
				FN(reg, f17), v17, \
				FN(reg, f18), v18, \
				FN(reg, f19), v19)

#घोषणा REG_UPDATE_20(reg, f1, v1, f2, v2, f3, v3, f4, v4, f5, v5, f6, v6, f7, v7, f8, v8, f9, v9, f10,\
		v10, f11, v11, f12, v12, f13, v13, f14, v14, f15, v15, f16, v16, f17, v17, f18, v18, f19, v19, f20, v20)\
		REG_UPDATE_N(reg, 20, \
				FN(reg, f1), v1,\
				FN(reg, f2), v2, \
				FN(reg, f3), v3, \
				FN(reg, f4), v4, \
				FN(reg, f5), v5, \
				FN(reg, f6), v6, \
				FN(reg, f7), v7, \
				FN(reg, f8), v8, \
				FN(reg, f9), v9, \
				FN(reg, f10), v10, \
				FN(reg, f11), v11, \
				FN(reg, f12), v12, \
				FN(reg, f13), v13, \
				FN(reg, f14), v14, \
				FN(reg, f15), v15, \
				FN(reg, f16), v16, \
				FN(reg, f17), v17, \
				FN(reg, f18), v18, \
				FN(reg, f19), v19, \
				FN(reg, f20), v20)
/* macro to update a रेजिस्टर field to specअगरied values in given sequences.
 * useful when toggling bits
 */
#घोषणा REG_UPDATE_SEQ_2(reg, f1, v1, f2, v2) \
अणु	uपूर्णांक32_t val = REG_UPDATE(reg, f1, v1); \
	REG_SET(reg, val, f2, v2); पूर्ण

#घोषणा REG_UPDATE_SEQ_3(reg, f1, v1, f2, v2, f3, v3) \
अणु	uपूर्णांक32_t val = REG_UPDATE(reg, f1, v1); \
	val = REG_SET(reg, val, f2, v2); \
	REG_SET(reg, val, f3, v3); पूर्ण

uपूर्णांक32_t generic_reg_get(स्थिर काष्ठा dc_context *ctx, uपूर्णांक32_t addr,
		uपूर्णांक8_t shअगरt, uपूर्णांक32_t mask, uपूर्णांक32_t *field_value);

uपूर्णांक32_t generic_reg_get2(स्थिर काष्ठा dc_context *ctx, uपूर्णांक32_t addr,
		uपूर्णांक8_t shअगरt1, uपूर्णांक32_t mask1, uपूर्णांक32_t *field_value1,
		uपूर्णांक8_t shअगरt2, uपूर्णांक32_t mask2, uपूर्णांक32_t *field_value2);

uपूर्णांक32_t generic_reg_get3(स्थिर काष्ठा dc_context *ctx, uपूर्णांक32_t addr,
		uपूर्णांक8_t shअगरt1, uपूर्णांक32_t mask1, uपूर्णांक32_t *field_value1,
		uपूर्णांक8_t shअगरt2, uपूर्णांक32_t mask2, uपूर्णांक32_t *field_value2,
		uपूर्णांक8_t shअगरt3, uपूर्णांक32_t mask3, uपूर्णांक32_t *field_value3);

uपूर्णांक32_t generic_reg_get4(स्थिर काष्ठा dc_context *ctx, uपूर्णांक32_t addr,
		uपूर्णांक8_t shअगरt1, uपूर्णांक32_t mask1, uपूर्णांक32_t *field_value1,
		uपूर्णांक8_t shअगरt2, uपूर्णांक32_t mask2, uपूर्णांक32_t *field_value2,
		uपूर्णांक8_t shअगरt3, uपूर्णांक32_t mask3, uपूर्णांक32_t *field_value3,
		uपूर्णांक8_t shअगरt4, uपूर्णांक32_t mask4, uपूर्णांक32_t *field_value4);

uपूर्णांक32_t generic_reg_get5(स्थिर काष्ठा dc_context *ctx, uपूर्णांक32_t addr,
		uपूर्णांक8_t shअगरt1, uपूर्णांक32_t mask1, uपूर्णांक32_t *field_value1,
		uपूर्णांक8_t shअगरt2, uपूर्णांक32_t mask2, uपूर्णांक32_t *field_value2,
		uपूर्णांक8_t shअगरt3, uपूर्णांक32_t mask3, uपूर्णांक32_t *field_value3,
		uपूर्णांक8_t shअगरt4, uपूर्णांक32_t mask4, uपूर्णांक32_t *field_value4,
		uपूर्णांक8_t shअगरt5, uपूर्णांक32_t mask5, uपूर्णांक32_t *field_value5);

uपूर्णांक32_t generic_reg_get6(स्थिर काष्ठा dc_context *ctx, uपूर्णांक32_t addr,
		uपूर्णांक8_t shअगरt1, uपूर्णांक32_t mask1, uपूर्णांक32_t *field_value1,
		uपूर्णांक8_t shअगरt2, uपूर्णांक32_t mask2, uपूर्णांक32_t *field_value2,
		uपूर्णांक8_t shअगरt3, uपूर्णांक32_t mask3, uपूर्णांक32_t *field_value3,
		uपूर्णांक8_t shअगरt4, uपूर्णांक32_t mask4, uपूर्णांक32_t *field_value4,
		uपूर्णांक8_t shअगरt5, uपूर्णांक32_t mask5, uपूर्णांक32_t *field_value5,
		uपूर्णांक8_t shअगरt6, uपूर्णांक32_t mask6, uपूर्णांक32_t *field_value6);

uपूर्णांक32_t generic_reg_get7(स्थिर काष्ठा dc_context *ctx, uपूर्णांक32_t addr,
		uपूर्णांक8_t shअगरt1, uपूर्णांक32_t mask1, uपूर्णांक32_t *field_value1,
		uपूर्णांक8_t shअगरt2, uपूर्णांक32_t mask2, uपूर्णांक32_t *field_value2,
		uपूर्णांक8_t shअगरt3, uपूर्णांक32_t mask3, uपूर्णांक32_t *field_value3,
		uपूर्णांक8_t shअगरt4, uपूर्णांक32_t mask4, uपूर्णांक32_t *field_value4,
		uपूर्णांक8_t shअगरt5, uपूर्णांक32_t mask5, uपूर्णांक32_t *field_value5,
		uपूर्णांक8_t shअगरt6, uपूर्णांक32_t mask6, uपूर्णांक32_t *field_value6,
		uपूर्णांक8_t shअगरt7, uपूर्णांक32_t mask7, uपूर्णांक32_t *field_value7);

uपूर्णांक32_t generic_reg_get8(स्थिर काष्ठा dc_context *ctx, uपूर्णांक32_t addr,
		uपूर्णांक8_t shअगरt1, uपूर्णांक32_t mask1, uपूर्णांक32_t *field_value1,
		uपूर्णांक8_t shअगरt2, uपूर्णांक32_t mask2, uपूर्णांक32_t *field_value2,
		uपूर्णांक8_t shअगरt3, uपूर्णांक32_t mask3, uपूर्णांक32_t *field_value3,
		uपूर्णांक8_t shअगरt4, uपूर्णांक32_t mask4, uपूर्णांक32_t *field_value4,
		uपूर्णांक8_t shअगरt5, uपूर्णांक32_t mask5, uपूर्णांक32_t *field_value5,
		uपूर्णांक8_t shअगरt6, uपूर्णांक32_t mask6, uपूर्णांक32_t *field_value6,
		uपूर्णांक8_t shअगरt7, uपूर्णांक32_t mask7, uपूर्णांक32_t *field_value7,
		uपूर्णांक8_t shअगरt8, uपूर्णांक32_t mask8, uपूर्णांक32_t *field_value8);


/* indirect रेजिस्टर access */

#घोषणा IX_REG_SET_N(index_reg_name, data_reg_name, index, n, initial_val, ...)	\
		generic_indirect_reg_update_ex(CTX, \
				REG(index_reg_name), REG(data_reg_name), IND_REG(index), \
				initial_val, \
				n, __VA_ARGS__)

#घोषणा IX_REG_SET_2(index_reg_name, data_reg_name, index, init_value, f1, v1, f2, v2)	\
		IX_REG_SET_N(index_reg_name, data_reg_name, index, 2, init_value, \
				FN(reg, f1), v1,\
				FN(reg, f2), v2)


#घोषणा IX_REG_READ(index_reg_name, data_reg_name, index) \
		generic_पढ़ो_indirect_reg(CTX, REG(index_reg_name), REG(data_reg_name), IND_REG(index))

#घोषणा IX_REG_GET_N(index_reg_name, data_reg_name, index, n, ...) \
		generic_indirect_reg_get(CTX, REG(index_reg_name), REG(data_reg_name), \
				IND_REG(index), \
				n, __VA_ARGS__)

#घोषणा IX_REG_GET(index_reg_name, data_reg_name, index, field, val) \
		IX_REG_GET_N(index_reg_name, data_reg_name, index, 1, \
				FN(data_reg_name, field), val)

#घोषणा IX_REG_UPDATE_N(index_reg_name, data_reg_name, index, n, ...)	\
		generic_indirect_reg_update_ex(CTX, \
				REG(index_reg_name), REG(data_reg_name), IND_REG(index), \
				IX_REG_READ(index_reg_name, data_reg_name, index), \
				n, __VA_ARGS__)

#घोषणा IX_REG_UPDATE_2(index_reg_name, data_reg_name, index, f1, v1, f2, v2)	\
		IX_REG_UPDATE_N(index_reg_name, data_reg_name, index, 2,\
				FN(reg, f1), v1,\
				FN(reg, f2), v2)

व्योम generic_ग_लिखो_indirect_reg(स्थिर काष्ठा dc_context *ctx,
		uपूर्णांक32_t addr_index, uपूर्णांक32_t addr_data,
		uपूर्णांक32_t index, uपूर्णांक32_t data);

uपूर्णांक32_t generic_पढ़ो_indirect_reg(स्थिर काष्ठा dc_context *ctx,
		uपूर्णांक32_t addr_index, uपूर्णांक32_t addr_data,
		uपूर्णांक32_t index);

uपूर्णांक32_t generic_indirect_reg_get(स्थिर काष्ठा dc_context *ctx,
		uपूर्णांक32_t addr_index, uपूर्णांक32_t addr_data,
		uपूर्णांक32_t index, पूर्णांक n,
		uपूर्णांक8_t shअगरt1, uपूर्णांक32_t mask1, uपूर्णांक32_t *field_value1,
		...);

uपूर्णांक32_t generic_indirect_reg_update_ex(स्थिर काष्ठा dc_context *ctx,
		uपूर्णांक32_t addr_index, uपूर्णांक32_t addr_data,
		uपूर्णांक32_t index, uपूर्णांक32_t reg_val, पूर्णांक n,
		uपूर्णांक8_t shअगरt1, uपूर्णांक32_t mask1, uपूर्णांक32_t field_value1,
		...);

/* रेजिस्टर offload macros
 *
 * instead of MMIO to रेजिस्टर directly, in some हालs we want
 * to gather रेजिस्टर sequence and execute the रेजिस्टर sequence
 * from another thपढ़ो so we optimize समय required क्रम lengthy ops
 */

/* start gathering रेजिस्टर sequence */
#घोषणा REG_SEQ_START() \
	reg_sequence_start_gather(CTX)

/* start execution of रेजिस्टर sequence gathered since REG_SEQ_START */
#घोषणा REG_SEQ_SUBMIT() \
	reg_sequence_start_execute(CTX)

/* रुको क्रम the last REG_SEQ_SUBMIT to finish */
#घोषणा REG_SEQ_WAIT_DONE() \
	reg_sequence_रुको_करोne(CTX)

#पूर्ण_अगर /* DRIVERS_GPU_DRM_AMD_DC_DEV_DC_INC_REG_HELPER_H_ */
