<शैली गुरु>
/*
 * Copyright 2010 Advanced Micro Devices, Inc.
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
#अगर_अघोषित NI_H
#घोषणा NI_H

#घोषणा CAYMAN_MAX_SH_GPRS           256
#घोषणा CAYMAN_MAX_TEMP_GPRS         16
#घोषणा CAYMAN_MAX_SH_THREADS        256
#घोषणा CAYMAN_MAX_SH_STACK_ENTRIES  4096
#घोषणा CAYMAN_MAX_FRC_EOV_CNT       16384
#घोषणा CAYMAN_MAX_BACKENDS          8
#घोषणा CAYMAN_MAX_BACKENDS_MASK     0xFF
#घोषणा CAYMAN_MAX_BACKENDS_PER_SE_MASK 0xF
#घोषणा CAYMAN_MAX_SIMDS             16
#घोषणा CAYMAN_MAX_SIMDS_MASK        0xFFFF
#घोषणा CAYMAN_MAX_SIMDS_PER_SE_MASK 0xFFF
#घोषणा CAYMAN_MAX_PIPES             8
#घोषणा CAYMAN_MAX_PIPES_MASK        0xFF
#घोषणा CAYMAN_MAX_LDS_NUM           0xFFFF
#घोषणा CAYMAN_MAX_TCC               16
#घोषणा CAYMAN_MAX_TCC_MASK          0xFF

#घोषणा CAYMAN_GB_ADDR_CONFIG_GOLDEN       0x02011003
#घोषणा ARUBA_GB_ADDR_CONFIG_GOLDEN        0x12010001

#घोषणा DMIF_ADDR_CONFIG  				0xBD4

/* fusion vce घड़ीs */
#घोषणा CG_ECLK_CNTL                                    0x620
#       define ECLK_DIVIDER_MASK                        0x7f
#       define ECLK_सूची_CNTL_EN                         (1 << 8)
#घोषणा CG_ECLK_STATUS                                  0x624
#       define ECLK_STATUS                              (1 << 0)

/* DCE6 only */
#घोषणा DMIF_ADDR_CALC  				0xC00

#घोषणा	SRBM_GFX_CNTL				        0x0E44
#घोषणा		RINGID(x)					(((x) & 0x3) << 0)
#घोषणा		VMID(x)						(((x) & 0x7) << 0)
#घोषणा	SRBM_STATUS				        0x0E50
#घोषणा		RLC_RQ_PENDING 				(1 << 3)
#घोषणा		GRBM_RQ_PENDING 			(1 << 5)
#घोषणा		VMC_BUSY 				(1 << 8)
#घोषणा		MCB_BUSY 				(1 << 9)
#घोषणा		MCB_NON_DISPLAY_BUSY 			(1 << 10)
#घोषणा		MCC_BUSY 				(1 << 11)
#घोषणा		MCD_BUSY 				(1 << 12)
#घोषणा		SEM_BUSY 				(1 << 14)
#घोषणा		RLC_BUSY 				(1 << 15)
#घोषणा		IH_BUSY 				(1 << 17)

#घोषणा	SRBM_SOFT_RESET				        0x0E60
#घोषणा		SOFT_RESET_BIF				(1 << 1)
#घोषणा		SOFT_RESET_CG				(1 << 2)
#घोषणा		SOFT_RESET_DC				(1 << 5)
#घोषणा		SOFT_RESET_DMA1				(1 << 6)
#घोषणा		SOFT_RESET_GRBM				(1 << 8)
#घोषणा		SOFT_RESET_HDP				(1 << 9)
#घोषणा		SOFT_RESET_IH				(1 << 10)
#घोषणा		SOFT_RESET_MC				(1 << 11)
#घोषणा		SOFT_RESET_RLC				(1 << 13)
#घोषणा		SOFT_RESET_ROM				(1 << 14)
#घोषणा		SOFT_RESET_SEM				(1 << 15)
#घोषणा		SOFT_RESET_VMC				(1 << 17)
#घोषणा		SOFT_RESET_DMA				(1 << 20)
#घोषणा		SOFT_RESET_TST				(1 << 21)
#घोषणा		SOFT_RESET_REGBB			(1 << 22)
#घोषणा		SOFT_RESET_ORB				(1 << 23)

#घोषणा SRBM_READ_ERROR					0xE98
#घोषणा SRBM_INT_CNTL					0xEA0
#घोषणा SRBM_INT_ACK					0xEA8

#घोषणा	SRBM_STATUS2				        0x0EC4
#घोषणा		DMA_BUSY 				(1 << 5)
#घोषणा		DMA1_BUSY 				(1 << 6)

#घोषणा VM_CONTEXT0_REQUEST_RESPONSE			0x1470
#घोषणा		REQUEST_TYPE(x)					(((x) & 0xf) << 0)
#घोषणा		RESPONSE_TYPE_MASK				0x000000F0
#घोषणा		RESPONSE_TYPE_SHIFT				4
#घोषणा VM_L2_CNTL					0x1400
#घोषणा		ENABLE_L2_CACHE					(1 << 0)
#घोषणा		ENABLE_L2_FRAGMENT_PROCESSING			(1 << 1)
#घोषणा		ENABLE_L2_PTE_CACHE_LRU_UPDATE_BY_WRITE		(1 << 9)
#घोषणा		ENABLE_L2_PDE0_CACHE_LRU_UPDATE_BY_WRITE	(1 << 10)
#घोषणा		EFFECTIVE_L2_QUEUE_SIZE(x)			(((x) & 7) << 14)
#घोषणा		CONTEXT1_IDENTITY_ACCESS_MODE(x)		(((x) & 3) << 18)
/* CONTEXT1_IDENTITY_ACCESS_MODE
 * 0 physical = logical
 * 1 logical via context1 page table
 * 2 inside identity aperture use translation, outside physical = logical
 * 3 inside identity aperture physical = logical, outside use translation
 */
#घोषणा VM_L2_CNTL2					0x1404
#घोषणा		INVALIDATE_ALL_L1_TLBS				(1 << 0)
#घोषणा		INVALIDATE_L2_CACHE				(1 << 1)
#घोषणा VM_L2_CNTL3					0x1408
#घोषणा		BANK_SELECT(x)					((x) << 0)
#घोषणा		CACHE_UPDATE_MODE(x)				((x) << 6)
#घोषणा		L2_CACHE_BIGK_ASSOCIATIVITY			(1 << 20)
#घोषणा		L2_CACHE_BIGK_FRAGMENT_SIZE(x)			((x) << 15)
#घोषणा	VM_L2_STATUS					0x140C
#घोषणा		L2_BUSY						(1 << 0)
#घोषणा VM_CONTEXT0_CNTL				0x1410
#घोषणा		ENABLE_CONTEXT					(1 << 0)
#घोषणा		PAGE_TABLE_DEPTH(x)				(((x) & 3) << 1)
#घोषणा		RANGE_PROTECTION_FAULT_ENABLE_INTERRUPT		(1 << 3)
#घोषणा		RANGE_PROTECTION_FAULT_ENABLE_DEFAULT		(1 << 4)
#घोषणा		DUMMY_PAGE_PROTECTION_FAULT_ENABLE_INTERRUPT	(1 << 6)
#घोषणा		DUMMY_PAGE_PROTECTION_FAULT_ENABLE_DEFAULT	(1 << 7)
#घोषणा		PDE0_PROTECTION_FAULT_ENABLE_INTERRUPT		(1 << 9)
#घोषणा		PDE0_PROTECTION_FAULT_ENABLE_DEFAULT		(1 << 10)
#घोषणा		VALID_PROTECTION_FAULT_ENABLE_INTERRUPT		(1 << 12)
#घोषणा		VALID_PROTECTION_FAULT_ENABLE_DEFAULT		(1 << 13)
#घोषणा		READ_PROTECTION_FAULT_ENABLE_INTERRUPT		(1 << 15)
#घोषणा		READ_PROTECTION_FAULT_ENABLE_DEFAULT		(1 << 16)
#घोषणा		WRITE_PROTECTION_FAULT_ENABLE_INTERRUPT		(1 << 18)
#घोषणा		WRITE_PROTECTION_FAULT_ENABLE_DEFAULT		(1 << 19)
#घोषणा		PAGE_TABLE_BLOCK_SIZE(x)			(((x) & 0xF) << 24)
#घोषणा VM_CONTEXT1_CNTL				0x1414
#घोषणा VM_CONTEXT0_CNTL2				0x1430
#घोषणा VM_CONTEXT1_CNTL2				0x1434
#घोषणा VM_INVALIDATE_REQUEST				0x1478
#घोषणा VM_INVALIDATE_RESPONSE				0x147c
#घोषणा	VM_CONTEXT1_PROTECTION_FAULT_ADDR		0x14FC
#घोषणा	VM_CONTEXT1_PROTECTION_FAULT_STATUS		0x14DC
#घोषणा		PROTECTIONS_MASK			(0xf << 0)
#घोषणा		PROTECTIONS_SHIFT			0
		/* bit 0: range
		 * bit 2: pde0
		 * bit 3: valid
		 * bit 4: पढ़ो
		 * bit 5: ग_लिखो
		 */
#घोषणा		MEMORY_CLIENT_ID_MASK			(0xff << 12)
#घोषणा		MEMORY_CLIENT_ID_SHIFT			12
#घोषणा		MEMORY_CLIENT_RW_MASK			(1 << 24)
#घोषणा		MEMORY_CLIENT_RW_SHIFT			24
#घोषणा		FAULT_VMID_MASK				(0x7 << 25)
#घोषणा		FAULT_VMID_SHIFT			25
#घोषणा VM_CONTEXT0_PROTECTION_FAULT_DEFAULT_ADDR	0x1518
#घोषणा VM_CONTEXT1_PROTECTION_FAULT_DEFAULT_ADDR	0x151c
#घोषणा	VM_CONTEXT0_PAGE_TABLE_BASE_ADDR		0x153C
#घोषणा	VM_CONTEXT0_PAGE_TABLE_START_ADDR		0x155C
#घोषणा	VM_CONTEXT0_PAGE_TABLE_END_ADDR			0x157C

#घोषणा MC_SHARED_CHMAP						0x2004
#घोषणा		NOOFCHAN_SHIFT					12
#घोषणा		NOOFCHAN_MASK					0x00003000
#घोषणा MC_SHARED_CHREMAP					0x2008

