<शैली गुरु>
#अगर_अघोषित _CHIP_H
#घोषणा _CHIP_H
/*
 * Copyright(c) 2015 - 2020 Intel Corporation.
 *
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * BSD LICENSE
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *  - Neither the name of Intel Corporation nor the names of its
 *    contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/*
 * This file contains all of the defines that is specअगरic to the HFI chip
 */

/* sizes */
#घोषणा BITS_PER_REGISTER (BITS_PER_BYTE * माप(u64))
#घोषणा NUM_INTERRUPT_SOURCES 768
#घोषणा RXE_NUM_CONTEXTS 160
#घोषणा RXE_PER_CONTEXT_SIZE 0x1000	/* 4k */
#घोषणा RXE_NUM_TID_FLOWS 32
#घोषणा RXE_NUM_DATA_VL 8
#घोषणा TXE_NUM_CONTEXTS 160
#घोषणा TXE_NUM_SDMA_ENGINES 16
#घोषणा NUM_CONTEXTS_PER_SET 8
#घोषणा VL_ARB_HIGH_PRIO_TABLE_SIZE 16
#घोषणा VL_ARB_LOW_PRIO_TABLE_SIZE 16
#घोषणा VL_ARB_TABLE_SIZE 16
#घोषणा TXE_NUM_32_BIT_COUNTER 7
#घोषणा TXE_NUM_64_BIT_COUNTER 30
#घोषणा TXE_NUM_DATA_VL 8
#घोषणा TXE_PIO_SIZE (32 * 0x100000)	/* 32 MB */
#घोषणा PIO_BLOCK_SIZE 64			/* bytes */
#घोषणा SDMA_BLOCK_SIZE 64			/* bytes */
#घोषणा RCV_BUF_BLOCK_SIZE 64               /* bytes */
#घोषणा PIO_CMASK 0x7ff	/* counter mask क्रम मुक्त and fill counters */
#घोषणा MAX_EAGER_ENTRIES    2048	/* max receive eager entries */
#घोषणा MAX_TID_PAIR_ENTRIES 1024	/* max receive expected pairs */
/*
 * Virtual? Allocation Unit, defined as AU = 8*2^vAU, 64 bytes, AU is fixed
 * at 64 bytes क्रम all generation one devices
 */
#घोषणा CM_VAU 3
/* HFI link credit count, AKA receive buffer depth (RBUF_DEPTH) */
#घोषणा CM_GLOBAL_CREDITS 0x880
/* Number of PKey entries in the HW */
#घोषणा MAX_PKEY_VALUES 16

#समावेश "chip_registers.h"

#घोषणा RXE_PER_CONTEXT_USER   (RXE + RXE_PER_CONTEXT_OFFSET)
#घोषणा TXE_PIO_SEND (TXE + TXE_PIO_SEND_OFFSET)

/* PBC flags */
#घोषणा PBC_INTR		BIT_ULL(31)
#घोषणा PBC_DC_INFO_SHIFT	(30)
#घोषणा PBC_DC_INFO		BIT_ULL(PBC_DC_INFO_SHIFT)
#घोषणा PBC_TEST_EBP		BIT_ULL(29)
#घोषणा PBC_PACKET_BYPASS	BIT_ULL(28)
#घोषणा PBC_CREDIT_RETURN	BIT_ULL(25)
#घोषणा PBC_INSERT_BYPASS_ICRC	BIT_ULL(24)
#घोषणा PBC_TEST_BAD_ICRC	BIT_ULL(23)
#घोषणा PBC_FECN		BIT_ULL(22)

/* PbcInsertHcrc field settings */
#घोषणा PBC_IHCRC_LKDETH 0x0	/* insert @ local KDETH offset */
#घोषणा PBC_IHCRC_GKDETH 0x1	/* insert @ global KDETH offset */
#घोषणा PBC_IHCRC_NONE   0x2	/* no HCRC inserted */

/* PBC fields */
#घोषणा PBC_STATIC_RATE_CONTROL_COUNT_SHIFT 32
#घोषणा PBC_STATIC_RATE_CONTROL_COUNT_MASK 0xffffull
#घोषणा PBC_STATIC_RATE_CONTROL_COUNT_SMASK \
	(PBC_STATIC_RATE_CONTROL_COUNT_MASK << \
	PBC_STATIC_RATE_CONTROL_COUNT_SHIFT)

#घोषणा PBC_INSERT_HCRC_SHIFT 26
#घोषणा PBC_INSERT_HCRC_MASK 0x3ull
#घोषणा PBC_INSERT_HCRC_SMASK \
	(PBC_INSERT_HCRC_MASK << PBC_INSERT_HCRC_SHIFT)

#घोषणा PBC_VL_SHIFT 12
#घोषणा PBC_VL_MASK 0xfull
#घोषणा PBC_VL_SMASK (PBC_VL_MASK << PBC_VL_SHIFT)

#घोषणा PBC_LENGTH_DWS_SHIFT 0
#घोषणा PBC_LENGTH_DWS_MASK 0xfffull
#घोषणा PBC_LENGTH_DWS_SMASK \
	(PBC_LENGTH_DWS_MASK << PBC_LENGTH_DWS_SHIFT)

/* Credit Return Fields */
#घोषणा CR_COUNTER_SHIFT 0
#घोषणा CR_COUNTER_MASK 0x7ffull
#घोषणा CR_COUNTER_SMASK (CR_COUNTER_MASK << CR_COUNTER_SHIFT)

#घोषणा CR_STATUS_SHIFT 11
#घोषणा CR_STATUS_MASK 0x1ull
#घोषणा CR_STATUS_SMASK (CR_STATUS_MASK << CR_STATUS_SHIFT)

#घोषणा CR_CREDIT_RETURN_DUE_TO_PBC_SHIFT 12
#घोषणा CR_CREDIT_RETURN_DUE_TO_PBC_MASK 0x1ull
#घोषणा CR_CREDIT_RETURN_DUE_TO_PBC_SMASK \
	(CR_CREDIT_RETURN_DUE_TO_PBC_MASK << \
	CR_CREDIT_RETURN_DUE_TO_PBC_SHIFT)

#घोषणा CR_CREDIT_RETURN_DUE_TO_THRESHOLD_SHIFT 13
#घोषणा CR_CREDIT_RETURN_DUE_TO_THRESHOLD_MASK 0x1ull
#घोषणा CR_CREDIT_RETURN_DUE_TO_THRESHOLD_SMASK \
	(CR_CREDIT_RETURN_DUE_TO_THRESHOLD_MASK << \
	CR_CREDIT_RETURN_DUE_TO_THRESHOLD_SHIFT)

#घोषणा CR_CREDIT_RETURN_DUE_TO_ERR_SHIFT 14
#घोषणा CR_CREDIT_RETURN_DUE_TO_ERR_MASK 0x1ull
#घोषणा CR_CREDIT_RETURN_DUE_TO_ERR_SMASK \
	(CR_CREDIT_RETURN_DUE_TO_ERR_MASK << \
	CR_CREDIT_RETURN_DUE_TO_ERR_SHIFT)

#घोषणा CR_CREDIT_RETURN_DUE_TO_FORCE_SHIFT 15
#घोषणा CR_CREDIT_RETURN_DUE_TO_FORCE_MASK 0x1ull
#घोषणा CR_CREDIT_RETURN_DUE_TO_FORCE_SMASK \
	(CR_CREDIT_RETURN_DUE_TO_FORCE_MASK << \
	CR_CREDIT_RETURN_DUE_TO_FORCE_SHIFT)

/* Specअगरic IRQ sources */
#घोषणा CCE_ERR_INT		  0
#घोषणा RXE_ERR_INT		  1
#घोषणा MISC_ERR_INT		  2
#घोषणा PIO_ERR_INT		  4
#घोषणा SDMA_ERR_INT		  5
#घोषणा EGRESS_ERR_INT		  6
#घोषणा TXE_ERR_INT		  7
#घोषणा PBC_INT			240
#घोषणा GPIO_ASSERT_INT		241
#घोषणा QSFP1_INT		242
#घोषणा QSFP2_INT		243
#घोषणा TCRIT_INT		244

/* पूर्णांकerrupt source ranges */
#घोषणा IS_FIRST_SOURCE		CCE_ERR_INT
#घोषणा IS_GENERAL_ERR_START		  0
#घोषणा IS_SDMAENG_ERR_START		 16
#घोषणा IS_SENDCTXT_ERR_START		 32
#घोषणा IS_SDMA_START			192
#घोषणा IS_SDMA_PROGRESS_START		208
#घोषणा IS_SDMA_IDLE_START		224
#घोषणा IS_VARIOUS_START		240
#घोषणा IS_DC_START			248
#घोषणा IS_RCVAVAIL_START		256
#घोषणा IS_RCVURGENT_START		416
#घोषणा IS_SENDCREDIT_START		576
#घोषणा IS_RESERVED_START		736
#घोषणा IS_LAST_SOURCE			767

/* derived पूर्णांकerrupt source values */
#घोषणा IS_GENERAL_ERR_END		7
#घोषणा IS_SDMAENG_ERR_END		31
#घोषणा IS_SENDCTXT_ERR_END		191
#घोषणा IS_SDMA_END                     207
#घोषणा IS_SDMA_PROGRESS_END            223
#घोषणा IS_SDMA_IDLE_END		239
#घोषणा IS_VARIOUS_END			244
#घोषणा IS_DC_END			255
#घोषणा IS_RCVAVAIL_END			415
#घोषणा IS_RCVURGENT_END		575
#घोषणा IS_SENDCREDIT_END		735
#घोषणा IS_RESERVED_END			IS_LAST_SOURCE

/* DCC_CFG_PORT_CONFIG logical link states */
#घोषणा LSTATE_DOWN    0x1
#घोषणा LSTATE_INIT    0x2
#घोषणा LSTATE_ARMED   0x3
#घोषणा LSTATE_ACTIVE  0x4

/* DCC_CFG_RESET reset states */
#घोषणा LCB_RX_FPE_TX_FPE_INTO_RESET   (DCC_CFG_RESET_RESET_LCB    | \
					DCC_CFG_RESET_RESET_TX_FPE | \
					DCC_CFG_RESET_RESET_RX_FPE | \
					DCC_CFG_RESET_ENABLE_CCLK_BCC)
					/* 0x17 */

