<शैली गुरु>
/*
 * This file is part of the Chelsio T4 Ethernet driver क्रम Linux.
 *
 * Copyright (c) 2009-2016 Chelsio Communications, Inc. All rights reserved.
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

#अगर_अघोषित _T4FW_INTERFACE_H_
#घोषणा _T4FW_INTERFACE_H_

क्रमागत fw_retval अणु
	FW_SUCCESS		= 0,	/* completed successfully */
	FW_EPERM		= 1,	/* operation not permitted */
	FW_ENOENT		= 2,	/* no such file or directory */
	FW_EIO			= 5,	/* input/output error; hw bad */
	FW_ENOEXEC		= 8,	/* exec क्रमmat error; inv microcode */
	FW_EAGAIN		= 11,	/* try again */
	FW_ENOMEM		= 12,	/* out of memory */
	FW_EFAULT		= 14,	/* bad address; fw bad */
	FW_EBUSY		= 16,	/* resource busy */
	FW_EEXIST		= 17,	/* file exists */
	FW_ENODEV		= 19,	/* no such device */
	FW_EINVAL		= 22,	/* invalid argument */
	FW_ENOSPC		= 28,	/* no space left on device */
	FW_ENOSYS		= 38,	/* functionality not implemented */
	FW_ENODATA		= 61,	/* no data available */
	FW_EPROTO		= 71,	/* protocol error */
	FW_EADDRINUSE		= 98,	/* address alपढ़ोy in use */
	FW_EADDRNOTAVAIL	= 99,	/* cannot asचिन्हित requested address */
	FW_ENETDOWN		= 100,	/* network is करोwn */
	FW_ENETUNREACH		= 101,	/* network is unreachable */
	FW_ENOBUFS		= 105,	/* no buffer space available */
	FW_ETIMEDOUT		= 110,	/* समयout */
	FW_EINPROGRESS		= 115,	/* fw पूर्णांकernal */
	FW_SCSI_ABORT_REQUESTED	= 128,	/* */
	FW_SCSI_ABORT_TIMEDOUT	= 129,	/* */
	FW_SCSI_ABORTED		= 130,	/* */
	FW_SCSI_CLOSE_REQUESTED	= 131,	/* */
	FW_ERR_LINK_DOWN	= 132,	/* */
	FW_RDEV_NOT_READY	= 133,	/* */
	FW_ERR_RDEV_LOST	= 134,	/* */
	FW_ERR_RDEV_LOGO	= 135,	/* */
	FW_FCOE_NO_XCHG		= 136,	/* */
	FW_SCSI_RSP_ERR		= 137,	/* */
	FW_ERR_RDEV_IMPL_LOGO	= 138,	/* */
	FW_SCSI_UNDER_FLOW_ERR  = 139,	/* */
	FW_SCSI_OVER_FLOW_ERR   = 140,	/* */
	FW_SCSI_DDP_ERR		= 141,	/* DDP error*/
	FW_SCSI_TASK_ERR	= 142,	/* No SCSI tasks available */
पूर्ण;

#घोषणा FW_T4VF_SGE_BASE_ADDR      0x0000
#घोषणा FW_T4VF_MPS_BASE_ADDR      0x0100
#घोषणा FW_T4VF_PL_BASE_ADDR       0x0200
#घोषणा FW_T4VF_MBDATA_BASE_ADDR   0x0240
#घोषणा FW_T4VF_CIM_BASE_ADDR      0x0300

क्रमागत fw_wr_opcodes अणु
	FW_FILTER_WR                   = 0x02,
	FW_ULPTX_WR                    = 0x04,
	FW_TP_WR                       = 0x05,
	FW_ETH_TX_PKT_WR               = 0x08,
	FW_ETH_TX_EO_WR                = 0x1c,
	FW_OFLD_CONNECTION_WR          = 0x2f,
	FW_FLOWC_WR                    = 0x0a,
	FW_OFLD_TX_DATA_WR             = 0x0b,
	FW_CMD_WR                      = 0x10,
	FW_ETH_TX_PKT_VM_WR            = 0x11,
	FW_RI_RES_WR                   = 0x0c,
	FW_RI_INIT_WR                  = 0x0d,
	FW_RI_RDMA_WRITE_WR            = 0x14,
	FW_RI_SEND_WR                  = 0x15,
	FW_RI_RDMA_READ_WR             = 0x16,
	FW_RI_RECV_WR                  = 0x17,
	FW_RI_BIND_MW_WR               = 0x18,
	FW_RI_FR_NSMR_WR               = 0x19,
	FW_RI_FR_NSMR_TPTE_WR	       = 0x20,
	FW_RI_RDMA_WRITE_CMPL_WR       = 0x21,
	FW_RI_INV_LSTAG_WR             = 0x1a,
	FW_ISCSI_TX_DATA_WR	       = 0x45,
	FW_PTP_TX_PKT_WR               = 0x46,
	FW_TLSTX_DATA_WR	       = 0x68,
	FW_CRYPTO_LOOKASIDE_WR         = 0X6d,
	FW_LASTC2E_WR                  = 0x70,
	FW_FILTER2_WR		       = 0x77
पूर्ण;

काष्ठा fw_wr_hdr अणु
	__be32 hi;
	__be32 lo;
पूर्ण;

/* work request opcode (hi) */
#घोषणा FW_WR_OP_S	24
#घोषणा FW_WR_OP_M      0xff
#घोषणा FW_WR_OP_V(x)   ((x) << FW_WR_OP_S)
#घोषणा FW_WR_OP_G(x)   (((x) >> FW_WR_OP_S) & FW_WR_OP_M)

/* atomic flag (hi) - firmware encapsulates CPLs in CPL_BARRIER */
#घोषणा FW_WR_ATOMIC_S		23
#घोषणा FW_WR_ATOMIC_V(x)	((x) << FW_WR_ATOMIC_S)

/* flush flag (hi) - firmware flushes flushable work request buffered
 * in the flow context.
 */
#घोषणा FW_WR_FLUSH_S     22
#घोषणा FW_WR_FLUSH_V(x)  ((x) << FW_WR_FLUSH_S)

/* completion flag (hi) - firmware generates a cpl_fw6_ack */
#घोषणा FW_WR_COMPL_S     21
#घोषणा FW_WR_COMPL_V(x)  ((x) << FW_WR_COMPL_S)
#घोषणा FW_WR_COMPL_F     FW_WR_COMPL_V(1U)

/* work request immediate data length (hi) */
#घोषणा FW_WR_IMMDLEN_S 0
#घोषणा FW_WR_IMMDLEN_M 0xff
#घोषणा FW_WR_IMMDLEN_V(x)      ((x) << FW_WR_IMMDLEN_S)

/* egress queue status update to associated ingress queue entry (lo) */
#घोषणा FW_WR_EQUIQ_S           31
#घोषणा FW_WR_EQUIQ_V(x)        ((x) << FW_WR_EQUIQ_S)
#घोषणा FW_WR_EQUIQ_F           FW_WR_EQUIQ_V(1U)

/* egress queue status update to egress queue status entry (lo) */
#घोषणा FW_WR_EQUEQ_S           30
#घोषणा FW_WR_EQUEQ_V(x)        ((x) << FW_WR_EQUEQ_S)
#घोषणा FW_WR_EQUEQ_F           FW_WR_EQUEQ_V(1U)

/* flow context identअगरier (lo) */
#घोषणा FW_WR_FLOWID_S          8
#घोषणा FW_WR_FLOWID_V(x)       ((x) << FW_WR_FLOWID_S)

/* length in units of 16-bytes (lo) */
#घोषणा FW_WR_LEN16_S           0
#घोषणा FW_WR_LEN16_V(x)        ((x) << FW_WR_LEN16_S)

#घोषणा HW_TPL_FR_MT_PR_IV_P_FC         0X32B
#घोषणा HW_TPL_FR_MT_PR_OV_P_FC         0X327

/* filter wr reply code in cookie in CPL_SET_TCB_RPL */
क्रमागत fw_filter_wr_cookie अणु
	FW_FILTER_WR_SUCCESS,
	FW_FILTER_WR_FLT_ADDED,
	FW_FILTER_WR_FLT_DELETED,
	FW_FILTER_WR_SMT_TBL_FULL,
	FW_FILTER_WR_EINVAL,
पूर्ण;

काष्ठा fw_filter_wr अणु
	__be32 op_pkd;
	__be32 len16_pkd;
	__be64 r3;
	__be32 tid_to_iq;
	__be32 del_filter_to_l2tix;
	__be16 ethtype;
	__be16 ethtypem;
	__u8   frag_to_ovlan_vldm;
	__u8   smac_sel;
	__be16 rx_chan_rx_rpl_iq;
	__be32 maci_to_matchtypem;
	__u8   ptcl;
	__u8   ptclm;
	__u8   ttyp;
	__u8   ttypm;
	__be16 ivlan;
	__be16 ivlanm;
	__be16 ovlan;
	__be16 ovlanm;
	__u8   lip[16];
	__u8   lipm[16];
	__u8   fip[16];
	__u8   fipm[16];
	__be16 lp;
	__be16 lpm;
	__be16 fp;
	__be16 fpm;
	__be16 r7;
	__u8   sma[6];
पूर्ण;

काष्ठा fw_filter2_wr अणु
	__be32 op_pkd;
	__be32 len16_pkd;
	__be64 r3;
	__be32 tid_to_iq;
	__be32 del_filter_to_l2tix;
	__be16 ethtype;
	__be16 ethtypem;
	__u8   frag_to_ovlan_vldm;
	__u8   smac_sel;
	__be16 rx_chan_rx_rpl_iq;
	__be32 maci_to_matchtypem;
	__u8   ptcl;
	__u8   ptclm;
	__u8   ttyp;
	__u8   ttypm;
	__be16 ivlan;
	__be16 ivlanm;
	__be16 ovlan;
	__be16 ovlanm;
	__u8   lip[16];
	__u8   lipm[16];
	__u8   fip[16];
	__u8   fipm[16];
	__be16 lp;
	__be16 lpm;
	__be16 fp;
	__be16 fpm;
	__be16 r7;
	__u8   sma[6];
	__be16 r8;
	__u8   filter_type_swapmac;
	__u8   naपंचांगode_to_ulp_type;
	__be16 newlport;
	__be16 newfport;
	__u8   newlip[16];
	__u8   newfip[16];
	__be32 natseqcheck;
	__be32 r9;
	__be64 r10;
	__be64 r11;
	__be64 r12;
	__be64 r13;
पूर्ण;

#घोषणा FW_FILTER_WR_TID_S      12
#घोषणा FW_FILTER_WR_TID_M      0xfffff
#घोषणा FW_FILTER_WR_TID_V(x)   ((x) << FW_FILTER_WR_TID_S)
#घोषणा FW_FILTER_WR_TID_G(x)   \
	(((x) >> FW_FILTER_WR_TID_S) & FW_FILTER_WR_TID_M)

#घोषणा FW_FILTER_WR_RQTYPE_S           11
#घोषणा FW_FILTER_WR_RQTYPE_M           0x1
#घोषणा FW_FILTER_WR_RQTYPE_V(x)        ((x) << FW_FILTER_WR_RQTYPE_S)
#घोषणा FW_FILTER_WR_RQTYPE_G(x)        \
	(((x) >> FW_FILTER_WR_RQTYPE_S) & FW_FILTER_WR_RQTYPE_M)
#घोषणा FW_FILTER_WR_RQTYPE_F   FW_FILTER_WR_RQTYPE_V(1U)

#घोषणा FW_FILTER_WR_NOREPLY_S          10
#घोषणा FW_FILTER_WR_NOREPLY_M          0x1
#घोषणा FW_FILTER_WR_NOREPLY_V(x)       ((x) << FW_FILTER_WR_NOREPLY_S)
#घोषणा FW_FILTER_WR_NOREPLY_G(x)       \
	(((x) >> FW_FILTER_WR_NOREPLY_S) & FW_FILTER_WR_NOREPLY_M)
#घोषणा FW_FILTER_WR_NOREPLY_F  FW_FILTER_WR_NOREPLY_V(1U)

#घोषणा FW_FILTER_WR_IQ_S       0
#घोषणा FW_FILTER_WR_IQ_M       0x3ff
#घोषणा FW_FILTER_WR_IQ_V(x)    ((x) << FW_FILTER_WR_IQ_S)
#घोषणा FW_FILTER_WR_IQ_G(x)    \
	(((x) >> FW_FILTER_WR_IQ_S) & FW_FILTER_WR_IQ_M)

#घोषणा FW_FILTER_WR_DEL_FILTER_S       31
#घोषणा FW_FILTER_WR_DEL_FILTER_M       0x1
#घोषणा FW_FILTER_WR_DEL_FILTER_V(x)    ((x) << FW_FILTER_WR_DEL_FILTER_S)
#घोषणा FW_FILTER_WR_DEL_FILTER_G(x)    \
	(((x) >> FW_FILTER_WR_DEL_FILTER_S) & FW_FILTER_WR_DEL_FILTER_M)
#घोषणा FW_FILTER_WR_DEL_FILTER_F       FW_FILTER_WR_DEL_FILTER_V(1U)

#घोषणा FW_FILTER_WR_RPTTID_S           25
#घोषणा FW_FILTER_WR_RPTTID_M           0x1
#घोषणा FW_FILTER_WR_RPTTID_V(x)        ((x) << FW_FILTER_WR_RPTTID_S)
#घोषणा FW_FILTER_WR_RPTTID_G(x)        \
	(((x) >> FW_FILTER_WR_RPTTID_S) & FW_FILTER_WR_RPTTID_M)
#घोषणा FW_FILTER_WR_RPTTID_F   FW_FILTER_WR_RPTTID_V(1U)

#घोषणा FW_FILTER_WR_DROP_S     24
#घोषणा FW_FILTER_WR_DROP_M     0x1
#घोषणा FW_FILTER_WR_DROP_V(x)  ((x) << FW_FILTER_WR_DROP_S)
#घोषणा FW_FILTER_WR_DROP_G(x)  \
	(((x) >> FW_FILTER_WR_DROP_S) & FW_FILTER_WR_DROP_M)
#घोषणा FW_FILTER_WR_DROP_F     FW_FILTER_WR_DROP_V(1U)

#घोषणा FW_FILTER_WR_सूचीSTEER_S         23
#घोषणा FW_FILTER_WR_सूचीSTEER_M         0x1
#घोषणा FW_FILTER_WR_सूचीSTEER_V(x)      ((x) << FW_FILTER_WR_सूचीSTEER_S)
#घोषणा FW_FILTER_WR_सूचीSTEER_G(x)      \
	(((x) >> FW_FILTER_WR_सूचीSTEER_S) & FW_FILTER_WR_सूचीSTEER_M)
#घोषणा FW_FILTER_WR_सूचीSTEER_F FW_FILTER_WR_सूचीSTEER_V(1U)

#घोषणा FW_FILTER_WR_MASKHASH_S         22
#घोषणा FW_FILTER_WR_MASKHASH_M         0x1
#घोषणा FW_FILTER_WR_MASKHASH_V(x)      ((x) << FW_FILTER_WR_MASKHASH_S)
#घोषणा FW_FILTER_WR_MASKHASH_G(x)      \
	(((x) >> FW_FILTER_WR_MASKHASH_S) & FW_FILTER_WR_MASKHASH_M)
#घोषणा FW_FILTER_WR_MASKHASH_F FW_FILTER_WR_MASKHASH_V(1U)

#घोषणा FW_FILTER_WR_सूचीSTEERHASH_S     21
#घोषणा FW_FILTER_WR_सूचीSTEERHASH_M     0x1
#घोषणा FW_FILTER_WR_सूचीSTEERHASH_V(x)  ((x) << FW_FILTER_WR_सूचीSTEERHASH_S)
#घोषणा FW_FILTER_WR_सूचीSTEERHASH_G(x)  \
	(((x) >> FW_FILTER_WR_सूचीSTEERHASH_S) & FW_FILTER_WR_सूचीSTEERHASH_M)
#घोषणा FW_FILTER_WR_सूचीSTEERHASH_F     FW_FILTER_WR_सूचीSTEERHASH_V(1U)

#घोषणा FW_FILTER_WR_LPBK_S     20
#घोषणा FW_FILTER_WR_LPBK_M     0x1
#घोषणा FW_FILTER_WR_LPBK_V(x)  ((x) << FW_FILTER_WR_LPBK_S)
#घोषणा FW_FILTER_WR_LPBK_G(x)  \
	(((x) >> FW_FILTER_WR_LPBK_S) & FW_FILTER_WR_LPBK_M)
#घोषणा FW_FILTER_WR_LPBK_F     FW_FILTER_WR_LPBK_V(1U)

#घोषणा FW_FILTER_WR_DMAC_S     19
#घोषणा FW_FILTER_WR_DMAC_M     0x1
#घोषणा FW_FILTER_WR_DMAC_V(x)  ((x) << FW_FILTER_WR_DMAC_S)
#घोषणा FW_FILTER_WR_DMAC_G(x)  \
	(((x) >> FW_FILTER_WR_DMAC_S) & FW_FILTER_WR_DMAC_M)
#घोषणा FW_FILTER_WR_DMAC_F     FW_FILTER_WR_DMAC_V(1U)

#घोषणा FW_FILTER_WR_SMAC_S     18
#घोषणा FW_FILTER_WR_SMAC_M     0x1
#घोषणा FW_FILTER_WR_SMAC_V(x)  ((x) << FW_FILTER_WR_SMAC_S)
#घोषणा FW_FILTER_WR_SMAC_G(x)  \
	(((x) >> FW_FILTER_WR_SMAC_S) & FW_FILTER_WR_SMAC_M)
#घोषणा FW_FILTER_WR_SMAC_F     FW_FILTER_WR_SMAC_V(1U)

#घोषणा FW_FILTER_WR_INSVLAN_S          17
#घोषणा FW_FILTER_WR_INSVLAN_M          0x1
#घोषणा FW_FILTER_WR_INSVLAN_V(x)       ((x) << FW_FILTER_WR_INSVLAN_S)
#घोषणा FW_FILTER_WR_INSVLAN_G(x)       \
	(((x) >> FW_FILTER_WR_INSVLAN_S) & FW_FILTER_WR_INSVLAN_M)
#घोषणा FW_FILTER_WR_INSVLAN_F  FW_FILTER_WR_INSVLAN_V(1U)

#घोषणा FW_FILTER_WR_RMVLAN_S           16
#घोषणा FW_FILTER_WR_RMVLAN_M           0x1
#घोषणा FW_FILTER_WR_RMVLAN_V(x)        ((x) << FW_FILTER_WR_RMVLAN_S)
#घोषणा FW_FILTER_WR_RMVLAN_G(x)        \
	(((x) >> FW_FILTER_WR_RMVLAN_S) & FW_FILTER_WR_RMVLAN_M)
#घोषणा FW_FILTER_WR_RMVLAN_F   FW_FILTER_WR_RMVLAN_V(1U)

#घोषणा FW_FILTER_WR_HITCNTS_S          15
#घोषणा FW_FILTER_WR_HITCNTS_M          0x1
#घोषणा FW_FILTER_WR_HITCNTS_V(x)       ((x) << FW_FILTER_WR_HITCNTS_S)
#घोषणा FW_FILTER_WR_HITCNTS_G(x)       \
	(((x) >> FW_FILTER_WR_HITCNTS_S) & FW_FILTER_WR_HITCNTS_M)
#घोषणा FW_FILTER_WR_HITCNTS_F  FW_FILTER_WR_HITCNTS_V(1U)

#घोषणा FW_FILTER_WR_TXCHAN_S           13
#घोषणा FW_FILTER_WR_TXCHAN_M           0x3
#घोषणा FW_FILTER_WR_TXCHAN_V(x)        ((x) << FW_FILTER_WR_TXCHAN_S)
#घोषणा FW_FILTER_WR_TXCHAN_G(x)        \
	(((x) >> FW_FILTER_WR_TXCHAN_S) & FW_FILTER_WR_TXCHAN_M)

#घोषणा FW_FILTER_WR_PRIO_S     12
#घोषणा FW_FILTER_WR_PRIO_M     0x1
#घोषणा FW_FILTER_WR_PRIO_V(x)  ((x) << FW_FILTER_WR_PRIO_S)
#घोषणा FW_FILTER_WR_PRIO_G(x)  \
	(((x) >> FW_FILTER_WR_PRIO_S) & FW_FILTER_WR_PRIO_M)
#घोषणा FW_FILTER_WR_PRIO_F     FW_FILTER_WR_PRIO_V(1U)

#घोषणा FW_FILTER_WR_L2TIX_S    0
#घोषणा FW_FILTER_WR_L2TIX_M    0xfff
#घोषणा FW_FILTER_WR_L2TIX_V(x) ((x) << FW_FILTER_WR_L2TIX_S)
#घोषणा FW_FILTER_WR_L2TIX_G(x) \
	(((x) >> FW_FILTER_WR_L2TIX_S) & FW_FILTER_WR_L2TIX_M)

#घोषणा FW_FILTER_WR_FRAG_S     7
#घोषणा FW_FILTER_WR_FRAG_M     0x1
#घोषणा FW_FILTER_WR_FRAG_V(x)  ((x) << FW_FILTER_WR_FRAG_S)
#घोषणा FW_FILTER_WR_FRAG_G(x)  \
	(((x) >> FW_FILTER_WR_FRAG_S) & FW_FILTER_WR_FRAG_M)
#घोषणा FW_FILTER_WR_FRAG_F     FW_FILTER_WR_FRAG_V(1U)

#घोषणा FW_FILTER_WR_FRAGM_S    6
#घोषणा FW_FILTER_WR_FRAGM_M    0x1
#घोषणा FW_FILTER_WR_FRAGM_V(x) ((x) << FW_FILTER_WR_FRAGM_S)
#घोषणा FW_FILTER_WR_FRAGM_G(x) \
	(((x) >> FW_FILTER_WR_FRAGM_S) & FW_FILTER_WR_FRAGM_M)
#घोषणा FW_FILTER_WR_FRAGM_F    FW_FILTER_WR_FRAGM_V(1U)

#घोषणा FW_FILTER_WR_IVLAN_VLD_S        5
#घोषणा FW_FILTER_WR_IVLAN_VLD_M        0x1
#घोषणा FW_FILTER_WR_IVLAN_VLD_V(x)     ((x) << FW_FILTER_WR_IVLAN_VLD_S)
#घोषणा FW_FILTER_WR_IVLAN_VLD_G(x)     \
	(((x) >> FW_FILTER_WR_IVLAN_VLD_S) & FW_FILTER_WR_IVLAN_VLD_M)
#घोषणा FW_FILTER_WR_IVLAN_VLD_F        FW_FILTER_WR_IVLAN_VLD_V(1U)

#घोषणा FW_FILTER_WR_OVLAN_VLD_S        4
#घोषणा FW_FILTER_WR_OVLAN_VLD_M        0x1
#घोषणा FW_FILTER_WR_OVLAN_VLD_V(x)     ((x) << FW_FILTER_WR_OVLAN_VLD_S)
#घोषणा FW_FILTER_WR_OVLAN_VLD_G(x)     \
	(((x) >> FW_FILTER_WR_OVLAN_VLD_S) & FW_FILTER_WR_OVLAN_VLD_M)
#घोषणा FW_FILTER_WR_OVLAN_VLD_F        FW_FILTER_WR_OVLAN_VLD_V(1U)

#घोषणा FW_FILTER_WR_IVLAN_VLDM_S       3
#घोषणा FW_FILTER_WR_IVLAN_VLDM_M       0x1
#घोषणा FW_FILTER_WR_IVLAN_VLDM_V(x)    ((x) << FW_FILTER_WR_IVLAN_VLDM_S)
#घोषणा FW_FILTER_WR_IVLAN_VLDM_G(x)    \
	(((x) >> FW_FILTER_WR_IVLAN_VLDM_S) & FW_FILTER_WR_IVLAN_VLDM_M)
#घोषणा FW_FILTER_WR_IVLAN_VLDM_F       FW_FILTER_WR_IVLAN_VLDM_V(1U)

#घोषणा FW_FILTER_WR_OVLAN_VLDM_S       2
#घोषणा FW_FILTER_WR_OVLAN_VLDM_M       0x1
#घोषणा FW_FILTER_WR_OVLAN_VLDM_V(x)    ((x) << FW_FILTER_WR_OVLAN_VLDM_S)
#घोषणा FW_FILTER_WR_OVLAN_VLDM_G(x)    \
	(((x) >> FW_FILTER_WR_OVLAN_VLDM_S) & FW_FILTER_WR_OVLAN_VLDM_M)
#घोषणा FW_FILTER_WR_OVLAN_VLDM_F       FW_FILTER_WR_OVLAN_VLDM_V(1U)

#घोषणा FW_FILTER_WR_RX_CHAN_S          15
#घोषणा FW_FILTER_WR_RX_CHAN_M          0x1
#घोषणा FW_FILTER_WR_RX_CHAN_V(x)       ((x) << FW_FILTER_WR_RX_CHAN_S)
#घोषणा FW_FILTER_WR_RX_CHAN_G(x)       \
	(((x) >> FW_FILTER_WR_RX_CHAN_S) & FW_FILTER_WR_RX_CHAN_M)
#घोषणा FW_FILTER_WR_RX_CHAN_F  FW_FILTER_WR_RX_CHAN_V(1U)

#घोषणा FW_FILTER_WR_RX_RPL_IQ_S        0
#घोषणा FW_FILTER_WR_RX_RPL_IQ_M        0x3ff
#घोषणा FW_FILTER_WR_RX_RPL_IQ_V(x)     ((x) << FW_FILTER_WR_RX_RPL_IQ_S)
#घोषणा FW_FILTER_WR_RX_RPL_IQ_G(x)     \
	(((x) >> FW_FILTER_WR_RX_RPL_IQ_S) & FW_FILTER_WR_RX_RPL_IQ_M)

#घोषणा FW_FILTER2_WR_FILTER_TYPE_S	1
#घोषणा FW_FILTER2_WR_FILTER_TYPE_M	0x1
#घोषणा FW_FILTER2_WR_FILTER_TYPE_V(x)	((x) << FW_FILTER2_WR_FILTER_TYPE_S)
#घोषणा FW_FILTER2_WR_FILTER_TYPE_G(x)  \
	(((x) >> FW_FILTER2_WR_FILTER_TYPE_S) & FW_FILTER2_WR_FILTER_TYPE_M)
#घोषणा FW_FILTER2_WR_FILTER_TYPE_F	FW_FILTER2_WR_FILTER_TYPE_V(1U)

#घोषणा FW_FILTER2_WR_NATMODE_S		5
#घोषणा FW_FILTER2_WR_NATMODE_M		0x7
#घोषणा FW_FILTER2_WR_NATMODE_V(x)	((x) << FW_FILTER2_WR_NATMODE_S)
#घोषणा FW_FILTER2_WR_NATMODE_G(x)      \
	(((x) >> FW_FILTER2_WR_NATMODE_S) & FW_FILTER2_WR_NATMODE_M)

#घोषणा FW_FILTER2_WR_NATFLAGCHECK_S	4
#घोषणा FW_FILTER2_WR_NATFLAGCHECK_M	0x1
#घोषणा FW_FILTER2_WR_NATFLAGCHECK_V(x)	((x) << FW_FILTER2_WR_NATFLAGCHECK_S)
#घोषणा FW_FILTER2_WR_NATFLAGCHECK_G(x) \
	(((x) >> FW_FILTER2_WR_NATFLAGCHECK_S) & FW_FILTER2_WR_NATFLAGCHECK_M)
#घोषणा FW_FILTER2_WR_NATFLAGCHECK_F	FW_FILTER2_WR_NATFLAGCHECK_V(1U)

#घोषणा FW_FILTER2_WR_ULP_TYPE_S	0
#घोषणा FW_FILTER2_WR_ULP_TYPE_M	0xf
#घोषणा FW_FILTER2_WR_ULP_TYPE_V(x)	((x) << FW_FILTER2_WR_ULP_TYPE_S)
#घोषणा FW_FILTER2_WR_ULP_TYPE_G(x)     \
	(((x) >> FW_FILTER2_WR_ULP_TYPE_S) & FW_FILTER2_WR_ULP_TYPE_M)

#घोषणा FW_FILTER_WR_MACI_S     23
#घोषणा FW_FILTER_WR_MACI_M     0x1ff
#घोषणा FW_FILTER_WR_MACI_V(x)  ((x) << FW_FILTER_WR_MACI_S)
#घोषणा FW_FILTER_WR_MACI_G(x)  \
	(((x) >> FW_FILTER_WR_MACI_S) & FW_FILTER_WR_MACI_M)

#घोषणा FW_FILTER_WR_MACIM_S    14
#घोषणा FW_FILTER_WR_MACIM_M    0x1ff
#घोषणा FW_FILTER_WR_MACIM_V(x) ((x) << FW_FILTER_WR_MACIM_S)
#घोषणा FW_FILTER_WR_MACIM_G(x) \
	(((x) >> FW_FILTER_WR_MACIM_S) & FW_FILTER_WR_MACIM_M)

#घोषणा FW_FILTER_WR_FCOE_S     13
#घोषणा FW_FILTER_WR_FCOE_M     0x1
#घोषणा FW_FILTER_WR_FCOE_V(x)  ((x) << FW_FILTER_WR_FCOE_S)
#घोषणा FW_FILTER_WR_FCOE_G(x)  \
	(((x) >> FW_FILTER_WR_FCOE_S) & FW_FILTER_WR_FCOE_M)
#घोषणा FW_FILTER_WR_FCOE_F     FW_FILTER_WR_FCOE_V(1U)

#घोषणा FW_FILTER_WR_FCOEM_S    12
#घोषणा FW_FILTER_WR_FCOEM_M    0x1
#घोषणा FW_FILTER_WR_FCOEM_V(x) ((x) << FW_FILTER_WR_FCOEM_S)
#घोषणा FW_FILTER_WR_FCOEM_G(x) \
	(((x) >> FW_FILTER_WR_FCOEM_S) & FW_FILTER_WR_FCOEM_M)
#घोषणा FW_FILTER_WR_FCOEM_F    FW_FILTER_WR_FCOEM_V(1U)

#घोषणा FW_FILTER_WR_PORT_S     9
#घोषणा FW_FILTER_WR_PORT_M     0x7
#घोषणा FW_FILTER_WR_PORT_V(x)  ((x) << FW_FILTER_WR_PORT_S)
#घोषणा FW_FILTER_WR_PORT_G(x)  \
	(((x) >> FW_FILTER_WR_PORT_S) & FW_FILTER_WR_PORT_M)

#घोषणा FW_FILTER_WR_PORTM_S    6
#घोषणा FW_FILTER_WR_PORTM_M    0x7
#घोषणा FW_FILTER_WR_PORTM_V(x) ((x) << FW_FILTER_WR_PORTM_S)
#घोषणा FW_FILTER_WR_PORTM_G(x) \
	(((x) >> FW_FILTER_WR_PORTM_S) & FW_FILTER_WR_PORTM_M)

#घोषणा FW_FILTER_WR_MATCHTYPE_S        3
#घोषणा FW_FILTER_WR_MATCHTYPE_M        0x7
#घोषणा FW_FILTER_WR_MATCHTYPE_V(x)     ((x) << FW_FILTER_WR_MATCHTYPE_S)
#घोषणा FW_FILTER_WR_MATCHTYPE_G(x)     \
	(((x) >> FW_FILTER_WR_MATCHTYPE_S) & FW_FILTER_WR_MATCHTYPE_M)

#घोषणा FW_FILTER_WR_MATCHTYPEM_S       0
#घोषणा FW_FILTER_WR_MATCHTYPEM_M       0x7
#घोषणा FW_FILTER_WR_MATCHTYPEM_V(x)    ((x) << FW_FILTER_WR_MATCHTYPEM_S)
#घोषणा FW_FILTER_WR_MATCHTYPEM_G(x)    \
	(((x) >> FW_FILTER_WR_MATCHTYPEM_S) & FW_FILTER_WR_MATCHTYPEM_M)

काष्ठा fw_ulptx_wr अणु
	__be32 op_to_compl;
	__be32 flowid_len16;
	u64 cookie;
पूर्ण;

#घोषणा FW_ULPTX_WR_DATA_S      28
#घोषणा FW_ULPTX_WR_DATA_M      0x1
#घोषणा FW_ULPTX_WR_DATA_V(x)   ((x) << FW_ULPTX_WR_DATA_S)
#घोषणा FW_ULPTX_WR_DATA_G(x)   \
	(((x) >> FW_ULPTX_WR_DATA_S) & FW_ULPTX_WR_DATA_M)
