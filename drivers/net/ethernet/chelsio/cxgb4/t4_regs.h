<शैली गुरु>
/*
 * This file is part of the Chelsio T4 Ethernet driver क्रम Linux.
 *
 * Copyright (c) 2003-2014 Chelsio Communications, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#अगर_अघोषित __T4_REGS_H
#घोषणा __T4_REGS_H

#घोषणा MYPF_BASE 0x1b000
#घोषणा MYPF_REG(reg_addr) (MYPF_BASE + (reg_addr))

#घोषणा PF0_BASE 0x1e000
#घोषणा PF0_REG(reg_addr) (PF0_BASE + (reg_addr))

#घोषणा PF_STRIDE 0x400
#घोषणा PF_BASE(idx) (PF0_BASE + (idx) * PF_STRIDE)
#घोषणा PF_REG(idx, reg) (PF_BASE(idx) + (reg))

#घोषणा NUM_CIM_CTL_TSCH_CHANNEL_INSTANCES 4
#घोषणा NUM_CIM_CTL_TSCH_CHANNEL_TSCH_CLASS_INSTANCES 16

#घोषणा MYPORT_BASE 0x1c000
#घोषणा MYPORT_REG(reg_addr) (MYPORT_BASE + (reg_addr))

#घोषणा PORT0_BASE 0x20000
#घोषणा PORT0_REG(reg_addr) (PORT0_BASE + (reg_addr))

#घोषणा PORT_STRIDE 0x2000
#घोषणा PORT_BASE(idx) (PORT0_BASE + (idx) * PORT_STRIDE)
#घोषणा PORT_REG(idx, reg) (PORT_BASE(idx) + (reg))

#घोषणा EDC_STRIDE (EDC_1_BASE_ADDR - EDC_0_BASE_ADDR)
#घोषणा EDC_REG(reg, idx) (reg + EDC_STRIDE * idx)

#घोषणा PCIE_MEM_ACCESS_REG(reg_addr, idx) ((reg_addr) + (idx) * 8)
#घोषणा PCIE_MAILBOX_REG(reg_addr, idx) ((reg_addr) + (idx) * 8)
#घोषणा MC_BIST_STATUS_REG(reg_addr, idx) ((reg_addr) + (idx) * 4)
#घोषणा EDC_BIST_STATUS_REG(reg_addr, idx) ((reg_addr) + (idx) * 4)

#घोषणा PCIE_FW_REG(reg_addr, idx) ((reg_addr) + (idx) * 4)

#घोषणा NUM_LE_DB_DBGI_REQ_DATA_INSTANCES 17
#घोषणा NUM_LE_DB_DBGI_RSP_DATA_INSTANCES 17

#घोषणा SGE_PF_KDOORBELL_A 0x0

#घोषणा QID_S    15
#घोषणा QID_V(x) ((x) << QID_S)

#घोषणा DBPRIO_S    14
#घोषणा DBPRIO_V(x) ((x) << DBPRIO_S)
#घोषणा DBPRIO_F    DBPRIO_V(1U)

#घोषणा PIDX_S    0
#घोषणा PIDX_V(x) ((x) << PIDX_S)

#घोषणा SGE_VF_KDOORBELL_A 0x0

#घोषणा DBTYPE_S    13
#घोषणा DBTYPE_V(x) ((x) << DBTYPE_S)
#घोषणा DBTYPE_F    DBTYPE_V(1U)

#घोषणा PIDX_T5_S    0
#घोषणा PIDX_T5_M    0x1fffU
#घोषणा PIDX_T5_V(x) ((x) << PIDX_T5_S)
#घोषणा PIDX_T5_G(x) (((x) >> PIDX_T5_S) & PIDX_T5_M)

#घोषणा SGE_PF_GTS_A 0x4

#घोषणा INGRESSQID_S    16
#घोषणा INGRESSQID_V(x) ((x) << INGRESSQID_S)

#घोषणा TIMERREG_S    13
#घोषणा TIMERREG_V(x) ((x) << TIMERREG_S)

#घोषणा SEINTARM_S    12
#घोषणा SEINTARM_V(x) ((x) << SEINTARM_S)

#घोषणा CIDXINC_S    0
#घोषणा CIDXINC_M    0xfffU
#घोषणा CIDXINC_V(x) ((x) << CIDXINC_S)

#घोषणा SGE_CONTROL_A	0x1008
#घोषणा SGE_CONTROL2_A	0x1124

#घोषणा RXPKTCPLMODE_S    18
#घोषणा RXPKTCPLMODE_V(x) ((x) << RXPKTCPLMODE_S)
#घोषणा RXPKTCPLMODE_F    RXPKTCPLMODE_V(1U)

#घोषणा EGRSTATUSPAGESIZE_S    17
#घोषणा EGRSTATUSPAGESIZE_V(x) ((x) << EGRSTATUSPAGESIZE_S)
#घोषणा EGRSTATUSPAGESIZE_F    EGRSTATUSPAGESIZE_V(1U)

#घोषणा PKTSHIFT_S    10
#घोषणा PKTSHIFT_M    0x7U
#घोषणा PKTSHIFT_V(x) ((x) << PKTSHIFT_S)
#घोषणा PKTSHIFT_G(x) (((x) >> PKTSHIFT_S) & PKTSHIFT_M)

#घोषणा INGPCIEBOUNDARY_S    7
#घोषणा INGPCIEBOUNDARY_V(x) ((x) << INGPCIEBOUNDARY_S)

#घोषणा INGPADBOUNDARY_S    4
#घोषणा INGPADBOUNDARY_M    0x7U
#घोषणा INGPADBOUNDARY_V(x) ((x) << INGPADBOUNDARY_S)
#घोषणा INGPADBOUNDARY_G(x) (((x) >> INGPADBOUNDARY_S) & INGPADBOUNDARY_M)

#घोषणा EGRPCIEBOUNDARY_S    1
#घोषणा EGRPCIEBOUNDARY_V(x) ((x) << EGRPCIEBOUNDARY_S)

#घोषणा  INGPACKBOUNDARY_S	16
#घोषणा  INGPACKBOUNDARY_M	0x7U
#घोषणा  INGPACKBOUNDARY_V(x)	((x) << INGPACKBOUNDARY_S)
#घोषणा  INGPACKBOUNDARY_G(x)	(((x) >> INGPACKBOUNDARY_S) \
				 & INGPACKBOUNDARY_M)

#घोषणा VFIFO_ENABLE_S    10
#घोषणा VFIFO_ENABLE_V(x) ((x) << VFIFO_ENABLE_S)
#घोषणा VFIFO_ENABLE_F    VFIFO_ENABLE_V(1U)

#घोषणा SGE_DBVFIFO_BADDR_A 0x1138

#घोषणा DBVFIFO_SIZE_S    6
#घोषणा DBVFIFO_SIZE_M    0xfffU
#घोषणा DBVFIFO_SIZE_G(x) (((x) >> DBVFIFO_SIZE_S) & DBVFIFO_SIZE_M)

#घोषणा T6_DBVFIFO_SIZE_S    0
#घोषणा T6_DBVFIFO_SIZE_M    0x1fffU
#घोषणा T6_DBVFIFO_SIZE_G(x) (((x) >> T6_DBVFIFO_SIZE_S) & T6_DBVFIFO_SIZE_M)

#घोषणा SGE_CTXT_CMD_A 0x11fc

#घोषणा BUSY_S    31
#घोषणा BUSY_V(x) ((x) << BUSY_S)
#घोषणा BUSY_F    BUSY_V(1U)

#घोषणा CTXTTYPE_S    24
#घोषणा CTXTTYPE_M    0x3U
#घोषणा CTXTTYPE_V(x) ((x) << CTXTTYPE_S)

#घोषणा CTXTQID_S    0
#घोषणा CTXTQID_M    0x1ffffU
#घोषणा CTXTQID_V(x) ((x) << CTXTQID_S)

#घोषणा SGE_CTXT_DATA0_A 0x1200
#घोषणा SGE_CTXT_DATA5_A 0x1214

#घोषणा GLOBALENABLE_S    0
#घोषणा GLOBALENABLE_V(x) ((x) << GLOBALENABLE_S)
#घोषणा GLOBALENABLE_F    GLOBALENABLE_V(1U)

#घोषणा SGE_HOST_PAGE_SIZE_A 0x100c

#घोषणा HOSTPAGESIZEPF7_S    28
#घोषणा HOSTPAGESIZEPF7_M    0xfU
#घोषणा HOSTPAGESIZEPF7_V(x) ((x) << HOSTPAGESIZEPF7_S)
#घोषणा HOSTPAGESIZEPF7_G(x) (((x) >> HOSTPAGESIZEPF7_S) & HOSTPAGESIZEPF7_M)

#घोषणा HOSTPAGESIZEPF6_S    24
#घोषणा HOSTPAGESIZEPF6_M    0xfU
#घोषणा HOSTPAGESIZEPF6_V(x) ((x) << HOSTPAGESIZEPF6_S)
#घोषणा HOSTPAGESIZEPF6_G(x) (((x) >> HOSTPAGESIZEPF6_S) & HOSTPAGESIZEPF6_M)

#घोषणा HOSTPAGESIZEPF5_S    20
#घोषणा HOSTPAGESIZEPF5_M    0xfU
#घोषणा HOSTPAGESIZEPF5_V(x) ((x) << HOSTPAGESIZEPF5_S)
#घोषणा HOSTPAGESIZEPF5_G(x) (((x) >> HOSTPAGESIZEPF5_S) & HOSTPAGESIZEPF5_M)

#घोषणा HOSTPAGESIZEPF4_S    16
#घोषणा HOSTPAGESIZEPF4_M    0xfU
#घोषणा HOSTPAGESIZEPF4_V(x) ((x) << HOSTPAGESIZEPF4_S)
#घोषणा HOSTPAGESIZEPF4_G(x) (((x) >> HOSTPAGESIZEPF4_S) & HOSTPAGESIZEPF4_M)

#घोषणा HOSTPAGESIZEPF3_S    12
#घोषणा HOSTPAGESIZEPF3_M    0xfU
#घोषणा HOSTPAGESIZEPF3_V(x) ((x) << HOSTPAGESIZEPF3_S)
#घोषणा HOSTPAGESIZEPF3_G(x) (((x) >> HOSTPAGESIZEPF3_S) & HOSTPAGESIZEPF3_M)

#घोषणा HOSTPAGESIZEPF2_S    8
#घोषणा HOSTPAGESIZEPF2_M    0xfU
#घोषणा HOSTPAGESIZEPF2_V(x) ((x) << HOSTPAGESIZEPF2_S)
#घोषणा HOSTPAGESIZEPF2_G(x) (((x) >> HOSTPAGESIZEPF2_S) & HOSTPAGESIZEPF2_M)

#घोषणा HOSTPAGESIZEPF1_S    4
#घोषणा HOSTPAGESIZEPF1_M    0xfU
#घोषणा HOSTPAGESIZEPF1_V(x) ((x) << HOSTPAGESIZEPF1_S)
#घोषणा HOSTPAGESIZEPF1_G(x) (((x) >> HOSTPAGESIZEPF1_S) & HOSTPAGESIZEPF1_M)

#घोषणा HOSTPAGESIZEPF0_S    0
#घोषणा HOSTPAGESIZEPF0_M    0xfU
#घोषणा HOSTPAGESIZEPF0_V(x) ((x) << HOSTPAGESIZEPF0_S)
#घोषणा HOSTPAGESIZEPF0_G(x) (((x) >> HOSTPAGESIZEPF0_S) & HOSTPAGESIZEPF0_M)

#घोषणा SGE_EGRESS_QUEUES_PER_PAGE_PF_A 0x1010
#घोषणा SGE_EGRESS_QUEUES_PER_PAGE_VF_A 0x1014

#घोषणा QUEUESPERPAGEPF1_S    4

#घोषणा QUEUESPERPAGEPF0_S    0
#घोषणा QUEUESPERPAGEPF0_M    0xfU
#घोषणा QUEUESPERPAGEPF0_V(x) ((x) << QUEUESPERPAGEPF0_S)
#घोषणा QUEUESPERPAGEPF0_G(x) (((x) >> QUEUESPERPAGEPF0_S) & QUEUESPERPAGEPF0_M)

#घोषणा SGE_INT_CAUSE1_A	0x1024
#घोषणा SGE_INT_CAUSE2_A	0x1030
#घोषणा SGE_INT_CAUSE3_A	0x103c

#घोषणा ERR_FLM_DBP_S    31
#घोषणा ERR_FLM_DBP_V(x) ((x) << ERR_FLM_DBP_S)
#घोषणा ERR_FLM_DBP_F    ERR_FLM_DBP_V(1U)

#घोषणा ERR_FLM_IDMA1_S    30
#घोषणा ERR_FLM_IDMA1_V(x) ((x) << ERR_FLM_IDMA1_S)
#घोषणा ERR_FLM_IDMA1_F    ERR_FLM_IDMA1_V(1U)

#घोषणा ERR_FLM_IDMA0_S    29
#घोषणा ERR_FLM_IDMA0_V(x) ((x) << ERR_FLM_IDMA0_S)
#घोषणा ERR_FLM_IDMA0_F    ERR_FLM_IDMA0_V(1U)

#घोषणा ERR_FLM_HINT_S    28
#घोषणा ERR_FLM_HINT_V(x) ((x) << ERR_FLM_HINT_S)
#घोषणा ERR_FLM_HINT_F    ERR_FLM_HINT_V(1U)

#घोषणा ERR_PCIE_ERROR3_S    27
#घोषणा ERR_PCIE_ERROR3_V(x) ((x) << ERR_PCIE_ERROR3_S)
#घोषणा ERR_PCIE_ERROR3_F    ERR_PCIE_ERROR3_V(1U)

#घोषणा ERR_PCIE_ERROR2_S    26
#घोषणा ERR_PCIE_ERROR2_V(x) ((x) << ERR_PCIE_ERROR2_S)
#घोषणा ERR_PCIE_ERROR2_F    ERR_PCIE_ERROR2_V(1U)

#घोषणा ERR_PCIE_ERROR1_S    25
#घोषणा ERR_PCIE_ERROR1_V(x) ((x) << ERR_PCIE_ERROR1_S)
#घोषणा ERR_PCIE_ERROR1_F    ERR_PCIE_ERROR1_V(1U)

#घोषणा ERR_PCIE_ERROR0_S    24
#घोषणा ERR_PCIE_ERROR0_V(x) ((x) << ERR_PCIE_ERROR0_S)
#घोषणा ERR_PCIE_ERROR0_F    ERR_PCIE_ERROR0_V(1U)

#घोषणा ERR_CPL_EXCEED_IQE_SIZE_S    22
#घोषणा ERR_CPL_EXCEED_IQE_SIZE_V(x) ((x) << ERR_CPL_EXCEED_IQE_SIZE_S)
#घोषणा ERR_CPL_EXCEED_IQE_SIZE_F    ERR_CPL_EXCEED_IQE_SIZE_V(1U)

#घोषणा ERR_INVALID_CIDX_INC_S    21
#घोषणा ERR_INVALID_CIDX_INC_V(x) ((x) << ERR_INVALID_CIDX_INC_S)
#घोषणा ERR_INVALID_CIDX_INC_F    ERR_INVALID_CIDX_INC_V(1U)

#घोषणा ERR_CPL_OPCODE_0_S    19
#घोषणा ERR_CPL_OPCODE_0_V(x) ((x) << ERR_CPL_OPCODE_0_S)
#घोषणा ERR_CPL_OPCODE_0_F    ERR_CPL_OPCODE_0_V(1U)

#घोषणा ERR_DROPPED_DB_S    18
#घोषणा ERR_DROPPED_DB_V(x) ((x) << ERR_DROPPED_DB_S)
#घोषणा ERR_DROPPED_DB_F    ERR_DROPPED_DB_V(1U)

#घोषणा ERR_DATA_CPL_ON_HIGH_QID1_S    17
#घोषणा ERR_DATA_CPL_ON_HIGH_QID1_V(x) ((x) << ERR_DATA_CPL_ON_HIGH_QID1_S)
#घोषणा ERR_DATA_CPL_ON_HIGH_QID1_F    ERR_DATA_CPL_ON_HIGH_QID1_V(1U)

#घोषणा ERR_DATA_CPL_ON_HIGH_QID0_S    16
#घोषणा ERR_DATA_CPL_ON_HIGH_QID0_V(x) ((x) << ERR_DATA_CPL_ON_HIGH_QID0_S)
#घोषणा ERR_DATA_CPL_ON_HIGH_QID0_F    ERR_DATA_CPL_ON_HIGH_QID0_V(1U)

#घोषणा ERR_BAD_DB_PIDX3_S    15
#घोषणा ERR_BAD_DB_PIDX3_V(x) ((x) << ERR_BAD_DB_PIDX3_S)
#घोषणा ERR_BAD_DB_PIDX3_F    ERR_BAD_DB_PIDX3_V(1U)

#घोषणा ERR_BAD_DB_PIDX2_S    14
#घोषणा ERR_BAD_DB_PIDX2_V(x) ((x) << ERR_BAD_DB_PIDX2_S)
#घोषणा ERR_BAD_DB_PIDX2_F    ERR_BAD_DB_PIDX2_V(1U)

#घोषणा ERR_BAD_DB_PIDX1_S    13
#घोषणा ERR_BAD_DB_PIDX1_V(x) ((x) << ERR_BAD_DB_PIDX1_S)
#घोषणा ERR_BAD_DB_PIDX1_F    ERR_BAD_DB_PIDX1_V(1U)

#घोषणा ERR_BAD_DB_PIDX0_S    12
#घोषणा ERR_BAD_DB_PIDX0_V(x) ((x) << ERR_BAD_DB_PIDX0_S)
#घोषणा ERR_BAD_DB_PIDX0_F    ERR_BAD_DB_PIDX0_V(1U)

#घोषणा ERR_ING_CTXT_PRIO_S    10
#घोषणा ERR_ING_CTXT_PRIO_V(x) ((x) << ERR_ING_CTXT_PRIO_S)
#घोषणा ERR_ING_CTXT_PRIO_F    ERR_ING_CTXT_PRIO_V(1U)

#घोषणा ERR_EGR_CTXT_PRIO_S    9
#घोषणा ERR_EGR_CTXT_PRIO_V(x) ((x) << ERR_EGR_CTXT_PRIO_S)
#घोषणा ERR_EGR_CTXT_PRIO_F    ERR_EGR_CTXT_PRIO_V(1U)

#घोषणा DBFIFO_HP_INT_S    8
#घोषणा DBFIFO_HP_INT_V(x) ((x) << DBFIFO_HP_INT_S)
#घोषणा DBFIFO_HP_INT_F    DBFIFO_HP_INT_V(1U)

#घोषणा DBFIFO_LP_INT_S    7
#घोषणा DBFIFO_LP_INT_V(x) ((x) << DBFIFO_LP_INT_S)
#घोषणा DBFIFO_LP_INT_F    DBFIFO_LP_INT_V(1U)

#घोषणा INGRESS_SIZE_ERR_S    5
#घोषणा INGRESS_SIZE_ERR_V(x) ((x) << INGRESS_SIZE_ERR_S)
#घोषणा INGRESS_SIZE_ERR_F    INGRESS_SIZE_ERR_V(1U)

#घोषणा EGRESS_SIZE_ERR_S    4
#घोषणा EGRESS_SIZE_ERR_V(x) ((x) << EGRESS_SIZE_ERR_S)
#घोषणा EGRESS_SIZE_ERR_F    EGRESS_SIZE_ERR_V(1U)

#घोषणा SGE_INT_ENABLE3_A 0x1040
#घोषणा SGE_FL_BUFFER_SIZE0_A 0x1044
#घोषणा SGE_FL_BUFFER_SIZE1_A 0x1048
#घोषणा SGE_FL_BUFFER_SIZE2_A 0x104c
#घोषणा SGE_FL_BUFFER_SIZE3_A 0x1050
#घोषणा SGE_FL_BUFFER_SIZE4_A 0x1054
#घोषणा SGE_FL_BUFFER_SIZE5_A 0x1058
#घोषणा SGE_FL_BUFFER_SIZE6_A 0x105c
#घोषणा SGE_FL_BUFFER_SIZE7_A 0x1060
#घोषणा SGE_FL_BUFFER_SIZE8_A 0x1064

#घोषणा SGE_IMSG_CTXT_BADDR_A 0x1088
#घोषणा SGE_FLM_CACHE_BADDR_A 0x108c
#घोषणा SGE_FLM_CFG_A 0x1090

#घोषणा NOHDR_S    18
#घोषणा NOHDR_V(x) ((x) << NOHDR_S)
#घोषणा NOHDR_F    NOHDR_V(1U)

#घोषणा HDRSTARTFLQ_S    11
#घोषणा HDRSTARTFLQ_M    0x7U
#घोषणा HDRSTARTFLQ_G(x) (((x) >> HDRSTARTFLQ_S) & HDRSTARTFLQ_M)

#घोषणा SGE_INGRESS_RX_THRESHOLD_A 0x10a0

#घोषणा THRESHOLD_0_S    24
#घोषणा THRESHOLD_0_M    0x3fU
#घोषणा THRESHOLD_0_V(x) ((x) << THRESHOLD_0_S)
#घोषणा THRESHOLD_0_G(x) (((x) >> THRESHOLD_0_S) & THRESHOLD_0_M)

#घोषणा THRESHOLD_1_S    16
#घोषणा THRESHOLD_1_M    0x3fU
#घोषणा THRESHOLD_1_V(x) ((x) << THRESHOLD_1_S)
#घोषणा THRESHOLD_1_G(x) (((x) >> THRESHOLD_1_S) & THRESHOLD_1_M)

#घोषणा THRESHOLD_2_S    8
#घोषणा THRESHOLD_2_M    0x3fU
#घोषणा THRESHOLD_2_V(x) ((x) << THRESHOLD_2_S)
#घोषणा THRESHOLD_2_G(x) (((x) >> THRESHOLD_2_S) & THRESHOLD_2_M)

#घोषणा THRESHOLD_3_S    0
#घोषणा THRESHOLD_3_M    0x3fU
#घोषणा THRESHOLD_3_V(x) ((x) << THRESHOLD_3_S)
#घोषणा THRESHOLD_3_G(x) (((x) >> THRESHOLD_3_S) & THRESHOLD_3_M)

#घोषणा SGE_CONM_CTRL_A 0x1094

#घोषणा EGRTHRESHOLD_S    8
#घोषणा EGRTHRESHOLD_M    0x3fU
#घोषणा EGRTHRESHOLD_V(x) ((x) << EGRTHRESHOLD_S)
#घोषणा EGRTHRESHOLD_G(x) (((x) >> EGRTHRESHOLD_S) & EGRTHRESHOLD_M)

#घोषणा EGRTHRESHOLDPACKING_S    14
#घोषणा EGRTHRESHOLDPACKING_M    0x3fU
#घोषणा EGRTHRESHOLDPACKING_V(x) ((x) << EGRTHRESHOLDPACKING_S)
#घोषणा EGRTHRESHOLDPACKING_G(x) \
	(((x) >> EGRTHRESHOLDPACKING_S) & EGRTHRESHOLDPACKING_M)

#घोषणा T6_EGRTHRESHOLDPACKING_S    16
#घोषणा T6_EGRTHRESHOLDPACKING_M    0xffU
#घोषणा T6_EGRTHRESHOLDPACKING_G(x) \
	(((x) >> T6_EGRTHRESHOLDPACKING_S) & T6_EGRTHRESHOLDPACKING_M)

#घोषणा SGE_TIMESTAMP_LO_A 0x1098
#घोषणा SGE_TIMESTAMP_HI_A 0x109c

#घोषणा TSOP_S    28
#घोषणा TSOP_M    0x3U
#घोषणा TSOP_V(x) ((x) << TSOP_S)
#घोषणा TSOP_G(x) (((x) >> TSOP_S) & TSOP_M)

#घोषणा TSVAL_S    0
#घोषणा TSVAL_M    0xfffffffU
#घोषणा TSVAL_V(x) ((x) << TSVAL_S)
#घोषणा TSVAL_G(x) (((x) >> TSVAL_S) & TSVAL_M)

#घोषणा SGE_DBFIFO_STATUS_A 0x10a4
#घोषणा SGE_DBVFIFO_SIZE_A 0x113c

#घोषणा HP_INT_THRESH_S    28
#घोषणा HP_INT_THRESH_M    0xfU
#घोषणा HP_INT_THRESH_V(x) ((x) << HP_INT_THRESH_S)

#घोषणा LP_INT_THRESH_S    12
#घोषणा LP_INT_THRESH_M    0xfU
#घोषणा LP_INT_THRESH_V(x) ((x) << LP_INT_THRESH_S)

#घोषणा SGE_DOORBELL_CONTROL_A 0x10a8

#घोषणा NOCOALESCE_S    26
#घोषणा NOCOALESCE_V(x) ((x) << NOCOALESCE_S)
#घोषणा NOCOALESCE_F    NOCOALESCE_V(1U)

#घोषणा ENABLE_DROP_S    13
#घोषणा ENABLE_DROP_V(x) ((x) << ENABLE_DROP_S)
#घोषणा ENABLE_DROP_F    ENABLE_DROP_V(1U)

#घोषणा SGE_TIMER_VALUE_0_AND_1_A 0x10b8

#घोषणा TIMERVALUE0_S    16
#घोषणा TIMERVALUE0_M    0xffffU
#घोषणा TIMERVALUE0_V(x) ((x) << TIMERVALUE0_S)
#घोषणा TIMERVALUE0_G(x) (((x) >> TIMERVALUE0_S) & TIMERVALUE0_M)

#घोषणा TIMERVALUE1_S    0
#घोषणा TIMERVALUE1_M    0xffffU
#घोषणा TIMERVALUE1_V(x) ((x) << TIMERVALUE1_S)
#घोषणा TIMERVALUE1_G(x) (((x) >> TIMERVALUE1_S) & TIMERVALUE1_M)

#घोषणा SGE_TIMER_VALUE_2_AND_3_A 0x10bc

#घोषणा TIMERVALUE2_S    16
#घोषणा TIMERVALUE2_M    0xffffU
#घोषणा TIMERVALUE2_V(x) ((x) << TIMERVALUE2_S)
#घोषणा TIMERVALUE2_G(x) (((x) >> TIMERVALUE2_S) & TIMERVALUE2_M)

#घोषणा TIMERVALUE3_S    0
#घोषणा TIMERVALUE3_M    0xffffU
#घोषणा TIMERVALUE3_V(x) ((x) << TIMERVALUE3_S)
#घोषणा TIMERVALUE3_G(x) (((x) >> TIMERVALUE3_S) & TIMERVALUE3_M)

#घोषणा SGE_TIMER_VALUE_4_AND_5_A 0x10c0

#घोषणा TIMERVALUE4_S    16
#घोषणा TIMERVALUE4_M    0xffffU
#घोषणा TIMERVALUE4_V(x) ((x) << TIMERVALUE4_S)
#घोषणा TIMERVALUE4_G(x) (((x) >> TIMERVALUE4_S) & TIMERVALUE4_M)

#घोषणा TIMERVALUE5_S    0
#घोषणा TIMERVALUE5_M    0xffffU
#घोषणा TIMERVALUE5_V(x) ((x) << TIMERVALUE5_S)
#घोषणा TIMERVALUE5_G(x) (((x) >> TIMERVALUE5_S) & TIMERVALUE5_M)

#घोषणा SGE_DEBUG_INDEX_A 0x10cc
#घोषणा SGE_DEBUG_DATA_HIGH_A 0x10d0
#घोषणा SGE_DEBUG_DATA_LOW_A 0x10d4

#घोषणा SGE_DEBUG_DATA_LOW_INDEX_2_A	0x12c8
#घोषणा SGE_DEBUG_DATA_LOW_INDEX_3_A	0x12cc
#घोषणा SGE_DEBUG_DATA_HIGH_INDEX_10_A	0x12a8

#घोषणा SGE_INGRESS_QUEUES_PER_PAGE_PF_A 0x10f4
#घोषणा SGE_INGRESS_QUEUES_PER_PAGE_VF_A 0x10f8

#घोषणा SGE_ERROR_STATS_A 0x1100

#घोषणा UNCAPTURED_ERROR_S    18
#घोषणा UNCAPTURED_ERROR_V(x) ((x) << UNCAPTURED_ERROR_S)
#घोषणा UNCAPTURED_ERROR_F    UNCAPTURED_ERROR_V(1U)

#घोषणा ERROR_QID_VALID_S    17
#घोषणा ERROR_QID_VALID_V(x) ((x) << ERROR_QID_VALID_S)
#घोषणा ERROR_QID_VALID_F    ERROR_QID_VALID_V(1U)

#घोषणा ERROR_QID_S    0
#घोषणा ERROR_QID_M    0x1ffffU
#घोषणा ERROR_QID_G(x) (((x) >> ERROR_QID_S) & ERROR_QID_M)

#घोषणा SGE_INT_CAUSE5_A        0x110c

#घोषणा ERR_T_RXCRC_S    31
#घोषणा ERR_T_RXCRC_V(x) ((x) << ERR_T_RXCRC_S)
#घोषणा ERR_T_RXCRC_F    ERR_T_RXCRC_V(1U)

#घोषणा HP_INT_THRESH_S    28
#घोषणा HP_INT_THRESH_M    0xfU
#घोषणा HP_INT_THRESH_V(x) ((x) << HP_INT_THRESH_S)

#घोषणा HP_COUNT_S    16
#घोषणा HP_COUNT_M    0x7ffU
#घोषणा HP_COUNT_G(x) (((x) >> HP_COUNT_S) & HP_COUNT_M)

#घोषणा LP_INT_THRESH_S    12
#घोषणा LP_INT_THRESH_M    0xfU
#घोषणा LP_INT_THRESH_V(x) ((x) << LP_INT_THRESH_S)

#घोषणा LP_COUNT_S    0
#घोषणा LP_COUNT_M    0x7ffU
#घोषणा LP_COUNT_G(x) (((x) >> LP_COUNT_S) & LP_COUNT_M)

#घोषणा LP_INT_THRESH_T5_S    18
#घोषणा LP_INT_THRESH_T5_M    0xfffU
#घोषणा LP_INT_THRESH_T5_V(x) ((x) << LP_INT_THRESH_T5_S)

#घोषणा LP_COUNT_T5_S    0
#घोषणा LP_COUNT_T5_M    0x3ffffU
#घोषणा LP_COUNT_T5_G(x) (((x) >> LP_COUNT_T5_S) & LP_COUNT_T5_M)

#घोषणा SGE_DOORBELL_CONTROL_A 0x10a8

#घोषणा SGE_STAT_TOTAL_A	0x10e4
#घोषणा SGE_STAT_MATCH_A	0x10e8
#घोषणा SGE_STAT_CFG_A		0x10ec

#घोषणा STATMODE_S    2
#घोषणा STATMODE_V(x) ((x) << STATMODE_S)

#घोषणा STATSOURCE_T5_S    9
#घोषणा STATSOURCE_T5_M    0xfU
#घोषणा STATSOURCE_T5_V(x) ((x) << STATSOURCE_T5_S)
#घोषणा STATSOURCE_T5_G(x) (((x) >> STATSOURCE_T5_S) & STATSOURCE_T5_M)

#घोषणा T6_STATMODE_S    0
#घोषणा T6_STATMODE_V(x) ((x) << T6_STATMODE_S)

#घोषणा SGE_DBFIFO_STATUS2_A 0x1118

#घोषणा HP_INT_THRESH_T5_S    10
#घोषणा HP_INT_THRESH_T5_M    0xfU
#घोषणा HP_INT_THRESH_T5_V(x) ((x) << HP_INT_THRESH_T5_S)

#घोषणा HP_COUNT_T5_S    0
#घोषणा HP_COUNT_T5_M    0x3ffU
#घोषणा HP_COUNT_T5_G(x) (((x) >> HP_COUNT_T5_S) & HP_COUNT_T5_M)

#घोषणा ENABLE_DROP_S    13
#घोषणा ENABLE_DROP_V(x) ((x) << ENABLE_DROP_S)
#घोषणा ENABLE_DROP_F    ENABLE_DROP_V(1U)

#घोषणा DROPPED_DB_S    0
#घोषणा DROPPED_DB_V(x) ((x) << DROPPED_DB_S)
#घोषणा DROPPED_DB_F    DROPPED_DB_V(1U)

#घोषणा SGE_CTXT_CMD_A 0x11fc
#घोषणा SGE_DBQ_CTXT_BADDR_A 0x1084

/* रेजिस्टरs क्रम module PCIE */
#घोषणा PCIE_PF_CFG_A	0x40

