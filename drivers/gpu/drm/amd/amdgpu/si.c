<शैली गुरु>
/*
 * Copyright 2015 Advanced Micro Devices, Inc.
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
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>

#समावेश <drm/amdgpu_drm.h>

#समावेश "amdgpu.h"
#समावेश "amdgpu_atombios.h"
#समावेश "amdgpu_ih.h"
#समावेश "amdgpu_uvd.h"
#समावेश "amdgpu_vce.h"
#समावेश "atom.h"
#समावेश "amd_pcie.h"
#समावेश "si_dpm.h"
#समावेश "sid.h"
#समावेश "si_ih.h"
#समावेश "gfx_v6_0.h"
#समावेश "gmc_v6_0.h"
#समावेश "si_dma.h"
#समावेश "dce_v6_0.h"
#समावेश "si.h"
#समावेश "uvd_v3_1.h"
#समावेश "dce_virtual.h"
#समावेश "gca/gfx_6_0_d.h"
#समावेश "oss/oss_1_0_d.h"
#समावेश "oss/oss_1_0_sh_mask.h"
#समावेश "gmc/gmc_6_0_d.h"
#समावेश "dce/dce_6_0_d.h"
#समावेश "uvd/uvd_4_0_d.h"
#समावेश "bif/bif_3_0_d.h"
#समावेश "bif/bif_3_0_sh_mask.h"

#समावेश "amdgpu_dm.h"

अटल स्थिर u32 tahiti_golden_रेजिस्टरs[] =
अणु
	mmAZALIA_SCLK_CONTROL, 0x00000030, 0x00000011,
	mmCB_HW_CONTROL, 0x00010000, 0x00018208,
	mmDB_DEBUG, 0xffffffff, 0x00000000,
	mmDB_DEBUG2, 0xf00fffff, 0x00000400,
	mmDB_DEBUG3, 0x0002021c, 0x00020200,
	mmDCI_CLK_CNTL, 0x00000080, 0x00000000,
	0x340c, 0x000000c0, 0x00800040,
	0x360c, 0x000000c0, 0x00800040,
	mmFBC_DEBUG_COMP, 0x000000f0, 0x00000070,
	mmFBC_MISC, 0x00200000, 0x50100000,
	mmDIG0_HDMI_CONTROL, 0x31000311, 0x00000011,
	mmMC_ARB_WTM_CNTL_RD, 0x00000003, 0x000007ff,
	mmMC_XPB_P2P_BAR_CFG, 0x000007ff, 0x00000000,
	mmPA_CL_ENHANCE, 0xf000001f, 0x00000007,
	mmPA_SC_FORCE_EOV_MAX_CNTS, 0xffffffff, 0x00ffffff,
	mmPA_SC_LINE_STIPPLE_STATE, 0x0000ff0f, 0x00000000,
	mmPA_SC_MODE_CNTL_1, 0x07ffffff, 0x4e000000,
	mmPA_SC_RASTER_CONFIG, 0x3f3f3fff, 0x2a00126a,
	0x000c, 0xffffffff, 0x0040,
	0x000d, 0x00000040, 0x00004040,
	mmSPI_CONFIG_CNTL, 0x07ffffff, 0x03000000,
	mmSQ_DED_CNT, 0x01ff1f3f, 0x00000000,
	mmSQ_SEC_CNT, 0x01ff1f3f, 0x00000000,
	mmSX_DEBUG_1, 0x0000007f, 0x00000020,
	mmTA_CNTL_AUX, 0x00010000, 0x00010000,
	mmTCP_ADDR_CONFIG, 0x00000200, 0x000002fb,
	mmTCP_CHAN_STEER_HI, 0xffffffff, 0x0000543b,
	mmTCP_CHAN_STEER_LO, 0xffffffff, 0xa9210876,
	mmVGT_FIFO_DEPTHS, 0xffffffff, 0x000fff40,
	mmVGT_GS_VERTEX_REUSE, 0x0000001f, 0x00000010,
	mmVM_CONTEXT0_CNTL, 0x20000000, 0x20fffed8,
	mmVM_L2_CG, 0x000c0fc0, 0x000c0400,
	mmVM_PRT_APERTURE0_LOW_ADDR, 0x0fffffff, 0xffffffff,
	mmVM_PRT_APERTURE1_LOW_ADDR, 0x0fffffff, 0x0fffffff,
	mmVM_PRT_APERTURE2_LOW_ADDR, 0x0fffffff, 0x0fffffff,
	mmVM_PRT_APERTURE3_LOW_ADDR, 0x0fffffff, 0x0fffffff,
पूर्ण;

अटल स्थिर u32 tahiti_golden_रेजिस्टरs2[] =
अणु
	mmMCIF_MEM_CONTROL, 0x00000001, 0x00000001,
पूर्ण;

अटल स्थिर u32 tahiti_golden_rlc_रेजिस्टरs[] =
अणु
	mmGB_ADDR_CONFIG, 0xffffffff, 0x12011003,
	mmRLC_LB_PARAMS, 0xffffffff, 0x00601005,
	0x311f, 0xffffffff, 0x10104040,
	0x3122, 0xffffffff, 0x0100000a,
	mmRLC_LB_CNTR_MAX, 0xffffffff, 0x00000800,
	mmRLC_LB_CNTL, 0xffffffff, 0x800000f4,
	mmUVD_CGC_GATE, 0x00000008, 0x00000000,
पूर्ण;

अटल स्थिर u32 pitcairn_golden_रेजिस्टरs[] =
अणु
	mmAZALIA_SCLK_CONTROL, 0x00000030, 0x00000011,
	mmCB_HW_CONTROL, 0x00010000, 0x00018208,
	mmDB_DEBUG, 0xffffffff, 0x00000000,
	mmDB_DEBUG2, 0xf00fffff, 0x00000400,
	mmDB_DEBUG3, 0x0002021c, 0x00020200,
	mmDCI_CLK_CNTL, 0x00000080, 0x00000000,
	0x340c, 0x000300c0, 0x00800040,
	0x360c, 0x000300c0, 0x00800040,
	mmFBC_DEBUG_COMP, 0x000000f0, 0x00000070,
	mmFBC_MISC, 0x00200000, 0x50100000,
	mmDIG0_HDMI_CONTROL, 0x31000311, 0x00000011,
	mmMC_SEQ_PMG_PG_HWCNTL, 0x00073ffe, 0x000022a2,
	mmMC_XPB_P2P_BAR_CFG, 0x000007ff, 0x00000000,
	mmPA_CL_ENHANCE, 0xf000001f, 0x00000007,
	mmPA_SC_FORCE_EOV_MAX_CNTS, 0xffffffff, 0x00ffffff,
	mmPA_SC_LINE_STIPPLE_STATE, 0x0000ff0f, 0x00000000,
	mmPA_SC_MODE_CNTL_1, 0x07ffffff, 0x4e000000,
	mmPA_SC_RASTER_CONFIG, 0x3f3f3fff, 0x2a00126a,
	0x000c, 0xffffffff, 0x0040,
	0x000d, 0x00000040, 0x00004040,
	mmSPI_CONFIG_CNTL, 0x07ffffff, 0x03000000,
	mmSX_DEBUG_1, 0x0000007f, 0x00000020,
	mmTA_CNTL_AUX, 0x00010000, 0x00010000,
	mmTCP_ADDR_CONFIG, 0x000003ff, 0x000000f7,
	mmTCP_CHAN_STEER_HI, 0xffffffff, 0x00000000,
	mmTCP_CHAN_STEER_LO, 0xffffffff, 0x32761054,
	mmVGT_GS_VERTEX_REUSE, 0x0000001f, 0x00000010,
	mmVM_L2_CG, 0x000c0fc0, 0x000c0400,
	mmVM_PRT_APERTURE0_LOW_ADDR, 0x0fffffff, 0xffffffff,
	mmVM_PRT_APERTURE1_LOW_ADDR, 0x0fffffff, 0x0fffffff,
	mmVM_PRT_APERTURE2_LOW_ADDR, 0x0fffffff, 0x0fffffff,
	mmVM_PRT_APERTURE3_LOW_ADDR, 0x0fffffff, 0x0fffffff,
पूर्ण;

अटल स्थिर u32 pitcairn_golden_rlc_रेजिस्टरs[] =
अणु
	mmGB_ADDR_CONFIG, 0xffffffff, 0x12011003,
	mmRLC_LB_PARAMS, 0xffffffff, 0x00601004,
	0x311f, 0xffffffff, 0x10102020,
	0x3122, 0xffffffff, 0x01000020,
	mmRLC_LB_CNTR_MAX, 0xffffffff, 0x00000800,
	mmRLC_LB_CNTL, 0xffffffff, 0x800000a4,
पूर्ण;

अटल स्थिर u32 verde_pg_init[] =
अणु
	mmGMCON_PGFSM_WRITE, 0xffffffff, 0x40000,
	mmGMCON_PGFSM_CONFIG, 0xffffffff, 0x200010ff,
	mmGMCON_PGFSM_WRITE, 0xffffffff, 0x0,
	mmGMCON_PGFSM_WRITE, 0xffffffff, 0x0,
	mmGMCON_PGFSM_WRITE, 0xffffffff, 0x0,
	mmGMCON_PGFSM_WRITE, 0xffffffff, 0x0,
	mmGMCON_PGFSM_WRITE, 0xffffffff, 0x0,
	mmGMCON_PGFSM_WRITE, 0xffffffff, 0x7007,
	mmGMCON_PGFSM_CONFIG, 0xffffffff, 0x300010ff,
	mmGMCON_PGFSM_WRITE, 0xffffffff, 0x0,
	mmGMCON_PGFSM_WRITE, 0xffffffff, 0x0,
	mmGMCON_PGFSM_WRITE, 0xffffffff, 0x0,
	mmGMCON_PGFSM_WRITE, 0xffffffff, 0x0,
	mmGMCON_PGFSM_WRITE, 0xffffffff, 0x0,
	mmGMCON_PGFSM_WRITE, 0xffffffff, 0x400000,
	mmGMCON_PGFSM_CONFIG, 0xffffffff, 0x100010ff,
	mmGMCON_PGFSM_WRITE, 0xffffffff, 0x0,
	mmGMCON_PGFSM_WRITE, 0xffffffff, 0x0,
	mmGMCON_PGFSM_WRITE, 0xffffffff, 0x0,
	mmGMCON_PGFSM_WRITE, 0xffffffff, 0x0,
	mmGMCON_PGFSM_WRITE, 0xffffffff, 0x0,
	mmGMCON_PGFSM_WRITE, 0xffffffff, 0x120200,
	mmGMCON_PGFSM_CONFIG, 0xffffffff, 0x500010ff,
	mmGMCON_PGFSM_WRITE, 0xffffffff, 0x0,
	mmGMCON_PGFSM_WRITE, 0xffffffff, 0x0,
	mmGMCON_PGFSM_WRITE, 0xffffffff, 0x0,
	mmGMCON_PGFSM_WRITE, 0xffffffff, 0x0,
	mmGMCON_PGFSM_WRITE, 0xffffffff, 0x0,
	mmGMCON_PGFSM_WRITE, 0xffffffff, 0x1e1e16,
	mmGMCON_PGFSM_CONFIG, 0xffffffff, 0x600010ff,
	mmGMCON_PGFSM_WRITE, 0xffffffff, 0x0,
	mmGMCON_PGFSM_WRITE, 0xffffffff, 0x0,
	mmGMCON_PGFSM_WRITE, 0xffffffff, 0x0,
	mmGMCON_PGFSM_WRITE, 0xffffffff, 0x0,
	mmGMCON_PGFSM_WRITE, 0xffffffff, 0x0,
	mmGMCON_PGFSM_WRITE, 0xffffffff, 0x171f1e,
	mmGMCON_PGFSM_CONFIG, 0xffffffff, 0x700010ff,
	mmGMCON_PGFSM_WRITE, 0xffffffff, 0x0,
	mmGMCON_PGFSM_WRITE, 0xffffffff, 0x0,
	mmGMCON_PGFSM_WRITE, 0xffffffff, 0x0,
	mmGMCON_PGFSM_WRITE, 0xffffffff, 0x0,
	mmGMCON_PGFSM_WRITE, 0xffffffff, 0x0,
	mmGMCON_PGFSM_WRITE, 0xffffffff, 0x0,
	mmGMCON_PGFSM_CONFIG, 0xffffffff, 0x9ff,
	mmGMCON_RENG_RAM_INDEX, 0xffffffff, 0x0,
	mmGMCON_RENG_RAM_DATA, 0xffffffff, 0x10000800,
	mmGMCON_RENG_RAM_DATA, 0xffffffff, 0xf,
	mmGMCON_RENG_RAM_DATA, 0xffffffff, 0xf,
	mmGMCON_RENG_RAM_INDEX, 0xffffffff, 0x4,
	mmGMCON_RENG_RAM_DATA, 0xffffffff, 0x1000051e,
	mmGMCON_RENG_RAM_DATA, 0xffffffff, 0xffff,
	mmGMCON_RENG_RAM_DATA, 0xffffffff, 0xffff,
	mmGMCON_RENG_RAM_INDEX, 0xffffffff, 0x8,
	mmGMCON_RENG_RAM_DATA, 0xffffffff, 0x80500,
	mmGMCON_RENG_RAM_INDEX, 0xffffffff, 0x12,
	mmGMCON_RENG_RAM_DATA, 0xffffffff, 0x9050c,
	mmGMCON_RENG_RAM_INDEX, 0xffffffff, 0x1d,
	mmGMCON_RENG_RAM_DATA, 0xffffffff, 0xb052c,
	mmGMCON_RENG_RAM_INDEX, 0xffffffff, 0x2a,
	mmGMCON_RENG_RAM_DATA, 0xffffffff, 0x1053e,
	mmGMCON_RENG_RAM_INDEX, 0xffffffff, 0x2d,
	mmGMCON_RENG_RAM_DATA, 0xffffffff, 0x10546,
	mmGMCON_RENG_RAM_INDEX, 0xffffffff, 0x30,
	mmGMCON_RENG_RAM_DATA, 0xffffffff, 0xa054e,
	mmGMCON_RENG_RAM_INDEX, 0xffffffff, 0x3c,
	mmGMCON_RENG_RAM_DATA, 0xffffffff, 0x1055f,
	mmGMCON_RENG_RAM_INDEX, 0xffffffff, 0x3f,
	mmGMCON_RENG_RAM_DATA, 0xffffffff, 0x10567,
	mmGMCON_RENG_RAM_INDEX, 0xffffffff, 0x42,
	mmGMCON_RENG_RAM_DATA, 0xffffffff, 0x1056f,
	mmGMCON_RENG_RAM_INDEX, 0xffffffff, 0x45,
	mmGMCON_RENG_RAM_DATA, 0xffffffff, 0x10572,
	mmGMCON_RENG_RAM_INDEX, 0xffffffff, 0x48,
	mmGMCON_RENG_RAM_DATA, 0xffffffff, 0x20575,
	mmGMCON_RENG_RAM_INDEX, 0xffffffff, 0x4c,
	mmGMCON_RENG_RAM_DATA, 0xffffffff, 0x190801,
	mmGMCON_RENG_RAM_INDEX, 0xffffffff, 0x67,
	mmGMCON_RENG_RAM_DATA, 0xffffffff, 0x1082a,
	mmGMCON_RENG_RAM_INDEX, 0xffffffff, 0x6a,
	mmGMCON_RENG_RAM_DATA, 0xffffffff, 0x1b082d,
	mmGMCON_RENG_RAM_INDEX, 0xffffffff, 0x87,
	mmGMCON_RENG_RAM_DATA, 0xffffffff, 0x310851,
	mmGMCON_RENG_RAM_INDEX, 0xffffffff, 0xba,
	mmGMCON_RENG_RAM_DATA, 0xffffffff, 0x891,
	mmGMCON_RENG_RAM_INDEX, 0xffffffff, 0xbc,
	mmGMCON_RENG_RAM_DATA, 0xffffffff, 0x893,
	mmGMCON_RENG_RAM_INDEX, 0xffffffff, 0xbe,
	mmGMCON_RENG_RAM_DATA, 0xffffffff, 0x20895,
	mmGMCON_RENG_RAM_INDEX, 0xffffffff, 0xc2,
	mmGMCON_RENG_RAM_DATA, 0xffffffff, 0x20899,
	mmGMCON_RENG_RAM_INDEX, 0xffffffff, 0xc6,
	mmGMCON_RENG_RAM_DATA, 0xffffffff, 0x2089d,
	mmGMCON_RENG_RAM_INDEX, 0xffffffff, 0xca,
	mmGMCON_RENG_RAM_DATA, 0xffffffff, 0x8a1,
	mmGMCON_RENG_RAM_INDEX, 0xffffffff, 0xcc,
	mmGMCON_RENG_RAM_DATA, 0xffffffff, 0x8a3,
	mmGMCON_RENG_RAM_INDEX, 0xffffffff, 0xce,
	mmGMCON_RENG_RAM_DATA, 0xffffffff, 0x308a5,
	mmGMCON_RENG_RAM_INDEX, 0xffffffff, 0xd3,
	mmGMCON_RENG_RAM_DATA, 0xffffffff, 0x6d08cd,
	mmGMCON_RENG_RAM_INDEX, 0xffffffff, 0x142,
	mmGMCON_RENG_RAM_DATA, 0xffffffff, 0x2000095a,
	mmGMCON_RENG_RAM_DATA, 0xffffffff, 0x1,
	mmGMCON_RENG_RAM_INDEX, 0xffffffff, 0x144,
	mmGMCON_RENG_RAM_DATA, 0xffffffff, 0x301f095b,
	mmGMCON_RENG_RAM_INDEX, 0xffffffff, 0x165,
	mmGMCON_RENG_RAM_DATA, 0xffffffff, 0xc094d,
	mmGMCON_RENG_RAM_INDEX, 0xffffffff, 0x173,
	mmGMCON_RENG_RAM_DATA, 0xffffffff, 0xf096d,
	mmGMCON_RENG_RAM_INDEX, 0xffffffff, 0x184,
	mmGMCON_RENG_RAM_DATA, 0xffffffff, 0x15097f,
	mmGMCON_RENG_RAM_INDEX, 0xffffffff, 0x19b,
	mmGMCON_RENG_RAM_DATA, 0xffffffff, 0xc0998,
	mmGMCON_RENG_RAM_INDEX, 0xffffffff, 0x1a9,
	mmGMCON_RENG_RAM_DATA, 0xffffffff, 0x409a7,
	mmGMCON_RENG_RAM_INDEX, 0xffffffff, 0x1af,
	mmGMCON_RENG_RAM_DATA, 0xffffffff, 0xcdc,
	mmGMCON_RENG_RAM_INDEX, 0xffffffff, 0x1b1,
	mmGMCON_RENG_RAM_DATA, 0xffffffff, 0x800,
	mmGMCON_RENG_EXECUTE, 0xffffffff, 0x6c9b2000,
	mmGMCON_MISC2, 0xfc00, 0x2000,
	mmGMCON_MISC3, 0xffffffff, 0xfc0,
	mmMC_PMG_AUTO_CFG, 0x00000100, 0x100,
पूर्ण;

अटल स्थिर u32 verde_golden_rlc_रेजिस्टरs[] =
अणु
	mmGB_ADDR_CONFIG, 0xffffffff, 0x02010002,
	mmRLC_LB_PARAMS, 0xffffffff, 0x033f1005,
	0x311f, 0xffffffff, 0x10808020,
	0x3122, 0xffffffff, 0x00800008,
	mmRLC_LB_CNTR_MAX, 0xffffffff, 0x00001000,
	mmRLC_LB_CNTL, 0xffffffff, 0x80010014,
पूर्ण;

अटल स्थिर u32 verde_golden_रेजिस्टरs[] =
अणु
	mmAZALIA_SCLK_CONTROL, 0x00000030, 0x00000011,
	mmCB_HW_CONTROL, 0x00010000, 0x00018208,
	mmDB_DEBUG, 0xffffffff, 0x00000000,
	mmDB_DEBUG2, 0xf00fffff, 0x00000400,
	mmDB_DEBUG3, 0x0002021c, 0x00020200,
	mmDCI_CLK_CNTL, 0x00000080, 0x00000000,
	0x340c, 0x000300c0, 0x00800040,
	0x360c, 0x000300c0, 0x00800040,
	mmFBC_DEBUG_COMP, 0x000000f0, 0x00000070,
	mmFBC_MISC, 0x00200000, 0x50100000,
	mmDIG0_HDMI_CONTROL, 0x31000311, 0x00000011,
	mmMC_SEQ_PMG_PG_HWCNTL, 0x00073ffe, 0x000022a2,
	mmMC_XPB_P2P_BAR_CFG, 0x000007ff, 0x00000000,
	mmPA_CL_ENHANCE, 0xf000001f, 0x00000007,
	mmPA_SC_FORCE_EOV_MAX_CNTS, 0xffffffff, 0x00ffffff,
	mmPA_SC_LINE_STIPPLE_STATE, 0x0000ff0f, 0x00000000,
	mmPA_SC_MODE_CNTL_1, 0x07ffffff, 0x4e000000,
	mmPA_SC_RASTER_CONFIG, 0x3f3f3fff, 0x0000124a,
	0x000c, 0xffffffff, 0x0040,
	0x000d, 0x00000040, 0x00004040,
	mmSPI_CONFIG_CNTL, 0x07ffffff, 0x03000000,
	mmSQ_DED_CNT, 0x01ff1f3f, 0x00000000,
	mmSQ_SEC_CNT, 0x01ff1f3f, 0x00000000,
	mmSX_DEBUG_1, 0x0000007f, 0x00000020,
	mmTA_CNTL_AUX, 0x00010000, 0x00010000,
	mmTCP_ADDR_CONFIG, 0x000003ff, 0x00000003,
	mmTCP_CHAN_STEER_HI, 0xffffffff, 0x00000000,
	mmTCP_CHAN_STEER_LO, 0xffffffff, 0x00001032,
	mmVGT_GS_VERTEX_REUSE, 0x0000001f, 0x00000010,
	mmVM_L2_CG, 0x000c0fc0, 0x000c0400,
	mmVM_PRT_APERTURE0_LOW_ADDR, 0x0fffffff, 0xffffffff,
	mmVM_PRT_APERTURE1_LOW_ADDR, 0x0fffffff, 0x0fffffff,
	mmVM_PRT_APERTURE2_LOW_ADDR, 0x0fffffff, 0x0fffffff,
	mmVM_PRT_APERTURE3_LOW_ADDR, 0x0fffffff, 0x0fffffff,
पूर्ण;

अटल स्थिर u32 oland_golden_रेजिस्टरs[] =
अणु
	mmAZALIA_SCLK_CONTROL, 0x00000030, 0x00000011,
	mmCB_HW_CONTROL, 0x00010000, 0x00018208,
	mmDB_DEBUG, 0xffffffff, 0x00000000,
	mmDB_DEBUG2, 0xf00fffff, 0x00000400,
	mmDB_DEBUG3, 0x0002021c, 0x00020200,
	mmDCI_CLK_CNTL, 0x00000080, 0x00000000,
	0x340c, 0x000300c0, 0x00800040,
	0x360c, 0x000300c0, 0x00800040,
	mmFBC_DEBUG_COMP, 0x000000f0, 0x00000070,
	mmFBC_MISC, 0x00200000, 0x50100000,
	mmDIG0_HDMI_CONTROL, 0x31000311, 0x00000011,
	mmMC_SEQ_PMG_PG_HWCNTL, 0x00073ffe, 0x000022a2,
	mmMC_XPB_P2P_BAR_CFG, 0x000007ff, 0x00000000,
	mmPA_CL_ENHANCE, 0xf000001f, 0x00000007,
	mmPA_SC_FORCE_EOV_MAX_CNTS, 0xffffffff, 0x00ffffff,
	mmPA_SC_LINE_STIPPLE_STATE, 0x0000ff0f, 0x00000000,
	mmPA_SC_MODE_CNTL_1, 0x07ffffff, 0x4e000000,
	mmPA_SC_RASTER_CONFIG, 0x3f3f3fff, 0x00000082,
	0x000c, 0xffffffff, 0x0040,
	0x000d, 0x00000040, 0x00004040,
	mmSPI_CONFIG_CNTL, 0x07ffffff, 0x03000000,
	mmSX_DEBUG_1, 0x0000007f, 0x00000020,
	mmTA_CNTL_AUX, 0x00010000, 0x00010000,
	mmTCP_ADDR_CONFIG, 0x000003ff, 0x000000f3,
	mmTCP_CHAN_STEER_HI, 0xffffffff, 0x00000000,
	mmTCP_CHAN_STEER_LO, 0xffffffff, 0x00003210,
	mmVGT_GS_VERTEX_REUSE, 0x0000001f, 0x00000010,
	mmVM_L2_CG, 0x000c0fc0, 0x000c0400,
	mmVM_PRT_APERTURE0_LOW_ADDR, 0x0fffffff, 0xffffffff,
	mmVM_PRT_APERTURE1_LOW_ADDR, 0x0fffffff, 0x0fffffff,
	mmVM_PRT_APERTURE2_LOW_ADDR, 0x0fffffff, 0x0fffffff,
	mmVM_PRT_APERTURE3_LOW_ADDR, 0x0fffffff, 0x0fffffff,

पूर्ण;

अटल स्थिर u32 oland_golden_rlc_रेजिस्टरs[] =
अणु
	mmGB_ADDR_CONFIG, 0xffffffff, 0x02010002,
	mmRLC_LB_PARAMS, 0xffffffff, 0x00601005,
	0x311f, 0xffffffff, 0x10104040,
	0x3122, 0xffffffff, 0x0100000a,
	mmRLC_LB_CNTR_MAX, 0xffffffff, 0x00000800,
	mmRLC_LB_CNTL, 0xffffffff, 0x800000f4,
पूर्ण;

अटल स्थिर u32 hainan_golden_रेजिस्टरs[] =
अणु
	0x17bc, 0x00000030, 0x00000011,
	mmCB_HW_CONTROL, 0x00010000, 0x00018208,
	mmDB_DEBUG, 0xffffffff, 0x00000000,
	mmDB_DEBUG2, 0xf00fffff, 0x00000400,
	mmDB_DEBUG3, 0x0002021c, 0x00020200,
	0x031e, 0x00000080, 0x00000000,
	0x3430, 0xff000fff, 0x00000100,
	0x340c, 0x000300c0, 0x00800040,
	0x3630, 0xff000fff, 0x00000100,
	0x360c, 0x000300c0, 0x00800040,
	0x16ec, 0x000000f0, 0x00000070,
	0x16f0, 0x00200000, 0x50100000,
	0x1c0c, 0x31000311, 0x00000011,
	mmMC_SEQ_PMG_PG_HWCNTL, 0x00073ffe, 0x000022a2,
	mmMC_XPB_P2P_BAR_CFG, 0x000007ff, 0x00000000,
	mmPA_CL_ENHANCE, 0xf000001f, 0x00000007,
	mmPA_SC_FORCE_EOV_MAX_CNTS, 0xffffffff, 0x00ffffff,
	mmPA_SC_LINE_STIPPLE_STATE, 0x0000ff0f, 0x00000000,
	mmPA_SC_MODE_CNTL_1, 0x07ffffff, 0x4e000000,
	mmPA_SC_RASTER_CONFIG, 0x3f3f3fff, 0x00000000,
	0x000c, 0xffffffff, 0x0040,
	0x000d, 0x00000040, 0x00004040,
	mmSPI_CONFIG_CNTL, 0x03e00000, 0x03600000,
	mmSX_DEBUG_1, 0x0000007f, 0x00000020,
	mmTA_CNTL_AUX, 0x00010000, 0x00010000,
	mmTCP_ADDR_CONFIG, 0x000003ff, 0x000000f1,
	mmTCP_CHAN_STEER_HI, 0xffffffff, 0x00000000,
	mmTCP_CHAN_STEER_LO, 0xffffffff, 0x00003210,
	mmVGT_GS_VERTEX_REUSE, 0x0000001f, 0x00000010,
	mmVM_L2_CG, 0x000c0fc0, 0x000c0400,
	mmVM_PRT_APERTURE0_LOW_ADDR, 0x0fffffff, 0xffffffff,
	mmVM_PRT_APERTURE1_LOW_ADDR, 0x0fffffff, 0x0fffffff,
	mmVM_PRT_APERTURE2_LOW_ADDR, 0x0fffffff, 0x0fffffff,
	mmVM_PRT_APERTURE3_LOW_ADDR, 0x0fffffff, 0x0fffffff,
पूर्ण;

अटल स्थिर u32 hainan_golden_रेजिस्टरs2[] =
अणु
	mmGB_ADDR_CONFIG, 0xffffffff, 0x2011003,
पूर्ण;

अटल स्थिर u32 tahiti_mgcg_cgcg_init[] =
अणु
	mmRLC_CGTT_MGCG_OVERRIDE, 0xffffffff, 0xfffffffc,
	mmGRBM_GFX_INDEX, 0xffffffff, 0xe0000000,
	mmCB_CGTT_SCLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_BCI_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_CP_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_GDS_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_IA_CLK_CTRL, 0xffffffff, 0x06000100,
	mmCGTT_PA_CLK_CTRL, 0xffffffff, 0x00000100,
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
	mmCGTT_TCI_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_TCP_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_VGT_CLK_CTRL, 0xffffffff, 0x06000100,
	mmDB_CGTT_CLK_CTRL_0, 0xffffffff, 0x00000100,
	mmTA_CGTT_CTRL, 0xffffffff, 0x00000100,
	mmTCA_CGTT_SCLK_CTRL, 0xffffffff, 0x00000100,
	mmTCC_CGTT_SCLK_CTRL, 0xffffffff, 0x00000100,
	mmTD_CGTT_CTRL, 0xffffffff, 0x00000100,
	mmGRBM_GFX_INDEX, 0xffffffff, 0xe0000000,
	0x2458, 0xffffffff, 0x00010000,
	0x2459, 0xffffffff, 0x00030002,
	0x245a, 0xffffffff, 0x00040007,
	0x245b, 0xffffffff, 0x00060005,
	0x245c, 0xffffffff, 0x00090008,
	0x245d, 0xffffffff, 0x00020001,
	0x245e, 0xffffffff, 0x00040003,
	0x245f, 0xffffffff, 0x00000007,
	0x2460, 0xffffffff, 0x00060005,
	0x2461, 0xffffffff, 0x00090008,
	0x2462, 0xffffffff, 0x00030002,
	0x2463, 0xffffffff, 0x00050004,
	0x2464, 0xffffffff, 0x00000008,
	0x2465, 0xffffffff, 0x00070006,
	0x2466, 0xffffffff, 0x000a0009,
	0x2467, 0xffffffff, 0x00040003,
	0x2468, 0xffffffff, 0x00060005,
	0x2469, 0xffffffff, 0x00000009,
	0x246a, 0xffffffff, 0x00080007,
	0x246b, 0xffffffff, 0x000b000a,
	0x246c, 0xffffffff, 0x00050004,
	0x246d, 0xffffffff, 0x00070006,
	0x246e, 0xffffffff, 0x0008000b,
	0x246f, 0xffffffff, 0x000a0009,
	0x2470, 0xffffffff, 0x000d000c,
	0x2471, 0xffffffff, 0x00060005,
	0x2472, 0xffffffff, 0x00080007,
	0x2473, 0xffffffff, 0x0000000b,
	0x2474, 0xffffffff, 0x000a0009,
	0x2475, 0xffffffff, 0x000d000c,
	0x2476, 0xffffffff, 0x00070006,
	0x2477, 0xffffffff, 0x00090008,
	0x2478, 0xffffffff, 0x0000000c,
	0x2479, 0xffffffff, 0x000b000a,
	0x247a, 0xffffffff, 0x000e000d,
	0x247b, 0xffffffff, 0x00080007,
	0x247c, 0xffffffff, 0x000a0009,
	0x247d, 0xffffffff, 0x0000000d,
	0x247e, 0xffffffff, 0x000c000b,
	0x247f, 0xffffffff, 0x000f000e,
	0x2480, 0xffffffff, 0x00090008,
	0x2481, 0xffffffff, 0x000b000a,
	0x2482, 0xffffffff, 0x000c000f,
	0x2483, 0xffffffff, 0x000e000d,
	0x2484, 0xffffffff, 0x00110010,
	0x2485, 0xffffffff, 0x000a0009,
	0x2486, 0xffffffff, 0x000c000b,
	0x2487, 0xffffffff, 0x0000000f,
	0x2488, 0xffffffff, 0x000e000d,
	0x2489, 0xffffffff, 0x00110010,
	0x248a, 0xffffffff, 0x000b000a,
	0x248b, 0xffffffff, 0x000d000c,
	0x248c, 0xffffffff, 0x00000010,
	0x248d, 0xffffffff, 0x000f000e,
	0x248e, 0xffffffff, 0x00120011,
	0x248f, 0xffffffff, 0x000c000b,
	0x2490, 0xffffffff, 0x000e000d,
	0x2491, 0xffffffff, 0x00000011,
	0x2492, 0xffffffff, 0x0010000f,
	0x2493, 0xffffffff, 0x00130012,
	0x2494, 0xffffffff, 0x000d000c,
	0x2495, 0xffffffff, 0x000f000e,
	0x2496, 0xffffffff, 0x00100013,
	0x2497, 0xffffffff, 0x00120011,
	0x2498, 0xffffffff, 0x00150014,
	0x2499, 0xffffffff, 0x000e000d,
	0x249a, 0xffffffff, 0x0010000f,
	0x249b, 0xffffffff, 0x00000013,
	0x249c, 0xffffffff, 0x00120011,
	0x249d, 0xffffffff, 0x00150014,
	0x249e, 0xffffffff, 0x000f000e,
	0x249f, 0xffffffff, 0x00110010,
	0x24a0, 0xffffffff, 0x00000014,
	0x24a1, 0xffffffff, 0x00130012,
	0x24a2, 0xffffffff, 0x00160015,
	0x24a3, 0xffffffff, 0x0010000f,
	0x24a4, 0xffffffff, 0x00120011,
	0x24a5, 0xffffffff, 0x00000015,
	0x24a6, 0xffffffff, 0x00140013,
	0x24a7, 0xffffffff, 0x00170016,
	mmCGTS_SM_CTRL_REG, 0xffffffff, 0x96940200,
	mmCP_RB_WPTR_POLL_CNTL, 0xffffffff, 0x00900100,
	mmRLC_GCPM_GENERAL_3, 0xffffffff, 0x00000080,
	mmRLC_CGCG_CGLS_CTRL, 0xffffffff, 0x0020003f,
	0x000c, 0xffffffff, 0x0000001c,
	0x000d, 0x000f0000, 0x000f0000,
	0x0583, 0xffffffff, 0x00000100,
	mmXDMA_CLOCK_GATING_CNTL, 0xffffffff, 0x00000100,
	mmXDMA_MEM_POWER_CNTL, 0x00000101, 0x00000000,
	mmMC_MEM_POWER_LS, 0xffffffff, 0x00000104,
	mmMC_CITF_MISC_WR_CG, 0x000c0000, 0x000c0000,
	mmMC_CITF_MISC_RD_CG, 0x000c0000, 0x000c0000,
	mmCGTT_DRM_CLK_CTRL0, 0xff000fff, 0x00000100,
	0x157a, 0x00000001, 0x00000001,
	mmHDP_MEM_POWER_LS, 0x00000001, 0x00000001,
	mmHDP_XDP_CGTT_BLK_CTRL, 0xc0000fff, 0x00000104,
	mmCP_MEM_SLP_CNTL, 0x00000001, 0x00000001,
	0x3430, 0xfffffff0, 0x00000100,
	0x3630, 0xfffffff0, 0x00000100,
पूर्ण;
अटल स्थिर u32 pitcairn_mgcg_cgcg_init[] =
अणु
	mmRLC_CGTT_MGCG_OVERRIDE, 0xffffffff, 0xfffffffc,
	mmGRBM_GFX_INDEX, 0xffffffff, 0xe0000000,
	mmCB_CGTT_SCLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_BCI_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_CP_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_GDS_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_IA_CLK_CTRL, 0xffffffff, 0x06000100,
	mmCGTT_PA_CLK_CTRL, 0xffffffff, 0x00000100,
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
	mmCGTT_TCI_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_TCP_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_VGT_CLK_CTRL, 0xffffffff, 0x06000100,
	mmDB_CGTT_CLK_CTRL_0, 0xffffffff, 0x00000100,
	mmTA_CGTT_CTRL, 0xffffffff, 0x00000100,
	mmTCA_CGTT_SCLK_CTRL, 0xffffffff, 0x00000100,
	mmTCC_CGTT_SCLK_CTRL, 0xffffffff, 0x00000100,
	mmTD_CGTT_CTRL, 0xffffffff, 0x00000100,
	mmGRBM_GFX_INDEX, 0xffffffff, 0xe0000000,
	0x2458, 0xffffffff, 0x00010000,
	0x2459, 0xffffffff, 0x00030002,
	0x245a, 0xffffffff, 0x00040007,
	0x245b, 0xffffffff, 0x00060005,
	0x245c, 0xffffffff, 0x00090008,
	0x245d, 0xffffffff, 0x00020001,
	0x245e, 0xffffffff, 0x00040003,
	0x245f, 0xffffffff, 0x00000007,
	0x2460, 0xffffffff, 0x00060005,
	0x2461, 0xffffffff, 0x00090008,
	0x2462, 0xffffffff, 0x00030002,
	0x2463, 0xffffffff, 0x00050004,
	0x2464, 0xffffffff, 0x00000008,
	0x2465, 0xffffffff, 0x00070006,
	0x2466, 0xffffffff, 0x000a0009,
	0x2467, 0xffffffff, 0x00040003,
	0x2468, 0xffffffff, 0x00060005,
	0x2469, 0xffffffff, 0x00000009,
	0x246a, 0xffffffff, 0x00080007,
	0x246b, 0xffffffff, 0x000b000a,
	0x246c, 0xffffffff, 0x00050004,
	0x246d, 0xffffffff, 0x00070006,
	0x246e, 0xffffffff, 0x0008000b,
	0x246f, 0xffffffff, 0x000a0009,
	0x2470, 0xffffffff, 0x000d000c,
	0x2480, 0xffffffff, 0x00090008,
	0x2481, 0xffffffff, 0x000b000a,
	0x2482, 0xffffffff, 0x000c000f,
	0x2483, 0xffffffff, 0x000e000d,
	0x2484, 0xffffffff, 0x00110010,
	0x2485, 0xffffffff, 0x000a0009,
	0x2486, 0xffffffff, 0x000c000b,
	0x2487, 0xffffffff, 0x0000000f,
	0x2488, 0xffffffff, 0x000e000d,
	0x2489, 0xffffffff, 0x00110010,
	0x248a, 0xffffffff, 0x000b000a,
	0x248b, 0xffffffff, 0x000d000c,
	0x248c, 0xffffffff, 0x00000010,
	0x248d, 0xffffffff, 0x000f000e,
	0x248e, 0xffffffff, 0x00120011,
	0x248f, 0xffffffff, 0x000c000b,
	0x2490, 0xffffffff, 0x000e000d,
	0x2491, 0xffffffff, 0x00000011,
	0x2492, 0xffffffff, 0x0010000f,
	0x2493, 0xffffffff, 0x00130012,
	0x2494, 0xffffffff, 0x000d000c,
	0x2495, 0xffffffff, 0x000f000e,
	0x2496, 0xffffffff, 0x00100013,
	0x2497, 0xffffffff, 0x00120011,
	0x2498, 0xffffffff, 0x00150014,
	mmCGTS_SM_CTRL_REG, 0xffffffff, 0x96940200,
	mmCP_RB_WPTR_POLL_CNTL, 0xffffffff, 0x00900100,
	mmRLC_GCPM_GENERAL_3, 0xffffffff, 0x00000080,
	mmRLC_CGCG_CGLS_CTRL, 0xffffffff, 0x0020003f,
	0x000c, 0xffffffff, 0x0000001c,
	0x000d, 0x000f0000, 0x000f0000,
	0x0583, 0xffffffff, 0x00000100,
	mmXDMA_CLOCK_GATING_CNTL, 0xffffffff, 0x00000100,
	mmXDMA_MEM_POWER_CNTL, 0x00000101, 0x00000000,
	mmMC_MEM_POWER_LS, 0xffffffff, 0x00000104,
	mmCGTT_DRM_CLK_CTRL0, 0xff000fff, 0x00000100,
	0x157a, 0x00000001, 0x00000001,
	mmHDP_MEM_POWER_LS, 0x00000001, 0x00000001,
	mmHDP_XDP_CGTT_BLK_CTRL, 0xc0000fff, 0x00000104,
	mmCP_MEM_SLP_CNTL, 0x00000001, 0x00000001,
	0x3430, 0xfffffff0, 0x00000100,
	0x3630, 0xfffffff0, 0x00000100,
पूर्ण;

अटल स्थिर u32 verde_mgcg_cgcg_init[] =
अणु
	mmRLC_CGTT_MGCG_OVERRIDE, 0xffffffff, 0xfffffffc,
	mmGRBM_GFX_INDEX, 0xffffffff, 0xe0000000,
	mmCB_CGTT_SCLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_BCI_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_CP_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_GDS_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_IA_CLK_CTRL, 0xffffffff, 0x06000100,
	mmCGTT_PA_CLK_CTRL, 0xffffffff, 0x00000100,
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
	mmCGTT_TCI_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_TCP_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_VGT_CLK_CTRL, 0xffffffff, 0x06000100,
	mmDB_CGTT_CLK_CTRL_0, 0xffffffff, 0x00000100,
	mmTA_CGTT_CTRL, 0xffffffff, 0x00000100,
	mmTCA_CGTT_SCLK_CTRL, 0xffffffff, 0x00000100,
	mmTCC_CGTT_SCLK_CTRL, 0xffffffff, 0x00000100,
	mmTD_CGTT_CTRL, 0xffffffff, 0x00000100,
	mmGRBM_GFX_INDEX, 0xffffffff, 0xe0000000,
	0x2458, 0xffffffff, 0x00010000,
	0x2459, 0xffffffff, 0x00030002,
	0x245a, 0xffffffff, 0x00040007,
	0x245b, 0xffffffff, 0x00060005,
	0x245c, 0xffffffff, 0x00090008,
	0x245d, 0xffffffff, 0x00020001,
	0x245e, 0xffffffff, 0x00040003,
	0x245f, 0xffffffff, 0x00000007,
	0x2460, 0xffffffff, 0x00060005,
	0x2461, 0xffffffff, 0x00090008,
	0x2462, 0xffffffff, 0x00030002,
	0x2463, 0xffffffff, 0x00050004,
	0x2464, 0xffffffff, 0x00000008,
	0x2465, 0xffffffff, 0x00070006,
	0x2466, 0xffffffff, 0x000a0009,
	0x2467, 0xffffffff, 0x00040003,
	0x2468, 0xffffffff, 0x00060005,
	0x2469, 0xffffffff, 0x00000009,
	0x246a, 0xffffffff, 0x00080007,
	0x246b, 0xffffffff, 0x000b000a,
	0x246c, 0xffffffff, 0x00050004,
	0x246d, 0xffffffff, 0x00070006,
	0x246e, 0xffffffff, 0x0008000b,
	0x246f, 0xffffffff, 0x000a0009,
	0x2470, 0xffffffff, 0x000d000c,
	0x2480, 0xffffffff, 0x00090008,
	0x2481, 0xffffffff, 0x000b000a,
	0x2482, 0xffffffff, 0x000c000f,
	0x2483, 0xffffffff, 0x000e000d,
	0x2484, 0xffffffff, 0x00110010,
	0x2485, 0xffffffff, 0x000a0009,
	0x2486, 0xffffffff, 0x000c000b,
	0x2487, 0xffffffff, 0x0000000f,
	0x2488, 0xffffffff, 0x000e000d,
	0x2489, 0xffffffff, 0x00110010,
	0x248a, 0xffffffff, 0x000b000a,
	0x248b, 0xffffffff, 0x000d000c,
	0x248c, 0xffffffff, 0x00000010,
	0x248d, 0xffffffff, 0x000f000e,
	0x248e, 0xffffffff, 0x00120011,
	0x248f, 0xffffffff, 0x000c000b,
	0x2490, 0xffffffff, 0x000e000d,
	0x2491, 0xffffffff, 0x00000011,
	0x2492, 0xffffffff, 0x0010000f,
	0x2493, 0xffffffff, 0x00130012,
	0x2494, 0xffffffff, 0x000d000c,
	0x2495, 0xffffffff, 0x000f000e,
	0x2496, 0xffffffff, 0x00100013,
	0x2497, 0xffffffff, 0x00120011,
	0x2498, 0xffffffff, 0x00150014,
	mmCGTS_SM_CTRL_REG, 0xffffffff, 0x96940200,
	mmCP_RB_WPTR_POLL_CNTL, 0xffffffff, 0x00900100,
	mmRLC_GCPM_GENERAL_3, 0xffffffff, 0x00000080,
	mmRLC_CGCG_CGLS_CTRL, 0xffffffff, 0x0020003f,
	0x000c, 0xffffffff, 0x0000001c,
	0x000d, 0x000f0000, 0x000f0000,
	0x0583, 0xffffffff, 0x00000100,
	mmXDMA_CLOCK_GATING_CNTL, 0xffffffff, 0x00000100,
	mmXDMA_MEM_POWER_CNTL, 0x00000101, 0x00000000,
	mmMC_MEM_POWER_LS, 0xffffffff, 0x00000104,
	mmMC_CITF_MISC_WR_CG, 0x000c0000, 0x000c0000,
	mmMC_CITF_MISC_RD_CG, 0x000c0000, 0x000c0000,
	mmCGTT_DRM_CLK_CTRL0, 0xff000fff, 0x00000100,
	0x157a, 0x00000001, 0x00000001,
	mmHDP_MEM_POWER_LS, 0x00000001, 0x00000001,
	mmHDP_XDP_CGTT_BLK_CTRL, 0xc0000fff, 0x00000104,
	mmCP_MEM_SLP_CNTL, 0x00000001, 0x00000001,
	0x3430, 0xfffffff0, 0x00000100,
	0x3630, 0xfffffff0, 0x00000100,
पूर्ण;

अटल स्थिर u32 oland_mgcg_cgcg_init[] =
अणु
	mmRLC_CGTT_MGCG_OVERRIDE, 0xffffffff, 0xfffffffc,
	mmGRBM_GFX_INDEX, 0xffffffff, 0xe0000000,
	mmCB_CGTT_SCLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_BCI_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_CP_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_GDS_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_IA_CLK_CTRL, 0xffffffff, 0x06000100,
	mmCGTT_PA_CLK_CTRL, 0xffffffff, 0x00000100,
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
	mmCGTT_TCI_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_TCP_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_VGT_CLK_CTRL, 0xffffffff, 0x06000100,
	mmDB_CGTT_CLK_CTRL_0, 0xffffffff, 0x00000100,
	mmTA_CGTT_CTRL, 0xffffffff, 0x00000100,
	mmTCA_CGTT_SCLK_CTRL, 0xffffffff, 0x00000100,
	mmTCC_CGTT_SCLK_CTRL, 0xffffffff, 0x00000100,
	mmTD_CGTT_CTRL, 0xffffffff, 0x00000100,
	mmGRBM_GFX_INDEX, 0xffffffff, 0xe0000000,
	0x2458, 0xffffffff, 0x00010000,
	0x2459, 0xffffffff, 0x00030002,
	0x245a, 0xffffffff, 0x00040007,
	0x245b, 0xffffffff, 0x00060005,
	0x245c, 0xffffffff, 0x00090008,
	0x245d, 0xffffffff, 0x00020001,
	0x245e, 0xffffffff, 0x00040003,
	0x245f, 0xffffffff, 0x00000007,
	0x2460, 0xffffffff, 0x00060005,
	0x2461, 0xffffffff, 0x00090008,
	0x2462, 0xffffffff, 0x00030002,
	0x2463, 0xffffffff, 0x00050004,
	0x2464, 0xffffffff, 0x00000008,
	0x2465, 0xffffffff, 0x00070006,
	0x2466, 0xffffffff, 0x000a0009,
	0x2467, 0xffffffff, 0x00040003,
	0x2468, 0xffffffff, 0x00060005,
	0x2469, 0xffffffff, 0x00000009,
	0x246a, 0xffffffff, 0x00080007,
	0x246b, 0xffffffff, 0x000b000a,
	0x246c, 0xffffffff, 0x00050004,
	0x246d, 0xffffffff, 0x00070006,
	0x246e, 0xffffffff, 0x0008000b,
	0x246f, 0xffffffff, 0x000a0009,
	0x2470, 0xffffffff, 0x000d000c,
	0x2471, 0xffffffff, 0x00060005,
	0x2472, 0xffffffff, 0x00080007,
	0x2473, 0xffffffff, 0x0000000b,
	0x2474, 0xffffffff, 0x000a0009,
	0x2475, 0xffffffff, 0x000d000c,
	mmCGTS_SM_CTRL_REG, 0xffffffff, 0x96940200,
	mmCP_RB_WPTR_POLL_CNTL, 0xffffffff, 0x00900100,
	mmRLC_GCPM_GENERAL_3, 0xffffffff, 0x00000080,
	mmRLC_CGCG_CGLS_CTRL, 0xffffffff, 0x0020003f,
	0x000c, 0xffffffff, 0x0000001c,
	0x000d, 0x000f0000, 0x000f0000,
	0x0583, 0xffffffff, 0x00000100,
	mmXDMA_CLOCK_GATING_CNTL, 0xffffffff, 0x00000100,
	mmXDMA_MEM_POWER_CNTL, 0x00000101, 0x00000000,
	mmMC_MEM_POWER_LS, 0xffffffff, 0x00000104,
	mmMC_CITF_MISC_WR_CG, 0x000c0000, 0x000c0000,
	mmMC_CITF_MISC_RD_CG, 0x000c0000, 0x000c0000,
	mmCGTT_DRM_CLK_CTRL0, 0xff000fff, 0x00000100,
	0x157a, 0x00000001, 0x00000001,
	mmHDP_MEM_POWER_LS, 0x00000001, 0x00000001,
	mmHDP_XDP_CGTT_BLK_CTRL, 0xc0000fff, 0x00000104,
	mmCP_MEM_SLP_CNTL, 0x00000001, 0x00000001,
	0x3430, 0xfffffff0, 0x00000100,
	0x3630, 0xfffffff0, 0x00000100,
पूर्ण;

अटल स्थिर u32 hainan_mgcg_cgcg_init[] =
अणु
	mmRLC_CGTT_MGCG_OVERRIDE, 0xffffffff, 0xfffffffc,
	mmGRBM_GFX_INDEX, 0xffffffff, 0xe0000000,
	mmCB_CGTT_SCLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_BCI_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_CP_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_GDS_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_IA_CLK_CTRL, 0xffffffff, 0x06000100,
	mmCGTT_PA_CLK_CTRL, 0xffffffff, 0x00000100,
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
	mmCGTT_TCI_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_TCP_CLK_CTRL, 0xffffffff, 0x00000100,
	mmCGTT_VGT_CLK_CTRL, 0xffffffff, 0x06000100,
	mmDB_CGTT_CLK_CTRL_0, 0xffffffff, 0x00000100,
	mmTA_CGTT_CTRL, 0xffffffff, 0x00000100,
	mmTCA_CGTT_SCLK_CTRL, 0xffffffff, 0x00000100,
	mmTCC_CGTT_SCLK_CTRL, 0xffffffff, 0x00000100,
	mmTD_CGTT_CTRL, 0xffffffff, 0x00000100,
	mmGRBM_GFX_INDEX, 0xffffffff, 0xe0000000,
	0x2458, 0xffffffff, 0x00010000,
	0x2459, 0xffffffff, 0x00030002,
	0x245a, 0xffffffff, 0x00040007,
	0x245b, 0xffffffff, 0x00060005,
	0x245c, 0xffffffff, 0x00090008,
	0x245d, 0xffffffff, 0x00020001,
	0x245e, 0xffffffff, 0x00040003,
	0x245f, 0xffffffff, 0x00000007,
	0x2460, 0xffffffff, 0x00060005,
	0x2461, 0xffffffff, 0x00090008,
	0x2462, 0xffffffff, 0x00030002,
	0x2463, 0xffffffff, 0x00050004,
	0x2464, 0xffffffff, 0x00000008,
	0x2465, 0xffffffff, 0x00070006,
	0x2466, 0xffffffff, 0x000a0009,
	0x2467, 0xffffffff, 0x00040003,
	0x2468, 0xffffffff, 0x00060005,
	0x2469, 0xffffffff, 0x00000009,
	0x246a, 0xffffffff, 0x00080007,
	0x246b, 0xffffffff, 0x000b000a,
	0x246c, 0xffffffff, 0x00050004,
	0x246d, 0xffffffff, 0x00070006,
	0x246e, 0xffffffff, 0x0008000b,
	0x246f, 0xffffffff, 0x000a0009,
	0x2470, 0xffffffff, 0x000d000c,
	0x2471, 0xffffffff, 0x00060005,
	0x2472, 0xffffffff, 0x00080007,
	0x2473, 0xffffffff, 0x0000000b,
	0x2474, 0xffffffff, 0x000a0009,
	0x2475, 0xffffffff, 0x000d000c,
	mmCGTS_SM_CTRL_REG, 0xffffffff, 0x96940200,
	mmCP_RB_WPTR_POLL_CNTL, 0xffffffff, 0x00900100,
	mmRLC_GCPM_GENERAL_3, 0xffffffff, 0x00000080,
	mmRLC_CGCG_CGLS_CTRL, 0xffffffff, 0x0020003f,
	0x000c, 0xffffffff, 0x0000001c,
	0x000d, 0x000f0000, 0x000f0000,
	0x0583, 0xffffffff, 0x00000100,
	0x0409, 0xffffffff, 0x00000100,
	mmMC_MEM_POWER_LS, 0xffffffff, 0x00000104,
	mmMC_CITF_MISC_WR_CG, 0x000c0000, 0x000c0000,
	mmMC_CITF_MISC_RD_CG, 0x000c0000, 0x000c0000,
	mmHDP_MEM_POWER_LS, 0x00000001, 0x00000001,
	mmHDP_XDP_CGTT_BLK_CTRL, 0xc0000fff, 0x00000104,
	mmCP_MEM_SLP_CNTL, 0x00000001, 0x00000001,
	0x3430, 0xfffffff0, 0x00000100,
	0x3630, 0xfffffff0, 0x00000100,
पूर्ण;

/* XXX: update when we support VCE */
#अगर 0
/* tahiti, pitcarin, verde */
अटल स्थिर काष्ठा amdgpu_video_codec_info tahiti_video_codecs_encode_array[] =
अणु
	अणु
		.codec_type = AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG4_AVC,
		.max_width = 2048,
		.max_height = 1152,
		.max_pixels_per_frame = 2048 * 1152,
		.max_level = 0,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_video_codecs tahiti_video_codecs_encode =
