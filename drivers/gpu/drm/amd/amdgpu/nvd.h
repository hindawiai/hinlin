<शैली गुरु>
/*
 * Copyright 2019 Advanced Micro Devices, Inc.
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

#अगर_अघोषित NVD_H
#घोषणा NVD_H

/**
 * Navi's PM4 definitions
 */
#घोषणा	PACKET_TYPE0	0
#घोषणा	PACKET_TYPE1	1
#घोषणा	PACKET_TYPE2	2
#घोषणा	PACKET_TYPE3	3

#घोषणा CP_PACKET_GET_TYPE(h) (((h) >> 30) & 3)
#घोषणा CP_PACKET_GET_COUNT(h) (((h) >> 16) & 0x3FFF)
#घोषणा CP_PACKET0_GET_REG(h) ((h) & 0xFFFF)
#घोषणा CP_PACKET3_GET_OPCODE(h) (((h) >> 8) & 0xFF)
#घोषणा PACKET0(reg, n)	((PACKET_TYPE0 << 30) |				\
			 ((reg) & 0xFFFF) |			\
			 ((n) & 0x3FFF) << 16)
#घोषणा CP_PACKET2			0x80000000
#घोषणा		PACKET2_PAD_SHIFT		0
#घोषणा		PACKET2_PAD_MASK		(0x3fffffff << 0)

#घोषणा PACKET2(v)	(CP_PACKET2 | REG_SET(PACKET2_PAD, (v)))

#घोषणा PACKET3(op, n)	((PACKET_TYPE3 << 30) |				\
			 (((op) & 0xFF) << 8) |				\
			 ((n) & 0x3FFF) << 16)

#घोषणा PACKET3_COMPUTE(op, n) (PACKET3(op, n) | 1 << 1)

/* Packet 3 types */
#घोषणा	PACKET3_NOP					0x10
#घोषणा	PACKET3_SET_BASE				0x11
#घोषणा		PACKET3_BASE_INDEX(x)                  ((x) << 0)
#घोषणा			CE_PARTITION_BASE		3
#घोषणा	PACKET3_CLEAR_STATE				0x12
#घोषणा	PACKET3_INDEX_BUFFER_SIZE			0x13
#घोषणा	PACKET3_DISPATCH_सूचीECT				0x15
#घोषणा	PACKET3_DISPATCH_INसूचीECT			0x16
#घोषणा	PACKET3_INसूचीECT_BUFFER_END			0x17
#घोषणा	PACKET3_INसूचीECT_BUFFER_CNST_END		0x19
#घोषणा	PACKET3_ATOMIC_GDS				0x1D
#घोषणा	PACKET3_ATOMIC_MEM				0x1E
#घोषणा	PACKET3_OCCLUSION_QUERY				0x1F
#घोषणा	PACKET3_SET_PREDICATION				0x20
#घोषणा	PACKET3_REG_RMW					0x21
#घोषणा	PACKET3_COND_EXEC				0x22
#घोषणा	PACKET3_PRED_EXEC				0x23
#घोषणा	PACKET3_DRAW_INसूचीECT				0x24
#घोषणा	PACKET3_DRAW_INDEX_INसूचीECT			0x25
#घोषणा	PACKET3_INDEX_BASE				0x26
#घोषणा	PACKET3_DRAW_INDEX_2				0x27
#घोषणा	PACKET3_CONTEXT_CONTROL				0x28
#घोषणा	PACKET3_INDEX_TYPE				0x2A
#घोषणा	PACKET3_DRAW_INसूचीECT_MULTI			0x2C
#घोषणा	PACKET3_DRAW_INDEX_AUTO				0x2D
#घोषणा	PACKET3_NUM_INSTANCES				0x2F
#घोषणा	PACKET3_DRAW_INDEX_MULTI_AUTO			0x30
#घोषणा	PACKET3_INसूचीECT_BUFFER_PRIV			0x32
#घोषणा	PACKET3_INसूचीECT_BUFFER_CNST			0x33
#घोषणा	PACKET3_COND_INसूचीECT_BUFFER_CNST		0x33
#घोषणा	PACKET3_STRMOUT_BUFFER_UPDATE			0x34
#घोषणा	PACKET3_DRAW_INDEX_OFFSET_2			0x35
#घोषणा	PACKET3_DRAW_PREAMBLE				0x36
#घोषणा	PACKET3_WRITE_DATA				0x37
#घोषणा		WRITE_DATA_DST_SEL(x)                   ((x) << 8)
		/* 0 - रेजिस्टर
		 * 1 - memory (sync - via GRBM)
		 * 2 - gl2
		 * 3 - gds
		 * 4 - reserved
		 * 5 - memory (async - direct)
		 */
