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

#अगर_अघोषित DAL_DC_INC_HW_VMID_H_
#घोषणा DAL_DC_INC_HW_VMID_H_

#समावेश "core_types.h"
#समावेश "dchubbub.h"

काष्ठा dcn_vmid_रेजिस्टरs अणु
	uपूर्णांक32_t CNTL;
	uपूर्णांक32_t PAGE_TABLE_BASE_ADDR_HI32;
	uपूर्णांक32_t PAGE_TABLE_BASE_ADDR_LO32;
	uपूर्णांक32_t PAGE_TABLE_START_ADDR_HI32;
	uपूर्णांक32_t PAGE_TABLE_START_ADDR_LO32;
	uपूर्णांक32_t PAGE_TABLE_END_ADDR_HI32;
	uपूर्णांक32_t PAGE_TABLE_END_ADDR_LO32;
पूर्ण;

काष्ठा dcn_vmid_page_table_config अणु
	uपूर्णांक64_t	page_table_start_addr;
	uपूर्णांक64_t	page_table_end_addr;
	क्रमागत dcn_hubbub_page_table_depth	depth;
	क्रमागत dcn_hubbub_page_table_block_size	block_size;
	uपूर्णांक64_t	page_table_base_addr;
पूर्ण;

#पूर्ण_अगर /* DAL_DC_INC_HW_VMID_H_ */
