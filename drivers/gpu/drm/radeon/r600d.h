<शैली गुरु>
/*
 * Copyright 2009 Advanced Micro Devices, Inc.
 * Copyright 2009 Red Hat Inc.
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
 * Authors: Dave Airlie
 *          Alex Deucher
 *          Jerome Glisse
 */
#अगर_अघोषित R600D_H
#घोषणा R600D_H

#घोषणा CP_PACKET2			0x80000000
#घोषणा		PACKET2_PAD_SHIFT		0
#घोषणा		PACKET2_PAD_MASK		(0x3fffffff << 0)

#घोषणा PACKET2(v)	(CP_PACKET2 | REG_SET(PACKET2_PAD, (v)))

#घोषणा R6XX_MAX_SH_GPRS			256
#घोषणा R6XX_MAX_TEMP_GPRS			16
#घोषणा R6XX_MAX_SH_THREADS			256
#घोषणा R6XX_MAX_SH_STACK_ENTRIES		4096
#घोषणा R6XX_MAX_BACKENDS			8
#घोषणा R6XX_MAX_BACKENDS_MASK			0xff
#घोषणा R6XX_MAX_SIMDS				8
#घोषणा R6XX_MAX_SIMDS_MASK			0xff
#घोषणा R6XX_MAX_PIPES				8
#घोषणा R6XX_MAX_PIPES_MASK			0xff

/* tiling bits */
#घोषणा     ARRAY_LINEAR_GENERAL              0x00000000
#घोषणा     ARRAY_LINEAR_ALIGNED              0x00000001
#घोषणा     ARRAY_1D_TILED_THIN1              0x00000002
#घोषणा     ARRAY_2D_TILED_THIN1              0x00000004

/* Registers */
#घोषणा	ARB_POP						0x2418
#घोषणा 	ENABLE_TC128					(1 << 30)
#घोषणा	ARB_GDEC_RD_CNTL				0x246C

#घोषणा	CC_GC_SHADER_PIPE_CONFIG			0x8950
#घोषणा	CC_RB_BACKEND_DISABLE				0x98F4
#घोषणा		BACKEND_DISABLE(x)				((x) << 16)

#घोषणा R_028808_CB_COLOR_CONTROL			0x28808
#घोषणा   S_028808_SPECIAL_OP(x)                       (((x) & 0x7) << 4)
#घोषणा   G_028808_SPECIAL_OP(x)                       (((x) >> 4) & 0x7)
#घोषणा   C_028808_SPECIAL_OP                          0xFFFFFF8F
#घोषणा     V_028808_SPECIAL_NORMAL                     0x00
#घोषणा     V_028808_SPECIAL_DISABLE                    0x01
#घोषणा     V_028808_SPECIAL_RESOLVE_BOX                0x07

#घोषणा	CB_COLOR0_BASE					0x28040
#घोषणा	CB_COLOR1_BASE					0x28044
#घोषणा	CB_COLOR2_BASE					0x28048
#घोषणा	CB_COLOR3_BASE					0x2804C
#घोषणा	CB_COLOR4_BASE					0x28050
#घोषणा	CB_COLOR5_BASE					0x28054
#घोषणा	CB_COLOR6_BASE					0x28058
#घोषणा	CB_COLOR7_BASE					0x2805C
#घोषणा	CB_COLOR7_FRAG					0x280FC

#घोषणा CB_COLOR0_SIZE                                  0x28060
#घोषणा CB_COLOR0_VIEW                                  0x28080
#घोषणा R_028080_CB_COLOR0_VIEW                      0x028080
#घोषणा   S_028080_SLICE_START(x)                      (((x) & 0x7FF) << 0)
#घोषणा   G_028080_SLICE_START(x)                      (((x) >> 0) & 0x7FF)
#घोषणा   C_028080_SLICE_START                         0xFFFFF800
#घोषणा   S_028080_SLICE_MAX(x)                        (((x) & 0x7FF) << 13)
#घोषणा   G_028080_SLICE_MAX(x)                        (((x) >> 13) & 0x7FF)
#घोषणा   C_028080_SLICE_MAX                           0xFF001FFF
#घोषणा R_028084_CB_COLOR1_VIEW                      0x028084
#घोषणा R_028088_CB_COLOR2_VIEW                      0x028088
#घोषणा R_02808C_CB_COLOR3_VIEW                      0x02808C
#घोषणा R_028090_CB_COLOR4_VIEW                      0x028090
#घोषणा R_028094_CB_COLOR5_VIEW                      0x028094
#घोषणा R_028098_CB_COLOR6_VIEW                      0x028098
#घोषणा R_02809C_CB_COLOR7_VIEW                      0x02809C
#घोषणा R_028100_CB_COLOR0_MASK                      0x028100
#घोषणा   S_028100_CMASK_BLOCK_MAX(x)                  (((x) & 0xFFF) << 0)
#घोषणा   G_028100_CMASK_BLOCK_MAX(x)                  (((x) >> 0) & 0xFFF)
#घोषणा   C_028100_CMASK_BLOCK_MAX                     0xFFFFF000
#घोषणा   S_028100_FMASK_TILE_MAX(x)                   (((x) & 0xFFFFF) << 12)
#घोषणा   G_028100_FMASK_TILE_MAX(x)                   (((x) >> 12) & 0xFFFFF)
#घोषणा   C_028100_FMASK_TILE_MAX                      0x00000FFF
#घोषणा R_028104_CB_COLOR1_MASK                      0x028104
#घोषणा R_028108_CB_COLOR2_MASK                      0x028108
#घोषणा R_02810C_CB_COLOR3_MASK                      0x02810C
#घोषणा R_028110_CB_COLOR4_MASK                      0x028110
#घोषणा R_028114_CB_COLOR5_MASK                      0x028114
#घोषणा R_028118_CB_COLOR6_MASK                      0x028118
#घोषणा R_02811C_CB_COLOR7_MASK                      0x02811C
#घोषणा CB_COLOR0_INFO                                  0x280a0
#	define CB_FORMAT(x)				((x) << 2)
#       define CB_ARRAY_MODE(x)                         ((x) << 8)
#	define CB_SOURCE_FORMAT(x)			((x) << 27)
#	define CB_SF_EXPORT_FULL			0
#	define CB_SF_EXPORT_NORM			1
#घोषणा CB_COLOR0_TILE                                  0x280c0
#घोषणा CB_COLOR0_FRAG                                  0x280e0
#घोषणा CB_COLOR0_MASK                                  0x28100

#घोषणा SQ_ALU_CONST_CACHE_PS_0				0x28940
#घोषणा SQ_ALU_CONST_CACHE_PS_1				0x28944
#घोषणा SQ_ALU_CONST_CACHE_PS_2				0x28948
#घोषणा SQ_ALU_CONST_CACHE_PS_3				0x2894c
#घोषणा SQ_ALU_CONST_CACHE_PS_4				0x28950
#घोषणा SQ_ALU_CONST_CACHE_PS_5				0x28954
#घोषणा SQ_ALU_CONST_CACHE_PS_6				0x28958
#घोषणा SQ_ALU_CONST_CACHE_PS_7				0x2895c
#घोषणा SQ_ALU_CONST_CACHE_PS_8				0x28960
#घोषणा SQ_ALU_CONST_CACHE_PS_9				0x28964
#घोषणा SQ_ALU_CONST_CACHE_PS_10			0x28968
#घोषणा SQ_ALU_CONST_CACHE_PS_11			0x2896c
#घोषणा SQ_ALU_CONST_CACHE_PS_12			0x28970
#घोषणा SQ_ALU_CONST_CACHE_PS_13			0x28974
#घोषणा SQ_ALU_CONST_CACHE_PS_14			0x28978
#घोषणा SQ_ALU_CONST_CACHE_PS_15			0x2897c
#घोषणा SQ_ALU_CONST_CACHE_VS_0				0x28980
#घोषणा SQ_ALU_CONST_CACHE_VS_1				0x28984
#घोषणा SQ_ALU_CONST_CACHE_VS_2				0x28988
#घोषणा SQ_ALU_CONST_CACHE_VS_3				0x2898c
#घोषणा SQ_ALU_CONST_CACHE_VS_4				0x28990
#घोषणा SQ_ALU_CONST_CACHE_VS_5				0x28994
#घोषणा SQ_ALU_CONST_CACHE_VS_6				0x28998
#घोषणा SQ_ALU_CONST_CACHE_VS_7				0x2899c
#घोषणा SQ_ALU_CONST_CACHE_VS_8				0x289a0
#घोषणा SQ_ALU_CONST_CACHE_VS_9				0x289a4
#घोषणा SQ_ALU_CONST_CACHE_VS_10			0x289a8
#घोषणा SQ_ALU_CONST_CACHE_VS_11			0x289ac
#घोषणा SQ_ALU_CONST_CACHE_VS_12			0x289b0
#घोषणा SQ_ALU_CONST_CACHE_VS_13			0x289b4
#घोषणा SQ_ALU_CONST_CACHE_VS_14			0x289b8
#घोषणा SQ_ALU_CONST_CACHE_VS_15			0x289bc
#घोषणा SQ_ALU_CONST_CACHE_GS_0				0x289c0
#घोषणा SQ_ALU_CONST_CACHE_GS_1				0x289c4
#घोषणा SQ_ALU_CONST_CACHE_GS_2				0x289c8
#घोषणा SQ_ALU_CONST_CACHE_GS_3				0x289cc
#घोषणा SQ_ALU_CONST_CACHE_GS_4				0x289d0
#घोषणा SQ_ALU_CONST_CACHE_GS_5				0x289d4
#घोषणा SQ_ALU_CONST_CACHE_GS_6				0x289d8
#घोषणा SQ_ALU_CONST_CACHE_GS_7				0x289dc
#घोषणा SQ_ALU_CONST_CACHE_GS_8				0x289e0
#घोषणा SQ_ALU_CONST_CACHE_GS_9				0x289e4
#घोषणा SQ_ALU_CONST_CACHE_GS_10			0x289e8
#घोषणा SQ_ALU_CONST_CACHE_GS_11			0x289ec
#घोषणा SQ_ALU_CONST_CACHE_GS_12			0x289f0
#घोषणा SQ_ALU_CONST_CACHE_GS_13			0x289f4
#घोषणा SQ_ALU_CONST_CACHE_GS_14			0x289f8
#घोषणा SQ_ALU_CONST_CACHE_GS_15			0x289fc

#घोषणा	CONFIG_MEMSIZE					0x5428
#घोषणा CONFIG_CNTL					0x5424
#घोषणा	CP_STALLED_STAT1			0x8674
#घोषणा	CP_STALLED_STAT2			0x8678
#घोषणा	CP_BUSY_STAT				0x867C
#घोषणा	CP_STAT						0x8680
#घोषणा	CP_COHER_BASE					0x85F8
#घोषणा	CP_DEBUG					0xC1FC
#घोषणा	R_0086D8_CP_ME_CNTL			0x86D8
#घोषणा		S_0086D8_CP_PFP_HALT(x)			(((x) & 1)<<26)
#घोषणा		C_0086D8_CP_PFP_HALT(x)			((x) & 0xFBFFFFFF)
#घोषणा		S_0086D8_CP_ME_HALT(x)			(((x) & 1)<<28)
#घोषणा		C_0086D8_CP_ME_HALT(x)			((x) & 0xEFFFFFFF)
#घोषणा	CP_ME_RAM_DATA					0xC160
#घोषणा	CP_ME_RAM_RADDR					0xC158
#घोषणा	CP_ME_RAM_WADDR					0xC15C
#घोषणा CP_MEQ_THRESHOLDS				0x8764
#घोषणा		MEQ_END(x)					((x) << 16)
#घोषणा		ROQ_END(x)					((x) << 24)
#घोषणा	CP_PERFMON_CNTL					0x87FC
#घोषणा	CP_PFP_UCODE_ADDR				0xC150
#घोषणा	CP_PFP_UCODE_DATA				0xC154
#घोषणा	CP_QUEUE_THRESHOLDS				0x8760
#घोषणा		ROQ_IB1_START(x)				((x) << 0)
#घोषणा		ROQ_IB2_START(x)				((x) << 8)
#घोषणा	CP_RB_BASE					0xC100
#घोषणा	CP_RB_CNTL					0xC104
#घोषणा		RB_BUFSZ(x)					((x) << 0)
#घोषणा		RB_BLKSZ(x)					((x) << 8)
#घोषणा		RB_NO_UPDATE					(1 << 27)
#घोषणा		RB_RPTR_WR_ENA					(1 << 31)
#घोषणा		BUF_SWAP_32BIT					(2 << 16)
#घोषणा	CP_RB_RPTR					0x8700
#घोषणा	CP_RB_RPTR_ADDR					0xC10C
#घोषणा		RB_RPTR_SWAP(x)					((x) << 0)
#घोषणा	CP_RB_RPTR_ADDR_HI				0xC110
#घोषणा	CP_RB_RPTR_WR					0xC108
#घोषणा	CP_RB_WPTR					0xC114
#घोषणा	CP_RB_WPTR_ADDR					0xC118
#घोषणा	CP_RB_WPTR_ADDR_HI				0xC11C
#घोषणा	CP_RB_WPTR_DELAY				0x8704
#घोषणा	CP_ROQ_IB1_STAT					0x8784
#घोषणा	CP_ROQ_IB2_STAT					0x8788
#घोषणा	CP_SEM_WAIT_TIMER				0x85BC

#घोषणा	DB_DEBUG					0x9830
#घोषणा		PREZ_MUST_WAIT_FOR_POSTZ_DONE			(1 << 31)
#घोषणा	DB_DEPTH_BASE					0x2800C
#घोषणा	DB_HTILE_DATA_BASE				0x28014
#घोषणा	DB_HTILE_SURFACE				0x28D24
#घोषणा   S_028D24_HTILE_WIDTH(x)                      (((x) & 0x1) << 0)
#घोषणा   G_028D24_HTILE_WIDTH(x)                      (((x) >> 0) & 0x1)
#घोषणा   C_028D24_HTILE_WIDTH                         0xFFFFFFFE
#घोषणा   S_028D24_HTILE_HEIGHT(x)                      (((x) & 0x1) << 1)
#घोषणा   G_028D24_HTILE_HEIGHT(x)                      (((x) >> 1) & 0x1)
#घोषणा   C_028D24_HTILE_HEIGHT                         0xFFFFFFFD
#घोषणा   G_028D24_LINEAR(x)                           (((x) >> 2) & 0x1)
#घोषणा	DB_WATERMARKS					0x9838
#घोषणा		DEPTH_FREE(x)					((x) << 0)
#घोषणा		DEPTH_FLUSH(x)					((x) << 5)
#घोषणा		DEPTH_PENDING_FREE(x)				((x) << 15)
#घोषणा		DEPTH_CACHELINE_FREE(x)				((x) << 20)

#घोषणा	DCP_TILING_CONFIG				0x6CA0
#घोषणा		PIPE_TILING(x)					((x) << 1)
#घोषणा 	BANK_TILING(x)					((x) << 4)
#घोषणा		GROUP_SIZE(x)					((x) << 6)
#घोषणा		ROW_TILING(x)					((x) << 8)
#घोषणा		BANK_SWAPS(x)					((x) << 11)
#घोषणा		SAMPLE_SPLIT(x)					((x) << 14)
#घोषणा		BACKEND_MAP(x)					((x) << 16)

#घोषणा GB_TILING_CONFIG				0x98F0
#घोषणा     PIPE_TILING__SHIFT              1
#घोषणा     PIPE_TILING__MASK               0x0000000e

#घोषणा	GC_USER_SHADER_PIPE_CONFIG			0x8954
#घोषणा		INACTIVE_QD_PIPES(x)				((x) << 8)
#घोषणा		INACTIVE_QD_PIPES_MASK				0x0000FF00
#घोषणा		INACTIVE_SIMDS(x)				((x) << 16)
#घोषणा		INACTIVE_SIMDS_MASK				0x00FF0000

#घोषणा SQ_CONFIG                                         0x8c00
#       define VC_ENABLE                                  (1 << 0)
#       define EXPORT_SRC_C                               (1 << 1)
#       define DX9_CONSTS                                 (1 << 2)
#       define ALU_INST_PREFER_VECTOR                     (1 << 3)
#       define DX10_CLAMP                                 (1 << 4)
#       define CLAUSE_SEQ_PRIO(x)                         ((x) << 8)
#       define PS_PRIO(x)                                 ((x) << 24)
#       define VS_PRIO(x)                                 ((x) << 26)
#       define GS_PRIO(x)                                 ((x) << 28)
#       define ES_PRIO(x)                                 ((x) << 30)
#घोषणा SQ_GPR_RESOURCE_MGMT_1                            0x8c04
#       define NUM_PS_GPRS(x)                             ((x) << 0)
#       define NUM_VS_GPRS(x)                             ((x) << 16)
#       define NUM_CLAUSE_TEMP_GPRS(x)                    ((x) << 28)
#घोषणा SQ_GPR_RESOURCE_MGMT_2                            0x8c08
#       define NUM_GS_GPRS(x)                             ((x) << 0)
#       define NUM_ES_GPRS(x)                             ((x) << 16)
#घोषणा SQ_THREAD_RESOURCE_MGMT                           0x8c0c
#       define NUM_PS_THREADS(x)                          ((x) << 0)
#       define NUM_VS_THREADS(x)                          ((x) << 8)
#       define NUM_GS_THREADS(x)                          ((x) << 16)
#       define NUM_ES_THREADS(x)                          ((x) << 24)
#घोषणा SQ_STACK_RESOURCE_MGMT_1                          0x8c10
#       define NUM_PS_STACK_ENTRIES(x)                    ((x) << 0)
#       define NUM_VS_STACK_ENTRIES(x)                    ((x) << 16)
#घोषणा SQ_STACK_RESOURCE_MGMT_2                          0x8c14
#       define NUM_GS_STACK_ENTRIES(x)                    ((x) << 0)
#       define NUM_ES_STACK_ENTRIES(x)                    ((x) << 16)
#घोषणा SQ_ESGS_RING_BASE                               0x8c40
#घोषणा SQ_GSVS_RING_BASE                               0x8c48
#घोषणा SQ_ESTMP_RING_BASE                              0x8c50
#घोषणा SQ_GSTMP_RING_BASE                              0x8c58
#घोषणा SQ_VSTMP_RING_BASE                              0x8c60
#घोषणा SQ_PSTMP_RING_BASE                              0x8c68
#घोषणा SQ_FBUF_RING_BASE                               0x8c70
#घोषणा SQ_REDUC_RING_BASE                              0x8c78

#घोषणा GRBM_CNTL                                       0x8000
#       define GRBM_READ_TIMEOUT(x)                     ((x) << 0)
#घोषणा	GRBM_STATUS					0x8010
#घोषणा		CMDFIFO_AVAIL_MASK				0x0000001F
#घोषणा		GUI_ACTIVE					(1<<31)
#घोषणा	GRBM_STATUS2					0x8014
#घोषणा	GRBM_SOFT_RESET					0x8020
#घोषणा		SOFT_RESET_CP					(1<<0)

#घोषणा	CG_THERMAL_CTRL					0x7F0
#घोषणा		DIG_THERM_DPM(x)			((x) << 12)
#घोषणा		DIG_THERM_DPM_MASK			0x000FF000
#घोषणा		DIG_THERM_DPM_SHIFT			12
#घोषणा	CG_THERMAL_STATUS				0x7F4
#घोषणा		ASIC_T(x)			        ((x) << 0)
#घोषणा		ASIC_T_MASK			        0x1FF
#घोषणा		ASIC_T_SHIFT			        0
#घोषणा	CG_THERMAL_INT					0x7F8
#घोषणा		DIG_THERM_INTH(x)			((x) << 8)
#घोषणा		DIG_THERM_INTH_MASK			0x0000FF00
#घोषणा		DIG_THERM_INTH_SHIFT			8
#घोषणा		DIG_THERM_INTL(x)			((x) << 16)
#घोषणा		DIG_THERM_INTL_MASK			0x00FF0000
#घोषणा		DIG_THERM_INTL_SHIFT			16
#घोषणा 	THERM_INT_MASK_HIGH			(1 << 24)
#घोषणा 	THERM_INT_MASK_LOW			(1 << 25)

#घोषणा	RV770_CG_THERMAL_INT				0x734

#घोषणा	HDP_HOST_PATH_CNTL				0x2C00
#घोषणा	HDP_NONSURFACE_BASE				0x2C04
#घोषणा	HDP_NONSURFACE_INFO				0x2C08
#घोषणा	HDP_NONSURFACE_SIZE				0x2C0C
#घोषणा HDP_REG_COHERENCY_FLUSH_CNTL			0x54A0
#घोषणा	HDP_TILING_CONFIG				0x2F3C
#घोषणा HDP_DEBUG1                                      0x2F34