#घोषणा		WR_ONE_ADDR                             (1 << 16)
#घोषणा		WR_CONFIRM                              (1 << 20)
#घोषणा		WRITE_DATA_CACHE_POLICY(x)              ((x) << 25)
		/* 0 - LRU
		 * 1 - Stream
		 */
#घोषणा		WRITE_DATA_ENGINE_SEL(x)                ((x) << 30)
		/* 0 - me
		 * 1 - pfp
		 * 2 - ce
		 */
#घोषणा	PACKET3_DRAW_INDEX_INसूचीECT_MULTI		0x38
#घोषणा	PACKET3_MEM_SEMAPHORE				0x39
#              define PACKET3_SEM_USE_MAILBOX       (0x1 << 16)
#              define PACKET3_SEM_SEL_SIGNAL_TYPE   (0x1 << 20) /* 0 = increment, 1 = ग_लिखो 1 */
#              define PACKET3_SEM_SEL_SIGNAL	    (0x6 << 29)
#              define PACKET3_SEM_SEL_WAIT	    (0x7 << 29)
#घोषणा	PACKET3_DRAW_INDEX_MULTI_INST			0x3A
#घोषणा	PACKET3_COPY_DW					0x3B
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
#घोषणा		WAIT_REG_MEM_OPERATION(x)               ((x) << 6)
		/* 0 - रुको_reg_mem
		 * 1 - wr_रुको_wr_reg
		 */
#घोषणा		WAIT_REG_MEM_ENGINE(x)                  ((x) << 8)
		/* 0 - me
		 * 1 - pfp
		 */
#घोषणा	PACKET3_INसूचीECT_BUFFER				0x3F
#घोषणा		INसूचीECT_BUFFER_VALID                   (1 << 23)
#घोषणा		INसूचीECT_BUFFER_CACHE_POLICY(x)         ((x) << 28)
		/* 0 - LRU
		 * 1 - Stream
		 * 2 - Bypass
		 */
#घोषणा		INसूचीECT_BUFFER_PRE_ENB(x)		((x) << 21)
#घोषणा		INसूचीECT_BUFFER_PRE_RESUME(x)           ((x) << 30)
#घोषणा	PACKET3_COND_INसूचीECT_BUFFER			0x3F
#घोषणा	PACKET3_COPY_DATA				0x40
#घोषणा	PACKET3_CP_DMA					0x41
#घोषणा	PACKET3_PFP_SYNC_ME				0x42
#घोषणा	PACKET3_SURFACE_SYNC				0x43
#घोषणा	PACKET3_ME_INITIALIZE				0x44
#घोषणा	PACKET3_COND_WRITE				0x45
#घोषणा	PACKET3_EVENT_WRITE				0x46
#घोषणा		EVENT_TYPE(x)                           ((x) << 0)
#घोषणा		EVENT_INDEX(x)                          ((x) << 8)
		/* 0 - any non-TS event
		 * 1 - ZPASS_DONE, PIXEL_PIPE_STAT_*
		 * 2 - SAMPLE_PIPELINESTAT
		 * 3 - SAMPLE_STREAMOUTSTAT*
		 * 4 - *S_PARTIAL_FLUSH
		 */
