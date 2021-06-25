<शैली गुरु>
/*
 * Copyright (c) 2009-2010 Chelsio, Inc. All rights reserved.
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
#अगर_अघोषित _T4FW_RI_API_H_
#घोषणा _T4FW_RI_API_H_

#समावेश "t4fw_api.h"

क्रमागत fw_ri_wr_opcode अणु
	FW_RI_RDMA_WRITE		= 0x0,	/* IETF RDMAP v1.0 ... */
	FW_RI_READ_REQ			= 0x1,
	FW_RI_READ_RESP			= 0x2,
	FW_RI_SEND			= 0x3,
	FW_RI_SEND_WITH_INV		= 0x4,
	FW_RI_SEND_WITH_SE		= 0x5,
	FW_RI_SEND_WITH_SE_INV		= 0x6,
	FW_RI_TERMINATE			= 0x7,
	FW_RI_RDMA_INIT			= 0x8,	/* CHELSIO RI specअगरic ... */
	FW_RI_BIND_MW			= 0x9,
	FW_RI_FAST_REGISTER		= 0xa,
	FW_RI_LOCAL_INV			= 0xb,
	FW_RI_QP_MODIFY			= 0xc,
	FW_RI_BYPASS			= 0xd,
	FW_RI_RECEIVE			= 0xe,

	FW_RI_SGE_EC_CR_RETURN		= 0xf,
	FW_RI_WRITE_IMMEDIATE           = FW_RI_RDMA_INIT
पूर्ण;

क्रमागत fw_ri_wr_flags अणु
	FW_RI_COMPLETION_FLAG		= 0x01,
	FW_RI_NOTIFICATION_FLAG		= 0x02,
	FW_RI_SOLICITED_EVENT_FLAG	= 0x04,
	FW_RI_READ_FENCE_FLAG		= 0x08,
	FW_RI_LOCAL_FENCE_FLAG		= 0x10,
	FW_RI_RDMA_READ_INVALIDATE	= 0x20,
	FW_RI_RDMA_WRITE_WITH_IMMEDIATE = 0x40
पूर्ण;

क्रमागत fw_ri_mpa_attrs अणु
	FW_RI_MPA_RX_MARKER_ENABLE	= 0x01,
	FW_RI_MPA_TX_MARKER_ENABLE	= 0x02,
	FW_RI_MPA_CRC_ENABLE		= 0x04,
	FW_RI_MPA_IETF_ENABLE		= 0x08
पूर्ण;

क्रमागत fw_ri_qp_caps अणु
	FW_RI_QP_RDMA_READ_ENABLE	= 0x01,
	FW_RI_QP_RDMA_WRITE_ENABLE	= 0x02,
	FW_RI_QP_BIND_ENABLE		= 0x04,
	FW_RI_QP_FAST_REGISTER_ENABLE	= 0x08,
	FW_RI_QP_STAG0_ENABLE		= 0x10
पूर्ण;

क्रमागत fw_ri_addr_type अणु
	FW_RI_ZERO_BASED_TO		= 0x00,
	FW_RI_VA_BASED_TO		= 0x01
पूर्ण;

क्रमागत fw_ri_mem_perms अणु
	FW_RI_MEM_ACCESS_REM_WRITE	= 0x01,
	FW_RI_MEM_ACCESS_REM_READ	= 0x02,
	FW_RI_MEM_ACCESS_REM		= 0x03,
	FW_RI_MEM_ACCESS_LOCAL_WRITE	= 0x04,
	FW_RI_MEM_ACCESS_LOCAL_READ	= 0x08,
	FW_RI_MEM_ACCESS_LOCAL		= 0x0C
पूर्ण;

क्रमागत fw_ri_stag_type अणु
	FW_RI_STAG_NSMR			= 0x00,
	FW_RI_STAG_SMR			= 0x01,
	FW_RI_STAG_MW			= 0x02,
	FW_RI_STAG_MW_RELAXED		= 0x03
पूर्ण;

क्रमागत fw_ri_data_op अणु
	FW_RI_DATA_IMMD			= 0x81,
	FW_RI_DATA_DSGL			= 0x82,
	FW_RI_DATA_ISGL			= 0x83
पूर्ण;

क्रमागत fw_ri_sgl_depth अणु
	FW_RI_SGL_DEPTH_MAX_SQ		= 16,
	FW_RI_SGL_DEPTH_MAX_RQ		= 4
पूर्ण;

काष्ठा fw_ri_dsge_pair अणु
	__be32	len[2];
	__be64	addr[2];
पूर्ण;

काष्ठा fw_ri_dsgl अणु
	__u8	op;
	__u8	r1;
	__be16	nsge;
	__be32	len0;
	__be64	addr0;
#अगर_अघोषित C99_NOT_SUPPORTED
	काष्ठा fw_ri_dsge_pair sge[];
#पूर्ण_अगर
पूर्ण;

काष्ठा fw_ri_sge अणु
	__be32 stag;
	__be32 len;
	__be64 to;
पूर्ण;

काष्ठा fw_ri_isgl अणु
	__u8	op;
	__u8	r1;
	__be16	nsge;
	__be32	r2;
#अगर_अघोषित C99_NOT_SUPPORTED
	काष्ठा fw_ri_sge sge[];
#पूर्ण_अगर
पूर्ण;

काष्ठा fw_ri_immd अणु
	__u8	op;
	__u8	r1;
	__be16	r2;
	__be32	immdlen;
#अगर_अघोषित C99_NOT_SUPPORTED
	__u8	data[];
#पूर्ण_अगर
पूर्ण;

काष्ठा fw_ri_tpte अणु
	__be32 valid_to_pdid;
	__be32 locपढ़ो_to_qpid;
	__be32 nosnoop_pbladdr;
	__be32 len_lo;
	__be32 va_hi;
	__be32 va_lo_fbo;
	__be32 dca_mwbcnt_pstag;
	__be32 len_hi;
पूर्ण;

