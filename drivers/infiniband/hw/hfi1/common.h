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

#अगर_अघोषित _COMMON_H
#घोषणा _COMMON_H

#समावेश <rdma/hfi/hfi1_user.h>

/*
 * This file contains defines, काष्ठाures, etc. that are used
 * to communicate between kernel and user code.
 */

/* version of protocol header (known to chip also). In the दीर्घ run,
 * we should be able to generate and accept a range of version numbers;
 * क्रम now we only accept one, and it's compiled in.
 */
#घोषणा IPS_PROTO_VERSION 2

/*
 * These are compile समय स्थिरants that you may want to enable or disable
 * अगर you are trying to debug problems with code or perक्रमmance.
 * HFI1_VERBOSE_TRACING define as 1 अगर you want additional tracing in
 * fast path code
 * HFI1_TRACE_REGWRITES define as 1 अगर you want रेजिस्टर ग_लिखोs to be
 * traced in fast path code
 * _HFI1_TRACING define as 0 अगर you want to हटाओ all tracing in a
 * compilation unit
 */

/* driver/hw feature set biपंचांगask */
#घोषणा HFI1_CAP_USER_SHIFT      24
#घोषणा HFI1_CAP_MASK            ((1UL << HFI1_CAP_USER_SHIFT) - 1)
/* locked flag - अगर set, only HFI1_CAP_WRITABLE_MASK bits can be set */
#घोषणा HFI1_CAP_LOCKED_SHIFT    63
#घोषणा HFI1_CAP_LOCKED_MASK     0x1ULL
#घोषणा HFI1_CAP_LOCKED_SMASK    (HFI1_CAP_LOCKED_MASK << HFI1_CAP_LOCKED_SHIFT)
/* extra bits used between kernel and user processes */
#घोषणा HFI1_CAP_MISC_SHIFT      (HFI1_CAP_USER_SHIFT * 2)
#घोषणा HFI1_CAP_MISC_MASK       ((1ULL << (HFI1_CAP_LOCKED_SHIFT - \
					   HFI1_CAP_MISC_SHIFT)) - 1)

#घोषणा HFI1_CAP_KSET(cap) (अणु hfi1_cap_mask |= HFI1_CAP_##cap; hfi1_cap_mask; पूर्ण)
#घोषणा HFI1_CAP_KCLEAR(cap)						\
	(अणु								\
		hfi1_cap_mask &= ~HFI1_CAP_##cap;			\
		hfi1_cap_mask;						\
	पूर्ण)
