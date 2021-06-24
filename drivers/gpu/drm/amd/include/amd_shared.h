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
 */

#अगर_अघोषित __AMD_SHARED_H__
#घोषणा __AMD_SHARED_H__

#समावेश <drm/amd_asic_type.h>


#घोषणा AMD_MAX_USEC_TIMEOUT		1000000  /* 1000 ms */

/*
 * Chip flags
 */
क्रमागत amd_chip_flags अणु
	AMD_ASIC_MASK = 0x0000ffffUL,
	AMD_FLAGS_MASK  = 0xffff0000UL,
	AMD_IS_MOBILITY = 0x00010000UL,
	AMD_IS_APU      = 0x00020000UL,
	AMD_IS_PX       = 0x00040000UL,
	AMD_EXP_HW_SUPPORT = 0x00080000UL,
पूर्ण;

क्रमागत amd_apu_flags अणु
	AMD_APU_IS_RAVEN = 0x00000001UL,
	AMD_APU_IS_RAVEN2 = 0x00000002UL,
	AMD_APU_IS_PICASSO = 0x00000004UL,
	AMD_APU_IS_RENOIR = 0x00000008UL,
	AMD_APU_IS_GREEN_SARDINE = 0x00000010UL,
	AMD_APU_IS_VANGOGH = 0x00000020UL,
पूर्ण;

/**
* DOC: IP Blocks
*
* GPUs are composed of IP (पूर्णांकellectual property) blocks. These
* IP blocks provide various functionalities: display, graphics,
* video decode, etc. The IP blocks that comprise a particular GPU
* are listed in the GPU's respective SoC file. amdgpu_device.c
* acquires the list of IP blocks क्रम the GPU in use on initialization.
* It can then operate on this list to perक्रमm standard driver operations
* such as: init, fini, suspend, resume, etc.
* 
*
* IP block implementations are named using the following convention:
* <functionality>_v<version> (E.g.: gfx_v6_0).
*/

/**
* क्रमागत amd_ip_block_type - Used to classअगरy IP blocks by functionality.
*
* @AMD_IP_BLOCK_TYPE_COMMON: GPU Family
* @AMD_IP_BLOCK_TYPE_GMC: Graphics Memory Controller
* @AMD_IP_BLOCK_TYPE_IH: Interrupt Handler
* @AMD_IP_BLOCK_TYPE_SMC: System Management Controller
* @AMD_IP_BLOCK_TYPE_PSP: Platक्रमm Security Processor
* @AMD_IP_BLOCK_TYPE_DCE: Display and Compositing Engine
* @AMD_IP_BLOCK_TYPE_GFX: Graphics and Compute Engine
* @AMD_IP_BLOCK_TYPE_SDMA: System DMA Engine
* @AMD_IP_BLOCK_TYPE_UVD: Unअगरied Video Decoder
* @AMD_IP_BLOCK_TYPE_VCE: Video Compression Engine
* @AMD_IP_BLOCK_TYPE_ACP: Audio Co-Processor
* @AMD_IP_BLOCK_TYPE_VCN: Video Core/Codec Next
* @AMD_IP_BLOCK_TYPE_MES: Micro-Engine Scheduler
* @AMD_IP_BLOCK_TYPE_JPEG: JPEG Engine
*/
क्रमागत amd_ip_block_type अणु
	AMD_IP_BLOCK_TYPE_COMMON,
	AMD_IP_BLOCK_TYPE_GMC,
	AMD_IP_BLOCK_TYPE_IH,
	AMD_IP_BLOCK_TYPE_SMC,
	AMD_IP_BLOCK_TYPE_PSP,
	AMD_IP_BLOCK_TYPE_DCE,
	AMD_IP_BLOCK_TYPE_GFX,
	AMD_IP_BLOCK_TYPE_SDMA,
	AMD_IP_BLOCK_TYPE_UVD,
	AMD_IP_BLOCK_TYPE_VCE,
	AMD_IP_BLOCK_TYPE_ACP,
	AMD_IP_BLOCK_TYPE_VCN,
	AMD_IP_BLOCK_TYPE_MES,
	AMD_IP_BLOCK_TYPE_JPEG
पूर्ण;