अणु
	.codec_count = ARRAY_SIZE(tahiti_video_codecs_encode_array),
	.codec_array = tahiti_video_codecs_encode_array,
पूर्ण;
#अन्यथा
अटल स्थिर काष्ठा amdgpu_video_codecs tahiti_video_codecs_encode =
अणु
	.codec_count = 0,
	.codec_array = शून्य,
पूर्ण;
#पूर्ण_अगर
/* oland and hainan करोn't support encode */
अटल स्थिर काष्ठा amdgpu_video_codecs hainan_video_codecs_encode =
अणु
	.codec_count = 0,
	.codec_array = शून्य,
पूर्ण;

/* tahiti, pitcarin, verde, oland */
अटल स्थिर काष्ठा amdgpu_video_codec_info tahiti_video_codecs_decode_array[] =
अणु
	अणु
		.codec_type = AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG2,
		.max_width = 2048,
		.max_height = 1152,
		.max_pixels_per_frame = 2048 * 1152,
		.max_level = 3,
	पूर्ण,
	अणु
		.codec_type = AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG4,
		.max_width = 2048,
		.max_height = 1152,
		.max_pixels_per_frame = 2048 * 1152,
		.max_level = 5,
	पूर्ण,
	अणु
		.codec_type = AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG4_AVC,
		.max_width = 2048,
		.max_height = 1152,
		.max_pixels_per_frame = 2048 * 1152,
		.max_level = 41,
	पूर्ण,
	अणु
		.codec_type = AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_VC1,
		.max_width = 2048,
		.max_height = 1152,
		.max_pixels_per_frame = 2048 * 1152,
		.max_level = 4,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_video_codecs tahiti_video_codecs_decode =