#घोषणा HFI1_CAP_USET(cap)						\
	(अणु								\
		hfi1_cap_mask |= (HFI1_CAP_##cap << HFI1_CAP_USER_SHIFT); \
		hfi1_cap_mask;						\
		पूर्ण)
#घोषणा HFI1_CAP_UCLEAR(cap)						\
	(अणु								\
		hfi1_cap_mask &= ~(HFI1_CAP_##cap << HFI1_CAP_USER_SHIFT); \
		hfi1_cap_mask;						\
	पूर्ण)
#घोषणा HFI1_CAP_SET(cap)						\
	(अणु								\
		hfi1_cap_mask |= (HFI1_CAP_##cap | (HFI1_CAP_##cap <<	\
						  HFI1_CAP_USER_SHIFT)); \
		hfi1_cap_mask;						\
	पूर्ण)
#घोषणा HFI1_CAP_CLEAR(cap)						\
	(अणु								\
		hfi1_cap_mask &= ~(HFI1_CAP_##cap |			\
				  (HFI1_CAP_##cap << HFI1_CAP_USER_SHIFT)); \
		hfi1_cap_mask;						\
	पूर्ण)
#घोषणा HFI1_CAP_LOCK()							\
	(अणु hfi1_cap_mask |= HFI1_CAP_LOCKED_SMASK; hfi1_cap_mask; पूर्ण)
#घोषणा HFI1_CAP_LOCKED() (!!(hfi1_cap_mask & HFI1_CAP_LOCKED_SMASK))
/*
 * The set of capability bits that can be changed after initial load
 * This set is the same क्रम kernel and user contexts. However, क्रम
 * user contexts, the set can be further filtered by using the
 * HFI1_CAP_RESERVED_MASK bits.
 */
#घोषणा HFI1_CAP_WRITABLE_MASK   (HFI1_CAP_SDMA_AHG |			\
				  HFI1_CAP_HDRSUPP |			\
				  HFI1_CAP_MULTI_PKT_EGR |		\
				  HFI1_CAP_NODROP_RHQ_FULL |		\
				  HFI1_CAP_NODROP_EGR_FULL |		\
				  HFI1_CAP_ALLOW_PERM_JKEY |		\
				  HFI1_CAP_STATIC_RATE_CTRL |		\
				  HFI1_CAP_PRINT_UNIMPL |		\
				  HFI1_CAP_TID_UNMAP |			\
				  HFI1_CAP_OPFN)
/*
 * A set of capability bits that are "global" and are not allowed to be
 * set in the user biपंचांगask.
 */
#घोषणा HFI1_CAP_RESERVED_MASK   ((HFI1_CAP_SDMA |			\
				   HFI1_CAP_USE_SDMA_HEAD |		\
				   HFI1_CAP_EXTENDED_PSN |		\
				   HFI1_CAP_PRINT_UNIMPL |		\
				   HFI1_CAP_NO_INTEGRITY |		\
				   HFI1_CAP_PKEY_CHECK |		\
				   HFI1_CAP_TID_RDMA |			\
				   HFI1_CAP_OPFN |			\
				   HFI1_CAP_AIP) <<			\
				  HFI1_CAP_USER_SHIFT)
/*
 * Set of capabilities that need to be enabled क्रम kernel context in
 * order to be allowed क्रम user contexts, as well.
 */
#घोषणा HFI1_CAP_MUST_HAVE_KERN (HFI1_CAP_STATIC_RATE_CTRL)
/* Default enabled capabilities (both kernel and user) */
#घोषणा HFI1_CAP_MASK_DEFAULT    (HFI1_CAP_HDRSUPP |			\
				 HFI1_CAP_NODROP_RHQ_FULL |		\
				 HFI1_CAP_NODROP_EGR_FULL |		\
				 HFI1_CAP_SDMA |			\
				 HFI1_CAP_PRINT_UNIMPL |		\
				 HFI1_CAP_STATIC_RATE_CTRL |		\
				 HFI1_CAP_PKEY_CHECK |			\
				 HFI1_CAP_MULTI_PKT_EGR |		\
				 HFI1_CAP_EXTENDED_PSN |		\
				 HFI1_CAP_AIP |				\
				 ((HFI1_CAP_HDRSUPP |			\
				   HFI1_CAP_MULTI_PKT_EGR |		\
				   HFI1_CAP_STATIC_RATE_CTRL |		\
				   HFI1_CAP_PKEY_CHECK |		\
				   HFI1_CAP_EARLY_CREDIT_RETURN) <<	\
				  HFI1_CAP_USER_SHIFT))
/*
 * A biपंचांगask of kernel/global capabilities that should be communicated
 * to user level processes.
 */
#घोषणा HFI1_CAP_K2U (HFI1_CAP_SDMA |			\
		     HFI1_CAP_EXTENDED_PSN |		\
		     HFI1_CAP_PKEY_CHECK |		\
		     HFI1_CAP_NO_INTEGRITY)

#घोषणा HFI1_USER_SWVERSION ((HFI1_USER_SWMAJOR << HFI1_SWMAJOR_SHIFT) | \
			     HFI1_USER_SWMINOR)

#अगर_अघोषित HFI1_KERN_TYPE
#घोषणा HFI1_KERN_TYPE 0
#पूर्ण_अगर