#घोषणा FW_ULPTX_WR_DATA_F      FW_ULPTX_WR_DATA_V(1U)

काष्ठा fw_tp_wr अणु
	__be32 op_to_immdlen;
	__be32 flowid_len16;
	u64 cookie;
पूर्ण;

काष्ठा fw_eth_tx_pkt_wr अणु
	__be32 op_immdlen;
	__be32 equiq_to_len16;
	__be64 r3;
पूर्ण;

क्रमागत fw_eth_tx_eo_type अणु
	FW_ETH_TX_EO_TYPE_UDPSEG = 0,
	FW_ETH_TX_EO_TYPE_TCPSEG,
पूर्ण;

काष्ठा fw_eth_tx_eo_wr अणु
	__be32 op_immdlen;
	__be32 equiq_to_len16;
	__be64 r3;
	जोड़ fw_eth_tx_eo अणु
		काष्ठा fw_eth_tx_eo_udpseg अणु
			__u8   type;
			__u8   ethlen;
			__be16 iplen;
			__u8   udplen;
			__u8   rtplen;
			__be16 r4;
			__be16 mss;
			__be16 schedpktsize;
			__be32 plen;
		पूर्ण udpseg;
		काष्ठा fw_eth_tx_eo_tcpseg अणु
			__u8   type;
			__u8   ethlen;
			__be16 iplen;
			__u8   tcplen;
			__u8   tsclk_tsoff;
			__be16 r4;
			__be16 mss;
			__be16 r5;
			__be32 plen;
		पूर्ण tcpseg;
	पूर्ण u;
पूर्ण;

#घोषणा FW_ETH_TX_EO_WR_IMMDLEN_S	0
#घोषणा FW_ETH_TX_EO_WR_IMMDLEN_M	0x1ff
#घोषणा FW_ETH_TX_EO_WR_IMMDLEN_V(x)	((x) << FW_ETH_TX_EO_WR_IMMDLEN_S)
#घोषणा FW_ETH_TX_EO_WR_IMMDLEN_G(x)	\
	(((x) >> FW_ETH_TX_EO_WR_IMMDLEN_S) & FW_ETH_TX_EO_WR_IMMDLEN_M)

काष्ठा fw_ofld_connection_wr अणु
	__be32 op_compl;
	__be32 len16_pkd;
	__u64  cookie;
	__be64 r2;
	__be64 r3;
	काष्ठा fw_ofld_connection_le अणु
		__be32 version_cpl;
		__be32 filter;
		__be32 r1;
		__be16 lport;
		__be16 pport;
		जोड़ fw_ofld_connection_leip अणु
			काष्ठा fw_ofld_connection_le_ipv4 अणु
				__be32 pip;
				__be32 lip;
				__be64 r0;
				__be64 r1;
				__be64 r2;
			पूर्ण ipv4;
			काष्ठा fw_ofld_connection_le_ipv6 अणु
				__be64 pip_hi;
				__be64 pip_lo;
				__be64 lip_hi;
				__be64 lip_lo;
			पूर्ण ipv6;
		पूर्ण u;
	पूर्ण le;
	काष्ठा fw_ofld_connection_tcb अणु
		__be32 t_state_to_astid;
		__be16 cplrxdataack_cplpassacceptrpl;
		__be16 rcv_adv;
		__be32 rcv_nxt;
		__be32 tx_max;
		__be64 opt0;
		__be32 opt2;
		__be32 r1;
		__be64 r2;
		__be64 r3;
	पूर्ण tcb;
पूर्ण;

#घोषणा FW_OFLD_CONNECTION_WR_VERSION_S                31
#घोषणा FW_OFLD_CONNECTION_WR_VERSION_M                0x1
#घोषणा FW_OFLD_CONNECTION_WR_VERSION_V(x)     \
	((x) << FW_OFLD_CONNECTION_WR_VERSION_S)
#घोषणा FW_OFLD_CONNECTION_WR_VERSION_G(x)     \
	(((x) >> FW_OFLD_CONNECTION_WR_VERSION_S) & \
	FW_OFLD_CONNECTION_WR_VERSION_M)
#घोषणा FW_OFLD_CONNECTION_WR_VERSION_F        \
	FW_OFLD_CONNECTION_WR_VERSION_V(1U)

#घोषणा FW_OFLD_CONNECTION_WR_CPL_S    30
#घोषणा FW_OFLD_CONNECTION_WR_CPL_M    0x1
#घोषणा FW_OFLD_CONNECTION_WR_CPL_V(x) ((x) << FW_OFLD_CONNECTION_WR_CPL_S)
#घोषणा FW_OFLD_CONNECTION_WR_CPL_G(x) \
	(((x) >> FW_OFLD_CONNECTION_WR_CPL_S) & FW_OFLD_CONNECTION_WR_CPL_M)
#घोषणा FW_OFLD_CONNECTION_WR_CPL_F    FW_OFLD_CONNECTION_WR_CPL_V(1U)

#घोषणा FW_OFLD_CONNECTION_WR_T_STATE_S                28
#घोषणा FW_OFLD_CONNECTION_WR_T_STATE_M                0xf
#घोषणा FW_OFLD_CONNECTION_WR_T_STATE_V(x)     \
	((x) << FW_OFLD_CONNECTION_WR_T_STATE_S)
#घोषणा FW_OFLD_CONNECTION_WR_T_STATE_G(x)     \
	(((x) >> FW_OFLD_CONNECTION_WR_T_STATE_S) & \
	FW_OFLD_CONNECTION_WR_T_STATE_M)

#घोषणा FW_OFLD_CONNECTION_WR_RCV_SCALE_S      24
#घोषणा FW_OFLD_CONNECTION_WR_RCV_SCALE_M      0xf
#घोषणा FW_OFLD_CONNECTION_WR_RCV_SCALE_V(x)   \
	((x) << FW_OFLD_CONNECTION_WR_RCV_SCALE_S)
#घोषणा FW_OFLD_CONNECTION_WR_RCV_SCALE_G(x)   \
	(((x) >> FW_OFLD_CONNECTION_WR_RCV_SCALE_S) & \
	FW_OFLD_CONNECTION_WR_RCV_SCALE_M)

#घोषणा FW_OFLD_CONNECTION_WR_ASTID_S          0
#घोषणा FW_OFLD_CONNECTION_WR_ASTID_M          0xffffff
#घोषणा FW_OFLD_CONNECTION_WR_ASTID_V(x)       \
	((x) << FW_OFLD_CONNECTION_WR_ASTID_S)
#घोषणा FW_OFLD_CONNECTION_WR_ASTID_G(x)       \
	(((x) >> FW_OFLD_CONNECTION_WR_ASTID_S) & FW_OFLD_CONNECTION_WR_ASTID_M)

#घोषणा FW_OFLD_CONNECTION_WR_CPLRXDATAACK_S   15
#घोषणा FW_OFLD_CONNECTION_WR_CPLRXDATAACK_M   0x1
#घोषणा FW_OFLD_CONNECTION_WR_CPLRXDATAACK_V(x)        \
	((x) << FW_OFLD_CONNECTION_WR_CPLRXDATAACK_S)
#घोषणा FW_OFLD_CONNECTION_WR_CPLRXDATAACK_G(x)        \
	(((x) >> FW_OFLD_CONNECTION_WR_CPLRXDATAACK_S) & \
	FW_OFLD_CONNECTION_WR_CPLRXDATAACK_M)
#घोषणा FW_OFLD_CONNECTION_WR_CPLRXDATAACK_F   \
	FW_OFLD_CONNECTION_WR_CPLRXDATAACK_V(1U)

#घोषणा FW_OFLD_CONNECTION_WR_CPLPASSACCEPTRPL_S       14
#घोषणा FW_OFLD_CONNECTION_WR_CPLPASSACCEPTRPL_M       0x1
#घोषणा FW_OFLD_CONNECTION_WR_CPLPASSACCEPTRPL_V(x)    \
	((x) << FW_OFLD_CONNECTION_WR_CPLPASSACCEPTRPL_S)
#घोषणा FW_OFLD_CONNECTION_WR_CPLPASSACCEPTRPL_G(x)    \
	(((x) >> FW_OFLD_CONNECTION_WR_CPLPASSACCEPTRPL_S) & \
	FW_OFLD_CONNECTION_WR_CPLPASSACCEPTRPL_M)
#घोषणा FW_OFLD_CONNECTION_WR_CPLPASSACCEPTRPL_F       \
	FW_OFLD_CONNECTION_WR_CPLPASSACCEPTRPL_V(1U)

क्रमागत fw_flowc_mnem_tcpstate अणु
	FW_FLOWC_MNEM_TCPSTATE_CLOSED   = 0, /* illegal */
	FW_FLOWC_MNEM_TCPSTATE_LISTEN   = 1, /* illegal */
	FW_FLOWC_MNEM_TCPSTATE_SYNSENT  = 2, /* illegal */
	FW_FLOWC_MNEM_TCPSTATE_SYNRECEIVED = 3, /* illegal */
	FW_FLOWC_MNEM_TCPSTATE_ESTABLISHED = 4, /* शेष */
	FW_FLOWC_MNEM_TCPSTATE_CLOSEWAIT = 5, /* got peer बंद alपढ़ोy */
	FW_FLOWC_MNEM_TCPSTATE_FINWAIT1 = 6, /* haven't gotten ACK क्रम FIN and
					      * will resend FIN - equiv ESTAB
					      */
	FW_FLOWC_MNEM_TCPSTATE_CLOSING  = 7, /* haven't gotten ACK क्रम FIN and
					      * will resend FIN but have
					      * received FIN
					      */
	FW_FLOWC_MNEM_TCPSTATE_LASTACK  = 8, /* haven't gotten ACK क्रम FIN and
					      * will resend FIN but have
					      * received FIN
					      */
	FW_FLOWC_MNEM_TCPSTATE_FINWAIT2 = 9, /* sent FIN and got FIN + ACK,
					      * रुकोing क्रम FIN
					      */
	FW_FLOWC_MNEM_TCPSTATE_TIMEWAIT = 10, /* not expected */
पूर्ण;

क्रमागत fw_flowc_mnem_eostate अणु
	FW_FLOWC_MNEM_EOSTATE_ESTABLISHED = 1, /* शेष */
	/* graceful बंद, after sending outstanding payload */
	FW_FLOWC_MNEM_EOSTATE_CLOSING = 2,
पूर्ण;

क्रमागत fw_flowc_mnem अणु
	FW_FLOWC_MNEM_PFNVFN,		/* PFN [15:8] VFN [7:0] */
	FW_FLOWC_MNEM_CH,
	FW_FLOWC_MNEM_PORT,
	FW_FLOWC_MNEM_IQID,
	FW_FLOWC_MNEM_SNDNXT,
	FW_FLOWC_MNEM_RCVNXT,
	FW_FLOWC_MNEM_SNDBUF,
	FW_FLOWC_MNEM_MSS,
	FW_FLOWC_MNEM_TXDATAPLEN_MAX,
	FW_FLOWC_MNEM_TCPSTATE,
	FW_FLOWC_MNEM_EOSTATE,
	FW_FLOWC_MNEM_SCHEDCLASS,
	FW_FLOWC_MNEM_DCBPRIO,
	FW_FLOWC_MNEM_SND_SCALE,
	FW_FLOWC_MNEM_RCV_SCALE,
	FW_FLOWC_MNEM_ULD_MODE,
	FW_FLOWC_MNEM_MAX,
पूर्ण;

काष्ठा fw_flowc_mnemval अणु
	u8 mnemonic;
	u8 r4[3];
	__be32 val;
पूर्ण;

काष्ठा fw_flowc_wr अणु
	__be32 op_to_nparams;
	__be32 flowid_len16;
	काष्ठा fw_flowc_mnemval mnemval[];
पूर्ण;

#घोषणा FW_FLOWC_WR_NPARAMS_S           0
#घोषणा FW_FLOWC_WR_NPARAMS_V(x)        ((x) << FW_FLOWC_WR_NPARAMS_S)

काष्ठा fw_ofld_tx_data_wr अणु
	__be32 op_to_immdlen;
	__be32 flowid_len16;
	__be32 plen;
	__be32 tunnel_to_proxy;
पूर्ण;

#घोषणा FW_OFLD_TX_DATA_WR_ALIGNPLD_S   30
#घोषणा FW_OFLD_TX_DATA_WR_ALIGNPLD_V(x) ((x) << FW_OFLD_TX_DATA_WR_ALIGNPLD_S)
#घोषणा FW_OFLD_TX_DATA_WR_ALIGNPLD_F   FW_OFLD_TX_DATA_WR_ALIGNPLD_V(1U)

#घोषणा FW_OFLD_TX_DATA_WR_SHOVE_S      29
#घोषणा FW_OFLD_TX_DATA_WR_SHOVE_V(x)   ((x) << FW_OFLD_TX_DATA_WR_SHOVE_S)
#घोषणा FW_OFLD_TX_DATA_WR_SHOVE_F      FW_OFLD_TX_DATA_WR_SHOVE_V(1U)

#घोषणा FW_OFLD_TX_DATA_WR_TUNNEL_S     19
#घोषणा FW_OFLD_TX_DATA_WR_TUNNEL_V(x)  ((x) << FW_OFLD_TX_DATA_WR_TUNNEL_S)

#घोषणा FW_OFLD_TX_DATA_WR_SAVE_S       18
#घोषणा FW_OFLD_TX_DATA_WR_SAVE_V(x)    ((x) << FW_OFLD_TX_DATA_WR_SAVE_S)

#घोषणा FW_OFLD_TX_DATA_WR_FLUSH_S      17
#घोषणा FW_OFLD_TX_DATA_WR_FLUSH_V(x)   ((x) << FW_OFLD_TX_DATA_WR_FLUSH_S)
#घोषणा FW_OFLD_TX_DATA_WR_FLUSH_F      FW_OFLD_TX_DATA_WR_FLUSH_V(1U)

#घोषणा FW_OFLD_TX_DATA_WR_URGENT_S     16
#घोषणा FW_OFLD_TX_DATA_WR_URGENT_V(x)  ((x) << FW_OFLD_TX_DATA_WR_URGENT_S)

#घोषणा FW_OFLD_TX_DATA_WR_MORE_S       15
#घोषणा FW_OFLD_TX_DATA_WR_MORE_V(x)    ((x) << FW_OFLD_TX_DATA_WR_MORE_S)

#घोषणा FW_OFLD_TX_DATA_WR_ULPMODE_S    10
#घोषणा FW_OFLD_TX_DATA_WR_ULPMODE_V(x) ((x) << FW_OFLD_TX_DATA_WR_ULPMODE_S)

#घोषणा FW_OFLD_TX_DATA_WR_ULPSUBMODE_S         6
#घोषणा FW_OFLD_TX_DATA_WR_ULPSUBMODE_V(x)      \
	((x) << FW_OFLD_TX_DATA_WR_ULPSUBMODE_S)

काष्ठा fw_cmd_wr अणु
	__be32 op_dma;
	__be32 len16_pkd;
	__be64 cookie_daddr;
पूर्ण;

#घोषणा FW_CMD_WR_DMA_S         17
#घोषणा FW_CMD_WR_DMA_V(x)      ((x) << FW_CMD_WR_DMA_S)

काष्ठा fw_eth_tx_pkt_vm_wr अणु
	__be32 op_immdlen;
	__be32 equiq_to_len16;
	__be32 r3[2];
	u8 ethmacdst[6];
	u8 ethmacsrc[6];
	__be16 ethtype;
	__be16 vlantci;
पूर्ण;

#घोषणा FW_CMD_MAX_TIMEOUT 10000

/*
 * If a host driver करोes a HELLO and discovers that there's alपढ़ोy a MASTER
 * selected, we may have to रुको क्रम that MASTER to finish issuing RESET,
 * configuration and INITIALIZE commands.  Also, there's a possibility that
 * our own HELLO may get lost अगर it happens right as the MASTER is issuign a
 * RESET command, so we need to be willing to make a few retries of our HELLO.
 */
#घोषणा FW_CMD_HELLO_TIMEOUT	(3 * FW_CMD_MAX_TIMEOUT)
#घोषणा FW_CMD_HELLO_RETRIES	3


क्रमागत fw_cmd_opcodes अणु
	FW_LDST_CMD                    = 0x01,
	FW_RESET_CMD                   = 0x03,
	FW_HELLO_CMD                   = 0x04,
	FW_BYE_CMD                     = 0x05,
	FW_INITIALIZE_CMD              = 0x06,
	FW_CAPS_CONFIG_CMD             = 0x07,
	FW_PARAMS_CMD                  = 0x08,
	FW_PFVF_CMD                    = 0x09,
	FW_IQ_CMD                      = 0x10,
	FW_EQ_MNGT_CMD                 = 0x11,
	FW_EQ_ETH_CMD                  = 0x12,
	FW_EQ_CTRL_CMD                 = 0x13,
	FW_EQ_OFLD_CMD                 = 0x21,
	FW_VI_CMD                      = 0x14,
	FW_VI_MAC_CMD                  = 0x15,
	FW_VI_RXMODE_CMD               = 0x16,
	FW_VI_ENABLE_CMD               = 0x17,
	FW_ACL_MAC_CMD                 = 0x18,
	FW_ACL_VLAN_CMD                = 0x19,
	FW_VI_STATS_CMD                = 0x1a,
	FW_PORT_CMD                    = 0x1b,
	FW_PORT_STATS_CMD              = 0x1c,
	FW_PORT_LB_STATS_CMD           = 0x1d,
	FW_PORT_TRACE_CMD              = 0x1e,
	FW_PORT_TRACE_MMAP_CMD         = 0x1f,
	FW_RSS_IND_TBL_CMD             = 0x20,
	FW_RSS_GLB_CONFIG_CMD          = 0x22,
	FW_RSS_VI_CONFIG_CMD           = 0x23,
	FW_SCHED_CMD                   = 0x24,
	FW_DEVLOG_CMD                  = 0x25,
	FW_CLIP_CMD                    = 0x28,
	FW_PTP_CMD                     = 0x3e,
	FW_HMA_CMD                     = 0x3f,
	FW_LASTC2E_CMD                 = 0x40,
	FW_ERROR_CMD                   = 0x80,
	FW_DEBUG_CMD                   = 0x81,
पूर्ण;

क्रमागत fw_cmd_cap अणु
	FW_CMD_CAP_PF                  = 0x01,
	FW_CMD_CAP_DMAQ                = 0x02,
	FW_CMD_CAP_PORT                = 0x04,
	FW_CMD_CAP_PORTPROMISC         = 0x08,
	FW_CMD_CAP_PORTSTATS           = 0x10,
	FW_CMD_CAP_VF                  = 0x80,
पूर्ण;

/*
 * Generic command header flit0
 */
काष्ठा fw_cmd_hdr अणु
	__be32 hi;
	__be32 lo;
पूर्ण;

#घोषणा FW_CMD_OP_S             24
#घोषणा FW_CMD_OP_M             0xff
#घोषणा FW_CMD_OP_V(x)          ((x) << FW_CMD_OP_S)
#घोषणा FW_CMD_OP_G(x)          (((x) >> FW_CMD_OP_S) & FW_CMD_OP_M)

#घोषणा FW_CMD_REQUEST_S        23
#घोषणा FW_CMD_REQUEST_V(x)     ((x) << FW_CMD_REQUEST_S)
#घोषणा FW_CMD_REQUEST_F        FW_CMD_REQUEST_V(1U)

#घोषणा FW_CMD_READ_S           22
#घोषणा FW_CMD_READ_V(x)        ((x) << FW_CMD_READ_S)
#घोषणा FW_CMD_READ_F           FW_CMD_READ_V(1U)

#घोषणा FW_CMD_WRITE_S          21
#घोषणा FW_CMD_WRITE_V(x)       ((x) << FW_CMD_WRITE_S)
#घोषणा FW_CMD_WRITE_F          FW_CMD_WRITE_V(1U)

#घोषणा FW_CMD_EXEC_S           20
#घोषणा FW_CMD_EXEC_V(x)        ((x) << FW_CMD_EXEC_S)
#घोषणा FW_CMD_EXEC_F           FW_CMD_EXEC_V(1U)

#घोषणा FW_CMD_RAMASK_S         20
#घोषणा FW_CMD_RAMASK_V(x)      ((x) << FW_CMD_RAMASK_S)

#घोषणा FW_CMD_RETVAL_S         8
#घोषणा FW_CMD_RETVAL_M         0xff
#घोषणा FW_CMD_RETVAL_V(x)      ((x) << FW_CMD_RETVAL_S)
#घोषणा FW_CMD_RETVAL_G(x)      (((x) >> FW_CMD_RETVAL_S) & FW_CMD_RETVAL_M)

#घोषणा FW_CMD_LEN16_S          0
#घोषणा FW_CMD_LEN16_V(x)       ((x) << FW_CMD_LEN16_S)

#घोषणा FW_LEN16(fw_काष्ठा)	FW_CMD_LEN16_V(माप(fw_काष्ठा) / 16)

क्रमागत fw_ldst_addrspc अणु
	FW_LDST_ADDRSPC_FIRMWARE  = 0x0001,
	FW_LDST_ADDRSPC_SGE_EGRC  = 0x0008,
	FW_LDST_ADDRSPC_SGE_INGC  = 0x0009,
	FW_LDST_ADDRSPC_SGE_FLMC  = 0x000a,
	FW_LDST_ADDRSPC_SGE_CONMC = 0x000b,
	FW_LDST_ADDRSPC_TP_PIO    = 0x0010,
	FW_LDST_ADDRSPC_TP_TM_PIO = 0x0011,
	FW_LDST_ADDRSPC_TP_MIB    = 0x0012,
	FW_LDST_ADDRSPC_MDIO      = 0x0018,
	FW_LDST_ADDRSPC_MPS       = 0x0020,
	FW_LDST_ADDRSPC_FUNC      = 0x0028,
	FW_LDST_ADDRSPC_FUNC_PCIE = 0x0029,
	FW_LDST_ADDRSPC_I2C       = 0x0038,
पूर्ण;

क्रमागत fw_ldst_mps_fid अणु
	FW_LDST_MPS_ATRB,
	FW_LDST_MPS_RPLC
पूर्ण;

क्रमागत fw_ldst_func_access_ctl अणु
	FW_LDST_FUNC_ACC_CTL_VIID,
	FW_LDST_FUNC_ACC_CTL_FID
पूर्ण;

क्रमागत fw_ldst_func_mod_index अणु
	FW_LDST_FUNC_MPS
पूर्ण;

काष्ठा fw_ldst_cmd अणु
	__be32 op_to_addrspace;
	__be32 cycles_to_len16;
	जोड़ fw_ldst अणु
		काष्ठा fw_ldst_addrval अणु
			__be32 addr;
			__be32 val;
		पूर्ण addrval;
		काष्ठा fw_ldst_idctxt अणु
			__be32 physid;
			__be32 msg_ctxtflush;
			__be32 ctxt_data7;
			__be32 ctxt_data6;
			__be32 ctxt_data5;
			__be32 ctxt_data4;
			__be32 ctxt_data3;
			__be32 ctxt_data2;
			__be32 ctxt_data1;
			__be32 ctxt_data0;
		पूर्ण idctxt;
		काष्ठा fw_ldst_mdio अणु
			__be16 paddr_mmd;
			__be16 raddr;
			__be16 vctl;
			__be16 rval;
		पूर्ण mdio;
		काष्ठा fw_ldst_cim_rq अणु
			u8 req_first64[8];
			u8 req_second64[8];
			u8 resp_first64[8];
			u8 resp_second64[8];
			__be32 r3[2];
		पूर्ण cim_rq;
		जोड़ fw_ldst_mps अणु
			काष्ठा fw_ldst_mps_rplc अणु
				__be16 fid_idx;
				__be16 rplcpf_pkd;
				__be32 rplc255_224;
				__be32 rplc223_192;
				__be32 rplc191_160;
				__be32 rplc159_128;
				__be32 rplc127_96;
				__be32 rplc95_64;
				__be32 rplc63_32;
				__be32 rplc31_0;
			पूर्ण rplc;
			काष्ठा fw_ldst_mps_atrb अणु
				__be16 fid_mpsid;
				__be16 r2[3];
				__be32 r3[2];
				__be32 r4;
				__be32 atrb;
				__be16 vlan[16];
			पूर्ण atrb;
		पूर्ण mps;
		काष्ठा fw_ldst_func अणु
			u8 access_ctl;
			u8 mod_index;
			__be16 ctl_id;
			__be32 offset;
			__be64 data0;
			__be64 data1;
		पूर्ण func;
		काष्ठा fw_ldst_pcie अणु
			u8 ctrl_to_fn;
			u8 bnum;
			u8 r;
			u8 ext_r;
			u8 select_naccess;
			u8 pcie_fn;
			__be16 nset_pkd;
			__be32 data[12];
		पूर्ण pcie;
		काष्ठा fw_ldst_i2c_deprecated अणु
			u8 pid_pkd;
			u8 base;
			u8 boffset;
			u8 data;
			__be32 r9;
		पूर्ण i2c_deprecated;
		काष्ठा fw_ldst_i2c अणु
			u8 pid;
			u8 did;
			u8 boffset;
			u8 blen;
			__be32 r9;
			__u8   data[48];
		पूर्ण i2c;
		काष्ठा fw_ldst_le अणु
			__be32 index;
			__be32 r9;
			u8 val[33];
			u8 r11[7];
		पूर्ण le;
	पूर्ण u;
पूर्ण;

#घोषणा FW_LDST_CMD_ADDRSPACE_S		0
#घोषणा FW_LDST_CMD_ADDRSPACE_V(x)	((x) << FW_LDST_CMD_ADDRSPACE_S)

#घोषणा FW_LDST_CMD_MSG_S       31
#घोषणा FW_LDST_CMD_MSG_V(x)	((x) << FW_LDST_CMD_MSG_S)

#घोषणा FW_LDST_CMD_CTXTFLUSH_S		30
#घोषणा FW_LDST_CMD_CTXTFLUSH_V(x)	((x) << FW_LDST_CMD_CTXTFLUSH_S)
#घोषणा FW_LDST_CMD_CTXTFLUSH_F		FW_LDST_CMD_CTXTFLUSH_V(1U)

#घोषणा FW_LDST_CMD_PADDR_S     8
#घोषणा FW_LDST_CMD_PADDR_V(x)	((x) << FW_LDST_CMD_PADDR_S)

#घोषणा FW_LDST_CMD_MMD_S       0
#घोषणा FW_LDST_CMD_MMD_V(x)	((x) << FW_LDST_CMD_MMD_S)

#घोषणा FW_LDST_CMD_FID_S       15
#घोषणा FW_LDST_CMD_FID_V(x)	((x) << FW_LDST_CMD_FID_S)

#घोषणा FW_LDST_CMD_IDX_S	0
#घोषणा FW_LDST_CMD_IDX_V(x)	((x) << FW_LDST_CMD_IDX_S)

#घोषणा FW_LDST_CMD_RPLCPF_S    0
#घोषणा FW_LDST_CMD_RPLCPF_V(x)	((x) << FW_LDST_CMD_RPLCPF_S)

#घोषणा FW_LDST_CMD_LC_S        4
#घोषणा FW_LDST_CMD_LC_V(x)     ((x) << FW_LDST_CMD_LC_S)
#घोषणा FW_LDST_CMD_LC_F	FW_LDST_CMD_LC_V(1U)

#घोषणा FW_LDST_CMD_FN_S        0
#घोषणा FW_LDST_CMD_FN_V(x)	((x) << FW_LDST_CMD_FN_S)

#घोषणा FW_LDST_CMD_NACCESS_S           0
#घोषणा FW_LDST_CMD_NACCESS_V(x)	((x) << FW_LDST_CMD_NACCESS_S)

काष्ठा fw_reset_cmd अणु
	__be32 op_to_ग_लिखो;
	__be32 retval_len16;
	__be32 val;
	__be32 halt_pkd;
पूर्ण;

#घोषणा FW_RESET_CMD_HALT_S	31
#घोषणा FW_RESET_CMD_HALT_M     0x1
#घोषणा FW_RESET_CMD_HALT_V(x)	((x) << FW_RESET_CMD_HALT_S)
#घोषणा FW_RESET_CMD_HALT_G(x)  \
	(((x) >> FW_RESET_CMD_HALT_S) & FW_RESET_CMD_HALT_M)
#घोषणा FW_RESET_CMD_HALT_F	FW_RESET_CMD_HALT_V(1U)

क्रमागत fw_hellow_cmd अणु
	fw_hello_cmd_stage_os		= 0x0
पूर्ण;

काष्ठा fw_hello_cmd अणु
	__be32 op_to_ग_लिखो;
	__be32 retval_len16;
	__be32 err_to_clearinit;
	__be32 fwrev;
पूर्ण;

#घोषणा FW_HELLO_CMD_ERR_S      31
#घोषणा FW_HELLO_CMD_ERR_V(x)   ((x) << FW_HELLO_CMD_ERR_S)
#घोषणा FW_HELLO_CMD_ERR_F	FW_HELLO_CMD_ERR_V(1U)

#घोषणा FW_HELLO_CMD_INIT_S     30
#घोषणा FW_HELLO_CMD_INIT_V(x)  ((x) << FW_HELLO_CMD_INIT_S)
#घोषणा FW_HELLO_CMD_INIT_F	FW_HELLO_CMD_INIT_V(1U)

#घोषणा FW_HELLO_CMD_MASTERDIS_S	29
#घोषणा FW_HELLO_CMD_MASTERDIS_V(x)	((x) << FW_HELLO_CMD_MASTERDIS_S)

#घोषणा FW_HELLO_CMD_MASTERFORCE_S      28
#घोषणा FW_HELLO_CMD_MASTERFORCE_V(x)	((x) << FW_HELLO_CMD_MASTERFORCE_S)

#घोषणा FW_HELLO_CMD_MBMASTER_S		24
#घोषणा FW_HELLO_CMD_MBMASTER_M		0xfU
#घोषणा FW_HELLO_CMD_MBMASTER_V(x)	((x) << FW_HELLO_CMD_MBMASTER_S)
#घोषणा FW_HELLO_CMD_MBMASTER_G(x)	\
	(((x) >> FW_HELLO_CMD_MBMASTER_S) & FW_HELLO_CMD_MBMASTER_M)

#घोषणा FW_HELLO_CMD_MBASYNCNOTINT_S    23
#घोषणा FW_HELLO_CMD_MBASYNCNOTINT_V(x)	((x) << FW_HELLO_CMD_MBASYNCNOTINT_S)

#घोषणा FW_HELLO_CMD_MBASYNCNOT_S       20
#घोषणा FW_HELLO_CMD_MBASYNCNOT_V(x)	((x) << FW_HELLO_CMD_MBASYNCNOT_S)

#घोषणा FW_HELLO_CMD_STAGE_S		17
#घोषणा FW_HELLO_CMD_STAGE_V(x)		((x) << FW_HELLO_CMD_STAGE_S)

#घोषणा FW_HELLO_CMD_CLEARINIT_S        16
#घोषणा FW_HELLO_CMD_CLEARINIT_V(x)     ((x) << FW_HELLO_CMD_CLEARINIT_S)
#घोषणा FW_HELLO_CMD_CLEARINIT_F	FW_HELLO_CMD_CLEARINIT_V(1U)

काष्ठा fw_bye_cmd अणु
	__be32 op_to_ग_लिखो;
	__be32 retval_len16;
	__be64 r3;
पूर्ण;

काष्ठा fw_initialize_cmd अणु
	__be32 op_to_ग_लिखो;
	__be32 retval_len16;
	__be64 r3;
पूर्ण;