#घोषणा FW_RI_TPTE_VALID_S		31
#घोषणा FW_RI_TPTE_VALID_M		0x1
#घोषणा FW_RI_TPTE_VALID_V(x)		((x) << FW_RI_TPTE_VALID_S)
#घोषणा FW_RI_TPTE_VALID_G(x)		\
	(((x) >> FW_RI_TPTE_VALID_S) & FW_RI_TPTE_VALID_M)
#घोषणा FW_RI_TPTE_VALID_F		FW_RI_TPTE_VALID_V(1U)

#घोषणा FW_RI_TPTE_STAGKEY_S		23
#घोषणा FW_RI_TPTE_STAGKEY_M		0xff
#घोषणा FW_RI_TPTE_STAGKEY_V(x)		((x) << FW_RI_TPTE_STAGKEY_S)
#घोषणा FW_RI_TPTE_STAGKEY_G(x)		\
	(((x) >> FW_RI_TPTE_STAGKEY_S) & FW_RI_TPTE_STAGKEY_M)

#घोषणा FW_RI_TPTE_STAGSTATE_S		22
#घोषणा FW_RI_TPTE_STAGSTATE_M		0x1
#घोषणा FW_RI_TPTE_STAGSTATE_V(x)	((x) << FW_RI_TPTE_STAGSTATE_S)
#घोषणा FW_RI_TPTE_STAGSTATE_G(x)	\
	(((x) >> FW_RI_TPTE_STAGSTATE_S) & FW_RI_TPTE_STAGSTATE_M)
#घोषणा FW_RI_TPTE_STAGSTATE_F		FW_RI_TPTE_STAGSTATE_V(1U)

#घोषणा FW_RI_TPTE_STAGTYPE_S		20
#घोषणा FW_RI_TPTE_STAGTYPE_M		0x3
#घोषणा FW_RI_TPTE_STAGTYPE_V(x)	((x) << FW_RI_TPTE_STAGTYPE_S)
#घोषणा FW_RI_TPTE_STAGTYPE_G(x)	\
	(((x) >> FW_RI_TPTE_STAGTYPE_S) & FW_RI_TPTE_STAGTYPE_M)

#घोषणा FW_RI_TPTE_PDID_S		0
#घोषणा FW_RI_TPTE_PDID_M		0xfffff
#घोषणा FW_RI_TPTE_PDID_V(x)		((x) << FW_RI_TPTE_PDID_S)
#घोषणा FW_RI_TPTE_PDID_G(x)		\
	(((x) >> FW_RI_TPTE_PDID_S) & FW_RI_TPTE_PDID_M)

#घोषणा FW_RI_TPTE_PERM_S		28
#घोषणा FW_RI_TPTE_PERM_M		0xf
#घोषणा FW_RI_TPTE_PERM_V(x)		((x) << FW_RI_TPTE_PERM_S)
#घोषणा FW_RI_TPTE_PERM_G(x)		\
	(((x) >> FW_RI_TPTE_PERM_S) & FW_RI_TPTE_PERM_M)

#घोषणा FW_RI_TPTE_REMINVDIS_S		27
#घोषणा FW_RI_TPTE_REMINVDIS_M		0x1
#घोषणा FW_RI_TPTE_REMINVDIS_V(x)	((x) << FW_RI_TPTE_REMINVDIS_S)
#घोषणा FW_RI_TPTE_REMINVDIS_G(x)	\
	(((x) >> FW_RI_TPTE_REMINVDIS_S) & FW_RI_TPTE_REMINVDIS_M)
#घोषणा FW_RI_TPTE_REMINVDIS_F		FW_RI_TPTE_REMINVDIS_V(1U)

#घोषणा FW_RI_TPTE_ADDRTYPE_S		26
#घोषणा FW_RI_TPTE_ADDRTYPE_M		1
#घोषणा FW_RI_TPTE_ADDRTYPE_V(x)	((x) << FW_RI_TPTE_ADDRTYPE_S)
#घोषणा FW_RI_TPTE_ADDRTYPE_G(x)	\
	(((x) >> FW_RI_TPTE_ADDRTYPE_S) & FW_RI_TPTE_ADDRTYPE_M)
#घोषणा FW_RI_TPTE_ADDRTYPE_F		FW_RI_TPTE_ADDRTYPE_V(1U)

#घोषणा FW_RI_TPTE_MWBINDEN_S		25
#घोषणा FW_RI_TPTE_MWBINDEN_M		0x1
#घोषणा FW_RI_TPTE_MWBINDEN_V(x)	((x) << FW_RI_TPTE_MWBINDEN_S)
#घोषणा FW_RI_TPTE_MWBINDEN_G(x)	\
	(((x) >> FW_RI_TPTE_MWBINDEN_S) & FW_RI_TPTE_MWBINDEN_M)
#घोषणा FW_RI_TPTE_MWBINDEN_F		FW_RI_TPTE_MWBINDEN_V(1U)

#घोषणा FW_RI_TPTE_PS_S			20
#घोषणा FW_RI_TPTE_PS_M			0x1f
#घोषणा FW_RI_TPTE_PS_V(x)		((x) << FW_RI_TPTE_PS_S)
#घोषणा FW_RI_TPTE_PS_G(x)		\
	(((x) >> FW_RI_TPTE_PS_S) & FW_RI_TPTE_PS_M)

#घोषणा FW_RI_TPTE_QPID_S		0
#घोषणा FW_RI_TPTE_QPID_M		0xfffff
#घोषणा FW_RI_TPTE_QPID_V(x)		((x) << FW_RI_TPTE_QPID_S)
#घोषणा FW_RI_TPTE_QPID_G(x)		\
	(((x) >> FW_RI_TPTE_QPID_S) & FW_RI_TPTE_QPID_M)

#घोषणा FW_RI_TPTE_NOSNOOP_S		30
#घोषणा FW_RI_TPTE_NOSNOOP_M		0x1
#घोषणा FW_RI_TPTE_NOSNOOP_V(x)		((x) << FW_RI_TPTE_NOSNOOP_S)
#घोषणा FW_RI_TPTE_NOSNOOP_G(x)		\
	(((x) >> FW_RI_TPTE_NOSNOOP_S) & FW_RI_TPTE_NOSNOOP_M)