/*
 * Similarly, this is the kernel version going back to the user.  It's
 * slightly dअगरferent, in that we want to tell अगर the driver was built as
 * part of a Intel release, or from the driver from खोलोfabrics.org,
 * kernel.org, or a standard distribution, क्रम support reasons.
 * The high bit is 0 क्रम non-Intel and 1 क्रम Intel-built/supplied.
 *
 * It's वापसed by the driver to the user code during initialization in the
 * spi_sw_version field of hfi1_base_info, so the user code can in turn
 * check क्रम compatibility with the kernel.
*/
#घोषणा HFI1_KERN_SWVERSION ((HFI1_KERN_TYPE << 31) | HFI1_USER_SWVERSION)

/*
 * Define the driver version number.  This is something that refers only
 * to the driver itself, not the software पूर्णांकerfaces it supports.
 */
#अगर_अघोषित HFI1_DRIVER_VERSION_BASE
#घोषणा HFI1_DRIVER_VERSION_BASE "0.9-294"
#पूर्ण_अगर

/* create the final driver version string */
#अगर_घोषित HFI1_IDSTR
#घोषणा HFI1_DRIVER_VERSION HFI1_DRIVER_VERSION_BASE " " HFI1_IDSTR
#अन्यथा
#घोषणा HFI1_DRIVER_VERSION HFI1_DRIVER_VERSION_BASE
#पूर्ण_अगर

/*
 * Diagnostics can send a packet by writing the following
 * काष्ठा to the diag packet special file.
 *
 * This allows a custom PBC qword, so that special modes and deliberate
 * changes to CRCs can be used.
 */
#घोषणा _DIAG_PKT_VERS 1
काष्ठा diag_pkt अणु
	__u16 version;		/* काष्ठाure version */
	__u16 unit;		/* which device */
	__u16 sw_index;		/* send sw index to use */
	__u16 len;		/* data length, in bytes */
	__u16 port;		/* port number */
	__u16 unused;
	__u32 flags;		/* call flags */
	__u64 data;		/* user data poपूर्णांकer */
	__u64 pbc;		/* PBC क्रम the packet */
पूर्ण;

/* diag_pkt flags */
#घोषणा F_DIAGPKT_WAIT 0x1	/* रुको until packet is sent */

/*
 * The next set of defines are क्रम packet headers, and chip रेजिस्टर
 * and memory bits that are visible to and/or used by user-mode software.
 */

/*
 * Receive Header Flags
 */
#घोषणा RHF_PKT_LEN_SHIFT	0
#घोषणा RHF_PKT_LEN_MASK	0xfffull
#घोषणा RHF_PKT_LEN_SMASK (RHF_PKT_LEN_MASK << RHF_PKT_LEN_SHIFT)

#घोषणा RHF_RCV_TYPE_SHIFT	12
#घोषणा RHF_RCV_TYPE_MASK	0x7ull
#घोषणा RHF_RCV_TYPE_SMASK (RHF_RCV_TYPE_MASK << RHF_RCV_TYPE_SHIFT)

#घोषणा RHF_USE_EGR_BFR_SHIFT	15
#घोषणा RHF_USE_EGR_BFR_MASK	0x1ull
#घोषणा RHF_USE_EGR_BFR_SMASK (RHF_USE_EGR_BFR_MASK << RHF_USE_EGR_BFR_SHIFT)

#घोषणा RHF_EGR_INDEX_SHIFT	16
#घोषणा RHF_EGR_INDEX_MASK	0x7ffull
#घोषणा RHF_EGR_INDEX_SMASK (RHF_EGR_INDEX_MASK << RHF_EGR_INDEX_SHIFT)

#घोषणा RHF_DC_INFO_SHIFT	27
#घोषणा RHF_DC_INFO_MASK	0x1ull
#घोषणा RHF_DC_INFO_SMASK (RHF_DC_INFO_MASK << RHF_DC_INFO_SHIFT)