#घोषणा	MC_VM_SYSTEM_APERTURE_LOW_ADDR			0x2034
#घोषणा	MC_VM_SYSTEM_APERTURE_HIGH_ADDR			0x2038
#घोषणा	MC_VM_SYSTEM_APERTURE_DEFAULT_ADDR		0x203C
#घोषणा	MC_VM_MX_L1_TLB_CNTL				0x2064
#घोषणा		ENABLE_L1_TLB					(1 << 0)
#घोषणा		ENABLE_L1_FRAGMENT_PROCESSING			(1 << 1)
#घोषणा		SYSTEM_ACCESS_MODE_PA_ONLY			(0 << 3)
#घोषणा		SYSTEM_ACCESS_MODE_USE_SYS_MAP			(1 << 3)
#घोषणा		SYSTEM_ACCESS_MODE_IN_SYS			(2 << 3)
#घोषणा		SYSTEM_ACCESS_MODE_NOT_IN_SYS			(3 << 3)
#घोषणा		SYSTEM_APERTURE_UNMAPPED_ACCESS_PASS_THRU	(0 << 5)
#घोषणा		ENABLE_ADVANCED_DRIVER_MODEL			(1 << 6)
#घोषणा	FUS_MC_VM_FB_OFFSET				0x2068

#घोषणा MC_SHARED_BLACKOUT_CNTL           		0x20ac
#घोषणा	MC_ARB_RAMCFG					0x2760
#घोषणा		NOOFBANK_SHIFT					0
#घोषणा		NOOFBANK_MASK					0x00000003
#घोषणा		NOOFRANK_SHIFT					2
#घोषणा		NOOFRANK_MASK					0x00000004
#घोषणा		NOOFROWS_SHIFT					3
#घोषणा		NOOFROWS_MASK					0x00000038
#घोषणा		NOOFCOLS_SHIFT					6
#घोषणा		NOOFCOLS_MASK					0x000000C0
#घोषणा		CHANSIZE_SHIFT					8
#घोषणा		CHANSIZE_MASK					0x00000100
#घोषणा		BURSTLENGTH_SHIFT				9
#घोषणा		BURSTLENGTH_MASK				0x00000200
#घोषणा		CHANSIZE_OVERRIDE				(1 << 11)
#घोषणा MC_SEQ_SUP_CNTL           			0x28c8
#घोषणा		RUN_MASK      				(1 << 0)
#घोषणा MC_SEQ_SUP_PGM           			0x28cc
#घोषणा MC_IO_PAD_CNTL_D0           			0x29d0
#घोषणा		MEM_FALL_OUT_CMD      			(1 << 8)
#घोषणा MC_SEQ_MISC0           				0x2a00
#घोषणा		MC_SEQ_MISC0_GDDR5_SHIFT      		28
#घोषणा		MC_SEQ_MISC0_GDDR5_MASK      		0xf0000000
#घोषणा		MC_SEQ_MISC0_GDDR5_VALUE      		5
#घोषणा MC_SEQ_IO_DEBUG_INDEX           		0x2a44
#घोषणा MC_SEQ_IO_DEBUG_DATA           			0x2a48

#घोषणा	HDP_HOST_PATH_CNTL				0x2C00
#घोषणा	HDP_NONSURFACE_BASE				0x2C04
#घोषणा	HDP_NONSURFACE_INFO				0x2C08
#घोषणा	HDP_NONSURFACE_SIZE				0x2C0C
#घोषणा HDP_ADDR_CONFIG  				0x2F48
#घोषणा HDP_MISC_CNTL					0x2F4C
#घोषणा 	HDP_FLUSH_INVALIDATE_CACHE			(1 << 0)

#घोषणा	CC_SYS_RB_BACKEND_DISABLE			0x3F88
#घोषणा	GC_USER_SYS_RB_BACKEND_DISABLE			0x3F8C
#घोषणा	CGTS_SYS_TCC_DISABLE				0x3F90
#घोषणा	CGTS_USER_SYS_TCC_DISABLE			0x3F94

#घोषणा RLC_GFX_INDEX           			0x3FC4

#घोषणा	CONFIG_MEMSIZE					0x5428

#घोषणा HDP_MEM_COHERENCY_FLUSH_CNTL			0x5480
#घोषणा HDP_REG_COHERENCY_FLUSH_CNTL			0x54A0

#घोषणा	GRBM_CNTL					0x8000
#घोषणा		GRBM_READ_TIMEOUT(x)				((x) << 0)
#घोषणा	GRBM_STATUS					0x8010
#घोषणा		CMDFIFO_AVAIL_MASK				0x0000000F
#घोषणा		RING2_RQ_PENDING				(1 << 4)
#घोषणा		SRBM_RQ_PENDING					(1 << 5)
#घोषणा		RING1_RQ_PENDING				(1 << 6)
#घोषणा		CF_RQ_PENDING					(1 << 7)
#घोषणा		PF_RQ_PENDING					(1 << 8)
#घोषणा		GDS_DMA_RQ_PENDING				(1 << 9)
#घोषणा		GRBM_EE_BUSY					(1 << 10)
#घोषणा		SX_CLEAN					(1 << 11)
#घोषणा		DB_CLEAN					(1 << 12)
#घोषणा		CB_CLEAN					(1 << 13)
#घोषणा		TA_BUSY 					(1 << 14)
#घोषणा		GDS_BUSY 					(1 << 15)
#घोषणा		VGT_BUSY_NO_DMA					(1 << 16)
#घोषणा		VGT_BUSY					(1 << 17)
#घोषणा		IA_BUSY_NO_DMA					(1 << 18)
#घोषणा		IA_BUSY						(1 << 19)
#घोषणा		SX_BUSY 					(1 << 20)
#घोषणा		SH_BUSY 					(1 << 21)
#घोषणा		SPI_BUSY					(1 << 22)
#घोषणा		SC_BUSY 					(1 << 24)
#घोषणा		PA_BUSY 					(1 << 25)
#घोषणा		DB_BUSY 					(1 << 26)
#घोषणा		CP_COHERENCY_BUSY      				(1 << 28)
#घोषणा		CP_BUSY 					(1 << 29)
#घोषणा		CB_BUSY 					(1 << 30)
#घोषणा		GUI_ACTIVE					(1 << 31)
#घोषणा	GRBM_STATUS_SE0					0x8014
#घोषणा	GRBM_STATUS_SE1					0x8018
#घोषणा		SE_SX_CLEAN					(1 << 0)
#घोषणा		SE_DB_CLEAN					(1 << 1)
#घोषणा		SE_CB_CLEAN					(1 << 2)
#घोषणा		SE_VGT_BUSY					(1 << 23)
#घोषणा		SE_PA_BUSY					(1 << 24)
#घोषणा		SE_TA_BUSY					(1 << 25)
#घोषणा		SE_SX_BUSY					(1 << 26)
#घोषणा		SE_SPI_BUSY					(1 << 27)
#घोषणा		SE_SH_BUSY					(1 << 28)
#घोषणा		SE_SC_BUSY					(1 << 29)
#घोषणा		SE_DB_BUSY					(1 << 30)
#घोषणा		SE_CB_BUSY					(1 << 31)
#घोषणा	GRBM_SOFT_RESET					0x8020
#घोषणा		SOFT_RESET_CP					(1 << 0)
#घोषणा		SOFT_RESET_CB					(1 << 1)
#घोषणा		SOFT_RESET_DB					(1 << 3)
#घोषणा		SOFT_RESET_GDS					(1 << 4)
#घोषणा		SOFT_RESET_PA					(1 << 5)
#घोषणा		SOFT_RESET_SC					(1 << 6)
#घोषणा		SOFT_RESET_SPI					(1 << 8)
#घोषणा		SOFT_RESET_SH					(1 << 9)
#घोषणा		SOFT_RESET_SX					(1 << 10)
#घोषणा		SOFT_RESET_TC					(1 << 11)
#घोषणा		SOFT_RESET_TA					(1 << 12)
#घोषणा		SOFT_RESET_VGT					(1 << 14)
#घोषणा		SOFT_RESET_IA					(1 << 15)

#घोषणा GRBM_GFX_INDEX          			0x802C
#घोषणा		INSTANCE_INDEX(x)			((x) << 0)
#घोषणा		SE_INDEX(x)     			((x) << 16)
#घोषणा		INSTANCE_BROADCAST_WRITES      		(1 << 30)
#घोषणा		SE_BROADCAST_WRITES      		(1 << 31)

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
#घोषणा	CP_SEM_WAIT_TIMER				0x85BC
#घोषणा	CP_SEM_INCOMPLETE_TIMER_CNTL			0x85C8
#घोषणा	CP_COHER_CNTL2					0x85E8
#घोषणा	CP_STALLED_STAT1			0x8674
#घोषणा	CP_STALLED_STAT2			0x8678
#घोषणा	CP_BUSY_STAT				0x867C
#घोषणा	CP_STAT						0x8680
#घोषणा CP_ME_CNTL					0x86D8
#घोषणा		CP_ME_HALT					(1 << 28)
#घोषणा		CP_PFP_HALT					(1 << 26)
#घोषणा	CP_RB2_RPTR					0x86f8
#घोषणा	CP_RB1_RPTR					0x86fc
#घोषणा	CP_RB0_RPTR					0x8700
#घोषणा	CP_RB_WPTR_DELAY				0x8704
#घोषणा CP_MEQ_THRESHOLDS				0x8764
#घोषणा		MEQ1_START(x)				((x) << 0)
#घोषणा		MEQ2_START(x)				((x) << 8)
#घोषणा	CP_PERFMON_CNTL					0x87FC

#घोषणा	VGT_CACHE_INVALIDATION				0x88C4
#घोषणा		CACHE_INVALIDATION(x)				((x) << 0)
#घोषणा			VC_ONLY						0
#घोषणा			TC_ONLY						1
#घोषणा			VC_AND_TC					2
#घोषणा		AUTO_INVLD_EN(x)				((x) << 6)
#घोषणा			NO_AUTO						0
#घोषणा			ES_AUTO						1
#घोषणा			GS_AUTO						2
#घोषणा			ES_AND_GS_AUTO					3
#घोषणा	VGT_GS_VERTEX_REUSE				0x88D4

#घोषणा CC_GC_SHADER_PIPE_CONFIG			0x8950
#घोषणा	GC_USER_SHADER_PIPE_CONFIG			0x8954
#घोषणा		INACTIVE_QD_PIPES(x)				((x) << 8)
#घोषणा		INACTIVE_QD_PIPES_MASK				0x0000FF00
#घोषणा		INACTIVE_QD_PIPES_SHIFT				8
#घोषणा		INACTIVE_SIMDS(x)				((x) << 16)
#घोषणा		INACTIVE_SIMDS_MASK				0xFFFF0000
#घोषणा		INACTIVE_SIMDS_SHIFT				16

