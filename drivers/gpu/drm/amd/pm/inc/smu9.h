<शैली गुरु>
/*
 * Copyright 2016 Advanced Micro Devices, Inc.
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

#अगर_अघोषित SMU9_H
#घोषणा SMU9_H

#आशय pack(push, 1)

#घोषणा ENABLE_DEBUG_FEATURES

/* Feature Control Defines */
#घोषणा FEATURE_DPM_PREFETCHER_BIT      0
#घोषणा FEATURE_DPM_GFXCLK_BIT          1
#घोषणा FEATURE_DPM_UCLK_BIT            2
#घोषणा FEATURE_DPM_SOCCLK_BIT          3
#घोषणा FEATURE_DPM_UVD_BIT             4
#घोषणा FEATURE_DPM_VCE_BIT             5
#घोषणा FEATURE_ULV_BIT                 6
#घोषणा FEATURE_DPM_MP0CLK_BIT          7
#घोषणा FEATURE_DPM_LINK_BIT            8
#घोषणा FEATURE_DPM_DCEFCLK_BIT         9
#घोषणा FEATURE_AVFS_BIT                10
#घोषणा FEATURE_DS_GFXCLK_BIT           11
#घोषणा FEATURE_DS_SOCCLK_BIT           12
#घोषणा FEATURE_DS_LCLK_BIT             13
#घोषणा FEATURE_PPT_BIT                 14
#घोषणा FEATURE_TDC_BIT                 15
#घोषणा FEATURE_THERMAL_BIT             16
#घोषणा FEATURE_GFX_PER_CU_CG_BIT       17
#घोषणा FEATURE_RM_BIT                  18
#घोषणा FEATURE_DS_DCEFCLK_BIT          19
#घोषणा FEATURE_ACDC_BIT                20
#घोषणा FEATURE_VR0HOT_BIT              21
#घोषणा FEATURE_VR1HOT_BIT              22
#घोषणा FEATURE_FW_CTF_BIT              23
#घोषणा FEATURE_LED_DISPLAY_BIT         24
#घोषणा FEATURE_FAN_CONTROL_BIT         25
#घोषणा FEATURE_FAST_PPT_BIT            26
#घोषणा FEATURE_GFX_EDC_BIT             27
#घोषणा FEATURE_ACG_BIT                 28
#घोषणा FEATURE_PCC_LIMIT_CONTROL_BIT   29
#घोषणा FEATURE_SPARE_30_BIT            30
#घोषणा FEATURE_SPARE_31_BIT            31

#घोषणा NUM_FEATURES                    32

#घोषणा FFEATURE_DPM_PREFETCHER_MASK     (1 << FEATURE_DPM_PREFETCHER_BIT     )
#घोषणा FFEATURE_DPM_GFXCLK_MASK         (1 << FEATURE_DPM_GFXCLK_BIT         )
#घोषणा FFEATURE_DPM_UCLK_MASK           (1 << FEATURE_DPM_UCLK_BIT           )
#घोषणा FFEATURE_DPM_SOCCLK_MASK         (1 << FEATURE_DPM_SOCCLK_BIT         )
#घोषणा FFEATURE_DPM_UVD_MASK            (1 << FEATURE_DPM_UVD_BIT            )
#घोषणा FFEATURE_DPM_VCE_MASK            (1 << FEATURE_DPM_VCE_BIT            )
#घोषणा FFEATURE_ULV_MASK                (1 << FEATURE_ULV_BIT                )
#घोषणा FFEATURE_DPM_MP0CLK_MASK         (1 << FEATURE_DPM_MP0CLK_BIT         )
#घोषणा FFEATURE_DPM_LINK_MASK           (1 << FEATURE_DPM_LINK_BIT           )
#घोषणा FFEATURE_DPM_DCEFCLK_MASK        (1 << FEATURE_DPM_DCEFCLK_BIT        )
#घोषणा FFEATURE_AVFS_MASK               (1 << FEATURE_AVFS_BIT               )
#घोषणा FFEATURE_DS_GFXCLK_MASK          (1 << FEATURE_DS_GFXCLK_BIT          )
#घोषणा FFEATURE_DS_SOCCLK_MASK          (1 << FEATURE_DS_SOCCLK_BIT          )
#घोषणा FFEATURE_DS_LCLK_MASK            (1 << FEATURE_DS_LCLK_BIT            )
#घोषणा FFEATURE_PPT_MASK                (1 << FEATURE_PPT_BIT                )
#घोषणा FFEATURE_TDC_MASK                (1 << FEATURE_TDC_BIT                )
#घोषणा FFEATURE_THERMAL_MASK            (1 << FEATURE_THERMAL_BIT            )
#घोषणा FFEATURE_GFX_PER_CU_CG_MASK      (1 << FEATURE_GFX_PER_CU_CG_BIT      )
#घोषणा FFEATURE_RM_MASK                 (1 << FEATURE_RM_BIT                 )
#घोषणा FFEATURE_DS_DCEFCLK_MASK         (1 << FEATURE_DS_DCEFCLK_BIT         )
#घोषणा FFEATURE_ACDC_MASK               (1 << FEATURE_ACDC_BIT               )
#घोषणा FFEATURE_VR0HOT_MASK             (1 << FEATURE_VR0HOT_BIT             )
#घोषणा FFEATURE_VR1HOT_MASK             (1 << FEATURE_VR1HOT_BIT             )
#घोषणा FFEATURE_FW_CTF_MASK             (1 << FEATURE_FW_CTF_BIT             )
#घोषणा FFEATURE_LED_DISPLAY_MASK        (1 << FEATURE_LED_DISPLAY_BIT        )
#घोषणा FFEATURE_FAN_CONTROL_MASK        (1 << FEATURE_FAN_CONTROL_BIT        )