#घोषणा	PACKET3_EVENT_WRITE_EOP				0x47
#घोषणा	PACKET3_EVENT_WRITE_EOS				0x48
#घोषणा	PACKET3_RELEASE_MEM				0x49
#घोषणा		PACKET3_RELEASE_MEM_EVENT_TYPE(x)	((x) << 0)
#घोषणा		PACKET3_RELEASE_MEM_EVENT_INDEX(x)	((x) << 8)
#घोषणा		PACKET3_RELEASE_MEM_GCR_GLM_WB		(1 << 12)
#घोषणा		PACKET3_RELEASE_MEM_GCR_GLM_INV		(1 << 13)
#घोषणा		PACKET3_RELEASE_MEM_GCR_GLV_INV		(1 << 14)
#घोषणा		PACKET3_RELEASE_MEM_GCR_GL1_INV		(1 << 15)
#घोषणा		PACKET3_RELEASE_MEM_GCR_GL2_US		(1 << 16)
#घोषणा		PACKET3_RELEASE_MEM_GCR_GL2_RANGE	(1 << 17)
#घोषणा		PACKET3_RELEASE_MEM_GCR_GL2_DISCARD	(1 << 19)
#घोषणा		PACKET3_RELEASE_MEM_GCR_GL2_INV		(1 << 20)
#घोषणा		PACKET3_RELEASE_MEM_GCR_GL2_WB		(1 << 21)
#घोषणा		PACKET3_RELEASE_MEM_GCR_SEQ		(1 << 22)
#घोषणा		PACKET3_RELEASE_MEM_CACHE_POLICY(x)	((x) << 25)
		/* 0 - cache_policy__me_release_mem__lru
		 * 1 - cache_policy__me_release_mem__stream
		 * 2 - cache_policy__me_release_mem__noa
		 * 3 - cache_policy__me_release_mem__bypass
		 */
#घोषणा		PACKET3_RELEASE_MEM_EXECUTE		(1 << 28)

#घोषणा		PACKET3_RELEASE_MEM_DATA_SEL(x)		((x) << 29)
		/* 0 - discard
		 * 1 - send low 32bit data
		 * 2 - send 64bit data
		 * 3 - send 64bit GPU counter value
		 * 4 - send 64bit sys counter value
		 */
#घोषणा		PACKET3_RELEASE_MEM_INT_SEL(x)		((x) << 24)
		/* 0 - none
		 * 1 - पूर्णांकerrupt only (DATA_SEL = 0)
		 * 2 - पूर्णांकerrupt when data ग_लिखो is confirmed
		 */
#घोषणा		PACKET3_RELEASE_MEM_DST_SEL(x)		((x) << 16)
		/* 0 - MC
		 * 1 - TC/L2
		 */



#घोषणा	PACKET3_PREAMBLE_CNTL				0x4A
#              define PACKET3_PREAMBLE_BEGIN_CLEAR_STATE     (2 << 28)
#              define PACKET3_PREAMBLE_END_CLEAR_STATE       (3 << 28)
#घोषणा	PACKET3_DMA_DATA				0x50
/* 1. header
 * 2. CONTROL
 * 3. SRC_ADDR_LO or DATA [31:0]
 * 4. SRC_ADDR_HI [31:0]
 * 5. DST_ADDR_LO [31:0]
 * 6. DST_ADDR_HI [7:0]
 * 7. COMMAND [31:26] | BYTE_COUNT [25:0]
 */
/* CONTROL */
#              define PACKET3_DMA_DATA_ENGINE(x)     ((x) << 0)
		/* 0 - ME
		 * 1 - PFP
		 */
#              define PACKET3_DMA_DATA_SRC_CACHE_POLICY(x) ((x) << 13)
		/* 0 - LRU
		 * 1 - Stream
		 */