#घोषणा LCB_RX_FPE_TX_FPE_OUT_OF_RESET  DCC_CFG_RESET_ENABLE_CCLK_BCC /* 0x10 */

/* DC8051_STS_CUR_STATE port values (physical link states) */
#घोषणा PLS_DISABLED			   0x30
#घोषणा PLS_OFFLINE				   0x90
#घोषणा PLS_OFFLINE_QUIET			   0x90
#घोषणा PLS_OFFLINE_PLANNED_DOWN_INFORM	   0x91
#घोषणा PLS_OFFLINE_READY_TO_QUIET_LT	   0x92
#घोषणा PLS_OFFLINE_REPORT_FAILURE		   0x93
#घोषणा PLS_OFFLINE_READY_TO_QUIET_BCC	   0x94
#घोषणा PLS_OFFLINE_QUIET_DURATION	   0x95
#घोषणा PLS_POLLING				   0x20
#घोषणा PLS_POLLING_QUIET			   0x20
#घोषणा PLS_POLLING_ACTIVE			   0x21
#घोषणा PLS_CONFIGPHY			   0x40
#घोषणा PLS_CONFIGPHY_DEBOUCE		   0x40
#घोषणा PLS_CONFIGPHY_ESTCOMM		   0x41
#घोषणा PLS_CONFIGPHY_ESTCOMM_TXRX_HUNT	   0x42
#घोषणा PLS_CONFIGPHY_ESTCOMM_LOCAL_COMPLETE   0x43
#घोषणा PLS_CONFIGPHY_OPTEQ			   0x44
#घोषणा PLS_CONFIGPHY_OPTEQ_OPTIMIZING	   0x44
#घोषणा PLS_CONFIGPHY_OPTEQ_LOCAL_COMPLETE	   0x45
#घोषणा PLS_CONFIGPHY_VERIFYCAP		   0x46
#घोषणा PLS_CONFIGPHY_VERIFYCAP_EXCHANGE	   0x46
#घोषणा PLS_CONFIGPHY_VERIFYCAP_LOCAL_COMPLETE 0x47
#घोषणा PLS_CONFIGLT			   0x48
#घोषणा PLS_CONFIGLT_CONFIGURE		   0x48
#घोषणा PLS_CONFIGLT_LINK_TRANSFER_ACTIVE	   0x49
#घोषणा PLS_LINKUP				   0x50
#घोषणा PLS_PHYTEST				   0xB0
#घोषणा PLS_INTERNAL_SERDES_LOOPBACK	   0xe1
#घोषणा PLS_QUICK_LINKUP			   0xe2

/* DC_DC8051_CFG_HOST_CMD_0.REQ_TYPE - 8051 host commands */
#घोषणा HCMD_LOAD_CONFIG_DATA  0x01
#घोषणा HCMD_READ_CONFIG_DATA  0x02
#घोषणा HCMD_CHANGE_PHY_STATE  0x03
#घोषणा HCMD_SEND_LCB_IDLE_MSG 0x04
#घोषणा HCMD_MISC		   0x05
#घोषणा HCMD_READ_LCB_IDLE_MSG 0x06
#घोषणा HCMD_READ_LCB_CSR      0x07
#घोषणा HCMD_WRITE_LCB_CSR     0x08
#घोषणा HCMD_INTERFACE_TEST	   0xff

/* DC_DC8051_CFG_HOST_CMD_1.RETURN_CODE - 8051 host command वापस */
#घोषणा HCMD_SUCCESS 2

/* DC_DC8051_DBG_ERR_INFO_SET_BY_8051.ERROR - error flags */
#घोषणा SPICO_ROM_FAILED		BIT(0)
#घोषणा UNKNOWN_FRAME			BIT(1)
#घोषणा TARGET_BER_NOT_MET		BIT(2)
#घोषणा FAILED_SERDES_INTERNAL_LOOPBACK	BIT(3)
#घोषणा FAILED_SERDES_INIT		BIT(4)
#घोषणा FAILED_LNI_POLLING		BIT(5)
#घोषणा FAILED_LNI_DEBOUNCE		BIT(6)
#घोषणा FAILED_LNI_ESTBCOMM		BIT(7)
#घोषणा FAILED_LNI_OPTEQ		BIT(8)
#घोषणा FAILED_LNI_VERIFY_CAP1		BIT(9)
#घोषणा FAILED_LNI_VERIFY_CAP2		BIT(10)
#घोषणा FAILED_LNI_CONFIGLT		BIT(11)
#घोषणा HOST_HANDSHAKE_TIMEOUT		BIT(12)
#घोषणा EXTERNAL_DEVICE_REQ_TIMEOUT	BIT(13)

#घोषणा FAILED_LNI (FAILED_LNI_POLLING | FAILED_LNI_DEBOUNCE \
			| FAILED_LNI_ESTBCOMM | FAILED_LNI_OPTEQ \
			| FAILED_LNI_VERIFY_CAP1 \
			| FAILED_LNI_VERIFY_CAP2 \
			| FAILED_LNI_CONFIGLT | HOST_HANDSHAKE_TIMEOUT \
			| EXTERNAL_DEVICE_REQ_TIMEOUT)

/* DC_DC8051_DBG_ERR_INFO_SET_BY_8051.HOST_MSG - host message flags */
#घोषणा HOST_REQ_DONE		BIT(0)
#घोषणा BC_PWR_MGM_MSG		BIT(1)
#घोषणा BC_SMA_MSG		BIT(2)
#घोषणा BC_BCC_UNKNOWN_MSG	BIT(3)
#घोषणा BC_IDLE_UNKNOWN_MSG	BIT(4)
#घोषणा EXT_DEVICE_CFG_REQ	BIT(5)
#घोषणा VERIFY_CAP_FRAME	BIT(6)
#घोषणा LINKUP_ACHIEVED		BIT(7)
#घोषणा LINK_GOING_DOWN		BIT(8)
#घोषणा LINK_WIDTH_DOWNGRADED	BIT(9)

/* DC_DC8051_CFG_EXT_DEV_1.REQ_TYPE - 8051 host requests */
#घोषणा HREQ_LOAD_CONFIG	0x01
#घोषणा HREQ_SAVE_CONFIG	0x02
#घोषणा HREQ_READ_CONFIG	0x03
#घोषणा HREQ_SET_TX_EQ_ABS	0x04
#घोषणा HREQ_SET_TX_EQ_REL	0x05
#घोषणा HREQ_ENABLE		0x06
#घोषणा HREQ_LCB_RESET		0x07
#घोषणा HREQ_CONFIG_DONE	0xfe
#घोषणा HREQ_INTERFACE_TEST	0xff

/* DC_DC8051_CFG_EXT_DEV_0.RETURN_CODE - 8051 host request वापस codes */
#घोषणा HREQ_INVALID		0x01
#घोषणा HREQ_SUCCESS		0x02
#घोषणा HREQ_NOT_SUPPORTED		0x03
#घोषणा HREQ_FEATURE_NOT_SUPPORTED	0x04 /* request specअगरic feature */
#घोषणा HREQ_REQUEST_REJECTED	0xfe
#घोषणा HREQ_EXECUTION_ONGOING	0xff

/* MISC host command functions */
#घोषणा HCMD_MISC_REQUEST_LCB_ACCESS 0x1
#घोषणा HCMD_MISC_GRANT_LCB_ACCESS   0x2

/* idle flit message types */
#घोषणा IDLE_PHYSICAL_LINK_MGMT 0x1
#घोषणा IDLE_CRU		    0x2
#घोषणा IDLE_SMA		    0x3
#घोषणा IDLE_POWER_MGMT	    0x4

/* idle flit message send fields (both send and पढ़ो) */
#घोषणा IDLE_PAYLOAD_MASK 0xffffffffffull /* 40 bits */
#घोषणा IDLE_PAYLOAD_SHIFT 8
#घोषणा IDLE_MSG_TYPE_MASK 0xf
#घोषणा IDLE_MSG_TYPE_SHIFT 0

/* idle flit message पढ़ो fields */
#घोषणा READ_IDLE_MSG_TYPE_MASK 0xf
#घोषणा READ_IDLE_MSG_TYPE_SHIFT 0

/* SMA idle flit payload commands */
#घोषणा SMA_IDLE_ARM	1
#घोषणा SMA_IDLE_ACTIVE 2

/* DC_DC8051_CFG_MODE.GENERAL bits */
#घोषणा DISABLE_SELF_GUID_CHECK 0x2

/* Bad L2 frame error code */
#घोषणा BAD_L2_ERR      0x6

/*
 * Eager buffer minimum and maximum sizes supported by the hardware.
 * All घातer-of-two sizes in between are supported as well.
 * MAX_EAGER_BUFFER_TOTAL is the maximum size of memory
 * allocatable क्रम Eager buffer to a single context. All others
 * are limits क्रम the RcvArray entries.
 */
#घोषणा MIN_EAGER_BUFFER       (4 * 1024)
#घोषणा MAX_EAGER_BUFFER       (256 * 1024)
#घोषणा MAX_EAGER_BUFFER_TOTAL (64 * (1 << 20)) /* max per ctxt 64MB */
#घोषणा MAX_EXPECTED_BUFFER    (2048 * 1024)
#घोषणा HFI1_MIN_HDRQ_EGRBUF_CNT 32
#घोषणा HFI1_MAX_HDRQ_EGRBUF_CNT 16352

/*
 * Receive expected base and count and eager base and count increment -
 * the CSR fields hold multiples of this value.
 */
#घोषणा RCV_SHIFT 3
#घोषणा RCV_INCREMENT BIT(RCV_SHIFT)

/*
 * Receive header queue entry increment - the CSR holds multiples of
 * this value.
 */
#घोषणा HDRQ_SIZE_SHIFT 5
#घोषणा HDRQ_INCREMENT BIT(HDRQ_SIZE_SHIFT)

/*
 * Freeze handling flags
 */
#घोषणा FREEZE_ABORT     0x01	/* करो not करो recovery */
#घोषणा FREEZE_SELF	     0x02	/* initiate the मुक्तze */
#घोषणा FREEZE_LINK_DOWN 0x04	/* link is करोwn */

/*
 * Chip implementation codes.
 */
#घोषणा ICODE_RTL_SILICON		0x00
#घोषणा ICODE_RTL_VCS_SIMULATION	0x01
#घोषणा ICODE_FPGA_EMULATION	0x02
#घोषणा ICODE_FUNCTIONAL_SIMULATOR	0x03

