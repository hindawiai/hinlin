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
 *
 */

#अगर_अघोषित SMU_UCODE_XFER_VI_H
#घोषणा SMU_UCODE_XFER_VI_H

#घोषणा SMU_DRAMData_TOC_VERSION  1
#घोषणा MAX_IH_REGISTER_COUNT     65535
#घोषणा SMU_DIGEST_SIZE_BYTES     20
#घोषणा SMU_FB_SIZE_BYTES         1048576
#घोषणा SMU_MAX_ENTRIES           12

#घोषणा UCODE_ID_SMU              0
#घोषणा UCODE_ID_SDMA0            1
#घोषणा UCODE_ID_SDMA1            2
#घोषणा UCODE_ID_CP_CE            3
#घोषणा UCODE_ID_CP_PFP           4
#घोषणा UCODE_ID_CP_ME            5
#घोषणा UCODE_ID_CP_MEC           6
#घोषणा UCODE_ID_CP_MEC_JT1       7
#घोषणा UCODE_ID_CP_MEC_JT2       8
#घोषणा UCODE_ID_GMCON_RENG       9
#घोषणा UCODE_ID_RLC_G            10
#घोषणा UCODE_ID_IH_REG_RESTORE   11
#घोषणा UCODE_ID_VBIOS            12
#घोषणा UCODE_ID_MISC_METADATA    13
#घोषणा UCODE_ID_SMU_SK		      14
#घोषणा UCODE_ID_RLC_SCRATCH      32
#घोषणा UCODE_ID_RLC_SRM_ARAM     33
#घोषणा UCODE_ID_RLC_SRM_DRAM     34
#घोषणा UCODE_ID_MEC_STORAGE      35
#घोषणा UCODE_ID_VBIOS_PARAMETERS 36
#घोषणा UCODE_META_DATA           0xFF

#घोषणा UCODE_ID_SMU_MASK             0x00000001
#घोषणा UCODE_ID_SDMA0_MASK           0x00000002
#घोषणा UCODE_ID_SDMA1_MASK           0x00000004
#घोषणा UCODE_ID_CP_CE_MASK           0x00000008
#घोषणा UCODE_ID_CP_PFP_MASK          0x00000010
#घोषणा UCODE_ID_CP_ME_MASK           0x00000020
#घोषणा UCODE_ID_CP_MEC_MASK          0x00000040
#घोषणा UCODE_ID_CP_MEC_JT1_MASK      0x00000080
#घोषणा UCODE_ID_CP_MEC_JT2_MASK      0x00000100
#घोषणा UCODE_ID_GMCON_RENG_MASK      0x00000200
#घोषणा UCODE_ID_RLC_G_MASK           0x00000400
#घोषणा UCODE_ID_IH_REG_RESTORE_MASK  0x00000800
#घोषणा UCODE_ID_VBIOS_MASK           0x00001000

#घोषणा UCODE_FLAG_UNHALT_MASK   0x1

काष्ठा SMU_Entry अणु
#अगर_अघोषित __BIG_ENDIAN
	uपूर्णांक16_t id;
	uपूर्णांक16_t version;
	uपूर्णांक32_t image_addr_high;
	uपूर्णांक32_t image_addr_low;
	uपूर्णांक32_t meta_data_addr_high;
	uपूर्णांक32_t meta_data_addr_low;
	uपूर्णांक32_t data_size_byte;
	uपूर्णांक16_t flags;
	uपूर्णांक16_t num_रेजिस्टर_entries;
#अन्यथा
	uपूर्णांक16_t version;
	uपूर्णांक16_t id;
	uपूर्णांक32_t image_addr_high;
	uपूर्णांक32_t image_addr_low;
	uपूर्णांक32_t meta_data_addr_high;
	uपूर्णांक32_t meta_data_addr_low;
	uपूर्णांक32_t data_size_byte;
	uपूर्णांक16_t num_रेजिस्टर_entries;
	uपूर्णांक16_t flags;
#पूर्ण_अगर
पूर्ण;

काष्ठा SMU_DRAMData_TOC अणु
	uपूर्णांक32_t काष्ठाure_version;
	uपूर्णांक32_t num_entries;
	काष्ठा SMU_Entry entry[SMU_MAX_ENTRIES];
पूर्ण;

#पूर्ण_अगर
