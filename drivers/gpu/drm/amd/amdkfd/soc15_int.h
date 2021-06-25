<शैली गुरु>
/*
 * Copyright 2016-2018 Advanced Micro Devices, Inc.
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

#अगर_अघोषित HSA_SOC15_INT_H_INCLUDED
#घोषणा HSA_SOC15_INT_H_INCLUDED

#समावेश "soc15_ih_clientid.h"

#घोषणा SOC15_INTSRC_CP_END_OF_PIPE	181
#घोषणा SOC15_INTSRC_CP_BAD_OPCODE	183
#घोषणा SOC15_INTSRC_SQ_INTERRUPT_MSG	239
#घोषणा SOC15_INTSRC_VMC_FAULT		0
#घोषणा SOC15_INTSRC_SDMA_TRAP		224


#घोषणा SOC15_CLIENT_ID_FROM_IH_ENTRY(entry) (le32_to_cpu(entry[0]) & 0xff)
#घोषणा SOC15_SOURCE_ID_FROM_IH_ENTRY(entry) (le32_to_cpu(entry[0]) >> 8 & 0xff)
#घोषणा SOC15_RING_ID_FROM_IH_ENTRY(entry) (le32_to_cpu(entry[0]) >> 16 & 0xff)
#घोषणा SOC15_VMID_FROM_IH_ENTRY(entry) (le32_to_cpu(entry[0]) >> 24 & 0xf)
#घोषणा SOC15_VMID_TYPE_FROM_IH_ENTRY(entry) (le32_to_cpu(entry[0]) >> 31 & 0x1)
#घोषणा SOC15_PASID_FROM_IH_ENTRY(entry) (le32_to_cpu(entry[3]) & 0xffff)
#घोषणा SOC15_CONTEXT_ID0_FROM_IH_ENTRY(entry) (le32_to_cpu(entry[4]))
#घोषणा SOC15_CONTEXT_ID1_FROM_IH_ENTRY(entry) (le32_to_cpu(entry[5]))
#घोषणा SOC15_CONTEXT_ID2_FROM_IH_ENTRY(entry) (le32_to_cpu(entry[6]))
#घोषणा SOC15_CONTEXT_ID3_FROM_IH_ENTRY(entry) (le32_to_cpu(entry[7]))

#पूर्ण_अगर