#              define PACKET3_DMA_DATA_DST_SEL(x)  ((x) << 20)
		/* 0 - DST_ADDR using DAS
		 * 1 - GDS
		 * 3 - DST_ADDR using L2
		 */
#              define PACKET3_DMA_DATA_DST_CACHE_POLICY(x) ((x) << 25)
		/* 0 - LRU
		 * 1 - Stream
		 */
#              define PACKET3_DMA_DATA_SRC_SEL(x)  ((x) << 29)
		/* 0 - SRC_ADDR using SAS
		 * 1 - GDS
		 * 2 - DATA
		 * 3 - SRC_ADDR using L2
		 */
#              define PACKET3_DMA_DATA_CP_SYNC     (1 << 31)
/* COMMAND */
#              define PACKET3_DMA_DATA_CMD_SAS     (1 << 26)
		/* 0 - memory
		 * 1 - रेजिस्टर
		 */
#              define PACKET3_DMA_DATA_CMD_DAS     (1 << 27)
		/* 0 - memory
		 * 1 - रेजिस्टर
		 */
#              define PACKET3_DMA_DATA_CMD_SAIC    (1 << 28)
#              define PACKET3_DMA_DATA_CMD_DAIC    (1 << 29)
#              define PACKET3_DMA_DATA_CMD_RAW_WAIT  (1 << 30)
#घोषणा	PACKET3_CONTEXT_REG_RMW				0x51
#घोषणा	PACKET3_GFX_CNTX_UPDATE				0x52
#घोषणा	PACKET3_BLK_CNTX_UPDATE				0x53
#घोषणा	PACKET3_INCR_UPDT_STATE				0x55
#घोषणा	PACKET3_ACQUIRE_MEM				0x58
/* 1.  HEADER
 * 2.  COHER_CNTL [30:0]
 * 2.1 ENGINE_SEL [31:31]
 * 2.  COHER_SIZE [31:0]
 * 3.  COHER_SIZE_HI [7:0]
 * 4.  COHER_BASE_LO [31:0]
 * 5.  COHER_BASE_HI [23:0]
 * 7.  POLL_INTERVAL [15:0]
 * 8.  GCR_CNTL [18:0]
 */
#घोषणा 	PACKET3_ACQUIRE_MEM_GCR_CNTL_GLI_INV(x) ((x) << 0)
		/*
		 * 0:NOP
		 * 1:ALL
		 * 2:RANGE
		 * 3:FIRST_LAST
		 */
#घोषणा 	PACKET3_ACQUIRE_MEM_GCR_CNTL_GL1_RANGE(x) ((x) << 2)
		/*
		 * 0:ALL
		 * 1:reserved
		 * 2:RANGE
		 * 3:FIRST_LAST
		 */
#घोषणा 	PACKET3_ACQUIRE_MEM_GCR_CNTL_GLM_WB(x) ((x) << 4)
#घोषणा 	PACKET3_ACQUIRE_MEM_GCR_CNTL_GLM_INV(x) ((x) << 5)
#घोषणा 	PACKET3_ACQUIRE_MEM_GCR_CNTL_GLK_WB(x) ((x) << 6)
#घोषणा 	PACKET3_ACQUIRE_MEM_GCR_CNTL_GLK_INV(x) ((x) << 7)
#घोषणा 	PACKET3_ACQUIRE_MEM_GCR_CNTL_GLV_INV(x) ((x) << 8)
#घोषणा 	PACKET3_ACQUIRE_MEM_GCR_CNTL_GL1_INV(x) ((x) << 9)
#घोषणा 	PACKET3_ACQUIRE_MEM_GCR_CNTL_GL2_US(x) ((x) << 10)
#घोषणा 	PACKET3_ACQUIRE_MEM_GCR_CNTL_GL2_RANGE(x) ((x) << 11)
		/*
		 * 0:ALL
		 * 1:VOL
		 * 2:RANGE
		 * 3:FIRST_LAST
		 */