#घोषणा VGT_PRIMITIVE_TYPE                              0x8958
#घोषणा	VGT_NUM_INSTANCES				0x8974
#घोषणा VGT_TF_RING_SIZE				0x8988
#घोषणा VGT_OFFCHIP_LDS_BASE				0x89b4

#घोषणा	PA_SC_LINE_STIPPLE_STATE			0x8B10
#घोषणा	PA_CL_ENHANCE					0x8A14
#घोषणा		CLIP_VTX_REORDER_ENA				(1 << 0)
#घोषणा		NUM_CLIP_SEQ(x)					((x) << 1)
#घोषणा	PA_SC_FIFO_SIZE					0x8BCC
#घोषणा		SC_PRIM_FIFO_SIZE(x)				((x) << 0)
#घोषणा		SC_HIZ_TILE_FIFO_SIZE(x)			((x) << 12)
#घोषणा		SC_EARLYZ_TILE_FIFO_SIZE(x)			((x) << 20)
#घोषणा	PA_SC_FORCE_EOV_MAX_CNTS			0x8B24
#घोषणा		FORCE_EOV_MAX_CLK_CNT(x)			((x) << 0)
#घोषणा		FORCE_EOV_MAX_REZ_CNT(x)			((x) << 16)

#घोषणा	SQ_CONFIG					0x8C00
#घोषणा		VC_ENABLE					(1 << 0)
#घोषणा		EXPORT_SRC_C					(1 << 1)
#घोषणा		GFX_PRIO(x)					((x) << 2)
#घोषणा		CS1_PRIO(x)					((x) << 4)
#घोषणा		CS2_PRIO(x)					((x) << 6)
#घोषणा	SQ_GPR_RESOURCE_MGMT_1				0x8C04
#घोषणा		NUM_PS_GPRS(x)					((x) << 0)
#घोषणा		NUM_VS_GPRS(x)					((x) << 16)
#घोषणा		NUM_CLAUSE_TEMP_GPRS(x)				((x) << 28)
#घोषणा SQ_ESGS_RING_SIZE				0x8c44
#घोषणा SQ_GSVS_RING_SIZE				0x8c4c
#घोषणा SQ_ESTMP_RING_BASE				0x8c50
#घोषणा SQ_ESTMP_RING_SIZE				0x8c54
#घोषणा SQ_GSTMP_RING_BASE				0x8c58
#घोषणा SQ_GSTMP_RING_SIZE				0x8c5c
#घोषणा SQ_VSTMP_RING_BASE				0x8c60
#घोषणा SQ_VSTMP_RING_SIZE				0x8c64
#घोषणा SQ_PSTMP_RING_BASE				0x8c68
#घोषणा SQ_PSTMP_RING_SIZE				0x8c6c
#घोषणा	SQ_MS_FIFO_SIZES				0x8CF0
#घोषणा		CACHE_FIFO_SIZE(x)				((x) << 0)
#घोषणा		FETCH_FIFO_HIWATER(x)				((x) << 8)
#घोषणा		DONE_FIFO_HIWATER(x)				((x) << 16)
#घोषणा		ALU_UPDATE_FIFO_HIWATER(x)			((x) << 24)
#घोषणा SQ_LSTMP_RING_BASE				0x8e10
#घोषणा SQ_LSTMP_RING_SIZE				0x8e14
#घोषणा SQ_HSTMP_RING_BASE				0x8e18
#घोषणा SQ_HSTMP_RING_SIZE				0x8e1c
#घोषणा	SQ_DYN_GPR_CNTL_PS_FLUSH_REQ    		0x8D8C
#घोषणा		DYN_GPR_ENABLE					(1 << 8)
#घोषणा SQ_CONST_MEM_BASE				0x8df8

#घोषणा	SX_EXPORT_BUFFER_SIZES				0x900C
#घोषणा		COLOR_BUFFER_SIZE(x)				((x) << 0)
#घोषणा		POSITION_BUFFER_SIZE(x)				((x) << 8)
#घोषणा		SMX_BUFFER_SIZE(x)				((x) << 16)
#घोषणा	SX_DEBUG_1					0x9058
#घोषणा		ENABLE_NEW_SMX_ADDRESS				(1 << 16)

#घोषणा	SPI_CONFIG_CNTL					0x9100
#घोषणा		GPR_WRITE_PRIORITY(x)				((x) << 0)
#घोषणा	SPI_CONFIG_CNTL_1				0x913C
#घोषणा		VTX_DONE_DELAY(x)				((x) << 0)
#घोषणा		INTERP_ONE_PRIM_PER_ROW				(1 << 4)
#घोषणा		CRC_SIMD_ID_WADDR_DISABLE			(1 << 8)

#घोषणा	CGTS_TCC_DISABLE				0x9148
#घोषणा	CGTS_USER_TCC_DISABLE				0x914C
#घोषणा		TCC_DISABLE_MASK				0xFFFF0000
#घोषणा		TCC_DISABLE_SHIFT				16
#घोषणा	CGTS_SM_CTRL_REG				0x9150
#घोषणा		OVERRIDE				(1 << 21)

#घोषणा	TA_CNTL_AUX					0x9508
#घोषणा		DISABLE_CUBE_WRAP				(1 << 0)
#घोषणा		DISABLE_CUBE_ANISO				(1 << 1)

#घोषणा	TCP_CHAN_STEER_LO				0x960c
#घोषणा	TCP_CHAN_STEER_HI				0x9610

#घोषणा CC_RB_BACKEND_DISABLE				0x98F4
#घोषणा		BACKEND_DISABLE(x)     			((x) << 16)
#घोषणा GB_ADDR_CONFIG  				0x98F8
#घोषणा		NUM_PIPES(x)				((x) << 0)
#घोषणा		NUM_PIPES_MASK				0x00000007
#घोषणा		NUM_PIPES_SHIFT				0
#घोषणा		PIPE_INTERLEAVE_SIZE(x)			((x) << 4)
#घोषणा		PIPE_INTERLEAVE_SIZE_MASK		0x00000070
#घोषणा		PIPE_INTERLEAVE_SIZE_SHIFT		4
#घोषणा		BANK_INTERLEAVE_SIZE(x)			((x) << 8)
#घोषणा		NUM_SHADER_ENGINES(x)			((x) << 12)
#घोषणा		NUM_SHADER_ENGINES_MASK			0x00003000
#घोषणा		NUM_SHADER_ENGINES_SHIFT		12
#घोषणा		SHADER_ENGINE_TILE_SIZE(x)     		((x) << 16)
#घोषणा		SHADER_ENGINE_TILE_SIZE_MASK		0x00070000
#घोषणा		SHADER_ENGINE_TILE_SIZE_SHIFT		16
#घोषणा		NUM_GPUS(x)     			((x) << 20)
#घोषणा		NUM_GPUS_MASK				0x00700000
#घोषणा		NUM_GPUS_SHIFT				20
#घोषणा		MULTI_GPU_TILE_SIZE(x)     		((x) << 24)
#घोषणा		MULTI_GPU_TILE_SIZE_MASK		0x03000000
#घोषणा		MULTI_GPU_TILE_SIZE_SHIFT		24
#घोषणा		ROW_SIZE(x)             		((x) << 28)
#घोषणा		ROW_SIZE_MASK				0x30000000
#घोषणा		ROW_SIZE_SHIFT				28
#घोषणा		NUM_LOWER_PIPES(x)			((x) << 30)
#घोषणा		NUM_LOWER_PIPES_MASK			0x40000000
#घोषणा		NUM_LOWER_PIPES_SHIFT			30
#घोषणा GB_BACKEND_MAP  				0x98FC

#घोषणा CB_PERF_CTR0_SEL_0				0x9A20
#घोषणा CB_PERF_CTR0_SEL_1				0x9A24
#घोषणा CB_PERF_CTR1_SEL_0				0x9A28
#घोषणा CB_PERF_CTR1_SEL_1				0x9A2C
#घोषणा CB_PERF_CTR2_SEL_0				0x9A30
#घोषणा CB_PERF_CTR2_SEL_1				0x9A34
#घोषणा CB_PERF_CTR3_SEL_0				0x9A38
#घोषणा CB_PERF_CTR3_SEL_1				0x9A3C

#घोषणा	GC_USER_RB_BACKEND_DISABLE			0x9B7C
#घोषणा		BACKEND_DISABLE_MASK			0x00FF0000
#घोषणा		BACKEND_DISABLE_SHIFT			16

#घोषणा	SMX_DC_CTL0					0xA020
#घोषणा		USE_HASH_FUNCTION				(1 << 0)
#घोषणा		NUMBER_OF_SETS(x)				((x) << 1)
#घोषणा		FLUSH_ALL_ON_EVENT				(1 << 10)
#घोषणा		STALL_ON_EVENT					(1 << 11)
#घोषणा	SMX_EVENT_CTL					0xA02C
#घोषणा		ES_FLUSH_CTL(x)					((x) << 0)
#घोषणा		GS_FLUSH_CTL(x)					((x) << 3)
#घोषणा		ACK_FLUSH_CTL(x)				((x) << 6)
#घोषणा		SYNC_FLUSH_CTL					(1 << 8)

#घोषणा	CP_RB0_BASE					0xC100
#घोषणा	CP_RB0_CNTL					0xC104
#घोषणा		RB_BUFSZ(x)					((x) << 0)
#घोषणा		RB_BLKSZ(x)					((x) << 8)
#घोषणा		RB_NO_UPDATE					(1 << 27)
#घोषणा		RB_RPTR_WR_ENA					(1 << 31)
#घोषणा		BUF_SWAP_32BIT					(2 << 16)
#घोषणा	CP_RB0_RPTR_ADDR				0xC10C
#घोषणा	CP_RB0_RPTR_ADDR_HI				0xC110
#घोषणा	CP_RB0_WPTR					0xC114

#घोषणा CP_INT_CNTL                                     0xC124
#       define CNTX_BUSY_INT_ENABLE                     (1 << 19)
#       define CNTX_EMPTY_INT_ENABLE                    (1 << 20)
#       define TIME_STAMP_INT_ENABLE                    (1 << 26)