क्रमागत amd_घड़ीgating_state अणु
	AMD_CG_STATE_GATE = 0,
	AMD_CG_STATE_UNGATE,
पूर्ण;


क्रमागत amd_घातergating_state अणु
	AMD_PG_STATE_GATE = 0,
	AMD_PG_STATE_UNGATE,
पूर्ण;


/* CG flags */
#घोषणा AMD_CG_SUPPORT_GFX_MGCG			(1 << 0)
#घोषणा AMD_CG_SUPPORT_GFX_MGLS			(1 << 1)
#घोषणा AMD_CG_SUPPORT_GFX_CGCG			(1 << 2)
#घोषणा AMD_CG_SUPPORT_GFX_CGLS			(1 << 3)
#घोषणा AMD_CG_SUPPORT_GFX_CGTS			(1 << 4)
#घोषणा AMD_CG_SUPPORT_GFX_CGTS_LS		(1 << 5)
#घोषणा AMD_CG_SUPPORT_GFX_CP_LS		(1 << 6)
#घोषणा AMD_CG_SUPPORT_GFX_RLC_LS		(1 << 7)
#घोषणा AMD_CG_SUPPORT_MC_LS			(1 << 8)
#घोषणा AMD_CG_SUPPORT_MC_MGCG			(1 << 9)
#घोषणा AMD_CG_SUPPORT_SDMA_LS			(1 << 10)
#घोषणा AMD_CG_SUPPORT_SDMA_MGCG		(1 << 11)
#घोषणा AMD_CG_SUPPORT_BIF_LS			(1 << 12)
#घोषणा AMD_CG_SUPPORT_UVD_MGCG			(1 << 13)
#घोषणा AMD_CG_SUPPORT_VCE_MGCG			(1 << 14)
#घोषणा AMD_CG_SUPPORT_HDP_LS			(1 << 15)
#घोषणा AMD_CG_SUPPORT_HDP_MGCG			(1 << 16)
#घोषणा AMD_CG_SUPPORT_ROM_MGCG			(1 << 17)
#घोषणा AMD_CG_SUPPORT_DRM_LS			(1 << 18)
#घोषणा AMD_CG_SUPPORT_BIF_MGCG			(1 << 19)
#घोषणा AMD_CG_SUPPORT_GFX_3D_CGCG		(1 << 20)
#घोषणा AMD_CG_SUPPORT_GFX_3D_CGLS		(1 << 21)
#घोषणा AMD_CG_SUPPORT_DRM_MGCG			(1 << 22)
#घोषणा AMD_CG_SUPPORT_DF_MGCG			(1 << 23)
#घोषणा AMD_CG_SUPPORT_VCN_MGCG			(1 << 24)
#घोषणा AMD_CG_SUPPORT_HDP_DS			(1 << 25)
#घोषणा AMD_CG_SUPPORT_HDP_SD			(1 << 26)
#घोषणा AMD_CG_SUPPORT_IH_CG			(1 << 27)
#घोषणा AMD_CG_SUPPORT_ATHUB_LS			(1 << 28)
#घोषणा AMD_CG_SUPPORT_ATHUB_MGCG		(1 << 29)
#घोषणा AMD_CG_SUPPORT_JPEG_MGCG		(1 << 30)
#घोषणा AMD_CG_SUPPORT_GFX_FGCG			(1 << 31)
/* PG flags */
#घोषणा AMD_PG_SUPPORT_GFX_PG			(1 << 0)
#घोषणा AMD_PG_SUPPORT_GFX_SMG			(1 << 1)
#घोषणा AMD_PG_SUPPORT_GFX_DMG			(1 << 2)
#घोषणा AMD_PG_SUPPORT_UVD			(1 << 3)
#घोषणा AMD_PG_SUPPORT_VCE			(1 << 4)
#घोषणा AMD_PG_SUPPORT_CP			(1 << 5)
#घोषणा AMD_PG_SUPPORT_GDS			(1 << 6)
#घोषणा AMD_PG_SUPPORT_RLC_SMU_HS		(1 << 7)
#घोषणा AMD_PG_SUPPORT_SDMA			(1 << 8)
#घोषणा AMD_PG_SUPPORT_ACP			(1 << 9)
#घोषणा AMD_PG_SUPPORT_SAMU			(1 << 10)
#घोषणा AMD_PG_SUPPORT_GFX_QUICK_MG		(1 << 11)
#घोषणा AMD_PG_SUPPORT_GFX_PIPELINE		(1 << 12)
#घोषणा AMD_PG_SUPPORT_MMHUB			(1 << 13)
#घोषणा AMD_PG_SUPPORT_VCN			(1 << 14)
#घोषणा AMD_PG_SUPPORT_VCN_DPG			(1 << 15)
#घोषणा AMD_PG_SUPPORT_ATHUB			(1 << 16)
#घोषणा AMD_PG_SUPPORT_JPEG			(1 << 17)

