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

#समावेश <linux/pci.h>
#समावेश <linux/seq_file.h>

#समावेश "atom.h"
#समावेश "btc_dpm.h"
#समावेश "btcd.h"
#समावेश "cypress_dpm.h"
#समावेश "evergreen.h"
#समावेश "r600_dpm.h"
#समावेश "rv770.h"
#समावेश "radeon.h"
#समावेश "radeon_asic.h"

#घोषणा MC_CG_ARB_FREQ_F0           0x0a
#घोषणा MC_CG_ARB_FREQ_F1           0x0b
#घोषणा MC_CG_ARB_FREQ_F2           0x0c
#घोषणा MC_CG_ARB_FREQ_F3           0x0d

#घोषणा MC_CG_SEQ_DRAMCONF_S0       0x05
#घोषणा MC_CG_SEQ_DRAMCONF_S1       0x06
#घोषणा MC_CG_SEQ_YCLK_SUSPEND      0x04
#घोषणा MC_CG_SEQ_YCLK_RESUME       0x0a

#घोषणा SMC_RAM_END 0x8000

#अगर_अघोषित BTC_MGCG_SEQUENCE
#घोषणा BTC_MGCG_SEQUENCE  300

बाह्य पूर्णांक ni_mc_load_microcode(काष्ठा radeon_device *rdev);

//********* BARTS **************//
अटल स्थिर u32 barts_cgcg_cgls_शेष[] =
अणु
	/* Register,   Value,     Mask bits */
	0x000008f8, 0x00000010, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000011, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000012, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000013, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000014, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000015, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000016, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000017, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000018, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000019, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x0000001a, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x0000001b, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000020, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000021, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000022, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000023, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000024, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000025, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000026, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000027, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000028, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000029, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x0000002a, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x0000002b, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff
पूर्ण;
#घोषणा BARTS_CGCG_CGLS_DEFAULT_LENGTH माप(barts_cgcg_cgls_शेष) / (3 * माप(u32))

अटल स्थिर u32 barts_cgcg_cgls_disable[] =
अणु
	0x000008f8, 0x00000010, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000011, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000012, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000013, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000014, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000015, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000016, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000017, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000018, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000019, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x0000001a, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x0000001b, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000020, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000021, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000022, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000023, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000024, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000025, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000026, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000027, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000028, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000029, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x0000002a, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x0000002b, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x00000644, 0x000f7912, 0x001f4180,
	0x00000644, 0x000f3812, 0x001f4180
पूर्ण;
#घोषणा BARTS_CGCG_CGLS_DISABLE_LENGTH माप(barts_cgcg_cgls_disable) / (3 * माप(u32))

अटल स्थिर u32 barts_cgcg_cgls_enable[] =
अणु
	/* 0x0000c124, 0x84180000, 0x00180000, */
	0x00000644, 0x000f7892, 0x001f4080,
	0x000008f8, 0x00000010, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000011, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000012, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000013, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000014, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000015, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000016, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000017, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000018, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000019, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x0000001a, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x0000001b, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000020, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000021, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000022, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000023, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000024, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000025, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000026, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000027, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000028, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000029, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x0000002a, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x0000002b, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff
पूर्ण;
#घोषणा BARTS_CGCG_CGLS_ENABLE_LENGTH माप(barts_cgcg_cgls_enable) / (3 * माप(u32))

अटल स्थिर u32 barts_mgcg_शेष[] =
अणु
	0x0000802c, 0xc0000000, 0xffffffff,
	0x00005448, 0x00000100, 0xffffffff,
	0x000055e4, 0x00600100, 0xffffffff,
	0x0000160c, 0x00000100, 0xffffffff,
	0x0000c164, 0x00000100, 0xffffffff,
	0x00008a18, 0x00000100, 0xffffffff,
	0x0000897c, 0x06000100, 0xffffffff,
	0x00008b28, 0x00000100, 0xffffffff,
	0x00009144, 0x00000100, 0xffffffff,
	0x00009a60, 0x00000100, 0xffffffff,
	0x00009868, 0x00000100, 0xffffffff,
	0x00008d58, 0x00000100, 0xffffffff,
	0x00009510, 0x00000100, 0xffffffff,
	0x0000949c, 0x00000100, 0xffffffff,
	0x00009654, 0x00000100, 0xffffffff,
	0x00009030, 0x00000100, 0xffffffff,
	0x00009034, 0x00000100, 0xffffffff,
	0x00009038, 0x00000100, 0xffffffff,
	0x0000903c, 0x00000100, 0xffffffff,
	0x00009040, 0x00000100, 0xffffffff,
	0x0000a200, 0x00000100, 0xffffffff,
	0x0000a204, 0x00000100, 0xffffffff,
	0x0000a208, 0x00000100, 0xffffffff,
	0x0000a20c, 0x00000100, 0xffffffff,
	0x0000977c, 0x00000100, 0xffffffff,
	0x00003f80, 0x00000100, 0xffffffff,
	0x0000a210, 0x00000100, 0xffffffff,
	0x0000a214, 0x00000100, 0xffffffff,
	0x000004d8, 0x00000100, 0xffffffff,
	0x00009784, 0x00000100, 0xffffffff,
	0x00009698, 0x00000100, 0xffffffff,
	0x000004d4, 0x00000200, 0xffffffff,
	0x000004d0, 0x00000000, 0xffffffff,
	0x000030cc, 0x00000100, 0xffffffff,
	0x0000d0c0, 0xff000100, 0xffffffff,
	0x0000802c, 0x40000000, 0xffffffff,
	0x0000915c, 0x00010000, 0xffffffff,
	0x00009160, 0x00030002, 0xffffffff,
	0x00009164, 0x00050004, 0xffffffff,
	0x00009168, 0x00070006, 0xffffffff,
	0x00009178, 0x00070000, 0xffffffff,
	0x0000917c, 0x00030002, 0xffffffff,
	0x00009180, 0x00050004, 0xffffffff,
	0x0000918c, 0x00010006, 0xffffffff,
	0x00009190, 0x00090008, 0xffffffff,
	0x00009194, 0x00070000, 0xffffffff,
	0x00009198, 0x00030002, 0xffffffff,
	0x0000919c, 0x00050004, 0xffffffff,
	0x000091a8, 0x00010006, 0xffffffff,
	0x000091ac, 0x00090008, 0xffffffff,
	0x000091b0, 0x00070000, 0xffffffff,
	0x000091b4, 0x00030002, 0xffffffff,
	0x000091b8, 0x00050004, 0xffffffff,
	0x000091c4, 0x00010006, 0xffffffff,
	0x000091c8, 0x00090008, 0xffffffff,
	0x000091cc, 0x00070000, 0xffffffff,
	0x000091d0, 0x00030002, 0xffffffff,
	0x000091d4, 0x00050004, 0xffffffff,
	0x000091e0, 0x00010006, 0xffffffff,
	0x000091e4, 0x00090008, 0xffffffff,
	0x000091e8, 0x00000000, 0xffffffff,
	0x000091ec, 0x00070000, 0xffffffff,
	0x000091f0, 0x00030002, 0xffffffff,
	0x000091f4, 0x00050004, 0xffffffff,
	0x00009200, 0x00010006, 0xffffffff,
	0x00009204, 0x00090008, 0xffffffff,
	0x00009208, 0x00070000, 0xffffffff,
	0x0000920c, 0x00030002, 0xffffffff,
	0x00009210, 0x00050004, 0xffffffff,
	0x0000921c, 0x00010006, 0xffffffff,
	0x00009220, 0x00090008, 0xffffffff,
	0x00009224, 0x00070000, 0xffffffff,
	0x00009228, 0x00030002, 0xffffffff,
	0x0000922c, 0x00050004, 0xffffffff,
	0x00009238, 0x00010006, 0xffffffff,
	0x0000923c, 0x00090008, 0xffffffff,
	0x00009294, 0x00000000, 0xffffffff,
	0x0000802c, 0x40010000, 0xffffffff,
	0x0000915c, 0x00010000, 0xffffffff,
	0x00009160, 0x00030002, 0xffffffff,
	0x00009164, 0x00050004, 0xffffffff,
	0x00009168, 0x00070006, 0xffffffff,
	0x00009178, 0x00070000, 0xffffffff,
	0x0000917c, 0x00030002, 0xffffffff,
	0x00009180, 0x00050004, 0xffffffff,
	0x0000918c, 0x00010006, 0xffffffff,
	0x00009190, 0x00090008, 0xffffffff,
	0x00009194, 0x00070000, 0xffffffff,
	0x00009198, 0x00030002, 0xffffffff,
	0x0000919c, 0x00050004, 0xffffffff,
	0x000091a8, 0x00010006, 0xffffffff,
	0x000091ac, 0x00090008, 0xffffffff,
	0x000091b0, 0x00070000, 0xffffffff,
	0x000091b4, 0x00030002, 0xffffffff,
	0x000091b8, 0x00050004, 0xffffffff,
	0x000091c4, 0x00010006, 0xffffffff,
	0x000091c8, 0x00090008, 0xffffffff,
	0x000091cc, 0x00070000, 0xffffffff,
	0x000091d0, 0x00030002, 0xffffffff,
	0x000091d4, 0x00050004, 0xffffffff,
	0x000091e0, 0x00010006, 0xffffffff,
	0x000091e4, 0x00090008, 0xffffffff,
	0x000091e8, 0x00000000, 0xffffffff,
	0x000091ec, 0x00070000, 0xffffffff,
	0x000091f0, 0x00030002, 0xffffffff,
	0x000091f4, 0x00050004, 0xffffffff,
	0x00009200, 0x00010006, 0xffffffff,
	0x00009204, 0x00090008, 0xffffffff,
	0x00009208, 0x00070000, 0xffffffff,
	0x0000920c, 0x00030002, 0xffffffff,
	0x00009210, 0x00050004, 0xffffffff,
	0x0000921c, 0x00010006, 0xffffffff,
	0x00009220, 0x00090008, 0xffffffff,
	0x00009224, 0x00070000, 0xffffffff,
	0x00009228, 0x00030002, 0xffffffff,
	0x0000922c, 0x00050004, 0xffffffff,
	0x00009238, 0x00010006, 0xffffffff,
	0x0000923c, 0x00090008, 0xffffffff,
	0x00009294, 0x00000000, 0xffffffff,
	0x0000802c, 0xc0000000, 0xffffffff,
	0x000008f8, 0x00000010, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000011, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000012, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000013, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000014, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000015, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000016, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000017, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000018, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000019, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x0000001a, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x0000001b, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff
पूर्ण;
#घोषणा BARTS_MGCG_DEFAULT_LENGTH माप(barts_mgcg_शेष) / (3 * माप(u32))

अटल स्थिर u32 barts_mgcg_disable[] =
अणु
	0x0000802c, 0xc0000000, 0xffffffff,
	0x000008f8, 0x00000000, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000001, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000002, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000003, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x00009150, 0x00600000, 0xffffffff
पूर्ण;
#घोषणा BARTS_MGCG_DISABLE_LENGTH माप(barts_mgcg_disable) / (3 * माप(u32))

अटल स्थिर u32 barts_mgcg_enable[] =
अणु
	0x0000802c, 0xc0000000, 0xffffffff,
	0x000008f8, 0x00000000, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000001, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000002, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000003, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x00009150, 0x81944000, 0xffffffff
पूर्ण;
#घोषणा BARTS_MGCG_ENABLE_LENGTH माप(barts_mgcg_enable) / (3 * माप(u32))

//********* CAICOS **************//
अटल स्थिर u32 caicos_cgcg_cgls_शेष[] =
अणु
	0x000008f8, 0x00000010, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000011, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000012, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000013, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000014, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000015, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000016, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000017, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000018, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000019, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x0000001a, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x0000001b, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000020, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000021, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000022, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000023, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000024, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000025, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000026, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000027, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000028, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000029, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x0000002a, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x0000002b, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff
पूर्ण;
#घोषणा CAICOS_CGCG_CGLS_DEFAULT_LENGTH माप(caicos_cgcg_cgls_शेष) / (3 * माप(u32))

अटल स्थिर u32 caicos_cgcg_cgls_disable[] =
अणु
	0x000008f8, 0x00000010, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000011, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000012, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000013, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000014, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000015, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000016, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000017, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000018, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000019, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x0000001a, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x0000001b, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000020, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000021, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000022, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000023, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000024, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000025, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000026, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000027, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000028, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000029, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x0000002a, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x0000002b, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x00000644, 0x000f7912, 0x001f4180,
	0x00000644, 0x000f3812, 0x001f4180
पूर्ण;
#घोषणा CAICOS_CGCG_CGLS_DISABLE_LENGTH माप(caicos_cgcg_cgls_disable) / (3 * माप(u32))

अटल स्थिर u32 caicos_cgcg_cgls_enable[] =
अणु
	/* 0x0000c124, 0x84180000, 0x00180000, */
	0x00000644, 0x000f7892, 0x001f4080,
	0x000008f8, 0x00000010, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000011, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000012, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000013, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000014, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000015, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000016, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000017, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000018, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000019, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x0000001a, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x0000001b, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000020, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000021, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000022, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000023, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000024, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000025, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000026, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000027, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000028, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000029, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x0000002a, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x0000002b, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff
