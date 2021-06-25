<शैली गुरु>
/*
 * Copyright 2011 Advanced Micro Devices, Inc.
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
 * Authors: Alex Deucher
 */

#समावेश <linux/firmware.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>

#समावेश <drm/drm_vblank.h>
#समावेश <drm/radeon_drm.h>

#समावेश "atom.h"
#समावेश "clearstate_si.h"
#समावेश "evergreen.h"
#समावेश "r600.h"
#समावेश "radeon.h"
#समावेश "radeon_asic.h"
#समावेश "radeon_audio.h"
#समावेश "radeon_ucode.h"
#समावेश "si_blit_shaders.h"
#समावेश "si.h"
#समावेश "sid.h"


MODULE_FIRMWARE("radeon/TAHITI_pfp.bin");
MODULE_FIRMWARE("radeon/TAHITI_me.bin");
MODULE_FIRMWARE("radeon/TAHITI_ce.bin");
MODULE_FIRMWARE("radeon/TAHITI_mc.bin");
MODULE_FIRMWARE("radeon/TAHITI_mc2.bin");
MODULE_FIRMWARE("radeon/TAHITI_rlc.bin");
MODULE_FIRMWARE("radeon/TAHITI_smc.bin");

MODULE_FIRMWARE("radeon/tahiti_pfp.bin");
MODULE_FIRMWARE("radeon/tahiti_me.bin");
MODULE_FIRMWARE("radeon/tahiti_ce.bin");
MODULE_FIRMWARE("radeon/tahiti_mc.bin");
MODULE_FIRMWARE("radeon/tahiti_rlc.bin");
MODULE_FIRMWARE("radeon/tahiti_smc.bin");

MODULE_FIRMWARE("radeon/PITCAIRN_pfp.bin");
MODULE_FIRMWARE("radeon/PITCAIRN_me.bin");
MODULE_FIRMWARE("radeon/PITCAIRN_ce.bin");
MODULE_FIRMWARE("radeon/PITCAIRN_mc.bin");
MODULE_FIRMWARE("radeon/PITCAIRN_mc2.bin");
MODULE_FIRMWARE("radeon/PITCAIRN_rlc.bin");
MODULE_FIRMWARE("radeon/PITCAIRN_smc.bin");

MODULE_FIRMWARE("radeon/pitcairn_pfp.bin");
MODULE_FIRMWARE("radeon/pitcairn_me.bin");
MODULE_FIRMWARE("radeon/pitcairn_ce.bin");
MODULE_FIRMWARE("radeon/pitcairn_mc.bin");
MODULE_FIRMWARE("radeon/pitcairn_rlc.bin");
MODULE_FIRMWARE("radeon/pitcairn_smc.bin");
MODULE_FIRMWARE("radeon/pitcairn_k_smc.bin");

MODULE_FIRMWARE("radeon/VERDE_pfp.bin");
MODULE_FIRMWARE("radeon/VERDE_me.bin");
MODULE_FIRMWARE("radeon/VERDE_ce.bin");
MODULE_FIRMWARE("radeon/VERDE_mc.bin");
MODULE_FIRMWARE("radeon/VERDE_mc2.bin");
MODULE_FIRMWARE("radeon/VERDE_rlc.bin");
MODULE_FIRMWARE("radeon/VERDE_smc.bin");

MODULE_FIRMWARE("radeon/verde_pfp.bin");
MODULE_FIRMWARE("radeon/verde_me.bin");
MODULE_FIRMWARE("radeon/verde_ce.bin");
MODULE_FIRMWARE("radeon/verde_mc.bin");
MODULE_FIRMWARE("radeon/verde_rlc.bin");
MODULE_FIRMWARE("radeon/verde_smc.bin");
MODULE_FIRMWARE("radeon/verde_k_smc.bin");

MODULE_FIRMWARE("radeon/OLAND_pfp.bin");
MODULE_FIRMWARE("radeon/OLAND_me.bin");
MODULE_FIRMWARE("radeon/OLAND_ce.bin");
MODULE_FIRMWARE("radeon/OLAND_mc.bin");
MODULE_FIRMWARE("radeon/OLAND_mc2.bin");
MODULE_FIRMWARE("radeon/OLAND_rlc.bin");
MODULE_FIRMWARE("radeon/OLAND_smc.bin");

MODULE_FIRMWARE("radeon/oland_pfp.bin");
MODULE_FIRMWARE("radeon/oland_me.bin");
MODULE_FIRMWARE("radeon/oland_ce.bin");
MODULE_FIRMWARE("radeon/oland_mc.bin");
MODULE_FIRMWARE("radeon/oland_rlc.bin");
MODULE_FIRMWARE("radeon/oland_smc.bin");
MODULE_FIRMWARE("radeon/oland_k_smc.bin");

MODULE_FIRMWARE("radeon/HAINAN_pfp.bin");
MODULE_FIRMWARE("radeon/HAINAN_me.bin");
MODULE_FIRMWARE("radeon/HAINAN_ce.bin");
MODULE_FIRMWARE("radeon/HAINAN_mc.bin");
MODULE_FIRMWARE("radeon/HAINAN_mc2.bin");
MODULE_FIRMWARE("radeon/HAINAN_rlc.bin");
MODULE_FIRMWARE("radeon/HAINAN_smc.bin");

MODULE_FIRMWARE("radeon/hainan_pfp.bin");
MODULE_FIRMWARE("radeon/hainan_me.bin");
MODULE_FIRMWARE("radeon/hainan_ce.bin");
MODULE_FIRMWARE("radeon/hainan_mc.bin");
MODULE_FIRMWARE("radeon/hainan_rlc.bin");
MODULE_FIRMWARE("radeon/hainan_smc.bin");
MODULE_FIRMWARE("radeon/hainan_k_smc.bin");
MODULE_FIRMWARE("radeon/banks_k_2_smc.bin");

MODULE_FIRMWARE("radeon/si58_mc.bin");

अटल u32 si_get_cu_active_biपंचांगap(काष्ठा radeon_device *rdev, u32 se, u32 sh);
अटल व्योम si_pcie_gen3_enable(काष्ठा radeon_device *rdev);
अटल व्योम si_program_aspm(काष्ठा radeon_device *rdev);
बाह्य व्योम sumo_rlc_fini(काष्ठा radeon_device *rdev);
बाह्य पूर्णांक sumo_rlc_init(काष्ठा radeon_device *rdev);
अटल व्योम si_enable_gui_idle_पूर्णांकerrupt(काष्ठा radeon_device *rdev,
					 bool enable);
अटल व्योम si_init_pg(काष्ठा radeon_device *rdev);
अटल व्योम si_init_cg(काष्ठा radeon_device *rdev);
अटल व्योम si_fini_pg(काष्ठा radeon_device *rdev);
अटल व्योम si_fini_cg(काष्ठा radeon_device *rdev);
अटल व्योम si_rlc_stop(काष्ठा radeon_device *rdev);

अटल स्थिर u32 crtc_offsets[] =
अणु
	EVERGREEN_CRTC0_REGISTER_OFFSET,
	EVERGREEN_CRTC1_REGISTER_OFFSET,
	EVERGREEN_CRTC2_REGISTER_OFFSET,
	EVERGREEN_CRTC3_REGISTER_OFFSET,
	EVERGREEN_CRTC4_REGISTER_OFFSET,
	EVERGREEN_CRTC5_REGISTER_OFFSET
पूर्ण;

अटल स्थिर u32 si_disp_पूर्णांक_status[] =
अणु
	DISP_INTERRUPT_STATUS,
	DISP_INTERRUPT_STATUS_CONTINUE,
	DISP_INTERRUPT_STATUS_CONTINUE2,
	DISP_INTERRUPT_STATUS_CONTINUE3,
	DISP_INTERRUPT_STATUS_CONTINUE4,
	DISP_INTERRUPT_STATUS_CONTINUE5
पूर्ण;

#घोषणा DC_HPDx_CONTROL(x)        (DC_HPD1_CONTROL     + (x * 0xc))
#घोषणा DC_HPDx_INT_CONTROL(x)    (DC_HPD1_INT_CONTROL + (x * 0xc))
#घोषणा DC_HPDx_INT_STATUS_REG(x) (DC_HPD1_INT_STATUS  + (x * 0xc))

अटल स्थिर u32 verde_rlc_save_restore_रेजिस्टर_list[] =
अणु
	(0x8000 << 16) | (0x98f4 >> 2),
	0x00000000,
	(0x8040 << 16) | (0x98f4 >> 2),
	0x00000000,
	(0x8000 << 16) | (0xe80 >> 2),
	0x00000000,
	(0x8040 << 16) | (0xe80 >> 2),
	0x00000000,
	(0x8000 << 16) | (0x89bc >> 2),
	0x00000000,
	(0x8040 << 16) | (0x89bc >> 2),
	0x00000000,
	(0x8000 << 16) | (0x8c1c >> 2),
	0x00000000,
	(0x8040 << 16) | (0x8c1c >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x98f0 >> 2),
	0x00000000,
	(0x9c00 << 16) | (0xe7c >> 2),
	0x00000000,
	(0x8000 << 16) | (0x9148 >> 2),
	0x00000000,
	(0x8040 << 16) | (0x9148 >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x9150 >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x897c >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x8d8c >> 2),
	0x00000000,
	(0x9c00 << 16) | (0xac54 >> 2),
	0X00000000,
	0x3,
	(0x9c00 << 16) | (0x98f8 >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x9910 >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x9914 >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x9918 >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x991c >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x9920 >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x9924 >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x9928 >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x992c >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x9930 >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x9934 >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x9938 >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x993c >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x9940 >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x9944 >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x9948 >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x994c >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x9950 >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x9954 >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x9958 >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x995c >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x9960 >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x9964 >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x9968 >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x996c >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x9970 >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x9974 >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x9978 >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x997c >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x9980 >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x9984 >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x9988 >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x998c >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x8c00 >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x8c14 >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x8c04 >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x8c08 >> 2),
	0x00000000,
	(0x8000 << 16) | (0x9b7c >> 2),
	0x00000000,
	(0x8040 << 16) | (0x9b7c >> 2),
	0x00000000,
	(0x8000 << 16) | (0xe84 >> 2),
	0x00000000,
	(0x8040 << 16) | (0xe84 >> 2),
	0x00000000,
	(0x8000 << 16) | (0x89c0 >> 2),
	0x00000000,
	(0x8040 << 16) | (0x89c0 >> 2),
	0x00000000,
	(0x8000 << 16) | (0x914c >> 2),
	0x00000000,
	(0x8040 << 16) | (0x914c >> 2),
	0x00000000,
	(0x8000 << 16) | (0x8c20 >> 2),
	0x00000000,
	(0x8040 << 16) | (0x8c20 >> 2),
	0x00000000,
	(0x8000 << 16) | (0x9354 >> 2),
	0x00000000,
	(0x8040 << 16) | (0x9354 >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x9060 >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x9364 >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x9100 >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x913c >> 2),
	0x00000000,
	(0x8000 << 16) | (0x90e0 >> 2),
	0x00000000,
	(0x8000 << 16) | (0x90e4 >> 2),
	0x00000000,
	(0x8000 << 16) | (0x90e8 >> 2),
	0x00000000,
	(0x8040 << 16) | (0x90e0 >> 2),
	0x00000000,
	(0x8040 << 16) | (0x90e4 >> 2),
	0x00000000,
	(0x8040 << 16) | (0x90e8 >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x8bcc >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x8b24 >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x88c4 >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x8e50 >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x8c0c >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x8e58 >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x8e5c >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x9508 >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x950c >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x9494 >> 2),
	0x00000000,
	(0x9c00 << 16) | (0xac0c >> 2),
	0x00000000,
	(0x9c00 << 16) | (0xac10 >> 2),
	0x00000000,
	(0x9c00 << 16) | (0xac14 >> 2),
	0x00000000,
	(0x9c00 << 16) | (0xae00 >> 2),
	0x00000000,
	(0x9c00 << 16) | (0xac08 >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x88d4 >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x88c8 >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x88cc >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x89b0 >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x8b10 >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x8a14 >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x9830 >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x9834 >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x9838 >> 2),
	0x00000000,
	(0x9c00 << 16) | (0x9a10 >> 2),
	0x00000000,
	(0x8000 << 16) | (0x9870 >> 2),
	0x00000000,
	(0x8000 << 16) | (0x9874 >> 2),
	0x00000000,
	(0x8001 << 16) | (0x9870 >> 2),
	0x00000000,
	(0x8001 << 16) | (0x9874 >> 2),
	0x00000000,
	(0x8040 << 16) | (0x9870 >> 2),
	0x00000000,
	(0x8040 << 16) | (0x9874 >> 2),
	0x00000000,
	(0x8041 << 16) | (0x9870 >> 2),
	0x00000000,
	(0x8041 << 16) | (0x9874 >> 2),
	0x00000000,
	0x00000000
पूर्ण;

अटल स्थिर u32 tahiti_golden_rlc_रेजिस्टरs[] =
अणु
	0xc424, 0xffffffff, 0x00601005,
	0xc47c, 0xffffffff, 0x10104040,
	0xc488, 0xffffffff, 0x0100000a,
	0xc314, 0xffffffff, 0x00000800,
	0xc30c, 0xffffffff, 0x800000f4,
	0xf4a8, 0xffffffff, 0x00000000
पूर्ण;

अटल स्थिर u32 tahiti_golden_रेजिस्टरs[] =
अणु
	0x9a10, 0x00010000, 0x00018208,
	0x9830, 0xffffffff, 0x00000000,
	0x9834, 0xf00fffff, 0x00000400,
	0x9838, 0x0002021c, 0x00020200,
	0xc78, 0x00000080, 0x00000000,
	0xd030, 0x000300c0, 0x00800040,
	0xd830, 0x000300c0, 0x00800040,
	0x5bb0, 0x000000f0, 0x00000070,
	0x5bc0, 0x00200000, 0x50100000,
	0x7030, 0x31000311, 0x00000011,
	0x277c, 0x00000003, 0x000007ff,
	0x240c, 0x000007ff, 0x00000000,
	0x8a14, 0xf000001f, 0x00000007,
	0x8b24, 0xffffffff, 0x00ffffff,
	0x8b10, 0x0000ff0f, 0x00000000,
	0x28a4c, 0x07ffffff, 0x4e000000,
	0x28350, 0x3f3f3fff, 0x2a00126a,
	0x30, 0x000000ff, 0x0040,
	0x34, 0x00000040, 0x00004040,
	0x9100, 0x07ffffff, 0x03000000,
	0x8e88, 0x01ff1f3f, 0x00000000,
	0x8e84, 0x01ff1f3f, 0x00000000,
	0x9060, 0x0000007f, 0x00000020,
	0x9508, 0x00010000, 0x00010000,
	0xac14, 0x00000200, 0x000002fb,
	0xac10, 0xffffffff, 0x0000543b,
	0xac0c, 0xffffffff, 0xa9210876,
	0x88d0, 0xffffffff, 0x000fff40,
	0x88d4, 0x0000001f, 0x00000010,
	0x1410, 0x20000000, 0x20fffed8,
	0x15c0, 0x000c0fc0, 0x000c0400
पूर्ण;

अटल स्थिर u32 tahiti_golden_रेजिस्टरs2[] =
अणु
	0xc64, 0x00000001, 0x00000001
पूर्ण;

अटल स्थिर u32 pitcairn_golden_rlc_रेजिस्टरs[] =
अणु
	0xc424, 0xffffffff, 0x00601004,
	0xc47c, 0xffffffff, 0x10102020,
	0xc488, 0xffffffff, 0x01000020,
	0xc314, 0xffffffff, 0x00000800,
	0xc30c, 0xffffffff, 0x800000a4
पूर्ण;

अटल स्थिर u32 pitcairn_golden_रेजिस्टरs[] =
अणु
	0x9a10, 0x00010000, 0x00018208,
	0x9830, 0xffffffff, 0x00000000,
	0x9834, 0xf00fffff, 0x00000400,
	0x9838, 0x0002021c, 0x00020200,
	0xc78, 0x00000080, 0x00000000,
	0xd030, 0x000300c0, 0x00800040,
	0xd830, 0x000300c0, 0x00800040,
	0x5bb0, 0x000000f0, 0x00000070,
	0x5bc0, 0x00200000, 0x50100000,
	0x7030, 0x31000311, 0x00000011,
	0x2ae4, 0x00073ffe, 0x000022a2,
	0x240c, 0x000007ff, 0x00000000,
	0x8a14, 0xf000001f, 0x00000007,
	0x8b24, 0xffffffff, 0x00ffffff,
	0x8b10, 0x0000ff0f, 0x00000000,
	0x28a4c, 0x07ffffff, 0x4e000000,
	0x28350, 0x3f3f3fff, 0x2a00126a,
	0x30, 0x000000ff, 0x0040,
	0x34, 0x00000040, 0x00004040,
	0x9100, 0x07ffffff, 0x03000000,
	0x9060, 0x0000007f, 0x00000020,
	0x9508, 0x00010000, 0x00010000,
	0xac14, 0x000003ff, 0x000000f7,
	0xac10, 0xffffffff, 0x00000000,
	0xac0c, 0xffffffff, 0x32761054,
	0x88d4, 0x0000001f, 0x00000010,
	0x15c0, 0x000c0fc0, 0x000c0400
पूर्ण;

अटल स्थिर u32 verde_golden_rlc_रेजिस्टरs[] =
अणु
	0xc424, 0xffffffff, 0x033f1005,
	0xc47c, 0xffffffff, 0x10808020,
	0xc488, 0xffffffff, 0x00800008,
	0xc314, 0xffffffff, 0x00001000,
	0xc30c, 0xffffffff, 0x80010014
पूर्ण;

अटल स्थिर u32 verde_golden_रेजिस्टरs[] =
अणु
	0x9a10, 0x00010000, 0x00018208,
	0x9830, 0xffffffff, 0x00000000,
	0x9834, 0xf00fffff, 0x00000400,
	0x9838, 0x0002021c, 0x00020200,
	0xc78, 0x00000080, 0x00000000,
	0xd030, 0x000300c0, 0x00800040,
	0xd030, 0x000300c0, 0x00800040,
	0xd830, 0x000300c0, 0x00800040,
	0xd830, 0x000300c0, 0x00800040,
	0x5bb0, 0x000000f0, 0x00000070,
	0x5bc0, 0x00200000, 0x50100000,
	0x7030, 0x31000311, 0x00000011,
	0x2ae4, 0x00073ffe, 0x000022a2,
	0x2ae4, 0x00073ffe, 0x000022a2,
	0x2ae4, 0x00073ffe, 0x000022a2,
	0x240c, 0x000007ff, 0x00000000,
	0x240c, 0x000007ff, 0x00000000,
	0x240c, 0x000007ff, 0x00000000,
	0x8a14, 0xf000001f, 0x00000007,
	0x8a14, 0xf000001f, 0x00000007,
	0x8a14, 0xf000001f, 0x00000007,
	0x8b24, 0xffffffff, 0x00ffffff,
	0x8b10, 0x0000ff0f, 0x00000000,
	0x28a4c, 0x07ffffff, 0x4e000000,
	0x28350, 0x3f3f3fff, 0x0000124a,
	0x28350, 0x3f3f3fff, 0x0000124a,
	0x28350, 0x3f3f3fff, 0x0000124a,
	0x30, 0x000000ff, 0x0040,
	0x34, 0x00000040, 0x00004040,
	0x9100, 0x07ffffff, 0x03000000,
	0x9100, 0x07ffffff, 0x03000000,
	0x8e88, 0x01ff1f3f, 0x00000000,
	0x8e88, 0x01ff1f3f, 0x00000000,
	0x8e88, 0x01ff1f3f, 0x00000000,
	0x8e84, 0x01ff1f3f, 0x00000000,
	0x8e84, 0x01ff1f3f, 0x00000000,
	0x8e84, 0x01ff1f3f, 0x00000000,
	0x9060, 0x0000007f, 0x00000020,
	0x9508, 0x00010000, 0x00010000,
	0xac14, 0x000003ff, 0x00000003,
	0xac14, 0x000003ff, 0x00000003,
	0xac14, 0x000003ff, 0x00000003,
	0xac10, 0xffffffff, 0x00000000,
	0xac10, 0xffffffff, 0x00000000,
	0xac10, 0xffffffff, 0x00000000,
	0xac0c, 0xffffffff, 0x00001032,
	0xac0c, 0xffffffff, 0x00001032,
	0xac0c, 0xffffffff, 0x00001032,
	0x88d4, 0x0000001f, 0x00000010,
	0x88d4, 0x0000001f, 0x00000010,
	0x88d4, 0x0000001f, 0x00000010,
	0x15c0, 0x000c0fc0, 0x000c0400
पूर्ण;

अटल स्थिर u32 oland_golden_rlc_रेजिस्टरs[] =
अणु
	0xc424, 0xffffffff, 0x00601005,
	0xc47c, 0xffffffff, 0x10104040,
	0xc488, 0xffffffff, 0x0100000a,
	0xc314, 0xffffffff, 0x00000800,
	0xc30c, 0xffffffff, 0x800000f4
पूर्ण;

अटल स्थिर u32 oland_golden_रेजिस्टरs[] =
अणु
	0x9a10, 0x00010000, 0x00018208,
	0x9830, 0xffffffff, 0x00000000,
	0x9834, 0xf00fffff, 0x00000400,
	0x9838, 0x0002021c, 0x00020200,
	0xc78, 0x00000080, 0x00000000,
	0xd030, 0x000300c0, 0x00800040,
	0xd830, 0x000300c0, 0x00800040,
	0x5bb0, 0x000000f0, 0x00000070,
	0x5bc0, 0x00200000, 0x50100000,
	0x7030, 0x31000311, 0x00000011,
	0x2ae4, 0x00073ffe, 0x000022a2,
	0x240c, 0x000007ff, 0x00000000,
	0x8a14, 0xf000001f, 0x00000007,
	0x8b24, 0xffffffff, 0x00ffffff,
	0x8b10, 0x0000ff0f, 0x00000000,
	0x28a4c, 0x07ffffff, 0x4e000000,
	0x28350, 0x3f3f3fff, 0x00000082,
	0x30, 0x000000ff, 0x0040,
	0x34, 0x00000040, 0x00004040,
	0x9100, 0x07ffffff, 0x03000000,
	0x9060, 0x0000007f, 0x00000020,
	0x9508, 0x00010000, 0x00010000,
	0xac14, 0x000003ff, 0x000000f3,
	0xac10, 0xffffffff, 0x00000000,
	0xac0c, 0xffffffff, 0x00003210,
	0x88d4, 0x0000001f, 0x00000010,
	0x15c0, 0x000c0fc0, 0x000c0400
पूर्ण;

अटल स्थिर u32 hainan_golden_रेजिस्टरs[] =
अणु
	0x9a10, 0x00010000, 0x00018208,
	0x9830, 0xffffffff, 0x00000000,
	0x9834, 0xf00fffff, 0x00000400,
	0x9838, 0x0002021c, 0x00020200,
	0xd0c0, 0xff000fff, 0x00000100,
	0xd030, 0x000300c0, 0x00800040,
	0xd8c0, 0xff000fff, 0x00000100,
	0xd830, 0x000300c0, 0x00800040,
	0x2ae4, 0x00073ffe, 0x000022a2,
	0x240c, 0x000007ff, 0x00000000,
	0x8a14, 0xf000001f, 0x00000007,
	0x8b24, 0xffffffff, 0x00ffffff,
	0x8b10, 0x0000ff0f, 0x00000000,
	0x28a4c, 0x07ffffff, 0x4e000000,
	0x28350, 0x3f3f3fff, 0x00000000,
	0x30, 0x000000ff, 0x0040,
	0x34, 0x00000040, 0x00004040,
	0x9100, 0x03e00000, 0x03600000,
	0x9060, 0x0000007f, 0x00000020,
	0x9508, 0x00010000, 0x00010000,
	0xac14, 0x000003ff, 0x000000f1,
	0xac10, 0xffffffff, 0x00000000,
	0xac0c, 0xffffffff, 0x00003210,
	0x88d4, 0x0000001f, 0x00000010,
	0x15c0, 0x000c0fc0, 0x000c0400
पूर्ण;

अटल स्थिर u32 hainan_golden_रेजिस्टरs2[] =
अणु
	0x98f8, 0xffffffff, 0x02010001
पूर्ण;

अटल स्थिर u32 tahiti_mgcg_cgcg_init[] =
अणु
	0xc400, 0xffffffff, 0xfffffffc,
	0x802c, 0xffffffff, 0xe0000000,
	0x9a60, 0xffffffff, 0x00000100,
	0x92a4, 0xffffffff, 0x00000100,
	0xc164, 0xffffffff, 0x00000100,
	0x9774, 0xffffffff, 0x00000100,
	0x8984, 0xffffffff, 0x06000100,
	0x8a18, 0xffffffff, 0x00000100,
	0x92a0, 0xffffffff, 0x00000100,
	0xc380, 0xffffffff, 0x00000100,
	0x8b28, 0xffffffff, 0x00000100,
	0x9144, 0xffffffff, 0x00000100,
	0x8d88, 0xffffffff, 0x00000100,
	0x8d8c, 0xffffffff, 0x00000100,
	0x9030, 0xffffffff, 0x00000100,
	0x9034, 0xffffffff, 0x00000100,
	0x9038, 0xffffffff, 0x00000100,
	0x903c, 0xffffffff, 0x00000100,
	0xad80, 0xffffffff, 0x00000100,
	0xac54, 0xffffffff, 0x00000100,
	0x897c, 0xffffffff, 0x06000100,
	0x9868, 0xffffffff, 0x00000100,
	0x9510, 0xffffffff, 0x00000100,
	0xaf04, 0xffffffff, 0x00000100,
	0xae04, 0xffffffff, 0x00000100,
	0x949c, 0xffffffff, 0x00000100,
	0x802c, 0xffffffff, 0xe0000000,
	0x9160, 0xffffffff, 0x00010000,
	0x9164, 0xffffffff, 0x00030002,
	0x9168, 0xffffffff, 0x00040007,
	0x916c, 0xffffffff, 0x00060005,
	0x9170, 0xffffffff, 0x00090008,
	0x9174, 0xffffffff, 0x00020001,
	0x9178, 0xffffffff, 0x00040003,
	0x917c, 0xffffffff, 0x00000007,
	0x9180, 0xffffffff, 0x00060005,
	0x9184, 0xffffffff, 0x00090008,
	0x9188, 0xffffffff, 0x00030002,
	0x918c, 0xffffffff, 0x00050004,
	0x9190, 0xffffffff, 0x00000008,
	0x9194, 0xffffffff, 0x00070006,
	0x9198, 0xffffffff, 0x000a0009,
	0x919c, 0xffffffff, 0x00040003,
	0x91a0, 0xffffffff, 0x00060005,
	0x91a4, 0xffffffff, 0x00000009,
	0x91a8, 0xffffffff, 0x00080007,
	0x91ac, 0xffffffff, 0x000b000a,
	0x91b0, 0xffffffff, 0x00050004,
	0x91b4, 0xffffffff, 0x00070006,
	0x91b8, 0xffffffff, 0x0008000b,
	0x91bc, 0xffffffff, 0x000a0009,
	0x91c0, 0xffffffff, 0x000d000c,
	0x91c4, 0xffffffff, 0x00060005,
	0x91c8, 0xffffffff, 0x00080007,
	0x91cc, 0xffffffff, 0x0000000b,
	0x91d0, 0xffffffff, 0x000a0009,
	0x91d4, 0xffffffff, 0x000d000c,
	0x91d8, 0xffffffff, 0x00070006,
	0x91dc, 0xffffffff, 0x00090008,
	0x91e0, 0xffffffff, 0x0000000c,
	0x91e4, 0xffffffff, 0x000b000a,
	0x91e8, 0xffffffff, 0x000e000d,
	0x91ec, 0xffffffff, 0x00080007,
	0x91f0, 0xffffffff, 0x000a0009,
	0x91f4, 0xffffffff, 0x0000000d,
	0x91f8, 0xffffffff, 0x000c000b,
	0x91fc, 0xffffffff, 0x000f000e,
	0x9200, 0xffffffff, 0x00090008,
	0x9204, 0xffffffff, 0x000b000a,
	0x9208, 0xffffffff, 0x000c000f,
	0x920c, 0xffffffff, 0x000e000d,
	0x9210, 0xffffffff, 0x00110010,
	0x9214, 0xffffffff, 0x000a0009,
	0x9218, 0xffffffff, 0x000c000b,
	0x921c, 0xffffffff, 0x0000000f,
	0x9220, 0xffffffff, 0x000e000d,
	0x9224, 0xffffffff, 0x00110010,
	0x9228, 0xffffffff, 0x000b000a,
	0x922c, 0xffffffff, 0x000d000c,
	0x9230, 0xffffffff, 0x00000010,
	0x9234, 0xffffffff, 0x000f000e,
	0x9238, 0xffffffff, 0x00120011,
	0x923c, 0xffffffff, 0x000c000b,
	0x9240, 0xffffffff, 0x000e000d,
	0x9244, 0xffffffff, 0x00000011,
	0x9248, 0xffffffff, 0x0010000f,
	0x924c, 0xffffffff, 0x00130012,
	0x9250, 0xffffffff, 0x000d000c,
	0x9254, 0xffffffff, 0x000f000e,
	0x9258, 0xffffffff, 0x00100013,
	0x925c, 0xffffffff, 0x00120011,
	0x9260, 0xffffffff, 0x00150014,
	0x9264, 0xffffffff, 0x000e000d,
	0x9268, 0xffffffff, 0x0010000f,
	0x926c, 0xffffffff, 0x00000013,
	0x9270, 0xffffffff, 0x00120011,
	0x9274, 0xffffffff, 0x00150014,
	0x9278, 0xffffffff, 0x000f000e,
	0x927c, 0xffffffff, 0x00110010,
	0x9280, 0xffffffff, 0x00000014,
	0x9284, 0xffffffff, 0x00130012,
	0x9288, 0xffffffff, 0x00160015,
	0x928c, 0xffffffff, 0x0010000f,
	0x9290, 0xffffffff, 0x00120011,
	0x9294, 0xffffffff, 0x00000015,
	0x9298, 0xffffffff, 0x00140013,
	0x929c, 0xffffffff, 0x00170016,
	0x9150, 0xffffffff, 0x96940200,
	0x8708, 0xffffffff, 0x00900100,
	0xc478, 0xffffffff, 0x00000080,
	0xc404, 0xffffffff, 0x0020003f,
	0x30, 0xffffffff, 0x0000001c,
	0x34, 0x000f0000, 0x000f0000,
	0x160c, 0xffffffff, 0x00000100,
	0x1024, 0xffffffff, 0x00000100,
	0x102c, 0x00000101, 0x00000000,
	0x20a8, 0xffffffff, 0x00000104,
	0x264c, 0x000c0000, 0x000c0000,
	0x2648, 0x000c0000, 0x000c0000,
	0x55e4, 0xff000fff, 0x00000100,
	0x55e8, 0x00000001, 0x00000001,
	0x2f50, 0x00000001, 0x00000001,
	0x30cc, 0xc0000fff, 0x00000104,
	0xc1e4, 0x00000001, 0x00000001,
	0xd0c0, 0xfffffff0, 0x00000100,
	0xd8c0, 0xfffffff0, 0x00000100
पूर्ण;

अटल स्थिर u32 pitcairn_mgcg_cgcg_init[] =
अणु
	0xc400, 0xffffffff, 0xfffffffc,
	0x802c, 0xffffffff, 0xe0000000,
	0x9a60, 0xffffffff, 0x00000100,
	0x92a4, 0xffffffff, 0x00000100,
	0xc164, 0xffffffff, 0x00000100,
	0x9774, 0xffffffff, 0x00000100,
	0x8984, 0xffffffff, 0x06000100,
	0x8a18, 0xffffffff, 0x00000100,
	0x92a0, 0xffffffff, 0x00000100,
	0xc380, 0xffffffff, 0x00000100,
	0x8b28, 0xffffffff, 0x00000100,
	0x9144, 0xffffffff, 0x00000100,
	0x8d88, 0xffffffff, 0x00000100,
	0x8d8c, 0xffffffff, 0x00000100,
	0x9030, 0xffffffff, 0x00000100,
	0x9034, 0xffffffff, 0x00000100,
	0x9038, 0xffffffff, 0x00000100,
	0x903c, 0xffffffff, 0x00000100,
	0xad80, 0xffffffff, 0x00000100,
	0xac54, 0xffffffff, 0x00000100,
	0x897c, 0xffffffff, 0x06000100,
	0x9868, 0xffffffff, 0x00000100,
	0x9510, 0xffffffff, 0x00000100,
	0xaf04, 0xffffffff, 0x00000100,
	0xae04, 0xffffffff, 0x00000100,
	0x949c, 0xffffffff, 0x00000100,
	0x802c, 0xffffffff, 0xe0000000,
	0x9160, 0xffffffff, 0x00010000,
	0x9164, 0xffffffff, 0x00030002,
	0x9168, 0xffffffff, 0x00040007,
	0x916c, 0xffffffff, 0x00060005,
	0x9170, 0xffffffff, 0x00090008,
	0x9174, 0xffffffff, 0x00020001,
	0x9178, 0xffffffff, 0x00040003,
	0x917c, 0xffffffff, 0x00000007,
	0x9180, 0xffffffff, 0x00060005,
	0x9184, 0xffffffff, 0x00090008,
	0x9188, 0xffffffff, 0x00030002,
	0x918c, 0xffffffff, 0x00050004,
	0x9190, 0xffffffff, 0x00000008,
	0x9194, 0xffffffff, 0x00070006,
	0x9198, 0xffffffff, 0x000a0009,
	0x919c, 0xffffffff, 0x00040003,
	0x91a0, 0xffffffff, 0x00060005,
	0x91a4, 0xffffffff, 0x00000009,
	0x91a8, 0xffffffff, 0x00080007,
	0x91ac, 0xffffffff, 0x000b000a,
	0x91b0, 0xffffffff, 0x00050004,
	0x91b4, 0xffffffff, 0x00070006,
	0x91b8, 0xffffffff, 0x0008000b,
	0x91bc, 0xffffffff, 0x000a0009,
	0x91c0, 0xffffffff, 0x000d000c,
	0x9200, 0xffffffff, 0x00090008,
	0x9204, 0xffffffff, 0x000b000a,
	0x9208, 0xffffffff, 0x000c000f,
	0x920c, 0xffffffff, 0x000e000d,
	0x9210, 0xffffffff, 0x00110010,
	0x9214, 0xffffffff, 0x000a0009,
	0x9218, 0xffffffff, 0x000c000b,
	0x921c, 0xffffffff, 0x0000000f,
	0x9220, 0xffffffff, 0x000e000d,
	0x9224, 0xffffffff, 0x00110010,
	0x9228, 0xffffffff, 0x000b000a,
	0x922c, 0xffffffff, 0x000d000c,
	0x9230, 0xffffffff, 0x00000010,
	0x9234, 0xffffffff, 0x000f000e,
	0x9238, 0xffffffff, 0x00120011,
	0x923c, 0xffffffff, 0x000c000b,
	0x9240, 0xffffffff, 0x000e000d,
	0x9244, 0xffffffff, 0x00000011,
	0x9248, 0xffffffff, 0x0010000f,
	0x924c, 0xffffffff, 0x00130012,
	0x9250, 0xffffffff, 0x000d000c,
	0x9254, 0xffffffff, 0x000f000e,
	0x9258, 0xffffffff, 0x00100013,
	0x925c, 0xffffffff, 0x00120011,
	0x9260, 0xffffffff, 0x00150014,
	0x9150, 0xffffffff, 0x96940200,
	0x8708, 0xffffffff, 0x00900100,
	0xc478, 0xffffffff, 0x00000080,
	0xc404, 0xffffffff, 0x0020003f,
	0x30, 0xffffffff, 0x0000001c,
	0x34, 0x000f0000, 0x000f0000,
	0x160c, 0xffffffff, 0x00000100,
	0x1024, 0xffffffff, 0x00000100,
	0x102c, 0x00000101, 0x00000000,
	0x20a8, 0xffffffff, 0x00000104,
	0x55e4, 0xff000fff, 0x00000100,
	0x55e8, 0x00000001, 0x00000001,
	0x2f50, 0x00000001, 0x00000001,
	0x30cc, 0xc0000fff, 0x00000104,
	0xc1e4, 0x00000001, 0x00000001,
	0xd0c0, 0xfffffff0, 0x00000100,
	0xd8c0, 0xfffffff0, 0x00000100
पूर्ण;

अटल स्थिर u32 verde_mgcg_cgcg_init[] =
अणु
	0xc400, 0xffffffff, 0xfffffffc,
	0x802c, 0xffffffff, 0xe0000000,
	0x9a60, 0xffffffff, 0x00000100,
	0x92a4, 0xffffffff, 0x00000100,
	0xc164, 0xffffffff, 0x00000100,
	0x9774, 0xffffffff, 0x00000100,
	0x8984, 0xffffffff, 0x06000100,
	0x8a18, 0xffffffff, 0x00000100,
	0x92a0, 0xffffffff, 0x00000100,
	0xc380, 0xffffffff, 0x00000100,
	0x8b28, 0xffffffff, 0x00000100,
	0x9144, 0xffffffff, 0x00000100,
	0x8d88, 0xffffffff, 0x00000100,
	0x8d8c, 0xffffffff, 0x00000100,
	0x9030, 0xffffffff, 0x00000100,
	0x9034, 0xffffffff, 0x00000100,
	0x9038, 0xffffffff, 0x00000100,
	0x903c, 0xffffffff, 0x00000100,
	0xad80, 0xffffffff, 0x00000100,
	0xac54, 0xffffffff, 0x00000100,
	0x897c, 0xffffffff, 0x06000100,
	0x9868, 0xffffffff, 0x00000100,
	0x9510, 0xffffffff, 0x00000100,
	0xaf04, 0xffffffff, 0x00000100,
	0xae04, 0xffffffff, 0x00000100,
	0x949c, 0xffffffff, 0x00000100,
	0x802c, 0xffffffff, 0xe0000000,
	0x9160, 0xffffffff, 0x00010000,
	0x9164, 0xffffffff, 0x00030002,
	0x9168, 0xffffffff, 0x00040007,
	0x916c, 0xffffffff, 0x00060005,
	0x9170, 0xffffffff, 0x00090008,
	0x9174, 0xffffffff, 0x00020001,
	0x9178, 0xffffffff, 0x00040003,
	0x917c, 0xffffffff, 0x00000007,
	0x9180, 0xffffffff, 0x00060005,
	0x9184, 0xffffffff, 0x00090008,
	0x9188, 0xffffffff, 0x00030002,
	0x918c, 0xffffffff, 0x00050004,
	0x9190, 0xffffffff, 0x00000008,
	0x9194, 0xffffffff, 0x00070006,
	0x9198, 0xffffffff, 0x000a0009,
	0x919c, 0xffffffff, 0x00040003,
	0x91a0, 0xffffffff, 0x00060005,
	0x91a4, 0xffffffff, 0x00000009,
	0x91a8, 0xffffffff, 0x00080007,
	0x91ac, 0xffffffff, 0x000b000a,
	0x91b0, 0xffffffff, 0x00050004,
	0x91b4, 0xffffffff, 0x00070006,
	0x91b8, 0xffffffff, 0x0008000b,
	0x91bc, 0xffffffff, 0x000a0009,
	0x91c0, 0xffffffff, 0x000d000c,
	0x9200, 0xffffffff, 0x00090008,
	0x9204, 0xffffffff, 0x000b000a,
	0x9208, 0xffffffff, 0x000c000f,
	0x920c, 0xffffffff, 0x000e000d,
	0x9210, 0xffffffff, 0x00110010,
	0x9214, 0xffffffff, 0x000a0009,
	0x9218, 0xffffffff, 0x000c000b,
	0x921c, 0xffffffff, 0x0000000f,
	0x9220, 0xffffffff, 0x000e000d,
	0x9224, 0xffffffff, 0x00110010,
	0x9228, 0xffffffff, 0x000b000a,
	0x922c, 0xffffffff, 0x000d000c,
	0x9230, 0xffffffff, 0x00000010,
	0x9234, 0xffffffff, 0x000f000e,
	0x9238, 0xffffffff, 0x00120011,
	0x923c, 0xffffffff, 0x000c000b,
	0x9240, 0xffffffff, 0x000e000d,
	0x9244, 0xffffffff, 0x00000011,
	0x9248, 0xffffffff, 0x0010000f,
	0x924c, 0xffffffff, 0x00130012,
	0x9250, 0xffffffff, 0x000d000c,
	0x9254, 0xffffffff, 0x000f000e,
	0x9258, 0xffffffff, 0x00100013,
	0x925c, 0xffffffff, 0x00120011,
	0x9260, 0xffffffff, 0x00150014,
	0x9150, 0xffffffff, 0x96940200,
	0x8708, 0xffffffff, 0x00900100,
	0xc478, 0xffffffff, 0x00000080,
	0xc404, 0xffffffff, 0x0020003f,
	0x30, 0xffffffff, 0x0000001c,
	0x34, 0x000f0000, 0x000f0000,
	0x160c, 0xffffffff, 0x00000100,
	0x1024, 0xffffffff, 0x00000100,
	0x102c, 0x00000101, 0x00000000,
	0x20a8, 0xffffffff, 0x00000104,
	0x264c, 0x000c0000, 0x000c0000,
	0x2648, 0x000c0000, 0x000c0000,
	0x55e4, 0xff000fff, 0x00000100,
	0x55e8, 0x00000001, 0x00000001,
	0x2f50, 0x00000001, 0x00000001,
	0x30cc, 0xc0000fff, 0x00000104,
	0xc1e4, 0x00000001, 0x00000001,
	0xd0c0, 0xfffffff0, 0x00000100,
	0xd8c0, 0xfffffff0, 0x00000100
पूर्ण;

अटल स्थिर u32 oland_mgcg_cgcg_init[] =
अणु
	0xc400, 0xffffffff, 0xfffffffc,
	0x802c, 0xffffffff, 0xe0000000,
	0x9a60, 0xffffffff, 0x00000100,
	0x92a4, 0xffffffff, 0x00000100,
	0xc164, 0xffffffff, 0x00000100,
	0x9774, 0xffffffff, 0x00000100,
	0x8984, 0xffffffff, 0x06000100,
	0x8a18, 0xffffffff, 0x00000100,
	0x92a0, 0xffffffff, 0x00000100,
	0xc380, 0xffffffff, 0x00000100,
	0x8b28, 0xffffffff, 0x00000100,
	0x9144, 0xffffffff, 0x00000100,
	0x8d88, 0xffffffff, 0x00000100,
	0x8d8c, 0xffffffff, 0x00000100,
	0x9030, 0xffffffff, 0x00000100,
	0x9034, 0xffffffff, 0x00000100,
	0x9038, 0xffffffff, 0x00000100,
	0x903c, 0xffffffff, 0x00000100,
	0xad80, 0xffffffff, 0x00000100,
	0xac54, 0xffffffff, 0x00000100,
	0x897c, 0xffffffff, 0x06000100,
	0x9868, 0xffffffff, 0x00000100,
	0x9510, 0xffffffff, 0x00000100,
	0xaf04, 0xffffffff, 0x00000100,
	0xae04, 0xffffffff, 0x00000100,
	0x949c, 0xffffffff, 0x00000100,
	0x802c, 0xffffffff, 0xe0000000,
	0x9160, 0xffffffff, 0x00010000,
	0x9164, 0xffffffff, 0x00030002,
	0x9168, 0xffffffff, 0x00040007,
	0x916c, 0xffffffff, 0x00060005,
	0x9170, 0xffffffff, 0x00090008,
	0x9174, 0xffffffff, 0x00020001,
	0x9178, 0xffffffff, 0x00040003,
	0x917c, 0xffffffff, 0x00000007,
	0x9180, 0xffffffff, 0x00060005,
	0x9184, 0xffffffff, 0x00090008,
	0x9188, 0xffffffff, 0x00030002,
	0x918c, 0xffffffff, 0x00050004,
	0x9190, 0xffffffff, 0x00000008,
	0x9194, 0xffffffff, 0x00070006,
	0x9198, 0xffffffff, 0x000a0009,
	0x919c, 0xffffffff, 0x00040003,
	0x91a0, 0xffffffff, 0x00060005,
	0x91a4, 0xffffffff, 0x00000009,
	0x91a8, 0xffffffff, 0x00080007,
	0x91ac, 0xffffffff, 0x000b000a,
	0x91b0, 0xffffffff, 0x00050004,
	0x91b4, 0xffffffff, 0x00070006,
	0x91b8, 0xffffffff, 0x0008000b,
	0x91bc, 0xffffffff, 0x000a0009,
	0x91c0, 0xffffffff, 0x000d000c,
	0x91c4, 0xffffffff, 0x00060005,
	0x91c8, 0xffffffff, 0x00080007,
	0x91cc, 0xffffffff, 0x0000000b,
	0x91d0, 0xffffffff, 0x000a0009,
	0x91d4, 0xffffffff, 0x000d000c,
	0x9150, 0xffffffff, 0x96940200,
	0x8708, 0xffffffff, 0x00900100,
	0xc478, 0xffffffff, 0x00000080,
	0xc404, 0xffffffff, 0x0020003f,
	0x30, 0xffffffff, 0x0000001c,
	0x34, 0x000f0000, 0x000f0000,
	0x160c, 0xffffffff, 0x00000100,
	0x1024, 0xffffffff, 0x00000100,
	0x102c, 0x00000101, 0x00000000,
	0x20a8, 0xffffffff, 0x00000104,
	0x264c, 0x000c0000, 0x000c0000,
	0x2648, 0x000c0000, 0x000c0000,
	0x55e4, 0xff000fff, 0x00000100,
	0x55e8, 0x00000001, 0x00000001,
	0x2f50, 0x00000001, 0x00000001,
	0x30cc, 0xc0000fff, 0x00000104,
	0xc1e4, 0x00000001, 0x00000001,
	0xd0c0, 0xfffffff0, 0x00000100,
	0xd8c0, 0xfffffff0, 0x00000100
पूर्ण;

अटल स्थिर u32 hainan_mgcg_cgcg_init[] =
अणु
	0xc400, 0xffffffff, 0xfffffffc,
	0x802c, 0xffffffff, 0xe0000000,
	0x9a60, 0xffffffff, 0x00000100,
	0x92a4, 0xffffffff, 0x00000100,
	0xc164, 0xffffffff, 0x00000100,
	0x9774, 0xffffffff, 0x00000100,
	0x8984, 0xffffffff, 0x06000100,
	0x8a18, 0xffffffff, 0x00000100,
	0x92a0, 0xffffffff, 0x00000100,
	0xc380, 0xffffffff, 0x00000100,
	0x8b28, 0xffffffff, 0x00000100,
	0x9144, 0xffffffff, 0x00000100,
	0x8d88, 0xffffffff, 0x00000100,
	0x8d8c, 0xffffffff, 0x00000100,
	0x9030, 0xffffffff, 0x00000100,
	0x9034, 0xffffffff, 0x00000100,
	0x9038, 0xffffffff, 0x00000100,
	0x903c, 0xffffffff, 0x00000100,
	0xad80, 0xffffffff, 0x00000100,
	0xac54, 0xffffffff, 0x00000100,
	0x897c, 0xffffffff, 0x06000100,
	0x9868, 0xffffffff, 0x00000100,
	0x9510, 0xffffffff, 0x00000100,
	0xaf04, 0xffffffff, 0x00000100,
	0xae04, 0xffffffff, 0x00000100,
	0x949c, 0xffffffff, 0x00000100,
	0x802c, 0xffffffff, 0xe0000000,
	0x9160, 0xffffffff, 0x00010000,
	0x9164, 0xffffffff, 0x00030002,
	0x9168, 0xffffffff, 0x00040007,
	0x916c, 0xffffffff, 0x00060005,
	0x9170, 0xffffffff, 0x00090008,
	0x9174, 0xffffffff, 0x00020001,
	0x9178, 0xffffffff, 0x00040003,
	0x917c, 0xffffffff, 0x00000007,
	0x9180, 0xffffffff, 0x00060005,
	0x9184, 0xffffffff, 0x00090008,
	0x9188, 0xffffffff, 0x00030002,
	0x918c, 0xffffffff, 0x00050004,
	0x9190, 0xffffffff, 0x00000008,
	0x9194, 0xffffffff, 0x00070006,
	0x9198, 0xffffffff, 0x000a0009,
	0x919c, 0xffffffff, 0x00040003,
	0x91a0, 0xffffffff, 0x00060005,
	0x91a4, 0xffffffff, 0x00000009,
	0x91a8, 0xffffffff, 0x00080007,
	0x91ac, 0xffffffff, 0x000b000a,
	0x91b0, 0xffffffff, 0x00050004,
	0x91b4, 0xffffffff, 0x00070006,
	0x91b8, 0xffffffff, 0x0008000b,
	0x91bc, 0xffffffff, 0x000a0009,
	0x91c0, 0xffffffff, 0x000d000c,
	0x91c4, 0xffffffff, 0x00060005,
	0x91c8, 0xffffffff, 0x00080007,
	0x91cc, 0xffffffff, 0x0000000b,
	0x91d0, 0xffffffff, 0x000a0009,
	0x91d4, 0xffffffff, 0x000d000c,
	0x9150, 0xffffffff, 0x96940200,
	0x8708, 0xffffffff, 0x00900100,
	0xc478, 0xffffffff, 0x00000080,
	0xc404, 0xffffffff, 0x0020003f,
	0x30, 0xffffffff, 0x0000001c,
	0x34, 0x000f0000, 0x000f0000,
	0x160c, 0xffffffff, 0x00000100,
	0x1024, 0xffffffff, 0x00000100,
	0x20a8, 0xffffffff, 0x00000104,
	0x264c, 0x000c0000, 0x000c0000,
	0x2648, 0x000c0000, 0x000c0000,
	0x2f50, 0x00000001, 0x00000001,
	0x30cc, 0xc0000fff, 0x00000104,
	0xc1e4, 0x00000001, 0x00000001,
	0xd0c0, 0xfffffff0, 0x00000100,
	0xd8c0, 0xfffffff0, 0x00000100
पूर्ण;

अटल u32 verde_pg_init[] =
अणु
	0x353c, 0xffffffff, 0x40000,
	0x3538, 0xffffffff, 0x200010ff,
	0x353c, 0xffffffff, 0x0,
	0x353c, 0xffffffff, 0x0,
	0x353c, 0xffffffff, 0x0,
	0x353c, 0xffffffff, 0x0,
	0x353c, 0xffffffff, 0x0,
	0x353c, 0xffffffff, 0x7007,
	0x3538, 0xffffffff, 0x300010ff,
	0x353c, 0xffffffff, 0x0,
	0x353c, 0xffffffff, 0x0,
	0x353c, 0xffffffff, 0x0,
	0x353c, 0xffffffff, 0x0,
	0x353c, 0xffffffff, 0x0,
	0x353c, 0xffffffff, 0x400000,
	0x3538, 0xffffffff, 0x100010ff,
	0x353c, 0xffffffff, 0x0,
	0x353c, 0xffffffff, 0x0,
	0x353c, 0xffffffff, 0x0,
	0x353c, 0xffffffff, 0x0,
	0x353c, 0xffffffff, 0x0,
	0x353c, 0xffffffff, 0x120200,
	0x3538, 0xffffffff, 0x500010ff,
	0x353c, 0xffffffff, 0x0,
	0x353c, 0xffffffff, 0x0,
	0x353c, 0xffffffff, 0x0,
	0x353c, 0xffffffff, 0x0,
	0x353c, 0xffffffff, 0x0,
	0x353c, 0xffffffff, 0x1e1e16,
	0x3538, 0xffffffff, 0x600010ff,
	0x353c, 0xffffffff, 0x0,
	0x353c, 0xffffffff, 0x0,
	0x353c, 0xffffffff, 0x0,
	0x353c, 0xffffffff, 0x0,
	0x353c, 0xffffffff, 0x0,
	0x353c, 0xffffffff, 0x171f1e,
	0x3538, 0xffffffff, 0x700010ff,
	0x353c, 0xffffffff, 0x0,
	0x353c, 0xffffffff, 0x0,
	0x353c, 0xffffffff, 0x0,
	0x353c, 0xffffffff, 0x0,
	0x353c, 0xffffffff, 0x0,
	0x353c, 0xffffffff, 0x0,
	0x3538, 0xffffffff, 0x9ff,
	0x3500, 0xffffffff, 0x0,
	0x3504, 0xffffffff, 0x10000800,
	0x3504, 0xffffffff, 0xf,
	0x3504, 0xffffffff, 0xf,
	0x3500, 0xffffffff, 0x4,
	0x3504, 0xffffffff, 0x1000051e,
	0x3504, 0xffffffff, 0xffff,
	0x3504, 0xffffffff, 0xffff,
	0x3500, 0xffffffff, 0x8,
	0x3504, 0xffffffff, 0x80500,
	0x3500, 0xffffffff, 0x12,
	0x3504, 0xffffffff, 0x9050c,
	0x3500, 0xffffffff, 0x1d,
	0x3504, 0xffffffff, 0xb052c,
	0x3500, 0xffffffff, 0x2a,
	0x3504, 0xffffffff, 0x1053e,
	0x3500, 0xffffffff, 0x2d,
	0x3504, 0xffffffff, 0x10546,
	0x3500, 0xffffffff, 0x30,
	0x3504, 0xffffffff, 0xa054e,
	0x3500, 0xffffffff, 0x3c,
	0x3504, 0xffffffff, 0x1055f,
	0x3500, 0xffffffff, 0x3f,
	0x3504, 0xffffffff, 0x10567,
	0x3500, 0xffffffff, 0x42,
	0x3504, 0xffffffff, 0x1056f,
	0x3500, 0xffffffff, 0x45,
	0x3504, 0xffffffff, 0x10572,
	0x3500, 0xffffffff, 0x48,
	0x3504, 0xffffffff, 0x20575,
	0x3500, 0xffffffff, 0x4c,
	0x3504, 0xffffffff, 0x190801,
	0x3500, 0xffffffff, 0x67,
	0x3504, 0xffffffff, 0x1082a,
	0x3500, 0xffffffff, 0x6a,
	0x3504, 0xffffffff, 0x1b082d,
	0x3500, 0xffffffff, 0x87,
	0x3504, 0xffffffff, 0x310851,
	0x3500, 0xffffffff, 0xba,
	0x3504, 0xffffffff, 0x891,
	0x3500, 0xffffffff, 0xbc,
	0x3504, 0xffffffff, 0x893,
	0x3500, 0xffffffff, 0xbe,
	0x3504, 0xffffffff, 0x20895,
	0x3500, 0xffffffff, 0xc2,
	0x3504, 0xffffffff, 0x20899,
	0x3500, 0xffffffff, 0xc6,
	0x3504, 0xffffffff, 0x2089d,
	0x3500, 0xffffffff, 0xca,
	0x3504, 0xffffffff, 0x8a1,
	0x3500, 0xffffffff, 0xcc,
	0x3504, 0xffffffff, 0x8a3,
	0x3500, 0xffffffff, 0xce,
	0x3504, 0xffffffff, 0x308a5,
	0x3500, 0xffffffff, 0xd3,
	0x3504, 0xffffffff, 0x6d08cd,
	0x3500, 0xffffffff, 0x142,
	0x3504, 0xffffffff, 0x2000095a,
	0x3504, 0xffffffff, 0x1,
	0x3500, 0xffffffff, 0x144,
	0x3504, 0xffffffff, 0x301f095b,
	0x3500, 0xffffffff, 0x165,
	0x3504, 0xffffffff, 0xc094d,
	0x3500, 0xffffffff, 0x173,
	0x3504, 0xffffffff, 0xf096d,
	0x3500, 0xffffffff, 0x184,
	0x3504, 0xffffffff, 0x15097f,
	0x3500, 0xffffffff, 0x19b,
	0x3504, 0xffffffff, 0xc0998,
	0x3500, 0xffffffff, 0x1a9,
	0x3504, 0xffffffff, 0x409a7,
	0x3500, 0xffffffff, 0x1af,
	0x3504, 0xffffffff, 0xcdc,
	0x3500, 0xffffffff, 0x1b1,
	0x3504, 0xffffffff, 0x800,
	0x3508, 0xffffffff, 0x6c9b2000,
	0x3510, 0xfc00, 0x2000,
	0x3544, 0xffffffff, 0xfc0,
	0x28d4, 0x00000100, 0x100
पूर्ण;

अटल व्योम si_init_golden_रेजिस्टरs(काष्ठा radeon_device *rdev)
अणु
	चयन (rdev->family) अणु
	हाल CHIP_TAHITI:
		radeon_program_रेजिस्टर_sequence(rdev,
						 tahiti_golden_रेजिस्टरs,
						 (स्थिर u32)ARRAY_SIZE(tahiti_golden_रेजिस्टरs));
		radeon_program_रेजिस्टर_sequence(rdev,
						 tahiti_golden_rlc_रेजिस्टरs,
						 (स्थिर u32)ARRAY_SIZE(tahiti_golden_rlc_रेजिस्टरs));
		radeon_program_रेजिस्टर_sequence(rdev,
						 tahiti_mgcg_cgcg_init,
						 (स्थिर u32)ARRAY_SIZE(tahiti_mgcg_cgcg_init));
		radeon_program_रेजिस्टर_sequence(rdev,
						 tahiti_golden_रेजिस्टरs2,
						 (स्थिर u32)ARRAY_SIZE(tahiti_golden_रेजिस्टरs2));
		अवरोध;
	हाल CHIP_PITCAIRN:
		radeon_program_रेजिस्टर_sequence(rdev,
						 pitcairn_golden_रेजिस्टरs,
						 (स्थिर u32)ARRAY_SIZE(pitcairn_golden_रेजिस्टरs));
		radeon_program_रेजिस्टर_sequence(rdev,
						 pitcairn_golden_rlc_रेजिस्टरs,
						 (स्थिर u32)ARRAY_SIZE(pitcairn_golden_rlc_रेजिस्टरs));
		radeon_program_रेजिस्टर_sequence(rdev,
						 pitcairn_mgcg_cgcg_init,
						 (स्थिर u32)ARRAY_SIZE(pitcairn_mgcg_cgcg_init));
		अवरोध;
	हाल CHIP_VERDE:
		radeon_program_रेजिस्टर_sequence(rdev,
						 verde_golden_रेजिस्टरs,
						 (स्थिर u32)ARRAY_SIZE(verde_golden_रेजिस्टरs));
		radeon_program_रेजिस्टर_sequence(rdev,
						 verde_golden_rlc_रेजिस्टरs,
						 (स्थिर u32)ARRAY_SIZE(verde_golden_rlc_रेजिस्टरs));
		radeon_program_रेजिस्टर_sequence(rdev,
						 verde_mgcg_cgcg_init,
						 (स्थिर u32)ARRAY_SIZE(verde_mgcg_cgcg_init));
		radeon_program_रेजिस्टर_sequence(rdev,
						 verde_pg_init,
						 (स्थिर u32)ARRAY_SIZE(verde_pg_init));
		अवरोध;
	हाल CHIP_OLAND:
		radeon_program_रेजिस्टर_sequence(rdev,
						 oland_golden_रेजिस्टरs,
						 (स्थिर u32)ARRAY_SIZE(oland_golden_रेजिस्टरs));
		radeon_program_रेजिस्टर_sequence(rdev,
						 oland_golden_rlc_रेजिस्टरs,
						 (स्थिर u32)ARRAY_SIZE(oland_golden_rlc_रेजिस्टरs));
		radeon_program_रेजिस्टर_sequence(rdev,
						 oland_mgcg_cgcg_init,
						 (स्थिर u32)ARRAY_SIZE(oland_mgcg_cgcg_init));
		अवरोध;
	हाल CHIP_HAIन_अंक:
		radeon_program_रेजिस्टर_sequence(rdev,
						 hainan_golden_रेजिस्टरs,
						 (स्थिर u32)ARRAY_SIZE(hainan_golden_रेजिस्टरs));
		radeon_program_रेजिस्टर_sequence(rdev,
						 hainan_golden_रेजिस्टरs2,
						 (स्थिर u32)ARRAY_SIZE(hainan_golden_रेजिस्टरs2));
		radeon_program_रेजिस्टर_sequence(rdev,
						 hainan_mgcg_cgcg_init,
						 (स्थिर u32)ARRAY_SIZE(hainan_mgcg_cgcg_init));
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/**
 * si_get_allowed_info_रेजिस्टर - fetch the रेजिस्टर क्रम the info ioctl
 *
 * @rdev: radeon_device poपूर्णांकer
 * @reg: रेजिस्टर offset in bytes
 * @val: रेजिस्टर value
 *
 * Returns 0 क्रम success or -EINVAL क्रम an invalid रेजिस्टर
 *
 */
पूर्णांक si_get_allowed_info_रेजिस्टर(काष्ठा radeon_device *rdev,
				 u32 reg, u32 *val)
अणु
	चयन (reg) अणु
	हाल GRBM_STATUS:
	हाल GRBM_STATUS2:
	हाल GRBM_STATUS_SE0:
	हाल GRBM_STATUS_SE1:
	हाल SRBM_STATUS:
	हाल SRBM_STATUS2:
	हाल (DMA_STATUS_REG + DMA0_REGISTER_OFFSET):
	हाल (DMA_STATUS_REG + DMA1_REGISTER_OFFSET):
	हाल UVD_STATUS:
		*val = RREG32(reg);
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

#घोषणा PCIE_BUS_CLK                10000
#घोषणा TCLK                        (PCIE_BUS_CLK / 10)

/**
 * si_get_xclk - get the xclk
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Returns the reference घड़ी used by the gfx engine
 * (SI).
 */
u32 si_get_xclk(काष्ठा radeon_device *rdev)
अणु
	u32 reference_घड़ी = rdev->घड़ी.spll.reference_freq;
	u32 पंचांगp;

	पंचांगp = RREG32(CG_CLKPIN_CNTL_2);
	अगर (पंचांगp & MUX_TCLK_TO_XCLK)
		वापस TCLK;

	पंचांगp = RREG32(CG_CLKPIN_CNTL);
	अगर (पंचांगp & XTALIN_DIVIDE)
		वापस reference_घड़ी / 4;

	वापस reference_घड़ी;
पूर्ण

/* get temperature in millidegrees */
पूर्णांक si_get_temp(काष्ठा radeon_device *rdev)
अणु
	u32 temp;
	पूर्णांक actual_temp = 0;

	temp = (RREG32(CG_MULT_THERMAL_STATUS) & CTF_TEMP_MASK) >>
		CTF_TEMP_SHIFT;

	अगर (temp & 0x200)
		actual_temp = 255;
	अन्यथा
		actual_temp = temp & 0x1ff;

	actual_temp = (actual_temp * 1000);

	वापस actual_temp;
पूर्ण

#घोषणा TAHITI_IO_MC_REGS_SIZE 36

अटल स्थिर u32 tahiti_io_mc_regs[TAHITI_IO_MC_REGS_SIZE][2] = अणु
	अणु0x0000006f, 0x03044000पूर्ण,
	अणु0x00000070, 0x0480c018पूर्ण,
	अणु0x00000071, 0x00000040पूर्ण,
	अणु0x00000072, 0x01000000पूर्ण,
	अणु0x00000074, 0x000000ffपूर्ण,
	अणु0x00000075, 0x00143400पूर्ण,
	अणु0x00000076, 0x08ec0800पूर्ण,
	अणु0x00000077, 0x040000ccपूर्ण,
	अणु0x00000079, 0x00000000पूर्ण,
	अणु0x0000007a, 0x21000409पूर्ण,
	अणु0x0000007c, 0x00000000पूर्ण,
	अणु0x0000007d, 0xe8000000पूर्ण,
	अणु0x0000007e, 0x044408a8पूर्ण,
	अणु0x0000007f, 0x00000003पूर्ण,
	अणु0x00000080, 0x00000000पूर्ण,
	अणु0x00000081, 0x01000000पूर्ण,
	अणु0x00000082, 0x02000000पूर्ण,
	अणु0x00000083, 0x00000000पूर्ण,
	अणु0x00000084, 0xe3f3e4f4पूर्ण,
	अणु0x00000085, 0x00052024पूर्ण,
	अणु0x00000087, 0x00000000पूर्ण,
	अणु0x00000088, 0x66036603पूर्ण,
	अणु0x00000089, 0x01000000पूर्ण,
	अणु0x0000008b, 0x1c0a0000पूर्ण,
	अणु0x0000008c, 0xff010000पूर्ण,
	अणु0x0000008e, 0xffffefffपूर्ण,
	अणु0x0000008f, 0xfff3efffपूर्ण,
	अणु0x00000090, 0xfff3efbfपूर्ण,
	अणु0x00000094, 0x00101101पूर्ण,
	अणु0x00000095, 0x00000fffपूर्ण,
	अणु0x00000096, 0x00116fffपूर्ण,
	अणु0x00000097, 0x60010000पूर्ण,
	अणु0x00000098, 0x10010000पूर्ण,
	अणु0x00000099, 0x00006000पूर्ण,
	अणु0x0000009a, 0x00001000पूर्ण,
	अणु0x0000009f, 0x00a77400पूर्ण
पूर्ण;

अटल स्थिर u32 pitcairn_io_mc_regs[TAHITI_IO_MC_REGS_SIZE][2] = अणु
	अणु0x0000006f, 0x03044000पूर्ण,
	अणु0x00000070, 0x0480c018पूर्ण,
	अणु0x00000071, 0x00000040पूर्ण,
	अणु0x00000072, 0x01000000पूर्ण,
	अणु0x00000074, 0x000000ffपूर्ण,
	अणु0x00000075, 0x00143400पूर्ण,
	अणु0x00000076, 0x08ec0800पूर्ण,
	अणु0x00000077, 0x040000ccपूर्ण,
	अणु0x00000079, 0x00000000पूर्ण,
	अणु0x0000007a, 0x21000409पूर्ण,
	अणु0x0000007c, 0x00000000पूर्ण,
	अणु0x0000007d, 0xe8000000पूर्ण,
	अणु0x0000007e, 0x044408a8पूर्ण,
	अणु0x0000007f, 0x00000003पूर्ण,
	अणु0x00000080, 0x00000000पूर्ण,
	अणु0x00000081, 0x01000000पूर्ण,
	अणु0x00000082, 0x02000000पूर्ण,
	अणु0x00000083, 0x00000000पूर्ण,
	अणु0x00000084, 0xe3f3e4f4पूर्ण,
	अणु0x00000085, 0x00052024पूर्ण,
	अणु0x00000087, 0x00000000पूर्ण,
	अणु0x00000088, 0x66036603पूर्ण,
	अणु0x00000089, 0x01000000पूर्ण,
	अणु0x0000008b, 0x1c0a0000पूर्ण,
	अणु0x0000008c, 0xff010000पूर्ण,
	अणु0x0000008e, 0xffffefffपूर्ण,
	अणु0x0000008f, 0xfff3efffपूर्ण,
	अणु0x00000090, 0xfff3efbfपूर्ण,
	अणु0x00000094, 0x00101101पूर्ण,
	अणु0x00000095, 0x00000fffपूर्ण,
	अणु0x00000096, 0x00116fffपूर्ण,
	अणु0x00000097, 0x60010000पूर्ण,
	अणु0x00000098, 0x10010000पूर्ण,
	अणु0x00000099, 0x00006000पूर्ण,
	अणु0x0000009a, 0x00001000पूर्ण,
	अणु0x0000009f, 0x00a47400पूर्ण
पूर्ण;

अटल स्थिर u32 verde_io_mc_regs[TAHITI_IO_MC_REGS_SIZE][2] = अणु
	अणु0x0000006f, 0x03044000पूर्ण,
	अणु0x00000070, 0x0480c018पूर्ण,
	अणु0x00000071, 0x00000040पूर्ण,
	अणु0x00000072, 0x01000000पूर्ण,
	अणु0x00000074, 0x000000ffपूर्ण,
	अणु0x00000075, 0x00143400पूर्ण,
	अणु0x00000076, 0x08ec0800पूर्ण,
	अणु0x00000077, 0x040000ccपूर्ण,
	अणु0x00000079, 0x00000000पूर्ण,
	अणु0x0000007a, 0x21000409पूर्ण,
	अणु0x0000007c, 0x00000000पूर्ण,
	अणु0x0000007d, 0xe8000000पूर्ण,
	अणु0x0000007e, 0x044408a8पूर्ण,
	अणु0x0000007f, 0x00000003पूर्ण,
	अणु0x00000080, 0x00000000पूर्ण,
	अणु0x00000081, 0x01000000पूर्ण,
	अणु0x00000082, 0x02000000पूर्ण,
	अणु0x00000083, 0x00000000पूर्ण,
	अणु0x00000084, 0xe3f3e4f4पूर्ण,
	अणु0x00000085, 0x00052024पूर्ण,
	अणु0x00000087, 0x00000000पूर्ण,
	अणु0x00000088, 0x66036603पूर्ण,
	अणु0x00000089, 0x01000000पूर्ण,
	अणु0x0000008b, 0x1c0a0000पूर्ण,
	अणु0x0000008c, 0xff010000पूर्ण,
	अणु0x0000008e, 0xffffefffपूर्ण,
	अणु0x0000008f, 0xfff3efffपूर्ण,
	अणु0x00000090, 0xfff3efbfपूर्ण,
	अणु0x00000094, 0x00101101पूर्ण,
	अणु0x00000095, 0x00000fffपूर्ण,
	अणु0x00000096, 0x00116fffपूर्ण,
	अणु0x00000097, 0x60010000पूर्ण,
	अणु0x00000098, 0x10010000पूर्ण,
	अणु0x00000099, 0x00006000पूर्ण,
	अणु0x0000009a, 0x00001000पूर्ण,
	अणु0x0000009f, 0x00a37400पूर्ण
पूर्ण;

अटल स्थिर u32 oland_io_mc_regs[TAHITI_IO_MC_REGS_SIZE][2] = अणु
	अणु0x0000006f, 0x03044000पूर्ण,
	अणु0x00000070, 0x0480c018पूर्ण,
	अणु0x00000071, 0x00000040पूर्ण,
	अणु0x00000072, 0x01000000पूर्ण,
	अणु0x00000074, 0x000000ffपूर्ण,
	अणु0x00000075, 0x00143400पूर्ण,
	अणु0x00000076, 0x08ec0800पूर्ण,
	अणु0x00000077, 0x040000ccपूर्ण,
	अणु0x00000079, 0x00000000पूर्ण,
	अणु0x0000007a, 0x21000409पूर्ण,
	अणु0x0000007c, 0x00000000पूर्ण,
	अणु0x0000007d, 0xe8000000पूर्ण,
	अणु0x0000007e, 0x044408a8पूर्ण,
	अणु0x0000007f, 0x00000003पूर्ण,
	अणु0x00000080, 0x00000000पूर्ण,
	अणु0x00000081, 0x01000000पूर्ण,
	अणु0x00000082, 0x02000000पूर्ण,
	अणु0x00000083, 0x00000000पूर्ण,
	अणु0x00000084, 0xe3f3e4f4पूर्ण,
	अणु0x00000085, 0x00052024पूर्ण,
	अणु0x00000087, 0x00000000पूर्ण,
	अणु0x00000088, 0x66036603पूर्ण,
	अणु0x00000089, 0x01000000पूर्ण,
	अणु0x0000008b, 0x1c0a0000पूर्ण,
	अणु0x0000008c, 0xff010000पूर्ण,
	अणु0x0000008e, 0xffffefffपूर्ण,
	अणु0x0000008f, 0xfff3efffपूर्ण,
	अणु0x00000090, 0xfff3efbfपूर्ण,
	अणु0x00000094, 0x00101101पूर्ण,
	अणु0x00000095, 0x00000fffपूर्ण,
	अणु0x00000096, 0x00116fffपूर्ण,
	अणु0x00000097, 0x60010000पूर्ण,
	अणु0x00000098, 0x10010000पूर्ण,
	अणु0x00000099, 0x00006000पूर्ण,
	अणु0x0000009a, 0x00001000पूर्ण,
	अणु0x0000009f, 0x00a17730पूर्ण
पूर्ण;

अटल स्थिर u32 hainan_io_mc_regs[TAHITI_IO_MC_REGS_SIZE][2] = अणु
	अणु0x0000006f, 0x03044000पूर्ण,
	अणु0x00000070, 0x0480c018पूर्ण,
	अणु0x00000071, 0x00000040पूर्ण,
	अणु0x00000072, 0x01000000पूर्ण,
	अणु0x00000074, 0x000000ffपूर्ण,
	अणु0x00000075, 0x00143400पूर्ण,
	अणु0x00000076, 0x08ec0800पूर्ण,
	अणु0x00000077, 0x040000ccपूर्ण,
	अणु0x00000079, 0x00000000पूर्ण,
	अणु0x0000007a, 0x21000409पूर्ण,
	अणु0x0000007c, 0x00000000पूर्ण,
	अणु0x0000007d, 0xe8000000पूर्ण,
	अणु0x0000007e, 0x044408a8पूर्ण,
	अणु0x0000007f, 0x00000003पूर्ण,
	अणु0x00000080, 0x00000000पूर्ण,
	अणु0x00000081, 0x01000000पूर्ण,
	अणु0x00000082, 0x02000000पूर्ण,
	अणु0x00000083, 0x00000000पूर्ण,
	अणु0x00000084, 0xe3f3e4f4पूर्ण,
	अणु0x00000085, 0x00052024पूर्ण,
	अणु0x00000087, 0x00000000पूर्ण,
	अणु0x00000088, 0x66036603पूर्ण,
	अणु0x00000089, 0x01000000पूर्ण,
	अणु0x0000008b, 0x1c0a0000पूर्ण,
	अणु0x0000008c, 0xff010000पूर्ण,
	अणु0x0000008e, 0xffffefffपूर्ण,
	अणु0x0000008f, 0xfff3efffपूर्ण,
	अणु0x00000090, 0xfff3efbfपूर्ण,
	अणु0x00000094, 0x00101101पूर्ण,
	अणु0x00000095, 0x00000fffपूर्ण,
	अणु0x00000096, 0x00116fffपूर्ण,
	अणु0x00000097, 0x60010000पूर्ण,
	अणु0x00000098, 0x10010000पूर्ण,
	अणु0x00000099, 0x00006000पूर्ण,
	अणु0x0000009a, 0x00001000पूर्ण,
	अणु0x0000009f, 0x00a07730पूर्ण
पूर्ण;

/* ucode loading */
पूर्णांक si_mc_load_microcode(काष्ठा radeon_device *rdev)
अणु
	स्थिर __be32 *fw_data = शून्य;
	स्थिर __le32 *new_fw_data = शून्य;
	u32 running;
	u32 *io_mc_regs = शून्य;
	स्थिर __le32 *new_io_mc_regs = शून्य;
	पूर्णांक i, regs_size, ucode_size;

	अगर (!rdev->mc_fw)
		वापस -EINVAL;

	अगर (rdev->new_fw) अणु
		स्थिर काष्ठा mc_firmware_header_v1_0 *hdr =
			(स्थिर काष्ठा mc_firmware_header_v1_0 *)rdev->mc_fw->data;

		radeon_ucode_prपूर्णांक_mc_hdr(&hdr->header);
		regs_size = le32_to_cpu(hdr->io_debug_size_bytes) / (4 * 2);
		new_io_mc_regs = (स्थिर __le32 *)
			(rdev->mc_fw->data + le32_to_cpu(hdr->io_debug_array_offset_bytes));
		ucode_size = le32_to_cpu(hdr->header.ucode_size_bytes) / 4;
		new_fw_data = (स्थिर __le32 *)
			(rdev->mc_fw->data + le32_to_cpu(hdr->header.ucode_array_offset_bytes));
	पूर्ण अन्यथा अणु
		ucode_size = rdev->mc_fw->size / 4;

		चयन (rdev->family) अणु
		हाल CHIP_TAHITI:
			io_mc_regs = (u32 *)&tahiti_io_mc_regs;
			regs_size = TAHITI_IO_MC_REGS_SIZE;
			अवरोध;
		हाल CHIP_PITCAIRN:
			io_mc_regs = (u32 *)&pitcairn_io_mc_regs;
			regs_size = TAHITI_IO_MC_REGS_SIZE;
			अवरोध;
		हाल CHIP_VERDE:
		शेष:
			io_mc_regs = (u32 *)&verde_io_mc_regs;
			regs_size = TAHITI_IO_MC_REGS_SIZE;
			अवरोध;
		हाल CHIP_OLAND:
			io_mc_regs = (u32 *)&oland_io_mc_regs;
			regs_size = TAHITI_IO_MC_REGS_SIZE;
			अवरोध;
		हाल CHIP_HAIन_अंक:
			io_mc_regs = (u32 *)&hainan_io_mc_regs;
			regs_size = TAHITI_IO_MC_REGS_SIZE;
			अवरोध;
		पूर्ण
		fw_data = (स्थिर __be32 *)rdev->mc_fw->data;
	पूर्ण

	running = RREG32(MC_SEQ_SUP_CNTL) & RUN_MASK;

	अगर (running == 0) अणु
		/* reset the engine and set to writable */
		WREG32(MC_SEQ_SUP_CNTL, 0x00000008);
		WREG32(MC_SEQ_SUP_CNTL, 0x00000010);

		/* load mc io regs */
		क्रम (i = 0; i < regs_size; i++) अणु
			अगर (rdev->new_fw) अणु
				WREG32(MC_SEQ_IO_DEBUG_INDEX, le32_to_cpup(new_io_mc_regs++));
				WREG32(MC_SEQ_IO_DEBUG_DATA, le32_to_cpup(new_io_mc_regs++));
			पूर्ण अन्यथा अणु
				WREG32(MC_SEQ_IO_DEBUG_INDEX, io_mc_regs[(i << 1)]);
				WREG32(MC_SEQ_IO_DEBUG_DATA, io_mc_regs[(i << 1) + 1]);
			पूर्ण
		पूर्ण
		/* load the MC ucode */
		क्रम (i = 0; i < ucode_size; i++) अणु
			अगर (rdev->new_fw)
				WREG32(MC_SEQ_SUP_PGM, le32_to_cpup(new_fw_data++));
			अन्यथा
				WREG32(MC_SEQ_SUP_PGM, be32_to_cpup(fw_data++));
		पूर्ण

		/* put the engine back पूर्णांकo the active state */
		WREG32(MC_SEQ_SUP_CNTL, 0x00000008);
		WREG32(MC_SEQ_SUP_CNTL, 0x00000004);
		WREG32(MC_SEQ_SUP_CNTL, 0x00000001);

		/* रुको क्रम training to complete */
		क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
			अगर (RREG32(MC_SEQ_TRAIN_WAKEUP_CNTL) & TRAIN_DONE_D0)
				अवरोध;
			udelay(1);
		पूर्ण
		क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
			अगर (RREG32(MC_SEQ_TRAIN_WAKEUP_CNTL) & TRAIN_DONE_D1)
				अवरोध;
			udelay(1);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक si_init_microcode(काष्ठा radeon_device *rdev)
अणु
	स्थिर अक्षर *chip_name;
	स्थिर अक्षर *new_chip_name;
	माप_प्रकार pfp_req_size, me_req_size, ce_req_size, rlc_req_size, mc_req_size;
	माप_प्रकार smc_req_size, mc2_req_size;
	अक्षर fw_name[30];
	पूर्णांक err;
	पूर्णांक new_fw = 0;
	bool new_smc = false;
	bool si58_fw = false;
	bool banks2_fw = false;

	DRM_DEBUG("\n");

	चयन (rdev->family) अणु
	हाल CHIP_TAHITI:
		chip_name = "TAHITI";
		new_chip_name = "tahiti";
		pfp_req_size = SI_PFP_UCODE_SIZE * 4;
		me_req_size = SI_PM4_UCODE_SIZE * 4;
		ce_req_size = SI_CE_UCODE_SIZE * 4;
		rlc_req_size = SI_RLC_UCODE_SIZE * 4;
		mc_req_size = SI_MC_UCODE_SIZE * 4;
		mc2_req_size = TAHITI_MC_UCODE_SIZE * 4;
		smc_req_size = ALIGN(TAHITI_SMC_UCODE_SIZE, 4);
		अवरोध;
	हाल CHIP_PITCAIRN:
		chip_name = "PITCAIRN";
		अगर ((rdev->pdev->revision == 0x81) &&
		    ((rdev->pdev->device == 0x6810) ||
		     (rdev->pdev->device == 0x6811)))
			new_smc = true;
		new_chip_name = "pitcairn";
		pfp_req_size = SI_PFP_UCODE_SIZE * 4;
		me_req_size = SI_PM4_UCODE_SIZE * 4;
		ce_req_size = SI_CE_UCODE_SIZE * 4;
		rlc_req_size = SI_RLC_UCODE_SIZE * 4;
		mc_req_size = SI_MC_UCODE_SIZE * 4;
		mc2_req_size = PITCAIRN_MC_UCODE_SIZE * 4;
		smc_req_size = ALIGN(PITCAIRN_SMC_UCODE_SIZE, 4);
		अवरोध;
	हाल CHIP_VERDE:
		chip_name = "VERDE";
		अगर (((rdev->pdev->device == 0x6820) &&
		     ((rdev->pdev->revision == 0x81) ||
		      (rdev->pdev->revision == 0x83))) ||
		    ((rdev->pdev->device == 0x6821) &&
		     ((rdev->pdev->revision == 0x83) ||
		      (rdev->pdev->revision == 0x87))) ||
		    ((rdev->pdev->revision == 0x87) &&
		     ((rdev->pdev->device == 0x6823) ||
		      (rdev->pdev->device == 0x682b))))
			new_smc = true;
		new_chip_name = "verde";
		pfp_req_size = SI_PFP_UCODE_SIZE * 4;
		me_req_size = SI_PM4_UCODE_SIZE * 4;
		ce_req_size = SI_CE_UCODE_SIZE * 4;
		rlc_req_size = SI_RLC_UCODE_SIZE * 4;
		mc_req_size = SI_MC_UCODE_SIZE * 4;
		mc2_req_size = VERDE_MC_UCODE_SIZE * 4;
		smc_req_size = ALIGN(VERDE_SMC_UCODE_SIZE, 4);
		अवरोध;
	हाल CHIP_OLAND:
		chip_name = "OLAND";
		अगर (((rdev->pdev->revision == 0x81) &&
		     ((rdev->pdev->device == 0x6600) ||
		      (rdev->pdev->device == 0x6604) ||
		      (rdev->pdev->device == 0x6605) ||
		      (rdev->pdev->device == 0x6610))) ||
		    ((rdev->pdev->revision == 0x83) &&
		     (rdev->pdev->device == 0x6610)))
			new_smc = true;
		new_chip_name = "oland";
		pfp_req_size = SI_PFP_UCODE_SIZE * 4;
		me_req_size = SI_PM4_UCODE_SIZE * 4;
		ce_req_size = SI_CE_UCODE_SIZE * 4;
		rlc_req_size = SI_RLC_UCODE_SIZE * 4;
		mc_req_size = mc2_req_size = OLAND_MC_UCODE_SIZE * 4;
		smc_req_size = ALIGN(OLAND_SMC_UCODE_SIZE, 4);
		अवरोध;
	हाल CHIP_HAIन_अंक:
		chip_name = "HAINAN";
		अगर (((rdev->pdev->revision == 0x81) &&
		     (rdev->pdev->device == 0x6660)) ||
		    ((rdev->pdev->revision == 0x83) &&
		     ((rdev->pdev->device == 0x6660) ||
		      (rdev->pdev->device == 0x6663) ||
		      (rdev->pdev->device == 0x6665) ||
		      (rdev->pdev->device == 0x6667))))
			new_smc = true;
		अन्यथा अगर ((rdev->pdev->revision == 0xc3) &&
			 (rdev->pdev->device == 0x6665))
			banks2_fw = true;
		new_chip_name = "hainan";
		pfp_req_size = SI_PFP_UCODE_SIZE * 4;
		me_req_size = SI_PM4_UCODE_SIZE * 4;
		ce_req_size = SI_CE_UCODE_SIZE * 4;
		rlc_req_size = SI_RLC_UCODE_SIZE * 4;
		mc_req_size = mc2_req_size = OLAND_MC_UCODE_SIZE * 4;
		smc_req_size = ALIGN(HAIन_अंक_SMC_UCODE_SIZE, 4);
		अवरोध;
	शेष: BUG();
	पूर्ण

	/* this memory configuration requires special firmware */
	अगर (((RREG32(MC_SEQ_MISC0) & 0xff000000) >> 24) == 0x58)
		si58_fw = true;

	DRM_INFO("Loading %s Microcode\n", new_chip_name);

	snम_लिखो(fw_name, माप(fw_name), "radeon/%s_pfp.bin", new_chip_name);
	err = request_firmware(&rdev->pfp_fw, fw_name, rdev->dev);
	अगर (err) अणु
		snम_लिखो(fw_name, माप(fw_name), "radeon/%s_pfp.bin", chip_name);
		err = request_firmware(&rdev->pfp_fw, fw_name, rdev->dev);
		अगर (err)
			जाओ out;
		अगर (rdev->pfp_fw->size != pfp_req_size) अणु
			pr_err("si_cp: Bogus length %zu in firmware \"%s\"\n",
			       rdev->pfp_fw->size, fw_name);
			err = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		err = radeon_ucode_validate(rdev->pfp_fw);
		अगर (err) अणु
			pr_err("si_cp: validation failed for firmware \"%s\"\n",
			       fw_name);
			जाओ out;
		पूर्ण अन्यथा अणु
			new_fw++;
		पूर्ण
	पूर्ण

	snम_लिखो(fw_name, माप(fw_name), "radeon/%s_me.bin", new_chip_name);
	err = request_firmware(&rdev->me_fw, fw_name, rdev->dev);
	अगर (err) अणु
		snम_लिखो(fw_name, माप(fw_name), "radeon/%s_me.bin", chip_name);
		err = request_firmware(&rdev->me_fw, fw_name, rdev->dev);
		अगर (err)
			जाओ out;
		अगर (rdev->me_fw->size != me_req_size) अणु
			pr_err("si_cp: Bogus length %zu in firmware \"%s\"\n",
			       rdev->me_fw->size, fw_name);
			err = -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		err = radeon_ucode_validate(rdev->me_fw);
		अगर (err) अणु
			pr_err("si_cp: validation failed for firmware \"%s\"\n",
			       fw_name);
			जाओ out;
		पूर्ण अन्यथा अणु
			new_fw++;
		पूर्ण
	पूर्ण

	snम_लिखो(fw_name, माप(fw_name), "radeon/%s_ce.bin", new_chip_name);
	err = request_firmware(&rdev->ce_fw, fw_name, rdev->dev);
	अगर (err) अणु
		snम_लिखो(fw_name, माप(fw_name), "radeon/%s_ce.bin", chip_name);
		err = request_firmware(&rdev->ce_fw, fw_name, rdev->dev);
		अगर (err)
			जाओ out;
		अगर (rdev->ce_fw->size != ce_req_size) अणु
			pr_err("si_cp: Bogus length %zu in firmware \"%s\"\n",
			       rdev->ce_fw->size, fw_name);
			err = -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		err = radeon_ucode_validate(rdev->ce_fw);
		अगर (err) अणु
			pr_err("si_cp: validation failed for firmware \"%s\"\n",
			       fw_name);
			जाओ out;
		पूर्ण अन्यथा अणु
			new_fw++;
		पूर्ण
	पूर्ण

	snम_लिखो(fw_name, माप(fw_name), "radeon/%s_rlc.bin", new_chip_name);
	err = request_firmware(&rdev->rlc_fw, fw_name, rdev->dev);
	अगर (err) अणु
		snम_लिखो(fw_name, माप(fw_name), "radeon/%s_rlc.bin", chip_name);
		err = request_firmware(&rdev->rlc_fw, fw_name, rdev->dev);
		अगर (err)
			जाओ out;
		अगर (rdev->rlc_fw->size != rlc_req_size) अणु
			pr_err("si_rlc: Bogus length %zu in firmware \"%s\"\n",
			       rdev->rlc_fw->size, fw_name);
			err = -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		err = radeon_ucode_validate(rdev->rlc_fw);
		अगर (err) अणु
			pr_err("si_cp: validation failed for firmware \"%s\"\n",
			       fw_name);
			जाओ out;
		पूर्ण अन्यथा अणु
			new_fw++;
		पूर्ण
	पूर्ण

	अगर (si58_fw)
		snम_लिखो(fw_name, माप(fw_name), "radeon/si58_mc.bin");
	अन्यथा
		snम_लिखो(fw_name, माप(fw_name), "radeon/%s_mc.bin", new_chip_name);
	err = request_firmware(&rdev->mc_fw, fw_name, rdev->dev);
	अगर (err) अणु
		snम_लिखो(fw_name, माप(fw_name), "radeon/%s_mc2.bin", chip_name);
		err = request_firmware(&rdev->mc_fw, fw_name, rdev->dev);
		अगर (err) अणु
			snम_लिखो(fw_name, माप(fw_name), "radeon/%s_mc.bin", chip_name);
			err = request_firmware(&rdev->mc_fw, fw_name, rdev->dev);
			अगर (err)
				जाओ out;
		पूर्ण
		अगर ((rdev->mc_fw->size != mc_req_size) &&
		    (rdev->mc_fw->size != mc2_req_size)) अणु
			pr_err("si_mc: Bogus length %zu in firmware \"%s\"\n",
			       rdev->mc_fw->size, fw_name);
			err = -EINVAL;
		पूर्ण
		DRM_INFO("%s: %zu bytes\n", fw_name, rdev->mc_fw->size);
	पूर्ण अन्यथा अणु
		err = radeon_ucode_validate(rdev->mc_fw);
		अगर (err) अणु
			pr_err("si_cp: validation failed for firmware \"%s\"\n",
			       fw_name);
			जाओ out;
		पूर्ण अन्यथा अणु
			new_fw++;
		पूर्ण
	पूर्ण

	अगर (banks2_fw)
		snम_लिखो(fw_name, माप(fw_name), "radeon/banks_k_2_smc.bin");
	अन्यथा अगर (new_smc)
		snम_लिखो(fw_name, माप(fw_name), "radeon/%s_k_smc.bin", new_chip_name);
	अन्यथा
		snम_लिखो(fw_name, माप(fw_name), "radeon/%s_smc.bin", new_chip_name);
	err = request_firmware(&rdev->smc_fw, fw_name, rdev->dev);
	अगर (err) अणु
		snम_लिखो(fw_name, माप(fw_name), "radeon/%s_smc.bin", chip_name);
		err = request_firmware(&rdev->smc_fw, fw_name, rdev->dev);
		अगर (err) अणु
			pr_err("smc: error loading firmware \"%s\"\n", fw_name);
			release_firmware(rdev->smc_fw);
			rdev->smc_fw = शून्य;
			err = 0;
		पूर्ण अन्यथा अगर (rdev->smc_fw->size != smc_req_size) अणु
			pr_err("si_smc: Bogus length %zu in firmware \"%s\"\n",
			       rdev->smc_fw->size, fw_name);
			err = -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		err = radeon_ucode_validate(rdev->smc_fw);
		अगर (err) अणु
			pr_err("si_cp: validation failed for firmware \"%s\"\n",
			       fw_name);
			जाओ out;
		पूर्ण अन्यथा अणु
			new_fw++;
		पूर्ण
	पूर्ण

	अगर (new_fw == 0) अणु
		rdev->new_fw = false;
	पूर्ण अन्यथा अगर (new_fw < 6) अणु
		pr_err("si_fw: mixing new and old firmware!\n");
		err = -EINVAL;
	पूर्ण अन्यथा अणु
		rdev->new_fw = true;
	पूर्ण
out:
	अगर (err) अणु
		अगर (err != -EINVAL)
			pr_err("si_cp: Failed to load firmware \"%s\"\n",
			       fw_name);
		release_firmware(rdev->pfp_fw);
		rdev->pfp_fw = शून्य;
		release_firmware(rdev->me_fw);
		rdev->me_fw = शून्य;
		release_firmware(rdev->ce_fw);
		rdev->ce_fw = शून्य;
		release_firmware(rdev->rlc_fw);
		rdev->rlc_fw = शून्य;
		release_firmware(rdev->mc_fw);
		rdev->mc_fw = शून्य;
		release_firmware(rdev->smc_fw);
		rdev->smc_fw = शून्य;
	पूर्ण
	वापस err;
पूर्ण

/* watermark setup */
अटल u32 dce6_line_buffer_adjust(काष्ठा radeon_device *rdev,
				   काष्ठा radeon_crtc *radeon_crtc,
				   काष्ठा drm_display_mode *mode,
				   काष्ठा drm_display_mode *other_mode)
अणु
	u32 पंचांगp, buffer_alloc, i;
	u32 pipe_offset = radeon_crtc->crtc_id * 0x20;
	/*
	 * Line Buffer Setup
	 * There are 3 line buffers, each one shared by 2 display controllers.
	 * DC_LB_MEMORY_SPLIT controls how that line buffer is shared between
	 * the display controllers.  The paritioning is करोne via one of four
	 * preset allocations specअगरied in bits 21:20:
	 *  0 - half lb
	 *  2 - whole lb, other crtc must be disabled
	 */
	/* this can get tricky अगर we have two large displays on a paired group
	 * of crtcs.  Ideally क्रम multiple large displays we'd assign them to
	 * non-linked crtcs क्रम maximum line buffer allocation.
	 */
	अगर (radeon_crtc->base.enabled && mode) अणु
		अगर (other_mode) अणु
			पंचांगp = 0; /* 1/2 */
			buffer_alloc = 1;
		पूर्ण अन्यथा अणु
			पंचांगp = 2; /* whole */
			buffer_alloc = 2;
		पूर्ण
	पूर्ण अन्यथा अणु
		पंचांगp = 0;
		buffer_alloc = 0;
	पूर्ण

	WREG32(DC_LB_MEMORY_SPLIT + radeon_crtc->crtc_offset,
	       DC_LB_MEMORY_CONFIG(पंचांगp));

	WREG32(PIPE0_DMIF_BUFFER_CONTROL + pipe_offset,
	       DMIF_BUFFERS_ALLOCATED(buffer_alloc));
	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		अगर (RREG32(PIPE0_DMIF_BUFFER_CONTROL + pipe_offset) &
		    DMIF_BUFFERS_ALLOCATED_COMPLETED)
			अवरोध;
		udelay(1);
	पूर्ण

	अगर (radeon_crtc->base.enabled && mode) अणु
		चयन (पंचांगp) अणु
		हाल 0:
		शेष:
			वापस 4096 * 2;
		हाल 2:
			वापस 8192 * 2;
		पूर्ण
	पूर्ण

	/* controller not enabled, so no lb used */
	वापस 0;
पूर्ण

अटल u32 si_get_number_of_dram_channels(काष्ठा radeon_device *rdev)
अणु
	u32 पंचांगp = RREG32(MC_SHARED_CHMAP);

	चयन ((पंचांगp & NOOFCHAN_MASK) >> NOOFCHAN_SHIFT) अणु
	हाल 0:
	शेष:
		वापस 1;
	हाल 1:
		वापस 2;
	हाल 2:
		वापस 4;
	हाल 3:
		वापस 8;
	हाल 4:
		वापस 3;
	हाल 5:
		वापस 6;
	हाल 6:
		वापस 10;
	हाल 7:
		वापस 12;
	हाल 8:
		वापस 16;
	पूर्ण
पूर्ण

काष्ठा dce6_wm_params अणु
	u32 dram_channels; /* number of dram channels */
	u32 yclk;          /* bandwidth per dram data pin in kHz */
	u32 sclk;          /* engine घड़ी in kHz */
	u32 disp_clk;      /* display घड़ी in kHz */
	u32 src_width;     /* viewport width */
	u32 active_समय;   /* active display समय in ns */
	u32 blank_समय;    /* blank समय in ns */
	bool पूर्णांकerlaced;    /* mode is पूर्णांकerlaced */
	fixed20_12 vsc;    /* vertical scale ratio */
	u32 num_heads;     /* number of active crtcs */
	u32 bytes_per_pixel; /* bytes per pixel display + overlay */
	u32 lb_size;       /* line buffer allocated to pipe */
	u32 vtaps;         /* vertical scaler taps */
पूर्ण;

अटल u32 dce6_dram_bandwidth(काष्ठा dce6_wm_params *wm)
अणु
	/* Calculate raw DRAM Bandwidth */
	fixed20_12 dram_efficiency; /* 0.7 */
	fixed20_12 yclk, dram_channels, bandwidth;
	fixed20_12 a;

	a.full = dfixed_स्थिर(1000);
	yclk.full = dfixed_स्थिर(wm->yclk);
	yclk.full = dfixed_भाग(yclk, a);
	dram_channels.full = dfixed_स्थिर(wm->dram_channels * 4);
	a.full = dfixed_स्थिर(10);
	dram_efficiency.full = dfixed_स्थिर(7);
	dram_efficiency.full = dfixed_भाग(dram_efficiency, a);
	bandwidth.full = dfixed_mul(dram_channels, yclk);
	bandwidth.full = dfixed_mul(bandwidth, dram_efficiency);

	वापस dfixed_trunc(bandwidth);
पूर्ण

अटल u32 dce6_dram_bandwidth_क्रम_display(काष्ठा dce6_wm_params *wm)
अणु
	/* Calculate DRAM Bandwidth and the part allocated to display. */
	fixed20_12 disp_dram_allocation; /* 0.3 to 0.7 */
	fixed20_12 yclk, dram_channels, bandwidth;
	fixed20_12 a;

	a.full = dfixed_स्थिर(1000);
	yclk.full = dfixed_स्थिर(wm->yclk);
	yclk.full = dfixed_भाग(yclk, a);
	dram_channels.full = dfixed_स्थिर(wm->dram_channels * 4);
	a.full = dfixed_स्थिर(10);
	disp_dram_allocation.full = dfixed_स्थिर(3); /* XXX worse हाल value 0.3 */
	disp_dram_allocation.full = dfixed_भाग(disp_dram_allocation, a);
	bandwidth.full = dfixed_mul(dram_channels, yclk);
	bandwidth.full = dfixed_mul(bandwidth, disp_dram_allocation);

	वापस dfixed_trunc(bandwidth);
पूर्ण

अटल u32 dce6_data_वापस_bandwidth(काष्ठा dce6_wm_params *wm)
अणु
	/* Calculate the display Data वापस Bandwidth */
	fixed20_12 वापस_efficiency; /* 0.8 */
	fixed20_12 sclk, bandwidth;
	fixed20_12 a;

	a.full = dfixed_स्थिर(1000);
	sclk.full = dfixed_स्थिर(wm->sclk);
	sclk.full = dfixed_भाग(sclk, a);
	a.full = dfixed_स्थिर(10);
	वापस_efficiency.full = dfixed_स्थिर(8);
	वापस_efficiency.full = dfixed_भाग(वापस_efficiency, a);
	a.full = dfixed_स्थिर(32);
	bandwidth.full = dfixed_mul(a, sclk);
	bandwidth.full = dfixed_mul(bandwidth, वापस_efficiency);

	वापस dfixed_trunc(bandwidth);
पूर्ण

अटल u32 dce6_get_dmअगर_bytes_per_request(काष्ठा dce6_wm_params *wm)
अणु
	वापस 32;
पूर्ण

अटल u32 dce6_dmअगर_request_bandwidth(काष्ठा dce6_wm_params *wm)
अणु
	/* Calculate the DMIF Request Bandwidth */
	fixed20_12 disp_clk_request_efficiency; /* 0.8 */
	fixed20_12 disp_clk, sclk, bandwidth;
	fixed20_12 a, b1, b2;
	u32 min_bandwidth;

	a.full = dfixed_स्थिर(1000);
	disp_clk.full = dfixed_स्थिर(wm->disp_clk);
	disp_clk.full = dfixed_भाग(disp_clk, a);
	a.full = dfixed_स्थिर(dce6_get_dmअगर_bytes_per_request(wm) / 2);
	b1.full = dfixed_mul(a, disp_clk);

	a.full = dfixed_स्थिर(1000);
	sclk.full = dfixed_स्थिर(wm->sclk);
	sclk.full = dfixed_भाग(sclk, a);
	a.full = dfixed_स्थिर(dce6_get_dmअगर_bytes_per_request(wm));
	b2.full = dfixed_mul(a, sclk);

	a.full = dfixed_स्थिर(10);
	disp_clk_request_efficiency.full = dfixed_स्थिर(8);
	disp_clk_request_efficiency.full = dfixed_भाग(disp_clk_request_efficiency, a);

	min_bandwidth = min(dfixed_trunc(b1), dfixed_trunc(b2));

	a.full = dfixed_स्थिर(min_bandwidth);
	bandwidth.full = dfixed_mul(a, disp_clk_request_efficiency);

	वापस dfixed_trunc(bandwidth);
पूर्ण

अटल u32 dce6_available_bandwidth(काष्ठा dce6_wm_params *wm)
अणु
	/* Calculate the Available bandwidth. Display can use this temporarily but not in average. */
	u32 dram_bandwidth = dce6_dram_bandwidth(wm);
	u32 data_वापस_bandwidth = dce6_data_वापस_bandwidth(wm);
	u32 dmअगर_req_bandwidth = dce6_dmअगर_request_bandwidth(wm);

	वापस min(dram_bandwidth, min(data_वापस_bandwidth, dmअगर_req_bandwidth));
पूर्ण

अटल u32 dce6_average_bandwidth(काष्ठा dce6_wm_params *wm)
अणु
	/* Calculate the display mode Average Bandwidth
	 * DisplayMode should contain the source and destination dimensions,
	 * timing, etc.
	 */
	fixed20_12 bpp;
	fixed20_12 line_समय;
	fixed20_12 src_width;
	fixed20_12 bandwidth;
	fixed20_12 a;

	a.full = dfixed_स्थिर(1000);
	line_समय.full = dfixed_स्थिर(wm->active_समय + wm->blank_समय);
	line_समय.full = dfixed_भाग(line_समय, a);
	bpp.full = dfixed_स्थिर(wm->bytes_per_pixel);
	src_width.full = dfixed_स्थिर(wm->src_width);
	bandwidth.full = dfixed_mul(src_width, bpp);
	bandwidth.full = dfixed_mul(bandwidth, wm->vsc);
	bandwidth.full = dfixed_भाग(bandwidth, line_समय);

	वापस dfixed_trunc(bandwidth);
पूर्ण

अटल u32 dce6_latency_watermark(काष्ठा dce6_wm_params *wm)
अणु
	/* First calcualte the latency in ns */
	u32 mc_latency = 2000; /* 2000 ns. */
	u32 available_bandwidth = dce6_available_bandwidth(wm);
	u32 worst_chunk_वापस_समय = (512 * 8 * 1000) / available_bandwidth;
	u32 cursor_line_pair_वापस_समय = (128 * 4 * 1000) / available_bandwidth;
	u32 dc_latency = 40000000 / wm->disp_clk; /* dc pipe latency */
	u32 other_heads_data_वापस_समय = ((wm->num_heads + 1) * worst_chunk_वापस_समय) +
		(wm->num_heads * cursor_line_pair_वापस_समय);
	u32 latency = mc_latency + other_heads_data_वापस_समय + dc_latency;
	u32 max_src_lines_per_dst_line, lb_fill_bw, line_fill_समय;
	u32 पंचांगp, dmअगर_size = 12288;
	fixed20_12 a, b, c;

	अगर (wm->num_heads == 0)
		वापस 0;

	a.full = dfixed_स्थिर(2);
	b.full = dfixed_स्थिर(1);
	अगर ((wm->vsc.full > a.full) ||
	    ((wm->vsc.full > b.full) && (wm->vtaps >= 3)) ||
	    (wm->vtaps >= 5) ||
	    ((wm->vsc.full >= a.full) && wm->पूर्णांकerlaced))
		max_src_lines_per_dst_line = 4;
	अन्यथा
		max_src_lines_per_dst_line = 2;

	a.full = dfixed_स्थिर(available_bandwidth);
	b.full = dfixed_स्थिर(wm->num_heads);
	a.full = dfixed_भाग(a, b);
	पंचांगp = भाग_u64((u64) dmअगर_size * (u64) wm->disp_clk, mc_latency + 512);
	पंचांगp = min(dfixed_trunc(a), पंचांगp);

	lb_fill_bw = min(पंचांगp, wm->disp_clk * wm->bytes_per_pixel / 1000);

	a.full = dfixed_स्थिर(max_src_lines_per_dst_line * wm->src_width * wm->bytes_per_pixel);
	b.full = dfixed_स्थिर(1000);
	c.full = dfixed_स्थिर(lb_fill_bw);
	b.full = dfixed_भाग(c, b);
	a.full = dfixed_भाग(a, b);
	line_fill_समय = dfixed_trunc(a);

	अगर (line_fill_समय < wm->active_समय)
		वापस latency;
	अन्यथा
		वापस latency + (line_fill_समय - wm->active_समय);

पूर्ण

अटल bool dce6_average_bandwidth_vs_dram_bandwidth_क्रम_display(काष्ठा dce6_wm_params *wm)
अणु
	अगर (dce6_average_bandwidth(wm) <=
	    (dce6_dram_bandwidth_क्रम_display(wm) / wm->num_heads))
		वापस true;
	अन्यथा
		वापस false;
पूर्ण;

अटल bool dce6_average_bandwidth_vs_available_bandwidth(काष्ठा dce6_wm_params *wm)
अणु
	अगर (dce6_average_bandwidth(wm) <=
	    (dce6_available_bandwidth(wm) / wm->num_heads))
		वापस true;
	अन्यथा
		वापस false;
पूर्ण;

अटल bool dce6_check_latency_hiding(काष्ठा dce6_wm_params *wm)
अणु
	u32 lb_partitions = wm->lb_size / wm->src_width;
	u32 line_समय = wm->active_समय + wm->blank_समय;
	u32 latency_tolerant_lines;
	u32 latency_hiding;
	fixed20_12 a;

	a.full = dfixed_स्थिर(1);
	अगर (wm->vsc.full > a.full)
		latency_tolerant_lines = 1;
	अन्यथा अणु
		अगर (lb_partitions <= (wm->vtaps + 1))
			latency_tolerant_lines = 1;
		अन्यथा
			latency_tolerant_lines = 2;
	पूर्ण

	latency_hiding = (latency_tolerant_lines * line_समय + wm->blank_समय);

	अगर (dce6_latency_watermark(wm) <= latency_hiding)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल व्योम dce6_program_watermarks(काष्ठा radeon_device *rdev,
					 काष्ठा radeon_crtc *radeon_crtc,
					 u32 lb_size, u32 num_heads)
अणु
	काष्ठा drm_display_mode *mode = &radeon_crtc->base.mode;
	काष्ठा dce6_wm_params wm_low, wm_high;
	u32 dram_channels;
	u32 active_समय;
	u32 line_समय = 0;
	u32 latency_watermark_a = 0, latency_watermark_b = 0;
	u32 priority_a_mark = 0, priority_b_mark = 0;
	u32 priority_a_cnt = PRIORITY_OFF;
	u32 priority_b_cnt = PRIORITY_OFF;
	u32 पंचांगp, arb_control3;
	fixed20_12 a, b, c;

	अगर (radeon_crtc->base.enabled && num_heads && mode) अणु
		active_समय = (u32) भाग_u64((u64)mode->crtc_hdisplay * 1000000,
					    (u32)mode->घड़ी);
		line_समय = (u32) भाग_u64((u64)mode->crtc_htotal * 1000000,
					  (u32)mode->घड़ी);
		line_समय = min(line_समय, (u32)65535);
		priority_a_cnt = 0;
		priority_b_cnt = 0;

		अगर (rdev->family == CHIP_ARUBA)
			dram_channels = evergreen_get_number_of_dram_channels(rdev);
		अन्यथा
			dram_channels = si_get_number_of_dram_channels(rdev);

		/* watermark क्रम high घड़ीs */
		अगर ((rdev->pm.pm_method == PM_METHOD_DPM) && rdev->pm.dpm_enabled) अणु
			wm_high.yclk =
				radeon_dpm_get_mclk(rdev, false) * 10;
			wm_high.sclk =
				radeon_dpm_get_sclk(rdev, false) * 10;
		पूर्ण अन्यथा अणु
			wm_high.yclk = rdev->pm.current_mclk * 10;
			wm_high.sclk = rdev->pm.current_sclk * 10;
		पूर्ण

		wm_high.disp_clk = mode->घड़ी;
		wm_high.src_width = mode->crtc_hdisplay;
		wm_high.active_समय = active_समय;
		wm_high.blank_समय = line_समय - wm_high.active_समय;
		wm_high.पूर्णांकerlaced = false;
		अगर (mode->flags & DRM_MODE_FLAG_INTERLACE)
			wm_high.पूर्णांकerlaced = true;
		wm_high.vsc = radeon_crtc->vsc;
		wm_high.vtaps = 1;
		अगर (radeon_crtc->rmx_type != RMX_OFF)
			wm_high.vtaps = 2;
		wm_high.bytes_per_pixel = 4; /* XXX: get this from fb config */
		wm_high.lb_size = lb_size;
		wm_high.dram_channels = dram_channels;
		wm_high.num_heads = num_heads;

		/* watermark क्रम low घड़ीs */
		अगर ((rdev->pm.pm_method == PM_METHOD_DPM) && rdev->pm.dpm_enabled) अणु
			wm_low.yclk =
				radeon_dpm_get_mclk(rdev, true) * 10;
			wm_low.sclk =
				radeon_dpm_get_sclk(rdev, true) * 10;
		पूर्ण अन्यथा अणु
			wm_low.yclk = rdev->pm.current_mclk * 10;
			wm_low.sclk = rdev->pm.current_sclk * 10;
		पूर्ण

		wm_low.disp_clk = mode->घड़ी;
		wm_low.src_width = mode->crtc_hdisplay;
		wm_low.active_समय = active_समय;
		wm_low.blank_समय = line_समय - wm_low.active_समय;
		wm_low.पूर्णांकerlaced = false;
		अगर (mode->flags & DRM_MODE_FLAG_INTERLACE)
			wm_low.पूर्णांकerlaced = true;
		wm_low.vsc = radeon_crtc->vsc;
		wm_low.vtaps = 1;
		अगर (radeon_crtc->rmx_type != RMX_OFF)
			wm_low.vtaps = 2;
		wm_low.bytes_per_pixel = 4; /* XXX: get this from fb config */
		wm_low.lb_size = lb_size;
		wm_low.dram_channels = dram_channels;
		wm_low.num_heads = num_heads;

		/* set क्रम high घड़ीs */
		latency_watermark_a = min(dce6_latency_watermark(&wm_high), (u32)65535);
		/* set क्रम low घड़ीs */
		latency_watermark_b = min(dce6_latency_watermark(&wm_low), (u32)65535);

		/* possibly क्रमce display priority to high */
		/* should really करो this at mode validation समय... */
		अगर (!dce6_average_bandwidth_vs_dram_bandwidth_क्रम_display(&wm_high) ||
		    !dce6_average_bandwidth_vs_available_bandwidth(&wm_high) ||
		    !dce6_check_latency_hiding(&wm_high) ||
		    (rdev->disp_priority == 2)) अणु
			DRM_DEBUG_KMS("force priority to high\n");
			priority_a_cnt |= PRIORITY_ALWAYS_ON;
			priority_b_cnt |= PRIORITY_ALWAYS_ON;
		पूर्ण
		अगर (!dce6_average_bandwidth_vs_dram_bandwidth_क्रम_display(&wm_low) ||
		    !dce6_average_bandwidth_vs_available_bandwidth(&wm_low) ||
		    !dce6_check_latency_hiding(&wm_low) ||
		    (rdev->disp_priority == 2)) अणु
			DRM_DEBUG_KMS("force priority to high\n");
			priority_a_cnt |= PRIORITY_ALWAYS_ON;
			priority_b_cnt |= PRIORITY_ALWAYS_ON;
		पूर्ण

		a.full = dfixed_स्थिर(1000);
		b.full = dfixed_स्थिर(mode->घड़ी);
		b.full = dfixed_भाग(b, a);
		c.full = dfixed_स्थिर(latency_watermark_a);
		c.full = dfixed_mul(c, b);
		c.full = dfixed_mul(c, radeon_crtc->hsc);
		c.full = dfixed_भाग(c, a);
		a.full = dfixed_स्थिर(16);
		c.full = dfixed_भाग(c, a);
		priority_a_mark = dfixed_trunc(c);
		priority_a_cnt |= priority_a_mark & PRIORITY_MARK_MASK;

		a.full = dfixed_स्थिर(1000);
		b.full = dfixed_स्थिर(mode->घड़ी);
		b.full = dfixed_भाग(b, a);
		c.full = dfixed_स्थिर(latency_watermark_b);
		c.full = dfixed_mul(c, b);
		c.full = dfixed_mul(c, radeon_crtc->hsc);
		c.full = dfixed_भाग(c, a);
		a.full = dfixed_स्थिर(16);
		c.full = dfixed_भाग(c, a);
		priority_b_mark = dfixed_trunc(c);
		priority_b_cnt |= priority_b_mark & PRIORITY_MARK_MASK;

		/* Save number of lines the linebuffer leads beक्रमe the scanout */
		radeon_crtc->lb_vblank_lead_lines = DIV_ROUND_UP(lb_size, mode->crtc_hdisplay);
	पूर्ण

	/* select wm A */
	arb_control3 = RREG32(DPG_PIPE_ARBITRATION_CONTROL3 + radeon_crtc->crtc_offset);
	पंचांगp = arb_control3;
	पंचांगp &= ~LATENCY_WATERMARK_MASK(3);
	पंचांगp |= LATENCY_WATERMARK_MASK(1);
	WREG32(DPG_PIPE_ARBITRATION_CONTROL3 + radeon_crtc->crtc_offset, पंचांगp);
	WREG32(DPG_PIPE_LATENCY_CONTROL + radeon_crtc->crtc_offset,
	       (LATENCY_LOW_WATERMARK(latency_watermark_a) |
		LATENCY_HIGH_WATERMARK(line_समय)));
	/* select wm B */
	पंचांगp = RREG32(DPG_PIPE_ARBITRATION_CONTROL3 + radeon_crtc->crtc_offset);
	पंचांगp &= ~LATENCY_WATERMARK_MASK(3);
	पंचांगp |= LATENCY_WATERMARK_MASK(2);
	WREG32(DPG_PIPE_ARBITRATION_CONTROL3 + radeon_crtc->crtc_offset, पंचांगp);
	WREG32(DPG_PIPE_LATENCY_CONTROL + radeon_crtc->crtc_offset,
	       (LATENCY_LOW_WATERMARK(latency_watermark_b) |
		LATENCY_HIGH_WATERMARK(line_समय)));
	/* restore original selection */
	WREG32(DPG_PIPE_ARBITRATION_CONTROL3 + radeon_crtc->crtc_offset, arb_control3);

	/* ग_लिखो the priority marks */
	WREG32(PRIORITY_A_CNT + radeon_crtc->crtc_offset, priority_a_cnt);
	WREG32(PRIORITY_B_CNT + radeon_crtc->crtc_offset, priority_b_cnt);

	/* save values क्रम DPM */
	radeon_crtc->line_समय = line_समय;
	radeon_crtc->wm_high = latency_watermark_a;
	radeon_crtc->wm_low = latency_watermark_b;
पूर्ण

व्योम dce6_bandwidth_update(काष्ठा radeon_device *rdev)
अणु
	काष्ठा drm_display_mode *mode0 = शून्य;
	काष्ठा drm_display_mode *mode1 = शून्य;
	u32 num_heads = 0, lb_size;
	पूर्णांक i;

	अगर (!rdev->mode_info.mode_config_initialized)
		वापस;

	radeon_update_display_priority(rdev);

	क्रम (i = 0; i < rdev->num_crtc; i++) अणु
		अगर (rdev->mode_info.crtcs[i]->base.enabled)
			num_heads++;
	पूर्ण
	क्रम (i = 0; i < rdev->num_crtc; i += 2) अणु
		mode0 = &rdev->mode_info.crtcs[i]->base.mode;
		mode1 = &rdev->mode_info.crtcs[i+1]->base.mode;
		lb_size = dce6_line_buffer_adjust(rdev, rdev->mode_info.crtcs[i], mode0, mode1);
		dce6_program_watermarks(rdev, rdev->mode_info.crtcs[i], lb_size, num_heads);
		lb_size = dce6_line_buffer_adjust(rdev, rdev->mode_info.crtcs[i+1], mode1, mode0);
		dce6_program_watermarks(rdev, rdev->mode_info.crtcs[i+1], lb_size, num_heads);
	पूर्ण
पूर्ण

/*
 * Core functions
 */
अटल व्योम si_tiling_mode_table_init(काष्ठा radeon_device *rdev)
अणु
	u32 *tile = rdev->config.si.tile_mode_array;
	स्थिर u32 num_tile_mode_states =
			ARRAY_SIZE(rdev->config.si.tile_mode_array);
	u32 reg_offset, split_equal_to_row_size;

	चयन (rdev->config.si.mem_row_size_in_kb) अणु
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

	चयन(rdev->family) अणु
	हाल CHIP_TAHITI:
	हाल CHIP_PITCAIRN:
		/* non-AA compressed depth or any compressed stencil */
		tile[0] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE(ADDR_SURF_DEPTH_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P8_32x32_8x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_64B) |
			   NUM_BANKS(ADDR_SURF_16_BANK) |
			   BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
			   BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
			   MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2));
		/* 2xAA/4xAA compressed depth only */
		tile[1] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE(ADDR_SURF_DEPTH_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P8_32x32_8x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_128B) |
			   NUM_BANKS(ADDR_SURF_16_BANK) |
			   BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
			   BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
			   MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2));
		/* 8xAA compressed depth only */
		tile[2] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE(ADDR_SURF_DEPTH_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P8_32x32_8x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_256B) |
			   NUM_BANKS(ADDR_SURF_16_BANK) |
			   BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
			   BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
			   MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2));
		/* 2xAA/4xAA compressed depth with stencil (क्रम depth buffer) */
		tile[3] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE(ADDR_SURF_DEPTH_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P8_32x32_8x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_128B) |
			   NUM_BANKS(ADDR_SURF_16_BANK) |
			   BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
			   BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
			   MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2));
		/* Maps w/ a dimension less than the 2D macro-tile dimensions (क्रम mipmapped depth textures) */
		tile[4] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
			   MICRO_TILE_MODE(ADDR_SURF_DEPTH_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P8_32x32_8x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_64B) |
			   NUM_BANKS(ADDR_SURF_16_BANK) |
			   BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
			   BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_2) |
			   MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2));
		/* Uncompressed 16bpp depth - and stencil buffer allocated with it */
		tile[5] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE(ADDR_SURF_DEPTH_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P8_32x32_8x16) |
			   TILE_SPLIT(split_equal_to_row_size) |
			   NUM_BANKS(ADDR_SURF_16_BANK) |
			   BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
			   BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_2) |
			   MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2));
		/* Uncompressed 32bpp depth - and stencil buffer allocated with it */
		tile[6] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE(ADDR_SURF_DEPTH_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P8_32x32_8x16) |
			   TILE_SPLIT(split_equal_to_row_size) |
			   NUM_BANKS(ADDR_SURF_16_BANK) |
			   BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
			   BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
			   MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_1));
		/* Uncompressed 8bpp stencil without depth (drivers typically करो not use) */
		tile[7] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE(ADDR_SURF_DEPTH_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P8_32x32_8x16) |
			   TILE_SPLIT(split_equal_to_row_size) |
			   NUM_BANKS(ADDR_SURF_16_BANK) |
			   BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
			   BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
			   MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2));
		/* 1D and 1D Array Surfaces */
		tile[8] = (ARRAY_MODE(ARRAY_LINEAR_ALIGNED) |
			   MICRO_TILE_MODE(ADDR_SURF_DISPLAY_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P8_32x32_8x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_64B) |
			   NUM_BANKS(ADDR_SURF_16_BANK) |
			   BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
			   BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_2) |
			   MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2));
		/* Displayable maps. */
		tile[9] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
			   MICRO_TILE_MODE(ADDR_SURF_DISPLAY_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P8_32x32_8x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_64B) |
			   NUM_BANKS(ADDR_SURF_16_BANK) |
			   BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
			   BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_2) |
			   MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2));
		/* Display 8bpp. */
		tile[10] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE(ADDR_SURF_DISPLAY_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P8_32x32_8x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_256B) |
			   NUM_BANKS(ADDR_SURF_16_BANK) |
			   BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
			   BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
			   MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2));
		/* Display 16bpp. */
		tile[11] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE(ADDR_SURF_DISPLAY_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P8_32x32_8x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_256B) |
			   NUM_BANKS(ADDR_SURF_16_BANK) |
			   BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
			   BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_2) |
			   MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2));
		/* Display 32bpp. */
		tile[12] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE(ADDR_SURF_DISPLAY_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P8_32x32_8x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_512B) |
			   NUM_BANKS(ADDR_SURF_16_BANK) |
			   BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
			   BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
			   MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_1));
		/* Thin. */
		tile[13] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
			   MICRO_TILE_MODE(ADDR_SURF_THIN_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P8_32x32_8x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_64B) |
			   NUM_BANKS(ADDR_SURF_16_BANK) |
			   BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
			   BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_2) |
			   MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2));
		/* Thin 8 bpp. */
		tile[14] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE(ADDR_SURF_THIN_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P8_32x32_8x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_256B) |
			   NUM_BANKS(ADDR_SURF_16_BANK) |
			   BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
			   BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
			   MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_1));
		/* Thin 16 bpp. */
		tile[15] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE(ADDR_SURF_THIN_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P8_32x32_8x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_256B) |
			   NUM_BANKS(ADDR_SURF_16_BANK) |
			   BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
			   BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_2) |
			   MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_1));
		/* Thin 32 bpp. */
		tile[16] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE(ADDR_SURF_THIN_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P8_32x32_8x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_512B) |
			   NUM_BANKS(ADDR_SURF_16_BANK) |
			   BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
			   BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
			   MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_1));
		/* Thin 64 bpp. */
		tile[17] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE(ADDR_SURF_THIN_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P8_32x32_8x16) |
			   TILE_SPLIT(split_equal_to_row_size) |
			   NUM_BANKS(ADDR_SURF_16_BANK) |
			   BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
			   BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
			   MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_1));
		/* 8 bpp PRT. */
		tile[21] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE(ADDR_SURF_THIN_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P8_32x32_8x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_256B) |
			   NUM_BANKS(ADDR_SURF_16_BANK) |
			   BANK_WIDTH(ADDR_SURF_BANK_WIDTH_2) |
			   BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
			   MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2));
		/* 16 bpp PRT */
		tile[22] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE(ADDR_SURF_THIN_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P8_32x32_8x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_256B) |
			   NUM_BANKS(ADDR_SURF_16_BANK) |
			   BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
			   BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
			   MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4));
		/* 32 bpp PRT */
		tile[23] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE(ADDR_SURF_THIN_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P8_32x32_8x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_256B) |
			   NUM_BANKS(ADDR_SURF_16_BANK) |
			   BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
			   BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_2) |
			   MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2));
		/* 64 bpp PRT */
		tile[24] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE(ADDR_SURF_THIN_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P8_32x32_8x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_512B) |
			   NUM_BANKS(ADDR_SURF_16_BANK) |
			   BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
			   BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
			   MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2));
		/* 128 bpp PRT */
		tile[25] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE(ADDR_SURF_THIN_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P8_32x32_8x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_1KB) |
			   NUM_BANKS(ADDR_SURF_8_BANK) |
			   BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
			   BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
			   MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_1));

		क्रम (reg_offset = 0; reg_offset < num_tile_mode_states; reg_offset++)
			WREG32(GB_TILE_MODE0 + (reg_offset * 4), tile[reg_offset]);
		अवरोध;

	हाल CHIP_VERDE:
	हाल CHIP_OLAND:
	हाल CHIP_HAIन_अंक:
		/* non-AA compressed depth or any compressed stencil */
		tile[0] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE(ADDR_SURF_DEPTH_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P4_8x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_64B) |
			   NUM_BANKS(ADDR_SURF_16_BANK) |
			   BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
			   BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
			   MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4));
		/* 2xAA/4xAA compressed depth only */
		tile[1] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE(ADDR_SURF_DEPTH_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P4_8x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_128B) |
			   NUM_BANKS(ADDR_SURF_16_BANK) |
			   BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
			   BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
			   MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4));
		/* 8xAA compressed depth only */
		tile[2] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE(ADDR_SURF_DEPTH_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P4_8x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_256B) |
			   NUM_BANKS(ADDR_SURF_16_BANK) |
			   BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
			   BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
			   MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4));
		/* 2xAA/4xAA compressed depth with stencil (क्रम depth buffer) */
		tile[3] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE(ADDR_SURF_DEPTH_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P4_8x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_128B) |
			   NUM_BANKS(ADDR_SURF_16_BANK) |
			   BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
			   BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
			   MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4));
		/* Maps w/ a dimension less than the 2D macro-tile dimensions (क्रम mipmapped depth textures) */
		tile[4] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
			   MICRO_TILE_MODE(ADDR_SURF_DEPTH_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P4_8x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_64B) |
			   NUM_BANKS(ADDR_SURF_16_BANK) |
			   BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
			   BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_2) |
			   MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2));
		/* Uncompressed 16bpp depth - and stencil buffer allocated with it */
		tile[5] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE(ADDR_SURF_DEPTH_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P4_8x16) |
			   TILE_SPLIT(split_equal_to_row_size) |
			   NUM_BANKS(ADDR_SURF_16_BANK) |
			   BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
			   BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_2) |
			   MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2));
		/* Uncompressed 32bpp depth - and stencil buffer allocated with it */
		tile[6] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE(ADDR_SURF_DEPTH_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P4_8x16) |
			   TILE_SPLIT(split_equal_to_row_size) |
			   NUM_BANKS(ADDR_SURF_16_BANK) |
			   BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
			   BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
			   MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2));
		/* Uncompressed 8bpp stencil without depth (drivers typically करो not use) */
		tile[7] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE(ADDR_SURF_DEPTH_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P4_8x16) |
			   TILE_SPLIT(split_equal_to_row_size) |
			   NUM_BANKS(ADDR_SURF_16_BANK) |
			   BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
			   BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
			   MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4));
		/* 1D and 1D Array Surfaces */
		tile[8] = (ARRAY_MODE(ARRAY_LINEAR_ALIGNED) |
			   MICRO_TILE_MODE(ADDR_SURF_DISPLAY_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P4_8x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_64B) |
			   NUM_BANKS(ADDR_SURF_16_BANK) |
			   BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
			   BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_2) |
			   MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2));
		/* Displayable maps. */
		tile[9] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
			   MICRO_TILE_MODE(ADDR_SURF_DISPLAY_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P4_8x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_64B) |
			   NUM_BANKS(ADDR_SURF_16_BANK) |
			   BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
			   BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_2) |
			   MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2));
		/* Display 8bpp. */
		tile[10] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE(ADDR_SURF_DISPLAY_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P4_8x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_256B) |
			   NUM_BANKS(ADDR_SURF_16_BANK) |
			   BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
			   BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
			   MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4));
		/* Display 16bpp. */
		tile[11] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE(ADDR_SURF_DISPLAY_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P4_8x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_256B) |
			   NUM_BANKS(ADDR_SURF_16_BANK) |
			   BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
			   BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_2) |
			   MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2));
		/* Display 32bpp. */
		tile[12] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE(ADDR_SURF_DISPLAY_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P4_8x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_512B) |
			   NUM_BANKS(ADDR_SURF_16_BANK) |
			   BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
			   BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
			   MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2));
		/* Thin. */
		tile[13] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
			   MICRO_TILE_MODE(ADDR_SURF_THIN_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P4_8x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_64B) |
			   NUM_BANKS(ADDR_SURF_16_BANK) |
			   BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
			   BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_2) |
			   MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2));
		/* Thin 8 bpp. */
		tile[14] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE(ADDR_SURF_THIN_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P4_8x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_256B) |
			   NUM_BANKS(ADDR_SURF_16_BANK) |
			   BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
			   BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
			   MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2));
		/* Thin 16 bpp. */
		tile[15] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE(ADDR_SURF_THIN_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P4_8x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_256B) |
			   NUM_BANKS(ADDR_SURF_16_BANK) |
			   BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
			   BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_2) |
			   MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2));
		/* Thin 32 bpp. */
		tile[16] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE(ADDR_SURF_THIN_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P4_8x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_512B) |
			   NUM_BANKS(ADDR_SURF_16_BANK) |
			   BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
			   BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
			   MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2));
		/* Thin 64 bpp. */
		tile[17] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE(ADDR_SURF_THIN_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P4_8x16) |
			   TILE_SPLIT(split_equal_to_row_size) |
			   NUM_BANKS(ADDR_SURF_16_BANK) |
			   BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
			   BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
			   MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2));
		/* 8 bpp PRT. */
		tile[21] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE(ADDR_SURF_THIN_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P8_32x32_8x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_256B) |
			   NUM_BANKS(ADDR_SURF_16_BANK) |
			   BANK_WIDTH(ADDR_SURF_BANK_WIDTH_2) |
			   BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
			   MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2));
		/* 16 bpp PRT */
		tile[22] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE(ADDR_SURF_THIN_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P8_32x32_8x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_256B) |
			   NUM_BANKS(ADDR_SURF_16_BANK) |
			   BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
			   BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
			   MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4));
		/* 32 bpp PRT */
		tile[23] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE(ADDR_SURF_THIN_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P8_32x32_8x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_256B) |
			   NUM_BANKS(ADDR_SURF_16_BANK) |
			   BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
			   BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_2) |
			   MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2));
		/* 64 bpp PRT */
		tile[24] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE(ADDR_SURF_THIN_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P8_32x32_8x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_512B) |
			   NUM_BANKS(ADDR_SURF_16_BANK) |
			   BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
			   BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
			   MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2));
		/* 128 bpp PRT */
		tile[25] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
			   MICRO_TILE_MODE(ADDR_SURF_THIN_MICRO_TILING) |
			   PIPE_CONFIG(ADDR_SURF_P8_32x32_8x16) |
			   TILE_SPLIT(ADDR_SURF_TILE_SPLIT_1KB) |
			   NUM_BANKS(ADDR_SURF_8_BANK) |
			   BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
			   BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
			   MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_1));

		क्रम (reg_offset = 0; reg_offset < num_tile_mode_states; reg_offset++)
			WREG32(GB_TILE_MODE0 + (reg_offset * 4), tile[reg_offset]);
		अवरोध;

	शेष:
		DRM_ERROR("unknown asic: 0x%x\n", rdev->family);
	पूर्ण
पूर्ण

अटल व्योम si_select_se_sh(काष्ठा radeon_device *rdev,
			    u32 se_num, u32 sh_num)
अणु
	u32 data = INSTANCE_BROADCAST_WRITES;

	अगर ((se_num == 0xffffffff) && (sh_num == 0xffffffff))
		data |= SH_BROADCAST_WRITES | SE_BROADCAST_WRITES;
	अन्यथा अगर (se_num == 0xffffffff)
		data |= SE_BROADCAST_WRITES | SH_INDEX(sh_num);
	अन्यथा अगर (sh_num == 0xffffffff)
		data |= SH_BROADCAST_WRITES | SE_INDEX(se_num);
	अन्यथा
		data |= SH_INDEX(sh_num) | SE_INDEX(se_num);
	WREG32(GRBM_GFX_INDEX, data);
पूर्ण

अटल u32 si_create_biपंचांगask(u32 bit_width)
अणु
	u32 i, mask = 0;

	क्रम (i = 0; i < bit_width; i++) अणु
		mask <<= 1;
		mask |= 1;
	पूर्ण
	वापस mask;
पूर्ण

अटल u32 si_get_cu_enabled(काष्ठा radeon_device *rdev, u32 cu_per_sh)
अणु
	u32 data, mask;

	data = RREG32(CC_GC_SHADER_ARRAY_CONFIG);
	अगर (data & 1)
		data &= INACTIVE_CUS_MASK;
	अन्यथा
		data = 0;
	data |= RREG32(GC_USER_SHADER_ARRAY_CONFIG);

	data >>= INACTIVE_CUS_SHIFT;

	mask = si_create_biपंचांगask(cu_per_sh);

	वापस ~data & mask;
पूर्ण

अटल व्योम si_setup_spi(काष्ठा radeon_device *rdev,
			 u32 se_num, u32 sh_per_se,
			 u32 cu_per_sh)
अणु
	पूर्णांक i, j, k;
	u32 data, mask, active_cu;

	क्रम (i = 0; i < se_num; i++) अणु
		क्रम (j = 0; j < sh_per_se; j++) अणु
			si_select_se_sh(rdev, i, j);
			data = RREG32(SPI_STATIC_THREAD_MGMT_3);
			active_cu = si_get_cu_enabled(rdev, cu_per_sh);

			mask = 1;
			क्रम (k = 0; k < 16; k++) अणु
				mask <<= k;
				अगर (active_cu & mask) अणु
					data &= ~mask;
					WREG32(SPI_STATIC_THREAD_MGMT_3, data);
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	si_select_se_sh(rdev, 0xffffffff, 0xffffffff);
पूर्ण

अटल u32 si_get_rb_disabled(काष्ठा radeon_device *rdev,
			      u32 max_rb_num_per_se,
			      u32 sh_per_se)
अणु
	u32 data, mask;

	data = RREG32(CC_RB_BACKEND_DISABLE);
	अगर (data & 1)
		data &= BACKEND_DISABLE_MASK;
	अन्यथा
		data = 0;
	data |= RREG32(GC_USER_RB_BACKEND_DISABLE);

	data >>= BACKEND_DISABLE_SHIFT;

	mask = si_create_biपंचांगask(max_rb_num_per_se / sh_per_se);

	वापस data & mask;
पूर्ण

अटल व्योम si_setup_rb(काष्ठा radeon_device *rdev,
			u32 se_num, u32 sh_per_se,
			u32 max_rb_num_per_se)
अणु
	पूर्णांक i, j;
	u32 data, mask;
	u32 disabled_rbs = 0;
	u32 enabled_rbs = 0;

	क्रम (i = 0; i < se_num; i++) अणु
		क्रम (j = 0; j < sh_per_se; j++) अणु
			si_select_se_sh(rdev, i, j);
			data = si_get_rb_disabled(rdev, max_rb_num_per_se, sh_per_se);
			disabled_rbs |= data << ((i * sh_per_se + j) * TAHITI_RB_BITMAP_WIDTH_PER_SH);
		पूर्ण
	पूर्ण
	si_select_se_sh(rdev, 0xffffffff, 0xffffffff);

	mask = 1;
	क्रम (i = 0; i < max_rb_num_per_se * se_num; i++) अणु
		अगर (!(disabled_rbs & mask))
			enabled_rbs |= mask;
		mask <<= 1;
	पूर्ण

	rdev->config.si.backend_enable_mask = enabled_rbs;

	क्रम (i = 0; i < se_num; i++) अणु
		si_select_se_sh(rdev, i, 0xffffffff);
		data = 0;
		क्रम (j = 0; j < sh_per_se; j++) अणु
			चयन (enabled_rbs & 3) अणु
			हाल 1:
				data |= (RASTER_CONFIG_RB_MAP_0 << (i * sh_per_se + j) * 2);
				अवरोध;
			हाल 2:
				data |= (RASTER_CONFIG_RB_MAP_3 << (i * sh_per_se + j) * 2);
				अवरोध;
			हाल 3:
			शेष:
				data |= (RASTER_CONFIG_RB_MAP_2 << (i * sh_per_se + j) * 2);
				अवरोध;
			पूर्ण
			enabled_rbs >>= 2;
		पूर्ण
		WREG32(PA_SC_RASTER_CONFIG, data);
	पूर्ण
	si_select_se_sh(rdev, 0xffffffff, 0xffffffff);
पूर्ण

अटल व्योम si_gpu_init(काष्ठा radeon_device *rdev)
अणु
	u32 gb_addr_config = 0;
	u32 mc_arb_ramcfg;
	u32 sx_debug_1;
	u32 hdp_host_path_cntl;
	u32 पंचांगp;
	पूर्णांक i, j;

	चयन (rdev->family) अणु
	हाल CHIP_TAHITI:
		rdev->config.si.max_shader_engines = 2;
		rdev->config.si.max_tile_pipes = 12;
		rdev->config.si.max_cu_per_sh = 8;
		rdev->config.si.max_sh_per_se = 2;
		rdev->config.si.max_backends_per_se = 4;
		rdev->config.si.max_texture_channel_caches = 12;
		rdev->config.si.max_gprs = 256;
		rdev->config.si.max_gs_thपढ़ोs = 32;
		rdev->config.si.max_hw_contexts = 8;

		rdev->config.si.sc_prim_fअगरo_size_frontend = 0x20;
		rdev->config.si.sc_prim_fअगरo_size_backend = 0x100;
		rdev->config.si.sc_hiz_tile_fअगरo_size = 0x30;
		rdev->config.si.sc_earlyz_tile_fअगरo_size = 0x130;
		gb_addr_config = TAHITI_GB_ADDR_CONFIG_GOLDEN;
		अवरोध;
	हाल CHIP_PITCAIRN:
		rdev->config.si.max_shader_engines = 2;
		rdev->config.si.max_tile_pipes = 8;
		rdev->config.si.max_cu_per_sh = 5;
		rdev->config.si.max_sh_per_se = 2;
		rdev->config.si.max_backends_per_se = 4;
		rdev->config.si.max_texture_channel_caches = 8;
		rdev->config.si.max_gprs = 256;
		rdev->config.si.max_gs_thपढ़ोs = 32;
		rdev->config.si.max_hw_contexts = 8;

		rdev->config.si.sc_prim_fअगरo_size_frontend = 0x20;
		rdev->config.si.sc_prim_fअगरo_size_backend = 0x100;
		rdev->config.si.sc_hiz_tile_fअगरo_size = 0x30;
		rdev->config.si.sc_earlyz_tile_fअगरo_size = 0x130;
		gb_addr_config = TAHITI_GB_ADDR_CONFIG_GOLDEN;
		अवरोध;
	हाल CHIP_VERDE:
	शेष:
		rdev->config.si.max_shader_engines = 1;
		rdev->config.si.max_tile_pipes = 4;
		rdev->config.si.max_cu_per_sh = 5;
		rdev->config.si.max_sh_per_se = 2;
		rdev->config.si.max_backends_per_se = 4;
		rdev->config.si.max_texture_channel_caches = 4;
		rdev->config.si.max_gprs = 256;
		rdev->config.si.max_gs_thपढ़ोs = 32;
		rdev->config.si.max_hw_contexts = 8;

		rdev->config.si.sc_prim_fअगरo_size_frontend = 0x20;
		rdev->config.si.sc_prim_fअगरo_size_backend = 0x40;
		rdev->config.si.sc_hiz_tile_fअगरo_size = 0x30;
		rdev->config.si.sc_earlyz_tile_fअगरo_size = 0x130;
		gb_addr_config = VERDE_GB_ADDR_CONFIG_GOLDEN;
		अवरोध;
	हाल CHIP_OLAND:
		rdev->config.si.max_shader_engines = 1;
		rdev->config.si.max_tile_pipes = 4;
		rdev->config.si.max_cu_per_sh = 6;
		rdev->config.si.max_sh_per_se = 1;
		rdev->config.si.max_backends_per_se = 2;
		rdev->config.si.max_texture_channel_caches = 4;
		rdev->config.si.max_gprs = 256;
		rdev->config.si.max_gs_thपढ़ोs = 16;
		rdev->config.si.max_hw_contexts = 8;

		rdev->config.si.sc_prim_fअगरo_size_frontend = 0x20;
		rdev->config.si.sc_prim_fअगरo_size_backend = 0x40;
		rdev->config.si.sc_hiz_tile_fअगरo_size = 0x30;
		rdev->config.si.sc_earlyz_tile_fअगरo_size = 0x130;
		gb_addr_config = VERDE_GB_ADDR_CONFIG_GOLDEN;
		अवरोध;
	हाल CHIP_HAIन_अंक:
		rdev->config.si.max_shader_engines = 1;
		rdev->config.si.max_tile_pipes = 4;
		rdev->config.si.max_cu_per_sh = 5;
		rdev->config.si.max_sh_per_se = 1;
		rdev->config.si.max_backends_per_se = 1;
		rdev->config.si.max_texture_channel_caches = 2;
		rdev->config.si.max_gprs = 256;
		rdev->config.si.max_gs_thपढ़ोs = 16;
		rdev->config.si.max_hw_contexts = 8;

		rdev->config.si.sc_prim_fअगरo_size_frontend = 0x20;
		rdev->config.si.sc_prim_fअगरo_size_backend = 0x40;
		rdev->config.si.sc_hiz_tile_fअगरo_size = 0x30;
		rdev->config.si.sc_earlyz_tile_fअगरo_size = 0x130;
		gb_addr_config = HAIन_अंक_GB_ADDR_CONFIG_GOLDEN;
		अवरोध;
	पूर्ण

	/* Initialize HDP */
	क्रम (i = 0, j = 0; i < 32; i++, j += 0x18) अणु
		WREG32((0x2c14 + j), 0x00000000);
		WREG32((0x2c18 + j), 0x00000000);
		WREG32((0x2c1c + j), 0x00000000);
		WREG32((0x2c20 + j), 0x00000000);
		WREG32((0x2c24 + j), 0x00000000);
	पूर्ण

	WREG32(GRBM_CNTL, GRBM_READ_TIMEOUT(0xff));
	WREG32(SRBM_INT_CNTL, 1);
	WREG32(SRBM_INT_ACK, 1);

	evergreen_fix_pci_max_पढ़ो_req_size(rdev);

	WREG32(BIF_FB_EN, FB_READ_EN | FB_WRITE_EN);

	RREG32(MC_SHARED_CHMAP);
	mc_arb_ramcfg = RREG32(MC_ARB_RAMCFG);

	rdev->config.si.num_tile_pipes = rdev->config.si.max_tile_pipes;
	rdev->config.si.mem_max_burst_length_bytes = 256;
	पंचांगp = (mc_arb_ramcfg & NOOFCOLS_MASK) >> NOOFCOLS_SHIFT;
	rdev->config.si.mem_row_size_in_kb = (4 * (1 << (8 + पंचांगp))) / 1024;
	अगर (rdev->config.si.mem_row_size_in_kb > 4)
		rdev->config.si.mem_row_size_in_kb = 4;
	/* XXX use MC settings? */
	rdev->config.si.shader_engine_tile_size = 32;
	rdev->config.si.num_gpus = 1;
	rdev->config.si.multi_gpu_tile_size = 64;

	/* fix up row size */
	gb_addr_config &= ~ROW_SIZE_MASK;
	चयन (rdev->config.si.mem_row_size_in_kb) अणु
	हाल 1:
	शेष:
		gb_addr_config |= ROW_SIZE(0);
		अवरोध;
	हाल 2:
		gb_addr_config |= ROW_SIZE(1);
		अवरोध;
	हाल 4:
		gb_addr_config |= ROW_SIZE(2);
		अवरोध;
	पूर्ण

	/* setup tiling info dword.  gb_addr_config is not adequate since it करोes
	 * not have bank info, so create a custom tiling dword.
	 * bits 3:0   num_pipes
	 * bits 7:4   num_banks
	 * bits 11:8  group_size
	 * bits 15:12 row_size
	 */
	rdev->config.si.tile_config = 0;
	चयन (rdev->config.si.num_tile_pipes) अणु
	हाल 1:
		rdev->config.si.tile_config |= (0 << 0);
		अवरोध;
	हाल 2:
		rdev->config.si.tile_config |= (1 << 0);
		अवरोध;
	हाल 4:
		rdev->config.si.tile_config |= (2 << 0);
		अवरोध;
	हाल 8:
	शेष:
		/* XXX what about 12? */
		rdev->config.si.tile_config |= (3 << 0);
		अवरोध;
	पूर्ण
	चयन ((mc_arb_ramcfg & NOOFBANK_MASK) >> NOOFBANK_SHIFT) अणु
	हाल 0: /* four banks */
		rdev->config.si.tile_config |= 0 << 4;
		अवरोध;
	हाल 1: /* eight banks */
		rdev->config.si.tile_config |= 1 << 4;
		अवरोध;
	हाल 2: /* sixteen banks */
	शेष:
		rdev->config.si.tile_config |= 2 << 4;
		अवरोध;
	पूर्ण
	rdev->config.si.tile_config |=
		((gb_addr_config & PIPE_INTERLEAVE_SIZE_MASK) >> PIPE_INTERLEAVE_SIZE_SHIFT) << 8;
	rdev->config.si.tile_config |=
		((gb_addr_config & ROW_SIZE_MASK) >> ROW_SIZE_SHIFT) << 12;

	WREG32(GB_ADDR_CONFIG, gb_addr_config);
	WREG32(DMIF_ADDR_CONFIG, gb_addr_config);
	WREG32(DMIF_ADDR_CALC, gb_addr_config);
	WREG32(HDP_ADDR_CONFIG, gb_addr_config);
	WREG32(DMA_TILING_CONFIG + DMA0_REGISTER_OFFSET, gb_addr_config);
	WREG32(DMA_TILING_CONFIG + DMA1_REGISTER_OFFSET, gb_addr_config);
	अगर (rdev->has_uvd) अणु
		WREG32(UVD_UDEC_ADDR_CONFIG, gb_addr_config);
		WREG32(UVD_UDEC_DB_ADDR_CONFIG, gb_addr_config);
		WREG32(UVD_UDEC_DBW_ADDR_CONFIG, gb_addr_config);
	पूर्ण

	si_tiling_mode_table_init(rdev);

	si_setup_rb(rdev, rdev->config.si.max_shader_engines,
		    rdev->config.si.max_sh_per_se,
		    rdev->config.si.max_backends_per_se);

	si_setup_spi(rdev, rdev->config.si.max_shader_engines,
		     rdev->config.si.max_sh_per_se,
		     rdev->config.si.max_cu_per_sh);

	rdev->config.si.active_cus = 0;
	क्रम (i = 0; i < rdev->config.si.max_shader_engines; i++) अणु
		क्रम (j = 0; j < rdev->config.si.max_sh_per_se; j++) अणु
			rdev->config.si.active_cus +=
				hweight32(si_get_cu_active_biपंचांगap(rdev, i, j));
		पूर्ण
	पूर्ण

	/* set HW शेषs क्रम 3D engine */
	WREG32(CP_QUEUE_THRESHOLDS, (ROQ_IB1_START(0x16) |
				     ROQ_IB2_START(0x2b)));
	WREG32(CP_MEQ_THRESHOLDS, MEQ1_START(0x30) | MEQ2_START(0x60));

	sx_debug_1 = RREG32(SX_DEBUG_1);
	WREG32(SX_DEBUG_1, sx_debug_1);

	WREG32(SPI_CONFIG_CNTL_1, VTX_DONE_DELAY(4));

	WREG32(PA_SC_FIFO_SIZE, (SC_FRONTEND_PRIM_FIFO_SIZE(rdev->config.si.sc_prim_fअगरo_size_frontend) |
				 SC_BACKEND_PRIM_FIFO_SIZE(rdev->config.si.sc_prim_fअगरo_size_backend) |
				 SC_HIZ_TILE_FIFO_SIZE(rdev->config.si.sc_hiz_tile_fअगरo_size) |
				 SC_EARLYZ_TILE_FIFO_SIZE(rdev->config.si.sc_earlyz_tile_fअगरo_size)));

	WREG32(VGT_NUM_INSTANCES, 1);

	WREG32(CP_PERFMON_CNTL, 0);

	WREG32(SQ_CONFIG, 0);

	WREG32(PA_SC_FORCE_EOV_MAX_CNTS, (FORCE_EOV_MAX_CLK_CNT(4095) |
					  FORCE_EOV_MAX_REZ_CNT(255)));

	WREG32(VGT_CACHE_INVALIDATION, CACHE_INVALIDATION(VC_AND_TC) |
	       AUTO_INVLD_EN(ES_AND_GS_AUTO));

	WREG32(VGT_GS_VERTEX_REUSE, 16);
	WREG32(PA_SC_LINE_STIPPLE_STATE, 0);

	WREG32(CB_PERFCOUNTER0_SELECT0, 0);
	WREG32(CB_PERFCOUNTER0_SELECT1, 0);
	WREG32(CB_PERFCOUNTER1_SELECT0, 0);
	WREG32(CB_PERFCOUNTER1_SELECT1, 0);
	WREG32(CB_PERFCOUNTER2_SELECT0, 0);
	WREG32(CB_PERFCOUNTER2_SELECT1, 0);
	WREG32(CB_PERFCOUNTER3_SELECT0, 0);
	WREG32(CB_PERFCOUNTER3_SELECT1, 0);

	पंचांगp = RREG32(HDP_MISC_CNTL);
	पंचांगp |= HDP_FLUSH_INVALIDATE_CACHE;
	WREG32(HDP_MISC_CNTL, पंचांगp);

	hdp_host_path_cntl = RREG32(HDP_HOST_PATH_CNTL);
	WREG32(HDP_HOST_PATH_CNTL, hdp_host_path_cntl);

	WREG32(PA_CL_ENHANCE, CLIP_VTX_REORDER_ENA | NUM_CLIP_SEQ(3));

	udelay(50);
पूर्ण

/*
 * GPU scratch रेजिस्टरs helpers function.
 */
अटल व्योम si_scratch_init(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक i;

	rdev->scratch.num_reg = 7;
	rdev->scratch.reg_base = SCRATCH_REG0;
	क्रम (i = 0; i < rdev->scratch.num_reg; i++) अणु
		rdev->scratch.मुक्त[i] = true;
		rdev->scratch.reg[i] = rdev->scratch.reg_base + (i * 4);
	पूर्ण
पूर्ण

व्योम si_fence_ring_emit(काष्ठा radeon_device *rdev,
			काष्ठा radeon_fence *fence)
अणु
	काष्ठा radeon_ring *ring = &rdev->ring[fence->ring];
	u64 addr = rdev->fence_drv[fence->ring].gpu_addr;

	/* flush पढ़ो cache over gart */
	radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_SET_CONFIG_REG, 1));
	radeon_ring_ग_लिखो(ring, (CP_COHER_CNTL2 - PACKET3_SET_CONFIG_REG_START) >> 2);
	radeon_ring_ग_लिखो(ring, 0);
	radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_SURFACE_SYNC, 3));
	radeon_ring_ग_लिखो(ring, PACKET3_TCL1_ACTION_ENA |
			  PACKET3_TC_ACTION_ENA |
			  PACKET3_SH_KCACHE_ACTION_ENA |
			  PACKET3_SH_ICACHE_ACTION_ENA);
	radeon_ring_ग_लिखो(ring, 0xFFFFFFFF);
	radeon_ring_ग_लिखो(ring, 0);
	radeon_ring_ग_लिखो(ring, 10); /* poll पूर्णांकerval */
	/* EVENT_WRITE_EOP - flush caches, send पूर्णांक */
	radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_EVENT_WRITE_EOP, 4));
	radeon_ring_ग_लिखो(ring, EVENT_TYPE(CACHE_FLUSH_AND_INV_TS_EVENT) | EVENT_INDEX(5));
	radeon_ring_ग_लिखो(ring, lower_32_bits(addr));
	radeon_ring_ग_लिखो(ring, (upper_32_bits(addr) & 0xff) | DATA_SEL(1) | INT_SEL(2));
	radeon_ring_ग_लिखो(ring, fence->seq);
	radeon_ring_ग_लिखो(ring, 0);
पूर्ण

/*
 * IB stuff
 */
व्योम si_ring_ib_execute(काष्ठा radeon_device *rdev, काष्ठा radeon_ib *ib)
अणु
	काष्ठा radeon_ring *ring = &rdev->ring[ib->ring];
	अचिन्हित vm_id = ib->vm ? ib->vm->ids[ib->ring].id : 0;
	u32 header;

	अगर (ib->is_स्थिर_ib) अणु
		/* set चयन buffer packet beक्रमe स्थिर IB */
		radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_SWITCH_BUFFER, 0));
		radeon_ring_ग_लिखो(ring, 0);

		header = PACKET3(PACKET3_INसूचीECT_BUFFER_CONST, 2);
	पूर्ण अन्यथा अणु
		u32 next_rptr;
		अगर (ring->rptr_save_reg) अणु
			next_rptr = ring->wptr + 3 + 4 + 8;
			radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_SET_CONFIG_REG, 1));
			radeon_ring_ग_लिखो(ring, ((ring->rptr_save_reg -
						  PACKET3_SET_CONFIG_REG_START) >> 2));
			radeon_ring_ग_लिखो(ring, next_rptr);
		पूर्ण अन्यथा अगर (rdev->wb.enabled) अणु
			next_rptr = ring->wptr + 5 + 4 + 8;
			radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_WRITE_DATA, 3));
			radeon_ring_ग_लिखो(ring, (1 << 8));
			radeon_ring_ग_लिखो(ring, ring->next_rptr_gpu_addr & 0xfffffffc);
			radeon_ring_ग_लिखो(ring, upper_32_bits(ring->next_rptr_gpu_addr));
			radeon_ring_ग_लिखो(ring, next_rptr);
		पूर्ण

		header = PACKET3(PACKET3_INसूचीECT_BUFFER, 2);
	पूर्ण

	radeon_ring_ग_लिखो(ring, header);
	radeon_ring_ग_लिखो(ring,
#अगर_घोषित __BIG_ENDIAN
			  (2 << 0) |
#पूर्ण_अगर
			  (ib->gpu_addr & 0xFFFFFFFC));
	radeon_ring_ग_लिखो(ring, upper_32_bits(ib->gpu_addr) & 0xFFFF);
	radeon_ring_ग_लिखो(ring, ib->length_dw | (vm_id << 24));

	अगर (!ib->is_स्थिर_ib) अणु
		/* flush पढ़ो cache over gart क्रम this vmid */
		radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_SET_CONFIG_REG, 1));
		radeon_ring_ग_लिखो(ring, (CP_COHER_CNTL2 - PACKET3_SET_CONFIG_REG_START) >> 2);
		radeon_ring_ग_लिखो(ring, vm_id);
		radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_SURFACE_SYNC, 3));
		radeon_ring_ग_लिखो(ring, PACKET3_TCL1_ACTION_ENA |
				  PACKET3_TC_ACTION_ENA |
				  PACKET3_SH_KCACHE_ACTION_ENA |
				  PACKET3_SH_ICACHE_ACTION_ENA);
		radeon_ring_ग_लिखो(ring, 0xFFFFFFFF);
		radeon_ring_ग_लिखो(ring, 0);
		radeon_ring_ग_लिखो(ring, 10); /* poll पूर्णांकerval */
	पूर्ण
पूर्ण

/*
 * CP.
 */
अटल व्योम si_cp_enable(काष्ठा radeon_device *rdev, bool enable)
अणु
	अगर (enable)
		WREG32(CP_ME_CNTL, 0);
	अन्यथा अणु
		अगर (rdev->asic->copy.copy_ring_index == RADEON_RING_TYPE_GFX_INDEX)
			radeon_tपंचांग_set_active_vram_size(rdev, rdev->mc.visible_vram_size);
		WREG32(CP_ME_CNTL, (CP_ME_HALT | CP_PFP_HALT | CP_CE_HALT));
		WREG32(SCRATCH_UMSK, 0);
		rdev->ring[RADEON_RING_TYPE_GFX_INDEX].पढ़ोy = false;
		rdev->ring[CAYMAN_RING_TYPE_CP1_INDEX].पढ़ोy = false;
		rdev->ring[CAYMAN_RING_TYPE_CP2_INDEX].पढ़ोy = false;
	पूर्ण
	udelay(50);
पूर्ण

अटल पूर्णांक si_cp_load_microcode(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक i;

	अगर (!rdev->me_fw || !rdev->pfp_fw || !rdev->ce_fw)
		वापस -EINVAL;

	si_cp_enable(rdev, false);

	अगर (rdev->new_fw) अणु
		स्थिर काष्ठा gfx_firmware_header_v1_0 *pfp_hdr =
			(स्थिर काष्ठा gfx_firmware_header_v1_0 *)rdev->pfp_fw->data;
		स्थिर काष्ठा gfx_firmware_header_v1_0 *ce_hdr =
			(स्थिर काष्ठा gfx_firmware_header_v1_0 *)rdev->ce_fw->data;
		स्थिर काष्ठा gfx_firmware_header_v1_0 *me_hdr =
			(स्थिर काष्ठा gfx_firmware_header_v1_0 *)rdev->me_fw->data;
		स्थिर __le32 *fw_data;
		u32 fw_size;

		radeon_ucode_prपूर्णांक_gfx_hdr(&pfp_hdr->header);
		radeon_ucode_prपूर्णांक_gfx_hdr(&ce_hdr->header);
		radeon_ucode_prपूर्णांक_gfx_hdr(&me_hdr->header);

		/* PFP */
		fw_data = (स्थिर __le32 *)
			(rdev->pfp_fw->data + le32_to_cpu(pfp_hdr->header.ucode_array_offset_bytes));
		fw_size = le32_to_cpu(pfp_hdr->header.ucode_size_bytes) / 4;
		WREG32(CP_PFP_UCODE_ADDR, 0);
		क्रम (i = 0; i < fw_size; i++)
			WREG32(CP_PFP_UCODE_DATA, le32_to_cpup(fw_data++));
		WREG32(CP_PFP_UCODE_ADDR, 0);

		/* CE */
		fw_data = (स्थिर __le32 *)
			(rdev->ce_fw->data + le32_to_cpu(ce_hdr->header.ucode_array_offset_bytes));
		fw_size = le32_to_cpu(ce_hdr->header.ucode_size_bytes) / 4;
		WREG32(CP_CE_UCODE_ADDR, 0);
		क्रम (i = 0; i < fw_size; i++)
			WREG32(CP_CE_UCODE_DATA, le32_to_cpup(fw_data++));
		WREG32(CP_CE_UCODE_ADDR, 0);

		/* ME */
		fw_data = (स्थिर __be32 *)
			(rdev->me_fw->data + le32_to_cpu(me_hdr->header.ucode_array_offset_bytes));
		fw_size = le32_to_cpu(me_hdr->header.ucode_size_bytes) / 4;
		WREG32(CP_ME_RAM_WADDR, 0);
		क्रम (i = 0; i < fw_size; i++)
			WREG32(CP_ME_RAM_DATA, le32_to_cpup(fw_data++));
		WREG32(CP_ME_RAM_WADDR, 0);
	पूर्ण अन्यथा अणु
		स्थिर __be32 *fw_data;

		/* PFP */
		fw_data = (स्थिर __be32 *)rdev->pfp_fw->data;
		WREG32(CP_PFP_UCODE_ADDR, 0);
		क्रम (i = 0; i < SI_PFP_UCODE_SIZE; i++)
			WREG32(CP_PFP_UCODE_DATA, be32_to_cpup(fw_data++));
		WREG32(CP_PFP_UCODE_ADDR, 0);

		/* CE */
		fw_data = (स्थिर __be32 *)rdev->ce_fw->data;
		WREG32(CP_CE_UCODE_ADDR, 0);
		क्रम (i = 0; i < SI_CE_UCODE_SIZE; i++)
			WREG32(CP_CE_UCODE_DATA, be32_to_cpup(fw_data++));
		WREG32(CP_CE_UCODE_ADDR, 0);

		/* ME */
		fw_data = (स्थिर __be32 *)rdev->me_fw->data;
		WREG32(CP_ME_RAM_WADDR, 0);
		क्रम (i = 0; i < SI_PM4_UCODE_SIZE; i++)
			WREG32(CP_ME_RAM_DATA, be32_to_cpup(fw_data++));
		WREG32(CP_ME_RAM_WADDR, 0);
	पूर्ण

	WREG32(CP_PFP_UCODE_ADDR, 0);
	WREG32(CP_CE_UCODE_ADDR, 0);
	WREG32(CP_ME_RAM_WADDR, 0);
	WREG32(CP_ME_RAM_RADDR, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक si_cp_start(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_ring *ring = &rdev->ring[RADEON_RING_TYPE_GFX_INDEX];
	पूर्णांक r, i;

	r = radeon_ring_lock(rdev, ring, 7 + 4);
	अगर (r) अणु
		DRM_ERROR("radeon: cp failed to lock ring (%d).\n", r);
		वापस r;
	पूर्ण
	/* init the CP */
	radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_ME_INITIALIZE, 5));
	radeon_ring_ग_लिखो(ring, 0x1);
	radeon_ring_ग_लिखो(ring, 0x0);
	radeon_ring_ग_लिखो(ring, rdev->config.si.max_hw_contexts - 1);
	radeon_ring_ग_लिखो(ring, PACKET3_ME_INITIALIZE_DEVICE_ID(1));
	radeon_ring_ग_लिखो(ring, 0);
	radeon_ring_ग_लिखो(ring, 0);

	/* init the CE partitions */
	radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_SET_BASE, 2));
	radeon_ring_ग_लिखो(ring, PACKET3_BASE_INDEX(CE_PARTITION_BASE));
	radeon_ring_ग_लिखो(ring, 0xc000);
	radeon_ring_ग_लिखो(ring, 0xe000);
	radeon_ring_unlock_commit(rdev, ring, false);

	si_cp_enable(rdev, true);

	r = radeon_ring_lock(rdev, ring, si_शेष_size + 10);
	अगर (r) अणु
		DRM_ERROR("radeon: cp failed to lock ring (%d).\n", r);
		वापस r;
	पूर्ण

	/* setup clear context state */
	radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_PREAMBLE_CNTL, 0));
	radeon_ring_ग_लिखो(ring, PACKET3_PREAMBLE_BEGIN_CLEAR_STATE);

	क्रम (i = 0; i < si_शेष_size; i++)
		radeon_ring_ग_लिखो(ring, si_शेष_state[i]);

	radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_PREAMBLE_CNTL, 0));
	radeon_ring_ग_लिखो(ring, PACKET3_PREAMBLE_END_CLEAR_STATE);

	/* set clear context state */
	radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_CLEAR_STATE, 0));
	radeon_ring_ग_लिखो(ring, 0);

	radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_SET_CONTEXT_REG, 2));
	radeon_ring_ग_लिखो(ring, 0x00000316);
	radeon_ring_ग_लिखो(ring, 0x0000000e); /* VGT_VERTEX_REUSE_BLOCK_CNTL */
	radeon_ring_ग_लिखो(ring, 0x00000010); /* VGT_OUT_DEALLOC_CNTL */

	radeon_ring_unlock_commit(rdev, ring, false);

	क्रम (i = RADEON_RING_TYPE_GFX_INDEX; i <= CAYMAN_RING_TYPE_CP2_INDEX; ++i) अणु
		ring = &rdev->ring[i];
		r = radeon_ring_lock(rdev, ring, 2);

		/* clear the compute context state */
		radeon_ring_ग_लिखो(ring, PACKET3_COMPUTE(PACKET3_CLEAR_STATE, 0));
		radeon_ring_ग_लिखो(ring, 0);

		radeon_ring_unlock_commit(rdev, ring, false);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम si_cp_fini(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_ring *ring;
	si_cp_enable(rdev, false);

	ring = &rdev->ring[RADEON_RING_TYPE_GFX_INDEX];
	radeon_ring_fini(rdev, ring);
	radeon_scratch_मुक्त(rdev, ring->rptr_save_reg);

	ring = &rdev->ring[CAYMAN_RING_TYPE_CP1_INDEX];
	radeon_ring_fini(rdev, ring);
	radeon_scratch_मुक्त(rdev, ring->rptr_save_reg);

	ring = &rdev->ring[CAYMAN_RING_TYPE_CP2_INDEX];
	radeon_ring_fini(rdev, ring);
	radeon_scratch_मुक्त(rdev, ring->rptr_save_reg);
पूर्ण

अटल पूर्णांक si_cp_resume(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_ring *ring;
	u32 पंचांगp;
	u32 rb_bufsz;
	पूर्णांक r;

	si_enable_gui_idle_पूर्णांकerrupt(rdev, false);

	WREG32(CP_SEM_WAIT_TIMER, 0x0);
	WREG32(CP_SEM_INCOMPLETE_TIMER_CNTL, 0x0);

	/* Set the ग_लिखो poपूर्णांकer delay */
	WREG32(CP_RB_WPTR_DELAY, 0);

	WREG32(CP_DEBUG, 0);
	WREG32(SCRATCH_ADDR, ((rdev->wb.gpu_addr + RADEON_WB_SCRATCH_OFFSET) >> 8) & 0xFFFFFFFF);

	/* ring 0 - compute and gfx */
	/* Set ring buffer size */
	ring = &rdev->ring[RADEON_RING_TYPE_GFX_INDEX];
	rb_bufsz = order_base_2(ring->ring_size / 8);
	पंचांगp = (order_base_2(RADEON_GPU_PAGE_SIZE/8) << 8) | rb_bufsz;
#अगर_घोषित __BIG_ENDIAN
	पंचांगp |= BUF_SWAP_32BIT;
#पूर्ण_अगर
	WREG32(CP_RB0_CNTL, पंचांगp);

	/* Initialize the ring buffer's पढ़ो and ग_लिखो poपूर्णांकers */
	WREG32(CP_RB0_CNTL, पंचांगp | RB_RPTR_WR_ENA);
	ring->wptr = 0;
	WREG32(CP_RB0_WPTR, ring->wptr);

	/* set the wb address whether it's enabled or not */
	WREG32(CP_RB0_RPTR_ADDR, (rdev->wb.gpu_addr + RADEON_WB_CP_RPTR_OFFSET) & 0xFFFFFFFC);
	WREG32(CP_RB0_RPTR_ADDR_HI, upper_32_bits(rdev->wb.gpu_addr + RADEON_WB_CP_RPTR_OFFSET) & 0xFF);

	अगर (rdev->wb.enabled)
		WREG32(SCRATCH_UMSK, 0xff);
	अन्यथा अणु
		पंचांगp |= RB_NO_UPDATE;
		WREG32(SCRATCH_UMSK, 0);
	पूर्ण

	mdelay(1);
	WREG32(CP_RB0_CNTL, पंचांगp);

	WREG32(CP_RB0_BASE, ring->gpu_addr >> 8);

	/* ring1  - compute only */
	/* Set ring buffer size */
	ring = &rdev->ring[CAYMAN_RING_TYPE_CP1_INDEX];
	rb_bufsz = order_base_2(ring->ring_size / 8);
	पंचांगp = (order_base_2(RADEON_GPU_PAGE_SIZE/8) << 8) | rb_bufsz;
#अगर_घोषित __BIG_ENDIAN
	पंचांगp |= BUF_SWAP_32BIT;
#पूर्ण_अगर
	WREG32(CP_RB1_CNTL, पंचांगp);

	/* Initialize the ring buffer's पढ़ो and ग_लिखो poपूर्णांकers */
	WREG32(CP_RB1_CNTL, पंचांगp | RB_RPTR_WR_ENA);
	ring->wptr = 0;
	WREG32(CP_RB1_WPTR, ring->wptr);

	/* set the wb address whether it's enabled or not */
	WREG32(CP_RB1_RPTR_ADDR, (rdev->wb.gpu_addr + RADEON_WB_CP1_RPTR_OFFSET) & 0xFFFFFFFC);
	WREG32(CP_RB1_RPTR_ADDR_HI, upper_32_bits(rdev->wb.gpu_addr + RADEON_WB_CP1_RPTR_OFFSET) & 0xFF);

	mdelay(1);
	WREG32(CP_RB1_CNTL, पंचांगp);

	WREG32(CP_RB1_BASE, ring->gpu_addr >> 8);

	/* ring2 - compute only */
	/* Set ring buffer size */
	ring = &rdev->ring[CAYMAN_RING_TYPE_CP2_INDEX];
	rb_bufsz = order_base_2(ring->ring_size / 8);
	पंचांगp = (order_base_2(RADEON_GPU_PAGE_SIZE/8) << 8) | rb_bufsz;
#अगर_घोषित __BIG_ENDIAN
	पंचांगp |= BUF_SWAP_32BIT;
#पूर्ण_अगर
	WREG32(CP_RB2_CNTL, पंचांगp);

	/* Initialize the ring buffer's पढ़ो and ग_लिखो poपूर्णांकers */
	WREG32(CP_RB2_CNTL, पंचांगp | RB_RPTR_WR_ENA);
	ring->wptr = 0;
	WREG32(CP_RB2_WPTR, ring->wptr);

	/* set the wb address whether it's enabled or not */
	WREG32(CP_RB2_RPTR_ADDR, (rdev->wb.gpu_addr + RADEON_WB_CP2_RPTR_OFFSET) & 0xFFFFFFFC);
	WREG32(CP_RB2_RPTR_ADDR_HI, upper_32_bits(rdev->wb.gpu_addr + RADEON_WB_CP2_RPTR_OFFSET) & 0xFF);

	mdelay(1);
	WREG32(CP_RB2_CNTL, पंचांगp);

	WREG32(CP_RB2_BASE, ring->gpu_addr >> 8);

	/* start the rings */
	si_cp_start(rdev);
	rdev->ring[RADEON_RING_TYPE_GFX_INDEX].पढ़ोy = true;
	rdev->ring[CAYMAN_RING_TYPE_CP1_INDEX].पढ़ोy = true;
	rdev->ring[CAYMAN_RING_TYPE_CP2_INDEX].पढ़ोy = true;
	r = radeon_ring_test(rdev, RADEON_RING_TYPE_GFX_INDEX, &rdev->ring[RADEON_RING_TYPE_GFX_INDEX]);
	अगर (r) अणु
		rdev->ring[RADEON_RING_TYPE_GFX_INDEX].पढ़ोy = false;
		rdev->ring[CAYMAN_RING_TYPE_CP1_INDEX].पढ़ोy = false;
		rdev->ring[CAYMAN_RING_TYPE_CP2_INDEX].पढ़ोy = false;
		वापस r;
	पूर्ण
	r = radeon_ring_test(rdev, CAYMAN_RING_TYPE_CP1_INDEX, &rdev->ring[CAYMAN_RING_TYPE_CP1_INDEX]);
	अगर (r) अणु
		rdev->ring[CAYMAN_RING_TYPE_CP1_INDEX].पढ़ोy = false;
	पूर्ण
	r = radeon_ring_test(rdev, CAYMAN_RING_TYPE_CP2_INDEX, &rdev->ring[CAYMAN_RING_TYPE_CP2_INDEX]);
	अगर (r) अणु
		rdev->ring[CAYMAN_RING_TYPE_CP2_INDEX].पढ़ोy = false;
	पूर्ण

	si_enable_gui_idle_पूर्णांकerrupt(rdev, true);

	अगर (rdev->asic->copy.copy_ring_index == RADEON_RING_TYPE_GFX_INDEX)
		radeon_tपंचांग_set_active_vram_size(rdev, rdev->mc.real_vram_size);

	वापस 0;
पूर्ण

u32 si_gpu_check_soft_reset(काष्ठा radeon_device *rdev)
अणु
	u32 reset_mask = 0;
	u32 पंचांगp;

	/* GRBM_STATUS */
	पंचांगp = RREG32(GRBM_STATUS);
	अगर (पंचांगp & (PA_BUSY | SC_BUSY |
		   BCI_BUSY | SX_BUSY |
		   TA_BUSY | VGT_BUSY |
		   DB_BUSY | CB_BUSY |
		   GDS_BUSY | SPI_BUSY |
		   IA_BUSY | IA_BUSY_NO_DMA))
		reset_mask |= RADEON_RESET_GFX;

	अगर (पंचांगp & (CF_RQ_PENDING | PF_RQ_PENDING |
		   CP_BUSY | CP_COHERENCY_BUSY))
		reset_mask |= RADEON_RESET_CP;

	अगर (पंचांगp & GRBM_EE_BUSY)
		reset_mask |= RADEON_RESET_GRBM | RADEON_RESET_GFX | RADEON_RESET_CP;

	/* GRBM_STATUS2 */
	पंचांगp = RREG32(GRBM_STATUS2);
	अगर (पंचांगp & (RLC_RQ_PENDING | RLC_BUSY))
		reset_mask |= RADEON_RESET_RLC;

	/* DMA_STATUS_REG 0 */
	पंचांगp = RREG32(DMA_STATUS_REG + DMA0_REGISTER_OFFSET);
	अगर (!(पंचांगp & DMA_IDLE))
		reset_mask |= RADEON_RESET_DMA;

	/* DMA_STATUS_REG 1 */
	पंचांगp = RREG32(DMA_STATUS_REG + DMA1_REGISTER_OFFSET);
	अगर (!(पंचांगp & DMA_IDLE))
		reset_mask |= RADEON_RESET_DMA1;

	/* SRBM_STATUS2 */
	पंचांगp = RREG32(SRBM_STATUS2);
	अगर (पंचांगp & DMA_BUSY)
		reset_mask |= RADEON_RESET_DMA;

	अगर (पंचांगp & DMA1_BUSY)
		reset_mask |= RADEON_RESET_DMA1;

	/* SRBM_STATUS */
	पंचांगp = RREG32(SRBM_STATUS);

	अगर (पंचांगp & IH_BUSY)
		reset_mask |= RADEON_RESET_IH;

	अगर (पंचांगp & SEM_BUSY)
		reset_mask |= RADEON_RESET_SEM;

	अगर (पंचांगp & GRBM_RQ_PENDING)
		reset_mask |= RADEON_RESET_GRBM;

	अगर (पंचांगp & VMC_BUSY)
		reset_mask |= RADEON_RESET_VMC;

	अगर (पंचांगp & (MCB_BUSY | MCB_NON_DISPLAY_BUSY |
		   MCC_BUSY | MCD_BUSY))
		reset_mask |= RADEON_RESET_MC;

	अगर (evergreen_is_display_hung(rdev))
		reset_mask |= RADEON_RESET_DISPLAY;

	/* VM_L2_STATUS */
	पंचांगp = RREG32(VM_L2_STATUS);
	अगर (पंचांगp & L2_BUSY)
		reset_mask |= RADEON_RESET_VMC;

	/* Skip MC reset as it's mostly likely not hung, just busy */
	अगर (reset_mask & RADEON_RESET_MC) अणु
		DRM_DEBUG("MC busy: 0x%08X, clearing.\n", reset_mask);
		reset_mask &= ~RADEON_RESET_MC;
	पूर्ण

	वापस reset_mask;
पूर्ण

अटल व्योम si_gpu_soft_reset(काष्ठा radeon_device *rdev, u32 reset_mask)
अणु
	काष्ठा evergreen_mc_save save;
	u32 grbm_soft_reset = 0, srbm_soft_reset = 0;
	u32 पंचांगp;

	अगर (reset_mask == 0)
		वापस;

	dev_info(rdev->dev, "GPU softreset: 0x%08X\n", reset_mask);

	evergreen_prपूर्णांक_gpu_status_regs(rdev);
	dev_info(rdev->dev, "  VM_CONTEXT1_PROTECTION_FAULT_ADDR   0x%08X\n",
		 RREG32(VM_CONTEXT1_PROTECTION_FAULT_ADDR));
	dev_info(rdev->dev, "  VM_CONTEXT1_PROTECTION_FAULT_STATUS 0x%08X\n",
		 RREG32(VM_CONTEXT1_PROTECTION_FAULT_STATUS));

	/* disable PG/CG */
	si_fini_pg(rdev);
	si_fini_cg(rdev);

	/* stop the rlc */
	si_rlc_stop(rdev);

	/* Disable CP parsing/prefetching */
	WREG32(CP_ME_CNTL, CP_ME_HALT | CP_PFP_HALT | CP_CE_HALT);

	अगर (reset_mask & RADEON_RESET_DMA) अणु
		/* dma0 */
		पंचांगp = RREG32(DMA_RB_CNTL + DMA0_REGISTER_OFFSET);
		पंचांगp &= ~DMA_RB_ENABLE;
		WREG32(DMA_RB_CNTL + DMA0_REGISTER_OFFSET, पंचांगp);
	पूर्ण
	अगर (reset_mask & RADEON_RESET_DMA1) अणु
		/* dma1 */
		पंचांगp = RREG32(DMA_RB_CNTL + DMA1_REGISTER_OFFSET);
		पंचांगp &= ~DMA_RB_ENABLE;
		WREG32(DMA_RB_CNTL + DMA1_REGISTER_OFFSET, पंचांगp);
	पूर्ण

	udelay(50);

	evergreen_mc_stop(rdev, &save);
	अगर (evergreen_mc_रुको_क्रम_idle(rdev)) अणु
		dev_warn(rdev->dev, "Wait for MC idle timedout !\n");
	पूर्ण

	अगर (reset_mask & (RADEON_RESET_GFX | RADEON_RESET_COMPUTE | RADEON_RESET_CP)) अणु
		grbm_soft_reset = SOFT_RESET_CB |
			SOFT_RESET_DB |
			SOFT_RESET_GDS |
			SOFT_RESET_PA |
			SOFT_RESET_SC |
			SOFT_RESET_BCI |
			SOFT_RESET_SPI |
			SOFT_RESET_SX |
			SOFT_RESET_TC |
			SOFT_RESET_TA |
			SOFT_RESET_VGT |
			SOFT_RESET_IA;
	पूर्ण

	अगर (reset_mask & RADEON_RESET_CP) अणु
		grbm_soft_reset |= SOFT_RESET_CP | SOFT_RESET_VGT;

		srbm_soft_reset |= SOFT_RESET_GRBM;
	पूर्ण

	अगर (reset_mask & RADEON_RESET_DMA)
		srbm_soft_reset |= SOFT_RESET_DMA;

	अगर (reset_mask & RADEON_RESET_DMA1)
		srbm_soft_reset |= SOFT_RESET_DMA1;

	अगर (reset_mask & RADEON_RESET_DISPLAY)
		srbm_soft_reset |= SOFT_RESET_DC;

	अगर (reset_mask & RADEON_RESET_RLC)
		grbm_soft_reset |= SOFT_RESET_RLC;

	अगर (reset_mask & RADEON_RESET_SEM)
		srbm_soft_reset |= SOFT_RESET_SEM;

	अगर (reset_mask & RADEON_RESET_IH)
		srbm_soft_reset |= SOFT_RESET_IH;

	अगर (reset_mask & RADEON_RESET_GRBM)
		srbm_soft_reset |= SOFT_RESET_GRBM;

	अगर (reset_mask & RADEON_RESET_VMC)
		srbm_soft_reset |= SOFT_RESET_VMC;

	अगर (reset_mask & RADEON_RESET_MC)
		srbm_soft_reset |= SOFT_RESET_MC;

	अगर (grbm_soft_reset) अणु
		पंचांगp = RREG32(GRBM_SOFT_RESET);
		पंचांगp |= grbm_soft_reset;
		dev_info(rdev->dev, "GRBM_SOFT_RESET=0x%08X\n", पंचांगp);
		WREG32(GRBM_SOFT_RESET, पंचांगp);
		पंचांगp = RREG32(GRBM_SOFT_RESET);

		udelay(50);

		पंचांगp &= ~grbm_soft_reset;
		WREG32(GRBM_SOFT_RESET, पंचांगp);
		पंचांगp = RREG32(GRBM_SOFT_RESET);
	पूर्ण

	अगर (srbm_soft_reset) अणु
		पंचांगp = RREG32(SRBM_SOFT_RESET);
		पंचांगp |= srbm_soft_reset;
		dev_info(rdev->dev, "SRBM_SOFT_RESET=0x%08X\n", पंचांगp);
		WREG32(SRBM_SOFT_RESET, पंचांगp);
		पंचांगp = RREG32(SRBM_SOFT_RESET);

		udelay(50);

		पंचांगp &= ~srbm_soft_reset;
		WREG32(SRBM_SOFT_RESET, पंचांगp);
		पंचांगp = RREG32(SRBM_SOFT_RESET);
	पूर्ण

	/* Wait a little क्रम things to settle करोwn */
	udelay(50);

	evergreen_mc_resume(rdev, &save);
	udelay(50);

	evergreen_prपूर्णांक_gpu_status_regs(rdev);
पूर्ण

अटल व्योम si_set_clk_bypass_mode(काष्ठा radeon_device *rdev)
अणु
	u32 पंचांगp, i;

	पंचांगp = RREG32(CG_SPLL_FUNC_CNTL);
	पंचांगp |= SPLL_BYPASS_EN;
	WREG32(CG_SPLL_FUNC_CNTL, पंचांगp);

	पंचांगp = RREG32(CG_SPLL_FUNC_CNTL_2);
	पंचांगp |= SPLL_CTLREQ_CHG;
	WREG32(CG_SPLL_FUNC_CNTL_2, पंचांगp);

	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		अगर (RREG32(SPLL_STATUS) & SPLL_CHG_STATUS)
			अवरोध;
		udelay(1);
	पूर्ण

	पंचांगp = RREG32(CG_SPLL_FUNC_CNTL_2);
	पंचांगp &= ~(SPLL_CTLREQ_CHG | SCLK_MUX_UPDATE);
	WREG32(CG_SPLL_FUNC_CNTL_2, पंचांगp);

	पंचांगp = RREG32(MPLL_CNTL_MODE);
	पंचांगp &= ~MPLL_MCLK_SEL;
	WREG32(MPLL_CNTL_MODE, पंचांगp);
पूर्ण

अटल व्योम si_spll_घातerकरोwn(काष्ठा radeon_device *rdev)
अणु
	u32 पंचांगp;

	पंचांगp = RREG32(SPLL_CNTL_MODE);
	पंचांगp |= SPLL_SW_सूची_CONTROL;
	WREG32(SPLL_CNTL_MODE, पंचांगp);

	पंचांगp = RREG32(CG_SPLL_FUNC_CNTL);
	पंचांगp |= SPLL_RESET;
	WREG32(CG_SPLL_FUNC_CNTL, पंचांगp);

	पंचांगp = RREG32(CG_SPLL_FUNC_CNTL);
	पंचांगp |= SPLL_SLEEP;
	WREG32(CG_SPLL_FUNC_CNTL, पंचांगp);

	पंचांगp = RREG32(SPLL_CNTL_MODE);
	पंचांगp &= ~SPLL_SW_सूची_CONTROL;
	WREG32(SPLL_CNTL_MODE, पंचांगp);
पूर्ण

अटल व्योम si_gpu_pci_config_reset(काष्ठा radeon_device *rdev)
अणु
	काष्ठा evergreen_mc_save save;
	u32 पंचांगp, i;

	dev_info(rdev->dev, "GPU pci config reset\n");

	/* disable dpm? */

	/* disable cg/pg */
	si_fini_pg(rdev);
	si_fini_cg(rdev);

	/* Disable CP parsing/prefetching */
	WREG32(CP_ME_CNTL, CP_ME_HALT | CP_PFP_HALT | CP_CE_HALT);
	/* dma0 */
	पंचांगp = RREG32(DMA_RB_CNTL + DMA0_REGISTER_OFFSET);
	पंचांगp &= ~DMA_RB_ENABLE;
	WREG32(DMA_RB_CNTL + DMA0_REGISTER_OFFSET, पंचांगp);
	/* dma1 */
	पंचांगp = RREG32(DMA_RB_CNTL + DMA1_REGISTER_OFFSET);
	पंचांगp &= ~DMA_RB_ENABLE;
	WREG32(DMA_RB_CNTL + DMA1_REGISTER_OFFSET, पंचांगp);
	/* XXX other engines? */

	/* halt the rlc, disable cp पूर्णांकernal पूर्णांकs */
	si_rlc_stop(rdev);

	udelay(50);

	/* disable mem access */
	evergreen_mc_stop(rdev, &save);
	अगर (evergreen_mc_रुको_क्रम_idle(rdev)) अणु
		dev_warn(rdev->dev, "Wait for MC idle timed out !\n");
	पूर्ण

	/* set mclk/sclk to bypass */
	si_set_clk_bypass_mode(rdev);
	/* घातerकरोwn spll */
	si_spll_घातerकरोwn(rdev);
	/* disable BM */
	pci_clear_master(rdev->pdev);
	/* reset */
	radeon_pci_config_reset(rdev);
	/* रुको क्रम asic to come out of reset */
	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		अगर (RREG32(CONFIG_MEMSIZE) != 0xffffffff)
			अवरोध;
		udelay(1);
	पूर्ण
पूर्ण

पूर्णांक si_asic_reset(काष्ठा radeon_device *rdev, bool hard)
अणु
	u32 reset_mask;

	अगर (hard) अणु
		si_gpu_pci_config_reset(rdev);
		वापस 0;
	पूर्ण

	reset_mask = si_gpu_check_soft_reset(rdev);

	अगर (reset_mask)
		r600_set_bios_scratch_engine_hung(rdev, true);

	/* try soft reset */
	si_gpu_soft_reset(rdev, reset_mask);

	reset_mask = si_gpu_check_soft_reset(rdev);

	/* try pci config reset */
	अगर (reset_mask && radeon_hard_reset)
		si_gpu_pci_config_reset(rdev);

	reset_mask = si_gpu_check_soft_reset(rdev);

	अगर (!reset_mask)
		r600_set_bios_scratch_engine_hung(rdev, false);

	वापस 0;
पूर्ण

/**
 * si_gfx_is_lockup - Check अगर the GFX engine is locked up
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ring: radeon_ring काष्ठाure holding ring inक्रमmation
 *
 * Check अगर the GFX engine is locked up.
 * Returns true अगर the engine appears to be locked up, false अगर not.
 */
bool si_gfx_is_lockup(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring)
अणु
	u32 reset_mask = si_gpu_check_soft_reset(rdev);

	अगर (!(reset_mask & (RADEON_RESET_GFX |
			    RADEON_RESET_COMPUTE |
			    RADEON_RESET_CP))) अणु
		radeon_ring_lockup_update(rdev, ring);
		वापस false;
	पूर्ण
	वापस radeon_ring_test_lockup(rdev, ring);
पूर्ण

/* MC */
अटल व्योम si_mc_program(काष्ठा radeon_device *rdev)
अणु
	काष्ठा evergreen_mc_save save;
	u32 पंचांगp;
	पूर्णांक i, j;

	/* Initialize HDP */
	क्रम (i = 0, j = 0; i < 32; i++, j += 0x18) अणु
		WREG32((0x2c14 + j), 0x00000000);
		WREG32((0x2c18 + j), 0x00000000);
		WREG32((0x2c1c + j), 0x00000000);
		WREG32((0x2c20 + j), 0x00000000);
		WREG32((0x2c24 + j), 0x00000000);
	पूर्ण
	WREG32(HDP_REG_COHERENCY_FLUSH_CNTL, 0);

	evergreen_mc_stop(rdev, &save);
	अगर (radeon_mc_रुको_क्रम_idle(rdev)) अणु
		dev_warn(rdev->dev, "Wait for MC idle timedout !\n");
	पूर्ण
	अगर (!ASIC_IS_NODCE(rdev))
		/* Lockout access through VGA aperture*/
		WREG32(VGA_HDP_CONTROL, VGA_MEMORY_DISABLE);
	/* Update configuration */
	WREG32(MC_VM_SYSTEM_APERTURE_LOW_ADDR,
	       rdev->mc.vram_start >> 12);
	WREG32(MC_VM_SYSTEM_APERTURE_HIGH_ADDR,
	       rdev->mc.vram_end >> 12);
	WREG32(MC_VM_SYSTEM_APERTURE_DEFAULT_ADDR,
	       rdev->vram_scratch.gpu_addr >> 12);
	पंचांगp = ((rdev->mc.vram_end >> 24) & 0xFFFF) << 16;
	पंचांगp |= ((rdev->mc.vram_start >> 24) & 0xFFFF);
	WREG32(MC_VM_FB_LOCATION, पंचांगp);
	/* XXX द्विगुन check these! */
	WREG32(HDP_NONSURFACE_BASE, (rdev->mc.vram_start >> 8));
	WREG32(HDP_NONSURFACE_INFO, (2 << 7) | (1 << 30));
	WREG32(HDP_NONSURFACE_SIZE, 0x3FFFFFFF);
	WREG32(MC_VM_AGP_BASE, 0);
	WREG32(MC_VM_AGP_TOP, 0x0FFFFFFF);
	WREG32(MC_VM_AGP_BOT, 0x0FFFFFFF);
	अगर (radeon_mc_रुको_क्रम_idle(rdev)) अणु
		dev_warn(rdev->dev, "Wait for MC idle timedout !\n");
	पूर्ण
	evergreen_mc_resume(rdev, &save);
	अगर (!ASIC_IS_NODCE(rdev)) अणु
		/* we need to own VRAM, so turn off the VGA renderer here
		 * to stop it overwriting our objects */
		rv515_vga_render_disable(rdev);
	पूर्ण
पूर्ण

व्योम si_vram_gtt_location(काष्ठा radeon_device *rdev,
			  काष्ठा radeon_mc *mc)
अणु
	अगर (mc->mc_vram_size > 0xFFC0000000ULL) अणु
		/* leave room क्रम at least 1024M GTT */
		dev_warn(rdev->dev, "limiting VRAM\n");
		mc->real_vram_size = 0xFFC0000000ULL;
		mc->mc_vram_size = 0xFFC0000000ULL;
	पूर्ण
	radeon_vram_location(rdev, &rdev->mc, 0);
	rdev->mc.gtt_base_align = 0;
	radeon_gtt_location(rdev, mc);
पूर्ण

अटल पूर्णांक si_mc_init(काष्ठा radeon_device *rdev)
अणु
	u32 पंचांगp;
	पूर्णांक chansize, numchan;

	/* Get VRAM inक्रमmations */
	rdev->mc.vram_is_ddr = true;
	पंचांगp = RREG32(MC_ARB_RAMCFG);
	अगर (पंचांगp & CHANSIZE_OVERRIDE) अणु
		chansize = 16;
	पूर्ण अन्यथा अगर (पंचांगp & CHANSIZE_MASK) अणु
		chansize = 64;
	पूर्ण अन्यथा अणु
		chansize = 32;
	पूर्ण
	पंचांगp = RREG32(MC_SHARED_CHMAP);
	चयन ((पंचांगp & NOOFCHAN_MASK) >> NOOFCHAN_SHIFT) अणु
	हाल 0:
	शेष:
		numchan = 1;
		अवरोध;
	हाल 1:
		numchan = 2;
		अवरोध;
	हाल 2:
		numchan = 4;
		अवरोध;
	हाल 3:
		numchan = 8;
		अवरोध;
	हाल 4:
		numchan = 3;
		अवरोध;
	हाल 5:
		numchan = 6;
		अवरोध;
	हाल 6:
		numchan = 10;
		अवरोध;
	हाल 7:
		numchan = 12;
		अवरोध;
	हाल 8:
		numchan = 16;
		अवरोध;
	पूर्ण
	rdev->mc.vram_width = numchan * chansize;
	/* Could aper size report 0 ? */
	rdev->mc.aper_base = pci_resource_start(rdev->pdev, 0);
	rdev->mc.aper_size = pci_resource_len(rdev->pdev, 0);
	/* size in MB on si */
	पंचांगp = RREG32(CONFIG_MEMSIZE);
	/* some boards may have garbage in the upper 16 bits */
	अगर (पंचांगp & 0xffff0000) अणु
		DRM_INFO("Probable bad vram size: 0x%08x\n", पंचांगp);
		अगर (पंचांगp & 0xffff)
			पंचांगp &= 0xffff;
	पूर्ण
	rdev->mc.mc_vram_size = पंचांगp * 1024ULL * 1024ULL;
	rdev->mc.real_vram_size = rdev->mc.mc_vram_size;
	rdev->mc.visible_vram_size = rdev->mc.aper_size;
	si_vram_gtt_location(rdev, &rdev->mc);
	radeon_update_bandwidth_info(rdev);

	वापस 0;
पूर्ण

/*
 * GART
 */
व्योम si_pcie_gart_tlb_flush(काष्ठा radeon_device *rdev)
अणु
	/* flush hdp cache */
	WREG32(HDP_MEM_COHERENCY_FLUSH_CNTL, 0x1);

	/* bits 0-15 are the VM contexts0-15 */
	WREG32(VM_INVALIDATE_REQUEST, 1);
पूर्ण

अटल पूर्णांक si_pcie_gart_enable(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r, i;

	अगर (rdev->gart.robj == शून्य) अणु
		dev_err(rdev->dev, "No VRAM object for PCIE GART.\n");
		वापस -EINVAL;
	पूर्ण
	r = radeon_gart_table_vram_pin(rdev);
	अगर (r)
		वापस r;
	/* Setup TLB control */
	WREG32(MC_VM_MX_L1_TLB_CNTL,
	       (0xA << 7) |
	       ENABLE_L1_TLB |
	       ENABLE_L1_FRAGMENT_PROCESSING |
	       SYSTEM_ACCESS_MODE_NOT_IN_SYS |
	       ENABLE_ADVANCED_DRIVER_MODEL |
	       SYSTEM_APERTURE_UNMAPPED_ACCESS_PASS_THRU);
	/* Setup L2 cache */
	WREG32(VM_L2_CNTL, ENABLE_L2_CACHE |
	       ENABLE_L2_FRAGMENT_PROCESSING |
	       ENABLE_L2_PTE_CACHE_LRU_UPDATE_BY_WRITE |
	       ENABLE_L2_PDE0_CACHE_LRU_UPDATE_BY_WRITE |
	       EFFECTIVE_L2_QUEUE_SIZE(7) |
	       CONTEXT1_IDENTITY_ACCESS_MODE(1));
	WREG32(VM_L2_CNTL2, INVALIDATE_ALL_L1_TLBS | INVALIDATE_L2_CACHE);
	WREG32(VM_L2_CNTL3, L2_CACHE_BIGK_ASSOCIATIVITY |
	       BANK_SELECT(4) |
	       L2_CACHE_BIGK_FRAGMENT_SIZE(4));
	/* setup context0 */
	WREG32(VM_CONTEXT0_PAGE_TABLE_START_ADDR, rdev->mc.gtt_start >> 12);
	WREG32(VM_CONTEXT0_PAGE_TABLE_END_ADDR, rdev->mc.gtt_end >> 12);
	WREG32(VM_CONTEXT0_PAGE_TABLE_BASE_ADDR, rdev->gart.table_addr >> 12);
	WREG32(VM_CONTEXT0_PROTECTION_FAULT_DEFAULT_ADDR,
			(u32)(rdev->dummy_page.addr >> 12));
	WREG32(VM_CONTEXT0_CNTL2, 0);
	WREG32(VM_CONTEXT0_CNTL, (ENABLE_CONTEXT | PAGE_TABLE_DEPTH(0) |
				  RANGE_PROTECTION_FAULT_ENABLE_DEFAULT));

	WREG32(0x15D4, 0);
	WREG32(0x15D8, 0);
	WREG32(0x15DC, 0);

	/* empty context1-15 */
	/* set vm size, must be a multiple of 4 */
	WREG32(VM_CONTEXT1_PAGE_TABLE_START_ADDR, 0);
	WREG32(VM_CONTEXT1_PAGE_TABLE_END_ADDR, rdev->vm_manager.max_pfn - 1);
	/* Assign the pt base to something valid क्रम now; the pts used क्रम
	 * the VMs are determined by the application and setup and asचिन्हित
	 * on the fly in the vm part of radeon_gart.c
	 */
	क्रम (i = 1; i < 16; i++) अणु
		अगर (i < 8)
			WREG32(VM_CONTEXT0_PAGE_TABLE_BASE_ADDR + (i << 2),
			       rdev->vm_manager.saved_table_addr[i]);
		अन्यथा
			WREG32(VM_CONTEXT8_PAGE_TABLE_BASE_ADDR + ((i - 8) << 2),
			       rdev->vm_manager.saved_table_addr[i]);
	पूर्ण

	/* enable context1-15 */
	WREG32(VM_CONTEXT1_PROTECTION_FAULT_DEFAULT_ADDR,
	       (u32)(rdev->dummy_page.addr >> 12));
	WREG32(VM_CONTEXT1_CNTL2, 4);
	WREG32(VM_CONTEXT1_CNTL, ENABLE_CONTEXT | PAGE_TABLE_DEPTH(1) |
				PAGE_TABLE_BLOCK_SIZE(radeon_vm_block_size - 9) |
				RANGE_PROTECTION_FAULT_ENABLE_INTERRUPT |
				RANGE_PROTECTION_FAULT_ENABLE_DEFAULT |
				DUMMY_PAGE_PROTECTION_FAULT_ENABLE_INTERRUPT |
				DUMMY_PAGE_PROTECTION_FAULT_ENABLE_DEFAULT |
				PDE0_PROTECTION_FAULT_ENABLE_INTERRUPT |
				PDE0_PROTECTION_FAULT_ENABLE_DEFAULT |
				VALID_PROTECTION_FAULT_ENABLE_INTERRUPT |
				VALID_PROTECTION_FAULT_ENABLE_DEFAULT |
				READ_PROTECTION_FAULT_ENABLE_INTERRUPT |
				READ_PROTECTION_FAULT_ENABLE_DEFAULT |
				WRITE_PROTECTION_FAULT_ENABLE_INTERRUPT |
				WRITE_PROTECTION_FAULT_ENABLE_DEFAULT);

	si_pcie_gart_tlb_flush(rdev);
	DRM_INFO("PCIE GART of %uM enabled (table at 0x%016llX).\n",
		 (अचिन्हित)(rdev->mc.gtt_size >> 20),
		 (अचिन्हित दीर्घ दीर्घ)rdev->gart.table_addr);
	rdev->gart.पढ़ोy = true;
	वापस 0;
पूर्ण

अटल व्योम si_pcie_gart_disable(काष्ठा radeon_device *rdev)
अणु
	अचिन्हित i;

	क्रम (i = 1; i < 16; ++i) अणु
		uपूर्णांक32_t reg;
		अगर (i < 8)
			reg = VM_CONTEXT0_PAGE_TABLE_BASE_ADDR + (i << 2);
		अन्यथा
			reg = VM_CONTEXT8_PAGE_TABLE_BASE_ADDR + ((i - 8) << 2);
		rdev->vm_manager.saved_table_addr[i] = RREG32(reg);
	पूर्ण

	/* Disable all tables */
	WREG32(VM_CONTEXT0_CNTL, 0);
	WREG32(VM_CONTEXT1_CNTL, 0);
	/* Setup TLB control */
	WREG32(MC_VM_MX_L1_TLB_CNTL, SYSTEM_ACCESS_MODE_NOT_IN_SYS |
	       SYSTEM_APERTURE_UNMAPPED_ACCESS_PASS_THRU);
	/* Setup L2 cache */
	WREG32(VM_L2_CNTL, ENABLE_L2_PTE_CACHE_LRU_UPDATE_BY_WRITE |
	       ENABLE_L2_PDE0_CACHE_LRU_UPDATE_BY_WRITE |
	       EFFECTIVE_L2_QUEUE_SIZE(7) |
	       CONTEXT1_IDENTITY_ACCESS_MODE(1));
	WREG32(VM_L2_CNTL2, 0);
	WREG32(VM_L2_CNTL3, L2_CACHE_BIGK_ASSOCIATIVITY |
	       L2_CACHE_BIGK_FRAGMENT_SIZE(0));
	radeon_gart_table_vram_unpin(rdev);
पूर्ण

अटल व्योम si_pcie_gart_fini(काष्ठा radeon_device *rdev)
अणु
	si_pcie_gart_disable(rdev);
	radeon_gart_table_vram_मुक्त(rdev);
	radeon_gart_fini(rdev);
पूर्ण

/* vm parser */
अटल bool si_vm_reg_valid(u32 reg)
अणु
	/* context regs are fine */
	अगर (reg >= 0x28000)
		वापस true;

	/* shader regs are also fine */
	अगर (reg >= 0xB000 && reg < 0xC000)
		वापस true;

	/* check config regs */
	चयन (reg) अणु
	हाल GRBM_GFX_INDEX:
	हाल CP_STRMOUT_CNTL:
	हाल VGT_VTX_VECT_EJECT_REG:
	हाल VGT_CACHE_INVALIDATION:
	हाल VGT_ESGS_RING_SIZE:
	हाल VGT_GSVS_RING_SIZE:
	हाल VGT_GS_VERTEX_REUSE:
	हाल VGT_PRIMITIVE_TYPE:
	हाल VGT_INDEX_TYPE:
	हाल VGT_NUM_INDICES:
	हाल VGT_NUM_INSTANCES:
	हाल VGT_TF_RING_SIZE:
	हाल VGT_HS_OFFCHIP_PARAM:
	हाल VGT_TF_MEMORY_BASE:
	हाल PA_CL_ENHANCE:
	हाल PA_SU_LINE_STIPPLE_VALUE:
	हाल PA_SC_LINE_STIPPLE_STATE:
	हाल PA_SC_ENHANCE:
	हाल SQC_CACHES:
	हाल SPI_STATIC_THREAD_MGMT_1:
	हाल SPI_STATIC_THREAD_MGMT_2:
	हाल SPI_STATIC_THREAD_MGMT_3:
	हाल SPI_PS_MAX_WAVE_ID:
	हाल SPI_CONFIG_CNTL:
	हाल SPI_CONFIG_CNTL_1:
	हाल TA_CNTL_AUX:
	हाल TA_CS_BC_BASE_ADDR:
		वापस true;
	शेष:
		DRM_ERROR("Invalid register 0x%x in CS\n", reg);
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक si_vm_packet3_ce_check(काष्ठा radeon_device *rdev,
				  u32 *ib, काष्ठा radeon_cs_packet *pkt)
अणु
	चयन (pkt->opcode) अणु
	हाल PACKET3_NOP:
	हाल PACKET3_SET_BASE:
	हाल PACKET3_SET_CE_DE_COUNTERS:
	हाल PACKET3_LOAD_CONST_RAM:
	हाल PACKET3_WRITE_CONST_RAM:
	हाल PACKET3_WRITE_CONST_RAM_OFFSET:
	हाल PACKET3_DUMP_CONST_RAM:
	हाल PACKET3_INCREMENT_CE_COUNTER:
	हाल PACKET3_WAIT_ON_DE_COUNTER:
	हाल PACKET3_CE_WRITE:
		अवरोध;
	शेष:
		DRM_ERROR("Invalid CE packet3: 0x%x\n", pkt->opcode);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक si_vm_packet3_cp_dma_check(u32 *ib, u32 idx)
अणु
	u32 start_reg, reg, i;
	u32 command = ib[idx + 4];
	u32 info = ib[idx + 1];
	u32 idx_value = ib[idx];
	अगर (command & PACKET3_CP_DMA_CMD_SAS) अणु
		/* src address space is रेजिस्टर */
		अगर (((info & 0x60000000) >> 29) == 0) अणु
			start_reg = idx_value << 2;
			अगर (command & PACKET3_CP_DMA_CMD_SAIC) अणु
				reg = start_reg;
				अगर (!si_vm_reg_valid(reg)) अणु
					DRM_ERROR("CP DMA Bad SRC register\n");
					वापस -EINVAL;
				पूर्ण
			पूर्ण अन्यथा अणु
				क्रम (i = 0; i < (command & 0x1fffff); i++) अणु
					reg = start_reg + (4 * i);
					अगर (!si_vm_reg_valid(reg)) अणु
						DRM_ERROR("CP DMA Bad SRC register\n");
						वापस -EINVAL;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (command & PACKET3_CP_DMA_CMD_DAS) अणु
		/* dst address space is रेजिस्टर */
		अगर (((info & 0x00300000) >> 20) == 0) अणु
			start_reg = ib[idx + 2];
			अगर (command & PACKET3_CP_DMA_CMD_DAIC) अणु
				reg = start_reg;
				अगर (!si_vm_reg_valid(reg)) अणु
					DRM_ERROR("CP DMA Bad DST register\n");
					वापस -EINVAL;
				पूर्ण
			पूर्ण अन्यथा अणु
				क्रम (i = 0; i < (command & 0x1fffff); i++) अणु
					reg = start_reg + (4 * i);
					अगर (!si_vm_reg_valid(reg)) अणु
						DRM_ERROR("CP DMA Bad DST register\n");
						वापस -EINVAL;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक si_vm_packet3_gfx_check(काष्ठा radeon_device *rdev,
				   u32 *ib, काष्ठा radeon_cs_packet *pkt)
अणु
	पूर्णांक r;
	u32 idx = pkt->idx + 1;
	u32 idx_value = ib[idx];
	u32 start_reg, end_reg, reg, i;

	चयन (pkt->opcode) अणु
	हाल PACKET3_NOP:
	हाल PACKET3_SET_BASE:
	हाल PACKET3_CLEAR_STATE:
	हाल PACKET3_INDEX_BUFFER_SIZE:
	हाल PACKET3_DISPATCH_सूचीECT:
	हाल PACKET3_DISPATCH_INसूचीECT:
	हाल PACKET3_ALLOC_GDS:
	हाल PACKET3_WRITE_GDS_RAM:
	हाल PACKET3_ATOMIC_GDS:
	हाल PACKET3_ATOMIC:
	हाल PACKET3_OCCLUSION_QUERY:
	हाल PACKET3_SET_PREDICATION:
	हाल PACKET3_COND_EXEC:
	हाल PACKET3_PRED_EXEC:
	हाल PACKET3_DRAW_INसूचीECT:
	हाल PACKET3_DRAW_INDEX_INसूचीECT:
	हाल PACKET3_INDEX_BASE:
	हाल PACKET3_DRAW_INDEX_2:
	हाल PACKET3_CONTEXT_CONTROL:
	हाल PACKET3_INDEX_TYPE:
	हाल PACKET3_DRAW_INसूचीECT_MULTI:
	हाल PACKET3_DRAW_INDEX_AUTO:
	हाल PACKET3_DRAW_INDEX_IMMD:
	हाल PACKET3_NUM_INSTANCES:
	हाल PACKET3_DRAW_INDEX_MULTI_AUTO:
	हाल PACKET3_STRMOUT_BUFFER_UPDATE:
	हाल PACKET3_DRAW_INDEX_OFFSET_2:
	हाल PACKET3_DRAW_INDEX_MULTI_ELEMENT:
	हाल PACKET3_DRAW_INDEX_INसूचीECT_MULTI:
	हाल PACKET3_MPEG_INDEX:
	हाल PACKET3_WAIT_REG_MEM:
	हाल PACKET3_MEM_WRITE:
	हाल PACKET3_PFP_SYNC_ME:
	हाल PACKET3_SURFACE_SYNC:
	हाल PACKET3_EVENT_WRITE:
	हाल PACKET3_EVENT_WRITE_EOP:
	हाल PACKET3_EVENT_WRITE_EOS:
	हाल PACKET3_SET_CONTEXT_REG:
	हाल PACKET3_SET_CONTEXT_REG_INसूचीECT:
	हाल PACKET3_SET_SH_REG:
	हाल PACKET3_SET_SH_REG_OFFSET:
	हाल PACKET3_INCREMENT_DE_COUNTER:
	हाल PACKET3_WAIT_ON_CE_COUNTER:
	हाल PACKET3_WAIT_ON_AVAIL_BUFFER:
	हाल PACKET3_ME_WRITE:
		अवरोध;
	हाल PACKET3_COPY_DATA:
		अगर ((idx_value & 0xf00) == 0) अणु
			reg = ib[idx + 3] * 4;
			अगर (!si_vm_reg_valid(reg))
				वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल PACKET3_WRITE_DATA:
		अगर ((idx_value & 0xf00) == 0) अणु
			start_reg = ib[idx + 1] * 4;
			अगर (idx_value & 0x10000) अणु
				अगर (!si_vm_reg_valid(start_reg))
					वापस -EINVAL;
			पूर्ण अन्यथा अणु
				क्रम (i = 0; i < (pkt->count - 2); i++) अणु
					reg = start_reg + (4 * i);
					अगर (!si_vm_reg_valid(reg))
						वापस -EINVAL;
				पूर्ण
			पूर्ण
		पूर्ण
		अवरोध;
	हाल PACKET3_COND_WRITE:
		अगर (idx_value & 0x100) अणु
			reg = ib[idx + 5] * 4;
			अगर (!si_vm_reg_valid(reg))
				वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल PACKET3_COPY_DW:
		अगर (idx_value & 0x2) अणु
			reg = ib[idx + 3] * 4;
			अगर (!si_vm_reg_valid(reg))
				वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल PACKET3_SET_CONFIG_REG:
		start_reg = (idx_value << 2) + PACKET3_SET_CONFIG_REG_START;
		end_reg = 4 * pkt->count + start_reg - 4;
		अगर ((start_reg < PACKET3_SET_CONFIG_REG_START) ||
		    (start_reg >= PACKET3_SET_CONFIG_REG_END) ||
		    (end_reg >= PACKET3_SET_CONFIG_REG_END)) अणु
			DRM_ERROR("bad PACKET3_SET_CONFIG_REG\n");
			वापस -EINVAL;
		पूर्ण
		क्रम (i = 0; i < pkt->count; i++) अणु
			reg = start_reg + (4 * i);
			अगर (!si_vm_reg_valid(reg))
				वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल PACKET3_CP_DMA:
		r = si_vm_packet3_cp_dma_check(ib, idx);
		अगर (r)
			वापस r;
		अवरोध;
	शेष:
		DRM_ERROR("Invalid GFX packet3: 0x%x\n", pkt->opcode);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक si_vm_packet3_compute_check(काष्ठा radeon_device *rdev,
				       u32 *ib, काष्ठा radeon_cs_packet *pkt)
अणु
	पूर्णांक r;
	u32 idx = pkt->idx + 1;
	u32 idx_value = ib[idx];
	u32 start_reg, reg, i;

	चयन (pkt->opcode) अणु
	हाल PACKET3_NOP:
	हाल PACKET3_SET_BASE:
	हाल PACKET3_CLEAR_STATE:
	हाल PACKET3_DISPATCH_सूचीECT:
	हाल PACKET3_DISPATCH_INसूचीECT:
	हाल PACKET3_ALLOC_GDS:
	हाल PACKET3_WRITE_GDS_RAM:
	हाल PACKET3_ATOMIC_GDS:
	हाल PACKET3_ATOMIC:
	हाल PACKET3_OCCLUSION_QUERY:
	हाल PACKET3_SET_PREDICATION:
	हाल PACKET3_COND_EXEC:
	हाल PACKET3_PRED_EXEC:
	हाल PACKET3_CONTEXT_CONTROL:
	हाल PACKET3_STRMOUT_BUFFER_UPDATE:
	हाल PACKET3_WAIT_REG_MEM:
	हाल PACKET3_MEM_WRITE:
	हाल PACKET3_PFP_SYNC_ME:
	हाल PACKET3_SURFACE_SYNC:
	हाल PACKET3_EVENT_WRITE:
	हाल PACKET3_EVENT_WRITE_EOP:
	हाल PACKET3_EVENT_WRITE_EOS:
	हाल PACKET3_SET_CONTEXT_REG:
	हाल PACKET3_SET_CONTEXT_REG_INसूचीECT:
	हाल PACKET3_SET_SH_REG:
	हाल PACKET3_SET_SH_REG_OFFSET:
	हाल PACKET3_INCREMENT_DE_COUNTER:
	हाल PACKET3_WAIT_ON_CE_COUNTER:
	हाल PACKET3_WAIT_ON_AVAIL_BUFFER:
	हाल PACKET3_ME_WRITE:
		अवरोध;
	हाल PACKET3_COPY_DATA:
		अगर ((idx_value & 0xf00) == 0) अणु
			reg = ib[idx + 3] * 4;
			अगर (!si_vm_reg_valid(reg))
				वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल PACKET3_WRITE_DATA:
		अगर ((idx_value & 0xf00) == 0) अणु
			start_reg = ib[idx + 1] * 4;
			अगर (idx_value & 0x10000) अणु
				अगर (!si_vm_reg_valid(start_reg))
					वापस -EINVAL;
			पूर्ण अन्यथा अणु
				क्रम (i = 0; i < (pkt->count - 2); i++) अणु
					reg = start_reg + (4 * i);
					अगर (!si_vm_reg_valid(reg))
						वापस -EINVAL;
				पूर्ण
			पूर्ण
		पूर्ण
		अवरोध;
	हाल PACKET3_COND_WRITE:
		अगर (idx_value & 0x100) अणु
			reg = ib[idx + 5] * 4;
			अगर (!si_vm_reg_valid(reg))
				वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल PACKET3_COPY_DW:
		अगर (idx_value & 0x2) अणु
			reg = ib[idx + 3] * 4;
			अगर (!si_vm_reg_valid(reg))
				वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल PACKET3_CP_DMA:
		r = si_vm_packet3_cp_dma_check(ib, idx);
		अगर (r)
			वापस r;
		अवरोध;
	शेष:
		DRM_ERROR("Invalid Compute packet3: 0x%x\n", pkt->opcode);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक si_ib_parse(काष्ठा radeon_device *rdev, काष्ठा radeon_ib *ib)
अणु
	पूर्णांक ret = 0;
	u32 idx = 0, i;
	काष्ठा radeon_cs_packet pkt;

	करो अणु
		pkt.idx = idx;
		pkt.type = RADEON_CP_PACKET_GET_TYPE(ib->ptr[idx]);
		pkt.count = RADEON_CP_PACKET_GET_COUNT(ib->ptr[idx]);
		pkt.one_reg_wr = 0;
		चयन (pkt.type) अणु
		हाल RADEON_PACKET_TYPE0:
			dev_err(rdev->dev, "Packet0 not allowed!\n");
			ret = -EINVAL;
			अवरोध;
		हाल RADEON_PACKET_TYPE2:
			idx += 1;
			अवरोध;
		हाल RADEON_PACKET_TYPE3:
			pkt.opcode = RADEON_CP_PACKET3_GET_OPCODE(ib->ptr[idx]);
			अगर (ib->is_स्थिर_ib)
				ret = si_vm_packet3_ce_check(rdev, ib->ptr, &pkt);
			अन्यथा अणु
				चयन (ib->ring) अणु
				हाल RADEON_RING_TYPE_GFX_INDEX:
					ret = si_vm_packet3_gfx_check(rdev, ib->ptr, &pkt);
					अवरोध;
				हाल CAYMAN_RING_TYPE_CP1_INDEX:
				हाल CAYMAN_RING_TYPE_CP2_INDEX:
					ret = si_vm_packet3_compute_check(rdev, ib->ptr, &pkt);
					अवरोध;
				शेष:
					dev_err(rdev->dev, "Non-PM4 ring %d !\n", ib->ring);
					ret = -EINVAL;
					अवरोध;
				पूर्ण
			पूर्ण
			idx += pkt.count + 2;
			अवरोध;
		शेष:
			dev_err(rdev->dev, "Unknown packet type %d !\n", pkt.type);
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		अगर (ret) अणु
			क्रम (i = 0; i < ib->length_dw; i++) अणु
				अगर (i == idx)
					prपूर्णांकk("\t0x%08x <---\n", ib->ptr[i]);
				अन्यथा
					prपूर्णांकk("\t0x%08x\n", ib->ptr[i]);
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण जबतक (idx < ib->length_dw);

	वापस ret;
पूर्ण

/*
 * vm
 */
पूर्णांक si_vm_init(काष्ठा radeon_device *rdev)
अणु
	/* number of VMs */
	rdev->vm_manager.nvm = 16;
	/* base offset of vram pages */
	rdev->vm_manager.vram_base_offset = 0;

	वापस 0;
पूर्ण

व्योम si_vm_fini(काष्ठा radeon_device *rdev)
अणु
पूर्ण

/**
 * si_vm_decode_fault - prपूर्णांक human पढ़ोable fault info
 *
 * @rdev: radeon_device poपूर्णांकer
 * @status: VM_CONTEXT1_PROTECTION_FAULT_STATUS रेजिस्टर value
 * @addr: VM_CONTEXT1_PROTECTION_FAULT_ADDR रेजिस्टर value
 *
 * Prपूर्णांक human पढ़ोable fault inक्रमmation (SI).
 */
अटल व्योम si_vm_decode_fault(काष्ठा radeon_device *rdev,
			       u32 status, u32 addr)
अणु
	u32 mc_id = (status & MEMORY_CLIENT_ID_MASK) >> MEMORY_CLIENT_ID_SHIFT;
	u32 vmid = (status & FAULT_VMID_MASK) >> FAULT_VMID_SHIFT;
	u32 protections = (status & PROTECTIONS_MASK) >> PROTECTIONS_SHIFT;
	अक्षर *block;

	अगर (rdev->family == CHIP_TAHITI) अणु
		चयन (mc_id) अणु
		हाल 160:
		हाल 144:
		हाल 96:
		हाल 80:
		हाल 224:
		हाल 208:
		हाल 32:
		हाल 16:
			block = "CB";
			अवरोध;
		हाल 161:
		हाल 145:
		हाल 97:
		हाल 81:
		हाल 225:
		हाल 209:
		हाल 33:
		हाल 17:
			block = "CB_FMASK";
			अवरोध;
		हाल 162:
		हाल 146:
		हाल 98:
		हाल 82:
		हाल 226:
		हाल 210:
		हाल 34:
		हाल 18:
			block = "CB_CMASK";
			अवरोध;
		हाल 163:
		हाल 147:
		हाल 99:
		हाल 83:
		हाल 227:
		हाल 211:
		हाल 35:
		हाल 19:
			block = "CB_IMMED";
			अवरोध;
		हाल 164:
		हाल 148:
		हाल 100:
		हाल 84:
		हाल 228:
		हाल 212:
		हाल 36:
		हाल 20:
			block = "DB";
			अवरोध;
		हाल 165:
		हाल 149:
		हाल 101:
		हाल 85:
		हाल 229:
		हाल 213:
		हाल 37:
		हाल 21:
			block = "DB_HTILE";
			अवरोध;
		हाल 167:
		हाल 151:
		हाल 103:
		हाल 87:
		हाल 231:
		हाल 215:
		हाल 39:
		हाल 23:
			block = "DB_STEN";
			अवरोध;
		हाल 72:
		हाल 68:
		हाल 64:
		हाल 8:
		हाल 4:
		हाल 0:
		हाल 136:
		हाल 132:
		हाल 128:
		हाल 200:
		हाल 196:
		हाल 192:
			block = "TC";
			अवरोध;
		हाल 112:
		हाल 48:
			block = "CP";
			अवरोध;
		हाल 49:
		हाल 177:
		हाल 50:
		हाल 178:
			block = "SH";
			अवरोध;
		हाल 53:
		हाल 190:
			block = "VGT";
			अवरोध;
		हाल 117:
			block = "IH";
			अवरोध;
		हाल 51:
		हाल 115:
			block = "RLC";
			अवरोध;
		हाल 119:
		हाल 183:
			block = "DMA0";
			अवरोध;
		हाल 61:
			block = "DMA1";
			अवरोध;
		हाल 248:
		हाल 120:
			block = "HDP";
			अवरोध;
		शेष:
			block = "unknown";
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (mc_id) अणु
		हाल 32:
		हाल 16:
		हाल 96:
		हाल 80:
		हाल 160:
		हाल 144:
		हाल 224:
		हाल 208:
			block = "CB";
			अवरोध;
		हाल 33:
		हाल 17:
		हाल 97:
		हाल 81:
		हाल 161:
		हाल 145:
		हाल 225:
		हाल 209:
			block = "CB_FMASK";
			अवरोध;
		हाल 34:
		हाल 18:
		हाल 98:
		हाल 82:
		हाल 162:
		हाल 146:
		हाल 226:
		हाल 210:
			block = "CB_CMASK";
			अवरोध;
		हाल 35:
		हाल 19:
		हाल 99:
		हाल 83:
		हाल 163:
		हाल 147:
		हाल 227:
		हाल 211:
			block = "CB_IMMED";
			अवरोध;
		हाल 36:
		हाल 20:
		हाल 100:
		हाल 84:
		हाल 164:
		हाल 148:
		हाल 228:
		हाल 212:
			block = "DB";
			अवरोध;
		हाल 37:
		हाल 21:
		हाल 101:
		हाल 85:
		हाल 165:
		हाल 149:
		हाल 229:
		हाल 213:
			block = "DB_HTILE";
			अवरोध;
		हाल 39:
		हाल 23:
		हाल 103:
		हाल 87:
		हाल 167:
		हाल 151:
		हाल 231:
		हाल 215:
			block = "DB_STEN";
			अवरोध;
		हाल 72:
		हाल 68:
		हाल 8:
		हाल 4:
		हाल 136:
		हाल 132:
		हाल 200:
		हाल 196:
			block = "TC";
			अवरोध;
		हाल 112:
		हाल 48:
			block = "CP";
			अवरोध;
		हाल 49:
		हाल 177:
		हाल 50:
		हाल 178:
			block = "SH";
			अवरोध;
		हाल 53:
			block = "VGT";
			अवरोध;
		हाल 117:
			block = "IH";
			अवरोध;
		हाल 51:
		हाल 115:
			block = "RLC";
			अवरोध;
		हाल 119:
		हाल 183:
			block = "DMA0";
			अवरोध;
		हाल 61:
			block = "DMA1";
			अवरोध;
		हाल 248:
		हाल 120:
			block = "HDP";
			अवरोध;
		शेष:
			block = "unknown";
			अवरोध;
		पूर्ण
	पूर्ण

	prपूर्णांकk("VM fault (0x%02x, vmid %d) at page %u, %s from %s (%d)\n",
	       protections, vmid, addr,
	       (status & MEMORY_CLIENT_RW_MASK) ? "write" : "read",
	       block, mc_id);
पूर्ण

व्योम si_vm_flush(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring,
		 अचिन्हित vm_id, uपूर्णांक64_t pd_addr)
अणु
	/* ग_लिखो new base address */
	radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_WRITE_DATA, 3));
	radeon_ring_ग_लिखो(ring, (WRITE_DATA_ENGINE_SEL(1) |
				 WRITE_DATA_DST_SEL(0)));

	अगर (vm_id < 8) अणु
		radeon_ring_ग_लिखो(ring,
				  (VM_CONTEXT0_PAGE_TABLE_BASE_ADDR + (vm_id << 2)) >> 2);
	पूर्ण अन्यथा अणु
		radeon_ring_ग_लिखो(ring,
				  (VM_CONTEXT8_PAGE_TABLE_BASE_ADDR + ((vm_id - 8) << 2)) >> 2);
	पूर्ण
	radeon_ring_ग_लिखो(ring, 0);
	radeon_ring_ग_लिखो(ring, pd_addr >> 12);

	/* flush hdp cache */
	radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_WRITE_DATA, 3));
	radeon_ring_ग_लिखो(ring, (WRITE_DATA_ENGINE_SEL(1) |
				 WRITE_DATA_DST_SEL(0)));
	radeon_ring_ग_लिखो(ring, HDP_MEM_COHERENCY_FLUSH_CNTL >> 2);
	radeon_ring_ग_लिखो(ring, 0);
	radeon_ring_ग_लिखो(ring, 0x1);

	/* bits 0-15 are the VM contexts0-15 */
	radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_WRITE_DATA, 3));
	radeon_ring_ग_लिखो(ring, (WRITE_DATA_ENGINE_SEL(1) |
				 WRITE_DATA_DST_SEL(0)));
	radeon_ring_ग_लिखो(ring, VM_INVALIDATE_REQUEST >> 2);
	radeon_ring_ग_लिखो(ring, 0);
	radeon_ring_ग_लिखो(ring, 1 << vm_id);

	/* रुको क्रम the invalidate to complete */
	radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_WAIT_REG_MEM, 5));
	radeon_ring_ग_लिखो(ring, (WAIT_REG_MEM_FUNCTION(0) |  /* always */
				 WAIT_REG_MEM_ENGINE(0))); /* me */
	radeon_ring_ग_लिखो(ring, VM_INVALIDATE_REQUEST >> 2);
	radeon_ring_ग_लिखो(ring, 0);
	radeon_ring_ग_लिखो(ring, 0); /* ref */
	radeon_ring_ग_लिखो(ring, 0); /* mask */
	radeon_ring_ग_लिखो(ring, 0x20); /* poll पूर्णांकerval */

	/* sync PFP to ME, otherwise we might get invalid PFP पढ़ोs */
	radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_PFP_SYNC_ME, 0));
	radeon_ring_ग_लिखो(ring, 0x0);
पूर्ण

/*
 *  Power and घड़ी gating
 */
अटल व्योम si_रुको_क्रम_rlc_serdes(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		अगर (RREG32(RLC_SERDES_MASTER_BUSY_0) == 0)
			अवरोध;
		udelay(1);
	पूर्ण

	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		अगर (RREG32(RLC_SERDES_MASTER_BUSY_1) == 0)
			अवरोध;
		udelay(1);
	पूर्ण
पूर्ण

अटल व्योम si_enable_gui_idle_पूर्णांकerrupt(काष्ठा radeon_device *rdev,
					 bool enable)
अणु
	u32 पंचांगp = RREG32(CP_INT_CNTL_RING0);
	u32 mask;
	पूर्णांक i;

	अगर (enable)
		पंचांगp |= (CNTX_BUSY_INT_ENABLE | CNTX_EMPTY_INT_ENABLE);
	अन्यथा
		पंचांगp &= ~(CNTX_BUSY_INT_ENABLE | CNTX_EMPTY_INT_ENABLE);
	WREG32(CP_INT_CNTL_RING0, पंचांगp);

	अगर (!enable) अणु
		/* पढ़ो a gfx रेजिस्टर */
		पंचांगp = RREG32(DB_DEPTH_INFO);

		mask = RLC_BUSY_STATUS | GFX_POWER_STATUS | GFX_CLOCK_STATUS | GFX_LS_STATUS;
		क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
			अगर ((RREG32(RLC_STAT) & mask) == (GFX_CLOCK_STATUS | GFX_POWER_STATUS))
				अवरोध;
			udelay(1);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम si_set_uvd_dcm(काष्ठा radeon_device *rdev,
			   bool sw_mode)
अणु
	u32 पंचांगp, पंचांगp2;

	पंचांगp = RREG32(UVD_CGC_CTRL);
	पंचांगp &= ~(CLK_OD_MASK | CG_DT_MASK);
	पंचांगp |= DCM | CG_DT(1) | CLK_OD(4);

	अगर (sw_mode) अणु
		पंचांगp &= ~0x7ffff800;
		पंचांगp2 = DYN_OR_EN | DYN_RR_EN | G_DIV_ID(7);
	पूर्ण अन्यथा अणु
		पंचांगp |= 0x7ffff800;
		पंचांगp2 = 0;
	पूर्ण

	WREG32(UVD_CGC_CTRL, पंचांगp);
	WREG32_UVD_CTX(UVD_CGC_CTRL2, पंचांगp2);
पूर्ण

व्योम si_init_uvd_पूर्णांकernal_cg(काष्ठा radeon_device *rdev)
अणु
	bool hw_mode = true;

	अगर (hw_mode) अणु
		si_set_uvd_dcm(rdev, false);
	पूर्ण अन्यथा अणु
		u32 पंचांगp = RREG32(UVD_CGC_CTRL);
		पंचांगp &= ~DCM;
		WREG32(UVD_CGC_CTRL, पंचांगp);
	पूर्ण
पूर्ण

अटल u32 si_halt_rlc(काष्ठा radeon_device *rdev)
अणु
	u32 data, orig;

	orig = data = RREG32(RLC_CNTL);

	अगर (data & RLC_ENABLE) अणु
		data &= ~RLC_ENABLE;
		WREG32(RLC_CNTL, data);

		si_रुको_क्रम_rlc_serdes(rdev);
	पूर्ण

	वापस orig;
पूर्ण

अटल व्योम si_update_rlc(काष्ठा radeon_device *rdev, u32 rlc)
अणु
	u32 पंचांगp;

	पंचांगp = RREG32(RLC_CNTL);
	अगर (पंचांगp != rlc)
		WREG32(RLC_CNTL, rlc);
पूर्ण

अटल व्योम si_enable_dma_pg(काष्ठा radeon_device *rdev, bool enable)
अणु
	u32 data, orig;

	orig = data = RREG32(DMA_PG);
	अगर (enable && (rdev->pg_flags & RADEON_PG_SUPPORT_SDMA))
		data |= PG_CNTL_ENABLE;
	अन्यथा
		data &= ~PG_CNTL_ENABLE;
	अगर (orig != data)
		WREG32(DMA_PG, data);
पूर्ण

अटल व्योम si_init_dma_pg(काष्ठा radeon_device *rdev)
अणु
	u32 पंचांगp;

	WREG32(DMA_PGFSM_WRITE,  0x00002000);
	WREG32(DMA_PGFSM_CONFIG, 0x100010ff);

	क्रम (पंचांगp = 0; पंचांगp < 5; पंचांगp++)
		WREG32(DMA_PGFSM_WRITE, 0);
पूर्ण

अटल व्योम si_enable_gfx_cgpg(काष्ठा radeon_device *rdev,
			       bool enable)
अणु
	u32 पंचांगp;

	अगर (enable && (rdev->pg_flags & RADEON_PG_SUPPORT_GFX_PG)) अणु
		पंचांगp = RLC_PUD(0x10) | RLC_PDD(0x10) | RLC_TTPD(0x10) | RLC_MSD(0x10);
		WREG32(RLC_TTOP_D, पंचांगp);

		पंचांगp = RREG32(RLC_PG_CNTL);
		पंचांगp |= GFX_PG_ENABLE;
		WREG32(RLC_PG_CNTL, पंचांगp);

		पंचांगp = RREG32(RLC_AUTO_PG_CTRL);
		पंचांगp |= AUTO_PG_EN;
		WREG32(RLC_AUTO_PG_CTRL, पंचांगp);
	पूर्ण अन्यथा अणु
		पंचांगp = RREG32(RLC_AUTO_PG_CTRL);
		पंचांगp &= ~AUTO_PG_EN;
		WREG32(RLC_AUTO_PG_CTRL, पंचांगp);

		पंचांगp = RREG32(DB_RENDER_CONTROL);
	पूर्ण
पूर्ण

अटल व्योम si_init_gfx_cgpg(काष्ठा radeon_device *rdev)
अणु
	u32 पंचांगp;

	WREG32(RLC_SAVE_AND_RESTORE_BASE, rdev->rlc.save_restore_gpu_addr >> 8);

	पंचांगp = RREG32(RLC_PG_CNTL);
	पंचांगp |= GFX_PG_SRC;
	WREG32(RLC_PG_CNTL, पंचांगp);

	WREG32(RLC_CLEAR_STATE_RESTORE_BASE, rdev->rlc.clear_state_gpu_addr >> 8);

	पंचांगp = RREG32(RLC_AUTO_PG_CTRL);

	पंचांगp &= ~GRBM_REG_SGIT_MASK;
	पंचांगp |= GRBM_REG_SGIT(0x700);
	पंचांगp &= ~PG_AFTER_GRBM_REG_ST_MASK;
	WREG32(RLC_AUTO_PG_CTRL, पंचांगp);
पूर्ण

अटल u32 si_get_cu_active_biपंचांगap(काष्ठा radeon_device *rdev, u32 se, u32 sh)
अणु
	u32 mask = 0, पंचांगp, पंचांगp1;
	पूर्णांक i;

	si_select_se_sh(rdev, se, sh);
	पंचांगp = RREG32(CC_GC_SHADER_ARRAY_CONFIG);
	पंचांगp1 = RREG32(GC_USER_SHADER_ARRAY_CONFIG);
	si_select_se_sh(rdev, 0xffffffff, 0xffffffff);

	पंचांगp &= 0xffff0000;

	पंचांगp |= पंचांगp1;
	पंचांगp >>= 16;

	क्रम (i = 0; i < rdev->config.si.max_cu_per_sh; i ++) अणु
		mask <<= 1;
		mask |= 1;
	पूर्ण

	वापस (~पंचांगp) & mask;
पूर्ण

अटल व्योम si_init_ao_cu_mask(काष्ठा radeon_device *rdev)
अणु
	u32 i, j, k, active_cu_number = 0;
	u32 mask, counter, cu_biपंचांगap;
	u32 पंचांगp = 0;

	क्रम (i = 0; i < rdev->config.si.max_shader_engines; i++) अणु
		क्रम (j = 0; j < rdev->config.si.max_sh_per_se; j++) अणु
			mask = 1;
			cu_biपंचांगap = 0;
			counter  = 0;
			क्रम (k = 0; k < rdev->config.si.max_cu_per_sh; k++) अणु
				अगर (si_get_cu_active_biपंचांगap(rdev, i, j) & mask) अणु
					अगर (counter < 2)
						cu_biपंचांगap |= mask;
					counter++;
				पूर्ण
				mask <<= 1;
			पूर्ण

			active_cu_number += counter;
			पंचांगp |= (cu_biपंचांगap << (i * 16 + j * 8));
		पूर्ण
	पूर्ण

	WREG32(RLC_PG_AO_CU_MASK, पंचांगp);

	पंचांगp = RREG32(RLC_MAX_PG_CU);
	पंचांगp &= ~MAX_PU_CU_MASK;
	पंचांगp |= MAX_PU_CU(active_cu_number);
	WREG32(RLC_MAX_PG_CU, पंचांगp);
पूर्ण

अटल व्योम si_enable_cgcg(काष्ठा radeon_device *rdev,
			   bool enable)
अणु
	u32 data, orig, पंचांगp;

	orig = data = RREG32(RLC_CGCG_CGLS_CTRL);

	अगर (enable && (rdev->cg_flags & RADEON_CG_SUPPORT_GFX_CGCG)) अणु
		si_enable_gui_idle_पूर्णांकerrupt(rdev, true);

		WREG32(RLC_GCPM_GENERAL_3, 0x00000080);

		पंचांगp = si_halt_rlc(rdev);

		WREG32(RLC_SERDES_WR_MASTER_MASK_0, 0xffffffff);
		WREG32(RLC_SERDES_WR_MASTER_MASK_1, 0xffffffff);
		WREG32(RLC_SERDES_WR_CTRL, 0x00b000ff);

		si_रुको_क्रम_rlc_serdes(rdev);

		si_update_rlc(rdev, पंचांगp);

		WREG32(RLC_SERDES_WR_CTRL, 0x007000ff);

		data |= CGCG_EN | CGLS_EN;
	पूर्ण अन्यथा अणु
		si_enable_gui_idle_पूर्णांकerrupt(rdev, false);

		RREG32(CB_CGTT_SCLK_CTRL);
		RREG32(CB_CGTT_SCLK_CTRL);
		RREG32(CB_CGTT_SCLK_CTRL);
		RREG32(CB_CGTT_SCLK_CTRL);

		data &= ~(CGCG_EN | CGLS_EN);
	पूर्ण

	अगर (orig != data)
		WREG32(RLC_CGCG_CGLS_CTRL, data);
पूर्ण

अटल व्योम si_enable_mgcg(काष्ठा radeon_device *rdev,
			   bool enable)
अणु
	u32 data, orig, पंचांगp = 0;

	अगर (enable && (rdev->cg_flags & RADEON_CG_SUPPORT_GFX_MGCG)) अणु
		orig = data = RREG32(CGTS_SM_CTRL_REG);
		data = 0x96940200;
		अगर (orig != data)
			WREG32(CGTS_SM_CTRL_REG, data);

		अगर (rdev->cg_flags & RADEON_CG_SUPPORT_GFX_CP_LS) अणु
			orig = data = RREG32(CP_MEM_SLP_CNTL);
			data |= CP_MEM_LS_EN;
			अगर (orig != data)
				WREG32(CP_MEM_SLP_CNTL, data);
		पूर्ण

		orig = data = RREG32(RLC_CGTT_MGCG_OVERRIDE);
		data &= 0xffffffc0;
		अगर (orig != data)
			WREG32(RLC_CGTT_MGCG_OVERRIDE, data);

		पंचांगp = si_halt_rlc(rdev);

		WREG32(RLC_SERDES_WR_MASTER_MASK_0, 0xffffffff);
		WREG32(RLC_SERDES_WR_MASTER_MASK_1, 0xffffffff);
		WREG32(RLC_SERDES_WR_CTRL, 0x00d000ff);

		si_update_rlc(rdev, पंचांगp);
	पूर्ण अन्यथा अणु
		orig = data = RREG32(RLC_CGTT_MGCG_OVERRIDE);
		data |= 0x00000003;
		अगर (orig != data)
			WREG32(RLC_CGTT_MGCG_OVERRIDE, data);

		data = RREG32(CP_MEM_SLP_CNTL);
		अगर (data & CP_MEM_LS_EN) अणु
			data &= ~CP_MEM_LS_EN;
			WREG32(CP_MEM_SLP_CNTL, data);
		पूर्ण
		orig = data = RREG32(CGTS_SM_CTRL_REG);
		data |= LS_OVERRIDE | OVERRIDE;
		अगर (orig != data)
			WREG32(CGTS_SM_CTRL_REG, data);

		पंचांगp = si_halt_rlc(rdev);

		WREG32(RLC_SERDES_WR_MASTER_MASK_0, 0xffffffff);
		WREG32(RLC_SERDES_WR_MASTER_MASK_1, 0xffffffff);
		WREG32(RLC_SERDES_WR_CTRL, 0x00e000ff);

		si_update_rlc(rdev, पंचांगp);
	पूर्ण
पूर्ण

अटल व्योम si_enable_uvd_mgcg(काष्ठा radeon_device *rdev,
			       bool enable)
अणु
	u32 orig, data, पंचांगp;

	अगर (enable && (rdev->cg_flags & RADEON_CG_SUPPORT_UVD_MGCG)) अणु
		पंचांगp = RREG32_UVD_CTX(UVD_CGC_MEM_CTRL);
		पंचांगp |= 0x3fff;
		WREG32_UVD_CTX(UVD_CGC_MEM_CTRL, पंचांगp);

		orig = data = RREG32(UVD_CGC_CTRL);
		data |= DCM;
		अगर (orig != data)
			WREG32(UVD_CGC_CTRL, data);

		WREG32_SMC(SMC_CG_IND_START + CG_CGTT_LOCAL_0, 0);
		WREG32_SMC(SMC_CG_IND_START + CG_CGTT_LOCAL_1, 0);
	पूर्ण अन्यथा अणु
		पंचांगp = RREG32_UVD_CTX(UVD_CGC_MEM_CTRL);
		पंचांगp &= ~0x3fff;
		WREG32_UVD_CTX(UVD_CGC_MEM_CTRL, पंचांगp);

		orig = data = RREG32(UVD_CGC_CTRL);
		data &= ~DCM;
		अगर (orig != data)
			WREG32(UVD_CGC_CTRL, data);

		WREG32_SMC(SMC_CG_IND_START + CG_CGTT_LOCAL_0, 0xffffffff);
		WREG32_SMC(SMC_CG_IND_START + CG_CGTT_LOCAL_1, 0xffffffff);
	पूर्ण
पूर्ण

अटल स्थिर u32 mc_cg_रेजिस्टरs[] =
अणु
	MC_HUB_MISC_HUB_CG,
	MC_HUB_MISC_SIP_CG,
	MC_HUB_MISC_VM_CG,
	MC_XPB_CLK_GAT,
	ATC_MISC_CG,
	MC_CITF_MISC_WR_CG,
	MC_CITF_MISC_RD_CG,
	MC_CITF_MISC_VM_CG,
	VM_L2_CG,
पूर्ण;

अटल व्योम si_enable_mc_ls(काष्ठा radeon_device *rdev,
			    bool enable)
अणु
	पूर्णांक i;
	u32 orig, data;

	क्रम (i = 0; i < ARRAY_SIZE(mc_cg_रेजिस्टरs); i++) अणु
		orig = data = RREG32(mc_cg_रेजिस्टरs[i]);
		अगर (enable && (rdev->cg_flags & RADEON_CG_SUPPORT_MC_LS))
			data |= MC_LS_ENABLE;
		अन्यथा
			data &= ~MC_LS_ENABLE;
		अगर (data != orig)
			WREG32(mc_cg_रेजिस्टरs[i], data);
	पूर्ण
पूर्ण

अटल व्योम si_enable_mc_mgcg(काष्ठा radeon_device *rdev,
			       bool enable)
अणु
	पूर्णांक i;
	u32 orig, data;

	क्रम (i = 0; i < ARRAY_SIZE(mc_cg_रेजिस्टरs); i++) अणु
		orig = data = RREG32(mc_cg_रेजिस्टरs[i]);
		अगर (enable && (rdev->cg_flags & RADEON_CG_SUPPORT_MC_MGCG))
			data |= MC_CG_ENABLE;
		अन्यथा
			data &= ~MC_CG_ENABLE;
		अगर (data != orig)
			WREG32(mc_cg_रेजिस्टरs[i], data);
	पूर्ण
पूर्ण

अटल व्योम si_enable_dma_mgcg(काष्ठा radeon_device *rdev,
			       bool enable)
अणु
	u32 orig, data, offset;
	पूर्णांक i;

	अगर (enable && (rdev->cg_flags & RADEON_CG_SUPPORT_SDMA_MGCG)) अणु
		क्रम (i = 0; i < 2; i++) अणु
			अगर (i == 0)
				offset = DMA0_REGISTER_OFFSET;
			अन्यथा
				offset = DMA1_REGISTER_OFFSET;
			orig = data = RREG32(DMA_POWER_CNTL + offset);
			data &= ~MEM_POWER_OVERRIDE;
			अगर (data != orig)
				WREG32(DMA_POWER_CNTL + offset, data);
			WREG32(DMA_CLK_CTRL + offset, 0x00000100);
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < 2; i++) अणु
			अगर (i == 0)
				offset = DMA0_REGISTER_OFFSET;
			अन्यथा
				offset = DMA1_REGISTER_OFFSET;
			orig = data = RREG32(DMA_POWER_CNTL + offset);
			data |= MEM_POWER_OVERRIDE;
			अगर (data != orig)
				WREG32(DMA_POWER_CNTL + offset, data);

			orig = data = RREG32(DMA_CLK_CTRL + offset);
			data = 0xff000000;
			अगर (data != orig)
				WREG32(DMA_CLK_CTRL + offset, data);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम si_enable_bअगर_mgls(काष्ठा radeon_device *rdev,
			       bool enable)
अणु
	u32 orig, data;

	orig = data = RREG32_PCIE(PCIE_CNTL2);

	अगर (enable && (rdev->cg_flags & RADEON_CG_SUPPORT_BIF_LS))
		data |= SLV_MEM_LS_EN | MST_MEM_LS_EN |
			REPLAY_MEM_LS_EN | SLV_MEM_AGGRESSIVE_LS_EN;
	अन्यथा
		data &= ~(SLV_MEM_LS_EN | MST_MEM_LS_EN |
			  REPLAY_MEM_LS_EN | SLV_MEM_AGGRESSIVE_LS_EN);

	अगर (orig != data)
		WREG32_PCIE(PCIE_CNTL2, data);
पूर्ण

अटल व्योम si_enable_hdp_mgcg(काष्ठा radeon_device *rdev,
			       bool enable)
अणु
	u32 orig, data;

	orig = data = RREG32(HDP_HOST_PATH_CNTL);

	अगर (enable && (rdev->cg_flags & RADEON_CG_SUPPORT_HDP_MGCG))
		data &= ~CLOCK_GATING_DIS;
	अन्यथा
		data |= CLOCK_GATING_DIS;

	अगर (orig != data)
		WREG32(HDP_HOST_PATH_CNTL, data);
पूर्ण

अटल व्योम si_enable_hdp_ls(काष्ठा radeon_device *rdev,
			     bool enable)
अणु
	u32 orig, data;

	orig = data = RREG32(HDP_MEM_POWER_LS);

	अगर (enable && (rdev->cg_flags & RADEON_CG_SUPPORT_HDP_LS))
		data |= HDP_LS_ENABLE;
	अन्यथा
		data &= ~HDP_LS_ENABLE;

	अगर (orig != data)
		WREG32(HDP_MEM_POWER_LS, data);
पूर्ण

अटल व्योम si_update_cg(काष्ठा radeon_device *rdev,
			 u32 block, bool enable)
अणु
	अगर (block & RADEON_CG_BLOCK_GFX) अणु
		si_enable_gui_idle_पूर्णांकerrupt(rdev, false);
		/* order matters! */
		अगर (enable) अणु
			si_enable_mgcg(rdev, true);
			si_enable_cgcg(rdev, true);
		पूर्ण अन्यथा अणु
			si_enable_cgcg(rdev, false);
			si_enable_mgcg(rdev, false);
		पूर्ण
		si_enable_gui_idle_पूर्णांकerrupt(rdev, true);
	पूर्ण

	अगर (block & RADEON_CG_BLOCK_MC) अणु
		si_enable_mc_mgcg(rdev, enable);
		si_enable_mc_ls(rdev, enable);
	पूर्ण

	अगर (block & RADEON_CG_BLOCK_SDMA) अणु
		si_enable_dma_mgcg(rdev, enable);
	पूर्ण

	अगर (block & RADEON_CG_BLOCK_BIF) अणु
		si_enable_bअगर_mgls(rdev, enable);
	पूर्ण

	अगर (block & RADEON_CG_BLOCK_UVD) अणु
		अगर (rdev->has_uvd) अणु
			si_enable_uvd_mgcg(rdev, enable);
		पूर्ण
	पूर्ण

	अगर (block & RADEON_CG_BLOCK_HDP) अणु
		si_enable_hdp_mgcg(rdev, enable);
		si_enable_hdp_ls(rdev, enable);
	पूर्ण
पूर्ण

अटल व्योम si_init_cg(काष्ठा radeon_device *rdev)
अणु
	si_update_cg(rdev, (RADEON_CG_BLOCK_GFX |
			    RADEON_CG_BLOCK_MC |
			    RADEON_CG_BLOCK_SDMA |
			    RADEON_CG_BLOCK_BIF |
			    RADEON_CG_BLOCK_HDP), true);
	अगर (rdev->has_uvd) अणु
		si_update_cg(rdev, RADEON_CG_BLOCK_UVD, true);
		si_init_uvd_पूर्णांकernal_cg(rdev);
	पूर्ण
पूर्ण

अटल व्योम si_fini_cg(काष्ठा radeon_device *rdev)
अणु
	अगर (rdev->has_uvd) अणु
		si_update_cg(rdev, RADEON_CG_BLOCK_UVD, false);
	पूर्ण
	si_update_cg(rdev, (RADEON_CG_BLOCK_GFX |
			    RADEON_CG_BLOCK_MC |
			    RADEON_CG_BLOCK_SDMA |
			    RADEON_CG_BLOCK_BIF |
			    RADEON_CG_BLOCK_HDP), false);
पूर्ण

u32 si_get_csb_size(काष्ठा radeon_device *rdev)
अणु
	u32 count = 0;
	स्थिर काष्ठा cs_section_def *sect = शून्य;
	स्थिर काष्ठा cs_extent_def *ext = शून्य;

	अगर (rdev->rlc.cs_data == शून्य)
		वापस 0;

	/* begin clear state */
	count += 2;
	/* context control state */
	count += 3;

	क्रम (sect = rdev->rlc.cs_data; sect->section != शून्य; ++sect) अणु
		क्रम (ext = sect->section; ext->extent != शून्य; ++ext) अणु
			अगर (sect->id == SECT_CONTEXT)
				count += 2 + ext->reg_count;
			अन्यथा
				वापस 0;
		पूर्ण
	पूर्ण
	/* pa_sc_raster_config */
	count += 3;
	/* end clear state */
	count += 2;
	/* clear state */
	count += 2;

	वापस count;
पूर्ण

व्योम si_get_csb_buffer(काष्ठा radeon_device *rdev, अस्थिर u32 *buffer)
अणु
	u32 count = 0, i;
	स्थिर काष्ठा cs_section_def *sect = शून्य;
	स्थिर काष्ठा cs_extent_def *ext = शून्य;

	अगर (rdev->rlc.cs_data == शून्य)
		वापस;
	अगर (buffer == शून्य)
		वापस;

	buffer[count++] = cpu_to_le32(PACKET3(PACKET3_PREAMBLE_CNTL, 0));
	buffer[count++] = cpu_to_le32(PACKET3_PREAMBLE_BEGIN_CLEAR_STATE);

	buffer[count++] = cpu_to_le32(PACKET3(PACKET3_CONTEXT_CONTROL, 1));
	buffer[count++] = cpu_to_le32(0x80000000);
	buffer[count++] = cpu_to_le32(0x80000000);

	क्रम (sect = rdev->rlc.cs_data; sect->section != शून्य; ++sect) अणु
		क्रम (ext = sect->section; ext->extent != शून्य; ++ext) अणु
			अगर (sect->id == SECT_CONTEXT) अणु
				buffer[count++] =
					cpu_to_le32(PACKET3(PACKET3_SET_CONTEXT_REG, ext->reg_count));
				buffer[count++] = cpu_to_le32(ext->reg_index - 0xa000);
				क्रम (i = 0; i < ext->reg_count; i++)
					buffer[count++] = cpu_to_le32(ext->extent[i]);
			पूर्ण अन्यथा अणु
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण

	buffer[count++] = cpu_to_le32(PACKET3(PACKET3_SET_CONTEXT_REG, 1));
	buffer[count++] = cpu_to_le32(PA_SC_RASTER_CONFIG - PACKET3_SET_CONTEXT_REG_START);
	चयन (rdev->family) अणु
	हाल CHIP_TAHITI:
	हाल CHIP_PITCAIRN:
		buffer[count++] = cpu_to_le32(0x2a00126a);
		अवरोध;
	हाल CHIP_VERDE:
		buffer[count++] = cpu_to_le32(0x0000124a);
		अवरोध;
	हाल CHIP_OLAND:
		buffer[count++] = cpu_to_le32(0x00000082);
		अवरोध;
	हाल CHIP_HAIन_अंक:
		buffer[count++] = cpu_to_le32(0x00000000);
		अवरोध;
	शेष:
		buffer[count++] = cpu_to_le32(0x00000000);
		अवरोध;
	पूर्ण

	buffer[count++] = cpu_to_le32(PACKET3(PACKET3_PREAMBLE_CNTL, 0));
	buffer[count++] = cpu_to_le32(PACKET3_PREAMBLE_END_CLEAR_STATE);

	buffer[count++] = cpu_to_le32(PACKET3(PACKET3_CLEAR_STATE, 0));
	buffer[count++] = cpu_to_le32(0);
पूर्ण

अटल व्योम si_init_pg(काष्ठा radeon_device *rdev)
अणु
	अगर (rdev->pg_flags) अणु
		अगर (rdev->pg_flags & RADEON_PG_SUPPORT_SDMA) अणु
			si_init_dma_pg(rdev);
		पूर्ण
		si_init_ao_cu_mask(rdev);
		अगर (rdev->pg_flags & RADEON_PG_SUPPORT_GFX_PG) अणु
			si_init_gfx_cgpg(rdev);
		पूर्ण अन्यथा अणु
			WREG32(RLC_SAVE_AND_RESTORE_BASE, rdev->rlc.save_restore_gpu_addr >> 8);
			WREG32(RLC_CLEAR_STATE_RESTORE_BASE, rdev->rlc.clear_state_gpu_addr >> 8);
		पूर्ण
		si_enable_dma_pg(rdev, true);
		si_enable_gfx_cgpg(rdev, true);
	पूर्ण अन्यथा अणु
		WREG32(RLC_SAVE_AND_RESTORE_BASE, rdev->rlc.save_restore_gpu_addr >> 8);
		WREG32(RLC_CLEAR_STATE_RESTORE_BASE, rdev->rlc.clear_state_gpu_addr >> 8);
	पूर्ण
पूर्ण

अटल व्योम si_fini_pg(काष्ठा radeon_device *rdev)
अणु
	अगर (rdev->pg_flags) अणु
		si_enable_dma_pg(rdev, false);
		si_enable_gfx_cgpg(rdev, false);
	पूर्ण
पूर्ण

/*
 * RLC
 */
व्योम si_rlc_reset(काष्ठा radeon_device *rdev)
अणु
	u32 पंचांगp = RREG32(GRBM_SOFT_RESET);

	पंचांगp |= SOFT_RESET_RLC;
	WREG32(GRBM_SOFT_RESET, पंचांगp);
	udelay(50);
	पंचांगp &= ~SOFT_RESET_RLC;
	WREG32(GRBM_SOFT_RESET, पंचांगp);
	udelay(50);
पूर्ण

अटल व्योम si_rlc_stop(काष्ठा radeon_device *rdev)
अणु
	WREG32(RLC_CNTL, 0);

	si_enable_gui_idle_पूर्णांकerrupt(rdev, false);

	si_रुको_क्रम_rlc_serdes(rdev);
पूर्ण

अटल व्योम si_rlc_start(काष्ठा radeon_device *rdev)
अणु
	WREG32(RLC_CNTL, RLC_ENABLE);

	si_enable_gui_idle_पूर्णांकerrupt(rdev, true);

	udelay(50);
पूर्ण

अटल bool si_lbpw_supported(काष्ठा radeon_device *rdev)
अणु
	u32 पंचांगp;

	/* Enable LBPW only क्रम DDR3 */
	पंचांगp = RREG32(MC_SEQ_MISC0);
	अगर ((पंचांगp & 0xF0000000) == 0xB0000000)
		वापस true;
	वापस false;
पूर्ण

अटल व्योम si_enable_lbpw(काष्ठा radeon_device *rdev, bool enable)
अणु
	u32 पंचांगp;

	पंचांगp = RREG32(RLC_LB_CNTL);
	अगर (enable)
		पंचांगp |= LOAD_BALANCE_ENABLE;
	अन्यथा
		पंचांगp &= ~LOAD_BALANCE_ENABLE;
	WREG32(RLC_LB_CNTL, पंचांगp);

	अगर (!enable) अणु
		si_select_se_sh(rdev, 0xffffffff, 0xffffffff);
		WREG32(SPI_LB_CU_MASK, 0x00ff);
	पूर्ण
पूर्ण

अटल पूर्णांक si_rlc_resume(काष्ठा radeon_device *rdev)
अणु
	u32 i;

	अगर (!rdev->rlc_fw)
		वापस -EINVAL;

	si_rlc_stop(rdev);

	si_rlc_reset(rdev);

	si_init_pg(rdev);

	si_init_cg(rdev);

	WREG32(RLC_RL_BASE, 0);
	WREG32(RLC_RL_SIZE, 0);
	WREG32(RLC_LB_CNTL, 0);
	WREG32(RLC_LB_CNTR_MAX, 0xffffffff);
	WREG32(RLC_LB_CNTR_INIT, 0);
	WREG32(RLC_LB_INIT_CU_MASK, 0xffffffff);

	WREG32(RLC_MC_CNTL, 0);
	WREG32(RLC_UCODE_CNTL, 0);

	अगर (rdev->new_fw) अणु
		स्थिर काष्ठा rlc_firmware_header_v1_0 *hdr =
			(स्थिर काष्ठा rlc_firmware_header_v1_0 *)rdev->rlc_fw->data;
		u32 fw_size = le32_to_cpu(hdr->header.ucode_size_bytes) / 4;
		स्थिर __le32 *fw_data = (स्थिर __le32 *)
			(rdev->rlc_fw->data + le32_to_cpu(hdr->header.ucode_array_offset_bytes));

		radeon_ucode_prपूर्णांक_rlc_hdr(&hdr->header);

		क्रम (i = 0; i < fw_size; i++) अणु
			WREG32(RLC_UCODE_ADDR, i);
			WREG32(RLC_UCODE_DATA, le32_to_cpup(fw_data++));
		पूर्ण
	पूर्ण अन्यथा अणु
		स्थिर __be32 *fw_data =
			(स्थिर __be32 *)rdev->rlc_fw->data;
		क्रम (i = 0; i < SI_RLC_UCODE_SIZE; i++) अणु
			WREG32(RLC_UCODE_ADDR, i);
			WREG32(RLC_UCODE_DATA, be32_to_cpup(fw_data++));
		पूर्ण
	पूर्ण
	WREG32(RLC_UCODE_ADDR, 0);

	si_enable_lbpw(rdev, si_lbpw_supported(rdev));

	si_rlc_start(rdev);

	वापस 0;
पूर्ण

अटल व्योम si_enable_पूर्णांकerrupts(काष्ठा radeon_device *rdev)
अणु
	u32 ih_cntl = RREG32(IH_CNTL);
	u32 ih_rb_cntl = RREG32(IH_RB_CNTL);

	ih_cntl |= ENABLE_INTR;
	ih_rb_cntl |= IH_RB_ENABLE;
	WREG32(IH_CNTL, ih_cntl);
	WREG32(IH_RB_CNTL, ih_rb_cntl);
	rdev->ih.enabled = true;
पूर्ण

अटल व्योम si_disable_पूर्णांकerrupts(काष्ठा radeon_device *rdev)
अणु
	u32 ih_rb_cntl = RREG32(IH_RB_CNTL);
	u32 ih_cntl = RREG32(IH_CNTL);

	ih_rb_cntl &= ~IH_RB_ENABLE;
	ih_cntl &= ~ENABLE_INTR;
	WREG32(IH_RB_CNTL, ih_rb_cntl);
	WREG32(IH_CNTL, ih_cntl);
	/* set rptr, wptr to 0 */
	WREG32(IH_RB_RPTR, 0);
	WREG32(IH_RB_WPTR, 0);
	rdev->ih.enabled = false;
	rdev->ih.rptr = 0;
पूर्ण

अटल व्योम si_disable_पूर्णांकerrupt_state(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक i;
	u32 पंचांगp;

	पंचांगp = RREG32(CP_INT_CNTL_RING0) &
		(CNTX_BUSY_INT_ENABLE | CNTX_EMPTY_INT_ENABLE);
	WREG32(CP_INT_CNTL_RING0, पंचांगp);
	WREG32(CP_INT_CNTL_RING1, 0);
	WREG32(CP_INT_CNTL_RING2, 0);
	पंचांगp = RREG32(DMA_CNTL + DMA0_REGISTER_OFFSET) & ~TRAP_ENABLE;
	WREG32(DMA_CNTL + DMA0_REGISTER_OFFSET, पंचांगp);
	पंचांगp = RREG32(DMA_CNTL + DMA1_REGISTER_OFFSET) & ~TRAP_ENABLE;
	WREG32(DMA_CNTL + DMA1_REGISTER_OFFSET, पंचांगp);
	WREG32(GRBM_INT_CNTL, 0);
	WREG32(SRBM_INT_CNTL, 0);
	क्रम (i = 0; i < rdev->num_crtc; i++)
		WREG32(INT_MASK + crtc_offsets[i], 0);
	क्रम (i = 0; i < rdev->num_crtc; i++)
		WREG32(GRPH_INT_CONTROL + crtc_offsets[i], 0);

	अगर (!ASIC_IS_NODCE(rdev)) अणु
		WREG32(DAC_AUTODETECT_INT_CONTROL, 0);

		क्रम (i = 0; i < 6; i++)
			WREG32_AND(DC_HPDx_INT_CONTROL(i),
				   DC_HPDx_INT_POLARITY);
	पूर्ण
पूर्ण

अटल पूर्णांक si_irq_init(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक ret = 0;
	पूर्णांक rb_bufsz;
	u32 पूर्णांकerrupt_cntl, ih_cntl, ih_rb_cntl;

	/* allocate ring */
	ret = r600_ih_ring_alloc(rdev);
	अगर (ret)
		वापस ret;

	/* disable irqs */
	si_disable_पूर्णांकerrupts(rdev);

	/* init rlc */
	ret = si_rlc_resume(rdev);
	अगर (ret) अणु
		r600_ih_ring_fini(rdev);
		वापस ret;
	पूर्ण

	/* setup पूर्णांकerrupt control */
	/* set dummy पढ़ो address to dummy page address */
	WREG32(INTERRUPT_CNTL2, rdev->dummy_page.addr >> 8);
	पूर्णांकerrupt_cntl = RREG32(INTERRUPT_CNTL);
	/* IH_DUMMY_RD_OVERRIDE=0 - dummy पढ़ो disabled with msi, enabled without msi
	 * IH_DUMMY_RD_OVERRIDE=1 - dummy पढ़ो controlled by IH_DUMMY_RD_EN
	 */
	पूर्णांकerrupt_cntl &= ~IH_DUMMY_RD_OVERRIDE;
	/* IH_REQ_NONSNOOP_EN=1 अगर ring is in non-cacheable memory, e.g., vram */
	पूर्णांकerrupt_cntl &= ~IH_REQ_NONSNOOP_EN;
	WREG32(INTERRUPT_CNTL, पूर्णांकerrupt_cntl);

	WREG32(IH_RB_BASE, rdev->ih.gpu_addr >> 8);
	rb_bufsz = order_base_2(rdev->ih.ring_size / 4);

	ih_rb_cntl = (IH_WPTR_OVERFLOW_ENABLE |
		      IH_WPTR_OVERFLOW_CLEAR |
		      (rb_bufsz << 1));

	अगर (rdev->wb.enabled)
		ih_rb_cntl |= IH_WPTR_WRITEBACK_ENABLE;

	/* set the ग_लिखोback address whether it's enabled or not */
	WREG32(IH_RB_WPTR_ADDR_LO, (rdev->wb.gpu_addr + R600_WB_IH_WPTR_OFFSET) & 0xFFFFFFFC);
	WREG32(IH_RB_WPTR_ADDR_HI, upper_32_bits(rdev->wb.gpu_addr + R600_WB_IH_WPTR_OFFSET) & 0xFF);

	WREG32(IH_RB_CNTL, ih_rb_cntl);

	/* set rptr, wptr to 0 */
	WREG32(IH_RB_RPTR, 0);
	WREG32(IH_RB_WPTR, 0);

	/* Default settings क्रम IH_CNTL (disabled at first) */
	ih_cntl = MC_WRREQ_CREDIT(0x10) | MC_WR_CLEAN_CNT(0x10) | MC_VMID(0);
	/* RPTR_REARM only works अगर msi's are enabled */
	अगर (rdev->msi_enabled)
		ih_cntl |= RPTR_REARM;
	WREG32(IH_CNTL, ih_cntl);

	/* क्रमce the active पूर्णांकerrupt state to all disabled */
	si_disable_पूर्णांकerrupt_state(rdev);

	pci_set_master(rdev->pdev);

	/* enable irqs */
	si_enable_पूर्णांकerrupts(rdev);

	वापस ret;
पूर्ण

/* The order we ग_लिखो back each रेजिस्टर here is important */
पूर्णांक si_irq_set(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक i;
	u32 cp_पूर्णांक_cntl;
	u32 cp_पूर्णांक_cntl1 = 0, cp_पूर्णांक_cntl2 = 0;
	u32 grbm_पूर्णांक_cntl = 0;
	u32 dma_cntl, dma_cntl1;
	u32 thermal_पूर्णांक = 0;

	अगर (!rdev->irq.installed) अणु
		WARN(1, "Can't enable IRQ/MSI because no handler is installed\n");
		वापस -EINVAL;
	पूर्ण
	/* करोn't enable anything अगर the ih is disabled */
	अगर (!rdev->ih.enabled) अणु
		si_disable_पूर्णांकerrupts(rdev);
		/* क्रमce the active पूर्णांकerrupt state to all disabled */
		si_disable_पूर्णांकerrupt_state(rdev);
		वापस 0;
	पूर्ण

	cp_पूर्णांक_cntl = RREG32(CP_INT_CNTL_RING0) &
		(CNTX_BUSY_INT_ENABLE | CNTX_EMPTY_INT_ENABLE);

	dma_cntl = RREG32(DMA_CNTL + DMA0_REGISTER_OFFSET) & ~TRAP_ENABLE;
	dma_cntl1 = RREG32(DMA_CNTL + DMA1_REGISTER_OFFSET) & ~TRAP_ENABLE;

	thermal_पूर्णांक = RREG32(CG_THERMAL_INT) &
		~(THERM_INT_MASK_HIGH | THERM_INT_MASK_LOW);

	/* enable CP पूर्णांकerrupts on all rings */
	अगर (atomic_पढ़ो(&rdev->irq.ring_पूर्णांक[RADEON_RING_TYPE_GFX_INDEX])) अणु
		DRM_DEBUG("si_irq_set: sw int gfx\n");
		cp_पूर्णांक_cntl |= TIME_STAMP_INT_ENABLE;
	पूर्ण
	अगर (atomic_पढ़ो(&rdev->irq.ring_पूर्णांक[CAYMAN_RING_TYPE_CP1_INDEX])) अणु
		DRM_DEBUG("si_irq_set: sw int cp1\n");
		cp_पूर्णांक_cntl1 |= TIME_STAMP_INT_ENABLE;
	पूर्ण
	अगर (atomic_पढ़ो(&rdev->irq.ring_पूर्णांक[CAYMAN_RING_TYPE_CP2_INDEX])) अणु
		DRM_DEBUG("si_irq_set: sw int cp2\n");
		cp_पूर्णांक_cntl2 |= TIME_STAMP_INT_ENABLE;
	पूर्ण
	अगर (atomic_पढ़ो(&rdev->irq.ring_पूर्णांक[R600_RING_TYPE_DMA_INDEX])) अणु
		DRM_DEBUG("si_irq_set: sw int dma\n");
		dma_cntl |= TRAP_ENABLE;
	पूर्ण

	अगर (atomic_पढ़ो(&rdev->irq.ring_पूर्णांक[CAYMAN_RING_TYPE_DMA1_INDEX])) अणु
		DRM_DEBUG("si_irq_set: sw int dma1\n");
		dma_cntl1 |= TRAP_ENABLE;
	पूर्ण

	WREG32(CP_INT_CNTL_RING0, cp_पूर्णांक_cntl);
	WREG32(CP_INT_CNTL_RING1, cp_पूर्णांक_cntl1);
	WREG32(CP_INT_CNTL_RING2, cp_पूर्णांक_cntl2);

	WREG32(DMA_CNTL + DMA0_REGISTER_OFFSET, dma_cntl);
	WREG32(DMA_CNTL + DMA1_REGISTER_OFFSET, dma_cntl1);

	WREG32(GRBM_INT_CNTL, grbm_पूर्णांक_cntl);

	अगर (rdev->irq.dpm_thermal) अणु
		DRM_DEBUG("dpm thermal\n");
		thermal_पूर्णांक |= THERM_INT_MASK_HIGH | THERM_INT_MASK_LOW;
	पूर्ण

	क्रम (i = 0; i < rdev->num_crtc; i++) अणु
		radeon_irq_kms_set_irq_n_enabled(
		    rdev, INT_MASK + crtc_offsets[i], VBLANK_INT_MASK,
		    rdev->irq.crtc_vblank_पूर्णांक[i] ||
		    atomic_पढ़ो(&rdev->irq.pflip[i]), "vblank", i);
	पूर्ण

	क्रम (i = 0; i < rdev->num_crtc; i++)
		WREG32(GRPH_INT_CONTROL + crtc_offsets[i], GRPH_PFLIP_INT_MASK);

	अगर (!ASIC_IS_NODCE(rdev)) अणु
		क्रम (i = 0; i < 6; i++) अणु
			radeon_irq_kms_set_irq_n_enabled(
			    rdev, DC_HPDx_INT_CONTROL(i),
			    DC_HPDx_INT_EN | DC_HPDx_RX_INT_EN,
			    rdev->irq.hpd[i], "HPD", i);
		पूर्ण
	पूर्ण

	WREG32(CG_THERMAL_INT, thermal_पूर्णांक);

	/* posting पढ़ो */
	RREG32(SRBM_STATUS);

	वापस 0;
पूर्ण

/* The order we ग_लिखो back each रेजिस्टर here is important */
अटल अंतरभूत व्योम si_irq_ack(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक i, j;
	u32 *disp_पूर्णांक = rdev->irq.stat_regs.evergreen.disp_पूर्णांक;
	u32 *grph_पूर्णांक = rdev->irq.stat_regs.evergreen.grph_पूर्णांक;

	अगर (ASIC_IS_NODCE(rdev))
		वापस;

	क्रम (i = 0; i < 6; i++) अणु
		disp_पूर्णांक[i] = RREG32(si_disp_पूर्णांक_status[i]);
		अगर (i < rdev->num_crtc)
			grph_पूर्णांक[i] = RREG32(GRPH_INT_STATUS + crtc_offsets[i]);
	पूर्ण

	/* We ग_लिखो back each पूर्णांकerrupt रेजिस्टर in pairs of two */
	क्रम (i = 0; i < rdev->num_crtc; i += 2) अणु
		क्रम (j = i; j < (i + 2); j++) अणु
			अगर (grph_पूर्णांक[j] & GRPH_PFLIP_INT_OCCURRED)
				WREG32(GRPH_INT_STATUS + crtc_offsets[j],
				       GRPH_PFLIP_INT_CLEAR);
		पूर्ण

		क्रम (j = i; j < (i + 2); j++) अणु
			अगर (disp_पूर्णांक[j] & LB_D1_VBLANK_INTERRUPT)
				WREG32(VBLANK_STATUS + crtc_offsets[j],
				       VBLANK_ACK);
			अगर (disp_पूर्णांक[j] & LB_D1_VLINE_INTERRUPT)
				WREG32(VLINE_STATUS + crtc_offsets[j],
				       VLINE_ACK);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < 6; i++) अणु
		अगर (disp_पूर्णांक[i] & DC_HPD1_INTERRUPT)
			WREG32_OR(DC_HPDx_INT_CONTROL(i), DC_HPDx_INT_ACK);
	पूर्ण

	क्रम (i = 0; i < 6; i++) अणु
		अगर (disp_पूर्णांक[i] & DC_HPD1_RX_INTERRUPT)
			WREG32_OR(DC_HPDx_INT_CONTROL(i), DC_HPDx_RX_INT_ACK);
	पूर्ण
पूर्ण

अटल व्योम si_irq_disable(काष्ठा radeon_device *rdev)
अणु
	si_disable_पूर्णांकerrupts(rdev);
	/* Wait and acknowledge irq */
	mdelay(1);
	si_irq_ack(rdev);
	si_disable_पूर्णांकerrupt_state(rdev);
पूर्ण

अटल व्योम si_irq_suspend(काष्ठा radeon_device *rdev)
अणु
	si_irq_disable(rdev);
	si_rlc_stop(rdev);
पूर्ण

अटल व्योम si_irq_fini(काष्ठा radeon_device *rdev)
अणु
	si_irq_suspend(rdev);
	r600_ih_ring_fini(rdev);
पूर्ण

अटल अंतरभूत u32 si_get_ih_wptr(काष्ठा radeon_device *rdev)
अणु
	u32 wptr, पंचांगp;

	अगर (rdev->wb.enabled)
		wptr = le32_to_cpu(rdev->wb.wb[R600_WB_IH_WPTR_OFFSET/4]);
	अन्यथा
		wptr = RREG32(IH_RB_WPTR);

	अगर (wptr & RB_OVERFLOW) अणु
		wptr &= ~RB_OVERFLOW;
		/* When a ring buffer overflow happen start parsing पूर्णांकerrupt
		 * from the last not overwritten vector (wptr + 16). Hopefully
		 * this should allow us to catchup.
		 */
		dev_warn(rdev->dev, "IH ring buffer overflow (0x%08X, 0x%08X, 0x%08X)\n",
			 wptr, rdev->ih.rptr, (wptr + 16) & rdev->ih.ptr_mask);
		rdev->ih.rptr = (wptr + 16) & rdev->ih.ptr_mask;
		पंचांगp = RREG32(IH_RB_CNTL);
		पंचांगp |= IH_WPTR_OVERFLOW_CLEAR;
		WREG32(IH_RB_CNTL, पंचांगp);
	पूर्ण
	वापस (wptr & rdev->ih.ptr_mask);
पूर्ण

/*        SI IV Ring
 * Each IV ring entry is 128 bits:
 * [7:0]    - पूर्णांकerrupt source id
 * [31:8]   - reserved
 * [59:32]  - पूर्णांकerrupt source data
 * [63:60]  - reserved
 * [71:64]  - RINGID
 * [79:72]  - VMID
 * [127:80] - reserved
 */
पूर्णांक si_irq_process(काष्ठा radeon_device *rdev)
अणु
	u32 *disp_पूर्णांक = rdev->irq.stat_regs.evergreen.disp_पूर्णांक;
	u32 crtc_idx, hpd_idx;
	u32 mask;
	u32 wptr;
	u32 rptr;
	u32 src_id, src_data, ring_id;
	u32 ring_index;
	bool queue_hotplug = false;
	bool queue_dp = false;
	bool queue_thermal = false;
	u32 status, addr;
	स्थिर अक्षर *event_name;

	अगर (!rdev->ih.enabled || rdev->shutकरोwn)
		वापस IRQ_NONE;

	wptr = si_get_ih_wptr(rdev);

restart_ih:
	/* is somebody अन्यथा alपढ़ोy processing irqs? */
	अगर (atomic_xchg(&rdev->ih.lock, 1))
		वापस IRQ_NONE;

	rptr = rdev->ih.rptr;
	DRM_DEBUG("si_irq_process start: rptr %d, wptr %d\n", rptr, wptr);

	/* Order पढ़ोing of wptr vs. पढ़ोing of IH ring data */
	rmb();

	/* display पूर्णांकerrupts */
	si_irq_ack(rdev);

	जबतक (rptr != wptr) अणु
		/* wptr/rptr are in bytes! */
		ring_index = rptr / 4;
		src_id =  le32_to_cpu(rdev->ih.ring[ring_index]) & 0xff;
		src_data = le32_to_cpu(rdev->ih.ring[ring_index + 1]) & 0xfffffff;
		ring_id = le32_to_cpu(rdev->ih.ring[ring_index + 2]) & 0xff;

		चयन (src_id) अणु
		हाल 1: /* D1 vblank/vline */
		हाल 2: /* D2 vblank/vline */
		हाल 3: /* D3 vblank/vline */
		हाल 4: /* D4 vblank/vline */
		हाल 5: /* D5 vblank/vline */
		हाल 6: /* D6 vblank/vline */
			crtc_idx = src_id - 1;

			अगर (src_data == 0) अणु /* vblank */
				mask = LB_D1_VBLANK_INTERRUPT;
				event_name = "vblank";

				अगर (rdev->irq.crtc_vblank_पूर्णांक[crtc_idx]) अणु
					drm_handle_vblank(rdev->ddev, crtc_idx);
					rdev->pm.vblank_sync = true;
					wake_up(&rdev->irq.vblank_queue);
				पूर्ण
				अगर (atomic_पढ़ो(&rdev->irq.pflip[crtc_idx])) अणु
					radeon_crtc_handle_vblank(rdev,
								  crtc_idx);
				पूर्ण

			पूर्ण अन्यथा अगर (src_data == 1) अणु /* vline */
				mask = LB_D1_VLINE_INTERRUPT;
				event_name = "vline";
			पूर्ण अन्यथा अणु
				DRM_DEBUG("Unhandled interrupt: %d %d\n",
					  src_id, src_data);
				अवरोध;
			पूर्ण

			अगर (!(disp_पूर्णांक[crtc_idx] & mask)) अणु
				DRM_DEBUG("IH: D%d %s - IH event w/o asserted irq bit?\n",
					  crtc_idx + 1, event_name);
			पूर्ण

			disp_पूर्णांक[crtc_idx] &= ~mask;
			DRM_DEBUG("IH: D%d %s\n", crtc_idx + 1, event_name);

			अवरोध;
		हाल 8: /* D1 page flip */
		हाल 10: /* D2 page flip */
		हाल 12: /* D3 page flip */
		हाल 14: /* D4 page flip */
		हाल 16: /* D5 page flip */
		हाल 18: /* D6 page flip */
			DRM_DEBUG("IH: D%d flip\n", ((src_id - 8) >> 1) + 1);
			अगर (radeon_use_pflipirq > 0)
				radeon_crtc_handle_flip(rdev, (src_id - 8) >> 1);
			अवरोध;
		हाल 42: /* HPD hotplug */
			अगर (src_data <= 5) अणु
				hpd_idx = src_data;
				mask = DC_HPD1_INTERRUPT;
				queue_hotplug = true;
				event_name = "HPD";

			पूर्ण अन्यथा अगर (src_data <= 11) अणु
				hpd_idx = src_data - 6;
				mask = DC_HPD1_RX_INTERRUPT;
				queue_dp = true;
				event_name = "HPD_RX";

			पूर्ण अन्यथा अणु
				DRM_DEBUG("Unhandled interrupt: %d %d\n",
					  src_id, src_data);
				अवरोध;
			पूर्ण

			अगर (!(disp_पूर्णांक[hpd_idx] & mask))
				DRM_DEBUG("IH: IH event w/o asserted irq bit?\n");

			disp_पूर्णांक[hpd_idx] &= ~mask;
			DRM_DEBUG("IH: %s%d\n", event_name, hpd_idx + 1);
			अवरोध;
		हाल 96:
			DRM_ERROR("SRBM_READ_ERROR: 0x%x\n", RREG32(SRBM_READ_ERROR));
			WREG32(SRBM_INT_ACK, 0x1);
			अवरोध;
		हाल 124: /* UVD */
			DRM_DEBUG("IH: UVD int: 0x%08x\n", src_data);
			radeon_fence_process(rdev, R600_RING_TYPE_UVD_INDEX);
			अवरोध;
		हाल 146:
		हाल 147:
			addr = RREG32(VM_CONTEXT1_PROTECTION_FAULT_ADDR);
			status = RREG32(VM_CONTEXT1_PROTECTION_FAULT_STATUS);
			/* reset addr and status */
			WREG32_P(VM_CONTEXT1_CNTL2, 1, ~1);
			अगर (addr == 0x0 && status == 0x0)
				अवरोध;
			dev_err(rdev->dev, "GPU fault detected: %d 0x%08x\n", src_id, src_data);
			dev_err(rdev->dev, "  VM_CONTEXT1_PROTECTION_FAULT_ADDR   0x%08X\n",
				addr);
			dev_err(rdev->dev, "  VM_CONTEXT1_PROTECTION_FAULT_STATUS 0x%08X\n",
				status);
			si_vm_decode_fault(rdev, status, addr);
			अवरोध;
		हाल 176: /* RINGID0 CP_INT */
			radeon_fence_process(rdev, RADEON_RING_TYPE_GFX_INDEX);
			अवरोध;
		हाल 177: /* RINGID1 CP_INT */
			radeon_fence_process(rdev, CAYMAN_RING_TYPE_CP1_INDEX);
			अवरोध;
		हाल 178: /* RINGID2 CP_INT */
			radeon_fence_process(rdev, CAYMAN_RING_TYPE_CP2_INDEX);
			अवरोध;
		हाल 181: /* CP EOP event */
			DRM_DEBUG("IH: CP EOP\n");
			चयन (ring_id) अणु
			हाल 0:
				radeon_fence_process(rdev, RADEON_RING_TYPE_GFX_INDEX);
				अवरोध;
			हाल 1:
				radeon_fence_process(rdev, CAYMAN_RING_TYPE_CP1_INDEX);
				अवरोध;
			हाल 2:
				radeon_fence_process(rdev, CAYMAN_RING_TYPE_CP2_INDEX);
				अवरोध;
			पूर्ण
			अवरोध;
		हाल 224: /* DMA trap event */
			DRM_DEBUG("IH: DMA trap\n");
			radeon_fence_process(rdev, R600_RING_TYPE_DMA_INDEX);
			अवरोध;
		हाल 230: /* thermal low to high */
			DRM_DEBUG("IH: thermal low to high\n");
			rdev->pm.dpm.thermal.high_to_low = false;
			queue_thermal = true;
			अवरोध;
		हाल 231: /* thermal high to low */
			DRM_DEBUG("IH: thermal high to low\n");
			rdev->pm.dpm.thermal.high_to_low = true;
			queue_thermal = true;
			अवरोध;
		हाल 233: /* GUI IDLE */
			DRM_DEBUG("IH: GUI idle\n");
			अवरोध;
		हाल 244: /* DMA trap event */
			DRM_DEBUG("IH: DMA1 trap\n");
			radeon_fence_process(rdev, CAYMAN_RING_TYPE_DMA1_INDEX);
			अवरोध;
		शेष:
			DRM_DEBUG("Unhandled interrupt: %d %d\n", src_id, src_data);
			अवरोध;
		पूर्ण

		/* wptr/rptr are in bytes! */
		rptr += 16;
		rptr &= rdev->ih.ptr_mask;
		WREG32(IH_RB_RPTR, rptr);
	पूर्ण
	अगर (queue_dp)
		schedule_work(&rdev->dp_work);
	अगर (queue_hotplug)
		schedule_delayed_work(&rdev->hotplug_work, 0);
	अगर (queue_thermal && rdev->pm.dpm_enabled)
		schedule_work(&rdev->pm.dpm.thermal.work);
	rdev->ih.rptr = rptr;
	atomic_set(&rdev->ih.lock, 0);

	/* make sure wptr hasn't changed जबतक processing */
	wptr = si_get_ih_wptr(rdev);
	अगर (wptr != rptr)
		जाओ restart_ih;

	वापस IRQ_HANDLED;
पूर्ण

/*
 * startup/shutकरोwn callbacks
 */
अटल व्योम si_uvd_init(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	अगर (!rdev->has_uvd)
		वापस;

	r = radeon_uvd_init(rdev);
	अगर (r) अणु
		dev_err(rdev->dev, "failed UVD (%d) init.\n", r);
		/*
		 * At this poपूर्णांक rdev->uvd.vcpu_bo is शून्य which trickles करोwn
		 * to early fails uvd_v2_2_resume() and thus nothing happens
		 * there. So it is poपूर्णांकless to try to go through that code
		 * hence why we disable uvd here.
		 */
		rdev->has_uvd = false;
		वापस;
	पूर्ण
	rdev->ring[R600_RING_TYPE_UVD_INDEX].ring_obj = शून्य;
	r600_ring_init(rdev, &rdev->ring[R600_RING_TYPE_UVD_INDEX], 4096);
पूर्ण

अटल व्योम si_uvd_start(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	अगर (!rdev->has_uvd)
		वापस;

	r = uvd_v2_2_resume(rdev);
	अगर (r) अणु
		dev_err(rdev->dev, "failed UVD resume (%d).\n", r);
		जाओ error;
	पूर्ण
	r = radeon_fence_driver_start_ring(rdev, R600_RING_TYPE_UVD_INDEX);
	अगर (r) अणु
		dev_err(rdev->dev, "failed initializing UVD fences (%d).\n", r);
		जाओ error;
	पूर्ण
	वापस;

error:
	rdev->ring[R600_RING_TYPE_UVD_INDEX].ring_size = 0;
पूर्ण

अटल व्योम si_uvd_resume(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_ring *ring;
	पूर्णांक r;

	अगर (!rdev->has_uvd || !rdev->ring[R600_RING_TYPE_UVD_INDEX].ring_size)
		वापस;

	ring = &rdev->ring[R600_RING_TYPE_UVD_INDEX];
	r = radeon_ring_init(rdev, ring, ring->ring_size, 0, PACKET0(UVD_NO_OP, 0));
	अगर (r) अणु
		dev_err(rdev->dev, "failed initializing UVD ring (%d).\n", r);
		वापस;
	पूर्ण
	r = uvd_v1_0_init(rdev);
	अगर (r) अणु
		dev_err(rdev->dev, "failed initializing UVD (%d).\n", r);
		वापस;
	पूर्ण
पूर्ण

अटल व्योम si_vce_init(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	अगर (!rdev->has_vce)
		वापस;

	r = radeon_vce_init(rdev);
	अगर (r) अणु
		dev_err(rdev->dev, "failed VCE (%d) init.\n", r);
		/*
		 * At this poपूर्णांक rdev->vce.vcpu_bo is शून्य which trickles करोwn
		 * to early fails si_vce_start() and thus nothing happens
		 * there. So it is poपूर्णांकless to try to go through that code
		 * hence why we disable vce here.
		 */
		rdev->has_vce = false;
		वापस;
	पूर्ण
	rdev->ring[TN_RING_TYPE_VCE1_INDEX].ring_obj = शून्य;
	r600_ring_init(rdev, &rdev->ring[TN_RING_TYPE_VCE1_INDEX], 4096);
	rdev->ring[TN_RING_TYPE_VCE2_INDEX].ring_obj = शून्य;
	r600_ring_init(rdev, &rdev->ring[TN_RING_TYPE_VCE2_INDEX], 4096);
पूर्ण

अटल व्योम si_vce_start(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	अगर (!rdev->has_vce)
		वापस;

	r = radeon_vce_resume(rdev);
	अगर (r) अणु
		dev_err(rdev->dev, "failed VCE resume (%d).\n", r);
		जाओ error;
	पूर्ण
	r = vce_v1_0_resume(rdev);
	अगर (r) अणु
		dev_err(rdev->dev, "failed VCE resume (%d).\n", r);
		जाओ error;
	पूर्ण
	r = radeon_fence_driver_start_ring(rdev, TN_RING_TYPE_VCE1_INDEX);
	अगर (r) अणु
		dev_err(rdev->dev, "failed initializing VCE1 fences (%d).\n", r);
		जाओ error;
	पूर्ण
	r = radeon_fence_driver_start_ring(rdev, TN_RING_TYPE_VCE2_INDEX);
	अगर (r) अणु
		dev_err(rdev->dev, "failed initializing VCE2 fences (%d).\n", r);
		जाओ error;
	पूर्ण
	वापस;

error:
	rdev->ring[TN_RING_TYPE_VCE1_INDEX].ring_size = 0;
	rdev->ring[TN_RING_TYPE_VCE2_INDEX].ring_size = 0;
पूर्ण

अटल व्योम si_vce_resume(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_ring *ring;
	पूर्णांक r;

	अगर (!rdev->has_vce || !rdev->ring[TN_RING_TYPE_VCE1_INDEX].ring_size)
		वापस;

	ring = &rdev->ring[TN_RING_TYPE_VCE1_INDEX];
	r = radeon_ring_init(rdev, ring, ring->ring_size, 0, VCE_CMD_NO_OP);
	अगर (r) अणु
		dev_err(rdev->dev, "failed initializing VCE1 ring (%d).\n", r);
		वापस;
	पूर्ण
	ring = &rdev->ring[TN_RING_TYPE_VCE2_INDEX];
	r = radeon_ring_init(rdev, ring, ring->ring_size, 0, VCE_CMD_NO_OP);
	अगर (r) अणु
		dev_err(rdev->dev, "failed initializing VCE1 ring (%d).\n", r);
		वापस;
	पूर्ण
	r = vce_v1_0_init(rdev);
	अगर (r) अणु
		dev_err(rdev->dev, "failed initializing VCE (%d).\n", r);
		वापस;
	पूर्ण
पूर्ण

अटल पूर्णांक si_startup(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_ring *ring;
	पूर्णांक r;

	/* enable pcie gen2/3 link */
	si_pcie_gen3_enable(rdev);
	/* enable aspm */
	si_program_aspm(rdev);

	/* scratch needs to be initialized beक्रमe MC */
	r = r600_vram_scratch_init(rdev);
	अगर (r)
		वापस r;

	si_mc_program(rdev);

	अगर (!rdev->pm.dpm_enabled) अणु
		r = si_mc_load_microcode(rdev);
		अगर (r) अणु
			DRM_ERROR("Failed to load MC firmware!\n");
			वापस r;
		पूर्ण
	पूर्ण

	r = si_pcie_gart_enable(rdev);
	अगर (r)
		वापस r;
	si_gpu_init(rdev);

	/* allocate rlc buffers */
	अगर (rdev->family == CHIP_VERDE) अणु
		rdev->rlc.reg_list = verde_rlc_save_restore_रेजिस्टर_list;
		rdev->rlc.reg_list_size =
			(u32)ARRAY_SIZE(verde_rlc_save_restore_रेजिस्टर_list);
	पूर्ण
	rdev->rlc.cs_data = si_cs_data;
	r = sumo_rlc_init(rdev);
	अगर (r) अणु
		DRM_ERROR("Failed to init rlc BOs!\n");
		वापस r;
	पूर्ण

	/* allocate wb buffer */
	r = radeon_wb_init(rdev);
	अगर (r)
		वापस r;

	r = radeon_fence_driver_start_ring(rdev, RADEON_RING_TYPE_GFX_INDEX);
	अगर (r) अणु
		dev_err(rdev->dev, "failed initializing CP fences (%d).\n", r);
		वापस r;
	पूर्ण

	r = radeon_fence_driver_start_ring(rdev, CAYMAN_RING_TYPE_CP1_INDEX);
	अगर (r) अणु
		dev_err(rdev->dev, "failed initializing CP fences (%d).\n", r);
		वापस r;
	पूर्ण

	r = radeon_fence_driver_start_ring(rdev, CAYMAN_RING_TYPE_CP2_INDEX);
	अगर (r) अणु
		dev_err(rdev->dev, "failed initializing CP fences (%d).\n", r);
		वापस r;
	पूर्ण

	r = radeon_fence_driver_start_ring(rdev, R600_RING_TYPE_DMA_INDEX);
	अगर (r) अणु
		dev_err(rdev->dev, "failed initializing DMA fences (%d).\n", r);
		वापस r;
	पूर्ण

	r = radeon_fence_driver_start_ring(rdev, CAYMAN_RING_TYPE_DMA1_INDEX);
	अगर (r) अणु
		dev_err(rdev->dev, "failed initializing DMA fences (%d).\n", r);
		वापस r;
	पूर्ण

	si_uvd_start(rdev);
	si_vce_start(rdev);

	/* Enable IRQ */
	अगर (!rdev->irq.installed) अणु
		r = radeon_irq_kms_init(rdev);
		अगर (r)
			वापस r;
	पूर्ण

	r = si_irq_init(rdev);
	अगर (r) अणु
		DRM_ERROR("radeon: IH init failed (%d).\n", r);
		radeon_irq_kms_fini(rdev);
		वापस r;
	पूर्ण
	si_irq_set(rdev);

	ring = &rdev->ring[RADEON_RING_TYPE_GFX_INDEX];
	r = radeon_ring_init(rdev, ring, ring->ring_size, RADEON_WB_CP_RPTR_OFFSET,
			     RADEON_CP_PACKET2);
	अगर (r)
		वापस r;

	ring = &rdev->ring[CAYMAN_RING_TYPE_CP1_INDEX];
	r = radeon_ring_init(rdev, ring, ring->ring_size, RADEON_WB_CP1_RPTR_OFFSET,
			     RADEON_CP_PACKET2);
	अगर (r)
		वापस r;

	ring = &rdev->ring[CAYMAN_RING_TYPE_CP2_INDEX];
	r = radeon_ring_init(rdev, ring, ring->ring_size, RADEON_WB_CP2_RPTR_OFFSET,
			     RADEON_CP_PACKET2);
	अगर (r)
		वापस r;

	ring = &rdev->ring[R600_RING_TYPE_DMA_INDEX];
	r = radeon_ring_init(rdev, ring, ring->ring_size, R600_WB_DMA_RPTR_OFFSET,
			     DMA_PACKET(DMA_PACKET_NOP, 0, 0, 0, 0));
	अगर (r)
		वापस r;

	ring = &rdev->ring[CAYMAN_RING_TYPE_DMA1_INDEX];
	r = radeon_ring_init(rdev, ring, ring->ring_size, CAYMAN_WB_DMA1_RPTR_OFFSET,
			     DMA_PACKET(DMA_PACKET_NOP, 0, 0, 0, 0));
	अगर (r)
		वापस r;

	r = si_cp_load_microcode(rdev);
	अगर (r)
		वापस r;
	r = si_cp_resume(rdev);
	अगर (r)
		वापस r;

	r = cayman_dma_resume(rdev);
	अगर (r)
		वापस r;

	si_uvd_resume(rdev);
	si_vce_resume(rdev);

	r = radeon_ib_pool_init(rdev);
	अगर (r) अणु
		dev_err(rdev->dev, "IB initialization failed (%d).\n", r);
		वापस r;
	पूर्ण

	r = radeon_vm_manager_init(rdev);
	अगर (r) अणु
		dev_err(rdev->dev, "vm manager initialization failed (%d).\n", r);
		वापस r;
	पूर्ण

	r = radeon_audio_init(rdev);
	अगर (r)
		वापस r;

	वापस 0;
पूर्ण

पूर्णांक si_resume(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	/* Do not reset GPU beक्रमe posting, on rv770 hw unlike on r500 hw,
	 * posting will perक्रमm necessary task to bring back GPU पूर्णांकo good
	 * shape.
	 */
	/* post card */
	atom_asic_init(rdev->mode_info.atom_context);

	/* init golden रेजिस्टरs */
	si_init_golden_रेजिस्टरs(rdev);

	अगर (rdev->pm.pm_method == PM_METHOD_DPM)
		radeon_pm_resume(rdev);

	rdev->accel_working = true;
	r = si_startup(rdev);
	अगर (r) अणु
		DRM_ERROR("si startup failed on resume\n");
		rdev->accel_working = false;
		वापस r;
	पूर्ण

	वापस r;

पूर्ण

पूर्णांक si_suspend(काष्ठा radeon_device *rdev)
अणु
	radeon_pm_suspend(rdev);
	radeon_audio_fini(rdev);
	radeon_vm_manager_fini(rdev);
	si_cp_enable(rdev, false);
	cayman_dma_stop(rdev);
	अगर (rdev->has_uvd) अणु
		uvd_v1_0_fini(rdev);
		radeon_uvd_suspend(rdev);
	पूर्ण
	अगर (rdev->has_vce)
		radeon_vce_suspend(rdev);
	si_fini_pg(rdev);
	si_fini_cg(rdev);
	si_irq_suspend(rdev);
	radeon_wb_disable(rdev);
	si_pcie_gart_disable(rdev);
	वापस 0;
पूर्ण

/* Plan is to move initialization in that function and use
 * helper function so that radeon_device_init pretty much
 * करो nothing more than calling asic specअगरic function. This
 * should also allow to हटाओ a bunch of callback function
 * like vram_info.
 */
पूर्णांक si_init(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_ring *ring = &rdev->ring[RADEON_RING_TYPE_GFX_INDEX];
	पूर्णांक r;

	/* Read BIOS */
	अगर (!radeon_get_bios(rdev)) अणु
		अगर (ASIC_IS_AVIVO(rdev))
			वापस -EINVAL;
	पूर्ण
	/* Must be an ATOMBIOS */
	अगर (!rdev->is_atom_bios) अणु
		dev_err(rdev->dev, "Expecting atombios for cayman GPU\n");
		वापस -EINVAL;
	पूर्ण
	r = radeon_atombios_init(rdev);
	अगर (r)
		वापस r;

	/* Post card अगर necessary */
	अगर (!radeon_card_posted(rdev)) अणु
		अगर (!rdev->bios) अणु
			dev_err(rdev->dev, "Card not posted and no BIOS - ignoring\n");
			वापस -EINVAL;
		पूर्ण
		DRM_INFO("GPU not posted. posting now...\n");
		atom_asic_init(rdev->mode_info.atom_context);
	पूर्ण
	/* init golden रेजिस्टरs */
	si_init_golden_रेजिस्टरs(rdev);
	/* Initialize scratch रेजिस्टरs */
	si_scratch_init(rdev);
	/* Initialize surface रेजिस्टरs */
	radeon_surface_init(rdev);
	/* Initialize घड़ीs */
	radeon_get_घड़ी_info(rdev->ddev);

	/* Fence driver */
	r = radeon_fence_driver_init(rdev);
	अगर (r)
		वापस r;

	/* initialize memory controller */
	r = si_mc_init(rdev);
	अगर (r)
		वापस r;
	/* Memory manager */
	r = radeon_bo_init(rdev);
	अगर (r)
		वापस r;

	अगर (!rdev->me_fw || !rdev->pfp_fw || !rdev->ce_fw ||
	    !rdev->rlc_fw || !rdev->mc_fw) अणु
		r = si_init_microcode(rdev);
		अगर (r) अणु
			DRM_ERROR("Failed to load firmware!\n");
			वापस r;
		पूर्ण
	पूर्ण

	/* Initialize घातer management */
	radeon_pm_init(rdev);

	ring = &rdev->ring[RADEON_RING_TYPE_GFX_INDEX];
	ring->ring_obj = शून्य;
	r600_ring_init(rdev, ring, 1024 * 1024);

	ring = &rdev->ring[CAYMAN_RING_TYPE_CP1_INDEX];
	ring->ring_obj = शून्य;
	r600_ring_init(rdev, ring, 1024 * 1024);

	ring = &rdev->ring[CAYMAN_RING_TYPE_CP2_INDEX];
	ring->ring_obj = शून्य;
	r600_ring_init(rdev, ring, 1024 * 1024);

	ring = &rdev->ring[R600_RING_TYPE_DMA_INDEX];
	ring->ring_obj = शून्य;
	r600_ring_init(rdev, ring, 64 * 1024);

	ring = &rdev->ring[CAYMAN_RING_TYPE_DMA1_INDEX];
	ring->ring_obj = शून्य;
	r600_ring_init(rdev, ring, 64 * 1024);

	si_uvd_init(rdev);
	si_vce_init(rdev);

	rdev->ih.ring_obj = शून्य;
	r600_ih_ring_init(rdev, 64 * 1024);

	r = r600_pcie_gart_init(rdev);
	अगर (r)
		वापस r;

	rdev->accel_working = true;
	r = si_startup(rdev);
	अगर (r) अणु
		dev_err(rdev->dev, "disabling GPU acceleration\n");
		si_cp_fini(rdev);
		cayman_dma_fini(rdev);
		si_irq_fini(rdev);
		sumo_rlc_fini(rdev);
		radeon_wb_fini(rdev);
		radeon_ib_pool_fini(rdev);
		radeon_vm_manager_fini(rdev);
		radeon_irq_kms_fini(rdev);
		si_pcie_gart_fini(rdev);
		rdev->accel_working = false;
	पूर्ण

	/* Don't start up अगर the MC ucode is missing.
	 * The शेष घड़ीs and voltages beक्रमe the MC ucode
	 * is loaded are not suffient क्रम advanced operations.
	 */
	अगर (!rdev->mc_fw) अणु
		DRM_ERROR("radeon: MC ucode required for NI+.\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

व्योम si_fini(काष्ठा radeon_device *rdev)
अणु
	radeon_pm_fini(rdev);
	si_cp_fini(rdev);
	cayman_dma_fini(rdev);
	si_fini_pg(rdev);
	si_fini_cg(rdev);
	si_irq_fini(rdev);
	sumo_rlc_fini(rdev);
	radeon_wb_fini(rdev);
	radeon_vm_manager_fini(rdev);
	radeon_ib_pool_fini(rdev);
	radeon_irq_kms_fini(rdev);
	अगर (rdev->has_uvd) अणु
		uvd_v1_0_fini(rdev);
		radeon_uvd_fini(rdev);
	पूर्ण
	अगर (rdev->has_vce)
		radeon_vce_fini(rdev);
	si_pcie_gart_fini(rdev);
	r600_vram_scratch_fini(rdev);
	radeon_gem_fini(rdev);
	radeon_fence_driver_fini(rdev);
	radeon_bo_fini(rdev);
	radeon_atombios_fini(rdev);
	kमुक्त(rdev->bios);
	rdev->bios = शून्य;
पूर्ण

/**
 * si_get_gpu_घड़ी_counter - वापस GPU घड़ी counter snapshot
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Fetches a GPU घड़ी counter snapshot (SI).
 * Returns the 64 bit घड़ी counter snapshot.
 */
uपूर्णांक64_t si_get_gpu_घड़ी_counter(काष्ठा radeon_device *rdev)
अणु
	uपूर्णांक64_t घड़ी;

	mutex_lock(&rdev->gpu_घड़ी_mutex);
	WREG32(RLC_CAPTURE_GPU_CLOCK_COUNT, 1);
	घड़ी = (uपूर्णांक64_t)RREG32(RLC_GPU_CLOCK_COUNT_LSB) |
		((uपूर्णांक64_t)RREG32(RLC_GPU_CLOCK_COUNT_MSB) << 32ULL);
	mutex_unlock(&rdev->gpu_घड़ी_mutex);
	वापस घड़ी;
पूर्ण

पूर्णांक si_set_uvd_घड़ीs(काष्ठा radeon_device *rdev, u32 vclk, u32 dclk)
अणु
	अचिन्हित fb_भाग = 0, vclk_भाग = 0, dclk_भाग = 0;
	पूर्णांक r;

	/* bypass vclk and dclk with bclk */
	WREG32_P(CG_UPLL_FUNC_CNTL_2,
		VCLK_SRC_SEL(1) | DCLK_SRC_SEL(1),
		~(VCLK_SRC_SEL_MASK | DCLK_SRC_SEL_MASK));

	/* put PLL in bypass mode */
	WREG32_P(CG_UPLL_FUNC_CNTL, UPLL_BYPASS_EN_MASK, ~UPLL_BYPASS_EN_MASK);

	अगर (!vclk || !dclk) अणु
		/* keep the Bypass mode */
		वापस 0;
	पूर्ण

	r = radeon_uvd_calc_upll_भागiders(rdev, vclk, dclk, 125000, 250000,
					  16384, 0x03FFFFFF, 0, 128, 5,
					  &fb_भाग, &vclk_भाग, &dclk_भाग);
	अगर (r)
		वापस r;

	/* set RESET_ANTI_MUX to 0 */
	WREG32_P(CG_UPLL_FUNC_CNTL_5, 0, ~RESET_ANTI_MUX_MASK);

	/* set VCO_MODE to 1 */
	WREG32_P(CG_UPLL_FUNC_CNTL, UPLL_VCO_MODE_MASK, ~UPLL_VCO_MODE_MASK);

	/* disable sleep mode */
	WREG32_P(CG_UPLL_FUNC_CNTL, 0, ~UPLL_SLEEP_MASK);

	/* deनिश्चित UPLL_RESET */
	WREG32_P(CG_UPLL_FUNC_CNTL, 0, ~UPLL_RESET_MASK);

	mdelay(1);

	r = radeon_uvd_send_upll_ctlreq(rdev, CG_UPLL_FUNC_CNTL);
	अगर (r)
		वापस r;

	/* निश्चित UPLL_RESET again */
	WREG32_P(CG_UPLL_FUNC_CNTL, UPLL_RESET_MASK, ~UPLL_RESET_MASK);

	/* disable spपढ़ो spectrum. */
	WREG32_P(CG_UPLL_SPREAD_SPECTRUM, 0, ~SSEN_MASK);

	/* set feedback भागider */
	WREG32_P(CG_UPLL_FUNC_CNTL_3, UPLL_FB_DIV(fb_भाग), ~UPLL_FB_DIV_MASK);

	/* set ref भागider to 0 */
	WREG32_P(CG_UPLL_FUNC_CNTL, 0, ~UPLL_REF_DIV_MASK);

	अगर (fb_भाग < 307200)
		WREG32_P(CG_UPLL_FUNC_CNTL_4, 0, ~UPLL_SPARE_ISPARE9);
	अन्यथा
		WREG32_P(CG_UPLL_FUNC_CNTL_4, UPLL_SPARE_ISPARE9, ~UPLL_SPARE_ISPARE9);

	/* set PDIV_A and PDIV_B */
	WREG32_P(CG_UPLL_FUNC_CNTL_2,
		UPLL_PDIV_A(vclk_भाग) | UPLL_PDIV_B(dclk_भाग),
		~(UPLL_PDIV_A_MASK | UPLL_PDIV_B_MASK));

	/* give the PLL some समय to settle */
	mdelay(15);

	/* deनिश्चित PLL_RESET */
	WREG32_P(CG_UPLL_FUNC_CNTL, 0, ~UPLL_RESET_MASK);

	mdelay(15);

	/* चयन from bypass mode to normal mode */
	WREG32_P(CG_UPLL_FUNC_CNTL, 0, ~UPLL_BYPASS_EN_MASK);

	r = radeon_uvd_send_upll_ctlreq(rdev, CG_UPLL_FUNC_CNTL);
	अगर (r)
		वापस r;

	/* चयन VCLK and DCLK selection */
	WREG32_P(CG_UPLL_FUNC_CNTL_2,
		VCLK_SRC_SEL(2) | DCLK_SRC_SEL(2),
		~(VCLK_SRC_SEL_MASK | DCLK_SRC_SEL_MASK));

	mdelay(100);

	वापस 0;
पूर्ण

अटल व्योम si_pcie_gen3_enable(काष्ठा radeon_device *rdev)
अणु
	काष्ठा pci_dev *root = rdev->pdev->bus->self;
	क्रमागत pci_bus_speed speed_cap;
	u32 speed_cntl, current_data_rate;
	पूर्णांक i;
	u16 पंचांगp16;

	अगर (pci_is_root_bus(rdev->pdev->bus))
		वापस;

	अगर (radeon_pcie_gen2 == 0)
		वापस;

	अगर (rdev->flags & RADEON_IS_IGP)
		वापस;

	अगर (!(rdev->flags & RADEON_IS_PCIE))
		वापस;

	speed_cap = pcie_get_speed_cap(root);
	अगर (speed_cap == PCI_SPEED_UNKNOWN)
		वापस;

	अगर ((speed_cap != PCIE_SPEED_8_0GT) &&
	    (speed_cap != PCIE_SPEED_5_0GT))
		वापस;

	speed_cntl = RREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL);
	current_data_rate = (speed_cntl & LC_CURRENT_DATA_RATE_MASK) >>
		LC_CURRENT_DATA_RATE_SHIFT;
	अगर (speed_cap == PCIE_SPEED_8_0GT) अणु
		अगर (current_data_rate == 2) अणु
			DRM_INFO("PCIE gen 3 link speeds already enabled\n");
			वापस;
		पूर्ण
		DRM_INFO("enabling PCIE gen 3 link speeds, disable with radeon.pcie_gen2=0\n");
	पूर्ण अन्यथा अगर (speed_cap == PCIE_SPEED_5_0GT) अणु
		अगर (current_data_rate == 1) अणु
			DRM_INFO("PCIE gen 2 link speeds already enabled\n");
			वापस;
		पूर्ण
		DRM_INFO("enabling PCIE gen 2 link speeds, disable with radeon.pcie_gen2=0\n");
	पूर्ण

	अगर (!pci_is_pcie(root) || !pci_is_pcie(rdev->pdev))
		वापस;

	अगर (speed_cap == PCIE_SPEED_8_0GT) अणु
		/* re-try equalization अगर gen3 is not alपढ़ोy enabled */
		अगर (current_data_rate != 2) अणु
			u16 bridge_cfg, gpu_cfg;
			u16 bridge_cfg2, gpu_cfg2;
			u32 max_lw, current_lw, पंचांगp;

			pcie_capability_पढ़ो_word(root, PCI_EXP_LNKCTL,
						  &bridge_cfg);
			pcie_capability_पढ़ो_word(rdev->pdev, PCI_EXP_LNKCTL,
						  &gpu_cfg);

			पंचांगp16 = bridge_cfg | PCI_EXP_LNKCTL_HAWD;
			pcie_capability_ग_लिखो_word(root, PCI_EXP_LNKCTL, पंचांगp16);

			पंचांगp16 = gpu_cfg | PCI_EXP_LNKCTL_HAWD;
			pcie_capability_ग_लिखो_word(rdev->pdev, PCI_EXP_LNKCTL,
						   पंचांगp16);

			पंचांगp = RREG32_PCIE(PCIE_LC_STATUS1);
			max_lw = (पंचांगp & LC_DETECTED_LINK_WIDTH_MASK) >> LC_DETECTED_LINK_WIDTH_SHIFT;
			current_lw = (पंचांगp & LC_OPERATING_LINK_WIDTH_MASK) >> LC_OPERATING_LINK_WIDTH_SHIFT;

			अगर (current_lw < max_lw) अणु
				पंचांगp = RREG32_PCIE_PORT(PCIE_LC_LINK_WIDTH_CNTL);
				अगर (पंचांगp & LC_RENEGOTIATION_SUPPORT) अणु
					पंचांगp &= ~(LC_LINK_WIDTH_MASK | LC_UPCONFIGURE_DIS);
					पंचांगp |= (max_lw << LC_LINK_WIDTH_SHIFT);
					पंचांगp |= LC_UPCONFIGURE_SUPPORT | LC_RENEGOTIATE_EN | LC_RECONFIG_NOW;
					WREG32_PCIE_PORT(PCIE_LC_LINK_WIDTH_CNTL, पंचांगp);
				पूर्ण
			पूर्ण

			क्रम (i = 0; i < 10; i++) अणु
				/* check status */
				pcie_capability_पढ़ो_word(rdev->pdev,
							  PCI_EXP_DEVSTA,
							  &पंचांगp16);
				अगर (पंचांगp16 & PCI_EXP_DEVSTA_TRPND)
					अवरोध;

				pcie_capability_पढ़ो_word(root, PCI_EXP_LNKCTL,
							  &bridge_cfg);
				pcie_capability_पढ़ो_word(rdev->pdev,
							  PCI_EXP_LNKCTL,
							  &gpu_cfg);

				pcie_capability_पढ़ो_word(root, PCI_EXP_LNKCTL2,
							  &bridge_cfg2);
				pcie_capability_पढ़ो_word(rdev->pdev,
							  PCI_EXP_LNKCTL2,
							  &gpu_cfg2);

				पंचांगp = RREG32_PCIE_PORT(PCIE_LC_CNTL4);
				पंचांगp |= LC_SET_QUIESCE;
				WREG32_PCIE_PORT(PCIE_LC_CNTL4, पंचांगp);

				पंचांगp = RREG32_PCIE_PORT(PCIE_LC_CNTL4);
				पंचांगp |= LC_REDO_EQ;
				WREG32_PCIE_PORT(PCIE_LC_CNTL4, पंचांगp);

				msleep(100);

				/* linkctl */
				pcie_capability_पढ़ो_word(root, PCI_EXP_LNKCTL,
							  &पंचांगp16);
				पंचांगp16 &= ~PCI_EXP_LNKCTL_HAWD;
				पंचांगp16 |= (bridge_cfg & PCI_EXP_LNKCTL_HAWD);
				pcie_capability_ग_लिखो_word(root,
							   PCI_EXP_LNKCTL,
							   पंचांगp16);

				pcie_capability_पढ़ो_word(rdev->pdev,
							  PCI_EXP_LNKCTL,
							  &पंचांगp16);
				पंचांगp16 &= ~PCI_EXP_LNKCTL_HAWD;
				पंचांगp16 |= (gpu_cfg & PCI_EXP_LNKCTL_HAWD);
				pcie_capability_ग_लिखो_word(rdev->pdev,
							   PCI_EXP_LNKCTL,
							   पंचांगp16);

				/* linkctl2 */
				pcie_capability_पढ़ो_word(root, PCI_EXP_LNKCTL2,
							  &पंचांगp16);
				पंचांगp16 &= ~(PCI_EXP_LNKCTL2_ENTER_COMP |
					   PCI_EXP_LNKCTL2_TX_MARGIN);
				पंचांगp16 |= (bridge_cfg2 &
					  (PCI_EXP_LNKCTL2_ENTER_COMP |
					   PCI_EXP_LNKCTL2_TX_MARGIN));
				pcie_capability_ग_लिखो_word(root,
							   PCI_EXP_LNKCTL2,
							   पंचांगp16);

				pcie_capability_पढ़ो_word(rdev->pdev,
							  PCI_EXP_LNKCTL2,
							  &पंचांगp16);
				पंचांगp16 &= ~(PCI_EXP_LNKCTL2_ENTER_COMP |
					   PCI_EXP_LNKCTL2_TX_MARGIN);
				पंचांगp16 |= (gpu_cfg2 &
					  (PCI_EXP_LNKCTL2_ENTER_COMP |
					   PCI_EXP_LNKCTL2_TX_MARGIN));
				pcie_capability_ग_लिखो_word(rdev->pdev,
							   PCI_EXP_LNKCTL2,
							   पंचांगp16);

				पंचांगp = RREG32_PCIE_PORT(PCIE_LC_CNTL4);
				पंचांगp &= ~LC_SET_QUIESCE;
				WREG32_PCIE_PORT(PCIE_LC_CNTL4, पंचांगp);
			पूर्ण
		पूर्ण
	पूर्ण

	/* set the link speed */
	speed_cntl |= LC_FORCE_EN_SW_SPEED_CHANGE | LC_FORCE_DIS_HW_SPEED_CHANGE;
	speed_cntl &= ~LC_FORCE_DIS_SW_SPEED_CHANGE;
	WREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL, speed_cntl);

	pcie_capability_पढ़ो_word(rdev->pdev, PCI_EXP_LNKCTL2, &पंचांगp16);
	पंचांगp16 &= ~PCI_EXP_LNKCTL2_TLS;
	अगर (speed_cap == PCIE_SPEED_8_0GT)
		पंचांगp16 |= PCI_EXP_LNKCTL2_TLS_8_0GT; /* gen3 */
	अन्यथा अगर (speed_cap == PCIE_SPEED_5_0GT)
		पंचांगp16 |= PCI_EXP_LNKCTL2_TLS_5_0GT; /* gen2 */
	अन्यथा
		पंचांगp16 |= PCI_EXP_LNKCTL2_TLS_2_5GT; /* gen1 */
	pcie_capability_ग_लिखो_word(rdev->pdev, PCI_EXP_LNKCTL2, पंचांगp16);

	speed_cntl = RREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL);
	speed_cntl |= LC_INITIATE_LINK_SPEED_CHANGE;
	WREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL, speed_cntl);

	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		speed_cntl = RREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL);
		अगर ((speed_cntl & LC_INITIATE_LINK_SPEED_CHANGE) == 0)
			अवरोध;
		udelay(1);
	पूर्ण
पूर्ण

अटल व्योम si_program_aspm(काष्ठा radeon_device *rdev)
अणु
	u32 data, orig;
	bool disable_l0s = false, disable_l1 = false, disable_plloff_in_l1 = false;
	bool disable_clkreq = false;

	अगर (radeon_aspm == 0)
		वापस;

	अगर (!(rdev->flags & RADEON_IS_PCIE))
		वापस;

	orig = data = RREG32_PCIE_PORT(PCIE_LC_N_FTS_CNTL);
	data &= ~LC_XMIT_N_FTS_MASK;
	data |= LC_XMIT_N_FTS(0x24) | LC_XMIT_N_FTS_OVERRIDE_EN;
	अगर (orig != data)
		WREG32_PCIE_PORT(PCIE_LC_N_FTS_CNTL, data);

	orig = data = RREG32_PCIE_PORT(PCIE_LC_CNTL3);
	data |= LC_GO_TO_RECOVERY;
	अगर (orig != data)
		WREG32_PCIE_PORT(PCIE_LC_CNTL3, data);

	orig = data = RREG32_PCIE(PCIE_P_CNTL);
	data |= P_IGNORE_EDB_ERR;
	अगर (orig != data)
		WREG32_PCIE(PCIE_P_CNTL, data);

	orig = data = RREG32_PCIE_PORT(PCIE_LC_CNTL);
	data &= ~(LC_L0S_INACTIVITY_MASK | LC_L1_INACTIVITY_MASK);
	data |= LC_PMI_TO_L1_DIS;
	अगर (!disable_l0s)
		data |= LC_L0S_INACTIVITY(7);

	अगर (!disable_l1) अणु
		data |= LC_L1_INACTIVITY(7);
		data &= ~LC_PMI_TO_L1_DIS;
		अगर (orig != data)
			WREG32_PCIE_PORT(PCIE_LC_CNTL, data);

		अगर (!disable_plloff_in_l1) अणु
			bool clk_req_support;

			orig = data = RREG32_PIF_PHY0(PB0_PIF_PWRDOWN_0);
			data &= ~(PLL_POWER_STATE_IN_OFF_0_MASK | PLL_POWER_STATE_IN_TXS2_0_MASK);
			data |= PLL_POWER_STATE_IN_OFF_0(7) | PLL_POWER_STATE_IN_TXS2_0(7);
			अगर (orig != data)
				WREG32_PIF_PHY0(PB0_PIF_PWRDOWN_0, data);

			orig = data = RREG32_PIF_PHY0(PB0_PIF_PWRDOWN_1);
			data &= ~(PLL_POWER_STATE_IN_OFF_1_MASK | PLL_POWER_STATE_IN_TXS2_1_MASK);
			data |= PLL_POWER_STATE_IN_OFF_1(7) | PLL_POWER_STATE_IN_TXS2_1(7);
			अगर (orig != data)
				WREG32_PIF_PHY0(PB0_PIF_PWRDOWN_1, data);

			orig = data = RREG32_PIF_PHY1(PB1_PIF_PWRDOWN_0);
			data &= ~(PLL_POWER_STATE_IN_OFF_0_MASK | PLL_POWER_STATE_IN_TXS2_0_MASK);
			data |= PLL_POWER_STATE_IN_OFF_0(7) | PLL_POWER_STATE_IN_TXS2_0(7);
			अगर (orig != data)
				WREG32_PIF_PHY1(PB1_PIF_PWRDOWN_0, data);

			orig = data = RREG32_PIF_PHY1(PB1_PIF_PWRDOWN_1);
			data &= ~(PLL_POWER_STATE_IN_OFF_1_MASK | PLL_POWER_STATE_IN_TXS2_1_MASK);
			data |= PLL_POWER_STATE_IN_OFF_1(7) | PLL_POWER_STATE_IN_TXS2_1(7);
			अगर (orig != data)
				WREG32_PIF_PHY1(PB1_PIF_PWRDOWN_1, data);

			अगर ((rdev->family != CHIP_OLAND) && (rdev->family != CHIP_HAIन_अंक)) अणु
				orig = data = RREG32_PIF_PHY0(PB0_PIF_PWRDOWN_0);
				data &= ~PLL_RAMP_UP_TIME_0_MASK;
				अगर (orig != data)
					WREG32_PIF_PHY0(PB0_PIF_PWRDOWN_0, data);

				orig = data = RREG32_PIF_PHY0(PB0_PIF_PWRDOWN_1);
				data &= ~PLL_RAMP_UP_TIME_1_MASK;
				अगर (orig != data)
					WREG32_PIF_PHY0(PB0_PIF_PWRDOWN_1, data);

				orig = data = RREG32_PIF_PHY0(PB0_PIF_PWRDOWN_2);
				data &= ~PLL_RAMP_UP_TIME_2_MASK;
				अगर (orig != data)
					WREG32_PIF_PHY0(PB0_PIF_PWRDOWN_2, data);

				orig = data = RREG32_PIF_PHY0(PB0_PIF_PWRDOWN_3);
				data &= ~PLL_RAMP_UP_TIME_3_MASK;
				अगर (orig != data)
					WREG32_PIF_PHY0(PB0_PIF_PWRDOWN_3, data);

				orig = data = RREG32_PIF_PHY1(PB1_PIF_PWRDOWN_0);
				data &= ~PLL_RAMP_UP_TIME_0_MASK;
				अगर (orig != data)
					WREG32_PIF_PHY1(PB1_PIF_PWRDOWN_0, data);

				orig = data = RREG32_PIF_PHY1(PB1_PIF_PWRDOWN_1);
				data &= ~PLL_RAMP_UP_TIME_1_MASK;
				अगर (orig != data)
					WREG32_PIF_PHY1(PB1_PIF_PWRDOWN_1, data);

				orig = data = RREG32_PIF_PHY1(PB1_PIF_PWRDOWN_2);
				data &= ~PLL_RAMP_UP_TIME_2_MASK;
				अगर (orig != data)
					WREG32_PIF_PHY1(PB1_PIF_PWRDOWN_2, data);

				orig = data = RREG32_PIF_PHY1(PB1_PIF_PWRDOWN_3);
				data &= ~PLL_RAMP_UP_TIME_3_MASK;
				अगर (orig != data)
					WREG32_PIF_PHY1(PB1_PIF_PWRDOWN_3, data);
			पूर्ण
			orig = data = RREG32_PCIE_PORT(PCIE_LC_LINK_WIDTH_CNTL);
			data &= ~LC_DYN_LANES_PWR_STATE_MASK;
			data |= LC_DYN_LANES_PWR_STATE(3);
			अगर (orig != data)
				WREG32_PCIE_PORT(PCIE_LC_LINK_WIDTH_CNTL, data);

			orig = data = RREG32_PIF_PHY0(PB0_PIF_CNTL);
			data &= ~LS2_EXIT_TIME_MASK;
			अगर ((rdev->family == CHIP_OLAND) || (rdev->family == CHIP_HAIन_अंक))
				data |= LS2_EXIT_TIME(5);
			अगर (orig != data)
				WREG32_PIF_PHY0(PB0_PIF_CNTL, data);

			orig = data = RREG32_PIF_PHY1(PB1_PIF_CNTL);
			data &= ~LS2_EXIT_TIME_MASK;
			अगर ((rdev->family == CHIP_OLAND) || (rdev->family == CHIP_HAIन_अंक))
				data |= LS2_EXIT_TIME(5);
			अगर (orig != data)
				WREG32_PIF_PHY1(PB1_PIF_CNTL, data);

			अगर (!disable_clkreq &&
			    !pci_is_root_bus(rdev->pdev->bus)) अणु
				काष्ठा pci_dev *root = rdev->pdev->bus->self;
				u32 lnkcap;

				clk_req_support = false;
				pcie_capability_पढ़ो_dword(root, PCI_EXP_LNKCAP, &lnkcap);
				अगर (lnkcap & PCI_EXP_LNKCAP_CLKPM)
					clk_req_support = true;
			पूर्ण अन्यथा अणु
				clk_req_support = false;
			पूर्ण

			अगर (clk_req_support) अणु
				orig = data = RREG32_PCIE_PORT(PCIE_LC_CNTL2);
				data |= LC_ALLOW_PDWN_IN_L1 | LC_ALLOW_PDWN_IN_L23;
				अगर (orig != data)
					WREG32_PCIE_PORT(PCIE_LC_CNTL2, data);

				orig = data = RREG32(THM_CLK_CNTL);
				data &= ~(CMON_CLK_SEL_MASK | TMON_CLK_SEL_MASK);
				data |= CMON_CLK_SEL(1) | TMON_CLK_SEL(1);
				अगर (orig != data)
					WREG32(THM_CLK_CNTL, data);

				orig = data = RREG32(MISC_CLK_CNTL);
				data &= ~(DEEP_SLEEP_CLK_SEL_MASK | ZCLK_SEL_MASK);
				data |= DEEP_SLEEP_CLK_SEL(1) | ZCLK_SEL(1);
				अगर (orig != data)
					WREG32(MISC_CLK_CNTL, data);

				orig = data = RREG32(CG_CLKPIN_CNTL);
				data &= ~BCLK_AS_XCLK;
				अगर (orig != data)
					WREG32(CG_CLKPIN_CNTL, data);

				orig = data = RREG32(CG_CLKPIN_CNTL_2);
				data &= ~FORCE_BIF_REFCLK_EN;
				अगर (orig != data)
					WREG32(CG_CLKPIN_CNTL_2, data);

				orig = data = RREG32(MPLL_BYPASSCLK_SEL);
				data &= ~MPLL_CLKOUT_SEL_MASK;
				data |= MPLL_CLKOUT_SEL(4);
				अगर (orig != data)
					WREG32(MPLL_BYPASSCLK_SEL, data);

				orig = data = RREG32(SPLL_CNTL_MODE);
				data &= ~SPLL_REFCLK_SEL_MASK;
				अगर (orig != data)
					WREG32(SPLL_CNTL_MODE, data);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (orig != data)
			WREG32_PCIE_PORT(PCIE_LC_CNTL, data);
	पूर्ण

	orig = data = RREG32_PCIE(PCIE_CNTL2);
	data |= SLV_MEM_LS_EN | MST_MEM_LS_EN | REPLAY_MEM_LS_EN;
	अगर (orig != data)
		WREG32_PCIE(PCIE_CNTL2, data);

	अगर (!disable_l0s) अणु
		data = RREG32_PCIE_PORT(PCIE_LC_N_FTS_CNTL);
		अगर((data & LC_N_FTS_MASK) == LC_N_FTS_MASK) अणु
			data = RREG32_PCIE(PCIE_LC_STATUS1);
			अगर ((data & LC_REVERSE_XMIT) && (data & LC_REVERSE_RCVR)) अणु
				orig = data = RREG32_PCIE_PORT(PCIE_LC_CNTL);
				data &= ~LC_L0S_INACTIVITY_MASK;
				अगर (orig != data)
					WREG32_PCIE_PORT(PCIE_LC_CNTL, data);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक si_vce_send_vcepll_ctlreq(काष्ठा radeon_device *rdev)
अणु
	अचिन्हित i;

	/* make sure VCEPLL_CTLREQ is deनिश्चितed */
	WREG32_SMC_P(CG_VCEPLL_FUNC_CNTL, 0, ~UPLL_CTLREQ_MASK);

	mdelay(10);

	/* निश्चित UPLL_CTLREQ */
	WREG32_SMC_P(CG_VCEPLL_FUNC_CNTL, UPLL_CTLREQ_MASK, ~UPLL_CTLREQ_MASK);

	/* रुको क्रम CTLACK and CTLACK2 to get निश्चितed */
	क्रम (i = 0; i < 100; ++i) अणु
		uपूर्णांक32_t mask = UPLL_CTLACK_MASK | UPLL_CTLACK2_MASK;
		अगर ((RREG32_SMC(CG_VCEPLL_FUNC_CNTL) & mask) == mask)
			अवरोध;
		mdelay(10);
	पूर्ण

	/* deनिश्चित UPLL_CTLREQ */
	WREG32_SMC_P(CG_VCEPLL_FUNC_CNTL, 0, ~UPLL_CTLREQ_MASK);

	अगर (i == 100) अणु
		DRM_ERROR("Timeout setting UVD clocks!\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक si_set_vce_घड़ीs(काष्ठा radeon_device *rdev, u32 evclk, u32 ecclk)
अणु
	अचिन्हित fb_भाग = 0, evclk_भाग = 0, ecclk_भाग = 0;
	पूर्णांक r;

	/* bypass evclk and ecclk with bclk */
	WREG32_SMC_P(CG_VCEPLL_FUNC_CNTL_2,
		     EVCLK_SRC_SEL(1) | ECCLK_SRC_SEL(1),
		     ~(EVCLK_SRC_SEL_MASK | ECCLK_SRC_SEL_MASK));

	/* put PLL in bypass mode */
	WREG32_SMC_P(CG_VCEPLL_FUNC_CNTL, VCEPLL_BYPASS_EN_MASK,
		     ~VCEPLL_BYPASS_EN_MASK);

	अगर (!evclk || !ecclk) अणु
		/* keep the Bypass mode, put PLL to sleep */
		WREG32_SMC_P(CG_VCEPLL_FUNC_CNTL, VCEPLL_SLEEP_MASK,
			     ~VCEPLL_SLEEP_MASK);
		वापस 0;
	पूर्ण

	r = radeon_uvd_calc_upll_भागiders(rdev, evclk, ecclk, 125000, 250000,
					  16384, 0x03FFFFFF, 0, 128, 5,
					  &fb_भाग, &evclk_भाग, &ecclk_भाग);
	अगर (r)
		वापस r;

	/* set RESET_ANTI_MUX to 0 */
	WREG32_SMC_P(CG_VCEPLL_FUNC_CNTL_5, 0, ~RESET_ANTI_MUX_MASK);

	/* set VCO_MODE to 1 */
	WREG32_SMC_P(CG_VCEPLL_FUNC_CNTL, VCEPLL_VCO_MODE_MASK,
		     ~VCEPLL_VCO_MODE_MASK);

	/* toggle VCEPLL_SLEEP to 1 then back to 0 */
	WREG32_SMC_P(CG_VCEPLL_FUNC_CNTL, VCEPLL_SLEEP_MASK,
		     ~VCEPLL_SLEEP_MASK);
	WREG32_SMC_P(CG_VCEPLL_FUNC_CNTL, 0, ~VCEPLL_SLEEP_MASK);

	/* deनिश्चित VCEPLL_RESET */
	WREG32_SMC_P(CG_VCEPLL_FUNC_CNTL, 0, ~VCEPLL_RESET_MASK);

	mdelay(1);

	r = si_vce_send_vcepll_ctlreq(rdev);
	अगर (r)
		वापस r;

	/* निश्चित VCEPLL_RESET again */
	WREG32_SMC_P(CG_VCEPLL_FUNC_CNTL, VCEPLL_RESET_MASK, ~VCEPLL_RESET_MASK);

	/* disable spपढ़ो spectrum. */
	WREG32_SMC_P(CG_VCEPLL_SPREAD_SPECTRUM, 0, ~SSEN_MASK);

	/* set feedback भागider */
	WREG32_SMC_P(CG_VCEPLL_FUNC_CNTL_3, VCEPLL_FB_DIV(fb_भाग), ~VCEPLL_FB_DIV_MASK);

	/* set ref भागider to 0 */
	WREG32_SMC_P(CG_VCEPLL_FUNC_CNTL, 0, ~VCEPLL_REF_DIV_MASK);

	/* set PDIV_A and PDIV_B */
	WREG32_SMC_P(CG_VCEPLL_FUNC_CNTL_2,
		     VCEPLL_PDIV_A(evclk_भाग) | VCEPLL_PDIV_B(ecclk_भाग),
		     ~(VCEPLL_PDIV_A_MASK | VCEPLL_PDIV_B_MASK));

	/* give the PLL some समय to settle */
	mdelay(15);

	/* deनिश्चित PLL_RESET */
	WREG32_SMC_P(CG_VCEPLL_FUNC_CNTL, 0, ~VCEPLL_RESET_MASK);

	mdelay(15);

	/* चयन from bypass mode to normal mode */
	WREG32_SMC_P(CG_VCEPLL_FUNC_CNTL, 0, ~VCEPLL_BYPASS_EN_MASK);

	r = si_vce_send_vcepll_ctlreq(rdev);
	अगर (r)
		वापस r;

	/* चयन VCLK and DCLK selection */
	WREG32_SMC_P(CG_VCEPLL_FUNC_CNTL_2,
		     EVCLK_SRC_SEL(16) | ECCLK_SRC_SEL(16),
		     ~(EVCLK_SRC_SEL_MASK | ECCLK_SRC_SEL_MASK));

	mdelay(100);

	वापस 0;
पूर्ण
