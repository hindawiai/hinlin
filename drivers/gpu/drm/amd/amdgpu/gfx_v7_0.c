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

#समावेश <linux/firmware.h>
#समावेश <linux/module.h>

#समावेश "amdgpu.h"
#समावेश "amdgpu_ih.h"
#समावेश "amdgpu_gfx.h"
#समावेश "cikd.h"
#समावेश "cik.h"
#समावेश "cik_structs.h"
#समावेश "atom.h"
#समावेश "amdgpu_ucode.h"
#समावेश "clearstate_ci.h"

#समावेश "dce/dce_8_0_d.h"
#समावेश "dce/dce_8_0_sh_mask.h"

#समावेश "bif/bif_4_1_d.h"
#समावेश "bif/bif_4_1_sh_mask.h"

#समावेश "gca/gfx_7_0_d.h"
#समावेश "gca/gfx_7_2_enum.h"
#समावेश "gca/gfx_7_2_sh_mask.h"

#समावेश "gmc/gmc_7_0_d.h"
#समावेश "gmc/gmc_7_0_sh_mask.h"

#समावेश "oss/oss_2_0_d.h"
#समावेश "oss/oss_2_0_sh_mask.h"

#घोषणा NUM_SIMD_PER_CU 0x4 /* missing from the gfx_7 IP headers */

#घोषणा GFX7_NUM_GFX_RINGS     1
#घोषणा GFX7_MEC_HPD_SIZE      2048

अटल व्योम gfx_v7_0_set_ring_funcs(काष्ठा amdgpu_device *adev);
अटल व्योम gfx_v7_0_set_irq_funcs(काष्ठा amdgpu_device *adev);
अटल व्योम gfx_v7_0_set_gds_init(काष्ठा amdgpu_device *adev);

MODULE_FIRMWARE("amdgpu/bonaire_pfp.bin");
MODULE_FIRMWARE("amdgpu/bonaire_me.bin");
MODULE_FIRMWARE("amdgpu/bonaire_ce.bin");
MODULE_FIRMWARE("amdgpu/bonaire_rlc.bin");
MODULE_FIRMWARE("amdgpu/bonaire_mec.bin");

MODULE_FIRMWARE("amdgpu/hawaii_pfp.bin");
MODULE_FIRMWARE("amdgpu/hawaii_me.bin");
MODULE_FIRMWARE("amdgpu/hawaii_ce.bin");
MODULE_FIRMWARE("amdgpu/hawaii_rlc.bin");
MODULE_FIRMWARE("amdgpu/hawaii_mec.bin");

MODULE_FIRMWARE("amdgpu/kaveri_pfp.bin");
MODULE_FIRMWARE("amdgpu/kaveri_me.bin");
MODULE_FIRMWARE("amdgpu/kaveri_ce.bin");
MODULE_FIRMWARE("amdgpu/kaveri_rlc.bin");
MODULE_FIRMWARE("amdgpu/kaveri_mec.bin");
MODULE_FIRMWARE("amdgpu/kaveri_mec2.bin");

MODULE_FIRMWARE("amdgpu/kabini_pfp.bin");
MODULE_FIRMWARE("amdgpu/kabini_me.bin");
MODULE_FIRMWARE("amdgpu/kabini_ce.bin");
MODULE_FIRMWARE("amdgpu/kabini_rlc.bin");
MODULE_FIRMWARE("amdgpu/kabini_mec.bin");

MODULE_FIRMWARE("amdgpu/mullins_pfp.bin");
MODULE_FIRMWARE("amdgpu/mullins_me.bin");
MODULE_FIRMWARE("amdgpu/mullins_ce.bin");
MODULE_FIRMWARE("amdgpu/mullins_rlc.bin");
MODULE_FIRMWARE("amdgpu/mullins_mec.bin");

अटल स्थिर काष्ठा amdgpu_gds_reg_offset amdgpu_gds_reg_offset[] =
अणु
	अणुmmGDS_VMID0_BASE, mmGDS_VMID0_SIZE, mmGDS_GWS_VMID0, mmGDS_OA_VMID0पूर्ण,
	अणुmmGDS_VMID1_BASE, mmGDS_VMID1_SIZE, mmGDS_GWS_VMID1, mmGDS_OA_VMID1पूर्ण,
	अणुmmGDS_VMID2_BASE, mmGDS_VMID2_SIZE, mmGDS_GWS_VMID2, mmGDS_OA_VMID2पूर्ण,
	अणुmmGDS_VMID3_BASE, mmGDS_VMID3_SIZE, mmGDS_GWS_VMID3, mmGDS_OA_VMID3पूर्ण,
	अणुmmGDS_VMID4_BASE, mmGDS_VMID4_SIZE, mmGDS_GWS_VMID4, mmGDS_OA_VMID4पूर्ण,
	अणुmmGDS_VMID5_BASE, mmGDS_VMID5_SIZE, mmGDS_GWS_VMID5, mmGDS_OA_VMID5पूर्ण,
	अणुmmGDS_VMID6_BASE, mmGDS_VMID6_SIZE, mmGDS_GWS_VMID6, mmGDS_OA_VMID6पूर्ण,
	अणुmmGDS_VMID7_BASE, mmGDS_VMID7_SIZE, mmGDS_GWS_VMID7, mmGDS_OA_VMID7पूर्ण,
	अणुmmGDS_VMID8_BASE, mmGDS_VMID8_SIZE, mmGDS_GWS_VMID8, mmGDS_OA_VMID8पूर्ण,
	अणुmmGDS_VMID9_BASE, mmGDS_VMID9_SIZE, mmGDS_GWS_VMID9, mmGDS_OA_VMID9पूर्ण,
	अणुmmGDS_VMID10_BASE, mmGDS_VMID10_SIZE, mmGDS_GWS_VMID10, mmGDS_OA_VMID10पूर्ण,
	अणुmmGDS_VMID11_BASE, mmGDS_VMID11_SIZE, mmGDS_GWS_VMID11, mmGDS_OA_VMID11पूर्ण,
	अणुmmGDS_VMID12_BASE, mmGDS_VMID12_SIZE, mmGDS_GWS_VMID12, mmGDS_OA_VMID12पूर्ण,
	अणुmmGDS_VMID13_BASE, mmGDS_VMID13_SIZE, mmGDS_GWS_VMID13, mmGDS_OA_VMID13पूर्ण,
	अणुmmGDS_VMID14_BASE, mmGDS_VMID14_SIZE, mmGDS_GWS_VMID14, mmGDS_OA_VMID14पूर्ण,
	अणुmmGDS_VMID15_BASE, mmGDS_VMID15_SIZE, mmGDS_GWS_VMID15, mmGDS_OA_VMID15पूर्ण
पूर्ण;

अटल स्थिर u32 spectre_rlc_save_restore_रेजिस्टर_list[] =
अणु
	(0x0e00 << 16) | (0xc12c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc140 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc150 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc15c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc168 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc170 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc178 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc204 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc2b4 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc2b8 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc2bc >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc2c0 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8228 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x829c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x869c >> 2),
	0x00000000,
	(0x0600 << 16) | (0x98f4 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x98f8 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x9900 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc260 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x90e8 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x3c000 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x3c00c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8c1c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x9700 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xcd20 >> 2),
	0x00000000,
	(0x4e00 << 16) | (0xcd20 >> 2),
	0x00000000,
	(0x5e00 << 16) | (0xcd20 >> 2),
	0x00000000,
	(0x6e00 << 16) | (0xcd20 >> 2),
	0x00000000,
	(0x7e00 << 16) | (0xcd20 >> 2),
	0x00000000,
	(0x8e00 << 16) | (0xcd20 >> 2),
	0x00000000,
	(0x9e00 << 16) | (0xcd20 >> 2),
	0x00000000,
	(0xae00 << 16) | (0xcd20 >> 2),
	0x00000000,
	(0xbe00 << 16) | (0xcd20 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x89bc >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8900 >> 2),
	0x00000000,
	0x3,
	(0x0e00 << 16) | (0xc130 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc134 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc1fc >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc208 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc264 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc268 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc26c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc270 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc274 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc278 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc27c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc280 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc284 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc288 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc28c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc290 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc294 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc298 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc29c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc2a0 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc2a4 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc2a8 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc2ac  >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc2b0 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x301d0 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x30238 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x30250 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x30254 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x30258 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x3025c >> 2),
	0x00000000,
	(0x4e00 << 16) | (0xc900 >> 2),
	0x00000000,
	(0x5e00 << 16) | (0xc900 >> 2),
	0x00000000,
	(0x6e00 << 16) | (0xc900 >> 2),
	0x00000000,
	(0x7e00 << 16) | (0xc900 >> 2),
	0x00000000,
	(0x8e00 << 16) | (0xc900 >> 2),
	0x00000000,
	(0x9e00 << 16) | (0xc900 >> 2),
	0x00000000,
	(0xae00 << 16) | (0xc900 >> 2),
	0x00000000,
	(0xbe00 << 16) | (0xc900 >> 2),
	0x00000000,
	(0x4e00 << 16) | (0xc904 >> 2),
	0x00000000,
	(0x5e00 << 16) | (0xc904 >> 2),
	0x00000000,
	(0x6e00 << 16) | (0xc904 >> 2),
	0x00000000,
	(0x7e00 << 16) | (0xc904 >> 2),
	0x00000000,
	(0x8e00 << 16) | (0xc904 >> 2),
	0x00000000,
	(0x9e00 << 16) | (0xc904 >> 2),
	0x00000000,
	(0xae00 << 16) | (0xc904 >> 2),
	0x00000000,
	(0xbe00 << 16) | (0xc904 >> 2),
	0x00000000,
	(0x4e00 << 16) | (0xc908 >> 2),
	0x00000000,
	(0x5e00 << 16) | (0xc908 >> 2),
	0x00000000,
	(0x6e00 << 16) | (0xc908 >> 2),
	0x00000000,
	(0x7e00 << 16) | (0xc908 >> 2),
	0x00000000,
	(0x8e00 << 16) | (0xc908 >> 2),
	0x00000000,
	(0x9e00 << 16) | (0xc908 >> 2),
	0x00000000,
	(0xae00 << 16) | (0xc908 >> 2),
	0x00000000,
	(0xbe00 << 16) | (0xc908 >> 2),
	0x00000000,
	(0x4e00 << 16) | (0xc90c >> 2),
	0x00000000,
	(0x5e00 << 16) | (0xc90c >> 2),
	0x00000000,
	(0x6e00 << 16) | (0xc90c >> 2),
	0x00000000,
	(0x7e00 << 16) | (0xc90c >> 2),
	0x00000000,
	(0x8e00 << 16) | (0xc90c >> 2),
	0x00000000,
	(0x9e00 << 16) | (0xc90c >> 2),
	0x00000000,
	(0xae00 << 16) | (0xc90c >> 2),
	0x00000000,
	(0xbe00 << 16) | (0xc90c >> 2),
	0x00000000,
	(0x4e00 << 16) | (0xc910 >> 2),
	0x00000000,
	(0x5e00 << 16) | (0xc910 >> 2),
	0x00000000,
	(0x6e00 << 16) | (0xc910 >> 2),
	0x00000000,
	(0x7e00 << 16) | (0xc910 >> 2),
	0x00000000,
	(0x8e00 << 16) | (0xc910 >> 2),
	0x00000000,
	(0x9e00 << 16) | (0xc910 >> 2),
	0x00000000,
	(0xae00 << 16) | (0xc910 >> 2),
	0x00000000,
	(0xbe00 << 16) | (0xc910 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc99c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x9834 >> 2),
	0x00000000,
	(0x0000 << 16) | (0x30f00 >> 2),
	0x00000000,
	(0x0001 << 16) | (0x30f00 >> 2),
	0x00000000,
	(0x0000 << 16) | (0x30f04 >> 2),
	0x00000000,
	(0x0001 << 16) | (0x30f04 >> 2),
	0x00000000,
	(0x0000 << 16) | (0x30f08 >> 2),
	0x00000000,
	(0x0001 << 16) | (0x30f08 >> 2),
	0x00000000,
	(0x0000 << 16) | (0x30f0c >> 2),
	0x00000000,
	(0x0001 << 16) | (0x30f0c >> 2),
	0x00000000,
	(0x0600 << 16) | (0x9b7c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8a14 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8a18 >> 2),
	0x00000000,
	(0x0600 << 16) | (0x30a00 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8bf0 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8bcc >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8b24 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x30a04 >> 2),
	0x00000000,
	(0x0600 << 16) | (0x30a10 >> 2),
	0x00000000,
	(0x0600 << 16) | (0x30a14 >> 2),
	0x00000000,
	(0x0600 << 16) | (0x30a18 >> 2),
	0x00000000,
	(0x0600 << 16) | (0x30a2c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc700 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc704 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc708 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc768 >> 2),
	0x00000000,
	(0x0400 << 16) | (0xc770 >> 2),
	0x00000000,
	(0x0400 << 16) | (0xc774 >> 2),
	0x00000000,
	(0x0400 << 16) | (0xc778 >> 2),
	0x00000000,
	(0x0400 << 16) | (0xc77c >> 2),
	0x00000000,
	(0x0400 << 16) | (0xc780 >> 2),
	0x00000000,
	(0x0400 << 16) | (0xc784 >> 2),
	0x00000000,
	(0x0400 << 16) | (0xc788 >> 2),
	0x00000000,
	(0x0400 << 16) | (0xc78c >> 2),
	0x00000000,
	(0x0400 << 16) | (0xc798 >> 2),
	0x00000000,
	(0x0400 << 16) | (0xc79c >> 2),
	0x00000000,
	(0x0400 << 16) | (0xc7a0 >> 2),
	0x00000000,
	(0x0400 << 16) | (0xc7a4 >> 2),
	0x00000000,
	(0x0400 << 16) | (0xc7a8 >> 2),
	0x00000000,
	(0x0400 << 16) | (0xc7ac >> 2),
	0x00000000,
	(0x0400 << 16) | (0xc7b0 >> 2),
	0x00000000,
	(0x0400 << 16) | (0xc7b4 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x9100 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x3c010 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x92a8 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x92ac >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x92b4 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x92b8 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x92bc >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x92c0 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x92c4 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x92c8 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x92cc >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x92d0 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8c00 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8c04 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8c20 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8c38 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8c3c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xae00 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x9604 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac08 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac0c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac10 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac14 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac58 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac68 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac6c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac70 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac74 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac78 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac7c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac80 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac84 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac88 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac8c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x970c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x9714 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x9718 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x971c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x31068 >> 2),
	0x00000000,
	(0x4e00 << 16) | (0x31068 >> 2),
	0x00000000,
	(0x5e00 << 16) | (0x31068 >> 2),
	0x00000000,
	(0x6e00 << 16) | (0x31068 >> 2),
	0x00000000,
	(0x7e00 << 16) | (0x31068 >> 2),
	0x00000000,
	(0x8e00 << 16) | (0x31068 >> 2),
	0x00000000,
	(0x9e00 << 16) | (0x31068 >> 2),
	0x00000000,
	(0xae00 << 16) | (0x31068 >> 2),
	0x00000000,
	(0xbe00 << 16) | (0x31068 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xcd10 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xcd14 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x88b0 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x88b4 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x88b8 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x88bc >> 2),
	0x00000000,
	(0x0400 << 16) | (0x89c0 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x88c4 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x88c8 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x88d0 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x88d4 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x88d8 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8980 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x30938 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x3093c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x30940 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x89a0 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x30900 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x30904 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x89b4 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x3c210 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x3c214 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x3c218 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8904 >> 2),
	0x00000000,
	0x5,
	(0x0e00 << 16) | (0x8c28 >> 2),
	(0x0e00 << 16) | (0x8c2c >> 2),
	(0x0e00 << 16) | (0x8c30 >> 2),
	(0x0e00 << 16) | (0x8c34 >> 2),
	(0x0e00 << 16) | (0x9600 >> 2),
पूर्ण;

अटल स्थिर u32 kalindi_rlc_save_restore_रेजिस्टर_list[] =
अणु
	(0x0e00 << 16) | (0xc12c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc140 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc150 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc15c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc168 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc170 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc204 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc2b4 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc2b8 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc2bc >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc2c0 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8228 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x829c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x869c >> 2),
	0x00000000,
	(0x0600 << 16) | (0x98f4 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x98f8 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x9900 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc260 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x90e8 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x3c000 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x3c00c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8c1c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x9700 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xcd20 >> 2),
	0x00000000,
	(0x4e00 << 16) | (0xcd20 >> 2),
	0x00000000,
	(0x5e00 << 16) | (0xcd20 >> 2),
	0x00000000,
	(0x6e00 << 16) | (0xcd20 >> 2),
	0x00000000,
	(0x7e00 << 16) | (0xcd20 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x89bc >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8900 >> 2),
	0x00000000,
	0x3,
	(0x0e00 << 16) | (0xc130 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc134 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc1fc >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc208 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc264 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc268 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc26c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc270 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc274 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc28c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc290 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc294 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc298 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc2a0 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc2a4 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc2a8 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc2ac >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x301d0 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x30238 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x30250 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x30254 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x30258 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x3025c >> 2),
	0x00000000,
	(0x4e00 << 16) | (0xc900 >> 2),
	0x00000000,
	(0x5e00 << 16) | (0xc900 >> 2),
	0x00000000,
	(0x6e00 << 16) | (0xc900 >> 2),
	0x00000000,
	(0x7e00 << 16) | (0xc900 >> 2),
	0x00000000,
	(0x4e00 << 16) | (0xc904 >> 2),
	0x00000000,
	(0x5e00 << 16) | (0xc904 >> 2),
	0x00000000,
	(0x6e00 << 16) | (0xc904 >> 2),
	0x00000000,
	(0x7e00 << 16) | (0xc904 >> 2),
	0x00000000,
	(0x4e00 << 16) | (0xc908 >> 2),
	0x00000000,
	(0x5e00 << 16) | (0xc908 >> 2),
	0x00000000,
	(0x6e00 << 16) | (0xc908 >> 2),
	0x00000000,
	(0x7e00 << 16) | (0xc908 >> 2),
	0x00000000,
	(0x4e00 << 16) | (0xc90c >> 2),
	0x00000000,
	(0x5e00 << 16) | (0xc90c >> 2),
	0x00000000,
	(0x6e00 << 16) | (0xc90c >> 2),
	0x00000000,
	(0x7e00 << 16) | (0xc90c >> 2),
	0x00000000,
	(0x4e00 << 16) | (0xc910 >> 2),
	0x00000000,
	(0x5e00 << 16) | (0xc910 >> 2),
	0x00000000,
	(0x6e00 << 16) | (0xc910 >> 2),
	0x00000000,
	(0x7e00 << 16) | (0xc910 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc99c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x9834 >> 2),
	0x00000000,
	(0x0000 << 16) | (0x30f00 >> 2),
	0x00000000,
	(0x0000 << 16) | (0x30f04 >> 2),
	0x00000000,
	(0x0000 << 16) | (0x30f08 >> 2),
	0x00000000,
	(0x0000 << 16) | (0x30f0c >> 2),
	0x00000000,
	(0x0600 << 16) | (0x9b7c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8a14 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8a18 >> 2),
	0x00000000,
	(0x0600 << 16) | (0x30a00 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8bf0 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8bcc >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8b24 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x30a04 >> 2),
	0x00000000,
	(0x0600 << 16) | (0x30a10 >> 2),
	0x00000000,
	(0x0600 << 16) | (0x30a14 >> 2),
	0x00000000,
	(0x0600 << 16) | (0x30a18 >> 2),
	0x00000000,
	(0x0600 << 16) | (0x30a2c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc700 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc704 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc708 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc768 >> 2),
	0x00000000,
	(0x0400 << 16) | (0xc770 >> 2),
	0x00000000,
	(0x0400 << 16) | (0xc774 >> 2),
	0x00000000,
	(0x0400 << 16) | (0xc798 >> 2),
	0x00000000,
	(0x0400 << 16) | (0xc79c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x9100 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x3c010 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8c00 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8c04 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8c20 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8c38 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8c3c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xae00 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x9604 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac08 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac0c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac10 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac14 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac58 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac68 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac6c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac70 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac74 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac78 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac7c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac80 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac84 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac88 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac8c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x970c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x9714 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x9718 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x971c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x31068 >> 2),
	0x00000000,
	(0x4e00 << 16) | (0x31068 >> 2),
	0x00000000,
	(0x5e00 << 16) | (0x31068 >> 2),
	0x00000000,
	(0x6e00 << 16) | (0x31068 >> 2),
	0x00000000,
	(0x7e00 << 16) | (0x31068 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xcd10 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xcd14 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x88b0 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x88b4 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x88b8 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x88bc >> 2),
	0x00000000,
	(0x0400 << 16) | (0x89c0 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x88c4 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x88c8 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x88d0 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x88d4 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x88d8 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8980 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x30938 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x3093c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x30940 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x89a0 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x30900 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x30904 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x89b4 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x3e1fc >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x3c210 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x3c214 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x3c218 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8904 >> 2),
	0x00000000,
	0x5,
	(0x0e00 << 16) | (0x8c28 >> 2),
	(0x0e00 << 16) | (0x8c2c >> 2),
	(0x0e00 << 16) | (0x8c30 >> 2),
	(0x0e00 << 16) | (0x8c34 >> 2),
	(0x0e00 << 16) | (0x9600 >> 2),
पूर्ण;

अटल u32 gfx_v7_0_get_csb_size(काष्ठा amdgpu_device *adev);
अटल व्योम gfx_v7_0_get_csb_buffer(काष्ठा amdgpu_device *adev, अस्थिर u32 *buffer);
अटल व्योम gfx_v7_0_init_pg(काष्ठा amdgpu_device *adev);
अटल व्योम gfx_v7_0_get_cu_info(काष्ठा amdgpu_device *adev);

/*
 * Core functions
 */
/**
 * gfx_v7_0_init_microcode - load ucode images from disk
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Use the firmware पूर्णांकerface to load the ucode images पूर्णांकo
 * the driver (not loaded पूर्णांकo hw).
 * Returns 0 on success, error on failure.
 */
अटल पूर्णांक gfx_v7_0_init_microcode(काष्ठा amdgpu_device *adev)
अणु
	स्थिर अक्षर *chip_name;
	अक्षर fw_name[30];
	पूर्णांक err;

	DRM_DEBUG("\n");

	चयन (adev->asic_type) अणु
	हाल CHIP_BONAIRE:
		chip_name = "bonaire";
		अवरोध;
	हाल CHIP_HAWAII:
		chip_name = "hawaii";
		अवरोध;
	हाल CHIP_KAVERI:
		chip_name = "kaveri";
		अवरोध;
	हाल CHIP_KABINI:
		chip_name = "kabini";
		अवरोध;
	हाल CHIP_MULLINS:
		chip_name = "mullins";
		अवरोध;
	शेष: BUG();
	पूर्ण

	snम_लिखो(fw_name, माप(fw_name), "amdgpu/%s_pfp.bin", chip_name);
	err = request_firmware(&adev->gfx.pfp_fw, fw_name, adev->dev);
	अगर (err)
		जाओ out;
	err = amdgpu_ucode_validate(adev->gfx.pfp_fw);
	अगर (err)
		जाओ out;

	snम_लिखो(fw_name, माप(fw_name), "amdgpu/%s_me.bin", chip_name);
	err = request_firmware(&adev->gfx.me_fw, fw_name, adev->dev);
	अगर (err)
		जाओ out;
	err = amdgpu_ucode_validate(adev->gfx.me_fw);
	अगर (err)
		जाओ out;

	snम_लिखो(fw_name, माप(fw_name), "amdgpu/%s_ce.bin", chip_name);
	err = request_firmware(&adev->gfx.ce_fw, fw_name, adev->dev);
	अगर (err)
		जाओ out;
	err = amdgpu_ucode_validate(adev->gfx.ce_fw);
	अगर (err)
		जाओ out;

	snम_लिखो(fw_name, माप(fw_name), "amdgpu/%s_mec.bin", chip_name);
	err = request_firmware(&adev->gfx.mec_fw, fw_name, adev->dev);
	अगर (err)
		जाओ out;
	err = amdgpu_ucode_validate(adev->gfx.mec_fw);
	अगर (err)
		जाओ out;

	अगर (adev->asic_type == CHIP_KAVERI) अणु
		snम_लिखो(fw_name, माप(fw_name), "amdgpu/%s_mec2.bin", chip_name);
		err = request_firmware(&adev->gfx.mec2_fw, fw_name, adev->dev);
		अगर (err)
			जाओ out;
		err = amdgpu_ucode_validate(adev->gfx.mec2_fw);
		अगर (err)
			जाओ out;
	पूर्ण

	snम_लिखो(fw_name, माप(fw_name), "amdgpu/%s_rlc.bin", chip_name);
	err = request_firmware(&adev->gfx.rlc_fw, fw_name, adev->dev);
	अगर (err)
		जाओ out;
	err = amdgpu_ucode_validate(adev->gfx.rlc_fw);

out:
	अगर (err) अणु
		pr_err("gfx7: Failed to load firmware \"%s\"\n", fw_name);
		release_firmware(adev->gfx.pfp_fw);
		adev->gfx.pfp_fw = शून्य;
		release_firmware(adev->gfx.me_fw);
		adev->gfx.me_fw = शून्य;
		release_firmware(adev->gfx.ce_fw);
		adev->gfx.ce_fw = शून्य;
		release_firmware(adev->gfx.mec_fw);
		adev->gfx.mec_fw = शून्य;
		release_firmware(adev->gfx.mec2_fw);
		adev->gfx.mec2_fw = शून्य;
		release_firmware(adev->gfx.rlc_fw);
		adev->gfx.rlc_fw = शून्य;
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम gfx_v7_0_मुक्त_microcode(काष्ठा amdgpu_device *adev)
अणु
	release_firmware(adev->gfx.pfp_fw);
	adev->gfx.pfp_fw = शून्य;
	release_firmware(adev->gfx.me_fw);
	adev->gfx.me_fw = शून्य;
	release_firmware(adev->gfx.ce_fw);
	adev->gfx.ce_fw = शून्य;
	release_firmware(adev->gfx.mec_fw);
	adev->gfx.mec_fw = शून्य;
	release_firmware(adev->gfx.mec2_fw);
	adev->gfx.mec2_fw = शून्य;
	release_firmware(adev->gfx.rlc_fw);
	adev->gfx.rlc_fw = शून्य;
पूर्ण

/**
 * gfx_v7_0_tiling_mode_table_init - init the hw tiling table
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Starting with SI, the tiling setup is करोne globally in a
 * set of 32 tiling modes.  Rather than selecting each set of
 * parameters per surface as on older asics, we just select
 * which index in the tiling table we want to use, and the
 * surface uses those parameters (CIK).
 */