#घोषणा 	PACKET3_ACQUIRE_MEM_GCR_CNTL_GL2_DISCARD(x)  ((x) << 13)
#घोषणा 	PACKET3_ACQUIRE_MEM_GCR_CNTL_GL2_INV(x) ((x) << 14)
#घोषणा 	PACKET3_ACQUIRE_MEM_GCR_CNTL_GL2_WB(x) ((x) << 15)
#घोषणा 	PACKET3_ACQUIRE_MEM_GCR_CNTL_SEQ(x) ((x) << 16)
		/*
		 * 0: PARALLEL
		 * 1: FORWARD
		 * 2: REVERSE
		 */
#घोषणा 	PACKET3_ACQUIRE_MEM_GCR_RANGE_IS_PA  (1 << 18)
#घोषणा	PACKET3_REWIND					0x59
#घोषणा	PACKET3_INTERRUPT				0x5A
#घोषणा	PACKET3_GEN_PDEPTE				0x5B
#घोषणा	PACKET3_INसूचीECT_BUFFER_PASID			0x5C
#घोषणा	PACKET3_PRIME_UTCL2				0x5D
#घोषणा	PACKET3_LOAD_UCONFIG_REG			0x5E
#घोषणा	PACKET3_LOAD_SH_REG				0x5F
#घोषणा	PACKET3_LOAD_CONFIG_REG				0x60
#घोषणा	PACKET3_LOAD_CONTEXT_REG			0x61
#घोषणा	PACKET3_LOAD_COMPUTE_STATE			0x62
#घोषणा	PACKET3_LOAD_SH_REG_INDEX			0x63
#घोषणा	PACKET3_SET_CONFIG_REG				0x68
#घोषणा		PACKET3_SET_CONFIG_REG_START			0x00002000
#घोषणा		PACKET3_SET_CONFIG_REG_END			0x00002c00
#घोषणा	PACKET3_SET_CONTEXT_REG				0x69
#घोषणा		PACKET3_SET_CONTEXT_REG_START			0x0000a000
#घोषणा		PACKET3_SET_CONTEXT_REG_END			0x0000a400
#घोषणा	PACKET3_SET_CONTEXT_REG_INDEX			0x6A
#घोषणा	PACKET3_SET_VGPR_REG_DI_MULTI			0x71
#घोषणा	PACKET3_SET_SH_REG_DI				0x72
#घोषणा	PACKET3_SET_CONTEXT_REG_INसूचीECT		0x73
#घोषणा	PACKET3_SET_SH_REG_DI_MULTI			0x74
#घोषणा	PACKET3_GFX_PIPE_LOCK				0x75
#घोषणा	PACKET3_SET_SH_REG				0x76
#घोषणा		PACKET3_SET_SH_REG_START			0x00002c00
#घोषणा		PACKET3_SET_SH_REG_END				0x00003000
#घोषणा	PACKET3_SET_SH_REG_OFFSET			0x77
#घोषणा	PACKET3_SET_QUEUE_REG				0x78
#घोषणा	PACKET3_SET_UCONFIG_REG				0x79
#घोषणा		PACKET3_SET_UCONFIG_REG_START			0x0000c000
#घोषणा		PACKET3_SET_UCONFIG_REG_END			0x0000c400
#घोषणा	PACKET3_SET_UCONFIG_REG_INDEX			0x7A
#घोषणा	PACKET3_FORWARD_HEADER				0x7C
#घोषणा	PACKET3_SCRATCH_RAM_WRITE			0x7D
#घोषणा	PACKET3_SCRATCH_RAM_READ			0x7E
#घोषणा	PACKET3_LOAD_CONST_RAM				0x80
#घोषणा	PACKET3_WRITE_CONST_RAM				0x81
#घोषणा	PACKET3_DUMP_CONST_RAM				0x83
#घोषणा	PACKET3_INCREMENT_CE_COUNTER			0x84
#घोषणा	PACKET3_INCREMENT_DE_COUNTER			0x85
#घोषणा	PACKET3_WAIT_ON_CE_COUNTER			0x86
#घोषणा	PACKET3_WAIT_ON_DE_COUNTER_DIFF			0x88
#घोषणा	PACKET3_SWITCH_BUFFER				0x8B
#घोषणा	PACKET3_DISPATCH_DRAW_PREAMBLE			0x8C
#घोषणा	PACKET3_DISPATCH_DRAW_PREAMBLE_ACE		0x8C
#घोषणा	PACKET3_DISPATCH_DRAW				0x8D
#घोषणा	PACKET3_DISPATCH_DRAW_ACE			0x8D
#घोषणा	PACKET3_GET_LOD_STATS				0x8E
#घोषणा	PACKET3_DRAW_MULTI_PREAMBLE			0x8F
#घोषणा	PACKET3_FRAME_CONTROL				0x90
#			define FRAME_TMZ	(1 << 0)
#			define FRAME_CMD(x) ((x) << 28)
			/*
			 * x=0: पंचांगz_begin
			 * x=1: पंचांगz_end
			 */