#घोषणा RHF_RCV_SEQ_SHIFT	28
#घोषणा RHF_RCV_SEQ_MASK	0xfull
#घोषणा RHF_RCV_SEQ_SMASK (RHF_RCV_SEQ_MASK << RHF_RCV_SEQ_SHIFT)

#घोषणा RHF_EGR_OFFSET_SHIFT	32
#घोषणा RHF_EGR_OFFSET_MASK	0xfffull
#घोषणा RHF_EGR_OFFSET_SMASK (RHF_EGR_OFFSET_MASK << RHF_EGR_OFFSET_SHIFT)
#घोषणा RHF_HDRQ_OFFSET_SHIFT	44
#घोषणा RHF_HDRQ_OFFSET_MASK	0x1ffull
#घोषणा RHF_HDRQ_OFFSET_SMASK (RHF_HDRQ_OFFSET_MASK << RHF_HDRQ_OFFSET_SHIFT)
#घोषणा RHF_K_HDR_LEN_ERR	(0x1ull << 53)
#घोषणा RHF_DC_UNC_ERR		(0x1ull << 54)
#घोषणा RHF_DC_ERR		(0x1ull << 55)
#घोषणा RHF_RCV_TYPE_ERR_SHIFT	56
#घोषणा RHF_RCV_TYPE_ERR_MASK	0x7ul
#घोषणा RHF_RCV_TYPE_ERR_SMASK (RHF_RCV_TYPE_ERR_MASK << RHF_RCV_TYPE_ERR_SHIFT)
#घोषणा RHF_TID_ERR		(0x1ull << 59)
#घोषणा RHF_LEN_ERR		(0x1ull << 60)
#घोषणा RHF_ECC_ERR		(0x1ull << 61)
#घोषणा RHF_RESERVED		(0x1ull << 62)
#घोषणा RHF_ICRC_ERR		(0x1ull << 63)

#घोषणा RHF_ERROR_SMASK 0xffe0000000000000ull		/* bits 63:53 */

/* RHF receive types */
#घोषणा RHF_RCV_TYPE_EXPECTED 0
#घोषणा RHF_RCV_TYPE_EAGER    1
#घोषणा RHF_RCV_TYPE_IB       2 /* normal IB, IB Raw, or IPv6 */
#घोषणा RHF_RCV_TYPE_ERROR    3
#घोषणा RHF_RCV_TYPE_BYPASS   4
#घोषणा RHF_RCV_TYPE_INVALID5 5
#घोषणा RHF_RCV_TYPE_INVALID6 6
#घोषणा RHF_RCV_TYPE_INVALID7 7

/* RHF receive type error - expected packet errors */
#घोषणा RHF_RTE_EXPECTED_FLOW_SEQ_ERR	0x2
#घोषणा RHF_RTE_EXPECTED_FLOW_GEN_ERR	0x4

/* RHF receive type error - eager packet errors */
#घोषणा RHF_RTE_EAGER_NO_ERR		0x0

/* RHF receive type error - IB packet errors */
#घोषणा RHF_RTE_IB_NO_ERR		0x0

/* RHF receive type error - error packet errors */
#घोषणा RHF_RTE_ERROR_NO_ERR		0x0
#घोषणा RHF_RTE_ERROR_OP_CODE_ERR	0x1
#घोषणा RHF_RTE_ERROR_KHDR_MIN_LEN_ERR	0x2
#घोषणा RHF_RTE_ERROR_KHDR_HCRC_ERR	0x3
#घोषणा RHF_RTE_ERROR_KHDR_KVER_ERR	0x4
#घोषणा RHF_RTE_ERROR_CONTEXT_ERR	0x5
#घोषणा RHF_RTE_ERROR_KHDR_TID_ERR	0x6