#घोषणा AIVEC_S    4
#घोषणा AIVEC_M    0x3ffU
#घोषणा AIVEC_V(x) ((x) << AIVEC_S)

#घोषणा PCIE_PF_CLI_A	0x44

#घोषणा PCIE_PF_EXPROM_OFST_A 0x4c
#घोषणा OFFSET_S    10
#घोषणा OFFSET_M    0x3fffU
#घोषणा OFFSET_G(x) (((x) >> OFFSET_S) & OFFSET_M)

#घोषणा PCIE_INT_CAUSE_A	0x3004

#घोषणा UNXSPLCPLERR_S    29
#घोषणा UNXSPLCPLERR_V(x) ((x) << UNXSPLCPLERR_S)
#घोषणा UNXSPLCPLERR_F    UNXSPLCPLERR_V(1U)

#घोषणा PCIEPINT_S    28
#घोषणा PCIEPINT_V(x) ((x) << PCIEPINT_S)
#घोषणा PCIEPINT_F    PCIEPINT_V(1U)

#घोषणा PCIESINT_S    27
#घोषणा PCIESINT_V(x) ((x) << PCIESINT_S)
#घोषणा PCIESINT_F    PCIESINT_V(1U)

#घोषणा RPLPERR_S    26
#घोषणा RPLPERR_V(x) ((x) << RPLPERR_S)
#घोषणा RPLPERR_F    RPLPERR_V(1U)

#घोषणा RXWRPERR_S    25
#घोषणा RXWRPERR_V(x) ((x) << RXWRPERR_S)
#घोषणा RXWRPERR_F    RXWRPERR_V(1U)

#घोषणा RXCPLPERR_S    24
#घोषणा RXCPLPERR_V(x) ((x) << RXCPLPERR_S)
#घोषणा RXCPLPERR_F    RXCPLPERR_V(1U)

#घोषणा PIOTAGPERR_S    23
#घोषणा PIOTAGPERR_V(x) ((x) << PIOTAGPERR_S)
#घोषणा PIOTAGPERR_F    PIOTAGPERR_V(1U)

#घोषणा MATAGPERR_S    22
#घोषणा MATAGPERR_V(x) ((x) << MATAGPERR_S)
#घोषणा MATAGPERR_F    MATAGPERR_V(1U)

#घोषणा INTXCLRPERR_S    21
#घोषणा INTXCLRPERR_V(x) ((x) << INTXCLRPERR_S)
#घोषणा INTXCLRPERR_F    INTXCLRPERR_V(1U)

#घोषणा FIDPERR_S    20
#घोषणा FIDPERR_V(x) ((x) << FIDPERR_S)
#घोषणा FIDPERR_F    FIDPERR_V(1U)

#घोषणा CFGSNPPERR_S    19
#घोषणा CFGSNPPERR_V(x) ((x) << CFGSNPPERR_S)
#घोषणा CFGSNPPERR_F    CFGSNPPERR_V(1U)

#घोषणा HRSPPERR_S    18
#घोषणा HRSPPERR_V(x) ((x) << HRSPPERR_S)
#घोषणा HRSPPERR_F    HRSPPERR_V(1U)

#घोषणा HREQPERR_S    17
#घोषणा HREQPERR_V(x) ((x) << HREQPERR_S)
#घोषणा HREQPERR_F    HREQPERR_V(1U)

#घोषणा HCNTPERR_S    16
#घोषणा HCNTPERR_V(x) ((x) << HCNTPERR_S)
#घोषणा HCNTPERR_F    HCNTPERR_V(1U)

#घोषणा DRSPPERR_S    15
#घोषणा DRSPPERR_V(x) ((x) << DRSPPERR_S)
#घोषणा DRSPPERR_F    DRSPPERR_V(1U)

#घोषणा DREQPERR_S    14
#घोषणा DREQPERR_V(x) ((x) << DREQPERR_S)
#घोषणा DREQPERR_F    DREQPERR_V(1U)

#घोषणा DCNTPERR_S    13
#घोषणा DCNTPERR_V(x) ((x) << DCNTPERR_S)
#घोषणा DCNTPERR_F    DCNTPERR_V(1U)

#घोषणा CRSPPERR_S    12
#घोषणा CRSPPERR_V(x) ((x) << CRSPPERR_S)
#घोषणा CRSPPERR_F    CRSPPERR_V(1U)

#घोषणा CREQPERR_S    11
#घोषणा CREQPERR_V(x) ((x) << CREQPERR_S)
#घोषणा CREQPERR_F    CREQPERR_V(1U)

#घोषणा CCNTPERR_S    10
#घोषणा CCNTPERR_V(x) ((x) << CCNTPERR_S)
#घोषणा CCNTPERR_F    CCNTPERR_V(1U)

#घोषणा TARTAGPERR_S    9
#घोषणा TARTAGPERR_V(x) ((x) << TARTAGPERR_S)
#घोषणा TARTAGPERR_F    TARTAGPERR_V(1U)

#घोषणा PIOREQPERR_S    8
#घोषणा PIOREQPERR_V(x) ((x) << PIOREQPERR_S)
#घोषणा PIOREQPERR_F    PIOREQPERR_V(1U)

#घोषणा PIOCPLPERR_S    7
#घोषणा PIOCPLPERR_V(x) ((x) << PIOCPLPERR_S)
#घोषणा PIOCPLPERR_F    PIOCPLPERR_V(1U)

#घोषणा MSIXDIPERR_S    6
#घोषणा MSIXDIPERR_V(x) ((x) << MSIXDIPERR_S)
#घोषणा MSIXDIPERR_F    MSIXDIPERR_V(1U)

#घोषणा MSIXDATAPERR_S    5
#घोषणा MSIXDATAPERR_V(x) ((x) << MSIXDATAPERR_S)
#घोषणा MSIXDATAPERR_F    MSIXDATAPERR_V(1U)

#घोषणा MSIXADDRHPERR_S    4
#घोषणा MSIXADDRHPERR_V(x) ((x) << MSIXADDRHPERR_S)
#घोषणा MSIXADDRHPERR_F    MSIXADDRHPERR_V(1U)

#घोषणा MSIXADDRLPERR_S    3
#घोषणा MSIXADDRLPERR_V(x) ((x) << MSIXADDRLPERR_S)
#घोषणा MSIXADDRLPERR_F    MSIXADDRLPERR_V(1U)

#घोषणा MSIDATAPERR_S    2
#घोषणा MSIDATAPERR_V(x) ((x) << MSIDATAPERR_S)
#घोषणा MSIDATAPERR_F    MSIDATAPERR_V(1U)

#घोषणा MSIADDRHPERR_S    1
#घोषणा MSIADDRHPERR_V(x) ((x) << MSIADDRHPERR_S)
#घोषणा MSIADDRHPERR_F    MSIADDRHPERR_V(1U)

#घोषणा MSIADDRLPERR_S    0
#घोषणा MSIADDRLPERR_V(x) ((x) << MSIADDRLPERR_S)
#घोषणा MSIADDRLPERR_F    MSIADDRLPERR_V(1U)

#घोषणा READRSPERR_S    29
#घोषणा READRSPERR_V(x) ((x) << READRSPERR_S)
#घोषणा READRSPERR_F    READRSPERR_V(1U)

#घोषणा TRGT1GRPPERR_S    28
#घोषणा TRGT1GRPPERR_V(x) ((x) << TRGT1GRPPERR_S)
#घोषणा TRGT1GRPPERR_F    TRGT1GRPPERR_V(1U)

#घोषणा IPSOTPERR_S    27
#घोषणा IPSOTPERR_V(x) ((x) << IPSOTPERR_S)
#घोषणा IPSOTPERR_F    IPSOTPERR_V(1U)

#घोषणा IPRETRYPERR_S    26
#घोषणा IPRETRYPERR_V(x) ((x) << IPRETRYPERR_S)
#घोषणा IPRETRYPERR_F    IPRETRYPERR_V(1U)

#घोषणा IPRXDATAGRPPERR_S    25
#घोषणा IPRXDATAGRPPERR_V(x) ((x) << IPRXDATAGRPPERR_S)
#घोषणा IPRXDATAGRPPERR_F    IPRXDATAGRPPERR_V(1U)

#घोषणा IPRXHDRGRPPERR_S    24
#घोषणा IPRXHDRGRPPERR_V(x) ((x) << IPRXHDRGRPPERR_S)
#घोषणा IPRXHDRGRPPERR_F    IPRXHDRGRPPERR_V(1U)

#घोषणा MAGRPPERR_S    22
#घोषणा MAGRPPERR_V(x) ((x) << MAGRPPERR_S)
#घोषणा MAGRPPERR_F    MAGRPPERR_V(1U)

#घोषणा VFIDPERR_S    21
#घोषणा VFIDPERR_V(x) ((x) << VFIDPERR_S)
#घोषणा VFIDPERR_F    VFIDPERR_V(1U)

#घोषणा HREQWRPERR_S    16
#घोषणा HREQWRPERR_V(x) ((x) << HREQWRPERR_S)
#घोषणा HREQWRPERR_F    HREQWRPERR_V(1U)

#घोषणा DREQWRPERR_S    13
#घोषणा DREQWRPERR_V(x) ((x) << DREQWRPERR_S)
#घोषणा DREQWRPERR_F    DREQWRPERR_V(1U)

#घोषणा CREQRDPERR_S    11
#घोषणा CREQRDPERR_V(x) ((x) << CREQRDPERR_S)
#घोषणा CREQRDPERR_F    CREQRDPERR_V(1U)

#घोषणा MSTTAGQPERR_S    10
#घोषणा MSTTAGQPERR_V(x) ((x) << MSTTAGQPERR_S)
#घोषणा MSTTAGQPERR_F    MSTTAGQPERR_V(1U)

#घोषणा PIOREQGRPPERR_S    8
#घोषणा PIOREQGRPPERR_V(x) ((x) << PIOREQGRPPERR_S)
#घोषणा PIOREQGRPPERR_F    PIOREQGRPPERR_V(1U)

#घोषणा PIOCPLGRPPERR_S    7
#घोषणा PIOCPLGRPPERR_V(x) ((x) << PIOCPLGRPPERR_S)
#घोषणा PIOCPLGRPPERR_F    PIOCPLGRPPERR_V(1U)

#घोषणा MSIXSTIPERR_S    2
#घोषणा MSIXSTIPERR_V(x) ((x) << MSIXSTIPERR_S)
#घोषणा MSIXSTIPERR_F    MSIXSTIPERR_V(1U)

#घोषणा MSTTIMEOUTPERR_S    1
#घोषणा MSTTIMEOUTPERR_V(x) ((x) << MSTTIMEOUTPERR_S)
#घोषणा MSTTIMEOUTPERR_F    MSTTIMEOUTPERR_V(1U)

#घोषणा MSTGRPPERR_S    0
#घोषणा MSTGRPPERR_V(x) ((x) << MSTGRPPERR_S)
#घोषणा MSTGRPPERR_F    MSTGRPPERR_V(1U)

#घोषणा PCIE_NONFAT_ERR_A	0x3010
#घोषणा PCIE_CFG_SPACE_REQ_A	0x3060
#घोषणा PCIE_CFG_SPACE_DATA_A	0x3064
#घोषणा PCIE_MEM_ACCESS_BASE_WIN_A 0x3068

#घोषणा PCIखातापूर्णST_S    10
#घोषणा PCIखातापूर्णST_M    0x3fffffU
#घोषणा PCIखातापूर्णST_G(x) (((x) >> PCIखातापूर्णST_S) & PCIखातापूर्णST_M)

#घोषणा BIR_S    8
#घोषणा BIR_M    0x3U
#घोषणा BIR_V(x) ((x) << BIR_S)
#घोषणा BIR_G(x) (((x) >> BIR_S) & BIR_M)

#घोषणा WINDOW_S    0
#घोषणा WINDOW_M    0xffU
#घोषणा WINDOW_V(x) ((x) << WINDOW_S)
#घोषणा WINDOW_G(x) (((x) >> WINDOW_S) & WINDOW_M)

#घोषणा PCIE_MEM_ACCESS_OFFSET_A 0x306c

#घोषणा ENABLE_S    30
#घोषणा ENABLE_V(x) ((x) << ENABLE_S)
#घोषणा ENABLE_F    ENABLE_V(1U)

#घोषणा LOCALCFG_S    28
#घोषणा LOCALCFG_V(x) ((x) << LOCALCFG_S)
#घोषणा LOCALCFG_F    LOCALCFG_V(1U)

#घोषणा FUNCTION_S    12
#घोषणा FUNCTION_V(x) ((x) << FUNCTION_S)

#घोषणा REGISTER_S    0
#घोषणा REGISTER_V(x) ((x) << REGISTER_S)

#घोषणा T6_ENABLE_S    31
#घोषणा T6_ENABLE_V(x) ((x) << T6_ENABLE_S)
#घोषणा T6_ENABLE_F    T6_ENABLE_V(1U)

#घोषणा PFNUM_S    0
#घोषणा PFNUM_V(x) ((x) << PFNUM_S)

#घोषणा PCIE_FW_A 0x30b8
#घोषणा PCIE_FW_PF_A 0x30bc

#घोषणा PCIE_CORE_UTL_SYSTEM_BUS_AGENT_STATUS_A 0x5908

#घोषणा RNPP_S    31
#घोषणा RNPP_V(x) ((x) << RNPP_S)
#घोषणा RNPP_F    RNPP_V(1U)

#घोषणा RPCP_S    29
#घोषणा RPCP_V(x) ((x) << RPCP_S)
#घोषणा RPCP_F    RPCP_V(1U)

#घोषणा RCIP_S    27
#घोषणा RCIP_V(x) ((x) << RCIP_S)
#घोषणा RCIP_F    RCIP_V(1U)

#घोषणा RCCP_S    26
#घोषणा RCCP_V(x) ((x) << RCCP_S)
#घोषणा RCCP_F    RCCP_V(1U)

#घोषणा RFTP_S    23
#घोषणा RFTP_V(x) ((x) << RFTP_S)
#घोषणा RFTP_F    RFTP_V(1U)

#घोषणा PTRP_S    20
#घोषणा PTRP_V(x) ((x) << PTRP_S)
#घोषणा PTRP_F    PTRP_V(1U)

#घोषणा PCIE_CORE_UTL_PCI_EXPRESS_PORT_STATUS_A 0x59a4

#घोषणा TPCP_S    30
#घोषणा TPCP_V(x) ((x) << TPCP_S)
#घोषणा TPCP_F    TPCP_V(1U)

#घोषणा TNPP_S    29
#घोषणा TNPP_V(x) ((x) << TNPP_S)
#घोषणा TNPP_F    TNPP_V(1U)

#घोषणा TFTP_S    28
#घोषणा TFTP_V(x) ((x) << TFTP_S)
#घोषणा TFTP_F    TFTP_V(1U)

#घोषणा TCAP_S    27
#घोषणा TCAP_V(x) ((x) << TCAP_S)
#घोषणा TCAP_F    TCAP_V(1U)

#घोषणा TCIP_S    26
#घोषणा TCIP_V(x) ((x) << TCIP_S)
#घोषणा TCIP_F    TCIP_V(1U)

#घोषणा RCAP_S    25
#घोषणा RCAP_V(x) ((x) << RCAP_S)
#घोषणा RCAP_F    RCAP_V(1U)

#घोषणा PLUP_S    23
#घोषणा PLUP_V(x) ((x) << PLUP_S)
#घोषणा PLUP_F    PLUP_V(1U)

#घोषणा PLDN_S    22
#घोषणा PLDN_V(x) ((x) << PLDN_S)
#घोषणा PLDN_F    PLDN_V(1U)

#घोषणा OTDD_S    21
#घोषणा OTDD_V(x) ((x) << OTDD_S)
#घोषणा OTDD_F    OTDD_V(1U)

#घोषणा GTRP_S    20
#घोषणा GTRP_V(x) ((x) << GTRP_S)
#घोषणा GTRP_F    GTRP_V(1U)

#घोषणा RDPE_S    18
#घोषणा RDPE_V(x) ((x) << RDPE_S)
#घोषणा RDPE_F    RDPE_V(1U)

#घोषणा TDCE_S    17
#घोषणा TDCE_V(x) ((x) << TDCE_S)
#घोषणा TDCE_F    TDCE_V(1U)

#घोषणा TDUE_S    16
#घोषणा TDUE_V(x) ((x) << TDUE_S)
#घोषणा TDUE_F    TDUE_V(1U)

/* SPARE2 रेजिस्टर contains 32-bit value at offset 0x6 in Serial INIT
 * Configuration flashed on EEPROM. This value corresponds to 32-bit
 * Serial Configuration Version inक्रमmation.
 */
#घोषणा PCIE_STATIC_SPARE2_A	0x5bfc

/* रेजिस्टरs क्रम module MC */
#घोषणा MC_INT_CAUSE_A		0x7518
#घोषणा MC_P_INT_CAUSE_A	0x41318

