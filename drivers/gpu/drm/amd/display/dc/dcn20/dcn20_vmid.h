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

#अगर_अघोषित DAL_DC_DCN20_DCN20_VMID_H_
#घोषणा DAL_DC_DCN20_DCN20_VMID_H_

#समावेश "vmid.h"

#घोषणा BASE_INNER(seg) \
	DCE_BASE__INST0_SEG ## seg

#घोषणा BASE(seg) \
	BASE_INNER(seg)

#घोषणा DCN20_VMID_REG_LIST(id)\
	SRI(CNTL, DCN_VM_CONTEXT, id),\
	SRI(PAGE_TABLE_BASE_ADDR_HI32, DCN_VM_CONTEXT, id),\
	SRI(PAGE_TABLE_BASE_ADDR_LO32, DCN_VM_CONTEXT, id),\
	SRI(PAGE_TABLE_START_ADDR_HI32, DCN_VM_CONTEXT, id),\
	SRI(PAGE_TABLE_START_ADDR_LO32, DCN_VM_CONTEXT, id),\
	SRI(PAGE_TABLE_END_ADDR_HI32, DCN_VM_CONTEXT, id),\
	SRI(PAGE_TABLE_END_ADDR_LO32, DCN_VM_CONTEXT, id)

#घोषणा DCN20_VMID_MASK_SH_LIST(mask_sh)\
	SF(DCN_VM_CONTEXT0_CNTL, VM_CONTEXT0_PAGE_TABLE_DEPTH, mask_sh),\
	SF(DCN_VM_CONTEXT0_CNTL, VM_CONTEXT0_PAGE_TABLE_BLOCK_SIZE, mask_sh),\
	SF(DCN_VM_CONTEXT0_PAGE_TABLE_BASE_ADDR_HI32, VM_CONTEXT0_PAGE_सूचीECTORY_ENTRY_HI32, mask_sh),\
	SF(DCN_VM_CONTEXT0_PAGE_TABLE_BASE_ADDR_LO32, VM_CONTEXT0_PAGE_सूचीECTORY_ENTRY_LO32, mask_sh),\
	SF(DCN_VM_CONTEXT0_PAGE_TABLE_START_ADDR_HI32, VM_CONTEXT0_START_LOGICAL_PAGE_NUMBER_HI4, mask_sh),\
	SF(DCN_VM_CONTEXT0_PAGE_TABLE_START_ADDR_LO32, VM_CONTEXT0_START_LOGICAL_PAGE_NUMBER_LO32, mask_sh),\
	SF(DCN_VM_CONTEXT0_PAGE_TABLE_END_ADDR_HI32, VM_CONTEXT0_END_LOGICAL_PAGE_NUMBER_HI4, mask_sh),\
	SF(DCN_VM_CONTEXT0_PAGE_TABLE_END_ADDR_LO32, VM_CONTEXT0_END_LOGICAL_PAGE_NUMBER_LO32, mask_sh)

#घोषणा DCN20_VMID_REG_FIELD_LIST(type)\
	type VM_CONTEXT0_PAGE_TABLE_DEPTH;\
	type VM_CONTEXT0_PAGE_TABLE_BLOCK_SIZE;\
	type VM_CONTEXT0_PAGE_सूचीECTORY_ENTRY_HI32;\
	type VM_CONTEXT0_PAGE_सूचीECTORY_ENTRY_LO32;\
	type VM_CONTEXT0_START_LOGICAL_PAGE_NUMBER_HI4;\
	type VM_CONTEXT0_START_LOGICAL_PAGE_NUMBER_LO32;\
	type VM_CONTEXT0_END_LOGICAL_PAGE_NUMBER_HI4;\
	type VM_CONTEXT0_END_LOGICAL_PAGE_NUMBER_LO32

काष्ठा dcn20_vmid_shअगरt अणु
	DCN20_VMID_REG_FIELD_LIST(uपूर्णांक8_t);
पूर्ण;

काष्ठा dcn20_vmid_mask अणु
	DCN20_VMID_REG_FIELD_LIST(uपूर्णांक32_t);
पूर्ण;

काष्ठा dcn20_vmid अणु
	काष्ठा dc_context *ctx;
	स्थिर काष्ठा dcn_vmid_रेजिस्टरs *regs;
	स्थिर काष्ठा dcn20_vmid_shअगरt *shअगरts;
	स्थिर काष्ठा dcn20_vmid_mask *masks;
पूर्ण;

व्योम dcn20_vmid_setup(काष्ठा dcn20_vmid *vmid, स्थिर काष्ठा dcn_vmid_page_table_config *config);

#पूर्ण_अगर /* DAL_DC_DCN20_DCN20_VMID_H_ */