पूर्ण;
#घोषणा CAICOS_CGCG_CGLS_ENABLE_LENGTH माप(caicos_cgcg_cgls_enable) / (3 * माप(u32))

अटल स्थिर u32 caicos_mgcg_शेष[] =
अणु
	0x0000802c, 0xc0000000, 0xffffffff,
	0x00005448, 0x00000100, 0xffffffff,
	0x000055e4, 0x00600100, 0xffffffff,
	0x0000160c, 0x00000100, 0xffffffff,
	0x0000c164, 0x00000100, 0xffffffff,
	0x00008a18, 0x00000100, 0xffffffff,
	0x0000897c, 0x06000100, 0xffffffff,
	0x00008b28, 0x00000100, 0xffffffff,
	0x00009144, 0x00000100, 0xffffffff,
	0x00009a60, 0x00000100, 0xffffffff,
	0x00009868, 0x00000100, 0xffffffff,
	0x00008d58, 0x00000100, 0xffffffff,
	0x00009510, 0x00000100, 0xffffffff,
	0x0000949c, 0x00000100, 0xffffffff,
	0x00009654, 0x00000100, 0xffffffff,
	0x00009030, 0x00000100, 0xffffffff,
	0x00009034, 0x00000100, 0xffffffff,
	0x00009038, 0x00000100, 0xffffffff,
	0x0000903c, 0x00000100, 0xffffffff,
	0x00009040, 0x00000100, 0xffffffff,
	0x0000a200, 0x00000100, 0xffffffff,
	0x0000a204, 0x00000100, 0xffffffff,
	0x0000a208, 0x00000100, 0xffffffff,
	0x0000a20c, 0x00000100, 0xffffffff,
	0x0000977c, 0x00000100, 0xffffffff,
	0x00003f80, 0x00000100, 0xffffffff,
	0x0000a210, 0x00000100, 0xffffffff,
	0x0000a214, 0x00000100, 0xffffffff,
	0x000004d8, 0x00000100, 0xffffffff,
	0x00009784, 0x00000100, 0xffffffff,
	0x00009698, 0x00000100, 0xffffffff,
	0x000004d4, 0x00000200, 0xffffffff,
	0x000004d0, 0x00000000, 0xffffffff,
	0x000030cc, 0x00000100, 0xffffffff,
	0x0000d0c0, 0xff000100, 0xffffffff,
	0x0000915c, 0x00010000, 0xffffffff,
	0x00009160, 0x00030002, 0xffffffff,
	0x00009164, 0x00050004, 0xffffffff,
	0x00009168, 0x00070006, 0xffffffff,
	0x00009178, 0x00070000, 0xffffffff,
	0x0000917c, 0x00030002, 0xffffffff,
	0x00009180, 0x00050004, 0xffffffff,
	0x0000918c, 0x00010006, 0xffffffff,
	0x00009190, 0x00090008, 0xffffffff,
	0x00009194, 0x00070000, 0xffffffff,
	0x00009198, 0x00030002, 0xffffffff,
	0x0000919c, 0x00050004, 0xffffffff,
	0x000091a8, 0x00010006, 0xffffffff,
	0x000091ac, 0x00090008, 0xffffffff,
	0x000091e8, 0x00000000, 0xffffffff,
	0x00009294, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000010, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000011, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000012, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000013, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000014, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000015, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000016, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000017, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000018, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000019, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x0000001a, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x0000001b, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff
पूर्ण;
#घोषणा CAICOS_MGCG_DEFAULT_LENGTH माप(caicos_mgcg_शेष) / (3 * माप(u32))

अटल स्थिर u32 caicos_mgcg_disable[] =
अणु
	0x0000802c, 0xc0000000, 0xffffffff,
	0x000008f8, 0x00000000, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000001, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000002, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000003, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x00009150, 0x00600000, 0xffffffff
पूर्ण;
#घोषणा CAICOS_MGCG_DISABLE_LENGTH माप(caicos_mgcg_disable) / (3 * माप(u32))

अटल स्थिर u32 caicos_mgcg_enable[] =
अणु
	0x0000802c, 0xc0000000, 0xffffffff,
	0x000008f8, 0x00000000, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000001, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000002, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000003, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x00009150, 0x46944040, 0xffffffff
पूर्ण;
#घोषणा CAICOS_MGCG_ENABLE_LENGTH माप(caicos_mgcg_enable) / (3 * माप(u32))

//********* TURKS **************//
अटल स्थिर u32 turks_cgcg_cgls_शेष[] =
अणु
	0x000008f8, 0x00000010, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000011, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000012, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000013, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000014, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000015, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000016, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000017, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000018, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000019, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x0000001a, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x0000001b, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000020, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000021, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000022, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000023, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000024, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000025, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000026, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000027, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000028, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000029, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x0000002a, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x0000002b, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff
पूर्ण;
#घोषणा TURKS_CGCG_CGLS_DEFAULT_LENGTH  माप(turks_cgcg_cgls_शेष) / (3 * माप(u32))

अटल स्थिर u32 turks_cgcg_cgls_disable[] =
अणु
	0x000008f8, 0x00000010, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000011, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000012, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000013, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000014, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000015, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000016, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000017, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000018, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000019, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x0000001a, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x0000001b, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000020, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000021, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000022, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000023, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000024, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000025, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000026, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000027, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000028, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000029, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x0000002a, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x0000002b, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x00000644, 0x000f7912, 0x001f4180,
	0x00000644, 0x000f3812, 0x001f4180
पूर्ण;
#घोषणा TURKS_CGCG_CGLS_DISABLE_LENGTH माप(turks_cgcg_cgls_disable) / (3 * माप(u32))

अटल स्थिर u32 turks_cgcg_cgls_enable[] =
अणु
	/* 0x0000c124, 0x84180000, 0x00180000, */
	0x00000644, 0x000f7892, 0x001f4080,
	0x000008f8, 0x00000010, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000011, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000012, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000013, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000014, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000015, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000016, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000017, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000018, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000019, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x0000001a, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x0000001b, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000020, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000021, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000022, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000023, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000024, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000025, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000026, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000027, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000028, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000029, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x0000002a, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x0000002b, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff
पूर्ण;
#घोषणा TURKS_CGCG_CGLS_ENABLE_LENGTH माप(turks_cgcg_cgls_enable) / (3 * माप(u32))

// These are the sequences क्रम turks_mgcg_shls
अटल स्थिर u32 turks_mgcg_शेष[] =
अणु
	0x0000802c, 0xc0000000, 0xffffffff,
	0x00005448, 0x00000100, 0xffffffff,
	0x000055e4, 0x00600100, 0xffffffff,
	0x0000160c, 0x00000100, 0xffffffff,
	0x0000c164, 0x00000100, 0xffffffff,
	0x00008a18, 0x00000100, 0xffffffff,
	0x0000897c, 0x06000100, 0xffffffff,
	0x00008b28, 0x00000100, 0xffffffff,
	0x00009144, 0x00000100, 0xffffffff,
	0x00009a60, 0x00000100, 0xffffffff,
	0x00009868, 0x00000100, 0xffffffff,
	0x00008d58, 0x00000100, 0xffffffff,
	0x00009510, 0x00000100, 0xffffffff,
	0x0000949c, 0x00000100, 0xffffffff,
	0x00009654, 0x00000100, 0xffffffff,
	0x00009030, 0x00000100, 0xffffffff,
	0x00009034, 0x00000100, 0xffffffff,
	0x00009038, 0x00000100, 0xffffffff,
	0x0000903c, 0x00000100, 0xffffffff,
	0x00009040, 0x00000100, 0xffffffff,
	0x0000a200, 0x00000100, 0xffffffff,
	0x0000a204, 0x00000100, 0xffffffff,
	0x0000a208, 0x00000100, 0xffffffff,
	0x0000a20c, 0x00000100, 0xffffffff,
	0x0000977c, 0x00000100, 0xffffffff,
	0x00003f80, 0x00000100, 0xffffffff,
	0x0000a210, 0x00000100, 0xffffffff,
	0x0000a214, 0x00000100, 0xffffffff,
	0x000004d8, 0x00000100, 0xffffffff,
	0x00009784, 0x00000100, 0xffffffff,
	0x00009698, 0x00000100, 0xffffffff,
	0x000004d4, 0x00000200, 0xffffffff,
	0x000004d0, 0x00000000, 0xffffffff,
	0x000030cc, 0x00000100, 0xffffffff,
	0x0000d0c0, 0x00000100, 0xffffffff,
	0x0000915c, 0x00010000, 0xffffffff,
	0x00009160, 0x00030002, 0xffffffff,
	0x00009164, 0x00050004, 0xffffffff,
	0x00009168, 0x00070006, 0xffffffff,
	0x00009178, 0x00070000, 0xffffffff,
	0x0000917c, 0x00030002, 0xffffffff,
	0x00009180, 0x00050004, 0xffffffff,
	0x0000918c, 0x00010006, 0xffffffff,
	0x00009190, 0x00090008, 0xffffffff,
	0x00009194, 0x00070000, 0xffffffff,
	0x00009198, 0x00030002, 0xffffffff,
	0x0000919c, 0x00050004, 0xffffffff,
	0x000091a8, 0x00010006, 0xffffffff,
	0x000091ac, 0x00090008, 0xffffffff,
	0x000091b0, 0x00070000, 0xffffffff,
	0x000091b4, 0x00030002, 0xffffffff,
	0x000091b8, 0x00050004, 0xffffffff,
	0x000091c4, 0x00010006, 0xffffffff,
	0x000091c8, 0x00090008, 0xffffffff,
	0x000091cc, 0x00070000, 0xffffffff,
	0x000091d0, 0x00030002, 0xffffffff,
	0x000091d4, 0x00050004, 0xffffffff,
	0x000091e0, 0x00010006, 0xffffffff,
	0x000091e4, 0x00090008, 0xffffffff,
	0x000091e8, 0x00000000, 0xffffffff,
	0x000091ec, 0x00070000, 0xffffffff,
	0x000091f0, 0x00030002, 0xffffffff,
	0x000091f4, 0x00050004, 0xffffffff,
	0x00009200, 0x00010006, 0xffffffff,
	0x00009204, 0x00090008, 0xffffffff,
	0x00009208, 0x00070000, 0xffffffff,
	0x0000920c, 0x00030002, 0xffffffff,
	0x00009210, 0x00050004, 0xffffffff,
	0x0000921c, 0x00010006, 0xffffffff,
	0x00009220, 0x00090008, 0xffffffff,
	0x00009294, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000010, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000011, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000012, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000013, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000014, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000015, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000016, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000017, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000018, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000019, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x0000001a, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x0000001b, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff
पूर्ण;
#घोषणा TURKS_MGCG_DEFAULT_LENGTH माप(turks_mgcg_शेष) / (3 * माप(u32))

अटल स्थिर u32 turks_mgcg_disable[] =
अणु
	0x0000802c, 0xc0000000, 0xffffffff,
	0x000008f8, 0x00000000, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000001, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000002, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000003, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x00009150, 0x00600000, 0xffffffff
पूर्ण;
#घोषणा TURKS_MGCG_DISABLE_LENGTH माप(turks_mgcg_disable) / (3 * माप(u32))

अटल स्थिर u32 turks_mgcg_enable[] =
अणु
	0x0000802c, 0xc0000000, 0xffffffff,
	0x000008f8, 0x00000000, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000001, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000002, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000003, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x00009150, 0x6e944000, 0xffffffff
पूर्ण;
#घोषणा TURKS_MGCG_ENABLE_LENGTH माप(turks_mgcg_enable) / (3 * माप(u32))

#पूर्ण_अगर

#अगर_अघोषित BTC_SYSLS_SEQUENCE
#घोषणा BTC_SYSLS_SEQUENCE  100


//********* BARTS **************//
अटल स्थिर u32 barts_sysls_शेष[] =
अणु
	/* Register,   Value,     Mask bits */
	0x000055e8, 0x00000000, 0xffffffff,
	0x0000d0bc, 0x00000000, 0xffffffff,
	0x000015c0, 0x000c1401, 0xffffffff,
	0x0000264c, 0x000c0400, 0xffffffff,
	0x00002648, 0x000c0400, 0xffffffff,
	0x00002650, 0x000c0400, 0xffffffff,
	0x000020b8, 0x000c0400, 0xffffffff,
	0x000020bc, 0x000c0400, 0xffffffff,
	0x000020c0, 0x000c0c80, 0xffffffff,
	0x0000f4a0, 0x000000c0, 0xffffffff,
	0x0000f4a4, 0x00680fff, 0xffffffff,
	0x000004c8, 0x00000001, 0xffffffff,
	0x000064ec, 0x00000000, 0xffffffff,
	0x00000c7c, 0x00000000, 0xffffffff,
	0x00006dfc, 0x00000000, 0xffffffff
पूर्ण;
#घोषणा BARTS_SYSLS_DEFAULT_LENGTH माप(barts_sysls_शेष) / (3 * माप(u32))

