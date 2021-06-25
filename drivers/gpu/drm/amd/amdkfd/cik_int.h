<शैली गुरु>
/*
 * Copyright 2014 Advanced Micro Devices, Inc.
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
 */

#अगर_अघोषित CIK_INT_H_INCLUDED
#घोषणा CIK_INT_H_INCLUDED

#समावेश <linux/types.h>

काष्ठा cik_ih_ring_entry अणु
	uपूर्णांक32_t source_id;
	uपूर्णांक32_t data;
	uपूर्णांक32_t ring_id;
	uपूर्णांक32_t reserved;
पूर्ण;

#घोषणा CIK_INTSRC_CP_END_OF_PIPE	0xB5
#घोषणा CIK_INTSRC_CP_BAD_OPCODE	0xB7
#घोषणा CIK_INTSRC_SDMA_TRAP		0xE0
#घोषणा CIK_INTSRC_SQ_INTERRUPT_MSG	0xEF
#घोषणा CIK_INTSRC_GFX_PAGE_INV_FAULT	0x92
#घोषणा CIK_INTSRC_GFX_MEM_PROT_FAULT	0x93

#पूर्ण_अगर

