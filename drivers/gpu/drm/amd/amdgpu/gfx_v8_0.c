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

#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/firmware.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>

#समावेश "amdgpu.h"
#समावेश "amdgpu_gfx.h"
#समावेश "amdgpu_ring.h"
#समावेश "vi.h"
#समावेश "vi_structs.h"
#समावेश "vid.h"
#समावेश "amdgpu_ucode.h"
#समावेश "amdgpu_atombios.h"
#समावेश "atombios_i2c.h"
#समावेश "clearstate_vi.h"

#समावेश "gmc/gmc_8_2_d.h"
#समावेश "gmc/gmc_8_2_sh_mask.h"

#समावेश "oss/oss_3_0_d.h"
#समावेश "oss/oss_3_0_sh_mask.h"

#समावेश "bif/bif_5_0_d.h"
#समावेश "bif/bif_5_0_sh_mask.h"
#समावेश "gca/gfx_8_0_d.h"
#समावेश "gca/gfx_8_0_enum.h"
#समावेश "gca/gfx_8_0_sh_mask.h"

#समावेश "dce/dce_10_0_d.h"
#समावेश "dce/dce_10_0_sh_mask.h"

#समावेश "smu/smu_7_1_3_d.h"

#समावेश "ivsrcid/ivsrcid_vislands30.h"

#घोषणा GFX8_NUM_GFX_RINGS     1
#घोषणा GFX8_MEC_HPD_SIZE 4096

#घोषणा TOPAZ_GB_ADDR_CONFIG_GOLDEN 0x22010001
#घोषणा CARRIZO_GB_ADDR_CONFIG_GOLDEN 0x22010001
#घोषणा POLARIS11_GB_ADDR_CONFIG_GOLDEN 0x22011002
#घोषणा TONGA_GB_ADDR_CONFIG_GOLDEN 0x22011003

#घोषणा ARRAY_MODE(x)					((x) << GB_TILE_MODE0__ARRAY_MODE__SHIFT)
#घोषणा PIPE_CONFIG(x)					((x) << GB_TILE_MODE0__PIPE_CONFIG__SHIFT)
#घोषणा TILE_SPLIT(x)					((x) << GB_TILE_MODE0__TILE_SPLIT__SHIFT)
#घोषणा MICRO_TILE_MODE_NEW(x)				((x) << GB_TILE_MODE0__MICRO_TILE_MODE_NEW__SHIFT)
#घोषणा SAMPLE_SPLIT(x)					((x) << GB_TILE_MODE0__SAMPLE_SPLIT__SHIFT)
#घोषणा BANK_WIDTH(x)					((x) << GB_MACROTILE_MODE0__BANK_WIDTH__SHIFT)
#घोषणा BANK_HEIGHT(x)					((x) << GB_MACROTILE_MODE0__BANK_HEIGHT__SHIFT)
#घोषणा MACRO_TILE_ASPECT(x)				((x) << GB_MACROTILE_MODE0__MACRO_TILE_ASPECT__SHIFT)
#घोषणा NUM_BANKS(x)					((x) << GB_MACROTILE_MODE0__NUM_BANKS__SHIFT)

#घोषणा RLC_CGTT_MGCG_OVERRIDE__CPF_MASK            0x00000001L
#घोषणा RLC_CGTT_MGCG_OVERRIDE__RLC_MASK            0x00000002L
#घोषणा RLC_CGTT_MGCG_OVERRIDE__MGCG_MASK           0x00000004L
#घोषणा RLC_CGTT_MGCG_OVERRIDE__CGCG_MASK           0x00000008L
#घोषणा RLC_CGTT_MGCG_OVERRIDE__CGLS_MASK           0x00000010L
#घोषणा RLC_CGTT_MGCG_OVERRIDE__GRBM_MASK           0x00000020L

/* BPM SERDES CMD */
#घोषणा SET_BPM_SERDES_CMD    1
#घोषणा CLE_BPM_SERDES_CMD    0

/* BPM Register Address*/
क्रमागत अणु
	BPM_REG_CGLS_EN = 0,        /* Enable/Disable CGLS */
	BPM_REG_CGLS_ON,            /* ON/OFF CGLS: shall be controlled by RLC FW */
	BPM_REG_CGCG_OVERRIDE,      /* Set/Clear CGCG Override */
	BPM_REG_MGCG_OVERRIDE,      /* Set/Clear MGCG Override */
	BPM_REG_FGCG_OVERRIDE,      /* Set/Clear FGCG Override */
	BPM_REG_FGCG_MAX
पूर्ण;

#घोषणा RLC_FormatDirectRegListLength        14

MODULE_FIRMWARE("amdgpu/carrizo_ce.bin");
MODULE_FIRMWARE("amdgpu/carrizo_pfp.bin");
MODULE_FIRMWARE("amdgpu/carrizo_me.bin");
MODULE_FIRMWARE("amdgpu/carrizo_mec.bin");
MODULE_FIRMWARE("amdgpu/carrizo_mec2.bin");
MODULE_FIRMWARE("amdgpu/carrizo_rlc.bin");

MODULE_FIRMWARE("amdgpu/stoney_ce.bin");
MODULE_FIRMWARE("amdgpu/stoney_pfp.bin");
MODULE_FIRMWARE("amdgpu/stoney_me.bin");
MODULE_FIRMWARE("amdgpu/stoney_mec.bin");
MODULE_FIRMWARE("amdgpu/stoney_rlc.bin");

MODULE_FIRMWARE("amdgpu/tonga_ce.bin");
MODULE_FIRMWARE("amdgpu/tonga_pfp.bin");
MODULE_FIRMWARE("amdgpu/tonga_me.bin");
MODULE_FIRMWARE("amdgpu/tonga_mec.bin");
MODULE_FIRMWARE("amdgpu/tonga_mec2.bin");
MODULE_FIRMWARE("amdgpu/tonga_rlc.bin");

MODULE_FIRMWARE("amdgpu/topaz_ce.bin");
MODULE_FIRMWARE("amdgpu/topaz_pfp.bin");
MODULE_FIRMWARE("amdgpu/topaz_me.bin");
MODULE_FIRMWARE("amdgpu/topaz_mec.bin");
MODULE_FIRMWARE("amdgpu/topaz_rlc.bin");

MODULE_FIRMWARE("amdgpu/fiji_ce.bin");
MODULE_FIRMWARE("amdgpu/fiji_pfp.bin");
MODULE_FIRMWARE("amdgpu/fiji_me.bin");
MODULE_FIRMWARE("amdgpu/fiji_mec.bin");
MODULE_FIRMWARE("amdgpu/fiji_mec2.bin");
MODULE_FIRMWARE("amdgpu/fiji_rlc.bin");

MODULE_FIRMWARE("amdgpu/polaris10_ce.bin");
MODULE_FIRMWARE("amdgpu/polaris10_ce_2.bin");
MODULE_FIRMWARE("amdgpu/polaris10_pfp.bin");
MODULE_FIRMWARE("amdgpu/polaris10_pfp_2.bin");
MODULE_FIRMWARE("amdgpu/polaris10_me.bin");
MODULE_FIRMWARE("amdgpu/polaris10_me_2.bin");
MODULE_FIRMWARE("amdgpu/polaris10_mec.bin");
MODULE_FIRMWARE("amdgpu/polaris10_mec_2.bin");
MODULE_FIRMWARE("amdgpu/polaris10_mec2.bin");
MODULE_FIRMWARE("amdgpu/polaris10_mec2_2.bin");
MODULE_FIRMWARE("amdgpu/polaris10_rlc.bin");

MODULE_FIRMWARE("amdgpu/polaris11_ce.bin");
MODULE_FIRMWARE("amdgpu/polaris11_ce_2.bin");
MODULE_FIRMWARE("amdgpu/polaris11_pfp.bin");
MODULE_FIRMWARE("amdgpu/polaris11_pfp_2.bin");
MODULE_FIRMWARE("amdgpu/polaris11_me.bin");
MODULE_FIRMWARE("amdgpu/polaris11_me_2.bin");
MODULE_FIRMWARE("amdgpu/polaris11_mec.bin");
MODULE_FIRMWARE("amdgpu/polaris11_mec_2.bin");
MODULE_FIRMWARE("amdgpu/polaris11_mec2.bin");
MODULE_FIRMWARE("amdgpu/polaris11_mec2_2.bin");
MODULE_FIRMWARE("amdgpu/polaris11_rlc.bin");

MODULE_FIRMWARE("amdgpu/polaris12_ce.bin");
MODULE_FIRMWARE("amdgpu/polaris12_ce_2.bin");
MODULE_FIRMWARE("amdgpu/polaris12_pfp.bin");
MODULE_FIRMWARE("amdgpu/polaris12_pfp_2.bin");
MODULE_FIRMWARE("amdgpu/polaris12_me.bin");
MODULE_FIRMWARE("amdgpu/polaris12_me_2.bin");
MODULE_FIRMWARE("amdgpu/polaris12_mec.bin");
MODULE_FIRMWARE("amdgpu/polaris12_mec_2.bin");
MODULE_FIRMWARE("amdgpu/polaris12_mec2.bin");
MODULE_FIRMWARE("amdgpu/polaris12_mec2_2.bin");
MODULE_FIRMWARE("amdgpu/polaris12_rlc.bin");

MODULE_FIRMWARE("amdgpu/vegam_ce.bin");
MODULE_FIRMWARE("amdgpu/vegam_pfp.bin");
MODULE_FIRMWARE("amdgpu/vegam_me.bin");
MODULE_FIRMWARE("amdgpu/vegam_mec.bin");
MODULE_FIRMWARE("amdgpu/vegam_mec2.bin");
MODULE_FIRMWARE("amdgpu/vegam_rlc.bin");

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

अटल स्थिर u32 golden_settings_tonga_a11[] =
अणु
	mmCB_HW_CONTROL, 0xfffdf3cf, 0x00007208,
	mmCB_HW_CONTROL_3, 0x00000040, 0x00000040,
	mmDB_DEBUG2, 0xf00fffff, 0x00000400,
	mmGB_GPU_ID, 0x0000000f, 0x00000000,
	mmPA_SC_ENHANCE, 0xffffffff, 0x20000001,
	mmPA_SC_FIFO_DEPTH_CNTL, 0x000003ff, 0x000000fc,
	mmPA_SC_LINE_STIPPLE_STATE, 0x0000ff0f, 0x00000000,
	mmRLC_CGCG_CGLS_CTRL, 0x00000003, 0x0000003c,
	mmSQ_RANDOM_WAVE_PRI, 0x001fffff, 0x000006fd,
	mmTA_CNTL_AUX, 0x000f000f, 0x000b0000,
	mmTCC_CTRL, 0x00100000, 0xf31fff7f,
	mmTCC_EXE_DISABLE, 0x00000002, 0x00000002,
	mmTCP_ADDR_CONFIG, 0x000003ff, 0x000002fb,
	mmTCP_CHAN_STEER_HI, 0xffffffff, 0x0000543b,
	mmTCP_CHAN_STEER_LO, 0xffffffff, 0xa9210876,
	mmVGT_RESET_DEBUG, 0x00000004, 0x00000004,
पूर्ण;

अटल स्थिर u32 tonga_golden_common_all[] =
अणु
	mmGRBM_GFX_INDEX, 0xffffffff, 0xe0000000,
	mmPA_SC_RASTER_CONFIG, 0xffffffff, 0x16000012,
	mmPA_SC_RASTER_CONFIG_1, 0xffffffff, 0x0000002A,
	mmGB_ADDR_CONFIG, 0xffffffff, 0x22011003,
	mmSPI_RESOURCE_RESERVE_CU_0, 0xffffffff, 0x00000800,
	mmSPI_RESOURCE_RESERVE_CU_1, 0xffffffff, 0x00000800,
	mmSPI_RESOURCE_RESERVE_EN_CU_0, 0xffffffff, 0x00FF7FBF,
	mmSPI_RESOURCE_RESERVE_EN_CU_1, 0xffffffff, 0x00FF7FAF
पूर्ण;

अटल स्थिर u32 tonga_mgcg_cgcg_init[] =
अणु
	mmRLC_CGTT_MGCG_OVERRIDE, 0xffffffff, 0xffffffff,
	mmGRBM_GFX_INDEX, 0xffffffff, 0xe0000000,
	mmCB_CGTT_SCLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_BCI_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_CP_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_CPC_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_CPF_CLK_CTRL, 0xffffffff, 0x40000100,
	mmCGTT_GDS_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_IA_CLK_CTRL, 0xffffffff, 0x06000100,
	mmCGTT_PA_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_WD_CLK_CTRL, 0xffffffff, 0x06000100,
	mmCGTT_PC_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_RLC_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_SC_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_SPI_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_SQ_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_SQG_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_SX_CLK_CTRL0, 0xffffffff, 0x00000100,
	mmCGTT_SX_CLK_CTRL1, 0xffffffff, 0x00000100,
	mmCGTT_SX_CLK_CTRL2, 0xffffffff, 0x00000100,
	mmCGTT_SX_CLK_CTRL3, 0xffffffff, 0x00000100,
	mmCGTT_SX_CLK_CTRL4, 0xffffffff, 0x00000100,
	mmCGTT_TCI_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_TCP_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_VGT_CLK_CTRL, 0xffffffff, 0x06000100,
	mmDB_CGTT_CLK_CTRL_0, 0xffffffff, 0x00000100,
	mmTA_CGTT_CTRL, 0xffffffff, 0x00000100,
	mmTCA_CGTT_SCLK_CTRL, 0xffffffff, 0x00000100,
	mmTCC_CGTT_SCLK_CTRL, 0xffffffff, 0x00000100,
	mmTD_CGTT_CTRL, 0xffffffff, 0x00000100,
	mmGRBM_GFX_INDEX, 0xffffffff, 0xe0000000,
	mmCGTS_CU0_SP0_CTRL_REG, 0xffffffff, 0x00010000,
	mmCGTS_CU0_LDS_SQ_CTRL_REG, 0xffffffff, 0x00030002,
	mmCGTS_CU0_TA_SQC_CTRL_REG, 0xffffffff, 0x00040007,
	mmCGTS_CU0_SP1_CTRL_REG, 0xffffffff, 0x00060005,
	mmCGTS_CU0_TD_TCP_CTRL_REG, 0xffffffff, 0x00090008,
	mmCGTS_CU1_SP0_CTRL_REG, 0xffffffff, 0x00010000,
	mmCGTS_CU1_LDS_SQ_CTRL_REG, 0xffffffff, 0x00030002,
	mmCGTS_CU1_TA_CTRL_REG, 0xffffffff, 0x00040007,
	mmCGTS_CU1_SP1_CTRL_REG, 0xffffffff, 0x00060005,
	mmCGTS_CU1_TD_TCP_CTRL_REG, 0xffffffff, 0x00090008,
	mmCGTS_CU2_SP0_CTRL_REG, 0xffffffff, 0x00010000,
	mmCGTS_CU2_LDS_SQ_CTRL_REG, 0xffffffff, 0x00030002,
	mmCGTS_CU2_TA_CTRL_REG, 0xffffffff, 0x00040007,
	mmCGTS_CU2_SP1_CTRL_REG, 0xffffffff, 0x00060005,
	mmCGTS_CU2_TD_TCP_CTRL_REG, 0xffffffff, 0x00090008,
	mmCGTS_CU3_SP0_CTRL_REG, 0xffffffff, 0x00010000,
	mmCGTS_CU3_LDS_SQ_CTRL_REG, 0xffffffff, 0x00030002,
	mmCGTS_CU3_TA_CTRL_REG, 0xffffffff, 0x00040007,
	mmCGTS_CU3_SP1_CTRL_REG, 0xffffffff, 0x00060005,
	mmCGTS_CU3_TD_TCP_CTRL_REG, 0xffffffff, 0x00090008,
	mmCGTS_CU4_SP0_CTRL_REG, 0xffffffff, 0x00010000,
	mmCGTS_CU4_LDS_SQ_CTRL_REG, 0xffffffff, 0x00030002,
	mmCGTS_CU4_TA_SQC_CTRL_REG, 0xffffffff, 0x00040007,
	mmCGTS_CU4_SP1_CTRL_REG, 0xffffffff, 0x00060005,
	mmCGTS_CU4_TD_TCP_CTRL_REG, 0xffffffff, 0x00090008,
	mmCGTS_CU5_SP0_CTRL_REG, 0xffffffff, 0x00010000,
	mmCGTS_CU5_LDS_SQ_CTRL_REG, 0xffffffff, 0x00030002,
	mmCGTS_CU5_TA_CTRL_REG, 0xffffffff, 0x00040007,
	mmCGTS_CU5_SP1_CTRL_REG, 0xffffffff, 0x00060005,
	mmCGTS_CU5_TD_TCP_CTRL_REG, 0xffffffff, 0x00090008,
	mmCGTS_CU6_SP0_CTRL_REG, 0xffffffff, 0x00010000,
	mmCGTS_CU6_LDS_SQ_CTRL_REG, 0xffffffff, 0x00030002,
	mmCGTS_CU6_TA_CTRL_REG, 0xffffffff, 0x00040007,
	mmCGTS_CU6_SP1_CTRL_REG, 0xffffffff, 0x00060005,
	mmCGTS_CU6_TD_TCP_CTRL_REG, 0xffffffff, 0x00090008,
	mmCGTS_CU7_SP0_CTRL_REG, 0xffffffff, 0x00010000,
	mmCGTS_CU7_LDS_SQ_CTRL_REG, 0xffffffff, 0x00030002,
	mmCGTS_CU7_TA_CTRL_REG, 0xffffffff, 0x00040007,
	mmCGTS_CU7_SP1_CTRL_REG, 0xffffffff, 0x00060005,
	mmCGTS_CU7_TD_TCP_CTRL_REG, 0xffffffff, 0x00090008,
	mmCGTS_SM_CTRL_REG, 0xffffffff, 0x96e00200,
	mmCP_RB_WPTR_POLL_CNTL, 0xffffffff, 0x00900100,
	mmRLC_CGCG_CGLS_CTRL, 0xffffffff, 0x0020003c,
	mmCP_MEM_SLP_CNTL, 0x00000001, 0x00000001,
पूर्ण;

अटल स्थिर u32 golden_settings_vegam_a11[] =
अणु
	mmCB_HW_CONTROL, 0x0001f3cf, 0x00007208,
	mmCB_HW_CONTROL_2, 0x0f000000, 0x0d000000,
	mmCB_HW_CONTROL_3, 0x000001ff, 0x00000040,
	mmDB_DEBUG2, 0xf00fffff, 0x00000400,
	mmPA_SC_ENHANCE, 0xffffffff, 0x20000001,
	mmPA_SC_LINE_STIPPLE_STATE, 0x0000ff0f, 0x00000000,
	mmPA_SC_RASTER_CONFIG, 0x3f3fffff, 0x3a00161a,
	mmPA_SC_RASTER_CONFIG_1, 0x0000003f, 0x0000002e,
	mmRLC_CGCG_CGLS_CTRL, 0x00000003, 0x0001003c,
	mmRLC_CGCG_CGLS_CTRL_3D, 0xffffffff, 0x0001003c,
	mmSQ_CONFIG, 0x07f80000, 0x01180000,
	mmTA_CNTL_AUX, 0x000f000f, 0x000b0000,
	mmTCC_CTRL, 0x00100000, 0xf31fff7f,
	mmTCP_ADDR_CONFIG, 0x000003ff, 0x000000f7,
	mmTCP_CHAN_STEER_HI, 0xffffffff, 0x00000000,
	mmTCP_CHAN_STEER_LO, 0xffffffff, 0x32761054,
	mmVGT_RESET_DEBUG, 0x00000004, 0x00000004,
पूर्ण;

अटल स्थिर u32 vegam_golden_common_all[] =
अणु
	mmGRBM_GFX_INDEX, 0xffffffff, 0xe0000000,
	mmGB_ADDR_CONFIG, 0xffffffff, 0x22011003,
	mmSPI_RESOURCE_RESERVE_CU_0, 0xffffffff, 0x00000800,
	mmSPI_RESOURCE_RESERVE_CU_1, 0xffffffff, 0x00000800,
	mmSPI_RESOURCE_RESERVE_EN_CU_0, 0xffffffff, 0x00FF7FBF,
	mmSPI_RESOURCE_RESERVE_EN_CU_1, 0xffffffff, 0x00FF7FAF,
पूर्ण;

अटल स्थिर u32 golden_settings_polaris11_a11[] =
अणु
	mmCB_HW_CONTROL, 0x0000f3cf, 0x00007208,
	mmCB_HW_CONTROL_2, 0x0f000000, 0x0f000000,
	mmCB_HW_CONTROL_3, 0x000001ff, 0x00000040,
	mmDB_DEBUG2, 0xf00fffff, 0x00000400,
	mmPA_SC_ENHANCE, 0xffffffff, 0x20000001,
	mmPA_SC_LINE_STIPPLE_STATE, 0x0000ff0f, 0x00000000,
	mmPA_SC_RASTER_CONFIG, 0x3f3fffff, 0x16000012,
	mmPA_SC_RASTER_CONFIG_1, 0x0000003f, 0x00000000,
	mmRLC_CGCG_CGLS_CTRL, 0x00000003, 0x0001003c,
	mmRLC_CGCG_CGLS_CTRL_3D, 0xffffffff, 0x0001003c,
	mmSQ_CONFIG, 0x07f80000, 0x01180000,
	mmTA_CNTL_AUX, 0x000f000f, 0x000b0000,
	mmTCC_CTRL, 0x00100000, 0xf31fff7f,
	mmTCP_ADDR_CONFIG, 0x000003ff, 0x000000f3,
	mmTCP_CHAN_STEER_HI, 0xffffffff, 0x00000000,
	mmTCP_CHAN_STEER_LO, 0xffffffff, 0x00003210,
	mmVGT_RESET_DEBUG, 0x00000004, 0x00000004,
पूर्ण;

अटल स्थिर u32 polaris11_golden_common_all[] =
अणु
	mmGRBM_GFX_INDEX, 0xffffffff, 0xe0000000,
	mmGB_ADDR_CONFIG, 0xffffffff, 0x22011002,
	mmSPI_RESOURCE_RESERVE_CU_0, 0xffffffff, 0x00000800,
	mmSPI_RESOURCE_RESERVE_CU_1, 0xffffffff, 0x00000800,
	mmSPI_RESOURCE_RESERVE_EN_CU_0, 0xffffffff, 0x00FF7FBF,
	mmSPI_RESOURCE_RESERVE_EN_CU_1, 0xffffffff, 0x00FF7FAF,
पूर्ण;

अटल स्थिर u32 golden_settings_polaris10_a11[] =
अणु
	mmATC_MISC_CG, 0x000c0fc0, 0x000c0200,
	mmCB_HW_CONTROL, 0x0001f3cf, 0x00007208,
	mmCB_HW_CONTROL_2, 0x0f000000, 0x0f000000,
	mmCB_HW_CONTROL_3, 0x000001ff, 0x00000040,
	mmDB_DEBUG2, 0xf00fffff, 0x00000400,
	mmPA_SC_ENHANCE, 0xffffffff, 0x20000001,
	mmPA_SC_LINE_STIPPLE_STATE, 0x0000ff0f, 0x00000000,
	mmPA_SC_RASTER_CONFIG, 0x3f3fffff, 0x16000012,
	mmPA_SC_RASTER_CONFIG_1, 0x0000003f, 0x0000002a,
	mmRLC_CGCG_CGLS_CTRL, 0x00000003, 0x0001003c,
	mmRLC_CGCG_CGLS_CTRL_3D, 0xffffffff, 0x0001003c,
	mmSQ_CONFIG, 0x07f80000, 0x07180000,
	mmTA_CNTL_AUX, 0x000f000f, 0x000b0000,
	mmTCC_CTRL, 0x00100000, 0xf31fff7f,
	mmTCP_ADDR_CONFIG, 0x000003ff, 0x000000f7,
	mmTCP_CHAN_STEER_HI, 0xffffffff, 0x00000000,
	mmVGT_RESET_DEBUG, 0x00000004, 0x00000004,
पूर्ण;

अटल स्थिर u32 polaris10_golden_common_all[] =
अणु
	mmGRBM_GFX_INDEX, 0xffffffff, 0xe0000000,
	mmPA_SC_RASTER_CONFIG, 0xffffffff, 0x16000012,
	mmPA_SC_RASTER_CONFIG_1, 0xffffffff, 0x0000002A,
	mmGB_ADDR_CONFIG, 0xffffffff, 0x22011003,
	mmSPI_RESOURCE_RESERVE_CU_0, 0xffffffff, 0x00000800,
	mmSPI_RESOURCE_RESERVE_CU_1, 0xffffffff, 0x00000800,
	mmSPI_RESOURCE_RESERVE_EN_CU_0, 0xffffffff, 0x00FF7FBF,
	mmSPI_RESOURCE_RESERVE_EN_CU_1, 0xffffffff, 0x00FF7FAF,
पूर्ण;

अटल स्थिर u32 fiji_golden_common_all[] =
अणु
	mmGRBM_GFX_INDEX, 0xffffffff, 0xe0000000,
	mmPA_SC_RASTER_CONFIG, 0xffffffff, 0x3a00161a,
	mmPA_SC_RASTER_CONFIG_1, 0xffffffff, 0x0000002e,
	mmGB_ADDR_CONFIG, 0xffffffff, 0x22011003,
	mmSPI_RESOURCE_RESERVE_CU_0, 0xffffffff, 0x00000800,
	mmSPI_RESOURCE_RESERVE_CU_1, 0xffffffff, 0x00000800,
	mmSPI_RESOURCE_RESERVE_EN_CU_0, 0xffffffff, 0x00FF7FBF,
	mmSPI_RESOURCE_RESERVE_EN_CU_1, 0xffffffff, 0x00FF7FAF,
	mmGRBM_GFX_INDEX, 0xffffffff, 0xe0000000,
	mmSPI_CONFIG_CNTL_1, 0x0000000f, 0x00000009,
पूर्ण;

अटल स्थिर u32 golden_settings_fiji_a10[] =
अणु
	mmCB_HW_CONTROL_3, 0x000001ff, 0x00000040,
	mmDB_DEBUG2, 0xf00fffff, 0x00000400,
	mmPA_SC_ENHANCE, 0xffffffff, 0x20000001,
	mmPA_SC_LINE_STIPPLE_STATE, 0x0000ff0f, 0x00000000,
	mmRLC_CGCG_CGLS_CTRL, 0x00000003, 0x0001003c,
	mmSQ_RANDOM_WAVE_PRI, 0x001fffff, 0x000006fd,
	mmTA_CNTL_AUX, 0x000f000f, 0x000b0000,
	mmTCC_CTRL, 0x00100000, 0xf31fff7f,
	mmTCC_EXE_DISABLE, 0x00000002, 0x00000002,
	mmTCP_ADDR_CONFIG, 0x000003ff, 0x000000ff,
	mmVGT_RESET_DEBUG, 0x00000004, 0x00000004,
पूर्ण;

अटल स्थिर u32 fiji_mgcg_cgcg_init[] =
अणु
	mmRLC_CGTT_MGCG_OVERRIDE, 0xffffffff, 0xffffffff,
	mmGRBM_GFX_INDEX, 0xffffffff, 0xe0000000,
	mmCB_CGTT_SCLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_BCI_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_CP_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_CPC_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_CPF_CLK_CTRL, 0xffffffff, 0x40000100,
	mmCGTT_GDS_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_IA_CLK_CTRL, 0xffffffff, 0x06000100,
	mmCGTT_PA_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_WD_CLK_CTRL, 0xffffffff, 0x06000100,
	mmCGTT_PC_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_RLC_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_SC_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_SPI_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_SQ_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_SQG_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_SX_CLK_CTRL0, 0xffffffff, 0x00000100,
	mmCGTT_SX_CLK_CTRL1, 0xffffffff, 0x00000100,
	mmCGTT_SX_CLK_CTRL2, 0xffffffff, 0x00000100,
	mmCGTT_SX_CLK_CTRL3, 0xffffffff, 0x00000100,
	mmCGTT_SX_CLK_CTRL4, 0xffffffff, 0x00000100,
	mmCGTT_TCI_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_TCP_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_VGT_CLK_CTRL, 0xffffffff, 0x06000100,
	mmDB_CGTT_CLK_CTRL_0, 0xffffffff, 0x00000100,
	mmTA_CGTT_CTRL, 0xffffffff, 0x00000100,
	mmTCA_CGTT_SCLK_CTRL, 0xffffffff, 0x00000100,
	mmTCC_CGTT_SCLK_CTRL, 0xffffffff, 0x00000100,
	mmTD_CGTT_CTRL, 0xffffffff, 0x00000100,
	mmGRBM_GFX_INDEX, 0xffffffff, 0xe0000000,
	mmCGTS_SM_CTRL_REG, 0xffffffff, 0x96e00200,
	mmCP_RB_WPTR_POLL_CNTL, 0xffffffff, 0x00900100,
	mmRLC_CGCG_CGLS_CTRL, 0xffffffff, 0x0020003c,
	mmCP_MEM_SLP_CNTL, 0x00000001, 0x00000001,
पूर्ण;

अटल स्थिर u32 golden_settings_iceland_a11[] =
अणु
	mmCB_HW_CONTROL_3, 0x00000040, 0x00000040,
	mmDB_DEBUG2, 0xf00fffff, 0x00000400,
	mmDB_DEBUG3, 0xc0000000, 0xc0000000,
	mmGB_GPU_ID, 0x0000000f, 0x00000000,
	mmPA_SC_ENHANCE, 0xffffffff, 0x20000001,
	mmPA_SC_LINE_STIPPLE_STATE, 0x0000ff0f, 0x00000000,
	mmPA_SC_RASTER_CONFIG, 0x3f3fffff, 0x00000002,
	mmPA_SC_RASTER_CONFIG_1, 0x0000003f, 0x00000000,
	mmRLC_CGCG_CGLS_CTRL, 0x00000003, 0x0000003c,
	mmSQ_RANDOM_WAVE_PRI, 0x001fffff, 0x000006fd,
	mmTA_CNTL_AUX, 0x000f000f, 0x000b0000,
	mmTCC_CTRL, 0x00100000, 0xf31fff7f,
	mmTCC_EXE_DISABLE, 0x00000002, 0x00000002,
	mmTCP_ADDR_CONFIG, 0x000003ff, 0x000000f1,
	mmTCP_CHAN_STEER_HI, 0xffffffff, 0x00000000,
	mmTCP_CHAN_STEER_LO, 0xffffffff, 0x00000010,
पूर्ण;

अटल स्थिर u32 iceland_golden_common_all[] =
अणु
	mmGRBM_GFX_INDEX, 0xffffffff, 0xe0000000,
	mmPA_SC_RASTER_CONFIG, 0xffffffff, 0x00000002,
	mmPA_SC_RASTER_CONFIG_1, 0xffffffff, 0x00000000,
	mmGB_ADDR_CONFIG, 0xffffffff, 0x22010001,
	mmSPI_RESOURCE_RESERVE_CU_0, 0xffffffff, 0x00000800,
	mmSPI_RESOURCE_RESERVE_CU_1, 0xffffffff, 0x00000800,
	mmSPI_RESOURCE_RESERVE_EN_CU_0, 0xffffffff, 0x00FF7FBF,
	mmSPI_RESOURCE_RESERVE_EN_CU_1, 0xffffffff, 0x00FF7FAF
पूर्ण;

अटल स्थिर u32 iceland_mgcg_cgcg_init[] =
अणु
	mmRLC_CGTT_MGCG_OVERRIDE, 0xffffffff, 0xffffffff,
	mmGRBM_GFX_INDEX, 0xffffffff, 0xe0000000,
	mmCB_CGTT_SCLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_BCI_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_CP_CLK_CTRL, 0xffffffff, 0xc0000100,
	mmCGTT_CPC_CLK_CTRL, 0xffffffff, 0xc0000100,
	mmCGTT_CPF_CLK_CTRL, 0xffffffff, 0xc0000100,
	mmCGTT_GDS_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_IA_CLK_CTRL, 0xffffffff, 0x06000100,
	mmCGTT_PA_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_WD_CLK_CTRL, 0xffffffff, 0x06000100,
	mmCGTT_PC_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_RLC_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_SC_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_SPI_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_SQ_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_SQG_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_SX_CLK_CTRL0, 0xffffffff, 0x00000100,
	mmCGTT_SX_CLK_CTRL1, 0xffffffff, 0x00000100,
	mmCGTT_SX_CLK_CTRL2, 0xffffffff, 0x00000100,
	mmCGTT_SX_CLK_CTRL3, 0xffffffff, 0x00000100,
	mmCGTT_SX_CLK_CTRL4, 0xffffffff, 0x00000100,
	mmCGTT_TCI_CLK_CTRL, 0xffffffff, 0xff000100,
	mmCGTT_TCP_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_VGT_CLK_CTRL, 0xffffffff, 0x06000100,
	mmDB_CGTT_CLK_CTRL_0, 0xffffffff, 0x00000100,
	mmTA_CGTT_CTRL, 0xffffffff, 0x00000100,
	mmTCA_CGTT_SCLK_CTRL, 0xffffffff, 0x00000100,
	mmTCC_CGTT_SCLK_CTRL, 0xffffffff, 0x00000100,
	mmTD_CGTT_CTRL, 0xffffffff, 0x00000100,
	mmGRBM_GFX_INDEX, 0xffffffff, 0xe0000000,
	mmCGTS_CU0_SP0_CTRL_REG, 0xffffffff, 0x00010000,
	mmCGTS_CU0_LDS_SQ_CTRL_REG, 0xffffffff, 0x00030002,
	mmCGTS_CU0_TA_SQC_CTRL_REG, 0xffffffff, 0x0f840f87,
	mmCGTS_CU0_SP1_CTRL_REG, 0xffffffff, 0x00060005,
	mmCGTS_CU0_TD_TCP_CTRL_REG, 0xffffffff, 0x00090008,
	mmCGTS_CU1_SP0_CTRL_REG, 0xffffffff, 0x00010000,
	mmCGTS_CU1_LDS_SQ_CTRL_REG, 0xffffffff, 0x00030002,
	mmCGTS_CU1_TA_CTRL_REG, 0xffffffff, 0x00040007,
	mmCGTS_CU1_SP1_CTRL_REG, 0xffffffff, 0x00060005,
	mmCGTS_CU1_TD_TCP_CTRL_REG, 0xffffffff, 0x00090008,
	mmCGTS_CU2_SP0_CTRL_REG, 0xffffffff, 0x00010000,
	mmCGTS_CU2_LDS_SQ_CTRL_REG, 0xffffffff, 0x00030002,
	mmCGTS_CU2_TA_CTRL_REG, 0xffffffff, 0x00040007,
	mmCGTS_CU2_SP1_CTRL_REG, 0xffffffff, 0x00060005,
	mmCGTS_CU2_TD_TCP_CTRL_REG, 0xffffffff, 0x00090008,
	mmCGTS_CU3_SP0_CTRL_REG, 0xffffffff, 0x00010000,
	mmCGTS_CU3_LDS_SQ_CTRL_REG, 0xffffffff, 0x00030002,
	mmCGTS_CU3_TA_CTRL_REG, 0xffffffff, 0x00040007,
	mmCGTS_CU3_SP1_CTRL_REG, 0xffffffff, 0x00060005,
	mmCGTS_CU3_TD_TCP_CTRL_REG, 0xffffffff, 0x00090008,
	mmCGTS_CU4_SP0_CTRL_REG, 0xffffffff, 0x00010000,
	mmCGTS_CU4_LDS_SQ_CTRL_REG, 0xffffffff, 0x00030002,
	mmCGTS_CU4_TA_SQC_CTRL_REG, 0xffffffff, 0x0f840f87,
	mmCGTS_CU4_SP1_CTRL_REG, 0xffffffff, 0x00060005,
	mmCGTS_CU4_TD_TCP_CTRL_REG, 0xffffffff, 0x00090008,
	mmCGTS_CU5_SP0_CTRL_REG, 0xffffffff, 0x00010000,
	mmCGTS_CU5_LDS_SQ_CTRL_REG, 0xffffffff, 0x00030002,
	mmCGTS_CU5_TA_CTRL_REG, 0xffffffff, 0x00040007,
	mmCGTS_CU5_SP1_CTRL_REG, 0xffffffff, 0x00060005,
	mmCGTS_CU5_TD_TCP_CTRL_REG, 0xffffffff, 0x00090008,
	mmCGTS_SM_CTRL_REG, 0xffffffff, 0x96e00200,
	mmCP_RB_WPTR_POLL_CNTL, 0xffffffff, 0x00900100,
	mmRLC_CGCG_CGLS_CTRL, 0xffffffff, 0x0020003c,
पूर्ण;

अटल स्थिर u32 cz_golden_settings_a11[] =
अणु
	mmCB_HW_CONTROL_3, 0x00000040, 0x00000040,
	mmDB_DEBUG2, 0xf00fffff, 0x00000400,
	mmGB_GPU_ID, 0x0000000f, 0x00000000,
	mmPA_SC_ENHANCE, 0xffffffff, 0x00000001,
	mmPA_SC_LINE_STIPPLE_STATE, 0x0000ff0f, 0x00000000,
	mmRLC_CGCG_CGLS_CTRL, 0x00000003, 0x0000003c,
	mmSQ_RANDOM_WAVE_PRI, 0x001fffff, 0x000006fd,
	mmTA_CNTL_AUX, 0x000f000f, 0x00010000,
	mmTCC_CTRL, 0x00100000, 0xf31fff7f,
	mmTCC_EXE_DISABLE, 0x00000002, 0x00000002,
	mmTCP_ADDR_CONFIG, 0x0000000f, 0x000000f3,
	mmTCP_CHAN_STEER_LO, 0xffffffff, 0x00001302
पूर्ण;

अटल स्थिर u32 cz_golden_common_all[] =
अणु
	mmGRBM_GFX_INDEX, 0xffffffff, 0xe0000000,
	mmPA_SC_RASTER_CONFIG, 0xffffffff, 0x00000002,
	mmPA_SC_RASTER_CONFIG_1, 0xffffffff, 0x00000000,
	mmGB_ADDR_CONFIG, 0xffffffff, 0x22010001,
	mmSPI_RESOURCE_RESERVE_CU_0, 0xffffffff, 0x00000800,
	mmSPI_RESOURCE_RESERVE_CU_1, 0xffffffff, 0x00000800,
	mmSPI_RESOURCE_RESERVE_EN_CU_0, 0xffffffff, 0x00FF7FBF,
	mmSPI_RESOURCE_RESERVE_EN_CU_1, 0xffffffff, 0x00FF7FAF
पूर्ण;

अटल स्थिर u32 cz_mgcg_cgcg_init[] =
अणु
	mmRLC_CGTT_MGCG_OVERRIDE, 0xffffffff, 0xffffffff,
	mmGRBM_GFX_INDEX, 0xffffffff, 0xe0000000,
	mmCB_CGTT_SCLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_BCI_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_CP_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_CPC_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_CPF_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_GDS_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_IA_CLK_CTRL, 0xffffffff, 0x06000100,
	mmCGTT_PA_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_WD_CLK_CTRL, 0xffffffff, 0x06000100,
	mmCGTT_PC_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_RLC_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_SC_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_SPI_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_SQ_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_SQG_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_SX_CLK_CTRL0, 0xffffffff, 0x00000100,
	mmCGTT_SX_CLK_CTRL1, 0xffffffff, 0x00000100,
	mmCGTT_SX_CLK_CTRL2, 0xffffffff, 0x00000100,
	mmCGTT_SX_CLK_CTRL3, 0xffffffff, 0x00000100,
	mmCGTT_SX_CLK_CTRL4, 0xffffffff, 0x00000100,
	mmCGTT_TCI_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_TCP_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_VGT_CLK_CTRL, 0xffffffff, 0x06000100,
	mmDB_CGTT_CLK_CTRL_0, 0xffffffff, 0x00000100,
	mmTA_CGTT_CTRL, 0xffffffff, 0x00000100,
	mmTCA_CGTT_SCLK_CTRL, 0xffffffff, 0x00000100,
	mmTCC_CGTT_SCLK_CTRL, 0xffffffff, 0x00000100,
	mmTD_CGTT_CTRL, 0xffffffff, 0x00000100,
	mmGRBM_GFX_INDEX, 0xffffffff, 0xe0000000,
	mmCGTS_CU0_SP0_CTRL_REG, 0xffffffff, 0x00010000,
	mmCGTS_CU0_LDS_SQ_CTRL_REG, 0xffffffff, 0x00030002,
	mmCGTS_CU0_TA_SQC_CTRL_REG, 0xffffffff, 0x00040007,
	mmCGTS_CU0_SP1_CTRL_REG, 0xffffffff, 0x00060005,
	mmCGTS_CU0_TD_TCP_CTRL_REG, 0xffffffff, 0x00090008,
	mmCGTS_CU1_SP0_CTRL_REG, 0xffffffff, 0x00010000,
	mmCGTS_CU1_LDS_SQ_CTRL_REG, 0xffffffff, 0x00030002,
	mmCGTS_CU1_TA_CTRL_REG, 0xffffffff, 0x00040007,
	mmCGTS_CU1_SP1_CTRL_REG, 0xffffffff, 0x00060005,
	mmCGTS_CU1_TD_TCP_CTRL_REG, 0xffffffff, 0x00090008,
	mmCGTS_CU2_SP0_CTRL_REG, 0xffffffff, 0x00010000,
	mmCGTS_CU2_LDS_SQ_CTRL_REG, 0xffffffff, 0x00030002,
	mmCGTS_CU2_TA_CTRL_REG, 0xffffffff, 0x00040007,
	mmCGTS_CU2_SP1_CTRL_REG, 0xffffffff, 0x00060005,
	mmCGTS_CU2_TD_TCP_CTRL_REG, 0xffffffff, 0x00090008,
	mmCGTS_CU3_SP0_CTRL_REG, 0xffffffff, 0x00010000,
	mmCGTS_CU3_LDS_SQ_CTRL_REG, 0xffffffff, 0x00030002,
	mmCGTS_CU3_TA_CTRL_REG, 0xffffffff, 0x00040007,
	mmCGTS_CU3_SP1_CTRL_REG, 0xffffffff, 0x00060005,
	mmCGTS_CU3_TD_TCP_CTRL_REG, 0xffffffff, 0x00090008,
	mmCGTS_CU4_SP0_CTRL_REG, 0xffffffff, 0x00010000,
	mmCGTS_CU4_LDS_SQ_CTRL_REG, 0xffffffff, 0x00030002,
	mmCGTS_CU4_TA_SQC_CTRL_REG, 0xffffffff, 0x00040007,
	mmCGTS_CU4_SP1_CTRL_REG, 0xffffffff, 0x00060005,
	mmCGTS_CU4_TD_TCP_CTRL_REG, 0xffffffff, 0x00090008,
	mmCGTS_CU5_SP0_CTRL_REG, 0xffffffff, 0x00010000,
	mmCGTS_CU5_LDS_SQ_CTRL_REG, 0xffffffff, 0x00030002,
	mmCGTS_CU5_TA_CTRL_REG, 0xffffffff, 0x00040007,
	mmCGTS_CU5_SP1_CTRL_REG, 0xffffffff, 0x00060005,
	mmCGTS_CU5_TD_TCP_CTRL_REG, 0xffffffff, 0x00090008,
	mmCGTS_CU6_SP0_CTRL_REG, 0xffffffff, 0x00010000,
	mmCGTS_CU6_LDS_SQ_CTRL_REG, 0xffffffff, 0x00030002,
	mmCGTS_CU6_TA_CTRL_REG, 0xffffffff, 0x00040007,
	mmCGTS_CU6_SP1_CTRL_REG, 0xffffffff, 0x00060005,
	mmCGTS_CU6_TD_TCP_CTRL_REG, 0xffffffff, 0x00090008,
	mmCGTS_CU7_SP0_CTRL_REG, 0xffffffff, 0x00010000,
	mmCGTS_CU7_LDS_SQ_CTRL_REG, 0xffffffff, 0x00030002,
	mmCGTS_CU7_TA_CTRL_REG, 0xffffffff, 0x00040007,
	mmCGTS_CU7_SP1_CTRL_REG, 0xffffffff, 0x00060005,
	mmCGTS_CU7_TD_TCP_CTRL_REG, 0xffffffff, 0x00090008,
	mmCGTS_SM_CTRL_REG, 0xffffffff, 0x96e00200,
	mmCP_RB_WPTR_POLL_CNTL, 0xffffffff, 0x00900100,
	mmRLC_CGCG_CGLS_CTRL, 0xffffffff, 0x0020003f,
	mmCP_MEM_SLP_CNTL, 0x00000001, 0x00000001,
पूर्ण;

अटल स्थिर u32 stoney_golden_settings_a11[] =
अणु
	mmDB_DEBUG2, 0xf00fffff, 0x00000400,
	mmGB_GPU_ID, 0x0000000f, 0x00000000,
	mmPA_SC_ENHANCE, 0xffffffff, 0x20000001,
	mmPA_SC_LINE_STIPPLE_STATE, 0x0000ff0f, 0x00000000,
	mmRLC_CGCG_CGLS_CTRL, 0x00000003, 0x0001003c,
	mmTA_CNTL_AUX, 0x000f000f, 0x000b0000,
	mmTCC_CTRL, 0x00100000, 0xf31fff7f,
	mmTCC_EXE_DISABLE, 0x00000002, 0x00000002,
	mmTCP_ADDR_CONFIG, 0x0000000f, 0x000000f1,
	mmTCP_CHAN_STEER_LO, 0xffffffff, 0x10101010,
पूर्ण;

अटल स्थिर u32 stoney_golden_common_all[] =
अणु
	mmGRBM_GFX_INDEX, 0xffffffff, 0xe0000000,
	mmPA_SC_RASTER_CONFIG, 0xffffffff, 0x00000000,
	mmPA_SC_RASTER_CONFIG_1, 0xffffffff, 0x00000000,
	mmGB_ADDR_CONFIG, 0xffffffff, 0x12010001,
	mmSPI_RESOURCE_RESERVE_CU_0, 0xffffffff, 0x00000800,
	mmSPI_RESOURCE_RESERVE_CU_1, 0xffffffff, 0x00000800,
	mmSPI_RESOURCE_RESERVE_EN_CU_0, 0xffffffff, 0x00FF7FBF,
	mmSPI_RESOURCE_RESERVE_EN_CU_1, 0xffffffff, 0x00FF7FAF,
पूर्ण;

अटल स्थिर u32 stoney_mgcg_cgcg_init[] =
अणु
	mmGRBM_GFX_INDEX, 0xffffffff, 0xe0000000,
	mmRLC_CGCG_CGLS_CTRL, 0xffffffff, 0x0020003f,
	mmCP_MEM_SLP_CNTL, 0xffffffff, 0x00020201,
	mmRLC_MEM_SLP_CNTL, 0xffffffff, 0x00020201,
	mmCGTS_SM_CTRL_REG, 0xffffffff, 0x96940200,
पूर्ण;


अटल स्थिर अक्षर * स्थिर sq_edc_source_names[] = अणु
	"SQ_EDC_INFO_SOURCE_INVALID: No EDC error has occurred",
	"SQ_EDC_INFO_SOURCE_INST: EDC source is Instruction Fetch",
	"SQ_EDC_INFO_SOURCE_SGPR: EDC source is SGPR or SQC data return",
	"SQ_EDC_INFO_SOURCE_VGPR: EDC source is VGPR",
	"SQ_EDC_INFO_SOURCE_LDS: EDC source is LDS",
	"SQ_EDC_INFO_SOURCE_GDS: EDC source is GDS",
	"SQ_EDC_INFO_SOURCE_TA: EDC source is TA",
पूर्ण;

अटल व्योम gfx_v8_0_set_ring_funcs(काष्ठा amdgpu_device *adev);
अटल व्योम gfx_v8_0_set_irq_funcs(काष्ठा amdgpu_device *adev);
अटल व्योम gfx_v8_0_set_gds_init(काष्ठा amdgpu_device *adev);
अटल व्योम gfx_v8_0_set_rlc_funcs(काष्ठा amdgpu_device *adev);
अटल u32 gfx_v8_0_get_csb_size(काष्ठा amdgpu_device *adev);
अटल व्योम gfx_v8_0_get_cu_info(काष्ठा amdgpu_device *adev);
अटल व्योम gfx_v8_0_ring_emit_ce_meta(काष्ठा amdgpu_ring *ring);
अटल व्योम gfx_v8_0_ring_emit_de_meta(काष्ठा amdgpu_ring *ring);

#घोषणा CG_ACLK_CNTL__ACLK_DIVIDER_MASK                    0x0000007fL
#घोषणा CG_ACLK_CNTL__ACLK_DIVIDER__SHIFT                  0x00000000L

अटल व्योम gfx_v8_0_init_golden_रेजिस्टरs(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक32_t data;

	चयन (adev->asic_type) अणु
	हाल CHIP_TOPAZ:
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							iceland_mgcg_cgcg_init,
							ARRAY_SIZE(iceland_mgcg_cgcg_init));
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							golden_settings_iceland_a11,
							ARRAY_SIZE(golden_settings_iceland_a11));
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							iceland_golden_common_all,
							ARRAY_SIZE(iceland_golden_common_all));
		अवरोध;
	हाल CHIP_FIJI:
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							fiji_mgcg_cgcg_init,
							ARRAY_SIZE(fiji_mgcg_cgcg_init));
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							golden_settings_fiji_a10,
							ARRAY_SIZE(golden_settings_fiji_a10));
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							fiji_golden_common_all,
							ARRAY_SIZE(fiji_golden_common_all));
		अवरोध;

	हाल CHIP_TONGA:
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							tonga_mgcg_cgcg_init,
							ARRAY_SIZE(tonga_mgcg_cgcg_init));
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							golden_settings_tonga_a11,
							ARRAY_SIZE(golden_settings_tonga_a11));
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							tonga_golden_common_all,
							ARRAY_SIZE(tonga_golden_common_all));
		अवरोध;
	हाल CHIP_VEGAM:
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							golden_settings_vegam_a11,
							ARRAY_SIZE(golden_settings_vegam_a11));
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							vegam_golden_common_all,
							ARRAY_SIZE(vegam_golden_common_all));
		अवरोध;
	हाल CHIP_POLARIS11:
	हाल CHIP_POLARIS12:
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							golden_settings_polaris11_a11,
							ARRAY_SIZE(golden_settings_polaris11_a11));
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							polaris11_golden_common_all,
							ARRAY_SIZE(polaris11_golden_common_all));
		अवरोध;
	हाल CHIP_POLARIS10:
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							golden_settings_polaris10_a11,
							ARRAY_SIZE(golden_settings_polaris10_a11));
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							polaris10_golden_common_all,
							ARRAY_SIZE(polaris10_golden_common_all));
		data = RREG32_SMC(ixCG_ACLK_CNTL);
		data &= ~CG_ACLK_CNTL__ACLK_DIVIDER_MASK;
		data |= 0x18 << CG_ACLK_CNTL__ACLK_DIVIDER__SHIFT;
		WREG32_SMC(ixCG_ACLK_CNTL, data);
		अगर ((adev->pdev->device == 0x67DF) && (adev->pdev->revision == 0xc7) &&
		    ((adev->pdev->subप्रणाली_device == 0xb37 && adev->pdev->subप्रणाली_venकरोr == 0x1002) ||
		     (adev->pdev->subप्रणाली_device == 0x4a8 && adev->pdev->subप्रणाली_venकरोr == 0x1043) ||
		     (adev->pdev->subप्रणाली_device == 0x9480 && adev->pdev->subप्रणाली_venकरोr == 0x1680))) अणु
			amdgpu_atombios_i2c_channel_trans(adev, 0x10, 0x96, 0x1E, 0xDD);
			amdgpu_atombios_i2c_channel_trans(adev, 0x10, 0x96, 0x1F, 0xD0);
		पूर्ण
		अवरोध;
	हाल CHIP_CARRIZO:
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							cz_mgcg_cgcg_init,
							ARRAY_SIZE(cz_mgcg_cgcg_init));
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							cz_golden_settings_a11,
							ARRAY_SIZE(cz_golden_settings_a11));
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							cz_golden_common_all,
							ARRAY_SIZE(cz_golden_common_all));
		अवरोध;
	हाल CHIP_STONEY:
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							stoney_mgcg_cgcg_init,
							ARRAY_SIZE(stoney_mgcg_cgcg_init));
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							stoney_golden_settings_a11,
							ARRAY_SIZE(stoney_golden_settings_a11));
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							stoney_golden_common_all,
							ARRAY_SIZE(stoney_golden_common_all));
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम gfx_v8_0_scratch_init(काष्ठा amdgpu_device *adev)
अणु
	adev->gfx.scratch.num_reg = 8;
	adev->gfx.scratch.reg_base = mmSCRATCH_REG0;
	adev->gfx.scratch.मुक्त_mask = (1u << adev->gfx.scratch.num_reg) - 1;
पूर्ण

अटल पूर्णांक gfx_v8_0_ring_test_ring(काष्ठा amdgpu_ring *ring)
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

अटल पूर्णांक gfx_v8_0_ring_test_ib(काष्ठा amdgpu_ring *ring, दीर्घ समयout)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	काष्ठा amdgpu_ib ib;
	काष्ठा dma_fence *f = शून्य;

	अचिन्हित पूर्णांक index;
	uपूर्णांक64_t gpu_addr;
	uपूर्णांक32_t पंचांगp;
	दीर्घ r;

	r = amdgpu_device_wb_get(adev, &index);
	अगर (r)
		वापस r;

	gpu_addr = adev->wb.gpu_addr + (index * 4);
	adev->wb.wb[index] = cpu_to_le32(0xCAFEDEAD);
	स_रखो(&ib, 0, माप(ib));
	r = amdgpu_ib_get(adev, शून्य, 16,
					AMDGPU_IB_POOL_सूचीECT, &ib);
	अगर (r)
		जाओ err1;

	ib.ptr[0] = PACKET3(PACKET3_WRITE_DATA, 3);
	ib.ptr[1] = WRITE_DATA_DST_SEL(5) | WR_CONFIRM;
	ib.ptr[2] = lower_32_bits(gpu_addr);
	ib.ptr[3] = upper_32_bits(gpu_addr);
	ib.ptr[4] = 0xDEADBEEF;
	ib.length_dw = 5;

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

	पंचांगp = adev->wb.wb[index];
	अगर (पंचांगp == 0xDEADBEEF)
		r = 0;
	अन्यथा
		r = -EINVAL;

err2:
	amdgpu_ib_मुक्त(adev, &ib, शून्य);
	dma_fence_put(f);
err1:
	amdgpu_device_wb_मुक्त(adev, index);
	वापस r;
पूर्ण


अटल व्योम gfx_v8_0_मुक्त_microcode(काष्ठा amdgpu_device *adev)
अणु
	release_firmware(adev->gfx.pfp_fw);
	adev->gfx.pfp_fw = शून्य;
	release_firmware(adev->gfx.me_fw);
	adev->gfx.me_fw = शून्य;
	release_firmware(adev->gfx.ce_fw);
	adev->gfx.ce_fw = शून्य;
	release_firmware(adev->gfx.rlc_fw);
	adev->gfx.rlc_fw = शून्य;
	release_firmware(adev->gfx.mec_fw);
	adev->gfx.mec_fw = शून्य;
	अगर ((adev->asic_type != CHIP_STONEY) &&
	    (adev->asic_type != CHIP_TOPAZ))
		release_firmware(adev->gfx.mec2_fw);
	adev->gfx.mec2_fw = शून्य;

	kमुक्त(adev->gfx.rlc.रेजिस्टर_list_क्रमmat);
पूर्ण

अटल पूर्णांक gfx_v8_0_init_microcode(काष्ठा amdgpu_device *adev)
अणु
	स्थिर अक्षर *chip_name;
	अक्षर fw_name[30];
	पूर्णांक err;
	काष्ठा amdgpu_firmware_info *info = शून्य;
	स्थिर काष्ठा common_firmware_header *header = शून्य;
	स्थिर काष्ठा gfx_firmware_header_v1_0 *cp_hdr;
	स्थिर काष्ठा rlc_firmware_header_v2_0 *rlc_hdr;
	अचिन्हित पूर्णांक *पंचांगp = शून्य, i;

	DRM_DEBUG("\n");

	चयन (adev->asic_type) अणु
	हाल CHIP_TOPAZ:
		chip_name = "topaz";
		अवरोध;
	हाल CHIP_TONGA:
		chip_name = "tonga";
		अवरोध;
	हाल CHIP_CARRIZO:
		chip_name = "carrizo";
		अवरोध;
	हाल CHIP_FIJI:
		chip_name = "fiji";
		अवरोध;
	हाल CHIP_STONEY:
		chip_name = "stoney";
		अवरोध;
	हाल CHIP_POLARIS10:
		chip_name = "polaris10";
		अवरोध;
	हाल CHIP_POLARIS11:
		chip_name = "polaris11";
		अवरोध;
	हाल CHIP_POLARIS12:
		chip_name = "polaris12";
		अवरोध;
	हाल CHIP_VEGAM:
		chip_name = "vegam";
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	अगर (adev->asic_type >= CHIP_POLARIS10 && adev->asic_type <= CHIP_POLARIS12) अणु
		snम_लिखो(fw_name, माप(fw_name), "amdgpu/%s_pfp_2.bin", chip_name);
		err = request_firmware(&adev->gfx.pfp_fw, fw_name, adev->dev);
		अगर (err == -ENOENT) अणु
			snम_लिखो(fw_name, माप(fw_name), "amdgpu/%s_pfp.bin", chip_name);
			err = request_firmware(&adev->gfx.pfp_fw, fw_name, adev->dev);
		पूर्ण
	पूर्ण अन्यथा अणु
		snम_लिखो(fw_name, माप(fw_name), "amdgpu/%s_pfp.bin", chip_name);
		err = request_firmware(&adev->gfx.pfp_fw, fw_name, adev->dev);
	पूर्ण
	अगर (err)
		जाओ out;
	err = amdgpu_ucode_validate(adev->gfx.pfp_fw);
	अगर (err)
		जाओ out;
	cp_hdr = (स्थिर काष्ठा gfx_firmware_header_v1_0 *)adev->gfx.pfp_fw->data;
	adev->gfx.pfp_fw_version = le32_to_cpu(cp_hdr->header.ucode_version);
	adev->gfx.pfp_feature_version = le32_to_cpu(cp_hdr->ucode_feature_version);

	अगर (adev->asic_type >= CHIP_POLARIS10 && adev->asic_type <= CHIP_POLARIS12) अणु
		snम_लिखो(fw_name, माप(fw_name), "amdgpu/%s_me_2.bin", chip_name);
		err = request_firmware(&adev->gfx.me_fw, fw_name, adev->dev);
		अगर (err == -ENOENT) अणु
			snम_लिखो(fw_name, माप(fw_name), "amdgpu/%s_me.bin", chip_name);
			err = request_firmware(&adev->gfx.me_fw, fw_name, adev->dev);
		पूर्ण
	पूर्ण अन्यथा अणु
		snम_लिखो(fw_name, माप(fw_name), "amdgpu/%s_me.bin", chip_name);
		err = request_firmware(&adev->gfx.me_fw, fw_name, adev->dev);
	पूर्ण
	अगर (err)
		जाओ out;
	err = amdgpu_ucode_validate(adev->gfx.me_fw);
	अगर (err)
		जाओ out;
	cp_hdr = (स्थिर काष्ठा gfx_firmware_header_v1_0 *)adev->gfx.me_fw->data;
	adev->gfx.me_fw_version = le32_to_cpu(cp_hdr->header.ucode_version);

	adev->gfx.me_feature_version = le32_to_cpu(cp_hdr->ucode_feature_version);

	अगर (adev->asic_type >= CHIP_POLARIS10 && adev->asic_type <= CHIP_POLARIS12) अणु
		snम_लिखो(fw_name, माप(fw_name), "amdgpu/%s_ce_2.bin", chip_name);
		err = request_firmware(&adev->gfx.ce_fw, fw_name, adev->dev);
		अगर (err == -ENOENT) अणु
			snम_लिखो(fw_name, माप(fw_name), "amdgpu/%s_ce.bin", chip_name);
			err = request_firmware(&adev->gfx.ce_fw, fw_name, adev->dev);
		पूर्ण
	पूर्ण अन्यथा अणु
		snम_लिखो(fw_name, माप(fw_name), "amdgpu/%s_ce.bin", chip_name);
		err = request_firmware(&adev->gfx.ce_fw, fw_name, adev->dev);
	पूर्ण
	अगर (err)
		जाओ out;
	err = amdgpu_ucode_validate(adev->gfx.ce_fw);
	अगर (err)
		जाओ out;
	cp_hdr = (स्थिर काष्ठा gfx_firmware_header_v1_0 *)adev->gfx.ce_fw->data;
	adev->gfx.ce_fw_version = le32_to_cpu(cp_hdr->header.ucode_version);
	adev->gfx.ce_feature_version = le32_to_cpu(cp_hdr->ucode_feature_version);

	/*
	 * Support क्रम MCBP/Virtualization in combination with chained IBs is
	 * क्रमmal released on feature version #46
	 */
	अगर (adev->gfx.ce_feature_version >= 46 &&
	    adev->gfx.pfp_feature_version >= 46) अणु
		adev->virt.chained_ib_support = true;
		DRM_INFO("Chained IB support enabled!\n");
	पूर्ण अन्यथा
		adev->virt.chained_ib_support = false;

	snम_लिखो(fw_name, माप(fw_name), "amdgpu/%s_rlc.bin", chip_name);
	err = request_firmware(&adev->gfx.rlc_fw, fw_name, adev->dev);
	अगर (err)
		जाओ out;
	err = amdgpu_ucode_validate(adev->gfx.rlc_fw);
	rlc_hdr = (स्थिर काष्ठा rlc_firmware_header_v2_0 *)adev->gfx.rlc_fw->data;
	adev->gfx.rlc_fw_version = le32_to_cpu(rlc_hdr->header.ucode_version);
	adev->gfx.rlc_feature_version = le32_to_cpu(rlc_hdr->ucode_feature_version);

	adev->gfx.rlc.save_and_restore_offset =
			le32_to_cpu(rlc_hdr->save_and_restore_offset);
	adev->gfx.rlc.clear_state_descriptor_offset =
			le32_to_cpu(rlc_hdr->clear_state_descriptor_offset);
	adev->gfx.rlc.avail_scratch_ram_locations =
			le32_to_cpu(rlc_hdr->avail_scratch_ram_locations);
	adev->gfx.rlc.reg_restore_list_size =
			le32_to_cpu(rlc_hdr->reg_restore_list_size);
	adev->gfx.rlc.reg_list_क्रमmat_start =
			le32_to_cpu(rlc_hdr->reg_list_क्रमmat_start);
	adev->gfx.rlc.reg_list_क्रमmat_separate_start =
			le32_to_cpu(rlc_hdr->reg_list_क्रमmat_separate_start);
	adev->gfx.rlc.starting_offsets_start =
			le32_to_cpu(rlc_hdr->starting_offsets_start);
	adev->gfx.rlc.reg_list_क्रमmat_size_bytes =
			le32_to_cpu(rlc_hdr->reg_list_क्रमmat_size_bytes);
	adev->gfx.rlc.reg_list_size_bytes =
			le32_to_cpu(rlc_hdr->reg_list_size_bytes);

	adev->gfx.rlc.रेजिस्टर_list_क्रमmat =
			kदो_स्मृति(adev->gfx.rlc.reg_list_क्रमmat_size_bytes +
					adev->gfx.rlc.reg_list_size_bytes, GFP_KERNEL);

	अगर (!adev->gfx.rlc.रेजिस्टर_list_क्रमmat) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	पंचांगp = (अचिन्हित पूर्णांक *)((uपूर्णांकptr_t)rlc_hdr +
			le32_to_cpu(rlc_hdr->reg_list_क्रमmat_array_offset_bytes));
	क्रम (i = 0 ; i < (adev->gfx.rlc.reg_list_क्रमmat_size_bytes >> 2); i++)
		adev->gfx.rlc.रेजिस्टर_list_क्रमmat[i] =	le32_to_cpu(पंचांगp[i]);

	adev->gfx.rlc.रेजिस्टर_restore = adev->gfx.rlc.रेजिस्टर_list_क्रमmat + i;

	पंचांगp = (अचिन्हित पूर्णांक *)((uपूर्णांकptr_t)rlc_hdr +
			le32_to_cpu(rlc_hdr->reg_list_array_offset_bytes));
	क्रम (i = 0 ; i < (adev->gfx.rlc.reg_list_size_bytes >> 2); i++)
		adev->gfx.rlc.रेजिस्टर_restore[i] = le32_to_cpu(पंचांगp[i]);

	अगर (adev->asic_type >= CHIP_POLARIS10 && adev->asic_type <= CHIP_POLARIS12) अणु
		snम_लिखो(fw_name, माप(fw_name), "amdgpu/%s_mec_2.bin", chip_name);
		err = request_firmware(&adev->gfx.mec_fw, fw_name, adev->dev);
		अगर (err == -ENOENT) अणु
			snम_लिखो(fw_name, माप(fw_name), "amdgpu/%s_mec.bin", chip_name);
			err = request_firmware(&adev->gfx.mec_fw, fw_name, adev->dev);
		पूर्ण
	पूर्ण अन्यथा अणु
		snम_लिखो(fw_name, माप(fw_name), "amdgpu/%s_mec.bin", chip_name);
		err = request_firmware(&adev->gfx.mec_fw, fw_name, adev->dev);
	पूर्ण
	अगर (err)
		जाओ out;
	err = amdgpu_ucode_validate(adev->gfx.mec_fw);
	अगर (err)
		जाओ out;
	cp_hdr = (स्थिर काष्ठा gfx_firmware_header_v1_0 *)adev->gfx.mec_fw->data;
	adev->gfx.mec_fw_version = le32_to_cpu(cp_hdr->header.ucode_version);
	adev->gfx.mec_feature_version = le32_to_cpu(cp_hdr->ucode_feature_version);

	अगर ((adev->asic_type != CHIP_STONEY) &&
	    (adev->asic_type != CHIP_TOPAZ)) अणु
		अगर (adev->asic_type >= CHIP_POLARIS10 && adev->asic_type <= CHIP_POLARIS12) अणु
			snम_लिखो(fw_name, माप(fw_name), "amdgpu/%s_mec2_2.bin", chip_name);
			err = request_firmware(&adev->gfx.mec2_fw, fw_name, adev->dev);
			अगर (err == -ENOENT) अणु
				snम_लिखो(fw_name, माप(fw_name), "amdgpu/%s_mec2.bin", chip_name);
				err = request_firmware(&adev->gfx.mec2_fw, fw_name, adev->dev);
			पूर्ण
		पूर्ण अन्यथा अणु
			snम_लिखो(fw_name, माप(fw_name), "amdgpu/%s_mec2.bin", chip_name);
			err = request_firmware(&adev->gfx.mec2_fw, fw_name, adev->dev);
		पूर्ण
		अगर (!err) अणु
			err = amdgpu_ucode_validate(adev->gfx.mec2_fw);
			अगर (err)
				जाओ out;
			cp_hdr = (स्थिर काष्ठा gfx_firmware_header_v1_0 *)
				adev->gfx.mec2_fw->data;
			adev->gfx.mec2_fw_version =
				le32_to_cpu(cp_hdr->header.ucode_version);
			adev->gfx.mec2_feature_version =
				le32_to_cpu(cp_hdr->ucode_feature_version);
		पूर्ण अन्यथा अणु
			err = 0;
			adev->gfx.mec2_fw = शून्य;
		पूर्ण
	पूर्ण

	info = &adev->firmware.ucode[AMDGPU_UCODE_ID_CP_PFP];
	info->ucode_id = AMDGPU_UCODE_ID_CP_PFP;
	info->fw = adev->gfx.pfp_fw;
	header = (स्थिर काष्ठा common_firmware_header *)info->fw->data;
	adev->firmware.fw_size +=
		ALIGN(le32_to_cpu(header->ucode_size_bytes), PAGE_SIZE);

	info = &adev->firmware.ucode[AMDGPU_UCODE_ID_CP_ME];
	info->ucode_id = AMDGPU_UCODE_ID_CP_ME;
	info->fw = adev->gfx.me_fw;
	header = (स्थिर काष्ठा common_firmware_header *)info->fw->data;
	adev->firmware.fw_size +=
		ALIGN(le32_to_cpu(header->ucode_size_bytes), PAGE_SIZE);

	info = &adev->firmware.ucode[AMDGPU_UCODE_ID_CP_CE];
	info->ucode_id = AMDGPU_UCODE_ID_CP_CE;
	info->fw = adev->gfx.ce_fw;
	header = (स्थिर काष्ठा common_firmware_header *)info->fw->data;
	adev->firmware.fw_size +=
		ALIGN(le32_to_cpu(header->ucode_size_bytes), PAGE_SIZE);

	info = &adev->firmware.ucode[AMDGPU_UCODE_ID_RLC_G];
	info->ucode_id = AMDGPU_UCODE_ID_RLC_G;
	info->fw = adev->gfx.rlc_fw;
	header = (स्थिर काष्ठा common_firmware_header *)info->fw->data;
	adev->firmware.fw_size +=
		ALIGN(le32_to_cpu(header->ucode_size_bytes), PAGE_SIZE);

	info = &adev->firmware.ucode[AMDGPU_UCODE_ID_CP_MEC1];
	info->ucode_id = AMDGPU_UCODE_ID_CP_MEC1;
	info->fw = adev->gfx.mec_fw;
	header = (स्थिर काष्ठा common_firmware_header *)info->fw->data;
	adev->firmware.fw_size +=
		ALIGN(le32_to_cpu(header->ucode_size_bytes), PAGE_SIZE);

	/* we need account JT in */
	cp_hdr = (स्थिर काष्ठा gfx_firmware_header_v1_0 *)adev->gfx.mec_fw->data;
	adev->firmware.fw_size +=
		ALIGN(le32_to_cpu(cp_hdr->jt_size) << 2, PAGE_SIZE);

	अगर (amdgpu_sriov_vf(adev)) अणु
		info = &adev->firmware.ucode[AMDGPU_UCODE_ID_STORAGE];
		info->ucode_id = AMDGPU_UCODE_ID_STORAGE;
		info->fw = adev->gfx.mec_fw;
		adev->firmware.fw_size +=
			ALIGN(le32_to_cpu(64 * PAGE_SIZE), PAGE_SIZE);
	पूर्ण

	अगर (adev->gfx.mec2_fw) अणु
		info = &adev->firmware.ucode[AMDGPU_UCODE_ID_CP_MEC2];
		info->ucode_id = AMDGPU_UCODE_ID_CP_MEC2;
		info->fw = adev->gfx.mec2_fw;
		header = (स्थिर काष्ठा common_firmware_header *)info->fw->data;
		adev->firmware.fw_size +=
			ALIGN(le32_to_cpu(header->ucode_size_bytes), PAGE_SIZE);
	पूर्ण

out:
	अगर (err) अणु
		dev_err(adev->dev,
			"gfx8: Failed to load firmware \"%s\"\n",
			fw_name);
		release_firmware(adev->gfx.pfp_fw);
		adev->gfx.pfp_fw = शून्य;
		release_firmware(adev->gfx.me_fw);
		adev->gfx.me_fw = शून्य;
		release_firmware(adev->gfx.ce_fw);
		adev->gfx.ce_fw = शून्य;
		release_firmware(adev->gfx.rlc_fw);
		adev->gfx.rlc_fw = शून्य;
		release_firmware(adev->gfx.mec_fw);
		adev->gfx.mec_fw = शून्य;
		release_firmware(adev->gfx.mec2_fw);
		adev->gfx.mec2_fw = शून्य;
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम gfx_v8_0_get_csb_buffer(काष्ठा amdgpu_device *adev,
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
				buffer[count++] = cpu_to_le32(ext->reg_index -
						PACKET3_SET_CONTEXT_REG_START);
				क्रम (i = 0; i < ext->reg_count; i++)
					buffer[count++] = cpu_to_le32(ext->extent[i]);
			पूर्ण अन्यथा अणु
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण

	buffer[count++] = cpu_to_le32(PACKET3(PACKET3_SET_CONTEXT_REG, 2));
	buffer[count++] = cpu_to_le32(mmPA_SC_RASTER_CONFIG -
			PACKET3_SET_CONTEXT_REG_START);
	buffer[count++] = cpu_to_le32(adev->gfx.config.rb_config[0][0].raster_config);
	buffer[count++] = cpu_to_le32(adev->gfx.config.rb_config[0][0].raster_config_1);

	buffer[count++] = cpu_to_le32(PACKET3(PACKET3_PREAMBLE_CNTL, 0));
	buffer[count++] = cpu_to_le32(PACKET3_PREAMBLE_END_CLEAR_STATE);

	buffer[count++] = cpu_to_le32(PACKET3(PACKET3_CLEAR_STATE, 0));
	buffer[count++] = cpu_to_le32(0);
पूर्ण

अटल पूर्णांक gfx_v8_0_cp_jump_table_num(काष्ठा amdgpu_device *adev)
अणु
	अगर (adev->asic_type == CHIP_CARRIZO)
		वापस 5;
	अन्यथा
		वापस 4;
पूर्ण

अटल पूर्णांक gfx_v8_0_rlc_init(काष्ठा amdgpu_device *adev)
अणु
	स्थिर काष्ठा cs_section_def *cs_data;
	पूर्णांक r;

	adev->gfx.rlc.cs_data = vi_cs_data;

	cs_data = adev->gfx.rlc.cs_data;

	अगर (cs_data) अणु
		/* init clear state block */
		r = amdgpu_gfx_rlc_init_csb(adev);
		अगर (r)
			वापस r;
	पूर्ण

	अगर ((adev->asic_type == CHIP_CARRIZO) ||
	    (adev->asic_type == CHIP_STONEY)) अणु
		adev->gfx.rlc.cp_table_size = ALIGN(96 * 5 * 4, 2048) + (64 * 1024); /* JT + GDS */
		r = amdgpu_gfx_rlc_init_cpt(adev);
		अगर (r)
			वापस r;
	पूर्ण

	/* init spm vmid with 0xf */
	अगर (adev->gfx.rlc.funcs->update_spm_vmid)
		adev->gfx.rlc.funcs->update_spm_vmid(adev, 0xf);

	वापस 0;
पूर्ण

अटल व्योम gfx_v8_0_mec_fini(काष्ठा amdgpu_device *adev)
अणु
	amdgpu_bo_मुक्त_kernel(&adev->gfx.mec.hpd_eop_obj, शून्य, शून्य);
पूर्ण

अटल पूर्णांक gfx_v8_0_mec_init(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक r;
	u32 *hpd;
	माप_प्रकार mec_hpd_size;

	biपंचांगap_zero(adev->gfx.mec.queue_biपंचांगap, AMDGPU_MAX_COMPUTE_QUEUES);

	/* take ownership of the relevant compute queues */
	amdgpu_gfx_compute_queue_acquire(adev);

	mec_hpd_size = adev->gfx.num_compute_rings * GFX8_MEC_HPD_SIZE;
	अगर (mec_hpd_size) अणु
		r = amdgpu_bo_create_reserved(adev, mec_hpd_size, PAGE_SIZE,
					      AMDGPU_GEM_DOMAIN_VRAM,
					      &adev->gfx.mec.hpd_eop_obj,
					      &adev->gfx.mec.hpd_eop_gpu_addr,
					      (व्योम **)&hpd);
		अगर (r) अणु
			dev_warn(adev->dev, "(%d) create HDP EOP bo failed\n", r);
			वापस r;
		पूर्ण

		स_रखो(hpd, 0, mec_hpd_size);

		amdgpu_bo_kunmap(adev->gfx.mec.hpd_eop_obj);
		amdgpu_bo_unreserve(adev->gfx.mec.hpd_eop_obj);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर u32 vgpr_init_compute_shader[] =
अणु
	0x7e000209, 0x7e020208,
	0x7e040207, 0x7e060206,
	0x7e080205, 0x7e0a0204,
	0x7e0c0203, 0x7e0e0202,
	0x7e100201, 0x7e120200,
	0x7e140209, 0x7e160208,
	0x7e180207, 0x7e1a0206,
	0x7e1c0205, 0x7e1e0204,
	0x7e200203, 0x7e220202,
	0x7e240201, 0x7e260200,
	0x7e280209, 0x7e2a0208,
	0x7e2c0207, 0x7e2e0206,
	0x7e300205, 0x7e320204,
	0x7e340203, 0x7e360202,
	0x7e380201, 0x7e3a0200,
	0x7e3c0209, 0x7e3e0208,
	0x7e400207, 0x7e420206,
	0x7e440205, 0x7e460204,
	0x7e480203, 0x7e4a0202,
	0x7e4c0201, 0x7e4e0200,
	0x7e500209, 0x7e520208,
	0x7e540207, 0x7e560206,
	0x7e580205, 0x7e5a0204,
	0x7e5c0203, 0x7e5e0202,
	0x7e600201, 0x7e620200,
	0x7e640209, 0x7e660208,
	0x7e680207, 0x7e6a0206,
	0x7e6c0205, 0x7e6e0204,
	0x7e700203, 0x7e720202,
	0x7e740201, 0x7e760200,
	0x7e780209, 0x7e7a0208,
	0x7e7c0207, 0x7e7e0206,
	0xbf8a0000, 0xbf810000,
पूर्ण;

अटल स्थिर u32 sgpr_init_compute_shader[] =
अणु
	0xbe8a0100, 0xbe8c0102,
	0xbe8e0104, 0xbe900106,
	0xbe920108, 0xbe940100,
	0xbe960102, 0xbe980104,
	0xbe9a0106, 0xbe9c0108,
	0xbe9e0100, 0xbea00102,
	0xbea20104, 0xbea40106,
	0xbea60108, 0xbea80100,
	0xbeaa0102, 0xbeac0104,
	0xbeae0106, 0xbeb00108,
	0xbeb20100, 0xbeb40102,
	0xbeb60104, 0xbeb80106,
	0xbeba0108, 0xbebc0100,
	0xbebe0102, 0xbec00104,
	0xbec20106, 0xbec40108,
	0xbec60100, 0xbec80102,
	0xbee60004, 0xbee70005,
	0xbeea0006, 0xbeeb0007,
	0xbee80008, 0xbee90009,
	0xbefc0000, 0xbf8a0000,
	0xbf810000, 0x00000000,
पूर्ण;

अटल स्थिर u32 vgpr_init_regs[] =
अणु
	mmCOMPUTE_STATIC_THREAD_MGMT_SE0, 0xffffffff,
	mmCOMPUTE_RESOURCE_LIMITS, 0x1000000, /* CU_GROUP_COUNT=1 */
	mmCOMPUTE_NUM_THREAD_X, 256*4,
	mmCOMPUTE_NUM_THREAD_Y, 1,
	mmCOMPUTE_NUM_THREAD_Z, 1,
	mmCOMPUTE_PGM_RSRC1, 0x100004f, /* VGPRS=15 (64 logical VGPRs), SGPRS=1 (16 SGPRs), BULKY=1 */
	mmCOMPUTE_PGM_RSRC2, 20,
	mmCOMPUTE_USER_DATA_0, 0xedcedc00,
	mmCOMPUTE_USER_DATA_1, 0xedcedc01,
	mmCOMPUTE_USER_DATA_2, 0xedcedc02,
	mmCOMPUTE_USER_DATA_3, 0xedcedc03,
	mmCOMPUTE_USER_DATA_4, 0xedcedc04,
	mmCOMPUTE_USER_DATA_5, 0xedcedc05,
	mmCOMPUTE_USER_DATA_6, 0xedcedc06,
	mmCOMPUTE_USER_DATA_7, 0xedcedc07,
	mmCOMPUTE_USER_DATA_8, 0xedcedc08,
	mmCOMPUTE_USER_DATA_9, 0xedcedc09,
पूर्ण;

अटल स्थिर u32 sgpr1_init_regs[] =
अणु
	mmCOMPUTE_STATIC_THREAD_MGMT_SE0, 0x0f,
	mmCOMPUTE_RESOURCE_LIMITS, 0x1000000, /* CU_GROUP_COUNT=1 */
	mmCOMPUTE_NUM_THREAD_X, 256*5,
	mmCOMPUTE_NUM_THREAD_Y, 1,
	mmCOMPUTE_NUM_THREAD_Z, 1,
	mmCOMPUTE_PGM_RSRC1, 0x240, /* SGPRS=9 (80 GPRS) */
	mmCOMPUTE_PGM_RSRC2, 20,
	mmCOMPUTE_USER_DATA_0, 0xedcedc00,
	mmCOMPUTE_USER_DATA_1, 0xedcedc01,
	mmCOMPUTE_USER_DATA_2, 0xedcedc02,
	mmCOMPUTE_USER_DATA_3, 0xedcedc03,
	mmCOMPUTE_USER_DATA_4, 0xedcedc04,
	mmCOMPUTE_USER_DATA_5, 0xedcedc05,
	mmCOMPUTE_USER_DATA_6, 0xedcedc06,
	mmCOMPUTE_USER_DATA_7, 0xedcedc07,
	mmCOMPUTE_USER_DATA_8, 0xedcedc08,
	mmCOMPUTE_USER_DATA_9, 0xedcedc09,
पूर्ण;

अटल स्थिर u32 sgpr2_init_regs[] =
अणु
	mmCOMPUTE_STATIC_THREAD_MGMT_SE0, 0xf0,
	mmCOMPUTE_RESOURCE_LIMITS, 0x1000000,
	mmCOMPUTE_NUM_THREAD_X, 256*5,
	mmCOMPUTE_NUM_THREAD_Y, 1,
	mmCOMPUTE_NUM_THREAD_Z, 1,
	mmCOMPUTE_PGM_RSRC1, 0x240, /* SGPRS=9 (80 GPRS) */
	mmCOMPUTE_PGM_RSRC2, 20,
	mmCOMPUTE_USER_DATA_0, 0xedcedc00,
	mmCOMPUTE_USER_DATA_1, 0xedcedc01,
	mmCOMPUTE_USER_DATA_2, 0xedcedc02,
	mmCOMPUTE_USER_DATA_3, 0xedcedc03,
	mmCOMPUTE_USER_DATA_4, 0xedcedc04,
	mmCOMPUTE_USER_DATA_5, 0xedcedc05,
	mmCOMPUTE_USER_DATA_6, 0xedcedc06,
	mmCOMPUTE_USER_DATA_7, 0xedcedc07,
	mmCOMPUTE_USER_DATA_8, 0xedcedc08,
	mmCOMPUTE_USER_DATA_9, 0xedcedc09,
पूर्ण;

अटल स्थिर u32 sec_ded_counter_रेजिस्टरs[] =
अणु
	mmCPC_EDC_ATC_CNT,
	mmCPC_EDC_SCRATCH_CNT,
	mmCPC_EDC_UCODE_CNT,
	mmCPF_EDC_ATC_CNT,
	mmCPF_EDC_ROQ_CNT,
	mmCPF_EDC_TAG_CNT,
	mmCPG_EDC_ATC_CNT,
	mmCPG_EDC_DMA_CNT,
	mmCPG_EDC_TAG_CNT,
	mmDC_EDC_CSINVOC_CNT,
	mmDC_EDC_RESTORE_CNT,
	mmDC_EDC_STATE_CNT,
	mmGDS_EDC_CNT,
	mmGDS_EDC_GRBM_CNT,
	mmGDS_EDC_OA_DED,
	mmSPI_EDC_CNT,
	mmSQC_ATC_EDC_GATCL1_CNT,
	mmSQC_EDC_CNT,
	mmSQ_EDC_DED_CNT,
	mmSQ_EDC_INFO,
	mmSQ_EDC_SEC_CNT,
	mmTCC_EDC_CNT,
	mmTCP_ATC_EDC_GATCL1_CNT,
	mmTCP_EDC_CNT,
	mmTD_EDC_CNT
पूर्ण;

अटल पूर्णांक gfx_v8_0_करो_edc_gpr_workarounds(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ring *ring = &adev->gfx.compute_ring[0];
	काष्ठा amdgpu_ib ib;
	काष्ठा dma_fence *f = शून्य;
	पूर्णांक r, i;
	u32 पंचांगp;
	अचिन्हित total_size, vgpr_offset, sgpr_offset;
	u64 gpu_addr;

	/* only supported on CZ */
	अगर (adev->asic_type != CHIP_CARRIZO)
		वापस 0;

	/* bail अगर the compute ring is not पढ़ोy */
	अगर (!ring->sched.पढ़ोy)
		वापस 0;

	पंचांगp = RREG32(mmGB_EDC_MODE);
	WREG32(mmGB_EDC_MODE, 0);

	total_size =
		(((ARRAY_SIZE(vgpr_init_regs) / 2) * 3) + 4 + 5 + 2) * 4;
	total_size +=
		(((ARRAY_SIZE(sgpr1_init_regs) / 2) * 3) + 4 + 5 + 2) * 4;
	total_size +=
		(((ARRAY_SIZE(sgpr2_init_regs) / 2) * 3) + 4 + 5 + 2) * 4;
	total_size = ALIGN(total_size, 256);
	vgpr_offset = total_size;
	total_size += ALIGN(माप(vgpr_init_compute_shader), 256);
	sgpr_offset = total_size;
	total_size += माप(sgpr_init_compute_shader);

	/* allocate an indirect buffer to put the commands in */
	स_रखो(&ib, 0, माप(ib));
	r = amdgpu_ib_get(adev, शून्य, total_size,
					AMDGPU_IB_POOL_सूचीECT, &ib);
	अगर (r) अणु
		DRM_ERROR("amdgpu: failed to get ib (%d).\n", r);
		वापस r;
	पूर्ण

	/* load the compute shaders */
	क्रम (i = 0; i < ARRAY_SIZE(vgpr_init_compute_shader); i++)
		ib.ptr[i + (vgpr_offset / 4)] = vgpr_init_compute_shader[i];

	क्रम (i = 0; i < ARRAY_SIZE(sgpr_init_compute_shader); i++)
		ib.ptr[i + (sgpr_offset / 4)] = sgpr_init_compute_shader[i];

	/* init the ib length to 0 */
	ib.length_dw = 0;

	/* VGPR */
	/* ग_लिखो the रेजिस्टर state क्रम the compute dispatch */
	क्रम (i = 0; i < ARRAY_SIZE(vgpr_init_regs); i += 2) अणु
		ib.ptr[ib.length_dw++] = PACKET3(PACKET3_SET_SH_REG, 1);
		ib.ptr[ib.length_dw++] = vgpr_init_regs[i] - PACKET3_SET_SH_REG_START;
		ib.ptr[ib.length_dw++] = vgpr_init_regs[i + 1];
	पूर्ण
	/* ग_लिखो the shader start address: mmCOMPUTE_PGM_LO, mmCOMPUTE_PGM_HI */
	gpu_addr = (ib.gpu_addr + (u64)vgpr_offset) >> 8;
	ib.ptr[ib.length_dw++] = PACKET3(PACKET3_SET_SH_REG, 2);
	ib.ptr[ib.length_dw++] = mmCOMPUTE_PGM_LO - PACKET3_SET_SH_REG_START;
	ib.ptr[ib.length_dw++] = lower_32_bits(gpu_addr);
	ib.ptr[ib.length_dw++] = upper_32_bits(gpu_addr);

	/* ग_लिखो dispatch packet */
	ib.ptr[ib.length_dw++] = PACKET3(PACKET3_DISPATCH_सूचीECT, 3);
	ib.ptr[ib.length_dw++] = 8; /* x */
	ib.ptr[ib.length_dw++] = 1; /* y */
	ib.ptr[ib.length_dw++] = 1; /* z */
	ib.ptr[ib.length_dw++] =
		REG_SET_FIELD(0, COMPUTE_DISPATCH_INITIATOR, COMPUTE_SHADER_EN, 1);

	/* ग_लिखो CS partial flush packet */
	ib.ptr[ib.length_dw++] = PACKET3(PACKET3_EVENT_WRITE, 0);
	ib.ptr[ib.length_dw++] = EVENT_TYPE(7) | EVENT_INDEX(4);

	/* SGPR1 */
	/* ग_लिखो the रेजिस्टर state क्रम the compute dispatch */
	क्रम (i = 0; i < ARRAY_SIZE(sgpr1_init_regs); i += 2) अणु
		ib.ptr[ib.length_dw++] = PACKET3(PACKET3_SET_SH_REG, 1);
		ib.ptr[ib.length_dw++] = sgpr1_init_regs[i] - PACKET3_SET_SH_REG_START;
		ib.ptr[ib.length_dw++] = sgpr1_init_regs[i + 1];
	पूर्ण
	/* ग_लिखो the shader start address: mmCOMPUTE_PGM_LO, mmCOMPUTE_PGM_HI */
	gpu_addr = (ib.gpu_addr + (u64)sgpr_offset) >> 8;
	ib.ptr[ib.length_dw++] = PACKET3(PACKET3_SET_SH_REG, 2);
	ib.ptr[ib.length_dw++] = mmCOMPUTE_PGM_LO - PACKET3_SET_SH_REG_START;
	ib.ptr[ib.length_dw++] = lower_32_bits(gpu_addr);
	ib.ptr[ib.length_dw++] = upper_32_bits(gpu_addr);

	/* ग_लिखो dispatch packet */
	ib.ptr[ib.length_dw++] = PACKET3(PACKET3_DISPATCH_सूचीECT, 3);
	ib.ptr[ib.length_dw++] = 8; /* x */
	ib.ptr[ib.length_dw++] = 1; /* y */
	ib.ptr[ib.length_dw++] = 1; /* z */
	ib.ptr[ib.length_dw++] =
		REG_SET_FIELD(0, COMPUTE_DISPATCH_INITIATOR, COMPUTE_SHADER_EN, 1);

	/* ग_लिखो CS partial flush packet */
	ib.ptr[ib.length_dw++] = PACKET3(PACKET3_EVENT_WRITE, 0);
	ib.ptr[ib.length_dw++] = EVENT_TYPE(7) | EVENT_INDEX(4);

	/* SGPR2 */
	/* ग_लिखो the रेजिस्टर state क्रम the compute dispatch */
	क्रम (i = 0; i < ARRAY_SIZE(sgpr2_init_regs); i += 2) अणु
		ib.ptr[ib.length_dw++] = PACKET3(PACKET3_SET_SH_REG, 1);
		ib.ptr[ib.length_dw++] = sgpr2_init_regs[i] - PACKET3_SET_SH_REG_START;
		ib.ptr[ib.length_dw++] = sgpr2_init_regs[i + 1];
	पूर्ण
	/* ग_लिखो the shader start address: mmCOMPUTE_PGM_LO, mmCOMPUTE_PGM_HI */
	gpu_addr = (ib.gpu_addr + (u64)sgpr_offset) >> 8;
	ib.ptr[ib.length_dw++] = PACKET3(PACKET3_SET_SH_REG, 2);
	ib.ptr[ib.length_dw++] = mmCOMPUTE_PGM_LO - PACKET3_SET_SH_REG_START;
	ib.ptr[ib.length_dw++] = lower_32_bits(gpu_addr);
	ib.ptr[ib.length_dw++] = upper_32_bits(gpu_addr);

	/* ग_लिखो dispatch packet */
	ib.ptr[ib.length_dw++] = PACKET3(PACKET3_DISPATCH_सूचीECT, 3);
	ib.ptr[ib.length_dw++] = 8; /* x */
	ib.ptr[ib.length_dw++] = 1; /* y */
	ib.ptr[ib.length_dw++] = 1; /* z */
	ib.ptr[ib.length_dw++] =
		REG_SET_FIELD(0, COMPUTE_DISPATCH_INITIATOR, COMPUTE_SHADER_EN, 1);

	/* ग_लिखो CS partial flush packet */
	ib.ptr[ib.length_dw++] = PACKET3(PACKET3_EVENT_WRITE, 0);
	ib.ptr[ib.length_dw++] = EVENT_TYPE(7) | EVENT_INDEX(4);

	/* shedule the ib on the ring */
	r = amdgpu_ib_schedule(ring, 1, &ib, शून्य, &f);
	अगर (r) अणु
		DRM_ERROR("amdgpu: ib submit failed (%d).\n", r);
		जाओ fail;
	पूर्ण

	/* रुको क्रम the GPU to finish processing the IB */
	r = dma_fence_रुको(f, false);
	अगर (r) अणु
		DRM_ERROR("amdgpu: fence wait failed (%d).\n", r);
		जाओ fail;
	पूर्ण

	पंचांगp = REG_SET_FIELD(पंचांगp, GB_EDC_MODE, DED_MODE, 2);
	पंचांगp = REG_SET_FIELD(पंचांगp, GB_EDC_MODE, PROP_FED, 1);
	WREG32(mmGB_EDC_MODE, पंचांगp);

	पंचांगp = RREG32(mmCC_GC_EDC_CONFIG);
	पंचांगp = REG_SET_FIELD(पंचांगp, CC_GC_EDC_CONFIG, DIS_EDC, 0) | 1;
	WREG32(mmCC_GC_EDC_CONFIG, पंचांगp);


	/* पढ़ो back रेजिस्टरs to clear the counters */
	क्रम (i = 0; i < ARRAY_SIZE(sec_ded_counter_रेजिस्टरs); i++)
		RREG32(sec_ded_counter_रेजिस्टरs[i]);

fail:
	amdgpu_ib_मुक्त(adev, &ib, शून्य);
	dma_fence_put(f);

	वापस r;
पूर्ण

अटल पूर्णांक gfx_v8_0_gpu_early_init(काष्ठा amdgpu_device *adev)
अणु
	u32 gb_addr_config;
	u32 mc_arb_ramcfg;
	u32 dimm00_addr_map, dimm01_addr_map, dimm10_addr_map, dimm11_addr_map;
	u32 पंचांगp;
	पूर्णांक ret;

	चयन (adev->asic_type) अणु
	हाल CHIP_TOPAZ:
		adev->gfx.config.max_shader_engines = 1;
		adev->gfx.config.max_tile_pipes = 2;
		adev->gfx.config.max_cu_per_sh = 6;
		adev->gfx.config.max_sh_per_se = 1;
		adev->gfx.config.max_backends_per_se = 2;
		adev->gfx.config.max_texture_channel_caches = 2;
		adev->gfx.config.max_gprs = 256;
		adev->gfx.config.max_gs_thपढ़ोs = 32;
		adev->gfx.config.max_hw_contexts = 8;

		adev->gfx.config.sc_prim_fअगरo_size_frontend = 0x20;
		adev->gfx.config.sc_prim_fअगरo_size_backend = 0x100;
		adev->gfx.config.sc_hiz_tile_fअगरo_size = 0x30;
		adev->gfx.config.sc_earlyz_tile_fअगरo_size = 0x130;
		gb_addr_config = TOPAZ_GB_ADDR_CONFIG_GOLDEN;
		अवरोध;
	हाल CHIP_FIJI:
		adev->gfx.config.max_shader_engines = 4;
		adev->gfx.config.max_tile_pipes = 16;
		adev->gfx.config.max_cu_per_sh = 16;
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
		gb_addr_config = TONGA_GB_ADDR_CONFIG_GOLDEN;
		अवरोध;
	हाल CHIP_POLARIS11:
	हाल CHIP_POLARIS12:
		ret = amdgpu_atombios_get_gfx_info(adev);
		अगर (ret)
			वापस ret;
		adev->gfx.config.max_gprs = 256;
		adev->gfx.config.max_gs_thपढ़ोs = 32;
		adev->gfx.config.max_hw_contexts = 8;

		adev->gfx.config.sc_prim_fअगरo_size_frontend = 0x20;
		adev->gfx.config.sc_prim_fअगरo_size_backend = 0x100;
		adev->gfx.config.sc_hiz_tile_fअगरo_size = 0x30;
		adev->gfx.config.sc_earlyz_tile_fअगरo_size = 0x130;
		gb_addr_config = POLARIS11_GB_ADDR_CONFIG_GOLDEN;
		अवरोध;
	हाल CHIP_POLARIS10:
	हाल CHIP_VEGAM:
		ret = amdgpu_atombios_get_gfx_info(adev);
		अगर (ret)
			वापस ret;
		adev->gfx.config.max_gprs = 256;
		adev->gfx.config.max_gs_thपढ़ोs = 32;
		adev->gfx.config.max_hw_contexts = 8;

		adev->gfx.config.sc_prim_fअगरo_size_frontend = 0x20;
		adev->gfx.config.sc_prim_fअगरo_size_backend = 0x100;
		adev->gfx.config.sc_hiz_tile_fअगरo_size = 0x30;
		adev->gfx.config.sc_earlyz_tile_fअगरo_size = 0x130;
		gb_addr_config = TONGA_GB_ADDR_CONFIG_GOLDEN;
		अवरोध;
	हाल CHIP_TONGA:
		adev->gfx.config.max_shader_engines = 4;
		adev->gfx.config.max_tile_pipes = 8;
		adev->gfx.config.max_cu_per_sh = 8;
		adev->gfx.config.max_sh_per_se = 1;
		adev->gfx.config.max_backends_per_se = 2;
		adev->gfx.config.max_texture_channel_caches = 8;
		adev->gfx.config.max_gprs = 256;
		adev->gfx.config.max_gs_thपढ़ोs = 32;
		adev->gfx.config.max_hw_contexts = 8;

		adev->gfx.config.sc_prim_fअगरo_size_frontend = 0x20;
		adev->gfx.config.sc_prim_fअगरo_size_backend = 0x100;
		adev->gfx.config.sc_hiz_tile_fअगरo_size = 0x30;
		adev->gfx.config.sc_earlyz_tile_fअगरo_size = 0x130;
		gb_addr_config = TONGA_GB_ADDR_CONFIG_GOLDEN;
		अवरोध;
	हाल CHIP_CARRIZO:
		adev->gfx.config.max_shader_engines = 1;
		adev->gfx.config.max_tile_pipes = 2;
		adev->gfx.config.max_sh_per_se = 1;
		adev->gfx.config.max_backends_per_se = 2;
		adev->gfx.config.max_cu_per_sh = 8;
		adev->gfx.config.max_texture_channel_caches = 2;
		adev->gfx.config.max_gprs = 256;
		adev->gfx.config.max_gs_thपढ़ोs = 32;
		adev->gfx.config.max_hw_contexts = 8;

		adev->gfx.config.sc_prim_fअगरo_size_frontend = 0x20;
		adev->gfx.config.sc_prim_fअगरo_size_backend = 0x100;
		adev->gfx.config.sc_hiz_tile_fअगरo_size = 0x30;
		adev->gfx.config.sc_earlyz_tile_fअगरo_size = 0x130;
		gb_addr_config = CARRIZO_GB_ADDR_CONFIG_GOLDEN;
		अवरोध;
	हाल CHIP_STONEY:
		adev->gfx.config.max_shader_engines = 1;
		adev->gfx.config.max_tile_pipes = 2;
		adev->gfx.config.max_sh_per_se = 1;
		adev->gfx.config.max_backends_per_se = 1;
		adev->gfx.config.max_cu_per_sh = 3;
		adev->gfx.config.max_texture_channel_caches = 2;
		adev->gfx.config.max_gprs = 256;
		adev->gfx.config.max_gs_thपढ़ोs = 16;
		adev->gfx.config.max_hw_contexts = 8;

		adev->gfx.config.sc_prim_fअगरo_size_frontend = 0x20;
		adev->gfx.config.sc_prim_fअगरo_size_backend = 0x100;
		adev->gfx.config.sc_hiz_tile_fअगरo_size = 0x30;
		adev->gfx.config.sc_earlyz_tile_fअगरo_size = 0x130;
		gb_addr_config = CARRIZO_GB_ADDR_CONFIG_GOLDEN;
		अवरोध;
	शेष:
		adev->gfx.config.max_shader_engines = 2;
		adev->gfx.config.max_tile_pipes = 4;
		adev->gfx.config.max_cu_per_sh = 2;
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
		gb_addr_config = TONGA_GB_ADDR_CONFIG_GOLDEN;
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
		पंचांगp = REG_GET_FIELD(mc_arb_ramcfg, MC_ARB_RAMCFG, NOOFCOLS);
		adev->gfx.config.mem_row_size_in_kb = (4 * (1 << (8 + पंचांगp))) / 1024;
		अगर (adev->gfx.config.mem_row_size_in_kb > 4)
			adev->gfx.config.mem_row_size_in_kb = 4;
	पूर्ण

	adev->gfx.config.shader_engine_tile_size = 32;
	adev->gfx.config.num_gpus = 1;
	adev->gfx.config.multi_gpu_tile_size = 64;

	/* fix up row size */
	चयन (adev->gfx.config.mem_row_size_in_kb) अणु
	हाल 1:
	शेष:
		gb_addr_config = REG_SET_FIELD(gb_addr_config, GB_ADDR_CONFIG, ROW_SIZE, 0);
		अवरोध;
	हाल 2:
		gb_addr_config = REG_SET_FIELD(gb_addr_config, GB_ADDR_CONFIG, ROW_SIZE, 1);
		अवरोध;
	हाल 4:
		gb_addr_config = REG_SET_FIELD(gb_addr_config, GB_ADDR_CONFIG, ROW_SIZE, 2);
		अवरोध;
	पूर्ण
	adev->gfx.config.gb_addr_config = gb_addr_config;

	वापस 0;
पूर्ण

अटल पूर्णांक gfx_v8_0_compute_ring_init(काष्ठा amdgpu_device *adev, पूर्णांक ring_id,
					पूर्णांक mec, पूर्णांक pipe, पूर्णांक queue)
अणु
	पूर्णांक r;
	अचिन्हित irq_type;
	काष्ठा amdgpu_ring *ring = &adev->gfx.compute_ring[ring_id];
	अचिन्हित पूर्णांक hw_prio;

	ring = &adev->gfx.compute_ring[ring_id];

	/* mec0 is me1 */
	ring->me = mec + 1;
	ring->pipe = pipe;
	ring->queue = queue;

	ring->ring_obj = शून्य;
	ring->use_करोorbell = true;
	ring->करोorbell_index = adev->करोorbell_index.mec_ring0 + ring_id;
	ring->eop_gpu_addr = adev->gfx.mec.hpd_eop_gpu_addr
				+ (ring_id * GFX8_MEC_HPD_SIZE);
	प्र_लिखो(ring->name, "comp_%d.%d.%d", ring->me, ring->pipe, ring->queue);

	irq_type = AMDGPU_CP_IRQ_COMPUTE_MEC1_PIPE0_EOP
		+ ((ring->me - 1) * adev->gfx.mec.num_pipe_per_mec)
		+ ring->pipe;

	hw_prio = amdgpu_gfx_is_high_priority_compute_queue(adev, ring) ?
			AMDGPU_GFX_PIPE_PRIO_HIGH : AMDGPU_RING_PRIO_DEFAULT;
	/* type-2 packets are deprecated on MEC, use type-3 instead */
	r = amdgpu_ring_init(adev, ring, 1024, &adev->gfx.eop_irq, irq_type,
			     hw_prio, शून्य);
	अगर (r)
		वापस r;


	वापस 0;
पूर्ण

अटल व्योम gfx_v8_0_sq_irq_work_func(काष्ठा work_काष्ठा *work);

अटल पूर्णांक gfx_v8_0_sw_init(व्योम *handle)
अणु
	पूर्णांक i, j, k, r, ring_id;
	काष्ठा amdgpu_ring *ring;
	काष्ठा amdgpu_kiq *kiq;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	चयन (adev->asic_type) अणु
	हाल CHIP_TONGA:
	हाल CHIP_CARRIZO:
	हाल CHIP_FIJI:
	हाल CHIP_POLARIS10:
	हाल CHIP_POLARIS11:
	हाल CHIP_POLARIS12:
	हाल CHIP_VEGAM:
		adev->gfx.mec.num_mec = 2;
		अवरोध;
	हाल CHIP_TOPAZ:
	हाल CHIP_STONEY:
	शेष:
		adev->gfx.mec.num_mec = 1;
		अवरोध;
	पूर्ण

	adev->gfx.mec.num_pipe_per_mec = 4;
	adev->gfx.mec.num_queue_per_pipe = 8;

	/* EOP Event */
	r = amdgpu_irq_add_id(adev, AMDGPU_IRQ_CLIENTID_LEGACY, VISLANDS30_IV_SRCID_CP_END_OF_PIPE, &adev->gfx.eop_irq);
	अगर (r)
		वापस r;

	/* Privileged reg */
	r = amdgpu_irq_add_id(adev, AMDGPU_IRQ_CLIENTID_LEGACY, VISLANDS30_IV_SRCID_CP_PRIV_REG_FAULT,
			      &adev->gfx.priv_reg_irq);
	अगर (r)
		वापस r;

	/* Privileged inst */
	r = amdgpu_irq_add_id(adev, AMDGPU_IRQ_CLIENTID_LEGACY, VISLANDS30_IV_SRCID_CP_PRIV_INSTR_FAULT,
			      &adev->gfx.priv_inst_irq);
	अगर (r)
		वापस r;

	/* Add CP EDC/ECC irq  */
	r = amdgpu_irq_add_id(adev, AMDGPU_IRQ_CLIENTID_LEGACY, VISLANDS30_IV_SRCID_CP_ECC_ERROR,
			      &adev->gfx.cp_ecc_error_irq);
	अगर (r)
		वापस r;

	/* SQ पूर्णांकerrupts. */
	r = amdgpu_irq_add_id(adev, AMDGPU_IRQ_CLIENTID_LEGACY, VISLANDS30_IV_SRCID_SQ_INTERRUPT_MSG,
			      &adev->gfx.sq_irq);
	अगर (r) अणु
		DRM_ERROR("amdgpu_irq_add() for SQ failed: %d\n", r);
		वापस r;
	पूर्ण

	INIT_WORK(&adev->gfx.sq_work.work, gfx_v8_0_sq_irq_work_func);

	adev->gfx.gfx_current_status = AMDGPU_GFX_NORMAL_MODE;

	gfx_v8_0_scratch_init(adev);

	r = gfx_v8_0_init_microcode(adev);
	अगर (r) अणु
		DRM_ERROR("Failed to load gfx firmware!\n");
		वापस r;
	पूर्ण

	r = adev->gfx.rlc.funcs->init(adev);
	अगर (r) अणु
		DRM_ERROR("Failed to init rlc BOs!\n");
		वापस r;
	पूर्ण

	r = gfx_v8_0_mec_init(adev);
	अगर (r) अणु
		DRM_ERROR("Failed to init MEC BOs!\n");
		वापस r;
	पूर्ण

	/* set up the gfx ring */
	क्रम (i = 0; i < adev->gfx.num_gfx_rings; i++) अणु
		ring = &adev->gfx.gfx_ring[i];
		ring->ring_obj = शून्य;
		प्र_लिखो(ring->name, "gfx");
		/* no gfx करोorbells on iceland */
		अगर (adev->asic_type != CHIP_TOPAZ) अणु
			ring->use_करोorbell = true;
			ring->करोorbell_index = adev->करोorbell_index.gfx_ring0;
		पूर्ण

		r = amdgpu_ring_init(adev, ring, 1024, &adev->gfx.eop_irq,
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

				r = gfx_v8_0_compute_ring_init(adev,
								ring_id,
								i, k, j);
				अगर (r)
					वापस r;

				ring_id++;
			पूर्ण
		पूर्ण
	पूर्ण

	r = amdgpu_gfx_kiq_init(adev, GFX8_MEC_HPD_SIZE);
	अगर (r) अणु
		DRM_ERROR("Failed to init KIQ BOs!\n");
		वापस r;
	पूर्ण

	kiq = &adev->gfx.kiq;
	r = amdgpu_gfx_kiq_init_ring(adev, &kiq->ring, &kiq->irq);
	अगर (r)
		वापस r;

	/* create MQD क्रम all compute queues as well as KIQ क्रम SRIOV हाल */
	r = amdgpu_gfx_mqd_sw_init(adev, माप(काष्ठा vi_mqd_allocation));
	अगर (r)
		वापस r;

	adev->gfx.ce_ram_size = 0x8000;

	r = gfx_v8_0_gpu_early_init(adev);
	अगर (r)
		वापस r;

	वापस 0;
पूर्ण

अटल पूर्णांक gfx_v8_0_sw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	पूर्णांक i;

	क्रम (i = 0; i < adev->gfx.num_gfx_rings; i++)
		amdgpu_ring_fini(&adev->gfx.gfx_ring[i]);
	क्रम (i = 0; i < adev->gfx.num_compute_rings; i++)
		amdgpu_ring_fini(&adev->gfx.compute_ring[i]);

	amdgpu_gfx_mqd_sw_fini(adev);
	amdgpu_gfx_kiq_मुक्त_ring(&adev->gfx.kiq.ring);
	amdgpu_gfx_kiq_fini(adev);

	gfx_v8_0_mec_fini(adev);
	amdgpu_gfx_rlc_fini(adev);
	amdgpu_bo_मुक्त_kernel(&adev->gfx.rlc.clear_state_obj,
				&adev->gfx.rlc.clear_state_gpu_addr,
				(व्योम **)&adev->gfx.rlc.cs_ptr);
	अगर ((adev->asic_type == CHIP_CARRIZO) ||
	    (adev->asic_type == CHIP_STONEY)) अणु
		amdgpu_bo_मुक्त_kernel(&adev->gfx.rlc.cp_table_obj,
				&adev->gfx.rlc.cp_table_gpu_addr,
				(व्योम **)&adev->gfx.rlc.cp_table_ptr);
	पूर्ण
	gfx_v8_0_मुक्त_microcode(adev);

	वापस 0;
पूर्ण

अटल व्योम gfx_v8_0_tiling_mode_table_init(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक32_t *modearray, *mod2array;
	स्थिर u32 num_tile_mode_states = ARRAY_SIZE(adev->gfx.config.tile_mode_array);
	स्थिर u32 num_secondary_tile_mode_states = ARRAY_SIZE(adev->gfx.config.macrotile_mode_array);
	u32 reg_offset;

	modearray = adev->gfx.config.tile_mode_array;
	mod2array = adev->gfx.config.macrotile_mode_array;

	क्रम (reg_offset = 0; reg_offset < num_tile_mode_states; reg_offset++)
		modearray[reg_offset] = 0;

	क्रम (reg_offset = 0; reg_offset <  num_secondary_tile_mode_states; reg_offset++)
		mod2array[reg_offset] = 0;

	चयन (adev->asic_type) अणु
	हाल CHIP_TOPAZ:
		modearray[0] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P2) |
				TILE_SPLIT(ADDR_SURF_TILE_SPLIT_64B) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		modearray[1] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P2) |
				TILE_SPLIT(ADDR_SURF_TILE_SPLIT_128B) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		modearray[2] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P2) |
				TILE_SPLIT(ADDR_SURF_TILE_SPLIT_256B) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		modearray[3] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P2) |
				TILE_SPLIT(ADDR_SURF_TILE_SPLIT_512B) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		modearray[4] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P2) |
				TILE_SPLIT(ADDR_SURF_TILE_SPLIT_2KB) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		modearray[5] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P2) |
				TILE_SPLIT(ADDR_SURF_TILE_SPLIT_2KB) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		modearray[6] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P2) |
				TILE_SPLIT(ADDR_SURF_TILE_SPLIT_2KB) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		modearray[8] = (ARRAY_MODE(ARRAY_LINEAR_ALIGNED) |
				PIPE_CONFIG(ADDR_SURF_P2));
		modearray[9] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P2) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DISPLAY_MICRO_TILING) |
				SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		modearray[10] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
				 PIPE_CONFIG(ADDR_SURF_P2) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_DISPLAY_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		modearray[11] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
				 PIPE_CONFIG(ADDR_SURF_P2) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_DISPLAY_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_8));
		modearray[13] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
				 PIPE_CONFIG(ADDR_SURF_P2) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		modearray[14] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
				 PIPE_CONFIG(ADDR_SURF_P2) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		modearray[15] = (ARRAY_MODE(ARRAY_3D_TILED_THIN1) |
				 PIPE_CONFIG(ADDR_SURF_P2) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		modearray[16] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
				 PIPE_CONFIG(ADDR_SURF_P2) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_8));
		modearray[18] = (ARRAY_MODE(ARRAY_1D_TILED_THICK) |
				 PIPE_CONFIG(ADDR_SURF_P2) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		modearray[19] = (ARRAY_MODE(ARRAY_1D_TILED_THICK) |
				 PIPE_CONFIG(ADDR_SURF_P2) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THICK_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		modearray[20] = (ARRAY_MODE(ARRAY_2D_TILED_THICK) |
				 PIPE_CONFIG(ADDR_SURF_P2) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THICK_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		modearray[21] = (ARRAY_MODE(ARRAY_3D_TILED_THICK) |
				 PIPE_CONFIG(ADDR_SURF_P2) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THICK_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		modearray[22] = (ARRAY_MODE(ARRAY_PRT_TILED_THICK) |
				 PIPE_CONFIG(ADDR_SURF_P2) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THICK_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		modearray[24] = (ARRAY_MODE(ARRAY_2D_TILED_THICK) |
				 PIPE_CONFIG(ADDR_SURF_P2) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		modearray[25] = (ARRAY_MODE(ARRAY_2D_TILED_XTHICK) |
				 PIPE_CONFIG(ADDR_SURF_P2) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THICK_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		modearray[26] = (ARRAY_MODE(ARRAY_3D_TILED_XTHICK) |
				 PIPE_CONFIG(ADDR_SURF_P2) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THICK_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		modearray[27] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
				 PIPE_CONFIG(ADDR_SURF_P2) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_ROTATED_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		modearray[28] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
				 PIPE_CONFIG(ADDR_SURF_P2) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_ROTATED_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		modearray[29] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
				 PIPE_CONFIG(ADDR_SURF_P2) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_ROTATED_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_8));

		mod2array[0] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_4) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				NUM_BANKS(ADDR_SURF_8_BANK));
		mod2array[1] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_4) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				NUM_BANKS(ADDR_SURF_8_BANK));
		mod2array[2] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_2) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				NUM_BANKS(ADDR_SURF_8_BANK));
		mod2array[3] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_8_BANK));
		mod2array[4] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_2) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				NUM_BANKS(ADDR_SURF_8_BANK));
		mod2array[5] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				NUM_BANKS(ADDR_SURF_8_BANK));
		mod2array[6] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				NUM_BANKS(ADDR_SURF_8_BANK));
		mod2array[8] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_4) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_8) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		mod2array[9] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_4) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		mod2array[10] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_2) |
				 BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
				 MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				 NUM_BANKS(ADDR_SURF_16_BANK));
		mod2array[11] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_2) |
				 BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_2) |
				 MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				 NUM_BANKS(ADDR_SURF_16_BANK));
		mod2array[12] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				 BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_2) |
				 MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				 NUM_BANKS(ADDR_SURF_16_BANK));
		mod2array[13] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				 BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				 MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				 NUM_BANKS(ADDR_SURF_16_BANK));
		mod2array[14] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				 BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				 MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				 NUM_BANKS(ADDR_SURF_8_BANK));

		क्रम (reg_offset = 0; reg_offset < num_tile_mode_states; reg_offset++)
			अगर (reg_offset != 7 && reg_offset != 12 && reg_offset != 17 &&
			    reg_offset != 23)
				WREG32(mmGB_TILE_MODE0 + reg_offset, modearray[reg_offset]);

		क्रम (reg_offset = 0; reg_offset < num_secondary_tile_mode_states; reg_offset++)
			अगर (reg_offset != 7)
				WREG32(mmGB_MACROTILE_MODE0 + reg_offset, mod2array[reg_offset]);

		अवरोध;
	हाल CHIP_FIJI:
	हाल CHIP_VEGAM:
		modearray[0] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
				TILE_SPLIT(ADDR_SURF_TILE_SPLIT_64B) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		modearray[1] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
				TILE_SPLIT(ADDR_SURF_TILE_SPLIT_128B) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		modearray[2] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
				TILE_SPLIT(ADDR_SURF_TILE_SPLIT_256B) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		modearray[3] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
				TILE_SPLIT(ADDR_SURF_TILE_SPLIT_512B) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		modearray[4] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
				TILE_SPLIT(ADDR_SURF_TILE_SPLIT_2KB) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		modearray[5] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
				TILE_SPLIT(ADDR_SURF_TILE_SPLIT_2KB) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		modearray[6] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
				TILE_SPLIT(ADDR_SURF_TILE_SPLIT_2KB) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		modearray[7] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P4_16x16) |
				TILE_SPLIT(ADDR_SURF_TILE_SPLIT_2KB) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		modearray[8] = (ARRAY_MODE(ARRAY_LINEAR_ALIGNED) |
				PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16));
		modearray[9] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DISPLAY_MICRO_TILING) |
				SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		modearray[10] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
				 PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_DISPLAY_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		modearray[11] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
				 PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_DISPLAY_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_8));
		modearray[12] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
				 PIPE_CONFIG(ADDR_SURF_P4_16x16) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_DISPLAY_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_8));
		modearray[13] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
				 PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		modearray[14] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
				 PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		modearray[15] = (ARRAY_MODE(ARRAY_3D_TILED_THIN1) |
				 PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		modearray[16] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
				 PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_8));
		modearray[17] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
				 PIPE_CONFIG(ADDR_SURF_P4_16x16) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_8));
		modearray[18] = (ARRAY_MODE(ARRAY_1D_TILED_THICK) |
				 PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		modearray[19] = (ARRAY_MODE(ARRAY_1D_TILED_THICK) |
				 PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THICK_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		modearray[20] = (ARRAY_MODE(ARRAY_2D_TILED_THICK) |
				 PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THICK_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		modearray[21] = (ARRAY_MODE(ARRAY_3D_TILED_THICK) |
				 PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THICK_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		modearray[22] = (ARRAY_MODE(ARRAY_PRT_TILED_THICK) |
				 PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THICK_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		modearray[23] = (ARRAY_MODE(ARRAY_PRT_TILED_THICK) |
				 PIPE_CONFIG(ADDR_SURF_P4_16x16) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THICK_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		modearray[24] = (ARRAY_MODE(ARRAY_2D_TILED_THICK) |
				 PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		modearray[25] = (ARRAY_MODE(ARRAY_2D_TILED_XTHICK) |
				 PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THICK_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		modearray[26] = (ARRAY_MODE(ARRAY_3D_TILED_XTHICK) |
				 PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THICK_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		modearray[27] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
				 PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_ROTATED_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		modearray[28] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
				 PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_ROTATED_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		modearray[29] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
				 PIPE_CONFIG(ADDR_SURF_P16_32x32_16x16) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_ROTATED_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_8));
		modearray[30] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
				 PIPE_CONFIG(ADDR_SURF_P4_16x16) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_ROTATED_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_8));

		mod2array[0] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				NUM_BANKS(ADDR_SURF_8_BANK));
		mod2array[1] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				NUM_BANKS(ADDR_SURF_8_BANK));
		mod2array[2] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				NUM_BANKS(ADDR_SURF_8_BANK));
		mod2array[3] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				NUM_BANKS(ADDR_SURF_8_BANK));
		mod2array[4] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_2) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_1) |
				NUM_BANKS(ADDR_SURF_8_BANK));
		mod2array[5] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_1) |
				NUM_BANKS(ADDR_SURF_8_BANK));
		mod2array[6] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_1) |
				NUM_BANKS(ADDR_SURF_8_BANK));
		mod2array[8] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_8) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				NUM_BANKS(ADDR_SURF_8_BANK));
		mod2array[9] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				NUM_BANKS(ADDR_SURF_8_BANK));
		mod2array[10] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				 BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_2) |
				 MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_1) |
				 NUM_BANKS(ADDR_SURF_8_BANK));
		mod2array[11] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				 BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				 MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_1) |
				 NUM_BANKS(ADDR_SURF_8_BANK));
		mod2array[12] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				 BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_2) |
				 MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				 NUM_BANKS(ADDR_SURF_8_BANK));
		mod2array[13] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				 BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				 MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				 NUM_BANKS(ADDR_SURF_8_BANK));
		mod2array[14] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				 BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				 MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_1) |
				 NUM_BANKS(ADDR_SURF_4_BANK));

		क्रम (reg_offset = 0; reg_offset < num_tile_mode_states; reg_offset++)
			WREG32(mmGB_TILE_MODE0 + reg_offset, modearray[reg_offset]);

		क्रम (reg_offset = 0; reg_offset < num_secondary_tile_mode_states; reg_offset++)
			अगर (reg_offset != 7)
				WREG32(mmGB_MACROTILE_MODE0 + reg_offset, mod2array[reg_offset]);

		अवरोध;
	हाल CHIP_TONGA:
		modearray[0] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
				TILE_SPLIT(ADDR_SURF_TILE_SPLIT_64B) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		modearray[1] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
				TILE_SPLIT(ADDR_SURF_TILE_SPLIT_128B) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		modearray[2] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
				TILE_SPLIT(ADDR_SURF_TILE_SPLIT_256B) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		modearray[3] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
				TILE_SPLIT(ADDR_SURF_TILE_SPLIT_512B) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		modearray[4] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
				TILE_SPLIT(ADDR_SURF_TILE_SPLIT_2KB) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		modearray[5] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
				TILE_SPLIT(ADDR_SURF_TILE_SPLIT_2KB) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		modearray[6] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
				TILE_SPLIT(ADDR_SURF_TILE_SPLIT_2KB) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		modearray[7] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P4_16x16) |
				TILE_SPLIT(ADDR_SURF_TILE_SPLIT_2KB) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		modearray[8] = (ARRAY_MODE(ARRAY_LINEAR_ALIGNED) |
				PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16));
		modearray[9] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DISPLAY_MICRO_TILING) |
				SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		modearray[10] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
				 PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_DISPLAY_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		modearray[11] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
				 PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_DISPLAY_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_8));
		modearray[12] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
				 PIPE_CONFIG(ADDR_SURF_P4_16x16) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_DISPLAY_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_8));
		modearray[13] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
				 PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		modearray[14] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
				 PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		modearray[15] = (ARRAY_MODE(ARRAY_3D_TILED_THIN1) |
				 PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		modearray[16] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
				 PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_8));
		modearray[17] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
				 PIPE_CONFIG(ADDR_SURF_P4_16x16) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_8));
		modearray[18] = (ARRAY_MODE(ARRAY_1D_TILED_THICK) |
				 PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		modearray[19] = (ARRAY_MODE(ARRAY_1D_TILED_THICK) |
				 PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THICK_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		modearray[20] = (ARRAY_MODE(ARRAY_2D_TILED_THICK) |
				 PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THICK_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		modearray[21] = (ARRAY_MODE(ARRAY_3D_TILED_THICK) |
				 PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THICK_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		modearray[22] = (ARRAY_MODE(ARRAY_PRT_TILED_THICK) |
				 PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THICK_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		modearray[23] = (ARRAY_MODE(ARRAY_PRT_TILED_THICK) |
				 PIPE_CONFIG(ADDR_SURF_P4_16x16) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THICK_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		modearray[24] = (ARRAY_MODE(ARRAY_2D_TILED_THICK) |
				 PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		modearray[25] = (ARRAY_MODE(ARRAY_2D_TILED_XTHICK) |
				 PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THICK_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		modearray[26] = (ARRAY_MODE(ARRAY_3D_TILED_XTHICK) |
				 PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THICK_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		modearray[27] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
				 PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_ROTATED_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		modearray[28] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
				 PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_ROTATED_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		modearray[29] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
				 PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_ROTATED_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_8));
		modearray[30] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
				 PIPE_CONFIG(ADDR_SURF_P4_16x16) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_ROTATED_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_8));

		mod2array[0] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		mod2array[1] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		mod2array[2] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		mod2array[3] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		mod2array[4] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_2) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		mod2array[5] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_1) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		mod2array[6] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_1) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		mod2array[8] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_8) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		mod2array[9] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		mod2array[10] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				 BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_2) |
				 MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				 NUM_BANKS(ADDR_SURF_16_BANK));
		mod2array[11] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				 BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				 MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				 NUM_BANKS(ADDR_SURF_16_BANK));
		mod2array[12] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				 BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				 MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_1) |
				 NUM_BANKS(ADDR_SURF_8_BANK));
		mod2array[13] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				 BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				 MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_1) |
				 NUM_BANKS(ADDR_SURF_4_BANK));
		mod2array[14] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				 BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				 MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_1) |
				 NUM_BANKS(ADDR_SURF_4_BANK));

		क्रम (reg_offset = 0; reg_offset < num_tile_mode_states; reg_offset++)
			WREG32(mmGB_TILE_MODE0 + reg_offset, modearray[reg_offset]);

		क्रम (reg_offset = 0; reg_offset < num_secondary_tile_mode_states; reg_offset++)
			अगर (reg_offset != 7)
				WREG32(mmGB_MACROTILE_MODE0 + reg_offset, mod2array[reg_offset]);

		अवरोध;
	हाल CHIP_POLARIS11:
	हाल CHIP_POLARIS12:
		modearray[0] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P4_16x16) |
				TILE_SPLIT(ADDR_SURF_TILE_SPLIT_64B) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		modearray[1] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P4_16x16) |
				TILE_SPLIT(ADDR_SURF_TILE_SPLIT_128B) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		modearray[2] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P4_16x16) |
				TILE_SPLIT(ADDR_SURF_TILE_SPLIT_256B) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		modearray[3] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P4_16x16) |
				TILE_SPLIT(ADDR_SURF_TILE_SPLIT_512B) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		modearray[4] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P4_16x16) |
				TILE_SPLIT(ADDR_SURF_TILE_SPLIT_2KB) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		modearray[5] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P4_16x16) |
				TILE_SPLIT(ADDR_SURF_TILE_SPLIT_2KB) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		modearray[6] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P4_16x16) |
				TILE_SPLIT(ADDR_SURF_TILE_SPLIT_2KB) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		modearray[7] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P4_16x16) |
				TILE_SPLIT(ADDR_SURF_TILE_SPLIT_2KB) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		modearray[8] = (ARRAY_MODE(ARRAY_LINEAR_ALIGNED) |
				PIPE_CONFIG(ADDR_SURF_P4_16x16));
		modearray[9] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P4_16x16) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DISPLAY_MICRO_TILING) |
				SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		modearray[10] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P4_16x16) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DISPLAY_MICRO_TILING) |
				SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		modearray[11] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P4_16x16) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DISPLAY_MICRO_TILING) |
				SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_8));
		modearray[12] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P4_16x16) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DISPLAY_MICRO_TILING) |
				SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_8));
		modearray[13] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P4_16x16) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
				SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		modearray[14] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P4_16x16) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
				SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		modearray[15] = (ARRAY_MODE(ARRAY_3D_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P4_16x16) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
				SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		modearray[16] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P4_16x16) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
				SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_8));
		modearray[17] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P4_16x16) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
				SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_8));
		modearray[18] = (ARRAY_MODE(ARRAY_1D_TILED_THICK) |
				PIPE_CONFIG(ADDR_SURF_P4_16x16) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
				SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		modearray[19] = (ARRAY_MODE(ARRAY_1D_TILED_THICK) |
				PIPE_CONFIG(ADDR_SURF_P4_16x16) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_THICK_MICRO_TILING) |
				SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		modearray[20] = (ARRAY_MODE(ARRAY_2D_TILED_THICK) |
				PIPE_CONFIG(ADDR_SURF_P4_16x16) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_THICK_MICRO_TILING) |
				SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		modearray[21] = (ARRAY_MODE(ARRAY_3D_TILED_THICK) |
				PIPE_CONFIG(ADDR_SURF_P4_16x16) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_THICK_MICRO_TILING) |
				SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		modearray[22] = (ARRAY_MODE(ARRAY_PRT_TILED_THICK) |
				PIPE_CONFIG(ADDR_SURF_P4_16x16) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_THICK_MICRO_TILING) |
				SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		modearray[23] = (ARRAY_MODE(ARRAY_PRT_TILED_THICK) |
				PIPE_CONFIG(ADDR_SURF_P4_16x16) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_THICK_MICRO_TILING) |
				SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		modearray[24] = (ARRAY_MODE(ARRAY_2D_TILED_THICK) |
				PIPE_CONFIG(ADDR_SURF_P4_16x16) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
				SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		modearray[25] = (ARRAY_MODE(ARRAY_2D_TILED_XTHICK) |
				PIPE_CONFIG(ADDR_SURF_P4_16x16) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_THICK_MICRO_TILING) |
				SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		modearray[26] = (ARRAY_MODE(ARRAY_3D_TILED_XTHICK) |
				PIPE_CONFIG(ADDR_SURF_P4_16x16) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_THICK_MICRO_TILING) |
				SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		modearray[27] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P4_16x16) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_ROTATED_MICRO_TILING) |
				SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		modearray[28] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P4_16x16) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_ROTATED_MICRO_TILING) |
				SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		modearray[29] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P4_16x16) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_ROTATED_MICRO_TILING) |
				SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_8));
		modearray[30] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P4_16x16) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_ROTATED_MICRO_TILING) |
				SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_8));

		mod2array[0] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_16_BANK));

		mod2array[1] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_16_BANK));

		mod2array[2] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_16_BANK));

		mod2array[3] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_2) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_16_BANK));

		mod2array[4] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				NUM_BANKS(ADDR_SURF_16_BANK));

		mod2array[5] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				NUM_BANKS(ADDR_SURF_16_BANK));

		mod2array[6] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				NUM_BANKS(ADDR_SURF_16_BANK));

		mod2array[8] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_2) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_8) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_16_BANK));

		mod2array[9] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_2) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_16_BANK));

		mod2array[10] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_16_BANK));

		mod2array[11] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_2) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_16_BANK));

		mod2array[12] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				NUM_BANKS(ADDR_SURF_16_BANK));

		mod2array[13] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				NUM_BANKS(ADDR_SURF_8_BANK));

		mod2array[14] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_1) |
				NUM_BANKS(ADDR_SURF_4_BANK));

		क्रम (reg_offset = 0; reg_offset < num_tile_mode_states; reg_offset++)
			WREG32(mmGB_TILE_MODE0 + reg_offset, modearray[reg_offset]);

		क्रम (reg_offset = 0; reg_offset < num_secondary_tile_mode_states; reg_offset++)
			अगर (reg_offset != 7)
				WREG32(mmGB_MACROTILE_MODE0 + reg_offset, mod2array[reg_offset]);

		अवरोध;
	हाल CHIP_POLARIS10:
		modearray[0] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
				TILE_SPLIT(ADDR_SURF_TILE_SPLIT_64B) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		modearray[1] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
				TILE_SPLIT(ADDR_SURF_TILE_SPLIT_128B) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		modearray[2] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
				TILE_SPLIT(ADDR_SURF_TILE_SPLIT_256B) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		modearray[3] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
				TILE_SPLIT(ADDR_SURF_TILE_SPLIT_512B) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		modearray[4] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
				TILE_SPLIT(ADDR_SURF_TILE_SPLIT_2KB) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		modearray[5] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
				TILE_SPLIT(ADDR_SURF_TILE_SPLIT_2KB) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		modearray[6] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
				TILE_SPLIT(ADDR_SURF_TILE_SPLIT_2KB) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		modearray[7] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P4_16x16) |
				TILE_SPLIT(ADDR_SURF_TILE_SPLIT_2KB) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		modearray[8] = (ARRAY_MODE(ARRAY_LINEAR_ALIGNED) |
				PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16));
		modearray[9] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DISPLAY_MICRO_TILING) |
				SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		modearray[10] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DISPLAY_MICRO_TILING) |
				SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		modearray[11] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DISPLAY_MICRO_TILING) |
				SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_8));
		modearray[12] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P4_16x16) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DISPLAY_MICRO_TILING) |
				SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_8));
		modearray[13] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
				SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		modearray[14] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
				SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		modearray[15] = (ARRAY_MODE(ARRAY_3D_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
				SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		modearray[16] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
				SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_8));
		modearray[17] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P4_16x16) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
				SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_8));
		modearray[18] = (ARRAY_MODE(ARRAY_1D_TILED_THICK) |
				PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
				SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		modearray[19] = (ARRAY_MODE(ARRAY_1D_TILED_THICK) |
				PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_THICK_MICRO_TILING) |
				SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		modearray[20] = (ARRAY_MODE(ARRAY_2D_TILED_THICK) |
				PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_THICK_MICRO_TILING) |
				SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		modearray[21] = (ARRAY_MODE(ARRAY_3D_TILED_THICK) |
				PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_THICK_MICRO_TILING) |
				SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		modearray[22] = (ARRAY_MODE(ARRAY_PRT_TILED_THICK) |
				PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_THICK_MICRO_TILING) |
				SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		modearray[23] = (ARRAY_MODE(ARRAY_PRT_TILED_THICK) |
				PIPE_CONFIG(ADDR_SURF_P4_16x16) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_THICK_MICRO_TILING) |
				SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		modearray[24] = (ARRAY_MODE(ARRAY_2D_TILED_THICK) |
				PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
				SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		modearray[25] = (ARRAY_MODE(ARRAY_2D_TILED_XTHICK) |
				PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_THICK_MICRO_TILING) |
				SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		modearray[26] = (ARRAY_MODE(ARRAY_3D_TILED_XTHICK) |
				PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_THICK_MICRO_TILING) |
				SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		modearray[27] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_ROTATED_MICRO_TILING) |
				SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		modearray[28] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_ROTATED_MICRO_TILING) |
				SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		modearray[29] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P8_32x32_16x16) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_ROTATED_MICRO_TILING) |
				SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_8));
		modearray[30] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P4_16x16) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_ROTATED_MICRO_TILING) |
				SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_8));

		mod2array[0] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_16_BANK));

		mod2array[1] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_16_BANK));

		mod2array[2] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_16_BANK));

		mod2array[3] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_16_BANK));

		mod2array[4] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_2) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				NUM_BANKS(ADDR_SURF_16_BANK));

		mod2array[5] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_1) |
				NUM_BANKS(ADDR_SURF_16_BANK));

		mod2array[6] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_1) |
				NUM_BANKS(ADDR_SURF_16_BANK));

		mod2array[8] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_8) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_16_BANK));

		mod2array[9] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_16_BANK));

		mod2array[10] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_2) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				NUM_BANKS(ADDR_SURF_16_BANK));

		mod2array[11] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				NUM_BANKS(ADDR_SURF_16_BANK));

		mod2array[12] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_1) |
				NUM_BANKS(ADDR_SURF_8_BANK));

		mod2array[13] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_1) |
				NUM_BANKS(ADDR_SURF_4_BANK));

		mod2array[14] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_1) |
				NUM_BANKS(ADDR_SURF_4_BANK));

		क्रम (reg_offset = 0; reg_offset < num_tile_mode_states; reg_offset++)
			WREG32(mmGB_TILE_MODE0 + reg_offset, modearray[reg_offset]);

		क्रम (reg_offset = 0; reg_offset < num_secondary_tile_mode_states; reg_offset++)
			अगर (reg_offset != 7)
				WREG32(mmGB_MACROTILE_MODE0 + reg_offset, mod2array[reg_offset]);

		अवरोध;
	हाल CHIP_STONEY:
		modearray[0] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P2) |
				TILE_SPLIT(ADDR_SURF_TILE_SPLIT_64B) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		modearray[1] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P2) |
				TILE_SPLIT(ADDR_SURF_TILE_SPLIT_128B) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		modearray[2] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P2) |
				TILE_SPLIT(ADDR_SURF_TILE_SPLIT_256B) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		modearray[3] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P2) |
				TILE_SPLIT(ADDR_SURF_TILE_SPLIT_512B) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		modearray[4] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P2) |
				TILE_SPLIT(ADDR_SURF_TILE_SPLIT_2KB) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		modearray[5] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P2) |
				TILE_SPLIT(ADDR_SURF_TILE_SPLIT_2KB) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		modearray[6] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P2) |
				TILE_SPLIT(ADDR_SURF_TILE_SPLIT_2KB) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		modearray[8] = (ARRAY_MODE(ARRAY_LINEAR_ALIGNED) |
				PIPE_CONFIG(ADDR_SURF_P2));
		modearray[9] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P2) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DISPLAY_MICRO_TILING) |
				SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		modearray[10] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
				 PIPE_CONFIG(ADDR_SURF_P2) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_DISPLAY_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		modearray[11] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
				 PIPE_CONFIG(ADDR_SURF_P2) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_DISPLAY_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_8));
		modearray[13] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
				 PIPE_CONFIG(ADDR_SURF_P2) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		modearray[14] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
				 PIPE_CONFIG(ADDR_SURF_P2) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		modearray[15] = (ARRAY_MODE(ARRAY_3D_TILED_THIN1) |
				 PIPE_CONFIG(ADDR_SURF_P2) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		modearray[16] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
				 PIPE_CONFIG(ADDR_SURF_P2) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_8));
		modearray[18] = (ARRAY_MODE(ARRAY_1D_TILED_THICK) |
				 PIPE_CONFIG(ADDR_SURF_P2) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		modearray[19] = (ARRAY_MODE(ARRAY_1D_TILED_THICK) |
				 PIPE_CONFIG(ADDR_SURF_P2) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THICK_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		modearray[20] = (ARRAY_MODE(ARRAY_2D_TILED_THICK) |
				 PIPE_CONFIG(ADDR_SURF_P2) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THICK_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		modearray[21] = (ARRAY_MODE(ARRAY_3D_TILED_THICK) |
				 PIPE_CONFIG(ADDR_SURF_P2) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THICK_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		modearray[22] = (ARRAY_MODE(ARRAY_PRT_TILED_THICK) |
				 PIPE_CONFIG(ADDR_SURF_P2) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THICK_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		modearray[24] = (ARRAY_MODE(ARRAY_2D_TILED_THICK) |
				 PIPE_CONFIG(ADDR_SURF_P2) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		modearray[25] = (ARRAY_MODE(ARRAY_2D_TILED_XTHICK) |
				 PIPE_CONFIG(ADDR_SURF_P2) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THICK_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		modearray[26] = (ARRAY_MODE(ARRAY_3D_TILED_XTHICK) |
				 PIPE_CONFIG(ADDR_SURF_P2) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THICK_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		modearray[27] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
				 PIPE_CONFIG(ADDR_SURF_P2) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_ROTATED_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		modearray[28] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
				 PIPE_CONFIG(ADDR_SURF_P2) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_ROTATED_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		modearray[29] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
				 PIPE_CONFIG(ADDR_SURF_P2) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_ROTATED_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_8));

		mod2array[0] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_8_BANK));
		mod2array[1] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_2) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_8_BANK));
		mod2array[2] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				NUM_BANKS(ADDR_SURF_8_BANK));
		mod2array[3] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				NUM_BANKS(ADDR_SURF_8_BANK));
		mod2array[4] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				NUM_BANKS(ADDR_SURF_8_BANK));
		mod2array[5] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				NUM_BANKS(ADDR_SURF_8_BANK));
		mod2array[6] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				NUM_BANKS(ADDR_SURF_8_BANK));
		mod2array[8] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_4) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_8) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		mod2array[9] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_4) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		mod2array[10] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_2) |
				 BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
				 MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				 NUM_BANKS(ADDR_SURF_16_BANK));
		mod2array[11] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_2) |
				 BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_2) |
				 MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				 NUM_BANKS(ADDR_SURF_16_BANK));
		mod2array[12] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				 BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_2) |
				 MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				 NUM_BANKS(ADDR_SURF_16_BANK));
		mod2array[13] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				 BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				 MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				 NUM_BANKS(ADDR_SURF_16_BANK));
		mod2array[14] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				 BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				 MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				 NUM_BANKS(ADDR_SURF_8_BANK));

		क्रम (reg_offset = 0; reg_offset < num_tile_mode_states; reg_offset++)
			अगर (reg_offset != 7 && reg_offset != 12 && reg_offset != 17 &&
			    reg_offset != 23)
				WREG32(mmGB_TILE_MODE0 + reg_offset, modearray[reg_offset]);

		क्रम (reg_offset = 0; reg_offset < num_secondary_tile_mode_states; reg_offset++)
			अगर (reg_offset != 7)
				WREG32(mmGB_MACROTILE_MODE0 + reg_offset, mod2array[reg_offset]);

		अवरोध;
	शेष:
		dev_warn(adev->dev,
			 "Unknown chip type (%d) in function gfx_v8_0_tiling_mode_table_init() falling through to CHIP_CARRIZO\n",
			 adev->asic_type);
		fallthrough;

	हाल CHIP_CARRIZO:
		modearray[0] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P2) |
				TILE_SPLIT(ADDR_SURF_TILE_SPLIT_64B) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		modearray[1] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P2) |
				TILE_SPLIT(ADDR_SURF_TILE_SPLIT_128B) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		modearray[2] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P2) |
				TILE_SPLIT(ADDR_SURF_TILE_SPLIT_256B) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		modearray[3] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P2) |
				TILE_SPLIT(ADDR_SURF_TILE_SPLIT_512B) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		modearray[4] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P2) |
				TILE_SPLIT(ADDR_SURF_TILE_SPLIT_2KB) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		modearray[5] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P2) |
				TILE_SPLIT(ADDR_SURF_TILE_SPLIT_2KB) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		modearray[6] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P2) |
				TILE_SPLIT(ADDR_SURF_TILE_SPLIT_2KB) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DEPTH_MICRO_TILING));
		modearray[8] = (ARRAY_MODE(ARRAY_LINEAR_ALIGNED) |
				PIPE_CONFIG(ADDR_SURF_P2));
		modearray[9] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
				PIPE_CONFIG(ADDR_SURF_P2) |
				MICRO_TILE_MODE_NEW(ADDR_SURF_DISPLAY_MICRO_TILING) |
				SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		modearray[10] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
				 PIPE_CONFIG(ADDR_SURF_P2) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_DISPLAY_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		modearray[11] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
				 PIPE_CONFIG(ADDR_SURF_P2) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_DISPLAY_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_8));
		modearray[13] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
				 PIPE_CONFIG(ADDR_SURF_P2) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		modearray[14] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
				 PIPE_CONFIG(ADDR_SURF_P2) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		modearray[15] = (ARRAY_MODE(ARRAY_3D_TILED_THIN1) |
				 PIPE_CONFIG(ADDR_SURF_P2) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		modearray[16] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
				 PIPE_CONFIG(ADDR_SURF_P2) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_8));
		modearray[18] = (ARRAY_MODE(ARRAY_1D_TILED_THICK) |
				 PIPE_CONFIG(ADDR_SURF_P2) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		modearray[19] = (ARRAY_MODE(ARRAY_1D_TILED_THICK) |
				 PIPE_CONFIG(ADDR_SURF_P2) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THICK_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		modearray[20] = (ARRAY_MODE(ARRAY_2D_TILED_THICK) |
				 PIPE_CONFIG(ADDR_SURF_P2) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THICK_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		modearray[21] = (ARRAY_MODE(ARRAY_3D_TILED_THICK) |
				 PIPE_CONFIG(ADDR_SURF_P2) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THICK_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		modearray[22] = (ARRAY_MODE(ARRAY_PRT_TILED_THICK) |
				 PIPE_CONFIG(ADDR_SURF_P2) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THICK_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		modearray[24] = (ARRAY_MODE(ARRAY_2D_TILED_THICK) |
				 PIPE_CONFIG(ADDR_SURF_P2) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THIN_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		modearray[25] = (ARRAY_MODE(ARRAY_2D_TILED_XTHICK) |
				 PIPE_CONFIG(ADDR_SURF_P2) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THICK_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		modearray[26] = (ARRAY_MODE(ARRAY_3D_TILED_XTHICK) |
				 PIPE_CONFIG(ADDR_SURF_P2) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_THICK_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_1));
		modearray[27] = (ARRAY_MODE(ARRAY_1D_TILED_THIN1) |
				 PIPE_CONFIG(ADDR_SURF_P2) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_ROTATED_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		modearray[28] = (ARRAY_MODE(ARRAY_2D_TILED_THIN1) |
				 PIPE_CONFIG(ADDR_SURF_P2) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_ROTATED_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_2));
		modearray[29] = (ARRAY_MODE(ARRAY_PRT_TILED_THIN1) |
				 PIPE_CONFIG(ADDR_SURF_P2) |
				 MICRO_TILE_MODE_NEW(ADDR_SURF_ROTATED_MICRO_TILING) |
				 SAMPLE_SPLIT(ADDR_SURF_SAMPLE_SPLIT_8));

		mod2array[0] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_8_BANK));
		mod2array[1] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_2) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_8_BANK));
		mod2array[2] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				NUM_BANKS(ADDR_SURF_8_BANK));
		mod2array[3] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				NUM_BANKS(ADDR_SURF_8_BANK));
		mod2array[4] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				NUM_BANKS(ADDR_SURF_8_BANK));
		mod2array[5] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				NUM_BANKS(ADDR_SURF_8_BANK));
		mod2array[6] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				NUM_BANKS(ADDR_SURF_8_BANK));
		mod2array[8] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_4) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_8) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		mod2array[9] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_4) |
				BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
				MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				NUM_BANKS(ADDR_SURF_16_BANK));
		mod2array[10] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_2) |
				 BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_4) |
				 MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				 NUM_BANKS(ADDR_SURF_16_BANK));
		mod2array[11] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_2) |
				 BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_2) |
				 MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				 NUM_BANKS(ADDR_SURF_16_BANK));
		mod2array[12] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				 BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_2) |
				 MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				 NUM_BANKS(ADDR_SURF_16_BANK));
		mod2array[13] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				 BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				 MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_4) |
				 NUM_BANKS(ADDR_SURF_16_BANK));
		mod2array[14] = (BANK_WIDTH(ADDR_SURF_BANK_WIDTH_1) |
				 BANK_HEIGHT(ADDR_SURF_BANK_HEIGHT_1) |
				 MACRO_TILE_ASPECT(ADDR_SURF_MACRO_ASPECT_2) |
				 NUM_BANKS(ADDR_SURF_8_BANK));

		क्रम (reg_offset = 0; reg_offset < num_tile_mode_states; reg_offset++)
			अगर (reg_offset != 7 && reg_offset != 12 && reg_offset != 17 &&
			    reg_offset != 23)
				WREG32(mmGB_TILE_MODE0 + reg_offset, modearray[reg_offset]);

		क्रम (reg_offset = 0; reg_offset < num_secondary_tile_mode_states; reg_offset++)
			अगर (reg_offset != 7)
				WREG32(mmGB_MACROTILE_MODE0 + reg_offset, mod2array[reg_offset]);

		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम gfx_v8_0_select_se_sh(काष्ठा amdgpu_device *adev,
				  u32 se_num, u32 sh_num, u32 instance)
अणु
	u32 data;

	अगर (instance == 0xffffffff)
		data = REG_SET_FIELD(0, GRBM_GFX_INDEX, INSTANCE_BROADCAST_WRITES, 1);
	अन्यथा
		data = REG_SET_FIELD(0, GRBM_GFX_INDEX, INSTANCE_INDEX, instance);

	अगर (se_num == 0xffffffff)
		data = REG_SET_FIELD(data, GRBM_GFX_INDEX, SE_BROADCAST_WRITES, 1);
	अन्यथा
		data = REG_SET_FIELD(data, GRBM_GFX_INDEX, SE_INDEX, se_num);

	अगर (sh_num == 0xffffffff)
		data = REG_SET_FIELD(data, GRBM_GFX_INDEX, SH_BROADCAST_WRITES, 1);
	अन्यथा
		data = REG_SET_FIELD(data, GRBM_GFX_INDEX, SH_INDEX, sh_num);

	WREG32(mmGRBM_GFX_INDEX, data);
पूर्ण

अटल व्योम gfx_v8_0_select_me_pipe_q(काष्ठा amdgpu_device *adev,
				  u32 me, u32 pipe, u32 q, u32 vm)
अणु
	vi_srbm_select(adev, me, pipe, q, vm);
पूर्ण

अटल u32 gfx_v8_0_get_rb_active_biपंचांगap(काष्ठा amdgpu_device *adev)
अणु
	u32 data, mask;

	data =  RREG32(mmCC_RB_BACKEND_DISABLE) |
		RREG32(mmGC_USER_RB_BACKEND_DISABLE);

	data = REG_GET_FIELD(data, GC_USER_RB_BACKEND_DISABLE, BACKEND_DISABLE);

	mask = amdgpu_gfx_create_biपंचांगask(adev->gfx.config.max_backends_per_se /
					 adev->gfx.config.max_sh_per_se);

	वापस (~data) & mask;
पूर्ण

अटल व्योम
gfx_v8_0_raster_config(काष्ठा amdgpu_device *adev, u32 *rconf, u32 *rconf1)
अणु
	चयन (adev->asic_type) अणु
	हाल CHIP_FIJI:
	हाल CHIP_VEGAM:
		*rconf |= RB_MAP_PKR0(2) | RB_MAP_PKR1(2) |
			  RB_XSEL2(1) | PKR_MAP(2) |
			  PKR_XSEL(1) | PKR_YSEL(1) |
			  SE_MAP(2) | SE_XSEL(2) | SE_YSEL(3);
		*rconf1 |= SE_PAIR_MAP(2) | SE_PAIR_XSEL(3) |
			   SE_PAIR_YSEL(2);
		अवरोध;
	हाल CHIP_TONGA:
	हाल CHIP_POLARIS10:
		*rconf |= RB_MAP_PKR0(2) | RB_XSEL2(1) | SE_MAP(2) |
			  SE_XSEL(1) | SE_YSEL(1);
		*rconf1 |= SE_PAIR_MAP(2) | SE_PAIR_XSEL(2) |
			   SE_PAIR_YSEL(2);
		अवरोध;
	हाल CHIP_TOPAZ:
	हाल CHIP_CARRIZO:
		*rconf |= RB_MAP_PKR0(2);
		*rconf1 |= 0x0;
		अवरोध;
	हाल CHIP_POLARIS11:
	हाल CHIP_POLARIS12:
		*rconf |= RB_MAP_PKR0(2) | RB_XSEL2(1) | SE_MAP(2) |
			  SE_XSEL(1) | SE_YSEL(1);
		*rconf1 |= 0x0;
		अवरोध;
	हाल CHIP_STONEY:
		*rconf |= 0x0;
		*rconf1 |= 0x0;
		अवरोध;
	शेष:
		DRM_ERROR("unknown asic: 0x%x\n", adev->asic_type);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
gfx_v8_0_ग_लिखो_harvested_raster_configs(काष्ठा amdgpu_device *adev,
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

		/* GRBM_GFX_INDEX has a dअगरferent offset on VI */
		gfx_v8_0_select_se_sh(adev, se, 0xffffffff, 0xffffffff);
		WREG32(mmPA_SC_RASTER_CONFIG, raster_config_se);
		WREG32(mmPA_SC_RASTER_CONFIG_1, raster_config_1);
	पूर्ण

	/* GRBM_GFX_INDEX has a dअगरferent offset on VI */
	gfx_v8_0_select_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff);
पूर्ण

अटल व्योम gfx_v8_0_setup_rb(काष्ठा amdgpu_device *adev)
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
			gfx_v8_0_select_se_sh(adev, i, j, 0xffffffff);
			data = gfx_v8_0_get_rb_active_biपंचांगap(adev);
			active_rbs |= data << ((i * adev->gfx.config.max_sh_per_se + j) *
					       rb_biपंचांगap_width_per_sh);
		पूर्ण
	पूर्ण
	gfx_v8_0_select_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff);

	adev->gfx.config.backend_enable_mask = active_rbs;
	adev->gfx.config.num_rbs = hweight32(active_rbs);

	num_rb_pipes = min_t(अचिन्हित, adev->gfx.config.max_backends_per_se *
			     adev->gfx.config.max_shader_engines, 16);

	gfx_v8_0_raster_config(adev, &raster_config, &raster_config_1);

	अगर (!adev->gfx.config.backend_enable_mask ||
			adev->gfx.config.num_rbs >= num_rb_pipes) अणु
		WREG32(mmPA_SC_RASTER_CONFIG, raster_config);
		WREG32(mmPA_SC_RASTER_CONFIG_1, raster_config_1);
	पूर्ण अन्यथा अणु
		gfx_v8_0_ग_लिखो_harvested_raster_configs(adev, raster_config, raster_config_1,
							adev->gfx.config.backend_enable_mask,
							num_rb_pipes);
	पूर्ण

	/* cache the values क्रम userspace */
	क्रम (i = 0; i < adev->gfx.config.max_shader_engines; i++) अणु
		क्रम (j = 0; j < adev->gfx.config.max_sh_per_se; j++) अणु
			gfx_v8_0_select_se_sh(adev, i, j, 0xffffffff);
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
	gfx_v8_0_select_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff);
	mutex_unlock(&adev->grbm_idx_mutex);
पूर्ण

#घोषणा DEFAULT_SH_MEM_BASES	(0x6000)
/**
 * gfx_v8_0_init_compute_vmid - gart enable
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Initialize compute vmid sh_mem रेजिस्टरs
 *
 */
अटल व्योम gfx_v8_0_init_compute_vmid(काष्ठा amdgpu_device *adev)
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

	sh_mem_config = SH_MEM_ADDRESS_MODE_HSA64 <<
			SH_MEM_CONFIG__ADDRESS_MODE__SHIFT |
			SH_MEM_ALIGNMENT_MODE_UNALIGNED <<
			SH_MEM_CONFIG__ALIGNMENT_MODE__SHIFT |
			MTYPE_CC << SH_MEM_CONFIG__DEFAULT_MTYPE__SHIFT |
			SH_MEM_CONFIG__PRIVATE_ATC_MASK;

	mutex_lock(&adev->srbm_mutex);
	क्रम (i = adev->vm_manager.first_kfd_vmid; i < AMDGPU_NUM_VMID; i++) अणु
		vi_srbm_select(adev, 0, 0, 0, i);
		/* CP and shaders */
		WREG32(mmSH_MEM_CONFIG, sh_mem_config);
		WREG32(mmSH_MEM_APE1_BASE, 1);
		WREG32(mmSH_MEM_APE1_LIMIT, 0);
		WREG32(mmSH_MEM_BASES, sh_mem_bases);
	पूर्ण
	vi_srbm_select(adev, 0, 0, 0, 0);
	mutex_unlock(&adev->srbm_mutex);

	/* Initialize all compute VMIDs to have no GDS, GWS, or OA
	   acccess. These should be enabled by FW क्रम target VMIDs. */
	क्रम (i = adev->vm_manager.first_kfd_vmid; i < AMDGPU_NUM_VMID; i++) अणु
		WREG32(amdgpu_gds_reg_offset[i].mem_base, 0);
		WREG32(amdgpu_gds_reg_offset[i].mem_size, 0);
		WREG32(amdgpu_gds_reg_offset[i].gws, 0);
		WREG32(amdgpu_gds_reg_offset[i].oa, 0);
	पूर्ण
पूर्ण

अटल व्योम gfx_v8_0_init_gds_vmid(काष्ठा amdgpu_device *adev)
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

अटल व्योम gfx_v8_0_config_init(काष्ठा amdgpu_device *adev)
अणु
	चयन (adev->asic_type) अणु
	शेष:
		adev->gfx.config.द्विगुन_offchip_lds_buf = 1;
		अवरोध;
	हाल CHIP_CARRIZO:
	हाल CHIP_STONEY:
		adev->gfx.config.द्विगुन_offchip_lds_buf = 0;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम gfx_v8_0_स्थिरants_init(काष्ठा amdgpu_device *adev)
अणु
	u32 पंचांगp, sh_अटल_mem_cfg;
	पूर्णांक i;

	WREG32_FIELD(GRBM_CNTL, READ_TIMEOUT, 0xFF);
	WREG32(mmGB_ADDR_CONFIG, adev->gfx.config.gb_addr_config);
	WREG32(mmHDP_ADDR_CONFIG, adev->gfx.config.gb_addr_config);
	WREG32(mmDMIF_ADDR_CALC, adev->gfx.config.gb_addr_config);

	gfx_v8_0_tiling_mode_table_init(adev);
	gfx_v8_0_setup_rb(adev);
	gfx_v8_0_get_cu_info(adev);
	gfx_v8_0_config_init(adev);

	/* XXX SH_MEM regs */
	/* where to put LDS, scratch, GPUVM in FSA64 space */
	sh_अटल_mem_cfg = REG_SET_FIELD(0, SH_STATIC_MEM_CONFIG,
				   SWIZZLE_ENABLE, 1);
	sh_अटल_mem_cfg = REG_SET_FIELD(sh_अटल_mem_cfg, SH_STATIC_MEM_CONFIG,
				   ELEMENT_SIZE, 1);
	sh_अटल_mem_cfg = REG_SET_FIELD(sh_अटल_mem_cfg, SH_STATIC_MEM_CONFIG,
				   INDEX_STRIDE, 3);
	WREG32(mmSH_STATIC_MEM_CONFIG, sh_अटल_mem_cfg);

	mutex_lock(&adev->srbm_mutex);
	क्रम (i = 0; i < adev->vm_manager.id_mgr[0].num_ids; i++) अणु
		vi_srbm_select(adev, 0, 0, 0, i);
		/* CP and shaders */
		अगर (i == 0) अणु
			पंचांगp = REG_SET_FIELD(0, SH_MEM_CONFIG, DEFAULT_MTYPE, MTYPE_UC);
			पंचांगp = REG_SET_FIELD(पंचांगp, SH_MEM_CONFIG, APE1_MTYPE, MTYPE_UC);
			पंचांगp = REG_SET_FIELD(पंचांगp, SH_MEM_CONFIG, ALIGNMENT_MODE,
					    SH_MEM_ALIGNMENT_MODE_UNALIGNED);
			WREG32(mmSH_MEM_CONFIG, पंचांगp);
			WREG32(mmSH_MEM_BASES, 0);
		पूर्ण अन्यथा अणु
			पंचांगp = REG_SET_FIELD(0, SH_MEM_CONFIG, DEFAULT_MTYPE, MTYPE_NC);
			पंचांगp = REG_SET_FIELD(पंचांगp, SH_MEM_CONFIG, APE1_MTYPE, MTYPE_UC);
			पंचांगp = REG_SET_FIELD(पंचांगp, SH_MEM_CONFIG, ALIGNMENT_MODE,
					    SH_MEM_ALIGNMENT_MODE_UNALIGNED);
			WREG32(mmSH_MEM_CONFIG, पंचांगp);
			पंचांगp = adev->gmc.shared_aperture_start >> 48;
			WREG32(mmSH_MEM_BASES, पंचांगp);
		पूर्ण

		WREG32(mmSH_MEM_APE1_BASE, 1);
		WREG32(mmSH_MEM_APE1_LIMIT, 0);
	पूर्ण
	vi_srbm_select(adev, 0, 0, 0, 0);
	mutex_unlock(&adev->srbm_mutex);

	gfx_v8_0_init_compute_vmid(adev);
	gfx_v8_0_init_gds_vmid(adev);

	mutex_lock(&adev->grbm_idx_mutex);
	/*
	 * making sure that the following रेजिस्टर ग_लिखोs will be broadcasted
	 * to all the shaders
	 */
	gfx_v8_0_select_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff);

	WREG32(mmPA_SC_FIFO_SIZE,
		   (adev->gfx.config.sc_prim_fअगरo_size_frontend <<
			PA_SC_FIFO_SIZE__SC_FRONTEND_PRIM_FIFO_SIZE__SHIFT) |
		   (adev->gfx.config.sc_prim_fअगरo_size_backend <<
			PA_SC_FIFO_SIZE__SC_BACKEND_PRIM_FIFO_SIZE__SHIFT) |
		   (adev->gfx.config.sc_hiz_tile_fअगरo_size <<
			PA_SC_FIFO_SIZE__SC_HIZ_TILE_FIFO_SIZE__SHIFT) |
		   (adev->gfx.config.sc_earlyz_tile_fअगरo_size <<
			PA_SC_FIFO_SIZE__SC_EARLYZ_TILE_FIFO_SIZE__SHIFT));

	पंचांगp = RREG32(mmSPI_ARB_PRIORITY);
	पंचांगp = REG_SET_FIELD(पंचांगp, SPI_ARB_PRIORITY, PIPE_ORDER_TS0, 2);
	पंचांगp = REG_SET_FIELD(पंचांगp, SPI_ARB_PRIORITY, PIPE_ORDER_TS1, 2);
	पंचांगp = REG_SET_FIELD(पंचांगp, SPI_ARB_PRIORITY, PIPE_ORDER_TS2, 2);
	पंचांगp = REG_SET_FIELD(पंचांगp, SPI_ARB_PRIORITY, PIPE_ORDER_TS3, 2);
	WREG32(mmSPI_ARB_PRIORITY, पंचांगp);

	mutex_unlock(&adev->grbm_idx_mutex);

पूर्ण

अटल व्योम gfx_v8_0_रुको_क्रम_rlc_serdes(काष्ठा amdgpu_device *adev)
अणु
	u32 i, j, k;
	u32 mask;

	mutex_lock(&adev->grbm_idx_mutex);
	क्रम (i = 0; i < adev->gfx.config.max_shader_engines; i++) अणु
		क्रम (j = 0; j < adev->gfx.config.max_sh_per_se; j++) अणु
			gfx_v8_0_select_se_sh(adev, i, j, 0xffffffff);
			क्रम (k = 0; k < adev->usec_समयout; k++) अणु
				अगर (RREG32(mmRLC_SERDES_CU_MASTER_BUSY) == 0)
					अवरोध;
				udelay(1);
			पूर्ण
			अगर (k == adev->usec_समयout) अणु
				gfx_v8_0_select_se_sh(adev, 0xffffffff,
						      0xffffffff, 0xffffffff);
				mutex_unlock(&adev->grbm_idx_mutex);
				DRM_INFO("Timeout wait for RLC serdes %u,%u\n",
					 i, j);
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण
	gfx_v8_0_select_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff);
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

अटल व्योम gfx_v8_0_enable_gui_idle_पूर्णांकerrupt(काष्ठा amdgpu_device *adev,
					       bool enable)
अणु
	u32 पंचांगp = RREG32(mmCP_INT_CNTL_RING0);

	पंचांगp = REG_SET_FIELD(पंचांगp, CP_INT_CNTL_RING0, CNTX_BUSY_INT_ENABLE, enable ? 1 : 0);
	पंचांगp = REG_SET_FIELD(पंचांगp, CP_INT_CNTL_RING0, CNTX_EMPTY_INT_ENABLE, enable ? 1 : 0);
	पंचांगp = REG_SET_FIELD(पंचांगp, CP_INT_CNTL_RING0, CMP_BUSY_INT_ENABLE, enable ? 1 : 0);
	पंचांगp = REG_SET_FIELD(पंचांगp, CP_INT_CNTL_RING0, GFX_IDLE_INT_ENABLE, enable ? 1 : 0);

	WREG32(mmCP_INT_CNTL_RING0, पंचांगp);
पूर्ण

अटल व्योम gfx_v8_0_init_csb(काष्ठा amdgpu_device *adev)
अणु
	adev->gfx.rlc.funcs->get_csb_buffer(adev, adev->gfx.rlc.cs_ptr);
	/* csib */
	WREG32(mmRLC_CSIB_ADDR_HI,
			adev->gfx.rlc.clear_state_gpu_addr >> 32);
	WREG32(mmRLC_CSIB_ADDR_LO,
			adev->gfx.rlc.clear_state_gpu_addr & 0xfffffffc);
	WREG32(mmRLC_CSIB_LENGTH,
			adev->gfx.rlc.clear_state_size);
पूर्ण

अटल व्योम gfx_v8_0_parse_ind_reg_list(पूर्णांक *रेजिस्टर_list_क्रमmat,
				पूर्णांक ind_offset,
				पूर्णांक list_size,
				पूर्णांक *unique_indices,
				पूर्णांक *indices_count,
				पूर्णांक max_indices,
				पूर्णांक *ind_start_offsets,
				पूर्णांक *offset_count,
				पूर्णांक max_offset)
अणु
	पूर्णांक indices;
	bool new_entry = true;

	क्रम (; ind_offset < list_size; ind_offset++) अणु

		अगर (new_entry) अणु
			new_entry = false;
			ind_start_offsets[*offset_count] = ind_offset;
			*offset_count = *offset_count + 1;
			BUG_ON(*offset_count >= max_offset);
		पूर्ण

		अगर (रेजिस्टर_list_क्रमmat[ind_offset] == 0xFFFFFFFF) अणु
			new_entry = true;
			जारी;
		पूर्ण

		ind_offset += 2;

		/* look क्रम the matching indice */
		क्रम (indices = 0;
			indices < *indices_count;
			indices++) अणु
			अगर (unique_indices[indices] ==
				रेजिस्टर_list_क्रमmat[ind_offset])
				अवरोध;
		पूर्ण

		अगर (indices >= *indices_count) अणु
			unique_indices[*indices_count] =
				रेजिस्टर_list_क्रमmat[ind_offset];
			indices = *indices_count;
			*indices_count = *indices_count + 1;
			BUG_ON(*indices_count >= max_indices);
		पूर्ण

		रेजिस्टर_list_क्रमmat[ind_offset] = indices;
	पूर्ण
पूर्ण

अटल पूर्णांक gfx_v8_0_init_save_restore_list(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i, temp, data;
	पूर्णांक unique_indices[] = अणु0, 0, 0, 0, 0, 0, 0, 0पूर्ण;
	पूर्णांक indices_count = 0;
	पूर्णांक indirect_start_offsets[] = अणु0, 0, 0, 0, 0, 0, 0, 0, 0, 0पूर्ण;
	पूर्णांक offset_count = 0;

	पूर्णांक list_size;
	अचिन्हित पूर्णांक *रेजिस्टर_list_क्रमmat =
		kmemdup(adev->gfx.rlc.रेजिस्टर_list_क्रमmat,
			adev->gfx.rlc.reg_list_क्रमmat_size_bytes, GFP_KERNEL);
	अगर (!रेजिस्टर_list_क्रमmat)
		वापस -ENOMEM;

	gfx_v8_0_parse_ind_reg_list(रेजिस्टर_list_क्रमmat,
				RLC_FormatDirectRegListLength,
				adev->gfx.rlc.reg_list_क्रमmat_size_bytes >> 2,
				unique_indices,
				&indices_count,
				ARRAY_SIZE(unique_indices),
				indirect_start_offsets,
				&offset_count,
				ARRAY_SIZE(indirect_start_offsets));

	/* save and restore list */
	WREG32_FIELD(RLC_SRM_CNTL, AUTO_INCR_ADDR, 1);

	WREG32(mmRLC_SRM_ARAM_ADDR, 0);
	क्रम (i = 0; i < adev->gfx.rlc.reg_list_size_bytes >> 2; i++)
		WREG32(mmRLC_SRM_ARAM_DATA, adev->gfx.rlc.रेजिस्टर_restore[i]);

	/* indirect list */
	WREG32(mmRLC_GPM_SCRATCH_ADDR, adev->gfx.rlc.reg_list_क्रमmat_start);
	क्रम (i = 0; i < adev->gfx.rlc.reg_list_क्रमmat_size_bytes >> 2; i++)
		WREG32(mmRLC_GPM_SCRATCH_DATA, रेजिस्टर_list_क्रमmat[i]);

	list_size = adev->gfx.rlc.reg_list_size_bytes >> 2;
	list_size = list_size >> 1;
	WREG32(mmRLC_GPM_SCRATCH_ADDR, adev->gfx.rlc.reg_restore_list_size);
	WREG32(mmRLC_GPM_SCRATCH_DATA, list_size);

	/* starting offsets starts */
	WREG32(mmRLC_GPM_SCRATCH_ADDR,
		adev->gfx.rlc.starting_offsets_start);
	क्रम (i = 0; i < ARRAY_SIZE(indirect_start_offsets); i++)
		WREG32(mmRLC_GPM_SCRATCH_DATA,
				indirect_start_offsets[i]);

	/* unique indices */
	temp = mmRLC_SRM_INDEX_CNTL_ADDR_0;
	data = mmRLC_SRM_INDEX_CNTL_DATA_0;
	क्रम (i = 0; i < ARRAY_SIZE(unique_indices); i++) अणु
		अगर (unique_indices[i] != 0) अणु
			WREG32(temp + i, unique_indices[i] & 0x3FFFF);
			WREG32(data + i, unique_indices[i] >> 20);
		पूर्ण
	पूर्ण
	kमुक्त(रेजिस्टर_list_क्रमmat);

	वापस 0;
पूर्ण

अटल व्योम gfx_v8_0_enable_save_restore_machine(काष्ठा amdgpu_device *adev)
अणु
	WREG32_FIELD(RLC_SRM_CNTL, SRM_ENABLE, 1);
पूर्ण

अटल व्योम gfx_v8_0_init_घातer_gating(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक32_t data;

	WREG32_FIELD(CP_RB_WPTR_POLL_CNTL, IDLE_POLL_COUNT, 0x60);

	data = REG_SET_FIELD(0, RLC_PG_DELAY, POWER_UP_DELAY, 0x10);
	data = REG_SET_FIELD(data, RLC_PG_DELAY, POWER_DOWN_DELAY, 0x10);
	data = REG_SET_FIELD(data, RLC_PG_DELAY, CMD_PROPAGATE_DELAY, 0x10);
	data = REG_SET_FIELD(data, RLC_PG_DELAY, MEM_SLEEP_DELAY, 0x10);
	WREG32(mmRLC_PG_DELAY, data);

	WREG32_FIELD(RLC_PG_DELAY_2, SERDES_CMD_DELAY, 0x3);
	WREG32_FIELD(RLC_AUTO_PG_CTRL, GRBM_REG_SAVE_GFX_IDLE_THRESHOLD, 0x55f0);

पूर्ण

अटल व्योम cz_enable_sck_slow_करोwn_on_घातer_up(काष्ठा amdgpu_device *adev,
						bool enable)
अणु
	WREG32_FIELD(RLC_PG_CNTL, SMU_CLK_SLOWDOWN_ON_PU_ENABLE, enable ? 1 : 0);
पूर्ण

अटल व्योम cz_enable_sck_slow_करोwn_on_घातer_करोwn(काष्ठा amdgpu_device *adev,
						  bool enable)
अणु
	WREG32_FIELD(RLC_PG_CNTL, SMU_CLK_SLOWDOWN_ON_PD_ENABLE, enable ? 1 : 0);
पूर्ण

अटल व्योम cz_enable_cp_घातer_gating(काष्ठा amdgpu_device *adev, bool enable)
अणु
	WREG32_FIELD(RLC_PG_CNTL, CP_PG_DISABLE, enable ? 0 : 1);
पूर्ण

अटल व्योम gfx_v8_0_init_pg(काष्ठा amdgpu_device *adev)
अणु
	अगर ((adev->asic_type == CHIP_CARRIZO) ||
	    (adev->asic_type == CHIP_STONEY)) अणु
		gfx_v8_0_init_csb(adev);
		gfx_v8_0_init_save_restore_list(adev);
		gfx_v8_0_enable_save_restore_machine(adev);
		WREG32(mmRLC_JUMP_TABLE_RESTORE, adev->gfx.rlc.cp_table_gpu_addr >> 8);
		gfx_v8_0_init_घातer_gating(adev);
		WREG32(mmRLC_PG_ALWAYS_ON_CU_MASK, adev->gfx.cu_info.ao_cu_mask);
	पूर्ण अन्यथा अगर ((adev->asic_type == CHIP_POLARIS11) ||
		   (adev->asic_type == CHIP_POLARIS12) ||
		   (adev->asic_type == CHIP_VEGAM)) अणु
		gfx_v8_0_init_csb(adev);
		gfx_v8_0_init_save_restore_list(adev);
		gfx_v8_0_enable_save_restore_machine(adev);
		gfx_v8_0_init_घातer_gating(adev);
	पूर्ण

पूर्ण

अटल व्योम gfx_v8_0_rlc_stop(काष्ठा amdgpu_device *adev)
अणु
	WREG32_FIELD(RLC_CNTL, RLC_ENABLE_F32, 0);

	gfx_v8_0_enable_gui_idle_पूर्णांकerrupt(adev, false);
	gfx_v8_0_रुको_क्रम_rlc_serdes(adev);
पूर्ण

अटल व्योम gfx_v8_0_rlc_reset(काष्ठा amdgpu_device *adev)
अणु
	WREG32_FIELD(GRBM_SOFT_RESET, SOFT_RESET_RLC, 1);
	udelay(50);

	WREG32_FIELD(GRBM_SOFT_RESET, SOFT_RESET_RLC, 0);
	udelay(50);
पूर्ण

अटल व्योम gfx_v8_0_rlc_start(काष्ठा amdgpu_device *adev)
अणु
	WREG32_FIELD(RLC_CNTL, RLC_ENABLE_F32, 1);

	/* carrizo करो enable cp पूर्णांकerrupt after cp inited */
	अगर (!(adev->flags & AMD_IS_APU))
		gfx_v8_0_enable_gui_idle_पूर्णांकerrupt(adev, true);

	udelay(50);
पूर्ण

अटल पूर्णांक gfx_v8_0_rlc_resume(काष्ठा amdgpu_device *adev)
अणु
	अगर (amdgpu_sriov_vf(adev)) अणु
		gfx_v8_0_init_csb(adev);
		वापस 0;
	पूर्ण

	adev->gfx.rlc.funcs->stop(adev);
	adev->gfx.rlc.funcs->reset(adev);
	gfx_v8_0_init_pg(adev);
	adev->gfx.rlc.funcs->start(adev);

	वापस 0;
पूर्ण

अटल व्योम gfx_v8_0_cp_gfx_enable(काष्ठा amdgpu_device *adev, bool enable)
अणु
	u32 पंचांगp = RREG32(mmCP_ME_CNTL);

	अगर (enable) अणु
		पंचांगp = REG_SET_FIELD(पंचांगp, CP_ME_CNTL, ME_HALT, 0);
		पंचांगp = REG_SET_FIELD(पंचांगp, CP_ME_CNTL, PFP_HALT, 0);
		पंचांगp = REG_SET_FIELD(पंचांगp, CP_ME_CNTL, CE_HALT, 0);
	पूर्ण अन्यथा अणु
		पंचांगp = REG_SET_FIELD(पंचांगp, CP_ME_CNTL, ME_HALT, 1);
		पंचांगp = REG_SET_FIELD(पंचांगp, CP_ME_CNTL, PFP_HALT, 1);
		पंचांगp = REG_SET_FIELD(पंचांगp, CP_ME_CNTL, CE_HALT, 1);
	पूर्ण
	WREG32(mmCP_ME_CNTL, पंचांगp);
	udelay(50);
पूर्ण

अटल u32 gfx_v8_0_get_csb_size(काष्ठा amdgpu_device *adev)
अणु
	u32 count = 0;
	स्थिर काष्ठा cs_section_def *sect = शून्य;
	स्थिर काष्ठा cs_extent_def *ext = शून्य;

	/* begin clear state */
	count += 2;
	/* context control state */
	count += 3;

	क्रम (sect = vi_cs_data; sect->section != शून्य; ++sect) अणु
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

अटल पूर्णांक gfx_v8_0_cp_gfx_start(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ring *ring = &adev->gfx.gfx_ring[0];
	स्थिर काष्ठा cs_section_def *sect = शून्य;
	स्थिर काष्ठा cs_extent_def *ext = शून्य;
	पूर्णांक r, i;

	/* init the CP */
	WREG32(mmCP_MAX_CONTEXT, adev->gfx.config.max_hw_contexts - 1);
	WREG32(mmCP_ENDIAN_SWAP, 0);
	WREG32(mmCP_DEVICE_ID, 1);

	gfx_v8_0_cp_gfx_enable(adev, true);

	r = amdgpu_ring_alloc(ring, gfx_v8_0_get_csb_size(adev) + 4);
	अगर (r) अणु
		DRM_ERROR("amdgpu: cp failed to lock ring (%d).\n", r);
		वापस r;
	पूर्ण

	/* clear state buffer */
	amdgpu_ring_ग_लिखो(ring, PACKET3(PACKET3_PREAMBLE_CNTL, 0));
	amdgpu_ring_ग_लिखो(ring, PACKET3_PREAMBLE_BEGIN_CLEAR_STATE);

	amdgpu_ring_ग_लिखो(ring, PACKET3(PACKET3_CONTEXT_CONTROL, 1));
	amdgpu_ring_ग_लिखो(ring, 0x80000000);
	amdgpu_ring_ग_लिखो(ring, 0x80000000);

	क्रम (sect = vi_cs_data; sect->section != शून्य; ++sect) अणु
		क्रम (ext = sect->section; ext->extent != शून्य; ++ext) अणु
			अगर (sect->id == SECT_CONTEXT) अणु
				amdgpu_ring_ग_लिखो(ring,
				       PACKET3(PACKET3_SET_CONTEXT_REG,
					       ext->reg_count));
				amdgpu_ring_ग_लिखो(ring,
				       ext->reg_index - PACKET3_SET_CONTEXT_REG_START);
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

	/* init the CE partitions */
	amdgpu_ring_ग_लिखो(ring, PACKET3(PACKET3_SET_BASE, 2));
	amdgpu_ring_ग_लिखो(ring, PACKET3_BASE_INDEX(CE_PARTITION_BASE));
	amdgpu_ring_ग_लिखो(ring, 0x8000);
	amdgpu_ring_ग_लिखो(ring, 0x8000);

	amdgpu_ring_commit(ring);

	वापस 0;
पूर्ण
अटल व्योम gfx_v8_0_set_cpg_करोor_bell(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_ring *ring)
अणु
	u32 पंचांगp;
	/* no gfx करोorbells on iceland */
	अगर (adev->asic_type == CHIP_TOPAZ)
		वापस;

	पंचांगp = RREG32(mmCP_RB_DOORBELL_CONTROL);

	अगर (ring->use_करोorbell) अणु
		पंचांगp = REG_SET_FIELD(पंचांगp, CP_RB_DOORBELL_CONTROL,
				DOORBELL_OFFSET, ring->करोorbell_index);
		पंचांगp = REG_SET_FIELD(पंचांगp, CP_RB_DOORBELL_CONTROL,
						DOORBELL_HIT, 0);
		पंचांगp = REG_SET_FIELD(पंचांगp, CP_RB_DOORBELL_CONTROL,
					    DOORBELL_EN, 1);
	पूर्ण अन्यथा अणु
		पंचांगp = REG_SET_FIELD(पंचांगp, CP_RB_DOORBELL_CONTROL, DOORBELL_EN, 0);
	पूर्ण

	WREG32(mmCP_RB_DOORBELL_CONTROL, पंचांगp);

	अगर (adev->flags & AMD_IS_APU)
		वापस;

	पंचांगp = REG_SET_FIELD(0, CP_RB_DOORBELL_RANGE_LOWER,
					DOORBELL_RANGE_LOWER,
					adev->करोorbell_index.gfx_ring0);
	WREG32(mmCP_RB_DOORBELL_RANGE_LOWER, पंचांगp);

	WREG32(mmCP_RB_DOORBELL_RANGE_UPPER,
		CP_RB_DOORBELL_RANGE_UPPER__DOORBELL_RANGE_UPPER_MASK);
पूर्ण

अटल पूर्णांक gfx_v8_0_cp_gfx_resume(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ring *ring;
	u32 पंचांगp;
	u32 rb_bufsz;
	u64 rb_addr, rptr_addr, wptr_gpu_addr;

	/* Set the ग_लिखो poपूर्णांकer delay */
	WREG32(mmCP_RB_WPTR_DELAY, 0);

	/* set the RB to use vmid 0 */
	WREG32(mmCP_RB_VMID, 0);

	/* Set ring buffer size */
	ring = &adev->gfx.gfx_ring[0];
	rb_bufsz = order_base_2(ring->ring_size / 8);
	पंचांगp = REG_SET_FIELD(0, CP_RB0_CNTL, RB_BUFSZ, rb_bufsz);
	पंचांगp = REG_SET_FIELD(पंचांगp, CP_RB0_CNTL, RB_BLKSZ, rb_bufsz - 2);
	पंचांगp = REG_SET_FIELD(पंचांगp, CP_RB0_CNTL, MTYPE, 3);
	पंचांगp = REG_SET_FIELD(पंचांगp, CP_RB0_CNTL, MIN_IB_AVAILSZ, 1);
#अगर_घोषित __BIG_ENDIAN
	पंचांगp = REG_SET_FIELD(पंचांगp, CP_RB0_CNTL, BUF_SWAP, 1);
#पूर्ण_अगर
	WREG32(mmCP_RB0_CNTL, पंचांगp);

	/* Initialize the ring buffer's पढ़ो and ग_लिखो poपूर्णांकers */
	WREG32(mmCP_RB0_CNTL, पंचांगp | CP_RB0_CNTL__RB_RPTR_WR_ENA_MASK);
	ring->wptr = 0;
	WREG32(mmCP_RB0_WPTR, lower_32_bits(ring->wptr));

	/* set the wb address wether it's enabled or not */
	rptr_addr = adev->wb.gpu_addr + (ring->rptr_offs * 4);
	WREG32(mmCP_RB0_RPTR_ADDR, lower_32_bits(rptr_addr));
	WREG32(mmCP_RB0_RPTR_ADDR_HI, upper_32_bits(rptr_addr) & 0xFF);

	wptr_gpu_addr = adev->wb.gpu_addr + (ring->wptr_offs * 4);
	WREG32(mmCP_RB_WPTR_POLL_ADDR_LO, lower_32_bits(wptr_gpu_addr));
	WREG32(mmCP_RB_WPTR_POLL_ADDR_HI, upper_32_bits(wptr_gpu_addr));
	mdelay(1);
	WREG32(mmCP_RB0_CNTL, पंचांगp);

	rb_addr = ring->gpu_addr >> 8;
	WREG32(mmCP_RB0_BASE, rb_addr);
	WREG32(mmCP_RB0_BASE_HI, upper_32_bits(rb_addr));

	gfx_v8_0_set_cpg_करोor_bell(adev, ring);
	/* start the ring */
	amdgpu_ring_clear_ring(ring);
	gfx_v8_0_cp_gfx_start(adev);
	ring->sched.पढ़ोy = true;

	वापस 0;
पूर्ण

अटल व्योम gfx_v8_0_cp_compute_enable(काष्ठा amdgpu_device *adev, bool enable)
अणु
	अगर (enable) अणु
		WREG32(mmCP_MEC_CNTL, 0);
	पूर्ण अन्यथा अणु
		WREG32(mmCP_MEC_CNTL, (CP_MEC_CNTL__MEC_ME1_HALT_MASK | CP_MEC_CNTL__MEC_ME2_HALT_MASK));
		adev->gfx.kiq.ring.sched.पढ़ोy = false;
	पूर्ण
	udelay(50);
पूर्ण

/* KIQ functions */
अटल व्योम gfx_v8_0_kiq_setting(काष्ठा amdgpu_ring *ring)
अणु
	uपूर्णांक32_t पंचांगp;
	काष्ठा amdgpu_device *adev = ring->adev;

	/* tell RLC which is KIQ queue */
	पंचांगp = RREG32(mmRLC_CP_SCHEDULERS);
	पंचांगp &= 0xffffff00;
	पंचांगp |= (ring->me << 5) | (ring->pipe << 3) | (ring->queue);
	WREG32(mmRLC_CP_SCHEDULERS, पंचांगp);
	पंचांगp |= 0x80;
	WREG32(mmRLC_CP_SCHEDULERS, पंचांगp);
पूर्ण

अटल पूर्णांक gfx_v8_0_kiq_kcq_enable(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ring *kiq_ring = &adev->gfx.kiq.ring;
	uपूर्णांक64_t queue_mask = 0;
	पूर्णांक r, i;

	क्रम (i = 0; i < AMDGPU_MAX_COMPUTE_QUEUES; ++i) अणु
		अगर (!test_bit(i, adev->gfx.mec.queue_biपंचांगap))
			जारी;

		/* This situation may be hit in the future अगर a new HW
		 * generation exposes more than 64 queues. If so, the
		 * definition of queue_mask needs updating */
		अगर (WARN_ON(i >= (माप(queue_mask)*8))) अणु
			DRM_ERROR("Invalid KCQ enabled: %d\n", i);
			अवरोध;
		पूर्ण

		queue_mask |= (1ull << i);
	पूर्ण

	r = amdgpu_ring_alloc(kiq_ring, (8 * adev->gfx.num_compute_rings) + 8);
	अगर (r) अणु
		DRM_ERROR("Failed to lock KIQ (%d).\n", r);
		वापस r;
	पूर्ण
	/* set resources */
	amdgpu_ring_ग_लिखो(kiq_ring, PACKET3(PACKET3_SET_RESOURCES, 6));
	amdgpu_ring_ग_लिखो(kiq_ring, 0);	/* vmid_mask:0 queue_type:0 (KIQ) */
	amdgpu_ring_ग_लिखो(kiq_ring, lower_32_bits(queue_mask));	/* queue mask lo */
	amdgpu_ring_ग_लिखो(kiq_ring, upper_32_bits(queue_mask));	/* queue mask hi */
	amdgpu_ring_ग_लिखो(kiq_ring, 0);	/* gws mask lo */
	amdgpu_ring_ग_लिखो(kiq_ring, 0);	/* gws mask hi */
	amdgpu_ring_ग_लिखो(kiq_ring, 0);	/* oac mask */
	amdgpu_ring_ग_लिखो(kiq_ring, 0);	/* gds heap base:0, gds heap size:0 */
	क्रम (i = 0; i < adev->gfx.num_compute_rings; i++) अणु
		काष्ठा amdgpu_ring *ring = &adev->gfx.compute_ring[i];
		uपूर्णांक64_t mqd_addr = amdgpu_bo_gpu_offset(ring->mqd_obj);
		uपूर्णांक64_t wptr_addr = adev->wb.gpu_addr + (ring->wptr_offs * 4);

		/* map queues */
		amdgpu_ring_ग_लिखो(kiq_ring, PACKET3(PACKET3_MAP_QUEUES, 5));
		/* Q_sel:0, vmid:0, vidmem: 1, engine:0, num_Q:1*/
		amdgpu_ring_ग_लिखो(kiq_ring,
				  PACKET3_MAP_QUEUES_NUM_QUEUES(1));
		amdgpu_ring_ग_लिखो(kiq_ring,
				  PACKET3_MAP_QUEUES_DOORBELL_OFFSET(ring->करोorbell_index) |
				  PACKET3_MAP_QUEUES_QUEUE(ring->queue) |
				  PACKET3_MAP_QUEUES_PIPE(ring->pipe) |
				  PACKET3_MAP_QUEUES_ME(ring->me == 1 ? 0 : 1)); /* करोorbell */
		amdgpu_ring_ग_लिखो(kiq_ring, lower_32_bits(mqd_addr));
		amdgpu_ring_ग_लिखो(kiq_ring, upper_32_bits(mqd_addr));
		amdgpu_ring_ग_लिखो(kiq_ring, lower_32_bits(wptr_addr));
		amdgpu_ring_ग_लिखो(kiq_ring, upper_32_bits(wptr_addr));
	पूर्ण

	amdgpu_ring_commit(kiq_ring);

	वापस 0;
पूर्ण

अटल पूर्णांक gfx_v8_0_deactivate_hqd(काष्ठा amdgpu_device *adev, u32 req)
अणु
	पूर्णांक i, r = 0;

	अगर (RREG32(mmCP_HQD_ACTIVE) & CP_HQD_ACTIVE__ACTIVE_MASK) अणु
		WREG32_FIELD(CP_HQD_DEQUEUE_REQUEST, DEQUEUE_REQ, req);
		क्रम (i = 0; i < adev->usec_समयout; i++) अणु
			अगर (!(RREG32(mmCP_HQD_ACTIVE) & CP_HQD_ACTIVE__ACTIVE_MASK))
				अवरोध;
			udelay(1);
		पूर्ण
		अगर (i == adev->usec_समयout)
			r = -ETIMEDOUT;
	पूर्ण
	WREG32(mmCP_HQD_DEQUEUE_REQUEST, 0);
	WREG32(mmCP_HQD_PQ_RPTR, 0);
	WREG32(mmCP_HQD_PQ_WPTR, 0);

	वापस r;
पूर्ण

अटल व्योम gfx_v8_0_mqd_set_priority(काष्ठा amdgpu_ring *ring, काष्ठा vi_mqd *mqd)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	अगर (ring->funcs->type == AMDGPU_RING_TYPE_COMPUTE) अणु
		अगर (amdgpu_gfx_is_high_priority_compute_queue(adev, ring)) अणु
			mqd->cp_hqd_pipe_priority = AMDGPU_GFX_PIPE_PRIO_HIGH;
			mqd->cp_hqd_queue_priority =
				AMDGPU_GFX_QUEUE_PRIORITY_MAXIMUM;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक gfx_v8_0_mqd_init(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	काष्ठा vi_mqd *mqd = ring->mqd_ptr;
	uपूर्णांक64_t hqd_gpu_addr, wb_gpu_addr, eop_base_addr;
	uपूर्णांक32_t पंचांगp;

	mqd->header = 0xC0310800;
	mqd->compute_pipelinestat_enable = 0x00000001;
	mqd->compute_अटल_thपढ़ो_mgmt_se0 = 0xffffffff;
	mqd->compute_अटल_thपढ़ो_mgmt_se1 = 0xffffffff;
	mqd->compute_अटल_thपढ़ो_mgmt_se2 = 0xffffffff;
	mqd->compute_अटल_thपढ़ो_mgmt_se3 = 0xffffffff;
	mqd->compute_misc_reserved = 0x00000003;
	mqd->dynamic_cu_mask_addr_lo = lower_32_bits(ring->mqd_gpu_addr
						     + दुरत्व(काष्ठा vi_mqd_allocation, dynamic_cu_mask));
	mqd->dynamic_cu_mask_addr_hi = upper_32_bits(ring->mqd_gpu_addr
						     + दुरत्व(काष्ठा vi_mqd_allocation, dynamic_cu_mask));
	eop_base_addr = ring->eop_gpu_addr >> 8;
	mqd->cp_hqd_eop_base_addr_lo = eop_base_addr;
	mqd->cp_hqd_eop_base_addr_hi = upper_32_bits(eop_base_addr);

	/* set the EOP size, रेजिस्टर value is 2^(EOP_SIZE+1) dwords */
	पंचांगp = RREG32(mmCP_HQD_EOP_CONTROL);
	पंचांगp = REG_SET_FIELD(पंचांगp, CP_HQD_EOP_CONTROL, EOP_SIZE,
			(order_base_2(GFX8_MEC_HPD_SIZE / 4) - 1));

	mqd->cp_hqd_eop_control = पंचांगp;

	/* enable करोorbell? */
	पंचांगp = REG_SET_FIELD(RREG32(mmCP_HQD_PQ_DOORBELL_CONTROL),
			    CP_HQD_PQ_DOORBELL_CONTROL,
			    DOORBELL_EN,
			    ring->use_करोorbell ? 1 : 0);

	mqd->cp_hqd_pq_करोorbell_control = पंचांगp;

	/* set the poपूर्णांकer to the MQD */
	mqd->cp_mqd_base_addr_lo = ring->mqd_gpu_addr & 0xfffffffc;
	mqd->cp_mqd_base_addr_hi = upper_32_bits(ring->mqd_gpu_addr);

	/* set MQD vmid to 0 */
	पंचांगp = RREG32(mmCP_MQD_CONTROL);
	पंचांगp = REG_SET_FIELD(पंचांगp, CP_MQD_CONTROL, VMID, 0);
	mqd->cp_mqd_control = पंचांगp;

	/* set the poपूर्णांकer to the HQD, this is similar CP_RB0_BASE/_HI */
	hqd_gpu_addr = ring->gpu_addr >> 8;
	mqd->cp_hqd_pq_base_lo = hqd_gpu_addr;
	mqd->cp_hqd_pq_base_hi = upper_32_bits(hqd_gpu_addr);

	/* set up the HQD, this is similar to CP_RB0_CNTL */
	पंचांगp = RREG32(mmCP_HQD_PQ_CONTROL);
	पंचांगp = REG_SET_FIELD(पंचांगp, CP_HQD_PQ_CONTROL, QUEUE_SIZE,
			    (order_base_2(ring->ring_size / 4) - 1));
	पंचांगp = REG_SET_FIELD(पंचांगp, CP_HQD_PQ_CONTROL, RPTR_BLOCK_SIZE,
			((order_base_2(AMDGPU_GPU_PAGE_SIZE / 4) - 1) << 8));
#अगर_घोषित __BIG_ENDIAN
	पंचांगp = REG_SET_FIELD(पंचांगp, CP_HQD_PQ_CONTROL, ENDIAN_SWAP, 1);
#पूर्ण_अगर
	पंचांगp = REG_SET_FIELD(पंचांगp, CP_HQD_PQ_CONTROL, UNORD_DISPATCH, 0);
	पंचांगp = REG_SET_FIELD(पंचांगp, CP_HQD_PQ_CONTROL, ROQ_PQ_IB_FLIP, 0);
	पंचांगp = REG_SET_FIELD(पंचांगp, CP_HQD_PQ_CONTROL, PRIV_STATE, 1);
	पंचांगp = REG_SET_FIELD(पंचांगp, CP_HQD_PQ_CONTROL, KMD_QUEUE, 1);
	mqd->cp_hqd_pq_control = पंचांगp;

	/* set the wb address whether it's enabled or not */
	wb_gpu_addr = adev->wb.gpu_addr + (ring->rptr_offs * 4);
	mqd->cp_hqd_pq_rptr_report_addr_lo = wb_gpu_addr & 0xfffffffc;
	mqd->cp_hqd_pq_rptr_report_addr_hi =
		upper_32_bits(wb_gpu_addr) & 0xffff;

	/* only used अगर CP_PQ_WPTR_POLL_CNTL.CP_PQ_WPTR_POLL_CNTL__EN_MASK=1 */
	wb_gpu_addr = adev->wb.gpu_addr + (ring->wptr_offs * 4);
	mqd->cp_hqd_pq_wptr_poll_addr_lo = wb_gpu_addr & 0xfffffffc;
	mqd->cp_hqd_pq_wptr_poll_addr_hi = upper_32_bits(wb_gpu_addr) & 0xffff;

	पंचांगp = 0;
	/* enable the करोorbell अगर requested */
	अगर (ring->use_करोorbell) अणु
		पंचांगp = RREG32(mmCP_HQD_PQ_DOORBELL_CONTROL);
		पंचांगp = REG_SET_FIELD(पंचांगp, CP_HQD_PQ_DOORBELL_CONTROL,
				DOORBELL_OFFSET, ring->करोorbell_index);

		पंचांगp = REG_SET_FIELD(पंचांगp, CP_HQD_PQ_DOORBELL_CONTROL,
					 DOORBELL_EN, 1);
		पंचांगp = REG_SET_FIELD(पंचांगp, CP_HQD_PQ_DOORBELL_CONTROL,
					 DOORBELL_SOURCE, 0);
		पंचांगp = REG_SET_FIELD(पंचांगp, CP_HQD_PQ_DOORBELL_CONTROL,
					 DOORBELL_HIT, 0);
	पूर्ण

	mqd->cp_hqd_pq_करोorbell_control = पंचांगp;

	/* reset पढ़ो and ग_लिखो poपूर्णांकers, similar to CP_RB0_WPTR/_RPTR */
	ring->wptr = 0;
	mqd->cp_hqd_pq_wptr = ring->wptr;
	mqd->cp_hqd_pq_rptr = RREG32(mmCP_HQD_PQ_RPTR);

	/* set the vmid क्रम the queue */
	mqd->cp_hqd_vmid = 0;

	पंचांगp = RREG32(mmCP_HQD_PERSISTENT_STATE);
	पंचांगp = REG_SET_FIELD(पंचांगp, CP_HQD_PERSISTENT_STATE, PRELOAD_SIZE, 0x53);
	mqd->cp_hqd_persistent_state = पंचांगp;

	/* set MTYPE */
	पंचांगp = RREG32(mmCP_HQD_IB_CONTROL);
	पंचांगp = REG_SET_FIELD(पंचांगp, CP_HQD_IB_CONTROL, MIN_IB_AVAIL_SIZE, 3);
	पंचांगp = REG_SET_FIELD(पंचांगp, CP_HQD_IB_CONTROL, MTYPE, 3);
	mqd->cp_hqd_ib_control = पंचांगp;

	पंचांगp = RREG32(mmCP_HQD_IQ_TIMER);
	पंचांगp = REG_SET_FIELD(पंचांगp, CP_HQD_IQ_TIMER, MTYPE, 3);
	mqd->cp_hqd_iq_समयr = पंचांगp;

	पंचांगp = RREG32(mmCP_HQD_CTX_SAVE_CONTROL);
	पंचांगp = REG_SET_FIELD(पंचांगp, CP_HQD_CTX_SAVE_CONTROL, MTYPE, 3);
	mqd->cp_hqd_ctx_save_control = पंचांगp;

	/* शेषs */
	mqd->cp_hqd_eop_rptr = RREG32(mmCP_HQD_EOP_RPTR);
	mqd->cp_hqd_eop_wptr = RREG32(mmCP_HQD_EOP_WPTR);
	mqd->cp_hqd_ctx_save_base_addr_lo = RREG32(mmCP_HQD_CTX_SAVE_BASE_ADDR_LO);
	mqd->cp_hqd_ctx_save_base_addr_hi = RREG32(mmCP_HQD_CTX_SAVE_BASE_ADDR_HI);
	mqd->cp_hqd_cntl_stack_offset = RREG32(mmCP_HQD_CNTL_STACK_OFFSET);
	mqd->cp_hqd_cntl_stack_size = RREG32(mmCP_HQD_CNTL_STACK_SIZE);
	mqd->cp_hqd_wg_state_offset = RREG32(mmCP_HQD_WG_STATE_OFFSET);
	mqd->cp_hqd_ctx_save_size = RREG32(mmCP_HQD_CTX_SAVE_SIZE);
	mqd->cp_hqd_eop_करोne_events = RREG32(mmCP_HQD_EOP_EVENTS);
	mqd->cp_hqd_error = RREG32(mmCP_HQD_ERROR);
	mqd->cp_hqd_eop_wptr_mem = RREG32(mmCP_HQD_EOP_WPTR_MEM);
	mqd->cp_hqd_eop_करोnes = RREG32(mmCP_HQD_EOP_DONES);

	/* set अटल priority क्रम a queue/ring */
	gfx_v8_0_mqd_set_priority(ring, mqd);
	mqd->cp_hqd_quantum = RREG32(mmCP_HQD_QUANTUM);

	/* map_queues packet करोesn't need activate the queue,
	 * so only kiq need set this field.
	 */
	अगर (ring->funcs->type == AMDGPU_RING_TYPE_KIQ)
		mqd->cp_hqd_active = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक gfx_v8_0_mqd_commit(काष्ठा amdgpu_device *adev,
			काष्ठा vi_mqd *mqd)
अणु
	uपूर्णांक32_t mqd_reg;
	uपूर्णांक32_t *mqd_data;

	/* HQD रेजिस्टरs extend from mmCP_MQD_BASE_ADDR to mmCP_HQD_ERROR */
	mqd_data = &mqd->cp_mqd_base_addr_lo;

	/* disable wptr polling */
	WREG32_FIELD(CP_PQ_WPTR_POLL_CNTL, EN, 0);

	/* program all HQD रेजिस्टरs */
	क्रम (mqd_reg = mmCP_HQD_VMID; mqd_reg <= mmCP_HQD_EOP_CONTROL; mqd_reg++)
		WREG32(mqd_reg, mqd_data[mqd_reg - mmCP_MQD_BASE_ADDR]);

	/* Tonga errata: EOP RPTR/WPTR should be left unmodअगरied.
	 * This is safe since EOP RPTR==WPTR क्रम any inactive HQD
	 * on ASICs that करो not support context-save.
	 * EOP ग_लिखोs/पढ़ोs can start anywhere in the ring.
	 */
	अगर (adev->asic_type != CHIP_TONGA) अणु
		WREG32(mmCP_HQD_EOP_RPTR, mqd->cp_hqd_eop_rptr);
		WREG32(mmCP_HQD_EOP_WPTR, mqd->cp_hqd_eop_wptr);
		WREG32(mmCP_HQD_EOP_WPTR_MEM, mqd->cp_hqd_eop_wptr_mem);
	पूर्ण

	क्रम (mqd_reg = mmCP_HQD_EOP_EVENTS; mqd_reg <= mmCP_HQD_ERROR; mqd_reg++)
		WREG32(mqd_reg, mqd_data[mqd_reg - mmCP_MQD_BASE_ADDR]);

	/* activate the HQD */
	क्रम (mqd_reg = mmCP_MQD_BASE_ADDR; mqd_reg <= mmCP_HQD_ACTIVE; mqd_reg++)
		WREG32(mqd_reg, mqd_data[mqd_reg - mmCP_MQD_BASE_ADDR]);

	वापस 0;
पूर्ण

अटल पूर्णांक gfx_v8_0_kiq_init_queue(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	काष्ठा vi_mqd *mqd = ring->mqd_ptr;
	पूर्णांक mqd_idx = AMDGPU_MAX_COMPUTE_RINGS;

	gfx_v8_0_kiq_setting(ring);

	अगर (amdgpu_in_reset(adev)) अणु /* क्रम GPU_RESET हाल */
		/* reset MQD to a clean status */
		अगर (adev->gfx.mec.mqd_backup[mqd_idx])
			स_नकल(mqd, adev->gfx.mec.mqd_backup[mqd_idx], माप(काष्ठा vi_mqd_allocation));

		/* reset ring buffer */
		ring->wptr = 0;
		amdgpu_ring_clear_ring(ring);
		mutex_lock(&adev->srbm_mutex);
		vi_srbm_select(adev, ring->me, ring->pipe, ring->queue, 0);
		gfx_v8_0_mqd_commit(adev, mqd);
		vi_srbm_select(adev, 0, 0, 0, 0);
		mutex_unlock(&adev->srbm_mutex);
	पूर्ण अन्यथा अणु
		स_रखो((व्योम *)mqd, 0, माप(काष्ठा vi_mqd_allocation));
		((काष्ठा vi_mqd_allocation *)mqd)->dynamic_cu_mask = 0xFFFFFFFF;
		((काष्ठा vi_mqd_allocation *)mqd)->dynamic_rb_mask = 0xFFFFFFFF;
		mutex_lock(&adev->srbm_mutex);
		vi_srbm_select(adev, ring->me, ring->pipe, ring->queue, 0);
		gfx_v8_0_mqd_init(ring);
		gfx_v8_0_mqd_commit(adev, mqd);
		vi_srbm_select(adev, 0, 0, 0, 0);
		mutex_unlock(&adev->srbm_mutex);

		अगर (adev->gfx.mec.mqd_backup[mqd_idx])
			स_नकल(adev->gfx.mec.mqd_backup[mqd_idx], mqd, माप(काष्ठा vi_mqd_allocation));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gfx_v8_0_kcq_init_queue(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	काष्ठा vi_mqd *mqd = ring->mqd_ptr;
	पूर्णांक mqd_idx = ring - &adev->gfx.compute_ring[0];

	अगर (!amdgpu_in_reset(adev) && !adev->in_suspend) अणु
		स_रखो((व्योम *)mqd, 0, माप(काष्ठा vi_mqd_allocation));
		((काष्ठा vi_mqd_allocation *)mqd)->dynamic_cu_mask = 0xFFFFFFFF;
		((काष्ठा vi_mqd_allocation *)mqd)->dynamic_rb_mask = 0xFFFFFFFF;
		mutex_lock(&adev->srbm_mutex);
		vi_srbm_select(adev, ring->me, ring->pipe, ring->queue, 0);
		gfx_v8_0_mqd_init(ring);
		vi_srbm_select(adev, 0, 0, 0, 0);
		mutex_unlock(&adev->srbm_mutex);

		अगर (adev->gfx.mec.mqd_backup[mqd_idx])
			स_नकल(adev->gfx.mec.mqd_backup[mqd_idx], mqd, माप(काष्ठा vi_mqd_allocation));
	पूर्ण अन्यथा अगर (amdgpu_in_reset(adev)) अणु /* क्रम GPU_RESET हाल */
		/* reset MQD to a clean status */
		अगर (adev->gfx.mec.mqd_backup[mqd_idx])
			स_नकल(mqd, adev->gfx.mec.mqd_backup[mqd_idx], माप(काष्ठा vi_mqd_allocation));
		/* reset ring buffer */
		ring->wptr = 0;
		amdgpu_ring_clear_ring(ring);
	पूर्ण अन्यथा अणु
		amdgpu_ring_clear_ring(ring);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम gfx_v8_0_set_mec_करोorbell_range(काष्ठा amdgpu_device *adev)
अणु
	अगर (adev->asic_type > CHIP_TONGA) अणु
		WREG32(mmCP_MEC_DOORBELL_RANGE_LOWER, adev->करोorbell_index.kiq << 2);
		WREG32(mmCP_MEC_DOORBELL_RANGE_UPPER, adev->करोorbell_index.mec_ring7 << 2);
	पूर्ण
	/* enable करोorbells */
	WREG32_FIELD(CP_PQ_STATUS, DOORBELL_ENABLE, 1);
पूर्ण

अटल पूर्णांक gfx_v8_0_kiq_resume(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ring *ring;
	पूर्णांक r;

	ring = &adev->gfx.kiq.ring;

	r = amdgpu_bo_reserve(ring->mqd_obj, false);
	अगर (unlikely(r != 0))
		वापस r;

	r = amdgpu_bo_kmap(ring->mqd_obj, &ring->mqd_ptr);
	अगर (unlikely(r != 0))
		वापस r;

	gfx_v8_0_kiq_init_queue(ring);
	amdgpu_bo_kunmap(ring->mqd_obj);
	ring->mqd_ptr = शून्य;
	amdgpu_bo_unreserve(ring->mqd_obj);
	ring->sched.पढ़ोy = true;
	वापस 0;
पूर्ण

अटल पूर्णांक gfx_v8_0_kcq_resume(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ring *ring = शून्य;
	पूर्णांक r = 0, i;

	gfx_v8_0_cp_compute_enable(adev, true);

	क्रम (i = 0; i < adev->gfx.num_compute_rings; i++) अणु
		ring = &adev->gfx.compute_ring[i];

		r = amdgpu_bo_reserve(ring->mqd_obj, false);
		अगर (unlikely(r != 0))
			जाओ करोne;
		r = amdgpu_bo_kmap(ring->mqd_obj, &ring->mqd_ptr);
		अगर (!r) अणु
			r = gfx_v8_0_kcq_init_queue(ring);
			amdgpu_bo_kunmap(ring->mqd_obj);
			ring->mqd_ptr = शून्य;
		पूर्ण
		amdgpu_bo_unreserve(ring->mqd_obj);
		अगर (r)
			जाओ करोne;
	पूर्ण

	gfx_v8_0_set_mec_करोorbell_range(adev);

	r = gfx_v8_0_kiq_kcq_enable(adev);
	अगर (r)
		जाओ करोne;

करोne:
	वापस r;
पूर्ण

अटल पूर्णांक gfx_v8_0_cp_test_all_rings(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक r, i;
	काष्ठा amdgpu_ring *ring;

	/* collect all the ring_tests here, gfx, kiq, compute */
	ring = &adev->gfx.gfx_ring[0];
	r = amdgpu_ring_test_helper(ring);
	अगर (r)
		वापस r;

	ring = &adev->gfx.kiq.ring;
	r = amdgpu_ring_test_helper(ring);
	अगर (r)
		वापस r;

	क्रम (i = 0; i < adev->gfx.num_compute_rings; i++) अणु
		ring = &adev->gfx.compute_ring[i];
		amdgpu_ring_test_helper(ring);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gfx_v8_0_cp_resume(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक r;

	अगर (!(adev->flags & AMD_IS_APU))
		gfx_v8_0_enable_gui_idle_पूर्णांकerrupt(adev, false);

	r = gfx_v8_0_kiq_resume(adev);
	अगर (r)
		वापस r;

	r = gfx_v8_0_cp_gfx_resume(adev);
	अगर (r)
		वापस r;

	r = gfx_v8_0_kcq_resume(adev);
	अगर (r)
		वापस r;

	r = gfx_v8_0_cp_test_all_rings(adev);
	अगर (r)
		वापस r;

	gfx_v8_0_enable_gui_idle_पूर्णांकerrupt(adev, true);

	वापस 0;
पूर्ण

अटल व्योम gfx_v8_0_cp_enable(काष्ठा amdgpu_device *adev, bool enable)
अणु
	gfx_v8_0_cp_gfx_enable(adev, enable);
	gfx_v8_0_cp_compute_enable(adev, enable);
पूर्ण

अटल पूर्णांक gfx_v8_0_hw_init(व्योम *handle)
अणु
	पूर्णांक r;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	gfx_v8_0_init_golden_रेजिस्टरs(adev);
	gfx_v8_0_स्थिरants_init(adev);

	r = adev->gfx.rlc.funcs->resume(adev);
	अगर (r)
		वापस r;

	r = gfx_v8_0_cp_resume(adev);

	वापस r;
पूर्ण

अटल पूर्णांक gfx_v8_0_kcq_disable(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक r, i;
	काष्ठा amdgpu_ring *kiq_ring = &adev->gfx.kiq.ring;

	r = amdgpu_ring_alloc(kiq_ring, 6 * adev->gfx.num_compute_rings);
	अगर (r)
		DRM_ERROR("Failed to lock KIQ (%d).\n", r);

	क्रम (i = 0; i < adev->gfx.num_compute_rings; i++) अणु
		काष्ठा amdgpu_ring *ring = &adev->gfx.compute_ring[i];

		amdgpu_ring_ग_लिखो(kiq_ring, PACKET3(PACKET3_UNMAP_QUEUES, 4));
		amdgpu_ring_ग_लिखो(kiq_ring, /* Q_sel: 0, vmid: 0, engine: 0, num_Q: 1 */
						PACKET3_UNMAP_QUEUES_ACTION(1) | /* RESET_QUEUES */
						PACKET3_UNMAP_QUEUES_QUEUE_SEL(0) |
						PACKET3_UNMAP_QUEUES_ENGINE_SEL(0) |
						PACKET3_UNMAP_QUEUES_NUM_QUEUES(1));
		amdgpu_ring_ग_लिखो(kiq_ring, PACKET3_UNMAP_QUEUES_DOORBELL_OFFSET0(ring->करोorbell_index));
		amdgpu_ring_ग_लिखो(kiq_ring, 0);
		amdgpu_ring_ग_लिखो(kiq_ring, 0);
		amdgpu_ring_ग_लिखो(kiq_ring, 0);
	पूर्ण
	r = amdgpu_ring_test_helper(kiq_ring);
	अगर (r)
		DRM_ERROR("KCQ disable failed\n");

	वापस r;
पूर्ण

अटल bool gfx_v8_0_is_idle(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (REG_GET_FIELD(RREG32(mmGRBM_STATUS), GRBM_STATUS, GUI_ACTIVE)
		|| RREG32(mmGRBM_STATUS2) != 0x8)
		वापस false;
	अन्यथा
		वापस true;
पूर्ण

अटल bool gfx_v8_0_rlc_is_idle(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (RREG32(mmGRBM_STATUS2) != 0x8)
		वापस false;
	अन्यथा
		वापस true;
पूर्ण

अटल पूर्णांक gfx_v8_0_रुको_क्रम_rlc_idle(व्योम *handle)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	क्रम (i = 0; i < adev->usec_समयout; i++) अणु
		अगर (gfx_v8_0_rlc_is_idle(handle))
			वापस 0;

		udelay(1);
	पूर्ण
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक gfx_v8_0_रुको_क्रम_idle(व्योम *handle)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	क्रम (i = 0; i < adev->usec_समयout; i++) अणु
		अगर (gfx_v8_0_is_idle(handle))
			वापस 0;

		udelay(1);
	पूर्ण
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक gfx_v8_0_hw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	amdgpu_irq_put(adev, &adev->gfx.priv_reg_irq, 0);
	amdgpu_irq_put(adev, &adev->gfx.priv_inst_irq, 0);

	amdgpu_irq_put(adev, &adev->gfx.cp_ecc_error_irq, 0);

	amdgpu_irq_put(adev, &adev->gfx.sq_irq, 0);

	/* disable KCQ to aव्योम CPC touch memory not valid anymore */
	gfx_v8_0_kcq_disable(adev);

	अगर (amdgpu_sriov_vf(adev)) अणु
		pr_debug("For SRIOV client, shouldn't do anything.\n");
		वापस 0;
	पूर्ण
	amdgpu_gfx_rlc_enter_safe_mode(adev);
	अगर (!gfx_v8_0_रुको_क्रम_idle(adev))
		gfx_v8_0_cp_enable(adev, false);
	अन्यथा
		pr_err("cp is busy, skip halt cp\n");
	अगर (!gfx_v8_0_रुको_क्रम_rlc_idle(adev))
		adev->gfx.rlc.funcs->stop(adev);
	अन्यथा
		pr_err("rlc is busy, skip halt rlc\n");
	amdgpu_gfx_rlc_निकास_safe_mode(adev);

	वापस 0;
पूर्ण

अटल पूर्णांक gfx_v8_0_suspend(व्योम *handle)
अणु
	वापस gfx_v8_0_hw_fini(handle);
पूर्ण

अटल पूर्णांक gfx_v8_0_resume(व्योम *handle)
अणु
	वापस gfx_v8_0_hw_init(handle);
पूर्ण

अटल bool gfx_v8_0_check_soft_reset(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	u32 grbm_soft_reset = 0, srbm_soft_reset = 0;
	u32 पंचांगp;

	/* GRBM_STATUS */
	पंचांगp = RREG32(mmGRBM_STATUS);
	अगर (पंचांगp & (GRBM_STATUS__PA_BUSY_MASK | GRBM_STATUS__SC_BUSY_MASK |
		   GRBM_STATUS__BCI_BUSY_MASK | GRBM_STATUS__SX_BUSY_MASK |
		   GRBM_STATUS__TA_BUSY_MASK | GRBM_STATUS__VGT_BUSY_MASK |
		   GRBM_STATUS__DB_BUSY_MASK | GRBM_STATUS__CB_BUSY_MASK |
		   GRBM_STATUS__GDS_BUSY_MASK | GRBM_STATUS__SPI_BUSY_MASK |
		   GRBM_STATUS__IA_BUSY_MASK | GRBM_STATUS__IA_BUSY_NO_DMA_MASK |
		   GRBM_STATUS__CP_BUSY_MASK | GRBM_STATUS__CP_COHERENCY_BUSY_MASK)) अणु
		grbm_soft_reset = REG_SET_FIELD(grbm_soft_reset,
						GRBM_SOFT_RESET, SOFT_RESET_CP, 1);
		grbm_soft_reset = REG_SET_FIELD(grbm_soft_reset,
						GRBM_SOFT_RESET, SOFT_RESET_GFX, 1);
		srbm_soft_reset = REG_SET_FIELD(srbm_soft_reset,
						SRBM_SOFT_RESET, SOFT_RESET_GRBM, 1);
	पूर्ण

	/* GRBM_STATUS2 */
	पंचांगp = RREG32(mmGRBM_STATUS2);
	अगर (REG_GET_FIELD(पंचांगp, GRBM_STATUS2, RLC_BUSY))
		grbm_soft_reset = REG_SET_FIELD(grbm_soft_reset,
						GRBM_SOFT_RESET, SOFT_RESET_RLC, 1);

	अगर (REG_GET_FIELD(पंचांगp, GRBM_STATUS2, CPF_BUSY) ||
	    REG_GET_FIELD(पंचांगp, GRBM_STATUS2, CPC_BUSY) ||
	    REG_GET_FIELD(पंचांगp, GRBM_STATUS2, CPG_BUSY)) अणु
		grbm_soft_reset = REG_SET_FIELD(grbm_soft_reset, GRBM_SOFT_RESET,
						SOFT_RESET_CPF, 1);
		grbm_soft_reset = REG_SET_FIELD(grbm_soft_reset, GRBM_SOFT_RESET,
						SOFT_RESET_CPC, 1);
		grbm_soft_reset = REG_SET_FIELD(grbm_soft_reset, GRBM_SOFT_RESET,
						SOFT_RESET_CPG, 1);
		srbm_soft_reset = REG_SET_FIELD(srbm_soft_reset, SRBM_SOFT_RESET,
						SOFT_RESET_GRBM, 1);
	पूर्ण

	/* SRBM_STATUS */
	पंचांगp = RREG32(mmSRBM_STATUS);
	अगर (REG_GET_FIELD(पंचांगp, SRBM_STATUS, GRBM_RQ_PENDING))
		srbm_soft_reset = REG_SET_FIELD(srbm_soft_reset,
						SRBM_SOFT_RESET, SOFT_RESET_GRBM, 1);
	अगर (REG_GET_FIELD(पंचांगp, SRBM_STATUS, SEM_BUSY))
		srbm_soft_reset = REG_SET_FIELD(srbm_soft_reset,
						SRBM_SOFT_RESET, SOFT_RESET_SEM, 1);

	अगर (grbm_soft_reset || srbm_soft_reset) अणु
		adev->gfx.grbm_soft_reset = grbm_soft_reset;
		adev->gfx.srbm_soft_reset = srbm_soft_reset;
		वापस true;
	पूर्ण अन्यथा अणु
		adev->gfx.grbm_soft_reset = 0;
		adev->gfx.srbm_soft_reset = 0;
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक gfx_v8_0_pre_soft_reset(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	u32 grbm_soft_reset = 0;

	अगर ((!adev->gfx.grbm_soft_reset) &&
	    (!adev->gfx.srbm_soft_reset))
		वापस 0;

	grbm_soft_reset = adev->gfx.grbm_soft_reset;

	/* stop the rlc */
	adev->gfx.rlc.funcs->stop(adev);

	अगर (REG_GET_FIELD(grbm_soft_reset, GRBM_SOFT_RESET, SOFT_RESET_CP) ||
	    REG_GET_FIELD(grbm_soft_reset, GRBM_SOFT_RESET, SOFT_RESET_GFX))
		/* Disable GFX parsing/prefetching */
		gfx_v8_0_cp_gfx_enable(adev, false);

	अगर (REG_GET_FIELD(grbm_soft_reset, GRBM_SOFT_RESET, SOFT_RESET_CP) ||
	    REG_GET_FIELD(grbm_soft_reset, GRBM_SOFT_RESET, SOFT_RESET_CPF) ||
	    REG_GET_FIELD(grbm_soft_reset, GRBM_SOFT_RESET, SOFT_RESET_CPC) ||
	    REG_GET_FIELD(grbm_soft_reset, GRBM_SOFT_RESET, SOFT_RESET_CPG)) अणु
		पूर्णांक i;

		क्रम (i = 0; i < adev->gfx.num_compute_rings; i++) अणु
			काष्ठा amdgpu_ring *ring = &adev->gfx.compute_ring[i];

			mutex_lock(&adev->srbm_mutex);
			vi_srbm_select(adev, ring->me, ring->pipe, ring->queue, 0);
			gfx_v8_0_deactivate_hqd(adev, 2);
			vi_srbm_select(adev, 0, 0, 0, 0);
			mutex_unlock(&adev->srbm_mutex);
		पूर्ण
		/* Disable MEC parsing/prefetching */
		gfx_v8_0_cp_compute_enable(adev, false);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gfx_v8_0_soft_reset(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	u32 grbm_soft_reset = 0, srbm_soft_reset = 0;
	u32 पंचांगp;

	अगर ((!adev->gfx.grbm_soft_reset) &&
	    (!adev->gfx.srbm_soft_reset))
		वापस 0;

	grbm_soft_reset = adev->gfx.grbm_soft_reset;
	srbm_soft_reset = adev->gfx.srbm_soft_reset;

	अगर (grbm_soft_reset || srbm_soft_reset) अणु
		पंचांगp = RREG32(mmGMCON_DEBUG);
		पंचांगp = REG_SET_FIELD(पंचांगp, GMCON_DEBUG, GFX_STALL, 1);
		पंचांगp = REG_SET_FIELD(पंचांगp, GMCON_DEBUG, GFX_CLEAR, 1);
		WREG32(mmGMCON_DEBUG, पंचांगp);
		udelay(50);
	पूर्ण

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

	अगर (grbm_soft_reset || srbm_soft_reset) अणु
		पंचांगp = RREG32(mmGMCON_DEBUG);
		पंचांगp = REG_SET_FIELD(पंचांगp, GMCON_DEBUG, GFX_STALL, 0);
		पंचांगp = REG_SET_FIELD(पंचांगp, GMCON_DEBUG, GFX_CLEAR, 0);
		WREG32(mmGMCON_DEBUG, पंचांगp);
	पूर्ण

	/* Wait a little क्रम things to settle करोwn */
	udelay(50);

	वापस 0;
पूर्ण

अटल पूर्णांक gfx_v8_0_post_soft_reset(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	u32 grbm_soft_reset = 0;

	अगर ((!adev->gfx.grbm_soft_reset) &&
	    (!adev->gfx.srbm_soft_reset))
		वापस 0;

	grbm_soft_reset = adev->gfx.grbm_soft_reset;

	अगर (REG_GET_FIELD(grbm_soft_reset, GRBM_SOFT_RESET, SOFT_RESET_CP) ||
	    REG_GET_FIELD(grbm_soft_reset, GRBM_SOFT_RESET, SOFT_RESET_CPF) ||
	    REG_GET_FIELD(grbm_soft_reset, GRBM_SOFT_RESET, SOFT_RESET_CPC) ||
	    REG_GET_FIELD(grbm_soft_reset, GRBM_SOFT_RESET, SOFT_RESET_CPG)) अणु
		पूर्णांक i;

		क्रम (i = 0; i < adev->gfx.num_compute_rings; i++) अणु
			काष्ठा amdgpu_ring *ring = &adev->gfx.compute_ring[i];

			mutex_lock(&adev->srbm_mutex);
			vi_srbm_select(adev, ring->me, ring->pipe, ring->queue, 0);
			gfx_v8_0_deactivate_hqd(adev, 2);
			vi_srbm_select(adev, 0, 0, 0, 0);
			mutex_unlock(&adev->srbm_mutex);
		पूर्ण
		gfx_v8_0_kiq_resume(adev);
		gfx_v8_0_kcq_resume(adev);
	पूर्ण

	अगर (REG_GET_FIELD(grbm_soft_reset, GRBM_SOFT_RESET, SOFT_RESET_CP) ||
	    REG_GET_FIELD(grbm_soft_reset, GRBM_SOFT_RESET, SOFT_RESET_GFX))
		gfx_v8_0_cp_gfx_resume(adev);

	gfx_v8_0_cp_test_all_rings(adev);

	adev->gfx.rlc.funcs->start(adev);

	वापस 0;
पूर्ण

/**
 * gfx_v8_0_get_gpu_घड़ी_counter - वापस GPU घड़ी counter snapshot
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Fetches a GPU घड़ी counter snapshot.
 * Returns the 64 bit घड़ी counter snapshot.
 */
अटल uपूर्णांक64_t gfx_v8_0_get_gpu_घड़ी_counter(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक64_t घड़ी;

	mutex_lock(&adev->gfx.gpu_घड़ी_mutex);
	WREG32(mmRLC_CAPTURE_GPU_CLOCK_COUNT, 1);
	घड़ी = (uपूर्णांक64_t)RREG32(mmRLC_GPU_CLOCK_COUNT_LSB) |
		((uपूर्णांक64_t)RREG32(mmRLC_GPU_CLOCK_COUNT_MSB) << 32ULL);
	mutex_unlock(&adev->gfx.gpu_घड़ी_mutex);
	वापस घड़ी;
पूर्ण

अटल व्योम gfx_v8_0_ring_emit_gds_चयन(काष्ठा amdgpu_ring *ring,
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

अटल व्योम gfx_v8_0_पढ़ो_wave_data(काष्ठा amdgpu_device *adev, uपूर्णांक32_t simd, uपूर्णांक32_t wave, uपूर्णांक32_t *dst, पूर्णांक *no_fields)
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

अटल व्योम gfx_v8_0_पढ़ो_wave_sgprs(काष्ठा amdgpu_device *adev, uपूर्णांक32_t simd,
				     uपूर्णांक32_t wave, uपूर्णांक32_t start,
				     uपूर्णांक32_t size, uपूर्णांक32_t *dst)
अणु
	wave_पढ़ो_regs(
		adev, simd, wave, 0,
		start + SQIND_WAVE_SGPRS_OFFSET, size, dst);
पूर्ण


अटल स्थिर काष्ठा amdgpu_gfx_funcs gfx_v8_0_gfx_funcs = अणु
	.get_gpu_घड़ी_counter = &gfx_v8_0_get_gpu_घड़ी_counter,
	.select_se_sh = &gfx_v8_0_select_se_sh,
	.पढ़ो_wave_data = &gfx_v8_0_पढ़ो_wave_data,
	.पढ़ो_wave_sgprs = &gfx_v8_0_पढ़ो_wave_sgprs,
	.select_me_pipe_q = &gfx_v8_0_select_me_pipe_q
पूर्ण;

अटल पूर्णांक gfx_v8_0_early_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	adev->gfx.num_gfx_rings = GFX8_NUM_GFX_RINGS;
	adev->gfx.num_compute_rings = min(amdgpu_gfx_get_num_kcq(adev),
					  AMDGPU_MAX_COMPUTE_RINGS);
	adev->gfx.funcs = &gfx_v8_0_gfx_funcs;
	gfx_v8_0_set_ring_funcs(adev);
	gfx_v8_0_set_irq_funcs(adev);
	gfx_v8_0_set_gds_init(adev);
	gfx_v8_0_set_rlc_funcs(adev);

	वापस 0;
पूर्ण

अटल पूर्णांक gfx_v8_0_late_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	पूर्णांक r;

	r = amdgpu_irq_get(adev, &adev->gfx.priv_reg_irq, 0);
	अगर (r)
		वापस r;

	r = amdgpu_irq_get(adev, &adev->gfx.priv_inst_irq, 0);
	अगर (r)
		वापस r;

	/* requires IBs so करो in late init after IB pool is initialized */
	r = gfx_v8_0_करो_edc_gpr_workarounds(adev);
	अगर (r)
		वापस r;

	r = amdgpu_irq_get(adev, &adev->gfx.cp_ecc_error_irq, 0);
	अगर (r) अणु
		DRM_ERROR("amdgpu_irq_get() failed to get IRQ for EDC, r: %d.\n", r);
		वापस r;
	पूर्ण

	r = amdgpu_irq_get(adev, &adev->gfx.sq_irq, 0);
	अगर (r) अणु
		DRM_ERROR(
			"amdgpu_irq_get() failed to get IRQ for SQ, r: %d.\n",
			r);
		वापस r;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम gfx_v8_0_enable_gfx_अटल_mg_घातer_gating(काष्ठा amdgpu_device *adev,
						       bool enable)
अणु
	अगर ((adev->asic_type == CHIP_POLARIS11) ||
	    (adev->asic_type == CHIP_POLARIS12) ||
	    (adev->asic_type == CHIP_VEGAM))
		/* Send msg to SMU via Powerplay */
		amdgpu_dpm_set_घातergating_by_smu(adev, AMD_IP_BLOCK_TYPE_GFX, enable);

	WREG32_FIELD(RLC_PG_CNTL, STATIC_PER_CU_PG_ENABLE, enable ? 1 : 0);
पूर्ण

अटल व्योम gfx_v8_0_enable_gfx_dynamic_mg_घातer_gating(काष्ठा amdgpu_device *adev,
							bool enable)
अणु
	WREG32_FIELD(RLC_PG_CNTL, DYN_PER_CU_PG_ENABLE, enable ? 1 : 0);
पूर्ण

अटल व्योम polaris11_enable_gfx_quick_mg_घातer_gating(काष्ठा amdgpu_device *adev,
		bool enable)
अणु
	WREG32_FIELD(RLC_PG_CNTL, QUICK_PG_ENABLE, enable ? 1 : 0);
पूर्ण

अटल व्योम cz_enable_gfx_cg_घातer_gating(काष्ठा amdgpu_device *adev,
					  bool enable)
अणु
	WREG32_FIELD(RLC_PG_CNTL, GFX_POWER_GATING_ENABLE, enable ? 1 : 0);
पूर्ण

अटल व्योम cz_enable_gfx_pipeline_घातer_gating(काष्ठा amdgpu_device *adev,
						bool enable)
अणु
	WREG32_FIELD(RLC_PG_CNTL, GFX_PIPELINE_PG_ENABLE, enable ? 1 : 0);

	/* Read any GFX रेजिस्टर to wake up GFX. */
	अगर (!enable)
		RREG32(mmDB_RENDER_CONTROL);
पूर्ण

अटल व्योम cz_update_gfx_cg_घातer_gating(काष्ठा amdgpu_device *adev,
					  bool enable)
अणु
	अगर ((adev->pg_flags & AMD_PG_SUPPORT_GFX_PG) && enable) अणु
		cz_enable_gfx_cg_घातer_gating(adev, true);
		अगर (adev->pg_flags & AMD_PG_SUPPORT_GFX_PIPELINE)
			cz_enable_gfx_pipeline_घातer_gating(adev, true);
	पूर्ण अन्यथा अणु
		cz_enable_gfx_cg_घातer_gating(adev, false);
		cz_enable_gfx_pipeline_घातer_gating(adev, false);
	पूर्ण
पूर्ण

अटल पूर्णांक gfx_v8_0_set_घातergating_state(व्योम *handle,
					  क्रमागत amd_घातergating_state state)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	bool enable = (state == AMD_PG_STATE_GATE);

	अगर (amdgpu_sriov_vf(adev))
		वापस 0;

	अगर (adev->pg_flags & (AMD_PG_SUPPORT_GFX_SMG |
				AMD_PG_SUPPORT_RLC_SMU_HS |
				AMD_PG_SUPPORT_CP |
				AMD_PG_SUPPORT_GFX_DMG))
		amdgpu_gfx_rlc_enter_safe_mode(adev);
	चयन (adev->asic_type) अणु
	हाल CHIP_CARRIZO:
	हाल CHIP_STONEY:

		अगर (adev->pg_flags & AMD_PG_SUPPORT_RLC_SMU_HS) अणु
			cz_enable_sck_slow_करोwn_on_घातer_up(adev, true);
			cz_enable_sck_slow_करोwn_on_घातer_करोwn(adev, true);
		पूर्ण अन्यथा अणु
			cz_enable_sck_slow_करोwn_on_घातer_up(adev, false);
			cz_enable_sck_slow_करोwn_on_घातer_करोwn(adev, false);
		पूर्ण
		अगर (adev->pg_flags & AMD_PG_SUPPORT_CP)
			cz_enable_cp_घातer_gating(adev, true);
		अन्यथा
			cz_enable_cp_घातer_gating(adev, false);

		cz_update_gfx_cg_घातer_gating(adev, enable);

		अगर ((adev->pg_flags & AMD_PG_SUPPORT_GFX_SMG) && enable)
			gfx_v8_0_enable_gfx_अटल_mg_घातer_gating(adev, true);
		अन्यथा
			gfx_v8_0_enable_gfx_अटल_mg_घातer_gating(adev, false);

		अगर ((adev->pg_flags & AMD_PG_SUPPORT_GFX_DMG) && enable)
			gfx_v8_0_enable_gfx_dynamic_mg_घातer_gating(adev, true);
		अन्यथा
			gfx_v8_0_enable_gfx_dynamic_mg_घातer_gating(adev, false);
		अवरोध;
	हाल CHIP_POLARIS11:
	हाल CHIP_POLARIS12:
	हाल CHIP_VEGAM:
		अगर ((adev->pg_flags & AMD_PG_SUPPORT_GFX_SMG) && enable)
			gfx_v8_0_enable_gfx_अटल_mg_घातer_gating(adev, true);
		अन्यथा
			gfx_v8_0_enable_gfx_अटल_mg_घातer_gating(adev, false);

		अगर ((adev->pg_flags & AMD_PG_SUPPORT_GFX_DMG) && enable)
			gfx_v8_0_enable_gfx_dynamic_mg_घातer_gating(adev, true);
		अन्यथा
			gfx_v8_0_enable_gfx_dynamic_mg_घातer_gating(adev, false);

		अगर ((adev->pg_flags & AMD_PG_SUPPORT_GFX_QUICK_MG) && enable)
			polaris11_enable_gfx_quick_mg_घातer_gating(adev, true);
		अन्यथा
			polaris11_enable_gfx_quick_mg_घातer_gating(adev, false);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	अगर (adev->pg_flags & (AMD_PG_SUPPORT_GFX_SMG |
				AMD_PG_SUPPORT_RLC_SMU_HS |
				AMD_PG_SUPPORT_CP |
				AMD_PG_SUPPORT_GFX_DMG))
		amdgpu_gfx_rlc_निकास_safe_mode(adev);
	वापस 0;
पूर्ण

अटल व्योम gfx_v8_0_get_घड़ीgating_state(व्योम *handle, u32 *flags)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	पूर्णांक data;

	अगर (amdgpu_sriov_vf(adev))
		*flags = 0;

	/* AMD_CG_SUPPORT_GFX_MGCG */
	data = RREG32(mmRLC_CGTT_MGCG_OVERRIDE);
	अगर (!(data & RLC_CGTT_MGCG_OVERRIDE__CPF_MASK))
		*flags |= AMD_CG_SUPPORT_GFX_MGCG;

	/* AMD_CG_SUPPORT_GFX_CGLG */
	data = RREG32(mmRLC_CGCG_CGLS_CTRL);
	अगर (data & RLC_CGCG_CGLS_CTRL__CGCG_EN_MASK)
		*flags |= AMD_CG_SUPPORT_GFX_CGCG;

	/* AMD_CG_SUPPORT_GFX_CGLS */
	अगर (data & RLC_CGCG_CGLS_CTRL__CGLS_EN_MASK)
		*flags |= AMD_CG_SUPPORT_GFX_CGLS;

	/* AMD_CG_SUPPORT_GFX_CGTS */
	data = RREG32(mmCGTS_SM_CTRL_REG);
	अगर (!(data & CGTS_SM_CTRL_REG__OVERRIDE_MASK))
		*flags |= AMD_CG_SUPPORT_GFX_CGTS;

	/* AMD_CG_SUPPORT_GFX_CGTS_LS */
	अगर (!(data & CGTS_SM_CTRL_REG__LS_OVERRIDE_MASK))
		*flags |= AMD_CG_SUPPORT_GFX_CGTS_LS;

	/* AMD_CG_SUPPORT_GFX_RLC_LS */
	data = RREG32(mmRLC_MEM_SLP_CNTL);
	अगर (data & RLC_MEM_SLP_CNTL__RLC_MEM_LS_EN_MASK)
		*flags |= AMD_CG_SUPPORT_GFX_RLC_LS | AMD_CG_SUPPORT_GFX_MGLS;

	/* AMD_CG_SUPPORT_GFX_CP_LS */
	data = RREG32(mmCP_MEM_SLP_CNTL);
	अगर (data & CP_MEM_SLP_CNTL__CP_MEM_LS_EN_MASK)
		*flags |= AMD_CG_SUPPORT_GFX_CP_LS | AMD_CG_SUPPORT_GFX_MGLS;
पूर्ण

अटल व्योम gfx_v8_0_send_serdes_cmd(काष्ठा amdgpu_device *adev,
				     uपूर्णांक32_t reg_addr, uपूर्णांक32_t cmd)
अणु
	uपूर्णांक32_t data;

	gfx_v8_0_select_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff);

	WREG32(mmRLC_SERDES_WR_CU_MASTER_MASK, 0xffffffff);
	WREG32(mmRLC_SERDES_WR_NONCU_MASTER_MASK, 0xffffffff);

	data = RREG32(mmRLC_SERDES_WR_CTRL);
	अगर (adev->asic_type == CHIP_STONEY)
		data &= ~(RLC_SERDES_WR_CTRL__WRITE_COMMAND_MASK |
			  RLC_SERDES_WR_CTRL__READ_COMMAND_MASK |
			  RLC_SERDES_WR_CTRL__P1_SELECT_MASK |
			  RLC_SERDES_WR_CTRL__P2_SELECT_MASK |
			  RLC_SERDES_WR_CTRL__RDDATA_RESET_MASK |
			  RLC_SERDES_WR_CTRL__POWER_DOWN_MASK |
			  RLC_SERDES_WR_CTRL__POWER_UP_MASK |
			  RLC_SERDES_WR_CTRL__SHORT_FORMAT_MASK |
			  RLC_SERDES_WR_CTRL__SRBM_OVERRIDE_MASK);
	अन्यथा
		data &= ~(RLC_SERDES_WR_CTRL__WRITE_COMMAND_MASK |
			  RLC_SERDES_WR_CTRL__READ_COMMAND_MASK |
			  RLC_SERDES_WR_CTRL__P1_SELECT_MASK |
			  RLC_SERDES_WR_CTRL__P2_SELECT_MASK |
			  RLC_SERDES_WR_CTRL__RDDATA_RESET_MASK |
			  RLC_SERDES_WR_CTRL__POWER_DOWN_MASK |
			  RLC_SERDES_WR_CTRL__POWER_UP_MASK |
			  RLC_SERDES_WR_CTRL__SHORT_FORMAT_MASK |
			  RLC_SERDES_WR_CTRL__BPM_DATA_MASK |
			  RLC_SERDES_WR_CTRL__REG_ADDR_MASK |
			  RLC_SERDES_WR_CTRL__SRBM_OVERRIDE_MASK);
	data |= (RLC_SERDES_WR_CTRL__RSVD_BPM_ADDR_MASK |
		 (cmd << RLC_SERDES_WR_CTRL__BPM_DATA__SHIFT) |
		 (reg_addr << RLC_SERDES_WR_CTRL__REG_ADDR__SHIFT) |
		 (0xff << RLC_SERDES_WR_CTRL__BPM_ADDR__SHIFT));

	WREG32(mmRLC_SERDES_WR_CTRL, data);
पूर्ण

#घोषणा MSG_ENTER_RLC_SAFE_MODE     1
#घोषणा MSG_EXIT_RLC_SAFE_MODE      0
#घोषणा RLC_GPR_REG2__REQ_MASK 0x00000001
#घोषणा RLC_GPR_REG2__REQ__SHIFT 0
#घोषणा RLC_GPR_REG2__MESSAGE__SHIFT 0x00000001
#घोषणा RLC_GPR_REG2__MESSAGE_MASK 0x0000001e

अटल bool gfx_v8_0_is_rlc_enabled(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक32_t rlc_setting;

	rlc_setting = RREG32(mmRLC_CNTL);
	अगर (!(rlc_setting & RLC_CNTL__RLC_ENABLE_F32_MASK))
		वापस false;

	वापस true;
पूर्ण

अटल व्योम gfx_v8_0_set_safe_mode(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक32_t data;
	अचिन्हित i;
	data = RREG32(mmRLC_CNTL);
	data |= RLC_SAFE_MODE__CMD_MASK;
	data &= ~RLC_SAFE_MODE__MESSAGE_MASK;
	data |= (1 << RLC_SAFE_MODE__MESSAGE__SHIFT);
	WREG32(mmRLC_SAFE_MODE, data);

	/* रुको क्रम RLC_SAFE_MODE */
	क्रम (i = 0; i < adev->usec_समयout; i++) अणु
		अगर ((RREG32(mmRLC_GPM_STAT) &
		     (RLC_GPM_STAT__GFX_CLOCK_STATUS_MASK |
		      RLC_GPM_STAT__GFX_POWER_STATUS_MASK)) ==
		    (RLC_GPM_STAT__GFX_CLOCK_STATUS_MASK |
		     RLC_GPM_STAT__GFX_POWER_STATUS_MASK))
			अवरोध;
		udelay(1);
	पूर्ण
	क्रम (i = 0; i < adev->usec_समयout; i++) अणु
		अगर (!REG_GET_FIELD(RREG32(mmRLC_SAFE_MODE), RLC_SAFE_MODE, CMD))
			अवरोध;
		udelay(1);
	पूर्ण
पूर्ण

अटल व्योम gfx_v8_0_unset_safe_mode(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक32_t data;
	अचिन्हित i;

	data = RREG32(mmRLC_CNTL);
	data |= RLC_SAFE_MODE__CMD_MASK;
	data &= ~RLC_SAFE_MODE__MESSAGE_MASK;
	WREG32(mmRLC_SAFE_MODE, data);

	क्रम (i = 0; i < adev->usec_समयout; i++) अणु
		अगर (!REG_GET_FIELD(RREG32(mmRLC_SAFE_MODE), RLC_SAFE_MODE, CMD))
			अवरोध;
		udelay(1);
	पूर्ण
पूर्ण

अटल व्योम gfx_v8_0_update_spm_vmid(काष्ठा amdgpu_device *adev, अचिन्हित vmid)
अणु
	u32 data;

	अगर (amdgpu_sriov_is_pp_one_vf(adev))
		data = RREG32_NO_KIQ(mmRLC_SPM_VMID);
	अन्यथा
		data = RREG32(mmRLC_SPM_VMID);

	data &= ~RLC_SPM_VMID__RLC_SPM_VMID_MASK;
	data |= (vmid & RLC_SPM_VMID__RLC_SPM_VMID_MASK) << RLC_SPM_VMID__RLC_SPM_VMID__SHIFT;

	अगर (amdgpu_sriov_is_pp_one_vf(adev))
		WREG32_NO_KIQ(mmRLC_SPM_VMID, data);
	अन्यथा
		WREG32(mmRLC_SPM_VMID, data);
पूर्ण

अटल स्थिर काष्ठा amdgpu_rlc_funcs iceland_rlc_funcs = अणु
	.is_rlc_enabled = gfx_v8_0_is_rlc_enabled,
	.set_safe_mode = gfx_v8_0_set_safe_mode,
	.unset_safe_mode = gfx_v8_0_unset_safe_mode,
	.init = gfx_v8_0_rlc_init,
	.get_csb_size = gfx_v8_0_get_csb_size,
	.get_csb_buffer = gfx_v8_0_get_csb_buffer,
	.get_cp_table_num = gfx_v8_0_cp_jump_table_num,
	.resume = gfx_v8_0_rlc_resume,
	.stop = gfx_v8_0_rlc_stop,
	.reset = gfx_v8_0_rlc_reset,
	.start = gfx_v8_0_rlc_start,
	.update_spm_vmid = gfx_v8_0_update_spm_vmid
पूर्ण;

अटल व्योम gfx_v8_0_update_medium_grain_घड़ी_gating(काष्ठा amdgpu_device *adev,
						      bool enable)
अणु
	uपूर्णांक32_t temp, data;

	amdgpu_gfx_rlc_enter_safe_mode(adev);

	/* It is disabled by HW by शेष */
	अगर (enable && (adev->cg_flags & AMD_CG_SUPPORT_GFX_MGCG)) अणु
		अगर (adev->cg_flags & AMD_CG_SUPPORT_GFX_MGLS) अणु
			अगर (adev->cg_flags & AMD_CG_SUPPORT_GFX_RLC_LS)
				/* 1 - RLC memory Light sleep */
				WREG32_FIELD(RLC_MEM_SLP_CNTL, RLC_MEM_LS_EN, 1);

			अगर (adev->cg_flags & AMD_CG_SUPPORT_GFX_CP_LS)
				WREG32_FIELD(CP_MEM_SLP_CNTL, CP_MEM_LS_EN, 1);
		पूर्ण

		/* 3 - RLC_CGTT_MGCG_OVERRIDE */
		temp = data = RREG32(mmRLC_CGTT_MGCG_OVERRIDE);
		अगर (adev->flags & AMD_IS_APU)
			data &= ~(RLC_CGTT_MGCG_OVERRIDE__CPF_MASK |
				  RLC_CGTT_MGCG_OVERRIDE__RLC_MASK |
				  RLC_CGTT_MGCG_OVERRIDE__MGCG_MASK);
		अन्यथा
			data &= ~(RLC_CGTT_MGCG_OVERRIDE__CPF_MASK |
				  RLC_CGTT_MGCG_OVERRIDE__RLC_MASK |
				  RLC_CGTT_MGCG_OVERRIDE__MGCG_MASK |
				  RLC_CGTT_MGCG_OVERRIDE__GRBM_MASK);

		अगर (temp != data)
			WREG32(mmRLC_CGTT_MGCG_OVERRIDE, data);

		/* 4 - रुको क्रम RLC_SERDES_CU_MASTER & RLC_SERDES_NONCU_MASTER idle */
		gfx_v8_0_रुको_क्रम_rlc_serdes(adev);

		/* 5 - clear mgcg override */
		gfx_v8_0_send_serdes_cmd(adev, BPM_REG_MGCG_OVERRIDE, CLE_BPM_SERDES_CMD);

		अगर (adev->cg_flags & AMD_CG_SUPPORT_GFX_CGTS) अणु
			/* 6 - Enable CGTS(Tree Shade) MGCG /MGLS */
			temp = data = RREG32(mmCGTS_SM_CTRL_REG);
			data &= ~(CGTS_SM_CTRL_REG__SM_MODE_MASK);
			data |= (0x2 << CGTS_SM_CTRL_REG__SM_MODE__SHIFT);
			data |= CGTS_SM_CTRL_REG__SM_MODE_ENABLE_MASK;
			data &= ~CGTS_SM_CTRL_REG__OVERRIDE_MASK;
			अगर ((adev->cg_flags & AMD_CG_SUPPORT_GFX_MGLS) &&
			    (adev->cg_flags & AMD_CG_SUPPORT_GFX_CGTS_LS))
				data &= ~CGTS_SM_CTRL_REG__LS_OVERRIDE_MASK;
			data |= CGTS_SM_CTRL_REG__ON_MONITOR_ADD_EN_MASK;
			data |= (0x96 << CGTS_SM_CTRL_REG__ON_MONITOR_ADD__SHIFT);
			अगर (temp != data)
				WREG32(mmCGTS_SM_CTRL_REG, data);
		पूर्ण
		udelay(50);

		/* 7 - रुको क्रम RLC_SERDES_CU_MASTER & RLC_SERDES_NONCU_MASTER idle */
		gfx_v8_0_रुको_क्रम_rlc_serdes(adev);
	पूर्ण अन्यथा अणु
		/* 1 - MGCG_OVERRIDE[0] क्रम CP and MGCG_OVERRIDE[1] क्रम RLC */
		temp = data = RREG32(mmRLC_CGTT_MGCG_OVERRIDE);
		data |= (RLC_CGTT_MGCG_OVERRIDE__CPF_MASK |
				RLC_CGTT_MGCG_OVERRIDE__RLC_MASK |
				RLC_CGTT_MGCG_OVERRIDE__MGCG_MASK |
				RLC_CGTT_MGCG_OVERRIDE__GRBM_MASK);
		अगर (temp != data)
			WREG32(mmRLC_CGTT_MGCG_OVERRIDE, data);

		/* 2 - disable MGLS in RLC */
		data = RREG32(mmRLC_MEM_SLP_CNTL);
		अगर (data & RLC_MEM_SLP_CNTL__RLC_MEM_LS_EN_MASK) अणु
			data &= ~RLC_MEM_SLP_CNTL__RLC_MEM_LS_EN_MASK;
			WREG32(mmRLC_MEM_SLP_CNTL, data);
		पूर्ण

		/* 3 - disable MGLS in CP */
		data = RREG32(mmCP_MEM_SLP_CNTL);
		अगर (data & CP_MEM_SLP_CNTL__CP_MEM_LS_EN_MASK) अणु
			data &= ~CP_MEM_SLP_CNTL__CP_MEM_LS_EN_MASK;
			WREG32(mmCP_MEM_SLP_CNTL, data);
		पूर्ण

		/* 4 - Disable CGTS(Tree Shade) MGCG and MGLS */
		temp = data = RREG32(mmCGTS_SM_CTRL_REG);
		data |= (CGTS_SM_CTRL_REG__OVERRIDE_MASK |
				CGTS_SM_CTRL_REG__LS_OVERRIDE_MASK);
		अगर (temp != data)
			WREG32(mmCGTS_SM_CTRL_REG, data);

		/* 5 - रुको क्रम RLC_SERDES_CU_MASTER & RLC_SERDES_NONCU_MASTER idle */
		gfx_v8_0_रुको_क्रम_rlc_serdes(adev);

		/* 6 - set mgcg override */
		gfx_v8_0_send_serdes_cmd(adev, BPM_REG_MGCG_OVERRIDE, SET_BPM_SERDES_CMD);

		udelay(50);

		/* 7- रुको क्रम RLC_SERDES_CU_MASTER & RLC_SERDES_NONCU_MASTER idle */
		gfx_v8_0_रुको_क्रम_rlc_serdes(adev);
	पूर्ण

	amdgpu_gfx_rlc_निकास_safe_mode(adev);
पूर्ण

अटल व्योम gfx_v8_0_update_coarse_grain_घड़ी_gating(काष्ठा amdgpu_device *adev,
						      bool enable)
अणु
	uपूर्णांक32_t temp, temp1, data, data1;

	temp = data = RREG32(mmRLC_CGCG_CGLS_CTRL);

	amdgpu_gfx_rlc_enter_safe_mode(adev);

	अगर (enable && (adev->cg_flags & AMD_CG_SUPPORT_GFX_CGCG)) अणु
		temp1 = data1 =	RREG32(mmRLC_CGTT_MGCG_OVERRIDE);
		data1 &= ~RLC_CGTT_MGCG_OVERRIDE__CGCG_MASK;
		अगर (temp1 != data1)
			WREG32(mmRLC_CGTT_MGCG_OVERRIDE, data1);

		/* : रुको क्रम RLC_SERDES_CU_MASTER & RLC_SERDES_NONCU_MASTER idle */
		gfx_v8_0_रुको_क्रम_rlc_serdes(adev);

		/* 2 - clear cgcg override */
		gfx_v8_0_send_serdes_cmd(adev, BPM_REG_CGCG_OVERRIDE, CLE_BPM_SERDES_CMD);

		/* रुको क्रम RLC_SERDES_CU_MASTER & RLC_SERDES_NONCU_MASTER idle */
		gfx_v8_0_रुको_क्रम_rlc_serdes(adev);

		/* 3 - ग_लिखो cmd to set CGLS */
		gfx_v8_0_send_serdes_cmd(adev, BPM_REG_CGLS_EN, SET_BPM_SERDES_CMD);

		/* 4 - enable cgcg */
		data |= RLC_CGCG_CGLS_CTRL__CGCG_EN_MASK;

		अगर (adev->cg_flags & AMD_CG_SUPPORT_GFX_CGLS) अणु
			/* enable cgls*/
			data |= RLC_CGCG_CGLS_CTRL__CGLS_EN_MASK;

			temp1 = data1 =	RREG32(mmRLC_CGTT_MGCG_OVERRIDE);
			data1 &= ~RLC_CGTT_MGCG_OVERRIDE__CGLS_MASK;

			अगर (temp1 != data1)
				WREG32(mmRLC_CGTT_MGCG_OVERRIDE, data1);
		पूर्ण अन्यथा अणु
			data &= ~RLC_CGCG_CGLS_CTRL__CGLS_EN_MASK;
		पूर्ण

		अगर (temp != data)
			WREG32(mmRLC_CGCG_CGLS_CTRL, data);

		/* 5 enable cntx_empty_पूर्णांक_enable/cntx_busy_पूर्णांक_enable/
		 * Cmp_busy/GFX_Idle पूर्णांकerrupts
		 */
		gfx_v8_0_enable_gui_idle_पूर्णांकerrupt(adev, true);
	पूर्ण अन्यथा अणु
		/* disable cntx_empty_पूर्णांक_enable & GFX Idle पूर्णांकerrupt */
		gfx_v8_0_enable_gui_idle_पूर्णांकerrupt(adev, false);

		/* TEST CGCG */
		temp1 = data1 =	RREG32(mmRLC_CGTT_MGCG_OVERRIDE);
		data1 |= (RLC_CGTT_MGCG_OVERRIDE__CGCG_MASK |
				RLC_CGTT_MGCG_OVERRIDE__CGLS_MASK);
		अगर (temp1 != data1)
			WREG32(mmRLC_CGTT_MGCG_OVERRIDE, data1);

		/* पढ़ो gfx रेजिस्टर to wake up cgcg */
		RREG32(mmCB_CGTT_SCLK_CTRL);
		RREG32(mmCB_CGTT_SCLK_CTRL);
		RREG32(mmCB_CGTT_SCLK_CTRL);
		RREG32(mmCB_CGTT_SCLK_CTRL);

		/* रुको क्रम RLC_SERDES_CU_MASTER & RLC_SERDES_NONCU_MASTER idle */
		gfx_v8_0_रुको_क्रम_rlc_serdes(adev);

		/* ग_लिखो cmd to Set CGCG Overrride */
		gfx_v8_0_send_serdes_cmd(adev, BPM_REG_CGCG_OVERRIDE, SET_BPM_SERDES_CMD);

		/* रुको क्रम RLC_SERDES_CU_MASTER & RLC_SERDES_NONCU_MASTER idle */
		gfx_v8_0_रुको_क्रम_rlc_serdes(adev);

		/* ग_लिखो cmd to Clear CGLS */
		gfx_v8_0_send_serdes_cmd(adev, BPM_REG_CGLS_EN, CLE_BPM_SERDES_CMD);

		/* disable cgcg, cgls should be disabled too. */
		data &= ~(RLC_CGCG_CGLS_CTRL__CGCG_EN_MASK |
			  RLC_CGCG_CGLS_CTRL__CGLS_EN_MASK);
		अगर (temp != data)
			WREG32(mmRLC_CGCG_CGLS_CTRL, data);
		/* enable पूर्णांकerrupts again क्रम PG */
		gfx_v8_0_enable_gui_idle_पूर्णांकerrupt(adev, true);
	पूर्ण

	gfx_v8_0_रुको_क्रम_rlc_serdes(adev);

	amdgpu_gfx_rlc_निकास_safe_mode(adev);
पूर्ण
अटल पूर्णांक gfx_v8_0_update_gfx_घड़ी_gating(काष्ठा amdgpu_device *adev,
					    bool enable)
अणु
	अगर (enable) अणु
		/* CGCG/CGLS should be enabled after MGCG/MGLS/TS(CG/LS)
		 * ===  MGCG + MGLS + TS(CG/LS) ===
		 */
		gfx_v8_0_update_medium_grain_घड़ी_gating(adev, enable);
		gfx_v8_0_update_coarse_grain_घड़ी_gating(adev, enable);
	पूर्ण अन्यथा अणु
		/* CGCG/CGLS should be disabled beक्रमe MGCG/MGLS/TS(CG/LS)
		 * ===  CGCG + CGLS ===
		 */
		gfx_v8_0_update_coarse_grain_घड़ी_gating(adev, enable);
		gfx_v8_0_update_medium_grain_घड़ी_gating(adev, enable);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक gfx_v8_0_tonga_update_gfx_घड़ी_gating(काष्ठा amdgpu_device *adev,
					  क्रमागत amd_घड़ीgating_state state)
अणु
	uपूर्णांक32_t msg_id, pp_state = 0;
	uपूर्णांक32_t pp_support_state = 0;

	अगर (adev->cg_flags & (AMD_CG_SUPPORT_GFX_CGCG | AMD_CG_SUPPORT_GFX_CGLS)) अणु
		अगर (adev->cg_flags & AMD_CG_SUPPORT_GFX_CGLS) अणु
			pp_support_state = PP_STATE_SUPPORT_LS;
			pp_state = PP_STATE_LS;
		पूर्ण
		अगर (adev->cg_flags & AMD_CG_SUPPORT_GFX_CGCG) अणु
			pp_support_state |= PP_STATE_SUPPORT_CG;
			pp_state |= PP_STATE_CG;
		पूर्ण
		अगर (state == AMD_CG_STATE_UNGATE)
			pp_state = 0;

		msg_id = PP_CG_MSG_ID(PP_GROUP_GFX,
				PP_BLOCK_GFX_CG,
				pp_support_state,
				pp_state);
		amdgpu_dpm_set_घड़ीgating_by_smu(adev, msg_id);
	पूर्ण

	अगर (adev->cg_flags & (AMD_CG_SUPPORT_GFX_MGCG | AMD_CG_SUPPORT_GFX_MGLS)) अणु
		अगर (adev->cg_flags & AMD_CG_SUPPORT_GFX_MGLS) अणु
			pp_support_state = PP_STATE_SUPPORT_LS;
			pp_state = PP_STATE_LS;
		पूर्ण

		अगर (adev->cg_flags & AMD_CG_SUPPORT_GFX_MGCG) अणु
			pp_support_state |= PP_STATE_SUPPORT_CG;
			pp_state |= PP_STATE_CG;
		पूर्ण

		अगर (state == AMD_CG_STATE_UNGATE)
			pp_state = 0;

		msg_id = PP_CG_MSG_ID(PP_GROUP_GFX,
				PP_BLOCK_GFX_MG,
				pp_support_state,
				pp_state);
		amdgpu_dpm_set_घड़ीgating_by_smu(adev, msg_id);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gfx_v8_0_polaris_update_gfx_घड़ी_gating(काष्ठा amdgpu_device *adev,
					  क्रमागत amd_घड़ीgating_state state)
अणु

	uपूर्णांक32_t msg_id, pp_state = 0;
	uपूर्णांक32_t pp_support_state = 0;

	अगर (adev->cg_flags & (AMD_CG_SUPPORT_GFX_CGCG | AMD_CG_SUPPORT_GFX_CGLS)) अणु
		अगर (adev->cg_flags & AMD_CG_SUPPORT_GFX_CGLS) अणु
			pp_support_state = PP_STATE_SUPPORT_LS;
			pp_state = PP_STATE_LS;
		पूर्ण
		अगर (adev->cg_flags & AMD_CG_SUPPORT_GFX_CGCG) अणु
			pp_support_state |= PP_STATE_SUPPORT_CG;
			pp_state |= PP_STATE_CG;
		पूर्ण
		अगर (state == AMD_CG_STATE_UNGATE)
			pp_state = 0;

		msg_id = PP_CG_MSG_ID(PP_GROUP_GFX,
				PP_BLOCK_GFX_CG,
				pp_support_state,
				pp_state);
		amdgpu_dpm_set_घड़ीgating_by_smu(adev, msg_id);
	पूर्ण

	अगर (adev->cg_flags & (AMD_CG_SUPPORT_GFX_3D_CGCG | AMD_CG_SUPPORT_GFX_3D_CGLS)) अणु
		अगर (adev->cg_flags & AMD_CG_SUPPORT_GFX_3D_CGLS) अणु
			pp_support_state = PP_STATE_SUPPORT_LS;
			pp_state = PP_STATE_LS;
		पूर्ण
		अगर (adev->cg_flags & AMD_CG_SUPPORT_GFX_3D_CGCG) अणु
			pp_support_state |= PP_STATE_SUPPORT_CG;
			pp_state |= PP_STATE_CG;
		पूर्ण
		अगर (state == AMD_CG_STATE_UNGATE)
			pp_state = 0;

		msg_id = PP_CG_MSG_ID(PP_GROUP_GFX,
				PP_BLOCK_GFX_3D,
				pp_support_state,
				pp_state);
		amdgpu_dpm_set_घड़ीgating_by_smu(adev, msg_id);
	पूर्ण

	अगर (adev->cg_flags & (AMD_CG_SUPPORT_GFX_MGCG | AMD_CG_SUPPORT_GFX_MGLS)) अणु
		अगर (adev->cg_flags & AMD_CG_SUPPORT_GFX_MGLS) अणु
			pp_support_state = PP_STATE_SUPPORT_LS;
			pp_state = PP_STATE_LS;
		पूर्ण

		अगर (adev->cg_flags & AMD_CG_SUPPORT_GFX_MGCG) अणु
			pp_support_state |= PP_STATE_SUPPORT_CG;
			pp_state |= PP_STATE_CG;
		पूर्ण

		अगर (state == AMD_CG_STATE_UNGATE)
			pp_state = 0;

		msg_id = PP_CG_MSG_ID(PP_GROUP_GFX,
				PP_BLOCK_GFX_MG,
				pp_support_state,
				pp_state);
		amdgpu_dpm_set_घड़ीgating_by_smu(adev, msg_id);
	पूर्ण

	अगर (adev->cg_flags & AMD_CG_SUPPORT_GFX_RLC_LS) अणु
		pp_support_state = PP_STATE_SUPPORT_LS;

		अगर (state == AMD_CG_STATE_UNGATE)
			pp_state = 0;
		अन्यथा
			pp_state = PP_STATE_LS;

		msg_id = PP_CG_MSG_ID(PP_GROUP_GFX,
				PP_BLOCK_GFX_RLC,
				pp_support_state,
				pp_state);
		amdgpu_dpm_set_घड़ीgating_by_smu(adev, msg_id);
	पूर्ण

	अगर (adev->cg_flags & AMD_CG_SUPPORT_GFX_CP_LS) अणु
		pp_support_state = PP_STATE_SUPPORT_LS;

		अगर (state == AMD_CG_STATE_UNGATE)
			pp_state = 0;
		अन्यथा
			pp_state = PP_STATE_LS;
		msg_id = PP_CG_MSG_ID(PP_GROUP_GFX,
			PP_BLOCK_GFX_CP,
			pp_support_state,
			pp_state);
		amdgpu_dpm_set_घड़ीgating_by_smu(adev, msg_id);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gfx_v8_0_set_घड़ीgating_state(व्योम *handle,
					  क्रमागत amd_घड़ीgating_state state)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (amdgpu_sriov_vf(adev))
		वापस 0;

	चयन (adev->asic_type) अणु
	हाल CHIP_FIJI:
	हाल CHIP_CARRIZO:
	हाल CHIP_STONEY:
		gfx_v8_0_update_gfx_घड़ी_gating(adev,
						 state == AMD_CG_STATE_GATE);
		अवरोध;
	हाल CHIP_TONGA:
		gfx_v8_0_tonga_update_gfx_घड़ी_gating(adev, state);
		अवरोध;
	हाल CHIP_POLARIS10:
	हाल CHIP_POLARIS11:
	हाल CHIP_POLARIS12:
	हाल CHIP_VEGAM:
		gfx_v8_0_polaris_update_gfx_घड़ी_gating(adev, state);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल u64 gfx_v8_0_ring_get_rptr(काष्ठा amdgpu_ring *ring)
अणु
	वापस ring->adev->wb.wb[ring->rptr_offs];
पूर्ण

अटल u64 gfx_v8_0_ring_get_wptr_gfx(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	अगर (ring->use_करोorbell)
		/* XXX check अगर swapping is necessary on BE */
		वापस ring->adev->wb.wb[ring->wptr_offs];
	अन्यथा
		वापस RREG32(mmCP_RB0_WPTR);
पूर्ण

अटल व्योम gfx_v8_0_ring_set_wptr_gfx(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	अगर (ring->use_करोorbell) अणु
		/* XXX check अगर swapping is necessary on BE */
		adev->wb.wb[ring->wptr_offs] = lower_32_bits(ring->wptr);
		WDOORBELL32(ring->करोorbell_index, lower_32_bits(ring->wptr));
	पूर्ण अन्यथा अणु
		WREG32(mmCP_RB0_WPTR, lower_32_bits(ring->wptr));
		(व्योम)RREG32(mmCP_RB0_WPTR);
	पूर्ण
पूर्ण

अटल व्योम gfx_v8_0_ring_emit_hdp_flush(काष्ठा amdgpu_ring *ring)
अणु
	u32 ref_and_mask, reg_mem_engine;

	अगर ((ring->funcs->type == AMDGPU_RING_TYPE_COMPUTE) ||
	    (ring->funcs->type == AMDGPU_RING_TYPE_KIQ)) अणु
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
		reg_mem_engine = 0;
	पूर्ण अन्यथा अणु
		ref_and_mask = GPU_HDP_FLUSH_DONE__CP0_MASK;
		reg_mem_engine = WAIT_REG_MEM_ENGINE(1); /* pfp */
	पूर्ण

	amdgpu_ring_ग_लिखो(ring, PACKET3(PACKET3_WAIT_REG_MEM, 5));
	amdgpu_ring_ग_लिखो(ring, (WAIT_REG_MEM_OPERATION(1) | /* ग_लिखो, रुको, ग_लिखो */
				 WAIT_REG_MEM_FUNCTION(3) |  /* == */
				 reg_mem_engine));
	amdgpu_ring_ग_लिखो(ring, mmGPU_HDP_FLUSH_REQ);
	amdgpu_ring_ग_लिखो(ring, mmGPU_HDP_FLUSH_DONE);
	amdgpu_ring_ग_लिखो(ring, ref_and_mask);
	amdgpu_ring_ग_लिखो(ring, ref_and_mask);
	amdgpu_ring_ग_लिखो(ring, 0x20); /* poll पूर्णांकerval */
पूर्ण

अटल व्योम gfx_v8_0_ring_emit_vgt_flush(काष्ठा amdgpu_ring *ring)
अणु
	amdgpu_ring_ग_लिखो(ring, PACKET3(PACKET3_EVENT_WRITE, 0));
	amdgpu_ring_ग_लिखो(ring, EVENT_TYPE(VS_PARTIAL_FLUSH) |
		EVENT_INDEX(4));

	amdgpu_ring_ग_लिखो(ring, PACKET3(PACKET3_EVENT_WRITE, 0));
	amdgpu_ring_ग_लिखो(ring, EVENT_TYPE(VGT_FLUSH) |
		EVENT_INDEX(0));
पूर्ण

अटल व्योम gfx_v8_0_ring_emit_ib_gfx(काष्ठा amdgpu_ring *ring,
					काष्ठा amdgpu_job *job,
					काष्ठा amdgpu_ib *ib,
					uपूर्णांक32_t flags)
अणु
	अचिन्हित vmid = AMDGPU_JOB_GET_VMID(job);
	u32 header, control = 0;

	अगर (ib->flags & AMDGPU_IB_FLAG_CE)
		header = PACKET3(PACKET3_INसूचीECT_BUFFER_CONST, 2);
	अन्यथा
		header = PACKET3(PACKET3_INसूचीECT_BUFFER, 2);

	control |= ib->length_dw | (vmid << 24);

	अगर (amdgpu_sriov_vf(ring->adev) && (ib->flags & AMDGPU_IB_FLAG_PREEMPT)) अणु
		control |= INसूचीECT_BUFFER_PRE_ENB(1);

		अगर (!(ib->flags & AMDGPU_IB_FLAG_CE) && vmid)
			gfx_v8_0_ring_emit_de_meta(ring);
	पूर्ण

	amdgpu_ring_ग_लिखो(ring, header);
	amdgpu_ring_ग_लिखो(ring,
#अगर_घोषित __BIG_ENDIAN
			  (2 << 0) |
#पूर्ण_अगर
			  (ib->gpu_addr & 0xFFFFFFFC));
	amdgpu_ring_ग_लिखो(ring, upper_32_bits(ib->gpu_addr) & 0xFFFF);
	amdgpu_ring_ग_लिखो(ring, control);
पूर्ण

अटल व्योम gfx_v8_0_ring_emit_ib_compute(काष्ठा amdgpu_ring *ring,
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

अटल व्योम gfx_v8_0_ring_emit_fence_gfx(काष्ठा amdgpu_ring *ring, u64 addr,
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
				 EOP_TC_WB_ACTION_EN |
				 EVENT_TYPE(CACHE_FLUSH_AND_INV_TS_EVENT) |
				 EVENT_INDEX(5)));
	amdgpu_ring_ग_लिखो(ring, addr & 0xfffffffc);
	amdgpu_ring_ग_लिखो(ring, (upper_32_bits(addr) & 0xffff) |
				DATA_SEL(1) | INT_SEL(0));
	amdgpu_ring_ग_लिखो(ring, lower_32_bits(seq - 1));
	amdgpu_ring_ग_लिखो(ring, upper_32_bits(seq - 1));

	/* Then send the real EOP event करोwn the pipe:
	 * EVENT_WRITE_EOP - flush caches, send पूर्णांक */
	amdgpu_ring_ग_लिखो(ring, PACKET3(PACKET3_EVENT_WRITE_EOP, 4));
	amdgpu_ring_ग_लिखो(ring, (EOP_TCL1_ACTION_EN |
				 EOP_TC_ACTION_EN |
				 EOP_TC_WB_ACTION_EN |
				 EVENT_TYPE(CACHE_FLUSH_AND_INV_TS_EVENT) |
				 EVENT_INDEX(5)));
	amdgpu_ring_ग_लिखो(ring, addr & 0xfffffffc);
	amdgpu_ring_ग_लिखो(ring, (upper_32_bits(addr) & 0xffff) |
			  DATA_SEL(ग_लिखो64bit ? 2 : 1) | INT_SEL(पूर्णांक_sel ? 2 : 0));
	amdgpu_ring_ग_लिखो(ring, lower_32_bits(seq));
	amdgpu_ring_ग_लिखो(ring, upper_32_bits(seq));

पूर्ण

अटल व्योम gfx_v8_0_ring_emit_pipeline_sync(काष्ठा amdgpu_ring *ring)
अणु
	पूर्णांक usepfp = (ring->funcs->type == AMDGPU_RING_TYPE_GFX);
	uपूर्णांक32_t seq = ring->fence_drv.sync_seq;
	uपूर्णांक64_t addr = ring->fence_drv.gpu_addr;

	amdgpu_ring_ग_लिखो(ring, PACKET3(PACKET3_WAIT_REG_MEM, 5));
	amdgpu_ring_ग_लिखो(ring, (WAIT_REG_MEM_MEM_SPACE(1) | /* memory */
				 WAIT_REG_MEM_FUNCTION(3) | /* equal */
				 WAIT_REG_MEM_ENGINE(usepfp))); /* pfp or me */
	amdgpu_ring_ग_लिखो(ring, addr & 0xfffffffc);
	amdgpu_ring_ग_लिखो(ring, upper_32_bits(addr) & 0xffffffff);
	amdgpu_ring_ग_लिखो(ring, seq);
	amdgpu_ring_ग_लिखो(ring, 0xffffffff);
	amdgpu_ring_ग_लिखो(ring, 4); /* poll पूर्णांकerval */
पूर्ण

अटल व्योम gfx_v8_0_ring_emit_vm_flush(काष्ठा amdgpu_ring *ring,
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
	पूर्ण
पूर्ण

अटल u64 gfx_v8_0_ring_get_wptr_compute(काष्ठा amdgpu_ring *ring)
अणु
	वापस ring->adev->wb.wb[ring->wptr_offs];
पूर्ण

अटल व्योम gfx_v8_0_ring_set_wptr_compute(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	/* XXX check अगर swapping is necessary on BE */
	adev->wb.wb[ring->wptr_offs] = lower_32_bits(ring->wptr);
	WDOORBELL32(ring->करोorbell_index, lower_32_bits(ring->wptr));
पूर्ण

अटल व्योम gfx_v8_0_ring_emit_fence_compute(काष्ठा amdgpu_ring *ring,
					     u64 addr, u64 seq,
					     अचिन्हित flags)
अणु
	bool ग_लिखो64bit = flags & AMDGPU_FENCE_FLAG_64BIT;
	bool पूर्णांक_sel = flags & AMDGPU_FENCE_FLAG_INT;

	/* RELEASE_MEM - flush caches, send पूर्णांक */
	amdgpu_ring_ग_लिखो(ring, PACKET3(PACKET3_RELEASE_MEM, 5));
	amdgpu_ring_ग_लिखो(ring, (EOP_TCL1_ACTION_EN |
				 EOP_TC_ACTION_EN |
				 EOP_TC_WB_ACTION_EN |
				 EVENT_TYPE(CACHE_FLUSH_AND_INV_TS_EVENT) |
				 EVENT_INDEX(5)));
	amdgpu_ring_ग_लिखो(ring, DATA_SEL(ग_लिखो64bit ? 2 : 1) | INT_SEL(पूर्णांक_sel ? 2 : 0));
	amdgpu_ring_ग_लिखो(ring, addr & 0xfffffffc);
	amdgpu_ring_ग_लिखो(ring, upper_32_bits(addr));
	amdgpu_ring_ग_लिखो(ring, lower_32_bits(seq));
	amdgpu_ring_ग_लिखो(ring, upper_32_bits(seq));
पूर्ण

अटल व्योम gfx_v8_0_ring_emit_fence_kiq(काष्ठा amdgpu_ring *ring, u64 addr,
					 u64 seq, अचिन्हित पूर्णांक flags)
अणु
	/* we only allocate 32bit क्रम each seq wb address */
	BUG_ON(flags & AMDGPU_FENCE_FLAG_64BIT);

	/* ग_लिखो fence seq to the "addr" */
	amdgpu_ring_ग_लिखो(ring, PACKET3(PACKET3_WRITE_DATA, 3));
	amdgpu_ring_ग_लिखो(ring, (WRITE_DATA_ENGINE_SEL(0) |
				 WRITE_DATA_DST_SEL(5) | WR_CONFIRM));
	amdgpu_ring_ग_लिखो(ring, lower_32_bits(addr));
	amdgpu_ring_ग_लिखो(ring, upper_32_bits(addr));
	amdgpu_ring_ग_लिखो(ring, lower_32_bits(seq));

	अगर (flags & AMDGPU_FENCE_FLAG_INT) अणु
		/* set रेजिस्टर to trigger INT */
		amdgpu_ring_ग_लिखो(ring, PACKET3(PACKET3_WRITE_DATA, 3));
		amdgpu_ring_ग_लिखो(ring, (WRITE_DATA_ENGINE_SEL(0) |
					 WRITE_DATA_DST_SEL(0) | WR_CONFIRM));
		amdgpu_ring_ग_लिखो(ring, mmCPC_INT_STATUS);
		amdgpu_ring_ग_लिखो(ring, 0);
		amdgpu_ring_ग_लिखो(ring, 0x20000000); /* src_id is 178 */
	पूर्ण
पूर्ण

अटल व्योम gfx_v8_ring_emit_sb(काष्ठा amdgpu_ring *ring)
अणु
	amdgpu_ring_ग_लिखो(ring, PACKET3(PACKET3_SWITCH_BUFFER, 0));
	amdgpu_ring_ग_लिखो(ring, 0);
पूर्ण

अटल व्योम gfx_v8_ring_emit_cntxcntl(काष्ठा amdgpu_ring *ring, uपूर्णांक32_t flags)
अणु
	uपूर्णांक32_t dw2 = 0;

	अगर (amdgpu_sriov_vf(ring->adev))
		gfx_v8_0_ring_emit_ce_meta(ring);

	dw2 |= 0x80000000; /* set load_enable otherwise this package is just NOPs */
	अगर (flags & AMDGPU_HAVE_CTX_SWITCH) अणु
		gfx_v8_0_ring_emit_vgt_flush(ring);
		/* set load_global_config & load_global_uconfig */
		dw2 |= 0x8001;
		/* set load_cs_sh_regs */
		dw2 |= 0x01000000;
		/* set load_per_context_state & load_gfx_sh_regs क्रम GFX */
		dw2 |= 0x10002;

		/* set load_ce_ram अगर preamble presented */
		अगर (AMDGPU_PREAMBLE_IB_PRESENT & flags)
			dw2 |= 0x10000000;
	पूर्ण अन्यथा अणु
		/* still load_ce_ram अगर this is the first समय preamble presented
		 * although there is no context चयन happens.
		 */
		अगर (AMDGPU_PREAMBLE_IB_PRESENT_FIRST & flags)
			dw2 |= 0x10000000;
	पूर्ण

	amdgpu_ring_ग_लिखो(ring, PACKET3(PACKET3_CONTEXT_CONTROL, 1));
	amdgpu_ring_ग_लिखो(ring, dw2);
	amdgpu_ring_ग_लिखो(ring, 0);
पूर्ण

अटल अचिन्हित gfx_v8_0_ring_emit_init_cond_exec(काष्ठा amdgpu_ring *ring)
अणु
	अचिन्हित ret;

	amdgpu_ring_ग_लिखो(ring, PACKET3(PACKET3_COND_EXEC, 3));
	amdgpu_ring_ग_लिखो(ring, lower_32_bits(ring->cond_exe_gpu_addr));
	amdgpu_ring_ग_लिखो(ring, upper_32_bits(ring->cond_exe_gpu_addr));
	amdgpu_ring_ग_लिखो(ring, 0); /* discard following DWs अगर *cond_exec_gpu_addr==0 */
	ret = ring->wptr & ring->buf_mask;
	amdgpu_ring_ग_लिखो(ring, 0x55aa55aa); /* patch dummy value later */
	वापस ret;
पूर्ण

अटल व्योम gfx_v8_0_ring_emit_patch_cond_exec(काष्ठा amdgpu_ring *ring, अचिन्हित offset)
अणु
	अचिन्हित cur;

	BUG_ON(offset > ring->buf_mask);
	BUG_ON(ring->ring[offset] != 0x55aa55aa);

	cur = (ring->wptr & ring->buf_mask) - 1;
	अगर (likely(cur > offset))
		ring->ring[offset] = cur - offset;
	अन्यथा
		ring->ring[offset] = (ring->ring_size >> 2) - offset + cur;
पूर्ण

अटल व्योम gfx_v8_0_ring_emit_rreg(काष्ठा amdgpu_ring *ring, uपूर्णांक32_t reg,
				    uपूर्णांक32_t reg_val_offs)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	amdgpu_ring_ग_लिखो(ring, PACKET3(PACKET3_COPY_DATA, 4));
	amdgpu_ring_ग_लिखो(ring, 0 |	/* src: रेजिस्टर*/
				(5 << 8) |	/* dst: memory */
				(1 << 20));	/* ग_लिखो confirm */
	amdgpu_ring_ग_लिखो(ring, reg);
	amdgpu_ring_ग_लिखो(ring, 0);
	amdgpu_ring_ग_लिखो(ring, lower_32_bits(adev->wb.gpu_addr +
				reg_val_offs * 4));
	amdgpu_ring_ग_लिखो(ring, upper_32_bits(adev->wb.gpu_addr +
				reg_val_offs * 4));
पूर्ण

अटल व्योम gfx_v8_0_ring_emit_wreg(काष्ठा amdgpu_ring *ring, uपूर्णांक32_t reg,
				  uपूर्णांक32_t val)
अणु
	uपूर्णांक32_t cmd;

	चयन (ring->funcs->type) अणु
	हाल AMDGPU_RING_TYPE_GFX:
		cmd = WRITE_DATA_ENGINE_SEL(1) | WR_CONFIRM;
		अवरोध;
	हाल AMDGPU_RING_TYPE_KIQ:
		cmd = 1 << 16; /* no inc addr */
		अवरोध;
	शेष:
		cmd = WR_CONFIRM;
		अवरोध;
	पूर्ण

	amdgpu_ring_ग_लिखो(ring, PACKET3(PACKET3_WRITE_DATA, 3));
	amdgpu_ring_ग_लिखो(ring, cmd);
	amdgpu_ring_ग_लिखो(ring, reg);
	amdgpu_ring_ग_लिखो(ring, 0);
	amdgpu_ring_ग_लिखो(ring, val);
पूर्ण

अटल व्योम gfx_v8_0_ring_soft_recovery(काष्ठा amdgpu_ring *ring, अचिन्हित vmid)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	uपूर्णांक32_t value = 0;

	value = REG_SET_FIELD(value, SQ_CMD, CMD, 0x03);
	value = REG_SET_FIELD(value, SQ_CMD, MODE, 0x01);
	value = REG_SET_FIELD(value, SQ_CMD, CHECK_VMID, 1);
	value = REG_SET_FIELD(value, SQ_CMD, VM_ID, vmid);
	WREG32(mmSQ_CMD, value);
पूर्ण

अटल व्योम gfx_v8_0_set_gfx_eop_पूर्णांकerrupt_state(काष्ठा amdgpu_device *adev,
						 क्रमागत amdgpu_पूर्णांकerrupt_state state)
अणु
	WREG32_FIELD(CP_INT_CNTL_RING0, TIME_STAMP_INT_ENABLE,
		     state == AMDGPU_IRQ_STATE_DISABLE ? 0 : 1);
पूर्ण

अटल व्योम gfx_v8_0_set_compute_eop_पूर्णांकerrupt_state(काष्ठा amdgpu_device *adev,
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

अटल पूर्णांक gfx_v8_0_set_priv_reg_fault_state(काष्ठा amdgpu_device *adev,
					     काष्ठा amdgpu_irq_src *source,
					     अचिन्हित type,
					     क्रमागत amdgpu_पूर्णांकerrupt_state state)
अणु
	WREG32_FIELD(CP_INT_CNTL_RING0, PRIV_REG_INT_ENABLE,
		     state == AMDGPU_IRQ_STATE_DISABLE ? 0 : 1);

	वापस 0;
पूर्ण

अटल पूर्णांक gfx_v8_0_set_priv_inst_fault_state(काष्ठा amdgpu_device *adev,
					      काष्ठा amdgpu_irq_src *source,
					      अचिन्हित type,
					      क्रमागत amdgpu_पूर्णांकerrupt_state state)
अणु
	WREG32_FIELD(CP_INT_CNTL_RING0, PRIV_INSTR_INT_ENABLE,
		     state == AMDGPU_IRQ_STATE_DISABLE ? 0 : 1);

	वापस 0;
पूर्ण

अटल पूर्णांक gfx_v8_0_set_eop_पूर्णांकerrupt_state(काष्ठा amdgpu_device *adev,
					    काष्ठा amdgpu_irq_src *src,
					    अचिन्हित type,
					    क्रमागत amdgpu_पूर्णांकerrupt_state state)
अणु
	चयन (type) अणु
	हाल AMDGPU_CP_IRQ_GFX_ME0_PIPE0_EOP:
		gfx_v8_0_set_gfx_eop_पूर्णांकerrupt_state(adev, state);
		अवरोध;
	हाल AMDGPU_CP_IRQ_COMPUTE_MEC1_PIPE0_EOP:
		gfx_v8_0_set_compute_eop_पूर्णांकerrupt_state(adev, 1, 0, state);
		अवरोध;
	हाल AMDGPU_CP_IRQ_COMPUTE_MEC1_PIPE1_EOP:
		gfx_v8_0_set_compute_eop_पूर्णांकerrupt_state(adev, 1, 1, state);
		अवरोध;
	हाल AMDGPU_CP_IRQ_COMPUTE_MEC1_PIPE2_EOP:
		gfx_v8_0_set_compute_eop_पूर्णांकerrupt_state(adev, 1, 2, state);
		अवरोध;
	हाल AMDGPU_CP_IRQ_COMPUTE_MEC1_PIPE3_EOP:
		gfx_v8_0_set_compute_eop_पूर्णांकerrupt_state(adev, 1, 3, state);
		अवरोध;
	हाल AMDGPU_CP_IRQ_COMPUTE_MEC2_PIPE0_EOP:
		gfx_v8_0_set_compute_eop_पूर्णांकerrupt_state(adev, 2, 0, state);
		अवरोध;
	हाल AMDGPU_CP_IRQ_COMPUTE_MEC2_PIPE1_EOP:
		gfx_v8_0_set_compute_eop_पूर्णांकerrupt_state(adev, 2, 1, state);
		अवरोध;
	हाल AMDGPU_CP_IRQ_COMPUTE_MEC2_PIPE2_EOP:
		gfx_v8_0_set_compute_eop_पूर्णांकerrupt_state(adev, 2, 2, state);
		अवरोध;
	हाल AMDGPU_CP_IRQ_COMPUTE_MEC2_PIPE3_EOP:
		gfx_v8_0_set_compute_eop_पूर्णांकerrupt_state(adev, 2, 3, state);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक gfx_v8_0_set_cp_ecc_पूर्णांक_state(काष्ठा amdgpu_device *adev,
					 काष्ठा amdgpu_irq_src *source,
					 अचिन्हित पूर्णांक type,
					 क्रमागत amdgpu_पूर्णांकerrupt_state state)
अणु
	पूर्णांक enable_flag;

	चयन (state) अणु
	हाल AMDGPU_IRQ_STATE_DISABLE:
		enable_flag = 0;
		अवरोध;

	हाल AMDGPU_IRQ_STATE_ENABLE:
		enable_flag = 1;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	WREG32_FIELD(CP_INT_CNTL, CP_ECC_ERROR_INT_ENABLE, enable_flag);
	WREG32_FIELD(CP_INT_CNTL_RING0, CP_ECC_ERROR_INT_ENABLE, enable_flag);
	WREG32_FIELD(CP_INT_CNTL_RING1, CP_ECC_ERROR_INT_ENABLE, enable_flag);
	WREG32_FIELD(CP_INT_CNTL_RING2, CP_ECC_ERROR_INT_ENABLE, enable_flag);
	WREG32_FIELD(CPC_INT_CNTL, CP_ECC_ERROR_INT_ENABLE, enable_flag);
	WREG32_FIELD(CP_ME1_PIPE0_INT_CNTL, CP_ECC_ERROR_INT_ENABLE,
		     enable_flag);
	WREG32_FIELD(CP_ME1_PIPE1_INT_CNTL, CP_ECC_ERROR_INT_ENABLE,
		     enable_flag);
	WREG32_FIELD(CP_ME1_PIPE2_INT_CNTL, CP_ECC_ERROR_INT_ENABLE,
		     enable_flag);
	WREG32_FIELD(CP_ME1_PIPE3_INT_CNTL, CP_ECC_ERROR_INT_ENABLE,
		     enable_flag);
	WREG32_FIELD(CP_ME2_PIPE0_INT_CNTL, CP_ECC_ERROR_INT_ENABLE,
		     enable_flag);
	WREG32_FIELD(CP_ME2_PIPE1_INT_CNTL, CP_ECC_ERROR_INT_ENABLE,
		     enable_flag);
	WREG32_FIELD(CP_ME2_PIPE2_INT_CNTL, CP_ECC_ERROR_INT_ENABLE,
		     enable_flag);
	WREG32_FIELD(CP_ME2_PIPE3_INT_CNTL, CP_ECC_ERROR_INT_ENABLE,
		     enable_flag);

	वापस 0;
पूर्ण

अटल पूर्णांक gfx_v8_0_set_sq_पूर्णांक_state(काष्ठा amdgpu_device *adev,
				     काष्ठा amdgpu_irq_src *source,
				     अचिन्हित पूर्णांक type,
				     क्रमागत amdgpu_पूर्णांकerrupt_state state)
अणु
	पूर्णांक enable_flag;

	चयन (state) अणु
	हाल AMDGPU_IRQ_STATE_DISABLE:
		enable_flag = 1;
		अवरोध;

	हाल AMDGPU_IRQ_STATE_ENABLE:
		enable_flag = 0;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	WREG32_FIELD(SQ_INTERRUPT_MSG_CTRL, STALL,
		     enable_flag);

	वापस 0;
पूर्ण

अटल पूर्णांक gfx_v8_0_eop_irq(काष्ठा amdgpu_device *adev,
			    काष्ठा amdgpu_irq_src *source,
			    काष्ठा amdgpu_iv_entry *entry)
अणु
	पूर्णांक i;
	u8 me_id, pipe_id, queue_id;
	काष्ठा amdgpu_ring *ring;

	DRM_DEBUG("IH: CP EOP\n");
	me_id = (entry->ring_id & 0x0c) >> 2;
	pipe_id = (entry->ring_id & 0x03) >> 0;
	queue_id = (entry->ring_id & 0x70) >> 4;

	चयन (me_id) अणु
	हाल 0:
		amdgpu_fence_process(&adev->gfx.gfx_ring[0]);
		अवरोध;
	हाल 1:
	हाल 2:
		क्रम (i = 0; i < adev->gfx.num_compute_rings; i++) अणु
			ring = &adev->gfx.compute_ring[i];
			/* Per-queue पूर्णांकerrupt is supported क्रम MEC starting from VI.
			  * The पूर्णांकerrupt can only be enabled/disabled per pipe instead of per queue.
			  */
			अगर ((ring->me == me_id) && (ring->pipe == pipe_id) && (ring->queue == queue_id))
				amdgpu_fence_process(ring);
		पूर्ण
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम gfx_v8_0_fault(काष्ठा amdgpu_device *adev,
			   काष्ठा amdgpu_iv_entry *entry)
अणु
	u8 me_id, pipe_id, queue_id;
	काष्ठा amdgpu_ring *ring;
	पूर्णांक i;

	me_id = (entry->ring_id & 0x0c) >> 2;
	pipe_id = (entry->ring_id & 0x03) >> 0;
	queue_id = (entry->ring_id & 0x70) >> 4;

	चयन (me_id) अणु
	हाल 0:
		drm_sched_fault(&adev->gfx.gfx_ring[0].sched);
		अवरोध;
	हाल 1:
	हाल 2:
		क्रम (i = 0; i < adev->gfx.num_compute_rings; i++) अणु
			ring = &adev->gfx.compute_ring[i];
			अगर (ring->me == me_id && ring->pipe == pipe_id &&
			    ring->queue == queue_id)
				drm_sched_fault(&ring->sched);
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक gfx_v8_0_priv_reg_irq(काष्ठा amdgpu_device *adev,
				 काष्ठा amdgpu_irq_src *source,
				 काष्ठा amdgpu_iv_entry *entry)
अणु
	DRM_ERROR("Illegal register access in command stream\n");
	gfx_v8_0_fault(adev, entry);
	वापस 0;
पूर्ण

अटल पूर्णांक gfx_v8_0_priv_inst_irq(काष्ठा amdgpu_device *adev,
				  काष्ठा amdgpu_irq_src *source,
				  काष्ठा amdgpu_iv_entry *entry)
अणु
	DRM_ERROR("Illegal instruction in command stream\n");
	gfx_v8_0_fault(adev, entry);
	वापस 0;
पूर्ण

अटल पूर्णांक gfx_v8_0_cp_ecc_error_irq(काष्ठा amdgpu_device *adev,
				     काष्ठा amdgpu_irq_src *source,
				     काष्ठा amdgpu_iv_entry *entry)
अणु
	DRM_ERROR("CP EDC/ECC error detected.");
	वापस 0;
पूर्ण

अटल व्योम gfx_v8_0_parse_sq_irq(काष्ठा amdgpu_device *adev, अचिन्हित ih_data,
				  bool from_wq)
अणु
	u32 enc, se_id, sh_id, cu_id;
	अक्षर type[20];
	पूर्णांक sq_edc_source = -1;

	enc = REG_GET_FIELD(ih_data, SQ_INTERRUPT_WORD_CMN, ENCODING);
	se_id = REG_GET_FIELD(ih_data, SQ_INTERRUPT_WORD_CMN, SE_ID);

	चयन (enc) अणु
		हाल 0:
			DRM_INFO("SQ general purpose intr detected:"
					"se_id %d, immed_overflow %d, host_reg_overflow %d,"
					"host_cmd_overflow %d, cmd_timestamp %d,"
					"reg_timestamp %d, thread_trace_buff_full %d,"
					"wlt %d, thread_trace %d.\n",
					se_id,
					REG_GET_FIELD(ih_data, SQ_INTERRUPT_WORD_AUTO, IMMED_OVERFLOW),
					REG_GET_FIELD(ih_data, SQ_INTERRUPT_WORD_AUTO, HOST_REG_OVERFLOW),
					REG_GET_FIELD(ih_data, SQ_INTERRUPT_WORD_AUTO, HOST_CMD_OVERFLOW),
					REG_GET_FIELD(ih_data, SQ_INTERRUPT_WORD_AUTO, CMD_TIMESTAMP),
					REG_GET_FIELD(ih_data, SQ_INTERRUPT_WORD_AUTO, REG_TIMESTAMP),
					REG_GET_FIELD(ih_data, SQ_INTERRUPT_WORD_AUTO, THREAD_TRACE_BUF_FULL),
					REG_GET_FIELD(ih_data, SQ_INTERRUPT_WORD_AUTO, WLT),
					REG_GET_FIELD(ih_data, SQ_INTERRUPT_WORD_AUTO, THREAD_TRACE)
					);
			अवरोध;
		हाल 1:
		हाल 2:

			cu_id = REG_GET_FIELD(ih_data, SQ_INTERRUPT_WORD_WAVE, CU_ID);
			sh_id = REG_GET_FIELD(ih_data, SQ_INTERRUPT_WORD_WAVE, SH_ID);

			/*
			 * This function can be called either directly from ISR
			 * or from BH in which हाल we can access SQ_EDC_INFO
			 * instance
			 */
			अगर (from_wq) अणु
				mutex_lock(&adev->grbm_idx_mutex);
				gfx_v8_0_select_se_sh(adev, se_id, sh_id, cu_id);

				sq_edc_source = REG_GET_FIELD(RREG32(mmSQ_EDC_INFO), SQ_EDC_INFO, SOURCE);

				gfx_v8_0_select_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff);
				mutex_unlock(&adev->grbm_idx_mutex);
			पूर्ण

			अगर (enc == 1)
				प्र_लिखो(type, "instruction intr");
			अन्यथा
				प्र_लिखो(type, "EDC/ECC error");

			DRM_INFO(
				"SQ %s detected: "
					"se_id %d, sh_id %d, cu_id %d, simd_id %d, wave_id %d, vm_id %d "
					"trap %s, sq_ed_info.source %s.\n",
					type, se_id, sh_id, cu_id,
					REG_GET_FIELD(ih_data, SQ_INTERRUPT_WORD_WAVE, SIMD_ID),
					REG_GET_FIELD(ih_data, SQ_INTERRUPT_WORD_WAVE, WAVE_ID),
					REG_GET_FIELD(ih_data, SQ_INTERRUPT_WORD_WAVE, VM_ID),
					REG_GET_FIELD(ih_data, SQ_INTERRUPT_WORD_WAVE, PRIV) ? "true" : "false",
					(sq_edc_source != -1) ? sq_edc_source_names[sq_edc_source] : "unavailable"
				);
			अवरोध;
		शेष:
			DRM_ERROR("SQ invalid encoding type\n.");
	पूर्ण
पूर्ण

अटल व्योम gfx_v8_0_sq_irq_work_func(काष्ठा work_काष्ठा *work)
अणु

	काष्ठा amdgpu_device *adev = container_of(work, काष्ठा amdgpu_device, gfx.sq_work.work);
	काष्ठा sq_work *sq_work = container_of(work, काष्ठा sq_work, work);

	gfx_v8_0_parse_sq_irq(adev, sq_work->ih_data, true);
पूर्ण

अटल पूर्णांक gfx_v8_0_sq_irq(काष्ठा amdgpu_device *adev,
			   काष्ठा amdgpu_irq_src *source,
			   काष्ठा amdgpu_iv_entry *entry)
अणु
	अचिन्हित ih_data = entry->src_data[0];

	/*
	 * Try to submit work so SQ_EDC_INFO can be accessed from
	 * BH. If previous work submission hasn't finished yet
	 * just prपूर्णांक whatever info is possible directly from the ISR.
	 */
	अगर (work_pending(&adev->gfx.sq_work.work)) अणु
		gfx_v8_0_parse_sq_irq(adev, ih_data, false);
	पूर्ण अन्यथा अणु
		adev->gfx.sq_work.ih_data = ih_data;
		schedule_work(&adev->gfx.sq_work.work);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम gfx_v8_0_emit_mem_sync(काष्ठा amdgpu_ring *ring)
अणु
	amdgpu_ring_ग_लिखो(ring, PACKET3(PACKET3_SURFACE_SYNC, 3));
	amdgpu_ring_ग_लिखो(ring, PACKET3_TCL1_ACTION_ENA |
			  PACKET3_TC_ACTION_ENA |
			  PACKET3_SH_KCACHE_ACTION_ENA |
			  PACKET3_SH_ICACHE_ACTION_ENA |
			  PACKET3_TC_WB_ACTION_ENA);  /* CP_COHER_CNTL */
	amdgpu_ring_ग_लिखो(ring, 0xffffffff);  /* CP_COHER_SIZE */
	amdgpu_ring_ग_लिखो(ring, 0);  /* CP_COHER_BASE */
	amdgpu_ring_ग_लिखो(ring, 0x0000000A); /* poll पूर्णांकerval */
पूर्ण

अटल व्योम gfx_v8_0_emit_mem_sync_compute(काष्ठा amdgpu_ring *ring)
अणु
	amdgpu_ring_ग_लिखो(ring, PACKET3(PACKET3_ACQUIRE_MEM, 5));
	amdgpu_ring_ग_लिखो(ring, PACKET3_TCL1_ACTION_ENA |
			  PACKET3_TC_ACTION_ENA |
			  PACKET3_SH_KCACHE_ACTION_ENA |
			  PACKET3_SH_ICACHE_ACTION_ENA |
			  PACKET3_TC_WB_ACTION_ENA);  /* CP_COHER_CNTL */
	amdgpu_ring_ग_लिखो(ring, 0xffffffff);	/* CP_COHER_SIZE */
	amdgpu_ring_ग_लिखो(ring, 0xff);		/* CP_COHER_SIZE_HI */
	amdgpu_ring_ग_लिखो(ring, 0);		/* CP_COHER_BASE */
	amdgpu_ring_ग_लिखो(ring, 0);		/* CP_COHER_BASE_HI */
	amdgpu_ring_ग_लिखो(ring, 0x0000000A);	/* poll पूर्णांकerval */
पूर्ण


/* mmSPI_WCL_PIPE_PERCENT_CS[0-7]_DEFAULT values are same */
#घोषणा mmSPI_WCL_PIPE_PERCENT_CS_DEFAULT	0x0000007f
अटल व्योम gfx_v8_0_emit_wave_limit_cs(काष्ठा amdgpu_ring *ring,
					uपूर्णांक32_t pipe, bool enable)
अणु
	uपूर्णांक32_t val;
	uपूर्णांक32_t wcl_cs_reg;

	val = enable ? 0x1 : mmSPI_WCL_PIPE_PERCENT_CS_DEFAULT;

	चयन (pipe) अणु
	हाल 0:
		wcl_cs_reg = mmSPI_WCL_PIPE_PERCENT_CS0;
		अवरोध;
	हाल 1:
		wcl_cs_reg = mmSPI_WCL_PIPE_PERCENT_CS1;
		अवरोध;
	हाल 2:
		wcl_cs_reg = mmSPI_WCL_PIPE_PERCENT_CS2;
		अवरोध;
	हाल 3:
		wcl_cs_reg = mmSPI_WCL_PIPE_PERCENT_CS3;
		अवरोध;
	शेष:
		DRM_DEBUG("invalid pipe %d\n", pipe);
		वापस;
	पूर्ण

	amdgpu_ring_emit_wreg(ring, wcl_cs_reg, val);

पूर्ण

#घोषणा mmSPI_WCL_PIPE_PERCENT_GFX_DEFAULT	0x07ffffff
अटल व्योम gfx_v8_0_emit_wave_limit(काष्ठा amdgpu_ring *ring, bool enable)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	uपूर्णांक32_t val;
	पूर्णांक i;

	/* mmSPI_WCL_PIPE_PERCENT_GFX is 7 bit multiplier रेजिस्टर to limit
	 * number of gfx waves. Setting 5 bit will make sure gfx only माला_लो
	 * around 25% of gpu resources.
	 */
	val = enable ? 0x1f : mmSPI_WCL_PIPE_PERCENT_GFX_DEFAULT;
	amdgpu_ring_emit_wreg(ring, mmSPI_WCL_PIPE_PERCENT_GFX, val);

	/* Restrict waves क्रम normal/low priority compute queues as well
	 * to get best QoS क्रम high priority compute jobs.
	 *
	 * amdgpu controls only 1st ME(0-3 CS pipes).
	 */
	क्रम (i = 0; i < adev->gfx.mec.num_pipe_per_mec; i++) अणु
		अगर (i != ring->pipe)
			gfx_v8_0_emit_wave_limit_cs(ring, i, enable);

	पूर्ण

पूर्ण

अटल स्थिर काष्ठा amd_ip_funcs gfx_v8_0_ip_funcs = अणु
	.name = "gfx_v8_0",
	.early_init = gfx_v8_0_early_init,
	.late_init = gfx_v8_0_late_init,
	.sw_init = gfx_v8_0_sw_init,
	.sw_fini = gfx_v8_0_sw_fini,
	.hw_init = gfx_v8_0_hw_init,
	.hw_fini = gfx_v8_0_hw_fini,
	.suspend = gfx_v8_0_suspend,
	.resume = gfx_v8_0_resume,
	.is_idle = gfx_v8_0_is_idle,
	.रुको_क्रम_idle = gfx_v8_0_रुको_क्रम_idle,
	.check_soft_reset = gfx_v8_0_check_soft_reset,
	.pre_soft_reset = gfx_v8_0_pre_soft_reset,
	.soft_reset = gfx_v8_0_soft_reset,
	.post_soft_reset = gfx_v8_0_post_soft_reset,
	.set_घड़ीgating_state = gfx_v8_0_set_घड़ीgating_state,
	.set_घातergating_state = gfx_v8_0_set_घातergating_state,
	.get_घड़ीgating_state = gfx_v8_0_get_घड़ीgating_state,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_ring_funcs gfx_v8_0_ring_funcs_gfx = अणु
	.type = AMDGPU_RING_TYPE_GFX,
	.align_mask = 0xff,
	.nop = PACKET3(PACKET3_NOP, 0x3FFF),
	.support_64bit_ptrs = false,
	.get_rptr = gfx_v8_0_ring_get_rptr,
	.get_wptr = gfx_v8_0_ring_get_wptr_gfx,
	.set_wptr = gfx_v8_0_ring_set_wptr_gfx,
	.emit_frame_size = /* maximum 215dw अगर count 16 IBs in */
		5 +  /* COND_EXEC */
		7 +  /* PIPELINE_SYNC */
		VI_FLUSH_GPU_TLB_NUM_WREG * 5 + 9 + /* VM_FLUSH */
		12 +  /* FENCE क्रम VM_FLUSH */
		20 + /* GDS चयन */
		4 + /* द्विगुन SWITCH_BUFFER,
		       the first COND_EXEC jump to the place just
			   prior to this द्विगुन SWITCH_BUFFER  */
		5 + /* COND_EXEC */
		7 +	 /*	HDP_flush */
		4 +	 /*	VGT_flush */
		14 + /*	CE_META */
		31 + /*	DE_META */
		3 + /* CNTX_CTRL */
		5 + /* HDP_INVL */
		12 + 12 + /* FENCE x2 */
		2 + /* SWITCH_BUFFER */
		5, /* SURFACE_SYNC */
	.emit_ib_size =	4, /* gfx_v8_0_ring_emit_ib_gfx */
	.emit_ib = gfx_v8_0_ring_emit_ib_gfx,
	.emit_fence = gfx_v8_0_ring_emit_fence_gfx,
	.emit_pipeline_sync = gfx_v8_0_ring_emit_pipeline_sync,
	.emit_vm_flush = gfx_v8_0_ring_emit_vm_flush,
	.emit_gds_चयन = gfx_v8_0_ring_emit_gds_चयन,
	.emit_hdp_flush = gfx_v8_0_ring_emit_hdp_flush,
	.test_ring = gfx_v8_0_ring_test_ring,
	.test_ib = gfx_v8_0_ring_test_ib,
	.insert_nop = amdgpu_ring_insert_nop,
	.pad_ib = amdgpu_ring_generic_pad_ib,
	.emit_चयन_buffer = gfx_v8_ring_emit_sb,
	.emit_cntxcntl = gfx_v8_ring_emit_cntxcntl,
	.init_cond_exec = gfx_v8_0_ring_emit_init_cond_exec,
	.patch_cond_exec = gfx_v8_0_ring_emit_patch_cond_exec,
	.emit_wreg = gfx_v8_0_ring_emit_wreg,
	.soft_recovery = gfx_v8_0_ring_soft_recovery,
	.emit_mem_sync = gfx_v8_0_emit_mem_sync,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_ring_funcs gfx_v8_0_ring_funcs_compute = अणु
	.type = AMDGPU_RING_TYPE_COMPUTE,
	.align_mask = 0xff,
	.nop = PACKET3(PACKET3_NOP, 0x3FFF),
	.support_64bit_ptrs = false,
	.get_rptr = gfx_v8_0_ring_get_rptr,
	.get_wptr = gfx_v8_0_ring_get_wptr_compute,
	.set_wptr = gfx_v8_0_ring_set_wptr_compute,
	.emit_frame_size =
		20 + /* gfx_v8_0_ring_emit_gds_चयन */
		7 + /* gfx_v8_0_ring_emit_hdp_flush */
		5 + /* hdp_invalidate */
		7 + /* gfx_v8_0_ring_emit_pipeline_sync */
		VI_FLUSH_GPU_TLB_NUM_WREG * 5 + 7 + /* gfx_v8_0_ring_emit_vm_flush */
		7 + 7 + 7 + /* gfx_v8_0_ring_emit_fence_compute x3 क्रम user fence, vm fence */
		7 + /* gfx_v8_0_emit_mem_sync_compute */
		5 + /* gfx_v8_0_emit_wave_limit क्रम updating mmSPI_WCL_PIPE_PERCENT_GFX रेजिस्टर */
		15, /* क्रम updating 3 mmSPI_WCL_PIPE_PERCENT_CS रेजिस्टरs */
	.emit_ib_size =	7, /* gfx_v8_0_ring_emit_ib_compute */
	.emit_ib = gfx_v8_0_ring_emit_ib_compute,
	.emit_fence = gfx_v8_0_ring_emit_fence_compute,
	.emit_pipeline_sync = gfx_v8_0_ring_emit_pipeline_sync,
	.emit_vm_flush = gfx_v8_0_ring_emit_vm_flush,
	.emit_gds_चयन = gfx_v8_0_ring_emit_gds_चयन,
	.emit_hdp_flush = gfx_v8_0_ring_emit_hdp_flush,
	.test_ring = gfx_v8_0_ring_test_ring,
	.test_ib = gfx_v8_0_ring_test_ib,
	.insert_nop = amdgpu_ring_insert_nop,
	.pad_ib = amdgpu_ring_generic_pad_ib,
	.emit_wreg = gfx_v8_0_ring_emit_wreg,
	.emit_mem_sync = gfx_v8_0_emit_mem_sync_compute,
	.emit_wave_limit = gfx_v8_0_emit_wave_limit,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_ring_funcs gfx_v8_0_ring_funcs_kiq = अणु
	.type = AMDGPU_RING_TYPE_KIQ,
	.align_mask = 0xff,
	.nop = PACKET3(PACKET3_NOP, 0x3FFF),
	.support_64bit_ptrs = false,
	.get_rptr = gfx_v8_0_ring_get_rptr,
	.get_wptr = gfx_v8_0_ring_get_wptr_compute,
	.set_wptr = gfx_v8_0_ring_set_wptr_compute,
	.emit_frame_size =
		20 + /* gfx_v8_0_ring_emit_gds_चयन */
		7 + /* gfx_v8_0_ring_emit_hdp_flush */
		5 + /* hdp_invalidate */
		7 + /* gfx_v8_0_ring_emit_pipeline_sync */
		17 + /* gfx_v8_0_ring_emit_vm_flush */
		7 + 7 + 7, /* gfx_v8_0_ring_emit_fence_kiq x3 क्रम user fence, vm fence */
	.emit_ib_size =	7, /* gfx_v8_0_ring_emit_ib_compute */
	.emit_fence = gfx_v8_0_ring_emit_fence_kiq,
	.test_ring = gfx_v8_0_ring_test_ring,
	.insert_nop = amdgpu_ring_insert_nop,
	.pad_ib = amdgpu_ring_generic_pad_ib,
	.emit_rreg = gfx_v8_0_ring_emit_rreg,
	.emit_wreg = gfx_v8_0_ring_emit_wreg,
पूर्ण;

अटल व्योम gfx_v8_0_set_ring_funcs(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i;

	adev->gfx.kiq.ring.funcs = &gfx_v8_0_ring_funcs_kiq;

	क्रम (i = 0; i < adev->gfx.num_gfx_rings; i++)
		adev->gfx.gfx_ring[i].funcs = &gfx_v8_0_ring_funcs_gfx;

	क्रम (i = 0; i < adev->gfx.num_compute_rings; i++)
		adev->gfx.compute_ring[i].funcs = &gfx_v8_0_ring_funcs_compute;
पूर्ण

अटल स्थिर काष्ठा amdgpu_irq_src_funcs gfx_v8_0_eop_irq_funcs = अणु
	.set = gfx_v8_0_set_eop_पूर्णांकerrupt_state,
	.process = gfx_v8_0_eop_irq,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_irq_src_funcs gfx_v8_0_priv_reg_irq_funcs = अणु
	.set = gfx_v8_0_set_priv_reg_fault_state,
	.process = gfx_v8_0_priv_reg_irq,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_irq_src_funcs gfx_v8_0_priv_inst_irq_funcs = अणु
	.set = gfx_v8_0_set_priv_inst_fault_state,
	.process = gfx_v8_0_priv_inst_irq,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_irq_src_funcs gfx_v8_0_cp_ecc_error_irq_funcs = अणु
	.set = gfx_v8_0_set_cp_ecc_पूर्णांक_state,
	.process = gfx_v8_0_cp_ecc_error_irq,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_irq_src_funcs gfx_v8_0_sq_irq_funcs = अणु
	.set = gfx_v8_0_set_sq_पूर्णांक_state,
	.process = gfx_v8_0_sq_irq,
पूर्ण;

अटल व्योम gfx_v8_0_set_irq_funcs(काष्ठा amdgpu_device *adev)
अणु
	adev->gfx.eop_irq.num_types = AMDGPU_CP_IRQ_LAST;
	adev->gfx.eop_irq.funcs = &gfx_v8_0_eop_irq_funcs;

	adev->gfx.priv_reg_irq.num_types = 1;
	adev->gfx.priv_reg_irq.funcs = &gfx_v8_0_priv_reg_irq_funcs;

	adev->gfx.priv_inst_irq.num_types = 1;
	adev->gfx.priv_inst_irq.funcs = &gfx_v8_0_priv_inst_irq_funcs;

	adev->gfx.cp_ecc_error_irq.num_types = 1;
	adev->gfx.cp_ecc_error_irq.funcs = &gfx_v8_0_cp_ecc_error_irq_funcs;

	adev->gfx.sq_irq.num_types = 1;
	adev->gfx.sq_irq.funcs = &gfx_v8_0_sq_irq_funcs;
पूर्ण

अटल व्योम gfx_v8_0_set_rlc_funcs(काष्ठा amdgpu_device *adev)
अणु
	adev->gfx.rlc.funcs = &iceland_rlc_funcs;
पूर्ण

अटल व्योम gfx_v8_0_set_gds_init(काष्ठा amdgpu_device *adev)
अणु
	/* init asci gds info */
	adev->gds.gds_size = RREG32(mmGDS_VMID0_SIZE);
	adev->gds.gws_size = 64;
	adev->gds.oa_size = 16;
	adev->gds.gds_compute_max_wave_id = RREG32(mmGDS_COMPUTE_MAX_WAVE_ID);
पूर्ण

अटल व्योम gfx_v8_0_set_user_cu_inactive_biपंचांगap(काष्ठा amdgpu_device *adev,
						 u32 biपंचांगap)
अणु
	u32 data;

	अगर (!biपंचांगap)
		वापस;

	data = biपंचांगap << GC_USER_SHADER_ARRAY_CONFIG__INACTIVE_CUS__SHIFT;
	data &= GC_USER_SHADER_ARRAY_CONFIG__INACTIVE_CUS_MASK;

	WREG32(mmGC_USER_SHADER_ARRAY_CONFIG, data);
पूर्ण

अटल u32 gfx_v8_0_get_cu_active_biपंचांगap(काष्ठा amdgpu_device *adev)
अणु
	u32 data, mask;

	data =  RREG32(mmCC_GC_SHADER_ARRAY_CONFIG) |
		RREG32(mmGC_USER_SHADER_ARRAY_CONFIG);

	mask = amdgpu_gfx_create_biपंचांगask(adev->gfx.config.max_cu_per_sh);

	वापस ~REG_GET_FIELD(data, CC_GC_SHADER_ARRAY_CONFIG, INACTIVE_CUS) & mask;
पूर्ण

अटल व्योम gfx_v8_0_get_cu_info(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i, j, k, counter, active_cu_number = 0;
	u32 mask, biपंचांगap, ao_biपंचांगap, ao_cu_mask = 0;
	काष्ठा amdgpu_cu_info *cu_info = &adev->gfx.cu_info;
	अचिन्हित disable_masks[4 * 2];
	u32 ao_cu_num;

	स_रखो(cu_info, 0, माप(*cu_info));

	अगर (adev->flags & AMD_IS_APU)
		ao_cu_num = 2;
	अन्यथा
		ao_cu_num = adev->gfx.config.max_cu_per_sh;

	amdgpu_gfx_parse_disable_cu(disable_masks, 4, 2);

	mutex_lock(&adev->grbm_idx_mutex);
	क्रम (i = 0; i < adev->gfx.config.max_shader_engines; i++) अणु
		क्रम (j = 0; j < adev->gfx.config.max_sh_per_se; j++) अणु
			mask = 1;
			ao_biपंचांगap = 0;
			counter = 0;
			gfx_v8_0_select_se_sh(adev, i, j, 0xffffffff);
			अगर (i < 4 && j < 2)
				gfx_v8_0_set_user_cu_inactive_biपंचांगap(
					adev, disable_masks[i * 2 + j]);
			biपंचांगap = gfx_v8_0_get_cu_active_biपंचांगap(adev);
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
	gfx_v8_0_select_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff);
	mutex_unlock(&adev->grbm_idx_mutex);

	cu_info->number = active_cu_number;
	cu_info->ao_cu_mask = ao_cu_mask;
	cu_info->simd_per_cu = NUM_SIMD_PER_CU;
	cu_info->max_waves_per_simd = 10;
	cu_info->max_scratch_slots_per_cu = 32;
	cu_info->wave_front_size = 64;
	cu_info->lds_size = 64;
पूर्ण

स्थिर काष्ठा amdgpu_ip_block_version gfx_v8_0_ip_block =
अणु
	.type = AMD_IP_BLOCK_TYPE_GFX,
	.major = 8,
	.minor = 0,
	.rev = 0,
	.funcs = &gfx_v8_0_ip_funcs,
पूर्ण;

स्थिर काष्ठा amdgpu_ip_block_version gfx_v8_1_ip_block =
अणु
	.type = AMD_IP_BLOCK_TYPE_GFX,
	.major = 8,
	.minor = 1,
	.rev = 0,
	.funcs = &gfx_v8_0_ip_funcs,
पूर्ण;

अटल व्योम gfx_v8_0_ring_emit_ce_meta(काष्ठा amdgpu_ring *ring)
अणु
	uपूर्णांक64_t ce_payload_addr;
	पूर्णांक cnt_ce;
	जोड़ अणु
		काष्ठा vi_ce_ib_state regular;
		काष्ठा vi_ce_ib_state_chained_ib chained;
	पूर्ण ce_payload = अणुपूर्ण;

	अगर (ring->adev->virt.chained_ib_support) अणु
		ce_payload_addr = amdgpu_csa_vaddr(ring->adev) +
			दुरत्व(काष्ठा vi_gfx_meta_data_chained_ib, ce_payload);
		cnt_ce = (माप(ce_payload.chained) >> 2) + 4 - 2;
	पूर्ण अन्यथा अणु
		ce_payload_addr = amdgpu_csa_vaddr(ring->adev) +
			दुरत्व(काष्ठा vi_gfx_meta_data, ce_payload);
		cnt_ce = (माप(ce_payload.regular) >> 2) + 4 - 2;
	पूर्ण

	amdgpu_ring_ग_लिखो(ring, PACKET3(PACKET3_WRITE_DATA, cnt_ce));
	amdgpu_ring_ग_लिखो(ring, (WRITE_DATA_ENGINE_SEL(2) |
				WRITE_DATA_DST_SEL(8) |
				WR_CONFIRM) |
				WRITE_DATA_CACHE_POLICY(0));
	amdgpu_ring_ग_लिखो(ring, lower_32_bits(ce_payload_addr));
	amdgpu_ring_ग_लिखो(ring, upper_32_bits(ce_payload_addr));
	amdgpu_ring_ग_लिखो_multiple(ring, (व्योम *)&ce_payload, cnt_ce - 2);
पूर्ण

अटल व्योम gfx_v8_0_ring_emit_de_meta(काष्ठा amdgpu_ring *ring)
अणु
	uपूर्णांक64_t de_payload_addr, gds_addr, csa_addr;
	पूर्णांक cnt_de;
	जोड़ अणु
		काष्ठा vi_de_ib_state regular;
		काष्ठा vi_de_ib_state_chained_ib chained;
	पूर्ण de_payload = अणुपूर्ण;

	csa_addr = amdgpu_csa_vaddr(ring->adev);
	gds_addr = csa_addr + 4096;
	अगर (ring->adev->virt.chained_ib_support) अणु
		de_payload.chained.gds_backup_addrlo = lower_32_bits(gds_addr);
		de_payload.chained.gds_backup_addrhi = upper_32_bits(gds_addr);
		de_payload_addr = csa_addr + दुरत्व(काष्ठा vi_gfx_meta_data_chained_ib, de_payload);
		cnt_de = (माप(de_payload.chained) >> 2) + 4 - 2;
	पूर्ण अन्यथा अणु
		de_payload.regular.gds_backup_addrlo = lower_32_bits(gds_addr);
		de_payload.regular.gds_backup_addrhi = upper_32_bits(gds_addr);
		de_payload_addr = csa_addr + दुरत्व(काष्ठा vi_gfx_meta_data, de_payload);
		cnt_de = (माप(de_payload.regular) >> 2) + 4 - 2;
	पूर्ण

	amdgpu_ring_ग_लिखो(ring, PACKET3(PACKET3_WRITE_DATA, cnt_de));
	amdgpu_ring_ग_लिखो(ring, (WRITE_DATA_ENGINE_SEL(1) |
				WRITE_DATA_DST_SEL(8) |
				WR_CONFIRM) |
				WRITE_DATA_CACHE_POLICY(0));
	amdgpu_ring_ग_लिखो(ring, lower_32_bits(de_payload_addr));
	amdgpu_ring_ग_लिखो(ring, upper_32_bits(de_payload_addr));
	amdgpu_ring_ग_लिखो_multiple(ring, (व्योम *)&de_payload, cnt_de - 2);
पूर्ण