अटल स्थिर u32 barts_sysls_disable[] =
अणु
	0x000055e8, 0x00000000, 0xffffffff,
	0x0000d0bc, 0x00000000, 0xffffffff,
	0x000015c0, 0x00041401, 0xffffffff,
	0x0000264c, 0x00040400, 0xffffffff,
	0x00002648, 0x00040400, 0xffffffff,
	0x00002650, 0x00040400, 0xffffffff,
	0x000020b8, 0x00040400, 0xffffffff,
	0x000020bc, 0x00040400, 0xffffffff,
	0x000020c0, 0x00040c80, 0xffffffff,
	0x0000f4a0, 0x000000c0, 0xffffffff,
	0x0000f4a4, 0x00680000, 0xffffffff,
	0x000004c8, 0x00000001, 0xffffffff,
	0x000064ec, 0x00007ffd, 0xffffffff,
	0x00000c7c, 0x0000ff00, 0xffffffff,
	0x00006dfc, 0x0000007f, 0xffffffff
पूर्ण;
#घोषणा BARTS_SYSLS_DISABLE_LENGTH माप(barts_sysls_disable) / (3 * माप(u32))

अटल स्थिर u32 barts_sysls_enable[] =
अणु
	0x000055e8, 0x00000001, 0xffffffff,
	0x0000d0bc, 0x00000100, 0xffffffff,
	0x000015c0, 0x000c1401, 0xffffffff,
	0x0000264c, 0x000c0400, 0xffffffff,
	0x00002648, 0x000c0400, 0xffffffff,
	0x00002650, 0x000c0400, 0xffffffff,
	0x000020b8, 0x000c0400, 0xffffffff,
	0x000020bc, 0x000c0400, 0xffffffff,
	0x000020c0, 0x000c0c80, 0xffffffff,
	0x0000f4a0, 0x000000c0, 0xffffffff,
	0x0000f4a4, 0x00680fff, 0xffffffff,
	0x000004c8, 0x00000000, 0xffffffff,
	0x000064ec, 0x00000000, 0xffffffff,
	0x00000c7c, 0x00000000, 0xffffffff,
	0x00006dfc, 0x00000000, 0xffffffff
पूर्ण;
#घोषणा BARTS_SYSLS_ENABLE_LENGTH माप(barts_sysls_enable) / (3 * माप(u32))

//********* CAICOS **************//
अटल स्थिर u32 caicos_sysls_शेष[] =
अणु
	0x000055e8, 0x00000000, 0xffffffff,
	0x0000d0bc, 0x00000000, 0xffffffff,
	0x000015c0, 0x000c1401, 0xffffffff,
	0x0000264c, 0x000c0400, 0xffffffff,
	0x00002648, 0x000c0400, 0xffffffff,
	0x00002650, 0x000c0400, 0xffffffff,
	0x000020b8, 0x000c0400, 0xffffffff,
	0x000020bc, 0x000c0400, 0xffffffff,
	0x0000f4a0, 0x000000c0, 0xffffffff,
	0x0000f4a4, 0x00680fff, 0xffffffff,
	0x000004c8, 0x00000001, 0xffffffff,
	0x000064ec, 0x00000000, 0xffffffff,
	0x00000c7c, 0x00000000, 0xffffffff,
	0x00006dfc, 0x00000000, 0xffffffff
पूर्ण;
#घोषणा CAICOS_SYSLS_DEFAULT_LENGTH माप(caicos_sysls_शेष) / (3 * माप(u32))

अटल स्थिर u32 caicos_sysls_disable[] =
अणु
	0x000055e8, 0x00000000, 0xffffffff,
	0x0000d0bc, 0x00000000, 0xffffffff,
	0x000015c0, 0x00041401, 0xffffffff,
	0x0000264c, 0x00040400, 0xffffffff,
	0x00002648, 0x00040400, 0xffffffff,
	0x00002650, 0x00040400, 0xffffffff,
	0x000020b8, 0x00040400, 0xffffffff,
	0x000020bc, 0x00040400, 0xffffffff,
	0x0000f4a0, 0x000000c0, 0xffffffff,
	0x0000f4a4, 0x00680000, 0xffffffff,
	0x000004c8, 0x00000001, 0xffffffff,
	0x000064ec, 0x00007ffd, 0xffffffff,
	0x00000c7c, 0x0000ff00, 0xffffffff,
	0x00006dfc, 0x0000007f, 0xffffffff
पूर्ण;
#घोषणा CAICOS_SYSLS_DISABLE_LENGTH माप(caicos_sysls_disable) / (3 * माप(u32))

अटल स्थिर u32 caicos_sysls_enable[] =
अणु
	0x000055e8, 0x00000001, 0xffffffff,
	0x0000d0bc, 0x00000100, 0xffffffff,
	0x000015c0, 0x000c1401, 0xffffffff,
	0x0000264c, 0x000c0400, 0xffffffff,
	0x00002648, 0x000c0400, 0xffffffff,
	0x00002650, 0x000c0400, 0xffffffff,
	0x000020b8, 0x000c0400, 0xffffffff,
	0x000020bc, 0x000c0400, 0xffffffff,
	0x0000f4a0, 0x000000c0, 0xffffffff,
	0x0000f4a4, 0x00680fff, 0xffffffff,
	0x000064ec, 0x00000000, 0xffffffff,
	0x00000c7c, 0x00000000, 0xffffffff,
	0x00006dfc, 0x00000000, 0xffffffff,
	0x000004c8, 0x00000000, 0xffffffff
पूर्ण;
#घोषणा CAICOS_SYSLS_ENABLE_LENGTH माप(caicos_sysls_enable) / (3 * माप(u32))

//********* TURKS **************//
अटल स्थिर u32 turks_sysls_शेष[] =
अणु
	0x000055e8, 0x00000000, 0xffffffff,
	0x0000d0bc, 0x00000000, 0xffffffff,
	0x000015c0, 0x000c1401, 0xffffffff,
	0x0000264c, 0x000c0400, 0xffffffff,
	0x00002648, 0x000c0400, 0xffffffff,
	0x00002650, 0x000c0400, 0xffffffff,
	0x000020b8, 0x000c0400, 0xffffffff,
	0x000020bc, 0x000c0400, 0xffffffff,
	0x000020c0, 0x000c0c80, 0xffffffff,
	0x0000f4a0, 0x000000c0, 0xffffffff,
	0x0000f4a4, 0x00680fff, 0xffffffff,
	0x000004c8, 0x00000001, 0xffffffff,
	0x000064ec, 0x00000000, 0xffffffff,
	0x00000c7c, 0x00000000, 0xffffffff,
	0x00006dfc, 0x00000000, 0xffffffff
पूर्ण;
#घोषणा TURKS_SYSLS_DEFAULT_LENGTH माप(turks_sysls_शेष) / (3 * माप(u32))

अटल स्थिर u32 turks_sysls_disable[] =
अणु
	0x000055e8, 0x00000000, 0xffffffff,
	0x0000d0bc, 0x00000000, 0xffffffff,
	0x000015c0, 0x00041401, 0xffffffff,
	0x0000264c, 0x00040400, 0xffffffff,
	0x00002648, 0x00040400, 0xffffffff,
	0x00002650, 0x00040400, 0xffffffff,
	0x000020b8, 0x00040400, 0xffffffff,
	0x000020bc, 0x00040400, 0xffffffff,
	0x000020c0, 0x00040c80, 0xffffffff,
	0x0000f4a0, 0x000000c0, 0xffffffff,
	0x0000f4a4, 0x00680000, 0xffffffff,
	0x000004c8, 0x00000001, 0xffffffff,
	0x000064ec, 0x00007ffd, 0xffffffff,
	0x00000c7c, 0x0000ff00, 0xffffffff,
	0x00006dfc, 0x0000007f, 0xffffffff
पूर्ण;
#घोषणा TURKS_SYSLS_DISABLE_LENGTH माप(turks_sysls_disable) / (3 * माप(u32))

अटल स्थिर u32 turks_sysls_enable[] =
अणु
	0x000055e8, 0x00000001, 0xffffffff,
	0x0000d0bc, 0x00000100, 0xffffffff,
	0x000015c0, 0x000c1401, 0xffffffff,
	0x0000264c, 0x000c0400, 0xffffffff,
	0x00002648, 0x000c0400, 0xffffffff,
	0x00002650, 0x000c0400, 0xffffffff,
	0x000020b8, 0x000c0400, 0xffffffff,
	0x000020bc, 0x000c0400, 0xffffffff,
	0x000020c0, 0x000c0c80, 0xffffffff,
	0x0000f4a0, 0x000000c0, 0xffffffff,
	0x0000f4a4, 0x00680fff, 0xffffffff,
	0x000004c8, 0x00000000, 0xffffffff,
	0x000064ec, 0x00000000, 0xffffffff,
	0x00000c7c, 0x00000000, 0xffffffff,
	0x00006dfc, 0x00000000, 0xffffffff
पूर्ण;
#घोषणा TURKS_SYSLS_ENABLE_LENGTH माप(turks_sysls_enable) / (3 * माप(u32))

#पूर्ण_अगर

u32 btc_valid_sclk[40] =
अणु
	5000,   10000,  15000,  20000,  25000,  30000,  35000,  40000,  45000,  50000,
	55000,  60000,  65000,  70000,  75000,  80000,  85000,  90000,  95000,  100000,
	105000, 110000, 11500,  120000, 125000, 130000, 135000, 140000, 145000, 150000,
	155000, 160000, 165000, 170000, 175000, 180000, 185000, 190000, 195000, 200000
पूर्ण;

अटल स्थिर काष्ठा radeon_blacklist_घड़ीs btc_blacklist_घड़ीs[] = अणु
	अणु 10000, 30000, RADEON_SCLK_UP पूर्ण,
	अणु 15000, 30000, RADEON_SCLK_UP पूर्ण,
	अणु 20000, 30000, RADEON_SCLK_UP पूर्ण,
	अणु 25000, 30000, RADEON_SCLK_UP पूर्ण
पूर्ण;

व्योम btc_get_max_घड़ी_from_voltage_dependency_table(काष्ठा radeon_घड़ी_voltage_dependency_table *table,
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

व्योम btc_apply_voltage_dependency_rules(काष्ठा radeon_घड़ी_voltage_dependency_table *table,
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

अटल u32 btc_find_valid_घड़ी(काष्ठा radeon_घड़ी_array *घड़ीs,
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

अटल u32 btc_get_valid_mclk(काष्ठा radeon_device *rdev,
			      u32 max_mclk, u32 requested_mclk)
अणु
	वापस btc_find_valid_घड़ी(&rdev->pm.dpm.dyn_state.valid_mclk_values,
				    max_mclk, requested_mclk);
पूर्ण

अटल u32 btc_get_valid_sclk(काष्ठा radeon_device *rdev,
			      u32 max_sclk, u32 requested_sclk)
अणु
	वापस btc_find_valid_घड़ी(&rdev->pm.dpm.dyn_state.valid_sclk_values,
				    max_sclk, requested_sclk);
पूर्ण

व्योम btc_skip_blacklist_घड़ीs(काष्ठा radeon_device *rdev,
			       स्थिर u32 max_sclk, स्थिर u32 max_mclk,
			       u32 *sclk, u32 *mclk)
अणु
	पूर्णांक i, num_blacklist_घड़ीs;

	अगर ((sclk == शून्य) || (mclk == शून्य))
		वापस;

	num_blacklist_घड़ीs = ARRAY_SIZE(btc_blacklist_घड़ीs);

	क्रम (i = 0; i < num_blacklist_घड़ीs; i++) अणु
		अगर ((btc_blacklist_घड़ीs[i].sclk == *sclk) &&
		    (btc_blacklist_घड़ीs[i].mclk == *mclk))
			अवरोध;
	पूर्ण

	अगर (i < num_blacklist_घड़ीs) अणु
		अगर (btc_blacklist_घड़ीs[i].action == RADEON_SCLK_UP) अणु
			*sclk = btc_get_valid_sclk(rdev, max_sclk, *sclk + 1);

			अगर (*sclk < max_sclk)
				btc_skip_blacklist_घड़ीs(rdev, max_sclk, max_mclk, sclk, mclk);
		पूर्ण
	पूर्ण
पूर्ण

व्योम btc_adjust_घड़ी_combinations(काष्ठा radeon_device *rdev,
				   स्थिर काष्ठा radeon_घड़ी_and_voltage_limits *max_limits,
				   काष्ठा rv7xx_pl *pl)
अणु

	अगर ((pl->mclk == 0) || (pl->sclk == 0))
		वापस;

	अगर (pl->mclk == pl->sclk)
		वापस;

	अगर (pl->mclk > pl->sclk) अणु
		अगर (((pl->mclk + (pl->sclk - 1)) / pl->sclk) > rdev->pm.dpm.dyn_state.mclk_sclk_ratio)
			pl->sclk = btc_get_valid_sclk(rdev,
						      max_limits->sclk,
						      (pl->mclk +
						       (rdev->pm.dpm.dyn_state.mclk_sclk_ratio - 1)) /
						      rdev->pm.dpm.dyn_state.mclk_sclk_ratio);
	पूर्ण अन्यथा अणु
		अगर ((pl->sclk - pl->mclk) > rdev->pm.dpm.dyn_state.sclk_mclk_delta)
			pl->mclk = btc_get_valid_mclk(rdev,
						      max_limits->mclk,
						      pl->sclk -
						      rdev->pm.dpm.dyn_state.sclk_mclk_delta);
	पूर्ण
पूर्ण

अटल u16 btc_find_voltage(काष्ठा atom_voltage_table *table, u16 voltage)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < table->count; i++) अणु
		अगर (voltage <= table->entries[i].value)
			वापस table->entries[i].value;
	पूर्ण

	वापस table->entries[table->count - 1].value;
पूर्ण

व्योम btc_apply_voltage_delta_rules(काष्ठा radeon_device *rdev,
				   u16 max_vddc, u16 max_vddci,
				   u16 *vddc, u16 *vddci)
अणु
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(rdev);
	u16 new_voltage;

	अगर ((0 == *vddc) || (0 == *vddci))
		वापस;

	अगर (*vddc > *vddci) अणु
		अगर ((*vddc - *vddci) > rdev->pm.dpm.dyn_state.vddc_vddci_delta) अणु
			new_voltage = btc_find_voltage(&eg_pi->vddci_voltage_table,
						       (*vddc - rdev->pm.dpm.dyn_state.vddc_vddci_delta));
			*vddci = (new_voltage < max_vddci) ? new_voltage : max_vddci;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((*vddci - *vddc) > rdev->pm.dpm.dyn_state.vddc_vddci_delta) अणु
			new_voltage = btc_find_voltage(&eg_pi->vddc_voltage_table,
						       (*vddci - rdev->pm.dpm.dyn_state.vddc_vddci_delta));
			*vddc = (new_voltage < max_vddc) ? new_voltage : max_vddc;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम btc_enable_bअगर_dynamic_pcie_gen2(काष्ठा radeon_device *rdev,
					     bool enable)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);
	u32 पंचांगp, bअगर;

	पंचांगp = RREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL);
	अगर (enable) अणु
		अगर ((पंचांगp & LC_OTHER_SIDE_EVER_SENT_GEN2) &&
		    (पंचांगp & LC_OTHER_SIDE_SUPPORTS_GEN2)) अणु
			अगर (!pi->boot_in_gen2) अणु
				bअगर = RREG32(CG_BIF_REQ_AND_RSP) & ~CG_CLIENT_REQ_MASK;
				bअगर |= CG_CLIENT_REQ(0xd);
				WREG32(CG_BIF_REQ_AND_RSP, bअगर);

				पंचांगp &= ~LC_HW_VOLTAGE_IF_CONTROL_MASK;
				पंचांगp |= LC_HW_VOLTAGE_IF_CONTROL(1);
				पंचांगp |= LC_GEN2_EN_STRAP;

				पंचांगp |= LC_CLR_FAILED_SPD_CHANGE_CNT;
				WREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL, पंचांगp);
				udelay(10);
				पंचांगp &= ~LC_CLR_FAILED_SPD_CHANGE_CNT;
				WREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL, पंचांगp);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((पंचांगp & LC_OTHER_SIDE_EVER_SENT_GEN2) ||
		    (पंचांगp & LC_OTHER_SIDE_SUPPORTS_GEN2)) अणु
			अगर (!pi->boot_in_gen2) अणु
				bअगर = RREG32(CG_BIF_REQ_AND_RSP) & ~CG_CLIENT_REQ_MASK;
				bअगर |= CG_CLIENT_REQ(0xd);
				WREG32(CG_BIF_REQ_AND_RSP, bअगर);

				पंचांगp &= ~LC_HW_VOLTAGE_IF_CONTROL_MASK;
				पंचांगp &= ~LC_GEN2_EN_STRAP;
			पूर्ण
			WREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL, पंचांगp);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम btc_enable_dynamic_pcie_gen2(काष्ठा radeon_device *rdev,
					 bool enable)