#घोषणा	PACKET3_INDEX_ATTRIBUTES_INसूचीECT		0x91
#घोषणा	PACKET3_WAIT_REG_MEM64				0x93
#घोषणा	PACKET3_COND_PREEMPT				0x94
#घोषणा	PACKET3_HDP_FLUSH				0x95
#घोषणा	PACKET3_COPY_DATA_RB				0x96
#घोषणा	PACKET3_INVALIDATE_TLBS				0x98
#              define PACKET3_INVALIDATE_TLBS_DST_SEL(x)     ((x) << 0)
#              define PACKET3_INVALIDATE_TLBS_ALL_HUB(x)     ((x) << 4)
#              define PACKET3_INVALIDATE_TLBS_PASID(x)       ((x) << 5)
#घोषणा	PACKET3_AQL_PACKET				0x99
#घोषणा	PACKET3_DMA_DATA_FILL_MULTI			0x9A
#घोषणा	PACKET3_SET_SH_REG_INDEX			0x9B
#घोषणा	PACKET3_DRAW_INसूचीECT_COUNT_MULTI		0x9C
#घोषणा	PACKET3_DRAW_INDEX_INसूचीECT_COUNT_MULTI		0x9D
#घोषणा	PACKET3_DUMP_CONST_RAM_OFFSET			0x9E
#घोषणा	PACKET3_LOAD_CONTEXT_REG_INDEX			0x9F
#घोषणा	PACKET3_SET_RESOURCES				0xA0
/* 1. header
 * 2. CONTROL
 * 3. QUEUE_MASK_LO [31:0]
 * 4. QUEUE_MASK_HI [31:0]
 * 5. GWS_MASK_LO [31:0]
 * 6. GWS_MASK_HI [31:0]
 * 7. OAC_MASK [15:0]
 * 8. GDS_HEAP_SIZE [16:11] | GDS_HEAP_BASE [5:0]
 */
#              define PACKET3_SET_RESOURCES_VMID_MASK(x)     ((x) << 0)
#              define PACKET3_SET_RESOURCES_UNMAP_LATENTY(x) ((x) << 16)
#              define PACKET3_SET_RESOURCES_QUEUE_TYPE(x)    ((x) << 29)
#घोषणा PACKET3_MAP_PROCESS				0xA1
#घोषणा PACKET3_MAP_QUEUES				0xA2
/* 1. header
 * 2. CONTROL
 * 3. CONTROL2
 * 4. MQD_ADDR_LO [31:0]
 * 5. MQD_ADDR_HI [31:0]
 * 6. WPTR_ADDR_LO [31:0]
 * 7. WPTR_ADDR_HI [31:0]
 */
