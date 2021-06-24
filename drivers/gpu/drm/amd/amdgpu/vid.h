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
#अगर_अघोषित VI_H
#घोषणा VI_H

#घोषणा SDMA0_REGISTER_OFFSET                             0x0 /* not a रेजिस्टर */
#घोषणा SDMA1_REGISTER_OFFSET                             0x200 /* not a रेजिस्टर */
#घोषणा SDMA_MAX_INSTANCE 2

#घोषणा KFD_VI_SDMA_QUEUE_OFFSET                      0x80 /* not a रेजिस्टर */

/* crtc instance offsets */
#घोषणा CRTC0_REGISTER_OFFSET                 (0x1b9c - 0x1b9c)
#घोषणा CRTC1_REGISTER_OFFSET                 (0x1d9c - 0x1b9c)
#घोषणा CRTC2_REGISTER_OFFSET                 (0x1f9c - 0x1b9c)
#घोषणा CRTC3_REGISTER_OFFSET                 (0x419c - 0x1b9c)
#घोषणा CRTC4_REGISTER_OFFSET                 (0x439c - 0x1b9c)
#घोषणा CRTC5_REGISTER_OFFSET                 (0x459c - 0x1b9c)
#घोषणा CRTC6_REGISTER_OFFSET                 (0x479c - 0x1b9c)

/* dig instance offsets */
#घोषणा DIG0_REGISTER_OFFSET                 (0x4a00 - 0x4a00)
#घोषणा DIG1_REGISTER_OFFSET                 (0x4b00 - 0x4a00)
#घोषणा DIG2_REGISTER_OFFSET                 (0x4c00 - 0x4a00)
#घोषणा DIG3_REGISTER_OFFSET                 (0x4d00 - 0x4a00)
#घोषणा DIG4_REGISTER_OFFSET                 (0x4e00 - 0x4a00)
#घोषणा DIG5_REGISTER_OFFSET                 (0x4f00 - 0x4a00)
#घोषणा DIG6_REGISTER_OFFSET                 (0x5400 - 0x4a00)
#घोषणा DIG7_REGISTER_OFFSET                 (0x5600 - 0x4a00)
#घोषणा DIG8_REGISTER_OFFSET                 (0x5700 - 0x4a00)

/* audio endpt instance offsets */
#घोषणा AUD0_REGISTER_OFFSET                 (0x17a8 - 0x17a8)
#घोषणा AUD1_REGISTER_OFFSET                 (0x17ac - 0x17a8)
#घोषणा AUD2_REGISTER_OFFSET                 (0x17b0 - 0x17a8)
#घोषणा AUD3_REGISTER_OFFSET                 (0x17b4 - 0x17a8)
#घोषणा AUD4_REGISTER_OFFSET                 (0x17b8 - 0x17a8)
#घोषणा AUD5_REGISTER_OFFSET                 (0x17bc - 0x17a8)
#घोषणा AUD6_REGISTER_OFFSET                 (0x17c0 - 0x17a8)
#घोषणा AUD7_REGISTER_OFFSET                 (0x17c4 - 0x17a8)

/* hpd instance offsets */
#घोषणा HPD0_REGISTER_OFFSET                 (0x1898 - 0x1898)
#घोषणा HPD1_REGISTER_OFFSET                 (0x18a0 - 0x1898)
#घोषणा HPD2_REGISTER_OFFSET                 (0x18a8 - 0x1898)
#घोषणा HPD3_REGISTER_OFFSET                 (0x18b0 - 0x1898)
#घोषणा HPD4_REGISTER_OFFSET                 (0x18b8 - 0x1898)
#घोषणा HPD5_REGISTER_OFFSET                 (0x18c0 - 0x1898)

#घोषणा		PIPEID(x)					((x) << 0)
#घोषणा		MEID(x)						((x) << 2)
#घोषणा		VMID(x)						((x) << 4)
#घोषणा		QUEUEID(x)					((x) << 8)

#घोषणा MC_SEQ_MISC0__MT__MASK	0xf0000000
#घोषणा MC_SEQ_MISC0__MT__GDDR1  0x10000000
#घोषणा MC_SEQ_MISC0__MT__DDR2   0x20000000
#घोषणा MC_SEQ_MISC0__MT__GDDR3  0x30000000
#घोषणा MC_SEQ_MISC0__MT__GDDR4  0x40000000
#घोषणा MC_SEQ_MISC0__MT__GDDR5  0x50000000
#घोषणा MC_SEQ_MISC0__MT__HBM    0x60000000
#घोषणा MC_SEQ_MISC0__MT__DDR3   0xB0000000

