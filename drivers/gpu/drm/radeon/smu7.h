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

#अगर_अघोषित SMU7_H
#घोषणा SMU7_H

#आशय pack(push, 1)

#घोषणा SMU7_CONTEXT_ID_SMC        1
#घोषणा SMU7_CONTEXT_ID_VBIOS      2


#घोषणा SMU7_CONTEXT_ID_SMC        1
#घोषणा SMU7_CONTEXT_ID_VBIOS      2

#घोषणा SMU7_MAX_LEVELS_VDDC            8
#घोषणा SMU7_MAX_LEVELS_VDDCI           4
#घोषणा SMU7_MAX_LEVELS_MVDD            4
#घोषणा SMU7_MAX_LEVELS_VDDNB           8

#घोषणा SMU7_MAX_LEVELS_GRAPHICS        SMU__NUM_SCLK_DPM_STATE   // SCLK + SQ DPM + ULV
#घोषणा SMU7_MAX_LEVELS_MEMORY          SMU__NUM_MCLK_DPM_LEVELS   // MCLK Levels DPM
#घोषणा SMU7_MAX_LEVELS_GIO             SMU__NUM_LCLK_DPM_LEVELS  // LCLK Levels
#घोषणा SMU7_MAX_LEVELS_LINK            SMU__NUM_PCIE_DPM_LEVELS  // PCIe speed and number of lanes.
#घोषणा SMU7_MAX_LEVELS_UVD             8   // VCLK/DCLK levels क्रम UVD.
#घोषणा SMU7_MAX_LEVELS_VCE             8   // ECLK levels क्रम VCE.
#घोषणा SMU7_MAX_LEVELS_ACP             8   // ACLK levels क्रम ACP.
#घोषणा SMU7_MAX_LEVELS_SAMU            8   // SAMCLK levels क्रम SAMU.
#घोषणा SMU7_MAX_ENTRIES_SMIO           32  // Number of entries in SMIO table.

#घोषणा DPM_NO_LIMIT 0
#घोषणा DPM_NO_UP 1
#घोषणा DPM_GO_DOWN 2
#घोषणा DPM_GO_UP 3

#घोषणा SMU7_FIRST_DPM_GRAPHICS_LEVEL    0
#घोषणा SMU7_FIRST_DPM_MEMORY_LEVEL      0

#घोषणा GPIO_CLAMP_MODE_VRHOT      1
#घोषणा GPIO_CLAMP_MODE_THERM      2
#घोषणा GPIO_CLAMP_MODE_DC         4

#घोषणा SCRATCH_B_TARG_PCIE_INDEX_SHIFT 0
#घोषणा SCRATCH_B_TARG_PCIE_INDEX_MASK  (0x7<<SCRATCH_B_TARG_PCIE_INDEX_SHIFT)
#घोषणा SCRATCH_B_CURR_PCIE_INDEX_SHIFT 3
#घोषणा SCRATCH_B_CURR_PCIE_INDEX_MASK  (0x7<<SCRATCH_B_CURR_PCIE_INDEX_SHIFT)
#घोषणा SCRATCH_B_TARG_UVD_INDEX_SHIFT  6
#घोषणा SCRATCH_B_TARG_UVD_INDEX_MASK   (0x7<<SCRATCH_B_TARG_UVD_INDEX_SHIFT)
#घोषणा SCRATCH_B_CURR_UVD_INDEX_SHIFT  9
#घोषणा SCRATCH_B_CURR_UVD_INDEX_MASK   (0x7<<SCRATCH_B_CURR_UVD_INDEX_SHIFT)
#घोषणा SCRATCH_B_TARG_VCE_INDEX_SHIFT  12
#घोषणा SCRATCH_B_TARG_VCE_INDEX_MASK   (0x7<<SCRATCH_B_TARG_VCE_INDEX_SHIFT)
#घोषणा SCRATCH_B_CURR_VCE_INDEX_SHIFT  15
#घोषणा SCRATCH_B_CURR_VCE_INDEX_MASK   (0x7<<SCRATCH_B_CURR_VCE_INDEX_SHIFT)
#घोषणा SCRATCH_B_TARG_ACP_INDEX_SHIFT  18
#घोषणा SCRATCH_B_TARG_ACP_INDEX_MASK   (0x7<<SCRATCH_B_TARG_ACP_INDEX_SHIFT)
#घोषणा SCRATCH_B_CURR_ACP_INDEX_SHIFT  21
#घोषणा SCRATCH_B_CURR_ACP_INDEX_MASK   (0x7<<SCRATCH_B_CURR_ACP_INDEX_SHIFT)
#घोषणा SCRATCH_B_TARG_SAMU_INDEX_SHIFT 24
#घोषणा SCRATCH_B_TARG_SAMU_INDEX_MASK  (0x7<<SCRATCH_B_TARG_SAMU_INDEX_SHIFT)
#घोषणा SCRATCH_B_CURR_SAMU_INDEX_SHIFT 27
#घोषणा SCRATCH_B_CURR_SAMU_INDEX_MASK  (0x7<<SCRATCH_B_CURR_SAMU_INDEX_SHIFT)


