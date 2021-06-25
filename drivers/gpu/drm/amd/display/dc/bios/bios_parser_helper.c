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

#समावेश "dm_services.h"

#समावेश "atom.h"

#समावेश "include/bios_parser_types.h"
#समावेश "bios_parser_helper.h"
#समावेश "command_table_helper.h"
#समावेश "command_table.h"
#समावेश "bios_parser_types_internal.h"

uपूर्णांक8_t *bios_get_image(काष्ठा dc_bios *bp,
	uपूर्णांक32_t offset,
	uपूर्णांक32_t size)
अणु
	अगर (bp->bios && offset + size < bp->bios_size)
		वापस bp->bios + offset;
	अन्यथा
		वापस शून्य;
पूर्ण

#समावेश "reg_helper.h"

#घोषणा CTX \
	bios->ctx
#घोषणा REG(reg)\
	(bios->regs->reg)

#अघोषित FN
#घोषणा FN(reg_name, field_name) \
		ATOM_ ## field_name ## _SHIFT, ATOM_ ## field_name

bool bios_is_accelerated_mode(
	काष्ठा dc_bios *bios)
अणु
	uपूर्णांक32_t acc_mode;
	REG_GET(BIOS_SCRATCH_6, S6_ACC_MODE, &acc_mode);
	वापस (acc_mode == 1);
पूर्ण


व्योम bios_set_scratch_acc_mode_change(
	काष्ठा dc_bios *bios,
	uपूर्णांक32_t state)
अणु
	REG_UPDATE(BIOS_SCRATCH_6, S6_ACC_MODE, state);
पूर्ण


व्योम bios_set_scratch_critical_state(
	काष्ठा dc_bios *bios,
	bool state)
अणु
	uपूर्णांक32_t critial_state = state ? 1 : 0;
	REG_UPDATE(BIOS_SCRATCH_6, S6_CRITICAL_STATE, critial_state);
पूर्ण

uपूर्णांक32_t bios_get_vga_enabled_displays(
	काष्ठा dc_bios *bios)
अणु
	uपूर्णांक32_t active_disp = 1;

	active_disp = REG_READ(BIOS_SCRATCH_3) & 0XFFFF;
	वापस active_disp;
पूर्ण