क्रमागत fw_caps_config_hm अणु
	FW_CAPS_CONFIG_HM_PCIE		= 0x00000001,
	FW_CAPS_CONFIG_HM_PL		= 0x00000002,
	FW_CAPS_CONFIG_HM_SGE		= 0x00000004,
	FW_CAPS_CONFIG_HM_CIM		= 0x00000008,
	FW_CAPS_CONFIG_HM_ULPTX		= 0x00000010,
	FW_CAPS_CONFIG_HM_TP		= 0x00000020,
	FW_CAPS_CONFIG_HM_ULPRX		= 0x00000040,
	FW_CAPS_CONFIG_HM_PMRX		= 0x00000080,
	FW_CAPS_CONFIG_HM_PMTX		= 0x00000100,
	FW_CAPS_CONFIG_HM_MC		= 0x00000200,
	FW_CAPS_CONFIG_HM_LE		= 0x00000400,
	FW_CAPS_CONFIG_HM_MPS		= 0x00000800,
	FW_CAPS_CONFIG_HM_XGMAC		= 0x00001000,
	FW_CAPS_CONFIG_HM_CPLSWITCH	= 0x00002000,
	FW_CAPS_CONFIG_HM_T4DBG		= 0x00004000,
	FW_CAPS_CONFIG_HM_MI		= 0x00008000,
	FW_CAPS_CONFIG_HM_I2CM		= 0x00010000,
	FW_CAPS_CONFIG_HM_NCSI		= 0x00020000,
	FW_CAPS_CONFIG_HM_SMB		= 0x00040000,
	FW_CAPS_CONFIG_HM_MA		= 0x00080000,
	FW_CAPS_CONFIG_HM_EDRAM		= 0x00100000,
	FW_CAPS_CONFIG_HM_PMU		= 0x00200000,
	FW_CAPS_CONFIG_HM_UART		= 0x00400000,
	FW_CAPS_CONFIG_HM_SF		= 0x00800000,
पूर्ण;

क्रमागत fw_caps_config_nbm अणु
	FW_CAPS_CONFIG_NBM_IPMI		= 0x00000001,
	FW_CAPS_CONFIG_NBM_NCSI		= 0x00000002,
पूर्ण;

क्रमागत fw_caps_config_link अणु
	FW_CAPS_CONFIG_LINK_PPP		= 0x00000001,
	FW_CAPS_CONFIG_LINK_QFC		= 0x00000002,
	FW_CAPS_CONFIG_LINK_DCBX	= 0x00000004,
पूर्ण;

क्रमागत fw_caps_config_चयन अणु
	FW_CAPS_CONFIG_SWITCH_INGRESS	= 0x00000001,
	FW_CAPS_CONFIG_SWITCH_EGRESS	= 0x00000002,
पूर्ण;

क्रमागत fw_caps_config_nic अणु
	FW_CAPS_CONFIG_NIC		= 0x00000001,
	FW_CAPS_CONFIG_NIC_VM		= 0x00000002,
	FW_CAPS_CONFIG_NIC_HASHFILTER	= 0x00000020,
	FW_CAPS_CONFIG_NIC_ETHOFLD	= 0x00000040,
पूर्ण;

क्रमागत fw_caps_config_ofld अणु
	FW_CAPS_CONFIG_OFLD		= 0x00000001,
पूर्ण;

क्रमागत fw_caps_config_rdma अणु
	FW_CAPS_CONFIG_RDMA_RDDP	= 0x00000001,
	FW_CAPS_CONFIG_RDMA_RDMAC	= 0x00000002,
पूर्ण;

क्रमागत fw_caps_config_iscsi अणु
	FW_CAPS_CONFIG_ISCSI_INITIATOR_PDU = 0x00000001,
	FW_CAPS_CONFIG_ISCSI_TARGET_PDU = 0x00000002,
	FW_CAPS_CONFIG_ISCSI_INITIATOR_CNXOFLD = 0x00000004,
	FW_CAPS_CONFIG_ISCSI_TARGET_CNXOFLD = 0x00000008,
पूर्ण;

क्रमागत fw_caps_config_crypto अणु
	FW_CAPS_CONFIG_CRYPTO_LOOKASIDE = 0x00000001,
	FW_CAPS_CONFIG_TLS_INLINE = 0x00000002,
	FW_CAPS_CONFIG_IPSEC_INLINE = 0x00000004,
	FW_CAPS_CONFIG_TLS_HW = 0x00000008,
पूर्ण;

क्रमागत fw_caps_config_fcoe अणु
	FW_CAPS_CONFIG_FCOE_INITIATOR	= 0x00000001,
	FW_CAPS_CONFIG_FCOE_TARGET	= 0x00000002,
	FW_CAPS_CONFIG_FCOE_CTRL_OFLD	= 0x00000004,
पूर्ण;

क्रमागत fw_memtype_cf अणु
	FW_MEMTYPE_CF_EDC0		= 0x0,
	FW_MEMTYPE_CF_EDC1		= 0x1,
	FW_MEMTYPE_CF_EXTMEM		= 0x2,
	FW_MEMTYPE_CF_FLASH		= 0x4,
	FW_MEMTYPE_CF_INTERNAL		= 0x5,
	FW_MEMTYPE_CF_EXTMEM1           = 0x6,
	FW_MEMTYPE_CF_HMA		= 0x7,
पूर्ण;

काष्ठा fw_caps_config_cmd अणु
	__be32 op_to_ग_लिखो;
	__be32 cfvalid_to_len16;
	__be32 r2;
	__be32 hwmbiपंचांगap;
	__be16 nbmcaps;
	__be16 linkcaps;
	__be16 चयनcaps;
	__be16 r3;
	__be16 niccaps;
	__be16 ofldcaps;
	__be16 rdmacaps;
	__be16 cryptocaps;
	__be16 iscsicaps;
	__be16 fcoecaps;
	__be32 cfcsum;
	__be32 finiver;
	__be32 finicsum;
पूर्ण;

#घोषणा FW_CAPS_CONFIG_CMD_CFVALID_S    27
#घोषणा FW_CAPS_CONFIG_CMD_CFVALID_V(x) ((x) << FW_CAPS_CONFIG_CMD_CFVALID_S)
#घोषणा FW_CAPS_CONFIG_CMD_CFVALID_F    FW_CAPS_CONFIG_CMD_CFVALID_V(1U)

#घोषणा FW_CAPS_CONFIG_CMD_MEMTYPE_CF_S		24
#घोषणा FW_CAPS_CONFIG_CMD_MEMTYPE_CF_V(x)	\
	((x) << FW_CAPS_CONFIG_CMD_MEMTYPE_CF_S)

#घोषणा FW_CAPS_CONFIG_CMD_MEMADDR64K_CF_S      16
#घोषणा FW_CAPS_CONFIG_CMD_MEMADDR64K_CF_V(x)	\
	((x) << FW_CAPS_CONFIG_CMD_MEMADDR64K_CF_S)

/*
 * params command mnemonics
 */
क्रमागत fw_params_mnem अणु
	FW_PARAMS_MNEM_DEV		= 1,	/* device params */
	FW_PARAMS_MNEM_PFVF		= 2,	/* function params */
	FW_PARAMS_MNEM_REG		= 3,	/* limited रेजिस्टर access */
	FW_PARAMS_MNEM_DMAQ		= 4,	/* dma queue params */
	FW_PARAMS_MNEM_CHNET            = 5,    /* chnet params */
	FW_PARAMS_MNEM_LAST
पूर्ण;

/*
 * device parameters
 */

#घोषणा FW_PARAMS_PARAM_FILTER_MODE_S 16
#घोषणा FW_PARAMS_PARAM_FILTER_MODE_M 0xffff
#घोषणा FW_PARAMS_PARAM_FILTER_MODE_V(x)          \
	((x) << FW_PARAMS_PARAM_FILTER_MODE_S)
#घोषणा FW_PARAMS_PARAM_FILTER_MODE_G(x)          \
	(((x) >> FW_PARAMS_PARAM_FILTER_MODE_S) & \
	FW_PARAMS_PARAM_FILTER_MODE_M)

#घोषणा FW_PARAMS_PARAM_FILTER_MASK_S 0
#घोषणा FW_PARAMS_PARAM_FILTER_MASK_M 0xffff
#घोषणा FW_PARAMS_PARAM_FILTER_MASK_V(x)          \
	((x) << FW_PARAMS_PARAM_FILTER_MASK_S)
#घोषणा FW_PARAMS_PARAM_FILTER_MASK_G(x)          \
	(((x) >> FW_PARAMS_PARAM_FILTER_MASK_S) & \
	FW_PARAMS_PARAM_FILTER_MASK_M)

क्रमागत fw_params_param_dev अणु
	FW_PARAMS_PARAM_DEV_CCLK	= 0x00, /* chip core घड़ी in khz */
	FW_PARAMS_PARAM_DEV_PORTVEC	= 0x01, /* the port vector */
	FW_PARAMS_PARAM_DEV_NTID	= 0x02, /* पढ़ोs the number of TIDs
						 * allocated by the device's
						 * Lookup Engine
						 */
	FW_PARAMS_PARAM_DEV_FLOWC_BUFFIFO_SZ = 0x03,
	FW_PARAMS_PARAM_DEV_INTVER_NIC	= 0x04,
	FW_PARAMS_PARAM_DEV_INTVER_VNIC = 0x05,
	FW_PARAMS_PARAM_DEV_INTVER_OFLD = 0x06,
	FW_PARAMS_PARAM_DEV_INTVER_RI	= 0x07,
	FW_PARAMS_PARAM_DEV_INTVER_ISCSIPDU = 0x08,
	FW_PARAMS_PARAM_DEV_INTVER_ISCSI = 0x09,
	FW_PARAMS_PARAM_DEV_INTVER_FCOE = 0x0A,
	FW_PARAMS_PARAM_DEV_FWREV = 0x0B,
	FW_PARAMS_PARAM_DEV_TPREV = 0x0C,
	FW_PARAMS_PARAM_DEV_CF = 0x0D,
	FW_PARAMS_PARAM_DEV_PHYFW = 0x0F,
	FW_PARAMS_PARAM_DEV_DIAG = 0x11,
	FW_PARAMS_PARAM_DEV_MAXORसूचीD_QP = 0x13, /* max supported QP IRD/ORD */
	FW_PARAMS_PARAM_DEV_MAXIRD_ADAPTER = 0x14, /* max supported adap IRD */
	FW_PARAMS_PARAM_DEV_ULPTX_MEMWRITE_DSGL = 0x17,
	FW_PARAMS_PARAM_DEV_FWCACHE = 0x18,
	FW_PARAMS_PARAM_DEV_SCFGREV = 0x1A,
	FW_PARAMS_PARAM_DEV_VPDREV = 0x1B,
	FW_PARAMS_PARAM_DEV_RI_FR_NSMR_TPTE_WR	= 0x1C,
	FW_PARAMS_PARAM_DEV_FILTER2_WR  = 0x1D,
	FW_PARAMS_PARAM_DEV_MPSBGMAP	= 0x1E,
	FW_PARAMS_PARAM_DEV_TPCHMAP     = 0x1F,
	FW_PARAMS_PARAM_DEV_HMA_SIZE	= 0x20,
	FW_PARAMS_PARAM_DEV_RDMA_WRITE_WITH_IMM = 0x21,
	FW_PARAMS_PARAM_DEV_PPOD_EDRAM  = 0x23,
	FW_PARAMS_PARAM_DEV_RI_WRITE_CMPL_WR    = 0x24,
	FW_PARAMS_PARAM_DEV_HPFILTER_REGION_SUPPORT = 0x26,
	FW_PARAMS_PARAM_DEV_OPAQUE_VIID_SMT_EXTN = 0x27,
	FW_PARAMS_PARAM_DEV_HASHFILTER_WITH_OFLD = 0x28,
	FW_PARAMS_PARAM_DEV_DBQ_TIMER	= 0x29,
	FW_PARAMS_PARAM_DEV_DBQ_TIMERTICK = 0x2A,
	FW_PARAMS_PARAM_DEV_NUM_TM_CLASS = 0x2B,
	FW_PARAMS_PARAM_DEV_FILTER = 0x2E,
	FW_PARAMS_PARAM_DEV_KTLS_HW = 0x31,
पूर्ण;

/*
 * physical and भव function parameters
 */
क्रमागत fw_params_param_pfvf अणु
	FW_PARAMS_PARAM_PFVF_RWXCAPS	= 0x00,
	FW_PARAMS_PARAM_PFVF_ROUTE_START = 0x01,
	FW_PARAMS_PARAM_PFVF_ROUTE_END = 0x02,
	FW_PARAMS_PARAM_PFVF_CLIP_START = 0x03,
	FW_PARAMS_PARAM_PFVF_CLIP_END = 0x04,
	FW_PARAMS_PARAM_PFVF_FILTER_START = 0x05,
	FW_PARAMS_PARAM_PFVF_FILTER_END = 0x06,
	FW_PARAMS_PARAM_PFVF_SERVER_START = 0x07,
	FW_PARAMS_PARAM_PFVF_SERVER_END = 0x08,
	FW_PARAMS_PARAM_PFVF_TDDP_START = 0x09,
	FW_PARAMS_PARAM_PFVF_TDDP_END = 0x0A,
	FW_PARAMS_PARAM_PFVF_ISCSI_START = 0x0B,
	FW_PARAMS_PARAM_PFVF_ISCSI_END = 0x0C,
	FW_PARAMS_PARAM_PFVF_STAG_START = 0x0D,
	FW_PARAMS_PARAM_PFVF_STAG_END = 0x0E,
	FW_PARAMS_PARAM_PFVF_RQ_START = 0x1F,
	FW_PARAMS_PARAM_PFVF_RQ_END	= 0x10,
	FW_PARAMS_PARAM_PFVF_PBL_START = 0x11,
	FW_PARAMS_PARAM_PFVF_PBL_END	= 0x12,
	FW_PARAMS_PARAM_PFVF_L2T_START = 0x13,
	FW_PARAMS_PARAM_PFVF_L2T_END = 0x14,
	FW_PARAMS_PARAM_PFVF_SQRQ_START = 0x15,
	FW_PARAMS_PARAM_PFVF_SQRQ_END	= 0x16,
	FW_PARAMS_PARAM_PFVF_CQ_START	= 0x17,
	FW_PARAMS_PARAM_PFVF_CQ_END	= 0x18,
	FW_PARAMS_PARAM_PFVF_SRQ_START  = 0x19,
	FW_PARAMS_PARAM_PFVF_SRQ_END    = 0x1A,
	FW_PARAMS_PARAM_PFVF_SCHEDCLASS_ETH = 0x20,
	FW_PARAMS_PARAM_PFVF_VIID       = 0x24,
	FW_PARAMS_PARAM_PFVF_CPMASK     = 0x25,
	FW_PARAMS_PARAM_PFVF_OCQ_START  = 0x26,
	FW_PARAMS_PARAM_PFVF_OCQ_END    = 0x27,
	FW_PARAMS_PARAM_PFVF_CONM_MAP   = 0x28,
	FW_PARAMS_PARAM_PFVF_IQFLINT_START = 0x29,
	FW_PARAMS_PARAM_PFVF_IQFLINT_END = 0x2A,
	FW_PARAMS_PARAM_PFVF_EQ_START	= 0x2B,
	FW_PARAMS_PARAM_PFVF_EQ_END	= 0x2C,
	FW_PARAMS_PARAM_PFVF_ACTIVE_FILTER_START = 0x2D,
	FW_PARAMS_PARAM_PFVF_ACTIVE_FILTER_END = 0x2E,
	FW_PARAMS_PARAM_PFVF_ETHOFLD_START = 0x2F,
	FW_PARAMS_PARAM_PFVF_ETHOFLD_END = 0x30,
	FW_PARAMS_PARAM_PFVF_CPLFW4MSG_ENCAP = 0x31,
	FW_PARAMS_PARAM_PFVF_HPFILTER_START = 0x32,
	FW_PARAMS_PARAM_PFVF_HPFILTER_END = 0x33,
	FW_PARAMS_PARAM_PFVF_TLS_START = 0x34,
	FW_PARAMS_PARAM_PFVF_TLS_END = 0x35,
	FW_PARAMS_PARAM_PFVF_RAWF_START = 0x36,
	FW_PARAMS_PARAM_PFVF_RAWF_END = 0x37,
	FW_PARAMS_PARAM_PFVF_NCRYPTO_LOOKASIDE = 0x39,
	FW_PARAMS_PARAM_PFVF_PORT_CAPS32 = 0x3A,
	FW_PARAMS_PARAM_PFVF_PPOD_EDRAM_START = 0x3B,
	FW_PARAMS_PARAM_PFVF_PPOD_EDRAM_END = 0x3C,
	FW_PARAMS_PARAM_PFVF_LINK_STATE = 0x40,
पूर्ण;

/* Virtual link state as seen by the specअगरied VF */
क्रमागत vf_link_states अणु
	FW_VF_LINK_STATE_AUTO		= 0x00,
	FW_VF_LINK_STATE_ENABLE		= 0x01,
	FW_VF_LINK_STATE_DISABLE	= 0x02,
पूर्ण;

/*
 * dma queue parameters
 */
क्रमागत fw_params_param_dmaq अणु
	FW_PARAMS_PARAM_DMAQ_IQ_DCAEN_DCACPU = 0x00,
	FW_PARAMS_PARAM_DMAQ_IQ_INTCNTTHRESH = 0x01,
	FW_PARAMS_PARAM_DMAQ_EQ_CMPLIQID_MNGT = 0x10,
	FW_PARAMS_PARAM_DMAQ_EQ_CMPLIQID_CTRL = 0x11,
	FW_PARAMS_PARAM_DMAQ_EQ_SCHEDCLASS_ETH = 0x12,
	FW_PARAMS_PARAM_DMAQ_EQ_DCBPRIO_ETH = 0x13,
	FW_PARAMS_PARAM_DMAQ_EQ_TIMERIX	= 0x15,
	FW_PARAMS_PARAM_DMAQ_CONM_CTXT = 0x20,
पूर्ण;

क्रमागत fw_params_param_dev_ktls_hw अणु
	FW_PARAMS_PARAM_DEV_KTLS_HW_DISABLE      = 0x00,
	FW_PARAMS_PARAM_DEV_KTLS_HW_ENABLE       = 0x01,
	FW_PARAMS_PARAM_DEV_KTLS_HW_USER_ENABLE  = 0x01,
पूर्ण;

क्रमागत fw_params_param_dev_phyfw अणु
	FW_PARAMS_PARAM_DEV_PHYFW_DOWNLOAD = 0x00,
	FW_PARAMS_PARAM_DEV_PHYFW_VERSION = 0x01,
पूर्ण;

क्रमागत fw_params_param_dev_diag अणु
	FW_PARAM_DEV_DIAG_TMP		= 0x00,
	FW_PARAM_DEV_DIAG_VDD		= 0x01,
	FW_PARAM_DEV_DIAG_MAXTMPTHRESH	= 0x02,
पूर्ण;

क्रमागत fw_params_param_dev_filter अणु
	FW_PARAM_DEV_FILTER_VNIC_MODE   = 0x00,
	FW_PARAM_DEV_FILTER_MODE_MASK   = 0x01,
पूर्ण;

क्रमागत fw_params_param_dev_fwcache अणु
	FW_PARAM_DEV_FWCACHE_FLUSH      = 0x00,
	FW_PARAM_DEV_FWCACHE_FLUSHINV   = 0x01,
पूर्ण;

#घोषणा FW_PARAMS_MNEM_S	24
#घोषणा FW_PARAMS_MNEM_V(x)	((x) << FW_PARAMS_MNEM_S)

#घोषणा FW_PARAMS_PARAM_X_S     16
#घोषणा FW_PARAMS_PARAM_X_V(x)	((x) << FW_PARAMS_PARAM_X_S)

#घोषणा FW_PARAMS_PARAM_Y_S	8
#घोषणा FW_PARAMS_PARAM_Y_M	0xffU
#घोषणा FW_PARAMS_PARAM_Y_V(x)	((x) << FW_PARAMS_PARAM_Y_S)
#घोषणा FW_PARAMS_PARAM_Y_G(x)	(((x) >> FW_PARAMS_PARAM_Y_S) &\
		FW_PARAMS_PARAM_Y_M)

#घोषणा FW_PARAMS_PARAM_Z_S	0
#घोषणा FW_PARAMS_PARAM_Z_M	0xffu
#घोषणा FW_PARAMS_PARAM_Z_V(x)	((x) << FW_PARAMS_PARAM_Z_S)
#घोषणा FW_PARAMS_PARAM_Z_G(x)	(((x) >> FW_PARAMS_PARAM_Z_S) &\
		FW_PARAMS_PARAM_Z_M)

#घोषणा FW_PARAMS_PARAM_XYZ_S		0
#घोषणा FW_PARAMS_PARAM_XYZ_V(x)	((x) << FW_PARAMS_PARAM_XYZ_S)

#घोषणा FW_PARAMS_PARAM_YZ_S		0
#घोषणा FW_PARAMS_PARAM_YZ_V(x)		((x) << FW_PARAMS_PARAM_YZ_S)

काष्ठा fw_params_cmd अणु
	__be32 op_to_vfn;
	__be32 retval_len16;
	काष्ठा fw_params_param अणु
		__be32 mnem;
		__be32 val;
	पूर्ण param[7];
पूर्ण;

#घोषणा FW_PARAMS_CMD_PFN_S     8
#घोषणा FW_PARAMS_CMD_PFN_V(x)	((x) << FW_PARAMS_CMD_PFN_S)

#घोषणा FW_PARAMS_CMD_VFN_S     0
#घोषणा FW_PARAMS_CMD_VFN_V(x)	((x) << FW_PARAMS_CMD_VFN_S)

काष्ठा fw_pfvf_cmd अणु
	__be32 op_to_vfn;
	__be32 retval_len16;
	__be32 niqflपूर्णांक_niq;
	__be32 type_to_neq;
	__be32 tc_to_nexactf;
	__be32 r_caps_to_nethctrl;
	__be16 nricq;
	__be16 nriqp;
	__be32 r4;
पूर्ण;

#घोषणा FW_PFVF_CMD_PFN_S	8
#घोषणा FW_PFVF_CMD_PFN_V(x)	((x) << FW_PFVF_CMD_PFN_S)

#घोषणा FW_PFVF_CMD_VFN_S       0
#घोषणा FW_PFVF_CMD_VFN_V(x)	((x) << FW_PFVF_CMD_VFN_S)

#घोषणा FW_PFVF_CMD_NIQFLINT_S          20
#घोषणा FW_PFVF_CMD_NIQFLINT_M          0xfff
#घोषणा FW_PFVF_CMD_NIQFLINT_V(x)	((x) << FW_PFVF_CMD_NIQFLINT_S)
#घोषणा FW_PFVF_CMD_NIQFLINT_G(x)	\
	(((x) >> FW_PFVF_CMD_NIQFLINT_S) & FW_PFVF_CMD_NIQFLINT_M)

#घोषणा FW_PFVF_CMD_NIQ_S       0
#घोषणा FW_PFVF_CMD_NIQ_M       0xfffff
#घोषणा FW_PFVF_CMD_NIQ_V(x)	((x) << FW_PFVF_CMD_NIQ_S)
#घोषणा FW_PFVF_CMD_NIQ_G(x)	\
	(((x) >> FW_PFVF_CMD_NIQ_S) & FW_PFVF_CMD_NIQ_M)

#घोषणा FW_PFVF_CMD_TYPE_S      31
#घोषणा FW_PFVF_CMD_TYPE_M      0x1
#घोषणा FW_PFVF_CMD_TYPE_V(x)   ((x) << FW_PFVF_CMD_TYPE_S)
#घोषणा FW_PFVF_CMD_TYPE_G(x)	\
	(((x) >> FW_PFVF_CMD_TYPE_S) & FW_PFVF_CMD_TYPE_M)
#घोषणा FW_PFVF_CMD_TYPE_F      FW_PFVF_CMD_TYPE_V(1U)

#घोषणा FW_PFVF_CMD_CMASK_S     24
#घोषणा FW_PFVF_CMD_CMASK_M	0xf
#घोषणा FW_PFVF_CMD_CMASK_V(x)	((x) << FW_PFVF_CMD_CMASK_S)
#घोषणा FW_PFVF_CMD_CMASK_G(x)	\
	(((x) >> FW_PFVF_CMD_CMASK_S) & FW_PFVF_CMD_CMASK_M)

#घोषणा FW_PFVF_CMD_PMASK_S     20
#घोषणा FW_PFVF_CMD_PMASK_M	0xf
#घोषणा FW_PFVF_CMD_PMASK_V(x)	((x) << FW_PFVF_CMD_PMASK_S)
#घोषणा FW_PFVF_CMD_PMASK_G(x) \
	(((x) >> FW_PFVF_CMD_PMASK_S) & FW_PFVF_CMD_PMASK_M)

#घोषणा FW_PFVF_CMD_NEQ_S       0
#घोषणा FW_PFVF_CMD_NEQ_M       0xfffff
#घोषणा FW_PFVF_CMD_NEQ_V(x)	((x) << FW_PFVF_CMD_NEQ_S)
#घोषणा FW_PFVF_CMD_NEQ_G(x)	\
	(((x) >> FW_PFVF_CMD_NEQ_S) & FW_PFVF_CMD_NEQ_M)

#घोषणा FW_PFVF_CMD_TC_S        24
#घोषणा FW_PFVF_CMD_TC_M        0xff
#घोषणा FW_PFVF_CMD_TC_V(x)	((x) << FW_PFVF_CMD_TC_S)
#घोषणा FW_PFVF_CMD_TC_G(x)	(((x) >> FW_PFVF_CMD_TC_S) & FW_PFVF_CMD_TC_M)

#घोषणा FW_PFVF_CMD_NVI_S       16
#घोषणा FW_PFVF_CMD_NVI_M       0xff
#घोषणा FW_PFVF_CMD_NVI_V(x)	((x) << FW_PFVF_CMD_NVI_S)
#घोषणा FW_PFVF_CMD_NVI_G(x)	(((x) >> FW_PFVF_CMD_NVI_S) & FW_PFVF_CMD_NVI_M)

#घोषणा FW_PFVF_CMD_NEXACTF_S           0
#घोषणा FW_PFVF_CMD_NEXACTF_M           0xffff
#घोषणा FW_PFVF_CMD_NEXACTF_V(x)	((x) << FW_PFVF_CMD_NEXACTF_S)
#घोषणा FW_PFVF_CMD_NEXACTF_G(x)	\
	(((x) >> FW_PFVF_CMD_NEXACTF_S) & FW_PFVF_CMD_NEXACTF_M)

#घोषणा FW_PFVF_CMD_R_CAPS_S    24
#घोषणा FW_PFVF_CMD_R_CAPS_M    0xff
#घोषणा FW_PFVF_CMD_R_CAPS_V(x) ((x) << FW_PFVF_CMD_R_CAPS_S)
#घोषणा FW_PFVF_CMD_R_CAPS_G(x) \
	(((x) >> FW_PFVF_CMD_R_CAPS_S) & FW_PFVF_CMD_R_CAPS_M)

#घोषणा FW_PFVF_CMD_WX_CAPS_S           16
#घोषणा FW_PFVF_CMD_WX_CAPS_M           0xff
#घोषणा FW_PFVF_CMD_WX_CAPS_V(x)	((x) << FW_PFVF_CMD_WX_CAPS_S)
#घोषणा FW_PFVF_CMD_WX_CAPS_G(x)	\
	(((x) >> FW_PFVF_CMD_WX_CAPS_S) & FW_PFVF_CMD_WX_CAPS_M)

#घोषणा FW_PFVF_CMD_NETHCTRL_S          0
#घोषणा FW_PFVF_CMD_NETHCTRL_M          0xffff
#घोषणा FW_PFVF_CMD_NETHCTRL_V(x)	((x) << FW_PFVF_CMD_NETHCTRL_S)
#घोषणा FW_PFVF_CMD_NETHCTRL_G(x)	\
	(((x) >> FW_PFVF_CMD_NETHCTRL_S) & FW_PFVF_CMD_NETHCTRL_M)

क्रमागत fw_iq_type अणु
	FW_IQ_TYPE_FL_INT_CAP,
	FW_IQ_TYPE_NO_FL_INT_CAP
पूर्ण;

क्रमागत fw_iq_iqtype अणु
	FW_IQ_IQTYPE_OTHER,
	FW_IQ_IQTYPE_NIC,
	FW_IQ_IQTYPE_OFLD,
पूर्ण;

काष्ठा fw_iq_cmd अणु
	__be32 op_to_vfn;
	__be32 alloc_to_len16;
	__be16 physiqid;
	__be16 iqid;
	__be16 fl0id;
	__be16 fl1id;
	__be32 type_to_iqandstindex;
	__be16 iqdroprss_to_iqesize;
	__be16 iqsize;
	__be64 iqaddr;
	__be32 iqns_to_fl0congen;
	__be16 fl0dcaen_to_fl0cidxfthresh;
	__be16 fl0size;
	__be64 fl0addr;
	__be32 fl1cngchmap_to_fl1congen;
	__be16 fl1dcaen_to_fl1cidxfthresh;
	__be16 fl1size;
	__be64 fl1addr;
पूर्ण;

#घोषणा FW_IQ_CMD_PFN_S		8
#घोषणा FW_IQ_CMD_PFN_V(x)	((x) << FW_IQ_CMD_PFN_S)

#घोषणा FW_IQ_CMD_VFN_S		0
#घोषणा FW_IQ_CMD_VFN_V(x)	((x) << FW_IQ_CMD_VFN_S)

#घोषणा FW_IQ_CMD_ALLOC_S	31
#घोषणा FW_IQ_CMD_ALLOC_V(x)	((x) << FW_IQ_CMD_ALLOC_S)
#घोषणा FW_IQ_CMD_ALLOC_F	FW_IQ_CMD_ALLOC_V(1U)

#घोषणा FW_IQ_CMD_FREE_S	30
#घोषणा FW_IQ_CMD_FREE_V(x)	((x) << FW_IQ_CMD_FREE_S)
#घोषणा FW_IQ_CMD_FREE_F	FW_IQ_CMD_FREE_V(1U)

#घोषणा FW_IQ_CMD_MODIFY_S	29
#घोषणा FW_IQ_CMD_MODIFY_V(x)	((x) << FW_IQ_CMD_MODIFY_S)
#घोषणा FW_IQ_CMD_MODIFY_F	FW_IQ_CMD_MODIFY_V(1U)

#घोषणा FW_IQ_CMD_IQSTART_S	28
#घोषणा FW_IQ_CMD_IQSTART_V(x)	((x) << FW_IQ_CMD_IQSTART_S)
#घोषणा FW_IQ_CMD_IQSTART_F	FW_IQ_CMD_IQSTART_V(1U)

#घोषणा FW_IQ_CMD_IQSTOP_S	27
#घोषणा FW_IQ_CMD_IQSTOP_V(x)	((x) << FW_IQ_CMD_IQSTOP_S)
#घोषणा FW_IQ_CMD_IQSTOP_F	FW_IQ_CMD_IQSTOP_V(1U)

#घोषणा FW_IQ_CMD_TYPE_S	29
#घोषणा FW_IQ_CMD_TYPE_V(x)	((x) << FW_IQ_CMD_TYPE_S)

#घोषणा FW_IQ_CMD_IQASYNCH_S	28
#घोषणा FW_IQ_CMD_IQASYNCH_V(x)	((x) << FW_IQ_CMD_IQASYNCH_S)

#घोषणा FW_IQ_CMD_VIID_S	16
#घोषणा FW_IQ_CMD_VIID_V(x)	((x) << FW_IQ_CMD_VIID_S)

#घोषणा FW_IQ_CMD_IQANDST_S	15
#घोषणा FW_IQ_CMD_IQANDST_V(x)	((x) << FW_IQ_CMD_IQANDST_S)

#घोषणा FW_IQ_CMD_IQANUS_S	14
#घोषणा FW_IQ_CMD_IQANUS_V(x)	((x) << FW_IQ_CMD_IQANUS_S)

#घोषणा FW_IQ_CMD_IQANUD_S	12
#घोषणा FW_IQ_CMD_IQANUD_V(x)	((x) << FW_IQ_CMD_IQANUD_S)

#घोषणा FW_IQ_CMD_IQANDSTINDEX_S	0
#घोषणा FW_IQ_CMD_IQANDSTINDEX_V(x)	((x) << FW_IQ_CMD_IQANDSTINDEX_S)

#घोषणा FW_IQ_CMD_IQDROPRSS_S		15
#घोषणा FW_IQ_CMD_IQDROPRSS_V(x)	((x) << FW_IQ_CMD_IQDROPRSS_S)
#घोषणा FW_IQ_CMD_IQDROPRSS_F	FW_IQ_CMD_IQDROPRSS_V(1U)

#घोषणा FW_IQ_CMD_IQGTSMODE_S		14
#घोषणा FW_IQ_CMD_IQGTSMODE_V(x)	((x) << FW_IQ_CMD_IQGTSMODE_S)
#घोषणा FW_IQ_CMD_IQGTSMODE_F		FW_IQ_CMD_IQGTSMODE_V(1U)