#घोषणा	CP_RB1_BASE					0xC180
#घोषणा	CP_RB1_CNTL					0xC184
#घोषणा	CP_RB1_RPTR_ADDR				0xC188
#घोषणा	CP_RB1_RPTR_ADDR_HI				0xC18C
#घोषणा	CP_RB1_WPTR					0xC190
#घोषणा	CP_RB2_BASE					0xC194
#घोषणा	CP_RB2_CNTL					0xC198
#घोषणा	CP_RB2_RPTR_ADDR				0xC19C
#घोषणा	CP_RB2_RPTR_ADDR_HI				0xC1A0
#घोषणा	CP_RB2_WPTR					0xC1A4
#घोषणा	CP_PFP_UCODE_ADDR				0xC150
#घोषणा	CP_PFP_UCODE_DATA				0xC154
#घोषणा	CP_ME_RAM_RADDR					0xC158
#घोषणा	CP_ME_RAM_WADDR					0xC15C
#घोषणा	CP_ME_RAM_DATA					0xC160
#घोषणा	CP_DEBUG					0xC1FC

#घोषणा VGT_EVENT_INITIATOR                             0x28a90
#       define CACHE_FLUSH_AND_INV_EVENT_TS                     (0x14 << 0)
#       define CACHE_FLUSH_AND_INV_EVENT                        (0x16 << 0)

/* TN SMU रेजिस्टरs */
#घोषणा	TN_CURRENT_GNB_TEMP				0x1F390

/* pm रेजिस्टरs */
#घोषणा	SMC_MSG						0x20c
#घोषणा		HOST_SMC_MSG(x)				((x) << 0)
#घोषणा		HOST_SMC_MSG_MASK			(0xff << 0)
#घोषणा		HOST_SMC_MSG_SHIFT			0
#घोषणा		HOST_SMC_RESP(x)			((x) << 8)
#घोषणा		HOST_SMC_RESP_MASK			(0xff << 8)
#घोषणा		HOST_SMC_RESP_SHIFT			8
#घोषणा		SMC_HOST_MSG(x)				((x) << 16)
#घोषणा		SMC_HOST_MSG_MASK			(0xff << 16)
#घोषणा		SMC_HOST_MSG_SHIFT			16
#घोषणा		SMC_HOST_RESP(x)			((x) << 24)
#घोषणा		SMC_HOST_RESP_MASK			(0xff << 24)
#घोषणा		SMC_HOST_RESP_SHIFT			24

#घोषणा	CG_SPLL_FUNC_CNTL				0x600
#घोषणा		SPLL_RESET				(1 << 0)
#घोषणा		SPLL_SLEEP				(1 << 1)
#घोषणा		SPLL_BYPASS_EN				(1 << 3)
#घोषणा		SPLL_REF_DIV(x)				((x) << 4)
#घोषणा		SPLL_REF_DIV_MASK			(0x3f << 4)
#घोषणा		SPLL_PDIV_A(x)				((x) << 20)
#घोषणा		SPLL_PDIV_A_MASK			(0x7f << 20)
#घोषणा		SPLL_PDIV_A_SHIFT			20
#घोषणा	CG_SPLL_FUNC_CNTL_2				0x604
#घोषणा		SCLK_MUX_SEL(x)				((x) << 0)
#घोषणा		SCLK_MUX_SEL_MASK			(0x1ff << 0)
#घोषणा	CG_SPLL_FUNC_CNTL_3				0x608
#घोषणा		SPLL_FB_DIV(x)				((x) << 0)
#घोषणा		SPLL_FB_DIV_MASK			(0x3ffffff << 0)
#घोषणा		SPLL_FB_DIV_SHIFT			0
#घोषणा		SPLL_DITHEN				(1 << 28)

#घोषणा MPLL_CNTL_MODE                                  0x61c
#       define SS_SSEN                                  (1 << 24)
#       define SS_DSMODE_EN                             (1 << 25)

#घोषणा	MPLL_AD_FUNC_CNTL				0x624
#घोषणा		CLKF(x)					((x) << 0)
#घोषणा		CLKF_MASK				(0x7f << 0)
#घोषणा		CLKR(x)					((x) << 7)
#घोषणा		CLKR_MASK				(0x1f << 7)
#घोषणा		CLKFRAC(x)				((x) << 12)
#घोषणा		CLKFRAC_MASK				(0x1f << 12)
#घोषणा		YCLK_POST_DIV(x)			((x) << 17)
#घोषणा		YCLK_POST_DIV_MASK			(3 << 17)
#घोषणा		IBIAS(x)				((x) << 20)
#घोषणा		IBIAS_MASK				(0x3ff << 20)
#घोषणा		RESET					(1 << 30)
#घोषणा		PDNB					(1 << 31)
#घोषणा	MPLL_AD_FUNC_CNTL_2				0x628
#घोषणा		BYPASS					(1 << 19)
#घोषणा		BIAS_GEN_PDNB				(1 << 24)
#घोषणा		RESET_EN				(1 << 25)
#घोषणा		VCO_MODE				(1 << 29)
#घोषणा	MPLL_DQ_FUNC_CNTL				0x62c
#घोषणा	MPLL_DQ_FUNC_CNTL_2				0x630

#घोषणा GENERAL_PWRMGT                                  0x63c
#       define GLOBAL_PWRMGT_EN                         (1 << 0)
#       define STATIC_PM_EN                             (1 << 1)
#       define THERMAL_PROTECTION_DIS                   (1 << 2)
#       define THERMAL_PROTECTION_TYPE                  (1 << 3)
#       define ENABLE_GEN2PCIE                          (1 << 4)
#       define ENABLE_GEN2XSP                           (1 << 5)
#       define SW_SMIO_INDEX(x)                         ((x) << 6)
#       define SW_SMIO_INDEX_MASK                       (3 << 6)
#       define SW_SMIO_INDEX_SHIFT                      6
#       define LOW_VOLT_D2_ACPI                         (1 << 8)
#       define LOW_VOLT_D3_ACPI                         (1 << 9)
#       define VOLT_PWRMGT_EN                           (1 << 10)
#       define BACKBIAS_PAD_EN                          (1 << 18)
#       define BACKBIAS_VALUE                           (1 << 19)
#       define DYN_SPREAD_SPECTRUM_EN                   (1 << 23)
#       define AC_DC_SW                                 (1 << 24)

#घोषणा SCLK_PWRMGT_CNTL                                  0x644
#       define SCLK_PWRMGT_OFF                            (1 << 0)
#       define SCLK_LOW_D1                                (1 << 1)
#       define FIR_RESET                                  (1 << 4)
#       define FIR_FORCE_TREND_SEL                        (1 << 5)
#       define FIR_TREND_MODE                             (1 << 6)
#       define DYN_GFX_CLK_OFF_EN                         (1 << 7)
#       define GFX_CLK_FORCE_ON                           (1 << 8)
#       define GFX_CLK_REQUEST_OFF                        (1 << 9)
#       define GFX_CLK_FORCE_OFF                          (1 << 10)
#       define GFX_CLK_OFF_ACPI_D1                        (1 << 11)
#       define GFX_CLK_OFF_ACPI_D2                        (1 << 12)
#       define GFX_CLK_OFF_ACPI_D3                        (1 << 13)
#       define DYN_LIGHT_SLEEP_EN                         (1 << 14)
#घोषणा	MCLK_PWRMGT_CNTL				0x648
#       define DLL_SPEED(x)				((x) << 0)
#       define DLL_SPEED_MASK				(0x1f << 0)
#       define MPLL_PWRMGT_OFF                          (1 << 5)
#       define DLL_READY                                (1 << 6)
#       define MC_INT_CNTL                              (1 << 7)
#       define MRDCKA0_PDNB                             (1 << 8)
#       define MRDCKA1_PDNB                             (1 << 9)
#       define MRDCKB0_PDNB                             (1 << 10)
#       define MRDCKB1_PDNB                             (1 << 11)
#       define MRDCKC0_PDNB                             (1 << 12)
#       define MRDCKC1_PDNB                             (1 << 13)
#       define MRDCKD0_PDNB                             (1 << 14)
#       define MRDCKD1_PDNB                             (1 << 15)
#       define MRDCKA0_RESET                            (1 << 16)
#       define MRDCKA1_RESET                            (1 << 17)
#       define MRDCKB0_RESET                            (1 << 18)
#       define MRDCKB1_RESET                            (1 << 19)
#       define MRDCKC0_RESET                            (1 << 20)
#       define MRDCKC1_RESET                            (1 << 21)
#       define MRDCKD0_RESET                            (1 << 22)
#       define MRDCKD1_RESET                            (1 << 23)
#       define DLL_READY_READ                           (1 << 24)
#       define USE_DISPLAY_GAP                          (1 << 25)
#       define USE_DISPLAY_URGENT_NORMAL                (1 << 26)
#       define MPLL_TURNOFF_D2                          (1 << 28)
#घोषणा	DLL_CNTL					0x64c
#       define MRDCKA0_BYPASS                           (1 << 24)
#       define MRDCKA1_BYPASS                           (1 << 25)
#       define MRDCKB0_BYPASS                           (1 << 26)
#       define MRDCKB1_BYPASS                           (1 << 27)
#       define MRDCKC0_BYPASS                           (1 << 28)
#       define MRDCKC1_BYPASS                           (1 << 29)
#       define MRDCKD0_BYPASS                           (1 << 30)
#       define MRDCKD1_BYPASS                           (1 << 31)

#घोषणा TARGET_AND_CURRENT_PROखाता_INDEX                  0x66c
#       define CURRENT_STATE_INDEX_MASK                   (0xf << 4)
#       define CURRENT_STATE_INDEX_SHIFT                  4

#घोषणा CG_AT                                           0x6d4
#       define CG_R(x)					((x) << 0)
#       define CG_R_MASK				(0xffff << 0)
#       define CG_L(x)					((x) << 16)
#       define CG_L_MASK				(0xffff << 16)

#घोषणा	CG_BIF_REQ_AND_RSP				0x7f4
#घोषणा		CG_CLIENT_REQ(x)			((x) << 0)
#घोषणा		CG_CLIENT_REQ_MASK			(0xff << 0)
#घोषणा		CG_CLIENT_REQ_SHIFT			0
#घोषणा		CG_CLIENT_RESP(x)			((x) << 8)
#घोषणा		CG_CLIENT_RESP_MASK			(0xff << 8)
#घोषणा		CG_CLIENT_RESP_SHIFT			8
#घोषणा		CLIENT_CG_REQ(x)			((x) << 16)
#घोषणा		CLIENT_CG_REQ_MASK			(0xff << 16)
#घोषणा		CLIENT_CG_REQ_SHIFT			16
#घोषणा		CLIENT_CG_RESP(x)			((x) << 24)
#घोषणा		CLIENT_CG_RESP_MASK			(0xff << 24)
#घोषणा		CLIENT_CG_RESP_SHIFT			24