#घोषणा ECC_UE_INT_CAUSE_S    2
#घोषणा ECC_UE_INT_CAUSE_V(x) ((x) << ECC_UE_INT_CAUSE_S)
#घोषणा ECC_UE_INT_CAUSE_F    ECC_UE_INT_CAUSE_V(1U)

#घोषणा ECC_CE_INT_CAUSE_S    1
#घोषणा ECC_CE_INT_CAUSE_V(x) ((x) << ECC_CE_INT_CAUSE_S)
#घोषणा ECC_CE_INT_CAUSE_F    ECC_CE_INT_CAUSE_V(1U)

#घोषणा PERR_INT_CAUSE_S    0
#घोषणा PERR_INT_CAUSE_V(x) ((x) << PERR_INT_CAUSE_S)
#घोषणा PERR_INT_CAUSE_F    PERR_INT_CAUSE_V(1U)

#घोषणा DBG_GPIO_EN_A		0x6010
#घोषणा XGMAC_PORT_CFG_A	0x1000
#घोषणा MAC_PORT_CFG_A		0x800

#घोषणा SIGNAL_DET_S    14
#घोषणा SIGNAL_DET_V(x) ((x) << SIGNAL_DET_S)
#घोषणा SIGNAL_DET_F    SIGNAL_DET_V(1U)

#घोषणा MC_ECC_STATUS_A		0x751c
#घोषणा MC_P_ECC_STATUS_A	0x4131c

#घोषणा ECC_CECNT_S    16
#घोषणा ECC_CECNT_M    0xffffU
#घोषणा ECC_CECNT_V(x) ((x) << ECC_CECNT_S)
#घोषणा ECC_CECNT_G(x) (((x) >> ECC_CECNT_S) & ECC_CECNT_M)

#घोषणा ECC_UECNT_S    0
#घोषणा ECC_UECNT_M    0xffffU
#घोषणा ECC_UECNT_V(x) ((x) << ECC_UECNT_S)
#घोषणा ECC_UECNT_G(x) (((x) >> ECC_UECNT_S) & ECC_UECNT_M)

#घोषणा MC_BIST_CMD_A 0x7600

#घोषणा START_BIST_S    31
#घोषणा START_BIST_V(x) ((x) << START_BIST_S)
#घोषणा START_BIST_F    START_BIST_V(1U)

#घोषणा BIST_CMD_GAP_S    8
#घोषणा BIST_CMD_GAP_V(x) ((x) << BIST_CMD_GAP_S)

#घोषणा BIST_OPCODE_S    0
#घोषणा BIST_OPCODE_V(x) ((x) << BIST_OPCODE_S)

#घोषणा MC_BIST_CMD_ADDR_A 0x7604
#घोषणा MC_BIST_CMD_LEN_A 0x7608
#घोषणा MC_BIST_DATA_PATTERN_A 0x760c

#घोषणा MC_BIST_STATUS_RDATA_A 0x7688

/* रेजिस्टरs क्रम module MA */
#घोषणा MA_EDRAM0_BAR_A 0x77c0

#घोषणा EDRAM0_BASE_S    16
#घोषणा EDRAM0_BASE_M    0xfffU
#घोषणा EDRAM0_BASE_G(x) (((x) >> EDRAM0_BASE_S) & EDRAM0_BASE_M)

#घोषणा EDRAM0_SIZE_S    0
#घोषणा EDRAM0_SIZE_M    0xfffU
#घोषणा EDRAM0_SIZE_V(x) ((x) << EDRAM0_SIZE_S)
#घोषणा EDRAM0_SIZE_G(x) (((x) >> EDRAM0_SIZE_S) & EDRAM0_SIZE_M)

#घोषणा MA_EDRAM1_BAR_A 0x77c4

#घोषणा EDRAM1_BASE_S    16
#घोषणा EDRAM1_BASE_M    0xfffU
#घोषणा EDRAM1_BASE_G(x) (((x) >> EDRAM1_BASE_S) & EDRAM1_BASE_M)

#घोषणा EDRAM1_SIZE_S    0
#घोषणा EDRAM1_SIZE_M    0xfffU
#घोषणा EDRAM1_SIZE_V(x) ((x) << EDRAM1_SIZE_S)
#घोषणा EDRAM1_SIZE_G(x) (((x) >> EDRAM1_SIZE_S) & EDRAM1_SIZE_M)

#घोषणा MA_EXT_MEMORY_BAR_A 0x77c8

#घोषणा EXT_MEM_BASE_S    16
#घोषणा EXT_MEM_BASE_M    0xfffU
#घोषणा EXT_MEM_BASE_V(x) ((x) << EXT_MEM_BASE_S)
#घोषणा EXT_MEM_BASE_G(x) (((x) >> EXT_MEM_BASE_S) & EXT_MEM_BASE_M)

#घोषणा EXT_MEM_SIZE_S    0
#घोषणा EXT_MEM_SIZE_M    0xfffU
#घोषणा EXT_MEM_SIZE_V(x) ((x) << EXT_MEM_SIZE_S)
#घोषणा EXT_MEM_SIZE_G(x) (((x) >> EXT_MEM_SIZE_S) & EXT_MEM_SIZE_M)

#घोषणा MA_EXT_MEMORY1_BAR_A 0x7808

#घोषणा HMA_MUX_S    5
#घोषणा HMA_MUX_V(x) ((x) << HMA_MUX_S)
#घोषणा HMA_MUX_F    HMA_MUX_V(1U)

#घोषणा EXT_MEM1_BASE_S    16
#घोषणा EXT_MEM1_BASE_M    0xfffU
#घोषणा EXT_MEM1_BASE_G(x) (((x) >> EXT_MEM1_BASE_S) & EXT_MEM1_BASE_M)

#घोषणा EXT_MEM1_SIZE_S    0
#घोषणा EXT_MEM1_SIZE_M    0xfffU
#घोषणा EXT_MEM1_SIZE_V(x) ((x) << EXT_MEM1_SIZE_S)
#घोषणा EXT_MEM1_SIZE_G(x) (((x) >> EXT_MEM1_SIZE_S) & EXT_MEM1_SIZE_M)

#घोषणा MA_EXT_MEMORY0_BAR_A 0x77c8

#घोषणा EXT_MEM0_BASE_S    16
#घोषणा EXT_MEM0_BASE_M    0xfffU
#घोषणा EXT_MEM0_BASE_G(x) (((x) >> EXT_MEM0_BASE_S) & EXT_MEM0_BASE_M)

#घोषणा EXT_MEM0_SIZE_S    0
#घोषणा EXT_MEM0_SIZE_M    0xfffU
#घोषणा EXT_MEM0_SIZE_V(x) ((x) << EXT_MEM0_SIZE_S)
#घोषणा EXT_MEM0_SIZE_G(x) (((x) >> EXT_MEM0_SIZE_S) & EXT_MEM0_SIZE_M)

#घोषणा MA_TARGET_MEM_ENABLE_A 0x77d8

#घोषणा EXT_MEM_ENABLE_S    2
#घोषणा EXT_MEM_ENABLE_V(x) ((x) << EXT_MEM_ENABLE_S)
#घोषणा EXT_MEM_ENABLE_F    EXT_MEM_ENABLE_V(1U)

#घोषणा EDRAM1_ENABLE_S    1
#घोषणा EDRAM1_ENABLE_V(x) ((x) << EDRAM1_ENABLE_S)
#घोषणा EDRAM1_ENABLE_F    EDRAM1_ENABLE_V(1U)

#घोषणा EDRAM0_ENABLE_S    0
#घोषणा EDRAM0_ENABLE_V(x) ((x) << EDRAM0_ENABLE_S)
#घोषणा EDRAM0_ENABLE_F    EDRAM0_ENABLE_V(1U)

#घोषणा EXT_MEM1_ENABLE_S    4
#घोषणा EXT_MEM1_ENABLE_V(x) ((x) << EXT_MEM1_ENABLE_S)
#घोषणा EXT_MEM1_ENABLE_F    EXT_MEM1_ENABLE_V(1U)

#घोषणा EXT_MEM0_ENABLE_S    2
#घोषणा EXT_MEM0_ENABLE_V(x) ((x) << EXT_MEM0_ENABLE_S)
#घोषणा EXT_MEM0_ENABLE_F    EXT_MEM0_ENABLE_V(1U)

#घोषणा MA_INT_CAUSE_A	0x77e0

#घोषणा MEM_PERR_INT_CAUSE_S    1
#घोषणा MEM_PERR_INT_CAUSE_V(x) ((x) << MEM_PERR_INT_CAUSE_S)
#घोषणा MEM_PERR_INT_CAUSE_F    MEM_PERR_INT_CAUSE_V(1U)

#घोषणा MEM_WRAP_INT_CAUSE_S    0
#घोषणा MEM_WRAP_INT_CAUSE_V(x) ((x) << MEM_WRAP_INT_CAUSE_S)
#घोषणा MEM_WRAP_INT_CAUSE_F    MEM_WRAP_INT_CAUSE_V(1U)

#घोषणा MA_INT_WRAP_STATUS_A	0x77e4

#घोषणा MEM_WRAP_ADDRESS_S    4
#घोषणा MEM_WRAP_ADDRESS_M    0xfffffffU
#घोषणा MEM_WRAP_ADDRESS_G(x) (((x) >> MEM_WRAP_ADDRESS_S) & MEM_WRAP_ADDRESS_M)

#घोषणा MEM_WRAP_CLIENT_NUM_S    0
#घोषणा MEM_WRAP_CLIENT_NUM_M    0xfU
#घोषणा MEM_WRAP_CLIENT_NUM_G(x) \
	(((x) >> MEM_WRAP_CLIENT_NUM_S) & MEM_WRAP_CLIENT_NUM_M)

#घोषणा MA_PARITY_ERROR_STATUS_A	0x77f4
#घोषणा MA_PARITY_ERROR_STATUS1_A	0x77f4
#घोषणा MA_PARITY_ERROR_STATUS2_A	0x7804

/* रेजिस्टरs क्रम module EDC_0 */
#घोषणा EDC_0_BASE_ADDR		0x7900

#घोषणा EDC_BIST_CMD_A		0x7904
#घोषणा EDC_BIST_CMD_ADDR_A	0x7908
#घोषणा EDC_BIST_CMD_LEN_A	0x790c
#घोषणा EDC_BIST_DATA_PATTERN_A 0x7910
#घोषणा EDC_BIST_STATUS_RDATA_A	0x7928
#घोषणा EDC_INT_CAUSE_A		0x7978

#घोषणा ECC_UE_PAR_S    5
#घोषणा ECC_UE_PAR_V(x) ((x) << ECC_UE_PAR_S)
#घोषणा ECC_UE_PAR_F    ECC_UE_PAR_V(1U)

#घोषणा ECC_CE_PAR_S    4
#घोषणा ECC_CE_PAR_V(x) ((x) << ECC_CE_PAR_S)
#घोषणा ECC_CE_PAR_F    ECC_CE_PAR_V(1U)

#घोषणा PERR_PAR_CAUSE_S    3
#घोषणा PERR_PAR_CAUSE_V(x) ((x) << PERR_PAR_CAUSE_S)
#घोषणा PERR_PAR_CAUSE_F    PERR_PAR_CAUSE_V(1U)

#घोषणा EDC_ECC_STATUS_A	0x797c

/* रेजिस्टरs क्रम module EDC_1 */
#घोषणा EDC_1_BASE_ADDR	0x7980

/* रेजिस्टरs क्रम module CIM */
#घोषणा CIM_BOOT_CFG_A 0x7b00
#घोषणा CIM_SDRAM_BASE_ADDR_A 0x7b14
#घोषणा CIM_SDRAM_ADDR_SIZE_A 0x7b18
#घोषणा CIM_EXTMEM2_BASE_ADDR_A 0x7b1c
#घोषणा CIM_EXTMEM2_ADDR_SIZE_A 0x7b20
#घोषणा CIM_PF_MAILBOX_CTRL_SHADOW_COPY_A 0x290

#घोषणा  BOOTADDR_M	0xffffff00U

#घोषणा UPCRST_S    0
#घोषणा UPCRST_V(x) ((x) << UPCRST_S)
#घोषणा UPCRST_F    UPCRST_V(1U)

#घोषणा CIM_PF_MAILBOX_DATA_A 0x240
#घोषणा CIM_PF_MAILBOX_CTRL_A 0x280

#घोषणा MBMSGVALID_S    3
#घोषणा MBMSGVALID_V(x) ((x) << MBMSGVALID_S)
#घोषणा MBMSGVALID_F    MBMSGVALID_V(1U)

#घोषणा MBINTREQ_S    2
#घोषणा MBINTREQ_V(x) ((x) << MBINTREQ_S)
#घोषणा MBINTREQ_F    MBINTREQ_V(1U)

#घोषणा MBOWNER_S    0
#घोषणा MBOWNER_M    0x3U
#घोषणा MBOWNER_V(x) ((x) << MBOWNER_S)
#घोषणा MBOWNER_G(x) (((x) >> MBOWNER_S) & MBOWNER_M)

#घोषणा CIM_PF_HOST_INT_ENABLE_A 0x288

#घोषणा MBMSGRDYINTEN_S    19
#घोषणा MBMSGRDYINTEN_V(x) ((x) << MBMSGRDYINTEN_S)
#घोषणा MBMSGRDYINTEN_F    MBMSGRDYINTEN_V(1U)

#घोषणा CIM_PF_HOST_INT_CAUSE_A 0x28c

#घोषणा MBMSGRDYINT_S    19
#घोषणा MBMSGRDYINT_V(x) ((x) << MBMSGRDYINT_S)
#घोषणा MBMSGRDYINT_F    MBMSGRDYINT_V(1U)

#घोषणा CIM_HOST_INT_CAUSE_A 0x7b2c

#घोषणा TIEQOUTPARERRINT_S    20
#घोषणा TIEQOUTPARERRINT_V(x) ((x) << TIEQOUTPARERRINT_S)
#घोषणा TIEQOUTPARERRINT_F    TIEQOUTPARERRINT_V(1U)

#घोषणा TIEQINPARERRINT_S    19
#घोषणा TIEQINPARERRINT_V(x) ((x) << TIEQINPARERRINT_S)
#घोषणा TIEQINPARERRINT_F    TIEQINPARERRINT_V(1U)

#घोषणा TIMER0INT_S    2
#घोषणा TIMER0INT_V(x) ((x) << TIMER0INT_S)
#घोषणा TIMER0INT_F    TIMER0INT_V(1U)

#घोषणा PREFDROPINT_S    1
#घोषणा PREFDROPINT_V(x) ((x) << PREFDROPINT_S)
#घोषणा PREFDROPINT_F    PREFDROPINT_V(1U)

#घोषणा UPACCNONZERO_S    0
#घोषणा UPACCNONZERO_V(x) ((x) << UPACCNONZERO_S)
#घोषणा UPACCNONZERO_F    UPACCNONZERO_V(1U)

#घोषणा MBHOSTPARERR_S    18
#घोषणा MBHOSTPARERR_V(x) ((x) << MBHOSTPARERR_S)
#घोषणा MBHOSTPARERR_F    MBHOSTPARERR_V(1U)

#घोषणा MBUPPARERR_S    17
#घोषणा MBUPPARERR_V(x) ((x) << MBUPPARERR_S)
#घोषणा MBUPPARERR_F    MBUPPARERR_V(1U)

#घोषणा IBQTP0PARERR_S    16
#घोषणा IBQTP0PARERR_V(x) ((x) << IBQTP0PARERR_S)
#घोषणा IBQTP0PARERR_F    IBQTP0PARERR_V(1U)

#घोषणा IBQTP1PARERR_S    15
#घोषणा IBQTP1PARERR_V(x) ((x) << IBQTP1PARERR_S)
#घोषणा IBQTP1PARERR_F    IBQTP1PARERR_V(1U)

#घोषणा IBQULPPARERR_S    14
#घोषणा IBQULPPARERR_V(x) ((x) << IBQULPPARERR_S)
#घोषणा IBQULPPARERR_F    IBQULPPARERR_V(1U)

#घोषणा IBQSGELOPARERR_S    13
#घोषणा IBQSGELOPARERR_V(x) ((x) << IBQSGELOPARERR_S)
#घोषणा IBQSGELOPARERR_F    IBQSGELOPARERR_V(1U)

#घोषणा IBQSGEHIPARERR_S    12
#घोषणा IBQSGEHIPARERR_V(x) ((x) << IBQSGEHIPARERR_S)
#घोषणा IBQSGEHIPARERR_F    IBQSGEHIPARERR_V(1U)

#घोषणा IBQNCSIPARERR_S    11
#घोषणा IBQNCSIPARERR_V(x) ((x) << IBQNCSIPARERR_S)
#घोषणा IBQNCSIPARERR_F    IBQNCSIPARERR_V(1U)

#घोषणा OBQULP0PARERR_S    10
#घोषणा OBQULP0PARERR_V(x) ((x) << OBQULP0PARERR_S)
#घोषणा OBQULP0PARERR_F    OBQULP0PARERR_V(1U)

#घोषणा OBQULP1PARERR_S    9
#घोषणा OBQULP1PARERR_V(x) ((x) << OBQULP1PARERR_S)
#घोषणा OBQULP1PARERR_F    OBQULP1PARERR_V(1U)

#घोषणा OBQULP2PARERR_S    8
#घोषणा OBQULP2PARERR_V(x) ((x) << OBQULP2PARERR_S)
#घोषणा OBQULP2PARERR_F    OBQULP2PARERR_V(1U)

#घोषणा OBQULP3PARERR_S    7
#घोषणा OBQULP3PARERR_V(x) ((x) << OBQULP3PARERR_S)
#घोषणा OBQULP3PARERR_F    OBQULP3PARERR_V(1U)

#घोषणा OBQSGEPARERR_S    6
#घोषणा OBQSGEPARERR_V(x) ((x) << OBQSGEPARERR_S)
#घोषणा OBQSGEPARERR_F    OBQSGEPARERR_V(1U)

#घोषणा OBQNCSIPARERR_S    5
#घोषणा OBQNCSIPARERR_V(x) ((x) << OBQNCSIPARERR_S)
#घोषणा OBQNCSIPARERR_F    OBQNCSIPARERR_V(1U)

#घोषणा CIM_HOST_UPACC_INT_CAUSE_A 0x7b34

#घोषणा EEPROMWRINT_S    30
#घोषणा EEPROMWRINT_V(x) ((x) << EEPROMWRINT_S)
#घोषणा EEPROMWRINT_F    EEPROMWRINT_V(1U)

#घोषणा TIMEOUTMAINT_S    29
#घोषणा TIMEOUTMAINT_V(x) ((x) << TIMEOUTMAINT_S)
#घोषणा TIMEOUTMAINT_F    TIMEOUTMAINT_V(1U)

#घोषणा TIMEOUTINT_S    28
#घोषणा TIMEOUTINT_V(x) ((x) << TIMEOUTINT_S)
#घोषणा TIMEOUTINT_F    TIMEOUTINT_V(1U)

#घोषणा RSPOVRLOOKUPINT_S    27
#घोषणा RSPOVRLOOKUPINT_V(x) ((x) << RSPOVRLOOKUPINT_S)
#घोषणा RSPOVRLOOKUPINT_F    RSPOVRLOOKUPINT_V(1U)

#घोषणा REQOVRLOOKUPINT_S    26
#घोषणा REQOVRLOOKUPINT_V(x) ((x) << REQOVRLOOKUPINT_S)
#घोषणा REQOVRLOOKUPINT_F    REQOVRLOOKUPINT_V(1U)

#घोषणा BLKWRPLINT_S    25
#घोषणा BLKWRPLINT_V(x) ((x) << BLKWRPLINT_S)
#घोषणा BLKWRPLINT_F    BLKWRPLINT_V(1U)

#घोषणा BLKRDPLINT_S    24
#घोषणा BLKRDPLINT_V(x) ((x) << BLKRDPLINT_S)
#घोषणा BLKRDPLINT_F    BLKRDPLINT_V(1U)

#घोषणा SGLWRPLINT_S    23
#घोषणा SGLWRPLINT_V(x) ((x) << SGLWRPLINT_S)
#घोषणा SGLWRPLINT_F    SGLWRPLINT_V(1U)

#घोषणा SGLRDPLINT_S    22
#घोषणा SGLRDPLINT_V(x) ((x) << SGLRDPLINT_S)
#घोषणा SGLRDPLINT_F    SGLRDPLINT_V(1U)

#घोषणा BLKWRCTLINT_S    21
#घोषणा BLKWRCTLINT_V(x) ((x) << BLKWRCTLINT_S)
#घोषणा BLKWRCTLINT_F    BLKWRCTLINT_V(1U)

#घोषणा BLKRDCTLINT_S    20
#घोषणा BLKRDCTLINT_V(x) ((x) << BLKRDCTLINT_S)
#घोषणा BLKRDCTLINT_F    BLKRDCTLINT_V(1U)

#घोषणा SGLWRCTLINT_S    19
#घोषणा SGLWRCTLINT_V(x) ((x) << SGLWRCTLINT_S)
#घोषणा SGLWRCTLINT_F    SGLWRCTLINT_V(1U)

#घोषणा SGLRDCTLINT_S    18
#घोषणा SGLRDCTLINT_V(x) ((x) << SGLRDCTLINT_S)
#घोषणा SGLRDCTLINT_F    SGLRDCTLINT_V(1U)

#घोषणा BLKWREEPROMINT_S    17
#घोषणा BLKWREEPROMINT_V(x) ((x) << BLKWREEPROMINT_S)
#घोषणा BLKWREEPROMINT_F    BLKWREEPROMINT_V(1U)

#घोषणा BLKRDEEPROMINT_S    16
#घोषणा BLKRDEEPROMINT_V(x) ((x) << BLKRDEEPROMINT_S)
#घोषणा BLKRDEEPROMINT_F    BLKRDEEPROMINT_V(1U)

#घोषणा SGLWREEPROMINT_S    15
#घोषणा SGLWREEPROMINT_V(x) ((x) << SGLWREEPROMINT_S)
#घोषणा SGLWREEPROMINT_F    SGLWREEPROMINT_V(1U)

#घोषणा SGLRDEEPROMINT_S    14
#घोषणा SGLRDEEPROMINT_V(x) ((x) << SGLRDEEPROMINT_S)
#घोषणा SGLRDEEPROMINT_F    SGLRDEEPROMINT_V(1U)

#घोषणा BLKWRFLASHINT_S    13
#घोषणा BLKWRFLASHINT_V(x) ((x) << BLKWRFLASHINT_S)
#घोषणा BLKWRFLASHINT_F    BLKWRFLASHINT_V(1U)

#घोषणा BLKRDFLASHINT_S    12
#घोषणा BLKRDFLASHINT_V(x) ((x) << BLKRDFLASHINT_S)
#घोषणा BLKRDFLASHINT_F    BLKRDFLASHINT_V(1U)

#घोषणा SGLWRFLASHINT_S    11
#घोषणा SGLWRFLASHINT_V(x) ((x) << SGLWRFLASHINT_S)
#घोषणा SGLWRFLASHINT_F    SGLWRFLASHINT_V(1U)

#घोषणा SGLRDFLASHINT_S    10
#घोषणा SGLRDFLASHINT_V(x) ((x) << SGLRDFLASHINT_S)
#घोषणा SGLRDFLASHINT_F    SGLRDFLASHINT_V(1U)

#घोषणा BLKWRBOOTINT_S    9
#घोषणा BLKWRBOOTINT_V(x) ((x) << BLKWRBOOTINT_S)
#घोषणा BLKWRBOOTINT_F    BLKWRBOOTINT_V(1U)

#घोषणा BLKRDBOOTINT_S    8
#घोषणा BLKRDBOOTINT_V(x) ((x) << BLKRDBOOTINT_S)
#घोषणा BLKRDBOOTINT_F    BLKRDBOOTINT_V(1U)

#घोषणा SGLWRBOOTINT_S    7
#घोषणा SGLWRBOOTINT_V(x) ((x) << SGLWRBOOTINT_S)
#घोषणा SGLWRBOOTINT_F    SGLWRBOOTINT_V(1U)

#घोषणा SGLRDBOOTINT_S    6
#घोषणा SGLRDBOOTINT_V(x) ((x) << SGLRDBOOTINT_S)
#घोषणा SGLRDBOOTINT_F    SGLRDBOOTINT_V(1U)

#घोषणा ILLWRBEINT_S    5
#घोषणा ILLWRBEINT_V(x) ((x) << ILLWRBEINT_S)
#घोषणा ILLWRBEINT_F    ILLWRBEINT_V(1U)

#घोषणा ILLRDBEINT_S    4
#घोषणा ILLRDBEINT_V(x) ((x) << ILLRDBEINT_S)
#घोषणा ILLRDBEINT_F    ILLRDBEINT_V(1U)