#घोषणा FW_RI_TPTE_NOSNOOP_F		FW_RI_TPTE_NOSNOOP_V(1U)

#घोषणा FW_RI_TPTE_PBLADDR_S		0
#घोषणा FW_RI_TPTE_PBLADDR_M		0x1fffffff
#घोषणा FW_RI_TPTE_PBLADDR_V(x)		((x) << FW_RI_TPTE_PBLADDR_S)
#घोषणा FW_RI_TPTE_PBLADDR_G(x)		\
	(((x) >> FW_RI_TPTE_PBLADDR_S) & FW_RI_TPTE_PBLADDR_M)

#घोषणा FW_RI_TPTE_DCA_S		24
#घोषणा FW_RI_TPTE_DCA_M		0x1f
#घोषणा FW_RI_TPTE_DCA_V(x)		((x) << FW_RI_TPTE_DCA_S)
#घोषणा FW_RI_TPTE_DCA_G(x)		\
	(((x) >> FW_RI_TPTE_DCA_S) & FW_RI_TPTE_DCA_M)

#घोषणा FW_RI_TPTE_MWBCNT_PSTAG_S	0
#घोषणा FW_RI_TPTE_MWBCNT_PSTAG_M	0xffffff
#घोषणा FW_RI_TPTE_MWBCNT_PSTAT_V(x)	\
	((x) << FW_RI_TPTE_MWBCNT_PSTAG_S)
#घोषणा FW_RI_TPTE_MWBCNT_PSTAG_G(x)	\
	(((x) >> FW_RI_TPTE_MWBCNT_PSTAG_S) & FW_RI_TPTE_MWBCNT_PSTAG_M)

क्रमागत fw_ri_res_type अणु
	FW_RI_RES_TYPE_SQ,
	FW_RI_RES_TYPE_RQ,
	FW_RI_RES_TYPE_CQ,
	FW_RI_RES_TYPE_SRQ,
पूर्ण;

क्रमागत fw_ri_res_op अणु
	FW_RI_RES_OP_WRITE,
	FW_RI_RES_OP_RESET,
पूर्ण;

काष्ठा fw_ri_res अणु
	जोड़ fw_ri_restype अणु
		काष्ठा fw_ri_res_sqrq अणु
			__u8   restype;
			__u8   op;
			__be16 r3;
			__be32 eqid;
			__be32 r4[2];
			__be32 fetchszm_to_iqid;
			__be32 dcaen_to_eqsize;
			__be64 eqaddr;
		पूर्ण sqrq;
		काष्ठा fw_ri_res_cq अणु
			__u8   restype;
			__u8   op;
			__be16 r3;
			__be32 iqid;
			__be32 r4[2];
			__be32 iqandst_to_iqandstindex;
			__be16 iqdroprss_to_iqesize;
			__be16 iqsize;
			__be64 iqaddr;
			__be32 iqns_iqro;
			__be32 r6_lo;
			__be64 r7;
		पूर्ण cq;
		काष्ठा fw_ri_res_srq अणु
			__u8   restype;
			__u8   op;
			__be16 r3;
			__be32 eqid;
			__be32 r4[2];
			__be32 fetchszm_to_iqid;
			__be32 dcaen_to_eqsize;
			__be64 eqaddr;
			__be32 srqid;
			__be32 pdid;
			__be32 hwsrqsize;
			__be32 hwsrqaddr;
		पूर्ण srq;
	पूर्ण u;
पूर्ण;

काष्ठा fw_ri_res_wr अणु
	__be32 op_nres;
	__be32 len16_pkd;
	__u64  cookie;
#अगर_अघोषित C99_NOT_SUPPORTED
	काष्ठा fw_ri_res res[];
#पूर्ण_अगर
पूर्ण;

#घोषणा FW_RI_RES_WR_NRES_S	0
#घोषणा FW_RI_RES_WR_NRES_M	0xff
#घोषणा FW_RI_RES_WR_NRES_V(x)	((x) << FW_RI_RES_WR_NRES_S)
#घोषणा FW_RI_RES_WR_NRES_G(x)	\
	(((x) >> FW_RI_RES_WR_NRES_S) & FW_RI_RES_WR_NRES_M)

#घोषणा FW_RI_RES_WR_FETCHSZM_S		26
#घोषणा FW_RI_RES_WR_FETCHSZM_M		0x1
#घोषणा FW_RI_RES_WR_FETCHSZM_V(x)	((x) << FW_RI_RES_WR_FETCHSZM_S)
#घोषणा FW_RI_RES_WR_FETCHSZM_G(x)	\
	(((x) >> FW_RI_RES_WR_FETCHSZM_S) & FW_RI_RES_WR_FETCHSZM_M)
#घोषणा FW_RI_RES_WR_FETCHSZM_F	FW_RI_RES_WR_FETCHSZM_V(1U)

#घोषणा FW_RI_RES_WR_STATUSPGNS_S	25
#घोषणा FW_RI_RES_WR_STATUSPGNS_M	0x1
#घोषणा FW_RI_RES_WR_STATUSPGNS_V(x)	((x) << FW_RI_RES_WR_STATUSPGNS_S)
#घोषणा FW_RI_RES_WR_STATUSPGNS_G(x)	\
	(((x) >> FW_RI_RES_WR_STATUSPGNS_S) & FW_RI_RES_WR_STATUSPGNS_M)
#घोषणा FW_RI_RES_WR_STATUSPGNS_F	FW_RI_RES_WR_STATUSPGNS_V(1U)

#घोषणा FW_RI_RES_WR_STATUSPGRO_S	24
#घोषणा FW_RI_RES_WR_STATUSPGRO_M	0x1
#घोषणा FW_RI_RES_WR_STATUSPGRO_V(x)	((x) << FW_RI_RES_WR_STATUSPGRO_S)
#घोषणा FW_RI_RES_WR_STATUSPGRO_G(x)	\
	(((x) >> FW_RI_RES_WR_STATUSPGRO_S) & FW_RI_RES_WR_STATUSPGRO_M)