#घोषणा	CG_SPLL_SPREAD_SPECTRUM				0x790
#घोषणा		SSEN					(1 << 0)
#घोषणा		CLK_S(x)				((x) << 4)
#घोषणा		CLK_S_MASK				(0xfff << 4)
#घोषणा		CLK_S_SHIFT				4
#घोषणा	CG_SPLL_SPREAD_SPECTRUM_2			0x794
#घोषणा		CLK_V(x)				((x) << 0)
#घोषणा		CLK_V_MASK				(0x3ffffff << 0)
#घोषणा		CLK_V_SHIFT				0

#घोषणा SMC_SCRATCH0                                    0x81c

#घोषणा	CG_SPLL_FUNC_CNTL_4				0x850

#घोषणा	MPLL_SS1					0x85c
#घोषणा		CLKV(x)					((x) << 0)
#घोषणा		CLKV_MASK				(0x3ffffff << 0)
#घोषणा	MPLL_SS2					0x860
#घोषणा		CLKS(x)					((x) << 0)
#घोषणा		CLKS_MASK				(0xfff << 0)

#घोषणा	CG_CAC_CTRL					0x88c
#घोषणा		TID_CNT(x)				((x) << 0)
#घोषणा		TID_CNT_MASK				(0x3fff << 0)
#घोषणा		TID_UNIT(x)				((x) << 14)
#घोषणा		TID_UNIT_MASK				(0xf << 14)

#घोषणा	CG_IND_ADDR					0x8f8
#घोषणा	CG_IND_DATA					0x8fc
/* CGIND regs */
#घोषणा	CG_CGTT_LOCAL_0					0x00
#घोषणा	CG_CGTT_LOCAL_1					0x01

#घोषणा MC_CG_CONFIG                                    0x25bc
#घोषणा         MCDW_WR_ENABLE                          (1 << 0)
#घोषणा         MCDX_WR_ENABLE                          (1 << 1)
#घोषणा         MCDY_WR_ENABLE                          (1 << 2)
#घोषणा         MCDZ_WR_ENABLE                          (1 << 3)
#घोषणा		MC_RD_ENABLE(x)				((x) << 4)
#घोषणा		MC_RD_ENABLE_MASK			(3 << 4)
#घोषणा		INDEX(x)				((x) << 6)
#घोषणा		INDEX_MASK				(0xfff << 6)
#घोषणा		INDEX_SHIFT				6

#घोषणा	MC_ARB_CAC_CNTL					0x2750
#घोषणा         ENABLE                                  (1 << 0)
#घोषणा		READ_WEIGHT(x)				((x) << 1)
#घोषणा		READ_WEIGHT_MASK			(0x3f << 1)
#घोषणा		READ_WEIGHT_SHIFT			1
#घोषणा		WRITE_WEIGHT(x)				((x) << 7)
#घोषणा		WRITE_WEIGHT_MASK			(0x3f << 7)
#घोषणा		WRITE_WEIGHT_SHIFT			7
#घोषणा         ALLOW_OVERFLOW                          (1 << 13)

#घोषणा	MC_ARB_DRAM_TIMING				0x2774
#घोषणा	MC_ARB_DRAM_TIMING2				0x2778

#घोषणा	MC_ARB_RFSH_RATE				0x27b0
#घोषणा		POWERMODE0(x)				((x) << 0)
#घोषणा		POWERMODE0_MASK				(0xff << 0)
#घोषणा		POWERMODE0_SHIFT			0
#घोषणा		POWERMODE1(x)				((x) << 8)
#घोषणा		POWERMODE1_MASK				(0xff << 8)
#घोषणा		POWERMODE1_SHIFT			8
#घोषणा		POWERMODE2(x)				((x) << 16)
#घोषणा		POWERMODE2_MASK				(0xff << 16)
#घोषणा		POWERMODE2_SHIFT			16
#घोषणा		POWERMODE3(x)				((x) << 24)
#घोषणा		POWERMODE3_MASK				(0xff << 24)
#घोषणा		POWERMODE3_SHIFT			24

#घोषणा MC_ARB_CG                                       0x27e8
#घोषणा		CG_ARB_REQ(x)				((x) << 0)
#घोषणा		CG_ARB_REQ_MASK				(0xff << 0)
#घोषणा		CG_ARB_REQ_SHIFT			0
#घोषणा		CG_ARB_RESP(x)				((x) << 8)
#घोषणा		CG_ARB_RESP_MASK			(0xff << 8)
#घोषणा		CG_ARB_RESP_SHIFT			8
#घोषणा		ARB_CG_REQ(x)				((x) << 16)
#घोषणा		ARB_CG_REQ_MASK				(0xff << 16)
#घोषणा		ARB_CG_REQ_SHIFT			16
#घोषणा		ARB_CG_RESP(x)				((x) << 24)
#घोषणा		ARB_CG_RESP_MASK			(0xff << 24)
#घोषणा		ARB_CG_RESP_SHIFT			24

#घोषणा	MC_ARB_DRAM_TIMING_1				0x27f0
#घोषणा	MC_ARB_DRAM_TIMING_2				0x27f4
#घोषणा	MC_ARB_DRAM_TIMING_3				0x27f8
#घोषणा	MC_ARB_DRAM_TIMING2_1				0x27fc
#घोषणा	MC_ARB_DRAM_TIMING2_2				0x2800
#घोषणा	MC_ARB_DRAM_TIMING2_3				0x2804
#घोषणा MC_ARB_BURST_TIME                               0x2808
#घोषणा		STATE0(x)				((x) << 0)
#घोषणा		STATE0_MASK				(0x1f << 0)
#घोषणा		STATE0_SHIFT				0
#घोषणा		STATE1(x)				((x) << 5)
#घोषणा		STATE1_MASK				(0x1f << 5)
#घोषणा		STATE1_SHIFT				5
#घोषणा		STATE2(x)				((x) << 10)
#घोषणा		STATE2_MASK				(0x1f << 10)
#घोषणा		STATE2_SHIFT				10
#घोषणा		STATE3(x)				((x) << 15)
#घोषणा		STATE3_MASK				(0x1f << 15)
#घोषणा		STATE3_SHIFT				15

#घोषणा MC_CG_DATAPORT                                  0x2884

#घोषणा MC_SEQ_RAS_TIMING                               0x28a0
#घोषणा MC_SEQ_CAS_TIMING                               0x28a4
#घोषणा MC_SEQ_MISC_TIMING                              0x28a8
#घोषणा MC_SEQ_MISC_TIMING2                             0x28ac
#घोषणा MC_SEQ_PMG_TIMING                               0x28b0
#घोषणा MC_SEQ_RD_CTL_D0                                0x28b4
#घोषणा MC_SEQ_RD_CTL_D1                                0x28b8
#घोषणा MC_SEQ_WR_CTL_D0                                0x28bc
#घोषणा MC_SEQ_WR_CTL_D1                                0x28c0

#घोषणा MC_SEQ_MISC0                                    0x2a00
#घोषणा         MC_SEQ_MISC0_GDDR5_SHIFT                28
#घोषणा         MC_SEQ_MISC0_GDDR5_MASK                 0xf0000000
#घोषणा         MC_SEQ_MISC0_GDDR5_VALUE                5
#घोषणा MC_SEQ_MISC1                                    0x2a04
#घोषणा MC_SEQ_RESERVE_M                                0x2a08
#घोषणा MC_PMG_CMD_EMRS                                 0x2a0c

#घोषणा MC_SEQ_MISC3                                    0x2a2c

#घोषणा MC_SEQ_MISC5                                    0x2a54
#घोषणा MC_SEQ_MISC6                                    0x2a58

#घोषणा MC_SEQ_MISC7                                    0x2a64

#घोषणा MC_SEQ_RAS_TIMING_LP                            0x2a6c
#घोषणा MC_SEQ_CAS_TIMING_LP                            0x2a70
#घोषणा MC_SEQ_MISC_TIMING_LP                           0x2a74
#घोषणा MC_SEQ_MISC_TIMING2_LP                          0x2a78
#घोषणा MC_SEQ_WR_CTL_D0_LP                             0x2a7c
#घोषणा MC_SEQ_WR_CTL_D1_LP                             0x2a80
#घोषणा MC_SEQ_PMG_CMD_EMRS_LP                          0x2a84
#घोषणा MC_SEQ_PMG_CMD_MRS_LP                           0x2a88

#घोषणा MC_PMG_CMD_MRS                                  0x2aac

#घोषणा MC_SEQ_RD_CTL_D0_LP                             0x2b1c
#घोषणा MC_SEQ_RD_CTL_D1_LP                             0x2b20

#घोषणा MC_PMG_CMD_MRS1                                 0x2b44
#घोषणा MC_SEQ_PMG_CMD_MRS1_LP                          0x2b48
#घोषणा MC_SEQ_PMG_TIMING_LP                            0x2b4c

#घोषणा MC_PMG_CMD_MRS2                                 0x2b5c
#घोषणा MC_SEQ_PMG_CMD_MRS2_LP                          0x2b60

#घोषणा AUX_CONTROL					0x6200
#घोषणा 	AUX_EN					(1 << 0)
#घोषणा 	AUX_LS_READ_EN				(1 << 8)
#घोषणा 	AUX_LS_UPDATE_DISABLE(x)		(((x) & 0x1) << 12)
#घोषणा 	AUX_HPD_DISCON(x)			(((x) & 0x1) << 16)
#घोषणा 	AUX_DET_EN				(1 << 18)
#घोषणा 	AUX_HPD_SEL(x)				(((x) & 0x7) << 20)
#घोषणा 	AUX_IMPCAL_REQ_EN			(1 << 24)
#घोषणा 	AUX_TEST_MODE				(1 << 28)
#घोषणा 	AUX_DEGLITCH_EN				(1 << 29)
#घोषणा AUX_SW_CONTROL					0x6204
#घोषणा 	AUX_SW_GO				(1 << 0)
#घोषणा 	AUX_LS_READ_TRIG			(1 << 2)
#घोषणा 	AUX_SW_START_DELAY(x)			(((x) & 0xf) << 4)
#घोषणा 	AUX_SW_WR_BYTES(x)			(((x) & 0x1f) << 16)