/*
 * PM4
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
#घोषणा	PACKET3_INसूचीECT_BUFFER_CONST			0x33
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
#              define PACKET3_SEM_CLIENT_CODE	    ((x) << 24) /* 0 = CP, 1 = CB, 2 = DB */
#              define PACKET3_SEM_SEL_SIGNAL	    (0x6 << 29)
#              define PACKET3_SEM_SEL_WAIT	    (0x7 << 29)
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
#घोषणा		INसूचीECT_BUFFER_TCL2_VOLATILE           (1 << 22)
#घोषणा		INसूचीECT_BUFFER_VALID                   (1 << 23)
#घोषणा		INसूचीECT_BUFFER_CACHE_POLICY(x)         ((x) << 28)
		/* 0 - LRU
		 * 1 - Stream
		 * 2 - Bypass
		 */
#घोषणा     INसूचीECT_BUFFER_PRE_ENB(x)		 ((x) << 21)
#घोषणा	PACKET3_COPY_DATA				0x40
#घोषणा	PACKET3_PFP_SYNC_ME				0x42
#घोषणा	PACKET3_SURFACE_SYNC				0x43
#              define PACKET3_DEST_BASE_0_ENA      (1 << 0)
#              define PACKET3_DEST_BASE_1_ENA      (1 << 1)
#              define PACKET3_CB0_DEST_BASE_ENA    (1 << 6)
#              define PACKET3_CB1_DEST_BASE_ENA    (1 << 7)
#              define PACKET3_CB2_DEST_BASE_ENA    (1 << 8)
#              define PACKET3_CB3_DEST_BASE_ENA    (1 << 9)
#              define PACKET3_CB4_DEST_BASE_ENA    (1 << 10)
#              define PACKET3_CB5_DEST_BASE_ENA    (1 << 11)
#              define PACKET3_CB6_DEST_BASE_ENA    (1 << 12)
#              define PACKET3_CB7_DEST_BASE_ENA    (1 << 13)
#              define PACKET3_DB_DEST_BASE_ENA     (1 << 14)
#              define PACKET3_TCL1_VOL_ACTION_ENA  (1 << 15)
#              define PACKET3_TC_VOL_ACTION_ENA    (1 << 16) /* L2 */
#              define PACKET3_TC_WB_ACTION_ENA     (1 << 18) /* L2 */
#              define PACKET3_DEST_BASE_2_ENA      (1 << 19)
#              define PACKET3_DEST_BASE_3_ENA      (1 << 21)
#              define PACKET3_TCL1_ACTION_ENA      (1 << 22)
#              define PACKET3_TC_ACTION_ENA        (1 << 23) /* L2 */
#              define PACKET3_CB_ACTION_ENA        (1 << 25)
#              define PACKET3_DB_ACTION_ENA        (1 << 26)
#              define PACKET3_SH_KCACHE_ACTION_ENA (1 << 27)
#              define PACKET3_SH_KCACHE_VOL_ACTION_ENA (1 << 28)
#              define PACKET3_SH_ICACHE_ACTION_ENA (1 << 29)
#घोषणा	PACKET3_COND_WRITE				0x45
#घोषणा	PACKET3_EVENT_WRITE				0x46
#घोषणा		EVENT_TYPE(x)                           ((x) << 0)
#घोषणा		EVENT_INDEX(x)                          ((x) << 8)
		/* 0 - any non-TS event
		 * 1 - ZPASS_DONE, PIXEL_PIPE_STAT_*
		 * 2 - SAMPLE_PIPELINESTAT
		 * 3 - SAMPLE_STREAMOUTSTAT*
		 * 4 - *S_PARTIAL_FLUSH
		 * 5 - EOP events
		 * 6 - EOS events
		 */
#घोषणा	PACKET3_EVENT_WRITE_EOP				0x47
#घोषणा		EOP_TCL1_VOL_ACTION_EN                  (1 << 12)
#घोषणा		EOP_TC_VOL_ACTION_EN                    (1 << 13) /* L2 */
#घोषणा		EOP_TC_WB_ACTION_EN                     (1 << 15) /* L2 */
#घोषणा		EOP_TCL1_ACTION_EN                      (1 << 16)
#घोषणा		EOP_TC_ACTION_EN                        (1 << 17) /* L2 */
#घोषणा		EOP_TCL2_VOLATILE                       (1 << 24)
#घोषणा		EOP_CACHE_POLICY(x)                     ((x) << 25)
		/* 0 - LRU
		 * 1 - Stream
		 * 2 - Bypass
		 */
#घोषणा		DATA_SEL(x)                             ((x) << 29)
		/* 0 - discard
		 * 1 - send low 32bit data
		 * 2 - send 64bit data
		 * 3 - send 64bit GPU counter value
		 * 4 - send 64bit sys counter value
		 */