#घोषणा MC_CONFIG					0x2000
#घोषणा MC_VM_AGP_TOP					0x2184
#घोषणा MC_VM_AGP_BOT					0x2188
#घोषणा	MC_VM_AGP_BASE					0x218C
#घोषणा MC_VM_FB_LOCATION				0x2180
#घोषणा MC_VM_L1_TLB_MCB_RD_UVD_CNTL			0x2124
#घोषणा 	ENABLE_L1_TLB					(1 << 0)
#घोषणा		ENABLE_L1_FRAGMENT_PROCESSING			(1 << 1)
#घोषणा		ENABLE_L1_STRICT_ORDERING			(1 << 2)
#घोषणा		SYSTEM_ACCESS_MODE_MASK				0x000000C0
#घोषणा		SYSTEM_ACCESS_MODE_SHIFT			6
#घोषणा		SYSTEM_ACCESS_MODE_PA_ONLY			(0 << 6)
#घोषणा		SYSTEM_ACCESS_MODE_USE_SYS_MAP			(1 << 6)
#घोषणा		SYSTEM_ACCESS_MODE_IN_SYS			(2 << 6)
#घोषणा		SYSTEM_ACCESS_MODE_NOT_IN_SYS			(3 << 6)
#घोषणा		SYSTEM_APERTURE_UNMAPPED_ACCESS_PASS_THRU	(0 << 8)
#घोषणा		SYSTEM_APERTURE_UNMAPPED_ACCESS_DEFAULT_PAGE	(1 << 8)
#घोषणा		ENABLE_SEMAPHORE_MODE				(1 << 10)
#घोषणा		ENABLE_WAIT_L2_QUERY				(1 << 11)
#घोषणा		EFFECTIVE_L1_TLB_SIZE(x)			(((x) & 7) << 12)
#घोषणा		EFFECTIVE_L1_TLB_SIZE_MASK			0x00007000
#घोषणा		EFFECTIVE_L1_TLB_SIZE_SHIFT			12
#घोषणा		EFFECTIVE_L1_QUEUE_SIZE(x)			(((x) & 7) << 15)
#घोषणा		EFFECTIVE_L1_QUEUE_SIZE_MASK			0x00038000
#घोषणा		EFFECTIVE_L1_QUEUE_SIZE_SHIFT			15
#घोषणा MC_VM_L1_TLB_MCD_RD_A_CNTL			0x219C
#घोषणा MC_VM_L1_TLB_MCD_RD_B_CNTL			0x21A0
#घोषणा MC_VM_L1_TLB_MCB_RD_GFX_CNTL			0x21FC
#घोषणा MC_VM_L1_TLB_MCB_RD_HDP_CNTL			0x2204
#घोषणा MC_VM_L1_TLB_MCB_RD_PDMA_CNTL			0x2208
#घोषणा MC_VM_L1_TLB_MCB_RD_SEM_CNTL			0x220C
#घोषणा	MC_VM_L1_TLB_MCB_RD_SYS_CNTL			0x2200
#घोषणा MC_VM_L1_TLB_MCB_WR_UVD_CNTL			0x212c
#घोषणा MC_VM_L1_TLB_MCD_WR_A_CNTL			0x21A4
#घोषणा MC_VM_L1_TLB_MCD_WR_B_CNTL			0x21A8
#घोषणा MC_VM_L1_TLB_MCB_WR_GFX_CNTL			0x2210
#घोषणा MC_VM_L1_TLB_MCB_WR_HDP_CNTL			0x2218
#घोषणा MC_VM_L1_TLB_MCB_WR_PDMA_CNTL			0x221C
#घोषणा MC_VM_L1_TLB_MCB_WR_SEM_CNTL			0x2220
#घोषणा MC_VM_L1_TLB_MCB_WR_SYS_CNTL			0x2214
#घोषणा MC_VM_SYSTEM_APERTURE_LOW_ADDR			0x2190
#घोषणा		LOGICAL_PAGE_NUMBER_MASK			0x000FFFFF
#घोषणा		LOGICAL_PAGE_NUMBER_SHIFT			0
#घोषणा MC_VM_SYSTEM_APERTURE_HIGH_ADDR			0x2194
#घोषणा MC_VM_SYSTEM_APERTURE_DEFAULT_ADDR		0x2198

#घोषणा RS_DQ_RD_RET_CONF				0x2348

#घोषणा	PA_CL_ENHANCE					0x8A14
#घोषणा		CLIP_VTX_REORDER_ENA				(1 << 0)
#घोषणा		NUM_CLIP_SEQ(x)					((x) << 1)
#घोषणा PA_SC_AA_CONFIG					0x28C04
#घोषणा	PA_SC_AA_SAMPLE_LOCS_2S				0x8B40
#घोषणा	PA_SC_AA_SAMPLE_LOCS_4S				0x8B44
#घोषणा	PA_SC_AA_SAMPLE_LOCS_8S_WD0			0x8B48
#घोषणा	PA_SC_AA_SAMPLE_LOCS_8S_WD1			0x8B4C
#घोषणा		S0_X(x)						((x) << 0)
#घोषणा		S0_Y(x)						((x) << 4)
#घोषणा		S1_X(x)						((x) << 8)
#घोषणा		S1_Y(x)						((x) << 12)
#घोषणा		S2_X(x)						((x) << 16)
#घोषणा		S2_Y(x)						((x) << 20)
#घोषणा		S3_X(x)						((x) << 24)
#घोषणा		S3_Y(x)						((x) << 28)
#घोषणा		S4_X(x)						((x) << 0)
#घोषणा		S4_Y(x)						((x) << 4)
#घोषणा		S5_X(x)						((x) << 8)
#घोषणा		S5_Y(x)						((x) << 12)
#घोषणा		S6_X(x)						((x) << 16)
#घोषणा		S6_Y(x)						((x) << 20)
#घोषणा		S7_X(x)						((x) << 24)
#घोषणा		S7_Y(x)						((x) << 28)
#घोषणा PA_SC_CLIPRECT_RULE				0x2820c
#घोषणा	PA_SC_ENHANCE					0x8BF0
#घोषणा		FORCE_EOV_MAX_CLK_CNT(x)			((x) << 0)
#घोषणा		FORCE_EOV_MAX_TILE_CNT(x)			((x) << 12)
#घोषणा PA_SC_LINE_STIPPLE				0x28A0C
#घोषणा	PA_SC_LINE_STIPPLE_STATE			0x8B10
#घोषणा PA_SC_MODE_CNTL					0x28A4C
#घोषणा	PA_SC_MULTI_CHIP_CNTL				0x8B20

#घोषणा PA_SC_SCREEN_SCISSOR_TL                         0x28030
#घोषणा PA_SC_GENERIC_SCISSOR_TL                        0x28240
#घोषणा PA_SC_WINDOW_SCISSOR_TL                         0x28204

#घोषणा	PCIE_PORT_INDEX					0x0038
#घोषणा	PCIE_PORT_DATA					0x003C

#घोषणा CHMAP						0x2004
#घोषणा		NOOFCHAN_SHIFT					12
#घोषणा		NOOFCHAN_MASK					0x00003000

#घोषणा RAMCFG						0x2408
#घोषणा		NOOFBANK_SHIFT					0
#घोषणा		NOOFBANK_MASK					0x00000001
#घोषणा		NOOFRANK_SHIFT					1
#घोषणा		NOOFRANK_MASK					0x00000002
#घोषणा		NOOFROWS_SHIFT					2
#घोषणा		NOOFROWS_MASK					0x0000001C
#घोषणा		NOOFCOLS_SHIFT					5
#घोषणा		NOOFCOLS_MASK					0x00000060
#घोषणा		CHANSIZE_SHIFT					7
#घोषणा		CHANSIZE_MASK					0x00000080
#घोषणा		BURSTLENGTH_SHIFT				8
#घोषणा		BURSTLENGTH_MASK				0x00000100
#घोषणा		CHANSIZE_OVERRIDE				(1 << 10)

#घोषणा	SCRATCH_REG0					0x8500
#घोषणा	SCRATCH_REG1					0x8504
#घोषणा	SCRATCH_REG2					0x8508
#घोषणा	SCRATCH_REG3					0x850C
#घोषणा	SCRATCH_REG4					0x8510
#घोषणा	SCRATCH_REG5					0x8514
#घोषणा	SCRATCH_REG6					0x8518
#घोषणा	SCRATCH_REG7					0x851C
#घोषणा	SCRATCH_UMSK					0x8540
#घोषणा	SCRATCH_ADDR					0x8544

#घोषणा	SPI_CONFIG_CNTL					0x9100
#घोषणा		GPR_WRITE_PRIORITY(x)				((x) << 0)
#घोषणा		DISABLE_INTERP_1				(1 << 5)
#घोषणा	SPI_CONFIG_CNTL_1				0x913C
#घोषणा		VTX_DONE_DELAY(x)				((x) << 0)
#घोषणा		INTERP_ONE_PRIM_PER_ROW				(1 << 4)
#घोषणा	SPI_INPUT_Z					0x286D8
#घोषणा	SPI_PS_IN_CONTROL_0				0x286CC
#घोषणा		NUM_INTERP(x)					((x)<<0)
#घोषणा		POSITION_ENA					(1<<8)
#घोषणा		POSITION_CENTROID				(1<<9)
#घोषणा		POSITION_ADDR(x)				((x)<<10)
#घोषणा		PARAM_GEN(x)					((x)<<15)
#घोषणा		PARAM_GEN_ADDR(x)				((x)<<19)
#घोषणा		BARYC_SAMPLE_CNTL(x)				((x)<<26)
#घोषणा		PERSP_GRADIENT_ENA				(1<<28)
#घोषणा		LINEAR_GRADIENT_ENA				(1<<29)
#घोषणा		POSITION_SAMPLE					(1<<30)
#घोषणा		BARYC_AT_SAMPLE_ENA				(1<<31)
#घोषणा	SPI_PS_IN_CONTROL_1				0x286D0
#घोषणा		GEN_INDEX_PIX					(1<<0)
#घोषणा		GEN_INDEX_PIX_ADDR(x)				((x)<<1)
#घोषणा		FRONT_FACE_ENA					(1<<8)
#घोषणा		FRONT_FACE_CHAN(x)				((x)<<9)
#घोषणा		FRONT_FACE_ALL_BITS				(1<<11)
#घोषणा		FRONT_FACE_ADDR(x)				((x)<<12)
#घोषणा		FOG_ADDR(x)					((x)<<17)
#घोषणा		FIXED_PT_POSITION_ENA				(1<<24)
#घोषणा		FIXED_PT_POSITION_ADDR(x)			((x)<<25)

#घोषणा	SQ_MS_FIFO_SIZES				0x8CF0
#घोषणा		CACHE_FIFO_SIZE(x)				((x) << 0)
#घोषणा		FETCH_FIFO_HIWATER(x)				((x) << 8)
#घोषणा		DONE_FIFO_HIWATER(x)				((x) << 16)
#घोषणा		ALU_UPDATE_FIFO_HIWATER(x)			((x) << 24)
#घोषणा	SQ_PGM_START_ES					0x28880
#घोषणा	SQ_PGM_START_FS					0x28894
#घोषणा	SQ_PGM_START_GS					0x2886C
#घोषणा	SQ_PGM_START_PS					0x28840
#घोषणा SQ_PGM_RESOURCES_PS                             0x28850
#घोषणा SQ_PGM_EXPORTS_PS                               0x28854
#घोषणा SQ_PGM_CF_OFFSET_PS                             0x288cc
#घोषणा	SQ_PGM_START_VS					0x28858
#घोषणा SQ_PGM_RESOURCES_VS                             0x28868
#घोषणा SQ_PGM_CF_OFFSET_VS                             0x288d0

#घोषणा SQ_VTX_CONSTANT_WORD0_0				0x30000
#घोषणा SQ_VTX_CONSTANT_WORD1_0				0x30004
#घोषणा SQ_VTX_CONSTANT_WORD2_0				0x30008
#	define SQ_VTXC_BASE_ADDR_HI(x)			((x) << 0)
#	define SQ_VTXC_STRIDE(x)			((x) << 8)
#	define SQ_VTXC_ENDIAN_SWAP(x)			((x) << 30)
#	define SQ_ENDIAN_NONE				0
#	define SQ_ENDIAN_8IN16				1
#	define SQ_ENDIAN_8IN32				2
#घोषणा SQ_VTX_CONSTANT_WORD3_0				0x3000c
#घोषणा	SQ_VTX_CONSTANT_WORD6_0				0x38018
#घोषणा		S__SQ_VTX_CONSTANT_TYPE(x)			(((x) & 3) << 30)
#घोषणा		G__SQ_VTX_CONSTANT_TYPE(x)			(((x) >> 30) & 3)
#घोषणा			SQ_TEX_VTX_INVALID_TEXTURE			0x0
#घोषणा			SQ_TEX_VTX_INVALID_BUFFER			0x1
#घोषणा			SQ_TEX_VTX_VALID_TEXTURE			0x2
#घोषणा			SQ_TEX_VTX_VALID_BUFFER				0x3


#घोषणा	SX_MISC						0x28350
#घोषणा	SX_MEMORY_EXPORT_BASE				0x9010
#घोषणा	SX_DEBUG_1					0x9054
#घोषणा		SMX_EVENT_RELEASE				(1 << 0)
#घोषणा		ENABLE_NEW_SMX_ADDRESS				(1 << 16)

#घोषणा	TA_CNTL_AUX					0x9508
#घोषणा		DISABLE_CUBE_WRAP				(1 << 0)
#घोषणा		DISABLE_CUBE_ANISO				(1 << 1)
#घोषणा		SYNC_GRADIENT					(1 << 24)
#घोषणा		SYNC_WALKER					(1 << 25)
#घोषणा		SYNC_ALIGNER					(1 << 26)
#घोषणा		BILINEAR_PRECISION_6_BIT			(0 << 31)
#घोषणा		BILINEAR_PRECISION_8_BIT			(1 << 31)

#घोषणा	TC_CNTL						0x9608
#घोषणा		TC_L2_SIZE(x)					((x)<<5)
#घोषणा		L2_DISABLE_LATE_HIT				(1<<9)

#घोषणा	VC_ENHANCE					0x9714

#घोषणा	VGT_CACHE_INVALIDATION				0x88C4
#घोषणा		CACHE_INVALIDATION(x)				((x)<<0)
#घोषणा			VC_ONLY						0
#घोषणा			TC_ONLY						1
#घोषणा			VC_AND_TC					2
#घोषणा	VGT_DMA_BASE					0x287E8
#घोषणा	VGT_DMA_BASE_HI					0x287E4
#घोषणा	VGT_ES_PER_GS					0x88CC
#घोषणा	VGT_GS_PER_ES					0x88C8
#घोषणा	VGT_GS_PER_VS					0x88E8
#घोषणा	VGT_GS_VERTEX_REUSE				0x88D4
#घोषणा VGT_PRIMITIVE_TYPE                              0x8958
#घोषणा	VGT_NUM_INSTANCES				0x8974
#घोषणा	VGT_OUT_DEALLOC_CNTL				0x28C5C
#घोषणा		DEALLOC_DIST_MASK				0x0000007F
#घोषणा	VGT_STRMOUT_BASE_OFFSET_0			0x28B10
#घोषणा	VGT_STRMOUT_BASE_OFFSET_1			0x28B14
#घोषणा	VGT_STRMOUT_BASE_OFFSET_2			0x28B18
#घोषणा	VGT_STRMOUT_BASE_OFFSET_3			0x28B1c
#घोषणा	VGT_STRMOUT_BASE_OFFSET_HI_0			0x28B44
#घोषणा	VGT_STRMOUT_BASE_OFFSET_HI_1			0x28B48
#घोषणा	VGT_STRMOUT_BASE_OFFSET_HI_2			0x28B4c
#घोषणा	VGT_STRMOUT_BASE_OFFSET_HI_3			0x28B50
#घोषणा	VGT_STRMOUT_BUFFER_BASE_0			0x28AD8
#घोषणा	VGT_STRMOUT_BUFFER_BASE_1			0x28AE8
#घोषणा	VGT_STRMOUT_BUFFER_BASE_2			0x28AF8
#घोषणा	VGT_STRMOUT_BUFFER_BASE_3			0x28B08
#घोषणा	VGT_STRMOUT_BUFFER_OFFSET_0			0x28ADC
#घोषणा	VGT_STRMOUT_BUFFER_OFFSET_1			0x28AEC
#घोषणा	VGT_STRMOUT_BUFFER_OFFSET_2			0x28AFC
#घोषणा	VGT_STRMOUT_BUFFER_OFFSET_3			0x28B0C
#घोषणा VGT_STRMOUT_BUFFER_SIZE_0			0x28AD0
#घोषणा VGT_STRMOUT_BUFFER_SIZE_1			0x28AE0
#घोषणा VGT_STRMOUT_BUFFER_SIZE_2			0x28AF0
#घोषणा VGT_STRMOUT_BUFFER_SIZE_3			0x28B00

#घोषणा	VGT_STRMOUT_EN					0x28AB0
#घोषणा	VGT_VERTEX_REUSE_BLOCK_CNTL			0x28C58
#घोषणा		VTX_REUSE_DEPTH_MASK				0x000000FF
#घोषणा VGT_EVENT_INITIATOR                             0x28a90
#       define CACHE_FLUSH_AND_INV_EVENT_TS                     (0x14 << 0)
#       define CACHE_FLUSH_AND_INV_EVENT                        (0x16 << 0)

#घोषणा VM_CONTEXT0_CNTL				0x1410
#घोषणा		ENABLE_CONTEXT					(1 << 0)
#घोषणा		PAGE_TABLE_DEPTH(x)				(((x) & 3) << 1)
#घोषणा		RANGE_PROTECTION_FAULT_ENABLE_DEFAULT		(1 << 4)
#घोषणा VM_CONTEXT0_INVALIDATION_LOW_ADDR		0x1490
#घोषणा VM_CONTEXT0_INVALIDATION_HIGH_ADDR		0x14B0
#घोषणा VM_CONTEXT0_PAGE_TABLE_BASE_ADDR		0x1574
#घोषणा VM_CONTEXT0_PAGE_TABLE_START_ADDR		0x1594
#घोषणा VM_CONTEXT0_PAGE_TABLE_END_ADDR			0x15B4
#घोषणा VM_CONTEXT0_PROTECTION_FAULT_DEFAULT_ADDR	0x1554
#घोषणा VM_CONTEXT0_REQUEST_RESPONSE			0x1470
#घोषणा		REQUEST_TYPE(x)					(((x) & 0xf) << 0)
#घोषणा		RESPONSE_TYPE_MASK				0x000000F0
#घोषणा		RESPONSE_TYPE_SHIFT				4
#घोषणा VM_L2_CNTL					0x1400
#घोषणा		ENABLE_L2_CACHE					(1 << 0)
#घोषणा		ENABLE_L2_FRAGMENT_PROCESSING			(1 << 1)
#घोषणा		ENABLE_L2_PTE_CACHE_LRU_UPDATE_BY_WRITE		(1 << 9)
#घोषणा		EFFECTIVE_L2_QUEUE_SIZE(x)			(((x) & 7) << 13)
#घोषणा VM_L2_CNTL2					0x1404
#घोषणा		INVALIDATE_ALL_L1_TLBS				(1 << 0)
#घोषणा		INVALIDATE_L2_CACHE				(1 << 1)
#घोषणा VM_L2_CNTL3					0x1408
#घोषणा		BANK_SELECT_0(x)				(((x) & 0x1f) << 0)
#घोषणा		BANK_SELECT_1(x)				(((x) & 0x1f) << 5)
#घोषणा		L2_CACHE_UPDATE_MODE(x)				(((x) & 3) << 10)
#घोषणा	VM_L2_STATUS					0x140C
#घोषणा		L2_BUSY						(1 << 0)

#घोषणा	WAIT_UNTIL					0x8040
#घोषणा         WAIT_CP_DMA_IDLE_bit                            (1 << 8)
#घोषणा         WAIT_2D_IDLE_bit                                (1 << 14)
#घोषणा         WAIT_3D_IDLE_bit                                (1 << 15)
#घोषणा         WAIT_2D_IDLECLEAN_bit                           (1 << 16)
#घोषणा         WAIT_3D_IDLECLEAN_bit                           (1 << 17)

/* async DMA */
#घोषणा DMA_TILING_CONFIG                                 0x3ec4
#घोषणा DMA_CONFIG                                        0x3e4c

#घोषणा DMA_RB_CNTL                                       0xd000
#       define DMA_RB_ENABLE                              (1 << 0)
#       define DMA_RB_SIZE(x)                             ((x) << 1) /* log2 */
#       define DMA_RB_SWAP_ENABLE                         (1 << 9) /* 8IN32 */
#       define DMA_RPTR_WRITEBACK_ENABLE                  (1 << 12)
#       define DMA_RPTR_WRITEBACK_SWAP_ENABLE             (1 << 13)  /* 8IN32 */
#       define DMA_RPTR_WRITEBACK_TIMER(x)                ((x) << 16) /* log2 */
#घोषणा DMA_RB_BASE                                       0xd004
#घोषणा DMA_RB_RPTR                                       0xd008
#घोषणा DMA_RB_WPTR                                       0xd00c

#घोषणा DMA_RB_RPTR_ADDR_HI                               0xd01c
#घोषणा DMA_RB_RPTR_ADDR_LO                               0xd020

#घोषणा DMA_IB_CNTL                                       0xd024
#       define DMA_IB_ENABLE                              (1 << 0)
#       define DMA_IB_SWAP_ENABLE                         (1 << 4)
#घोषणा DMA_IB_RPTR                                       0xd028
#घोषणा DMA_CNTL                                          0xd02c
#       define TRAP_ENABLE                                (1 << 0)
#       define SEM_INCOMPLETE_INT_ENABLE                  (1 << 1)
#       define SEM_WAIT_INT_ENABLE                        (1 << 2)
#       define DATA_SWAP_ENABLE                           (1 << 3)
#       define FENCE_SWAP_ENABLE                          (1 << 4)
#       define CTXEMPTY_INT_ENABLE                        (1 << 28)
#घोषणा DMA_STATUS_REG                                    0xd034
#       define DMA_IDLE                                   (1 << 0)
#घोषणा DMA_SEM_INCOMPLETE_TIMER_CNTL                     0xd044
#घोषणा DMA_SEM_WAIT_FAIL_TIMER_CNTL                      0xd048
#घोषणा DMA_MODE                                          0xd0bc

/* async DMA packets */
#घोषणा DMA_PACKET(cmd, t, s, n)	((((cmd) & 0xF) << 28) |	\
					 (((t) & 0x1) << 23) |		\
					 (((s) & 0x1) << 22) |		\
					 (((n) & 0xFFFF) << 0))
/* async DMA Packet types */
#घोषणा	DMA_PACKET_WRITE				  0x2
#घोषणा	DMA_PACKET_COPY					  0x3
#घोषणा	DMA_PACKET_INसूचीECT_BUFFER			  0x4
#घोषणा	DMA_PACKET_SEMAPHORE				  0x5
#घोषणा	DMA_PACKET_FENCE				  0x6
#घोषणा	DMA_PACKET_TRAP					  0x7
#घोषणा	DMA_PACKET_CONSTANT_FILL			  0xd /* 7xx only */
#घोषणा	DMA_PACKET_NOP					  0xf

