<शैली गुरु>
/*
 * Copyright 2013 Advanced Micro Devices, Inc.
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

#समावेश <linux/module.h>
#समावेश <linux/pci.h>

#समावेश "amdgpu.h"
#समावेश "amdgpu_pm.h"
#समावेश "amdgpu_dpm.h"
#समावेश "amdgpu_atombios.h"
#समावेश "amd_pcie.h"
#समावेश "sid.h"
#समावेश "r600_dpm.h"
#समावेश "si_dpm.h"
#समावेश "atom.h"
#समावेश "../include/pptable.h"
#समावेश <linux/math64.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/firmware.h>

#घोषणा MC_CG_ARB_FREQ_F0           0x0a
#घोषणा MC_CG_ARB_FREQ_F1           0x0b
#घोषणा MC_CG_ARB_FREQ_F2           0x0c
#घोषणा MC_CG_ARB_FREQ_F3           0x0d

#घोषणा SMC_RAM_END                 0x20000

#घोषणा SCLK_MIN_DEEPSLEEP_FREQ     1350


/* माप(ATOM_PPLIB_EXTENDEDHEADER) */
#घोषणा SIZE_OF_ATOM_PPLIB_EXTENDEDHEADER_V2 12
#घोषणा SIZE_OF_ATOM_PPLIB_EXTENDEDHEADER_V3 14
#घोषणा SIZE_OF_ATOM_PPLIB_EXTENDEDHEADER_V4 16
#घोषणा SIZE_OF_ATOM_PPLIB_EXTENDEDHEADER_V5 18
#घोषणा SIZE_OF_ATOM_PPLIB_EXTENDEDHEADER_V6 20
#घोषणा SIZE_OF_ATOM_PPLIB_EXTENDEDHEADER_V7 22

#घोषणा BIOS_SCRATCH_4                                    0x5cd

MODULE_FIRMWARE("amdgpu/tahiti_smc.bin");
MODULE_FIRMWARE("amdgpu/pitcairn_smc.bin");
MODULE_FIRMWARE("amdgpu/pitcairn_k_smc.bin");
MODULE_FIRMWARE("amdgpu/verde_smc.bin");
MODULE_FIRMWARE("amdgpu/verde_k_smc.bin");
MODULE_FIRMWARE("amdgpu/oland_smc.bin");
MODULE_FIRMWARE("amdgpu/oland_k_smc.bin");
MODULE_FIRMWARE("amdgpu/hainan_smc.bin");
MODULE_FIRMWARE("amdgpu/hainan_k_smc.bin");
MODULE_FIRMWARE("amdgpu/banks_k_2_smc.bin");

अटल स्थिर काष्ठा amd_pm_funcs si_dpm_funcs;

जोड़ घातer_info अणु
	काष्ठा _ATOM_POWERPLAY_INFO info;
	काष्ठा _ATOM_POWERPLAY_INFO_V2 info_2;
	काष्ठा _ATOM_POWERPLAY_INFO_V3 info_3;
	काष्ठा _ATOM_PPLIB_POWERPLAYTABLE pplib;
	काष्ठा _ATOM_PPLIB_POWERPLAYTABLE2 pplib2;
	काष्ठा _ATOM_PPLIB_POWERPLAYTABLE3 pplib3;
	काष्ठा _ATOM_PPLIB_POWERPLAYTABLE4 pplib4;
	काष्ठा _ATOM_PPLIB_POWERPLAYTABLE5 pplib5;
पूर्ण;

जोड़ fan_info अणु
	काष्ठा _ATOM_PPLIB_FANTABLE fan;
	काष्ठा _ATOM_PPLIB_FANTABLE2 fan2;
	काष्ठा _ATOM_PPLIB_FANTABLE3 fan3;
पूर्ण;

जोड़ pplib_घड़ी_info अणु
	काष्ठा _ATOM_PPLIB_R600_CLOCK_INFO r600;
	काष्ठा _ATOM_PPLIB_RS780_CLOCK_INFO rs780;
	काष्ठा _ATOM_PPLIB_EVERGREEN_CLOCK_INFO evergreen;
	काष्ठा _ATOM_PPLIB_SUMO_CLOCK_INFO sumo;
	काष्ठा _ATOM_PPLIB_SI_CLOCK_INFO si;
पूर्ण;

अटल स्थिर u32 r600_utc[R600_PM_NUMBER_OF_TC] =
अणु
	R600_UTC_DFLT_00,
	R600_UTC_DFLT_01,
	R600_UTC_DFLT_02,
	R600_UTC_DFLT_03,
	R600_UTC_DFLT_04,
	R600_UTC_DFLT_05,
	R600_UTC_DFLT_06,
	R600_UTC_DFLT_07,
	R600_UTC_DFLT_08,
	R600_UTC_DFLT_09,
	R600_UTC_DFLT_10,
	R600_UTC_DFLT_11,
	R600_UTC_DFLT_12,
	R600_UTC_DFLT_13,
	R600_UTC_DFLT_14,
पूर्ण;

अटल स्थिर u32 r600_dtc[R600_PM_NUMBER_OF_TC] =
अणु
	R600_DTC_DFLT_00,
	R600_DTC_DFLT_01,
	R600_DTC_DFLT_02,
	R600_DTC_DFLT_03,
	R600_DTC_DFLT_04,
	R600_DTC_DFLT_05,
	R600_DTC_DFLT_06,
	R600_DTC_DFLT_07,
	R600_DTC_DFLT_08,
	R600_DTC_DFLT_09,
	R600_DTC_DFLT_10,
	R600_DTC_DFLT_11,
	R600_DTC_DFLT_12,
	R600_DTC_DFLT_13,
	R600_DTC_DFLT_14,
पूर्ण;

अटल स्थिर काष्ठा si_cac_config_reg cac_weights_tahiti[] =
अणु
	अणु 0x0, 0x0000ffff, 0, 0xc, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x0, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1, 0x0000ffff, 0, 0x101, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1, 0xffff0000, 16, 0xc, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x2, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x3, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x3, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x4, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x4, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x5, 0x0000ffff, 0, 0x8fc, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x5, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x6, 0x0000ffff, 0, 0x95, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x6, 0xffff0000, 16, 0x34e, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x18f, 0x0000ffff, 0, 0x1a1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x7, 0x0000ffff, 0, 0xda, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x7, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x8, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x8, 0xffff0000, 16, 0x46, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x9, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xa, 0x0000ffff, 0, 0x208, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xb, 0x0000ffff, 0, 0xe7, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xb, 0xffff0000, 16, 0x948, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xc, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xd, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xd, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xe, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xf, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xf, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x10, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x10, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x11, 0x0000ffff, 0, 0x167, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x11, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x12, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x13, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x13, 0xffff0000, 16, 0x35, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x14, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x15, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x15, 0xffff0000, 16, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x4e, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x16, 0x0000ffff, 0, 0x31, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x16, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x17, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x18, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x18, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x19, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x19, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1a, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1a, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1b, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1b, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1c, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1c, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1d, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1d, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1e, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1e, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1f, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1f, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x20, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x6d, 0x0000ffff, 0, 0x18e, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xFFFFFFFF पूर्ण
पूर्ण;

अटल स्थिर काष्ठा si_cac_config_reg lcac_tahiti[] =
अणु
	अणु 0x143, 0x0001fffe, 1, 0x3, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x143, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x146, 0x0001fffe, 1, 0x3, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x146, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x149, 0x0001fffe, 1, 0x3, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x149, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x14c, 0x0001fffe, 1, 0x3, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x14c, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x98, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x98, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x9b, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x9b, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x9e, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x9e, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x101, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x101, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x104, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x104, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x107, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x107, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x10a, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x10a, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x10d, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x10d, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x8c, 0x0001fffe, 1, 0x8, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x8c, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x8f, 0x0001fffe, 1, 0x8, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x8f, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x92, 0x0001fffe, 1, 0x8, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x92, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x95, 0x0001fffe, 1, 0x8, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x95, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x14f, 0x0001fffe, 1, 0x8, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x14f, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x152, 0x0001fffe, 1, 0x8, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x152, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x155, 0x0001fffe, 1, 0x8, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x155, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x158, 0x0001fffe, 1, 0x8, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x158, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x110, 0x0001fffe, 1, 0x8, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x110, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x113, 0x0001fffe, 1, 0x8, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x113, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x116, 0x0001fffe, 1, 0x8, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x116, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x119, 0x0001fffe, 1, 0x8, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x119, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x11c, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x11c, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x11f, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x11f, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x122, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x122, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x125, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x125, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x128, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x128, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x12b, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x12b, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x15b, 0x0001fffe, 1, 0x4, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x15b, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x15e, 0x0001fffe, 1, 0x4, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x15e, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x161, 0x0001fffe, 1, 0x4, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x161, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x164, 0x0001fffe, 1, 0x4, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x164, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x167, 0x0001fffe, 1, 0x4, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x167, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x16a, 0x0001fffe, 1, 0x4, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x16a, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x16d, 0x0001fffe, 1, 0x6, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x16d, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x170, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x170, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x173, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x173, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x176, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x176, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x179, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x179, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x17c, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x17c, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x17f, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x17f, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xFFFFFFFF पूर्ण

पूर्ण;

अटल स्थिर काष्ठा si_cac_config_reg cac_override_tahiti[] =
अणु
	अणु 0xFFFFFFFF पूर्ण
पूर्ण;

अटल स्थिर काष्ठा si_घातertune_data घातertune_data_tahiti =
अणु
	((1 << 16) | 27027),
	6,
	0,
	4,
	95,
	अणु
		0UL,
		0UL,
		4521550UL,
		309631529UL,
		-1270850L,
		4513710L,
		40
	पूर्ण,
	595000000UL,
	12,
	अणु
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0
	पूर्ण,
	true
पूर्ण;

अटल स्थिर काष्ठा si_dte_data dte_data_tahiti =
अणु
	अणु 1159409, 0, 0, 0, 0 पूर्ण,
	अणु 777, 0, 0, 0, 0 पूर्ण,
	2,
	54000,
	127000,
	25,
	2,
	10,
	13,
	अणु 27, 31, 35, 39, 43, 47, 54, 61, 67, 74, 81, 88, 95, 0, 0, 0 पूर्ण,
	अणु 240888759, 221057860, 235370597, 162287531, 158510299, 131423027, 116673180, 103067515, 87941937, 76209048, 68209175, 64090048, 58301890, 0, 0, 0 पूर्ण,
	अणु 12024, 11189, 11451, 8411, 7939, 6666, 5681, 4905, 4241, 3720, 3354, 3122, 2890, 0, 0, 0 पूर्ण,
	85,
	false
पूर्ण;

अटल स्थिर काष्ठा si_dte_data dte_data_tahiti_pro =
अणु
	अणु 0x1E8480, 0x3D0900, 0x989680, 0x2625A00, 0x0 पूर्ण,
	अणु 0x0, 0x0, 0x0, 0x0, 0x0 पूर्ण,
	5,
	45000,
	100,
	0xA,
	1,
	0,
	0x10,
	अणु 0x96, 0xB4, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF पूर्ण,
	अणु 0x895440, 0x3D0900, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680 पूर्ण,
	अणु 0x7D0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 पूर्ण,
	90,
	true
पूर्ण;

अटल स्थिर काष्ठा si_dte_data dte_data_new_zealand =
अणु
	अणु 0x1E8480, 0x3D0900, 0x989680, 0x2625A00, 0 पूर्ण,
	अणु 0x29B, 0x3E9, 0x537, 0x7D2, 0 पूर्ण,
	0x5,
	0xAFC8,
	0x69,
	0x32,
	1,
	0,
	0x10,
	अणु 0x82, 0xA0, 0xB4, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE पूर्ण,
	अणु 0x895440, 0x3D0900, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680 पूर्ण,
	अणु 0xDAC, 0x1388, 0x685, 0x685, 0x685, 0x685, 0x685, 0x685, 0x685, 0x685, 0x685, 0x685, 0x685, 0x685, 0x685, 0x685 पूर्ण,
	85,
	true
पूर्ण;

अटल स्थिर काष्ठा si_dte_data dte_data_aruba_pro =
अणु
	अणु 0x1E8480, 0x3D0900, 0x989680, 0x2625A00, 0x0 पूर्ण,
	अणु 0x0, 0x0, 0x0, 0x0, 0x0 पूर्ण,
	5,
	45000,
	100,
	0xA,
	1,
	0,
	0x10,
	अणु 0x96, 0xB4, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF पूर्ण,
	अणु 0x895440, 0x3D0900, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680 पूर्ण,
	अणु 0x1000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 पूर्ण,
	90,
	true
पूर्ण;

अटल स्थिर काष्ठा si_dte_data dte_data_malta =
अणु
	अणु 0x1E8480, 0x3D0900, 0x989680, 0x2625A00, 0x0 पूर्ण,
	अणु 0x0, 0x0, 0x0, 0x0, 0x0 पूर्ण,
	5,
	45000,
	100,
	0xA,
	1,
	0,
	0x10,
	अणु 0x96, 0xB4, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF पूर्ण,
	अणु 0x895440, 0x3D0900, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680 पूर्ण,
	अणु 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 पूर्ण,
	90,
	true
पूर्ण;

अटल स्थिर काष्ठा si_cac_config_reg cac_weights_pitcairn[] =
अणु
	अणु 0x0, 0x0000ffff, 0, 0x8a, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x0, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1, 0xffff0000, 16, 0x24d, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x2, 0x0000ffff, 0, 0x19, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x3, 0x0000ffff, 0, 0x118, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x3, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x4, 0x0000ffff, 0, 0x76, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x4, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x5, 0x0000ffff, 0, 0xc11, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x5, 0xffff0000, 16, 0x7f3, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x6, 0x0000ffff, 0, 0x403, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x6, 0xffff0000, 16, 0x367, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x18f, 0x0000ffff, 0, 0x4c9, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x7, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x7, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x8, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x8, 0xffff0000, 16, 0x45d, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x9, 0x0000ffff, 0, 0x36d, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xa, 0x0000ffff, 0, 0x534, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xb, 0x0000ffff, 0, 0x5da, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xb, 0xffff0000, 16, 0x880, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xc, 0x0000ffff, 0, 0x201, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xd, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xd, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xe, 0x0000ffff, 0, 0x9f, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xf, 0x0000ffff, 0, 0x1f, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xf, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x10, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x10, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x11, 0x0000ffff, 0, 0x5de, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x11, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x12, 0x0000ffff, 0, 0x7b, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x13, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x13, 0xffff0000, 16, 0x13, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x14, 0x0000ffff, 0, 0xf9, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x15, 0x0000ffff, 0, 0x66, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x15, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x4e, 0x0000ffff, 0, 0x13, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x16, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x16, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x17, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x18, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x18, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x19, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x19, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1a, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1a, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1b, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1b, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1c, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1c, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1d, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1d, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1e, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1e, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1f, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1f, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x20, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x6d, 0x0000ffff, 0, 0x186, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xFFFFFFFF पूर्ण
पूर्ण;

अटल स्थिर काष्ठा si_cac_config_reg lcac_pitcairn[] =
अणु
	अणु 0x98, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x98, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x104, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x104, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x110, 0x0001fffe, 1, 0x5, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x110, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x14f, 0x0001fffe, 1, 0x5, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x14f, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x8c, 0x0001fffe, 1, 0x5, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x8c, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x143, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x143, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x9b, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x9b, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x107, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x107, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x113, 0x0001fffe, 1, 0x5, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x113, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x152, 0x0001fffe, 1, 0x5, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x152, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x8f, 0x0001fffe, 1, 0x5, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x8f, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x146, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x146, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x9e, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x9e, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x10a, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x10a, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x116, 0x0001fffe, 1, 0x5, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x116, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x155, 0x0001fffe, 1, 0x5, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x155, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x92, 0x0001fffe, 1, 0x5, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x92, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x149, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x149, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x101, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x101, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x10d, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x10d, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x119, 0x0001fffe, 1, 0x5, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x119, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x158, 0x0001fffe, 1, 0x5, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x158, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x95, 0x0001fffe, 1, 0x5, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x95, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x14c, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x14c, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x11c, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x11c, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x11f, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x11f, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x122, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x122, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x125, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x125, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x128, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x128, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x12b, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x12b, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x164, 0x0001fffe, 1, 0x4, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x164, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x167, 0x0001fffe, 1, 0x4, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x167, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x16a, 0x0001fffe, 1, 0x4, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x16a, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x15e, 0x0001fffe, 1, 0x4, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x15e, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x161, 0x0001fffe, 1, 0x4, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x161, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x15b, 0x0001fffe, 1, 0x4, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x15b, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x16d, 0x0001fffe, 1, 0x4, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x16d, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x170, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x170, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x173, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x173, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x176, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x176, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x179, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x179, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x17c, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x17c, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x17f, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x17f, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xFFFFFFFF पूर्ण
पूर्ण;

अटल स्थिर काष्ठा si_cac_config_reg cac_override_pitcairn[] =
अणु
    अणु 0xFFFFFFFF पूर्ण
पूर्ण;

अटल स्थिर काष्ठा si_घातertune_data घातertune_data_pitcairn =
अणु
	((1 << 16) | 27027),
	5,
	0,
	6,
	100,
	अणु
		51600000UL,
		1800000UL,
		7194395UL,
		309631529UL,
		-1270850L,
		4513710L,
		100
	पूर्ण,
	117830498UL,
	12,
	अणु
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0
	पूर्ण,
	true
पूर्ण;

अटल स्थिर काष्ठा si_dte_data dte_data_pitcairn =
अणु
	अणु 0, 0, 0, 0, 0 पूर्ण,
	अणु 0, 0, 0, 0, 0 पूर्ण,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	अणु 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 पूर्ण,
	अणु 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 पूर्ण,
	अणु 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 पूर्ण,
	0,
	false
पूर्ण;

अटल स्थिर काष्ठा si_dte_data dte_data_curacao_xt =
अणु
	अणु 0x1E8480, 0x3D0900, 0x989680, 0x2625A00, 0x0 पूर्ण,
	अणु 0x0, 0x0, 0x0, 0x0, 0x0 पूर्ण,
	5,
	45000,
	100,
	0xA,
	1,
	0,
	0x10,
	अणु 0x96, 0xB4, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF पूर्ण,
	अणु 0x895440, 0x3D0900, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680 पूर्ण,
	अणु 0x1D17, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 पूर्ण,
	90,
	true
पूर्ण;

अटल स्थिर काष्ठा si_dte_data dte_data_curacao_pro =
अणु
	अणु 0x1E8480, 0x3D0900, 0x989680, 0x2625A00, 0x0 पूर्ण,
	अणु 0x0, 0x0, 0x0, 0x0, 0x0 पूर्ण,
	5,
	45000,
	100,
	0xA,
	1,
	0,
	0x10,
	अणु 0x96, 0xB4, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF पूर्ण,
	अणु 0x895440, 0x3D0900, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680 पूर्ण,
	अणु 0x1D17, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 पूर्ण,
	90,
	true
पूर्ण;

अटल स्थिर काष्ठा si_dte_data dte_data_neptune_xt =
अणु
	अणु 0x1E8480, 0x3D0900, 0x989680, 0x2625A00, 0x0 पूर्ण,
	अणु 0x0, 0x0, 0x0, 0x0, 0x0 पूर्ण,
	5,
	45000,
	100,
	0xA,
	1,
	0,
	0x10,
	अणु 0x96, 0xB4, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF पूर्ण,
	अणु 0x895440, 0x3D0900, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680 पूर्ण,
	अणु 0x3A2F, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 पूर्ण,
	90,
	true
पूर्ण;

अटल स्थिर काष्ठा si_cac_config_reg cac_weights_chअन्यथाa_pro[] =
अणु
	अणु 0x0, 0x0000ffff, 0, 0x82, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x0, 0xffff0000, 16, 0x4F, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1, 0x0000ffff, 0, 0x153, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1, 0xffff0000, 16, 0x52, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x2, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x3, 0x0000ffff, 0, 0x135, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x3, 0xffff0000, 16, 0x4F, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x4, 0x0000ffff, 0, 0x135, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x4, 0xffff0000, 16, 0xAC, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x5, 0x0000ffff, 0, 0x118, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x5, 0xffff0000, 16, 0xBE, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x6, 0x0000ffff, 0, 0x110, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x6, 0xffff0000, 16, 0x4CD, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x18f, 0x0000ffff, 0, 0x30, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x7, 0x0000ffff, 0, 0x37, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x7, 0xffff0000, 16, 0x27, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x8, 0x0000ffff, 0, 0xC3, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x8, 0xffff0000, 16, 0x35, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x9, 0x0000ffff, 0, 0x28, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xa, 0x0000ffff, 0, 0x26C, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xb, 0x0000ffff, 0, 0x3B2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xb, 0xffff0000, 16, 0x99D, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xc, 0x0000ffff, 0, 0xA3F, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xd, 0x0000ffff, 0, 0xA, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xd, 0xffff0000, 16, 0xA, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xe, 0x0000ffff, 0, 0x5, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xf, 0x0000ffff, 0, 0x3, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xf, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x10, 0x0000ffff, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x10, 0xffff0000, 16, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x11, 0x0000ffff, 0, 0x5, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x11, 0xffff0000, 16, 0x15, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x12, 0x0000ffff, 0, 0x34, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x13, 0x0000ffff, 0, 0x4, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x13, 0xffff0000, 16, 0x4, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x14, 0x0000ffff, 0, 0x2BD, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x15, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x15, 0xffff0000, 16, 0x6, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x4e, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x16, 0x0000ffff, 0, 0x30, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x16, 0xffff0000, 16, 0x7A, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x17, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x18, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x18, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x19, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x19, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1a, 0x0000ffff, 0, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1a, 0xffff0000, 16, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1b, 0x0000ffff, 0, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1b, 0xffff0000, 16, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1c, 0x0000ffff, 0, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1c, 0xffff0000, 16, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1d, 0x0000ffff, 0, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1d, 0xffff0000, 16, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1e, 0x0000ffff, 0, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1e, 0xffff0000, 16, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1f, 0x0000ffff, 0, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1f, 0xffff0000, 16, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x20, 0x0000ffff, 0, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x6d, 0x0000ffff, 0, 0x100, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xFFFFFFFF पूर्ण
पूर्ण;

अटल स्थिर काष्ठा si_cac_config_reg cac_weights_chअन्यथाa_xt[] =
अणु
	अणु 0x0, 0x0000ffff, 0, 0x82, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x0, 0xffff0000, 16, 0x4F, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1, 0x0000ffff, 0, 0x153, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1, 0xffff0000, 16, 0x52, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x2, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x3, 0x0000ffff, 0, 0x135, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x3, 0xffff0000, 16, 0x4F, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x4, 0x0000ffff, 0, 0x135, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x4, 0xffff0000, 16, 0xAC, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x5, 0x0000ffff, 0, 0x118, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x5, 0xffff0000, 16, 0xBE, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x6, 0x0000ffff, 0, 0x110, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x6, 0xffff0000, 16, 0x4CD, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x18f, 0x0000ffff, 0, 0x30, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x7, 0x0000ffff, 0, 0x37, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x7, 0xffff0000, 16, 0x27, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x8, 0x0000ffff, 0, 0xC3, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x8, 0xffff0000, 16, 0x35, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x9, 0x0000ffff, 0, 0x28, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xa, 0x0000ffff, 0, 0x26C, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xb, 0x0000ffff, 0, 0x3B2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xb, 0xffff0000, 16, 0x99D, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xc, 0x0000ffff, 0, 0xA3F, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xd, 0x0000ffff, 0, 0xA, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xd, 0xffff0000, 16, 0xA, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xe, 0x0000ffff, 0, 0x5, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xf, 0x0000ffff, 0, 0x3, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xf, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x10, 0x0000ffff, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x10, 0xffff0000, 16, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x11, 0x0000ffff, 0, 0x5, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x11, 0xffff0000, 16, 0x15, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x12, 0x0000ffff, 0, 0x34, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x13, 0x0000ffff, 0, 0x4, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x13, 0xffff0000, 16, 0x4, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x14, 0x0000ffff, 0, 0x30A, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x15, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x15, 0xffff0000, 16, 0x6, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x4e, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x16, 0x0000ffff, 0, 0x30, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x16, 0xffff0000, 16, 0x7A, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x17, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x18, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x18, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x19, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x19, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1a, 0x0000ffff, 0, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1a, 0xffff0000, 16, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1b, 0x0000ffff, 0, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1b, 0xffff0000, 16, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1c, 0x0000ffff, 0, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1c, 0xffff0000, 16, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1d, 0x0000ffff, 0, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1d, 0xffff0000, 16, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1e, 0x0000ffff, 0, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1e, 0xffff0000, 16, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1f, 0x0000ffff, 0, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1f, 0xffff0000, 16, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x20, 0x0000ffff, 0, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x6d, 0x0000ffff, 0, 0x100, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xFFFFFFFF पूर्ण
पूर्ण;

अटल स्थिर काष्ठा si_cac_config_reg cac_weights_heathrow[] =
अणु
	अणु 0x0, 0x0000ffff, 0, 0x82, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x0, 0xffff0000, 16, 0x4F, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1, 0x0000ffff, 0, 0x153, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1, 0xffff0000, 16, 0x52, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x2, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x3, 0x0000ffff, 0, 0x135, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x3, 0xffff0000, 16, 0x4F, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x4, 0x0000ffff, 0, 0x135, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x4, 0xffff0000, 16, 0xAC, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x5, 0x0000ffff, 0, 0x118, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x5, 0xffff0000, 16, 0xBE, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x6, 0x0000ffff, 0, 0x110, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x6, 0xffff0000, 16, 0x4CD, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x18f, 0x0000ffff, 0, 0x30, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x7, 0x0000ffff, 0, 0x37, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x7, 0xffff0000, 16, 0x27, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x8, 0x0000ffff, 0, 0xC3, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x8, 0xffff0000, 16, 0x35, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x9, 0x0000ffff, 0, 0x28, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xa, 0x0000ffff, 0, 0x26C, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xb, 0x0000ffff, 0, 0x3B2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xb, 0xffff0000, 16, 0x99D, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xc, 0x0000ffff, 0, 0xA3F, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xd, 0x0000ffff, 0, 0xA, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xd, 0xffff0000, 16, 0xA, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xe, 0x0000ffff, 0, 0x5, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xf, 0x0000ffff, 0, 0x3, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xf, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x10, 0x0000ffff, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x10, 0xffff0000, 16, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x11, 0x0000ffff, 0, 0x5, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x11, 0xffff0000, 16, 0x15, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x12, 0x0000ffff, 0, 0x34, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x13, 0x0000ffff, 0, 0x4, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x13, 0xffff0000, 16, 0x4, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x14, 0x0000ffff, 0, 0x362, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x15, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x15, 0xffff0000, 16, 0x6, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x4e, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x16, 0x0000ffff, 0, 0x30, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x16, 0xffff0000, 16, 0x7A, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x17, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x18, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x18, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x19, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x19, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1a, 0x0000ffff, 0, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1a, 0xffff0000, 16, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1b, 0x0000ffff, 0, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1b, 0xffff0000, 16, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1c, 0x0000ffff, 0, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1c, 0xffff0000, 16, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1d, 0x0000ffff, 0, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1d, 0xffff0000, 16, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1e, 0x0000ffff, 0, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1e, 0xffff0000, 16, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1f, 0x0000ffff, 0, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1f, 0xffff0000, 16, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x20, 0x0000ffff, 0, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x6d, 0x0000ffff, 0, 0x100, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xFFFFFFFF पूर्ण
पूर्ण;

अटल स्थिर काष्ठा si_cac_config_reg cac_weights_cape_verde_pro[] =
अणु
	अणु 0x0, 0x0000ffff, 0, 0x82, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x0, 0xffff0000, 16, 0x4F, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1, 0x0000ffff, 0, 0x153, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1, 0xffff0000, 16, 0x52, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x2, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x3, 0x0000ffff, 0, 0x135, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x3, 0xffff0000, 16, 0x4F, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x4, 0x0000ffff, 0, 0x135, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x4, 0xffff0000, 16, 0xAC, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x5, 0x0000ffff, 0, 0x118, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x5, 0xffff0000, 16, 0xBE, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x6, 0x0000ffff, 0, 0x110, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x6, 0xffff0000, 16, 0x4CD, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x18f, 0x0000ffff, 0, 0x30, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x7, 0x0000ffff, 0, 0x37, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x7, 0xffff0000, 16, 0x27, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x8, 0x0000ffff, 0, 0xC3, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x8, 0xffff0000, 16, 0x35, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x9, 0x0000ffff, 0, 0x28, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xa, 0x0000ffff, 0, 0x26C, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xb, 0x0000ffff, 0, 0x3B2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xb, 0xffff0000, 16, 0x99D, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xc, 0x0000ffff, 0, 0xA3F, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xd, 0x0000ffff, 0, 0xA, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xd, 0xffff0000, 16, 0xA, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xe, 0x0000ffff, 0, 0x5, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xf, 0x0000ffff, 0, 0x3, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xf, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x10, 0x0000ffff, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x10, 0xffff0000, 16, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x11, 0x0000ffff, 0, 0x5, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x11, 0xffff0000, 16, 0x15, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x12, 0x0000ffff, 0, 0x34, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x13, 0x0000ffff, 0, 0x4, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x13, 0xffff0000, 16, 0x4, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x14, 0x0000ffff, 0, 0x315, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x15, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x15, 0xffff0000, 16, 0x6, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x4e, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x16, 0x0000ffff, 0, 0x30, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x16, 0xffff0000, 16, 0x7A, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x17, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x18, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x18, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x19, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x19, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1a, 0x0000ffff, 0, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1a, 0xffff0000, 16, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1b, 0x0000ffff, 0, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1b, 0xffff0000, 16, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1c, 0x0000ffff, 0, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1c, 0xffff0000, 16, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1d, 0x0000ffff, 0, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1d, 0xffff0000, 16, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1e, 0x0000ffff, 0, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1e, 0xffff0000, 16, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1f, 0x0000ffff, 0, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1f, 0xffff0000, 16, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x20, 0x0000ffff, 0, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x6d, 0x0000ffff, 0, 0x100, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xFFFFFFFF पूर्ण
पूर्ण;

अटल स्थिर काष्ठा si_cac_config_reg cac_weights_cape_verde[] =
अणु
	अणु 0x0, 0x0000ffff, 0, 0x82, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x0, 0xffff0000, 16, 0x4F, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1, 0x0000ffff, 0, 0x153, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1, 0xffff0000, 16, 0x52, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x2, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x3, 0x0000ffff, 0, 0x135, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x3, 0xffff0000, 16, 0x4F, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x4, 0x0000ffff, 0, 0x135, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x4, 0xffff0000, 16, 0xAC, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x5, 0x0000ffff, 0, 0x118, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x5, 0xffff0000, 16, 0xBE, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x6, 0x0000ffff, 0, 0x110, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x6, 0xffff0000, 16, 0x4CD, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x18f, 0x0000ffff, 0, 0x30, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x7, 0x0000ffff, 0, 0x37, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x7, 0xffff0000, 16, 0x27, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x8, 0x0000ffff, 0, 0xC3, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x8, 0xffff0000, 16, 0x35, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x9, 0x0000ffff, 0, 0x28, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xa, 0x0000ffff, 0, 0x26C, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xb, 0x0000ffff, 0, 0x3B2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xb, 0xffff0000, 16, 0x99D, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xc, 0x0000ffff, 0, 0xA3F, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xd, 0x0000ffff, 0, 0xA, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xd, 0xffff0000, 16, 0xA, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xe, 0x0000ffff, 0, 0x5, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xf, 0x0000ffff, 0, 0x3, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xf, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x10, 0x0000ffff, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x10, 0xffff0000, 16, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x11, 0x0000ffff, 0, 0x5, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x11, 0xffff0000, 16, 0x15, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x12, 0x0000ffff, 0, 0x34, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x13, 0x0000ffff, 0, 0x4, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x13, 0xffff0000, 16, 0x4, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x14, 0x0000ffff, 0, 0x3BA, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x15, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x15, 0xffff0000, 16, 0x6, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x4e, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x16, 0x0000ffff, 0, 0x30, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x16, 0xffff0000, 16, 0x7A, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x17, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x18, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x18, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x19, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x19, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1a, 0x0000ffff, 0, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1a, 0xffff0000, 16, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1b, 0x0000ffff, 0, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1b, 0xffff0000, 16, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1c, 0x0000ffff, 0, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1c, 0xffff0000, 16, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1d, 0x0000ffff, 0, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1d, 0xffff0000, 16, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1e, 0x0000ffff, 0, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1e, 0xffff0000, 16, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1f, 0x0000ffff, 0, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1f, 0xffff0000, 16, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x20, 0x0000ffff, 0, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x6d, 0x0000ffff, 0, 0x100, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xFFFFFFFF पूर्ण
पूर्ण;

अटल स्थिर काष्ठा si_cac_config_reg lcac_cape_verde[] =
अणु
	अणु 0x98, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x98, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x104, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x104, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x110, 0x0001fffe, 1, 0x5, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x110, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x14f, 0x0001fffe, 1, 0x5, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x14f, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x8c, 0x0001fffe, 1, 0x5, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x8c, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x143, 0x0001fffe, 1, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x143, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x9b, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x9b, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x107, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x107, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x113, 0x0001fffe, 1, 0x5, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x113, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x152, 0x0001fffe, 1, 0x5, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x152, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x8f, 0x0001fffe, 1, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x8f, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x146, 0x0001fffe, 1, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x146, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x11c, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x11c, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x11f, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x11f, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x164, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x164, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x167, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x167, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x16a, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x16a, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x15e, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x15e, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x161, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x161, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x15b, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x15b, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x16d, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x16d, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x170, 0x0001fffe, 1, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x170, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x173, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x173, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x176, 0x0001fffe, 1, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x176, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x179, 0x0001fffe, 1, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x179, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x17c, 0x0001fffe, 1, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x17c, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x17f, 0x0001fffe, 1, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x17f, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xFFFFFFFF पूर्ण
पूर्ण;

अटल स्थिर काष्ठा si_cac_config_reg cac_override_cape_verde[] =
अणु
    अणु 0xFFFFFFFF पूर्ण
पूर्ण;

अटल स्थिर काष्ठा si_घातertune_data घातertune_data_cape_verde =
अणु
	((1 << 16) | 0x6993),
	5,
	0,
	7,
	105,
	अणु
		0UL,
		0UL,
		7194395UL,
		309631529UL,
		-1270850L,
		4513710L,
		100
	पूर्ण,
	117830498UL,
	12,
	अणु
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0
	पूर्ण,
	true
पूर्ण;

अटल स्थिर काष्ठा si_dte_data dte_data_cape_verde =
अणु
	अणु 0, 0, 0, 0, 0 पूर्ण,
	अणु 0, 0, 0, 0, 0 पूर्ण,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	अणु 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 पूर्ण,
	अणु 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 पूर्ण,
	अणु 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 पूर्ण,
	0,
	false
पूर्ण;

अटल स्थिर काष्ठा si_dte_data dte_data_venus_xtx =
अणु
	अणु 0x1E8480, 0x3D0900, 0x989680, 0x2625A00, 0x0 पूर्ण,
	अणु 0x71C, 0xAAB, 0xE39, 0x11C7, 0x0 पूर्ण,
	5,
	55000,
	0x69,
	0xA,
	1,
	0,
	0x3,
	अणु 0x96, 0xB4, 0xFF, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 पूर्ण,
	अणु 0x895440, 0x3D0900, 0x989680, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 पूर्ण,
	अणु 0xD6D8, 0x88B8, 0x1555, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 पूर्ण,
	90,
	true
पूर्ण;

अटल स्थिर काष्ठा si_dte_data dte_data_venus_xt =
अणु
	अणु 0x1E8480, 0x3D0900, 0x989680, 0x2625A00, 0x0 पूर्ण,
	अणु 0xBDA, 0x11C7, 0x17B4, 0x1DA1, 0x0 पूर्ण,
	5,
	55000,
	0x69,
	0xA,
	1,
	0,
	0x3,
	अणु 0x96, 0xB4, 0xFF, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 पूर्ण,
	अणु 0x895440, 0x3D0900, 0x989680, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 पूर्ण,
	अणु 0xAFC8, 0x88B8, 0x238E, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 पूर्ण,
	90,
	true
पूर्ण;

अटल स्थिर काष्ठा si_dte_data dte_data_venus_pro =
अणु
	अणु  0x1E8480, 0x3D0900, 0x989680, 0x2625A00, 0x0 पूर्ण,
	अणु 0x11C7, 0x1AAB, 0x238E, 0x2C72, 0x0 पूर्ण,
	5,
	55000,
	0x69,
	0xA,
	1,
	0,
	0x3,
	अणु 0x96, 0xB4, 0xFF, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 पूर्ण,
	अणु 0x895440, 0x3D0900, 0x989680, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 पूर्ण,
	अणु 0x88B8, 0x88B8, 0x3555, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 पूर्ण,
	90,
	true
पूर्ण;

अटल स्थिर काष्ठा si_cac_config_reg cac_weights_oland[] =
अणु
	अणु 0x0, 0x0000ffff, 0, 0x82, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x0, 0xffff0000, 16, 0x4F, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1, 0x0000ffff, 0, 0x153, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1, 0xffff0000, 16, 0x52, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x2, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x3, 0x0000ffff, 0, 0x135, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x3, 0xffff0000, 16, 0x4F, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x4, 0x0000ffff, 0, 0x135, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x4, 0xffff0000, 16, 0xAC, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x5, 0x0000ffff, 0, 0x118, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x5, 0xffff0000, 16, 0xBE, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x6, 0x0000ffff, 0, 0x110, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x6, 0xffff0000, 16, 0x4CD, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x18f, 0x0000ffff, 0, 0x30, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x7, 0x0000ffff, 0, 0x37, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x7, 0xffff0000, 16, 0x27, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x8, 0x0000ffff, 0, 0xC3, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x8, 0xffff0000, 16, 0x35, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x9, 0x0000ffff, 0, 0x28, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xa, 0x0000ffff, 0, 0x26C, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xb, 0x0000ffff, 0, 0x3B2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xb, 0xffff0000, 16, 0x99D, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xc, 0x0000ffff, 0, 0xA3F, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xd, 0x0000ffff, 0, 0xA, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xd, 0xffff0000, 16, 0xA, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xe, 0x0000ffff, 0, 0x5, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xf, 0x0000ffff, 0, 0x3, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xf, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x10, 0x0000ffff, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x10, 0xffff0000, 16, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x11, 0x0000ffff, 0, 0x5, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x11, 0xffff0000, 16, 0x15, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x12, 0x0000ffff, 0, 0x34, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x13, 0x0000ffff, 0, 0x4, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x13, 0xffff0000, 16, 0x4, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x14, 0x0000ffff, 0, 0x3BA, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x15, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x15, 0xffff0000, 16, 0x6, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x4e, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x16, 0x0000ffff, 0, 0x30, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x16, 0xffff0000, 16, 0x7A, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x17, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x18, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x18, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x19, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x19, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1a, 0x0000ffff, 0, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1a, 0xffff0000, 16, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1b, 0x0000ffff, 0, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1b, 0xffff0000, 16, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1c, 0x0000ffff, 0, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1c, 0xffff0000, 16, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1d, 0x0000ffff, 0, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1d, 0xffff0000, 16, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1e, 0x0000ffff, 0, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1e, 0xffff0000, 16, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1f, 0x0000ffff, 0, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1f, 0xffff0000, 16, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x20, 0x0000ffff, 0, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x6d, 0x0000ffff, 0, 0x100, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xFFFFFFFF पूर्ण
पूर्ण;

अटल स्थिर काष्ठा si_cac_config_reg cac_weights_mars_pro[] =
अणु
	अणु 0x0, 0x0000ffff, 0, 0x43, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x0, 0xffff0000, 16, 0x29, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1, 0x0000ffff, 0, 0xAF, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1, 0xffff0000, 16, 0x2A, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x2, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x3, 0x0000ffff, 0, 0xA0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x3, 0xffff0000, 16, 0x29, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x4, 0x0000ffff, 0, 0xA0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x4, 0xffff0000, 16, 0x59, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x5, 0x0000ffff, 0, 0x1A5, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x5, 0xffff0000, 16, 0x1D6, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x6, 0x0000ffff, 0, 0x2A3, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x6, 0xffff0000, 16, 0x8FD, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x18f, 0x0000ffff, 0, 0x76, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x7, 0x0000ffff, 0, 0x8A, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x7, 0xffff0000, 16, 0xA3, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x8, 0x0000ffff, 0, 0x71, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x8, 0xffff0000, 16, 0x36, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x9, 0x0000ffff, 0, 0xA6, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xa, 0x0000ffff, 0, 0x81, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xb, 0x0000ffff, 0, 0x3D2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xb, 0xffff0000, 16, 0x27C, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xc, 0x0000ffff, 0, 0xA96, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xd, 0x0000ffff, 0, 0x5, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xd, 0xffff0000, 16, 0x5, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xe, 0x0000ffff, 0, 0xB, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xf, 0x0000ffff, 0, 0x3, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xf, 0xffff0000, 16, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x10, 0x0000ffff, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x10, 0xffff0000, 16, 0x4, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x11, 0x0000ffff, 0, 0x15, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x11, 0xffff0000, 16, 0x7, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x12, 0x0000ffff, 0, 0x36, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x13, 0x0000ffff, 0, 0x10, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x13, 0xffff0000, 16, 0x10, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x14, 0x0000ffff, 0, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x15, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x15, 0xffff0000, 16, 0x6, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x4e, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x16, 0x0000ffff, 0, 0x32, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x16, 0xffff0000, 16, 0x7E, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x17, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x18, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x18, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x19, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x19, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1a, 0x0000ffff, 0, 0x280, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1a, 0xffff0000, 16, 0x7, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1b, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1b, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1c, 0x0000ffff, 0, 0x3C, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1c, 0xffff0000, 16, 0x203, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1d, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1d, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1e, 0x0000ffff, 0, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1e, 0xffff0000, 16, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1f, 0x0000ffff, 0, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1f, 0xffff0000, 16, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x20, 0x0000ffff, 0, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x6d, 0x0000ffff, 0, 0xB4, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xFFFFFFFF पूर्ण
पूर्ण;

अटल स्थिर काष्ठा si_cac_config_reg cac_weights_mars_xt[] =
अणु
	अणु 0x0, 0x0000ffff, 0, 0x43, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x0, 0xffff0000, 16, 0x29, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1, 0x0000ffff, 0, 0xAF, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1, 0xffff0000, 16, 0x2A, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x2, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x3, 0x0000ffff, 0, 0xA0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x3, 0xffff0000, 16, 0x29, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x4, 0x0000ffff, 0, 0xA0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x4, 0xffff0000, 16, 0x59, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x5, 0x0000ffff, 0, 0x1A5, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x5, 0xffff0000, 16, 0x1D6, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x6, 0x0000ffff, 0, 0x2A3, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x6, 0xffff0000, 16, 0x8FD, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x18f, 0x0000ffff, 0, 0x76, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x7, 0x0000ffff, 0, 0x8A, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x7, 0xffff0000, 16, 0xA3, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x8, 0x0000ffff, 0, 0x71, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x8, 0xffff0000, 16, 0x36, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x9, 0x0000ffff, 0, 0xA6, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xa, 0x0000ffff, 0, 0x81, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xb, 0x0000ffff, 0, 0x3D2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xb, 0xffff0000, 16, 0x27C, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xc, 0x0000ffff, 0, 0xA96, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xd, 0x0000ffff, 0, 0x5, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xd, 0xffff0000, 16, 0x5, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xe, 0x0000ffff, 0, 0xB, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xf, 0x0000ffff, 0, 0x3, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xf, 0xffff0000, 16, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x10, 0x0000ffff, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x10, 0xffff0000, 16, 0x4, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x11, 0x0000ffff, 0, 0x15, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x11, 0xffff0000, 16, 0x7, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x12, 0x0000ffff, 0, 0x36, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x13, 0x0000ffff, 0, 0x10, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x13, 0xffff0000, 16, 0x10, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x14, 0x0000ffff, 0, 0x60, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x15, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x15, 0xffff0000, 16, 0x6, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x4e, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x16, 0x0000ffff, 0, 0x32, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x16, 0xffff0000, 16, 0x7E, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x17, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x18, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x18, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x19, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x19, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1a, 0x0000ffff, 0, 0x280, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1a, 0xffff0000, 16, 0x7, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1b, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1b, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1c, 0x0000ffff, 0, 0x3C, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1c, 0xffff0000, 16, 0x203, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1d, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1d, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1e, 0x0000ffff, 0, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1e, 0xffff0000, 16, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1f, 0x0000ffff, 0, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1f, 0xffff0000, 16, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x20, 0x0000ffff, 0, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x6d, 0x0000ffff, 0, 0xB4, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xFFFFFFFF पूर्ण
पूर्ण;

अटल स्थिर काष्ठा si_cac_config_reg cac_weights_oland_pro[] =
अणु
	अणु 0x0, 0x0000ffff, 0, 0x43, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x0, 0xffff0000, 16, 0x29, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1, 0x0000ffff, 0, 0xAF, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1, 0xffff0000, 16, 0x2A, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x2, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x3, 0x0000ffff, 0, 0xA0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x3, 0xffff0000, 16, 0x29, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x4, 0x0000ffff, 0, 0xA0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x4, 0xffff0000, 16, 0x59, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x5, 0x0000ffff, 0, 0x1A5, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x5, 0xffff0000, 16, 0x1D6, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x6, 0x0000ffff, 0, 0x2A3, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x6, 0xffff0000, 16, 0x8FD, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x18f, 0x0000ffff, 0, 0x76, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x7, 0x0000ffff, 0, 0x8A, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x7, 0xffff0000, 16, 0xA3, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x8, 0x0000ffff, 0, 0x71, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x8, 0xffff0000, 16, 0x36, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x9, 0x0000ffff, 0, 0xA6, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xa, 0x0000ffff, 0, 0x81, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xb, 0x0000ffff, 0, 0x3D2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xb, 0xffff0000, 16, 0x27C, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xc, 0x0000ffff, 0, 0xA96, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xd, 0x0000ffff, 0, 0x5, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xd, 0xffff0000, 16, 0x5, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xe, 0x0000ffff, 0, 0xB, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xf, 0x0000ffff, 0, 0x3, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xf, 0xffff0000, 16, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x10, 0x0000ffff, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x10, 0xffff0000, 16, 0x4, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x11, 0x0000ffff, 0, 0x15, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x11, 0xffff0000, 16, 0x7, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x12, 0x0000ffff, 0, 0x36, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x13, 0x0000ffff, 0, 0x10, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x13, 0xffff0000, 16, 0x10, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x14, 0x0000ffff, 0, 0x90, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x15, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x15, 0xffff0000, 16, 0x6, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x4e, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x16, 0x0000ffff, 0, 0x32, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x16, 0xffff0000, 16, 0x7E, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x17, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x18, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x18, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x19, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x19, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1a, 0x0000ffff, 0, 0x280, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1a, 0xffff0000, 16, 0x7, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1b, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1b, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1c, 0x0000ffff, 0, 0x3C, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1c, 0xffff0000, 16, 0x203, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1d, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1d, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1e, 0x0000ffff, 0, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1e, 0xffff0000, 16, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1f, 0x0000ffff, 0, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1f, 0xffff0000, 16, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x20, 0x0000ffff, 0, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x6d, 0x0000ffff, 0, 0xB4, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xFFFFFFFF पूर्ण
पूर्ण;

अटल स्थिर काष्ठा si_cac_config_reg cac_weights_oland_xt[] =
अणु
	अणु 0x0, 0x0000ffff, 0, 0x43, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x0, 0xffff0000, 16, 0x29, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1, 0x0000ffff, 0, 0xAF, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1, 0xffff0000, 16, 0x2A, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x2, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x3, 0x0000ffff, 0, 0xA0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x3, 0xffff0000, 16, 0x29, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x4, 0x0000ffff, 0, 0xA0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x4, 0xffff0000, 16, 0x59, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x5, 0x0000ffff, 0, 0x1A5, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x5, 0xffff0000, 16, 0x1D6, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x6, 0x0000ffff, 0, 0x2A3, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x6, 0xffff0000, 16, 0x8FD, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x18f, 0x0000ffff, 0, 0x76, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x7, 0x0000ffff, 0, 0x8A, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x7, 0xffff0000, 16, 0xA3, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x8, 0x0000ffff, 0, 0x71, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x8, 0xffff0000, 16, 0x36, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x9, 0x0000ffff, 0, 0xA6, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xa, 0x0000ffff, 0, 0x81, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xb, 0x0000ffff, 0, 0x3D2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xb, 0xffff0000, 16, 0x27C, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xc, 0x0000ffff, 0, 0xA96, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xd, 0x0000ffff, 0, 0x5, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xd, 0xffff0000, 16, 0x5, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xe, 0x0000ffff, 0, 0xB, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xf, 0x0000ffff, 0, 0x3, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xf, 0xffff0000, 16, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x10, 0x0000ffff, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x10, 0xffff0000, 16, 0x4, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x11, 0x0000ffff, 0, 0x15, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x11, 0xffff0000, 16, 0x7, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x12, 0x0000ffff, 0, 0x36, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x13, 0x0000ffff, 0, 0x10, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x13, 0xffff0000, 16, 0x10, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x14, 0x0000ffff, 0, 0x120, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x15, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x15, 0xffff0000, 16, 0x6, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x4e, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x16, 0x0000ffff, 0, 0x32, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x16, 0xffff0000, 16, 0x7E, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x17, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x18, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x18, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x19, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x19, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1a, 0x0000ffff, 0, 0x280, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1a, 0xffff0000, 16, 0x7, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1b, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1b, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1c, 0x0000ffff, 0, 0x3C, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1c, 0xffff0000, 16, 0x203, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1d, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1d, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1e, 0x0000ffff, 0, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1e, 0xffff0000, 16, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1f, 0x0000ffff, 0, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1f, 0xffff0000, 16, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x20, 0x0000ffff, 0, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x6d, 0x0000ffff, 0, 0xB4, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xFFFFFFFF पूर्ण
पूर्ण;

अटल स्थिर काष्ठा si_cac_config_reg lcac_oland[] =
अणु
	अणु 0x98, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x98, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x104, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x104, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x110, 0x0001fffe, 1, 0x6, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x110, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x14f, 0x0001fffe, 1, 0x6, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x14f, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x8c, 0x0001fffe, 1, 0x6, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x8c, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x143, 0x0001fffe, 1, 0x4, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x143, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x11c, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x11c, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x11f, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x11f, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x164, 0x0001fffe, 1, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x164, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x167, 0x0001fffe, 1, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x167, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x16a, 0x0001fffe, 1, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x16a, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x15e, 0x0001fffe, 1, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x15e, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x161, 0x0001fffe, 1, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x161, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x15b, 0x0001fffe, 1, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x15b, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x16d, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x16d, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x170, 0x0001fffe, 1, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x170, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x173, 0x0001fffe, 1, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x173, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x176, 0x0001fffe, 1, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x176, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x179, 0x0001fffe, 1, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x179, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x17c, 0x0001fffe, 1, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x17c, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x17f, 0x0001fffe, 1, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x17f, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xFFFFFFFF पूर्ण
पूर्ण;

अटल स्थिर काष्ठा si_cac_config_reg lcac_mars_pro[] =
अणु
	अणु 0x98, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x98, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x104, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x104, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x110, 0x0001fffe, 1, 0x6, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x110, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x14f, 0x0001fffe, 1, 0x6, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x14f, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x8c, 0x0001fffe, 1, 0x6, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x8c, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x143, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x143, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x11c, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x11c, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x11f, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x11f, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x164, 0x0001fffe, 1, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x164, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x167, 0x0001fffe, 1, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x167, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x16a, 0x0001fffe, 1, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x16a, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x15e, 0x0001fffe, 1, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x15e, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x161, 0x0001fffe, 1, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x161, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x15b, 0x0001fffe, 1, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x15b, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x16d, 0x0001fffe, 1, 0x2, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x16d, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x170, 0x0001fffe, 1, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x170, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x173, 0x0001fffe, 1, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x173, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x176, 0x0001fffe, 1, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x176, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x179, 0x0001fffe, 1, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x179, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x17c, 0x0001fffe, 1, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x17c, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x17f, 0x0001fffe, 1, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x17f, 0x00000001, 0, 0x1, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xFFFFFFFF पूर्ण
पूर्ण;

अटल स्थिर काष्ठा si_cac_config_reg cac_override_oland[] =
अणु
	अणु 0xFFFFFFFF पूर्ण
पूर्ण;

अटल स्थिर काष्ठा si_घातertune_data घातertune_data_oland =
अणु
	((1 << 16) | 0x6993),
	5,
	0,
	7,
	105,
	अणु
		0UL,
		0UL,
		7194395UL,
		309631529UL,
		-1270850L,
		4513710L,
		100
	पूर्ण,
	117830498UL,
	12,
	अणु
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0
	पूर्ण,
	true
पूर्ण;

अटल स्थिर काष्ठा si_घातertune_data घातertune_data_mars_pro =
अणु
	((1 << 16) | 0x6993),
	5,
	0,
	7,
	105,
	अणु
		0UL,
		0UL,
		7194395UL,
		309631529UL,
		-1270850L,
		4513710L,
		100
	पूर्ण,
	117830498UL,
	12,
	अणु
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0
	पूर्ण,
	true
पूर्ण;

अटल स्थिर काष्ठा si_dte_data dte_data_oland =
अणु
	अणु 0, 0, 0, 0, 0 पूर्ण,
	अणु 0, 0, 0, 0, 0 पूर्ण,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	अणु 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 पूर्ण,
	अणु 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 पूर्ण,
	अणु 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 पूर्ण,
	0,
	false
पूर्ण;

अटल स्थिर काष्ठा si_dte_data dte_data_mars_pro =
अणु
	अणु 0x1E8480, 0x3D0900, 0x989680, 0x2625A00, 0x0 पूर्ण,
	अणु 0x0, 0x0, 0x0, 0x0, 0x0 पूर्ण,
	5,
	55000,
	105,
	0xA,
	1,
	0,
	0x10,
	अणु 0x96, 0xB4, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF पूर्ण,
	अणु 0x895440, 0x3D0900, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680 पूर्ण,
	अणु 0xF627, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 पूर्ण,
	90,
	true
पूर्ण;

अटल स्थिर काष्ठा si_dte_data dte_data_sun_xt =
अणु
	अणु 0x1E8480, 0x3D0900, 0x989680, 0x2625A00, 0x0 पूर्ण,
	अणु 0x0, 0x0, 0x0, 0x0, 0x0 पूर्ण,
	5,
	55000,
	105,
	0xA,
	1,
	0,
	0x10,
	अणु 0x96, 0xB4, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF पूर्ण,
	अणु 0x895440, 0x3D0900, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680, 0x989680 पूर्ण,
	अणु 0xD555, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 पूर्ण,
	90,
	true
पूर्ण;


अटल स्थिर काष्ठा si_cac_config_reg cac_weights_hainan[] =
अणु
	अणु 0x0, 0x0000ffff, 0, 0x2d9, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x0, 0xffff0000, 16, 0x22b, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1, 0x0000ffff, 0, 0x21c, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1, 0xffff0000, 16, 0x1dc, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x2, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x3, 0x0000ffff, 0, 0x24e, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x3, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x4, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x4, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x5, 0x0000ffff, 0, 0x35e, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x5, 0xffff0000, 16, 0x1143, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x6, 0x0000ffff, 0, 0xe17, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x6, 0xffff0000, 16, 0x441, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x18f, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x7, 0x0000ffff, 0, 0x28b, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x7, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x8, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x8, 0xffff0000, 16, 0xabe, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x9, 0x0000ffff, 0, 0xf11, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xa, 0x0000ffff, 0, 0x907, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xb, 0x0000ffff, 0, 0xb45, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xb, 0xffff0000, 16, 0xd1e, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xc, 0x0000ffff, 0, 0xa2c, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xd, 0x0000ffff, 0, 0x62, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xd, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xe, 0x0000ffff, 0, 0x1f3, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xf, 0x0000ffff, 0, 0x42, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xf, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x10, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x10, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x11, 0x0000ffff, 0, 0x709, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x11, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x12, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x13, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x13, 0xffff0000, 16, 0x3a, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x14, 0x0000ffff, 0, 0x357, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x15, 0x0000ffff, 0, 0x9f, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x15, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x4e, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x16, 0x0000ffff, 0, 0x314, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x16, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x17, 0x0000ffff, 0, 0x6d, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x18, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x18, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x19, 0x0000ffff, 0, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x19, 0xffff0000, 16, 0x0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1a, 0x0000ffff, 0, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1a, 0xffff0000, 16, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1b, 0x0000ffff, 0, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1b, 0xffff0000, 16, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1c, 0x0000ffff, 0, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1c, 0xffff0000, 16, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1d, 0x0000ffff, 0, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1d, 0xffff0000, 16, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1e, 0x0000ffff, 0, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1e, 0xffff0000, 16, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1f, 0x0000ffff, 0, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x1f, 0xffff0000, 16, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x20, 0x0000ffff, 0, 0, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0x6d, 0x0000ffff, 0, 0x1b9, SISLANDS_CACCONFIG_CGIND पूर्ण,
	अणु 0xFFFFFFFF पूर्ण
पूर्ण;

अटल स्थिर काष्ठा si_घातertune_data घातertune_data_hainan =
अणु
	((1 << 16) | 0x6993),
	5,
	0,
	9,
	105,
	अणु
		0UL,
		0UL,
		7194395UL,
		309631529UL,
		-1270850L,
		4513710L,
		100
	पूर्ण,
	117830498UL,
	12,
	अणु
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0
	पूर्ण,
	true
पूर्ण;

अटल काष्ठा rv7xx_घातer_info *rv770_get_pi(काष्ठा amdgpu_device *adev);
अटल काष्ठा evergreen_घातer_info *evergreen_get_pi(काष्ठा amdgpu_device *adev);
अटल काष्ठा ni_घातer_info *ni_get_pi(काष्ठा amdgpu_device *adev);
अटल काष्ठा  si_ps *si_get_ps(काष्ठा amdgpu_ps *rps);

अटल पूर्णांक si_populate_voltage_value(काष्ठा amdgpu_device *adev,
				     स्थिर काष्ठा atom_voltage_table *table,
				     u16 value, SISLANDS_SMC_VOLTAGE_VALUE *voltage);
अटल पूर्णांक si_get_std_voltage_value(काष्ठा amdgpu_device *adev,
				    SISLANDS_SMC_VOLTAGE_VALUE *voltage,
				    u16 *std_voltage);
अटल पूर्णांक si_ग_लिखो_smc_soft_रेजिस्टर(काष्ठा amdgpu_device *adev,
				      u16 reg_offset, u32 value);
अटल पूर्णांक si_convert_घातer_level_to_smc(काष्ठा amdgpu_device *adev,
					 काष्ठा rv7xx_pl *pl,
					 SISLANDS_SMC_HW_PERFORMANCE_LEVEL *level);
अटल पूर्णांक si_calculate_sclk_params(काष्ठा amdgpu_device *adev,
				    u32 engine_घड़ी,
				    SISLANDS_SMC_SCLK_VALUE *sclk);

अटल व्योम si_thermal_start_smc_fan_control(काष्ठा amdgpu_device *adev);
अटल व्योम si_fan_ctrl_set_शेष_mode(काष्ठा amdgpu_device *adev);
अटल व्योम si_dpm_set_irq_funcs(काष्ठा amdgpu_device *adev);

अटल काष्ठा si_घातer_info *si_get_pi(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा si_घातer_info *pi = adev->pm.dpm.priv;
	वापस pi;
पूर्ण

अटल व्योम si_calculate_leakage_क्रम_v_and_t_क्रमmula(स्थिर काष्ठा ni_leakage_coeffients *coeff,
						     u16 v, s32 t, u32 ileakage, u32 *leakage)
अणु
	s64 kt, kv, leakage_w, i_leakage, vddc;
	s64 temperature, t_slope, t_पूर्णांकercept, av, bv, t_ref;
	s64 पंचांगp;

	i_leakage = भाग64_s64(drm_पूर्णांक2fixp(ileakage), 100);
	vddc = भाग64_s64(drm_पूर्णांक2fixp(v), 1000);
	temperature = भाग64_s64(drm_पूर्णांक2fixp(t), 1000);

	t_slope = भाग64_s64(drm_पूर्णांक2fixp(coeff->t_slope), 100000000);
	t_पूर्णांकercept = भाग64_s64(drm_पूर्णांक2fixp(coeff->t_पूर्णांकercept), 100000000);
	av = भाग64_s64(drm_पूर्णांक2fixp(coeff->av), 100000000);
	bv = भाग64_s64(drm_पूर्णांक2fixp(coeff->bv), 100000000);
	t_ref = drm_पूर्णांक2fixp(coeff->t_ref);

	पंचांगp = drm_fixp_mul(t_slope, vddc) + t_पूर्णांकercept;
	kt = drm_fixp_exp(drm_fixp_mul(पंचांगp, temperature));
	kt = drm_fixp_भाग(kt, drm_fixp_exp(drm_fixp_mul(पंचांगp, t_ref)));
	kv = drm_fixp_mul(av, drm_fixp_exp(drm_fixp_mul(bv, vddc)));

	leakage_w = drm_fixp_mul(drm_fixp_mul(drm_fixp_mul(i_leakage, kt), kv), vddc);

	*leakage = drm_fixp2पूर्णांक(leakage_w * 1000);
पूर्ण

अटल व्योम si_calculate_leakage_क्रम_v_and_t(काष्ठा amdgpu_device *adev,
					     स्थिर काष्ठा ni_leakage_coeffients *coeff,
					     u16 v,
					     s32 t,
					     u32 i_leakage,
					     u32 *leakage)
अणु
	si_calculate_leakage_क्रम_v_and_t_क्रमmula(coeff, v, t, i_leakage, leakage);
पूर्ण

अटल व्योम si_calculate_leakage_क्रम_v_क्रमmula(स्थिर काष्ठा ni_leakage_coeffients *coeff,
					       स्थिर u32 fixed_kt, u16 v,
					       u32 ileakage, u32 *leakage)
अणु
	s64 kt, kv, leakage_w, i_leakage, vddc;

	i_leakage = भाग64_s64(drm_पूर्णांक2fixp(ileakage), 100);
	vddc = भाग64_s64(drm_पूर्णांक2fixp(v), 1000);

	kt = भाग64_s64(drm_पूर्णांक2fixp(fixed_kt), 100000000);
	kv = drm_fixp_mul(भाग64_s64(drm_पूर्णांक2fixp(coeff->av), 100000000),
			  drm_fixp_exp(drm_fixp_mul(भाग64_s64(drm_पूर्णांक2fixp(coeff->bv), 100000000), vddc)));

	leakage_w = drm_fixp_mul(drm_fixp_mul(drm_fixp_mul(i_leakage, kt), kv), vddc);

	*leakage = drm_fixp2पूर्णांक(leakage_w * 1000);
पूर्ण

अटल व्योम si_calculate_leakage_क्रम_v(काष्ठा amdgpu_device *adev,
				       स्थिर काष्ठा ni_leakage_coeffients *coeff,
				       स्थिर u32 fixed_kt,
				       u16 v,
				       u32 i_leakage,
				       u32 *leakage)
अणु
	si_calculate_leakage_क्रम_v_क्रमmula(coeff, fixed_kt, v, i_leakage, leakage);
पूर्ण


अटल व्योम si_update_dte_from_pl2(काष्ठा amdgpu_device *adev,
				   काष्ठा si_dte_data *dte_data)
अणु
	u32 p_limit1 = adev->pm.dpm.tdp_limit;
	u32 p_limit2 = adev->pm.dpm.near_tdp_limit;
	u32 k = dte_data->k;
	u32 t_max = dte_data->max_t;
	u32 t_split[5] = अणु 10, 15, 20, 25, 30 पूर्ण;
	u32 t_0 = dte_data->t0;
	u32 i;

	अगर (p_limit2 != 0 && p_limit2 <= p_limit1) अणु
		dte_data->tdep_count = 3;

		क्रम (i = 0; i < k; i++) अणु
			dte_data->r[i] =
				(t_split[i] * (t_max - t_0/(u32)1000) * (1 << 14)) /
				(p_limit2  * (u32)100);
		पूर्ण

		dte_data->tdep_r[1] = dte_data->r[4] * 2;

		क्रम (i = 2; i < SMC_SISLANDS_DTE_MAX_TEMPERATURE_DEPENDENT_ARRAY_SIZE; i++) अणु
			dte_data->tdep_r[i] = dte_data->r[4];
		पूर्ण
	पूर्ण अन्यथा अणु
		DRM_ERROR("Invalid PL2! DTE will not be updated.\n");
	पूर्ण
पूर्ण

अटल काष्ठा rv7xx_घातer_info *rv770_get_pi(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा rv7xx_घातer_info *pi = adev->pm.dpm.priv;

	वापस pi;
पूर्ण

अटल काष्ठा ni_घातer_info *ni_get_pi(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा ni_घातer_info *pi = adev->pm.dpm.priv;

	वापस pi;
पूर्ण

अटल काष्ठा si_ps *si_get_ps(काष्ठा amdgpu_ps *aps)
अणु
	काष्ठा  si_ps *ps = aps->ps_priv;

	वापस ps;
पूर्ण

अटल व्योम si_initialize_घातertune_शेषs(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा ni_घातer_info *ni_pi = ni_get_pi(adev);
	काष्ठा si_घातer_info *si_pi = si_get_pi(adev);
	bool update_dte_from_pl2 = false;

	अगर (adev->asic_type == CHIP_TAHITI) अणु
		si_pi->cac_weights = cac_weights_tahiti;
		si_pi->lcac_config = lcac_tahiti;
		si_pi->cac_override = cac_override_tahiti;
		si_pi->घातertune_data = &घातertune_data_tahiti;
		si_pi->dte_data = dte_data_tahiti;

		चयन (adev->pdev->device) अणु
		हाल 0x6798:
			si_pi->dte_data.enable_dte_by_शेष = true;
			अवरोध;
		हाल 0x6799:
			si_pi->dte_data = dte_data_new_zealand;
			अवरोध;
		हाल 0x6790:
		हाल 0x6791:
		हाल 0x6792:
		हाल 0x679E:
			si_pi->dte_data = dte_data_aruba_pro;
			update_dte_from_pl2 = true;
			अवरोध;
		हाल 0x679B:
			si_pi->dte_data = dte_data_malta;
			update_dte_from_pl2 = true;
			अवरोध;
		हाल 0x679A:
			si_pi->dte_data = dte_data_tahiti_pro;
			update_dte_from_pl2 = true;
			अवरोध;
		शेष:
			अगर (si_pi->dte_data.enable_dte_by_शेष == true)
				DRM_ERROR("DTE is not enabled!\n");
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (adev->asic_type == CHIP_PITCAIRN) अणु
		si_pi->cac_weights = cac_weights_pitcairn;
		si_pi->lcac_config = lcac_pitcairn;
		si_pi->cac_override = cac_override_pitcairn;
		si_pi->घातertune_data = &घातertune_data_pitcairn;

		चयन (adev->pdev->device) अणु
		हाल 0x6810:
		हाल 0x6818:
			si_pi->dte_data = dte_data_curacao_xt;
			update_dte_from_pl2 = true;
			अवरोध;
		हाल 0x6819:
		हाल 0x6811:
			si_pi->dte_data = dte_data_curacao_pro;
			update_dte_from_pl2 = true;
			अवरोध;
		हाल 0x6800:
		हाल 0x6806:
			si_pi->dte_data = dte_data_neptune_xt;
			update_dte_from_pl2 = true;
			अवरोध;
		शेष:
			si_pi->dte_data = dte_data_pitcairn;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (adev->asic_type == CHIP_VERDE) अणु
		si_pi->lcac_config = lcac_cape_verde;
		si_pi->cac_override = cac_override_cape_verde;
		si_pi->घातertune_data = &घातertune_data_cape_verde;

		चयन (adev->pdev->device) अणु
		हाल 0x683B:
		हाल 0x683F:
		हाल 0x6829:
		हाल 0x6835:
			si_pi->cac_weights = cac_weights_cape_verde_pro;
			si_pi->dte_data = dte_data_cape_verde;
			अवरोध;
		हाल 0x682C:
			si_pi->cac_weights = cac_weights_cape_verde_pro;
			si_pi->dte_data = dte_data_sun_xt;
			update_dte_from_pl2 = true;
			अवरोध;
		हाल 0x6825:
		हाल 0x6827:
			si_pi->cac_weights = cac_weights_heathrow;
			si_pi->dte_data = dte_data_cape_verde;
			अवरोध;
		हाल 0x6824:
		हाल 0x682D:
			si_pi->cac_weights = cac_weights_chअन्यथाa_xt;
			si_pi->dte_data = dte_data_cape_verde;
			अवरोध;
		हाल 0x682F:
			si_pi->cac_weights = cac_weights_chअन्यथाa_pro;
			si_pi->dte_data = dte_data_cape_verde;
			अवरोध;
		हाल 0x6820:
			si_pi->cac_weights = cac_weights_heathrow;
			si_pi->dte_data = dte_data_venus_xtx;
			अवरोध;
		हाल 0x6821:
			si_pi->cac_weights = cac_weights_heathrow;
			si_pi->dte_data = dte_data_venus_xt;
			अवरोध;
		हाल 0x6823:
		हाल 0x682B:
		हाल 0x6822:
		हाल 0x682A:
			si_pi->cac_weights = cac_weights_chअन्यथाa_pro;
			si_pi->dte_data = dte_data_venus_pro;
			अवरोध;
		शेष:
			si_pi->cac_weights = cac_weights_cape_verde;
			si_pi->dte_data = dte_data_cape_verde;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (adev->asic_type == CHIP_OLAND) अणु
		si_pi->lcac_config = lcac_mars_pro;
		si_pi->cac_override = cac_override_oland;
		si_pi->घातertune_data = &घातertune_data_mars_pro;
		si_pi->dte_data = dte_data_mars_pro;

		चयन (adev->pdev->device) अणु
		हाल 0x6601:
		हाल 0x6621:
		हाल 0x6603:
		हाल 0x6605:
			si_pi->cac_weights = cac_weights_mars_pro;
			update_dte_from_pl2 = true;
			अवरोध;
		हाल 0x6600:
		हाल 0x6606:
		हाल 0x6620:
		हाल 0x6604:
			si_pi->cac_weights = cac_weights_mars_xt;
			update_dte_from_pl2 = true;
			अवरोध;
		हाल 0x6611:
		हाल 0x6613:
		हाल 0x6608:
			si_pi->cac_weights = cac_weights_oland_pro;
			update_dte_from_pl2 = true;
			अवरोध;
		हाल 0x6610:
			si_pi->cac_weights = cac_weights_oland_xt;
			update_dte_from_pl2 = true;
			अवरोध;
		शेष:
			si_pi->cac_weights = cac_weights_oland;
			si_pi->lcac_config = lcac_oland;
			si_pi->cac_override = cac_override_oland;
			si_pi->घातertune_data = &घातertune_data_oland;
			si_pi->dte_data = dte_data_oland;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (adev->asic_type == CHIP_HAIन_अंक) अणु
		si_pi->cac_weights = cac_weights_hainan;
		si_pi->lcac_config = lcac_oland;
		si_pi->cac_override = cac_override_oland;
		si_pi->घातertune_data = &घातertune_data_hainan;
		si_pi->dte_data = dte_data_sun_xt;
		update_dte_from_pl2 = true;
	पूर्ण अन्यथा अणु
		DRM_ERROR("Unknown SI asic revision, failed to initialize PowerTune!\n");
		वापस;
	पूर्ण

	ni_pi->enable_घातer_containment = false;
	ni_pi->enable_cac = false;
	ni_pi->enable_sq_ramping = false;
	si_pi->enable_dte = false;

	अगर (si_pi->घातertune_data->enable_घातertune_by_शेष) अणु
		ni_pi->enable_घातer_containment = true;
		ni_pi->enable_cac = true;
		अगर (si_pi->dte_data.enable_dte_by_शेष) अणु
			si_pi->enable_dte = true;
			अगर (update_dte_from_pl2)
				si_update_dte_from_pl2(adev, &si_pi->dte_data);

		पूर्ण
		ni_pi->enable_sq_ramping = true;
	पूर्ण

	ni_pi->driver_calculate_cac_leakage = true;
	ni_pi->cac_configuration_required = true;

	अगर (ni_pi->cac_configuration_required) अणु
		ni_pi->support_cac_दीर्घ_term_average = true;
		si_pi->dyn_घातertune_data.l2_lta_winकरोw_size =
			si_pi->घातertune_data->l2_lta_winकरोw_size_शेष;
		si_pi->dyn_घातertune_data.lts_truncate =
			si_pi->घातertune_data->lts_truncate_शेष;
	पूर्ण अन्यथा अणु
		ni_pi->support_cac_दीर्घ_term_average = false;
		si_pi->dyn_घातertune_data.l2_lta_winकरोw_size = 0;
		si_pi->dyn_घातertune_data.lts_truncate = 0;
	पूर्ण

	si_pi->dyn_घातertune_data.disable_uvd_घातertune = false;
पूर्ण

अटल u32 si_get_smc_घातer_scaling_factor(काष्ठा amdgpu_device *adev)
अणु
	वापस 1;
पूर्ण

अटल u32 si_calculate_cac_wपूर्णांकime(काष्ठा amdgpu_device *adev)
अणु
	u32 xclk;
	u32 wपूर्णांकime;
	u32 cac_winकरोw;
	u32 cac_winकरोw_size;

	xclk = amdgpu_asic_get_xclk(adev);

	अगर (xclk == 0)
		वापस 0;

	cac_winकरोw = RREG32(CG_CAC_CTRL) & CAC_WINDOW_MASK;
	cac_winकरोw_size = ((cac_winकरोw & 0xFFFF0000) >> 16) * (cac_winकरोw & 0x0000FFFF);

	wपूर्णांकime = (cac_winकरोw_size * 100) / xclk;

	वापस wपूर्णांकime;
पूर्ण

अटल u32 si_scale_घातer_क्रम_smc(u32 घातer_in_watts, u32 scaling_factor)
अणु
	वापस घातer_in_watts;
पूर्ण

अटल पूर्णांक si_calculate_adjusted_tdp_limits(काष्ठा amdgpu_device *adev,
					    bool adjust_polarity,
					    u32 tdp_adjusपंचांगent,
					    u32 *tdp_limit,
					    u32 *near_tdp_limit)
अणु
	u32 adjusपंचांगent_delta, max_tdp_limit;

	अगर (tdp_adjusपंचांगent > (u32)adev->pm.dpm.tdp_od_limit)
		वापस -EINVAL;

	max_tdp_limit = ((100 + 100) * adev->pm.dpm.tdp_limit) / 100;

	अगर (adjust_polarity) अणु
		*tdp_limit = ((100 + tdp_adjusपंचांगent) * adev->pm.dpm.tdp_limit) / 100;
		*near_tdp_limit = adev->pm.dpm.near_tdp_limit_adjusted + (*tdp_limit - adev->pm.dpm.tdp_limit);
	पूर्ण अन्यथा अणु
		*tdp_limit = ((100 - tdp_adjusपंचांगent) * adev->pm.dpm.tdp_limit) / 100;
		adjusपंचांगent_delta  = adev->pm.dpm.tdp_limit - *tdp_limit;
		अगर (adjusपंचांगent_delta < adev->pm.dpm.near_tdp_limit_adjusted)
			*near_tdp_limit = adev->pm.dpm.near_tdp_limit_adjusted - adjusपंचांगent_delta;
		अन्यथा
			*near_tdp_limit = 0;
	पूर्ण

	अगर ((*tdp_limit <= 0) || (*tdp_limit > max_tdp_limit))
		वापस -EINVAL;
	अगर ((*near_tdp_limit <= 0) || (*near_tdp_limit > *tdp_limit))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक si_populate_smc_tdp_limits(काष्ठा amdgpu_device *adev,
				      काष्ठा amdgpu_ps *amdgpu_state)
अणु
	काष्ठा ni_घातer_info *ni_pi = ni_get_pi(adev);
	काष्ठा si_घातer_info *si_pi = si_get_pi(adev);

	अगर (ni_pi->enable_घातer_containment) अणु
		SISLANDS_SMC_STATETABLE *smc_table = &si_pi->smc_statetable;
		PP_SIslands_PAPMParameters *papm_parm;
		काष्ठा amdgpu_ppm_table *ppm = adev->pm.dpm.dyn_state.ppm_table;
		u32 scaling_factor = si_get_smc_घातer_scaling_factor(adev);
		u32 tdp_limit;
		u32 near_tdp_limit;
		पूर्णांक ret;

		अगर (scaling_factor == 0)
			वापस -EINVAL;

		स_रखो(smc_table, 0, माप(SISLANDS_SMC_STATETABLE));

		ret = si_calculate_adjusted_tdp_limits(adev,
						       false, /* ??? */
						       adev->pm.dpm.tdp_adjusपंचांगent,
						       &tdp_limit,
						       &near_tdp_limit);
		अगर (ret)
			वापस ret;

		smc_table->dpm2Params.TDPLimit =
			cpu_to_be32(si_scale_घातer_क्रम_smc(tdp_limit, scaling_factor) * 1000);
		smc_table->dpm2Params.NearTDPLimit =
			cpu_to_be32(si_scale_घातer_क्रम_smc(near_tdp_limit, scaling_factor) * 1000);
		smc_table->dpm2Params.SafePowerLimit =
			cpu_to_be32(si_scale_घातer_क्रम_smc((near_tdp_limit * SISLANDS_DPM2_TDP_SAFE_LIMIT_PERCENT) / 100, scaling_factor) * 1000);

		ret = amdgpu_si_copy_bytes_to_smc(adev,
						  (si_pi->state_table_start + दुरत्व(SISLANDS_SMC_STATETABLE, dpm2Params) +
						   दुरत्व(PP_SIslands_DPM2Parameters, TDPLimit)),
						  (u8 *)(&(smc_table->dpm2Params.TDPLimit)),
						  माप(u32) * 3,
						  si_pi->sram_end);
		अगर (ret)
			वापस ret;

		अगर (si_pi->enable_ppm) अणु
			papm_parm = &si_pi->papm_parm;
			स_रखो(papm_parm, 0, माप(PP_SIslands_PAPMParameters));
			papm_parm->NearTDPLimitTherm = cpu_to_be32(ppm->dgpu_tdp);
			papm_parm->dGPU_T_Limit = cpu_to_be32(ppm->tj_max);
			papm_parm->dGPU_T_Warning = cpu_to_be32(95);
			papm_parm->dGPU_T_Hysteresis = cpu_to_be32(5);
			papm_parm->Platक्रमmPowerLimit = 0xffffffff;
			papm_parm->NearTDPLimitPAPM = 0xffffffff;

			ret = amdgpu_si_copy_bytes_to_smc(adev, si_pi->papm_cfg_table_start,
							  (u8 *)papm_parm,
							  माप(PP_SIslands_PAPMParameters),
							  si_pi->sram_end);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक si_populate_smc_tdp_limits_2(काष्ठा amdgpu_device *adev,
					काष्ठा amdgpu_ps *amdgpu_state)
अणु
	काष्ठा ni_घातer_info *ni_pi = ni_get_pi(adev);
	काष्ठा si_घातer_info *si_pi = si_get_pi(adev);

	अगर (ni_pi->enable_घातer_containment) अणु
		SISLANDS_SMC_STATETABLE *smc_table = &si_pi->smc_statetable;
		u32 scaling_factor = si_get_smc_घातer_scaling_factor(adev);
		पूर्णांक ret;

		स_रखो(smc_table, 0, माप(SISLANDS_SMC_STATETABLE));

		smc_table->dpm2Params.NearTDPLimit =
			cpu_to_be32(si_scale_घातer_क्रम_smc(adev->pm.dpm.near_tdp_limit_adjusted, scaling_factor) * 1000);
		smc_table->dpm2Params.SafePowerLimit =
			cpu_to_be32(si_scale_घातer_क्रम_smc((adev->pm.dpm.near_tdp_limit_adjusted * SISLANDS_DPM2_TDP_SAFE_LIMIT_PERCENT) / 100, scaling_factor) * 1000);

		ret = amdgpu_si_copy_bytes_to_smc(adev,
						  (si_pi->state_table_start +
						   दुरत्व(SISLANDS_SMC_STATETABLE, dpm2Params) +
						   दुरत्व(PP_SIslands_DPM2Parameters, NearTDPLimit)),
						  (u8 *)(&(smc_table->dpm2Params.NearTDPLimit)),
						  माप(u32) * 2,
						  si_pi->sram_end);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल u16 si_calculate_घातer_efficiency_ratio(काष्ठा amdgpu_device *adev,
					       स्थिर u16 prev_std_vddc,
					       स्थिर u16 curr_std_vddc)
अणु
	u64 margin = (u64)SISLANDS_DPM2_PWREFFICIENCYRATIO_MARGIN;
	u64 prev_vddc = (u64)prev_std_vddc;
	u64 curr_vddc = (u64)curr_std_vddc;
	u64 pwr_efficiency_ratio, n, d;

	अगर ((prev_vddc == 0) || (curr_vddc == 0))
		वापस 0;

	n = भाग64_u64((u64)1024 * curr_vddc * curr_vddc * ((u64)1000 + margin), (u64)1000);
	d = prev_vddc * prev_vddc;
	pwr_efficiency_ratio = भाग64_u64(n, d);

	अगर (pwr_efficiency_ratio > (u64)0xFFFF)
		वापस 0;

	वापस (u16)pwr_efficiency_ratio;
पूर्ण

अटल bool si_should_disable_uvd_घातertune(काष्ठा amdgpu_device *adev,
					    काष्ठा amdgpu_ps *amdgpu_state)
अणु
	काष्ठा si_घातer_info *si_pi = si_get_pi(adev);

	अगर (si_pi->dyn_घातertune_data.disable_uvd_घातertune &&
	    amdgpu_state->vclk && amdgpu_state->dclk)
		वापस true;

	वापस false;
पूर्ण

काष्ठा evergreen_घातer_info *evergreen_get_pi(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा evergreen_घातer_info *pi = adev->pm.dpm.priv;

	वापस pi;
पूर्ण

अटल पूर्णांक si_populate_घातer_containment_values(काष्ठा amdgpu_device *adev,
						काष्ठा amdgpu_ps *amdgpu_state,
						SISLANDS_SMC_SWSTATE *smc_state)
अणु
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(adev);
	काष्ठा ni_घातer_info *ni_pi = ni_get_pi(adev);
	काष्ठा  si_ps *state = si_get_ps(amdgpu_state);
	SISLANDS_SMC_VOLTAGE_VALUE vddc;
	u32 prev_sclk;
	u32 max_sclk;
	u32 min_sclk;
	u16 prev_std_vddc;
	u16 curr_std_vddc;
	पूर्णांक i;
	u16 pwr_efficiency_ratio;
	u8 max_ps_percent;
	bool disable_uvd_घातer_tune;
	पूर्णांक ret;

	अगर (ni_pi->enable_घातer_containment == false)
		वापस 0;

	अगर (state->perक्रमmance_level_count == 0)
		वापस -EINVAL;

	अगर (smc_state->levelCount != state->perक्रमmance_level_count)
		वापस -EINVAL;

	disable_uvd_घातer_tune = si_should_disable_uvd_घातertune(adev, amdgpu_state);

	smc_state->levels[0].dpm2.MaxPS = 0;
	smc_state->levels[0].dpm2.NearTDPDec = 0;
	smc_state->levels[0].dpm2.AboveSafeInc = 0;
	smc_state->levels[0].dpm2.BelowSafeInc = 0;
	smc_state->levels[0].dpm2.PwrEfficiencyRatio = 0;

	क्रम (i = 1; i < state->perक्रमmance_level_count; i++) अणु
		prev_sclk = state->perक्रमmance_levels[i-1].sclk;
		max_sclk  = state->perक्रमmance_levels[i].sclk;
		अगर (i == 1)
			max_ps_percent = SISLANDS_DPM2_MAXPS_PERCENT_M;
		अन्यथा
			max_ps_percent = SISLANDS_DPM2_MAXPS_PERCENT_H;

		अगर (prev_sclk > max_sclk)
			वापस -EINVAL;

		अगर ((max_ps_percent == 0) ||
		    (prev_sclk == max_sclk) ||
		    disable_uvd_घातer_tune)
			min_sclk = max_sclk;
		अन्यथा अगर (i == 1)
			min_sclk = prev_sclk;
		अन्यथा
			min_sclk = (prev_sclk * (u32)max_ps_percent) / 100;

		अगर (min_sclk < state->perक्रमmance_levels[0].sclk)
			min_sclk = state->perक्रमmance_levels[0].sclk;

		अगर (min_sclk == 0)
			वापस -EINVAL;

		ret = si_populate_voltage_value(adev, &eg_pi->vddc_voltage_table,
						state->perक्रमmance_levels[i-1].vddc, &vddc);
		अगर (ret)
			वापस ret;

		ret = si_get_std_voltage_value(adev, &vddc, &prev_std_vddc);
		अगर (ret)
			वापस ret;

		ret = si_populate_voltage_value(adev, &eg_pi->vddc_voltage_table,
						state->perक्रमmance_levels[i].vddc, &vddc);
		अगर (ret)
			वापस ret;

		ret = si_get_std_voltage_value(adev, &vddc, &curr_std_vddc);
		अगर (ret)
			वापस ret;

		pwr_efficiency_ratio = si_calculate_घातer_efficiency_ratio(adev,
									   prev_std_vddc, curr_std_vddc);

		smc_state->levels[i].dpm2.MaxPS = (u8)((SISLANDS_DPM2_MAX_PULSE_SKIP * (max_sclk - min_sclk)) / max_sclk);
		smc_state->levels[i].dpm2.NearTDPDec = SISLANDS_DPM2_NEAR_TDP_DEC;
		smc_state->levels[i].dpm2.AboveSafeInc = SISLANDS_DPM2_ABOVE_SAFE_INC;
		smc_state->levels[i].dpm2.BelowSafeInc = SISLANDS_DPM2_BELOW_SAFE_INC;
		smc_state->levels[i].dpm2.PwrEfficiencyRatio = cpu_to_be16(pwr_efficiency_ratio);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक si_populate_sq_ramping_values(काष्ठा amdgpu_device *adev,
					 काष्ठा amdgpu_ps *amdgpu_state,
					 SISLANDS_SMC_SWSTATE *smc_state)
अणु
	काष्ठा ni_घातer_info *ni_pi = ni_get_pi(adev);
	काष्ठा  si_ps *state = si_get_ps(amdgpu_state);
	u32 sq_घातer_throttle, sq_घातer_throttle2;
	bool enable_sq_ramping = ni_pi->enable_sq_ramping;
	पूर्णांक i;

	अगर (state->perक्रमmance_level_count == 0)
		वापस -EINVAL;

	अगर (smc_state->levelCount != state->perक्रमmance_level_count)
		वापस -EINVAL;

	अगर (adev->pm.dpm.sq_ramping_threshold == 0)
		वापस -EINVAL;

	अगर (SISLANDS_DPM2_SQ_RAMP_MAX_POWER > (MAX_POWER_MASK >> MAX_POWER_SHIFT))
		enable_sq_ramping = false;

	अगर (SISLANDS_DPM2_SQ_RAMP_MIN_POWER > (MIN_POWER_MASK >> MIN_POWER_SHIFT))
		enable_sq_ramping = false;

	अगर (SISLANDS_DPM2_SQ_RAMP_MAX_POWER_DELTA > (MAX_POWER_DELTA_MASK >> MAX_POWER_DELTA_SHIFT))
		enable_sq_ramping = false;

	अगर (SISLANDS_DPM2_SQ_RAMP_STI_SIZE > (STI_SIZE_MASK >> STI_SIZE_SHIFT))
		enable_sq_ramping = false;

	अगर (SISLANDS_DPM2_SQ_RAMP_LTI_RATIO > (LTI_RATIO_MASK >> LTI_RATIO_SHIFT))
		enable_sq_ramping = false;

	क्रम (i = 0; i < state->perक्रमmance_level_count; i++) अणु
		sq_घातer_throttle = 0;
		sq_घातer_throttle2 = 0;

		अगर ((state->perक्रमmance_levels[i].sclk >= adev->pm.dpm.sq_ramping_threshold) &&
		    enable_sq_ramping) अणु
			sq_घातer_throttle |= MAX_POWER(SISLANDS_DPM2_SQ_RAMP_MAX_POWER);
			sq_घातer_throttle |= MIN_POWER(SISLANDS_DPM2_SQ_RAMP_MIN_POWER);
			sq_घातer_throttle2 |= MAX_POWER_DELTA(SISLANDS_DPM2_SQ_RAMP_MAX_POWER_DELTA);
			sq_घातer_throttle2 |= STI_SIZE(SISLANDS_DPM2_SQ_RAMP_STI_SIZE);
			sq_घातer_throttle2 |= LTI_RATIO(SISLANDS_DPM2_SQ_RAMP_LTI_RATIO);
		पूर्ण अन्यथा अणु
			sq_घातer_throttle |= MAX_POWER_MASK | MIN_POWER_MASK;
			sq_घातer_throttle2 |= MAX_POWER_DELTA_MASK | STI_SIZE_MASK | LTI_RATIO_MASK;
		पूर्ण

		smc_state->levels[i].SQPowerThrottle = cpu_to_be32(sq_घातer_throttle);
		smc_state->levels[i].SQPowerThrottle_2 = cpu_to_be32(sq_घातer_throttle2);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक si_enable_घातer_containment(काष्ठा amdgpu_device *adev,
				       काष्ठा amdgpu_ps *amdgpu_new_state,
				       bool enable)
अणु
	काष्ठा ni_घातer_info *ni_pi = ni_get_pi(adev);
	PPSMC_Result smc_result;
	पूर्णांक ret = 0;

	अगर (ni_pi->enable_घातer_containment) अणु
		अगर (enable) अणु
			अगर (!si_should_disable_uvd_घातertune(adev, amdgpu_new_state)) अणु
				smc_result = amdgpu_si_send_msg_to_smc(adev, PPSMC_TDPClampingActive);
				अगर (smc_result != PPSMC_Result_OK) अणु
					ret = -EINVAL;
					ni_pi->pc_enabled = false;
				पूर्ण अन्यथा अणु
					ni_pi->pc_enabled = true;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			smc_result = amdgpu_si_send_msg_to_smc(adev, PPSMC_TDPClampingInactive);
			अगर (smc_result != PPSMC_Result_OK)
				ret = -EINVAL;
			ni_pi->pc_enabled = false;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक si_initialize_smc_dte_tables(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा si_घातer_info *si_pi = si_get_pi(adev);
	पूर्णांक ret = 0;
	काष्ठा si_dte_data *dte_data = &si_pi->dte_data;
	Smc_SIslands_DTE_Configuration *dte_tables = शून्य;
	u32 table_size;
	u8 tdep_count;
	u32 i;

	अगर (dte_data == शून्य)
		si_pi->enable_dte = false;

	अगर (si_pi->enable_dte == false)
		वापस 0;

	अगर (dte_data->k <= 0)
		वापस -EINVAL;

	dte_tables = kzalloc(माप(Smc_SIslands_DTE_Configuration), GFP_KERNEL);
	अगर (dte_tables == शून्य) अणु
		si_pi->enable_dte = false;
		वापस -ENOMEM;
	पूर्ण

	table_size = dte_data->k;

	अगर (table_size > SMC_SISLANDS_DTE_MAX_FILTER_STAGES)
		table_size = SMC_SISLANDS_DTE_MAX_FILTER_STAGES;

	tdep_count = dte_data->tdep_count;
	अगर (tdep_count > SMC_SISLANDS_DTE_MAX_TEMPERATURE_DEPENDENT_ARRAY_SIZE)
		tdep_count = SMC_SISLANDS_DTE_MAX_TEMPERATURE_DEPENDENT_ARRAY_SIZE;

	dte_tables->K = cpu_to_be32(table_size);
	dte_tables->T0 = cpu_to_be32(dte_data->t0);
	dte_tables->MaxT = cpu_to_be32(dte_data->max_t);
	dte_tables->WinकरोwSize = dte_data->winकरोw_size;
	dte_tables->temp_select = dte_data->temp_select;
	dte_tables->DTE_mode = dte_data->dte_mode;
	dte_tables->Tthreshold = cpu_to_be32(dte_data->t_threshold);

	अगर (tdep_count > 0)
		table_size--;

	क्रम (i = 0; i < table_size; i++) अणु
		dte_tables->tau[i] = cpu_to_be32(dte_data->tau[i]);
		dte_tables->R[i]   = cpu_to_be32(dte_data->r[i]);
	पूर्ण

	dte_tables->Tdep_count = tdep_count;

	क्रम (i = 0; i < (u32)tdep_count; i++) अणु
		dte_tables->T_limits[i] = dte_data->t_limits[i];
		dte_tables->Tdep_tau[i] = cpu_to_be32(dte_data->tdep_tau[i]);
		dte_tables->Tdep_R[i] = cpu_to_be32(dte_data->tdep_r[i]);
	पूर्ण

	ret = amdgpu_si_copy_bytes_to_smc(adev, si_pi->dte_table_start,
					  (u8 *)dte_tables,
					  माप(Smc_SIslands_DTE_Configuration),
					  si_pi->sram_end);
	kमुक्त(dte_tables);

	वापस ret;
पूर्ण

अटल पूर्णांक si_get_cac_std_voltage_max_min(काष्ठा amdgpu_device *adev,
					  u16 *max, u16 *min)
अणु
	काष्ठा si_घातer_info *si_pi = si_get_pi(adev);
	काष्ठा amdgpu_cac_leakage_table *table =
		&adev->pm.dpm.dyn_state.cac_leakage_table;
	u32 i;
	u32 v0_loadline;

	अगर (table == शून्य)
		वापस -EINVAL;

	*max = 0;
	*min = 0xFFFF;

	क्रम (i = 0; i < table->count; i++) अणु
		अगर (table->entries[i].vddc > *max)
			*max = table->entries[i].vddc;
		अगर (table->entries[i].vddc < *min)
			*min = table->entries[i].vddc;
	पूर्ण

	अगर (si_pi->घातertune_data->lkge_lut_v0_percent > 100)
		वापस -EINVAL;

	v0_loadline = (*min) * (100 - si_pi->घातertune_data->lkge_lut_v0_percent) / 100;

	अगर (v0_loadline > 0xFFFFUL)
		वापस -EINVAL;

	*min = (u16)v0_loadline;

	अगर ((*min > *max) || (*max == 0) || (*min == 0))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल u16 si_get_cac_std_voltage_step(u16 max, u16 min)
अणु
	वापस ((max - min) + (SMC_SISLANDS_LKGE_LUT_NUM_OF_VOLT_ENTRIES - 1)) /
		SMC_SISLANDS_LKGE_LUT_NUM_OF_VOLT_ENTRIES;
पूर्ण

अटल पूर्णांक si_init_dte_leakage_table(काष्ठा amdgpu_device *adev,
				     PP_SIslands_CacConfig *cac_tables,
				     u16 vddc_max, u16 vddc_min, u16 vddc_step,
				     u16 t0, u16 t_step)
अणु
	काष्ठा si_घातer_info *si_pi = si_get_pi(adev);
	u32 leakage;
	अचिन्हित पूर्णांक i, j;
	s32 t;
	u32 smc_leakage;
	u32 scaling_factor;
	u16 voltage;

	scaling_factor = si_get_smc_घातer_scaling_factor(adev);

	क्रम (i = 0; i < SMC_SISLANDS_LKGE_LUT_NUM_OF_TEMP_ENTRIES ; i++) अणु
		t = (1000 * (i * t_step + t0));

		क्रम (j = 0; j < SMC_SISLANDS_LKGE_LUT_NUM_OF_VOLT_ENTRIES; j++) अणु
			voltage = vddc_max - (vddc_step * j);

			si_calculate_leakage_क्रम_v_and_t(adev,
							 &si_pi->घातertune_data->leakage_coefficients,
							 voltage,
							 t,
							 si_pi->dyn_घातertune_data.cac_leakage,
							 &leakage);

			smc_leakage = si_scale_घातer_क्रम_smc(leakage, scaling_factor) / 4;

			अगर (smc_leakage > 0xFFFF)
				smc_leakage = 0xFFFF;

			cac_tables->cac_lkge_lut[i][SMC_SISLANDS_LKGE_LUT_NUM_OF_VOLT_ENTRIES-1-j] =
				cpu_to_be16((u16)smc_leakage);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक si_init_simplअगरied_leakage_table(काष्ठा amdgpu_device *adev,
					    PP_SIslands_CacConfig *cac_tables,
					    u16 vddc_max, u16 vddc_min, u16 vddc_step)
अणु
	काष्ठा si_घातer_info *si_pi = si_get_pi(adev);
	u32 leakage;
	अचिन्हित पूर्णांक i, j;
	u32 smc_leakage;
	u32 scaling_factor;
	u16 voltage;

	scaling_factor = si_get_smc_घातer_scaling_factor(adev);

	क्रम (j = 0; j < SMC_SISLANDS_LKGE_LUT_NUM_OF_VOLT_ENTRIES; j++) अणु
		voltage = vddc_max - (vddc_step * j);

		si_calculate_leakage_क्रम_v(adev,
					   &si_pi->घातertune_data->leakage_coefficients,
					   si_pi->घातertune_data->fixed_kt,
					   voltage,
					   si_pi->dyn_घातertune_data.cac_leakage,
					   &leakage);

		smc_leakage = si_scale_घातer_क्रम_smc(leakage, scaling_factor) / 4;

		अगर (smc_leakage > 0xFFFF)
			smc_leakage = 0xFFFF;

		क्रम (i = 0; i < SMC_SISLANDS_LKGE_LUT_NUM_OF_TEMP_ENTRIES ; i++)
			cac_tables->cac_lkge_lut[i][SMC_SISLANDS_LKGE_LUT_NUM_OF_VOLT_ENTRIES-1-j] =
				cpu_to_be16((u16)smc_leakage);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक si_initialize_smc_cac_tables(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा ni_घातer_info *ni_pi = ni_get_pi(adev);
	काष्ठा si_घातer_info *si_pi = si_get_pi(adev);
	PP_SIslands_CacConfig *cac_tables = शून्य;
	u16 vddc_max, vddc_min, vddc_step;
	u16 t0, t_step;
	u32 load_line_slope, reg;
	पूर्णांक ret = 0;
	u32 ticks_per_us = amdgpu_asic_get_xclk(adev) / 100;

	अगर (ni_pi->enable_cac == false)
		वापस 0;

	cac_tables = kzalloc(माप(PP_SIslands_CacConfig), GFP_KERNEL);
	अगर (!cac_tables)
		वापस -ENOMEM;

	reg = RREG32(CG_CAC_CTRL) & ~CAC_WINDOW_MASK;
	reg |= CAC_WINDOW(si_pi->घातertune_data->cac_winकरोw);
	WREG32(CG_CAC_CTRL, reg);

	si_pi->dyn_घातertune_data.cac_leakage = adev->pm.dpm.cac_leakage;
	si_pi->dyn_घातertune_data.dc_pwr_value =
		si_pi->घातertune_data->dc_cac[NISLANDS_DCCAC_LEVEL_0];
	si_pi->dyn_घातertune_data.wपूर्णांकime = si_calculate_cac_wपूर्णांकime(adev);
	si_pi->dyn_घातertune_data.shअगरt_n = si_pi->घातertune_data->shअगरt_n_शेष;

	si_pi->dyn_घातertune_data.leakage_minimum_temperature = 80 * 1000;

	ret = si_get_cac_std_voltage_max_min(adev, &vddc_max, &vddc_min);
	अगर (ret)
		जाओ करोne_मुक्त;

	vddc_step = si_get_cac_std_voltage_step(vddc_max, vddc_min);
	vddc_min = vddc_max - (vddc_step * (SMC_SISLANDS_LKGE_LUT_NUM_OF_VOLT_ENTRIES - 1));
	t_step = 4;
	t0 = 60;

	अगर (si_pi->enable_dte || ni_pi->driver_calculate_cac_leakage)
		ret = si_init_dte_leakage_table(adev, cac_tables,
						vddc_max, vddc_min, vddc_step,
						t0, t_step);
	अन्यथा
		ret = si_init_simplअगरied_leakage_table(adev, cac_tables,
						       vddc_max, vddc_min, vddc_step);
	अगर (ret)
		जाओ करोne_मुक्त;

	load_line_slope = ((u32)adev->pm.dpm.load_line_slope << SMC_SISLANDS_SCALE_R) / 100;

	cac_tables->l2numWin_TDP = cpu_to_be32(si_pi->dyn_घातertune_data.l2_lta_winकरोw_size);
	cac_tables->lts_truncate_n = si_pi->dyn_घातertune_data.lts_truncate;
	cac_tables->SHIFT_N = si_pi->dyn_घातertune_data.shअगरt_n;
	cac_tables->lkge_lut_V0 = cpu_to_be32((u32)vddc_min);
	cac_tables->lkge_lut_Vstep = cpu_to_be32((u32)vddc_step);
	cac_tables->R_LL = cpu_to_be32(load_line_slope);
	cac_tables->WinTime = cpu_to_be32(si_pi->dyn_घातertune_data.wपूर्णांकime);
	cac_tables->calculation_repeats = cpu_to_be32(2);
	cac_tables->dc_cac = cpu_to_be32(0);
	cac_tables->log2_PG_LKG_SCALE = 12;
	cac_tables->cac_temp = si_pi->घातertune_data->operating_temp;
	cac_tables->lkge_lut_T0 = cpu_to_be32((u32)t0);
	cac_tables->lkge_lut_Tstep = cpu_to_be32((u32)t_step);

	ret = amdgpu_si_copy_bytes_to_smc(adev, si_pi->cac_table_start,
					  (u8 *)cac_tables,
					  माप(PP_SIslands_CacConfig),
					  si_pi->sram_end);

	अगर (ret)
		जाओ करोne_मुक्त;

	ret = si_ग_लिखो_smc_soft_रेजिस्टर(adev, SI_SMC_SOFT_REGISTER_ticks_per_us, ticks_per_us);

करोne_मुक्त:
	अगर (ret) अणु
		ni_pi->enable_cac = false;
		ni_pi->enable_घातer_containment = false;
	पूर्ण

	kमुक्त(cac_tables);

	वापस ret;
पूर्ण

अटल पूर्णांक si_program_cac_config_रेजिस्टरs(काष्ठा amdgpu_device *adev,
					   स्थिर काष्ठा si_cac_config_reg *cac_config_regs)
अणु
	स्थिर काष्ठा si_cac_config_reg *config_regs = cac_config_regs;
	u32 data = 0, offset;

	अगर (!config_regs)
		वापस -EINVAL;

	जबतक (config_regs->offset != 0xFFFFFFFF) अणु
		चयन (config_regs->type) अणु
		हाल SISLANDS_CACCONFIG_CGIND:
			offset = SMC_CG_IND_START + config_regs->offset;
			अगर (offset < SMC_CG_IND_END)
				data = RREG32_SMC(offset);
			अवरोध;
		शेष:
			data = RREG32(config_regs->offset);
			अवरोध;
		पूर्ण

		data &= ~config_regs->mask;
		data |= ((config_regs->value << config_regs->shअगरt) & config_regs->mask);

		चयन (config_regs->type) अणु
		हाल SISLANDS_CACCONFIG_CGIND:
			offset = SMC_CG_IND_START + config_regs->offset;
			अगर (offset < SMC_CG_IND_END)
				WREG32_SMC(offset, data);
			अवरोध;
		शेष:
			WREG32(config_regs->offset, data);
			अवरोध;
		पूर्ण
		config_regs++;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक si_initialize_hardware_cac_manager(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा ni_घातer_info *ni_pi = ni_get_pi(adev);
	काष्ठा si_घातer_info *si_pi = si_get_pi(adev);
	पूर्णांक ret;

	अगर ((ni_pi->enable_cac == false) ||
	    (ni_pi->cac_configuration_required == false))
		वापस 0;

	ret = si_program_cac_config_रेजिस्टरs(adev, si_pi->lcac_config);
	अगर (ret)
		वापस ret;
	ret = si_program_cac_config_रेजिस्टरs(adev, si_pi->cac_override);
	अगर (ret)
		वापस ret;
	ret = si_program_cac_config_रेजिस्टरs(adev, si_pi->cac_weights);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक si_enable_smc_cac(काष्ठा amdgpu_device *adev,
			     काष्ठा amdgpu_ps *amdgpu_new_state,
			     bool enable)
अणु
	काष्ठा ni_घातer_info *ni_pi = ni_get_pi(adev);
	काष्ठा si_घातer_info *si_pi = si_get_pi(adev);
	PPSMC_Result smc_result;
	पूर्णांक ret = 0;

	अगर (ni_pi->enable_cac) अणु
		अगर (enable) अणु
			अगर (!si_should_disable_uvd_घातertune(adev, amdgpu_new_state)) अणु
				अगर (ni_pi->support_cac_दीर्घ_term_average) अणु
					smc_result = amdgpu_si_send_msg_to_smc(adev, PPSMC_CACLongTermAvgEnable);
					अगर (smc_result != PPSMC_Result_OK)
						ni_pi->support_cac_दीर्घ_term_average = false;
				पूर्ण

				smc_result = amdgpu_si_send_msg_to_smc(adev, PPSMC_MSG_EnableCac);
				अगर (smc_result != PPSMC_Result_OK) अणु
					ret = -EINVAL;
					ni_pi->cac_enabled = false;
				पूर्ण अन्यथा अणु
					ni_pi->cac_enabled = true;
				पूर्ण

				अगर (si_pi->enable_dte) अणु
					smc_result = amdgpu_si_send_msg_to_smc(adev, PPSMC_MSG_EnableDTE);
					अगर (smc_result != PPSMC_Result_OK)
						ret = -EINVAL;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अगर (ni_pi->cac_enabled) अणु
			अगर (si_pi->enable_dte)
				smc_result = amdgpu_si_send_msg_to_smc(adev, PPSMC_MSG_DisableDTE);

			smc_result = amdgpu_si_send_msg_to_smc(adev, PPSMC_MSG_DisableCac);

			ni_pi->cac_enabled = false;

			अगर (ni_pi->support_cac_दीर्घ_term_average)
				smc_result = amdgpu_si_send_msg_to_smc(adev, PPSMC_CACLongTermAvgDisable);
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक si_init_smc_spll_table(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा ni_घातer_info *ni_pi = ni_get_pi(adev);
	काष्ठा si_घातer_info *si_pi = si_get_pi(adev);
	SMC_SISLANDS_SPLL_DIV_TABLE *spll_table;
	SISLANDS_SMC_SCLK_VALUE sclk_params;
	u32 fb_भाग, p_भाग;
	u32 clk_s, clk_v;
	u32 sclk = 0;
	पूर्णांक ret = 0;
	u32 पंचांगp;
	पूर्णांक i;

	अगर (si_pi->spll_table_start == 0)
		वापस -EINVAL;

	spll_table = kzalloc(माप(SMC_SISLANDS_SPLL_DIV_TABLE), GFP_KERNEL);
	अगर (spll_table == शून्य)
		वापस -ENOMEM;

	क्रम (i = 0; i < 256; i++) अणु
		ret = si_calculate_sclk_params(adev, sclk, &sclk_params);
		अगर (ret)
			अवरोध;
		p_भाग = (sclk_params.vCG_SPLL_FUNC_CNTL & SPLL_PDIV_A_MASK) >> SPLL_PDIV_A_SHIFT;
		fb_भाग = (sclk_params.vCG_SPLL_FUNC_CNTL_3 & SPLL_FB_DIV_MASK) >> SPLL_FB_DIV_SHIFT;
		clk_s = (sclk_params.vCG_SPLL_SPREAD_SPECTRUM & CLK_S_MASK) >> CLK_S_SHIFT;
		clk_v = (sclk_params.vCG_SPLL_SPREAD_SPECTRUM_2 & CLK_V_MASK) >> CLK_V_SHIFT;

		fb_भाग &= ~0x00001FFF;
		fb_भाग >>= 1;
		clk_v >>= 6;

		अगर (p_भाग & ~(SMC_SISLANDS_SPLL_DIV_TABLE_PDIV_MASK >> SMC_SISLANDS_SPLL_DIV_TABLE_PDIV_SHIFT))
			ret = -EINVAL;
		अगर (fb_भाग & ~(SMC_SISLANDS_SPLL_DIV_TABLE_FBDIV_MASK >> SMC_SISLANDS_SPLL_DIV_TABLE_FBDIV_SHIFT))
			ret = -EINVAL;
		अगर (clk_s & ~(SMC_SISLANDS_SPLL_DIV_TABLE_CLKS_MASK >> SMC_SISLANDS_SPLL_DIV_TABLE_CLKS_SHIFT))
			ret = -EINVAL;
		अगर (clk_v & ~(SMC_SISLANDS_SPLL_DIV_TABLE_CLKV_MASK >> SMC_SISLANDS_SPLL_DIV_TABLE_CLKV_SHIFT))
			ret = -EINVAL;

		अगर (ret)
			अवरोध;

		पंचांगp = ((fb_भाग << SMC_SISLANDS_SPLL_DIV_TABLE_FBDIV_SHIFT) & SMC_SISLANDS_SPLL_DIV_TABLE_FBDIV_MASK) |
			((p_भाग << SMC_SISLANDS_SPLL_DIV_TABLE_PDIV_SHIFT) & SMC_SISLANDS_SPLL_DIV_TABLE_PDIV_MASK);
		spll_table->freq[i] = cpu_to_be32(पंचांगp);

		पंचांगp = ((clk_v << SMC_SISLANDS_SPLL_DIV_TABLE_CLKV_SHIFT) & SMC_SISLANDS_SPLL_DIV_TABLE_CLKV_MASK) |
			((clk_s << SMC_SISLANDS_SPLL_DIV_TABLE_CLKS_SHIFT) & SMC_SISLANDS_SPLL_DIV_TABLE_CLKS_MASK);
		spll_table->ss[i] = cpu_to_be32(पंचांगp);

		sclk += 512;
	पूर्ण


	अगर (!ret)
		ret = amdgpu_si_copy_bytes_to_smc(adev, si_pi->spll_table_start,
						  (u8 *)spll_table,
						  माप(SMC_SISLANDS_SPLL_DIV_TABLE),
						  si_pi->sram_end);

	अगर (ret)
		ni_pi->enable_घातer_containment = false;

	kमुक्त(spll_table);

	वापस ret;
पूर्ण

अटल u16 si_get_lower_of_leakage_and_vce_voltage(काष्ठा amdgpu_device *adev,
						   u16 vce_voltage)
अणु
	u16 highest_leakage = 0;
	काष्ठा si_घातer_info *si_pi = si_get_pi(adev);
	पूर्णांक i;

	क्रम (i = 0; i < si_pi->leakage_voltage.count; i++)अणु
		अगर (highest_leakage < si_pi->leakage_voltage.entries[i].voltage)
			highest_leakage = si_pi->leakage_voltage.entries[i].voltage;
	पूर्ण

	अगर (si_pi->leakage_voltage.count && (highest_leakage < vce_voltage))
		वापस highest_leakage;

	वापस vce_voltage;
पूर्ण

अटल पूर्णांक si_get_vce_घड़ी_voltage(काष्ठा amdgpu_device *adev,
				    u32 evclk, u32 ecclk, u16 *voltage)
अणु
	u32 i;
	पूर्णांक ret = -EINVAL;
	काष्ठा amdgpu_vce_घड़ी_voltage_dependency_table *table =
		&adev->pm.dpm.dyn_state.vce_घड़ी_voltage_dependency_table;

	अगर (((evclk == 0) && (ecclk == 0)) ||
	    (table && (table->count == 0))) अणु
		*voltage = 0;
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < table->count; i++) अणु
		अगर ((evclk <= table->entries[i].evclk) &&
		    (ecclk <= table->entries[i].ecclk)) अणु
			*voltage = table->entries[i].v;
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	/* अगर no match वापस the highest voltage */
	अगर (ret)
		*voltage = table->entries[table->count - 1].v;

	*voltage = si_get_lower_of_leakage_and_vce_voltage(adev, *voltage);

	वापस ret;
पूर्ण

अटल bool si_dpm_vblank_too_लघु(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	u32 vblank_समय = amdgpu_dpm_get_vblank_समय(adev);
	/* we never hit the non-gddr5 limit so disable it */
	u32 चयन_limit = adev->gmc.vram_type == AMDGPU_VRAM_TYPE_GDDR5 ? 450 : 0;

	अगर (vblank_समय < चयन_limit)
		वापस true;
	अन्यथा
		वापस false;

पूर्ण

अटल पूर्णांक ni_copy_and_चयन_arb_sets(काष्ठा amdgpu_device *adev,
				u32 arb_freq_src, u32 arb_freq_dest)
अणु
	u32 mc_arb_dram_timing;
	u32 mc_arb_dram_timing2;
	u32 burst_समय;
	u32 mc_cg_config;

	चयन (arb_freq_src) अणु
	हाल MC_CG_ARB_FREQ_F0:
		mc_arb_dram_timing  = RREG32(MC_ARB_DRAM_TIMING);
		mc_arb_dram_timing2 = RREG32(MC_ARB_DRAM_TIMING2);
		burst_समय = (RREG32(MC_ARB_BURST_TIME) & STATE0_MASK) >> STATE0_SHIFT;
		अवरोध;
	हाल MC_CG_ARB_FREQ_F1:
		mc_arb_dram_timing  = RREG32(MC_ARB_DRAM_TIMING_1);
		mc_arb_dram_timing2 = RREG32(MC_ARB_DRAM_TIMING2_1);
		burst_समय = (RREG32(MC_ARB_BURST_TIME) & STATE1_MASK) >> STATE1_SHIFT;
		अवरोध;
	हाल MC_CG_ARB_FREQ_F2:
		mc_arb_dram_timing  = RREG32(MC_ARB_DRAM_TIMING_2);
		mc_arb_dram_timing2 = RREG32(MC_ARB_DRAM_TIMING2_2);
		burst_समय = (RREG32(MC_ARB_BURST_TIME) & STATE2_MASK) >> STATE2_SHIFT;
		अवरोध;
	हाल MC_CG_ARB_FREQ_F3:
		mc_arb_dram_timing  = RREG32(MC_ARB_DRAM_TIMING_3);
		mc_arb_dram_timing2 = RREG32(MC_ARB_DRAM_TIMING2_3);
		burst_समय = (RREG32(MC_ARB_BURST_TIME) & STATE3_MASK) >> STATE3_SHIFT;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (arb_freq_dest) अणु
	हाल MC_CG_ARB_FREQ_F0:
		WREG32(MC_ARB_DRAM_TIMING, mc_arb_dram_timing);
		WREG32(MC_ARB_DRAM_TIMING2, mc_arb_dram_timing2);
		WREG32_P(MC_ARB_BURST_TIME, STATE0(burst_समय), ~STATE0_MASK);
		अवरोध;
	हाल MC_CG_ARB_FREQ_F1:
		WREG32(MC_ARB_DRAM_TIMING_1, mc_arb_dram_timing);
		WREG32(MC_ARB_DRAM_TIMING2_1, mc_arb_dram_timing2);
		WREG32_P(MC_ARB_BURST_TIME, STATE1(burst_समय), ~STATE1_MASK);
		अवरोध;
	हाल MC_CG_ARB_FREQ_F2:
		WREG32(MC_ARB_DRAM_TIMING_2, mc_arb_dram_timing);
		WREG32(MC_ARB_DRAM_TIMING2_2, mc_arb_dram_timing2);
		WREG32_P(MC_ARB_BURST_TIME, STATE2(burst_समय), ~STATE2_MASK);
		अवरोध;
	हाल MC_CG_ARB_FREQ_F3:
		WREG32(MC_ARB_DRAM_TIMING_3, mc_arb_dram_timing);
		WREG32(MC_ARB_DRAM_TIMING2_3, mc_arb_dram_timing2);
		WREG32_P(MC_ARB_BURST_TIME, STATE3(burst_समय), ~STATE3_MASK);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	mc_cg_config = RREG32(MC_CG_CONFIG) | 0x0000000F;
	WREG32(MC_CG_CONFIG, mc_cg_config);
	WREG32_P(MC_ARB_CG, CG_ARB_REQ(arb_freq_dest), ~CG_ARB_REQ_MASK);

	वापस 0;
पूर्ण

अटल व्योम ni_update_current_ps(काष्ठा amdgpu_device *adev,
			  काष्ठा amdgpu_ps *rps)
अणु
	काष्ठा si_ps *new_ps = si_get_ps(rps);
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(adev);
	काष्ठा ni_घातer_info *ni_pi = ni_get_pi(adev);

	eg_pi->current_rps = *rps;
	ni_pi->current_ps = *new_ps;
	eg_pi->current_rps.ps_priv = &ni_pi->current_ps;
	adev->pm.dpm.current_ps = &eg_pi->current_rps;
पूर्ण

अटल व्योम ni_update_requested_ps(काष्ठा amdgpu_device *adev,
			    काष्ठा amdgpu_ps *rps)
अणु
	काष्ठा si_ps *new_ps = si_get_ps(rps);
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(adev);
	काष्ठा ni_घातer_info *ni_pi = ni_get_pi(adev);

	eg_pi->requested_rps = *rps;
	ni_pi->requested_ps = *new_ps;
	eg_pi->requested_rps.ps_priv = &ni_pi->requested_ps;
	adev->pm.dpm.requested_ps = &eg_pi->requested_rps;
पूर्ण

अटल व्योम ni_set_uvd_घड़ी_beक्रमe_set_eng_घड़ी(काष्ठा amdgpu_device *adev,
					   काष्ठा amdgpu_ps *new_ps,
					   काष्ठा amdgpu_ps *old_ps)
अणु
	काष्ठा si_ps *new_state = si_get_ps(new_ps);
	काष्ठा si_ps *current_state = si_get_ps(old_ps);

	अगर ((new_ps->vclk == old_ps->vclk) &&
	    (new_ps->dclk == old_ps->dclk))
		वापस;

	अगर (new_state->perक्रमmance_levels[new_state->perक्रमmance_level_count - 1].sclk >=
	    current_state->perक्रमmance_levels[current_state->perक्रमmance_level_count - 1].sclk)
		वापस;

	amdgpu_asic_set_uvd_घड़ीs(adev, new_ps->vclk, new_ps->dclk);
पूर्ण

अटल व्योम ni_set_uvd_घड़ी_after_set_eng_घड़ी(काष्ठा amdgpu_device *adev,
					  काष्ठा amdgpu_ps *new_ps,
					  काष्ठा amdgpu_ps *old_ps)
अणु
	काष्ठा si_ps *new_state = si_get_ps(new_ps);
	काष्ठा si_ps *current_state = si_get_ps(old_ps);

	अगर ((new_ps->vclk == old_ps->vclk) &&
	    (new_ps->dclk == old_ps->dclk))
		वापस;

	अगर (new_state->perक्रमmance_levels[new_state->perक्रमmance_level_count - 1].sclk <
	    current_state->perक्रमmance_levels[current_state->perक्रमmance_level_count - 1].sclk)
		वापस;

	amdgpu_asic_set_uvd_घड़ीs(adev, new_ps->vclk, new_ps->dclk);
पूर्ण

अटल u16 btc_find_voltage(काष्ठा atom_voltage_table *table, u16 voltage)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < table->count; i++)
		अगर (voltage <= table->entries[i].value)
			वापस table->entries[i].value;

	वापस table->entries[table->count - 1].value;
पूर्ण

अटल u32 btc_find_valid_घड़ी(काष्ठा amdgpu_घड़ी_array *घड़ीs,
		                u32 max_घड़ी, u32 requested_घड़ी)
अणु
	अचिन्हित पूर्णांक i;

	अगर ((घड़ीs == शून्य) || (घड़ीs->count == 0))
		वापस (requested_घड़ी < max_घड़ी) ? requested_घड़ी : max_घड़ी;

	क्रम (i = 0; i < घड़ीs->count; i++) अणु
		अगर (घड़ीs->values[i] >= requested_घड़ी)
			वापस (घड़ीs->values[i] < max_घड़ी) ? घड़ीs->values[i] : max_घड़ी;
	पूर्ण

	वापस (घड़ीs->values[घड़ीs->count - 1] < max_घड़ी) ?
		घड़ीs->values[घड़ीs->count - 1] : max_घड़ी;
पूर्ण

अटल u32 btc_get_valid_mclk(काष्ठा amdgpu_device *adev,
			      u32 max_mclk, u32 requested_mclk)
अणु
	वापस btc_find_valid_घड़ी(&adev->pm.dpm.dyn_state.valid_mclk_values,
				    max_mclk, requested_mclk);
पूर्ण

अटल u32 btc_get_valid_sclk(काष्ठा amdgpu_device *adev,
		              u32 max_sclk, u32 requested_sclk)
अणु
	वापस btc_find_valid_घड़ी(&adev->pm.dpm.dyn_state.valid_sclk_values,
				    max_sclk, requested_sclk);
पूर्ण

अटल व्योम btc_get_max_घड़ी_from_voltage_dependency_table(काष्ठा amdgpu_घड़ी_voltage_dependency_table *table,
							    u32 *max_घड़ी)
अणु
	u32 i, घड़ी = 0;

	अगर ((table == शून्य) || (table->count == 0)) अणु
		*max_घड़ी = घड़ी;
		वापस;
	पूर्ण

	क्रम (i = 0; i < table->count; i++) अणु
		अगर (घड़ी < table->entries[i].clk)
			घड़ी = table->entries[i].clk;
	पूर्ण
	*max_घड़ी = घड़ी;
पूर्ण

अटल व्योम btc_apply_voltage_dependency_rules(काष्ठा amdgpu_घड़ी_voltage_dependency_table *table,
					       u32 घड़ी, u16 max_voltage, u16 *voltage)
अणु
	u32 i;

	अगर ((table == शून्य) || (table->count == 0))
		वापस;

	क्रम (i= 0; i < table->count; i++) अणु
		अगर (घड़ी <= table->entries[i].clk) अणु
			अगर (*voltage < table->entries[i].v)
				*voltage = (u16)((table->entries[i].v < max_voltage) ?
					   table->entries[i].v : max_voltage);
			वापस;
		पूर्ण
	पूर्ण

	*voltage = (*voltage > max_voltage) ? *voltage : max_voltage;
पूर्ण

अटल व्योम btc_adjust_घड़ी_combinations(काष्ठा amdgpu_device *adev,
					  स्थिर काष्ठा amdgpu_घड़ी_and_voltage_limits *max_limits,
					  काष्ठा rv7xx_pl *pl)
अणु

	अगर ((pl->mclk == 0) || (pl->sclk == 0))
		वापस;

	अगर (pl->mclk == pl->sclk)
		वापस;

	अगर (pl->mclk > pl->sclk) अणु
		अगर (((pl->mclk + (pl->sclk - 1)) / pl->sclk) > adev->pm.dpm.dyn_state.mclk_sclk_ratio)
			pl->sclk = btc_get_valid_sclk(adev,
						      max_limits->sclk,
						      (pl->mclk +
						      (adev->pm.dpm.dyn_state.mclk_sclk_ratio - 1)) /
						      adev->pm.dpm.dyn_state.mclk_sclk_ratio);
	पूर्ण अन्यथा अणु
		अगर ((pl->sclk - pl->mclk) > adev->pm.dpm.dyn_state.sclk_mclk_delta)
			pl->mclk = btc_get_valid_mclk(adev,
						      max_limits->mclk,
						      pl->sclk -
						      adev->pm.dpm.dyn_state.sclk_mclk_delta);
	पूर्ण
पूर्ण

अटल व्योम btc_apply_voltage_delta_rules(काष्ठा amdgpu_device *adev,
					  u16 max_vddc, u16 max_vddci,
					  u16 *vddc, u16 *vddci)
अणु
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(adev);
	u16 new_voltage;

	अगर ((0 == *vddc) || (0 == *vddci))
		वापस;

	अगर (*vddc > *vddci) अणु
		अगर ((*vddc - *vddci) > adev->pm.dpm.dyn_state.vddc_vddci_delta) अणु
			new_voltage = btc_find_voltage(&eg_pi->vddci_voltage_table,
						       (*vddc - adev->pm.dpm.dyn_state.vddc_vddci_delta));
			*vddci = (new_voltage < max_vddci) ? new_voltage : max_vddci;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((*vddci - *vddc) > adev->pm.dpm.dyn_state.vddc_vddci_delta) अणु
			new_voltage = btc_find_voltage(&eg_pi->vddc_voltage_table,
						       (*vddci - adev->pm.dpm.dyn_state.vddc_vddci_delta));
			*vddc = (new_voltage < max_vddc) ? new_voltage : max_vddc;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम r600_calculate_u_and_p(u32 i, u32 r_c, u32 p_b,
			    u32 *p, u32 *u)
अणु
	u32 b_c = 0;
	u32 i_c;
	u32 पंचांगp;

	i_c = (i * r_c) / 100;
	पंचांगp = i_c >> p_b;

	जबतक (पंचांगp) अणु
		b_c++;
		पंचांगp >>= 1;
	पूर्ण

	*u = (b_c + 1) / 2;
	*p = i_c / (1 << (2 * (*u)));
पूर्ण

अटल पूर्णांक r600_calculate_at(u32 t, u32 h, u32 fh, u32 fl, u32 *tl, u32 *th)
अणु
	u32 k, a, ah, al;
	u32 t1;

	अगर ((fl == 0) || (fh == 0) || (fl > fh))
		वापस -EINVAL;

	k = (100 * fh) / fl;
	t1 = (t * (k - 100));
	a = (1000 * (100 * h + t1)) / (10000 + (t1 / 100));
	a = (a + 5) / 10;
	ah = ((a * t) + 5000) / 10000;
	al = a - ah;

	*th = t - ah;
	*tl = t + al;

	वापस 0;
पूर्ण

अटल bool r600_is_uvd_state(u32 class, u32 class2)
अणु
	अगर (class & ATOM_PPLIB_CLASSIFICATION_UVDSTATE)
		वापस true;
	अगर (class & ATOM_PPLIB_CLASSIFICATION_HD2STATE)
		वापस true;
	अगर (class & ATOM_PPLIB_CLASSIFICATION_HDSTATE)
		वापस true;
	अगर (class & ATOM_PPLIB_CLASSIFICATION_SDSTATE)
		वापस true;
	अगर (class2 & ATOM_PPLIB_CLASSIFICATION2_MVC)
		वापस true;
	वापस false;
पूर्ण

अटल u8 rv770_get_memory_module_index(काष्ठा amdgpu_device *adev)
अणु
	वापस (u8) ((RREG32(BIOS_SCRATCH_4) >> 16) & 0xff);
पूर्ण

अटल व्योम rv770_get_max_vddc(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(adev);
	u16 vddc;

	अगर (amdgpu_atombios_get_max_vddc(adev, 0, 0, &vddc))
		pi->max_vddc = 0;
	अन्यथा
		pi->max_vddc = vddc;
पूर्ण

अटल व्योम rv770_get_engine_memory_ss(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(adev);
	काष्ठा amdgpu_atom_ss ss;

	pi->sclk_ss = amdgpu_atombios_get_asic_ss_info(adev, &ss,
						       ASIC_INTERNAL_ENGINE_SS, 0);
	pi->mclk_ss = amdgpu_atombios_get_asic_ss_info(adev, &ss,
						       ASIC_INTERNAL_MEMORY_SS, 0);

	अगर (pi->sclk_ss || pi->mclk_ss)
		pi->dynamic_ss = true;
	अन्यथा
		pi->dynamic_ss = false;
पूर्ण


अटल व्योम si_apply_state_adjust_rules(काष्ठा amdgpu_device *adev,
					काष्ठा amdgpu_ps *rps)
अणु
	काष्ठा  si_ps *ps = si_get_ps(rps);
	काष्ठा amdgpu_घड़ी_and_voltage_limits *max_limits;
	bool disable_mclk_चयनing = false;
	bool disable_sclk_चयनing = false;
	u32 mclk, sclk;
	u16 vddc, vddci, min_vce_voltage = 0;
	u32 max_sclk_vddc, max_mclk_vddci, max_mclk_vddc;
	u32 max_sclk = 0, max_mclk = 0;
	पूर्णांक i;

	अगर (adev->asic_type == CHIP_HAIन_अंक) अणु
		अगर ((adev->pdev->revision == 0x81) ||
		    (adev->pdev->revision == 0xC3) ||
		    (adev->pdev->device == 0x6664) ||
		    (adev->pdev->device == 0x6665) ||
		    (adev->pdev->device == 0x6667)) अणु
			max_sclk = 75000;
		पूर्ण
		अगर ((adev->pdev->revision == 0xC3) ||
		    (adev->pdev->device == 0x6665)) अणु
			max_sclk = 60000;
			max_mclk = 80000;
		पूर्ण
	पूर्ण अन्यथा अगर (adev->asic_type == CHIP_OLAND) अणु
		अगर ((adev->pdev->revision == 0xC7) ||
		    (adev->pdev->revision == 0x80) ||
		    (adev->pdev->revision == 0x81) ||
		    (adev->pdev->revision == 0x83) ||
		    (adev->pdev->revision == 0x87) ||
		    (adev->pdev->device == 0x6604) ||
		    (adev->pdev->device == 0x6605)) अणु
			max_sclk = 75000;
		पूर्ण
	पूर्ण

	अगर (rps->vce_active) अणु
		rps->evclk = adev->pm.dpm.vce_states[adev->pm.dpm.vce_level].evclk;
		rps->ecclk = adev->pm.dpm.vce_states[adev->pm.dpm.vce_level].ecclk;
		si_get_vce_घड़ी_voltage(adev, rps->evclk, rps->ecclk,
					 &min_vce_voltage);
	पूर्ण अन्यथा अणु
		rps->evclk = 0;
		rps->ecclk = 0;
	पूर्ण

	अगर ((adev->pm.dpm.new_active_crtc_count > 1) ||
	    si_dpm_vblank_too_लघु(adev))
		disable_mclk_चयनing = true;

	अगर (rps->vclk || rps->dclk) अणु
		disable_mclk_चयनing = true;
		disable_sclk_चयनing = true;
	पूर्ण

	अगर (adev->pm.ac_घातer)
		max_limits = &adev->pm.dpm.dyn_state.max_घड़ी_voltage_on_ac;
	अन्यथा
		max_limits = &adev->pm.dpm.dyn_state.max_घड़ी_voltage_on_dc;

	क्रम (i = ps->perक्रमmance_level_count - 2; i >= 0; i--) अणु
		अगर (ps->perक्रमmance_levels[i].vddc > ps->perक्रमmance_levels[i+1].vddc)
			ps->perक्रमmance_levels[i].vddc = ps->perक्रमmance_levels[i+1].vddc;
	पूर्ण
	अगर (adev->pm.ac_घातer == false) अणु
		क्रम (i = 0; i < ps->perक्रमmance_level_count; i++) अणु
			अगर (ps->perक्रमmance_levels[i].mclk > max_limits->mclk)
				ps->perक्रमmance_levels[i].mclk = max_limits->mclk;
			अगर (ps->perक्रमmance_levels[i].sclk > max_limits->sclk)
				ps->perक्रमmance_levels[i].sclk = max_limits->sclk;
			अगर (ps->perक्रमmance_levels[i].vddc > max_limits->vddc)
				ps->perक्रमmance_levels[i].vddc = max_limits->vddc;
			अगर (ps->perक्रमmance_levels[i].vddci > max_limits->vddci)
				ps->perक्रमmance_levels[i].vddci = max_limits->vddci;
		पूर्ण
	पूर्ण

	/* limit घड़ीs to max supported घड़ीs based on voltage dependency tables */
	btc_get_max_घड़ी_from_voltage_dependency_table(&adev->pm.dpm.dyn_state.vddc_dependency_on_sclk,
							&max_sclk_vddc);
	btc_get_max_घड़ी_from_voltage_dependency_table(&adev->pm.dpm.dyn_state.vddci_dependency_on_mclk,
							&max_mclk_vddci);
	btc_get_max_घड़ी_from_voltage_dependency_table(&adev->pm.dpm.dyn_state.vddc_dependency_on_mclk,
							&max_mclk_vddc);

	क्रम (i = 0; i < ps->perक्रमmance_level_count; i++) अणु
		अगर (max_sclk_vddc) अणु
			अगर (ps->perक्रमmance_levels[i].sclk > max_sclk_vddc)
				ps->perक्रमmance_levels[i].sclk = max_sclk_vddc;
		पूर्ण
		अगर (max_mclk_vddci) अणु
			अगर (ps->perक्रमmance_levels[i].mclk > max_mclk_vddci)
				ps->perक्रमmance_levels[i].mclk = max_mclk_vddci;
		पूर्ण
		अगर (max_mclk_vddc) अणु
			अगर (ps->perक्रमmance_levels[i].mclk > max_mclk_vddc)
				ps->perक्रमmance_levels[i].mclk = max_mclk_vddc;
		पूर्ण
		अगर (max_mclk) अणु
			अगर (ps->perक्रमmance_levels[i].mclk > max_mclk)
				ps->perक्रमmance_levels[i].mclk = max_mclk;
		पूर्ण
		अगर (max_sclk) अणु
			अगर (ps->perक्रमmance_levels[i].sclk > max_sclk)
				ps->perक्रमmance_levels[i].sclk = max_sclk;
		पूर्ण
	पूर्ण

	/* XXX validate the min घड़ीs required क्रम display */

	अगर (disable_mclk_चयनing) अणु
		mclk  = ps->perक्रमmance_levels[ps->perक्रमmance_level_count - 1].mclk;
		vddci = ps->perक्रमmance_levels[ps->perक्रमmance_level_count - 1].vddci;
	पूर्ण अन्यथा अणु
		mclk = ps->perक्रमmance_levels[0].mclk;
		vddci = ps->perक्रमmance_levels[0].vddci;
	पूर्ण

	अगर (disable_sclk_चयनing) अणु
		sclk = ps->perक्रमmance_levels[ps->perक्रमmance_level_count - 1].sclk;
		vddc = ps->perक्रमmance_levels[ps->perक्रमmance_level_count - 1].vddc;
	पूर्ण अन्यथा अणु
		sclk = ps->perक्रमmance_levels[0].sclk;
		vddc = ps->perक्रमmance_levels[0].vddc;
	पूर्ण

	अगर (rps->vce_active) अणु
		अगर (sclk < adev->pm.dpm.vce_states[adev->pm.dpm.vce_level].sclk)
			sclk = adev->pm.dpm.vce_states[adev->pm.dpm.vce_level].sclk;
		अगर (mclk < adev->pm.dpm.vce_states[adev->pm.dpm.vce_level].mclk)
			mclk = adev->pm.dpm.vce_states[adev->pm.dpm.vce_level].mclk;
	पूर्ण

	/* adjusted low state */
	ps->perक्रमmance_levels[0].sclk = sclk;
	ps->perक्रमmance_levels[0].mclk = mclk;
	ps->perक्रमmance_levels[0].vddc = vddc;
	ps->perक्रमmance_levels[0].vddci = vddci;

	अगर (disable_sclk_चयनing) अणु
		sclk = ps->perक्रमmance_levels[0].sclk;
		क्रम (i = 1; i < ps->perक्रमmance_level_count; i++) अणु
			अगर (sclk < ps->perक्रमmance_levels[i].sclk)
				sclk = ps->perक्रमmance_levels[i].sclk;
		पूर्ण
		क्रम (i = 0; i < ps->perक्रमmance_level_count; i++) अणु
			ps->perक्रमmance_levels[i].sclk = sclk;
			ps->perक्रमmance_levels[i].vddc = vddc;
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 1; i < ps->perक्रमmance_level_count; i++) अणु
			अगर (ps->perक्रमmance_levels[i].sclk < ps->perक्रमmance_levels[i - 1].sclk)
				ps->perक्रमmance_levels[i].sclk = ps->perक्रमmance_levels[i - 1].sclk;
			अगर (ps->perक्रमmance_levels[i].vddc < ps->perक्रमmance_levels[i - 1].vddc)
				ps->perक्रमmance_levels[i].vddc = ps->perक्रमmance_levels[i - 1].vddc;
		पूर्ण
	पूर्ण

	अगर (disable_mclk_चयनing) अणु
		mclk = ps->perक्रमmance_levels[0].mclk;
		क्रम (i = 1; i < ps->perक्रमmance_level_count; i++) अणु
			अगर (mclk < ps->perक्रमmance_levels[i].mclk)
				mclk = ps->perक्रमmance_levels[i].mclk;
		पूर्ण
		क्रम (i = 0; i < ps->perक्रमmance_level_count; i++) अणु
			ps->perक्रमmance_levels[i].mclk = mclk;
			ps->perक्रमmance_levels[i].vddci = vddci;
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 1; i < ps->perक्रमmance_level_count; i++) अणु
			अगर (ps->perक्रमmance_levels[i].mclk < ps->perक्रमmance_levels[i - 1].mclk)
				ps->perक्रमmance_levels[i].mclk = ps->perक्रमmance_levels[i - 1].mclk;
			अगर (ps->perक्रमmance_levels[i].vddci < ps->perक्रमmance_levels[i - 1].vddci)
				ps->perक्रमmance_levels[i].vddci = ps->perक्रमmance_levels[i - 1].vddci;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < ps->perक्रमmance_level_count; i++)
		btc_adjust_घड़ी_combinations(adev, max_limits,
					      &ps->perक्रमmance_levels[i]);

	क्रम (i = 0; i < ps->perक्रमmance_level_count; i++) अणु
		अगर (ps->perक्रमmance_levels[i].vddc < min_vce_voltage)
			ps->perक्रमmance_levels[i].vddc = min_vce_voltage;
		btc_apply_voltage_dependency_rules(&adev->pm.dpm.dyn_state.vddc_dependency_on_sclk,
						   ps->perक्रमmance_levels[i].sclk,
						   max_limits->vddc,  &ps->perक्रमmance_levels[i].vddc);
		btc_apply_voltage_dependency_rules(&adev->pm.dpm.dyn_state.vddci_dependency_on_mclk,
						   ps->perक्रमmance_levels[i].mclk,
						   max_limits->vddci, &ps->perक्रमmance_levels[i].vddci);
		btc_apply_voltage_dependency_rules(&adev->pm.dpm.dyn_state.vddc_dependency_on_mclk,
						   ps->perक्रमmance_levels[i].mclk,
						   max_limits->vddc,  &ps->perक्रमmance_levels[i].vddc);
		btc_apply_voltage_dependency_rules(&adev->pm.dpm.dyn_state.vddc_dependency_on_dispclk,
						   adev->घड़ी.current_dispclk,
						   max_limits->vddc,  &ps->perक्रमmance_levels[i].vddc);
	पूर्ण

	क्रम (i = 0; i < ps->perक्रमmance_level_count; i++) अणु
		btc_apply_voltage_delta_rules(adev,
					      max_limits->vddc, max_limits->vddci,
					      &ps->perक्रमmance_levels[i].vddc,
					      &ps->perक्रमmance_levels[i].vddci);
	पूर्ण

	ps->dc_compatible = true;
	क्रम (i = 0; i < ps->perक्रमmance_level_count; i++) अणु
		अगर (ps->perक्रमmance_levels[i].vddc > adev->pm.dpm.dyn_state.max_घड़ी_voltage_on_dc.vddc)
			ps->dc_compatible = false;
	पूर्ण
पूर्ण

#अगर 0
अटल पूर्णांक si_पढ़ो_smc_soft_रेजिस्टर(काष्ठा amdgpu_device *adev,
				     u16 reg_offset, u32 *value)
अणु
	काष्ठा si_घातer_info *si_pi = si_get_pi(adev);

	वापस amdgpu_si_पढ़ो_smc_sram_dword(adev,
					     si_pi->soft_regs_start + reg_offset, value,
					     si_pi->sram_end);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक si_ग_लिखो_smc_soft_रेजिस्टर(काष्ठा amdgpu_device *adev,
				      u16 reg_offset, u32 value)
अणु
	काष्ठा si_घातer_info *si_pi = si_get_pi(adev);

	वापस amdgpu_si_ग_लिखो_smc_sram_dword(adev,
					      si_pi->soft_regs_start + reg_offset,
					      value, si_pi->sram_end);
पूर्ण

अटल bool si_is_special_1gb_platक्रमm(काष्ठा amdgpu_device *adev)
अणु
	bool ret = false;
	u32 पंचांगp, width, row, column, bank, density;
	bool is_memory_gddr5, is_special;

	पंचांगp = RREG32(MC_SEQ_MISC0);
	is_memory_gddr5 = (MC_SEQ_MISC0_GDDR5_VALUE == ((पंचांगp & MC_SEQ_MISC0_GDDR5_MASK) >> MC_SEQ_MISC0_GDDR5_SHIFT));
	is_special = (MC_SEQ_MISC0_REV_ID_VALUE == ((पंचांगp & MC_SEQ_MISC0_REV_ID_MASK) >> MC_SEQ_MISC0_REV_ID_SHIFT))
		& (MC_SEQ_MISC0_VEN_ID_VALUE == ((पंचांगp & MC_SEQ_MISC0_VEN_ID_MASK) >> MC_SEQ_MISC0_VEN_ID_SHIFT));

	WREG32(MC_SEQ_IO_DEBUG_INDEX, 0xb);
	width = ((RREG32(MC_SEQ_IO_DEBUG_DATA) >> 1) & 1) ? 16 : 32;

	पंचांगp = RREG32(MC_ARB_RAMCFG);
	row = ((पंचांगp & NOOFROWS_MASK) >> NOOFROWS_SHIFT) + 10;
	column = ((पंचांगp & NOOFCOLS_MASK) >> NOOFCOLS_SHIFT) + 8;
	bank = ((पंचांगp & NOOFBANK_MASK) >> NOOFBANK_SHIFT) + 2;

	density = (1 << (row + column - 20 + bank)) * width;

	अगर ((adev->pdev->device == 0x6819) &&
	    is_memory_gddr5 && is_special && (density == 0x400))
		ret = true;

	वापस ret;
पूर्ण

अटल व्योम si_get_leakage_vddc(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा si_घातer_info *si_pi = si_get_pi(adev);
	u16 vddc, count = 0;
	पूर्णांक i, ret;

	क्रम (i = 0; i < SISLANDS_MAX_LEAKAGE_COUNT; i++) अणु
		ret = amdgpu_atombios_get_leakage_vddc_based_on_leakage_idx(adev, &vddc, SISLANDS_LEAKAGE_INDEX0 + i);

		अगर (!ret && (vddc > 0) && (vddc != (SISLANDS_LEAKAGE_INDEX0 + i))) अणु
			si_pi->leakage_voltage.entries[count].voltage = vddc;
			si_pi->leakage_voltage.entries[count].leakage_index =
				SISLANDS_LEAKAGE_INDEX0 + i;
			count++;
		पूर्ण
	पूर्ण
	si_pi->leakage_voltage.count = count;
पूर्ण

अटल पूर्णांक si_get_leakage_voltage_from_leakage_index(काष्ठा amdgpu_device *adev,
						     u32 index, u16 *leakage_voltage)
अणु
	काष्ठा si_घातer_info *si_pi = si_get_pi(adev);
	पूर्णांक i;

	अगर (leakage_voltage == शून्य)
		वापस -EINVAL;

	अगर ((index & 0xff00) != 0xff00)
		वापस -EINVAL;

	अगर ((index & 0xff) > SISLANDS_MAX_LEAKAGE_COUNT + 1)
		वापस -EINVAL;

	अगर (index < SISLANDS_LEAKAGE_INDEX0)
		वापस -EINVAL;

	क्रम (i = 0; i < si_pi->leakage_voltage.count; i++) अणु
		अगर (si_pi->leakage_voltage.entries[i].leakage_index == index) अणु
			*leakage_voltage = si_pi->leakage_voltage.entries[i].voltage;
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -EAGAIN;
पूर्ण

अटल व्योम si_set_dpm_event_sources(काष्ठा amdgpu_device *adev, u32 sources)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(adev);
	bool want_thermal_protection;
	क्रमागत amdgpu_dpm_event_src dpm_event_src;

	चयन (sources) अणु
	हाल 0:
	शेष:
		want_thermal_protection = false;
		अवरोध;
	हाल (1 << AMDGPU_DPM_AUTO_THROTTLE_SRC_THERMAL):
		want_thermal_protection = true;
		dpm_event_src = AMDGPU_DPM_EVENT_SRC_DIGITAL;
		अवरोध;
	हाल (1 << AMDGPU_DPM_AUTO_THROTTLE_SRC_EXTERNAL):
		want_thermal_protection = true;
		dpm_event_src = AMDGPU_DPM_EVENT_SRC_EXTERNAL;
		अवरोध;
	हाल ((1 << AMDGPU_DPM_AUTO_THROTTLE_SRC_EXTERNAL) |
	      (1 << AMDGPU_DPM_AUTO_THROTTLE_SRC_THERMAL)):
		want_thermal_protection = true;
		dpm_event_src = AMDGPU_DPM_EVENT_SRC_DIGIAL_OR_EXTERNAL;
		अवरोध;
	पूर्ण

	अगर (want_thermal_protection) अणु
		WREG32_P(CG_THERMAL_CTRL, DPM_EVENT_SRC(dpm_event_src), ~DPM_EVENT_SRC_MASK);
		अगर (pi->thermal_protection)
			WREG32_P(GENERAL_PWRMGT, 0, ~THERMAL_PROTECTION_DIS);
	पूर्ण अन्यथा अणु
		WREG32_P(GENERAL_PWRMGT, THERMAL_PROTECTION_DIS, ~THERMAL_PROTECTION_DIS);
	पूर्ण
पूर्ण

अटल व्योम si_enable_स्वतः_throttle_source(काष्ठा amdgpu_device *adev,
					   क्रमागत amdgpu_dpm_स्वतः_throttle_src source,
					   bool enable)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(adev);

	अगर (enable) अणु
		अगर (!(pi->active_स्वतः_throttle_sources & (1 << source))) अणु
			pi->active_स्वतः_throttle_sources |= 1 << source;
			si_set_dpm_event_sources(adev, pi->active_स्वतः_throttle_sources);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (pi->active_स्वतः_throttle_sources & (1 << source)) अणु
			pi->active_स्वतः_throttle_sources &= ~(1 << source);
			si_set_dpm_event_sources(adev, pi->active_स्वतः_throttle_sources);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम si_start_dpm(काष्ठा amdgpu_device *adev)
अणु
	WREG32_P(GENERAL_PWRMGT, GLOBAL_PWRMGT_EN, ~GLOBAL_PWRMGT_EN);
पूर्ण

अटल व्योम si_stop_dpm(काष्ठा amdgpu_device *adev)
अणु
	WREG32_P(GENERAL_PWRMGT, 0, ~GLOBAL_PWRMGT_EN);
पूर्ण

अटल व्योम si_enable_sclk_control(काष्ठा amdgpu_device *adev, bool enable)
अणु
	अगर (enable)
		WREG32_P(SCLK_PWRMGT_CNTL, 0, ~SCLK_PWRMGT_OFF);
	अन्यथा
		WREG32_P(SCLK_PWRMGT_CNTL, SCLK_PWRMGT_OFF, ~SCLK_PWRMGT_OFF);

पूर्ण

#अगर 0
अटल पूर्णांक si_notअगरy_hardware_of_thermal_state(काष्ठा amdgpu_device *adev,
					       u32 thermal_level)
अणु
	PPSMC_Result ret;

	अगर (thermal_level == 0) अणु
		ret = amdgpu_si_send_msg_to_smc(adev, PPSMC_MSG_EnableThermalInterrupt);
		अगर (ret == PPSMC_Result_OK)
			वापस 0;
		अन्यथा
			वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम si_notअगरy_hardware_vpu_recovery_event(काष्ठा amdgpu_device *adev)
अणु
	si_ग_लिखो_smc_soft_रेजिस्टर(adev, SI_SMC_SOFT_REGISTER_tdr_is_about_to_happen, true);
पूर्ण
#पूर्ण_अगर

#अगर 0
अटल पूर्णांक si_notअगरy_hw_of_घातersource(काष्ठा amdgpu_device *adev, bool ac_घातer)
अणु
	अगर (ac_घातer)
		वापस (amdgpu_si_send_msg_to_smc(adev, PPSMC_MSG_RunningOnAC) == PPSMC_Result_OK) ?
			0 : -EINVAL;

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल PPSMC_Result si_send_msg_to_smc_with_parameter(काष्ठा amdgpu_device *adev,
						      PPSMC_Msg msg, u32 parameter)
अणु
	WREG32(SMC_SCRATCH0, parameter);
	वापस amdgpu_si_send_msg_to_smc(adev, msg);
पूर्ण

अटल पूर्णांक si_restrict_perक्रमmance_levels_beक्रमe_चयन(काष्ठा amdgpu_device *adev)
अणु
	अगर (amdgpu_si_send_msg_to_smc(adev, PPSMC_MSG_NoForcedLevel) != PPSMC_Result_OK)
		वापस -EINVAL;

	वापस (si_send_msg_to_smc_with_parameter(adev, PPSMC_MSG_SetEnabledLevels, 1) == PPSMC_Result_OK) ?
		0 : -EINVAL;
पूर्ण

अटल पूर्णांक si_dpm_क्रमce_perक्रमmance_level(व्योम *handle,
				   क्रमागत amd_dpm_क्रमced_level level)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	काष्ठा amdgpu_ps *rps = adev->pm.dpm.current_ps;
	काष्ठा  si_ps *ps = si_get_ps(rps);
	u32 levels = ps->perक्रमmance_level_count;

	अगर (level == AMD_DPM_FORCED_LEVEL_HIGH) अणु
		अगर (si_send_msg_to_smc_with_parameter(adev, PPSMC_MSG_SetEnabledLevels, levels) != PPSMC_Result_OK)
			वापस -EINVAL;

		अगर (si_send_msg_to_smc_with_parameter(adev, PPSMC_MSG_SetForcedLevels, 1) != PPSMC_Result_OK)
			वापस -EINVAL;
	पूर्ण अन्यथा अगर (level == AMD_DPM_FORCED_LEVEL_LOW) अणु
		अगर (si_send_msg_to_smc_with_parameter(adev, PPSMC_MSG_SetForcedLevels, 0) != PPSMC_Result_OK)
			वापस -EINVAL;

		अगर (si_send_msg_to_smc_with_parameter(adev, PPSMC_MSG_SetEnabledLevels, 1) != PPSMC_Result_OK)
			वापस -EINVAL;
	पूर्ण अन्यथा अगर (level == AMD_DPM_FORCED_LEVEL_AUTO) अणु
		अगर (si_send_msg_to_smc_with_parameter(adev, PPSMC_MSG_SetForcedLevels, 0) != PPSMC_Result_OK)
			वापस -EINVAL;

		अगर (si_send_msg_to_smc_with_parameter(adev, PPSMC_MSG_SetEnabledLevels, levels) != PPSMC_Result_OK)
			वापस -EINVAL;
	पूर्ण

	adev->pm.dpm.क्रमced_level = level;

	वापस 0;
पूर्ण

#अगर 0
अटल पूर्णांक si_set_boot_state(काष्ठा amdgpu_device *adev)
अणु
	वापस (amdgpu_si_send_msg_to_smc(adev, PPSMC_MSG_SwitchToInitialState) == PPSMC_Result_OK) ?
		0 : -EINVAL;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक si_set_sw_state(काष्ठा amdgpu_device *adev)
अणु
	वापस (amdgpu_si_send_msg_to_smc(adev, PPSMC_MSG_SwitchToSwState) == PPSMC_Result_OK) ?
		0 : -EINVAL;
पूर्ण

अटल पूर्णांक si_halt_smc(काष्ठा amdgpu_device *adev)
अणु
	अगर (amdgpu_si_send_msg_to_smc(adev, PPSMC_MSG_Halt) != PPSMC_Result_OK)
		वापस -EINVAL;

	वापस (amdgpu_si_रुको_क्रम_smc_inactive(adev) == PPSMC_Result_OK) ?
		0 : -EINVAL;
पूर्ण

अटल पूर्णांक si_resume_smc(काष्ठा amdgpu_device *adev)
अणु
	अगर (amdgpu_si_send_msg_to_smc(adev, PPSMC_FlushDataCache) != PPSMC_Result_OK)
		वापस -EINVAL;

	वापस (amdgpu_si_send_msg_to_smc(adev, PPSMC_MSG_Resume) == PPSMC_Result_OK) ?
		0 : -EINVAL;
पूर्ण

अटल व्योम si_dpm_start_smc(काष्ठा amdgpu_device *adev)
अणु
	amdgpu_si_program_jump_on_start(adev);
	amdgpu_si_start_smc(adev);
	amdgpu_si_smc_घड़ी(adev, true);
पूर्ण

अटल व्योम si_dpm_stop_smc(काष्ठा amdgpu_device *adev)
अणु
	amdgpu_si_reset_smc(adev);
	amdgpu_si_smc_घड़ी(adev, false);
पूर्ण

अटल पूर्णांक si_process_firmware_header(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा si_घातer_info *si_pi = si_get_pi(adev);
	u32 पंचांगp;
	पूर्णांक ret;

	ret = amdgpu_si_पढ़ो_smc_sram_dword(adev,
					    SISLANDS_SMC_FIRMWARE_HEADER_LOCATION +
					    SISLANDS_SMC_FIRMWARE_HEADER_stateTable,
					    &पंचांगp, si_pi->sram_end);
	अगर (ret)
		वापस ret;

	si_pi->state_table_start = पंचांगp;

	ret = amdgpu_si_पढ़ो_smc_sram_dword(adev,
					    SISLANDS_SMC_FIRMWARE_HEADER_LOCATION +
					    SISLANDS_SMC_FIRMWARE_HEADER_softRegisters,
					    &पंचांगp, si_pi->sram_end);
	अगर (ret)
		वापस ret;

	si_pi->soft_regs_start = पंचांगp;

	ret = amdgpu_si_पढ़ो_smc_sram_dword(adev,
					    SISLANDS_SMC_FIRMWARE_HEADER_LOCATION +
					    SISLANDS_SMC_FIRMWARE_HEADER_mcRegisterTable,
					    &पंचांगp, si_pi->sram_end);
	अगर (ret)
		वापस ret;

	si_pi->mc_reg_table_start = पंचांगp;

	ret = amdgpu_si_पढ़ो_smc_sram_dword(adev,
					    SISLANDS_SMC_FIRMWARE_HEADER_LOCATION +
					    SISLANDS_SMC_FIRMWARE_HEADER_fanTable,
					    &पंचांगp, si_pi->sram_end);
	अगर (ret)
		वापस ret;

	si_pi->fan_table_start = पंचांगp;

	ret = amdgpu_si_पढ़ो_smc_sram_dword(adev,
					    SISLANDS_SMC_FIRMWARE_HEADER_LOCATION +
					    SISLANDS_SMC_FIRMWARE_HEADER_mcArbDramAutoRefreshTable,
					    &पंचांगp, si_pi->sram_end);
	अगर (ret)
		वापस ret;

	si_pi->arb_table_start = पंचांगp;

	ret = amdgpu_si_पढ़ो_smc_sram_dword(adev,
					    SISLANDS_SMC_FIRMWARE_HEADER_LOCATION +
					    SISLANDS_SMC_FIRMWARE_HEADER_CacConfigTable,
					    &पंचांगp, si_pi->sram_end);
	अगर (ret)
		वापस ret;

	si_pi->cac_table_start = पंचांगp;

	ret = amdgpu_si_पढ़ो_smc_sram_dword(adev,
					    SISLANDS_SMC_FIRMWARE_HEADER_LOCATION +
					    SISLANDS_SMC_FIRMWARE_HEADER_DteConfiguration,
					    &पंचांगp, si_pi->sram_end);
	अगर (ret)
		वापस ret;

	si_pi->dte_table_start = पंचांगp;

	ret = amdgpu_si_पढ़ो_smc_sram_dword(adev,
					    SISLANDS_SMC_FIRMWARE_HEADER_LOCATION +
					    SISLANDS_SMC_FIRMWARE_HEADER_spllTable,
					    &पंचांगp, si_pi->sram_end);
	अगर (ret)
		वापस ret;

	si_pi->spll_table_start = पंचांगp;

	ret = amdgpu_si_पढ़ो_smc_sram_dword(adev,
					    SISLANDS_SMC_FIRMWARE_HEADER_LOCATION +
					    SISLANDS_SMC_FIRMWARE_HEADER_PAPMParameters,
					    &पंचांगp, si_pi->sram_end);
	अगर (ret)
		वापस ret;

	si_pi->papm_cfg_table_start = पंचांगp;

	वापस ret;
पूर्ण

अटल व्योम si_पढ़ो_घड़ी_रेजिस्टरs(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा si_घातer_info *si_pi = si_get_pi(adev);

	si_pi->घड़ी_रेजिस्टरs.cg_spll_func_cntl = RREG32(CG_SPLL_FUNC_CNTL);
	si_pi->घड़ी_रेजिस्टरs.cg_spll_func_cntl_2 = RREG32(CG_SPLL_FUNC_CNTL_2);
	si_pi->घड़ी_रेजिस्टरs.cg_spll_func_cntl_3 = RREG32(CG_SPLL_FUNC_CNTL_3);
	si_pi->घड़ी_रेजिस्टरs.cg_spll_func_cntl_4 = RREG32(CG_SPLL_FUNC_CNTL_4);
	si_pi->घड़ी_रेजिस्टरs.cg_spll_spपढ़ो_spectrum = RREG32(CG_SPLL_SPREAD_SPECTRUM);
	si_pi->घड़ी_रेजिस्टरs.cg_spll_spपढ़ो_spectrum_2 = RREG32(CG_SPLL_SPREAD_SPECTRUM_2);
	si_pi->घड़ी_रेजिस्टरs.dll_cntl = RREG32(DLL_CNTL);
	si_pi->घड़ी_रेजिस्टरs.mclk_pwrmgt_cntl = RREG32(MCLK_PWRMGT_CNTL);
	si_pi->घड़ी_रेजिस्टरs.mpll_ad_func_cntl = RREG32(MPLL_AD_FUNC_CNTL);
	si_pi->घड़ी_रेजिस्टरs.mpll_dq_func_cntl = RREG32(MPLL_DQ_FUNC_CNTL);
	si_pi->घड़ी_रेजिस्टरs.mpll_func_cntl = RREG32(MPLL_FUNC_CNTL);
	si_pi->घड़ी_रेजिस्टरs.mpll_func_cntl_1 = RREG32(MPLL_FUNC_CNTL_1);
	si_pi->घड़ी_रेजिस्टरs.mpll_func_cntl_2 = RREG32(MPLL_FUNC_CNTL_2);
	si_pi->घड़ी_रेजिस्टरs.mpll_ss1 = RREG32(MPLL_SS1);
	si_pi->घड़ी_रेजिस्टरs.mpll_ss2 = RREG32(MPLL_SS2);
पूर्ण

अटल व्योम si_enable_thermal_protection(काष्ठा amdgpu_device *adev,
					  bool enable)
अणु
	अगर (enable)
		WREG32_P(GENERAL_PWRMGT, 0, ~THERMAL_PROTECTION_DIS);
	अन्यथा
		WREG32_P(GENERAL_PWRMGT, THERMAL_PROTECTION_DIS, ~THERMAL_PROTECTION_DIS);
पूर्ण

अटल व्योम si_enable_acpi_घातer_management(काष्ठा amdgpu_device *adev)
अणु
	WREG32_P(GENERAL_PWRMGT, STATIC_PM_EN, ~STATIC_PM_EN);
पूर्ण

#अगर 0
अटल पूर्णांक si_enter_ulp_state(काष्ठा amdgpu_device *adev)
अणु
	WREG32(SMC_MESSAGE_0, PPSMC_MSG_SwitchToMinimumPower);

	udelay(25000);

	वापस 0;
पूर्ण

अटल पूर्णांक si_निकास_ulp_state(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i;

	WREG32(SMC_MESSAGE_0, PPSMC_MSG_ResumeFromMinimumPower);

	udelay(7000);

	क्रम (i = 0; i < adev->usec_समयout; i++) अणु
		अगर (RREG32(SMC_RESP_0) == 1)
			अवरोध;
		udelay(1000);
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक si_notअगरy_smc_display_change(काष्ठा amdgpu_device *adev,
				     bool has_display)
अणु
	PPSMC_Msg msg = has_display ?
		PPSMC_MSG_HasDisplay : PPSMC_MSG_NoDisplay;

	वापस (amdgpu_si_send_msg_to_smc(adev, msg) == PPSMC_Result_OK) ?
		0 : -EINVAL;
पूर्ण

अटल व्योम si_program_response_बार(काष्ठा amdgpu_device *adev)
अणु
	u32 voltage_response_समय, acpi_delay_समय, vbi_समय_out;
	u32 vddc_dly, acpi_dly, vbi_dly;
	u32 reference_घड़ी;

	si_ग_लिखो_smc_soft_रेजिस्टर(adev, SI_SMC_SOFT_REGISTER_mvdd_chg_समय, 1);

	voltage_response_समय = (u32)adev->pm.dpm.voltage_response_समय;

	अगर (voltage_response_समय == 0)
		voltage_response_समय = 1000;

	acpi_delay_समय = 15000;
	vbi_समय_out = 100000;

	reference_घड़ी = amdgpu_asic_get_xclk(adev);

	vddc_dly = (voltage_response_समय  * reference_घड़ी) / 100;
	acpi_dly = (acpi_delay_समय * reference_घड़ी) / 100;
	vbi_dly  = (vbi_समय_out * reference_घड़ी) / 100;

	si_ग_लिखो_smc_soft_रेजिस्टर(adev, SI_SMC_SOFT_REGISTER_delay_vreg,  vddc_dly);
	si_ग_लिखो_smc_soft_रेजिस्टर(adev, SI_SMC_SOFT_REGISTER_delay_acpi,  acpi_dly);
	si_ग_लिखो_smc_soft_रेजिस्टर(adev, SI_SMC_SOFT_REGISTER_mclk_chg_समयout, vbi_dly);
	si_ग_लिखो_smc_soft_रेजिस्टर(adev, SI_SMC_SOFT_REGISTER_mc_block_delay, 0xAA);
पूर्ण

अटल व्योम si_program_ds_रेजिस्टरs(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(adev);
	u32 पंचांगp;

	/* DEEP_SLEEP_CLK_SEL field should be 0x10 on tahiti A0 */
	अगर (adev->asic_type == CHIP_TAHITI && adev->rev_id == 0x0)
		पंचांगp = 0x10;
	अन्यथा
		पंचांगp = 0x1;

	अगर (eg_pi->sclk_deep_sleep) अणु
		WREG32_P(MISC_CLK_CNTL, DEEP_SLEEP_CLK_SEL(पंचांगp), ~DEEP_SLEEP_CLK_SEL_MASK);
		WREG32_P(CG_SPLL_AUTOSCALE_CNTL, AUTOSCALE_ON_SS_CLEAR,
			 ~AUTOSCALE_ON_SS_CLEAR);
	पूर्ण
पूर्ण

अटल व्योम si_program_display_gap(काष्ठा amdgpu_device *adev)
अणु
	u32 पंचांगp, pipe;
	पूर्णांक i;

	पंचांगp = RREG32(CG_DISPLAY_GAP_CNTL) & ~(DISP1_GAP_MASK | DISP2_GAP_MASK);
	अगर (adev->pm.dpm.new_active_crtc_count > 0)
		पंचांगp |= DISP1_GAP(R600_PM_DISPLAY_GAP_VBLANK_OR_WM);
	अन्यथा
		पंचांगp |= DISP1_GAP(R600_PM_DISPLAY_GAP_IGNORE);

	अगर (adev->pm.dpm.new_active_crtc_count > 1)
		पंचांगp |= DISP2_GAP(R600_PM_DISPLAY_GAP_VBLANK_OR_WM);
	अन्यथा
		पंचांगp |= DISP2_GAP(R600_PM_DISPLAY_GAP_IGNORE);

	WREG32(CG_DISPLAY_GAP_CNTL, पंचांगp);

	पंचांगp = RREG32(DCCG_DISP_SLOW_SELECT_REG);
	pipe = (पंचांगp & DCCG_DISP1_SLOW_SELECT_MASK) >> DCCG_DISP1_SLOW_SELECT_SHIFT;

	अगर ((adev->pm.dpm.new_active_crtc_count > 0) &&
	    (!(adev->pm.dpm.new_active_crtcs & (1 << pipe)))) अणु
		/* find the first active crtc */
		क्रम (i = 0; i < adev->mode_info.num_crtc; i++) अणु
			अगर (adev->pm.dpm.new_active_crtcs & (1 << i))
				अवरोध;
		पूर्ण
		अगर (i == adev->mode_info.num_crtc)
			pipe = 0;
		अन्यथा
			pipe = i;

		पंचांगp &= ~DCCG_DISP1_SLOW_SELECT_MASK;
		पंचांगp |= DCCG_DISP1_SLOW_SELECT(pipe);
		WREG32(DCCG_DISP_SLOW_SELECT_REG, पंचांगp);
	पूर्ण

	/* Setting this to false क्रमces the perक्रमmance state to low अगर the crtcs are disabled.
	 * This can be a problem on PowerXpress प्रणालीs or अगर you want to use the card
	 * क्रम offscreen rendering or compute अगर there are no crtcs enabled.
	 */
	si_notअगरy_smc_display_change(adev, adev->pm.dpm.new_active_crtc_count > 0);
पूर्ण

अटल व्योम si_enable_spपढ़ो_spectrum(काष्ठा amdgpu_device *adev, bool enable)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(adev);

	अगर (enable) अणु
		अगर (pi->sclk_ss)
			WREG32_P(GENERAL_PWRMGT, DYN_SPREAD_SPECTRUM_EN, ~DYN_SPREAD_SPECTRUM_EN);
	पूर्ण अन्यथा अणु
		WREG32_P(CG_SPLL_SPREAD_SPECTRUM, 0, ~SSEN);
		WREG32_P(GENERAL_PWRMGT, 0, ~DYN_SPREAD_SPECTRUM_EN);
	पूर्ण
पूर्ण

अटल व्योम si_setup_bsp(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(adev);
	u32 xclk = amdgpu_asic_get_xclk(adev);

	r600_calculate_u_and_p(pi->asi,
			       xclk,
			       16,
			       &pi->bsp,
			       &pi->bsu);

	r600_calculate_u_and_p(pi->pasi,
			       xclk,
			       16,
			       &pi->pbsp,
			       &pi->pbsu);


        pi->dsp = BSP(pi->bsp) | BSU(pi->bsu);
	pi->psp = BSP(pi->pbsp) | BSU(pi->pbsu);

	WREG32(CG_BSP, pi->dsp);
पूर्ण

अटल व्योम si_program_git(काष्ठा amdgpu_device *adev)
अणु
	WREG32_P(CG_GIT, CG_GICST(R600_GICST_DFLT), ~CG_GICST_MASK);
पूर्ण

अटल व्योम si_program_tp(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i;
	क्रमागत r600_td td = R600_TD_DFLT;

	क्रम (i = 0; i < R600_PM_NUMBER_OF_TC; i++)
		WREG32(CG_FFCT_0 + i, (UTC_0(r600_utc[i]) | DTC_0(r600_dtc[i])));

	अगर (td == R600_TD_AUTO)
		WREG32_P(SCLK_PWRMGT_CNTL, 0, ~FIR_FORCE_TREND_SEL);
	अन्यथा
		WREG32_P(SCLK_PWRMGT_CNTL, FIR_FORCE_TREND_SEL, ~FIR_FORCE_TREND_SEL);

	अगर (td == R600_TD_UP)
		WREG32_P(SCLK_PWRMGT_CNTL, 0, ~FIR_TREND_MODE);

	अगर (td == R600_TD_DOWN)
		WREG32_P(SCLK_PWRMGT_CNTL, FIR_TREND_MODE, ~FIR_TREND_MODE);
पूर्ण

अटल व्योम si_program_tpp(काष्ठा amdgpu_device *adev)
अणु
	WREG32(CG_TPC, R600_TPC_DFLT);
पूर्ण

अटल व्योम si_program_sstp(काष्ठा amdgpu_device *adev)
अणु
	WREG32(CG_SSP, (SSTU(R600_SSTU_DFLT) | SST(R600_SST_DFLT)));
पूर्ण

अटल व्योम si_enable_display_gap(काष्ठा amdgpu_device *adev)
अणु
	u32 पंचांगp = RREG32(CG_DISPLAY_GAP_CNTL);

	पंचांगp &= ~(DISP1_GAP_MASK | DISP2_GAP_MASK);
	पंचांगp |= (DISP1_GAP(R600_PM_DISPLAY_GAP_IGNORE) |
		DISP2_GAP(R600_PM_DISPLAY_GAP_IGNORE));

	पंचांगp &= ~(DISP1_GAP_MCHG_MASK | DISP2_GAP_MCHG_MASK);
	पंचांगp |= (DISP1_GAP_MCHG(R600_PM_DISPLAY_GAP_VBLANK) |
		DISP2_GAP_MCHG(R600_PM_DISPLAY_GAP_IGNORE));
	WREG32(CG_DISPLAY_GAP_CNTL, पंचांगp);
पूर्ण

अटल व्योम si_program_vc(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(adev);

	WREG32(CG_FTV, pi->vrc);
पूर्ण

अटल व्योम si_clear_vc(काष्ठा amdgpu_device *adev)
अणु
	WREG32(CG_FTV, 0);
पूर्ण

अटल u8 si_get_ddr3_mclk_frequency_ratio(u32 memory_घड़ी)
अणु
	u8 mc_para_index;

	अगर (memory_घड़ी < 10000)
		mc_para_index = 0;
	अन्यथा अगर (memory_घड़ी >= 80000)
		mc_para_index = 0x0f;
	अन्यथा
		mc_para_index = (u8)((memory_घड़ी - 10000) / 5000 + 1);
	वापस mc_para_index;
पूर्ण

अटल u8 si_get_mclk_frequency_ratio(u32 memory_घड़ी, bool strobe_mode)
अणु
	u8 mc_para_index;

	अगर (strobe_mode) अणु
		अगर (memory_घड़ी < 12500)
			mc_para_index = 0x00;
		अन्यथा अगर (memory_घड़ी > 47500)
			mc_para_index = 0x0f;
		अन्यथा
			mc_para_index = (u8)((memory_घड़ी - 10000) / 2500);
	पूर्ण अन्यथा अणु
		अगर (memory_घड़ी < 65000)
			mc_para_index = 0x00;
		अन्यथा अगर (memory_घड़ी > 135000)
			mc_para_index = 0x0f;
		अन्यथा
			mc_para_index = (u8)((memory_घड़ी - 60000) / 5000);
	पूर्ण
	वापस mc_para_index;
पूर्ण

अटल u8 si_get_strobe_mode_settings(काष्ठा amdgpu_device *adev, u32 mclk)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(adev);
	bool strobe_mode = false;
	u8 result = 0;

	अगर (mclk <= pi->mclk_strobe_mode_threshold)
		strobe_mode = true;

	अगर (adev->gmc.vram_type == AMDGPU_VRAM_TYPE_GDDR5)
		result = si_get_mclk_frequency_ratio(mclk, strobe_mode);
	अन्यथा
		result = si_get_ddr3_mclk_frequency_ratio(mclk);

	अगर (strobe_mode)
		result |= SISLANDS_SMC_STROBE_ENABLE;

	वापस result;
पूर्ण

अटल पूर्णांक si_upload_firmware(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा si_घातer_info *si_pi = si_get_pi(adev);

	amdgpu_si_reset_smc(adev);
	amdgpu_si_smc_घड़ी(adev, false);

	वापस amdgpu_si_load_smc_ucode(adev, si_pi->sram_end);
पूर्ण

अटल bool si_validate_phase_shedding_tables(काष्ठा amdgpu_device *adev,
					      स्थिर काष्ठा atom_voltage_table *table,
					      स्थिर काष्ठा amdgpu_phase_shedding_limits_table *limits)
अणु
	u32 data, num_bits, num_levels;

	अगर ((table == शून्य) || (limits == शून्य))
		वापस false;

	data = table->mask_low;

	num_bits = hweight32(data);

	अगर (num_bits == 0)
		वापस false;

	num_levels = (1 << num_bits);

	अगर (table->count != num_levels)
		वापस false;

	अगर (limits->count != (num_levels - 1))
		वापस false;

	वापस true;
पूर्ण

अटल व्योम si_trim_voltage_table_to_fit_state_table(काष्ठा amdgpu_device *adev,
					      u32 max_voltage_steps,
					      काष्ठा atom_voltage_table *voltage_table)
अणु
	अचिन्हित पूर्णांक i, dअगरf;

	अगर (voltage_table->count <= max_voltage_steps)
		वापस;

	dअगरf = voltage_table->count - max_voltage_steps;

	क्रम (i= 0; i < max_voltage_steps; i++)
		voltage_table->entries[i] = voltage_table->entries[i + dअगरf];

	voltage_table->count = max_voltage_steps;
पूर्ण

अटल पूर्णांक si_get_svi2_voltage_table(काष्ठा amdgpu_device *adev,
				     काष्ठा amdgpu_घड़ी_voltage_dependency_table *voltage_dependency_table,
				     काष्ठा atom_voltage_table *voltage_table)
अणु
	u32 i;

	अगर (voltage_dependency_table == शून्य)
		वापस -EINVAL;

	voltage_table->mask_low = 0;
	voltage_table->phase_delay = 0;

	voltage_table->count = voltage_dependency_table->count;
	क्रम (i = 0; i < voltage_table->count; i++) अणु
		voltage_table->entries[i].value = voltage_dependency_table->entries[i].v;
		voltage_table->entries[i].smio_low = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक si_स्थिरruct_voltage_tables(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(adev);
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(adev);
	काष्ठा si_घातer_info *si_pi = si_get_pi(adev);
	पूर्णांक ret;

	अगर (pi->voltage_control) अणु
		ret = amdgpu_atombios_get_voltage_table(adev, VOLTAGE_TYPE_VDDC,
						    VOLTAGE_OBJ_GPIO_LUT, &eg_pi->vddc_voltage_table);
		अगर (ret)
			वापस ret;

		अगर (eg_pi->vddc_voltage_table.count > SISLANDS_MAX_NO_VREG_STEPS)
			si_trim_voltage_table_to_fit_state_table(adev,
								 SISLANDS_MAX_NO_VREG_STEPS,
								 &eg_pi->vddc_voltage_table);
	पूर्ण अन्यथा अगर (si_pi->voltage_control_svi2) अणु
		ret = si_get_svi2_voltage_table(adev,
						&adev->pm.dpm.dyn_state.vddc_dependency_on_mclk,
						&eg_pi->vddc_voltage_table);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	अगर (eg_pi->vddci_control) अणु
		ret = amdgpu_atombios_get_voltage_table(adev, VOLTAGE_TYPE_VDDCI,
						    VOLTAGE_OBJ_GPIO_LUT, &eg_pi->vddci_voltage_table);
		अगर (ret)
			वापस ret;

		अगर (eg_pi->vddci_voltage_table.count > SISLANDS_MAX_NO_VREG_STEPS)
			si_trim_voltage_table_to_fit_state_table(adev,
								 SISLANDS_MAX_NO_VREG_STEPS,
								 &eg_pi->vddci_voltage_table);
	पूर्ण
	अगर (si_pi->vddci_control_svi2) अणु
		ret = si_get_svi2_voltage_table(adev,
						&adev->pm.dpm.dyn_state.vddci_dependency_on_mclk,
						&eg_pi->vddci_voltage_table);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (pi->mvdd_control) अणु
		ret = amdgpu_atombios_get_voltage_table(adev, VOLTAGE_TYPE_MVDDC,
						    VOLTAGE_OBJ_GPIO_LUT, &si_pi->mvdd_voltage_table);

		अगर (ret) अणु
			pi->mvdd_control = false;
			वापस ret;
		पूर्ण

		अगर (si_pi->mvdd_voltage_table.count == 0) अणु
			pi->mvdd_control = false;
			वापस -EINVAL;
		पूर्ण

		अगर (si_pi->mvdd_voltage_table.count > SISLANDS_MAX_NO_VREG_STEPS)
			si_trim_voltage_table_to_fit_state_table(adev,
								 SISLANDS_MAX_NO_VREG_STEPS,
								 &si_pi->mvdd_voltage_table);
	पूर्ण

	अगर (si_pi->vddc_phase_shed_control) अणु
		ret = amdgpu_atombios_get_voltage_table(adev, VOLTAGE_TYPE_VDDC,
						    VOLTAGE_OBJ_PHASE_LUT, &si_pi->vddc_phase_shed_table);
		अगर (ret)
			si_pi->vddc_phase_shed_control = false;

		अगर ((si_pi->vddc_phase_shed_table.count == 0) ||
		    (si_pi->vddc_phase_shed_table.count > SISLANDS_MAX_NO_VREG_STEPS))
			si_pi->vddc_phase_shed_control = false;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम si_populate_smc_voltage_table(काष्ठा amdgpu_device *adev,
					  स्थिर काष्ठा atom_voltage_table *voltage_table,
					  SISLANDS_SMC_STATETABLE *table)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < voltage_table->count; i++)
		table->lowSMIO[i] |= cpu_to_be32(voltage_table->entries[i].smio_low);
पूर्ण

अटल पूर्णांक si_populate_smc_voltage_tables(काष्ठा amdgpu_device *adev,
					  SISLANDS_SMC_STATETABLE *table)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(adev);
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(adev);
	काष्ठा si_घातer_info *si_pi = si_get_pi(adev);
	u8 i;

	अगर (si_pi->voltage_control_svi2) अणु
		si_ग_लिखो_smc_soft_रेजिस्टर(adev, SI_SMC_SOFT_REGISTER_svi_rework_gpio_id_svc,
			si_pi->svc_gpio_id);
		si_ग_लिखो_smc_soft_रेजिस्टर(adev, SI_SMC_SOFT_REGISTER_svi_rework_gpio_id_svd,
			si_pi->svd_gpio_id);
		si_ग_लिखो_smc_soft_रेजिस्टर(adev, SI_SMC_SOFT_REGISTER_svi_rework_plat_type,
					   2);
	पूर्ण अन्यथा अणु
		अगर (eg_pi->vddc_voltage_table.count) अणु
			si_populate_smc_voltage_table(adev, &eg_pi->vddc_voltage_table, table);
			table->voltageMaskTable.lowMask[SISLANDS_SMC_VOLTAGEMASK_VDDC] =
				cpu_to_be32(eg_pi->vddc_voltage_table.mask_low);

			क्रम (i = 0; i < eg_pi->vddc_voltage_table.count; i++) अणु
				अगर (pi->max_vddc_in_table <= eg_pi->vddc_voltage_table.entries[i].value) अणु
					table->maxVDDCIndexInPPTable = i;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (eg_pi->vddci_voltage_table.count) अणु
			si_populate_smc_voltage_table(adev, &eg_pi->vddci_voltage_table, table);

			table->voltageMaskTable.lowMask[SISLANDS_SMC_VOLTAGEMASK_VDDCI] =
				cpu_to_be32(eg_pi->vddci_voltage_table.mask_low);
		पूर्ण


		अगर (si_pi->mvdd_voltage_table.count) अणु
			si_populate_smc_voltage_table(adev, &si_pi->mvdd_voltage_table, table);

			table->voltageMaskTable.lowMask[SISLANDS_SMC_VOLTAGEMASK_MVDD] =
				cpu_to_be32(si_pi->mvdd_voltage_table.mask_low);
		पूर्ण

		अगर (si_pi->vddc_phase_shed_control) अणु
			अगर (si_validate_phase_shedding_tables(adev, &si_pi->vddc_phase_shed_table,
							      &adev->pm.dpm.dyn_state.phase_shedding_limits_table)) अणु
				si_populate_smc_voltage_table(adev, &si_pi->vddc_phase_shed_table, table);

				table->phaseMaskTable.lowMask[SISLANDS_SMC_VOLTAGEMASK_VDDC_PHASE_SHEDDING] =
					cpu_to_be32(si_pi->vddc_phase_shed_table.mask_low);

				si_ग_लिखो_smc_soft_रेजिस्टर(adev, SI_SMC_SOFT_REGISTER_phase_shedding_delay,
							   (u32)si_pi->vddc_phase_shed_table.phase_delay);
			पूर्ण अन्यथा अणु
				si_pi->vddc_phase_shed_control = false;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक si_populate_voltage_value(काष्ठा amdgpu_device *adev,
				     स्थिर काष्ठा atom_voltage_table *table,
				     u16 value, SISLANDS_SMC_VOLTAGE_VALUE *voltage)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < table->count; i++) अणु
		अगर (value <= table->entries[i].value) अणु
			voltage->index = (u8)i;
			voltage->value = cpu_to_be16(table->entries[i].value);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i >= table->count)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक si_populate_mvdd_value(काष्ठा amdgpu_device *adev, u32 mclk,
				  SISLANDS_SMC_VOLTAGE_VALUE *voltage)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(adev);
	काष्ठा si_घातer_info *si_pi = si_get_pi(adev);

	अगर (pi->mvdd_control) अणु
		अगर (mclk <= pi->mvdd_split_frequency)
			voltage->index = 0;
		अन्यथा
			voltage->index = (u8)(si_pi->mvdd_voltage_table.count) - 1;

		voltage->value = cpu_to_be16(si_pi->mvdd_voltage_table.entries[voltage->index].value);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक si_get_std_voltage_value(काष्ठा amdgpu_device *adev,
				    SISLANDS_SMC_VOLTAGE_VALUE *voltage,
				    u16 *std_voltage)
अणु
	u16 v_index;
	bool voltage_found = false;
	*std_voltage = be16_to_cpu(voltage->value);

	अगर (adev->pm.dpm.dyn_state.cac_leakage_table.entries) अणु
		अगर (adev->pm.dpm.platक्रमm_caps & ATOM_PP_PLATFORM_CAP_NEW_CAC_VOLTAGE) अणु
			अगर (adev->pm.dpm.dyn_state.vddc_dependency_on_sclk.entries == शून्य)
				वापस -EINVAL;

			क्रम (v_index = 0; (u32)v_index < adev->pm.dpm.dyn_state.vddc_dependency_on_sclk.count; v_index++) अणु
				अगर (be16_to_cpu(voltage->value) ==
				    (u16)adev->pm.dpm.dyn_state.vddc_dependency_on_sclk.entries[v_index].v) अणु
					voltage_found = true;
					अगर ((u32)v_index < adev->pm.dpm.dyn_state.cac_leakage_table.count)
						*std_voltage =
							adev->pm.dpm.dyn_state.cac_leakage_table.entries[v_index].vddc;
					अन्यथा
						*std_voltage =
							adev->pm.dpm.dyn_state.cac_leakage_table.entries[adev->pm.dpm.dyn_state.cac_leakage_table.count-1].vddc;
					अवरोध;
				पूर्ण
			पूर्ण

			अगर (!voltage_found) अणु
				क्रम (v_index = 0; (u32)v_index < adev->pm.dpm.dyn_state.vddc_dependency_on_sclk.count; v_index++) अणु
					अगर (be16_to_cpu(voltage->value) <=
					    (u16)adev->pm.dpm.dyn_state.vddc_dependency_on_sclk.entries[v_index].v) अणु
						voltage_found = true;
						अगर ((u32)v_index < adev->pm.dpm.dyn_state.cac_leakage_table.count)
							*std_voltage =
								adev->pm.dpm.dyn_state.cac_leakage_table.entries[v_index].vddc;
						अन्यथा
							*std_voltage =
								adev->pm.dpm.dyn_state.cac_leakage_table.entries[adev->pm.dpm.dyn_state.cac_leakage_table.count-1].vddc;
						अवरोध;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर ((u32)voltage->index < adev->pm.dpm.dyn_state.cac_leakage_table.count)
				*std_voltage = adev->pm.dpm.dyn_state.cac_leakage_table.entries[voltage->index].vddc;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक si_populate_std_voltage_value(काष्ठा amdgpu_device *adev,
					 u16 value, u8 index,
					 SISLANDS_SMC_VOLTAGE_VALUE *voltage)
अणु
	voltage->index = index;
	voltage->value = cpu_to_be16(value);

	वापस 0;
पूर्ण

अटल पूर्णांक si_populate_phase_shedding_value(काष्ठा amdgpu_device *adev,
					    स्थिर काष्ठा amdgpu_phase_shedding_limits_table *limits,
					    u16 voltage, u32 sclk, u32 mclk,
					    SISLANDS_SMC_VOLTAGE_VALUE *smc_voltage)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < limits->count; i++) अणु
		अगर ((voltage <= limits->entries[i].voltage) &&
		    (sclk <= limits->entries[i].sclk) &&
		    (mclk <= limits->entries[i].mclk))
			अवरोध;
	पूर्ण

	smc_voltage->phase_settings = (u8)i;

	वापस 0;
पूर्ण

अटल पूर्णांक si_init_arb_table_index(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा si_घातer_info *si_pi = si_get_pi(adev);
	u32 पंचांगp;
	पूर्णांक ret;

	ret = amdgpu_si_पढ़ो_smc_sram_dword(adev, si_pi->arb_table_start,
					    &पंचांगp, si_pi->sram_end);
	अगर (ret)
		वापस ret;

	पंचांगp &= 0x00FFFFFF;
	पंचांगp |= MC_CG_ARB_FREQ_F1 << 24;

	वापस amdgpu_si_ग_लिखो_smc_sram_dword(adev, si_pi->arb_table_start,
					      पंचांगp, si_pi->sram_end);
पूर्ण

अटल पूर्णांक si_initial_चयन_from_arb_f0_to_f1(काष्ठा amdgpu_device *adev)
अणु
	वापस ni_copy_and_चयन_arb_sets(adev, MC_CG_ARB_FREQ_F0, MC_CG_ARB_FREQ_F1);
पूर्ण

अटल पूर्णांक si_reset_to_शेष(काष्ठा amdgpu_device *adev)
अणु
	वापस (amdgpu_si_send_msg_to_smc(adev, PPSMC_MSG_ResetToDefaults) == PPSMC_Result_OK) ?
		0 : -EINVAL;
पूर्ण

अटल पूर्णांक si_क्रमce_चयन_to_arb_f0(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा si_घातer_info *si_pi = si_get_pi(adev);
	u32 पंचांगp;
	पूर्णांक ret;

	ret = amdgpu_si_पढ़ो_smc_sram_dword(adev, si_pi->arb_table_start,
					    &पंचांगp, si_pi->sram_end);
	अगर (ret)
		वापस ret;

	पंचांगp = (पंचांगp >> 24) & 0xff;

	अगर (पंचांगp == MC_CG_ARB_FREQ_F0)
		वापस 0;

	वापस ni_copy_and_चयन_arb_sets(adev, पंचांगp, MC_CG_ARB_FREQ_F0);
पूर्ण

अटल u32 si_calculate_memory_refresh_rate(काष्ठा amdgpu_device *adev,
					    u32 engine_घड़ी)
अणु
	u32 dram_rows;
	u32 dram_refresh_rate;
	u32 mc_arb_rfsh_rate;
	u32 पंचांगp = (RREG32(MC_ARB_RAMCFG) & NOOFROWS_MASK) >> NOOFROWS_SHIFT;

	अगर (पंचांगp >= 4)
		dram_rows = 16384;
	अन्यथा
		dram_rows = 1 << (पंचांगp + 10);

	dram_refresh_rate = 1 << ((RREG32(MC_SEQ_MISC0) & 0x3) + 3);
	mc_arb_rfsh_rate = ((engine_घड़ी * 10) * dram_refresh_rate / dram_rows - 32) / 64;

	वापस mc_arb_rfsh_rate;
पूर्ण

अटल पूर्णांक si_populate_memory_timing_parameters(काष्ठा amdgpu_device *adev,
						काष्ठा rv7xx_pl *pl,
						SMC_SIslands_MCArbDramTimingRegisterSet *arb_regs)
अणु
	u32 dram_timing;
	u32 dram_timing2;
	u32 burst_समय;

	arb_regs->mc_arb_rfsh_rate =
		(u8)si_calculate_memory_refresh_rate(adev, pl->sclk);

	amdgpu_atombios_set_engine_dram_timings(adev,
					    pl->sclk,
		                            pl->mclk);

	dram_timing  = RREG32(MC_ARB_DRAM_TIMING);
	dram_timing2 = RREG32(MC_ARB_DRAM_TIMING2);
	burst_समय = RREG32(MC_ARB_BURST_TIME) & STATE0_MASK;

	arb_regs->mc_arb_dram_timing  = cpu_to_be32(dram_timing);
	arb_regs->mc_arb_dram_timing2 = cpu_to_be32(dram_timing2);
	arb_regs->mc_arb_burst_समय = (u8)burst_समय;

	वापस 0;
पूर्ण

अटल पूर्णांक si_करो_program_memory_timing_parameters(काष्ठा amdgpu_device *adev,
						  काष्ठा amdgpu_ps *amdgpu_state,
						  अचिन्हित पूर्णांक first_arb_set)
अणु
	काष्ठा si_घातer_info *si_pi = si_get_pi(adev);
	काष्ठा  si_ps *state = si_get_ps(amdgpu_state);
	SMC_SIslands_MCArbDramTimingRegisterSet arb_regs = अणु 0 पूर्ण;
	पूर्णांक i, ret = 0;

	क्रम (i = 0; i < state->perक्रमmance_level_count; i++) अणु
		ret = si_populate_memory_timing_parameters(adev, &state->perक्रमmance_levels[i], &arb_regs);
		अगर (ret)
			अवरोध;
		ret = amdgpu_si_copy_bytes_to_smc(adev,
						  si_pi->arb_table_start +
						  दुरत्व(SMC_SIslands_MCArbDramTimingRegisters, data) +
						  माप(SMC_SIslands_MCArbDramTimingRegisterSet) * (first_arb_set + i),
						  (u8 *)&arb_regs,
						  माप(SMC_SIslands_MCArbDramTimingRegisterSet),
						  si_pi->sram_end);
		अगर (ret)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक si_program_memory_timing_parameters(काष्ठा amdgpu_device *adev,
					       काष्ठा amdgpu_ps *amdgpu_new_state)
अणु
	वापस si_करो_program_memory_timing_parameters(adev, amdgpu_new_state,
						      SISLANDS_DRIVER_STATE_ARB_INDEX);
पूर्ण

अटल पूर्णांक si_populate_initial_mvdd_value(काष्ठा amdgpu_device *adev,
					  काष्ठा SISLANDS_SMC_VOLTAGE_VALUE *voltage)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(adev);
	काष्ठा si_घातer_info *si_pi = si_get_pi(adev);

	अगर (pi->mvdd_control)
		वापस si_populate_voltage_value(adev, &si_pi->mvdd_voltage_table,
						 si_pi->mvdd_bootup_value, voltage);

	वापस 0;
पूर्ण

अटल पूर्णांक si_populate_smc_initial_state(काष्ठा amdgpu_device *adev,
					 काष्ठा amdgpu_ps *amdgpu_initial_state,
					 SISLANDS_SMC_STATETABLE *table)
अणु
	काष्ठा  si_ps *initial_state = si_get_ps(amdgpu_initial_state);
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(adev);
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(adev);
	काष्ठा si_घातer_info *si_pi = si_get_pi(adev);
	u32 reg;
	पूर्णांक ret;

	table->initialState.level.mclk.vDLL_CNTL =
		cpu_to_be32(si_pi->घड़ी_रेजिस्टरs.dll_cntl);
	table->initialState.level.mclk.vMCLK_PWRMGT_CNTL =
		cpu_to_be32(si_pi->घड़ी_रेजिस्टरs.mclk_pwrmgt_cntl);
	table->initialState.level.mclk.vMPLL_AD_FUNC_CNTL =
		cpu_to_be32(si_pi->घड़ी_रेजिस्टरs.mpll_ad_func_cntl);
	table->initialState.level.mclk.vMPLL_DQ_FUNC_CNTL =
		cpu_to_be32(si_pi->घड़ी_रेजिस्टरs.mpll_dq_func_cntl);
	table->initialState.level.mclk.vMPLL_FUNC_CNTL =
		cpu_to_be32(si_pi->घड़ी_रेजिस्टरs.mpll_func_cntl);
	table->initialState.level.mclk.vMPLL_FUNC_CNTL_1 =
		cpu_to_be32(si_pi->घड़ी_रेजिस्टरs.mpll_func_cntl_1);
	table->initialState.level.mclk.vMPLL_FUNC_CNTL_2 =
		cpu_to_be32(si_pi->घड़ी_रेजिस्टरs.mpll_func_cntl_2);
	table->initialState.level.mclk.vMPLL_SS =
		cpu_to_be32(si_pi->घड़ी_रेजिस्टरs.mpll_ss1);
	table->initialState.level.mclk.vMPLL_SS2 =
		cpu_to_be32(si_pi->घड़ी_रेजिस्टरs.mpll_ss2);

	table->initialState.level.mclk.mclk_value =
		cpu_to_be32(initial_state->perक्रमmance_levels[0].mclk);

	table->initialState.level.sclk.vCG_SPLL_FUNC_CNTL =
		cpu_to_be32(si_pi->घड़ी_रेजिस्टरs.cg_spll_func_cntl);
	table->initialState.level.sclk.vCG_SPLL_FUNC_CNTL_2 =
		cpu_to_be32(si_pi->घड़ी_रेजिस्टरs.cg_spll_func_cntl_2);
	table->initialState.level.sclk.vCG_SPLL_FUNC_CNTL_3 =
		cpu_to_be32(si_pi->घड़ी_रेजिस्टरs.cg_spll_func_cntl_3);
	table->initialState.level.sclk.vCG_SPLL_FUNC_CNTL_4 =
		cpu_to_be32(si_pi->घड़ी_रेजिस्टरs.cg_spll_func_cntl_4);
	table->initialState.level.sclk.vCG_SPLL_SPREAD_SPECTRUM =
		cpu_to_be32(si_pi->घड़ी_रेजिस्टरs.cg_spll_spपढ़ो_spectrum);
	table->initialState.level.sclk.vCG_SPLL_SPREAD_SPECTRUM_2  =
		cpu_to_be32(si_pi->घड़ी_रेजिस्टरs.cg_spll_spपढ़ो_spectrum_2);

	table->initialState.level.sclk.sclk_value =
		cpu_to_be32(initial_state->perक्रमmance_levels[0].sclk);

	table->initialState.level.arbRefreshState =
		SISLANDS_INITIAL_STATE_ARB_INDEX;

	table->initialState.level.ACIndex = 0;

	ret = si_populate_voltage_value(adev, &eg_pi->vddc_voltage_table,
					initial_state->perक्रमmance_levels[0].vddc,
					&table->initialState.level.vddc);

	अगर (!ret) अणु
		u16 std_vddc;

		ret = si_get_std_voltage_value(adev,
					       &table->initialState.level.vddc,
					       &std_vddc);
		अगर (!ret)
			si_populate_std_voltage_value(adev, std_vddc,
						      table->initialState.level.vddc.index,
						      &table->initialState.level.std_vddc);
	पूर्ण

	अगर (eg_pi->vddci_control)
		si_populate_voltage_value(adev,
					  &eg_pi->vddci_voltage_table,
					  initial_state->perक्रमmance_levels[0].vddci,
					  &table->initialState.level.vddci);

	अगर (si_pi->vddc_phase_shed_control)
		si_populate_phase_shedding_value(adev,
						 &adev->pm.dpm.dyn_state.phase_shedding_limits_table,
						 initial_state->perक्रमmance_levels[0].vddc,
						 initial_state->perक्रमmance_levels[0].sclk,
						 initial_state->perक्रमmance_levels[0].mclk,
						 &table->initialState.level.vddc);

	si_populate_initial_mvdd_value(adev, &table->initialState.level.mvdd);

	reg = CG_R(0xffff) | CG_L(0);
	table->initialState.level.aT = cpu_to_be32(reg);
	table->initialState.level.bSP = cpu_to_be32(pi->dsp);
	table->initialState.level.gen2PCIE = (u8)si_pi->boot_pcie_gen;

	अगर (adev->gmc.vram_type == AMDGPU_VRAM_TYPE_GDDR5) अणु
		table->initialState.level.strobeMode =
			si_get_strobe_mode_settings(adev,
						    initial_state->perक्रमmance_levels[0].mclk);

		अगर (initial_state->perक्रमmance_levels[0].mclk > pi->mclk_edc_enable_threshold)
			table->initialState.level.mcFlags = SISLANDS_SMC_MC_EDC_RD_FLAG | SISLANDS_SMC_MC_EDC_WR_FLAG;
		अन्यथा
			table->initialState.level.mcFlags =  0;
	पूर्ण

	table->initialState.levelCount = 1;

	table->initialState.flags |= PPSMC_SWSTATE_FLAG_DC;

	table->initialState.level.dpm2.MaxPS = 0;
	table->initialState.level.dpm2.NearTDPDec = 0;
	table->initialState.level.dpm2.AboveSafeInc = 0;
	table->initialState.level.dpm2.BelowSafeInc = 0;
	table->initialState.level.dpm2.PwrEfficiencyRatio = 0;

	reg = MIN_POWER_MASK | MAX_POWER_MASK;
	table->initialState.level.SQPowerThrottle = cpu_to_be32(reg);

	reg = MAX_POWER_DELTA_MASK | STI_SIZE_MASK | LTI_RATIO_MASK;
	table->initialState.level.SQPowerThrottle_2 = cpu_to_be32(reg);

	वापस 0;
पूर्ण

अटल पूर्णांक si_populate_smc_acpi_state(काष्ठा amdgpu_device *adev,
				      SISLANDS_SMC_STATETABLE *table)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(adev);
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(adev);
	काष्ठा si_घातer_info *si_pi = si_get_pi(adev);
	u32 spll_func_cntl = si_pi->घड़ी_रेजिस्टरs.cg_spll_func_cntl;
	u32 spll_func_cntl_2 = si_pi->घड़ी_रेजिस्टरs.cg_spll_func_cntl_2;
	u32 spll_func_cntl_3 = si_pi->घड़ी_रेजिस्टरs.cg_spll_func_cntl_3;
	u32 spll_func_cntl_4 = si_pi->घड़ी_रेजिस्टरs.cg_spll_func_cntl_4;
	u32 dll_cntl = si_pi->घड़ी_रेजिस्टरs.dll_cntl;
	u32 mclk_pwrmgt_cntl = si_pi->घड़ी_रेजिस्टरs.mclk_pwrmgt_cntl;
	u32 mpll_ad_func_cntl = si_pi->घड़ी_रेजिस्टरs.mpll_ad_func_cntl;
	u32 mpll_dq_func_cntl = si_pi->घड़ी_रेजिस्टरs.mpll_dq_func_cntl;
	u32 mpll_func_cntl = si_pi->घड़ी_रेजिस्टरs.mpll_func_cntl;
	u32 mpll_func_cntl_1 = si_pi->घड़ी_रेजिस्टरs.mpll_func_cntl_1;
	u32 mpll_func_cntl_2 = si_pi->घड़ी_रेजिस्टरs.mpll_func_cntl_2;
	u32 reg;
	पूर्णांक ret;

	table->ACPIState = table->initialState;

	table->ACPIState.flags &= ~PPSMC_SWSTATE_FLAG_DC;

	अगर (pi->acpi_vddc) अणु
		ret = si_populate_voltage_value(adev, &eg_pi->vddc_voltage_table,
						pi->acpi_vddc, &table->ACPIState.level.vddc);
		अगर (!ret) अणु
			u16 std_vddc;

			ret = si_get_std_voltage_value(adev,
						       &table->ACPIState.level.vddc, &std_vddc);
			अगर (!ret)
				si_populate_std_voltage_value(adev, std_vddc,
							      table->ACPIState.level.vddc.index,
							      &table->ACPIState.level.std_vddc);
		पूर्ण
		table->ACPIState.level.gen2PCIE = si_pi->acpi_pcie_gen;

		अगर (si_pi->vddc_phase_shed_control) अणु
			si_populate_phase_shedding_value(adev,
							 &adev->pm.dpm.dyn_state.phase_shedding_limits_table,
							 pi->acpi_vddc,
							 0,
							 0,
							 &table->ACPIState.level.vddc);
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = si_populate_voltage_value(adev, &eg_pi->vddc_voltage_table,
						pi->min_vddc_in_table, &table->ACPIState.level.vddc);
		अगर (!ret) अणु
			u16 std_vddc;

			ret = si_get_std_voltage_value(adev,
						       &table->ACPIState.level.vddc, &std_vddc);

			अगर (!ret)
				si_populate_std_voltage_value(adev, std_vddc,
							      table->ACPIState.level.vddc.index,
							      &table->ACPIState.level.std_vddc);
		पूर्ण
		table->ACPIState.level.gen2PCIE =
			(u8)amdgpu_get_pcie_gen_support(adev,
							si_pi->sys_pcie_mask,
							si_pi->boot_pcie_gen,
							AMDGPU_PCIE_GEN1);

		अगर (si_pi->vddc_phase_shed_control)
			si_populate_phase_shedding_value(adev,
							 &adev->pm.dpm.dyn_state.phase_shedding_limits_table,
							 pi->min_vddc_in_table,
							 0,
							 0,
							 &table->ACPIState.level.vddc);
	पूर्ण

	अगर (pi->acpi_vddc) अणु
		अगर (eg_pi->acpi_vddci)
			si_populate_voltage_value(adev, &eg_pi->vddci_voltage_table,
						  eg_pi->acpi_vddci,
						  &table->ACPIState.level.vddci);
	पूर्ण

	mclk_pwrmgt_cntl |= MRDCK0_RESET | MRDCK1_RESET;
	mclk_pwrmgt_cntl &= ~(MRDCK0_PDNB | MRDCK1_PDNB);

	dll_cntl &= ~(MRDCK0_BYPASS | MRDCK1_BYPASS);

	spll_func_cntl_2 &= ~SCLK_MUX_SEL_MASK;
	spll_func_cntl_2 |= SCLK_MUX_SEL(4);

	table->ACPIState.level.mclk.vDLL_CNTL =
		cpu_to_be32(dll_cntl);
	table->ACPIState.level.mclk.vMCLK_PWRMGT_CNTL =
		cpu_to_be32(mclk_pwrmgt_cntl);
	table->ACPIState.level.mclk.vMPLL_AD_FUNC_CNTL =
		cpu_to_be32(mpll_ad_func_cntl);
	table->ACPIState.level.mclk.vMPLL_DQ_FUNC_CNTL =
		cpu_to_be32(mpll_dq_func_cntl);
	table->ACPIState.level.mclk.vMPLL_FUNC_CNTL =
		cpu_to_be32(mpll_func_cntl);
	table->ACPIState.level.mclk.vMPLL_FUNC_CNTL_1 =
		cpu_to_be32(mpll_func_cntl_1);
	table->ACPIState.level.mclk.vMPLL_FUNC_CNTL_2 =
		cpu_to_be32(mpll_func_cntl_2);
	table->ACPIState.level.mclk.vMPLL_SS =
		cpu_to_be32(si_pi->घड़ी_रेजिस्टरs.mpll_ss1);
	table->ACPIState.level.mclk.vMPLL_SS2 =
		cpu_to_be32(si_pi->घड़ी_रेजिस्टरs.mpll_ss2);

	table->ACPIState.level.sclk.vCG_SPLL_FUNC_CNTL =
		cpu_to_be32(spll_func_cntl);
	table->ACPIState.level.sclk.vCG_SPLL_FUNC_CNTL_2 =
		cpu_to_be32(spll_func_cntl_2);
	table->ACPIState.level.sclk.vCG_SPLL_FUNC_CNTL_3 =
		cpu_to_be32(spll_func_cntl_3);
	table->ACPIState.level.sclk.vCG_SPLL_FUNC_CNTL_4 =
		cpu_to_be32(spll_func_cntl_4);

	table->ACPIState.level.mclk.mclk_value = 0;
	table->ACPIState.level.sclk.sclk_value = 0;

	si_populate_mvdd_value(adev, 0, &table->ACPIState.level.mvdd);

	अगर (eg_pi->dynamic_ac_timing)
		table->ACPIState.level.ACIndex = 0;

	table->ACPIState.level.dpm2.MaxPS = 0;
	table->ACPIState.level.dpm2.NearTDPDec = 0;
	table->ACPIState.level.dpm2.AboveSafeInc = 0;
	table->ACPIState.level.dpm2.BelowSafeInc = 0;
	table->ACPIState.level.dpm2.PwrEfficiencyRatio = 0;

	reg = MIN_POWER_MASK | MAX_POWER_MASK;
	table->ACPIState.level.SQPowerThrottle = cpu_to_be32(reg);

	reg = MAX_POWER_DELTA_MASK | STI_SIZE_MASK | LTI_RATIO_MASK;
	table->ACPIState.level.SQPowerThrottle_2 = cpu_to_be32(reg);

	वापस 0;
पूर्ण

अटल पूर्णांक si_populate_ulv_state(काष्ठा amdgpu_device *adev,
				 काष्ठा SISLANDS_SMC_SWSTATE_SINGLE *state)
अणु
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(adev);
	काष्ठा si_घातer_info *si_pi = si_get_pi(adev);
	काष्ठा si_ulv_param *ulv = &si_pi->ulv;
	u32 sclk_in_sr = 1350; /* ??? */
	पूर्णांक ret;

	ret = si_convert_घातer_level_to_smc(adev, &ulv->pl,
					    &state->level);
	अगर (!ret) अणु
		अगर (eg_pi->sclk_deep_sleep) अणु
			अगर (sclk_in_sr <= SCLK_MIN_DEEPSLEEP_FREQ)
				state->level.stateFlags |= PPSMC_STATEFLAG_DEEPSLEEP_BYPASS;
			अन्यथा
				state->level.stateFlags |= PPSMC_STATEFLAG_DEEPSLEEP_THROTTLE;
		पूर्ण
		अगर (ulv->one_pcie_lane_in_ulv)
			state->flags |= PPSMC_SWSTATE_FLAG_PCIE_X1;
		state->level.arbRefreshState = (u8)(SISLANDS_ULV_STATE_ARB_INDEX);
		state->level.ACIndex = 1;
		state->level.std_vddc = state->level.vddc;
		state->levelCount = 1;

		state->flags |= PPSMC_SWSTATE_FLAG_DC;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक si_program_ulv_memory_timing_parameters(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा si_घातer_info *si_pi = si_get_pi(adev);
	काष्ठा si_ulv_param *ulv = &si_pi->ulv;
	SMC_SIslands_MCArbDramTimingRegisterSet arb_regs = अणु 0 पूर्ण;
	पूर्णांक ret;

	ret = si_populate_memory_timing_parameters(adev, &ulv->pl,
						   &arb_regs);
	अगर (ret)
		वापस ret;

	si_ग_लिखो_smc_soft_रेजिस्टर(adev, SI_SMC_SOFT_REGISTER_ulv_volt_change_delay,
				   ulv->volt_change_delay);

	ret = amdgpu_si_copy_bytes_to_smc(adev,
					  si_pi->arb_table_start +
					  दुरत्व(SMC_SIslands_MCArbDramTimingRegisters, data) +
					  माप(SMC_SIslands_MCArbDramTimingRegisterSet) * SISLANDS_ULV_STATE_ARB_INDEX,
					  (u8 *)&arb_regs,
					  माप(SMC_SIslands_MCArbDramTimingRegisterSet),
					  si_pi->sram_end);

	वापस ret;
पूर्ण

अटल व्योम si_get_mvdd_configuration(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(adev);

	pi->mvdd_split_frequency = 30000;
पूर्ण

अटल पूर्णांक si_init_smc_table(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा si_घातer_info *si_pi = si_get_pi(adev);
	काष्ठा amdgpu_ps *amdgpu_boot_state = adev->pm.dpm.boot_ps;
	स्थिर काष्ठा si_ulv_param *ulv = &si_pi->ulv;
	SISLANDS_SMC_STATETABLE  *table = &si_pi->smc_statetable;
	पूर्णांक ret;
	u32 lane_width;
	u32 vr_hot_gpio;

	si_populate_smc_voltage_tables(adev, table);

	चयन (adev->pm.पूर्णांक_thermal_type) अणु
	हाल THERMAL_TYPE_SI:
	हाल THERMAL_TYPE_EMC2103_WITH_INTERNAL:
		table->thermalProtectType = PPSMC_THERMAL_PROTECT_TYPE_INTERNAL;
		अवरोध;
	हाल THERMAL_TYPE_NONE:
		table->thermalProtectType = PPSMC_THERMAL_PROTECT_TYPE_NONE;
		अवरोध;
	शेष:
		table->thermalProtectType = PPSMC_THERMAL_PROTECT_TYPE_EXTERNAL;
		अवरोध;
	पूर्ण

	अगर (adev->pm.dpm.platक्रमm_caps & ATOM_PP_PLATFORM_CAP_HARDWAREDC)
		table->प्रणालीFlags |= PPSMC_SYSTEMFLAG_GPIO_DC;

	अगर (adev->pm.dpm.platक्रमm_caps & ATOM_PP_PLATFORM_CAP_REGULATOR_HOT) अणु
		अगर ((adev->pdev->device != 0x6818) && (adev->pdev->device != 0x6819))
			table->प्रणालीFlags |= PPSMC_SYSTEMFLAG_REGULATOR_HOT;
	पूर्ण

	अगर (adev->pm.dpm.platक्रमm_caps & ATOM_PP_PLATFORM_CAP_STEPVDDC)
		table->प्रणालीFlags |= PPSMC_SYSTEMFLAG_STEPVDDC;

	अगर (adev->gmc.vram_type == AMDGPU_VRAM_TYPE_GDDR5)
		table->प्रणालीFlags |= PPSMC_SYSTEMFLAG_GDDR5;

	अगर (adev->pm.dpm.platक्रमm_caps & ATOM_PP_PLATFORM_CAP_REVERT_GPIO5_POLARITY)
		table->extraFlags |= PPSMC_EXTRAFLAGS_AC2DC_GPIO5_POLARITY_HIGH;

	अगर (adev->pm.dpm.platक्रमm_caps & ATOM_PP_PLATFORM_CAP_VRHOT_GPIO_CONFIGURABLE) अणु
		table->प्रणालीFlags |= PPSMC_SYSTEMFLAG_REGULATOR_HOT_PROG_GPIO;
		vr_hot_gpio = adev->pm.dpm.backbias_response_समय;
		si_ग_लिखो_smc_soft_रेजिस्टर(adev, SI_SMC_SOFT_REGISTER_vr_hot_gpio,
					   vr_hot_gpio);
	पूर्ण

	ret = si_populate_smc_initial_state(adev, amdgpu_boot_state, table);
	अगर (ret)
		वापस ret;

	ret = si_populate_smc_acpi_state(adev, table);
	अगर (ret)
		वापस ret;

	table->driverState.flags = table->initialState.flags;
	table->driverState.levelCount = table->initialState.levelCount;
	table->driverState.levels[0] = table->initialState.level;

	ret = si_करो_program_memory_timing_parameters(adev, amdgpu_boot_state,
						     SISLANDS_INITIAL_STATE_ARB_INDEX);
	अगर (ret)
		वापस ret;

	अगर (ulv->supported && ulv->pl.vddc) अणु
		ret = si_populate_ulv_state(adev, &table->ULVState);
		अगर (ret)
			वापस ret;

		ret = si_program_ulv_memory_timing_parameters(adev);
		अगर (ret)
			वापस ret;

		WREG32(CG_ULV_CONTROL, ulv->cg_ulv_control);
		WREG32(CG_ULV_PARAMETER, ulv->cg_ulv_parameter);

		lane_width = amdgpu_get_pcie_lanes(adev);
		si_ग_लिखो_smc_soft_रेजिस्टर(adev, SI_SMC_SOFT_REGISTER_non_ulv_pcie_link_width, lane_width);
	पूर्ण अन्यथा अणु
		table->ULVState = table->initialState;
	पूर्ण

	वापस amdgpu_si_copy_bytes_to_smc(adev, si_pi->state_table_start,
					   (u8 *)table, माप(SISLANDS_SMC_STATETABLE),
					   si_pi->sram_end);
पूर्ण

अटल पूर्णांक si_calculate_sclk_params(काष्ठा amdgpu_device *adev,
				    u32 engine_घड़ी,
				    SISLANDS_SMC_SCLK_VALUE *sclk)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(adev);
	काष्ठा si_घातer_info *si_pi = si_get_pi(adev);
	काष्ठा atom_घड़ी_भागiders भागiders;
	u32 spll_func_cntl = si_pi->घड़ी_रेजिस्टरs.cg_spll_func_cntl;
	u32 spll_func_cntl_2 = si_pi->घड़ी_रेजिस्टरs.cg_spll_func_cntl_2;
	u32 spll_func_cntl_3 = si_pi->घड़ी_रेजिस्टरs.cg_spll_func_cntl_3;
	u32 spll_func_cntl_4 = si_pi->घड़ी_रेजिस्टरs.cg_spll_func_cntl_4;
	u32 cg_spll_spपढ़ो_spectrum = si_pi->घड़ी_रेजिस्टरs.cg_spll_spपढ़ो_spectrum;
	u32 cg_spll_spपढ़ो_spectrum_2 = si_pi->घड़ी_रेजिस्टरs.cg_spll_spपढ़ो_spectrum_2;
	u64 पंचांगp;
	u32 reference_घड़ी = adev->घड़ी.spll.reference_freq;
	u32 reference_भागider;
	u32 fbभाग;
	पूर्णांक ret;

	ret = amdgpu_atombios_get_घड़ी_भागiders(adev, COMPUTE_ENGINE_PLL_PARAM,
					     engine_घड़ी, false, &भागiders);
	अगर (ret)
		वापस ret;

	reference_भागider = 1 + भागiders.ref_भाग;

	पंचांगp = (u64) engine_घड़ी * reference_भागider * भागiders.post_भाग * 16384;
	करो_भाग(पंचांगp, reference_घड़ी);
	fbभाग = (u32) पंचांगp;

	spll_func_cntl &= ~(SPLL_PDIV_A_MASK | SPLL_REF_DIV_MASK);
	spll_func_cntl |= SPLL_REF_DIV(भागiders.ref_भाग);
	spll_func_cntl |= SPLL_PDIV_A(भागiders.post_भाग);

	spll_func_cntl_2 &= ~SCLK_MUX_SEL_MASK;
	spll_func_cntl_2 |= SCLK_MUX_SEL(2);

	spll_func_cntl_3 &= ~SPLL_FB_DIV_MASK;
	spll_func_cntl_3 |= SPLL_FB_DIV(fbभाग);
	spll_func_cntl_3 |= SPLL_DITHEN;

	अगर (pi->sclk_ss) अणु
		काष्ठा amdgpu_atom_ss ss;
		u32 vco_freq = engine_घड़ी * भागiders.post_भाग;

		अगर (amdgpu_atombios_get_asic_ss_info(adev, &ss,
						     ASIC_INTERNAL_ENGINE_SS, vco_freq)) अणु
			u32 clk_s = reference_घड़ी * 5 / (reference_भागider * ss.rate);
			u32 clk_v = 4 * ss.percentage * fbभाग / (clk_s * 10000);

			cg_spll_spपढ़ो_spectrum &= ~CLK_S_MASK;
			cg_spll_spपढ़ो_spectrum |= CLK_S(clk_s);
			cg_spll_spपढ़ो_spectrum |= SSEN;

			cg_spll_spपढ़ो_spectrum_2 &= ~CLK_V_MASK;
			cg_spll_spपढ़ो_spectrum_2 |= CLK_V(clk_v);
		पूर्ण
	पूर्ण

	sclk->sclk_value = engine_घड़ी;
	sclk->vCG_SPLL_FUNC_CNTL = spll_func_cntl;
	sclk->vCG_SPLL_FUNC_CNTL_2 = spll_func_cntl_2;
	sclk->vCG_SPLL_FUNC_CNTL_3 = spll_func_cntl_3;
	sclk->vCG_SPLL_FUNC_CNTL_4 = spll_func_cntl_4;
	sclk->vCG_SPLL_SPREAD_SPECTRUM = cg_spll_spपढ़ो_spectrum;
	sclk->vCG_SPLL_SPREAD_SPECTRUM_2 = cg_spll_spपढ़ो_spectrum_2;

	वापस 0;
पूर्ण

अटल पूर्णांक si_populate_sclk_value(काष्ठा amdgpu_device *adev,
				  u32 engine_घड़ी,
				  SISLANDS_SMC_SCLK_VALUE *sclk)
अणु
	SISLANDS_SMC_SCLK_VALUE sclk_पंचांगp;
	पूर्णांक ret;

	ret = si_calculate_sclk_params(adev, engine_घड़ी, &sclk_पंचांगp);
	अगर (!ret) अणु
		sclk->sclk_value = cpu_to_be32(sclk_पंचांगp.sclk_value);
		sclk->vCG_SPLL_FUNC_CNTL = cpu_to_be32(sclk_पंचांगp.vCG_SPLL_FUNC_CNTL);
		sclk->vCG_SPLL_FUNC_CNTL_2 = cpu_to_be32(sclk_पंचांगp.vCG_SPLL_FUNC_CNTL_2);
		sclk->vCG_SPLL_FUNC_CNTL_3 = cpu_to_be32(sclk_पंचांगp.vCG_SPLL_FUNC_CNTL_3);
		sclk->vCG_SPLL_FUNC_CNTL_4 = cpu_to_be32(sclk_पंचांगp.vCG_SPLL_FUNC_CNTL_4);
		sclk->vCG_SPLL_SPREAD_SPECTRUM = cpu_to_be32(sclk_पंचांगp.vCG_SPLL_SPREAD_SPECTRUM);
		sclk->vCG_SPLL_SPREAD_SPECTRUM_2 = cpu_to_be32(sclk_पंचांगp.vCG_SPLL_SPREAD_SPECTRUM_2);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक si_populate_mclk_value(काष्ठा amdgpu_device *adev,
				  u32 engine_घड़ी,
				  u32 memory_घड़ी,
				  SISLANDS_SMC_MCLK_VALUE *mclk,
				  bool strobe_mode,
				  bool dll_state_on)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(adev);
	काष्ठा si_घातer_info *si_pi = si_get_pi(adev);
	u32  dll_cntl = si_pi->घड़ी_रेजिस्टरs.dll_cntl;
	u32  mclk_pwrmgt_cntl = si_pi->घड़ी_रेजिस्टरs.mclk_pwrmgt_cntl;
	u32  mpll_ad_func_cntl = si_pi->घड़ी_रेजिस्टरs.mpll_ad_func_cntl;
	u32  mpll_dq_func_cntl = si_pi->घड़ी_रेजिस्टरs.mpll_dq_func_cntl;
	u32  mpll_func_cntl = si_pi->घड़ी_रेजिस्टरs.mpll_func_cntl;
	u32  mpll_func_cntl_1 = si_pi->घड़ी_रेजिस्टरs.mpll_func_cntl_1;
	u32  mpll_func_cntl_2 = si_pi->घड़ी_रेजिस्टरs.mpll_func_cntl_2;
	u32  mpll_ss1 = si_pi->घड़ी_रेजिस्टरs.mpll_ss1;
	u32  mpll_ss2 = si_pi->घड़ी_रेजिस्टरs.mpll_ss2;
	काष्ठा atom_mpll_param mpll_param;
	पूर्णांक ret;

	ret = amdgpu_atombios_get_memory_pll_भागiders(adev, memory_घड़ी, strobe_mode, &mpll_param);
	अगर (ret)
		वापस ret;

	mpll_func_cntl &= ~BWCTRL_MASK;
	mpll_func_cntl |= BWCTRL(mpll_param.bwcntl);

	mpll_func_cntl_1 &= ~(CLKF_MASK | CLKFRAC_MASK | VCO_MODE_MASK);
	mpll_func_cntl_1 |= CLKF(mpll_param.clkf) |
		CLKFRAC(mpll_param.clkfrac) | VCO_MODE(mpll_param.vco_mode);

	mpll_ad_func_cntl &= ~YCLK_POST_DIV_MASK;
	mpll_ad_func_cntl |= YCLK_POST_DIV(mpll_param.post_भाग);

	अगर (adev->gmc.vram_type == AMDGPU_VRAM_TYPE_GDDR5) अणु
		mpll_dq_func_cntl &= ~(YCLK_SEL_MASK | YCLK_POST_DIV_MASK);
		mpll_dq_func_cntl |= YCLK_SEL(mpll_param.yclk_sel) |
			YCLK_POST_DIV(mpll_param.post_भाग);
	पूर्ण

	अगर (pi->mclk_ss) अणु
		काष्ठा amdgpu_atom_ss ss;
		u32 freq_nom;
		u32 पंचांगp;
		u32 reference_घड़ी = adev->घड़ी.mpll.reference_freq;

		अगर (adev->gmc.vram_type == AMDGPU_VRAM_TYPE_GDDR5)
			freq_nom = memory_घड़ी * 4;
		अन्यथा
			freq_nom = memory_घड़ी * 2;

		पंचांगp = freq_nom / reference_घड़ी;
		पंचांगp = पंचांगp * पंचांगp;
		अगर (amdgpu_atombios_get_asic_ss_info(adev, &ss,
		                                     ASIC_INTERNAL_MEMORY_SS, freq_nom)) अणु
			u32 clks = reference_घड़ी * 5 / ss.rate;
			u32 clkv = (u32)((((131 * ss.percentage * ss.rate) / 100) * पंचांगp) / freq_nom);

		        mpll_ss1 &= ~CLKV_MASK;
		        mpll_ss1 |= CLKV(clkv);

		        mpll_ss2 &= ~CLKS_MASK;
		        mpll_ss2 |= CLKS(clks);
		पूर्ण
	पूर्ण

	mclk_pwrmgt_cntl &= ~DLL_SPEED_MASK;
	mclk_pwrmgt_cntl |= DLL_SPEED(mpll_param.dll_speed);

	अगर (dll_state_on)
		mclk_pwrmgt_cntl |= MRDCK0_PDNB | MRDCK1_PDNB;
	अन्यथा
		mclk_pwrmgt_cntl &= ~(MRDCK0_PDNB | MRDCK1_PDNB);

	mclk->mclk_value = cpu_to_be32(memory_घड़ी);
	mclk->vMPLL_FUNC_CNTL = cpu_to_be32(mpll_func_cntl);
	mclk->vMPLL_FUNC_CNTL_1 = cpu_to_be32(mpll_func_cntl_1);
	mclk->vMPLL_FUNC_CNTL_2 = cpu_to_be32(mpll_func_cntl_2);
	mclk->vMPLL_AD_FUNC_CNTL = cpu_to_be32(mpll_ad_func_cntl);
	mclk->vMPLL_DQ_FUNC_CNTL = cpu_to_be32(mpll_dq_func_cntl);
	mclk->vMCLK_PWRMGT_CNTL = cpu_to_be32(mclk_pwrmgt_cntl);
	mclk->vDLL_CNTL = cpu_to_be32(dll_cntl);
	mclk->vMPLL_SS = cpu_to_be32(mpll_ss1);
	mclk->vMPLL_SS2 = cpu_to_be32(mpll_ss2);

	वापस 0;
पूर्ण

अटल व्योम si_populate_smc_sp(काष्ठा amdgpu_device *adev,
			       काष्ठा amdgpu_ps *amdgpu_state,
			       SISLANDS_SMC_SWSTATE *smc_state)
अणु
	काष्ठा  si_ps *ps = si_get_ps(amdgpu_state);
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(adev);
	पूर्णांक i;

	क्रम (i = 0; i < ps->perक्रमmance_level_count - 1; i++)
		smc_state->levels[i].bSP = cpu_to_be32(pi->dsp);

	smc_state->levels[ps->perक्रमmance_level_count - 1].bSP =
		cpu_to_be32(pi->psp);
पूर्ण

अटल पूर्णांक si_convert_घातer_level_to_smc(काष्ठा amdgpu_device *adev,
					 काष्ठा rv7xx_pl *pl,
					 SISLANDS_SMC_HW_PERFORMANCE_LEVEL *level)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(adev);
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(adev);
	काष्ठा si_घातer_info *si_pi = si_get_pi(adev);
	पूर्णांक ret;
	bool dll_state_on;
	u16 std_vddc;
	bool gmc_pg = false;

	अगर (eg_pi->pcie_perक्रमmance_request &&
	    (si_pi->क्रमce_pcie_gen != AMDGPU_PCIE_GEN_INVALID))
		level->gen2PCIE = (u8)si_pi->क्रमce_pcie_gen;
	अन्यथा
		level->gen2PCIE = (u8)pl->pcie_gen;

	ret = si_populate_sclk_value(adev, pl->sclk, &level->sclk);
	अगर (ret)
		वापस ret;

	level->mcFlags =  0;

	अगर (pi->mclk_stutter_mode_threshold &&
	    (pl->mclk <= pi->mclk_stutter_mode_threshold) &&
	    !eg_pi->uvd_enabled &&
	    (RREG32(DPG_PIPE_STUTTER_CONTROL) & STUTTER_ENABLE) &&
	    (adev->pm.dpm.new_active_crtc_count <= 2)) अणु
		level->mcFlags |= SISLANDS_SMC_MC_STUTTER_EN;

		अगर (gmc_pg)
			level->mcFlags |= SISLANDS_SMC_MC_PG_EN;
	पूर्ण

	अगर (adev->gmc.vram_type == AMDGPU_VRAM_TYPE_GDDR5) अणु
		अगर (pl->mclk > pi->mclk_edc_enable_threshold)
			level->mcFlags |= SISLANDS_SMC_MC_EDC_RD_FLAG;

		अगर (pl->mclk > eg_pi->mclk_edc_wr_enable_threshold)
			level->mcFlags |= SISLANDS_SMC_MC_EDC_WR_FLAG;

		level->strobeMode = si_get_strobe_mode_settings(adev, pl->mclk);

		अगर (level->strobeMode & SISLANDS_SMC_STROBE_ENABLE) अणु
			अगर (si_get_mclk_frequency_ratio(pl->mclk, true) >=
			    ((RREG32(MC_SEQ_MISC7) >> 16) & 0xf))
				dll_state_on = ((RREG32(MC_SEQ_MISC5) >> 1) & 0x1) ? true : false;
			अन्यथा
				dll_state_on = ((RREG32(MC_SEQ_MISC6) >> 1) & 0x1) ? true : false;
		पूर्ण अन्यथा अणु
			dll_state_on = false;
		पूर्ण
	पूर्ण अन्यथा अणु
		level->strobeMode = si_get_strobe_mode_settings(adev,
								pl->mclk);

		dll_state_on = ((RREG32(MC_SEQ_MISC5) >> 1) & 0x1) ? true : false;
	पूर्ण

	ret = si_populate_mclk_value(adev,
				     pl->sclk,
				     pl->mclk,
				     &level->mclk,
				     (level->strobeMode & SISLANDS_SMC_STROBE_ENABLE) != 0, dll_state_on);
	अगर (ret)
		वापस ret;

	ret = si_populate_voltage_value(adev,
					&eg_pi->vddc_voltage_table,
					pl->vddc, &level->vddc);
	अगर (ret)
		वापस ret;


	ret = si_get_std_voltage_value(adev, &level->vddc, &std_vddc);
	अगर (ret)
		वापस ret;

	ret = si_populate_std_voltage_value(adev, std_vddc,
					    level->vddc.index, &level->std_vddc);
	अगर (ret)
		वापस ret;

	अगर (eg_pi->vddci_control) अणु
		ret = si_populate_voltage_value(adev, &eg_pi->vddci_voltage_table,
						pl->vddci, &level->vddci);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (si_pi->vddc_phase_shed_control) अणु
		ret = si_populate_phase_shedding_value(adev,
						       &adev->pm.dpm.dyn_state.phase_shedding_limits_table,
						       pl->vddc,
						       pl->sclk,
						       pl->mclk,
						       &level->vddc);
		अगर (ret)
			वापस ret;
	पूर्ण

	level->MaxPoweredUpCU = si_pi->max_cu;

	ret = si_populate_mvdd_value(adev, pl->mclk, &level->mvdd);

	वापस ret;
पूर्ण

अटल पूर्णांक si_populate_smc_t(काष्ठा amdgpu_device *adev,
			     काष्ठा amdgpu_ps *amdgpu_state,
			     SISLANDS_SMC_SWSTATE *smc_state)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(adev);
	काष्ठा  si_ps *state = si_get_ps(amdgpu_state);
	u32 a_t;
	u32 t_l, t_h;
	u32 high_bsp;
	पूर्णांक i, ret;

	अगर (state->perक्रमmance_level_count >= 9)
		वापस -EINVAL;

	अगर (state->perक्रमmance_level_count < 2) अणु
		a_t = CG_R(0xffff) | CG_L(0);
		smc_state->levels[0].aT = cpu_to_be32(a_t);
		वापस 0;
	पूर्ण

	smc_state->levels[0].aT = cpu_to_be32(0);

	क्रम (i = 0; i <= state->perक्रमmance_level_count - 2; i++) अणु
		ret = r600_calculate_at(
			(50 / SISLANDS_MAX_HARDWARE_POWERLEVELS) * 100 * (i + 1),
			100 * R600_AH_DFLT,
			state->perक्रमmance_levels[i + 1].sclk,
			state->perक्रमmance_levels[i].sclk,
			&t_l,
			&t_h);

		अगर (ret) अणु
			t_h = (i + 1) * 1000 - 50 * R600_AH_DFLT;
			t_l = (i + 1) * 1000 + 50 * R600_AH_DFLT;
		पूर्ण

		a_t = be32_to_cpu(smc_state->levels[i].aT) & ~CG_R_MASK;
		a_t |= CG_R(t_l * pi->bsp / 20000);
		smc_state->levels[i].aT = cpu_to_be32(a_t);

		high_bsp = (i == state->perक्रमmance_level_count - 2) ?
			pi->pbsp : pi->bsp;
		a_t = CG_R(0xffff) | CG_L(t_h * high_bsp / 20000);
		smc_state->levels[i + 1].aT = cpu_to_be32(a_t);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक si_disable_ulv(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा si_घातer_info *si_pi = si_get_pi(adev);
	काष्ठा si_ulv_param *ulv = &si_pi->ulv;

	अगर (ulv->supported)
		वापस (amdgpu_si_send_msg_to_smc(adev, PPSMC_MSG_DisableULV) == PPSMC_Result_OK) ?
			0 : -EINVAL;

	वापस 0;
पूर्ण

अटल bool si_is_state_ulv_compatible(काष्ठा amdgpu_device *adev,
				       काष्ठा amdgpu_ps *amdgpu_state)
अणु
	स्थिर काष्ठा si_घातer_info *si_pi = si_get_pi(adev);
	स्थिर काष्ठा si_ulv_param *ulv = &si_pi->ulv;
	स्थिर काष्ठा  si_ps *state = si_get_ps(amdgpu_state);
	पूर्णांक i;

	अगर (state->perक्रमmance_levels[0].mclk != ulv->pl.mclk)
		वापस false;

	/* XXX validate against display requirements! */

	क्रम (i = 0; i < adev->pm.dpm.dyn_state.vddc_dependency_on_dispclk.count; i++) अणु
		अगर (adev->घड़ी.current_dispclk <=
		    adev->pm.dpm.dyn_state.vddc_dependency_on_dispclk.entries[i].clk) अणु
			अगर (ulv->pl.vddc <
			    adev->pm.dpm.dyn_state.vddc_dependency_on_dispclk.entries[i].v)
				वापस false;
		पूर्ण
	पूर्ण

	अगर ((amdgpu_state->vclk != 0) || (amdgpu_state->dclk != 0))
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक si_set_घातer_state_conditionally_enable_ulv(काष्ठा amdgpu_device *adev,
						       काष्ठा amdgpu_ps *amdgpu_new_state)
अणु
	स्थिर काष्ठा si_घातer_info *si_pi = si_get_pi(adev);
	स्थिर काष्ठा si_ulv_param *ulv = &si_pi->ulv;

	अगर (ulv->supported) अणु
		अगर (si_is_state_ulv_compatible(adev, amdgpu_new_state))
			वापस (amdgpu_si_send_msg_to_smc(adev, PPSMC_MSG_EnableULV) == PPSMC_Result_OK) ?
				0 : -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक si_convert_घातer_state_to_smc(काष्ठा amdgpu_device *adev,
					 काष्ठा amdgpu_ps *amdgpu_state,
					 SISLANDS_SMC_SWSTATE *smc_state)
अणु
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(adev);
	काष्ठा ni_घातer_info *ni_pi = ni_get_pi(adev);
	काष्ठा si_घातer_info *si_pi = si_get_pi(adev);
	काष्ठा  si_ps *state = si_get_ps(amdgpu_state);
	पूर्णांक i, ret;
	u32 threshold;
	u32 sclk_in_sr = 1350; /* ??? */

	अगर (state->perक्रमmance_level_count > SISLANDS_MAX_HARDWARE_POWERLEVELS)
		वापस -EINVAL;

	threshold = state->perक्रमmance_levels[state->perक्रमmance_level_count-1].sclk * 100 / 100;

	अगर (amdgpu_state->vclk && amdgpu_state->dclk) अणु
		eg_pi->uvd_enabled = true;
		अगर (eg_pi->smu_uvd_hs)
			smc_state->flags |= PPSMC_SWSTATE_FLAG_UVD;
	पूर्ण अन्यथा अणु
		eg_pi->uvd_enabled = false;
	पूर्ण

	अगर (state->dc_compatible)
		smc_state->flags |= PPSMC_SWSTATE_FLAG_DC;

	smc_state->levelCount = 0;
	क्रम (i = 0; i < state->perक्रमmance_level_count; i++) अणु
		अगर (eg_pi->sclk_deep_sleep) अणु
			अगर ((i == 0) || si_pi->sclk_deep_sleep_above_low) अणु
				अगर (sclk_in_sr <= SCLK_MIN_DEEPSLEEP_FREQ)
					smc_state->levels[i].stateFlags |= PPSMC_STATEFLAG_DEEPSLEEP_BYPASS;
				अन्यथा
					smc_state->levels[i].stateFlags |= PPSMC_STATEFLAG_DEEPSLEEP_THROTTLE;
			पूर्ण
		पूर्ण

		ret = si_convert_घातer_level_to_smc(adev, &state->perक्रमmance_levels[i],
						    &smc_state->levels[i]);
		smc_state->levels[i].arbRefreshState =
			(u8)(SISLANDS_DRIVER_STATE_ARB_INDEX + i);

		अगर (ret)
			वापस ret;

		अगर (ni_pi->enable_घातer_containment)
			smc_state->levels[i].displayWatermark =
				(state->perक्रमmance_levels[i].sclk < threshold) ?
				PPSMC_DISPLAY_WATERMARK_LOW : PPSMC_DISPLAY_WATERMARK_HIGH;
		अन्यथा
			smc_state->levels[i].displayWatermark = (i < 2) ?
				PPSMC_DISPLAY_WATERMARK_LOW : PPSMC_DISPLAY_WATERMARK_HIGH;

		अगर (eg_pi->dynamic_ac_timing)
			smc_state->levels[i].ACIndex = SISLANDS_MCREGISTERTABLE_FIRST_DRIVERSTATE_SLOT + i;
		अन्यथा
			smc_state->levels[i].ACIndex = 0;

		smc_state->levelCount++;
	पूर्ण

	si_ग_लिखो_smc_soft_रेजिस्टर(adev,
				   SI_SMC_SOFT_REGISTER_watermark_threshold,
				   threshold / 512);

	si_populate_smc_sp(adev, amdgpu_state, smc_state);

	ret = si_populate_घातer_containment_values(adev, amdgpu_state, smc_state);
	अगर (ret)
		ni_pi->enable_घातer_containment = false;

	ret = si_populate_sq_ramping_values(adev, amdgpu_state, smc_state);
	अगर (ret)
		ni_pi->enable_sq_ramping = false;

	वापस si_populate_smc_t(adev, amdgpu_state, smc_state);
पूर्ण

अटल पूर्णांक si_upload_sw_state(काष्ठा amdgpu_device *adev,
			      काष्ठा amdgpu_ps *amdgpu_new_state)
अणु
	काष्ठा si_घातer_info *si_pi = si_get_pi(adev);
	काष्ठा  si_ps *new_state = si_get_ps(amdgpu_new_state);
	पूर्णांक ret;
	u32 address = si_pi->state_table_start +
		दुरत्व(SISLANDS_SMC_STATETABLE, driverState);
	SISLANDS_SMC_SWSTATE *smc_state = &si_pi->smc_statetable.driverState;
	माप_प्रकार state_size = काष्ठा_size(smc_state, levels,
					new_state->perक्रमmance_level_count);
	स_रखो(smc_state, 0, state_size);

	ret = si_convert_घातer_state_to_smc(adev, amdgpu_new_state, smc_state);
	अगर (ret)
		वापस ret;

	वापस amdgpu_si_copy_bytes_to_smc(adev, address, (u8 *)smc_state,
					   state_size, si_pi->sram_end);
पूर्ण

अटल पूर्णांक si_upload_ulv_state(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा si_घातer_info *si_pi = si_get_pi(adev);
	काष्ठा si_ulv_param *ulv = &si_pi->ulv;
	पूर्णांक ret = 0;

	अगर (ulv->supported && ulv->pl.vddc) अणु
		u32 address = si_pi->state_table_start +
			दुरत्व(SISLANDS_SMC_STATETABLE, ULVState);
		काष्ठा SISLANDS_SMC_SWSTATE_SINGLE *smc_state = &si_pi->smc_statetable.ULVState;
		u32 state_size = माप(काष्ठा SISLANDS_SMC_SWSTATE_SINGLE);

		स_रखो(smc_state, 0, state_size);

		ret = si_populate_ulv_state(adev, smc_state);
		अगर (!ret)
			ret = amdgpu_si_copy_bytes_to_smc(adev, address, (u8 *)smc_state,
							  state_size, si_pi->sram_end);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक si_upload_smc_data(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_crtc *amdgpu_crtc = शून्य;
	पूर्णांक i;

	अगर (adev->pm.dpm.new_active_crtc_count == 0)
		वापस 0;

	क्रम (i = 0; i < adev->mode_info.num_crtc; i++) अणु
		अगर (adev->pm.dpm.new_active_crtcs & (1 << i)) अणु
			amdgpu_crtc = adev->mode_info.crtcs[i];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (amdgpu_crtc == शून्य)
		वापस 0;

	अगर (amdgpu_crtc->line_समय <= 0)
		वापस 0;

	अगर (si_ग_लिखो_smc_soft_रेजिस्टर(adev,
				       SI_SMC_SOFT_REGISTER_crtc_index,
				       amdgpu_crtc->crtc_id) != PPSMC_Result_OK)
		वापस 0;

	अगर (si_ग_लिखो_smc_soft_रेजिस्टर(adev,
				       SI_SMC_SOFT_REGISTER_mclk_change_block_cp_min,
				       amdgpu_crtc->wm_high / amdgpu_crtc->line_समय) != PPSMC_Result_OK)
		वापस 0;

	अगर (si_ग_लिखो_smc_soft_रेजिस्टर(adev,
				       SI_SMC_SOFT_REGISTER_mclk_change_block_cp_max,
				       amdgpu_crtc->wm_low / amdgpu_crtc->line_समय) != PPSMC_Result_OK)
		वापस 0;

	वापस 0;
पूर्ण

अटल पूर्णांक si_set_mc_special_रेजिस्टरs(काष्ठा amdgpu_device *adev,
				       काष्ठा si_mc_reg_table *table)
अणु
	u8 i, j, k;
	u32 temp_reg;

	क्रम (i = 0, j = table->last; i < table->last; i++) अणु
		अगर (j >= SMC_SISLANDS_MC_REGISTER_ARRAY_SIZE)
			वापस -EINVAL;
		चयन (table->mc_reg_address[i].s1) अणु
		हाल MC_SEQ_MISC1:
			temp_reg = RREG32(MC_PMG_CMD_EMRS);
			table->mc_reg_address[j].s1 = MC_PMG_CMD_EMRS;
			table->mc_reg_address[j].s0 = MC_SEQ_PMG_CMD_EMRS_LP;
			क्रम (k = 0; k < table->num_entries; k++)
				table->mc_reg_table_entry[k].mc_data[j] =
					((temp_reg & 0xffff0000)) |
					((table->mc_reg_table_entry[k].mc_data[i] & 0xffff0000) >> 16);
			j++;

			अगर (j >= SMC_SISLANDS_MC_REGISTER_ARRAY_SIZE)
				वापस -EINVAL;
			temp_reg = RREG32(MC_PMG_CMD_MRS);
			table->mc_reg_address[j].s1 = MC_PMG_CMD_MRS;
			table->mc_reg_address[j].s0 = MC_SEQ_PMG_CMD_MRS_LP;
			क्रम (k = 0; k < table->num_entries; k++) अणु
				table->mc_reg_table_entry[k].mc_data[j] =
					(temp_reg & 0xffff0000) |
					(table->mc_reg_table_entry[k].mc_data[i] & 0x0000ffff);
				अगर (adev->gmc.vram_type != AMDGPU_VRAM_TYPE_GDDR5)
					table->mc_reg_table_entry[k].mc_data[j] |= 0x100;
			पूर्ण
			j++;

			अगर (adev->gmc.vram_type != AMDGPU_VRAM_TYPE_GDDR5) अणु
				अगर (j >= SMC_SISLANDS_MC_REGISTER_ARRAY_SIZE)
					वापस -EINVAL;
				table->mc_reg_address[j].s1 = MC_PMG_AUTO_CMD;
				table->mc_reg_address[j].s0 = MC_PMG_AUTO_CMD;
				क्रम (k = 0; k < table->num_entries; k++)
					table->mc_reg_table_entry[k].mc_data[j] =
						(table->mc_reg_table_entry[k].mc_data[i] & 0xffff0000) >> 16;
				j++;
			पूर्ण
			अवरोध;
		हाल MC_SEQ_RESERVE_M:
			temp_reg = RREG32(MC_PMG_CMD_MRS1);
			table->mc_reg_address[j].s1 = MC_PMG_CMD_MRS1;
			table->mc_reg_address[j].s0 = MC_SEQ_PMG_CMD_MRS1_LP;
			क्रम(k = 0; k < table->num_entries; k++)
				table->mc_reg_table_entry[k].mc_data[j] =
					(temp_reg & 0xffff0000) |
					(table->mc_reg_table_entry[k].mc_data[i] & 0x0000ffff);
			j++;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	table->last = j;

	वापस 0;
पूर्ण

अटल bool si_check_s0_mc_reg_index(u16 in_reg, u16 *out_reg)
अणु
	bool result = true;
	चयन (in_reg) अणु
	हाल  MC_SEQ_RAS_TIMING:
		*out_reg = MC_SEQ_RAS_TIMING_LP;
		अवरोध;
	हाल MC_SEQ_CAS_TIMING:
		*out_reg = MC_SEQ_CAS_TIMING_LP;
		अवरोध;
	हाल MC_SEQ_MISC_TIMING:
		*out_reg = MC_SEQ_MISC_TIMING_LP;
		अवरोध;
	हाल MC_SEQ_MISC_TIMING2:
		*out_reg = MC_SEQ_MISC_TIMING2_LP;
		अवरोध;
	हाल MC_SEQ_RD_CTL_D0:
		*out_reg = MC_SEQ_RD_CTL_D0_LP;
		अवरोध;
	हाल MC_SEQ_RD_CTL_D1:
		*out_reg = MC_SEQ_RD_CTL_D1_LP;
		अवरोध;
	हाल MC_SEQ_WR_CTL_D0:
		*out_reg = MC_SEQ_WR_CTL_D0_LP;
		अवरोध;
	हाल MC_SEQ_WR_CTL_D1:
		*out_reg = MC_SEQ_WR_CTL_D1_LP;
		अवरोध;
	हाल MC_PMG_CMD_EMRS:
		*out_reg = MC_SEQ_PMG_CMD_EMRS_LP;
		अवरोध;
	हाल MC_PMG_CMD_MRS:
		*out_reg = MC_SEQ_PMG_CMD_MRS_LP;
		अवरोध;
	हाल MC_PMG_CMD_MRS1:
		*out_reg = MC_SEQ_PMG_CMD_MRS1_LP;
		अवरोध;
	हाल MC_SEQ_PMG_TIMING:
		*out_reg = MC_SEQ_PMG_TIMING_LP;
		अवरोध;
	हाल MC_PMG_CMD_MRS2:
		*out_reg = MC_SEQ_PMG_CMD_MRS2_LP;
		अवरोध;
	हाल MC_SEQ_WR_CTL_2:
		*out_reg = MC_SEQ_WR_CTL_2_LP;
		अवरोध;
	शेष:
		result = false;
		अवरोध;
	पूर्ण

	वापस result;
पूर्ण

अटल व्योम si_set_valid_flag(काष्ठा si_mc_reg_table *table)
अणु
	u8 i, j;

	क्रम (i = 0; i < table->last; i++) अणु
		क्रम (j = 1; j < table->num_entries; j++) अणु
			अगर (table->mc_reg_table_entry[j-1].mc_data[i] != table->mc_reg_table_entry[j].mc_data[i]) अणु
				table->valid_flag |= 1 << i;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम si_set_s0_mc_reg_index(काष्ठा si_mc_reg_table *table)
अणु
	u32 i;
	u16 address;

	क्रम (i = 0; i < table->last; i++)
		table->mc_reg_address[i].s0 = si_check_s0_mc_reg_index(table->mc_reg_address[i].s1, &address) ?
			address : table->mc_reg_address[i].s1;

पूर्ण

अटल पूर्णांक si_copy_vbios_mc_reg_table(काष्ठा atom_mc_reg_table *table,
				      काष्ठा si_mc_reg_table *si_table)
अणु
	u8 i, j;

	अगर (table->last > SMC_SISLANDS_MC_REGISTER_ARRAY_SIZE)
		वापस -EINVAL;
	अगर (table->num_entries > MAX_AC_TIMING_ENTRIES)
		वापस -EINVAL;

	क्रम (i = 0; i < table->last; i++)
		si_table->mc_reg_address[i].s1 = table->mc_reg_address[i].s1;
	si_table->last = table->last;

	क्रम (i = 0; i < table->num_entries; i++) अणु
		si_table->mc_reg_table_entry[i].mclk_max =
			table->mc_reg_table_entry[i].mclk_max;
		क्रम (j = 0; j < table->last; j++) अणु
			si_table->mc_reg_table_entry[i].mc_data[j] =
				table->mc_reg_table_entry[i].mc_data[j];
		पूर्ण
	पूर्ण
	si_table->num_entries = table->num_entries;

	वापस 0;
पूर्ण

अटल पूर्णांक si_initialize_mc_reg_table(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा si_घातer_info *si_pi = si_get_pi(adev);
	काष्ठा atom_mc_reg_table *table;
	काष्ठा si_mc_reg_table *si_table = &si_pi->mc_reg_table;
	u8 module_index = rv770_get_memory_module_index(adev);
	पूर्णांक ret;

	table = kzalloc(माप(काष्ठा atom_mc_reg_table), GFP_KERNEL);
	अगर (!table)
		वापस -ENOMEM;

	WREG32(MC_SEQ_RAS_TIMING_LP, RREG32(MC_SEQ_RAS_TIMING));
	WREG32(MC_SEQ_CAS_TIMING_LP, RREG32(MC_SEQ_CAS_TIMING));
	WREG32(MC_SEQ_MISC_TIMING_LP, RREG32(MC_SEQ_MISC_TIMING));
	WREG32(MC_SEQ_MISC_TIMING2_LP, RREG32(MC_SEQ_MISC_TIMING2));
	WREG32(MC_SEQ_PMG_CMD_EMRS_LP, RREG32(MC_PMG_CMD_EMRS));
	WREG32(MC_SEQ_PMG_CMD_MRS_LP, RREG32(MC_PMG_CMD_MRS));
	WREG32(MC_SEQ_PMG_CMD_MRS1_LP, RREG32(MC_PMG_CMD_MRS1));
	WREG32(MC_SEQ_WR_CTL_D0_LP, RREG32(MC_SEQ_WR_CTL_D0));
	WREG32(MC_SEQ_WR_CTL_D1_LP, RREG32(MC_SEQ_WR_CTL_D1));
	WREG32(MC_SEQ_RD_CTL_D0_LP, RREG32(MC_SEQ_RD_CTL_D0));
	WREG32(MC_SEQ_RD_CTL_D1_LP, RREG32(MC_SEQ_RD_CTL_D1));
	WREG32(MC_SEQ_PMG_TIMING_LP, RREG32(MC_SEQ_PMG_TIMING));
	WREG32(MC_SEQ_PMG_CMD_MRS2_LP, RREG32(MC_PMG_CMD_MRS2));
	WREG32(MC_SEQ_WR_CTL_2_LP, RREG32(MC_SEQ_WR_CTL_2));

	ret = amdgpu_atombios_init_mc_reg_table(adev, module_index, table);
	अगर (ret)
		जाओ init_mc_करोne;

	ret = si_copy_vbios_mc_reg_table(table, si_table);
	अगर (ret)
		जाओ init_mc_करोne;

	si_set_s0_mc_reg_index(si_table);

	ret = si_set_mc_special_रेजिस्टरs(adev, si_table);
	अगर (ret)
		जाओ init_mc_करोne;

	si_set_valid_flag(si_table);

init_mc_करोne:
	kमुक्त(table);

	वापस ret;

पूर्ण

अटल व्योम si_populate_mc_reg_addresses(काष्ठा amdgpu_device *adev,
					 SMC_SIslands_MCRegisters *mc_reg_table)
अणु
	काष्ठा si_घातer_info *si_pi = si_get_pi(adev);
	u32 i, j;

	क्रम (i = 0, j = 0; j < si_pi->mc_reg_table.last; j++) अणु
		अगर (si_pi->mc_reg_table.valid_flag & (1 << j)) अणु
			अगर (i >= SMC_SISLANDS_MC_REGISTER_ARRAY_SIZE)
				अवरोध;
			mc_reg_table->address[i].s0 =
				cpu_to_be16(si_pi->mc_reg_table.mc_reg_address[j].s0);
			mc_reg_table->address[i].s1 =
				cpu_to_be16(si_pi->mc_reg_table.mc_reg_address[j].s1);
			i++;
		पूर्ण
	पूर्ण
	mc_reg_table->last = (u8)i;
पूर्ण

अटल व्योम si_convert_mc_रेजिस्टरs(स्थिर काष्ठा si_mc_reg_entry *entry,
				    SMC_SIslands_MCRegisterSet *data,
				    u32 num_entries, u32 valid_flag)
अणु
	u32 i, j;

	क्रम(i = 0, j = 0; j < num_entries; j++) अणु
		अगर (valid_flag & (1 << j)) अणु
			data->value[i] = cpu_to_be32(entry->mc_data[j]);
			i++;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम si_convert_mc_reg_table_entry_to_smc(काष्ठा amdgpu_device *adev,
						 काष्ठा rv7xx_pl *pl,
						 SMC_SIslands_MCRegisterSet *mc_reg_table_data)
अणु
	काष्ठा si_घातer_info *si_pi = si_get_pi(adev);
	u32 i = 0;

	क्रम (i = 0; i < si_pi->mc_reg_table.num_entries; i++) अणु
		अगर (pl->mclk <= si_pi->mc_reg_table.mc_reg_table_entry[i].mclk_max)
			अवरोध;
	पूर्ण

	अगर ((i == si_pi->mc_reg_table.num_entries) && (i > 0))
		--i;

	si_convert_mc_रेजिस्टरs(&si_pi->mc_reg_table.mc_reg_table_entry[i],
				mc_reg_table_data, si_pi->mc_reg_table.last,
				si_pi->mc_reg_table.valid_flag);
पूर्ण

अटल व्योम si_convert_mc_reg_table_to_smc(काष्ठा amdgpu_device *adev,
					   काष्ठा amdgpu_ps *amdgpu_state,
					   SMC_SIslands_MCRegisters *mc_reg_table)
अणु
	काष्ठा si_ps *state = si_get_ps(amdgpu_state);
	पूर्णांक i;

	क्रम (i = 0; i < state->perक्रमmance_level_count; i++) अणु
		si_convert_mc_reg_table_entry_to_smc(adev,
						     &state->perक्रमmance_levels[i],
						     &mc_reg_table->data[SISLANDS_MCREGISTERTABLE_FIRST_DRIVERSTATE_SLOT + i]);
	पूर्ण
पूर्ण

अटल पूर्णांक si_populate_mc_reg_table(काष्ठा amdgpu_device *adev,
				    काष्ठा amdgpu_ps *amdgpu_boot_state)
अणु
	काष्ठा  si_ps *boot_state = si_get_ps(amdgpu_boot_state);
	काष्ठा si_घातer_info *si_pi = si_get_pi(adev);
	काष्ठा si_ulv_param *ulv = &si_pi->ulv;
	SMC_SIslands_MCRegisters *smc_mc_reg_table = &si_pi->smc_mc_reg_table;

	स_रखो(smc_mc_reg_table, 0, माप(SMC_SIslands_MCRegisters));

	si_ग_लिखो_smc_soft_रेजिस्टर(adev, SI_SMC_SOFT_REGISTER_seq_index, 1);

	si_populate_mc_reg_addresses(adev, smc_mc_reg_table);

	si_convert_mc_reg_table_entry_to_smc(adev, &boot_state->perक्रमmance_levels[0],
					     &smc_mc_reg_table->data[SISLANDS_MCREGISTERTABLE_INITIAL_SLOT]);

	si_convert_mc_रेजिस्टरs(&si_pi->mc_reg_table.mc_reg_table_entry[0],
				&smc_mc_reg_table->data[SISLANDS_MCREGISTERTABLE_ACPI_SLOT],
				si_pi->mc_reg_table.last,
				si_pi->mc_reg_table.valid_flag);

	अगर (ulv->supported && ulv->pl.vddc != 0)
		si_convert_mc_reg_table_entry_to_smc(adev, &ulv->pl,
						     &smc_mc_reg_table->data[SISLANDS_MCREGISTERTABLE_ULV_SLOT]);
	अन्यथा
		si_convert_mc_रेजिस्टरs(&si_pi->mc_reg_table.mc_reg_table_entry[0],
					&smc_mc_reg_table->data[SISLANDS_MCREGISTERTABLE_ULV_SLOT],
					si_pi->mc_reg_table.last,
					si_pi->mc_reg_table.valid_flag);

	si_convert_mc_reg_table_to_smc(adev, amdgpu_boot_state, smc_mc_reg_table);

	वापस amdgpu_si_copy_bytes_to_smc(adev, si_pi->mc_reg_table_start,
					   (u8 *)smc_mc_reg_table,
					   माप(SMC_SIslands_MCRegisters), si_pi->sram_end);
पूर्ण

अटल पूर्णांक si_upload_mc_reg_table(काष्ठा amdgpu_device *adev,
				  काष्ठा amdgpu_ps *amdgpu_new_state)
अणु
	काष्ठा si_ps *new_state = si_get_ps(amdgpu_new_state);
	काष्ठा si_घातer_info *si_pi = si_get_pi(adev);
	u32 address = si_pi->mc_reg_table_start +
		दुरत्व(SMC_SIslands_MCRegisters,
			 data[SISLANDS_MCREGISTERTABLE_FIRST_DRIVERSTATE_SLOT]);
	SMC_SIslands_MCRegisters *smc_mc_reg_table = &si_pi->smc_mc_reg_table;

	स_रखो(smc_mc_reg_table, 0, माप(SMC_SIslands_MCRegisters));

	si_convert_mc_reg_table_to_smc(adev, amdgpu_new_state, smc_mc_reg_table);

	वापस amdgpu_si_copy_bytes_to_smc(adev, address,
					   (u8 *)&smc_mc_reg_table->data[SISLANDS_MCREGISTERTABLE_FIRST_DRIVERSTATE_SLOT],
					   माप(SMC_SIslands_MCRegisterSet) * new_state->perक्रमmance_level_count,
					   si_pi->sram_end);
पूर्ण

अटल व्योम si_enable_voltage_control(काष्ठा amdgpu_device *adev, bool enable)
अणु
	अगर (enable)
		WREG32_P(GENERAL_PWRMGT, VOLT_PWRMGT_EN, ~VOLT_PWRMGT_EN);
	अन्यथा
		WREG32_P(GENERAL_PWRMGT, 0, ~VOLT_PWRMGT_EN);
पूर्ण

अटल क्रमागत amdgpu_pcie_gen si_get_maximum_link_speed(काष्ठा amdgpu_device *adev,
						      काष्ठा amdgpu_ps *amdgpu_state)
अणु
	काष्ठा si_ps *state = si_get_ps(amdgpu_state);
	पूर्णांक i;
	u16 pcie_speed, max_speed = 0;

	क्रम (i = 0; i < state->perक्रमmance_level_count; i++) अणु
		pcie_speed = state->perक्रमmance_levels[i].pcie_gen;
		अगर (max_speed < pcie_speed)
			max_speed = pcie_speed;
	पूर्ण
	वापस max_speed;
पूर्ण

अटल u16 si_get_current_pcie_speed(काष्ठा amdgpu_device *adev)
अणु
	u32 speed_cntl;

	speed_cntl = RREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL) & LC_CURRENT_DATA_RATE_MASK;
	speed_cntl >>= LC_CURRENT_DATA_RATE_SHIFT;

	वापस (u16)speed_cntl;
पूर्ण

अटल व्योम si_request_link_speed_change_beक्रमe_state_change(काष्ठा amdgpu_device *adev,
							     काष्ठा amdgpu_ps *amdgpu_new_state,
							     काष्ठा amdgpu_ps *amdgpu_current_state)
अणु
	काष्ठा si_घातer_info *si_pi = si_get_pi(adev);
	क्रमागत amdgpu_pcie_gen target_link_speed = si_get_maximum_link_speed(adev, amdgpu_new_state);
	क्रमागत amdgpu_pcie_gen current_link_speed;

	अगर (si_pi->क्रमce_pcie_gen == AMDGPU_PCIE_GEN_INVALID)
		current_link_speed = si_get_maximum_link_speed(adev, amdgpu_current_state);
	अन्यथा
		current_link_speed = si_pi->क्रमce_pcie_gen;

	si_pi->क्रमce_pcie_gen = AMDGPU_PCIE_GEN_INVALID;
	si_pi->pspp_notअगरy_required = false;
	अगर (target_link_speed > current_link_speed) अणु
		चयन (target_link_speed) अणु
#अगर defined(CONFIG_ACPI)
		हाल AMDGPU_PCIE_GEN3:
			अगर (amdgpu_acpi_pcie_perक्रमmance_request(adev, PCIE_PERF_REQ_PECI_GEN3, false) == 0)
				अवरोध;
			si_pi->क्रमce_pcie_gen = AMDGPU_PCIE_GEN2;
			अगर (current_link_speed == AMDGPU_PCIE_GEN2)
				अवरोध;
			fallthrough;
		हाल AMDGPU_PCIE_GEN2:
			अगर (amdgpu_acpi_pcie_perक्रमmance_request(adev, PCIE_PERF_REQ_PECI_GEN2, false) == 0)
				अवरोध;
			fallthrough;
#पूर्ण_अगर
		शेष:
			si_pi->क्रमce_pcie_gen = si_get_current_pcie_speed(adev);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (target_link_speed < current_link_speed)
			si_pi->pspp_notअगरy_required = true;
	पूर्ण
पूर्ण

अटल व्योम si_notअगरy_link_speed_change_after_state_change(काष्ठा amdgpu_device *adev,
							   काष्ठा amdgpu_ps *amdgpu_new_state,
							   काष्ठा amdgpu_ps *amdgpu_current_state)
अणु
	काष्ठा si_घातer_info *si_pi = si_get_pi(adev);
	क्रमागत amdgpu_pcie_gen target_link_speed = si_get_maximum_link_speed(adev, amdgpu_new_state);
	u8 request;

	अगर (si_pi->pspp_notअगरy_required) अणु
		अगर (target_link_speed == AMDGPU_PCIE_GEN3)
			request = PCIE_PERF_REQ_PECI_GEN3;
		अन्यथा अगर (target_link_speed == AMDGPU_PCIE_GEN2)
			request = PCIE_PERF_REQ_PECI_GEN2;
		अन्यथा
			request = PCIE_PERF_REQ_PECI_GEN1;

		अगर ((request == PCIE_PERF_REQ_PECI_GEN1) &&
		    (si_get_current_pcie_speed(adev) > 0))
			वापस;

#अगर defined(CONFIG_ACPI)
		amdgpu_acpi_pcie_perक्रमmance_request(adev, request, false);
#पूर्ण_अगर
	पूर्ण
पूर्ण

#अगर 0
अटल पूर्णांक si_ds_request(काष्ठा amdgpu_device *adev,
			 bool ds_status_on, u32 count_ग_लिखो)
अणु
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(adev);

	अगर (eg_pi->sclk_deep_sleep) अणु
		अगर (ds_status_on)
			वापस (amdgpu_si_send_msg_to_smc(adev, PPSMC_MSG_CancelThrottleOVRDSCLKDS) ==
				PPSMC_Result_OK) ?
				0 : -EINVAL;
		अन्यथा
			वापस (amdgpu_si_send_msg_to_smc(adev, PPSMC_MSG_ThrottleOVRDSCLKDS) ==
				PPSMC_Result_OK) ? 0 : -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल व्योम si_set_max_cu_value(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा si_घातer_info *si_pi = si_get_pi(adev);

	अगर (adev->asic_type == CHIP_VERDE) अणु
		चयन (adev->pdev->device) अणु
		हाल 0x6820:
		हाल 0x6825:
		हाल 0x6821:
		हाल 0x6823:
		हाल 0x6827:
			si_pi->max_cu = 10;
			अवरोध;
		हाल 0x682D:
		हाल 0x6824:
		हाल 0x682F:
		हाल 0x6826:
			si_pi->max_cu = 8;
			अवरोध;
		हाल 0x6828:
		हाल 0x6830:
		हाल 0x6831:
		हाल 0x6838:
		हाल 0x6839:
		हाल 0x683D:
			si_pi->max_cu = 10;
			अवरोध;
		हाल 0x683B:
		हाल 0x683F:
		हाल 0x6829:
			si_pi->max_cu = 8;
			अवरोध;
		शेष:
			si_pi->max_cu = 0;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		si_pi->max_cu = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक si_patch_single_dependency_table_based_on_leakage(काष्ठा amdgpu_device *adev,
							     काष्ठा amdgpu_घड़ी_voltage_dependency_table *table)
अणु
	u32 i;
	पूर्णांक j;
	u16 leakage_voltage;

	अगर (table) अणु
		क्रम (i = 0; i < table->count; i++) अणु
			चयन (si_get_leakage_voltage_from_leakage_index(adev,
									  table->entries[i].v,
									  &leakage_voltage)) अणु
			हाल 0:
				table->entries[i].v = leakage_voltage;
				अवरोध;
			हाल -EAGAIN:
				वापस -EINVAL;
			हाल -EINVAL:
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण

		क्रम (j = (table->count - 2); j >= 0; j--) अणु
			table->entries[j].v = (table->entries[j].v <= table->entries[j + 1].v) ?
				table->entries[j].v : table->entries[j + 1].v;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक si_patch_dependency_tables_based_on_leakage(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक ret = 0;

	ret = si_patch_single_dependency_table_based_on_leakage(adev,
								&adev->pm.dpm.dyn_state.vddc_dependency_on_sclk);
	अगर (ret)
		DRM_ERROR("Could not patch vddc_on_sclk leakage table\n");
	ret = si_patch_single_dependency_table_based_on_leakage(adev,
								&adev->pm.dpm.dyn_state.vddc_dependency_on_mclk);
	अगर (ret)
		DRM_ERROR("Could not patch vddc_on_mclk leakage table\n");
	ret = si_patch_single_dependency_table_based_on_leakage(adev,
								&adev->pm.dpm.dyn_state.vddci_dependency_on_mclk);
	अगर (ret)
		DRM_ERROR("Could not patch vddci_on_mclk leakage table\n");
	वापस ret;
पूर्ण

अटल व्योम si_set_pcie_lane_width_in_smc(काष्ठा amdgpu_device *adev,
					  काष्ठा amdgpu_ps *amdgpu_new_state,
					  काष्ठा amdgpu_ps *amdgpu_current_state)
अणु
	u32 lane_width;
	u32 new_lane_width =
		((amdgpu_new_state->caps & ATOM_PPLIB_PCIE_LINK_WIDTH_MASK) >> ATOM_PPLIB_PCIE_LINK_WIDTH_SHIFT) + 1;
	u32 current_lane_width =
		((amdgpu_current_state->caps & ATOM_PPLIB_PCIE_LINK_WIDTH_MASK) >> ATOM_PPLIB_PCIE_LINK_WIDTH_SHIFT) + 1;

	अगर (new_lane_width != current_lane_width) अणु
		amdgpu_set_pcie_lanes(adev, new_lane_width);
		lane_width = amdgpu_get_pcie_lanes(adev);
		si_ग_लिखो_smc_soft_रेजिस्टर(adev, SI_SMC_SOFT_REGISTER_non_ulv_pcie_link_width, lane_width);
	पूर्ण
पूर्ण

अटल व्योम si_dpm_setup_asic(काष्ठा amdgpu_device *adev)
अणु
	si_पढ़ो_घड़ी_रेजिस्टरs(adev);
	si_enable_acpi_घातer_management(adev);
पूर्ण

अटल पूर्णांक si_thermal_enable_alert(काष्ठा amdgpu_device *adev,
				   bool enable)
अणु
	u32 thermal_पूर्णांक = RREG32(CG_THERMAL_INT);

	अगर (enable) अणु
		PPSMC_Result result;

		thermal_पूर्णांक &= ~(THERM_INT_MASK_HIGH | THERM_INT_MASK_LOW);
		WREG32(CG_THERMAL_INT, thermal_पूर्णांक);
		result = amdgpu_si_send_msg_to_smc(adev, PPSMC_MSG_EnableThermalInterrupt);
		अगर (result != PPSMC_Result_OK) अणु
			DRM_DEBUG_KMS("Could not enable thermal interrupts.\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		thermal_पूर्णांक |= THERM_INT_MASK_HIGH | THERM_INT_MASK_LOW;
		WREG32(CG_THERMAL_INT, thermal_पूर्णांक);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक si_thermal_set_temperature_range(काष्ठा amdgpu_device *adev,
					    पूर्णांक min_temp, पूर्णांक max_temp)
अणु
	पूर्णांक low_temp = 0 * 1000;
	पूर्णांक high_temp = 255 * 1000;

	अगर (low_temp < min_temp)
		low_temp = min_temp;
	अगर (high_temp > max_temp)
		high_temp = max_temp;
	अगर (high_temp < low_temp) अणु
		DRM_ERROR("invalid thermal range: %d - %d\n", low_temp, high_temp);
		वापस -EINVAL;
	पूर्ण

	WREG32_P(CG_THERMAL_INT, DIG_THERM_INTH(high_temp / 1000), ~DIG_THERM_INTH_MASK);
	WREG32_P(CG_THERMAL_INT, DIG_THERM_INTL(low_temp / 1000), ~DIG_THERM_INTL_MASK);
	WREG32_P(CG_THERMAL_CTRL, DIG_THERM_DPM(high_temp / 1000), ~DIG_THERM_DPM_MASK);

	adev->pm.dpm.thermal.min_temp = low_temp;
	adev->pm.dpm.thermal.max_temp = high_temp;

	वापस 0;
पूर्ण

अटल व्योम si_fan_ctrl_set_अटल_mode(काष्ठा amdgpu_device *adev, u32 mode)
अणु
	काष्ठा si_घातer_info *si_pi = si_get_pi(adev);
	u32 पंचांगp;

	अगर (si_pi->fan_ctrl_is_in_शेष_mode) अणु
		पंचांगp = (RREG32(CG_FDO_CTRL2) & FDO_PWM_MODE_MASK) >> FDO_PWM_MODE_SHIFT;
		si_pi->fan_ctrl_शेष_mode = पंचांगp;
		पंचांगp = (RREG32(CG_FDO_CTRL2) & TMIN_MASK) >> TMIN_SHIFT;
		si_pi->t_min = पंचांगp;
		si_pi->fan_ctrl_is_in_शेष_mode = false;
	पूर्ण

	पंचांगp = RREG32(CG_FDO_CTRL2) & ~TMIN_MASK;
	पंचांगp |= TMIN(0);
	WREG32(CG_FDO_CTRL2, पंचांगp);

	पंचांगp = RREG32(CG_FDO_CTRL2) & ~FDO_PWM_MODE_MASK;
	पंचांगp |= FDO_PWM_MODE(mode);
	WREG32(CG_FDO_CTRL2, पंचांगp);
पूर्ण

अटल पूर्णांक si_thermal_setup_fan_table(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा si_घातer_info *si_pi = si_get_pi(adev);
	PP_SIslands_FanTable fan_table = अणु FDO_MODE_HARDWARE पूर्ण;
	u32 duty100;
	u32 t_dअगरf1, t_dअगरf2, pwm_dअगरf1, pwm_dअगरf2;
	u16 fकरो_min, slope1, slope2;
	u32 reference_घड़ी, पंचांगp;
	पूर्णांक ret;
	u64 पंचांगp64;

	अगर (!si_pi->fan_table_start) अणु
		adev->pm.dpm.fan.ucode_fan_control = false;
		वापस 0;
	पूर्ण

	duty100 = (RREG32(CG_FDO_CTRL1) & FMAX_DUTY100_MASK) >> FMAX_DUTY100_SHIFT;

	अगर (duty100 == 0) अणु
		adev->pm.dpm.fan.ucode_fan_control = false;
		वापस 0;
	पूर्ण

	पंचांगp64 = (u64)adev->pm.dpm.fan.pwm_min * duty100;
	करो_भाग(पंचांगp64, 10000);
	fकरो_min = (u16)पंचांगp64;

	t_dअगरf1 = adev->pm.dpm.fan.t_med - adev->pm.dpm.fan.t_min;
	t_dअगरf2 = adev->pm.dpm.fan.t_high - adev->pm.dpm.fan.t_med;

	pwm_dअगरf1 = adev->pm.dpm.fan.pwm_med - adev->pm.dpm.fan.pwm_min;
	pwm_dअगरf2 = adev->pm.dpm.fan.pwm_high - adev->pm.dpm.fan.pwm_med;

	slope1 = (u16)((50 + ((16 * duty100 * pwm_dअगरf1) / t_dअगरf1)) / 100);
	slope2 = (u16)((50 + ((16 * duty100 * pwm_dअगरf2) / t_dअगरf2)) / 100);

	fan_table.temp_min = cpu_to_be16((50 + adev->pm.dpm.fan.t_min) / 100);
	fan_table.temp_med = cpu_to_be16((50 + adev->pm.dpm.fan.t_med) / 100);
	fan_table.temp_max = cpu_to_be16((50 + adev->pm.dpm.fan.t_max) / 100);
	fan_table.slope1 = cpu_to_be16(slope1);
	fan_table.slope2 = cpu_to_be16(slope2);
	fan_table.fकरो_min = cpu_to_be16(fकरो_min);
	fan_table.hys_करोwn = cpu_to_be16(adev->pm.dpm.fan.t_hyst);
	fan_table.hys_up = cpu_to_be16(1);
	fan_table.hys_slope = cpu_to_be16(1);
	fan_table.temp_resp_lim = cpu_to_be16(5);
	reference_घड़ी = amdgpu_asic_get_xclk(adev);

	fan_table.refresh_period = cpu_to_be32((adev->pm.dpm.fan.cycle_delay *
						reference_घड़ी) / 1600);
	fan_table.fकरो_max = cpu_to_be16((u16)duty100);

	पंचांगp = (RREG32(CG_MULT_THERMAL_CTRL) & TEMP_SEL_MASK) >> TEMP_SEL_SHIFT;
	fan_table.temp_src = (uपूर्णांक8_t)पंचांगp;

	ret = amdgpu_si_copy_bytes_to_smc(adev,
					  si_pi->fan_table_start,
					  (u8 *)(&fan_table),
					  माप(fan_table),
					  si_pi->sram_end);

	अगर (ret) अणु
		DRM_ERROR("Failed to load fan table to the SMC.");
		adev->pm.dpm.fan.ucode_fan_control = false;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक si_fan_ctrl_start_smc_fan_control(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा si_घातer_info *si_pi = si_get_pi(adev);
	PPSMC_Result ret;

	ret = amdgpu_si_send_msg_to_smc(adev, PPSMC_StartFanControl);
	अगर (ret == PPSMC_Result_OK) अणु
		si_pi->fan_is_controlled_by_smc = true;
		वापस 0;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक si_fan_ctrl_stop_smc_fan_control(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा si_घातer_info *si_pi = si_get_pi(adev);
	PPSMC_Result ret;

	ret = amdgpu_si_send_msg_to_smc(adev, PPSMC_StopFanControl);

	अगर (ret == PPSMC_Result_OK) अणु
		si_pi->fan_is_controlled_by_smc = false;
		वापस 0;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक si_dpm_get_fan_speed_percent(व्योम *handle,
				      u32 *speed)
अणु
	u32 duty, duty100;
	u64 पंचांगp64;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (adev->pm.no_fan)
		वापस -ENOENT;

	duty100 = (RREG32(CG_FDO_CTRL1) & FMAX_DUTY100_MASK) >> FMAX_DUTY100_SHIFT;
	duty = (RREG32(CG_THERMAL_STATUS) & FDO_PWM_DUTY_MASK) >> FDO_PWM_DUTY_SHIFT;

	अगर (duty100 == 0)
		वापस -EINVAL;

	पंचांगp64 = (u64)duty * 100;
	करो_भाग(पंचांगp64, duty100);
	*speed = (u32)पंचांगp64;

	अगर (*speed > 100)
		*speed = 100;

	वापस 0;
पूर्ण

अटल पूर्णांक si_dpm_set_fan_speed_percent(व्योम *handle,
				      u32 speed)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	काष्ठा si_घातer_info *si_pi = si_get_pi(adev);
	u32 पंचांगp;
	u32 duty, duty100;
	u64 पंचांगp64;

	अगर (adev->pm.no_fan)
		वापस -ENOENT;

	अगर (si_pi->fan_is_controlled_by_smc)
		वापस -EINVAL;

	अगर (speed > 100)
		वापस -EINVAL;

	duty100 = (RREG32(CG_FDO_CTRL1) & FMAX_DUTY100_MASK) >> FMAX_DUTY100_SHIFT;

	अगर (duty100 == 0)
		वापस -EINVAL;

	पंचांगp64 = (u64)speed * duty100;
	करो_भाग(पंचांगp64, 100);
	duty = (u32)पंचांगp64;

	पंचांगp = RREG32(CG_FDO_CTRL0) & ~FDO_STATIC_DUTY_MASK;
	पंचांगp |= FDO_STATIC_DUTY(duty);
	WREG32(CG_FDO_CTRL0, पंचांगp);

	वापस 0;
पूर्ण

अटल व्योम si_dpm_set_fan_control_mode(व्योम *handle, u32 mode)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (mode) अणु
		/* stop स्वतः-manage */
		अगर (adev->pm.dpm.fan.ucode_fan_control)
			si_fan_ctrl_stop_smc_fan_control(adev);
		si_fan_ctrl_set_अटल_mode(adev, mode);
	पूर्ण अन्यथा अणु
		/* restart स्वतः-manage */
		अगर (adev->pm.dpm.fan.ucode_fan_control)
			si_thermal_start_smc_fan_control(adev);
		अन्यथा
			si_fan_ctrl_set_शेष_mode(adev);
	पूर्ण
पूर्ण

अटल u32 si_dpm_get_fan_control_mode(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	काष्ठा si_घातer_info *si_pi = si_get_pi(adev);
	u32 पंचांगp;

	अगर (si_pi->fan_is_controlled_by_smc)
		वापस 0;

	पंचांगp = RREG32(CG_FDO_CTRL2) & FDO_PWM_MODE_MASK;
	वापस (पंचांगp >> FDO_PWM_MODE_SHIFT);
पूर्ण

#अगर 0
अटल पूर्णांक si_fan_ctrl_get_fan_speed_rpm(काष्ठा amdgpu_device *adev,
					 u32 *speed)
अणु
	u32 tach_period;
	u32 xclk = amdgpu_asic_get_xclk(adev);

	अगर (adev->pm.no_fan)
		वापस -ENOENT;

	अगर (adev->pm.fan_pulses_per_revolution == 0)
		वापस -ENOENT;

	tach_period = (RREG32(CG_TACH_STATUS) & TACH_PERIOD_MASK) >> TACH_PERIOD_SHIFT;
	अगर (tach_period == 0)
		वापस -ENOENT;

	*speed = 60 * xclk * 10000 / tach_period;

	वापस 0;
पूर्ण

अटल पूर्णांक si_fan_ctrl_set_fan_speed_rpm(काष्ठा amdgpu_device *adev,
					 u32 speed)
अणु
	u32 tach_period, पंचांगp;
	u32 xclk = amdgpu_asic_get_xclk(adev);

	अगर (adev->pm.no_fan)
		वापस -ENOENT;

	अगर (adev->pm.fan_pulses_per_revolution == 0)
		वापस -ENOENT;

	अगर ((speed < adev->pm.fan_min_rpm) ||
	    (speed > adev->pm.fan_max_rpm))
		वापस -EINVAL;

	अगर (adev->pm.dpm.fan.ucode_fan_control)
		si_fan_ctrl_stop_smc_fan_control(adev);

	tach_period = 60 * xclk * 10000 / (8 * speed);
	पंचांगp = RREG32(CG_TACH_CTRL) & ~TARGET_PERIOD_MASK;
	पंचांगp |= TARGET_PERIOD(tach_period);
	WREG32(CG_TACH_CTRL, पंचांगp);

	si_fan_ctrl_set_अटल_mode(adev, FDO_PWM_MODE_STATIC_RPM);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल व्योम si_fan_ctrl_set_शेष_mode(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा si_घातer_info *si_pi = si_get_pi(adev);
	u32 पंचांगp;

	अगर (!si_pi->fan_ctrl_is_in_शेष_mode) अणु
		पंचांगp = RREG32(CG_FDO_CTRL2) & ~FDO_PWM_MODE_MASK;
		पंचांगp |= FDO_PWM_MODE(si_pi->fan_ctrl_शेष_mode);
		WREG32(CG_FDO_CTRL2, पंचांगp);

		पंचांगp = RREG32(CG_FDO_CTRL2) & ~TMIN_MASK;
		पंचांगp |= TMIN(si_pi->t_min);
		WREG32(CG_FDO_CTRL2, पंचांगp);
		si_pi->fan_ctrl_is_in_शेष_mode = true;
	पूर्ण
पूर्ण

अटल व्योम si_thermal_start_smc_fan_control(काष्ठा amdgpu_device *adev)
अणु
	अगर (adev->pm.dpm.fan.ucode_fan_control) अणु
		si_fan_ctrl_start_smc_fan_control(adev);
		si_fan_ctrl_set_अटल_mode(adev, FDO_PWM_MODE_STATIC);
	पूर्ण
पूर्ण

अटल व्योम si_thermal_initialize(काष्ठा amdgpu_device *adev)
अणु
	u32 पंचांगp;

	अगर (adev->pm.fan_pulses_per_revolution) अणु
		पंचांगp = RREG32(CG_TACH_CTRL) & ~EDGE_PER_REV_MASK;
		पंचांगp |= EDGE_PER_REV(adev->pm.fan_pulses_per_revolution -1);
		WREG32(CG_TACH_CTRL, पंचांगp);
	पूर्ण

	पंचांगp = RREG32(CG_FDO_CTRL2) & ~TACH_PWM_RESP_RATE_MASK;
	पंचांगp |= TACH_PWM_RESP_RATE(0x28);
	WREG32(CG_FDO_CTRL2, पंचांगp);
पूर्ण

अटल पूर्णांक si_thermal_start_thermal_controller(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक ret;

	si_thermal_initialize(adev);
	ret = si_thermal_set_temperature_range(adev, R600_TEMP_RANGE_MIN, R600_TEMP_RANGE_MAX);
	अगर (ret)
		वापस ret;
	ret = si_thermal_enable_alert(adev, true);
	अगर (ret)
		वापस ret;
	अगर (adev->pm.dpm.fan.ucode_fan_control) अणु
		ret = si_halt_smc(adev);
		अगर (ret)
			वापस ret;
		ret = si_thermal_setup_fan_table(adev);
		अगर (ret)
			वापस ret;
		ret = si_resume_smc(adev);
		अगर (ret)
			वापस ret;
		si_thermal_start_smc_fan_control(adev);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम si_thermal_stop_thermal_controller(काष्ठा amdgpu_device *adev)
अणु
	अगर (!adev->pm.no_fan) अणु
		si_fan_ctrl_set_शेष_mode(adev);
		si_fan_ctrl_stop_smc_fan_control(adev);
	पूर्ण
पूर्ण

अटल पूर्णांक si_dpm_enable(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(adev);
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(adev);
	काष्ठा si_घातer_info *si_pi = si_get_pi(adev);
	काष्ठा amdgpu_ps *boot_ps = adev->pm.dpm.boot_ps;
	पूर्णांक ret;

	अगर (amdgpu_si_is_smc_running(adev))
		वापस -EINVAL;
	अगर (pi->voltage_control || si_pi->voltage_control_svi2)
		si_enable_voltage_control(adev, true);
	अगर (pi->mvdd_control)
		si_get_mvdd_configuration(adev);
	अगर (pi->voltage_control || si_pi->voltage_control_svi2) अणु
		ret = si_स्थिरruct_voltage_tables(adev);
		अगर (ret) अणु
			DRM_ERROR("si_construct_voltage_tables failed\n");
			वापस ret;
		पूर्ण
	पूर्ण
	अगर (eg_pi->dynamic_ac_timing) अणु
		ret = si_initialize_mc_reg_table(adev);
		अगर (ret)
			eg_pi->dynamic_ac_timing = false;
	पूर्ण
	अगर (pi->dynamic_ss)
		si_enable_spपढ़ो_spectrum(adev, true);
	अगर (pi->thermal_protection)
		si_enable_thermal_protection(adev, true);
	si_setup_bsp(adev);
	si_program_git(adev);
	si_program_tp(adev);
	si_program_tpp(adev);
	si_program_sstp(adev);
	si_enable_display_gap(adev);
	si_program_vc(adev);
	ret = si_upload_firmware(adev);
	अगर (ret) अणु
		DRM_ERROR("si_upload_firmware failed\n");
		वापस ret;
	पूर्ण
	ret = si_process_firmware_header(adev);
	अगर (ret) अणु
		DRM_ERROR("si_process_firmware_header failed\n");
		वापस ret;
	पूर्ण
	ret = si_initial_चयन_from_arb_f0_to_f1(adev);
	अगर (ret) अणु
		DRM_ERROR("si_initial_switch_from_arb_f0_to_f1 failed\n");
		वापस ret;
	पूर्ण
	ret = si_init_smc_table(adev);
	अगर (ret) अणु
		DRM_ERROR("si_init_smc_table failed\n");
		वापस ret;
	पूर्ण
	ret = si_init_smc_spll_table(adev);
	अगर (ret) अणु
		DRM_ERROR("si_init_smc_spll_table failed\n");
		वापस ret;
	पूर्ण
	ret = si_init_arb_table_index(adev);
	अगर (ret) अणु
		DRM_ERROR("si_init_arb_table_index failed\n");
		वापस ret;
	पूर्ण
	अगर (eg_pi->dynamic_ac_timing) अणु
		ret = si_populate_mc_reg_table(adev, boot_ps);
		अगर (ret) अणु
			DRM_ERROR("si_populate_mc_reg_table failed\n");
			वापस ret;
		पूर्ण
	पूर्ण
	ret = si_initialize_smc_cac_tables(adev);
	अगर (ret) अणु
		DRM_ERROR("si_initialize_smc_cac_tables failed\n");
		वापस ret;
	पूर्ण
	ret = si_initialize_hardware_cac_manager(adev);
	अगर (ret) अणु
		DRM_ERROR("si_initialize_hardware_cac_manager failed\n");
		वापस ret;
	पूर्ण
	ret = si_initialize_smc_dte_tables(adev);
	अगर (ret) अणु
		DRM_ERROR("si_initialize_smc_dte_tables failed\n");
		वापस ret;
	पूर्ण
	ret = si_populate_smc_tdp_limits(adev, boot_ps);
	अगर (ret) अणु
		DRM_ERROR("si_populate_smc_tdp_limits failed\n");
		वापस ret;
	पूर्ण
	ret = si_populate_smc_tdp_limits_2(adev, boot_ps);
	अगर (ret) अणु
		DRM_ERROR("si_populate_smc_tdp_limits_2 failed\n");
		वापस ret;
	पूर्ण
	si_program_response_बार(adev);
	si_program_ds_रेजिस्टरs(adev);
	si_dpm_start_smc(adev);
	ret = si_notअगरy_smc_display_change(adev, false);
	अगर (ret) अणु
		DRM_ERROR("si_notify_smc_display_change failed\n");
		वापस ret;
	पूर्ण
	si_enable_sclk_control(adev, true);
	si_start_dpm(adev);

	si_enable_स्वतः_throttle_source(adev, AMDGPU_DPM_AUTO_THROTTLE_SRC_THERMAL, true);
	si_thermal_start_thermal_controller(adev);

	वापस 0;
पूर्ण

अटल पूर्णांक si_set_temperature_range(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक ret;

	ret = si_thermal_enable_alert(adev, false);
	अगर (ret)
		वापस ret;
	ret = si_thermal_set_temperature_range(adev, R600_TEMP_RANGE_MIN, R600_TEMP_RANGE_MAX);
	अगर (ret)
		वापस ret;
	ret = si_thermal_enable_alert(adev, true);
	अगर (ret)
		वापस ret;

	वापस ret;
पूर्ण

अटल व्योम si_dpm_disable(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(adev);
	काष्ठा amdgpu_ps *boot_ps = adev->pm.dpm.boot_ps;

	अगर (!amdgpu_si_is_smc_running(adev))
		वापस;
	si_thermal_stop_thermal_controller(adev);
	si_disable_ulv(adev);
	si_clear_vc(adev);
	अगर (pi->thermal_protection)
		si_enable_thermal_protection(adev, false);
	si_enable_घातer_containment(adev, boot_ps, false);
	si_enable_smc_cac(adev, boot_ps, false);
	si_enable_spपढ़ो_spectrum(adev, false);
	si_enable_स्वतः_throttle_source(adev, AMDGPU_DPM_AUTO_THROTTLE_SRC_THERMAL, false);
	si_stop_dpm(adev);
	si_reset_to_शेष(adev);
	si_dpm_stop_smc(adev);
	si_क्रमce_चयन_to_arb_f0(adev);

	ni_update_current_ps(adev, boot_ps);
पूर्ण

अटल पूर्णांक si_dpm_pre_set_घातer_state(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(adev);
	काष्ठा amdgpu_ps requested_ps = *adev->pm.dpm.requested_ps;
	काष्ठा amdgpu_ps *new_ps = &requested_ps;

	ni_update_requested_ps(adev, new_ps);
	si_apply_state_adjust_rules(adev, &eg_pi->requested_rps);

	वापस 0;
पूर्ण

अटल पूर्णांक si_घातer_control_set_level(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ps *new_ps = adev->pm.dpm.requested_ps;
	पूर्णांक ret;

	ret = si_restrict_perक्रमmance_levels_beक्रमe_चयन(adev);
	अगर (ret)
		वापस ret;
	ret = si_halt_smc(adev);
	अगर (ret)
		वापस ret;
	ret = si_populate_smc_tdp_limits(adev, new_ps);
	अगर (ret)
		वापस ret;
	ret = si_populate_smc_tdp_limits_2(adev, new_ps);
	अगर (ret)
		वापस ret;
	ret = si_resume_smc(adev);
	अगर (ret)
		वापस ret;
	ret = si_set_sw_state(adev);
	अगर (ret)
		वापस ret;
	वापस 0;
पूर्ण

अटल व्योम si_set_vce_घड़ी(काष्ठा amdgpu_device *adev,
			     काष्ठा amdgpu_ps *new_rps,
			     काष्ठा amdgpu_ps *old_rps)
अणु
	अगर ((old_rps->evclk != new_rps->evclk) ||
	    (old_rps->ecclk != new_rps->ecclk)) अणु
		/* Turn the घड़ीs on when encoding, off otherwise */
		अगर (new_rps->evclk || new_rps->ecclk) अणु
			/* Place holder क्रम future VCE1.0 porting to amdgpu
			vce_v1_0_enable_mgcg(adev, false, false);*/
		पूर्ण अन्यथा अणु
			/* Place holder क्रम future VCE1.0 porting to amdgpu
			vce_v1_0_enable_mgcg(adev, true, false);
			amdgpu_asic_set_vce_घड़ीs(adev, new_rps->evclk, new_rps->ecclk);*/
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक si_dpm_set_घातer_state(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(adev);
	काष्ठा amdgpu_ps *new_ps = &eg_pi->requested_rps;
	काष्ठा amdgpu_ps *old_ps = &eg_pi->current_rps;
	पूर्णांक ret;

	ret = si_disable_ulv(adev);
	अगर (ret) अणु
		DRM_ERROR("si_disable_ulv failed\n");
		वापस ret;
	पूर्ण
	ret = si_restrict_perक्रमmance_levels_beक्रमe_चयन(adev);
	अगर (ret) अणु
		DRM_ERROR("si_restrict_performance_levels_before_switch failed\n");
		वापस ret;
	पूर्ण
	अगर (eg_pi->pcie_perक्रमmance_request)
		si_request_link_speed_change_beक्रमe_state_change(adev, new_ps, old_ps);
	ni_set_uvd_घड़ी_beक्रमe_set_eng_घड़ी(adev, new_ps, old_ps);
	ret = si_enable_घातer_containment(adev, new_ps, false);
	अगर (ret) अणु
		DRM_ERROR("si_enable_power_containment failed\n");
		वापस ret;
	पूर्ण
	ret = si_enable_smc_cac(adev, new_ps, false);
	अगर (ret) अणु
		DRM_ERROR("si_enable_smc_cac failed\n");
		वापस ret;
	पूर्ण
	ret = si_halt_smc(adev);
	अगर (ret) अणु
		DRM_ERROR("si_halt_smc failed\n");
		वापस ret;
	पूर्ण
	ret = si_upload_sw_state(adev, new_ps);
	अगर (ret) अणु
		DRM_ERROR("si_upload_sw_state failed\n");
		वापस ret;
	पूर्ण
	ret = si_upload_smc_data(adev);
	अगर (ret) अणु
		DRM_ERROR("si_upload_smc_data failed\n");
		वापस ret;
	पूर्ण
	ret = si_upload_ulv_state(adev);
	अगर (ret) अणु
		DRM_ERROR("si_upload_ulv_state failed\n");
		वापस ret;
	पूर्ण
	अगर (eg_pi->dynamic_ac_timing) अणु
		ret = si_upload_mc_reg_table(adev, new_ps);
		अगर (ret) अणु
			DRM_ERROR("si_upload_mc_reg_table failed\n");
			वापस ret;
		पूर्ण
	पूर्ण
	ret = si_program_memory_timing_parameters(adev, new_ps);
	अगर (ret) अणु
		DRM_ERROR("si_program_memory_timing_parameters failed\n");
		वापस ret;
	पूर्ण
	si_set_pcie_lane_width_in_smc(adev, new_ps, old_ps);

	ret = si_resume_smc(adev);
	अगर (ret) अणु
		DRM_ERROR("si_resume_smc failed\n");
		वापस ret;
	पूर्ण
	ret = si_set_sw_state(adev);
	अगर (ret) अणु
		DRM_ERROR("si_set_sw_state failed\n");
		वापस ret;
	पूर्ण
	ni_set_uvd_घड़ी_after_set_eng_घड़ी(adev, new_ps, old_ps);
	si_set_vce_घड़ी(adev, new_ps, old_ps);
	अगर (eg_pi->pcie_perक्रमmance_request)
		si_notअगरy_link_speed_change_after_state_change(adev, new_ps, old_ps);
	ret = si_set_घातer_state_conditionally_enable_ulv(adev, new_ps);
	अगर (ret) अणु
		DRM_ERROR("si_set_power_state_conditionally_enable_ulv failed\n");
		वापस ret;
	पूर्ण
	ret = si_enable_smc_cac(adev, new_ps, true);
	अगर (ret) अणु
		DRM_ERROR("si_enable_smc_cac failed\n");
		वापस ret;
	पूर्ण
	ret = si_enable_घातer_containment(adev, new_ps, true);
	अगर (ret) अणु
		DRM_ERROR("si_enable_power_containment failed\n");
		वापस ret;
	पूर्ण

	ret = si_घातer_control_set_level(adev);
	अगर (ret) अणु
		DRM_ERROR("si_power_control_set_level failed\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम si_dpm_post_set_घातer_state(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(adev);
	काष्ठा amdgpu_ps *new_ps = &eg_pi->requested_rps;

	ni_update_current_ps(adev, new_ps);
पूर्ण

#अगर 0
व्योम si_dpm_reset_asic(काष्ठा amdgpu_device *adev)
अणु
	si_restrict_perक्रमmance_levels_beक्रमe_चयन(adev);
	si_disable_ulv(adev);
	si_set_boot_state(adev);
पूर्ण
#पूर्ण_अगर

अटल व्योम si_dpm_display_configuration_changed(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	si_program_display_gap(adev);
पूर्ण


अटल व्योम si_parse_pplib_non_घड़ी_info(काष्ठा amdgpu_device *adev,
					  काष्ठा amdgpu_ps *rps,
					  काष्ठा _ATOM_PPLIB_NONCLOCK_INFO *non_घड़ी_info,
					  u8 table_rev)
अणु
	rps->caps = le32_to_cpu(non_घड़ी_info->ulCapsAndSettings);
	rps->class = le16_to_cpu(non_घड़ी_info->usClassअगरication);
	rps->class2 = le16_to_cpu(non_घड़ी_info->usClassअगरication2);

	अगर (ATOM_PPLIB_NONCLOCKINFO_VER1 < table_rev) अणु
		rps->vclk = le32_to_cpu(non_घड़ी_info->ulVCLK);
		rps->dclk = le32_to_cpu(non_घड़ी_info->ulDCLK);
	पूर्ण अन्यथा अगर (r600_is_uvd_state(rps->class, rps->class2)) अणु
		rps->vclk = RV770_DEFAULT_VCLK_FREQ;
		rps->dclk = RV770_DEFAULT_DCLK_FREQ;
	पूर्ण अन्यथा अणु
		rps->vclk = 0;
		rps->dclk = 0;
	पूर्ण

	अगर (rps->class & ATOM_PPLIB_CLASSIFICATION_BOOT)
		adev->pm.dpm.boot_ps = rps;
	अगर (rps->class & ATOM_PPLIB_CLASSIFICATION_UVDSTATE)
		adev->pm.dpm.uvd_ps = rps;
पूर्ण

अटल व्योम si_parse_pplib_घड़ी_info(काष्ठा amdgpu_device *adev,
				      काष्ठा amdgpu_ps *rps, पूर्णांक index,
				      जोड़ pplib_घड़ी_info *घड़ी_info)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(adev);
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(adev);
	काष्ठा si_घातer_info *si_pi = si_get_pi(adev);
	काष्ठा  si_ps *ps = si_get_ps(rps);
	u16 leakage_voltage;
	काष्ठा rv7xx_pl *pl = &ps->perक्रमmance_levels[index];
	पूर्णांक ret;

	ps->perक्रमmance_level_count = index + 1;

	pl->sclk = le16_to_cpu(घड़ी_info->si.usEngineClockLow);
	pl->sclk |= घड़ी_info->si.ucEngineClockHigh << 16;
	pl->mclk = le16_to_cpu(घड़ी_info->si.usMemoryClockLow);
	pl->mclk |= घड़ी_info->si.ucMemoryClockHigh << 16;

	pl->vddc = le16_to_cpu(घड़ी_info->si.usVDDC);
	pl->vddci = le16_to_cpu(घड़ी_info->si.usVDDCI);
	pl->flags = le32_to_cpu(घड़ी_info->si.ulFlags);
	pl->pcie_gen = amdgpu_get_pcie_gen_support(adev,
						   si_pi->sys_pcie_mask,
						   si_pi->boot_pcie_gen,
						   घड़ी_info->si.ucPCIEGen);

	/* patch up vddc अगर necessary */
	ret = si_get_leakage_voltage_from_leakage_index(adev, pl->vddc,
							&leakage_voltage);
	अगर (ret == 0)
		pl->vddc = leakage_voltage;

	अगर (rps->class & ATOM_PPLIB_CLASSIFICATION_ACPI) अणु
		pi->acpi_vddc = pl->vddc;
		eg_pi->acpi_vddci = pl->vddci;
		si_pi->acpi_pcie_gen = pl->pcie_gen;
	पूर्ण

	अगर ((rps->class2 & ATOM_PPLIB_CLASSIFICATION2_ULV) &&
	    index == 0) अणु
		/* XXX disable क्रम A0 tahiti */
		si_pi->ulv.supported = false;
		si_pi->ulv.pl = *pl;
		si_pi->ulv.one_pcie_lane_in_ulv = false;
		si_pi->ulv.volt_change_delay = SISLANDS_ULVVOLTAGECHANGEDELAY_DFLT;
		si_pi->ulv.cg_ulv_parameter = SISLANDS_CGULVPARAMETER_DFLT;
		si_pi->ulv.cg_ulv_control = SISLANDS_CGULVCONTROL_DFLT;
	पूर्ण

	अगर (pi->min_vddc_in_table > pl->vddc)
		pi->min_vddc_in_table = pl->vddc;

	अगर (pi->max_vddc_in_table < pl->vddc)
		pi->max_vddc_in_table = pl->vddc;

	/* patch up boot state */
	अगर (rps->class & ATOM_PPLIB_CLASSIFICATION_BOOT) अणु
		u16 vddc, vddci, mvdd;
		amdgpu_atombios_get_शेष_voltages(adev, &vddc, &vddci, &mvdd);
		pl->mclk = adev->घड़ी.शेष_mclk;
		pl->sclk = adev->घड़ी.शेष_sclk;
		pl->vddc = vddc;
		pl->vddci = vddci;
		si_pi->mvdd_bootup_value = mvdd;
	पूर्ण

	अगर ((rps->class & ATOM_PPLIB_CLASSIFICATION_UI_MASK) ==
	    ATOM_PPLIB_CLASSIFICATION_UI_PERFORMANCE) अणु
		adev->pm.dpm.dyn_state.max_घड़ी_voltage_on_ac.sclk = pl->sclk;
		adev->pm.dpm.dyn_state.max_घड़ी_voltage_on_ac.mclk = pl->mclk;
		adev->pm.dpm.dyn_state.max_घड़ी_voltage_on_ac.vddc = pl->vddc;
		adev->pm.dpm.dyn_state.max_घड़ी_voltage_on_ac.vddci = pl->vddci;
	पूर्ण
पूर्ण

जोड़ pplib_घातer_state अणु
	काष्ठा _ATOM_PPLIB_STATE v1;
	काष्ठा _ATOM_PPLIB_STATE_V2 v2;
पूर्ण;

अटल पूर्णांक si_parse_घातer_table(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_mode_info *mode_info = &adev->mode_info;
	काष्ठा _ATOM_PPLIB_NONCLOCK_INFO *non_घड़ी_info;
	जोड़ pplib_घातer_state *घातer_state;
	पूर्णांक i, j, k, non_घड़ी_array_index, घड़ी_array_index;
	जोड़ pplib_घड़ी_info *घड़ी_info;
	काष्ठा _StateArray *state_array;
	काष्ठा _ClockInfoArray *घड़ी_info_array;
	काष्ठा _NonClockInfoArray *non_घड़ी_info_array;
	जोड़ घातer_info *घातer_info;
	पूर्णांक index = GetIndexIntoMasterTable(DATA, PowerPlayInfo);
	u16 data_offset;
	u8 frev, crev;
	u8 *घातer_state_offset;
	काष्ठा  si_ps *ps;

	अगर (!amdgpu_atom_parse_data_header(mode_info->atom_context, index, शून्य,
				   &frev, &crev, &data_offset))
		वापस -EINVAL;
	घातer_info = (जोड़ घातer_info *)(mode_info->atom_context->bios + data_offset);

	amdgpu_add_thermal_controller(adev);

	state_array = (काष्ठा _StateArray *)
		(mode_info->atom_context->bios + data_offset +
		 le16_to_cpu(घातer_info->pplib.usStateArrayOffset));
	घड़ी_info_array = (काष्ठा _ClockInfoArray *)
		(mode_info->atom_context->bios + data_offset +
		 le16_to_cpu(घातer_info->pplib.usClockInfoArrayOffset));
	non_घड़ी_info_array = (काष्ठा _NonClockInfoArray *)
		(mode_info->atom_context->bios + data_offset +
		 le16_to_cpu(घातer_info->pplib.usNonClockInfoArrayOffset));

	adev->pm.dpm.ps = kसुस्मृति(state_array->ucNumEntries,
				  माप(काष्ठा amdgpu_ps),
				  GFP_KERNEL);
	अगर (!adev->pm.dpm.ps)
		वापस -ENOMEM;
	घातer_state_offset = (u8 *)state_array->states;
	क्रम (i = 0; i < state_array->ucNumEntries; i++) अणु
		u8 *idx;
		घातer_state = (जोड़ pplib_घातer_state *)घातer_state_offset;
		non_घड़ी_array_index = घातer_state->v2.nonClockInfoIndex;
		non_घड़ी_info = (काष्ठा _ATOM_PPLIB_NONCLOCK_INFO *)
			&non_घड़ी_info_array->nonClockInfo[non_घड़ी_array_index];
		ps = kzalloc(माप(काष्ठा  si_ps), GFP_KERNEL);
		अगर (ps == शून्य) अणु
			kमुक्त(adev->pm.dpm.ps);
			वापस -ENOMEM;
		पूर्ण
		adev->pm.dpm.ps[i].ps_priv = ps;
		si_parse_pplib_non_घड़ी_info(adev, &adev->pm.dpm.ps[i],
					      non_घड़ी_info,
					      non_घड़ी_info_array->ucEntrySize);
		k = 0;
		idx = (u8 *)&घातer_state->v2.घड़ीInfoIndex[0];
		क्रम (j = 0; j < घातer_state->v2.ucNumDPMLevels; j++) अणु
			घड़ी_array_index = idx[j];
			अगर (घड़ी_array_index >= घड़ी_info_array->ucNumEntries)
				जारी;
			अगर (k >= SISLANDS_MAX_HARDWARE_POWERLEVELS)
				अवरोध;
			घड़ी_info = (जोड़ pplib_घड़ी_info *)
				((u8 *)&घड़ी_info_array->घड़ीInfo[0] +
				 (घड़ी_array_index * घड़ी_info_array->ucEntrySize));
			si_parse_pplib_घड़ी_info(adev,
						  &adev->pm.dpm.ps[i], k,
						  घड़ी_info);
			k++;
		पूर्ण
		घातer_state_offset += 2 + घातer_state->v2.ucNumDPMLevels;
	पूर्ण
	adev->pm.dpm.num_ps = state_array->ucNumEntries;

	/* fill in the vce घातer states */
	क्रम (i = 0; i < adev->pm.dpm.num_of_vce_states; i++) अणु
		u32 sclk, mclk;
		घड़ी_array_index = adev->pm.dpm.vce_states[i].clk_idx;
		घड़ी_info = (जोड़ pplib_घड़ी_info *)
			&घड़ी_info_array->घड़ीInfo[घड़ी_array_index * घड़ी_info_array->ucEntrySize];
		sclk = le16_to_cpu(घड़ी_info->si.usEngineClockLow);
		sclk |= घड़ी_info->si.ucEngineClockHigh << 16;
		mclk = le16_to_cpu(घड़ी_info->si.usMemoryClockLow);
		mclk |= घड़ी_info->si.ucMemoryClockHigh << 16;
		adev->pm.dpm.vce_states[i].sclk = sclk;
		adev->pm.dpm.vce_states[i].mclk = mclk;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक si_dpm_init(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा rv7xx_घातer_info *pi;
	काष्ठा evergreen_घातer_info *eg_pi;
	काष्ठा ni_घातer_info *ni_pi;
	काष्ठा si_घातer_info *si_pi;
	काष्ठा atom_घड़ी_भागiders भागiders;
	पूर्णांक ret;

	si_pi = kzalloc(माप(काष्ठा si_घातer_info), GFP_KERNEL);
	अगर (si_pi == शून्य)
		वापस -ENOMEM;
	adev->pm.dpm.priv = si_pi;
	ni_pi = &si_pi->ni;
	eg_pi = &ni_pi->eg;
	pi = &eg_pi->rv7xx;

	si_pi->sys_pcie_mask =
		adev->pm.pcie_gen_mask & CAIL_PCIE_LINK_SPEED_SUPPORT_MASK;
	si_pi->क्रमce_pcie_gen = AMDGPU_PCIE_GEN_INVALID;
	si_pi->boot_pcie_gen = si_get_current_pcie_speed(adev);

	si_set_max_cu_value(adev);

	rv770_get_max_vddc(adev);
	si_get_leakage_vddc(adev);
	si_patch_dependency_tables_based_on_leakage(adev);

	pi->acpi_vddc = 0;
	eg_pi->acpi_vddci = 0;
	pi->min_vddc_in_table = 0;
	pi->max_vddc_in_table = 0;

	ret = amdgpu_get_platक्रमm_caps(adev);
	अगर (ret)
		वापस ret;

	ret = amdgpu_parse_extended_घातer_table(adev);
	अगर (ret)
		वापस ret;

	ret = si_parse_घातer_table(adev);
	अगर (ret)
		वापस ret;

	adev->pm.dpm.dyn_state.vddc_dependency_on_dispclk.entries =
		kसुस्मृति(4,
			माप(काष्ठा amdgpu_घड़ी_voltage_dependency_entry),
			GFP_KERNEL);
	अगर (!adev->pm.dpm.dyn_state.vddc_dependency_on_dispclk.entries) अणु
		amdgpu_मुक्त_extended_घातer_table(adev);
		वापस -ENOMEM;
	पूर्ण
	adev->pm.dpm.dyn_state.vddc_dependency_on_dispclk.count = 4;
	adev->pm.dpm.dyn_state.vddc_dependency_on_dispclk.entries[0].clk = 0;
	adev->pm.dpm.dyn_state.vddc_dependency_on_dispclk.entries[0].v = 0;
	adev->pm.dpm.dyn_state.vddc_dependency_on_dispclk.entries[1].clk = 36000;
	adev->pm.dpm.dyn_state.vddc_dependency_on_dispclk.entries[1].v = 720;
	adev->pm.dpm.dyn_state.vddc_dependency_on_dispclk.entries[2].clk = 54000;
	adev->pm.dpm.dyn_state.vddc_dependency_on_dispclk.entries[2].v = 810;
	adev->pm.dpm.dyn_state.vddc_dependency_on_dispclk.entries[3].clk = 72000;
	adev->pm.dpm.dyn_state.vddc_dependency_on_dispclk.entries[3].v = 900;

	अगर (adev->pm.dpm.voltage_response_समय == 0)
		adev->pm.dpm.voltage_response_समय = R600_VOLTAGERESPONSETIME_DFLT;
	अगर (adev->pm.dpm.backbias_response_समय == 0)
		adev->pm.dpm.backbias_response_समय = R600_BACKBIASRESPONSETIME_DFLT;

	ret = amdgpu_atombios_get_घड़ी_भागiders(adev, COMPUTE_ENGINE_PLL_PARAM,
					     0, false, &भागiders);
	अगर (ret)
		pi->ref_भाग = भागiders.ref_भाग + 1;
	अन्यथा
		pi->ref_भाग = R600_REFERENCEDIVIDER_DFLT;

	eg_pi->smu_uvd_hs = false;

	pi->mclk_strobe_mode_threshold = 40000;
	अगर (si_is_special_1gb_platक्रमm(adev))
		pi->mclk_stutter_mode_threshold = 0;
	अन्यथा
		pi->mclk_stutter_mode_threshold = pi->mclk_strobe_mode_threshold;
	pi->mclk_edc_enable_threshold = 40000;
	eg_pi->mclk_edc_wr_enable_threshold = 40000;

	ni_pi->mclk_rtt_mode_threshold = eg_pi->mclk_edc_wr_enable_threshold;

	pi->voltage_control =
		amdgpu_atombios_is_voltage_gpio(adev, SET_VOLTAGE_TYPE_ASIC_VDDC,
					    VOLTAGE_OBJ_GPIO_LUT);
	अगर (!pi->voltage_control) अणु
		si_pi->voltage_control_svi2 =
			amdgpu_atombios_is_voltage_gpio(adev, SET_VOLTAGE_TYPE_ASIC_VDDC,
						    VOLTAGE_OBJ_SVID2);
		अगर (si_pi->voltage_control_svi2)
			amdgpu_atombios_get_svi2_info(adev, SET_VOLTAGE_TYPE_ASIC_VDDC,
						  &si_pi->svd_gpio_id, &si_pi->svc_gpio_id);
	पूर्ण

	pi->mvdd_control =
		amdgpu_atombios_is_voltage_gpio(adev, SET_VOLTAGE_TYPE_ASIC_MVDDC,
					    VOLTAGE_OBJ_GPIO_LUT);

	eg_pi->vddci_control =
		amdgpu_atombios_is_voltage_gpio(adev, SET_VOLTAGE_TYPE_ASIC_VDDCI,
					    VOLTAGE_OBJ_GPIO_LUT);
	अगर (!eg_pi->vddci_control)
		si_pi->vddci_control_svi2 =
			amdgpu_atombios_is_voltage_gpio(adev, SET_VOLTAGE_TYPE_ASIC_VDDCI,
						    VOLTAGE_OBJ_SVID2);

	si_pi->vddc_phase_shed_control =
		amdgpu_atombios_is_voltage_gpio(adev, SET_VOLTAGE_TYPE_ASIC_VDDC,
					    VOLTAGE_OBJ_PHASE_LUT);

	rv770_get_engine_memory_ss(adev);

	pi->asi = RV770_ASI_DFLT;
	pi->pasi = CYPRESS_HASI_DFLT;
	pi->vrc = SISLANDS_VRC_DFLT;

	pi->gfx_घड़ी_gating = true;

	eg_pi->sclk_deep_sleep = true;
	si_pi->sclk_deep_sleep_above_low = false;

	अगर (adev->pm.पूर्णांक_thermal_type != THERMAL_TYPE_NONE)
		pi->thermal_protection = true;
	अन्यथा
		pi->thermal_protection = false;

	eg_pi->dynamic_ac_timing = true;

	eg_pi->light_sleep = true;
#अगर defined(CONFIG_ACPI)
	eg_pi->pcie_perक्रमmance_request =
		amdgpu_acpi_is_pcie_perक्रमmance_request_supported(adev);
#अन्यथा
	eg_pi->pcie_perक्रमmance_request = false;
#पूर्ण_अगर

	si_pi->sram_end = SMC_RAM_END;

	adev->pm.dpm.dyn_state.mclk_sclk_ratio = 4;
	adev->pm.dpm.dyn_state.sclk_mclk_delta = 15000;
	adev->pm.dpm.dyn_state.vddc_vddci_delta = 200;
	adev->pm.dpm.dyn_state.valid_sclk_values.count = 0;
	adev->pm.dpm.dyn_state.valid_sclk_values.values = शून्य;
	adev->pm.dpm.dyn_state.valid_mclk_values.count = 0;
	adev->pm.dpm.dyn_state.valid_mclk_values.values = शून्य;

	si_initialize_घातertune_शेषs(adev);

	/* make sure dc limits are valid */
	अगर ((adev->pm.dpm.dyn_state.max_घड़ी_voltage_on_dc.sclk == 0) ||
	    (adev->pm.dpm.dyn_state.max_घड़ी_voltage_on_dc.mclk == 0))
		adev->pm.dpm.dyn_state.max_घड़ी_voltage_on_dc =
			adev->pm.dpm.dyn_state.max_घड़ी_voltage_on_ac;

	si_pi->fan_ctrl_is_in_शेष_mode = true;

	वापस 0;
पूर्ण

अटल व्योम si_dpm_fini(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i;

	अगर (adev->pm.dpm.ps)
		क्रम (i = 0; i < adev->pm.dpm.num_ps; i++)
			kमुक्त(adev->pm.dpm.ps[i].ps_priv);
	kमुक्त(adev->pm.dpm.ps);
	kमुक्त(adev->pm.dpm.priv);
	kमुक्त(adev->pm.dpm.dyn_state.vddc_dependency_on_dispclk.entries);
	amdgpu_मुक्त_extended_घातer_table(adev);
पूर्ण

अटल व्योम si_dpm_debugfs_prपूर्णांक_current_perक्रमmance_level(व्योम *handle,
						    काष्ठा seq_file *m)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(adev);
	काष्ठा amdgpu_ps *rps = &eg_pi->current_rps;
	काष्ठा  si_ps *ps = si_get_ps(rps);
	काष्ठा rv7xx_pl *pl;
	u32 current_index =
		(RREG32(TARGET_AND_CURRENT_PROखाता_INDEX) & CURRENT_STATE_INDEX_MASK) >>
		CURRENT_STATE_INDEX_SHIFT;

	अगर (current_index >= ps->perक्रमmance_level_count) अणु
		seq_म_लिखो(m, "invalid dpm profile %d\n", current_index);
	पूर्ण अन्यथा अणु
		pl = &ps->perक्रमmance_levels[current_index];
		seq_म_लिखो(m, "uvd    vclk: %d dclk: %d\n", rps->vclk, rps->dclk);
		seq_म_लिखो(m, "power level %d    sclk: %u mclk: %u vddc: %u vddci: %u pcie gen: %u\n",
			   current_index, pl->sclk, pl->mclk, pl->vddc, pl->vddci, pl->pcie_gen + 1);
	पूर्ण
पूर्ण

अटल पूर्णांक si_dpm_set_पूर्णांकerrupt_state(काष्ठा amdgpu_device *adev,
				      काष्ठा amdgpu_irq_src *source,
				      अचिन्हित type,
				      क्रमागत amdgpu_पूर्णांकerrupt_state state)
अणु
	u32 cg_thermal_पूर्णांक;

	चयन (type) अणु
	हाल AMDGPU_THERMAL_IRQ_LOW_TO_HIGH:
		चयन (state) अणु
		हाल AMDGPU_IRQ_STATE_DISABLE:
			cg_thermal_पूर्णांक = RREG32_SMC(CG_THERMAL_INT);
			cg_thermal_पूर्णांक |= THERM_INT_MASK_HIGH;
			WREG32_SMC(CG_THERMAL_INT, cg_thermal_पूर्णांक);
			अवरोध;
		हाल AMDGPU_IRQ_STATE_ENABLE:
			cg_thermal_पूर्णांक = RREG32_SMC(CG_THERMAL_INT);
			cg_thermal_पूर्णांक &= ~THERM_INT_MASK_HIGH;
			WREG32_SMC(CG_THERMAL_INT, cg_thermal_पूर्णांक);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;

	हाल AMDGPU_THERMAL_IRQ_HIGH_TO_LOW:
		चयन (state) अणु
		हाल AMDGPU_IRQ_STATE_DISABLE:
			cg_thermal_पूर्णांक = RREG32_SMC(CG_THERMAL_INT);
			cg_thermal_पूर्णांक |= THERM_INT_MASK_LOW;
			WREG32_SMC(CG_THERMAL_INT, cg_thermal_पूर्णांक);
			अवरोध;
		हाल AMDGPU_IRQ_STATE_ENABLE:
			cg_thermal_पूर्णांक = RREG32_SMC(CG_THERMAL_INT);
			cg_thermal_पूर्णांक &= ~THERM_INT_MASK_LOW;
			WREG32_SMC(CG_THERMAL_INT, cg_thermal_पूर्णांक);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक si_dpm_process_पूर्णांकerrupt(काष्ठा amdgpu_device *adev,
				    काष्ठा amdgpu_irq_src *source,
				    काष्ठा amdgpu_iv_entry *entry)
अणु
	bool queue_thermal = false;

	अगर (entry == शून्य)
		वापस -EINVAL;

	चयन (entry->src_id) अणु
	हाल 230: /* thermal low to high */
		DRM_DEBUG("IH: thermal low to high\n");
		adev->pm.dpm.thermal.high_to_low = false;
		queue_thermal = true;
		अवरोध;
	हाल 231: /* thermal high to low */
		DRM_DEBUG("IH: thermal high to low\n");
		adev->pm.dpm.thermal.high_to_low = true;
		queue_thermal = true;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (queue_thermal)
		schedule_work(&adev->pm.dpm.thermal.work);

	वापस 0;
पूर्ण

अटल पूर्णांक si_dpm_late_init(व्योम *handle)
अणु
	पूर्णांक ret;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (!adev->pm.dpm_enabled)
		वापस 0;

	ret = si_set_temperature_range(adev);
	अगर (ret)
		वापस ret;
#अगर 0 //TODO ?
	si_dpm_घातergate_uvd(adev, true);
#पूर्ण_अगर
	वापस 0;
पूर्ण

/**
 * si_dpm_init_microcode - load ucode images from disk
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Use the firmware पूर्णांकerface to load the ucode images पूर्णांकo
 * the driver (not loaded पूर्णांकo hw).
 * Returns 0 on success, error on failure.
 */
अटल पूर्णांक si_dpm_init_microcode(काष्ठा amdgpu_device *adev)
अणु
	स्थिर अक्षर *chip_name;
	अक्षर fw_name[30];
	पूर्णांक err;

	DRM_DEBUG("\n");
	चयन (adev->asic_type) अणु
	हाल CHIP_TAHITI:
		chip_name = "tahiti";
		अवरोध;
	हाल CHIP_PITCAIRN:
		अगर ((adev->pdev->revision == 0x81) &&
		    ((adev->pdev->device == 0x6810) ||
		    (adev->pdev->device == 0x6811)))
			chip_name = "pitcairn_k";
		अन्यथा
			chip_name = "pitcairn";
		अवरोध;
	हाल CHIP_VERDE:
		अगर (((adev->pdev->device == 0x6820) &&
			((adev->pdev->revision == 0x81) ||
			(adev->pdev->revision == 0x83))) ||
		    ((adev->pdev->device == 0x6821) &&
			((adev->pdev->revision == 0x83) ||
			(adev->pdev->revision == 0x87))) ||
		    ((adev->pdev->revision == 0x87) &&
			((adev->pdev->device == 0x6823) ||
			(adev->pdev->device == 0x682b))))
			chip_name = "verde_k";
		अन्यथा
			chip_name = "verde";
		अवरोध;
	हाल CHIP_OLAND:
		अगर (((adev->pdev->revision == 0x81) &&
			((adev->pdev->device == 0x6600) ||
			(adev->pdev->device == 0x6604) ||
			(adev->pdev->device == 0x6605) ||
			(adev->pdev->device == 0x6610))) ||
		    ((adev->pdev->revision == 0x83) &&
			(adev->pdev->device == 0x6610)))
			chip_name = "oland_k";
		अन्यथा
			chip_name = "oland";
		अवरोध;
	हाल CHIP_HAIन_अंक:
		अगर (((adev->pdev->revision == 0x81) &&
			(adev->pdev->device == 0x6660)) ||
		    ((adev->pdev->revision == 0x83) &&
			((adev->pdev->device == 0x6660) ||
			(adev->pdev->device == 0x6663) ||
			(adev->pdev->device == 0x6665) ||
			 (adev->pdev->device == 0x6667))))
			chip_name = "hainan_k";
		अन्यथा अगर ((adev->pdev->revision == 0xc3) &&
			 (adev->pdev->device == 0x6665))
			chip_name = "banks_k_2";
		अन्यथा
			chip_name = "hainan";
		अवरोध;
	शेष: BUG();
	पूर्ण

	snम_लिखो(fw_name, माप(fw_name), "amdgpu/%s_smc.bin", chip_name);
	err = request_firmware(&adev->pm.fw, fw_name, adev->dev);
	अगर (err)
		जाओ out;
	err = amdgpu_ucode_validate(adev->pm.fw);

out:
	अगर (err) अणु
		DRM_ERROR("si_smc: Failed to load firmware. err = %d\"%s\"\n",
			  err, fw_name);
		release_firmware(adev->pm.fw);
		adev->pm.fw = शून्य;
	पूर्ण
	वापस err;

पूर्ण

अटल पूर्णांक si_dpm_sw_init(व्योम *handle)
अणु
	पूर्णांक ret;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	ret = amdgpu_irq_add_id(adev, AMDGPU_IRQ_CLIENTID_LEGACY, 230, &adev->pm.dpm.thermal.irq);
	अगर (ret)
		वापस ret;

	ret = amdgpu_irq_add_id(adev, AMDGPU_IRQ_CLIENTID_LEGACY, 231, &adev->pm.dpm.thermal.irq);
	अगर (ret)
		वापस ret;

	/* शेष to balanced state */
	adev->pm.dpm.state = POWER_STATE_TYPE_BALANCED;
	adev->pm.dpm.user_state = POWER_STATE_TYPE_BALANCED;
	adev->pm.dpm.क्रमced_level = AMD_DPM_FORCED_LEVEL_AUTO;
	adev->pm.शेष_sclk = adev->घड़ी.शेष_sclk;
	adev->pm.शेष_mclk = adev->घड़ी.शेष_mclk;
	adev->pm.current_sclk = adev->घड़ी.शेष_sclk;
	adev->pm.current_mclk = adev->घड़ी.शेष_mclk;
	adev->pm.पूर्णांक_thermal_type = THERMAL_TYPE_NONE;

	अगर (amdgpu_dpm == 0)
		वापस 0;

	ret = si_dpm_init_microcode(adev);
	अगर (ret)
		वापस ret;

	INIT_WORK(&adev->pm.dpm.thermal.work, amdgpu_dpm_thermal_work_handler);
	mutex_lock(&adev->pm.mutex);
	ret = si_dpm_init(adev);
	अगर (ret)
		जाओ dpm_failed;
	adev->pm.dpm.current_ps = adev->pm.dpm.requested_ps = adev->pm.dpm.boot_ps;
	अगर (amdgpu_dpm == 1)
		amdgpu_pm_prपूर्णांक_घातer_states(adev);
	mutex_unlock(&adev->pm.mutex);
	DRM_INFO("amdgpu: dpm initialized\n");

	वापस 0;

dpm_failed:
	si_dpm_fini(adev);
	mutex_unlock(&adev->pm.mutex);
	DRM_ERROR("amdgpu: dpm initialization failed\n");
	वापस ret;
पूर्ण

अटल पूर्णांक si_dpm_sw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	flush_work(&adev->pm.dpm.thermal.work);

	mutex_lock(&adev->pm.mutex);
	si_dpm_fini(adev);
	mutex_unlock(&adev->pm.mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक si_dpm_hw_init(व्योम *handle)
अणु
	पूर्णांक ret;

	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (!amdgpu_dpm)
		वापस 0;

	mutex_lock(&adev->pm.mutex);
	si_dpm_setup_asic(adev);
	ret = si_dpm_enable(adev);
	अगर (ret)
		adev->pm.dpm_enabled = false;
	अन्यथा
		adev->pm.dpm_enabled = true;
	mutex_unlock(&adev->pm.mutex);
	amdgpu_pm_compute_घड़ीs(adev);
	वापस ret;
पूर्ण

अटल पूर्णांक si_dpm_hw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (adev->pm.dpm_enabled) अणु
		mutex_lock(&adev->pm.mutex);
		si_dpm_disable(adev);
		mutex_unlock(&adev->pm.mutex);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक si_dpm_suspend(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (adev->pm.dpm_enabled) अणु
		mutex_lock(&adev->pm.mutex);
		/* disable dpm */
		si_dpm_disable(adev);
		/* reset the घातer state */
		adev->pm.dpm.current_ps = adev->pm.dpm.requested_ps = adev->pm.dpm.boot_ps;
		mutex_unlock(&adev->pm.mutex);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक si_dpm_resume(व्योम *handle)
अणु
	पूर्णांक ret;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (adev->pm.dpm_enabled) अणु
		/* asic init will reset to the boot state */
		mutex_lock(&adev->pm.mutex);
		si_dpm_setup_asic(adev);
		ret = si_dpm_enable(adev);
		अगर (ret)
			adev->pm.dpm_enabled = false;
		अन्यथा
			adev->pm.dpm_enabled = true;
		mutex_unlock(&adev->pm.mutex);
		अगर (adev->pm.dpm_enabled)
			amdgpu_pm_compute_घड़ीs(adev);
	पूर्ण
	वापस 0;
पूर्ण

अटल bool si_dpm_is_idle(व्योम *handle)
अणु
	/* XXX */
	वापस true;
पूर्ण

अटल पूर्णांक si_dpm_रुको_क्रम_idle(व्योम *handle)
अणु
	/* XXX */
	वापस 0;
पूर्ण

अटल पूर्णांक si_dpm_soft_reset(व्योम *handle)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक si_dpm_set_घड़ीgating_state(व्योम *handle,
					क्रमागत amd_घड़ीgating_state state)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक si_dpm_set_घातergating_state(व्योम *handle,
					क्रमागत amd_घातergating_state state)
अणु
	वापस 0;
पूर्ण

/* get temperature in millidegrees */
अटल पूर्णांक si_dpm_get_temp(व्योम *handle)
अणु
	u32 temp;
	पूर्णांक actual_temp = 0;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	temp = (RREG32(CG_MULT_THERMAL_STATUS) & CTF_TEMP_MASK) >>
		CTF_TEMP_SHIFT;

	अगर (temp & 0x200)
		actual_temp = 255;
	अन्यथा
		actual_temp = temp & 0x1ff;

	actual_temp = (actual_temp * 1000);

	वापस actual_temp;
पूर्ण

अटल u32 si_dpm_get_sclk(व्योम *handle, bool low)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(adev);
	काष्ठा  si_ps *requested_state = si_get_ps(&eg_pi->requested_rps);

	अगर (low)
		वापस requested_state->perक्रमmance_levels[0].sclk;
	अन्यथा
		वापस requested_state->perक्रमmance_levels[requested_state->perक्रमmance_level_count - 1].sclk;
पूर्ण

अटल u32 si_dpm_get_mclk(व्योम *handle, bool low)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(adev);
	काष्ठा  si_ps *requested_state = si_get_ps(&eg_pi->requested_rps);

	अगर (low)
		वापस requested_state->perक्रमmance_levels[0].mclk;
	अन्यथा
		वापस requested_state->perक्रमmance_levels[requested_state->perक्रमmance_level_count - 1].mclk;
पूर्ण

अटल व्योम si_dpm_prपूर्णांक_घातer_state(व्योम *handle,
				     व्योम *current_ps)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	काष्ठा amdgpu_ps *rps = (काष्ठा amdgpu_ps *)current_ps;
	काष्ठा  si_ps *ps = si_get_ps(rps);
	काष्ठा rv7xx_pl *pl;
	पूर्णांक i;

	amdgpu_dpm_prपूर्णांक_class_info(rps->class, rps->class2);
	amdgpu_dpm_prपूर्णांक_cap_info(rps->caps);
	DRM_INFO("\tuvd    vclk: %d dclk: %d\n", rps->vclk, rps->dclk);
	क्रम (i = 0; i < ps->perक्रमmance_level_count; i++) अणु
		pl = &ps->perक्रमmance_levels[i];
		अगर (adev->asic_type >= CHIP_TAHITI)
			DRM_INFO("\t\tpower level %d    sclk: %u mclk: %u vddc: %u vddci: %u pcie gen: %u\n",
				 i, pl->sclk, pl->mclk, pl->vddc, pl->vddci, pl->pcie_gen + 1);
		अन्यथा
			DRM_INFO("\t\tpower level %d    sclk: %u mclk: %u vddc: %u vddci: %u\n",
				 i, pl->sclk, pl->mclk, pl->vddc, pl->vddci);
	पूर्ण
	amdgpu_dpm_prपूर्णांक_ps_status(adev, rps);
पूर्ण

अटल पूर्णांक si_dpm_early_init(व्योम *handle)
अणु

	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	adev->घातerplay.pp_funcs = &si_dpm_funcs;
	adev->घातerplay.pp_handle = adev;
	si_dpm_set_irq_funcs(adev);
	वापस 0;
पूर्ण

अटल अंतरभूत bool si_are_घातer_levels_equal(स्थिर काष्ठा rv7xx_pl  *si_cpl1,
						स्थिर काष्ठा rv7xx_pl *si_cpl2)
अणु
	वापस ((si_cpl1->mclk == si_cpl2->mclk) &&
		  (si_cpl1->sclk == si_cpl2->sclk) &&
		  (si_cpl1->pcie_gen == si_cpl2->pcie_gen) &&
		  (si_cpl1->vddc == si_cpl2->vddc) &&
		  (si_cpl1->vddci == si_cpl2->vddci));
पूर्ण

अटल पूर्णांक si_check_state_equal(व्योम *handle,
				व्योम *current_ps,
				व्योम *request_ps,
				bool *equal)
अणु
	काष्ठा si_ps *si_cps;
	काष्ठा si_ps *si_rps;
	पूर्णांक i;
	काष्ठा amdgpu_ps *cps = (काष्ठा amdgpu_ps *)current_ps;
	काष्ठा amdgpu_ps *rps = (काष्ठा amdgpu_ps *)request_ps;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (adev == शून्य || cps == शून्य || rps == शून्य || equal == शून्य)
		वापस -EINVAL;

	si_cps = si_get_ps((काष्ठा amdgpu_ps *)cps);
	si_rps = si_get_ps((काष्ठा amdgpu_ps *)rps);

	अगर (si_cps == शून्य) अणु
		prपूर्णांकk("si_cps is NULL\n");
		*equal = false;
		वापस 0;
	पूर्ण

	अगर (si_cps->perक्रमmance_level_count != si_rps->perक्रमmance_level_count) अणु
		*equal = false;
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < si_cps->perक्रमmance_level_count; i++) अणु
		अगर (!si_are_घातer_levels_equal(&(si_cps->perक्रमmance_levels[i]),
					&(si_rps->perक्रमmance_levels[i]))) अणु
			*equal = false;
			वापस 0;
		पूर्ण
	पूर्ण

	/* If all perक्रमmance levels are the same try to use the UVD घड़ीs to अवरोध the tie.*/
	*equal = ((cps->vclk == rps->vclk) && (cps->dclk == rps->dclk));
	*equal &= ((cps->evclk == rps->evclk) && (cps->ecclk == rps->ecclk));

	वापस 0;
पूर्ण

अटल पूर्णांक si_dpm_पढ़ो_sensor(व्योम *handle, पूर्णांक idx,
			      व्योम *value, पूर्णांक *size)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(adev);
	काष्ठा amdgpu_ps *rps = &eg_pi->current_rps;
	काष्ठा  si_ps *ps = si_get_ps(rps);
	uपूर्णांक32_t sclk, mclk;
	u32 pl_index =
		(RREG32(TARGET_AND_CURRENT_PROखाता_INDEX) & CURRENT_STATE_INDEX_MASK) >>
		CURRENT_STATE_INDEX_SHIFT;

	/* size must be at least 4 bytes क्रम all sensors */
	अगर (*size < 4)
		वापस -EINVAL;

	चयन (idx) अणु
	हाल AMDGPU_PP_SENSOR_GFX_SCLK:
		अगर (pl_index < ps->perक्रमmance_level_count) अणु
			sclk = ps->perक्रमmance_levels[pl_index].sclk;
			*((uपूर्णांक32_t *)value) = sclk;
			*size = 4;
			वापस 0;
		पूर्ण
		वापस -EINVAL;
	हाल AMDGPU_PP_SENSOR_GFX_MCLK:
		अगर (pl_index < ps->perक्रमmance_level_count) अणु
			mclk = ps->perक्रमmance_levels[pl_index].mclk;
			*((uपूर्णांक32_t *)value) = mclk;
			*size = 4;
			वापस 0;
		पूर्ण
		वापस -EINVAL;
	हाल AMDGPU_PP_SENSOR_GPU_TEMP:
		*((uपूर्णांक32_t *)value) = si_dpm_get_temp(adev);
		*size = 4;
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा amd_ip_funcs si_dpm_ip_funcs = अणु
	.name = "si_dpm",
	.early_init = si_dpm_early_init,
	.late_init = si_dpm_late_init,
	.sw_init = si_dpm_sw_init,
	.sw_fini = si_dpm_sw_fini,
	.hw_init = si_dpm_hw_init,
	.hw_fini = si_dpm_hw_fini,
	.suspend = si_dpm_suspend,
	.resume = si_dpm_resume,
	.is_idle = si_dpm_is_idle,
	.रुको_क्रम_idle = si_dpm_रुको_क्रम_idle,
	.soft_reset = si_dpm_soft_reset,
	.set_घड़ीgating_state = si_dpm_set_घड़ीgating_state,
	.set_घातergating_state = si_dpm_set_घातergating_state,
पूर्ण;

स्थिर काष्ठा amdgpu_ip_block_version si_smu_ip_block =
अणु
	.type = AMD_IP_BLOCK_TYPE_SMC,
	.major = 6,
	.minor = 0,
	.rev = 0,
	.funcs = &si_dpm_ip_funcs,
पूर्ण;

अटल स्थिर काष्ठा amd_pm_funcs si_dpm_funcs = अणु
	.pre_set_घातer_state = &si_dpm_pre_set_घातer_state,
	.set_घातer_state = &si_dpm_set_घातer_state,
	.post_set_घातer_state = &si_dpm_post_set_घातer_state,
	.display_configuration_changed = &si_dpm_display_configuration_changed,
	.get_sclk = &si_dpm_get_sclk,
	.get_mclk = &si_dpm_get_mclk,
	.prपूर्णांक_घातer_state = &si_dpm_prपूर्णांक_घातer_state,
	.debugfs_prपूर्णांक_current_perक्रमmance_level = &si_dpm_debugfs_prपूर्णांक_current_perक्रमmance_level,
	.क्रमce_perक्रमmance_level = &si_dpm_क्रमce_perक्रमmance_level,
	.vblank_too_लघु = &si_dpm_vblank_too_लघु,
	.set_fan_control_mode = &si_dpm_set_fan_control_mode,
	.get_fan_control_mode = &si_dpm_get_fan_control_mode,
	.set_fan_speed_percent = &si_dpm_set_fan_speed_percent,
	.get_fan_speed_percent = &si_dpm_get_fan_speed_percent,
	.check_state_equal = &si_check_state_equal,
	.get_vce_घड़ी_state = amdgpu_get_vce_घड़ी_state,
	.पढ़ो_sensor = &si_dpm_पढ़ो_sensor,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_irq_src_funcs si_dpm_irq_funcs = अणु
	.set = si_dpm_set_पूर्णांकerrupt_state,
	.process = si_dpm_process_पूर्णांकerrupt,
पूर्ण;

अटल व्योम si_dpm_set_irq_funcs(काष्ठा amdgpu_device *adev)
अणु
	adev->pm.dpm.thermal.irq.num_types = AMDGPU_THERMAL_IRQ_LAST;
	adev->pm.dpm.thermal.irq.funcs = &si_dpm_irq_funcs;
पूर्ण