#घोषणा		INT_SEL(x)                              ((x) << 24)
		/* 0 - none
		 * 1 - पूर्णांकerrupt only (DATA_SEL = 0)
		 * 2 - पूर्णांकerrupt when data ग_लिखो is confirmed
		 */
#घोषणा		DST_SEL(x)                              ((x) << 16)
		/* 0 - MC
		 * 1 - TC/L2
		 */
#घोषणा	PACKET3_EVENT_WRITE_EOS				0x48
#घोषणा	PACKET3_RELEASE_MEM				0x49
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
 * 7. COMMAND [30:21] | BYTE_COUNT [20:0]
 */
/* CONTROL */
#              define PACKET3_DMA_DATA_ENGINE(x)     ((x) << 0)
		/* 0 - ME
		 * 1 - PFP
		 */
#              define PACKET3_DMA_DATA_SRC_CACHE_POLICY(x) ((x) << 13)
		/* 0 - LRU
		 * 1 - Stream
		 * 2 - Bypass
		 */
#              define PACKET3_DMA_DATA_SRC_VOLATILE (1 << 15)
#              define PACKET3_DMA_DATA_DST_SEL(x)  ((x) << 20)
		/* 0 - DST_ADDR using DAS
		 * 1 - GDS
		 * 3 - DST_ADDR using L2
		 */
#              define PACKET3_DMA_DATA_DST_CACHE_POLICY(x) ((x) << 25)
		/* 0 - LRU
		 * 1 - Stream
		 * 2 - Bypass
		 */
#              define PACKET3_DMA_DATA_DST_VOLATILE (1 << 27)
#              define PACKET3_DMA_DATA_SRC_SEL(x)  ((x) << 29)
		/* 0 - SRC_ADDR using SAS
		 * 1 - GDS
		 * 2 - DATA
		 * 3 - SRC_ADDR using L2
		 */
#              define PACKET3_DMA_DATA_CP_SYNC     (1 << 31)
/* COMMAND */
#              define PACKET3_DMA_DATA_DIS_WC      (1 << 21)
#              define PACKET3_DMA_DATA_CMD_SRC_SWAP(x) ((x) << 22)
		/* 0 - none
		 * 1 - 8 in 16
		 * 2 - 8 in 32
		 * 3 - 8 in 64
		 */
#              define PACKET3_DMA_DATA_CMD_DST_SWAP(x) ((x) << 24)
		/* 0 - none
		 * 1 - 8 in 16
		 * 2 - 8 in 32
		 * 3 - 8 in 64
		 */
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
#घोषणा	PACKET3_ACQUIRE_MEM				0x58
#घोषणा	PACKET3_REWIND					0x59
#घोषणा	PACKET3_LOAD_UCONFIG_REG			0x5E
#घोषणा	PACKET3_LOAD_SH_REG				0x5F
#घोषणा	PACKET3_LOAD_CONFIG_REG				0x60
#घोषणा	PACKET3_LOAD_CONTEXT_REG			0x61
#घोषणा	PACKET3_SET_CONFIG_REG				0x68
#घोषणा		PACKET3_SET_CONFIG_REG_START			0x00002000
#घोषणा		PACKET3_SET_CONFIG_REG_END			0x00002c00
#घोषणा	PACKET3_SET_CONTEXT_REG				0x69
#घोषणा		PACKET3_SET_CONTEXT_REG_START			0x0000a000
#घोषणा		PACKET3_SET_CONTEXT_REG_END			0x0000a400
#घोषणा	PACKET3_SET_CONTEXT_REG_INसूचीECT		0x73
#घोषणा	PACKET3_SET_SH_REG				0x76
#घोषणा		PACKET3_SET_SH_REG_START			0x00002c00
#घोषणा		PACKET3_SET_SH_REG_END				0x00003000
#घोषणा	PACKET3_SET_SH_REG_OFFSET			0x77
#घोषणा	PACKET3_SET_QUEUE_REG				0x78
#घोषणा	PACKET3_SET_UCONFIG_REG				0x79
#घोषणा		PACKET3_SET_UCONFIG_REG_START			0x0000c000
#घोषणा		PACKET3_SET_UCONFIG_REG_END			0x0000c400
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
#घोषणा PACKET3_FRAME_CONTROL				0x90
#			define FRAME_CMD(x) ((x) << 28)
			/*
			 * x=0: पंचांगz_begin
			 * x=1: पंचांगz_end
			 */
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
#घोषणा	PACKET3_MAP_QUEUES				0xA2
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
#              define PACKET3_MAP_QUEUES_QUEUE_TYPE(x)      ((x) << 21)
#              define PACKET3_MAP_QUEUES_ALLOC_FORMAT(x)    ((x) << 24)
#              define PACKET3_MAP_QUEUES_ENGINE_SEL(x)      ((x) << 26)
#              define PACKET3_MAP_QUEUES_NUM_QUEUES(x)      ((x) << 29)
/* CONTROL2 */
#              define PACKET3_MAP_QUEUES_CHECK_DISABLE(x)   ((x) << 1)
#              define PACKET3_MAP_QUEUES_DOORBELL_OFFSET(x) ((x) << 2)
#              define PACKET3_MAP_QUEUES_QUEUE(x)           ((x) << 26)
#              define PACKET3_MAP_QUEUES_PIPE(x)            ((x) << 29)
#              define PACKET3_MAP_QUEUES_ME(x)              ((x) << 31)
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