/*
 * 8051 data memory size.
 */
#घोषणा DC8051_DATA_MEM_SIZE 0x1000

/*
 * 8051 firmware रेजिस्टरs
 */
#घोषणा NUM_GENERAL_FIELDS 0x17
#घोषणा NUM_LANE_FIELDS    0x8

/* 8051 general रेजिस्टर Field IDs */
#घोषणा LINK_OPTIMIZATION_SETTINGS   0x00
#घोषणा LINK_TUNING_PARAMETERS	     0x02
#घोषणा DC_HOST_COMM_SETTINGS	     0x03
#घोषणा TX_SETTINGS		     0x06
#घोषणा VERIFY_CAP_LOCAL_PHY	     0x07
#घोषणा VERIFY_CAP_LOCAL_FABRIC	     0x08
#घोषणा VERIFY_CAP_LOCAL_LINK_MODE   0x09
#घोषणा LOCAL_DEVICE_ID		     0x0a
#घोषणा RESERVED_REGISTERS	     0x0b
#घोषणा LOCAL_LNI_INFO		     0x0c
#घोषणा REMOTE_LNI_INFO              0x0d
#घोषणा MISC_STATUS		     0x0e
#घोषणा VERIFY_CAP_REMOTE_PHY	     0x0f
#घोषणा VERIFY_CAP_REMOTE_FABRIC     0x10
#घोषणा VERIFY_CAP_REMOTE_LINK_WIDTH 0x11
#घोषणा LAST_LOCAL_STATE_COMPLETE    0x12
#घोषणा LAST_REMOTE_STATE_COMPLETE   0x13
#घोषणा LINK_QUALITY_INFO            0x14
#घोषणा REMOTE_DEVICE_ID	     0x15
#घोषणा LINK_DOWN_REASON	     0x16 /* first byte of offset 0x16 */
#घोषणा VERSION_PATCH		     0x16 /* last byte of offset 0x16 */

/* 8051 lane specअगरic रेजिस्टर field IDs */
#घोषणा TX_EQ_SETTINGS		0x00
#घोषणा CHANNEL_LOSS_SETTINGS	0x05

/* Lane ID क्रम general configuration रेजिस्टरs */
#घोषणा GENERAL_CONFIG 4

/* LINK_TUNING_PARAMETERS fields */
#घोषणा TUNING_METHOD_SHIFT 24

/* LINK_OPTIMIZATION_SETTINGS fields */
#घोषणा ENABLE_EXT_DEV_CONFIG_SHIFT 24

/* LOAD_DATA 8051 command shअगरts and fields */
#घोषणा LOAD_DATA_FIELD_ID_SHIFT 40
#घोषणा LOAD_DATA_FIELD_ID_MASK 0xfull
#घोषणा LOAD_DATA_LANE_ID_SHIFT 32
#घोषणा LOAD_DATA_LANE_ID_MASK 0xfull
#घोषणा LOAD_DATA_DATA_SHIFT   0x0
#घोषणा LOAD_DATA_DATA_MASK   0xffffffffull

/* READ_DATA 8051 command shअगरts and fields */
#घोषणा READ_DATA_FIELD_ID_SHIFT 40
#घोषणा READ_DATA_FIELD_ID_MASK 0xffull
#घोषणा READ_DATA_LANE_ID_SHIFT 32
#घोषणा READ_DATA_LANE_ID_MASK 0xffull
#घोषणा READ_DATA_DATA_SHIFT   0x0
#घोषणा READ_DATA_DATA_MASK   0xffffffffull

/* TX settings fields */
#घोषणा ENABLE_LANE_TX_SHIFT		0
#घोषणा ENABLE_LANE_TX_MASK		0xff
#घोषणा TX_POLARITY_INVERSION_SHIFT	8
#घोषणा TX_POLARITY_INVERSION_MASK	0xff
#घोषणा RX_POLARITY_INVERSION_SHIFT	16
#घोषणा RX_POLARITY_INVERSION_MASK	0xff
#घोषणा MAX_RATE_SHIFT			24
#घोषणा MAX_RATE_MASK			0xff

/* verअगरy capability PHY fields */
#घोषणा CONTINIOUS_REMOTE_UPDATE_SUPPORT_SHIFT	0x4
#घोषणा CONTINIOUS_REMOTE_UPDATE_SUPPORT_MASK	0x1
#घोषणा POWER_MANAGEMENT_SHIFT			0x0
#घोषणा POWER_MANAGEMENT_MASK			0xf

/* 8051 lane रेजिस्टर Field IDs */
#घोषणा SPICO_FW_VERSION 0x7	/* SPICO firmware version */

/* SPICO firmware version fields */
#घोषणा SPICO_ROM_VERSION_SHIFT 0
#घोषणा SPICO_ROM_VERSION_MASK 0xffff
#घोषणा SPICO_ROM_PROD_ID_SHIFT 16
#घोषणा SPICO_ROM_PROD_ID_MASK 0xffff

/* verअगरy capability fabric fields */
#घोषणा VAU_SHIFT	0
#घोषणा VAU_MASK	0x0007
#घोषणा Z_SHIFT		3
#घोषणा Z_MASK		0x0001
#घोषणा VCU_SHIFT	4
#घोषणा VCU_MASK	0x0007
#घोषणा VL15BUF_SHIFT	8
#घोषणा VL15BUF_MASK	0x0fff
#घोषणा CRC_SIZES_SHIFT 20
#घोषणा CRC_SIZES_MASK	0x7

/* verअगरy capability local link width fields */
#घोषणा LINK_WIDTH_SHIFT 0		/* also क्रम remote link width */
#घोषणा LINK_WIDTH_MASK 0xffff		/* also क्रम remote link width */
#घोषणा LOCAL_FLAG_BITS_SHIFT 16
#घोषणा LOCAL_FLAG_BITS_MASK 0xff
#घोषणा MISC_CONFIG_BITS_SHIFT 24
#घोषणा MISC_CONFIG_BITS_MASK 0xff

/* verअगरy capability remote link width fields */
#घोषणा REMOTE_TX_RATE_SHIFT 16
#घोषणा REMOTE_TX_RATE_MASK 0xff

/* LOCAL_DEVICE_ID fields */
#घोषणा LOCAL_DEVICE_REV_SHIFT 0
#घोषणा LOCAL_DEVICE_REV_MASK 0xff
#घोषणा LOCAL_DEVICE_ID_SHIFT 8
#घोषणा LOCAL_DEVICE_ID_MASK 0xffff

/* REMOTE_DEVICE_ID fields */
#घोषणा REMOTE_DEVICE_REV_SHIFT 0
#घोषणा REMOTE_DEVICE_REV_MASK 0xff
#घोषणा REMOTE_DEVICE_ID_SHIFT 8
#घोषणा REMOTE_DEVICE_ID_MASK 0xffff

/* local LNI link width fields */
#घोषणा ENABLE_LANE_RX_SHIFT 16
#घोषणा ENABLE_LANE_RX_MASK  0xff

/* mask, shअगरt क्रम पढ़ोing 'mgmt_enabled' value from REMOTE_LNI_INFO field */
#घोषणा MGMT_ALLOWED_SHIFT 23
#घोषणा MGMT_ALLOWED_MASK 0x1

/* mask, shअगरt क्रम 'link_quality' within LINK_QUALITY_INFO field */
#घोषणा LINK_QUALITY_SHIFT 24
#घोषणा LINK_QUALITY_MASK  0x7

/*
 * mask, shअगरt क्रम पढ़ोing 'planned_down_remote_reason_code'
 * from LINK_QUALITY_INFO field
 */
#घोषणा DOWN_REMOTE_REASON_SHIFT 16
#घोषणा DOWN_REMOTE_REASON_MASK  0xff

#घोषणा HOST_INTERFACE_VERSION 1
#घोषणा HOST_INTERFACE_VERSION_SHIFT 16
#घोषणा HOST_INTERFACE_VERSION_MASK  0xff

/* verअगरy capability PHY घातer management bits */
#घोषणा PWRM_BER_CONTROL	0x1
#घोषणा PWRM_BANDWIDTH_CONTROL	0x2

/* 8051 link करोwn reasons */
#घोषणा LDR_LINK_TRANSFER_ACTIVE_LOW   0xa
#घोषणा LDR_RECEIVED_LINKDOWN_IDLE_MSG 0xb
#घोषणा LDR_RECEIVED_HOST_OFFLINE_REQ  0xc

/* verअगरy capability fabric CRC size bits */
क्रमागत अणु
	CAP_CRC_14B = (1 << 0), /* 14b CRC */
	CAP_CRC_48B = (1 << 1), /* 48b CRC */
	CAP_CRC_12B_16B_PER_LANE = (1 << 2) /* 12b-16b per lane CRC */
पूर्ण;

#घोषणा SUPPORTED_CRCS (CAP_CRC_14B | CAP_CRC_48B)

/* misc status version fields */
#घोषणा STS_FM_VERSION_MINOR_SHIFT 16
#घोषणा STS_FM_VERSION_MINOR_MASK  0xff
#घोषणा STS_FM_VERSION_MAJOR_SHIFT 24
#घोषणा STS_FM_VERSION_MAJOR_MASK  0xff
#घोषणा STS_FM_VERSION_PATCH_SHIFT 24
#घोषणा STS_FM_VERSION_PATCH_MASK  0xff

/* LCB_CFG_CRC_MODE TX_VAL and RX_VAL CRC mode values */
#घोषणा LCB_CRC_16B			0x0	/* 16b CRC */
#घोषणा LCB_CRC_14B			0x1	/* 14b CRC */
#घोषणा LCB_CRC_48B			0x2	/* 48b CRC */
#घोषणा LCB_CRC_12B_16B_PER_LANE	0x3	/* 12b-16b per lane CRC */

/*
 * the following क्रमागत is (almost) a copy/paste of the definition
 * in the OPA spec, section 20.2.2.6.8 (PortInfo)
 */
क्रमागत अणु
	PORT_LTP_CRC_MODE_NONE = 0,
	PORT_LTP_CRC_MODE_14 = 1, /* 14-bit LTP CRC mode (optional) */
	PORT_LTP_CRC_MODE_16 = 2, /* 16-bit LTP CRC mode */
	PORT_LTP_CRC_MODE_48 = 4,
		/* 48-bit overlapping LTP CRC mode (optional) */
	PORT_LTP_CRC_MODE_PER_LANE = 8
		/* 12 to 16 bit per lane LTP CRC mode (optional) */