/* CONTROL */
#              define PACKET3_MAP_QUEUES_QUEUE_SEL(x)       ((x) << 4)
#              define PACKET3_MAP_QUEUES_VMID(x)            ((x) << 8)
#              define PACKET3_MAP_QUEUES_QUEUE(x)           ((x) << 13)
#              define PACKET3_MAP_QUEUES_PIPE(x)            ((x) << 16)
#              define PACKET3_MAP_QUEUES_ME(x)              ((x) << 18)
#              define PACKET3_MAP_QUEUES_QUEUE_TYPE(x)      ((x) << 21)
#              define PACKET3_MAP_QUEUES_ALLOC_FORMAT(x)    ((x) << 24)
#              define PACKET3_MAP_QUEUES_ENGINE_SEL(x)      ((x) << 26)
#              define PACKET3_MAP_QUEUES_NUM_QUEUES(x)      ((x) << 29)
/* CONTROL2 */
#              define PACKET3_MAP_QUEUES_CHECK_DISABLE(x)   ((x) << 1)
#              define PACKET3_MAP_QUEUES_DOORBELL_OFFSET(x) ((x) << 2)
#घोषणा	PACKET3_UNMAP_QUEUES				0xA3
/* 1. header
 * 2. CONTROL
 * 3. CONTROL2
 * 4. CONTROL3
 * 5. CONTROL4
 * 6. CONTROL5
 */
/* CONTROL */
#              define PACKET3_UNMAP_QUEUES_ACTION(x)           ((x) << 0)
		/* 0 - PREEMPT_QUEUES
		 * 1 - RESET_QUEUES
		 * 2 - DISABLE_PROCESS_QUEUES
		 * 3 - PREEMPT_QUEUES_NO_UNMAP
		 */
#              define PACKET3_UNMAP_QUEUES_QUEUE_SEL(x)        ((x) << 4)
#              define PACKET3_UNMAP_QUEUES_ENGINE_SEL(x)       ((x) << 26)
#              define PACKET3_UNMAP_QUEUES_NUM_QUEUES(x)       ((x) << 29)
/* CONTROL2a */
#              define PACKET3_UNMAP_QUEUES_PASID(x)            ((x) << 0)
/* CONTROL2b */
#              define PACKET3_UNMAP_QUEUES_DOORBELL_OFFSET0(x) ((x) << 2)
/* CONTROL3a */
#              define PACKET3_UNMAP_QUEUES_DOORBELL_OFFSET1(x) ((x) << 2)
/* CONTROL3b */
#              define PACKET3_UNMAP_QUEUES_RB_WPTR(x)          ((x) << 0)
/* CONTROL4 */
#              define PACKET3_UNMAP_QUEUES_DOORBELL_OFFSET2(x) ((x) << 2)
/* CONTROL5 */
#              define PACKET3_UNMAP_QUEUES_DOORBELL_OFFSET3(x) ((x) << 2)
#घोषणा	PACKET3_QUERY_STATUS				0xA4
/* 1. header
 * 2. CONTROL
 * 3. CONTROL2
 * 4. ADDR_LO [31:0]
 * 5. ADDR_HI [31:0]
 * 6. DATA_LO [31:0]
 * 7. DATA_HI [31:0]
 */
/* CONTROL */
#              define PACKET3_QUERY_STATUS_CONTEXT_ID(x)       ((x) << 0)
#              define PACKET3_QUERY_STATUS_INTERRUPT_SEL(x)    ((x) << 28)
#              define PACKET3_QUERY_STATUS_COMMAND(x)          ((x) << 30)
/* CONTROL2a */
#              define PACKET3_QUERY_STATUS_PASID(x)            ((x) << 0)
/* CONTROL2b */
#              define PACKET3_QUERY_STATUS_DOORBELL_OFFSET(x)  ((x) << 2)
#              define PACKET3_QUERY_STATUS_ENG_SEL(x)          ((x) << 25)
#घोषणा	PACKET3_RUN_LIST				0xA5
#घोषणा	PACKET3_MAP_PROCESS_VM				0xA6


#पूर्ण_अगर