#घोषणा ILLRDINT_S    3
#घोषणा ILLRDINT_V(x) ((x) << ILLRDINT_S)
#घोषणा ILLRDINT_F    ILLRDINT_V(1U)

#घोषणा ILLWRINT_S    2
#घोषणा ILLWRINT_V(x) ((x) << ILLWRINT_S)
#घोषणा ILLWRINT_F    ILLWRINT_V(1U)

#घोषणा ILLTRANSINT_S    1
#घोषणा ILLTRANSINT_V(x) ((x) << ILLTRANSINT_S)
#घोषणा ILLTRANSINT_F    ILLTRANSINT_V(1U)

#घोषणा RSVDSPACEINT_S    0
#घोषणा RSVDSPACEINT_V(x) ((x) << RSVDSPACEINT_S)
#घोषणा RSVDSPACEINT_F    RSVDSPACEINT_V(1U)

/* रेजिस्टरs क्रम module TP */
#घोषणा DBGLAWHLF_S    23
#घोषणा DBGLAWHLF_V(x) ((x) << DBGLAWHLF_S)
#घोषणा DBGLAWHLF_F    DBGLAWHLF_V(1U)

#घोषणा DBGLAWPTR_S    16
#घोषणा DBGLAWPTR_M    0x7fU
#घोषणा DBGLAWPTR_G(x) (((x) >> DBGLAWPTR_S) & DBGLAWPTR_M)

#घोषणा DBGLAENABLE_S    12
#घोषणा DBGLAENABLE_V(x) ((x) << DBGLAENABLE_S)
#घोषणा DBGLAENABLE_F    DBGLAENABLE_V(1U)

#घोषणा DBGLARPTR_S    0
#घोषणा DBGLARPTR_M    0x7fU
#घोषणा DBGLARPTR_V(x) ((x) << DBGLARPTR_S)

#घोषणा CRXPKTENC_S    3
#घोषणा CRXPKTENC_V(x) ((x) << CRXPKTENC_S)
#घोषणा CRXPKTENC_F    CRXPKTENC_V(1U)

#घोषणा TP_DBG_LA_DATAL_A	0x7ed8
#घोषणा TP_DBG_LA_CONFIG_A	0x7ed4
#घोषणा TP_OUT_CONFIG_A		0x7d04
#घोषणा TP_GLOBAL_CONFIG_A	0x7d08

#घोषणा ACTIVEFILTERCOUNTS_S    22
#घोषणा ACTIVEFILTERCOUNTS_V(x) ((x) << ACTIVEFILTERCOUNTS_S)
#घोषणा ACTIVEFILTERCOUNTS_F    ACTIVEFILTERCOUNTS_V(1U)

#घोषणा TP_CMM_TCB_BASE_A 0x7d10
#घोषणा TP_CMM_MM_BASE_A 0x7d14
#घोषणा TP_CMM_TIMER_BASE_A 0x7d18
#घोषणा TP_PMM_TX_BASE_A 0x7d20
#घोषणा TP_PMM_RX_BASE_A 0x7d28
#घोषणा TP_PMM_RX_PAGE_SIZE_A 0x7d2c
#घोषणा TP_PMM_RX_MAX_PAGE_A 0x7d30
#घोषणा TP_PMM_TX_PAGE_SIZE_A 0x7d34
#घोषणा TP_PMM_TX_MAX_PAGE_A 0x7d38
#घोषणा TP_CMM_MM_MAX_PSTRUCT_A 0x7e6c

#घोषणा PMRXNUMCHN_S    31
#घोषणा PMRXNUMCHN_V(x) ((x) << PMRXNUMCHN_S)
#घोषणा PMRXNUMCHN_F    PMRXNUMCHN_V(1U)

#घोषणा PMTXNUMCHN_S    30
#घोषणा PMTXNUMCHN_M    0x3U
#घोषणा PMTXNUMCHN_G(x) (((x) >> PMTXNUMCHN_S) & PMTXNUMCHN_M)

#घोषणा PMTXMAXPAGE_S    0
#घोषणा PMTXMAXPAGE_M    0x1fffffU
#घोषणा PMTXMAXPAGE_G(x) (((x) >> PMTXMAXPAGE_S) & PMTXMAXPAGE_M)

#घोषणा PMRXMAXPAGE_S    0
#घोषणा PMRXMAXPAGE_M    0x1fffffU
#घोषणा PMRXMAXPAGE_G(x) (((x) >> PMRXMAXPAGE_S) & PMRXMAXPAGE_M)

#घोषणा DBGLAMODE_S	14
#घोषणा DBGLAMODE_M	0x3U
#घोषणा DBGLAMODE_G(x)	(((x) >> DBGLAMODE_S) & DBGLAMODE_M)

#घोषणा FIVETUPLELOOKUP_S    17
#घोषणा FIVETUPLELOOKUP_M    0x3U
#घोषणा FIVETUPLELOOKUP_V(x) ((x) << FIVETUPLELOOKUP_S)
#घोषणा FIVETUPLELOOKUP_G(x) (((x) >> FIVETUPLELOOKUP_S) & FIVETUPLELOOKUP_M)

#घोषणा TP_PARA_REG2_A 0x7d68

#घोषणा MAXRXDATA_S    16
#घोषणा MAXRXDATA_M    0xffffU
#घोषणा MAXRXDATA_G(x) (((x) >> MAXRXDATA_S) & MAXRXDATA_M)

#घोषणा TP_TIMER_RESOLUTION_A 0x7d90

#घोषणा TIMERRESOLUTION_S    16
#घोषणा TIMERRESOLUTION_M    0xffU
#घोषणा TIMERRESOLUTION_G(x) (((x) >> TIMERRESOLUTION_S) & TIMERRESOLUTION_M)

#घोषणा TIMESTAMPRESOLUTION_S    8
#घोषणा TIMESTAMPRESOLUTION_M    0xffU
#घोषणा TIMESTAMPRESOLUTION_G(x) \
	(((x) >> TIMESTAMPRESOLUTION_S) & TIMESTAMPRESOLUTION_M)

#घोषणा DELAYEDACKRESOLUTION_S    0
#घोषणा DELAYEDACKRESOLUTION_M    0xffU
#घोषणा DELAYEDACKRESOLUTION_G(x) \
	(((x) >> DELAYEDACKRESOLUTION_S) & DELAYEDACKRESOLUTION_M)

#घोषणा TP_SHIFT_CNT_A 0x7dc0
#घोषणा TP_RXT_MIN_A 0x7d98
#घोषणा TP_RXT_MAX_A 0x7d9c
#घोषणा TP_PERS_MIN_A 0x7da0
#घोषणा TP_PERS_MAX_A 0x7da4
#घोषणा TP_KEEP_IDLE_A 0x7da8
#घोषणा TP_KEEP_INTVL_A 0x7dac
#घोषणा TP_INIT_SRTT_A 0x7db0
#घोषणा TP_DACK_TIMER_A 0x7db4
#घोषणा TP_FINWAIT2_TIMER_A 0x7db8

#घोषणा INITSRTT_S    0
#घोषणा INITSRTT_M    0xffffU
#घोषणा INITSRTT_G(x) (((x) >> INITSRTT_S) & INITSRTT_M)

#घोषणा PERSMAX_S    0
#घोषणा PERSMAX_M    0x3fffffffU
#घोषणा PERSMAX_V(x) ((x) << PERSMAX_S)
#घोषणा PERSMAX_G(x) (((x) >> PERSMAX_S) & PERSMAX_M)

#घोषणा SYNSHIFTMAX_S    24
#घोषणा SYNSHIFTMAX_M    0xffU
#घोषणा SYNSHIFTMAX_V(x) ((x) << SYNSHIFTMAX_S)
#घोषणा SYNSHIFTMAX_G(x) (((x) >> SYNSHIFTMAX_S) & SYNSHIFTMAX_M)

#घोषणा RXTSHIFTMAXR1_S    20
#घोषणा RXTSHIFTMAXR1_M    0xfU
#घोषणा RXTSHIFTMAXR1_V(x) ((x) << RXTSHIFTMAXR1_S)
#घोषणा RXTSHIFTMAXR1_G(x) (((x) >> RXTSHIFTMAXR1_S) & RXTSHIFTMAXR1_M)

#घोषणा RXTSHIFTMAXR2_S    16
#घोषणा RXTSHIFTMAXR2_M    0xfU
#घोषणा RXTSHIFTMAXR2_V(x) ((x) << RXTSHIFTMAXR2_S)
#घोषणा RXTSHIFTMAXR2_G(x) (((x) >> RXTSHIFTMAXR2_S) & RXTSHIFTMAXR2_M)

#घोषणा PERSHIFTBACKOFFMAX_S    12
#घोषणा PERSHIFTBACKOFFMAX_M    0xfU
#घोषणा PERSHIFTBACKOFFMAX_V(x) ((x) << PERSHIFTBACKOFFMAX_S)
#घोषणा PERSHIFTBACKOFFMAX_G(x) \
	(((x) >> PERSHIFTBACKOFFMAX_S) & PERSHIFTBACKOFFMAX_M)

#घोषणा PERSHIFTMAX_S    8
#घोषणा PERSHIFTMAX_M    0xfU
#घोषणा PERSHIFTMAX_V(x) ((x) << PERSHIFTMAX_S)
#घोषणा PERSHIFTMAX_G(x) (((x) >> PERSHIFTMAX_S) & PERSHIFTMAX_M)

#घोषणा KEEPALIVEMAXR1_S    4
#घोषणा KEEPALIVEMAXR1_M    0xfU
#घोषणा KEEPALIVEMAXR1_V(x) ((x) << KEEPALIVEMAXR1_S)
#घोषणा KEEPALIVEMAXR1_G(x) (((x) >> KEEPALIVEMAXR1_S) & KEEPALIVEMAXR1_M)

#घोषणा KEEPALIVEMAXR2_S    0
#घोषणा KEEPALIVEMAXR2_M    0xfU
#घोषणा KEEPALIVEMAXR2_V(x) ((x) << KEEPALIVEMAXR2_S)
#घोषणा KEEPALIVEMAXR2_G(x) (((x) >> KEEPALIVEMAXR2_S) & KEEPALIVEMAXR2_M)

#घोषणा ROWINDEX_S    16
#घोषणा ROWINDEX_V(x) ((x) << ROWINDEX_S)

#घोषणा TP_CCTRL_TABLE_A	0x7ddc
#घोषणा TP_PACE_TABLE_A 0x7dd8
#घोषणा TP_MTU_TABLE_A		0x7de4

#घोषणा MTUINDEX_S    24
#घोषणा MTUINDEX_V(x) ((x) << MTUINDEX_S)

#घोषणा MTUWIDTH_S    16
#घोषणा MTUWIDTH_M    0xfU
#घोषणा MTUWIDTH_V(x) ((x) << MTUWIDTH_S)
#घोषणा MTUWIDTH_G(x) (((x) >> MTUWIDTH_S) & MTUWIDTH_M)

#घोषणा MTUVALUE_S    0
#घोषणा MTUVALUE_M    0x3fffU
#घोषणा MTUVALUE_V(x) ((x) << MTUVALUE_S)
#घोषणा MTUVALUE_G(x) (((x) >> MTUVALUE_S) & MTUVALUE_M)

#घोषणा TP_RSS_LKP_TABLE_A	0x7dec
#घोषणा TP_CMM_MM_RX_FLST_BASE_A 0x7e60
#घोषणा TP_CMM_MM_TX_FLST_BASE_A 0x7e64
#घोषणा TP_CMM_MM_PS_FLST_BASE_A 0x7e68

#घोषणा LKPTBLROWVLD_S    31
#घोषणा LKPTBLROWVLD_V(x) ((x) << LKPTBLROWVLD_S)
#घोषणा LKPTBLROWVLD_F    LKPTBLROWVLD_V(1U)

#घोषणा LKPTBLQUEUE1_S    10
#घोषणा LKPTBLQUEUE1_M    0x3ffU
#घोषणा LKPTBLQUEUE1_G(x) (((x) >> LKPTBLQUEUE1_S) & LKPTBLQUEUE1_M)

#घोषणा LKPTBLQUEUE0_S    0
#घोषणा LKPTBLQUEUE0_M    0x3ffU
#घोषणा LKPTBLQUEUE0_G(x) (((x) >> LKPTBLQUEUE0_S) & LKPTBLQUEUE0_M)

#घोषणा TP_TM_PIO_ADDR_A 0x7e18
#घोषणा TP_TM_PIO_DATA_A 0x7e1c
#घोषणा TP_MOD_CONFIG_A 0x7e24

#घोषणा TIMERMODE_S    8
#घोषणा TIMERMODE_M    0xffU
#घोषणा TIMERMODE_G(x) (((x) >> TIMERMODE_S) & TIMERMODE_M)

#घोषणा TP_TX_MOD_Q1_Q0_TIMER_SEPARATOR_A 0x3
#घोषणा TP_TX_MOD_Q1_Q0_RATE_LIMIT_A 0x8

#घोषणा TP_PIO_ADDR_A	0x7e40
#घोषणा TP_PIO_DATA_A	0x7e44
#घोषणा TP_MIB_INDEX_A	0x7e50
#घोषणा TP_MIB_DATA_A	0x7e54
#घोषणा TP_INT_CAUSE_A	0x7e74

#घोषणा TP_FLM_FREE_PS_CNT_A 0x7e80
#घोषणा TP_FLM_FREE_RX_CNT_A 0x7e84

#घोषणा FREEPSTRUCTCOUNT_S    0
#घोषणा FREEPSTRUCTCOUNT_M    0x1fffffU
#घोषणा FREEPSTRUCTCOUNT_G(x) (((x) >> FREEPSTRUCTCOUNT_S) & FREEPSTRUCTCOUNT_M)

#घोषणा FREERXPAGECOUNT_S    0
#घोषणा FREERXPAGECOUNT_M    0x1fffffU
#घोषणा FREERXPAGECOUNT_V(x) ((x) << FREERXPAGECOUNT_S)
#घोषणा FREERXPAGECOUNT_G(x) (((x) >> FREERXPAGECOUNT_S) & FREERXPAGECOUNT_M)

#घोषणा TP_FLM_FREE_TX_CNT_A 0x7e88

#घोषणा FREETXPAGECOUNT_S    0
#घोषणा FREETXPAGECOUNT_M    0x1fffffU
#घोषणा FREETXPAGECOUNT_V(x) ((x) << FREETXPAGECOUNT_S)
#घोषणा FREETXPAGECOUNT_G(x) (((x) >> FREETXPAGECOUNT_S) & FREETXPAGECOUNT_M)

#घोषणा FLMTXFLSTEMPTY_S    30
#घोषणा FLMTXFLSTEMPTY_V(x) ((x) << FLMTXFLSTEMPTY_S)
#घोषणा FLMTXFLSTEMPTY_F    FLMTXFLSTEMPTY_V(1U)

#घोषणा TP_TX_ORATE_A 0x7ebc

#घोषणा OFDRATE3_S    24
#घोषणा OFDRATE3_M    0xffU
#घोषणा OFDRATE3_G(x) (((x) >> OFDRATE3_S) & OFDRATE3_M)

#घोषणा OFDRATE2_S    16
#घोषणा OFDRATE2_M    0xffU
#घोषणा OFDRATE2_G(x) (((x) >> OFDRATE2_S) & OFDRATE2_M)

#घोषणा OFDRATE1_S    8
#घोषणा OFDRATE1_M    0xffU
#घोषणा OFDRATE1_G(x) (((x) >> OFDRATE1_S) & OFDRATE1_M)

#घोषणा OFDRATE0_S    0
#घोषणा OFDRATE0_M    0xffU
#घोषणा OFDRATE0_G(x) (((x) >> OFDRATE0_S) & OFDRATE0_M)

#घोषणा TP_TX_TRATE_A 0x7ed0

#घोषणा TNLRATE3_S    24
#घोषणा TNLRATE3_M    0xffU
#घोषणा TNLRATE3_G(x) (((x) >> TNLRATE3_S) & TNLRATE3_M)

#घोषणा TNLRATE2_S    16
#घोषणा TNLRATE2_M    0xffU
#घोषणा TNLRATE2_G(x) (((x) >> TNLRATE2_S) & TNLRATE2_M)

#घोषणा TNLRATE1_S    8
#घोषणा TNLRATE1_M    0xffU
#घोषणा TNLRATE1_G(x) (((x) >> TNLRATE1_S) & TNLRATE1_M)

#घोषणा TNLRATE0_S    0
#घोषणा TNLRATE0_M    0xffU
#घोषणा TNLRATE0_G(x) (((x) >> TNLRATE0_S) & TNLRATE0_M)

#घोषणा TP_VLAN_PRI_MAP_A 0x140

#घोषणा FRAGMENTATION_S    9
#घोषणा FRAGMENTATION_V(x) ((x) << FRAGMENTATION_S)
#घोषणा FRAGMENTATION_F    FRAGMENTATION_V(1U)

#घोषणा MPSHITTYPE_S    8
#घोषणा MPSHITTYPE_V(x) ((x) << MPSHITTYPE_S)
#घोषणा MPSHITTYPE_F    MPSHITTYPE_V(1U)

#घोषणा MACMATCH_S    7
#घोषणा MACMATCH_V(x) ((x) << MACMATCH_S)
#घोषणा MACMATCH_F    MACMATCH_V(1U)

#घोषणा ETHERTYPE_S    6
#घोषणा ETHERTYPE_V(x) ((x) << ETHERTYPE_S)
#घोषणा ETHERTYPE_F    ETHERTYPE_V(1U)

#घोषणा PROTOCOL_S    5
#घोषणा PROTOCOL_V(x) ((x) << PROTOCOL_S)
#घोषणा PROTOCOL_F    PROTOCOL_V(1U)

#घोषणा TOS_S    4
#घोषणा TOS_V(x) ((x) << TOS_S)
#घोषणा TOS_F    TOS_V(1U)

#घोषणा VLAN_S    3
#घोषणा VLAN_V(x) ((x) << VLAN_S)
#घोषणा VLAN_F    VLAN_V(1U)

#घोषणा VNIC_ID_S    2
#घोषणा VNIC_ID_V(x) ((x) << VNIC_ID_S)
#घोषणा VNIC_ID_F    VNIC_ID_V(1U)

#घोषणा PORT_S    1
#घोषणा PORT_V(x) ((x) << PORT_S)
#घोषणा PORT_F    PORT_V(1U)

#घोषणा FCOE_S    0
#घोषणा FCOE_V(x) ((x) << FCOE_S)
#घोषणा FCOE_F    FCOE_V(1U)

#घोषणा FILTERMODE_S    15
#घोषणा FILTERMODE_V(x) ((x) << FILTERMODE_S)
#घोषणा FILTERMODE_F    FILTERMODE_V(1U)

#घोषणा FCOEMASK_S    14
#घोषणा FCOEMASK_V(x) ((x) << FCOEMASK_S)
#घोषणा FCOEMASK_F    FCOEMASK_V(1U)

#घोषणा TP_INGRESS_CONFIG_A	0x141

#घोषणा VNIC_S    11
#घोषणा VNIC_V(x) ((x) << VNIC_S)
#घोषणा VNIC_F    VNIC_V(1U)

#घोषणा USE_ENC_IDX_S		13
#घोषणा USE_ENC_IDX_V(x)	((x) << USE_ENC_IDX_S)
#घोषणा USE_ENC_IDX_F		USE_ENC_IDX_V(1U)

#घोषणा CSUM_HAS_PSEUDO_HDR_S    10
#घोषणा CSUM_HAS_PSEUDO_HDR_V(x) ((x) << CSUM_HAS_PSEUDO_HDR_S)
#घोषणा CSUM_HAS_PSEUDO_HDR_F    CSUM_HAS_PSEUDO_HDR_V(1U)

#घोषणा TP_MIB_MAC_IN_ERR_0_A	0x0
#घोषणा TP_MIB_HDR_IN_ERR_0_A	0x4
#घोषणा TP_MIB_TCP_IN_ERR_0_A	0x8
#घोषणा TP_MIB_TCP_OUT_RST_A	0xc
#घोषणा TP_MIB_TCP_IN_SEG_HI_A	0x10
#घोषणा TP_MIB_TCP_IN_SEG_LO_A	0x11
#घोषणा TP_MIB_TCP_OUT_SEG_HI_A	0x12
#घोषणा TP_MIB_TCP_OUT_SEG_LO_A 0x13
#घोषणा TP_MIB_TCP_RXT_SEG_HI_A	0x14
#घोषणा TP_MIB_TCP_RXT_SEG_LO_A	0x15
#घोषणा TP_MIB_TNL_CNG_DROP_0_A 0x18
#घोषणा TP_MIB_OFD_CHN_DROP_0_A 0x1c
#घोषणा TP_MIB_TCP_V6IN_ERR_0_A 0x28
#घोषणा TP_MIB_TCP_V6OUT_RST_A	0x2c
#घोषणा TP_MIB_OFD_ARP_DROP_A	0x36
#घोषणा TP_MIB_CPL_IN_REQ_0_A	0x38
#घोषणा TP_MIB_CPL_OUT_RSP_0_A	0x3c
#घोषणा TP_MIB_TNL_DROP_0_A	0x44
#घोषणा TP_MIB_FCOE_DDP_0_A	0x48
#घोषणा TP_MIB_FCOE_DROP_0_A	0x4c
#घोषणा TP_MIB_FCOE_BYTE_0_HI_A	0x50
#घोषणा TP_MIB_OFD_VLN_DROP_0_A	0x58
#घोषणा TP_MIB_USM_PKTS_A	0x5c
#घोषणा TP_MIB_RQE_DFR_PKT_A	0x64

#घोषणा ULP_TX_INT_CAUSE_A	0x8dcc
#घोषणा ULP_TX_TPT_LLIMIT_A	0x8dd4
#घोषणा ULP_TX_TPT_ULIMIT_A	0x8dd8
#घोषणा ULP_TX_PBL_LLIMIT_A	0x8ddc
#घोषणा ULP_TX_PBL_ULIMIT_A	0x8de0
#घोषणा ULP_TX_ERR_TABLE_BASE_A 0x8e04

#घोषणा PBL_BOUND_ERR_CH3_S    31
#घोषणा PBL_BOUND_ERR_CH3_V(x) ((x) << PBL_BOUND_ERR_CH3_S)
#घोषणा PBL_BOUND_ERR_CH3_F    PBL_BOUND_ERR_CH3_V(1U)

#घोषणा PBL_BOUND_ERR_CH2_S    30
#घोषणा PBL_BOUND_ERR_CH2_V(x) ((x) << PBL_BOUND_ERR_CH2_S)
#घोषणा PBL_BOUND_ERR_CH2_F    PBL_BOUND_ERR_CH2_V(1U)

#घोषणा PBL_BOUND_ERR_CH1_S    29
#घोषणा PBL_BOUND_ERR_CH1_V(x) ((x) << PBL_BOUND_ERR_CH1_S)
#घोषणा PBL_BOUND_ERR_CH1_F    PBL_BOUND_ERR_CH1_V(1U)

#घोषणा PBL_BOUND_ERR_CH0_S    28
#घोषणा PBL_BOUND_ERR_CH0_V(x) ((x) << PBL_BOUND_ERR_CH0_S)
#घोषणा PBL_BOUND_ERR_CH0_F    PBL_BOUND_ERR_CH0_V(1U)

#घोषणा PM_RX_INT_CAUSE_A	0x8fdc
#घोषणा PM_RX_STAT_CONFIG_A 0x8fc8
#घोषणा PM_RX_STAT_COUNT_A 0x8fcc
#घोषणा PM_RX_STAT_LSB_A 0x8fd0
#घोषणा PM_RX_DBG_CTRL_A 0x8fd0
#घोषणा PM_RX_DBG_DATA_A 0x8fd4
#घोषणा PM_RX_DBG_STAT_MSB_A 0x10013

#घोषणा PMRX_FRAMING_ERROR_F	0x003ffff0U

#घोषणा ZERO_E_CMD_ERROR_S    22
#घोषणा ZERO_E_CMD_ERROR_V(x) ((x) << ZERO_E_CMD_ERROR_S)
#घोषणा ZERO_E_CMD_ERROR_F    ZERO_E_CMD_ERROR_V(1U)

#घोषणा OCSPI_PAR_ERROR_S    3
#घोषणा OCSPI_PAR_ERROR_V(x) ((x) << OCSPI_PAR_ERROR_S)
#घोषणा OCSPI_PAR_ERROR_F    OCSPI_PAR_ERROR_V(1U)

#घोषणा DB_OPTIONS_PAR_ERROR_S    2
#घोषणा DB_OPTIONS_PAR_ERROR_V(x) ((x) << DB_OPTIONS_PAR_ERROR_S)
#घोषणा DB_OPTIONS_PAR_ERROR_F    DB_OPTIONS_PAR_ERROR_V(1U)