पूर्ण;

/* समयouts */
#घोषणा LINK_RESTART_DELAY 1000		/* link restart delay, in ms */
#घोषणा TIMEOUT_8051_START 5000         /* 8051 start समयout, in ms */
#घोषणा DC8051_COMMAND_TIMEOUT 1000	/* DC8051 command समयout, in ms */
#घोषणा FREEZE_STATUS_TIMEOUT 20	/* रुको क्रम मुक्तze indicators, in ms */
#घोषणा VL_STATUS_CLEAR_TIMEOUT 5000	/* per-VL status clear, in ms */
#घोषणा CCE_STATUS_TIMEOUT 10		/* समय to clear CCE Status, in ms */

/* cघड़ी tick समय, in picoseconds per tick: 1/speed * 10^12  */
#घोषणा ASIC_CCLOCK_PS  1242	/* 805 MHz */
#घोषणा FPGA_CCLOCK_PS 30300	/*  33 MHz */

/*
 * Mask of enabled MISC errors.  Do not enable the two RSA engine errors -
 * see firmware.c:run_rsa() क्रम details.
 */
#घोषणा DRIVER_MISC_MASK \
	(~(MISC_ERR_STATUS_MISC_FW_AUTH_FAILED_ERR_SMASK \
		| MISC_ERR_STATUS_MISC_KEY_MISMATCH_ERR_SMASK))

/* valid values क्रम the loopback module parameter */
#घोषणा LOOPBACK_NONE	0	/* no loopback - शेष */
#घोषणा LOOPBACK_SERDES 1
#घोषणा LOOPBACK_LCB	2
#घोषणा LOOPBACK_CABLE	3	/* बाह्यal cable */

/* set up bits in MISC_CONFIG_BITS */
#घोषणा LOOPBACK_SERDES_CONFIG_BIT_MASK_SHIFT 0
#घोषणा EXT_CFG_LCB_RESET_SUPPORTED_SHIFT     3

/* पढ़ो and ग_लिखो hardware रेजिस्टरs */
u64 पढ़ो_csr(स्थिर काष्ठा hfi1_devdata *dd, u32 offset);
व्योम ग_लिखो_csr(स्थिर काष्ठा hfi1_devdata *dd, u32 offset, u64 value);

/*
 * The *_kctxt_* flavor of the CSR पढ़ो/ग_लिखो functions are क्रम
 * per-context or per-SDMA CSRs that are not mappable to user-space.
 * Their spacing is not a PAGE_SIZE multiple.
 */
अटल अंतरभूत u64 पढ़ो_kctxt_csr(स्थिर काष्ठा hfi1_devdata *dd, पूर्णांक ctxt,
				 u32 offset0)
अणु
	/* kernel per-context CSRs are separated by 0x100 */
	वापस पढ़ो_csr(dd, offset0 + (0x100 * ctxt));
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_kctxt_csr(काष्ठा hfi1_devdata *dd, पूर्णांक ctxt,
				   u32 offset0, u64 value)
अणु
	/* kernel per-context CSRs are separated by 0x100 */
	ग_लिखो_csr(dd, offset0 + (0x100 * ctxt), value);
पूर्ण

पूर्णांक पढ़ो_lcb_csr(काष्ठा hfi1_devdata *dd, u32 offset, u64 *data);
पूर्णांक ग_लिखो_lcb_csr(काष्ठा hfi1_devdata *dd, u32 offset, u64 data);

व्योम __iomem *get_csr_addr(
	स्थिर काष्ठा hfi1_devdata *dd,
	u32 offset);

अटल अंतरभूत व्योम __iomem *get_kctxt_csr_addr(
	स्थिर काष्ठा hfi1_devdata *dd,
	पूर्णांक ctxt,
	u32 offset0)
अणु
	वापस get_csr_addr(dd, offset0 + (0x100 * ctxt));
पूर्ण

/*
 * The *_uctxt_* flavor of the CSR पढ़ो/ग_लिखो functions are क्रम
 * per-context CSRs that are mappable to user space. All these CSRs
 * are spaced by a PAGE_SIZE multiple in order to be mappable to
 * dअगरferent processes without exposing other contexts' CSRs
 */
अटल अंतरभूत u64 पढ़ो_uctxt_csr(स्थिर काष्ठा hfi1_devdata *dd, पूर्णांक ctxt,
				 u32 offset0)
अणु
	/* user per-context CSRs are separated by 0x1000 */
	वापस पढ़ो_csr(dd, offset0 + (0x1000 * ctxt));
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_uctxt_csr(काष्ठा hfi1_devdata *dd, पूर्णांक ctxt,
				   u32 offset0, u64 value)
अणु
	/* user per-context CSRs are separated by 0x1000 */
	ग_लिखो_csr(dd, offset0 + (0x1000 * ctxt), value);
पूर्ण

अटल अंतरभूत u32 chip_rcv_contexts(काष्ठा hfi1_devdata *dd)
अणु
	वापस पढ़ो_csr(dd, RCV_CONTEXTS);
पूर्ण

अटल अंतरभूत u32 chip_send_contexts(काष्ठा hfi1_devdata *dd)
अणु
	वापस पढ़ो_csr(dd, SEND_CONTEXTS);
पूर्ण

अटल अंतरभूत u32 chip_sdma_engines(काष्ठा hfi1_devdata *dd)
अणु
	वापस पढ़ो_csr(dd, SEND_DMA_ENGINES);
पूर्ण

अटल अंतरभूत u32 chip_pio_mem_size(काष्ठा hfi1_devdata *dd)
अणु
	वापस पढ़ो_csr(dd, SEND_PIO_MEM_SIZE);
पूर्ण

अटल अंतरभूत u32 chip_sdma_mem_size(काष्ठा hfi1_devdata *dd)
अणु
	वापस पढ़ो_csr(dd, SEND_DMA_MEM_SIZE);
पूर्ण

अटल अंतरभूत u32 chip_rcv_array_count(काष्ठा hfi1_devdata *dd)
अणु
	वापस पढ़ो_csr(dd, RCV_ARRAY_CNT);
पूर्ण

u8 encode_rcv_header_entry_size(u8 size);
पूर्णांक hfi1_validate_rcvhdrcnt(काष्ठा hfi1_devdata *dd, uपूर्णांक thecnt);
व्योम set_hdrq_regs(काष्ठा hfi1_devdata *dd, u8 ctxt, u8 entsize, u16 hdrcnt);

u64 create_pbc(काष्ठा hfi1_pportdata *ppd, u64 flags, पूर्णांक srate_mbs, u32 vl,
	       u32 dw_len);

/* firmware.c */
#घोषणा SBUS_MASTER_BROADCAST 0xfd
#घोषणा NUM_PCIE_SERDES 16	/* number of PCIe serdes on the SBus */
बाह्य स्थिर u8 pcie_serdes_broadcast[];
बाह्य स्थिर u8 pcie_pcs_addrs[2][NUM_PCIE_SERDES];

/* SBus commands */
#घोषणा RESET_SBUS_RECEIVER 0x20
#घोषणा WRITE_SBUS_RECEIVER 0x21
#घोषणा READ_SBUS_RECEIVER  0x22
व्योम sbus_request(काष्ठा hfi1_devdata *dd,
		  u8 receiver_addr, u8 data_addr, u8 command, u32 data_in);
पूर्णांक sbus_request_slow(काष्ठा hfi1_devdata *dd,
		      u8 receiver_addr, u8 data_addr, u8 command, u32 data_in);
व्योम set_sbus_fast_mode(काष्ठा hfi1_devdata *dd);
व्योम clear_sbus_fast_mode(काष्ठा hfi1_devdata *dd);
पूर्णांक hfi1_firmware_init(काष्ठा hfi1_devdata *dd);
पूर्णांक load_pcie_firmware(काष्ठा hfi1_devdata *dd);
पूर्णांक load_firmware(काष्ठा hfi1_devdata *dd);
व्योम dispose_firmware(व्योम);
पूर्णांक acquire_hw_mutex(काष्ठा hfi1_devdata *dd);
व्योम release_hw_mutex(काष्ठा hfi1_devdata *dd);

/*
 * Biपंचांगask of dynamic access क्रम ASIC block chip resources.  Each HFI has its
 * own range of bits क्रम the resource so it can clear its own bits on
 * starting and निकासing.  If either HFI has the resource bit set, the
 * resource is in use.  The separate bit ranges are:
 *	HFI0 bits  7:0
 *	HFI1 bits 15:8
 */
#घोषणा CR_SBUS  0x01	/* SBUS, THERM, and PCIE रेजिस्टरs */
#घोषणा CR_EPROM 0x02	/* EEP, GPIO रेजिस्टरs */
#घोषणा CR_I2C1  0x04	/* QSFP1_OE रेजिस्टर */
#घोषणा CR_I2C2  0x08	/* QSFP2_OE रेजिस्टर */
#घोषणा CR_DYN_SHIFT 8	/* dynamic flag shअगरt */
#घोषणा CR_DYN_MASK  ((1ull << CR_DYN_SHIFT) - 1)

/*
 * Biपंचांगask of अटल ASIC states these are outside of the dynamic ASIC
 * block chip resources above.  These are to be set once and never cleared.
 * Must be holding the SBus dynamic flag when setting.
 */
#घोषणा CR_THERM_INIT	0x010000

पूर्णांक acquire_chip_resource(काष्ठा hfi1_devdata *dd, u32 resource, u32 msरुको);
व्योम release_chip_resource(काष्ठा hfi1_devdata *dd, u32 resource);
bool check_chip_resource(काष्ठा hfi1_devdata *dd, u32 resource,
			 स्थिर अक्षर *func);
व्योम init_chip_resources(काष्ठा hfi1_devdata *dd);
व्योम finish_chip_resources(काष्ठा hfi1_devdata *dd);

/* ms रुको समय क्रम access to an SBus resoure */
#घोषणा SBUS_TIMEOUT 4000 /* दीर्घ enough क्रम a FW करोwnload and SBR */

/* ms रुको समय क्रम a qsfp (i2c) chain to become available */
#घोषणा QSFP_WAIT 20000 /* दीर्घ enough क्रम FW update to the F4 uc */

व्योम fabric_serdes_reset(काष्ठा hfi1_devdata *dd);
पूर्णांक पढ़ो_8051_data(काष्ठा hfi1_devdata *dd, u32 addr, u32 len, u64 *result);

