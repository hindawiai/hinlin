<शैली गुरु>
/* SPDX-License-Identअगरier: ((GPL-2.0 WITH Linux-syscall-note) OR BSD-3-Clause) */
/*
 *
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * Copyright(c) 2015 - 2020 Intel Corporation.
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
 * Copyright(c) 2015 Intel Corporation.
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
 * This file contains defines, काष्ठाures, etc. that are used
 * to communicate between kernel and user code.
 */

#अगर_अघोषित _LINUX__HFI1_USER_H
#घोषणा _LINUX__HFI1_USER_H

#समावेश <linux/types.h>
#समावेश <rdma/rdma_user_ioctl.h>

/*
 * This version number is given to the driver by the user code during
 * initialization in the spu_userversion field of hfi1_user_info, so
 * the driver can check क्रम compatibility with user code.
 *
 * The major version changes when data काष्ठाures change in an incompatible
 * way. The driver must be the same क्रम initialization to succeed.
 */
#घोषणा HFI1_USER_SWMAJOR 6

/*
 * Minor version dअगरferences are always compatible
 * a within a major version, however अगर user software is larger
 * than driver software, some new features and/or काष्ठाure fields
 * may not be implemented; the user code must deal with this अगर it
 * cares, or it must पात after initialization reports the dअगरference.
 */
#घोषणा HFI1_USER_SWMINOR 3

/*
 * We will encode the major/minor inside a single 32bit version number.
 */
#घोषणा HFI1_SWMAJOR_SHIFT 16

/*
 * Set of HW and driver capability/feature bits.
 * These bit values are used to configure enabled/disabled HW and
 * driver features. The same set of bits are communicated to user
 * space.
 */
#घोषणा HFI1_CAP_DMA_RTAIL        (1UL <<  0) /* Use DMA'ed RTail value */
#घोषणा HFI1_CAP_SDMA             (1UL <<  1) /* Enable SDMA support */
#घोषणा HFI1_CAP_SDMA_AHG         (1UL <<  2) /* Enable SDMA AHG support */
#घोषणा HFI1_CAP_EXTENDED_PSN     (1UL <<  3) /* Enable Extended PSN support */
#घोषणा HFI1_CAP_HDRSUPP          (1UL <<  4) /* Enable Header Suppression */
#घोषणा HFI1_CAP_TID_RDMA         (1UL <<  5) /* Enable TID RDMA operations */
#घोषणा HFI1_CAP_USE_SDMA_HEAD    (1UL <<  6) /* DMA Hdr Q tail vs. use CSR */
#घोषणा HFI1_CAP_MULTI_PKT_EGR    (1UL <<  7) /* Enable multi-packet Egr buffs*/
#घोषणा HFI1_CAP_NODROP_RHQ_FULL  (1UL <<  8) /* Don't drop on Hdr Q full */
#घोषणा HFI1_CAP_NODROP_EGR_FULL  (1UL <<  9) /* Don't drop on EGR buffs full */
#घोषणा HFI1_CAP_TID_UNMAP        (1UL << 10) /* Disable Expected TID caching */
#घोषणा HFI1_CAP_PRINT_UNIMPL     (1UL << 11) /* Show क्रम unimplemented feats */
#घोषणा HFI1_CAP_ALLOW_PERM_JKEY  (1UL << 12) /* Allow use of permissive JKEY */
#घोषणा HFI1_CAP_NO_INTEGRITY     (1UL << 13) /* Enable ctxt पूर्णांकegrity checks */
#घोषणा HFI1_CAP_PKEY_CHECK       (1UL << 14) /* Enable ctxt PKey checking */
#घोषणा HFI1_CAP_STATIC_RATE_CTRL (1UL << 15) /* Allow PBC.StaticRateControl */
#घोषणा HFI1_CAP_OPFN             (1UL << 16) /* Enable the OPFN protocol */
#घोषणा HFI1_CAP_SDMA_HEAD_CHECK  (1UL << 17) /* SDMA head checking */
#घोषणा HFI1_CAP_EARLY_CREDIT_RETURN (1UL << 18) /* early credit वापस */
#घोषणा HFI1_CAP_AIP              (1UL << 19) /* Enable accelerated IP */

#घोषणा HFI1_RCVHDR_ENTSIZE_2    (1UL << 0)
#घोषणा HFI1_RCVHDR_ENTSIZE_16   (1UL << 1)
#घोषणा HFI1_RCVDHR_ENTSIZE_32   (1UL << 2)

#घोषणा _HFI1_EVENT_FROZEN_BIT         0
#घोषणा _HFI1_EVENT_LINKDOWN_BIT       1
#घोषणा _HFI1_EVENT_LID_CHANGE_BIT     2
#घोषणा _HFI1_EVENT_LMC_CHANGE_BIT     3
#घोषणा _HFI1_EVENT_SL2VL_CHANGE_BIT   4
#घोषणा _HFI1_EVENT_TID_MMU_NOTIFY_BIT 5
#घोषणा _HFI1_MAX_EVENT_BIT _HFI1_EVENT_TID_MMU_NOTIFY_BIT