#घोषणा AUX_SW_INTERRUPT_CONTROL			0x620c
#घोषणा 	AUX_SW_DONE_INT				(1 << 0)
#घोषणा 	AUX_SW_DONE_ACK				(1 << 1)
#घोषणा 	AUX_SW_DONE_MASK			(1 << 2)
#घोषणा 	AUX_SW_LS_DONE_INT			(1 << 4)
#घोषणा 	AUX_SW_LS_DONE_MASK			(1 << 6)
#घोषणा AUX_SW_STATUS					0x6210
#घोषणा 	AUX_SW_DONE				(1 << 0)
#घोषणा 	AUX_SW_REQ				(1 << 1)
#घोषणा 	AUX_SW_RX_TIMEOUT_STATE(x)		(((x) & 0x7) << 4)
#घोषणा 	AUX_SW_RX_TIMEOUT			(1 << 7)
#घोषणा 	AUX_SW_RX_OVERFLOW			(1 << 8)
#घोषणा 	AUX_SW_RX_HPD_DISCON			(1 << 9)
#घोषणा 	AUX_SW_RX_PARTIAL_BYTE			(1 << 10)
#घोषणा 	AUX_SW_NON_AUX_MODE			(1 << 11)
#घोषणा 	AUX_SW_RX_MIN_COUNT_VIOL		(1 << 12)
#घोषणा 	AUX_SW_RX_INVALID_STOP			(1 << 14)
#घोषणा 	AUX_SW_RX_SYNC_INVALID_L		(1 << 17)
#घोषणा 	AUX_SW_RX_SYNC_INVALID_H		(1 << 18)
#घोषणा 	AUX_SW_RX_INVALID_START			(1 << 19)
#घोषणा 	AUX_SW_RX_RECV_NO_DET			(1 << 20)
#घोषणा 	AUX_SW_RX_RECV_INVALID_H		(1 << 22)
#घोषणा 	AUX_SW_RX_RECV_INVALID_V		(1 << 23)

#घोषणा AUX_SW_DATA					0x6218
#घोषणा AUX_SW_DATA_RW					(1 << 0)
#घोषणा AUX_SW_DATA_MASK(x)				(((x) & 0xff) << 8)
#घोषणा AUX_SW_DATA_INDEX(x)				(((x) & 0x1f) << 16)
#घोषणा AUX_SW_AUTOINCREMENT_DISABLE			(1 << 31)

#घोषणा	LB_SYNC_RESET_SEL				0x6b28
#घोषणा		LB_SYNC_RESET_SEL_MASK			(3 << 0)
#घोषणा		LB_SYNC_RESET_SEL_SHIFT			0

#घोषणा	DC_STUTTER_CNTL					0x6b30
#घोषणा		DC_STUTTER_ENABLE_A			(1 << 0)
#घोषणा		DC_STUTTER_ENABLE_B			(1 << 1)

#घोषणा SQ_CAC_THRESHOLD                                0x8e4c
#घोषणा		VSP(x)					((x) << 0)
#घोषणा		VSP_MASK				(0xff << 0)
#घोषणा		VSP_SHIFT				0
#घोषणा		VSP0(x)					((x) << 8)
#घोषणा		VSP0_MASK				(0xff << 8)
#घोषणा		VSP0_SHIFT				8
#घोषणा		GPR(x)					((x) << 16)
#घोषणा		GPR_MASK				(0xff << 16)
#घोषणा		GPR_SHIFT				16

#घोषणा SQ_POWER_THROTTLE                               0x8e58
#घोषणा		MIN_POWER(x)				((x) << 0)
#घोषणा		MIN_POWER_MASK				(0x3fff << 0)
#घोषणा		MIN_POWER_SHIFT				0
#घोषणा		MAX_POWER(x)				((x) << 16)
#घोषणा		MAX_POWER_MASK				(0x3fff << 16)
#घोषणा		MAX_POWER_SHIFT				0
#घोषणा SQ_POWER_THROTTLE2                              0x8e5c
#घोषणा		MAX_POWER_DELTA(x)			((x) << 0)
#घोषणा		MAX_POWER_DELTA_MASK			(0x3fff << 0)
#घोषणा		MAX_POWER_DELTA_SHIFT			0
#घोषणा		STI_SIZE(x)				((x) << 16)
#घोषणा		STI_SIZE_MASK				(0x3ff << 16)
#घोषणा		STI_SIZE_SHIFT				16
#घोषणा		LTI_RATIO(x)				((x) << 27)
#घोषणा		LTI_RATIO_MASK				(0xf << 27)
#घोषणा		LTI_RATIO_SHIFT				27