/* chip.c */
व्योम पढ़ो_misc_status(काष्ठा hfi1_devdata *dd, u8 *ver_major, u8 *ver_minor,
		      u8 *ver_patch);
पूर्णांक ग_लिखो_host_पूर्णांकerface_version(काष्ठा hfi1_devdata *dd, u8 version);
व्योम पढ़ो_guid(काष्ठा hfi1_devdata *dd);
पूर्णांक रुको_fm_पढ़ोy(काष्ठा hfi1_devdata *dd, u32 msसमयout);
व्योम set_link_करोwn_reason(काष्ठा hfi1_pportdata *ppd, u8 lcl_reason,
			  u8 neigh_reason, u8 rem_reason);
पूर्णांक set_link_state(काष्ठा hfi1_pportdata *, u32 state);
पूर्णांक port_ltp_to_cap(पूर्णांक port_ltp);
व्योम handle_verअगरy_cap(काष्ठा work_काष्ठा *work);
व्योम handle_मुक्तze(काष्ठा work_काष्ठा *work);
व्योम handle_link_up(काष्ठा work_काष्ठा *work);
व्योम handle_link_करोwn(काष्ठा work_काष्ठा *work);
व्योम handle_link_करोwngrade(काष्ठा work_काष्ठा *work);
व्योम handle_link_bounce(काष्ठा work_काष्ठा *work);
व्योम handle_start_link(काष्ठा work_काष्ठा *work);
व्योम handle_sma_message(काष्ठा work_काष्ठा *work);
पूर्णांक reset_qsfp(काष्ठा hfi1_pportdata *ppd);
व्योम qsfp_event(काष्ठा work_काष्ठा *work);
व्योम start_मुक्तze_handling(काष्ठा hfi1_pportdata *ppd, पूर्णांक flags);
पूर्णांक send_idle_sma(काष्ठा hfi1_devdata *dd, u64 message);
पूर्णांक load_8051_config(काष्ठा hfi1_devdata *, u8, u8, u32);
पूर्णांक पढ़ो_8051_config(काष्ठा hfi1_devdata *, u8, u8, u32 *);
पूर्णांक start_link(काष्ठा hfi1_pportdata *ppd);
पूर्णांक bringup_serdes(काष्ठा hfi1_pportdata *ppd);
व्योम set_पूर्णांकr_state(काष्ठा hfi1_devdata *dd, u32 enable);
bool apply_link_करोwngrade_policy(काष्ठा hfi1_pportdata *ppd,
				 bool refresh_widths);
व्योम update_usrhead(काष्ठा hfi1_ctxtdata *rcd, u32 hd, u32 updegr, u32 egrhd,
		    u32 पूर्णांकr_adjust, u32 npkts);
पूर्णांक stop_drain_data_vls(काष्ठा hfi1_devdata *dd);
पूर्णांक खोलो_fill_data_vls(काष्ठा hfi1_devdata *dd);
u32 ns_to_cघड़ी(काष्ठा hfi1_devdata *dd, u32 ns);
u32 cघड़ी_प्रकारo_ns(काष्ठा hfi1_devdata *dd, u32 cघड़ी);
व्योम get_linkup_link_widths(काष्ठा hfi1_pportdata *ppd);
व्योम पढ़ो_ltp_rtt(काष्ठा hfi1_devdata *dd);
व्योम clear_linkup_counters(काष्ठा hfi1_devdata *dd);
u32 hdrqempty(काष्ठा hfi1_ctxtdata *rcd);
पूर्णांक is_ax(काष्ठा hfi1_devdata *dd);
पूर्णांक is_bx(काष्ठा hfi1_devdata *dd);
bool is_urg_masked(काष्ठा hfi1_ctxtdata *rcd);
u32 पढ़ो_physical_state(काष्ठा hfi1_devdata *dd);
u32 chip_to_opa_pstate(काष्ठा hfi1_devdata *dd, u32 chip_pstate);
स्थिर अक्षर *opa_lstate_name(u32 lstate);
स्थिर अक्षर *opa_pstate_name(u32 pstate);
u32 driver_pstate(काष्ठा hfi1_pportdata *ppd);
u32 driver_lstate(काष्ठा hfi1_pportdata *ppd);

पूर्णांक acquire_lcb_access(काष्ठा hfi1_devdata *dd, पूर्णांक sleep_ok);
पूर्णांक release_lcb_access(काष्ठा hfi1_devdata *dd, पूर्णांक sleep_ok);
#घोषणा LCB_START DC_LCB_CSRS
#घोषणा LCB_END   DC_8051_CSRS /* next block is 8051 */
बाह्य uपूर्णांक num_vls;

बाह्य uपूर्णांक disable_पूर्णांकegrity;
u64 पढ़ो_dev_cntr(काष्ठा hfi1_devdata *dd, पूर्णांक index, पूर्णांक vl);
u64 ग_लिखो_dev_cntr(काष्ठा hfi1_devdata *dd, पूर्णांक index, पूर्णांक vl, u64 data);
u64 पढ़ो_port_cntr(काष्ठा hfi1_pportdata *ppd, पूर्णांक index, पूर्णांक vl);
u64 ग_लिखो_port_cntr(काष्ठा hfi1_pportdata *ppd, पूर्णांक index, पूर्णांक vl, u64 data);
u32 पढ़ो_logical_state(काष्ठा hfi1_devdata *dd);
व्योम क्रमce_recv_पूर्णांकr(काष्ठा hfi1_ctxtdata *rcd);

/* Per VL indexes */
क्रमागत अणु
	C_VL_0 = 0,
	C_VL_1,
	C_VL_2,
	C_VL_3,
	C_VL_4,
	C_VL_5,
	C_VL_6,
	C_VL_7,
	C_VL_15,
	C_VL_COUNT
पूर्ण;

अटल अंतरभूत पूर्णांक vl_from_idx(पूर्णांक idx)
अणु
	वापस (idx == C_VL_15 ? 15 : idx);
पूर्ण

अटल अंतरभूत पूर्णांक idx_from_vl(पूर्णांक vl)
अणु
	वापस (vl == 15 ? C_VL_15 : vl);
पूर्ण

/* Per device counter indexes */
क्रमागत अणु
	C_RCV_OVF = 0,
	C_RX_LEN_ERR,
	C_RX_SHORT_ERR,
	C_RX_ICRC_ERR,
	C_RX_EBP,
	C_RX_TID_FULL,
	C_RX_TID_INVALID,
	C_RX_TID_FLGMS,
	C_RX_CTX_EGRS,
	C_RCV_TID_FLSMS,
	C_CCE_PCI_CR_ST,
	C_CCE_PCI_TR_ST,
	C_CCE_PIO_WR_ST,
	C_CCE_ERR_INT,
	C_CCE_SDMA_INT,
	C_CCE_MISC_INT,
	C_CCE_RCV_AV_INT,
	C_CCE_RCV_URG_INT,
	C_CCE_SEND_CR_INT,
	C_DC_UNC_ERR,
	C_DC_RCV_ERR,
	C_DC_FM_CFG_ERR,
	C_DC_RMT_PHY_ERR,
	C_DC_DROPPED_PKT,
	C_DC_MC_XMIT_PKTS,
	C_DC_MC_RCV_PKTS,
	C_DC_XMIT_CERR,
	C_DC_RCV_CERR,
	C_DC_RCV_FCC,
	C_DC_XMIT_FCC,
	C_DC_XMIT_FLITS,
	C_DC_RCV_FLITS,
	C_DC_XMIT_PKTS,
	C_DC_RCV_PKTS,
	C_DC_RX_FLIT_VL,
	C_DC_RX_PKT_VL,
	C_DC_RCV_FCN,
	C_DC_RCV_FCN_VL,
	C_DC_RCV_BCN,
	C_DC_RCV_BCN_VL,
	C_DC_RCV_BBL,
	C_DC_RCV_BBL_VL,
	C_DC_MARK_FECN,
	C_DC_MARK_FECN_VL,
	C_DC_TOTAL_CRC,
	C_DC_CRC_LN0,
	C_DC_CRC_LN1,
	C_DC_CRC_LN2,
	C_DC_CRC_LN3,
	C_DC_CRC_MULT_LN,
	C_DC_TX_REPLAY,
	C_DC_RX_REPLAY,
	C_DC_SEQ_CRC_CNT,
	C_DC_ESC0_ONLY_CNT,
	C_DC_ESC0_PLUS1_CNT,
	C_DC_ESC0_PLUS2_CNT,
	C_DC_REINIT_FROM_PEER_CNT,
	C_DC_SBE_CNT,
	C_DC_MISC_FLG_CNT,
	C_DC_PRF_GOOD_LTP_CNT,
	C_DC_PRF_ACCEPTED_LTP_CNT,
	C_DC_PRF_RX_FLIT_CNT,
	C_DC_PRF_TX_FLIT_CNT,
	C_DC_PRF_CLK_CNTR,
	C_DC_PG_DBG_FLIT_CRDTS_CNT,
	C_DC_PG_STS_PAUSE_COMPLETE_CNT,
	C_DC_PG_STS_TX_SBE_CNT,
	C_DC_PG_STS_TX_MBE_CNT,
	C_SW_CPU_INTR,
	C_SW_CPU_RCV_LIM,
	C_SW_CTX0_SEQ_DROP,
	C_SW_VTX_WAIT,
	C_SW_PIO_WAIT,
	C_SW_PIO_DRAIN,
	C_SW_KMEM_WAIT,
	C_SW_TID_WAIT,
	C_SW_SEND_SCHED,
	C_SDMA_DESC_FETCHED_CNT,
	C_SDMA_INT_CNT,
	C_SDMA_ERR_CNT,
	C_SDMA_IDLE_INT_CNT,
	C_SDMA_PROGRESS_INT_CNT,
/* MISC_ERR_STATUS */
	C_MISC_PLL_LOCK_FAIL_ERR,
	C_MISC_MBIST_FAIL_ERR,
	C_MISC_INVALID_EEP_CMD_ERR,
	C_MISC_EFUSE_DONE_PARITY_ERR,
	C_MISC_EFUSE_WRITE_ERR,
	C_MISC_EFUSE_READ_BAD_ADDR_ERR,
	C_MISC_EFUSE_CSR_PARITY_ERR,
	C_MISC_FW_AUTH_FAILED_ERR,
	C_MISC_KEY_MISMATCH_ERR,
	C_MISC_SBUS_WRITE_FAILED_ERR,
	C_MISC_CSR_WRITE_BAD_ADDR_ERR,
	C_MISC_CSR_READ_BAD_ADDR_ERR,
	C_MISC_CSR_PARITY_ERR,