अणु
	btc_enable_bअगर_dynamic_pcie_gen2(rdev, enable);

	अगर (enable)
		WREG32_P(GENERAL_PWRMGT, ENABLE_GEN2PCIE, ~ENABLE_GEN2PCIE);
	अन्यथा
		WREG32_P(GENERAL_PWRMGT, 0, ~ENABLE_GEN2PCIE);
पूर्ण

अटल पूर्णांक btc_disable_ulv(काष्ठा radeon_device *rdev)
अणु
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(rdev);

	अगर (eg_pi->ulv.supported) अणु
		अगर (rv770_send_msg_to_smc(rdev, PPSMC_MSG_DisableULV) != PPSMC_Result_OK)
			वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक btc_populate_ulv_state(काष्ठा radeon_device *rdev,
				  RV770_SMC_STATETABLE *table)
अणु
	पूर्णांक ret = -EINVAL;
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(rdev);
	काष्ठा rv7xx_pl *ulv_pl = eg_pi->ulv.pl;

	अगर (ulv_pl->vddc) अणु
		ret = cypress_convert_घातer_level_to_smc(rdev,
							 ulv_pl,
							 &table->ULVState.levels[0],
							 PPSMC_DISPLAY_WATERMARK_LOW);
		अगर (ret == 0) अणु
			table->ULVState.levels[0].arbValue = MC_CG_ARB_FREQ_F0;
			table->ULVState.levels[0].ACIndex = 1;

			table->ULVState.levels[1] = table->ULVState.levels[0];
			table->ULVState.levels[2] = table->ULVState.levels[0];

			table->ULVState.flags |= PPSMC_SWSTATE_FLAG_DC;

			WREG32(CG_ULV_CONTROL, BTC_CGULVCONTROL_DFLT);
			WREG32(CG_ULV_PARAMETER, BTC_CGULVPARAMETER_DFLT);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक btc_populate_smc_acpi_state(काष्ठा radeon_device *rdev,
				       RV770_SMC_STATETABLE *table)
अणु
	पूर्णांक ret = cypress_populate_smc_acpi_state(rdev, table);

	अगर (ret == 0) अणु
		table->ACPIState.levels[0].ACIndex = 0;
		table->ACPIState.levels[1].ACIndex = 0;
		table->ACPIState.levels[2].ACIndex = 0;
	पूर्ण

	वापस ret;
पूर्ण

व्योम btc_program_mgcg_hw_sequence(काष्ठा radeon_device *rdev,
				  स्थिर u32 *sequence, u32 count)
अणु
	u32 i, length = count * 3;
	u32 पंचांगp;

	क्रम (i = 0; i < length; i+=3) अणु
		पंचांगp = RREG32(sequence[i]);
		पंचांगp &= ~sequence[i+2];
		पंचांगp |= sequence[i+1] & sequence[i+2];
		WREG32(sequence[i], पंचांगp);
	पूर्ण
पूर्ण

अटल व्योम btc_cg_घड़ी_gating_शेष(काष्ठा radeon_device *rdev)
अणु
	u32 count;
	स्थिर u32 *p = शून्य;

	अगर (rdev->family == CHIP_BARTS) अणु
		p = (स्थिर u32 *)&barts_cgcg_cgls_शेष;
		count = BARTS_CGCG_CGLS_DEFAULT_LENGTH;
	पूर्ण अन्यथा अगर (rdev->family == CHIP_TURKS) अणु
		p = (स्थिर u32 *)&turks_cgcg_cgls_शेष;
		count = TURKS_CGCG_CGLS_DEFAULT_LENGTH;
	पूर्ण अन्यथा अगर (rdev->family == CHIP_CAICOS) अणु
		p = (स्थिर u32 *)&caicos_cgcg_cgls_शेष;
		count = CAICOS_CGCG_CGLS_DEFAULT_LENGTH;
	पूर्ण अन्यथा
		वापस;

	btc_program_mgcg_hw_sequence(rdev, p, count);
पूर्ण

अटल व्योम btc_cg_घड़ी_gating_enable(काष्ठा radeon_device *rdev,
				       bool enable)
अणु
	u32 count;
	स्थिर u32 *p = शून्य;

	अगर (enable) अणु
		अगर (rdev->family == CHIP_BARTS) अणु
			p = (स्थिर u32 *)&barts_cgcg_cgls_enable;
			count = BARTS_CGCG_CGLS_ENABLE_LENGTH;
		पूर्ण अन्यथा अगर (rdev->family == CHIP_TURKS) अणु
			p = (स्थिर u32 *)&turks_cgcg_cgls_enable;
			count = TURKS_CGCG_CGLS_ENABLE_LENGTH;
		पूर्ण अन्यथा अगर (rdev->family == CHIP_CAICOS) अणु
			p = (स्थिर u32 *)&caicos_cgcg_cgls_enable;
			count = CAICOS_CGCG_CGLS_ENABLE_LENGTH;
		पूर्ण अन्यथा
			वापस;
	पूर्ण अन्यथा अणु
		अगर (rdev->family == CHIP_BARTS) अणु
			p = (स्थिर u32 *)&barts_cgcg_cgls_disable;
			count = BARTS_CGCG_CGLS_DISABLE_LENGTH;
		पूर्ण अन्यथा अगर (rdev->family == CHIP_TURKS) अणु
			p = (स्थिर u32 *)&turks_cgcg_cgls_disable;
			count = TURKS_CGCG_CGLS_DISABLE_LENGTH;
		पूर्ण अन्यथा अगर (rdev->family == CHIP_CAICOS) अणु
			p = (स्थिर u32 *)&caicos_cgcg_cgls_disable;
			count = CAICOS_CGCG_CGLS_DISABLE_LENGTH;
		पूर्ण अन्यथा
			वापस;
	पूर्ण

	btc_program_mgcg_hw_sequence(rdev, p, count);
पूर्ण

अटल व्योम btc_mg_घड़ी_gating_शेष(काष्ठा radeon_device *rdev)
अणु
	u32 count;
	स्थिर u32 *p = शून्य;

	अगर (rdev->family == CHIP_BARTS) अणु
		p = (स्थिर u32 *)&barts_mgcg_शेष;
		count = BARTS_MGCG_DEFAULT_LENGTH;
	पूर्ण अन्यथा अगर (rdev->family == CHIP_TURKS) अणु
		p = (स्थिर u32 *)&turks_mgcg_शेष;
		count = TURKS_MGCG_DEFAULT_LENGTH;
	पूर्ण अन्यथा अगर (rdev->family == CHIP_CAICOS) अणु
		p = (स्थिर u32 *)&caicos_mgcg_शेष;
		count = CAICOS_MGCG_DEFAULT_LENGTH;
	पूर्ण अन्यथा
		वापस;

	btc_program_mgcg_hw_sequence(rdev, p, count);
पूर्ण

अटल व्योम btc_mg_घड़ी_gating_enable(काष्ठा radeon_device *rdev,
				       bool enable)
अणु
	u32 count;
	स्थिर u32 *p = शून्य;

	अगर (enable) अणु
		अगर (rdev->family == CHIP_BARTS) अणु
			p = (स्थिर u32 *)&barts_mgcg_enable;
			count = BARTS_MGCG_ENABLE_LENGTH;
		पूर्ण अन्यथा अगर (rdev->family == CHIP_TURKS) अणु
			p = (स्थिर u32 *)&turks_mgcg_enable;
			count = TURKS_MGCG_ENABLE_LENGTH;
		पूर्ण अन्यथा अगर (rdev->family == CHIP_CAICOS) अणु
			p = (स्थिर u32 *)&caicos_mgcg_enable;
			count = CAICOS_MGCG_ENABLE_LENGTH;
		पूर्ण अन्यथा
			वापस;
	पूर्ण अन्यथा अणु
		अगर (rdev->family == CHIP_BARTS) अणु
			p = (स्थिर u32 *)&barts_mgcg_disable[0];
			count = BARTS_MGCG_DISABLE_LENGTH;
		पूर्ण अन्यथा अगर (rdev->family == CHIP_TURKS) अणु
			p = (स्थिर u32 *)&turks_mgcg_disable[0];
			count = TURKS_MGCG_DISABLE_LENGTH;
		पूर्ण अन्यथा अगर (rdev->family == CHIP_CAICOS) अणु
			p = (स्थिर u32 *)&caicos_mgcg_disable[0];
			count = CAICOS_MGCG_DISABLE_LENGTH;
		पूर्ण अन्यथा
			वापस;
	पूर्ण

	btc_program_mgcg_hw_sequence(rdev, p, count);
पूर्ण

अटल व्योम btc_ls_घड़ी_gating_शेष(काष्ठा radeon_device *rdev)
अणु
	u32 count;
	स्थिर u32 *p = शून्य;

	अगर (rdev->family == CHIP_BARTS) अणु
		p = (स्थिर u32 *)&barts_sysls_शेष;
		count = BARTS_SYSLS_DEFAULT_LENGTH;
	पूर्ण अन्यथा अगर (rdev->family == CHIP_TURKS) अणु
		p = (स्थिर u32 *)&turks_sysls_शेष;
		count = TURKS_SYSLS_DEFAULT_LENGTH;
	पूर्ण अन्यथा अगर (rdev->family == CHIP_CAICOS) अणु
		p = (स्थिर u32 *)&caicos_sysls_शेष;
		count = CAICOS_SYSLS_DEFAULT_LENGTH;
	पूर्ण अन्यथा
		वापस;

	btc_program_mgcg_hw_sequence(rdev, p, count);
पूर्ण

अटल व्योम btc_ls_घड़ी_gating_enable(काष्ठा radeon_device *rdev,
				       bool enable)