#घोषणा IESPI_PAR_ERROR_S    1
#घोषणा IESPI_PAR_ERROR_V(x) ((x) << IESPI_PAR_ERROR_S)
#घोषणा IESPI_PAR_ERROR_F    IESPI_PAR_ERROR_V(1U)

#घोषणा ULP_TX_LA_RDPTR_0_A 0x8ec0
#घोषणा ULP_TX_LA_RDDATA_0_A 0x8ec4
#घोषणा ULP_TX_LA_WRPTR_0_A 0x8ec8
#घोषणा ULP_TX_ASIC_DEBUG_CTRL_A 0x8f70

#घोषणा ULP_TX_ASIC_DEBUG_0_A 0x8f74
#घोषणा ULP_TX_ASIC_DEBUG_1_A 0x8f78
#घोषणा ULP_TX_ASIC_DEBUG_2_A 0x8f7c
#घोषणा ULP_TX_ASIC_DEBUG_3_A 0x8f80
#घोषणा ULP_TX_ASIC_DEBUG_4_A 0x8f84

/* रेजिस्टरs क्रम module PM_RX */
#घोषणा PM_RX_BASE_ADDR 0x8fc0

#घोषणा PMRX_E_PCMD_PAR_ERROR_S    0
#घोषणा PMRX_E_PCMD_PAR_ERROR_V(x) ((x) << PMRX_E_PCMD_PAR_ERROR_S)
#घोषणा PMRX_E_PCMD_PAR_ERROR_F    PMRX_E_PCMD_PAR_ERROR_V(1U)

#घोषणा PM_TX_INT_CAUSE_A	0x8ffc
#घोषणा PM_TX_STAT_CONFIG_A 0x8fe8
#घोषणा PM_TX_STAT_COUNT_A 0x8fec
#घोषणा PM_TX_STAT_LSB_A 0x8ff0
#घोषणा PM_TX_DBG_CTRL_A 0x8ff0
#घोषणा PM_TX_DBG_DATA_A 0x8ff4
#घोषणा PM_TX_DBG_STAT_MSB_A 0x1001a

#घोषणा PCMD_LEN_OVFL0_S    31
#घोषणा PCMD_LEN_OVFL0_V(x) ((x) << PCMD_LEN_OVFL0_S)
#घोषणा PCMD_LEN_OVFL0_F    PCMD_LEN_OVFL0_V(1U)

#घोषणा PCMD_LEN_OVFL1_S    30
#घोषणा PCMD_LEN_OVFL1_V(x) ((x) << PCMD_LEN_OVFL1_S)
#घोषणा PCMD_LEN_OVFL1_F    PCMD_LEN_OVFL1_V(1U)

#घोषणा PCMD_LEN_OVFL2_S    29
#घोषणा PCMD_LEN_OVFL2_V(x) ((x) << PCMD_LEN_OVFL2_S)
#घोषणा PCMD_LEN_OVFL2_F    PCMD_LEN_OVFL2_V(1U)

#घोषणा ZERO_C_CMD_ERROR_S    28
#घोषणा ZERO_C_CMD_ERROR_V(x) ((x) << ZERO_C_CMD_ERROR_S)
#घोषणा ZERO_C_CMD_ERROR_F    ZERO_C_CMD_ERROR_V(1U)

#घोषणा  PMTX_FRAMING_ERROR_F 0x0ffffff0U

#घोषणा OESPI_PAR_ERROR_S    3
#घोषणा OESPI_PAR_ERROR_V(x) ((x) << OESPI_PAR_ERROR_S)
#घोषणा OESPI_PAR_ERROR_F    OESPI_PAR_ERROR_V(1U)

#घोषणा ICSPI_PAR_ERROR_S    1
#घोषणा ICSPI_PAR_ERROR_V(x) ((x) << ICSPI_PAR_ERROR_S)
#घोषणा ICSPI_PAR_ERROR_F    ICSPI_PAR_ERROR_V(1U)

#घोषणा PMTX_C_PCMD_PAR_ERROR_S    0
#घोषणा PMTX_C_PCMD_PAR_ERROR_V(x) ((x) << PMTX_C_PCMD_PAR_ERROR_S)
#घोषणा PMTX_C_PCMD_PAR_ERROR_F    PMTX_C_PCMD_PAR_ERROR_V(1U)

#घोषणा MPS_PORT_STAT_TX_PORT_BYTES_L 0x400
#घोषणा MPS_PORT_STAT_TX_PORT_BYTES_H 0x404
#घोषणा MPS_PORT_STAT_TX_PORT_FRAMES_L 0x408
#घोषणा MPS_PORT_STAT_TX_PORT_FRAMES_H 0x40c
#घोषणा MPS_PORT_STAT_TX_PORT_BCAST_L 0x410
#घोषणा MPS_PORT_STAT_TX_PORT_BCAST_H 0x414
#घोषणा MPS_PORT_STAT_TX_PORT_MCAST_L 0x418
#घोषणा MPS_PORT_STAT_TX_PORT_MCAST_H 0x41c
#घोषणा MPS_PORT_STAT_TX_PORT_UCAST_L 0x420
#घोषणा MPS_PORT_STAT_TX_PORT_UCAST_H 0x424
#घोषणा MPS_PORT_STAT_TX_PORT_ERROR_L 0x428
#घोषणा MPS_PORT_STAT_TX_PORT_ERROR_H 0x42c
#घोषणा MPS_PORT_STAT_TX_PORT_64B_L 0x430
#घोषणा MPS_PORT_STAT_TX_PORT_64B_H 0x434
#घोषणा MPS_PORT_STAT_TX_PORT_65B_127B_L 0x438
#घोषणा MPS_PORT_STAT_TX_PORT_65B_127B_H 0x43c
#घोषणा MPS_PORT_STAT_TX_PORT_128B_255B_L 0x440
#घोषणा MPS_PORT_STAT_TX_PORT_128B_255B_H 0x444
#घोषणा MPS_PORT_STAT_TX_PORT_256B_511B_L 0x448
#घोषणा MPS_PORT_STAT_TX_PORT_256B_511B_H 0x44c
#घोषणा MPS_PORT_STAT_TX_PORT_512B_1023B_L 0x450
#घोषणा MPS_PORT_STAT_TX_PORT_512B_1023B_H 0x454
#घोषणा MPS_PORT_STAT_TX_PORT_1024B_1518B_L 0x458
#घोषणा MPS_PORT_STAT_TX_PORT_1024B_1518B_H 0x45c
#घोषणा MPS_PORT_STAT_TX_PORT_1519B_MAX_L 0x460
#घोषणा MPS_PORT_STAT_TX_PORT_1519B_MAX_H 0x464
#घोषणा MPS_PORT_STAT_TX_PORT_DROP_L 0x468
#घोषणा MPS_PORT_STAT_TX_PORT_DROP_H 0x46c
#घोषणा MPS_PORT_STAT_TX_PORT_PAUSE_L 0x470
#घोषणा MPS_PORT_STAT_TX_PORT_PAUSE_H 0x474
#घोषणा MPS_PORT_STAT_TX_PORT_PPP0_L 0x478
#घोषणा MPS_PORT_STAT_TX_PORT_PPP0_H 0x47c
#घोषणा MPS_PORT_STAT_TX_PORT_PPP1_L 0x480
#घोषणा MPS_PORT_STAT_TX_PORT_PPP1_H 0x484
#घोषणा MPS_PORT_STAT_TX_PORT_PPP2_L 0x488
#घोषणा MPS_PORT_STAT_TX_PORT_PPP2_H 0x48c
#घोषणा MPS_PORT_STAT_TX_PORT_PPP3_L 0x490
#घोषणा MPS_PORT_STAT_TX_PORT_PPP3_H 0x494
#घोषणा MPS_PORT_STAT_TX_PORT_PPP4_L 0x498
#घोषणा MPS_PORT_STAT_TX_PORT_PPP4_H 0x49c
#घोषणा MPS_PORT_STAT_TX_PORT_PPP5_L 0x4a0
#घोषणा MPS_PORT_STAT_TX_PORT_PPP5_H 0x4a4
#घोषणा MPS_PORT_STAT_TX_PORT_PPP6_L 0x4a8
#घोषणा MPS_PORT_STAT_TX_PORT_PPP6_H 0x4ac
#घोषणा MPS_PORT_STAT_TX_PORT_PPP7_L 0x4b0
#घोषणा MPS_PORT_STAT_TX_PORT_PPP7_H 0x4b4
#घोषणा MPS_PORT_STAT_LB_PORT_BYTES_L 0x4c0
#घोषणा MPS_PORT_STAT_LB_PORT_BYTES_H 0x4c4
#घोषणा MPS_PORT_STAT_LB_PORT_FRAMES_L 0x4c8
#घोषणा MPS_PORT_STAT_LB_PORT_FRAMES_H 0x4cc
#घोषणा MPS_PORT_STAT_LB_PORT_BCAST_L 0x4d0
#घोषणा MPS_PORT_STAT_LB_PORT_BCAST_H 0x4d4
#घोषणा MPS_PORT_STAT_LB_PORT_MCAST_L 0x4d8
#घोषणा MPS_PORT_STAT_LB_PORT_MCAST_H 0x4dc
#घोषणा MPS_PORT_STAT_LB_PORT_UCAST_L 0x4e0
#घोषणा MPS_PORT_STAT_LB_PORT_UCAST_H 0x4e4
#घोषणा MPS_PORT_STAT_LB_PORT_ERROR_L 0x4e8
#घोषणा MPS_PORT_STAT_LB_PORT_ERROR_H 0x4ec
#घोषणा MPS_PORT_STAT_LB_PORT_64B_L 0x4f0
#घोषणा MPS_PORT_STAT_LB_PORT_64B_H 0x4f4
#घोषणा MPS_PORT_STAT_LB_PORT_65B_127B_L 0x4f8
#घोषणा MPS_PORT_STAT_LB_PORT_65B_127B_H 0x4fc
#घोषणा MPS_PORT_STAT_LB_PORT_128B_255B_L 0x500
#घोषणा MPS_PORT_STAT_LB_PORT_128B_255B_H 0x504
#घोषणा MPS_PORT_STAT_LB_PORT_256B_511B_L 0x508
#घोषणा MPS_PORT_STAT_LB_PORT_256B_511B_H 0x50c
#घोषणा MPS_PORT_STAT_LB_PORT_512B_1023B_L 0x510
#घोषणा MPS_PORT_STAT_LB_PORT_512B_1023B_H 0x514
#घोषणा MPS_PORT_STAT_LB_PORT_1024B_1518B_L 0x518
#घोषणा MPS_PORT_STAT_LB_PORT_1024B_1518B_H 0x51c
#घोषणा MPS_PORT_STAT_LB_PORT_1519B_MAX_L 0x520
#घोषणा MPS_PORT_STAT_LB_PORT_1519B_MAX_H 0x524
#घोषणा MPS_PORT_STAT_LB_PORT_DROP_FRAMES 0x528
#घोषणा MPS_PORT_STAT_LB_PORT_DROP_FRAMES_L 0x528
#घोषणा MPS_PORT_STAT_RX_PORT_BYTES_L 0x540
#घोषणा MPS_PORT_STAT_RX_PORT_BYTES_H 0x544
#घोषणा MPS_PORT_STAT_RX_PORT_FRAMES_L 0x548
#घोषणा MPS_PORT_STAT_RX_PORT_FRAMES_H 0x54c
#घोषणा MPS_PORT_STAT_RX_PORT_BCAST_L 0x550
#घोषणा MPS_PORT_STAT_RX_PORT_BCAST_H 0x554
#घोषणा MPS_PORT_STAT_RX_PORT_MCAST_L 0x558
#घोषणा MPS_PORT_STAT_RX_PORT_MCAST_H 0x55c
#घोषणा MPS_PORT_STAT_RX_PORT_UCAST_L 0x560
#घोषणा MPS_PORT_STAT_RX_PORT_UCAST_H 0x564
#घोषणा MPS_PORT_STAT_RX_PORT_MTU_ERROR_L 0x568
#घोषणा MPS_PORT_STAT_RX_PORT_MTU_ERROR_H 0x56c
#घोषणा MPS_PORT_STAT_RX_PORT_MTU_CRC_ERROR_L 0x570
#घोषणा MPS_PORT_STAT_RX_PORT_MTU_CRC_ERROR_H 0x574
#घोषणा MPS_PORT_STAT_RX_PORT_CRC_ERROR_L 0x578
#घोषणा MPS_PORT_STAT_RX_PORT_CRC_ERROR_H 0x57c
#घोषणा MPS_PORT_STAT_RX_PORT_LEN_ERROR_L 0x580
#घोषणा MPS_PORT_STAT_RX_PORT_LEN_ERROR_H 0x584
#घोषणा MPS_PORT_STAT_RX_PORT_SYM_ERROR_L 0x588
#घोषणा MPS_PORT_STAT_RX_PORT_SYM_ERROR_H 0x58c
#घोषणा MPS_PORT_STAT_RX_PORT_64B_L 0x590
#घोषणा MPS_PORT_STAT_RX_PORT_64B_H 0x594
#घोषणा MPS_PORT_STAT_RX_PORT_65B_127B_L 0x598
#घोषणा MPS_PORT_STAT_RX_PORT_65B_127B_H 0x59c
#घोषणा MPS_PORT_STAT_RX_PORT_128B_255B_L 0x5a0
#घोषणा MPS_PORT_STAT_RX_PORT_128B_255B_H 0x5a4
#घोषणा MPS_PORT_STAT_RX_PORT_256B_511B_L 0x5a8
#घोषणा MPS_PORT_STAT_RX_PORT_256B_511B_H 0x5ac
#घोषणा MPS_PORT_STAT_RX_PORT_512B_1023B_L 0x5b0
#घोषणा MPS_PORT_STAT_RX_PORT_512B_1023B_H 0x5b4
#घोषणा MPS_PORT_STAT_RX_PORT_1024B_1518B_L 0x5b8
#घोषणा MPS_PORT_STAT_RX_PORT_1024B_1518B_H 0x5bc
#घोषणा MPS_PORT_STAT_RX_PORT_1519B_MAX_L 0x5c0
#घोषणा MPS_PORT_STAT_RX_PORT_1519B_MAX_H 0x5c4
#घोषणा MPS_PORT_STAT_RX_PORT_PAUSE_L 0x5c8
#घोषणा MPS_PORT_STAT_RX_PORT_PAUSE_H 0x5cc
#घोषणा MPS_PORT_STAT_RX_PORT_PPP0_L 0x5d0
#घोषणा MPS_PORT_STAT_RX_PORT_PPP0_H 0x5d4
#घोषणा MPS_PORT_STAT_RX_PORT_PPP1_L 0x5d8
#घोषणा MPS_PORT_STAT_RX_PORT_PPP1_H 0x5dc
#घोषणा MPS_PORT_STAT_RX_PORT_PPP2_L 0x5e0
#घोषणा MPS_PORT_STAT_RX_PORT_PPP2_H 0x5e4
#घोषणा MPS_PORT_STAT_RX_PORT_PPP3_L 0x5e8
#घोषणा MPS_PORT_STAT_RX_PORT_PPP3_H 0x5ec
#घोषणा MPS_PORT_STAT_RX_PORT_PPP4_L 0x5f0
#घोषणा MPS_PORT_STAT_RX_PORT_PPP4_H 0x5f4
#घोषणा MPS_PORT_STAT_RX_PORT_PPP5_L 0x5f8
#घोषणा MPS_PORT_STAT_RX_PORT_PPP5_H 0x5fc
#घोषणा MPS_PORT_STAT_RX_PORT_PPP6_L 0x600
#घोषणा MPS_PORT_STAT_RX_PORT_PPP6_H 0x604
#घोषणा MPS_PORT_STAT_RX_PORT_PPP7_L 0x608
#घोषणा MPS_PORT_STAT_RX_PORT_PPP7_H 0x60c
#घोषणा MPS_PORT_STAT_RX_PORT_LESS_64B_L 0x610
#घोषणा MPS_PORT_STAT_RX_PORT_LESS_64B_H 0x614
#घोषणा MAC_PORT_MAGIC_MACID_LO 0x824
#घोषणा MAC_PORT_MAGIC_MACID_HI 0x828
#घोषणा MAC_PORT_TX_TS_VAL_LO   0x928
#घोषणा MAC_PORT_TX_TS_VAL_HI   0x92c

#घोषणा MAC_PORT_EPIO_DATA0_A 0x8c0
#घोषणा MAC_PORT_EPIO_DATA1_A 0x8c4
#घोषणा MAC_PORT_EPIO_DATA2_A 0x8c8
#घोषणा MAC_PORT_EPIO_DATA3_A 0x8cc
#घोषणा MAC_PORT_EPIO_OP_A 0x8d0

#घोषणा MAC_PORT_CFG2_A 0x818

#घोषणा MAC_PORT_PTP_SUM_LO_A 0x990
#घोषणा MAC_PORT_PTP_SUM_HI_A 0x994

#घोषणा MPS_CMN_CTL_A	0x9000

#घोषणा COUNTPAUSEMCRX_S    5
#घोषणा COUNTPAUSEMCRX_V(x) ((x) << COUNTPAUSEMCRX_S)
#घोषणा COUNTPAUSEMCRX_F    COUNTPAUSEMCRX_V(1U)

#घोषणा COUNTPAUSESTATRX_S    4
#घोषणा COUNTPAUSESTATRX_V(x) ((x) << COUNTPAUSESTATRX_S)
#घोषणा COUNTPAUSESTATRX_F    COUNTPAUSESTATRX_V(1U)

#घोषणा COUNTPAUSEMCTX_S    3
#घोषणा COUNTPAUSEMCTX_V(x) ((x) << COUNTPAUSEMCTX_S)
#घोषणा COUNTPAUSEMCTX_F    COUNTPAUSEMCTX_V(1U)

#घोषणा COUNTPAUSESTATTX_S    2
#घोषणा COUNTPAUSESTATTX_V(x) ((x) << COUNTPAUSESTATTX_S)
#घोषणा COUNTPAUSESTATTX_F    COUNTPAUSESTATTX_V(1U)

#घोषणा NUMPORTS_S    0
#घोषणा NUMPORTS_M    0x3U
#घोषणा NUMPORTS_G(x) (((x) >> NUMPORTS_S) & NUMPORTS_M)

#घोषणा MPS_INT_CAUSE_A 0x9008
#घोषणा MPS_TX_INT_CAUSE_A 0x9408
#घोषणा MPS_STAT_CTL_A 0x9600

#घोषणा FRMERR_S    15
#घोषणा FRMERR_V(x) ((x) << FRMERR_S)
#घोषणा FRMERR_F    FRMERR_V(1U)

#घोषणा SECNTERR_S    14
#घोषणा SECNTERR_V(x) ((x) << SECNTERR_S)
#घोषणा SECNTERR_F    SECNTERR_V(1U)

#घोषणा BUBBLE_S    13
#घोषणा BUBBLE_V(x) ((x) << BUBBLE_S)
#घोषणा BUBBLE_F    BUBBLE_V(1U)

#घोषणा TXDESCFIFO_S    9
#घोषणा TXDESCFIFO_M    0xfU
#घोषणा TXDESCFIFO_V(x) ((x) << TXDESCFIFO_S)

#घोषणा TXDATAFIFO_S    5
#घोषणा TXDATAFIFO_M    0xfU
#घोषणा TXDATAFIFO_V(x) ((x) << TXDATAFIFO_S)

#घोषणा NCSIFIFO_S    4
#घोषणा NCSIFIFO_V(x) ((x) << NCSIFIFO_S)
#घोषणा NCSIFIFO_F    NCSIFIFO_V(1U)

#घोषणा TPFIFO_S    0
#घोषणा TPFIFO_M    0xfU
#घोषणा TPFIFO_V(x) ((x) << TPFIFO_S)

#घोषणा MPS_STAT_PERR_INT_CAUSE_SRAM_A		0x9614
#घोषणा MPS_STAT_PERR_INT_CAUSE_TX_FIFO_A	0x9620
#घोषणा MPS_STAT_PERR_INT_CAUSE_RX_FIFO_A	0x962c

#घोषणा MPS_STAT_RX_BG_0_MAC_DROP_FRAME_L 0x9640
#घोषणा MPS_STAT_RX_BG_0_MAC_DROP_FRAME_H 0x9644
#घोषणा MPS_STAT_RX_BG_1_MAC_DROP_FRAME_L 0x9648
#घोषणा MPS_STAT_RX_BG_1_MAC_DROP_FRAME_H 0x964c
#घोषणा MPS_STAT_RX_BG_2_MAC_DROP_FRAME_L 0x9650
#घोषणा MPS_STAT_RX_BG_2_MAC_DROP_FRAME_H 0x9654
#घोषणा MPS_STAT_RX_BG_3_MAC_DROP_FRAME_L 0x9658
#घोषणा MPS_STAT_RX_BG_3_MAC_DROP_FRAME_H 0x965c
#घोषणा MPS_STAT_RX_BG_0_LB_DROP_FRAME_L 0x9660
#घोषणा MPS_STAT_RX_BG_0_LB_DROP_FRAME_H 0x9664
#घोषणा MPS_STAT_RX_BG_1_LB_DROP_FRAME_L 0x9668
#घोषणा MPS_STAT_RX_BG_1_LB_DROP_FRAME_H 0x966c
#घोषणा MPS_STAT_RX_BG_2_LB_DROP_FRAME_L 0x9670
#घोषणा MPS_STAT_RX_BG_2_LB_DROP_FRAME_H 0x9674
#घोषणा MPS_STAT_RX_BG_3_LB_DROP_FRAME_L 0x9678
#घोषणा MPS_STAT_RX_BG_3_LB_DROP_FRAME_H 0x967c
#घोषणा MPS_STAT_RX_BG_0_MAC_TRUNC_FRAME_L 0x9680
#घोषणा MPS_STAT_RX_BG_0_MAC_TRUNC_FRAME_H 0x9684
#घोषणा MPS_STAT_RX_BG_1_MAC_TRUNC_FRAME_L 0x9688
#घोषणा MPS_STAT_RX_BG_1_MAC_TRUNC_FRAME_H 0x968c
#घोषणा MPS_STAT_RX_BG_2_MAC_TRUNC_FRAME_L 0x9690
#घोषणा MPS_STAT_RX_BG_2_MAC_TRUNC_FRAME_H 0x9694
#घोषणा MPS_STAT_RX_BG_3_MAC_TRUNC_FRAME_L 0x9698
#घोषणा MPS_STAT_RX_BG_3_MAC_TRUNC_FRAME_H 0x969c
#घोषणा MPS_STAT_RX_BG_0_LB_TRUNC_FRAME_L 0x96a0
#घोषणा MPS_STAT_RX_BG_0_LB_TRUNC_FRAME_H 0x96a4
#घोषणा MPS_STAT_RX_BG_1_LB_TRUNC_FRAME_L 0x96a8
#घोषणा MPS_STAT_RX_BG_1_LB_TRUNC_FRAME_H 0x96ac
#घोषणा MPS_STAT_RX_BG_2_LB_TRUNC_FRAME_L 0x96b0
#घोषणा MPS_STAT_RX_BG_2_LB_TRUNC_FRAME_H 0x96b4
#घोषणा MPS_STAT_RX_BG_3_LB_TRUNC_FRAME_L 0x96b8
#घोषणा MPS_STAT_RX_BG_3_LB_TRUNC_FRAME_H 0x96bc

#घोषणा MPS_TRC_CFG_A 0x9800

#घोषणा TRCFIFOEMPTY_S    4
#घोषणा TRCFIFOEMPTY_V(x) ((x) << TRCFIFOEMPTY_S)
#घोषणा TRCFIFOEMPTY_F    TRCFIFOEMPTY_V(1U)

#घोषणा TRCIGNOREDROPINPUT_S    3
#घोषणा TRCIGNOREDROPINPUT_V(x) ((x) << TRCIGNOREDROPINPUT_S)
#घोषणा TRCIGNOREDROPINPUT_F    TRCIGNOREDROPINPUT_V(1U)

#घोषणा TRCKEEPDUPLICATES_S    2
#घोषणा TRCKEEPDUPLICATES_V(x) ((x) << TRCKEEPDUPLICATES_S)
#घोषणा TRCKEEPDUPLICATES_F    TRCKEEPDUPLICATES_V(1U)

#घोषणा TRCEN_S    1
#घोषणा TRCEN_V(x) ((x) << TRCEN_S)
#घोषणा TRCEN_F    TRCEN_V(1U)

#घोषणा TRCMULTIFILTER_S    0
#घोषणा TRCMULTIFILTER_V(x) ((x) << TRCMULTIFILTER_S)
#घोषणा TRCMULTIFILTER_F    TRCMULTIFILTER_V(1U)