#घोषणा IH_RB_CNTL                                        0x3e00
#       define IH_RB_ENABLE                               (1 << 0)
#       define IH_RB_SIZE(x)                              ((x) << 1) /* log2 */
#       define IH_RB_FULL_DRAIN_ENABLE                    (1 << 6)
#       define IH_WPTR_WRITEBACK_ENABLE                   (1 << 8)
#       define IH_WPTR_WRITEBACK_TIMER(x)                 ((x) << 9) /* log2 */
#       define IH_WPTR_OVERFLOW_ENABLE                    (1 << 16)
#       define IH_WPTR_OVERFLOW_CLEAR                     (1 << 31)
#घोषणा IH_RB_BASE                                        0x3e04
#घोषणा IH_RB_RPTR                                        0x3e08
#घोषणा IH_RB_WPTR                                        0x3e0c
#       define RB_OVERFLOW                                (1 << 0)
#       define WPTR_OFFSET_MASK                           0x3fffc
#घोषणा IH_RB_WPTR_ADDR_HI                                0x3e10
#घोषणा IH_RB_WPTR_ADDR_LO                                0x3e14
#घोषणा IH_CNTL                                           0x3e18
#       define ENABLE_INTR                                (1 << 0)
#       define IH_MC_SWAP(x)                              ((x) << 1)
#       define IH_MC_SWAP_NONE                            0
#       define IH_MC_SWAP_16BIT                           1
#       define IH_MC_SWAP_32BIT                           2
#       define IH_MC_SWAP_64BIT                           3
#       define RPTR_REARM                                 (1 << 4)
#       define MC_WRREQ_CREDIT(x)                         ((x) << 15)
#       define MC_WR_CLEAN_CNT(x)                         ((x) << 20)

#घोषणा RLC_CNTL                                          0x3f00
#       define RLC_ENABLE                                 (1 << 0)
#घोषणा RLC_HB_BASE                                       0x3f10
#घोषणा RLC_HB_CNTL                                       0x3f0c
#घोषणा RLC_HB_RPTR                                       0x3f20
#घोषणा RLC_HB_WPTR                                       0x3f1c
#घोषणा RLC_HB_WPTR_LSB_ADDR                              0x3f14
#घोषणा RLC_HB_WPTR_MSB_ADDR                              0x3f18
#घोषणा RLC_GPU_CLOCK_COUNT_LSB				  0x3f38
#घोषणा RLC_GPU_CLOCK_COUNT_MSB				  0x3f3c
#घोषणा RLC_CAPTURE_GPU_CLOCK_COUNT			  0x3f40
#घोषणा RLC_MC_CNTL                                       0x3f44
#घोषणा RLC_UCODE_CNTL                                    0x3f48
#घोषणा RLC_UCODE_ADDR                                    0x3f2c
#घोषणा RLC_UCODE_DATA                                    0x3f30

#घोषणा SRBM_SOFT_RESET                                   0xe60
#       define SOFT_RESET_BIF                             (1 << 1)
#       define SOFT_RESET_DMA                             (1 << 12)
#       define SOFT_RESET_RLC                             (1 << 13)
#       define SOFT_RESET_UVD                             (1 << 18)
#       define RV770_SOFT_RESET_DMA                       (1 << 20)

#घोषणा BIF_SCRATCH0                                      0x5438

#घोषणा BUS_CNTL                                          0x5420
#       define BIOS_ROM_DIS                               (1 << 1)
#       define VGA_COHE_SPEC_TIMER_DIS                    (1 << 9)

#घोषणा CP_INT_CNTL                                       0xc124
#       define CNTX_BUSY_INT_ENABLE                       (1 << 19)
#       define CNTX_EMPTY_INT_ENABLE                      (1 << 20)
#       define SCRATCH_INT_ENABLE                         (1 << 25)
#       define TIME_STAMP_INT_ENABLE                      (1 << 26)
#       define IB2_INT_ENABLE                             (1 << 29)
#       define IB1_INT_ENABLE                             (1 << 30)
#       define RB_INT_ENABLE                              (1 << 31)
#घोषणा CP_INT_STATUS                                     0xc128
#       define SCRATCH_INT_STAT                           (1 << 25)
#       define TIME_STAMP_INT_STAT                        (1 << 26)
#       define IB2_INT_STAT                               (1 << 29)
#       define IB1_INT_STAT                               (1 << 30)
#       define RB_INT_STAT                                (1 << 31)

#घोषणा GRBM_INT_CNTL                                     0x8060
#       define RDERR_INT_ENABLE                           (1 << 0)
#       define WAIT_COUNT_TIMEOUT_INT_ENABLE              (1 << 1)
#       define GUI_IDLE_INT_ENABLE                        (1 << 19)

#घोषणा INTERRUPT_CNTL                                    0x5468
#       define IH_DUMMY_RD_OVERRIDE                       (1 << 0)
#       define IH_DUMMY_RD_EN                             (1 << 1)
#       define IH_REQ_NONSNOOP_EN                         (1 << 3)
#       define GEN_IH_INT_EN                              (1 << 8)
#घोषणा INTERRUPT_CNTL2                                   0x546c

#घोषणा D1MODE_VBLANK_STATUS                              0x6534
#घोषणा D2MODE_VBLANK_STATUS                              0x6d34
#       define DxMODE_VBLANK_OCCURRED                     (1 << 0)
#       define DxMODE_VBLANK_ACK                          (1 << 4)
#       define DxMODE_VBLANK_STAT                         (1 << 12)
#       define DxMODE_VBLANK_INTERRUPT                    (1 << 16)
#       define DxMODE_VBLANK_INTERRUPT_TYPE               (1 << 17)
#घोषणा D1MODE_VLINE_STATUS                               0x653c
#घोषणा D2MODE_VLINE_STATUS                               0x6d3c
#       define DxMODE_VLINE_OCCURRED                      (1 << 0)
#       define DxMODE_VLINE_ACK                           (1 << 4)
#       define DxMODE_VLINE_STAT                          (1 << 12)
#       define DxMODE_VLINE_INTERRUPT                     (1 << 16)
#       define DxMODE_VLINE_INTERRUPT_TYPE                (1 << 17)
#घोषणा DxMODE_INT_MASK                                   0x6540
#       define D1MODE_VBLANK_INT_MASK                     (1 << 0)
#       define D1MODE_VLINE_INT_MASK                      (1 << 4)
#       define D2MODE_VBLANK_INT_MASK                     (1 << 8)
#       define D2MODE_VLINE_INT_MASK                      (1 << 12)
#घोषणा DCE3_DISP_INTERRUPT_STATUS                        0x7ddc
#       define DC_HPD1_INTERRUPT                          (1 << 18)
#       define DC_HPD2_INTERRUPT                          (1 << 19)
#घोषणा DISP_INTERRUPT_STATUS                             0x7edc
#       define LB_D1_VLINE_INTERRUPT                      (1 << 2)
#       define LB_D2_VLINE_INTERRUPT                      (1 << 3)
#       define LB_D1_VBLANK_INTERRUPT                     (1 << 4)
#       define LB_D2_VBLANK_INTERRUPT                     (1 << 5)
#       define DACA_AUTODETECT_INTERRUPT                  (1 << 16)
#       define DACB_AUTODETECT_INTERRUPT                  (1 << 17)
#       define DC_HOT_PLUG_DETECT1_INTERRUPT              (1 << 18)
#       define DC_HOT_PLUG_DETECT2_INTERRUPT              (1 << 19)
#       define DC_I2C_SW_DONE_INTERRUPT                   (1 << 20)
#       define DC_I2C_HW_DONE_INTERRUPT                   (1 << 21)
#घोषणा DISP_INTERRUPT_STATUS_CONTINUE                    0x7ee8
#घोषणा DCE3_DISP_INTERRUPT_STATUS_CONTINUE               0x7de8
#       define DC_HPD4_INTERRUPT                          (1 << 14)
#       define DC_HPD4_RX_INTERRUPT                       (1 << 15)
#       define DC_HPD3_INTERRUPT                          (1 << 28)
#       define DC_HPD1_RX_INTERRUPT                       (1 << 29)
#       define DC_HPD2_RX_INTERRUPT                       (1 << 30)
#घोषणा DCE3_DISP_INTERRUPT_STATUS_CONTINUE2              0x7dec
#       define DC_HPD3_RX_INTERRUPT                       (1 << 0)
#       define DIGA_DP_VID_STREAM_DISABLE_INTERRUPT       (1 << 1)
#       define DIGA_DP_STEER_FIFO_OVERFLOW_INTERRUPT      (1 << 2)
#       define DIGB_DP_VID_STREAM_DISABLE_INTERRUPT       (1 << 3)
#       define DIGB_DP_STEER_FIFO_OVERFLOW_INTERRUPT      (1 << 4)
#       define AUX1_SW_DONE_INTERRUPT                     (1 << 5)
#       define AUX1_LS_DONE_INTERRUPT                     (1 << 6)
#       define AUX2_SW_DONE_INTERRUPT                     (1 << 7)
#       define AUX2_LS_DONE_INTERRUPT                     (1 << 8)
#       define AUX3_SW_DONE_INTERRUPT                     (1 << 9)
#       define AUX3_LS_DONE_INTERRUPT                     (1 << 10)
#       define AUX4_SW_DONE_INTERRUPT                     (1 << 11)
#       define AUX4_LS_DONE_INTERRUPT                     (1 << 12)
#       define DIGA_DP_FAST_TRAINING_COMPLETE_INTERRUPT   (1 << 13)
#       define DIGB_DP_FAST_TRAINING_COMPLETE_INTERRUPT   (1 << 14)
/* DCE 3.2 */
#       define AUX5_SW_DONE_INTERRUPT                     (1 << 15)
#       define AUX5_LS_DONE_INTERRUPT                     (1 << 16)
#       define AUX6_SW_DONE_INTERRUPT                     (1 << 17)
#       define AUX6_LS_DONE_INTERRUPT                     (1 << 18)
#       define DC_HPD5_INTERRUPT                          (1 << 19)
#       define DC_HPD5_RX_INTERRUPT                       (1 << 20)
#       define DC_HPD6_INTERRUPT                          (1 << 21)
#       define DC_HPD6_RX_INTERRUPT                       (1 << 22)

#घोषणा DACA_AUTO_DETECT_CONTROL                          0x7828
#घोषणा DACB_AUTO_DETECT_CONTROL                          0x7a28
#घोषणा DCE3_DACA_AUTO_DETECT_CONTROL                     0x7028
#घोषणा DCE3_DACB_AUTO_DETECT_CONTROL                     0x7128
#       define DACx_AUTODETECT_MODE(x)                    ((x) << 0)
#       define DACx_AUTODETECT_MODE_NONE                  0
#       define DACx_AUTODETECT_MODE_CONNECT               1
#       define DACx_AUTODETECT_MODE_DISCONNECT            2
#       define DACx_AUTODETECT_FRAME_TIME_COUNTER(x)      ((x) << 8)
/* bit 18 = R/C, 17 = G/Y, 16 = B/Comp */
#       define DACx_AUTODETECT_CHECK_MASK(x)              ((x) << 16)

#घोषणा DCE3_DACA_AUTODETECT_INT_CONTROL                  0x7038
#घोषणा DCE3_DACB_AUTODETECT_INT_CONTROL                  0x7138
#घोषणा DACA_AUTODETECT_INT_CONTROL                       0x7838
#घोषणा DACB_AUTODETECT_INT_CONTROL                       0x7a38
#       define DACx_AUTODETECT_ACK                        (1 << 0)
#       define DACx_AUTODETECT_INT_ENABLE                 (1 << 16)

#घोषणा DC_HOT_PLUG_DETECT1_CONTROL                       0x7d00
#घोषणा DC_HOT_PLUG_DETECT2_CONTROL                       0x7d10
#घोषणा DC_HOT_PLUG_DETECT3_CONTROL                       0x7d24
#       define DC_HOT_PLUG_DETECTx_EN                     (1 << 0)

#घोषणा DC_HOT_PLUG_DETECT1_INT_STATUS                    0x7d04
#घोषणा DC_HOT_PLUG_DETECT2_INT_STATUS                    0x7d14
#घोषणा DC_HOT_PLUG_DETECT3_INT_STATUS                    0x7d28
#       define DC_HOT_PLUG_DETECTx_INT_STATUS             (1 << 0)
#       define DC_HOT_PLUG_DETECTx_SENSE                  (1 << 1)

/* DCE 3.0 */
#घोषणा DC_HPD1_INT_STATUS                                0x7d00
#घोषणा DC_HPD2_INT_STATUS                                0x7d0c
#घोषणा DC_HPD3_INT_STATUS                                0x7d18
#घोषणा DC_HPD4_INT_STATUS                                0x7d24
/* DCE 3.2 */
#घोषणा DC_HPD5_INT_STATUS                                0x7dc0
#घोषणा DC_HPD6_INT_STATUS                                0x7df4
#       define DC_HPDx_INT_STATUS                         (1 << 0)
#       define DC_HPDx_SENSE                              (1 << 1)
#       define DC_HPDx_RX_INT_STATUS                      (1 << 8)

#घोषणा DC_HOT_PLUG_DETECT1_INT_CONTROL                   0x7d08
#घोषणा DC_HOT_PLUG_DETECT2_INT_CONTROL                   0x7d18
#घोषणा DC_HOT_PLUG_DETECT3_INT_CONTROL                   0x7d2c
#       define DC_HOT_PLUG_DETECTx_INT_ACK                (1 << 0)
#       define DC_HOT_PLUG_DETECTx_INT_POLARITY           (1 << 8)
#       define DC_HOT_PLUG_DETECTx_INT_EN                 (1 << 16)
/* DCE 3.0 */
#घोषणा DC_HPD1_INT_CONTROL                               0x7d04
#घोषणा DC_HPD2_INT_CONTROL                               0x7d10
#घोषणा DC_HPD3_INT_CONTROL                               0x7d1c
#घोषणा DC_HPD4_INT_CONTROL                               0x7d28
/* DCE 3.2 */
#घोषणा DC_HPD5_INT_CONTROL                               0x7dc4
#घोषणा DC_HPD6_INT_CONTROL                               0x7df8
#       define DC_HPDx_INT_ACK                            (1 << 0)
#       define DC_HPDx_INT_POLARITY                       (1 << 8)
#       define DC_HPDx_INT_EN                             (1 << 16)
#       define DC_HPDx_RX_INT_ACK                         (1 << 20)
#       define DC_HPDx_RX_INT_EN                          (1 << 24)

/* DCE 3.0 */
#घोषणा DC_HPD1_CONTROL                                   0x7d08
#घोषणा DC_HPD2_CONTROL                                   0x7d14
#घोषणा DC_HPD3_CONTROL                                   0x7d20
#घोषणा DC_HPD4_CONTROL                                   0x7d2c
/* DCE 3.2 */
#घोषणा DC_HPD5_CONTROL                                   0x7dc8
#घोषणा DC_HPD6_CONTROL                                   0x7dfc
#       define DC_HPDx_CONNECTION_TIMER(x)                ((x) << 0)
#       define DC_HPDx_RX_INT_TIMER(x)                    ((x) << 16)
/* DCE 3.2 */
#       define DC_HPDx_EN                                 (1 << 28)

#घोषणा D1GRPH_INTERRUPT_STATUS                           0x6158
#घोषणा D2GRPH_INTERRUPT_STATUS                           0x6958
#       define DxGRPH_PFLIP_INT_OCCURRED                  (1 << 0)
#       define DxGRPH_PFLIP_INT_CLEAR                     (1 << 8)
#घोषणा D1GRPH_INTERRUPT_CONTROL                          0x615c
#घोषणा D2GRPH_INTERRUPT_CONTROL                          0x695c
#       define DxGRPH_PFLIP_INT_MASK                      (1 << 0)
#       define DxGRPH_PFLIP_INT_TYPE                      (1 << 8)

/* PCIE link stuff */
#घोषणा PCIE_LC_TRAINING_CNTL                             0xa1 /* PCIE_P */
#       define LC_POINT_7_PLUS_EN                         (1 << 6)
#घोषणा PCIE_LC_LINK_WIDTH_CNTL                           0xa2 /* PCIE_P */
#       define LC_LINK_WIDTH_SHIFT                        0
#       define LC_LINK_WIDTH_MASK                         0x7
#       define LC_LINK_WIDTH_X0                           0
#       define LC_LINK_WIDTH_X1                           1
#       define LC_LINK_WIDTH_X2                           2
#       define LC_LINK_WIDTH_X4                           3
#       define LC_LINK_WIDTH_X8                           4
#       define LC_LINK_WIDTH_X16                          6
#       define LC_LINK_WIDTH_RD_SHIFT                     4
#       define LC_LINK_WIDTH_RD_MASK                      0x70
#       define LC_RECONFIG_ARC_MISSING_ESCAPE             (1 << 7)
#       define LC_RECONFIG_NOW                            (1 << 8)
#       define LC_RENEGOTIATION_SUPPORT                   (1 << 9)
#       define LC_RENEGOTIATE_EN                          (1 << 10)
#       define LC_SHORT_RECONFIG_EN                       (1 << 11)
#       define LC_UPCONFIGURE_SUPPORT                     (1 << 12)
#       define LC_UPCONFIGURE_DIS                         (1 << 13)
#घोषणा PCIE_LC_SPEED_CNTL                                0xa4 /* PCIE_P */
#       define LC_GEN2_EN_STRAP                           (1 << 0)
#       define LC_TARGET_LINK_SPEED_OVERRIDE_EN           (1 << 1)
#       define LC_FORCE_EN_HW_SPEED_CHANGE                (1 << 5)
#       define LC_FORCE_DIS_HW_SPEED_CHANGE               (1 << 6)
#       define LC_SPEED_CHANGE_ATTEMPTS_ALLOWED_MASK      (0x3 << 8)
#       define LC_SPEED_CHANGE_ATTEMPTS_ALLOWED_SHIFT     3
#       define LC_CURRENT_DATA_RATE                       (1 << 11)
#       define LC_VOLTAGE_TIMER_SEL_MASK                  (0xf << 14)
#       define LC_CLR_FAILED_SPD_CHANGE_CNT               (1 << 21)
#       define LC_OTHER_SIDE_EVER_SENT_GEN2               (1 << 23)
#       define LC_OTHER_SIDE_SUPPORTS_GEN2                (1 << 24)
#घोषणा MM_CFGREGS_CNTL                                   0x544c
#       define MM_WR_TO_CFG_EN                            (1 << 3)
#घोषणा LINK_CNTL2                                        0x88 /* F0 */
#       define TARGET_LINK_SPEED_MASK                     (0xf << 0)
#       define SELECTABLE_DEEMPHASIS                      (1 << 6)

/* Audio */
#घोषणा AZ_HOT_PLUG_CONTROL               0x7300
#       define AZ_FORCE_CODEC_WAKE        (1 << 0)
#       define JACK_DETECTION_ENABLE      (1 << 4)
#       define UNSOLICITED_RESPONSE_ENABLE (1 << 8)
#       define CODEC_HOT_PLUG_ENABLE      (1 << 12)
#       define AUDIO_ENABLED              (1 << 31)
/* DCE3 adds */
#       define PIN0_JACK_DETECTION_ENABLE (1 << 4)
#       define PIN1_JACK_DETECTION_ENABLE (1 << 5)
#       define PIN2_JACK_DETECTION_ENABLE (1 << 6)
#       define PIN3_JACK_DETECTION_ENABLE (1 << 7)
#       define PIN0_AUDIO_ENABLED         (1 << 24)
#       define PIN1_AUDIO_ENABLED         (1 << 25)
#       define PIN2_AUDIO_ENABLED         (1 << 26)
#       define PIN3_AUDIO_ENABLED         (1 << 27)

/* Audio घड़ीs DCE 2.0/3.0 */
#घोषणा AUDIO_DTO                         0x7340
#       define AUDIO_DTO_PHASE(x)         (((x) & 0xffff) << 0)
#       define AUDIO_DTO_MODULE(x)        (((x) & 0xffff) << 16)

/* Audio घड़ीs DCE 3.2 */
#घोषणा DCCG_AUDIO_DTO0_PHASE             0x0514
#घोषणा DCCG_AUDIO_DTO0_MODULE            0x0518
#घोषणा DCCG_AUDIO_DTO0_LOAD              0x051c
#       define DTO_LOAD                   (1 << 31)
#घोषणा DCCG_AUDIO_DTO0_CNTL              0x0520
#       define DCCG_AUDIO_DTO_WALLCLOCK_RATIO(x) (((x) & 7) << 0)
#       define DCCG_AUDIO_DTO_WALLCLOCK_RATIO_MASK 7
#       define DCCG_AUDIO_DTO_WALLCLOCK_RATIO_SHIFT 0

#घोषणा DCCG_AUDIO_DTO1_PHASE             0x0524
#घोषणा DCCG_AUDIO_DTO1_MODULE            0x0528
#घोषणा DCCG_AUDIO_DTO1_LOAD              0x052c
#घोषणा DCCG_AUDIO_DTO1_CNTL              0x0530

#घोषणा DCCG_AUDIO_DTO_SELECT             0x0534

/* digital blocks */
#घोषणा TMDSA_CNTL                       0x7880
#       define TMDSA_HDMI_EN             (1 << 2)
#घोषणा LVTMA_CNTL                       0x7a80
#       define LVTMA_HDMI_EN             (1 << 2)
#घोषणा DDIA_CNTL                        0x7200
#       define DDIA_HDMI_EN              (1 << 2)
#घोषणा DIG0_CNTL                        0x75a0
#       define DIG_MODE(x)               (((x) & 7) << 8)
#       define DIG_MODE_DP               0
#       define DIG_MODE_LVDS             1
#       define DIG_MODE_TMDS_DVI         2
#       define DIG_MODE_TMDS_HDMI        3
#       define DIG_MODE_SDVO             4
#घोषणा DIG1_CNTL                        0x79a0

#घोषणा AZ_F0_CODEC_PIN0_CONTROL_CHANNEL_SPEAKER          0x71bc
#घोषणा		SPEAKER_ALLOCATION(x)			(((x) & 0x7f) << 0)
#घोषणा		SPEAKER_ALLOCATION_MASK			(0x7f << 0)
#घोषणा		SPEAKER_ALLOCATION_SHIFT		0
#घोषणा		HDMI_CONNECTION				(1 << 16)
#घोषणा		DP_CONNECTION				(1 << 17)

