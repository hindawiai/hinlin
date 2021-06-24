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

#समावेश "../dmub_srv.h"
#समावेश "dmub_reg.h"
#समावेश "dmub_dcn21.h"

#समावेश "dcn/dcn_2_1_0_offset.h"
#समावेश "dcn/dcn_2_1_0_sh_mask.h"
#समावेश "renoir_ip_offset.h"

#घोषणा BASE_INNER(seg) DMU_BASE__INST0_SEG##seg
#घोषणा CTX dmub
#घोषणा REGS dmub->regs

/* Registers. */

स्थिर काष्ठा dmub_srv_common_regs dmub_srv_dcn21_regs = अणु
#घोषणा DMUB_SR(reg) REG_OFFSET(reg),
	अणु DMUB_COMMON_REGS() पूर्ण,
#अघोषित DMUB_SR

#घोषणा DMUB_SF(reg, field) FD_MASK(reg, field),
	अणु DMUB_COMMON_FIELDS() पूर्ण,
#अघोषित DMUB_SF

#घोषणा DMUB_SF(reg, field) FD_SHIFT(reg, field),
	अणु DMUB_COMMON_FIELDS() पूर्ण,
#अघोषित DMUB_SF
पूर्ण;

/* Shared functions. */

bool dmub_dcn21_is_phy_init(काष्ठा dmub_srv *dmub)
अणु
	वापस REG_READ(DMCUB_SCRATCH10) == 0;
पूर्ण