अणु
	.codec_count = ARRAY_SIZE(tahiti_video_codecs_decode_array),
	.codec_array = tahiti_video_codecs_decode_array,
पूर्ण;

/* hainan करोesn't support decode */
अटल स्थिर काष्ठा amdgpu_video_codecs hainan_video_codecs_decode =
अणु
	.codec_count = 0,
	.codec_array = शून्य,
पूर्ण;

अटल पूर्णांक si_query_video_codecs(काष्ठा amdgpu_device *adev, bool encode,
				 स्थिर काष्ठा amdgpu_video_codecs **codecs)
अणु
	चयन (adev->asic_type) अणु
	हाल CHIP_VERDE:
	हाल CHIP_TAHITI:
	हाल CHIP_PITCAIRN:
		अगर (encode)
			*codecs = &tahiti_video_codecs_encode;
		अन्यथा
			*codecs = &tahiti_video_codecs_decode;
		वापस 0;
	हाल CHIP_OLAND:
		अगर (encode)
			*codecs = &hainan_video_codecs_encode;
		अन्यथा
			*codecs = &tahiti_video_codecs_decode;
		वापस 0;
	हाल CHIP_HAIन_अंक:
		अगर (encode)
			*codecs = &hainan_video_codecs_encode;
		अन्यथा
			*codecs = &hainan_video_codecs_decode;
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल u32 si_pcie_rreg(काष्ठा amdgpu_device *adev, u32 reg)
अणु
	अचिन्हित दीर्घ flags;
	u32 r;

	spin_lock_irqsave(&adev->pcie_idx_lock, flags);
	WREG32(AMDGPU_PCIE_INDEX, reg);
	(व्योम)RREG32(AMDGPU_PCIE_INDEX);
	r = RREG32(AMDGPU_PCIE_DATA);
	spin_unlock_irqrestore(&adev->pcie_idx_lock, flags);
	वापस r;