अटल व्योम gfx_v7_0_tiling_mode_table_init(काष्ठा amdgpu_device *adev)
अणु
	स्थिर u32 num_tile_mode_states =
			ARRAY_SIZE(adev->gfx.config.tile_mode_array);
	स्थिर u32 num_secondary_tile_mode_states =
			ARRAY_SIZE(adev->gfx.config.macrotile_mode_array);
	u32 reg_offset, split_equal_to_row_size;
	uपूर्णांक32_t *tile, *macrotile;

	tile = adev->gfx.config.tile_mode_array;
	macrotile = adev->gfx.config.macrotile_mode_array;

	चयन (adev->gfx.config.mem_row_size_in_kb) अणु
	हाल 1:
		split_equal_to_row_size = ADDR_SURF_TILE_SPLIT_1KB;
		अवरोध;
	हाल 2:
	शेष:
		split_equal_to_row_size = ADDR_SURF_TILE_SPLIT_2KB;
		अवरोध;
	हाल 4:
		split_equal_to_row_size = ADDR_SURF_TILE_SPLIT_4KB;
		अवरोध;
	पूर्ण

	क्रम (reg_offset = 0; reg_offset < num_tile_mode_states; reg_offset++)
		tile[reg_offset] = 0;
	क्रम (reg_offset = 0; reg_offset < num_secondary_tile_mode_states; reg_offset++)
		macrotile[reg_offset] = 0;

	चयन (adev->asic_type) अणु
	हाल CHIP_BONAIRE:
		tile[0] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   PIPE_CONFIG(ADDR_SURF_P4_16x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_64B) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		tile[1] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   PIPE_CONFIG(ADDR_SURF_P4_16x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_128B) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		tile[2] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   PIPE_CONFIG(ADDR_SURF_P4_16x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_256B) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		tile[3] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   PIPE_CONFIG(ADDR_SURF_P4_16x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_512B) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		tile[4] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   PIPE_CONFIG(ADDR_SURF_P4_16x16) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING) |
			   TILE_SPLIT(split_equal_to_row_size));
		tile[5] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
			   PIPE_CONFIG(ADDR_SURF_P4_16x16) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		tile[6] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
			   PIPE_CONFIG(ADDR_SURF_P4_16x16) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING) |
			   TILE_SPLIT(split_equal_to_row_size));
		tile[7] = (TILE_SPLIT(split_equal_to_row_size));
		tile[8] = (ARRAY_MODE(ARRAY_LINEAR_ALIGNED) |
			   PIPE_CONFIG(ADDR_SURF_P4_16x16));
		tile[9] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
			   PIPE_CONFIG(ADDR_SURF_P4_16x16) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DISPLAY_MICRO_TILING));
		tile[10] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			    PIPE_CONFIG(ADDR_SURF_P4_16x16) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_DISPLAY_MICRO_TILING) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		tile[11] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
			    PIPE_CONFIG(ADDR_SURF_P4_16x16) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_DISPLAY_MICRO_TILING) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_8));
		tile[12] = (TILE_SPLIT(split_equal_to_row_size));
		tile[13] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
			    PIPE_CONFIG(ADDR_SURF_P4_16x16) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING));
		tile[14] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			    PIPE_CONFIG(ADDR_SURF_P4_16x16) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		tile[15] = (ARRAY_MODE(ARRAY_3D_TILED_THIN1) |
			    PIPE_CONFIG(ADDR_SURF_P4_16x16) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		tile[16] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
			    PIPE_CONFIG(ADDR_SURF_P4_16x16) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_8));
		tile[17] = (TILE_SPLIT(split_equal_to_row_size));
		tile[18] = (ARRAY_MODE(ARRAY_1D_TILED_THICK) |
			    PIPE_CONFIG(ADDR_SURF_P4_16x16) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		tile[19] = (ARRAY_MODE(ARRAY_1D_TILED_THICK) |
			    PIPE_CONFIG(ADDR_SURF_P4_16x16) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING));
		tile[20] = (ARRAY_MODE(ARRAY_2D_TILED_THICK) |
			    PIPE_CONFIG(ADDR_SURF_P4_16x16) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		tile[21] =  (ARRAY_MODE(ARRAY_3D_TILED_THICK) |
			    PIPE_CONFIG(ADDR_SURF_P4_16x16) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		tile[22] = (ARRAY_MODE(ARRAY_PRT_TILED_THICK) |
			    PIPE_CONFIG(ADDR_SURF_P4_16x16) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		tile[23] = (TILE_SPLIT(split_equal_to_row_size));
		tile[24] = (ARRAY_MODE(ARRAY_2D_TILED_THICK) |
			    PIPE_CONFIG(ADDR_SURF_P4_16x16) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		tile[25] = (ARRAY_MODE(ARRAY_2D_TILED_XTHICK) |
			    PIPE_CONFIG(ADDR_SURF_P4_16x16) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		tile[26] = (ARRAY_MODE(ARRAY_3D_TILED_XTHICK) |
			    PIPE_CONFIG(ADDR_SURF_P4_16x16) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		tile[27] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
			    PIPE_CONFIG(ADDR_SURF_P4_16x16) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_ROTATED_MICRO_TILING));
		tile[28] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			    PIPE_CONFIG(ADDR_SURF_P4_16x16) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_ROTATED_MICRO_TILING) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		tile[29] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
			    PIPE_CONFIG(ADDR_SURF_P4_16x16) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_ROTATED_MICRO_TILING) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_8));
		tile[30] = (TILE_SPLIT(split_equal_to_row_size));

		macrotile[0] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		macrotile[1] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_2) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		macrotile[2] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		macrotile[3] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		macrotile[4] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		macrotile[5] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				NUM_BANKS(ADDR_SURF_8_BANK));
		macrotile[6] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_1) |
				NUM_BANKS(ADDR_SURF_4_BANK));
		macrotile[8] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_2) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_8) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		macrotile[9] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_2) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		macrotile[10] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		macrotile[11] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_2) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		macrotile[12] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		macrotile[13] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				NUM_BANKS(ADDR_SURF_8_BANK));
		macrotile[14] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_1) |
				NUM_BANKS(ADDR_SURF_4_BANK));

		क्रम (reg_offset = 0; reg_offset < num_tile_mode_states; reg_offset++)
			WREG32(mmGB_TILE_MODE0 + reg_offset, tile[reg_offset]);
		क्रम (reg_offset = 0; reg_offset < num_secondary_tile_mode_states; reg_offset++)
			अगर (reg_offset != 7)
				WREG32(mmGB_MACROTILE_MODE0 + reg_offset, macrotile[reg_offset]);
		अवरोध;
	हाल CHIP_HAWAII:
		tile[0] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_64B) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		tile[1] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_128B) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		tile[2] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_256B) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		tile[3] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_512B) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		tile[4] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING) |
			   TILE_SPLIT(split_equal_to_row_size));
		tile[5] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
			   PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING) |
			   TILE_SPLIT(split_equal_to_row_size));
		tile[6] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
			   PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING) |
			   TILE_SPLIT(split_equal_to_row_size));
		tile[7] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
			   PIPE_CONFIG(ADDR_SURF_P4_16x16) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING) |
			   TILE_SPLIT(split_equal_to_row_size));
		tile[8] = (ARRAY_MODE(ARRAY_LINEAR_ALIGNED) |
			   PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16));
		tile[9] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
			   PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DISPLAY_MICRO_TILING));
		tile[10] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			    PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_DISPLAY_MICRO_TILING) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		tile[11] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
			    PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_DISPLAY_MICRO_TILING) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_8));
		tile[12] = (ARRAY_MODE(ARRAY_PRT_2D_TILED_THIN1) |
			    PIPE_CONFIG(ADDR_SURF_P4_16x16) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_DISPLAY_MICRO_TILING) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_8));
		tile[13] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
			    PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING));
		tile[14] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			    PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		tile[15] = (ARRAY_MODE(ARRAY_3D_TILED_THIN1) |
			    PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		tile[16] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
			    PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_8));
		tile[17] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
			    PIPE_CONFIG(ADDR_SURF_P4_16x16) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_8));
		tile[18] = (ARRAY_MODE(ARRAY_1D_TILED_THICK) |
			    PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		tile[19] = (ARRAY_MODE(ARRAY_1D_TILED_THICK) |
			    PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_THICK_MICRO_TILING));
		tile[20] = (ARRAY_MODE(ARRAY_2D_TILED_THICK) |
			    PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_THICK_MICRO_TILING) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		tile[21] = (ARRAY_MODE(ARRAY_3D_TILED_THICK) |
			    PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_THICK_MICRO_TILING) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		tile[22] = (ARRAY_MODE(ARRAY_PRT_TILED_THICK) |
			    PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_THICK_MICRO_TILING) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		tile[23] = (ARRAY_MODE(ARRAY_PRT_TILED_THICK) |
			    PIPE_CONFIG(ADDR_SURF_P4_16x16) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_THICK_MICRO_TILING) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		tile[24] = (ARRAY_MODE(ARRAY_2D_TILED_THICK) |
			    PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		tile[25] = (ARRAY_MODE(ARRAY_2D_TILED_XTHICK) |
			    PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_THICK_MICRO_TILING) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		tile[26] = (ARRAY_MODE(ARRAY_3D_TILED_XTHICK) |
			    PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_THICK_MICRO_TILING) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		tile[27] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
			    PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_ROTATED_MICRO_TILING));
		tile[28] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			    PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_ROTATED_MICRO_TILING) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		tile[29] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
			    PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_ROTATED_MICRO_TILING) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_8));
		tile[30] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
			    PIPE_CONFIG(ADDR_SURF_P4_16x16) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_ROTATED_MICRO_TILING) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_8));

		macrotile[0] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		macrotile[1] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_2) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		macrotile[2] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_1) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		macrotile[3] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_1) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		macrotile[4] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_1) |
				NUM_BANKS(ADDR_SURF_8_BANK));
		macrotile[5] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_1) |
				NUM_BANKS(ADDR_SURF_4_BANK));
		macrotile[6] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_1) |
				NUM_BANKS(ADDR_SURF_4_BANK));
		macrotile[8] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		macrotile[9] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_2) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		macrotile[10] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_1) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		macrotile[11] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_1) |
				NUM_BANKS(ADDR_SURF_8_BANK));
		macrotile[12] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		macrotile[13] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				NUM_BANKS(ADDR_SURF_8_BANK));
		macrotile[14] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_1) |
				NUM_BANKS(ADDR_SURF_4_BANK));

		क्रम (reg_offset = 0; reg_offset < num_tile_mode_states; reg_offset++)
			WREG32(mmGB_TILE_MODE0 + reg_offset, tile[reg_offset]);
		क्रम (reg_offset = 0; reg_offset < num_secondary_tile_mode_states; reg_offset++)
			अगर (reg_offset != 7)
				WREG32(mmGB_MACROTILE_MODE0 + reg_offset, macrotile[reg_offset]);
		अवरोध;
	हाल CHIP_KABINI:
	हाल CHIP_KAVERI:
	हाल CHIP_MULLINS:
	शेष:
		tile[0] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   PIPE_CONFIG(ADDR_SURF_P2) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_64B) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		tile[1] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   PIPE_CONFIG(ADDR_SURF_P2) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_128B) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		tile[2] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   PIPE_CONFIG(ADDR_SURF_P2) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_256B) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		tile[3] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   PIPE_CONFIG(ADDR_SURF_P2) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_512B) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		tile[4] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   PIPE_CONFIG(ADDR_SURF_P2) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING) |
			   TILE_SPLIT(split_equal_to_row_size));
		tile[5] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
			   PIPE_CONFIG(ADDR_SURF_P2) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		tile[6] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
			   PIPE_CONFIG(ADDR_SURF_P2) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING) |
			   TILE_SPLIT(split_equal_to_row_size));
		tile[7] = (TILE_SPLIT(split_equal_to_row_size));
		tile[8] = (ARRAY_MODE(ARRAY_LINEAR_ALIGNED) |
			   PIPE_CONFIG(ADDR_SURF_P2));
		tile[9] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
			   PIPE_CONFIG(ADDR_SURF_P2) |
			   MICRO_TILE_MODE_NEW(ADDR_SURF_DISPLAY_MICRO_TILING));
		tile[10] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			    PIPE_CONFIG(ADDR_SURF_P2) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_DISPLAY_MICRO_TILING) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		tile[11] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
			    PIPE_CONFIG(ADDR_SURF_P2) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_DISPLAY_MICRO_TILING) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_8));
		tile[12] = (TILE_SPLIT(split_equal_to_row_size));
		tile[13] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
			    PIPE_CONFIG(ADDR_SURF_P2) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING));
		tile[14] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			    PIPE_CONFIG(ADDR_SURF_P2) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		tile[15] = (ARRAY_MODE(ARRAY_3D_TILED_THIN1) |
			    PIPE_CONFIG(ADDR_SURF_P2) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		tile[16] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
			    PIPE_CONFIG(ADDR_SURF_P2) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_8));
		tile[17] = (TILE_SPLIT(split_equal_to_row_size));
		tile[18] = (ARRAY_MODE(ARRAY_1D_TILED_THICK) |
			    PIPE_CONFIG(ADDR_SURF_P2) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		tile[19] = (ARRAY_MODE(ARRAY_1D_TILED_THICK) |
			    PIPE_CONFIG(ADDR_SURF_P2) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_THICK_MICRO_TILING));
		tile[20] = (ARRAY_MODE(ARRAY_2D_TILED_THICK) |
			    PIPE_CONFIG(ADDR_SURF_P2) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_THICK_MICRO_TILING) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		tile[21] = (ARRAY_MODE(ARRAY_3D_TILED_THICK) |
			    PIPE_CONFIG(ADDR_SURF_P2) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_THICK_MICRO_TILING) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		tile[22] = (ARRAY_MODE(ARRAY_PRT_TILED_THICK) |
			    PIPE_CONFIG(ADDR_SURF_P2) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_THICK_MICRO_TILING) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		tile[23] = (TILE_SPLIT(split_equal_to_row_size));
		tile[24] = (ARRAY_MODE(ARRAY_2D_TILED_THICK) |
			    PIPE_CONFIG(ADDR_SURF_P2) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		tile[25] = (ARRAY_MODE(ARRAY_2D_TILED_XTHICK) |
			    PIPE_CONFIG(ADDR_SURF_P2) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_THICK_MICRO_TILING) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		tile[26] = (ARRAY_MODE(ARRAY_3D_TILED_XTHICK) |
			    PIPE_CONFIG(ADDR_SURF_P2) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_THICK_MICRO_TILING) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		tile[27] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
			    PIPE_CONFIG(ADDR_SURF_P2) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_ROTATED_MICRO_TILING));
		tile[28] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			    PIPE_CONFIG(ADDR_SURF_P2) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_ROTATED_MICRO_TILING) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		tile[29] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
			    PIPE_CONFIG(ADDR_SURF_P2) |
			    MICRO_TILE_MODE_NEW(ADDR_SURF_ROTATED_MICRO_TILING) |
			    SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_8));
		tile[30] = (TILE_SPLIT(split_equal_to_row_size));

		macrotile[0] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_8_BANK));
		macrotile[1] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_2) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_8_BANK));
		macrotile[2] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_2) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				NUM_BANKS(ADDR_SURF_8_BANK));
		macrotile[3] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				NUM_BANKS(ADDR_SURF_8_BANK));
		macrotile[4] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				NUM_BANKS(ADDR_SURF_8_BANK));
		macrotile[5] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				NUM_BANKS(ADDR_SURF_8_BANK));
		macrotile[6] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				NUM_BANKS(ADDR_SURF_8_BANK));
		macrotile[8] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_4) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_8) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		macrotile[9] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_4) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		macrotile[10] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_2) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		macrotile[11] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_2) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_2) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		macrotile[12] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_2) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		macrotile[13] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		macrotile[14] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				NUM_BANKS(ADDR_SURF_8_BANK));

		क्रम (reg_offset = 0; reg_offset < num_tile_mode_states; reg_offset++)
			WREG32(mmGB_TILE_MODE0 + reg_offset, tile[reg_offset]);
		क्रम (reg_offset = 0; reg_offset < num_secondary_tile_mode_states; reg_offset++)
			अगर (reg_offset != 7)
				WREG32(mmGB_MACROTILE_MODE0 + reg_offset, macrotile[reg_offset]);
		अवरोध;
	पूर्ण
पूर्ण

/**
 * gfx_v7_0_select_se_sh - select which SE, SH to address
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @se_num: shader engine to address
 * @sh_num: sh block to address
 * @instance: Certain रेजिस्टरs are instanced per SE or SH.
 *            0xffffffff means broadcast to all SEs or SHs (CIK).
 *
 * Select which SE, SH combinations to address.
 */
अटल व्योम gfx_v7_0_select_se_sh(काष्ठा amdgpu_device *adev,
				  u32 se_num, u32 sh_num, u32 instance)
अणु
	u32 data;

	अगर (instance == 0xffffffff)
		data = REG_SET_FIELD(0, GRBM_GFX_INDEX, INSTANCE_BROADCAST_WRITES, 1);
	अन्यथा
		data = REG_SET_FIELD(0, GRBM_GFX_INDEX, INSTANCE_INDEX, instance);

	अगर ((se_num == 0xffffffff) && (sh_num == 0xffffffff))
		data |= GRBM_GFX_INDEX__SH_BROADCAST_WRITES_MASK |
			GRBM_GFX_INDEX__SE_BROADCAST_WRITES_MASK;
	अन्यथा अगर (se_num == 0xffffffff)
		data |= GRBM_GFX_INDEX__SE_BROADCAST_WRITES_MASK |
			(sh_num << GRBM_GFX_INDEX__SH_INDEX__SHIFT);
	अन्यथा अगर (sh_num == 0xffffffff)
		data |= GRBM_GFX_INDEX__SH_BROADCAST_WRITES_MASK |
			(se_num << GRBM_GFX_INDEX__SE_INDEX__SHIFT);
	अन्यथा
		data |= (sh_num << GRBM_GFX_INDEX__SH_INDEX__SHIFT) |
			(se_num << GRBM_GFX_INDEX__SE_INDEX__SHIFT);
	WREG32(mmGRBM_GFX_INDEX, data);
पूर्ण

/**
 * gfx_v7_0_get_rb_active_biपंचांगap - computes the mask of enabled RBs
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Calculates the biपंचांगask of enabled RBs (CIK).
 * Returns the enabled RB biपंचांगask.
 */
अटल u32 gfx_v7_0_get_rb_active_biपंचांगap(काष्ठा amdgpu_device *adev)
अणु
	u32 data, mask;

	data = RREG32(mmCC_RB_BACKEND_DISABLE);
	data |= RREG32(mmGC_USER_RB_BACKEND_DISABLE);

	data &= CC_RB_BACKEND_DISABLE__BACKEND_DISABLE_MASK;
	data >>= GC_USER_RB_BACKEND_DISABLE__BACKEND_DISABLE__SHIFT;

	mask = amdgpu_gfx_create_biपंचांगask(adev->gfx.config.max_backends_per_se /
					 adev->gfx.config.max_sh_per_se);

	वापस (~data) & mask;
पूर्ण

अटल व्योम
gfx_v7_0_raster_config(काष्ठा amdgpu_device *adev, u32 *rconf, u32 *rconf1)
अणु
	चयन (adev->asic_type) अणु
	हाल CHIP_BONAIRE:
		*rconf |= RB_MAP_PKR0(2) | RB_XSEL2(1) | SE_MAP(2) |
			  SE_XSEL(1) | SE_YSEL(1);
		*rconf1 |= 0x0;
		अवरोध;
	हाल CHIP_HAWAII:
		*rconf |= RB_MAP_PKR0(2) | RB_MAP_PKR1(2) |
			  RB_XSEL2(1) | PKR_MAP(2) | PKR_XSEL(1) |
			  PKR_YSEL(1) | SE_MAP(2) | SE_XSEL(2) |
			  SE_YSEL(3);
		*rconf1 |= SE_PAIR_MAP(2) | SE_PAIR_XSEL(3) |
			   SE_PAIR_YSEL(2);
		अवरोध;
	हाल CHIP_KAVERI:
		*rconf |= RB_MAP_PKR0(2);
		*rconf1 |= 0x0;
		अवरोध;
	हाल CHIP_KABINI:
	हाल CHIP_MULLINS:
		*rconf |= 0x0;
		*rconf1 |= 0x0;
		अवरोध;
	शेष:
		DRM_ERROR("unknown asic: 0x%x\n", adev->asic_type);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
gfx_v7_0_ग_लिखो_harvested_raster_configs(काष्ठा amdgpu_device *adev,
					u32 raster_config, u32 raster_config_1,
					अचिन्हित rb_mask, अचिन्हित num_rb)
अणु
	अचिन्हित sh_per_se = max_t(अचिन्हित, adev->gfx.config.max_sh_per_se, 1);
	अचिन्हित num_se = max_t(अचिन्हित, adev->gfx.config.max_shader_engines, 1);
	अचिन्हित rb_per_pkr = min_t(अचिन्हित, num_rb / num_se / sh_per_se, 2);
	अचिन्हित rb_per_se = num_rb / num_se;
	अचिन्हित se_mask[4];
	अचिन्हित se;

	se_mask[0] = ((1 << rb_per_se) - 1) & rb_mask;
	se_mask[1] = (se_mask[0] << rb_per_se) & rb_mask;
	se_mask[2] = (se_mask[1] << rb_per_se) & rb_mask;
	se_mask[3] = (se_mask[2] << rb_per_se) & rb_mask;

	WARN_ON(!(num_se == 1 || num_se == 2 || num_se == 4));
	WARN_ON(!(sh_per_se == 1 || sh_per_se == 2));
	WARN_ON(!(rb_per_pkr == 1 || rb_per_pkr == 2));

	अगर ((num_se > 2) && ((!se_mask[0] && !se_mask[1]) ||
			     (!se_mask[2] && !se_mask[3]))) अणु
		raster_config_1 &= ~SE_PAIR_MAP_MASK;

		अगर (!se_mask[0] && !se_mask[1]) अणु
			raster_config_1 |=
				SE_PAIR_MAP(RASTER_CONFIG_SE_PAIR_MAP_3);
		पूर्ण अन्यथा अणु
			raster_config_1 |=
				SE_PAIR_MAP(RASTER_CONFIG_SE_PAIR_MAP_0);
		पूर्ण
	पूर्ण

	क्रम (se = 0; se < num_se; se++) अणु
		अचिन्हित raster_config_se = raster_config;
		अचिन्हित pkr0_mask = ((1 << rb_per_pkr) - 1) << (se * rb_per_se);
		अचिन्हित pkr1_mask = pkr0_mask << rb_per_pkr;
		पूर्णांक idx = (se / 2) * 2;

		अगर ((num_se > 1) && (!se_mask[idx] || !se_mask[idx + 1])) अणु
			raster_config_se &= ~SE_MAP_MASK;

			अगर (!se_mask[idx]) अणु
				raster_config_se |= SE_MAP(RASTER_CONFIG_SE_MAP_3);
			पूर्ण अन्यथा अणु
				raster_config_se |= SE_MAP(RASTER_CONFIG_SE_MAP_0);
			पूर्ण
		पूर्ण

		pkr0_mask &= rb_mask;
		pkr1_mask &= rb_mask;
		अगर (rb_per_se > 2 && (!pkr0_mask || !pkr1_mask)) अणु
			raster_config_se &= ~PKR_MAP_MASK;

			अगर (!pkr0_mask) अणु
				raster_config_se |= PKR_MAP(RASTER_CONFIG_PKR_MAP_3);
			पूर्ण अन्यथा अणु
				raster_config_se |= PKR_MAP(RASTER_CONFIG_PKR_MAP_0);
			पूर्ण
		पूर्ण

		अगर (rb_per_se >= 2) अणु
			अचिन्हित rb0_mask = 1 << (se * rb_per_se);
			अचिन्हित rb1_mask = rb0_mask << 1;

			rb0_mask &= rb_mask;
			rb1_mask &= rb_mask;
			अगर (!rb0_mask || !rb1_mask) अणु
				raster_config_se &= ~RB_MAP_PKR0_MASK;

				अगर (!rb0_mask) अणु
					raster_config_se |=
						RB_MAP_PKR0(RASTER_CONFIG_RB_MAP_3);
				पूर्ण अन्यथा अणु
					raster_config_se |=
						RB_MAP_PKR0(RASTER_CONFIG_RB_MAP_0);
				पूर्ण
			पूर्ण

			अगर (rb_per_se > 2) अणु
				rb0_mask = 1 << (se * rb_per_se + rb_per_pkr);
				rb1_mask = rb0_mask << 1;
				rb0_mask &= rb_mask;
				rb1_mask &= rb_mask;
				अगर (!rb0_mask || !rb1_mask) अणु
					raster_config_se &= ~RB_MAP_PKR1_MASK;

					अगर (!rb0_mask) अणु
						raster_config_se |=
							RB_MAP_PKR1(RASTER_CONFIG_RB_MAP_3);
					पूर्ण अन्यथा अणु
						raster_config_se |=
							RB_MAP_PKR1(RASTER_CONFIG_RB_MAP_0);
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण

		/* GRBM_GFX_INDEX has a dअगरferent offset on CI+ */
		gfx_v7_0_select_se_sh(adev, se, 0xffffffff, 0xffffffff);
		WREG32(mmPA_SC_RASTER_CONFIG, raster_config_se);
		WREG32(mmPA_SC_RASTER_CONFIG_1, raster_config_1);
	पूर्ण

	/* GRBM_GFX_INDEX has a dअगरferent offset on CI+ */
	gfx_v7_0_select_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff);
पूर्ण

/**
 * gfx_v7_0_setup_rb - setup the RBs on the asic
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Configures per-SE/SH RB रेजिस्टरs (CIK).
 */
अटल व्योम gfx_v7_0_setup_rb(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i, j;
	u32 data;
	u32 raster_config = 0, raster_config_1 = 0;
	u32 active_rbs = 0;
	u32 rb_biपंचांगap_width_per_sh = adev->gfx.config.max_backends_per_se /
					adev->gfx.config.max_sh_per_se;
	अचिन्हित num_rb_pipes;

	mutex_lock(&adev->grbm_idx_mutex);
	क्रम (i = 0; i < adev->gfx.config.max_shader_engines; i++) अणु
		क्रम (j = 0; j < adev->gfx.config.max_sh_per_se; j++) अणु
			gfx_v7_0_select_se_sh(adev, i, j, 0xffffffff);
			data = gfx_v7_0_get_rb_active_biपंचांगap(adev);
			active_rbs |= data << ((i * adev->gfx.config.max_sh_per_se + j) *
					       rb_biपंचांगap_width_per_sh);
		पूर्ण
	पूर्ण
	gfx_v7_0_select_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff);

	adev->gfx.config.backend_enable_mask = active_rbs;
	adev->gfx.config.num_rbs = hweight32(active_rbs);

	num_rb_pipes = min_t(अचिन्हित, adev->gfx.config.max_backends_per_se *
			     adev->gfx.config.max_shader_engines, 16);

	gfx_v7_0_raster_config(adev, &raster_config, &raster_config_1);

	अगर (!adev->gfx.config.backend_enable_mask ||
			adev->gfx.config.num_rbs >= num_rb_pipes) अणु
		WREG32(mmPA_SC_RASTER_CONFIG, raster_config);
		WREG32(mmPA_SC_RASTER_CONFIG_1, raster_config_1);
	पूर्ण अन्यथा अणु
		gfx_v7_0_ग_लिखो_harvested_raster_configs(adev, raster_config, raster_config_1,
							adev->gfx.config.backend_enable_mask,
							num_rb_pipes);
	पूर्ण

	/* cache the values क्रम userspace */
	क्रम (i = 0; i < adev->gfx.config.max_shader_engines; i++) अणु
		क्रम (j = 0; j < adev->gfx.config.max_sh_per_se; j++) अणु
			gfx_v7_0_select_se_sh(adev, i, j, 0xffffffff);
			adev->gfx.config.rb_config[i][j].rb_backend_disable =
				RREG32(mmCC_RB_BACKEND_DISABLE);
			adev->gfx.config.rb_config[i][j].user_rb_backend_disable =
				RREG32(mmGC_USER_RB_BACKEND_DISABLE);
			adev->gfx.config.rb_config[i][j].raster_config =
				RREG32(mmPA_SC_RASTER_CONFIG);
			adev->gfx.config.rb_config[i][j].raster_config_1 =
				RREG32(mmPA_SC_RASTER_CONFIG_1);
		पूर्ण
	पूर्ण
	gfx_v7_0_select_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff);
	mutex_unlock(&adev->grbm_idx_mutex);
पूर्ण

#घोषणा DEFAULT_SH_MEM_BASES	(0x6000)
/**
 * gfx_v7_0_init_compute_vmid - gart enable
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Initialize compute vmid sh_mem रेजिस्टरs
 *
 */