#घोषणा AZ_F0_CODEC_PIN0_CONTROL_AUDIO_DESCRIPTOR0        0x71c8 /* LPCM */
#घोषणा AZ_F0_CODEC_PIN0_CONTROL_AUDIO_DESCRIPTOR1        0x71cc /* AC3 */
#घोषणा AZ_F0_CODEC_PIN0_CONTROL_AUDIO_DESCRIPTOR2        0x71d0 /* MPEG1 */
#घोषणा AZ_F0_CODEC_PIN0_CONTROL_AUDIO_DESCRIPTOR3        0x71d4 /* MP3 */
#घोषणा AZ_F0_CODEC_PIN0_CONTROL_AUDIO_DESCRIPTOR4        0x71d8 /* MPEG2 */
#घोषणा AZ_F0_CODEC_PIN0_CONTROL_AUDIO_DESCRIPTOR5        0x71dc /* AAC */
#घोषणा AZ_F0_CODEC_PIN0_CONTROL_AUDIO_DESCRIPTOR6        0x71e0 /* DTS */
#घोषणा AZ_F0_CODEC_PIN0_CONTROL_AUDIO_DESCRIPTOR7        0x71e4 /* ATRAC */
#घोषणा AZ_F0_CODEC_PIN0_CONTROL_AUDIO_DESCRIPTOR8        0x71e8 /* one bit audio - leave at 0 (शेष) */
#घोषणा AZ_F0_CODEC_PIN0_CONTROL_AUDIO_DESCRIPTOR9        0x71ec /* Dolby Digital */
#घोषणा AZ_F0_CODEC_PIN0_CONTROL_AUDIO_DESCRIPTOR10       0x71f0 /* DTS-HD */
#घोषणा AZ_F0_CODEC_PIN0_CONTROL_AUDIO_DESCRIPTOR11       0x71f4 /* MAT-MLP */
#घोषणा AZ_F0_CODEC_PIN0_CONTROL_AUDIO_DESCRIPTOR12       0x71f8 /* DTS */
#घोषणा AZ_F0_CODEC_PIN0_CONTROL_AUDIO_DESCRIPTOR13       0x71fc /* WMA Pro */
#       define MAX_CHANNELS(x)                            (((x) & 0x7) << 0)
/* max channels minus one.  7 = 8 channels */
#       define SUPPORTED_FREQUENCIES(x)                   (((x) & 0xff) << 8)
#       define DESCRIPTOR_BYTE_2(x)                       (((x) & 0xff) << 16)
#       define SUPPORTED_FREQUENCIES_STEREO(x)            (((x) & 0xff) << 24) /* LPCM only */
/* SUPPORTED_FREQUENCIES, SUPPORTED_FREQUENCIES_STEREO
 * bit0 = 32 kHz
 * bit1 = 44.1 kHz
 * bit2 = 48 kHz
 * bit3 = 88.2 kHz
 * bit4 = 96 kHz
 * bit5 = 176.4 kHz
 * bit6 = 192 kHz
 */

/* rs6xx/rs740 and r6xx share the same HDMI blocks, however, rs6xx has only one
 * instance of the blocks जबतक r6xx has 2.  DCE 3.0 cards are slightly
 * dअगरferent due to the new DIG blocks, but also have 2 instances.
 * DCE 3.0 HDMI blocks are part of each DIG encoder.
 */

/* rs6xx/rs740/r6xx/dce3 */
#घोषणा HDMI0_CONTROL                0x7400
/* rs6xx/rs740/r6xx */
#       define HDMI0_ENABLE          (1 << 0)
#       define HDMI0_STREAM(x)       (((x) & 3) << 2)
#       define HDMI0_STREAM_TMDSA    0
#       define HDMI0_STREAM_LVTMA    1
#       define HDMI0_STREAM_DVOA     2
#       define HDMI0_STREAM_DDIA     3
/* rs6xx/r6xx/dce3 */
#       define HDMI0_ERROR_ACK       (1 << 8)
#       define HDMI0_ERROR_MASK      (1 << 9)
#घोषणा HDMI0_STATUS                 0x7404
#       define HDMI0_ACTIVE_AVMUTE   (1 << 0)
#       define HDMI0_AUDIO_ENABLE    (1 << 4)
#       define HDMI0_AZ_FORMAT_WTRIG     (1 << 28)
#       define HDMI0_AZ_FORMAT_WTRIG_INT (1 << 29)
#घोषणा HDMI0_AUDIO_PACKET_CONTROL   0x7408
#       define HDMI0_AUDIO_SAMPLE_SEND  (1 << 0)
#       define HDMI0_AUDIO_DELAY_EN(x)  (((x) & 3) << 4)
#       define HDMI0_AUDIO_DELAY_EN_MASK	(3 << 4)
#       define HDMI0_AUDIO_SEND_MAX_PACKETS  (1 << 8)
#       define HDMI0_AUDIO_TEST_EN         (1 << 12)
#       define HDMI0_AUDIO_PACKETS_PER_LINE(x)  (((x) & 0x1f) << 16)
#       define HDMI0_AUDIO_PACKETS_PER_LINE_MASK	(0x1f << 16)
#       define HDMI0_AUDIO_CHANNEL_SWAP    (1 << 24)
#       define HDMI0_60958_CS_UPDATE       (1 << 26)
#       define HDMI0_AZ_FORMAT_WTRIG_MASK  (1 << 28)
#       define HDMI0_AZ_FORMAT_WTRIG_ACK   (1 << 29)
#घोषणा HDMI0_AUDIO_CRC_CONTROL      0x740c
#       define HDMI0_AUDIO_CRC_EN    (1 << 0)
#घोषणा DCE3_HDMI0_ACR_PACKET_CONTROL	0x740c
#घोषणा HDMI0_VBI_PACKET_CONTROL     0x7410
#       define HDMI0_शून्य_SEND       (1 << 0)
#       define HDMI0_GC_SEND         (1 << 4)
#       define HDMI0_GC_CONT         (1 << 5) /* 0 - once; 1 - every frame */
#घोषणा HDMI0_INFOFRAME_CONTROL0     0x7414
#       define HDMI0_AVI_INFO_SEND   (1 << 0)
#       define HDMI0_AVI_INFO_CONT   (1 << 1)
#       define HDMI0_AUDIO_INFO_SEND (1 << 4)
#       define HDMI0_AUDIO_INFO_CONT (1 << 5)
#       define HDMI0_AUDIO_INFO_SOURCE (1 << 6) /* 0 - sound block; 1 - hdmi regs */
#       define HDMI0_AUDIO_INFO_UPDATE (1 << 7)
#       define HDMI0_MPEG_INFO_SEND  (1 << 8)
#       define HDMI0_MPEG_INFO_CONT  (1 << 9)
#       define HDMI0_MPEG_INFO_UPDATE  (1 << 10)
#घोषणा HDMI0_INFOFRAME_CONTROL1     0x7418
#       define HDMI0_AVI_INFO_LINE(x)  (((x) & 0x3f) << 0)
#       define HDMI0_AVI_INFO_LINE_MASK		(0x3f << 0)
#       define HDMI0_AUDIO_INFO_LINE(x)  (((x) & 0x3f) << 8)
#       define HDMI0_AUDIO_INFO_LINE_MASK	(0x3f << 8)
#       define HDMI0_MPEG_INFO_LINE(x)  (((x) & 0x3f) << 16)
#घोषणा HDMI0_GENERIC_PACKET_CONTROL 0x741c
#       define HDMI0_GENERIC0_SEND   (1 << 0)
#       define HDMI0_GENERIC0_CONT   (1 << 1)
#       define HDMI0_GENERIC0_UPDATE (1 << 2)
#       define HDMI0_GENERIC1_SEND   (1 << 4)
#       define HDMI0_GENERIC1_CONT   (1 << 5)
#       define HDMI0_GENERIC0_LINE(x)  (((x) & 0x3f) << 16)
#       define HDMI0_GENERIC0_LINE_MASK		(0x3f << 16)
#       define HDMI0_GENERIC1_LINE(x)  (((x) & 0x3f) << 24)
#       define HDMI0_GENERIC1_LINE_MASK		(0x3f << 24)
#घोषणा HDMI0_GC                     0x7428
#       define HDMI0_GC_AVMUTE       (1 << 0)
#घोषणा HDMI0_AVI_INFO0              0x7454
#       define HDMI0_AVI_INFO_CHECKSUM(x)  (((x) & 0xff) << 0)
#       define HDMI0_AVI_INFO_S(x)   (((x) & 3) << 8)
#       define HDMI0_AVI_INFO_B(x)   (((x) & 3) << 10)
#       define HDMI0_AVI_INFO_A(x)   (((x) & 1) << 12)
#       define HDMI0_AVI_INFO_Y(x)   (((x) & 3) << 13)
#       define HDMI0_AVI_INFO_Y_RGB       0
#       define HDMI0_AVI_INFO_Y_YCBCR422  1
#       define HDMI0_AVI_INFO_Y_YCBCR444  2
#       define HDMI0_AVI_INFO_Y_A_B_S(x)   (((x) & 0xff) << 8)
#       define HDMI0_AVI_INFO_R(x)   (((x) & 0xf) << 16)
#       define HDMI0_AVI_INFO_M(x)   (((x) & 0x3) << 20)
#       define HDMI0_AVI_INFO_C(x)   (((x) & 0x3) << 22)
#       define HDMI0_AVI_INFO_C_M_R(x)   (((x) & 0xff) << 16)
#       define HDMI0_AVI_INFO_SC(x)  (((x) & 0x3) << 24)
#       define HDMI0_AVI_INFO_ITC_EC_Q_SC(x)  (((x) & 0xff) << 24)
#घोषणा HDMI0_AVI_INFO1              0x7458
#       define HDMI0_AVI_INFO_VIC(x) (((x) & 0x7f) << 0) /* करोn't use avi infoframe v1 */
#       define HDMI0_AVI_INFO_PR(x)  (((x) & 0xf) << 8) /* करोn't use avi infoframe v1 */
#       define HDMI0_AVI_INFO_TOP(x) (((x) & 0xffff) << 16)
#घोषणा HDMI0_AVI_INFO2              0x745c
#       define HDMI0_AVI_INFO_BOTTOM(x)  (((x) & 0xffff) << 0)
#       define HDMI0_AVI_INFO_LEFT(x)    (((x) & 0xffff) << 16)
#घोषणा HDMI0_AVI_INFO3              0x7460
#       define HDMI0_AVI_INFO_RIGHT(x)    (((x) & 0xffff) << 0)
#       define HDMI0_AVI_INFO_VERSION(x)  (((x) & 3) << 24)
#घोषणा HDMI0_MPEG_INFO0             0x7464
#       define HDMI0_MPEG_INFO_CHECKSUM(x)  (((x) & 0xff) << 0)
#       define HDMI0_MPEG_INFO_MB0(x)  (((x) & 0xff) << 8)
#       define HDMI0_MPEG_INFO_MB1(x)  (((x) & 0xff) << 16)
#       define HDMI0_MPEG_INFO_MB2(x)  (((x) & 0xff) << 24)
#घोषणा HDMI0_MPEG_INFO1             0x7468
#       define HDMI0_MPEG_INFO_MB3(x)  (((x) & 0xff) << 0)
#       define HDMI0_MPEG_INFO_MF(x)   (((x) & 3) << 8)
#       define HDMI0_MPEG_INFO_FR(x)   (((x) & 1) << 12)
#घोषणा HDMI0_GENERIC0_HDR           0x746c
#घोषणा HDMI0_GENERIC0_0             0x7470
#घोषणा HDMI0_GENERIC0_1             0x7474
#घोषणा HDMI0_GENERIC0_2             0x7478
#घोषणा HDMI0_GENERIC0_3             0x747c
#घोषणा HDMI0_GENERIC0_4             0x7480
#घोषणा HDMI0_GENERIC0_5             0x7484
#घोषणा HDMI0_GENERIC0_6             0x7488
#घोषणा HDMI0_GENERIC1_HDR           0x748c
#घोषणा HDMI0_GENERIC1_0             0x7490
#घोषणा HDMI0_GENERIC1_1             0x7494
#घोषणा HDMI0_GENERIC1_2             0x7498
#घोषणा HDMI0_GENERIC1_3             0x749c
#घोषणा HDMI0_GENERIC1_4             0x74a0
#घोषणा HDMI0_GENERIC1_5             0x74a4
#घोषणा HDMI0_GENERIC1_6             0x74a8
#घोषणा HDMI0_ACR_32_0               0x74ac
#       define HDMI0_ACR_CTS_32(x)   (((x) & 0xfffff) << 12)
#       define HDMI0_ACR_CTS_32_MASK		(0xfffff << 12)
#घोषणा HDMI0_ACR_32_1               0x74b0
#       define HDMI0_ACR_N_32(x)   (((x) & 0xfffff) << 0)
#       define HDMI0_ACR_N_32_MASK		(0xfffff << 0)
#घोषणा HDMI0_ACR_44_0               0x74b4
#       define HDMI0_ACR_CTS_44(x)   (((x) & 0xfffff) << 12)
#       define HDMI0_ACR_CTS_44_MASK		(0xfffff << 12)
#घोषणा HDMI0_ACR_44_1               0x74b8
#       define HDMI0_ACR_N_44(x)   (((x) & 0xfffff) << 0)
#       define HDMI0_ACR_N_44_MASK		(0xfffff << 0)
#घोषणा HDMI0_ACR_48_0               0x74bc
#       define HDMI0_ACR_CTS_48(x)   (((x) & 0xfffff) << 12)
#       define HDMI0_ACR_CTS_48_MASK		(0xfffff << 12)
#घोषणा HDMI0_ACR_48_1               0x74c0
#       define HDMI0_ACR_N_48(x)   (((x) & 0xfffff) << 0)
#       define HDMI0_ACR_N_48_MASK		(0xfffff << 0)
#घोषणा HDMI0_ACR_STATUS_0           0x74c4
#घोषणा HDMI0_ACR_STATUS_1           0x74c8
#घोषणा HDMI0_AUDIO_INFO0            0x74cc
#       define HDMI0_AUDIO_INFO_CHECKSUM(x)  (((x) & 0xff) << 0)
#       define HDMI0_AUDIO_INFO_CC(x)  (((x) & 7) << 8)
#घोषणा HDMI0_AUDIO_INFO1            0x74d0
#       define HDMI0_AUDIO_INFO_CA(x)  (((x) & 0xff) << 0)
#       define HDMI0_AUDIO_INFO_LSV(x)  (((x) & 0xf) << 11)
#       define HDMI0_AUDIO_INFO_DM_INH(x)  (((x) & 1) << 15)
#       define HDMI0_AUDIO_INFO_DM_INH_LSV(x)  (((x) & 0xff) << 8)
#घोषणा HDMI0_60958_0                0x74d4
#       define HDMI0_60958_CS_A(x)   (((x) & 1) << 0)
#       define HDMI0_60958_CS_B(x)   (((x) & 1) << 1)
#       define HDMI0_60958_CS_C(x)   (((x) & 1) << 2)
#       define HDMI0_60958_CS_D(x)   (((x) & 3) << 3)
#       define HDMI0_60958_CS_MODE(x)   (((x) & 3) << 6)
#       define HDMI0_60958_CS_CATEGORY_CODE(x)      (((x) & 0xff) << 8)
#       define HDMI0_60958_CS_SOURCE_NUMBER(x)      (((x) & 0xf) << 16)
#       define HDMI0_60958_CS_CHANNEL_NUMBER_L(x)   (((x) & 0xf) << 20)
#       define HDMI0_60958_CS_CHANNEL_NUMBER_L_MASK	(0xf << 20)
#       define HDMI0_60958_CS_SAMPLING_FREQUENCY(x) (((x) & 0xf) << 24)
#       define HDMI0_60958_CS_CLOCK_ACCURACY(x)     (((x) & 3) << 28)
#       define HDMI0_60958_CS_CLOCK_ACCURACY_MASK	(3 << 28)
#घोषणा HDMI0_60958_1                0x74d8
#       define HDMI0_60958_CS_WORD_LENGTH(x)        (((x) & 0xf) << 0)
#       define HDMI0_60958_CS_ORIGINAL_SAMPLING_FREQUENCY(x)   (((x) & 0xf) << 4)
#       define HDMI0_60958_CS_VALID_L(x)   (((x) & 1) << 16)
#       define HDMI0_60958_CS_VALID_R(x)   (((x) & 1) << 18)
#       define HDMI0_60958_CS_CHANNEL_NUMBER_R(x)   (((x) & 0xf) << 20)
#       define HDMI0_60958_CS_CHANNEL_NUMBER_R_MASK	(0xf << 20)
#घोषणा HDMI0_ACR_PACKET_CONTROL     0x74dc
#       define HDMI0_ACR_SEND        (1 << 0)
#       define HDMI0_ACR_CONT        (1 << 1)
#       define HDMI0_ACR_SELECT(x)   (((x) & 3) << 4)
#       define HDMI0_ACR_HW          0
#       define HDMI0_ACR_32          1
#       define HDMI0_ACR_44          2
#       define HDMI0_ACR_48          3
#       define HDMI0_ACR_SOURCE      (1 << 8) /* 0 - hw; 1 - cts value */
#       define HDMI0_ACR_AUTO_SEND   (1 << 12)
#घोषणा DCE3_HDMI0_AUDIO_CRC_CONTROL	0x74dc
#घोषणा HDMI0_RAMP_CONTROL0          0x74e0
#       define HDMI0_RAMP_MAX_COUNT(x)   (((x) & 0xffffff) << 0)
#घोषणा HDMI0_RAMP_CONTROL1          0x74e4
#       define HDMI0_RAMP_MIN_COUNT(x)   (((x) & 0xffffff) << 0)
#घोषणा HDMI0_RAMP_CONTROL2          0x74e8
#       define HDMI0_RAMP_INC_COUNT(x)   (((x) & 0xffffff) << 0)
#घोषणा HDMI0_RAMP_CONTROL3          0x74ec
#       define HDMI0_RAMP_DEC_COUNT(x)   (((x) & 0xffffff) << 0)
/* HDMI0_60958_2 is r7xx only */
#घोषणा HDMI0_60958_2                0x74f0
#       define HDMI0_60958_CS_CHANNEL_NUMBER_2(x)   (((x) & 0xf) << 0)
#       define HDMI0_60958_CS_CHANNEL_NUMBER_3(x)   (((x) & 0xf) << 4)
#       define HDMI0_60958_CS_CHANNEL_NUMBER_4(x)   (((x) & 0xf) << 8)
#       define HDMI0_60958_CS_CHANNEL_NUMBER_5(x)   (((x) & 0xf) << 12)
#       define HDMI0_60958_CS_CHANNEL_NUMBER_6(x)   (((x) & 0xf) << 16)
#       define HDMI0_60958_CS_CHANNEL_NUMBER_7(x)   (((x) & 0xf) << 20)
/* r6xx only; second instance starts at 0x7700 */
#घोषणा HDMI1_CONTROL                0x7700
#घोषणा HDMI1_STATUS                 0x7704
#घोषणा HDMI1_AUDIO_PACKET_CONTROL   0x7708
/* DCE3; second instance starts at 0x7800 NOT 0x7700 */
#घोषणा DCE3_HDMI1_CONTROL                0x7800
#घोषणा DCE3_HDMI1_STATUS                 0x7804
#घोषणा DCE3_HDMI1_AUDIO_PACKET_CONTROL   0x7808
/* DCE3.2 (क्रम पूर्णांकerrupts) */
#घोषणा AFMT_STATUS                          0x7600
#       define AFMT_AUDIO_ENABLE             (1 << 4)
#       define AFMT_AZ_FORMAT_WTRIG          (1 << 28)
#       define AFMT_AZ_FORMAT_WTRIG_INT      (1 << 29)
#       define AFMT_AZ_AUDIO_ENABLE_CHG      (1 << 30)
#घोषणा AFMT_AUDIO_PACKET_CONTROL            0x7604
#       define AFMT_AUDIO_SAMPLE_SEND        (1 << 0)
#       define AFMT_AUDIO_TEST_EN            (1 << 12)
#       define AFMT_AUDIO_CHANNEL_SWAP       (1 << 24)
#       define AFMT_60958_CS_UPDATE          (1 << 26)
#       define AFMT_AZ_AUDIO_ENABLE_CHG_MASK (1 << 27)
#       define AFMT_AZ_FORMAT_WTRIG_MASK     (1 << 28)
#       define AFMT_AZ_FORMAT_WTRIG_ACK      (1 << 29)
#       define AFMT_AZ_AUDIO_ENABLE_CHG_ACK  (1 << 30)

/* DCE3 FMT blocks */
#घोषणा FMT_CONTROL                          0x6700
#       define FMT_PIXEL_ENCODING            (1 << 16)
        /* 0 = RGB 4:4:4 or YCbCr 4:4:4, 1 = YCbCr 4:2:2 */
#घोषणा FMT_BIT_DEPTH_CONTROL                0x6710
#       define FMT_TRUNCATE_EN               (1 << 0)
#       define FMT_TRUNCATE_DEPTH            (1 << 4)
#       define FMT_SPATIAL_DITHER_EN         (1 << 8)
#       define FMT_SPATIAL_DITHER_MODE(x)    ((x) << 9)
#       define FMT_SPATIAL_DITHER_DEPTH      (1 << 12)
#       define FMT_FRAME_RANDOM_ENABLE       (1 << 13)
#       define FMT_RGB_RANDOM_ENABLE         (1 << 14)
#       define FMT_HIGHPASS_RANDOM_ENABLE    (1 << 15)
#       define FMT_TEMPORAL_DITHER_EN        (1 << 16)
#       define FMT_TEMPORAL_DITHER_DEPTH     (1 << 20)
#       define FMT_TEMPORAL_DITHER_OFFSET(x) ((x) << 21)
#       define FMT_TEMPORAL_LEVEL            (1 << 24)
#       define FMT_TEMPORAL_DITHER_RESET     (1 << 25)
#       define FMT_25FRC_SEL(x)              ((x) << 26)
#       define FMT_50FRC_SEL(x)              ((x) << 28)
#       define FMT_75FRC_SEL(x)              ((x) << 30)
#घोषणा FMT_CLAMP_CONTROL                    0x672c
#       define FMT_CLAMP_DATA_EN             (1 << 0)
#       define FMT_CLAMP_COLOR_FORMAT(x)     ((x) << 16)
#       define FMT_CLAMP_6BPC                0
#       define FMT_CLAMP_8BPC                1
#       define FMT_CLAMP_10BPC               2

