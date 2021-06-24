<शैली गुरु>
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
 * This file contains all of the code that is specअगरic to the HFI chip
 */

#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>

#समावेश "hfi.h"
#समावेश "trace.h"
#समावेश "mad.h"
#समावेश "pio.h"
#समावेश "sdma.h"
#समावेश "eprom.h"
#समावेश "efivar.h"
#समावेश "platform.h"
#समावेश "aspm.h"
#समावेश "affinity.h"
#समावेश "debugfs.h"
#समावेश "fault.h"
#समावेश "netdev.h"

uपूर्णांक num_vls = HFI1_MAX_VLS_SUPPORTED;
module_param(num_vls, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(num_vls, "Set number of Virtual Lanes to use (1-8)");

/*
 * Default समय to aggregate two 10K packets from the idle state
 * (समयr not running). The समयr starts at the end of the first packet,
 * so only the समय क्रम one 10K packet and header plus a bit extra is needed.
 * 10 * 1024 + 64 header byte = 10304 byte
 * 10304 byte / 12.5 GB/s = 824.32ns
 */
uपूर्णांक rcv_पूर्णांकr_समयout = (824 + 16); /* 16 is क्रम coalescing पूर्णांकerrupt */
module_param(rcv_पूर्णांकr_समयout, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(rcv_पूर्णांकr_समयout, "Receive interrupt mitigation timeout in ns");

uपूर्णांक rcv_पूर्णांकr_count = 16; /* same as qib */
module_param(rcv_पूर्णांकr_count, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(rcv_पूर्णांकr_count, "Receive interrupt mitigation count");

uलघु link_crc_mask = SUPPORTED_CRCS;
module_param(link_crc_mask, uलघु, S_IRUGO);
MODULE_PARM_DESC(link_crc_mask, "CRCs to use on the link");

uपूर्णांक loopback;
module_param_named(loopback, loopback, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(loopback, "Put into loopback mode (1 = serdes, 3 = external cable");

/* Other driver tunables */
uपूर्णांक rcv_पूर्णांकr_dynamic = 1; /* enable dynamic mode क्रम rcv पूर्णांक mitigation*/
अटल uलघु crc_14b_sideband = 1;
अटल uपूर्णांक use_flr = 1;
uपूर्णांक quick_linkup; /* skip LNI */

काष्ठा flag_table अणु
	u64 flag;	/* the flag */
	अक्षर *str;	/* description string */
	u16 extra;	/* extra inक्रमmation */
	u16 unused0;
	u32 unused1;
पूर्ण;

/* str must be a string स्थिरant */
#घोषणा FLAG_ENTRY(str, extra, flag) अणुflag, str, extraपूर्ण
#घोषणा FLAG_ENTRY0(str, flag) अणुflag, str, 0पूर्ण

/* Send Error Consequences */
#घोषणा SEC_WRITE_DROPPED	0x1
#घोषणा SEC_PACKET_DROPPED	0x2
#घोषणा SEC_SC_HALTED		0x4	/* per-context only */
#घोषणा SEC_SPC_FREEZE		0x8	/* per-HFI only */

#घोषणा DEFAULT_KRCVQS		  2
#घोषणा MIN_KERNEL_KCTXTS         2
#घोषणा FIRST_KERNEL_KCTXT        1

/*
 * RSM instance allocation
 *   0 - User Fecn Handling
 *   1 - Vnic
 *   2 - AIP
 *   3 - Verbs
 */
#घोषणा RSM_INS_FECN              0
#घोषणा RSM_INS_VNIC              1
#घोषणा RSM_INS_AIP               2
#घोषणा RSM_INS_VERBS             3

/* Bit offset पूर्णांकo the GUID which carries HFI id inक्रमmation */
#घोषणा GUID_HFI_INDEX_SHIFT     39

/* extract the emulation revision */
#घोषणा emulator_rev(dd) ((dd)->irev >> 8)
/* parallel and serial emulation versions are 3 and 4 respectively */
#घोषणा is_emulator_p(dd) ((((dd)->irev) & 0xf) == 3)
#घोषणा is_emulator_s(dd) ((((dd)->irev) & 0xf) == 4)

/* RSM fields क्रम Verbs */
/* packet type */
#घोषणा IB_PACKET_TYPE         2ull
#घोषणा QW_SHIFT               6ull
/* QPN[7..1] */
#घोषणा QPN_WIDTH              7ull

/* LRH.BTH: QW 0, OFFSET 48 - क्रम match */
#घोषणा LRH_BTH_QW             0ull
#घोषणा LRH_BTH_BIT_OFFSET     48ull
#घोषणा LRH_BTH_OFFSET(off)    ((LRH_BTH_QW << QW_SHIFT) | (off))
#घोषणा LRH_BTH_MATCH_OFFSET   LRH_BTH_OFFSET(LRH_BTH_BIT_OFFSET)
#घोषणा LRH_BTH_SELECT
#घोषणा LRH_BTH_MASK           3ull
#घोषणा LRH_BTH_VALUE          2ull

/* LRH.SC[3..0] QW 0, OFFSET 56 - क्रम match */
#घोषणा LRH_SC_QW              0ull
#घोषणा LRH_SC_BIT_OFFSET      56ull
#घोषणा LRH_SC_OFFSET(off)     ((LRH_SC_QW << QW_SHIFT) | (off))
#घोषणा LRH_SC_MATCH_OFFSET    LRH_SC_OFFSET(LRH_SC_BIT_OFFSET)
#घोषणा LRH_SC_MASK            128ull
#घोषणा LRH_SC_VALUE           0ull

/* SC[n..0] QW 0, OFFSET 60 - क्रम select */
#घोषणा LRH_SC_SELECT_OFFSET  ((LRH_SC_QW << QW_SHIFT) | (60ull))

/* QPN[m+n:1] QW 1, OFFSET 1 */
#घोषणा QPN_SELECT_OFFSET      ((1ull << QW_SHIFT) | (1ull))

/* RSM fields क्रम AIP */
/* LRH.BTH above is reused क्रम this rule */

/* BTH.DESTQP: QW 1, OFFSET 16 क्रम match */
#घोषणा BTH_DESTQP_QW           1ull
#घोषणा BTH_DESTQP_BIT_OFFSET   16ull
#घोषणा BTH_DESTQP_OFFSET(off) ((BTH_DESTQP_QW << QW_SHIFT) | (off))
#घोषणा BTH_DESTQP_MATCH_OFFSET BTH_DESTQP_OFFSET(BTH_DESTQP_BIT_OFFSET)
#घोषणा BTH_DESTQP_MASK         0xFFull
#घोषणा BTH_DESTQP_VALUE        0x81ull

/* DETH.SQPN: QW 1 Offset 56 क्रम select */
/* We use 8 most signअगरicant Soure QPN bits as entropy fpr AIP */
#घोषणा DETH_AIP_SQPN_QW 3ull
#घोषणा DETH_AIP_SQPN_BIT_OFFSET 56ull
#घोषणा DETH_AIP_SQPN_OFFSET(off) ((DETH_AIP_SQPN_QW << QW_SHIFT) | (off))
#घोषणा DETH_AIP_SQPN_SELECT_OFFSET \
	DETH_AIP_SQPN_OFFSET(DETH_AIP_SQPN_BIT_OFFSET)

/* RSM fields क्रम Vnic */
/* L2_TYPE: QW 0, OFFSET 61 - क्रम match */
#घोषणा L2_TYPE_QW             0ull
#घोषणा L2_TYPE_BIT_OFFSET     61ull
#घोषणा L2_TYPE_OFFSET(off)    ((L2_TYPE_QW << QW_SHIFT) | (off))
#घोषणा L2_TYPE_MATCH_OFFSET   L2_TYPE_OFFSET(L2_TYPE_BIT_OFFSET)
#घोषणा L2_TYPE_MASK           3ull
#घोषणा L2_16B_VALUE           2ull

/* L4_TYPE QW 1, OFFSET 0 - क्रम match */
#घोषणा L4_TYPE_QW              1ull
#घोषणा L4_TYPE_BIT_OFFSET      0ull
#घोषणा L4_TYPE_OFFSET(off)     ((L4_TYPE_QW << QW_SHIFT) | (off))
#घोषणा L4_TYPE_MATCH_OFFSET    L4_TYPE_OFFSET(L4_TYPE_BIT_OFFSET)
#घोषणा L4_16B_TYPE_MASK        0xFFull
#घोषणा L4_16B_ETH_VALUE        0x78ull

/* 16B VESWID - क्रम select */
#घोषणा L4_16B_HDR_VESWID_OFFSET  ((2 << QW_SHIFT) | (16ull))
/* 16B ENTROPY - क्रम select */
#घोषणा L2_16B_ENTROPY_OFFSET     ((1 << QW_SHIFT) | (32ull))

/* defines to build घातer on SC2VL table */
#घोषणा SC2VL_VAL( \
	num, \
	sc0, sc0val, \
	sc1, sc1val, \
	sc2, sc2val, \
	sc3, sc3val, \
	sc4, sc4val, \
	sc5, sc5val, \
	sc6, sc6val, \
	sc7, sc7val) \
( \
	((u64)(sc0val) << SEND_SC2VLT##num##_SC##sc0##_SHIFT) | \
	((u64)(sc1val) << SEND_SC2VLT##num##_SC##sc1##_SHIFT) | \
	((u64)(sc2val) << SEND_SC2VLT##num##_SC##sc2##_SHIFT) | \
	((u64)(sc3val) << SEND_SC2VLT##num##_SC##sc3##_SHIFT) | \
	((u64)(sc4val) << SEND_SC2VLT##num##_SC##sc4##_SHIFT) | \
	((u64)(sc5val) << SEND_SC2VLT##num##_SC##sc5##_SHIFT) | \
	((u64)(sc6val) << SEND_SC2VLT##num##_SC##sc6##_SHIFT) | \
	((u64)(sc7val) << SEND_SC2VLT##num##_SC##sc7##_SHIFT)   \
)

#घोषणा DC_SC_VL_VAL( \
	range, \
	e0, e0val, \
	e1, e1val, \
	e2, e2val, \
	e3, e3val, \
	e4, e4val, \
	e5, e5val, \
	e6, e6val, \
	e7, e7val, \
	e8, e8val, \
	e9, e9val, \
	e10, e10val, \
	e11, e11val, \
	e12, e12val, \
	e13, e13val, \
	e14, e14val, \
	e15, e15val) \
( \
	((u64)(e0val) << DCC_CFG_SC_VL_TABLE_##range##_ENTRY##e0##_SHIFT) | \
	((u64)(e1val) << DCC_CFG_SC_VL_TABLE_##range##_ENTRY##e1##_SHIFT) | \
	((u64)(e2val) << DCC_CFG_SC_VL_TABLE_##range##_ENTRY##e2##_SHIFT) | \
	((u64)(e3val) << DCC_CFG_SC_VL_TABLE_##range##_ENTRY##e3##_SHIFT) | \
	((u64)(e4val) << DCC_CFG_SC_VL_TABLE_##range##_ENTRY##e4##_SHIFT) | \
	((u64)(e5val) << DCC_CFG_SC_VL_TABLE_##range##_ENTRY##e5##_SHIFT) | \
	((u64)(e6val) << DCC_CFG_SC_VL_TABLE_##range##_ENTRY##e6##_SHIFT) | \
	((u64)(e7val) << DCC_CFG_SC_VL_TABLE_##range##_ENTRY##e7##_SHIFT) | \
	((u64)(e8val) << DCC_CFG_SC_VL_TABLE_##range##_ENTRY##e8##_SHIFT) | \
	((u64)(e9val) << DCC_CFG_SC_VL_TABLE_##range##_ENTRY##e9##_SHIFT) | \
	((u64)(e10val) << DCC_CFG_SC_VL_TABLE_##range##_ENTRY##e10##_SHIFT) | \
	((u64)(e11val) << DCC_CFG_SC_VL_TABLE_##range##_ENTRY##e11##_SHIFT) | \
	((u64)(e12val) << DCC_CFG_SC_VL_TABLE_##range##_ENTRY##e12##_SHIFT) | \
	((u64)(e13val) << DCC_CFG_SC_VL_TABLE_##range##_ENTRY##e13##_SHIFT) | \
	((u64)(e14val) << DCC_CFG_SC_VL_TABLE_##range##_ENTRY##e14##_SHIFT) | \
	((u64)(e15val) << DCC_CFG_SC_VL_TABLE_##range##_ENTRY##e15##_SHIFT) \
)

/* all CceStatus sub-block मुक्तze bits */
#घोषणा ALL_FROZE (CCE_STATUS_SDMA_FROZE_SMASK \
			| CCE_STATUS_RXE_FROZE_SMASK \
			| CCE_STATUS_TXE_FROZE_SMASK \
			| CCE_STATUS_TXE_PIO_FROZE_SMASK)
/* all CceStatus sub-block TXE छोड़ो bits */
#घोषणा ALL_TXE_PAUSE (CCE_STATUS_TXE_PIO_PAUSED_SMASK \
			| CCE_STATUS_TXE_PAUSED_SMASK \
			| CCE_STATUS_SDMA_PAUSED_SMASK)
/* all CceStatus sub-block RXE छोड़ो bits */
#घोषणा ALL_RXE_PAUSE CCE_STATUS_RXE_PAUSED_SMASK

#घोषणा CNTR_MAX 0xFFFFFFFFFFFFFFFFULL
#घोषणा CNTR_32BIT_MAX 0x00000000FFFFFFFF

/*
 * CCE Error flags.
 */
अटल काष्ठा flag_table cce_err_status_flags[] = अणु
/* 0*/	FLAG_ENTRY0("CceCsrParityErr",
		CCE_ERR_STATUS_CCE_CSR_PARITY_ERR_SMASK),
/* 1*/	FLAG_ENTRY0("CceCsrReadBadAddrErr",
		CCE_ERR_STATUS_CCE_CSR_READ_BAD_ADDR_ERR_SMASK),
/* 2*/	FLAG_ENTRY0("CceCsrWriteBadAddrErr",
		CCE_ERR_STATUS_CCE_CSR_WRITE_BAD_ADDR_ERR_SMASK),
/* 3*/	FLAG_ENTRY0("CceTrgtAsyncFifoParityErr",
		CCE_ERR_STATUS_CCE_TRGT_ASYNC_FIFO_PARITY_ERR_SMASK),
/* 4*/	FLAG_ENTRY0("CceTrgtAccessErr",
		CCE_ERR_STATUS_CCE_TRGT_ACCESS_ERR_SMASK),
/* 5*/	FLAG_ENTRY0("CceRspdDataParityErr",
		CCE_ERR_STATUS_CCE_RSPD_DATA_PARITY_ERR_SMASK),
/* 6*/	FLAG_ENTRY0("CceCli0AsyncFifoParityErr",
		CCE_ERR_STATUS_CCE_CLI0_ASYNC_FIFO_PARITY_ERR_SMASK),
/* 7*/	FLAG_ENTRY0("CceCsrCfgBusParityErr",
		CCE_ERR_STATUS_CCE_CSR_CFG_BUS_PARITY_ERR_SMASK),
/* 8*/	FLAG_ENTRY0("CceCli2AsyncFifoParityErr",
		CCE_ERR_STATUS_CCE_CLI2_ASYNC_FIFO_PARITY_ERR_SMASK),
/* 9*/	FLAG_ENTRY0("CceCli1AsyncFifoPioCrdtParityErr",
	    CCE_ERR_STATUS_CCE_CLI1_ASYNC_FIFO_PIO_CRDT_PARITY_ERR_SMASK),
/*10*/	FLAG_ENTRY0("CceCli1AsyncFifoPioCrdtParityErr",
	    CCE_ERR_STATUS_CCE_CLI1_ASYNC_FIFO_SDMA_HD_PARITY_ERR_SMASK),
/*11*/	FLAG_ENTRY0("CceCli1AsyncFifoRxdmaParityError",
	    CCE_ERR_STATUS_CCE_CLI1_ASYNC_FIFO_RXDMA_PARITY_ERROR_SMASK),
/*12*/	FLAG_ENTRY0("CceCli1AsyncFifoDbgParityError",
		CCE_ERR_STATUS_CCE_CLI1_ASYNC_FIFO_DBG_PARITY_ERROR_SMASK),
/*13*/	FLAG_ENTRY0("PcicRetryMemCorErr",
		CCE_ERR_STATUS_PCIC_RETRY_MEM_COR_ERR_SMASK),
/*14*/	FLAG_ENTRY0("PcicRetryMemCorErr",
		CCE_ERR_STATUS_PCIC_RETRY_SOT_MEM_COR_ERR_SMASK),
/*15*/	FLAG_ENTRY0("PcicPostHdQCorErr",
		CCE_ERR_STATUS_PCIC_POST_HD_QCOR_ERR_SMASK),
/*16*/	FLAG_ENTRY0("PcicPostHdQCorErr",
		CCE_ERR_STATUS_PCIC_POST_DAT_QCOR_ERR_SMASK),
/*17*/	FLAG_ENTRY0("PcicPostHdQCorErr",
		CCE_ERR_STATUS_PCIC_CPL_HD_QCOR_ERR_SMASK),
/*18*/	FLAG_ENTRY0("PcicCplDatQCorErr",
		CCE_ERR_STATUS_PCIC_CPL_DAT_QCOR_ERR_SMASK),
/*19*/	FLAG_ENTRY0("PcicNPostHQParityErr",
		CCE_ERR_STATUS_PCIC_NPOST_HQ_PARITY_ERR_SMASK),
/*20*/	FLAG_ENTRY0("PcicNPostDatQParityErr",
		CCE_ERR_STATUS_PCIC_NPOST_DAT_QPARITY_ERR_SMASK),
/*21*/	FLAG_ENTRY0("PcicRetryMemUncErr",
		CCE_ERR_STATUS_PCIC_RETRY_MEM_UNC_ERR_SMASK),
/*22*/	FLAG_ENTRY0("PcicRetrySotMemUncErr",
		CCE_ERR_STATUS_PCIC_RETRY_SOT_MEM_UNC_ERR_SMASK),
/*23*/	FLAG_ENTRY0("PcicPostHdQUncErr",
		CCE_ERR_STATUS_PCIC_POST_HD_QUNC_ERR_SMASK),
/*24*/	FLAG_ENTRY0("PcicPostDatQUncErr",
		CCE_ERR_STATUS_PCIC_POST_DAT_QUNC_ERR_SMASK),
/*25*/	FLAG_ENTRY0("PcicCplHdQUncErr",
		CCE_ERR_STATUS_PCIC_CPL_HD_QUNC_ERR_SMASK),
/*26*/	FLAG_ENTRY0("PcicCplDatQUncErr",
		CCE_ERR_STATUS_PCIC_CPL_DAT_QUNC_ERR_SMASK),
/*27*/	FLAG_ENTRY0("PcicTransmitFrontParityErr",
		CCE_ERR_STATUS_PCIC_TRANSMIT_FRONT_PARITY_ERR_SMASK),
/*28*/	FLAG_ENTRY0("PcicTransmitBackParityErr",
		CCE_ERR_STATUS_PCIC_TRANSMIT_BACK_PARITY_ERR_SMASK),
/*29*/	FLAG_ENTRY0("PcicReceiveParityErr",
		CCE_ERR_STATUS_PCIC_RECEIVE_PARITY_ERR_SMASK),
/*30*/	FLAG_ENTRY0("CceTrgtCplTimeoutErr",
		CCE_ERR_STATUS_CCE_TRGT_CPL_TIMEOUT_ERR_SMASK),
/*31*/	FLAG_ENTRY0("LATriggered",
		CCE_ERR_STATUS_LA_TRIGGERED_SMASK),
/*32*/	FLAG_ENTRY0("CceSegReadBadAddrErr",
		CCE_ERR_STATUS_CCE_SEG_READ_BAD_ADDR_ERR_SMASK),
/*33*/	FLAG_ENTRY0("CceSegWriteBadAddrErr",
		CCE_ERR_STATUS_CCE_SEG_WRITE_BAD_ADDR_ERR_SMASK),
/*34*/	FLAG_ENTRY0("CceRcplAsyncFifoParityErr",
		CCE_ERR_STATUS_CCE_RCPL_ASYNC_FIFO_PARITY_ERR_SMASK),
/*35*/	FLAG_ENTRY0("CceRxdmaConvFifoParityErr",
		CCE_ERR_STATUS_CCE_RXDMA_CONV_FIFO_PARITY_ERR_SMASK),
/*36*/	FLAG_ENTRY0("CceMsixTableCorErr",
		CCE_ERR_STATUS_CCE_MSIX_TABLE_COR_ERR_SMASK),
/*37*/	FLAG_ENTRY0("CceMsixTableUncErr",
		CCE_ERR_STATUS_CCE_MSIX_TABLE_UNC_ERR_SMASK),
/*38*/	FLAG_ENTRY0("CceIntMapCorErr",
		CCE_ERR_STATUS_CCE_INT_MAP_COR_ERR_SMASK),
/*39*/	FLAG_ENTRY0("CceIntMapUncErr",
		CCE_ERR_STATUS_CCE_INT_MAP_UNC_ERR_SMASK),
/*40*/	FLAG_ENTRY0("CceMsixCsrParityErr",
		CCE_ERR_STATUS_CCE_MSIX_CSR_PARITY_ERR_SMASK),
/*41-63 reserved*/
पूर्ण;

/*
 * Misc Error flags
 */
#घोषणा MES(text) MISC_ERR_STATUS_MISC_##text##_ERR_SMASK
अटल काष्ठा flag_table misc_err_status_flags[] = अणु
/* 0*/	FLAG_ENTRY0("CSR_PARITY", MES(CSR_PARITY)),
/* 1*/	FLAG_ENTRY0("CSR_READ_BAD_ADDR", MES(CSR_READ_BAD_ADDR)),
/* 2*/	FLAG_ENTRY0("CSR_WRITE_BAD_ADDR", MES(CSR_WRITE_BAD_ADDR)),
/* 3*/	FLAG_ENTRY0("SBUS_WRITE_FAILED", MES(SBUS_WRITE_FAILED)),
/* 4*/	FLAG_ENTRY0("KEY_MISMATCH", MES(KEY_MISMATCH)),
/* 5*/	FLAG_ENTRY0("FW_AUTH_FAILED", MES(FW_AUTH_FAILED)),
/* 6*/	FLAG_ENTRY0("EFUSE_CSR_PARITY", MES(EFUSE_CSR_PARITY)),
/* 7*/	FLAG_ENTRY0("EFUSE_READ_BAD_ADDR", MES(EFUSE_READ_BAD_ADDR)),
/* 8*/	FLAG_ENTRY0("EFUSE_WRITE", MES(EFUSE_WRITE)),
/* 9*/	FLAG_ENTRY0("EFUSE_DONE_PARITY", MES(EFUSE_DONE_PARITY)),
/*10*/	FLAG_ENTRY0("INVALID_EEP_CMD", MES(INVALID_EEP_CMD)),
/*11*/	FLAG_ENTRY0("MBIST_FAIL", MES(MBIST_FAIL)),
/*12*/	FLAG_ENTRY0("PLL_LOCK_FAIL", MES(PLL_LOCK_FAIL))
पूर्ण;

/*
 * TXE PIO Error flags and consequences
 */
अटल काष्ठा flag_table pio_err_status_flags[] = अणु
/* 0*/	FLAG_ENTRY("PioWriteBadCtxt",
	SEC_WRITE_DROPPED,
	SEND_PIO_ERR_STATUS_PIO_WRITE_BAD_CTXT_ERR_SMASK),
/* 1*/	FLAG_ENTRY("PioWriteAddrParity",
	SEC_SPC_FREEZE,
	SEND_PIO_ERR_STATUS_PIO_WRITE_ADDR_PARITY_ERR_SMASK),
/* 2*/	FLAG_ENTRY("PioCsrParity",
	SEC_SPC_FREEZE,
	SEND_PIO_ERR_STATUS_PIO_CSR_PARITY_ERR_SMASK),
/* 3*/	FLAG_ENTRY("PioSbMemFifo0",
	SEC_SPC_FREEZE,
	SEND_PIO_ERR_STATUS_PIO_SB_MEM_FIFO0_ERR_SMASK),
/* 4*/	FLAG_ENTRY("PioSbMemFifo1",
	SEC_SPC_FREEZE,
	SEND_PIO_ERR_STATUS_PIO_SB_MEM_FIFO1_ERR_SMASK),
/* 5*/	FLAG_ENTRY("PioPccFifoParity",
	SEC_SPC_FREEZE,
	SEND_PIO_ERR_STATUS_PIO_PCC_FIFO_PARITY_ERR_SMASK),
/* 6*/	FLAG_ENTRY("PioPecFifoParity",
	SEC_SPC_FREEZE,
	SEND_PIO_ERR_STATUS_PIO_PEC_FIFO_PARITY_ERR_SMASK),
/* 7*/	FLAG_ENTRY("PioSbrdctlCrrelParity",
	SEC_SPC_FREEZE,
	SEND_PIO_ERR_STATUS_PIO_SBRDCTL_CRREL_PARITY_ERR_SMASK),
/* 8*/	FLAG_ENTRY("PioSbrdctrlCrrelFifoParity",
	SEC_SPC_FREEZE,
	SEND_PIO_ERR_STATUS_PIO_SBRDCTRL_CRREL_FIFO_PARITY_ERR_SMASK),
/* 9*/	FLAG_ENTRY("PioPktEvictFifoParityErr",
	SEC_SPC_FREEZE,
	SEND_PIO_ERR_STATUS_PIO_PKT_EVICT_FIFO_PARITY_ERR_SMASK),
/*10*/	FLAG_ENTRY("PioSmPktResetParity",
	SEC_SPC_FREEZE,
	SEND_PIO_ERR_STATUS_PIO_SM_PKT_RESET_PARITY_ERR_SMASK),
/*11*/	FLAG_ENTRY("PioVlLenMemBank0Unc",
	SEC_SPC_FREEZE,
	SEND_PIO_ERR_STATUS_PIO_VL_LEN_MEM_BANK0_UNC_ERR_SMASK),
/*12*/	FLAG_ENTRY("PioVlLenMemBank1Unc",
	SEC_SPC_FREEZE,
	SEND_PIO_ERR_STATUS_PIO_VL_LEN_MEM_BANK1_UNC_ERR_SMASK),
/*13*/	FLAG_ENTRY("PioVlLenMemBank0Cor",
	0,
	SEND_PIO_ERR_STATUS_PIO_VL_LEN_MEM_BANK0_COR_ERR_SMASK),
/*14*/	FLAG_ENTRY("PioVlLenMemBank1Cor",
	0,
	SEND_PIO_ERR_STATUS_PIO_VL_LEN_MEM_BANK1_COR_ERR_SMASK),
/*15*/	FLAG_ENTRY("PioCreditRetFifoParity",
	SEC_SPC_FREEZE,
	SEND_PIO_ERR_STATUS_PIO_CREDIT_RET_FIFO_PARITY_ERR_SMASK),
/*16*/	FLAG_ENTRY("PioPpmcPblFifo",
	SEC_SPC_FREEZE,
	SEND_PIO_ERR_STATUS_PIO_PPMC_PBL_FIFO_ERR_SMASK),
/*17*/	FLAG_ENTRY("PioInitSmIn",
	0,
	SEND_PIO_ERR_STATUS_PIO_INIT_SM_IN_ERR_SMASK),
/*18*/	FLAG_ENTRY("PioPktEvictSmOrArbSm",
	SEC_SPC_FREEZE,
	SEND_PIO_ERR_STATUS_PIO_PKT_EVICT_SM_OR_ARB_SM_ERR_SMASK),
/*19*/	FLAG_ENTRY("PioHostAddrMemUnc",
	SEC_SPC_FREEZE,
	SEND_PIO_ERR_STATUS_PIO_HOST_ADDR_MEM_UNC_ERR_SMASK),
/*20*/	FLAG_ENTRY("PioHostAddrMemCor",
	0,
	SEND_PIO_ERR_STATUS_PIO_HOST_ADDR_MEM_COR_ERR_SMASK),
/*21*/	FLAG_ENTRY("PioWriteDataParity",
	SEC_SPC_FREEZE,
	SEND_PIO_ERR_STATUS_PIO_WRITE_DATA_PARITY_ERR_SMASK),
/*22*/	FLAG_ENTRY("PioStateMachine",
	SEC_SPC_FREEZE,
	SEND_PIO_ERR_STATUS_PIO_STATE_MACHINE_ERR_SMASK),
/*23*/	FLAG_ENTRY("PioWriteQwValidParity",
	SEC_WRITE_DROPPED | SEC_SPC_FREEZE,
	SEND_PIO_ERR_STATUS_PIO_WRITE_QW_VALID_PARITY_ERR_SMASK),
/*24*/	FLAG_ENTRY("PioBlockQwCountParity",
	SEC_WRITE_DROPPED | SEC_SPC_FREEZE,
	SEND_PIO_ERR_STATUS_PIO_BLOCK_QW_COUNT_PARITY_ERR_SMASK),
/*25*/	FLAG_ENTRY("PioVlfVlLenParity",
	SEC_SPC_FREEZE,
	SEND_PIO_ERR_STATUS_PIO_VLF_VL_LEN_PARITY_ERR_SMASK),
/*26*/	FLAG_ENTRY("PioVlfSopParity",
	SEC_SPC_FREEZE,
	SEND_PIO_ERR_STATUS_PIO_VLF_SOP_PARITY_ERR_SMASK),
/*27*/	FLAG_ENTRY("PioVlFifoParity",
	SEC_SPC_FREEZE,
	SEND_PIO_ERR_STATUS_PIO_VL_FIFO_PARITY_ERR_SMASK),
/*28*/	FLAG_ENTRY("PioPpmcBqcMemParity",
	SEC_SPC_FREEZE,
	SEND_PIO_ERR_STATUS_PIO_PPMC_BQC_MEM_PARITY_ERR_SMASK),
/*29*/	FLAG_ENTRY("PioPpmcSopLen",
	SEC_SPC_FREEZE,
	SEND_PIO_ERR_STATUS_PIO_PPMC_SOP_LEN_ERR_SMASK),
/*30-31 reserved*/
/*32*/	FLAG_ENTRY("PioCurrentFreeCntParity",
	SEC_SPC_FREEZE,
	SEND_PIO_ERR_STATUS_PIO_CURRENT_FREE_CNT_PARITY_ERR_SMASK),
/*33*/	FLAG_ENTRY("PioLastReturnedCntParity",
	SEC_SPC_FREEZE,
	SEND_PIO_ERR_STATUS_PIO_LAST_RETURNED_CNT_PARITY_ERR_SMASK),
/*34*/	FLAG_ENTRY("PioPccSopHeadParity",
	SEC_SPC_FREEZE,
	SEND_PIO_ERR_STATUS_PIO_PCC_SOP_HEAD_PARITY_ERR_SMASK),
/*35*/	FLAG_ENTRY("PioPecSopHeadParityErr",
	SEC_SPC_FREEZE,
	SEND_PIO_ERR_STATUS_PIO_PEC_SOP_HEAD_PARITY_ERR_SMASK),
/*36-63 reserved*/
पूर्ण;

/* TXE PIO errors that cause an SPC मुक्तze */
#घोषणा ALL_PIO_FREEZE_ERR \
	(SEND_PIO_ERR_STATUS_PIO_WRITE_ADDR_PARITY_ERR_SMASK \
	| SEND_PIO_ERR_STATUS_PIO_CSR_PARITY_ERR_SMASK \
	| SEND_PIO_ERR_STATUS_PIO_SB_MEM_FIFO0_ERR_SMASK \
	| SEND_PIO_ERR_STATUS_PIO_SB_MEM_FIFO1_ERR_SMASK \
	| SEND_PIO_ERR_STATUS_PIO_PCC_FIFO_PARITY_ERR_SMASK \
	| SEND_PIO_ERR_STATUS_PIO_PEC_FIFO_PARITY_ERR_SMASK \
	| SEND_PIO_ERR_STATUS_PIO_SBRDCTL_CRREL_PARITY_ERR_SMASK \
	| SEND_PIO_ERR_STATUS_PIO_SBRDCTRL_CRREL_FIFO_PARITY_ERR_SMASK \
	| SEND_PIO_ERR_STATUS_PIO_PKT_EVICT_FIFO_PARITY_ERR_SMASK \
	| SEND_PIO_ERR_STATUS_PIO_SM_PKT_RESET_PARITY_ERR_SMASK \
	| SEND_PIO_ERR_STATUS_PIO_VL_LEN_MEM_BANK0_UNC_ERR_SMASK \
	| SEND_PIO_ERR_STATUS_PIO_VL_LEN_MEM_BANK1_UNC_ERR_SMASK \
	| SEND_PIO_ERR_STATUS_PIO_CREDIT_RET_FIFO_PARITY_ERR_SMASK \
	| SEND_PIO_ERR_STATUS_PIO_PPMC_PBL_FIFO_ERR_SMASK \
	| SEND_PIO_ERR_STATUS_PIO_PKT_EVICT_SM_OR_ARB_SM_ERR_SMASK \
	| SEND_PIO_ERR_STATUS_PIO_HOST_ADDR_MEM_UNC_ERR_SMASK \
	| SEND_PIO_ERR_STATUS_PIO_WRITE_DATA_PARITY_ERR_SMASK \
	| SEND_PIO_ERR_STATUS_PIO_STATE_MACHINE_ERR_SMASK \
	| SEND_PIO_ERR_STATUS_PIO_WRITE_QW_VALID_PARITY_ERR_SMASK \
	| SEND_PIO_ERR_STATUS_PIO_BLOCK_QW_COUNT_PARITY_ERR_SMASK \
	| SEND_PIO_ERR_STATUS_PIO_VLF_VL_LEN_PARITY_ERR_SMASK \
	| SEND_PIO_ERR_STATUS_PIO_VLF_SOP_PARITY_ERR_SMASK \
	| SEND_PIO_ERR_STATUS_PIO_VL_FIFO_PARITY_ERR_SMASK \
	| SEND_PIO_ERR_STATUS_PIO_PPMC_BQC_MEM_PARITY_ERR_SMASK \
	| SEND_PIO_ERR_STATUS_PIO_PPMC_SOP_LEN_ERR_SMASK \
	| SEND_PIO_ERR_STATUS_PIO_CURRENT_FREE_CNT_PARITY_ERR_SMASK \
	| SEND_PIO_ERR_STATUS_PIO_LAST_RETURNED_CNT_PARITY_ERR_SMASK \
	| SEND_PIO_ERR_STATUS_PIO_PCC_SOP_HEAD_PARITY_ERR_SMASK \
	| SEND_PIO_ERR_STATUS_PIO_PEC_SOP_HEAD_PARITY_ERR_SMASK)

/*
 * TXE SDMA Error flags
 */
अटल काष्ठा flag_table sdma_err_status_flags[] = अणु
/* 0*/	FLAG_ENTRY0("SDmaRpyTagErr",
		SEND_DMA_ERR_STATUS_SDMA_RPY_TAG_ERR_SMASK),
/* 1*/	FLAG_ENTRY0("SDmaCsrParityErr",
		SEND_DMA_ERR_STATUS_SDMA_CSR_PARITY_ERR_SMASK),
/* 2*/	FLAG_ENTRY0("SDmaPcieReqTrackingUncErr",
		SEND_DMA_ERR_STATUS_SDMA_PCIE_REQ_TRACKING_UNC_ERR_SMASK),
/* 3*/	FLAG_ENTRY0("SDmaPcieReqTrackingCorErr",
		SEND_DMA_ERR_STATUS_SDMA_PCIE_REQ_TRACKING_COR_ERR_SMASK),
/*04-63 reserved*/
पूर्ण;

/* TXE SDMA errors that cause an SPC मुक्तze */
#घोषणा ALL_SDMA_FREEZE_ERR  \
		(SEND_DMA_ERR_STATUS_SDMA_RPY_TAG_ERR_SMASK \
		| SEND_DMA_ERR_STATUS_SDMA_CSR_PARITY_ERR_SMASK \
		| SEND_DMA_ERR_STATUS_SDMA_PCIE_REQ_TRACKING_UNC_ERR_SMASK)

/* SendEgressErrInfo bits that correspond to a PortXmitDiscard counter */
#घोषणा PORT_DISCARD_EGRESS_ERRS \
	(SEND_EGRESS_ERR_INFO_TOO_LONG_IB_PACKET_ERR_SMASK \
	| SEND_EGRESS_ERR_INFO_VL_MAPPING_ERR_SMASK \
	| SEND_EGRESS_ERR_INFO_VL_ERR_SMASK)

/*
 * TXE Egress Error flags
 */
#घोषणा SEES(text) SEND_EGRESS_ERR_STATUS_##text##_ERR_SMASK
अटल काष्ठा flag_table egress_err_status_flags[] = अणु
/* 0*/	FLAG_ENTRY0("TxPktIntegrityMemCorErr", SEES(TX_PKT_INTEGRITY_MEM_COR)),
/* 1*/	FLAG_ENTRY0("TxPktIntegrityMemUncErr", SEES(TX_PKT_INTEGRITY_MEM_UNC)),
/* 2 reserved */
/* 3*/	FLAG_ENTRY0("TxEgressFifoUnderrunOrParityErr",
		SEES(TX_EGRESS_FIFO_UNDERRUN_OR_PARITY)),
/* 4*/	FLAG_ENTRY0("TxLinkdownErr", SEES(TX_LINKDOWN)),
/* 5*/	FLAG_ENTRY0("TxIncorrectLinkStateErr", SEES(TX_INCORRECT_LINK_STATE)),
/* 6 reserved */
/* 7*/	FLAG_ENTRY0("TxPioLaunchIntfParityErr",
		SEES(TX_PIO_LAUNCH_INTF_PARITY)),
/* 8*/	FLAG_ENTRY0("TxSdmaLaunchIntfParityErr",
		SEES(TX_SDMA_LAUNCH_INTF_PARITY)),
/* 9-10 reserved */
/*11*/	FLAG_ENTRY0("TxSbrdCtlStateMachineParityErr",
		SEES(TX_SBRD_CTL_STATE_MACHINE_PARITY)),
/*12*/	FLAG_ENTRY0("TxIllegalVLErr", SEES(TX_ILLEGAL_VL)),
/*13*/	FLAG_ENTRY0("TxLaunchCsrParityErr", SEES(TX_LAUNCH_CSR_PARITY)),
/*14*/	FLAG_ENTRY0("TxSbrdCtlCsrParityErr", SEES(TX_SBRD_CTL_CSR_PARITY)),
/*15*/	FLAG_ENTRY0("TxConfigParityErr", SEES(TX_CONFIG_PARITY)),
/*16*/	FLAG_ENTRY0("TxSdma0DisallowedPacketErr",
		SEES(TX_SDMA0_DISALLOWED_PACKET)),
/*17*/	FLAG_ENTRY0("TxSdma1DisallowedPacketErr",
		SEES(TX_SDMA1_DISALLOWED_PACKET)),
/*18*/	FLAG_ENTRY0("TxSdma2DisallowedPacketErr",
		SEES(TX_SDMA2_DISALLOWED_PACKET)),
/*19*/	FLAG_ENTRY0("TxSdma3DisallowedPacketErr",
		SEES(TX_SDMA3_DISALLOWED_PACKET)),
/*20*/	FLAG_ENTRY0("TxSdma4DisallowedPacketErr",
		SEES(TX_SDMA4_DISALLOWED_PACKET)),
/*21*/	FLAG_ENTRY0("TxSdma5DisallowedPacketErr",
		SEES(TX_SDMA5_DISALLOWED_PACKET)),
/*22*/	FLAG_ENTRY0("TxSdma6DisallowedPacketErr",
		SEES(TX_SDMA6_DISALLOWED_PACKET)),
/*23*/	FLAG_ENTRY0("TxSdma7DisallowedPacketErr",
		SEES(TX_SDMA7_DISALLOWED_PACKET)),
/*24*/	FLAG_ENTRY0("TxSdma8DisallowedPacketErr",
		SEES(TX_SDMA8_DISALLOWED_PACKET)),
/*25*/	FLAG_ENTRY0("TxSdma9DisallowedPacketErr",
		SEES(TX_SDMA9_DISALLOWED_PACKET)),
/*26*/	FLAG_ENTRY0("TxSdma10DisallowedPacketErr",
		SEES(TX_SDMA10_DISALLOWED_PACKET)),
/*27*/	FLAG_ENTRY0("TxSdma11DisallowedPacketErr",
		SEES(TX_SDMA11_DISALLOWED_PACKET)),
/*28*/	FLAG_ENTRY0("TxSdma12DisallowedPacketErr",
		SEES(TX_SDMA12_DISALLOWED_PACKET)),
/*29*/	FLAG_ENTRY0("TxSdma13DisallowedPacketErr",
		SEES(TX_SDMA13_DISALLOWED_PACKET)),
/*30*/	FLAG_ENTRY0("TxSdma14DisallowedPacketErr",
		SEES(TX_SDMA14_DISALLOWED_PACKET)),
/*31*/	FLAG_ENTRY0("TxSdma15DisallowedPacketErr",
		SEES(TX_SDMA15_DISALLOWED_PACKET)),
/*32*/	FLAG_ENTRY0("TxLaunchFifo0UncOrParityErr",
		SEES(TX_LAUNCH_FIFO0_UNC_OR_PARITY)),
/*33*/	FLAG_ENTRY0("TxLaunchFifo1UncOrParityErr",
		SEES(TX_LAUNCH_FIFO1_UNC_OR_PARITY)),
/*34*/	FLAG_ENTRY0("TxLaunchFifo2UncOrParityErr",
		SEES(TX_LAUNCH_FIFO2_UNC_OR_PARITY)),
/*35*/	FLAG_ENTRY0("TxLaunchFifo3UncOrParityErr",
		SEES(TX_LAUNCH_FIFO3_UNC_OR_PARITY)),
/*36*/	FLAG_ENTRY0("TxLaunchFifo4UncOrParityErr",
		SEES(TX_LAUNCH_FIFO4_UNC_OR_PARITY)),
/*37*/	FLAG_ENTRY0("TxLaunchFifo5UncOrParityErr",
		SEES(TX_LAUNCH_FIFO5_UNC_OR_PARITY)),
/*38*/	FLAG_ENTRY0("TxLaunchFifo6UncOrParityErr",
		SEES(TX_LAUNCH_FIFO6_UNC_OR_PARITY)),
/*39*/	FLAG_ENTRY0("TxLaunchFifo7UncOrParityErr",
		SEES(TX_LAUNCH_FIFO7_UNC_OR_PARITY)),
/*40*/	FLAG_ENTRY0("TxLaunchFifo8UncOrParityErr",
		SEES(TX_LAUNCH_FIFO8_UNC_OR_PARITY)),
/*41*/	FLAG_ENTRY0("TxCreditReturnParityErr", SEES(TX_CREDIT_RETURN_PARITY)),
/*42*/	FLAG_ENTRY0("TxSbHdrUncErr", SEES(TX_SB_HDR_UNC)),
/*43*/	FLAG_ENTRY0("TxReadSdmaMemoryUncErr", SEES(TX_READ_SDMA_MEMORY_UNC)),
/*44*/	FLAG_ENTRY0("TxReadPioMemoryUncErr", SEES(TX_READ_PIO_MEMORY_UNC)),
/*45*/	FLAG_ENTRY0("TxEgressFifoUncErr", SEES(TX_EGRESS_FIFO_UNC)),
/*46*/	FLAG_ENTRY0("TxHcrcInsertionErr", SEES(TX_HCRC_INSERTION)),
/*47*/	FLAG_ENTRY0("TxCreditReturnVLErr", SEES(TX_CREDIT_RETURN_VL)),
/*48*/	FLAG_ENTRY0("TxLaunchFifo0CorErr", SEES(TX_LAUNCH_FIFO0_COR)),
/*49*/	FLAG_ENTRY0("TxLaunchFifo1CorErr", SEES(TX_LAUNCH_FIFO1_COR)),
/*50*/	FLAG_ENTRY0("TxLaunchFifo2CorErr", SEES(TX_LAUNCH_FIFO2_COR)),
/*51*/	FLAG_ENTRY0("TxLaunchFifo3CorErr", SEES(TX_LAUNCH_FIFO3_COR)),
/*52*/	FLAG_ENTRY0("TxLaunchFifo4CorErr", SEES(TX_LAUNCH_FIFO4_COR)),
/*53*/	FLAG_ENTRY0("TxLaunchFifo5CorErr", SEES(TX_LAUNCH_FIFO5_COR)),
/*54*/	FLAG_ENTRY0("TxLaunchFifo6CorErr", SEES(TX_LAUNCH_FIFO6_COR)),
/*55*/	FLAG_ENTRY0("TxLaunchFifo7CorErr", SEES(TX_LAUNCH_FIFO7_COR)),
/*56*/	FLAG_ENTRY0("TxLaunchFifo8CorErr", SEES(TX_LAUNCH_FIFO8_COR)),
/*57*/	FLAG_ENTRY0("TxCreditOverrunErr", SEES(TX_CREDIT_OVERRUN)),
/*58*/	FLAG_ENTRY0("TxSbHdrCorErr", SEES(TX_SB_HDR_COR)),
/*59*/	FLAG_ENTRY0("TxReadSdmaMemoryCorErr", SEES(TX_READ_SDMA_MEMORY_COR)),
/*60*/	FLAG_ENTRY0("TxReadPioMemoryCorErr", SEES(TX_READ_PIO_MEMORY_COR)),
/*61*/	FLAG_ENTRY0("TxEgressFifoCorErr", SEES(TX_EGRESS_FIFO_COR)),
/*62*/	FLAG_ENTRY0("TxReadSdmaMemoryCsrUncErr",
		SEES(TX_READ_SDMA_MEMORY_CSR_UNC)),
/*63*/	FLAG_ENTRY0("TxReadPioMemoryCsrUncErr",
		SEES(TX_READ_PIO_MEMORY_CSR_UNC)),
पूर्ण;

/*
 * TXE Egress Error Info flags
 */
#घोषणा SEEI(text) SEND_EGRESS_ERR_INFO_##text##_ERR_SMASK
अटल काष्ठा flag_table egress_err_info_flags[] = अणु
/* 0*/	FLAG_ENTRY0("Reserved", 0ull),
/* 1*/	FLAG_ENTRY0("VLErr", SEEI(VL)),
/* 2*/	FLAG_ENTRY0("JobKeyErr", SEEI(JOB_KEY)),
/* 3*/	FLAG_ENTRY0("JobKeyErr", SEEI(JOB_KEY)),
/* 4*/	FLAG_ENTRY0("PartitionKeyErr", SEEI(PARTITION_KEY)),
/* 5*/	FLAG_ENTRY0("SLIDErr", SEEI(SLID)),
/* 6*/	FLAG_ENTRY0("OpcodeErr", SEEI(OPCODE)),
/* 7*/	FLAG_ENTRY0("VLMappingErr", SEEI(VL_MAPPING)),
/* 8*/	FLAG_ENTRY0("RawErr", SEEI(RAW)),
/* 9*/	FLAG_ENTRY0("RawIPv6Err", SEEI(RAW_IPV6)),
/*10*/	FLAG_ENTRY0("GRHErr", SEEI(GRH)),
/*11*/	FLAG_ENTRY0("BypassErr", SEEI(BYPASS)),
/*12*/	FLAG_ENTRY0("KDETHPacketsErr", SEEI(KDETH_PACKETS)),
/*13*/	FLAG_ENTRY0("NonKDETHPacketsErr", SEEI(NON_KDETH_PACKETS)),
/*14*/	FLAG_ENTRY0("TooSmallIBPacketsErr", SEEI(TOO_SMALL_IB_PACKETS)),
/*15*/	FLAG_ENTRY0("TooSmallBypassPacketsErr", SEEI(TOO_SMALL_BYPASS_PACKETS)),
/*16*/	FLAG_ENTRY0("PbcTestErr", SEEI(PBC_TEST)),
/*17*/	FLAG_ENTRY0("BadPktLenErr", SEEI(BAD_PKT_LEN)),
/*18*/	FLAG_ENTRY0("TooLongIBPacketErr", SEEI(TOO_LONG_IB_PACKET)),
/*19*/	FLAG_ENTRY0("TooLongBypassPacketsErr", SEEI(TOO_LONG_BYPASS_PACKETS)),
/*20*/	FLAG_ENTRY0("PbcStaticRateControlErr", SEEI(PBC_STATIC_RATE_CONTROL)),
/*21*/	FLAG_ENTRY0("BypassBadPktLenErr", SEEI(BAD_PKT_LEN)),
पूर्ण;

/* TXE Egress errors that cause an SPC मुक्तze */
#घोषणा ALL_TXE_EGRESS_FREEZE_ERR \
	(SEES(TX_EGRESS_FIFO_UNDERRUN_OR_PARITY) \
	| SEES(TX_PIO_LAUNCH_INTF_PARITY) \
	| SEES(TX_SDMA_LAUNCH_INTF_PARITY) \
	| SEES(TX_SBRD_CTL_STATE_MACHINE_PARITY) \
	| SEES(TX_LAUNCH_CSR_PARITY) \
	| SEES(TX_SBRD_CTL_CSR_PARITY) \
	| SEES(TX_CONFIG_PARITY) \
	| SEES(TX_LAUNCH_FIFO0_UNC_OR_PARITY) \
	| SEES(TX_LAUNCH_FIFO1_UNC_OR_PARITY) \
	| SEES(TX_LAUNCH_FIFO2_UNC_OR_PARITY) \
	| SEES(TX_LAUNCH_FIFO3_UNC_OR_PARITY) \
	| SEES(TX_LAUNCH_FIFO4_UNC_OR_PARITY) \
	| SEES(TX_LAUNCH_FIFO5_UNC_OR_PARITY) \
	| SEES(TX_LAUNCH_FIFO6_UNC_OR_PARITY) \
	| SEES(TX_LAUNCH_FIFO7_UNC_OR_PARITY) \
	| SEES(TX_LAUNCH_FIFO8_UNC_OR_PARITY) \
	| SEES(TX_CREDIT_RETURN_PARITY))

/*
 * TXE Send error flags
 */
#घोषणा SES(name) SEND_ERR_STATUS_SEND_##name##_ERR_SMASK
अटल काष्ठा flag_table send_err_status_flags[] = अणु
/* 0*/	FLAG_ENTRY0("SendCsrParityErr", SES(CSR_PARITY)),
/* 1*/	FLAG_ENTRY0("SendCsrReadBadAddrErr", SES(CSR_READ_BAD_ADDR)),
/* 2*/	FLAG_ENTRY0("SendCsrWriteBadAddrErr", SES(CSR_WRITE_BAD_ADDR))
पूर्ण;

/*
 * TXE Send Context Error flags and consequences
 */
अटल काष्ठा flag_table sc_err_status_flags[] = अणु
/* 0*/	FLAG_ENTRY("InconsistentSop",
		SEC_PACKET_DROPPED | SEC_SC_HALTED,
		SEND_CTXT_ERR_STATUS_PIO_INCONSISTENT_SOP_ERR_SMASK),
/* 1*/	FLAG_ENTRY("DisallowedPacket",
		SEC_PACKET_DROPPED | SEC_SC_HALTED,
		SEND_CTXT_ERR_STATUS_PIO_DISALLOWED_PACKET_ERR_SMASK),
/* 2*/	FLAG_ENTRY("WriteCrossesBoundary",
		SEC_WRITE_DROPPED | SEC_SC_HALTED,
		SEND_CTXT_ERR_STATUS_PIO_WRITE_CROSSES_BOUNDARY_ERR_SMASK),
/* 3*/	FLAG_ENTRY("WriteOverflow",
		SEC_WRITE_DROPPED | SEC_SC_HALTED,
		SEND_CTXT_ERR_STATUS_PIO_WRITE_OVERFLOW_ERR_SMASK),
/* 4*/	FLAG_ENTRY("WriteOutOfBounds",
		SEC_WRITE_DROPPED | SEC_SC_HALTED,
		SEND_CTXT_ERR_STATUS_PIO_WRITE_OUT_OF_BOUNDS_ERR_SMASK),
/* 5-63 reserved*/
पूर्ण;

/*
 * RXE Receive Error flags
 */
#घोषणा RXES(name) RCV_ERR_STATUS_RX_##name##_ERR_SMASK
अटल काष्ठा flag_table rxe_err_status_flags[] = अणु
/* 0*/	FLAG_ENTRY0("RxDmaCsrCorErr", RXES(DMA_CSR_COR)),
/* 1*/	FLAG_ENTRY0("RxDcIntfParityErr", RXES(DC_INTF_PARITY)),
/* 2*/	FLAG_ENTRY0("RxRcvHdrUncErr", RXES(RCV_HDR_UNC)),
/* 3*/	FLAG_ENTRY0("RxRcvHdrCorErr", RXES(RCV_HDR_COR)),
/* 4*/	FLAG_ENTRY0("RxRcvDataUncErr", RXES(RCV_DATA_UNC)),
/* 5*/	FLAG_ENTRY0("RxRcvDataCorErr", RXES(RCV_DATA_COR)),
/* 6*/	FLAG_ENTRY0("RxRcvQpMapTableUncErr", RXES(RCV_QP_MAP_TABLE_UNC)),
/* 7*/	FLAG_ENTRY0("RxRcvQpMapTableCorErr", RXES(RCV_QP_MAP_TABLE_COR)),
/* 8*/	FLAG_ENTRY0("RxRcvCsrParityErr", RXES(RCV_CSR_PARITY)),
/* 9*/	FLAG_ENTRY0("RxDcSopEopParityErr", RXES(DC_SOP_EOP_PARITY)),
/*10*/	FLAG_ENTRY0("RxDmaFlagUncErr", RXES(DMA_FLAG_UNC)),
/*11*/	FLAG_ENTRY0("RxDmaFlagCorErr", RXES(DMA_FLAG_COR)),
/*12*/	FLAG_ENTRY0("RxRcvFsmEncodingErr", RXES(RCV_FSM_ENCODING)),
/*13*/	FLAG_ENTRY0("RxRbufFreeListUncErr", RXES(RBUF_FREE_LIST_UNC)),
/*14*/	FLAG_ENTRY0("RxRbufFreeListCorErr", RXES(RBUF_FREE_LIST_COR)),
/*15*/	FLAG_ENTRY0("RxRbufLookupDesRegUncErr", RXES(RBUF_LOOKUP_DES_REG_UNC)),
/*16*/	FLAG_ENTRY0("RxRbufLookupDesRegUncCorErr",
		RXES(RBUF_LOOKUP_DES_REG_UNC_COR)),
/*17*/	FLAG_ENTRY0("RxRbufLookupDesUncErr", RXES(RBUF_LOOKUP_DES_UNC)),
/*18*/	FLAG_ENTRY0("RxRbufLookupDesCorErr", RXES(RBUF_LOOKUP_DES_COR)),
/*19*/	FLAG_ENTRY0("RxRbufBlockListReadUncErr",
		RXES(RBUF_BLOCK_LIST_READ_UNC)),
/*20*/	FLAG_ENTRY0("RxRbufBlockListReadCorErr",
		RXES(RBUF_BLOCK_LIST_READ_COR)),
/*21*/	FLAG_ENTRY0("RxRbufCsrQHeadBufNumParityErr",
		RXES(RBUF_CSR_QHEAD_BUF_NUM_PARITY)),
/*22*/	FLAG_ENTRY0("RxRbufCsrQEntCntParityErr",
		RXES(RBUF_CSR_QENT_CNT_PARITY)),
/*23*/	FLAG_ENTRY0("RxRbufCsrQNextBufParityErr",
		RXES(RBUF_CSR_QNEXT_BUF_PARITY)),
/*24*/	FLAG_ENTRY0("RxRbufCsrQVldBitParityErr",
		RXES(RBUF_CSR_QVLD_BIT_PARITY)),
/*25*/	FLAG_ENTRY0("RxRbufCsrQHdPtrParityErr", RXES(RBUF_CSR_QHD_PTR_PARITY)),
/*26*/	FLAG_ENTRY0("RxRbufCsrQTlPtrParityErr", RXES(RBUF_CSR_QTL_PTR_PARITY)),
/*27*/	FLAG_ENTRY0("RxRbufCsrQNumOfPktParityErr",
		RXES(RBUF_CSR_QNUM_OF_PKT_PARITY)),
/*28*/	FLAG_ENTRY0("RxRbufCsrQEOPDWParityErr", RXES(RBUF_CSR_QEOPDW_PARITY)),
/*29*/	FLAG_ENTRY0("RxRbufCtxIdParityErr", RXES(RBUF_CTX_ID_PARITY)),
/*30*/	FLAG_ENTRY0("RxRBufBadLookupErr", RXES(RBUF_BAD_LOOKUP)),
/*31*/	FLAG_ENTRY0("RxRbufFullErr", RXES(RBUF_FULL)),
/*32*/	FLAG_ENTRY0("RxRbufEmptyErr", RXES(RBUF_EMPTY)),
/*33*/	FLAG_ENTRY0("RxRbufFlRdAddrParityErr", RXES(RBUF_FL_RD_ADDR_PARITY)),
/*34*/	FLAG_ENTRY0("RxRbufFlWrAddrParityErr", RXES(RBUF_FL_WR_ADDR_PARITY)),
/*35*/	FLAG_ENTRY0("RxRbufFlInitdoneParityErr",
		RXES(RBUF_FL_INITDONE_PARITY)),
/*36*/	FLAG_ENTRY0("RxRbufFlInitWrAddrParityErr",
		RXES(RBUF_FL_INIT_WR_ADDR_PARITY)),
/*37*/	FLAG_ENTRY0("RxRbufNextFreeBufUncErr", RXES(RBUF_NEXT_FREE_BUF_UNC)),
/*38*/	FLAG_ENTRY0("RxRbufNextFreeBufCorErr", RXES(RBUF_NEXT_FREE_BUF_COR)),
/*39*/	FLAG_ENTRY0("RxLookupDesPart1UncErr", RXES(LOOKUP_DES_PART1_UNC)),
/*40*/	FLAG_ENTRY0("RxLookupDesPart1UncCorErr",
		RXES(LOOKUP_DES_PART1_UNC_COR)),
/*41*/	FLAG_ENTRY0("RxLookupDesPart2ParityErr",
		RXES(LOOKUP_DES_PART2_PARITY)),
/*42*/	FLAG_ENTRY0("RxLookupRcvArrayUncErr", RXES(LOOKUP_RCV_ARRAY_UNC)),
/*43*/	FLAG_ENTRY0("RxLookupRcvArrayCorErr", RXES(LOOKUP_RCV_ARRAY_COR)),
/*44*/	FLAG_ENTRY0("RxLookupCsrParityErr", RXES(LOOKUP_CSR_PARITY)),
/*45*/	FLAG_ENTRY0("RxHqIntrCsrParityErr", RXES(HQ_INTR_CSR_PARITY)),
/*46*/	FLAG_ENTRY0("RxHqIntrFsmErr", RXES(HQ_INTR_FSM)),
/*47*/	FLAG_ENTRY0("RxRbufDescPart1UncErr", RXES(RBUF_DESC_PART1_UNC)),
/*48*/	FLAG_ENTRY0("RxRbufDescPart1CorErr", RXES(RBUF_DESC_PART1_COR)),
/*49*/	FLAG_ENTRY0("RxRbufDescPart2UncErr", RXES(RBUF_DESC_PART2_UNC)),
/*50*/	FLAG_ENTRY0("RxRbufDescPart2CorErr", RXES(RBUF_DESC_PART2_COR)),
/*51*/	FLAG_ENTRY0("RxDmaHdrFifoRdUncErr", RXES(DMA_HDR_FIFO_RD_UNC)),
/*52*/	FLAG_ENTRY0("RxDmaHdrFifoRdCorErr", RXES(DMA_HDR_FIFO_RD_COR)),
/*53*/	FLAG_ENTRY0("RxDmaDataFifoRdUncErr", RXES(DMA_DATA_FIFO_RD_UNC)),
/*54*/	FLAG_ENTRY0("RxDmaDataFifoRdCorErr", RXES(DMA_DATA_FIFO_RD_COR)),
/*55*/	FLAG_ENTRY0("RxRbufDataUncErr", RXES(RBUF_DATA_UNC)),
/*56*/	FLAG_ENTRY0("RxRbufDataCorErr", RXES(RBUF_DATA_COR)),
/*57*/	FLAG_ENTRY0("RxDmaCsrParityErr", RXES(DMA_CSR_PARITY)),
/*58*/	FLAG_ENTRY0("RxDmaEqFsmEncodingErr", RXES(DMA_EQ_FSM_ENCODING)),
/*59*/	FLAG_ENTRY0("RxDmaDqFsmEncodingErr", RXES(DMA_DQ_FSM_ENCODING)),
/*60*/	FLAG_ENTRY0("RxDmaCsrUncErr", RXES(DMA_CSR_UNC)),
/*61*/	FLAG_ENTRY0("RxCsrReadBadAddrErr", RXES(CSR_READ_BAD_ADDR)),
/*62*/	FLAG_ENTRY0("RxCsrWriteBadAddrErr", RXES(CSR_WRITE_BAD_ADDR)),
/*63*/	FLAG_ENTRY0("RxCsrParityErr", RXES(CSR_PARITY))
पूर्ण;

/* RXE errors that will trigger an SPC मुक्तze */
#घोषणा ALL_RXE_FREEZE_ERR  \
	(RCV_ERR_STATUS_RX_RCV_QP_MAP_TABLE_UNC_ERR_SMASK \
	| RCV_ERR_STATUS_RX_RCV_CSR_PARITY_ERR_SMASK \
	| RCV_ERR_STATUS_RX_DMA_FLAG_UNC_ERR_SMASK \
	| RCV_ERR_STATUS_RX_RCV_FSM_ENCODING_ERR_SMASK \
	| RCV_ERR_STATUS_RX_RBUF_FREE_LIST_UNC_ERR_SMASK \
	| RCV_ERR_STATUS_RX_RBUF_LOOKUP_DES_REG_UNC_ERR_SMASK \
	| RCV_ERR_STATUS_RX_RBUF_LOOKUP_DES_REG_UNC_COR_ERR_SMASK \
	| RCV_ERR_STATUS_RX_RBUF_LOOKUP_DES_UNC_ERR_SMASK \
	| RCV_ERR_STATUS_RX_RBUF_BLOCK_LIST_READ_UNC_ERR_SMASK \
	| RCV_ERR_STATUS_RX_RBUF_CSR_QHEAD_BUF_NUM_PARITY_ERR_SMASK \
	| RCV_ERR_STATUS_RX_RBUF_CSR_QENT_CNT_PARITY_ERR_SMASK \
	| RCV_ERR_STATUS_RX_RBUF_CSR_QNEXT_BUF_PARITY_ERR_SMASK \
	| RCV_ERR_STATUS_RX_RBUF_CSR_QVLD_BIT_PARITY_ERR_SMASK \
	| RCV_ERR_STATUS_RX_RBUF_CSR_QHD_PTR_PARITY_ERR_SMASK \
	| RCV_ERR_STATUS_RX_RBUF_CSR_QTL_PTR_PARITY_ERR_SMASK \
	| RCV_ERR_STATUS_RX_RBUF_CSR_QNUM_OF_PKT_PARITY_ERR_SMASK \
	| RCV_ERR_STATUS_RX_RBUF_CSR_QEOPDW_PARITY_ERR_SMASK \
	| RCV_ERR_STATUS_RX_RBUF_CTX_ID_PARITY_ERR_SMASK \
	| RCV_ERR_STATUS_RX_RBUF_BAD_LOOKUP_ERR_SMASK \
	| RCV_ERR_STATUS_RX_RBUF_FULL_ERR_SMASK \
	| RCV_ERR_STATUS_RX_RBUF_EMPTY_ERR_SMASK \
	| RCV_ERR_STATUS_RX_RBUF_FL_RD_ADDR_PARITY_ERR_SMASK \
	| RCV_ERR_STATUS_RX_RBUF_FL_WR_ADDR_PARITY_ERR_SMASK \
	| RCV_ERR_STATUS_RX_RBUF_FL_INITDONE_PARITY_ERR_SMASK \
	| RCV_ERR_STATUS_RX_RBUF_FL_INIT_WR_ADDR_PARITY_ERR_SMASK \
	| RCV_ERR_STATUS_RX_RBUF_NEXT_FREE_BUF_UNC_ERR_SMASK \
	| RCV_ERR_STATUS_RX_LOOKUP_DES_PART1_UNC_ERR_SMASK \
	| RCV_ERR_STATUS_RX_LOOKUP_DES_PART1_UNC_COR_ERR_SMASK \
	| RCV_ERR_STATUS_RX_LOOKUP_DES_PART2_PARITY_ERR_SMASK \
	| RCV_ERR_STATUS_RX_LOOKUP_RCV_ARRAY_UNC_ERR_SMASK \
	| RCV_ERR_STATUS_RX_LOOKUP_CSR_PARITY_ERR_SMASK \
	| RCV_ERR_STATUS_RX_HQ_INTR_CSR_PARITY_ERR_SMASK \
	| RCV_ERR_STATUS_RX_HQ_INTR_FSM_ERR_SMASK \
	| RCV_ERR_STATUS_RX_RBUF_DESC_PART1_UNC_ERR_SMASK \
	| RCV_ERR_STATUS_RX_RBUF_DESC_PART1_COR_ERR_SMASK \
	| RCV_ERR_STATUS_RX_RBUF_DESC_PART2_UNC_ERR_SMASK \
	| RCV_ERR_STATUS_RX_DMA_HDR_FIFO_RD_UNC_ERR_SMASK \
	| RCV_ERR_STATUS_RX_DMA_DATA_FIFO_RD_UNC_ERR_SMASK \
	| RCV_ERR_STATUS_RX_RBUF_DATA_UNC_ERR_SMASK \
	| RCV_ERR_STATUS_RX_DMA_CSR_PARITY_ERR_SMASK \
	| RCV_ERR_STATUS_RX_DMA_EQ_FSM_ENCODING_ERR_SMASK \
	| RCV_ERR_STATUS_RX_DMA_DQ_FSM_ENCODING_ERR_SMASK \
	| RCV_ERR_STATUS_RX_DMA_CSR_UNC_ERR_SMASK \
	| RCV_ERR_STATUS_RX_CSR_PARITY_ERR_SMASK)

#घोषणा RXE_FREEZE_ABORT_MASK \
	(RCV_ERR_STATUS_RX_DMA_CSR_UNC_ERR_SMASK | \
	RCV_ERR_STATUS_RX_DMA_HDR_FIFO_RD_UNC_ERR_SMASK | \
	RCV_ERR_STATUS_RX_DMA_DATA_FIFO_RD_UNC_ERR_SMASK)

/*
 * DCC Error Flags
 */
#घोषणा DCCE(name) DCC_ERR_FLG_##name##_SMASK
अटल काष्ठा flag_table dcc_err_flags[] = अणु
	FLAG_ENTRY0("bad_l2_err", DCCE(BAD_L2_ERR)),
	FLAG_ENTRY0("bad_sc_err", DCCE(BAD_SC_ERR)),
	FLAG_ENTRY0("bad_mid_tail_err", DCCE(BAD_MID_TAIL_ERR)),
	FLAG_ENTRY0("bad_preemption_err", DCCE(BAD_PREEMPTION_ERR)),
	FLAG_ENTRY0("preemption_err", DCCE(PREEMPTION_ERR)),
	FLAG_ENTRY0("preemptionvl15_err", DCCE(PREEMPTIONVL15_ERR)),
	FLAG_ENTRY0("bad_vl_marker_err", DCCE(BAD_VL_MARKER_ERR)),
	FLAG_ENTRY0("bad_dlid_target_err", DCCE(BAD_DLID_TARGET_ERR)),
	FLAG_ENTRY0("bad_lver_err", DCCE(BAD_LVER_ERR)),
	FLAG_ENTRY0("uncorrectable_err", DCCE(UNCORRECTABLE_ERR)),
	FLAG_ENTRY0("bad_crdt_ack_err", DCCE(BAD_CRDT_ACK_ERR)),
	FLAG_ENTRY0("unsup_pkt_type", DCCE(UNSUP_PKT_TYPE)),
	FLAG_ENTRY0("bad_ctrl_flit_err", DCCE(BAD_CTRL_FLIT_ERR)),
	FLAG_ENTRY0("event_cntr_parity_err", DCCE(EVENT_CNTR_PARITY_ERR)),
	FLAG_ENTRY0("event_cntr_rollover_err", DCCE(EVENT_CNTR_ROLLOVER_ERR)),
	FLAG_ENTRY0("link_err", DCCE(LINK_ERR)),
	FLAG_ENTRY0("misc_cntr_rollover_err", DCCE(MISC_CNTR_ROLLOVER_ERR)),
	FLAG_ENTRY0("bad_ctrl_dist_err", DCCE(BAD_CTRL_DIST_ERR)),
	FLAG_ENTRY0("bad_tail_dist_err", DCCE(BAD_TAIL_DIST_ERR)),
	FLAG_ENTRY0("bad_head_dist_err", DCCE(BAD_HEAD_DIST_ERR)),
	FLAG_ENTRY0("nonvl15_state_err", DCCE(NONVL15_STATE_ERR)),
	FLAG_ENTRY0("vl15_multi_err", DCCE(VL15_MULTI_ERR)),
	FLAG_ENTRY0("bad_pkt_length_err", DCCE(BAD_PKT_LENGTH_ERR)),
	FLAG_ENTRY0("unsup_vl_err", DCCE(UNSUP_VL_ERR)),
	FLAG_ENTRY0("perm_nvl15_err", DCCE(PERM_NVL15_ERR)),
	FLAG_ENTRY0("slid_zero_err", DCCE(SLID_ZERO_ERR)),
	FLAG_ENTRY0("dlid_zero_err", DCCE(DLID_ZERO_ERR)),
	FLAG_ENTRY0("length_mtu_err", DCCE(LENGTH_MTU_ERR)),
	FLAG_ENTRY0("rx_early_drop_err", DCCE(RX_EARLY_DROP_ERR)),
	FLAG_ENTRY0("late_short_err", DCCE(LATE_SHORT_ERR)),
	FLAG_ENTRY0("late_long_err", DCCE(LATE_LONG_ERR)),
	FLAG_ENTRY0("late_ebp_err", DCCE(LATE_EBP_ERR)),
	FLAG_ENTRY0("fpe_tx_fifo_ovflw_err", DCCE(FPE_TX_FIFO_OVFLW_ERR)),
	FLAG_ENTRY0("fpe_tx_fifo_unflw_err", DCCE(FPE_TX_FIFO_UNFLW_ERR)),
	FLAG_ENTRY0("csr_access_blocked_host", DCCE(CSR_ACCESS_BLOCKED_HOST)),
	FLAG_ENTRY0("csr_access_blocked_uc", DCCE(CSR_ACCESS_BLOCKED_UC)),
	FLAG_ENTRY0("tx_ctrl_parity_err", DCCE(TX_CTRL_PARITY_ERR)),
	FLAG_ENTRY0("tx_ctrl_parity_mbe_err", DCCE(TX_CTRL_PARITY_MBE_ERR)),
	FLAG_ENTRY0("tx_sc_parity_err", DCCE(TX_SC_PARITY_ERR)),
	FLAG_ENTRY0("rx_ctrl_parity_mbe_err", DCCE(RX_CTRL_PARITY_MBE_ERR)),
	FLAG_ENTRY0("csr_parity_err", DCCE(CSR_PARITY_ERR)),
	FLAG_ENTRY0("csr_inval_addr", DCCE(CSR_INVAL_ADDR)),
	FLAG_ENTRY0("tx_byte_shft_parity_err", DCCE(TX_BYTE_SHFT_PARITY_ERR)),
	FLAG_ENTRY0("rx_byte_shft_parity_err", DCCE(RX_BYTE_SHFT_PARITY_ERR)),
	FLAG_ENTRY0("fmconfig_err", DCCE(FMCONFIG_ERR)),
	FLAG_ENTRY0("rcvport_err", DCCE(RCVPORT_ERR)),
पूर्ण;

/*
 * LCB error flags
 */
#घोषणा LCBE(name) DC_LCB_ERR_FLG_##name##_SMASK
अटल काष्ठा flag_table lcb_err_flags[] = अणु
/* 0*/	FLAG_ENTRY0("CSR_PARITY_ERR", LCBE(CSR_PARITY_ERR)),
/* 1*/	FLAG_ENTRY0("INVALID_CSR_ADDR", LCBE(INVALID_CSR_ADDR)),
/* 2*/	FLAG_ENTRY0("RST_FOR_FAILED_DESKEW", LCBE(RST_FOR_FAILED_DESKEW)),
/* 3*/	FLAG_ENTRY0("ALL_LNS_FAILED_REINIT_TEST",
		LCBE(ALL_LNS_FAILED_REINIT_TEST)),
/* 4*/	FLAG_ENTRY0("LOST_REINIT_STALL_OR_TOS", LCBE(LOST_REINIT_STALL_OR_TOS)),
/* 5*/	FLAG_ENTRY0("TX_LESS_THAN_FOUR_LNS", LCBE(TX_LESS_THAN_FOUR_LNS)),
/* 6*/	FLAG_ENTRY0("RX_LESS_THAN_FOUR_LNS", LCBE(RX_LESS_THAN_FOUR_LNS)),
/* 7*/	FLAG_ENTRY0("SEQ_CRC_ERR", LCBE(SEQ_CRC_ERR)),
/* 8*/	FLAG_ENTRY0("REINIT_FROM_PEER", LCBE(REINIT_FROM_PEER)),
/* 9*/	FLAG_ENTRY0("REINIT_FOR_LN_DEGRADE", LCBE(REINIT_FOR_LN_DEGRADE)),
/*10*/	FLAG_ENTRY0("CRC_ERR_CNT_HIT_LIMIT", LCBE(CRC_ERR_CNT_HIT_LIMIT)),
/*11*/	FLAG_ENTRY0("RCLK_STOPPED", LCBE(RCLK_STOPPED)),
/*12*/	FLAG_ENTRY0("UNEXPECTED_REPLAY_MARKER", LCBE(UNEXPECTED_REPLAY_MARKER)),
/*13*/	FLAG_ENTRY0("UNEXPECTED_ROUND_TRIP_MARKER",
		LCBE(UNEXPECTED_ROUND_TRIP_MARKER)),
/*14*/	FLAG_ENTRY0("ILLEGAL_NULL_LTP", LCBE(ILLEGAL_शून्य_LTP)),
/*15*/	FLAG_ENTRY0("ILLEGAL_FLIT_ENCODING", LCBE(ILLEGAL_FLIT_ENCODING)),
/*16*/	FLAG_ENTRY0("FLIT_INPUT_BUF_OFLW", LCBE(FLIT_INPUT_BUF_OFLW)),
/*17*/	FLAG_ENTRY0("VL_ACK_INPUT_BUF_OFLW", LCBE(VL_ACK_INPUT_BUF_OFLW)),
/*18*/	FLAG_ENTRY0("VL_ACK_INPUT_PARITY_ERR", LCBE(VL_ACK_INPUT_PARITY_ERR)),
/*19*/	FLAG_ENTRY0("VL_ACK_INPUT_WRONG_CRC_MODE",
		LCBE(VL_ACK_INPUT_WRONG_CRC_MODE)),
/*20*/	FLAG_ENTRY0("FLIT_INPUT_BUF_MBE", LCBE(FLIT_INPUT_BUF_MBE)),
/*21*/	FLAG_ENTRY0("FLIT_INPUT_BUF_SBE", LCBE(FLIT_INPUT_BUF_SBE)),
/*22*/	FLAG_ENTRY0("REPLAY_BUF_MBE", LCBE(REPLAY_BUF_MBE)),
/*23*/	FLAG_ENTRY0("REPLAY_BUF_SBE", LCBE(REPLAY_BUF_SBE)),
/*24*/	FLAG_ENTRY0("CREDIT_RETURN_FLIT_MBE", LCBE(CREDIT_RETURN_FLIT_MBE)),
/*25*/	FLAG_ENTRY0("RST_FOR_LINK_TIMEOUT", LCBE(RST_FOR_LINK_TIMEOUT)),
/*26*/	FLAG_ENTRY0("RST_FOR_INCOMPLT_RND_TRIP",
		LCBE(RST_FOR_INCOMPLT_RND_TRIP)),
/*27*/	FLAG_ENTRY0("HOLD_REINIT", LCBE(HOLD_REINIT)),
/*28*/	FLAG_ENTRY0("NEG_EDGE_LINK_TRANSFER_ACTIVE",
		LCBE(NEG_EDGE_LINK_TRANSFER_ACTIVE)),
/*29*/	FLAG_ENTRY0("REDUNDANT_FLIT_PARITY_ERR",
		LCBE(REDUNDANT_FLIT_PARITY_ERR))
पूर्ण;

/*
 * DC8051 Error Flags
 */
#घोषणा D8E(name) DC_DC8051_ERR_FLG_##name##_SMASK
अटल काष्ठा flag_table dc8051_err_flags[] = अणु
	FLAG_ENTRY0("SET_BY_8051", D8E(SET_BY_8051)),
	FLAG_ENTRY0("LOST_8051_HEART_BEAT", D8E(LOST_8051_HEART_BEAT)),
	FLAG_ENTRY0("CRAM_MBE", D8E(CRAM_MBE)),
	FLAG_ENTRY0("CRAM_SBE", D8E(CRAM_SBE)),
	FLAG_ENTRY0("DRAM_MBE", D8E(DRAM_MBE)),
	FLAG_ENTRY0("DRAM_SBE", D8E(DRAM_SBE)),
	FLAG_ENTRY0("IRAM_MBE", D8E(IRAM_MBE)),
	FLAG_ENTRY0("IRAM_SBE", D8E(IRAM_SBE)),
	FLAG_ENTRY0("UNMATCHED_SECURE_MSG_ACROSS_BCC_LANES",
		    D8E(UNMATCHED_SECURE_MSG_ACROSS_BCC_LANES)),
	FLAG_ENTRY0("INVALID_CSR_ADDR", D8E(INVALID_CSR_ADDR)),
पूर्ण;

/*
 * DC8051 Inक्रमmation Error flags
 *
 * Flags in DC8051_DBG_ERR_INFO_SET_BY_8051.ERROR field.
 */
अटल काष्ठा flag_table dc8051_info_err_flags[] = अणु
	FLAG_ENTRY0("Spico ROM check failed",  SPICO_ROM_FAILED),
	FLAG_ENTRY0("Unknown frame received",  UNKNOWN_FRAME),
	FLAG_ENTRY0("Target BER not met",      TARGET_BER_NOT_MET),
	FLAG_ENTRY0("Serdes internal loopback failure",
		    FAILED_SERDES_INTERNAL_LOOPBACK),
	FLAG_ENTRY0("Failed SerDes init",      FAILED_SERDES_INIT),
	FLAG_ENTRY0("Failed LNI(Polling)",     FAILED_LNI_POLLING),
	FLAG_ENTRY0("Failed LNI(Debounce)",    FAILED_LNI_DEBOUNCE),
	FLAG_ENTRY0("Failed LNI(EstbComm)",    FAILED_LNI_ESTBCOMM),
	FLAG_ENTRY0("Failed LNI(OptEq)",       FAILED_LNI_OPTEQ),
	FLAG_ENTRY0("Failed LNI(VerifyCap_1)", FAILED_LNI_VERIFY_CAP1),
	FLAG_ENTRY0("Failed LNI(VerifyCap_2)", FAILED_LNI_VERIFY_CAP2),
	FLAG_ENTRY0("Failed LNI(ConfigLT)",    FAILED_LNI_CONFIGLT),
	FLAG_ENTRY0("Host Handshake Timeout",  HOST_HANDSHAKE_TIMEOUT),
	FLAG_ENTRY0("External Device Request Timeout",
		    EXTERNAL_DEVICE_REQ_TIMEOUT),
पूर्ण;

/*
 * DC8051 Inक्रमmation Host Inक्रमmation flags
 *
 * Flags in DC8051_DBG_ERR_INFO_SET_BY_8051.HOST_MSG field.
 */
अटल काष्ठा flag_table dc8051_info_host_msg_flags[] = अणु
	FLAG_ENTRY0("Host request done", 0x0001),
	FLAG_ENTRY0("BC PWR_MGM message", 0x0002),
	FLAG_ENTRY0("BC SMA message", 0x0004),
	FLAG_ENTRY0("BC Unknown message (BCC)", 0x0008),
	FLAG_ENTRY0("BC Unknown message (LCB)", 0x0010),
	FLAG_ENTRY0("External device config request", 0x0020),
	FLAG_ENTRY0("VerifyCap all frames received", 0x0040),
	FLAG_ENTRY0("LinkUp achieved", 0x0080),
	FLAG_ENTRY0("Link going down", 0x0100),
	FLAG_ENTRY0("Link width downgraded", 0x0200),
पूर्ण;

अटल u32 encoded_size(u32 size);
अटल u32 chip_to_opa_lstate(काष्ठा hfi1_devdata *dd, u32 chip_lstate);
अटल पूर्णांक set_physical_link_state(काष्ठा hfi1_devdata *dd, u64 state);
अटल व्योम पढ़ो_vc_remote_phy(काष्ठा hfi1_devdata *dd, u8 *घातer_management,
			       u8 *continuous);
अटल व्योम पढ़ो_vc_remote_fabric(काष्ठा hfi1_devdata *dd, u8 *vau, u8 *z,
				  u8 *vcu, u16 *vl15buf, u8 *crc_sizes);
अटल व्योम पढ़ो_vc_remote_link_width(काष्ठा hfi1_devdata *dd,
				      u8 *remote_tx_rate, u16 *link_widths);
अटल व्योम पढ़ो_vc_local_link_mode(काष्ठा hfi1_devdata *dd, u8 *misc_bits,
				    u8 *flag_bits, u16 *link_widths);
अटल व्योम पढ़ो_remote_device_id(काष्ठा hfi1_devdata *dd, u16 *device_id,
				  u8 *device_rev);
अटल व्योम पढ़ो_local_lni(काष्ठा hfi1_devdata *dd, u8 *enable_lane_rx);
अटल पूर्णांक पढ़ो_tx_settings(काष्ठा hfi1_devdata *dd, u8 *enable_lane_tx,
			    u8 *tx_polarity_inversion,
			    u8 *rx_polarity_inversion, u8 *max_rate);
अटल व्योम handle_sdma_eng_err(काष्ठा hfi1_devdata *dd,
				अचिन्हित पूर्णांक context, u64 err_status);
अटल व्योम handle_qsfp_पूर्णांक(काष्ठा hfi1_devdata *dd, u32 source, u64 reg);
अटल व्योम handle_dcc_err(काष्ठा hfi1_devdata *dd,
			   अचिन्हित पूर्णांक context, u64 err_status);
अटल व्योम handle_lcb_err(काष्ठा hfi1_devdata *dd,
			   अचिन्हित पूर्णांक context, u64 err_status);
अटल व्योम handle_8051_पूर्णांकerrupt(काष्ठा hfi1_devdata *dd, u32 unused, u64 reg);
अटल व्योम handle_cce_err(काष्ठा hfi1_devdata *dd, u32 unused, u64 reg);
अटल व्योम handle_rxe_err(काष्ठा hfi1_devdata *dd, u32 unused, u64 reg);
अटल व्योम handle_misc_err(काष्ठा hfi1_devdata *dd, u32 unused, u64 reg);
अटल व्योम handle_pio_err(काष्ठा hfi1_devdata *dd, u32 unused, u64 reg);
अटल व्योम handle_sdma_err(काष्ठा hfi1_devdata *dd, u32 unused, u64 reg);
अटल व्योम handle_egress_err(काष्ठा hfi1_devdata *dd, u32 unused, u64 reg);
अटल व्योम handle_txe_err(काष्ठा hfi1_devdata *dd, u32 unused, u64 reg);
अटल व्योम set_partition_keys(काष्ठा hfi1_pportdata *ppd);
अटल स्थिर अक्षर *link_state_name(u32 state);
अटल स्थिर अक्षर *link_state_reason_name(काष्ठा hfi1_pportdata *ppd,
					  u32 state);
अटल पूर्णांक करो_8051_command(काष्ठा hfi1_devdata *dd, u32 type, u64 in_data,
			   u64 *out_data);
अटल पूर्णांक पढ़ो_idle_sma(काष्ठा hfi1_devdata *dd, u64 *data);
अटल पूर्णांक thermal_init(काष्ठा hfi1_devdata *dd);

अटल व्योम update_statusp(काष्ठा hfi1_pportdata *ppd, u32 state);
अटल पूर्णांक रुको_phys_link_offline_substates(काष्ठा hfi1_pportdata *ppd,
					    पूर्णांक msecs);
अटल पूर्णांक रुको_logical_linkstate(काष्ठा hfi1_pportdata *ppd, u32 state,
				  पूर्णांक msecs);
अटल व्योम log_state_transition(काष्ठा hfi1_pportdata *ppd, u32 state);
अटल व्योम log_physical_state(काष्ठा hfi1_pportdata *ppd, u32 state);
अटल पूर्णांक रुको_physical_linkstate(काष्ठा hfi1_pportdata *ppd, u32 state,
				   पूर्णांक msecs);
अटल पूर्णांक रुको_phys_link_out_of_offline(काष्ठा hfi1_pportdata *ppd,
					 पूर्णांक msecs);
अटल व्योम पढ़ो_planned_करोwn_reason_code(काष्ठा hfi1_devdata *dd, u8 *pdrrc);
अटल व्योम पढ़ो_link_करोwn_reason(काष्ठा hfi1_devdata *dd, u8 *ldr);
अटल व्योम handle_temp_err(काष्ठा hfi1_devdata *dd);
अटल व्योम dc_shutकरोwn(काष्ठा hfi1_devdata *dd);
अटल व्योम dc_start(काष्ठा hfi1_devdata *dd);
अटल पूर्णांक qos_rmt_entries(काष्ठा hfi1_devdata *dd, अचिन्हित पूर्णांक *mp,
			   अचिन्हित पूर्णांक *np);
अटल व्योम clear_full_mgmt_pkey(काष्ठा hfi1_pportdata *ppd);
अटल पूर्णांक रुको_link_transfer_active(काष्ठा hfi1_devdata *dd, पूर्णांक रुको_ms);
अटल व्योम clear_rsm_rule(काष्ठा hfi1_devdata *dd, u8 rule_index);
अटल व्योम update_xmit_counters(काष्ठा hfi1_pportdata *ppd, u16 link_width);

/*
 * Error पूर्णांकerrupt table entry.  This is used as input to the पूर्णांकerrupt
 * "clear down" routine used क्रम all second tier error पूर्णांकerrupt रेजिस्टर.
 * Second tier पूर्णांकerrupt रेजिस्टरs have a single bit representing them
 * in the top-level CceIntStatus.
 */
काष्ठा err_reg_info अणु
	u32 status;		/* status CSR offset */
	u32 clear;		/* clear CSR offset */
	u32 mask;		/* mask CSR offset */
	व्योम (*handler)(काष्ठा hfi1_devdata *dd, u32 source, u64 reg);
	स्थिर अक्षर *desc;
पूर्ण;

#घोषणा NUM_MISC_ERRS (IS_GENERAL_ERR_END + 1 - IS_GENERAL_ERR_START)
#घोषणा NUM_DC_ERRS (IS_DC_END + 1 - IS_DC_START)
#घोषणा NUM_VARIOUS (IS_VARIOUS_END + 1 - IS_VARIOUS_START)

/*
 * Helpers क्रम building HFI and DC error पूर्णांकerrupt table entries.  Dअगरferent
 * helpers are needed because of inconsistent रेजिस्टर names.
 */
#घोषणा EE(reg, handler, desc) \
	अणु reg##_STATUS, reg##_CLEAR, reg##_MASK, \
		handler, desc पूर्ण
#घोषणा DC_EE1(reg, handler, desc) \
	अणु reg##_FLG, reg##_FLG_CLR, reg##_FLG_EN, handler, desc पूर्ण
#घोषणा DC_EE2(reg, handler, desc) \
	अणु reg##_FLG, reg##_CLR, reg##_EN, handler, desc पूर्ण

/*
 * Table of the "misc" grouping of error पूर्णांकerrupts.  Each entry refers to
 * another रेजिस्टर containing more inक्रमmation.
 */
अटल स्थिर काष्ठा err_reg_info misc_errs[NUM_MISC_ERRS] = अणु
/* 0*/	EE(CCE_ERR,		handle_cce_err,    "CceErr"),
/* 1*/	EE(RCV_ERR,		handle_rxe_err,    "RxeErr"),
/* 2*/	EE(MISC_ERR,	handle_misc_err,   "MiscErr"),
/* 3*/	अणु 0, 0, 0, शून्य पूर्ण, /* reserved */
/* 4*/	EE(SEND_PIO_ERR,    handle_pio_err,    "PioErr"),
/* 5*/	EE(SEND_DMA_ERR,    handle_sdma_err,   "SDmaErr"),
/* 6*/	EE(SEND_EGRESS_ERR, handle_egress_err, "EgressErr"),
/* 7*/	EE(SEND_ERR,	handle_txe_err,    "TxeErr")
	/* the rest are reserved */
पूर्ण;

/*
 * Index पूर्णांकo the Various section of the पूर्णांकerrupt sources
 * corresponding to the Critical Temperature पूर्णांकerrupt.
 */
#घोषणा TCRIT_INT_SOURCE 4

/*
 * SDMA error पूर्णांकerrupt entry - refers to another रेजिस्टर containing more
 * inक्रमmation.
 */
अटल स्थिर काष्ठा err_reg_info sdma_eng_err =
	EE(SEND_DMA_ENG_ERR, handle_sdma_eng_err, "SDmaEngErr");

अटल स्थिर काष्ठा err_reg_info various_err[NUM_VARIOUS] = अणु
/* 0*/	अणु 0, 0, 0, शून्य पूर्ण, /* PbcInt */
/* 1*/	अणु 0, 0, 0, शून्य पूर्ण, /* GpioAssertInt */
/* 2*/	EE(ASIC_QSFP1,	handle_qsfp_पूर्णांक,	"QSFP1"),
/* 3*/	EE(ASIC_QSFP2,	handle_qsfp_पूर्णांक,	"QSFP2"),
/* 4*/	अणु 0, 0, 0, शून्य पूर्ण, /* TCritInt */
	/* rest are reserved */
पूर्ण;

/*
 * The DC encoding of mtu_cap क्रम 10K MTU in the DCC_CFG_PORT_CONFIG
 * रेजिस्टर can not be derived from the MTU value because 10K is not
 * a घातer of 2. Thereक्रमe, we need a स्थिरant. Everything अन्यथा can
 * be calculated.
 */
#घोषणा DCC_CFG_PORT_MTU_CAP_10240 7

/*
 * Table of the DC grouping of error पूर्णांकerrupts.  Each entry refers to
 * another रेजिस्टर containing more inक्रमmation.
 */
अटल स्थिर काष्ठा err_reg_info dc_errs[NUM_DC_ERRS] = अणु
/* 0*/	DC_EE1(DCC_ERR,		handle_dcc_err,	       "DCC Err"),
/* 1*/	DC_EE2(DC_LCB_ERR,	handle_lcb_err,	       "LCB Err"),
/* 2*/	DC_EE2(DC_DC8051_ERR,	handle_8051_पूर्णांकerrupt, "DC8051 Interrupt"),
/* 3*/	/* dc_lbm_पूर्णांक - special, see is_dc_पूर्णांक() */
	/* the rest are reserved */
पूर्ण;

काष्ठा cntr_entry अणु
	/*
	 * counter name
	 */
	अक्षर *name;

	/*
	 * csr to पढ़ो क्रम name (अगर applicable)
	 */
	u64 csr;

	/*
	 * offset पूर्णांकo dd or ppd to store the counter's value
	 */
	पूर्णांक offset;

	/*
	 * flags
	 */
	u8 flags;

	/*
	 * accessor क्रम stat element, context either dd or ppd
	 */
	u64 (*rw_cntr)(स्थिर काष्ठा cntr_entry *, व्योम *context, पूर्णांक vl,
		       पूर्णांक mode, u64 data);
पूर्ण;

#घोषणा C_RCV_HDR_OVF_FIRST C_RCV_HDR_OVF_0
#घोषणा C_RCV_HDR_OVF_LAST C_RCV_HDR_OVF_159

#घोषणा CNTR_ELEM(name, csr, offset, flags, accessor) \
अणु \
	name, \
	csr, \
	offset, \
	flags, \
	accessor \
पूर्ण

/* 32bit RXE */
#घोषणा RXE32_PORT_CNTR_ELEM(name, counter, flags) \
CNTR_ELEM(#name, \
	  (counter * 8 + RCV_COUNTER_ARRAY32), \
	  0, flags | CNTR_32BIT, \
	  port_access_u32_csr)

#घोषणा RXE32_DEV_CNTR_ELEM(name, counter, flags) \
CNTR_ELEM(#name, \
	  (counter * 8 + RCV_COUNTER_ARRAY32), \
	  0, flags | CNTR_32BIT, \
	  dev_access_u32_csr)

/* 64bit RXE */
#घोषणा RXE64_PORT_CNTR_ELEM(name, counter, flags) \
CNTR_ELEM(#name, \
	  (counter * 8 + RCV_COUNTER_ARRAY64), \
	  0, flags, \
	  port_access_u64_csr)

#घोषणा RXE64_DEV_CNTR_ELEM(name, counter, flags) \
CNTR_ELEM(#name, \
	  (counter * 8 + RCV_COUNTER_ARRAY64), \
	  0, flags, \
	  dev_access_u64_csr)

#घोषणा OVR_LBL(ctx) C_RCV_HDR_OVF_ ## ctx
#घोषणा OVR_ELM(ctx) \
CNTR_ELEM("RcvHdrOvr" #ctx, \
	  (RCV_HDR_OVFL_CNT + ctx * 0x100), \
	  0, CNTR_NORMAL, port_access_u64_csr)

/* 32bit TXE */
#घोषणा TXE32_PORT_CNTR_ELEM(name, counter, flags) \
CNTR_ELEM(#name, \
	  (counter * 8 + SEND_COUNTER_ARRAY32), \
	  0, flags | CNTR_32BIT, \
	  port_access_u32_csr)

/* 64bit TXE */
#घोषणा TXE64_PORT_CNTR_ELEM(name, counter, flags) \
CNTR_ELEM(#name, \
	  (counter * 8 + SEND_COUNTER_ARRAY64), \
	  0, flags, \
	  port_access_u64_csr)

# define TX64_DEV_CNTR_ELEM(name, counter, flags) \
CNTR_ELEM(#name,\
	  counter * 8 + SEND_COUNTER_ARRAY64, \
	  0, \
	  flags, \
	  dev_access_u64_csr)

/* CCE */
#घोषणा CCE_PERF_DEV_CNTR_ELEM(name, counter, flags) \
CNTR_ELEM(#name, \
	  (counter * 8 + CCE_COUNTER_ARRAY32), \
	  0, flags | CNTR_32BIT, \
	  dev_access_u32_csr)

#घोषणा CCE_INT_DEV_CNTR_ELEM(name, counter, flags) \
CNTR_ELEM(#name, \
	  (counter * 8 + CCE_INT_COUNTER_ARRAY32), \
	  0, flags | CNTR_32BIT, \
	  dev_access_u32_csr)

/* DC */
#घोषणा DC_PERF_CNTR(name, counter, flags) \
CNTR_ELEM(#name, \
	  counter, \
	  0, \
	  flags, \
	  dev_access_u64_csr)

#घोषणा DC_PERF_CNTR_LCB(name, counter, flags) \
CNTR_ELEM(#name, \
	  counter, \
	  0, \
	  flags, \
	  dc_access_lcb_cntr)

/* ibp counters */
#घोषणा SW_IBP_CNTR(name, cntr) \
CNTR_ELEM(#name, \
	  0, \
	  0, \
	  CNTR_SYNTH, \
	  access_ibp_##cntr)

/**
 * hfi1_addr_from_offset - वापस addr क्रम पढ़ोq/ग_लिखोq
 * @dd: the dd device
 * @offset: the offset of the CSR within bar0
 *
 * This routine selects the appropriate base address
 * based on the indicated offset.
 */
अटल अंतरभूत व्योम __iomem *hfi1_addr_from_offset(
	स्थिर काष्ठा hfi1_devdata *dd,
	u32 offset)
अणु
	अगर (offset >= dd->base2_start)
		वापस dd->kregbase2 + (offset - dd->base2_start);
	वापस dd->kregbase1 + offset;
पूर्ण

/**
 * पढ़ो_csr - पढ़ो CSR at the indicated offset
 * @dd: the dd device
 * @offset: the offset of the CSR within bar0
 *
 * Return: the value पढ़ो or all FF's अगर there
 * is no mapping
 */
u64 पढ़ो_csr(स्थिर काष्ठा hfi1_devdata *dd, u32 offset)
अणु
	अगर (dd->flags & HFI1_PRESENT)
		वापस पढ़ोq(hfi1_addr_from_offset(dd, offset));
	वापस -1;
पूर्ण

/**
 * ग_लिखो_csr - ग_लिखो CSR at the indicated offset
 * @dd: the dd device
 * @offset: the offset of the CSR within bar0
 * @value: value to ग_लिखो
 */
व्योम ग_लिखो_csr(स्थिर काष्ठा hfi1_devdata *dd, u32 offset, u64 value)
अणु
	अगर (dd->flags & HFI1_PRESENT) अणु
		व्योम __iomem *base = hfi1_addr_from_offset(dd, offset);

		/* aव्योम ग_लिखो to RcvArray */
		अगर (WARN_ON(offset >= RCV_ARRAY && offset < dd->base2_start))
			वापस;
		ग_लिखोq(value, base);
	पूर्ण
पूर्ण

/**
 * get_csr_addr - वापस te iomem address क्रम offset
 * @dd: the dd device
 * @offset: the offset of the CSR within bar0
 *
 * Return: The iomem address to use in subsequent
 * ग_लिखोq/पढ़ोq operations.
 */
व्योम __iomem *get_csr_addr(
	स्थिर काष्ठा hfi1_devdata *dd,
	u32 offset)
अणु
	अगर (dd->flags & HFI1_PRESENT)
		वापस hfi1_addr_from_offset(dd, offset);
	वापस शून्य;
पूर्ण

अटल अंतरभूत u64 पढ़ो_ग_लिखो_csr(स्थिर काष्ठा hfi1_devdata *dd, u32 csr,
				 पूर्णांक mode, u64 value)
अणु
	u64 ret;

	अगर (mode == CNTR_MODE_R) अणु
		ret = पढ़ो_csr(dd, csr);
	पूर्ण अन्यथा अगर (mode == CNTR_MODE_W) अणु
		ग_लिखो_csr(dd, csr, value);
		ret = value;
	पूर्ण अन्यथा अणु
		dd_dev_err(dd, "Invalid cntr register access mode");
		वापस 0;
	पूर्ण

	hfi1_cdbg(CNTR, "csr 0x%x val 0x%llx mode %d", csr, ret, mode);
	वापस ret;
पूर्ण

/* Dev Access */
अटल u64 dev_access_u32_csr(स्थिर काष्ठा cntr_entry *entry,
			      व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = context;
	u64 csr = entry->csr;

	अगर (entry->flags & CNTR_SDMA) अणु
		अगर (vl == CNTR_INVALID_VL)
			वापस 0;
		csr += 0x100 * vl;
	पूर्ण अन्यथा अणु
		अगर (vl != CNTR_INVALID_VL)
			वापस 0;
	पूर्ण
	वापस पढ़ो_ग_लिखो_csr(dd, csr, mode, data);
पूर्ण

अटल u64 access_sde_err_cnt(स्थिर काष्ठा cntr_entry *entry,
			      व्योम *context, पूर्णांक idx, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	अगर (dd->per_sdma && idx < dd->num_sdma)
		वापस dd->per_sdma[idx].err_cnt;
	वापस 0;
पूर्ण

अटल u64 access_sde_पूर्णांक_cnt(स्थिर काष्ठा cntr_entry *entry,
			      व्योम *context, पूर्णांक idx, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	अगर (dd->per_sdma && idx < dd->num_sdma)
		वापस dd->per_sdma[idx].sdma_पूर्णांक_cnt;
	वापस 0;
पूर्ण

अटल u64 access_sde_idle_पूर्णांक_cnt(स्थिर काष्ठा cntr_entry *entry,
				   व्योम *context, पूर्णांक idx, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	अगर (dd->per_sdma && idx < dd->num_sdma)
		वापस dd->per_sdma[idx].idle_पूर्णांक_cnt;
	वापस 0;
पूर्ण

अटल u64 access_sde_progress_पूर्णांक_cnt(स्थिर काष्ठा cntr_entry *entry,
				       व्योम *context, पूर्णांक idx, पूर्णांक mode,
				       u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	अगर (dd->per_sdma && idx < dd->num_sdma)
		वापस dd->per_sdma[idx].progress_पूर्णांक_cnt;
	वापस 0;
पूर्ण

अटल u64 dev_access_u64_csr(स्थिर काष्ठा cntr_entry *entry, व्योम *context,
			      पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = context;

	u64 val = 0;
	u64 csr = entry->csr;

	अगर (entry->flags & CNTR_VL) अणु
		अगर (vl == CNTR_INVALID_VL)
			वापस 0;
		csr += 8 * vl;
	पूर्ण अन्यथा अणु
		अगर (vl != CNTR_INVALID_VL)
			वापस 0;
	पूर्ण

	val = पढ़ो_ग_लिखो_csr(dd, csr, mode, data);
	वापस val;
पूर्ण

अटल u64 dc_access_lcb_cntr(स्थिर काष्ठा cntr_entry *entry, व्योम *context,
			      पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = context;
	u32 csr = entry->csr;
	पूर्णांक ret = 0;

	अगर (vl != CNTR_INVALID_VL)
		वापस 0;
	अगर (mode == CNTR_MODE_R)
		ret = पढ़ो_lcb_csr(dd, csr, &data);
	अन्यथा अगर (mode == CNTR_MODE_W)
		ret = ग_लिखो_lcb_csr(dd, csr, data);

	अगर (ret) अणु
		dd_dev_err(dd, "Could not acquire LCB for counter 0x%x", csr);
		वापस 0;
	पूर्ण

	hfi1_cdbg(CNTR, "csr 0x%x val 0x%llx mode %d", csr, data, mode);
	वापस data;
पूर्ण

/* Port Access */
अटल u64 port_access_u32_csr(स्थिर काष्ठा cntr_entry *entry, व्योम *context,
			       पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_pportdata *ppd = context;

	अगर (vl != CNTR_INVALID_VL)
		वापस 0;
	वापस पढ़ो_ग_लिखो_csr(ppd->dd, entry->csr, mode, data);
पूर्ण

अटल u64 port_access_u64_csr(स्थिर काष्ठा cntr_entry *entry,
			       व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_pportdata *ppd = context;
	u64 val;
	u64 csr = entry->csr;

	अगर (entry->flags & CNTR_VL) अणु
		अगर (vl == CNTR_INVALID_VL)
			वापस 0;
		csr += 8 * vl;
	पूर्ण अन्यथा अणु
		अगर (vl != CNTR_INVALID_VL)
			वापस 0;
	पूर्ण
	val = पढ़ो_ग_लिखो_csr(ppd->dd, csr, mode, data);
	वापस val;
पूर्ण

/* Software defined */
अटल अंतरभूत u64 पढ़ो_ग_लिखो_sw(काष्ठा hfi1_devdata *dd, u64 *cntr, पूर्णांक mode,
				u64 data)
अणु
	u64 ret;

	अगर (mode == CNTR_MODE_R) अणु
		ret = *cntr;
	पूर्ण अन्यथा अगर (mode == CNTR_MODE_W) अणु
		*cntr = data;
		ret = data;
	पूर्ण अन्यथा अणु
		dd_dev_err(dd, "Invalid cntr sw access mode");
		वापस 0;
	पूर्ण

	hfi1_cdbg(CNTR, "val 0x%llx mode %d", ret, mode);

	वापस ret;
पूर्ण

अटल u64 access_sw_link_dn_cnt(स्थिर काष्ठा cntr_entry *entry, व्योम *context,
				 पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_pportdata *ppd = context;

	अगर (vl != CNTR_INVALID_VL)
		वापस 0;
	वापस पढ़ो_ग_लिखो_sw(ppd->dd, &ppd->link_करोwned, mode, data);
पूर्ण

अटल u64 access_sw_link_up_cnt(स्थिर काष्ठा cntr_entry *entry, व्योम *context,
				 पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_pportdata *ppd = context;

	अगर (vl != CNTR_INVALID_VL)
		वापस 0;
	वापस पढ़ो_ग_लिखो_sw(ppd->dd, &ppd->link_up, mode, data);
पूर्ण

अटल u64 access_sw_unknown_frame_cnt(स्थिर काष्ठा cntr_entry *entry,
				       व्योम *context, पूर्णांक vl, पूर्णांक mode,
				       u64 data)
अणु
	काष्ठा hfi1_pportdata *ppd = (काष्ठा hfi1_pportdata *)context;

	अगर (vl != CNTR_INVALID_VL)
		वापस 0;
	वापस पढ़ो_ग_लिखो_sw(ppd->dd, &ppd->unknown_frame_count, mode, data);
पूर्ण

अटल u64 access_sw_xmit_discards(स्थिर काष्ठा cntr_entry *entry,
				   व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_pportdata *ppd = (काष्ठा hfi1_pportdata *)context;
	u64 zero = 0;
	u64 *counter;

	अगर (vl == CNTR_INVALID_VL)
		counter = &ppd->port_xmit_discards;
	अन्यथा अगर (vl >= 0 && vl < C_VL_COUNT)
		counter = &ppd->port_xmit_discards_vl[vl];
	अन्यथा
		counter = &zero;

	वापस पढ़ो_ग_लिखो_sw(ppd->dd, counter, mode, data);
पूर्ण

अटल u64 access_xmit_स्थिरraपूर्णांक_errs(स्थिर काष्ठा cntr_entry *entry,
				       व्योम *context, पूर्णांक vl, पूर्णांक mode,
				       u64 data)
अणु
	काष्ठा hfi1_pportdata *ppd = context;

	अगर (vl != CNTR_INVALID_VL)
		वापस 0;

	वापस पढ़ो_ग_लिखो_sw(ppd->dd, &ppd->port_xmit_स्थिरraपूर्णांक_errors,
			     mode, data);
पूर्ण

अटल u64 access_rcv_स्थिरraपूर्णांक_errs(स्थिर काष्ठा cntr_entry *entry,
				      व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_pportdata *ppd = context;

	अगर (vl != CNTR_INVALID_VL)
		वापस 0;

	वापस पढ़ो_ग_लिखो_sw(ppd->dd, &ppd->port_rcv_स्थिरraपूर्णांक_errors,
			     mode, data);
पूर्ण

u64 get_all_cpu_total(u64 __percpu *cntr)
अणु
	पूर्णांक cpu;
	u64 counter = 0;

	क्रम_each_possible_cpu(cpu)
		counter += *per_cpu_ptr(cntr, cpu);
	वापस counter;
पूर्ण

अटल u64 पढ़ो_ग_लिखो_cpu(काष्ठा hfi1_devdata *dd, u64 *z_val,
			  u64 __percpu *cntr,
			  पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	u64 ret = 0;

	अगर (vl != CNTR_INVALID_VL)
		वापस 0;

	अगर (mode == CNTR_MODE_R) अणु
		ret = get_all_cpu_total(cntr) - *z_val;
	पूर्ण अन्यथा अगर (mode == CNTR_MODE_W) अणु
		/* A ग_लिखो can only zero the counter */
		अगर (data == 0)
			*z_val = get_all_cpu_total(cntr);
		अन्यथा
			dd_dev_err(dd, "Per CPU cntrs can only be zeroed");
	पूर्ण अन्यथा अणु
		dd_dev_err(dd, "Invalid cntr sw cpu access mode");
		वापस 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल u64 access_sw_cpu_पूर्णांकr(स्थिर काष्ठा cntr_entry *entry,
			      व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = context;

	वापस पढ़ो_ग_लिखो_cpu(dd, &dd->z_पूर्णांक_counter, dd->पूर्णांक_counter, vl,
			      mode, data);
पूर्ण

अटल u64 access_sw_cpu_rcv_limit(स्थिर काष्ठा cntr_entry *entry,
				   व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = context;

	वापस पढ़ो_ग_लिखो_cpu(dd, &dd->z_rcv_limit, dd->rcv_limit, vl,
			      mode, data);
पूर्ण

अटल u64 access_sw_pio_रुको(स्थिर काष्ठा cntr_entry *entry,
			      व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = context;

	वापस dd->verbs_dev.n_pioरुको;
पूर्ण

अटल u64 access_sw_pio_drain(स्थिर काष्ठा cntr_entry *entry,
			       व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->verbs_dev.n_piodrain;
पूर्ण

अटल u64 access_sw_ctx0_seq_drop(स्थिर काष्ठा cntr_entry *entry,
				   व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = context;

	वापस dd->ctx0_seq_drop;
पूर्ण

अटल u64 access_sw_vtx_रुको(स्थिर काष्ठा cntr_entry *entry,
			      व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = context;

	वापस dd->verbs_dev.n_txरुको;
पूर्ण

अटल u64 access_sw_kmem_रुको(स्थिर काष्ठा cntr_entry *entry,
			       व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = context;

	वापस dd->verbs_dev.n_kmem_रुको;
पूर्ण

अटल u64 access_sw_send_schedule(स्थिर काष्ठा cntr_entry *entry,
				   व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस पढ़ो_ग_लिखो_cpu(dd, &dd->z_send_schedule, dd->send_schedule, vl,
			      mode, data);
पूर्ण

/* Software counters क्रम the error status bits within MISC_ERR_STATUS */
अटल u64 access_misc_pll_lock_fail_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					     व्योम *context, पूर्णांक vl, पूर्णांक mode,
					     u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->misc_err_status_cnt[12];
पूर्ण

अटल u64 access_misc_mbist_fail_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					  व्योम *context, पूर्णांक vl, पूर्णांक mode,
					  u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->misc_err_status_cnt[11];
पूर्ण

अटल u64 access_misc_invalid_eep_cmd_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					       व्योम *context, पूर्णांक vl, पूर्णांक mode,
					       u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->misc_err_status_cnt[10];
पूर्ण

अटल u64 access_misc_efuse_करोne_parity_err_cnt(स्थिर काष्ठा cntr_entry *entry,
						 व्योम *context, पूर्णांक vl,
						 पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->misc_err_status_cnt[9];
पूर्ण

अटल u64 access_misc_efuse_ग_लिखो_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					   व्योम *context, पूर्णांक vl, पूर्णांक mode,
					   u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->misc_err_status_cnt[8];
पूर्ण

अटल u64 access_misc_efuse_पढ़ो_bad_addr_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->misc_err_status_cnt[7];
पूर्ण

अटल u64 access_misc_efuse_csr_parity_err_cnt(स्थिर काष्ठा cntr_entry *entry,
						व्योम *context, पूर्णांक vl,
						पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->misc_err_status_cnt[6];
पूर्ण

अटल u64 access_misc_fw_auth_failed_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					      व्योम *context, पूर्णांक vl, पूर्णांक mode,
					      u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->misc_err_status_cnt[5];
पूर्ण

अटल u64 access_misc_key_mismatch_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					    व्योम *context, पूर्णांक vl, पूर्णांक mode,
					    u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->misc_err_status_cnt[4];
पूर्ण

अटल u64 access_misc_sbus_ग_लिखो_failed_err_cnt(स्थिर काष्ठा cntr_entry *entry,
						 व्योम *context, पूर्णांक vl,
						 पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->misc_err_status_cnt[3];
पूर्ण

अटल u64 access_misc_csr_ग_लिखो_bad_addr_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->misc_err_status_cnt[2];
पूर्ण

अटल u64 access_misc_csr_पढ़ो_bad_addr_err_cnt(स्थिर काष्ठा cntr_entry *entry,
						 व्योम *context, पूर्णांक vl,
						 पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->misc_err_status_cnt[1];
पूर्ण

अटल u64 access_misc_csr_parity_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					  व्योम *context, पूर्णांक vl, पूर्णांक mode,
					  u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->misc_err_status_cnt[0];
पूर्ण

/*
 * Software counter क्रम the aggregate of
 * inभागidual CceErrStatus counters
 */
अटल u64 access_sw_cce_err_status_aggregated_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->sw_cce_err_status_aggregate;
पूर्ण

/*
 * Software counters corresponding to each of the
 * error status bits within CceErrStatus
 */
अटल u64 access_cce_msix_csr_parity_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					      व्योम *context, पूर्णांक vl, पूर्णांक mode,
					      u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->cce_err_status_cnt[40];
पूर्ण

अटल u64 access_cce_पूर्णांक_map_unc_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					  व्योम *context, पूर्णांक vl, पूर्णांक mode,
					  u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->cce_err_status_cnt[39];
पूर्ण

अटल u64 access_cce_पूर्णांक_map_cor_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					  व्योम *context, पूर्णांक vl, पूर्णांक mode,
					  u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->cce_err_status_cnt[38];
पूर्ण

अटल u64 access_cce_msix_table_unc_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					     व्योम *context, पूर्णांक vl, पूर्णांक mode,
					     u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->cce_err_status_cnt[37];
पूर्ण

अटल u64 access_cce_msix_table_cor_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					     व्योम *context, पूर्णांक vl, पूर्णांक mode,
					     u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->cce_err_status_cnt[36];
पूर्ण

अटल u64 access_cce_rxdma_conv_fअगरo_parity_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->cce_err_status_cnt[35];
पूर्ण

अटल u64 access_cce_rcpl_async_fअगरo_parity_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->cce_err_status_cnt[34];
पूर्ण

अटल u64 access_cce_seg_ग_लिखो_bad_addr_err_cnt(स्थिर काष्ठा cntr_entry *entry,
						 व्योम *context, पूर्णांक vl,
						 पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->cce_err_status_cnt[33];
पूर्ण

अटल u64 access_cce_seg_पढ़ो_bad_addr_err_cnt(स्थिर काष्ठा cntr_entry *entry,
						व्योम *context, पूर्णांक vl, पूर्णांक mode,
						u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->cce_err_status_cnt[32];
पूर्ण

अटल u64 access_la_triggered_cnt(स्थिर काष्ठा cntr_entry *entry,
				   व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->cce_err_status_cnt[31];
पूर्ण

अटल u64 access_cce_trgt_cpl_समयout_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					       व्योम *context, पूर्णांक vl, पूर्णांक mode,
					       u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->cce_err_status_cnt[30];
पूर्ण

अटल u64 access_pcic_receive_parity_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					      व्योम *context, पूर्णांक vl, पूर्णांक mode,
					      u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->cce_err_status_cnt[29];
पूर्ण

अटल u64 access_pcic_transmit_back_parity_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->cce_err_status_cnt[28];
पूर्ण

अटल u64 access_pcic_transmit_front_parity_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->cce_err_status_cnt[27];
पूर्ण

अटल u64 access_pcic_cpl_dat_q_unc_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					     व्योम *context, पूर्णांक vl, पूर्णांक mode,
					     u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->cce_err_status_cnt[26];
पूर्ण

अटल u64 access_pcic_cpl_hd_q_unc_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					    व्योम *context, पूर्णांक vl, पूर्णांक mode,
					    u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->cce_err_status_cnt[25];
पूर्ण

अटल u64 access_pcic_post_dat_q_unc_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					      व्योम *context, पूर्णांक vl, पूर्णांक mode,
					      u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->cce_err_status_cnt[24];
पूर्ण

अटल u64 access_pcic_post_hd_q_unc_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					     व्योम *context, पूर्णांक vl, पूर्णांक mode,
					     u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->cce_err_status_cnt[23];
पूर्ण

अटल u64 access_pcic_retry_sot_mem_unc_err_cnt(स्थिर काष्ठा cntr_entry *entry,
						 व्योम *context, पूर्णांक vl,
						 पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->cce_err_status_cnt[22];
पूर्ण

अटल u64 access_pcic_retry_mem_unc_err(स्थिर काष्ठा cntr_entry *entry,
					 व्योम *context, पूर्णांक vl, पूर्णांक mode,
					 u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->cce_err_status_cnt[21];
पूर्ण

अटल u64 access_pcic_n_post_dat_q_parity_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->cce_err_status_cnt[20];
पूर्ण

अटल u64 access_pcic_n_post_h_q_parity_err_cnt(स्थिर काष्ठा cntr_entry *entry,
						 व्योम *context, पूर्णांक vl,
						 पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->cce_err_status_cnt[19];
पूर्ण

अटल u64 access_pcic_cpl_dat_q_cor_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					     व्योम *context, पूर्णांक vl, पूर्णांक mode,
					     u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->cce_err_status_cnt[18];
पूर्ण

अटल u64 access_pcic_cpl_hd_q_cor_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					    व्योम *context, पूर्णांक vl, पूर्णांक mode,
					    u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->cce_err_status_cnt[17];
पूर्ण

अटल u64 access_pcic_post_dat_q_cor_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					      व्योम *context, पूर्णांक vl, पूर्णांक mode,
					      u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->cce_err_status_cnt[16];
पूर्ण

अटल u64 access_pcic_post_hd_q_cor_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					     व्योम *context, पूर्णांक vl, पूर्णांक mode,
					     u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->cce_err_status_cnt[15];
पूर्ण

अटल u64 access_pcic_retry_sot_mem_cor_err_cnt(स्थिर काष्ठा cntr_entry *entry,
						 व्योम *context, पूर्णांक vl,
						 पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->cce_err_status_cnt[14];
पूर्ण

अटल u64 access_pcic_retry_mem_cor_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					     व्योम *context, पूर्णांक vl, पूर्णांक mode,
					     u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->cce_err_status_cnt[13];
पूर्ण

अटल u64 access_cce_cli1_async_fअगरo_dbg_parity_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->cce_err_status_cnt[12];
पूर्ण

अटल u64 access_cce_cli1_async_fअगरo_rxdma_parity_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->cce_err_status_cnt[11];
पूर्ण

अटल u64 access_cce_cli1_async_fअगरo_sdma_hd_parity_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->cce_err_status_cnt[10];
पूर्ण

अटल u64 access_cce_cl1_async_fअगरo_pio_crdt_parity_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->cce_err_status_cnt[9];
पूर्ण

अटल u64 access_cce_cli2_async_fअगरo_parity_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->cce_err_status_cnt[8];
पूर्ण

अटल u64 access_cce_csr_cfg_bus_parity_err_cnt(स्थिर काष्ठा cntr_entry *entry,
						 व्योम *context, पूर्णांक vl,
						 पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->cce_err_status_cnt[7];
पूर्ण

अटल u64 access_cce_cli0_async_fअगरo_parity_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->cce_err_status_cnt[6];
पूर्ण

अटल u64 access_cce_rspd_data_parity_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					       व्योम *context, पूर्णांक vl, पूर्णांक mode,
					       u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->cce_err_status_cnt[5];
पूर्ण

अटल u64 access_cce_trgt_access_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					  व्योम *context, पूर्णांक vl, पूर्णांक mode,
					  u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->cce_err_status_cnt[4];
पूर्ण

अटल u64 access_cce_trgt_async_fअगरo_parity_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->cce_err_status_cnt[3];
पूर्ण

अटल u64 access_cce_csr_ग_लिखो_bad_addr_err_cnt(स्थिर काष्ठा cntr_entry *entry,
						 व्योम *context, पूर्णांक vl,
						 पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->cce_err_status_cnt[2];
पूर्ण

अटल u64 access_cce_csr_पढ़ो_bad_addr_err_cnt(स्थिर काष्ठा cntr_entry *entry,
						व्योम *context, पूर्णांक vl,
						पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->cce_err_status_cnt[1];
पूर्ण

अटल u64 access_ccs_csr_parity_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					 व्योम *context, पूर्णांक vl, पूर्णांक mode,
					 u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->cce_err_status_cnt[0];
पूर्ण

/*
 * Software counters corresponding to each of the
 * error status bits within RcvErrStatus
 */
अटल u64 access_rx_csr_parity_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					व्योम *context, पूर्णांक vl, पूर्णांक mode,
					u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[63];
पूर्ण

अटल u64 access_rx_csr_ग_लिखो_bad_addr_err_cnt(स्थिर काष्ठा cntr_entry *entry,
						व्योम *context, पूर्णांक vl,
						पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[62];
पूर्ण

अटल u64 access_rx_csr_पढ़ो_bad_addr_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					       व्योम *context, पूर्णांक vl, पूर्णांक mode,
					       u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[61];
पूर्ण

अटल u64 access_rx_dma_csr_unc_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					 व्योम *context, पूर्णांक vl, पूर्णांक mode,
					 u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[60];
पूर्ण

अटल u64 access_rx_dma_dq_fsm_encoding_err_cnt(स्थिर काष्ठा cntr_entry *entry,
						 व्योम *context, पूर्णांक vl,
						 पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[59];
पूर्ण

अटल u64 access_rx_dma_eq_fsm_encoding_err_cnt(स्थिर काष्ठा cntr_entry *entry,
						 व्योम *context, पूर्णांक vl,
						 पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[58];
पूर्ण

अटल u64 access_rx_dma_csr_parity_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					    व्योम *context, पूर्णांक vl, पूर्णांक mode,
					    u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[57];
पूर्ण

अटल u64 access_rx_rbuf_data_cor_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					   व्योम *context, पूर्णांक vl, पूर्णांक mode,
					   u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[56];
पूर्ण

अटल u64 access_rx_rbuf_data_unc_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					   व्योम *context, पूर्णांक vl, पूर्णांक mode,
					   u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[55];
पूर्ण

अटल u64 access_rx_dma_data_fअगरo_rd_cor_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[54];
पूर्ण

अटल u64 access_rx_dma_data_fअगरo_rd_unc_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[53];
पूर्ण

अटल u64 access_rx_dma_hdr_fअगरo_rd_cor_err_cnt(स्थिर काष्ठा cntr_entry *entry,
						 व्योम *context, पूर्णांक vl,
						 पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[52];
पूर्ण

अटल u64 access_rx_dma_hdr_fअगरo_rd_unc_err_cnt(स्थिर काष्ठा cntr_entry *entry,
						 व्योम *context, पूर्णांक vl,
						 पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[51];
पूर्ण

अटल u64 access_rx_rbuf_desc_part2_cor_err_cnt(स्थिर काष्ठा cntr_entry *entry,
						 व्योम *context, पूर्णांक vl,
						 पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[50];
पूर्ण

अटल u64 access_rx_rbuf_desc_part2_unc_err_cnt(स्थिर काष्ठा cntr_entry *entry,
						 व्योम *context, पूर्णांक vl,
						 पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[49];
पूर्ण

अटल u64 access_rx_rbuf_desc_part1_cor_err_cnt(स्थिर काष्ठा cntr_entry *entry,
						 व्योम *context, पूर्णांक vl,
						 पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[48];
पूर्ण

अटल u64 access_rx_rbuf_desc_part1_unc_err_cnt(स्थिर काष्ठा cntr_entry *entry,
						 व्योम *context, पूर्णांक vl,
						 पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[47];
पूर्ण

अटल u64 access_rx_hq_पूर्णांकr_fsm_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					 व्योम *context, पूर्णांक vl, पूर्णांक mode,
					 u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[46];
पूर्ण

अटल u64 access_rx_hq_पूर्णांकr_csr_parity_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[45];
पूर्ण

अटल u64 access_rx_lookup_csr_parity_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[44];
पूर्ण

अटल u64 access_rx_lookup_rcv_array_cor_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[43];
पूर्ण

अटल u64 access_rx_lookup_rcv_array_unc_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[42];
पूर्ण

अटल u64 access_rx_lookup_des_part2_parity_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[41];
पूर्ण

अटल u64 access_rx_lookup_des_part1_unc_cor_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[40];
पूर्ण

अटल u64 access_rx_lookup_des_part1_unc_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[39];
पूर्ण

अटल u64 access_rx_rbuf_next_मुक्त_buf_cor_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[38];
पूर्ण

अटल u64 access_rx_rbuf_next_मुक्त_buf_unc_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[37];
पूर्ण

अटल u64 access_rbuf_fl_init_wr_addr_parity_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[36];
पूर्ण

अटल u64 access_rx_rbuf_fl_initकरोne_parity_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[35];
पूर्ण

अटल u64 access_rx_rbuf_fl_ग_लिखो_addr_parity_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[34];
पूर्ण

अटल u64 access_rx_rbuf_fl_rd_addr_parity_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[33];
पूर्ण

अटल u64 access_rx_rbuf_empty_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					व्योम *context, पूर्णांक vl, पूर्णांक mode,
					u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[32];
पूर्ण

अटल u64 access_rx_rbuf_full_err_cnt(स्थिर काष्ठा cntr_entry *entry,
				       व्योम *context, पूर्णांक vl, पूर्णांक mode,
				       u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[31];
पूर्ण

अटल u64 access_rbuf_bad_lookup_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					  व्योम *context, पूर्णांक vl, पूर्णांक mode,
					  u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[30];
पूर्ण

अटल u64 access_rbuf_ctx_id_parity_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					     व्योम *context, पूर्णांक vl, पूर्णांक mode,
					     u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[29];
पूर्ण

अटल u64 access_rbuf_csr_qeopdw_parity_err_cnt(स्थिर काष्ठा cntr_entry *entry,
						 व्योम *context, पूर्णांक vl,
						 पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[28];
पूर्ण

अटल u64 access_rx_rbuf_csr_q_num_of_pkt_parity_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[27];
पूर्ण

अटल u64 access_rx_rbuf_csr_q_t1_ptr_parity_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[26];
पूर्ण

अटल u64 access_rx_rbuf_csr_q_hd_ptr_parity_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[25];
पूर्ण

अटल u64 access_rx_rbuf_csr_q_vld_bit_parity_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[24];
पूर्ण

अटल u64 access_rx_rbuf_csr_q_next_buf_parity_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[23];
पूर्ण

अटल u64 access_rx_rbuf_csr_q_ent_cnt_parity_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[22];
पूर्ण

अटल u64 access_rx_rbuf_csr_q_head_buf_num_parity_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[21];
पूर्ण

अटल u64 access_rx_rbuf_block_list_पढ़ो_cor_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[20];
पूर्ण

अटल u64 access_rx_rbuf_block_list_पढ़ो_unc_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[19];
पूर्ण

अटल u64 access_rx_rbuf_lookup_des_cor_err_cnt(स्थिर काष्ठा cntr_entry *entry,
						 व्योम *context, पूर्णांक vl,
						 पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[18];
पूर्ण

अटल u64 access_rx_rbuf_lookup_des_unc_err_cnt(स्थिर काष्ठा cntr_entry *entry,
						 व्योम *context, पूर्णांक vl,
						 पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[17];
पूर्ण

अटल u64 access_rx_rbuf_lookup_des_reg_unc_cor_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[16];
पूर्ण

अटल u64 access_rx_rbuf_lookup_des_reg_unc_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[15];
पूर्ण

अटल u64 access_rx_rbuf_मुक्त_list_cor_err_cnt(स्थिर काष्ठा cntr_entry *entry,
						व्योम *context, पूर्णांक vl,
						पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[14];
पूर्ण

अटल u64 access_rx_rbuf_मुक्त_list_unc_err_cnt(स्थिर काष्ठा cntr_entry *entry,
						व्योम *context, पूर्णांक vl,
						पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[13];
पूर्ण

अटल u64 access_rx_rcv_fsm_encoding_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					      व्योम *context, पूर्णांक vl, पूर्णांक mode,
					      u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[12];
पूर्ण

अटल u64 access_rx_dma_flag_cor_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					  व्योम *context, पूर्णांक vl, पूर्णांक mode,
					  u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[11];
पूर्ण

अटल u64 access_rx_dma_flag_unc_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					  व्योम *context, पूर्णांक vl, पूर्णांक mode,
					  u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[10];
पूर्ण

अटल u64 access_rx_dc_sop_eop_parity_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					       व्योम *context, पूर्णांक vl, पूर्णांक mode,
					       u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[9];
पूर्ण

अटल u64 access_rx_rcv_csr_parity_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					    व्योम *context, पूर्णांक vl, पूर्णांक mode,
					    u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[8];
पूर्ण

अटल u64 access_rx_rcv_qp_map_table_cor_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[7];
पूर्ण

अटल u64 access_rx_rcv_qp_map_table_unc_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[6];
पूर्ण

अटल u64 access_rx_rcv_data_cor_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					  व्योम *context, पूर्णांक vl, पूर्णांक mode,
					  u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[5];
पूर्ण

अटल u64 access_rx_rcv_data_unc_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					  व्योम *context, पूर्णांक vl, पूर्णांक mode,
					  u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[4];
पूर्ण

अटल u64 access_rx_rcv_hdr_cor_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					 व्योम *context, पूर्णांक vl, पूर्णांक mode,
					 u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[3];
पूर्ण

अटल u64 access_rx_rcv_hdr_unc_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					 व्योम *context, पूर्णांक vl, पूर्णांक mode,
					 u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[2];
पूर्ण

अटल u64 access_rx_dc_पूर्णांकf_parity_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					    व्योम *context, पूर्णांक vl, पूर्णांक mode,
					    u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[1];
पूर्ण

अटल u64 access_rx_dma_csr_cor_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					 व्योम *context, पूर्णांक vl, पूर्णांक mode,
					 u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->rcv_err_status_cnt[0];
पूर्ण

/*
 * Software counters corresponding to each of the
 * error status bits within SendPioErrStatus
 */
अटल u64 access_pio_pec_sop_head_parity_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_pio_err_status_cnt[35];
पूर्ण

अटल u64 access_pio_pcc_sop_head_parity_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_pio_err_status_cnt[34];
पूर्ण

अटल u64 access_pio_last_वापसed_cnt_parity_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_pio_err_status_cnt[33];
पूर्ण

अटल u64 access_pio_current_मुक्त_cnt_parity_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_pio_err_status_cnt[32];
पूर्ण

अटल u64 access_pio_reserved_31_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					  व्योम *context, पूर्णांक vl, पूर्णांक mode,
					  u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_pio_err_status_cnt[31];
पूर्ण

अटल u64 access_pio_reserved_30_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					  व्योम *context, पूर्णांक vl, पूर्णांक mode,
					  u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_pio_err_status_cnt[30];
पूर्ण

अटल u64 access_pio_ppmc_sop_len_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					   व्योम *context, पूर्णांक vl, पूर्णांक mode,
					   u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_pio_err_status_cnt[29];
पूर्ण

अटल u64 access_pio_ppmc_bqc_mem_parity_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_pio_err_status_cnt[28];
पूर्ण

अटल u64 access_pio_vl_fअगरo_parity_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					     व्योम *context, पूर्णांक vl, पूर्णांक mode,
					     u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_pio_err_status_cnt[27];
पूर्ण

अटल u64 access_pio_vlf_sop_parity_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					     व्योम *context, पूर्णांक vl, पूर्णांक mode,
					     u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_pio_err_status_cnt[26];
पूर्ण

अटल u64 access_pio_vlf_v1_len_parity_err_cnt(स्थिर काष्ठा cntr_entry *entry,
						व्योम *context, पूर्णांक vl,
						पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_pio_err_status_cnt[25];
पूर्ण

अटल u64 access_pio_block_qw_count_parity_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_pio_err_status_cnt[24];
पूर्ण

अटल u64 access_pio_ग_लिखो_qw_valid_parity_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_pio_err_status_cnt[23];
पूर्ण

अटल u64 access_pio_state_machine_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					    व्योम *context, पूर्णांक vl, पूर्णांक mode,
					    u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_pio_err_status_cnt[22];
पूर्ण

अटल u64 access_pio_ग_लिखो_data_parity_err_cnt(स्थिर काष्ठा cntr_entry *entry,
						व्योम *context, पूर्णांक vl,
						पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_pio_err_status_cnt[21];
पूर्ण

अटल u64 access_pio_host_addr_mem_cor_err_cnt(स्थिर काष्ठा cntr_entry *entry,
						व्योम *context, पूर्णांक vl,
						पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_pio_err_status_cnt[20];
पूर्ण

अटल u64 access_pio_host_addr_mem_unc_err_cnt(स्थिर काष्ठा cntr_entry *entry,
						व्योम *context, पूर्णांक vl,
						पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_pio_err_status_cnt[19];
पूर्ण

अटल u64 access_pio_pkt_evict_sm_or_arb_sm_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_pio_err_status_cnt[18];
पूर्ण

अटल u64 access_pio_init_sm_in_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					 व्योम *context, पूर्णांक vl, पूर्णांक mode,
					 u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_pio_err_status_cnt[17];
पूर्ण

अटल u64 access_pio_ppmc_pbl_fअगरo_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					    व्योम *context, पूर्णांक vl, पूर्णांक mode,
					    u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_pio_err_status_cnt[16];
पूर्ण

अटल u64 access_pio_credit_ret_fअगरo_parity_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_pio_err_status_cnt[15];
पूर्ण

अटल u64 access_pio_v1_len_mem_bank1_cor_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_pio_err_status_cnt[14];
पूर्ण

अटल u64 access_pio_v1_len_mem_bank0_cor_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_pio_err_status_cnt[13];
पूर्ण

अटल u64 access_pio_v1_len_mem_bank1_unc_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_pio_err_status_cnt[12];
पूर्ण

अटल u64 access_pio_v1_len_mem_bank0_unc_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_pio_err_status_cnt[11];
पूर्ण

अटल u64 access_pio_sm_pkt_reset_parity_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_pio_err_status_cnt[10];
पूर्ण

अटल u64 access_pio_pkt_evict_fअगरo_parity_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_pio_err_status_cnt[9];
पूर्ण

अटल u64 access_pio_sbrdctrl_crrel_fअगरo_parity_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_pio_err_status_cnt[8];
पूर्ण

अटल u64 access_pio_sbrdctl_crrel_parity_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_pio_err_status_cnt[7];
पूर्ण

अटल u64 access_pio_pec_fअगरo_parity_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					      व्योम *context, पूर्णांक vl, पूर्णांक mode,
					      u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_pio_err_status_cnt[6];
पूर्ण

अटल u64 access_pio_pcc_fअगरo_parity_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					      व्योम *context, पूर्णांक vl, पूर्णांक mode,
					      u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_pio_err_status_cnt[5];
पूर्ण

अटल u64 access_pio_sb_mem_fअगरo1_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					   व्योम *context, पूर्णांक vl, पूर्णांक mode,
					   u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_pio_err_status_cnt[4];
पूर्ण

अटल u64 access_pio_sb_mem_fअगरo0_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					   व्योम *context, पूर्णांक vl, पूर्णांक mode,
					   u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_pio_err_status_cnt[3];
पूर्ण

अटल u64 access_pio_csr_parity_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					 व्योम *context, पूर्णांक vl, पूर्णांक mode,
					 u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_pio_err_status_cnt[2];
पूर्ण

अटल u64 access_pio_ग_लिखो_addr_parity_err_cnt(स्थिर काष्ठा cntr_entry *entry,
						व्योम *context, पूर्णांक vl,
						पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_pio_err_status_cnt[1];
पूर्ण

अटल u64 access_pio_ग_लिखो_bad_ctxt_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					     व्योम *context, पूर्णांक vl, पूर्णांक mode,
					     u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_pio_err_status_cnt[0];
पूर्ण

/*
 * Software counters corresponding to each of the
 * error status bits within SendDmaErrStatus
 */
अटल u64 access_sdma_pcie_req_tracking_cor_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_dma_err_status_cnt[3];
पूर्ण

अटल u64 access_sdma_pcie_req_tracking_unc_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_dma_err_status_cnt[2];
पूर्ण

अटल u64 access_sdma_csr_parity_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					  व्योम *context, पूर्णांक vl, पूर्णांक mode,
					  u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_dma_err_status_cnt[1];
पूर्ण

अटल u64 access_sdma_rpy_tag_err_cnt(स्थिर काष्ठा cntr_entry *entry,
				       व्योम *context, पूर्णांक vl, पूर्णांक mode,
				       u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_dma_err_status_cnt[0];
पूर्ण

/*
 * Software counters corresponding to each of the
 * error status bits within SendEgressErrStatus
 */
अटल u64 access_tx_पढ़ो_pio_memory_csr_unc_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[63];
पूर्ण

अटल u64 access_tx_पढ़ो_sdma_memory_csr_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[62];
पूर्ण

अटल u64 access_tx_egress_fअगरo_cor_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					     व्योम *context, पूर्णांक vl, पूर्णांक mode,
					     u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[61];
पूर्ण

अटल u64 access_tx_पढ़ो_pio_memory_cor_err_cnt(स्थिर काष्ठा cntr_entry *entry,
						 व्योम *context, पूर्णांक vl,
						 पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[60];
पूर्ण

अटल u64 access_tx_पढ़ो_sdma_memory_cor_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[59];
पूर्ण

अटल u64 access_tx_sb_hdr_cor_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					व्योम *context, पूर्णांक vl, पूर्णांक mode,
					u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[58];
पूर्ण

अटल u64 access_tx_credit_overrun_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					    व्योम *context, पूर्णांक vl, पूर्णांक mode,
					    u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[57];
पूर्ण

अटल u64 access_tx_launch_fअगरo8_cor_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					      व्योम *context, पूर्णांक vl, पूर्णांक mode,
					      u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[56];
पूर्ण

अटल u64 access_tx_launch_fअगरo7_cor_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					      व्योम *context, पूर्णांक vl, पूर्णांक mode,
					      u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[55];
पूर्ण

अटल u64 access_tx_launch_fअगरo6_cor_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					      व्योम *context, पूर्णांक vl, पूर्णांक mode,
					      u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[54];
पूर्ण

अटल u64 access_tx_launch_fअगरo5_cor_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					      व्योम *context, पूर्णांक vl, पूर्णांक mode,
					      u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[53];
पूर्ण

अटल u64 access_tx_launch_fअगरo4_cor_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					      व्योम *context, पूर्णांक vl, पूर्णांक mode,
					      u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[52];
पूर्ण

अटल u64 access_tx_launch_fअगरo3_cor_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					      व्योम *context, पूर्णांक vl, पूर्णांक mode,
					      u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[51];
पूर्ण

अटल u64 access_tx_launch_fअगरo2_cor_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					      व्योम *context, पूर्णांक vl, पूर्णांक mode,
					      u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[50];
पूर्ण

अटल u64 access_tx_launch_fअगरo1_cor_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					      व्योम *context, पूर्णांक vl, पूर्णांक mode,
					      u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[49];
पूर्ण

अटल u64 access_tx_launch_fअगरo0_cor_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					      व्योम *context, पूर्णांक vl, पूर्णांक mode,
					      u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[48];
पूर्ण

अटल u64 access_tx_credit_वापस_vl_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					      व्योम *context, पूर्णांक vl, पूर्णांक mode,
					      u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[47];
पूर्ण

अटल u64 access_tx_hcrc_insertion_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					    व्योम *context, पूर्णांक vl, पूर्णांक mode,
					    u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[46];
पूर्ण

अटल u64 access_tx_egress_fअगरo_unc_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					     व्योम *context, पूर्णांक vl, पूर्णांक mode,
					     u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[45];
पूर्ण

अटल u64 access_tx_पढ़ो_pio_memory_unc_err_cnt(स्थिर काष्ठा cntr_entry *entry,
						 व्योम *context, पूर्णांक vl,
						 पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[44];
पूर्ण

अटल u64 access_tx_पढ़ो_sdma_memory_unc_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[43];
पूर्ण

अटल u64 access_tx_sb_hdr_unc_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					व्योम *context, पूर्णांक vl, पूर्णांक mode,
					u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[42];
पूर्ण

अटल u64 access_tx_credit_वापस_partiy_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[41];
पूर्ण

अटल u64 access_tx_launch_fअगरo8_unc_or_parity_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[40];
पूर्ण

अटल u64 access_tx_launch_fअगरo7_unc_or_parity_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[39];
पूर्ण

अटल u64 access_tx_launch_fअगरo6_unc_or_parity_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[38];
पूर्ण

अटल u64 access_tx_launch_fअगरo5_unc_or_parity_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[37];
पूर्ण

अटल u64 access_tx_launch_fअगरo4_unc_or_parity_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[36];
पूर्ण

अटल u64 access_tx_launch_fअगरo3_unc_or_parity_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[35];
पूर्ण

अटल u64 access_tx_launch_fअगरo2_unc_or_parity_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[34];
पूर्ण

अटल u64 access_tx_launch_fअगरo1_unc_or_parity_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[33];
पूर्ण

अटल u64 access_tx_launch_fअगरo0_unc_or_parity_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[32];
पूर्ण

अटल u64 access_tx_sdma15_disallowed_packet_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[31];
पूर्ण

अटल u64 access_tx_sdma14_disallowed_packet_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[30];
पूर्ण

अटल u64 access_tx_sdma13_disallowed_packet_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[29];
पूर्ण

अटल u64 access_tx_sdma12_disallowed_packet_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[28];
पूर्ण

अटल u64 access_tx_sdma11_disallowed_packet_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[27];
पूर्ण

अटल u64 access_tx_sdma10_disallowed_packet_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[26];
पूर्ण

अटल u64 access_tx_sdma9_disallowed_packet_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[25];
पूर्ण

अटल u64 access_tx_sdma8_disallowed_packet_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[24];
पूर्ण

अटल u64 access_tx_sdma7_disallowed_packet_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[23];
पूर्ण

अटल u64 access_tx_sdma6_disallowed_packet_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[22];
पूर्ण

अटल u64 access_tx_sdma5_disallowed_packet_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[21];
पूर्ण

अटल u64 access_tx_sdma4_disallowed_packet_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[20];
पूर्ण

अटल u64 access_tx_sdma3_disallowed_packet_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[19];
पूर्ण

अटल u64 access_tx_sdma2_disallowed_packet_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[18];
पूर्ण

अटल u64 access_tx_sdma1_disallowed_packet_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[17];
पूर्ण

अटल u64 access_tx_sdma0_disallowed_packet_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[16];
पूर्ण

अटल u64 access_tx_config_parity_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					   व्योम *context, पूर्णांक vl, पूर्णांक mode,
					   u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[15];
पूर्ण

अटल u64 access_tx_sbrd_ctl_csr_parity_err_cnt(स्थिर काष्ठा cntr_entry *entry,
						 व्योम *context, पूर्णांक vl,
						 पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[14];
पूर्ण

अटल u64 access_tx_launch_csr_parity_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					       व्योम *context, पूर्णांक vl, पूर्णांक mode,
					       u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[13];
पूर्ण

अटल u64 access_tx_illegal_vl_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					व्योम *context, पूर्णांक vl, पूर्णांक mode,
					u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[12];
पूर्ण

अटल u64 access_tx_sbrd_ctl_state_machine_parity_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[11];
पूर्ण

अटल u64 access_egress_reserved_10_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					     व्योम *context, पूर्णांक vl, पूर्णांक mode,
					     u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[10];
पूर्ण

अटल u64 access_egress_reserved_9_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					    व्योम *context, पूर्णांक vl, पूर्णांक mode,
					    u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[9];
पूर्ण

अटल u64 access_tx_sdma_launch_पूर्णांकf_parity_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[8];
पूर्ण

अटल u64 access_tx_pio_launch_पूर्णांकf_parity_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[7];
पूर्ण

अटल u64 access_egress_reserved_6_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					    व्योम *context, पूर्णांक vl, पूर्णांक mode,
					    u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[6];
पूर्ण

अटल u64 access_tx_incorrect_link_state_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[5];
पूर्ण

अटल u64 access_tx_linkकरोwn_err_cnt(स्थिर काष्ठा cntr_entry *entry,
				      व्योम *context, पूर्णांक vl, पूर्णांक mode,
				      u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[4];
पूर्ण

अटल u64 access_tx_egress_fअगरi_underrun_or_parity_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[3];
पूर्ण

अटल u64 access_egress_reserved_2_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					    व्योम *context, पूर्णांक vl, पूर्णांक mode,
					    u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[2];
पूर्ण

अटल u64 access_tx_pkt_पूर्णांकegrity_mem_unc_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[1];
पूर्ण

अटल u64 access_tx_pkt_पूर्णांकegrity_mem_cor_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_egress_err_status_cnt[0];
पूर्ण

/*
 * Software counters corresponding to each of the
 * error status bits within SendErrStatus
 */
अटल u64 access_send_csr_ग_लिखो_bad_addr_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_err_status_cnt[2];
पूर्ण

अटल u64 access_send_csr_पढ़ो_bad_addr_err_cnt(स्थिर काष्ठा cntr_entry *entry,
						 व्योम *context, पूर्णांक vl,
						 पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_err_status_cnt[1];
पूर्ण

अटल u64 access_send_csr_parity_cnt(स्थिर काष्ठा cntr_entry *entry,
				      व्योम *context, पूर्णांक vl, पूर्णांक mode,
				      u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->send_err_status_cnt[0];
पूर्ण

/*
 * Software counters corresponding to each of the
 * error status bits within SendCtxtErrStatus
 */
अटल u64 access_pio_ग_लिखो_out_of_bounds_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->sw_ctxt_err_status_cnt[4];
पूर्ण

अटल u64 access_pio_ग_लिखो_overflow_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					     व्योम *context, पूर्णांक vl, पूर्णांक mode,
					     u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->sw_ctxt_err_status_cnt[3];
पूर्ण

अटल u64 access_pio_ग_लिखो_crosses_boundary_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->sw_ctxt_err_status_cnt[2];
पूर्ण

अटल u64 access_pio_disallowed_packet_err_cnt(स्थिर काष्ठा cntr_entry *entry,
						व्योम *context, पूर्णांक vl,
						पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->sw_ctxt_err_status_cnt[1];
पूर्ण

अटल u64 access_pio_inconsistent_sop_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					       व्योम *context, पूर्णांक vl, पूर्णांक mode,
					       u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->sw_ctxt_err_status_cnt[0];
पूर्ण

/*
 * Software counters corresponding to each of the
 * error status bits within SendDmaEngErrStatus
 */
अटल u64 access_sdma_header_request_fअगरo_cor_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->sw_send_dma_eng_err_status_cnt[23];
पूर्ण

अटल u64 access_sdma_header_storage_cor_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->sw_send_dma_eng_err_status_cnt[22];
पूर्ण

अटल u64 access_sdma_packet_tracking_cor_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->sw_send_dma_eng_err_status_cnt[21];
पूर्ण

अटल u64 access_sdma_assembly_cor_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					    व्योम *context, पूर्णांक vl, पूर्णांक mode,
					    u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->sw_send_dma_eng_err_status_cnt[20];
पूर्ण

अटल u64 access_sdma_desc_table_cor_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					      व्योम *context, पूर्णांक vl, पूर्णांक mode,
					      u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->sw_send_dma_eng_err_status_cnt[19];
पूर्ण

अटल u64 access_sdma_header_request_fअगरo_unc_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->sw_send_dma_eng_err_status_cnt[18];
पूर्ण

अटल u64 access_sdma_header_storage_unc_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->sw_send_dma_eng_err_status_cnt[17];
पूर्ण

अटल u64 access_sdma_packet_tracking_unc_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->sw_send_dma_eng_err_status_cnt[16];
पूर्ण

अटल u64 access_sdma_assembly_unc_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					    व्योम *context, पूर्णांक vl, पूर्णांक mode,
					    u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->sw_send_dma_eng_err_status_cnt[15];
पूर्ण

अटल u64 access_sdma_desc_table_unc_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					      व्योम *context, पूर्णांक vl, पूर्णांक mode,
					      u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->sw_send_dma_eng_err_status_cnt[14];
पूर्ण

अटल u64 access_sdma_समयout_err_cnt(स्थिर काष्ठा cntr_entry *entry,
				       व्योम *context, पूर्णांक vl, पूर्णांक mode,
				       u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->sw_send_dma_eng_err_status_cnt[13];
पूर्ण

अटल u64 access_sdma_header_length_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					     व्योम *context, पूर्णांक vl, पूर्णांक mode,
					     u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->sw_send_dma_eng_err_status_cnt[12];
पूर्ण

अटल u64 access_sdma_header_address_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					      व्योम *context, पूर्णांक vl, पूर्णांक mode,
					      u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->sw_send_dma_eng_err_status_cnt[11];
पूर्ण

अटल u64 access_sdma_header_select_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					     व्योम *context, पूर्णांक vl, पूर्णांक mode,
					     u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->sw_send_dma_eng_err_status_cnt[10];
पूर्ण

अटल u64 access_sdma_reserved_9_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					  व्योम *context, पूर्णांक vl, पूर्णांक mode,
					  u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->sw_send_dma_eng_err_status_cnt[9];
पूर्ण

अटल u64 access_sdma_packet_desc_overflow_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->sw_send_dma_eng_err_status_cnt[8];
पूर्ण

अटल u64 access_sdma_length_mismatch_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					       व्योम *context, पूर्णांक vl,
					       पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->sw_send_dma_eng_err_status_cnt[7];
पूर्ण

अटल u64 access_sdma_halt_err_cnt(स्थिर काष्ठा cntr_entry *entry,
				    व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->sw_send_dma_eng_err_status_cnt[6];
पूर्ण

अटल u64 access_sdma_mem_पढ़ो_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					व्योम *context, पूर्णांक vl, पूर्णांक mode,
					u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->sw_send_dma_eng_err_status_cnt[5];
पूर्ण

अटल u64 access_sdma_first_desc_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					  व्योम *context, पूर्णांक vl, पूर्णांक mode,
					  u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->sw_send_dma_eng_err_status_cnt[4];
पूर्ण

अटल u64 access_sdma_tail_out_of_bounds_err_cnt(
				स्थिर काष्ठा cntr_entry *entry,
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->sw_send_dma_eng_err_status_cnt[3];
पूर्ण

अटल u64 access_sdma_too_दीर्घ_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					व्योम *context, पूर्णांक vl, पूर्णांक mode,
					u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->sw_send_dma_eng_err_status_cnt[2];
पूर्ण

अटल u64 access_sdma_gen_mismatch_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					    व्योम *context, पूर्णांक vl, पूर्णांक mode,
					    u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->sw_send_dma_eng_err_status_cnt[1];
पूर्ण

अटल u64 access_sdma_wrong_dw_err_cnt(स्थिर काष्ठा cntr_entry *entry,
					व्योम *context, पूर्णांक vl, पूर्णांक mode,
					u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	वापस dd->sw_send_dma_eng_err_status_cnt[0];
पूर्ण

अटल u64 access_dc_rcv_err_cnt(स्थिर काष्ठा cntr_entry *entry,
				 व्योम *context, पूर्णांक vl, पूर्णांक mode,
				 u64 data)
अणु
	काष्ठा hfi1_devdata *dd = (काष्ठा hfi1_devdata *)context;

	u64 val = 0;
	u64 csr = entry->csr;

	val = पढ़ो_ग_लिखो_csr(dd, csr, mode, data);
	अगर (mode == CNTR_MODE_R) अणु
		val = val > CNTR_MAX - dd->sw_rcv_bypass_packet_errors ?
			CNTR_MAX : val + dd->sw_rcv_bypass_packet_errors;
	पूर्ण अन्यथा अगर (mode == CNTR_MODE_W) अणु
		dd->sw_rcv_bypass_packet_errors = 0;
	पूर्ण अन्यथा अणु
		dd_dev_err(dd, "Invalid cntr register access mode");
		वापस 0;
	पूर्ण
	वापस val;
पूर्ण

#घोषणा def_access_sw_cpu(cntr) \
अटल u64 access_sw_cpu_##cntr(स्थिर काष्ठा cntr_entry *entry,		      \
			      व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)      \
अणु									      \
	काष्ठा hfi1_pportdata *ppd = (काष्ठा hfi1_pportdata *)context;	      \
	वापस पढ़ो_ग_लिखो_cpu(ppd->dd, &ppd->ibport_data.rvp.z_ ##cntr,	      \
			      ppd->ibport_data.rvp.cntr, vl,		      \
			      mode, data);				      \
पूर्ण

def_access_sw_cpu(rc_acks);
def_access_sw_cpu(rc_qacks);
def_access_sw_cpu(rc_delayed_comp);

#घोषणा def_access_ibp_counter(cntr) \
अटल u64 access_ibp_##cntr(स्थिर काष्ठा cntr_entry *entry,		      \
				व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)    \
अणु									      \
	काष्ठा hfi1_pportdata *ppd = (काष्ठा hfi1_pportdata *)context;	      \
									      \
	अगर (vl != CNTR_INVALID_VL)					      \
		वापस 0;						      \
									      \
	वापस पढ़ो_ग_लिखो_sw(ppd->dd, &ppd->ibport_data.rvp.n_ ##cntr,	      \
			     mode, data);				      \
पूर्ण

def_access_ibp_counter(loop_pkts);
def_access_ibp_counter(rc_resends);
def_access_ibp_counter(rnr_naks);
def_access_ibp_counter(other_naks);
def_access_ibp_counter(rc_समयouts);
def_access_ibp_counter(pkt_drops);
def_access_ibp_counter(dmaरुको);
def_access_ibp_counter(rc_seqnak);
def_access_ibp_counter(rc_dupreq);
def_access_ibp_counter(rdma_seq);
def_access_ibp_counter(unaligned);
def_access_ibp_counter(seq_naks);
def_access_ibp_counter(rc_crरुकोs);

अटल काष्ठा cntr_entry dev_cntrs[DEV_CNTR_LAST] = अणु
[C_RCV_OVF] = RXE32_DEV_CNTR_ELEM(RcvOverflow, RCV_BUF_OVFL_CNT, CNTR_SYNTH),
[C_RX_LEN_ERR] = RXE32_DEV_CNTR_ELEM(RxLenErr, RCV_LENGTH_ERR_CNT, CNTR_SYNTH),
[C_RX_SHORT_ERR] = RXE32_DEV_CNTR_ELEM(RxShrErr, RCV_SHORT_ERR_CNT, CNTR_SYNTH),
[C_RX_ICRC_ERR] = RXE32_DEV_CNTR_ELEM(RxICrcErr, RCV_ICRC_ERR_CNT, CNTR_SYNTH),
[C_RX_EBP] = RXE32_DEV_CNTR_ELEM(RxEbpCnt, RCV_EBP_CNT, CNTR_SYNTH),
[C_RX_TID_FULL] = RXE32_DEV_CNTR_ELEM(RxTIDFullEr, RCV_TID_FULL_ERR_CNT,
			CNTR_NORMAL),
[C_RX_TID_INVALID] = RXE32_DEV_CNTR_ELEM(RxTIDInvalid, RCV_TID_VALID_ERR_CNT,
			CNTR_NORMAL),
[C_RX_TID_FLGMS] = RXE32_DEV_CNTR_ELEM(RxTidFLGMs,
			RCV_TID_FLOW_GEN_MISMATCH_CNT,
			CNTR_NORMAL),
[C_RX_CTX_EGRS] = RXE32_DEV_CNTR_ELEM(RxCtxEgrS, RCV_CONTEXT_EGR_STALL,
			CNTR_NORMAL),
[C_RCV_TID_FLSMS] = RXE32_DEV_CNTR_ELEM(RxTidFLSMs,
			RCV_TID_FLOW_SEQ_MISMATCH_CNT, CNTR_NORMAL),
[C_CCE_PCI_CR_ST] = CCE_PERF_DEV_CNTR_ELEM(CcePciCrSt,
			CCE_PCIE_POSTED_CRDT_STALL_CNT, CNTR_NORMAL),
[C_CCE_PCI_TR_ST] = CCE_PERF_DEV_CNTR_ELEM(CcePciTrSt, CCE_PCIE_TRGT_STALL_CNT,
			CNTR_NORMAL),
[C_CCE_PIO_WR_ST] = CCE_PERF_DEV_CNTR_ELEM(CcePioWrSt, CCE_PIO_WR_STALL_CNT,
			CNTR_NORMAL),
[C_CCE_ERR_INT] = CCE_INT_DEV_CNTR_ELEM(CceErrInt, CCE_ERR_INT_CNT,
			CNTR_NORMAL),
[C_CCE_SDMA_INT] = CCE_INT_DEV_CNTR_ELEM(CceSdmaInt, CCE_SDMA_INT_CNT,
			CNTR_NORMAL),
[C_CCE_MISC_INT] = CCE_INT_DEV_CNTR_ELEM(CceMiscInt, CCE_MISC_INT_CNT,
			CNTR_NORMAL),
[C_CCE_RCV_AV_INT] = CCE_INT_DEV_CNTR_ELEM(CceRcvAvInt, CCE_RCV_AVAIL_INT_CNT,
			CNTR_NORMAL),
[C_CCE_RCV_URG_INT] = CCE_INT_DEV_CNTR_ELEM(CceRcvUrgInt,
			CCE_RCV_URGENT_INT_CNT,	CNTR_NORMAL),
[C_CCE_SEND_CR_INT] = CCE_INT_DEV_CNTR_ELEM(CceSndCrInt,
			CCE_SEND_CREDIT_INT_CNT, CNTR_NORMAL),
[C_DC_UNC_ERR] = DC_PERF_CNTR(DcUnctblErr, DCC_ERR_UNCORRECTABLE_CNT,
			      CNTR_SYNTH),
[C_DC_RCV_ERR] = CNTR_ELEM("DcRecvErr", DCC_ERR_PORTRCV_ERR_CNT, 0, CNTR_SYNTH,
			    access_dc_rcv_err_cnt),
[C_DC_FM_CFG_ERR] = DC_PERF_CNTR(DcFmCfgErr, DCC_ERR_FMCONFIG_ERR_CNT,
				 CNTR_SYNTH),
[C_DC_RMT_PHY_ERR] = DC_PERF_CNTR(DcRmtPhyErr, DCC_ERR_RCVREMOTE_PHY_ERR_CNT,
				  CNTR_SYNTH),
[C_DC_DROPPED_PKT] = DC_PERF_CNTR(DcDroppedPkt, DCC_ERR_DROPPED_PKT_CNT,
				  CNTR_SYNTH),
[C_DC_MC_XMIT_PKTS] = DC_PERF_CNTR(DcMcXmitPkts,
				   DCC_PRF_PORT_XMIT_MULTICAST_CNT, CNTR_SYNTH),
[C_DC_MC_RCV_PKTS] = DC_PERF_CNTR(DcMcRcvPkts,
				  DCC_PRF_PORT_RCV_MULTICAST_PKT_CNT,
				  CNTR_SYNTH),
[C_DC_XMIT_CERR] = DC_PERF_CNTR(DcXmitCorr,
				DCC_PRF_PORT_XMIT_CORRECTABLE_CNT, CNTR_SYNTH),
[C_DC_RCV_CERR] = DC_PERF_CNTR(DcRcvCorrCnt, DCC_PRF_PORT_RCV_CORRECTABLE_CNT,
			       CNTR_SYNTH),
[C_DC_RCV_FCC] = DC_PERF_CNTR(DcRxFCntl, DCC_PRF_RX_FLOW_CRTL_CNT,
			      CNTR_SYNTH),
[C_DC_XMIT_FCC] = DC_PERF_CNTR(DcXmitFCntl, DCC_PRF_TX_FLOW_CRTL_CNT,
			       CNTR_SYNTH),
[C_DC_XMIT_FLITS] = DC_PERF_CNTR(DcXmitFlits, DCC_PRF_PORT_XMIT_DATA_CNT,
				 CNTR_SYNTH),
[C_DC_RCV_FLITS] = DC_PERF_CNTR(DcRcvFlits, DCC_PRF_PORT_RCV_DATA_CNT,
				CNTR_SYNTH),
[C_DC_XMIT_PKTS] = DC_PERF_CNTR(DcXmitPkts, DCC_PRF_PORT_XMIT_PKTS_CNT,
				CNTR_SYNTH),
[C_DC_RCV_PKTS] = DC_PERF_CNTR(DcRcvPkts, DCC_PRF_PORT_RCV_PKTS_CNT,
			       CNTR_SYNTH),
[C_DC_RX_FLIT_VL] = DC_PERF_CNTR(DcRxFlitVl, DCC_PRF_PORT_VL_RCV_DATA_CNT,
				 CNTR_SYNTH | CNTR_VL),
[C_DC_RX_PKT_VL] = DC_PERF_CNTR(DcRxPktVl, DCC_PRF_PORT_VL_RCV_PKTS_CNT,
				CNTR_SYNTH | CNTR_VL),
[C_DC_RCV_FCN] = DC_PERF_CNTR(DcRcvFcn, DCC_PRF_PORT_RCV_FECN_CNT, CNTR_SYNTH),
[C_DC_RCV_FCN_VL] = DC_PERF_CNTR(DcRcvFcnVl, DCC_PRF_PORT_VL_RCV_FECN_CNT,
				 CNTR_SYNTH | CNTR_VL),
[C_DC_RCV_BCN] = DC_PERF_CNTR(DcRcvBcn, DCC_PRF_PORT_RCV_BECN_CNT, CNTR_SYNTH),
[C_DC_RCV_BCN_VL] = DC_PERF_CNTR(DcRcvBcnVl, DCC_PRF_PORT_VL_RCV_BECN_CNT,
				 CNTR_SYNTH | CNTR_VL),
[C_DC_RCV_BBL] = DC_PERF_CNTR(DcRcvBbl, DCC_PRF_PORT_RCV_BUBBLE_CNT,
			      CNTR_SYNTH),
[C_DC_RCV_BBL_VL] = DC_PERF_CNTR(DcRcvBblVl, DCC_PRF_PORT_VL_RCV_BUBBLE_CNT,
				 CNTR_SYNTH | CNTR_VL),
[C_DC_MARK_FECN] = DC_PERF_CNTR(DcMarkFcn, DCC_PRF_PORT_MARK_FECN_CNT,
				CNTR_SYNTH),
[C_DC_MARK_FECN_VL] = DC_PERF_CNTR(DcMarkFcnVl, DCC_PRF_PORT_VL_MARK_FECN_CNT,
				   CNTR_SYNTH | CNTR_VL),
[C_DC_TOTAL_CRC] =
	DC_PERF_CNTR_LCB(DcTotCrc, DC_LCB_ERR_INFO_TOTAL_CRC_ERR,
			 CNTR_SYNTH),
[C_DC_CRC_LN0] = DC_PERF_CNTR_LCB(DcCrcLn0, DC_LCB_ERR_INFO_CRC_ERR_LN0,
				  CNTR_SYNTH),
[C_DC_CRC_LN1] = DC_PERF_CNTR_LCB(DcCrcLn1, DC_LCB_ERR_INFO_CRC_ERR_LN1,
				  CNTR_SYNTH),
[C_DC_CRC_LN2] = DC_PERF_CNTR_LCB(DcCrcLn2, DC_LCB_ERR_INFO_CRC_ERR_LN2,
				  CNTR_SYNTH),
[C_DC_CRC_LN3] = DC_PERF_CNTR_LCB(DcCrcLn3, DC_LCB_ERR_INFO_CRC_ERR_LN3,
				  CNTR_SYNTH),
[C_DC_CRC_MULT_LN] =
	DC_PERF_CNTR_LCB(DcMultLn, DC_LCB_ERR_INFO_CRC_ERR_MULTI_LN,
			 CNTR_SYNTH),
[C_DC_TX_REPLAY] = DC_PERF_CNTR_LCB(DcTxReplay, DC_LCB_ERR_INFO_TX_REPLAY_CNT,
				    CNTR_SYNTH),
[C_DC_RX_REPLAY] = DC_PERF_CNTR_LCB(DcRxReplay, DC_LCB_ERR_INFO_RX_REPLAY_CNT,
				    CNTR_SYNTH),
[C_DC_SEQ_CRC_CNT] =
	DC_PERF_CNTR_LCB(DcLinkSeqCrc, DC_LCB_ERR_INFO_SEQ_CRC_CNT,
			 CNTR_SYNTH),
[C_DC_ESC0_ONLY_CNT] =
	DC_PERF_CNTR_LCB(DcEsc0, DC_LCB_ERR_INFO_ESCAPE_0_ONLY_CNT,
			 CNTR_SYNTH),
[C_DC_ESC0_PLUS1_CNT] =
	DC_PERF_CNTR_LCB(DcEsc1, DC_LCB_ERR_INFO_ESCAPE_0_PLUS1_CNT,
			 CNTR_SYNTH),
[C_DC_ESC0_PLUS2_CNT] =
	DC_PERF_CNTR_LCB(DcEsc0Plus2, DC_LCB_ERR_INFO_ESCAPE_0_PLUS2_CNT,
			 CNTR_SYNTH),
[C_DC_REINIT_FROM_PEER_CNT] =
	DC_PERF_CNTR_LCB(DcReinitPeer, DC_LCB_ERR_INFO_REINIT_FROM_PEER_CNT,
			 CNTR_SYNTH),
[C_DC_SBE_CNT] = DC_PERF_CNTR_LCB(DcSbe, DC_LCB_ERR_INFO_SBE_CNT,
				  CNTR_SYNTH),
[C_DC_MISC_FLG_CNT] =
	DC_PERF_CNTR_LCB(DcMiscFlg, DC_LCB_ERR_INFO_MISC_FLG_CNT,
			 CNTR_SYNTH),
[C_DC_PRF_GOOD_LTP_CNT] =
	DC_PERF_CNTR_LCB(DcGoodLTP, DC_LCB_PRF_GOOD_LTP_CNT, CNTR_SYNTH),
[C_DC_PRF_ACCEPTED_LTP_CNT] =
	DC_PERF_CNTR_LCB(DcAccLTP, DC_LCB_PRF_ACCEPTED_LTP_CNT,
			 CNTR_SYNTH),
[C_DC_PRF_RX_FLIT_CNT] =
	DC_PERF_CNTR_LCB(DcPrfRxFlit, DC_LCB_PRF_RX_FLIT_CNT, CNTR_SYNTH),
[C_DC_PRF_TX_FLIT_CNT] =
	DC_PERF_CNTR_LCB(DcPrfTxFlit, DC_LCB_PRF_TX_FLIT_CNT, CNTR_SYNTH),
[C_DC_PRF_CLK_CNTR] =
	DC_PERF_CNTR_LCB(DcPrfClk, DC_LCB_PRF_CLK_CNTR, CNTR_SYNTH),
[C_DC_PG_DBG_FLIT_CRDTS_CNT] =
	DC_PERF_CNTR_LCB(DcFltCrdts, DC_LCB_PG_DBG_FLIT_CRDTS_CNT, CNTR_SYNTH),
[C_DC_PG_STS_PAUSE_COMPLETE_CNT] =
	DC_PERF_CNTR_LCB(DcPauseComp, DC_LCB_PG_STS_PAUSE_COMPLETE_CNT,
			 CNTR_SYNTH),
[C_DC_PG_STS_TX_SBE_CNT] =
	DC_PERF_CNTR_LCB(DcStsTxSbe, DC_LCB_PG_STS_TX_SBE_CNT, CNTR_SYNTH),
[C_DC_PG_STS_TX_MBE_CNT] =
	DC_PERF_CNTR_LCB(DcStsTxMbe, DC_LCB_PG_STS_TX_MBE_CNT,
			 CNTR_SYNTH),
[C_SW_CPU_INTR] = CNTR_ELEM("Intr", 0, 0, CNTR_NORMAL,
			    access_sw_cpu_पूर्णांकr),
[C_SW_CPU_RCV_LIM] = CNTR_ELEM("RcvLimit", 0, 0, CNTR_NORMAL,
			    access_sw_cpu_rcv_limit),
[C_SW_CTX0_SEQ_DROP] = CNTR_ELEM("SeqDrop0", 0, 0, CNTR_NORMAL,
			    access_sw_ctx0_seq_drop),
[C_SW_VTX_WAIT] = CNTR_ELEM("vTxWait", 0, 0, CNTR_NORMAL,
			    access_sw_vtx_रुको),
[C_SW_PIO_WAIT] = CNTR_ELEM("PioWait", 0, 0, CNTR_NORMAL,
			    access_sw_pio_रुको),
[C_SW_PIO_DRAIN] = CNTR_ELEM("PioDrain", 0, 0, CNTR_NORMAL,
			    access_sw_pio_drain),
[C_SW_KMEM_WAIT] = CNTR_ELEM("KmemWait", 0, 0, CNTR_NORMAL,
			    access_sw_kmem_रुको),
[C_SW_TID_WAIT] = CNTR_ELEM("TidWait", 0, 0, CNTR_NORMAL,
			    hfi1_access_sw_tid_रुको),
[C_SW_SEND_SCHED] = CNTR_ELEM("SendSched", 0, 0, CNTR_NORMAL,
			    access_sw_send_schedule),
[C_SDMA_DESC_FETCHED_CNT] = CNTR_ELEM("SDEDscFdCn",
				      SEND_DMA_DESC_FETCHED_CNT, 0,
				      CNTR_NORMAL | CNTR_32BIT | CNTR_SDMA,
				      dev_access_u32_csr),
[C_SDMA_INT_CNT] = CNTR_ELEM("SDMAInt", 0, 0,
			     CNTR_NORMAL | CNTR_32BIT | CNTR_SDMA,
			     access_sde_पूर्णांक_cnt),
[C_SDMA_ERR_CNT] = CNTR_ELEM("SDMAErrCt", 0, 0,
			     CNTR_NORMAL | CNTR_32BIT | CNTR_SDMA,
			     access_sde_err_cnt),
[C_SDMA_IDLE_INT_CNT] = CNTR_ELEM("SDMAIdInt", 0, 0,
				  CNTR_NORMAL | CNTR_32BIT | CNTR_SDMA,
				  access_sde_idle_पूर्णांक_cnt),
[C_SDMA_PROGRESS_INT_CNT] = CNTR_ELEM("SDMAPrIntCn", 0, 0,
				      CNTR_NORMAL | CNTR_32BIT | CNTR_SDMA,
				      access_sde_progress_पूर्णांक_cnt),
/* MISC_ERR_STATUS */
[C_MISC_PLL_LOCK_FAIL_ERR] = CNTR_ELEM("MISC_PLL_LOCK_FAIL_ERR", 0, 0,
				CNTR_NORMAL,
				access_misc_pll_lock_fail_err_cnt),
[C_MISC_MBIST_FAIL_ERR] = CNTR_ELEM("MISC_MBIST_FAIL_ERR", 0, 0,
				CNTR_NORMAL,
				access_misc_mbist_fail_err_cnt),
[C_MISC_INVALID_EEP_CMD_ERR] = CNTR_ELEM("MISC_INVALID_EEP_CMD_ERR", 0, 0,
				CNTR_NORMAL,
				access_misc_invalid_eep_cmd_err_cnt),
[C_MISC_EFUSE_DONE_PARITY_ERR] = CNTR_ELEM("MISC_EFUSE_DONE_PARITY_ERR", 0, 0,
				CNTR_NORMAL,
				access_misc_efuse_करोne_parity_err_cnt),
[C_MISC_EFUSE_WRITE_ERR] = CNTR_ELEM("MISC_EFUSE_WRITE_ERR", 0, 0,
				CNTR_NORMAL,
				access_misc_efuse_ग_लिखो_err_cnt),
[C_MISC_EFUSE_READ_BAD_ADDR_ERR] = CNTR_ELEM("MISC_EFUSE_READ_BAD_ADDR_ERR", 0,
				0, CNTR_NORMAL,
				access_misc_efuse_पढ़ो_bad_addr_err_cnt),
[C_MISC_EFUSE_CSR_PARITY_ERR] = CNTR_ELEM("MISC_EFUSE_CSR_PARITY_ERR", 0, 0,
				CNTR_NORMAL,
				access_misc_efuse_csr_parity_err_cnt),
[C_MISC_FW_AUTH_FAILED_ERR] = CNTR_ELEM("MISC_FW_AUTH_FAILED_ERR", 0, 0,
				CNTR_NORMAL,
				access_misc_fw_auth_failed_err_cnt),
[C_MISC_KEY_MISMATCH_ERR] = CNTR_ELEM("MISC_KEY_MISMATCH_ERR", 0, 0,
				CNTR_NORMAL,
				access_misc_key_mismatch_err_cnt),
[C_MISC_SBUS_WRITE_FAILED_ERR] = CNTR_ELEM("MISC_SBUS_WRITE_FAILED_ERR", 0, 0,
				CNTR_NORMAL,
				access_misc_sbus_ग_लिखो_failed_err_cnt),
[C_MISC_CSR_WRITE_BAD_ADDR_ERR] = CNTR_ELEM("MISC_CSR_WRITE_BAD_ADDR_ERR", 0, 0,
				CNTR_NORMAL,
				access_misc_csr_ग_लिखो_bad_addr_err_cnt),
[C_MISC_CSR_READ_BAD_ADDR_ERR] = CNTR_ELEM("MISC_CSR_READ_BAD_ADDR_ERR", 0, 0,
				CNTR_NORMAL,
				access_misc_csr_पढ़ो_bad_addr_err_cnt),
[C_MISC_CSR_PARITY_ERR] = CNTR_ELEM("MISC_CSR_PARITY_ERR", 0, 0,
				CNTR_NORMAL,
				access_misc_csr_parity_err_cnt),
/* CceErrStatus */
[C_CCE_ERR_STATUS_AGGREGATED_CNT] = CNTR_ELEM("CceErrStatusAggregatedCnt", 0, 0,
				CNTR_NORMAL,
				access_sw_cce_err_status_aggregated_cnt),
[C_CCE_MSIX_CSR_PARITY_ERR] = CNTR_ELEM("CceMsixCsrParityErr", 0, 0,
				CNTR_NORMAL,
				access_cce_msix_csr_parity_err_cnt),
[C_CCE_INT_MAP_UNC_ERR] = CNTR_ELEM("CceIntMapUncErr", 0, 0,
				CNTR_NORMAL,
				access_cce_पूर्णांक_map_unc_err_cnt),
[C_CCE_INT_MAP_COR_ERR] = CNTR_ELEM("CceIntMapCorErr", 0, 0,
				CNTR_NORMAL,
				access_cce_पूर्णांक_map_cor_err_cnt),
[C_CCE_MSIX_TABLE_UNC_ERR] = CNTR_ELEM("CceMsixTableUncErr", 0, 0,
				CNTR_NORMAL,
				access_cce_msix_table_unc_err_cnt),
[C_CCE_MSIX_TABLE_COR_ERR] = CNTR_ELEM("CceMsixTableCorErr", 0, 0,
				CNTR_NORMAL,
				access_cce_msix_table_cor_err_cnt),
[C_CCE_RXDMA_CONV_FIFO_PARITY_ERR] = CNTR_ELEM("CceRxdmaConvFifoParityErr", 0,
				0, CNTR_NORMAL,
				access_cce_rxdma_conv_fअगरo_parity_err_cnt),
[C_CCE_RCPL_ASYNC_FIFO_PARITY_ERR] = CNTR_ELEM("CceRcplAsyncFifoParityErr", 0,
				0, CNTR_NORMAL,
				access_cce_rcpl_async_fअगरo_parity_err_cnt),
[C_CCE_SEG_WRITE_BAD_ADDR_ERR] = CNTR_ELEM("CceSegWriteBadAddrErr", 0, 0,
				CNTR_NORMAL,
				access_cce_seg_ग_लिखो_bad_addr_err_cnt),
[C_CCE_SEG_READ_BAD_ADDR_ERR] = CNTR_ELEM("CceSegReadBadAddrErr", 0, 0,
				CNTR_NORMAL,
				access_cce_seg_पढ़ो_bad_addr_err_cnt),
[C_LA_TRIGGERED] = CNTR_ELEM("Cce LATriggered", 0, 0,
				CNTR_NORMAL,
				access_la_triggered_cnt),
[C_CCE_TRGT_CPL_TIMEOUT_ERR] = CNTR_ELEM("CceTrgtCplTimeoutErr", 0, 0,
				CNTR_NORMAL,
				access_cce_trgt_cpl_समयout_err_cnt),
[C_PCIC_RECEIVE_PARITY_ERR] = CNTR_ELEM("PcicReceiveParityErr", 0, 0,
				CNTR_NORMAL,
				access_pcic_receive_parity_err_cnt),
[C_PCIC_TRANSMIT_BACK_PARITY_ERR] = CNTR_ELEM("PcicTransmitBackParityErr", 0, 0,
				CNTR_NORMAL,
				access_pcic_transmit_back_parity_err_cnt),
[C_PCIC_TRANSMIT_FRONT_PARITY_ERR] = CNTR_ELEM("PcicTransmitFrontParityErr", 0,
				0, CNTR_NORMAL,
				access_pcic_transmit_front_parity_err_cnt),
[C_PCIC_CPL_DAT_Q_UNC_ERR] = CNTR_ELEM("PcicCplDatQUncErr", 0, 0,
				CNTR_NORMAL,
				access_pcic_cpl_dat_q_unc_err_cnt),
[C_PCIC_CPL_HD_Q_UNC_ERR] = CNTR_ELEM("PcicCplHdQUncErr", 0, 0,
				CNTR_NORMAL,
				access_pcic_cpl_hd_q_unc_err_cnt),
[C_PCIC_POST_DAT_Q_UNC_ERR] = CNTR_ELEM("PcicPostDatQUncErr", 0, 0,
				CNTR_NORMAL,
				access_pcic_post_dat_q_unc_err_cnt),
[C_PCIC_POST_HD_Q_UNC_ERR] = CNTR_ELEM("PcicPostHdQUncErr", 0, 0,
				CNTR_NORMAL,
				access_pcic_post_hd_q_unc_err_cnt),
[C_PCIC_RETRY_SOT_MEM_UNC_ERR] = CNTR_ELEM("PcicRetrySotMemUncErr", 0, 0,
				CNTR_NORMAL,
				access_pcic_retry_sot_mem_unc_err_cnt),
[C_PCIC_RETRY_MEM_UNC_ERR] = CNTR_ELEM("PcicRetryMemUncErr", 0, 0,
				CNTR_NORMAL,
				access_pcic_retry_mem_unc_err),
[C_PCIC_N_POST_DAT_Q_PARITY_ERR] = CNTR_ELEM("PcicNPostDatQParityErr", 0, 0,
				CNTR_NORMAL,
				access_pcic_n_post_dat_q_parity_err_cnt),
[C_PCIC_N_POST_H_Q_PARITY_ERR] = CNTR_ELEM("PcicNPostHQParityErr", 0, 0,
				CNTR_NORMAL,
				access_pcic_n_post_h_q_parity_err_cnt),
[C_PCIC_CPL_DAT_Q_COR_ERR] = CNTR_ELEM("PcicCplDatQCorErr", 0, 0,
				CNTR_NORMAL,
				access_pcic_cpl_dat_q_cor_err_cnt),
[C_PCIC_CPL_HD_Q_COR_ERR] = CNTR_ELEM("PcicCplHdQCorErr", 0, 0,
				CNTR_NORMAL,
				access_pcic_cpl_hd_q_cor_err_cnt),
[C_PCIC_POST_DAT_Q_COR_ERR] = CNTR_ELEM("PcicPostDatQCorErr", 0, 0,
				CNTR_NORMAL,
				access_pcic_post_dat_q_cor_err_cnt),
[C_PCIC_POST_HD_Q_COR_ERR] = CNTR_ELEM("PcicPostHdQCorErr", 0, 0,
				CNTR_NORMAL,
				access_pcic_post_hd_q_cor_err_cnt),
[C_PCIC_RETRY_SOT_MEM_COR_ERR] = CNTR_ELEM("PcicRetrySotMemCorErr", 0, 0,
				CNTR_NORMAL,
				access_pcic_retry_sot_mem_cor_err_cnt),
[C_PCIC_RETRY_MEM_COR_ERR] = CNTR_ELEM("PcicRetryMemCorErr", 0, 0,
				CNTR_NORMAL,
				access_pcic_retry_mem_cor_err_cnt),
[C_CCE_CLI1_ASYNC_FIFO_DBG_PARITY_ERR] = CNTR_ELEM(
				"CceCli1AsyncFifoDbgParityError", 0, 0,
				CNTR_NORMAL,
				access_cce_cli1_async_fअगरo_dbg_parity_err_cnt),
[C_CCE_CLI1_ASYNC_FIFO_RXDMA_PARITY_ERR] = CNTR_ELEM(
				"CceCli1AsyncFifoRxdmaParityError", 0, 0,
				CNTR_NORMAL,
				access_cce_cli1_async_fअगरo_rxdma_parity_err_cnt
				),
[C_CCE_CLI1_ASYNC_FIFO_SDMA_HD_PARITY_ERR] = CNTR_ELEM(
			"CceCli1AsyncFifoSdmaHdParityErr", 0, 0,
			CNTR_NORMAL,
			access_cce_cli1_async_fअगरo_sdma_hd_parity_err_cnt),
[C_CCE_CLI1_ASYNC_FIFO_PIO_CRDT_PARITY_ERR] = CNTR_ELEM(
			"CceCli1AsyncFifoPioCrdtParityErr", 0, 0,
			CNTR_NORMAL,
			access_cce_cl1_async_fअगरo_pio_crdt_parity_err_cnt),
[C_CCE_CLI2_ASYNC_FIFO_PARITY_ERR] = CNTR_ELEM("CceCli2AsyncFifoParityErr", 0,
			0, CNTR_NORMAL,
			access_cce_cli2_async_fअगरo_parity_err_cnt),
[C_CCE_CSR_CFG_BUS_PARITY_ERR] = CNTR_ELEM("CceCsrCfgBusParityErr", 0, 0,
			CNTR_NORMAL,
			access_cce_csr_cfg_bus_parity_err_cnt),
[C_CCE_CLI0_ASYNC_FIFO_PARTIY_ERR] = CNTR_ELEM("CceCli0AsyncFifoParityErr", 0,
			0, CNTR_NORMAL,
			access_cce_cli0_async_fअगरo_parity_err_cnt),
[C_CCE_RSPD_DATA_PARITY_ERR] = CNTR_ELEM("CceRspdDataParityErr", 0, 0,
			CNTR_NORMAL,
			access_cce_rspd_data_parity_err_cnt),
[C_CCE_TRGT_ACCESS_ERR] = CNTR_ELEM("CceTrgtAccessErr", 0, 0,
			CNTR_NORMAL,
			access_cce_trgt_access_err_cnt),
[C_CCE_TRGT_ASYNC_FIFO_PARITY_ERR] = CNTR_ELEM("CceTrgtAsyncFifoParityErr", 0,
			0, CNTR_NORMAL,
			access_cce_trgt_async_fअगरo_parity_err_cnt),
[C_CCE_CSR_WRITE_BAD_ADDR_ERR] = CNTR_ELEM("CceCsrWriteBadAddrErr", 0, 0,
			CNTR_NORMAL,
			access_cce_csr_ग_लिखो_bad_addr_err_cnt),
[C_CCE_CSR_READ_BAD_ADDR_ERR] = CNTR_ELEM("CceCsrReadBadAddrErr", 0, 0,
			CNTR_NORMAL,
			access_cce_csr_पढ़ो_bad_addr_err_cnt),
[C_CCE_CSR_PARITY_ERR] = CNTR_ELEM("CceCsrParityErr", 0, 0,
			CNTR_NORMAL,
			access_ccs_csr_parity_err_cnt),

/* RcvErrStatus */
[C_RX_CSR_PARITY_ERR] = CNTR_ELEM("RxCsrParityErr", 0, 0,
			CNTR_NORMAL,
			access_rx_csr_parity_err_cnt),
[C_RX_CSR_WRITE_BAD_ADDR_ERR] = CNTR_ELEM("RxCsrWriteBadAddrErr", 0, 0,
			CNTR_NORMAL,
			access_rx_csr_ग_लिखो_bad_addr_err_cnt),
[C_RX_CSR_READ_BAD_ADDR_ERR] = CNTR_ELEM("RxCsrReadBadAddrErr", 0, 0,
			CNTR_NORMAL,
			access_rx_csr_पढ़ो_bad_addr_err_cnt),
[C_RX_DMA_CSR_UNC_ERR] = CNTR_ELEM("RxDmaCsrUncErr", 0, 0,
			CNTR_NORMAL,
			access_rx_dma_csr_unc_err_cnt),
[C_RX_DMA_DQ_FSM_ENCODING_ERR] = CNTR_ELEM("RxDmaDqFsmEncodingErr", 0, 0,
			CNTR_NORMAL,
			access_rx_dma_dq_fsm_encoding_err_cnt),
[C_RX_DMA_EQ_FSM_ENCODING_ERR] = CNTR_ELEM("RxDmaEqFsmEncodingErr", 0, 0,
			CNTR_NORMAL,
			access_rx_dma_eq_fsm_encoding_err_cnt),
[C_RX_DMA_CSR_PARITY_ERR] = CNTR_ELEM("RxDmaCsrParityErr", 0, 0,
			CNTR_NORMAL,
			access_rx_dma_csr_parity_err_cnt),
[C_RX_RBUF_DATA_COR_ERR] = CNTR_ELEM("RxRbufDataCorErr", 0, 0,
			CNTR_NORMAL,
			access_rx_rbuf_data_cor_err_cnt),
[C_RX_RBUF_DATA_UNC_ERR] = CNTR_ELEM("RxRbufDataUncErr", 0, 0,
			CNTR_NORMAL,
			access_rx_rbuf_data_unc_err_cnt),
[C_RX_DMA_DATA_FIFO_RD_COR_ERR] = CNTR_ELEM("RxDmaDataFifoRdCorErr", 0, 0,
			CNTR_NORMAL,
			access_rx_dma_data_fअगरo_rd_cor_err_cnt),
[C_RX_DMA_DATA_FIFO_RD_UNC_ERR] = CNTR_ELEM("RxDmaDataFifoRdUncErr", 0, 0,
			CNTR_NORMAL,
			access_rx_dma_data_fअगरo_rd_unc_err_cnt),
[C_RX_DMA_HDR_FIFO_RD_COR_ERR] = CNTR_ELEM("RxDmaHdrFifoRdCorErr", 0, 0,
			CNTR_NORMAL,
			access_rx_dma_hdr_fअगरo_rd_cor_err_cnt),
[C_RX_DMA_HDR_FIFO_RD_UNC_ERR] = CNTR_ELEM("RxDmaHdrFifoRdUncErr", 0, 0,
			CNTR_NORMAL,
			access_rx_dma_hdr_fअगरo_rd_unc_err_cnt),
[C_RX_RBUF_DESC_PART2_COR_ERR] = CNTR_ELEM("RxRbufDescPart2CorErr", 0, 0,
			CNTR_NORMAL,
			access_rx_rbuf_desc_part2_cor_err_cnt),
[C_RX_RBUF_DESC_PART2_UNC_ERR] = CNTR_ELEM("RxRbufDescPart2UncErr", 0, 0,
			CNTR_NORMAL,
			access_rx_rbuf_desc_part2_unc_err_cnt),
[C_RX_RBUF_DESC_PART1_COR_ERR] = CNTR_ELEM("RxRbufDescPart1CorErr", 0, 0,
			CNTR_NORMAL,
			access_rx_rbuf_desc_part1_cor_err_cnt),
[C_RX_RBUF_DESC_PART1_UNC_ERR] = CNTR_ELEM("RxRbufDescPart1UncErr", 0, 0,
			CNTR_NORMAL,
			access_rx_rbuf_desc_part1_unc_err_cnt),
[C_RX_HQ_INTR_FSM_ERR] = CNTR_ELEM("RxHqIntrFsmErr", 0, 0,
			CNTR_NORMAL,
			access_rx_hq_पूर्णांकr_fsm_err_cnt),
[C_RX_HQ_INTR_CSR_PARITY_ERR] = CNTR_ELEM("RxHqIntrCsrParityErr", 0, 0,
			CNTR_NORMAL,
			access_rx_hq_पूर्णांकr_csr_parity_err_cnt),
[C_RX_LOOKUP_CSR_PARITY_ERR] = CNTR_ELEM("RxLookupCsrParityErr", 0, 0,
			CNTR_NORMAL,
			access_rx_lookup_csr_parity_err_cnt),
[C_RX_LOOKUP_RCV_ARRAY_COR_ERR] = CNTR_ELEM("RxLookupRcvArrayCorErr", 0, 0,
			CNTR_NORMAL,
			access_rx_lookup_rcv_array_cor_err_cnt),
[C_RX_LOOKUP_RCV_ARRAY_UNC_ERR] = CNTR_ELEM("RxLookupRcvArrayUncErr", 0, 0,
			CNTR_NORMAL,
			access_rx_lookup_rcv_array_unc_err_cnt),
[C_RX_LOOKUP_DES_PART2_PARITY_ERR] = CNTR_ELEM("RxLookupDesPart2ParityErr", 0,
			0, CNTR_NORMAL,
			access_rx_lookup_des_part2_parity_err_cnt),
[C_RX_LOOKUP_DES_PART1_UNC_COR_ERR] = CNTR_ELEM("RxLookupDesPart1UncCorErr", 0,
			0, CNTR_NORMAL,
			access_rx_lookup_des_part1_unc_cor_err_cnt),
[C_RX_LOOKUP_DES_PART1_UNC_ERR] = CNTR_ELEM("RxLookupDesPart1UncErr", 0, 0,
			CNTR_NORMAL,
			access_rx_lookup_des_part1_unc_err_cnt),
[C_RX_RBUF_NEXT_FREE_BUF_COR_ERR] = CNTR_ELEM("RxRbufNextFreeBufCorErr", 0, 0,
			CNTR_NORMAL,
			access_rx_rbuf_next_मुक्त_buf_cor_err_cnt),
[C_RX_RBUF_NEXT_FREE_BUF_UNC_ERR] = CNTR_ELEM("RxRbufNextFreeBufUncErr", 0, 0,
			CNTR_NORMAL,
			access_rx_rbuf_next_मुक्त_buf_unc_err_cnt),
[C_RX_RBUF_FL_INIT_WR_ADDR_PARITY_ERR] = CNTR_ELEM(
			"RxRbufFlInitWrAddrParityErr", 0, 0,
			CNTR_NORMAL,
			access_rbuf_fl_init_wr_addr_parity_err_cnt),
[C_RX_RBUF_FL_INITDONE_PARITY_ERR] = CNTR_ELEM("RxRbufFlInitdoneParityErr", 0,
			0, CNTR_NORMAL,
			access_rx_rbuf_fl_initकरोne_parity_err_cnt),
[C_RX_RBUF_FL_WRITE_ADDR_PARITY_ERR] = CNTR_ELEM("RxRbufFlWrAddrParityErr", 0,
			0, CNTR_NORMAL,
			access_rx_rbuf_fl_ग_लिखो_addr_parity_err_cnt),
[C_RX_RBUF_FL_RD_ADDR_PARITY_ERR] = CNTR_ELEM("RxRbufFlRdAddrParityErr", 0, 0,
			CNTR_NORMAL,
			access_rx_rbuf_fl_rd_addr_parity_err_cnt),
[C_RX_RBUF_EMPTY_ERR] = CNTR_ELEM("RxRbufEmptyErr", 0, 0,
			CNTR_NORMAL,
			access_rx_rbuf_empty_err_cnt),
[C_RX_RBUF_FULL_ERR] = CNTR_ELEM("RxRbufFullErr", 0, 0,
			CNTR_NORMAL,
			access_rx_rbuf_full_err_cnt),
[C_RX_RBUF_BAD_LOOKUP_ERR] = CNTR_ELEM("RxRBufBadLookupErr", 0, 0,
			CNTR_NORMAL,
			access_rbuf_bad_lookup_err_cnt),
[C_RX_RBUF_CTX_ID_PARITY_ERR] = CNTR_ELEM("RxRbufCtxIdParityErr", 0, 0,
			CNTR_NORMAL,
			access_rbuf_ctx_id_parity_err_cnt),
[C_RX_RBUF_CSR_QEOPDW_PARITY_ERR] = CNTR_ELEM("RxRbufCsrQEOPDWParityErr", 0, 0,
			CNTR_NORMAL,
			access_rbuf_csr_qeopdw_parity_err_cnt),
[C_RX_RBUF_CSR_Q_NUM_OF_PKT_PARITY_ERR] = CNTR_ELEM(
			"RxRbufCsrQNumOfPktParityErr", 0, 0,
			CNTR_NORMAL,
			access_rx_rbuf_csr_q_num_of_pkt_parity_err_cnt),
[C_RX_RBUF_CSR_Q_T1_PTR_PARITY_ERR] = CNTR_ELEM(
			"RxRbufCsrQTlPtrParityErr", 0, 0,
			CNTR_NORMAL,
			access_rx_rbuf_csr_q_t1_ptr_parity_err_cnt),
[C_RX_RBUF_CSR_Q_HD_PTR_PARITY_ERR] = CNTR_ELEM("RxRbufCsrQHdPtrParityErr", 0,
			0, CNTR_NORMAL,
			access_rx_rbuf_csr_q_hd_ptr_parity_err_cnt),
[C_RX_RBUF_CSR_Q_VLD_BIT_PARITY_ERR] = CNTR_ELEM("RxRbufCsrQVldBitParityErr", 0,
			0, CNTR_NORMAL,
			access_rx_rbuf_csr_q_vld_bit_parity_err_cnt),
[C_RX_RBUF_CSR_Q_NEXT_BUF_PARITY_ERR] = CNTR_ELEM("RxRbufCsrQNextBufParityErr",
			0, 0, CNTR_NORMAL,
			access_rx_rbuf_csr_q_next_buf_parity_err_cnt),
[C_RX_RBUF_CSR_Q_ENT_CNT_PARITY_ERR] = CNTR_ELEM("RxRbufCsrQEntCntParityErr", 0,
			0, CNTR_NORMAL,
			access_rx_rbuf_csr_q_ent_cnt_parity_err_cnt),
[C_RX_RBUF_CSR_Q_HEAD_BUF_NUM_PARITY_ERR] = CNTR_ELEM(
			"RxRbufCsrQHeadBufNumParityErr", 0, 0,
			CNTR_NORMAL,
			access_rx_rbuf_csr_q_head_buf_num_parity_err_cnt),
[C_RX_RBUF_BLOCK_LIST_READ_COR_ERR] = CNTR_ELEM("RxRbufBlockListReadCorErr", 0,
			0, CNTR_NORMAL,
			access_rx_rbuf_block_list_पढ़ो_cor_err_cnt),
[C_RX_RBUF_BLOCK_LIST_READ_UNC_ERR] = CNTR_ELEM("RxRbufBlockListReadUncErr", 0,
			0, CNTR_NORMAL,
			access_rx_rbuf_block_list_पढ़ो_unc_err_cnt),
[C_RX_RBUF_LOOKUP_DES_COR_ERR] = CNTR_ELEM("RxRbufLookupDesCorErr", 0, 0,
			CNTR_NORMAL,
			access_rx_rbuf_lookup_des_cor_err_cnt),
[C_RX_RBUF_LOOKUP_DES_UNC_ERR] = CNTR_ELEM("RxRbufLookupDesUncErr", 0, 0,
			CNTR_NORMAL,
			access_rx_rbuf_lookup_des_unc_err_cnt),
[C_RX_RBUF_LOOKUP_DES_REG_UNC_COR_ERR] = CNTR_ELEM(
			"RxRbufLookupDesRegUncCorErr", 0, 0,
			CNTR_NORMAL,
			access_rx_rbuf_lookup_des_reg_unc_cor_err_cnt),
[C_RX_RBUF_LOOKUP_DES_REG_UNC_ERR] = CNTR_ELEM("RxRbufLookupDesRegUncErr", 0, 0,
			CNTR_NORMAL,
			access_rx_rbuf_lookup_des_reg_unc_err_cnt),
[C_RX_RBUF_FREE_LIST_COR_ERR] = CNTR_ELEM("RxRbufFreeListCorErr", 0, 0,
			CNTR_NORMAL,
			access_rx_rbuf_मुक्त_list_cor_err_cnt),
[C_RX_RBUF_FREE_LIST_UNC_ERR] = CNTR_ELEM("RxRbufFreeListUncErr", 0, 0,
			CNTR_NORMAL,
			access_rx_rbuf_मुक्त_list_unc_err_cnt),
[C_RX_RCV_FSM_ENCODING_ERR] = CNTR_ELEM("RxRcvFsmEncodingErr", 0, 0,
			CNTR_NORMAL,
			access_rx_rcv_fsm_encoding_err_cnt),
[C_RX_DMA_FLAG_COR_ERR] = CNTR_ELEM("RxDmaFlagCorErr", 0, 0,
			CNTR_NORMAL,
			access_rx_dma_flag_cor_err_cnt),
[C_RX_DMA_FLAG_UNC_ERR] = CNTR_ELEM("RxDmaFlagUncErr", 0, 0,
			CNTR_NORMAL,
			access_rx_dma_flag_unc_err_cnt),
[C_RX_DC_SOP_EOP_PARITY_ERR] = CNTR_ELEM("RxDcSopEopParityErr", 0, 0,
			CNTR_NORMAL,
			access_rx_dc_sop_eop_parity_err_cnt),
[C_RX_RCV_CSR_PARITY_ERR] = CNTR_ELEM("RxRcvCsrParityErr", 0, 0,
			CNTR_NORMAL,
			access_rx_rcv_csr_parity_err_cnt),
[C_RX_RCV_QP_MAP_TABLE_COR_ERR] = CNTR_ELEM("RxRcvQpMapTableCorErr", 0, 0,
			CNTR_NORMAL,
			access_rx_rcv_qp_map_table_cor_err_cnt),
[C_RX_RCV_QP_MAP_TABLE_UNC_ERR] = CNTR_ELEM("RxRcvQpMapTableUncErr", 0, 0,
			CNTR_NORMAL,
			access_rx_rcv_qp_map_table_unc_err_cnt),
[C_RX_RCV_DATA_COR_ERR] = CNTR_ELEM("RxRcvDataCorErr", 0, 0,
			CNTR_NORMAL,
			access_rx_rcv_data_cor_err_cnt),
[C_RX_RCV_DATA_UNC_ERR] = CNTR_ELEM("RxRcvDataUncErr", 0, 0,
			CNTR_NORMAL,
			access_rx_rcv_data_unc_err_cnt),
[C_RX_RCV_HDR_COR_ERR] = CNTR_ELEM("RxRcvHdrCorErr", 0, 0,
			CNTR_NORMAL,
			access_rx_rcv_hdr_cor_err_cnt),
[C_RX_RCV_HDR_UNC_ERR] = CNTR_ELEM("RxRcvHdrUncErr", 0, 0,
			CNTR_NORMAL,
			access_rx_rcv_hdr_unc_err_cnt),
[C_RX_DC_INTF_PARITY_ERR] = CNTR_ELEM("RxDcIntfParityErr", 0, 0,
			CNTR_NORMAL,
			access_rx_dc_पूर्णांकf_parity_err_cnt),
[C_RX_DMA_CSR_COR_ERR] = CNTR_ELEM("RxDmaCsrCorErr", 0, 0,
			CNTR_NORMAL,
			access_rx_dma_csr_cor_err_cnt),
/* SendPioErrStatus */
[C_PIO_PEC_SOP_HEAD_PARITY_ERR] = CNTR_ELEM("PioPecSopHeadParityErr", 0, 0,
			CNTR_NORMAL,
			access_pio_pec_sop_head_parity_err_cnt),
[C_PIO_PCC_SOP_HEAD_PARITY_ERR] = CNTR_ELEM("PioPccSopHeadParityErr", 0, 0,
			CNTR_NORMAL,
			access_pio_pcc_sop_head_parity_err_cnt),
[C_PIO_LAST_RETURNED_CNT_PARITY_ERR] = CNTR_ELEM("PioLastReturnedCntParityErr",
			0, 0, CNTR_NORMAL,
			access_pio_last_वापसed_cnt_parity_err_cnt),
[C_PIO_CURRENT_FREE_CNT_PARITY_ERR] = CNTR_ELEM("PioCurrentFreeCntParityErr", 0,
			0, CNTR_NORMAL,
			access_pio_current_मुक्त_cnt_parity_err_cnt),
[C_PIO_RSVD_31_ERR] = CNTR_ELEM("Pio Reserved 31", 0, 0,
			CNTR_NORMAL,
			access_pio_reserved_31_err_cnt),
[C_PIO_RSVD_30_ERR] = CNTR_ELEM("Pio Reserved 30", 0, 0,
			CNTR_NORMAL,
			access_pio_reserved_30_err_cnt),
[C_PIO_PPMC_SOP_LEN_ERR] = CNTR_ELEM("PioPpmcSopLenErr", 0, 0,
			CNTR_NORMAL,
			access_pio_ppmc_sop_len_err_cnt),
[C_PIO_PPMC_BQC_MEM_PARITY_ERR] = CNTR_ELEM("PioPpmcBqcMemParityErr", 0, 0,
			CNTR_NORMAL,
			access_pio_ppmc_bqc_mem_parity_err_cnt),
[C_PIO_VL_FIFO_PARITY_ERR] = CNTR_ELEM("PioVlFifoParityErr", 0, 0,
			CNTR_NORMAL,
			access_pio_vl_fअगरo_parity_err_cnt),
[C_PIO_VLF_SOP_PARITY_ERR] = CNTR_ELEM("PioVlfSopParityErr", 0, 0,
			CNTR_NORMAL,
			access_pio_vlf_sop_parity_err_cnt),
[C_PIO_VLF_V1_LEN_PARITY_ERR] = CNTR_ELEM("PioVlfVlLenParityErr", 0, 0,
			CNTR_NORMAL,
			access_pio_vlf_v1_len_parity_err_cnt),
[C_PIO_BLOCK_QW_COUNT_PARITY_ERR] = CNTR_ELEM("PioBlockQwCountParityErr", 0, 0,
			CNTR_NORMAL,
			access_pio_block_qw_count_parity_err_cnt),
[C_PIO_WRITE_QW_VALID_PARITY_ERR] = CNTR_ELEM("PioWriteQwValidParityErr", 0, 0,
			CNTR_NORMAL,
			access_pio_ग_लिखो_qw_valid_parity_err_cnt),
[C_PIO_STATE_MACHINE_ERR] = CNTR_ELEM("PioStateMachineErr", 0, 0,
			CNTR_NORMAL,
			access_pio_state_machine_err_cnt),
[C_PIO_WRITE_DATA_PARITY_ERR] = CNTR_ELEM("PioWriteDataParityErr", 0, 0,
			CNTR_NORMAL,
			access_pio_ग_लिखो_data_parity_err_cnt),
[C_PIO_HOST_ADDR_MEM_COR_ERR] = CNTR_ELEM("PioHostAddrMemCorErr", 0, 0,
			CNTR_NORMAL,
			access_pio_host_addr_mem_cor_err_cnt),
[C_PIO_HOST_ADDR_MEM_UNC_ERR] = CNTR_ELEM("PioHostAddrMemUncErr", 0, 0,
			CNTR_NORMAL,
			access_pio_host_addr_mem_unc_err_cnt),
[C_PIO_PKT_EVICT_SM_OR_ARM_SM_ERR] = CNTR_ELEM("PioPktEvictSmOrArbSmErr", 0, 0,
			CNTR_NORMAL,
			access_pio_pkt_evict_sm_or_arb_sm_err_cnt),
[C_PIO_INIT_SM_IN_ERR] = CNTR_ELEM("PioInitSmInErr", 0, 0,
			CNTR_NORMAL,
			access_pio_init_sm_in_err_cnt),
[C_PIO_PPMC_PBL_FIFO_ERR] = CNTR_ELEM("PioPpmcPblFifoErr", 0, 0,
			CNTR_NORMAL,
			access_pio_ppmc_pbl_fअगरo_err_cnt),
[C_PIO_CREDIT_RET_FIFO_PARITY_ERR] = CNTR_ELEM("PioCreditRetFifoParityErr", 0,
			0, CNTR_NORMAL,
			access_pio_credit_ret_fअगरo_parity_err_cnt),
[C_PIO_V1_LEN_MEM_BANK1_COR_ERR] = CNTR_ELEM("PioVlLenMemBank1CorErr", 0, 0,
			CNTR_NORMAL,
			access_pio_v1_len_mem_bank1_cor_err_cnt),
[C_PIO_V1_LEN_MEM_BANK0_COR_ERR] = CNTR_ELEM("PioVlLenMemBank0CorErr", 0, 0,
			CNTR_NORMAL,
			access_pio_v1_len_mem_bank0_cor_err_cnt),
[C_PIO_V1_LEN_MEM_BANK1_UNC_ERR] = CNTR_ELEM("PioVlLenMemBank1UncErr", 0, 0,
			CNTR_NORMAL,
			access_pio_v1_len_mem_bank1_unc_err_cnt),
[C_PIO_V1_LEN_MEM_BANK0_UNC_ERR] = CNTR_ELEM("PioVlLenMemBank0UncErr", 0, 0,
			CNTR_NORMAL,
			access_pio_v1_len_mem_bank0_unc_err_cnt),
[C_PIO_SM_PKT_RESET_PARITY_ERR] = CNTR_ELEM("PioSmPktResetParityErr", 0, 0,
			CNTR_NORMAL,
			access_pio_sm_pkt_reset_parity_err_cnt),
[C_PIO_PKT_EVICT_FIFO_PARITY_ERR] = CNTR_ELEM("PioPktEvictFifoParityErr", 0, 0,
			CNTR_NORMAL,
			access_pio_pkt_evict_fअगरo_parity_err_cnt),
[C_PIO_SBRDCTRL_CRREL_FIFO_PARITY_ERR] = CNTR_ELEM(
			"PioSbrdctrlCrrelFifoParityErr", 0, 0,
			CNTR_NORMAL,
			access_pio_sbrdctrl_crrel_fअगरo_parity_err_cnt),
[C_PIO_SBRDCTL_CRREL_PARITY_ERR] = CNTR_ELEM("PioSbrdctlCrrelParityErr", 0, 0,
			CNTR_NORMAL,
			access_pio_sbrdctl_crrel_parity_err_cnt),
[C_PIO_PEC_FIFO_PARITY_ERR] = CNTR_ELEM("PioPecFifoParityErr", 0, 0,
			CNTR_NORMAL,
			access_pio_pec_fअगरo_parity_err_cnt),
[C_PIO_PCC_FIFO_PARITY_ERR] = CNTR_ELEM("PioPccFifoParityErr", 0, 0,
			CNTR_NORMAL,
			access_pio_pcc_fअगरo_parity_err_cnt),
[C_PIO_SB_MEM_FIFO1_ERR] = CNTR_ELEM("PioSbMemFifo1Err", 0, 0,
			CNTR_NORMAL,
			access_pio_sb_mem_fअगरo1_err_cnt),
[C_PIO_SB_MEM_FIFO0_ERR] = CNTR_ELEM("PioSbMemFifo0Err", 0, 0,
			CNTR_NORMAL,
			access_pio_sb_mem_fअगरo0_err_cnt),
[C_PIO_CSR_PARITY_ERR] = CNTR_ELEM("PioCsrParityErr", 0, 0,
			CNTR_NORMAL,
			access_pio_csr_parity_err_cnt),
[C_PIO_WRITE_ADDR_PARITY_ERR] = CNTR_ELEM("PioWriteAddrParityErr", 0, 0,
			CNTR_NORMAL,
			access_pio_ग_लिखो_addr_parity_err_cnt),
[C_PIO_WRITE_BAD_CTXT_ERR] = CNTR_ELEM("PioWriteBadCtxtErr", 0, 0,
			CNTR_NORMAL,
			access_pio_ग_लिखो_bad_ctxt_err_cnt),
/* SendDmaErrStatus */
[C_SDMA_PCIE_REQ_TRACKING_COR_ERR] = CNTR_ELEM("SDmaPcieReqTrackingCorErr", 0,
			0, CNTR_NORMAL,
			access_sdma_pcie_req_tracking_cor_err_cnt),
[C_SDMA_PCIE_REQ_TRACKING_UNC_ERR] = CNTR_ELEM("SDmaPcieReqTrackingUncErr", 0,
			0, CNTR_NORMAL,
			access_sdma_pcie_req_tracking_unc_err_cnt),
[C_SDMA_CSR_PARITY_ERR] = CNTR_ELEM("SDmaCsrParityErr", 0, 0,
			CNTR_NORMAL,
			access_sdma_csr_parity_err_cnt),
[C_SDMA_RPY_TAG_ERR] = CNTR_ELEM("SDmaRpyTagErr", 0, 0,
			CNTR_NORMAL,
			access_sdma_rpy_tag_err_cnt),
/* SendEgressErrStatus */
[C_TX_READ_PIO_MEMORY_CSR_UNC_ERR] = CNTR_ELEM("TxReadPioMemoryCsrUncErr", 0, 0,
			CNTR_NORMAL,
			access_tx_पढ़ो_pio_memory_csr_unc_err_cnt),
[C_TX_READ_SDMA_MEMORY_CSR_UNC_ERR] = CNTR_ELEM("TxReadSdmaMemoryCsrUncErr", 0,
			0, CNTR_NORMAL,
			access_tx_पढ़ो_sdma_memory_csr_err_cnt),
[C_TX_EGRESS_FIFO_COR_ERR] = CNTR_ELEM("TxEgressFifoCorErr", 0, 0,
			CNTR_NORMAL,
			access_tx_egress_fअगरo_cor_err_cnt),
[C_TX_READ_PIO_MEMORY_COR_ERR] = CNTR_ELEM("TxReadPioMemoryCorErr", 0, 0,
			CNTR_NORMAL,
			access_tx_पढ़ो_pio_memory_cor_err_cnt),
[C_TX_READ_SDMA_MEMORY_COR_ERR] = CNTR_ELEM("TxReadSdmaMemoryCorErr", 0, 0,
			CNTR_NORMAL,
			access_tx_पढ़ो_sdma_memory_cor_err_cnt),
[C_TX_SB_HDR_COR_ERR] = CNTR_ELEM("TxSbHdrCorErr", 0, 0,
			CNTR_NORMAL,
			access_tx_sb_hdr_cor_err_cnt),
[C_TX_CREDIT_OVERRUN_ERR] = CNTR_ELEM("TxCreditOverrunErr", 0, 0,
			CNTR_NORMAL,
			access_tx_credit_overrun_err_cnt),
[C_TX_LAUNCH_FIFO8_COR_ERR] = CNTR_ELEM("TxLaunchFifo8CorErr", 0, 0,
			CNTR_NORMAL,
			access_tx_launch_fअगरo8_cor_err_cnt),
[C_TX_LAUNCH_FIFO7_COR_ERR] = CNTR_ELEM("TxLaunchFifo7CorErr", 0, 0,
			CNTR_NORMAL,
			access_tx_launch_fअगरo7_cor_err_cnt),
[C_TX_LAUNCH_FIFO6_COR_ERR] = CNTR_ELEM("TxLaunchFifo6CorErr", 0, 0,
			CNTR_NORMAL,
			access_tx_launch_fअगरo6_cor_err_cnt),
[C_TX_LAUNCH_FIFO5_COR_ERR] = CNTR_ELEM("TxLaunchFifo5CorErr", 0, 0,
			CNTR_NORMAL,
			access_tx_launch_fअगरo5_cor_err_cnt),
[C_TX_LAUNCH_FIFO4_COR_ERR] = CNTR_ELEM("TxLaunchFifo4CorErr", 0, 0,
			CNTR_NORMAL,
			access_tx_launch_fअगरo4_cor_err_cnt),
[C_TX_LAUNCH_FIFO3_COR_ERR] = CNTR_ELEM("TxLaunchFifo3CorErr", 0, 0,
			CNTR_NORMAL,
			access_tx_launch_fअगरo3_cor_err_cnt),
[C_TX_LAUNCH_FIFO2_COR_ERR] = CNTR_ELEM("TxLaunchFifo2CorErr", 0, 0,
			CNTR_NORMAL,
			access_tx_launch_fअगरo2_cor_err_cnt),
[C_TX_LAUNCH_FIFO1_COR_ERR] = CNTR_ELEM("TxLaunchFifo1CorErr", 0, 0,
			CNTR_NORMAL,
			access_tx_launch_fअगरo1_cor_err_cnt),
[C_TX_LAUNCH_FIFO0_COR_ERR] = CNTR_ELEM("TxLaunchFifo0CorErr", 0, 0,
			CNTR_NORMAL,
			access_tx_launch_fअगरo0_cor_err_cnt),
[C_TX_CREDIT_RETURN_VL_ERR] = CNTR_ELEM("TxCreditReturnVLErr", 0, 0,
			CNTR_NORMAL,
			access_tx_credit_वापस_vl_err_cnt),
[C_TX_HCRC_INSERTION_ERR] = CNTR_ELEM("TxHcrcInsertionErr", 0, 0,
			CNTR_NORMAL,
			access_tx_hcrc_insertion_err_cnt),
[C_TX_EGRESS_FIFI_UNC_ERR] = CNTR_ELEM("TxEgressFifoUncErr", 0, 0,
			CNTR_NORMAL,
			access_tx_egress_fअगरo_unc_err_cnt),
[C_TX_READ_PIO_MEMORY_UNC_ERR] = CNTR_ELEM("TxReadPioMemoryUncErr", 0, 0,
			CNTR_NORMAL,
			access_tx_पढ़ो_pio_memory_unc_err_cnt),
[C_TX_READ_SDMA_MEMORY_UNC_ERR] = CNTR_ELEM("TxReadSdmaMemoryUncErr", 0, 0,
			CNTR_NORMAL,
			access_tx_पढ़ो_sdma_memory_unc_err_cnt),
[C_TX_SB_HDR_UNC_ERR] = CNTR_ELEM("TxSbHdrUncErr", 0, 0,
			CNTR_NORMAL,
			access_tx_sb_hdr_unc_err_cnt),
[C_TX_CREDIT_RETURN_PARITY_ERR] = CNTR_ELEM("TxCreditReturnParityErr", 0, 0,
			CNTR_NORMAL,
			access_tx_credit_वापस_partiy_err_cnt),
[C_TX_LAUNCH_FIFO8_UNC_OR_PARITY_ERR] = CNTR_ELEM("TxLaunchFifo8UncOrParityErr",
			0, 0, CNTR_NORMAL,
			access_tx_launch_fअगरo8_unc_or_parity_err_cnt),
[C_TX_LAUNCH_FIFO7_UNC_OR_PARITY_ERR] = CNTR_ELEM("TxLaunchFifo7UncOrParityErr",
			0, 0, CNTR_NORMAL,
			access_tx_launch_fअगरo7_unc_or_parity_err_cnt),
[C_TX_LAUNCH_FIFO6_UNC_OR_PARITY_ERR] = CNTR_ELEM("TxLaunchFifo6UncOrParityErr",
			0, 0, CNTR_NORMAL,
			access_tx_launch_fअगरo6_unc_or_parity_err_cnt),
[C_TX_LAUNCH_FIFO5_UNC_OR_PARITY_ERR] = CNTR_ELEM("TxLaunchFifo5UncOrParityErr",
			0, 0, CNTR_NORMAL,
			access_tx_launch_fअगरo5_unc_or_parity_err_cnt),
[C_TX_LAUNCH_FIFO4_UNC_OR_PARITY_ERR] = CNTR_ELEM("TxLaunchFifo4UncOrParityErr",
			0, 0, CNTR_NORMAL,
			access_tx_launch_fअगरo4_unc_or_parity_err_cnt),
[C_TX_LAUNCH_FIFO3_UNC_OR_PARITY_ERR] = CNTR_ELEM("TxLaunchFifo3UncOrParityErr",
			0, 0, CNTR_NORMAL,
			access_tx_launch_fअगरo3_unc_or_parity_err_cnt),
[C_TX_LAUNCH_FIFO2_UNC_OR_PARITY_ERR] = CNTR_ELEM("TxLaunchFifo2UncOrParityErr",
			0, 0, CNTR_NORMAL,
			access_tx_launch_fअगरo2_unc_or_parity_err_cnt),
[C_TX_LAUNCH_FIFO1_UNC_OR_PARITY_ERR] = CNTR_ELEM("TxLaunchFifo1UncOrParityErr",
			0, 0, CNTR_NORMAL,
			access_tx_launch_fअगरo1_unc_or_parity_err_cnt),
[C_TX_LAUNCH_FIFO0_UNC_OR_PARITY_ERR] = CNTR_ELEM("TxLaunchFifo0UncOrParityErr",
			0, 0, CNTR_NORMAL,
			access_tx_launch_fअगरo0_unc_or_parity_err_cnt),
[C_TX_SDMA15_DISALLOWED_PACKET_ERR] = CNTR_ELEM("TxSdma15DisallowedPacketErr",
			0, 0, CNTR_NORMAL,
			access_tx_sdma15_disallowed_packet_err_cnt),
[C_TX_SDMA14_DISALLOWED_PACKET_ERR] = CNTR_ELEM("TxSdma14DisallowedPacketErr",
			0, 0, CNTR_NORMAL,
			access_tx_sdma14_disallowed_packet_err_cnt),
[C_TX_SDMA13_DISALLOWED_PACKET_ERR] = CNTR_ELEM("TxSdma13DisallowedPacketErr",
			0, 0, CNTR_NORMAL,
			access_tx_sdma13_disallowed_packet_err_cnt),
[C_TX_SDMA12_DISALLOWED_PACKET_ERR] = CNTR_ELEM("TxSdma12DisallowedPacketErr",
			0, 0, CNTR_NORMAL,
			access_tx_sdma12_disallowed_packet_err_cnt),
[C_TX_SDMA11_DISALLOWED_PACKET_ERR] = CNTR_ELEM("TxSdma11DisallowedPacketErr",
			0, 0, CNTR_NORMAL,
			access_tx_sdma11_disallowed_packet_err_cnt),
[C_TX_SDMA10_DISALLOWED_PACKET_ERR] = CNTR_ELEM("TxSdma10DisallowedPacketErr",
			0, 0, CNTR_NORMAL,
			access_tx_sdma10_disallowed_packet_err_cnt),
[C_TX_SDMA9_DISALLOWED_PACKET_ERR] = CNTR_ELEM("TxSdma9DisallowedPacketErr",
			0, 0, CNTR_NORMAL,
			access_tx_sdma9_disallowed_packet_err_cnt),
[C_TX_SDMA8_DISALLOWED_PACKET_ERR] = CNTR_ELEM("TxSdma8DisallowedPacketErr",
			0, 0, CNTR_NORMAL,
			access_tx_sdma8_disallowed_packet_err_cnt),
[C_TX_SDMA7_DISALLOWED_PACKET_ERR] = CNTR_ELEM("TxSdma7DisallowedPacketErr",
			0, 0, CNTR_NORMAL,
			access_tx_sdma7_disallowed_packet_err_cnt),
[C_TX_SDMA6_DISALLOWED_PACKET_ERR] = CNTR_ELEM("TxSdma6DisallowedPacketErr",
			0, 0, CNTR_NORMAL,
			access_tx_sdma6_disallowed_packet_err_cnt),
[C_TX_SDMA5_DISALLOWED_PACKET_ERR] = CNTR_ELEM("TxSdma5DisallowedPacketErr",
			0, 0, CNTR_NORMAL,
			access_tx_sdma5_disallowed_packet_err_cnt),
[C_TX_SDMA4_DISALLOWED_PACKET_ERR] = CNTR_ELEM("TxSdma4DisallowedPacketErr",
			0, 0, CNTR_NORMAL,
			access_tx_sdma4_disallowed_packet_err_cnt),
[C_TX_SDMA3_DISALLOWED_PACKET_ERR] = CNTR_ELEM("TxSdma3DisallowedPacketErr",
			0, 0, CNTR_NORMAL,
			access_tx_sdma3_disallowed_packet_err_cnt),
[C_TX_SDMA2_DISALLOWED_PACKET_ERR] = CNTR_ELEM("TxSdma2DisallowedPacketErr",
			0, 0, CNTR_NORMAL,
			access_tx_sdma2_disallowed_packet_err_cnt),
[C_TX_SDMA1_DISALLOWED_PACKET_ERR] = CNTR_ELEM("TxSdma1DisallowedPacketErr",
			0, 0, CNTR_NORMAL,
			access_tx_sdma1_disallowed_packet_err_cnt),
[C_TX_SDMA0_DISALLOWED_PACKET_ERR] = CNTR_ELEM("TxSdma0DisallowedPacketErr",
			0, 0, CNTR_NORMAL,
			access_tx_sdma0_disallowed_packet_err_cnt),
[C_TX_CONFIG_PARITY_ERR] = CNTR_ELEM("TxConfigParityErr", 0, 0,
			CNTR_NORMAL,
			access_tx_config_parity_err_cnt),
[C_TX_SBRD_CTL_CSR_PARITY_ERR] = CNTR_ELEM("TxSbrdCtlCsrParityErr", 0, 0,
			CNTR_NORMAL,
			access_tx_sbrd_ctl_csr_parity_err_cnt),
[C_TX_LAUNCH_CSR_PARITY_ERR] = CNTR_ELEM("TxLaunchCsrParityErr", 0, 0,
			CNTR_NORMAL,
			access_tx_launch_csr_parity_err_cnt),
[C_TX_ILLEGAL_CL_ERR] = CNTR_ELEM("TxIllegalVLErr", 0, 0,
			CNTR_NORMAL,
			access_tx_illegal_vl_err_cnt),
[C_TX_SBRD_CTL_STATE_MACHINE_PARITY_ERR] = CNTR_ELEM(
			"TxSbrdCtlStateMachineParityErr", 0, 0,
			CNTR_NORMAL,
			access_tx_sbrd_ctl_state_machine_parity_err_cnt),
[C_TX_RESERVED_10] = CNTR_ELEM("Tx Egress Reserved 10", 0, 0,
			CNTR_NORMAL,
			access_egress_reserved_10_err_cnt),
[C_TX_RESERVED_9] = CNTR_ELEM("Tx Egress Reserved 9", 0, 0,
			CNTR_NORMAL,
			access_egress_reserved_9_err_cnt),
[C_TX_SDMA_LAUNCH_INTF_PARITY_ERR] = CNTR_ELEM("TxSdmaLaunchIntfParityErr",
			0, 0, CNTR_NORMAL,
			access_tx_sdma_launch_पूर्णांकf_parity_err_cnt),
[C_TX_PIO_LAUNCH_INTF_PARITY_ERR] = CNTR_ELEM("TxPioLaunchIntfParityErr", 0, 0,
			CNTR_NORMAL,
			access_tx_pio_launch_पूर्णांकf_parity_err_cnt),
[C_TX_RESERVED_6] = CNTR_ELEM("Tx Egress Reserved 6", 0, 0,
			CNTR_NORMAL,
			access_egress_reserved_6_err_cnt),
[C_TX_INCORRECT_LINK_STATE_ERR] = CNTR_ELEM("TxIncorrectLinkStateErr", 0, 0,
			CNTR_NORMAL,
			access_tx_incorrect_link_state_err_cnt),
[C_TX_LINK_DOWN_ERR] = CNTR_ELEM("TxLinkdownErr", 0, 0,
			CNTR_NORMAL,
			access_tx_linkकरोwn_err_cnt),
[C_TX_EGRESS_FIFO_UNDERRUN_OR_PARITY_ERR] = CNTR_ELEM(
			"EgressFifoUnderrunOrParityErr", 0, 0,
			CNTR_NORMAL,
			access_tx_egress_fअगरi_underrun_or_parity_err_cnt),
[C_TX_RESERVED_2] = CNTR_ELEM("Tx Egress Reserved 2", 0, 0,
			CNTR_NORMAL,
			access_egress_reserved_2_err_cnt),
[C_TX_PKT_INTEGRITY_MEM_UNC_ERR] = CNTR_ELEM("TxPktIntegrityMemUncErr", 0, 0,
			CNTR_NORMAL,
			access_tx_pkt_पूर्णांकegrity_mem_unc_err_cnt),
[C_TX_PKT_INTEGRITY_MEM_COR_ERR] = CNTR_ELEM("TxPktIntegrityMemCorErr", 0, 0,
			CNTR_NORMAL,
			access_tx_pkt_पूर्णांकegrity_mem_cor_err_cnt),
/* SendErrStatus */
[C_SEND_CSR_WRITE_BAD_ADDR_ERR] = CNTR_ELEM("SendCsrWriteBadAddrErr", 0, 0,
			CNTR_NORMAL,
			access_send_csr_ग_लिखो_bad_addr_err_cnt),
[C_SEND_CSR_READ_BAD_ADD_ERR] = CNTR_ELEM("SendCsrReadBadAddrErr", 0, 0,
			CNTR_NORMAL,
			access_send_csr_पढ़ो_bad_addr_err_cnt),
[C_SEND_CSR_PARITY_ERR] = CNTR_ELEM("SendCsrParityErr", 0, 0,
			CNTR_NORMAL,
			access_send_csr_parity_cnt),
/* SendCtxtErrStatus */
[C_PIO_WRITE_OUT_OF_BOUNDS_ERR] = CNTR_ELEM("PioWriteOutOfBoundsErr", 0, 0,
			CNTR_NORMAL,
			access_pio_ग_लिखो_out_of_bounds_err_cnt),
[C_PIO_WRITE_OVERFLOW_ERR] = CNTR_ELEM("PioWriteOverflowErr", 0, 0,
			CNTR_NORMAL,
			access_pio_ग_लिखो_overflow_err_cnt),
[C_PIO_WRITE_CROSSES_BOUNDARY_ERR] = CNTR_ELEM("PioWriteCrossesBoundaryErr",
			0, 0, CNTR_NORMAL,
			access_pio_ग_लिखो_crosses_boundary_err_cnt),
[C_PIO_DISALLOWED_PACKET_ERR] = CNTR_ELEM("PioDisallowedPacketErr", 0, 0,
			CNTR_NORMAL,
			access_pio_disallowed_packet_err_cnt),
[C_PIO_INCONSISTENT_SOP_ERR] = CNTR_ELEM("PioInconsistentSopErr", 0, 0,
			CNTR_NORMAL,
			access_pio_inconsistent_sop_err_cnt),
/* SendDmaEngErrStatus */
[C_SDMA_HEADER_REQUEST_FIFO_COR_ERR] = CNTR_ELEM("SDmaHeaderRequestFifoCorErr",
			0, 0, CNTR_NORMAL,
			access_sdma_header_request_fअगरo_cor_err_cnt),
[C_SDMA_HEADER_STORAGE_COR_ERR] = CNTR_ELEM("SDmaHeaderStorageCorErr", 0, 0,
			CNTR_NORMAL,
			access_sdma_header_storage_cor_err_cnt),
[C_SDMA_PACKET_TRACKING_COR_ERR] = CNTR_ELEM("SDmaPacketTrackingCorErr", 0, 0,
			CNTR_NORMAL,
			access_sdma_packet_tracking_cor_err_cnt),
[C_SDMA_ASSEMBLY_COR_ERR] = CNTR_ELEM("SDmaAssemblyCorErr", 0, 0,
			CNTR_NORMAL,
			access_sdma_assembly_cor_err_cnt),
[C_SDMA_DESC_TABLE_COR_ERR] = CNTR_ELEM("SDmaDescTableCorErr", 0, 0,
			CNTR_NORMAL,
			access_sdma_desc_table_cor_err_cnt),
[C_SDMA_HEADER_REQUEST_FIFO_UNC_ERR] = CNTR_ELEM("SDmaHeaderRequestFifoUncErr",
			0, 0, CNTR_NORMAL,
			access_sdma_header_request_fअगरo_unc_err_cnt),
[C_SDMA_HEADER_STORAGE_UNC_ERR] = CNTR_ELEM("SDmaHeaderStorageUncErr", 0, 0,
			CNTR_NORMAL,
			access_sdma_header_storage_unc_err_cnt),
[C_SDMA_PACKET_TRACKING_UNC_ERR] = CNTR_ELEM("SDmaPacketTrackingUncErr", 0, 0,
			CNTR_NORMAL,
			access_sdma_packet_tracking_unc_err_cnt),
[C_SDMA_ASSEMBLY_UNC_ERR] = CNTR_ELEM("SDmaAssemblyUncErr", 0, 0,
			CNTR_NORMAL,
			access_sdma_assembly_unc_err_cnt),
[C_SDMA_DESC_TABLE_UNC_ERR] = CNTR_ELEM("SDmaDescTableUncErr", 0, 0,
			CNTR_NORMAL,
			access_sdma_desc_table_unc_err_cnt),
[C_SDMA_TIMEOUT_ERR] = CNTR_ELEM("SDmaTimeoutErr", 0, 0,
			CNTR_NORMAL,
			access_sdma_समयout_err_cnt),
[C_SDMA_HEADER_LENGTH_ERR] = CNTR_ELEM("SDmaHeaderLengthErr", 0, 0,
			CNTR_NORMAL,
			access_sdma_header_length_err_cnt),
[C_SDMA_HEADER_ADDRESS_ERR] = CNTR_ELEM("SDmaHeaderAddressErr", 0, 0,
			CNTR_NORMAL,
			access_sdma_header_address_err_cnt),
[C_SDMA_HEADER_SELECT_ERR] = CNTR_ELEM("SDmaHeaderSelectErr", 0, 0,
			CNTR_NORMAL,
			access_sdma_header_select_err_cnt),
[C_SMDA_RESERVED_9] = CNTR_ELEM("SDma Reserved 9", 0, 0,
			CNTR_NORMAL,
			access_sdma_reserved_9_err_cnt),
[C_SDMA_PACKET_DESC_OVERFLOW_ERR] = CNTR_ELEM("SDmaPacketDescOverflowErr", 0, 0,
			CNTR_NORMAL,
			access_sdma_packet_desc_overflow_err_cnt),
[C_SDMA_LENGTH_MISMATCH_ERR] = CNTR_ELEM("SDmaLengthMismatchErr", 0, 0,
			CNTR_NORMAL,
			access_sdma_length_mismatch_err_cnt),
[C_SDMA_HALT_ERR] = CNTR_ELEM("SDmaHaltErr", 0, 0,
			CNTR_NORMAL,
			access_sdma_halt_err_cnt),
[C_SDMA_MEM_READ_ERR] = CNTR_ELEM("SDmaMemReadErr", 0, 0,
			CNTR_NORMAL,
			access_sdma_mem_पढ़ो_err_cnt),
[C_SDMA_FIRST_DESC_ERR] = CNTR_ELEM("SDmaFirstDescErr", 0, 0,
			CNTR_NORMAL,
			access_sdma_first_desc_err_cnt),
[C_SDMA_TAIL_OUT_OF_BOUNDS_ERR] = CNTR_ELEM("SDmaTailOutOfBoundsErr", 0, 0,
			CNTR_NORMAL,
			access_sdma_tail_out_of_bounds_err_cnt),
[C_SDMA_TOO_LONG_ERR] = CNTR_ELEM("SDmaTooLongErr", 0, 0,
			CNTR_NORMAL,
			access_sdma_too_दीर्घ_err_cnt),
[C_SDMA_GEN_MISMATCH_ERR] = CNTR_ELEM("SDmaGenMismatchErr", 0, 0,
			CNTR_NORMAL,
			access_sdma_gen_mismatch_err_cnt),
[C_SDMA_WRONG_DW_ERR] = CNTR_ELEM("SDmaWrongDwErr", 0, 0,
			CNTR_NORMAL,
			access_sdma_wrong_dw_err_cnt),
पूर्ण;

अटल काष्ठा cntr_entry port_cntrs[PORT_CNTR_LAST] = अणु
[C_TX_UNSUP_VL] = TXE32_PORT_CNTR_ELEM(TxUnVLErr, SEND_UNSUP_VL_ERR_CNT,
			CNTR_NORMAL),
[C_TX_INVAL_LEN] = TXE32_PORT_CNTR_ELEM(TxInvalLen, SEND_LEN_ERR_CNT,
			CNTR_NORMAL),
[C_TX_MM_LEN_ERR] = TXE32_PORT_CNTR_ELEM(TxMMLenErr, SEND_MAX_MIN_LEN_ERR_CNT,
			CNTR_NORMAL),
[C_TX_UNDERRUN] = TXE32_PORT_CNTR_ELEM(TxUnderrun, SEND_UNDERRUN_CNT,
			CNTR_NORMAL),
[C_TX_FLOW_STALL] = TXE32_PORT_CNTR_ELEM(TxFlowStall, SEND_FLOW_STALL_CNT,
			CNTR_NORMAL),
[C_TX_DROPPED] = TXE32_PORT_CNTR_ELEM(TxDropped, SEND_DROPPED_PKT_CNT,
			CNTR_NORMAL),
[C_TX_HDR_ERR] = TXE32_PORT_CNTR_ELEM(TxHdrErr, SEND_HEADERS_ERR_CNT,
			CNTR_NORMAL),
[C_TX_PKT] = TXE64_PORT_CNTR_ELEM(TxPkt, SEND_DATA_PKT_CNT, CNTR_NORMAL),
[C_TX_WORDS] = TXE64_PORT_CNTR_ELEM(TxWords, SEND_DWORD_CNT, CNTR_NORMAL),
[C_TX_WAIT] = TXE64_PORT_CNTR_ELEM(TxWait, SEND_WAIT_CNT, CNTR_SYNTH),
[C_TX_FLIT_VL] = TXE64_PORT_CNTR_ELEM(TxFlitVL, SEND_DATA_VL0_CNT,
				      CNTR_SYNTH | CNTR_VL),
[C_TX_PKT_VL] = TXE64_PORT_CNTR_ELEM(TxPktVL, SEND_DATA_PKT_VL0_CNT,
				     CNTR_SYNTH | CNTR_VL),
[C_TX_WAIT_VL] = TXE64_PORT_CNTR_ELEM(TxWaitVL, SEND_WAIT_VL0_CNT,
				      CNTR_SYNTH | CNTR_VL),
[C_RX_PKT] = RXE64_PORT_CNTR_ELEM(RxPkt, RCV_DATA_PKT_CNT, CNTR_NORMAL),
[C_RX_WORDS] = RXE64_PORT_CNTR_ELEM(RxWords, RCV_DWORD_CNT, CNTR_NORMAL),
[C_SW_LINK_DOWN] = CNTR_ELEM("SwLinkDown", 0, 0, CNTR_SYNTH | CNTR_32BIT,
			     access_sw_link_dn_cnt),
[C_SW_LINK_UP] = CNTR_ELEM("SwLinkUp", 0, 0, CNTR_SYNTH | CNTR_32BIT,
			   access_sw_link_up_cnt),
[C_SW_UNKNOWN_FRAME] = CNTR_ELEM("UnknownFrame", 0, 0, CNTR_NORMAL,
				 access_sw_unknown_frame_cnt),
[C_SW_XMIT_DSCD] = CNTR_ELEM("XmitDscd", 0, 0, CNTR_SYNTH | CNTR_32BIT,
			     access_sw_xmit_discards),
[C_SW_XMIT_DSCD_VL] = CNTR_ELEM("XmitDscdVl", 0, 0,
				CNTR_SYNTH | CNTR_32BIT | CNTR_VL,
				access_sw_xmit_discards),
[C_SW_XMIT_CSTR_ERR] = CNTR_ELEM("XmitCstrErr", 0, 0, CNTR_SYNTH,
				 access_xmit_स्थिरraपूर्णांक_errs),
[C_SW_RCV_CSTR_ERR] = CNTR_ELEM("RcvCstrErr", 0, 0, CNTR_SYNTH,
				access_rcv_स्थिरraपूर्णांक_errs),
[C_SW_IBP_LOOP_PKTS] = SW_IBP_CNTR(LoopPkts, loop_pkts),
[C_SW_IBP_RC_RESENDS] = SW_IBP_CNTR(RcResend, rc_resends),
[C_SW_IBP_RNR_NAKS] = SW_IBP_CNTR(RnrNak, rnr_naks),
[C_SW_IBP_OTHER_NAKS] = SW_IBP_CNTR(OtherNak, other_naks),
[C_SW_IBP_RC_TIMEOUTS] = SW_IBP_CNTR(RcTimeOut, rc_समयouts),
[C_SW_IBP_PKT_DROPS] = SW_IBP_CNTR(PktDrop, pkt_drops),
[C_SW_IBP_DMA_WAIT] = SW_IBP_CNTR(DmaWait, dmaरुको),
[C_SW_IBP_RC_SEQNAK] = SW_IBP_CNTR(RcSeqNak, rc_seqnak),
[C_SW_IBP_RC_DUPREQ] = SW_IBP_CNTR(RcDupRew, rc_dupreq),
[C_SW_IBP_RDMA_SEQ] = SW_IBP_CNTR(RdmaSeq, rdma_seq),
[C_SW_IBP_UNALIGNED] = SW_IBP_CNTR(Unaligned, unaligned),
[C_SW_IBP_SEQ_NAK] = SW_IBP_CNTR(SeqNak, seq_naks),
[C_SW_IBP_RC_CRWAITS] = SW_IBP_CNTR(RcCrWait, rc_crरुकोs),
[C_SW_CPU_RC_ACKS] = CNTR_ELEM("RcAcks", 0, 0, CNTR_NORMAL,
			       access_sw_cpu_rc_acks),
[C_SW_CPU_RC_QACKS] = CNTR_ELEM("RcQacks", 0, 0, CNTR_NORMAL,
				access_sw_cpu_rc_qacks),
[C_SW_CPU_RC_DELAYED_COMP] = CNTR_ELEM("RcDelayComp", 0, 0, CNTR_NORMAL,
				       access_sw_cpu_rc_delayed_comp),
[OVR_LBL(0)] = OVR_ELM(0), [OVR_LBL(1)] = OVR_ELM(1),
[OVR_LBL(2)] = OVR_ELM(2), [OVR_LBL(3)] = OVR_ELM(3),
[OVR_LBL(4)] = OVR_ELM(4), [OVR_LBL(5)] = OVR_ELM(5),
[OVR_LBL(6)] = OVR_ELM(6), [OVR_LBL(7)] = OVR_ELM(7),
[OVR_LBL(8)] = OVR_ELM(8), [OVR_LBL(9)] = OVR_ELM(9),
[OVR_LBL(10)] = OVR_ELM(10), [OVR_LBL(11)] = OVR_ELM(11),
[OVR_LBL(12)] = OVR_ELM(12), [OVR_LBL(13)] = OVR_ELM(13),
[OVR_LBL(14)] = OVR_ELM(14), [OVR_LBL(15)] = OVR_ELM(15),
[OVR_LBL(16)] = OVR_ELM(16), [OVR_LBL(17)] = OVR_ELM(17),
[OVR_LBL(18)] = OVR_ELM(18), [OVR_LBL(19)] = OVR_ELM(19),
[OVR_LBL(20)] = OVR_ELM(20), [OVR_LBL(21)] = OVR_ELM(21),
[OVR_LBL(22)] = OVR_ELM(22), [OVR_LBL(23)] = OVR_ELM(23),
[OVR_LBL(24)] = OVR_ELM(24), [OVR_LBL(25)] = OVR_ELM(25),
[OVR_LBL(26)] = OVR_ELM(26), [OVR_LBL(27)] = OVR_ELM(27),
[OVR_LBL(28)] = OVR_ELM(28), [OVR_LBL(29)] = OVR_ELM(29),
[OVR_LBL(30)] = OVR_ELM(30), [OVR_LBL(31)] = OVR_ELM(31),
[OVR_LBL(32)] = OVR_ELM(32), [OVR_LBL(33)] = OVR_ELM(33),
[OVR_LBL(34)] = OVR_ELM(34), [OVR_LBL(35)] = OVR_ELM(35),
[OVR_LBL(36)] = OVR_ELM(36), [OVR_LBL(37)] = OVR_ELM(37),
[OVR_LBL(38)] = OVR_ELM(38), [OVR_LBL(39)] = OVR_ELM(39),
[OVR_LBL(40)] = OVR_ELM(40), [OVR_LBL(41)] = OVR_ELM(41),
[OVR_LBL(42)] = OVR_ELM(42), [OVR_LBL(43)] = OVR_ELM(43),
[OVR_LBL(44)] = OVR_ELM(44), [OVR_LBL(45)] = OVR_ELM(45),
[OVR_LBL(46)] = OVR_ELM(46), [OVR_LBL(47)] = OVR_ELM(47),
[OVR_LBL(48)] = OVR_ELM(48), [OVR_LBL(49)] = OVR_ELM(49),
[OVR_LBL(50)] = OVR_ELM(50), [OVR_LBL(51)] = OVR_ELM(51),
[OVR_LBL(52)] = OVR_ELM(52), [OVR_LBL(53)] = OVR_ELM(53),
[OVR_LBL(54)] = OVR_ELM(54), [OVR_LBL(55)] = OVR_ELM(55),
[OVR_LBL(56)] = OVR_ELM(56), [OVR_LBL(57)] = OVR_ELM(57),
[OVR_LBL(58)] = OVR_ELM(58), [OVR_LBL(59)] = OVR_ELM(59),
[OVR_LBL(60)] = OVR_ELM(60), [OVR_LBL(61)] = OVR_ELM(61),
[OVR_LBL(62)] = OVR_ELM(62), [OVR_LBL(63)] = OVR_ELM(63),
[OVR_LBL(64)] = OVR_ELM(64), [OVR_LBL(65)] = OVR_ELM(65),
[OVR_LBL(66)] = OVR_ELM(66), [OVR_LBL(67)] = OVR_ELM(67),
[OVR_LBL(68)] = OVR_ELM(68), [OVR_LBL(69)] = OVR_ELM(69),
[OVR_LBL(70)] = OVR_ELM(70), [OVR_LBL(71)] = OVR_ELM(71),
[OVR_LBL(72)] = OVR_ELM(72), [OVR_LBL(73)] = OVR_ELM(73),
[OVR_LBL(74)] = OVR_ELM(74), [OVR_LBL(75)] = OVR_ELM(75),
[OVR_LBL(76)] = OVR_ELM(76), [OVR_LBL(77)] = OVR_ELM(77),
[OVR_LBL(78)] = OVR_ELM(78), [OVR_LBL(79)] = OVR_ELM(79),
[OVR_LBL(80)] = OVR_ELM(80), [OVR_LBL(81)] = OVR_ELM(81),
[OVR_LBL(82)] = OVR_ELM(82), [OVR_LBL(83)] = OVR_ELM(83),
[OVR_LBL(84)] = OVR_ELM(84), [OVR_LBL(85)] = OVR_ELM(85),
[OVR_LBL(86)] = OVR_ELM(86), [OVR_LBL(87)] = OVR_ELM(87),
[OVR_LBL(88)] = OVR_ELM(88), [OVR_LBL(89)] = OVR_ELM(89),
[OVR_LBL(90)] = OVR_ELM(90), [OVR_LBL(91)] = OVR_ELM(91),
[OVR_LBL(92)] = OVR_ELM(92), [OVR_LBL(93)] = OVR_ELM(93),
[OVR_LBL(94)] = OVR_ELM(94), [OVR_LBL(95)] = OVR_ELM(95),
[OVR_LBL(96)] = OVR_ELM(96), [OVR_LBL(97)] = OVR_ELM(97),
[OVR_LBL(98)] = OVR_ELM(98), [OVR_LBL(99)] = OVR_ELM(99),
[OVR_LBL(100)] = OVR_ELM(100), [OVR_LBL(101)] = OVR_ELM(101),
[OVR_LBL(102)] = OVR_ELM(102), [OVR_LBL(103)] = OVR_ELM(103),
[OVR_LBL(104)] = OVR_ELM(104), [OVR_LBL(105)] = OVR_ELM(105),
[OVR_LBL(106)] = OVR_ELM(106), [OVR_LBL(107)] = OVR_ELM(107),
[OVR_LBL(108)] = OVR_ELM(108), [OVR_LBL(109)] = OVR_ELM(109),
[OVR_LBL(110)] = OVR_ELM(110), [OVR_LBL(111)] = OVR_ELM(111),
[OVR_LBL(112)] = OVR_ELM(112), [OVR_LBL(113)] = OVR_ELM(113),
[OVR_LBL(114)] = OVR_ELM(114), [OVR_LBL(115)] = OVR_ELM(115),
[OVR_LBL(116)] = OVR_ELM(116), [OVR_LBL(117)] = OVR_ELM(117),
[OVR_LBL(118)] = OVR_ELM(118), [OVR_LBL(119)] = OVR_ELM(119),
[OVR_LBL(120)] = OVR_ELM(120), [OVR_LBL(121)] = OVR_ELM(121),
[OVR_LBL(122)] = OVR_ELM(122), [OVR_LBL(123)] = OVR_ELM(123),
[OVR_LBL(124)] = OVR_ELM(124), [OVR_LBL(125)] = OVR_ELM(125),
[OVR_LBL(126)] = OVR_ELM(126), [OVR_LBL(127)] = OVR_ELM(127),
[OVR_LBL(128)] = OVR_ELM(128), [OVR_LBL(129)] = OVR_ELM(129),
[OVR_LBL(130)] = OVR_ELM(130), [OVR_LBL(131)] = OVR_ELM(131),
[OVR_LBL(132)] = OVR_ELM(132), [OVR_LBL(133)] = OVR_ELM(133),
[OVR_LBL(134)] = OVR_ELM(134), [OVR_LBL(135)] = OVR_ELM(135),
[OVR_LBL(136)] = OVR_ELM(136), [OVR_LBL(137)] = OVR_ELM(137),
[OVR_LBL(138)] = OVR_ELM(138), [OVR_LBL(139)] = OVR_ELM(139),
[OVR_LBL(140)] = OVR_ELM(140), [OVR_LBL(141)] = OVR_ELM(141),
[OVR_LBL(142)] = OVR_ELM(142), [OVR_LBL(143)] = OVR_ELM(143),
[OVR_LBL(144)] = OVR_ELM(144), [OVR_LBL(145)] = OVR_ELM(145),
[OVR_LBL(146)] = OVR_ELM(146), [OVR_LBL(147)] = OVR_ELM(147),
[OVR_LBL(148)] = OVR_ELM(148), [OVR_LBL(149)] = OVR_ELM(149),
[OVR_LBL(150)] = OVR_ELM(150), [OVR_LBL(151)] = OVR_ELM(151),
[OVR_LBL(152)] = OVR_ELM(152), [OVR_LBL(153)] = OVR_ELM(153),
[OVR_LBL(154)] = OVR_ELM(154), [OVR_LBL(155)] = OVR_ELM(155),
[OVR_LBL(156)] = OVR_ELM(156), [OVR_LBL(157)] = OVR_ELM(157),
[OVR_LBL(158)] = OVR_ELM(158), [OVR_LBL(159)] = OVR_ELM(159),
पूर्ण;

/* ======================================================================== */

/* वापस true अगर this is chip revision revision a */
पूर्णांक is_ax(काष्ठा hfi1_devdata *dd)
अणु
	u8 chip_rev_minor =
		dd->revision >> CCE_REVISION_CHIP_REV_MINOR_SHIFT
			& CCE_REVISION_CHIP_REV_MINOR_MASK;
	वापस (chip_rev_minor & 0xf0) == 0;
पूर्ण

/* वापस true अगर this is chip revision revision b */
पूर्णांक is_bx(काष्ठा hfi1_devdata *dd)
अणु
	u8 chip_rev_minor =
		dd->revision >> CCE_REVISION_CHIP_REV_MINOR_SHIFT
			& CCE_REVISION_CHIP_REV_MINOR_MASK;
	वापस (chip_rev_minor & 0xF0) == 0x10;
पूर्ण

/* वापस true is kernel urg disabled क्रम rcd */
bool is_urg_masked(काष्ठा hfi1_ctxtdata *rcd)
अणु
	u64 mask;
	u32 is = IS_RCVURGENT_START + rcd->ctxt;
	u8 bit = is % 64;

	mask = पढ़ो_csr(rcd->dd, CCE_INT_MASK + (8 * (is / 64)));
	वापस !(mask & BIT_ULL(bit));
पूर्ण

/*
 * Append string s to buffer buf.  Arguments curp and len are the current
 * position and reमुख्यing length, respectively.
 *
 * वापस 0 on success, 1 on out of room
 */
अटल पूर्णांक append_str(अक्षर *buf, अक्षर **curp, पूर्णांक *lenp, स्थिर अक्षर *s)
अणु
	अक्षर *p = *curp;
	पूर्णांक len = *lenp;
	पूर्णांक result = 0; /* success */
	अक्षर c;

	/* add a comma, अगर first in the buffer */
	अगर (p != buf) अणु
		अगर (len == 0) अणु
			result = 1; /* out of room */
			जाओ करोne;
		पूर्ण
		*p++ = ',';
		len--;
	पूर्ण

	/* copy the string */
	जबतक ((c = *s++) != 0) अणु
		अगर (len == 0) अणु
			result = 1; /* out of room */
			जाओ करोne;
		पूर्ण
		*p++ = c;
		len--;
	पूर्ण

करोne:
	/* ग_लिखो वापस values */
	*curp = p;
	*lenp = len;

	वापस result;
पूर्ण

/*
 * Using the given flag table, prपूर्णांक a comma separated string पूर्णांकo
 * the buffer.  End in '*' अगर the buffer is too लघु.
 */
अटल अक्षर *flag_string(अक्षर *buf, पूर्णांक buf_len, u64 flags,
			 काष्ठा flag_table *table, पूर्णांक table_size)
अणु
	अक्षर extra[32];
	अक्षर *p = buf;
	पूर्णांक len = buf_len;
	पूर्णांक no_room = 0;
	पूर्णांक i;

	/* make sure there is at least 2 so we can क्रमm "*" */
	अगर (len < 2)
		वापस "";

	len--;	/* leave room क्रम a nul */
	क्रम (i = 0; i < table_size; i++) अणु
		अगर (flags & table[i].flag) अणु
			no_room = append_str(buf, &p, &len, table[i].str);
			अगर (no_room)
				अवरोध;
			flags &= ~table[i].flag;
		पूर्ण
	पूर्ण

	/* any unकरोcumented bits left? */
	अगर (!no_room && flags) अणु
		snम_लिखो(extra, माप(extra), "bits 0x%llx", flags);
		no_room = append_str(buf, &p, &len, extra);
	पूर्ण

	/* add * अगर ran out of room */
	अगर (no_room) अणु
		/* may need to back up to add space क्रम a '*' */
		अगर (len == 0)
			--p;
		*p++ = '*';
	पूर्ण

	/* add final nul - space alपढ़ोy allocated above */
	*p = 0;
	वापस buf;
पूर्ण

/* first 8 CCE error पूर्णांकerrupt source names */
अटल स्थिर अक्षर * स्थिर cce_misc_names[] = अणु
	"CceErrInt",		/* 0 */
	"RxeErrInt",		/* 1 */
	"MiscErrInt",		/* 2 */
	"Reserved3",		/* 3 */
	"PioErrInt",		/* 4 */
	"SDmaErrInt",		/* 5 */
	"EgressErrInt",		/* 6 */
	"TxeErrInt"		/* 7 */
पूर्ण;

/*
 * Return the miscellaneous error पूर्णांकerrupt name.
 */
अटल अक्षर *is_misc_err_name(अक्षर *buf, माप_प्रकार bsize, अचिन्हित पूर्णांक source)
अणु
	अगर (source < ARRAY_SIZE(cce_misc_names))
		म_नकलन(buf, cce_misc_names[source], bsize);
	अन्यथा
		snम_लिखो(buf, bsize, "Reserved%u",
			 source + IS_GENERAL_ERR_START);

	वापस buf;
पूर्ण

/*
 * Return the SDMA engine error पूर्णांकerrupt name.
 */
अटल अक्षर *is_sdma_eng_err_name(अक्षर *buf, माप_प्रकार bsize, अचिन्हित पूर्णांक source)
अणु
	snम_लिखो(buf, bsize, "SDmaEngErrInt%u", source);
	वापस buf;
पूर्ण

/*
 * Return the send context error पूर्णांकerrupt name.
 */
अटल अक्षर *is_sendctxt_err_name(अक्षर *buf, माप_प्रकार bsize, अचिन्हित पूर्णांक source)
अणु
	snम_लिखो(buf, bsize, "SendCtxtErrInt%u", source);
	वापस buf;
पूर्ण

अटल स्थिर अक्षर * स्थिर various_names[] = अणु
	"PbcInt",
	"GpioAssertInt",
	"Qsfp1Int",
	"Qsfp2Int",
	"TCritInt"
पूर्ण;

/*
 * Return the various पूर्णांकerrupt name.
 */
अटल अक्षर *is_various_name(अक्षर *buf, माप_प्रकार bsize, अचिन्हित पूर्णांक source)
अणु
	अगर (source < ARRAY_SIZE(various_names))
		म_नकलन(buf, various_names[source], bsize);
	अन्यथा
		snम_लिखो(buf, bsize, "Reserved%u", source + IS_VARIOUS_START);
	वापस buf;
पूर्ण

/*
 * Return the DC पूर्णांकerrupt name.
 */
अटल अक्षर *is_dc_name(अक्षर *buf, माप_प्रकार bsize, अचिन्हित पूर्णांक source)
अणु
	अटल स्थिर अक्षर * स्थिर dc_पूर्णांक_names[] = अणु
		"common",
		"lcb",
		"8051",
		"lbm"	/* local block merge */
	पूर्ण;

	अगर (source < ARRAY_SIZE(dc_पूर्णांक_names))
		snम_लिखो(buf, bsize, "dc_%s_int", dc_पूर्णांक_names[source]);
	अन्यथा
		snम_लिखो(buf, bsize, "DCInt%u", source);
	वापस buf;
पूर्ण

अटल स्थिर अक्षर * स्थिर sdma_पूर्णांक_names[] = अणु
	"SDmaInt",
	"SdmaIdleInt",
	"SdmaProgressInt",
पूर्ण;

/*
 * Return the SDMA engine पूर्णांकerrupt name.
 */
अटल अक्षर *is_sdma_eng_name(अक्षर *buf, माप_प्रकार bsize, अचिन्हित पूर्णांक source)
अणु
	/* what पूर्णांकerrupt */
	अचिन्हित पूर्णांक what  = source / TXE_NUM_SDMA_ENGINES;
	/* which engine */
	अचिन्हित पूर्णांक which = source % TXE_NUM_SDMA_ENGINES;

	अगर (likely(what < 3))
		snम_लिखो(buf, bsize, "%s%u", sdma_पूर्णांक_names[what], which);
	अन्यथा
		snम_लिखो(buf, bsize, "Invalid SDMA interrupt %u", source);
	वापस buf;
पूर्ण

/*
 * Return the receive available पूर्णांकerrupt name.
 */
अटल अक्षर *is_rcv_avail_name(अक्षर *buf, माप_प्रकार bsize, अचिन्हित पूर्णांक source)
अणु
	snम_लिखो(buf, bsize, "RcvAvailInt%u", source);
	वापस buf;
पूर्ण

/*
 * Return the receive urgent पूर्णांकerrupt name.
 */
अटल अक्षर *is_rcv_urgent_name(अक्षर *buf, माप_प्रकार bsize, अचिन्हित पूर्णांक source)
अणु
	snम_लिखो(buf, bsize, "RcvUrgentInt%u", source);
	वापस buf;
पूर्ण

/*
 * Return the send credit पूर्णांकerrupt name.
 */
अटल अक्षर *is_send_credit_name(अक्षर *buf, माप_प्रकार bsize, अचिन्हित पूर्णांक source)
अणु
	snम_लिखो(buf, bsize, "SendCreditInt%u", source);
	वापस buf;
पूर्ण

/*
 * Return the reserved पूर्णांकerrupt name.
 */
अटल अक्षर *is_reserved_name(अक्षर *buf, माप_प्रकार bsize, अचिन्हित पूर्णांक source)
अणु
	snम_लिखो(buf, bsize, "Reserved%u", source + IS_RESERVED_START);
	वापस buf;
पूर्ण

अटल अक्षर *cce_err_status_string(अक्षर *buf, पूर्णांक buf_len, u64 flags)
अणु
	वापस flag_string(buf, buf_len, flags,
			   cce_err_status_flags,
			   ARRAY_SIZE(cce_err_status_flags));
पूर्ण

अटल अक्षर *rxe_err_status_string(अक्षर *buf, पूर्णांक buf_len, u64 flags)
अणु
	वापस flag_string(buf, buf_len, flags,
			   rxe_err_status_flags,
			   ARRAY_SIZE(rxe_err_status_flags));
पूर्ण

अटल अक्षर *misc_err_status_string(अक्षर *buf, पूर्णांक buf_len, u64 flags)
अणु
	वापस flag_string(buf, buf_len, flags, misc_err_status_flags,
			   ARRAY_SIZE(misc_err_status_flags));
पूर्ण

अटल अक्षर *pio_err_status_string(अक्षर *buf, पूर्णांक buf_len, u64 flags)
अणु
	वापस flag_string(buf, buf_len, flags,
			   pio_err_status_flags,
			   ARRAY_SIZE(pio_err_status_flags));
पूर्ण

अटल अक्षर *sdma_err_status_string(अक्षर *buf, पूर्णांक buf_len, u64 flags)
अणु
	वापस flag_string(buf, buf_len, flags,
			   sdma_err_status_flags,
			   ARRAY_SIZE(sdma_err_status_flags));
पूर्ण

अटल अक्षर *egress_err_status_string(अक्षर *buf, पूर्णांक buf_len, u64 flags)
अणु
	वापस flag_string(buf, buf_len, flags,
			   egress_err_status_flags,
			   ARRAY_SIZE(egress_err_status_flags));
पूर्ण

अटल अक्षर *egress_err_info_string(अक्षर *buf, पूर्णांक buf_len, u64 flags)
अणु
	वापस flag_string(buf, buf_len, flags,
			   egress_err_info_flags,
			   ARRAY_SIZE(egress_err_info_flags));
पूर्ण

अटल अक्षर *send_err_status_string(अक्षर *buf, पूर्णांक buf_len, u64 flags)
अणु
	वापस flag_string(buf, buf_len, flags,
			   send_err_status_flags,
			   ARRAY_SIZE(send_err_status_flags));
पूर्ण

अटल व्योम handle_cce_err(काष्ठा hfi1_devdata *dd, u32 unused, u64 reg)
अणु
	अक्षर buf[96];
	पूर्णांक i = 0;

	/*
	 * For most these errors, there is nothing that can be करोne except
	 * report or record it.
	 */
	dd_dev_info(dd, "CCE Error: %s\n",
		    cce_err_status_string(buf, माप(buf), reg));

	अगर ((reg & CCE_ERR_STATUS_CCE_CLI2_ASYNC_FIFO_PARITY_ERR_SMASK) &&
	    is_ax(dd) && (dd->icode != ICODE_FUNCTIONAL_SIMULATOR)) अणु
		/* this error requires a manual drop पूर्णांकo SPC मुक्तze mode */
		/* then a fix up */
		start_मुक्तze_handling(dd->pport, FREEZE_SELF);
	पूर्ण

	क्रम (i = 0; i < NUM_CCE_ERR_STATUS_COUNTERS; i++) अणु
		अगर (reg & (1ull << i)) अणु
			incr_cntr64(&dd->cce_err_status_cnt[i]);
			/* मुख्यtain a counter over all cce_err_status errors */
			incr_cntr64(&dd->sw_cce_err_status_aggregate);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Check counters क्रम receive errors that करो not have an पूर्णांकerrupt
 * associated with them.
 */
#घोषणा RCVERR_CHECK_TIME 10
अटल व्योम update_rcverr_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा hfi1_devdata *dd = from_समयr(dd, t, rcverr_समयr);
	काष्ठा hfi1_pportdata *ppd = dd->pport;
	u32 cur_ovfl_cnt = पढ़ो_dev_cntr(dd, C_RCV_OVF, CNTR_INVALID_VL);

	अगर (dd->rcv_ovfl_cnt < cur_ovfl_cnt &&
	    ppd->port_error_action & OPA_PI_MASK_EX_BUFFER_OVERRUN) अणु
		dd_dev_info(dd, "%s: PortErrorAction bounce\n", __func__);
		set_link_करोwn_reason(
		ppd, OPA_LINKDOWN_REASON_EXCESSIVE_BUFFER_OVERRUN, 0,
		OPA_LINKDOWN_REASON_EXCESSIVE_BUFFER_OVERRUN);
		queue_work(ppd->link_wq, &ppd->link_bounce_work);
	पूर्ण
	dd->rcv_ovfl_cnt = (u32)cur_ovfl_cnt;

	mod_समयr(&dd->rcverr_समयr, jअगरfies + HZ * RCVERR_CHECK_TIME);
पूर्ण

अटल पूर्णांक init_rcverr(काष्ठा hfi1_devdata *dd)
अणु
	समयr_setup(&dd->rcverr_समयr, update_rcverr_समयr, 0);
	/* Assume the hardware counter has been reset */
	dd->rcv_ovfl_cnt = 0;
	वापस mod_समयr(&dd->rcverr_समयr, jअगरfies + HZ * RCVERR_CHECK_TIME);
पूर्ण

अटल व्योम मुक्त_rcverr(काष्ठा hfi1_devdata *dd)
अणु
	अगर (dd->rcverr_समयr.function)
		del_समयr_sync(&dd->rcverr_समयr);
पूर्ण

अटल व्योम handle_rxe_err(काष्ठा hfi1_devdata *dd, u32 unused, u64 reg)
अणु
	अक्षर buf[96];
	पूर्णांक i = 0;

	dd_dev_info(dd, "Receive Error: %s\n",
		    rxe_err_status_string(buf, माप(buf), reg));

	अगर (reg & ALL_RXE_FREEZE_ERR) अणु
		पूर्णांक flags = 0;

		/*
		 * Freeze mode recovery is disabled क्रम the errors
		 * in RXE_FREEZE_ABORT_MASK
		 */
		अगर (is_ax(dd) && (reg & RXE_FREEZE_ABORT_MASK))
			flags = FREEZE_ABORT;

		start_मुक्तze_handling(dd->pport, flags);
	पूर्ण

	क्रम (i = 0; i < NUM_RCV_ERR_STATUS_COUNTERS; i++) अणु
		अगर (reg & (1ull << i))
			incr_cntr64(&dd->rcv_err_status_cnt[i]);
	पूर्ण
पूर्ण

अटल व्योम handle_misc_err(काष्ठा hfi1_devdata *dd, u32 unused, u64 reg)
अणु
	अक्षर buf[96];
	पूर्णांक i = 0;

	dd_dev_info(dd, "Misc Error: %s",
		    misc_err_status_string(buf, माप(buf), reg));
	क्रम (i = 0; i < NUM_MISC_ERR_STATUS_COUNTERS; i++) अणु
		अगर (reg & (1ull << i))
			incr_cntr64(&dd->misc_err_status_cnt[i]);
	पूर्ण
पूर्ण

अटल व्योम handle_pio_err(काष्ठा hfi1_devdata *dd, u32 unused, u64 reg)
अणु
	अक्षर buf[96];
	पूर्णांक i = 0;

	dd_dev_info(dd, "PIO Error: %s\n",
		    pio_err_status_string(buf, माप(buf), reg));

	अगर (reg & ALL_PIO_FREEZE_ERR)
		start_मुक्तze_handling(dd->pport, 0);

	क्रम (i = 0; i < NUM_SEND_PIO_ERR_STATUS_COUNTERS; i++) अणु
		अगर (reg & (1ull << i))
			incr_cntr64(&dd->send_pio_err_status_cnt[i]);
	पूर्ण
पूर्ण

अटल व्योम handle_sdma_err(काष्ठा hfi1_devdata *dd, u32 unused, u64 reg)
अणु
	अक्षर buf[96];
	पूर्णांक i = 0;

	dd_dev_info(dd, "SDMA Error: %s\n",
		    sdma_err_status_string(buf, माप(buf), reg));

	अगर (reg & ALL_SDMA_FREEZE_ERR)
		start_मुक्तze_handling(dd->pport, 0);

	क्रम (i = 0; i < NUM_SEND_DMA_ERR_STATUS_COUNTERS; i++) अणु
		अगर (reg & (1ull << i))
			incr_cntr64(&dd->send_dma_err_status_cnt[i]);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम __count_port_discards(काष्ठा hfi1_pportdata *ppd)
अणु
	incr_cntr64(&ppd->port_xmit_discards);
पूर्ण

अटल व्योम count_port_inactive(काष्ठा hfi1_devdata *dd)
अणु
	__count_port_discards(dd->pport);
पूर्ण

/*
 * We have had a "disallowed packet" error during egress. Determine the
 * पूर्णांकegrity check which failed, and update relevant error counter, etc.
 *
 * Note that the SEND_EGRESS_ERR_INFO रेजिस्टर has only a single
 * bit of state per पूर्णांकegrity check, and so we can miss the reason क्रम an
 * egress error अगर more than one packet fails the same पूर्णांकegrity check
 * since we cleared the corresponding bit in SEND_EGRESS_ERR_INFO.
 */
अटल व्योम handle_send_egress_err_info(काष्ठा hfi1_devdata *dd,
					पूर्णांक vl)
अणु
	काष्ठा hfi1_pportdata *ppd = dd->pport;
	u64 src = पढ़ो_csr(dd, SEND_EGRESS_ERR_SOURCE); /* पढ़ो first */
	u64 info = पढ़ो_csr(dd, SEND_EGRESS_ERR_INFO);
	अक्षर buf[96];

	/* clear करोwn all observed info as quickly as possible after पढ़ो */
	ग_लिखो_csr(dd, SEND_EGRESS_ERR_INFO, info);

	dd_dev_info(dd,
		    "Egress Error Info: 0x%llx, %s Egress Error Src 0x%llx\n",
		    info, egress_err_info_string(buf, माप(buf), info), src);

	/* Eventually add other counters क्रम each bit */
	अगर (info & PORT_DISCARD_EGRESS_ERRS) अणु
		पूर्णांक weight, i;

		/*
		 * Count all applicable bits as inभागidual errors and
		 * attribute them to the packet that triggered this handler.
		 * This may not be completely accurate due to limitations
		 * on the available hardware error inक्रमmation.  There is
		 * a single inक्रमmation रेजिस्टर and any number of error
		 * packets may have occurred and contributed to it beक्रमe
		 * this routine is called.  This means that:
		 * a) If multiple packets with the same error occur beक्रमe
		 *    this routine is called, earlier packets are missed.
		 *    There is only a single bit क्रम each error type.
		 * b) Errors may not be attributed to the correct VL.
		 *    The driver is attributing all bits in the info रेजिस्टर
		 *    to the packet that triggered this call, but bits
		 *    could be an accumulation of dअगरferent packets with
		 *    dअगरferent VLs.
		 * c) A single error packet may have multiple counts attached
		 *    to it.  There is no way क्रम the driver to know अगर
		 *    multiple bits set in the info रेजिस्टर are due to a
		 *    single packet or multiple packets.  The driver assumes
		 *    multiple packets.
		 */
		weight = hweight64(info & PORT_DISCARD_EGRESS_ERRS);
		क्रम (i = 0; i < weight; i++) अणु
			__count_port_discards(ppd);
			अगर (vl >= 0 && vl < TXE_NUM_DATA_VL)
				incr_cntr64(&ppd->port_xmit_discards_vl[vl]);
			अन्यथा अगर (vl == 15)
				incr_cntr64(&ppd->port_xmit_discards_vl
					    [C_VL_15]);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Input value is a bit position within the SEND_EGRESS_ERR_STATUS
 * रेजिस्टर. Does it represent a 'port inactive' error?
 */
अटल अंतरभूत पूर्णांक port_inactive_err(u64 posn)
अणु
	वापस (posn >= SEES(TX_LINKDOWN) &&
		posn <= SEES(TX_INCORRECT_LINK_STATE));
पूर्ण

/*
 * Input value is a bit position within the SEND_EGRESS_ERR_STATUS
 * रेजिस्टर. Does it represent a 'disallowed packet' error?
 */
अटल अंतरभूत पूर्णांक disallowed_pkt_err(पूर्णांक posn)
अणु
	वापस (posn >= SEES(TX_SDMA0_DISALLOWED_PACKET) &&
		posn <= SEES(TX_SDMA15_DISALLOWED_PACKET));
पूर्ण

/*
 * Input value is a bit position of one of the SDMA engine disallowed
 * packet errors.  Return which engine.  Use of this must be guarded by
 * disallowed_pkt_err().
 */
अटल अंतरभूत पूर्णांक disallowed_pkt_engine(पूर्णांक posn)
अणु
	वापस posn - SEES(TX_SDMA0_DISALLOWED_PACKET);
पूर्ण

/*
 * Translate an SDMA engine to a VL.  Return -1 अगर the tranlation cannot
 * be करोne.
 */
अटल पूर्णांक engine_to_vl(काष्ठा hfi1_devdata *dd, पूर्णांक engine)
अणु
	काष्ठा sdma_vl_map *m;
	पूर्णांक vl;

	/* range check */
	अगर (engine < 0 || engine >= TXE_NUM_SDMA_ENGINES)
		वापस -1;

	rcu_पढ़ो_lock();
	m = rcu_dereference(dd->sdma_map);
	vl = m->engine_to_vl[engine];
	rcu_पढ़ो_unlock();

	वापस vl;
पूर्ण

/*
 * Translate the send context (sofware index) पूर्णांकo a VL.  Return -1 अगर the
 * translation cannot be करोne.
 */
अटल पूर्णांक sc_to_vl(काष्ठा hfi1_devdata *dd, पूर्णांक sw_index)
अणु
	काष्ठा send_context_info *sci;
	काष्ठा send_context *sc;
	पूर्णांक i;

	sci = &dd->send_contexts[sw_index];

	/* there is no inक्रमmation क्रम user (PSM) and ack contexts */
	अगर ((sci->type != SC_KERNEL) && (sci->type != SC_VL15))
		वापस -1;

	sc = sci->sc;
	अगर (!sc)
		वापस -1;
	अगर (dd->vld[15].sc == sc)
		वापस 15;
	क्रम (i = 0; i < num_vls; i++)
		अगर (dd->vld[i].sc == sc)
			वापस i;

	वापस -1;
पूर्ण

अटल व्योम handle_egress_err(काष्ठा hfi1_devdata *dd, u32 unused, u64 reg)
अणु
	u64 reg_copy = reg, handled = 0;
	अक्षर buf[96];
	पूर्णांक i = 0;

	अगर (reg & ALL_TXE_EGRESS_FREEZE_ERR)
		start_मुक्तze_handling(dd->pport, 0);
	अन्यथा अगर (is_ax(dd) &&
		 (reg & SEND_EGRESS_ERR_STATUS_TX_CREDIT_RETURN_VL_ERR_SMASK) &&
		 (dd->icode != ICODE_FUNCTIONAL_SIMULATOR))
		start_मुक्तze_handling(dd->pport, 0);

	जबतक (reg_copy) अणु
		पूर्णांक posn = fls64(reg_copy);
		/* fls64() वापसs a 1-based offset, we want it zero based */
		पूर्णांक shअगरt = posn - 1;
		u64 mask = 1ULL << shअगरt;

		अगर (port_inactive_err(shअगरt)) अणु
			count_port_inactive(dd);
			handled |= mask;
		पूर्ण अन्यथा अगर (disallowed_pkt_err(shअगरt)) अणु
			पूर्णांक vl = engine_to_vl(dd, disallowed_pkt_engine(shअगरt));

			handle_send_egress_err_info(dd, vl);
			handled |= mask;
		पूर्ण
		reg_copy &= ~mask;
	पूर्ण

	reg &= ~handled;

	अगर (reg)
		dd_dev_info(dd, "Egress Error: %s\n",
			    egress_err_status_string(buf, माप(buf), reg));

	क्रम (i = 0; i < NUM_SEND_EGRESS_ERR_STATUS_COUNTERS; i++) अणु
		अगर (reg & (1ull << i))
			incr_cntr64(&dd->send_egress_err_status_cnt[i]);
	पूर्ण
पूर्ण

अटल व्योम handle_txe_err(काष्ठा hfi1_devdata *dd, u32 unused, u64 reg)
अणु
	अक्षर buf[96];
	पूर्णांक i = 0;

	dd_dev_info(dd, "Send Error: %s\n",
		    send_err_status_string(buf, माप(buf), reg));

	क्रम (i = 0; i < NUM_SEND_ERR_STATUS_COUNTERS; i++) अणु
		अगर (reg & (1ull << i))
			incr_cntr64(&dd->send_err_status_cnt[i]);
	पूर्ण
पूर्ण

/*
 * The maximum number of बार the error clear करोwn will loop beक्रमe
 * blocking a repeating error.  This value is arbitrary.
 */
#घोषणा MAX_CLEAR_COUNT 20

/*
 * Clear and handle an error रेजिस्टर.  All error पूर्णांकerrupts are funneled
 * through here to have a central location to correctly handle single-
 * or multi-shot errors.
 *
 * For non per-context रेजिस्टरs, call this routine with a context value
 * of 0 so the per-context offset is zero.
 *
 * If the handler loops too many बार, assume that something is wrong
 * and can't be fixed, so mask the error bits.
 */
अटल व्योम पूर्णांकerrupt_clear_करोwn(काष्ठा hfi1_devdata *dd,
				 u32 context,
				 स्थिर काष्ठा err_reg_info *eri)
अणु
	u64 reg;
	u32 count;

	/* पढ़ो in a loop until no more errors are seen */
	count = 0;
	जबतक (1) अणु
		reg = पढ़ो_kctxt_csr(dd, context, eri->status);
		अगर (reg == 0)
			अवरोध;
		ग_लिखो_kctxt_csr(dd, context, eri->clear, reg);
		अगर (likely(eri->handler))
			eri->handler(dd, context, reg);
		count++;
		अगर (count > MAX_CLEAR_COUNT) अणु
			u64 mask;

			dd_dev_err(dd, "Repeating %s bits 0x%llx - masking\n",
				   eri->desc, reg);
			/*
			 * Read-modअगरy-ग_लिखो so any other masked bits
			 * reमुख्य masked.
			 */
			mask = पढ़ो_kctxt_csr(dd, context, eri->mask);
			mask &= ~reg;
			ग_लिखो_kctxt_csr(dd, context, eri->mask, mask);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * CCE block "misc" पूर्णांकerrupt.  Source is < 16.
 */
अटल व्योम is_misc_err_पूर्णांक(काष्ठा hfi1_devdata *dd, अचिन्हित पूर्णांक source)
अणु
	स्थिर काष्ठा err_reg_info *eri = &misc_errs[source];

	अगर (eri->handler) अणु
		पूर्णांकerrupt_clear_करोwn(dd, 0, eri);
	पूर्ण अन्यथा अणु
		dd_dev_err(dd, "Unexpected misc interrupt (%u) - reserved\n",
			   source);
	पूर्ण
पूर्ण

अटल अक्षर *send_context_err_status_string(अक्षर *buf, पूर्णांक buf_len, u64 flags)
अणु
	वापस flag_string(buf, buf_len, flags,
			   sc_err_status_flags,
			   ARRAY_SIZE(sc_err_status_flags));
पूर्ण

/*
 * Send context error पूर्णांकerrupt.  Source (hw_context) is < 160.
 *
 * All send context errors cause the send context to halt.  The normal
 * clear-करोwn mechanism cannot be used because we cannot clear the
 * error bits until several other दीर्घ-running items are करोne first.
 * This is OK because with the context halted, nothing अन्यथा is going
 * to happen on it anyway.
 */
अटल व्योम is_sendctxt_err_पूर्णांक(काष्ठा hfi1_devdata *dd,
				अचिन्हित पूर्णांक hw_context)
अणु
	काष्ठा send_context_info *sci;
	काष्ठा send_context *sc;
	अक्षर flags[96];
	u64 status;
	u32 sw_index;
	पूर्णांक i = 0;
	अचिन्हित दीर्घ irq_flags;

	sw_index = dd->hw_to_sw[hw_context];
	अगर (sw_index >= dd->num_send_contexts) अणु
		dd_dev_err(dd,
			   "out of range sw index %u for send context %u\n",
			   sw_index, hw_context);
		वापस;
	पूर्ण
	sci = &dd->send_contexts[sw_index];
	spin_lock_irqsave(&dd->sc_lock, irq_flags);
	sc = sci->sc;
	अगर (!sc) अणु
		dd_dev_err(dd, "%s: context %u(%u): no sc?\n", __func__,
			   sw_index, hw_context);
		spin_unlock_irqrestore(&dd->sc_lock, irq_flags);
		वापस;
	पूर्ण

	/* tell the software that a halt has begun */
	sc_stop(sc, SCF_HALTED);

	status = पढ़ो_kctxt_csr(dd, hw_context, SEND_CTXT_ERR_STATUS);

	dd_dev_info(dd, "Send Context %u(%u) Error: %s\n", sw_index, hw_context,
		    send_context_err_status_string(flags, माप(flags),
						   status));

	अगर (status & SEND_CTXT_ERR_STATUS_PIO_DISALLOWED_PACKET_ERR_SMASK)
		handle_send_egress_err_info(dd, sc_to_vl(dd, sw_index));

	/*
	 * Automatically restart halted kernel contexts out of पूर्णांकerrupt
	 * context.  User contexts must ask the driver to restart the context.
	 */
	अगर (sc->type != SC_USER)
		queue_work(dd->pport->hfi1_wq, &sc->halt_work);
	spin_unlock_irqrestore(&dd->sc_lock, irq_flags);

	/*
	 * Update the counters क्रम the corresponding status bits.
	 * Note that these particular counters are aggregated over all
	 * 160 contexts.
	 */
	क्रम (i = 0; i < NUM_SEND_CTXT_ERR_STATUS_COUNTERS; i++) अणु
		अगर (status & (1ull << i))
			incr_cntr64(&dd->sw_ctxt_err_status_cnt[i]);
	पूर्ण
पूर्ण

अटल व्योम handle_sdma_eng_err(काष्ठा hfi1_devdata *dd,
				अचिन्हित पूर्णांक source, u64 status)
अणु
	काष्ठा sdma_engine *sde;
	पूर्णांक i = 0;

	sde = &dd->per_sdma[source];
#अगर_घोषित CONFIG_SDMA_VERBOSITY
	dd_dev_err(sde->dd, "CONFIG SDMA(%u) %s:%d %s()\n", sde->this_idx,
		   slashstrip(__खाता__), __LINE__, __func__);
	dd_dev_err(sde->dd, "CONFIG SDMA(%u) source: %u status 0x%llx\n",
		   sde->this_idx, source, (अचिन्हित दीर्घ दीर्घ)status);
#पूर्ण_अगर
	sde->err_cnt++;
	sdma_engine_error(sde, status);

	/*
	* Update the counters क्रम the corresponding status bits.
	* Note that these particular counters are aggregated over
	* all 16 DMA engines.
	*/
	क्रम (i = 0; i < NUM_SEND_DMA_ENG_ERR_STATUS_COUNTERS; i++) अणु
		अगर (status & (1ull << i))
			incr_cntr64(&dd->sw_send_dma_eng_err_status_cnt[i]);
	पूर्ण
पूर्ण

/*
 * CCE block SDMA error पूर्णांकerrupt.  Source is < 16.
 */
अटल व्योम is_sdma_eng_err_पूर्णांक(काष्ठा hfi1_devdata *dd, अचिन्हित पूर्णांक source)
अणु
#अगर_घोषित CONFIG_SDMA_VERBOSITY
	काष्ठा sdma_engine *sde = &dd->per_sdma[source];

	dd_dev_err(dd, "CONFIG SDMA(%u) %s:%d %s()\n", sde->this_idx,
		   slashstrip(__खाता__), __LINE__, __func__);
	dd_dev_err(dd, "CONFIG SDMA(%u) source: %u\n", sde->this_idx,
		   source);
	sdma_dumpstate(sde);
#पूर्ण_अगर
	पूर्णांकerrupt_clear_करोwn(dd, source, &sdma_eng_err);
पूर्ण

/*
 * CCE block "various" पूर्णांकerrupt.  Source is < 8.
 */
अटल व्योम is_various_पूर्णांक(काष्ठा hfi1_devdata *dd, अचिन्हित पूर्णांक source)
अणु
	स्थिर काष्ठा err_reg_info *eri = &various_err[source];

	/*
	 * TCritInt cannot go through पूर्णांकerrupt_clear_करोwn()
	 * because it is not a second tier पूर्णांकerrupt. The handler
	 * should be called directly.
	 */
	अगर (source == TCRIT_INT_SOURCE)
		handle_temp_err(dd);
	अन्यथा अगर (eri->handler)
		पूर्णांकerrupt_clear_करोwn(dd, 0, eri);
	अन्यथा
		dd_dev_info(dd,
			    "%s: Unimplemented/reserved interrupt %d\n",
			    __func__, source);
पूर्ण

अटल व्योम handle_qsfp_पूर्णांक(काष्ठा hfi1_devdata *dd, u32 src_ctx, u64 reg)
अणु
	/* src_ctx is always zero */
	काष्ठा hfi1_pportdata *ppd = dd->pport;
	अचिन्हित दीर्घ flags;
	u64 qsfp_पूर्णांक_mgmt = (u64)(QSFP_HFI0_INT_N | QSFP_HFI0_MODPRST_N);

	अगर (reg & QSFP_HFI0_MODPRST_N) अणु
		अगर (!qsfp_mod_present(ppd)) अणु
			dd_dev_info(dd, "%s: QSFP module removed\n",
				    __func__);

			ppd->driver_link_पढ़ोy = 0;
			/*
			 * Cable हटाओd, reset all our inक्रमmation about the
			 * cache and cable capabilities
			 */

			spin_lock_irqsave(&ppd->qsfp_info.qsfp_lock, flags);
			/*
			 * We करोn't set cache_refresh_required here as we expect
			 * an पूर्णांकerrupt when a cable is inserted
			 */
			ppd->qsfp_info.cache_valid = 0;
			ppd->qsfp_info.reset_needed = 0;
			ppd->qsfp_info.limiting_active = 0;
			spin_unlock_irqrestore(&ppd->qsfp_info.qsfp_lock,
					       flags);
			/* Invert the ModPresent pin now to detect plug-in */
			ग_लिखो_csr(dd, dd->hfi1_id ? ASIC_QSFP2_INVERT :
				  ASIC_QSFP1_INVERT, qsfp_पूर्णांक_mgmt);

			अगर ((ppd->offline_disabled_reason >
			  HFI1_ODR_MASK(
			  OPA_LINKDOWN_REASON_LOCAL_MEDIA_NOT_INSTALLED)) ||
			  (ppd->offline_disabled_reason ==
			  HFI1_ODR_MASK(OPA_LINKDOWN_REASON_NONE)))
				ppd->offline_disabled_reason =
				HFI1_ODR_MASK(
				OPA_LINKDOWN_REASON_LOCAL_MEDIA_NOT_INSTALLED);

			अगर (ppd->host_link_state == HLS_DN_POLL) अणु
				/*
				 * The link is still in POLL. This means
				 * that the normal link करोwn processing
				 * will not happen. We have to करो it here
				 * beक्रमe turning the DC off.
				 */
				queue_work(ppd->link_wq, &ppd->link_करोwn_work);
			पूर्ण
		पूर्ण अन्यथा अणु
			dd_dev_info(dd, "%s: QSFP module inserted\n",
				    __func__);

			spin_lock_irqsave(&ppd->qsfp_info.qsfp_lock, flags);
			ppd->qsfp_info.cache_valid = 0;
			ppd->qsfp_info.cache_refresh_required = 1;
			spin_unlock_irqrestore(&ppd->qsfp_info.qsfp_lock,
					       flags);

			/*
			 * Stop inversion of ModPresent pin to detect
			 * removal of the cable
			 */
			qsfp_पूर्णांक_mgmt &= ~(u64)QSFP_HFI0_MODPRST_N;
			ग_लिखो_csr(dd, dd->hfi1_id ? ASIC_QSFP2_INVERT :
				  ASIC_QSFP1_INVERT, qsfp_पूर्णांक_mgmt);

			ppd->offline_disabled_reason =
				HFI1_ODR_MASK(OPA_LINKDOWN_REASON_TRANSIENT);
		पूर्ण
	पूर्ण

	अगर (reg & QSFP_HFI0_INT_N) अणु
		dd_dev_info(dd, "%s: Interrupt received from QSFP module\n",
			    __func__);
		spin_lock_irqsave(&ppd->qsfp_info.qsfp_lock, flags);
		ppd->qsfp_info.check_पूर्णांकerrupt_flags = 1;
		spin_unlock_irqrestore(&ppd->qsfp_info.qsfp_lock, flags);
	पूर्ण

	/* Schedule the QSFP work only अगर there is a cable attached. */
	अगर (qsfp_mod_present(ppd))
		queue_work(ppd->link_wq, &ppd->qsfp_info.qsfp_work);
पूर्ण

अटल पूर्णांक request_host_lcb_access(काष्ठा hfi1_devdata *dd)
अणु
	पूर्णांक ret;

	ret = करो_8051_command(dd, HCMD_MISC,
			      (u64)HCMD_MISC_REQUEST_LCB_ACCESS <<
			      LOAD_DATA_FIELD_ID_SHIFT, शून्य);
	अगर (ret != HCMD_SUCCESS) अणु
		dd_dev_err(dd, "%s: command failed with error %d\n",
			   __func__, ret);
	पूर्ण
	वापस ret == HCMD_SUCCESS ? 0 : -EBUSY;
पूर्ण

अटल पूर्णांक request_8051_lcb_access(काष्ठा hfi1_devdata *dd)
अणु
	पूर्णांक ret;

	ret = करो_8051_command(dd, HCMD_MISC,
			      (u64)HCMD_MISC_GRANT_LCB_ACCESS <<
			      LOAD_DATA_FIELD_ID_SHIFT, शून्य);
	अगर (ret != HCMD_SUCCESS) अणु
		dd_dev_err(dd, "%s: command failed with error %d\n",
			   __func__, ret);
	पूर्ण
	वापस ret == HCMD_SUCCESS ? 0 : -EBUSY;
पूर्ण

/*
 * Set the LCB selector - allow host access.  The DCC selector always
 * poपूर्णांकs to the host.
 */
अटल अंतरभूत व्योम set_host_lcb_access(काष्ठा hfi1_devdata *dd)
अणु
	ग_लिखो_csr(dd, DC_DC8051_CFG_CSR_ACCESS_SEL,
		  DC_DC8051_CFG_CSR_ACCESS_SEL_DCC_SMASK |
		  DC_DC8051_CFG_CSR_ACCESS_SEL_LCB_SMASK);
पूर्ण

/*
 * Clear the LCB selector - allow 8051 access.  The DCC selector always
 * poपूर्णांकs to the host.
 */
अटल अंतरभूत व्योम set_8051_lcb_access(काष्ठा hfi1_devdata *dd)
अणु
	ग_लिखो_csr(dd, DC_DC8051_CFG_CSR_ACCESS_SEL,
		  DC_DC8051_CFG_CSR_ACCESS_SEL_DCC_SMASK);
पूर्ण

/*
 * Acquire LCB access from the 8051.  If the host alपढ़ोy has access,
 * just increment a counter.  Otherwise, inक्रमm the 8051 that the
 * host is taking access.
 *
 * Returns:
 *	0 on success
 *	-EBUSY अगर the 8051 has control and cannot be disturbed
 *	-त्रुटि_सं अगर unable to acquire access from the 8051
 */
पूर्णांक acquire_lcb_access(काष्ठा hfi1_devdata *dd, पूर्णांक sleep_ok)
अणु
	काष्ठा hfi1_pportdata *ppd = dd->pport;
	पूर्णांक ret = 0;

	/*
	 * Use the host link state lock so the operation of this routine
	 * अणु link state check, selector change, count increment पूर्ण can occur
	 * as a unit against a link state change.  Otherwise there is a
	 * race between the state change and the count increment.
	 */
	अगर (sleep_ok) अणु
		mutex_lock(&ppd->hls_lock);
	पूर्ण अन्यथा अणु
		जबतक (!mutex_trylock(&ppd->hls_lock))
			udelay(1);
	पूर्ण

	/* this access is valid only when the link is up */
	अगर (ppd->host_link_state & HLS_DOWN) अणु
		dd_dev_info(dd, "%s: link state %s not up\n",
			    __func__, link_state_name(ppd->host_link_state));
		ret = -EBUSY;
		जाओ करोne;
	पूर्ण

	अगर (dd->lcb_access_count == 0) अणु
		ret = request_host_lcb_access(dd);
		अगर (ret) अणु
			dd_dev_err(dd,
				   "%s: unable to acquire LCB access, err %d\n",
				   __func__, ret);
			जाओ करोne;
		पूर्ण
		set_host_lcb_access(dd);
	पूर्ण
	dd->lcb_access_count++;
करोne:
	mutex_unlock(&ppd->hls_lock);
	वापस ret;
पूर्ण

/*
 * Release LCB access by decrementing the use count.  If the count is moving
 * from 1 to 0, inक्रमm 8051 that it has control back.
 *
 * Returns:
 *	0 on success
 *	-त्रुटि_सं अगर unable to release access to the 8051
 */
पूर्णांक release_lcb_access(काष्ठा hfi1_devdata *dd, पूर्णांक sleep_ok)
अणु
	पूर्णांक ret = 0;

	/*
	 * Use the host link state lock because the acquire needed it.
	 * Here, we only need to keep अणु selector change, count decrement पूर्ण
	 * as a unit.
	 */
	अगर (sleep_ok) अणु
		mutex_lock(&dd->pport->hls_lock);
	पूर्ण अन्यथा अणु
		जबतक (!mutex_trylock(&dd->pport->hls_lock))
			udelay(1);
	पूर्ण

	अगर (dd->lcb_access_count == 0) अणु
		dd_dev_err(dd, "%s: LCB access count is zero.  Skipping.\n",
			   __func__);
		जाओ करोne;
	पूर्ण

	अगर (dd->lcb_access_count == 1) अणु
		set_8051_lcb_access(dd);
		ret = request_8051_lcb_access(dd);
		अगर (ret) अणु
			dd_dev_err(dd,
				   "%s: unable to release LCB access, err %d\n",
				   __func__, ret);
			/* restore host access अगर the grant didn't work */
			set_host_lcb_access(dd);
			जाओ करोne;
		पूर्ण
	पूर्ण
	dd->lcb_access_count--;
करोne:
	mutex_unlock(&dd->pport->hls_lock);
	वापस ret;
पूर्ण

/*
 * Initialize LCB access variables and state.  Called during driver load,
 * after most of the initialization is finished.
 *
 * The DC शेष is LCB access on क्रम the host.  The driver शेषs to
 * leaving access to the 8051.  Assign access now - this स्थिरrains the call
 * to this routine to be after all LCB set-up is करोne.  In particular, after
 * hf1_init_dd() -> set_up_पूर्णांकerrupts() -> clear_all_पूर्णांकerrupts()
 */
अटल व्योम init_lcb_access(काष्ठा hfi1_devdata *dd)
अणु
	dd->lcb_access_count = 0;
पूर्ण

/*
 * Write a response back to a 8051 request.
 */
अटल व्योम hreq_response(काष्ठा hfi1_devdata *dd, u8 वापस_code, u16 rsp_data)
अणु
	ग_लिखो_csr(dd, DC_DC8051_CFG_EXT_DEV_0,
		  DC_DC8051_CFG_EXT_DEV_0_COMPLETED_SMASK |
		  (u64)वापस_code <<
		  DC_DC8051_CFG_EXT_DEV_0_RETURN_CODE_SHIFT |
		  (u64)rsp_data << DC_DC8051_CFG_EXT_DEV_0_RSP_DATA_SHIFT);
पूर्ण

/*
 * Handle host requests from the 8051.
 */
अटल व्योम handle_8051_request(काष्ठा hfi1_pportdata *ppd)
अणु
	काष्ठा hfi1_devdata *dd = ppd->dd;
	u64 reg;
	u16 data = 0;
	u8 type;

	reg = पढ़ो_csr(dd, DC_DC8051_CFG_EXT_DEV_1);
	अगर ((reg & DC_DC8051_CFG_EXT_DEV_1_REQ_NEW_SMASK) == 0)
		वापस;	/* no request */

	/* zero out COMPLETED so the response is seen */
	ग_लिखो_csr(dd, DC_DC8051_CFG_EXT_DEV_0, 0);

	/* extract request details */
	type = (reg >> DC_DC8051_CFG_EXT_DEV_1_REQ_TYPE_SHIFT)
			& DC_DC8051_CFG_EXT_DEV_1_REQ_TYPE_MASK;
	data = (reg >> DC_DC8051_CFG_EXT_DEV_1_REQ_DATA_SHIFT)
			& DC_DC8051_CFG_EXT_DEV_1_REQ_DATA_MASK;

	चयन (type) अणु
	हाल HREQ_LOAD_CONFIG:
	हाल HREQ_SAVE_CONFIG:
	हाल HREQ_READ_CONFIG:
	हाल HREQ_SET_TX_EQ_ABS:
	हाल HREQ_SET_TX_EQ_REL:
	हाल HREQ_ENABLE:
		dd_dev_info(dd, "8051 request: request 0x%x not supported\n",
			    type);
		hreq_response(dd, HREQ_NOT_SUPPORTED, 0);
		अवरोध;
	हाल HREQ_LCB_RESET:
		/* Put the LCB, RX FPE and TX FPE पूर्णांकo reset */
		ग_लिखो_csr(dd, DCC_CFG_RESET, LCB_RX_FPE_TX_FPE_INTO_RESET);
		/* Make sure the ग_लिखो completed */
		(व्योम)पढ़ो_csr(dd, DCC_CFG_RESET);
		/* Hold the reset दीर्घ enough to take effect */
		udelay(1);
		/* Take the LCB, RX FPE and TX FPE out of reset */
		ग_लिखो_csr(dd, DCC_CFG_RESET, LCB_RX_FPE_TX_FPE_OUT_OF_RESET);
		hreq_response(dd, HREQ_SUCCESS, 0);

		अवरोध;
	हाल HREQ_CONFIG_DONE:
		hreq_response(dd, HREQ_SUCCESS, 0);
		अवरोध;

	हाल HREQ_INTERFACE_TEST:
		hreq_response(dd, HREQ_SUCCESS, data);
		अवरोध;
	शेष:
		dd_dev_err(dd, "8051 request: unknown request 0x%x\n", type);
		hreq_response(dd, HREQ_NOT_SUPPORTED, 0);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * Set up allocation unit vaulue.
 */
व्योम set_up_vau(काष्ठा hfi1_devdata *dd, u8 vau)
अणु
	u64 reg = पढ़ो_csr(dd, SEND_CM_GLOBAL_CREDIT);

	/* करो not modअगरy other values in the रेजिस्टर */
	reg &= ~SEND_CM_GLOBAL_CREDIT_AU_SMASK;
	reg |= (u64)vau << SEND_CM_GLOBAL_CREDIT_AU_SHIFT;
	ग_लिखो_csr(dd, SEND_CM_GLOBAL_CREDIT, reg);
पूर्ण

/*
 * Set up initial VL15 credits of the remote.  Assumes the rest of
 * the CM credit रेजिस्टरs are zero from a previous global or credit reset.
 * Shared limit क्रम VL15 will always be 0.
 */
व्योम set_up_vl15(काष्ठा hfi1_devdata *dd, u16 vl15buf)
अणु
	u64 reg = पढ़ो_csr(dd, SEND_CM_GLOBAL_CREDIT);

	/* set initial values क्रम total and shared credit limit */
	reg &= ~(SEND_CM_GLOBAL_CREDIT_TOTAL_CREDIT_LIMIT_SMASK |
		 SEND_CM_GLOBAL_CREDIT_SHARED_LIMIT_SMASK);

	/*
	 * Set total limit to be equal to VL15 credits.
	 * Leave shared limit at 0.
	 */
	reg |= (u64)vl15buf << SEND_CM_GLOBAL_CREDIT_TOTAL_CREDIT_LIMIT_SHIFT;
	ग_लिखो_csr(dd, SEND_CM_GLOBAL_CREDIT, reg);

	ग_लिखो_csr(dd, SEND_CM_CREDIT_VL15, (u64)vl15buf
		  << SEND_CM_CREDIT_VL15_DEDICATED_LIMIT_VL_SHIFT);
पूर्ण

/*
 * Zero all credit details from the previous connection and
 * reset the CM manager's पूर्णांकernal counters.
 */
व्योम reset_link_credits(काष्ठा hfi1_devdata *dd)
अणु
	पूर्णांक i;

	/* हटाओ all previous VL credit limits */
	क्रम (i = 0; i < TXE_NUM_DATA_VL; i++)
		ग_लिखो_csr(dd, SEND_CM_CREDIT_VL + (8 * i), 0);
	ग_लिखो_csr(dd, SEND_CM_CREDIT_VL15, 0);
	ग_लिखो_csr(dd, SEND_CM_GLOBAL_CREDIT, 0);
	/* reset the CM block */
	pio_send_control(dd, PSC_CM_RESET);
	/* reset cached value */
	dd->vl15buf_cached = 0;
पूर्ण

/* convert a vCU to a CU */
अटल u32 vcu_to_cu(u8 vcu)
अणु
	वापस 1 << vcu;
पूर्ण

/* convert a CU to a vCU */
अटल u8 cu_to_vcu(u32 cu)
अणु
	वापस ilog2(cu);
पूर्ण

/* convert a vAU to an AU */
अटल u32 vau_to_au(u8 vau)
अणु
	वापस 8 * (1 << vau);
पूर्ण

अटल व्योम set_linkup_शेषs(काष्ठा hfi1_pportdata *ppd)
अणु
	ppd->sm_trap_qp = 0x0;
	ppd->sa_qp = 0x1;
पूर्ण

/*
 * Graceful LCB shutकरोwn.  This leaves the LCB FIFOs in reset.
 */
अटल व्योम lcb_shutकरोwn(काष्ठा hfi1_devdata *dd, पूर्णांक पात)
अणु
	u64 reg;

	/* clear lcb run: LCB_CFG_RUN.EN = 0 */
	ग_लिखो_csr(dd, DC_LCB_CFG_RUN, 0);
	/* set tx fअगरo reset: LCB_CFG_TX_FIFOS_RESET.VAL = 1 */
	ग_लिखो_csr(dd, DC_LCB_CFG_TX_FIFOS_RESET,
		  1ull << DC_LCB_CFG_TX_FIFOS_RESET_VAL_SHIFT);
	/* set dcc reset csr: DCC_CFG_RESET.अणुreset_lcb,reset_rx_fpeपूर्ण = 1 */
	dd->lcb_err_en = पढ़ो_csr(dd, DC_LCB_ERR_EN);
	reg = पढ़ो_csr(dd, DCC_CFG_RESET);
	ग_लिखो_csr(dd, DCC_CFG_RESET, reg |
		  DCC_CFG_RESET_RESET_LCB | DCC_CFG_RESET_RESET_RX_FPE);
	(व्योम)पढ़ो_csr(dd, DCC_CFG_RESET); /* make sure the ग_लिखो completed */
	अगर (!पात) अणु
		udelay(1);    /* must hold क्रम the दीर्घer of 16cclks or 20ns */
		ग_लिखो_csr(dd, DCC_CFG_RESET, reg);
		ग_लिखो_csr(dd, DC_LCB_ERR_EN, dd->lcb_err_en);
	पूर्ण
पूर्ण

/*
 * This routine should be called after the link has been transitioned to
 * OFFLINE (OFFLINE state has the side effect of putting the SerDes पूर्णांकo
 * reset).
 *
 * The expectation is that the caller of this routine would have taken
 * care of properly transitioning the link पूर्णांकo the correct state.
 * NOTE: the caller needs to acquire the dd->dc8051_lock lock
 *       beक्रमe calling this function.
 */
अटल व्योम _dc_shutकरोwn(काष्ठा hfi1_devdata *dd)
अणु
	lockdep_निश्चित_held(&dd->dc8051_lock);

	अगर (dd->dc_shutकरोwn)
		वापस;

	dd->dc_shutकरोwn = 1;
	/* Shutकरोwn the LCB */
	lcb_shutकरोwn(dd, 1);
	/*
	 * Going to OFFLINE would have causes the 8051 to put the
	 * SerDes पूर्णांकo reset alपढ़ोy. Just need to shut करोwn the 8051,
	 * itself.
	 */
	ग_लिखो_csr(dd, DC_DC8051_CFG_RST, 0x1);
पूर्ण

अटल व्योम dc_shutकरोwn(काष्ठा hfi1_devdata *dd)
अणु
	mutex_lock(&dd->dc8051_lock);
	_dc_shutकरोwn(dd);
	mutex_unlock(&dd->dc8051_lock);
पूर्ण

/*
 * Calling this after the DC has been brought out of reset should not
 * करो any damage.
 * NOTE: the caller needs to acquire the dd->dc8051_lock lock
 *       beक्रमe calling this function.
 */
अटल व्योम _dc_start(काष्ठा hfi1_devdata *dd)
अणु
	lockdep_निश्चित_held(&dd->dc8051_lock);

	अगर (!dd->dc_shutकरोwn)
		वापस;

	/* Take the 8051 out of reset */
	ग_लिखो_csr(dd, DC_DC8051_CFG_RST, 0ull);
	/* Wait until 8051 is पढ़ोy */
	अगर (रुको_fm_पढ़ोy(dd, TIMEOUT_8051_START))
		dd_dev_err(dd, "%s: timeout starting 8051 firmware\n",
			   __func__);

	/* Take away reset क्रम LCB and RX FPE (set in lcb_shutकरोwn). */
	ग_लिखो_csr(dd, DCC_CFG_RESET, LCB_RX_FPE_TX_FPE_OUT_OF_RESET);
	/* lcb_shutकरोwn() with पात=1 करोes not restore these */
	ग_लिखो_csr(dd, DC_LCB_ERR_EN, dd->lcb_err_en);
	dd->dc_shutकरोwn = 0;
पूर्ण

अटल व्योम dc_start(काष्ठा hfi1_devdata *dd)
अणु
	mutex_lock(&dd->dc8051_lock);
	_dc_start(dd);
	mutex_unlock(&dd->dc8051_lock);
पूर्ण

/*
 * These LCB adjusपंचांगents are क्रम the Aurora SerDes core in the FPGA.
 */
अटल व्योम adjust_lcb_क्रम_fpga_serdes(काष्ठा hfi1_devdata *dd)
अणु
	u64 rx_radr, tx_radr;
	u32 version;

	अगर (dd->icode != ICODE_FPGA_EMULATION)
		वापस;

	/*
	 * These LCB शेषs on emulator _s are good, nothing to करो here:
	 *	LCB_CFG_TX_FIFOS_RADR
	 *	LCB_CFG_RX_FIFOS_RADR
	 *	LCB_CFG_LN_DCLK
	 *	LCB_CFG_IGNORE_LOST_RCLK
	 */
	अगर (is_emulator_s(dd))
		वापस;
	/* अन्यथा this is _p */

	version = emulator_rev(dd);
	अगर (!is_ax(dd))
		version = 0x2d;	/* all B0 use 0x2d or higher settings */

	अगर (version <= 0x12) अणु
		/* release 0x12 and below */

		/*
		 * LCB_CFG_RX_FIFOS_RADR.RST_VAL = 0x9
		 * LCB_CFG_RX_FIFOS_RADR.OK_TO_JUMP_VAL = 0x9
		 * LCB_CFG_RX_FIFOS_RADR.DO_NOT_JUMP_VAL = 0xa
		 */
		rx_radr =
		      0xaull << DC_LCB_CFG_RX_FIFOS_RADR_DO_NOT_JUMP_VAL_SHIFT
		    | 0x9ull << DC_LCB_CFG_RX_FIFOS_RADR_OK_TO_JUMP_VAL_SHIFT
		    | 0x9ull << DC_LCB_CFG_RX_FIFOS_RADR_RST_VAL_SHIFT;
		/*
		 * LCB_CFG_TX_FIFOS_RADR.ON_REINIT = 0 (शेष)
		 * LCB_CFG_TX_FIFOS_RADR.RST_VAL = 6
		 */
		tx_radr = 6ull << DC_LCB_CFG_TX_FIFOS_RADR_RST_VAL_SHIFT;
	पूर्ण अन्यथा अगर (version <= 0x18) अणु
		/* release 0x13 up to 0x18 */
		/* LCB_CFG_RX_FIFOS_RADR = 0x988 */
		rx_radr =
		      0x9ull << DC_LCB_CFG_RX_FIFOS_RADR_DO_NOT_JUMP_VAL_SHIFT
		    | 0x8ull << DC_LCB_CFG_RX_FIFOS_RADR_OK_TO_JUMP_VAL_SHIFT
		    | 0x8ull << DC_LCB_CFG_RX_FIFOS_RADR_RST_VAL_SHIFT;
		tx_radr = 7ull << DC_LCB_CFG_TX_FIFOS_RADR_RST_VAL_SHIFT;
	पूर्ण अन्यथा अगर (version == 0x19) अणु
		/* release 0x19 */
		/* LCB_CFG_RX_FIFOS_RADR = 0xa99 */
		rx_radr =
		      0xAull << DC_LCB_CFG_RX_FIFOS_RADR_DO_NOT_JUMP_VAL_SHIFT
		    | 0x9ull << DC_LCB_CFG_RX_FIFOS_RADR_OK_TO_JUMP_VAL_SHIFT
		    | 0x9ull << DC_LCB_CFG_RX_FIFOS_RADR_RST_VAL_SHIFT;
		tx_radr = 3ull << DC_LCB_CFG_TX_FIFOS_RADR_RST_VAL_SHIFT;
	पूर्ण अन्यथा अगर (version == 0x1a) अणु
		/* release 0x1a */
		/* LCB_CFG_RX_FIFOS_RADR = 0x988 */
		rx_radr =
		      0x9ull << DC_LCB_CFG_RX_FIFOS_RADR_DO_NOT_JUMP_VAL_SHIFT
		    | 0x8ull << DC_LCB_CFG_RX_FIFOS_RADR_OK_TO_JUMP_VAL_SHIFT
		    | 0x8ull << DC_LCB_CFG_RX_FIFOS_RADR_RST_VAL_SHIFT;
		tx_radr = 7ull << DC_LCB_CFG_TX_FIFOS_RADR_RST_VAL_SHIFT;
		ग_लिखो_csr(dd, DC_LCB_CFG_LN_DCLK, 1ull);
	पूर्ण अन्यथा अणु
		/* release 0x1b and higher */
		/* LCB_CFG_RX_FIFOS_RADR = 0x877 */
		rx_radr =
		      0x8ull << DC_LCB_CFG_RX_FIFOS_RADR_DO_NOT_JUMP_VAL_SHIFT
		    | 0x7ull << DC_LCB_CFG_RX_FIFOS_RADR_OK_TO_JUMP_VAL_SHIFT
		    | 0x7ull << DC_LCB_CFG_RX_FIFOS_RADR_RST_VAL_SHIFT;
		tx_radr = 3ull << DC_LCB_CFG_TX_FIFOS_RADR_RST_VAL_SHIFT;
	पूर्ण

	ग_लिखो_csr(dd, DC_LCB_CFG_RX_FIFOS_RADR, rx_radr);
	/* LCB_CFG_IGNORE_LOST_RCLK.EN = 1 */
	ग_लिखो_csr(dd, DC_LCB_CFG_IGNORE_LOST_RCLK,
		  DC_LCB_CFG_IGNORE_LOST_RCLK_EN_SMASK);
	ग_लिखो_csr(dd, DC_LCB_CFG_TX_FIFOS_RADR, tx_radr);
पूर्ण

/*
 * Handle a SMA idle message
 *
 * This is a work-queue function outside of the पूर्णांकerrupt.
 */
व्योम handle_sma_message(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hfi1_pportdata *ppd = container_of(work, काष्ठा hfi1_pportdata,
							sma_message_work);
	काष्ठा hfi1_devdata *dd = ppd->dd;
	u64 msg;
	पूर्णांक ret;

	/*
	 * msg is bytes 1-4 of the 40-bit idle message - the command code
	 * is stripped off
	 */
	ret = पढ़ो_idle_sma(dd, &msg);
	अगर (ret)
		वापस;
	dd_dev_info(dd, "%s: SMA message 0x%llx\n", __func__, msg);
	/*
	 * React to the SMA message.  Byte[1] (0 क्रम us) is the command.
	 */
	चयन (msg & 0xff) अणु
	हाल SMA_IDLE_ARM:
		/*
		 * See OPAv1 table 9-14 - HFI and External Switch Ports Key
		 * State Transitions
		 *
		 * Only expected in INIT or ARMED, discard otherwise.
		 */
		अगर (ppd->host_link_state & (HLS_UP_INIT | HLS_UP_ARMED))
			ppd->neighbor_normal = 1;
		अवरोध;
	हाल SMA_IDLE_ACTIVE:
		/*
		 * See OPAv1 table 9-14 - HFI and External Switch Ports Key
		 * State Transitions
		 *
		 * Can activate the node.  Discard otherwise.
		 */
		अगर (ppd->host_link_state == HLS_UP_ARMED &&
		    ppd->is_active_optimize_enabled) अणु
			ppd->neighbor_normal = 1;
			ret = set_link_state(ppd, HLS_UP_ACTIVE);
			अगर (ret)
				dd_dev_err(
					dd,
					"%s: received Active SMA idle message, couldn't set link to Active\n",
					__func__);
		पूर्ण
		अवरोध;
	शेष:
		dd_dev_err(dd,
			   "%s: received unexpected SMA idle message 0x%llx\n",
			   __func__, msg);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम adjust_rcvctrl(काष्ठा hfi1_devdata *dd, u64 add, u64 clear)
अणु
	u64 rcvctrl;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dd->rcvctrl_lock, flags);
	rcvctrl = पढ़ो_csr(dd, RCV_CTRL);
	rcvctrl |= add;
	rcvctrl &= ~clear;
	ग_लिखो_csr(dd, RCV_CTRL, rcvctrl);
	spin_unlock_irqrestore(&dd->rcvctrl_lock, flags);
पूर्ण

अटल अंतरभूत व्योम add_rcvctrl(काष्ठा hfi1_devdata *dd, u64 add)
अणु
	adjust_rcvctrl(dd, add, 0);
पूर्ण

अटल अंतरभूत व्योम clear_rcvctrl(काष्ठा hfi1_devdata *dd, u64 clear)
अणु
	adjust_rcvctrl(dd, 0, clear);
पूर्ण

/*
 * Called from all पूर्णांकerrupt handlers to start handling an SPC मुक्तze.
 */
व्योम start_मुक्तze_handling(काष्ठा hfi1_pportdata *ppd, पूर्णांक flags)
अणु
	काष्ठा hfi1_devdata *dd = ppd->dd;
	काष्ठा send_context *sc;
	पूर्णांक i;
	पूर्णांक sc_flags;

	अगर (flags & FREEZE_SELF)
		ग_लिखो_csr(dd, CCE_CTRL, CCE_CTRL_SPC_FREEZE_SMASK);

	/* enter frozen mode */
	dd->flags |= HFI1_FROZEN;

	/* notअगरy all SDMA engines that they are going पूर्णांकo a मुक्तze */
	sdma_मुक्तze_notअगरy(dd, !!(flags & FREEZE_LINK_DOWN));

	sc_flags = SCF_FROZEN | SCF_HALTED | (flags & FREEZE_LINK_DOWN ?
					      SCF_LINK_DOWN : 0);
	/* करो halt pre-handling on all enabled send contexts */
	क्रम (i = 0; i < dd->num_send_contexts; i++) अणु
		sc = dd->send_contexts[i].sc;
		अगर (sc && (sc->flags & SCF_ENABLED))
			sc_stop(sc, sc_flags);
	पूर्ण

	/* Send context are frozen. Notअगरy user space */
	hfi1_set_uevent_bits(ppd, _HFI1_EVENT_FROZEN_BIT);

	अगर (flags & FREEZE_ABORT) अणु
		dd_dev_err(dd,
			   "Aborted freeze recovery. Please REBOOT system\n");
		वापस;
	पूर्ण
	/* queue non-पूर्णांकerrupt handler */
	queue_work(ppd->hfi1_wq, &ppd->मुक्तze_work);
पूर्ण

/*
 * Wait until all 4 sub-blocks indicate that they have frozen or unfrozen,
 * depending on the "freeze" parameter.
 *
 * No need to वापस an error अगर it बार out, our only option
 * is to proceed anyway.
 */
अटल व्योम रुको_क्रम_मुक्तze_status(काष्ठा hfi1_devdata *dd, पूर्णांक मुक्तze)
अणु
	अचिन्हित दीर्घ समयout;
	u64 reg;

	समयout = jअगरfies + msecs_to_jअगरfies(FREEZE_STATUS_TIMEOUT);
	जबतक (1) अणु
		reg = पढ़ो_csr(dd, CCE_STATUS);
		अगर (मुक्तze) अणु
			/* रुकोing until all indicators are set */
			अगर ((reg & ALL_FROZE) == ALL_FROZE)
				वापस;	/* all करोne */
		पूर्ण अन्यथा अणु
			/* रुकोing until all indicators are clear */
			अगर ((reg & ALL_FROZE) == 0)
				वापस; /* all करोne */
		पूर्ण

		अगर (समय_after(jअगरfies, समयout)) अणु
			dd_dev_err(dd,
				   "Time out waiting for SPC %sfreeze, bits 0x%llx, expecting 0x%llx, continuing",
				   मुक्तze ? "" : "un", reg & ALL_FROZE,
				   मुक्तze ? ALL_FROZE : 0ull);
			वापस;
		पूर्ण
		usleep_range(80, 120);
	पूर्ण
पूर्ण

/*
 * Do all मुक्तze handling क्रम the RXE block.
 */
अटल व्योम rxe_मुक्तze(काष्ठा hfi1_devdata *dd)
अणु
	पूर्णांक i;
	काष्ठा hfi1_ctxtdata *rcd;

	/* disable port */
	clear_rcvctrl(dd, RCV_CTRL_RCV_PORT_ENABLE_SMASK);

	/* disable all receive contexts */
	क्रम (i = 0; i < dd->num_rcv_contexts; i++) अणु
		rcd = hfi1_rcd_get_by_index(dd, i);
		hfi1_rcvctrl(dd, HFI1_RCVCTRL_CTXT_DIS, rcd);
		hfi1_rcd_put(rcd);
	पूर्ण
पूर्ण

/*
 * Unमुक्तze handling क्रम the RXE block - kernel contexts only.
 * This will also enable the port.  User contexts will करो unमुक्तze
 * handling on a per-context basis as they call पूर्णांकo the driver.
 *
 */
अटल व्योम rxe_kernel_unमुक्तze(काष्ठा hfi1_devdata *dd)
अणु
	u32 rcvmask;
	u16 i;
	काष्ठा hfi1_ctxtdata *rcd;

	/* enable all kernel contexts */
	क्रम (i = 0; i < dd->num_rcv_contexts; i++) अणु
		rcd = hfi1_rcd_get_by_index(dd, i);

		/* Ensure all non-user contexts(including vnic) are enabled */
		अगर (!rcd ||
		    (i >= dd->first_dyn_alloc_ctxt && !rcd->is_vnic)) अणु
			hfi1_rcd_put(rcd);
			जारी;
		पूर्ण
		rcvmask = HFI1_RCVCTRL_CTXT_ENB;
		/* HFI1_RCVCTRL_TAILUPD_[ENB|DIS] needs to be set explicitly */
		rcvmask |= hfi1_rcvhdrtail_kvaddr(rcd) ?
			HFI1_RCVCTRL_TAILUPD_ENB : HFI1_RCVCTRL_TAILUPD_DIS;
		hfi1_rcvctrl(dd, rcvmask, rcd);
		hfi1_rcd_put(rcd);
	पूर्ण

	/* enable port */
	add_rcvctrl(dd, RCV_CTRL_RCV_PORT_ENABLE_SMASK);
पूर्ण

/*
 * Non-पूर्णांकerrupt SPC मुक्तze handling.
 *
 * This is a work-queue function outside of the triggering पूर्णांकerrupt.
 */
व्योम handle_मुक्तze(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hfi1_pportdata *ppd = container_of(work, काष्ठा hfi1_pportdata,
								मुक्तze_work);
	काष्ठा hfi1_devdata *dd = ppd->dd;

	/* रुको क्रम मुक्तze indicators on all affected blocks */
	रुको_क्रम_मुक्तze_status(dd, 1);

	/* SPC is now frozen */

	/* करो send PIO मुक्तze steps */
	pio_मुक्तze(dd);

	/* करो send DMA मुक्तze steps */
	sdma_मुक्तze(dd);

	/* करो send egress मुक्तze steps - nothing to करो */

	/* करो receive मुक्तze steps */
	rxe_मुक्तze(dd);

	/*
	 * Unमुक्तze the hardware - clear the मुक्तze, रुको क्रम each
	 * block's frozen bit to clear, then clear the frozen flag.
	 */
	ग_लिखो_csr(dd, CCE_CTRL, CCE_CTRL_SPC_UNFREEZE_SMASK);
	रुको_क्रम_मुक्तze_status(dd, 0);

	अगर (is_ax(dd)) अणु
		ग_लिखो_csr(dd, CCE_CTRL, CCE_CTRL_SPC_FREEZE_SMASK);
		रुको_क्रम_मुक्तze_status(dd, 1);
		ग_लिखो_csr(dd, CCE_CTRL, CCE_CTRL_SPC_UNFREEZE_SMASK);
		रुको_क्रम_मुक्तze_status(dd, 0);
	पूर्ण

	/* करो send PIO unमुक्तze steps क्रम kernel contexts */
	pio_kernel_unमुक्तze(dd);

	/* करो send DMA unमुक्तze steps */
	sdma_unमुक्तze(dd);

	/* करो send egress unमुक्तze steps - nothing to करो */

	/* करो receive unमुक्तze steps क्रम kernel contexts */
	rxe_kernel_unमुक्तze(dd);

	/*
	 * The unमुक्तze procedure touches global device रेजिस्टरs when
	 * it disables and re-enables RXE. Mark the device unfrozen
	 * after all that is करोne so other parts of the driver रुकोing
	 * क्रम the device to unमुक्तze करोn't करो things out of order.
	 *
	 * The above implies that the meaning of HFI1_FROZEN flag is
	 * "Device has gone पूर्णांकo मुक्तze mode and मुक्तze mode handling
	 * is still in progress."
	 *
	 * The flag will be हटाओd when मुक्तze mode processing has
	 * completed.
	 */
	dd->flags &= ~HFI1_FROZEN;
	wake_up(&dd->event_queue);

	/* no दीर्घer frozen */
पूर्ण

/**
 * update_xmit_counters - update PortXmitWait/PortVlXmitWait
 * counters.
 * @ppd: info of physical Hfi port
 * @link_width: new link width after link up or करोwngrade
 *
 * Update the PortXmitWait and PortVlXmitWait counters after
 * a link up or करोwngrade event to reflect a link width change.
 */
अटल व्योम update_xmit_counters(काष्ठा hfi1_pportdata *ppd, u16 link_width)
अणु
	पूर्णांक i;
	u16 tx_width;
	u16 link_speed;

	tx_width = tx_link_width(link_width);
	link_speed = get_link_speed(ppd->link_speed_active);

	/*
	 * There are C_VL_COUNT number of PortVLXmitWait counters.
	 * Adding 1 to C_VL_COUNT to include the PortXmitWait counter.
	 */
	क्रम (i = 0; i < C_VL_COUNT + 1; i++)
		get_xmit_रुको_counters(ppd, tx_width, link_speed, i);
पूर्ण

/*
 * Handle a link up पूर्णांकerrupt from the 8051.
 *
 * This is a work-queue function outside of the पूर्णांकerrupt.
 */
व्योम handle_link_up(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hfi1_pportdata *ppd = container_of(work, काष्ठा hfi1_pportdata,
						  link_up_work);
	काष्ठा hfi1_devdata *dd = ppd->dd;

	set_link_state(ppd, HLS_UP_INIT);

	/* cache the पढ़ो of DC_LCB_STS_ROUND_TRIP_LTP_CNT */
	पढ़ो_ltp_rtt(dd);
	/*
	 * OPA specअगरies that certain counters are cleared on a transition
	 * to link up, so करो that.
	 */
	clear_linkup_counters(dd);
	/*
	 * And (re)set link up शेष values.
	 */
	set_linkup_शेषs(ppd);

	/*
	 * Set VL15 credits. Use cached value from verअगरy cap पूर्णांकerrupt.
	 * In हाल of quick linkup or simulator, vl15 value will be set by
	 * handle_linkup_change. VerअगरyCap पूर्णांकerrupt handler will not be
	 * called in those scenarios.
	 */
	अगर (!(quick_linkup || dd->icode == ICODE_FUNCTIONAL_SIMULATOR))
		set_up_vl15(dd, dd->vl15buf_cached);

	/* enक्रमce link speed enabled */
	अगर ((ppd->link_speed_active & ppd->link_speed_enabled) == 0) अणु
		/* oops - current speed is not enabled, bounce */
		dd_dev_err(dd,
			   "Link speed active 0x%x is outside enabled 0x%x, downing link\n",
			   ppd->link_speed_active, ppd->link_speed_enabled);
		set_link_करोwn_reason(ppd, OPA_LINKDOWN_REASON_SPEED_POLICY, 0,
				     OPA_LINKDOWN_REASON_SPEED_POLICY);
		set_link_state(ppd, HLS_DN_OFFLINE);
		start_link(ppd);
	पूर्ण
पूर्ण

/*
 * Several pieces of LNI inक्रमmation were cached क्रम SMA in ppd.
 * Reset these on link करोwn
 */
अटल व्योम reset_neighbor_info(काष्ठा hfi1_pportdata *ppd)
अणु
	ppd->neighbor_guid = 0;
	ppd->neighbor_port_number = 0;
	ppd->neighbor_type = 0;
	ppd->neighbor_fm_security = 0;
पूर्ण

अटल स्थिर अक्षर * स्थिर link_करोwn_reason_strs[] = अणु
	[OPA_LINKDOWN_REASON_NONE] = "None",
	[OPA_LINKDOWN_REASON_RCV_ERROR_0] = "Receive error 0",
	[OPA_LINKDOWN_REASON_BAD_PKT_LEN] = "Bad packet length",
	[OPA_LINKDOWN_REASON_PKT_TOO_LONG] = "Packet too long",
	[OPA_LINKDOWN_REASON_PKT_TOO_SHORT] = "Packet too short",
	[OPA_LINKDOWN_REASON_BAD_SLID] = "Bad SLID",
	[OPA_LINKDOWN_REASON_BAD_DLID] = "Bad DLID",
	[OPA_LINKDOWN_REASON_BAD_L2] = "Bad L2",
	[OPA_LINKDOWN_REASON_BAD_SC] = "Bad SC",
	[OPA_LINKDOWN_REASON_RCV_ERROR_8] = "Receive error 8",
	[OPA_LINKDOWN_REASON_BAD_MID_TAIL] = "Bad mid tail",
	[OPA_LINKDOWN_REASON_RCV_ERROR_10] = "Receive error 10",
	[OPA_LINKDOWN_REASON_PREEMPT_ERROR] = "Preempt error",
	[OPA_LINKDOWN_REASON_PREEMPT_VL15] = "Preempt vl15",
	[OPA_LINKDOWN_REASON_BAD_VL_MARKER] = "Bad VL marker",
	[OPA_LINKDOWN_REASON_RCV_ERROR_14] = "Receive error 14",
	[OPA_LINKDOWN_REASON_RCV_ERROR_15] = "Receive error 15",
	[OPA_LINKDOWN_REASON_BAD_HEAD_DIST] = "Bad head distance",
	[OPA_LINKDOWN_REASON_BAD_TAIL_DIST] = "Bad tail distance",
	[OPA_LINKDOWN_REASON_BAD_CTRL_DIST] = "Bad control distance",
	[OPA_LINKDOWN_REASON_BAD_CREDIT_ACK] = "Bad credit ack",
	[OPA_LINKDOWN_REASON_UNSUPPORTED_VL_MARKER] = "Unsupported VL marker",
	[OPA_LINKDOWN_REASON_BAD_PREEMPT] = "Bad preempt",
	[OPA_LINKDOWN_REASON_BAD_CONTROL_FLIT] = "Bad control flit",
	[OPA_LINKDOWN_REASON_EXCEED_MULTICAST_LIMIT] = "Exceed multicast limit",
	[OPA_LINKDOWN_REASON_RCV_ERROR_24] = "Receive error 24",
	[OPA_LINKDOWN_REASON_RCV_ERROR_25] = "Receive error 25",
	[OPA_LINKDOWN_REASON_RCV_ERROR_26] = "Receive error 26",
	[OPA_LINKDOWN_REASON_RCV_ERROR_27] = "Receive error 27",
	[OPA_LINKDOWN_REASON_RCV_ERROR_28] = "Receive error 28",
	[OPA_LINKDOWN_REASON_RCV_ERROR_29] = "Receive error 29",
	[OPA_LINKDOWN_REASON_RCV_ERROR_30] = "Receive error 30",
	[OPA_LINKDOWN_REASON_EXCESSIVE_BUFFER_OVERRUN] =
					"Excessive buffer overrun",
	[OPA_LINKDOWN_REASON_UNKNOWN] = "Unknown",
	[OPA_LINKDOWN_REASON_REBOOT] = "Reboot",
	[OPA_LINKDOWN_REASON_NEIGHBOR_UNKNOWN] = "Neighbor unknown",
	[OPA_LINKDOWN_REASON_FM_BOUNCE] = "FM bounce",
	[OPA_LINKDOWN_REASON_SPEED_POLICY] = "Speed policy",
	[OPA_LINKDOWN_REASON_WIDTH_POLICY] = "Width policy",
	[OPA_LINKDOWN_REASON_DISCONNECTED] = "Disconnected",
	[OPA_LINKDOWN_REASON_LOCAL_MEDIA_NOT_INSTALLED] =
					"Local media not installed",
	[OPA_LINKDOWN_REASON_NOT_INSTALLED] = "Not installed",
	[OPA_LINKDOWN_REASON_CHASSIS_CONFIG] = "Chassis config",
	[OPA_LINKDOWN_REASON_END_TO_END_NOT_INSTALLED] =
					"End to end not installed",
	[OPA_LINKDOWN_REASON_POWER_POLICY] = "Power policy",
	[OPA_LINKDOWN_REASON_LINKSPEED_POLICY] = "Link speed policy",
	[OPA_LINKDOWN_REASON_LINKWIDTH_POLICY] = "Link width policy",
	[OPA_LINKDOWN_REASON_SWITCH_MGMT] = "Switch management",
	[OPA_LINKDOWN_REASON_SMA_DISABLED] = "SMA disabled",
	[OPA_LINKDOWN_REASON_TRANSIENT] = "Transient"
पूर्ण;

/* वापस the neighbor link करोwn reason string */
अटल स्थिर अक्षर *link_करोwn_reason_str(u8 reason)
अणु
	स्थिर अक्षर *str = शून्य;

	अगर (reason < ARRAY_SIZE(link_करोwn_reason_strs))
		str = link_करोwn_reason_strs[reason];
	अगर (!str)
		str = "(invalid)";

	वापस str;
पूर्ण

/*
 * Handle a link करोwn पूर्णांकerrupt from the 8051.
 *
 * This is a work-queue function outside of the पूर्णांकerrupt.
 */
व्योम handle_link_करोwn(काष्ठा work_काष्ठा *work)
अणु
	u8 lcl_reason, neigh_reason = 0;
	u8 link_करोwn_reason;
	काष्ठा hfi1_pportdata *ppd = container_of(work, काष्ठा hfi1_pportdata,
						  link_करोwn_work);
	पूर्णांक was_up;
	अटल स्थिर अक्षर ldr_str[] = "Link down reason: ";

	अगर ((ppd->host_link_state &
	     (HLS_DN_POLL | HLS_VERIFY_CAP | HLS_GOING_UP)) &&
	     ppd->port_type == PORT_TYPE_FIXED)
		ppd->offline_disabled_reason =
			HFI1_ODR_MASK(OPA_LINKDOWN_REASON_NOT_INSTALLED);

	/* Go offline first, then deal with पढ़ोing/writing through 8051 */
	was_up = !!(ppd->host_link_state & HLS_UP);
	set_link_state(ppd, HLS_DN_OFFLINE);
	xchg(&ppd->is_link_करोwn_queued, 0);

	अगर (was_up) अणु
		lcl_reason = 0;
		/* link करोwn reason is only valid अगर the link was up */
		पढ़ो_link_करोwn_reason(ppd->dd, &link_करोwn_reason);
		चयन (link_करोwn_reason) अणु
		हाल LDR_LINK_TRANSFER_ACTIVE_LOW:
			/* the link went करोwn, no idle message reason */
			dd_dev_info(ppd->dd, "%sUnexpected link down\n",
				    ldr_str);
			अवरोध;
		हाल LDR_RECEIVED_LINKDOWN_IDLE_MSG:
			/*
			 * The neighbor reason is only valid अगर an idle message
			 * was received क्रम it.
			 */
			पढ़ो_planned_करोwn_reason_code(ppd->dd, &neigh_reason);
			dd_dev_info(ppd->dd,
				    "%sNeighbor link down message %d, %s\n",
				    ldr_str, neigh_reason,
				    link_करोwn_reason_str(neigh_reason));
			अवरोध;
		हाल LDR_RECEIVED_HOST_OFFLINE_REQ:
			dd_dev_info(ppd->dd,
				    "%sHost requested link to go offline\n",
				    ldr_str);
			अवरोध;
		शेष:
			dd_dev_info(ppd->dd, "%sUnknown reason 0x%x\n",
				    ldr_str, link_करोwn_reason);
			अवरोध;
		पूर्ण

		/*
		 * If no reason, assume peer-initiated but missed
		 * LinkGoingDown idle flits.
		 */
		अगर (neigh_reason == 0)
			lcl_reason = OPA_LINKDOWN_REASON_NEIGHBOR_UNKNOWN;
	पूर्ण अन्यथा अणु
		/* went करोwn जबतक polling or going up */
		lcl_reason = OPA_LINKDOWN_REASON_TRANSIENT;
	पूर्ण

	set_link_करोwn_reason(ppd, lcl_reason, neigh_reason, 0);

	/* inक्रमm the SMA when the link transitions from up to करोwn */
	अगर (was_up && ppd->local_link_करोwn_reason.sma == 0 &&
	    ppd->neigh_link_करोwn_reason.sma == 0) अणु
		ppd->local_link_करोwn_reason.sma =
					ppd->local_link_करोwn_reason.latest;
		ppd->neigh_link_करोwn_reason.sma =
					ppd->neigh_link_करोwn_reason.latest;
	पूर्ण

	reset_neighbor_info(ppd);

	/* disable the port */
	clear_rcvctrl(ppd->dd, RCV_CTRL_RCV_PORT_ENABLE_SMASK);

	/*
	 * If there is no cable attached, turn the DC off. Otherwise,
	 * start the link bring up.
	 */
	अगर (ppd->port_type == PORT_TYPE_QSFP && !qsfp_mod_present(ppd))
		dc_shutकरोwn(ppd->dd);
	अन्यथा
		start_link(ppd);
पूर्ण

व्योम handle_link_bounce(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hfi1_pportdata *ppd = container_of(work, काष्ठा hfi1_pportdata,
							link_bounce_work);

	/*
	 * Only करो something अगर the link is currently up.
	 */
	अगर (ppd->host_link_state & HLS_UP) अणु
		set_link_state(ppd, HLS_DN_OFFLINE);
		start_link(ppd);
	पूर्ण अन्यथा अणु
		dd_dev_info(ppd->dd, "%s: link not up (%s), nothing to do\n",
			    __func__, link_state_name(ppd->host_link_state));
	पूर्ण
पूर्ण

/*
 * Mask conversion: Capability exchange to Port LTP.  The capability
 * exchange has an implicit 16b CRC that is mandatory.
 */
अटल पूर्णांक cap_to_port_ltp(पूर्णांक cap)
अणु
	पूर्णांक port_ltp = PORT_LTP_CRC_MODE_16; /* this mode is mandatory */

	अगर (cap & CAP_CRC_14B)
		port_ltp |= PORT_LTP_CRC_MODE_14;
	अगर (cap & CAP_CRC_48B)
		port_ltp |= PORT_LTP_CRC_MODE_48;
	अगर (cap & CAP_CRC_12B_16B_PER_LANE)
		port_ltp |= PORT_LTP_CRC_MODE_PER_LANE;

	वापस port_ltp;
पूर्ण

/*
 * Convert an OPA Port LTP mask to capability mask
 */
पूर्णांक port_ltp_to_cap(पूर्णांक port_ltp)
अणु
	पूर्णांक cap_mask = 0;

	अगर (port_ltp & PORT_LTP_CRC_MODE_14)
		cap_mask |= CAP_CRC_14B;
	अगर (port_ltp & PORT_LTP_CRC_MODE_48)
		cap_mask |= CAP_CRC_48B;
	अगर (port_ltp & PORT_LTP_CRC_MODE_PER_LANE)
		cap_mask |= CAP_CRC_12B_16B_PER_LANE;

	वापस cap_mask;
पूर्ण

/*
 * Convert a single DC LCB CRC mode to an OPA Port LTP mask.
 */
अटल पूर्णांक lcb_to_port_ltp(पूर्णांक lcb_crc)
अणु
	पूर्णांक port_ltp = 0;

	अगर (lcb_crc == LCB_CRC_12B_16B_PER_LANE)
		port_ltp = PORT_LTP_CRC_MODE_PER_LANE;
	अन्यथा अगर (lcb_crc == LCB_CRC_48B)
		port_ltp = PORT_LTP_CRC_MODE_48;
	अन्यथा अगर (lcb_crc == LCB_CRC_14B)
		port_ltp = PORT_LTP_CRC_MODE_14;
	अन्यथा
		port_ltp = PORT_LTP_CRC_MODE_16;

	वापस port_ltp;
पूर्ण

अटल व्योम clear_full_mgmt_pkey(काष्ठा hfi1_pportdata *ppd)
अणु
	अगर (ppd->pkeys[2] != 0) अणु
		ppd->pkeys[2] = 0;
		(व्योम)hfi1_set_ib_cfg(ppd, HFI1_IB_CFG_PKEYS, 0);
		hfi1_event_pkey_change(ppd->dd, ppd->port);
	पूर्ण
पूर्ण

/*
 * Convert the given link width to the OPA link width biपंचांगask.
 */
अटल u16 link_width_to_bits(काष्ठा hfi1_devdata *dd, u16 width)
अणु
	चयन (width) अणु
	हाल 0:
		/*
		 * Simulator and quick linkup करो not set the width.
		 * Just set it to 4x without complaपूर्णांक.
		 */
		अगर (dd->icode == ICODE_FUNCTIONAL_SIMULATOR || quick_linkup)
			वापस OPA_LINK_WIDTH_4X;
		वापस 0; /* no lanes up */
	हाल 1: वापस OPA_LINK_WIDTH_1X;
	हाल 2: वापस OPA_LINK_WIDTH_2X;
	हाल 3: वापस OPA_LINK_WIDTH_3X;
	हाल 4: वापस OPA_LINK_WIDTH_4X;
	शेष:
		dd_dev_info(dd, "%s: invalid width %d, using 4\n",
			    __func__, width);
		वापस OPA_LINK_WIDTH_4X;
	पूर्ण
पूर्ण

/*
 * Do a population count on the bottom nibble.
 */
अटल स्थिर u8 bit_counts[16] = अणु
	0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4
पूर्ण;

अटल अंतरभूत u8 nibble_to_count(u8 nibble)
अणु
	वापस bit_counts[nibble & 0xf];
पूर्ण

/*
 * Read the active lane inक्रमmation from the 8051 रेजिस्टरs and वापस
 * their widths.
 *
 * Active lane inक्रमmation is found in these 8051 रेजिस्टरs:
 *	enable_lane_tx
 *	enable_lane_rx
 */
अटल व्योम get_link_widths(काष्ठा hfi1_devdata *dd, u16 *tx_width,
			    u16 *rx_width)
अणु
	u16 tx, rx;
	u8 enable_lane_rx;
	u8 enable_lane_tx;
	u8 tx_polarity_inversion;
	u8 rx_polarity_inversion;
	u8 max_rate;

	/* पढ़ो the active lanes */
	पढ़ो_tx_settings(dd, &enable_lane_tx, &tx_polarity_inversion,
			 &rx_polarity_inversion, &max_rate);
	पढ़ो_local_lni(dd, &enable_lane_rx);

	/* convert to counts */
	tx = nibble_to_count(enable_lane_tx);
	rx = nibble_to_count(enable_lane_rx);

	/*
	 * Set link_speed_active here, overriding what was set in
	 * handle_verअगरy_cap().  The ASIC 8051 firmware करोes not correctly
	 * set the max_rate field in handle_verअगरy_cap until v0.19.
	 */
	अगर ((dd->icode == ICODE_RTL_SILICON) &&
	    (dd->dc8051_ver < dc8051_ver(0, 19, 0))) अणु
		/* max_rate: 0 = 12.5G, 1 = 25G */
		चयन (max_rate) अणु
		हाल 0:
			dd->pport[0].link_speed_active = OPA_LINK_SPEED_12_5G;
			अवरोध;
		हाल 1:
			dd->pport[0].link_speed_active = OPA_LINK_SPEED_25G;
			अवरोध;
		शेष:
			dd_dev_err(dd,
				   "%s: unexpected max rate %d, using 25Gb\n",
				   __func__, (पूर्णांक)max_rate);
			dd->pport[0].link_speed_active = OPA_LINK_SPEED_25G;
			अवरोध;
		पूर्ण
	पूर्ण

	dd_dev_info(dd,
		    "Fabric active lanes (width): tx 0x%x (%d), rx 0x%x (%d)\n",
		    enable_lane_tx, tx, enable_lane_rx, rx);
	*tx_width = link_width_to_bits(dd, tx);
	*rx_width = link_width_to_bits(dd, rx);
पूर्ण

/*
 * Read verअगरy_cap_local_fm_link_width[1] to obtain the link widths.
 * Valid after the end of VerअगरyCap and during LinkUp.  Does not change
 * after link up.  I.e. look अन्यथाwhere क्रम करोwngrade inक्रमmation.
 *
 * Bits are:
 *	+ bits [7:4] contain the number of active transmitters
 *	+ bits [3:0] contain the number of active receivers
 * These are numbers 1 through 4 and can be dअगरferent values अगर the
 * link is asymmetric.
 *
 * verअगरy_cap_local_fm_link_width[0] retains its original value.
 */
अटल व्योम get_linkup_widths(काष्ठा hfi1_devdata *dd, u16 *tx_width,
			      u16 *rx_width)
अणु
	u16 widths, tx, rx;
	u8 misc_bits, local_flags;
	u16 active_tx, active_rx;

	पढ़ो_vc_local_link_mode(dd, &misc_bits, &local_flags, &widths);
	tx = widths >> 12;
	rx = (widths >> 8) & 0xf;

	*tx_width = link_width_to_bits(dd, tx);
	*rx_width = link_width_to_bits(dd, rx);

	/* prपूर्णांक the active widths */
	get_link_widths(dd, &active_tx, &active_rx);
पूर्ण

/*
 * Set ppd->link_width_active and ppd->link_width_करोwngrade_active using
 * hardware inक्रमmation when the link first comes up.
 *
 * The link width is not available until after VerअगरyCap.AllFramesReceived
 * (the trigger क्रम handle_verअगरy_cap), so this is outside that routine
 * and should be called when the 8051 संकेतs linkup.
 */
व्योम get_linkup_link_widths(काष्ठा hfi1_pportdata *ppd)
अणु
	u16 tx_width, rx_width;

	/* get end-of-LNI link widths */
	get_linkup_widths(ppd->dd, &tx_width, &rx_width);

	/* use tx_width as the link is supposed to be symmetric on link up */
	ppd->link_width_active = tx_width;
	/* link width करोwngrade active (LWD.A) starts out matching LW.A */
	ppd->link_width_करोwngrade_tx_active = ppd->link_width_active;
	ppd->link_width_करोwngrade_rx_active = ppd->link_width_active;
	/* per OPA spec, on link up LWD.E resets to LWD.S */
	ppd->link_width_करोwngrade_enabled = ppd->link_width_करोwngrade_supported;
	/* cache the active egress rate (units अणु10^6 bits/sec]) */
	ppd->current_egress_rate = active_egress_rate(ppd);
पूर्ण

/*
 * Handle a verअगरy capabilities पूर्णांकerrupt from the 8051.
 *
 * This is a work-queue function outside of the पूर्णांकerrupt.
 */
व्योम handle_verअगरy_cap(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hfi1_pportdata *ppd = container_of(work, काष्ठा hfi1_pportdata,
								link_vc_work);
	काष्ठा hfi1_devdata *dd = ppd->dd;
	u64 reg;
	u8 घातer_management;
	u8 continuous;
	u8 vcu;
	u8 vau;
	u8 z;
	u16 vl15buf;
	u16 link_widths;
	u16 crc_mask;
	u16 crc_val;
	u16 device_id;
	u16 active_tx, active_rx;
	u8 partner_supported_crc;
	u8 remote_tx_rate;
	u8 device_rev;

	set_link_state(ppd, HLS_VERIFY_CAP);

	lcb_shutकरोwn(dd, 0);
	adjust_lcb_क्रम_fpga_serdes(dd);

	पढ़ो_vc_remote_phy(dd, &घातer_management, &continuous);
	पढ़ो_vc_remote_fabric(dd, &vau, &z, &vcu, &vl15buf,
			      &partner_supported_crc);
	पढ़ो_vc_remote_link_width(dd, &remote_tx_rate, &link_widths);
	पढ़ो_remote_device_id(dd, &device_id, &device_rev);

	/* prपूर्णांक the active widths */
	get_link_widths(dd, &active_tx, &active_rx);
	dd_dev_info(dd,
		    "Peer PHY: power management 0x%x, continuous updates 0x%x\n",
		    (पूर्णांक)घातer_management, (पूर्णांक)continuous);
	dd_dev_info(dd,
		    "Peer Fabric: vAU %d, Z %d, vCU %d, vl15 credits 0x%x, CRC sizes 0x%x\n",
		    (पूर्णांक)vau, (पूर्णांक)z, (पूर्णांक)vcu, (पूर्णांक)vl15buf,
		    (पूर्णांक)partner_supported_crc);
	dd_dev_info(dd, "Peer Link Width: tx rate 0x%x, widths 0x%x\n",
		    (u32)remote_tx_rate, (u32)link_widths);
	dd_dev_info(dd, "Peer Device ID: 0x%04x, Revision 0x%02x\n",
		    (u32)device_id, (u32)device_rev);
	/*
	 * The peer vAU value just पढ़ो is the peer receiver value.  HFI करोes
	 * not support a transmit vAU of 0 (AU == 8).  We advertised that
	 * with Z=1 in the fabric capabilities sent to the peer.  The peer
	 * will see our Z=1, and, अगर it advertised a vAU of 0, will move its
	 * receive to vAU of 1 (AU == 16).  Do the same here.  We करो not care
	 * about the peer Z value - our sent vAU is 3 (hardwired) and is not
	 * subject to the Z value exception.
	 */
	अगर (vau == 0)
		vau = 1;
	set_up_vau(dd, vau);

	/*
	 * Set VL15 credits to 0 in global credit रेजिस्टर. Cache remote VL15
	 * credits value and रुको क्रम link-up पूर्णांकerrupt ot set it.
	 */
	set_up_vl15(dd, 0);
	dd->vl15buf_cached = vl15buf;

	/* set up the LCB CRC mode */
	crc_mask = ppd->port_crc_mode_enabled & partner_supported_crc;

	/* order is important: use the lowest bit in common */
	अगर (crc_mask & CAP_CRC_14B)
		crc_val = LCB_CRC_14B;
	अन्यथा अगर (crc_mask & CAP_CRC_48B)
		crc_val = LCB_CRC_48B;
	अन्यथा अगर (crc_mask & CAP_CRC_12B_16B_PER_LANE)
		crc_val = LCB_CRC_12B_16B_PER_LANE;
	अन्यथा
		crc_val = LCB_CRC_16B;

	dd_dev_info(dd, "Final LCB CRC mode: %d\n", (पूर्णांक)crc_val);
	ग_लिखो_csr(dd, DC_LCB_CFG_CRC_MODE,
		  (u64)crc_val << DC_LCB_CFG_CRC_MODE_TX_VAL_SHIFT);

	/* set (14b only) or clear sideband credit */
	reg = पढ़ो_csr(dd, SEND_CM_CTRL);
	अगर (crc_val == LCB_CRC_14B && crc_14b_sideband) अणु
		ग_लिखो_csr(dd, SEND_CM_CTRL,
			  reg | SEND_CM_CTRL_FORCE_CREDIT_MODE_SMASK);
	पूर्ण अन्यथा अणु
		ग_लिखो_csr(dd, SEND_CM_CTRL,
			  reg & ~SEND_CM_CTRL_FORCE_CREDIT_MODE_SMASK);
	पूर्ण

	ppd->link_speed_active = 0;	/* invalid value */
	अगर (dd->dc8051_ver < dc8051_ver(0, 20, 0)) अणु
		/* remote_tx_rate: 0 = 12.5G, 1 = 25G */
		चयन (remote_tx_rate) अणु
		हाल 0:
			ppd->link_speed_active = OPA_LINK_SPEED_12_5G;
			अवरोध;
		हाल 1:
			ppd->link_speed_active = OPA_LINK_SPEED_25G;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* actual rate is highest bit of the ANDed rates */
		u8 rate = remote_tx_rate & ppd->local_tx_rate;

		अगर (rate & 2)
			ppd->link_speed_active = OPA_LINK_SPEED_25G;
		अन्यथा अगर (rate & 1)
			ppd->link_speed_active = OPA_LINK_SPEED_12_5G;
	पूर्ण
	अगर (ppd->link_speed_active == 0) अणु
		dd_dev_err(dd, "%s: unexpected remote tx rate %d, using 25Gb\n",
			   __func__, (पूर्णांक)remote_tx_rate);
		ppd->link_speed_active = OPA_LINK_SPEED_25G;
	पूर्ण

	/*
	 * Cache the values of the supported, enabled, and active
	 * LTP CRC modes to वापस in 'portinfo' queries. But the bit
	 * flags that are वापसed in the portinfo query dअगरfer from
	 * what's in the link_crc_mask, crc_sizes, and crc_val
	 * variables. Convert these here.
	 */
	ppd->port_ltp_crc_mode = cap_to_port_ltp(link_crc_mask) << 8;
		/* supported crc modes */
	ppd->port_ltp_crc_mode |=
		cap_to_port_ltp(ppd->port_crc_mode_enabled) << 4;
		/* enabled crc modes */
	ppd->port_ltp_crc_mode |= lcb_to_port_ltp(crc_val);
		/* active crc mode */

	/* set up the remote credit वापस table */
	assign_remote_cm_au_table(dd, vcu);

	/*
	 * The LCB is reset on entry to handle_verअगरy_cap(), so this must
	 * be applied on every link up.
	 *
	 * Adjust LCB error समाप्त enable to समाप्त the link अगर
	 * these RBUF errors are seen:
	 *	REPLAY_BUF_MBE_SMASK
	 *	FLIT_INPUT_BUF_MBE_SMASK
	 */
	अगर (is_ax(dd)) अणु			/* fixed in B0 */
		reg = पढ़ो_csr(dd, DC_LCB_CFG_LINK_KILL_EN);
		reg |= DC_LCB_CFG_LINK_KILL_EN_REPLAY_BUF_MBE_SMASK
			| DC_LCB_CFG_LINK_KILL_EN_FLIT_INPUT_BUF_MBE_SMASK;
		ग_लिखो_csr(dd, DC_LCB_CFG_LINK_KILL_EN, reg);
	पूर्ण

	/* pull LCB fअगरos out of reset - all fअगरo घड़ीs must be stable */
	ग_लिखो_csr(dd, DC_LCB_CFG_TX_FIFOS_RESET, 0);

	/* give 8051 access to the LCB CSRs */
	ग_लिखो_csr(dd, DC_LCB_ERR_EN, 0); /* mask LCB errors */
	set_8051_lcb_access(dd);

	/* tell the 8051 to go to LinkUp */
	set_link_state(ppd, HLS_GOING_UP);
पूर्ण

/**
 * apply_link_करोwngrade_policy - Apply the link width करोwngrade enabled
 * policy against the current active link widths.
 * @ppd: info of physical Hfi port
 * @refresh_widths: True indicates link करोwngrade event
 * @वापस: True indicates a successful link करोwngrade. False indicates
 *	    link करोwngrade event failed and the link will bounce back to
 *	    शेष link width.
 *
 * Called when the enabled policy changes or the active link widths
 * change.
 * Refresh_widths indicates that a link करोwngrade occurred. The
 * link_करोwngraded variable is set by refresh_widths and
 * determines the success/failure of the policy application.
 */
bool apply_link_करोwngrade_policy(काष्ठा hfi1_pportdata *ppd,
				 bool refresh_widths)
अणु
	पूर्णांक करो_bounce = 0;
	पूर्णांक tries;
	u16 lwde;
	u16 tx, rx;
	bool link_करोwngraded = refresh_widths;

	/* use the hls lock to aव्योम a race with actual link up */
	tries = 0;
retry:
	mutex_lock(&ppd->hls_lock);
	/* only apply अगर the link is up */
	अगर (ppd->host_link_state & HLS_DOWN) अणु
		/* still going up..रुको and retry */
		अगर (ppd->host_link_state & HLS_GOING_UP) अणु
			अगर (++tries < 1000) अणु
				mutex_unlock(&ppd->hls_lock);
				usleep_range(100, 120); /* arbitrary */
				जाओ retry;
			पूर्ण
			dd_dev_err(ppd->dd,
				   "%s: giving up waiting for link state change\n",
				   __func__);
		पूर्ण
		जाओ करोne;
	पूर्ण

	lwde = ppd->link_width_करोwngrade_enabled;

	अगर (refresh_widths) अणु
		get_link_widths(ppd->dd, &tx, &rx);
		ppd->link_width_करोwngrade_tx_active = tx;
		ppd->link_width_करोwngrade_rx_active = rx;
	पूर्ण

	अगर (ppd->link_width_करोwngrade_tx_active == 0 ||
	    ppd->link_width_करोwngrade_rx_active == 0) अणु
		/* the 8051 reported a dead link as a करोwngrade */
		dd_dev_err(ppd->dd, "Link downgrade is really a link down, ignoring\n");
		link_करोwngraded = false;
	पूर्ण अन्यथा अगर (lwde == 0) अणु
		/* करोwngrade is disabled */

		/* bounce अगर not at starting active width */
		अगर ((ppd->link_width_active !=
		     ppd->link_width_करोwngrade_tx_active) ||
		    (ppd->link_width_active !=
		     ppd->link_width_करोwngrade_rx_active)) अणु
			dd_dev_err(ppd->dd,
				   "Link downgrade is disabled and link has downgraded, downing link\n");
			dd_dev_err(ppd->dd,
				   "  original 0x%x, tx active 0x%x, rx active 0x%x\n",
				   ppd->link_width_active,
				   ppd->link_width_करोwngrade_tx_active,
				   ppd->link_width_करोwngrade_rx_active);
			करो_bounce = 1;
			link_करोwngraded = false;
		पूर्ण
	पूर्ण अन्यथा अगर ((lwde & ppd->link_width_करोwngrade_tx_active) == 0 ||
		   (lwde & ppd->link_width_करोwngrade_rx_active) == 0) अणु
		/* Tx or Rx is outside the enabled policy */
		dd_dev_err(ppd->dd,
			   "Link is outside of downgrade allowed, downing link\n");
		dd_dev_err(ppd->dd,
			   "  enabled 0x%x, tx active 0x%x, rx active 0x%x\n",
			   lwde, ppd->link_width_करोwngrade_tx_active,
			   ppd->link_width_करोwngrade_rx_active);
		करो_bounce = 1;
		link_करोwngraded = false;
	पूर्ण

करोne:
	mutex_unlock(&ppd->hls_lock);

	अगर (करो_bounce) अणु
		set_link_करोwn_reason(ppd, OPA_LINKDOWN_REASON_WIDTH_POLICY, 0,
				     OPA_LINKDOWN_REASON_WIDTH_POLICY);
		set_link_state(ppd, HLS_DN_OFFLINE);
		start_link(ppd);
	पूर्ण

	वापस link_करोwngraded;
पूर्ण

/*
 * Handle a link करोwngrade पूर्णांकerrupt from the 8051.
 *
 * This is a work-queue function outside of the पूर्णांकerrupt.
 */
व्योम handle_link_करोwngrade(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hfi1_pportdata *ppd = container_of(work, काष्ठा hfi1_pportdata,
							link_करोwngrade_work);

	dd_dev_info(ppd->dd, "8051: Link width downgrade\n");
	अगर (apply_link_करोwngrade_policy(ppd, true))
		update_xmit_counters(ppd, ppd->link_width_करोwngrade_tx_active);
पूर्ण

अटल अक्षर *dcc_err_string(अक्षर *buf, पूर्णांक buf_len, u64 flags)
अणु
	वापस flag_string(buf, buf_len, flags, dcc_err_flags,
		ARRAY_SIZE(dcc_err_flags));
पूर्ण

अटल अक्षर *lcb_err_string(अक्षर *buf, पूर्णांक buf_len, u64 flags)
अणु
	वापस flag_string(buf, buf_len, flags, lcb_err_flags,
		ARRAY_SIZE(lcb_err_flags));
पूर्ण

अटल अक्षर *dc8051_err_string(अक्षर *buf, पूर्णांक buf_len, u64 flags)
अणु
	वापस flag_string(buf, buf_len, flags, dc8051_err_flags,
		ARRAY_SIZE(dc8051_err_flags));
पूर्ण

अटल अक्षर *dc8051_info_err_string(अक्षर *buf, पूर्णांक buf_len, u64 flags)
अणु
	वापस flag_string(buf, buf_len, flags, dc8051_info_err_flags,
		ARRAY_SIZE(dc8051_info_err_flags));
पूर्ण

अटल अक्षर *dc8051_info_host_msg_string(अक्षर *buf, पूर्णांक buf_len, u64 flags)
अणु
	वापस flag_string(buf, buf_len, flags, dc8051_info_host_msg_flags,
		ARRAY_SIZE(dc8051_info_host_msg_flags));
पूर्ण

अटल व्योम handle_8051_पूर्णांकerrupt(काष्ठा hfi1_devdata *dd, u32 unused, u64 reg)
अणु
	काष्ठा hfi1_pportdata *ppd = dd->pport;
	u64 info, err, host_msg;
	पूर्णांक queue_link_करोwn = 0;
	अक्षर buf[96];

	/* look at the flags */
	अगर (reg & DC_DC8051_ERR_FLG_SET_BY_8051_SMASK) अणु
		/* 8051 inक्रमmation set by firmware */
		/* पढ़ो DC8051_DBG_ERR_INFO_SET_BY_8051 क्रम details */
		info = पढ़ो_csr(dd, DC_DC8051_DBG_ERR_INFO_SET_BY_8051);
		err = (info >> DC_DC8051_DBG_ERR_INFO_SET_BY_8051_ERROR_SHIFT)
			& DC_DC8051_DBG_ERR_INFO_SET_BY_8051_ERROR_MASK;
		host_msg = (info >>
			DC_DC8051_DBG_ERR_INFO_SET_BY_8051_HOST_MSG_SHIFT)
			& DC_DC8051_DBG_ERR_INFO_SET_BY_8051_HOST_MSG_MASK;

		/*
		 * Handle error flags.
		 */
		अगर (err & FAILED_LNI) अणु
			/*
			 * LNI error indications are cleared by the 8051
			 * only when starting polling.  Only pay attention
			 * to them when in the states that occur during
			 * LNI.
			 */
			अगर (ppd->host_link_state
			    & (HLS_DN_POLL | HLS_VERIFY_CAP | HLS_GOING_UP)) अणु
				queue_link_करोwn = 1;
				dd_dev_info(dd, "Link error: %s\n",
					    dc8051_info_err_string(buf,
								   माप(buf),
								   err &
								   FAILED_LNI));
			पूर्ण
			err &= ~(u64)FAILED_LNI;
		पूर्ण
		/* unknown frames can happen durning LNI, just count */
		अगर (err & UNKNOWN_FRAME) अणु
			ppd->unknown_frame_count++;
			err &= ~(u64)UNKNOWN_FRAME;
		पूर्ण
		अगर (err) अणु
			/* report reमुख्यing errors, but करो not करो anything */
			dd_dev_err(dd, "8051 info error: %s\n",
				   dc8051_info_err_string(buf, माप(buf),
							  err));
		पूर्ण

		/*
		 * Handle host message flags.
		 */
		अगर (host_msg & HOST_REQ_DONE) अणु
			/*
			 * Presently, the driver करोes a busy रुको क्रम
			 * host requests to complete.  This is only an
			 * inक्रमmational message.
			 * NOTE: The 8051 clears the host message
			 * inक्रमmation *on the next 8051 command*.
			 * Thereक्रमe, when linkup is achieved,
			 * this flag will still be set.
			 */
			host_msg &= ~(u64)HOST_REQ_DONE;
		पूर्ण
		अगर (host_msg & BC_SMA_MSG) अणु
			queue_work(ppd->link_wq, &ppd->sma_message_work);
			host_msg &= ~(u64)BC_SMA_MSG;
		पूर्ण
		अगर (host_msg & LINKUP_ACHIEVED) अणु
			dd_dev_info(dd, "8051: Link up\n");
			queue_work(ppd->link_wq, &ppd->link_up_work);
			host_msg &= ~(u64)LINKUP_ACHIEVED;
		पूर्ण
		अगर (host_msg & EXT_DEVICE_CFG_REQ) अणु
			handle_8051_request(ppd);
			host_msg &= ~(u64)EXT_DEVICE_CFG_REQ;
		पूर्ण
		अगर (host_msg & VERIFY_CAP_FRAME) अणु
			queue_work(ppd->link_wq, &ppd->link_vc_work);
			host_msg &= ~(u64)VERIFY_CAP_FRAME;
		पूर्ण
		अगर (host_msg & LINK_GOING_DOWN) अणु
			स्थिर अक्षर *extra = "";
			/* no करोwngrade action needed अगर going करोwn */
			अगर (host_msg & LINK_WIDTH_DOWNGRADED) अणु
				host_msg &= ~(u64)LINK_WIDTH_DOWNGRADED;
				extra = " (ignoring downgrade)";
			पूर्ण
			dd_dev_info(dd, "8051: Link down%s\n", extra);
			queue_link_करोwn = 1;
			host_msg &= ~(u64)LINK_GOING_DOWN;
		पूर्ण
		अगर (host_msg & LINK_WIDTH_DOWNGRADED) अणु
			queue_work(ppd->link_wq, &ppd->link_करोwngrade_work);
			host_msg &= ~(u64)LINK_WIDTH_DOWNGRADED;
		पूर्ण
		अगर (host_msg) अणु
			/* report reमुख्यing messages, but करो not करो anything */
			dd_dev_info(dd, "8051 info host message: %s\n",
				    dc8051_info_host_msg_string(buf,
								माप(buf),
								host_msg));
		पूर्ण

		reg &= ~DC_DC8051_ERR_FLG_SET_BY_8051_SMASK;
	पूर्ण
	अगर (reg & DC_DC8051_ERR_FLG_LOST_8051_HEART_BEAT_SMASK) अणु
		/*
		 * Lost the 8051 heartbeat.  If this happens, we
		 * receive स्थिरant पूर्णांकerrupts about it.  Disable
		 * the पूर्णांकerrupt after the first.
		 */
		dd_dev_err(dd, "Lost 8051 heartbeat\n");
		ग_लिखो_csr(dd, DC_DC8051_ERR_EN,
			  पढ़ो_csr(dd, DC_DC8051_ERR_EN) &
			  ~DC_DC8051_ERR_EN_LOST_8051_HEART_BEAT_SMASK);

		reg &= ~DC_DC8051_ERR_FLG_LOST_8051_HEART_BEAT_SMASK;
	पूर्ण
	अगर (reg) अणु
		/* report the error, but करो not करो anything */
		dd_dev_err(dd, "8051 error: %s\n",
			   dc8051_err_string(buf, माप(buf), reg));
	पूर्ण

	अगर (queue_link_करोwn) अणु
		/*
		 * अगर the link is alपढ़ोy going करोwn or disabled, करो not
		 * queue another. If there's a link करोwn entry alपढ़ोy
		 * queued, करोn't queue another one.
		 */
		अगर ((ppd->host_link_state &
		    (HLS_GOING_OFFLINE | HLS_LINK_COOLDOWN)) ||
		    ppd->link_enabled == 0) अणु
			dd_dev_info(dd, "%s: not queuing link down. host_link_state %x, link_enabled %x\n",
				    __func__, ppd->host_link_state,
				    ppd->link_enabled);
		पूर्ण अन्यथा अणु
			अगर (xchg(&ppd->is_link_करोwn_queued, 1) == 1)
				dd_dev_info(dd,
					    "%s: link down request already queued\n",
					    __func__);
			अन्यथा
				queue_work(ppd->link_wq, &ppd->link_करोwn_work);
		पूर्ण
	पूर्ण
पूर्ण

अटल स्थिर अक्षर * स्थिर fm_config_txt[] = अणु
[0] =
	"BadHeadDist: Distance violation between two head flits",
[1] =
	"BadTailDist: Distance violation between two tail flits",
[2] =
	"BadCtrlDist: Distance violation between two credit control flits",
[3] =
	"BadCrdAck: Credits return for unsupported VL",
[4] =
	"UnsupportedVLMarker: Received VL Marker",
[5] =
	"BadPreempt: Exceeded the preemption nesting level",
[6] =
	"BadControlFlit: Received unsupported control flit",
/* no 7 */
[8] =
	"UnsupportedVLMarker: Received VL Marker for unconfigured or disabled VL",
पूर्ण;

अटल स्थिर अक्षर * स्थिर port_rcv_txt[] = अणु
[1] =
	"BadPktLen: Illegal PktLen",
[2] =
	"PktLenTooLong: Packet longer than PktLen",
[3] =
	"PktLenTooShort: Packet shorter than PktLen",
[4] =
	"BadSLID: Illegal SLID (0, using multicast as SLID, does not include security validation of SLID)",
[5] =
	"BadDLID: Illegal DLID (0, doesn't match HFI)",
[6] =
	"BadL2: Illegal L2 opcode",
[7] =
	"BadSC: Unsupported SC",
[9] =
	"BadRC: Illegal RC",
[11] =
	"PreemptError: Preempting with same VL",
[12] =
	"PreemptVL15: Preempting a VL15 packet",
पूर्ण;

#घोषणा OPA_LDR_FMCONFIG_OFFSET 16
#घोषणा OPA_LDR_PORTRCV_OFFSET 0
अटल व्योम handle_dcc_err(काष्ठा hfi1_devdata *dd, u32 unused, u64 reg)
अणु
	u64 info, hdr0, hdr1;
	स्थिर अक्षर *extra;
	अक्षर buf[96];
	काष्ठा hfi1_pportdata *ppd = dd->pport;
	u8 lcl_reason = 0;
	पूर्णांक करो_bounce = 0;

	अगर (reg & DCC_ERR_FLG_UNCORRECTABLE_ERR_SMASK) अणु
		अगर (!(dd->err_info_uncorrectable & OPA_EI_STATUS_SMASK)) अणु
			info = पढ़ो_csr(dd, DCC_ERR_INFO_UNCORRECTABLE);
			dd->err_info_uncorrectable = info & OPA_EI_CODE_SMASK;
			/* set status bit */
			dd->err_info_uncorrectable |= OPA_EI_STATUS_SMASK;
		पूर्ण
		reg &= ~DCC_ERR_FLG_UNCORRECTABLE_ERR_SMASK;
	पूर्ण

	अगर (reg & DCC_ERR_FLG_LINK_ERR_SMASK) अणु
		काष्ठा hfi1_pportdata *ppd = dd->pport;
		/* this counter saturates at (2^32) - 1 */
		अगर (ppd->link_करोwned < (u32)अच_पूर्णांक_उच्च)
			ppd->link_करोwned++;
		reg &= ~DCC_ERR_FLG_LINK_ERR_SMASK;
	पूर्ण

	अगर (reg & DCC_ERR_FLG_FMCONFIG_ERR_SMASK) अणु
		u8 reason_valid = 1;

		info = पढ़ो_csr(dd, DCC_ERR_INFO_FMCONFIG);
		अगर (!(dd->err_info_fmconfig & OPA_EI_STATUS_SMASK)) अणु
			dd->err_info_fmconfig = info & OPA_EI_CODE_SMASK;
			/* set status bit */
			dd->err_info_fmconfig |= OPA_EI_STATUS_SMASK;
		पूर्ण
		चयन (info) अणु
		हाल 0:
		हाल 1:
		हाल 2:
		हाल 3:
		हाल 4:
		हाल 5:
		हाल 6:
			extra = fm_config_txt[info];
			अवरोध;
		हाल 8:
			extra = fm_config_txt[info];
			अगर (ppd->port_error_action &
			    OPA_PI_MASK_FM_CFG_UNSUPPORTED_VL_MARKER) अणु
				करो_bounce = 1;
				/*
				 * lcl_reason cannot be derived from info
				 * क्रम this error
				 */
				lcl_reason =
				  OPA_LINKDOWN_REASON_UNSUPPORTED_VL_MARKER;
			पूर्ण
			अवरोध;
		शेष:
			reason_valid = 0;
			snम_लिखो(buf, माप(buf), "reserved%lld", info);
			extra = buf;
			अवरोध;
		पूर्ण

		अगर (reason_valid && !करो_bounce) अणु
			करो_bounce = ppd->port_error_action &
					(1 << (OPA_LDR_FMCONFIG_OFFSET + info));
			lcl_reason = info + OPA_LINKDOWN_REASON_BAD_HEAD_DIST;
		पूर्ण

		/* just report this */
		dd_dev_info_ratelimited(dd, "DCC Error: fmconfig error: %s\n",
					extra);
		reg &= ~DCC_ERR_FLG_FMCONFIG_ERR_SMASK;
	पूर्ण

	अगर (reg & DCC_ERR_FLG_RCVPORT_ERR_SMASK) अणु
		u8 reason_valid = 1;

		info = पढ़ो_csr(dd, DCC_ERR_INFO_PORTRCV);
		hdr0 = पढ़ो_csr(dd, DCC_ERR_INFO_PORTRCV_HDR0);
		hdr1 = पढ़ो_csr(dd, DCC_ERR_INFO_PORTRCV_HDR1);
		अगर (!(dd->err_info_rcvport.status_and_code &
		      OPA_EI_STATUS_SMASK)) अणु
			dd->err_info_rcvport.status_and_code =
				info & OPA_EI_CODE_SMASK;
			/* set status bit */
			dd->err_info_rcvport.status_and_code |=
				OPA_EI_STATUS_SMASK;
			/*
			 * save first 2 flits in the packet that caused
			 * the error
			 */
			dd->err_info_rcvport.packet_flit1 = hdr0;
			dd->err_info_rcvport.packet_flit2 = hdr1;
		पूर्ण
		चयन (info) अणु
		हाल 1:
		हाल 2:
		हाल 3:
		हाल 4:
		हाल 5:
		हाल 6:
		हाल 7:
		हाल 9:
		हाल 11:
		हाल 12:
			extra = port_rcv_txt[info];
			अवरोध;
		शेष:
			reason_valid = 0;
			snम_लिखो(buf, माप(buf), "reserved%lld", info);
			extra = buf;
			अवरोध;
		पूर्ण

		अगर (reason_valid && !करो_bounce) अणु
			करो_bounce = ppd->port_error_action &
					(1 << (OPA_LDR_PORTRCV_OFFSET + info));
			lcl_reason = info + OPA_LINKDOWN_REASON_RCV_ERROR_0;
		पूर्ण

		/* just report this */
		dd_dev_info_ratelimited(dd, "DCC Error: PortRcv error: %s\n"
					"               hdr0 0x%llx, hdr1 0x%llx\n",
					extra, hdr0, hdr1);

		reg &= ~DCC_ERR_FLG_RCVPORT_ERR_SMASK;
	पूर्ण

	अगर (reg & DCC_ERR_FLG_EN_CSR_ACCESS_BLOCKED_UC_SMASK) अणु
		/* inक्रमmative only */
		dd_dev_info_ratelimited(dd, "8051 access to LCB blocked\n");
		reg &= ~DCC_ERR_FLG_EN_CSR_ACCESS_BLOCKED_UC_SMASK;
	पूर्ण
	अगर (reg & DCC_ERR_FLG_EN_CSR_ACCESS_BLOCKED_HOST_SMASK) अणु
		/* inक्रमmative only */
		dd_dev_info_ratelimited(dd, "host access to LCB blocked\n");
		reg &= ~DCC_ERR_FLG_EN_CSR_ACCESS_BLOCKED_HOST_SMASK;
	पूर्ण

	अगर (unlikely(hfi1_dbg_fault_suppress_err(&dd->verbs_dev)))
		reg &= ~DCC_ERR_FLG_LATE_EBP_ERR_SMASK;

	/* report any reमुख्यing errors */
	अगर (reg)
		dd_dev_info_ratelimited(dd, "DCC Error: %s\n",
					dcc_err_string(buf, माप(buf), reg));

	अगर (lcl_reason == 0)
		lcl_reason = OPA_LINKDOWN_REASON_UNKNOWN;

	अगर (करो_bounce) अणु
		dd_dev_info_ratelimited(dd, "%s: PortErrorAction bounce\n",
					__func__);
		set_link_करोwn_reason(ppd, lcl_reason, 0, lcl_reason);
		queue_work(ppd->link_wq, &ppd->link_bounce_work);
	पूर्ण
पूर्ण

अटल व्योम handle_lcb_err(काष्ठा hfi1_devdata *dd, u32 unused, u64 reg)
अणु
	अक्षर buf[96];

	dd_dev_info(dd, "LCB Error: %s\n",
		    lcb_err_string(buf, माप(buf), reg));
पूर्ण

/*
 * CCE block DC पूर्णांकerrupt.  Source is < 8.
 */
अटल व्योम is_dc_पूर्णांक(काष्ठा hfi1_devdata *dd, अचिन्हित पूर्णांक source)
अणु
	स्थिर काष्ठा err_reg_info *eri = &dc_errs[source];

	अगर (eri->handler) अणु
		पूर्णांकerrupt_clear_करोwn(dd, 0, eri);
	पूर्ण अन्यथा अगर (source == 3 /* dc_lbm_पूर्णांक */) अणु
		/*
		 * This indicates that a parity error has occurred on the
		 * address/control lines presented to the LBM.  The error
		 * is a single pulse, there is no associated error flag,
		 * and it is non-maskable.  This is because अगर a parity
		 * error occurs on the request the request is dropped.
		 * This should never occur, but it is nice to know अगर it
		 * ever करोes.
		 */
		dd_dev_err(dd, "Parity error in DC LBM block\n");
	पूर्ण अन्यथा अणु
		dd_dev_err(dd, "Invalid DC interrupt %u\n", source);
	पूर्ण
पूर्ण

/*
 * TX block send credit पूर्णांकerrupt.  Source is < 160.
 */
अटल व्योम is_send_credit_पूर्णांक(काष्ठा hfi1_devdata *dd, अचिन्हित पूर्णांक source)
अणु
	sc_group_release_update(dd, source);
पूर्ण

/*
 * TX block SDMA पूर्णांकerrupt.  Source is < 48.
 *
 * SDMA पूर्णांकerrupts are grouped by type:
 *
 *	 0 -  N-1 = SDma
 *	 N - 2N-1 = SDmaProgress
 *	2N - 3N-1 = SDmaIdle
 */
अटल व्योम is_sdma_eng_पूर्णांक(काष्ठा hfi1_devdata *dd, अचिन्हित पूर्णांक source)
अणु
	/* what पूर्णांकerrupt */
	अचिन्हित पूर्णांक what  = source / TXE_NUM_SDMA_ENGINES;
	/* which engine */
	अचिन्हित पूर्णांक which = source % TXE_NUM_SDMA_ENGINES;

#अगर_घोषित CONFIG_SDMA_VERBOSITY
	dd_dev_err(dd, "CONFIG SDMA(%u) %s:%d %s()\n", which,
		   slashstrip(__खाता__), __LINE__, __func__);
	sdma_dumpstate(&dd->per_sdma[which]);
#पूर्ण_अगर

	अगर (likely(what < 3 && which < dd->num_sdma)) अणु
		sdma_engine_पूर्णांकerrupt(&dd->per_sdma[which], 1ull << source);
	पूर्ण अन्यथा अणु
		/* should not happen */
		dd_dev_err(dd, "Invalid SDMA interrupt 0x%x\n", source);
	पूर्ण
पूर्ण

/**
 * is_rcv_avail_पूर्णांक() - User receive context available IRQ handler
 * @dd: valid dd
 * @source: logical IRQ source (offset from IS_RCVAVAIL_START)
 *
 * RX block receive available पूर्णांकerrupt.  Source is < 160.
 *
 * This is the general पूर्णांकerrupt handler क्रम user (PSM) receive contexts,
 * and can only be used क्रम non-thपढ़ोed IRQs.
 */
अटल व्योम is_rcv_avail_पूर्णांक(काष्ठा hfi1_devdata *dd, अचिन्हित पूर्णांक source)
अणु
	काष्ठा hfi1_ctxtdata *rcd;
	अक्षर *err_detail;

	अगर (likely(source < dd->num_rcv_contexts)) अणु
		rcd = hfi1_rcd_get_by_index(dd, source);
		अगर (rcd) अणु
			handle_user_पूर्णांकerrupt(rcd);
			hfi1_rcd_put(rcd);
			वापस;	/* OK */
		पूर्ण
		/* received an पूर्णांकerrupt, but no rcd */
		err_detail = "dataless";
	पूर्ण अन्यथा अणु
		/* received an पूर्णांकerrupt, but are not using that context */
		err_detail = "out of range";
	पूर्ण
	dd_dev_err(dd, "unexpected %s receive available context interrupt %u\n",
		   err_detail, source);
पूर्ण

/**
 * is_rcv_urgent_पूर्णांक() - User receive context urgent IRQ handler
 * @dd: valid dd
 * @source: logical IRQ source (offset from IS_RCVURGENT_START)
 *
 * RX block receive urgent पूर्णांकerrupt.  Source is < 160.
 *
 * NOTE: kernel receive contexts specअगरically करो NOT enable this IRQ.
 */
अटल व्योम is_rcv_urgent_पूर्णांक(काष्ठा hfi1_devdata *dd, अचिन्हित पूर्णांक source)
अणु
	काष्ठा hfi1_ctxtdata *rcd;
	अक्षर *err_detail;

	अगर (likely(source < dd->num_rcv_contexts)) अणु
		rcd = hfi1_rcd_get_by_index(dd, source);
		अगर (rcd) अणु
			handle_user_पूर्णांकerrupt(rcd);
			hfi1_rcd_put(rcd);
			वापस;	/* OK */
		पूर्ण
		/* received an पूर्णांकerrupt, but no rcd */
		err_detail = "dataless";
	पूर्ण अन्यथा अणु
		/* received an पूर्णांकerrupt, but are not using that context */
		err_detail = "out of range";
	पूर्ण
	dd_dev_err(dd, "unexpected %s receive urgent context interrupt %u\n",
		   err_detail, source);
पूर्ण

/*
 * Reserved range पूर्णांकerrupt.  Should not be called in normal operation.
 */
अटल व्योम is_reserved_पूर्णांक(काष्ठा hfi1_devdata *dd, अचिन्हित पूर्णांक source)
अणु
	अक्षर name[64];

	dd_dev_err(dd, "unexpected %s interrupt\n",
		   is_reserved_name(name, माप(name), source));
पूर्ण

अटल स्थिर काष्ठा is_table is_table[] = अणु
/*
 * start		 end
 *				name func		पूर्णांकerrupt func
 */
अणु IS_GENERAL_ERR_START,  IS_GENERAL_ERR_END,
				is_misc_err_name,	is_misc_err_पूर्णांक पूर्ण,
अणु IS_SDMAENG_ERR_START,  IS_SDMAENG_ERR_END,
				is_sdma_eng_err_name,	is_sdma_eng_err_पूर्णांक पूर्ण,
अणु IS_SENDCTXT_ERR_START, IS_SENDCTXT_ERR_END,
				is_sendctxt_err_name,	is_sendctxt_err_पूर्णांक पूर्ण,
अणु IS_SDMA_START,	     IS_SDMA_IDLE_END,
				is_sdma_eng_name,	is_sdma_eng_पूर्णांक पूर्ण,
अणु IS_VARIOUS_START,	     IS_VARIOUS_END,
				is_various_name,	is_various_पूर्णांक पूर्ण,
अणु IS_DC_START,	     IS_DC_END,
				is_dc_name,		is_dc_पूर्णांक पूर्ण,
अणु IS_RCVAVAIL_START,     IS_RCVAVAIL_END,
				is_rcv_avail_name,	is_rcv_avail_पूर्णांक पूर्ण,
अणु IS_RCVURGENT_START,    IS_RCVURGENT_END,
				is_rcv_urgent_name,	is_rcv_urgent_पूर्णांक पूर्ण,
अणु IS_SENDCREDIT_START,   IS_SENDCREDIT_END,
				is_send_credit_name,	is_send_credit_पूर्णांकपूर्ण,
अणु IS_RESERVED_START,     IS_RESERVED_END,
				is_reserved_name,	is_reserved_पूर्णांकपूर्ण,
पूर्ण;

/*
 * Interrupt source पूर्णांकerrupt - called when the given source has an पूर्णांकerrupt.
 * Source is a bit index पूर्णांकo an array of 64-bit पूर्णांकegers.
 */
अटल व्योम is_पूर्णांकerrupt(काष्ठा hfi1_devdata *dd, अचिन्हित पूर्णांक source)
अणु
	स्थिर काष्ठा is_table *entry;

	/* aव्योमs a द्विगुन compare by walking the table in-order */
	क्रम (entry = &is_table[0]; entry->is_name; entry++) अणु
		अगर (source <= entry->end) अणु
			trace_hfi1_पूर्णांकerrupt(dd, entry, source);
			entry->is_पूर्णांक(dd, source - entry->start);
			वापस;
		पूर्ण
	पूर्ण
	/* fell off the end */
	dd_dev_err(dd, "invalid interrupt source %u\n", source);
पूर्ण

/**
 * general_पूर्णांकerrupt -  General पूर्णांकerrupt handler
 * @irq: MSIx IRQ vector
 * @data: hfi1 devdata
 *
 * This is able to correctly handle all non-thपढ़ोed पूर्णांकerrupts.  Receive
 * context DATA IRQs are thपढ़ोed and are not supported by this handler.
 *
 */
irqवापस_t general_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा hfi1_devdata *dd = data;
	u64 regs[CCE_NUM_INT_CSRS];
	u32 bit;
	पूर्णांक i;
	irqवापस_t handled = IRQ_NONE;

	this_cpu_inc(*dd->पूर्णांक_counter);

	/* phase 1: scan and clear all handled पूर्णांकerrupts */
	क्रम (i = 0; i < CCE_NUM_INT_CSRS; i++) अणु
		अगर (dd->gi_mask[i] == 0) अणु
			regs[i] = 0;	/* used later */
			जारी;
		पूर्ण
		regs[i] = पढ़ो_csr(dd, CCE_INT_STATUS + (8 * i)) &
				dd->gi_mask[i];
		/* only clear अगर anything is set */
		अगर (regs[i])
			ग_लिखो_csr(dd, CCE_INT_CLEAR + (8 * i), regs[i]);
	पूर्ण

	/* phase 2: call the appropriate handler */
	क्रम_each_set_bit(bit, (अचिन्हित दीर्घ *)&regs[0],
			 CCE_NUM_INT_CSRS * 64) अणु
		is_पूर्णांकerrupt(dd, bit);
		handled = IRQ_HANDLED;
	पूर्ण

	वापस handled;
पूर्ण

irqवापस_t sdma_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा sdma_engine *sde = data;
	काष्ठा hfi1_devdata *dd = sde->dd;
	u64 status;

#अगर_घोषित CONFIG_SDMA_VERBOSITY
	dd_dev_err(dd, "CONFIG SDMA(%u) %s:%d %s()\n", sde->this_idx,
		   slashstrip(__खाता__), __LINE__, __func__);
	sdma_dumpstate(sde);
#पूर्ण_अगर

	this_cpu_inc(*dd->पूर्णांक_counter);

	/* This पढ़ो_csr is really bad in the hot path */
	status = पढ़ो_csr(dd,
			  CCE_INT_STATUS + (8 * (IS_SDMA_START / 64)))
			  & sde->imask;
	अगर (likely(status)) अणु
		/* clear the पूर्णांकerrupt(s) */
		ग_लिखो_csr(dd,
			  CCE_INT_CLEAR + (8 * (IS_SDMA_START / 64)),
			  status);

		/* handle the पूर्णांकerrupt(s) */
		sdma_engine_पूर्णांकerrupt(sde, status);
	पूर्ण अन्यथा अणु
		dd_dev_info_ratelimited(dd, "SDMA engine %u interrupt, but no status bits set\n",
					sde->this_idx);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

/*
 * Clear the receive पूर्णांकerrupt.  Use a पढ़ो of the पूर्णांकerrupt clear CSR
 * to insure that the ग_लिखो completed.  This करोes NOT guarantee that
 * queued DMA ग_लिखोs to memory from the chip are pushed.
 */
अटल अंतरभूत व्योम clear_recv_पूर्णांकr(काष्ठा hfi1_ctxtdata *rcd)
अणु
	काष्ठा hfi1_devdata *dd = rcd->dd;
	u32 addr = CCE_INT_CLEAR + (8 * rcd->ireg);

	ग_लिखो_csr(dd, addr, rcd->imask);
	/* क्रमce the above ग_लिखो on the chip and get a value back */
	(व्योम)पढ़ो_csr(dd, addr);
पूर्ण

/* क्रमce the receive पूर्णांकerrupt */
व्योम क्रमce_recv_पूर्णांकr(काष्ठा hfi1_ctxtdata *rcd)
अणु
	ग_लिखो_csr(rcd->dd, CCE_INT_FORCE + (8 * rcd->ireg), rcd->imask);
पूर्ण

/*
 * Return non-zero अगर a packet is present.
 *
 * This routine is called when rechecking क्रम packets after the RcvAvail
 * पूर्णांकerrupt has been cleared करोwn.  First, करो a quick check of memory क्रम
 * a packet present.  If not found, use an expensive CSR पढ़ो of the context
 * tail to determine the actual tail.  The CSR पढ़ो is necessary because there
 * is no method to push pending DMAs to memory other than an पूर्णांकerrupt and we
 * are trying to determine अगर we need to क्रमce an पूर्णांकerrupt.
 */
अटल अंतरभूत पूर्णांक check_packet_present(काष्ठा hfi1_ctxtdata *rcd)
अणु
	u32 tail;

	अगर (hfi1_packet_present(rcd))
		वापस 1;

	/* fall back to a CSR पढ़ो, correct indpendent of DMA_RTAIL */
	tail = (u32)पढ़ो_uctxt_csr(rcd->dd, rcd->ctxt, RCV_HDR_TAIL);
	वापस hfi1_rcd_head(rcd) != tail;
पूर्ण

/*
 * Common code क्रम receive contexts पूर्णांकerrupt handlers.
 * Update traces, increment kernel IRQ counter and
 * setup ASPM when needed.
 */
अटल व्योम receive_पूर्णांकerrupt_common(काष्ठा hfi1_ctxtdata *rcd)
अणु
	काष्ठा hfi1_devdata *dd = rcd->dd;

	trace_hfi1_receive_पूर्णांकerrupt(dd, rcd);
	this_cpu_inc(*dd->पूर्णांक_counter);
	aspm_ctx_disable(rcd);
पूर्ण

/*
 * __hfi1_rcd_eoi_पूर्णांकr() - Make HW issue receive पूर्णांकerrupt
 * when there are packets present in the queue. When calling
 * with पूर्णांकerrupts enabled please use hfi1_rcd_eoi_पूर्णांकr.
 *
 * @rcd: valid receive context
 */
अटल व्योम __hfi1_rcd_eoi_पूर्णांकr(काष्ठा hfi1_ctxtdata *rcd)
अणु
	clear_recv_पूर्णांकr(rcd);
	अगर (check_packet_present(rcd))
		क्रमce_recv_पूर्णांकr(rcd);
पूर्ण

/**
 * hfi1_rcd_eoi_पूर्णांकr() - End of Interrupt processing action
 *
 * @rcd: Ptr to hfi1_ctxtdata of receive context
 *
 *  Hold IRQs so we can safely clear the पूर्णांकerrupt and
 *  recheck क्रम a packet that may have arrived after the previous
 *  check and the पूर्णांकerrupt clear.  If a packet arrived, क्रमce another
 *  पूर्णांकerrupt. This routine can be called at the end of receive packet
 *  processing in पूर्णांकerrupt service routines, पूर्णांकerrupt service thपढ़ो
 *  and softirqs
 */
अटल व्योम hfi1_rcd_eoi_पूर्णांकr(काष्ठा hfi1_ctxtdata *rcd)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	__hfi1_rcd_eoi_पूर्णांकr(rcd);
	local_irq_restore(flags);
पूर्ण

/**
 * hfi1_netdev_rx_napi - napi poll function to move eoi अंतरभूत
 * @napi: poपूर्णांकer to napi object
 * @budget: netdev budget
 */
पूर्णांक hfi1_netdev_rx_napi(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा hfi1_netdev_rxq *rxq = container_of(napi,
			काष्ठा hfi1_netdev_rxq, napi);
	काष्ठा hfi1_ctxtdata *rcd = rxq->rcd;
	पूर्णांक work_करोne = 0;

	work_करोne = rcd->करो_पूर्णांकerrupt(rcd, budget);

	अगर (work_करोne < budget) अणु
		napi_complete_करोne(napi, work_करोne);
		hfi1_rcd_eoi_पूर्णांकr(rcd);
	पूर्ण

	वापस work_करोne;
पूर्ण

/* Receive packet napi handler क्रम netdevs VNIC and AIP  */
irqवापस_t receive_context_पूर्णांकerrupt_napi(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा hfi1_ctxtdata *rcd = data;

	receive_पूर्णांकerrupt_common(rcd);

	अगर (likely(rcd->napi)) अणु
		अगर (likely(napi_schedule_prep(rcd->napi)))
			__napi_schedule_irqoff(rcd->napi);
		अन्यथा
			__hfi1_rcd_eoi_पूर्णांकr(rcd);
	पूर्ण अन्यथा अणु
		WARN_ONCE(1, "Napi IRQ handler without napi set up ctxt=%d\n",
			  rcd->ctxt);
		__hfi1_rcd_eoi_पूर्णांकr(rcd);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/*
 * Receive packet IRQ handler.  This routine expects to be on its own IRQ.
 * This routine will try to handle packets immediately (latency), but अगर
 * it finds too many, it will invoke the thपढ़ो handler (bandwitdh).  The
 * chip receive पूर्णांकerrupt is *not* cleared करोwn until this or the thपढ़ो (अगर
 * invoked) is finished.  The पूर्णांकent is to aव्योम extra पूर्णांकerrupts जबतक we
 * are processing packets anyway.
 */
irqवापस_t receive_context_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा hfi1_ctxtdata *rcd = data;
	पूर्णांक disposition;

	receive_पूर्णांकerrupt_common(rcd);

	/* receive पूर्णांकerrupt reमुख्यs blocked जबतक processing packets */
	disposition = rcd->करो_पूर्णांकerrupt(rcd, 0);

	/*
	 * Too many packets were seen जबतक processing packets in this
	 * IRQ handler.  Invoke the handler thपढ़ो.  The receive पूर्णांकerrupt
	 * reमुख्यs blocked.
	 */
	अगर (disposition == RCV_PKT_LIMIT)
		वापस IRQ_WAKE_THREAD;

	__hfi1_rcd_eoi_पूर्णांकr(rcd);
	वापस IRQ_HANDLED;
पूर्ण

/*
 * Receive packet thपढ़ो handler.  This expects to be invoked with the
 * receive पूर्णांकerrupt still blocked.
 */
irqवापस_t receive_context_thपढ़ो(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा hfi1_ctxtdata *rcd = data;

	/* receive पूर्णांकerrupt is still blocked from the IRQ handler */
	(व्योम)rcd->करो_पूर्णांकerrupt(rcd, 1);

	hfi1_rcd_eoi_पूर्णांकr(rcd);

	वापस IRQ_HANDLED;
पूर्ण

/* ========================================================================= */

u32 पढ़ो_physical_state(काष्ठा hfi1_devdata *dd)
अणु
	u64 reg;

	reg = पढ़ो_csr(dd, DC_DC8051_STS_CUR_STATE);
	वापस (reg >> DC_DC8051_STS_CUR_STATE_PORT_SHIFT)
				& DC_DC8051_STS_CUR_STATE_PORT_MASK;
पूर्ण

u32 पढ़ो_logical_state(काष्ठा hfi1_devdata *dd)
अणु
	u64 reg;

	reg = पढ़ो_csr(dd, DCC_CFG_PORT_CONFIG);
	वापस (reg >> DCC_CFG_PORT_CONFIG_LINK_STATE_SHIFT)
				& DCC_CFG_PORT_CONFIG_LINK_STATE_MASK;
पूर्ण

अटल व्योम set_logical_state(काष्ठा hfi1_devdata *dd, u32 chip_lstate)
अणु
	u64 reg;

	reg = पढ़ो_csr(dd, DCC_CFG_PORT_CONFIG);
	/* clear current state, set new state */
	reg &= ~DCC_CFG_PORT_CONFIG_LINK_STATE_SMASK;
	reg |= (u64)chip_lstate << DCC_CFG_PORT_CONFIG_LINK_STATE_SHIFT;
	ग_लिखो_csr(dd, DCC_CFG_PORT_CONFIG, reg);
पूर्ण

/*
 * Use the 8051 to पढ़ो a LCB CSR.
 */
अटल पूर्णांक पढ़ो_lcb_via_8051(काष्ठा hfi1_devdata *dd, u32 addr, u64 *data)
अणु
	u32 regno;
	पूर्णांक ret;

	अगर (dd->icode == ICODE_FUNCTIONAL_SIMULATOR) अणु
		अगर (acquire_lcb_access(dd, 0) == 0) अणु
			*data = पढ़ो_csr(dd, addr);
			release_lcb_access(dd, 0);
			वापस 0;
		पूर्ण
		वापस -EBUSY;
	पूर्ण

	/* रेजिस्टर is an index of LCB रेजिस्टरs: (offset - base) / 8 */
	regno = (addr - DC_LCB_CFG_RUN) >> 3;
	ret = करो_8051_command(dd, HCMD_READ_LCB_CSR, regno, data);
	अगर (ret != HCMD_SUCCESS)
		वापस -EBUSY;
	वापस 0;
पूर्ण

/*
 * Provide a cache क्रम some of the LCB रेजिस्टरs in हाल the LCB is
 * unavailable.
 * (The LCB is unavailable in certain link states, क्रम example.)
 */
काष्ठा lcb_datum अणु
	u32 off;
	u64 val;
पूर्ण;

अटल काष्ठा lcb_datum lcb_cache[] = अणु
	अणु DC_LCB_ERR_INFO_RX_REPLAY_CNT, 0पूर्ण,
	अणु DC_LCB_ERR_INFO_SEQ_CRC_CNT, 0 पूर्ण,
	अणु DC_LCB_ERR_INFO_REINIT_FROM_PEER_CNT, 0 पूर्ण,
पूर्ण;

अटल व्योम update_lcb_cache(काष्ठा hfi1_devdata *dd)
अणु
	पूर्णांक i;
	पूर्णांक ret;
	u64 val;

	क्रम (i = 0; i < ARRAY_SIZE(lcb_cache); i++) अणु
		ret = पढ़ो_lcb_csr(dd, lcb_cache[i].off, &val);

		/* Update अगर we get good data */
		अगर (likely(ret != -EBUSY))
			lcb_cache[i].val = val;
	पूर्ण
पूर्ण

अटल पूर्णांक पढ़ो_lcb_cache(u32 off, u64 *val)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(lcb_cache); i++) अणु
		अगर (lcb_cache[i].off == off) अणु
			*val = lcb_cache[i].val;
			वापस 0;
		पूर्ण
	पूर्ण

	pr_warn("%s bad offset 0x%x\n", __func__, off);
	वापस -1;
पूर्ण

/*
 * Read an LCB CSR.  Access may not be in host control, so check.
 * Return 0 on success, -EBUSY on failure.
 */
पूर्णांक पढ़ो_lcb_csr(काष्ठा hfi1_devdata *dd, u32 addr, u64 *data)
अणु
	काष्ठा hfi1_pportdata *ppd = dd->pport;

	/* अगर up, go through the 8051 क्रम the value */
	अगर (ppd->host_link_state & HLS_UP)
		वापस पढ़ो_lcb_via_8051(dd, addr, data);
	/* अगर going up or करोwn, check the cache, otherwise, no access */
	अगर (ppd->host_link_state & (HLS_GOING_UP | HLS_GOING_OFFLINE)) अणु
		अगर (पढ़ो_lcb_cache(addr, data))
			वापस -EBUSY;
		वापस 0;
	पूर्ण

	/* otherwise, host has access */
	*data = पढ़ो_csr(dd, addr);
	वापस 0;
पूर्ण

/*
 * Use the 8051 to ग_लिखो a LCB CSR.
 */
अटल पूर्णांक ग_लिखो_lcb_via_8051(काष्ठा hfi1_devdata *dd, u32 addr, u64 data)
अणु
	u32 regno;
	पूर्णांक ret;

	अगर (dd->icode == ICODE_FUNCTIONAL_SIMULATOR ||
	    (dd->dc8051_ver < dc8051_ver(0, 20, 0))) अणु
		अगर (acquire_lcb_access(dd, 0) == 0) अणु
			ग_लिखो_csr(dd, addr, data);
			release_lcb_access(dd, 0);
			वापस 0;
		पूर्ण
		वापस -EBUSY;
	पूर्ण

	/* रेजिस्टर is an index of LCB रेजिस्टरs: (offset - base) / 8 */
	regno = (addr - DC_LCB_CFG_RUN) >> 3;
	ret = करो_8051_command(dd, HCMD_WRITE_LCB_CSR, regno, &data);
	अगर (ret != HCMD_SUCCESS)
		वापस -EBUSY;
	वापस 0;
पूर्ण

/*
 * Write an LCB CSR.  Access may not be in host control, so check.
 * Return 0 on success, -EBUSY on failure.
 */
पूर्णांक ग_लिखो_lcb_csr(काष्ठा hfi1_devdata *dd, u32 addr, u64 data)
अणु
	काष्ठा hfi1_pportdata *ppd = dd->pport;

	/* अगर up, go through the 8051 क्रम the value */
	अगर (ppd->host_link_state & HLS_UP)
		वापस ग_लिखो_lcb_via_8051(dd, addr, data);
	/* अगर going up or करोwn, no access */
	अगर (ppd->host_link_state & (HLS_GOING_UP | HLS_GOING_OFFLINE))
		वापस -EBUSY;
	/* otherwise, host has access */
	ग_लिखो_csr(dd, addr, data);
	वापस 0;
पूर्ण

/*
 * Returns:
 *	< 0 = Linux error, not able to get access
 *	> 0 = 8051 command RETURN_CODE
 */
अटल पूर्णांक करो_8051_command(काष्ठा hfi1_devdata *dd, u32 type, u64 in_data,
			   u64 *out_data)
अणु
	u64 reg, completed;
	पूर्णांक वापस_code;
	अचिन्हित दीर्घ समयout;

	hfi1_cdbg(DC8051, "type %d, data 0x%012llx", type, in_data);

	mutex_lock(&dd->dc8051_lock);

	/* We can't send any commands to the 8051 if it's in reset */
	अगर (dd->dc_shutकरोwn) अणु
		वापस_code = -ENODEV;
		जाओ fail;
	पूर्ण

	/*
	 * If an 8051 host command समयd out previously, then the 8051 is
	 * stuck.
	 *
	 * On first समयout, attempt to reset and restart the entire DC
	 * block (including 8051). (Is this too big of a hammer?)
	 *
	 * If the 8051 बार out a second समय, the reset did not bring it
	 * back to healthy lअगरe. In that हाल, fail any subsequent commands.
	 */
	अगर (dd->dc8051_समयd_out) अणु
		अगर (dd->dc8051_समयd_out > 1) अणु
			dd_dev_err(dd,
				   "Previous 8051 host command timed out, skipping command %u\n",
				   type);
			वापस_code = -ENXIO;
			जाओ fail;
		पूर्ण
		_dc_shutकरोwn(dd);
		_dc_start(dd);
	पूर्ण

	/*
	 * If there is no समयout, then the 8051 command पूर्णांकerface is
	 * रुकोing क्रम a command.
	 */

	/*
	 * When writing a LCB CSR, out_data contains the full value to
	 * to be written, जबतक in_data contains the relative LCB
	 * address in 7:0.  Do the work here, rather than the caller,
	 * of distrubting the ग_लिखो data to where it needs to go:
	 *
	 * Write data
	 *   39:00 -> in_data[47:8]
	 *   47:40 -> DC8051_CFG_EXT_DEV_0.RETURN_CODE
	 *   63:48 -> DC8051_CFG_EXT_DEV_0.RSP_DATA
	 */
	अगर (type == HCMD_WRITE_LCB_CSR) अणु
		in_data |= ((*out_data) & 0xffffffffffull) << 8;
		/* must preserve COMPLETED - it is tied to hardware */
		reg = पढ़ो_csr(dd, DC_DC8051_CFG_EXT_DEV_0);
		reg &= DC_DC8051_CFG_EXT_DEV_0_COMPLETED_SMASK;
		reg |= ((((*out_data) >> 40) & 0xff) <<
				DC_DC8051_CFG_EXT_DEV_0_RETURN_CODE_SHIFT)
		      | ((((*out_data) >> 48) & 0xffff) <<
				DC_DC8051_CFG_EXT_DEV_0_RSP_DATA_SHIFT);
		ग_लिखो_csr(dd, DC_DC8051_CFG_EXT_DEV_0, reg);
	पूर्ण

	/*
	 * Do two ग_लिखोs: the first to stabilize the type and req_data, the
	 * second to activate.
	 */
	reg = ((u64)type & DC_DC8051_CFG_HOST_CMD_0_REQ_TYPE_MASK)
			<< DC_DC8051_CFG_HOST_CMD_0_REQ_TYPE_SHIFT
		| (in_data & DC_DC8051_CFG_HOST_CMD_0_REQ_DATA_MASK)
			<< DC_DC8051_CFG_HOST_CMD_0_REQ_DATA_SHIFT;
	ग_लिखो_csr(dd, DC_DC8051_CFG_HOST_CMD_0, reg);
	reg |= DC_DC8051_CFG_HOST_CMD_0_REQ_NEW_SMASK;
	ग_लिखो_csr(dd, DC_DC8051_CFG_HOST_CMD_0, reg);

	/* रुको क्रम completion, alternate: पूर्णांकerrupt */
	समयout = jअगरfies + msecs_to_jअगरfies(DC8051_COMMAND_TIMEOUT);
	जबतक (1) अणु
		reg = पढ़ो_csr(dd, DC_DC8051_CFG_HOST_CMD_1);
		completed = reg & DC_DC8051_CFG_HOST_CMD_1_COMPLETED_SMASK;
		अगर (completed)
			अवरोध;
		अगर (समय_after(jअगरfies, समयout)) अणु
			dd->dc8051_समयd_out++;
			dd_dev_err(dd, "8051 host command %u timeout\n", type);
			अगर (out_data)
				*out_data = 0;
			वापस_code = -ETIMEDOUT;
			जाओ fail;
		पूर्ण
		udelay(2);
	पूर्ण

	अगर (out_data) अणु
		*out_data = (reg >> DC_DC8051_CFG_HOST_CMD_1_RSP_DATA_SHIFT)
				& DC_DC8051_CFG_HOST_CMD_1_RSP_DATA_MASK;
		अगर (type == HCMD_READ_LCB_CSR) अणु
			/* top 16 bits are in a dअगरferent रेजिस्टर */
			*out_data |= (पढ़ो_csr(dd, DC_DC8051_CFG_EXT_DEV_1)
				& DC_DC8051_CFG_EXT_DEV_1_REQ_DATA_SMASK)
				<< (48
				    - DC_DC8051_CFG_EXT_DEV_1_REQ_DATA_SHIFT);
		पूर्ण
	पूर्ण
	वापस_code = (reg >> DC_DC8051_CFG_HOST_CMD_1_RETURN_CODE_SHIFT)
				& DC_DC8051_CFG_HOST_CMD_1_RETURN_CODE_MASK;
	dd->dc8051_समयd_out = 0;
	/*
	 * Clear command क्रम next user.
	 */
	ग_लिखो_csr(dd, DC_DC8051_CFG_HOST_CMD_0, 0);

fail:
	mutex_unlock(&dd->dc8051_lock);
	वापस वापस_code;
पूर्ण

अटल पूर्णांक set_physical_link_state(काष्ठा hfi1_devdata *dd, u64 state)
अणु
	वापस करो_8051_command(dd, HCMD_CHANGE_PHY_STATE, state, शून्य);
पूर्ण

पूर्णांक load_8051_config(काष्ठा hfi1_devdata *dd, u8 field_id,
		     u8 lane_id, u32 config_data)
अणु
	u64 data;
	पूर्णांक ret;

	data = (u64)field_id << LOAD_DATA_FIELD_ID_SHIFT
		| (u64)lane_id << LOAD_DATA_LANE_ID_SHIFT
		| (u64)config_data << LOAD_DATA_DATA_SHIFT;
	ret = करो_8051_command(dd, HCMD_LOAD_CONFIG_DATA, data, शून्य);
	अगर (ret != HCMD_SUCCESS) अणु
		dd_dev_err(dd,
			   "load 8051 config: field id %d, lane %d, err %d\n",
			   (पूर्णांक)field_id, (पूर्णांक)lane_id, ret);
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Read the 8051 firmware "registers".  Use the RAM directly.  Always
 * set the result, even on error.
 * Return 0 on success, -त्रुटि_सं on failure
 */
पूर्णांक पढ़ो_8051_config(काष्ठा hfi1_devdata *dd, u8 field_id, u8 lane_id,
		     u32 *result)
अणु
	u64 big_data;
	u32 addr;
	पूर्णांक ret;

	/* address start depends on the lane_id */
	अगर (lane_id < 4)
		addr = (4 * NUM_GENERAL_FIELDS)
			+ (lane_id * 4 * NUM_LANE_FIELDS);
	अन्यथा
		addr = 0;
	addr += field_id * 4;

	/* पढ़ो is in 8-byte chunks, hardware will truncate the address करोwn */
	ret = पढ़ो_8051_data(dd, addr, 8, &big_data);

	अगर (ret == 0) अणु
		/* extract the 4 bytes we want */
		अगर (addr & 0x4)
			*result = (u32)(big_data >> 32);
		अन्यथा
			*result = (u32)big_data;
	पूर्ण अन्यथा अणु
		*result = 0;
		dd_dev_err(dd, "%s: direct read failed, lane %d, field %d!\n",
			   __func__, lane_id, field_id);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ग_लिखो_vc_local_phy(काष्ठा hfi1_devdata *dd, u8 घातer_management,
			      u8 continuous)
अणु
	u32 frame;

	frame = continuous << CONTINIOUS_REMOTE_UPDATE_SUPPORT_SHIFT
		| घातer_management << POWER_MANAGEMENT_SHIFT;
	वापस load_8051_config(dd, VERIFY_CAP_LOCAL_PHY,
				GENERAL_CONFIG, frame);
पूर्ण

अटल पूर्णांक ग_लिखो_vc_local_fabric(काष्ठा hfi1_devdata *dd, u8 vau, u8 z, u8 vcu,
				 u16 vl15buf, u8 crc_sizes)
अणु
	u32 frame;

	frame = (u32)vau << VAU_SHIFT
		| (u32)z << Z_SHIFT
		| (u32)vcu << VCU_SHIFT
		| (u32)vl15buf << VL15BUF_SHIFT
		| (u32)crc_sizes << CRC_SIZES_SHIFT;
	वापस load_8051_config(dd, VERIFY_CAP_LOCAL_FABRIC,
				GENERAL_CONFIG, frame);
पूर्ण

अटल व्योम पढ़ो_vc_local_link_mode(काष्ठा hfi1_devdata *dd, u8 *misc_bits,
				    u8 *flag_bits, u16 *link_widths)
अणु
	u32 frame;

	पढ़ो_8051_config(dd, VERIFY_CAP_LOCAL_LINK_MODE, GENERAL_CONFIG,
			 &frame);
	*misc_bits = (frame >> MISC_CONFIG_BITS_SHIFT) & MISC_CONFIG_BITS_MASK;
	*flag_bits = (frame >> LOCAL_FLAG_BITS_SHIFT) & LOCAL_FLAG_BITS_MASK;
	*link_widths = (frame >> LINK_WIDTH_SHIFT) & LINK_WIDTH_MASK;
पूर्ण

अटल पूर्णांक ग_लिखो_vc_local_link_mode(काष्ठा hfi1_devdata *dd,
				    u8 misc_bits,
				    u8 flag_bits,
				    u16 link_widths)
अणु
	u32 frame;

	frame = (u32)misc_bits << MISC_CONFIG_BITS_SHIFT
		| (u32)flag_bits << LOCAL_FLAG_BITS_SHIFT
		| (u32)link_widths << LINK_WIDTH_SHIFT;
	वापस load_8051_config(dd, VERIFY_CAP_LOCAL_LINK_MODE, GENERAL_CONFIG,
		     frame);
पूर्ण

अटल पूर्णांक ग_लिखो_local_device_id(काष्ठा hfi1_devdata *dd, u16 device_id,
				 u8 device_rev)
अणु
	u32 frame;

	frame = ((u32)device_id << LOCAL_DEVICE_ID_SHIFT)
		| ((u32)device_rev << LOCAL_DEVICE_REV_SHIFT);
	वापस load_8051_config(dd, LOCAL_DEVICE_ID, GENERAL_CONFIG, frame);
पूर्ण

अटल व्योम पढ़ो_remote_device_id(काष्ठा hfi1_devdata *dd, u16 *device_id,
				  u8 *device_rev)
अणु
	u32 frame;

	पढ़ो_8051_config(dd, REMOTE_DEVICE_ID, GENERAL_CONFIG, &frame);
	*device_id = (frame >> REMOTE_DEVICE_ID_SHIFT) & REMOTE_DEVICE_ID_MASK;
	*device_rev = (frame >> REMOTE_DEVICE_REV_SHIFT)
			& REMOTE_DEVICE_REV_MASK;
पूर्ण

पूर्णांक ग_लिखो_host_पूर्णांकerface_version(काष्ठा hfi1_devdata *dd, u8 version)
अणु
	u32 frame;
	u32 mask;

	mask = (HOST_INTERFACE_VERSION_MASK << HOST_INTERFACE_VERSION_SHIFT);
	पढ़ो_8051_config(dd, RESERVED_REGISTERS, GENERAL_CONFIG, &frame);
	/* Clear, then set field */
	frame &= ~mask;
	frame |= ((u32)version << HOST_INTERFACE_VERSION_SHIFT);
	वापस load_8051_config(dd, RESERVED_REGISTERS, GENERAL_CONFIG,
				frame);
पूर्ण

व्योम पढ़ो_misc_status(काष्ठा hfi1_devdata *dd, u8 *ver_major, u8 *ver_minor,
		      u8 *ver_patch)
अणु
	u32 frame;

	पढ़ो_8051_config(dd, MISC_STATUS, GENERAL_CONFIG, &frame);
	*ver_major = (frame >> STS_FM_VERSION_MAJOR_SHIFT) &
		STS_FM_VERSION_MAJOR_MASK;
	*ver_minor = (frame >> STS_FM_VERSION_MINOR_SHIFT) &
		STS_FM_VERSION_MINOR_MASK;

	पढ़ो_8051_config(dd, VERSION_PATCH, GENERAL_CONFIG, &frame);
	*ver_patch = (frame >> STS_FM_VERSION_PATCH_SHIFT) &
		STS_FM_VERSION_PATCH_MASK;
पूर्ण

अटल व्योम पढ़ो_vc_remote_phy(काष्ठा hfi1_devdata *dd, u8 *घातer_management,
			       u8 *continuous)
अणु
	u32 frame;

	पढ़ो_8051_config(dd, VERIFY_CAP_REMOTE_PHY, GENERAL_CONFIG, &frame);
	*घातer_management = (frame >> POWER_MANAGEMENT_SHIFT)
					& POWER_MANAGEMENT_MASK;
	*continuous = (frame >> CONTINIOUS_REMOTE_UPDATE_SUPPORT_SHIFT)
					& CONTINIOUS_REMOTE_UPDATE_SUPPORT_MASK;
पूर्ण

अटल व्योम पढ़ो_vc_remote_fabric(काष्ठा hfi1_devdata *dd, u8 *vau, u8 *z,
				  u8 *vcu, u16 *vl15buf, u8 *crc_sizes)
अणु
	u32 frame;

	पढ़ो_8051_config(dd, VERIFY_CAP_REMOTE_FABRIC, GENERAL_CONFIG, &frame);
	*vau = (frame >> VAU_SHIFT) & VAU_MASK;
	*z = (frame >> Z_SHIFT) & Z_MASK;
	*vcu = (frame >> VCU_SHIFT) & VCU_MASK;
	*vl15buf = (frame >> VL15BUF_SHIFT) & VL15BUF_MASK;
	*crc_sizes = (frame >> CRC_SIZES_SHIFT) & CRC_SIZES_MASK;
पूर्ण

अटल व्योम पढ़ो_vc_remote_link_width(काष्ठा hfi1_devdata *dd,
				      u8 *remote_tx_rate,
				      u16 *link_widths)
अणु
	u32 frame;

	पढ़ो_8051_config(dd, VERIFY_CAP_REMOTE_LINK_WIDTH, GENERAL_CONFIG,
			 &frame);
	*remote_tx_rate = (frame >> REMOTE_TX_RATE_SHIFT)
				& REMOTE_TX_RATE_MASK;
	*link_widths = (frame >> LINK_WIDTH_SHIFT) & LINK_WIDTH_MASK;
पूर्ण

अटल व्योम पढ़ो_local_lni(काष्ठा hfi1_devdata *dd, u8 *enable_lane_rx)
अणु
	u32 frame;

	पढ़ो_8051_config(dd, LOCAL_LNI_INFO, GENERAL_CONFIG, &frame);
	*enable_lane_rx = (frame >> ENABLE_LANE_RX_SHIFT) & ENABLE_LANE_RX_MASK;
पूर्ण

अटल व्योम पढ़ो_last_local_state(काष्ठा hfi1_devdata *dd, u32 *lls)
अणु
	पढ़ो_8051_config(dd, LAST_LOCAL_STATE_COMPLETE, GENERAL_CONFIG, lls);
पूर्ण

अटल व्योम पढ़ो_last_remote_state(काष्ठा hfi1_devdata *dd, u32 *lrs)
अणु
	पढ़ो_8051_config(dd, LAST_REMOTE_STATE_COMPLETE, GENERAL_CONFIG, lrs);
पूर्ण

व्योम hfi1_पढ़ो_link_quality(काष्ठा hfi1_devdata *dd, u8 *link_quality)
अणु
	u32 frame;
	पूर्णांक ret;

	*link_quality = 0;
	अगर (dd->pport->host_link_state & HLS_UP) अणु
		ret = पढ़ो_8051_config(dd, LINK_QUALITY_INFO, GENERAL_CONFIG,
				       &frame);
		अगर (ret == 0)
			*link_quality = (frame >> LINK_QUALITY_SHIFT)
						& LINK_QUALITY_MASK;
	पूर्ण
पूर्ण

अटल व्योम पढ़ो_planned_करोwn_reason_code(काष्ठा hfi1_devdata *dd, u8 *pdrrc)
अणु
	u32 frame;

	पढ़ो_8051_config(dd, LINK_QUALITY_INFO, GENERAL_CONFIG, &frame);
	*pdrrc = (frame >> DOWN_REMOTE_REASON_SHIFT) & DOWN_REMOTE_REASON_MASK;
पूर्ण

अटल व्योम पढ़ो_link_करोwn_reason(काष्ठा hfi1_devdata *dd, u8 *ldr)
अणु
	u32 frame;

	पढ़ो_8051_config(dd, LINK_DOWN_REASON, GENERAL_CONFIG, &frame);
	*ldr = (frame & 0xff);
पूर्ण

अटल पूर्णांक पढ़ो_tx_settings(काष्ठा hfi1_devdata *dd,
			    u8 *enable_lane_tx,
			    u8 *tx_polarity_inversion,
			    u8 *rx_polarity_inversion,
			    u8 *max_rate)
अणु
	u32 frame;
	पूर्णांक ret;

	ret = पढ़ो_8051_config(dd, TX_SETTINGS, GENERAL_CONFIG, &frame);
	*enable_lane_tx = (frame >> ENABLE_LANE_TX_SHIFT)
				& ENABLE_LANE_TX_MASK;
	*tx_polarity_inversion = (frame >> TX_POLARITY_INVERSION_SHIFT)
				& TX_POLARITY_INVERSION_MASK;
	*rx_polarity_inversion = (frame >> RX_POLARITY_INVERSION_SHIFT)
				& RX_POLARITY_INVERSION_MASK;
	*max_rate = (frame >> MAX_RATE_SHIFT) & MAX_RATE_MASK;
	वापस ret;
पूर्ण

अटल पूर्णांक ग_लिखो_tx_settings(काष्ठा hfi1_devdata *dd,
			     u8 enable_lane_tx,
			     u8 tx_polarity_inversion,
			     u8 rx_polarity_inversion,
			     u8 max_rate)
अणु
	u32 frame;

	/* no need to mask, all variable sizes match field widths */
	frame = enable_lane_tx << ENABLE_LANE_TX_SHIFT
		| tx_polarity_inversion << TX_POLARITY_INVERSION_SHIFT
		| rx_polarity_inversion << RX_POLARITY_INVERSION_SHIFT
		| max_rate << MAX_RATE_SHIFT;
	वापस load_8051_config(dd, TX_SETTINGS, GENERAL_CONFIG, frame);
पूर्ण

/*
 * Read an idle LCB message.
 *
 * Returns 0 on success, -EINVAL on error
 */
अटल पूर्णांक पढ़ो_idle_message(काष्ठा hfi1_devdata *dd, u64 type, u64 *data_out)
अणु
	पूर्णांक ret;

	ret = करो_8051_command(dd, HCMD_READ_LCB_IDLE_MSG, type, data_out);
	अगर (ret != HCMD_SUCCESS) अणु
		dd_dev_err(dd, "read idle message: type %d, err %d\n",
			   (u32)type, ret);
		वापस -EINVAL;
	पूर्ण
	dd_dev_info(dd, "%s: read idle message 0x%llx\n", __func__, *data_out);
	/* वापस only the payload as we alपढ़ोy know the type */
	*data_out >>= IDLE_PAYLOAD_SHIFT;
	वापस 0;
पूर्ण

/*
 * Read an idle SMA message.  To be करोne in response to a notअगरication from
 * the 8051.
 *
 * Returns 0 on success, -EINVAL on error
 */
अटल पूर्णांक पढ़ो_idle_sma(काष्ठा hfi1_devdata *dd, u64 *data)
अणु
	वापस पढ़ो_idle_message(dd, (u64)IDLE_SMA << IDLE_MSG_TYPE_SHIFT,
				 data);
पूर्ण

/*
 * Send an idle LCB message.
 *
 * Returns 0 on success, -EINVAL on error
 */
अटल पूर्णांक send_idle_message(काष्ठा hfi1_devdata *dd, u64 data)
अणु
	पूर्णांक ret;

	dd_dev_info(dd, "%s: sending idle message 0x%llx\n", __func__, data);
	ret = करो_8051_command(dd, HCMD_SEND_LCB_IDLE_MSG, data, शून्य);
	अगर (ret != HCMD_SUCCESS) अणु
		dd_dev_err(dd, "send idle message: data 0x%llx, err %d\n",
			   data, ret);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Send an idle SMA message.
 *
 * Returns 0 on success, -EINVAL on error
 */
पूर्णांक send_idle_sma(काष्ठा hfi1_devdata *dd, u64 message)
अणु
	u64 data;

	data = ((message & IDLE_PAYLOAD_MASK) << IDLE_PAYLOAD_SHIFT) |
		((u64)IDLE_SMA << IDLE_MSG_TYPE_SHIFT);
	वापस send_idle_message(dd, data);
पूर्ण

/*
 * Initialize the LCB then करो a quick link up.  This may or may not be
 * in loopback.
 *
 * वापस 0 on success, -त्रुटि_सं on error
 */
अटल पूर्णांक करो_quick_linkup(काष्ठा hfi1_devdata *dd)
अणु
	पूर्णांक ret;

	lcb_shutकरोwn(dd, 0);

	अगर (loopback) अणु
		/* LCB_CFG_LOOPBACK.VAL = 2 */
		/* LCB_CFG_LANE_WIDTH.VAL = 0 */
		ग_लिखो_csr(dd, DC_LCB_CFG_LOOPBACK,
			  IB_PACKET_TYPE << DC_LCB_CFG_LOOPBACK_VAL_SHIFT);
		ग_लिखो_csr(dd, DC_LCB_CFG_LANE_WIDTH, 0);
	पूर्ण

	/* start the LCBs */
	/* LCB_CFG_TX_FIFOS_RESET.VAL = 0 */
	ग_लिखो_csr(dd, DC_LCB_CFG_TX_FIFOS_RESET, 0);

	/* simulator only loopback steps */
	अगर (loopback && dd->icode == ICODE_FUNCTIONAL_SIMULATOR) अणु
		/* LCB_CFG_RUN.EN = 1 */
		ग_लिखो_csr(dd, DC_LCB_CFG_RUN,
			  1ull << DC_LCB_CFG_RUN_EN_SHIFT);

		ret = रुको_link_transfer_active(dd, 10);
		अगर (ret)
			वापस ret;

		ग_लिखो_csr(dd, DC_LCB_CFG_ALLOW_LINK_UP,
			  1ull << DC_LCB_CFG_ALLOW_LINK_UP_VAL_SHIFT);
	पूर्ण

	अगर (!loopback) अणु
		/*
		 * When करोing quick linkup and not in loopback, both
		 * sides must be करोne with LCB set-up beक्रमe either
		 * starts the quick linkup.  Put a delay here so that
		 * both sides can be started and have a chance to be
		 * करोne with LCB set up beक्रमe resuming.
		 */
		dd_dev_err(dd,
			   "Pausing for peer to be finished with LCB set up\n");
		msleep(5000);
		dd_dev_err(dd, "Continuing with quick linkup\n");
	पूर्ण

	ग_लिखो_csr(dd, DC_LCB_ERR_EN, 0); /* mask LCB errors */
	set_8051_lcb_access(dd);

	/*
	 * State "quick" LinkUp request sets the physical link state to
	 * LinkUp without a verअगरy capability sequence.
	 * This state is in simulator v37 and later.
	 */
	ret = set_physical_link_state(dd, PLS_QUICK_LINKUP);
	अगर (ret != HCMD_SUCCESS) अणु
		dd_dev_err(dd,
			   "%s: set physical link state to quick LinkUp failed with return %d\n",
			   __func__, ret);

		set_host_lcb_access(dd);
		ग_लिखो_csr(dd, DC_LCB_ERR_EN, ~0ull); /* watch LCB errors */

		अगर (ret >= 0)
			ret = -EINVAL;
		वापस ret;
	पूर्ण

	वापस 0; /* success */
पूर्ण

/*
 * Do all special steps to set up loopback.
 */
अटल पूर्णांक init_loopback(काष्ठा hfi1_devdata *dd)
अणु
	dd_dev_info(dd, "Entering loopback mode\n");

	/* all loopbacks should disable self GUID check */
	ग_लिखो_csr(dd, DC_DC8051_CFG_MODE,
		  (पढ़ो_csr(dd, DC_DC8051_CFG_MODE) | DISABLE_SELF_GUID_CHECK));

	/*
	 * The simulator has only one loopback option - LCB.  Switch
	 * to that option, which includes quick link up.
	 *
	 * Accept all valid loopback values.
	 */
	अगर ((dd->icode == ICODE_FUNCTIONAL_SIMULATOR) &&
	    (loopback == LOOPBACK_SERDES || loopback == LOOPBACK_LCB ||
	     loopback == LOOPBACK_CABLE)) अणु
		loopback = LOOPBACK_LCB;
		quick_linkup = 1;
		वापस 0;
	पूर्ण

	/*
	 * SerDes loopback init sequence is handled in set_local_link_attributes
	 */
	अगर (loopback == LOOPBACK_SERDES)
		वापस 0;

	/* LCB loopback - handled at poll समय */
	अगर (loopback == LOOPBACK_LCB) अणु
		quick_linkup = 1; /* LCB is always quick linkup */

		/* not supported in emulation due to emulation RTL changes */
		अगर (dd->icode == ICODE_FPGA_EMULATION) अणु
			dd_dev_err(dd,
				   "LCB loopback not supported in emulation\n");
			वापस -EINVAL;
		पूर्ण
		वापस 0;
	पूर्ण

	/* बाह्यal cable loopback requires no extra steps */
	अगर (loopback == LOOPBACK_CABLE)
		वापस 0;

	dd_dev_err(dd, "Invalid loopback mode %d\n", loopback);
	वापस -EINVAL;
पूर्ण

/*
 * Translate from the OPA_LINK_WIDTH handed to us by the FM to bits
 * used in the Verअगरy Capability link width attribute.
 */
अटल u16 opa_to_vc_link_widths(u16 opa_widths)
अणु
	पूर्णांक i;
	u16 result = 0;

	अटल स्थिर काष्ठा link_bits अणु
		u16 from;
		u16 to;
	पूर्ण opa_link_xlate[] = अणु
		अणु OPA_LINK_WIDTH_1X, 1 << (1 - 1)  पूर्ण,
		अणु OPA_LINK_WIDTH_2X, 1 << (2 - 1)  पूर्ण,
		अणु OPA_LINK_WIDTH_3X, 1 << (3 - 1)  पूर्ण,
		अणु OPA_LINK_WIDTH_4X, 1 << (4 - 1)  पूर्ण,
	पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(opa_link_xlate); i++) अणु
		अगर (opa_widths & opa_link_xlate[i].from)
			result |= opa_link_xlate[i].to;
	पूर्ण
	वापस result;
पूर्ण

/*
 * Set link attributes beक्रमe moving to polling.
 */
अटल पूर्णांक set_local_link_attributes(काष्ठा hfi1_pportdata *ppd)
अणु
	काष्ठा hfi1_devdata *dd = ppd->dd;
	u8 enable_lane_tx;
	u8 tx_polarity_inversion;
	u8 rx_polarity_inversion;
	पूर्णांक ret;
	u32 misc_bits = 0;
	/* reset our fabric serdes to clear any lingering problems */
	fabric_serdes_reset(dd);

	/* set the local tx rate - need to पढ़ो-modअगरy-ग_लिखो */
	ret = पढ़ो_tx_settings(dd, &enable_lane_tx, &tx_polarity_inversion,
			       &rx_polarity_inversion, &ppd->local_tx_rate);
	अगर (ret)
		जाओ set_local_link_attributes_fail;

	अगर (dd->dc8051_ver < dc8051_ver(0, 20, 0)) अणु
		/* set the tx rate to the fastest enabled */
		अगर (ppd->link_speed_enabled & OPA_LINK_SPEED_25G)
			ppd->local_tx_rate = 1;
		अन्यथा
			ppd->local_tx_rate = 0;
	पूर्ण अन्यथा अणु
		/* set the tx rate to all enabled */
		ppd->local_tx_rate = 0;
		अगर (ppd->link_speed_enabled & OPA_LINK_SPEED_25G)
			ppd->local_tx_rate |= 2;
		अगर (ppd->link_speed_enabled & OPA_LINK_SPEED_12_5G)
			ppd->local_tx_rate |= 1;
	पूर्ण

	enable_lane_tx = 0xF; /* enable all four lanes */
	ret = ग_लिखो_tx_settings(dd, enable_lane_tx, tx_polarity_inversion,
				rx_polarity_inversion, ppd->local_tx_rate);
	अगर (ret != HCMD_SUCCESS)
		जाओ set_local_link_attributes_fail;

	ret = ग_लिखो_host_पूर्णांकerface_version(dd, HOST_INTERFACE_VERSION);
	अगर (ret != HCMD_SUCCESS) अणु
		dd_dev_err(dd,
			   "Failed to set host interface version, return 0x%x\n",
			   ret);
		जाओ set_local_link_attributes_fail;
	पूर्ण

	/*
	 * DC supports continuous updates.
	 */
	ret = ग_लिखो_vc_local_phy(dd,
				 0 /* no घातer management */,
				 1 /* continuous updates */);
	अगर (ret != HCMD_SUCCESS)
		जाओ set_local_link_attributes_fail;

	/* z=1 in the next call: AU of 0 is not supported by the hardware */
	ret = ग_लिखो_vc_local_fabric(dd, dd->vau, 1, dd->vcu, dd->vl15_init,
				    ppd->port_crc_mode_enabled);
	अगर (ret != HCMD_SUCCESS)
		जाओ set_local_link_attributes_fail;

	/*
	 * SerDes loopback init sequence requires
	 * setting bit 0 of MISC_CONFIG_BITS
	 */
	अगर (loopback == LOOPBACK_SERDES)
		misc_bits |= 1 << LOOPBACK_SERDES_CONFIG_BIT_MASK_SHIFT;

	/*
	 * An बाह्यal device configuration request is used to reset the LCB
	 * to retry to obtain operational lanes when the first attempt is
	 * unsuccesful.
	 */
	अगर (dd->dc8051_ver >= dc8051_ver(1, 25, 0))
		misc_bits |= 1 << EXT_CFG_LCB_RESET_SUPPORTED_SHIFT;

	ret = ग_लिखो_vc_local_link_mode(dd, misc_bits, 0,
				       opa_to_vc_link_widths(
						ppd->link_width_enabled));
	अगर (ret != HCMD_SUCCESS)
		जाओ set_local_link_attributes_fail;

	/* let peer know who we are */
	ret = ग_लिखो_local_device_id(dd, dd->pcidev->device, dd->minrev);
	अगर (ret == HCMD_SUCCESS)
		वापस 0;

set_local_link_attributes_fail:
	dd_dev_err(dd,
		   "Failed to set local link attributes, return 0x%x\n",
		   ret);
	वापस ret;
पूर्ण

/*
 * Call this to start the link.
 * Do not करो anything अगर the link is disabled.
 * Returns 0 अगर link is disabled, moved to polling, or the driver is not पढ़ोy.
 */
पूर्णांक start_link(काष्ठा hfi1_pportdata *ppd)
अणु
	/*
	 * Tune the SerDes to a ballpark setting क्रम optimal संकेत and bit
	 * error rate.  Needs to be करोne beक्रमe starting the link.
	 */
	tune_serdes(ppd);

	अगर (!ppd->driver_link_पढ़ोy) अणु
		dd_dev_info(ppd->dd,
			    "%s: stopping link start because driver is not ready\n",
			    __func__);
		वापस 0;
	पूर्ण

	/*
	 * FULL_MGMT_P_KEY is cleared from the pkey table, so that the
	 * pkey table can be configured properly अगर the HFI unit is connected
	 * to चयन port with MgmtAllowed=NO
	 */
	clear_full_mgmt_pkey(ppd);

	वापस set_link_state(ppd, HLS_DN_POLL);
पूर्ण

अटल व्योम रुको_क्रम_qsfp_init(काष्ठा hfi1_pportdata *ppd)
अणु
	काष्ठा hfi1_devdata *dd = ppd->dd;
	u64 mask;
	अचिन्हित दीर्घ समयout;

	/*
	 * Some QSFP cables have a quirk that निश्चितs the IntN line as a side
	 * effect of घातer up on plug-in. We ignore this false positive
	 * पूर्णांकerrupt until the module has finished घातering up by रुकोing क्रम
	 * a minimum समयout of the module inrush initialization समय of
	 * 500 ms (SFF 8679 Table 5-6) to ensure the voltage rails in the
	 * module have stabilized.
	 */
	msleep(500);

	/*
	 * Check क्रम QSFP पूर्णांकerrupt क्रम t_init (SFF 8679 Table 8-1)
	 */
	समयout = jअगरfies + msecs_to_jअगरfies(2000);
	जबतक (1) अणु
		mask = पढ़ो_csr(dd, dd->hfi1_id ?
				ASIC_QSFP2_IN : ASIC_QSFP1_IN);
		अगर (!(mask & QSFP_HFI0_INT_N))
			अवरोध;
		अगर (समय_after(jअगरfies, समयout)) अणु
			dd_dev_info(dd, "%s: No IntN detected, reset complete\n",
				    __func__);
			अवरोध;
		पूर्ण
		udelay(2);
	पूर्ण
पूर्ण

अटल व्योम set_qsfp_पूर्णांक_n(काष्ठा hfi1_pportdata *ppd, u8 enable)
अणु
	काष्ठा hfi1_devdata *dd = ppd->dd;
	u64 mask;

	mask = पढ़ो_csr(dd, dd->hfi1_id ? ASIC_QSFP2_MASK : ASIC_QSFP1_MASK);
	अगर (enable) अणु
		/*
		 * Clear the status रेजिस्टर to aव्योम an immediate पूर्णांकerrupt
		 * when we re-enable the IntN pin
		 */
		ग_लिखो_csr(dd, dd->hfi1_id ? ASIC_QSFP2_CLEAR : ASIC_QSFP1_CLEAR,
			  QSFP_HFI0_INT_N);
		mask |= (u64)QSFP_HFI0_INT_N;
	पूर्ण अन्यथा अणु
		mask &= ~(u64)QSFP_HFI0_INT_N;
	पूर्ण
	ग_लिखो_csr(dd, dd->hfi1_id ? ASIC_QSFP2_MASK : ASIC_QSFP1_MASK, mask);
पूर्ण

पूर्णांक reset_qsfp(काष्ठा hfi1_pportdata *ppd)
अणु
	काष्ठा hfi1_devdata *dd = ppd->dd;
	u64 mask, qsfp_mask;

	/* Disable INT_N from triggering QSFP पूर्णांकerrupts */
	set_qsfp_पूर्णांक_n(ppd, 0);

	/* Reset the QSFP */
	mask = (u64)QSFP_HFI0_RESET_N;

	qsfp_mask = पढ़ो_csr(dd,
			     dd->hfi1_id ? ASIC_QSFP2_OUT : ASIC_QSFP1_OUT);
	qsfp_mask &= ~mask;
	ग_लिखो_csr(dd,
		  dd->hfi1_id ? ASIC_QSFP2_OUT : ASIC_QSFP1_OUT, qsfp_mask);

	udelay(10);

	qsfp_mask |= mask;
	ग_लिखो_csr(dd,
		  dd->hfi1_id ? ASIC_QSFP2_OUT : ASIC_QSFP1_OUT, qsfp_mask);

	रुको_क्रम_qsfp_init(ppd);

	/*
	 * Allow INT_N to trigger the QSFP पूर्णांकerrupt to watch
	 * क्रम alarms and warnings
	 */
	set_qsfp_पूर्णांक_n(ppd, 1);

	/*
	 * After the reset, AOC transmitters are enabled by शेष. They need
	 * to be turned off to complete the QSFP setup beक्रमe they can be
	 * enabled again.
	 */
	वापस set_qsfp_tx(ppd, 0);
पूर्ण

अटल पूर्णांक handle_qsfp_error_conditions(काष्ठा hfi1_pportdata *ppd,
					u8 *qsfp_पूर्णांकerrupt_status)
अणु
	काष्ठा hfi1_devdata *dd = ppd->dd;

	अगर ((qsfp_पूर्णांकerrupt_status[0] & QSFP_HIGH_TEMP_ALARM) ||
	    (qsfp_पूर्णांकerrupt_status[0] & QSFP_HIGH_TEMP_WARNING))
		dd_dev_err(dd, "%s: QSFP cable temperature too high\n",
			   __func__);

	अगर ((qsfp_पूर्णांकerrupt_status[0] & QSFP_LOW_TEMP_ALARM) ||
	    (qsfp_पूर्णांकerrupt_status[0] & QSFP_LOW_TEMP_WARNING))
		dd_dev_err(dd, "%s: QSFP cable temperature too low\n",
			   __func__);

	/*
	 * The reमुख्यing alarms/warnings करोn't matter अगर the link is करोwn.
	 */
	अगर (ppd->host_link_state & HLS_DOWN)
		वापस 0;

	अगर ((qsfp_पूर्णांकerrupt_status[1] & QSFP_HIGH_VCC_ALARM) ||
	    (qsfp_पूर्णांकerrupt_status[1] & QSFP_HIGH_VCC_WARNING))
		dd_dev_err(dd, "%s: QSFP supply voltage too high\n",
			   __func__);

	अगर ((qsfp_पूर्णांकerrupt_status[1] & QSFP_LOW_VCC_ALARM) ||
	    (qsfp_पूर्णांकerrupt_status[1] & QSFP_LOW_VCC_WARNING))
		dd_dev_err(dd, "%s: QSFP supply voltage too low\n",
			   __func__);

	/* Byte 2 is venकरोr specअगरic */

	अगर ((qsfp_पूर्णांकerrupt_status[3] & QSFP_HIGH_POWER_ALARM) ||
	    (qsfp_पूर्णांकerrupt_status[3] & QSFP_HIGH_POWER_WARNING))
		dd_dev_err(dd, "%s: Cable RX channel 1/2 power too high\n",
			   __func__);

	अगर ((qsfp_पूर्णांकerrupt_status[3] & QSFP_LOW_POWER_ALARM) ||
	    (qsfp_पूर्णांकerrupt_status[3] & QSFP_LOW_POWER_WARNING))
		dd_dev_err(dd, "%s: Cable RX channel 1/2 power too low\n",
			   __func__);

	अगर ((qsfp_पूर्णांकerrupt_status[4] & QSFP_HIGH_POWER_ALARM) ||
	    (qsfp_पूर्णांकerrupt_status[4] & QSFP_HIGH_POWER_WARNING))
		dd_dev_err(dd, "%s: Cable RX channel 3/4 power too high\n",
			   __func__);

	अगर ((qsfp_पूर्णांकerrupt_status[4] & QSFP_LOW_POWER_ALARM) ||
	    (qsfp_पूर्णांकerrupt_status[4] & QSFP_LOW_POWER_WARNING))
		dd_dev_err(dd, "%s: Cable RX channel 3/4 power too low\n",
			   __func__);

	अगर ((qsfp_पूर्णांकerrupt_status[5] & QSFP_HIGH_BIAS_ALARM) ||
	    (qsfp_पूर्णांकerrupt_status[5] & QSFP_HIGH_BIAS_WARNING))
		dd_dev_err(dd, "%s: Cable TX channel 1/2 bias too high\n",
			   __func__);

	अगर ((qsfp_पूर्णांकerrupt_status[5] & QSFP_LOW_BIAS_ALARM) ||
	    (qsfp_पूर्णांकerrupt_status[5] & QSFP_LOW_BIAS_WARNING))
		dd_dev_err(dd, "%s: Cable TX channel 1/2 bias too low\n",
			   __func__);

	अगर ((qsfp_पूर्णांकerrupt_status[6] & QSFP_HIGH_BIAS_ALARM) ||
	    (qsfp_पूर्णांकerrupt_status[6] & QSFP_HIGH_BIAS_WARNING))
		dd_dev_err(dd, "%s: Cable TX channel 3/4 bias too high\n",
			   __func__);

	अगर ((qsfp_पूर्णांकerrupt_status[6] & QSFP_LOW_BIAS_ALARM) ||
	    (qsfp_पूर्णांकerrupt_status[6] & QSFP_LOW_BIAS_WARNING))
		dd_dev_err(dd, "%s: Cable TX channel 3/4 bias too low\n",
			   __func__);

	अगर ((qsfp_पूर्णांकerrupt_status[7] & QSFP_HIGH_POWER_ALARM) ||
	    (qsfp_पूर्णांकerrupt_status[7] & QSFP_HIGH_POWER_WARNING))
		dd_dev_err(dd, "%s: Cable TX channel 1/2 power too high\n",
			   __func__);

	अगर ((qsfp_पूर्णांकerrupt_status[7] & QSFP_LOW_POWER_ALARM) ||
	    (qsfp_पूर्णांकerrupt_status[7] & QSFP_LOW_POWER_WARNING))
		dd_dev_err(dd, "%s: Cable TX channel 1/2 power too low\n",
			   __func__);

	अगर ((qsfp_पूर्णांकerrupt_status[8] & QSFP_HIGH_POWER_ALARM) ||
	    (qsfp_पूर्णांकerrupt_status[8] & QSFP_HIGH_POWER_WARNING))
		dd_dev_err(dd, "%s: Cable TX channel 3/4 power too high\n",
			   __func__);

	अगर ((qsfp_पूर्णांकerrupt_status[8] & QSFP_LOW_POWER_ALARM) ||
	    (qsfp_पूर्णांकerrupt_status[8] & QSFP_LOW_POWER_WARNING))
		dd_dev_err(dd, "%s: Cable TX channel 3/4 power too low\n",
			   __func__);

	/* Bytes 9-10 and 11-12 are reserved */
	/* Bytes 13-15 are venकरोr specअगरic */

	वापस 0;
पूर्ण

/* This routine will only be scheduled अगर the QSFP module present is निश्चितed */
व्योम qsfp_event(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qsfp_data *qd;
	काष्ठा hfi1_pportdata *ppd;
	काष्ठा hfi1_devdata *dd;

	qd = container_of(work, काष्ठा qsfp_data, qsfp_work);
	ppd = qd->ppd;
	dd = ppd->dd;

	/* Sanity check */
	अगर (!qsfp_mod_present(ppd))
		वापस;

	अगर (ppd->host_link_state == HLS_DN_DISABLE) अणु
		dd_dev_info(ppd->dd,
			    "%s: stopping link start because link is disabled\n",
			    __func__);
		वापस;
	पूर्ण

	/*
	 * Turn DC back on after cable has been re-inserted. Up until
	 * now, the DC has been in reset to save घातer.
	 */
	dc_start(dd);

	अगर (qd->cache_refresh_required) अणु
		set_qsfp_पूर्णांक_n(ppd, 0);

		रुको_क्रम_qsfp_init(ppd);

		/*
		 * Allow INT_N to trigger the QSFP पूर्णांकerrupt to watch
		 * क्रम alarms and warnings
		 */
		set_qsfp_पूर्णांक_n(ppd, 1);

		start_link(ppd);
	पूर्ण

	अगर (qd->check_पूर्णांकerrupt_flags) अणु
		u8 qsfp_पूर्णांकerrupt_status[16] = अणु0,पूर्ण;

		अगर (one_qsfp_पढ़ो(ppd, dd->hfi1_id, 6,
				  &qsfp_पूर्णांकerrupt_status[0], 16) != 16) अणु
			dd_dev_info(dd,
				    "%s: Failed to read status of QSFP module\n",
				    __func__);
		पूर्ण अन्यथा अणु
			अचिन्हित दीर्घ flags;

			handle_qsfp_error_conditions(
					ppd, qsfp_पूर्णांकerrupt_status);
			spin_lock_irqsave(&ppd->qsfp_info.qsfp_lock, flags);
			ppd->qsfp_info.check_पूर्णांकerrupt_flags = 0;
			spin_unlock_irqrestore(&ppd->qsfp_info.qsfp_lock,
					       flags);
		पूर्ण
	पूर्ण
पूर्ण

व्योम init_qsfp_पूर्णांक(काष्ठा hfi1_devdata *dd)
अणु
	काष्ठा hfi1_pportdata *ppd = dd->pport;
	u64 qsfp_mask;

	qsfp_mask = (u64)(QSFP_HFI0_INT_N | QSFP_HFI0_MODPRST_N);
	/* Clear current status to aव्योम spurious पूर्णांकerrupts */
	ग_लिखो_csr(dd, dd->hfi1_id ? ASIC_QSFP2_CLEAR : ASIC_QSFP1_CLEAR,
		  qsfp_mask);
	ग_लिखो_csr(dd, dd->hfi1_id ? ASIC_QSFP2_MASK : ASIC_QSFP1_MASK,
		  qsfp_mask);

	set_qsfp_पूर्णांक_n(ppd, 0);

	/* Handle active low nature of INT_N and MODPRST_N pins */
	अगर (qsfp_mod_present(ppd))
		qsfp_mask &= ~(u64)QSFP_HFI0_MODPRST_N;
	ग_लिखो_csr(dd,
		  dd->hfi1_id ? ASIC_QSFP2_INVERT : ASIC_QSFP1_INVERT,
		  qsfp_mask);

	/* Enable the appropriate QSFP IRQ source */
	अगर (!dd->hfi1_id)
		set_पूर्णांकr_bits(dd, QSFP1_INT, QSFP1_INT, true);
	अन्यथा
		set_पूर्णांकr_bits(dd, QSFP2_INT, QSFP2_INT, true);
पूर्ण

/*
 * Do a one-समय initialize of the LCB block.
 */
अटल व्योम init_lcb(काष्ठा hfi1_devdata *dd)
अणु
	/* simulator करोes not correctly handle LCB cclk loopback, skip */
	अगर (dd->icode == ICODE_FUNCTIONAL_SIMULATOR)
		वापस;

	/* the DC has been reset earlier in the driver load */

	/* set LCB क्रम cclk loopback on the port */
	ग_लिखो_csr(dd, DC_LCB_CFG_TX_FIFOS_RESET, 0x01);
	ग_लिखो_csr(dd, DC_LCB_CFG_LANE_WIDTH, 0x00);
	ग_लिखो_csr(dd, DC_LCB_CFG_REINIT_AS_SLAVE, 0x00);
	ग_लिखो_csr(dd, DC_LCB_CFG_CNT_FOR_SKIP_STALL, 0x110);
	ग_लिखो_csr(dd, DC_LCB_CFG_CLK_CNTR, 0x08);
	ग_लिखो_csr(dd, DC_LCB_CFG_LOOPBACK, 0x02);
	ग_लिखो_csr(dd, DC_LCB_CFG_TX_FIFOS_RESET, 0x00);
पूर्ण

/*
 * Perक्रमm a test पढ़ो on the QSFP.  Return 0 on success, -ERRNO
 * on error.
 */
अटल पूर्णांक test_qsfp_पढ़ो(काष्ठा hfi1_pportdata *ppd)
अणु
	पूर्णांक ret;
	u8 status;

	/*
	 * Report success अगर not a QSFP or, अगर it is a QSFP, but the cable is
	 * not present
	 */
	अगर (ppd->port_type != PORT_TYPE_QSFP || !qsfp_mod_present(ppd))
		वापस 0;

	/* पढ़ो byte 2, the status byte */
	ret = one_qsfp_पढ़ो(ppd, ppd->dd->hfi1_id, 2, &status, 1);
	अगर (ret < 0)
		वापस ret;
	अगर (ret != 1)
		वापस -EIO;

	वापस 0; /* success */
पूर्ण

/*
 * Values क्रम QSFP retry.
 *
 * Give up after 10s (20 x 500ms).  The overall समयout was empirically
 * arrived at from experience on a large cluster.
 */
#घोषणा MAX_QSFP_RETRIES 20
#घोषणा QSFP_RETRY_WAIT 500 /* msec */

/*
 * Try a QSFP पढ़ो.  If it fails, schedule a retry क्रम later.
 * Called on first link activation after driver load.
 */
अटल व्योम try_start_link(काष्ठा hfi1_pportdata *ppd)
अणु
	अगर (test_qsfp_पढ़ो(ppd)) अणु
		/* पढ़ो failed */
		अगर (ppd->qsfp_retry_count >= MAX_QSFP_RETRIES) अणु
			dd_dev_err(ppd->dd, "QSFP not responding, giving up\n");
			वापस;
		पूर्ण
		dd_dev_info(ppd->dd,
			    "QSFP not responding, waiting and retrying %d\n",
			    (पूर्णांक)ppd->qsfp_retry_count);
		ppd->qsfp_retry_count++;
		queue_delayed_work(ppd->link_wq, &ppd->start_link_work,
				   msecs_to_jअगरfies(QSFP_RETRY_WAIT));
		वापस;
	पूर्ण
	ppd->qsfp_retry_count = 0;

	start_link(ppd);
पूर्ण

/*
 * Workqueue function to start the link after a delay.
 */
व्योम handle_start_link(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hfi1_pportdata *ppd = container_of(work, काष्ठा hfi1_pportdata,
						  start_link_work.work);
	try_start_link(ppd);
पूर्ण

पूर्णांक bringup_serdes(काष्ठा hfi1_pportdata *ppd)
अणु
	काष्ठा hfi1_devdata *dd = ppd->dd;
	u64 guid;
	पूर्णांक ret;

	अगर (HFI1_CAP_IS_KSET(EXTENDED_PSN))
		add_rcvctrl(dd, RCV_CTRL_RCV_EXTENDED_PSN_ENABLE_SMASK);

	guid = ppd->guids[HFI1_PORT_GUID_INDEX];
	अगर (!guid) अणु
		अगर (dd->base_guid)
			guid = dd->base_guid + ppd->port - 1;
		ppd->guids[HFI1_PORT_GUID_INDEX] = guid;
	पूर्ण

	/* Set linkinit_reason on घातer up per OPA spec */
	ppd->linkinit_reason = OPA_LINKINIT_REASON_LINKUP;

	/* one-समय init of the LCB */
	init_lcb(dd);

	अगर (loopback) अणु
		ret = init_loopback(dd);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	get_port_type(ppd);
	अगर (ppd->port_type == PORT_TYPE_QSFP) अणु
		set_qsfp_पूर्णांक_n(ppd, 0);
		रुको_क्रम_qsfp_init(ppd);
		set_qsfp_पूर्णांक_n(ppd, 1);
	पूर्ण

	try_start_link(ppd);
	वापस 0;
पूर्ण

व्योम hfi1_quiet_serdes(काष्ठा hfi1_pportdata *ppd)
अणु
	काष्ठा hfi1_devdata *dd = ppd->dd;

	/*
	 * Shut करोwn the link and keep it करोwn.   First turn off that the
	 * driver wants to allow the link to be up (driver_link_पढ़ोy).
	 * Then make sure the link is not स्वतःmatically restarted
	 * (link_enabled).  Cancel any pending restart.  And finally
	 * go offline.
	 */
	ppd->driver_link_पढ़ोy = 0;
	ppd->link_enabled = 0;

	ppd->qsfp_retry_count = MAX_QSFP_RETRIES; /* prevent more retries */
	flush_delayed_work(&ppd->start_link_work);
	cancel_delayed_work_sync(&ppd->start_link_work);

	ppd->offline_disabled_reason =
			HFI1_ODR_MASK(OPA_LINKDOWN_REASON_REBOOT);
	set_link_करोwn_reason(ppd, OPA_LINKDOWN_REASON_REBOOT, 0,
			     OPA_LINKDOWN_REASON_REBOOT);
	set_link_state(ppd, HLS_DN_OFFLINE);

	/* disable the port */
	clear_rcvctrl(dd, RCV_CTRL_RCV_PORT_ENABLE_SMASK);
	cancel_work_sync(&ppd->मुक्तze_work);
पूर्ण

अटल अंतरभूत पूर्णांक init_cpu_counters(काष्ठा hfi1_devdata *dd)
अणु
	काष्ठा hfi1_pportdata *ppd;
	पूर्णांक i;

	ppd = (काष्ठा hfi1_pportdata *)(dd + 1);
	क्रम (i = 0; i < dd->num_pports; i++, ppd++) अणु
		ppd->ibport_data.rvp.rc_acks = शून्य;
		ppd->ibport_data.rvp.rc_qacks = शून्य;
		ppd->ibport_data.rvp.rc_acks = alloc_percpu(u64);
		ppd->ibport_data.rvp.rc_qacks = alloc_percpu(u64);
		ppd->ibport_data.rvp.rc_delayed_comp = alloc_percpu(u64);
		अगर (!ppd->ibport_data.rvp.rc_acks ||
		    !ppd->ibport_data.rvp.rc_delayed_comp ||
		    !ppd->ibport_data.rvp.rc_qacks)
			वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * index is the index पूर्णांकo the receive array
 */
व्योम hfi1_put_tid(काष्ठा hfi1_devdata *dd, u32 index,
		  u32 type, अचिन्हित दीर्घ pa, u16 order)
अणु
	u64 reg;

	अगर (!(dd->flags & HFI1_PRESENT))
		जाओ करोne;

	अगर (type == PT_INVALID || type == PT_INVALID_FLUSH) अणु
		pa = 0;
		order = 0;
	पूर्ण अन्यथा अगर (type > PT_INVALID) अणु
		dd_dev_err(dd,
			   "unexpected receive array type %u for index %u, not handled\n",
			   type, index);
		जाओ करोne;
	पूर्ण
	trace_hfi1_put_tid(dd, index, type, pa, order);

#घोषणा RT_ADDR_SHIFT 12	/* 4KB kernel address boundary */
	reg = RCV_ARRAY_RT_WRITE_ENABLE_SMASK
		| (u64)order << RCV_ARRAY_RT_BUF_SIZE_SHIFT
		| ((pa >> RT_ADDR_SHIFT) & RCV_ARRAY_RT_ADDR_MASK)
					<< RCV_ARRAY_RT_ADDR_SHIFT;
	trace_hfi1_ग_लिखो_rcvarray(dd->rcvarray_wc + (index * 8), reg);
	ग_लिखोq(reg, dd->rcvarray_wc + (index * 8));

	अगर (type == PT_EAGER || type == PT_INVALID_FLUSH || (index & 3) == 3)
		/*
		 * Eager entries are written and flushed
		 *
		 * Expected entries are flushed every 4 ग_लिखोs
		 */
		flush_wc();
करोne:
	वापस;
पूर्ण

व्योम hfi1_clear_tids(काष्ठा hfi1_ctxtdata *rcd)
अणु
	काष्ठा hfi1_devdata *dd = rcd->dd;
	u32 i;

	/* this could be optimized */
	क्रम (i = rcd->eager_base; i < rcd->eager_base +
		     rcd->egrbufs.alloced; i++)
		hfi1_put_tid(dd, i, PT_INVALID, 0, 0);

	क्रम (i = rcd->expected_base;
			i < rcd->expected_base + rcd->expected_count; i++)
		hfi1_put_tid(dd, i, PT_INVALID, 0, 0);
पूर्ण

अटल स्थिर अक्षर * स्थिर ib_cfg_name_strings[] = अणु
	"HFI1_IB_CFG_LIDLMC",
	"HFI1_IB_CFG_LWID_DG_ENB",
	"HFI1_IB_CFG_LWID_ENB",
	"HFI1_IB_CFG_LWID",
	"HFI1_IB_CFG_SPD_ENB",
	"HFI1_IB_CFG_SPD",
	"HFI1_IB_CFG_RXPOL_ENB",
	"HFI1_IB_CFG_LREV_ENB",
	"HFI1_IB_CFG_LINKLATENCY",
	"HFI1_IB_CFG_HRTBT",
	"HFI1_IB_CFG_OP_VLS",
	"HFI1_IB_CFG_VL_HIGH_CAP",
	"HFI1_IB_CFG_VL_LOW_CAP",
	"HFI1_IB_CFG_OVERRUN_THRESH",
	"HFI1_IB_CFG_PHYERR_THRESH",
	"HFI1_IB_CFG_LINKDEFAULT",
	"HFI1_IB_CFG_PKEYS",
	"HFI1_IB_CFG_MTU",
	"HFI1_IB_CFG_LSTATE",
	"HFI1_IB_CFG_VL_HIGH_LIMIT",
	"HFI1_IB_CFG_PMA_TICKS",
	"HFI1_IB_CFG_PORT"
पूर्ण;

अटल स्थिर अक्षर *ib_cfg_name(पूर्णांक which)
अणु
	अगर (which < 0 || which >= ARRAY_SIZE(ib_cfg_name_strings))
		वापस "invalid";
	वापस ib_cfg_name_strings[which];
पूर्ण

पूर्णांक hfi1_get_ib_cfg(काष्ठा hfi1_pportdata *ppd, पूर्णांक which)
अणु
	काष्ठा hfi1_devdata *dd = ppd->dd;
	पूर्णांक val = 0;

	चयन (which) अणु
	हाल HFI1_IB_CFG_LWID_ENB: /* allowed Link-width */
		val = ppd->link_width_enabled;
		अवरोध;
	हाल HFI1_IB_CFG_LWID: /* currently active Link-width */
		val = ppd->link_width_active;
		अवरोध;
	हाल HFI1_IB_CFG_SPD_ENB: /* allowed Link speeds */
		val = ppd->link_speed_enabled;
		अवरोध;
	हाल HFI1_IB_CFG_SPD: /* current Link speed */
		val = ppd->link_speed_active;
		अवरोध;

	हाल HFI1_IB_CFG_RXPOL_ENB: /* Auto-RX-polarity enable */
	हाल HFI1_IB_CFG_LREV_ENB: /* Auto-Lane-reversal enable */
	हाल HFI1_IB_CFG_LINKLATENCY:
		जाओ unimplemented;

	हाल HFI1_IB_CFG_OP_VLS:
		val = ppd->actual_vls_operational;
		अवरोध;
	हाल HFI1_IB_CFG_VL_HIGH_CAP: /* VL arb high priority table size */
		val = VL_ARB_HIGH_PRIO_TABLE_SIZE;
		अवरोध;
	हाल HFI1_IB_CFG_VL_LOW_CAP: /* VL arb low priority table size */
		val = VL_ARB_LOW_PRIO_TABLE_SIZE;
		अवरोध;
	हाल HFI1_IB_CFG_OVERRUN_THRESH: /* IB overrun threshold */
		val = ppd->overrun_threshold;
		अवरोध;
	हाल HFI1_IB_CFG_PHYERR_THRESH: /* IB PHY error threshold */
		val = ppd->phy_error_threshold;
		अवरोध;
	हाल HFI1_IB_CFG_LINKDEFAULT: /* IB link शेष (sleep/poll) */
		val = HLS_DEFAULT;
		अवरोध;

	हाल HFI1_IB_CFG_HRTBT: /* Heartbeat off/enable/स्वतः */
	हाल HFI1_IB_CFG_PMA_TICKS:
	शेष:
unimplemented:
		अगर (HFI1_CAP_IS_KSET(PRINT_UNIMPL))
			dd_dev_info(
				dd,
				"%s: which %s: not implemented\n",
				__func__,
				ib_cfg_name(which));
		अवरोध;
	पूर्ण

	वापस val;
पूर्ण

/*
 * The largest MAD packet size.
 */
#घोषणा MAX_MAD_PACKET 2048

/*
 * Return the maximum header bytes that can go on the _wire_
 * क्रम this device. This count includes the ICRC which is
 * not part of the packet held in memory but it is appended
 * by the HW.
 * This is dependent on the device's receive header entry size.
 * HFI allows this to be set per-receive context, but the
 * driver presently enक्रमces a global value.
 */
u32 lrh_max_header_bytes(काष्ठा hfi1_devdata *dd)
अणु
	/*
	 * The maximum non-payload (MTU) bytes in LRH.PktLen are
	 * the Receive Header Entry Size minus the PBC (or RHF) size
	 * plus one DW क्रम the ICRC appended by HW.
	 *
	 * dd->rcd[0].rcvhdrqentsize is in DW.
	 * We use rcd[0] as all context will have the same value. Also,
	 * the first kernel context would have been allocated by now so
	 * we are guaranteed a valid value.
	 */
	वापस (get_hdrqentsize(dd->rcd[0]) - 2/*PBC/RHF*/ + 1/*ICRC*/) << 2;
पूर्ण

/*
 * Set Send Length
 * @ppd: per port data
 *
 * Set the MTU by limiting how many DWs may be sent.  The SendLenCheck*
 * रेजिस्टरs compare against LRH.PktLen, so use the max bytes included
 * in the LRH.
 *
 * This routine changes all VL values except VL15, which it मुख्यtains at
 * the same value.
 */
अटल व्योम set_send_length(काष्ठा hfi1_pportdata *ppd)
अणु
	काष्ठा hfi1_devdata *dd = ppd->dd;
	u32 max_hb = lrh_max_header_bytes(dd), dcmtu;
	u32 maxvlmtu = dd->vld[15].mtu;
	u64 len1 = 0, len2 = (((dd->vld[15].mtu + max_hb) >> 2)
			      & SEND_LEN_CHECK1_LEN_VL15_MASK) <<
		SEND_LEN_CHECK1_LEN_VL15_SHIFT;
	पूर्णांक i, j;
	u32 thres;

	क्रम (i = 0; i < ppd->vls_supported; i++) अणु
		अगर (dd->vld[i].mtu > maxvlmtu)
			maxvlmtu = dd->vld[i].mtu;
		अगर (i <= 3)
			len1 |= (((dd->vld[i].mtu + max_hb) >> 2)
				 & SEND_LEN_CHECK0_LEN_VL0_MASK) <<
				((i % 4) * SEND_LEN_CHECK0_LEN_VL1_SHIFT);
		अन्यथा
			len2 |= (((dd->vld[i].mtu + max_hb) >> 2)
				 & SEND_LEN_CHECK1_LEN_VL4_MASK) <<
				((i % 4) * SEND_LEN_CHECK1_LEN_VL5_SHIFT);
	पूर्ण
	ग_लिखो_csr(dd, SEND_LEN_CHECK0, len1);
	ग_लिखो_csr(dd, SEND_LEN_CHECK1, len2);
	/* adjust kernel credit वापस thresholds based on new MTUs */
	/* all kernel receive contexts have the same hdrqentsize */
	क्रम (i = 0; i < ppd->vls_supported; i++) अणु
		thres = min(sc_percent_to_threshold(dd->vld[i].sc, 50),
			    sc_mtu_to_threshold(dd->vld[i].sc,
						dd->vld[i].mtu,
						get_hdrqentsize(dd->rcd[0])));
		क्रम (j = 0; j < INIT_SC_PER_VL; j++)
			sc_set_cr_threshold(
					pio_select_send_context_vl(dd, j, i),
					    thres);
	पूर्ण
	thres = min(sc_percent_to_threshold(dd->vld[15].sc, 50),
		    sc_mtu_to_threshold(dd->vld[15].sc,
					dd->vld[15].mtu,
					dd->rcd[0]->rcvhdrqentsize));
	sc_set_cr_threshold(dd->vld[15].sc, thres);

	/* Adjust maximum MTU क्रम the port in DC */
	dcmtu = maxvlmtu == 10240 ? DCC_CFG_PORT_MTU_CAP_10240 :
		(ilog2(maxvlmtu >> 8) + 1);
	len1 = पढ़ो_csr(ppd->dd, DCC_CFG_PORT_CONFIG);
	len1 &= ~DCC_CFG_PORT_CONFIG_MTU_CAP_SMASK;
	len1 |= ((u64)dcmtu & DCC_CFG_PORT_CONFIG_MTU_CAP_MASK) <<
		DCC_CFG_PORT_CONFIG_MTU_CAP_SHIFT;
	ग_लिखो_csr(ppd->dd, DCC_CFG_PORT_CONFIG, len1);
पूर्ण

अटल व्योम set_lidlmc(काष्ठा hfi1_pportdata *ppd)
अणु
	पूर्णांक i;
	u64 sreg = 0;
	काष्ठा hfi1_devdata *dd = ppd->dd;
	u32 mask = ~((1U << ppd->lmc) - 1);
	u64 c1 = पढ़ो_csr(ppd->dd, DCC_CFG_PORT_CONFIG1);
	u32 lid;

	/*
	 * Program 0 in CSR अगर port lid is extended. This prevents
	 * 9B packets being sent out क्रम large lids.
	 */
	lid = (ppd->lid >= be16_to_cpu(IB_MULTICAST_LID_BASE)) ? 0 : ppd->lid;
	c1 &= ~(DCC_CFG_PORT_CONFIG1_TARGET_DLID_SMASK
		| DCC_CFG_PORT_CONFIG1_DLID_MASK_SMASK);
	c1 |= ((lid & DCC_CFG_PORT_CONFIG1_TARGET_DLID_MASK)
			<< DCC_CFG_PORT_CONFIG1_TARGET_DLID_SHIFT) |
	      ((mask & DCC_CFG_PORT_CONFIG1_DLID_MASK_MASK)
			<< DCC_CFG_PORT_CONFIG1_DLID_MASK_SHIFT);
	ग_लिखो_csr(ppd->dd, DCC_CFG_PORT_CONFIG1, c1);

	/*
	 * Iterate over all the send contexts and set their SLID check
	 */
	sreg = ((mask & SEND_CTXT_CHECK_SLID_MASK_MASK) <<
			SEND_CTXT_CHECK_SLID_MASK_SHIFT) |
	       (((lid & mask) & SEND_CTXT_CHECK_SLID_VALUE_MASK) <<
			SEND_CTXT_CHECK_SLID_VALUE_SHIFT);

	क्रम (i = 0; i < chip_send_contexts(dd); i++) अणु
		hfi1_cdbg(LINKVERB, "SendContext[%d].SLID_CHECK = 0x%x",
			  i, (u32)sreg);
		ग_लिखो_kctxt_csr(dd, i, SEND_CTXT_CHECK_SLID, sreg);
	पूर्ण

	/* Now we have to करो the same thing क्रम the sdma engines */
	sdma_update_lmc(dd, mask, lid);
पूर्ण

अटल स्थिर अक्षर *state_completed_string(u32 completed)
अणु
	अटल स्थिर अक्षर * स्थिर state_completed[] = अणु
		"EstablishComm",
		"OptimizeEQ",
		"VerifyCap"
	पूर्ण;

	अगर (completed < ARRAY_SIZE(state_completed))
		वापस state_completed[completed];

	वापस "unknown";
पूर्ण

अटल स्थिर अक्षर all_lanes_dead_समयout_expired[] =
	"All lanes were inactive ै  was the interconnect media removed?";
अटल स्थिर अक्षर tx_out_of_policy[] =
	"Passing lanes on local port do not meet the local link width policy";
अटल स्थिर अक्षर no_state_complete[] =
	"State timeout occurred before link partner completed the state";
अटल स्थिर अक्षर * स्थिर state_complete_reasons[] = अणु
	[0x00] = "Reason unknown",
	[0x01] = "Link was halted by driver, refer to LinkDownReason",
	[0x02] = "Link partner reported failure",
	[0x10] = "Unable to achieve frame sync on any lane",
	[0x11] =
	  "Unable to find a common bit rate with the link partner",
	[0x12] =
	  "Unable to achieve frame sync on sufficient lanes to meet the local link width policy",
	[0x13] =
	  "Unable to identify preset equalization on sufficient lanes to meet the local link width policy",
	[0x14] = no_state_complete,
	[0x15] =
	  "State timeout occurred before link partner identified equalization presets",
	[0x16] =
	  "Link partner completed the EstablishComm state, but the passing lanes do not meet the local link width policy",
	[0x17] = tx_out_of_policy,
	[0x20] = all_lanes_dead_समयout_expired,
	[0x21] =
	  "Unable to achieve acceptable BER on sufficient lanes to meet the local link width policy",
	[0x22] = no_state_complete,
	[0x23] =
	  "Link partner completed the OptimizeEq state, but the passing lanes do not meet the local link width policy",
	[0x24] = tx_out_of_policy,
	[0x30] = all_lanes_dead_समयout_expired,
	[0x31] =
	  "State timeout occurred waiting for host to process received frames",
	[0x32] = no_state_complete,
	[0x33] =
	  "Link partner completed the VerifyCap state, but the passing lanes do not meet the local link width policy",
	[0x34] = tx_out_of_policy,
	[0x35] = "Negotiated link width is mutually exclusive",
	[0x36] =
	  "Timed out before receiving verifycap frames in VerifyCap.Exchange",
	[0x37] = "Unable to resolve secure data exchange",
पूर्ण;

अटल स्थिर अक्षर *state_complete_reason_code_string(काष्ठा hfi1_pportdata *ppd,
						     u32 code)
अणु
	स्थिर अक्षर *str = शून्य;

	अगर (code < ARRAY_SIZE(state_complete_reasons))
		str = state_complete_reasons[code];

	अगर (str)
		वापस str;
	वापस "Reserved";
पूर्ण

/* describe the given last state complete frame */
अटल व्योम decode_state_complete(काष्ठा hfi1_pportdata *ppd, u32 frame,
				  स्थिर अक्षर *prefix)
अणु
	काष्ठा hfi1_devdata *dd = ppd->dd;
	u32 success;
	u32 state;
	u32 reason;
	u32 lanes;

	/*
	 * Decode frame:
	 *  [ 0: 0] - success
	 *  [ 3: 1] - state
	 *  [ 7: 4] - next state समयout
	 *  [15: 8] - reason code
	 *  [31:16] - lanes
	 */
	success = frame & 0x1;
	state = (frame >> 1) & 0x7;
	reason = (frame >> 8) & 0xff;
	lanes = (frame >> 16) & 0xffff;

	dd_dev_err(dd, "Last %s LNI state complete frame 0x%08x:\n",
		   prefix, frame);
	dd_dev_err(dd, "    last reported state state: %s (0x%x)\n",
		   state_completed_string(state), state);
	dd_dev_err(dd, "    state successfully completed: %s\n",
		   success ? "yes" : "no");
	dd_dev_err(dd, "    fail reason 0x%x: %s\n",
		   reason, state_complete_reason_code_string(ppd, reason));
	dd_dev_err(dd, "    passing lane mask: 0x%x", lanes);
पूर्ण

/*
 * Read the last state complete frames and explain them.  This routine
 * expects to be called अगर the link went करोwn during link negotiation
 * and initialization (LNI).  That is, anywhere between polling and link up.
 */
अटल व्योम check_lni_states(काष्ठा hfi1_pportdata *ppd)
अणु
	u32 last_local_state;
	u32 last_remote_state;

	पढ़ो_last_local_state(ppd->dd, &last_local_state);
	पढ़ो_last_remote_state(ppd->dd, &last_remote_state);

	/*
	 * Don't report anything अगर there is nothing to report.  A value of
	 * 0 means the link was taken करोwn जबतक polling and there was no
	 * training in-process.
	 */
	अगर (last_local_state == 0 && last_remote_state == 0)
		वापस;

	decode_state_complete(ppd, last_local_state, "transmitted");
	decode_state_complete(ppd, last_remote_state, "received");
पूर्ण

/* रुको क्रम रुको_ms क्रम LINK_TRANSFER_ACTIVE to go to 1 */
अटल पूर्णांक रुको_link_transfer_active(काष्ठा hfi1_devdata *dd, पूर्णांक रुको_ms)
अणु
	u64 reg;
	अचिन्हित दीर्घ समयout;

	/* watch LCB_STS_LINK_TRANSFER_ACTIVE */
	समयout = jअगरfies + msecs_to_jअगरfies(रुको_ms);
	जबतक (1) अणु
		reg = पढ़ो_csr(dd, DC_LCB_STS_LINK_TRANSFER_ACTIVE);
		अगर (reg)
			अवरोध;
		अगर (समय_after(jअगरfies, समयout)) अणु
			dd_dev_err(dd,
				   "timeout waiting for LINK_TRANSFER_ACTIVE\n");
			वापस -ETIMEDOUT;
		पूर्ण
		udelay(2);
	पूर्ण
	वापस 0;
पूर्ण

/* called when the logical link state is not करोwn as it should be */
अटल व्योम क्रमce_logical_link_state_करोwn(काष्ठा hfi1_pportdata *ppd)
अणु
	काष्ठा hfi1_devdata *dd = ppd->dd;

	/*
	 * Bring link up in LCB loopback
	 */
	ग_लिखो_csr(dd, DC_LCB_CFG_TX_FIFOS_RESET, 1);
	ग_लिखो_csr(dd, DC_LCB_CFG_IGNORE_LOST_RCLK,
		  DC_LCB_CFG_IGNORE_LOST_RCLK_EN_SMASK);

	ग_लिखो_csr(dd, DC_LCB_CFG_LANE_WIDTH, 0);
	ग_लिखो_csr(dd, DC_LCB_CFG_REINIT_AS_SLAVE, 0);
	ग_लिखो_csr(dd, DC_LCB_CFG_CNT_FOR_SKIP_STALL, 0x110);
	ग_लिखो_csr(dd, DC_LCB_CFG_LOOPBACK, 0x2);

	ग_लिखो_csr(dd, DC_LCB_CFG_TX_FIFOS_RESET, 0);
	(व्योम)पढ़ो_csr(dd, DC_LCB_CFG_TX_FIFOS_RESET);
	udelay(3);
	ग_लिखो_csr(dd, DC_LCB_CFG_ALLOW_LINK_UP, 1);
	ग_लिखो_csr(dd, DC_LCB_CFG_RUN, 1ull << DC_LCB_CFG_RUN_EN_SHIFT);

	रुको_link_transfer_active(dd, 100);

	/*
	 * Bring the link करोwn again.
	 */
	ग_लिखो_csr(dd, DC_LCB_CFG_TX_FIFOS_RESET, 1);
	ग_लिखो_csr(dd, DC_LCB_CFG_ALLOW_LINK_UP, 0);
	ग_लिखो_csr(dd, DC_LCB_CFG_IGNORE_LOST_RCLK, 0);

	dd_dev_info(ppd->dd, "logical state forced to LINK_DOWN\n");
पूर्ण

/*
 * Helper क्रम set_link_state().  Do not call except from that routine.
 * Expects ppd->hls_mutex to be held.
 *
 * @rem_reason value to be sent to the neighbor
 *
 * LinkDownReasons only set अगर transition succeeds.
 */
अटल पूर्णांक जाओ_offline(काष्ठा hfi1_pportdata *ppd, u8 rem_reason)
अणु
	काष्ठा hfi1_devdata *dd = ppd->dd;
	u32 previous_state;
	पूर्णांक offline_state_ret;
	पूर्णांक ret;

	update_lcb_cache(dd);

	previous_state = ppd->host_link_state;
	ppd->host_link_state = HLS_GOING_OFFLINE;

	/* start offline transition */
	ret = set_physical_link_state(dd, (rem_reason << 8) | PLS_OFFLINE);

	अगर (ret != HCMD_SUCCESS) अणु
		dd_dev_err(dd,
			   "Failed to transition to Offline link state, return %d\n",
			   ret);
		वापस -EINVAL;
	पूर्ण
	अगर (ppd->offline_disabled_reason ==
			HFI1_ODR_MASK(OPA_LINKDOWN_REASON_NONE))
		ppd->offline_disabled_reason =
		HFI1_ODR_MASK(OPA_LINKDOWN_REASON_TRANSIENT);

	offline_state_ret = रुको_phys_link_offline_substates(ppd, 10000);
	अगर (offline_state_ret < 0)
		वापस offline_state_ret;

	/* Disabling AOC transmitters */
	अगर (ppd->port_type == PORT_TYPE_QSFP &&
	    ppd->qsfp_info.limiting_active &&
	    qsfp_mod_present(ppd)) अणु
		पूर्णांक ret;

		ret = acquire_chip_resource(dd, qsfp_resource(dd), QSFP_WAIT);
		अगर (ret == 0) अणु
			set_qsfp_tx(ppd, 0);
			release_chip_resource(dd, qsfp_resource(dd));
		पूर्ण अन्यथा अणु
			/* not fatal, but should warn */
			dd_dev_err(dd,
				   "Unable to acquire lock to turn off QSFP TX\n");
		पूर्ण
	पूर्ण

	/*
	 * Wait क्रम the offline.Quiet transition अगर it hasn't happened yet. It
	 * can take a जबतक क्रम the link to go करोwn.
	 */
	अगर (offline_state_ret != PLS_OFFLINE_QUIET) अणु
		ret = रुको_physical_linkstate(ppd, PLS_OFFLINE, 30000);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/*
	 * Now in अक्षरge of LCB - must be after the physical state is
	 * offline.quiet and beक्रमe host_link_state is changed.
	 */
	set_host_lcb_access(dd);
	ग_लिखो_csr(dd, DC_LCB_ERR_EN, ~0ull); /* watch LCB errors */

	/* make sure the logical state is also करोwn */
	ret = रुको_logical_linkstate(ppd, IB_PORT_DOWN, 1000);
	अगर (ret)
		क्रमce_logical_link_state_करोwn(ppd);

	ppd->host_link_state = HLS_LINK_COOLDOWN; /* LCB access allowed */
	update_statusp(ppd, IB_PORT_DOWN);

	/*
	 * The LNI has a mandatory रुको समय after the physical state
	 * moves to Offline.Quiet.  The रुको समय may be dअगरferent
	 * depending on how the link went करोwn.  The 8051 firmware
	 * will observe the needed रुको समय and only move to पढ़ोy
	 * when that is completed.  The largest of the quiet समयouts
	 * is 6s, so रुको that दीर्घ and then at least 0.5s more क्रम
	 * other transitions, and another 0.5s क्रम a buffer.
	 */
	ret = रुको_fm_पढ़ोy(dd, 7000);
	अगर (ret) अणु
		dd_dev_err(dd,
			   "After going offline, timed out waiting for the 8051 to become ready to accept host requests\n");
		/* state is really offline, so make it so */
		ppd->host_link_state = HLS_DN_OFFLINE;
		वापस ret;
	पूर्ण

	/*
	 * The state is now offline and the 8051 is पढ़ोy to accept host
	 * requests.
	 *	- change our state
	 *	- notअगरy others अगर we were previously in a linkup state
	 */
	ppd->host_link_state = HLS_DN_OFFLINE;
	अगर (previous_state & HLS_UP) अणु
		/* went करोwn जबतक link was up */
		handle_linkup_change(dd, 0);
	पूर्ण अन्यथा अगर (previous_state
			& (HLS_DN_POLL | HLS_VERIFY_CAP | HLS_GOING_UP)) अणु
		/* went करोwn जबतक attempting link up */
		check_lni_states(ppd);

		/* The QSFP करोesn't need to be reset on LNI failure */
		ppd->qsfp_info.reset_needed = 0;
	पूर्ण

	/* the active link width (करोwngrade) is 0 on link करोwn */
	ppd->link_width_active = 0;
	ppd->link_width_करोwngrade_tx_active = 0;
	ppd->link_width_करोwngrade_rx_active = 0;
	ppd->current_egress_rate = 0;
	वापस 0;
पूर्ण

/* वापस the link state name */
अटल स्थिर अक्षर *link_state_name(u32 state)
अणु
	स्थिर अक्षर *name;
	पूर्णांक n = ilog2(state);
	अटल स्थिर अक्षर * स्थिर names[] = अणु
		[__HLS_UP_INIT_BP]	 = "INIT",
		[__HLS_UP_ARMED_BP]	 = "ARMED",
		[__HLS_UP_ACTIVE_BP]	 = "ACTIVE",
		[__HLS_DN_DOWNDEF_BP]	 = "DOWNDEF",
		[__HLS_DN_POLL_BP]	 = "POLL",
		[__HLS_DN_DISABLE_BP]	 = "DISABLE",
		[__HLS_DN_OFFLINE_BP]	 = "OFFLINE",
		[__HLS_VERIFY_CAP_BP]	 = "VERIFY_CAP",
		[__HLS_GOING_UP_BP]	 = "GOING_UP",
		[__HLS_GOING_OFFLINE_BP] = "GOING_OFFLINE",
		[__HLS_LINK_COOLDOWN_BP] = "LINK_COOLDOWN"
	पूर्ण;

	name = n < ARRAY_SIZE(names) ? names[n] : शून्य;
	वापस name ? name : "unknown";
पूर्ण

/* वापस the link state reason name */
अटल स्थिर अक्षर *link_state_reason_name(काष्ठा hfi1_pportdata *ppd, u32 state)
अणु
	अगर (state == HLS_UP_INIT) अणु
		चयन (ppd->linkinit_reason) अणु
		हाल OPA_LINKINIT_REASON_LINKUP:
			वापस "(LINKUP)";
		हाल OPA_LINKINIT_REASON_FLAPPING:
			वापस "(FLAPPING)";
		हाल OPA_LINKINIT_OUTSIDE_POLICY:
			वापस "(OUTSIDE_POLICY)";
		हाल OPA_LINKINIT_QUARANTINED:
			वापस "(QUARANTINED)";
		हाल OPA_LINKINIT_INSUFIC_CAPABILITY:
			वापस "(INSUFIC_CAPABILITY)";
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	वापस "";
पूर्ण

/*
 * driver_pstate - convert the driver's notion of a port's
 * state (an HLS_*) पूर्णांकo a physical state (a अणुIB,OPAपूर्ण_PORTPHYSSTATE_*).
 * Return -1 (converted to a u32) to indicate error.
 */
u32 driver_pstate(काष्ठा hfi1_pportdata *ppd)
अणु
	चयन (ppd->host_link_state) अणु
	हाल HLS_UP_INIT:
	हाल HLS_UP_ARMED:
	हाल HLS_UP_ACTIVE:
		वापस IB_PORTPHYSSTATE_LINKUP;
	हाल HLS_DN_POLL:
		वापस IB_PORTPHYSSTATE_POLLING;
	हाल HLS_DN_DISABLE:
		वापस IB_PORTPHYSSTATE_DISABLED;
	हाल HLS_DN_OFFLINE:
		वापस OPA_PORTPHYSSTATE_OFFLINE;
	हाल HLS_VERIFY_CAP:
		वापस IB_PORTPHYSSTATE_TRAINING;
	हाल HLS_GOING_UP:
		वापस IB_PORTPHYSSTATE_TRAINING;
	हाल HLS_GOING_OFFLINE:
		वापस OPA_PORTPHYSSTATE_OFFLINE;
	हाल HLS_LINK_COOLDOWN:
		वापस OPA_PORTPHYSSTATE_OFFLINE;
	हाल HLS_DN_DOWNDEF:
	शेष:
		dd_dev_err(ppd->dd, "invalid host_link_state 0x%x\n",
			   ppd->host_link_state);
		वापस  -1;
	पूर्ण
पूर्ण

/*
 * driver_lstate - convert the driver's notion of a port's
 * state (an HLS_*) पूर्णांकo a logical state (a IB_PORT_*). Return -1
 * (converted to a u32) to indicate error.
 */
u32 driver_lstate(काष्ठा hfi1_pportdata *ppd)
अणु
	अगर (ppd->host_link_state && (ppd->host_link_state & HLS_DOWN))
		वापस IB_PORT_DOWN;

	चयन (ppd->host_link_state & HLS_UP) अणु
	हाल HLS_UP_INIT:
		वापस IB_PORT_INIT;
	हाल HLS_UP_ARMED:
		वापस IB_PORT_ARMED;
	हाल HLS_UP_ACTIVE:
		वापस IB_PORT_ACTIVE;
	शेष:
		dd_dev_err(ppd->dd, "invalid host_link_state 0x%x\n",
			   ppd->host_link_state);
	वापस -1;
	पूर्ण
पूर्ण

व्योम set_link_करोwn_reason(काष्ठा hfi1_pportdata *ppd, u8 lcl_reason,
			  u8 neigh_reason, u8 rem_reason)
अणु
	अगर (ppd->local_link_करोwn_reason.latest == 0 &&
	    ppd->neigh_link_करोwn_reason.latest == 0) अणु
		ppd->local_link_करोwn_reason.latest = lcl_reason;
		ppd->neigh_link_करोwn_reason.latest = neigh_reason;
		ppd->remote_link_करोwn_reason = rem_reason;
	पूर्ण
पूर्ण

/**
 * data_vls_operational() - Verअगरy अगर data VL BCT credits and MTU
 *			    are both set.
 * @ppd: poपूर्णांकer to hfi1_pportdata काष्ठाure
 *
 * Return: true - Ok, false -otherwise.
 */
अटल अंतरभूत bool data_vls_operational(काष्ठा hfi1_pportdata *ppd)
अणु
	पूर्णांक i;
	u64 reg;

	अगर (!ppd->actual_vls_operational)
		वापस false;

	क्रम (i = 0; i < ppd->vls_supported; i++) अणु
		reg = पढ़ो_csr(ppd->dd, SEND_CM_CREDIT_VL + (8 * i));
		अगर ((reg && !ppd->dd->vld[i].mtu) ||
		    (!reg && ppd->dd->vld[i].mtu))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

/*
 * Change the physical and/or logical link state.
 *
 * Do not call this routine जबतक inside an पूर्णांकerrupt.  It contains
 * calls to routines that can take multiple seconds to finish.
 *
 * Returns 0 on success, -त्रुटि_सं on failure.
 */
पूर्णांक set_link_state(काष्ठा hfi1_pportdata *ppd, u32 state)
अणु
	काष्ठा hfi1_devdata *dd = ppd->dd;
	काष्ठा ib_event event = अणु.device = शून्यपूर्ण;
	पूर्णांक ret1, ret = 0;
	पूर्णांक orig_new_state, poll_bounce;

	mutex_lock(&ppd->hls_lock);

	orig_new_state = state;
	अगर (state == HLS_DN_DOWNDEF)
		state = HLS_DEFAULT;

	/* पूर्णांकerpret poll -> poll as a link bounce */
	poll_bounce = ppd->host_link_state == HLS_DN_POLL &&
		      state == HLS_DN_POLL;

	dd_dev_info(dd, "%s: current %s, new %s %s%s\n", __func__,
		    link_state_name(ppd->host_link_state),
		    link_state_name(orig_new_state),
		    poll_bounce ? "(bounce) " : "",
		    link_state_reason_name(ppd, state));

	/*
	 * If we're going to a (HLS_*) link state that implies the logical
	 * link state is neither of (IB_PORT_ARMED, IB_PORT_ACTIVE), then
	 * reset is_sm_config_started to 0.
	 */
	अगर (!(state & (HLS_UP_ARMED | HLS_UP_ACTIVE)))
		ppd->is_sm_config_started = 0;

	/*
	 * Do nothing अगर the states match.  Let a poll to poll link bounce
	 * go through.
	 */
	अगर (ppd->host_link_state == state && !poll_bounce)
		जाओ करोne;

	चयन (state) अणु
	हाल HLS_UP_INIT:
		अगर (ppd->host_link_state == HLS_DN_POLL &&
		    (quick_linkup || dd->icode == ICODE_FUNCTIONAL_SIMULATOR)) अणु
			/*
			 * Quick link up jumps from polling to here.
			 *
			 * Whether in normal or loopback mode, the
			 * simulator jumps from polling to link up.
			 * Accept that here.
			 */
			/* OK */
		पूर्ण अन्यथा अगर (ppd->host_link_state != HLS_GOING_UP) अणु
			जाओ unexpected;
		पूर्ण

		/*
		 * Wait क्रम Link_Up physical state.
		 * Physical and Logical states should alपढ़ोy be
		 * be transitioned to LinkUp and LinkInit respectively.
		 */
		ret = रुको_physical_linkstate(ppd, PLS_LINKUP, 1000);
		अगर (ret) अणु
			dd_dev_err(dd,
				   "%s: physical state did not change to LINK-UP\n",
				   __func__);
			अवरोध;
		पूर्ण

		ret = रुको_logical_linkstate(ppd, IB_PORT_INIT, 1000);
		अगर (ret) अणु
			dd_dev_err(dd,
				   "%s: logical state did not change to INIT\n",
				   __func__);
			अवरोध;
		पूर्ण

		/* clear old transient LINKINIT_REASON code */
		अगर (ppd->linkinit_reason >= OPA_LINKINIT_REASON_CLEAR)
			ppd->linkinit_reason =
				OPA_LINKINIT_REASON_LINKUP;

		/* enable the port */
		add_rcvctrl(dd, RCV_CTRL_RCV_PORT_ENABLE_SMASK);

		handle_linkup_change(dd, 1);
		pio_kernel_linkup(dd);

		/*
		 * After link up, a new link width will have been set.
		 * Update the xmit counters with regards to the new
		 * link width.
		 */
		update_xmit_counters(ppd, ppd->link_width_active);

		ppd->host_link_state = HLS_UP_INIT;
		update_statusp(ppd, IB_PORT_INIT);
		अवरोध;
	हाल HLS_UP_ARMED:
		अगर (ppd->host_link_state != HLS_UP_INIT)
			जाओ unexpected;

		अगर (!data_vls_operational(ppd)) अणु
			dd_dev_err(dd,
				   "%s: Invalid data VL credits or mtu\n",
				   __func__);
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		set_logical_state(dd, LSTATE_ARMED);
		ret = रुको_logical_linkstate(ppd, IB_PORT_ARMED, 1000);
		अगर (ret) अणु
			dd_dev_err(dd,
				   "%s: logical state did not change to ARMED\n",
				   __func__);
			अवरोध;
		पूर्ण
		ppd->host_link_state = HLS_UP_ARMED;
		update_statusp(ppd, IB_PORT_ARMED);
		/*
		 * The simulator करोes not currently implement SMA messages,
		 * so neighbor_normal is not set.  Set it here when we first
		 * move to Armed.
		 */
		अगर (dd->icode == ICODE_FUNCTIONAL_SIMULATOR)
			ppd->neighbor_normal = 1;
		अवरोध;
	हाल HLS_UP_ACTIVE:
		अगर (ppd->host_link_state != HLS_UP_ARMED)
			जाओ unexpected;

		set_logical_state(dd, LSTATE_ACTIVE);
		ret = रुको_logical_linkstate(ppd, IB_PORT_ACTIVE, 1000);
		अगर (ret) अणु
			dd_dev_err(dd,
				   "%s: logical state did not change to ACTIVE\n",
				   __func__);
		पूर्ण अन्यथा अणु
			/* tell all engines to go running */
			sdma_all_running(dd);
			ppd->host_link_state = HLS_UP_ACTIVE;
			update_statusp(ppd, IB_PORT_ACTIVE);

			/* Signal the IB layer that the port has went active */
			event.device = &dd->verbs_dev.rdi.ibdev;
			event.element.port_num = ppd->port;
			event.event = IB_EVENT_PORT_ACTIVE;
		पूर्ण
		अवरोध;
	हाल HLS_DN_POLL:
		अगर ((ppd->host_link_state == HLS_DN_DISABLE ||
		     ppd->host_link_state == HLS_DN_OFFLINE) &&
		    dd->dc_shutकरोwn)
			dc_start(dd);
		/* Hand LED control to the DC */
		ग_लिखो_csr(dd, DCC_CFG_LED_CNTRL, 0);

		अगर (ppd->host_link_state != HLS_DN_OFFLINE) अणु
			u8 पंचांगp = ppd->link_enabled;

			ret = जाओ_offline(ppd, ppd->remote_link_करोwn_reason);
			अगर (ret) अणु
				ppd->link_enabled = पंचांगp;
				अवरोध;
			पूर्ण
			ppd->remote_link_करोwn_reason = 0;

			अगर (ppd->driver_link_पढ़ोy)
				ppd->link_enabled = 1;
		पूर्ण

		set_all_slowpath(ppd->dd);
		ret = set_local_link_attributes(ppd);
		अगर (ret)
			अवरोध;

		ppd->port_error_action = 0;

		अगर (quick_linkup) अणु
			/* quick linkup करोes not go पूर्णांकo polling */
			ret = करो_quick_linkup(dd);
		पूर्ण अन्यथा अणु
			ret1 = set_physical_link_state(dd, PLS_POLLING);
			अगर (!ret1)
				ret1 = रुको_phys_link_out_of_offline(ppd,
								     3000);
			अगर (ret1 != HCMD_SUCCESS) अणु
				dd_dev_err(dd,
					   "Failed to transition to Polling link state, return 0x%x\n",
					   ret1);
				ret = -EINVAL;
			पूर्ण
		पूर्ण

		/*
		 * Change the host link state after requesting DC8051 to
		 * change its physical state so that we can ignore any
		 * पूर्णांकerrupt with stale LNI(XX) error, which will not be
		 * cleared until DC8051 transitions to Polling state.
		 */
		ppd->host_link_state = HLS_DN_POLL;
		ppd->offline_disabled_reason =
			HFI1_ODR_MASK(OPA_LINKDOWN_REASON_NONE);
		/*
		 * If an error occurred above, go back to offline.  The
		 * caller may reschedule another attempt.
		 */
		अगर (ret)
			जाओ_offline(ppd, 0);
		अन्यथा
			log_physical_state(ppd, PLS_POLLING);
		अवरोध;
	हाल HLS_DN_DISABLE:
		/* link is disabled */
		ppd->link_enabled = 0;

		/* allow any state to transition to disabled */

		/* must transition to offline first */
		अगर (ppd->host_link_state != HLS_DN_OFFLINE) अणु
			ret = जाओ_offline(ppd, ppd->remote_link_करोwn_reason);
			अगर (ret)
				अवरोध;
			ppd->remote_link_करोwn_reason = 0;
		पूर्ण

		अगर (!dd->dc_shutकरोwn) अणु
			ret1 = set_physical_link_state(dd, PLS_DISABLED);
			अगर (ret1 != HCMD_SUCCESS) अणु
				dd_dev_err(dd,
					   "Failed to transition to Disabled link state, return 0x%x\n",
					   ret1);
				ret = -EINVAL;
				अवरोध;
			पूर्ण
			ret = रुको_physical_linkstate(ppd, PLS_DISABLED, 10000);
			अगर (ret) अणु
				dd_dev_err(dd,
					   "%s: physical state did not change to DISABLED\n",
					   __func__);
				अवरोध;
			पूर्ण
			dc_shutकरोwn(dd);
		पूर्ण
		ppd->host_link_state = HLS_DN_DISABLE;
		अवरोध;
	हाल HLS_DN_OFFLINE:
		अगर (ppd->host_link_state == HLS_DN_DISABLE)
			dc_start(dd);

		/* allow any state to transition to offline */
		ret = जाओ_offline(ppd, ppd->remote_link_करोwn_reason);
		अगर (!ret)
			ppd->remote_link_करोwn_reason = 0;
		अवरोध;
	हाल HLS_VERIFY_CAP:
		अगर (ppd->host_link_state != HLS_DN_POLL)
			जाओ unexpected;
		ppd->host_link_state = HLS_VERIFY_CAP;
		log_physical_state(ppd, PLS_CONFIGPHY_VERIFYCAP);
		अवरोध;
	हाल HLS_GOING_UP:
		अगर (ppd->host_link_state != HLS_VERIFY_CAP)
			जाओ unexpected;

		ret1 = set_physical_link_state(dd, PLS_LINKUP);
		अगर (ret1 != HCMD_SUCCESS) अणु
			dd_dev_err(dd,
				   "Failed to transition to link up state, return 0x%x\n",
				   ret1);
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		ppd->host_link_state = HLS_GOING_UP;
		अवरोध;

	हाल HLS_GOING_OFFLINE:		/* transient within जाओ_offline() */
	हाल HLS_LINK_COOLDOWN:		/* transient within जाओ_offline() */
	शेष:
		dd_dev_info(dd, "%s: state 0x%x: not supported\n",
			    __func__, state);
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	जाओ करोne;

unexpected:
	dd_dev_err(dd, "%s: unexpected state transition from %s to %s\n",
		   __func__, link_state_name(ppd->host_link_state),
		   link_state_name(state));
	ret = -EINVAL;

करोne:
	mutex_unlock(&ppd->hls_lock);

	अगर (event.device)
		ib_dispatch_event(&event);

	वापस ret;
पूर्ण

पूर्णांक hfi1_set_ib_cfg(काष्ठा hfi1_pportdata *ppd, पूर्णांक which, u32 val)
अणु
	u64 reg;
	पूर्णांक ret = 0;

	चयन (which) अणु
	हाल HFI1_IB_CFG_LIDLMC:
		set_lidlmc(ppd);
		अवरोध;
	हाल HFI1_IB_CFG_VL_HIGH_LIMIT:
		/*
		 * The VL Arbitrator high limit is sent in units of 4k
		 * bytes, जबतक HFI stores it in units of 64 bytes.
		 */
		val *= 4096 / 64;
		reg = ((u64)val & SEND_HIGH_PRIORITY_LIMIT_LIMIT_MASK)
			<< SEND_HIGH_PRIORITY_LIMIT_LIMIT_SHIFT;
		ग_लिखो_csr(ppd->dd, SEND_HIGH_PRIORITY_LIMIT, reg);
		अवरोध;
	हाल HFI1_IB_CFG_LINKDEFAULT: /* IB link शेष (sleep/poll) */
		/* HFI only supports POLL as the शेष link करोwn state */
		अगर (val != HLS_DN_POLL)
			ret = -EINVAL;
		अवरोध;
	हाल HFI1_IB_CFG_OP_VLS:
		अगर (ppd->vls_operational != val) अणु
			ppd->vls_operational = val;
			अगर (!ppd->port)
				ret = -EINVAL;
		पूर्ण
		अवरोध;
	/*
	 * For link width, link width करोwngrade, and speed enable, always AND
	 * the setting with what is actually supported.  This has two benefits.
	 * First, enabled can't have unsupported values, no matter what the
	 * SM or FM might want.  Second, the ALL_SUPPORTED wildcards that mean
	 * "fill in with your supported value" have all the bits in the
	 * field set, so simply ANDing with supported has the desired result.
	 */
	हाल HFI1_IB_CFG_LWID_ENB: /* set allowed Link-width */
		ppd->link_width_enabled = val & ppd->link_width_supported;
		अवरोध;
	हाल HFI1_IB_CFG_LWID_DG_ENB: /* set allowed link width करोwngrade */
		ppd->link_width_करोwngrade_enabled =
				val & ppd->link_width_करोwngrade_supported;
		अवरोध;
	हाल HFI1_IB_CFG_SPD_ENB: /* allowed Link speeds */
		ppd->link_speed_enabled = val & ppd->link_speed_supported;
		अवरोध;
	हाल HFI1_IB_CFG_OVERRUN_THRESH: /* IB overrun threshold */
		/*
		 * HFI करोes not follow IB specs, save this value
		 * so we can report it, अगर asked.
		 */
		ppd->overrun_threshold = val;
		अवरोध;
	हाल HFI1_IB_CFG_PHYERR_THRESH: /* IB PHY error threshold */
		/*
		 * HFI करोes not follow IB specs, save this value
		 * so we can report it, अगर asked.
		 */
		ppd->phy_error_threshold = val;
		अवरोध;

	हाल HFI1_IB_CFG_MTU:
		set_send_length(ppd);
		अवरोध;

	हाल HFI1_IB_CFG_PKEYS:
		अगर (HFI1_CAP_IS_KSET(PKEY_CHECK))
			set_partition_keys(ppd);
		अवरोध;

	शेष:
		अगर (HFI1_CAP_IS_KSET(PRINT_UNIMPL))
			dd_dev_info(ppd->dd,
				    "%s: which %s, val 0x%x: not implemented\n",
				    __func__, ib_cfg_name(which), val);
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

/* begin functions related to vl arbitration table caching */
अटल व्योम init_vl_arb_caches(काष्ठा hfi1_pportdata *ppd)
अणु
	पूर्णांक i;

	BUILD_BUG_ON(VL_ARB_TABLE_SIZE !=
			VL_ARB_LOW_PRIO_TABLE_SIZE);
	BUILD_BUG_ON(VL_ARB_TABLE_SIZE !=
			VL_ARB_HIGH_PRIO_TABLE_SIZE);

	/*
	 * Note that we always वापस values directly from the
	 * 'vl_arb_cache' (and करो no CSR पढ़ोs) in response to a
	 * 'Get(VLArbTable)'. This is obviously correct after a
	 * 'Set(VLArbTable)', since the cache will then be up to
	 * date. But it's also correct prior to any 'Set(VLArbTable)'
	 * since then both the cache, and the relevant h/w रेजिस्टरs
	 * will be zeroed.
	 */

	क्रम (i = 0; i < MAX_PRIO_TABLE; i++)
		spin_lock_init(&ppd->vl_arb_cache[i].lock);
पूर्ण

/*
 * vl_arb_lock_cache
 *
 * All other vl_arb_* functions should be called only after locking
 * the cache.
 */
अटल अंतरभूत काष्ठा vl_arb_cache *
vl_arb_lock_cache(काष्ठा hfi1_pportdata *ppd, पूर्णांक idx)
अणु
	अगर (idx != LO_PRIO_TABLE && idx != HI_PRIO_TABLE)
		वापस शून्य;
	spin_lock(&ppd->vl_arb_cache[idx].lock);
	वापस &ppd->vl_arb_cache[idx];
पूर्ण

अटल अंतरभूत व्योम vl_arb_unlock_cache(काष्ठा hfi1_pportdata *ppd, पूर्णांक idx)
अणु
	spin_unlock(&ppd->vl_arb_cache[idx].lock);
पूर्ण

अटल व्योम vl_arb_get_cache(काष्ठा vl_arb_cache *cache,
			     काष्ठा ib_vl_weight_elem *vl)
अणु
	स_नकल(vl, cache->table, VL_ARB_TABLE_SIZE * माप(*vl));
पूर्ण

अटल व्योम vl_arb_set_cache(काष्ठा vl_arb_cache *cache,
			     काष्ठा ib_vl_weight_elem *vl)
अणु
	स_नकल(cache->table, vl, VL_ARB_TABLE_SIZE * माप(*vl));
पूर्ण

अटल पूर्णांक vl_arb_match_cache(काष्ठा vl_arb_cache *cache,
			      काष्ठा ib_vl_weight_elem *vl)
अणु
	वापस !स_भेद(cache->table, vl, VL_ARB_TABLE_SIZE * माप(*vl));
पूर्ण

/* end functions related to vl arbitration table caching */

अटल पूर्णांक set_vl_weights(काष्ठा hfi1_pportdata *ppd, u32 target,
			  u32 size, काष्ठा ib_vl_weight_elem *vl)
अणु
	काष्ठा hfi1_devdata *dd = ppd->dd;
	u64 reg;
	अचिन्हित पूर्णांक i, is_up = 0;
	पूर्णांक drain, ret = 0;

	mutex_lock(&ppd->hls_lock);

	अगर (ppd->host_link_state & HLS_UP)
		is_up = 1;

	drain = !is_ax(dd) && is_up;

	अगर (drain)
		/*
		 * Beक्रमe adjusting VL arbitration weights, empty per-VL
		 * FIFOs, otherwise a packet whose VL weight is being
		 * set to 0 could get stuck in a FIFO with no chance to
		 * egress.
		 */
		ret = stop_drain_data_vls(dd);

	अगर (ret) अणु
		dd_dev_err(
			dd,
			"%s: cannot stop/drain VLs - refusing to change VL arbitration weights\n",
			__func__);
		जाओ err;
	पूर्ण

	क्रम (i = 0; i < size; i++, vl++) अणु
		/*
		 * NOTE: The low priority shअगरt and mask are used here, but
		 * they are the same क्रम both the low and high रेजिस्टरs.
		 */
		reg = (((u64)vl->vl & SEND_LOW_PRIORITY_LIST_VL_MASK)
				<< SEND_LOW_PRIORITY_LIST_VL_SHIFT)
		      | (((u64)vl->weight
				& SEND_LOW_PRIORITY_LIST_WEIGHT_MASK)
				<< SEND_LOW_PRIORITY_LIST_WEIGHT_SHIFT);
		ग_लिखो_csr(dd, target + (i * 8), reg);
	पूर्ण
	pio_send_control(dd, PSC_GLOBAL_VLARB_ENABLE);

	अगर (drain)
		खोलो_fill_data_vls(dd); /* reखोलो all VLs */

err:
	mutex_unlock(&ppd->hls_lock);

	वापस ret;
पूर्ण

/*
 * Read one credit merge VL रेजिस्टर.
 */
अटल व्योम पढ़ो_one_cm_vl(काष्ठा hfi1_devdata *dd, u32 csr,
			   काष्ठा vl_limit *vll)
अणु
	u64 reg = पढ़ो_csr(dd, csr);

	vll->dedicated = cpu_to_be16(
		(reg >> SEND_CM_CREDIT_VL_DEDICATED_LIMIT_VL_SHIFT)
		& SEND_CM_CREDIT_VL_DEDICATED_LIMIT_VL_MASK);
	vll->shared = cpu_to_be16(
		(reg >> SEND_CM_CREDIT_VL_SHARED_LIMIT_VL_SHIFT)
		& SEND_CM_CREDIT_VL_SHARED_LIMIT_VL_MASK);
पूर्ण

/*
 * Read the current credit merge limits.
 */
अटल पूर्णांक get_buffer_control(काष्ठा hfi1_devdata *dd,
			      काष्ठा buffer_control *bc, u16 *overall_limit)
अणु
	u64 reg;
	पूर्णांक i;

	/* not all entries are filled in */
	स_रखो(bc, 0, माप(*bc));

	/* OPA and HFI have a 1-1 mapping */
	क्रम (i = 0; i < TXE_NUM_DATA_VL; i++)
		पढ़ो_one_cm_vl(dd, SEND_CM_CREDIT_VL + (8 * i), &bc->vl[i]);

	/* NOTE: assumes that VL* and VL15 CSRs are bit-wise identical */
	पढ़ो_one_cm_vl(dd, SEND_CM_CREDIT_VL15, &bc->vl[15]);

	reg = पढ़ो_csr(dd, SEND_CM_GLOBAL_CREDIT);
	bc->overall_shared_limit = cpu_to_be16(
		(reg >> SEND_CM_GLOBAL_CREDIT_SHARED_LIMIT_SHIFT)
		& SEND_CM_GLOBAL_CREDIT_SHARED_LIMIT_MASK);
	अगर (overall_limit)
		*overall_limit = (reg
			>> SEND_CM_GLOBAL_CREDIT_TOTAL_CREDIT_LIMIT_SHIFT)
			& SEND_CM_GLOBAL_CREDIT_TOTAL_CREDIT_LIMIT_MASK;
	वापस माप(काष्ठा buffer_control);
पूर्ण

अटल पूर्णांक get_sc2vlnt(काष्ठा hfi1_devdata *dd, काष्ठा sc2vlnt *dp)
अणु
	u64 reg;
	पूर्णांक i;

	/* each रेजिस्टर contains 16 SC->VLnt mappings, 4 bits each */
	reg = पढ़ो_csr(dd, DCC_CFG_SC_VL_TABLE_15_0);
	क्रम (i = 0; i < माप(u64); i++) अणु
		u8 byte = *(((u8 *)&reg) + i);

		dp->vlnt[2 * i] = byte & 0xf;
		dp->vlnt[(2 * i) + 1] = (byte & 0xf0) >> 4;
	पूर्ण

	reg = पढ़ो_csr(dd, DCC_CFG_SC_VL_TABLE_31_16);
	क्रम (i = 0; i < माप(u64); i++) अणु
		u8 byte = *(((u8 *)&reg) + i);

		dp->vlnt[16 + (2 * i)] = byte & 0xf;
		dp->vlnt[16 + (2 * i) + 1] = (byte & 0xf0) >> 4;
	पूर्ण
	वापस माप(काष्ठा sc2vlnt);
पूर्ण

अटल व्योम get_vlarb_preempt(काष्ठा hfi1_devdata *dd, u32 nelems,
			      काष्ठा ib_vl_weight_elem *vl)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < nelems; i++, vl++) अणु
		vl->vl = 0xf;
		vl->weight = 0;
	पूर्ण
पूर्ण

अटल व्योम set_sc2vlnt(काष्ठा hfi1_devdata *dd, काष्ठा sc2vlnt *dp)
अणु
	ग_लिखो_csr(dd, DCC_CFG_SC_VL_TABLE_15_0,
		  DC_SC_VL_VAL(15_0,
			       0, dp->vlnt[0] & 0xf,
			       1, dp->vlnt[1] & 0xf,
			       2, dp->vlnt[2] & 0xf,
			       3, dp->vlnt[3] & 0xf,
			       4, dp->vlnt[4] & 0xf,
			       5, dp->vlnt[5] & 0xf,
			       6, dp->vlnt[6] & 0xf,
			       7, dp->vlnt[7] & 0xf,
			       8, dp->vlnt[8] & 0xf,
			       9, dp->vlnt[9] & 0xf,
			       10, dp->vlnt[10] & 0xf,
			       11, dp->vlnt[11] & 0xf,
			       12, dp->vlnt[12] & 0xf,
			       13, dp->vlnt[13] & 0xf,
			       14, dp->vlnt[14] & 0xf,
			       15, dp->vlnt[15] & 0xf));
	ग_लिखो_csr(dd, DCC_CFG_SC_VL_TABLE_31_16,
		  DC_SC_VL_VAL(31_16,
			       16, dp->vlnt[16] & 0xf,
			       17, dp->vlnt[17] & 0xf,
			       18, dp->vlnt[18] & 0xf,
			       19, dp->vlnt[19] & 0xf,
			       20, dp->vlnt[20] & 0xf,
			       21, dp->vlnt[21] & 0xf,
			       22, dp->vlnt[22] & 0xf,
			       23, dp->vlnt[23] & 0xf,
			       24, dp->vlnt[24] & 0xf,
			       25, dp->vlnt[25] & 0xf,
			       26, dp->vlnt[26] & 0xf,
			       27, dp->vlnt[27] & 0xf,
			       28, dp->vlnt[28] & 0xf,
			       29, dp->vlnt[29] & 0xf,
			       30, dp->vlnt[30] & 0xf,
			       31, dp->vlnt[31] & 0xf));
पूर्ण

अटल व्योम nonzero_msg(काष्ठा hfi1_devdata *dd, पूर्णांक idx, स्थिर अक्षर *what,
			u16 limit)
अणु
	अगर (limit != 0)
		dd_dev_info(dd, "Invalid %s limit %d on VL %d, ignoring\n",
			    what, (पूर्णांक)limit, idx);
पूर्ण

/* change only the shared limit portion of SendCmGLobalCredit */
अटल व्योम set_global_shared(काष्ठा hfi1_devdata *dd, u16 limit)
अणु
	u64 reg;

	reg = पढ़ो_csr(dd, SEND_CM_GLOBAL_CREDIT);
	reg &= ~SEND_CM_GLOBAL_CREDIT_SHARED_LIMIT_SMASK;
	reg |= (u64)limit << SEND_CM_GLOBAL_CREDIT_SHARED_LIMIT_SHIFT;
	ग_लिखो_csr(dd, SEND_CM_GLOBAL_CREDIT, reg);
पूर्ण

/* change only the total credit limit portion of SendCmGLobalCredit */
अटल व्योम set_global_limit(काष्ठा hfi1_devdata *dd, u16 limit)
अणु
	u64 reg;

	reg = पढ़ो_csr(dd, SEND_CM_GLOBAL_CREDIT);
	reg &= ~SEND_CM_GLOBAL_CREDIT_TOTAL_CREDIT_LIMIT_SMASK;
	reg |= (u64)limit << SEND_CM_GLOBAL_CREDIT_TOTAL_CREDIT_LIMIT_SHIFT;
	ग_लिखो_csr(dd, SEND_CM_GLOBAL_CREDIT, reg);
पूर्ण

/* set the given per-VL shared limit */
अटल व्योम set_vl_shared(काष्ठा hfi1_devdata *dd, पूर्णांक vl, u16 limit)
अणु
	u64 reg;
	u32 addr;

	अगर (vl < TXE_NUM_DATA_VL)
		addr = SEND_CM_CREDIT_VL + (8 * vl);
	अन्यथा
		addr = SEND_CM_CREDIT_VL15;

	reg = पढ़ो_csr(dd, addr);
	reg &= ~SEND_CM_CREDIT_VL_SHARED_LIMIT_VL_SMASK;
	reg |= (u64)limit << SEND_CM_CREDIT_VL_SHARED_LIMIT_VL_SHIFT;
	ग_लिखो_csr(dd, addr, reg);
पूर्ण

/* set the given per-VL dedicated limit */
अटल व्योम set_vl_dedicated(काष्ठा hfi1_devdata *dd, पूर्णांक vl, u16 limit)
अणु
	u64 reg;
	u32 addr;

	अगर (vl < TXE_NUM_DATA_VL)
		addr = SEND_CM_CREDIT_VL + (8 * vl);
	अन्यथा
		addr = SEND_CM_CREDIT_VL15;

	reg = पढ़ो_csr(dd, addr);
	reg &= ~SEND_CM_CREDIT_VL_DEDICATED_LIMIT_VL_SMASK;
	reg |= (u64)limit << SEND_CM_CREDIT_VL_DEDICATED_LIMIT_VL_SHIFT;
	ग_लिखो_csr(dd, addr, reg);
पूर्ण

/* spin until the given per-VL status mask bits clear */
अटल व्योम रुको_क्रम_vl_status_clear(काष्ठा hfi1_devdata *dd, u64 mask,
				     स्थिर अक्षर *which)
अणु
	अचिन्हित दीर्घ समयout;
	u64 reg;

	समयout = jअगरfies + msecs_to_jअगरfies(VL_STATUS_CLEAR_TIMEOUT);
	जबतक (1) अणु
		reg = पढ़ो_csr(dd, SEND_CM_CREDIT_USED_STATUS) & mask;

		अगर (reg == 0)
			वापस;	/* success */
		अगर (समय_after(jअगरfies, समयout))
			अवरोध;		/* समयd out */
		udelay(1);
	पूर्ण

	dd_dev_err(dd,
		   "%s credit change status not clearing after %dms, mask 0x%llx, not clear 0x%llx\n",
		   which, VL_STATUS_CLEAR_TIMEOUT, mask, reg);
	/*
	 * If this occurs, it is likely there was a credit loss on the link.
	 * The only recovery from that is a link bounce.
	 */
	dd_dev_err(dd,
		   "Continuing anyway.  A credit loss may occur.  Suggest a link bounce\n");
पूर्ण

/*
 * The number of credits on the VLs may be changed जबतक everything
 * is "live", but the following algorithm must be followed due to
 * how the hardware is actually implemented.  In particular,
 * Return_Credit_Status[] is the only correct status check.
 *
 * अगर (reducing Global_Shared_Credit_Limit or any shared limit changing)
 *     set Global_Shared_Credit_Limit = 0
 *     use_all_vl = 1
 * mask0 = all VLs that are changing either dedicated or shared limits
 * set Shared_Limit[mask0] = 0
 * spin until Return_Credit_Status[use_all_vl ? all VL : mask0] == 0
 * अगर (changing any dedicated limit)
 *     mask1 = all VLs that are lowering dedicated limits
 *     lower Dedicated_Limit[mask1]
 *     spin until Return_Credit_Status[mask1] == 0
 *     उठाओ Dedicated_Limits
 * उठाओ Shared_Limits
 * उठाओ Global_Shared_Credit_Limit
 *
 * lower = अगर the new limit is lower, set the limit to the new value
 * उठाओ = अगर the new limit is higher than the current value (may be changed
 *	earlier in the algorithm), set the new limit to the new value
 */
पूर्णांक set_buffer_control(काष्ठा hfi1_pportdata *ppd,
		       काष्ठा buffer_control *new_bc)
अणु
	काष्ठा hfi1_devdata *dd = ppd->dd;
	u64 changing_mask, ld_mask, stat_mask;
	पूर्णांक change_count;
	पूर्णांक i, use_all_mask;
	पूर्णांक this_shared_changing;
	पूर्णांक vl_count = 0, ret;
	/*
	 * A0: add the variable any_shared_limit_changing below and in the
	 * algorithm above.  If removing A0 support, it can be हटाओd.
	 */
	पूर्णांक any_shared_limit_changing;
	काष्ठा buffer_control cur_bc;
	u8 changing[OPA_MAX_VLS];
	u8 lowering_dedicated[OPA_MAX_VLS];
	u16 cur_total;
	u32 new_total = 0;
	स्थिर u64 all_mask =
	SEND_CM_CREDIT_USED_STATUS_VL0_RETURN_CREDIT_STATUS_SMASK
	 | SEND_CM_CREDIT_USED_STATUS_VL1_RETURN_CREDIT_STATUS_SMASK
	 | SEND_CM_CREDIT_USED_STATUS_VL2_RETURN_CREDIT_STATUS_SMASK
	 | SEND_CM_CREDIT_USED_STATUS_VL3_RETURN_CREDIT_STATUS_SMASK
	 | SEND_CM_CREDIT_USED_STATUS_VL4_RETURN_CREDIT_STATUS_SMASK
	 | SEND_CM_CREDIT_USED_STATUS_VL5_RETURN_CREDIT_STATUS_SMASK
	 | SEND_CM_CREDIT_USED_STATUS_VL6_RETURN_CREDIT_STATUS_SMASK
	 | SEND_CM_CREDIT_USED_STATUS_VL7_RETURN_CREDIT_STATUS_SMASK
	 | SEND_CM_CREDIT_USED_STATUS_VL15_RETURN_CREDIT_STATUS_SMASK;

#घोषणा valid_vl(idx) ((idx) < TXE_NUM_DATA_VL || (idx) == 15)
#घोषणा NUM_USABLE_VLS 16	/* look at VL15 and less */

	/* find the new total credits, करो sanity check on unused VLs */
	क्रम (i = 0; i < OPA_MAX_VLS; i++) अणु
		अगर (valid_vl(i)) अणु
			new_total += be16_to_cpu(new_bc->vl[i].dedicated);
			जारी;
		पूर्ण
		nonzero_msg(dd, i, "dedicated",
			    be16_to_cpu(new_bc->vl[i].dedicated));
		nonzero_msg(dd, i, "shared",
			    be16_to_cpu(new_bc->vl[i].shared));
		new_bc->vl[i].dedicated = 0;
		new_bc->vl[i].shared = 0;
	पूर्ण
	new_total += be16_to_cpu(new_bc->overall_shared_limit);

	/* fetch the current values */
	get_buffer_control(dd, &cur_bc, &cur_total);

	/*
	 * Create the masks we will use.
	 */
	स_रखो(changing, 0, माप(changing));
	स_रखो(lowering_dedicated, 0, माप(lowering_dedicated));
	/*
	 * NOTE: Assumes that the inभागidual VL bits are adjacent and in
	 * increasing order
	 */
	stat_mask =
		SEND_CM_CREDIT_USED_STATUS_VL0_RETURN_CREDIT_STATUS_SMASK;
	changing_mask = 0;
	ld_mask = 0;
	change_count = 0;
	any_shared_limit_changing = 0;
	क्रम (i = 0; i < NUM_USABLE_VLS; i++, stat_mask <<= 1) अणु
		अगर (!valid_vl(i))
			जारी;
		this_shared_changing = new_bc->vl[i].shared
						!= cur_bc.vl[i].shared;
		अगर (this_shared_changing)
			any_shared_limit_changing = 1;
		अगर (new_bc->vl[i].dedicated != cur_bc.vl[i].dedicated ||
		    this_shared_changing) अणु
			changing[i] = 1;
			changing_mask |= stat_mask;
			change_count++;
		पूर्ण
		अगर (be16_to_cpu(new_bc->vl[i].dedicated) <
					be16_to_cpu(cur_bc.vl[i].dedicated)) अणु
			lowering_dedicated[i] = 1;
			ld_mask |= stat_mask;
		पूर्ण
	पूर्ण

	/* bracket the credit change with a total adjusपंचांगent */
	अगर (new_total > cur_total)
		set_global_limit(dd, new_total);

	/*
	 * Start the credit change algorithm.
	 */
	use_all_mask = 0;
	अगर ((be16_to_cpu(new_bc->overall_shared_limit) <
	     be16_to_cpu(cur_bc.overall_shared_limit)) ||
	    (is_ax(dd) && any_shared_limit_changing)) अणु
		set_global_shared(dd, 0);
		cur_bc.overall_shared_limit = 0;
		use_all_mask = 1;
	पूर्ण

	क्रम (i = 0; i < NUM_USABLE_VLS; i++) अणु
		अगर (!valid_vl(i))
			जारी;

		अगर (changing[i]) अणु
			set_vl_shared(dd, i, 0);
			cur_bc.vl[i].shared = 0;
		पूर्ण
	पूर्ण

	रुको_क्रम_vl_status_clear(dd, use_all_mask ? all_mask : changing_mask,
				 "shared");

	अगर (change_count > 0) अणु
		क्रम (i = 0; i < NUM_USABLE_VLS; i++) अणु
			अगर (!valid_vl(i))
				जारी;

			अगर (lowering_dedicated[i]) अणु
				set_vl_dedicated(dd, i,
						 be16_to_cpu(new_bc->
							     vl[i].dedicated));
				cur_bc.vl[i].dedicated =
						new_bc->vl[i].dedicated;
			पूर्ण
		पूर्ण

		रुको_क्रम_vl_status_clear(dd, ld_mask, "dedicated");

		/* now उठाओ all dedicated that are going up */
		क्रम (i = 0; i < NUM_USABLE_VLS; i++) अणु
			अगर (!valid_vl(i))
				जारी;

			अगर (be16_to_cpu(new_bc->vl[i].dedicated) >
					be16_to_cpu(cur_bc.vl[i].dedicated))
				set_vl_dedicated(dd, i,
						 be16_to_cpu(new_bc->
							     vl[i].dedicated));
		पूर्ण
	पूर्ण

	/* next उठाओ all shared that are going up */
	क्रम (i = 0; i < NUM_USABLE_VLS; i++) अणु
		अगर (!valid_vl(i))
			जारी;

		अगर (be16_to_cpu(new_bc->vl[i].shared) >
				be16_to_cpu(cur_bc.vl[i].shared))
			set_vl_shared(dd, i, be16_to_cpu(new_bc->vl[i].shared));
	पूर्ण

	/* finally उठाओ the global shared */
	अगर (be16_to_cpu(new_bc->overall_shared_limit) >
	    be16_to_cpu(cur_bc.overall_shared_limit))
		set_global_shared(dd,
				  be16_to_cpu(new_bc->overall_shared_limit));

	/* bracket the credit change with a total adjusपंचांगent */
	अगर (new_total < cur_total)
		set_global_limit(dd, new_total);

	/*
	 * Determine the actual number of operational VLS using the number of
	 * dedicated and shared credits क्रम each VL.
	 */
	अगर (change_count > 0) अणु
		क्रम (i = 0; i < TXE_NUM_DATA_VL; i++)
			अगर (be16_to_cpu(new_bc->vl[i].dedicated) > 0 ||
			    be16_to_cpu(new_bc->vl[i].shared) > 0)
				vl_count++;
		ppd->actual_vls_operational = vl_count;
		ret = sdma_map_init(dd, ppd->port - 1, vl_count ?
				    ppd->actual_vls_operational :
				    ppd->vls_operational,
				    शून्य);
		अगर (ret == 0)
			ret = pio_map_init(dd, ppd->port - 1, vl_count ?
					   ppd->actual_vls_operational :
					   ppd->vls_operational, शून्य);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Read the given fabric manager table. Return the size of the
 * table (in bytes) on success, and a negative error code on
 * failure.
 */
पूर्णांक fm_get_table(काष्ठा hfi1_pportdata *ppd, पूर्णांक which, व्योम *t)

अणु
	पूर्णांक size;
	काष्ठा vl_arb_cache *vlc;

	चयन (which) अणु
	हाल FM_TBL_VL_HIGH_ARB:
		size = 256;
		/*
		 * OPA specअगरies 128 elements (of 2 bytes each), though
		 * HFI supports only 16 elements in h/w.
		 */
		vlc = vl_arb_lock_cache(ppd, HI_PRIO_TABLE);
		vl_arb_get_cache(vlc, t);
		vl_arb_unlock_cache(ppd, HI_PRIO_TABLE);
		अवरोध;
	हाल FM_TBL_VL_LOW_ARB:
		size = 256;
		/*
		 * OPA specअगरies 128 elements (of 2 bytes each), though
		 * HFI supports only 16 elements in h/w.
		 */
		vlc = vl_arb_lock_cache(ppd, LO_PRIO_TABLE);
		vl_arb_get_cache(vlc, t);
		vl_arb_unlock_cache(ppd, LO_PRIO_TABLE);
		अवरोध;
	हाल FM_TBL_BUFFER_CONTROL:
		size = get_buffer_control(ppd->dd, t, शून्य);
		अवरोध;
	हाल FM_TBL_SC2VLNT:
		size = get_sc2vlnt(ppd->dd, t);
		अवरोध;
	हाल FM_TBL_VL_PREEMPT_ELEMS:
		size = 256;
		/* OPA specअगरies 128 elements, of 2 bytes each */
		get_vlarb_preempt(ppd->dd, OPA_MAX_VLS, t);
		अवरोध;
	हाल FM_TBL_VL_PREEMPT_MATRIX:
		size = 256;
		/*
		 * OPA specअगरies that this is the same size as the VL
		 * arbitration tables (i.e., 256 bytes).
		 */
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस size;
पूर्ण

/*
 * Write the given fabric manager table.
 */
पूर्णांक fm_set_table(काष्ठा hfi1_pportdata *ppd, पूर्णांक which, व्योम *t)
अणु
	पूर्णांक ret = 0;
	काष्ठा vl_arb_cache *vlc;

	चयन (which) अणु
	हाल FM_TBL_VL_HIGH_ARB:
		vlc = vl_arb_lock_cache(ppd, HI_PRIO_TABLE);
		अगर (vl_arb_match_cache(vlc, t)) अणु
			vl_arb_unlock_cache(ppd, HI_PRIO_TABLE);
			अवरोध;
		पूर्ण
		vl_arb_set_cache(vlc, t);
		vl_arb_unlock_cache(ppd, HI_PRIO_TABLE);
		ret = set_vl_weights(ppd, SEND_HIGH_PRIORITY_LIST,
				     VL_ARB_HIGH_PRIO_TABLE_SIZE, t);
		अवरोध;
	हाल FM_TBL_VL_LOW_ARB:
		vlc = vl_arb_lock_cache(ppd, LO_PRIO_TABLE);
		अगर (vl_arb_match_cache(vlc, t)) अणु
			vl_arb_unlock_cache(ppd, LO_PRIO_TABLE);
			अवरोध;
		पूर्ण
		vl_arb_set_cache(vlc, t);
		vl_arb_unlock_cache(ppd, LO_PRIO_TABLE);
		ret = set_vl_weights(ppd, SEND_LOW_PRIORITY_LIST,
				     VL_ARB_LOW_PRIO_TABLE_SIZE, t);
		अवरोध;
	हाल FM_TBL_BUFFER_CONTROL:
		ret = set_buffer_control(ppd, t);
		अवरोध;
	हाल FM_TBL_SC2VLNT:
		set_sc2vlnt(ppd->dd, t);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Disable all data VLs.
 *
 * Return 0 अगर disabled, non-zero अगर the VLs cannot be disabled.
 */
अटल पूर्णांक disable_data_vls(काष्ठा hfi1_devdata *dd)
अणु
	अगर (is_ax(dd))
		वापस 1;

	pio_send_control(dd, PSC_DATA_VL_DISABLE);

	वापस 0;
पूर्ण

/*
 * खोलो_fill_data_vls() - the counterpart to stop_drain_data_vls().
 * Just re-enables all data VLs (the "fill" part happens
 * स्वतःmatically - the name was chosen क्रम symmetry with
 * stop_drain_data_vls()).
 *
 * Return 0 अगर successful, non-zero अगर the VLs cannot be enabled.
 */
पूर्णांक खोलो_fill_data_vls(काष्ठा hfi1_devdata *dd)
अणु
	अगर (is_ax(dd))
		वापस 1;

	pio_send_control(dd, PSC_DATA_VL_ENABLE);

	वापस 0;
पूर्ण

/*
 * drain_data_vls() - assumes that disable_data_vls() has been called,
 * रुको क्रम occupancy (of per-VL FIFOs) क्रम all contexts, and SDMA
 * engines to drop to 0.
 */
अटल व्योम drain_data_vls(काष्ठा hfi1_devdata *dd)
अणु
	sc_रुको(dd);
	sdma_रुको(dd);
	छोड़ो_क्रम_credit_वापस(dd);
पूर्ण

/*
 * stop_drain_data_vls() - disable, then drain all per-VL fअगरos.
 *
 * Use खोलो_fill_data_vls() to resume using data VLs.  This pair is
 * meant to be used like this:
 *
 * stop_drain_data_vls(dd);
 * // करो things with per-VL resources
 * खोलो_fill_data_vls(dd);
 */
पूर्णांक stop_drain_data_vls(काष्ठा hfi1_devdata *dd)
अणु
	पूर्णांक ret;

	ret = disable_data_vls(dd);
	अगर (ret == 0)
		drain_data_vls(dd);

	वापस ret;
पूर्ण

/*
 * Convert a nanosecond समय to a cघड़ी count.  No matter how slow
 * the cघड़ी, a non-zero ns will always have a non-zero result.
 */
u32 ns_to_cघड़ी(काष्ठा hfi1_devdata *dd, u32 ns)
अणु
	u32 cघड़ीs;

	अगर (dd->icode == ICODE_FPGA_EMULATION)
		cघड़ीs = (ns * 1000) / FPGA_CCLOCK_PS;
	अन्यथा  /* simulation pretends to be ASIC */
		cघड़ीs = (ns * 1000) / ASIC_CCLOCK_PS;
	अगर (ns && !cघड़ीs)	/* अगर ns nonzero, must be at least 1 */
		cघड़ीs = 1;
	वापस cघड़ीs;
पूर्ण

/*
 * Convert a cघड़ी count to nanoseconds. Not matter how slow
 * the cघड़ी, a non-zero cघड़ीs will always have a non-zero result.
 */
u32 cघड़ी_प्रकारo_ns(काष्ठा hfi1_devdata *dd, u32 cघड़ीs)
अणु
	u32 ns;

	अगर (dd->icode == ICODE_FPGA_EMULATION)
		ns = (cघड़ीs * FPGA_CCLOCK_PS) / 1000;
	अन्यथा  /* simulation pretends to be ASIC */
		ns = (cघड़ीs * ASIC_CCLOCK_PS) / 1000;
	अगर (cघड़ीs && !ns)
		ns = 1;
	वापस ns;
पूर्ण

/*
 * Dynamically adjust the receive पूर्णांकerrupt समयout क्रम a context based on
 * incoming packet rate.
 *
 * NOTE: Dynamic adjusपंचांगent करोes not allow rcv_पूर्णांकr_count to be zero.
 */
अटल व्योम adjust_rcv_समयout(काष्ठा hfi1_ctxtdata *rcd, u32 npkts)
अणु
	काष्ठा hfi1_devdata *dd = rcd->dd;
	u32 समयout = rcd->rcvavail_समयout;

	/*
	 * This algorithm द्विगुनs or halves the समयout depending on whether
	 * the number of packets received in this पूर्णांकerrupt were less than or
	 * greater equal the पूर्णांकerrupt count.
	 *
	 * The calculations below करो not allow a steady state to be achieved.
	 * Only at the endpoपूर्णांकs it is possible to have an unchanging
	 * समयout.
	 */
	अगर (npkts < rcv_पूर्णांकr_count) अणु
		/*
		 * Not enough packets arrived beक्रमe the समयout, adjust
		 * समयout करोwnward.
		 */
		अगर (समयout < 2) /* alपढ़ोy at minimum? */
			वापस;
		समयout >>= 1;
	पूर्ण अन्यथा अणु
		/*
		 * More than enough packets arrived beक्रमe the समयout, adjust
		 * समयout upward.
		 */
		अगर (समयout >= dd->rcv_पूर्णांकr_समयout_csr) /* alपढ़ोy at max? */
			वापस;
		समयout = min(समयout << 1, dd->rcv_पूर्णांकr_समयout_csr);
	पूर्ण

	rcd->rcvavail_समयout = समयout;
	/*
	 * समयout cannot be larger than rcv_पूर्णांकr_समयout_csr which has alपढ़ोy
	 * been verअगरied to be in range
	 */
	ग_लिखो_kctxt_csr(dd, rcd->ctxt, RCV_AVAIL_TIME_OUT,
			(u64)समयout <<
			RCV_AVAIL_TIME_OUT_TIME_OUT_RELOAD_SHIFT);
पूर्ण

व्योम update_usrhead(काष्ठा hfi1_ctxtdata *rcd, u32 hd, u32 updegr, u32 egrhd,
		    u32 पूर्णांकr_adjust, u32 npkts)
अणु
	काष्ठा hfi1_devdata *dd = rcd->dd;
	u64 reg;
	u32 ctxt = rcd->ctxt;

	/*
	 * Need to ग_लिखो समयout रेजिस्टर beक्रमe updating RcvHdrHead to ensure
	 * that a new value is used when the HW decides to restart counting.
	 */
	अगर (पूर्णांकr_adjust)
		adjust_rcv_समयout(rcd, npkts);
	अगर (updegr) अणु
		reg = (egrhd & RCV_EGR_INDEX_HEAD_HEAD_MASK)
			<< RCV_EGR_INDEX_HEAD_HEAD_SHIFT;
		ग_लिखो_uctxt_csr(dd, ctxt, RCV_EGR_INDEX_HEAD, reg);
	पूर्ण
	reg = ((u64)rcv_पूर्णांकr_count << RCV_HDR_HEAD_COUNTER_SHIFT) |
		(((u64)hd & RCV_HDR_HEAD_HEAD_MASK)
			<< RCV_HDR_HEAD_HEAD_SHIFT);
	ग_लिखो_uctxt_csr(dd, ctxt, RCV_HDR_HEAD, reg);
पूर्ण

u32 hdrqempty(काष्ठा hfi1_ctxtdata *rcd)
अणु
	u32 head, tail;

	head = (पढ़ो_uctxt_csr(rcd->dd, rcd->ctxt, RCV_HDR_HEAD)
		& RCV_HDR_HEAD_HEAD_SMASK) >> RCV_HDR_HEAD_HEAD_SHIFT;

	अगर (hfi1_rcvhdrtail_kvaddr(rcd))
		tail = get_rcvhdrtail(rcd);
	अन्यथा
		tail = पढ़ो_uctxt_csr(rcd->dd, rcd->ctxt, RCV_HDR_TAIL);

	वापस head == tail;
पूर्ण

/*
 * Context Control and Receive Array encoding क्रम buffer size:
 *	0x0 invalid
 *	0x1   4 KB
 *	0x2   8 KB
 *	0x3  16 KB
 *	0x4  32 KB
 *	0x5  64 KB
 *	0x6 128 KB
 *	0x7 256 KB
 *	0x8 512 KB (Receive Array only)
 *	0x9   1 MB (Receive Array only)
 *	0xa   2 MB (Receive Array only)
 *
 *	0xB-0xF - reserved (Receive Array only)
 *
 *
 * This routine assumes that the value has alपढ़ोy been sanity checked.
 */
अटल u32 encoded_size(u32 size)
अणु
	चयन (size) अणु
	हाल   4 * 1024: वापस 0x1;
	हाल   8 * 1024: वापस 0x2;
	हाल  16 * 1024: वापस 0x3;
	हाल  32 * 1024: वापस 0x4;
	हाल  64 * 1024: वापस 0x5;
	हाल 128 * 1024: वापस 0x6;
	हाल 256 * 1024: वापस 0x7;
	हाल 512 * 1024: वापस 0x8;
	हाल   1 * 1024 * 1024: वापस 0x9;
	हाल   2 * 1024 * 1024: वापस 0xa;
	पूर्ण
	वापस 0x1;	/* अगर invalid, go with the minimum size */
पूर्ण

/**
 * encode_rcv_header_entry_size - वापस chip specअगरic encoding क्रम size
 * @size: size in dwords
 *
 * Convert a receive header entry size that to the encoding used in the CSR.
 *
 * Return a zero अगर the given size is invalid, otherwise the encoding.
 */
u8 encode_rcv_header_entry_size(u8 size)
अणु
	/* there are only 3 valid receive header entry sizes */
	अगर (size == 2)
		वापस 1;
	अगर (size == 16)
		वापस 2;
	अगर (size == 32)
		वापस 4;
	वापस 0; /* invalid */
पूर्ण

/**
 * hfi1_validate_rcvhdrcnt - validate hdrcnt
 * @dd: the device data
 * @thecnt: the header count
 */
पूर्णांक hfi1_validate_rcvhdrcnt(काष्ठा hfi1_devdata *dd, uपूर्णांक thecnt)
अणु
	अगर (thecnt <= HFI1_MIN_HDRQ_EGRBUF_CNT) अणु
		dd_dev_err(dd, "Receive header queue count too small\n");
		वापस -EINVAL;
	पूर्ण

	अगर (thecnt > HFI1_MAX_HDRQ_EGRBUF_CNT) अणु
		dd_dev_err(dd,
			   "Receive header queue count cannot be greater than %u\n",
			   HFI1_MAX_HDRQ_EGRBUF_CNT);
		वापस -EINVAL;
	पूर्ण

	अगर (thecnt % HDRQ_INCREMENT) अणु
		dd_dev_err(dd, "Receive header queue count %d must be divisible by %lu\n",
			   thecnt, HDRQ_INCREMENT);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * set_hdrq_regs - set header queue रेजिस्टरs क्रम context
 * @dd: the device data
 * @ctxt: the context
 * @entsize: the dword entry size
 * @hdrcnt: the number of header entries
 */
व्योम set_hdrq_regs(काष्ठा hfi1_devdata *dd, u8 ctxt, u8 entsize, u16 hdrcnt)
अणु
	u64 reg;

	reg = (((u64)hdrcnt >> HDRQ_SIZE_SHIFT) & RCV_HDR_CNT_CNT_MASK) <<
	      RCV_HDR_CNT_CNT_SHIFT;
	ग_लिखो_kctxt_csr(dd, ctxt, RCV_HDR_CNT, reg);
	reg = ((u64)encode_rcv_header_entry_size(entsize) &
	       RCV_HDR_ENT_SIZE_ENT_SIZE_MASK) <<
	      RCV_HDR_ENT_SIZE_ENT_SIZE_SHIFT;
	ग_लिखो_kctxt_csr(dd, ctxt, RCV_HDR_ENT_SIZE, reg);
	reg = ((u64)DEFAULT_RCVHDRSIZE & RCV_HDR_SIZE_HDR_SIZE_MASK) <<
	      RCV_HDR_SIZE_HDR_SIZE_SHIFT;
	ग_लिखो_kctxt_csr(dd, ctxt, RCV_HDR_SIZE, reg);

	/*
	 * Program dummy tail address क्रम every receive context
	 * beक्रमe enabling any receive context
	 */
	ग_लिखो_kctxt_csr(dd, ctxt, RCV_HDR_TAIL_ADDR,
			dd->rcvhdrtail_dummy_dma);
पूर्ण

व्योम hfi1_rcvctrl(काष्ठा hfi1_devdata *dd, अचिन्हित पूर्णांक op,
		  काष्ठा hfi1_ctxtdata *rcd)
अणु
	u64 rcvctrl, reg;
	पूर्णांक did_enable = 0;
	u16 ctxt;

	अगर (!rcd)
		वापस;

	ctxt = rcd->ctxt;

	hfi1_cdbg(RCVCTRL, "ctxt %d op 0x%x", ctxt, op);

	rcvctrl = पढ़ो_kctxt_csr(dd, ctxt, RCV_CTXT_CTRL);
	/* अगर the context alपढ़ोy enabled, करोn't करो the extra steps */
	अगर ((op & HFI1_RCVCTRL_CTXT_ENB) &&
	    !(rcvctrl & RCV_CTXT_CTRL_ENABLE_SMASK)) अणु
		/* reset the tail and hdr addresses, and sequence count */
		ग_लिखो_kctxt_csr(dd, ctxt, RCV_HDR_ADDR,
				rcd->rcvhdrq_dma);
		अगर (hfi1_rcvhdrtail_kvaddr(rcd))
			ग_लिखो_kctxt_csr(dd, ctxt, RCV_HDR_TAIL_ADDR,
					rcd->rcvhdrqtailaddr_dma);
		hfi1_set_seq_cnt(rcd, 1);

		/* reset the cached receive header queue head value */
		hfi1_set_rcd_head(rcd, 0);

		/*
		 * Zero the receive header queue so we करोn't get false
		 * positives when checking the sequence number.  The
		 * sequence numbers could land exactly on the same spot.
		 * E.g. a rcd restart beक्रमe the receive header wrapped.
		 */
		स_रखो(rcd->rcvhdrq, 0, rcvhdrq_size(rcd));

		/* starting समयout */
		rcd->rcvavail_समयout = dd->rcv_पूर्णांकr_समयout_csr;

		/* enable the context */
		rcvctrl |= RCV_CTXT_CTRL_ENABLE_SMASK;

		/* clean the egr buffer size first */
		rcvctrl &= ~RCV_CTXT_CTRL_EGR_BUF_SIZE_SMASK;
		rcvctrl |= ((u64)encoded_size(rcd->egrbufs.rcvtid_size)
				& RCV_CTXT_CTRL_EGR_BUF_SIZE_MASK)
					<< RCV_CTXT_CTRL_EGR_BUF_SIZE_SHIFT;

		/* zero RcvHdrHead - set RcvHdrHead.Counter after enable */
		ग_लिखो_uctxt_csr(dd, ctxt, RCV_HDR_HEAD, 0);
		did_enable = 1;

		/* zero RcvEgrIndexHead */
		ग_लिखो_uctxt_csr(dd, ctxt, RCV_EGR_INDEX_HEAD, 0);

		/* set eager count and base index */
		reg = (((u64)(rcd->egrbufs.alloced >> RCV_SHIFT)
			& RCV_EGR_CTRL_EGR_CNT_MASK)
		       << RCV_EGR_CTRL_EGR_CNT_SHIFT) |
			(((rcd->eager_base >> RCV_SHIFT)
			  & RCV_EGR_CTRL_EGR_BASE_INDEX_MASK)
			 << RCV_EGR_CTRL_EGR_BASE_INDEX_SHIFT);
		ग_लिखो_kctxt_csr(dd, ctxt, RCV_EGR_CTRL, reg);

		/*
		 * Set TID (expected) count and base index.
		 * rcd->expected_count is set to inभागidual RcvArray entries,
		 * not pairs, and the CSR takes a pair-count in groups of
		 * four, so भागide by 8.
		 */
		reg = (((rcd->expected_count >> RCV_SHIFT)
					& RCV_TID_CTRL_TID_PAIR_CNT_MASK)
				<< RCV_TID_CTRL_TID_PAIR_CNT_SHIFT) |
		      (((rcd->expected_base >> RCV_SHIFT)
					& RCV_TID_CTRL_TID_BASE_INDEX_MASK)
				<< RCV_TID_CTRL_TID_BASE_INDEX_SHIFT);
		ग_लिखो_kctxt_csr(dd, ctxt, RCV_TID_CTRL, reg);
		अगर (ctxt == HFI1_CTRL_CTXT)
			ग_लिखो_csr(dd, RCV_VL15, HFI1_CTRL_CTXT);
	पूर्ण
	अगर (op & HFI1_RCVCTRL_CTXT_DIS) अणु
		ग_लिखो_csr(dd, RCV_VL15, 0);
		/*
		 * When receive context is being disabled turn on tail
		 * update with a dummy tail address and then disable
		 * receive context.
		 */
		अगर (dd->rcvhdrtail_dummy_dma) अणु
			ग_लिखो_kctxt_csr(dd, ctxt, RCV_HDR_TAIL_ADDR,
					dd->rcvhdrtail_dummy_dma);
			/* Enabling RcvCtxtCtrl.TailUpd is पूर्णांकentional. */
			rcvctrl |= RCV_CTXT_CTRL_TAIL_UPD_SMASK;
		पूर्ण

		rcvctrl &= ~RCV_CTXT_CTRL_ENABLE_SMASK;
	पूर्ण
	अगर (op & HFI1_RCVCTRL_INTRAVAIL_ENB) अणु
		set_पूर्णांकr_bits(dd, IS_RCVAVAIL_START + rcd->ctxt,
			      IS_RCVAVAIL_START + rcd->ctxt, true);
		rcvctrl |= RCV_CTXT_CTRL_INTR_AVAIL_SMASK;
	पूर्ण
	अगर (op & HFI1_RCVCTRL_INTRAVAIL_DIS) अणु
		set_पूर्णांकr_bits(dd, IS_RCVAVAIL_START + rcd->ctxt,
			      IS_RCVAVAIL_START + rcd->ctxt, false);
		rcvctrl &= ~RCV_CTXT_CTRL_INTR_AVAIL_SMASK;
	पूर्ण
	अगर ((op & HFI1_RCVCTRL_TAILUPD_ENB) && hfi1_rcvhdrtail_kvaddr(rcd))
		rcvctrl |= RCV_CTXT_CTRL_TAIL_UPD_SMASK;
	अगर (op & HFI1_RCVCTRL_TAILUPD_DIS) अणु
		/* See comment on RcvCtxtCtrl.TailUpd above */
		अगर (!(op & HFI1_RCVCTRL_CTXT_DIS))
			rcvctrl &= ~RCV_CTXT_CTRL_TAIL_UPD_SMASK;
	पूर्ण
	अगर (op & HFI1_RCVCTRL_TIDFLOW_ENB)
		rcvctrl |= RCV_CTXT_CTRL_TID_FLOW_ENABLE_SMASK;
	अगर (op & HFI1_RCVCTRL_TIDFLOW_DIS)
		rcvctrl &= ~RCV_CTXT_CTRL_TID_FLOW_ENABLE_SMASK;
	अगर (op & HFI1_RCVCTRL_ONE_PKT_EGR_ENB) अणु
		/*
		 * In one-packet-per-eager mode, the size comes from
		 * the RcvArray entry.
		 */
		rcvctrl &= ~RCV_CTXT_CTRL_EGR_BUF_SIZE_SMASK;
		rcvctrl |= RCV_CTXT_CTRL_ONE_PACKET_PER_EGR_BUFFER_SMASK;
	पूर्ण
	अगर (op & HFI1_RCVCTRL_ONE_PKT_EGR_DIS)
		rcvctrl &= ~RCV_CTXT_CTRL_ONE_PACKET_PER_EGR_BUFFER_SMASK;
	अगर (op & HFI1_RCVCTRL_NO_RHQ_DROP_ENB)
		rcvctrl |= RCV_CTXT_CTRL_DONT_DROP_RHQ_FULL_SMASK;
	अगर (op & HFI1_RCVCTRL_NO_RHQ_DROP_DIS)
		rcvctrl &= ~RCV_CTXT_CTRL_DONT_DROP_RHQ_FULL_SMASK;
	अगर (op & HFI1_RCVCTRL_NO_EGR_DROP_ENB)
		rcvctrl |= RCV_CTXT_CTRL_DONT_DROP_EGR_FULL_SMASK;
	अगर (op & HFI1_RCVCTRL_NO_EGR_DROP_DIS)
		rcvctrl &= ~RCV_CTXT_CTRL_DONT_DROP_EGR_FULL_SMASK;
	अगर (op & HFI1_RCVCTRL_URGENT_ENB)
		set_पूर्णांकr_bits(dd, IS_RCVURGENT_START + rcd->ctxt,
			      IS_RCVURGENT_START + rcd->ctxt, true);
	अगर (op & HFI1_RCVCTRL_URGENT_DIS)
		set_पूर्णांकr_bits(dd, IS_RCVURGENT_START + rcd->ctxt,
			      IS_RCVURGENT_START + rcd->ctxt, false);

	hfi1_cdbg(RCVCTRL, "ctxt %d rcvctrl 0x%llx\n", ctxt, rcvctrl);
	ग_लिखो_kctxt_csr(dd, ctxt, RCV_CTXT_CTRL, rcvctrl);

	/* work around sticky RcvCtxtStatus.BlockedRHQFull */
	अगर (did_enable &&
	    (rcvctrl & RCV_CTXT_CTRL_DONT_DROP_RHQ_FULL_SMASK)) अणु
		reg = पढ़ो_kctxt_csr(dd, ctxt, RCV_CTXT_STATUS);
		अगर (reg != 0) अणु
			dd_dev_info(dd, "ctxt %d status %lld (blocked)\n",
				    ctxt, reg);
			पढ़ो_uctxt_csr(dd, ctxt, RCV_HDR_HEAD);
			ग_लिखो_uctxt_csr(dd, ctxt, RCV_HDR_HEAD, 0x10);
			ग_लिखो_uctxt_csr(dd, ctxt, RCV_HDR_HEAD, 0x00);
			पढ़ो_uctxt_csr(dd, ctxt, RCV_HDR_HEAD);
			reg = पढ़ो_kctxt_csr(dd, ctxt, RCV_CTXT_STATUS);
			dd_dev_info(dd, "ctxt %d status %lld (%s blocked)\n",
				    ctxt, reg, reg == 0 ? "not" : "still");
		पूर्ण
	पूर्ण

	अगर (did_enable) अणु
		/*
		 * The पूर्णांकerrupt समयout and count must be set after
		 * the context is enabled to take effect.
		 */
		/* set पूर्णांकerrupt समयout */
		ग_लिखो_kctxt_csr(dd, ctxt, RCV_AVAIL_TIME_OUT,
				(u64)rcd->rcvavail_समयout <<
				RCV_AVAIL_TIME_OUT_TIME_OUT_RELOAD_SHIFT);

		/* set RcvHdrHead.Counter, zero RcvHdrHead.Head (again) */
		reg = (u64)rcv_पूर्णांकr_count << RCV_HDR_HEAD_COUNTER_SHIFT;
		ग_लिखो_uctxt_csr(dd, ctxt, RCV_HDR_HEAD, reg);
	पूर्ण

	अगर (op & (HFI1_RCVCTRL_TAILUPD_DIS | HFI1_RCVCTRL_CTXT_DIS))
		/*
		 * If the context has been disabled and the Tail Update has
		 * been cleared, set the RCV_HDR_TAIL_ADDR CSR to dummy address
		 * so it करोesn't contain an address that is invalid.
		 */
		ग_लिखो_kctxt_csr(dd, ctxt, RCV_HDR_TAIL_ADDR,
				dd->rcvhdrtail_dummy_dma);
पूर्ण

u32 hfi1_पढ़ो_cntrs(काष्ठा hfi1_devdata *dd, अक्षर **namep, u64 **cntrp)
अणु
	पूर्णांक ret;
	u64 val = 0;

	अगर (namep) अणु
		ret = dd->cntrnameslen;
		*namep = dd->cntrnames;
	पूर्ण अन्यथा अणु
		स्थिर काष्ठा cntr_entry *entry;
		पूर्णांक i, j;

		ret = (dd->ndevcntrs) * माप(u64);

		/* Get the start of the block of counters */
		*cntrp = dd->cntrs;

		/*
		 * Now go and fill in each counter in the block.
		 */
		क्रम (i = 0; i < DEV_CNTR_LAST; i++) अणु
			entry = &dev_cntrs[i];
			hfi1_cdbg(CNTR, "reading %s", entry->name);
			अगर (entry->flags & CNTR_DISABLED) अणु
				/* Nothing */
				hfi1_cdbg(CNTR, "\tDisabled\n");
			पूर्ण अन्यथा अणु
				अगर (entry->flags & CNTR_VL) अणु
					hfi1_cdbg(CNTR, "\tPer VL\n");
					क्रम (j = 0; j < C_VL_COUNT; j++) अणु
						val = entry->rw_cntr(entry,
								  dd, j,
								  CNTR_MODE_R,
								  0);
						hfi1_cdbg(
						   CNTR,
						   "\t\tRead 0x%llx for %d\n",
						   val, j);
						dd->cntrs[entry->offset + j] =
									    val;
					पूर्ण
				पूर्ण अन्यथा अगर (entry->flags & CNTR_SDMA) अणु
					hfi1_cdbg(CNTR,
						  "\t Per SDMA Engine\n");
					क्रम (j = 0; j < chip_sdma_engines(dd);
					     j++) अणु
						val =
						entry->rw_cntr(entry, dd, j,
							       CNTR_MODE_R, 0);
						hfi1_cdbg(CNTR,
							  "\t\tRead 0x%llx for %d\n",
							  val, j);
						dd->cntrs[entry->offset + j] =
									val;
					पूर्ण
				पूर्ण अन्यथा अणु
					val = entry->rw_cntr(entry, dd,
							CNTR_INVALID_VL,
							CNTR_MODE_R, 0);
					dd->cntrs[entry->offset] = val;
					hfi1_cdbg(CNTR, "\tRead 0x%llx", val);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Used by sysfs to create files क्रम hfi stats to पढ़ो
 */
u32 hfi1_पढ़ो_portcntrs(काष्ठा hfi1_pportdata *ppd, अक्षर **namep, u64 **cntrp)
अणु
	पूर्णांक ret;
	u64 val = 0;

	अगर (namep) अणु
		ret = ppd->dd->portcntrnameslen;
		*namep = ppd->dd->portcntrnames;
	पूर्ण अन्यथा अणु
		स्थिर काष्ठा cntr_entry *entry;
		पूर्णांक i, j;

		ret = ppd->dd->nportcntrs * माप(u64);
		*cntrp = ppd->cntrs;

		क्रम (i = 0; i < PORT_CNTR_LAST; i++) अणु
			entry = &port_cntrs[i];
			hfi1_cdbg(CNTR, "reading %s", entry->name);
			अगर (entry->flags & CNTR_DISABLED) अणु
				/* Nothing */
				hfi1_cdbg(CNTR, "\tDisabled\n");
				जारी;
			पूर्ण

			अगर (entry->flags & CNTR_VL) अणु
				hfi1_cdbg(CNTR, "\tPer VL");
				क्रम (j = 0; j < C_VL_COUNT; j++) अणु
					val = entry->rw_cntr(entry, ppd, j,
							       CNTR_MODE_R,
							       0);
					hfi1_cdbg(
					   CNTR,
					   "\t\tRead 0x%llx for %d",
					   val, j);
					ppd->cntrs[entry->offset + j] = val;
				पूर्ण
			पूर्ण अन्यथा अणु
				val = entry->rw_cntr(entry, ppd,
						       CNTR_INVALID_VL,
						       CNTR_MODE_R,
						       0);
				ppd->cntrs[entry->offset] = val;
				hfi1_cdbg(CNTR, "\tRead 0x%llx", val);
			पूर्ण
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम मुक्त_cntrs(काष्ठा hfi1_devdata *dd)
अणु
	काष्ठा hfi1_pportdata *ppd;
	पूर्णांक i;

	अगर (dd->synth_stats_समयr.function)
		del_समयr_sync(&dd->synth_stats_समयr);
	ppd = (काष्ठा hfi1_pportdata *)(dd + 1);
	क्रम (i = 0; i < dd->num_pports; i++, ppd++) अणु
		kमुक्त(ppd->cntrs);
		kमुक्त(ppd->scntrs);
		मुक्त_percpu(ppd->ibport_data.rvp.rc_acks);
		मुक्त_percpu(ppd->ibport_data.rvp.rc_qacks);
		मुक्त_percpu(ppd->ibport_data.rvp.rc_delayed_comp);
		ppd->cntrs = शून्य;
		ppd->scntrs = शून्य;
		ppd->ibport_data.rvp.rc_acks = शून्य;
		ppd->ibport_data.rvp.rc_qacks = शून्य;
		ppd->ibport_data.rvp.rc_delayed_comp = शून्य;
	पूर्ण
	kमुक्त(dd->portcntrnames);
	dd->portcntrnames = शून्य;
	kमुक्त(dd->cntrs);
	dd->cntrs = शून्य;
	kमुक्त(dd->scntrs);
	dd->scntrs = शून्य;
	kमुक्त(dd->cntrnames);
	dd->cntrnames = शून्य;
	अगर (dd->update_cntr_wq) अणु
		destroy_workqueue(dd->update_cntr_wq);
		dd->update_cntr_wq = शून्य;
	पूर्ण
पूर्ण

अटल u64 पढ़ो_dev_port_cntr(काष्ठा hfi1_devdata *dd, काष्ठा cntr_entry *entry,
			      u64 *psval, व्योम *context, पूर्णांक vl)
अणु
	u64 val;
	u64 sval = *psval;

	अगर (entry->flags & CNTR_DISABLED) अणु
		dd_dev_err(dd, "Counter %s not enabled", entry->name);
		वापस 0;
	पूर्ण

	hfi1_cdbg(CNTR, "cntr: %s vl %d psval 0x%llx", entry->name, vl, *psval);

	val = entry->rw_cntr(entry, context, vl, CNTR_MODE_R, 0);

	/* If its a synthetic counter there is more work we need to करो */
	अगर (entry->flags & CNTR_SYNTH) अणु
		अगर (sval == CNTR_MAX) अणु
			/* No need to पढ़ो alपढ़ोy saturated */
			वापस CNTR_MAX;
		पूर्ण

		अगर (entry->flags & CNTR_32BIT) अणु
			/* 32bit counters can wrap multiple बार */
			u64 upper = sval >> 32;
			u64 lower = (sval << 32) >> 32;

			अगर (lower > val) अणु /* hw wrapped */
				अगर (upper == CNTR_32BIT_MAX)
					val = CNTR_MAX;
				अन्यथा
					upper++;
			पूर्ण

			अगर (val != CNTR_MAX)
				val = (upper << 32) | val;

		पूर्ण अन्यथा अणु
			/* If we rolled we are saturated */
			अगर ((val < sval) || (val > CNTR_MAX))
				val = CNTR_MAX;
		पूर्ण
	पूर्ण

	*psval = val;

	hfi1_cdbg(CNTR, "\tNew val=0x%llx", val);

	वापस val;
पूर्ण

अटल u64 ग_लिखो_dev_port_cntr(काष्ठा hfi1_devdata *dd,
			       काष्ठा cntr_entry *entry,
			       u64 *psval, व्योम *context, पूर्णांक vl, u64 data)
अणु
	u64 val;

	अगर (entry->flags & CNTR_DISABLED) अणु
		dd_dev_err(dd, "Counter %s not enabled", entry->name);
		वापस 0;
	पूर्ण

	hfi1_cdbg(CNTR, "cntr: %s vl %d psval 0x%llx", entry->name, vl, *psval);

	अगर (entry->flags & CNTR_SYNTH) अणु
		*psval = data;
		अगर (entry->flags & CNTR_32BIT) अणु
			val = entry->rw_cntr(entry, context, vl, CNTR_MODE_W,
					     (data << 32) >> 32);
			val = data; /* वापस the full 64bit value */
		पूर्ण अन्यथा अणु
			val = entry->rw_cntr(entry, context, vl, CNTR_MODE_W,
					     data);
		पूर्ण
	पूर्ण अन्यथा अणु
		val = entry->rw_cntr(entry, context, vl, CNTR_MODE_W, data);
	पूर्ण

	*psval = val;

	hfi1_cdbg(CNTR, "\tNew val=0x%llx", val);

	वापस val;
पूर्ण

u64 पढ़ो_dev_cntr(काष्ठा hfi1_devdata *dd, पूर्णांक index, पूर्णांक vl)
अणु
	काष्ठा cntr_entry *entry;
	u64 *sval;

	entry = &dev_cntrs[index];
	sval = dd->scntrs + entry->offset;

	अगर (vl != CNTR_INVALID_VL)
		sval += vl;

	वापस पढ़ो_dev_port_cntr(dd, entry, sval, dd, vl);
पूर्ण

u64 ग_लिखो_dev_cntr(काष्ठा hfi1_devdata *dd, पूर्णांक index, पूर्णांक vl, u64 data)
अणु
	काष्ठा cntr_entry *entry;
	u64 *sval;

	entry = &dev_cntrs[index];
	sval = dd->scntrs + entry->offset;

	अगर (vl != CNTR_INVALID_VL)
		sval += vl;

	वापस ग_लिखो_dev_port_cntr(dd, entry, sval, dd, vl, data);
पूर्ण

u64 पढ़ो_port_cntr(काष्ठा hfi1_pportdata *ppd, पूर्णांक index, पूर्णांक vl)
अणु
	काष्ठा cntr_entry *entry;
	u64 *sval;

	entry = &port_cntrs[index];
	sval = ppd->scntrs + entry->offset;

	अगर (vl != CNTR_INVALID_VL)
		sval += vl;

	अगर ((index >= C_RCV_HDR_OVF_FIRST + ppd->dd->num_rcv_contexts) &&
	    (index <= C_RCV_HDR_OVF_LAST)) अणु
		/* We करो not want to bother क्रम disabled contexts */
		वापस 0;
	पूर्ण

	वापस पढ़ो_dev_port_cntr(ppd->dd, entry, sval, ppd, vl);
पूर्ण

u64 ग_लिखो_port_cntr(काष्ठा hfi1_pportdata *ppd, पूर्णांक index, पूर्णांक vl, u64 data)
अणु
	काष्ठा cntr_entry *entry;
	u64 *sval;

	entry = &port_cntrs[index];
	sval = ppd->scntrs + entry->offset;

	अगर (vl != CNTR_INVALID_VL)
		sval += vl;

	अगर ((index >= C_RCV_HDR_OVF_FIRST + ppd->dd->num_rcv_contexts) &&
	    (index <= C_RCV_HDR_OVF_LAST)) अणु
		/* We करो not want to bother क्रम disabled contexts */
		वापस 0;
	पूर्ण

	वापस ग_लिखो_dev_port_cntr(ppd->dd, entry, sval, ppd, vl, data);
पूर्ण

अटल व्योम करो_update_synth_समयr(काष्ठा work_काष्ठा *work)
अणु
	u64 cur_tx;
	u64 cur_rx;
	u64 total_flits;
	u8 update = 0;
	पूर्णांक i, j, vl;
	काष्ठा hfi1_pportdata *ppd;
	काष्ठा cntr_entry *entry;
	काष्ठा hfi1_devdata *dd = container_of(work, काष्ठा hfi1_devdata,
					       update_cntr_work);

	/*
	 * Rather than keep beating on the CSRs pick a minimal set that we can
	 * check to watch क्रम potential roll over. We can करो this by looking at
	 * the number of flits sent/recv. If the total flits exceeds 32bits then
	 * we have to iterate all the counters and update.
	 */
	entry = &dev_cntrs[C_DC_RCV_FLITS];
	cur_rx = entry->rw_cntr(entry, dd, CNTR_INVALID_VL, CNTR_MODE_R, 0);

	entry = &dev_cntrs[C_DC_XMIT_FLITS];
	cur_tx = entry->rw_cntr(entry, dd, CNTR_INVALID_VL, CNTR_MODE_R, 0);

	hfi1_cdbg(
	    CNTR,
	    "[%d] curr tx=0x%llx rx=0x%llx :: last tx=0x%llx rx=0x%llx\n",
	    dd->unit, cur_tx, cur_rx, dd->last_tx, dd->last_rx);

	अगर ((cur_tx < dd->last_tx) || (cur_rx < dd->last_rx)) अणु
		/*
		 * May not be strictly necessary to update but it won't hurt and
		 * simplअगरies the logic here.
		 */
		update = 1;
		hfi1_cdbg(CNTR, "[%d] Tripwire counter rolled, updating",
			  dd->unit);
	पूर्ण अन्यथा अणु
		total_flits = (cur_tx - dd->last_tx) + (cur_rx - dd->last_rx);
		hfi1_cdbg(CNTR,
			  "[%d] total flits 0x%llx limit 0x%llx\n", dd->unit,
			  total_flits, (u64)CNTR_32BIT_MAX);
		अगर (total_flits >= CNTR_32BIT_MAX) अणु
			hfi1_cdbg(CNTR, "[%d] 32bit limit hit, updating",
				  dd->unit);
			update = 1;
		पूर्ण
	पूर्ण

	अगर (update) अणु
		hfi1_cdbg(CNTR, "[%d] Updating dd and ppd counters", dd->unit);
		क्रम (i = 0; i < DEV_CNTR_LAST; i++) अणु
			entry = &dev_cntrs[i];
			अगर (entry->flags & CNTR_VL) अणु
				क्रम (vl = 0; vl < C_VL_COUNT; vl++)
					पढ़ो_dev_cntr(dd, i, vl);
			पूर्ण अन्यथा अणु
				पढ़ो_dev_cntr(dd, i, CNTR_INVALID_VL);
			पूर्ण
		पूर्ण
		ppd = (काष्ठा hfi1_pportdata *)(dd + 1);
		क्रम (i = 0; i < dd->num_pports; i++, ppd++) अणु
			क्रम (j = 0; j < PORT_CNTR_LAST; j++) अणु
				entry = &port_cntrs[j];
				अगर (entry->flags & CNTR_VL) अणु
					क्रम (vl = 0; vl < C_VL_COUNT; vl++)
						पढ़ो_port_cntr(ppd, j, vl);
				पूर्ण अन्यथा अणु
					पढ़ो_port_cntr(ppd, j, CNTR_INVALID_VL);
				पूर्ण
			पूर्ण
		पूर्ण

		/*
		 * We want the value in the रेजिस्टर. The goal is to keep track
		 * of the number of "ticks" not the counter value. In other
		 * words अगर the रेजिस्टर rolls we want to notice it and go ahead
		 * and क्रमce an update.
		 */
		entry = &dev_cntrs[C_DC_XMIT_FLITS];
		dd->last_tx = entry->rw_cntr(entry, dd, CNTR_INVALID_VL,
						CNTR_MODE_R, 0);

		entry = &dev_cntrs[C_DC_RCV_FLITS];
		dd->last_rx = entry->rw_cntr(entry, dd, CNTR_INVALID_VL,
						CNTR_MODE_R, 0);

		hfi1_cdbg(CNTR, "[%d] setting last tx/rx to 0x%llx 0x%llx",
			  dd->unit, dd->last_tx, dd->last_rx);

	पूर्ण अन्यथा अणु
		hfi1_cdbg(CNTR, "[%d] No update necessary", dd->unit);
	पूर्ण
पूर्ण

अटल व्योम update_synth_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा hfi1_devdata *dd = from_समयr(dd, t, synth_stats_समयr);

	queue_work(dd->update_cntr_wq, &dd->update_cntr_work);
	mod_समयr(&dd->synth_stats_समयr, jअगरfies + HZ * SYNTH_CNT_TIME);
पूर्ण

#घोषणा C_MAX_NAME 16 /* 15 अक्षरs + one क्रम /0 */
अटल पूर्णांक init_cntrs(काष्ठा hfi1_devdata *dd)
अणु
	पूर्णांक i, rcv_ctxts, j;
	माप_प्रकार sz;
	अक्षर *p;
	अक्षर name[C_MAX_NAME];
	काष्ठा hfi1_pportdata *ppd;
	स्थिर अक्षर *bit_type_32 = ",32";
	स्थिर पूर्णांक bit_type_32_sz = म_माप(bit_type_32);
	u32 sdma_engines = chip_sdma_engines(dd);

	/* set up the stats समयr; the add_समयr is करोne at the end */
	समयr_setup(&dd->synth_stats_समयr, update_synth_समयr, 0);

	/***********************/
	/* per device counters */
	/***********************/

	/* size names and determine how many we have*/
	dd->ndevcntrs = 0;
	sz = 0;

	क्रम (i = 0; i < DEV_CNTR_LAST; i++) अणु
		अगर (dev_cntrs[i].flags & CNTR_DISABLED) अणु
			hfi1_dbg_early("\tSkipping %s\n", dev_cntrs[i].name);
			जारी;
		पूर्ण

		अगर (dev_cntrs[i].flags & CNTR_VL) अणु
			dev_cntrs[i].offset = dd->ndevcntrs;
			क्रम (j = 0; j < C_VL_COUNT; j++) अणु
				snम_लिखो(name, C_MAX_NAME, "%s%d",
					 dev_cntrs[i].name, vl_from_idx(j));
				sz += म_माप(name);
				/* Add ",32" क्रम 32-bit counters */
				अगर (dev_cntrs[i].flags & CNTR_32BIT)
					sz += bit_type_32_sz;
				sz++;
				dd->ndevcntrs++;
			पूर्ण
		पूर्ण अन्यथा अगर (dev_cntrs[i].flags & CNTR_SDMA) अणु
			dev_cntrs[i].offset = dd->ndevcntrs;
			क्रम (j = 0; j < sdma_engines; j++) अणु
				snम_लिखो(name, C_MAX_NAME, "%s%d",
					 dev_cntrs[i].name, j);
				sz += म_माप(name);
				/* Add ",32" क्रम 32-bit counters */
				अगर (dev_cntrs[i].flags & CNTR_32BIT)
					sz += bit_type_32_sz;
				sz++;
				dd->ndevcntrs++;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* +1 क्रम newline. */
			sz += म_माप(dev_cntrs[i].name) + 1;
			/* Add ",32" क्रम 32-bit counters */
			अगर (dev_cntrs[i].flags & CNTR_32BIT)
				sz += bit_type_32_sz;
			dev_cntrs[i].offset = dd->ndevcntrs;
			dd->ndevcntrs++;
		पूर्ण
	पूर्ण

	/* allocate space क्रम the counter values */
	dd->cntrs = kसुस्मृति(dd->ndevcntrs + num_driver_cntrs, माप(u64),
			    GFP_KERNEL);
	अगर (!dd->cntrs)
		जाओ bail;

	dd->scntrs = kसुस्मृति(dd->ndevcntrs, माप(u64), GFP_KERNEL);
	अगर (!dd->scntrs)
		जाओ bail;

	/* allocate space क्रम the counter names */
	dd->cntrnameslen = sz;
	dd->cntrnames = kदो_स्मृति(sz, GFP_KERNEL);
	अगर (!dd->cntrnames)
		जाओ bail;

	/* fill in the names */
	क्रम (p = dd->cntrnames, i = 0; i < DEV_CNTR_LAST; i++) अणु
		अगर (dev_cntrs[i].flags & CNTR_DISABLED) अणु
			/* Nothing */
		पूर्ण अन्यथा अगर (dev_cntrs[i].flags & CNTR_VL) अणु
			क्रम (j = 0; j < C_VL_COUNT; j++) अणु
				snम_लिखो(name, C_MAX_NAME, "%s%d",
					 dev_cntrs[i].name,
					 vl_from_idx(j));
				स_नकल(p, name, म_माप(name));
				p += म_माप(name);

				/* Counter is 32 bits */
				अगर (dev_cntrs[i].flags & CNTR_32BIT) अणु
					स_नकल(p, bit_type_32, bit_type_32_sz);
					p += bit_type_32_sz;
				पूर्ण

				*p++ = '\n';
			पूर्ण
		पूर्ण अन्यथा अगर (dev_cntrs[i].flags & CNTR_SDMA) अणु
			क्रम (j = 0; j < sdma_engines; j++) अणु
				snम_लिखो(name, C_MAX_NAME, "%s%d",
					 dev_cntrs[i].name, j);
				स_नकल(p, name, म_माप(name));
				p += म_माप(name);

				/* Counter is 32 bits */
				अगर (dev_cntrs[i].flags & CNTR_32BIT) अणु
					स_नकल(p, bit_type_32, bit_type_32_sz);
					p += bit_type_32_sz;
				पूर्ण

				*p++ = '\n';
			पूर्ण
		पूर्ण अन्यथा अणु
			स_नकल(p, dev_cntrs[i].name, म_माप(dev_cntrs[i].name));
			p += म_माप(dev_cntrs[i].name);

			/* Counter is 32 bits */
			अगर (dev_cntrs[i].flags & CNTR_32BIT) अणु
				स_नकल(p, bit_type_32, bit_type_32_sz);
				p += bit_type_32_sz;
			पूर्ण

			*p++ = '\n';
		पूर्ण
	पूर्ण

	/*********************/
	/* per port counters */
	/*********************/

	/*
	 * Go through the counters क्रम the overflows and disable the ones we
	 * करोn't need. This varies based on platक्रमm so we need to करो it
	 * dynamically here.
	 */
	rcv_ctxts = dd->num_rcv_contexts;
	क्रम (i = C_RCV_HDR_OVF_FIRST + rcv_ctxts;
	     i <= C_RCV_HDR_OVF_LAST; i++) अणु
		port_cntrs[i].flags |= CNTR_DISABLED;
	पूर्ण

	/* size port counter names and determine how many we have*/
	sz = 0;
	dd->nportcntrs = 0;
	क्रम (i = 0; i < PORT_CNTR_LAST; i++) अणु
		अगर (port_cntrs[i].flags & CNTR_DISABLED) अणु
			hfi1_dbg_early("\tSkipping %s\n", port_cntrs[i].name);
			जारी;
		पूर्ण

		अगर (port_cntrs[i].flags & CNTR_VL) अणु
			port_cntrs[i].offset = dd->nportcntrs;
			क्रम (j = 0; j < C_VL_COUNT; j++) अणु
				snम_लिखो(name, C_MAX_NAME, "%s%d",
					 port_cntrs[i].name, vl_from_idx(j));
				sz += म_माप(name);
				/* Add ",32" क्रम 32-bit counters */
				अगर (port_cntrs[i].flags & CNTR_32BIT)
					sz += bit_type_32_sz;
				sz++;
				dd->nportcntrs++;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* +1 क्रम newline */
			sz += म_माप(port_cntrs[i].name) + 1;
			/* Add ",32" क्रम 32-bit counters */
			अगर (port_cntrs[i].flags & CNTR_32BIT)
				sz += bit_type_32_sz;
			port_cntrs[i].offset = dd->nportcntrs;
			dd->nportcntrs++;
		पूर्ण
	पूर्ण

	/* allocate space क्रम the counter names */
	dd->portcntrnameslen = sz;
	dd->portcntrnames = kदो_स्मृति(sz, GFP_KERNEL);
	अगर (!dd->portcntrnames)
		जाओ bail;

	/* fill in port cntr names */
	क्रम (p = dd->portcntrnames, i = 0; i < PORT_CNTR_LAST; i++) अणु
		अगर (port_cntrs[i].flags & CNTR_DISABLED)
			जारी;

		अगर (port_cntrs[i].flags & CNTR_VL) अणु
			क्रम (j = 0; j < C_VL_COUNT; j++) अणु
				snम_लिखो(name, C_MAX_NAME, "%s%d",
					 port_cntrs[i].name, vl_from_idx(j));
				स_नकल(p, name, म_माप(name));
				p += म_माप(name);

				/* Counter is 32 bits */
				अगर (port_cntrs[i].flags & CNTR_32BIT) अणु
					स_नकल(p, bit_type_32, bit_type_32_sz);
					p += bit_type_32_sz;
				पूर्ण

				*p++ = '\n';
			पूर्ण
		पूर्ण अन्यथा अणु
			स_नकल(p, port_cntrs[i].name,
			       म_माप(port_cntrs[i].name));
			p += म_माप(port_cntrs[i].name);

			/* Counter is 32 bits */
			अगर (port_cntrs[i].flags & CNTR_32BIT) अणु
				स_नकल(p, bit_type_32, bit_type_32_sz);
				p += bit_type_32_sz;
			पूर्ण

			*p++ = '\n';
		पूर्ण
	पूर्ण

	/* allocate per port storage क्रम counter values */
	ppd = (काष्ठा hfi1_pportdata *)(dd + 1);
	क्रम (i = 0; i < dd->num_pports; i++, ppd++) अणु
		ppd->cntrs = kसुस्मृति(dd->nportcntrs, माप(u64), GFP_KERNEL);
		अगर (!ppd->cntrs)
			जाओ bail;

		ppd->scntrs = kसुस्मृति(dd->nportcntrs, माप(u64), GFP_KERNEL);
		अगर (!ppd->scntrs)
			जाओ bail;
	पूर्ण

	/* CPU counters need to be allocated and zeroed */
	अगर (init_cpu_counters(dd))
		जाओ bail;

	dd->update_cntr_wq = alloc_ordered_workqueue("hfi1_update_cntr_%d",
						     WQ_MEM_RECLAIM, dd->unit);
	अगर (!dd->update_cntr_wq)
		जाओ bail;

	INIT_WORK(&dd->update_cntr_work, करो_update_synth_समयr);

	mod_समयr(&dd->synth_stats_समयr, jअगरfies + HZ * SYNTH_CNT_TIME);
	वापस 0;
bail:
	मुक्त_cntrs(dd);
	वापस -ENOMEM;
पूर्ण

अटल u32 chip_to_opa_lstate(काष्ठा hfi1_devdata *dd, u32 chip_lstate)
अणु
	चयन (chip_lstate) अणु
	हाल LSTATE_DOWN:
		वापस IB_PORT_DOWN;
	हाल LSTATE_INIT:
		वापस IB_PORT_INIT;
	हाल LSTATE_ARMED:
		वापस IB_PORT_ARMED;
	हाल LSTATE_ACTIVE:
		वापस IB_PORT_ACTIVE;
	शेष:
		dd_dev_err(dd,
			   "Unknown logical state 0x%x, reporting IB_PORT_DOWN\n",
			   chip_lstate);
		वापस IB_PORT_DOWN;
	पूर्ण
पूर्ण

u32 chip_to_opa_pstate(काष्ठा hfi1_devdata *dd, u32 chip_pstate)
अणु
	/* look at the HFI meta-states only */
	चयन (chip_pstate & 0xf0) अणु
	हाल PLS_DISABLED:
		वापस IB_PORTPHYSSTATE_DISABLED;
	हाल PLS_OFFLINE:
		वापस OPA_PORTPHYSSTATE_OFFLINE;
	हाल PLS_POLLING:
		वापस IB_PORTPHYSSTATE_POLLING;
	हाल PLS_CONFIGPHY:
		वापस IB_PORTPHYSSTATE_TRAINING;
	हाल PLS_LINKUP:
		वापस IB_PORTPHYSSTATE_LINKUP;
	हाल PLS_PHYTEST:
		वापस IB_PORTPHYSSTATE_PHY_TEST;
	शेष:
		dd_dev_err(dd, "Unexpected chip physical state of 0x%x\n",
			   chip_pstate);
		वापस IB_PORTPHYSSTATE_DISABLED;
	पूर्ण
पूर्ण

/* वापस the OPA port logical state name */
स्थिर अक्षर *opa_lstate_name(u32 lstate)
अणु
	अटल स्थिर अक्षर * स्थिर port_logical_names[] = अणु
		"PORT_NOP",
		"PORT_DOWN",
		"PORT_INIT",
		"PORT_ARMED",
		"PORT_ACTIVE",
		"PORT_ACTIVE_DEFER",
	पूर्ण;
	अगर (lstate < ARRAY_SIZE(port_logical_names))
		वापस port_logical_names[lstate];
	वापस "unknown";
पूर्ण

/* वापस the OPA port physical state name */
स्थिर अक्षर *opa_pstate_name(u32 pstate)
अणु
	अटल स्थिर अक्षर * स्थिर port_physical_names[] = अणु
		"PHYS_NOP",
		"reserved1",
		"PHYS_POLL",
		"PHYS_DISABLED",
		"PHYS_TRAINING",
		"PHYS_LINKUP",
		"PHYS_LINK_ERR_RECOVER",
		"PHYS_PHY_TEST",
		"reserved8",
		"PHYS_OFFLINE",
		"PHYS_GANGED",
		"PHYS_TEST",
	पूर्ण;
	अगर (pstate < ARRAY_SIZE(port_physical_names))
		वापस port_physical_names[pstate];
	वापस "unknown";
पूर्ण

/**
 * update_statusp - Update userspace status flag
 * @ppd: Port data काष्ठाure
 * @state: port state inक्रमmation
 *
 * Actual port status is determined by the host_link_state value
 * in the ppd.
 *
 * host_link_state MUST be updated beक्रमe updating the user space
 * statusp.
 */
अटल व्योम update_statusp(काष्ठा hfi1_pportdata *ppd, u32 state)
अणु
	/*
	 * Set port status flags in the page mapped पूर्णांकo userspace
	 * memory. Do it here to ensure a reliable state - this is
	 * the only function called by all state handling code.
	 * Always set the flags due to the fact that the cache value
	 * might have been changed explicitly outside of this
	 * function.
	 */
	अगर (ppd->statusp) अणु
		चयन (state) अणु
		हाल IB_PORT_DOWN:
		हाल IB_PORT_INIT:
			*ppd->statusp &= ~(HFI1_STATUS_IB_CONF |
					   HFI1_STATUS_IB_READY);
			अवरोध;
		हाल IB_PORT_ARMED:
			*ppd->statusp |= HFI1_STATUS_IB_CONF;
			अवरोध;
		हाल IB_PORT_ACTIVE:
			*ppd->statusp |= HFI1_STATUS_IB_READY;
			अवरोध;
		पूर्ण
	पूर्ण
	dd_dev_info(ppd->dd, "logical state changed to %s (0x%x)\n",
		    opa_lstate_name(state), state);
पूर्ण

/**
 * रुको_logical_linkstate - रुको क्रम an IB link state change to occur
 * @ppd: port device
 * @state: the state to रुको क्रम
 * @msecs: the number of milliseconds to रुको
 *
 * Wait up to msecs milliseconds क्रम IB link state change to occur.
 * For now, take the easy polling route.
 * Returns 0 अगर state reached, otherwise -ETIMEDOUT.
 */
अटल पूर्णांक रुको_logical_linkstate(काष्ठा hfi1_pportdata *ppd, u32 state,
				  पूर्णांक msecs)
अणु
	अचिन्हित दीर्घ समयout;
	u32 new_state;

	समयout = jअगरfies + msecs_to_jअगरfies(msecs);
	जबतक (1) अणु
		new_state = chip_to_opa_lstate(ppd->dd,
					       पढ़ो_logical_state(ppd->dd));
		अगर (new_state == state)
			अवरोध;
		अगर (समय_after(jअगरfies, समयout)) अणु
			dd_dev_err(ppd->dd,
				   "timeout waiting for link state 0x%x\n",
				   state);
			वापस -ETIMEDOUT;
		पूर्ण
		msleep(20);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम log_state_transition(काष्ठा hfi1_pportdata *ppd, u32 state)
अणु
	u32 ib_pstate = chip_to_opa_pstate(ppd->dd, state);

	dd_dev_info(ppd->dd,
		    "physical state changed to %s (0x%x), phy 0x%x\n",
		    opa_pstate_name(ib_pstate), ib_pstate, state);
पूर्ण

/*
 * Read the physical hardware link state and check अगर it matches host
 * drivers anticipated state.
 */
अटल व्योम log_physical_state(काष्ठा hfi1_pportdata *ppd, u32 state)
अणु
	u32 पढ़ो_state = पढ़ो_physical_state(ppd->dd);

	अगर (पढ़ो_state == state) अणु
		log_state_transition(ppd, state);
	पूर्ण अन्यथा अणु
		dd_dev_err(ppd->dd,
			   "anticipated phy link state 0x%x, read 0x%x\n",
			   state, पढ़ो_state);
	पूर्ण
पूर्ण

/*
 * रुको_physical_linkstate - रुको क्रम an physical link state change to occur
 * @ppd: port device
 * @state: the state to रुको क्रम
 * @msecs: the number of milliseconds to रुको
 *
 * Wait up to msecs milliseconds क्रम physical link state change to occur.
 * Returns 0 अगर state reached, otherwise -ETIMEDOUT.
 */
अटल पूर्णांक रुको_physical_linkstate(काष्ठा hfi1_pportdata *ppd, u32 state,
				   पूर्णांक msecs)
अणु
	u32 पढ़ो_state;
	अचिन्हित दीर्घ समयout;

	समयout = jअगरfies + msecs_to_jअगरfies(msecs);
	जबतक (1) अणु
		पढ़ो_state = पढ़ो_physical_state(ppd->dd);
		अगर (पढ़ो_state == state)
			अवरोध;
		अगर (समय_after(jअगरfies, समयout)) अणु
			dd_dev_err(ppd->dd,
				   "timeout waiting for phy link state 0x%x\n",
				   state);
			वापस -ETIMEDOUT;
		पूर्ण
		usleep_range(1950, 2050); /* sleep 2ms-ish */
	पूर्ण

	log_state_transition(ppd, state);
	वापस 0;
पूर्ण

/*
 * रुको_phys_link_offline_quiet_substates - रुको क्रम any offline substate
 * @ppd: port device
 * @msecs: the number of milliseconds to रुको
 *
 * Wait up to msecs milliseconds क्रम any offline physical link
 * state change to occur.
 * Returns 0 अगर at least one state is reached, otherwise -ETIMEDOUT.
 */
अटल पूर्णांक रुको_phys_link_offline_substates(काष्ठा hfi1_pportdata *ppd,
					    पूर्णांक msecs)
अणु
	u32 पढ़ो_state;
	अचिन्हित दीर्घ समयout;

	समयout = jअगरfies + msecs_to_jअगरfies(msecs);
	जबतक (1) अणु
		पढ़ो_state = पढ़ो_physical_state(ppd->dd);
		अगर ((पढ़ो_state & 0xF0) == PLS_OFFLINE)
			अवरोध;
		अगर (समय_after(jअगरfies, समयout)) अणु
			dd_dev_err(ppd->dd,
				   "timeout waiting for phy link offline.quiet substates. Read state 0x%x, %dms\n",
				   पढ़ो_state, msecs);
			वापस -ETIMEDOUT;
		पूर्ण
		usleep_range(1950, 2050); /* sleep 2ms-ish */
	पूर्ण

	log_state_transition(ppd, पढ़ो_state);
	वापस पढ़ो_state;
पूर्ण

/*
 * रुको_phys_link_out_of_offline - रुको क्रम any out of offline state
 * @ppd: port device
 * @msecs: the number of milliseconds to रुको
 *
 * Wait up to msecs milliseconds क्रम any out of offline physical link
 * state change to occur.
 * Returns 0 अगर at least one state is reached, otherwise -ETIMEDOUT.
 */
अटल पूर्णांक रुको_phys_link_out_of_offline(काष्ठा hfi1_pportdata *ppd,
					 पूर्णांक msecs)
अणु
	u32 पढ़ो_state;
	अचिन्हित दीर्घ समयout;

	समयout = jअगरfies + msecs_to_jअगरfies(msecs);
	जबतक (1) अणु
		पढ़ो_state = पढ़ो_physical_state(ppd->dd);
		अगर ((पढ़ो_state & 0xF0) != PLS_OFFLINE)
			अवरोध;
		अगर (समय_after(jअगरfies, समयout)) अणु
			dd_dev_err(ppd->dd,
				   "timeout waiting for phy link out of offline. Read state 0x%x, %dms\n",
				   पढ़ो_state, msecs);
			वापस -ETIMEDOUT;
		पूर्ण
		usleep_range(1950, 2050); /* sleep 2ms-ish */
	पूर्ण

	log_state_transition(ppd, पढ़ो_state);
	वापस पढ़ो_state;
पूर्ण

#घोषणा CLEAR_STATIC_RATE_CONTROL_SMASK(r) \
(r &= ~SEND_CTXT_CHECK_ENABLE_DISALLOW_PBC_STATIC_RATE_CONTROL_SMASK)

#घोषणा SET_STATIC_RATE_CONTROL_SMASK(r) \
(r |= SEND_CTXT_CHECK_ENABLE_DISALLOW_PBC_STATIC_RATE_CONTROL_SMASK)

व्योम hfi1_init_ctxt(काष्ठा send_context *sc)
अणु
	अगर (sc) अणु
		काष्ठा hfi1_devdata *dd = sc->dd;
		u64 reg;
		u8 set = (sc->type == SC_USER ?
			  HFI1_CAP_IS_USET(STATIC_RATE_CTRL) :
			  HFI1_CAP_IS_KSET(STATIC_RATE_CTRL));
		reg = पढ़ो_kctxt_csr(dd, sc->hw_context,
				     SEND_CTXT_CHECK_ENABLE);
		अगर (set)
			CLEAR_STATIC_RATE_CONTROL_SMASK(reg);
		अन्यथा
			SET_STATIC_RATE_CONTROL_SMASK(reg);
		ग_लिखो_kctxt_csr(dd, sc->hw_context,
				SEND_CTXT_CHECK_ENABLE, reg);
	पूर्ण
पूर्ण

पूर्णांक hfi1_tempsense_rd(काष्ठा hfi1_devdata *dd, काष्ठा hfi1_temp *temp)
अणु
	पूर्णांक ret = 0;
	u64 reg;

	अगर (dd->icode != ICODE_RTL_SILICON) अणु
		अगर (HFI1_CAP_IS_KSET(PRINT_UNIMPL))
			dd_dev_info(dd, "%s: tempsense not supported by HW\n",
				    __func__);
		वापस -EINVAL;
	पूर्ण
	reg = पढ़ो_csr(dd, ASIC_STS_THERM);
	temp->curr = ((reg >> ASIC_STS_THERM_CURR_TEMP_SHIFT) &
		      ASIC_STS_THERM_CURR_TEMP_MASK);
	temp->lo_lim = ((reg >> ASIC_STS_THERM_LO_TEMP_SHIFT) &
			ASIC_STS_THERM_LO_TEMP_MASK);
	temp->hi_lim = ((reg >> ASIC_STS_THERM_HI_TEMP_SHIFT) &
			ASIC_STS_THERM_HI_TEMP_MASK);
	temp->crit_lim = ((reg >> ASIC_STS_THERM_CRIT_TEMP_SHIFT) &
			  ASIC_STS_THERM_CRIT_TEMP_MASK);
	/* triggers is a 3-bit value - 1 bit per trigger. */
	temp->triggers = (u8)((reg >> ASIC_STS_THERM_LOW_SHIFT) & 0x7);

	वापस ret;
पूर्ण

/* ========================================================================= */

/**
 * पढ़ो_mod_ग_लिखो() - Calculate the IRQ रेजिस्टर index and set/clear the bits
 * @dd: valid devdata
 * @src: IRQ source to determine रेजिस्टर index from
 * @bits: the bits to set or clear
 * @set: true == set the bits, false == clear the bits
 *
 */
अटल व्योम पढ़ो_mod_ग_लिखो(काष्ठा hfi1_devdata *dd, u16 src, u64 bits,
			   bool set)
अणु
	u64 reg;
	u16 idx = src / BITS_PER_REGISTER;

	spin_lock(&dd->irq_src_lock);
	reg = पढ़ो_csr(dd, CCE_INT_MASK + (8 * idx));
	अगर (set)
		reg |= bits;
	अन्यथा
		reg &= ~bits;
	ग_लिखो_csr(dd, CCE_INT_MASK + (8 * idx), reg);
	spin_unlock(&dd->irq_src_lock);
पूर्ण

/**
 * set_पूर्णांकr_bits() - Enable/disable a range (one or more) IRQ sources
 * @dd: valid devdata
 * @first: first IRQ source to set/clear
 * @last: last IRQ source (inclusive) to set/clear
 * @set: true == set the bits, false == clear the bits
 *
 * If first == last, set the exact source.
 */
पूर्णांक set_पूर्णांकr_bits(काष्ठा hfi1_devdata *dd, u16 first, u16 last, bool set)
अणु
	u64 bits = 0;
	u64 bit;
	u16 src;

	अगर (first > NUM_INTERRUPT_SOURCES || last > NUM_INTERRUPT_SOURCES)
		वापस -EINVAL;

	अगर (last < first)
		वापस -दुस्फल;

	क्रम (src = first; src <= last; src++) अणु
		bit = src % BITS_PER_REGISTER;
		/* wrapped to next रेजिस्टर? */
		अगर (!bit && bits) अणु
			पढ़ो_mod_ग_लिखो(dd, src - 1, bits, set);
			bits = 0;
		पूर्ण
		bits |= BIT_ULL(bit);
	पूर्ण
	पढ़ो_mod_ग_लिखो(dd, last, bits, set);

	वापस 0;
पूर्ण

/*
 * Clear all पूर्णांकerrupt sources on the chip.
 */
व्योम clear_all_पूर्णांकerrupts(काष्ठा hfi1_devdata *dd)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < CCE_NUM_INT_CSRS; i++)
		ग_लिखो_csr(dd, CCE_INT_CLEAR + (8 * i), ~(u64)0);

	ग_लिखो_csr(dd, CCE_ERR_CLEAR, ~(u64)0);
	ग_लिखो_csr(dd, MISC_ERR_CLEAR, ~(u64)0);
	ग_लिखो_csr(dd, RCV_ERR_CLEAR, ~(u64)0);
	ग_लिखो_csr(dd, SEND_ERR_CLEAR, ~(u64)0);
	ग_लिखो_csr(dd, SEND_PIO_ERR_CLEAR, ~(u64)0);
	ग_लिखो_csr(dd, SEND_DMA_ERR_CLEAR, ~(u64)0);
	ग_लिखो_csr(dd, SEND_EGRESS_ERR_CLEAR, ~(u64)0);
	क्रम (i = 0; i < chip_send_contexts(dd); i++)
		ग_लिखो_kctxt_csr(dd, i, SEND_CTXT_ERR_CLEAR, ~(u64)0);
	क्रम (i = 0; i < chip_sdma_engines(dd); i++)
		ग_लिखो_kctxt_csr(dd, i, SEND_DMA_ENG_ERR_CLEAR, ~(u64)0);

	ग_लिखो_csr(dd, DCC_ERR_FLG_CLR, ~(u64)0);
	ग_लिखो_csr(dd, DC_LCB_ERR_CLR, ~(u64)0);
	ग_लिखो_csr(dd, DC_DC8051_ERR_CLR, ~(u64)0);
पूर्ण

/*
 * Remap the पूर्णांकerrupt source from the general handler to the given MSI-X
 * पूर्णांकerrupt.
 */
व्योम remap_पूर्णांकr(काष्ठा hfi1_devdata *dd, पूर्णांक isrc, पूर्णांक msix_पूर्णांकr)
अणु
	u64 reg;
	पूर्णांक m, n;

	/* clear from the handled mask of the general पूर्णांकerrupt */
	m = isrc / 64;
	n = isrc % 64;
	अगर (likely(m < CCE_NUM_INT_CSRS)) अणु
		dd->gi_mask[m] &= ~((u64)1 << n);
	पूर्ण अन्यथा अणु
		dd_dev_err(dd, "remap interrupt err\n");
		वापस;
	पूर्ण

	/* direct the chip source to the given MSI-X पूर्णांकerrupt */
	m = isrc / 8;
	n = isrc % 8;
	reg = पढ़ो_csr(dd, CCE_INT_MAP + (8 * m));
	reg &= ~((u64)0xff << (8 * n));
	reg |= ((u64)msix_पूर्णांकr & 0xff) << (8 * n);
	ग_लिखो_csr(dd, CCE_INT_MAP + (8 * m), reg);
पूर्ण

व्योम remap_sdma_पूर्णांकerrupts(काष्ठा hfi1_devdata *dd, पूर्णांक engine, पूर्णांक msix_पूर्णांकr)
अणु
	/*
	 * SDMA engine पूर्णांकerrupt sources grouped by type, rather than
	 * engine.  Per-engine पूर्णांकerrupts are as follows:
	 *	SDMA
	 *	SDMAProgress
	 *	SDMAIdle
	 */
	remap_पूर्णांकr(dd, IS_SDMA_START + engine, msix_पूर्णांकr);
	remap_पूर्णांकr(dd, IS_SDMA_PROGRESS_START + engine, msix_पूर्णांकr);
	remap_पूर्णांकr(dd, IS_SDMA_IDLE_START + engine, msix_पूर्णांकr);
पूर्ण

/*
 * Set the general handler to accept all पूर्णांकerrupts, remap all
 * chip पूर्णांकerrupts back to MSI-X 0.
 */
व्योम reset_पूर्णांकerrupts(काष्ठा hfi1_devdata *dd)
अणु
	पूर्णांक i;

	/* all पूर्णांकerrupts handled by the general handler */
	क्रम (i = 0; i < CCE_NUM_INT_CSRS; i++)
		dd->gi_mask[i] = ~(u64)0;

	/* all chip पूर्णांकerrupts map to MSI-X 0 */
	क्रम (i = 0; i < CCE_NUM_INT_MAP_CSRS; i++)
		ग_लिखो_csr(dd, CCE_INT_MAP + (8 * i), 0);
पूर्ण

/**
 * set_up_पूर्णांकerrupts() - Initialize the IRQ resources and state
 * @dd: valid devdata
 *
 */
अटल पूर्णांक set_up_पूर्णांकerrupts(काष्ठा hfi1_devdata *dd)
अणु
	पूर्णांक ret;

	/* mask all पूर्णांकerrupts */
	set_पूर्णांकr_bits(dd, IS_FIRST_SOURCE, IS_LAST_SOURCE, false);

	/* clear all pending पूर्णांकerrupts */
	clear_all_पूर्णांकerrupts(dd);

	/* reset general handler mask, chip MSI-X mappings */
	reset_पूर्णांकerrupts(dd);

	/* ask क्रम MSI-X पूर्णांकerrupts */
	ret = msix_initialize(dd);
	अगर (ret)
		वापस ret;

	ret = msix_request_irqs(dd);
	अगर (ret)
		msix_clean_up_पूर्णांकerrupts(dd);

	वापस ret;
पूर्ण

/*
 * Set up context values in dd.  Sets:
 *
 *	num_rcv_contexts - number of contexts being used
 *	n_krcv_queues - number of kernel contexts
 *	first_dyn_alloc_ctxt - first dynamically allocated context
 *                             in array of contexts
 *	मुक्तctxts  - number of मुक्त user contexts
 *	num_send_contexts - number of PIO send contexts being used
 *	num_netdev_contexts - number of contexts reserved क्रम netdev
 */
अटल पूर्णांक set_up_context_variables(काष्ठा hfi1_devdata *dd)
अणु
	अचिन्हित दीर्घ num_kernel_contexts;
	u16 num_netdev_contexts;
	पूर्णांक ret;
	अचिन्हित ngroups;
	पूर्णांक rmt_count;
	पूर्णांक user_rmt_reduced;
	u32 n_usr_ctxts;
	u32 send_contexts = chip_send_contexts(dd);
	u32 rcv_contexts = chip_rcv_contexts(dd);

	/*
	 * Kernel receive contexts:
	 * - Context 0 - control context (VL15/multicast/error)
	 * - Context 1 - first kernel context
	 * - Context 2 - second kernel context
	 * ...
	 */
	अगर (n_krcvqs)
		/*
		 * n_krcvqs is the sum of module parameter kernel receive
		 * contexts, krcvqs[].  It करोes not include the control
		 * context, so add that.
		 */
		num_kernel_contexts = n_krcvqs + 1;
	अन्यथा
		num_kernel_contexts = DEFAULT_KRCVQS + 1;
	/*
	 * Every kernel receive context needs an ACK send context.
	 * one send context is allocated क्रम each VLअणु0-7पूर्ण and VL15
	 */
	अगर (num_kernel_contexts > (send_contexts - num_vls - 1)) अणु
		dd_dev_err(dd,
			   "Reducing # kernel rcv contexts to: %d, from %lu\n",
			   send_contexts - num_vls - 1,
			   num_kernel_contexts);
		num_kernel_contexts = send_contexts - num_vls - 1;
	पूर्ण

	/*
	 * User contexts:
	 *	- शेष to 1 user context per real (non-HT) CPU core अगर
	 *	  num_user_contexts is negative
	 */
	अगर (num_user_contexts < 0)
		n_usr_ctxts = cpumask_weight(&node_affinity.real_cpu_mask);
	अन्यथा
		n_usr_ctxts = num_user_contexts;
	/*
	 * Adjust the counts given a global max.
	 */
	अगर (num_kernel_contexts + n_usr_ctxts > rcv_contexts) अणु
		dd_dev_err(dd,
			   "Reducing # user receive contexts to: %u, from %u\n",
			   (u32)(rcv_contexts - num_kernel_contexts),
			   n_usr_ctxts);
		/* recalculate */
		n_usr_ctxts = rcv_contexts - num_kernel_contexts;
	पूर्ण

	num_netdev_contexts =
		hfi1_num_netdev_contexts(dd, rcv_contexts -
					 (num_kernel_contexts + n_usr_ctxts),
					 &node_affinity.real_cpu_mask);
	/*
	 * The RMT entries are currently allocated as shown below:
	 * 1. QOS (0 to 128 entries);
	 * 2. FECN (num_kernel_context - 1 + num_user_contexts +
	 *    num_netdev_contexts);
	 * 3. netdev (num_netdev_contexts).
	 * It should be noted that FECN oversubscribe num_netdev_contexts
	 * entries of RMT because both netdev and PSM could allocate any receive
	 * context between dd->first_dyn_alloc_text and dd->num_rcv_contexts,
	 * and PSM FECN must reserve an RMT entry क्रम each possible PSM receive
	 * context.
	 */
	rmt_count = qos_rmt_entries(dd, शून्य, शून्य) + (num_netdev_contexts * 2);
	अगर (HFI1_CAP_IS_KSET(TID_RDMA))
		rmt_count += num_kernel_contexts - 1;
	अगर (rmt_count + n_usr_ctxts > NUM_MAP_ENTRIES) अणु
		user_rmt_reduced = NUM_MAP_ENTRIES - rmt_count;
		dd_dev_err(dd,
			   "RMT size is reducing the number of user receive contexts from %u to %d\n",
			   n_usr_ctxts,
			   user_rmt_reduced);
		/* recalculate */
		n_usr_ctxts = user_rmt_reduced;
	पूर्ण

	/* the first N are kernel contexts, the rest are user/netdev contexts */
	dd->num_rcv_contexts =
		num_kernel_contexts + n_usr_ctxts + num_netdev_contexts;
	dd->n_krcv_queues = num_kernel_contexts;
	dd->first_dyn_alloc_ctxt = num_kernel_contexts;
	dd->num_netdev_contexts = num_netdev_contexts;
	dd->num_user_contexts = n_usr_ctxts;
	dd->मुक्तctxts = n_usr_ctxts;
	dd_dev_info(dd,
		    "rcv contexts: chip %d, used %d (kernel %d, netdev %u, user %u)\n",
		    rcv_contexts,
		    (पूर्णांक)dd->num_rcv_contexts,
		    (पूर्णांक)dd->n_krcv_queues,
		    dd->num_netdev_contexts,
		    dd->num_user_contexts);

	/*
	 * Receive array allocation:
	 *   All RcvArray entries are भागided पूर्णांकo groups of 8. This
	 *   is required by the hardware and will speed up ग_लिखोs to
	 *   consecutive entries by using ग_लिखो-combining of the entire
	 *   cacheline.
	 *
	 *   The number of groups are evenly भागided among all contexts.
	 *   any left over groups will be given to the first N user
	 *   contexts.
	 */
	dd->rcv_entries.group_size = RCV_INCREMENT;
	ngroups = chip_rcv_array_count(dd) / dd->rcv_entries.group_size;
	dd->rcv_entries.ngroups = ngroups / dd->num_rcv_contexts;
	dd->rcv_entries.nctxt_extra = ngroups -
		(dd->num_rcv_contexts * dd->rcv_entries.ngroups);
	dd_dev_info(dd, "RcvArray groups %u, ctxts extra %u\n",
		    dd->rcv_entries.ngroups,
		    dd->rcv_entries.nctxt_extra);
	अगर (dd->rcv_entries.ngroups * dd->rcv_entries.group_size >
	    MAX_EAGER_ENTRIES * 2) अणु
		dd->rcv_entries.ngroups = (MAX_EAGER_ENTRIES * 2) /
			dd->rcv_entries.group_size;
		dd_dev_info(dd,
			    "RcvArray group count too high, change to %u\n",
			    dd->rcv_entries.ngroups);
		dd->rcv_entries.nctxt_extra = 0;
	पूर्ण
	/*
	 * PIO send contexts
	 */
	ret = init_sc_pools_and_sizes(dd);
	अगर (ret >= 0) अणु	/* success */
		dd->num_send_contexts = ret;
		dd_dev_info(
			dd,
			"send contexts: chip %d, used %d (kernel %d, ack %d, user %d, vl15 %d)\n",
			send_contexts,
			dd->num_send_contexts,
			dd->sc_sizes[SC_KERNEL].count,
			dd->sc_sizes[SC_ACK].count,
			dd->sc_sizes[SC_USER].count,
			dd->sc_sizes[SC_VL15].count);
		ret = 0;	/* success */
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Set the device/port partition key table. The MAD code
 * will ensure that, at least, the partial management
 * partition key is present in the table.
 */
अटल व्योम set_partition_keys(काष्ठा hfi1_pportdata *ppd)
अणु
	काष्ठा hfi1_devdata *dd = ppd->dd;
	u64 reg = 0;
	पूर्णांक i;

	dd_dev_info(dd, "Setting partition keys\n");
	क्रम (i = 0; i < hfi1_get_npkeys(dd); i++) अणु
		reg |= (ppd->pkeys[i] &
			RCV_PARTITION_KEY_PARTITION_KEY_A_MASK) <<
			((i % 4) *
			 RCV_PARTITION_KEY_PARTITION_KEY_B_SHIFT);
		/* Each रेजिस्टर holds 4 PKey values. */
		अगर ((i % 4) == 3) अणु
			ग_लिखो_csr(dd, RCV_PARTITION_KEY +
				  ((i - 3) * 2), reg);
			reg = 0;
		पूर्ण
	पूर्ण

	/* Always enable HW pkeys check when pkeys table is set */
	add_rcvctrl(dd, RCV_CTRL_RCV_PARTITION_KEY_ENABLE_SMASK);
पूर्ण

/*
 * These CSRs and memories are uninitialized on reset and must be
 * written beक्रमe पढ़ोing to set the ECC/parity bits.
 *
 * NOTE: All user context CSRs that are not mmaped ग_लिखो-only
 * (e.g. the TID flows) must be initialized even अगर the driver never
 * पढ़ोs them.
 */
अटल व्योम ग_लिखो_uninitialized_csrs_and_memories(काष्ठा hfi1_devdata *dd)
अणु
	पूर्णांक i, j;

	/* CceIntMap */
	क्रम (i = 0; i < CCE_NUM_INT_MAP_CSRS; i++)
		ग_लिखो_csr(dd, CCE_INT_MAP + (8 * i), 0);

	/* SendCtxtCreditReturnAddr */
	क्रम (i = 0; i < chip_send_contexts(dd); i++)
		ग_लिखो_kctxt_csr(dd, i, SEND_CTXT_CREDIT_RETURN_ADDR, 0);

	/* PIO Send buffers */
	/* SDMA Send buffers */
	/*
	 * These are not normally पढ़ो, and (presently) have no method
	 * to be पढ़ो, so are not pre-initialized
	 */

	/* RcvHdrAddr */
	/* RcvHdrTailAddr */
	/* RcvTidFlowTable */
	क्रम (i = 0; i < chip_rcv_contexts(dd); i++) अणु
		ग_लिखो_kctxt_csr(dd, i, RCV_HDR_ADDR, 0);
		ग_लिखो_kctxt_csr(dd, i, RCV_HDR_TAIL_ADDR, 0);
		क्रम (j = 0; j < RXE_NUM_TID_FLOWS; j++)
			ग_लिखो_uctxt_csr(dd, i, RCV_TID_FLOW_TABLE + (8 * j), 0);
	पूर्ण

	/* RcvArray */
	क्रम (i = 0; i < chip_rcv_array_count(dd); i++)
		hfi1_put_tid(dd, i, PT_INVALID_FLUSH, 0, 0);

	/* RcvQPMapTable */
	क्रम (i = 0; i < 32; i++)
		ग_लिखो_csr(dd, RCV_QP_MAP_TABLE + (8 * i), 0);
पूर्ण

/*
 * Use the ctrl_bits in CceCtrl to clear the status_bits in CceStatus.
 */
अटल व्योम clear_cce_status(काष्ठा hfi1_devdata *dd, u64 status_bits,
			     u64 ctrl_bits)
अणु
	अचिन्हित दीर्घ समयout;
	u64 reg;

	/* is the condition present? */
	reg = पढ़ो_csr(dd, CCE_STATUS);
	अगर ((reg & status_bits) == 0)
		वापस;

	/* clear the condition */
	ग_लिखो_csr(dd, CCE_CTRL, ctrl_bits);

	/* रुको क्रम the condition to clear */
	समयout = jअगरfies + msecs_to_jअगरfies(CCE_STATUS_TIMEOUT);
	जबतक (1) अणु
		reg = पढ़ो_csr(dd, CCE_STATUS);
		अगर ((reg & status_bits) == 0)
			वापस;
		अगर (समय_after(jअगरfies, समयout)) अणु
			dd_dev_err(dd,
				   "Timeout waiting for CceStatus to clear bits 0x%llx, remaining 0x%llx\n",
				   status_bits, reg & status_bits);
			वापस;
		पूर्ण
		udelay(1);
	पूर्ण
पूर्ण

/* set CCE CSRs to chip reset शेषs */
अटल व्योम reset_cce_csrs(काष्ठा hfi1_devdata *dd)
अणु
	पूर्णांक i;

	/* CCE_REVISION पढ़ो-only */
	/* CCE_REVISION2 पढ़ो-only */
	/* CCE_CTRL - bits clear स्वतःmatically */
	/* CCE_STATUS पढ़ो-only, use CceCtrl to clear */
	clear_cce_status(dd, ALL_FROZE, CCE_CTRL_SPC_UNFREEZE_SMASK);
	clear_cce_status(dd, ALL_TXE_PAUSE, CCE_CTRL_TXE_RESUME_SMASK);
	clear_cce_status(dd, ALL_RXE_PAUSE, CCE_CTRL_RXE_RESUME_SMASK);
	क्रम (i = 0; i < CCE_NUM_SCRATCH; i++)
		ग_लिखो_csr(dd, CCE_SCRATCH + (8 * i), 0);
	/* CCE_ERR_STATUS पढ़ो-only */
	ग_लिखो_csr(dd, CCE_ERR_MASK, 0);
	ग_लिखो_csr(dd, CCE_ERR_CLEAR, ~0ull);
	/* CCE_ERR_FORCE leave alone */
	क्रम (i = 0; i < CCE_NUM_32_BIT_COUNTERS; i++)
		ग_लिखो_csr(dd, CCE_COUNTER_ARRAY32 + (8 * i), 0);
	ग_लिखो_csr(dd, CCE_DC_CTRL, CCE_DC_CTRL_RESETCSR);
	/* CCE_PCIE_CTRL leave alone */
	क्रम (i = 0; i < CCE_NUM_MSIX_VECTORS; i++) अणु
		ग_लिखो_csr(dd, CCE_MSIX_TABLE_LOWER + (8 * i), 0);
		ग_लिखो_csr(dd, CCE_MSIX_TABLE_UPPER + (8 * i),
			  CCE_MSIX_TABLE_UPPER_RESETCSR);
	पूर्ण
	क्रम (i = 0; i < CCE_NUM_MSIX_PBAS; i++) अणु
		/* CCE_MSIX_PBA पढ़ो-only */
		ग_लिखो_csr(dd, CCE_MSIX_INT_GRANTED, ~0ull);
		ग_लिखो_csr(dd, CCE_MSIX_VEC_CLR_WITHOUT_INT, ~0ull);
	पूर्ण
	क्रम (i = 0; i < CCE_NUM_INT_MAP_CSRS; i++)
		ग_लिखो_csr(dd, CCE_INT_MAP, 0);
	क्रम (i = 0; i < CCE_NUM_INT_CSRS; i++) अणु
		/* CCE_INT_STATUS पढ़ो-only */
		ग_लिखो_csr(dd, CCE_INT_MASK + (8 * i), 0);
		ग_लिखो_csr(dd, CCE_INT_CLEAR + (8 * i), ~0ull);
		/* CCE_INT_FORCE leave alone */
		/* CCE_INT_BLOCKED पढ़ो-only */
	पूर्ण
	क्रम (i = 0; i < CCE_NUM_32_BIT_INT_COUNTERS; i++)
		ग_लिखो_csr(dd, CCE_INT_COUNTER_ARRAY32 + (8 * i), 0);
पूर्ण

/* set MISC CSRs to chip reset शेषs */
अटल व्योम reset_misc_csrs(काष्ठा hfi1_devdata *dd)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 32; i++) अणु
		ग_लिखो_csr(dd, MISC_CFG_RSA_R2 + (8 * i), 0);
		ग_लिखो_csr(dd, MISC_CFG_RSA_SIGNATURE + (8 * i), 0);
		ग_लिखो_csr(dd, MISC_CFG_RSA_MODULUS + (8 * i), 0);
	पूर्ण
	/*
	 * MISC_CFG_SHA_PRELOAD leave alone - always पढ़ोs 0 and can
	 * only be written 128-byte chunks
	 */
	/* init RSA engine to clear lingering errors */
	ग_लिखो_csr(dd, MISC_CFG_RSA_CMD, 1);
	ग_लिखो_csr(dd, MISC_CFG_RSA_MU, 0);
	ग_लिखो_csr(dd, MISC_CFG_FW_CTRL, 0);
	/* MISC_STS_8051_DIGEST पढ़ो-only */
	/* MISC_STS_SBM_DIGEST पढ़ो-only */
	/* MISC_STS_PCIE_DIGEST पढ़ो-only */
	/* MISC_STS_FAB_DIGEST पढ़ो-only */
	/* MISC_ERR_STATUS पढ़ो-only */
	ग_लिखो_csr(dd, MISC_ERR_MASK, 0);
	ग_लिखो_csr(dd, MISC_ERR_CLEAR, ~0ull);
	/* MISC_ERR_FORCE leave alone */
पूर्ण

/* set TXE CSRs to chip reset शेषs */
अटल व्योम reset_txe_csrs(काष्ठा hfi1_devdata *dd)
अणु
	पूर्णांक i;

	/*
	 * TXE Kernel CSRs
	 */
	ग_लिखो_csr(dd, SEND_CTRL, 0);
	__cm_reset(dd, 0);	/* reset CM पूर्णांकernal state */
	/* SEND_CONTEXTS पढ़ो-only */
	/* SEND_DMA_ENGINES पढ़ो-only */
	/* SEND_PIO_MEM_SIZE पढ़ो-only */
	/* SEND_DMA_MEM_SIZE पढ़ो-only */
	ग_लिखो_csr(dd, SEND_HIGH_PRIORITY_LIMIT, 0);
	pio_reset_all(dd);	/* SEND_PIO_INIT_CTXT */
	/* SEND_PIO_ERR_STATUS पढ़ो-only */
	ग_लिखो_csr(dd, SEND_PIO_ERR_MASK, 0);
	ग_लिखो_csr(dd, SEND_PIO_ERR_CLEAR, ~0ull);
	/* SEND_PIO_ERR_FORCE leave alone */
	/* SEND_DMA_ERR_STATUS पढ़ो-only */
	ग_लिखो_csr(dd, SEND_DMA_ERR_MASK, 0);
	ग_लिखो_csr(dd, SEND_DMA_ERR_CLEAR, ~0ull);
	/* SEND_DMA_ERR_FORCE leave alone */
	/* SEND_EGRESS_ERR_STATUS पढ़ो-only */
	ग_लिखो_csr(dd, SEND_EGRESS_ERR_MASK, 0);
	ग_लिखो_csr(dd, SEND_EGRESS_ERR_CLEAR, ~0ull);
	/* SEND_EGRESS_ERR_FORCE leave alone */
	ग_लिखो_csr(dd, SEND_BTH_QP, 0);
	ग_लिखो_csr(dd, SEND_STATIC_RATE_CONTROL, 0);
	ग_लिखो_csr(dd, SEND_SC2VLT0, 0);
	ग_लिखो_csr(dd, SEND_SC2VLT1, 0);
	ग_लिखो_csr(dd, SEND_SC2VLT2, 0);
	ग_लिखो_csr(dd, SEND_SC2VLT3, 0);
	ग_लिखो_csr(dd, SEND_LEN_CHECK0, 0);
	ग_लिखो_csr(dd, SEND_LEN_CHECK1, 0);
	/* SEND_ERR_STATUS पढ़ो-only */
	ग_लिखो_csr(dd, SEND_ERR_MASK, 0);
	ग_लिखो_csr(dd, SEND_ERR_CLEAR, ~0ull);
	/* SEND_ERR_FORCE पढ़ो-only */
	क्रम (i = 0; i < VL_ARB_LOW_PRIO_TABLE_SIZE; i++)
		ग_लिखो_csr(dd, SEND_LOW_PRIORITY_LIST + (8 * i), 0);
	क्रम (i = 0; i < VL_ARB_HIGH_PRIO_TABLE_SIZE; i++)
		ग_लिखो_csr(dd, SEND_HIGH_PRIORITY_LIST + (8 * i), 0);
	क्रम (i = 0; i < chip_send_contexts(dd) / NUM_CONTEXTS_PER_SET; i++)
		ग_लिखो_csr(dd, SEND_CONTEXT_SET_CTRL + (8 * i), 0);
	क्रम (i = 0; i < TXE_NUM_32_BIT_COUNTER; i++)
		ग_लिखो_csr(dd, SEND_COUNTER_ARRAY32 + (8 * i), 0);
	क्रम (i = 0; i < TXE_NUM_64_BIT_COUNTER; i++)
		ग_लिखो_csr(dd, SEND_COUNTER_ARRAY64 + (8 * i), 0);
	ग_लिखो_csr(dd, SEND_CM_CTRL, SEND_CM_CTRL_RESETCSR);
	ग_लिखो_csr(dd, SEND_CM_GLOBAL_CREDIT, SEND_CM_GLOBAL_CREDIT_RESETCSR);
	/* SEND_CM_CREDIT_USED_STATUS पढ़ो-only */
	ग_लिखो_csr(dd, SEND_CM_TIMER_CTRL, 0);
	ग_लिखो_csr(dd, SEND_CM_LOCAL_AU_TABLE0_TO3, 0);
	ग_लिखो_csr(dd, SEND_CM_LOCAL_AU_TABLE4_TO7, 0);
	ग_लिखो_csr(dd, SEND_CM_REMOTE_AU_TABLE0_TO3, 0);
	ग_लिखो_csr(dd, SEND_CM_REMOTE_AU_TABLE4_TO7, 0);
	क्रम (i = 0; i < TXE_NUM_DATA_VL; i++)
		ग_लिखो_csr(dd, SEND_CM_CREDIT_VL + (8 * i), 0);
	ग_लिखो_csr(dd, SEND_CM_CREDIT_VL15, 0);
	/* SEND_CM_CREDIT_USED_VL पढ़ो-only */
	/* SEND_CM_CREDIT_USED_VL15 पढ़ो-only */
	/* SEND_EGRESS_CTXT_STATUS पढ़ो-only */
	/* SEND_EGRESS_SEND_DMA_STATUS पढ़ो-only */
	ग_लिखो_csr(dd, SEND_EGRESS_ERR_INFO, ~0ull);
	/* SEND_EGRESS_ERR_INFO पढ़ो-only */
	/* SEND_EGRESS_ERR_SOURCE पढ़ो-only */

	/*
	 * TXE Per-Context CSRs
	 */
	क्रम (i = 0; i < chip_send_contexts(dd); i++) अणु
		ग_लिखो_kctxt_csr(dd, i, SEND_CTXT_CTRL, 0);
		ग_लिखो_kctxt_csr(dd, i, SEND_CTXT_CREDIT_CTRL, 0);
		ग_लिखो_kctxt_csr(dd, i, SEND_CTXT_CREDIT_RETURN_ADDR, 0);
		ग_लिखो_kctxt_csr(dd, i, SEND_CTXT_CREDIT_FORCE, 0);
		ग_लिखो_kctxt_csr(dd, i, SEND_CTXT_ERR_MASK, 0);
		ग_लिखो_kctxt_csr(dd, i, SEND_CTXT_ERR_CLEAR, ~0ull);
		ग_लिखो_kctxt_csr(dd, i, SEND_CTXT_CHECK_ENABLE, 0);
		ग_लिखो_kctxt_csr(dd, i, SEND_CTXT_CHECK_VL, 0);
		ग_लिखो_kctxt_csr(dd, i, SEND_CTXT_CHECK_JOB_KEY, 0);
		ग_लिखो_kctxt_csr(dd, i, SEND_CTXT_CHECK_PARTITION_KEY, 0);
		ग_लिखो_kctxt_csr(dd, i, SEND_CTXT_CHECK_SLID, 0);
		ग_लिखो_kctxt_csr(dd, i, SEND_CTXT_CHECK_OPCODE, 0);
	पूर्ण

	/*
	 * TXE Per-SDMA CSRs
	 */
	क्रम (i = 0; i < chip_sdma_engines(dd); i++) अणु
		ग_लिखो_kctxt_csr(dd, i, SEND_DMA_CTRL, 0);
		/* SEND_DMA_STATUS पढ़ो-only */
		ग_लिखो_kctxt_csr(dd, i, SEND_DMA_BASE_ADDR, 0);
		ग_लिखो_kctxt_csr(dd, i, SEND_DMA_LEN_GEN, 0);
		ग_लिखो_kctxt_csr(dd, i, SEND_DMA_TAIL, 0);
		/* SEND_DMA_HEAD पढ़ो-only */
		ग_लिखो_kctxt_csr(dd, i, SEND_DMA_HEAD_ADDR, 0);
		ग_लिखो_kctxt_csr(dd, i, SEND_DMA_PRIORITY_THLD, 0);
		/* SEND_DMA_IDLE_CNT पढ़ो-only */
		ग_लिखो_kctxt_csr(dd, i, SEND_DMA_RELOAD_CNT, 0);
		ग_लिखो_kctxt_csr(dd, i, SEND_DMA_DESC_CNT, 0);
		/* SEND_DMA_DESC_FETCHED_CNT पढ़ो-only */
		/* SEND_DMA_ENG_ERR_STATUS पढ़ो-only */
		ग_लिखो_kctxt_csr(dd, i, SEND_DMA_ENG_ERR_MASK, 0);
		ग_लिखो_kctxt_csr(dd, i, SEND_DMA_ENG_ERR_CLEAR, ~0ull);
		/* SEND_DMA_ENG_ERR_FORCE leave alone */
		ग_लिखो_kctxt_csr(dd, i, SEND_DMA_CHECK_ENABLE, 0);
		ग_लिखो_kctxt_csr(dd, i, SEND_DMA_CHECK_VL, 0);
		ग_लिखो_kctxt_csr(dd, i, SEND_DMA_CHECK_JOB_KEY, 0);
		ग_लिखो_kctxt_csr(dd, i, SEND_DMA_CHECK_PARTITION_KEY, 0);
		ग_लिखो_kctxt_csr(dd, i, SEND_DMA_CHECK_SLID, 0);
		ग_लिखो_kctxt_csr(dd, i, SEND_DMA_CHECK_OPCODE, 0);
		ग_लिखो_kctxt_csr(dd, i, SEND_DMA_MEMORY, 0);
	पूर्ण
पूर्ण

/*
 * Expect on entry:
 * o Packet ingress is disabled, i.e. RcvCtrl.RcvPortEnable == 0
 */
अटल व्योम init_rbufs(काष्ठा hfi1_devdata *dd)
अणु
	u64 reg;
	पूर्णांक count;

	/*
	 * Wait क्रम DMA to stop: RxRbufPktPending and RxPktInProgress are
	 * clear.
	 */
	count = 0;
	जबतक (1) अणु
		reg = पढ़ो_csr(dd, RCV_STATUS);
		अगर ((reg & (RCV_STATUS_RX_RBUF_PKT_PENDING_SMASK
			    | RCV_STATUS_RX_PKT_IN_PROGRESS_SMASK)) == 0)
			अवरोध;
		/*
		 * Give up after 1ms - maximum रुको समय.
		 *
		 * RBuf size is 136KiB.  Slowest possible is PCIe Gen1 x1 at
		 * 250MB/s bandwidth.  Lower rate to 66% क्रम overhead to get:
		 *	136 KB / (66% * 250MB/s) = 844us
		 */
		अगर (count++ > 500) अणु
			dd_dev_err(dd,
				   "%s: in-progress DMA not clearing: RcvStatus 0x%llx, continuing\n",
				   __func__, reg);
			अवरोध;
		पूर्ण
		udelay(2); /* करो not busy-रुको the CSR */
	पूर्ण

	/* start the init - expect RcvCtrl to be 0 */
	ग_लिखो_csr(dd, RCV_CTRL, RCV_CTRL_RX_RBUF_INIT_SMASK);

	/*
	 * Read to क्रमce the ग_लिखो of Rcvtrl.RxRbufInit.  There is a brief
	 * period after the ग_लिखो beक्रमe RcvStatus.RxRbufInitDone is valid.
	 * The delay in the first run through the loop below is sufficient and
	 * required beक्रमe the first पढ़ो of RcvStatus.RxRbufInपूर्णांकDone.
	 */
	पढ़ो_csr(dd, RCV_CTRL);

	/* रुको क्रम the init to finish */
	count = 0;
	जबतक (1) अणु
		/* delay is required first समय through - see above */
		udelay(2); /* करो not busy-रुको the CSR */
		reg = पढ़ो_csr(dd, RCV_STATUS);
		अगर (reg & (RCV_STATUS_RX_RBUF_INIT_DONE_SMASK))
			अवरोध;

		/* give up after 100us - slowest possible at 33MHz is 73us */
		अगर (count++ > 50) अणु
			dd_dev_err(dd,
				   "%s: RcvStatus.RxRbufInit not set, continuing\n",
				   __func__);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/* set RXE CSRs to chip reset शेषs */
अटल व्योम reset_rxe_csrs(काष्ठा hfi1_devdata *dd)
अणु
	पूर्णांक i, j;

	/*
	 * RXE Kernel CSRs
	 */
	ग_लिखो_csr(dd, RCV_CTRL, 0);
	init_rbufs(dd);
	/* RCV_STATUS पढ़ो-only */
	/* RCV_CONTEXTS पढ़ो-only */
	/* RCV_ARRAY_CNT पढ़ो-only */
	/* RCV_BUF_SIZE पढ़ो-only */
	ग_लिखो_csr(dd, RCV_BTH_QP, 0);
	ग_लिखो_csr(dd, RCV_MULTICAST, 0);
	ग_लिखो_csr(dd, RCV_BYPASS, 0);
	ग_लिखो_csr(dd, RCV_VL15, 0);
	/* this is a clear-करोwn */
	ग_लिखो_csr(dd, RCV_ERR_INFO,
		  RCV_ERR_INFO_RCV_EXCESS_BUFFER_OVERRUN_SMASK);
	/* RCV_ERR_STATUS पढ़ो-only */
	ग_लिखो_csr(dd, RCV_ERR_MASK, 0);
	ग_लिखो_csr(dd, RCV_ERR_CLEAR, ~0ull);
	/* RCV_ERR_FORCE leave alone */
	क्रम (i = 0; i < 32; i++)
		ग_लिखो_csr(dd, RCV_QP_MAP_TABLE + (8 * i), 0);
	क्रम (i = 0; i < 4; i++)
		ग_लिखो_csr(dd, RCV_PARTITION_KEY + (8 * i), 0);
	क्रम (i = 0; i < RXE_NUM_32_BIT_COUNTERS; i++)
		ग_लिखो_csr(dd, RCV_COUNTER_ARRAY32 + (8 * i), 0);
	क्रम (i = 0; i < RXE_NUM_64_BIT_COUNTERS; i++)
		ग_लिखो_csr(dd, RCV_COUNTER_ARRAY64 + (8 * i), 0);
	क्रम (i = 0; i < RXE_NUM_RSM_INSTANCES; i++)
		clear_rsm_rule(dd, i);
	क्रम (i = 0; i < 32; i++)
		ग_लिखो_csr(dd, RCV_RSM_MAP_TABLE + (8 * i), 0);

	/*
	 * RXE Kernel and User Per-Context CSRs
	 */
	क्रम (i = 0; i < chip_rcv_contexts(dd); i++) अणु
		/* kernel */
		ग_लिखो_kctxt_csr(dd, i, RCV_CTXT_CTRL, 0);
		/* RCV_CTXT_STATUS पढ़ो-only */
		ग_लिखो_kctxt_csr(dd, i, RCV_EGR_CTRL, 0);
		ग_लिखो_kctxt_csr(dd, i, RCV_TID_CTRL, 0);
		ग_लिखो_kctxt_csr(dd, i, RCV_KEY_CTRL, 0);
		ग_लिखो_kctxt_csr(dd, i, RCV_HDR_ADDR, 0);
		ग_लिखो_kctxt_csr(dd, i, RCV_HDR_CNT, 0);
		ग_लिखो_kctxt_csr(dd, i, RCV_HDR_ENT_SIZE, 0);
		ग_लिखो_kctxt_csr(dd, i, RCV_HDR_SIZE, 0);
		ग_लिखो_kctxt_csr(dd, i, RCV_HDR_TAIL_ADDR, 0);
		ग_लिखो_kctxt_csr(dd, i, RCV_AVAIL_TIME_OUT, 0);
		ग_लिखो_kctxt_csr(dd, i, RCV_HDR_OVFL_CNT, 0);

		/* user */
		/* RCV_HDR_TAIL पढ़ो-only */
		ग_लिखो_uctxt_csr(dd, i, RCV_HDR_HEAD, 0);
		/* RCV_EGR_INDEX_TAIL पढ़ो-only */
		ग_लिखो_uctxt_csr(dd, i, RCV_EGR_INDEX_HEAD, 0);
		/* RCV_EGR_OFFSET_TAIL पढ़ो-only */
		क्रम (j = 0; j < RXE_NUM_TID_FLOWS; j++) अणु
			ग_लिखो_uctxt_csr(dd, i,
					RCV_TID_FLOW_TABLE + (8 * j), 0);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Set sc2vl tables.
 *
 * They घातer on to zeros, so to aव्योम send context errors
 * they need to be set:
 *
 * SC 0-7 -> VL 0-7 (respectively)
 * SC 15  -> VL 15
 * otherwise
 *        -> VL 0
 */
अटल व्योम init_sc2vl_tables(काष्ठा hfi1_devdata *dd)
अणु
	पूर्णांक i;
	/* init per architecture spec, स्थिरrained by hardware capability */

	/* HFI maps sent packets */
	ग_लिखो_csr(dd, SEND_SC2VLT0, SC2VL_VAL(
		0,
		0, 0, 1, 1,
		2, 2, 3, 3,
		4, 4, 5, 5,
		6, 6, 7, 7));
	ग_लिखो_csr(dd, SEND_SC2VLT1, SC2VL_VAL(
		1,
		8, 0, 9, 0,
		10, 0, 11, 0,
		12, 0, 13, 0,
		14, 0, 15, 15));
	ग_लिखो_csr(dd, SEND_SC2VLT2, SC2VL_VAL(
		2,
		16, 0, 17, 0,
		18, 0, 19, 0,
		20, 0, 21, 0,
		22, 0, 23, 0));
	ग_लिखो_csr(dd, SEND_SC2VLT3, SC2VL_VAL(
		3,
		24, 0, 25, 0,
		26, 0, 27, 0,
		28, 0, 29, 0,
		30, 0, 31, 0));

	/* DC maps received packets */
	ग_लिखो_csr(dd, DCC_CFG_SC_VL_TABLE_15_0, DC_SC_VL_VAL(
		15_0,
		0, 0, 1, 1,  2, 2,  3, 3,  4, 4,  5, 5,  6, 6,  7,  7,
		8, 0, 9, 0, 10, 0, 11, 0, 12, 0, 13, 0, 14, 0, 15, 15));
	ग_लिखो_csr(dd, DCC_CFG_SC_VL_TABLE_31_16, DC_SC_VL_VAL(
		31_16,
		16, 0, 17, 0, 18, 0, 19, 0, 20, 0, 21, 0, 22, 0, 23, 0,
		24, 0, 25, 0, 26, 0, 27, 0, 28, 0, 29, 0, 30, 0, 31, 0));

	/* initialize the cached sc2vl values consistently with h/w */
	क्रम (i = 0; i < 32; i++) अणु
		अगर (i < 8 || i == 15)
			*((u8 *)(dd->sc2vl) + i) = (u8)i;
		अन्यथा
			*((u8 *)(dd->sc2vl) + i) = 0;
	पूर्ण
पूर्ण

/*
 * Read chip sizes and then reset parts to sane, disabled, values.  We cannot
 * depend on the chip going through a घातer-on reset - a driver may be loaded
 * and unloaded many बार.
 *
 * Do not ग_लिखो any CSR values to the chip in this routine - there may be
 * a reset following the (possible) FLR in this routine.
 *
 */
अटल पूर्णांक init_chip(काष्ठा hfi1_devdata *dd)
अणु
	पूर्णांक i;
	पूर्णांक ret = 0;

	/*
	 * Put the HFI CSRs in a known state.
	 * Combine this with a DC reset.
	 *
	 * Stop the device from करोing anything जबतक we करो a
	 * reset.  We know there are no other active users of
	 * the device since we are now in अक्षरge.  Turn off
	 * off all outbound and inbound traffic and make sure
	 * the device करोes not generate any पूर्णांकerrupts.
	 */

	/* disable send contexts and SDMA engines */
	ग_लिखो_csr(dd, SEND_CTRL, 0);
	क्रम (i = 0; i < chip_send_contexts(dd); i++)
		ग_लिखो_kctxt_csr(dd, i, SEND_CTXT_CTRL, 0);
	क्रम (i = 0; i < chip_sdma_engines(dd); i++)
		ग_लिखो_kctxt_csr(dd, i, SEND_DMA_CTRL, 0);
	/* disable port (turn off RXE inbound traffic) and contexts */
	ग_लिखो_csr(dd, RCV_CTRL, 0);
	क्रम (i = 0; i < chip_rcv_contexts(dd); i++)
		ग_लिखो_csr(dd, RCV_CTXT_CTRL, 0);
	/* mask all पूर्णांकerrupt sources */
	क्रम (i = 0; i < CCE_NUM_INT_CSRS; i++)
		ग_लिखो_csr(dd, CCE_INT_MASK + (8 * i), 0ull);

	/*
	 * DC Reset: करो a full DC reset beक्रमe the रेजिस्टर clear.
	 * A recommended length of समय to hold is one CSR पढ़ो,
	 * so reपढ़ो the CceDcCtrl.  Then, hold the DC in reset
	 * across the clear.
	 */
	ग_लिखो_csr(dd, CCE_DC_CTRL, CCE_DC_CTRL_DC_RESET_SMASK);
	(व्योम)पढ़ो_csr(dd, CCE_DC_CTRL);

	अगर (use_flr) अणु
		/*
		 * A FLR will reset the SPC core and part of the PCIe.
		 * The parts that need to be restored have alपढ़ोy been
		 * saved.
		 */
		dd_dev_info(dd, "Resetting CSRs with FLR\n");

		/* करो the FLR, the DC reset will reमुख्य */
		pcie_flr(dd->pcidev);

		/* restore command and BARs */
		ret = restore_pci_variables(dd);
		अगर (ret) अणु
			dd_dev_err(dd, "%s: Could not restore PCI variables\n",
				   __func__);
			वापस ret;
		पूर्ण

		अगर (is_ax(dd)) अणु
			dd_dev_info(dd, "Resetting CSRs with FLR\n");
			pcie_flr(dd->pcidev);
			ret = restore_pci_variables(dd);
			अगर (ret) अणु
				dd_dev_err(dd, "%s: Could not restore PCI variables\n",
					   __func__);
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		dd_dev_info(dd, "Resetting CSRs with writes\n");
		reset_cce_csrs(dd);
		reset_txe_csrs(dd);
		reset_rxe_csrs(dd);
		reset_misc_csrs(dd);
	पूर्ण
	/* clear the DC reset */
	ग_लिखो_csr(dd, CCE_DC_CTRL, 0);

	/* Set the LED off */
	setextled(dd, 0);

	/*
	 * Clear the QSFP reset.
	 * An FLR enक्रमces a 0 on all out pins. The driver करोes not touch
	 * ASIC_QSFPn_OUT otherwise.  This leaves RESET_N low and
	 * anything plugged स्थिरantly in reset, अगर it pays attention
	 * to RESET_N.
	 * Prime examples of this are optical cables. Set all pins high.
	 * I2CCLK and I2CDAT will change per direction, and INT_N and
	 * MODPRS_N are input only and their value is ignored.
	 */
	ग_लिखो_csr(dd, ASIC_QSFP1_OUT, 0x1f);
	ग_लिखो_csr(dd, ASIC_QSFP2_OUT, 0x1f);
	init_chip_resources(dd);
	वापस ret;
पूर्ण

अटल व्योम init_early_variables(काष्ठा hfi1_devdata *dd)
अणु
	पूर्णांक i;

	/* assign link credit variables */
	dd->vau = CM_VAU;
	dd->link_credits = CM_GLOBAL_CREDITS;
	अगर (is_ax(dd))
		dd->link_credits--;
	dd->vcu = cu_to_vcu(hfi1_cu);
	/* enough room क्रम 8 MAD packets plus header - 17K */
	dd->vl15_init = (8 * (2048 + 128)) / vau_to_au(dd->vau);
	अगर (dd->vl15_init > dd->link_credits)
		dd->vl15_init = dd->link_credits;

	ग_लिखो_uninitialized_csrs_and_memories(dd);

	अगर (HFI1_CAP_IS_KSET(PKEY_CHECK))
		क्रम (i = 0; i < dd->num_pports; i++) अणु
			काष्ठा hfi1_pportdata *ppd = &dd->pport[i];

			set_partition_keys(ppd);
		पूर्ण
	init_sc2vl_tables(dd);
पूर्ण

अटल व्योम init_kdeth_qp(काष्ठा hfi1_devdata *dd)
अणु
	ग_लिखो_csr(dd, SEND_BTH_QP,
		  (RVT_KDETH_QP_PREFIX & SEND_BTH_QP_KDETH_QP_MASK) <<
		  SEND_BTH_QP_KDETH_QP_SHIFT);

	ग_लिखो_csr(dd, RCV_BTH_QP,
		  (RVT_KDETH_QP_PREFIX & RCV_BTH_QP_KDETH_QP_MASK) <<
		  RCV_BTH_QP_KDETH_QP_SHIFT);
पूर्ण

/**
 * hfi1_get_qp_map
 * @dd: device data
 * @idx: index to पढ़ो
 */
u8 hfi1_get_qp_map(काष्ठा hfi1_devdata *dd, u8 idx)
अणु
	u64 reg = पढ़ो_csr(dd, RCV_QP_MAP_TABLE + (idx / 8) * 8);

	reg >>= (idx % 8) * 8;
	वापस reg;
पूर्ण

/**
 * init_qpmap_table
 * @dd: device data
 * @first_ctxt: first context
 * @last_ctxt: first context
 *
 * This वापस sets the qpn mapping table that
 * is indexed by qpn[8:1].
 *
 * The routine will round robin the 256 settings
 * from first_ctxt to last_ctxt.
 *
 * The first/last looks ahead to having specialized
 * receive contexts क्रम mgmt and bypass.  Normal
 * verbs traffic will assumed to be on a range
 * of receive contexts.
 */
अटल व्योम init_qpmap_table(काष्ठा hfi1_devdata *dd,
			     u32 first_ctxt,
			     u32 last_ctxt)
अणु
	u64 reg = 0;
	u64 regno = RCV_QP_MAP_TABLE;
	पूर्णांक i;
	u64 ctxt = first_ctxt;

	क्रम (i = 0; i < 256; i++) अणु
		reg |= ctxt << (8 * (i % 8));
		ctxt++;
		अगर (ctxt > last_ctxt)
			ctxt = first_ctxt;
		अगर (i % 8 == 7) अणु
			ग_लिखो_csr(dd, regno, reg);
			reg = 0;
			regno += 8;
		पूर्ण
	पूर्ण

	add_rcvctrl(dd, RCV_CTRL_RCV_QP_MAP_ENABLE_SMASK
			| RCV_CTRL_RCV_BYPASS_ENABLE_SMASK);
पूर्ण

काष्ठा rsm_map_table अणु
	u64 map[NUM_MAP_REGS];
	अचिन्हित पूर्णांक used;
पूर्ण;

काष्ठा rsm_rule_data अणु
	u8 offset;
	u8 pkt_type;
	u32 field1_off;
	u32 field2_off;
	u32 index1_off;
	u32 index1_width;
	u32 index2_off;
	u32 index2_width;
	u32 mask1;
	u32 value1;
	u32 mask2;
	u32 value2;
पूर्ण;

/*
 * Return an initialized RMT map table क्रम users to fill in.  OK अगर it
 * वापसs शून्य, indicating no table.
 */
अटल काष्ठा rsm_map_table *alloc_rsm_map_table(काष्ठा hfi1_devdata *dd)
अणु
	काष्ठा rsm_map_table *rmt;
	u8 rxcontext = is_ax(dd) ? 0 : 0xff;  /* 0 is शेष अगर a0 ver. */

	rmt = kदो_स्मृति(माप(*rmt), GFP_KERNEL);
	अगर (rmt) अणु
		स_रखो(rmt->map, rxcontext, माप(rmt->map));
		rmt->used = 0;
	पूर्ण

	वापस rmt;
पूर्ण

/*
 * Write the final RMT map table to the chip and मुक्त the table.  OK अगर
 * table is शून्य.
 */
अटल व्योम complete_rsm_map_table(काष्ठा hfi1_devdata *dd,
				   काष्ठा rsm_map_table *rmt)
अणु
	पूर्णांक i;

	अगर (rmt) अणु
		/* ग_लिखो table to chip */
		क्रम (i = 0; i < NUM_MAP_REGS; i++)
			ग_लिखो_csr(dd, RCV_RSM_MAP_TABLE + (8 * i), rmt->map[i]);

		/* enable RSM */
		add_rcvctrl(dd, RCV_CTRL_RCV_RSM_ENABLE_SMASK);
	पूर्ण
पूर्ण

/* Is a receive side mapping rule */
अटल bool has_rsm_rule(काष्ठा hfi1_devdata *dd, u8 rule_index)
अणु
	वापस पढ़ो_csr(dd, RCV_RSM_CFG + (8 * rule_index)) != 0;
पूर्ण

/*
 * Add a receive side mapping rule.
 */
अटल व्योम add_rsm_rule(काष्ठा hfi1_devdata *dd, u8 rule_index,
			 काष्ठा rsm_rule_data *rrd)
अणु
	ग_लिखो_csr(dd, RCV_RSM_CFG + (8 * rule_index),
		  (u64)rrd->offset << RCV_RSM_CFG_OFFSET_SHIFT |
		  1ull << rule_index | /* enable bit */
		  (u64)rrd->pkt_type << RCV_RSM_CFG_PACKET_TYPE_SHIFT);
	ग_लिखो_csr(dd, RCV_RSM_SELECT + (8 * rule_index),
		  (u64)rrd->field1_off << RCV_RSM_SELECT_FIELD1_OFFSET_SHIFT |
		  (u64)rrd->field2_off << RCV_RSM_SELECT_FIELD2_OFFSET_SHIFT |
		  (u64)rrd->index1_off << RCV_RSM_SELECT_INDEX1_OFFSET_SHIFT |
		  (u64)rrd->index1_width << RCV_RSM_SELECT_INDEX1_WIDTH_SHIFT |
		  (u64)rrd->index2_off << RCV_RSM_SELECT_INDEX2_OFFSET_SHIFT |
		  (u64)rrd->index2_width << RCV_RSM_SELECT_INDEX2_WIDTH_SHIFT);
	ग_लिखो_csr(dd, RCV_RSM_MATCH + (8 * rule_index),
		  (u64)rrd->mask1 << RCV_RSM_MATCH_MASK1_SHIFT |
		  (u64)rrd->value1 << RCV_RSM_MATCH_VALUE1_SHIFT |
		  (u64)rrd->mask2 << RCV_RSM_MATCH_MASK2_SHIFT |
		  (u64)rrd->value2 << RCV_RSM_MATCH_VALUE2_SHIFT);
पूर्ण

/*
 * Clear a receive side mapping rule.
 */
अटल व्योम clear_rsm_rule(काष्ठा hfi1_devdata *dd, u8 rule_index)
अणु
	ग_लिखो_csr(dd, RCV_RSM_CFG + (8 * rule_index), 0);
	ग_लिखो_csr(dd, RCV_RSM_SELECT + (8 * rule_index), 0);
	ग_लिखो_csr(dd, RCV_RSM_MATCH + (8 * rule_index), 0);
पूर्ण

/* वापस the number of RSM map table entries that will be used क्रम QOS */
अटल पूर्णांक qos_rmt_entries(काष्ठा hfi1_devdata *dd, अचिन्हित पूर्णांक *mp,
			   अचिन्हित पूर्णांक *np)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक m, n;
	u8 max_by_vl = 0;

	/* is QOS active at all? */
	अगर (dd->n_krcv_queues <= MIN_KERNEL_KCTXTS ||
	    num_vls == 1 ||
	    krcvqsset <= 1)
		जाओ no_qos;

	/* determine bits क्रम qpn */
	क्रम (i = 0; i < min_t(अचिन्हित पूर्णांक, num_vls, krcvqsset); i++)
		अगर (krcvqs[i] > max_by_vl)
			max_by_vl = krcvqs[i];
	अगर (max_by_vl > 32)
		जाओ no_qos;
	m = ilog2(__roundup_घात_of_two(max_by_vl));

	/* determine bits क्रम vl */
	n = ilog2(__roundup_घात_of_two(num_vls));

	/* reject अगर too much is used */
	अगर ((m + n) > 7)
		जाओ no_qos;

	अगर (mp)
		*mp = m;
	अगर (np)
		*np = n;

	वापस 1 << (m + n);

no_qos:
	अगर (mp)
		*mp = 0;
	अगर (np)
		*np = 0;
	वापस 0;
पूर्ण

/**
 * init_qos - init RX qos
 * @dd: device data
 * @rmt: RSM map table
 *
 * This routine initializes Rule 0 and the RSM map table to implement
 * quality of service (qos).
 *
 * If all of the limit tests succeed, qos is applied based on the array
 * पूर्णांकerpretation of krcvqs where entry 0 is VL0.
 *
 * The number of vl bits (n) and the number of qpn bits (m) are computed to
 * feed both the RSM map table and the single rule.
 */
अटल व्योम init_qos(काष्ठा hfi1_devdata *dd, काष्ठा rsm_map_table *rmt)
अणु
	काष्ठा rsm_rule_data rrd;
	अचिन्हित qpns_per_vl, ctxt, i, qpn, n = 1, m;
	अचिन्हित पूर्णांक rmt_entries;
	u64 reg;

	अगर (!rmt)
		जाओ bail;
	rmt_entries = qos_rmt_entries(dd, &m, &n);
	अगर (rmt_entries == 0)
		जाओ bail;
	qpns_per_vl = 1 << m;

	/* enough room in the map table? */
	rmt_entries = 1 << (m + n);
	अगर (rmt->used + rmt_entries >= NUM_MAP_ENTRIES)
		जाओ bail;

	/* add qos entries to the the RSM map table */
	क्रम (i = 0, ctxt = FIRST_KERNEL_KCTXT; i < num_vls; i++) अणु
		अचिन्हित tctxt;

		क्रम (qpn = 0, tctxt = ctxt;
		     krcvqs[i] && qpn < qpns_per_vl; qpn++) अणु
			अचिन्हित idx, regoff, regidx;

			/* generate the index the hardware will produce */
			idx = rmt->used + ((qpn << n) ^ i);
			regoff = (idx % 8) * 8;
			regidx = idx / 8;
			/* replace शेष with context number */
			reg = rmt->map[regidx];
			reg &= ~(RCV_RSM_MAP_TABLE_RCV_CONTEXT_A_MASK
				<< regoff);
			reg |= (u64)(tctxt++) << regoff;
			rmt->map[regidx] = reg;
			अगर (tctxt == ctxt + krcvqs[i])
				tctxt = ctxt;
		पूर्ण
		ctxt += krcvqs[i];
	पूर्ण

	rrd.offset = rmt->used;
	rrd.pkt_type = 2;
	rrd.field1_off = LRH_BTH_MATCH_OFFSET;
	rrd.field2_off = LRH_SC_MATCH_OFFSET;
	rrd.index1_off = LRH_SC_SELECT_OFFSET;
	rrd.index1_width = n;
	rrd.index2_off = QPN_SELECT_OFFSET;
	rrd.index2_width = m + n;
	rrd.mask1 = LRH_BTH_MASK;
	rrd.value1 = LRH_BTH_VALUE;
	rrd.mask2 = LRH_SC_MASK;
	rrd.value2 = LRH_SC_VALUE;

	/* add rule 0 */
	add_rsm_rule(dd, RSM_INS_VERBS, &rrd);

	/* mark RSM map entries as used */
	rmt->used += rmt_entries;
	/* map everything अन्यथा to the mcast/err/vl15 context */
	init_qpmap_table(dd, HFI1_CTRL_CTXT, HFI1_CTRL_CTXT);
	dd->qos_shअगरt = n + 1;
	वापस;
bail:
	dd->qos_shअगरt = 1;
	init_qpmap_table(dd, FIRST_KERNEL_KCTXT, dd->n_krcv_queues - 1);
पूर्ण

अटल व्योम init_fecn_handling(काष्ठा hfi1_devdata *dd,
			       काष्ठा rsm_map_table *rmt)
अणु
	काष्ठा rsm_rule_data rrd;
	u64 reg;
	पूर्णांक i, idx, regoff, regidx, start;
	u8 offset;
	u32 total_cnt;

	अगर (HFI1_CAP_IS_KSET(TID_RDMA))
		/* Exclude context 0 */
		start = 1;
	अन्यथा
		start = dd->first_dyn_alloc_ctxt;

	total_cnt = dd->num_rcv_contexts - start;

	/* there needs to be enough room in the map table */
	अगर (rmt->used + total_cnt >= NUM_MAP_ENTRIES) अणु
		dd_dev_err(dd, "FECN handling disabled - too many contexts allocated\n");
		वापस;
	पूर्ण

	/*
	 * RSM will extract the destination context as an index पूर्णांकo the
	 * map table.  The destination contexts are a sequential block
	 * in the range start...num_rcv_contexts-1 (inclusive).
	 * Map entries are accessed as offset + extracted value.  Adjust
	 * the added offset so this sequence can be placed anywhere in
	 * the table - as दीर्घ as the entries themselves करो not wrap.
	 * There are only enough bits in offset क्रम the table size, so
	 * start with that to allow क्रम a "negative" offset.
	 */
	offset = (u8)(NUM_MAP_ENTRIES + rmt->used - start);

	क्रम (i = start, idx = rmt->used; i < dd->num_rcv_contexts;
	     i++, idx++) अणु
		/* replace with identity mapping */
		regoff = (idx % 8) * 8;
		regidx = idx / 8;
		reg = rmt->map[regidx];
		reg &= ~(RCV_RSM_MAP_TABLE_RCV_CONTEXT_A_MASK << regoff);
		reg |= (u64)i << regoff;
		rmt->map[regidx] = reg;
	पूर्ण

	/*
	 * For RSM पूर्णांकercept of Expected FECN packets:
	 * o packet type 0 - expected
	 * o match on F (bit 95), using select/match 1, and
	 * o match on SH (bit 133), using select/match 2.
	 *
	 * Use index 1 to extract the 8-bit receive context from DestQP
	 * (start at bit 64).  Use that as the RSM map table index.
	 */
	rrd.offset = offset;
	rrd.pkt_type = 0;
	rrd.field1_off = 95;
	rrd.field2_off = 133;
	rrd.index1_off = 64;
	rrd.index1_width = 8;
	rrd.index2_off = 0;
	rrd.index2_width = 0;
	rrd.mask1 = 1;
	rrd.value1 = 1;
	rrd.mask2 = 1;
	rrd.value2 = 1;

	/* add rule 1 */
	add_rsm_rule(dd, RSM_INS_FECN, &rrd);

	rmt->used += total_cnt;
पूर्ण

अटल अंतरभूत bool hfi1_is_rmt_full(पूर्णांक start, पूर्णांक spare)
अणु
	वापस (start + spare) > NUM_MAP_ENTRIES;
पूर्ण

अटल bool hfi1_netdev_update_rmt(काष्ठा hfi1_devdata *dd)
अणु
	u8 i, j;
	u8 ctx_id = 0;
	u64 reg;
	u32 regoff;
	पूर्णांक rmt_start = hfi1_netdev_get_मुक्त_rmt_idx(dd);
	पूर्णांक ctxt_count = hfi1_netdev_ctxt_count(dd);

	/* We alपढ़ोy have contexts mapped in RMT */
	अगर (has_rsm_rule(dd, RSM_INS_VNIC) || has_rsm_rule(dd, RSM_INS_AIP)) अणु
		dd_dev_info(dd, "Contexts are already mapped in RMT\n");
		वापस true;
	पूर्ण

	अगर (hfi1_is_rmt_full(rmt_start, NUM_NETDEV_MAP_ENTRIES)) अणु
		dd_dev_err(dd, "Not enough RMT entries used = %d\n",
			   rmt_start);
		वापस false;
	पूर्ण

	dev_dbg(&(dd)->pcidev->dev, "RMT start = %d, end %d\n",
		rmt_start,
		rmt_start + NUM_NETDEV_MAP_ENTRIES);

	/* Update RSM mapping table, 32 regs, 256 entries - 1 ctx per byte */
	regoff = RCV_RSM_MAP_TABLE + (rmt_start / 8) * 8;
	reg = पढ़ो_csr(dd, regoff);
	क्रम (i = 0; i < NUM_NETDEV_MAP_ENTRIES; i++) अणु
		/* Update map रेजिस्टर with netdev context */
		j = (rmt_start + i) % 8;
		reg &= ~(0xffllu << (j * 8));
		reg |= (u64)hfi1_netdev_get_ctxt(dd, ctx_id++)->ctxt << (j * 8);
		/* Wrap up netdev ctx index */
		ctx_id %= ctxt_count;
		/* Write back map रेजिस्टर */
		अगर (j == 7 || ((i + 1) == NUM_NETDEV_MAP_ENTRIES)) अणु
			dev_dbg(&(dd)->pcidev->dev,
				"RMT[%d] =0x%llx\n",
				regoff - RCV_RSM_MAP_TABLE, reg);

			ग_लिखो_csr(dd, regoff, reg);
			regoff += 8;
			अगर (i < (NUM_NETDEV_MAP_ENTRIES - 1))
				reg = पढ़ो_csr(dd, regoff);
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम hfi1_enable_rsm_rule(काष्ठा hfi1_devdata *dd,
				 पूर्णांक rule, काष्ठा rsm_rule_data *rrd)
अणु
	अगर (!hfi1_netdev_update_rmt(dd)) अणु
		dd_dev_err(dd, "Failed to update RMT for RSM%d rule\n", rule);
		वापस;
	पूर्ण

	add_rsm_rule(dd, rule, rrd);
	add_rcvctrl(dd, RCV_CTRL_RCV_RSM_ENABLE_SMASK);
पूर्ण

व्योम hfi1_init_aip_rsm(काष्ठा hfi1_devdata *dd)
अणु
	/*
	 * go through with the initialisation only अगर this rule actually करोesn't
	 * exist yet
	 */
	अगर (atomic_fetch_inc(&dd->ipoib_rsm_usr_num) == 0) अणु
		पूर्णांक rmt_start = hfi1_netdev_get_मुक्त_rmt_idx(dd);
		काष्ठा rsm_rule_data rrd = अणु
			.offset = rmt_start,
			.pkt_type = IB_PACKET_TYPE,
			.field1_off = LRH_BTH_MATCH_OFFSET,
			.mask1 = LRH_BTH_MASK,
			.value1 = LRH_BTH_VALUE,
			.field2_off = BTH_DESTQP_MATCH_OFFSET,
			.mask2 = BTH_DESTQP_MASK,
			.value2 = BTH_DESTQP_VALUE,
			.index1_off = DETH_AIP_SQPN_SELECT_OFFSET +
					ilog2(NUM_NETDEV_MAP_ENTRIES),
			.index1_width = ilog2(NUM_NETDEV_MAP_ENTRIES),
			.index2_off = DETH_AIP_SQPN_SELECT_OFFSET,
			.index2_width = ilog2(NUM_NETDEV_MAP_ENTRIES)
		पूर्ण;

		hfi1_enable_rsm_rule(dd, RSM_INS_AIP, &rrd);
	पूर्ण
पूर्ण

/* Initialize RSM क्रम VNIC */
व्योम hfi1_init_vnic_rsm(काष्ठा hfi1_devdata *dd)
अणु
	पूर्णांक rmt_start = hfi1_netdev_get_मुक्त_rmt_idx(dd);
	काष्ठा rsm_rule_data rrd = अणु
		/* Add rule क्रम vnic */
		.offset = rmt_start,
		.pkt_type = 4,
		/* Match 16B packets */
		.field1_off = L2_TYPE_MATCH_OFFSET,
		.mask1 = L2_TYPE_MASK,
		.value1 = L2_16B_VALUE,
		/* Match ETH L4 packets */
		.field2_off = L4_TYPE_MATCH_OFFSET,
		.mask2 = L4_16B_TYPE_MASK,
		.value2 = L4_16B_ETH_VALUE,
		/* Calc context from veswid and entropy */
		.index1_off = L4_16B_HDR_VESWID_OFFSET,
		.index1_width = ilog2(NUM_NETDEV_MAP_ENTRIES),
		.index2_off = L2_16B_ENTROPY_OFFSET,
		.index2_width = ilog2(NUM_NETDEV_MAP_ENTRIES)
	पूर्ण;

	hfi1_enable_rsm_rule(dd, RSM_INS_VNIC, &rrd);
पूर्ण

व्योम hfi1_deinit_vnic_rsm(काष्ठा hfi1_devdata *dd)
अणु
	clear_rsm_rule(dd, RSM_INS_VNIC);
पूर्ण

व्योम hfi1_deinit_aip_rsm(काष्ठा hfi1_devdata *dd)
अणु
	/* only actually clear the rule अगर it's the last user asking to करो so */
	अगर (atomic_fetch_add_unless(&dd->ipoib_rsm_usr_num, -1, 0) == 1)
		clear_rsm_rule(dd, RSM_INS_AIP);
पूर्ण

अटल पूर्णांक init_rxe(काष्ठा hfi1_devdata *dd)
अणु
	काष्ठा rsm_map_table *rmt;
	u64 val;

	/* enable all receive errors */
	ग_लिखो_csr(dd, RCV_ERR_MASK, ~0ull);

	rmt = alloc_rsm_map_table(dd);
	अगर (!rmt)
		वापस -ENOMEM;

	/* set up QOS, including the QPN map table */
	init_qos(dd, rmt);
	init_fecn_handling(dd, rmt);
	complete_rsm_map_table(dd, rmt);
	/* record number of used rsm map entries क्रम netdev */
	hfi1_netdev_set_मुक्त_rmt_idx(dd, rmt->used);
	kमुक्त(rmt);

	/*
	 * make sure RcvCtrl.RcvWcb <= PCIe Device Control
	 * Register Max_Payload_Size (PCI_EXP_DEVCTL in Linux PCIe config
	 * space, PciCfgCap2.MaxPayloadSize in HFI).  There is only one
	 * invalid configuration: RcvCtrl.RcvWcb set to its max of 256 and
	 * Max_PayLoad_Size set to its minimum of 128.
	 *
	 * Presently, RcvCtrl.RcvWcb is not modअगरied from its शेष of 0
	 * (64 bytes).  Max_Payload_Size is possibly modअगरied upward in
	 * tune_pcie_caps() which is called after this routine.
	 */

	/* Have 16 bytes (4DW) of bypass header available in header queue */
	val = पढ़ो_csr(dd, RCV_BYPASS);
	val &= ~RCV_BYPASS_HDR_SIZE_SMASK;
	val |= ((4ull & RCV_BYPASS_HDR_SIZE_MASK) <<
		RCV_BYPASS_HDR_SIZE_SHIFT);
	ग_लिखो_csr(dd, RCV_BYPASS, val);
	वापस 0;
पूर्ण

अटल व्योम init_other(काष्ठा hfi1_devdata *dd)
अणु
	/* enable all CCE errors */
	ग_लिखो_csr(dd, CCE_ERR_MASK, ~0ull);
	/* enable *some* Misc errors */
	ग_लिखो_csr(dd, MISC_ERR_MASK, DRIVER_MISC_MASK);
	/* enable all DC errors, except LCB */
	ग_लिखो_csr(dd, DCC_ERR_FLG_EN, ~0ull);
	ग_लिखो_csr(dd, DC_DC8051_ERR_EN, ~0ull);
पूर्ण

/*
 * Fill out the given AU table using the given CU.  A CU is defined in terms
 * AUs.  The table is a an encoding: given the index, how many AUs करोes that
 * represent?
 *
 * NOTE: Assumes that the रेजिस्टर layout is the same क्रम the
 * local and remote tables.
 */
अटल व्योम assign_cm_au_table(काष्ठा hfi1_devdata *dd, u32 cu,
			       u32 csr0to3, u32 csr4to7)
अणु
	ग_लिखो_csr(dd, csr0to3,
		  0ull << SEND_CM_LOCAL_AU_TABLE0_TO3_LOCAL_AU_TABLE0_SHIFT |
		  1ull << SEND_CM_LOCAL_AU_TABLE0_TO3_LOCAL_AU_TABLE1_SHIFT |
		  2ull * cu <<
		  SEND_CM_LOCAL_AU_TABLE0_TO3_LOCAL_AU_TABLE2_SHIFT |
		  4ull * cu <<
		  SEND_CM_LOCAL_AU_TABLE0_TO3_LOCAL_AU_TABLE3_SHIFT);
	ग_लिखो_csr(dd, csr4to7,
		  8ull * cu <<
		  SEND_CM_LOCAL_AU_TABLE4_TO7_LOCAL_AU_TABLE4_SHIFT |
		  16ull * cu <<
		  SEND_CM_LOCAL_AU_TABLE4_TO7_LOCAL_AU_TABLE5_SHIFT |
		  32ull * cu <<
		  SEND_CM_LOCAL_AU_TABLE4_TO7_LOCAL_AU_TABLE6_SHIFT |
		  64ull * cu <<
		  SEND_CM_LOCAL_AU_TABLE4_TO7_LOCAL_AU_TABLE7_SHIFT);
पूर्ण

अटल व्योम assign_local_cm_au_table(काष्ठा hfi1_devdata *dd, u8 vcu)
अणु
	assign_cm_au_table(dd, vcu_to_cu(vcu), SEND_CM_LOCAL_AU_TABLE0_TO3,
			   SEND_CM_LOCAL_AU_TABLE4_TO7);
पूर्ण

व्योम assign_remote_cm_au_table(काष्ठा hfi1_devdata *dd, u8 vcu)
अणु
	assign_cm_au_table(dd, vcu_to_cu(vcu), SEND_CM_REMOTE_AU_TABLE0_TO3,
			   SEND_CM_REMOTE_AU_TABLE4_TO7);
पूर्ण

अटल व्योम init_txe(काष्ठा hfi1_devdata *dd)
अणु
	पूर्णांक i;

	/* enable all PIO, SDMA, general, and Egress errors */
	ग_लिखो_csr(dd, SEND_PIO_ERR_MASK, ~0ull);
	ग_लिखो_csr(dd, SEND_DMA_ERR_MASK, ~0ull);
	ग_लिखो_csr(dd, SEND_ERR_MASK, ~0ull);
	ग_लिखो_csr(dd, SEND_EGRESS_ERR_MASK, ~0ull);

	/* enable all per-context and per-SDMA engine errors */
	क्रम (i = 0; i < chip_send_contexts(dd); i++)
		ग_लिखो_kctxt_csr(dd, i, SEND_CTXT_ERR_MASK, ~0ull);
	क्रम (i = 0; i < chip_sdma_engines(dd); i++)
		ग_लिखो_kctxt_csr(dd, i, SEND_DMA_ENG_ERR_MASK, ~0ull);

	/* set the local CU to AU mapping */
	assign_local_cm_au_table(dd, dd->vcu);

	/*
	 * Set reasonable शेष क्रम Credit Return Timer
	 * Don't set on Simulator - causes it to choke.
	 */
	अगर (dd->icode != ICODE_FUNCTIONAL_SIMULATOR)
		ग_लिखो_csr(dd, SEND_CM_TIMER_CTRL, HFI1_CREDIT_RETURN_RATE);
पूर्ण

पूर्णांक hfi1_set_ctxt_jkey(काष्ठा hfi1_devdata *dd, काष्ठा hfi1_ctxtdata *rcd,
		       u16 jkey)
अणु
	u8 hw_ctxt;
	u64 reg;

	अगर (!rcd || !rcd->sc)
		वापस -EINVAL;

	hw_ctxt = rcd->sc->hw_context;
	reg = SEND_CTXT_CHECK_JOB_KEY_MASK_SMASK | /* mask is always 1's */
		((jkey & SEND_CTXT_CHECK_JOB_KEY_VALUE_MASK) <<
		 SEND_CTXT_CHECK_JOB_KEY_VALUE_SHIFT);
	/* JOB_KEY_ALLOW_PERMISSIVE is not allowed by शेष */
	अगर (HFI1_CAP_KGET_MASK(rcd->flags, ALLOW_PERM_JKEY))
		reg |= SEND_CTXT_CHECK_JOB_KEY_ALLOW_PERMISSIVE_SMASK;
	ग_लिखो_kctxt_csr(dd, hw_ctxt, SEND_CTXT_CHECK_JOB_KEY, reg);
	/*
	 * Enable send-side J_KEY पूर्णांकegrity check, unless this is A0 h/w
	 */
	अगर (!is_ax(dd)) अणु
		reg = पढ़ो_kctxt_csr(dd, hw_ctxt, SEND_CTXT_CHECK_ENABLE);
		reg |= SEND_CTXT_CHECK_ENABLE_CHECK_JOB_KEY_SMASK;
		ग_लिखो_kctxt_csr(dd, hw_ctxt, SEND_CTXT_CHECK_ENABLE, reg);
	पूर्ण

	/* Enable J_KEY check on receive context. */
	reg = RCV_KEY_CTRL_JOB_KEY_ENABLE_SMASK |
		((jkey & RCV_KEY_CTRL_JOB_KEY_VALUE_MASK) <<
		 RCV_KEY_CTRL_JOB_KEY_VALUE_SHIFT);
	ग_लिखो_kctxt_csr(dd, rcd->ctxt, RCV_KEY_CTRL, reg);

	वापस 0;
पूर्ण

पूर्णांक hfi1_clear_ctxt_jkey(काष्ठा hfi1_devdata *dd, काष्ठा hfi1_ctxtdata *rcd)
अणु
	u8 hw_ctxt;
	u64 reg;

	अगर (!rcd || !rcd->sc)
		वापस -EINVAL;

	hw_ctxt = rcd->sc->hw_context;
	ग_लिखो_kctxt_csr(dd, hw_ctxt, SEND_CTXT_CHECK_JOB_KEY, 0);
	/*
	 * Disable send-side J_KEY पूर्णांकegrity check, unless this is A0 h/w.
	 * This check would not have been enabled क्रम A0 h/w, see
	 * set_ctxt_jkey().
	 */
	अगर (!is_ax(dd)) अणु
		reg = पढ़ो_kctxt_csr(dd, hw_ctxt, SEND_CTXT_CHECK_ENABLE);
		reg &= ~SEND_CTXT_CHECK_ENABLE_CHECK_JOB_KEY_SMASK;
		ग_लिखो_kctxt_csr(dd, hw_ctxt, SEND_CTXT_CHECK_ENABLE, reg);
	पूर्ण
	/* Turn off the J_KEY on the receive side */
	ग_लिखो_kctxt_csr(dd, rcd->ctxt, RCV_KEY_CTRL, 0);

	वापस 0;
पूर्ण

पूर्णांक hfi1_set_ctxt_pkey(काष्ठा hfi1_devdata *dd, काष्ठा hfi1_ctxtdata *rcd,
		       u16 pkey)
अणु
	u8 hw_ctxt;
	u64 reg;

	अगर (!rcd || !rcd->sc)
		वापस -EINVAL;

	hw_ctxt = rcd->sc->hw_context;
	reg = ((u64)pkey & SEND_CTXT_CHECK_PARTITION_KEY_VALUE_MASK) <<
		SEND_CTXT_CHECK_PARTITION_KEY_VALUE_SHIFT;
	ग_लिखो_kctxt_csr(dd, hw_ctxt, SEND_CTXT_CHECK_PARTITION_KEY, reg);
	reg = पढ़ो_kctxt_csr(dd, hw_ctxt, SEND_CTXT_CHECK_ENABLE);
	reg |= SEND_CTXT_CHECK_ENABLE_CHECK_PARTITION_KEY_SMASK;
	reg &= ~SEND_CTXT_CHECK_ENABLE_DISALLOW_KDETH_PACKETS_SMASK;
	ग_लिखो_kctxt_csr(dd, hw_ctxt, SEND_CTXT_CHECK_ENABLE, reg);

	वापस 0;
पूर्ण

पूर्णांक hfi1_clear_ctxt_pkey(काष्ठा hfi1_devdata *dd, काष्ठा hfi1_ctxtdata *ctxt)
अणु
	u8 hw_ctxt;
	u64 reg;

	अगर (!ctxt || !ctxt->sc)
		वापस -EINVAL;

	hw_ctxt = ctxt->sc->hw_context;
	reg = पढ़ो_kctxt_csr(dd, hw_ctxt, SEND_CTXT_CHECK_ENABLE);
	reg &= ~SEND_CTXT_CHECK_ENABLE_CHECK_PARTITION_KEY_SMASK;
	ग_लिखो_kctxt_csr(dd, hw_ctxt, SEND_CTXT_CHECK_ENABLE, reg);
	ग_लिखो_kctxt_csr(dd, hw_ctxt, SEND_CTXT_CHECK_PARTITION_KEY, 0);

	वापस 0;
पूर्ण

/*
 * Start करोing the clean up the the chip. Our clean up happens in multiple
 * stages and this is just the first.
 */
व्योम hfi1_start_cleanup(काष्ठा hfi1_devdata *dd)
अणु
	aspm_निकास(dd);
	मुक्त_cntrs(dd);
	मुक्त_rcverr(dd);
	finish_chip_resources(dd);
पूर्ण

#घोषणा HFI_BASE_GUID(dev) \
	((dev)->base_guid & ~(1ULL << GUID_HFI_INDEX_SHIFT))

/*
 * Inक्रमmation can be shared between the two HFIs on the same ASIC
 * in the same OS.  This function finds the peer device and sets
 * up a shared काष्ठाure.
 */
अटल पूर्णांक init_asic_data(काष्ठा hfi1_devdata *dd)
अणु
	अचिन्हित दीर्घ index;
	काष्ठा hfi1_devdata *peer;
	काष्ठा hfi1_asic_data *asic_data;
	पूर्णांक ret = 0;

	/* pre-allocate the asic काष्ठाure in हाल we are the first device */
	asic_data = kzalloc(माप(*dd->asic_data), GFP_KERNEL);
	अगर (!asic_data)
		वापस -ENOMEM;

	xa_lock_irq(&hfi1_dev_table);
	/* Find our peer device */
	xa_क्रम_each(&hfi1_dev_table, index, peer) अणु
		अगर ((HFI_BASE_GUID(dd) == HFI_BASE_GUID(peer)) &&
		    dd->unit != peer->unit)
			अवरोध;
	पूर्ण

	अगर (peer) अणु
		/* use alपढ़ोy allocated काष्ठाure */
		dd->asic_data = peer->asic_data;
		kमुक्त(asic_data);
	पूर्ण अन्यथा अणु
		dd->asic_data = asic_data;
		mutex_init(&dd->asic_data->asic_resource_mutex);
	पूर्ण
	dd->asic_data->dds[dd->hfi1_id] = dd; /* self back-poपूर्णांकer */
	xa_unlock_irq(&hfi1_dev_table);

	/* first one through - set up i2c devices */
	अगर (!peer)
		ret = set_up_i2c(dd, dd->asic_data);

	वापस ret;
पूर्ण

/*
 * Set dd->boardname.  Use a generic name अगर a name is not वापसed from
 * EFI variable space.
 *
 * Return 0 on success, -ENOMEM अगर space could not be allocated.
 */
अटल पूर्णांक obtain_boardname(काष्ठा hfi1_devdata *dd)
अणु
	/* generic board description */
	स्थिर अक्षर generic[] =
		"Intel Omni-Path Host Fabric Interface Adapter 100 Series";
	अचिन्हित दीर्घ size;
	पूर्णांक ret;

	ret = पढ़ो_hfi1_efi_var(dd, "description", &size,
				(व्योम **)&dd->boardname);
	अगर (ret) अणु
		dd_dev_info(dd, "Board description not found\n");
		/* use generic description */
		dd->boardname = kstrdup(generic, GFP_KERNEL);
		अगर (!dd->boardname)
			वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Check the पूर्णांकerrupt रेजिस्टरs to make sure that they are mapped correctly.
 * It is पूर्णांकended to help user identअगरy any mismapping by VMM when the driver
 * is running in a VM. This function should only be called beक्रमe पूर्णांकerrupt
 * is set up properly.
 *
 * Return 0 on success, -EINVAL on failure.
 */
अटल पूर्णांक check_पूर्णांक_रेजिस्टरs(काष्ठा hfi1_devdata *dd)
अणु
	u64 reg;
	u64 all_bits = ~(u64)0;
	u64 mask;

	/* Clear CceIntMask[0] to aव्योम raising any पूर्णांकerrupts */
	mask = पढ़ो_csr(dd, CCE_INT_MASK);
	ग_लिखो_csr(dd, CCE_INT_MASK, 0ull);
	reg = पढ़ो_csr(dd, CCE_INT_MASK);
	अगर (reg)
		जाओ err_निकास;

	/* Clear all पूर्णांकerrupt status bits */
	ग_लिखो_csr(dd, CCE_INT_CLEAR, all_bits);
	reg = पढ़ो_csr(dd, CCE_INT_STATUS);
	अगर (reg)
		जाओ err_निकास;

	/* Set all पूर्णांकerrupt status bits */
	ग_लिखो_csr(dd, CCE_INT_FORCE, all_bits);
	reg = पढ़ो_csr(dd, CCE_INT_STATUS);
	अगर (reg != all_bits)
		जाओ err_निकास;

	/* Restore the पूर्णांकerrupt mask */
	ग_लिखो_csr(dd, CCE_INT_CLEAR, all_bits);
	ग_लिखो_csr(dd, CCE_INT_MASK, mask);

	वापस 0;
err_निकास:
	ग_लिखो_csr(dd, CCE_INT_MASK, mask);
	dd_dev_err(dd, "Interrupt registers not properly mapped by VMM\n");
	वापस -EINVAL;
पूर्ण

/**
 * hfi1_init_dd() - Initialize most of the dd काष्ठाure.
 * @dd: the dd device
 *
 * This is global, and is called directly at init to set up the
 * chip-specअगरic function poपूर्णांकers क्रम later use.
 */
पूर्णांक hfi1_init_dd(काष्ठा hfi1_devdata *dd)
अणु
	काष्ठा pci_dev *pdev = dd->pcidev;
	काष्ठा hfi1_pportdata *ppd;
	u64 reg;
	पूर्णांक i, ret;
	अटल स्थिर अक्षर * स्थिर inames[] = अणु /* implementation names */
		"RTL silicon",
		"RTL VCS simulation",
		"RTL FPGA emulation",
		"Functional simulator"
	पूर्ण;
	काष्ठा pci_dev *parent = pdev->bus->self;
	u32 sdma_engines = chip_sdma_engines(dd);

	ppd = dd->pport;
	क्रम (i = 0; i < dd->num_pports; i++, ppd++) अणु
		पूर्णांक vl;
		/* init common fields */
		hfi1_init_pportdata(pdev, ppd, dd, 0, 1);
		/* DC supports 4 link widths */
		ppd->link_width_supported =
			OPA_LINK_WIDTH_1X | OPA_LINK_WIDTH_2X |
			OPA_LINK_WIDTH_3X | OPA_LINK_WIDTH_4X;
		ppd->link_width_करोwngrade_supported =
			ppd->link_width_supported;
		/* start out enabling only 4X */
		ppd->link_width_enabled = OPA_LINK_WIDTH_4X;
		ppd->link_width_करोwngrade_enabled =
					ppd->link_width_करोwngrade_supported;
		/* link width active is 0 when link is करोwn */
		/* link width करोwngrade active is 0 when link is करोwn */

		अगर (num_vls < HFI1_MIN_VLS_SUPPORTED ||
		    num_vls > HFI1_MAX_VLS_SUPPORTED) अणु
			dd_dev_err(dd, "Invalid num_vls %u, using %u VLs\n",
				   num_vls, HFI1_MAX_VLS_SUPPORTED);
			num_vls = HFI1_MAX_VLS_SUPPORTED;
		पूर्ण
		ppd->vls_supported = num_vls;
		ppd->vls_operational = ppd->vls_supported;
		/* Set the शेष MTU. */
		क्रम (vl = 0; vl < num_vls; vl++)
			dd->vld[vl].mtu = hfi1_max_mtu;
		dd->vld[15].mtu = MAX_MAD_PACKET;
		/*
		 * Set the initial values to reasonable शेष, will be set
		 * क्रम real when link is up.
		 */
		ppd->overrun_threshold = 0x4;
		ppd->phy_error_threshold = 0xf;
		ppd->port_crc_mode_enabled = link_crc_mask;
		/* initialize supported LTP CRC mode */
		ppd->port_ltp_crc_mode = cap_to_port_ltp(link_crc_mask) << 8;
		/* initialize enabled LTP CRC mode */
		ppd->port_ltp_crc_mode |= cap_to_port_ltp(link_crc_mask) << 4;
		/* start in offline */
		ppd->host_link_state = HLS_DN_OFFLINE;
		init_vl_arb_caches(ppd);
	पूर्ण

	/*
	 * Do reमुख्यing PCIe setup and save PCIe values in dd.
	 * Any error prपूर्णांकing is alपढ़ोy करोne by the init code.
	 * On वापस, we have the chip mapped.
	 */
	ret = hfi1_pcie_ddinit(dd, pdev);
	अगर (ret < 0)
		जाओ bail_मुक्त;

	/* Save PCI space रेजिस्टरs to reग_लिखो after device reset */
	ret = save_pci_variables(dd);
	अगर (ret < 0)
		जाओ bail_cleanup;

	dd->majrev = (dd->revision >> CCE_REVISION_CHIP_REV_MAJOR_SHIFT)
			& CCE_REVISION_CHIP_REV_MAJOR_MASK;
	dd->minrev = (dd->revision >> CCE_REVISION_CHIP_REV_MINOR_SHIFT)
			& CCE_REVISION_CHIP_REV_MINOR_MASK;

	/*
	 * Check पूर्णांकerrupt रेजिस्टरs mapping अगर the driver has no access to
	 * the upstream component. In this हाल, it is likely that the driver
	 * is running in a VM.
	 */
	अगर (!parent) अणु
		ret = check_पूर्णांक_रेजिस्टरs(dd);
		अगर (ret)
			जाओ bail_cleanup;
	पूर्ण

	/*
	 * obtain the hardware ID - NOT related to unit, which is a
	 * software क्रमागतeration
	 */
	reg = पढ़ो_csr(dd, CCE_REVISION2);
	dd->hfi1_id = (reg >> CCE_REVISION2_HFI_ID_SHIFT)
					& CCE_REVISION2_HFI_ID_MASK;
	/* the variable size will हटाओ unwanted bits */
	dd->icode = reg >> CCE_REVISION2_IMPL_CODE_SHIFT;
	dd->irev = reg >> CCE_REVISION2_IMPL_REVISION_SHIFT;
	dd_dev_info(dd, "Implementation: %s, revision 0x%x\n",
		    dd->icode < ARRAY_SIZE(inames) ?
		    inames[dd->icode] : "unknown", (पूर्णांक)dd->irev);

	/* speeds the hardware can support */
	dd->pport->link_speed_supported = OPA_LINK_SPEED_25G;
	/* speeds allowed to run at */
	dd->pport->link_speed_enabled = dd->pport->link_speed_supported;
	/* give a reasonable active value, will be set on link up */
	dd->pport->link_speed_active = OPA_LINK_SPEED_25G;

	/* fix up link widths क्रम emulation _p */
	ppd = dd->pport;
	अगर (dd->icode == ICODE_FPGA_EMULATION && is_emulator_p(dd)) अणु
		ppd->link_width_supported =
			ppd->link_width_enabled =
			ppd->link_width_करोwngrade_supported =
			ppd->link_width_करोwngrade_enabled =
				OPA_LINK_WIDTH_1X;
	पूर्ण
	/* insure num_vls isn't larger than number of sdma engines */
	अगर (HFI1_CAP_IS_KSET(SDMA) && num_vls > sdma_engines) अणु
		dd_dev_err(dd, "num_vls %u too large, using %u VLs\n",
			   num_vls, sdma_engines);
		num_vls = sdma_engines;
		ppd->vls_supported = sdma_engines;
		ppd->vls_operational = ppd->vls_supported;
	पूर्ण

	/*
	 * Convert the ns parameter to the 64 * cघड़ीs used in the CSR.
	 * Limit the max अगर larger than the field holds.  If समयout is
	 * non-zero, then the calculated field will be at least 1.
	 *
	 * Must be after icode is set up - the cघड़ी rate depends
	 * on knowing the hardware being used.
	 */
	dd->rcv_पूर्णांकr_समयout_csr = ns_to_cघड़ी(dd, rcv_पूर्णांकr_समयout) / 64;
	अगर (dd->rcv_पूर्णांकr_समयout_csr >
			RCV_AVAIL_TIME_OUT_TIME_OUT_RELOAD_MASK)
		dd->rcv_पूर्णांकr_समयout_csr =
			RCV_AVAIL_TIME_OUT_TIME_OUT_RELOAD_MASK;
	अन्यथा अगर (dd->rcv_पूर्णांकr_समयout_csr == 0 && rcv_पूर्णांकr_समयout)
		dd->rcv_पूर्णांकr_समयout_csr = 1;

	/* needs to be करोne beक्रमe we look क्रम the peer device */
	पढ़ो_guid(dd);

	/* set up shared ASIC data with peer device */
	ret = init_asic_data(dd);
	अगर (ret)
		जाओ bail_cleanup;

	/* obtain chip sizes, reset chip CSRs */
	ret = init_chip(dd);
	अगर (ret)
		जाओ bail_cleanup;

	/* पढ़ो in the PCIe link speed inक्रमmation */
	ret = pcie_speeds(dd);
	अगर (ret)
		जाओ bail_cleanup;

	/* call beक्रमe get_platक्रमm_config(), after init_chip_resources() */
	ret = eprom_init(dd);
	अगर (ret)
		जाओ bail_मुक्त_rcverr;

	/* Needs to be called beक्रमe hfi1_firmware_init */
	get_platक्रमm_config(dd);

	/* पढ़ो in firmware */
	ret = hfi1_firmware_init(dd);
	अगर (ret)
		जाओ bail_cleanup;

	/*
	 * In general, the PCIe Gen3 transition must occur after the
	 * chip has been idled (so it won't initiate any PCIe transactions
	 * e.g. an पूर्णांकerrupt) and beक्रमe the driver changes any रेजिस्टरs
	 * (the transition will reset the रेजिस्टरs).
	 *
	 * In particular, place this call after:
	 * - init_chip()     - the chip will not initiate any PCIe transactions
	 * - pcie_speeds()   - पढ़ोs the current link speed
	 * - hfi1_firmware_init() - the needed firmware is पढ़ोy to be
	 *			    करोwnloaded
	 */
	ret = करो_pcie_gen3_transition(dd);
	अगर (ret)
		जाओ bail_cleanup;

	/*
	 * This should probably occur in hfi1_pcie_init(), but historically
	 * occurs after the करो_pcie_gen3_transition() code.
	 */
	tune_pcie_caps(dd);

	/* start setting dd values and adjusting CSRs */
	init_early_variables(dd);

	parse_platक्रमm_config(dd);

	ret = obtain_boardname(dd);
	अगर (ret)
		जाओ bail_cleanup;

	snम_लिखो(dd->boardversion, BOARD_VERS_MAX,
		 "ChipABI %u.%u, ChipRev %u.%u, SW Compat %llu\n",
		 HFI1_CHIP_VERS_MAJ, HFI1_CHIP_VERS_MIN,
		 (u32)dd->majrev,
		 (u32)dd->minrev,
		 (dd->revision >> CCE_REVISION_SW_SHIFT)
		    & CCE_REVISION_SW_MASK);

	/* alloc VNIC/AIP rx data */
	ret = hfi1_alloc_rx(dd);
	अगर (ret)
		जाओ bail_cleanup;

	ret = set_up_context_variables(dd);
	अगर (ret)
		जाओ bail_cleanup;

	/* set initial RXE CSRs */
	ret = init_rxe(dd);
	अगर (ret)
		जाओ bail_cleanup;

	/* set initial TXE CSRs */
	init_txe(dd);
	/* set initial non-RXE, non-TXE CSRs */
	init_other(dd);
	/* set up KDETH QP prefix in both RX and TX CSRs */
	init_kdeth_qp(dd);

	ret = hfi1_dev_affinity_init(dd);
	अगर (ret)
		जाओ bail_cleanup;

	/* send contexts must be set up beक्रमe receive contexts */
	ret = init_send_contexts(dd);
	अगर (ret)
		जाओ bail_cleanup;

	ret = hfi1_create_kctxts(dd);
	अगर (ret)
		जाओ bail_cleanup;

	/*
	 * Initialize aspm, to be करोne after gen3 transition and setting up
	 * contexts and beक्रमe enabling पूर्णांकerrupts
	 */
	aspm_init(dd);

	ret = init_pervl_scs(dd);
	अगर (ret)
		जाओ bail_cleanup;

	/* sdma init */
	क्रम (i = 0; i < dd->num_pports; ++i) अणु
		ret = sdma_init(dd, i);
		अगर (ret)
			जाओ bail_cleanup;
	पूर्ण

	/* use contexts created by hfi1_create_kctxts */
	ret = set_up_पूर्णांकerrupts(dd);
	अगर (ret)
		जाओ bail_cleanup;

	ret = hfi1_comp_vectors_set_up(dd);
	अगर (ret)
		जाओ bail_clear_पूर्णांकr;

	/* set up LCB access - must be after set_up_पूर्णांकerrupts() */
	init_lcb_access(dd);

	/*
	 * Serial number is created from the base guid:
	 * [27:24] = base guid [38:35]
	 * [23: 0] = base guid [23: 0]
	 */
	snम_लिखो(dd->serial, SERIAL_MAX, "0x%08llx\n",
		 (dd->base_guid & 0xFFFFFF) |
		     ((dd->base_guid >> 11) & 0xF000000));

	dd->oui1 = dd->base_guid >> 56 & 0xFF;
	dd->oui2 = dd->base_guid >> 48 & 0xFF;
	dd->oui3 = dd->base_guid >> 40 & 0xFF;

	ret = load_firmware(dd); /* asymmetric with dispose_firmware() */
	अगर (ret)
		जाओ bail_clear_पूर्णांकr;

	thermal_init(dd);

	ret = init_cntrs(dd);
	अगर (ret)
		जाओ bail_clear_पूर्णांकr;

	ret = init_rcverr(dd);
	अगर (ret)
		जाओ bail_मुक्त_cntrs;

	init_completion(&dd->user_comp);

	/* The user refcount starts with one to inidicate an active device */
	atomic_set(&dd->user_refcount, 1);

	जाओ bail;

bail_मुक्त_rcverr:
	मुक्त_rcverr(dd);
bail_मुक्त_cntrs:
	मुक्त_cntrs(dd);
bail_clear_पूर्णांकr:
	hfi1_comp_vectors_clean_up(dd);
	msix_clean_up_पूर्णांकerrupts(dd);
bail_cleanup:
	hfi1_मुक्त_rx(dd);
	hfi1_pcie_ddcleanup(dd);
bail_मुक्त:
	hfi1_मुक्त_devdata(dd);
bail:
	वापस ret;
पूर्ण

अटल u16 delay_cycles(काष्ठा hfi1_pportdata *ppd, u32 desired_egress_rate,
			u32 dw_len)
अणु
	u32 delta_cycles;
	u32 current_egress_rate = ppd->current_egress_rate;
	/* rates here are in units of 10^6 bits/sec */

	अगर (desired_egress_rate == -1)
		वापस 0; /* shouldn't happen */

	अगर (desired_egress_rate >= current_egress_rate)
		वापस 0; /* we can't help go faster, only slower */

	delta_cycles = egress_cycles(dw_len * 4, desired_egress_rate) -
			egress_cycles(dw_len * 4, current_egress_rate);

	वापस (u16)delta_cycles;
पूर्ण

/**
 * create_pbc - build a pbc क्रम transmission
 * @ppd: info of physical Hfi port
 * @flags: special हाल flags or-ed in built pbc
 * @srate_mbs: अटल rate
 * @vl: vl
 * @dw_len: dword length (header words + data words + pbc words)
 *
 * Create a PBC with the given flags, rate, VL, and length.
 *
 * NOTE: The PBC created will not insert any HCRC - all callers but one are
 * क्रम verbs, which करोes not use this PSM feature.  The lone other caller
 * is क्रम the diagnostic पूर्णांकerface which calls this अगर the user करोes not
 * supply their own PBC.
 */
u64 create_pbc(काष्ठा hfi1_pportdata *ppd, u64 flags, पूर्णांक srate_mbs, u32 vl,
	       u32 dw_len)
अणु
	u64 pbc, delay = 0;

	अगर (unlikely(srate_mbs))
		delay = delay_cycles(ppd, srate_mbs, dw_len);

	pbc = flags
		| (delay << PBC_STATIC_RATE_CONTROL_COUNT_SHIFT)
		| ((u64)PBC_IHCRC_NONE << PBC_INSERT_HCRC_SHIFT)
		| (vl & PBC_VL_MASK) << PBC_VL_SHIFT
		| (dw_len & PBC_LENGTH_DWS_MASK)
			<< PBC_LENGTH_DWS_SHIFT;

	वापस pbc;
पूर्ण

#घोषणा SBUS_THERMAL    0x4f
#घोषणा SBUS_THERM_MONITOR_MODE 0x1

#घोषणा THERM_FAILURE(dev, ret, reason) \
	dd_dev_err((dd),						\
		   "Thermal sensor initialization failed: %s (%d)\n",	\
		   (reason), (ret))

/*
 * Initialize the thermal sensor.
 *
 * After initialization, enable polling of thermal sensor through
 * SBus पूर्णांकerface. In order क्रम this to work, the SBus Master
 * firmware has to be loaded due to the fact that the HW polling
 * logic uses SBus पूर्णांकerrupts, which are not supported with
 * शेष firmware. Otherwise, no data will be वापसed through
 * the ASIC_STS_THERM CSR.
 */
अटल पूर्णांक thermal_init(काष्ठा hfi1_devdata *dd)
अणु
	पूर्णांक ret = 0;

	अगर (dd->icode != ICODE_RTL_SILICON ||
	    check_chip_resource(dd, CR_THERM_INIT, शून्य))
		वापस ret;

	ret = acquire_chip_resource(dd, CR_SBUS, SBUS_TIMEOUT);
	अगर (ret) अणु
		THERM_FAILURE(dd, ret, "Acquire SBus");
		वापस ret;
	पूर्ण

	dd_dev_info(dd, "Initializing thermal sensor\n");
	/* Disable polling of thermal पढ़ोings */
	ग_लिखो_csr(dd, ASIC_CFG_THERM_POLL_EN, 0x0);
	msleep(100);
	/* Thermal Sensor Initialization */
	/*    Step 1: Reset the Thermal SBus Receiver */
	ret = sbus_request_slow(dd, SBUS_THERMAL, 0x0,
				RESET_SBUS_RECEIVER, 0);
	अगर (ret) अणु
		THERM_FAILURE(dd, ret, "Bus Reset");
		जाओ करोne;
	पूर्ण
	/*    Step 2: Set Reset bit in Thermal block */
	ret = sbus_request_slow(dd, SBUS_THERMAL, 0x0,
				WRITE_SBUS_RECEIVER, 0x1);
	अगर (ret) अणु
		THERM_FAILURE(dd, ret, "Therm Block Reset");
		जाओ करोne;
	पूर्ण
	/*    Step 3: Write घड़ी भागider value (100MHz -> 2MHz) */
	ret = sbus_request_slow(dd, SBUS_THERMAL, 0x1,
				WRITE_SBUS_RECEIVER, 0x32);
	अगर (ret) अणु
		THERM_FAILURE(dd, ret, "Write Clock Div");
		जाओ करोne;
	पूर्ण
	/*    Step 4: Select temperature mode */
	ret = sbus_request_slow(dd, SBUS_THERMAL, 0x3,
				WRITE_SBUS_RECEIVER,
				SBUS_THERM_MONITOR_MODE);
	अगर (ret) अणु
		THERM_FAILURE(dd, ret, "Write Mode Sel");
		जाओ करोne;
	पूर्ण
	/*    Step 5: De-निश्चित block reset and start conversion */
	ret = sbus_request_slow(dd, SBUS_THERMAL, 0x0,
				WRITE_SBUS_RECEIVER, 0x2);
	अगर (ret) अणु
		THERM_FAILURE(dd, ret, "Write Reset Deassert");
		जाओ करोne;
	पूर्ण
	/*    Step 5.1: Wait क्रम first conversion (21.5ms per spec) */
	msleep(22);

	/* Enable polling of thermal पढ़ोings */
	ग_लिखो_csr(dd, ASIC_CFG_THERM_POLL_EN, 0x1);

	/* Set initialized flag */
	ret = acquire_chip_resource(dd, CR_THERM_INIT, 0);
	अगर (ret)
		THERM_FAILURE(dd, ret, "Unable to set thermal init flag");

करोne:
	release_chip_resource(dd, CR_SBUS);
	वापस ret;
पूर्ण

अटल व्योम handle_temp_err(काष्ठा hfi1_devdata *dd)
अणु
	काष्ठा hfi1_pportdata *ppd = &dd->pport[0];
	/*
	 * Thermal Critical Interrupt
	 * Put the device पूर्णांकo क्रमced मुक्तze mode, take link करोwn to
	 * offline, and put DC पूर्णांकo reset.
	 */
	dd_dev_emerg(dd,
		     "Critical temperature reached! Forcing device into freeze mode!\n");
	dd->flags |= HFI1_FORCED_FREEZE;
	start_मुक्तze_handling(ppd, FREEZE_SELF | FREEZE_ABORT);
	/*
	 * Shut DC करोwn as much and as quickly as possible.
	 *
	 * Step 1: Take the link करोwn to OFFLINE. This will cause the
	 *         8051 to put the Serdes in reset. However, we करोn't want to
	 *         go through the entire link state machine since we want to
	 *         shutकरोwn ASAP. Furthermore, this is not a graceful shutकरोwn
	 *         but rather an attempt to save the chip.
	 *         Code below is almost the same as quiet_serdes() but aव्योमs
	 *         all the extra work and the sleeps.
	 */
	ppd->driver_link_पढ़ोy = 0;
	ppd->link_enabled = 0;
	set_physical_link_state(dd, (OPA_LINKDOWN_REASON_SMA_DISABLED << 8) |
				PLS_OFFLINE);
	/*
	 * Step 2: Shutकरोwn LCB and 8051
	 *         After shutकरोwn, करो not restore DC_CFG_RESET value.
	 */
	dc_shutकरोwn(dd);
पूर्ण