/* CceErrStatus */
	/*
	* A special counter that is the aggregate count
	* of all the cce_err_status errors.  The reमुख्यder
	* are actual bits in the CceErrStatus रेजिस्टर.
	*/
	C_CCE_ERR_STATUS_AGGREGATED_CNT,
	C_CCE_MSIX_CSR_PARITY_ERR,
	C_CCE_INT_MAP_UNC_ERR,
	C_CCE_INT_MAP_COR_ERR,
	C_CCE_MSIX_TABLE_UNC_ERR,
	C_CCE_MSIX_TABLE_COR_ERR,
	C_CCE_RXDMA_CONV_FIFO_PARITY_ERR,
	C_CCE_RCPL_ASYNC_FIFO_PARITY_ERR,
	C_CCE_SEG_WRITE_BAD_ADDR_ERR,
	C_CCE_SEG_READ_BAD_ADDR_ERR,
	C_LA_TRIGGERED,
	C_CCE_TRGT_CPL_TIMEOUT_ERR,
	C_PCIC_RECEIVE_PARITY_ERR,
	C_PCIC_TRANSMIT_BACK_PARITY_ERR,
	C_PCIC_TRANSMIT_FRONT_PARITY_ERR,
	C_PCIC_CPL_DAT_Q_UNC_ERR,
	C_PCIC_CPL_HD_Q_UNC_ERR,
	C_PCIC_POST_DAT_Q_UNC_ERR,
	C_PCIC_POST_HD_Q_UNC_ERR,
	C_PCIC_RETRY_SOT_MEM_UNC_ERR,
	C_PCIC_RETRY_MEM_UNC_ERR,
	C_PCIC_N_POST_DAT_Q_PARITY_ERR,
	C_PCIC_N_POST_H_Q_PARITY_ERR,
	C_PCIC_CPL_DAT_Q_COR_ERR,
	C_PCIC_CPL_HD_Q_COR_ERR,
	C_PCIC_POST_DAT_Q_COR_ERR,
	C_PCIC_POST_HD_Q_COR_ERR,
	C_PCIC_RETRY_SOT_MEM_COR_ERR,
	C_PCIC_RETRY_MEM_COR_ERR,
	C_CCE_CLI1_ASYNC_FIFO_DBG_PARITY_ERR,
	C_CCE_CLI1_ASYNC_FIFO_RXDMA_PARITY_ERR,
	C_CCE_CLI1_ASYNC_FIFO_SDMA_HD_PARITY_ERR,
	C_CCE_CLI1_ASYNC_FIFO_PIO_CRDT_PARITY_ERR,
	C_CCE_CLI2_ASYNC_FIFO_PARITY_ERR,
	C_CCE_CSR_CFG_BUS_PARITY_ERR,
	C_CCE_CLI0_ASYNC_FIFO_PARTIY_ERR,
	C_CCE_RSPD_DATA_PARITY_ERR,
	C_CCE_TRGT_ACCESS_ERR,
	C_CCE_TRGT_ASYNC_FIFO_PARITY_ERR,
	C_CCE_CSR_WRITE_BAD_ADDR_ERR,
	C_CCE_CSR_READ_BAD_ADDR_ERR,
	C_CCE_CSR_PARITY_ERR,
/* RcvErrStatus */
	C_RX_CSR_PARITY_ERR,
	C_RX_CSR_WRITE_BAD_ADDR_ERR,
	C_RX_CSR_READ_BAD_ADDR_ERR,
	C_RX_DMA_CSR_UNC_ERR,
	C_RX_DMA_DQ_FSM_ENCODING_ERR,
	C_RX_DMA_EQ_FSM_ENCODING_ERR,
	C_RX_DMA_CSR_PARITY_ERR,
	C_RX_RBUF_DATA_COR_ERR,
	C_RX_RBUF_DATA_UNC_ERR,
	C_RX_DMA_DATA_FIFO_RD_COR_ERR,
	C_RX_DMA_DATA_FIFO_RD_UNC_ERR,
	C_RX_DMA_HDR_FIFO_RD_COR_ERR,
	C_RX_DMA_HDR_FIFO_RD_UNC_ERR,
	C_RX_RBUF_DESC_PART2_COR_ERR,
	C_RX_RBUF_DESC_PART2_UNC_ERR,
	C_RX_RBUF_DESC_PART1_COR_ERR,
	C_RX_RBUF_DESC_PART1_UNC_ERR,
	C_RX_HQ_INTR_FSM_ERR,
	C_RX_HQ_INTR_CSR_PARITY_ERR,
	C_RX_LOOKUP_CSR_PARITY_ERR,
	C_RX_LOOKUP_RCV_ARRAY_COR_ERR,
	C_RX_LOOKUP_RCV_ARRAY_UNC_ERR,
	C_RX_LOOKUP_DES_PART2_PARITY_ERR,
	C_RX_LOOKUP_DES_PART1_UNC_COR_ERR,
	C_RX_LOOKUP_DES_PART1_UNC_ERR,
	C_RX_RBUF_NEXT_FREE_BUF_COR_ERR,
	C_RX_RBUF_NEXT_FREE_BUF_UNC_ERR,
	C_RX_RBUF_FL_INIT_WR_ADDR_PARITY_ERR,
	C_RX_RBUF_FL_INITDONE_PARITY_ERR,
	C_RX_RBUF_FL_WRITE_ADDR_PARITY_ERR,
	C_RX_RBUF_FL_RD_ADDR_PARITY_ERR,
	C_RX_RBUF_EMPTY_ERR,
	C_RX_RBUF_FULL_ERR,
	C_RX_RBUF_BAD_LOOKUP_ERR,
	C_RX_RBUF_CTX_ID_PARITY_ERR,
	C_RX_RBUF_CSR_QEOPDW_PARITY_ERR,
	C_RX_RBUF_CSR_Q_NUM_OF_PKT_PARITY_ERR,
	C_RX_RBUF_CSR_Q_T1_PTR_PARITY_ERR,
	C_RX_RBUF_CSR_Q_HD_PTR_PARITY_ERR,
	C_RX_RBUF_CSR_Q_VLD_BIT_PARITY_ERR,
	C_RX_RBUF_CSR_Q_NEXT_BUF_PARITY_ERR,
	C_RX_RBUF_CSR_Q_ENT_CNT_PARITY_ERR,
	C_RX_RBUF_CSR_Q_HEAD_BUF_NUM_PARITY_ERR,
	C_RX_RBUF_BLOCK_LIST_READ_COR_ERR,
	C_RX_RBUF_BLOCK_LIST_READ_UNC_ERR,
	C_RX_RBUF_LOOKUP_DES_COR_ERR,
	C_RX_RBUF_LOOKUP_DES_UNC_ERR,
	C_RX_RBUF_LOOKUP_DES_REG_UNC_COR_ERR,
	C_RX_RBUF_LOOKUP_DES_REG_UNC_ERR,
	C_RX_RBUF_FREE_LIST_COR_ERR,
	C_RX_RBUF_FREE_LIST_UNC_ERR,
	C_RX_RCV_FSM_ENCODING_ERR,
	C_RX_DMA_FLAG_COR_ERR,
	C_RX_DMA_FLAG_UNC_ERR,
	C_RX_DC_SOP_EOP_PARITY_ERR,
	C_RX_RCV_CSR_PARITY_ERR,
	C_RX_RCV_QP_MAP_TABLE_COR_ERR,
	C_RX_RCV_QP_MAP_TABLE_UNC_ERR,
	C_RX_RCV_DATA_COR_ERR,
	C_RX_RCV_DATA_UNC_ERR,
	C_RX_RCV_HDR_COR_ERR,
	C_RX_RCV_HDR_UNC_ERR,
	C_RX_DC_INTF_PARITY_ERR,
	C_RX_DMA_CSR_COR_ERR,
/* SendPioErrStatus */
	C_PIO_PEC_SOP_HEAD_PARITY_ERR,
	C_PIO_PCC_SOP_HEAD_PARITY_ERR,
	C_PIO_LAST_RETURNED_CNT_PARITY_ERR,
	C_PIO_CURRENT_FREE_CNT_PARITY_ERR,
	C_PIO_RSVD_31_ERR,
	C_PIO_RSVD_30_ERR,
	C_PIO_PPMC_SOP_LEN_ERR,
	C_PIO_PPMC_BQC_MEM_PARITY_ERR,
	C_PIO_VL_FIFO_PARITY_ERR,
	C_PIO_VLF_SOP_PARITY_ERR,
	C_PIO_VLF_V1_LEN_PARITY_ERR,
	C_PIO_BLOCK_QW_COUNT_PARITY_ERR,
	C_PIO_WRITE_QW_VALID_PARITY_ERR,
	C_PIO_STATE_MACHINE_ERR,
	C_PIO_WRITE_DATA_PARITY_ERR,
	C_PIO_HOST_ADDR_MEM_COR_ERR,
	C_PIO_HOST_ADDR_MEM_UNC_ERR,
	C_PIO_PKT_EVICT_SM_OR_ARM_SM_ERR,
	C_PIO_INIT_SM_IN_ERR,
	C_PIO_PPMC_PBL_FIFO_ERR,
	C_PIO_CREDIT_RET_FIFO_PARITY_ERR,
	C_PIO_V1_LEN_MEM_BANK1_COR_ERR,
	C_PIO_V1_LEN_MEM_BANK0_COR_ERR,
	C_PIO_V1_LEN_MEM_BANK1_UNC_ERR,
	C_PIO_V1_LEN_MEM_BANK0_UNC_ERR,
	C_PIO_SM_PKT_RESET_PARITY_ERR,
	C_PIO_PKT_EVICT_FIFO_PARITY_ERR,
	C_PIO_SBRDCTRL_CRREL_FIFO_PARITY_ERR,
	C_PIO_SBRDCTL_CRREL_PARITY_ERR,
	C_PIO_PEC_FIFO_PARITY_ERR,
	C_PIO_PCC_FIFO_PARITY_ERR,
	C_PIO_SB_MEM_FIFO1_ERR,
	C_PIO_SB_MEM_FIFO0_ERR,
	C_PIO_CSR_PARITY_ERR,
	C_PIO_WRITE_ADDR_PARITY_ERR,
	C_PIO_WRITE_BAD_CTXT_ERR,