अणु
	u32 count;
	स्थिर u32 *p = शून्य;

	अगर (enable) अणु
		अगर (rdev->family == CHIP_BARTS) अणु
			p = (स्थिर u32 *)&barts_sysls_enable;
			count = BARTS_SYSLS_ENABLE_LENGTH;
		पूर्ण अन्यथा अगर (rdev->family == CHIP_TURKS) अणु
			p = (स्थिर u32 *)&turks_sysls_enable;
			count = TURKS_SYSLS_ENABLE_LENGTH;
		पूर्ण अन्यथा अगर (rdev->family == CHIP_CAICOS) अणु
			p = (स्थिर u32 *)&caicos_sysls_enable;
			count = CAICOS_SYSLS_ENABLE_LENGTH;
		पूर्ण अन्यथा
			वापस;
	पूर्ण अन्यथा अणु
		अगर (rdev->family == CHIP_BARTS) अणु
			p = (स्थिर u32 *)&barts_sysls_disable;
			count = BARTS_SYSLS_DISABLE_LENGTH;
		पूर्ण अन्यथा अगर (rdev->family == CHIP_TURKS) अणु
			p = (स्थिर u32 *)&turks_sysls_disable;
			count = TURKS_SYSLS_DISABLE_LENGTH;
		पूर्ण अन्यथा अगर (rdev->family == CHIP_CAICOS) अणु
			p = (स्थिर u32 *)&caicos_sysls_disable;
			count = CAICOS_SYSLS_DISABLE_LENGTH;
		पूर्ण अन्यथा
			वापस;
	पूर्ण

	btc_program_mgcg_hw_sequence(rdev, p, count);
पूर्ण

bool btc_dpm_enabled(काष्ठा radeon_device *rdev)
अणु
	अगर (rv770_is_smc_running(rdev))
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल पूर्णांक btc_init_smc_table(काष्ठा radeon_device *rdev,
			      काष्ठा radeon_ps *radeon_boot_state)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(rdev);
	RV770_SMC_STATETABLE *table = &pi->smc_statetable;
	पूर्णांक ret;

	स_रखो(table, 0, माप(RV770_SMC_STATETABLE));

	cypress_populate_smc_voltage_tables(rdev, table);

	चयन (rdev->pm.पूर्णांक_thermal_type) अणु
	हाल THERMAL_TYPE_EVERGREEN:
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

	अगर (rdev->pm.dpm.platक्रमm_caps & ATOM_PP_PLATFORM_CAP_HARDWAREDC)
		table->प्रणालीFlags |= PPSMC_SYSTEMFLAG_GPIO_DC;

	अगर (rdev->pm.dpm.platक्रमm_caps & ATOM_PP_PLATFORM_CAP_REGULATOR_HOT)
		table->प्रणालीFlags |= PPSMC_SYSTEMFLAG_REGULATOR_HOT;

	अगर (rdev->pm.dpm.platक्रमm_caps & ATOM_PP_PLATFORM_CAP_STEPVDDC)
		table->प्रणालीFlags |= PPSMC_SYSTEMFLAG_STEPVDDC;

	अगर (pi->mem_gddr5)
		table->प्रणालीFlags |= PPSMC_SYSTEMFLAG_GDDR5;

	ret = cypress_populate_smc_initial_state(rdev, radeon_boot_state, table);
	अगर (ret)
		वापस ret;

	अगर (eg_pi->sclk_deep_sleep)
		WREG32_P(SCLK_PSKIP_CNTL, PSKIP_ON_ALLOW_STOP_HI(32),
			 ~PSKIP_ON_ALLOW_STOP_HI_MASK);

	ret = btc_populate_smc_acpi_state(rdev, table);
	अगर (ret)
		वापस ret;

	अगर (eg_pi->ulv.supported) अणु
		ret = btc_populate_ulv_state(rdev, table);
		अगर (ret)
			eg_pi->ulv.supported = false;
	पूर्ण

	table->driverState = table->initialState;

	वापस rv770_copy_bytes_to_smc(rdev,
				       pi->state_table_start,
				       (u8 *)table,
				       माप(RV770_SMC_STATETABLE),
				       pi->sram_end);
पूर्ण

अटल व्योम btc_set_at_क्रम_uvd(काष्ठा radeon_device *rdev,
			       काष्ठा radeon_ps *radeon_new_state)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(rdev);
	पूर्णांक idx = 0;

	अगर (r600_is_uvd_state(radeon_new_state->class, radeon_new_state->class2))
		idx = 1;

	अगर ((idx == 1) && !eg_pi->smu_uvd_hs) अणु
		pi->rlp = 10;
		pi->rmp = 100;
		pi->lhp = 100;
		pi->lmp = 10;
	पूर्ण अन्यथा अणु
		pi->rlp = eg_pi->ats[idx].rlp;
		pi->rmp = eg_pi->ats[idx].rmp;
		pi->lhp = eg_pi->ats[idx].lhp;
		pi->lmp = eg_pi->ats[idx].lmp;
	पूर्ण

पूर्ण

व्योम btc_notअगरy_uvd_to_smc(काष्ठा radeon_device *rdev,
			   काष्ठा radeon_ps *radeon_new_state)
अणु
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(rdev);

	अगर (r600_is_uvd_state(radeon_new_state->class, radeon_new_state->class2)) अणु
		rv770_ग_लिखो_smc_soft_रेजिस्टर(rdev,
					      RV770_SMC_SOFT_REGISTER_uvd_enabled, 1);
		eg_pi->uvd_enabled = true;
	पूर्ण अन्यथा अणु
		rv770_ग_लिखो_smc_soft_रेजिस्टर(rdev,
					      RV770_SMC_SOFT_REGISTER_uvd_enabled, 0);
		eg_pi->uvd_enabled = false;
	पूर्ण
पूर्ण

पूर्णांक btc_reset_to_शेष(काष्ठा radeon_device *rdev)
अणु
	अगर (rv770_send_msg_to_smc(rdev, PPSMC_MSG_ResetToDefaults) != PPSMC_Result_OK)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल व्योम btc_stop_smc(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		अगर (((RREG32(LB_SYNC_RESET_SEL) & LB_SYNC_RESET_SEL_MASK) >> LB_SYNC_RESET_SEL_SHIFT) != 1)
			अवरोध;
		udelay(1);
	पूर्ण
	udelay(100);

	r7xx_stop_smc(rdev);
पूर्ण

व्योम btc_पढ़ो_arb_रेजिस्टरs(काष्ठा radeon_device *rdev)
अणु
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(rdev);
	काष्ठा evergreen_arb_रेजिस्टरs *arb_रेजिस्टरs =
		&eg_pi->bootup_arb_रेजिस्टरs;

	arb_रेजिस्टरs->mc_arb_dram_timing = RREG32(MC_ARB_DRAM_TIMING);
	arb_रेजिस्टरs->mc_arb_dram_timing2 = RREG32(MC_ARB_DRAM_TIMING2);
	arb_रेजिस्टरs->mc_arb_rfsh_rate = RREG32(MC_ARB_RFSH_RATE);
	arb_रेजिस्टरs->mc_arb_burst_समय = RREG32(MC_ARB_BURST_TIME);
पूर्ण


अटल व्योम btc_set_arb0_रेजिस्टरs(काष्ठा radeon_device *rdev,
				   काष्ठा evergreen_arb_रेजिस्टरs *arb_रेजिस्टरs)
अणु
	u32 val;

	WREG32(MC_ARB_DRAM_TIMING,  arb_रेजिस्टरs->mc_arb_dram_timing);
	WREG32(MC_ARB_DRAM_TIMING2, arb_रेजिस्टरs->mc_arb_dram_timing2);

	val = (arb_रेजिस्टरs->mc_arb_rfsh_rate & POWERMODE0_MASK) >>
		POWERMODE0_SHIFT;
	WREG32_P(MC_ARB_RFSH_RATE, POWERMODE0(val), ~POWERMODE0_MASK);

	val = (arb_रेजिस्टरs->mc_arb_burst_समय & STATE0_MASK) >>
		STATE0_SHIFT;
	WREG32_P(MC_ARB_BURST_TIME, STATE0(val), ~STATE0_MASK);
पूर्ण

अटल व्योम btc_set_boot_state_timing(काष्ठा radeon_device *rdev)
अणु
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(rdev);

	अगर (eg_pi->ulv.supported)
		btc_set_arb0_रेजिस्टरs(rdev, &eg_pi->bootup_arb_रेजिस्टरs);
पूर्ण

अटल bool btc_is_state_ulv_compatible(काष्ठा radeon_device *rdev,
					काष्ठा radeon_ps *radeon_state)
अणु
	काष्ठा rv7xx_ps *state = rv770_get_ps(radeon_state);
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(rdev);
	काष्ठा rv7xx_pl *ulv_pl = eg_pi->ulv.pl;

	अगर (state->low.mclk != ulv_pl->mclk)
		वापस false;

	अगर (state->low.vddci != ulv_pl->vddci)
		वापस false;

	/* XXX check minघड़ीs, etc. */

	वापस true;
पूर्ण


अटल पूर्णांक btc_set_ulv_dram_timing(काष्ठा radeon_device *rdev)
अणु
	u32 val;
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(rdev);
	काष्ठा rv7xx_pl *ulv_pl = eg_pi->ulv.pl;

	radeon_atom_set_engine_dram_timings(rdev,
					    ulv_pl->sclk,
					    ulv_pl->mclk);

	val = rv770_calculate_memory_refresh_rate(rdev, ulv_pl->sclk);
	WREG32_P(MC_ARB_RFSH_RATE, POWERMODE0(val), ~POWERMODE0_MASK);

	val = cypress_calculate_burst_समय(rdev, ulv_pl->sclk, ulv_pl->mclk);
	WREG32_P(MC_ARB_BURST_TIME, STATE0(val), ~STATE0_MASK);

	वापस 0;
पूर्ण

अटल पूर्णांक btc_enable_ulv(काष्ठा radeon_device *rdev)
अणु
	अगर (rv770_send_msg_to_smc(rdev, PPSMC_MSG_EnableULV) != PPSMC_Result_OK)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक btc_set_घातer_state_conditionally_enable_ulv(काष्ठा radeon_device *rdev,
							काष्ठा radeon_ps *radeon_new_state)
अणु
	पूर्णांक ret = 0;
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(rdev);

	अगर (eg_pi->ulv.supported) अणु
		अगर (btc_is_state_ulv_compatible(rdev, radeon_new_state)) अणु
			// Set ARB[0] to reflect the DRAM timing needed क्रम ULV.
			ret = btc_set_ulv_dram_timing(rdev);
			अगर (ret == 0)
				ret = btc_enable_ulv(rdev);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल bool btc_check_s0_mc_reg_index(u16 in_reg, u16 *out_reg)
अणु
	bool result = true;

	चयन (in_reg) अणु
	हाल MC_SEQ_RAS_TIMING >> 2:
		*out_reg = MC_SEQ_RAS_TIMING_LP >> 2;
		अवरोध;
	हाल MC_SEQ_CAS_TIMING >> 2:
		*out_reg = MC_SEQ_CAS_TIMING_LP >> 2;
		अवरोध;
	हाल MC_SEQ_MISC_TIMING >> 2:
		*out_reg = MC_SEQ_MISC_TIMING_LP >> 2;
		अवरोध;
	हाल MC_SEQ_MISC_TIMING2 >> 2:
		*out_reg = MC_SEQ_MISC_TIMING2_LP >> 2;
		अवरोध;
	हाल MC_SEQ_RD_CTL_D0 >> 2:
		*out_reg = MC_SEQ_RD_CTL_D0_LP >> 2;
		अवरोध;
	हाल MC_SEQ_RD_CTL_D1 >> 2:
		*out_reg = MC_SEQ_RD_CTL_D1_LP >> 2;
		अवरोध;
	हाल MC_SEQ_WR_CTL_D0 >> 2:
		*out_reg = MC_SEQ_WR_CTL_D0_LP >> 2;
		अवरोध;
	हाल MC_SEQ_WR_CTL_D1 >> 2:
		*out_reg = MC_SEQ_WR_CTL_D1_LP >> 2;
		अवरोध;
	हाल MC_PMG_CMD_EMRS >> 2:
		*out_reg = MC_SEQ_PMG_CMD_EMRS_LP >> 2;
		अवरोध;
	हाल MC_PMG_CMD_MRS >> 2:
		*out_reg = MC_SEQ_PMG_CMD_MRS_LP >> 2;
		अवरोध;
	हाल MC_PMG_CMD_MRS1 >> 2:
		*out_reg = MC_SEQ_PMG_CMD_MRS1_LP >> 2;
		अवरोध;
	शेष:
		result = false;
		अवरोध;
	पूर्ण

	वापस result;
पूर्ण

अटल व्योम btc_set_valid_flag(काष्ठा evergreen_mc_reg_table *table)
अणु
	u8 i, j;

	क्रम (i = 0; i < table->last; i++) अणु
		क्रम (j = 1; j < table->num_entries; j++) अणु
			अगर (table->mc_reg_table_entry[j-1].mc_data[i] !=
			    table->mc_reg_table_entry[j].mc_data[i]) अणु
				table->valid_flag |= (1 << i);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक btc_set_mc_special_रेजिस्टरs(काष्ठा radeon_device *rdev,
					काष्ठा evergreen_mc_reg_table *table)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);
	u8 i, j, k;
	u32 पंचांगp;

	क्रम (i = 0, j = table->last; i < table->last; i++) अणु
		चयन (table->mc_reg_address[i].s1) अणु
		हाल MC_SEQ_MISC1 >> 2:
			पंचांगp = RREG32(MC_PMG_CMD_EMRS);
			table->mc_reg_address[j].s1 = MC_PMG_CMD_EMRS >> 2;
			table->mc_reg_address[j].s0 = MC_SEQ_PMG_CMD_EMRS_LP >> 2;
			क्रम (k = 0; k < table->num_entries; k++) अणु
				table->mc_reg_table_entry[k].mc_data[j] =
					((पंचांगp & 0xffff0000)) |
					((table->mc_reg_table_entry[k].mc_data[i] & 0xffff0000) >> 16);
			पूर्ण
			j++;

			अगर (j >= SMC_EVERGREEN_MC_REGISTER_ARRAY_SIZE)
				वापस -EINVAL;

			पंचांगp = RREG32(MC_PMG_CMD_MRS);
			table->mc_reg_address[j].s1 = MC_PMG_CMD_MRS >> 2;
			table->mc_reg_address[j].s0 = MC_SEQ_PMG_CMD_MRS_LP >> 2;
			क्रम (k = 0; k < table->num_entries; k++) अणु
				table->mc_reg_table_entry[k].mc_data[j] =
					(पंचांगp & 0xffff0000) |
					(table->mc_reg_table_entry[k].mc_data[i] & 0x0000ffff);
				अगर (!pi->mem_gddr5)
					table->mc_reg_table_entry[k].mc_data[j] |= 0x100;
			पूर्ण
			j++;

			अगर (j >= SMC_EVERGREEN_MC_REGISTER_ARRAY_SIZE)
				वापस -EINVAL;
			अवरोध;
		हाल MC_SEQ_RESERVE_M >> 2:
			पंचांगp = RREG32(MC_PMG_CMD_MRS1);
			table->mc_reg_address[j].s1 = MC_PMG_CMD_MRS1 >> 2;
			table->mc_reg_address[j].s0 = MC_SEQ_PMG_CMD_MRS1_LP >> 2;
			क्रम (k = 0; k < table->num_entries; k++) अणु
				table->mc_reg_table_entry[k].mc_data[j] =
					(पंचांगp & 0xffff0000) |
					(table->mc_reg_table_entry[k].mc_data[i] & 0x0000ffff);
			पूर्ण
			j++;

			अगर (j >= SMC_EVERGREEN_MC_REGISTER_ARRAY_SIZE)
				वापस -EINVAL;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	table->last = j;

	वापस 0;