#घोषणा FW_IQ_CMD_IQPCIECH_S	12
#घोषणा FW_IQ_CMD_IQPCIECH_V(x)	((x) << FW_IQ_CMD_IQPCIECH_S)

#घोषणा FW_IQ_CMD_IQDCAEN_S	11
#घोषणा FW_IQ_CMD_IQDCAEN_V(x)	((x) << FW_IQ_CMD_IQDCAEN_S)

#घोषणा FW_IQ_CMD_IQDCACPU_S	6
#घोषणा FW_IQ_CMD_IQDCACPU_V(x)	((x) << FW_IQ_CMD_IQDCACPU_S)

#घोषणा FW_IQ_CMD_IQINTCNTTHRESH_S	4
#घोषणा FW_IQ_CMD_IQINTCNTTHRESH_V(x)	((x) << FW_IQ_CMD_IQINTCNTTHRESH_S)

#घोषणा FW_IQ_CMD_IQO_S		3
#घोषणा FW_IQ_CMD_IQO_V(x)	((x) << FW_IQ_CMD_IQO_S)
#घोषणा FW_IQ_CMD_IQO_F		FW_IQ_CMD_IQO_V(1U)

#घोषणा FW_IQ_CMD_IQCPRIO_S	2
#घोषणा FW_IQ_CMD_IQCPRIO_V(x)	((x) << FW_IQ_CMD_IQCPRIO_S)

#घोषणा FW_IQ_CMD_IQESIZE_S	0
#घोषणा FW_IQ_CMD_IQESIZE_V(x)	((x) << FW_IQ_CMD_IQESIZE_S)

#घोषणा FW_IQ_CMD_IQNS_S	31
#घोषणा FW_IQ_CMD_IQNS_V(x)	((x) << FW_IQ_CMD_IQNS_S)

#घोषणा FW_IQ_CMD_IQRO_S	30
#घोषणा FW_IQ_CMD_IQRO_V(x)	((x) << FW_IQ_CMD_IQRO_S)

#घोषणा FW_IQ_CMD_IQFLINTIQHSEN_S	28
#घोषणा FW_IQ_CMD_IQFLINTIQHSEN_V(x)	((x) << FW_IQ_CMD_IQFLINTIQHSEN_S)

#घोषणा FW_IQ_CMD_IQFLINTCONGEN_S	27
#घोषणा FW_IQ_CMD_IQFLINTCONGEN_V(x)	((x) << FW_IQ_CMD_IQFLINTCONGEN_S)
#घोषणा FW_IQ_CMD_IQFLINTCONGEN_F	FW_IQ_CMD_IQFLINTCONGEN_V(1U)

#घोषणा FW_IQ_CMD_IQFLINTISCSIC_S	26
#घोषणा FW_IQ_CMD_IQFLINTISCSIC_V(x)	((x) << FW_IQ_CMD_IQFLINTISCSIC_S)

#घोषणा FW_IQ_CMD_IQTYPE_S		24
#घोषणा FW_IQ_CMD_IQTYPE_M		0x3
#घोषणा FW_IQ_CMD_IQTYPE_V(x)		((x) << FW_IQ_CMD_IQTYPE_S)
#घोषणा FW_IQ_CMD_IQTYPE_G(x)		\
	(((x) >> FW_IQ_CMD_IQTYPE_S) & FW_IQ_CMD_IQTYPE_M)

#घोषणा FW_IQ_CMD_FL0CNGCHMAP_S		20
#घोषणा FW_IQ_CMD_FL0CNGCHMAP_V(x)	((x) << FW_IQ_CMD_FL0CNGCHMAP_S)

#घोषणा FW_IQ_CMD_FL0CACHELOCK_S	15
#घोषणा FW_IQ_CMD_FL0CACHELOCK_V(x)	((x) << FW_IQ_CMD_FL0CACHELOCK_S)

#घोषणा FW_IQ_CMD_FL0DBP_S	14
#घोषणा FW_IQ_CMD_FL0DBP_V(x)	((x) << FW_IQ_CMD_FL0DBP_S)

#घोषणा FW_IQ_CMD_FL0DATANS_S		13
#घोषणा FW_IQ_CMD_FL0DATANS_V(x)	((x) << FW_IQ_CMD_FL0DATANS_S)

#घोषणा FW_IQ_CMD_FL0DATARO_S		12
#घोषणा FW_IQ_CMD_FL0DATARO_V(x)	((x) << FW_IQ_CMD_FL0DATARO_S)
#घोषणा FW_IQ_CMD_FL0DATARO_F		FW_IQ_CMD_FL0DATARO_V(1U)

#घोषणा FW_IQ_CMD_FL0CONGCIF_S		11
#घोषणा FW_IQ_CMD_FL0CONGCIF_V(x)	((x) << FW_IQ_CMD_FL0CONGCIF_S)
#घोषणा FW_IQ_CMD_FL0CONGCIF_F		FW_IQ_CMD_FL0CONGCIF_V(1U)

#घोषणा FW_IQ_CMD_FL0ONCHIP_S		10
#घोषणा FW_IQ_CMD_FL0ONCHIP_V(x)	((x) << FW_IQ_CMD_FL0ONCHIP_S)

#घोषणा FW_IQ_CMD_FL0STATUSPGNS_S	9
#घोषणा FW_IQ_CMD_FL0STATUSPGNS_V(x)	((x) << FW_IQ_CMD_FL0STATUSPGNS_S)

#घोषणा FW_IQ_CMD_FL0STATUSPGRO_S	8
#घोषणा FW_IQ_CMD_FL0STATUSPGRO_V(x)	((x) << FW_IQ_CMD_FL0STATUSPGRO_S)

#घोषणा FW_IQ_CMD_FL0FETCHNS_S		7
#घोषणा FW_IQ_CMD_FL0FETCHNS_V(x)	((x) << FW_IQ_CMD_FL0FETCHNS_S)

#घोषणा FW_IQ_CMD_FL0FETCHRO_S		6
#घोषणा FW_IQ_CMD_FL0FETCHRO_V(x)	((x) << FW_IQ_CMD_FL0FETCHRO_S)
#घोषणा FW_IQ_CMD_FL0FETCHRO_F		FW_IQ_CMD_FL0FETCHRO_V(1U)

#घोषणा FW_IQ_CMD_FL0HOSTFCMODE_S	4
#घोषणा FW_IQ_CMD_FL0HOSTFCMODE_V(x)	((x) << FW_IQ_CMD_FL0HOSTFCMODE_S)

#घोषणा FW_IQ_CMD_FL0CPRIO_S	3
#घोषणा FW_IQ_CMD_FL0CPRIO_V(x)	((x) << FW_IQ_CMD_FL0CPRIO_S)

#घोषणा FW_IQ_CMD_FL0PADEN_S	2
#घोषणा FW_IQ_CMD_FL0PADEN_V(x)	((x) << FW_IQ_CMD_FL0PADEN_S)
#घोषणा FW_IQ_CMD_FL0PADEN_F	FW_IQ_CMD_FL0PADEN_V(1U)

#घोषणा FW_IQ_CMD_FL0PACKEN_S		1
#घोषणा FW_IQ_CMD_FL0PACKEN_V(x)	((x) << FW_IQ_CMD_FL0PACKEN_S)
#घोषणा FW_IQ_CMD_FL0PACKEN_F		FW_IQ_CMD_FL0PACKEN_V(1U)

#घोषणा FW_IQ_CMD_FL0CONGEN_S		0
#घोषणा FW_IQ_CMD_FL0CONGEN_V(x)	((x) << FW_IQ_CMD_FL0CONGEN_S)
#घोषणा FW_IQ_CMD_FL0CONGEN_F		FW_IQ_CMD_FL0CONGEN_V(1U)

#घोषणा FW_IQ_CMD_FL0DCAEN_S	15
#घोषणा FW_IQ_CMD_FL0DCAEN_V(x)	((x) << FW_IQ_CMD_FL0DCAEN_S)

#घोषणा FW_IQ_CMD_FL0DCACPU_S		10
#घोषणा FW_IQ_CMD_FL0DCACPU_V(x)	((x) << FW_IQ_CMD_FL0DCACPU_S)

#घोषणा FW_IQ_CMD_FL0FBMIN_S	7
#घोषणा FW_IQ_CMD_FL0FBMIN_V(x)	((x) << FW_IQ_CMD_FL0FBMIN_S)

#घोषणा FW_IQ_CMD_FL0FBMAX_S	4
#घोषणा FW_IQ_CMD_FL0FBMAX_V(x)	((x) << FW_IQ_CMD_FL0FBMAX_S)

#घोषणा FW_IQ_CMD_FL0CIDXFTHRESHO_S	3
#घोषणा FW_IQ_CMD_FL0CIDXFTHRESHO_V(x)	((x) << FW_IQ_CMD_FL0CIDXFTHRESHO_S)
#घोषणा FW_IQ_CMD_FL0CIDXFTHRESHO_F	FW_IQ_CMD_FL0CIDXFTHRESHO_V(1U)

#घोषणा FW_IQ_CMD_FL0CIDXFTHRESH_S	0
#घोषणा FW_IQ_CMD_FL0CIDXFTHRESH_V(x)	((x) << FW_IQ_CMD_FL0CIDXFTHRESH_S)

#घोषणा FW_IQ_CMD_FL1CNGCHMAP_S		20
#घोषणा FW_IQ_CMD_FL1CNGCHMAP_V(x)	((x) << FW_IQ_CMD_FL1CNGCHMAP_S)

#घोषणा FW_IQ_CMD_FL1CACHELOCK_S	15
#घोषणा FW_IQ_CMD_FL1CACHELOCK_V(x)	((x) << FW_IQ_CMD_FL1CACHELOCK_S)

#घोषणा FW_IQ_CMD_FL1DBP_S	14
#घोषणा FW_IQ_CMD_FL1DBP_V(x)	((x) << FW_IQ_CMD_FL1DBP_S)

#घोषणा FW_IQ_CMD_FL1DATANS_S		13
#घोषणा FW_IQ_CMD_FL1DATANS_V(x)	((x) << FW_IQ_CMD_FL1DATANS_S)

#घोषणा FW_IQ_CMD_FL1DATARO_S		12
#घोषणा FW_IQ_CMD_FL1DATARO_V(x)	((x) << FW_IQ_CMD_FL1DATARO_S)

#घोषणा FW_IQ_CMD_FL1CONGCIF_S		11
#घोषणा FW_IQ_CMD_FL1CONGCIF_V(x)	((x) << FW_IQ_CMD_FL1CONGCIF_S)

#घोषणा FW_IQ_CMD_FL1ONCHIP_S		10
#घोषणा FW_IQ_CMD_FL1ONCHIP_V(x)	((x) << FW_IQ_CMD_FL1ONCHIP_S)

#घोषणा FW_IQ_CMD_FL1STATUSPGNS_S	9
#घोषणा FW_IQ_CMD_FL1STATUSPGNS_V(x)	((x) << FW_IQ_CMD_FL1STATUSPGNS_S)

#घोषणा FW_IQ_CMD_FL1STATUSPGRO_S	8
#घोषणा FW_IQ_CMD_FL1STATUSPGRO_V(x)	((x) << FW_IQ_CMD_FL1STATUSPGRO_S)

#घोषणा FW_IQ_CMD_FL1FETCHNS_S		7
#घोषणा FW_IQ_CMD_FL1FETCHNS_V(x)	((x) << FW_IQ_CMD_FL1FETCHNS_S)

#घोषणा FW_IQ_CMD_FL1FETCHRO_S		6
#घोषणा FW_IQ_CMD_FL1FETCHRO_V(x)	((x) << FW_IQ_CMD_FL1FETCHRO_S)

#घोषणा FW_IQ_CMD_FL1HOSTFCMODE_S	4
#घोषणा FW_IQ_CMD_FL1HOSTFCMODE_V(x)	((x) << FW_IQ_CMD_FL1HOSTFCMODE_S)

#घोषणा FW_IQ_CMD_FL1CPRIO_S	3
#घोषणा FW_IQ_CMD_FL1CPRIO_V(x)	((x) << FW_IQ_CMD_FL1CPRIO_S)

#घोषणा FW_IQ_CMD_FL1PADEN_S	2
#घोषणा FW_IQ_CMD_FL1PADEN_V(x)	((x) << FW_IQ_CMD_FL1PADEN_S)
#घोषणा FW_IQ_CMD_FL1PADEN_F	FW_IQ_CMD_FL1PADEN_V(1U)

#घोषणा FW_IQ_CMD_FL1PACKEN_S		1
#घोषणा FW_IQ_CMD_FL1PACKEN_V(x)	((x) << FW_IQ_CMD_FL1PACKEN_S)
#घोषणा FW_IQ_CMD_FL1PACKEN_F	FW_IQ_CMD_FL1PACKEN_V(1U)

#घोषणा FW_IQ_CMD_FL1CONGEN_S		0
#घोषणा FW_IQ_CMD_FL1CONGEN_V(x)	((x) << FW_IQ_CMD_FL1CONGEN_S)
#घोषणा FW_IQ_CMD_FL1CONGEN_F	FW_IQ_CMD_FL1CONGEN_V(1U)

#घोषणा FW_IQ_CMD_FL1DCAEN_S	15
#घोषणा FW_IQ_CMD_FL1DCAEN_V(x)	((x) << FW_IQ_CMD_FL1DCAEN_S)

#घोषणा FW_IQ_CMD_FL1DCACPU_S		10
#घोषणा FW_IQ_CMD_FL1DCACPU_V(x)	((x) << FW_IQ_CMD_FL1DCACPU_S)

#घोषणा FW_IQ_CMD_FL1FBMIN_S	7
#घोषणा FW_IQ_CMD_FL1FBMIN_V(x)	((x) << FW_IQ_CMD_FL1FBMIN_S)

#घोषणा FW_IQ_CMD_FL1FBMAX_S	4
#घोषणा FW_IQ_CMD_FL1FBMAX_V(x)	((x) << FW_IQ_CMD_FL1FBMAX_S)

#घोषणा FW_IQ_CMD_FL1CIDXFTHRESHO_S	3
#घोषणा FW_IQ_CMD_FL1CIDXFTHRESHO_V(x)	((x) << FW_IQ_CMD_FL1CIDXFTHRESHO_S)
#घोषणा FW_IQ_CMD_FL1CIDXFTHRESHO_F	FW_IQ_CMD_FL1CIDXFTHRESHO_V(1U)

#घोषणा FW_IQ_CMD_FL1CIDXFTHRESH_S	0
#घोषणा FW_IQ_CMD_FL1CIDXFTHRESH_V(x)	((x) << FW_IQ_CMD_FL1CIDXFTHRESH_S)

काष्ठा fw_eq_eth_cmd अणु
	__be32 op_to_vfn;
	__be32 alloc_to_len16;
	__be32 eqid_pkd;
	__be32 physeqid_pkd;
	__be32 fetchszm_to_iqid;
	__be32 dcaen_to_eqsize;
	__be64 eqaddr;
	__be32 स्वतःequiqe_to_viid;
	__be32 समयren_समयrix;
	__be64 r9;
पूर्ण;

#घोषणा FW_EQ_ETH_CMD_PFN_S	8
#घोषणा FW_EQ_ETH_CMD_PFN_V(x)	((x) << FW_EQ_ETH_CMD_PFN_S)

#घोषणा FW_EQ_ETH_CMD_VFN_S	0
#घोषणा FW_EQ_ETH_CMD_VFN_V(x)	((x) << FW_EQ_ETH_CMD_VFN_S)

#घोषणा FW_EQ_ETH_CMD_ALLOC_S		31
#घोषणा FW_EQ_ETH_CMD_ALLOC_V(x)	((x) << FW_EQ_ETH_CMD_ALLOC_S)
#घोषणा FW_EQ_ETH_CMD_ALLOC_F	FW_EQ_ETH_CMD_ALLOC_V(1U)

#घोषणा FW_EQ_ETH_CMD_FREE_S	30
#घोषणा FW_EQ_ETH_CMD_FREE_V(x)	((x) << FW_EQ_ETH_CMD_FREE_S)
#घोषणा FW_EQ_ETH_CMD_FREE_F	FW_EQ_ETH_CMD_FREE_V(1U)

#घोषणा FW_EQ_ETH_CMD_MODIFY_S		29
#घोषणा FW_EQ_ETH_CMD_MODIFY_V(x)	((x) << FW_EQ_ETH_CMD_MODIFY_S)
#घोषणा FW_EQ_ETH_CMD_MODIFY_F	FW_EQ_ETH_CMD_MODIFY_V(1U)

#घोषणा FW_EQ_ETH_CMD_EQSTART_S		28
#घोषणा FW_EQ_ETH_CMD_EQSTART_V(x)	((x) << FW_EQ_ETH_CMD_EQSTART_S)
#घोषणा FW_EQ_ETH_CMD_EQSTART_F	FW_EQ_ETH_CMD_EQSTART_V(1U)

#घोषणा FW_EQ_ETH_CMD_EQSTOP_S		27
#घोषणा FW_EQ_ETH_CMD_EQSTOP_V(x)	((x) << FW_EQ_ETH_CMD_EQSTOP_S)
#घोषणा FW_EQ_ETH_CMD_EQSTOP_F	FW_EQ_ETH_CMD_EQSTOP_V(1U)

#घोषणा FW_EQ_ETH_CMD_EQID_S	0
#घोषणा FW_EQ_ETH_CMD_EQID_M	0xfffff
#घोषणा FW_EQ_ETH_CMD_EQID_V(x)	((x) << FW_EQ_ETH_CMD_EQID_S)
#घोषणा FW_EQ_ETH_CMD_EQID_G(x)	\
	(((x) >> FW_EQ_ETH_CMD_EQID_S) & FW_EQ_ETH_CMD_EQID_M)

#घोषणा FW_EQ_ETH_CMD_PHYSEQID_S	0
#घोषणा FW_EQ_ETH_CMD_PHYSEQID_M	0xfffff
#घोषणा FW_EQ_ETH_CMD_PHYSEQID_V(x)	((x) << FW_EQ_ETH_CMD_PHYSEQID_S)
#घोषणा FW_EQ_ETH_CMD_PHYSEQID_G(x)	\
	(((x) >> FW_EQ_ETH_CMD_PHYSEQID_S) & FW_EQ_ETH_CMD_PHYSEQID_M)

#घोषणा FW_EQ_ETH_CMD_FETCHSZM_S	26
#घोषणा FW_EQ_ETH_CMD_FETCHSZM_V(x)	((x) << FW_EQ_ETH_CMD_FETCHSZM_S)
#घोषणा FW_EQ_ETH_CMD_FETCHSZM_F	FW_EQ_ETH_CMD_FETCHSZM_V(1U)

#घोषणा FW_EQ_ETH_CMD_STATUSPGNS_S	25
#घोषणा FW_EQ_ETH_CMD_STATUSPGNS_V(x)	((x) << FW_EQ_ETH_CMD_STATUSPGNS_S)

#घोषणा FW_EQ_ETH_CMD_STATUSPGRO_S	24
#घोषणा FW_EQ_ETH_CMD_STATUSPGRO_V(x)	((x) << FW_EQ_ETH_CMD_STATUSPGRO_S)

#घोषणा FW_EQ_ETH_CMD_FETCHNS_S		23
#घोषणा FW_EQ_ETH_CMD_FETCHNS_V(x)	((x) << FW_EQ_ETH_CMD_FETCHNS_S)

#घोषणा FW_EQ_ETH_CMD_FETCHRO_S		22
#घोषणा FW_EQ_ETH_CMD_FETCHRO_V(x)	((x) << FW_EQ_ETH_CMD_FETCHRO_S)
#घोषणा FW_EQ_ETH_CMD_FETCHRO_F		FW_EQ_ETH_CMD_FETCHRO_V(1U)

#घोषणा FW_EQ_ETH_CMD_HOSTFCMODE_S	20
#घोषणा FW_EQ_ETH_CMD_HOSTFCMODE_V(x)	((x) << FW_EQ_ETH_CMD_HOSTFCMODE_S)

#घोषणा FW_EQ_ETH_CMD_CPRIO_S		19
#घोषणा FW_EQ_ETH_CMD_CPRIO_V(x)	((x) << FW_EQ_ETH_CMD_CPRIO_S)

#घोषणा FW_EQ_ETH_CMD_ONCHIP_S		18
#घोषणा FW_EQ_ETH_CMD_ONCHIP_V(x)	((x) << FW_EQ_ETH_CMD_ONCHIP_S)

#घोषणा FW_EQ_ETH_CMD_PCIECHN_S		16
#घोषणा FW_EQ_ETH_CMD_PCIECHN_V(x)	((x) << FW_EQ_ETH_CMD_PCIECHN_S)

#घोषणा FW_EQ_ETH_CMD_IQID_S	0
#घोषणा FW_EQ_ETH_CMD_IQID_V(x)	((x) << FW_EQ_ETH_CMD_IQID_S)

#घोषणा FW_EQ_ETH_CMD_DCAEN_S		31
#घोषणा FW_EQ_ETH_CMD_DCAEN_V(x)	((x) << FW_EQ_ETH_CMD_DCAEN_S)

#घोषणा FW_EQ_ETH_CMD_DCACPU_S		26
#घोषणा FW_EQ_ETH_CMD_DCACPU_V(x)	((x) << FW_EQ_ETH_CMD_DCACPU_S)

#घोषणा FW_EQ_ETH_CMD_FBMIN_S		23
#घोषणा FW_EQ_ETH_CMD_FBMIN_V(x)	((x) << FW_EQ_ETH_CMD_FBMIN_S)

#घोषणा FW_EQ_ETH_CMD_FBMAX_S		20
#घोषणा FW_EQ_ETH_CMD_FBMAX_V(x)	((x) << FW_EQ_ETH_CMD_FBMAX_S)

#घोषणा FW_EQ_ETH_CMD_CIDXFTHRESHO_S	19
#घोषणा FW_EQ_ETH_CMD_CIDXFTHRESHO_V(x)	((x) << FW_EQ_ETH_CMD_CIDXFTHRESHO_S)

#घोषणा FW_EQ_ETH_CMD_CIDXFTHRESH_S	16
#घोषणा FW_EQ_ETH_CMD_CIDXFTHRESH_V(x)	((x) << FW_EQ_ETH_CMD_CIDXFTHRESH_S)

#घोषणा FW_EQ_ETH_CMD_EQSIZE_S		0
#घोषणा FW_EQ_ETH_CMD_EQSIZE_V(x)	((x) << FW_EQ_ETH_CMD_EQSIZE_S)

#घोषणा FW_EQ_ETH_CMD_AUTOEQUIQE_S	31
#घोषणा FW_EQ_ETH_CMD_AUTOEQUIQE_V(x)	((x) << FW_EQ_ETH_CMD_AUTOEQUIQE_S)
#घोषणा FW_EQ_ETH_CMD_AUTOEQUIQE_F	FW_EQ_ETH_CMD_AUTOEQUIQE_V(1U)

#घोषणा FW_EQ_ETH_CMD_AUTOEQUEQE_S	30
#घोषणा FW_EQ_ETH_CMD_AUTOEQUEQE_V(x)	((x) << FW_EQ_ETH_CMD_AUTOEQUEQE_S)
#घोषणा FW_EQ_ETH_CMD_AUTOEQUEQE_F	FW_EQ_ETH_CMD_AUTOEQUEQE_V(1U)

#घोषणा FW_EQ_ETH_CMD_VIID_S	16
#घोषणा FW_EQ_ETH_CMD_VIID_V(x)	((x) << FW_EQ_ETH_CMD_VIID_S)

#घोषणा FW_EQ_ETH_CMD_TIMEREN_S		3
#घोषणा FW_EQ_ETH_CMD_TIMEREN_M		0x1
#घोषणा FW_EQ_ETH_CMD_TIMEREN_V(x)	((x) << FW_EQ_ETH_CMD_TIMEREN_S)
#घोषणा FW_EQ_ETH_CMD_TIMEREN_G(x)	\
    (((x) >> FW_EQ_ETH_CMD_TIMEREN_S) & FW_EQ_ETH_CMD_TIMEREN_M)
#घोषणा FW_EQ_ETH_CMD_TIMEREN_F	FW_EQ_ETH_CMD_TIMEREN_V(1U)

#घोषणा FW_EQ_ETH_CMD_TIMERIX_S		0
#घोषणा FW_EQ_ETH_CMD_TIMERIX_M		0x7
#घोषणा FW_EQ_ETH_CMD_TIMERIX_V(x)	((x) << FW_EQ_ETH_CMD_TIMERIX_S)
#घोषणा FW_EQ_ETH_CMD_TIMERIX_G(x)	\
    (((x) >> FW_EQ_ETH_CMD_TIMERIX_S) & FW_EQ_ETH_CMD_TIMERIX_M)

काष्ठा fw_eq_ctrl_cmd अणु
	__be32 op_to_vfn;
	__be32 alloc_to_len16;
	__be32 cmpliqid_eqid;
	__be32 physeqid_pkd;
	__be32 fetchszm_to_iqid;
	__be32 dcaen_to_eqsize;
	__be64 eqaddr;
पूर्ण;

#घोषणा FW_EQ_CTRL_CMD_PFN_S	8
#घोषणा FW_EQ_CTRL_CMD_PFN_V(x)	((x) << FW_EQ_CTRL_CMD_PFN_S)

#घोषणा FW_EQ_CTRL_CMD_VFN_S	0
#घोषणा FW_EQ_CTRL_CMD_VFN_V(x)	((x) << FW_EQ_CTRL_CMD_VFN_S)

#घोषणा FW_EQ_CTRL_CMD_ALLOC_S		31
#घोषणा FW_EQ_CTRL_CMD_ALLOC_V(x)	((x) << FW_EQ_CTRL_CMD_ALLOC_S)
#घोषणा FW_EQ_CTRL_CMD_ALLOC_F		FW_EQ_CTRL_CMD_ALLOC_V(1U)

#घोषणा FW_EQ_CTRL_CMD_FREE_S		30
#घोषणा FW_EQ_CTRL_CMD_FREE_V(x)	((x) << FW_EQ_CTRL_CMD_FREE_S)
#घोषणा FW_EQ_CTRL_CMD_FREE_F		FW_EQ_CTRL_CMD_FREE_V(1U)

#घोषणा FW_EQ_CTRL_CMD_MODIFY_S		29
#घोषणा FW_EQ_CTRL_CMD_MODIFY_V(x)	((x) << FW_EQ_CTRL_CMD_MODIFY_S)
#घोषणा FW_EQ_CTRL_CMD_MODIFY_F		FW_EQ_CTRL_CMD_MODIFY_V(1U)

#घोषणा FW_EQ_CTRL_CMD_EQSTART_S	28
#घोषणा FW_EQ_CTRL_CMD_EQSTART_V(x)	((x) << FW_EQ_CTRL_CMD_EQSTART_S)
#घोषणा FW_EQ_CTRL_CMD_EQSTART_F	FW_EQ_CTRL_CMD_EQSTART_V(1U)

#घोषणा FW_EQ_CTRL_CMD_EQSTOP_S		27
#घोषणा FW_EQ_CTRL_CMD_EQSTOP_V(x)	((x) << FW_EQ_CTRL_CMD_EQSTOP_S)
#घोषणा FW_EQ_CTRL_CMD_EQSTOP_F		FW_EQ_CTRL_CMD_EQSTOP_V(1U)

#घोषणा FW_EQ_CTRL_CMD_CMPLIQID_S	20
#घोषणा FW_EQ_CTRL_CMD_CMPLIQID_V(x)	((x) << FW_EQ_CTRL_CMD_CMPLIQID_S)

#घोषणा FW_EQ_CTRL_CMD_EQID_S		0
#घोषणा FW_EQ_CTRL_CMD_EQID_M		0xfffff
#घोषणा FW_EQ_CTRL_CMD_EQID_V(x)	((x) << FW_EQ_CTRL_CMD_EQID_S)
#घोषणा FW_EQ_CTRL_CMD_EQID_G(x)	\
	(((x) >> FW_EQ_CTRL_CMD_EQID_S) & FW_EQ_CTRL_CMD_EQID_M)

#घोषणा FW_EQ_CTRL_CMD_PHYSEQID_S	0
#घोषणा FW_EQ_CTRL_CMD_PHYSEQID_M	0xfffff
#घोषणा FW_EQ_CTRL_CMD_PHYSEQID_G(x)	\
	(((x) >> FW_EQ_CTRL_CMD_PHYSEQID_S) & FW_EQ_CTRL_CMD_PHYSEQID_M)

#घोषणा FW_EQ_CTRL_CMD_FETCHSZM_S	26
#घोषणा FW_EQ_CTRL_CMD_FETCHSZM_V(x)	((x) << FW_EQ_CTRL_CMD_FETCHSZM_S)
#घोषणा FW_EQ_CTRL_CMD_FETCHSZM_F	FW_EQ_CTRL_CMD_FETCHSZM_V(1U)

#घोषणा FW_EQ_CTRL_CMD_STATUSPGNS_S	25
#घोषणा FW_EQ_CTRL_CMD_STATUSPGNS_V(x)	((x) << FW_EQ_CTRL_CMD_STATUSPGNS_S)
#घोषणा FW_EQ_CTRL_CMD_STATUSPGNS_F	FW_EQ_CTRL_CMD_STATUSPGNS_V(1U)

#घोषणा FW_EQ_CTRL_CMD_STATUSPGRO_S	24
#घोषणा FW_EQ_CTRL_CMD_STATUSPGRO_V(x)	((x) << FW_EQ_CTRL_CMD_STATUSPGRO_S)
#घोषणा FW_EQ_CTRL_CMD_STATUSPGRO_F	FW_EQ_CTRL_CMD_STATUSPGRO_V(1U)

#घोषणा FW_EQ_CTRL_CMD_FETCHNS_S	23
#घोषणा FW_EQ_CTRL_CMD_FETCHNS_V(x)	((x) << FW_EQ_CTRL_CMD_FETCHNS_S)
#घोषणा FW_EQ_CTRL_CMD_FETCHNS_F	FW_EQ_CTRL_CMD_FETCHNS_V(1U)

#घोषणा FW_EQ_CTRL_CMD_FETCHRO_S	22
#घोषणा FW_EQ_CTRL_CMD_FETCHRO_V(x)	((x) << FW_EQ_CTRL_CMD_FETCHRO_S)
#घोषणा FW_EQ_CTRL_CMD_FETCHRO_F	FW_EQ_CTRL_CMD_FETCHRO_V(1U)

#घोषणा FW_EQ_CTRL_CMD_HOSTFCMODE_S	20
#घोषणा FW_EQ_CTRL_CMD_HOSTFCMODE_V(x)	((x) << FW_EQ_CTRL_CMD_HOSTFCMODE_S)

#घोषणा FW_EQ_CTRL_CMD_CPRIO_S		19
#घोषणा FW_EQ_CTRL_CMD_CPRIO_V(x)	((x) << FW_EQ_CTRL_CMD_CPRIO_S)

#घोषणा FW_EQ_CTRL_CMD_ONCHIP_S		18
#घोषणा FW_EQ_CTRL_CMD_ONCHIP_V(x)	((x) << FW_EQ_CTRL_CMD_ONCHIP_S)

#घोषणा FW_EQ_CTRL_CMD_PCIECHN_S	16
#घोषणा FW_EQ_CTRL_CMD_PCIECHN_V(x)	((x) << FW_EQ_CTRL_CMD_PCIECHN_S)

#घोषणा FW_EQ_CTRL_CMD_IQID_S		0
#घोषणा FW_EQ_CTRL_CMD_IQID_V(x)	((x) << FW_EQ_CTRL_CMD_IQID_S)

#घोषणा FW_EQ_CTRL_CMD_DCAEN_S		31
#घोषणा FW_EQ_CTRL_CMD_DCAEN_V(x)	((x) << FW_EQ_CTRL_CMD_DCAEN_S)

#घोषणा FW_EQ_CTRL_CMD_DCACPU_S		26
#घोषणा FW_EQ_CTRL_CMD_DCACPU_V(x)	((x) << FW_EQ_CTRL_CMD_DCACPU_S)

#घोषणा FW_EQ_CTRL_CMD_FBMIN_S		23
#घोषणा FW_EQ_CTRL_CMD_FBMIN_V(x)	((x) << FW_EQ_CTRL_CMD_FBMIN_S)