/* SendDmaErrStatus */
	C_SDMA_PCIE_REQ_TRACKING_COR_ERR,
	C_SDMA_PCIE_REQ_TRACKING_UNC_ERR,
	C_SDMA_CSR_PARITY_ERR,
	C_SDMA_RPY_TAG_ERR,
/* SendEgressErrStatus */
	C_TX_READ_PIO_MEMORY_CSR_UNC_ERR,
	C_TX_READ_SDMA_MEMORY_CSR_UNC_ERR,
	C_TX_EGRESS_FIFO_COR_ERR,
	C_TX_READ_PIO_MEMORY_COR_ERR,
	C_TX_READ_SDMA_MEMORY_COR_ERR,
	C_TX_SB_HDR_COR_ERR,
	C_TX_CREDIT_OVERRUN_ERR,
	C_TX_LAUNCH_FIFO8_COR_ERR,
	C_TX_LAUNCH_FIFO7_COR_ERR,
	C_TX_LAUNCH_FIFO6_COR_ERR,
	C_TX_LAUNCH_FIFO5_COR_ERR,
	C_TX_LAUNCH_FIFO4_COR_ERR,
	C_TX_LAUNCH_FIFO3_COR_ERR,
	C_TX_LAUNCH_FIFO2_COR_ERR,
	C_TX_LAUNCH_FIFO1_COR_ERR,
	C_TX_LAUNCH_FIFO0_COR_ERR,
	C_TX_CREDIT_RETURN_VL_ERR,
	C_TX_HCRC_INSERTION_ERR,
	C_TX_EGRESS_FIFI_UNC_ERR,
	C_TX_READ_PIO_MEMORY_UNC_ERR,
	C_TX_READ_SDMA_MEMORY_UNC_ERR,
	C_TX_SB_HDR_UNC_ERR,
	C_TX_CREDIT_RETURN_PARITY_ERR,
	C_TX_LAUNCH_FIFO8_UNC_OR_PARITY_ERR,
	C_TX_LAUNCH_FIFO7_UNC_OR_PARITY_ERR,
	C_TX_LAUNCH_FIFO6_UNC_OR_PARITY_ERR,
	C_TX_LAUNCH_FIFO5_UNC_OR_PARITY_ERR,
	C_TX_LAUNCH_FIFO4_UNC_OR_PARITY_ERR,
	C_TX_LAUNCH_FIFO3_UNC_OR_PARITY_ERR,
	C_TX_LAUNCH_FIFO2_UNC_OR_PARITY_ERR,
	C_TX_LAUNCH_FIFO1_UNC_OR_PARITY_ERR,
	C_TX_LAUNCH_FIFO0_UNC_OR_PARITY_ERR,
	C_TX_SDMA15_DISALLOWED_PACKET_ERR,
	C_TX_SDMA14_DISALLOWED_PACKET_ERR,
	C_TX_SDMA13_DISALLOWED_PACKET_ERR,
	C_TX_SDMA12_DISALLOWED_PACKET_ERR,
	C_TX_SDMA11_DISALLOWED_PACKET_ERR,
	C_TX_SDMA10_DISALLOWED_PACKET_ERR,
	C_TX_SDMA9_DISALLOWED_PACKET_ERR,
	C_TX_SDMA8_DISALLOWED_PACKET_ERR,
	C_TX_SDMA7_DISALLOWED_PACKET_ERR,
	C_TX_SDMA6_DISALLOWED_PACKET_ERR,
	C_TX_SDMA5_DISALLOWED_PACKET_ERR,
	C_TX_SDMA4_DISALLOWED_PACKET_ERR,
	C_TX_SDMA3_DISALLOWED_PACKET_ERR,
	C_TX_SDMA2_DISALLOWED_PACKET_ERR,
	C_TX_SDMA1_DISALLOWED_PACKET_ERR,
	C_TX_SDMA0_DISALLOWED_PACKET_ERR,
	C_TX_CONFIG_PARITY_ERR,
	C_TX_SBRD_CTL_CSR_PARITY_ERR,
	C_TX_LAUNCH_CSR_PARITY_ERR,
	C_TX_ILLEGAL_CL_ERR,
	C_TX_SBRD_CTL_STATE_MACHINE_PARITY_ERR,
	C_TX_RESERVED_10,
	C_TX_RESERVED_9,
	C_TX_SDMA_LAUNCH_INTF_PARITY_ERR,
	C_TX_PIO_LAUNCH_INTF_PARITY_ERR,
	C_TX_RESERVED_6,
	C_TX_INCORRECT_LINK_STATE_ERR,
	C_TX_LINK_DOWN_ERR,
	C_TX_EGRESS_FIFO_UNDERRUN_OR_PARITY_ERR,
	C_TX_RESERVED_2,
	C_TX_PKT_INTEGRITY_MEM_UNC_ERR,
	C_TX_PKT_INTEGRITY_MEM_COR_ERR,
/* SendErrStatus */
	C_SEND_CSR_WRITE_BAD_ADDR_ERR,
	C_SEND_CSR_READ_BAD_ADD_ERR,
	C_SEND_CSR_PARITY_ERR,
/* SendCtxtErrStatus */
	C_PIO_WRITE_OUT_OF_BOUNDS_ERR,
	C_PIO_WRITE_OVERFLOW_ERR,
	C_PIO_WRITE_CROSSES_BOUNDARY_ERR,
	C_PIO_DISALLOWED_PACKET_ERR,
	C_PIO_INCONSISTENT_SOP_ERR,
/*SendDmaEngErrStatus */
	C_SDMA_HEADER_REQUEST_FIFO_COR_ERR,
	C_SDMA_HEADER_STORAGE_COR_ERR,
	C_SDMA_PACKET_TRACKING_COR_ERR,
	C_SDMA_ASSEMBLY_COR_ERR,
	C_SDMA_DESC_TABLE_COR_ERR,
	C_SDMA_HEADER_REQUEST_FIFO_UNC_ERR,
	C_SDMA_HEADER_STORAGE_UNC_ERR,
	C_SDMA_PACKET_TRACKING_UNC_ERR,
	C_SDMA_ASSEMBLY_UNC_ERR,
	C_SDMA_DESC_TABLE_UNC_ERR,
	C_SDMA_TIMEOUT_ERR,
	C_SDMA_HEADER_LENGTH_ERR,
	C_SDMA_HEADER_ADDRESS_ERR,
	C_SDMA_HEADER_SELECT_ERR,
	C_SMDA_RESERVED_9,
	C_SDMA_PACKET_DESC_OVERFLOW_ERR,
	C_SDMA_LENGTH_MISMATCH_ERR,
	C_SDMA_HALT_ERR,
	C_SDMA_MEM_READ_ERR,
	C_SDMA_FIRST_DESC_ERR,
	C_SDMA_TAIL_OUT_OF_BOUNDS_ERR,
	C_SDMA_TOO_LONG_ERR,
	C_SDMA_GEN_MISMATCH_ERR,
	C_SDMA_WRONG_DW_ERR,
	DEV_CNTR_LAST  /* Must be kept last */
पूर्ण;