/* RHF receive type error - bypass packet errors */
#घोषणा RHF_RTE_BYPASS_NO_ERR		0x0

/* MAX RcvSEQ */
#घोषणा RHF_MAX_SEQ 13

/* IB - LRH header स्थिरants */
#घोषणा HFI1_LRH_GRH 0x0003      /* 1. word of IB LRH - next header: GRH */
#घोषणा HFI1_LRH_BTH 0x0002      /* 1. word of IB LRH - next header: BTH */

/* misc. */
#घोषणा SC15_PACKET 0xF
#घोषणा SIZE_OF_CRC 1
#घोषणा SIZE_OF_LT 1
#घोषणा MAX_16B_PADDING 12 /* CRC = 4, LT = 1, Pad = 0 to 7 bytes */

#घोषणा LIM_MGMT_P_KEY       0x7FFF
#घोषणा FULL_MGMT_P_KEY      0xFFFF

#घोषणा DEFAULT_P_KEY LIM_MGMT_P_KEY

#घोषणा HFI1_PSM_IOC_BASE_SEQ 0x0

/* Number of BTH.PSN bits used क्रम sequence number in expected rcvs */
#घोषणा HFI1_KDETH_BTH_SEQ_SHIFT 11
#घोषणा HFI1_KDETH_BTH_SEQ_MASK (BIT(HFI1_KDETH_BTH_SEQ_SHIFT) - 1)

अटल अंतरभूत __u64 rhf_to_cpu(स्थिर __le32 *rbuf)
अणु
	वापस __le64_to_cpu(*((__le64 *)rbuf));
पूर्ण

अटल अंतरभूत u64 rhf_err_flags(u64 rhf)
अणु
	वापस rhf & RHF_ERROR_SMASK;
पूर्ण

अटल अंतरभूत u32 rhf_rcv_type(u64 rhf)
अणु
	वापस (rhf >> RHF_RCV_TYPE_SHIFT) & RHF_RCV_TYPE_MASK;
पूर्ण

अटल अंतरभूत u32 rhf_rcv_type_err(u64 rhf)
अणु
	वापस (rhf >> RHF_RCV_TYPE_ERR_SHIFT) & RHF_RCV_TYPE_ERR_MASK;
पूर्ण

/* वापस size is in bytes, not DWORDs */
अटल अंतरभूत u32 rhf_pkt_len(u64 rhf)
अणु
	वापस ((rhf & RHF_PKT_LEN_SMASK) >> RHF_PKT_LEN_SHIFT) << 2;
पूर्ण

अटल अंतरभूत u32 rhf_egr_index(u64 rhf)
अणु
	वापस (rhf >> RHF_EGR_INDEX_SHIFT) & RHF_EGR_INDEX_MASK;
पूर्ण

अटल अंतरभूत u32 rhf_rcv_seq(u64 rhf)
अणु
	वापस (rhf >> RHF_RCV_SEQ_SHIFT) & RHF_RCV_SEQ_MASK;
पूर्ण

/* वापसed offset is in DWORDS */
अटल अंतरभूत u32 rhf_hdrq_offset(u64 rhf)
अणु
	वापस (rhf >> RHF_HDRQ_OFFSET_SHIFT) & RHF_HDRQ_OFFSET_MASK;
पूर्ण

अटल अंतरभूत u64 rhf_use_egr_bfr(u64 rhf)
अणु
	वापस rhf & RHF_USE_EGR_BFR_SMASK;
पूर्ण

अटल अंतरभूत u64 rhf_dc_info(u64 rhf)
अणु
	वापस rhf & RHF_DC_INFO_SMASK;
पूर्ण

अटल अंतरभूत u32 rhf_egr_buf_offset(u64 rhf)
अणु
	वापस (rhf >> RHF_EGR_OFFSET_SHIFT) & RHF_EGR_OFFSET_MASK;
पूर्ण
#पूर्ण_अगर /* _COMMON_H */
