<शैली गुरु>
/*
 * Copyright 2018 Advanced Micro Devices, Inc.
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

#समावेश <linux/delay.h>

#समावेश "dcn20_vmid.h"
#समावेश "reg_helper.h"

#घोषणा REG(reg)\
	vmid->regs->reg

#घोषणा CTX \
	vmid->ctx

#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	vmid->shअगरts->field_name, vmid->masks->field_name

अटल व्योम dcn20_रुको_क्रम_vmid_पढ़ोy(काष्ठा dcn20_vmid *vmid)
अणु
	/* According the hardware spec, we need to poll क्रम the lowest
	 * bit of PAGE_TABLE_BASE_ADDR_LO32 = 1 any समय a GPUVM
	 * context is updated. We can't use REG_WAIT here since we
	 * करोn't have a seperate field to रुको on.
	 *
	 * TODO: Confirm समयout / poll पूर्णांकerval with hardware team
	 */

	पूर्णांक max_बार = 10000;
	पूर्णांक delay_us  = 5;
	पूर्णांक i;

	क्रम (i = 0; i < max_बार; ++i) अणु
		uपूर्णांक32_t entry_lo32;

		REG_GET(PAGE_TABLE_BASE_ADDR_LO32,
			VM_CONTEXT0_PAGE_सूचीECTORY_ENTRY_LO32,
			&entry_lo32);

		अगर (entry_lo32 & 0x1)
			वापस;

		udelay(delay_us);
	पूर्ण

	/* VM setup समयd out */
	DC_LOG_WARNING("Timeout while waiting for GPUVM context update\n");
	ASSERT(0);
पूर्ण

व्योम dcn20_vmid_setup(काष्ठा dcn20_vmid *vmid, स्थिर काष्ठा dcn_vmid_page_table_config *config)
अणु
	REG_SET(PAGE_TABLE_START_ADDR_HI32, 0,
			VM_CONTEXT0_START_LOGICAL_PAGE_NUMBER_HI4, (config->page_table_start_addr >> 32) & 0xF);
	REG_SET(PAGE_TABLE_START_ADDR_LO32, 0,
			VM_CONTEXT0_START_LOGICAL_PAGE_NUMBER_LO32, config->page_table_start_addr & 0xFFFFFFFF);

	REG_SET(PAGE_TABLE_END_ADDR_HI32, 0,
			VM_CONTEXT0_END_LOGICAL_PAGE_NUMBER_HI4, (config->page_table_end_addr >> 32) & 0xF);
	REG_SET(PAGE_TABLE_END_ADDR_LO32, 0,
			VM_CONTEXT0_END_LOGICAL_PAGE_NUMBER_LO32, config->page_table_end_addr & 0xFFFFFFFF);

	REG_SET_2(CNTL, 0,
			VM_CONTEXT0_PAGE_TABLE_DEPTH, config->depth,
			VM_CONTEXT0_PAGE_TABLE_BLOCK_SIZE, config->block_size);

	REG_SET(PAGE_TABLE_BASE_ADDR_HI32, 0,
			VM_CONTEXT0_PAGE_सूचीECTORY_ENTRY_HI32, (config->page_table_base_addr >> 32) & 0xFFFFFFFF);
	/* Note: per hardware spec PAGE_TABLE_BASE_ADDR_LO32 must be programmed last in sequence */
	REG_SET(PAGE_TABLE_BASE_ADDR_LO32, 0,
			VM_CONTEXT0_PAGE_सूचीECTORY_ENTRY_LO32, config->page_table_base_addr & 0xFFFFFFFF);

	dcn20_रुको_क्रम_vmid_पढ़ोy(vmid);
पूर्ण