#घोषणा FW_EQ_CTRL_CMD_FBMAX_S		20
#घोषणा FW_EQ_CTRL_CMD_FBMAX_V(x)	((x) << FW_EQ_CTRL_CMD_FBMAX_S)

#घोषणा FW_EQ_CTRL_CMD_CIDXFTHRESHO_S		19
#घोषणा FW_EQ_CTRL_CMD_CIDXFTHRESHO_V(x)	\
	((x) << FW_EQ_CTRL_CMD_CIDXFTHRESHO_S)

#घोषणा FW_EQ_CTRL_CMD_CIDXFTHRESH_S	16
#घोषणा FW_EQ_CTRL_CMD_CIDXFTHRESH_V(x)	((x) << FW_EQ_CTRL_CMD_CIDXFTHRESH_S)

#घोषणा FW_EQ_CTRL_CMD_EQSIZE_S		0
#घोषणा FW_EQ_CTRL_CMD_EQSIZE_V(x)	((x) << FW_EQ_CTRL_CMD_EQSIZE_S)

काष्ठा fw_eq_ofld_cmd अणु
	__be32 op_to_vfn;
	__be32 alloc_to_len16;
	__be32 eqid_pkd;
	__be32 physeqid_pkd;
	__be32 fetchszm_to_iqid;
	__be32 dcaen_to_eqsize;
	__be64 eqaddr;
पूर्ण;

#घोषणा FW_EQ_OFLD_CMD_PFN_S	8
#घोषणा FW_EQ_OFLD_CMD_PFN_V(x)	((x) << FW_EQ_OFLD_CMD_PFN_S)

#घोषणा FW_EQ_OFLD_CMD_VFN_S	0
#घोषणा FW_EQ_OFLD_CMD_VFN_V(x)	((x) << FW_EQ_OFLD_CMD_VFN_S)

#घोषणा FW_EQ_OFLD_CMD_ALLOC_S		31
#घोषणा FW_EQ_OFLD_CMD_ALLOC_V(x)	((x) << FW_EQ_OFLD_CMD_ALLOC_S)
#घोषणा FW_EQ_OFLD_CMD_ALLOC_F		FW_EQ_OFLD_CMD_ALLOC_V(1U)

#घोषणा FW_EQ_OFLD_CMD_FREE_S		30
#घोषणा FW_EQ_OFLD_CMD_FREE_V(x)	((x) << FW_EQ_OFLD_CMD_FREE_S)
#घोषणा FW_EQ_OFLD_CMD_FREE_F		FW_EQ_OFLD_CMD_FREE_V(1U)

#घोषणा FW_EQ_OFLD_CMD_MODIFY_S		29
#घोषणा FW_EQ_OFLD_CMD_MODIFY_V(x)	((x) << FW_EQ_OFLD_CMD_MODIFY_S)
#घोषणा FW_EQ_OFLD_CMD_MODIFY_F		FW_EQ_OFLD_CMD_MODIFY_V(1U)

#घोषणा FW_EQ_OFLD_CMD_EQSTART_S	28
#घोषणा FW_EQ_OFLD_CMD_EQSTART_V(x)	((x) << FW_EQ_OFLD_CMD_EQSTART_S)
#घोषणा FW_EQ_OFLD_CMD_EQSTART_F	FW_EQ_OFLD_CMD_EQSTART_V(1U)

#घोषणा FW_EQ_OFLD_CMD_EQSTOP_S		27
#घोषणा FW_EQ_OFLD_CMD_EQSTOP_V(x)	((x) << FW_EQ_OFLD_CMD_EQSTOP_S)
#घोषणा FW_EQ_OFLD_CMD_EQSTOP_F		FW_EQ_OFLD_CMD_EQSTOP_V(1U)

#घोषणा FW_EQ_OFLD_CMD_EQID_S		0
#घोषणा FW_EQ_OFLD_CMD_EQID_M		0xfffff
#घोषणा FW_EQ_OFLD_CMD_EQID_V(x)	((x) << FW_EQ_OFLD_CMD_EQID_S)
#घोषणा FW_EQ_OFLD_CMD_EQID_G(x)	\
	(((x) >> FW_EQ_OFLD_CMD_EQID_S) & FW_EQ_OFLD_CMD_EQID_M)

#घोषणा FW_EQ_OFLD_CMD_PHYSEQID_S	0
#घोषणा FW_EQ_OFLD_CMD_PHYSEQID_M	0xfffff
#घोषणा FW_EQ_OFLD_CMD_PHYSEQID_G(x)	\
	(((x) >> FW_EQ_OFLD_CMD_PHYSEQID_S) & FW_EQ_OFLD_CMD_PHYSEQID_M)

#घोषणा FW_EQ_OFLD_CMD_FETCHSZM_S	26
#घोषणा FW_EQ_OFLD_CMD_FETCHSZM_V(x)	((x) << FW_EQ_OFLD_CMD_FETCHSZM_S)

#घोषणा FW_EQ_OFLD_CMD_STATUSPGNS_S	25
#घोषणा FW_EQ_OFLD_CMD_STATUSPGNS_V(x)	((x) << FW_EQ_OFLD_CMD_STATUSPGNS_S)

#घोषणा FW_EQ_OFLD_CMD_STATUSPGRO_S	24
#घोषणा FW_EQ_OFLD_CMD_STATUSPGRO_V(x)	((x) << FW_EQ_OFLD_CMD_STATUSPGRO_S)

#घोषणा FW_EQ_OFLD_CMD_FETCHNS_S	23
#घोषणा FW_EQ_OFLD_CMD_FETCHNS_V(x)	((x) << FW_EQ_OFLD_CMD_FETCHNS_S)

#घोषणा FW_EQ_OFLD_CMD_FETCHRO_S	22
#घोषणा FW_EQ_OFLD_CMD_FETCHRO_V(x)	((x) << FW_EQ_OFLD_CMD_FETCHRO_S)
#घोषणा FW_EQ_OFLD_CMD_FETCHRO_F	FW_EQ_OFLD_CMD_FETCHRO_V(1U)

#घोषणा FW_EQ_OFLD_CMD_HOSTFCMODE_S	20
#घोषणा FW_EQ_OFLD_CMD_HOSTFCMODE_V(x)	((x) << FW_EQ_OFLD_CMD_HOSTFCMODE_S)

#घोषणा FW_EQ_OFLD_CMD_CPRIO_S		19
#घोषणा FW_EQ_OFLD_CMD_CPRIO_V(x)	((x) << FW_EQ_OFLD_CMD_CPRIO_S)

#घोषणा FW_EQ_OFLD_CMD_ONCHIP_S		18
#घोषणा FW_EQ_OFLD_CMD_ONCHIP_V(x)	((x) << FW_EQ_OFLD_CMD_ONCHIP_S)

#घोषणा FW_EQ_OFLD_CMD_PCIECHN_S	16
#घोषणा FW_EQ_OFLD_CMD_PCIECHN_V(x)	((x) << FW_EQ_OFLD_CMD_PCIECHN_S)

#घोषणा FW_EQ_OFLD_CMD_IQID_S		0
#घोषणा FW_EQ_OFLD_CMD_IQID_V(x)	((x) << FW_EQ_OFLD_CMD_IQID_S)

#घोषणा FW_EQ_OFLD_CMD_DCAEN_S		31
#घोषणा FW_EQ_OFLD_CMD_DCAEN_V(x)	((x) << FW_EQ_OFLD_CMD_DCAEN_S)

#घोषणा FW_EQ_OFLD_CMD_DCACPU_S		26
#घोषणा FW_EQ_OFLD_CMD_DCACPU_V(x)	((x) << FW_EQ_OFLD_CMD_DCACPU_S)

#घोषणा FW_EQ_OFLD_CMD_FBMIN_S		23
#घोषणा FW_EQ_OFLD_CMD_FBMIN_V(x)	((x) << FW_EQ_OFLD_CMD_FBMIN_S)

#घोषणा FW_EQ_OFLD_CMD_FBMAX_S		20
#घोषणा FW_EQ_OFLD_CMD_FBMAX_V(x)	((x) << FW_EQ_OFLD_CMD_FBMAX_S)

#घोषणा FW_EQ_OFLD_CMD_CIDXFTHRESHO_S		19
#घोषणा FW_EQ_OFLD_CMD_CIDXFTHRESHO_V(x)	\
	((x) << FW_EQ_OFLD_CMD_CIDXFTHRESHO_S)

#घोषणा FW_EQ_OFLD_CMD_CIDXFTHRESH_S	16
#घोषणा FW_EQ_OFLD_CMD_CIDXFTHRESH_V(x)	((x) << FW_EQ_OFLD_CMD_CIDXFTHRESH_S)

#घोषणा FW_EQ_OFLD_CMD_EQSIZE_S		0
#घोषणा FW_EQ_OFLD_CMD_EQSIZE_V(x)	((x) << FW_EQ_OFLD_CMD_EQSIZE_S)

/*
 * Macros क्रम VIID parsing:
 * VIID - [10:8] PFN, [7] VI Valid, [6:0] VI number
 */

#घोषणा FW_VIID_PFN_S           8
#घोषणा FW_VIID_PFN_M           0x7
#घोषणा FW_VIID_PFN_G(x)        (((x) >> FW_VIID_PFN_S) & FW_VIID_PFN_M)

#घोषणा FW_VIID_VIVLD_S		7
#घोषणा FW_VIID_VIVLD_M		0x1
#घोषणा FW_VIID_VIVLD_G(x)	(((x) >> FW_VIID_VIVLD_S) & FW_VIID_VIVLD_M)

#घोषणा FW_VIID_VIN_S		0
#घोषणा FW_VIID_VIN_M		0x7F
#घोषणा FW_VIID_VIN_G(x)	(((x) >> FW_VIID_VIN_S) & FW_VIID_VIN_M)

काष्ठा fw_vi_cmd अणु
	__be32 op_to_vfn;
	__be32 alloc_to_len16;
	__be16 type_viid;
	u8 mac[6];
	u8 portid_pkd;
	u8 nmac;
	u8 nmac0[6];
	__be16 rsssize_pkd;
	u8 nmac1[6];
	__be16 idsiiq_pkd;
	u8 nmac2[6];
	__be16 idseiq_pkd;
	u8 nmac3[6];
	__be64 r9;
	__be64 r10;
पूर्ण;

#घोषणा FW_VI_CMD_PFN_S		8
#घोषणा FW_VI_CMD_PFN_V(x)	((x) << FW_VI_CMD_PFN_S)

#घोषणा FW_VI_CMD_VFN_S		0
#घोषणा FW_VI_CMD_VFN_V(x)	((x) << FW_VI_CMD_VFN_S)

#घोषणा FW_VI_CMD_ALLOC_S	31
#घोषणा FW_VI_CMD_ALLOC_V(x)	((x) << FW_VI_CMD_ALLOC_S)
#घोषणा FW_VI_CMD_ALLOC_F	FW_VI_CMD_ALLOC_V(1U)

#घोषणा FW_VI_CMD_FREE_S	30
#घोषणा FW_VI_CMD_FREE_V(x)	((x) << FW_VI_CMD_FREE_S)
#घोषणा FW_VI_CMD_FREE_F	FW_VI_CMD_FREE_V(1U)

#घोषणा FW_VI_CMD_VFVLD_S	24
#घोषणा FW_VI_CMD_VFVLD_M	0x1
#घोषणा FW_VI_CMD_VFVLD_V(x)	((x) << FW_VI_CMD_VFVLD_S)
#घोषणा FW_VI_CMD_VFVLD_G(x)	\
	(((x) >> FW_VI_CMD_VFVLD_S) & FW_VI_CMD_VFVLD_M)
#घोषणा FW_VI_CMD_VFVLD_F	FW_VI_CMD_VFVLD_V(1U)

#घोषणा FW_VI_CMD_VIN_S		16
#घोषणा FW_VI_CMD_VIN_M		0xff
#घोषणा FW_VI_CMD_VIN_V(x)	((x) << FW_VI_CMD_VIN_S)
#घोषणा FW_VI_CMD_VIN_G(x)	\
	(((x) >> FW_VI_CMD_VIN_S) & FW_VI_CMD_VIN_M)

#घोषणा FW_VI_CMD_VIID_S	0
#घोषणा FW_VI_CMD_VIID_M	0xfff
#घोषणा FW_VI_CMD_VIID_V(x)	((x) << FW_VI_CMD_VIID_S)
#घोषणा FW_VI_CMD_VIID_G(x)	(((x) >> FW_VI_CMD_VIID_S) & FW_VI_CMD_VIID_M)

#घोषणा FW_VI_CMD_PORTID_S	4
#घोषणा FW_VI_CMD_PORTID_M	0xf
#घोषणा FW_VI_CMD_PORTID_V(x)	((x) << FW_VI_CMD_PORTID_S)
#घोषणा FW_VI_CMD_PORTID_G(x)	\
	(((x) >> FW_VI_CMD_PORTID_S) & FW_VI_CMD_PORTID_M)

#घोषणा FW_VI_CMD_RSSSIZE_S	0
#घोषणा FW_VI_CMD_RSSSIZE_M	0x7ff
#घोषणा FW_VI_CMD_RSSSIZE_G(x)	\
	(((x) >> FW_VI_CMD_RSSSIZE_S) & FW_VI_CMD_RSSSIZE_M)

/* Special VI_MAC command index ids */
#घोषणा FW_VI_MAC_ADD_MAC		0x3FF
#घोषणा FW_VI_MAC_ADD_PERSIST_MAC	0x3FE
#घोषणा FW_VI_MAC_MAC_BASED_FREE	0x3FD
#घोषणा FW_VI_MAC_ID_BASED_FREE		0x3FC
#घोषणा FW_CLS_TCAM_NUM_ENTRIES		336

क्रमागत fw_vi_mac_smac अणु
	FW_VI_MAC_MPS_TCAM_ENTRY,
	FW_VI_MAC_MPS_TCAM_ONLY,
	FW_VI_MAC_SMT_ONLY,
	FW_VI_MAC_SMT_AND_MPSTCAM
पूर्ण;

क्रमागत fw_vi_mac_result अणु
	FW_VI_MAC_R_SUCCESS,
	FW_VI_MAC_R_F_NONEXISTENT_NOMEM,
	FW_VI_MAC_R_SMAC_FAIL,
	FW_VI_MAC_R_F_ACL_CHECK
पूर्ण;

क्रमागत fw_vi_mac_entry_types अणु
	FW_VI_MAC_TYPE_EXACTMAC,
	FW_VI_MAC_TYPE_HASHVEC,
	FW_VI_MAC_TYPE_RAW,
	FW_VI_MAC_TYPE_EXACTMAC_VNI,
पूर्ण;

काष्ठा fw_vi_mac_cmd अणु
	__be32 op_to_viid;
	__be32 मुक्तmacs_to_len16;
	जोड़ fw_vi_mac अणु
		काष्ठा fw_vi_mac_exact अणु
			__be16 valid_to_idx;
			u8 macaddr[6];
		पूर्ण exact[7];
		काष्ठा fw_vi_mac_hash अणु
			__be64 hashvec;
		पूर्ण hash;
		काष्ठा fw_vi_mac_raw अणु
			__be32 raw_idx_pkd;
			__be32 data0_pkd;
			__be32 data1[2];
			__be64 data0m_pkd;
			__be32 data1m[2];
		पूर्ण raw;
		काष्ठा fw_vi_mac_vni अणु
			__be16 valid_to_idx;
			__u8 macaddr[6];
			__be16 r7;
			__u8 macaddr_mask[6];
			__be32 lookup_type_to_vni;
			__be32 vni_mask_pkd;
		पूर्ण exact_vni[2];
	पूर्ण u;
पूर्ण;

#घोषणा FW_VI_MAC_CMD_SMTID_S		12
#घोषणा FW_VI_MAC_CMD_SMTID_M		0xff
#घोषणा FW_VI_MAC_CMD_SMTID_V(x)	((x) << FW_VI_MAC_CMD_SMTID_S)
#घोषणा FW_VI_MAC_CMD_SMTID_G(x)	\
	(((x) >> FW_VI_MAC_CMD_SMTID_S) & FW_VI_MAC_CMD_SMTID_M)

#घोषणा FW_VI_MAC_CMD_VIID_S	0
#घोषणा FW_VI_MAC_CMD_VIID_V(x)	((x) << FW_VI_MAC_CMD_VIID_S)

#घोषणा FW_VI_MAC_CMD_FREEMACS_S	31
#घोषणा FW_VI_MAC_CMD_FREEMACS_V(x)	((x) << FW_VI_MAC_CMD_FREEMACS_S)

#घोषणा FW_VI_MAC_CMD_ENTRY_TYPE_S      23
#घोषणा FW_VI_MAC_CMD_ENTRY_TYPE_M      0x7
#घोषणा FW_VI_MAC_CMD_ENTRY_TYPE_V(x)   ((x) << FW_VI_MAC_CMD_ENTRY_TYPE_S)
#घोषणा FW_VI_MAC_CMD_ENTRY_TYPE_G(x)	\
	(((x) >> FW_VI_MAC_CMD_ENTRY_TYPE_S) & FW_VI_MAC_CMD_ENTRY_TYPE_M)

#घोषणा FW_VI_MAC_CMD_HASHVECEN_S	23
#घोषणा FW_VI_MAC_CMD_HASHVECEN_V(x)	((x) << FW_VI_MAC_CMD_HASHVECEN_S)
#घोषणा FW_VI_MAC_CMD_HASHVECEN_F	FW_VI_MAC_CMD_HASHVECEN_V(1U)

#घोषणा FW_VI_MAC_CMD_HASHUNIEN_S	22
#घोषणा FW_VI_MAC_CMD_HASHUNIEN_V(x)	((x) << FW_VI_MAC_CMD_HASHUNIEN_S)

#घोषणा FW_VI_MAC_CMD_VALID_S		15
#घोषणा FW_VI_MAC_CMD_VALID_V(x)	((x) << FW_VI_MAC_CMD_VALID_S)
#घोषणा FW_VI_MAC_CMD_VALID_F	FW_VI_MAC_CMD_VALID_V(1U)

#घोषणा FW_VI_MAC_CMD_PRIO_S	12
#घोषणा FW_VI_MAC_CMD_PRIO_V(x)	((x) << FW_VI_MAC_CMD_PRIO_S)

#घोषणा FW_VI_MAC_CMD_SMAC_RESULT_S	10
#घोषणा FW_VI_MAC_CMD_SMAC_RESULT_M	0x3
#घोषणा FW_VI_MAC_CMD_SMAC_RESULT_V(x)	((x) << FW_VI_MAC_CMD_SMAC_RESULT_S)
#घोषणा FW_VI_MAC_CMD_SMAC_RESULT_G(x)	\
	(((x) >> FW_VI_MAC_CMD_SMAC_RESULT_S) & FW_VI_MAC_CMD_SMAC_RESULT_M)

#घोषणा FW_VI_MAC_CMD_IDX_S	0
#घोषणा FW_VI_MAC_CMD_IDX_M	0x3ff
#घोषणा FW_VI_MAC_CMD_IDX_V(x)	((x) << FW_VI_MAC_CMD_IDX_S)
#घोषणा FW_VI_MAC_CMD_IDX_G(x)	\
	(((x) >> FW_VI_MAC_CMD_IDX_S) & FW_VI_MAC_CMD_IDX_M)

#घोषणा FW_VI_MAC_CMD_RAW_IDX_S         16
#घोषणा FW_VI_MAC_CMD_RAW_IDX_M         0xffff
#घोषणा FW_VI_MAC_CMD_RAW_IDX_V(x)      ((x) << FW_VI_MAC_CMD_RAW_IDX_S)
#घोषणा FW_VI_MAC_CMD_RAW_IDX_G(x)      \
	(((x) >> FW_VI_MAC_CMD_RAW_IDX_S) & FW_VI_MAC_CMD_RAW_IDX_M)

#घोषणा FW_VI_MAC_CMD_LOOKUP_TYPE_S	31
#घोषणा FW_VI_MAC_CMD_LOOKUP_TYPE_M	0x1
#घोषणा FW_VI_MAC_CMD_LOOKUP_TYPE_V(x)	((x) << FW_VI_MAC_CMD_LOOKUP_TYPE_S)
#घोषणा FW_VI_MAC_CMD_LOOKUP_TYPE_G(x)	\
	(((x) >> FW_VI_MAC_CMD_LOOKUP_TYPE_S) & FW_VI_MAC_CMD_LOOKUP_TYPE_M)
#घोषणा FW_VI_MAC_CMD_LOOKUP_TYPE_F	FW_VI_MAC_CMD_LOOKUP_TYPE_V(1U)

#घोषणा FW_VI_MAC_CMD_DIP_HIT_S		30
#घोषणा FW_VI_MAC_CMD_DIP_HIT_M		0x1
#घोषणा FW_VI_MAC_CMD_DIP_HIT_V(x)	((x) << FW_VI_MAC_CMD_DIP_HIT_S)
#घोषणा FW_VI_MAC_CMD_DIP_HIT_G(x)	\
	(((x) >> FW_VI_MAC_CMD_DIP_HIT_S) & FW_VI_MAC_CMD_DIP_HIT_M)
#घोषणा FW_VI_MAC_CMD_DIP_HIT_F		FW_VI_MAC_CMD_DIP_HIT_V(1U)

#घोषणा FW_VI_MAC_CMD_VNI_S		0
#घोषणा FW_VI_MAC_CMD_VNI_M		0xffffff
#घोषणा FW_VI_MAC_CMD_VNI_V(x)		((x) << FW_VI_MAC_CMD_VNI_S)
#घोषणा FW_VI_MAC_CMD_VNI_G(x)		\
	(((x) >> FW_VI_MAC_CMD_VNI_S) & FW_VI_MAC_CMD_VNI_M)

#घोषणा FW_VI_MAC_CMD_VNI_MASK_S	0
#घोषणा FW_VI_MAC_CMD_VNI_MASK_M	0xffffff
#घोषणा FW_VI_MAC_CMD_VNI_MASK_V(x)	((x) << FW_VI_MAC_CMD_VNI_MASK_S)
#घोषणा FW_VI_MAC_CMD_VNI_MASK_G(x)	\
	(((x) >> FW_VI_MAC_CMD_VNI_MASK_S) & FW_VI_MAC_CMD_VNI_MASK_M)

#घोषणा FW_RXMODE_MTU_NO_CHG	65535

काष्ठा fw_vi_rxmode_cmd अणु
	__be32 op_to_viid;
	__be32 retval_len16;
	__be32 mtu_to_vlanexen;
	__be32 r4_lo;
पूर्ण;

#घोषणा FW_VI_RXMODE_CMD_VIID_S		0
#घोषणा FW_VI_RXMODE_CMD_VIID_V(x)	((x) << FW_VI_RXMODE_CMD_VIID_S)

#घोषणा FW_VI_RXMODE_CMD_MTU_S		16
#घोषणा FW_VI_RXMODE_CMD_MTU_M		0xffff
#घोषणा FW_VI_RXMODE_CMD_MTU_V(x)	((x) << FW_VI_RXMODE_CMD_MTU_S)

#घोषणा FW_VI_RXMODE_CMD_PROMISCEN_S	14
#घोषणा FW_VI_RXMODE_CMD_PROMISCEN_M	0x3
#घोषणा FW_VI_RXMODE_CMD_PROMISCEN_V(x)	((x) << FW_VI_RXMODE_CMD_PROMISCEN_S)

#घोषणा FW_VI_RXMODE_CMD_ALLMULTIEN_S		12
#घोषणा FW_VI_RXMODE_CMD_ALLMULTIEN_M		0x3
#घोषणा FW_VI_RXMODE_CMD_ALLMULTIEN_V(x)	\
	((x) << FW_VI_RXMODE_CMD_ALLMULTIEN_S)

#घोषणा FW_VI_RXMODE_CMD_BROADCASTEN_S		10
#घोषणा FW_VI_RXMODE_CMD_BROADCASTEN_M		0x3
#घोषणा FW_VI_RXMODE_CMD_BROADCASTEN_V(x)	\
	((x) << FW_VI_RXMODE_CMD_BROADCASTEN_S)

#घोषणा FW_VI_RXMODE_CMD_VLANEXEN_S	8
#घोषणा FW_VI_RXMODE_CMD_VLANEXEN_M	0x3
#घोषणा FW_VI_RXMODE_CMD_VLANEXEN_V(x)	((x) << FW_VI_RXMODE_CMD_VLANEXEN_S)

काष्ठा fw_vi_enable_cmd अणु
	__be32 op_to_viid;
	__be32 ien_to_len16;
	__be16 blinkdur;
	__be16 r3;
	__be32 r4;
पूर्ण;

#घोषणा FW_VI_ENABLE_CMD_VIID_S         0
#घोषणा FW_VI_ENABLE_CMD_VIID_V(x)      ((x) << FW_VI_ENABLE_CMD_VIID_S)

#घोषणा FW_VI_ENABLE_CMD_IEN_S		31
#घोषणा FW_VI_ENABLE_CMD_IEN_V(x)	((x) << FW_VI_ENABLE_CMD_IEN_S)

#घोषणा FW_VI_ENABLE_CMD_EEN_S		30
#घोषणा FW_VI_ENABLE_CMD_EEN_V(x)	((x) << FW_VI_ENABLE_CMD_EEN_S)

#घोषणा FW_VI_ENABLE_CMD_LED_S		29
#घोषणा FW_VI_ENABLE_CMD_LED_V(x)	((x) << FW_VI_ENABLE_CMD_LED_S)
#घोषणा FW_VI_ENABLE_CMD_LED_F	FW_VI_ENABLE_CMD_LED_V(1U)

#घोषणा FW_VI_ENABLE_CMD_DCB_INFO_S	28
#घोषणा FW_VI_ENABLE_CMD_DCB_INFO_V(x)	((x) << FW_VI_ENABLE_CMD_DCB_INFO_S)

/* VI VF stats offset definitions */
#घोषणा VI_VF_NUM_STATS	16
क्रमागत fw_vi_stats_vf_index अणु
	FW_VI_VF_STAT_TX_BCAST_BYTES_IX,
	FW_VI_VF_STAT_TX_BCAST_FRAMES_IX,
	FW_VI_VF_STAT_TX_MCAST_BYTES_IX,
	FW_VI_VF_STAT_TX_MCAST_FRAMES_IX,
	FW_VI_VF_STAT_TX_UCAST_BYTES_IX,
	FW_VI_VF_STAT_TX_UCAST_FRAMES_IX,
	FW_VI_VF_STAT_TX_DROP_FRAMES_IX,
	FW_VI_VF_STAT_TX_OFLD_BYTES_IX,
	FW_VI_VF_STAT_TX_OFLD_FRAMES_IX,
	FW_VI_VF_STAT_RX_BCAST_BYTES_IX,
	FW_VI_VF_STAT_RX_BCAST_FRAMES_IX,
	FW_VI_VF_STAT_RX_MCAST_BYTES_IX,
	FW_VI_VF_STAT_RX_MCAST_FRAMES_IX,
	FW_VI_VF_STAT_RX_UCAST_BYTES_IX,
	FW_VI_VF_STAT_RX_UCAST_FRAMES_IX,
	FW_VI_VF_STAT_RX_ERR_FRAMES_IX
पूर्ण;

/* VI PF stats offset definitions */
#घोषणा VI_PF_NUM_STATS	17
क्रमागत fw_vi_stats_pf_index अणु
	FW_VI_PF_STAT_TX_BCAST_BYTES_IX,
	FW_VI_PF_STAT_TX_BCAST_FRAMES_IX,
	FW_VI_PF_STAT_TX_MCAST_BYTES_IX,
	FW_VI_PF_STAT_TX_MCAST_FRAMES_IX,
	FW_VI_PF_STAT_TX_UCAST_BYTES_IX,
	FW_VI_PF_STAT_TX_UCAST_FRAMES_IX,
	FW_VI_PF_STAT_TX_OFLD_BYTES_IX,
	FW_VI_PF_STAT_TX_OFLD_FRAMES_IX,
	FW_VI_PF_STAT_RX_BYTES_IX,
	FW_VI_PF_STAT_RX_FRAMES_IX,
	FW_VI_PF_STAT_RX_BCAST_BYTES_IX,
	FW_VI_PF_STAT_RX_BCAST_FRAMES_IX,
	FW_VI_PF_STAT_RX_MCAST_BYTES_IX,
	FW_VI_PF_STAT_RX_MCAST_FRAMES_IX,
	FW_VI_PF_STAT_RX_UCAST_BYTES_IX,
	FW_VI_PF_STAT_RX_UCAST_FRAMES_IX,
	FW_VI_PF_STAT_RX_ERR_FRAMES_IX
पूर्ण;

काष्ठा fw_vi_stats_cmd अणु
	__be32 op_to_viid;
	__be32 retval_len16;
	जोड़ fw_vi_stats अणु
		काष्ठा fw_vi_stats_ctl अणु
			__be16 nstats_ix;
			__be16 r6;
			__be32 r7;
			__be64 stat0;
			__be64 stat1;
			__be64 stat2;
			__be64 stat3;
			__be64 stat4;
			__be64 stat5;
		पूर्ण ctl;
		काष्ठा fw_vi_stats_pf अणु
			__be64 tx_bcast_bytes;
			__be64 tx_bcast_frames;
			__be64 tx_mcast_bytes;
			__be64 tx_mcast_frames;
			__be64 tx_ucast_bytes;
			__be64 tx_ucast_frames;
			__be64 tx_offload_bytes;
			__be64 tx_offload_frames;
			__be64 rx_pf_bytes;
			__be64 rx_pf_frames;
			__be64 rx_bcast_bytes;
			__be64 rx_bcast_frames;
			__be64 rx_mcast_bytes;
			__be64 rx_mcast_frames;
			__be64 rx_ucast_bytes;
			__be64 rx_ucast_frames;
			__be64 rx_err_frames;
		पूर्ण pf;
		काष्ठा fw_vi_stats_vf अणु
			__be64 tx_bcast_bytes;
			__be64 tx_bcast_frames;
			__be64 tx_mcast_bytes;
			__be64 tx_mcast_frames;
			__be64 tx_ucast_bytes;
			__be64 tx_ucast_frames;
			__be64 tx_drop_frames;
			__be64 tx_offload_bytes;
			__be64 tx_offload_frames;
			__be64 rx_bcast_bytes;
			__be64 rx_bcast_frames;
			__be64 rx_mcast_bytes;
			__be64 rx_mcast_frames;
			__be64 rx_ucast_bytes;
			__be64 rx_ucast_frames;
			__be64 rx_err_frames;
		पूर्ण vf;
	पूर्ण u;
पूर्ण;

#घोषणा FW_VI_STATS_CMD_VIID_S		0
#घोषणा FW_VI_STATS_CMD_VIID_V(x)	((x) << FW_VI_STATS_CMD_VIID_S)

#घोषणा FW_VI_STATS_CMD_NSTATS_S	12
#घोषणा FW_VI_STATS_CMD_NSTATS_V(x)	((x) << FW_VI_STATS_CMD_NSTATS_S)

#घोषणा FW_VI_STATS_CMD_IX_S	0
#घोषणा FW_VI_STATS_CMD_IX_V(x)	((x) << FW_VI_STATS_CMD_IX_S)

काष्ठा fw_acl_mac_cmd अणु
	__be32 op_to_vfn;
	__be32 en_to_len16;
	u8 nmac;
	u8 r3[7];
	__be16 r4;
	u8 macaddr0[6];
	__be16 r5;
	u8 macaddr1[6];
	__be16 r6;
	u8 macaddr2[6];
	__be16 r7;
	u8 macaddr3[6];
पूर्ण;

#घोषणा FW_ACL_MAC_CMD_PFN_S	8
#घोषणा FW_ACL_MAC_CMD_PFN_V(x)	((x) << FW_ACL_MAC_CMD_PFN_S)

#घोषणा FW_ACL_MAC_CMD_VFN_S	0
#घोषणा FW_ACL_MAC_CMD_VFN_V(x)	((x) << FW_ACL_MAC_CMD_VFN_S)

#घोषणा FW_ACL_MAC_CMD_EN_S	31
#घोषणा FW_ACL_MAC_CMD_EN_V(x)	((x) << FW_ACL_MAC_CMD_EN_S)

काष्ठा fw_acl_vlan_cmd अणु
	__be32 op_to_vfn;
	__be32 en_to_len16;
	u8 nvlan;
	u8 dropnovlan_fm;
	u8 r3_lo[6];
	__be16 vlanid[16];
पूर्ण;