/**
 * क्रमागत PP_FEATURE_MASK - Used to mask घातer play features.
 *
 * @PP_SCLK_DPM_MASK: Dynamic adjusपंचांगent of the प्रणाली (graphics) घड़ी.
 * @PP_MCLK_DPM_MASK: Dynamic adjusपंचांगent of the memory घड़ी.
 * @PP_PCIE_DPM_MASK: Dynamic adjusपंचांगent of PCIE घड़ीs and lanes.
 * @PP_SCLK_DEEP_SLEEP_MASK: System (graphics) घड़ी deep sleep.
 * @PP_POWER_CONTAINMENT_MASK: Power containment.
 * @PP_UVD_HANDSHAKE_MASK: Unअगरied video decoder handshake.
 * @PP_SMC_VOLTAGE_CONTROL_MASK: Dynamic voltage control.
 * @PP_VBI_TIME_SUPPORT_MASK: Vertical blank पूर्णांकerval support.
 * @PP_ULV_MASK: Ultra low voltage.
 * @PP_ENABLE_GFX_CG_THRU_SMU: SMU control of GFX engine घड़ीgating.
 * @PP_CLOCK_STRETCH_MASK: Clock stretching.
 * @PP_OD_FUZZY_FAN_CONTROL_MASK: Overdrive fuzzy fan control.
 * @PP_SOCCLK_DPM_MASK: Dynamic adjusपंचांगent of the SoC घड़ी.
 * @PP_DCEFCLK_DPM_MASK: Dynamic adjusपंचांगent of the Display Controller Engine Fabric घड़ी.
 * @PP_OVERDRIVE_MASK: Over- and under-घड़ीing support.
 * @PP_GFXOFF_MASK: Dynamic graphics engine घातer control.
 * @PP_ACG_MASK: Adaptive घड़ी generator.
 * @PP_STUTTER_MODE: Stutter mode.
 * @PP_AVFS_MASK: Adaptive voltage and frequency scaling.
 *
 * To override these settings on boot, append amdgpu.ppfeaturemask=<mask> to
 * the kernel's command line parameters. This is usually done through a system's
 * boot loader (E.g. GRUB). If manually loading the driver, pass
 * ppfeaturemask=<mask> as a modprobe parameter.
 */
क्रमागत PP_FEATURE_MASK अणु
	PP_SCLK_DPM_MASK = 0x1,
	PP_MCLK_DPM_MASK = 0x2,
	PP_PCIE_DPM_MASK = 0x4,
	PP_SCLK_DEEP_SLEEP_MASK = 0x8,
	PP_POWER_CONTAINMENT_MASK = 0x10,
	PP_UVD_HANDSHAKE_MASK = 0x20,
	PP_SMC_VOLTAGE_CONTROL_MASK = 0x40,
	PP_VBI_TIME_SUPPORT_MASK = 0x80,
	PP_ULV_MASK = 0x100,
	PP_ENABLE_GFX_CG_THRU_SMU = 0x200,
	PP_CLOCK_STRETCH_MASK = 0x400,
	PP_OD_FUZZY_FAN_CONTROL_MASK = 0x800,
	PP_SOCCLK_DPM_MASK = 0x1000,
	PP_DCEFCLK_DPM_MASK = 0x2000,
	PP_OVERDRIVE_MASK = 0x4000,
	PP_GFXOFF_MASK = 0x8000,
	PP_ACG_MASK = 0x10000,
	PP_STUTTER_MODE = 0x20000,
	PP_AVFS_MASK = 0x40000,
	PP_GFX_DCS_MASK = 0x80000,
पूर्ण;