काष्ठा SMU7_PIDController
अणु
    uपूर्णांक32_t Ki;
    पूर्णांक32_t LFWindupUL;
    पूर्णांक32_t LFWindupLL;
    uपूर्णांक32_t StatePrecision;
    uपूर्णांक32_t LfPrecision;
    uपूर्णांक32_t LfOffset;
    uपूर्णांक32_t MaxState;
    uपूर्णांक32_t MaxLfFraction;
    uपूर्णांक32_t StateShअगरt;
पूर्ण;

प्रकार काष्ठा SMU7_PIDController SMU7_PIDController;

// -------------------------------------------------------------------------------------------------------------------------
#घोषणा SMU7_MAX_PCIE_LINK_SPEEDS 3 /* 0:Gen1 1:Gen2 2:Gen3 */

#घोषणा SMU7_SCLK_DPM_CONFIG_MASK                        0x01
#घोषणा SMU7_VOLTAGE_CONTROLLER_CONFIG_MASK              0x02
#घोषणा SMU7_THERMAL_CONTROLLER_CONFIG_MASK              0x04
#घोषणा SMU7_MCLK_DPM_CONFIG_MASK                        0x08
#घोषणा SMU7_UVD_DPM_CONFIG_MASK                         0x10
#घोषणा SMU7_VCE_DPM_CONFIG_MASK                         0x20
#घोषणा SMU7_ACP_DPM_CONFIG_MASK                         0x40
#घोषणा SMU7_SAMU_DPM_CONFIG_MASK                        0x80
#घोषणा SMU7_PCIEGEN_DPM_CONFIG_MASK                    0x100

#घोषणा SMU7_ACP_MCLK_HANDSHAKE_DISABLE                  0x00000001
#घोषणा SMU7_ACP_SCLK_HANDSHAKE_DISABLE                  0x00000002
#घोषणा SMU7_UVD_MCLK_HANDSHAKE_DISABLE                  0x00000100
#घोषणा SMU7_UVD_SCLK_HANDSHAKE_DISABLE                  0x00000200
#घोषणा SMU7_VCE_MCLK_HANDSHAKE_DISABLE                  0x00010000
#घोषणा SMU7_VCE_SCLK_HANDSHAKE_DISABLE                  0x00020000

काष्ठा SMU7_Firmware_Header
अणु
    uपूर्णांक32_t Digest[5];
    uपूर्णांक32_t Version;
    uपूर्णांक32_t HeaderSize;
    uपूर्णांक32_t Flags;
    uपूर्णांक32_t EntryPoपूर्णांक;
    uपूर्णांक32_t CodeSize;
    uपूर्णांक32_t ImageSize;

    uपूर्णांक32_t Rtos;
    uपूर्णांक32_t SoftRegisters;
    uपूर्णांक32_t DpmTable;
    uपूर्णांक32_t FanTable;
    uपूर्णांक32_t CacConfigTable;
    uपूर्णांक32_t CacStatusTable;

    uपूर्णांक32_t mcRegisterTable;

    uपूर्णांक32_t mcArbDramTimingTable;

    uपूर्णांक32_t PmFuseTable;
    uपूर्णांक32_t Globals;
    uपूर्णांक32_t Reserved[42];
    uपूर्णांक32_t Signature;
पूर्ण;

प्रकार काष्ठा SMU7_Firmware_Header SMU7_Firmware_Header;

#घोषणा SMU7_FIRMWARE_HEADER_LOCATION 0x20000

क्रमागत  DisplayConfig अणु
    PowerDown = 1,
    DP54x4,
    DP54x2,
    DP54x1,
    DP27x4,
    DP27x2,
    DP27x1,
    HDMI297,
    HDMI162,
    LVDS,
    DP324x4,
    DP324x2,
    DP324x1
पूर्ण;

#आशय pack(pop)

#पूर्ण_अगर