#घोषणा FW_ACL_VLAN_CMD_PFN_S		8
#घोषणा FW_ACL_VLAN_CMD_PFN_V(x)	((x) << FW_ACL_VLAN_CMD_PFN_S)

#घोषणा FW_ACL_VLAN_CMD_VFN_S		0
#घोषणा FW_ACL_VLAN_CMD_VFN_V(x)	((x) << FW_ACL_VLAN_CMD_VFN_S)

#घोषणा FW_ACL_VLAN_CMD_EN_S		31
#घोषणा FW_ACL_VLAN_CMD_EN_M		0x1
#घोषणा FW_ACL_VLAN_CMD_EN_V(x)		((x) << FW_ACL_VLAN_CMD_EN_S)
#घोषणा FW_ACL_VLAN_CMD_EN_G(x)         \
	(((x) >> S_FW_ACL_VLAN_CMD_EN_S) & FW_ACL_VLAN_CMD_EN_M)
#घोषणा FW_ACL_VLAN_CMD_EN_F            FW_ACL_VLAN_CMD_EN_V(1U)

#घोषणा FW_ACL_VLAN_CMD_DROPNOVLAN_S	7
#घोषणा FW_ACL_VLAN_CMD_DROPNOVLAN_V(x)	((x) << FW_ACL_VLAN_CMD_DROPNOVLAN_S)
#घोषणा FW_ACL_VLAN_CMD_DROPNOVLAN_F    FW_ACL_VLAN_CMD_DROPNOVLAN_V(1U)

#घोषणा FW_ACL_VLAN_CMD_FM_S		6
#घोषणा FW_ACL_VLAN_CMD_FM_M		0x1
#घोषणा FW_ACL_VLAN_CMD_FM_V(x)         ((x) << FW_ACL_VLAN_CMD_FM_S)
#घोषणा FW_ACL_VLAN_CMD_FM_G(x)         \
	(((x) >> FW_ACL_VLAN_CMD_FM_S) & FW_ACL_VLAN_CMD_FM_M)
#घोषणा FW_ACL_VLAN_CMD_FM_F            FW_ACL_VLAN_CMD_FM_V(1U)

/* old 16-bit port capabilities biपंचांगap (fw_port_cap16_t) */
क्रमागत fw_port_cap अणु
	FW_PORT_CAP_SPEED_100M		= 0x0001,
	FW_PORT_CAP_SPEED_1G		= 0x0002,
	FW_PORT_CAP_SPEED_25G		= 0x0004,
	FW_PORT_CAP_SPEED_10G		= 0x0008,
	FW_PORT_CAP_SPEED_40G		= 0x0010,
	FW_PORT_CAP_SPEED_100G		= 0x0020,
	FW_PORT_CAP_FC_RX		= 0x0040,
	FW_PORT_CAP_FC_TX		= 0x0080,
	FW_PORT_CAP_ANEG		= 0x0100,
	FW_PORT_CAP_MDIAUTO		= 0x0200,
	FW_PORT_CAP_MDISTRAIGHT		= 0x0400,
	FW_PORT_CAP_FEC_RS		= 0x0800,
	FW_PORT_CAP_FEC_BASER_RS	= 0x1000,
	FW_PORT_CAP_FORCE_PAUSE		= 0x2000,
	FW_PORT_CAP_802_3_PAUSE		= 0x4000,
	FW_PORT_CAP_802_3_ASM_सूची	= 0x8000,
पूर्ण;

#घोषणा FW_PORT_CAP_SPEED_S     0
#घोषणा FW_PORT_CAP_SPEED_M     0x3f
#घोषणा FW_PORT_CAP_SPEED_V(x)  ((x) << FW_PORT_CAP_SPEED_S)
#घोषणा FW_PORT_CAP_SPEED_G(x) \
	(((x) >> FW_PORT_CAP_SPEED_S) & FW_PORT_CAP_SPEED_M)

क्रमागत fw_port_mdi अणु
	FW_PORT_CAP_MDI_UNCHANGED,
	FW_PORT_CAP_MDI_AUTO,
	FW_PORT_CAP_MDI_F_STRAIGHT,
	FW_PORT_CAP_MDI_F_CROSSOVER
पूर्ण;

#घोषणा FW_PORT_CAP_MDI_S 9
#घोषणा FW_PORT_CAP_MDI_V(x) ((x) << FW_PORT_CAP_MDI_S)

/* new 32-bit port capabilities biपंचांगap (fw_port_cap32_t) */
#घोषणा	FW_PORT_CAP32_SPEED_100M	0x00000001UL
#घोषणा	FW_PORT_CAP32_SPEED_1G		0x00000002UL
#घोषणा	FW_PORT_CAP32_SPEED_10G		0x00000004UL
#घोषणा	FW_PORT_CAP32_SPEED_25G		0x00000008UL
#घोषणा	FW_PORT_CAP32_SPEED_40G		0x00000010UL
#घोषणा	FW_PORT_CAP32_SPEED_50G		0x00000020UL
#घोषणा	FW_PORT_CAP32_SPEED_100G	0x00000040UL
#घोषणा	FW_PORT_CAP32_SPEED_200G	0x00000080UL
#घोषणा	FW_PORT_CAP32_SPEED_400G	0x00000100UL
#घोषणा	FW_PORT_CAP32_SPEED_RESERVED1	0x00000200UL
#घोषणा	FW_PORT_CAP32_SPEED_RESERVED2	0x00000400UL
#घोषणा	FW_PORT_CAP32_SPEED_RESERVED3	0x00000800UL
#घोषणा	FW_PORT_CAP32_RESERVED1		0x0000f000UL
#घोषणा	FW_PORT_CAP32_FC_RX		0x00010000UL
#घोषणा	FW_PORT_CAP32_FC_TX		0x00020000UL
#घोषणा	FW_PORT_CAP32_802_3_PAUSE	0x00040000UL
#घोषणा	FW_PORT_CAP32_802_3_ASM_सूची	0x00080000UL
#घोषणा	FW_PORT_CAP32_ANEG		0x00100000UL
#घोषणा	FW_PORT_CAP32_MDIAUTO		0x00200000UL
#घोषणा	FW_PORT_CAP32_MDISTRAIGHT	0x00400000UL
#घोषणा	FW_PORT_CAP32_FEC_RS		0x00800000UL
#घोषणा	FW_PORT_CAP32_FEC_BASER_RS	0x01000000UL
#घोषणा	FW_PORT_CAP32_FEC_RESERVED1	0x02000000UL
#घोषणा	FW_PORT_CAP32_FEC_RESERVED2	0x04000000UL
#घोषणा	FW_PORT_CAP32_FEC_RESERVED3	0x08000000UL
#घोषणा FW_PORT_CAP32_FORCE_PAUSE	0x10000000UL
#घोषणा FW_PORT_CAP32_RESERVED2		0xe0000000UL

#घोषणा FW_PORT_CAP32_SPEED_S	0
#घोषणा FW_PORT_CAP32_SPEED_M	0xfff
#घोषणा FW_PORT_CAP32_SPEED_V(x)	((x) << FW_PORT_CAP32_SPEED_S)
#घोषणा FW_PORT_CAP32_SPEED_G(x) \
	(((x) >> FW_PORT_CAP32_SPEED_S) & FW_PORT_CAP32_SPEED_M)

#घोषणा FW_PORT_CAP32_FC_S	16
#घोषणा FW_PORT_CAP32_FC_M	0x3
#घोषणा FW_PORT_CAP32_FC_V(x)	((x) << FW_PORT_CAP32_FC_S)
#घोषणा FW_PORT_CAP32_FC_G(x) \
	(((x) >> FW_PORT_CAP32_FC_S) & FW_PORT_CAP32_FC_M)

#घोषणा FW_PORT_CAP32_802_3_S	18
#घोषणा FW_PORT_CAP32_802_3_M	0x3
#घोषणा FW_PORT_CAP32_802_3_V(x)	((x) << FW_PORT_CAP32_802_3_S)
#घोषणा FW_PORT_CAP32_802_3_G(x) \
	(((x) >> FW_PORT_CAP32_802_3_S) & FW_PORT_CAP32_802_3_M)

#घोषणा FW_PORT_CAP32_ANEG_S	20
#घोषणा FW_PORT_CAP32_ANEG_M	0x1
#घोषणा FW_PORT_CAP32_ANEG_V(x)	((x) << FW_PORT_CAP32_ANEG_S)
#घोषणा FW_PORT_CAP32_ANEG_G(x) \
	(((x) >> FW_PORT_CAP32_ANEG_S) & FW_PORT_CAP32_ANEG_M)

क्रमागत fw_port_mdi32 अणु
	FW_PORT_CAP32_MDI_UNCHANGED,
	FW_PORT_CAP32_MDI_AUTO,
	FW_PORT_CAP32_MDI_F_STRAIGHT,
	FW_PORT_CAP32_MDI_F_CROSSOVER
पूर्ण;

#घोषणा FW_PORT_CAP32_MDI_S 21
#घोषणा FW_PORT_CAP32_MDI_M 3
#घोषणा FW_PORT_CAP32_MDI_V(x) ((x) << FW_PORT_CAP32_MDI_S)
#घोषणा FW_PORT_CAP32_MDI_G(x) \
	(((x) >> FW_PORT_CAP32_MDI_S) & FW_PORT_CAP32_MDI_M)

#घोषणा FW_PORT_CAP32_FEC_S	23
#घोषणा FW_PORT_CAP32_FEC_M	0x1f
#घोषणा FW_PORT_CAP32_FEC_V(x)	((x) << FW_PORT_CAP32_FEC_S)
#घोषणा FW_PORT_CAP32_FEC_G(x) \
	(((x) >> FW_PORT_CAP32_FEC_S) & FW_PORT_CAP32_FEC_M)

/* macros to isolate various 32-bit Port Capabilities sub-fields */
#घोषणा CAP32_SPEED(__cap32) \
	(FW_PORT_CAP32_SPEED_V(FW_PORT_CAP32_SPEED_M) & __cap32)

#घोषणा CAP32_FEC(__cap32) \
	(FW_PORT_CAP32_FEC_V(FW_PORT_CAP32_FEC_M) & __cap32)

क्रमागत fw_port_action अणु
	FW_PORT_ACTION_L1_CFG		= 0x0001,
	FW_PORT_ACTION_L2_CFG		= 0x0002,
	FW_PORT_ACTION_GET_PORT_INFO	= 0x0003,
	FW_PORT_ACTION_L2_PPP_CFG	= 0x0004,
	FW_PORT_ACTION_L2_DCB_CFG	= 0x0005,
	FW_PORT_ACTION_DCB_READ_TRANS	= 0x0006,
	FW_PORT_ACTION_DCB_READ_RECV	= 0x0007,
	FW_PORT_ACTION_DCB_READ_DET	= 0x0008,
	FW_PORT_ACTION_L1_CFG32		= 0x0009,
	FW_PORT_ACTION_GET_PORT_INFO32	= 0x000a,
	FW_PORT_ACTION_LOW_PWR_TO_NORMAL = 0x0010,
	FW_PORT_ACTION_L1_LOW_PWR_EN	= 0x0011,
	FW_PORT_ACTION_L2_WOL_MODE_EN	= 0x0012,
	FW_PORT_ACTION_LPBK_TO_NORMAL	= 0x0020,
	FW_PORT_ACTION_L1_LPBK		= 0x0021,
	FW_PORT_ACTION_L1_PMA_LPBK	= 0x0022,
	FW_PORT_ACTION_L1_PCS_LPBK	= 0x0023,
	FW_PORT_ACTION_L1_PHYXS_CSIDE_LPBK = 0x0024,
	FW_PORT_ACTION_L1_PHYXS_ESIDE_LPBK = 0x0025,
	FW_PORT_ACTION_PHY_RESET	= 0x0040,
	FW_PORT_ACTION_PMA_RESET	= 0x0041,
	FW_PORT_ACTION_PCS_RESET	= 0x0042,
	FW_PORT_ACTION_PHYXS_RESET	= 0x0043,
	FW_PORT_ACTION_DTEXS_REEST	= 0x0044,
	FW_PORT_ACTION_AN_RESET		= 0x0045
पूर्ण;

क्रमागत fw_port_l2cfg_ctlbf अणु
	FW_PORT_L2_CTLBF_OVLAN0	= 0x01,
	FW_PORT_L2_CTLBF_OVLAN1	= 0x02,
	FW_PORT_L2_CTLBF_OVLAN2	= 0x04,
	FW_PORT_L2_CTLBF_OVLAN3	= 0x08,
	FW_PORT_L2_CTLBF_IVLAN	= 0x10,
	FW_PORT_L2_CTLBF_TXIPG	= 0x20
पूर्ण;

क्रमागत fw_port_dcb_versions अणु
	FW_PORT_DCB_VER_UNKNOWN,
	FW_PORT_DCB_VER_CEE1D0,
	FW_PORT_DCB_VER_CEE1D01,
	FW_PORT_DCB_VER_IEEE,
	FW_PORT_DCB_VER_AUTO = 7
पूर्ण;

क्रमागत fw_port_dcb_cfg अणु
	FW_PORT_DCB_CFG_PG	= 0x01,
	FW_PORT_DCB_CFG_PFC	= 0x02,
	FW_PORT_DCB_CFG_APPL	= 0x04
पूर्ण;

क्रमागत fw_port_dcb_cfg_rc अणु
	FW_PORT_DCB_CFG_SUCCESS	= 0x0,
	FW_PORT_DCB_CFG_ERROR	= 0x1
पूर्ण;

क्रमागत fw_port_dcb_type अणु
	FW_PORT_DCB_TYPE_PGID		= 0x00,
	FW_PORT_DCB_TYPE_PGRATE		= 0x01,
	FW_PORT_DCB_TYPE_PRIORATE	= 0x02,
	FW_PORT_DCB_TYPE_PFC		= 0x03,
	FW_PORT_DCB_TYPE_APP_ID		= 0x04,
	FW_PORT_DCB_TYPE_CONTROL	= 0x05,
पूर्ण;

क्रमागत fw_port_dcb_feature_state अणु
	FW_PORT_DCB_FEATURE_STATE_PENDING = 0x0,
	FW_PORT_DCB_FEATURE_STATE_SUCCESS = 0x1,
	FW_PORT_DCB_FEATURE_STATE_ERROR	= 0x2,
	FW_PORT_DCB_FEATURE_STATE_TIMEOUT = 0x3,
पूर्ण;

काष्ठा fw_port_cmd अणु
	__be32 op_to_portid;
	__be32 action_to_len16;
	जोड़ fw_port अणु
		काष्ठा fw_port_l1cfg अणु
			__be32 rcap;
			__be32 r;
		पूर्ण l1cfg;
		काष्ठा fw_port_l2cfg अणु
			__u8   ctlbf;
			__u8   ovlan3_to_ivlan0;
			__be16 ivlantype;
			__be16 txipg_क्रमce_pinfo;
			__be16 mtu;
			__be16 ovlan0mask;
			__be16 ovlan0type;
			__be16 ovlan1mask;
			__be16 ovlan1type;
			__be16 ovlan2mask;
			__be16 ovlan2type;
			__be16 ovlan3mask;
			__be16 ovlan3type;
		पूर्ण l2cfg;
		काष्ठा fw_port_info अणु
			__be32 lstatus_to_modtype;
			__be16 pcap;
			__be16 acap;
			__be16 mtu;
			__u8   cbllen;
			__u8   auxlinfo;
			__u8   dcbxdis_pkd;
			__u8   r8_lo;
			__be16 lpacap;
			__be64 r9;
		पूर्ण info;
		काष्ठा fw_port_diags अणु
			__u8   diagop;
			__u8   r[3];
			__be32 diagval;
		पूर्ण diags;
		जोड़ fw_port_dcb अणु
			काष्ठा fw_port_dcb_pgid अणु
				__u8   type;
				__u8   apply_pkd;
				__u8   r10_lo[2];
				__be32 pgid;
				__be64 r11;
			पूर्ण pgid;
			काष्ठा fw_port_dcb_pgrate अणु
				__u8   type;
				__u8   apply_pkd;
				__u8   r10_lo[5];
				__u8   num_tcs_supported;
				__u8   pgrate[8];
				__u8   tsa[8];
			पूर्ण pgrate;
			काष्ठा fw_port_dcb_priorate अणु
				__u8   type;
				__u8   apply_pkd;
				__u8   r10_lo[6];
				__u8   strict_priorate[8];
			पूर्ण priorate;
			काष्ठा fw_port_dcb_pfc अणु
				__u8   type;
				__u8   pfcen;
				__u8   r10[5];
				__u8   max_pfc_tcs;
				__be64 r11;
			पूर्ण pfc;
			काष्ठा fw_port_app_priority अणु
				__u8   type;
				__u8   r10[2];
				__u8   idx;
				__u8   user_prio_map;
				__u8   sel_field;
				__be16 protocolid;
				__be64 r12;
			पूर्ण app_priority;
			काष्ठा fw_port_dcb_control अणु
				__u8   type;
				__u8   all_syncd_pkd;
				__be16 dcb_version_to_app_state;
				__be32 r11;
				__be64 r12;
			पूर्ण control;
		पूर्ण dcb;
		काष्ठा fw_port_l1cfg32 अणु
			__be32 rcap32;
			__be32 r;
		पूर्ण l1cfg32;
		काष्ठा fw_port_info32 अणु
			__be32 lstatus32_to_cbllen32;
			__be32 auxlinfo32_mtu32;
			__be32 linkattr32;
			__be32 pcaps32;
			__be32 acaps32;
			__be32 lpacaps32;
		पूर्ण info32;
	पूर्ण u;
पूर्ण;

#घोषणा FW_PORT_CMD_READ_S	22
#घोषणा FW_PORT_CMD_READ_V(x)	((x) << FW_PORT_CMD_READ_S)
#घोषणा FW_PORT_CMD_READ_F	FW_PORT_CMD_READ_V(1U)

#घोषणा FW_PORT_CMD_PORTID_S	0
#घोषणा FW_PORT_CMD_PORTID_M	0xf
#घोषणा FW_PORT_CMD_PORTID_V(x)	((x) << FW_PORT_CMD_PORTID_S)
#घोषणा FW_PORT_CMD_PORTID_G(x)	\
	(((x) >> FW_PORT_CMD_PORTID_S) & FW_PORT_CMD_PORTID_M)

#घोषणा FW_PORT_CMD_ACTION_S	16
#घोषणा FW_PORT_CMD_ACTION_M	0xffff
#घोषणा FW_PORT_CMD_ACTION_V(x)	((x) << FW_PORT_CMD_ACTION_S)
#घोषणा FW_PORT_CMD_ACTION_G(x)	\
	(((x) >> FW_PORT_CMD_ACTION_S) & FW_PORT_CMD_ACTION_M)

#घोषणा FW_PORT_CMD_OVLAN3_S	7
#घोषणा FW_PORT_CMD_OVLAN3_V(x)	((x) << FW_PORT_CMD_OVLAN3_S)

#घोषणा FW_PORT_CMD_OVLAN2_S	6
#घोषणा FW_PORT_CMD_OVLAN2_V(x)	((x) << FW_PORT_CMD_OVLAN2_S)

#घोषणा FW_PORT_CMD_OVLAN1_S	5
#घोषणा FW_PORT_CMD_OVLAN1_V(x)	((x) << FW_PORT_CMD_OVLAN1_S)

#घोषणा FW_PORT_CMD_OVLAN0_S	4
#घोषणा FW_PORT_CMD_OVLAN0_V(x)	((x) << FW_PORT_CMD_OVLAN0_S)

#घोषणा FW_PORT_CMD_IVLAN0_S	3
#घोषणा FW_PORT_CMD_IVLAN0_V(x)	((x) << FW_PORT_CMD_IVLAN0_S)

#घोषणा FW_PORT_CMD_TXIPG_S	3
#घोषणा FW_PORT_CMD_TXIPG_V(x)	((x) << FW_PORT_CMD_TXIPG_S)

#घोषणा FW_PORT_CMD_LSTATUS_S           31
#घोषणा FW_PORT_CMD_LSTATUS_M           0x1
#घोषणा FW_PORT_CMD_LSTATUS_V(x)        ((x) << FW_PORT_CMD_LSTATUS_S)
#घोषणा FW_PORT_CMD_LSTATUS_G(x)        \
	(((x) >> FW_PORT_CMD_LSTATUS_S) & FW_PORT_CMD_LSTATUS_M)
#घोषणा FW_PORT_CMD_LSTATUS_F   FW_PORT_CMD_LSTATUS_V(1U)

#घोषणा FW_PORT_CMD_LSPEED_S	24
#घोषणा FW_PORT_CMD_LSPEED_M	0x3f
#घोषणा FW_PORT_CMD_LSPEED_V(x)	((x) << FW_PORT_CMD_LSPEED_S)
#घोषणा FW_PORT_CMD_LSPEED_G(x)	\
	(((x) >> FW_PORT_CMD_LSPEED_S) & FW_PORT_CMD_LSPEED_M)

#घोषणा FW_PORT_CMD_TXPAUSE_S		23
#घोषणा FW_PORT_CMD_TXPAUSE_V(x)	((x) << FW_PORT_CMD_TXPAUSE_S)
#घोषणा FW_PORT_CMD_TXPAUSE_F	FW_PORT_CMD_TXPAUSE_V(1U)

#घोषणा FW_PORT_CMD_RXPAUSE_S		22
#घोषणा FW_PORT_CMD_RXPAUSE_V(x)	((x) << FW_PORT_CMD_RXPAUSE_S)
#घोषणा FW_PORT_CMD_RXPAUSE_F	FW_PORT_CMD_RXPAUSE_V(1U)

#घोषणा FW_PORT_CMD_MDIOCAP_S		21
#घोषणा FW_PORT_CMD_MDIOCAP_V(x)	((x) << FW_PORT_CMD_MDIOCAP_S)
#घोषणा FW_PORT_CMD_MDIOCAP_F	FW_PORT_CMD_MDIOCAP_V(1U)

#घोषणा FW_PORT_CMD_MDIOADDR_S		16
#घोषणा FW_PORT_CMD_MDIOADDR_M		0x1f
#घोषणा FW_PORT_CMD_MDIOADDR_G(x)	\
	(((x) >> FW_PORT_CMD_MDIOADDR_S) & FW_PORT_CMD_MDIOADDR_M)

#घोषणा FW_PORT_CMD_LPTXPAUSE_S		15
#घोषणा FW_PORT_CMD_LPTXPAUSE_V(x)	((x) << FW_PORT_CMD_LPTXPAUSE_S)
#घोषणा FW_PORT_CMD_LPTXPAUSE_F	FW_PORT_CMD_LPTXPAUSE_V(1U)

#घोषणा FW_PORT_CMD_LPRXPAUSE_S		14
#घोषणा FW_PORT_CMD_LPRXPAUSE_V(x)	((x) << FW_PORT_CMD_LPRXPAUSE_S)
#घोषणा FW_PORT_CMD_LPRXPAUSE_F	FW_PORT_CMD_LPRXPAUSE_V(1U)

#घोषणा FW_PORT_CMD_PTYPE_S	8
#घोषणा FW_PORT_CMD_PTYPE_M	0x1f
#घोषणा FW_PORT_CMD_PTYPE_G(x)	\
	(((x) >> FW_PORT_CMD_PTYPE_S) & FW_PORT_CMD_PTYPE_M)

#घोषणा FW_PORT_CMD_LINKDNRC_S		5
#घोषणा FW_PORT_CMD_LINKDNRC_M		0x7
#घोषणा FW_PORT_CMD_LINKDNRC_G(x)	\
	(((x) >> FW_PORT_CMD_LINKDNRC_S) & FW_PORT_CMD_LINKDNRC_M)

#घोषणा FW_PORT_CMD_MODTYPE_S		0
#घोषणा FW_PORT_CMD_MODTYPE_M		0x1f
#घोषणा FW_PORT_CMD_MODTYPE_V(x)	((x) << FW_PORT_CMD_MODTYPE_S)
#घोषणा FW_PORT_CMD_MODTYPE_G(x)	\
	(((x) >> FW_PORT_CMD_MODTYPE_S) & FW_PORT_CMD_MODTYPE_M)

#घोषणा FW_PORT_CMD_DCBXDIS_S		7
#घोषणा FW_PORT_CMD_DCBXDIS_V(x)	((x) << FW_PORT_CMD_DCBXDIS_S)
#घोषणा FW_PORT_CMD_DCBXDIS_F	FW_PORT_CMD_DCBXDIS_V(1U)

#घोषणा FW_PORT_CMD_APPLY_S	7
#घोषणा FW_PORT_CMD_APPLY_V(x)	((x) << FW_PORT_CMD_APPLY_S)
#घोषणा FW_PORT_CMD_APPLY_F	FW_PORT_CMD_APPLY_V(1U)

#घोषणा FW_PORT_CMD_ALL_SYNCD_S		7
#घोषणा FW_PORT_CMD_ALL_SYNCD_V(x)	((x) << FW_PORT_CMD_ALL_SYNCD_S)
#घोषणा FW_PORT_CMD_ALL_SYNCD_F	FW_PORT_CMD_ALL_SYNCD_V(1U)

#घोषणा FW_PORT_CMD_DCB_VERSION_S	12
#घोषणा FW_PORT_CMD_DCB_VERSION_M	0x7
#घोषणा FW_PORT_CMD_DCB_VERSION_G(x)	\
	(((x) >> FW_PORT_CMD_DCB_VERSION_S) & FW_PORT_CMD_DCB_VERSION_M)

#घोषणा FW_PORT_CMD_LSTATUS32_S		31
#घोषणा FW_PORT_CMD_LSTATUS32_M		0x1
#घोषणा FW_PORT_CMD_LSTATUS32_V(x)	((x) << FW_PORT_CMD_LSTATUS32_S)
#घोषणा FW_PORT_CMD_LSTATUS32_G(x)	\
	(((x) >> FW_PORT_CMD_LSTATUS32_S) & FW_PORT_CMD_LSTATUS32_M)
#घोषणा FW_PORT_CMD_LSTATUS32_F	FW_PORT_CMD_LSTATUS32_V(1U)

#घोषणा FW_PORT_CMD_LINKDNRC32_S	28
#घोषणा FW_PORT_CMD_LINKDNRC32_M	0x7
#घोषणा FW_PORT_CMD_LINKDNRC32_V(x)	((x) << FW_PORT_CMD_LINKDNRC32_S)
#घोषणा FW_PORT_CMD_LINKDNRC32_G(x)	\
	(((x) >> FW_PORT_CMD_LINKDNRC32_S) & FW_PORT_CMD_LINKDNRC32_M)

#घोषणा FW_PORT_CMD_DCBXDIS32_S		27
#घोषणा FW_PORT_CMD_DCBXDIS32_M		0x1
#घोषणा FW_PORT_CMD_DCBXDIS32_V(x)	((x) << FW_PORT_CMD_DCBXDIS32_S)
#घोषणा FW_PORT_CMD_DCBXDIS32_G(x)	\
	(((x) >> FW_PORT_CMD_DCBXDIS32_S) & FW_PORT_CMD_DCBXDIS32_M)
#घोषणा FW_PORT_CMD_DCBXDIS32_F	FW_PORT_CMD_DCBXDIS32_V(1U)

#घोषणा FW_PORT_CMD_MDIOCAP32_S		26
#घोषणा FW_PORT_CMD_MDIOCAP32_M		0x1
#घोषणा FW_PORT_CMD_MDIOCAP32_V(x)	((x) << FW_PORT_CMD_MDIOCAP32_S)
#घोषणा FW_PORT_CMD_MDIOCAP32_G(x)	\
	(((x) >> FW_PORT_CMD_MDIOCAP32_S) & FW_PORT_CMD_MDIOCAP32_M)
#घोषणा FW_PORT_CMD_MDIOCAP32_F	FW_PORT_CMD_MDIOCAP32_V(1U)

#घोषणा FW_PORT_CMD_MDIOADDR32_S	21
#घोषणा FW_PORT_CMD_MDIOADDR32_M	0x1f
#घोषणा FW_PORT_CMD_MDIOADDR32_V(x)	((x) << FW_PORT_CMD_MDIOADDR32_S)
#घोषणा FW_PORT_CMD_MDIOADDR32_G(x)	\
	(((x) >> FW_PORT_CMD_MDIOADDR32_S) & FW_PORT_CMD_MDIOADDR32_M)

#घोषणा FW_PORT_CMD_PORTTYPE32_S	13
#घोषणा FW_PORT_CMD_PORTTYPE32_M	0xff
#घोषणा FW_PORT_CMD_PORTTYPE32_V(x)	((x) << FW_PORT_CMD_PORTTYPE32_S)
#घोषणा FW_PORT_CMD_PORTTYPE32_G(x)	\
	(((x) >> FW_PORT_CMD_PORTTYPE32_S) & FW_PORT_CMD_PORTTYPE32_M)

#घोषणा FW_PORT_CMD_MODTYPE32_S		8
#घोषणा FW_PORT_CMD_MODTYPE32_M		0x1f
#घोषणा FW_PORT_CMD_MODTYPE32_V(x)	((x) << FW_PORT_CMD_MODTYPE32_S)
#घोषणा FW_PORT_CMD_MODTYPE32_G(x)	\
	(((x) >> FW_PORT_CMD_MODTYPE32_S) & FW_PORT_CMD_MODTYPE32_M)

#घोषणा FW_PORT_CMD_CBLLEN32_S		0
#घोषणा FW_PORT_CMD_CBLLEN32_M		0xff
#घोषणा FW_PORT_CMD_CBLLEN32_V(x)	((x) << FW_PORT_CMD_CBLLEN32_S)
#घोषणा FW_PORT_CMD_CBLLEN32_G(x)	\
	(((x) >> FW_PORT_CMD_CBLLEN32_S) & FW_PORT_CMD_CBLLEN32_M)

#घोषणा FW_PORT_CMD_AUXLINFO32_S	24
#घोषणा FW_PORT_CMD_AUXLINFO32_M	0xff
#घोषणा FW_PORT_CMD_AUXLINFO32_V(x)	((x) << FW_PORT_CMD_AUXLINFO32_S)
#घोषणा FW_PORT_CMD_AUXLINFO32_G(x)	\
	(((x) >> FW_PORT_CMD_AUXLINFO32_S) & FW_PORT_CMD_AUXLINFO32_M)

#घोषणा FW_PORT_AUXLINFO32_KX4_S	2
#घोषणा FW_PORT_AUXLINFO32_KX4_M	0x1
#घोषणा FW_PORT_AUXLINFO32_KX4_V(x) \
	((x) << FW_PORT_AUXLINFO32_KX4_S)
#घोषणा FW_PORT_AUXLINFO32_KX4_G(x) \
	(((x) >> FW_PORT_AUXLINFO32_KX4_S) & FW_PORT_AUXLINFO32_KX4_M)
#घोषणा FW_PORT_AUXLINFO32_KX4_F	FW_PORT_AUXLINFO32_KX4_V(1U)

#घोषणा FW_PORT_AUXLINFO32_KR_S	1
#घोषणा FW_PORT_AUXLINFO32_KR_M	0x1
#घोषणा FW_PORT_AUXLINFO32_KR_V(x) \
	((x) << FW_PORT_AUXLINFO32_KR_S)
#घोषणा FW_PORT_AUXLINFO32_KR_G(x) \
	(((x) >> FW_PORT_AUXLINFO32_KR_S) & FW_PORT_AUXLINFO32_KR_M)
#घोषणा FW_PORT_AUXLINFO32_KR_F	FW_PORT_AUXLINFO32_KR_V(1U)

#घोषणा FW_PORT_CMD_MTU32_S	0
#घोषणा FW_PORT_CMD_MTU32_M	0xffff
#घोषणा FW_PORT_CMD_MTU32_V(x)	((x) << FW_PORT_CMD_MTU32_S)
#घोषणा FW_PORT_CMD_MTU32_G(x)	\
	(((x) >> FW_PORT_CMD_MTU32_S) & FW_PORT_CMD_MTU32_M)