पूर्ण

अटल व्योम btc_set_s0_mc_reg_index(काष्ठा evergreen_mc_reg_table *table)
अणु
	u32 i;
	u16 address;

	क्रम (i = 0; i < table->last; i++) अणु
		table->mc_reg_address[i].s0 =
			btc_check_s0_mc_reg_index(table->mc_reg_address[i].s1, &address) ?
			address : table->mc_reg_address[i].s1;
	पूर्ण
पूर्ण

अटल पूर्णांक btc_copy_vbios_mc_reg_table(काष्ठा atom_mc_reg_table *table,
				       काष्ठा evergreen_mc_reg_table *eg_table)
अणु
	u8 i, j;

	अगर (table->last > SMC_EVERGREEN_MC_REGISTER_ARRAY_SIZE)
		वापस -EINVAL;

	अगर (table->num_entries > MAX_AC_TIMING_ENTRIES)
		वापस -EINVAL;

	क्रम (i = 0; i < table->last; i++)
		eg_table->mc_reg_address[i].s1 = table->mc_reg_address[i].s1;
	eg_table->last = table->last;

	क्रम (i = 0; i < table->num_entries; i++) अणु
		eg_table->mc_reg_table_entry[i].mclk_max =
			table->mc_reg_table_entry[i].mclk_max;
		क्रम(j = 0; j < table->last; j++)
			eg_table->mc_reg_table_entry[i].mc_data[j] =
				table->mc_reg_table_entry[i].mc_data[j];
	पूर्ण
	eg_table->num_entries = table->num_entries;

	वापस 0;
पूर्ण