#घोषणा FW_RI_RES_WR_STATUSPGRO_F	FW_RI_RES_WR_STATUSPGRO_V(1U)

#घोषणा FW_RI_RES_WR_FETCHNS_S		23
#घोषणा FW_RI_RES_WR_FETCHNS_M		0x1
#घोषणा FW_RI_RES_WR_FETCHNS_V(x)	((x) << FW_RI_RES_WR_FETCHNS_S)
#घोषणा FW_RI_RES_WR_FETCHNS_G(x)	\
	(((x) >> FW_RI_RES_WR_FETCHNS_S) & FW_RI_RES_WR_FETCHNS_M)
#घोषणा FW_RI_RES_WR_FETCHNS_F	FW_RI_RES_WR_FETCHNS_V(1U)

#घोषणा FW_RI_RES_WR_FETCHRO_S		22
#घोषणा FW_RI_RES_WR_FETCHRO_M		0x1
#घोषणा FW_RI_RES_WR_FETCHRO_V(x)	((x) << FW_RI_RES_WR_FETCHRO_S)
#घोषणा FW_RI_RES_WR_FETCHRO_G(x)	\
	(((x) >> FW_RI_RES_WR_FETCHRO_S) & FW_RI_RES_WR_FETCHRO_M)
#घोषणा FW_RI_RES_WR_FETCHRO_F	FW_RI_RES_WR_FETCHRO_V(1U)

#घोषणा FW_RI_RES_WR_HOSTFCMODE_S	20
#घोषणा FW_RI_RES_WR_HOSTFCMODE_M	0x3
#घोषणा FW_RI_RES_WR_HOSTFCMODE_V(x)	((x) << FW_RI_RES_WR_HOSTFCMODE_S)
#घोषणा FW_RI_RES_WR_HOSTFCMODE_G(x)	\
	(((x) >> FW_RI_RES_WR_HOSTFCMODE_S) & FW_RI_RES_WR_HOSTFCMODE_M)

#घोषणा FW_RI_RES_WR_CPRIO_S	19
#घोषणा FW_RI_RES_WR_CPRIO_M	0x1
#घोषणा FW_RI_RES_WR_CPRIO_V(x)	((x) << FW_RI_RES_WR_CPRIO_S)
#घोषणा FW_RI_RES_WR_CPRIO_G(x)	\
	(((x) >> FW_RI_RES_WR_CPRIO_S) & FW_RI_RES_WR_CPRIO_M)
#घोषणा FW_RI_RES_WR_CPRIO_F	FW_RI_RES_WR_CPRIO_V(1U)

#घोषणा FW_RI_RES_WR_ONCHIP_S		18
#घोषणा FW_RI_RES_WR_ONCHIP_M		0x1
#घोषणा FW_RI_RES_WR_ONCHIP_V(x)	((x) << FW_RI_RES_WR_ONCHIP_S)
#घोषणा FW_RI_RES_WR_ONCHIP_G(x)	\
	(((x) >> FW_RI_RES_WR_ONCHIP_S) & FW_RI_RES_WR_ONCHIP_M)
#घोषणा FW_RI_RES_WR_ONCHIP_F	FW_RI_RES_WR_ONCHIP_V(1U)

#घोषणा FW_RI_RES_WR_PCIECHN_S		16
#घोषणा FW_RI_RES_WR_PCIECHN_M		0x3
#घोषणा FW_RI_RES_WR_PCIECHN_V(x)	((x) << FW_RI_RES_WR_PCIECHN_S)
#घोषणा FW_RI_RES_WR_PCIECHN_G(x)	\
	(((x) >> FW_RI_RES_WR_PCIECHN_S) & FW_RI_RES_WR_PCIECHN_M)

#घोषणा FW_RI_RES_WR_IQID_S	0
#घोषणा FW_RI_RES_WR_IQID_M	0xffff
#घोषणा FW_RI_RES_WR_IQID_V(x)	((x) << FW_RI_RES_WR_IQID_S)
#घोषणा FW_RI_RES_WR_IQID_G(x)	\
	(((x) >> FW_RI_RES_WR_IQID_S) & FW_RI_RES_WR_IQID_M)

#घोषणा FW_RI_RES_WR_DCAEN_S	31
#घोषणा FW_RI_RES_WR_DCAEN_M	0x1
#घोषणा FW_RI_RES_WR_DCAEN_V(x)	((x) << FW_RI_RES_WR_DCAEN_S)
#घोषणा FW_RI_RES_WR_DCAEN_G(x)	\
	(((x) >> FW_RI_RES_WR_DCAEN_S) & FW_RI_RES_WR_DCAEN_M)
#घोषणा FW_RI_RES_WR_DCAEN_F	FW_RI_RES_WR_DCAEN_V(1U)

#घोषणा FW_RI_RES_WR_DCACPU_S		26
#घोषणा FW_RI_RES_WR_DCACPU_M		0x1f
#घोषणा FW_RI_RES_WR_DCACPU_V(x)	((x) << FW_RI_RES_WR_DCACPU_S)
#घोषणा FW_RI_RES_WR_DCACPU_G(x)	\
	(((x) >> FW_RI_RES_WR_DCACPU_S) & FW_RI_RES_WR_DCACPU_M)

#घोषणा FW_RI_RES_WR_FBMIN_S	23
#घोषणा FW_RI_RES_WR_FBMIN_M	0x7
#घोषणा FW_RI_RES_WR_FBMIN_V(x)	((x) << FW_RI_RES_WR_FBMIN_S)
#घोषणा FW_RI_RES_WR_FBMIN_G(x)	\
	(((x) >> FW_RI_RES_WR_FBMIN_S) & FW_RI_RES_WR_FBMIN_M)