#घोषणा FEATURE_FAST_PPT_MASK            (1 << FAST_PPT_BIT                   )
#घोषणा FEATURE_GFX_EDC_MASK             (1 << FEATURE_GFX_EDC_BIT            )
#घोषणा FEATURE_ACG_MASK                 (1 << FEATURE_ACG_BIT                )
#घोषणा FEATURE_PCC_LIMIT_CONTROL_MASK   (1 << FEATURE_PCC_LIMIT_CONTROL_BIT  )
#घोषणा FFEATURE_SPARE_30_MASK           (1 << FEATURE_SPARE_30_BIT           )
#घोषणा FFEATURE_SPARE_31_MASK           (1 << FEATURE_SPARE_31_BIT           )
/* Workload types */
#घोषणा WORKLOAD_VR_BIT                 0
#घोषणा WORKLOAD_FRTC_BIT               1
#घोषणा WORKLOAD_VIDEO_BIT              2
#घोषणा WORKLOAD_COMPUTE_BIT            3
#घोषणा NUM_WORKLOADS                   4

/* ULV Client Masks */
#घोषणा ULV_CLIENT_RLC_MASK         0x00000001
#घोषणा ULV_CLIENT_UVD_MASK         0x00000002
#घोषणा ULV_CLIENT_VCE_MASK         0x00000004
#घोषणा ULV_CLIENT_SDMA0_MASK       0x00000008
#घोषणा ULV_CLIENT_SDMA1_MASK       0x00000010
#घोषणा ULV_CLIENT_JPEG_MASK        0x00000020
#घोषणा ULV_CLIENT_GFXCLK_DPM_MASK  0x00000040
#घोषणा ULV_CLIENT_UVD_DPM_MASK     0x00000080
#घोषणा ULV_CLIENT_VCE_DPM_MASK     0x00000100
#घोषणा ULV_CLIENT_MP0CLK_DPM_MASK  0x00000200
#घोषणा ULV_CLIENT_UCLK_DPM_MASK    0x00000400
#घोषणा ULV_CLIENT_SOCCLK_DPM_MASK  0x00000800
#घोषणा ULV_CLIENT_DCEFCLK_DPM_MASK 0x00001000

प्रकार काष्ठा अणु
	/* MP1_EXT_SCRATCH0 */
	uपूर्णांक32_t CurrLevel_GFXCLK  : 4;
	uपूर्णांक32_t CurrLevel_UVD     : 4;
	uपूर्णांक32_t CurrLevel_VCE     : 4;
	uपूर्णांक32_t CurrLevel_LCLK    : 4;
	uपूर्णांक32_t CurrLevel_MP0CLK  : 4;
	uपूर्णांक32_t CurrLevel_UCLK    : 4;
	uपूर्णांक32_t CurrLevel_SOCCLK  : 4;
	uपूर्णांक32_t CurrLevel_DCEFCLK : 4;
	/* MP1_EXT_SCRATCH1 */
	uपूर्णांक32_t TargLevel_GFXCLK  : 4;
	uपूर्णांक32_t TargLevel_UVD     : 4;
	uपूर्णांक32_t TargLevel_VCE     : 4;
	uपूर्णांक32_t TargLevel_LCLK    : 4;
	uपूर्णांक32_t TargLevel_MP0CLK  : 4;
	uपूर्णांक32_t TargLevel_UCLK    : 4;
	uपूर्णांक32_t TargLevel_SOCCLK  : 4;
	uपूर्णांक32_t TargLevel_DCEFCLK : 4;
	/* MP1_EXT_SCRATCH2-7 */
	uपूर्णांक32_t Reserved[6];
पूर्ण FwStatus_t;

#आशय pack(pop)

#पूर्ण_अगर