/* Power management */
#घोषणा CG_SPLL_FUNC_CNTL                                 0x600
#       define SPLL_RESET                                (1 << 0)
#       define SPLL_SLEEP                                (1 << 1)
#       define SPLL_REF_DIV(x)                           ((x) << 2)
#       define SPLL_REF_DIV_MASK                         (7 << 2)
#       define SPLL_FB_DIV(x)                            ((x) << 5)
#       define SPLL_FB_DIV_MASK                          (0xff << 5)
#       define SPLL_PULSEEN                              (1 << 13)
#       define SPLL_PULSENUM(x)                          ((x) << 14)
#       define SPLL_PULSENUM_MASK                        (3 << 14)
#       define SPLL_SW_HILEN(x)                          ((x) << 16)
#       define SPLL_SW_HILEN_MASK                        (0xf << 16)
#       define SPLL_SW_LOLEN(x)                          ((x) << 20)
#       define SPLL_SW_LOLEN_MASK                        (0xf << 20)
#       define SPLL_DIVEN                                (1 << 24)
#       define SPLL_BYPASS_EN                            (1 << 25)
#       define SPLL_CHG_STATUS                           (1 << 29)
#       define SPLL_CTLREQ                               (1 << 30)
#       define SPLL_CTLACK                               (1 << 31)

#घोषणा GENERAL_PWRMGT                                    0x618
#       define GLOBAL_PWRMGT_EN                           (1 << 0)
#       define STATIC_PM_EN                               (1 << 1)
#       define MOBILE_SU                                  (1 << 2)
#       define THERMAL_PROTECTION_DIS                     (1 << 3)
#       define THERMAL_PROTECTION_TYPE                    (1 << 4)
#       define ENABLE_GEN2PCIE                            (1 << 5)
#       define SW_GPIO_INDEX(x)                           ((x) << 6)
#       define SW_GPIO_INDEX_MASK                         (3 << 6)
#       define LOW_VOLT_D2_ACPI                           (1 << 8)
#       define LOW_VOLT_D3_ACPI                           (1 << 9)
#       define VOLT_PWRMGT_EN                             (1 << 10)
#घोषणा CG_TPC                                            0x61c
#       define TPCC(x)                                    ((x) << 0)
#       define TPCC_MASK                                  (0x7fffff << 0)
#       define TPU(x)                                     ((x) << 23)
#       define TPU_MASK                                   (0x1f << 23)
#घोषणा SCLK_PWRMGT_CNTL                                  0x620
#       define SCLK_PWRMGT_OFF                            (1 << 0)
#       define SCLK_TURNOFF                               (1 << 1)
#       define SPLL_TURNOFF                               (1 << 2)
#       define SU_SCLK_USE_BCLK                           (1 << 3)
#       define DYNAMIC_GFX_ISLAND_PWR_DOWN                (1 << 4)
#       define DYNAMIC_GFX_ISLAND_PWR_LP                  (1 << 5)
#       define CLK_TURN_ON_STAGGER                        (1 << 6)
#       define CLK_TURN_OFF_STAGGER                       (1 << 7)
#       define FIR_FORCE_TREND_SEL                        (1 << 8)
#       define FIR_TREND_MODE                             (1 << 9)
#       define DYN_GFX_CLK_OFF_EN                         (1 << 10)
#       define VDDC3D_TURNOFF_D1                          (1 << 11)
#       define VDDC3D_TURNOFF_D2                          (1 << 12)
#       define VDDC3D_TURNOFF_D3                          (1 << 13)
#       define SPLL_TURNOFF_D2                            (1 << 14)
#       define SCLK_LOW_D1                                (1 << 15)
#       define DYN_GFX_CLK_OFF_MC_EN                      (1 << 16)
#घोषणा MCLK_PWRMGT_CNTL                                  0x624
#       define MPLL_PWRMGT_OFF                            (1 << 0)
#       define YCLK_TURNOFF                               (1 << 1)
#       define MPLL_TURNOFF                               (1 << 2)
#       define SU_MCLK_USE_BCLK                           (1 << 3)
#       define DLL_READY                                  (1 << 4)
#       define MC_BUSY                                    (1 << 5)
#       define MC_INT_CNTL                                (1 << 7)
#       define MRDCKA_SLEEP                               (1 << 8)
#       define MRDCKB_SLEEP                               (1 << 9)
#       define MRDCKC_SLEEP                               (1 << 10)
#       define MRDCKD_SLEEP                               (1 << 11)
#       define MRDCKE_SLEEP                               (1 << 12)
#       define MRDCKF_SLEEP                               (1 << 13)
#       define MRDCKG_SLEEP                               (1 << 14)
#       define MRDCKH_SLEEP                               (1 << 15)
#       define MRDCKA_RESET                               (1 << 16)
#       define MRDCKB_RESET                               (1 << 17)
#       define MRDCKC_RESET                               (1 << 18)
#       define MRDCKD_RESET                               (1 << 19)
#       define MRDCKE_RESET                               (1 << 20)
#       define MRDCKF_RESET                               (1 << 21)
#       define MRDCKG_RESET                               (1 << 22)
#       define MRDCKH_RESET                               (1 << 23)
#       define DLL_READY_READ                             (1 << 24)
#       define USE_DISPLAY_GAP                            (1 << 25)
#       define USE_DISPLAY_URGENT_NORMAL                  (1 << 26)
#       define USE_DISPLAY_GAP_CTXSW                      (1 << 27)
#       define MPLL_TURNOFF_D2                            (1 << 28)
#       define USE_DISPLAY_URGENT_CTXSW                   (1 << 29)

#घोषणा MPLL_TIME                                         0x634
#       define MPLL_LOCK_TIME(x)                          ((x) << 0)
#       define MPLL_LOCK_TIME_MASK                        (0xffff << 0)
#       define MPLL_RESET_TIME(x)                         ((x) << 16)
#       define MPLL_RESET_TIME_MASK                       (0xffff << 16)

#घोषणा SCLK_FREQ_SETTING_STEP_0_PART1                    0x648
#       define STEP_0_SPLL_POST_DIV(x)                    ((x) << 0)
#       define STEP_0_SPLL_POST_DIV_MASK                  (0xff << 0)
#       define STEP_0_SPLL_FB_DIV(x)                      ((x) << 8)
#       define STEP_0_SPLL_FB_DIV_MASK                    (0xff << 8)
#       define STEP_0_SPLL_REF_DIV(x)                     ((x) << 16)
#       define STEP_0_SPLL_REF_DIV_MASK                   (7 << 16)
#       define STEP_0_SPLL_STEP_TIME(x)                   ((x) << 19)
#       define STEP_0_SPLL_STEP_TIME_MASK                 (0x1fff << 19)
#घोषणा SCLK_FREQ_SETTING_STEP_0_PART2                    0x64c
#       define STEP_0_PULSE_HIGH_CNT(x)                   ((x) << 0)
#       define STEP_0_PULSE_HIGH_CNT_MASK                 (0x1ff << 0)
#       define STEP_0_POST_DIV_EN                         (1 << 9)
#       define STEP_0_SPLL_STEP_ENABLE                    (1 << 30)
#       define STEP_0_SPLL_ENTRY_VALID                    (1 << 31)

#घोषणा VID_RT                                            0x6f8
#       define VID_CRT(x)                                 ((x) << 0)
#       define VID_CRT_MASK                               (0x1fff << 0)
#       define VID_CRTU(x)                                ((x) << 13)
#       define VID_CRTU_MASK                              (7 << 13)
#       define SSTU(x)                                    ((x) << 16)
#       define SSTU_MASK                                  (7 << 16)
#घोषणा CTXSW_PROखाता_INDEX                               0x6fc
#       define CTXSW_FREQ_VIDS_CFG_INDEX(x)               ((x) << 0)
#       define CTXSW_FREQ_VIDS_CFG_INDEX_MASK             (3 << 0)
#       define CTXSW_FREQ_VIDS_CFG_INDEX_SHIFT            0
#       define CTXSW_FREQ_MCLK_CFG_INDEX(x)               ((x) << 2)
#       define CTXSW_FREQ_MCLK_CFG_INDEX_MASK             (3 << 2)
#       define CTXSW_FREQ_MCLK_CFG_INDEX_SHIFT            2
#       define CTXSW_FREQ_SCLK_CFG_INDEX(x)               ((x) << 4)
#       define CTXSW_FREQ_SCLK_CFG_INDEX_MASK             (0x1f << 4)
#       define CTXSW_FREQ_SCLK_CFG_INDEX_SHIFT            4
#       define CTXSW_FREQ_STATE_SPLL_RESET_EN             (1 << 9)
#       define CTXSW_FREQ_STATE_ENABLE                    (1 << 10)
#       define CTXSW_FREQ_DISPLAY_WATERMARK               (1 << 11)
#       define CTXSW_FREQ_GEN2PCIE_VOLT                   (1 << 12)

#घोषणा TARGET_AND_CURRENT_PROखाता_INDEX                  0x70c
#       define TARGET_PROखाता_INDEX_MASK                  (3 << 0)
#       define TARGET_PROखाता_INDEX_SHIFT                 0
#       define CURRENT_PROखाता_INDEX_MASK                 (3 << 2)
#       define CURRENT_PROखाता_INDEX_SHIFT                2
#       define DYN_PWR_ENTER_INDEX(x)                     ((x) << 4)
#       define DYN_PWR_ENTER_INDEX_MASK                   (3 << 4)
#       define DYN_PWR_ENTER_INDEX_SHIFT                  4
#       define CURR_MCLK_INDEX_MASK                       (3 << 6)
#       define CURR_MCLK_INDEX_SHIFT                      6
#       define CURR_SCLK_INDEX_MASK                       (0x1f << 8)
#       define CURR_SCLK_INDEX_SHIFT                      8
#       define CURR_VID_INDEX_MASK                        (3 << 13)
#       define CURR_VID_INDEX_SHIFT                       13

#घोषणा LOWER_GPIO_ENABLE                                 0x710
#घोषणा UPPER_GPIO_ENABLE                                 0x714
#घोषणा CTXSW_VID_LOWER_GPIO_CNTL                         0x718

#घोषणा VID_UPPER_GPIO_CNTL                               0x740
#घोषणा CG_CTX_CGTT3D_R                                   0x744
#       define PHC(x)                                     ((x) << 0)
#       define PHC_MASK                                   (0x1ff << 0)
#       define SDC(x)                                     ((x) << 9)
#       define SDC_MASK                                   (0x3fff << 9)
#घोषणा CG_VDDC3D_OOR                                     0x748
#       define SU(x)                                      ((x) << 23)
#       define SU_MASK                                    (0xf << 23)
#घोषणा CG_FTV                                            0x74c
#घोषणा CG_FFCT_0                                         0x750
#       define UTC_0(x)                                   ((x) << 0)
#       define UTC_0_MASK                                 (0x3ff << 0)
#       define DTC_0(x)                                   ((x) << 10)
#       define DTC_0_MASK                                 (0x3ff << 10)

#घोषणा CG_BSP                                            0x78c
#       define BSP(x)                                     ((x) << 0)
#       define BSP_MASK                                   (0xffff << 0)
#       define BSU(x)                                     ((x) << 16)
#       define BSU_MASK                                   (0xf << 16)
#घोषणा CG_RT                                             0x790
#       define FLS(x)                                     ((x) << 0)
#       define FLS_MASK                                   (0xffff << 0)
#       define FMS(x)                                     ((x) << 16)
#       define FMS_MASK                                   (0xffff << 16)
#घोषणा CG_LT                                             0x794
#       define FHS(x)                                     ((x) << 0)
#       define FHS_MASK                                   (0xffff << 0)
#घोषणा CG_GIT                                            0x798
#       define CG_GICST(x)                                ((x) << 0)
#       define CG_GICST_MASK                              (0xffff << 0)
#       define CG_GIPOT(x)                                ((x) << 16)
#       define CG_GIPOT_MASK                              (0xffff << 16)

#घोषणा CG_SSP                                            0x7a8
#       define CG_SST(x)                                  ((x) << 0)
#       define CG_SST_MASK                                (0xffff << 0)
#       define CG_SSTU(x)                                 ((x) << 16)
#       define CG_SSTU_MASK                               (0xf << 16)

#घोषणा CG_RLC_REQ_AND_RSP                                0x7c4
#       define RLC_CG_REQ_TYPE_MASK                       0xf
#       define RLC_CG_REQ_TYPE_SHIFT                      0
#       define CG_RLC_RSP_TYPE_MASK                       0xf0
#       define CG_RLC_RSP_TYPE_SHIFT                      4

#घोषणा CG_FC_T                                           0x7cc
#       define FC_T(x)                                    ((x) << 0)
#       define FC_T_MASK                                  (0xffff << 0)
#       define FC_TU(x)                                   ((x) << 16)
#       define FC_TU_MASK                                 (0x1f << 16)

#घोषणा GPIOPAD_MASK                                      0x1798
#घोषणा GPIOPAD_A                                         0x179c
#घोषणा GPIOPAD_EN                                        0x17a0

#घोषणा GRBM_PWR_CNTL                                     0x800c
#       define REQ_TYPE_MASK                              0xf
#       define REQ_TYPE_SHIFT                             0
#       define RSP_TYPE_MASK                              0xf0
#       define RSP_TYPE_SHIFT                             4

/*
 * UVD
 */
#घोषणा UVD_SEMA_ADDR_LOW				0xef00
#घोषणा UVD_SEMA_ADDR_HIGH				0xef04
#घोषणा UVD_SEMA_CMD					0xef08

#घोषणा UVD_GPCOM_VCPU_CMD				0xef0c
#घोषणा UVD_GPCOM_VCPU_DATA0				0xef10
#घोषणा UVD_GPCOM_VCPU_DATA1				0xef14
#घोषणा UVD_ENGINE_CNTL					0xef18
#घोषणा UVD_NO_OP					0xeffc

#घोषणा UVD_SEMA_CNTL					0xf400
#घोषणा UVD_RB_ARB_CTRL					0xf480

#घोषणा UVD_LMI_EXT40_ADDR				0xf498
#घोषणा UVD_CGC_GATE					0xf4a8
#घोषणा UVD_LMI_CTRL2					0xf4f4
#घोषणा UVD_MASTINT_EN					0xf500
#घोषणा UVD_FW_START					0xf51C
#घोषणा UVD_LMI_ADDR_EXT				0xf594
#घोषणा UVD_LMI_CTRL					0xf598
#घोषणा UVD_LMI_SWAP_CNTL				0xf5b4
#घोषणा UVD_MP_SWAP_CNTL				0xf5bC
#घोषणा UVD_MPC_CNTL					0xf5dC
#घोषणा UVD_MPC_SET_MUXA0				0xf5e4
#घोषणा UVD_MPC_SET_MUXA1				0xf5e8
#घोषणा UVD_MPC_SET_MUXB0				0xf5eC
#घोषणा UVD_MPC_SET_MUXB1				0xf5f0
#घोषणा UVD_MPC_SET_MUX					0xf5f4
#घोषणा UVD_MPC_SET_ALU					0xf5f8

#घोषणा UVD_VCPU_CACHE_OFFSET0				0xf608
#घोषणा UVD_VCPU_CACHE_SIZE0				0xf60c
#घोषणा UVD_VCPU_CACHE_OFFSET1				0xf610
#घोषणा UVD_VCPU_CACHE_SIZE1				0xf614
#घोषणा UVD_VCPU_CACHE_OFFSET2				0xf618
#घोषणा UVD_VCPU_CACHE_SIZE2				0xf61c

#घोषणा UVD_VCPU_CNTL					0xf660
#घोषणा UVD_SOFT_RESET					0xf680
#घोषणा		RBC_SOFT_RESET					(1<<0)
#घोषणा		LBSI_SOFT_RESET					(1<<1)
#घोषणा		LMI_SOFT_RESET					(1<<2)
#घोषणा		VCPU_SOFT_RESET					(1<<3)
#घोषणा		CSM_SOFT_RESET					(1<<5)
#घोषणा		CXW_SOFT_RESET					(1<<6)
#घोषणा		TAP_SOFT_RESET					(1<<7)
#घोषणा		LMI_UMC_SOFT_RESET				(1<<13)
#घोषणा UVD_RBC_IB_BASE					0xf684
#घोषणा UVD_RBC_IB_SIZE					0xf688
#घोषणा UVD_RBC_RB_BASE					0xf68c
#घोषणा UVD_RBC_RB_RPTR					0xf690
#घोषणा UVD_RBC_RB_WPTR					0xf694
#घोषणा UVD_RBC_RB_WPTR_CNTL				0xf698

#घोषणा UVD_STATUS					0xf6bc

#घोषणा UVD_SEMA_TIMEOUT_STATUS				0xf6c0
#घोषणा UVD_SEMA_WAIT_INCOMPLETE_TIMEOUT_CNTL		0xf6c4
#घोषणा UVD_SEMA_WAIT_FAULT_TIMEOUT_CNTL		0xf6c8
#घोषणा UVD_SEMA_SIGNAL_INCOMPLETE_TIMEOUT_CNTL		0xf6cc

#घोषणा UVD_RBC_RB_CNTL					0xf6a4
#घोषणा UVD_RBC_RB_RPTR_ADDR				0xf6a8

#घोषणा UVD_CONTEXT_ID					0xf6f4

/* rs780 only */
#घोषणा	GFX_MACRO_BYPASS_CNTL				0x30c0
#घोषणा		SPLL_BYPASS_CNTL			(1 << 0)
#घोषणा		UPLL_BYPASS_CNTL			(1 << 1)

#घोषणा CG_UPLL_FUNC_CNTL				0x7e0
#	define UPLL_RESET_MASK				0x00000001
#	define UPLL_SLEEP_MASK				0x00000002
#	define UPLL_BYPASS_EN_MASK			0x00000004
#	define UPLL_CTLREQ_MASK				0x00000008
#	define UPLL_FB_DIV(x)				((x) << 4)
#	define UPLL_FB_DIV_MASK				0x0000FFF0
#	define UPLL_REF_DIV(x)				((x) << 16)
#	define UPLL_REF_DIV_MASK			0x003F0000
#	define UPLL_REFCLK_SRC_SEL_MASK			0x20000000
#	define UPLL_CTLACK_MASK				0x40000000
#	define UPLL_CTLACK2_MASK			0x80000000
#घोषणा CG_UPLL_FUNC_CNTL_2				0x7e4
#	define UPLL_SW_HILEN(x)				((x) << 0)
#	define UPLL_SW_LOLEN(x)				((x) << 4)
#	define UPLL_SW_HILEN2(x)			((x) << 8)
#	define UPLL_SW_LOLEN2(x)			((x) << 12)
#	define UPLL_DIVEN_MASK				0x00010000
#	define UPLL_DIVEN2_MASK				0x00020000
#	define UPLL_SW_MASK				0x0003FFFF
#	define VCLK_SRC_SEL(x)				((x) << 20)
#	define VCLK_SRC_SEL_MASK			0x01F00000
#	define DCLK_SRC_SEL(x)				((x) << 25)
#	define DCLK_SRC_SEL_MASK			0x3E000000

/*
 * PM4
 */
#घोषणा PACKET0(reg, n)	((RADEON_PACKET_TYPE0 << 30) |			\
			 (((reg) >> 2) & 0xFFFF) |			\
			 ((n) & 0x3FFF) << 16)
#घोषणा PACKET3(op, n)	((RADEON_PACKET_TYPE3 << 30) |			\
			 (((op) & 0xFF) << 8) |				\
			 ((n) & 0x3FFF) << 16)

/* Packet 3 types */
#घोषणा	PACKET3_NOP					0x10
#घोषणा	PACKET3_INसूचीECT_BUFFER_END			0x17
#घोषणा	PACKET3_SET_PREDICATION				0x20
#घोषणा	PACKET3_REG_RMW					0x21
#घोषणा	PACKET3_COND_EXEC				0x22
#घोषणा	PACKET3_PRED_EXEC				0x23
#घोषणा	PACKET3_START_3D_CMDBUF				0x24
#घोषणा	PACKET3_DRAW_INDEX_2				0x27
#घोषणा	PACKET3_CONTEXT_CONTROL				0x28
#घोषणा	PACKET3_DRAW_INDEX_IMMD_BE			0x29
#घोषणा	PACKET3_INDEX_TYPE				0x2A
#घोषणा	PACKET3_DRAW_INDEX				0x2B
#घोषणा	PACKET3_DRAW_INDEX_AUTO				0x2D
#घोषणा	PACKET3_DRAW_INDEX_IMMD				0x2E
#घोषणा	PACKET3_NUM_INSTANCES				0x2F
#घोषणा	PACKET3_STRMOUT_BUFFER_UPDATE			0x34
#घोषणा	PACKET3_INसूचीECT_BUFFER_MP			0x38
#घोषणा	PACKET3_MEM_SEMAPHORE				0x39
#              define PACKET3_SEM_WAIT_ON_SIGNAL    (0x1 << 12)
#              define PACKET3_SEM_SEL_SIGNAL	    (0x6 << 29)
#              define PACKET3_SEM_SEL_WAIT	    (0x7 << 29)
#घोषणा	PACKET3_MPEG_INDEX				0x3A
#घोषणा	PACKET3_COPY_DW					0x3B
#घोषणा	PACKET3_WAIT_REG_MEM				0x3C
#घोषणा	PACKET3_MEM_WRITE				0x3D
#घोषणा	PACKET3_INसूचीECT_BUFFER				0x32
#घोषणा	PACKET3_CP_DMA					0x41
/* 1. header
 * 2. SRC_ADDR_LO [31:0]
 * 3. CP_SYNC [31] | SRC_ADDR_HI [7:0]
 * 4. DST_ADDR_LO [31:0]
 * 5. DST_ADDR_HI [7:0]
 * 6. COMMAND [29:22] | BYTE_COUNT [20:0]
 */