#घोषणा MPS_TRC_RSS_CONTROL_A		0x9808
#घोषणा MPS_TRC_FILTER1_RSS_CONTROL_A	0x9ff4
#घोषणा MPS_TRC_FILTER2_RSS_CONTROL_A	0x9ffc
#घोषणा MPS_TRC_FILTER3_RSS_CONTROL_A	0xa004
#घोषणा MPS_T5_TRC_RSS_CONTROL_A	0xa00c

#घोषणा RSSCONTROL_S    16
#घोषणा RSSCONTROL_V(x) ((x) << RSSCONTROL_S)

#घोषणा QUEUENUMBER_S    0
#घोषणा QUEUENUMBER_V(x) ((x) << QUEUENUMBER_S)

#घोषणा TFINVERTMATCH_S    24
#घोषणा TFINVERTMATCH_V(x) ((x) << TFINVERTMATCH_S)
#घोषणा TFINVERTMATCH_F    TFINVERTMATCH_V(1U)

#घोषणा TFEN_S    22
#घोषणा TFEN_V(x) ((x) << TFEN_S)
#घोषणा TFEN_F    TFEN_V(1U)

#घोषणा TFPORT_S    18
#घोषणा TFPORT_M    0xfU
#घोषणा TFPORT_V(x) ((x) << TFPORT_S)
#घोषणा TFPORT_G(x) (((x) >> TFPORT_S) & TFPORT_M)

#घोषणा TFLENGTH_S    8
#घोषणा TFLENGTH_M    0x1fU
#घोषणा TFLENGTH_V(x) ((x) << TFLENGTH_S)
#घोषणा TFLENGTH_G(x) (((x) >> TFLENGTH_S) & TFLENGTH_M)

#घोषणा TFOFFSET_S    0
#घोषणा TFOFFSET_M    0x1fU
#घोषणा TFOFFSET_V(x) ((x) << TFOFFSET_S)
#घोषणा TFOFFSET_G(x) (((x) >> TFOFFSET_S) & TFOFFSET_M)

#घोषणा T5_TFINVERTMATCH_S    25
#घोषणा T5_TFINVERTMATCH_V(x) ((x) << T5_TFINVERTMATCH_S)
#घोषणा T5_TFINVERTMATCH_F    T5_TFINVERTMATCH_V(1U)

#घोषणा T5_TFEN_S    23
#घोषणा T5_TFEN_V(x) ((x) << T5_TFEN_S)
#घोषणा T5_TFEN_F    T5_TFEN_V(1U)

#घोषणा T5_TFPORT_S    18
#घोषणा T5_TFPORT_M    0x1fU
#घोषणा T5_TFPORT_V(x) ((x) << T5_TFPORT_S)
#घोषणा T5_TFPORT_G(x) (((x) >> T5_TFPORT_S) & T5_TFPORT_M)

#घोषणा MPS_TRC_FILTER_MATCH_CTL_A_A 0x9810
#घोषणा MPS_TRC_FILTER_MATCH_CTL_B_A 0x9820

#घोषणा TFMINPKTSIZE_S    16
#घोषणा TFMINPKTSIZE_M    0x1ffU
#घोषणा TFMINPKTSIZE_V(x) ((x) << TFMINPKTSIZE_S)
#घोषणा TFMINPKTSIZE_G(x) (((x) >> TFMINPKTSIZE_S) & TFMINPKTSIZE_M)

#घोषणा TFCAPTUREMAX_S    0
#घोषणा TFCAPTUREMAX_M    0x3fffU
#घोषणा TFCAPTUREMAX_V(x) ((x) << TFCAPTUREMAX_S)
#घोषणा TFCAPTUREMAX_G(x) (((x) >> TFCAPTUREMAX_S) & TFCAPTUREMAX_M)

#घोषणा MPS_TRC_FILTER0_MATCH_A 0x9c00
#घोषणा MPS_TRC_FILTER0_DONT_CARE_A 0x9c80
#घोषणा MPS_TRC_FILTER1_MATCH_A 0x9d00

#घोषणा TP_RSS_CONFIG_A 0x7df0

#घोषणा TNL4TUPENIPV6_S    31
#घोषणा TNL4TUPENIPV6_V(x) ((x) << TNL4TUPENIPV6_S)
#घोषणा TNL4TUPENIPV6_F    TNL4TUPENIPV6_V(1U)

#घोषणा TNL2TUPENIPV6_S    30
#घोषणा TNL2TUPENIPV6_V(x) ((x) << TNL2TUPENIPV6_S)
#घोषणा TNL2TUPENIPV6_F    TNL2TUPENIPV6_V(1U)

#घोषणा TNL4TUPENIPV4_S    29
#घोषणा TNL4TUPENIPV4_V(x) ((x) << TNL4TUPENIPV4_S)
#घोषणा TNL4TUPENIPV4_F    TNL4TUPENIPV4_V(1U)

#घोषणा TNL2TUPENIPV4_S    28
#घोषणा TNL2TUPENIPV4_V(x) ((x) << TNL2TUPENIPV4_S)
#घोषणा TNL2TUPENIPV4_F    TNL2TUPENIPV4_V(1U)

#घोषणा TNLTCPSEL_S    27
#घोषणा TNLTCPSEL_V(x) ((x) << TNLTCPSEL_S)
#घोषणा TNLTCPSEL_F    TNLTCPSEL_V(1U)

#घोषणा TNLIP6SEL_S    26
#घोषणा TNLIP6SEL_V(x) ((x) << TNLIP6SEL_S)
#घोषणा TNLIP6SEL_F    TNLIP6SEL_V(1U)

#घोषणा TNLVRTSEL_S    25
#घोषणा TNLVRTSEL_V(x) ((x) << TNLVRTSEL_S)
#घोषणा TNLVRTSEL_F    TNLVRTSEL_V(1U)

#घोषणा TNLMAPEN_S    24
#घोषणा TNLMAPEN_V(x) ((x) << TNLMAPEN_S)
#घोषणा TNLMAPEN_F    TNLMAPEN_V(1U)

#घोषणा OFDHASHSAVE_S    19
#घोषणा OFDHASHSAVE_V(x) ((x) << OFDHASHSAVE_S)
#घोषणा OFDHASHSAVE_F    OFDHASHSAVE_V(1U)

#घोषणा OFDVRTSEL_S    18
#घोषणा OFDVRTSEL_V(x) ((x) << OFDVRTSEL_S)
#घोषणा OFDVRTSEL_F    OFDVRTSEL_V(1U)

#घोषणा OFDMAPEN_S    17
#घोषणा OFDMAPEN_V(x) ((x) << OFDMAPEN_S)
#घोषणा OFDMAPEN_F    OFDMAPEN_V(1U)

#घोषणा OFDLKPEN_S    16
#घोषणा OFDLKPEN_V(x) ((x) << OFDLKPEN_S)
#घोषणा OFDLKPEN_F    OFDLKPEN_V(1U)

#घोषणा SYN4TUPENIPV6_S    15
#घोषणा SYN4TUPENIPV6_V(x) ((x) << SYN4TUPENIPV6_S)
#घोषणा SYN4TUPENIPV6_F    SYN4TUPENIPV6_V(1U)

#घोषणा SYN2TUPENIPV6_S    14
#घोषणा SYN2TUPENIPV6_V(x) ((x) << SYN2TUPENIPV6_S)
#घोषणा SYN2TUPENIPV6_F    SYN2TUPENIPV6_V(1U)

#घोषणा SYN4TUPENIPV4_S    13
#घोषणा SYN4TUPENIPV4_V(x) ((x) << SYN4TUPENIPV4_S)
#घोषणा SYN4TUPENIPV4_F    SYN4TUPENIPV4_V(1U)

#घोषणा SYN2TUPENIPV4_S    12
#घोषणा SYN2TUPENIPV4_V(x) ((x) << SYN2TUPENIPV4_S)
#घोषणा SYN2TUPENIPV4_F    SYN2TUPENIPV4_V(1U)

#घोषणा SYNIP6SEL_S    11
#घोषणा SYNIP6SEL_V(x) ((x) << SYNIP6SEL_S)
#घोषणा SYNIP6SEL_F    SYNIP6SEL_V(1U)

#घोषणा SYNVRTSEL_S    10
#घोषणा SYNVRTSEL_V(x) ((x) << SYNVRTSEL_S)
#घोषणा SYNVRTSEL_F    SYNVRTSEL_V(1U)

#घोषणा SYNMAPEN_S    9
#घोषणा SYNMAPEN_V(x) ((x) << SYNMAPEN_S)
#घोषणा SYNMAPEN_F    SYNMAPEN_V(1U)

#घोषणा SYNLKPEN_S    8
#घोषणा SYNLKPEN_V(x) ((x) << SYNLKPEN_S)
#घोषणा SYNLKPEN_F    SYNLKPEN_V(1U)

#घोषणा CHANNELENABLE_S    7
#घोषणा CHANNELENABLE_V(x) ((x) << CHANNELENABLE_S)
#घोषणा CHANNELENABLE_F    CHANNELENABLE_V(1U)

#घोषणा PORTENABLE_S    6
#घोषणा PORTENABLE_V(x) ((x) << PORTENABLE_S)
#घोषणा PORTENABLE_F    PORTENABLE_V(1U)

#घोषणा TNLALLLOOKUP_S    5
#घोषणा TNLALLLOOKUP_V(x) ((x) << TNLALLLOOKUP_S)
#घोषणा TNLALLLOOKUP_F    TNLALLLOOKUP_V(1U)

#घोषणा VIRTENABLE_S    4
#घोषणा VIRTENABLE_V(x) ((x) << VIRTENABLE_S)
#घोषणा VIRTENABLE_F    VIRTENABLE_V(1U)

#घोषणा CONGESTIONENABLE_S    3
#घोषणा CONGESTIONENABLE_V(x) ((x) << CONGESTIONENABLE_S)
#घोषणा CONGESTIONENABLE_F    CONGESTIONENABLE_V(1U)

#घोषणा HASHTOEPLITZ_S    2
#घोषणा HASHTOEPLITZ_V(x) ((x) << HASHTOEPLITZ_S)
#घोषणा HASHTOEPLITZ_F    HASHTOEPLITZ_V(1U)

#घोषणा UDPENABLE_S    1
#घोषणा UDPENABLE_V(x) ((x) << UDPENABLE_S)
#घोषणा UDPENABLE_F    UDPENABLE_V(1U)

#घोषणा DISABLE_S    0
#घोषणा DISABLE_V(x) ((x) << DISABLE_S)
#घोषणा DISABLE_F    DISABLE_V(1U)

#घोषणा TP_RSS_CONFIG_TNL_A 0x7df4

#घोषणा MASKSIZE_S    28
#घोषणा MASKSIZE_M    0xfU
#घोषणा MASKSIZE_V(x) ((x) << MASKSIZE_S)
#घोषणा MASKSIZE_G(x) (((x) >> MASKSIZE_S) & MASKSIZE_M)

#घोषणा MASKFILTER_S    16
#घोषणा MASKFILTER_M    0x7ffU
#घोषणा MASKFILTER_V(x) ((x) << MASKFILTER_S)
#घोषणा MASKFILTER_G(x) (((x) >> MASKFILTER_S) & MASKFILTER_M)

#घोषणा USEWIRECH_S    0
#घोषणा USEWIRECH_V(x) ((x) << USEWIRECH_S)
#घोषणा USEWIRECH_F    USEWIRECH_V(1U)

#घोषणा HASHALL_S    2
#घोषणा HASHALL_V(x) ((x) << HASHALL_S)
#घोषणा HASHALL_F    HASHALL_V(1U)

#घोषणा HASHETH_S    1
#घोषणा HASHETH_V(x) ((x) << HASHETH_S)
#घोषणा HASHETH_F    HASHETH_V(1U)

#घोषणा TP_RSS_CONFIG_OFD_A 0x7df8

#घोषणा RRCPLMAPEN_S    20
#घोषणा RRCPLMAPEN_V(x) ((x) << RRCPLMAPEN_S)
#घोषणा RRCPLMAPEN_F    RRCPLMAPEN_V(1U)

#घोषणा RRCPLQUEWIDTH_S    16
#घोषणा RRCPLQUEWIDTH_M    0xfU
#घोषणा RRCPLQUEWIDTH_V(x) ((x) << RRCPLQUEWIDTH_S)
#घोषणा RRCPLQUEWIDTH_G(x) (((x) >> RRCPLQUEWIDTH_S) & RRCPLQUEWIDTH_M)

#घोषणा TP_RSS_CONFIG_SYN_A 0x7dfc
#घोषणा TP_RSS_CONFIG_VRT_A 0x7e00

#घोषणा VFRDRG_S    25
#घोषणा VFRDRG_V(x) ((x) << VFRDRG_S)
#घोषणा VFRDRG_F    VFRDRG_V(1U)

#घोषणा VFRDEN_S    24
#घोषणा VFRDEN_V(x) ((x) << VFRDEN_S)
#घोषणा VFRDEN_F    VFRDEN_V(1U)

#घोषणा VFPERREN_S    23
#घोषणा VFPERREN_V(x) ((x) << VFPERREN_S)
#घोषणा VFPERREN_F    VFPERREN_V(1U)

#घोषणा KEYPERREN_S    22
#घोषणा KEYPERREN_V(x) ((x) << KEYPERREN_S)
#घोषणा KEYPERREN_F    KEYPERREN_V(1U)

#घोषणा DISABLEVLAN_S    21
#घोषणा DISABLEVLAN_V(x) ((x) << DISABLEVLAN_S)
#घोषणा DISABLEVLAN_F    DISABLEVLAN_V(1U)

#घोषणा ENABLEUP0_S    20
#घोषणा ENABLEUP0_V(x) ((x) << ENABLEUP0_S)
#घोषणा ENABLEUP0_F    ENABLEUP0_V(1U)

#घोषणा HASHDELAY_S    16
#घोषणा HASHDELAY_M    0xfU
#घोषणा HASHDELAY_V(x) ((x) << HASHDELAY_S)
#घोषणा HASHDELAY_G(x) (((x) >> HASHDELAY_S) & HASHDELAY_M)

#घोषणा VFWRADDR_S    8
#घोषणा VFWRADDR_M    0x7fU
#घोषणा VFWRADDR_V(x) ((x) << VFWRADDR_S)
#घोषणा VFWRADDR_G(x) (((x) >> VFWRADDR_S) & VFWRADDR_M)

#घोषणा KEYMODE_S    6
#घोषणा KEYMODE_M    0x3U
#घोषणा KEYMODE_V(x) ((x) << KEYMODE_S)
#घोषणा KEYMODE_G(x) (((x) >> KEYMODE_S) & KEYMODE_M)

#घोषणा VFWREN_S    5
#घोषणा VFWREN_V(x) ((x) << VFWREN_S)
#घोषणा VFWREN_F    VFWREN_V(1U)

#घोषणा KEYWREN_S    4
#घोषणा KEYWREN_V(x) ((x) << KEYWREN_S)
#घोषणा KEYWREN_F    KEYWREN_V(1U)

#घोषणा KEYWRADDR_S    0
#घोषणा KEYWRADDR_M    0xfU
#घोषणा KEYWRADDR_V(x) ((x) << KEYWRADDR_S)
#घोषणा KEYWRADDR_G(x) (((x) >> KEYWRADDR_S) & KEYWRADDR_M)

#घोषणा KEYWRADDRX_S    30
#घोषणा KEYWRADDRX_M    0x3U
#घोषणा KEYWRADDRX_V(x) ((x) << KEYWRADDRX_S)
#घोषणा KEYWRADDRX_G(x) (((x) >> KEYWRADDRX_S) & KEYWRADDRX_M)

#घोषणा KEYEXTEND_S    26
#घोषणा KEYEXTEND_V(x) ((x) << KEYEXTEND_S)
#घोषणा KEYEXTEND_F    KEYEXTEND_V(1U)

#घोषणा LKPIDXSIZE_S    24
#घोषणा LKPIDXSIZE_M    0x3U
#घोषणा LKPIDXSIZE_V(x) ((x) << LKPIDXSIZE_S)
#घोषणा LKPIDXSIZE_G(x) (((x) >> LKPIDXSIZE_S) & LKPIDXSIZE_M)

#घोषणा TP_RSS_VFL_CONFIG_A 0x3a
#घोषणा TP_RSS_VFH_CONFIG_A 0x3b

#घोषणा ENABLEUDPHASH_S    31
#घोषणा ENABLEUDPHASH_V(x) ((x) << ENABLEUDPHASH_S)
#घोषणा ENABLEUDPHASH_F    ENABLEUDPHASH_V(1U)

#घोषणा VFUPEN_S    30
#घोषणा VFUPEN_V(x) ((x) << VFUPEN_S)
#घोषणा VFUPEN_F    VFUPEN_V(1U)

#घोषणा VFVLNEX_S    28
#घोषणा VFVLNEX_V(x) ((x) << VFVLNEX_S)
#घोषणा VFVLNEX_F    VFVLNEX_V(1U)

#घोषणा VFPRTEN_S    27
#घोषणा VFPRTEN_V(x) ((x) << VFPRTEN_S)
#घोषणा VFPRTEN_F    VFPRTEN_V(1U)

#घोषणा VFCHNEN_S    26
#घोषणा VFCHNEN_V(x) ((x) << VFCHNEN_S)
#घोषणा VFCHNEN_F    VFCHNEN_V(1U)

#घोषणा DEFAULTQUEUE_S    16
#घोषणा DEFAULTQUEUE_M    0x3ffU
#घोषणा DEFAULTQUEUE_G(x) (((x) >> DEFAULTQUEUE_S) & DEFAULTQUEUE_M)

#घोषणा VFIP6TWOTUPEN_S    6
#घोषणा VFIP6TWOTUPEN_V(x) ((x) << VFIP6TWOTUPEN_S)
#घोषणा VFIP6TWOTUPEN_F    VFIP6TWOTUPEN_V(1U)

#घोषणा VFIP4FOURTUPEN_S    5
#घोषणा VFIP4FOURTUPEN_V(x) ((x) << VFIP4FOURTUPEN_S)
#घोषणा VFIP4FOURTUPEN_F    VFIP4FOURTUPEN_V(1U)

#घोषणा VFIP4TWOTUPEN_S    4
#घोषणा VFIP4TWOTUPEN_V(x) ((x) << VFIP4TWOTUPEN_S)
#घोषणा VFIP4TWOTUPEN_F    VFIP4TWOTUPEN_V(1U)

#घोषणा KEYINDEX_S    0
#घोषणा KEYINDEX_M    0xfU
#घोषणा KEYINDEX_G(x) (((x) >> KEYINDEX_S) & KEYINDEX_M)

#घोषणा MAPENABLE_S    31
#घोषणा MAPENABLE_V(x) ((x) << MAPENABLE_S)
#घोषणा MAPENABLE_F    MAPENABLE_V(1U)

#घोषणा CHNENABLE_S    30
#घोषणा CHNENABLE_V(x) ((x) << CHNENABLE_S)
#घोषणा CHNENABLE_F    CHNENABLE_V(1U)

#घोषणा LE_DB_DBGI_CONFIG_A 0x19cf0

#घोषणा DBGICMDBUSY_S    3
#घोषणा DBGICMDBUSY_V(x) ((x) << DBGICMDBUSY_S)
#घोषणा DBGICMDBUSY_F    DBGICMDBUSY_V(1U)

#घोषणा DBGICMDSTRT_S    2
#घोषणा DBGICMDSTRT_V(x) ((x) << DBGICMDSTRT_S)
#घोषणा DBGICMDSTRT_F    DBGICMDSTRT_V(1U)

#घोषणा DBGICMDMODE_S    0
#घोषणा DBGICMDMODE_M    0x3U
#घोषणा DBGICMDMODE_V(x) ((x) << DBGICMDMODE_S)

#घोषणा LE_DB_DBGI_REQ_TCAM_CMD_A 0x19cf4

#घोषणा DBGICMD_S    20
#घोषणा DBGICMD_M    0xfU
#घोषणा DBGICMD_V(x) ((x) << DBGICMD_S)

#घोषणा DBGITID_S    0
#घोषणा DBGITID_M    0xfffffU
#घोषणा DBGITID_V(x) ((x) << DBGITID_S)

#घोषणा LE_DB_DBGI_REQ_DATA_A 0x19d00
#घोषणा LE_DB_DBGI_RSP_STATUS_A 0x19d94

#घोषणा LE_DB_DBGI_RSP_DATA_A 0x19da0

#घोषणा PRTENABLE_S    29
#घोषणा PRTENABLE_V(x) ((x) << PRTENABLE_S)
#घोषणा PRTENABLE_F    PRTENABLE_V(1U)

#घोषणा UDPFOURTUPEN_S    28
#घोषणा UDPFOURTUPEN_V(x) ((x) << UDPFOURTUPEN_S)
#घोषणा UDPFOURTUPEN_F    UDPFOURTUPEN_V(1U)

#घोषणा IP6FOURTUPEN_S    27
#घोषणा IP6FOURTUPEN_V(x) ((x) << IP6FOURTUPEN_S)
#घोषणा IP6FOURTUPEN_F    IP6FOURTUPEN_V(1U)

#घोषणा IP6TWOTUPEN_S    26
#घोषणा IP6TWOTUPEN_V(x) ((x) << IP6TWOTUPEN_S)
#घोषणा IP6TWOTUPEN_F    IP6TWOTUPEN_V(1U)

#घोषणा IP4FOURTUPEN_S    25
#घोषणा IP4FOURTUPEN_V(x) ((x) << IP4FOURTUPEN_S)
#घोषणा IP4FOURTUPEN_F    IP4FOURTUPEN_V(1U)

#घोषणा IP4TWOTUPEN_S    24
#घोषणा IP4TWOTUPEN_V(x) ((x) << IP4TWOTUPEN_S)
#घोषणा IP4TWOTUPEN_F    IP4TWOTUPEN_V(1U)

#घोषणा IVFWIDTH_S    20
#घोषणा IVFWIDTH_M    0xfU
#घोषणा IVFWIDTH_V(x) ((x) << IVFWIDTH_S)
#घोषणा IVFWIDTH_G(x) (((x) >> IVFWIDTH_S) & IVFWIDTH_M)

#घोषणा CH1DEFAULTQUEUE_S    10
#घोषणा CH1DEFAULTQUEUE_M    0x3ffU
#घोषणा CH1DEFAULTQUEUE_V(x) ((x) << CH1DEFAULTQUEUE_S)
#घोषणा CH1DEFAULTQUEUE_G(x) (((x) >> CH1DEFAULTQUEUE_S) & CH1DEFAULTQUEUE_M)

#घोषणा CH0DEFAULTQUEUE_S    0
#घोषणा CH0DEFAULTQUEUE_M    0x3ffU
#घोषणा CH0DEFAULTQUEUE_V(x) ((x) << CH0DEFAULTQUEUE_S)
#घोषणा CH0DEFAULTQUEUE_G(x) (((x) >> CH0DEFAULTQUEUE_S) & CH0DEFAULTQUEUE_M)

#घोषणा VFLKPIDX_S    8
#घोषणा VFLKPIDX_M    0xffU
#घोषणा VFLKPIDX_G(x) (((x) >> VFLKPIDX_S) & VFLKPIDX_M)

#घोषणा T6_VFWRADDR_S    8
#घोषणा T6_VFWRADDR_M    0xffU
#घोषणा T6_VFWRADDR_V(x) ((x) << T6_VFWRADDR_S)
#घोषणा T6_VFWRADDR_G(x) (((x) >> T6_VFWRADDR_S) & T6_VFWRADDR_M)

#घोषणा TP_RSS_CONFIG_CNG_A 0x7e04
#घोषणा TP_RSS_SECRET_KEY0_A 0x40
#घोषणा TP_RSS_PF0_CONFIG_A 0x30
#घोषणा TP_RSS_PF_MAP_A 0x38
#घोषणा TP_RSS_PF_MSK_A 0x39

#घोषणा PF1LKPIDX_S    3

#घोषणा PF0LKPIDX_M    0x7U

#घोषणा PF1MSKSIZE_S    4
#घोषणा PF1MSKSIZE_M    0xfU

#घोषणा CHNCOUNT3_S    31
#घोषणा CHNCOUNT3_V(x) ((x) << CHNCOUNT3_S)
#घोषणा CHNCOUNT3_F    CHNCOUNT3_V(1U)

#घोषणा CHNCOUNT2_S    30
#घोषणा CHNCOUNT2_V(x) ((x) << CHNCOUNT2_S)
#घोषणा CHNCOUNT2_F    CHNCOUNT2_V(1U)

#घोषणा CHNCOUNT1_S    29
#घोषणा CHNCOUNT1_V(x) ((x) << CHNCOUNT1_S)
#घोषणा CHNCOUNT1_F    CHNCOUNT1_V(1U)