अटल व्योम gfx_v7_0_init_compute_vmid(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i;
	uपूर्णांक32_t sh_mem_config;
	uपूर्णांक32_t sh_mem_bases;

	/*
	 * Configure apertures:
	 * LDS:         0x60000000'00000000 - 0x60000001'00000000 (4GB)
	 * Scratch:     0x60000001'00000000 - 0x60000002'00000000 (4GB)
	 * GPUVM:       0x60010000'00000000 - 0x60020000'00000000 (1TB)
	*/
	sh_mem_bases = DEFAULT_SH_MEM_BASES | (DEFAULT_SH_MEM_BASES << 16);
	sh_mem_config = SH_MEM_ALIGNMENT_MODE_UNALIGNED <<
			SH_MEM_CONFIG__ALIGNMENT_MODE__SHIFT;
	sh_mem_config |= MTYPE_NONCACHED << SH_MEM_CONFIG__DEFAULT_MTYPE__SHIFT;
	mutex_lock(&adev->srbm_mutex);
	क्रम (i = adev->vm_manager.first_kfd_vmid; i < AMDGPU_NUM_VMID; i++) अणु
		cik_srbm_select(adev, 0, 0, 0, i);
		/* CP and shaders */
		WREG32(mmSH_MEM_CONFIG, sh_mem_config);
		WREG32(mmSH_MEM_APE1_BASE, 1);
		WREG32(mmSH_MEM_APE1_LIMIT, 0);
		WREG32(mmSH_MEM_BASES, sh_mem_bases);
	पूर्ण
	cik_srbm_select(adev, 0, 0, 0, 0);
	mutex_unlock(&adev->srbm_mutex);

	/* Initialize all compute VMIDs to have no GDS, GWS, or OA
	   access. These should be enabled by FW क्रम target VMIDs. */
	क्रम (i = adev->vm_manager.first_kfd_vmid; i < AMDGPU_NUM_VMID; i++) अणु
		WREG32(amdgpu_gds_reg_offset[i].mem_base, 0);
		WREG32(amdgpu_gds_reg_offset[i].mem_size, 0);
		WREG32(amdgpu_gds_reg_offset[i].gws, 0);
		WREG32(amdgpu_gds_reg_offset[i].oa, 0);
	पूर्ण
पूर्ण

अटल व्योम gfx_v7_0_init_gds_vmid(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक vmid;

	/*
	 * Initialize all compute and user-gfx VMIDs to have no GDS, GWS, or OA
	 * access. Compute VMIDs should be enabled by FW क्रम target VMIDs,
	 * the driver can enable them क्रम graphics. VMID0 should मुख्यtain
	 * access so that HWS firmware can save/restore entries.
	 */
	क्रम (vmid = 1; vmid < AMDGPU_NUM_VMID; vmid++) अणु
		WREG32(amdgpu_gds_reg_offset[vmid].mem_base, 0);
		WREG32(amdgpu_gds_reg_offset[vmid].mem_size, 0);
		WREG32(amdgpu_gds_reg_offset[vmid].gws, 0);
		WREG32(amdgpu_gds_reg_offset[vmid].oa, 0);
	पूर्ण
पूर्ण

अटल व्योम gfx_v7_0_config_init(काष्ठा amdgpu_device *adev)
अणु
	adev->gfx.config.द्विगुन_offchip_lds_buf = 1;
पूर्ण

/**
 * gfx_v7_0_स्थिरants_init - setup the 3D engine
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * init the gfx स्थिरants such as the 3D engine, tiling configuration
 * रेजिस्टरs, maximum number of quad pipes, render backends...
 */
अटल व्योम gfx_v7_0_स्थिरants_init(काष्ठा amdgpu_device *adev)
अणु
	u32 sh_mem_cfg, sh_अटल_mem_cfg, sh_mem_base;
	u32 पंचांगp;
	पूर्णांक i;

	WREG32(mmGRBM_CNTL, (0xff << GRBM_CNTL__READ_TIMEOUT__SHIFT));

	WREG32(mmGB_ADDR_CONFIG, adev->gfx.config.gb_addr_config);
	WREG32(mmHDP_ADDR_CONFIG, adev->gfx.config.gb_addr_config);
	WREG32(mmDMIF_ADDR_CALC, adev->gfx.config.gb_addr_config);

	gfx_v7_0_tiling_mode_table_init(adev);

	gfx_v7_0_setup_rb(adev);
	gfx_v7_0_get_cu_info(adev);
	gfx_v7_0_config_init(adev);

	/* set HW शेषs क्रम 3D engine */
	WREG32(mmCP_MEQ_THRESHOLDS,
	       (0x30 << CP_MEQ_THRESHOLDS__MEQ1_START__SHIFT) |
	       (0x60 << CP_MEQ_THRESHOLDS__MEQ2_START__SHIFT));

	mutex_lock(&adev->grbm_idx_mutex);
	/*
	 * making sure that the following रेजिस्टर ग_लिखोs will be broadcasted
	 * to all the shaders
	 */
	gfx_v7_0_select_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff);

	/* XXX SH_MEM regs */
	/* where to put LDS, scratch, GPUVM in FSA64 space */
	sh_mem_cfg = REG_SET_FIELD(0, SH_MEM_CONFIG, ALIGNMENT_MODE,
				   SH_MEM_ALIGNMENT_MODE_UNALIGNED);
	sh_mem_cfg = REG_SET_FIELD(sh_mem_cfg, SH_MEM_CONFIG, DEFAULT_MTYPE,
				   MTYPE_NC);
	sh_mem_cfg = REG_SET_FIELD(sh_mem_cfg, SH_MEM_CONFIG, APE1_MTYPE,
				   MTYPE_UC);
	sh_mem_cfg = REG_SET_FIELD(sh_mem_cfg, SH_MEM_CONFIG, PRIVATE_ATC, 0);

	sh_अटल_mem_cfg = REG_SET_FIELD(0, SH_STATIC_MEM_CONFIG,
				   SWIZZLE_ENABLE, 1);
	sh_अटल_mem_cfg = REG_SET_FIELD(sh_अटल_mem_cfg, SH_STATIC_MEM_CONFIG,
				   ELEMENT_SIZE, 1);
	sh_अटल_mem_cfg = REG_SET_FIELD(sh_अटल_mem_cfg, SH_STATIC_MEM_CONFIG,
				   INDEX_STRIDE, 3);
	WREG32(mmSH_STATIC_MEM_CONFIG, sh_अटल_mem_cfg);

	mutex_lock(&adev->srbm_mutex);
	क्रम (i = 0; i < adev->vm_manager.id_mgr[0].num_ids; i++) अणु
		अगर (i == 0)
			sh_mem_base = 0;
		अन्यथा
			sh_mem_base = adev->gmc.shared_aperture_start >> 48;
		cik_srbm_select(adev, 0, 0, 0, i);
		/* CP and shaders */
		WREG32(mmSH_MEM_CONFIG, sh_mem_cfg);
		WREG32(mmSH_MEM_APE1_BASE, 1);
		WREG32(mmSH_MEM_APE1_LIMIT, 0);
		WREG32(mmSH_MEM_BASES, sh_mem_base);
	पूर्ण
	cik_srbm_select(adev, 0, 0, 0, 0);
	mutex_unlock(&adev->srbm_mutex);

	gfx_v7_0_init_compute_vmid(adev);
	gfx_v7_0_init_gds_vmid(adev);

	WREG32(mmSX_DEBUG_1, 0x20);

	WREG32(mmTA_CNTL_AUX, 0x00010000);

	पंचांगp = RREG32(mmSPI_CONFIG_CNTL);
	पंचांगp |= 0x03000000;
	WREG32(mmSPI_CONFIG_CNTL, पंचांगp);

	WREG32(mmSQ_CONFIG, 1);

	WREG32(mmDB_DEBUG, 0);

	पंचांगp = RREG32(mmDB_DEBUG2) & ~0xf00fffff;
	पंचांगp |= 0x00000400;
	WREG32(mmDB_DEBUG2, पंचांगp);

	पंचांगp = RREG32(mmDB_DEBUG3) & ~0x0002021c;
	पंचांगp |= 0x00020200;
	WREG32(mmDB_DEBUG3, पंचांगp);

	पंचांगp = RREG32(mmCB_HW_CONTROL) & ~0x00010000;
	पंचांगp |= 0x00018208;
	WREG32(mmCB_HW_CONTROL, पंचांगp);

	WREG32(mmSPI_CONFIG_CNTL_1, (4 << SPI_CONFIG_CNTL_1__VTX_DONE_DELAY__SHIFT));

	WREG32(mmPA_SC_FIFO_SIZE,
		((adev->gfx.config.sc_prim_fअगरo_size_frontend << PA_SC_FIFO_SIZE__SC_FRONTEND_PRIM_FIFO_SIZE__SHIFT) |
		(adev->gfx.config.sc_prim_fअगरo_size_backend << PA_SC_FIFO_SIZE__SC_BACKEND_PRIM_FIFO_SIZE__SHIFT) |
		(adev->gfx.config.sc_hiz_tile_fअगरo_size << PA_SC_FIFO_SIZE__SC_HIZ_TILE_FIFO_SIZE__SHIFT) |
		(adev->gfx.config.sc_earlyz_tile_fअगरo_size << PA_SC_FIFO_SIZE__SC_EARLYZ_TILE_FIFO_SIZE__SHIFT)));

	WREG32(mmVGT_NUM_INSTANCES, 1);

	WREG32(mmCP_PERFMON_CNTL, 0);

	WREG32(mmSQ_CONFIG, 0);

	WREG32(mmPA_SC_FORCE_EOV_MAX_CNTS,
		((4095 << PA_SC_FORCE_EOV_MAX_CNTS__FORCE_EOV_MAX_CLK_CNT__SHIFT) |
		(255 << PA_SC_FORCE_EOV_MAX_CNTS__FORCE_EOV_MAX_REZ_CNT__SHIFT)));

	WREG32(mmVGT_CACHE_INVALIDATION,
		(VC_AND_TC << VGT_CACHE_INVALIDATION__CACHE_INVALIDATION__SHIFT) |
		(ES_AND_GS_AUTO << VGT_CACHE_INVALIDATION__AUTO_INVLD_EN__SHIFT));

	WREG32(mmVGT_GS_VERTEX_REUSE, 16);
	WREG32(mmPA_SC_LINE_STIPPLE_STATE, 0);

	WREG32(mmPA_CL_ENHANCE, PA_CL_ENHANCE__CLIP_VTX_REORDER_ENA_MASK |
			(3 << PA_CL_ENHANCE__NUM_CLIP_SEQ__SHIFT));
	WREG32(mmPA_SC_ENHANCE, PA_SC_ENHANCE__ENABLE_PA_SC_OUT_OF_ORDER_MASK);

	पंचांगp = RREG32(mmSPI_ARB_PRIORITY);
	पंचांगp = REG_SET_FIELD(पंचांगp, SPI_ARB_PRIORITY, PIPE_ORDER_TS0, 2);
	पंचांगp = REG_SET_FIELD(पंचांगp, SPI_ARB_PRIORITY, PIPE_ORDER_TS1, 2);
	पंचांगp = REG_SET_FIELD(पंचांगp, SPI_ARB_PRIORITY, PIPE_ORDER_TS2, 2);
	पंचांगp = REG_SET_FIELD(पंचांगp, SPI_ARB_PRIORITY, PIPE_ORDER_TS3, 2);
	WREG32(mmSPI_ARB_PRIORITY, पंचांगp);

	mutex_unlock(&adev->grbm_idx_mutex);

	udelay(50);
पूर्ण

/*
 * GPU scratch रेजिस्टरs helpers function.
 */
/**
 * gfx_v7_0_scratch_init - setup driver info क्रम CP scratch regs
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Set up the number and offset of the CP scratch रेजिस्टरs.
 * NOTE: use of CP scratch रेजिस्टरs is a legacy पूर्णांकerface and
 * is not used by शेष on newer asics (r6xx+).  On newer asics,
 * memory buffers are used क्रम fences rather than scratch regs.
 */
अटल व्योम gfx_v7_0_scratch_init(काष्ठा amdgpu_device *adev)
अणु
	adev->gfx.scratch.num_reg = 8;
	adev->gfx.scratch.reg_base = mmSCRATCH_REG0;
	adev->gfx.scratch.मुक्त_mask = (1u << adev->gfx.scratch.num_reg) - 1;
पूर्ण

/**
 * gfx_v7_0_ring_test_ring - basic gfx ring test
 *
 * @ring: amdgpu_ring काष्ठाure holding ring inक्रमmation
 *
 * Allocate a scratch रेजिस्टर and ग_लिखो to it using the gfx ring (CIK).
 * Provides a basic gfx ring test to verअगरy that the ring is working.
 * Used by gfx_v7_0_cp_gfx_resume();
 * Returns 0 on success, error on failure.
 */
अटल पूर्णांक gfx_v7_0_ring_test_ring(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	uपूर्णांक32_t scratch;
	uपूर्णांक32_t पंचांगp = 0;
	अचिन्हित i;
	पूर्णांक r;

	r = amdgpu_gfx_scratch_get(adev, &scratch);
	अगर (r)
		वापस r;

	WREG32(scratch, 0xCAFEDEAD);
	r = amdgpu_ring_alloc(ring, 3);
	अगर (r)
		जाओ error_मुक्त_scratch;

	amdgpu_ring_ग_लिखो(ring, PACKET3(PACKET3_SET_UCONFIG_REG, 1));
	amdgpu_ring_ग_लिखो(ring, (scratch - PACKET3_SET_UCONFIG_REG_START));
	amdgpu_ring_ग_लिखो(ring, 0xDEADBEEF);
	amdgpu_ring_commit(ring);

	क्रम (i = 0; i < adev->usec_समयout; i++) अणु
		पंचांगp = RREG32(scratch);
		अगर (पंचांगp == 0xDEADBEEF)
			अवरोध;
		udelay(1);
	पूर्ण
	अगर (i >= adev->usec_समयout)
		r = -ETIMEDOUT;

error_मुक्त_scratch:
	amdgpu_gfx_scratch_मुक्त(adev, scratch);
	वापस r;
पूर्ण

/**
 * gfx_v7_0_ring_emit_hdp - emit an hdp flush on the cp
 *
 * @ring: amdgpu_ring काष्ठाure holding ring inक्रमmation
 *
 * Emits an hdp flush on the cp.
 */
अटल व्योम gfx_v7_0_ring_emit_hdp_flush(काष्ठा amdgpu_ring *ring)
अणु
	u32 ref_and_mask;
	पूर्णांक usepfp = ring->funcs->type == AMDGPU_RING_TYPE_COMPUTE ? 0 : 1;

	अगर (ring->funcs->type == AMDGPU_RING_TYPE_COMPUTE) अणु
		चयन (ring->me) अणु
		हाल 1:
			ref_and_mask = GPU_HDP_FLUSH_DONE__CP2_MASK << ring->pipe;
			अवरोध;
		हाल 2:
			ref_and_mask = GPU_HDP_FLUSH_DONE__CP6_MASK << ring->pipe;
			अवरोध;
		शेष:
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		ref_and_mask = GPU_HDP_FLUSH_DONE__CP0_MASK;
	पूर्ण

	amdgpu_ring_ग_लिखो(ring, PACKET3(PACKET3_WAIT_REG_MEM, 5));
	amdgpu_ring_ग_लिखो(ring, (WAIT_REG_MEM_OPERATION(1) | /* ग_लिखो, रुको, ग_लिखो */
				 WAIT_REG_MEM_FUNCTION(3) |  /* == */
				 WAIT_REG_MEM_ENGINE(usepfp)));   /* pfp or me */
	amdgpu_ring_ग_लिखो(ring, mmGPU_HDP_FLUSH_REQ);
	amdgpu_ring_ग_लिखो(ring, mmGPU_HDP_FLUSH_DONE);
	amdgpu_ring_ग_लिखो(ring, ref_and_mask);
	amdgpu_ring_ग_लिखो(ring, ref_and_mask);
	amdgpu_ring_ग_लिखो(ring, 0x20); /* poll पूर्णांकerval */
पूर्ण

अटल व्योम gfx_v7_0_ring_emit_vgt_flush(काष्ठा amdgpu_ring *ring)
अणु
	amdgpu_ring_ग_लिखो(ring, PACKET3(PACKET3_EVENT_WRITE, 0));
	amdgpu_ring_ग_लिखो(ring, EVENT_TYPE(VS_PARTIAL_FLUSH) |
		EVENT_INDEX(4));

	amdgpu_ring_ग_लिखो(ring, PACKET3(PACKET3_EVENT_WRITE, 0));
	amdgpu_ring_ग_लिखो(ring, EVENT_TYPE(VGT_FLUSH) |
		EVENT_INDEX(0));
पूर्ण

/**
 * gfx_v7_0_ring_emit_fence_gfx - emit a fence on the gfx ring
 *
 * @ring: amdgpu_ring काष्ठाure holding ring inक्रमmation
 * @addr: address
 * @seq: sequence number
 * @flags: fence related flags
 *
 * Emits a fence sequence number on the gfx ring and flushes
 * GPU caches.
 */
अटल व्योम gfx_v7_0_ring_emit_fence_gfx(काष्ठा amdgpu_ring *ring, u64 addr,
					 u64 seq, अचिन्हित flags)
अणु
	bool ग_लिखो64bit = flags & AMDGPU_FENCE_FLAG_64BIT;
	bool पूर्णांक_sel = flags & AMDGPU_FENCE_FLAG_INT;
	/* Workaround क्रम cache flush problems. First send a dummy EOP
	 * event करोwn the pipe with seq one below.
	 */
	amdgpu_ring_ग_लिखो(ring, PACKET3(PACKET3_EVENT_WRITE_EOP, 4));
	amdgpu_ring_ग_लिखो(ring, (EOP_TCL1_ACTION_EN |
				 EOP_TC_ACTION_EN |
				 EVENT_TYPE(CACHE_FLUSH_AND_INV_TS_EVENT) |
				 EVENT_INDEX(5)));
	amdgpu_ring_ग_लिखो(ring, addr & 0xfffffffc);
	amdgpu_ring_ग_लिखो(ring, (upper_32_bits(addr) & 0xffff) |
				DATA_SEL(1) | INT_SEL(0));
	amdgpu_ring_ग_लिखो(ring, lower_32_bits(seq - 1));
	amdgpu_ring_ग_लिखो(ring, upper_32_bits(seq - 1));

	/* Then send the real EOP event करोwn the pipe. */
	amdgpu_ring_ग_लिखो(ring, PACKET3(PACKET3_EVENT_WRITE_EOP, 4));
	amdgpu_ring_ग_लिखो(ring, (EOP_TCL1_ACTION_EN |
				 EOP_TC_ACTION_EN |
				 EVENT_TYPE(CACHE_FLUSH_AND_INV_TS_EVENT) |
				 EVENT_INDEX(5)));
	amdgpu_ring_ग_लिखो(ring, addr & 0xfffffffc);
	amdgpu_ring_ग_लिखो(ring, (upper_32_bits(addr) & 0xffff) |
				DATA_SEL(ग_लिखो64bit ? 2 : 1) | INT_SEL(पूर्णांक_sel ? 2 : 0));
	amdgpu_ring_ग_लिखो(ring, lower_32_bits(seq));
	amdgpu_ring_ग_लिखो(ring, upper_32_bits(seq));
पूर्ण

/**
 * gfx_v7_0_ring_emit_fence_compute - emit a fence on the compute ring
 *
 * @ring: amdgpu_ring काष्ठाure holding ring inक्रमmation
 * @addr: address
 * @seq: sequence number
 * @flags: fence related flags
 *
 * Emits a fence sequence number on the compute ring and flushes
 * GPU caches.
 */
अटल व्योम gfx_v7_0_ring_emit_fence_compute(काष्ठा amdgpu_ring *ring,
					     u64 addr, u64 seq,
					     अचिन्हित flags)
अणु
	bool ग_लिखो64bit = flags & AMDGPU_FENCE_FLAG_64BIT;
	bool पूर्णांक_sel = flags & AMDGPU_FENCE_FLAG_INT;

	/* RELEASE_MEM - flush caches, send पूर्णांक */
	amdgpu_ring_ग_लिखो(ring, PACKET3(PACKET3_RELEASE_MEM, 5));
	amdgpu_ring_ग_लिखो(ring, (EOP_TCL1_ACTION_EN |
				 EOP_TC_ACTION_EN |
				 EVENT_TYPE(CACHE_FLUSH_AND_INV_TS_EVENT) |
				 EVENT_INDEX(5)));
	amdgpu_ring_ग_लिखो(ring, DATA_SEL(ग_लिखो64bit ? 2 : 1) | INT_SEL(पूर्णांक_sel ? 2 : 0));
	amdgpu_ring_ग_लिखो(ring, addr & 0xfffffffc);
	amdgpu_ring_ग_लिखो(ring, upper_32_bits(addr));
	amdgpu_ring_ग_लिखो(ring, lower_32_bits(seq));
	amdgpu_ring_ग_लिखो(ring, upper_32_bits(seq));
पूर्ण

/*
 * IB stuff
 */
/**
 * gfx_v7_0_ring_emit_ib - emit an IB (Indirect Buffer) on the ring
 *
 * @ring: amdgpu_ring काष्ठाure holding ring inक्रमmation
 * @job: job to retrieve vmid from
 * @ib: amdgpu indirect buffer object
 * @flags: options (AMDGPU_HAVE_CTX_SWITCH)
 *
 * Emits an DE (drawing engine) or CE (स्थिरant engine) IB
 * on the gfx ring.  IBs are usually generated by userspace
 * acceleration drivers and submitted to the kernel क्रम
 * scheduling on the ring.  This function schedules the IB
 * on the gfx ring क्रम execution by the GPU.
 */
अटल व्योम gfx_v7_0_ring_emit_ib_gfx(काष्ठा amdgpu_ring *ring,
					काष्ठा amdgpu_job *job,
					काष्ठा amdgpu_ib *ib,
					uपूर्णांक32_t flags)
अणु
	अचिन्हित vmid = AMDGPU_JOB_GET_VMID(job);
	u32 header, control = 0;

	/* insert SWITCH_BUFFER packet beक्रमe first IB in the ring frame */
	अगर (flags & AMDGPU_HAVE_CTX_SWITCH) अणु
		amdgpu_ring_ग_लिखो(ring, PACKET3(PACKET3_SWITCH_BUFFER, 0));
		amdgpu_ring_ग_लिखो(ring, 0);
	पूर्ण

	अगर (ib->flags & AMDGPU_IB_FLAG_CE)
		header = PACKET3(PACKET3_INसूचीECT_BUFFER_CONST, 2);
	अन्यथा
		header = PACKET3(PACKET3_INसूचीECT_BUFFER, 2);

	control |= ib->length_dw | (vmid << 24);

	amdgpu_ring_ग_लिखो(ring, header);
	amdgpu_ring_ग_लिखो(ring,
#अगर_घोषित __BIG_ENDIAN
			  (2 << 0) |
#पूर्ण_अगर
			  (ib->gpu_addr & 0xFFFFFFFC));
	amdgpu_ring_ग_लिखो(ring, upper_32_bits(ib->gpu_addr) & 0xFFFF);
	amdgpu_ring_ग_लिखो(ring, control);
पूर्ण

अटल व्योम gfx_v7_0_ring_emit_ib_compute(काष्ठा amdgpu_ring *ring,
					  काष्ठा amdgpu_job *job,
					  काष्ठा amdgpu_ib *ib,
					  uपूर्णांक32_t flags)
अणु
	अचिन्हित vmid = AMDGPU_JOB_GET_VMID(job);
	u32 control = INसूचीECT_BUFFER_VALID | ib->length_dw | (vmid << 24);

	/* Currently, there is a high possibility to get wave ID mismatch
	 * between ME and GDS, leading to a hw deadlock, because ME generates
	 * dअगरferent wave IDs than the GDS expects. This situation happens
	 * अक्रमomly when at least 5 compute pipes use GDS ordered append.
	 * The wave IDs generated by ME are also wrong after suspend/resume.
	 * Those are probably bugs somewhere अन्यथा in the kernel driver.
	 *
	 * Writing GDS_COMPUTE_MAX_WAVE_ID resets wave ID counters in ME and
	 * GDS to 0 क्रम this ring (me/pipe).
	 */
	अगर (ib->flags & AMDGPU_IB_FLAG_RESET_GDS_MAX_WAVE_ID) अणु
		amdgpu_ring_ग_लिखो(ring, PACKET3(PACKET3_SET_CONFIG_REG, 1));
		amdgpu_ring_ग_लिखो(ring, mmGDS_COMPUTE_MAX_WAVE_ID - PACKET3_SET_CONFIG_REG_START);
		amdgpu_ring_ग_लिखो(ring, ring->adev->gds.gds_compute_max_wave_id);
	पूर्ण

	amdgpu_ring_ग_लिखो(ring, PACKET3(PACKET3_INसूचीECT_BUFFER, 2));
	amdgpu_ring_ग_लिखो(ring,
#अगर_घोषित __BIG_ENDIAN
					  (2 << 0) |
#पूर्ण_अगर
					  (ib->gpu_addr & 0xFFFFFFFC));
	amdgpu_ring_ग_लिखो(ring, upper_32_bits(ib->gpu_addr) & 0xFFFF);
	amdgpu_ring_ग_लिखो(ring, control);
पूर्ण

अटल व्योम gfx_v7_ring_emit_cntxcntl(काष्ठा amdgpu_ring *ring, uपूर्णांक32_t flags)
अणु
	uपूर्णांक32_t dw2 = 0;

	dw2 |= 0x80000000; /* set load_enable otherwise this package is just NOPs */
	अगर (flags & AMDGPU_HAVE_CTX_SWITCH) अणु
		gfx_v7_0_ring_emit_vgt_flush(ring);
		/* set load_global_config & load_global_uconfig */
		dw2 |= 0x8001;
		/* set load_cs_sh_regs */
		dw2 |= 0x01000000;
		/* set load_per_context_state & load_gfx_sh_regs */
		dw2 |= 0x10002;
	पूर्ण

	amdgpu_ring_ग_लिखो(ring, PACKET3(PACKET3_CONTEXT_CONTROL, 1));
	amdgpu_ring_ग_लिखो(ring, dw2);
	amdgpu_ring_ग_लिखो(ring, 0);
पूर्ण

/**
 * gfx_v7_0_ring_test_ib - basic ring IB test
 *
 * @ring: amdgpu_ring काष्ठाure holding ring inक्रमmation
 * @समयout: समयout value in jअगरfies, or MAX_SCHEDULE_TIMEOUT
 *
 * Allocate an IB and execute it on the gfx ring (CIK).
 * Provides a basic gfx ring test to verअगरy that IBs are working.
 * Returns 0 on success, error on failure.
 */
अटल पूर्णांक gfx_v7_0_ring_test_ib(काष्ठा amdgpu_ring *ring, दीर्घ समयout)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	काष्ठा amdgpu_ib ib;
	काष्ठा dma_fence *f = शून्य;
	uपूर्णांक32_t scratch;
	uपूर्णांक32_t पंचांगp = 0;
	दीर्घ r;

	r = amdgpu_gfx_scratch_get(adev, &scratch);
	अगर (r)
		वापस r;

	WREG32(scratch, 0xCAFEDEAD);
	स_रखो(&ib, 0, माप(ib));
	r = amdgpu_ib_get(adev, शून्य, 256,
					AMDGPU_IB_POOL_सूचीECT, &ib);
	अगर (r)
		जाओ err1;

	ib.ptr[0] = PACKET3(PACKET3_SET_UCONFIG_REG, 1);
	ib.ptr[1] = ((scratch - PACKET3_SET_UCONFIG_REG_START));
	ib.ptr[2] = 0xDEADBEEF;
	ib.length_dw = 3;

	r = amdgpu_ib_schedule(ring, 1, &ib, शून्य, &f);
	अगर (r)
		जाओ err2;

	r = dma_fence_रुको_समयout(f, false, समयout);
	अगर (r == 0) अणु
		r = -ETIMEDOUT;
		जाओ err2;
	पूर्ण अन्यथा अगर (r < 0) अणु
		जाओ err2;
	पूर्ण
	पंचांगp = RREG32(scratch);
	अगर (पंचांगp == 0xDEADBEEF)
		r = 0;
	अन्यथा
		r = -EINVAL;

err2:
	amdgpu_ib_मुक्त(adev, &ib, शून्य);
	dma_fence_put(f);
err1:
	amdgpu_gfx_scratch_मुक्त(adev, scratch);
	वापस r;
पूर्ण

/*
 * CP.
 * On CIK, gfx and compute now have independent command processors.
 *
 * GFX
 * Gfx consists of a single ring and can process both gfx jobs and
 * compute jobs.  The gfx CP consists of three microengines (ME):
 * PFP - Pre-Fetch Parser
 * ME - Micro Engine
 * CE - Constant Engine
 * The PFP and ME make up what is considered the Drawing Engine (DE).
 * The CE is an asynchronous engine used क्रम updating buffer desciptors
 * used by the DE so that they can be loaded पूर्णांकo cache in parallel
 * जबतक the DE is processing state update packets.
 *
 * Compute
 * The compute CP consists of two microengines (ME):
 * MEC1 - Compute MicroEngine 1
 * MEC2 - Compute MicroEngine 2
 * Each MEC supports 4 compute pipes and each pipe supports 8 queues.
 * The queues are exposed to userspace and are programmed directly
 * by the compute runसमय.
 */
/**
 * gfx_v7_0_cp_gfx_enable - enable/disable the gfx CP MEs
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @enable: enable or disable the MEs
 *
 * Halts or unhalts the gfx MEs.
 */
अटल व्योम gfx_v7_0_cp_gfx_enable(काष्ठा amdgpu_device *adev, bool enable)
अणु
	अगर (enable)
		WREG32(mmCP_ME_CNTL, 0);
	अन्यथा
		WREG32(mmCP_ME_CNTL, (CP_ME_CNTL__ME_HALT_MASK |
				      CP_ME_CNTL__PFP_HALT_MASK |
				      CP_ME_CNTL__CE_HALT_MASK));
	udelay(50);
पूर्ण

/**
 * gfx_v7_0_cp_gfx_load_microcode - load the gfx CP ME ucode
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Loads the gfx PFP, ME, and CE ucode.
 * Returns 0 क्रम success, -EINVAL अगर the ucode is not available.
 */
अटल पूर्णांक gfx_v7_0_cp_gfx_load_microcode(काष्ठा amdgpu_device *adev)
अणु
	स्थिर काष्ठा gfx_firmware_header_v1_0 *pfp_hdr;
	स्थिर काष्ठा gfx_firmware_header_v1_0 *ce_hdr;
	स्थिर काष्ठा gfx_firmware_header_v1_0 *me_hdr;
	स्थिर __le32 *fw_data;
	अचिन्हित i, fw_size;

	अगर (!adev->gfx.me_fw || !adev->gfx.pfp_fw || !adev->gfx.ce_fw)
		वापस -EINVAL;

	pfp_hdr = (स्थिर काष्ठा gfx_firmware_header_v1_0 *)adev->gfx.pfp_fw->data;
	ce_hdr = (स्थिर काष्ठा gfx_firmware_header_v1_0 *)adev->gfx.ce_fw->data;
	me_hdr = (स्थिर काष्ठा gfx_firmware_header_v1_0 *)adev->gfx.me_fw->data;

	amdgpu_ucode_prपूर्णांक_gfx_hdr(&pfp_hdr->header);
	amdgpu_ucode_prपूर्णांक_gfx_hdr(&ce_hdr->header);
	amdgpu_ucode_prपूर्णांक_gfx_hdr(&me_hdr->header);
	adev->gfx.pfp_fw_version = le32_to_cpu(pfp_hdr->header.ucode_version);
	adev->gfx.ce_fw_version = le32_to_cpu(ce_hdr->header.ucode_version);
	adev->gfx.me_fw_version = le32_to_cpu(me_hdr->header.ucode_version);
	adev->gfx.me_feature_version = le32_to_cpu(me_hdr->ucode_feature_version);
	adev->gfx.ce_feature_version = le32_to_cpu(ce_hdr->ucode_feature_version);
	adev->gfx.pfp_feature_version = le32_to_cpu(pfp_hdr->ucode_feature_version);

	gfx_v7_0_cp_gfx_enable(adev, false);

	/* PFP */
	fw_data = (स्थिर __le32 *)
		(adev->gfx.pfp_fw->data +
		 le32_to_cpu(pfp_hdr->header.ucode_array_offset_bytes));
	fw_size = le32_to_cpu(pfp_hdr->header.ucode_size_bytes) / 4;
	WREG32(mmCP_PFP_UCODE_ADDR, 0);
	क्रम (i = 0; i < fw_size; i++)
		WREG32(mmCP_PFP_UCODE_DATA, le32_to_cpup(fw_data++));
	WREG32(mmCP_PFP_UCODE_ADDR, adev->gfx.pfp_fw_version);

	/* CE */
	fw_data = (स्थिर __le32 *)
		(adev->gfx.ce_fw->data +
		 le32_to_cpu(ce_hdr->header.ucode_array_offset_bytes));
	fw_size = le32_to_cpu(ce_hdr->header.ucode_size_bytes) / 4;
	WREG32(mmCP_CE_UCODE_ADDR, 0);
	क्रम (i = 0; i < fw_size; i++)
		WREG32(mmCP_CE_UCODE_DATA, le32_to_cpup(fw_data++));
	WREG32(mmCP_CE_UCODE_ADDR, adev->gfx.ce_fw_version);

	/* ME */
	fw_data = (स्थिर __le32 *)
		(adev->gfx.me_fw->data +
		 le32_to_cpu(me_hdr->header.ucode_array_offset_bytes));
	fw_size = le32_to_cpu(me_hdr->header.ucode_size_bytes) / 4;
	WREG32(mmCP_ME_RAM_WADDR, 0);
	क्रम (i = 0; i < fw_size; i++)
		WREG32(mmCP_ME_RAM_DATA, le32_to_cpup(fw_data++));
	WREG32(mmCP_ME_RAM_WADDR, adev->gfx.me_fw_version);

	वापस 0;
पूर्ण

/**
 * gfx_v7_0_cp_gfx_start - start the gfx ring
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Enables the ring and loads the clear state context and other
 * packets required to init the ring.
 * Returns 0 क्रम success, error क्रम failure.
 */
अटल पूर्णांक gfx_v7_0_cp_gfx_start(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ring *ring = &adev->gfx.gfx_ring[0];
	स्थिर काष्ठा cs_section_def *sect = शून्य;
	स्थिर काष्ठा cs_extent_def *ext = शून्य;
	पूर्णांक r, i;

	/* init the CP */
	WREG32(mmCP_MAX_CONTEXT, adev->gfx.config.max_hw_contexts - 1);
	WREG32(mmCP_ENDIAN_SWAP, 0);
	WREG32(mmCP_DEVICE_ID, 1);

	gfx_v7_0_cp_gfx_enable(adev, true);

	r = amdgpu_ring_alloc(ring, gfx_v7_0_get_csb_size(adev) + 8);
	अगर (r) अणु
		DRM_ERROR("amdgpu: cp failed to lock ring (%d).\n", r);
		वापस r;
	पूर्ण

	/* init the CE partitions.  CE only used क्रम gfx on CIK */
	amdgpu_ring_ग_लिखो(ring, PACKET3(PACKET3_SET_BASE, 2));
	amdgpu_ring_ग_लिखो(ring, PACKET3_BASE_INDEX(CE_PARTITION_BASE));
	amdgpu_ring_ग_लिखो(ring, 0x8000);
	amdgpu_ring_ग_लिखो(ring, 0x8000);

	/* clear state buffer */
	amdgpu_ring_ग_लिखो(ring, PACKET3(PACKET3_PREAMBLE_CNTL, 0));
	amdgpu_ring_ग_लिखो(ring, PACKET3_PREAMBLE_BEGIN_CLEAR_STATE);

	amdgpu_ring_ग_लिखो(ring, PACKET3(PACKET3_CONTEXT_CONTROL, 1));
	amdgpu_ring_ग_लिखो(ring, 0x80000000);
	amdgpu_ring_ग_लिखो(ring, 0x80000000);

	क्रम (sect = adev->gfx.rlc.cs_data; sect->section != शून्य; ++sect) अणु
		क्रम (ext = sect->section; ext->extent != शून्य; ++ext) अणु
			अगर (sect->id == SECT_CONTEXT) अणु
				amdgpu_ring_ग_लिखो(ring,
						  PACKET3(PACKET3_SET_CONTEXT_REG, ext->reg_count));
				amdgpu_ring_ग_लिखो(ring, ext->reg_index - PACKET3_SET_CONTEXT_REG_START);
				क्रम (i = 0; i < ext->reg_count; i++)
					amdgpu_ring_ग_लिखो(ring, ext->extent[i]);
			पूर्ण
		पूर्ण
	पूर्ण

	amdgpu_ring_ग_लिखो(ring, PACKET3(PACKET3_SET_CONTEXT_REG, 2));
	amdgpu_ring_ग_लिखो(ring, mmPA_SC_RASTER_CONFIG - PACKET3_SET_CONTEXT_REG_START);
	amdgpu_ring_ग_लिखो(ring, adev->gfx.config.rb_config[0][0].raster_config);
	amdgpu_ring_ग_लिखो(ring, adev->gfx.config.rb_config[0][0].raster_config_1);

	amdgpu_ring_ग_लिखो(ring, PACKET3(PACKET3_PREAMBLE_CNTL, 0));
	amdgpu_ring_ग_लिखो(ring, PACKET3_PREAMBLE_END_CLEAR_STATE);

	amdgpu_ring_ग_लिखो(ring, PACKET3(PACKET3_CLEAR_STATE, 0));
	amdgpu_ring_ग_लिखो(ring, 0);

	amdgpu_ring_ग_लिखो(ring, PACKET3(PACKET3_SET_CONTEXT_REG, 2));
	amdgpu_ring_ग_लिखो(ring, 0x00000316);
	amdgpu_ring_ग_लिखो(ring, 0x0000000e); /* VGT_VERTEX_REUSE_BLOCK_CNTL */
	amdgpu_ring_ग_लिखो(ring, 0x00000010); /* VGT_OUT_DEALLOC_CNTL */

	amdgpu_ring_commit(ring);

	वापस 0;
पूर्ण

/**
 * gfx_v7_0_cp_gfx_resume - setup the gfx ring buffer रेजिस्टरs
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Program the location and size of the gfx ring buffer
 * and test it to make sure it's working.
 * Returns 0 क्रम success, error क्रम failure.
 */
अटल पूर्णांक gfx_v7_0_cp_gfx_resume(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ring *ring;
	u32 पंचांगp;
	u32 rb_bufsz;
	u64 rb_addr, rptr_addr;
	पूर्णांक r;

	WREG32(mmCP_SEM_WAIT_TIMER, 0x0);
	अगर (adev->asic_type != CHIP_HAWAII)
		WREG32(mmCP_SEM_INCOMPLETE_TIMER_CNTL, 0x0);

	/* Set the ग_लिखो poपूर्णांकer delay */
	WREG32(mmCP_RB_WPTR_DELAY, 0);

	/* set the RB to use vmid 0 */
	WREG32(mmCP_RB_VMID, 0);

	WREG32(mmSCRATCH_ADDR, 0);

	/* ring 0 - compute and gfx */
	/* Set ring buffer size */
	ring = &adev->gfx.gfx_ring[0];
	rb_bufsz = order_base_2(ring->ring_size / 8);
	पंचांगp = (order_base_2(AMDGPU_GPU_PAGE_SIZE/8) << 8) | rb_bufsz;
#अगर_घोषित __BIG_ENDIAN
	पंचांगp |= 2 << CP_RB0_CNTL__BUF_SWAP__SHIFT;
#पूर्ण_अगर
	WREG32(mmCP_RB0_CNTL, पंचांगp);

	/* Initialize the ring buffer's पढ़ो and ग_लिखो poपूर्णांकers */
	WREG32(mmCP_RB0_CNTL, पंचांगp | CP_RB0_CNTL__RB_RPTR_WR_ENA_MASK);
	ring->wptr = 0;
	WREG32(mmCP_RB0_WPTR, lower_32_bits(ring->wptr));

	/* set the wb address whether it's enabled or not */
	rptr_addr = adev->wb.gpu_addr + (ring->rptr_offs * 4);
	WREG32(mmCP_RB0_RPTR_ADDR, lower_32_bits(rptr_addr));
	WREG32(mmCP_RB0_RPTR_ADDR_HI, upper_32_bits(rptr_addr) & 0xFF);

	/* scratch रेजिस्टर shaकरोwing is no दीर्घer supported */
	WREG32(mmSCRATCH_UMSK, 0);

	mdelay(1);
	WREG32(mmCP_RB0_CNTL, पंचांगp);

	rb_addr = ring->gpu_addr >> 8;
	WREG32(mmCP_RB0_BASE, rb_addr);
	WREG32(mmCP_RB0_BASE_HI, upper_32_bits(rb_addr));

	/* start the ring */
	gfx_v7_0_cp_gfx_start(adev);
	r = amdgpu_ring_test_helper(ring);
	अगर (r)
		वापस r;

	वापस 0;
पूर्ण

अटल u64 gfx_v7_0_ring_get_rptr(काष्ठा amdgpu_ring *ring)
अणु
	वापस ring->adev->wb.wb[ring->rptr_offs];
पूर्ण

अटल u64 gfx_v7_0_ring_get_wptr_gfx(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	वापस RREG32(mmCP_RB0_WPTR);
पूर्ण

अटल व्योम gfx_v7_0_ring_set_wptr_gfx(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	WREG32(mmCP_RB0_WPTR, lower_32_bits(ring->wptr));
	(व्योम)RREG32(mmCP_RB0_WPTR);
पूर्ण

अटल u64 gfx_v7_0_ring_get_wptr_compute(काष्ठा amdgpu_ring *ring)
अणु
	/* XXX check अगर swapping is necessary on BE */
	वापस ring->adev->wb.wb[ring->wptr_offs];
पूर्ण

अटल व्योम gfx_v7_0_ring_set_wptr_compute(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	/* XXX check अगर swapping is necessary on BE */
	adev->wb.wb[ring->wptr_offs] = lower_32_bits(ring->wptr);
	WDOORBELL32(ring->करोorbell_index, lower_32_bits(ring->wptr));
पूर्ण

/**
 * gfx_v7_0_cp_compute_enable - enable/disable the compute CP MEs
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @enable: enable or disable the MEs
 *
 * Halts or unhalts the compute MEs.
 */
अटल व्योम gfx_v7_0_cp_compute_enable(काष्ठा amdgpu_device *adev, bool enable)
अणु
	अगर (enable)
		WREG32(mmCP_MEC_CNTL, 0);
	अन्यथा
		WREG32(mmCP_MEC_CNTL, (CP_MEC_CNTL__MEC_ME1_HALT_MASK |
				       CP_MEC_CNTL__MEC_ME2_HALT_MASK));
	udelay(50);
पूर्ण

/**
 * gfx_v7_0_cp_compute_load_microcode - load the compute CP ME ucode
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Loads the compute MEC1&2 ucode.
 * Returns 0 क्रम success, -EINVAL अगर the ucode is not available.
 */
अटल पूर्णांक gfx_v7_0_cp_compute_load_microcode(काष्ठा amdgpu_device *adev)
अणु
	स्थिर काष्ठा gfx_firmware_header_v1_0 *mec_hdr;
	स्थिर __le32 *fw_data;
	अचिन्हित i, fw_size;

	अगर (!adev->gfx.mec_fw)
		वापस -EINVAL;

	mec_hdr = (स्थिर काष्ठा gfx_firmware_header_v1_0 *)adev->gfx.mec_fw->data;
	amdgpu_ucode_prपूर्णांक_gfx_hdr(&mec_hdr->header);
	adev->gfx.mec_fw_version = le32_to_cpu(mec_hdr->header.ucode_version);
	adev->gfx.mec_feature_version = le32_to_cpu(
					mec_hdr->ucode_feature_version);

	gfx_v7_0_cp_compute_enable(adev, false);

	/* MEC1 */
	fw_data = (स्थिर __le32 *)
		(adev->gfx.mec_fw->data +
		 le32_to_cpu(mec_hdr->header.ucode_array_offset_bytes));
	fw_size = le32_to_cpu(mec_hdr->header.ucode_size_bytes) / 4;
	WREG32(mmCP_MEC_ME1_UCODE_ADDR, 0);
	क्रम (i = 0; i < fw_size; i++)
		WREG32(mmCP_MEC_ME1_UCODE_DATA, le32_to_cpup(fw_data++));
	WREG32(mmCP_MEC_ME1_UCODE_ADDR, 0);

	अगर (adev->asic_type == CHIP_KAVERI) अणु
		स्थिर काष्ठा gfx_firmware_header_v1_0 *mec2_hdr;

		अगर (!adev->gfx.mec2_fw)
			वापस -EINVAL;

		mec2_hdr = (स्थिर काष्ठा gfx_firmware_header_v1_0 *)adev->gfx.mec2_fw->data;
		amdgpu_ucode_prपूर्णांक_gfx_hdr(&mec2_hdr->header);
		adev->gfx.mec2_fw_version = le32_to_cpu(mec2_hdr->header.ucode_version);
		adev->gfx.mec2_feature_version = le32_to_cpu(
				mec2_hdr->ucode_feature_version);

		/* MEC2 */
		fw_data = (स्थिर __le32 *)
			(adev->gfx.mec2_fw->data +
			 le32_to_cpu(mec2_hdr->header.ucode_array_offset_bytes));
		fw_size = le32_to_cpu(mec2_hdr->header.ucode_size_bytes) / 4;
		WREG32(mmCP_MEC_ME2_UCODE_ADDR, 0);
		क्रम (i = 0; i < fw_size; i++)
			WREG32(mmCP_MEC_ME2_UCODE_DATA, le32_to_cpup(fw_data++));
		WREG32(mmCP_MEC_ME2_UCODE_ADDR, 0);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * gfx_v7_0_cp_compute_fini - stop the compute queues
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Stop the compute queues and tear करोwn the driver queue
 * info.
 */
अटल व्योम gfx_v7_0_cp_compute_fini(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adev->gfx.num_compute_rings; i++) अणु
		काष्ठा amdgpu_ring *ring = &adev->gfx.compute_ring[i];

		amdgpu_bo_मुक्त_kernel(&ring->mqd_obj, शून्य, शून्य);
	पूर्ण
पूर्ण

अटल व्योम gfx_v7_0_mec_fini(काष्ठा amdgpu_device *adev)
अणु
	amdgpu_bo_मुक्त_kernel(&adev->gfx.mec.hpd_eop_obj, शून्य, शून्य);
पूर्ण

अटल पूर्णांक gfx_v7_0_mec_init(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक r;
	u32 *hpd;
	माप_प्रकार mec_hpd_size;

	biपंचांगap_zero(adev->gfx.mec.queue_biपंचांगap, AMDGPU_MAX_COMPUTE_QUEUES);

	/* take ownership of the relevant compute queues */
	amdgpu_gfx_compute_queue_acquire(adev);

	/* allocate space क्रम ALL pipes (even the ones we करोn't own) */
	mec_hpd_size = adev->gfx.mec.num_mec * adev->gfx.mec.num_pipe_per_mec
		* GFX7_MEC_HPD_SIZE * 2;

	r = amdgpu_bo_create_reserved(adev, mec_hpd_size, PAGE_SIZE,
				      AMDGPU_GEM_DOMAIN_VRAM,
				      &adev->gfx.mec.hpd_eop_obj,
				      &adev->gfx.mec.hpd_eop_gpu_addr,
				      (व्योम **)&hpd);
	अगर (r) अणु
		dev_warn(adev->dev, "(%d) create, pin or map of HDP EOP bo failed\n", r);
		gfx_v7_0_mec_fini(adev);
		वापस r;
	पूर्ण

	/* clear memory.  Not sure अगर this is required or not */
	स_रखो(hpd, 0, mec_hpd_size);

	amdgpu_bo_kunmap(adev->gfx.mec.hpd_eop_obj);
	amdgpu_bo_unreserve(adev->gfx.mec.hpd_eop_obj);

	वापस 0;
पूर्ण

काष्ठा hqd_रेजिस्टरs
अणु
	u32 cp_mqd_base_addr;
	u32 cp_mqd_base_addr_hi;
	u32 cp_hqd_active;
	u32 cp_hqd_vmid;
	u32 cp_hqd_persistent_state;
	u32 cp_hqd_pipe_priority;
	u32 cp_hqd_queue_priority;
	u32 cp_hqd_quantum;
	u32 cp_hqd_pq_base;
	u32 cp_hqd_pq_base_hi;
	u32 cp_hqd_pq_rptr;
	u32 cp_hqd_pq_rptr_report_addr;
	u32 cp_hqd_pq_rptr_report_addr_hi;
	u32 cp_hqd_pq_wptr_poll_addr;
	u32 cp_hqd_pq_wptr_poll_addr_hi;
	u32 cp_hqd_pq_करोorbell_control;
	u32 cp_hqd_pq_wptr;
	u32 cp_hqd_pq_control;
	u32 cp_hqd_ib_base_addr;
	u32 cp_hqd_ib_base_addr_hi;
	u32 cp_hqd_ib_rptr;
	u32 cp_hqd_ib_control;
	u32 cp_hqd_iq_समयr;
	u32 cp_hqd_iq_rptr;
	u32 cp_hqd_dequeue_request;
	u32 cp_hqd_dma_offload;
	u32 cp_hqd_sema_cmd;
	u32 cp_hqd_msg_type;
	u32 cp_hqd_atomic0_preop_lo;
	u32 cp_hqd_atomic0_preop_hi;
	u32 cp_hqd_atomic1_preop_lo;
	u32 cp_hqd_atomic1_preop_hi;
	u32 cp_hqd_hq_scheduler0;
	u32 cp_hqd_hq_scheduler1;
	u32 cp_mqd_control;
पूर्ण;

अटल व्योम gfx_v7_0_compute_pipe_init(काष्ठा amdgpu_device *adev,
				       पूर्णांक mec, पूर्णांक pipe)
अणु
	u64 eop_gpu_addr;
	u32 पंचांगp;
	माप_प्रकार eop_offset = (mec * adev->gfx.mec.num_pipe_per_mec + pipe)
			    * GFX7_MEC_HPD_SIZE * 2;

	mutex_lock(&adev->srbm_mutex);
	eop_gpu_addr = adev->gfx.mec.hpd_eop_gpu_addr + eop_offset;

	cik_srbm_select(adev, mec + 1, pipe, 0, 0);

	/* ग_लिखो the EOP addr */
	WREG32(mmCP_HPD_EOP_BASE_ADDR, eop_gpu_addr >> 8);
	WREG32(mmCP_HPD_EOP_BASE_ADDR_HI, upper_32_bits(eop_gpu_addr) >> 8);

	/* set the VMID asचिन्हित */
	WREG32(mmCP_HPD_EOP_VMID, 0);

	/* set the EOP size, रेजिस्टर value is 2^(EOP_SIZE+1) dwords */
	पंचांगp = RREG32(mmCP_HPD_EOP_CONTROL);
	पंचांगp &= ~CP_HPD_EOP_CONTROL__EOP_SIZE_MASK;
	पंचांगp |= order_base_2(GFX7_MEC_HPD_SIZE / 8);
	WREG32(mmCP_HPD_EOP_CONTROL, पंचांगp);

	cik_srbm_select(adev, 0, 0, 0, 0);
	mutex_unlock(&adev->srbm_mutex);
पूर्ण

अटल पूर्णांक gfx_v7_0_mqd_deactivate(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i;

	/* disable the queue अगर it's active */
	अगर (RREG32(mmCP_HQD_ACTIVE) & 1) अणु
		WREG32(mmCP_HQD_DEQUEUE_REQUEST, 1);
		क्रम (i = 0; i < adev->usec_समयout; i++) अणु
			अगर (!(RREG32(mmCP_HQD_ACTIVE) & 1))
				अवरोध;
			udelay(1);
		पूर्ण

		अगर (i == adev->usec_समयout)
			वापस -ETIMEDOUT;

		WREG32(mmCP_HQD_DEQUEUE_REQUEST, 0);
		WREG32(mmCP_HQD_PQ_RPTR, 0);
		WREG32(mmCP_HQD_PQ_WPTR, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम gfx_v7_0_mqd_init(काष्ठा amdgpu_device *adev,
			     काष्ठा cik_mqd *mqd,
			     uपूर्णांक64_t mqd_gpu_addr,
			     काष्ठा amdgpu_ring *ring)
अणु
	u64 hqd_gpu_addr;
	u64 wb_gpu_addr;

	/* init the mqd काष्ठा */
	स_रखो(mqd, 0, माप(काष्ठा cik_mqd));

	mqd->header = 0xC0310800;
	mqd->compute_अटल_thपढ़ो_mgmt_se0 = 0xffffffff;
	mqd->compute_अटल_thपढ़ो_mgmt_se1 = 0xffffffff;
	mqd->compute_अटल_thपढ़ो_mgmt_se2 = 0xffffffff;
	mqd->compute_अटल_thपढ़ो_mgmt_se3 = 0xffffffff;

	/* enable करोorbell? */
	mqd->cp_hqd_pq_करोorbell_control =
		RREG32(mmCP_HQD_PQ_DOORBELL_CONTROL);
	अगर (ring->use_करोorbell)
		mqd->cp_hqd_pq_करोorbell_control |= CP_HQD_PQ_DOORBELL_CONTROL__DOORBELL_EN_MASK;
	अन्यथा
		mqd->cp_hqd_pq_करोorbell_control &= ~CP_HQD_PQ_DOORBELL_CONTROL__DOORBELL_EN_MASK;

	/* set the poपूर्णांकer to the MQD */
	mqd->cp_mqd_base_addr_lo = mqd_gpu_addr & 0xfffffffc;
	mqd->cp_mqd_base_addr_hi = upper_32_bits(mqd_gpu_addr);

	/* set MQD vmid to 0 */
	mqd->cp_mqd_control = RREG32(mmCP_MQD_CONTROL);
	mqd->cp_mqd_control &= ~CP_MQD_CONTROL__VMID_MASK;

	/* set the poपूर्णांकer to the HQD, this is similar CP_RB0_BASE/_HI */
	hqd_gpu_addr = ring->gpu_addr >> 8;
	mqd->cp_hqd_pq_base_lo = hqd_gpu_addr;
	mqd->cp_hqd_pq_base_hi = upper_32_bits(hqd_gpu_addr);

	/* set up the HQD, this is similar to CP_RB0_CNTL */
	mqd->cp_hqd_pq_control = RREG32(mmCP_HQD_PQ_CONTROL);
	mqd->cp_hqd_pq_control &=
		~(CP_HQD_PQ_CONTROL__QUEUE_SIZE_MASK |
				CP_HQD_PQ_CONTROL__RPTR_BLOCK_SIZE_MASK);

	mqd->cp_hqd_pq_control |=
		order_base_2(ring->ring_size / 8);
	mqd->cp_hqd_pq_control |=
		(order_base_2(AMDGPU_GPU_PAGE_SIZE/8) << 8);
#अगर_घोषित __BIG_ENDIAN
	mqd->cp_hqd_pq_control |=
		2 << CP_HQD_PQ_CONTROL__ENDIAN_SWAP__SHIFT;
#पूर्ण_अगर
	mqd->cp_hqd_pq_control &=
		~(CP_HQD_PQ_CONTROL__UNORD_DISPATCH_MASK |
				CP_HQD_PQ_CONTROL__ROQ_PQ_IB_FLIP_MASK |
				CP_HQD_PQ_CONTROL__PQ_VOLATILE_MASK);
	mqd->cp_hqd_pq_control |=
		CP_HQD_PQ_CONTROL__PRIV_STATE_MASK |
		CP_HQD_PQ_CONTROL__KMD_QUEUE_MASK; /* assuming kernel queue control */

	/* only used अगर CP_PQ_WPTR_POLL_CNTL.CP_PQ_WPTR_POLL_CNTL__EN_MASK=1 */
	wb_gpu_addr = adev->wb.gpu_addr + (ring->wptr_offs * 4);
	mqd->cp_hqd_pq_wptr_poll_addr_lo = wb_gpu_addr & 0xfffffffc;
	mqd->cp_hqd_pq_wptr_poll_addr_hi = upper_32_bits(wb_gpu_addr) & 0xffff;

	/* set the wb address whether it's enabled or not */
	wb_gpu_addr = adev->wb.gpu_addr + (ring->rptr_offs * 4);
	mqd->cp_hqd_pq_rptr_report_addr_lo = wb_gpu_addr & 0xfffffffc;
	mqd->cp_hqd_pq_rptr_report_addr_hi =
		upper_32_bits(wb_gpu_addr) & 0xffff;

	/* enable the करोorbell अगर requested */
	अगर (ring->use_करोorbell) अणु
		mqd->cp_hqd_pq_करोorbell_control =
			RREG32(mmCP_HQD_PQ_DOORBELL_CONTROL);
		mqd->cp_hqd_pq_करोorbell_control &=
			~CP_HQD_PQ_DOORBELL_CONTROL__DOORBELL_OFFSET_MASK;
		mqd->cp_hqd_pq_करोorbell_control |=
			(ring->करोorbell_index <<
			 CP_HQD_PQ_DOORBELL_CONTROL__DOORBELL_OFFSET__SHIFT);
		mqd->cp_hqd_pq_करोorbell_control |=
			CP_HQD_PQ_DOORBELL_CONTROL__DOORBELL_EN_MASK;
		mqd->cp_hqd_pq_करोorbell_control &=
			~(CP_HQD_PQ_DOORBELL_CONTROL__DOORBELL_SOURCE_MASK |
					CP_HQD_PQ_DOORBELL_CONTROL__DOORBELL_HIT_MASK);

	पूर्ण अन्यथा अणु
		mqd->cp_hqd_pq_करोorbell_control = 0;
	पूर्ण

	/* पढ़ो and ग_लिखो poपूर्णांकers, similar to CP_RB0_WPTR/_RPTR */
	ring->wptr = 0;
	mqd->cp_hqd_pq_wptr = lower_32_bits(ring->wptr);
	mqd->cp_hqd_pq_rptr = RREG32(mmCP_HQD_PQ_RPTR);

	/* set the vmid क्रम the queue */
	mqd->cp_hqd_vmid = 0;

	/* शेषs */
	mqd->cp_hqd_ib_control = RREG32(mmCP_HQD_IB_CONTROL);
	mqd->cp_hqd_ib_base_addr_lo = RREG32(mmCP_HQD_IB_BASE_ADDR);
	mqd->cp_hqd_ib_base_addr_hi = RREG32(mmCP_HQD_IB_BASE_ADDR_HI);
	mqd->cp_hqd_ib_rptr = RREG32(mmCP_HQD_IB_RPTR);
	mqd->cp_hqd_persistent_state = RREG32(mmCP_HQD_PERSISTENT_STATE);
	mqd->cp_hqd_sema_cmd = RREG32(mmCP_HQD_SEMA_CMD);
	mqd->cp_hqd_msg_type = RREG32(mmCP_HQD_MSG_TYPE);
	mqd->cp_hqd_atomic0_preop_lo = RREG32(mmCP_HQD_ATOMIC0_PREOP_LO);
	mqd->cp_hqd_atomic0_preop_hi = RREG32(mmCP_HQD_ATOMIC0_PREOP_HI);
	mqd->cp_hqd_atomic1_preop_lo = RREG32(mmCP_HQD_ATOMIC1_PREOP_LO);
	mqd->cp_hqd_atomic1_preop_hi = RREG32(mmCP_HQD_ATOMIC1_PREOP_HI);
	mqd->cp_hqd_pq_rptr = RREG32(mmCP_HQD_PQ_RPTR);
	mqd->cp_hqd_quantum = RREG32(mmCP_HQD_QUANTUM);
	mqd->cp_hqd_pipe_priority = RREG32(mmCP_HQD_PIPE_PRIORITY);
	mqd->cp_hqd_queue_priority = RREG32(mmCP_HQD_QUEUE_PRIORITY);
	mqd->cp_hqd_iq_rptr = RREG32(mmCP_HQD_IQ_RPTR);

	/* activate the queue */
	mqd->cp_hqd_active = 1;
पूर्ण

अटल पूर्णांक gfx_v7_0_mqd_commit(काष्ठा amdgpu_device *adev, काष्ठा cik_mqd *mqd)
अणु
	uपूर्णांक32_t पंचांगp;
	uपूर्णांक32_t mqd_reg;
	uपूर्णांक32_t *mqd_data;

	/* HQD रेजिस्टरs extend from mmCP_MQD_BASE_ADDR to mmCP_MQD_CONTROL */
	mqd_data = &mqd->cp_mqd_base_addr_lo;

	/* disable wptr polling */
	पंचांगp = RREG32(mmCP_PQ_WPTR_POLL_CNTL);
	पंचांगp = REG_SET_FIELD(पंचांगp, CP_PQ_WPTR_POLL_CNTL, EN, 0);
	WREG32(mmCP_PQ_WPTR_POLL_CNTL, पंचांगp);

	/* program all HQD रेजिस्टरs */
	क्रम (mqd_reg = mmCP_HQD_VMID; mqd_reg <= mmCP_MQD_CONTROL; mqd_reg++)
		WREG32(mqd_reg, mqd_data[mqd_reg - mmCP_MQD_BASE_ADDR]);

	/* activate the HQD */
	क्रम (mqd_reg = mmCP_MQD_BASE_ADDR; mqd_reg <= mmCP_HQD_ACTIVE; mqd_reg++)
		WREG32(mqd_reg, mqd_data[mqd_reg - mmCP_MQD_BASE_ADDR]);

	वापस 0;
पूर्ण

अटल पूर्णांक gfx_v7_0_compute_queue_init(काष्ठा amdgpu_device *adev, पूर्णांक ring_id)
अणु
	पूर्णांक r;
	u64 mqd_gpu_addr;
	काष्ठा cik_mqd *mqd;
	काष्ठा amdgpu_ring *ring = &adev->gfx.compute_ring[ring_id];

	r = amdgpu_bo_create_reserved(adev, माप(काष्ठा cik_mqd), PAGE_SIZE,
				      AMDGPU_GEM_DOMAIN_GTT, &ring->mqd_obj,
				      &mqd_gpu_addr, (व्योम **)&mqd);
	अगर (r) अणु
		dev_warn(adev->dev, "(%d) create MQD bo failed\n", r);
		वापस r;
	पूर्ण

	mutex_lock(&adev->srbm_mutex);
	cik_srbm_select(adev, ring->me, ring->pipe, ring->queue, 0);

	gfx_v7_0_mqd_init(adev, mqd, mqd_gpu_addr, ring);
	gfx_v7_0_mqd_deactivate(adev);
	gfx_v7_0_mqd_commit(adev, mqd);

	cik_srbm_select(adev, 0, 0, 0, 0);
	mutex_unlock(&adev->srbm_mutex);

	amdgpu_bo_kunmap(ring->mqd_obj);
	amdgpu_bo_unreserve(ring->mqd_obj);
	वापस 0;
पूर्ण

/**
 * gfx_v7_0_cp_compute_resume - setup the compute queue रेजिस्टरs
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Program the compute queues and test them to make sure they
 * are working.
 * Returns 0 क्रम success, error क्रम failure.
 */
अटल पूर्णांक gfx_v7_0_cp_compute_resume(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक r, i, j;
	u32 पंचांगp;
	काष्ठा amdgpu_ring *ring;

	/* fix up chicken bits */
	पंचांगp = RREG32(mmCP_CPF_DEBUG);
	पंचांगp |= (1 << 23);
	WREG32(mmCP_CPF_DEBUG, पंचांगp);

	/* init all pipes (even the ones we करोn't own) */
	क्रम (i = 0; i < adev->gfx.mec.num_mec; i++)
		क्रम (j = 0; j < adev->gfx.mec.num_pipe_per_mec; j++)
			gfx_v7_0_compute_pipe_init(adev, i, j);

	/* init the queues */
	क्रम (i = 0; i < adev->gfx.num_compute_rings; i++) अणु
		r = gfx_v7_0_compute_queue_init(adev, i);
		अगर (r) अणु
			gfx_v7_0_cp_compute_fini(adev);
			वापस r;
		पूर्ण
	पूर्ण

	gfx_v7_0_cp_compute_enable(adev, true);

	क्रम (i = 0; i < adev->gfx.num_compute_rings; i++) अणु
		ring = &adev->gfx.compute_ring[i];
		amdgpu_ring_test_helper(ring);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम gfx_v7_0_cp_enable(काष्ठा amdgpu_device *adev, bool enable)
अणु
	gfx_v7_0_cp_gfx_enable(adev, enable);
	gfx_v7_0_cp_compute_enable(adev, enable);
पूर्ण

अटल पूर्णांक gfx_v7_0_cp_load_microcode(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक r;

	r = gfx_v7_0_cp_gfx_load_microcode(adev);
	अगर (r)
		वापस r;
	r = gfx_v7_0_cp_compute_load_microcode(adev);
	अगर (r)
		वापस r;

	वापस 0;
पूर्ण

अटल व्योम gfx_v7_0_enable_gui_idle_पूर्णांकerrupt(काष्ठा amdgpu_device *adev,
					       bool enable)
अणु
	u32 पंचांगp = RREG32(mmCP_INT_CNTL_RING0);

	अगर (enable)
		पंचांगp |= (CP_INT_CNTL_RING0__CNTX_BUSY_INT_ENABLE_MASK |
				CP_INT_CNTL_RING0__CNTX_EMPTY_INT_ENABLE_MASK);
	अन्यथा
		पंचांगp &= ~(CP_INT_CNTL_RING0__CNTX_BUSY_INT_ENABLE_MASK |
				CP_INT_CNTL_RING0__CNTX_EMPTY_INT_ENABLE_MASK);
	WREG32(mmCP_INT_CNTL_RING0, पंचांगp);
पूर्ण

अटल पूर्णांक gfx_v7_0_cp_resume(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक r;

	gfx_v7_0_enable_gui_idle_पूर्णांकerrupt(adev, false);

	r = gfx_v7_0_cp_load_microcode(adev);
	अगर (r)
		वापस r;

	r = gfx_v7_0_cp_gfx_resume(adev);
	अगर (r)
		वापस r;
	r = gfx_v7_0_cp_compute_resume(adev);
	अगर (r)
		वापस r;

	gfx_v7_0_enable_gui_idle_पूर्णांकerrupt(adev, true);

	वापस 0;
पूर्ण

/**
 * gfx_v7_0_ring_emit_vm_flush - cik vm flush using the CP
 *
 * @ring: the ring to emit the commands to
 *
 * Sync the command pipeline with the PFP. E.g. रुको क्रम everything
 * to be completed.
 */
अटल व्योम gfx_v7_0_ring_emit_pipeline_sync(काष्ठा amdgpu_ring *ring)
अणु
	पूर्णांक usepfp = (ring->funcs->type == AMDGPU_RING_TYPE_GFX);
	uपूर्णांक32_t seq = ring->fence_drv.sync_seq;
	uपूर्णांक64_t addr = ring->fence_drv.gpu_addr;

	amdgpu_ring_ग_लिखो(ring, PACKET3(PACKET3_WAIT_REG_MEM, 5));
	amdgpu_ring_ग_लिखो(ring, (WAIT_REG_MEM_MEM_SPACE(1) | /* memory */
				 WAIT_REG_MEM_FUNCTION(3) | /* equal */
				 WAIT_REG_MEM_ENGINE(usepfp)));   /* pfp or me */
	amdgpu_ring_ग_लिखो(ring, addr & 0xfffffffc);
	amdgpu_ring_ग_लिखो(ring, upper_32_bits(addr) & 0xffffffff);
	amdgpu_ring_ग_लिखो(ring, seq);
	amdgpu_ring_ग_लिखो(ring, 0xffffffff);
	amdgpu_ring_ग_लिखो(ring, 4); /* poll पूर्णांकerval */

	अगर (usepfp) अणु
		/* sync CE with ME to prevent CE fetch CEIB beक्रमe context चयन करोne */
		amdgpu_ring_ग_लिखो(ring, PACKET3(PACKET3_SWITCH_BUFFER, 0));
		amdgpu_ring_ग_लिखो(ring, 0);
		amdgpu_ring_ग_लिखो(ring, PACKET3(PACKET3_SWITCH_BUFFER, 0));
		amdgpu_ring_ग_लिखो(ring, 0);
	पूर्ण
पूर्ण

/*
 * vm
 * VMID 0 is the physical GPU addresses as used by the kernel.
 * VMIDs 1-15 are used क्रम userspace clients and are handled
 * by the amdgpu vm/hsa code.
 */
/**
 * gfx_v7_0_ring_emit_vm_flush - cik vm flush using the CP
 *
 * @ring: amdgpu_ring poपूर्णांकer
 * @vmid: vmid number to use
 * @pd_addr: address
 *
 * Update the page table base and flush the VM TLB
 * using the CP (CIK).
 */
अटल व्योम gfx_v7_0_ring_emit_vm_flush(काष्ठा amdgpu_ring *ring,
					अचिन्हित vmid, uपूर्णांक64_t pd_addr)
अणु
	पूर्णांक usepfp = (ring->funcs->type == AMDGPU_RING_TYPE_GFX);

	amdgpu_gmc_emit_flush_gpu_tlb(ring, vmid, pd_addr);

	/* रुको क्रम the invalidate to complete */
	amdgpu_ring_ग_लिखो(ring, PACKET3(PACKET3_WAIT_REG_MEM, 5));
	amdgpu_ring_ग_लिखो(ring, (WAIT_REG_MEM_OPERATION(0) | /* रुको */
				 WAIT_REG_MEM_FUNCTION(0) |  /* always */
				 WAIT_REG_MEM_ENGINE(0))); /* me */
	amdgpu_ring_ग_लिखो(ring, mmVM_INVALIDATE_REQUEST);
	amdgpu_ring_ग_लिखो(ring, 0);
	amdgpu_ring_ग_लिखो(ring, 0); /* ref */
	amdgpu_ring_ग_लिखो(ring, 0); /* mask */
	amdgpu_ring_ग_लिखो(ring, 0x20); /* poll पूर्णांकerval */

	/* compute करोesn't have PFP */
	अगर (usepfp) अणु
		/* sync PFP to ME, otherwise we might get invalid PFP पढ़ोs */
		amdgpu_ring_ग_लिखो(ring, PACKET3(PACKET3_PFP_SYNC_ME, 0));
		amdgpu_ring_ग_लिखो(ring, 0x0);

		/* synce CE with ME to prevent CE fetch CEIB beक्रमe context चयन करोne */
		amdgpu_ring_ग_लिखो(ring, PACKET3(PACKET3_SWITCH_BUFFER, 0));
		amdgpu_ring_ग_लिखो(ring, 0);
		amdgpu_ring_ग_लिखो(ring, PACKET3(PACKET3_SWITCH_BUFFER, 0));
		amdgpu_ring_ग_लिखो(ring, 0);
	पूर्ण
पूर्ण

अटल व्योम gfx_v7_0_ring_emit_wreg(काष्ठा amdgpu_ring *ring,
				    uपूर्णांक32_t reg, uपूर्णांक32_t val)
अणु
	पूर्णांक usepfp = (ring->funcs->type == AMDGPU_RING_TYPE_GFX);

	amdgpu_ring_ग_लिखो(ring, PACKET3(PACKET3_WRITE_DATA, 3));
	amdgpu_ring_ग_लिखो(ring, (WRITE_DATA_ENGINE_SEL(usepfp) |
				 WRITE_DATA_DST_SEL(0)));
	amdgpu_ring_ग_लिखो(ring, reg);
	amdgpu_ring_ग_लिखो(ring, 0);
	amdgpu_ring_ग_लिखो(ring, val);
पूर्ण

/*
 * RLC
 * The RLC is a multi-purpose microengine that handles a
 * variety of functions.
 */
अटल पूर्णांक gfx_v7_0_rlc_init(काष्ठा amdgpu_device *adev)
अणु
	स्थिर u32 *src_ptr;
	u32 dws;
	स्थिर काष्ठा cs_section_def *cs_data;
	पूर्णांक r;

	/* allocate rlc buffers */
	अगर (adev->flags & AMD_IS_APU) अणु
		अगर (adev->asic_type == CHIP_KAVERI) अणु
			adev->gfx.rlc.reg_list = spectre_rlc_save_restore_रेजिस्टर_list;
			adev->gfx.rlc.reg_list_size =
				(u32)ARRAY_SIZE(spectre_rlc_save_restore_रेजिस्टर_list);
		पूर्ण अन्यथा अणु
			adev->gfx.rlc.reg_list = kalindi_rlc_save_restore_रेजिस्टर_list;
			adev->gfx.rlc.reg_list_size =
				(u32)ARRAY_SIZE(kalindi_rlc_save_restore_रेजिस्टर_list);
		पूर्ण
	पूर्ण
	adev->gfx.rlc.cs_data = ci_cs_data;
	adev->gfx.rlc.cp_table_size = ALIGN(CP_ME_TABLE_SIZE * 5 * 4, 2048); /* CP JT */
	adev->gfx.rlc.cp_table_size += 64 * 1024; /* GDS */

	src_ptr = adev->gfx.rlc.reg_list;
	dws = adev->gfx.rlc.reg_list_size;
	dws += (5 * 16) + 48 + 48 + 64;

	cs_data = adev->gfx.rlc.cs_data;

	अगर (src_ptr) अणु
		/* init save restore block */
		r = amdgpu_gfx_rlc_init_sr(adev, dws);
		अगर (r)
			वापस r;
	पूर्ण

	अगर (cs_data) अणु
		/* init clear state block */
		r = amdgpu_gfx_rlc_init_csb(adev);
		अगर (r)
			वापस r;
	पूर्ण

	अगर (adev->gfx.rlc.cp_table_size) अणु
		r = amdgpu_gfx_rlc_init_cpt(adev);
		अगर (r)
			वापस r;
	पूर्ण

	/* init spm vmid with 0xf */
	अगर (adev->gfx.rlc.funcs->update_spm_vmid)
		adev->gfx.rlc.funcs->update_spm_vmid(adev, 0xf);

	वापस 0;
पूर्ण

अटल व्योम gfx_v7_0_enable_lbpw(काष्ठा amdgpu_device *adev, bool enable)
अणु
	u32 पंचांगp;

	पंचांगp = RREG32(mmRLC_LB_CNTL);
	अगर (enable)
		पंचांगp |= RLC_LB_CNTL__LOAD_BALANCE_ENABLE_MASK;
	अन्यथा
		पंचांगp &= ~RLC_LB_CNTL__LOAD_BALANCE_ENABLE_MASK;
	WREG32(mmRLC_LB_CNTL, पंचांगp);
पूर्ण

अटल व्योम gfx_v7_0_रुको_क्रम_rlc_serdes(काष्ठा amdgpu_device *adev)
अणु
	u32 i, j, k;
	u32 mask;

	mutex_lock(&adev->grbm_idx_mutex);
	क्रम (i = 0; i < adev->gfx.config.max_shader_engines; i++) अणु
		क्रम (j = 0; j < adev->gfx.config.max_sh_per_se; j++) अणु
			gfx_v7_0_select_se_sh(adev, i, j, 0xffffffff);
			क्रम (k = 0; k < adev->usec_समयout; k++) अणु
				अगर (RREG32(mmRLC_SERDES_CU_MASTER_BUSY) == 0)
					अवरोध;
				udelay(1);
			पूर्ण
		पूर्ण
	पूर्ण
	gfx_v7_0_select_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff);
	mutex_unlock(&adev->grbm_idx_mutex);

	mask = RLC_SERDES_NONCU_MASTER_BUSY__SE_MASTER_BUSY_MASK |
		RLC_SERDES_NONCU_MASTER_BUSY__GC_MASTER_BUSY_MASK |
		RLC_SERDES_NONCU_MASTER_BUSY__TC0_MASTER_BUSY_MASK |
		RLC_SERDES_NONCU_MASTER_BUSY__TC1_MASTER_BUSY_MASK;
	क्रम (k = 0; k < adev->usec_समयout; k++) अणु
		अगर ((RREG32(mmRLC_SERDES_NONCU_MASTER_BUSY) & mask) == 0)
			अवरोध;
		udelay(1);
	पूर्ण
पूर्ण

अटल व्योम gfx_v7_0_update_rlc(काष्ठा amdgpu_device *adev, u32 rlc)
अणु
	u32 पंचांगp;

	पंचांगp = RREG32(mmRLC_CNTL);
	अगर (पंचांगp != rlc)
		WREG32(mmRLC_CNTL, rlc);
पूर्ण

अटल u32 gfx_v7_0_halt_rlc(काष्ठा amdgpu_device *adev)
अणु
	u32 data, orig;

	orig = data = RREG32(mmRLC_CNTL);

	अगर (data & RLC_CNTL__RLC_ENABLE_F32_MASK) अणु
		u32 i;

		data &= ~RLC_CNTL__RLC_ENABLE_F32_MASK;
		WREG32(mmRLC_CNTL, data);

		क्रम (i = 0; i < adev->usec_समयout; i++) अणु
			अगर ((RREG32(mmRLC_GPM_STAT) & RLC_GPM_STAT__RLC_BUSY_MASK) == 0)
				अवरोध;
			udelay(1);
		पूर्ण

		gfx_v7_0_रुको_क्रम_rlc_serdes(adev);
	पूर्ण

	वापस orig;
पूर्ण

अटल bool gfx_v7_0_is_rlc_enabled(काष्ठा amdgpu_device *adev)
अणु
	वापस true;
पूर्ण

अटल व्योम gfx_v7_0_set_safe_mode(काष्ठा amdgpu_device *adev)
अणु
	u32 पंचांगp, i, mask;

	पंचांगp = 0x1 | (1 << 1);
	WREG32(mmRLC_GPR_REG2, पंचांगp);

	mask = RLC_GPM_STAT__GFX_POWER_STATUS_MASK |
		RLC_GPM_STAT__GFX_CLOCK_STATUS_MASK;
	क्रम (i = 0; i < adev->usec_समयout; i++) अणु
		अगर ((RREG32(mmRLC_GPM_STAT) & mask) == mask)
			अवरोध;
		udelay(1);
	पूर्ण

	क्रम (i = 0; i < adev->usec_समयout; i++) अणु
		अगर ((RREG32(mmRLC_GPR_REG2) & 0x1) == 0)
			अवरोध;
		udelay(1);
	पूर्ण
पूर्ण

अटल व्योम gfx_v7_0_unset_safe_mode(काष्ठा amdgpu_device *adev)
अणु
	u32 पंचांगp;

	पंचांगp = 0x1 | (0 << 1);
	WREG32(mmRLC_GPR_REG2, पंचांगp);
पूर्ण

/**
 * gfx_v7_0_rlc_stop - stop the RLC ME
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Halt the RLC ME (MicroEngine) (CIK).
 */
अटल व्योम gfx_v7_0_rlc_stop(काष्ठा amdgpu_device *adev)
अणु
	WREG32(mmRLC_CNTL, 0);

	gfx_v7_0_enable_gui_idle_पूर्णांकerrupt(adev, false);

	gfx_v7_0_रुको_क्रम_rlc_serdes(adev);
पूर्ण

/**
 * gfx_v7_0_rlc_start - start the RLC ME
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Unhalt the RLC ME (MicroEngine) (CIK).
 */
अटल व्योम gfx_v7_0_rlc_start(काष्ठा amdgpu_device *adev)
अणु
	WREG32(mmRLC_CNTL, RLC_CNTL__RLC_ENABLE_F32_MASK);

	gfx_v7_0_enable_gui_idle_पूर्णांकerrupt(adev, true);

	udelay(50);
पूर्ण

अटल व्योम gfx_v7_0_rlc_reset(काष्ठा amdgpu_device *adev)
अणु
	u32 पंचांगp = RREG32(mmGRBM_SOFT_RESET);

	पंचांगp |= GRBM_SOFT_RESET__SOFT_RESET_RLC_MASK;
	WREG32(mmGRBM_SOFT_RESET, पंचांगp);
	udelay(50);
	पंचांगp &= ~GRBM_SOFT_RESET__SOFT_RESET_RLC_MASK;
	WREG32(mmGRBM_SOFT_RESET, पंचांगp);
	udelay(50);
पूर्ण

/**
 * gfx_v7_0_rlc_resume - setup the RLC hw
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Initialize the RLC रेजिस्टरs, load the ucode,
 * and start the RLC (CIK).
 * Returns 0 क्रम success, -EINVAL अगर the ucode is not available.
 */
अटल पूर्णांक gfx_v7_0_rlc_resume(काष्ठा amdgpu_device *adev)
अणु
	स्थिर काष्ठा rlc_firmware_header_v1_0 *hdr;
	स्थिर __le32 *fw_data;
	अचिन्हित i, fw_size;
	u32 पंचांगp;

	अगर (!adev->gfx.rlc_fw)
		वापस -EINVAL;

	hdr = (स्थिर काष्ठा rlc_firmware_header_v1_0 *)adev->gfx.rlc_fw->data;
	amdgpu_ucode_prपूर्णांक_rlc_hdr(&hdr->header);
	adev->gfx.rlc_fw_version = le32_to_cpu(hdr->header.ucode_version);
	adev->gfx.rlc_feature_version = le32_to_cpu(
					hdr->ucode_feature_version);

	adev->gfx.rlc.funcs->stop(adev);

	/* disable CG */
	पंचांगp = RREG32(mmRLC_CGCG_CGLS_CTRL) & 0xfffffffc;
	WREG32(mmRLC_CGCG_CGLS_CTRL, पंचांगp);

	adev->gfx.rlc.funcs->reset(adev);

	gfx_v7_0_init_pg(adev);

	WREG32(mmRLC_LB_CNTR_INIT, 0);
	WREG32(mmRLC_LB_CNTR_MAX, 0x00008000);

	mutex_lock(&adev->grbm_idx_mutex);
	gfx_v7_0_select_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff);
	WREG32(mmRLC_LB_INIT_CU_MASK, 0xffffffff);
	WREG32(mmRLC_LB_PARAMS, 0x00600408);
	WREG32(mmRLC_LB_CNTL, 0x80000004);
	mutex_unlock(&adev->grbm_idx_mutex);

	WREG32(mmRLC_MC_CNTL, 0);
	WREG32(mmRLC_UCODE_CNTL, 0);

	fw_data = (स्थिर __le32 *)
		(adev->gfx.rlc_fw->data + le32_to_cpu(hdr->header.ucode_array_offset_bytes));
	fw_size = le32_to_cpu(hdr->header.ucode_size_bytes) / 4;
	WREG32(mmRLC_GPM_UCODE_ADDR, 0);
	क्रम (i = 0; i < fw_size; i++)
		WREG32(mmRLC_GPM_UCODE_DATA, le32_to_cpup(fw_data++));
	WREG32(mmRLC_GPM_UCODE_ADDR, adev->gfx.rlc_fw_version);

	/* XXX - find out what chips support lbpw */
	gfx_v7_0_enable_lbpw(adev, false);

	अगर (adev->asic_type == CHIP_BONAIRE)
		WREG32(mmRLC_DRIVER_CPDMA_STATUS, 0);

	adev->gfx.rlc.funcs->start(adev);

	वापस 0;
पूर्ण

अटल व्योम gfx_v7_0_update_spm_vmid(काष्ठा amdgpu_device *adev, अचिन्हित vmid)
अणु
	u32 data;

	data = RREG32(mmRLC_SPM_VMID);

	data &= ~RLC_SPM_VMID__RLC_SPM_VMID_MASK;
	data |= (vmid & RLC_SPM_VMID__RLC_SPM_VMID_MASK) << RLC_SPM_VMID__RLC_SPM_VMID__SHIFT;

	WREG32(mmRLC_SPM_VMID, data);
पूर्ण

अटल व्योम gfx_v7_0_enable_cgcg(काष्ठा amdgpu_device *adev, bool enable)
अणु
	u32 data, orig, पंचांगp, पंचांगp2;

	orig = data = RREG32(mmRLC_CGCG_CGLS_CTRL);

	अगर (enable && (adev->cg_flags & AMD_CG_SUPPORT_GFX_CGCG)) अणु
		gfx_v7_0_enable_gui_idle_पूर्णांकerrupt(adev, true);

		पंचांगp = gfx_v7_0_halt_rlc(adev);

		mutex_lock(&adev->grbm_idx_mutex);
		gfx_v7_0_select_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff);
		WREG32(mmRLC_SERDES_WR_CU_MASTER_MASK, 0xffffffff);
		WREG32(mmRLC_SERDES_WR_NONCU_MASTER_MASK, 0xffffffff);
		पंचांगp2 = RLC_SERDES_WR_CTRL__BPM_ADDR_MASK |
			RLC_SERDES_WR_CTRL__CGCG_OVERRIDE_0_MASK |
			RLC_SERDES_WR_CTRL__CGLS_ENABLE_MASK;
		WREG32(mmRLC_SERDES_WR_CTRL, पंचांगp2);
		mutex_unlock(&adev->grbm_idx_mutex);

		gfx_v7_0_update_rlc(adev, पंचांगp);

		data |= RLC_CGCG_CGLS_CTRL__CGCG_EN_MASK | RLC_CGCG_CGLS_CTRL__CGLS_EN_MASK;
		अगर (orig != data)
			WREG32(mmRLC_CGCG_CGLS_CTRL, data);

	पूर्ण अन्यथा अणु
		gfx_v7_0_enable_gui_idle_पूर्णांकerrupt(adev, false);

		RREG32(mmCB_CGTT_SCLK_CTRL);
		RREG32(mmCB_CGTT_SCLK_CTRL);
		RREG32(mmCB_CGTT_SCLK_CTRL);
		RREG32(mmCB_CGTT_SCLK_CTRL);

		data &= ~(RLC_CGCG_CGLS_CTRL__CGCG_EN_MASK | RLC_CGCG_CGLS_CTRL__CGLS_EN_MASK);
		अगर (orig != data)
			WREG32(mmRLC_CGCG_CGLS_CTRL, data);

		gfx_v7_0_enable_gui_idle_पूर्णांकerrupt(adev, true);
	पूर्ण
पूर्ण

अटल व्योम gfx_v7_0_enable_mgcg(काष्ठा amdgpu_device *adev, bool enable)
अणु
	u32 data, orig, पंचांगp = 0;

	अगर (enable && (adev->cg_flags & AMD_CG_SUPPORT_GFX_MGCG)) अणु
		अगर (adev->cg_flags & AMD_CG_SUPPORT_GFX_MGLS) अणु
			अगर (adev->cg_flags & AMD_CG_SUPPORT_GFX_CP_LS) अणु
				orig = data = RREG32(mmCP_MEM_SLP_CNTL);
				data |= CP_MEM_SLP_CNTL__CP_MEM_LS_EN_MASK;
				अगर (orig != data)
					WREG32(mmCP_MEM_SLP_CNTL, data);
			पूर्ण
		पूर्ण

		orig = data = RREG32(mmRLC_CGTT_MGCG_OVERRIDE);
		data |= 0x00000001;
		data &= 0xfffffffd;
		अगर (orig != data)
			WREG32(mmRLC_CGTT_MGCG_OVERRIDE, data);

		पंचांगp = gfx_v7_0_halt_rlc(adev);

		mutex_lock(&adev->grbm_idx_mutex);
		gfx_v7_0_select_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff);
		WREG32(mmRLC_SERDES_WR_CU_MASTER_MASK, 0xffffffff);
		WREG32(mmRLC_SERDES_WR_NONCU_MASTER_MASK, 0xffffffff);
		data = RLC_SERDES_WR_CTRL__BPM_ADDR_MASK |
			RLC_SERDES_WR_CTRL__MGCG_OVERRIDE_0_MASK;
		WREG32(mmRLC_SERDES_WR_CTRL, data);
		mutex_unlock(&adev->grbm_idx_mutex);

		gfx_v7_0_update_rlc(adev, पंचांगp);

		अगर (adev->cg_flags & AMD_CG_SUPPORT_GFX_CGTS) अणु
			orig = data = RREG32(mmCGTS_SM_CTRL_REG);
			data &= ~CGTS_SM_CTRL_REG__SM_MODE_MASK;
			data |= (0x2 << CGTS_SM_CTRL_REG__SM_MODE__SHIFT);
			data |= CGTS_SM_CTRL_REG__SM_MODE_ENABLE_MASK;
			data &= ~CGTS_SM_CTRL_REG__OVERRIDE_MASK;
			अगर ((adev->cg_flags & AMD_CG_SUPPORT_GFX_MGLS) &&
			    (adev->cg_flags & AMD_CG_SUPPORT_GFX_CGTS_LS))
				data &= ~CGTS_SM_CTRL_REG__LS_OVERRIDE_MASK;
			data &= ~CGTS_SM_CTRL_REG__ON_MONITOR_ADD_MASK;
			data |= CGTS_SM_CTRL_REG__ON_MONITOR_ADD_EN_MASK;
			data |= (0x96 << CGTS_SM_CTRL_REG__ON_MONITOR_ADD__SHIFT);
			अगर (orig != data)
				WREG32(mmCGTS_SM_CTRL_REG, data);
		पूर्ण
	पूर्ण अन्यथा अणु
		orig = data = RREG32(mmRLC_CGTT_MGCG_OVERRIDE);
		data |= 0x00000003;
		अगर (orig != data)
			WREG32(mmRLC_CGTT_MGCG_OVERRIDE, data);

		data = RREG32(mmRLC_MEM_SLP_CNTL);
		अगर (data & RLC_MEM_SLP_CNTL__RLC_MEM_LS_EN_MASK) अणु
			data &= ~RLC_MEM_SLP_CNTL__RLC_MEM_LS_EN_MASK;
			WREG32(mmRLC_MEM_SLP_CNTL, data);
		पूर्ण

		data = RREG32(mmCP_MEM_SLP_CNTL);
		अगर (data & CP_MEM_SLP_CNTL__CP_MEM_LS_EN_MASK) अणु
			data &= ~CP_MEM_SLP_CNTL__CP_MEM_LS_EN_MASK;
			WREG32(mmCP_MEM_SLP_CNTL, data);
		पूर्ण

		orig = data = RREG32(mmCGTS_SM_CTRL_REG);
		data |= CGTS_SM_CTRL_REG__OVERRIDE_MASK | CGTS_SM_CTRL_REG__LS_OVERRIDE_MASK;
		अगर (orig != data)
			WREG32(mmCGTS_SM_CTRL_REG, data);

		पंचांगp = gfx_v7_0_halt_rlc(adev);

		mutex_lock(&adev->grbm_idx_mutex);
		gfx_v7_0_select_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff);
		WREG32(mmRLC_SERDES_WR_CU_MASTER_MASK, 0xffffffff);
		WREG32(mmRLC_SERDES_WR_NONCU_MASTER_MASK, 0xffffffff);
		data = RLC_SERDES_WR_CTRL__BPM_ADDR_MASK | RLC_SERDES_WR_CTRL__MGCG_OVERRIDE_1_MASK;
		WREG32(mmRLC_SERDES_WR_CTRL, data);
		mutex_unlock(&adev->grbm_idx_mutex);

		gfx_v7_0_update_rlc(adev, पंचांगp);
	पूर्ण
पूर्ण

अटल व्योम gfx_v7_0_update_cg(काष्ठा amdgpu_device *adev,
			       bool enable)
अणु
	gfx_v7_0_enable_gui_idle_पूर्णांकerrupt(adev, false);
	/* order matters! */
	अगर (enable) अणु
		gfx_v7_0_enable_mgcg(adev, true);
		gfx_v7_0_enable_cgcg(adev, true);
	पूर्ण अन्यथा अणु
		gfx_v7_0_enable_cgcg(adev, false);
		gfx_v7_0_enable_mgcg(adev, false);
	पूर्ण
	gfx_v7_0_enable_gui_idle_पूर्णांकerrupt(adev, true);
पूर्ण

अटल व्योम gfx_v7_0_enable_sclk_slowकरोwn_on_pu(काष्ठा amdgpu_device *adev,
						bool enable)
अणु
	u32 data, orig;

	orig = data = RREG32(mmRLC_PG_CNTL);
	अगर (enable && (adev->pg_flags & AMD_PG_SUPPORT_RLC_SMU_HS))
		data |= RLC_PG_CNTL__SMU_CLK_SLOWDOWN_ON_PU_ENABLE_MASK;
	अन्यथा
		data &= ~RLC_PG_CNTL__SMU_CLK_SLOWDOWN_ON_PU_ENABLE_MASK;
	अगर (orig != data)
		WREG32(mmRLC_PG_CNTL, data);
पूर्ण

अटल व्योम gfx_v7_0_enable_sclk_slowकरोwn_on_pd(काष्ठा amdgpu_device *adev,
						bool enable)
अणु
	u32 data, orig;

	orig = data = RREG32(mmRLC_PG_CNTL);
	अगर (enable && (adev->pg_flags & AMD_PG_SUPPORT_RLC_SMU_HS))
		data |= RLC_PG_CNTL__SMU_CLK_SLOWDOWN_ON_PD_ENABLE_MASK;
	अन्यथा
		data &= ~RLC_PG_CNTL__SMU_CLK_SLOWDOWN_ON_PD_ENABLE_MASK;
	अगर (orig != data)
		WREG32(mmRLC_PG_CNTL, data);
पूर्ण

अटल व्योम gfx_v7_0_enable_cp_pg(काष्ठा amdgpu_device *adev, bool enable)
अणु
	u32 data, orig;

	orig = data = RREG32(mmRLC_PG_CNTL);
	अगर (enable && (adev->pg_flags & AMD_PG_SUPPORT_CP))
		data &= ~0x8000;
	अन्यथा
		data |= 0x8000;
	अगर (orig != data)
		WREG32(mmRLC_PG_CNTL, data);
पूर्ण

अटल व्योम gfx_v7_0_enable_gds_pg(काष्ठा amdgpu_device *adev, bool enable)
अणु
	u32 data, orig;

	orig = data = RREG32(mmRLC_PG_CNTL);
	अगर (enable && (adev->pg_flags & AMD_PG_SUPPORT_GDS))
		data &= ~0x2000;
	अन्यथा
		data |= 0x2000;
	अगर (orig != data)
		WREG32(mmRLC_PG_CNTL, data);
पूर्ण

अटल पूर्णांक gfx_v7_0_cp_pg_table_num(काष्ठा amdgpu_device *adev)
अणु
	अगर (adev->asic_type == CHIP_KAVERI)
		वापस 5;
	अन्यथा
		वापस 4;
पूर्ण

अटल व्योम gfx_v7_0_enable_gfx_cgpg(काष्ठा amdgpu_device *adev,
				     bool enable)
अणु
	u32 data, orig;

	अगर (enable && (adev->pg_flags & AMD_PG_SUPPORT_GFX_PG)) अणु
		orig = data = RREG32(mmRLC_PG_CNTL);
		data |= RLC_PG_CNTL__GFX_POWER_GATING_ENABLE_MASK;
		अगर (orig != data)
			WREG32(mmRLC_PG_CNTL, data);

		orig = data = RREG32(mmRLC_AUTO_PG_CTRL);
		data |= RLC_AUTO_PG_CTRL__AUTO_PG_EN_MASK;
		अगर (orig != data)
			WREG32(mmRLC_AUTO_PG_CTRL, data);
	पूर्ण अन्यथा अणु
		orig = data = RREG32(mmRLC_PG_CNTL);
		data &= ~RLC_PG_CNTL__GFX_POWER_GATING_ENABLE_MASK;
		अगर (orig != data)
			WREG32(mmRLC_PG_CNTL, data);

		orig = data = RREG32(mmRLC_AUTO_PG_CTRL);
		data &= ~RLC_AUTO_PG_CTRL__AUTO_PG_EN_MASK;
		अगर (orig != data)
			WREG32(mmRLC_AUTO_PG_CTRL, data);

		data = RREG32(mmDB_RENDER_CONTROL);
	पूर्ण
पूर्ण

अटल व्योम gfx_v7_0_set_user_cu_inactive_biपंचांगap(काष्ठा amdgpu_device *adev,
						 u32 biपंचांगap)
अणु
	u32 data;

	अगर (!biपंचांगap)
		वापस;

	data = biपंचांगap << GC_USER_SHADER_ARRAY_CONFIG__INACTIVE_CUS__SHIFT;
	data &= GC_USER_SHADER_ARRAY_CONFIG__INACTIVE_CUS_MASK;

	WREG32(mmGC_USER_SHADER_ARRAY_CONFIG, data);
पूर्ण

अटल u32 gfx_v7_0_get_cu_active_biपंचांगap(काष्ठा amdgpu_device *adev)
अणु
	u32 data, mask;

	data = RREG32(mmCC_GC_SHADER_ARRAY_CONFIG);
	data |= RREG32(mmGC_USER_SHADER_ARRAY_CONFIG);

	data &= CC_GC_SHADER_ARRAY_CONFIG__INACTIVE_CUS_MASK;
	data >>= CC_GC_SHADER_ARRAY_CONFIG__INACTIVE_CUS__SHIFT;

	mask = amdgpu_gfx_create_biपंचांगask(adev->gfx.config.max_cu_per_sh);

	वापस (~data) & mask;
पूर्ण

अटल व्योम gfx_v7_0_init_ao_cu_mask(काष्ठा amdgpu_device *adev)
अणु
	u32 पंचांगp;

	WREG32(mmRLC_PG_ALWAYS_ON_CU_MASK, adev->gfx.cu_info.ao_cu_mask);

	पंचांगp = RREG32(mmRLC_MAX_PG_CU);
	पंचांगp &= ~RLC_MAX_PG_CU__MAX_POWERED_UP_CU_MASK;
	पंचांगp |= (adev->gfx.cu_info.number << RLC_MAX_PG_CU__MAX_POWERED_UP_CU__SHIFT);
	WREG32(mmRLC_MAX_PG_CU, पंचांगp);
पूर्ण

अटल व्योम gfx_v7_0_enable_gfx_अटल_mgpg(काष्ठा amdgpu_device *adev,
					    bool enable)
अणु
	u32 data, orig;

	orig = data = RREG32(mmRLC_PG_CNTL);
	अगर (enable && (adev->pg_flags & AMD_PG_SUPPORT_GFX_SMG))
		data |= RLC_PG_CNTL__STATIC_PER_CU_PG_ENABLE_MASK;
	अन्यथा
		data &= ~RLC_PG_CNTL__STATIC_PER_CU_PG_ENABLE_MASK;
	अगर (orig != data)
		WREG32(mmRLC_PG_CNTL, data);
पूर्ण

अटल व्योम gfx_v7_0_enable_gfx_dynamic_mgpg(काष्ठा amdgpu_device *adev,
					     bool enable)
अणु
	u32 data, orig;

	orig = data = RREG32(mmRLC_PG_CNTL);
	अगर (enable && (adev->pg_flags & AMD_PG_SUPPORT_GFX_DMG))
		data |= RLC_PG_CNTL__DYN_PER_CU_PG_ENABLE_MASK;
	अन्यथा
		data &= ~RLC_PG_CNTL__DYN_PER_CU_PG_ENABLE_MASK;
	अगर (orig != data)
		WREG32(mmRLC_PG_CNTL, data);
पूर्ण

#घोषणा RLC_SAVE_AND_RESTORE_STARTING_OFFSET 0x90
#घोषणा RLC_CLEAR_STATE_DESCRIPTOR_OFFSET    0x3D

अटल व्योम gfx_v7_0_init_gfx_cgpg(काष्ठा amdgpu_device *adev)
अणु
	u32 data, orig;
	u32 i;

	अगर (adev->gfx.rlc.cs_data) अणु
		WREG32(mmRLC_GPM_SCRATCH_ADDR, RLC_CLEAR_STATE_DESCRIPTOR_OFFSET);
		WREG32(mmRLC_GPM_SCRATCH_DATA, upper_32_bits(adev->gfx.rlc.clear_state_gpu_addr));
		WREG32(mmRLC_GPM_SCRATCH_DATA, lower_32_bits(adev->gfx.rlc.clear_state_gpu_addr));
		WREG32(mmRLC_GPM_SCRATCH_DATA, adev->gfx.rlc.clear_state_size);
	पूर्ण अन्यथा अणु
		WREG32(mmRLC_GPM_SCRATCH_ADDR, RLC_CLEAR_STATE_DESCRIPTOR_OFFSET);
		क्रम (i = 0; i < 3; i++)
			WREG32(mmRLC_GPM_SCRATCH_DATA, 0);
	पूर्ण
	अगर (adev->gfx.rlc.reg_list) अणु
		WREG32(mmRLC_GPM_SCRATCH_ADDR, RLC_SAVE_AND_RESTORE_STARTING_OFFSET);
		क्रम (i = 0; i < adev->gfx.rlc.reg_list_size; i++)
			WREG32(mmRLC_GPM_SCRATCH_DATA, adev->gfx.rlc.reg_list[i]);
	पूर्ण

	orig = data = RREG32(mmRLC_PG_CNTL);
	data |= RLC_PG_CNTL__GFX_POWER_GATING_SRC_MASK;
	अगर (orig != data)
		WREG32(mmRLC_PG_CNTL, data);

	WREG32(mmRLC_SAVE_AND_RESTORE_BASE, adev->gfx.rlc.save_restore_gpu_addr >> 8);
	WREG32(mmRLC_JUMP_TABLE_RESTORE, adev->gfx.rlc.cp_table_gpu_addr >> 8);

	data = RREG32(mmCP_RB_WPTR_POLL_CNTL);
	data &= ~CP_RB_WPTR_POLL_CNTL__IDLE_POLL_COUNT_MASK;
	data |= (0x60 << CP_RB_WPTR_POLL_CNTL__IDLE_POLL_COUNT__SHIFT);
	WREG32(mmCP_RB_WPTR_POLL_CNTL, data);

	data = 0x10101010;
	WREG32(mmRLC_PG_DELAY, data);

	data = RREG32(mmRLC_PG_DELAY_2);
	data &= ~0xff;
	data |= 0x3;
	WREG32(mmRLC_PG_DELAY_2, data);

	data = RREG32(mmRLC_AUTO_PG_CTRL);
	data &= ~RLC_AUTO_PG_CTRL__GRBM_REG_SAVE_GFX_IDLE_THRESHOLD_MASK;
	data |= (0x700 << RLC_AUTO_PG_CTRL__GRBM_REG_SAVE_GFX_IDLE_THRESHOLD__SHIFT);
	WREG32(mmRLC_AUTO_PG_CTRL, data);

पूर्ण

अटल व्योम gfx_v7_0_update_gfx_pg(काष्ठा amdgpu_device *adev, bool enable)
अणु
	gfx_v7_0_enable_gfx_cgpg(adev, enable);
	gfx_v7_0_enable_gfx_अटल_mgpg(adev, enable);
	gfx_v7_0_enable_gfx_dynamic_mgpg(adev, enable);
पूर्ण

अटल u32 gfx_v7_0_get_csb_size(काष्ठा amdgpu_device *adev)
अणु
	u32 count = 0;
	स्थिर काष्ठा cs_section_def *sect = शून्य;
	स्थिर काष्ठा cs_extent_def *ext = शून्य;

	अगर (adev->gfx.rlc.cs_data == शून्य)
		वापस 0;

	/* begin clear state */
	count += 2;
	/* context control state */
	count += 3;

	क्रम (sect = adev->gfx.rlc.cs_data; sect->section != शून्य; ++sect) अणु
		क्रम (ext = sect->section; ext->extent != शून्य; ++ext) अणु
			अगर (sect->id == SECT_CONTEXT)
				count += 2 + ext->reg_count;
			अन्यथा
				वापस 0;
		पूर्ण
	पूर्ण
	/* pa_sc_raster_config/pa_sc_raster_config1 */
	count += 4;
	/* end clear state */
	count += 2;
	/* clear state */
	count += 2;

	वापस count;
पूर्ण

अटल व्योम gfx_v7_0_get_csb_buffer(काष्ठा amdgpu_device *adev,
				    अस्थिर u32 *buffer)
अणु
	u32 count = 0, i;
	स्थिर काष्ठा cs_section_def *sect = शून्य;
	स्थिर काष्ठा cs_extent_def *ext = शून्य;

	अगर (adev->gfx.rlc.cs_data == शून्य)
		वापस;
	अगर (buffer == शून्य)
		वापस;

	buffer[count++] = cpu_to_le32(PACKET3(PACKET3_PREAMBLE_CNTL, 0));
	buffer[count++] = cpu_to_le32(PACKET3_PREAMBLE_BEGIN_CLEAR_STATE);

	buffer[count++] = cpu_to_le32(PACKET3(PACKET3_CONTEXT_CONTROL, 1));
	buffer[count++] = cpu_to_le32(0x80000000);
	buffer[count++] = cpu_to_le32(0x80000000);

	क्रम (sect = adev->gfx.rlc.cs_data; sect->section != शून्य; ++sect) अणु
		क्रम (ext = sect->section; ext->extent != शून्य; ++ext) अणु
			अगर (sect->id == SECT_CONTEXT) अणु
				buffer[count++] =
					cpu_to_le32(PACKET3(PACKET3_SET_CONTEXT_REG, ext->reg_count));
				buffer[count++] = cpu_to_le32(ext->reg_index - PACKET3_SET_CONTEXT_REG_START);
				क्रम (i = 0; i < ext->reg_count; i++)
					buffer[count++] = cpu_to_le32(ext->extent[i]);
			पूर्ण अन्यथा अणु
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण

	buffer[count++] = cpu_to_le32(PACKET3(PACKET3_SET_CONTEXT_REG, 2));
	buffer[count++] = cpu_to_le32(mmPA_SC_RASTER_CONFIG - PACKET3_SET_CONTEXT_REG_START);
	चयन (adev->asic_type) अणु
	हाल CHIP_BONAIRE:
		buffer[count++] = cpu_to_le32(0x16000012);
		buffer[count++] = cpu_to_le32(0x00000000);
		अवरोध;
	हाल CHIP_KAVERI:
		buffer[count++] = cpu_to_le32(0x00000000); /* XXX */
		buffer[count++] = cpu_to_le32(0x00000000);
		अवरोध;
	हाल CHIP_KABINI:
	हाल CHIP_MULLINS:
		buffer[count++] = cpu_to_le32(0x00000000); /* XXX */
		buffer[count++] = cpu_to_le32(0x00000000);
		अवरोध;
	हाल CHIP_HAWAII:
		buffer[count++] = cpu_to_le32(0x3a00161a);
		buffer[count++] = cpu_to_le32(0x0000002e);
		अवरोध;
	शेष:
		buffer[count++] = cpu_to_le32(0x00000000);
		buffer[count++] = cpu_to_le32(0x00000000);
		अवरोध;
	पूर्ण

	buffer[count++] = cpu_to_le32(PACKET3(PACKET3_PREAMBLE_CNTL, 0));
	buffer[count++] = cpu_to_le32(PACKET3_PREAMBLE_END_CLEAR_STATE);

	buffer[count++] = cpu_to_le32(PACKET3(PACKET3_CLEAR_STATE, 0));
	buffer[count++] = cpu_to_le32(0);
पूर्ण

अटल व्योम gfx_v7_0_init_pg(काष्ठा amdgpu_device *adev)
अणु
	अगर (adev->pg_flags & (AMD_PG_SUPPORT_GFX_PG |
			      AMD_PG_SUPPORT_GFX_SMG |
			      AMD_PG_SUPPORT_GFX_DMG |
			      AMD_PG_SUPPORT_CP |
			      AMD_PG_SUPPORT_GDS |
			      AMD_PG_SUPPORT_RLC_SMU_HS)) अणु
		gfx_v7_0_enable_sclk_slowकरोwn_on_pu(adev, true);
		gfx_v7_0_enable_sclk_slowकरोwn_on_pd(adev, true);
		अगर (adev->pg_flags & AMD_PG_SUPPORT_GFX_PG) अणु
			gfx_v7_0_init_gfx_cgpg(adev);
			gfx_v7_0_enable_cp_pg(adev, true);
			gfx_v7_0_enable_gds_pg(adev, true);
		पूर्ण
		gfx_v7_0_init_ao_cu_mask(adev);
		gfx_v7_0_update_gfx_pg(adev, true);
	पूर्ण
पूर्ण

अटल व्योम gfx_v7_0_fini_pg(काष्ठा amdgpu_device *adev)
अणु
	अगर (adev->pg_flags & (AMD_PG_SUPPORT_GFX_PG |
			      AMD_PG_SUPPORT_GFX_SMG |
			      AMD_PG_SUPPORT_GFX_DMG |
			      AMD_PG_SUPPORT_CP |
			      AMD_PG_SUPPORT_GDS |
			      AMD_PG_SUPPORT_RLC_SMU_HS)) अणु
		gfx_v7_0_update_gfx_pg(adev, false);
		अगर (adev->pg_flags & AMD_PG_SUPPORT_GFX_PG) अणु
			gfx_v7_0_enable_cp_pg(adev, false);
			gfx_v7_0_enable_gds_pg(adev, false);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * gfx_v7_0_get_gpu_घड़ी_counter - वापस GPU घड़ी counter snapshot
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Fetches a GPU घड़ी counter snapshot (SI).
 * Returns the 64 bit घड़ी counter snapshot.
 */
अटल uपूर्णांक64_t gfx_v7_0_get_gpu_घड़ी_counter(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक64_t घड़ी;

	mutex_lock(&adev->gfx.gpu_घड़ी_mutex);
	WREG32(mmRLC_CAPTURE_GPU_CLOCK_COUNT, 1);
	घड़ी = (uपूर्णांक64_t)RREG32(mmRLC_GPU_CLOCK_COUNT_LSB) |
		((uपूर्णांक64_t)RREG32(mmRLC_GPU_CLOCK_COUNT_MSB) << 32ULL);
	mutex_unlock(&adev->gfx.gpu_घड़ी_mutex);
	वापस घड़ी;
पूर्ण

अटल व्योम gfx_v7_0_ring_emit_gds_चयन(काष्ठा amdgpu_ring *ring,
					  uपूर्णांक32_t vmid,
					  uपूर्णांक32_t gds_base, uपूर्णांक32_t gds_size,
					  uपूर्णांक32_t gws_base, uपूर्णांक32_t gws_size,
					  uपूर्णांक32_t oa_base, uपूर्णांक32_t oa_size)
अणु
	/* GDS Base */
	amdgpu_ring_ग_लिखो(ring, PACKET3(PACKET3_WRITE_DATA, 3));
	amdgpu_ring_ग_लिखो(ring, (WRITE_DATA_ENGINE_SEL(0) |
				WRITE_DATA_DST_SEL(0)));
	amdgpu_ring_ग_लिखो(ring, amdgpu_gds_reg_offset[vmid].mem_base);
	amdgpu_ring_ग_लिखो(ring, 0);
	amdgpu_ring_ग_लिखो(ring, gds_base);

	/* GDS Size */
	amdgpu_ring_ग_लिखो(ring, PACKET3(PACKET3_WRITE_DATA, 3));
	amdgpu_ring_ग_लिखो(ring, (WRITE_DATA_ENGINE_SEL(0) |
				WRITE_DATA_DST_SEL(0)));
	amdgpu_ring_ग_लिखो(ring, amdgpu_gds_reg_offset[vmid].mem_size);
	amdgpu_ring_ग_लिखो(ring, 0);
	amdgpu_ring_ग_लिखो(ring, gds_size);

	/* GWS */
	amdgpu_ring_ग_लिखो(ring, PACKET3(PACKET3_WRITE_DATA, 3));
	amdgpu_ring_ग_लिखो(ring, (WRITE_DATA_ENGINE_SEL(0) |
				WRITE_DATA_DST_SEL(0)));
	amdgpu_ring_ग_लिखो(ring, amdgpu_gds_reg_offset[vmid].gws);
	amdgpu_ring_ग_लिखो(ring, 0);
	amdgpu_ring_ग_लिखो(ring, gws_size << GDS_GWS_VMID0__SIZE__SHIFT | gws_base);

	/* OA */
	amdgpu_ring_ग_लिखो(ring, PACKET3(PACKET3_WRITE_DATA, 3));
	amdgpu_ring_ग_लिखो(ring, (WRITE_DATA_ENGINE_SEL(0) |
				WRITE_DATA_DST_SEL(0)));
	amdgpu_ring_ग_लिखो(ring, amdgpu_gds_reg_offset[vmid].oa);
	amdgpu_ring_ग_लिखो(ring, 0);
	amdgpu_ring_ग_लिखो(ring, (1 << (oa_size + oa_base)) - (1 << oa_base));
पूर्ण

अटल व्योम gfx_v7_0_ring_soft_recovery(काष्ठा amdgpu_ring *ring, अचिन्हित vmid)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	uपूर्णांक32_t value = 0;

	value = REG_SET_FIELD(value, SQ_CMD, CMD, 0x03);
	value = REG_SET_FIELD(value, SQ_CMD, MODE, 0x01);
	value = REG_SET_FIELD(value, SQ_CMD, CHECK_VMID, 1);
	value = REG_SET_FIELD(value, SQ_CMD, VM_ID, vmid);
	WREG32(mmSQ_CMD, value);
पूर्ण

अटल uपूर्णांक32_t wave_पढ़ो_ind(काष्ठा amdgpu_device *adev, uपूर्णांक32_t simd, uपूर्णांक32_t wave, uपूर्णांक32_t address)
अणु
	WREG32(mmSQ_IND_INDEX,
		(wave << SQ_IND_INDEX__WAVE_ID__SHIFT) |
		(simd << SQ_IND_INDEX__SIMD_ID__SHIFT) |
		(address << SQ_IND_INDEX__INDEX__SHIFT) |
		(SQ_IND_INDEX__FORCE_READ_MASK));
	वापस RREG32(mmSQ_IND_DATA);
पूर्ण

अटल व्योम wave_पढ़ो_regs(काष्ठा amdgpu_device *adev, uपूर्णांक32_t simd,
			   uपूर्णांक32_t wave, uपूर्णांक32_t thपढ़ो,
			   uपूर्णांक32_t regno, uपूर्णांक32_t num, uपूर्णांक32_t *out)
अणु
	WREG32(mmSQ_IND_INDEX,
		(wave << SQ_IND_INDEX__WAVE_ID__SHIFT) |
		(simd << SQ_IND_INDEX__SIMD_ID__SHIFT) |
		(regno << SQ_IND_INDEX__INDEX__SHIFT) |
		(thपढ़ो << SQ_IND_INDEX__THREAD_ID__SHIFT) |
		(SQ_IND_INDEX__FORCE_READ_MASK) |
		(SQ_IND_INDEX__AUTO_INCR_MASK));
	जबतक (num--)
		*(out++) = RREG32(mmSQ_IND_DATA);
पूर्ण

अटल व्योम gfx_v7_0_पढ़ो_wave_data(काष्ठा amdgpu_device *adev, uपूर्णांक32_t simd, uपूर्णांक32_t wave, uपूर्णांक32_t *dst, पूर्णांक *no_fields)
अणु
	/* type 0 wave data */
	dst[(*no_fields)++] = 0;
	dst[(*no_fields)++] = wave_पढ़ो_ind(adev, simd, wave, ixSQ_WAVE_STATUS);
	dst[(*no_fields)++] = wave_पढ़ो_ind(adev, simd, wave, ixSQ_WAVE_PC_LO);
	dst[(*no_fields)++] = wave_पढ़ो_ind(adev, simd, wave, ixSQ_WAVE_PC_HI);
	dst[(*no_fields)++] = wave_पढ़ो_ind(adev, simd, wave, ixSQ_WAVE_EXEC_LO);
	dst[(*no_fields)++] = wave_पढ़ो_ind(adev, simd, wave, ixSQ_WAVE_EXEC_HI);
	dst[(*no_fields)++] = wave_पढ़ो_ind(adev, simd, wave, ixSQ_WAVE_HW_ID);
	dst[(*no_fields)++] = wave_पढ़ो_ind(adev, simd, wave, ixSQ_WAVE_INST_DW0);
	dst[(*no_fields)++] = wave_पढ़ो_ind(adev, simd, wave, ixSQ_WAVE_INST_DW1);
	dst[(*no_fields)++] = wave_पढ़ो_ind(adev, simd, wave, ixSQ_WAVE_GPR_ALLOC);
	dst[(*no_fields)++] = wave_पढ़ो_ind(adev, simd, wave, ixSQ_WAVE_LDS_ALLOC);
	dst[(*no_fields)++] = wave_पढ़ो_ind(adev, simd, wave, ixSQ_WAVE_TRAPSTS);
	dst[(*no_fields)++] = wave_पढ़ो_ind(adev, simd, wave, ixSQ_WAVE_IB_STS);
	dst[(*no_fields)++] = wave_पढ़ो_ind(adev, simd, wave, ixSQ_WAVE_TBA_LO);
	dst[(*no_fields)++] = wave_पढ़ो_ind(adev, simd, wave, ixSQ_WAVE_TBA_HI);
	dst[(*no_fields)++] = wave_पढ़ो_ind(adev, simd, wave, ixSQ_WAVE_TMA_LO);
	dst[(*no_fields)++] = wave_पढ़ो_ind(adev, simd, wave, ixSQ_WAVE_TMA_HI);
	dst[(*no_fields)++] = wave_पढ़ो_ind(adev, simd, wave, ixSQ_WAVE_IB_DBG0);
	dst[(*no_fields)++] = wave_पढ़ो_ind(adev, simd, wave, ixSQ_WAVE_M0);
पूर्ण

अटल व्योम gfx_v7_0_पढ़ो_wave_sgprs(काष्ठा amdgpu_device *adev, uपूर्णांक32_t simd,
				     uपूर्णांक32_t wave, uपूर्णांक32_t start,
				     uपूर्णांक32_t size, uपूर्णांक32_t *dst)
अणु
	wave_पढ़ो_regs(
		adev, simd, wave, 0,
		start + SQIND_WAVE_SGPRS_OFFSET, size, dst);
पूर्ण

अटल व्योम gfx_v7_0_select_me_pipe_q(काष्ठा amdgpu_device *adev,
				  u32 me, u32 pipe, u32 q, u32 vm)
अणु
	cik_srbm_select(adev, me, pipe, q, vm);
पूर्ण

अटल स्थिर काष्ठा amdgpu_gfx_funcs gfx_v7_0_gfx_funcs = अणु
	.get_gpu_घड़ी_counter = &gfx_v7_0_get_gpu_घड़ी_counter,
	.select_se_sh = &gfx_v7_0_select_se_sh,
	.पढ़ो_wave_data = &gfx_v7_0_पढ़ो_wave_data,
	.पढ़ो_wave_sgprs = &gfx_v7_0_पढ़ो_wave_sgprs,
	.select_me_pipe_q = &gfx_v7_0_select_me_pipe_q
पूर्ण;

अटल स्थिर काष्ठा amdgpu_rlc_funcs gfx_v7_0_rlc_funcs = अणु
	.is_rlc_enabled = gfx_v7_0_is_rlc_enabled,
	.set_safe_mode = gfx_v7_0_set_safe_mode,
	.unset_safe_mode = gfx_v7_0_unset_safe_mode,
	.init = gfx_v7_0_rlc_init,
	.get_csb_size = gfx_v7_0_get_csb_size,
	.get_csb_buffer = gfx_v7_0_get_csb_buffer,
	.get_cp_table_num = gfx_v7_0_cp_pg_table_num,
	.resume = gfx_v7_0_rlc_resume,
	.stop = gfx_v7_0_rlc_stop,
	.reset = gfx_v7_0_rlc_reset,
	.start = gfx_v7_0_rlc_start,
	.update_spm_vmid = gfx_v7_0_update_spm_vmid
पूर्ण;

अटल पूर्णांक gfx_v7_0_early_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	adev->gfx.num_gfx_rings = GFX7_NUM_GFX_RINGS;
	adev->gfx.num_compute_rings = min(amdgpu_gfx_get_num_kcq(adev),
					  AMDGPU_MAX_COMPUTE_RINGS);
	adev->gfx.funcs = &gfx_v7_0_gfx_funcs;
	adev->gfx.rlc.funcs = &gfx_v7_0_rlc_funcs;
	gfx_v7_0_set_ring_funcs(adev);
	gfx_v7_0_set_irq_funcs(adev);
	gfx_v7_0_set_gds_init(adev);

	वापस 0;
पूर्ण

अटल पूर्णांक gfx_v7_0_late_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	पूर्णांक r;

	r = amdgpu_irq_get(adev, &adev->gfx.priv_reg_irq, 0);
	अगर (r)
		वापस r;

	r = amdgpu_irq_get(adev, &adev->gfx.priv_inst_irq, 0);
	अगर (r)
		वापस r;

	वापस 0;
पूर्ण

अटल व्योम gfx_v7_0_gpu_early_init(काष्ठा amdgpu_device *adev)
अणु
	u32 gb_addr_config;
	u32 mc_arb_ramcfg;
	u32 dimm00_addr_map, dimm01_addr_map, dimm10_addr_map, dimm11_addr_map;
	u32 पंचांगp;

	चयन (adev->asic_type) अणु
	हाल CHIP_BONAIRE:
		adev->gfx.config.max_shader_engines = 2;
		adev->gfx.config.max_tile_pipes = 4;
		adev->gfx.config.max_cu_per_sh = 7;
		adev->gfx.config.max_sh_per_se = 1;
		adev->gfx.config.max_backends_per_se = 2;
		adev->gfx.config.max_texture_channel_caches = 4;
		adev->gfx.config.max_gprs = 256;
		adev->gfx.config.max_gs_thपढ़ोs = 32;
		adev->gfx.config.max_hw_contexts = 8;

		adev->gfx.config.sc_prim_fअगरo_size_frontend = 0x20;
		adev->gfx.config.sc_prim_fअगरo_size_backend = 0x100;
		adev->gfx.config.sc_hiz_tile_fअगरo_size = 0x30;
		adev->gfx.config.sc_earlyz_tile_fअगरo_size = 0x130;
		gb_addr_config = BONAIRE_GB_ADDR_CONFIG_GOLDEN;
		अवरोध;
	हाल CHIP_HAWAII:
		adev->gfx.config.max_shader_engines = 4;
		adev->gfx.config.max_tile_pipes = 16;
		adev->gfx.config.max_cu_per_sh = 11;
		adev->gfx.config.max_sh_per_se = 1;
		adev->gfx.config.max_backends_per_se = 4;
		adev->gfx.config.max_texture_channel_caches = 16;
		adev->gfx.config.max_gprs = 256;
		adev->gfx.config.max_gs_thपढ़ोs = 32;
		adev->gfx.config.max_hw_contexts = 8;

		adev->gfx.config.sc_prim_fअगरo_size_frontend = 0x20;
		adev->gfx.config.sc_prim_fअगरo_size_backend = 0x100;
		adev->gfx.config.sc_hiz_tile_fअगरo_size = 0x30;
		adev->gfx.config.sc_earlyz_tile_fअगरo_size = 0x130;
		gb_addr_config = HAWAII_GB_ADDR_CONFIG_GOLDEN;
		अवरोध;
	हाल CHIP_KAVERI:
		adev->gfx.config.max_shader_engines = 1;
		adev->gfx.config.max_tile_pipes = 4;
		adev->gfx.config.max_cu_per_sh = 8;
		adev->gfx.config.max_backends_per_se = 2;
		adev->gfx.config.max_sh_per_se = 1;
		adev->gfx.config.max_texture_channel_caches = 4;
		adev->gfx.config.max_gprs = 256;
		adev->gfx.config.max_gs_thपढ़ोs = 16;
		adev->gfx.config.max_hw_contexts = 8;

		adev->gfx.config.sc_prim_fअगरo_size_frontend = 0x20;
		adev->gfx.config.sc_prim_fअगरo_size_backend = 0x100;
		adev->gfx.config.sc_hiz_tile_fअगरo_size = 0x30;
		adev->gfx.config.sc_earlyz_tile_fअगरo_size = 0x130;
		gb_addr_config = BONAIRE_GB_ADDR_CONFIG_GOLDEN;
		अवरोध;
	हाल CHIP_KABINI:
	हाल CHIP_MULLINS:
	शेष:
		adev->gfx.config.max_shader_engines = 1;
		adev->gfx.config.max_tile_pipes = 2;
		adev->gfx.config.max_cu_per_sh = 2;
		adev->gfx.config.max_sh_per_se = 1;
		adev->gfx.config.max_backends_per_se = 1;
		adev->gfx.config.max_texture_channel_caches = 2;
		adev->gfx.config.max_gprs = 256;
		adev->gfx.config.max_gs_thपढ़ोs = 16;
		adev->gfx.config.max_hw_contexts = 8;

		adev->gfx.config.sc_prim_fअगरo_size_frontend = 0x20;
		adev->gfx.config.sc_prim_fअगरo_size_backend = 0x100;
		adev->gfx.config.sc_hiz_tile_fअगरo_size = 0x30;
		adev->gfx.config.sc_earlyz_tile_fअगरo_size = 0x130;
		gb_addr_config = BONAIRE_GB_ADDR_CONFIG_GOLDEN;
		अवरोध;
	पूर्ण

	adev->gfx.config.mc_arb_ramcfg = RREG32(mmMC_ARB_RAMCFG);
	mc_arb_ramcfg = adev->gfx.config.mc_arb_ramcfg;

	adev->gfx.config.num_banks = REG_GET_FIELD(mc_arb_ramcfg,
				MC_ARB_RAMCFG, NOOFBANK);
	adev->gfx.config.num_ranks = REG_GET_FIELD(mc_arb_ramcfg,
				MC_ARB_RAMCFG, NOOFRANKS);

	adev->gfx.config.num_tile_pipes = adev->gfx.config.max_tile_pipes;
	adev->gfx.config.mem_max_burst_length_bytes = 256;
	अगर (adev->flags & AMD_IS_APU) अणु
		/* Get memory bank mapping mode. */
		पंचांगp = RREG32(mmMC_FUS_DRAM0_BANK_ADDR_MAPPING);
		dimm00_addr_map = REG_GET_FIELD(पंचांगp, MC_FUS_DRAM0_BANK_ADDR_MAPPING, DIMM0ADDRMAP);
		dimm01_addr_map = REG_GET_FIELD(पंचांगp, MC_FUS_DRAM0_BANK_ADDR_MAPPING, DIMM1ADDRMAP);

		पंचांगp = RREG32(mmMC_FUS_DRAM1_BANK_ADDR_MAPPING);
		dimm10_addr_map = REG_GET_FIELD(पंचांगp, MC_FUS_DRAM1_BANK_ADDR_MAPPING, DIMM0ADDRMAP);
		dimm11_addr_map = REG_GET_FIELD(पंचांगp, MC_FUS_DRAM1_BANK_ADDR_MAPPING, DIMM1ADDRMAP);

		/* Validate settings in हाल only one DIMM installed. */
		अगर ((dimm00_addr_map == 0) || (dimm00_addr_map == 3) || (dimm00_addr_map == 4) || (dimm00_addr_map > 12))
			dimm00_addr_map = 0;
		अगर ((dimm01_addr_map == 0) || (dimm01_addr_map == 3) || (dimm01_addr_map == 4) || (dimm01_addr_map > 12))
			dimm01_addr_map = 0;
		अगर ((dimm10_addr_map == 0) || (dimm10_addr_map == 3) || (dimm10_addr_map == 4) || (dimm10_addr_map > 12))
			dimm10_addr_map = 0;
		अगर ((dimm11_addr_map == 0) || (dimm11_addr_map == 3) || (dimm11_addr_map == 4) || (dimm11_addr_map > 12))
			dimm11_addr_map = 0;

		/* If DIMM Addr map is 8GB, ROW size should be 2KB. Otherwise 1KB. */
		/* If ROW size(DIMM1) != ROW size(DMIMM0), ROW size should be larger one. */
		अगर ((dimm00_addr_map == 11) || (dimm01_addr_map == 11) || (dimm10_addr_map == 11) || (dimm11_addr_map == 11))
			adev->gfx.config.mem_row_size_in_kb = 2;
		अन्यथा
			adev->gfx.config.mem_row_size_in_kb = 1;
	पूर्ण अन्यथा अणु
		पंचांगp = (mc_arb_ramcfg & MC_ARB_RAMCFG__NOOFCOLS_MASK) >> MC_ARB_RAMCFG__NOOFCOLS__SHIFT;
		adev->gfx.config.mem_row_size_in_kb = (4 * (1 << (8 + पंचांगp))) / 1024;
		अगर (adev->gfx.config.mem_row_size_in_kb > 4)
			adev->gfx.config.mem_row_size_in_kb = 4;
	पूर्ण
	/* XXX use MC settings? */
	adev->gfx.config.shader_engine_tile_size = 32;
	adev->gfx.config.num_gpus = 1;
	adev->gfx.config.multi_gpu_tile_size = 64;

	/* fix up row size */
	gb_addr_config &= ~GB_ADDR_CONFIG__ROW_SIZE_MASK;
	चयन (adev->gfx.config.mem_row_size_in_kb) अणु
	हाल 1:
	शेष:
		gb_addr_config |= (0 << GB_ADDR_CONFIG__ROW_SIZE__SHIFT);
		अवरोध;
	हाल 2:
		gb_addr_config |= (1 << GB_ADDR_CONFIG__ROW_SIZE__SHIFT);
		अवरोध;
	हाल 4:
		gb_addr_config |= (2 << GB_ADDR_CONFIG__ROW_SIZE__SHIFT);
		अवरोध;
	पूर्ण
	adev->gfx.config.gb_addr_config = gb_addr_config;
पूर्ण

अटल पूर्णांक gfx_v7_0_compute_ring_init(काष्ठा amdgpu_device *adev, पूर्णांक ring_id,
					पूर्णांक mec, पूर्णांक pipe, पूर्णांक queue)
अणु
	पूर्णांक r;
	अचिन्हित irq_type;
	काष्ठा amdgpu_ring *ring = &adev->gfx.compute_ring[ring_id];

	/* mec0 is me1 */
	ring->me = mec + 1;
	ring->pipe = pipe;
	ring->queue = queue;

	ring->ring_obj = शून्य;
	ring->use_करोorbell = true;
	ring->करोorbell_index = adev->करोorbell_index.mec_ring0 + ring_id;
	प्र_लिखो(ring->name, "comp_%d.%d.%d", ring->me, ring->pipe, ring->queue);

	irq_type = AMDGPU_CP_IRQ_COMPUTE_MEC1_PIPE0_EOP
		+ ((ring->me - 1) * adev->gfx.mec.num_pipe_per_mec)
		+ ring->pipe;

	/* type-2 packets are deprecated on MEC, use type-3 instead */
	r = amdgpu_ring_init(adev, ring, 1024,
			     &adev->gfx.eop_irq, irq_type,
			     AMDGPU_RING_PRIO_DEFAULT, शून्य);
	अगर (r)
		वापस r;


	वापस 0;
पूर्ण

अटल पूर्णांक gfx_v7_0_sw_init(व्योम *handle)
अणु
	काष्ठा amdgpu_ring *ring;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	पूर्णांक i, j, k, r, ring_id;

	चयन (adev->asic_type) अणु
	हाल CHIP_KAVERI:
		adev->gfx.mec.num_mec = 2;
		अवरोध;
	हाल CHIP_BONAIRE:
	हाल CHIP_HAWAII:
	हाल CHIP_KABINI:
	हाल CHIP_MULLINS:
	शेष:
		adev->gfx.mec.num_mec = 1;
		अवरोध;
	पूर्ण
	adev->gfx.mec.num_pipe_per_mec = 4;
	adev->gfx.mec.num_queue_per_pipe = 8;

	/* EOP Event */
	r = amdgpu_irq_add_id(adev, AMDGPU_IRQ_CLIENTID_LEGACY, 181, &adev->gfx.eop_irq);
	अगर (r)
		वापस r;

	/* Privileged reg */
	r = amdgpu_irq_add_id(adev, AMDGPU_IRQ_CLIENTID_LEGACY, 184,
			      &adev->gfx.priv_reg_irq);
	अगर (r)
		वापस r;

	/* Privileged inst */
	r = amdgpu_irq_add_id(adev, AMDGPU_IRQ_CLIENTID_LEGACY, 185,
			      &adev->gfx.priv_inst_irq);
	अगर (r)
		वापस r;

	gfx_v7_0_scratch_init(adev);

	r = gfx_v7_0_init_microcode(adev);
	अगर (r) अणु
		DRM_ERROR("Failed to load gfx firmware!\n");
		वापस r;
	पूर्ण

	r = adev->gfx.rlc.funcs->init(adev);
	अगर (r) अणु
		DRM_ERROR("Failed to init rlc BOs!\n");
		वापस r;
	पूर्ण

	/* allocate mec buffers */
	r = gfx_v7_0_mec_init(adev);
	अगर (r) अणु
		DRM_ERROR("Failed to init MEC BOs!\n");
		वापस r;
	पूर्ण

	क्रम (i = 0; i < adev->gfx.num_gfx_rings; i++) अणु
		ring = &adev->gfx.gfx_ring[i];
		ring->ring_obj = शून्य;
		प्र_लिखो(ring->name, "gfx");
		r = amdgpu_ring_init(adev, ring, 1024,
				     &adev->gfx.eop_irq,
				     AMDGPU_CP_IRQ_GFX_ME0_PIPE0_EOP,
				     AMDGPU_RING_PRIO_DEFAULT, शून्य);
		अगर (r)
			वापस r;
	पूर्ण

	/* set up the compute queues - allocate horizontally across pipes */
	ring_id = 0;
	क्रम (i = 0; i < adev->gfx.mec.num_mec; ++i) अणु
		क्रम (j = 0; j < adev->gfx.mec.num_queue_per_pipe; j++) अणु
			क्रम (k = 0; k < adev->gfx.mec.num_pipe_per_mec; k++) अणु
				अगर (!amdgpu_gfx_is_mec_queue_enabled(adev, i, k, j))
					जारी;

				r = gfx_v7_0_compute_ring_init(adev,
								ring_id,
								i, k, j);
				अगर (r)
					वापस r;

				ring_id++;
			पूर्ण
		पूर्ण
	पूर्ण

	adev->gfx.ce_ram_size = 0x8000;

	gfx_v7_0_gpu_early_init(adev);

	वापस r;
पूर्ण

अटल पूर्णांक gfx_v7_0_sw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	पूर्णांक i;

	क्रम (i = 0; i < adev->gfx.num_gfx_rings; i++)
		amdgpu_ring_fini(&adev->gfx.gfx_ring[i]);
	क्रम (i = 0; i < adev->gfx.num_compute_rings; i++)
		amdgpu_ring_fini(&adev->gfx.compute_ring[i]);

	gfx_v7_0_cp_compute_fini(adev);
	amdgpu_gfx_rlc_fini(adev);
	gfx_v7_0_mec_fini(adev);
	amdgpu_bo_मुक्त_kernel(&adev->gfx.rlc.clear_state_obj,
				&adev->gfx.rlc.clear_state_gpu_addr,
				(व्योम **)&adev->gfx.rlc.cs_ptr);
	अगर (adev->gfx.rlc.cp_table_size) अणु
		amdgpu_bo_मुक्त_kernel(&adev->gfx.rlc.cp_table_obj,
				&adev->gfx.rlc.cp_table_gpu_addr,
				(व्योम **)&adev->gfx.rlc.cp_table_ptr);
	पूर्ण
	gfx_v7_0_मुक्त_microcode(adev);

	वापस 0;
पूर्ण

अटल पूर्णांक gfx_v7_0_hw_init(व्योम *handle)
अणु
	पूर्णांक r;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	gfx_v7_0_स्थिरants_init(adev);

	/* init CSB */
	adev->gfx.rlc.funcs->get_csb_buffer(adev, adev->gfx.rlc.cs_ptr);
	/* init rlc */
	r = adev->gfx.rlc.funcs->resume(adev);
	अगर (r)
		वापस r;

	r = gfx_v7_0_cp_resume(adev);
	अगर (r)
		वापस r;

	वापस r;
पूर्ण

अटल पूर्णांक gfx_v7_0_hw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	amdgpu_irq_put(adev, &adev->gfx.priv_reg_irq, 0);
	amdgpu_irq_put(adev, &adev->gfx.priv_inst_irq, 0);
	gfx_v7_0_cp_enable(adev, false);
	adev->gfx.rlc.funcs->stop(adev);
	gfx_v7_0_fini_pg(adev);

	वापस 0;
पूर्ण

अटल पूर्णांक gfx_v7_0_suspend(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	वापस gfx_v7_0_hw_fini(adev);
पूर्ण

अटल पूर्णांक gfx_v7_0_resume(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	वापस gfx_v7_0_hw_init(adev);
पूर्ण

अटल bool gfx_v7_0_is_idle(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (RREG32(mmGRBM_STATUS) & GRBM_STATUS__GUI_ACTIVE_MASK)
		वापस false;
	अन्यथा
		वापस true;
पूर्ण

अटल पूर्णांक gfx_v7_0_रुको_क्रम_idle(व्योम *handle)
अणु
	अचिन्हित i;
	u32 पंचांगp;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	क्रम (i = 0; i < adev->usec_समयout; i++) अणु
		/* पढ़ो MC_STATUS */
		पंचांगp = RREG32(mmGRBM_STATUS) & GRBM_STATUS__GUI_ACTIVE_MASK;

		अगर (!पंचांगp)
			वापस 0;
		udelay(1);
	पूर्ण
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक gfx_v7_0_soft_reset(व्योम *handle)
अणु
	u32 grbm_soft_reset = 0, srbm_soft_reset = 0;
	u32 पंचांगp;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	/* GRBM_STATUS */
	पंचांगp = RREG32(mmGRBM_STATUS);
	अगर (पंचांगp & (GRBM_STATUS__PA_BUSY_MASK | GRBM_STATUS__SC_BUSY_MASK |
		   GRBM_STATUS__BCI_BUSY_MASK | GRBM_STATUS__SX_BUSY_MASK |
		   GRBM_STATUS__TA_BUSY_MASK | GRBM_STATUS__VGT_BUSY_MASK |
		   GRBM_STATUS__DB_BUSY_MASK | GRBM_STATUS__CB_BUSY_MASK |
		   GRBM_STATUS__GDS_BUSY_MASK | GRBM_STATUS__SPI_BUSY_MASK |
		   GRBM_STATUS__IA_BUSY_MASK | GRBM_STATUS__IA_BUSY_NO_DMA_MASK))
		grbm_soft_reset |= GRBM_SOFT_RESET__SOFT_RESET_CP_MASK |
			GRBM_SOFT_RESET__SOFT_RESET_GFX_MASK;

	अगर (पंचांगp & (GRBM_STATUS__CP_BUSY_MASK | GRBM_STATUS__CP_COHERENCY_BUSY_MASK)) अणु
		grbm_soft_reset |= GRBM_SOFT_RESET__SOFT_RESET_CP_MASK;
		srbm_soft_reset |= SRBM_SOFT_RESET__SOFT_RESET_GRBM_MASK;
	पूर्ण

	/* GRBM_STATUS2 */
	पंचांगp = RREG32(mmGRBM_STATUS2);
	अगर (पंचांगp & GRBM_STATUS2__RLC_BUSY_MASK)
		grbm_soft_reset |= GRBM_SOFT_RESET__SOFT_RESET_RLC_MASK;

	/* SRBM_STATUS */
	पंचांगp = RREG32(mmSRBM_STATUS);
	अगर (पंचांगp & SRBM_STATUS__GRBM_RQ_PENDING_MASK)
		srbm_soft_reset |= SRBM_SOFT_RESET__SOFT_RESET_GRBM_MASK;

	अगर (grbm_soft_reset || srbm_soft_reset) अणु
		/* disable CG/PG */
		gfx_v7_0_fini_pg(adev);
		gfx_v7_0_update_cg(adev, false);

		/* stop the rlc */
		adev->gfx.rlc.funcs->stop(adev);

		/* Disable GFX parsing/prefetching */
		WREG32(mmCP_ME_CNTL, CP_ME_CNTL__ME_HALT_MASK | CP_ME_CNTL__PFP_HALT_MASK | CP_ME_CNTL__CE_HALT_MASK);

		/* Disable MEC parsing/prefetching */
		WREG32(mmCP_MEC_CNTL, CP_MEC_CNTL__MEC_ME1_HALT_MASK | CP_MEC_CNTL__MEC_ME2_HALT_MASK);

		अगर (grbm_soft_reset) अणु
			पंचांगp = RREG32(mmGRBM_SOFT_RESET);
			पंचांगp |= grbm_soft_reset;
			dev_info(adev->dev, "GRBM_SOFT_RESET=0x%08X\n", पंचांगp);
			WREG32(mmGRBM_SOFT_RESET, पंचांगp);
			पंचांगp = RREG32(mmGRBM_SOFT_RESET);

			udelay(50);

			पंचांगp &= ~grbm_soft_reset;
			WREG32(mmGRBM_SOFT_RESET, पंचांगp);
			पंचांगp = RREG32(mmGRBM_SOFT_RESET);
		पूर्ण

		अगर (srbm_soft_reset) अणु
			पंचांगp = RREG32(mmSRBM_SOFT_RESET);
			पंचांगp |= srbm_soft_reset;
			dev_info(adev->dev, "SRBM_SOFT_RESET=0x%08X\n", पंचांगp);
			WREG32(mmSRBM_SOFT_RESET, पंचांगp);
			पंचांगp = RREG32(mmSRBM_SOFT_RESET);

			udelay(50);

			पंचांगp &= ~srbm_soft_reset;
			WREG32(mmSRBM_SOFT_RESET, पंचांगp);
			पंचांगp = RREG32(mmSRBM_SOFT_RESET);
		पूर्ण
		/* Wait a little क्रम things to settle करोwn */
		udelay(50);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम gfx_v7_0_set_gfx_eop_पूर्णांकerrupt_state(काष्ठा amdgpu_device *adev,
						 क्रमागत amdgpu_पूर्णांकerrupt_state state)
अणु
	u32 cp_पूर्णांक_cntl;

	चयन (state) अणु
	हाल AMDGPU_IRQ_STATE_DISABLE:
		cp_पूर्णांक_cntl = RREG32(mmCP_INT_CNTL_RING0);
		cp_पूर्णांक_cntl &= ~CP_INT_CNTL_RING0__TIME_STAMP_INT_ENABLE_MASK;
		WREG32(mmCP_INT_CNTL_RING0, cp_पूर्णांक_cntl);
		अवरोध;
	हाल AMDGPU_IRQ_STATE_ENABLE:
		cp_पूर्णांक_cntl = RREG32(mmCP_INT_CNTL_RING0);
		cp_पूर्णांक_cntl |= CP_INT_CNTL_RING0__TIME_STAMP_INT_ENABLE_MASK;
		WREG32(mmCP_INT_CNTL_RING0, cp_पूर्णांक_cntl);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम gfx_v7_0_set_compute_eop_पूर्णांकerrupt_state(काष्ठा amdgpu_device *adev,
						     पूर्णांक me, पूर्णांक pipe,
						     क्रमागत amdgpu_पूर्णांकerrupt_state state)
अणु
	u32 mec_पूर्णांक_cntl, mec_पूर्णांक_cntl_reg;

	/*
	 * amdgpu controls only the first MEC. That's why this function only
	 * handles the setting of पूर्णांकerrupts क्रम this specअगरic MEC. All other
	 * pipes' पूर्णांकerrupts are set by amdkfd.
	 */

	अगर (me == 1) अणु
		चयन (pipe) अणु
		हाल 0:
			mec_पूर्णांक_cntl_reg = mmCP_ME1_PIPE0_INT_CNTL;
			अवरोध;
		हाल 1:
			mec_पूर्णांक_cntl_reg = mmCP_ME1_PIPE1_INT_CNTL;
			अवरोध;
		हाल 2:
			mec_पूर्णांक_cntl_reg = mmCP_ME1_PIPE2_INT_CNTL;
			अवरोध;
		हाल 3:
			mec_पूर्णांक_cntl_reg = mmCP_ME1_PIPE3_INT_CNTL;
			अवरोध;
		शेष:
			DRM_DEBUG("invalid pipe %d\n", pipe);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		DRM_DEBUG("invalid me %d\n", me);
		वापस;
	पूर्ण

	चयन (state) अणु
	हाल AMDGPU_IRQ_STATE_DISABLE:
		mec_पूर्णांक_cntl = RREG32(mec_पूर्णांक_cntl_reg);
		mec_पूर्णांक_cntl &= ~CP_INT_CNTL_RING0__TIME_STAMP_INT_ENABLE_MASK;
		WREG32(mec_पूर्णांक_cntl_reg, mec_पूर्णांक_cntl);
		अवरोध;
	हाल AMDGPU_IRQ_STATE_ENABLE:
		mec_पूर्णांक_cntl = RREG32(mec_पूर्णांक_cntl_reg);
		mec_पूर्णांक_cntl |= CP_INT_CNTL_RING0__TIME_STAMP_INT_ENABLE_MASK;
		WREG32(mec_पूर्णांक_cntl_reg, mec_पूर्णांक_cntl);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक gfx_v7_0_set_priv_reg_fault_state(काष्ठा amdgpu_device *adev,
					     काष्ठा amdgpu_irq_src *src,
					     अचिन्हित type,
					     क्रमागत amdgpu_पूर्णांकerrupt_state state)
अणु
	u32 cp_पूर्णांक_cntl;

	चयन (state) अणु
	हाल AMDGPU_IRQ_STATE_DISABLE:
		cp_पूर्णांक_cntl = RREG32(mmCP_INT_CNTL_RING0);
		cp_पूर्णांक_cntl &= ~CP_INT_CNTL_RING0__PRIV_REG_INT_ENABLE_MASK;
		WREG32(mmCP_INT_CNTL_RING0, cp_पूर्णांक_cntl);
		अवरोध;
	हाल AMDGPU_IRQ_STATE_ENABLE:
		cp_पूर्णांक_cntl = RREG32(mmCP_INT_CNTL_RING0);
		cp_पूर्णांक_cntl |= CP_INT_CNTL_RING0__PRIV_REG_INT_ENABLE_MASK;
		WREG32(mmCP_INT_CNTL_RING0, cp_पूर्णांक_cntl);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gfx_v7_0_set_priv_inst_fault_state(काष्ठा amdgpu_device *adev,
					      काष्ठा amdgpu_irq_src *src,
					      अचिन्हित type,
					      क्रमागत amdgpu_पूर्णांकerrupt_state state)
अणु
	u32 cp_पूर्णांक_cntl;

	चयन (state) अणु
	हाल AMDGPU_IRQ_STATE_DISABLE:
		cp_पूर्णांक_cntl = RREG32(mmCP_INT_CNTL_RING0);
		cp_पूर्णांक_cntl &= ~CP_INT_CNTL_RING0__PRIV_INSTR_INT_ENABLE_MASK;
		WREG32(mmCP_INT_CNTL_RING0, cp_पूर्णांक_cntl);
		अवरोध;
	हाल AMDGPU_IRQ_STATE_ENABLE:
		cp_पूर्णांक_cntl = RREG32(mmCP_INT_CNTL_RING0);
		cp_पूर्णांक_cntl |= CP_INT_CNTL_RING0__PRIV_INSTR_INT_ENABLE_MASK;
		WREG32(mmCP_INT_CNTL_RING0, cp_पूर्णांक_cntl);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gfx_v7_0_set_eop_पूर्णांकerrupt_state(काष्ठा amdgpu_device *adev,
					    काष्ठा amdgpu_irq_src *src,
					    अचिन्हित type,
					    क्रमागत amdgpu_पूर्णांकerrupt_state state)
अणु
	चयन (type) अणु
	हाल AMDGPU_CP_IRQ_GFX_ME0_PIPE0_EOP:
		gfx_v7_0_set_gfx_eop_पूर्णांकerrupt_state(adev, state);
		अवरोध;
	हाल AMDGPU_CP_IRQ_COMPUTE_MEC1_PIPE0_EOP:
		gfx_v7_0_set_compute_eop_पूर्णांकerrupt_state(adev, 1, 0, state);
		अवरोध;
	हाल AMDGPU_CP_IRQ_COMPUTE_MEC1_PIPE1_EOP:
		gfx_v7_0_set_compute_eop_पूर्णांकerrupt_state(adev, 1, 1, state);
		अवरोध;
	हाल AMDGPU_CP_IRQ_COMPUTE_MEC1_PIPE2_EOP:
		gfx_v7_0_set_compute_eop_पूर्णांकerrupt_state(adev, 1, 2, state);
		अवरोध;
	हाल AMDGPU_CP_IRQ_COMPUTE_MEC1_PIPE3_EOP:
		gfx_v7_0_set_compute_eop_पूर्णांकerrupt_state(adev, 1, 3, state);
		अवरोध;
	हाल AMDGPU_CP_IRQ_COMPUTE_MEC2_PIPE0_EOP:
		gfx_v7_0_set_compute_eop_पूर्णांकerrupt_state(adev, 2, 0, state);
		अवरोध;
	हाल AMDGPU_CP_IRQ_COMPUTE_MEC2_PIPE1_EOP:
		gfx_v7_0_set_compute_eop_पूर्णांकerrupt_state(adev, 2, 1, state);
		अवरोध;
	हाल AMDGPU_CP_IRQ_COMPUTE_MEC2_PIPE2_EOP:
		gfx_v7_0_set_compute_eop_पूर्णांकerrupt_state(adev, 2, 2, state);
		अवरोध;
	हाल AMDGPU_CP_IRQ_COMPUTE_MEC2_PIPE3_EOP:
		gfx_v7_0_set_compute_eop_पूर्णांकerrupt_state(adev, 2, 3, state);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक gfx_v7_0_eop_irq(काष्ठा amdgpu_device *adev,
			    काष्ठा amdgpu_irq_src *source,
			    काष्ठा amdgpu_iv_entry *entry)
अणु
	u8 me_id, pipe_id;
	काष्ठा amdgpu_ring *ring;
	पूर्णांक i;

	DRM_DEBUG("IH: CP EOP\n");
	me_id = (entry->ring_id & 0x0c) >> 2;
	pipe_id = (entry->ring_id & 0x03) >> 0;
	चयन (me_id) अणु
	हाल 0:
		amdgpu_fence_process(&adev->gfx.gfx_ring[0]);
		अवरोध;
	हाल 1:
	हाल 2:
		क्रम (i = 0; i < adev->gfx.num_compute_rings; i++) अणु
			ring = &adev->gfx.compute_ring[i];
			अगर ((ring->me == me_id) && (ring->pipe == pipe_id))
				amdgpu_fence_process(ring);
		पूर्ण
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम gfx_v7_0_fault(काष्ठा amdgpu_device *adev,
			   काष्ठा amdgpu_iv_entry *entry)
अणु
	काष्ठा amdgpu_ring *ring;
	u8 me_id, pipe_id;
	पूर्णांक i;

	me_id = (entry->ring_id & 0x0c) >> 2;
	pipe_id = (entry->ring_id & 0x03) >> 0;
	चयन (me_id) अणु
	हाल 0:
		drm_sched_fault(&adev->gfx.gfx_ring[0].sched);
		अवरोध;
	हाल 1:
	हाल 2:
		क्रम (i = 0; i < adev->gfx.num_compute_rings; i++) अणु
			ring = &adev->gfx.compute_ring[i];
			अगर ((ring->me == me_id) && (ring->pipe == pipe_id))
				drm_sched_fault(&ring->sched);
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक gfx_v7_0_priv_reg_irq(काष्ठा amdgpu_device *adev,
				 काष्ठा amdgpu_irq_src *source,
				 काष्ठा amdgpu_iv_entry *entry)
अणु
	DRM_ERROR("Illegal register access in command stream\n");
	gfx_v7_0_fault(adev, entry);
	वापस 0;
पूर्ण

अटल पूर्णांक gfx_v7_0_priv_inst_irq(काष्ठा amdgpu_device *adev,
				  काष्ठा amdgpu_irq_src *source,
				  काष्ठा amdgpu_iv_entry *entry)
अणु
	DRM_ERROR("Illegal instruction in command stream\n");
	// XXX soft reset the gfx block only
	gfx_v7_0_fault(adev, entry);
	वापस 0;
पूर्ण

अटल पूर्णांक gfx_v7_0_set_घड़ीgating_state(व्योम *handle,
					  क्रमागत amd_घड़ीgating_state state)
अणु
	bool gate = false;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (state == AMD_CG_STATE_GATE)
		gate = true;

	gfx_v7_0_enable_gui_idle_पूर्णांकerrupt(adev, false);
	/* order matters! */
	अगर (gate) अणु
		gfx_v7_0_enable_mgcg(adev, true);
		gfx_v7_0_enable_cgcg(adev, true);
	पूर्ण अन्यथा अणु
		gfx_v7_0_enable_cgcg(adev, false);
		gfx_v7_0_enable_mgcg(adev, false);
	पूर्ण
	gfx_v7_0_enable_gui_idle_पूर्णांकerrupt(adev, true);

	वापस 0;
पूर्ण

अटल पूर्णांक gfx_v7_0_set_घातergating_state(व्योम *handle,
					  क्रमागत amd_घातergating_state state)
अणु
	bool gate = false;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (state == AMD_PG_STATE_GATE)
		gate = true;

	अगर (adev->pg_flags & (AMD_PG_SUPPORT_GFX_PG |
			      AMD_PG_SUPPORT_GFX_SMG |
			      AMD_PG_SUPPORT_GFX_DMG |
			      AMD_PG_SUPPORT_CP |
			      AMD_PG_SUPPORT_GDS |
			      AMD_PG_SUPPORT_RLC_SMU_HS)) अणु
		gfx_v7_0_update_gfx_pg(adev, gate);
		अगर (adev->pg_flags & AMD_PG_SUPPORT_GFX_PG) अणु
			gfx_v7_0_enable_cp_pg(adev, gate);
			gfx_v7_0_enable_gds_pg(adev, gate);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम gfx_v7_0_emit_mem_sync(काष्ठा amdgpu_ring *ring)
अणु
	amdgpu_ring_ग_लिखो(ring, PACKET3(PACKET3_SURFACE_SYNC, 3));
	amdgpu_ring_ग_लिखो(ring, PACKET3_TCL1_ACTION_ENA |
			  PACKET3_TC_ACTION_ENA |
			  PACKET3_SH_KCACHE_ACTION_ENA |
			  PACKET3_SH_ICACHE_ACTION_ENA);  /* CP_COHER_CNTL */
	amdgpu_ring_ग_लिखो(ring, 0xffffffff);  /* CP_COHER_SIZE */
	amdgpu_ring_ग_लिखो(ring, 0);  /* CP_COHER_BASE */
	amdgpu_ring_ग_लिखो(ring, 0x0000000A); /* poll पूर्णांकerval */
पूर्ण

अटल व्योम gfx_v7_0_emit_mem_sync_compute(काष्ठा amdgpu_ring *ring)
अणु
	amdgpu_ring_ग_लिखो(ring, PACKET3(PACKET3_ACQUIRE_MEM, 5));
	amdgpu_ring_ग_लिखो(ring, PACKET3_TCL1_ACTION_ENA |
			  PACKET3_TC_ACTION_ENA |
			  PACKET3_SH_KCACHE_ACTION_ENA |
			  PACKET3_SH_ICACHE_ACTION_ENA);  /* CP_COHER_CNTL */
	amdgpu_ring_ग_लिखो(ring, 0xffffffff);	/* CP_COHER_SIZE */
	amdgpu_ring_ग_लिखो(ring, 0xff);		/* CP_COHER_SIZE_HI */
	amdgpu_ring_ग_लिखो(ring, 0);		/* CP_COHER_BASE */
	amdgpu_ring_ग_लिखो(ring, 0);		/* CP_COHER_BASE_HI */
	amdgpu_ring_ग_लिखो(ring, 0x0000000A);	/* poll पूर्णांकerval */
पूर्ण

अटल स्थिर काष्ठा amd_ip_funcs gfx_v7_0_ip_funcs = अणु
	.name = "gfx_v7_0",
	.early_init = gfx_v7_0_early_init,
	.late_init = gfx_v7_0_late_init,
	.sw_init = gfx_v7_0_sw_init,
	.sw_fini = gfx_v7_0_sw_fini,
	.hw_init = gfx_v7_0_hw_init,
	.hw_fini = gfx_v7_0_hw_fini,
	.suspend = gfx_v7_0_suspend,
	.resume = gfx_v7_0_resume,
	.is_idle = gfx_v7_0_is_idle,
	.रुको_क्रम_idle = gfx_v7_0_रुको_क्रम_idle,
	.soft_reset = gfx_v7_0_soft_reset,
	.set_घड़ीgating_state = gfx_v7_0_set_घड़ीgating_state,
	.set_घातergating_state = gfx_v7_0_set_घातergating_state,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_ring_funcs gfx_v7_0_ring_funcs_gfx = अणु
	.type = AMDGPU_RING_TYPE_GFX,
	.align_mask = 0xff,
	.nop = PACKET3(PACKET3_NOP, 0x3FFF),
	.support_64bit_ptrs = false,
	.get_rptr = gfx_v7_0_ring_get_rptr,
	.get_wptr = gfx_v7_0_ring_get_wptr_gfx,
	.set_wptr = gfx_v7_0_ring_set_wptr_gfx,
	.emit_frame_size =
		20 + /* gfx_v7_0_ring_emit_gds_चयन */
		7 + /* gfx_v7_0_ring_emit_hdp_flush */
		5 + /* hdp invalidate */
		12 + 12 + 12 + /* gfx_v7_0_ring_emit_fence_gfx x3 क्रम user fence, vm fence */
		7 + 4 + /* gfx_v7_0_ring_emit_pipeline_sync */
		CIK_FLUSH_GPU_TLB_NUM_WREG * 5 + 7 + 6 + /* gfx_v7_0_ring_emit_vm_flush */
		3 + 4 + /* gfx_v7_ring_emit_cntxcntl including vgt flush*/
		5, /* SURFACE_SYNC */
	.emit_ib_size = 4, /* gfx_v7_0_ring_emit_ib_gfx */
	.emit_ib = gfx_v7_0_ring_emit_ib_gfx,
	.emit_fence = gfx_v7_0_ring_emit_fence_gfx,
	.emit_pipeline_sync = gfx_v7_0_ring_emit_pipeline_sync,
	.emit_vm_flush = gfx_v7_0_ring_emit_vm_flush,
	.emit_gds_चयन = gfx_v7_0_ring_emit_gds_चयन,
	.emit_hdp_flush = gfx_v7_0_ring_emit_hdp_flush,
	.test_ring = gfx_v7_0_ring_test_ring,
	.test_ib = gfx_v7_0_ring_test_ib,
	.insert_nop = amdgpu_ring_insert_nop,
	.pad_ib = amdgpu_ring_generic_pad_ib,
	.emit_cntxcntl = gfx_v7_ring_emit_cntxcntl,
	.emit_wreg = gfx_v7_0_ring_emit_wreg,
	.soft_recovery = gfx_v7_0_ring_soft_recovery,
	.emit_mem_sync = gfx_v7_0_emit_mem_sync,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_ring_funcs gfx_v7_0_ring_funcs_compute = अणु
	.type = AMDGPU_RING_TYPE_COMPUTE,
	.align_mask = 0xff,
	.nop = PACKET3(PACKET3_NOP, 0x3FFF),
	.support_64bit_ptrs = false,
	.get_rptr = gfx_v7_0_ring_get_rptr,
	.get_wptr = gfx_v7_0_ring_get_wptr_compute,
	.set_wptr = gfx_v7_0_ring_set_wptr_compute,
	.emit_frame_size =
		20 + /* gfx_v7_0_ring_emit_gds_चयन */
		7 + /* gfx_v7_0_ring_emit_hdp_flush */
		5 + /* hdp invalidate */
		7 + /* gfx_v7_0_ring_emit_pipeline_sync */
		CIK_FLUSH_GPU_TLB_NUM_WREG * 5 + 7 + /* gfx_v7_0_ring_emit_vm_flush */
		7 + 7 + 7 + /* gfx_v7_0_ring_emit_fence_compute x3 क्रम user fence, vm fence */
		7, /* gfx_v7_0_emit_mem_sync_compute */
	.emit_ib_size =	7, /* gfx_v7_0_ring_emit_ib_compute */
	.emit_ib = gfx_v7_0_ring_emit_ib_compute,
	.emit_fence = gfx_v7_0_ring_emit_fence_compute,
	.emit_pipeline_sync = gfx_v7_0_ring_emit_pipeline_sync,
	.emit_vm_flush = gfx_v7_0_ring_emit_vm_flush,
	.emit_gds_चयन = gfx_v7_0_ring_emit_gds_चयन,
	.emit_hdp_flush = gfx_v7_0_ring_emit_hdp_flush,
	.test_ring = gfx_v7_0_ring_test_ring,
	.test_ib = gfx_v7_0_ring_test_ib,
	.insert_nop = amdgpu_ring_insert_nop,
	.pad_ib = amdgpu_ring_generic_pad_ib,
	.emit_wreg = gfx_v7_0_ring_emit_wreg,
	.emit_mem_sync = gfx_v7_0_emit_mem_sync_compute,
पूर्ण;

अटल व्योम gfx_v7_0_set_ring_funcs(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adev->gfx.num_gfx_rings; i++)
		adev->gfx.gfx_ring[i].funcs = &gfx_v7_0_ring_funcs_gfx;
	क्रम (i = 0; i < adev->gfx.num_compute_rings; i++)
		adev->gfx.compute_ring[i].funcs = &gfx_v7_0_ring_funcs_compute;
पूर्ण

अटल स्थिर काष्ठा amdgpu_irq_src_funcs gfx_v7_0_eop_irq_funcs = अणु
	.set = gfx_v7_0_set_eop_पूर्णांकerrupt_state,
	.process = gfx_v7_0_eop_irq,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_irq_src_funcs gfx_v7_0_priv_reg_irq_funcs = अणु
	.set = gfx_v7_0_set_priv_reg_fault_state,
	.process = gfx_v7_0_priv_reg_irq,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_irq_src_funcs gfx_v7_0_priv_inst_irq_funcs = अणु
	.set = gfx_v7_0_set_priv_inst_fault_state,
	.process = gfx_v7_0_priv_inst_irq,
पूर्ण;

अटल व्योम gfx_v7_0_set_irq_funcs(काष्ठा amdgpu_device *adev)
अणु
	adev->gfx.eop_irq.num_types = AMDGPU_CP_IRQ_LAST;
	adev->gfx.eop_irq.funcs = &gfx_v7_0_eop_irq_funcs;

	adev->gfx.priv_reg_irq.num_types = 1;
	adev->gfx.priv_reg_irq.funcs = &gfx_v7_0_priv_reg_irq_funcs;

	adev->gfx.priv_inst_irq.num_types = 1;
	adev->gfx.priv_inst_irq.funcs = &gfx_v7_0_priv_inst_irq_funcs;
पूर्ण

अटल व्योम gfx_v7_0_set_gds_init(काष्ठा amdgpu_device *adev)
अणु
	/* init asci gds info */
	adev->gds.gds_size = RREG32(mmGDS_VMID0_SIZE);
	adev->gds.gws_size = 64;
	adev->gds.oa_size = 16;
	adev->gds.gds_compute_max_wave_id = RREG32(mmGDS_COMPUTE_MAX_WAVE_ID);
पूर्ण


अटल व्योम gfx_v7_0_get_cu_info(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i, j, k, counter, active_cu_number = 0;
	u32 mask, biपंचांगap, ao_biपंचांगap, ao_cu_mask = 0;
	काष्ठा amdgpu_cu_info *cu_info = &adev->gfx.cu_info;
	अचिन्हित disable_masks[4 * 2];
	u32 ao_cu_num;

	अगर (adev->flags & AMD_IS_APU)
		ao_cu_num = 2;
	अन्यथा
		ao_cu_num = adev->gfx.config.max_cu_per_sh;

	स_रखो(cu_info, 0, माप(*cu_info));

	amdgpu_gfx_parse_disable_cu(disable_masks, 4, 2);

	mutex_lock(&adev->grbm_idx_mutex);
	क्रम (i = 0; i < adev->gfx.config.max_shader_engines; i++) अणु
		क्रम (j = 0; j < adev->gfx.config.max_sh_per_se; j++) अणु
			mask = 1;
			ao_biपंचांगap = 0;
			counter = 0;
			gfx_v7_0_select_se_sh(adev, i, j, 0xffffffff);
			अगर (i < 4 && j < 2)
				gfx_v7_0_set_user_cu_inactive_biपंचांगap(
					adev, disable_masks[i * 2 + j]);
			biपंचांगap = gfx_v7_0_get_cu_active_biपंचांगap(adev);
			cu_info->biपंचांगap[i][j] = biपंचांगap;

			क्रम (k = 0; k < adev->gfx.config.max_cu_per_sh; k ++) अणु
				अगर (biपंचांगap & mask) अणु
					अगर (counter < ao_cu_num)
						ao_biपंचांगap |= mask;
					counter ++;
				पूर्ण
				mask <<= 1;
			पूर्ण
			active_cu_number += counter;
			अगर (i < 2 && j < 2)
				ao_cu_mask |= (ao_biपंचांगap << (i * 16 + j * 8));
			cu_info->ao_cu_biपंचांगap[i][j] = ao_biपंचांगap;
		पूर्ण
	पूर्ण
	gfx_v7_0_select_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff);
	mutex_unlock(&adev->grbm_idx_mutex);

	cu_info->number = active_cu_number;
	cu_info->ao_cu_mask = ao_cu_mask;
	cu_info->simd_per_cu = NUM_SIMD_PER_CU;
	cu_info->max_waves_per_simd = 10;
	cu_info->max_scratch_slots_per_cu = 32;
	cu_info->wave_front_size = 64;
	cu_info->lds_size = 64;
पूर्ण

स्थिर काष्ठा amdgpu_ip_block_version gfx_v7_1_ip_block =
अणु
	.type = AMD_IP_BLOCK_TYPE_GFX,
	.major = 7,
	.minor = 1,
	.rev = 0,
	.funcs = &gfx_v7_0_ip_funcs,
पूर्ण;

स्थिर काष्ठा amdgpu_ip_block_version gfx_v7_2_ip_block =
अणु
	.type = AMD_IP_BLOCK_TYPE_GFX,
	.major = 7,
	.minor = 2,
	.rev = 0,
	.funcs = &gfx_v7_0_ip_funcs,
पूर्ण;

स्थिर काष्ठा amdgpu_ip_block_version gfx_v7_3_ip_block =
अणु
	.type = AMD_IP_BLOCK_TYPE_GFX,
	.major = 7,
	.minor = 3,
	.rev = 0,
	.funcs = &gfx_v7_0_ip_funcs,
पूर्ण;