#घोषणा FW_RI_RES_WR_FBMAX_S	20
#घोषणा FW_RI_RES_WR_FBMAX_M	0x7
#घोषणा FW_RI_RES_WR_FBMAX_V(x)	((x) << FW_RI_RES_WR_FBMAX_S)
#घोषणा FW_RI_RES_WR_FBMAX_G(x)	\
	(((x) >> FW_RI_RES_WR_FBMAX_S) & FW_RI_RES_WR_FBMAX_M)

#घोषणा FW_RI_RES_WR_CIDXFTHRESHO_S	19
#घोषणा FW_RI_RES_WR_CIDXFTHRESHO_M	0x1
#घोषणा FW_RI_RES_WR_CIDXFTHRESHO_V(x)	((x) << FW_RI_RES_WR_CIDXFTHRESHO_S)
#घोषणा FW_RI_RES_WR_CIDXFTHRESHO_G(x)	\
	(((x) >> FW_RI_RES_WR_CIDXFTHRESHO_S) & FW_RI_RES_WR_CIDXFTHRESHO_M)
#घोषणा FW_RI_RES_WR_CIDXFTHRESHO_F	FW_RI_RES_WR_CIDXFTHRESHO_V(1U)

#घोषणा FW_RI_RES_WR_CIDXFTHRESH_S	16
#घोषणा FW_RI_RES_WR_CIDXFTHRESH_M	0x7
#घोषणा FW_RI_RES_WR_CIDXFTHRESH_V(x)	((x) << FW_RI_RES_WR_CIDXFTHRESH_S)
#घोषणा FW_RI_RES_WR_CIDXFTHRESH_G(x)	\
	(((x) >> FW_RI_RES_WR_CIDXFTHRESH_S) & FW_RI_RES_WR_CIDXFTHRESH_M)

#घोषणा FW_RI_RES_WR_EQSIZE_S		0
#घोषणा FW_RI_RES_WR_EQSIZE_M		0xffff
#घोषणा FW_RI_RES_WR_EQSIZE_V(x)	((x) << FW_RI_RES_WR_EQSIZE_S)
#घोषणा FW_RI_RES_WR_EQSIZE_G(x)	\
	(((x) >> FW_RI_RES_WR_EQSIZE_S) & FW_RI_RES_WR_EQSIZE_M)

#घोषणा FW_RI_RES_WR_IQANDST_S		15
#घोषणा FW_RI_RES_WR_IQANDST_M		0x1
#घोषणा FW_RI_RES_WR_IQANDST_V(x)	((x) << FW_RI_RES_WR_IQANDST_S)
#घोषणा FW_RI_RES_WR_IQANDST_G(x)	\
	(((x) >> FW_RI_RES_WR_IQANDST_S) & FW_RI_RES_WR_IQANDST_M)
#घोषणा FW_RI_RES_WR_IQANDST_F	FW_RI_RES_WR_IQANDST_V(1U)

#घोषणा FW_RI_RES_WR_IQANUS_S		14
#घोषणा FW_RI_RES_WR_IQANUS_M		0x1
#घोषणा FW_RI_RES_WR_IQANUS_V(x)	((x) << FW_RI_RES_WR_IQANUS_S)
#घोषणा FW_RI_RES_WR_IQANUS_G(x)	\
	(((x) >> FW_RI_RES_WR_IQANUS_S) & FW_RI_RES_WR_IQANUS_M)
#घोषणा FW_RI_RES_WR_IQANUS_F	FW_RI_RES_WR_IQANUS_V(1U)

#घोषणा FW_RI_RES_WR_IQANUD_S		12
#घोषणा FW_RI_RES_WR_IQANUD_M		0x3
#घोषणा FW_RI_RES_WR_IQANUD_V(x)	((x) << FW_RI_RES_WR_IQANUD_S)
#घोषणा FW_RI_RES_WR_IQANUD_G(x)	\
	(((x) >> FW_RI_RES_WR_IQANUD_S) & FW_RI_RES_WR_IQANUD_M)

#घोषणा FW_RI_RES_WR_IQANDSTINDEX_S	0
#घोषणा FW_RI_RES_WR_IQANDSTINDEX_M	0xfff
#घोषणा FW_RI_RES_WR_IQANDSTINDEX_V(x)	((x) << FW_RI_RES_WR_IQANDSTINDEX_S)
#घोषणा FW_RI_RES_WR_IQANDSTINDEX_G(x)	\
	(((x) >> FW_RI_RES_WR_IQANDSTINDEX_S) & FW_RI_RES_WR_IQANDSTINDEX_M)

#घोषणा FW_RI_RES_WR_IQDROPRSS_S	15
#घोषणा FW_RI_RES_WR_IQDROPRSS_M	0x1
#घोषणा FW_RI_RES_WR_IQDROPRSS_V(x)	((x) << FW_RI_RES_WR_IQDROPRSS_S)
#घोषणा FW_RI_RES_WR_IQDROPRSS_G(x)	\
	(((x) >> FW_RI_RES_WR_IQDROPRSS_S) & FW_RI_RES_WR_IQDROPRSS_M)
#घोषणा FW_RI_RES_WR_IQDROPRSS_F	FW_RI_RES_WR_IQDROPRSS_V(1U)

#घोषणा FW_RI_RES_WR_IQGTSMODE_S	14
#घोषणा FW_RI_RES_WR_IQGTSMODE_M	0x1
#घोषणा FW_RI_RES_WR_IQGTSMODE_V(x)	((x) << FW_RI_RES_WR_IQGTSMODE_S)
#घोषणा FW_RI_RES_WR_IQGTSMODE_G(x)	\
	(((x) >> FW_RI_RES_WR_IQGTSMODE_S) & FW_RI_RES_WR_IQGTSMODE_M)
#घोषणा FW_RI_RES_WR_IQGTSMODE_F	FW_RI_RES_WR_IQGTSMODE_V(1U)