#घोषणा CHNCOUNT0_S    28
#घोषणा CHNCOUNT0_V(x) ((x) << CHNCOUNT0_S)
#घोषणा CHNCOUNT0_F    CHNCOUNT0_V(1U)

#घोषणा CHNUNDFLOW3_S    27
#घोषणा CHNUNDFLOW3_V(x) ((x) << CHNUNDFLOW3_S)
#घोषणा CHNUNDFLOW3_F    CHNUNDFLOW3_V(1U)

#घोषणा CHNUNDFLOW2_S    26
#घोषणा CHNUNDFLOW2_V(x) ((x) << CHNUNDFLOW2_S)
#घोषणा CHNUNDFLOW2_F    CHNUNDFLOW2_V(1U)

#घोषणा CHNUNDFLOW1_S    25
#घोषणा CHNUNDFLOW1_V(x) ((x) << CHNUNDFLOW1_S)
#घोषणा CHNUNDFLOW1_F    CHNUNDFLOW1_V(1U)

#घोषणा CHNUNDFLOW0_S    24
#घोषणा CHNUNDFLOW0_V(x) ((x) << CHNUNDFLOW0_S)
#घोषणा CHNUNDFLOW0_F    CHNUNDFLOW0_V(1U)

#घोषणा RSTCHN3_S    19
#घोषणा RSTCHN3_V(x) ((x) << RSTCHN3_S)
#घोषणा RSTCHN3_F    RSTCHN3_V(1U)

#घोषणा RSTCHN2_S    18
#घोषणा RSTCHN2_V(x) ((x) << RSTCHN2_S)
#घोषणा RSTCHN2_F    RSTCHN2_V(1U)

#घोषणा RSTCHN1_S    17
#घोषणा RSTCHN1_V(x) ((x) << RSTCHN1_S)
#घोषणा RSTCHN1_F    RSTCHN1_V(1U)

#घोषणा RSTCHN0_S    16
#घोषणा RSTCHN0_V(x) ((x) << RSTCHN0_S)
#घोषणा RSTCHN0_F    RSTCHN0_V(1U)

#घोषणा UPDVLD_S    15
#घोषणा UPDVLD_V(x) ((x) << UPDVLD_S)
#घोषणा UPDVLD_F    UPDVLD_V(1U)

#घोषणा XOFF_S    14
#घोषणा XOFF_V(x) ((x) << XOFF_S)
#घोषणा XOFF_F    XOFF_V(1U)

#घोषणा UPDCHN3_S    13
#घोषणा UPDCHN3_V(x) ((x) << UPDCHN3_S)
#घोषणा UPDCHN3_F    UPDCHN3_V(1U)

#घोषणा UPDCHN2_S    12
#घोषणा UPDCHN2_V(x) ((x) << UPDCHN2_S)
#घोषणा UPDCHN2_F    UPDCHN2_V(1U)

#घोषणा UPDCHN1_S    11
#घोषणा UPDCHN1_V(x) ((x) << UPDCHN1_S)
#घोषणा UPDCHN1_F    UPDCHN1_V(1U)

#घोषणा UPDCHN0_S    10
#घोषणा UPDCHN0_V(x) ((x) << UPDCHN0_S)
#घोषणा UPDCHN0_F    UPDCHN0_V(1U)

#घोषणा QUEUE_S    0
#घोषणा QUEUE_M    0x3ffU
#घोषणा QUEUE_V(x) ((x) << QUEUE_S)
#घोषणा QUEUE_G(x) (((x) >> QUEUE_S) & QUEUE_M)

#घोषणा MPS_TRC_INT_CAUSE_A	0x985c

#घोषणा MISCPERR_S    8
#घोषणा MISCPERR_V(x) ((x) << MISCPERR_S)
#घोषणा MISCPERR_F    MISCPERR_V(1U)

#घोषणा PKTFIFO_S    4
#घोषणा PKTFIFO_M    0xfU
#घोषणा PKTFIFO_V(x) ((x) << PKTFIFO_S)

#घोषणा FILTMEM_S    0
#घोषणा FILTMEM_M    0xfU
#घोषणा FILTMEM_V(x) ((x) << FILTMEM_S)

#घोषणा MPS_CLS_INT_CAUSE_A 0xd028

#घोषणा HASHSRAM_S    2
#घोषणा HASHSRAM_V(x) ((x) << HASHSRAM_S)
#घोषणा HASHSRAM_F    HASHSRAM_V(1U)

#घोषणा MATCHTCAM_S    1
#घोषणा MATCHTCAM_V(x) ((x) << MATCHTCAM_S)
#घोषणा MATCHTCAM_F    MATCHTCAM_V(1U)

#घोषणा MATCHSRAM_S    0
#घोषणा MATCHSRAM_V(x) ((x) << MATCHSRAM_S)
#घोषणा MATCHSRAM_F    MATCHSRAM_V(1U)

#घोषणा MPS_RX_PG_RSV0_A 0x11010
#घोषणा MPS_RX_PG_RSV4_A 0x11020
#घोषणा MPS_RX_PERR_INT_CAUSE_A 0x11074
#घोषणा MPS_RX_MAC_BG_PG_CNT0_A 0x11208
#घोषणा MPS_RX_LPBK_BG_PG_CNT0_A 0x11218

#घोषणा MPS_RX_VXLAN_TYPE_A 0x11234

#घोषणा VXLAN_EN_S    16
#घोषणा VXLAN_EN_V(x) ((x) << VXLAN_EN_S)
#घोषणा VXLAN_EN_F    VXLAN_EN_V(1U)

#घोषणा VXLAN_S    0
#घोषणा VXLAN_M    0xffffU
#घोषणा VXLAN_V(x) ((x) << VXLAN_S)
#घोषणा VXLAN_G(x) (((x) >> VXLAN_S) & VXLAN_M)

#घोषणा MPS_RX_GENEVE_TYPE_A 0x11238

#घोषणा GENEVE_EN_S    16
#घोषणा GENEVE_EN_V(x) ((x) << GENEVE_EN_S)
#घोषणा GENEVE_EN_F    GENEVE_EN_V(1U)

#घोषणा GENEVE_S    0
#घोषणा GENEVE_M    0xffffU
#घोषणा GENEVE_V(x) ((x) << GENEVE_S)
#घोषणा GENEVE_G(x) (((x) >> GENEVE_S) & GENEVE_M)

#घोषणा MPS_CLS_TCAM_Y_L_A 0xf000
#घोषणा MPS_CLS_TCAM_DATA0_A 0xf000
#घोषणा MPS_CLS_TCAM_DATA1_A 0xf004

#घोषणा CTLREQID_S    30
#घोषणा CTLREQID_V(x) ((x) << CTLREQID_S)

#घोषणा MPS_VF_RPLCT_MAP0_A 0x1111c
#घोषणा MPS_VF_RPLCT_MAP1_A 0x11120
#घोषणा MPS_VF_RPLCT_MAP2_A 0x11124
#घोषणा MPS_VF_RPLCT_MAP3_A 0x11128
#घोषणा MPS_VF_RPLCT_MAP4_A 0x11300
#घोषणा MPS_VF_RPLCT_MAP5_A 0x11304
#घोषणा MPS_VF_RPLCT_MAP6_A 0x11308
#घोषणा MPS_VF_RPLCT_MAP7_A 0x1130c

#घोषणा VIDL_S    16
#घोषणा VIDL_M    0xffffU
#घोषणा VIDL_G(x) (((x) >> VIDL_S) & VIDL_M)

#घोषणा DATALKPTYPE_S    10
#घोषणा DATALKPTYPE_M    0x3U
#घोषणा DATALKPTYPE_G(x) (((x) >> DATALKPTYPE_S) & DATALKPTYPE_M)

#घोषणा DATAPORTNUM_S    12
#घोषणा DATAPORTNUM_M    0xfU
#घोषणा DATAPORTNUM_V(x) ((x) << DATAPORTNUM_S)
#घोषणा DATAPORTNUM_G(x) (((x) >> DATAPORTNUM_S) & DATAPORTNUM_M)

#घोषणा DATALKPTYPE_S    10
#घोषणा DATALKPTYPE_M    0x3U
#घोषणा DATALKPTYPE_V(x) ((x) << DATALKPTYPE_S)
#घोषणा DATALKPTYPE_G(x) (((x) >> DATALKPTYPE_S) & DATALKPTYPE_M)

#घोषणा DATADIPHIT_S    8
#घोषणा DATADIPHIT_V(x) ((x) << DATADIPHIT_S)
#घोषणा DATADIPHIT_F    DATADIPHIT_V(1U)

#घोषणा DATAVIDH2_S    7
#घोषणा DATAVIDH2_V(x) ((x) << DATAVIDH2_S)
#घोषणा DATAVIDH2_F    DATAVIDH2_V(1U)

#घोषणा DATAVIDH1_S    0
#घोषणा DATAVIDH1_M    0x7fU
#घोषणा DATAVIDH1_G(x) (((x) >> DATAVIDH1_S) & DATAVIDH1_M)

#घोषणा MPS_CLS_TCAM_RDATA0_REQ_ID1_A 0xf020
#घोषणा MPS_CLS_TCAM_RDATA1_REQ_ID1_A 0xf024
#घोषणा MPS_CLS_TCAM_RDATA2_REQ_ID1_A 0xf028

#घोषणा USED_S    16
#घोषणा USED_M    0x7ffU
#घोषणा USED_G(x) (((x) >> USED_S) & USED_M)

#घोषणा ALLOC_S    0
#घोषणा ALLOC_M    0x7ffU
#घोषणा ALLOC_G(x) (((x) >> ALLOC_S) & ALLOC_M)

#घोषणा T5_USED_S    16
#घोषणा T5_USED_M    0xfffU
#घोषणा T5_USED_G(x) (((x) >> T5_USED_S) & T5_USED_M)

#घोषणा T5_ALLOC_S    0
#घोषणा T5_ALLOC_M    0xfffU
#घोषणा T5_ALLOC_G(x) (((x) >> T5_ALLOC_S) & T5_ALLOC_M)

#घोषणा DMACH_S    0
#घोषणा DMACH_M    0xffffU
#घोषणा DMACH_G(x) (((x) >> DMACH_S) & DMACH_M)

#घोषणा MPS_CLS_TCAM_X_L_A 0xf008
#घोषणा MPS_CLS_TCAM_DATA2_CTL_A 0xf008

#घोषणा CTLCMDTYPE_S    31
#घोषणा CTLCMDTYPE_V(x) ((x) << CTLCMDTYPE_S)
#घोषणा CTLCMDTYPE_F    CTLCMDTYPE_V(1U)

#घोषणा CTLTCAMSEL_S    25
#घोषणा CTLTCAMSEL_V(x) ((x) << CTLTCAMSEL_S)

#घोषणा CTLTCAMINDEX_S    17
#घोषणा CTLTCAMINDEX_V(x) ((x) << CTLTCAMINDEX_S)

#घोषणा CTLXYBITSEL_S    16
#घोषणा CTLXYBITSEL_V(x) ((x) << CTLXYBITSEL_S)

#घोषणा MPS_CLS_TCAM_Y_L(idx) (MPS_CLS_TCAM_Y_L_A + (idx) * 16)
#घोषणा NUM_MPS_CLS_TCAM_Y_L_INSTANCES 512

#घोषणा MPS_CLS_TCAM_X_L(idx) (MPS_CLS_TCAM_X_L_A + (idx) * 16)
#घोषणा NUM_MPS_CLS_TCAM_X_L_INSTANCES 512

#घोषणा MPS_CLS_SRAM_L_A 0xe000

#घोषणा T6_MULTILISTEN0_S    26

#घोषणा T6_SRAM_PRIO3_S    23
#घोषणा T6_SRAM_PRIO3_M    0x7U
#घोषणा T6_SRAM_PRIO3_G(x) (((x) >> T6_SRAM_PRIO3_S) & T6_SRAM_PRIO3_M)

#घोषणा T6_SRAM_PRIO2_S    20
#घोषणा T6_SRAM_PRIO2_M    0x7U
#घोषणा T6_SRAM_PRIO2_G(x) (((x) >> T6_SRAM_PRIO2_S) & T6_SRAM_PRIO2_M)

#घोषणा T6_SRAM_PRIO1_S    17
#घोषणा T6_SRAM_PRIO1_M    0x7U
#घोषणा T6_SRAM_PRIO1_G(x) (((x) >> T6_SRAM_PRIO1_S) & T6_SRAM_PRIO1_M)

#घोषणा T6_SRAM_PRIO0_S    14
#घोषणा T6_SRAM_PRIO0_M    0x7U
#घोषणा T6_SRAM_PRIO0_G(x) (((x) >> T6_SRAM_PRIO0_S) & T6_SRAM_PRIO0_M)

#घोषणा T6_SRAM_VLD_S    13
#घोषणा T6_SRAM_VLD_V(x) ((x) << T6_SRAM_VLD_S)
#घोषणा T6_SRAM_VLD_F    T6_SRAM_VLD_V(1U)

#घोषणा T6_REPLICATE_S    12
#घोषणा T6_REPLICATE_V(x) ((x) << T6_REPLICATE_S)
#घोषणा T6_REPLICATE_F    T6_REPLICATE_V(1U)

#घोषणा T6_PF_S    9
#घोषणा T6_PF_M    0x7U
#घोषणा T6_PF_G(x) (((x) >> T6_PF_S) & T6_PF_M)

#घोषणा T6_VF_VALID_S    8
#घोषणा T6_VF_VALID_V(x) ((x) << T6_VF_VALID_S)
#घोषणा T6_VF_VALID_F    T6_VF_VALID_V(1U)

#घोषणा T6_VF_S    0
#घोषणा T6_VF_M    0xffU
#घोषणा T6_VF_G(x) (((x) >> T6_VF_S) & T6_VF_M)

#घोषणा MPS_CLS_SRAM_H_A 0xe004

#घोषणा MPS_CLS_SRAM_L(idx) (MPS_CLS_SRAM_L_A + (idx) * 8)
#घोषणा NUM_MPS_CLS_SRAM_L_INSTANCES 336

#घोषणा MPS_CLS_SRAM_H(idx) (MPS_CLS_SRAM_H_A + (idx) * 8)
#घोषणा NUM_MPS_CLS_SRAM_H_INSTANCES 336

#घोषणा MULTILISTEN0_S    25

#घोषणा REPLICATE_S    11
#घोषणा REPLICATE_V(x) ((x) << REPLICATE_S)
#घोषणा REPLICATE_F    REPLICATE_V(1U)

#घोषणा PF_S    8
#घोषणा PF_M    0x7U
#घोषणा PF_G(x) (((x) >> PF_S) & PF_M)

#घोषणा VF_VALID_S    7
#घोषणा VF_VALID_V(x) ((x) << VF_VALID_S)
#घोषणा VF_VALID_F    VF_VALID_V(1U)

#घोषणा VF_S    0
#घोषणा VF_M    0x7fU
#घोषणा VF_G(x) (((x) >> VF_S) & VF_M)

#घोषणा SRAM_PRIO3_S    22
#घोषणा SRAM_PRIO3_M    0x7U
#घोषणा SRAM_PRIO3_G(x) (((x) >> SRAM_PRIO3_S) & SRAM_PRIO3_M)

#घोषणा SRAM_PRIO2_S    19
#घोषणा SRAM_PRIO2_M    0x7U
#घोषणा SRAM_PRIO2_G(x) (((x) >> SRAM_PRIO2_S) & SRAM_PRIO2_M)

#घोषणा SRAM_PRIO1_S    16
#घोषणा SRAM_PRIO1_M    0x7U
#घोषणा SRAM_PRIO1_G(x) (((x) >> SRAM_PRIO1_S) & SRAM_PRIO1_M)

#घोषणा SRAM_PRIO0_S    13
#घोषणा SRAM_PRIO0_M    0x7U
#घोषणा SRAM_PRIO0_G(x) (((x) >> SRAM_PRIO0_S) & SRAM_PRIO0_M)

#घोषणा SRAM_VLD_S    12
#घोषणा SRAM_VLD_V(x) ((x) << SRAM_VLD_S)
#घोषणा SRAM_VLD_F    SRAM_VLD_V(1U)

#घोषणा PORTMAP_S    0
#घोषणा PORTMAP_M    0xfU
#घोषणा PORTMAP_G(x) (((x) >> PORTMAP_S) & PORTMAP_M)

#घोषणा CPL_INTR_CAUSE_A 0x19054

#घोषणा CIM_OP_MAP_PERR_S    5
#घोषणा CIM_OP_MAP_PERR_V(x) ((x) << CIM_OP_MAP_PERR_S)
#घोषणा CIM_OP_MAP_PERR_F    CIM_OP_MAP_PERR_V(1U)

#घोषणा CIM_OVFL_ERROR_S    4
#घोषणा CIM_OVFL_ERROR_V(x) ((x) << CIM_OVFL_ERROR_S)
#घोषणा CIM_OVFL_ERROR_F    CIM_OVFL_ERROR_V(1U)

#घोषणा TP_FRAMING_ERROR_S    3
#घोषणा TP_FRAMING_ERROR_V(x) ((x) << TP_FRAMING_ERROR_S)
#घोषणा TP_FRAMING_ERROR_F    TP_FRAMING_ERROR_V(1U)

#घोषणा SGE_FRAMING_ERROR_S    2
#घोषणा SGE_FRAMING_ERROR_V(x) ((x) << SGE_FRAMING_ERROR_S)
#घोषणा SGE_FRAMING_ERROR_F    SGE_FRAMING_ERROR_V(1U)

#घोषणा CIM_FRAMING_ERROR_S    1
#घोषणा CIM_FRAMING_ERROR_V(x) ((x) << CIM_FRAMING_ERROR_S)
#घोषणा CIM_FRAMING_ERROR_F    CIM_FRAMING_ERROR_V(1U)

#घोषणा ZERO_SWITCH_ERROR_S    0
#घोषणा ZERO_SWITCH_ERROR_V(x) ((x) << ZERO_SWITCH_ERROR_S)
#घोषणा ZERO_SWITCH_ERROR_F    ZERO_SWITCH_ERROR_V(1U)

#घोषणा SMB_INT_CAUSE_A 0x19090

#घोषणा MSTTXFIFOPARINT_S    21
#घोषणा MSTTXFIFOPARINT_V(x) ((x) << MSTTXFIFOPARINT_S)
#घोषणा MSTTXFIFOPARINT_F    MSTTXFIFOPARINT_V(1U)

#घोषणा MSTRXFIFOPARINT_S    20
#घोषणा MSTRXFIFOPARINT_V(x) ((x) << MSTRXFIFOPARINT_S)
#घोषणा MSTRXFIFOPARINT_F    MSTRXFIFOPARINT_V(1U)

#घोषणा SLVFIFOPARINT_S    19
#घोषणा SLVFIFOPARINT_V(x) ((x) << SLVFIFOPARINT_S)
#घोषणा SLVFIFOPARINT_F    SLVFIFOPARINT_V(1U)

#घोषणा ULP_RX_INT_CAUSE_A 0x19158
#घोषणा ULP_RX_ISCSI_LLIMIT_A 0x1915c
#घोषणा ULP_RX_ISCSI_ULIMIT_A 0x19160
#घोषणा ULP_RX_ISCSI_TAGMASK_A 0x19164
#घोषणा ULP_RX_ISCSI_PSZ_A 0x19168
#घोषणा ULP_RX_TDDP_LLIMIT_A 0x1916c
#घोषणा ULP_RX_TDDP_ULIMIT_A 0x19170
#घोषणा ULP_RX_STAG_LLIMIT_A 0x1917c
#घोषणा ULP_RX_STAG_ULIMIT_A 0x19180
#घोषणा ULP_RX_RQ_LLIMIT_A 0x19184
#घोषणा ULP_RX_RQ_ULIMIT_A 0x19188
#घोषणा ULP_RX_PBL_LLIMIT_A 0x1918c
#घोषणा ULP_RX_PBL_ULIMIT_A 0x19190
#घोषणा ULP_RX_CTX_BASE_A 0x19194
#घोषणा ULP_RX_RQUDP_LLIMIT_A 0x191a4
#घोषणा ULP_RX_RQUDP_ULIMIT_A 0x191a8
#घोषणा ULP_RX_LA_CTL_A 0x1923c
#घोषणा ULP_RX_LA_RDPTR_A 0x19240
#घोषणा ULP_RX_LA_RDDATA_A 0x19244
#घोषणा ULP_RX_LA_WRPTR_A 0x19248
#घोषणा ULP_RX_TLS_KEY_LLIMIT_A 0x192ac
#घोषणा ULP_RX_TLS_KEY_ULIMIT_A 0x192b0

#घोषणा HPZ3_S    24
#घोषणा HPZ3_V(x) ((x) << HPZ3_S)

#घोषणा HPZ2_S    16
#घोषणा HPZ2_V(x) ((x) << HPZ2_S)

#घोषणा HPZ1_S    8
#घोषणा HPZ1_V(x) ((x) << HPZ1_S)

#घोषणा HPZ0_S    0
#घोषणा HPZ0_V(x) ((x) << HPZ0_S)

#घोषणा ULP_RX_TDDP_PSZ_A 0x19178

/* रेजिस्टरs क्रम module SF */
#घोषणा SF_DATA_A 0x193f8
#घोषणा SF_OP_A 0x193fc

#घोषणा SF_BUSY_S    31
#घोषणा SF_BUSY_V(x) ((x) << SF_BUSY_S)
#घोषणा SF_BUSY_F    SF_BUSY_V(1U)

#घोषणा SF_LOCK_S    4
#घोषणा SF_LOCK_V(x) ((x) << SF_LOCK_S)
#घोषणा SF_LOCK_F    SF_LOCK_V(1U)

#घोषणा SF_CONT_S    3
#घोषणा SF_CONT_V(x) ((x) << SF_CONT_S)
#घोषणा SF_CONT_F    SF_CONT_V(1U)

#घोषणा BYTECNT_S    1
#घोषणा BYTECNT_V(x) ((x) << BYTECNT_S)

#घोषणा OP_S    0
#घोषणा OP_V(x) ((x) << OP_S)
#घोषणा OP_F    OP_V(1U)

#घोषणा PL_PF_INT_CAUSE_A 0x3c0

#घोषणा PFSW_S    3
#घोषणा PFSW_V(x) ((x) << PFSW_S)
#घोषणा PFSW_F    PFSW_V(1U)

#घोषणा PFCIM_S    1
#घोषणा PFCIM_V(x) ((x) << PFCIM_S)
#घोषणा PFCIM_F    PFCIM_V(1U)

#घोषणा PL_PF_INT_ENABLE_A 0x3c4
#घोषणा PL_PF_CTL_A 0x3c8

#घोषणा PL_WHOAMI_A 0x19400

#घोषणा SOURCEPF_S    8
#घोषणा SOURCEPF_M    0x7U
#घोषणा SOURCEPF_G(x) (((x) >> SOURCEPF_S) & SOURCEPF_M)

#घोषणा T6_SOURCEPF_S    9
#घोषणा T6_SOURCEPF_M    0x7U
#घोषणा T6_SOURCEPF_G(x) (((x) >> T6_SOURCEPF_S) & T6_SOURCEPF_M)

#घोषणा PL_INT_CAUSE_A 0x1940c

#घोषणा ULP_TX_S    27
#घोषणा ULP_TX_V(x) ((x) << ULP_TX_S)
#घोषणा ULP_TX_F    ULP_TX_V(1U)

#घोषणा SGE_S    26
#घोषणा SGE_V(x) ((x) << SGE_S)
#घोषणा SGE_F    SGE_V(1U)

#घोषणा CPL_SWITCH_S    24
#घोषणा CPL_SWITCH_V(x) ((x) << CPL_SWITCH_S)
#घोषणा CPL_SWITCH_F    CPL_SWITCH_V(1U)

#घोषणा ULP_RX_S    23
#घोषणा ULP_RX_V(x) ((x) << ULP_RX_S)
#घोषणा ULP_RX_F    ULP_RX_V(1U)

#घोषणा PM_RX_S    22
#घोषणा PM_RX_V(x) ((x) << PM_RX_S)
#घोषणा PM_RX_F    PM_RX_V(1U)

#घोषणा PM_TX_S    21
#घोषणा PM_TX_V(x) ((x) << PM_TX_S)
#घोषणा PM_TX_F    PM_TX_V(1U)

#घोषणा MA_S    20
#घोषणा MA_V(x) ((x) << MA_S)
#घोषणा MA_F    MA_V(1U)

#घोषणा TP_S    19
#घोषणा TP_V(x) ((x) << TP_S)
#घोषणा TP_F    TP_V(1U)

#घोषणा LE_S    18
#घोषणा LE_V(x) ((x) << LE_S)
#घोषणा LE_F    LE_V(1U)