/* CG indirect रेजिस्टरs */
#घोषणा CG_CAC_REGION_1_WEIGHT_0                        0x83
#घोषणा		WEIGHT_TCP_SIG0(x)			((x) << 0)
#घोषणा		WEIGHT_TCP_SIG0_MASK			(0x3f << 0)
#घोषणा		WEIGHT_TCP_SIG0_SHIFT			0
#घोषणा		WEIGHT_TCP_SIG1(x)			((x) << 6)
#घोषणा		WEIGHT_TCP_SIG1_MASK			(0x3f << 6)
#घोषणा		WEIGHT_TCP_SIG1_SHIFT			6
#घोषणा		WEIGHT_TA_SIG(x)			((x) << 12)
#घोषणा		WEIGHT_TA_SIG_MASK			(0x3f << 12)
#घोषणा		WEIGHT_TA_SIG_SHIFT			12
#घोषणा CG_CAC_REGION_1_WEIGHT_1                        0x84
#घोषणा		WEIGHT_TCC_EN0(x)			((x) << 0)
#घोषणा		WEIGHT_TCC_EN0_MASK			(0x3f << 0)
#घोषणा		WEIGHT_TCC_EN0_SHIFT			0
#घोषणा		WEIGHT_TCC_EN1(x)			((x) << 6)
#घोषणा		WEIGHT_TCC_EN1_MASK			(0x3f << 6)
#घोषणा		WEIGHT_TCC_EN1_SHIFT			6
#घोषणा		WEIGHT_TCC_EN2(x)			((x) << 12)
#घोषणा		WEIGHT_TCC_EN2_MASK			(0x3f << 12)
#घोषणा		WEIGHT_TCC_EN2_SHIFT			12
#घोषणा		WEIGHT_TCC_EN3(x)			((x) << 18)
#घोषणा		WEIGHT_TCC_EN3_MASK			(0x3f << 18)
#घोषणा		WEIGHT_TCC_EN3_SHIFT			18
#घोषणा CG_CAC_REGION_2_WEIGHT_0                        0x85
#घोषणा		WEIGHT_CB_EN0(x)			((x) << 0)
#घोषणा		WEIGHT_CB_EN0_MASK			(0x3f << 0)
#घोषणा		WEIGHT_CB_EN0_SHIFT			0
#घोषणा		WEIGHT_CB_EN1(x)			((x) << 6)
#घोषणा		WEIGHT_CB_EN1_MASK			(0x3f << 6)
#घोषणा		WEIGHT_CB_EN1_SHIFT			6
#घोषणा		WEIGHT_CB_EN2(x)			((x) << 12)
#घोषणा		WEIGHT_CB_EN2_MASK			(0x3f << 12)
#घोषणा		WEIGHT_CB_EN2_SHIFT			12
#घोषणा		WEIGHT_CB_EN3(x)			((x) << 18)
#घोषणा		WEIGHT_CB_EN3_MASK			(0x3f << 18)
#घोषणा		WEIGHT_CB_EN3_SHIFT			18
#घोषणा CG_CAC_REGION_2_WEIGHT_1                        0x86
#घोषणा		WEIGHT_DB_SIG0(x)			((x) << 0)
#घोषणा		WEIGHT_DB_SIG0_MASK			(0x3f << 0)
#घोषणा		WEIGHT_DB_SIG0_SHIFT			0
#घोषणा		WEIGHT_DB_SIG1(x)			((x) << 6)
#घोषणा		WEIGHT_DB_SIG1_MASK			(0x3f << 6)
#घोषणा		WEIGHT_DB_SIG1_SHIFT			6
#घोषणा		WEIGHT_DB_SIG2(x)			((x) << 12)
#घोषणा		WEIGHT_DB_SIG2_MASK			(0x3f << 12)
#घोषणा		WEIGHT_DB_SIG2_SHIFT			12
#घोषणा		WEIGHT_DB_SIG3(x)			((x) << 18)
#घोषणा		WEIGHT_DB_SIG3_MASK			(0x3f << 18)
#घोषणा		WEIGHT_DB_SIG3_SHIFT			18
#घोषणा CG_CAC_REGION_2_WEIGHT_2                        0x87
#घोषणा		WEIGHT_SXM_SIG0(x)			((x) << 0)
#घोषणा		WEIGHT_SXM_SIG0_MASK			(0x3f << 0)
#घोषणा		WEIGHT_SXM_SIG0_SHIFT			0
#घोषणा		WEIGHT_SXM_SIG1(x)			((x) << 6)
#घोषणा		WEIGHT_SXM_SIG1_MASK			(0x3f << 6)
#घोषणा		WEIGHT_SXM_SIG1_SHIFT			6
#घोषणा		WEIGHT_SXM_SIG2(x)			((x) << 12)
#घोषणा		WEIGHT_SXM_SIG2_MASK			(0x3f << 12)
#घोषणा		WEIGHT_SXM_SIG2_SHIFT			12
#घोषणा		WEIGHT_SXS_SIG0(x)			((x) << 18)
#घोषणा		WEIGHT_SXS_SIG0_MASK			(0x3f << 18)
#घोषणा		WEIGHT_SXS_SIG0_SHIFT			18
#घोषणा		WEIGHT_SXS_SIG1(x)			((x) << 24)
#घोषणा		WEIGHT_SXS_SIG1_MASK			(0x3f << 24)
#घोषणा		WEIGHT_SXS_SIG1_SHIFT			24
#घोषणा CG_CAC_REGION_3_WEIGHT_0                        0x88
#घोषणा		WEIGHT_XBR_0(x)				((x) << 0)
#घोषणा		WEIGHT_XBR_0_MASK			(0x3f << 0)
#घोषणा		WEIGHT_XBR_0_SHIFT			0
#घोषणा		WEIGHT_XBR_1(x)				((x) << 6)
#घोषणा		WEIGHT_XBR_1_MASK			(0x3f << 6)
#घोषणा		WEIGHT_XBR_1_SHIFT			6
#घोषणा		WEIGHT_XBR_2(x)				((x) << 12)
#घोषणा		WEIGHT_XBR_2_MASK			(0x3f << 12)
#घोषणा		WEIGHT_XBR_2_SHIFT			12
#घोषणा		WEIGHT_SPI_SIG0(x)			((x) << 18)
#घोषणा		WEIGHT_SPI_SIG0_MASK			(0x3f << 18)
#घोषणा		WEIGHT_SPI_SIG0_SHIFT			18
#घोषणा CG_CAC_REGION_3_WEIGHT_1                        0x89
#घोषणा		WEIGHT_SPI_SIG1(x)			((x) << 0)
#घोषणा		WEIGHT_SPI_SIG1_MASK			(0x3f << 0)
#घोषणा		WEIGHT_SPI_SIG1_SHIFT			0
#घोषणा		WEIGHT_SPI_SIG2(x)			((x) << 6)
#घोषणा		WEIGHT_SPI_SIG2_MASK			(0x3f << 6)
#घोषणा		WEIGHT_SPI_SIG2_SHIFT			6
#घोषणा		WEIGHT_SPI_SIG3(x)			((x) << 12)
#घोषणा		WEIGHT_SPI_SIG3_MASK			(0x3f << 12)
#घोषणा		WEIGHT_SPI_SIG3_SHIFT			12
#घोषणा		WEIGHT_SPI_SIG4(x)			((x) << 18)
#घोषणा		WEIGHT_SPI_SIG4_MASK			(0x3f << 18)
#घोषणा		WEIGHT_SPI_SIG4_SHIFT			18
#घोषणा		WEIGHT_SPI_SIG5(x)			((x) << 24)
#घोषणा		WEIGHT_SPI_SIG5_MASK			(0x3f << 24)
#घोषणा		WEIGHT_SPI_SIG5_SHIFT			24
#घोषणा CG_CAC_REGION_4_WEIGHT_0                        0x8a
#घोषणा		WEIGHT_LDS_SIG0(x)			((x) << 0)
#घोषणा		WEIGHT_LDS_SIG0_MASK			(0x3f << 0)
#घोषणा		WEIGHT_LDS_SIG0_SHIFT			0
#घोषणा		WEIGHT_LDS_SIG1(x)			((x) << 6)
#घोषणा		WEIGHT_LDS_SIG1_MASK			(0x3f << 6)
#घोषणा		WEIGHT_LDS_SIG1_SHIFT			6
#घोषणा		WEIGHT_SC(x)				((x) << 24)
#घोषणा		WEIGHT_SC_MASK				(0x3f << 24)
#घोषणा		WEIGHT_SC_SHIFT				24
#घोषणा CG_CAC_REGION_4_WEIGHT_1                        0x8b
#घोषणा		WEIGHT_BIF(x)				((x) << 0)
#घोषणा		WEIGHT_BIF_MASK				(0x3f << 0)
#घोषणा		WEIGHT_BIF_SHIFT			0
#घोषणा		WEIGHT_CP(x)				((x) << 6)
#घोषणा		WEIGHT_CP_MASK				(0x3f << 6)
#घोषणा		WEIGHT_CP_SHIFT				6
#घोषणा		WEIGHT_PA_SIG0(x)			((x) << 12)
#घोषणा		WEIGHT_PA_SIG0_MASK			(0x3f << 12)
#घोषणा		WEIGHT_PA_SIG0_SHIFT			12
#घोषणा		WEIGHT_PA_SIG1(x)			((x) << 18)
#घोषणा		WEIGHT_PA_SIG1_MASK			(0x3f << 18)
#घोषणा		WEIGHT_PA_SIG1_SHIFT			18
#घोषणा		WEIGHT_VGT_SIG0(x)			((x) << 24)
#घोषणा		WEIGHT_VGT_SIG0_MASK			(0x3f << 24)
#घोषणा		WEIGHT_VGT_SIG0_SHIFT			24
#घोषणा CG_CAC_REGION_4_WEIGHT_2                        0x8c
#घोषणा		WEIGHT_VGT_SIG1(x)			((x) << 0)
#घोषणा		WEIGHT_VGT_SIG1_MASK			(0x3f << 0)
#घोषणा		WEIGHT_VGT_SIG1_SHIFT			0
#घोषणा		WEIGHT_VGT_SIG2(x)			((x) << 6)
#घोषणा		WEIGHT_VGT_SIG2_MASK			(0x3f << 6)
#घोषणा		WEIGHT_VGT_SIG2_SHIFT			6
#घोषणा		WEIGHT_DC_SIG0(x)			((x) << 12)
#घोषणा		WEIGHT_DC_SIG0_MASK			(0x3f << 12)
#घोषणा		WEIGHT_DC_SIG0_SHIFT			12
#घोषणा		WEIGHT_DC_SIG1(x)			((x) << 18)
#घोषणा		WEIGHT_DC_SIG1_MASK			(0x3f << 18)
#घोषणा		WEIGHT_DC_SIG1_SHIFT			18
#घोषणा		WEIGHT_DC_SIG2(x)			((x) << 24)
#घोषणा		WEIGHT_DC_SIG2_MASK			(0x3f << 24)
#घोषणा		WEIGHT_DC_SIG2_SHIFT			24
#घोषणा CG_CAC_REGION_4_WEIGHT_3                        0x8d
#घोषणा		WEIGHT_DC_SIG3(x)			((x) << 0)
#घोषणा		WEIGHT_DC_SIG3_MASK			(0x3f << 0)
#घोषणा		WEIGHT_DC_SIG3_SHIFT			0
#घोषणा		WEIGHT_UVD_SIG0(x)			((x) << 6)
#घोषणा		WEIGHT_UVD_SIG0_MASK			(0x3f << 6)
#घोषणा		WEIGHT_UVD_SIG0_SHIFT			6
#घोषणा		WEIGHT_UVD_SIG1(x)			((x) << 12)
#घोषणा		WEIGHT_UVD_SIG1_MASK			(0x3f << 12)
#घोषणा		WEIGHT_UVD_SIG1_SHIFT			12
#घोषणा		WEIGHT_SPARE0(x)			((x) << 18)
#घोषणा		WEIGHT_SPARE0_MASK			(0x3f << 18)
#घोषणा		WEIGHT_SPARE0_SHIFT			18
#घोषणा		WEIGHT_SPARE1(x)			((x) << 24)
#घोषणा		WEIGHT_SPARE1_MASK			(0x3f << 24)
#घोषणा		WEIGHT_SPARE1_SHIFT			24
#घोषणा CG_CAC_REGION_5_WEIGHT_0                        0x8e
#घोषणा		WEIGHT_SQ_VSP(x)			((x) << 0)
#घोषणा		WEIGHT_SQ_VSP_MASK			(0x3fff << 0)
#घोषणा		WEIGHT_SQ_VSP_SHIFT			0
#घोषणा		WEIGHT_SQ_VSP0(x)			((x) << 14)
#घोषणा		WEIGHT_SQ_VSP0_MASK			(0x3fff << 14)
#घोषणा		WEIGHT_SQ_VSP0_SHIFT			14
#घोषणा CG_CAC_REGION_4_OVERRIDE_4                      0xab
#घोषणा		OVR_MODE_SPARE_0(x)			((x) << 16)
#घोषणा		OVR_MODE_SPARE_0_MASK			(0x1 << 16)
#घोषणा		OVR_MODE_SPARE_0_SHIFT			16
#घोषणा		OVR_VAL_SPARE_0(x)			((x) << 17)
#घोषणा		OVR_VAL_SPARE_0_MASK			(0x1 << 17)
#घोषणा		OVR_VAL_SPARE_0_SHIFT			17
#घोषणा		OVR_MODE_SPARE_1(x)			((x) << 18)
#घोषणा		OVR_MODE_SPARE_1_MASK			(0x3f << 18)
#घोषणा		OVR_MODE_SPARE_1_SHIFT			18
#घोषणा		OVR_VAL_SPARE_1(x)			((x) << 19)
#घोषणा		OVR_VAL_SPARE_1_MASK			(0x3f << 19)
#घोषणा		OVR_VAL_SPARE_1_SHIFT			19
#घोषणा CG_CAC_REGION_5_WEIGHT_1                        0xb7
#घोषणा		WEIGHT_SQ_GPR(x)			((x) << 0)
#घोषणा		WEIGHT_SQ_GPR_MASK			(0x3fff << 0)
#घोषणा		WEIGHT_SQ_GPR_SHIFT			0
#घोषणा		WEIGHT_SQ_LDS(x)			((x) << 14)
#घोषणा		WEIGHT_SQ_LDS_MASK			(0x3fff << 14)
#घोषणा		WEIGHT_SQ_LDS_SHIFT			14

/* PCIE link stuff */
#घोषणा PCIE_LC_TRAINING_CNTL                             0xa1 /* PCIE_P */
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
#       define LC_HW_VOLTAGE_IF_CONTROL(x)                ((x) << 12)
#       define LC_HW_VOLTAGE_IF_CONTROL_MASK              (3 << 12)
#       define LC_HW_VOLTAGE_IF_CONTROL_SHIFT             12
#       define LC_VOLTAGE_TIMER_SEL_MASK                  (0xf << 14)
#       define LC_CLR_FAILED_SPD_CHANGE_CNT               (1 << 21)
#       define LC_OTHER_SIDE_EVER_SENT_GEN2               (1 << 23)
#       define LC_OTHER_SIDE_SUPPORTS_GEN2                (1 << 24)
#घोषणा MM_CFGREGS_CNTL                                   0x544c
#       define MM_WR_TO_CFG_EN                            (1 << 3)
#घोषणा LINK_CNTL2                                        0x88 /* F0 */
#       define TARGET_LINK_SPEED_MASK                     (0xf << 0)
#       define SELECTABLE_DEEMPHASIS                      (1 << 6)

/*
 * UVD
 */
#घोषणा UVD_SEMA_ADDR_LOW				0xEF00
#घोषणा UVD_SEMA_ADDR_HIGH				0xEF04
#घोषणा UVD_SEMA_CMD					0xEF08
#घोषणा UVD_UDEC_ADDR_CONFIG				0xEF4C
#घोषणा UVD_UDEC_DB_ADDR_CONFIG				0xEF50
#घोषणा UVD_UDEC_DBW_ADDR_CONFIG			0xEF54
#घोषणा UVD_NO_OP					0xEFFC
#घोषणा UVD_RBC_RB_RPTR					0xF690
#घोषणा UVD_RBC_RB_WPTR					0xF694
#घोषणा UVD_STATUS					0xf6bc

/*
 * PM4
 */
#घोषणा PACKET0(reg, n)	((RADEON_PACKET_TYPE0 << 30) |			\
			 (((reg) >> 2) & 0xFFFF) |			\
			 ((n) & 0x3FFF) << 16)
