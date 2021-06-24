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

#अगर_अघोषित SMU8_FUSION_H
#घोषणा SMU8_FUSION_H

#समावेश "smu8.h"

#आशय pack(push, 1)

#घोषणा SMU8_MAX_CUS 2
#घोषणा SMU8_PSMS_PER_CU 4
#घोषणा SMU8_CACS_PER_CU 4

काष्ठा SMU8_GfxCuPgScoreboard अणु
    uपूर्णांक8_t Enabled;
    uपूर्णांक8_t spare[3];
पूर्ण;

काष्ठा SMU8_Port80MonitorTable अणु
	uपूर्णांक32_t MmioAddress;
	uपूर्णांक32_t MemoryBaseHi;
	uपूर्णांक32_t MemoryBaseLo;
	uपूर्णांक16_t MemoryBufferSize;
	uपूर्णांक16_t MemoryPosition;
	uपूर्णांक16_t PollingInterval;
	uपूर्णांक8_t  EnableCsrShaकरोw;
	uपूर्णांक8_t  EnableDramShaकरोw;
पूर्ण;

/*  Display specअगरic घातer management parameters */
#घोषणा PWRMGT_SEPARATION_TIME_SHIFT            0
#घोषणा PWRMGT_SEPARATION_TIME_MASK             0xFFFF
#घोषणा PWRMGT_DISABLE_CPU_CSTATES_SHIFT        16
#घोषणा PWRMGT_DISABLE_CPU_CSTATES_MASK         0x1
#घोषणा PWRMGT_DISABLE_CPU_PSTATES_SHIFT        24
#घोषणा PWRMGT_DISABLE_CPU_PSTATES_MASK         0x1

/* Clock Table Definitions */
#घोषणा NUM_SCLK_LEVELS     8
#घोषणा NUM_LCLK_LEVELS     8
#घोषणा NUM_UVD_LEVELS      8
#घोषणा NUM_ECLK_LEVELS     8
#घोषणा NUM_ACLK_LEVELS     8

काष्ठा SMU8_Fusion_ClkLevel अणु
	uपूर्णांक8_t		GnbVid;
	uपूर्णांक8_t		GfxVid;
	uपूर्णांक8_t		DfsDid;
	uपूर्णांक8_t		DeepSleepDid;
	uपूर्णांक32_t	DfsBypass;
	uपूर्णांक32_t	Frequency;
पूर्ण;

काष्ठा SMU8_Fusion_SclkBreakकरोwnTable अणु
	काष्ठा SMU8_Fusion_ClkLevel ClkLevel[NUM_SCLK_LEVELS];
	काष्ठा SMU8_Fusion_ClkLevel DpmOffLevel;
	/* SMU8_Fusion_ClkLevel PwrOffLevel; */
	uपूर्णांक32_t    SclkValidMask;
	uपूर्णांक32_t    MaxSclkIndex;
पूर्ण;

काष्ठा SMU8_Fusion_LclkBreakकरोwnTable अणु
	काष्ठा SMU8_Fusion_ClkLevel ClkLevel[NUM_LCLK_LEVELS];
	काष्ठा SMU8_Fusion_ClkLevel DpmOffLevel;
    /* SMU8_Fusion_ClkLevel PwrOffLevel; */
	uपूर्णांक32_t    LclkValidMask;
	uपूर्णांक32_t    MaxLclkIndex;
पूर्ण;

काष्ठा SMU8_Fusion_EclkBreakकरोwnTable अणु
	काष्ठा SMU8_Fusion_ClkLevel ClkLevel[NUM_ECLK_LEVELS];
	काष्ठा SMU8_Fusion_ClkLevel DpmOffLevel;
	काष्ठा SMU8_Fusion_ClkLevel PwrOffLevel;
	uपूर्णांक32_t    EclkValidMask;
	uपूर्णांक32_t    MaxEclkIndex;
पूर्ण;

काष्ठा SMU8_Fusion_VclkBreakकरोwnTable अणु
	काष्ठा SMU8_Fusion_ClkLevel ClkLevel[NUM_UVD_LEVELS];
	काष्ठा SMU8_Fusion_ClkLevel DpmOffLevel;
	काष्ठा SMU8_Fusion_ClkLevel PwrOffLevel;
	uपूर्णांक32_t    VclkValidMask;
	uपूर्णांक32_t    MaxVclkIndex;
पूर्ण;

काष्ठा SMU8_Fusion_DclkBreakकरोwnTable अणु
	काष्ठा SMU8_Fusion_ClkLevel ClkLevel[NUM_UVD_LEVELS];
	काष्ठा SMU8_Fusion_ClkLevel DpmOffLevel;
	काष्ठा SMU8_Fusion_ClkLevel PwrOffLevel;
	uपूर्णांक32_t    DclkValidMask;
	uपूर्णांक32_t    MaxDclkIndex;
पूर्ण;

काष्ठा SMU8_Fusion_AclkBreakकरोwnTable अणु
	काष्ठा SMU8_Fusion_ClkLevel ClkLevel[NUM_ACLK_LEVELS];
	काष्ठा SMU8_Fusion_ClkLevel DpmOffLevel;
	काष्ठा SMU8_Fusion_ClkLevel PwrOffLevel;
	uपूर्णांक32_t    AclkValidMask;
	uपूर्णांक32_t    MaxAclkIndex;
पूर्ण;


काष्ठा SMU8_Fusion_ClkTable अणु
	काष्ठा SMU8_Fusion_SclkBreakकरोwnTable SclkBreakकरोwnTable;
	काष्ठा SMU8_Fusion_LclkBreakकरोwnTable LclkBreakकरोwnTable;
	काष्ठा SMU8_Fusion_EclkBreakकरोwnTable EclkBreakकरोwnTable;
	काष्ठा SMU8_Fusion_VclkBreakकरोwnTable VclkBreakकरोwnTable;
	काष्ठा SMU8_Fusion_DclkBreakकरोwnTable DclkBreakकरोwnTable;
	काष्ठा SMU8_Fusion_AclkBreakकरोwnTable AclkBreakकरोwnTable;
पूर्ण;

#आशय pack(pop)

#पूर्ण_अगर