#घोषणा EDC1_S    17
#घोषणा EDC1_V(x) ((x) << EDC1_S)
#घोषणा EDC1_F    EDC1_V(1U)

#घोषणा EDC0_S    16
#घोषणा EDC0_V(x) ((x) << EDC0_S)
#घोषणा EDC0_F    EDC0_V(1U)

#घोषणा MC_S    15
#घोषणा MC_V(x) ((x) << MC_S)
#घोषणा MC_F    MC_V(1U)

#घोषणा PCIE_S    14
#घोषणा PCIE_V(x) ((x) << PCIE_S)
#घोषणा PCIE_F    PCIE_V(1U)

#घोषणा XGMAC_KR1_S    12
#घोषणा XGMAC_KR1_V(x) ((x) << XGMAC_KR1_S)
#घोषणा XGMAC_KR1_F    XGMAC_KR1_V(1U)

#घोषणा XGMAC_KR0_S    11
#घोषणा XGMAC_KR0_V(x) ((x) << XGMAC_KR0_S)
#घोषणा XGMAC_KR0_F    XGMAC_KR0_V(1U)

#घोषणा XGMAC1_S    10
#घोषणा XGMAC1_V(x) ((x) << XGMAC1_S)
#घोषणा XGMAC1_F    XGMAC1_V(1U)

#घोषणा XGMAC0_S    9
#घोषणा XGMAC0_V(x) ((x) << XGMAC0_S)
#घोषणा XGMAC0_F    XGMAC0_V(1U)

#घोषणा SMB_S    8
#घोषणा SMB_V(x) ((x) << SMB_S)
#घोषणा SMB_F    SMB_V(1U)

#घोषणा SF_S    7
#घोषणा SF_V(x) ((x) << SF_S)
#घोषणा SF_F    SF_V(1U)

#घोषणा PL_S    6
#घोषणा PL_V(x) ((x) << PL_S)
#घोषणा PL_F    PL_V(1U)

#घोषणा NCSI_S    5
#घोषणा NCSI_V(x) ((x) << NCSI_S)
#घोषणा NCSI_F    NCSI_V(1U)

#घोषणा MPS_S    4
#घोषणा MPS_V(x) ((x) << MPS_S)
#घोषणा MPS_F    MPS_V(1U)

#घोषणा CIM_S    0
#घोषणा CIM_V(x) ((x) << CIM_S)
#घोषणा CIM_F    CIM_V(1U)

#घोषणा MC1_S    31
#घोषणा MC1_V(x) ((x) << MC1_S)
#घोषणा MC1_F    MC1_V(1U)

#घोषणा PL_INT_ENABLE_A 0x19410
#घोषणा PL_INT_MAP0_A 0x19414
#घोषणा PL_RST_A 0x19428

#घोषणा PIORST_S    1
#घोषणा PIORST_V(x) ((x) << PIORST_S)
#घोषणा PIORST_F    PIORST_V(1U)

#घोषणा PIORSTMODE_S    0
#घोषणा PIORSTMODE_V(x) ((x) << PIORSTMODE_S)
#घोषणा PIORSTMODE_F    PIORSTMODE_V(1U)

#घोषणा PL_PL_INT_CAUSE_A 0x19430

#घोषणा FATALPERR_S    4
#घोषणा FATALPERR_V(x) ((x) << FATALPERR_S)
#घोषणा FATALPERR_F    FATALPERR_V(1U)

#घोषणा PERRVFID_S    0
#घोषणा PERRVFID_V(x) ((x) << PERRVFID_S)
#घोषणा PERRVFID_F    PERRVFID_V(1U)

#घोषणा PL_REV_A 0x1943c

#घोषणा REV_S    0
#घोषणा REV_M    0xfU
#घोषणा REV_V(x) ((x) << REV_S)
#घोषणा REV_G(x) (((x) >> REV_S) & REV_M)

#घोषणा HASHTBLMEMCRCERR_S    27
#घोषणा HASHTBLMEMCRCERR_V(x) ((x) << HASHTBLMEMCRCERR_S)
#घोषणा HASHTBLMEMCRCERR_F    HASHTBLMEMCRCERR_V(1U)

#घोषणा CMDTIDERR_S    22
#घोषणा CMDTIDERR_V(x) ((x) << CMDTIDERR_S)
#घोषणा CMDTIDERR_F    CMDTIDERR_V(1U)

#घोषणा T6_UNKNOWNCMD_S    3
#घोषणा T6_UNKNOWNCMD_V(x) ((x) << T6_UNKNOWNCMD_S)
#घोषणा T6_UNKNOWNCMD_F    T6_UNKNOWNCMD_V(1U)

#घोषणा T6_LIP0_S    2
#घोषणा T6_LIP0_V(x) ((x) << T6_LIP0_S)
#घोषणा T6_LIP0_F    T6_LIP0_V(1U)

#घोषणा T6_LIPMISS_S    1
#घोषणा T6_LIPMISS_V(x) ((x) << T6_LIPMISS_S)
#घोषणा T6_LIPMISS_F    T6_LIPMISS_V(1U)

#घोषणा LE_DB_CONFIG_A 0x19c04
#घोषणा LE_DB_ROUTING_TABLE_INDEX_A 0x19c10
#घोषणा LE_DB_ACTIVE_TABLE_START_INDEX_A 0x19c10
#घोषणा LE_DB_FILTER_TABLE_INDEX_A 0x19c14
#घोषणा LE_DB_SERVER_INDEX_A 0x19c18
#घोषणा LE_DB_SRVR_START_INDEX_A 0x19c18
#घोषणा LE_DB_CLIP_TABLE_INDEX_A 0x19c1c
#घोषणा LE_DB_ACT_CNT_IPV4_A 0x19c20
#घोषणा LE_DB_ACT_CNT_IPV6_A 0x19c24
#घोषणा LE_DB_HASH_CONFIG_A 0x19c28

#घोषणा HASHTIDSIZE_S    16
#घोषणा HASHTIDSIZE_M    0x3fU
#घोषणा HASHTIDSIZE_G(x) (((x) >> HASHTIDSIZE_S) & HASHTIDSIZE_M)

#घोषणा HASHTBLSIZE_S    3
#घोषणा HASHTBLSIZE_M    0x1ffffU
#घोषणा HASHTBLSIZE_G(x) (((x) >> HASHTBLSIZE_S) & HASHTBLSIZE_M)

#घोषणा LE_DB_HASH_TID_BASE_A 0x19c30
#घोषणा LE_DB_HASH_TBL_BASE_ADDR_A 0x19c30
#घोषणा LE_DB_INT_CAUSE_A 0x19c3c
#घोषणा LE_DB_CLCAM_TID_BASE_A 0x19df4
#घोषणा LE_DB_TID_HASHBASE_A 0x19df8
#घोषणा T6_LE_DB_HASH_TID_BASE_A 0x19df8

#घोषणा HASHEN_S    20
#घोषणा HASHEN_V(x) ((x) << HASHEN_S)
#घोषणा HASHEN_F    HASHEN_V(1U)

#घोषणा ASLIPCOMPEN_S    17
#घोषणा ASLIPCOMPEN_V(x) ((x) << ASLIPCOMPEN_S)
#घोषणा ASLIPCOMPEN_F    ASLIPCOMPEN_V(1U)

#घोषणा REQQPARERR_S    16
#घोषणा REQQPARERR_V(x) ((x) << REQQPARERR_S)
#घोषणा REQQPARERR_F    REQQPARERR_V(1U)

#घोषणा UNKNOWNCMD_S    15
#घोषणा UNKNOWNCMD_V(x) ((x) << UNKNOWNCMD_S)
#घोषणा UNKNOWNCMD_F    UNKNOWNCMD_V(1U)

#घोषणा PARITYERR_S    6
#घोषणा PARITYERR_V(x) ((x) << PARITYERR_S)
#घोषणा PARITYERR_F    PARITYERR_V(1U)

#घोषणा LIPMISS_S    5
#घोषणा LIPMISS_V(x) ((x) << LIPMISS_S)
#घोषणा LIPMISS_F    LIPMISS_V(1U)

#घोषणा LIP0_S    4
#घोषणा LIP0_V(x) ((x) << LIP0_S)
#घोषणा LIP0_F    LIP0_V(1U)

#घोषणा BASEADDR_S    3
#घोषणा BASEADDR_M    0x1fffffffU
#घोषणा BASEADDR_G(x) (((x) >> BASEADDR_S) & BASEADDR_M)

#घोषणा TCAMINTPERR_S    13
#घोषणा TCAMINTPERR_V(x) ((x) << TCAMINTPERR_S)
#घोषणा TCAMINTPERR_F    TCAMINTPERR_V(1U)

#घोषणा SSRAMINTPERR_S    10
#घोषणा SSRAMINTPERR_V(x) ((x) << SSRAMINTPERR_S)
#घोषणा SSRAMINTPERR_F    SSRAMINTPERR_V(1U)

#घोषणा LE_DB_RSP_CODE_0_A	0x19c74

#घोषणा TCAM_ACTV_HIT_S		0
#घोषणा TCAM_ACTV_HIT_M		0x1fU
#घोषणा TCAM_ACTV_HIT_V(x)	((x) << TCAM_ACTV_HIT_S)
#घोषणा TCAM_ACTV_HIT_G(x)	(((x) >> TCAM_ACTV_HIT_S) & TCAM_ACTV_HIT_M)

#घोषणा LE_DB_RSP_CODE_1_A     0x19c78

#घोषणा HASH_ACTV_HIT_S		25
#घोषणा HASH_ACTV_HIT_M		0x1fU
#घोषणा HASH_ACTV_HIT_V(x)	((x) << HASH_ACTV_HIT_S)
#घोषणा HASH_ACTV_HIT_G(x)	(((x) >> HASH_ACTV_HIT_S) & HASH_ACTV_HIT_M)

#घोषणा LE_3_DB_HASH_MASK_GEN_IPV4_T6_A	0x19eac
#घोषणा LE_4_DB_HASH_MASK_GEN_IPV4_T6_A	0x19eb0

#घोषणा NCSI_INT_CAUSE_A 0x1a0d8

#घोषणा CIM_DM_PRTY_ERR_S    8
#घोषणा CIM_DM_PRTY_ERR_V(x) ((x) << CIM_DM_PRTY_ERR_S)
#घोषणा CIM_DM_PRTY_ERR_F    CIM_DM_PRTY_ERR_V(1U)

#घोषणा MPS_DM_PRTY_ERR_S    7
#घोषणा MPS_DM_PRTY_ERR_V(x) ((x) << MPS_DM_PRTY_ERR_S)
#घोषणा MPS_DM_PRTY_ERR_F    MPS_DM_PRTY_ERR_V(1U)

#घोषणा TXFIFO_PRTY_ERR_S    1
#घोषणा TXFIFO_PRTY_ERR_V(x) ((x) << TXFIFO_PRTY_ERR_S)
#घोषणा TXFIFO_PRTY_ERR_F    TXFIFO_PRTY_ERR_V(1U)

#घोषणा RXFIFO_PRTY_ERR_S    0
#घोषणा RXFIFO_PRTY_ERR_V(x) ((x) << RXFIFO_PRTY_ERR_S)
#घोषणा RXFIFO_PRTY_ERR_F    RXFIFO_PRTY_ERR_V(1U)

#घोषणा XGMAC_PORT_CFG2_A 0x1018

#घोषणा PATEN_S    18
#घोषणा PATEN_V(x) ((x) << PATEN_S)
#घोषणा PATEN_F    PATEN_V(1U)

#घोषणा MAGICEN_S    17
#घोषणा MAGICEN_V(x) ((x) << MAGICEN_S)
#घोषणा MAGICEN_F    MAGICEN_V(1U)

#घोषणा XGMAC_PORT_MAGIC_MACID_LO 0x1024
#घोषणा XGMAC_PORT_MAGIC_MACID_HI 0x1028

#घोषणा XGMAC_PORT_EPIO_DATA0_A 0x10c0
#घोषणा XGMAC_PORT_EPIO_DATA1_A 0x10c4
#घोषणा XGMAC_PORT_EPIO_DATA2_A 0x10c8
#घोषणा XGMAC_PORT_EPIO_DATA3_A 0x10cc
#घोषणा XGMAC_PORT_EPIO_OP_A 0x10d0

#घोषणा EPIOWR_S    8
#घोषणा EPIOWR_V(x) ((x) << EPIOWR_S)
#घोषणा EPIOWR_F    EPIOWR_V(1U)

#घोषणा ADDRESS_S    0
#घोषणा ADDRESS_V(x) ((x) << ADDRESS_S)

#घोषणा MAC_PORT_INT_CAUSE_A 0x8dc
#घोषणा XGMAC_PORT_INT_CAUSE_A 0x10dc

#घोषणा TP_TX_MOD_QUEUE_REQ_MAP_A 0x7e28

#घोषणा TP_TX_MOD_QUEUE_WEIGHT0_A 0x7e30
#घोषणा TP_TX_MOD_CHANNEL_WEIGHT_A 0x7e34

#घोषणा TX_MOD_QUEUE_REQ_MAP_S    0
#घोषणा TX_MOD_QUEUE_REQ_MAP_V(x) ((x) << TX_MOD_QUEUE_REQ_MAP_S)

#घोषणा TX_MODQ_WEIGHT3_S    24
#घोषणा TX_MODQ_WEIGHT3_V(x) ((x) << TX_MODQ_WEIGHT3_S)

#घोषणा TX_MODQ_WEIGHT2_S    16
#घोषणा TX_MODQ_WEIGHT2_V(x) ((x) << TX_MODQ_WEIGHT2_S)

#घोषणा TX_MODQ_WEIGHT1_S    8
#घोषणा TX_MODQ_WEIGHT1_V(x) ((x) << TX_MODQ_WEIGHT1_S)

#घोषणा TX_MODQ_WEIGHT0_S    0
#घोषणा TX_MODQ_WEIGHT0_V(x) ((x) << TX_MODQ_WEIGHT0_S)

#घोषणा TP_TX_SCHED_HDR_A 0x23
#घोषणा TP_TX_SCHED_FIFO_A 0x24
#घोषणा TP_TX_SCHED_PCMD_A 0x25

#घोषणा NUM_MPS_CLS_SRAM_L_INSTANCES 336
#घोषणा NUM_MPS_T5_CLS_SRAM_L_INSTANCES 512

#घोषणा T5_PORT0_BASE 0x30000
#घोषणा T5_PORT_STRIDE 0x4000
#घोषणा T5_PORT_BASE(idx) (T5_PORT0_BASE + (idx) * T5_PORT_STRIDE)
#घोषणा T5_PORT_REG(idx, reg) (T5_PORT_BASE(idx) + (reg))

#घोषणा MC_0_BASE_ADDR 0x40000
#घोषणा MC_1_BASE_ADDR 0x48000
#घोषणा MC_STRIDE (MC_1_BASE_ADDR - MC_0_BASE_ADDR)
#घोषणा MC_REG(reg, idx) (reg + MC_STRIDE * idx)

#घोषणा MC_P_BIST_CMD_A			0x41400
#घोषणा MC_P_BIST_CMD_ADDR_A		0x41404
#घोषणा MC_P_BIST_CMD_LEN_A		0x41408
#घोषणा MC_P_BIST_DATA_PATTERN_A	0x4140c
#घोषणा MC_P_BIST_STATUS_RDATA_A	0x41488

#घोषणा EDC_T50_BASE_ADDR		0x50000

#घोषणा EDC_H_BIST_CMD_A		0x50004
#घोषणा EDC_H_BIST_CMD_ADDR_A		0x50008
#घोषणा EDC_H_BIST_CMD_LEN_A		0x5000c
#घोषणा EDC_H_BIST_DATA_PATTERN_A	0x50010
#घोषणा EDC_H_BIST_STATUS_RDATA_A	0x50028

#घोषणा EDC_H_ECC_ERR_ADDR_A		0x50084
#घोषणा EDC_T51_BASE_ADDR		0x50800

#घोषणा EDC_T5_STRIDE (EDC_T51_BASE_ADDR - EDC_T50_BASE_ADDR)
#घोषणा EDC_T5_REG(reg, idx) (reg + EDC_T5_STRIDE * idx)

#घोषणा PL_VF_REV_A 0x4
#घोषणा PL_VF_WHOAMI_A 0x0
#घोषणा PL_VF_REVISION_A 0x8

/* रेजिस्टरs क्रम module CIM */
#घोषणा CIM_HOST_ACC_CTRL_A	0x7b50
#घोषणा CIM_HOST_ACC_DATA_A	0x7b54
#घोषणा UP_UP_DBG_LA_CFG_A	0x140
#घोषणा UP_UP_DBG_LA_DATA_A	0x144

#घोषणा HOSTBUSY_S	17
#घोषणा HOSTBUSY_V(x)	((x) << HOSTBUSY_S)
#घोषणा HOSTBUSY_F	HOSTBUSY_V(1U)

#घोषणा HOSTWRITE_S	16
#घोषणा HOSTWRITE_V(x)	((x) << HOSTWRITE_S)
#घोषणा HOSTWRITE_F	HOSTWRITE_V(1U)

#घोषणा CIM_IBQ_DBG_CFG_A 0x7b60

#घोषणा IBQDBGADDR_S    16
#घोषणा IBQDBGADDR_M    0xfffU
#घोषणा IBQDBGADDR_V(x) ((x) << IBQDBGADDR_S)
#घोषणा IBQDBGADDR_G(x) (((x) >> IBQDBGADDR_S) & IBQDBGADDR_M)

#घोषणा IBQDBGBUSY_S    1
#घोषणा IBQDBGBUSY_V(x) ((x) << IBQDBGBUSY_S)
#घोषणा IBQDBGBUSY_F    IBQDBGBUSY_V(1U)

#घोषणा IBQDBGEN_S    0
#घोषणा IBQDBGEN_V(x) ((x) << IBQDBGEN_S)
#घोषणा IBQDBGEN_F    IBQDBGEN_V(1U)

#घोषणा CIM_OBQ_DBG_CFG_A 0x7b64

#घोषणा OBQDBGADDR_S    16
#घोषणा OBQDBGADDR_M    0xfffU
#घोषणा OBQDBGADDR_V(x) ((x) << OBQDBGADDR_S)
#घोषणा OBQDBGADDR_G(x) (((x) >> OBQDBGADDR_S) & OBQDBGADDR_M)

#घोषणा OBQDBGBUSY_S    1
#घोषणा OBQDBGBUSY_V(x) ((x) << OBQDBGBUSY_S)
#घोषणा OBQDBGBUSY_F    OBQDBGBUSY_V(1U)

#घोषणा OBQDBGEN_S    0
#घोषणा OBQDBGEN_V(x) ((x) << OBQDBGEN_S)
#घोषणा OBQDBGEN_F    OBQDBGEN_V(1U)

#घोषणा CIM_IBQ_DBG_DATA_A 0x7b68
#घोषणा CIM_OBQ_DBG_DATA_A 0x7b6c
#घोषणा CIM_DEBUGCFG_A 0x7b70
#घोषणा CIM_DEBUGSTS_A 0x7b74

#घोषणा POLADBGRDPTR_S		23
#घोषणा POLADBGRDPTR_M		0x1ffU
#घोषणा POLADBGRDPTR_V(x)	((x) << POLADBGRDPTR_S)

#घोषणा POLADBGWRPTR_S		16
#घोषणा POLADBGWRPTR_M		0x1ffU
#घोषणा POLADBGWRPTR_G(x)	(((x) >> POLADBGWRPTR_S) & POLADBGWRPTR_M)

#घोषणा PILADBGRDPTR_S		14
#घोषणा PILADBGRDPTR_M		0x1ffU
#घोषणा PILADBGRDPTR_V(x)	((x) << PILADBGRDPTR_S)

#घोषणा PILADBGWRPTR_S		0
#घोषणा PILADBGWRPTR_M		0x1ffU
#घोषणा PILADBGWRPTR_G(x)	(((x) >> PILADBGWRPTR_S) & PILADBGWRPTR_M)

#घोषणा LADBGEN_S	12
#घोषणा LADBGEN_V(x)	((x) << LADBGEN_S)
#घोषणा LADBGEN_F	LADBGEN_V(1U)

#घोषणा CIM_PO_LA_DEBUGDATA_A 0x7b78
#घोषणा CIM_PI_LA_DEBUGDATA_A 0x7b7c
#घोषणा CIM_PO_LA_MADEBUGDATA_A	0x7b80
#घोषणा CIM_PI_LA_MADEBUGDATA_A	0x7b84

#घोषणा UPDBGLARDEN_S		1
#घोषणा UPDBGLARDEN_V(x)	((x) << UPDBGLARDEN_S)
#घोषणा UPDBGLARDEN_F		UPDBGLARDEN_V(1U)

#घोषणा UPDBGLAEN_S	0
#घोषणा UPDBGLAEN_V(x)	((x) << UPDBGLAEN_S)
#घोषणा UPDBGLAEN_F	UPDBGLAEN_V(1U)

#घोषणा UPDBGLARDPTR_S		2
#घोषणा UPDBGLARDPTR_M		0xfffU
#घोषणा UPDBGLARDPTR_V(x)	((x) << UPDBGLARDPTR_S)

#घोषणा UPDBGLAWRPTR_S    16
#घोषणा UPDBGLAWRPTR_M    0xfffU
#घोषणा UPDBGLAWRPTR_G(x) (((x) >> UPDBGLAWRPTR_S) & UPDBGLAWRPTR_M)

#घोषणा UPDBGLACAPTPCONLY_S	30
#घोषणा UPDBGLACAPTPCONLY_V(x)	((x) << UPDBGLACAPTPCONLY_S)
#घोषणा UPDBGLACAPTPCONLY_F	UPDBGLACAPTPCONLY_V(1U)

#घोषणा CIM_QUEUE_CONFIG_REF_A 0x7b48
#घोषणा CIM_QUEUE_CONFIG_CTRL_A 0x7b4c

#घोषणा CIMQSIZE_S    24
#घोषणा CIMQSIZE_M    0x3fU
#घोषणा CIMQSIZE_G(x) (((x) >> CIMQSIZE_S) & CIMQSIZE_M)

#घोषणा CIMQBASE_S    16
#घोषणा CIMQBASE_M    0x3fU
#घोषणा CIMQBASE_G(x) (((x) >> CIMQBASE_S) & CIMQBASE_M)

#घोषणा QUEFULLTHRSH_S    0
#घोषणा QUEFULLTHRSH_M    0x1ffU
#घोषणा QUEFULLTHRSH_G(x) (((x) >> QUEFULLTHRSH_S) & QUEFULLTHRSH_M)

#घोषणा UP_IBQ_0_RDADDR_A 0x10
#घोषणा UP_IBQ_0_SHADOW_RDADDR_A 0x280
#घोषणा UP_OBQ_0_REALADDR_A 0x104
#घोषणा UP_OBQ_0_SHADOW_REALADDR_A 0x394

#घोषणा IBQRDADDR_S    0
#घोषणा IBQRDADDR_M    0x1fffU
#घोषणा IBQRDADDR_G(x) (((x) >> IBQRDADDR_S) & IBQRDADDR_M)

#घोषणा IBQWRADDR_S    0
#घोषणा IBQWRADDR_M    0x1fffU
#घोषणा IBQWRADDR_G(x) (((x) >> IBQWRADDR_S) & IBQWRADDR_M)

#घोषणा QUERDADDR_S    0
#घोषणा QUERDADDR_M    0x7fffU
#घोषणा QUERDADDR_G(x) (((x) >> QUERDADDR_S) & QUERDADDR_M)

#घोषणा QUEREMFLITS_S    0
#घोषणा QUEREMFLITS_M    0x7ffU
#घोषणा QUEREMFLITS_G(x) (((x) >> QUEREMFLITS_S) & QUEREMFLITS_M)

#घोषणा QUEEOPCNT_S    16
#घोषणा QUEEOPCNT_M    0xfffU
#घोषणा QUEEOPCNT_G(x) (((x) >> QUEEOPCNT_S) & QUEEOPCNT_M)

#घोषणा QUESOPCNT_S    0
#घोषणा QUESOPCNT_M    0xfffU
#घोषणा QUESOPCNT_G(x) (((x) >> QUESOPCNT_S) & QUESOPCNT_M)

#घोषणा OBQSELECT_S    4
#घोषणा OBQSELECT_V(x) ((x) << OBQSELECT_S)
#घोषणा OBQSELECT_F    OBQSELECT_V(1U)

#घोषणा IBQSELECT_S    3
#घोषणा IBQSELECT_V(x) ((x) << IBQSELECT_S)
#घोषणा IBQSELECT_F    IBQSELECT_V(1U)

#घोषणा QUENUMSELECT_S    0
#घोषणा QUENUMSELECT_V(x) ((x) << QUENUMSELECT_S)

#पूर्ण_अगर /* __T4_REGS_H */