#घोषणा FW_RI_RES_WR_IQPCIECH_S		12
#घोषणा FW_RI_RES_WR_IQPCIECH_M		0x3
#घोषणा FW_RI_RES_WR_IQPCIECH_V(x)	((x) << FW_RI_RES_WR_IQPCIECH_S)
#घोषणा FW_RI_RES_WR_IQPCIECH_G(x)	\
	(((x) >> FW_RI_RES_WR_IQPCIECH_S) & FW_RI_RES_WR_IQPCIECH_M)

#घोषणा FW_RI_RES_WR_IQDCAEN_S		11
#घोषणा FW_RI_RES_WR_IQDCAEN_M		0x1
#घोषणा FW_RI_RES_WR_IQDCAEN_V(x)	((x) << FW_RI_RES_WR_IQDCAEN_S)
#घोषणा FW_RI_RES_WR_IQDCAEN_G(x)	\
	(((x) >> FW_RI_RES_WR_IQDCAEN_S) & FW_RI_RES_WR_IQDCAEN_M)
#घोषणा FW_RI_RES_WR_IQDCAEN_F	FW_RI_RES_WR_IQDCAEN_V(1U)

#घोषणा FW_RI_RES_WR_IQDCACPU_S		6
#घोषणा FW_RI_RES_WR_IQDCACPU_M		0x1f
#घोषणा FW_RI_RES_WR_IQDCACPU_V(x)	((x) << FW_RI_RES_WR_IQDCACPU_S)
#घोषणा FW_RI_RES_WR_IQDCACPU_G(x)	\
	(((x) >> FW_RI_RES_WR_IQDCACPU_S) & FW_RI_RES_WR_IQDCACPU_M)

#घोषणा FW_RI_RES_WR_IQINTCNTTHRESH_S		4
#घोषणा FW_RI_RES_WR_IQINTCNTTHRESH_M		0x3
#घोषणा FW_RI_RES_WR_IQINTCNTTHRESH_V(x)	\
	((x) << FW_RI_RES_WR_IQINTCNTTHRESH_S)
#घोषणा FW_RI_RES_WR_IQINTCNTTHRESH_G(x)	\
	(((x) >> FW_RI_RES_WR_IQINTCNTTHRESH_S) & FW_RI_RES_WR_IQINTCNTTHRESH_M)

#घोषणा FW_RI_RES_WR_IQO_S	3
#घोषणा FW_RI_RES_WR_IQO_M	0x1
#घोषणा FW_RI_RES_WR_IQO_V(x)	((x) << FW_RI_RES_WR_IQO_S)
#घोषणा FW_RI_RES_WR_IQO_G(x)	\
	(((x) >> FW_RI_RES_WR_IQO_S) & FW_RI_RES_WR_IQO_M)
#घोषणा FW_RI_RES_WR_IQO_F	FW_RI_RES_WR_IQO_V(1U)

#घोषणा FW_RI_RES_WR_IQCPRIO_S		2
#घोषणा FW_RI_RES_WR_IQCPRIO_M		0x1
#घोषणा FW_RI_RES_WR_IQCPRIO_V(x)	((x) << FW_RI_RES_WR_IQCPRIO_S)
#घोषणा FW_RI_RES_WR_IQCPRIO_G(x)	\
	(((x) >> FW_RI_RES_WR_IQCPRIO_S) & FW_RI_RES_WR_IQCPRIO_M)
#घोषणा FW_RI_RES_WR_IQCPRIO_F	FW_RI_RES_WR_IQCPRIO_V(1U)

#घोषणा FW_RI_RES_WR_IQESIZE_S		0
#घोषणा FW_RI_RES_WR_IQESIZE_M		0x3
#घोषणा FW_RI_RES_WR_IQESIZE_V(x)	((x) << FW_RI_RES_WR_IQESIZE_S)
#घोषणा FW_RI_RES_WR_IQESIZE_G(x)	\
	(((x) >> FW_RI_RES_WR_IQESIZE_S) & FW_RI_RES_WR_IQESIZE_M)

#घोषणा FW_RI_RES_WR_IQNS_S	31
#घोषणा FW_RI_RES_WR_IQNS_M	0x1
#घोषणा FW_RI_RES_WR_IQNS_V(x)	((x) << FW_RI_RES_WR_IQNS_S)
#घोषणा FW_RI_RES_WR_IQNS_G(x)	\
	(((x) >> FW_RI_RES_WR_IQNS_S) & FW_RI_RES_WR_IQNS_M)
#घोषणा FW_RI_RES_WR_IQNS_F	FW_RI_RES_WR_IQNS_V(1U)

#घोषणा FW_RI_RES_WR_IQRO_S	30
#घोषणा FW_RI_RES_WR_IQRO_M	0x1
#घोषणा FW_RI_RES_WR_IQRO_V(x)	((x) << FW_RI_RES_WR_IQRO_S)
#घोषणा FW_RI_RES_WR_IQRO_G(x)	\
	(((x) >> FW_RI_RES_WR_IQRO_S) & FW_RI_RES_WR_IQRO_M)
#घोषणा FW_RI_RES_WR_IQRO_F	FW_RI_RES_WR_IQRO_V(1U)

काष्ठा fw_ri_rdma_ग_लिखो_wr अणु
	__u8   opcode;
	__u8   flags;
	__u16  wrid;
	__u8   r1[3];
	__u8   len16;
	/*
	 * Use जोड़ क्रम immediate data to be consistent with stack's 32 bit
	 * data and iWARP spec's 64 bit data.
	 */
	जोड़ अणु
		काष्ठा अणु
			__be32 imm_data32;
			u32 reserved;
		पूर्ण ib_imm_data;
		__be64 imm_data64;
	पूर्ण iw_imm_data;
	__be32 plen;
	__be32 stag_sink;
	__be64 to_sink;
#अगर_अघोषित C99_NOT_SUPPORTED
	जोड़ अणु
		काष्ठा fw_ri_immd immd_src[0];
		काष्ठा fw_ri_isgl isgl_src[0];
	पूर्ण u;
#पूर्ण_अगर
पूर्ण;

काष्ठा fw_ri_send_wr अणु
	__u8   opcode;
	__u8   flags;
	__u16  wrid;
	__u8   r1[3];
	__u8   len16;
	__be32 senकरोp_pkd;
	__be32 stag_inv;
	__be32 plen;
	__be32 r3;
	__be64 r4;