क्रमागत amd_harvest_ip_mask अणु
    AMD_HARVEST_IP_VCN_MASK = 0x1,
    AMD_HARVEST_IP_JPEG_MASK = 0x2,
    AMD_HARVEST_IP_DMU_MASK = 0x4,
पूर्ण;

क्रमागत DC_FEATURE_MASK अणु
	DC_FBC_MASK = 0x1,
	DC_MULTI_MON_PP_MCLK_SWITCH_MASK = 0x2,
	DC_DISABLE_FRACTIONAL_PWM_MASK = 0x4,
	DC_PSR_MASK = 0x8,
पूर्ण;

क्रमागत DC_DEBUG_MASK अणु
	DC_DISABLE_PIPE_SPLIT = 0x1,
	DC_DISABLE_STUTTER = 0x2,
	DC_DISABLE_DSC = 0x4,
	DC_DISABLE_CLOCK_GATING = 0x8
पूर्ण;

क्रमागत amd_dpm_क्रमced_level;

/**
 * काष्ठा amd_ip_funcs - general hooks क्रम managing amdgpu IP Blocks
 * @name: Name of IP block
 * @early_init: sets up early driver state (pre sw_init),
 *              करोes not configure hw - Optional
 * @late_init: sets up late driver/hw state (post hw_init) - Optional
 * @sw_init: sets up driver state, करोes not configure hw
 * @sw_fini: tears करोwn driver state, करोes not configure hw
 * @hw_init: sets up the hw state
 * @hw_fini: tears करोwn the hw state
 * @late_fini: final cleanup
 * @suspend: handles IP specअगरic hw/sw changes क्रम suspend
 * @resume: handles IP specअगरic hw/sw changes क्रम resume
 * @is_idle: वापसs current IP block idle status
 * @रुको_क्रम_idle: poll क्रम idle
 * @check_soft_reset: check soft reset the IP block
 * @pre_soft_reset: pre soft reset the IP block
 * @soft_reset: soft reset the IP block
 * @post_soft_reset: post soft reset the IP block
 * @set_घड़ीgating_state: enable/disable cg क्रम the IP block
 * @set_घातergating_state: enable/disable pg क्रम the IP block
 * @get_घड़ीgating_state: get current घड़ीgating status
 * @enable_umd_pstate: enable UMD घातerstate
 *
 * These hooks provide an पूर्णांकerface क्रम controlling the operational state
 * of IP blocks. After acquiring a list of IP blocks क्रम the GPU in use,
 * the driver can make chip-wide state changes by walking this list and
 * making calls to hooks from each IP block. This list is ordered to ensure
 * that the driver initializes the IP blocks in a safe sequence.
 */
काष्ठा amd_ip_funcs अणु
	अक्षर *name;
	पूर्णांक (*early_init)(व्योम *handle);
	पूर्णांक (*late_init)(व्योम *handle);
	पूर्णांक (*sw_init)(व्योम *handle);
	पूर्णांक (*sw_fini)(व्योम *handle);
	पूर्णांक (*hw_init)(व्योम *handle);
	पूर्णांक (*hw_fini)(व्योम *handle);
	व्योम (*late_fini)(व्योम *handle);
	पूर्णांक (*suspend)(व्योम *handle);
	पूर्णांक (*resume)(व्योम *handle);
	bool (*is_idle)(व्योम *handle);
	पूर्णांक (*रुको_क्रम_idle)(व्योम *handle);
	bool (*check_soft_reset)(व्योम *handle);
	पूर्णांक (*pre_soft_reset)(व्योम *handle);
	पूर्णांक (*soft_reset)(व्योम *handle);
	पूर्णांक (*post_soft_reset)(व्योम *handle);
	पूर्णांक (*set_घड़ीgating_state)(व्योम *handle,
				     क्रमागत amd_घड़ीgating_state state);
	पूर्णांक (*set_घातergating_state)(व्योम *handle,
				     क्रमागत amd_घातergating_state state);
	व्योम (*get_घड़ीgating_state)(व्योम *handle, u32 *flags);
	पूर्णांक (*enable_umd_pstate)(व्योम *handle, क्रमागत amd_dpm_क्रमced_level *level);
पूर्ण;


#पूर्ण_अगर /* __AMD_SHARED_H__ */