#घोषणा CP_PACKET2			0x80000000
#घोषणा		PACKET2_PAD_SHIFT		0
#घोषणा		PACKET2_PAD_MASK		(0x3fffffff << 0)

#घोषणा PACKET2(v)	(CP_PACKET2 | REG_SET(PACKET2_PAD, (v)))

#घोषणा PACKET3(op, n)	((RADEON_PACKET_TYPE3 << 30) |			\
			 (((op) & 0xFF) << 8) |				\
			 ((n) & 0x3FFF) << 16)

/* Packet 3 types */
#घोषणा	PACKET3_NOP					0x10
#घोषणा	PACKET3_SET_BASE				0x11
#घोषणा	PACKET3_CLEAR_STATE				0x12
#घोषणा	PACKET3_INDEX_BUFFER_SIZE			0x13
#घोषणा	PACKET3_DEALLOC_STATE				0x14
#घोषणा	PACKET3_DISPATCH_सूचीECT				0x15
#घोषणा	PACKET3_DISPATCH_INसूचीECT			0x16
#घोषणा	PACKET3_INसूचीECT_BUFFER_END			0x17
#घोषणा	PACKET3_MODE_CONTROL				0x18
#घोषणा	PACKET3_SET_PREDICATION				0x20
#घोषणा	PACKET3_REG_RMW					0x21
#घोषणा	PACKET3_COND_EXEC				0x22
#घोषणा	PACKET3_PRED_EXEC				0x23
#घोषणा	PACKET3_DRAW_INसूचीECT				0x24
#घोषणा	PACKET3_DRAW_INDEX_INसूचीECT			0x25
#घोषणा	PACKET3_INDEX_BASE				0x26
#घोषणा	PACKET3_DRAW_INDEX_2				0x27
#घोषणा	PACKET3_CONTEXT_CONTROL				0x28
#घोषणा	PACKET3_DRAW_INDEX_OFFSET			0x29
#घोषणा	PACKET3_INDEX_TYPE				0x2A
#घोषणा	PACKET3_DRAW_INDEX				0x2B
#घोषणा	PACKET3_DRAW_INDEX_AUTO				0x2D
#घोषणा	PACKET3_DRAW_INDEX_IMMD				0x2E
#घोषणा	PACKET3_NUM_INSTANCES				0x2F
#घोषणा	PACKET3_DRAW_INDEX_MULTI_AUTO			0x30
#घोषणा	PACKET3_INसूचीECT_BUFFER				0x32
#घोषणा	PACKET3_STRMOUT_BUFFER_UPDATE			0x34
#घोषणा	PACKET3_DRAW_INDEX_OFFSET_2			0x35
#घोषणा	PACKET3_DRAW_INDEX_MULTI_ELEMENT		0x36
#घोषणा	PACKET3_WRITE_DATA				0x37
#घोषणा	PACKET3_MEM_SEMAPHORE				0x39
#घोषणा	PACKET3_MPEG_INDEX				0x3A
#घोषणा	PACKET3_WAIT_REG_MEM				0x3C
#घोषणा		WAIT_REG_MEM_FUNCTION(x)                ((x) << 0)
                /* 0 - always
		 * 1 - <
		 * 2 - <=
		 * 3 - ==
		 * 4 - !=
		 * 5 - >=
		 * 6 - >
		 */
#घोषणा		WAIT_REG_MEM_MEM_SPACE(x)               ((x) << 4)
                /* 0 - reg
		 * 1 - mem
		 */
#घोषणा		WAIT_REG_MEM_ENGINE(x)                  ((x) << 8)
                /* 0 - me
		 * 1 - pfp
		 */
#घोषणा	PACKET3_MEM_WRITE				0x3D
#घोषणा	PACKET3_PFP_SYNC_ME				0x42
#घोषणा	PACKET3_SURFACE_SYNC				0x43
#              define PACKET3_CB0_DEST_BASE_ENA    (1 << 6)
#              define PACKET3_CB1_DEST_BASE_ENA    (1 << 7)
#              define PACKET3_CB2_DEST_BASE_ENA    (1 << 8)
#              define PACKET3_CB3_DEST_BASE_ENA    (1 << 9)
#              define PACKET3_CB4_DEST_BASE_ENA    (1 << 10)
#              define PACKET3_CB5_DEST_BASE_ENA    (1 << 11)
#              define PACKET3_CB6_DEST_BASE_ENA    (1 << 12)
#              define PACKET3_CB7_DEST_BASE_ENA    (1 << 13)
#              define PACKET3_DB_DEST_BASE_ENA     (1 << 14)
#              define PACKET3_CB8_DEST_BASE_ENA    (1 << 15)
#              define PACKET3_CB9_DEST_BASE_ENA    (1 << 16)
#              define PACKET3_CB10_DEST_BASE_ENA   (1 << 17)
#              define PACKET3_CB11_DEST_BASE_ENA   (1 << 18)
#              define PACKET3_FULL_CACHE_ENA       (1 << 20)
#              define PACKET3_TC_ACTION_ENA        (1 << 23)
#              define PACKET3_CB_ACTION_ENA        (1 << 25)
#              define PACKET3_DB_ACTION_ENA        (1 << 26)
#              define PACKET3_SH_ACTION_ENA        (1 << 27)
#              define PACKET3_SX_ACTION_ENA        (1 << 28)
#              define PACKET3_ENGINE_ME            (1 << 31)
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
#घोषणा	PACKET3_EVENT_WRITE_EOS				0x48
#घोषणा	PACKET3_PREAMBLE_CNTL				0x4A
#              define PACKET3_PREAMBLE_BEGIN_CLEAR_STATE     (2 << 28)
#              define PACKET3_PREAMBLE_END_CLEAR_STATE       (3 << 28)
#घोषणा	PACKET3_ALU_PS_CONST_BUFFER_COPY		0x4C
#घोषणा	PACKET3_ALU_VS_CONST_BUFFER_COPY		0x4D
#घोषणा	PACKET3_ALU_PS_CONST_UPDATE		        0x4E
#घोषणा	PACKET3_ALU_VS_CONST_UPDATE		        0x4F
#घोषणा	PACKET3_ONE_REG_WRITE				0x57
#घोषणा	PACKET3_SET_CONFIG_REG				0x68
#घोषणा		PACKET3_SET_CONFIG_REG_START			0x00008000
#घोषणा		PACKET3_SET_CONFIG_REG_END			0x0000ac00
#घोषणा	PACKET3_SET_CONTEXT_REG				0x69
#घोषणा		PACKET3_SET_CONTEXT_REG_START			0x00028000
#घोषणा		PACKET3_SET_CONTEXT_REG_END			0x00029000
#घोषणा	PACKET3_SET_ALU_CONST				0x6A
/* alu स्थिर buffers only; no reg file */
#घोषणा	PACKET3_SET_BOOL_CONST				0x6B
#घोषणा		PACKET3_SET_BOOL_CONST_START			0x0003a500
#घोषणा		PACKET3_SET_BOOL_CONST_END			0x0003a518
#घोषणा	PACKET3_SET_LOOP_CONST				0x6C
#घोषणा		PACKET3_SET_LOOP_CONST_START			0x0003a200
#घोषणा		PACKET3_SET_LOOP_CONST_END			0x0003a500
#घोषणा	PACKET3_SET_RESOURCE				0x6D
#घोषणा		PACKET3_SET_RESOURCE_START			0x00030000
#घोषणा		PACKET3_SET_RESOURCE_END			0x00038000
#घोषणा	PACKET3_SET_SAMPLER				0x6E
#घोषणा		PACKET3_SET_SAMPLER_START			0x0003c000
#घोषणा		PACKET3_SET_SAMPLER_END				0x0003c600
#घोषणा	PACKET3_SET_CTL_CONST				0x6F
#घोषणा		PACKET3_SET_CTL_CONST_START			0x0003cff0
#घोषणा		PACKET3_SET_CTL_CONST_END			0x0003ff0c
#घोषणा	PACKET3_SET_RESOURCE_OFFSET			0x70
#घोषणा	PACKET3_SET_ALU_CONST_VS			0x71
#घोषणा	PACKET3_SET_ALU_CONST_DI			0x72
#घोषणा	PACKET3_SET_CONTEXT_REG_INसूचीECT		0x73
#घोषणा	PACKET3_SET_RESOURCE_INसूचीECT			0x74
#घोषणा	PACKET3_SET_APPEND_CNT			        0x75
#घोषणा	PACKET3_ME_WRITE				0x7A

/* ASYNC DMA - first instance at 0xd000, second at 0xd800 */
#घोषणा DMA0_REGISTER_OFFSET                              0x0 /* not a रेजिस्टर */
#घोषणा DMA1_REGISTER_OFFSET                              0x800 /* not a रेजिस्टर */

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
#       define CMD_VMID_FORCE                             (1 << 31)
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
#घोषणा DMA_TILING_CONFIG  				  0xd0b8
#घोषणा DMA_MODE                                          0xd0bc

#घोषणा DMA_PACKET(cmd, t, s, n)	((((cmd) & 0xF) << 28) |	\
					 (((t) & 0x1) << 23) |		\
					 (((s) & 0x1) << 22) |		\
					 (((n) & 0xFFFFF) << 0))

#घोषणा DMA_IB_PACKET(cmd, vmid, n)	((((cmd) & 0xF) << 28) |	\
					 (((vmid) & 0xF) << 20) |	\
					 (((n) & 0xFFFFF) << 0))

#घोषणा DMA_PTE_PDE_PACKET(n)		((2 << 28) |			\
					 (1 << 26) |			\
					 (1 << 21) |			\
					 (((n) & 0xFFFFF) << 0))

#घोषणा DMA_SRBM_POLL_PACKET		((9 << 28) |			\
					 (1 << 27) |			\
					 (1 << 26))

#घोषणा DMA_SRBM_READ_PACKET		((9 << 28) |			\
					 (1 << 27))

/* async DMA Packet types */
#घोषणा	DMA_PACKET_WRITE				  0x2
#घोषणा	DMA_PACKET_COPY					  0x3
#घोषणा	DMA_PACKET_INसूचीECT_BUFFER			  0x4
#घोषणा	DMA_PACKET_SEMAPHORE				  0x5
#घोषणा	DMA_PACKET_FENCE				  0x6
#घोषणा	DMA_PACKET_TRAP					  0x7
#घोषणा	DMA_PACKET_SRBM_WRITE				  0x9
#घोषणा	DMA_PACKET_CONSTANT_FILL			  0xd
#घोषणा	DMA_PACKET_NOP					  0xf

#पूर्ण_अगर