#अगर_अघोषित C99_NOT_SUPPORTED
	जोड़ अणु
		काष्ठा fw_ri_immd immd_src[0];
		काष्ठा fw_ri_isgl isgl_src[0];
	पूर्ण u;
#पूर्ण_अगर
पूर्ण;

#घोषणा FW_RI_SEND_WR_SENDOP_S		0
#घोषणा FW_RI_SEND_WR_SENDOP_M		0xf
#घोषणा FW_RI_SEND_WR_SENDOP_V(x)	((x) << FW_RI_SEND_WR_SENDOP_S)
#घोषणा FW_RI_SEND_WR_SENDOP_G(x)	\
	(((x) >> FW_RI_SEND_WR_SENDOP_S) & FW_RI_SEND_WR_SENDOP_M)

काष्ठा fw_ri_rdma_ग_लिखो_cmpl_wr अणु
	__u8   opcode;
	__u8   flags;
	__u16  wrid;
	__u8   r1[3];
	__u8   len16;
	__u8   r2;
	__u8   flags_send;
	__u16  wrid_send;
	__be32 stag_inv;
	__be32 plen;
	__be32 stag_sink;
	__be64 to_sink;
	जोड़ fw_ri_cmpl अणु
		काष्ठा fw_ri_immd_cmpl अणु
			__u8   op;
			__u8   r1[6];
			__u8   immdlen;
			__u8   data[16];
		पूर्ण immd_src;
		काष्ठा fw_ri_isgl isgl_src;
	पूर्ण u_cmpl;
	__be64 r3;
#अगर_अघोषित C99_NOT_SUPPORTED
	जोड़ fw_ri_ग_लिखो अणु
		काष्ठा fw_ri_immd immd_src[0];
		काष्ठा fw_ri_isgl isgl_src[0];
	पूर्ण u;
#पूर्ण_अगर
पूर्ण;

काष्ठा fw_ri_rdma_पढ़ो_wr अणु
	__u8   opcode;
	__u8   flags;
	__u16  wrid;
	__u8   r1[3];
	__u8   len16;
	__be64 r2;
	__be32 stag_sink;
	__be32 to_sink_hi;
	__be32 to_sink_lo;
	__be32 plen;
	__be32 stag_src;
	__be32 to_src_hi;
	__be32 to_src_lo;
	__be32 r5;
पूर्ण;

काष्ठा fw_ri_recv_wr अणु
	__u8   opcode;
	__u8   r1;
	__u16  wrid;
	__u8   r2[3];
	__u8   len16;
	काष्ठा fw_ri_isgl isgl;
पूर्ण;

काष्ठा fw_ri_bind_mw_wr अणु
	__u8   opcode;
	__u8   flags;
	__u16  wrid;
	__u8   r1[3];
	__u8   len16;
	__u8   qpbinde_to_dcacpu;
	__u8   pgsz_shअगरt;
	__u8   addr_type;
	__u8   mem_perms;
	__be32 stag_mr;
	__be32 stag_mw;
	__be32 r3;
	__be64 len_mw;
	__be64 va_fbo;
	__be64 r4;
पूर्ण;

#घोषणा FW_RI_BIND_MW_WR_QPBINDE_S	6
#घोषणा FW_RI_BIND_MW_WR_QPBINDE_M	0x1
#घोषणा FW_RI_BIND_MW_WR_QPBINDE_V(x)	((x) << FW_RI_BIND_MW_WR_QPBINDE_S)
#घोषणा FW_RI_BIND_MW_WR_QPBINDE_G(x)	\
	(((x) >> FW_RI_BIND_MW_WR_QPBINDE_S) & FW_RI_BIND_MW_WR_QPBINDE_M)
#घोषणा FW_RI_BIND_MW_WR_QPBINDE_F	FW_RI_BIND_MW_WR_QPBINDE_V(1U)

#घोषणा FW_RI_BIND_MW_WR_NS_S		5
#घोषणा FW_RI_BIND_MW_WR_NS_M		0x1
#घोषणा FW_RI_BIND_MW_WR_NS_V(x)	((x) << FW_RI_BIND_MW_WR_NS_S)
#घोषणा FW_RI_BIND_MW_WR_NS_G(x)	\
	(((x) >> FW_RI_BIND_MW_WR_NS_S) & FW_RI_BIND_MW_WR_NS_M)
#घोषणा FW_RI_BIND_MW_WR_NS_F	FW_RI_BIND_MW_WR_NS_V(1U)

#घोषणा FW_RI_BIND_MW_WR_DCACPU_S	0
#घोषणा FW_RI_BIND_MW_WR_DCACPU_M	0x1f
#घोषणा FW_RI_BIND_MW_WR_DCACPU_V(x)	((x) << FW_RI_BIND_MW_WR_DCACPU_S)
#घोषणा FW_RI_BIND_MW_WR_DCACPU_G(x)	\
	(((x) >> FW_RI_BIND_MW_WR_DCACPU_S) & FW_RI_BIND_MW_WR_DCACPU_M)

काष्ठा fw_ri_fr_nsmr_wr अणु
	__u8   opcode;
	__u8   flags;
	__u16  wrid;
	__u8   r1[3];
	__u8   len16;
	__u8   qpbinde_to_dcacpu;
	__u8   pgsz_shअगरt;
	__u8   addr_type;
	__u8   mem_perms;
	__be32 stag;
	__be32 len_hi;
	__be32 len_lo;
	__be32 va_hi;
	__be32 va_lo_fbo;
पूर्ण;

#घोषणा FW_RI_FR_NSMR_WR_QPBINDE_S	6
#घोषणा FW_RI_FR_NSMR_WR_QPBINDE_M	0x1
#घोषणा FW_RI_FR_NSMR_WR_QPBINDE_V(x)	((x) << FW_RI_FR_NSMR_WR_QPBINDE_S)
#घोषणा FW_RI_FR_NSMR_WR_QPBINDE_G(x)	\
	(((x) >> FW_RI_FR_NSMR_WR_QPBINDE_S) & FW_RI_FR_NSMR_WR_QPBINDE_M)