#घोषणा VCE_CMD_NO_OP		0x00000000
#घोषणा VCE_CMD_END		0x00000001
#घोषणा VCE_CMD_IB		0x00000002
#घोषणा VCE_CMD_FENCE		0x00000003
#घोषणा VCE_CMD_TRAP		0x00000004
#घोषणा VCE_CMD_IB_AUTO	0x00000005
#घोषणा VCE_CMD_SEMAPHORE	0x00000006

#घोषणा VCE_CMD_IB_VM           0x00000102
#घोषणा VCE_CMD_WAIT_GE         0x00000106
#घोषणा VCE_CMD_UPDATE_PTB      0x00000107
#घोषणा VCE_CMD_FLUSH_TLB       0x00000108

/* HEVC ENC */
#घोषणा HEVC_ENC_CMD_NO_OP         0x00000000
#घोषणा HEVC_ENC_CMD_END           0x00000001
#घोषणा HEVC_ENC_CMD_FENCE         0x00000003
#घोषणा HEVC_ENC_CMD_TRAP          0x00000004
#घोषणा HEVC_ENC_CMD_IB_VM         0x00000102
#घोषणा HEVC_ENC_CMD_WAIT_GE       0x00000106
#घोषणा HEVC_ENC_CMD_UPDATE_PTB    0x00000107
#घोषणा HEVC_ENC_CMD_FLUSH_TLB     0x00000108

/* mmPA_SC_RASTER_CONFIG mask */
#घोषणा RB_MAP_PKR0(x)				((x) << 0)
#घोषणा RB_MAP_PKR0_MASK			(0x3 << 0)
#घोषणा RB_MAP_PKR1(x)				((x) << 2)
#घोषणा RB_MAP_PKR1_MASK			(0x3 << 2)
#घोषणा RB_XSEL2(x)				((x) << 4)
#घोषणा RB_XSEL2_MASK				(0x3 << 4)
#घोषणा RB_XSEL					(1 << 6)
#घोषणा RB_YSEL					(1 << 7)
#घोषणा PKR_MAP(x)				((x) << 8)
#घोषणा PKR_MAP_MASK				(0x3 << 8)
#घोषणा PKR_XSEL(x)				((x) << 10)
#घोषणा PKR_XSEL_MASK				(0x3 << 10)
#घोषणा PKR_YSEL(x)				((x) << 12)
#घोषणा PKR_YSEL_MASK				(0x3 << 12)
#घोषणा SC_MAP(x)				((x) << 16)
#घोषणा SC_MAP_MASK				(0x3 << 16)
#घोषणा SC_XSEL(x)				((x) << 18)
#घोषणा SC_XSEL_MASK				(0x3 << 18)
#घोषणा SC_YSEL(x)				((x) << 20)
#घोषणा SC_YSEL_MASK				(0x3 << 20)
#घोषणा SE_MAP(x)				((x) << 24)
#घोषणा SE_MAP_MASK				(0x3 << 24)
#घोषणा SE_XSEL(x)				((x) << 26)
#घोषणा SE_XSEL_MASK				(0x3 << 26)
#घोषणा SE_YSEL(x)				((x) << 28)
#घोषणा SE_YSEL_MASK				(0x3 << 28)

/* mmPA_SC_RASTER_CONFIG_1 mask */
#घोषणा SE_PAIR_MAP(x)				((x) << 0)
#घोषणा SE_PAIR_MAP_MASK			(0x3 << 0)
#घोषणा SE_PAIR_XSEL(x)				((x) << 2)
#घोषणा SE_PAIR_XSEL_MASK			(0x3 << 2)
#घोषणा SE_PAIR_YSEL(x)				((x) << 4)
#घोषणा SE_PAIR_YSEL_MASK			(0x3 << 4)

#पूर्ण_अगर