पूर्ण

अटल व्योम si_pcie_wreg(काष्ठा amdgpu_device *adev, u32 reg, u32 v)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&adev->pcie_idx_lock, flags);
	WREG32(AMDGPU_PCIE_INDEX, reg);
	(व्योम)RREG32(AMDGPU_PCIE_INDEX);
	WREG32(AMDGPU_PCIE_DATA, v);
	(व्योम)RREG32(AMDGPU_PCIE_DATA);
	spin_unlock_irqrestore(&adev->pcie_idx_lock, flags);
पूर्ण

अटल u32 si_pciep_rreg(काष्ठा amdgpu_device *adev, u32 reg)
अणु
	अचिन्हित दीर्घ flags;
	u32 r;

	spin_lock_irqsave(&adev->pcie_idx_lock, flags);
	WREG32(PCIE_PORT_INDEX, ((reg) & 0xff));
	(व्योम)RREG32(PCIE_PORT_INDEX);
	r = RREG32(PCIE_PORT_DATA);
	spin_unlock_irqrestore(&adev->pcie_idx_lock, flags);
	वापस r;
पूर्ण

अटल व्योम si_pciep_wreg(काष्ठा amdgpu_device *adev, u32 reg, u32 v)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&adev->pcie_idx_lock, flags);
	WREG32(PCIE_PORT_INDEX, ((reg) & 0xff));
	(व्योम)RREG32(PCIE_PORT_INDEX);
	WREG32(PCIE_PORT_DATA, (v));
	(व्योम)RREG32(PCIE_PORT_DATA);
	spin_unlock_irqrestore(&adev->pcie_idx_lock, flags);
पूर्ण

अटल u32 si_smc_rreg(काष्ठा amdgpu_device *adev, u32 reg)
अणु
	अचिन्हित दीर्घ flags;
	u32 r;

	spin_lock_irqsave(&adev->smc_idx_lock, flags);
	WREG32(SMC_IND_INDEX_0, (reg));
	r = RREG32(SMC_IND_DATA_0);
	spin_unlock_irqrestore(&adev->smc_idx_lock, flags);
	वापस r;
पूर्ण

अटल व्योम si_smc_wreg(काष्ठा amdgpu_device *adev, u32 reg, u32 v)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&adev->smc_idx_lock, flags);
	WREG32(SMC_IND_INDEX_0, (reg));
	WREG32(SMC_IND_DATA_0, (v));
	spin_unlock_irqrestore(&adev->smc_idx_lock, flags);
पूर्ण

अटल u32 si_uvd_ctx_rreg(काष्ठा amdgpu_device *adev, u32 reg)
अणु
	अचिन्हित दीर्घ flags;
	u32 r;

	spin_lock_irqsave(&adev->uvd_ctx_idx_lock, flags);
	WREG32(mmUVD_CTX_INDEX, ((reg) & 0x1ff));
	r = RREG32(mmUVD_CTX_DATA);
	spin_unlock_irqrestore(&adev->uvd_ctx_idx_lock, flags);
	वापस r;
पूर्ण

अटल व्योम si_uvd_ctx_wreg(काष्ठा amdgpu_device *adev, u32 reg, u32 v)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&adev->uvd_ctx_idx_lock, flags);
	WREG32(mmUVD_CTX_INDEX, ((reg) & 0x1ff));
	WREG32(mmUVD_CTX_DATA, (v));
	spin_unlock_irqrestore(&adev->uvd_ctx_idx_lock, flags);
पूर्ण

अटल काष्ठा amdgpu_allowed_रेजिस्टर_entry si_allowed_पढ़ो_रेजिस्टरs[] = अणु
	अणुGRBM_STATUSपूर्ण,
	अणुmmGRBM_STATUS2पूर्ण,
	अणुmmGRBM_STATUS_SE0पूर्ण,
	अणुmmGRBM_STATUS_SE1पूर्ण,
	अणुmmSRBM_STATUSपूर्ण,
	अणुmmSRBM_STATUS2पूर्ण,
	अणुDMA_STATUS_REG + DMA0_REGISTER_OFFSETपूर्ण,
	अणुDMA_STATUS_REG + DMA1_REGISTER_OFFSETपूर्ण,
	अणुmmCP_STATपूर्ण,
	अणुmmCP_STALLED_STAT1पूर्ण,
	अणुmmCP_STALLED_STAT2पूर्ण,
	अणुmmCP_STALLED_STAT3पूर्ण,
	अणुGB_ADDR_CONFIGपूर्ण,
	अणुMC_ARB_RAMCFGपूर्ण,
	अणुGB_TILE_MODE0पूर्ण,
	अणुGB_TILE_MODE1पूर्ण,
	अणुGB_TILE_MODE2पूर्ण,
	अणुGB_TILE_MODE3पूर्ण,
	अणुGB_TILE_MODE4पूर्ण,
	अणुGB_TILE_MODE5पूर्ण,
	अणुGB_TILE_MODE6पूर्ण,
	अणुGB_TILE_MODE7पूर्ण,
	अणुGB_TILE_MODE8पूर्ण,
	अणुGB_TILE_MODE9पूर्ण,
	अणुGB_TILE_MODE10पूर्ण,
	अणुGB_TILE_MODE11पूर्ण,
	अणुGB_TILE_MODE12पूर्ण,
	अणुGB_TILE_MODE13पूर्ण,
	अणुGB_TILE_MODE14पूर्ण,
	अणुGB_TILE_MODE15पूर्ण,
	अणुGB_TILE_MODE16पूर्ण,
	अणुGB_TILE_MODE17पूर्ण,
	अणुGB_TILE_MODE18पूर्ण,
	अणुGB_TILE_MODE19पूर्ण,
	अणुGB_TILE_MODE20पूर्ण,
	अणुGB_TILE_MODE21पूर्ण,
	अणुGB_TILE_MODE22पूर्ण,
	अणुGB_TILE_MODE23पूर्ण,
	अणुGB_TILE_MODE24पूर्ण,
	अणुGB_TILE_MODE25पूर्ण,
	अणुGB_TILE_MODE26पूर्ण,
	अणुGB_TILE_MODE27पूर्ण,
	अणुGB_TILE_MODE28पूर्ण,
	अणुGB_TILE_MODE29पूर्ण,
	अणुGB_TILE_MODE30पूर्ण,
	अणुGB_TILE_MODE31पूर्ण,
	अणुCC_RB_BACKEND_DISABLE, trueपूर्ण,
	अणुGC_USER_RB_BACKEND_DISABLE, trueपूर्ण,
	अणुPA_SC_RASTER_CONFIG, trueपूर्ण,
पूर्ण;

अटल uपूर्णांक32_t si_get_रेजिस्टर_value(काष्ठा amdgpu_device *adev,
				      bool indexed, u32 se_num,
				      u32 sh_num, u32 reg_offset)