#घोषणा HFI1_EVENT_FROZEN            (1UL << _HFI1_EVENT_FROZEN_BIT)
#घोषणा HFI1_EVENT_LINKDOWN          (1UL << _HFI1_EVENT_LINKDOWN_BIT)
#घोषणा HFI1_EVENT_LID_CHANGE        (1UL << _HFI1_EVENT_LID_CHANGE_BIT)
#घोषणा HFI1_EVENT_LMC_CHANGE        (1UL << _HFI1_EVENT_LMC_CHANGE_BIT)
#घोषणा HFI1_EVENT_SL2VL_CHANGE      (1UL << _HFI1_EVENT_SL2VL_CHANGE_BIT)
#घोषणा HFI1_EVENT_TID_MMU_NOTIFY    (1UL << _HFI1_EVENT_TID_MMU_NOTIFY_BIT)

/*
 * These are the status bits पढ़ोable (in ASCII क्रमm, 64bit value)
 * from the "status" sysfs file.  For binary compatibility, values
 * must reमुख्य as is; हटाओd states can be reused क्रम dअगरferent
 * purposes.
 */
#घोषणा HFI1_STATUS_INITTED       0x1    /* basic initialization करोne */
/* Chip has been found and initialized */
#घोषणा HFI1_STATUS_CHIP_PRESENT 0x20
/* IB link is at ACTIVE, usable क्रम data traffic */
#घोषणा HFI1_STATUS_IB_READY     0x40
/* link is configured, LID, MTU, etc. have been set */
#घोषणा HFI1_STATUS_IB_CONF      0x80
/* A Fatal hardware error has occurred. */
#घोषणा HFI1_STATUS_HWERROR     0x200

/*
 * Number of supported shared contexts.
 * This is the maximum number of software contexts that can share
 * a hardware send/receive context.
 */
#घोषणा HFI1_MAX_SHARED_CTXTS 8

/*
 * Poll types
 */
#घोषणा HFI1_POLL_TYPE_ANYRCV     0x0
#घोषणा HFI1_POLL_TYPE_URGENT     0x1

क्रमागत hfi1_sdma_comp_state अणु
	FREE = 0,
	QUEUED,
	COMPLETE,
	ERROR
पूर्ण;

/*
 * SDMA completion ring entry
 */
काष्ठा hfi1_sdma_comp_entry अणु
	__u32 status;
	__u32 errcode;
पूर्ण;

/*
 * Device status and notअगरications from driver to user-space.
 */
काष्ठा hfi1_status अणु
	__aligned_u64 dev;      /* device/hw status bits */
	__aligned_u64 port;     /* port state and status bits */
	अक्षर मुक्तzemsg[0];
पूर्ण;

क्रमागत sdma_req_opcode अणु
	EXPECTED = 0,
	EAGER
पूर्ण;

#घोषणा HFI1_SDMA_REQ_VERSION_MASK 0xF
#घोषणा HFI1_SDMA_REQ_VERSION_SHIFT 0x0
#घोषणा HFI1_SDMA_REQ_OPCODE_MASK 0xF
#घोषणा HFI1_SDMA_REQ_OPCODE_SHIFT 0x4
#घोषणा HFI1_SDMA_REQ_IOVCNT_MASK 0xFF
#घोषणा HFI1_SDMA_REQ_IOVCNT_SHIFT 0x8

काष्ठा sdma_req_info अणु
	/*
	 * bits 0-3 - version (currently unused)
	 * bits 4-7 - opcode (क्रमागत sdma_req_opcode)
	 * bits 8-15 - io vector count
	 */
	__u16 ctrl;
	/*
	 * Number of fragments contained in this request.
	 * User-space has alपढ़ोy computed how many
	 * fragment-sized packet the user buffer will be
	 * split पूर्णांकo.
	 */
	__u16 npkts;
	/*
	 * Size of each fragment the user buffer will be
	 * split पूर्णांकo.
	 */
	__u16 fragsize;
	/*
	 * Index of the slot in the SDMA completion ring
	 * this request should be using. User-space is
	 * in अक्षरge of managing its own ring.
	 */
	__u16 comp_idx;
पूर्ण __attribute__((__packed__));

/*
 * SW KDETH header.
 * swdata is SW defined portion.
 */
काष्ठा hfi1_kdeth_header अणु
	__le32 ver_tid_offset;
	__le16 jkey;
	__le16 hcrc;
	__le32 swdata[7];
पूर्ण  __attribute__((__packed__));

/*
 * Structure describing the headers that User space uses. The
 * काष्ठाure above is a subset of this one.
 */
काष्ठा hfi1_pkt_header अणु
	__le16 pbc[4];
	__be16 lrh[4];
	__be32 bth[3];
	काष्ठा hfi1_kdeth_header kdeth;
पूर्ण  __attribute__((__packed__));


/*
 * The list of usermode accessible रेजिस्टरs.
 */
क्रमागत hfi1_ureg अणु
	/* (RO)  DMA RcvHdr to be used next. */
	ur_rcvhdrtail = 0,
	/* (RW)  RcvHdr entry to be processed next by host. */
	ur_rcvhdrhead = 1,
	/* (RO)  Index of next Eager index to use. */
	ur_rcvegrindextail = 2,
	/* (RW)  Eager TID to be processed next */
	ur_rcvegrindexhead = 3,
	/* (RO)  Receive Eager Offset Tail */
	ur_rcvegroffsettail = 4,
	/* For पूर्णांकernal use only; max रेजिस्टर number. */
	ur_maxreg,
	/* (RW)  Receive TID flow table */
	ur_rcvtidflowtable = 256
पूर्ण;

#पूर्ण_अगर /* _LINIUX__HFI1_USER_H */