#              define PACKET3_CP_DMA_CP_SYNC       (1 << 31)
/* COMMAND */
#              define PACKET3_CP_DMA_CMD_SRC_SWAP(x) ((x) << 22)
                /* 0 - none
		 * 1 - 8 in 16
		 * 2 - 8 in 32
		 * 3 - 8 in 64
		 */
#              define PACKET3_CP_DMA_CMD_DST_SWAP(x) ((x) << 24)
                /* 0 - none
		 * 1 - 8 in 16
		 * 2 - 8 in 32
		 * 3 - 8 in 64
		 */
#              define PACKET3_CP_DMA_CMD_SAS       (1 << 26)
                /* 0 - memory
		 * 1 - रेजिस्टर
		 */
#              define PACKET3_CP_DMA_CMD_DAS       (1 << 27)
                /* 0 - memory
		 * 1 - रेजिस्टर
		 */
#              define PACKET3_CP_DMA_CMD_SAIC      (1 << 28)
#              define PACKET3_CP_DMA_CMD_DAIC      (1 << 29)
#घोषणा	PACKET3_PFP_SYNC_ME				0x42 /* r7xx+ only */
#घोषणा	PACKET3_SURFACE_SYNC				0x43
#              define PACKET3_CB0_DEST_BASE_ENA    (1 << 6)
#              define PACKET3_FULL_CACHE_ENA       (1 << 20) /* r7xx+ only */
#              define PACKET3_TC_ACTION_ENA        (1 << 23)
#              define PACKET3_VC_ACTION_ENA        (1 << 24)
#              define PACKET3_CB_ACTION_ENA        (1 << 25)
#              define PACKET3_DB_ACTION_ENA        (1 << 26)
#              define PACKET3_SH_ACTION_ENA        (1 << 27)
#              define PACKET3_SMX_ACTION_ENA       (1 << 28)
#घोषणा	PACKET3_ME_INITIALIZE				0x44
#घोषणा		PACKET3_ME_INITIALIZE_DEVICE_ID(x) ((x) << 16)
#घोषणा	PACKET3_COND_WRITE				0x45
#घोषणा	PACKET3_EVENT_WRITE				0x46
#घोषणा		EVENT_TYPE(x)                           ((x) << 0)
#घोषणा		EVENT_INDEX(x)                          ((x) << 8)
                /* 0 - any non-TS event
		 * 1 - ZPASS_DONE
		 * 2 - SAMPLE_PIPELINESTAT
		 * 3 - SAMPLE_STREAMOUTSTAT*
		 * 4 - *S_PARTIAL_FLUSH
		 * 5 - TS events
		 */
#घोषणा	PACKET3_EVENT_WRITE_EOP				0x47
#घोषणा		DATA_SEL(x)                             ((x) << 29)
                /* 0 - discard
		 * 1 - send low 32bit data
		 * 2 - send 64bit data
		 * 3 - send 64bit counter value
		 */
#घोषणा		INT_SEL(x)                              ((x) << 24)
                /* 0 - none
		 * 1 - पूर्णांकerrupt only (DATA_SEL = 0)
		 * 2 - पूर्णांकerrupt when data ग_लिखो is confirmed
		 */
#घोषणा	PACKET3_ONE_REG_WRITE				0x57
#घोषणा	PACKET3_SET_CONFIG_REG				0x68
#घोषणा		PACKET3_SET_CONFIG_REG_OFFSET			0x00008000
#घोषणा		PACKET3_SET_CONFIG_REG_END			0x0000ac00
#घोषणा	PACKET3_SET_CONTEXT_REG				0x69
#घोषणा		PACKET3_SET_CONTEXT_REG_OFFSET			0x00028000
#घोषणा		PACKET3_SET_CONTEXT_REG_END			0x00029000
#घोषणा	PACKET3_SET_ALU_CONST				0x6A
#घोषणा		PACKET3_SET_ALU_CONST_OFFSET			0x00030000
#घोषणा		PACKET3_SET_ALU_CONST_END			0x00032000
#घोषणा	PACKET3_SET_BOOL_CONST				0x6B
#घोषणा		PACKET3_SET_BOOL_CONST_OFFSET			0x0003e380
#घोषणा		PACKET3_SET_BOOL_CONST_END			0x00040000
#घोषणा	PACKET3_SET_LOOP_CONST				0x6C
#घोषणा		PACKET3_SET_LOOP_CONST_OFFSET			0x0003e200
#घोषणा		PACKET3_SET_LOOP_CONST_END			0x0003e380
#घोषणा	PACKET3_SET_RESOURCE				0x6D
#घोषणा		PACKET3_SET_RESOURCE_OFFSET			0x00038000
#घोषणा		PACKET3_SET_RESOURCE_END			0x0003c000
#घोषणा	PACKET3_SET_SAMPLER				0x6E
#घोषणा		PACKET3_SET_SAMPLER_OFFSET			0x0003c000
#घोषणा		PACKET3_SET_SAMPLER_END				0x0003cff0
#घोषणा	PACKET3_SET_CTL_CONST				0x6F
#घोषणा		PACKET3_SET_CTL_CONST_OFFSET			0x0003cff0
#घोषणा		PACKET3_SET_CTL_CONST_END			0x0003e200
#घोषणा	PACKET3_STRMOUT_BASE_UPDATE			0x72 /* r7xx */
#घोषणा	PACKET3_SURFACE_BASE_UPDATE			0x73

#घोषणा R_000011_K8_FB_LOCATION                 0x11
#घोषणा R_000012_MC_MISC_UMA_CNTL               0x12
#घोषणा   G_000012_K8_ADDR_EXT(x)               (((x) >> 0) & 0xFF)
#घोषणा R_0028F8_MC_INDEX			0x28F8
#घोषणा   	S_0028F8_MC_IND_ADDR(x)                 (((x) & 0x1FF) << 0)
#घोषणा   	C_0028F8_MC_IND_ADDR                    0xFFFFFE00
#घोषणा   	S_0028F8_MC_IND_WR_EN(x)                (((x) & 0x1) << 9)
#घोषणा R_0028FC_MC_DATA                        0x28FC

#घोषणा	R_008020_GRBM_SOFT_RESET		0x8020
#घोषणा		S_008020_SOFT_RESET_CP(x)		(((x) & 1) << 0)
#घोषणा		S_008020_SOFT_RESET_CB(x)		(((x) & 1) << 1)
#घोषणा		S_008020_SOFT_RESET_CR(x)		(((x) & 1) << 2)
#घोषणा		S_008020_SOFT_RESET_DB(x)		(((x) & 1) << 3)
#घोषणा		S_008020_SOFT_RESET_PA(x)		(((x) & 1) << 5)
#घोषणा		S_008020_SOFT_RESET_SC(x)		(((x) & 1) << 6)
#घोषणा		S_008020_SOFT_RESET_SMX(x)		(((x) & 1) << 7)
#घोषणा		S_008020_SOFT_RESET_SPI(x)		(((x) & 1) << 8)
#घोषणा		S_008020_SOFT_RESET_SH(x)		(((x) & 1) << 9)
#घोषणा		S_008020_SOFT_RESET_SX(x)		(((x) & 1) << 10)
#घोषणा		S_008020_SOFT_RESET_TC(x)		(((x) & 1) << 11)
#घोषणा		S_008020_SOFT_RESET_TA(x)		(((x) & 1) << 12)
#घोषणा		S_008020_SOFT_RESET_VC(x)		(((x) & 1) << 13)
#घोषणा		S_008020_SOFT_RESET_VGT(x)		(((x) & 1) << 14)
#घोषणा	R_008010_GRBM_STATUS			0x8010
#घोषणा		S_008010_CMDFIFO_AVAIL(x)		(((x) & 0x1F) << 0)
#घोषणा		S_008010_CP_RQ_PENDING(x)		(((x) & 1) << 6)
#घोषणा		S_008010_CF_RQ_PENDING(x)		(((x) & 1) << 7)
#घोषणा		S_008010_PF_RQ_PENDING(x)		(((x) & 1) << 8)
#घोषणा		S_008010_GRBM_EE_BUSY(x)		(((x) & 1) << 10)
#घोषणा		S_008010_VC_BUSY(x)			(((x) & 1) << 11)
#घोषणा		S_008010_DB03_CLEAN(x)			(((x) & 1) << 12)
#घोषणा		S_008010_CB03_CLEAN(x)			(((x) & 1) << 13)
#घोषणा		S_008010_VGT_BUSY_NO_DMA(x)		(((x) & 1) << 16)
#घोषणा		S_008010_VGT_BUSY(x)			(((x) & 1) << 17)
#घोषणा		S_008010_TA03_BUSY(x)			(((x) & 1) << 18)
#घोषणा		S_008010_TC_BUSY(x)			(((x) & 1) << 19)
#घोषणा		S_008010_SX_BUSY(x)			(((x) & 1) << 20)
#घोषणा		S_008010_SH_BUSY(x)			(((x) & 1) << 21)
#घोषणा		S_008010_SPI03_BUSY(x)			(((x) & 1) << 22)
#घोषणा		S_008010_SMX_BUSY(x)			(((x) & 1) << 23)
#घोषणा		S_008010_SC_BUSY(x)			(((x) & 1) << 24)
#घोषणा		S_008010_PA_BUSY(x)			(((x) & 1) << 25)
#घोषणा		S_008010_DB03_BUSY(x)			(((x) & 1) << 26)
#घोषणा		S_008010_CR_BUSY(x)			(((x) & 1) << 27)
#घोषणा		S_008010_CP_COHERENCY_BUSY(x)		(((x) & 1) << 28)
#घोषणा		S_008010_CP_BUSY(x)			(((x) & 1) << 29)
#घोषणा		S_008010_CB03_BUSY(x)			(((x) & 1) << 30)
#घोषणा		S_008010_GUI_ACTIVE(x)			(((x) & 1) << 31)
#घोषणा		G_008010_CMDFIFO_AVAIL(x)		(((x) >> 0) & 0x1F)
#घोषणा		G_008010_CP_RQ_PENDING(x)		(((x) >> 6) & 1)
#घोषणा		G_008010_CF_RQ_PENDING(x)		(((x) >> 7) & 1)
#घोषणा		G_008010_PF_RQ_PENDING(x)		(((x) >> 8) & 1)
#घोषणा		G_008010_GRBM_EE_BUSY(x)		(((x) >> 10) & 1)
#घोषणा		G_008010_VC_BUSY(x)			(((x) >> 11) & 1)
#घोषणा		G_008010_DB03_CLEAN(x)			(((x) >> 12) & 1)
#घोषणा		G_008010_CB03_CLEAN(x)			(((x) >> 13) & 1)
#घोषणा		G_008010_TA_BUSY(x)			(((x) >> 14) & 1)
#घोषणा		G_008010_VGT_BUSY_NO_DMA(x)		(((x) >> 16) & 1)
#घोषणा		G_008010_VGT_BUSY(x)			(((x) >> 17) & 1)
#घोषणा		G_008010_TA03_BUSY(x)			(((x) >> 18) & 1)
#घोषणा		G_008010_TC_BUSY(x)			(((x) >> 19) & 1)
#घोषणा		G_008010_SX_BUSY(x)			(((x) >> 20) & 1)
#घोषणा		G_008010_SH_BUSY(x)			(((x) >> 21) & 1)
#घोषणा		G_008010_SPI03_BUSY(x)			(((x) >> 22) & 1)
#घोषणा		G_008010_SMX_BUSY(x)			(((x) >> 23) & 1)
#घोषणा		G_008010_SC_BUSY(x)			(((x) >> 24) & 1)
#घोषणा		G_008010_PA_BUSY(x)			(((x) >> 25) & 1)
#घोषणा		G_008010_DB03_BUSY(x)			(((x) >> 26) & 1)
#घोषणा		G_008010_CR_BUSY(x)			(((x) >> 27) & 1)
#घोषणा		G_008010_CP_COHERENCY_BUSY(x)		(((x) >> 28) & 1)
#घोषणा		G_008010_CP_BUSY(x)			(((x) >> 29) & 1)
#घोषणा		G_008010_CB03_BUSY(x)			(((x) >> 30) & 1)
#घोषणा		G_008010_GUI_ACTIVE(x)			(((x) >> 31) & 1)
#घोषणा	R_008014_GRBM_STATUS2			0x8014
#घोषणा		S_008014_CR_CLEAN(x)			(((x) & 1) << 0)
#घोषणा		S_008014_SMX_CLEAN(x)			(((x) & 1) << 1)
#घोषणा		S_008014_SPI0_BUSY(x)			(((x) & 1) << 8)
#घोषणा		S_008014_SPI1_BUSY(x)			(((x) & 1) << 9)
#घोषणा		S_008014_SPI2_BUSY(x)			(((x) & 1) << 10)
#घोषणा		S_008014_SPI3_BUSY(x)			(((x) & 1) << 11)
#घोषणा		S_008014_TA0_BUSY(x)			(((x) & 1) << 12)
#घोषणा		S_008014_TA1_BUSY(x)			(((x) & 1) << 13)
#घोषणा		S_008014_TA2_BUSY(x)			(((x) & 1) << 14)
#घोषणा		S_008014_TA3_BUSY(x)			(((x) & 1) << 15)
#घोषणा		S_008014_DB0_BUSY(x)			(((x) & 1) << 16)
#घोषणा		S_008014_DB1_BUSY(x)			(((x) & 1) << 17)
#घोषणा		S_008014_DB2_BUSY(x)			(((x) & 1) << 18)
#घोषणा		S_008014_DB3_BUSY(x)			(((x) & 1) << 19)
#घोषणा		S_008014_CB0_BUSY(x)			(((x) & 1) << 20)
#घोषणा		S_008014_CB1_BUSY(x)			(((x) & 1) << 21)
#घोषणा		S_008014_CB2_BUSY(x)			(((x) & 1) << 22)
#घोषणा		S_008014_CB3_BUSY(x)			(((x) & 1) << 23)
#घोषणा		G_008014_CR_CLEAN(x)			(((x) >> 0) & 1)
#घोषणा		G_008014_SMX_CLEAN(x)			(((x) >> 1) & 1)
#घोषणा		G_008014_SPI0_BUSY(x)			(((x) >> 8) & 1)
#घोषणा		G_008014_SPI1_BUSY(x)			(((x) >> 9) & 1)
#घोषणा		G_008014_SPI2_BUSY(x)			(((x) >> 10) & 1)
#घोषणा		G_008014_SPI3_BUSY(x)			(((x) >> 11) & 1)
#घोषणा		G_008014_TA0_BUSY(x)			(((x) >> 12) & 1)
#घोषणा		G_008014_TA1_BUSY(x)			(((x) >> 13) & 1)
#घोषणा		G_008014_TA2_BUSY(x)			(((x) >> 14) & 1)
#घोषणा		G_008014_TA3_BUSY(x)			(((x) >> 15) & 1)
#घोषणा		G_008014_DB0_BUSY(x)			(((x) >> 16) & 1)
#घोषणा		G_008014_DB1_BUSY(x)			(((x) >> 17) & 1)
#घोषणा		G_008014_DB2_BUSY(x)			(((x) >> 18) & 1)
#घोषणा		G_008014_DB3_BUSY(x)			(((x) >> 19) & 1)
#घोषणा		G_008014_CB0_BUSY(x)			(((x) >> 20) & 1)
#घोषणा		G_008014_CB1_BUSY(x)			(((x) >> 21) & 1)
#घोषणा		G_008014_CB2_BUSY(x)			(((x) >> 22) & 1)
#घोषणा		G_008014_CB3_BUSY(x)			(((x) >> 23) & 1)
#घोषणा	R_000E50_SRBM_STATUS				0x0E50
#घोषणा		G_000E50_RLC_RQ_PENDING(x)		(((x) >> 3) & 1)
#घोषणा		G_000E50_RCU_RQ_PENDING(x)		(((x) >> 4) & 1)
#घोषणा		G_000E50_GRBM_RQ_PENDING(x)		(((x) >> 5) & 1)
#घोषणा		G_000E50_HI_RQ_PENDING(x)		(((x) >> 6) & 1)
#घोषणा		G_000E50_IO_EXTERN_SIGNAL(x)		(((x) >> 7) & 1)
#घोषणा		G_000E50_VMC_BUSY(x)			(((x) >> 8) & 1)
#घोषणा		G_000E50_MCB_BUSY(x)			(((x) >> 9) & 1)
#घोषणा		G_000E50_MCDZ_BUSY(x)			(((x) >> 10) & 1)
#घोषणा		G_000E50_MCDY_BUSY(x)			(((x) >> 11) & 1)
#घोषणा		G_000E50_MCDX_BUSY(x)			(((x) >> 12) & 1)
#घोषणा		G_000E50_MCDW_BUSY(x)			(((x) >> 13) & 1)
#घोषणा		G_000E50_SEM_BUSY(x)			(((x) >> 14) & 1)
#घोषणा		G_000E50_RLC_BUSY(x)			(((x) >> 15) & 1)
#घोषणा		G_000E50_IH_BUSY(x)			(((x) >> 17) & 1)
#घोषणा		G_000E50_BIF_BUSY(x)			(((x) >> 29) & 1)
#घोषणा	R_000E60_SRBM_SOFT_RESET			0x0E60
#घोषणा		S_000E60_SOFT_RESET_BIF(x)		(((x) & 1) << 1)
#घोषणा		S_000E60_SOFT_RESET_CG(x)		(((x) & 1) << 2)
#घोषणा		S_000E60_SOFT_RESET_CMC(x)		(((x) & 1) << 3)
#घोषणा		S_000E60_SOFT_RESET_CSC(x)		(((x) & 1) << 4)
#घोषणा		S_000E60_SOFT_RESET_DC(x)		(((x) & 1) << 5)
#घोषणा		S_000E60_SOFT_RESET_GRBM(x)		(((x) & 1) << 8)
#घोषणा		S_000E60_SOFT_RESET_HDP(x)		(((x) & 1) << 9)
#घोषणा		S_000E60_SOFT_RESET_IH(x)		(((x) & 1) << 10)
#घोषणा		S_000E60_SOFT_RESET_MC(x)		(((x) & 1) << 11)
#घोषणा		S_000E60_SOFT_RESET_RLC(x)		(((x) & 1) << 13)
#घोषणा		S_000E60_SOFT_RESET_ROM(x)		(((x) & 1) << 14)
#घोषणा		S_000E60_SOFT_RESET_SEM(x)		(((x) & 1) << 15)
#घोषणा		S_000E60_SOFT_RESET_TSC(x)		(((x) & 1) << 16)
#घोषणा		S_000E60_SOFT_RESET_VMC(x)		(((x) & 1) << 17)

#घोषणा R_005480_HDP_MEM_COHERENCY_FLUSH_CNTL		0x5480