अणु
	अगर (indexed) अणु
		uपूर्णांक32_t val;
		अचिन्हित se_idx = (se_num == 0xffffffff) ? 0 : se_num;
		अचिन्हित sh_idx = (sh_num == 0xffffffff) ? 0 : sh_num;

		चयन (reg_offset) अणु
		हाल mmCC_RB_BACKEND_DISABLE:
			वापस adev->gfx.config.rb_config[se_idx][sh_idx].rb_backend_disable;
		हाल mmGC_USER_RB_BACKEND_DISABLE:
			वापस adev->gfx.config.rb_config[se_idx][sh_idx].user_rb_backend_disable;
		हाल mmPA_SC_RASTER_CONFIG:
			वापस adev->gfx.config.rb_config[se_idx][sh_idx].raster_config;
		पूर्ण

		mutex_lock(&adev->grbm_idx_mutex);
		अगर (se_num != 0xffffffff || sh_num != 0xffffffff)
			amdgpu_gfx_select_se_sh(adev, se_num, sh_num, 0xffffffff);

		val = RREG32(reg_offset);

		अगर (se_num != 0xffffffff || sh_num != 0xffffffff)
			amdgpu_gfx_select_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff);
		mutex_unlock(&adev->grbm_idx_mutex);
		वापस val;
	पूर्ण अन्यथा अणु
		अचिन्हित idx;

		चयन (reg_offset) अणु
		हाल mmGB_ADDR_CONFIG:
			वापस adev->gfx.config.gb_addr_config;
		हाल mmMC_ARB_RAMCFG:
			वापस adev->gfx.config.mc_arb_ramcfg;
		हाल mmGB_TILE_MODE0:
		हाल mmGB_TILE_MODE1:
		हाल mmGB_TILE_MODE2:
		हाल mmGB_TILE_MODE3:
		हाल mmGB_TILE_MODE4:
		हाल mmGB_TILE_MODE5:
		हाल mmGB_TILE_MODE6:
		हाल mmGB_TILE_MODE7:
		हाल mmGB_TILE_MODE8:
		हाल mmGB_TILE_MODE9:
		हाल mmGB_TILE_MODE10:
		हाल mmGB_TILE_MODE11:
		हाल mmGB_TILE_MODE12:
		हाल mmGB_TILE_MODE13:
		हाल mmGB_TILE_MODE14:
		हाल mmGB_TILE_MODE15:
		हाल mmGB_TILE_MODE16:
		हाल mmGB_TILE_MODE17:
		हाल mmGB_TILE_MODE18:
		हाल mmGB_TILE_MODE19:
		हाल mmGB_TILE_MODE20:
		हाल mmGB_TILE_MODE21:
		हाल mmGB_TILE_MODE22:
		हाल mmGB_TILE_MODE23:
		हाल mmGB_TILE_MODE24:
		हाल mmGB_TILE_MODE25:
		हाल mmGB_TILE_MODE26:
		हाल mmGB_TILE_MODE27:
		हाल mmGB_TILE_MODE28:
		हाल mmGB_TILE_MODE29:
		हाल mmGB_TILE_MODE30:
		हाल mmGB_TILE_MODE31:
			idx = (reg_offset - mmGB_TILE_MODE0);
			वापस adev->gfx.config.tile_mode_array[idx];
		शेष:
			वापस RREG32(reg_offset);
		पूर्ण
	पूर्ण
पूर्ण
अटल पूर्णांक si_पढ़ो_रेजिस्टर(काष्ठा amdgpu_device *adev, u32 se_num,
			     u32 sh_num, u32 reg_offset, u32 *value)
अणु
	uपूर्णांक32_t i;

	*value = 0;
	क्रम (i = 0; i < ARRAY_SIZE(si_allowed_पढ़ो_रेजिस्टरs); i++) अणु
		bool indexed = si_allowed_पढ़ो_रेजिस्टरs[i].grbm_indexed;

		अगर (reg_offset != si_allowed_पढ़ो_रेजिस्टरs[i].reg_offset)
			जारी;

		*value = si_get_रेजिस्टर_value(adev, indexed, se_num, sh_num,
					       reg_offset);
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल bool si_पढ़ो_disabled_bios(काष्ठा amdgpu_device *adev)
अणु
	u32 bus_cntl;
	u32 d1vga_control = 0;
	u32 d2vga_control = 0;
	u32 vga_render_control = 0;
	u32 rom_cntl;
	bool r;

	bus_cntl = RREG32(R600_BUS_CNTL);
	अगर (adev->mode_info.num_crtc) अणु
		d1vga_control = RREG32(AVIVO_D1VGA_CONTROL);
		d2vga_control = RREG32(AVIVO_D2VGA_CONTROL);
		vga_render_control = RREG32(VGA_RENDER_CONTROL);
	पूर्ण
	rom_cntl = RREG32(R600_ROM_CNTL);

	/* enable the rom */
	WREG32(R600_BUS_CNTL, (bus_cntl & ~R600_BIOS_ROM_DIS));
	अगर (adev->mode_info.num_crtc) अणु
		/* Disable VGA mode */
		WREG32(AVIVO_D1VGA_CONTROL,
		       (d1vga_control & ~(AVIVO_DVGA_CONTROL_MODE_ENABLE |
					  AVIVO_DVGA_CONTROL_TIMING_SELECT)));
		WREG32(AVIVO_D2VGA_CONTROL,
		       (d2vga_control & ~(AVIVO_DVGA_CONTROL_MODE_ENABLE |
					  AVIVO_DVGA_CONTROL_TIMING_SELECT)));
		WREG32(VGA_RENDER_CONTROL,
		       (vga_render_control & C_000300_VGA_VSTATUS_CNTL));
	पूर्ण
	WREG32(R600_ROM_CNTL, rom_cntl | R600_SCK_OVERWRITE);

	r = amdgpu_पढ़ो_bios(adev);

	/* restore regs */
	WREG32(R600_BUS_CNTL, bus_cntl);
	अगर (adev->mode_info.num_crtc) अणु
		WREG32(AVIVO_D1VGA_CONTROL, d1vga_control);
		WREG32(AVIVO_D2VGA_CONTROL, d2vga_control);
		WREG32(VGA_RENDER_CONTROL, vga_render_control);
	पूर्ण
	WREG32(R600_ROM_CNTL, rom_cntl);
	वापस r;
पूर्ण

#घोषणा mmROM_INDEX 0x2A
#घोषणा mmROM_DATA  0x2B

अटल bool si_पढ़ो_bios_from_rom(काष्ठा amdgpu_device *adev,
				  u8 *bios, u32 length_bytes)
अणु
	u32 *dw_ptr;
	u32 i, length_dw;

	अगर (bios == शून्य)
		वापस false;
	अगर (length_bytes == 0)
		वापस false;
	/* APU vbios image is part of sbios image */
	अगर (adev->flags & AMD_IS_APU)
		वापस false;

	dw_ptr = (u32 *)bios;
	length_dw = ALIGN(length_bytes, 4) / 4;
	/* set rom index to 0 */
	WREG32(mmROM_INDEX, 0);
	क्रम (i = 0; i < length_dw; i++)
		dw_ptr[i] = RREG32(mmROM_DATA);

	वापस true;
पूर्ण

अटल व्योम si_set_clk_bypass_mode(काष्ठा amdgpu_device *adev)
अणु
	u32 पंचांगp, i;

	पंचांगp = RREG32(CG_SPLL_FUNC_CNTL);
	पंचांगp |= SPLL_BYPASS_EN;
	WREG32(CG_SPLL_FUNC_CNTL, पंचांगp);

	पंचांगp = RREG32(CG_SPLL_FUNC_CNTL_2);
	पंचांगp |= SPLL_CTLREQ_CHG;
	WREG32(CG_SPLL_FUNC_CNTL_2, पंचांगp);

	क्रम (i = 0; i < adev->usec_समयout; i++) अणु
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

अटल व्योम si_spll_घातerकरोwn(काष्ठा amdgpu_device *adev)
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

अटल पूर्णांक si_gpu_pci_config_reset(काष्ठा amdgpu_device *adev)
अणु
	u32 i;
	पूर्णांक r = -EINVAL;

	amdgpu_atombios_scratch_regs_engine_hung(adev, true);

	/* set mclk/sclk to bypass */
	si_set_clk_bypass_mode(adev);
	/* घातerकरोwn spll */
	si_spll_घातerकरोwn(adev);
	/* disable BM */
	pci_clear_master(adev->pdev);
	/* reset */
	amdgpu_device_pci_config_reset(adev);

	udelay(100);

	/* रुको क्रम asic to come out of reset */
	क्रम (i = 0; i < adev->usec_समयout; i++) अणु
		अगर (RREG32(mmCONFIG_MEMSIZE) != 0xffffffff) अणु
			/* enable BM */
			pci_set_master(adev->pdev);
			adev->has_hw_reset = true;
			r = 0;
			अवरोध;
		पूर्ण
		udelay(1);
	पूर्ण
	amdgpu_atombios_scratch_regs_engine_hung(adev, false);

	वापस r;
पूर्ण

अटल bool si_asic_supports_baco(काष्ठा amdgpu_device *adev)
अणु
	वापस false;
पूर्ण

अटल क्रमागत amd_reset_method
si_asic_reset_method(काष्ठा amdgpu_device *adev)
अणु
	अगर (amdgpu_reset_method == AMD_RESET_METHOD_PCI)
		वापस amdgpu_reset_method;
	अन्यथा अगर (amdgpu_reset_method != AMD_RESET_METHOD_LEGACY &&
		 amdgpu_reset_method != -1)
		dev_warn(adev->dev, "Specified reset method:%d isn't supported, using AUTO instead.\n",
			 amdgpu_reset_method);

	वापस AMD_RESET_METHOD_LEGACY;
पूर्ण