क्रमागत fw_port_type अणु
	FW_PORT_TYPE_FIBER_XFI,
	FW_PORT_TYPE_FIBER_XAUI,
	FW_PORT_TYPE_BT_SGMII,
	FW_PORT_TYPE_BT_XFI,
	FW_PORT_TYPE_BT_XAUI,
	FW_PORT_TYPE_KX4,
	FW_PORT_TYPE_CX4,
	FW_PORT_TYPE_KX,
	FW_PORT_TYPE_KR,
	FW_PORT_TYPE_SFP,
	FW_PORT_TYPE_BP_AP,
	FW_PORT_TYPE_BP4_AP,
	FW_PORT_TYPE_QSFP_10G,
	FW_PORT_TYPE_QSA,
	FW_PORT_TYPE_QSFP,
	FW_PORT_TYPE_BP40_BA,
	FW_PORT_TYPE_KR4_100G,
	FW_PORT_TYPE_CR4_QSFP,
	FW_PORT_TYPE_CR_QSFP,
	FW_PORT_TYPE_CR2_QSFP,
	FW_PORT_TYPE_SFP28,
	FW_PORT_TYPE_KR_SFP28,
	FW_PORT_TYPE_KR_XLAUI,

	FW_PORT_TYPE_NONE = FW_PORT_CMD_PTYPE_M
पूर्ण;

क्रमागत fw_port_module_type अणु
	FW_PORT_MOD_TYPE_NA,
	FW_PORT_MOD_TYPE_LR,
	FW_PORT_MOD_TYPE_SR,
	FW_PORT_MOD_TYPE_ER,
	FW_PORT_MOD_TYPE_TWINAX_PASSIVE,
	FW_PORT_MOD_TYPE_TWINAX_ACTIVE,
	FW_PORT_MOD_TYPE_LRM,
	FW_PORT_MOD_TYPE_ERROR		= FW_PORT_CMD_MODTYPE_M - 3,
	FW_PORT_MOD_TYPE_UNKNOWN	= FW_PORT_CMD_MODTYPE_M - 2,
	FW_PORT_MOD_TYPE_NOTSUPPORTED	= FW_PORT_CMD_MODTYPE_M - 1,

	FW_PORT_MOD_TYPE_NONE = FW_PORT_CMD_MODTYPE_M
पूर्ण;

क्रमागत fw_port_mod_sub_type अणु
	FW_PORT_MOD_SUB_TYPE_NA,
	FW_PORT_MOD_SUB_TYPE_MV88E114X = 0x1,
	FW_PORT_MOD_SUB_TYPE_TN8022 = 0x2,
	FW_PORT_MOD_SUB_TYPE_AQ1202 = 0x3,
	FW_PORT_MOD_SUB_TYPE_88x3120 = 0x4,
	FW_PORT_MOD_SUB_TYPE_BCM84834 = 0x5,
	FW_PORT_MOD_SUB_TYPE_BT_VSC8634 = 0x8,

	/* The following will never been in the VPD.  They are TWINAX cable
	 * lengths decoded from SFP+ module i2c PROMs.  These should
	 * almost certainly go somewhere अन्यथा ...
	 */
	FW_PORT_MOD_SUB_TYPE_TWINAX_1 = 0x9,
	FW_PORT_MOD_SUB_TYPE_TWINAX_3 = 0xA,
	FW_PORT_MOD_SUB_TYPE_TWINAX_5 = 0xB,
	FW_PORT_MOD_SUB_TYPE_TWINAX_7 = 0xC,
पूर्ण;

क्रमागत fw_port_stats_tx_index अणु
	FW_STAT_TX_PORT_BYTES_IX = 0,
	FW_STAT_TX_PORT_FRAMES_IX,
	FW_STAT_TX_PORT_BCAST_IX,
	FW_STAT_TX_PORT_MCAST_IX,
	FW_STAT_TX_PORT_UCAST_IX,
	FW_STAT_TX_PORT_ERROR_IX,
	FW_STAT_TX_PORT_64B_IX,
	FW_STAT_TX_PORT_65B_127B_IX,
	FW_STAT_TX_PORT_128B_255B_IX,
	FW_STAT_TX_PORT_256B_511B_IX,
	FW_STAT_TX_PORT_512B_1023B_IX,
	FW_STAT_TX_PORT_1024B_1518B_IX,
	FW_STAT_TX_PORT_1519B_MAX_IX,
	FW_STAT_TX_PORT_DROP_IX,
	FW_STAT_TX_PORT_PAUSE_IX,
	FW_STAT_TX_PORT_PPP0_IX,
	FW_STAT_TX_PORT_PPP1_IX,
	FW_STAT_TX_PORT_PPP2_IX,
	FW_STAT_TX_PORT_PPP3_IX,
	FW_STAT_TX_PORT_PPP4_IX,
	FW_STAT_TX_PORT_PPP5_IX,
	FW_STAT_TX_PORT_PPP6_IX,
	FW_STAT_TX_PORT_PPP7_IX,
	FW_NUM_PORT_TX_STATS
पूर्ण;

क्रमागत fw_port_stat_rx_index अणु
	FW_STAT_RX_PORT_BYTES_IX = 0,
	FW_STAT_RX_PORT_FRAMES_IX,
	FW_STAT_RX_PORT_BCAST_IX,
	FW_STAT_RX_PORT_MCAST_IX,
	FW_STAT_RX_PORT_UCAST_IX,
	FW_STAT_RX_PORT_MTU_ERROR_IX,
	FW_STAT_RX_PORT_MTU_CRC_ERROR_IX,
	FW_STAT_RX_PORT_CRC_ERROR_IX,
	FW_STAT_RX_PORT_LEN_ERROR_IX,
	FW_STAT_RX_PORT_SYM_ERROR_IX,
	FW_STAT_RX_PORT_64B_IX,
	FW_STAT_RX_PORT_65B_127B_IX,
	FW_STAT_RX_PORT_128B_255B_IX,
	FW_STAT_RX_PORT_256B_511B_IX,
	FW_STAT_RX_PORT_512B_1023B_IX,
	FW_STAT_RX_PORT_1024B_1518B_IX,
	FW_STAT_RX_PORT_1519B_MAX_IX,
	FW_STAT_RX_PORT_PAUSE_IX,
	FW_STAT_RX_PORT_PPP0_IX,
	FW_STAT_RX_PORT_PPP1_IX,
	FW_STAT_RX_PORT_PPP2_IX,
	FW_STAT_RX_PORT_PPP3_IX,
	FW_STAT_RX_PORT_PPP4_IX,
	FW_STAT_RX_PORT_PPP5_IX,
	FW_STAT_RX_PORT_PPP6_IX,
	FW_STAT_RX_PORT_PPP7_IX,
	FW_STAT_RX_PORT_LESS_64B_IX,
	FW_STAT_RX_PORT_MAC_ERROR_IX,
	FW_NUM_PORT_RX_STATS
पूर्ण;

/* port stats */
#घोषणा FW_NUM_PORT_STATS (FW_NUM_PORT_TX_STATS + FW_NUM_PORT_RX_STATS)

काष्ठा fw_port_stats_cmd अणु
	__be32 op_to_portid;
	__be32 retval_len16;
	जोड़ fw_port_stats अणु
		काष्ठा fw_port_stats_ctl अणु
			u8 nstats_bg_bm;
			u8 tx_ix;
			__be16 r6;
			__be32 r7;
			__be64 stat0;
			__be64 stat1;
			__be64 stat2;
			__be64 stat3;
			__be64 stat4;
			__be64 stat5;
		पूर्ण ctl;
		काष्ठा fw_port_stats_all अणु
			__be64 tx_bytes;
			__be64 tx_frames;
			__be64 tx_bcast;
			__be64 tx_mcast;
			__be64 tx_ucast;
			__be64 tx_error;
			__be64 tx_64b;
			__be64 tx_65b_127b;
			__be64 tx_128b_255b;
			__be64 tx_256b_511b;
			__be64 tx_512b_1023b;
			__be64 tx_1024b_1518b;
			__be64 tx_1519b_max;
			__be64 tx_drop;
			__be64 tx_छोड़ो;
			__be64 tx_ppp0;
			__be64 tx_ppp1;
			__be64 tx_ppp2;
			__be64 tx_ppp3;
			__be64 tx_ppp4;
			__be64 tx_ppp5;
			__be64 tx_ppp6;
			__be64 tx_ppp7;
			__be64 rx_bytes;
			__be64 rx_frames;
			__be64 rx_bcast;
			__be64 rx_mcast;
			__be64 rx_ucast;
			__be64 rx_mtu_error;
			__be64 rx_mtu_crc_error;
			__be64 rx_crc_error;
			__be64 rx_len_error;
			__be64 rx_sym_error;
			__be64 rx_64b;
			__be64 rx_65b_127b;
			__be64 rx_128b_255b;
			__be64 rx_256b_511b;
			__be64 rx_512b_1023b;
			__be64 rx_1024b_1518b;
			__be64 rx_1519b_max;
			__be64 rx_छोड़ो;
			__be64 rx_ppp0;
			__be64 rx_ppp1;
			__be64 rx_ppp2;
			__be64 rx_ppp3;
			__be64 rx_ppp4;
			__be64 rx_ppp5;
			__be64 rx_ppp6;
			__be64 rx_ppp7;
			__be64 rx_less_64b;
			__be64 rx_bg_drop;
			__be64 rx_bg_trunc;
		पूर्ण all;
	पूर्ण u;
पूर्ण;

/* port loopback stats */
#घोषणा FW_NUM_LB_STATS 16
क्रमागत fw_port_lb_stats_index अणु
	FW_STAT_LB_PORT_BYTES_IX,
	FW_STAT_LB_PORT_FRAMES_IX,
	FW_STAT_LB_PORT_BCAST_IX,
	FW_STAT_LB_PORT_MCAST_IX,
	FW_STAT_LB_PORT_UCAST_IX,
	FW_STAT_LB_PORT_ERROR_IX,
	FW_STAT_LB_PORT_64B_IX,
	FW_STAT_LB_PORT_65B_127B_IX,
	FW_STAT_LB_PORT_128B_255B_IX,
	FW_STAT_LB_PORT_256B_511B_IX,
	FW_STAT_LB_PORT_512B_1023B_IX,
	FW_STAT_LB_PORT_1024B_1518B_IX,
	FW_STAT_LB_PORT_1519B_MAX_IX,
	FW_STAT_LB_PORT_DROP_FRAMES_IX
पूर्ण;

काष्ठा fw_port_lb_stats_cmd अणु
	__be32 op_to_lbport;
	__be32 retval_len16;
	जोड़ fw_port_lb_stats अणु
		काष्ठा fw_port_lb_stats_ctl अणु
			u8 nstats_bg_bm;
			u8 ix_pkd;
			__be16 r6;
			__be32 r7;
			__be64 stat0;
			__be64 stat1;
			__be64 stat2;
			__be64 stat3;
			__be64 stat4;
			__be64 stat5;
		पूर्ण ctl;
		काष्ठा fw_port_lb_stats_all अणु
			__be64 tx_bytes;
			__be64 tx_frames;
			__be64 tx_bcast;
			__be64 tx_mcast;
			__be64 tx_ucast;
			__be64 tx_error;
			__be64 tx_64b;
			__be64 tx_65b_127b;
			__be64 tx_128b_255b;
			__be64 tx_256b_511b;
			__be64 tx_512b_1023b;
			__be64 tx_1024b_1518b;
			__be64 tx_1519b_max;
			__be64 rx_lb_drop;
			__be64 rx_lb_trunc;
		पूर्ण all;
	पूर्ण u;
पूर्ण;

क्रमागत fw_ptp_subop अणु
	/* none */
	FW_PTP_SC_INIT_TIMER            = 0x00,
	FW_PTP_SC_TX_TYPE               = 0x01,
	/* init */
	FW_PTP_SC_RXTIME_STAMP          = 0x08,
	FW_PTP_SC_RDRX_TYPE             = 0x09,
	/* ts */
	FW_PTP_SC_ADJ_FREQ              = 0x10,
	FW_PTP_SC_ADJ_TIME              = 0x11,
	FW_PTP_SC_ADJ_FTIME             = 0x12,
	FW_PTP_SC_WALL_CLOCK            = 0x13,
	FW_PTP_SC_GET_TIME              = 0x14,
	FW_PTP_SC_SET_TIME              = 0x15,
पूर्ण;

काष्ठा fw_ptp_cmd अणु
	__be32 op_to_portid;
	__be32 retval_len16;
	जोड़ fw_ptp अणु
		काष्ठा fw_ptp_sc अणु
			__u8   sc;
			__u8   r3[7];
		पूर्ण scmd;
		काष्ठा fw_ptp_init अणु
			__u8   sc;
			__u8   txchan;
			__be16 असलid;
			__be16 mode;
			__be16 r3;
		पूर्ण init;
		काष्ठा fw_ptp_ts अणु
			__u8   sc;
			__u8   sign;
			__be16 r3;
			__be32 ppb;
			__be64 पंचांग;
		पूर्ण ts;
	पूर्ण u;
	__be64 r3;
पूर्ण;

#घोषणा FW_PTP_CMD_PORTID_S             0
#घोषणा FW_PTP_CMD_PORTID_M             0xf
#घोषणा FW_PTP_CMD_PORTID_V(x)          ((x) << FW_PTP_CMD_PORTID_S)
#घोषणा FW_PTP_CMD_PORTID_G(x)          \
	(((x) >> FW_PTP_CMD_PORTID_S) & FW_PTP_CMD_PORTID_M)

काष्ठा fw_rss_ind_tbl_cmd अणु
	__be32 op_to_viid;
	__be32 retval_len16;
	__be16 niqid;
	__be16 startidx;
	__be32 r3;
	__be32 iq0_to_iq2;
	__be32 iq3_to_iq5;
	__be32 iq6_to_iq8;
	__be32 iq9_to_iq11;
	__be32 iq12_to_iq14;
	__be32 iq15_to_iq17;
	__be32 iq18_to_iq20;
	__be32 iq21_to_iq23;
	__be32 iq24_to_iq26;
	__be32 iq27_to_iq29;
	__be32 iq30_iq31;
	__be32 r15_lo;
पूर्ण;

#घोषणा FW_RSS_IND_TBL_CMD_VIID_S	0
#घोषणा FW_RSS_IND_TBL_CMD_VIID_V(x)	((x) << FW_RSS_IND_TBL_CMD_VIID_S)

#घोषणा FW_RSS_IND_TBL_CMD_IQ0_S	20
#घोषणा FW_RSS_IND_TBL_CMD_IQ0_V(x)	((x) << FW_RSS_IND_TBL_CMD_IQ0_S)

#घोषणा FW_RSS_IND_TBL_CMD_IQ1_S	10
#घोषणा FW_RSS_IND_TBL_CMD_IQ1_V(x)	((x) << FW_RSS_IND_TBL_CMD_IQ1_S)

#घोषणा FW_RSS_IND_TBL_CMD_IQ2_S	0
#घोषणा FW_RSS_IND_TBL_CMD_IQ2_V(x)	((x) << FW_RSS_IND_TBL_CMD_IQ2_S)

काष्ठा fw_rss_glb_config_cmd अणु
	__be32 op_to_ग_लिखो;
	__be32 retval_len16;
	जोड़ fw_rss_glb_config अणु
		काष्ठा fw_rss_glb_config_manual अणु
			__be32 mode_pkd;
			__be32 r3;
			__be64 r4;
			__be64 r5;
		पूर्ण manual;
		काष्ठा fw_rss_glb_config_basicभव अणु
			__be32 mode_pkd;
			__be32 synmapen_to_hashtoeplitz;
			__be64 r8;
			__be64 r9;
		पूर्ण basicभव;
	पूर्ण u;
पूर्ण;

#घोषणा FW_RSS_GLB_CONFIG_CMD_MODE_S	28
#घोषणा FW_RSS_GLB_CONFIG_CMD_MODE_M	0xf
#घोषणा FW_RSS_GLB_CONFIG_CMD_MODE_V(x)	((x) << FW_RSS_GLB_CONFIG_CMD_MODE_S)
#घोषणा FW_RSS_GLB_CONFIG_CMD_MODE_G(x)	\
	(((x) >> FW_RSS_GLB_CONFIG_CMD_MODE_S) & FW_RSS_GLB_CONFIG_CMD_MODE_M)

#घोषणा FW_RSS_GLB_CONFIG_CMD_MODE_MANUAL	0
#घोषणा FW_RSS_GLB_CONFIG_CMD_MODE_BASICVIRTUAL	1

#घोषणा FW_RSS_GLB_CONFIG_CMD_SYNMAPEN_S	8
#घोषणा FW_RSS_GLB_CONFIG_CMD_SYNMAPEN_V(x)	\
	((x) << FW_RSS_GLB_CONFIG_CMD_SYNMAPEN_S)
#घोषणा FW_RSS_GLB_CONFIG_CMD_SYNMAPEN_F	\
	FW_RSS_GLB_CONFIG_CMD_SYNMAPEN_V(1U)

#घोषणा FW_RSS_GLB_CONFIG_CMD_SYN4TUPENIPV6_S		7
#घोषणा FW_RSS_GLB_CONFIG_CMD_SYN4TUPENIPV6_V(x)	\
	((x) << FW_RSS_GLB_CONFIG_CMD_SYN4TUPENIPV6_S)
#घोषणा FW_RSS_GLB_CONFIG_CMD_SYN4TUPENIPV6_F	\
	FW_RSS_GLB_CONFIG_CMD_SYN4TUPENIPV6_V(1U)

#घोषणा FW_RSS_GLB_CONFIG_CMD_SYN2TUPENIPV6_S		6
#घोषणा FW_RSS_GLB_CONFIG_CMD_SYN2TUPENIPV6_V(x)	\
	((x) << FW_RSS_GLB_CONFIG_CMD_SYN2TUPENIPV6_S)
#घोषणा FW_RSS_GLB_CONFIG_CMD_SYN2TUPENIPV6_F	\
	FW_RSS_GLB_CONFIG_CMD_SYN2TUPENIPV6_V(1U)

#घोषणा FW_RSS_GLB_CONFIG_CMD_SYN4TUPENIPV4_S		5
#घोषणा FW_RSS_GLB_CONFIG_CMD_SYN4TUPENIPV4_V(x)	\
	((x) << FW_RSS_GLB_CONFIG_CMD_SYN4TUPENIPV4_S)
#घोषणा FW_RSS_GLB_CONFIG_CMD_SYN4TUPENIPV4_F	\
	FW_RSS_GLB_CONFIG_CMD_SYN4TUPENIPV4_V(1U)

#घोषणा FW_RSS_GLB_CONFIG_CMD_SYN2TUPENIPV4_S		4
#घोषणा FW_RSS_GLB_CONFIG_CMD_SYN2TUPENIPV4_V(x)	\
	((x) << FW_RSS_GLB_CONFIG_CMD_SYN2TUPENIPV4_S)
#घोषणा FW_RSS_GLB_CONFIG_CMD_SYN2TUPENIPV4_F	\
	FW_RSS_GLB_CONFIG_CMD_SYN2TUPENIPV4_V(1U)

#घोषणा FW_RSS_GLB_CONFIG_CMD_OFDMAPEN_S	3
#घोषणा FW_RSS_GLB_CONFIG_CMD_OFDMAPEN_V(x)	\
	((x) << FW_RSS_GLB_CONFIG_CMD_OFDMAPEN_S)
#घोषणा FW_RSS_GLB_CONFIG_CMD_OFDMAPEN_F	\
	FW_RSS_GLB_CONFIG_CMD_OFDMAPEN_V(1U)

#घोषणा FW_RSS_GLB_CONFIG_CMD_TNLMAPEN_S	2
#घोषणा FW_RSS_GLB_CONFIG_CMD_TNLMAPEN_V(x)	\
	((x) << FW_RSS_GLB_CONFIG_CMD_TNLMAPEN_S)
#घोषणा FW_RSS_GLB_CONFIG_CMD_TNLMAPEN_F	\
	FW_RSS_GLB_CONFIG_CMD_TNLMAPEN_V(1U)

#घोषणा FW_RSS_GLB_CONFIG_CMD_TNLALLLKP_S	1
#घोषणा FW_RSS_GLB_CONFIG_CMD_TNLALLLKP_V(x)	\
	((x) << FW_RSS_GLB_CONFIG_CMD_TNLALLLKP_S)
#घोषणा FW_RSS_GLB_CONFIG_CMD_TNLALLLKP_F	\
	FW_RSS_GLB_CONFIG_CMD_TNLALLLKP_V(1U)

#घोषणा FW_RSS_GLB_CONFIG_CMD_HASHTOEPLITZ_S	0
#घोषणा FW_RSS_GLB_CONFIG_CMD_HASHTOEPLITZ_V(x)	\
	((x) << FW_RSS_GLB_CONFIG_CMD_HASHTOEPLITZ_S)
#घोषणा FW_RSS_GLB_CONFIG_CMD_HASHTOEPLITZ_F	\
	FW_RSS_GLB_CONFIG_CMD_HASHTOEPLITZ_V(1U)

काष्ठा fw_rss_vi_config_cmd अणु
	__be32 op_to_viid;
#घोषणा FW_RSS_VI_CONFIG_CMD_VIID(x) ((x) << 0)
	__be32 retval_len16;
	जोड़ fw_rss_vi_config अणु
		काष्ठा fw_rss_vi_config_manual अणु
			__be64 r3;
			__be64 r4;
			__be64 r5;
		पूर्ण manual;
		काष्ठा fw_rss_vi_config_basicभव अणु
			__be32 r6;
			__be32 शेषq_to_udpen;
			__be64 r9;
			__be64 r10;
		पूर्ण basicभव;
	पूर्ण u;
पूर्ण;

#घोषणा FW_RSS_VI_CONFIG_CMD_VIID_S	0
#घोषणा FW_RSS_VI_CONFIG_CMD_VIID_V(x)	((x) << FW_RSS_VI_CONFIG_CMD_VIID_S)

#घोषणा FW_RSS_VI_CONFIG_CMD_DEFAULTQ_S		16
#घोषणा FW_RSS_VI_CONFIG_CMD_DEFAULTQ_M		0x3ff
#घोषणा FW_RSS_VI_CONFIG_CMD_DEFAULTQ_V(x)	\
	((x) << FW_RSS_VI_CONFIG_CMD_DEFAULTQ_S)
#घोषणा FW_RSS_VI_CONFIG_CMD_DEFAULTQ_G(x)	\
	(((x) >> FW_RSS_VI_CONFIG_CMD_DEFAULTQ_S) & \
	 FW_RSS_VI_CONFIG_CMD_DEFAULTQ_M)

#घोषणा FW_RSS_VI_CONFIG_CMD_IP6FOURTUPEN_S	4
#घोषणा FW_RSS_VI_CONFIG_CMD_IP6FOURTUPEN_V(x)	\
	((x) << FW_RSS_VI_CONFIG_CMD_IP6FOURTUPEN_S)
#घोषणा FW_RSS_VI_CONFIG_CMD_IP6FOURTUPEN_F	\
	FW_RSS_VI_CONFIG_CMD_IP6FOURTUPEN_V(1U)

#घोषणा FW_RSS_VI_CONFIG_CMD_IP6TWOTUPEN_S	3
#घोषणा FW_RSS_VI_CONFIG_CMD_IP6TWOTUPEN_V(x)	\
	((x) << FW_RSS_VI_CONFIG_CMD_IP6TWOTUPEN_S)
#घोषणा FW_RSS_VI_CONFIG_CMD_IP6TWOTUPEN_F	\
	FW_RSS_VI_CONFIG_CMD_IP6TWOTUPEN_V(1U)

#घोषणा FW_RSS_VI_CONFIG_CMD_IP4FOURTUPEN_S	2
#घोषणा FW_RSS_VI_CONFIG_CMD_IP4FOURTUPEN_V(x)	\
	((x) << FW_RSS_VI_CONFIG_CMD_IP4FOURTUPEN_S)
#घोषणा FW_RSS_VI_CONFIG_CMD_IP4FOURTUPEN_F	\
	FW_RSS_VI_CONFIG_CMD_IP4FOURTUPEN_V(1U)

#घोषणा FW_RSS_VI_CONFIG_CMD_IP4TWOTUPEN_S	1
#घोषणा FW_RSS_VI_CONFIG_CMD_IP4TWOTUPEN_V(x)	\
	((x) << FW_RSS_VI_CONFIG_CMD_IP4TWOTUPEN_S)
#घोषणा FW_RSS_VI_CONFIG_CMD_IP4TWOTUPEN_F	\
	FW_RSS_VI_CONFIG_CMD_IP4TWOTUPEN_V(1U)

#घोषणा FW_RSS_VI_CONFIG_CMD_UDPEN_S	0
#घोषणा FW_RSS_VI_CONFIG_CMD_UDPEN_V(x)	((x) << FW_RSS_VI_CONFIG_CMD_UDPEN_S)
#घोषणा FW_RSS_VI_CONFIG_CMD_UDPEN_F	FW_RSS_VI_CONFIG_CMD_UDPEN_V(1U)

क्रमागत fw_sched_sc अणु
	FW_SCHED_SC_PARAMS		= 1,
पूर्ण;

काष्ठा fw_sched_cmd अणु
	__be32 op_to_ग_लिखो;
	__be32 retval_len16;
	जोड़ fw_sched अणु
		काष्ठा fw_sched_config अणु
			__u8   sc;
			__u8   type;
			__u8   minmaxen;
			__u8   r3[5];
			__u8   nclasses[4];
			__be32 r4;
		पूर्ण config;
		काष्ठा fw_sched_params अणु
			__u8   sc;
			__u8   type;
			__u8   level;
			__u8   mode;
			__u8   unit;
			__u8   rate;
			__u8   ch;
			__u8   cl;
			__be32 min;
			__be32 max;
			__be16 weight;
			__be16 pktsize;
			__be16 burstsize;
			__be16 r4;
		पूर्ण params;
	पूर्ण u;
पूर्ण;

काष्ठा fw_clip_cmd अणु
	__be32 op_to_ग_लिखो;
	__be32 alloc_to_len16;
	__be64 ip_hi;
	__be64 ip_lo;
	__be32 r4[2];
पूर्ण;

#घोषणा FW_CLIP_CMD_ALLOC_S     31
#घोषणा FW_CLIP_CMD_ALLOC_V(x)  ((x) << FW_CLIP_CMD_ALLOC_S)
#घोषणा FW_CLIP_CMD_ALLOC_F     FW_CLIP_CMD_ALLOC_V(1U)

#घोषणा FW_CLIP_CMD_FREE_S      30
#घोषणा FW_CLIP_CMD_FREE_V(x)   ((x) << FW_CLIP_CMD_FREE_S)
#घोषणा FW_CLIP_CMD_FREE_F      FW_CLIP_CMD_FREE_V(1U)

क्रमागत fw_error_type अणु
	FW_ERROR_TYPE_EXCEPTION		= 0x0,
	FW_ERROR_TYPE_HWMODULE		= 0x1,
	FW_ERROR_TYPE_WR		= 0x2,
	FW_ERROR_TYPE_ACL		= 0x3,
पूर्ण;

काष्ठा fw_error_cmd अणु
	__be32 op_to_type;
	__be32 len16_pkd;
	जोड़ fw_error अणु
		काष्ठा fw_error_exception अणु
			__be32 info[6];
		पूर्ण exception;
		काष्ठा fw_error_hwmodule अणु
			__be32 regaddr;
			__be32 regval;
		पूर्ण hwmodule;
		काष्ठा fw_error_wr अणु
			__be16 cidx;
			__be16 pfn_vfn;
			__be32 eqid;
			u8 wrhdr[16];
		पूर्ण wr;
		काष्ठा fw_error_acl अणु
			__be16 cidx;
			__be16 pfn_vfn;
			__be32 eqid;
			__be16 mv_pkd;
			u8 val[6];
			__be64 r4;
		पूर्ण acl;
	पूर्ण u;
पूर्ण;

काष्ठा fw_debug_cmd अणु
	__be32 op_type;
	__be32 len16_pkd;
	जोड़ fw_debug अणु
		काष्ठा fw_debug_निश्चित अणु
			__be32 fcid;
			__be32 line;
			__be32 x;
			__be32 y;
			u8 filename_0_7[8];
			u8 filename_8_15[8];
			__be64 r3;
		पूर्ण निश्चित;
		काष्ठा fw_debug_prt अणु
			__be16 dprtstridx;
			__be16 r3[3];
			__be32 dprtstrparam0;
			__be32 dprtstrparam1;
			__be32 dprtstrparam2;
			__be32 dprtstrparam3;
		पूर्ण prt;
	पूर्ण u;
पूर्ण;

#घोषणा FW_DEBUG_CMD_TYPE_S	0
#घोषणा FW_DEBUG_CMD_TYPE_M	0xff
#घोषणा FW_DEBUG_CMD_TYPE_G(x)	\
	(((x) >> FW_DEBUG_CMD_TYPE_S) & FW_DEBUG_CMD_TYPE_M)

काष्ठा fw_hma_cmd अणु
	__be32 op_pkd;
	__be32 retval_len16;
	__be32 mode_to_pcie_params;
	__be32 naddr_size;
	__be32 addr_size_pkd;
	__be32 r6;
	__be64 phy_address[5];
पूर्ण;

#घोषणा FW_HMA_CMD_MODE_S	31
#घोषणा FW_HMA_CMD_MODE_M	0x1
#घोषणा FW_HMA_CMD_MODE_V(x)	((x) << FW_HMA_CMD_MODE_S)
#घोषणा FW_HMA_CMD_MODE_G(x)	\
	(((x) >> FW_HMA_CMD_MODE_S) & FW_HMA_CMD_MODE_M)
#घोषणा FW_HMA_CMD_MODE_F	FW_HMA_CMD_MODE_V(1U)

#घोषणा FW_HMA_CMD_SOC_S	30
#घोषणा FW_HMA_CMD_SOC_M	0x1
#घोषणा FW_HMA_CMD_SOC_V(x)	((x) << FW_HMA_CMD_SOC_S)
#घोषणा FW_HMA_CMD_SOC_G(x)	(((x) >> FW_HMA_CMD_SOC_S) & FW_HMA_CMD_SOC_M)
#घोषणा FW_HMA_CMD_SOC_F	FW_HMA_CMD_SOC_V(1U)

#घोषणा FW_HMA_CMD_EOC_S	29
#घोषणा FW_HMA_CMD_EOC_M	0x1
#घोषणा FW_HMA_CMD_EOC_V(x)	((x) << FW_HMA_CMD_EOC_S)
#घोषणा FW_HMA_CMD_EOC_G(x)	(((x) >> FW_HMA_CMD_EOC_S) & FW_HMA_CMD_EOC_M)
#घोषणा FW_HMA_CMD_EOC_F	FW_HMA_CMD_EOC_V(1U)

#घोषणा FW_HMA_CMD_PCIE_PARAMS_S	0
#घोषणा FW_HMA_CMD_PCIE_PARAMS_M	0x7ffffff
#घोषणा FW_HMA_CMD_PCIE_PARAMS_V(x)	((x) << FW_HMA_CMD_PCIE_PARAMS_S)
#घोषणा FW_HMA_CMD_PCIE_PARAMS_G(x)	\
	(((x) >> FW_HMA_CMD_PCIE_PARAMS_S) & FW_HMA_CMD_PCIE_PARAMS_M)

#घोषणा FW_HMA_CMD_NADDR_S	12
#घोषणा FW_HMA_CMD_NADDR_M	0x3f
#घोषणा FW_HMA_CMD_NADDR_V(x)	((x) << FW_HMA_CMD_NADDR_S)
#घोषणा FW_HMA_CMD_NADDR_G(x)	\
	(((x) >> FW_HMA_CMD_NADDR_S) & FW_HMA_CMD_NADDR_M)

#घोषणा FW_HMA_CMD_SIZE_S	0
#घोषणा FW_HMA_CMD_SIZE_M	0xfff
#घोषणा FW_HMA_CMD_SIZE_V(x)	((x) << FW_HMA_CMD_SIZE_S)
#घोषणा FW_HMA_CMD_SIZE_G(x)	\
	(((x) >> FW_HMA_CMD_SIZE_S) & FW_HMA_CMD_SIZE_M)

#घोषणा FW_HMA_CMD_ADDR_SIZE_S		11
#घोषणा FW_HMA_CMD_ADDR_SIZE_M		0x1fffff
#घोषणा FW_HMA_CMD_ADDR_SIZE_V(x)	((x) << FW_HMA_CMD_ADDR_SIZE_S)
#घोषणा FW_HMA_CMD_ADDR_SIZE_G(x)	\
	(((x) >> FW_HMA_CMD_ADDR_SIZE_S) & FW_HMA_CMD_ADDR_SIZE_M)

क्रमागत pcie_fw_eval अणु
	PCIE_FW_EVAL_CRASH = 0,
पूर्ण;