#घोषणा R_028C04_PA_SC_AA_CONFIG                     0x028C04
#घोषणा   S_028C04_MSAA_NUM_SAMPLES(x)                 (((x) & 0x3) << 0)
#घोषणा   G_028C04_MSAA_NUM_SAMPLES(x)                 (((x) >> 0) & 0x3)
#घोषणा   C_028C04_MSAA_NUM_SAMPLES                    0xFFFFFFFC
#घोषणा   S_028C04_AA_MASK_CENTROID_DTMN(x)            (((x) & 0x1) << 4)
#घोषणा   G_028C04_AA_MASK_CENTROID_DTMN(x)            (((x) >> 4) & 0x1)
#घोषणा   C_028C04_AA_MASK_CENTROID_DTMN               0xFFFFFFEF
#घोषणा   S_028C04_MAX_SAMPLE_DIST(x)                  (((x) & 0xF) << 13)
#घोषणा   G_028C04_MAX_SAMPLE_DIST(x)                  (((x) >> 13) & 0xF)
#घोषणा   C_028C04_MAX_SAMPLE_DIST                     0xFFFE1FFF
#घोषणा R_0280E0_CB_COLOR0_FRAG                      0x0280E0
#घोषणा   S_0280E0_BASE_256B(x)                        (((x) & 0xFFFFFFFF) << 0)
#घोषणा   G_0280E0_BASE_256B(x)                        (((x) >> 0) & 0xFFFFFFFF)
#घोषणा   C_0280E0_BASE_256B                           0x00000000
#घोषणा R_0280E4_CB_COLOR1_FRAG                      0x0280E4
#घोषणा R_0280E8_CB_COLOR2_FRAG                      0x0280E8
#घोषणा R_0280EC_CB_COLOR3_FRAG                      0x0280EC
#घोषणा R_0280F0_CB_COLOR4_FRAG                      0x0280F0
#घोषणा R_0280F4_CB_COLOR5_FRAG                      0x0280F4
#घोषणा R_0280F8_CB_COLOR6_FRAG                      0x0280F8
#घोषणा R_0280FC_CB_COLOR7_FRAG                      0x0280FC
#घोषणा R_0280C0_CB_COLOR0_TILE                      0x0280C0
#घोषणा   S_0280C0_BASE_256B(x)                        (((x) & 0xFFFFFFFF) << 0)
#घोषणा   G_0280C0_BASE_256B(x)                        (((x) >> 0) & 0xFFFFFFFF)
#घोषणा   C_0280C0_BASE_256B                           0x00000000
#घोषणा R_0280C4_CB_COLOR1_TILE                      0x0280C4
#घोषणा R_0280C8_CB_COLOR2_TILE                      0x0280C8
#घोषणा R_0280CC_CB_COLOR3_TILE                      0x0280CC
#घोषणा R_0280D0_CB_COLOR4_TILE                      0x0280D0
#घोषणा R_0280D4_CB_COLOR5_TILE                      0x0280D4
#घोषणा R_0280D8_CB_COLOR6_TILE                      0x0280D8
#घोषणा R_0280DC_CB_COLOR7_TILE                      0x0280DC
#घोषणा R_0280A0_CB_COLOR0_INFO                      0x0280A0
#घोषणा   S_0280A0_ENDIAN(x)                           (((x) & 0x3) << 0)
#घोषणा   G_0280A0_ENDIAN(x)                           (((x) >> 0) & 0x3)
#घोषणा   C_0280A0_ENDIAN                              0xFFFFFFFC
#घोषणा   S_0280A0_FORMAT(x)                           (((x) & 0x3F) << 2)
#घोषणा   G_0280A0_FORMAT(x)                           (((x) >> 2) & 0x3F)
#घोषणा   C_0280A0_FORMAT                              0xFFFFFF03
#घोषणा     V_0280A0_COLOR_INVALID                     0x00000000
#घोषणा     V_0280A0_COLOR_8                           0x00000001
#घोषणा     V_0280A0_COLOR_4_4                         0x00000002
#घोषणा     V_0280A0_COLOR_3_3_2                       0x00000003
#घोषणा     V_0280A0_COLOR_16                          0x00000005
#घोषणा     V_0280A0_COLOR_16_FLOAT                    0x00000006
#घोषणा     V_0280A0_COLOR_8_8                         0x00000007
#घोषणा     V_0280A0_COLOR_5_6_5                       0x00000008
#घोषणा     V_0280A0_COLOR_6_5_5                       0x00000009
#घोषणा     V_0280A0_COLOR_1_5_5_5                     0x0000000A
#घोषणा     V_0280A0_COLOR_4_4_4_4                     0x0000000B
#घोषणा     V_0280A0_COLOR_5_5_5_1                     0x0000000C
#घोषणा     V_0280A0_COLOR_32                          0x0000000D
#घोषणा     V_0280A0_COLOR_32_FLOAT                    0x0000000E
#घोषणा     V_0280A0_COLOR_16_16                       0x0000000F
#घोषणा     V_0280A0_COLOR_16_16_FLOAT                 0x00000010
#घोषणा     V_0280A0_COLOR_8_24                        0x00000011
#घोषणा     V_0280A0_COLOR_8_24_FLOAT                  0x00000012
#घोषणा     V_0280A0_COLOR_24_8                        0x00000013
#घोषणा     V_0280A0_COLOR_24_8_FLOAT                  0x00000014
#घोषणा     V_0280A0_COLOR_10_11_11                    0x00000015
#घोषणा     V_0280A0_COLOR_10_11_11_FLOAT              0x00000016
#घोषणा     V_0280A0_COLOR_11_11_10                    0x00000017
#घोषणा     V_0280A0_COLOR_11_11_10_FLOAT              0x00000018
#घोषणा     V_0280A0_COLOR_2_10_10_10                  0x00000019
#घोषणा     V_0280A0_COLOR_8_8_8_8                     0x0000001A
#घोषणा     V_0280A0_COLOR_10_10_10_2                  0x0000001B
#घोषणा     V_0280A0_COLOR_X24_8_32_FLOAT              0x0000001C
#घोषणा     V_0280A0_COLOR_32_32                       0x0000001D
#घोषणा     V_0280A0_COLOR_32_32_FLOAT                 0x0000001E
#घोषणा     V_0280A0_COLOR_16_16_16_16                 0x0000001F
#घोषणा     V_0280A0_COLOR_16_16_16_16_FLOAT           0x00000020
#घोषणा     V_0280A0_COLOR_32_32_32_32                 0x00000022
#घोषणा     V_0280A0_COLOR_32_32_32_32_FLOAT           0x00000023
#घोषणा   S_0280A0_ARRAY_MODE(x)                       (((x) & 0xF) << 8)
#घोषणा   G_0280A0_ARRAY_MODE(x)                       (((x) >> 8) & 0xF)
#घोषणा   C_0280A0_ARRAY_MODE                          0xFFFFF0FF
#घोषणा     V_0280A0_ARRAY_LINEAR_GENERAL              0x00000000
#घोषणा     V_0280A0_ARRAY_LINEAR_ALIGNED              0x00000001
#घोषणा     V_0280A0_ARRAY_1D_TILED_THIN1              0x00000002
#घोषणा     V_0280A0_ARRAY_2D_TILED_THIN1              0x00000004
#घोषणा   S_0280A0_NUMBER_TYPE(x)                      (((x) & 0x7) << 12)
#घोषणा   G_0280A0_NUMBER_TYPE(x)                      (((x) >> 12) & 0x7)
#घोषणा   C_0280A0_NUMBER_TYPE                         0xFFFF8FFF
#घोषणा   S_0280A0_READ_SIZE(x)                        (((x) & 0x1) << 15)
#घोषणा   G_0280A0_READ_SIZE(x)                        (((x) >> 15) & 0x1)
#घोषणा   C_0280A0_READ_SIZE                           0xFFFF7FFF
#घोषणा   S_0280A0_COMP_SWAP(x)                        (((x) & 0x3) << 16)
#घोषणा   G_0280A0_COMP_SWAP(x)                        (((x) >> 16) & 0x3)
#घोषणा   C_0280A0_COMP_SWAP                           0xFFFCFFFF
#घोषणा   S_0280A0_TILE_MODE(x)                        (((x) & 0x3) << 18)
#घोषणा   G_0280A0_TILE_MODE(x)                        (((x) >> 18) & 0x3)
#घोषणा   C_0280A0_TILE_MODE                           0xFFF3FFFF
#घोषणा     V_0280A0_TILE_DISABLE			0
#घोषणा     V_0280A0_CLEAR_ENABLE			1
#घोषणा     V_0280A0_FRAG_ENABLE			2
#घोषणा   S_0280A0_BLEND_CLAMP(x)                      (((x) & 0x1) << 20)
#घोषणा   G_0280A0_BLEND_CLAMP(x)                      (((x) >> 20) & 0x1)
#घोषणा   C_0280A0_BLEND_CLAMP                         0xFFEFFFFF
#घोषणा   S_0280A0_CLEAR_COLOR(x)                      (((x) & 0x1) << 21)
#घोषणा   G_0280A0_CLEAR_COLOR(x)                      (((x) >> 21) & 0x1)
#घोषणा   C_0280A0_CLEAR_COLOR                         0xFFDFFFFF
#घोषणा   S_0280A0_BLEND_BYPASS(x)                     (((x) & 0x1) << 22)
#घोषणा   G_0280A0_BLEND_BYPASS(x)                     (((x) >> 22) & 0x1)
#घोषणा   C_0280A0_BLEND_BYPASS                        0xFFBFFFFF
#घोषणा   S_0280A0_BLEND_FLOAT32(x)                    (((x) & 0x1) << 23)
#घोषणा   G_0280A0_BLEND_FLOAT32(x)                    (((x) >> 23) & 0x1)
#घोषणा   C_0280A0_BLEND_FLOAT32                       0xFF7FFFFF
#घोषणा   S_0280A0_SIMPLE_FLOAT(x)                     (((x) & 0x1) << 24)
#घोषणा   G_0280A0_SIMPLE_FLOAT(x)                     (((x) >> 24) & 0x1)
#घोषणा   C_0280A0_SIMPLE_FLOAT                        0xFEFFFFFF
#घोषणा   S_0280A0_ROUND_MODE(x)                       (((x) & 0x1) << 25)
#घोषणा   G_0280A0_ROUND_MODE(x)                       (((x) >> 25) & 0x1)
#घोषणा   C_0280A0_ROUND_MODE                          0xFDFFFFFF
#घोषणा   S_0280A0_TILE_COMPACT(x)                     (((x) & 0x1) << 26)
#घोषणा   G_0280A0_TILE_COMPACT(x)                     (((x) >> 26) & 0x1)
#घोषणा   C_0280A0_TILE_COMPACT                        0xFBFFFFFF
#घोषणा   S_0280A0_SOURCE_FORMAT(x)                    (((x) & 0x1) << 27)
#घोषणा   G_0280A0_SOURCE_FORMAT(x)                    (((x) >> 27) & 0x1)
#घोषणा   C_0280A0_SOURCE_FORMAT                       0xF7FFFFFF
#घोषणा R_0280A4_CB_COLOR1_INFO                      0x0280A4
#घोषणा R_0280A8_CB_COLOR2_INFO                      0x0280A8
#घोषणा R_0280AC_CB_COLOR3_INFO                      0x0280AC
#घोषणा R_0280B0_CB_COLOR4_INFO                      0x0280B0
#घोषणा R_0280B4_CB_COLOR5_INFO                      0x0280B4
#घोषणा R_0280B8_CB_COLOR6_INFO                      0x0280B8
#घोषणा R_0280BC_CB_COLOR7_INFO                      0x0280BC
#घोषणा R_028060_CB_COLOR0_SIZE                      0x028060
#घोषणा   S_028060_PITCH_TILE_MAX(x)                   (((x) & 0x3FF) << 0)
#घोषणा   G_028060_PITCH_TILE_MAX(x)                   (((x) >> 0) & 0x3FF)
#घोषणा   C_028060_PITCH_TILE_MAX                      0xFFFFFC00
#घोषणा   S_028060_SLICE_TILE_MAX(x)                   (((x) & 0xFFFFF) << 10)
#घोषणा   G_028060_SLICE_TILE_MAX(x)                   (((x) >> 10) & 0xFFFFF)
#घोषणा   C_028060_SLICE_TILE_MAX                      0xC00003FF
#घोषणा R_028064_CB_COLOR1_SIZE                      0x028064
#घोषणा R_028068_CB_COLOR2_SIZE                      0x028068
#घोषणा R_02806C_CB_COLOR3_SIZE                      0x02806C
#घोषणा R_028070_CB_COLOR4_SIZE                      0x028070
#घोषणा R_028074_CB_COLOR5_SIZE                      0x028074
#घोषणा R_028078_CB_COLOR6_SIZE                      0x028078
#घोषणा R_02807C_CB_COLOR7_SIZE                      0x02807C
#घोषणा R_028238_CB_TARGET_MASK                      0x028238
#घोषणा   S_028238_TARGET0_ENABLE(x)                   (((x) & 0xF) << 0)
#घोषणा   G_028238_TARGET0_ENABLE(x)                   (((x) >> 0) & 0xF)
#घोषणा   C_028238_TARGET0_ENABLE                      0xFFFFFFF0
#घोषणा   S_028238_TARGET1_ENABLE(x)                   (((x) & 0xF) << 4)
#घोषणा   G_028238_TARGET1_ENABLE(x)                   (((x) >> 4) & 0xF)
#घोषणा   C_028238_TARGET1_ENABLE                      0xFFFFFF0F
#घोषणा   S_028238_TARGET2_ENABLE(x)                   (((x) & 0xF) << 8)
#घोषणा   G_028238_TARGET2_ENABLE(x)                   (((x) >> 8) & 0xF)
#घोषणा   C_028238_TARGET2_ENABLE                      0xFFFFF0FF
#घोषणा   S_028238_TARGET3_ENABLE(x)                   (((x) & 0xF) << 12)
#घोषणा   G_028238_TARGET3_ENABLE(x)                   (((x) >> 12) & 0xF)
#घोषणा   C_028238_TARGET3_ENABLE                      0xFFFF0FFF
#घोषणा   S_028238_TARGET4_ENABLE(x)                   (((x) & 0xF) << 16)
#घोषणा   G_028238_TARGET4_ENABLE(x)                   (((x) >> 16) & 0xF)
#घोषणा   C_028238_TARGET4_ENABLE                      0xFFF0FFFF
#घोषणा   S_028238_TARGET5_ENABLE(x)                   (((x) & 0xF) << 20)
#घोषणा   G_028238_TARGET5_ENABLE(x)                   (((x) >> 20) & 0xF)
#घोषणा   C_028238_TARGET5_ENABLE                      0xFF0FFFFF
#घोषणा   S_028238_TARGET6_ENABLE(x)                   (((x) & 0xF) << 24)
#घोषणा   G_028238_TARGET6_ENABLE(x)                   (((x) >> 24) & 0xF)
#घोषणा   C_028238_TARGET6_ENABLE                      0xF0FFFFFF
#घोषणा   S_028238_TARGET7_ENABLE(x)                   (((x) & 0xF) << 28)
#घोषणा   G_028238_TARGET7_ENABLE(x)                   (((x) >> 28) & 0xF)
#घोषणा   C_028238_TARGET7_ENABLE                      0x0FFFFFFF
#घोषणा R_02823C_CB_SHADER_MASK                      0x02823C
#घोषणा   S_02823C_OUTPUT0_ENABLE(x)                   (((x) & 0xF) << 0)
#घोषणा   G_02823C_OUTPUT0_ENABLE(x)                   (((x) >> 0) & 0xF)
#घोषणा   C_02823C_OUTPUT0_ENABLE                      0xFFFFFFF0
#घोषणा   S_02823C_OUTPUT1_ENABLE(x)                   (((x) & 0xF) << 4)
#घोषणा   G_02823C_OUTPUT1_ENABLE(x)                   (((x) >> 4) & 0xF)
#घोषणा   C_02823C_OUTPUT1_ENABLE                      0xFFFFFF0F
#घोषणा   S_02823C_OUTPUT2_ENABLE(x)                   (((x) & 0xF) << 8)
#घोषणा   G_02823C_OUTPUT2_ENABLE(x)                   (((x) >> 8) & 0xF)
#घोषणा   C_02823C_OUTPUT2_ENABLE                      0xFFFFF0FF
#घोषणा   S_02823C_OUTPUT3_ENABLE(x)                   (((x) & 0xF) << 12)
#घोषणा   G_02823C_OUTPUT3_ENABLE(x)                   (((x) >> 12) & 0xF)
#घोषणा   C_02823C_OUTPUT3_ENABLE                      0xFFFF0FFF
#घोषणा   S_02823C_OUTPUT4_ENABLE(x)                   (((x) & 0xF) << 16)
#घोषणा   G_02823C_OUTPUT4_ENABLE(x)                   (((x) >> 16) & 0xF)
#घोषणा   C_02823C_OUTPUT4_ENABLE                      0xFFF0FFFF
#घोषणा   S_02823C_OUTPUT5_ENABLE(x)                   (((x) & 0xF) << 20)
#घोषणा   G_02823C_OUTPUT5_ENABLE(x)                   (((x) >> 20) & 0xF)
#घोषणा   C_02823C_OUTPUT5_ENABLE                      0xFF0FFFFF
#घोषणा   S_02823C_OUTPUT6_ENABLE(x)                   (((x) & 0xF) << 24)
#घोषणा   G_02823C_OUTPUT6_ENABLE(x)                   (((x) >> 24) & 0xF)
#घोषणा   C_02823C_OUTPUT6_ENABLE                      0xF0FFFFFF
#घोषणा   S_02823C_OUTPUT7_ENABLE(x)                   (((x) & 0xF) << 28)
#घोषणा   G_02823C_OUTPUT7_ENABLE(x)                   (((x) >> 28) & 0xF)
#घोषणा   C_02823C_OUTPUT7_ENABLE                      0x0FFFFFFF
#घोषणा R_028AB0_VGT_STRMOUT_EN                      0x028AB0
#घोषणा   S_028AB0_STREAMOUT(x)                        (((x) & 0x1) << 0)
#घोषणा   G_028AB0_STREAMOUT(x)                        (((x) >> 0) & 0x1)
#घोषणा   C_028AB0_STREAMOUT                           0xFFFFFFFE
#घोषणा R_028B20_VGT_STRMOUT_BUFFER_EN               0x028B20
#घोषणा   S_028B20_BUFFER_0_EN(x)                      (((x) & 0x1) << 0)
#घोषणा   G_028B20_BUFFER_0_EN(x)                      (((x) >> 0) & 0x1)
#घोषणा   C_028B20_BUFFER_0_EN                         0xFFFFFFFE
#घोषणा   S_028B20_BUFFER_1_EN(x)                      (((x) & 0x1) << 1)
#घोषणा   G_028B20_BUFFER_1_EN(x)                      (((x) >> 1) & 0x1)
#घोषणा   C_028B20_BUFFER_1_EN                         0xFFFFFFFD
#घोषणा   S_028B20_BUFFER_2_EN(x)                      (((x) & 0x1) << 2)
#घोषणा   G_028B20_BUFFER_2_EN(x)                      (((x) >> 2) & 0x1)
#घोषणा   C_028B20_BUFFER_2_EN                         0xFFFFFFFB
#घोषणा   S_028B20_BUFFER_3_EN(x)                      (((x) & 0x1) << 3)
#घोषणा   G_028B20_BUFFER_3_EN(x)                      (((x) >> 3) & 0x1)
#घोषणा   C_028B20_BUFFER_3_EN                         0xFFFFFFF7
#घोषणा   S_028B20_SIZE(x)                             (((x) & 0xFFFFFFFF) << 0)
#घोषणा   G_028B20_SIZE(x)                             (((x) >> 0) & 0xFFFFFFFF)
#घोषणा   C_028B20_SIZE                                0x00000000
#घोषणा R_038000_SQ_TEX_RESOURCE_WORD0_0             0x038000
#घोषणा   S_038000_DIM(x)                              (((x) & 0x7) << 0)
#घोषणा   G_038000_DIM(x)                              (((x) >> 0) & 0x7)
#घोषणा   C_038000_DIM                                 0xFFFFFFF8
#घोषणा     V_038000_SQ_TEX_DIM_1D                     0x00000000
#घोषणा     V_038000_SQ_TEX_DIM_2D                     0x00000001
#घोषणा     V_038000_SQ_TEX_DIM_3D                     0x00000002
#घोषणा     V_038000_SQ_TEX_DIM_CUBEMAP                0x00000003
#घोषणा     V_038000_SQ_TEX_DIM_1D_ARRAY               0x00000004
#घोषणा     V_038000_SQ_TEX_DIM_2D_ARRAY               0x00000005
#घोषणा     V_038000_SQ_TEX_DIM_2D_MSAA                0x00000006
#घोषणा     V_038000_SQ_TEX_DIM_2D_ARRAY_MSAA          0x00000007
#घोषणा   S_038000_TILE_MODE(x)                        (((x) & 0xF) << 3)
#घोषणा   G_038000_TILE_MODE(x)                        (((x) >> 3) & 0xF)
#घोषणा   C_038000_TILE_MODE                           0xFFFFFF87
#घोषणा     V_038000_ARRAY_LINEAR_GENERAL              0x00000000
#घोषणा     V_038000_ARRAY_LINEAR_ALIGNED              0x00000001
#घोषणा     V_038000_ARRAY_1D_TILED_THIN1              0x00000002
#घोषणा     V_038000_ARRAY_2D_TILED_THIN1              0x00000004
#घोषणा   S_038000_TILE_TYPE(x)                        (((x) & 0x1) << 7)
#घोषणा   G_038000_TILE_TYPE(x)                        (((x) >> 7) & 0x1)
#घोषणा   C_038000_TILE_TYPE                           0xFFFFFF7F
#घोषणा   S_038000_PITCH(x)                            (((x) & 0x7FF) << 8)
#घोषणा   G_038000_PITCH(x)                            (((x) >> 8) & 0x7FF)
#घोषणा   C_038000_PITCH                               0xFFF800FF
#घोषणा   S_038000_TEX_WIDTH(x)                        (((x) & 0x1FFF) << 19)
#घोषणा   G_038000_TEX_WIDTH(x)                        (((x) >> 19) & 0x1FFF)
#घोषणा   C_038000_TEX_WIDTH                           0x0007FFFF
#घोषणा R_038004_SQ_TEX_RESOURCE_WORD1_0             0x038004
#घोषणा   S_038004_TEX_HEIGHT(x)                       (((x) & 0x1FFF) << 0)
#घोषणा   G_038004_TEX_HEIGHT(x)                       (((x) >> 0) & 0x1FFF)
#घोषणा   C_038004_TEX_HEIGHT                          0xFFFFE000
#घोषणा   S_038004_TEX_DEPTH(x)                        (((x) & 0x1FFF) << 13)
#घोषणा   G_038004_TEX_DEPTH(x)                        (((x) >> 13) & 0x1FFF)
#घोषणा   C_038004_TEX_DEPTH                           0xFC001FFF
#घोषणा   S_038004_DATA_FORMAT(x)                      (((x) & 0x3F) << 26)
#घोषणा   G_038004_DATA_FORMAT(x)                      (((x) >> 26) & 0x3F)
#घोषणा   C_038004_DATA_FORMAT                         0x03FFFFFF
#घोषणा     V_038004_COLOR_INVALID                     0x00000000
#घोषणा     V_038004_COLOR_8                           0x00000001
#घोषणा     V_038004_COLOR_4_4                         0x00000002
#घोषणा     V_038004_COLOR_3_3_2                       0x00000003
#घोषणा     V_038004_COLOR_16                          0x00000005
#घोषणा     V_038004_COLOR_16_FLOAT                    0x00000006
#घोषणा     V_038004_COLOR_8_8                         0x00000007
#घोषणा     V_038004_COLOR_5_6_5                       0x00000008
#घोषणा     V_038004_COLOR_6_5_5                       0x00000009
#घोषणा     V_038004_COLOR_1_5_5_5                     0x0000000A
#घोषणा     V_038004_COLOR_4_4_4_4                     0x0000000B
#घोषणा     V_038004_COLOR_5_5_5_1                     0x0000000C
#घोषणा     V_038004_COLOR_32                          0x0000000D
#घोषणा     V_038004_COLOR_32_FLOAT                    0x0000000E
#घोषणा     V_038004_COLOR_16_16                       0x0000000F
#घोषणा     V_038004_COLOR_16_16_FLOAT                 0x00000010
#घोषणा     V_038004_COLOR_8_24                        0x00000011
#घोषणा     V_038004_COLOR_8_24_FLOAT                  0x00000012
#घोषणा     V_038004_COLOR_24_8                        0x00000013
#घोषणा     V_038004_COLOR_24_8_FLOAT                  0x00000014
#घोषणा     V_038004_COLOR_10_11_11                    0x00000015
#घोषणा     V_038004_COLOR_10_11_11_FLOAT              0x00000016
#घोषणा     V_038004_COLOR_11_11_10                    0x00000017
#घोषणा     V_038004_COLOR_11_11_10_FLOAT              0x00000018
#घोषणा     V_038004_COLOR_2_10_10_10                  0x00000019
#घोषणा     V_038004_COLOR_8_8_8_8                     0x0000001A
#घोषणा     V_038004_COLOR_10_10_10_2                  0x0000001B
#घोषणा     V_038004_COLOR_X24_8_32_FLOAT              0x0000001C
#घोषणा     V_038004_COLOR_32_32                       0x0000001D
#घोषणा     V_038004_COLOR_32_32_FLOAT                 0x0000001E
#घोषणा     V_038004_COLOR_16_16_16_16                 0x0000001F
#घोषणा     V_038004_COLOR_16_16_16_16_FLOAT           0x00000020
#घोषणा     V_038004_COLOR_32_32_32_32                 0x00000022
#घोषणा     V_038004_COLOR_32_32_32_32_FLOAT           0x00000023
#घोषणा     V_038004_FMT_1                             0x00000025
#घोषणा     V_038004_FMT_GB_GR                         0x00000027
#घोषणा     V_038004_FMT_BG_RG                         0x00000028
#घोषणा     V_038004_FMT_32_AS_8                       0x00000029
#घोषणा     V_038004_FMT_32_AS_8_8                     0x0000002A
#घोषणा     V_038004_FMT_5_9_9_9_SHAREDEXP             0x0000002B
#घोषणा     V_038004_FMT_8_8_8                         0x0000002C
#घोषणा     V_038004_FMT_16_16_16                      0x0000002D
#घोषणा     V_038004_FMT_16_16_16_FLOAT                0x0000002E
#घोषणा     V_038004_FMT_32_32_32                      0x0000002F
#घोषणा     V_038004_FMT_32_32_32_FLOAT                0x00000030
#घोषणा     V_038004_FMT_BC1                           0x00000031
#घोषणा     V_038004_FMT_BC2                           0x00000032
#घोषणा     V_038004_FMT_BC3                           0x00000033
#घोषणा     V_038004_FMT_BC4                           0x00000034
#घोषणा     V_038004_FMT_BC5                           0x00000035
#घोषणा     V_038004_FMT_BC6                           0x00000036
#घोषणा     V_038004_FMT_BC7                           0x00000037
#घोषणा     V_038004_FMT_32_AS_32_32_32_32             0x00000038
#घोषणा R_038010_SQ_TEX_RESOURCE_WORD4_0             0x038010
#घोषणा   S_038010_FORMAT_COMP_X(x)                    (((x) & 0x3) << 0)
#घोषणा   G_038010_FORMAT_COMP_X(x)                    (((x) >> 0) & 0x3)
#घोषणा   C_038010_FORMAT_COMP_X                       0xFFFFFFFC
#घोषणा   S_038010_FORMAT_COMP_Y(x)                    (((x) & 0x3) << 2)
#घोषणा   G_038010_FORMAT_COMP_Y(x)                    (((x) >> 2) & 0x3)
#घोषणा   C_038010_FORMAT_COMP_Y                       0xFFFFFFF3
#घोषणा   S_038010_FORMAT_COMP_Z(x)                    (((x) & 0x3) << 4)
#घोषणा   G_038010_FORMAT_COMP_Z(x)                    (((x) >> 4) & 0x3)
#घोषणा   C_038010_FORMAT_COMP_Z                       0xFFFFFFCF
#घोषणा   S_038010_FORMAT_COMP_W(x)                    (((x) & 0x3) << 6)
#घोषणा   G_038010_FORMAT_COMP_W(x)                    (((x) >> 6) & 0x3)
#घोषणा   C_038010_FORMAT_COMP_W                       0xFFFFFF3F
#घोषणा   S_038010_NUM_FORMAT_ALL(x)                   (((x) & 0x3) << 8)
#घोषणा   G_038010_NUM_FORMAT_ALL(x)                   (((x) >> 8) & 0x3)
#घोषणा   C_038010_NUM_FORMAT_ALL                      0xFFFFFCFF
#घोषणा   S_038010_SRF_MODE_ALL(x)                     (((x) & 0x1) << 10)
#घोषणा   G_038010_SRF_MODE_ALL(x)                     (((x) >> 10) & 0x1)
#घोषणा   C_038010_SRF_MODE_ALL                        0xFFFFFBFF
#घोषणा   S_038010_FORCE_DEGAMMA(x)                    (((x) & 0x1) << 11)
#घोषणा   G_038010_FORCE_DEGAMMA(x)                    (((x) >> 11) & 0x1)
#घोषणा   C_038010_FORCE_DEGAMMA                       0xFFFFF7FF
#घोषणा   S_038010_ENDIAN_SWAP(x)                      (((x) & 0x3) << 12)
#घोषणा   G_038010_ENDIAN_SWAP(x)                      (((x) >> 12) & 0x3)
#घोषणा   C_038010_ENDIAN_SWAP                         0xFFFFCFFF
#घोषणा   S_038010_REQUEST_SIZE(x)                     (((x) & 0x3) << 14)
#घोषणा   G_038010_REQUEST_SIZE(x)                     (((x) >> 14) & 0x3)
#घोषणा   C_038010_REQUEST_SIZE                        0xFFFF3FFF
#घोषणा   S_038010_DST_SEL_X(x)                        (((x) & 0x7) << 16)
#घोषणा   G_038010_DST_SEL_X(x)                        (((x) >> 16) & 0x7)
#घोषणा   C_038010_DST_SEL_X                           0xFFF8FFFF
#घोषणा   S_038010_DST_SEL_Y(x)                        (((x) & 0x7) << 19)
#घोषणा   G_038010_DST_SEL_Y(x)                        (((x) >> 19) & 0x7)
#घोषणा   C_038010_DST_SEL_Y                           0xFFC7FFFF
#घोषणा   S_038010_DST_SEL_Z(x)                        (((x) & 0x7) << 22)
#घोषणा   G_038010_DST_SEL_Z(x)                        (((x) >> 22) & 0x7)
#घोषणा   C_038010_DST_SEL_Z                           0xFE3FFFFF
#घोषणा   S_038010_DST_SEL_W(x)                        (((x) & 0x7) << 25)
#घोषणा   G_038010_DST_SEL_W(x)                        (((x) >> 25) & 0x7)
#घोषणा   C_038010_DST_SEL_W                           0xF1FFFFFF
#	define SQ_SEL_X					0
#	define SQ_SEL_Y					1
#	define SQ_SEL_Z					2
#	define SQ_SEL_W					3
#	define SQ_SEL_0					4
#	define SQ_SEL_1					5
#घोषणा   S_038010_BASE_LEVEL(x)                       (((x) & 0xF) << 28)
#घोषणा   G_038010_BASE_LEVEL(x)                       (((x) >> 28) & 0xF)
#घोषणा   C_038010_BASE_LEVEL                          0x0FFFFFFF
#घोषणा R_038014_SQ_TEX_RESOURCE_WORD5_0             0x038014
#घोषणा   S_038014_LAST_LEVEL(x)                       (((x) & 0xF) << 0)
#घोषणा   G_038014_LAST_LEVEL(x)                       (((x) >> 0) & 0xF)
#घोषणा   C_038014_LAST_LEVEL                          0xFFFFFFF0
#घोषणा   S_038014_BASE_ARRAY(x)                       (((x) & 0x1FFF) << 4)
#घोषणा   G_038014_BASE_ARRAY(x)                       (((x) >> 4) & 0x1FFF)
#घोषणा   C_038014_BASE_ARRAY                          0xFFFE000F
#घोषणा   S_038014_LAST_ARRAY(x)                       (((x) & 0x1FFF) << 17)
#घोषणा   G_038014_LAST_ARRAY(x)                       (((x) >> 17) & 0x1FFF)
#घोषणा   C_038014_LAST_ARRAY                          0xC001FFFF
#घोषणा R_0288A8_SQ_ESGS_RING_ITEMSIZE               0x0288A8
#घोषणा   S_0288A8_ITEMSIZE(x)                         (((x) & 0x7FFF) << 0)
#घोषणा   G_0288A8_ITEMSIZE(x)                         (((x) >> 0) & 0x7FFF)
#घोषणा   C_0288A8_ITEMSIZE                            0xFFFF8000
#घोषणा R_008C44_SQ_ESGS_RING_SIZE                   0x008C44
#घोषणा   S_008C44_MEM_SIZE(x)                         (((x) & 0xFFFFFFFF) << 0)
#घोषणा   G_008C44_MEM_SIZE(x)                         (((x) >> 0) & 0xFFFFFFFF)
#घोषणा   C_008C44_MEM_SIZE                            0x00000000
#घोषणा R_0288B0_SQ_ESTMP_RING_ITEMSIZE              0x0288B0
#घोषणा   S_0288B0_ITEMSIZE(x)                         (((x) & 0x7FFF) << 0)
#घोषणा   G_0288B0_ITEMSIZE(x)                         (((x) >> 0) & 0x7FFF)
#घोषणा   C_0288B0_ITEMSIZE                            0xFFFF8000
#घोषणा R_008C54_SQ_ESTMP_RING_SIZE                  0x008C54
#घोषणा   S_008C54_MEM_SIZE(x)                         (((x) & 0xFFFFFFFF) << 0)
#घोषणा   G_008C54_MEM_SIZE(x)                         (((x) >> 0) & 0xFFFFFFFF)
#घोषणा   C_008C54_MEM_SIZE                            0x00000000
#घोषणा R_0288C0_SQ_FBUF_RING_ITEMSIZE               0x0288C0
#घोषणा   S_0288C0_ITEMSIZE(x)                         (((x) & 0x7FFF) << 0)
#घोषणा   G_0288C0_ITEMSIZE(x)                         (((x) >> 0) & 0x7FFF)
#घोषणा   C_0288C0_ITEMSIZE                            0xFFFF8000
#घोषणा R_008C74_SQ_FBUF_RING_SIZE                   0x008C74
#घोषणा   S_008C74_MEM_SIZE(x)                         (((x) & 0xFFFFFFFF) << 0)
#घोषणा   G_008C74_MEM_SIZE(x)                         (((x) >> 0) & 0xFFFFFFFF)
#घोषणा   C_008C74_MEM_SIZE                            0x00000000
#घोषणा R_0288B4_SQ_GSTMP_RING_ITEMSIZE              0x0288B4
#घोषणा   S_0288B4_ITEMSIZE(x)                         (((x) & 0x7FFF) << 0)
#घोषणा   G_0288B4_ITEMSIZE(x)                         (((x) >> 0) & 0x7FFF)
#घोषणा   C_0288B4_ITEMSIZE                            0xFFFF8000
#घोषणा R_008C5C_SQ_GSTMP_RING_SIZE                  0x008C5C
#घोषणा   S_008C5C_MEM_SIZE(x)                         (((x) & 0xFFFFFFFF) << 0)
#घोषणा   G_008C5C_MEM_SIZE(x)                         (((x) >> 0) & 0xFFFFFFFF)
#घोषणा   C_008C5C_MEM_SIZE                            0x00000000
#घोषणा R_0288AC_SQ_GSVS_RING_ITEMSIZE               0x0288AC
#घोषणा   S_0288AC_ITEMSIZE(x)                         (((x) & 0x7FFF) << 0)
#घोषणा   G_0288AC_ITEMSIZE(x)                         (((x) >> 0) & 0x7FFF)
#घोषणा   C_0288AC_ITEMSIZE                            0xFFFF8000
#घोषणा R_008C4C_SQ_GSVS_RING_SIZE                   0x008C4C
#घोषणा   S_008C4C_MEM_SIZE(x)                         (((x) & 0xFFFFFFFF) << 0)
#घोषणा   G_008C4C_MEM_SIZE(x)                         (((x) >> 0) & 0xFFFFFFFF)
#घोषणा   C_008C4C_MEM_SIZE                            0x00000000
#घोषणा R_0288BC_SQ_PSTMP_RING_ITEMSIZE              0x0288BC
#घोषणा   S_0288BC_ITEMSIZE(x)                         (((x) & 0x7FFF) << 0)
#घोषणा   G_0288BC_ITEMSIZE(x)                         (((x) >> 0) & 0x7FFF)
#घोषणा   C_0288BC_ITEMSIZE                            0xFFFF8000
#घोषणा R_008C6C_SQ_PSTMP_RING_SIZE                  0x008C6C
#घोषणा   S_008C6C_MEM_SIZE(x)                         (((x) & 0xFFFFFFFF) << 0)
#घोषणा   G_008C6C_MEM_SIZE(x)                         (((x) >> 0) & 0xFFFFFFFF)
#घोषणा   C_008C6C_MEM_SIZE                            0x00000000
#घोषणा R_0288C4_SQ_REDUC_RING_ITEMSIZE              0x0288C4
#घोषणा   S_0288C4_ITEMSIZE(x)                         (((x) & 0x7FFF) << 0)
#घोषणा   G_0288C4_ITEMSIZE(x)                         (((x) >> 0) & 0x7FFF)
#घोषणा   C_0288C4_ITEMSIZE                            0xFFFF8000
#घोषणा R_008C7C_SQ_REDUC_RING_SIZE                  0x008C7C
#घोषणा   S_008C7C_MEM_SIZE(x)                         (((x) & 0xFFFFFFFF) << 0)
#घोषणा   G_008C7C_MEM_SIZE(x)                         (((x) >> 0) & 0xFFFFFFFF)
#घोषणा   C_008C7C_MEM_SIZE                            0x00000000
#घोषणा R_0288B8_SQ_VSTMP_RING_ITEMSIZE              0x0288B8
#घोषणा   S_0288B8_ITEMSIZE(x)                         (((x) & 0x7FFF) << 0)
#घोषणा   G_0288B8_ITEMSIZE(x)                         (((x) >> 0) & 0x7FFF)
#घोषणा   C_0288B8_ITEMSIZE                            0xFFFF8000
#घोषणा R_008C64_SQ_VSTMP_RING_SIZE                  0x008C64
#घोषणा   S_008C64_MEM_SIZE(x)                         (((x) & 0xFFFFFFFF) << 0)
#घोषणा   G_008C64_MEM_SIZE(x)                         (((x) >> 0) & 0xFFFFFFFF)
#घोषणा   C_008C64_MEM_SIZE                            0x00000000
#घोषणा R_0288C8_SQ_GS_VERT_ITEMSIZE                 0x0288C8
#घोषणा   S_0288C8_ITEMSIZE(x)                         (((x) & 0x7FFF) << 0)
#घोषणा   G_0288C8_ITEMSIZE(x)                         (((x) >> 0) & 0x7FFF)
#घोषणा   C_0288C8_ITEMSIZE                            0xFFFF8000
#घोषणा R_028010_DB_DEPTH_INFO                       0x028010
#घोषणा   S_028010_FORMAT(x)                           (((x) & 0x7) << 0)
#घोषणा   G_028010_FORMAT(x)                           (((x) >> 0) & 0x7)
#घोषणा   C_028010_FORMAT                              0xFFFFFFF8
#घोषणा     V_028010_DEPTH_INVALID                     0x00000000
#घोषणा     V_028010_DEPTH_16                          0x00000001
#घोषणा     V_028010_DEPTH_X8_24                       0x00000002
#घोषणा     V_028010_DEPTH_8_24                        0x00000003
#घोषणा     V_028010_DEPTH_X8_24_FLOAT                 0x00000004
#घोषणा     V_028010_DEPTH_8_24_FLOAT                  0x00000005
#घोषणा     V_028010_DEPTH_32_FLOAT                    0x00000006
#घोषणा     V_028010_DEPTH_X24_8_32_FLOAT              0x00000007
#घोषणा   S_028010_READ_SIZE(x)                        (((x) & 0x1) << 3)
#घोषणा   G_028010_READ_SIZE(x)                        (((x) >> 3) & 0x1)
#घोषणा   C_028010_READ_SIZE                           0xFFFFFFF7
#घोषणा   S_028010_ARRAY_MODE(x)                       (((x) & 0xF) << 15)
#घोषणा   G_028010_ARRAY_MODE(x)                       (((x) >> 15) & 0xF)
#घोषणा   C_028010_ARRAY_MODE                          0xFFF87FFF
#घोषणा     V_028010_ARRAY_1D_TILED_THIN1              0x00000002
#घोषणा     V_028010_ARRAY_2D_TILED_THIN1              0x00000004
#घोषणा   S_028010_TILE_SURFACE_ENABLE(x)              (((x) & 0x1) << 25)
#घोषणा   G_028010_TILE_SURFACE_ENABLE(x)              (((x) >> 25) & 0x1)
#घोषणा   C_028010_TILE_SURFACE_ENABLE                 0xFDFFFFFF
#घोषणा   S_028010_TILE_COMPACT(x)                     (((x) & 0x1) << 26)
#घोषणा   G_028010_TILE_COMPACT(x)                     (((x) >> 26) & 0x1)
#घोषणा   C_028010_TILE_COMPACT                        0xFBFFFFFF
#घोषणा   S_028010_ZRANGE_PRECISION(x)                 (((x) & 0x1) << 31)
#घोषणा   G_028010_ZRANGE_PRECISION(x)                 (((x) >> 31) & 0x1)
#घोषणा   C_028010_ZRANGE_PRECISION                    0x7FFFFFFF
#घोषणा R_028000_DB_DEPTH_SIZE                       0x028000
#घोषणा   S_028000_PITCH_TILE_MAX(x)                   (((x) & 0x3FF) << 0)
#घोषणा   G_028000_PITCH_TILE_MAX(x)                   (((x) >> 0) & 0x3FF)
#घोषणा   C_028000_PITCH_TILE_MAX                      0xFFFFFC00
#घोषणा   S_028000_SLICE_TILE_MAX(x)                   (((x) & 0xFFFFF) << 10)
#घोषणा   G_028000_SLICE_TILE_MAX(x)                   (((x) >> 10) & 0xFFFFF)
#घोषणा   C_028000_SLICE_TILE_MAX                      0xC00003FF
#घोषणा R_028004_DB_DEPTH_VIEW                       0x028004
#घोषणा   S_028004_SLICE_START(x)                      (((x) & 0x7FF) << 0)
#घोषणा   G_028004_SLICE_START(x)                      (((x) >> 0) & 0x7FF)
#घोषणा   C_028004_SLICE_START                         0xFFFFF800
#घोषणा   S_028004_SLICE_MAX(x)                        (((x) & 0x7FF) << 13)
#घोषणा   G_028004_SLICE_MAX(x)                        (((x) >> 13) & 0x7FF)
#घोषणा   C_028004_SLICE_MAX                           0xFF001FFF
#घोषणा R_028800_DB_DEPTH_CONTROL                    0x028800
#घोषणा   S_028800_STENCIL_ENABLE(x)                   (((x) & 0x1) << 0)
#घोषणा   G_028800_STENCIL_ENABLE(x)                   (((x) >> 0) & 0x1)
#घोषणा   C_028800_STENCIL_ENABLE                      0xFFFFFFFE
#घोषणा   S_028800_Z_ENABLE(x)                         (((x) & 0x1) << 1)
#घोषणा   G_028800_Z_ENABLE(x)                         (((x) >> 1) & 0x1)
#घोषणा   C_028800_Z_ENABLE                            0xFFFFFFFD
#घोषणा   S_028800_Z_WRITE_ENABLE(x)                   (((x) & 0x1) << 2)
#घोषणा   G_028800_Z_WRITE_ENABLE(x)                   (((x) >> 2) & 0x1)
#घोषणा   C_028800_Z_WRITE_ENABLE                      0xFFFFFFFB
#घोषणा   S_028800_ZFUNC(x)                            (((x) & 0x7) << 4)
#घोषणा   G_028800_ZFUNC(x)                            (((x) >> 4) & 0x7)
#घोषणा   C_028800_ZFUNC                               0xFFFFFF8F
#घोषणा   S_028800_BACKFACE_ENABLE(x)                  (((x) & 0x1) << 7)
#घोषणा   G_028800_BACKFACE_ENABLE(x)                  (((x) >> 7) & 0x1)
#घोषणा   C_028800_BACKFACE_ENABLE                     0xFFFFFF7F
#घोषणा   S_028800_STENCILFUNC(x)                      (((x) & 0x7) << 8)
#घोषणा   G_028800_STENCILFUNC(x)                      (((x) >> 8) & 0x7)
#घोषणा   C_028800_STENCILFUNC                         0xFFFFF8FF
#घोषणा   S_028800_STENCILFAIL(x)                      (((x) & 0x7) << 11)
#घोषणा   G_028800_STENCILFAIL(x)                      (((x) >> 11) & 0x7)
#घोषणा   C_028800_STENCILFAIL                         0xFFFFC7FF
#घोषणा   S_028800_STENCILZPASS(x)                     (((x) & 0x7) << 14)
#घोषणा   G_028800_STENCILZPASS(x)                     (((x) >> 14) & 0x7)
#घोषणा   C_028800_STENCILZPASS                        0xFFFE3FFF
#घोषणा   S_028800_STENCILZFAIL(x)                     (((x) & 0x7) << 17)
#घोषणा   G_028800_STENCILZFAIL(x)                     (((x) >> 17) & 0x7)
#घोषणा   C_028800_STENCILZFAIL                        0xFFF1FFFF
#घोषणा   S_028800_STENCILFUNC_BF(x)                   (((x) & 0x7) << 20)
#घोषणा   G_028800_STENCILFUNC_BF(x)                   (((x) >> 20) & 0x7)
#घोषणा   C_028800_STENCILFUNC_BF                      0xFF8FFFFF
#घोषणा   S_028800_STENCILFAIL_BF(x)                   (((x) & 0x7) << 23)
#घोषणा   G_028800_STENCILFAIL_BF(x)                   (((x) >> 23) & 0x7)
#घोषणा   C_028800_STENCILFAIL_BF                      0xFC7FFFFF
#घोषणा   S_028800_STENCILZPASS_BF(x)                  (((x) & 0x7) << 26)
#घोषणा   G_028800_STENCILZPASS_BF(x)                  (((x) >> 26) & 0x7)
#घोषणा   C_028800_STENCILZPASS_BF                     0xE3FFFFFF
#घोषणा   S_028800_STENCILZFAIL_BF(x)                  (((x) & 0x7) << 29)
#घोषणा   G_028800_STENCILZFAIL_BF(x)                  (((x) >> 29) & 0x7)
#घोषणा   C_028800_STENCILZFAIL_BF                     0x1FFFFFFF

#पूर्ण_अगर