/* Per port counter indexes */
क्रमागत अणु
	C_TX_UNSUP_VL = 0,
	C_TX_INVAL_LEN,
	C_TX_MM_LEN_ERR,
	C_TX_UNDERRUN,
	C_TX_FLOW_STALL,
	C_TX_DROPPED,
	C_TX_HDR_ERR,
	C_TX_PKT,
	C_TX_WORDS,
	C_TX_WAIT,
	C_TX_FLIT_VL,
	C_TX_PKT_VL,
	C_TX_WAIT_VL,
	C_RX_PKT,
	C_RX_WORDS,
	C_SW_LINK_DOWN,
	C_SW_LINK_UP,
	C_SW_UNKNOWN_FRAME,
	C_SW_XMIT_DSCD,
	C_SW_XMIT_DSCD_VL,
	C_SW_XMIT_CSTR_ERR,
	C_SW_RCV_CSTR_ERR,
	C_SW_IBP_LOOP_PKTS,
	C_SW_IBP_RC_RESENDS,
	C_SW_IBP_RNR_NAKS,
	C_SW_IBP_OTHER_NAKS,
	C_SW_IBP_RC_TIMEOUTS,
	C_SW_IBP_PKT_DROPS,
	C_SW_IBP_DMA_WAIT,
	C_SW_IBP_RC_SEQNAK,
	C_SW_IBP_RC_DUPREQ,
	C_SW_IBP_RDMA_SEQ,
	C_SW_IBP_UNALIGNED,
	C_SW_IBP_SEQ_NAK,
	C_SW_IBP_RC_CRWAITS,
	C_SW_CPU_RC_ACKS,
	C_SW_CPU_RC_QACKS,
	C_SW_CPU_RC_DELAYED_COMP,
	C_RCV_HDR_OVF_0,
	C_RCV_HDR_OVF_1,
	C_RCV_HDR_OVF_2,
	C_RCV_HDR_OVF_3,
	C_RCV_HDR_OVF_4,
	C_RCV_HDR_OVF_5,
	C_RCV_HDR_OVF_6,
	C_RCV_HDR_OVF_7,
	C_RCV_HDR_OVF_8,
	C_RCV_HDR_OVF_9,
	C_RCV_HDR_OVF_10,
	C_RCV_HDR_OVF_11,
	C_RCV_HDR_OVF_12,
	C_RCV_HDR_OVF_13,
	C_RCV_HDR_OVF_14,
	C_RCV_HDR_OVF_15,
	C_RCV_HDR_OVF_16,
	C_RCV_HDR_OVF_17,
	C_RCV_HDR_OVF_18,
	C_RCV_HDR_OVF_19,
	C_RCV_HDR_OVF_20,
	C_RCV_HDR_OVF_21,
	C_RCV_HDR_OVF_22,
	C_RCV_HDR_OVF_23,
	C_RCV_HDR_OVF_24,
	C_RCV_HDR_OVF_25,
	C_RCV_HDR_OVF_26,
	C_RCV_HDR_OVF_27,
	C_RCV_HDR_OVF_28,
	C_RCV_HDR_OVF_29,
	C_RCV_HDR_OVF_30,
	C_RCV_HDR_OVF_31,
	C_RCV_HDR_OVF_32,
	C_RCV_HDR_OVF_33,
	C_RCV_HDR_OVF_34,
	C_RCV_HDR_OVF_35,
	C_RCV_HDR_OVF_36,
	C_RCV_HDR_OVF_37,
	C_RCV_HDR_OVF_38,
	C_RCV_HDR_OVF_39,
	C_RCV_HDR_OVF_40,
	C_RCV_HDR_OVF_41,
	C_RCV_HDR_OVF_42,
	C_RCV_HDR_OVF_43,
	C_RCV_HDR_OVF_44,
	C_RCV_HDR_OVF_45,
	C_RCV_HDR_OVF_46,
	C_RCV_HDR_OVF_47,
	C_RCV_HDR_OVF_48,
	C_RCV_HDR_OVF_49,
	C_RCV_HDR_OVF_50,
	C_RCV_HDR_OVF_51,
	C_RCV_HDR_OVF_52,
	C_RCV_HDR_OVF_53,
	C_RCV_HDR_OVF_54,
	C_RCV_HDR_OVF_55,
	C_RCV_HDR_OVF_56,
	C_RCV_HDR_OVF_57,
	C_RCV_HDR_OVF_58,
	C_RCV_HDR_OVF_59,
	C_RCV_HDR_OVF_60,
	C_RCV_HDR_OVF_61,
	C_RCV_HDR_OVF_62,
	C_RCV_HDR_OVF_63,
	C_RCV_HDR_OVF_64,
	C_RCV_HDR_OVF_65,
	C_RCV_HDR_OVF_66,
	C_RCV_HDR_OVF_67,
	C_RCV_HDR_OVF_68,
	C_RCV_HDR_OVF_69,
	C_RCV_HDR_OVF_70,
	C_RCV_HDR_OVF_71,
	C_RCV_HDR_OVF_72,
	C_RCV_HDR_OVF_73,
	C_RCV_HDR_OVF_74,
	C_RCV_HDR_OVF_75,
	C_RCV_HDR_OVF_76,
	C_RCV_HDR_OVF_77,
	C_RCV_HDR_OVF_78,
	C_RCV_HDR_OVF_79,
	C_RCV_HDR_OVF_80,
	C_RCV_HDR_OVF_81,
	C_RCV_HDR_OVF_82,
	C_RCV_HDR_OVF_83,
	C_RCV_HDR_OVF_84,
	C_RCV_HDR_OVF_85,
	C_RCV_HDR_OVF_86,
	C_RCV_HDR_OVF_87,
	C_RCV_HDR_OVF_88,
	C_RCV_HDR_OVF_89,
	C_RCV_HDR_OVF_90,
	C_RCV_HDR_OVF_91,
	C_RCV_HDR_OVF_92,
	C_RCV_HDR_OVF_93,
	C_RCV_HDR_OVF_94,
	C_RCV_HDR_OVF_95,
	C_RCV_HDR_OVF_96,
	C_RCV_HDR_OVF_97,
	C_RCV_HDR_OVF_98,
	C_RCV_HDR_OVF_99,
	C_RCV_HDR_OVF_100,
	C_RCV_HDR_OVF_101,
	C_RCV_HDR_OVF_102,
	C_RCV_HDR_OVF_103,
	C_RCV_HDR_OVF_104,
	C_RCV_HDR_OVF_105,
	C_RCV_HDR_OVF_106,
	C_RCV_HDR_OVF_107,
	C_RCV_HDR_OVF_108,
	C_RCV_HDR_OVF_109,
	C_RCV_HDR_OVF_110,
	C_RCV_HDR_OVF_111,
	C_RCV_HDR_OVF_112,
	C_RCV_HDR_OVF_113,
	C_RCV_HDR_OVF_114,
	C_RCV_HDR_OVF_115,
	C_RCV_HDR_OVF_116,
	C_RCV_HDR_OVF_117,
	C_RCV_HDR_OVF_118,
	C_RCV_HDR_OVF_119,
	C_RCV_HDR_OVF_120,
	C_RCV_HDR_OVF_121,
	C_RCV_HDR_OVF_122,
	C_RCV_HDR_OVF_123,
	C_RCV_HDR_OVF_124,
	C_RCV_HDR_OVF_125,
	C_RCV_HDR_OVF_126,
	C_RCV_HDR_OVF_127,
	C_RCV_HDR_OVF_128,
	C_RCV_HDR_OVF_129,
	C_RCV_HDR_OVF_130,
	C_RCV_HDR_OVF_131,
	C_RCV_HDR_OVF_132,
	C_RCV_HDR_OVF_133,
	C_RCV_HDR_OVF_134,
	C_RCV_HDR_OVF_135,
	C_RCV_HDR_OVF_136,
	C_RCV_HDR_OVF_137,
	C_RCV_HDR_OVF_138,
	C_RCV_HDR_OVF_139,
	C_RCV_HDR_OVF_140,
	C_RCV_HDR_OVF_141,
	C_RCV_HDR_OVF_142,
	C_RCV_HDR_OVF_143,
	C_RCV_HDR_OVF_144,
	C_RCV_HDR_OVF_145,
	C_RCV_HDR_OVF_146,
	C_RCV_HDR_OVF_147,
	C_RCV_HDR_OVF_148,
	C_RCV_HDR_OVF_149,
	C_RCV_HDR_OVF_150,
	C_RCV_HDR_OVF_151,
	C_RCV_HDR_OVF_152,
	C_RCV_HDR_OVF_153,
	C_RCV_HDR_OVF_154,
	C_RCV_HDR_OVF_155,
	C_RCV_HDR_OVF_156,
	C_RCV_HDR_OVF_157,
	C_RCV_HDR_OVF_158,
	C_RCV_HDR_OVF_159,
	PORT_CNTR_LAST /* Must be kept last */
पूर्ण;

u64 get_all_cpu_total(u64 __percpu *cntr);
व्योम hfi1_start_cleanup(काष्ठा hfi1_devdata *dd);
व्योम hfi1_clear_tids(काष्ठा hfi1_ctxtdata *rcd);
व्योम hfi1_init_ctxt(काष्ठा send_context *sc);
व्योम hfi1_put_tid(काष्ठा hfi1_devdata *dd, u32 index,
		  u32 type, अचिन्हित दीर्घ pa, u16 order);
व्योम hfi1_quiet_serdes(काष्ठा hfi1_pportdata *ppd);
व्योम hfi1_rcvctrl(काष्ठा hfi1_devdata *dd, अचिन्हित पूर्णांक op,
		  काष्ठा hfi1_ctxtdata *rcd);
u32 hfi1_पढ़ो_cntrs(काष्ठा hfi1_devdata *dd, अक्षर **namep, u64 **cntrp);
u32 hfi1_पढ़ो_portcntrs(काष्ठा hfi1_pportdata *ppd, अक्षर **namep, u64 **cntrp);
पूर्णांक hfi1_get_ib_cfg(काष्ठा hfi1_pportdata *ppd, पूर्णांक which);
पूर्णांक hfi1_set_ib_cfg(काष्ठा hfi1_pportdata *ppd, पूर्णांक which, u32 val);
पूर्णांक hfi1_set_ctxt_jkey(काष्ठा hfi1_devdata *dd, काष्ठा hfi1_ctxtdata *rcd,
		       u16 jkey);
पूर्णांक hfi1_clear_ctxt_jkey(काष्ठा hfi1_devdata *dd, काष्ठा hfi1_ctxtdata *ctxt);
पूर्णांक hfi1_set_ctxt_pkey(काष्ठा hfi1_devdata *dd, काष्ठा hfi1_ctxtdata *ctxt,
		       u16 pkey);
पूर्णांक hfi1_clear_ctxt_pkey(काष्ठा hfi1_devdata *dd, काष्ठा hfi1_ctxtdata *ctxt);
व्योम hfi1_पढ़ो_link_quality(काष्ठा hfi1_devdata *dd, u8 *link_quality);
व्योम hfi1_init_vnic_rsm(काष्ठा hfi1_devdata *dd);
व्योम hfi1_deinit_vnic_rsm(काष्ठा hfi1_devdata *dd);

irqवापस_t general_पूर्णांकerrupt(पूर्णांक irq, व्योम *data);
irqवापस_t sdma_पूर्णांकerrupt(पूर्णांक irq, व्योम *data);
irqवापस_t receive_context_पूर्णांकerrupt(पूर्णांक irq, व्योम *data);
irqवापस_t receive_context_thपढ़ो(पूर्णांक irq, व्योम *data);
irqवापस_t receive_context_पूर्णांकerrupt_napi(पूर्णांक irq, व्योम *data);

पूर्णांक set_पूर्णांकr_bits(काष्ठा hfi1_devdata *dd, u16 first, u16 last, bool set);
व्योम init_qsfp_पूर्णांक(काष्ठा hfi1_devdata *dd);
व्योम clear_all_पूर्णांकerrupts(काष्ठा hfi1_devdata *dd);
व्योम remap_पूर्णांकr(काष्ठा hfi1_devdata *dd, पूर्णांक isrc, पूर्णांक msix_पूर्णांकr);
व्योम remap_sdma_पूर्णांकerrupts(काष्ठा hfi1_devdata *dd, पूर्णांक engine, पूर्णांक msix_पूर्णांकr);
व्योम reset_पूर्णांकerrupts(काष्ठा hfi1_devdata *dd);
u8 hfi1_get_qp_map(काष्ठा hfi1_devdata *dd, u8 idx);
व्योम hfi1_init_aip_rsm(काष्ठा hfi1_devdata *dd);
व्योम hfi1_deinit_aip_rsm(काष्ठा hfi1_devdata *dd);

/*
 * Interrupt source table.
 *
 * Each entry is an पूर्णांकerrupt source "type".  It is ordered by increasing
 * number.
 */
काष्ठा is_table अणु
	पूर्णांक start;	 /* पूर्णांकerrupt source type start */
	पूर्णांक end;	 /* पूर्णांकerrupt source type end */
	/* routine that वापसs the name of the पूर्णांकerrupt source */
	अक्षर *(*is_name)(अक्षर *name, माप_प्रकार size, अचिन्हित पूर्णांक source);
	/* routine to call when receiving an पूर्णांकerrupt */
	व्योम (*is_पूर्णांक)(काष्ठा hfi1_devdata *dd, अचिन्हित पूर्णांक source);
पूर्ण;

#पूर्ण_अगर /* _CHIP_H */