अटल पूर्णांक btc_initialize_mc_reg_table(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक ret;
	काष्ठा atom_mc_reg_table *table;
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(rdev);
	काष्ठा evergreen_mc_reg_table *eg_table = &eg_pi->mc_reg_table;
	u8 module_index = rv770_get_memory_module_index(rdev);

	table = kzalloc(माप(काष्ठा atom_mc_reg_table), GFP_KERNEL);
	अगर (!table)
		वापस -ENOMEM;

	/* Program additional LP रेजिस्टरs that are no दीर्घer programmed by VBIOS */
	WREG32(MC_SEQ_RAS_TIMING_LP, RREG32(MC_SEQ_RAS_TIMING));
	WREG32(MC_SEQ_CAS_TIMING_LP, RREG32(MC_SEQ_CAS_TIMING));
	WREG32(MC_SEQ_MISC_TIMING_LP, RREG32(MC_SEQ_MISC_TIMING));
	WREG32(MC_SEQ_MISC_TIMING2_LP, RREG32(MC_SEQ_MISC_TIMING2));
	WREG32(MC_SEQ_RD_CTL_D0_LP, RREG32(MC_SEQ_RD_CTL_D0));
	WREG32(MC_SEQ_RD_CTL_D1_LP, RREG32(MC_SEQ_RD_CTL_D1));
	WREG32(MC_SEQ_WR_CTL_D0_LP, RREG32(MC_SEQ_WR_CTL_D0));
	WREG32(MC_SEQ_WR_CTL_D1_LP, RREG32(MC_SEQ_WR_CTL_D1));
	WREG32(MC_SEQ_PMG_CMD_EMRS_LP, RREG32(MC_PMG_CMD_EMRS));
	WREG32(MC_SEQ_PMG_CMD_MRS_LP, RREG32(MC_PMG_CMD_MRS));
	WREG32(MC_SEQ_PMG_CMD_MRS1_LP, RREG32(MC_PMG_CMD_MRS1));

	ret = radeon_atom_init_mc_reg_table(rdev, module_index, table);

	अगर (ret)
		जाओ init_mc_करोne;

	ret = btc_copy_vbios_mc_reg_table(table, eg_table);

	अगर (ret)
		जाओ init_mc_करोne;

	btc_set_s0_mc_reg_index(eg_table);
	ret = btc_set_mc_special_रेजिस्टरs(rdev, eg_table);

	अगर (ret)
		जाओ init_mc_करोne;

	btc_set_valid_flag(eg_table);

init_mc_करोne:
	kमुक्त(table);

	वापस ret;
पूर्ण

अटल व्योम btc_init_stutter_mode(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);
	u32 पंचांगp;

	अगर (pi->mclk_stutter_mode_threshold) अणु
		अगर (pi->mem_gddr5) अणु
			पंचांगp = RREG32(MC_PMG_AUTO_CFG);
			अगर ((0x200 & पंचांगp) == 0) अणु
				पंचांगp = (पंचांगp & 0xfffffc0b) | 0x204;
				WREG32(MC_PMG_AUTO_CFG, पंचांगp);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

bool btc_dpm_vblank_too_लघु(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);
	u32 vblank_समय = r600_dpm_get_vblank_समय(rdev);
	u32 चयन_limit = pi->mem_gddr5 ? 450 : 100;

	अगर (vblank_समय < चयन_limit)
		वापस true;
	अन्यथा
		वापस false;

पूर्ण

अटल व्योम btc_apply_state_adjust_rules(काष्ठा radeon_device *rdev,
					 काष्ठा radeon_ps *rps)
अणु
	काष्ठा rv7xx_ps *ps = rv770_get_ps(rps);
	काष्ठा radeon_घड़ी_and_voltage_limits *max_limits;
	bool disable_mclk_चयनing;
	u32 mclk, sclk;
	u16 vddc, vddci;

	अगर ((rdev->pm.dpm.new_active_crtc_count > 1) ||
	    btc_dpm_vblank_too_लघु(rdev))
		disable_mclk_चयनing = true;
	अन्यथा
		disable_mclk_चयनing = false;

	अगर (rdev->pm.dpm.ac_घातer)
		max_limits = &rdev->pm.dpm.dyn_state.max_घड़ी_voltage_on_ac;
	अन्यथा
		max_limits = &rdev->pm.dpm.dyn_state.max_घड़ी_voltage_on_dc;

	अगर (rdev->pm.dpm.ac_घातer == false) अणु
		अगर (ps->high.mclk > max_limits->mclk)
			ps->high.mclk = max_limits->mclk;
		अगर (ps->high.sclk > max_limits->sclk)
			ps->high.sclk = max_limits->sclk;
		अगर (ps->high.vddc > max_limits->vddc)
			ps->high.vddc = max_limits->vddc;
		अगर (ps->high.vddci > max_limits->vddci)
			ps->high.vddci = max_limits->vddci;

		अगर (ps->medium.mclk > max_limits->mclk)
			ps->medium.mclk = max_limits->mclk;
		अगर (ps->medium.sclk > max_limits->sclk)
			ps->medium.sclk = max_limits->sclk;
		अगर (ps->medium.vddc > max_limits->vddc)
			ps->medium.vddc = max_limits->vddc;
		अगर (ps->medium.vddci > max_limits->vddci)
			ps->medium.vddci = max_limits->vddci;

		अगर (ps->low.mclk > max_limits->mclk)
			ps->low.mclk = max_limits->mclk;
		अगर (ps->low.sclk > max_limits->sclk)
			ps->low.sclk = max_limits->sclk;
		अगर (ps->low.vddc > max_limits->vddc)
			ps->low.vddc = max_limits->vddc;
		अगर (ps->low.vddci > max_limits->vddci)
			ps->low.vddci = max_limits->vddci;
	पूर्ण

	/* XXX validate the min घड़ीs required क्रम display */

	अगर (disable_mclk_चयनing) अणु
		sclk = ps->low.sclk;
		mclk = ps->high.mclk;
		vddc = ps->low.vddc;
		vddci = ps->high.vddci;
	पूर्ण अन्यथा अणु
		sclk = ps->low.sclk;
		mclk = ps->low.mclk;
		vddc = ps->low.vddc;
		vddci = ps->low.vddci;
	पूर्ण

	/* adjusted low state */
	ps->low.sclk = sclk;
	ps->low.mclk = mclk;
	ps->low.vddc = vddc;
	ps->low.vddci = vddci;

	btc_skip_blacklist_घड़ीs(rdev, max_limits->sclk, max_limits->mclk,
				  &ps->low.sclk, &ps->low.mclk);

	/* adjusted medium, high states */
	अगर (ps->medium.sclk < ps->low.sclk)
		ps->medium.sclk = ps->low.sclk;
	अगर (ps->medium.vddc < ps->low.vddc)
		ps->medium.vddc = ps->low.vddc;
	अगर (ps->high.sclk < ps->medium.sclk)
		ps->high.sclk = ps->medium.sclk;
	अगर (ps->high.vddc < ps->medium.vddc)
		ps->high.vddc = ps->medium.vddc;

	अगर (disable_mclk_चयनing) अणु
		mclk = ps->low.mclk;
		अगर (mclk < ps->medium.mclk)
			mclk = ps->medium.mclk;
		अगर (mclk < ps->high.mclk)
			mclk = ps->high.mclk;
		ps->low.mclk = mclk;
		ps->low.vddci = vddci;
		ps->medium.mclk = mclk;
		ps->medium.vddci = vddci;
		ps->high.mclk = mclk;
		ps->high.vddci = vddci;
	पूर्ण अन्यथा अणु
		अगर (ps->medium.mclk < ps->low.mclk)
			ps->medium.mclk = ps->low.mclk;
		अगर (ps->medium.vddci < ps->low.vddci)
			ps->medium.vddci = ps->low.vddci;
		अगर (ps->high.mclk < ps->medium.mclk)
			ps->high.mclk = ps->medium.mclk;
		अगर (ps->high.vddci < ps->medium.vddci)
			ps->high.vddci = ps->medium.vddci;
	पूर्ण

	btc_skip_blacklist_घड़ीs(rdev, max_limits->sclk, max_limits->mclk,
				  &ps->medium.sclk, &ps->medium.mclk);
	btc_skip_blacklist_घड़ीs(rdev, max_limits->sclk, max_limits->mclk,
				  &ps->high.sclk, &ps->high.mclk);

	btc_adjust_घड़ी_combinations(rdev, max_limits, &ps->low);
	btc_adjust_घड़ी_combinations(rdev, max_limits, &ps->medium);
	btc_adjust_घड़ी_combinations(rdev, max_limits, &ps->high);

	btc_apply_voltage_dependency_rules(&rdev->pm.dpm.dyn_state.vddc_dependency_on_sclk,
					   ps->low.sclk, max_limits->vddc, &ps->low.vddc);
	btc_apply_voltage_dependency_rules(&rdev->pm.dpm.dyn_state.vddci_dependency_on_mclk,
					   ps->low.mclk, max_limits->vddci, &ps->low.vddci);
	btc_apply_voltage_dependency_rules(&rdev->pm.dpm.dyn_state.vddc_dependency_on_mclk,
					   ps->low.mclk, max_limits->vddc, &ps->low.vddc);
	btc_apply_voltage_dependency_rules(&rdev->pm.dpm.dyn_state.vddc_dependency_on_dispclk,
					   rdev->घड़ी.current_dispclk, max_limits->vddc, &ps->low.vddc);

	btc_apply_voltage_dependency_rules(&rdev->pm.dpm.dyn_state.vddc_dependency_on_sclk,
					   ps->medium.sclk, max_limits->vddc, &ps->medium.vddc);
	btc_apply_voltage_dependency_rules(&rdev->pm.dpm.dyn_state.vddci_dependency_on_mclk,
					   ps->medium.mclk, max_limits->vddci, &ps->medium.vddci);
	btc_apply_voltage_dependency_rules(&rdev->pm.dpm.dyn_state.vddc_dependency_on_mclk,
					   ps->medium.mclk, max_limits->vddc, &ps->medium.vddc);
	btc_apply_voltage_dependency_rules(&rdev->pm.dpm.dyn_state.vddc_dependency_on_dispclk,
					   rdev->घड़ी.current_dispclk, max_limits->vddc, &ps->medium.vddc);

	btc_apply_voltage_dependency_rules(&rdev->pm.dpm.dyn_state.vddc_dependency_on_sclk,
					   ps->high.sclk, max_limits->vddc, &ps->high.vddc);
	btc_apply_voltage_dependency_rules(&rdev->pm.dpm.dyn_state.vddci_dependency_on_mclk,
					   ps->high.mclk, max_limits->vddci, &ps->high.vddci);
	btc_apply_voltage_dependency_rules(&rdev->pm.dpm.dyn_state.vddc_dependency_on_mclk,
					   ps->high.mclk, max_limits->vddc, &ps->high.vddc);
	btc_apply_voltage_dependency_rules(&rdev->pm.dpm.dyn_state.vddc_dependency_on_dispclk,
					   rdev->घड़ी.current_dispclk, max_limits->vddc, &ps->high.vddc);

	btc_apply_voltage_delta_rules(rdev, max_limits->vddc, max_limits->vddci,
				      &ps->low.vddc, &ps->low.vddci);
	btc_apply_voltage_delta_rules(rdev, max_limits->vddc, max_limits->vddci,
				      &ps->medium.vddc, &ps->medium.vddci);
	btc_apply_voltage_delta_rules(rdev, max_limits->vddc, max_limits->vddci,
				      &ps->high.vddc, &ps->high.vddci);

	अगर ((ps->high.vddc <= rdev->pm.dpm.dyn_state.max_घड़ी_voltage_on_dc.vddc) &&
	    (ps->medium.vddc <= rdev->pm.dpm.dyn_state.max_घड़ी_voltage_on_dc.vddc) &&
	    (ps->low.vddc <= rdev->pm.dpm.dyn_state.max_घड़ी_voltage_on_dc.vddc))
		ps->dc_compatible = true;
	अन्यथा
		ps->dc_compatible = false;

	अगर (ps->low.vddc < rdev->pm.dpm.dyn_state.min_vddc_क्रम_pcie_gen2)
		ps->low.flags &= ~ATOM_PPLIB_R600_FLAGS_PCIEGEN2;
	अगर (ps->medium.vddc < rdev->pm.dpm.dyn_state.min_vddc_क्रम_pcie_gen2)
		ps->medium.flags &= ~ATOM_PPLIB_R600_FLAGS_PCIEGEN2;
	अगर (ps->high.vddc < rdev->pm.dpm.dyn_state.min_vddc_क्रम_pcie_gen2)
		ps->high.flags &= ~ATOM_PPLIB_R600_FLAGS_PCIEGEN2;
पूर्ण

अटल व्योम btc_update_current_ps(काष्ठा radeon_device *rdev,
				  काष्ठा radeon_ps *rps)
अणु
	काष्ठा rv7xx_ps *new_ps = rv770_get_ps(rps);
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(rdev);

	eg_pi->current_rps = *rps;
	eg_pi->current_ps = *new_ps;
	eg_pi->current_rps.ps_priv = &eg_pi->current_ps;
पूर्ण

अटल व्योम btc_update_requested_ps(काष्ठा radeon_device *rdev,
				    काष्ठा radeon_ps *rps)
अणु
	काष्ठा rv7xx_ps *new_ps = rv770_get_ps(rps);
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(rdev);

	eg_pi->requested_rps = *rps;
	eg_pi->requested_ps = *new_ps;
	eg_pi->requested_rps.ps_priv = &eg_pi->requested_ps;
पूर्ण

#अगर 0
व्योम btc_dpm_reset_asic(काष्ठा radeon_device *rdev)
अणु
	rv770_restrict_perक्रमmance_levels_beक्रमe_चयन(rdev);
	btc_disable_ulv(rdev);
	btc_set_boot_state_timing(rdev);
	rv770_set_boot_state(rdev);
पूर्ण
#पूर्ण_अगर

पूर्णांक btc_dpm_pre_set_घातer_state(काष्ठा radeon_device *rdev)
अणु
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(rdev);
	काष्ठा radeon_ps requested_ps = *rdev->pm.dpm.requested_ps;
	काष्ठा radeon_ps *new_ps = &requested_ps;

	btc_update_requested_ps(rdev, new_ps);

	btc_apply_state_adjust_rules(rdev, &eg_pi->requested_rps);

	वापस 0;
पूर्ण

पूर्णांक btc_dpm_set_घातer_state(काष्ठा radeon_device *rdev)
अणु
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(rdev);
	काष्ठा radeon_ps *new_ps = &eg_pi->requested_rps;
	काष्ठा radeon_ps *old_ps = &eg_pi->current_rps;
	पूर्णांक ret;

	ret = btc_disable_ulv(rdev);
	btc_set_boot_state_timing(rdev);
	ret = rv770_restrict_perक्रमmance_levels_beक्रमe_चयन(rdev);
	अगर (ret) अणु
		DRM_ERROR("rv770_restrict_performance_levels_before_switch failed\n");
		वापस ret;
	पूर्ण
	अगर (eg_pi->pcie_perक्रमmance_request)
		cypress_notअगरy_link_speed_change_beक्रमe_state_change(rdev, new_ps, old_ps);

	rv770_set_uvd_घड़ी_beक्रमe_set_eng_घड़ी(rdev, new_ps, old_ps);
	ret = rv770_halt_smc(rdev);
	अगर (ret) अणु
		DRM_ERROR("rv770_halt_smc failed\n");
		वापस ret;
	पूर्ण
	btc_set_at_क्रम_uvd(rdev, new_ps);
	अगर (eg_pi->smu_uvd_hs)
		btc_notअगरy_uvd_to_smc(rdev, new_ps);
	ret = cypress_upload_sw_state(rdev, new_ps);
	अगर (ret) अणु
		DRM_ERROR("cypress_upload_sw_state failed\n");
		वापस ret;
	पूर्ण
	अगर (eg_pi->dynamic_ac_timing) अणु
		ret = cypress_upload_mc_reg_table(rdev, new_ps);
		अगर (ret) अणु
			DRM_ERROR("cypress_upload_mc_reg_table failed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	cypress_program_memory_timing_parameters(rdev, new_ps);

	ret = rv770_resume_smc(rdev);
	अगर (ret) अणु
		DRM_ERROR("rv770_resume_smc failed\n");
		वापस ret;
	पूर्ण
	ret = rv770_set_sw_state(rdev);
	अगर (ret) अणु
		DRM_ERROR("rv770_set_sw_state failed\n");
		वापस ret;
	पूर्ण
	rv770_set_uvd_घड़ी_after_set_eng_घड़ी(rdev, new_ps, old_ps);

	अगर (eg_pi->pcie_perक्रमmance_request)
		cypress_notअगरy_link_speed_change_after_state_change(rdev, new_ps, old_ps);

	ret = btc_set_घातer_state_conditionally_enable_ulv(rdev, new_ps);
	अगर (ret) अणु
		DRM_ERROR("btc_set_power_state_conditionally_enable_ulv failed\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

व्योम btc_dpm_post_set_घातer_state(काष्ठा radeon_device *rdev)
अणु
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(rdev);
	काष्ठा radeon_ps *new_ps = &eg_pi->requested_rps;

	btc_update_current_ps(rdev, new_ps);
पूर्ण

पूर्णांक btc_dpm_enable(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(rdev);
	काष्ठा radeon_ps *boot_ps = rdev->pm.dpm.boot_ps;
	पूर्णांक ret;

	अगर (pi->gfx_घड़ी_gating)
		btc_cg_घड़ी_gating_शेष(rdev);

	अगर (btc_dpm_enabled(rdev))
		वापस -EINVAL;

	अगर (pi->mg_घड़ी_gating)
		btc_mg_घड़ी_gating_शेष(rdev);

	अगर (eg_pi->ls_घड़ी_gating)
		btc_ls_घड़ी_gating_शेष(rdev);

	अगर (pi->voltage_control) अणु
		rv770_enable_voltage_control(rdev, true);
		ret = cypress_स्थिरruct_voltage_tables(rdev);
		अगर (ret) अणु
			DRM_ERROR("cypress_construct_voltage_tables failed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (pi->mvdd_control) अणु
		ret = cypress_get_mvdd_configuration(rdev);
		अगर (ret) अणु
			DRM_ERROR("cypress_get_mvdd_configuration failed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (eg_pi->dynamic_ac_timing) अणु
		ret = btc_initialize_mc_reg_table(rdev);
		अगर (ret)
			eg_pi->dynamic_ac_timing = false;
	पूर्ण

	अगर (rdev->pm.dpm.platक्रमm_caps & ATOM_PP_PLATFORM_CAP_BACKBIAS)
		rv770_enable_backbias(rdev, true);

	अगर (pi->dynamic_ss)
		cypress_enable_spपढ़ो_spectrum(rdev, true);

	अगर (pi->thermal_protection)
		rv770_enable_thermal_protection(rdev, true);

	rv770_setup_bsp(rdev);
	rv770_program_git(rdev);
	rv770_program_tp(rdev);
	rv770_program_tpp(rdev);
	rv770_program_sstp(rdev);
	rv770_program_engine_speed_parameters(rdev);
	cypress_enable_display_gap(rdev);
	rv770_program_vc(rdev);

	अगर (pi->dynamic_pcie_gen2)
		btc_enable_dynamic_pcie_gen2(rdev, true);

	ret = rv770_upload_firmware(rdev);
	अगर (ret) अणु
		DRM_ERROR("rv770_upload_firmware failed\n");
		वापस ret;
	पूर्ण
	ret = cypress_get_table_locations(rdev);
	अगर (ret) अणु
		DRM_ERROR("cypress_get_table_locations failed\n");
		वापस ret;
	पूर्ण
	ret = btc_init_smc_table(rdev, boot_ps);
	अगर (ret)
		वापस ret;

	अगर (eg_pi->dynamic_ac_timing) अणु
		ret = cypress_populate_mc_reg_table(rdev, boot_ps);
		अगर (ret) अणु
			DRM_ERROR("cypress_populate_mc_reg_table failed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	cypress_program_response_बार(rdev);
	r7xx_start_smc(rdev);
	ret = cypress_notअगरy_smc_display_change(rdev, false);
	अगर (ret) अणु
		DRM_ERROR("cypress_notify_smc_display_change failed\n");
		वापस ret;
	पूर्ण
	cypress_enable_sclk_control(rdev, true);

	अगर (eg_pi->memory_transition)
		cypress_enable_mclk_control(rdev, true);

	cypress_start_dpm(rdev);

	अगर (pi->gfx_घड़ी_gating)
		btc_cg_घड़ी_gating_enable(rdev, true);

	अगर (pi->mg_घड़ी_gating)
		btc_mg_घड़ी_gating_enable(rdev, true);

	अगर (eg_pi->ls_घड़ी_gating)
		btc_ls_घड़ी_gating_enable(rdev, true);

	rv770_enable_स्वतः_throttle_source(rdev, RADEON_DPM_AUTO_THROTTLE_SRC_THERMAL, true);

	btc_init_stutter_mode(rdev);

	btc_update_current_ps(rdev, rdev->pm.dpm.boot_ps);

	वापस 0;
पूर्ण;

व्योम btc_dpm_disable(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(rdev);

	अगर (!btc_dpm_enabled(rdev))
		वापस;

	rv770_clear_vc(rdev);

	अगर (pi->thermal_protection)
		rv770_enable_thermal_protection(rdev, false);

	अगर (pi->dynamic_pcie_gen2)
		btc_enable_dynamic_pcie_gen2(rdev, false);

	अगर (rdev->irq.installed &&
	    r600_is_पूर्णांकernal_thermal_sensor(rdev->pm.पूर्णांक_thermal_type)) अणु
		rdev->irq.dpm_thermal = false;
		radeon_irq_set(rdev);
	पूर्ण

	अगर (pi->gfx_घड़ी_gating)
		btc_cg_घड़ी_gating_enable(rdev, false);

	अगर (pi->mg_घड़ी_gating)
		btc_mg_घड़ी_gating_enable(rdev, false);

	अगर (eg_pi->ls_घड़ी_gating)
		btc_ls_घड़ी_gating_enable(rdev, false);

	rv770_stop_dpm(rdev);
	btc_reset_to_शेष(rdev);
	btc_stop_smc(rdev);
	cypress_enable_spपढ़ो_spectrum(rdev, false);

	btc_update_current_ps(rdev, rdev->pm.dpm.boot_ps);
पूर्ण

व्योम btc_dpm_setup_asic(काष्ठा radeon_device *rdev)
अणु
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(rdev);
	पूर्णांक r;

	r = ni_mc_load_microcode(rdev);
	अगर (r)
		DRM_ERROR("Failed to load MC firmware!\n");
	rv770_get_memory_type(rdev);
	rv740_पढ़ो_घड़ी_रेजिस्टरs(rdev);
	btc_पढ़ो_arb_रेजिस्टरs(rdev);
	rv770_पढ़ो_voltage_smio_रेजिस्टरs(rdev);

	अगर (eg_pi->pcie_perक्रमmance_request)
		cypress_advertise_gen2_capability(rdev);

	rv770_get_pcie_gen2_status(rdev);
	rv770_enable_acpi_pm(rdev);
पूर्ण

पूर्णांक btc_dpm_init(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv7xx_घातer_info *pi;
	काष्ठा evergreen_घातer_info *eg_pi;
	काष्ठा atom_घड़ी_भागiders भागiders;
	पूर्णांक ret;

	eg_pi = kzalloc(माप(काष्ठा evergreen_घातer_info), GFP_KERNEL);
	अगर (eg_pi == शून्य)
		वापस -ENOMEM;
	rdev->pm.dpm.priv = eg_pi;
	pi = &eg_pi->rv7xx;

	rv770_get_max_vddc(rdev);

	eg_pi->ulv.supported = false;
	pi->acpi_vddc = 0;
	eg_pi->acpi_vddci = 0;
	pi->min_vddc_in_table = 0;
	pi->max_vddc_in_table = 0;

	ret = r600_get_platक्रमm_caps(rdev);
	अगर (ret)
		वापस ret;

	ret = rv7xx_parse_घातer_table(rdev);
	अगर (ret)
		वापस ret;
	ret = r600_parse_extended_घातer_table(rdev);
	अगर (ret)
		वापस ret;

	rdev->pm.dpm.dyn_state.vddc_dependency_on_dispclk.entries =
		kसुस्मृति(4,
			माप(काष्ठा radeon_घड़ी_voltage_dependency_entry),
			GFP_KERNEL);
	अगर (!rdev->pm.dpm.dyn_state.vddc_dependency_on_dispclk.entries) अणु
		r600_मुक्त_extended_घातer_table(rdev);
		वापस -ENOMEM;
	पूर्ण
	rdev->pm.dpm.dyn_state.vddc_dependency_on_dispclk.count = 4;
	rdev->pm.dpm.dyn_state.vddc_dependency_on_dispclk.entries[0].clk = 0;
	rdev->pm.dpm.dyn_state.vddc_dependency_on_dispclk.entries[0].v = 0;
	rdev->pm.dpm.dyn_state.vddc_dependency_on_dispclk.entries[1].clk = 36000;
	rdev->pm.dpm.dyn_state.vddc_dependency_on_dispclk.entries[1].v = 800;
	rdev->pm.dpm.dyn_state.vddc_dependency_on_dispclk.entries[2].clk = 54000;
	rdev->pm.dpm.dyn_state.vddc_dependency_on_dispclk.entries[2].v = 800;
	rdev->pm.dpm.dyn_state.vddc_dependency_on_dispclk.entries[3].clk = 72000;
	rdev->pm.dpm.dyn_state.vddc_dependency_on_dispclk.entries[3].v = 800;

	अगर (rdev->pm.dpm.voltage_response_समय == 0)
		rdev->pm.dpm.voltage_response_समय = R600_VOLTAGERESPONSETIME_DFLT;
	अगर (rdev->pm.dpm.backbias_response_समय == 0)
		rdev->pm.dpm.backbias_response_समय = R600_BACKBIASRESPONSETIME_DFLT;

	ret = radeon_atom_get_घड़ी_भागiders(rdev, COMPUTE_ENGINE_PLL_PARAM,
					     0, false, &भागiders);
	अगर (ret)
		pi->ref_भाग = भागiders.ref_भाग + 1;
	अन्यथा
		pi->ref_भाग = R600_REFERENCEDIVIDER_DFLT;

	pi->mclk_strobe_mode_threshold = 40000;
	pi->mclk_edc_enable_threshold = 40000;
	eg_pi->mclk_edc_wr_enable_threshold = 40000;

	pi->rlp = RV770_RLP_DFLT;
	pi->rmp = RV770_RMP_DFLT;
	pi->lhp = RV770_LHP_DFLT;
	pi->lmp = RV770_LMP_DFLT;

	eg_pi->ats[0].rlp = RV770_RLP_DFLT;
	eg_pi->ats[0].rmp = RV770_RMP_DFLT;
	eg_pi->ats[0].lhp = RV770_LHP_DFLT;
	eg_pi->ats[0].lmp = RV770_LMP_DFLT;

	eg_pi->ats[1].rlp = BTC_RLP_UVD_DFLT;
	eg_pi->ats[1].rmp = BTC_RMP_UVD_DFLT;
	eg_pi->ats[1].lhp = BTC_LHP_UVD_DFLT;
	eg_pi->ats[1].lmp = BTC_LMP_UVD_DFLT;

	eg_pi->smu_uvd_hs = true;

	pi->voltage_control =
		radeon_atom_is_voltage_gpio(rdev, SET_VOLTAGE_TYPE_ASIC_VDDC, 0);

	pi->mvdd_control =
		radeon_atom_is_voltage_gpio(rdev, SET_VOLTAGE_TYPE_ASIC_MVDDC, 0);

	eg_pi->vddci_control =
		radeon_atom_is_voltage_gpio(rdev, SET_VOLTAGE_TYPE_ASIC_VDDCI, 0);

	rv770_get_engine_memory_ss(rdev);

	pi->asi = RV770_ASI_DFLT;
	pi->pasi = CYPRESS_HASI_DFLT;
	pi->vrc = CYPRESS_VRC_DFLT;

	pi->घातer_gating = false;

	pi->gfx_घड़ी_gating = true;

	pi->mg_घड़ी_gating = true;
	pi->mgcgtssm = true;
	eg_pi->ls_घड़ी_gating = false;
	eg_pi->sclk_deep_sleep = false;

	pi->dynamic_pcie_gen2 = true;

	अगर (rdev->pm.पूर्णांक_thermal_type != THERMAL_TYPE_NONE)
		pi->thermal_protection = true;
	अन्यथा
		pi->thermal_protection = false;

	pi->display_gap = true;

	अगर (rdev->flags & RADEON_IS_MOBILITY)
		pi->dcodt = true;
	अन्यथा
		pi->dcodt = false;

	pi->ulps = true;

	eg_pi->dynamic_ac_timing = true;
	eg_pi->abm = true;
	eg_pi->mcls = true;
	eg_pi->light_sleep = true;
	eg_pi->memory_transition = true;
#अगर defined(CONFIG_ACPI)
	eg_pi->pcie_perक्रमmance_request =
		radeon_acpi_is_pcie_perक्रमmance_request_supported(rdev);
#अन्यथा
	eg_pi->pcie_perक्रमmance_request = false;
#पूर्ण_अगर

	अगर (rdev->family == CHIP_BARTS)
		eg_pi->dll_शेष_on = true;
	अन्यथा
		eg_pi->dll_शेष_on = false;

	eg_pi->sclk_deep_sleep = false;
	अगर (ASIC_IS_LOMBOK(rdev))
		pi->mclk_stutter_mode_threshold = 30000;
	अन्यथा
		pi->mclk_stutter_mode_threshold = 0;

	pi->sram_end = SMC_RAM_END;

	rdev->pm.dpm.dyn_state.mclk_sclk_ratio = 4;
	rdev->pm.dpm.dyn_state.vddc_vddci_delta = 200;
	rdev->pm.dpm.dyn_state.min_vddc_क्रम_pcie_gen2 = 900;
	rdev->pm.dpm.dyn_state.valid_sclk_values.count = ARRAY_SIZE(btc_valid_sclk);
	rdev->pm.dpm.dyn_state.valid_sclk_values.values = btc_valid_sclk;
	rdev->pm.dpm.dyn_state.valid_mclk_values.count = 0;
	rdev->pm.dpm.dyn_state.valid_mclk_values.values = शून्य;

	अगर (rdev->family == CHIP_TURKS)
		rdev->pm.dpm.dyn_state.sclk_mclk_delta = 15000;
	अन्यथा
		rdev->pm.dpm.dyn_state.sclk_mclk_delta = 10000;

	/* make sure dc limits are valid */
	अगर ((rdev->pm.dpm.dyn_state.max_घड़ी_voltage_on_dc.sclk == 0) ||
	    (rdev->pm.dpm.dyn_state.max_घड़ी_voltage_on_dc.mclk == 0))
		rdev->pm.dpm.dyn_state.max_घड़ी_voltage_on_dc =
			rdev->pm.dpm.dyn_state.max_घड़ी_voltage_on_ac;

	वापस 0;
पूर्ण

व्योम btc_dpm_fini(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < rdev->pm.dpm.num_ps; i++) अणु
		kमुक्त(rdev->pm.dpm.ps[i].ps_priv);
	पूर्ण
	kमुक्त(rdev->pm.dpm.ps);
	kमुक्त(rdev->pm.dpm.priv);
	kमुक्त(rdev->pm.dpm.dyn_state.vddc_dependency_on_dispclk.entries);
	r600_मुक्त_extended_घातer_table(rdev);
पूर्ण

व्योम btc_dpm_debugfs_prपूर्णांक_current_perक्रमmance_level(काष्ठा radeon_device *rdev,
						     काष्ठा seq_file *m)
अणु
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(rdev);
	काष्ठा radeon_ps *rps = &eg_pi->current_rps;
	काष्ठा rv7xx_ps *ps = rv770_get_ps(rps);
	काष्ठा rv7xx_pl *pl;
	u32 current_index =
		(RREG32(TARGET_AND_CURRENT_PROखाता_INDEX) & CURRENT_PROखाता_INDEX_MASK) >>
		CURRENT_PROखाता_INDEX_SHIFT;

	अगर (current_index > 2) अणु
		seq_म_लिखो(m, "invalid dpm profile %d\n", current_index);
	पूर्ण अन्यथा अणु
		अगर (current_index == 0)
			pl = &ps->low;
		अन्यथा अगर (current_index == 1)
			pl = &ps->medium;
		अन्यथा /* current_index == 2 */
			pl = &ps->high;
		seq_म_लिखो(m, "uvd    vclk: %d dclk: %d\n", rps->vclk, rps->dclk);
		seq_म_लिखो(m, "power level %d    sclk: %u mclk: %u vddc: %u vddci: %u\n",
			   current_index, pl->sclk, pl->mclk, pl->vddc, pl->vddci);
	पूर्ण
पूर्ण

u32 btc_dpm_get_current_sclk(काष्ठा radeon_device *rdev)
अणु
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(rdev);
	काष्ठा radeon_ps *rps = &eg_pi->current_rps;
	काष्ठा rv7xx_ps *ps = rv770_get_ps(rps);
	काष्ठा rv7xx_pl *pl;
	u32 current_index =
		(RREG32(TARGET_AND_CURRENT_PROखाता_INDEX) & CURRENT_PROखाता_INDEX_MASK) >>
		CURRENT_PROखाता_INDEX_SHIFT;

	अगर (current_index > 2) अणु
		वापस 0;
	पूर्ण अन्यथा अणु
		अगर (current_index == 0)
			pl = &ps->low;
		अन्यथा अगर (current_index == 1)
			pl = &ps->medium;
		अन्यथा /* current_index == 2 */
			pl = &ps->high;
		वापस pl->sclk;
	पूर्ण
पूर्ण

u32 btc_dpm_get_current_mclk(काष्ठा radeon_device *rdev)
अणु
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(rdev);
	काष्ठा radeon_ps *rps = &eg_pi->current_rps;
	काष्ठा rv7xx_ps *ps = rv770_get_ps(rps);
	काष्ठा rv7xx_pl *pl;
	u32 current_index =
		(RREG32(TARGET_AND_CURRENT_PROखाता_INDEX) & CURRENT_PROखाता_INDEX_MASK) >>
		CURRENT_PROखाता_INDEX_SHIFT;

	अगर (current_index > 2) अणु
		वापस 0;
	पूर्ण अन्यथा अणु
		अगर (current_index == 0)
			pl = &ps->low;
		अन्यथा अगर (current_index == 1)
			pl = &ps->medium;
		अन्यथा /* current_index == 2 */
			pl = &ps->high;
		वापस pl->mclk;
	पूर्ण
पूर्ण

u32 btc_dpm_get_sclk(काष्ठा radeon_device *rdev, bool low)
अणु
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(rdev);
	काष्ठा rv7xx_ps *requested_state = rv770_get_ps(&eg_pi->requested_rps);

	अगर (low)
		वापस requested_state->low.sclk;
	अन्यथा
		वापस requested_state->high.sclk;
पूर्ण

u32 btc_dpm_get_mclk(काष्ठा radeon_device *rdev, bool low)
अणु
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(rdev);
	काष्ठा rv7xx_ps *requested_state = rv770_get_ps(&eg_pi->requested_rps);

	अगर (low)
		वापस requested_state->low.mclk;
	अन्यथा
		वापस requested_state->high.mclk;
पूर्ण