अटल पूर्णांक si_asic_reset(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक r;

	चयन (si_asic_reset_method(adev)) अणु
	हाल AMD_RESET_METHOD_PCI:
		dev_info(adev->dev, "PCI reset\n");
		r = amdgpu_device_pci_reset(adev);
		अवरोध;
	शेष:
		dev_info(adev->dev, "PCI CONFIG reset\n");
		r = si_gpu_pci_config_reset(adev);
		अवरोध;
	पूर्ण

	वापस r;
पूर्ण

अटल u32 si_get_config_memsize(काष्ठा amdgpu_device *adev)
अणु
	वापस RREG32(mmCONFIG_MEMSIZE);
पूर्ण

अटल व्योम si_vga_set_state(काष्ठा amdgpu_device *adev, bool state)
अणु
	uपूर्णांक32_t temp;

	temp = RREG32(CONFIG_CNTL);
	अगर (!state) अणु
		temp &= ~(1<<0);
		temp |= (1<<1);
	पूर्ण अन्यथा अणु
		temp &= ~(1<<1);
	पूर्ण
	WREG32(CONFIG_CNTL, temp);
पूर्ण

अटल u32 si_get_xclk(काष्ठा amdgpu_device *adev)
अणु
	u32 reference_घड़ी = adev->घड़ी.spll.reference_freq;
	u32 पंचांगp;

	पंचांगp = RREG32(CG_CLKPIN_CNTL_2);
	अगर (पंचांगp & MUX_TCLK_TO_XCLK)
		वापस TCLK;

	पंचांगp = RREG32(CG_CLKPIN_CNTL);
	अगर (पंचांगp & XTALIN_DIVIDE)
		वापस reference_घड़ी / 4;

	वापस reference_घड़ी;
पूर्ण

अटल व्योम si_flush_hdp(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_ring *ring)
अणु
	अगर (!ring || !ring->funcs->emit_wreg) अणु
		WREG32(mmHDP_MEM_COHERENCY_FLUSH_CNTL, 1);
		RREG32(mmHDP_MEM_COHERENCY_FLUSH_CNTL);
	पूर्ण अन्यथा अणु
		amdgpu_ring_emit_wreg(ring, mmHDP_MEM_COHERENCY_FLUSH_CNTL, 1);
	पूर्ण
पूर्ण

अटल व्योम si_invalidate_hdp(काष्ठा amdgpu_device *adev,
			      काष्ठा amdgpu_ring *ring)
अणु
	अगर (!ring || !ring->funcs->emit_wreg) अणु
		WREG32(mmHDP_DEBUG0, 1);
		RREG32(mmHDP_DEBUG0);
	पूर्ण अन्यथा अणु
		amdgpu_ring_emit_wreg(ring, mmHDP_DEBUG0, 1);
	पूर्ण
पूर्ण

अटल bool si_need_full_reset(काष्ठा amdgpu_device *adev)
अणु
	/* change this when we support soft reset */
	वापस true;
पूर्ण

अटल bool si_need_reset_on_init(काष्ठा amdgpu_device *adev)
अणु
	वापस false;
पूर्ण

अटल पूर्णांक si_get_pcie_lanes(काष्ठा amdgpu_device *adev)
अणु
	u32 link_width_cntl;

	अगर (adev->flags & AMD_IS_APU)
		वापस 0;

	link_width_cntl = RREG32_PCIE_PORT(PCIE_LC_LINK_WIDTH_CNTL);

	चयन ((link_width_cntl & LC_LINK_WIDTH_RD_MASK) >> LC_LINK_WIDTH_RD_SHIFT) अणु
	हाल LC_LINK_WIDTH_X1:
		वापस 1;
	हाल LC_LINK_WIDTH_X2:
		वापस 2;
	हाल LC_LINK_WIDTH_X4:
		वापस 4;
	हाल LC_LINK_WIDTH_X8:
		वापस 8;
	हाल LC_LINK_WIDTH_X0:
	हाल LC_LINK_WIDTH_X16:
	शेष:
		वापस 16;
	पूर्ण
पूर्ण

अटल व्योम si_set_pcie_lanes(काष्ठा amdgpu_device *adev, पूर्णांक lanes)
अणु
	u32 link_width_cntl, mask;

	अगर (adev->flags & AMD_IS_APU)
		वापस;

	चयन (lanes) अणु
	हाल 0:
		mask = LC_LINK_WIDTH_X0;
		अवरोध;
	हाल 1:
		mask = LC_LINK_WIDTH_X1;
		अवरोध;
	हाल 2:
		mask = LC_LINK_WIDTH_X2;
		अवरोध;
	हाल 4:
		mask = LC_LINK_WIDTH_X4;
		अवरोध;
	हाल 8:
		mask = LC_LINK_WIDTH_X8;
		अवरोध;
	हाल 16:
		mask = LC_LINK_WIDTH_X16;
		अवरोध;
	शेष:
		DRM_ERROR("invalid pcie lane request: %d\n", lanes);
		वापस;
	पूर्ण

	link_width_cntl = RREG32_PCIE_PORT(PCIE_LC_LINK_WIDTH_CNTL);
	link_width_cntl &= ~LC_LINK_WIDTH_MASK;
	link_width_cntl |= mask << LC_LINK_WIDTH_SHIFT;
	link_width_cntl |= (LC_RECONFIG_NOW |
			    LC_RECONFIG_ARC_MISSING_ESCAPE);

	WREG32_PCIE_PORT(PCIE_LC_LINK_WIDTH_CNTL, link_width_cntl);
पूर्ण

अटल व्योम si_get_pcie_usage(काष्ठा amdgpu_device *adev, uपूर्णांक64_t *count0,
			      uपूर्णांक64_t *count1)
अणु
	uपूर्णांक32_t perfctr = 0;
	uपूर्णांक64_t cnt0_of, cnt1_of;
	पूर्णांक पंचांगp;

	/* This reports 0 on APUs, so वापस to aव्योम writing/पढ़ोing रेजिस्टरs
	 * that may or may not be dअगरferent from their GPU counterparts
	 */
	अगर (adev->flags & AMD_IS_APU)
		वापस;

	/* Set the 2 events that we wish to watch, defined above */
	/* Reg 40 is # received msgs, Reg 104 is # of posted requests sent */
	perfctr = REG_SET_FIELD(perfctr, PCIE_PERF_CNTL_TXCLK, EVENT0_SEL, 40);
	perfctr = REG_SET_FIELD(perfctr, PCIE_PERF_CNTL_TXCLK, EVENT1_SEL, 104);

	/* Write to enable desired perf counters */
	WREG32_PCIE(ixPCIE_PERF_CNTL_TXCLK, perfctr);
	/* Zero out and enable the perf counters
	 * Write 0x5:
	 * Bit 0 = Start all counters(1)
	 * Bit 2 = Global counter reset enable(1)
	 */
	WREG32_PCIE(ixPCIE_PERF_COUNT_CNTL, 0x00000005);

	msleep(1000);

	/* Load the shaकरोw and disable the perf counters
	 * Write 0x2:
	 * Bit 0 = Stop counters(0)
	 * Bit 1 = Load the shaकरोw counters(1)
	 */
	WREG32_PCIE(ixPCIE_PERF_COUNT_CNTL, 0x00000002);

	/* Read रेजिस्टर values to get any >32bit overflow */
	पंचांगp = RREG32_PCIE(ixPCIE_PERF_CNTL_TXCLK);
	cnt0_of = REG_GET_FIELD(पंचांगp, PCIE_PERF_CNTL_TXCLK, COUNTER0_UPPER);
	cnt1_of = REG_GET_FIELD(पंचांगp, PCIE_PERF_CNTL_TXCLK, COUNTER1_UPPER);

	/* Get the values and add the overflow */
	*count0 = RREG32_PCIE(ixPCIE_PERF_COUNT0_TXCLK) | (cnt0_of << 32);
	*count1 = RREG32_PCIE(ixPCIE_PERF_COUNT1_TXCLK) | (cnt1_of << 32);
पूर्ण

अटल uपूर्णांक64_t si_get_pcie_replay_count(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक64_t nak_r, nak_g;

	/* Get the number of NAKs received and generated */
	nak_r = RREG32_PCIE(ixPCIE_RX_NUM_NAK);
	nak_g = RREG32_PCIE(ixPCIE_RX_NUM_NAK_GENERATED);

	/* Add the total number of NAKs, i.e the number of replays */
	वापस (nak_r + nak_g);
पूर्ण

अटल पूर्णांक si_uvd_send_upll_ctlreq(काष्ठा amdgpu_device *adev,
				   अचिन्हित cg_upll_func_cntl)
अणु
	अचिन्हित i;

	/* Make sure UPLL_CTLREQ is deनिश्चितed */
	WREG32_P(cg_upll_func_cntl, 0, ~UPLL_CTLREQ_MASK);

	mdelay(10);

	/* Assert UPLL_CTLREQ */
	WREG32_P(cg_upll_func_cntl, UPLL_CTLREQ_MASK, ~UPLL_CTLREQ_MASK);

	/* Wait क्रम CTLACK and CTLACK2 to get निश्चितed */
	क्रम (i = 0; i < SI_MAX_CTLACKS_ASSERTION_WAIT; ++i) अणु
		uपूर्णांक32_t mask = UPLL_CTLACK_MASK | UPLL_CTLACK2_MASK;

		अगर ((RREG32(cg_upll_func_cntl) & mask) == mask)
			अवरोध;
		mdelay(10);
	पूर्ण

	/* Deनिश्चित UPLL_CTLREQ */
	WREG32_P(cg_upll_func_cntl, 0, ~UPLL_CTLREQ_MASK);

	अगर (i == SI_MAX_CTLACKS_ASSERTION_WAIT) अणु
		DRM_ERROR("Timeout setting UVD clocks!\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित si_uvd_calc_upll_post_भाग(अचिन्हित vco_freq,
					  अचिन्हित target_freq,
					  अचिन्हित pd_min,
					  अचिन्हित pd_even)
अणु
	अचिन्हित post_भाग = vco_freq / target_freq;

	/* Adjust to post भागider minimum value */
	अगर (post_भाग < pd_min)
		post_भाग = pd_min;

	/* We alway need a frequency less than or equal the target */
	अगर ((vco_freq / post_भाग) > target_freq)
		post_भाग += 1;

	/* Post भागiders above a certain value must be even */
	अगर (post_भाग > pd_even && post_भाग % 2)
		post_भाग += 1;

	वापस post_भाग;
पूर्ण

/**
 * si_calc_upll_भागiders - calc UPLL घड़ी भागiders
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @vclk: wanted VCLK
 * @dclk: wanted DCLK
 * @vco_min: minimum VCO frequency
 * @vco_max: maximum VCO frequency
 * @fb_factor: factor to multiply vco freq with
 * @fb_mask: limit and biपंचांगask क्रम feedback भागider
 * @pd_min: post भागider minimum
 * @pd_max: post भागider maximum
 * @pd_even: post भागider must be even above this value
 * @optimal_fb_भाग: resulting feedback भागider
 * @optimal_vclk_भाग: resulting vclk post भागider
 * @optimal_dclk_भाग: resulting dclk post भागider
 *
 * Calculate भागiders क्रम UVDs UPLL (except APUs).
 * Returns zero on success; -EINVAL on error.
 */
अटल पूर्णांक si_calc_upll_भागiders(काष्ठा amdgpu_device *adev,
				 अचिन्हित vclk, अचिन्हित dclk,
				 अचिन्हित vco_min, अचिन्हित vco_max,
				 अचिन्हित fb_factor, अचिन्हित fb_mask,
				 अचिन्हित pd_min, अचिन्हित pd_max,
				 अचिन्हित pd_even,
				 अचिन्हित *optimal_fb_भाग,
				 अचिन्हित *optimal_vclk_भाग,
				 अचिन्हित *optimal_dclk_भाग)
अणु
	अचिन्हित vco_freq, ref_freq = adev->घड़ी.spll.reference_freq;

	/* Start off with something large */
	अचिन्हित optimal_score = ~0;

	/* Loop through vco from low to high */
	vco_min = max(max(vco_min, vclk), dclk);
	क्रम (vco_freq = vco_min; vco_freq <= vco_max; vco_freq += 100) अणु
		uपूर्णांक64_t fb_भाग = (uपूर्णांक64_t)vco_freq * fb_factor;
		अचिन्हित vclk_भाग, dclk_भाग, score;

		करो_भाग(fb_भाग, ref_freq);

		/* fb भाग out of range ? */
		अगर (fb_भाग > fb_mask)
			अवरोध; /* It can oly get worse */

		fb_भाग &= fb_mask;

		/* Calc vclk भागider with current vco freq */
		vclk_भाग = si_uvd_calc_upll_post_भाग(vco_freq, vclk,
						     pd_min, pd_even);
		अगर (vclk_भाग > pd_max)
			अवरोध; /* vco is too big, it has to stop */

		/* Calc dclk भागider with current vco freq */
		dclk_भाग = si_uvd_calc_upll_post_भाग(vco_freq, dclk,
						     pd_min, pd_even);
		अगर (dclk_भाग > pd_max)
			अवरोध; /* vco is too big, it has to stop */

		/* Calc score with current vco freq */
		score = vclk - (vco_freq / vclk_भाग) + dclk - (vco_freq / dclk_भाग);

		/* Determine अगर this vco setting is better than current optimal settings */
		अगर (score < optimal_score) अणु
			*optimal_fb_भाग = fb_भाग;
			*optimal_vclk_भाग = vclk_भाग;
			*optimal_dclk_भाग = dclk_भाग;
			optimal_score = score;
			अगर (optimal_score == 0)
				अवरोध; /* It can't get better than this */
		पूर्ण
	पूर्ण

	/* Did we found a valid setup ? */
	अगर (optimal_score == ~0)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक si_set_uvd_घड़ीs(काष्ठा amdgpu_device *adev, u32 vclk, u32 dclk)
अणु
	अचिन्हित fb_भाग = 0, vclk_भाग = 0, dclk_भाग = 0;
	पूर्णांक r;

	/* Bypass vclk and dclk with bclk */
	WREG32_P(CG_UPLL_FUNC_CNTL_2,
		 VCLK_SRC_SEL(1) | DCLK_SRC_SEL(1),
		 ~(VCLK_SRC_SEL_MASK | DCLK_SRC_SEL_MASK));

	/* Put PLL in bypass mode */
	WREG32_P(CG_UPLL_FUNC_CNTL, UPLL_BYPASS_EN_MASK, ~UPLL_BYPASS_EN_MASK);

	अगर (!vclk || !dclk) अणु
		/* Keep the Bypass mode */
		वापस 0;
	पूर्ण

	r = si_calc_upll_भागiders(adev, vclk, dclk, 125000, 250000,
				  16384, 0x03FFFFFF, 0, 128, 5,
				  &fb_भाग, &vclk_भाग, &dclk_भाग);
	अगर (r)
		वापस r;

	/* Set RESET_ANTI_MUX to 0 */
	WREG32_P(CG_UPLL_FUNC_CNTL_5, 0, ~RESET_ANTI_MUX_MASK);

	/* Set VCO_MODE to 1 */
	WREG32_P(CG_UPLL_FUNC_CNTL, UPLL_VCO_MODE_MASK, ~UPLL_VCO_MODE_MASK);

	/* Disable sleep mode */
	WREG32_P(CG_UPLL_FUNC_CNTL, 0, ~UPLL_SLEEP_MASK);

	/* Deनिश्चित UPLL_RESET */
	WREG32_P(CG_UPLL_FUNC_CNTL, 0, ~UPLL_RESET_MASK);

	mdelay(1);

	r = si_uvd_send_upll_ctlreq(adev, CG_UPLL_FUNC_CNTL);
	अगर (r)
		वापस r;

	/* Assert UPLL_RESET again */
	WREG32_P(CG_UPLL_FUNC_CNTL, UPLL_RESET_MASK, ~UPLL_RESET_MASK);

	/* Disable spपढ़ो spectrum. */
	WREG32_P(CG_UPLL_SPREAD_SPECTRUM, 0, ~SSEN_MASK);

	/* Set feedback भागider */
	WREG32_P(CG_UPLL_FUNC_CNTL_3, UPLL_FB_DIV(fb_भाग), ~UPLL_FB_DIV_MASK);

	/* Set ref भागider to 0 */
	WREG32_P(CG_UPLL_FUNC_CNTL, 0, ~UPLL_REF_DIV_MASK);

	अगर (fb_भाग < 307200)
		WREG32_P(CG_UPLL_FUNC_CNTL_4, 0, ~UPLL_SPARE_ISPARE9);
	अन्यथा
		WREG32_P(CG_UPLL_FUNC_CNTL_4,
			 UPLL_SPARE_ISPARE9,
			 ~UPLL_SPARE_ISPARE9);

	/* Set PDIV_A and PDIV_B */
	WREG32_P(CG_UPLL_FUNC_CNTL_2,
		 UPLL_PDIV_A(vclk_भाग) | UPLL_PDIV_B(dclk_भाग),
		 ~(UPLL_PDIV_A_MASK | UPLL_PDIV_B_MASK));

	/* Give the PLL some समय to settle */
	mdelay(15);

	/* Deनिश्चित PLL_RESET */
	WREG32_P(CG_UPLL_FUNC_CNTL, 0, ~UPLL_RESET_MASK);

	mdelay(15);

	/* Switch from bypass mode to normal mode */
	WREG32_P(CG_UPLL_FUNC_CNTL, 0, ~UPLL_BYPASS_EN_MASK);

	r = si_uvd_send_upll_ctlreq(adev, CG_UPLL_FUNC_CNTL);
	अगर (r)
		वापस r;

	/* Switch VCLK and DCLK selection */
	WREG32_P(CG_UPLL_FUNC_CNTL_2,
		 VCLK_SRC_SEL(2) | DCLK_SRC_SEL(2),
		 ~(VCLK_SRC_SEL_MASK | DCLK_SRC_SEL_MASK));

	mdelay(100);

	वापस 0;
पूर्ण

अटल पूर्णांक si_vce_send_vcepll_ctlreq(काष्ठा amdgpu_device *adev)
अणु
	अचिन्हित i;

	/* Make sure VCEPLL_CTLREQ is deनिश्चितed */
	WREG32_SMC_P(CG_VCEPLL_FUNC_CNTL, 0, ~UPLL_CTLREQ_MASK);

	mdelay(10);

	/* Assert UPLL_CTLREQ */
	WREG32_SMC_P(CG_VCEPLL_FUNC_CNTL, UPLL_CTLREQ_MASK, ~UPLL_CTLREQ_MASK);

	/* Wait क्रम CTLACK and CTLACK2 to get निश्चितed */
	क्रम (i = 0; i < SI_MAX_CTLACKS_ASSERTION_WAIT; ++i) अणु
		uपूर्णांक32_t mask = UPLL_CTLACK_MASK | UPLL_CTLACK2_MASK;

		अगर ((RREG32_SMC(CG_VCEPLL_FUNC_CNTL) & mask) == mask)
			अवरोध;
		mdelay(10);
	पूर्ण

	/* Deनिश्चित UPLL_CTLREQ */
	WREG32_SMC_P(CG_VCEPLL_FUNC_CNTL, 0, ~UPLL_CTLREQ_MASK);

	अगर (i == SI_MAX_CTLACKS_ASSERTION_WAIT) अणु
		DRM_ERROR("Timeout setting UVD clocks!\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक si_set_vce_घड़ीs(काष्ठा amdgpu_device *adev, u32 evclk, u32 ecclk)
अणु
	अचिन्हित fb_भाग = 0, evclk_भाग = 0, ecclk_भाग = 0;
	पूर्णांक r;

	/* Bypass evclk and ecclk with bclk */
	WREG32_SMC_P(CG_VCEPLL_FUNC_CNTL_2,
		     EVCLK_SRC_SEL(1) | ECCLK_SRC_SEL(1),
		     ~(EVCLK_SRC_SEL_MASK | ECCLK_SRC_SEL_MASK));

	/* Put PLL in bypass mode */
	WREG32_SMC_P(CG_VCEPLL_FUNC_CNTL, VCEPLL_BYPASS_EN_MASK,
		     ~VCEPLL_BYPASS_EN_MASK);

	अगर (!evclk || !ecclk) अणु
		/* Keep the Bypass mode, put PLL to sleep */
		WREG32_SMC_P(CG_VCEPLL_FUNC_CNTL, VCEPLL_SLEEP_MASK,
			     ~VCEPLL_SLEEP_MASK);
		वापस 0;
	पूर्ण

	r = si_calc_upll_भागiders(adev, evclk, ecclk, 125000, 250000,
				  16384, 0x03FFFFFF, 0, 128, 5,
				  &fb_भाग, &evclk_भाग, &ecclk_भाग);
	अगर (r)
		वापस r;

	/* Set RESET_ANTI_MUX to 0 */
	WREG32_SMC_P(CG_VCEPLL_FUNC_CNTL_5, 0, ~RESET_ANTI_MUX_MASK);

	/* Set VCO_MODE to 1 */
	WREG32_SMC_P(CG_VCEPLL_FUNC_CNTL, VCEPLL_VCO_MODE_MASK,
		     ~VCEPLL_VCO_MODE_MASK);

	/* Toggle VCEPLL_SLEEP to 1 then back to 0 */
	WREG32_SMC_P(CG_VCEPLL_FUNC_CNTL, VCEPLL_SLEEP_MASK,
		     ~VCEPLL_SLEEP_MASK);
	WREG32_SMC_P(CG_VCEPLL_FUNC_CNTL, 0, ~VCEPLL_SLEEP_MASK);

	/* Deनिश्चित VCEPLL_RESET */
	WREG32_SMC_P(CG_VCEPLL_FUNC_CNTL, 0, ~VCEPLL_RESET_MASK);

	mdelay(1);

	r = si_vce_send_vcepll_ctlreq(adev);
	अगर (r)
		वापस r;

	/* Assert VCEPLL_RESET again */
	WREG32_SMC_P(CG_VCEPLL_FUNC_CNTL, VCEPLL_RESET_MASK, ~VCEPLL_RESET_MASK);

	/* Disable spपढ़ो spectrum. */
	WREG32_SMC_P(CG_VCEPLL_SPREAD_SPECTRUM, 0, ~SSEN_MASK);

	/* Set feedback भागider */
	WREG32_SMC_P(CG_VCEPLL_FUNC_CNTL_3,
		     VCEPLL_FB_DIV(fb_भाग),
		     ~VCEPLL_FB_DIV_MASK);

	/* Set ref भागider to 0 */
	WREG32_SMC_P(CG_VCEPLL_FUNC_CNTL, 0, ~VCEPLL_REF_DIV_MASK);

	/* Set PDIV_A and PDIV_B */
	WREG32_SMC_P(CG_VCEPLL_FUNC_CNTL_2,
		     VCEPLL_PDIV_A(evclk_भाग) | VCEPLL_PDIV_B(ecclk_भाग),
		     ~(VCEPLL_PDIV_A_MASK | VCEPLL_PDIV_B_MASK));

	/* Give the PLL some समय to settle */
	mdelay(15);

	/* Deनिश्चित PLL_RESET */
	WREG32_SMC_P(CG_VCEPLL_FUNC_CNTL, 0, ~VCEPLL_RESET_MASK);

	mdelay(15);

	/* Switch from bypass mode to normal mode */
	WREG32_SMC_P(CG_VCEPLL_FUNC_CNTL, 0, ~VCEPLL_BYPASS_EN_MASK);

	r = si_vce_send_vcepll_ctlreq(adev);
	अगर (r)
		वापस r;

	/* Switch VCLK and DCLK selection */
	WREG32_SMC_P(CG_VCEPLL_FUNC_CNTL_2,
		     EVCLK_SRC_SEL(16) | ECCLK_SRC_SEL(16),
		     ~(EVCLK_SRC_SEL_MASK | ECCLK_SRC_SEL_MASK));

	mdelay(100);

	वापस 0;
पूर्ण

अटल व्योम si_pre_asic_init(काष्ठा amdgpu_device *adev)
अणु
पूर्ण

अटल स्थिर काष्ठा amdgpu_asic_funcs si_asic_funcs =
अणु
	.पढ़ो_disabled_bios = &si_पढ़ो_disabled_bios,
	.पढ़ो_bios_from_rom = &si_पढ़ो_bios_from_rom,
	.पढ़ो_रेजिस्टर = &si_पढ़ो_रेजिस्टर,
	.reset = &si_asic_reset,
	.reset_method = &si_asic_reset_method,
	.set_vga_state = &si_vga_set_state,
	.get_xclk = &si_get_xclk,
	.set_uvd_घड़ीs = &si_set_uvd_घड़ीs,
	.set_vce_घड़ीs = &si_set_vce_घड़ीs,
	.get_pcie_lanes = &si_get_pcie_lanes,
	.set_pcie_lanes = &si_set_pcie_lanes,
	.get_config_memsize = &si_get_config_memsize,
	.flush_hdp = &si_flush_hdp,
	.invalidate_hdp = &si_invalidate_hdp,
	.need_full_reset = &si_need_full_reset,
	.get_pcie_usage = &si_get_pcie_usage,
	.need_reset_on_init = &si_need_reset_on_init,
	.get_pcie_replay_count = &si_get_pcie_replay_count,
	.supports_baco = &si_asic_supports_baco,
	.pre_asic_init = &si_pre_asic_init,
	.query_video_codecs = &si_query_video_codecs,
पूर्ण;

अटल uपूर्णांक32_t si_get_rev_id(काष्ठा amdgpu_device *adev)
अणु
	वापस (RREG32(CC_DRM_ID_STRAPS) & CC_DRM_ID_STRAPS__ATI_REV_ID_MASK)
		>> CC_DRM_ID_STRAPS__ATI_REV_ID__SHIFT;
पूर्ण

अटल पूर्णांक si_common_early_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	adev->smc_rreg = &si_smc_rreg;
	adev->smc_wreg = &si_smc_wreg;
	adev->pcie_rreg = &si_pcie_rreg;
	adev->pcie_wreg = &si_pcie_wreg;
	adev->pciep_rreg = &si_pciep_rreg;
	adev->pciep_wreg = &si_pciep_wreg;
	adev->uvd_ctx_rreg = si_uvd_ctx_rreg;
	adev->uvd_ctx_wreg = si_uvd_ctx_wreg;
	adev->didt_rreg = शून्य;
	adev->didt_wreg = शून्य;

	adev->asic_funcs = &si_asic_funcs;

	adev->rev_id = si_get_rev_id(adev);
	adev->बाह्यal_rev_id = 0xFF;
	चयन (adev->asic_type) अणु
	हाल CHIP_TAHITI:
		adev->cg_flags =
			AMD_CG_SUPPORT_GFX_MGCG |
			AMD_CG_SUPPORT_GFX_MGLS |
			/*AMD_CG_SUPPORT_GFX_CGCG |*/
			AMD_CG_SUPPORT_GFX_CGLS |
			AMD_CG_SUPPORT_GFX_CGTS |
			AMD_CG_SUPPORT_GFX_CP_LS |
			AMD_CG_SUPPORT_MC_MGCG |
			AMD_CG_SUPPORT_SDMA_MGCG |
			AMD_CG_SUPPORT_BIF_LS |
			AMD_CG_SUPPORT_VCE_MGCG |
			AMD_CG_SUPPORT_UVD_MGCG |
			AMD_CG_SUPPORT_HDP_LS |
			AMD_CG_SUPPORT_HDP_MGCG;
		adev->pg_flags = 0;
		adev->बाह्यal_rev_id = (adev->rev_id == 0) ? 1 :
					(adev->rev_id == 1) ? 5 : 6;
		अवरोध;
	हाल CHIP_PITCAIRN:
		adev->cg_flags =
			AMD_CG_SUPPORT_GFX_MGCG |
			AMD_CG_SUPPORT_GFX_MGLS |
			/*AMD_CG_SUPPORT_GFX_CGCG |*/
			AMD_CG_SUPPORT_GFX_CGLS |
			AMD_CG_SUPPORT_GFX_CGTS |
			AMD_CG_SUPPORT_GFX_CP_LS |
			AMD_CG_SUPPORT_GFX_RLC_LS |
			AMD_CG_SUPPORT_MC_LS |
			AMD_CG_SUPPORT_MC_MGCG |
			AMD_CG_SUPPORT_SDMA_MGCG |
			AMD_CG_SUPPORT_BIF_LS |
			AMD_CG_SUPPORT_VCE_MGCG |
			AMD_CG_SUPPORT_UVD_MGCG |
			AMD_CG_SUPPORT_HDP_LS |
			AMD_CG_SUPPORT_HDP_MGCG;
		adev->pg_flags = 0;
		adev->बाह्यal_rev_id = adev->rev_id + 20;
		अवरोध;

	हाल CHIP_VERDE:
		adev->cg_flags =
			AMD_CG_SUPPORT_GFX_MGCG |
			AMD_CG_SUPPORT_GFX_MGLS |
			AMD_CG_SUPPORT_GFX_CGLS |
			AMD_CG_SUPPORT_GFX_CGTS |
			AMD_CG_SUPPORT_GFX_CGTS_LS |
			AMD_CG_SUPPORT_GFX_CP_LS |
			AMD_CG_SUPPORT_MC_LS |
			AMD_CG_SUPPORT_MC_MGCG |
			AMD_CG_SUPPORT_SDMA_MGCG |
			AMD_CG_SUPPORT_SDMA_LS |
			AMD_CG_SUPPORT_BIF_LS |
			AMD_CG_SUPPORT_VCE_MGCG |
			AMD_CG_SUPPORT_UVD_MGCG |
			AMD_CG_SUPPORT_HDP_LS |
			AMD_CG_SUPPORT_HDP_MGCG;
		adev->pg_flags = 0;
		//???
		adev->बाह्यal_rev_id = adev->rev_id + 40;
		अवरोध;
	हाल CHIP_OLAND:
		adev->cg_flags =
			AMD_CG_SUPPORT_GFX_MGCG |
			AMD_CG_SUPPORT_GFX_MGLS |
			/*AMD_CG_SUPPORT_GFX_CGCG |*/
			AMD_CG_SUPPORT_GFX_CGLS |
			AMD_CG_SUPPORT_GFX_CGTS |
			AMD_CG_SUPPORT_GFX_CP_LS |
			AMD_CG_SUPPORT_GFX_RLC_LS |
			AMD_CG_SUPPORT_MC_LS |
			AMD_CG_SUPPORT_MC_MGCG |
			AMD_CG_SUPPORT_SDMA_MGCG |
			AMD_CG_SUPPORT_BIF_LS |
			AMD_CG_SUPPORT_UVD_MGCG |
			AMD_CG_SUPPORT_HDP_LS |
			AMD_CG_SUPPORT_HDP_MGCG;
		adev->pg_flags = 0;
		adev->बाह्यal_rev_id = 60;
		अवरोध;
	हाल CHIP_HAIन_अंक:
		adev->cg_flags =
			AMD_CG_SUPPORT_GFX_MGCG |
			AMD_CG_SUPPORT_GFX_MGLS |
			/*AMD_CG_SUPPORT_GFX_CGCG |*/
			AMD_CG_SUPPORT_GFX_CGLS |
			AMD_CG_SUPPORT_GFX_CGTS |
			AMD_CG_SUPPORT_GFX_CP_LS |
			AMD_CG_SUPPORT_GFX_RLC_LS |
			AMD_CG_SUPPORT_MC_LS |
			AMD_CG_SUPPORT_MC_MGCG |
			AMD_CG_SUPPORT_SDMA_MGCG |
			AMD_CG_SUPPORT_BIF_LS |
			AMD_CG_SUPPORT_HDP_LS |
			AMD_CG_SUPPORT_HDP_MGCG;
		adev->pg_flags = 0;
		adev->बाह्यal_rev_id = 70;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक si_common_sw_init(व्योम *handle)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक si_common_sw_fini(व्योम *handle)
अणु
	वापस 0;
पूर्ण


अटल व्योम si_init_golden_रेजिस्टरs(काष्ठा amdgpu_device *adev)
अणु
	चयन (adev->asic_type) अणु
	हाल CHIP_TAHITI:
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							tahiti_golden_रेजिस्टरs,
							ARRAY_SIZE(tahiti_golden_रेजिस्टरs));
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							tahiti_golden_rlc_रेजिस्टरs,
							ARRAY_SIZE(tahiti_golden_rlc_रेजिस्टरs));
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							tahiti_mgcg_cgcg_init,
							ARRAY_SIZE(tahiti_mgcg_cgcg_init));
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							tahiti_golden_रेजिस्टरs2,
							ARRAY_SIZE(tahiti_golden_रेजिस्टरs2));
		अवरोध;
	हाल CHIP_PITCAIRN:
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							pitcairn_golden_रेजिस्टरs,
							ARRAY_SIZE(pitcairn_golden_रेजिस्टरs));
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							pitcairn_golden_rlc_रेजिस्टरs,
							ARRAY_SIZE(pitcairn_golden_rlc_रेजिस्टरs));
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							pitcairn_mgcg_cgcg_init,
							ARRAY_SIZE(pitcairn_mgcg_cgcg_init));
		अवरोध;
	हाल CHIP_VERDE:
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							verde_golden_रेजिस्टरs,
							ARRAY_SIZE(verde_golden_रेजिस्टरs));
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							verde_golden_rlc_रेजिस्टरs,
							ARRAY_SIZE(verde_golden_rlc_रेजिस्टरs));
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							verde_mgcg_cgcg_init,
							ARRAY_SIZE(verde_mgcg_cgcg_init));
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							verde_pg_init,
							ARRAY_SIZE(verde_pg_init));
		अवरोध;
	हाल CHIP_OLAND:
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							oland_golden_रेजिस्टरs,
							ARRAY_SIZE(oland_golden_रेजिस्टरs));
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							oland_golden_rlc_रेजिस्टरs,
							ARRAY_SIZE(oland_golden_rlc_रेजिस्टरs));
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							oland_mgcg_cgcg_init,
							ARRAY_SIZE(oland_mgcg_cgcg_init));
		अवरोध;
	हाल CHIP_HAIन_अंक:
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							hainan_golden_रेजिस्टरs,
							ARRAY_SIZE(hainan_golden_रेजिस्टरs));
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							hainan_golden_रेजिस्टरs2,
							ARRAY_SIZE(hainan_golden_रेजिस्टरs2));
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							hainan_mgcg_cgcg_init,
							ARRAY_SIZE(hainan_mgcg_cgcg_init));
		अवरोध;


	शेष:
		BUG();
	पूर्ण