#घोषणा PCIE_FW_ERR_S		31
#घोषणा PCIE_FW_ERR_V(x)	((x) << PCIE_FW_ERR_S)
#घोषणा PCIE_FW_ERR_F		PCIE_FW_ERR_V(1U)

#घोषणा PCIE_FW_INIT_S		30
#घोषणा PCIE_FW_INIT_V(x)	((x) << PCIE_FW_INIT_S)
#घोषणा PCIE_FW_INIT_F		PCIE_FW_INIT_V(1U)

#घोषणा PCIE_FW_HALT_S          29
#घोषणा PCIE_FW_HALT_V(x)       ((x) << PCIE_FW_HALT_S)
#घोषणा PCIE_FW_HALT_F          PCIE_FW_HALT_V(1U)

#घोषणा PCIE_FW_EVAL_S		24
#घोषणा PCIE_FW_EVAL_M		0x7
#घोषणा PCIE_FW_EVAL_G(x)	(((x) >> PCIE_FW_EVAL_S) & PCIE_FW_EVAL_M)

#घोषणा PCIE_FW_MASTER_VLD_S	15
#घोषणा PCIE_FW_MASTER_VLD_V(x)	((x) << PCIE_FW_MASTER_VLD_S)
#घोषणा PCIE_FW_MASTER_VLD_F	PCIE_FW_MASTER_VLD_V(1U)

#घोषणा PCIE_FW_MASTER_S	12
#घोषणा PCIE_FW_MASTER_M	0x7
#घोषणा PCIE_FW_MASTER_V(x)	((x) << PCIE_FW_MASTER_S)
#घोषणा PCIE_FW_MASTER_G(x)	(((x) >> PCIE_FW_MASTER_S) & PCIE_FW_MASTER_M)

काष्ठा fw_hdr अणु
	u8 ver;
	u8 chip;			/* terminator chip type */
	__be16	len512;			/* bin length in units of 512-bytes */
	__be32	fw_ver;			/* firmware version */
	__be32	tp_microcode_ver;
	u8 पूर्णांकfver_nic;
	u8 पूर्णांकfver_vnic;
	u8 पूर्णांकfver_ofld;
	u8 पूर्णांकfver_ri;
	u8 पूर्णांकfver_iscsipdu;
	u8 पूर्णांकfver_iscsi;
	u8 पूर्णांकfver_fcoepdu;
	u8 पूर्णांकfver_fcoe;
	__u32   reserved2;
	__u32   reserved3;
	__u32   reserved4;
	__be32  flags;
	__be32  reserved6[23];
पूर्ण;

क्रमागत fw_hdr_chip अणु
	FW_HDR_CHIP_T4,
	FW_HDR_CHIP_T5,
	FW_HDR_CHIP_T6
पूर्ण;

#घोषणा FW_HDR_FW_VER_MAJOR_S	24
#घोषणा FW_HDR_FW_VER_MAJOR_M	0xff
#घोषणा FW_HDR_FW_VER_MAJOR_V(x) \
	((x) << FW_HDR_FW_VER_MAJOR_S)
#घोषणा FW_HDR_FW_VER_MAJOR_G(x) \
	(((x) >> FW_HDR_FW_VER_MAJOR_S) & FW_HDR_FW_VER_MAJOR_M)

#घोषणा FW_HDR_FW_VER_MINOR_S	16
#घोषणा FW_HDR_FW_VER_MINOR_M	0xff
#घोषणा FW_HDR_FW_VER_MINOR_V(x) \
	((x) << FW_HDR_FW_VER_MINOR_S)
#घोषणा FW_HDR_FW_VER_MINOR_G(x) \
	(((x) >> FW_HDR_FW_VER_MINOR_S) & FW_HDR_FW_VER_MINOR_M)

#घोषणा FW_HDR_FW_VER_MICRO_S	8
#घोषणा FW_HDR_FW_VER_MICRO_M	0xff
#घोषणा FW_HDR_FW_VER_MICRO_V(x) \
	((x) << FW_HDR_FW_VER_MICRO_S)
#घोषणा FW_HDR_FW_VER_MICRO_G(x) \
	(((x) >> FW_HDR_FW_VER_MICRO_S) & FW_HDR_FW_VER_MICRO_M)

#घोषणा FW_HDR_FW_VER_BUILD_S	0
#घोषणा FW_HDR_FW_VER_BUILD_M	0xff
#घोषणा FW_HDR_FW_VER_BUILD_V(x) \
	((x) << FW_HDR_FW_VER_BUILD_S)
#घोषणा FW_HDR_FW_VER_BUILD_G(x) \
	(((x) >> FW_HDR_FW_VER_BUILD_S) & FW_HDR_FW_VER_BUILD_M)

क्रमागत fw_hdr_पूर्णांकfver अणु
	FW_HDR_INTFVER_NIC      = 0x00,
	FW_HDR_INTFVER_VNIC     = 0x00,
	FW_HDR_INTFVER_OFLD     = 0x00,
	FW_HDR_INTFVER_RI       = 0x00,
	FW_HDR_INTFVER_ISCSIPDU = 0x00,
	FW_HDR_INTFVER_ISCSI    = 0x00,
	FW_HDR_INTFVER_FCOEPDU  = 0x00,
	FW_HDR_INTFVER_FCOE     = 0x00,
पूर्ण;

क्रमागत fw_hdr_flags अणु
	FW_HDR_FLAGS_RESET_HALT = 0x00000001,
पूर्ण;

/* length of the क्रमmatting string  */
#घोषणा FW_DEVLOG_FMT_LEN	192

/* maximum number of the क्रमmatting string parameters */
#घोषणा FW_DEVLOG_FMT_PARAMS_NUM 8

/* priority levels */
क्रमागत fw_devlog_level अणु
	FW_DEVLOG_LEVEL_EMERG	= 0x0,
	FW_DEVLOG_LEVEL_CRIT	= 0x1,
	FW_DEVLOG_LEVEL_ERR	= 0x2,
	FW_DEVLOG_LEVEL_NOTICE	= 0x3,
	FW_DEVLOG_LEVEL_INFO	= 0x4,
	FW_DEVLOG_LEVEL_DEBUG	= 0x5,
	FW_DEVLOG_LEVEL_MAX	= 0x5,
पूर्ण;

/* facilities that may send a log message */
क्रमागत fw_devlog_facility अणु
	FW_DEVLOG_FACILITY_CORE		= 0x00,
	FW_DEVLOG_FACILITY_CF		= 0x01,
	FW_DEVLOG_FACILITY_SCHED	= 0x02,
	FW_DEVLOG_FACILITY_TIMER	= 0x04,
	FW_DEVLOG_FACILITY_RES		= 0x06,
	FW_DEVLOG_FACILITY_HW		= 0x08,
	FW_DEVLOG_FACILITY_FLR		= 0x10,
	FW_DEVLOG_FACILITY_DMAQ		= 0x12,
	FW_DEVLOG_FACILITY_PHY		= 0x14,
	FW_DEVLOG_FACILITY_MAC		= 0x16,
	FW_DEVLOG_FACILITY_PORT		= 0x18,
	FW_DEVLOG_FACILITY_VI		= 0x1A,
	FW_DEVLOG_FACILITY_FILTER	= 0x1C,
	FW_DEVLOG_FACILITY_ACL		= 0x1E,
	FW_DEVLOG_FACILITY_TM		= 0x20,
	FW_DEVLOG_FACILITY_QFC		= 0x22,
	FW_DEVLOG_FACILITY_DCB		= 0x24,
	FW_DEVLOG_FACILITY_ETH		= 0x26,
	FW_DEVLOG_FACILITY_OFLD		= 0x28,
	FW_DEVLOG_FACILITY_RI		= 0x2A,
	FW_DEVLOG_FACILITY_ISCSI	= 0x2C,
	FW_DEVLOG_FACILITY_FCOE		= 0x2E,
	FW_DEVLOG_FACILITY_FOISCSI	= 0x30,
	FW_DEVLOG_FACILITY_FOFCOE	= 0x32,
	FW_DEVLOG_FACILITY_CHNET        = 0x34,
	FW_DEVLOG_FACILITY_MAX          = 0x34,
पूर्ण;

/* log message क्रमmat */
काष्ठा fw_devlog_e अणु
	__be64	बारtamp;
	__be32	seqno;
	__be16	reserved1;
	__u8	level;
	__u8	facility;
	__u8	fmt[FW_DEVLOG_FMT_LEN];
	__be32	params[FW_DEVLOG_FMT_PARAMS_NUM];
	__be32	reserved3[4];
पूर्ण;

काष्ठा fw_devlog_cmd अणु
	__be32 op_to_ग_लिखो;
	__be32 retval_len16;
	__u8   level;
	__u8   r2[7];
	__be32 memtype_devlog_memaddr16_devlog;
	__be32 memsize_devlog;
	__be32 r3[2];
पूर्ण;

#घोषणा FW_DEVLOG_CMD_MEMTYPE_DEVLOG_S		28
#घोषणा FW_DEVLOG_CMD_MEMTYPE_DEVLOG_M		0xf
#घोषणा FW_DEVLOG_CMD_MEMTYPE_DEVLOG_G(x)	\
	(((x) >> FW_DEVLOG_CMD_MEMTYPE_DEVLOG_S) & \
	 FW_DEVLOG_CMD_MEMTYPE_DEVLOG_M)

#घोषणा FW_DEVLOG_CMD_MEMADDR16_DEVLOG_S	0
#घोषणा FW_DEVLOG_CMD_MEMADDR16_DEVLOG_M	0xfffffff
#घोषणा FW_DEVLOG_CMD_MEMADDR16_DEVLOG_G(x)	\
	(((x) >> FW_DEVLOG_CMD_MEMADDR16_DEVLOG_S) & \
	 FW_DEVLOG_CMD_MEMADDR16_DEVLOG_M)

/* P C I E   F W   P F 7   R E G I S T E R */

/* PF7 stores the Firmware Device Log parameters which allows Host Drivers to
 * access the "devlog" which needing to contact firmware.  The encoding is
 * mostly the same as that वापसed by the DEVLOG command except क्रम the size
 * which is encoded as the number of entries in multiples-1 of 128 here rather
 * than the memory size as is करोne in the DEVLOG command.  Thus, 0 means 128
 * and 15 means 2048.  This of course in turn स्थिरrains the allowed values
 * क्रम the devlog size ...
 */
#घोषणा PCIE_FW_PF_DEVLOG		7

#घोषणा PCIE_FW_PF_DEVLOG_NENTRIES128_S	28
#घोषणा PCIE_FW_PF_DEVLOG_NENTRIES128_M	0xf
#घोषणा PCIE_FW_PF_DEVLOG_NENTRIES128_V(x) \
	((x) << PCIE_FW_PF_DEVLOG_NENTRIES128_S)
#घोषणा PCIE_FW_PF_DEVLOG_NENTRIES128_G(x) \
	(((x) >> PCIE_FW_PF_DEVLOG_NENTRIES128_S) & \
	 PCIE_FW_PF_DEVLOG_NENTRIES128_M)

#घोषणा PCIE_FW_PF_DEVLOG_ADDR16_S	4
#घोषणा PCIE_FW_PF_DEVLOG_ADDR16_M	0xffffff
#घोषणा PCIE_FW_PF_DEVLOG_ADDR16_V(x)	((x) << PCIE_FW_PF_DEVLOG_ADDR16_S)
#घोषणा PCIE_FW_PF_DEVLOG_ADDR16_G(x) \
	(((x) >> PCIE_FW_PF_DEVLOG_ADDR16_S) & PCIE_FW_PF_DEVLOG_ADDR16_M)

#घोषणा PCIE_FW_PF_DEVLOG_MEMTYPE_S	0
#घोषणा PCIE_FW_PF_DEVLOG_MEMTYPE_M	0xf
#घोषणा PCIE_FW_PF_DEVLOG_MEMTYPE_V(x)	((x) << PCIE_FW_PF_DEVLOG_MEMTYPE_S)
#घोषणा PCIE_FW_PF_DEVLOG_MEMTYPE_G(x) \
	(((x) >> PCIE_FW_PF_DEVLOG_MEMTYPE_S) & PCIE_FW_PF_DEVLOG_MEMTYPE_M)

#घोषणा MAX_IMM_OFLD_TX_DATA_WR_LEN (0xff + माप(काष्ठा fw_ofld_tx_data_wr))

काष्ठा fw_crypto_lookaside_wr अणु
	__be32 op_to_cctx_size;
	__be32 len16_pkd;
	__be32 session_id;
	__be32 rx_chid_to_rx_q_id;
	__be32 key_addr;
	__be32 pld_size_hash_size;
	__be64 cookie;
पूर्ण;

#घोषणा FW_CRYPTO_LOOKASIDE_WR_OPCODE_S 24
#घोषणा FW_CRYPTO_LOOKASIDE_WR_OPCODE_M 0xff
#घोषणा FW_CRYPTO_LOOKASIDE_WR_OPCODE_V(x) \
	((x) << FW_CRYPTO_LOOKASIDE_WR_OPCODE_S)
#घोषणा FW_CRYPTO_LOOKASIDE_WR_OPCODE_G(x) \
	(((x) >> FW_CRYPTO_LOOKASIDE_WR_OPCODE_S) & \
	 FW_CRYPTO_LOOKASIDE_WR_OPCODE_M)

#घोषणा FW_CRYPTO_LOOKASIDE_WR_COMPL_S 23
#घोषणा FW_CRYPTO_LOOKASIDE_WR_COMPL_M 0x1
#घोषणा FW_CRYPTO_LOOKASIDE_WR_COMPL_V(x) \
	((x) << FW_CRYPTO_LOOKASIDE_WR_COMPL_S)
#घोषणा FW_CRYPTO_LOOKASIDE_WR_COMPL_G(x) \
	(((x) >> FW_CRYPTO_LOOKASIDE_WR_COMPL_S) & \
	 FW_CRYPTO_LOOKASIDE_WR_COMPL_M)
#घोषणा FW_CRYPTO_LOOKASIDE_WR_COMPL_F FW_CRYPTO_LOOKASIDE_WR_COMPL_V(1U)

#घोषणा FW_CRYPTO_LOOKASIDE_WR_IMM_LEN_S 15
#घोषणा FW_CRYPTO_LOOKASIDE_WR_IMM_LEN_M 0xff
#घोषणा FW_CRYPTO_LOOKASIDE_WR_IMM_LEN_V(x) \
	((x) << FW_CRYPTO_LOOKASIDE_WR_IMM_LEN_S)
#घोषणा FW_CRYPTO_LOOKASIDE_WR_IMM_LEN_G(x) \
	(((x) >> FW_CRYPTO_LOOKASIDE_WR_IMM_LEN_S) & \
	 FW_CRYPTO_LOOKASIDE_WR_IMM_LEN_M)

#घोषणा FW_CRYPTO_LOOKASIDE_WR_CCTX_LOC_S 5
#घोषणा FW_CRYPTO_LOOKASIDE_WR_CCTX_LOC_M 0x3
#घोषणा FW_CRYPTO_LOOKASIDE_WR_CCTX_LOC_V(x) \
	((x) << FW_CRYPTO_LOOKASIDE_WR_CCTX_LOC_S)
#घोषणा FW_CRYPTO_LOOKASIDE_WR_CCTX_LOC_G(x) \
	(((x) >> FW_CRYPTO_LOOKASIDE_WR_CCTX_LOC_S) & \
	 FW_CRYPTO_LOOKASIDE_WR_CCTX_LOC_M)

#घोषणा FW_CRYPTO_LOOKASIDE_WR_CCTX_SIZE_S 0
#घोषणा FW_CRYPTO_LOOKASIDE_WR_CCTX_SIZE_M 0x1f
#घोषणा FW_CRYPTO_LOOKASIDE_WR_CCTX_SIZE_V(x) \
	((x) << FW_CRYPTO_LOOKASIDE_WR_CCTX_SIZE_S)
#घोषणा FW_CRYPTO_LOOKASIDE_WR_CCTX_SIZE_G(x) \
	(((x) >> FW_CRYPTO_LOOKASIDE_WR_CCTX_SIZE_S) & \
	 FW_CRYPTO_LOOKASIDE_WR_CCTX_SIZE_M)

#घोषणा FW_CRYPTO_LOOKASIDE_WR_LEN16_S 0
#घोषणा FW_CRYPTO_LOOKASIDE_WR_LEN16_M 0xff
#घोषणा FW_CRYPTO_LOOKASIDE_WR_LEN16_V(x) \
	((x) << FW_CRYPTO_LOOKASIDE_WR_LEN16_S)
#घोषणा FW_CRYPTO_LOOKASIDE_WR_LEN16_G(x) \
	(((x) >> FW_CRYPTO_LOOKASIDE_WR_LEN16_S) & \
	 FW_CRYPTO_LOOKASIDE_WR_LEN16_M)

#घोषणा FW_CRYPTO_LOOKASIDE_WR_RX_CHID_S 29
#घोषणा FW_CRYPTO_LOOKASIDE_WR_RX_CHID_M 0x3
#घोषणा FW_CRYPTO_LOOKASIDE_WR_RX_CHID_V(x) \
	((x) << FW_CRYPTO_LOOKASIDE_WR_RX_CHID_S)
#घोषणा FW_CRYPTO_LOOKASIDE_WR_RX_CHID_G(x) \
	(((x) >> FW_CRYPTO_LOOKASIDE_WR_RX_CHID_S) & \
	 FW_CRYPTO_LOOKASIDE_WR_RX_CHID_M)

#घोषणा FW_CRYPTO_LOOKASIDE_WR_LCB_S  27
#घोषणा FW_CRYPTO_LOOKASIDE_WR_LCB_M  0x3
#घोषणा FW_CRYPTO_LOOKASIDE_WR_LCB_V(x) \
	((x) << FW_CRYPTO_LOOKASIDE_WR_LCB_S)
#घोषणा FW_CRYPTO_LOOKASIDE_WR_LCB_G(x) \
	(((x) >> FW_CRYPTO_LOOKASIDE_WR_LCB_S) & FW_CRYPTO_LOOKASIDE_WR_LCB_M)

#घोषणा FW_CRYPTO_LOOKASIDE_WR_PHASH_S 25
#घोषणा FW_CRYPTO_LOOKASIDE_WR_PHASH_M 0x3
#घोषणा FW_CRYPTO_LOOKASIDE_WR_PHASH_V(x) \
	((x) << FW_CRYPTO_LOOKASIDE_WR_PHASH_S)
#घोषणा FW_CRYPTO_LOOKASIDE_WR_PHASH_G(x) \
	(((x) >> FW_CRYPTO_LOOKASIDE_WR_PHASH_S) & \
	 FW_CRYPTO_LOOKASIDE_WR_PHASH_M)

#घोषणा FW_CRYPTO_LOOKASIDE_WR_IV_S   23
#घोषणा FW_CRYPTO_LOOKASIDE_WR_IV_M   0x3
#घोषणा FW_CRYPTO_LOOKASIDE_WR_IV_V(x) \
	((x) << FW_CRYPTO_LOOKASIDE_WR_IV_S)
#घोषणा FW_CRYPTO_LOOKASIDE_WR_IV_G(x) \
	(((x) >> FW_CRYPTO_LOOKASIDE_WR_IV_S) & FW_CRYPTO_LOOKASIDE_WR_IV_M)

#घोषणा FW_CRYPTO_LOOKASIDE_WR_FQIDX_S   15
#घोषणा FW_CRYPTO_LOOKASIDE_WR_FQIDX_M   0xff
#घोषणा FW_CRYPTO_LOOKASIDE_WR_FQIDX_V(x) \
	((x) << FW_CRYPTO_LOOKASIDE_WR_FQIDX_S)
#घोषणा FW_CRYPTO_LOOKASIDE_WR_FQIDX_G(x) \
	(((x) >> FW_CRYPTO_LOOKASIDE_WR_FQIDX_S) & \
	 FW_CRYPTO_LOOKASIDE_WR_FQIDX_M)

#घोषणा FW_CRYPTO_LOOKASIDE_WR_TX_CH_S 10
#घोषणा FW_CRYPTO_LOOKASIDE_WR_TX_CH_M 0x3
#घोषणा FW_CRYPTO_LOOKASIDE_WR_TX_CH_V(x) \
	((x) << FW_CRYPTO_LOOKASIDE_WR_TX_CH_S)
#घोषणा FW_CRYPTO_LOOKASIDE_WR_TX_CH_G(x) \
	(((x) >> FW_CRYPTO_LOOKASIDE_WR_TX_CH_S) & \
	 FW_CRYPTO_LOOKASIDE_WR_TX_CH_M)

#घोषणा FW_CRYPTO_LOOKASIDE_WR_RX_Q_ID_S 0
#घोषणा FW_CRYPTO_LOOKASIDE_WR_RX_Q_ID_M 0x3ff
#घोषणा FW_CRYPTO_LOOKASIDE_WR_RX_Q_ID_V(x) \
	((x) << FW_CRYPTO_LOOKASIDE_WR_RX_Q_ID_S)
#घोषणा FW_CRYPTO_LOOKASIDE_WR_RX_Q_ID_G(x) \
	(((x) >> FW_CRYPTO_LOOKASIDE_WR_RX_Q_ID_S) & \
	 FW_CRYPTO_LOOKASIDE_WR_RX_Q_ID_M)

#घोषणा FW_CRYPTO_LOOKASIDE_WR_PLD_SIZE_S 24
#घोषणा FW_CRYPTO_LOOKASIDE_WR_PLD_SIZE_M 0xff
#घोषणा FW_CRYPTO_LOOKASIDE_WR_PLD_SIZE_V(x) \
	((x) << FW_CRYPTO_LOOKASIDE_WR_PLD_SIZE_S)
#घोषणा FW_CRYPTO_LOOKASIDE_WR_PLD_SIZE_G(x) \
	(((x) >> FW_CRYPTO_LOOKASIDE_WR_PLD_SIZE_S) & \
	 FW_CRYPTO_LOOKASIDE_WR_PLD_SIZE_M)

#घोषणा FW_CRYPTO_LOOKASIDE_WR_HASH_SIZE_S 17
#घोषणा FW_CRYPTO_LOOKASIDE_WR_HASH_SIZE_M 0x7f
#घोषणा FW_CRYPTO_LOOKASIDE_WR_HASH_SIZE_V(x) \
	((x) << FW_CRYPTO_LOOKASIDE_WR_HASH_SIZE_S)
#घोषणा FW_CRYPTO_LOOKASIDE_WR_HASH_SIZE_G(x) \
	(((x) >> FW_CRYPTO_LOOKASIDE_WR_HASH_SIZE_S) & \
	 FW_CRYPTO_LOOKASIDE_WR_HASH_SIZE_M)

काष्ठा fw_tlstx_data_wr अणु
	__be32 op_to_immdlen;
	__be32 flowid_len16;
	__be32 plen;
	__be32 lsodisable_to_flags;
	__be32 r5;
	__be32 ctxloc_to_exp;
	__be16 mfs;
	__be16 adjustedplen_pkd;
	__be16 expinplenmax_pkd;
	u8   pdusinplenmax_pkd;
	u8   r10;
पूर्ण;

#घोषणा FW_TLSTX_DATA_WR_OPCODE_S       24
#घोषणा FW_TLSTX_DATA_WR_OPCODE_M       0xff
#घोषणा FW_TLSTX_DATA_WR_OPCODE_V(x)    ((x) << FW_TLSTX_DATA_WR_OPCODE_S)
#घोषणा FW_TLSTX_DATA_WR_OPCODE_G(x)    \
	(((x) >> FW_TLSTX_DATA_WR_OPCODE_S) & FW_TLSTX_DATA_WR_OPCODE_M)

#घोषणा FW_TLSTX_DATA_WR_COMPL_S        21
#घोषणा FW_TLSTX_DATA_WR_COMPL_M        0x1
#घोषणा FW_TLSTX_DATA_WR_COMPL_V(x)     ((x) << FW_TLSTX_DATA_WR_COMPL_S)
#घोषणा FW_TLSTX_DATA_WR_COMPL_G(x)     \
	(((x) >> FW_TLSTX_DATA_WR_COMPL_S) & FW_TLSTX_DATA_WR_COMPL_M)
#घोषणा FW_TLSTX_DATA_WR_COMPL_F        FW_TLSTX_DATA_WR_COMPL_V(1U)

#घोषणा FW_TLSTX_DATA_WR_IMMDLEN_S      0
#घोषणा FW_TLSTX_DATA_WR_IMMDLEN_M      0xff
#घोषणा FW_TLSTX_DATA_WR_IMMDLEN_V(x)   ((x) << FW_TLSTX_DATA_WR_IMMDLEN_S)
#घोषणा FW_TLSTX_DATA_WR_IMMDLEN_G(x)   \
	(((x) >> FW_TLSTX_DATA_WR_IMMDLEN_S) & FW_TLSTX_DATA_WR_IMMDLEN_M)

#घोषणा FW_TLSTX_DATA_WR_FLOWID_S       8
#घोषणा FW_TLSTX_DATA_WR_FLOWID_M       0xfffff
#घोषणा FW_TLSTX_DATA_WR_FLOWID_V(x)    ((x) << FW_TLSTX_DATA_WR_FLOWID_S)
#घोषणा FW_TLSTX_DATA_WR_FLOWID_G(x)    \
	(((x) >> FW_TLSTX_DATA_WR_FLOWID_S) & FW_TLSTX_DATA_WR_FLOWID_M)

#घोषणा FW_TLSTX_DATA_WR_LEN16_S        0
#घोषणा FW_TLSTX_DATA_WR_LEN16_M        0xff
#घोषणा FW_TLSTX_DATA_WR_LEN16_V(x)     ((x) << FW_TLSTX_DATA_WR_LEN16_S)
#घोषणा FW_TLSTX_DATA_WR_LEN16_G(x)     \
	(((x) >> FW_TLSTX_DATA_WR_LEN16_S) & FW_TLSTX_DATA_WR_LEN16_M)

#घोषणा FW_TLSTX_DATA_WR_LSODISABLE_S   31
#घोषणा FW_TLSTX_DATA_WR_LSODISABLE_M   0x1
#घोषणा FW_TLSTX_DATA_WR_LSODISABLE_V(x) \
	((x) << FW_TLSTX_DATA_WR_LSODISABLE_S)
#घोषणा FW_TLSTX_DATA_WR_LSODISABLE_G(x) \
	(((x) >> FW_TLSTX_DATA_WR_LSODISABLE_S) & FW_TLSTX_DATA_WR_LSODISABLE_M)
#घोषणा FW_TLSTX_DATA_WR_LSODISABLE_F   FW_TLSTX_DATA_WR_LSODISABLE_V(1U)

#घोषणा FW_TLSTX_DATA_WR_ALIGNPLD_S     30
#घोषणा FW_TLSTX_DATA_WR_ALIGNPLD_M     0x1
#घोषणा FW_TLSTX_DATA_WR_ALIGNPLD_V(x)  ((x) << FW_TLSTX_DATA_WR_ALIGNPLD_S)
#घोषणा FW_TLSTX_DATA_WR_ALIGNPLD_G(x)  \
	(((x) >> FW_TLSTX_DATA_WR_ALIGNPLD_S) & FW_TLSTX_DATA_WR_ALIGNPLD_M)
#घोषणा FW_TLSTX_DATA_WR_ALIGNPLD_F     FW_TLSTX_DATA_WR_ALIGNPLD_V(1U)

#घोषणा FW_TLSTX_DATA_WR_ALIGNPLDSHOVE_S 29
#घोषणा FW_TLSTX_DATA_WR_ALIGNPLDSHOVE_M 0x1
#घोषणा FW_TLSTX_DATA_WR_ALIGNPLDSHOVE_V(x) \
	((x) << FW_TLSTX_DATA_WR_ALIGNPLDSHOVE_S)
#घोषणा FW_TLSTX_DATA_WR_ALIGNPLDSHOVE_G(x) \
	(((x) >> FW_TLSTX_DATA_WR_ALIGNPLDSHOVE_S) & \
	FW_TLSTX_DATA_WR_ALIGNPLDSHOVE_M)
#घोषणा FW_TLSTX_DATA_WR_ALIGNPLDSHOVE_F FW_TLSTX_DATA_WR_ALIGNPLDSHOVE_V(1U)

#घोषणा FW_TLSTX_DATA_WR_FLAGS_S        0
#घोषणा FW_TLSTX_DATA_WR_FLAGS_M        0xfffffff
#घोषणा FW_TLSTX_DATA_WR_FLAGS_V(x)     ((x) << FW_TLSTX_DATA_WR_FLAGS_S)
#घोषणा FW_TLSTX_DATA_WR_FLAGS_G(x)     \
	(((x) >> FW_TLSTX_DATA_WR_FLAGS_S) & FW_TLSTX_DATA_WR_FLAGS_M)

#घोषणा FW_TLSTX_DATA_WR_CTXLOC_S       30
#घोषणा FW_TLSTX_DATA_WR_CTXLOC_M       0x3
#घोषणा FW_TLSTX_DATA_WR_CTXLOC_V(x)    ((x) << FW_TLSTX_DATA_WR_CTXLOC_S)
#घोषणा FW_TLSTX_DATA_WR_CTXLOC_G(x)    \
	(((x) >> FW_TLSTX_DATA_WR_CTXLOC_S) & FW_TLSTX_DATA_WR_CTXLOC_M)

#घोषणा FW_TLSTX_DATA_WR_IVDSGL_S       29
#घोषणा FW_TLSTX_DATA_WR_IVDSGL_M       0x1
#घोषणा FW_TLSTX_DATA_WR_IVDSGL_V(x)    ((x) << FW_TLSTX_DATA_WR_IVDSGL_S)
#घोषणा FW_TLSTX_DATA_WR_IVDSGL_G(x)    \
	(((x) >> FW_TLSTX_DATA_WR_IVDSGL_S) & FW_TLSTX_DATA_WR_IVDSGL_M)
#घोषणा FW_TLSTX_DATA_WR_IVDSGL_F       FW_TLSTX_DATA_WR_IVDSGL_V(1U)

#घोषणा FW_TLSTX_DATA_WR_KEYSIZE_S      24
#घोषणा FW_TLSTX_DATA_WR_KEYSIZE_M      0x1f
#घोषणा FW_TLSTX_DATA_WR_KEYSIZE_V(x)   ((x) << FW_TLSTX_DATA_WR_KEYSIZE_S)
#घोषणा FW_TLSTX_DATA_WR_KEYSIZE_G(x)   \
	(((x) >> FW_TLSTX_DATA_WR_KEYSIZE_S) & FW_TLSTX_DATA_WR_KEYSIZE_M)

#घोषणा FW_TLSTX_DATA_WR_NUMIVS_S       14
#घोषणा FW_TLSTX_DATA_WR_NUMIVS_M       0xff
#घोषणा FW_TLSTX_DATA_WR_NUMIVS_V(x)    ((x) << FW_TLSTX_DATA_WR_NUMIVS_S)
#घोषणा FW_TLSTX_DATA_WR_NUMIVS_G(x)    \
	(((x) >> FW_TLSTX_DATA_WR_NUMIVS_S) & FW_TLSTX_DATA_WR_NUMIVS_M)

#घोषणा FW_TLSTX_DATA_WR_EXP_S          0
#घोषणा FW_TLSTX_DATA_WR_EXP_M          0x3fff
#घोषणा FW_TLSTX_DATA_WR_EXP_V(x)       ((x) << FW_TLSTX_DATA_WR_EXP_S)
#घोषणा FW_TLSTX_DATA_WR_EXP_G(x)       \
	(((x) >> FW_TLSTX_DATA_WR_EXP_S) & FW_TLSTX_DATA_WR_EXP_M)

#घोषणा FW_TLSTX_DATA_WR_ADJUSTEDPLEN_S 1
#घोषणा FW_TLSTX_DATA_WR_ADJUSTEDPLEN_V(x) \
	((x) << FW_TLSTX_DATA_WR_ADJUSTEDPLEN_S)

#घोषणा FW_TLSTX_DATA_WR_EXPINPLENMAX_S 4
#घोषणा FW_TLSTX_DATA_WR_EXPINPLENMAX_V(x) \
	((x) << FW_TLSTX_DATA_WR_EXPINPLENMAX_S)

#घोषणा FW_TLSTX_DATA_WR_PDUSINPLENMAX_S 2
#घोषणा FW_TLSTX_DATA_WR_PDUSINPLENMAX_V(x) \
	((x) << FW_TLSTX_DATA_WR_PDUSINPLENMAX_S)

#पूर्ण_अगर /* _T4FW_INTERFACE_H_ */