#घोषणा FW_RI_FR_NSMR_WR_QPBINDE_F	FW_RI_FR_NSMR_WR_QPBINDE_V(1U)

#घोषणा FW_RI_FR_NSMR_WR_NS_S		5
#घोषणा FW_RI_FR_NSMR_WR_NS_M		0x1
#घोषणा FW_RI_FR_NSMR_WR_NS_V(x)	((x) << FW_RI_FR_NSMR_WR_NS_S)
#घोषणा FW_RI_FR_NSMR_WR_NS_G(x)	\
	(((x) >> FW_RI_FR_NSMR_WR_NS_S) & FW_RI_FR_NSMR_WR_NS_M)
#घोषणा FW_RI_FR_NSMR_WR_NS_F	FW_RI_FR_NSMR_WR_NS_V(1U)

#घोषणा FW_RI_FR_NSMR_WR_DCACPU_S	0
#घोषणा FW_RI_FR_NSMR_WR_DCACPU_M	0x1f
#घोषणा FW_RI_FR_NSMR_WR_DCACPU_V(x)	((x) << FW_RI_FR_NSMR_WR_DCACPU_S)
#घोषणा FW_RI_FR_NSMR_WR_DCACPU_G(x)	\
	(((x) >> FW_RI_FR_NSMR_WR_DCACPU_S) & FW_RI_FR_NSMR_WR_DCACPU_M)

काष्ठा fw_ri_fr_nsmr_tpte_wr अणु
	__u8	opcode;
	__u8   flags;
	__u16  wrid;
	__u8   r1[3];
	__u8   len16;
	__be32  r2;
	__be32  stag;
	काष्ठा fw_ri_tpte tpte;
	__u64  pbl[2];
पूर्ण;

काष्ठा fw_ri_inv_lstag_wr अणु
	__u8   opcode;
	__u8   flags;
	__u16  wrid;
	__u8   r1[3];
	__u8   len16;
	__be32 r2;
	__be32 stag_inv;
पूर्ण;

क्रमागत fw_ri_type अणु
	FW_RI_TYPE_INIT,
	FW_RI_TYPE_FINI,
	FW_RI_TYPE_TERMINATE
पूर्ण;

क्रमागत fw_ri_init_p2ptype अणु
	FW_RI_INIT_P2PTYPE_RDMA_WRITE		= FW_RI_RDMA_WRITE,
	FW_RI_INIT_P2PTYPE_READ_REQ		= FW_RI_READ_REQ,
	FW_RI_INIT_P2PTYPE_SEND			= FW_RI_SEND,
	FW_RI_INIT_P2PTYPE_SEND_WITH_INV	= FW_RI_SEND_WITH_INV,
	FW_RI_INIT_P2PTYPE_SEND_WITH_SE		= FW_RI_SEND_WITH_SE,
	FW_RI_INIT_P2PTYPE_SEND_WITH_SE_INV	= FW_RI_SEND_WITH_SE_INV,
	FW_RI_INIT_P2PTYPE_DISABLED		= 0xf,
पूर्ण;

क्रमागत fw_ri_init_rqeqid_srq अणु
	FW_RI_INIT_RQEQID_SRQ			= 1 << 31,
पूर्ण;

काष्ठा fw_ri_wr अणु
	__be32 op_compl;
	__be32 flowid_len16;
	__u64  cookie;
	जोड़ fw_ri अणु
		काष्ठा fw_ri_init अणु
			__u8   type;
			__u8   mpareqbit_p2ptype;
			__u8   r4[2];
			__u8   mpa_attrs;
			__u8   qp_caps;
			__be16 nrqe;
			__be32 pdid;
			__be32 qpid;
			__be32 sq_eqid;
			__be32 rq_eqid;
			__be32 scqid;
			__be32 rcqid;
			__be32 ord_max;
			__be32 ird_max;
			__be32 iss;
			__be32 irs;
			__be32 hwrqsize;
			__be32 hwrqaddr;
			__be64 r5;
			जोड़ fw_ri_init_p2p अणु
				काष्ठा fw_ri_rdma_ग_लिखो_wr ग_लिखो;
				काष्ठा fw_ri_rdma_पढ़ो_wr पढ़ो;
				काष्ठा fw_ri_send_wr send;
			पूर्ण u;
		पूर्ण init;
		काष्ठा fw_ri_fini अणु
			__u8   type;
			__u8   r3[7];
			__be64 r4;
		पूर्ण fini;
		काष्ठा fw_ri_terminate अणु
			__u8   type;
			__u8   r3[3];
			__be32 immdlen;
			__u8   termmsg[40];
		पूर्ण terminate;
	पूर्ण u;
पूर्ण;

#घोषणा FW_RI_WR_MPAREQBIT_S	7
#घोषणा FW_RI_WR_MPAREQBIT_M	0x1
#घोषणा FW_RI_WR_MPAREQBIT_V(x)	((x) << FW_RI_WR_MPAREQBIT_S)
#घोषणा FW_RI_WR_MPAREQBIT_G(x)	\
	(((x) >> FW_RI_WR_MPAREQBIT_S) & FW_RI_WR_MPAREQBIT_M)
#घोषणा FW_RI_WR_MPAREQBIT_F	FW_RI_WR_MPAREQBIT_V(1U)

#घोषणा FW_RI_WR_P2PTYPE_S	0
#घोषणा FW_RI_WR_P2PTYPE_M	0xf
#घोषणा FW_RI_WR_P2PTYPE_V(x)	((x) << FW_RI_WR_P2PTYPE_S)
#घोषणा FW_RI_WR_P2PTYPE_G(x)	\
	(((x) >> FW_RI_WR_P2PTYPE_S) & FW_RI_WR_P2PTYPE_M)

#पूर्ण_अगर /* _T4FW_RI_API_H_ */