पूर्ण

अटल व्योम si_pcie_gen3_enable(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा pci_dev *root = adev->pdev->bus->self;
	u32 speed_cntl, current_data_rate;
	पूर्णांक i;
	u16 पंचांगp16;

	अगर (pci_is_root_bus(adev->pdev->bus))
		वापस;

	अगर (amdgpu_pcie_gen2 == 0)
		वापस;

	अगर (adev->flags & AMD_IS_APU)
		वापस;

	अगर (!(adev->pm.pcie_gen_mask & (CAIL_PCIE_LINK_SPEED_SUPPORT_GEN2 |
					CAIL_PCIE_LINK_SPEED_SUPPORT_GEN3)))
		वापस;

	speed_cntl = RREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL);
	current_data_rate = (speed_cntl & LC_CURRENT_DATA_RATE_MASK) >>
		LC_CURRENT_DATA_RATE_SHIFT;
	अगर (adev->pm.pcie_gen_mask & CAIL_PCIE_LINK_SPEED_SUPPORT_GEN3) अणु
		अगर (current_data_rate == 2) अणु
			DRM_INFO("PCIE gen 3 link speeds already enabled\n");
			वापस;
		पूर्ण
		DRM_INFO("enabling PCIE gen 3 link speeds, disable with amdgpu.pcie_gen2=0\n");
	पूर्ण अन्यथा अगर (adev->pm.pcie_gen_mask & CAIL_PCIE_LINK_SPEED_SUPPORT_GEN2) अणु
		अगर (current_data_rate == 1) अणु
			DRM_INFO("PCIE gen 2 link speeds already enabled\n");
			वापस;
		पूर्ण
		DRM_INFO("enabling PCIE gen 2 link speeds, disable with amdgpu.pcie_gen2=0\n");
	पूर्ण

	अगर (!pci_is_pcie(root) || !pci_is_pcie(adev->pdev))
		वापस;

	अगर (adev->pm.pcie_gen_mask & CAIL_PCIE_LINK_SPEED_SUPPORT_GEN3) अणु
		अगर (current_data_rate != 2) अणु
			u16 bridge_cfg, gpu_cfg;
			u16 bridge_cfg2, gpu_cfg2;
			u32 max_lw, current_lw, पंचांगp;

			pcie_capability_पढ़ो_word(root, PCI_EXP_LNKCTL,
						  &bridge_cfg);
			pcie_capability_पढ़ो_word(adev->pdev, PCI_EXP_LNKCTL,
						  &gpu_cfg);

			पंचांगp16 = bridge_cfg | PCI_EXP_LNKCTL_HAWD;
			pcie_capability_ग_लिखो_word(root, PCI_EXP_LNKCTL, पंचांगp16);

			पंचांगp16 = gpu_cfg | PCI_EXP_LNKCTL_HAWD;
			pcie_capability_ग_लिखो_word(adev->pdev, PCI_EXP_LNKCTL,
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
				pcie_capability_पढ़ो_word(adev->pdev,
							  PCI_EXP_DEVSTA,
							  &पंचांगp16);
				अगर (पंचांगp16 & PCI_EXP_DEVSTA_TRPND)
					अवरोध;

				pcie_capability_पढ़ो_word(root, PCI_EXP_LNKCTL,
							  &bridge_cfg);
				pcie_capability_पढ़ो_word(adev->pdev,
							  PCI_EXP_LNKCTL,
							  &gpu_cfg);

				pcie_capability_पढ़ो_word(root, PCI_EXP_LNKCTL2,
							  &bridge_cfg2);
				pcie_capability_पढ़ो_word(adev->pdev,
							  PCI_EXP_LNKCTL2,
							  &gpu_cfg2);

				पंचांगp = RREG32_PCIE_PORT(PCIE_LC_CNTL4);
				पंचांगp |= LC_SET_QUIESCE;
				WREG32_PCIE_PORT(PCIE_LC_CNTL4, पंचांगp);

				पंचांगp = RREG32_PCIE_PORT(PCIE_LC_CNTL4);
				पंचांगp |= LC_REDO_EQ;
				WREG32_PCIE_PORT(PCIE_LC_CNTL4, पंचांगp);

				mdelay(100);

				pcie_capability_पढ़ो_word(root, PCI_EXP_LNKCTL,
							  &पंचांगp16);
				पंचांगp16 &= ~PCI_EXP_LNKCTL_HAWD;
				पंचांगp16 |= (bridge_cfg & PCI_EXP_LNKCTL_HAWD);
				pcie_capability_ग_लिखो_word(root, PCI_EXP_LNKCTL,
							   पंचांगp16);

				pcie_capability_पढ़ो_word(adev->pdev,
							  PCI_EXP_LNKCTL,
							  &पंचांगp16);
				पंचांगp16 &= ~PCI_EXP_LNKCTL_HAWD;
				पंचांगp16 |= (gpu_cfg & PCI_EXP_LNKCTL_HAWD);
				pcie_capability_ग_लिखो_word(adev->pdev,
							   PCI_EXP_LNKCTL,
							   पंचांगp16);

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

				pcie_capability_पढ़ो_word(adev->pdev,
							  PCI_EXP_LNKCTL2,
							  &पंचांगp16);
				पंचांगp16 &= ~(PCI_EXP_LNKCTL2_ENTER_COMP |
					   PCI_EXP_LNKCTL2_TX_MARGIN);
				पंचांगp16 |= (gpu_cfg2 &
					  (PCI_EXP_LNKCTL2_ENTER_COMP |
					   PCI_EXP_LNKCTL2_TX_MARGIN));
				pcie_capability_ग_लिखो_word(adev->pdev,
							   PCI_EXP_LNKCTL2,
							   पंचांगp16);

				पंचांगp = RREG32_PCIE_PORT(PCIE_LC_CNTL4);
				पंचांगp &= ~LC_SET_QUIESCE;
				WREG32_PCIE_PORT(PCIE_LC_CNTL4, पंचांगp);
			पूर्ण
		पूर्ण
	पूर्ण

	speed_cntl |= LC_FORCE_EN_SW_SPEED_CHANGE | LC_FORCE_DIS_HW_SPEED_CHANGE;
	speed_cntl &= ~LC_FORCE_DIS_SW_SPEED_CHANGE;
	WREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL, speed_cntl);

	pcie_capability_पढ़ो_word(adev->pdev, PCI_EXP_LNKCTL2, &पंचांगp16);
	पंचांगp16 &= ~PCI_EXP_LNKCTL2_TLS;

	अगर (adev->pm.pcie_gen_mask & CAIL_PCIE_LINK_SPEED_SUPPORT_GEN3)
		पंचांगp16 |= PCI_EXP_LNKCTL2_TLS_8_0GT; /* gen3 */
	अन्यथा अगर (adev->pm.pcie_gen_mask & CAIL_PCIE_LINK_SPEED_SUPPORT_GEN2)
		पंचांगp16 |= PCI_EXP_LNKCTL2_TLS_5_0GT; /* gen2 */
	अन्यथा
		पंचांगp16 |= PCI_EXP_LNKCTL2_TLS_2_5GT; /* gen1 */
	pcie_capability_ग_लिखो_word(adev->pdev, PCI_EXP_LNKCTL2, पंचांगp16);

	speed_cntl = RREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL);
	speed_cntl |= LC_INITIATE_LINK_SPEED_CHANGE;
	WREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL, speed_cntl);

	क्रम (i = 0; i < adev->usec_समयout; i++) अणु
		speed_cntl = RREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL);
		अगर ((speed_cntl & LC_INITIATE_LINK_SPEED_CHANGE) == 0)
			अवरोध;
		udelay(1);
	पूर्ण
पूर्ण

अटल अंतरभूत u32 si_pअगर_phy0_rreg(काष्ठा amdgpu_device *adev, u32 reg)
अणु
	अचिन्हित दीर्घ flags;
	u32 r;

	spin_lock_irqsave(&adev->pcie_idx_lock, flags);
	WREG32(EVERGREEN_PIF_PHY0_INDEX, ((reg) & 0xffff));
	r = RREG32(EVERGREEN_PIF_PHY0_DATA);
	spin_unlock_irqrestore(&adev->pcie_idx_lock, flags);
	वापस r;
पूर्ण

अटल अंतरभूत व्योम si_pअगर_phy0_wreg(काष्ठा amdgpu_device *adev, u32 reg, u32 v)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&adev->pcie_idx_lock, flags);
	WREG32(EVERGREEN_PIF_PHY0_INDEX, ((reg) & 0xffff));
	WREG32(EVERGREEN_PIF_PHY0_DATA, (v));
	spin_unlock_irqrestore(&adev->pcie_idx_lock, flags);
पूर्ण

अटल अंतरभूत u32 si_pअगर_phy1_rreg(काष्ठा amdgpu_device *adev, u32 reg)
अणु
	अचिन्हित दीर्घ flags;
	u32 r;

	spin_lock_irqsave(&adev->pcie_idx_lock, flags);
	WREG32(EVERGREEN_PIF_PHY1_INDEX, ((reg) & 0xffff));
	r = RREG32(EVERGREEN_PIF_PHY1_DATA);
	spin_unlock_irqrestore(&adev->pcie_idx_lock, flags);
	वापस r;
पूर्ण

अटल अंतरभूत व्योम si_pअगर_phy1_wreg(काष्ठा amdgpu_device *adev, u32 reg, u32 v)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&adev->pcie_idx_lock, flags);
	WREG32(EVERGREEN_PIF_PHY1_INDEX, ((reg) & 0xffff));
	WREG32(EVERGREEN_PIF_PHY1_DATA, (v));
	spin_unlock_irqrestore(&adev->pcie_idx_lock, flags);
पूर्ण
अटल व्योम si_program_aspm(काष्ठा amdgpu_device *adev)
अणु
	u32 data, orig;
	bool disable_l0s = false, disable_l1 = false, disable_plloff_in_l1 = false;
	bool disable_clkreq = false;

	अगर (amdgpu_aspm == 0)
		वापस;

	अगर (adev->flags & AMD_IS_APU)
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

			orig = data = si_pअगर_phy0_rreg(adev,PB0_PIF_PWRDOWN_0);
			data &= ~(PLL_POWER_STATE_IN_OFF_0_MASK | PLL_POWER_STATE_IN_TXS2_0_MASK);
			data |= PLL_POWER_STATE_IN_OFF_0(7) | PLL_POWER_STATE_IN_TXS2_0(7);
			अगर (orig != data)
				si_pअगर_phy0_wreg(adev,PB0_PIF_PWRDOWN_0, data);

			orig = data = si_pअगर_phy0_rreg(adev,PB0_PIF_PWRDOWN_1);
			data &= ~(PLL_POWER_STATE_IN_OFF_1_MASK | PLL_POWER_STATE_IN_TXS2_1_MASK);
			data |= PLL_POWER_STATE_IN_OFF_1(7) | PLL_POWER_STATE_IN_TXS2_1(7);
			अगर (orig != data)
				si_pअगर_phy0_wreg(adev,PB0_PIF_PWRDOWN_1, data);

			orig = data = si_pअगर_phy1_rreg(adev,PB1_PIF_PWRDOWN_0);
			data &= ~(PLL_POWER_STATE_IN_OFF_0_MASK | PLL_POWER_STATE_IN_TXS2_0_MASK);
			data |= PLL_POWER_STATE_IN_OFF_0(7) | PLL_POWER_STATE_IN_TXS2_0(7);
			अगर (orig != data)
				si_pअगर_phy1_wreg(adev,PB1_PIF_PWRDOWN_0, data);

			orig = data = si_pअगर_phy1_rreg(adev,PB1_PIF_PWRDOWN_1);
			data &= ~(PLL_POWER_STATE_IN_OFF_1_MASK | PLL_POWER_STATE_IN_TXS2_1_MASK);
			data |= PLL_POWER_STATE_IN_OFF_1(7) | PLL_POWER_STATE_IN_TXS2_1(7);
			अगर (orig != data)
				si_pअगर_phy1_wreg(adev,PB1_PIF_PWRDOWN_1, data);

			अगर ((adev->asic_type != CHIP_OLAND) && (adev->asic_type != CHIP_HAIन_अंक)) अणु
				orig = data = si_pअगर_phy0_rreg(adev,PB0_PIF_PWRDOWN_0);
				data &= ~PLL_RAMP_UP_TIME_0_MASK;
				अगर (orig != data)
					si_pअगर_phy0_wreg(adev,PB0_PIF_PWRDOWN_0, data);

				orig = data = si_pअगर_phy0_rreg(adev,PB0_PIF_PWRDOWN_1);
				data &= ~PLL_RAMP_UP_TIME_1_MASK;
				अगर (orig != data)
					si_pअगर_phy0_wreg(adev,PB0_PIF_PWRDOWN_1, data);

				orig = data = si_pअगर_phy0_rreg(adev,PB0_PIF_PWRDOWN_2);
				data &= ~PLL_RAMP_UP_TIME_2_MASK;
				अगर (orig != data)
					si_pअगर_phy0_wreg(adev,PB0_PIF_PWRDOWN_2, data);

				orig = data = si_pअगर_phy0_rreg(adev,PB0_PIF_PWRDOWN_3);
				data &= ~PLL_RAMP_UP_TIME_3_MASK;
				अगर (orig != data)
					si_pअगर_phy0_wreg(adev,PB0_PIF_PWRDOWN_3, data);

				orig = data = si_pअगर_phy1_rreg(adev,PB1_PIF_PWRDOWN_0);
				data &= ~PLL_RAMP_UP_TIME_0_MASK;
				अगर (orig != data)
					si_pअगर_phy1_wreg(adev,PB1_PIF_PWRDOWN_0, data);

				orig = data = si_pअगर_phy1_rreg(adev,PB1_PIF_PWRDOWN_1);
				data &= ~PLL_RAMP_UP_TIME_1_MASK;
				अगर (orig != data)
					si_pअगर_phy1_wreg(adev,PB1_PIF_PWRDOWN_1, data);

				orig = data = si_pअगर_phy1_rreg(adev,PB1_PIF_PWRDOWN_2);
				data &= ~PLL_RAMP_UP_TIME_2_MASK;
				अगर (orig != data)
					si_pअगर_phy1_wreg(adev,PB1_PIF_PWRDOWN_2, data);

				orig = data = si_pअगर_phy1_rreg(adev,PB1_PIF_PWRDOWN_3);
				data &= ~PLL_RAMP_UP_TIME_3_MASK;
				अगर (orig != data)
					si_pअगर_phy1_wreg(adev,PB1_PIF_PWRDOWN_3, data);
			पूर्ण
			orig = data = RREG32_PCIE_PORT(PCIE_LC_LINK_WIDTH_CNTL);
			data &= ~LC_DYN_LANES_PWR_STATE_MASK;
			data |= LC_DYN_LANES_PWR_STATE(3);
			अगर (orig != data)
				WREG32_PCIE_PORT(PCIE_LC_LINK_WIDTH_CNTL, data);

			orig = data = si_pअगर_phy0_rreg(adev,PB0_PIF_CNTL);
			data &= ~LS2_EXIT_TIME_MASK;
			अगर ((adev->asic_type == CHIP_OLAND) || (adev->asic_type == CHIP_HAIन_अंक))
				data |= LS2_EXIT_TIME(5);
			अगर (orig != data)
				si_pअगर_phy0_wreg(adev,PB0_PIF_CNTL, data);

			orig = data = si_pअगर_phy1_rreg(adev,PB1_PIF_CNTL);
			data &= ~LS2_EXIT_TIME_MASK;
			अगर ((adev->asic_type == CHIP_OLAND) || (adev->asic_type == CHIP_HAIन_अंक))
				data |= LS2_EXIT_TIME(5);
			अगर (orig != data)
				si_pअगर_phy1_wreg(adev,PB1_PIF_CNTL, data);

			अगर (!disable_clkreq &&
			    !pci_is_root_bus(adev->pdev->bus)) अणु
				काष्ठा pci_dev *root = adev->pdev->bus->self;
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

अटल व्योम si_fix_pci_max_पढ़ो_req_size(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक पढ़ोrq;
	u16 v;

	पढ़ोrq = pcie_get_पढ़ोrq(adev->pdev);
	v = ffs(पढ़ोrq) - 8;
	अगर ((v == 0) || (v == 6) || (v == 7))
		pcie_set_पढ़ोrq(adev->pdev, 512);
पूर्ण

अटल पूर्णांक si_common_hw_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	si_fix_pci_max_पढ़ो_req_size(adev);
	si_init_golden_रेजिस्टरs(adev);
	si_pcie_gen3_enable(adev);
	si_program_aspm(adev);

	वापस 0;
पूर्ण

अटल पूर्णांक si_common_hw_fini(व्योम *handle)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक si_common_suspend(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	वापस si_common_hw_fini(adev);
पूर्ण

अटल पूर्णांक si_common_resume(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	वापस si_common_hw_init(adev);
पूर्ण

अटल bool si_common_is_idle(व्योम *handle)
अणु
	वापस true;
पूर्ण

अटल पूर्णांक si_common_रुको_क्रम_idle(व्योम *handle)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक si_common_soft_reset(व्योम *handle)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक si_common_set_घड़ीgating_state(व्योम *handle,
					    क्रमागत amd_घड़ीgating_state state)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक si_common_set_घातergating_state(व्योम *handle,
					    क्रमागत amd_घातergating_state state)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा amd_ip_funcs si_common_ip_funcs = अणु
	.name = "si_common",
	.early_init = si_common_early_init,
	.late_init = शून्य,
	.sw_init = si_common_sw_init,
	.sw_fini = si_common_sw_fini,
	.hw_init = si_common_hw_init,
	.hw_fini = si_common_hw_fini,
	.suspend = si_common_suspend,
	.resume = si_common_resume,
	.is_idle = si_common_is_idle,
	.रुको_क्रम_idle = si_common_रुको_क्रम_idle,
	.soft_reset = si_common_soft_reset,
	.set_घड़ीgating_state = si_common_set_घड़ीgating_state,
	.set_घातergating_state = si_common_set_घातergating_state,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_ip_block_version si_common_ip_block =
अणु
	.type = AMD_IP_BLOCK_TYPE_COMMON,
	.major = 1,
	.minor = 0,
	.rev = 0,
	.funcs = &si_common_ip_funcs,
पूर्ण;

पूर्णांक si_set_ip_blocks(काष्ठा amdgpu_device *adev)
अणु
	चयन (adev->asic_type) अणु
	हाल CHIP_VERDE:
	हाल CHIP_TAHITI:
	हाल CHIP_PITCAIRN:
		amdgpu_device_ip_block_add(adev, &si_common_ip_block);
		amdgpu_device_ip_block_add(adev, &gmc_v6_0_ip_block);
		amdgpu_device_ip_block_add(adev, &si_ih_ip_block);
		amdgpu_device_ip_block_add(adev, &gfx_v6_0_ip_block);
		amdgpu_device_ip_block_add(adev, &si_dma_ip_block);
		amdgpu_device_ip_block_add(adev, &si_smu_ip_block);
		अगर (adev->enable_भव_display)
			amdgpu_device_ip_block_add(adev, &dce_भव_ip_block);
#अगर defined(CONFIG_DRM_AMD_DC) && defined(CONFIG_DRM_AMD_DC_SI)
		अन्यथा अगर (amdgpu_device_has_dc_support(adev))
			amdgpu_device_ip_block_add(adev, &dm_ip_block);
#पूर्ण_अगर
		अन्यथा
			amdgpu_device_ip_block_add(adev, &dce_v6_0_ip_block);
		amdgpu_device_ip_block_add(adev, &uvd_v3_1_ip_block);
		/* amdgpu_device_ip_block_add(adev, &vce_v1_0_ip_block); */
		अवरोध;
	हाल CHIP_OLAND:
		amdgpu_device_ip_block_add(adev, &si_common_ip_block);
		amdgpu_device_ip_block_add(adev, &gmc_v6_0_ip_block);
		amdgpu_device_ip_block_add(adev, &si_ih_ip_block);
		amdgpu_device_ip_block_add(adev, &gfx_v6_0_ip_block);
		amdgpu_device_ip_block_add(adev, &si_dma_ip_block);
		amdgpu_device_ip_block_add(adev, &si_smu_ip_block);
		अगर (adev->enable_भव_display)
			amdgpu_device_ip_block_add(adev, &dce_भव_ip_block);
#अगर defined(CONFIG_DRM_AMD_DC) && defined(CONFIG_DRM_AMD_DC_SI)
		अन्यथा अगर (amdgpu_device_has_dc_support(adev))
			amdgpu_device_ip_block_add(adev, &dm_ip_block);
#पूर्ण_अगर
		अन्यथा
			amdgpu_device_ip_block_add(adev, &dce_v6_4_ip_block);
		amdgpu_device_ip_block_add(adev, &uvd_v3_1_ip_block);
		/* amdgpu_device_ip_block_add(adev, &vce_v1_0_ip_block); */
		अवरोध;
	हाल CHIP_HAIन_अंक:
		amdgpu_device_ip_block_add(adev, &si_common_ip_block);
		amdgpu_device_ip_block_add(adev, &gmc_v6_0_ip_block);
		amdgpu_device_ip_block_add(adev, &si_ih_ip_block);
		amdgpu_device_ip_block_add(adev, &gfx_v6_0_ip_block);
		amdgpu_device_ip_block_add(adev, &si_dma_ip_block);
		amdgpu_device_ip_block_add(adev, &si_smu_ip_block);
		अगर (adev->enable_भव_display)
			amdgpu_device_ip_block_add(adev, &dce_भव_ip_block);
		अवरोध;
	शेष:
		BUG();
	पूर्ण
	वापस 0;
पूर्ण

