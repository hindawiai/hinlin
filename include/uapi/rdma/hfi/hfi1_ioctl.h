<शैली गुरु>
/* SPDX-License-Identअगरier: ((GPL-2.0 WITH Linux-syscall-note) OR BSD-3-Clause) */
/*
 *
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * Copyright(c) 2015 Intel Corporation.
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

#अगर_अघोषित _LINUX__HFI1_IOCTL_H
#घोषणा _LINUX__HFI1_IOCTL_H
#समावेश <linux/types.h>

/*
 * This काष्ठाure is passed to the driver to tell it where
 * user code buffers are, sizes, etc.   The offsets and sizes of the
 * fields must reमुख्य unchanged, क्रम binary compatibility.  It can
 * be extended, अगर userversion is changed so user code can tell, अगर needed
 */
काष्ठा hfi1_user_info अणु
	/*
	 * version of user software, to detect compatibility issues.
	 * Should be set to HFI1_USER_SWVERSION.
	 */
	__u32 userversion;
	__u32 pad;
	/*
	 * If two or more processes wish to share a context, each process
	 * must set the subcontext_cnt and subcontext_id to the same
	 * values.  The only restriction on the subcontext_id is that
	 * it be unique क्रम a given node.
	 */
	__u16 subctxt_cnt;
	__u16 subctxt_id;
	/* 128bit UUID passed in by PSM. */
	__u8 uuid[16];
पूर्ण;

काष्ठा hfi1_ctxt_info अणु
	__aligned_u64 runसमय_flags;    /* chip/drv runसमय flags (HFI1_CAP_*) */
	__u32 rcvegr_size;      /* size of each eager buffer */
	__u16 num_active;       /* number of active units */
	__u16 unit;             /* unit (chip) asचिन्हित to caller */
	__u16 ctxt;             /* ctxt on unit asचिन्हित to caller */
	__u16 subctxt;          /* subctxt on unit asचिन्हित to caller */
	__u16 rcvtids;          /* number of Rcv TIDs क्रम this context */
	__u16 credits;          /* number of PIO credits क्रम this context */
	__u16 numa_node;        /* NUMA node of the asचिन्हित device */
	__u16 rec_cpu;          /* cpu # क्रम affinity (0xffff अगर none) */
	__u16 send_ctxt;        /* send context in use by this user context */
	__u16 egrtids;          /* number of RcvArray entries क्रम Eager Rcvs */
	__u16 rcvhdrq_cnt;      /* number of RcvHdrQ entries */
	__u16 rcvhdrq_entsize;  /* size (in bytes) क्रम each RcvHdrQ entry */
	__u16 sdma_ring_size;   /* number of entries in SDMA request ring */
पूर्ण;

काष्ठा hfi1_tid_info अणु
	/* भव address of first page in transfer */
	__aligned_u64 vaddr;
	/* poपूर्णांकer to tid array. this array is big enough */
	__aligned_u64 tidlist;
	/* number of tids programmed by this request */
	__u32 tidcnt;
	/* length of transfer buffer programmed by this request */
	__u32 length;
पूर्ण;

/*
 * This काष्ठाure is वापसed by the driver immediately after
 * खोलो to get implementation-specअगरic info, and info specअगरic to this
 * instance.
 *
 * This काष्ठा must have explicit pad fields where type sizes
 * may result in dअगरferent alignments between 32 and 64 bit
 * programs, since the 64 bit * bit kernel requires the user code
 * to have matching offsets
 */
काष्ठा hfi1_base_info अणु
	/* version of hardware, क्रम feature checking. */
	__u32 hw_version;
	/* version of software, क्रम feature checking. */
	__u32 sw_version;
	/* Job key */
	__u16 jkey;
	__u16 padding1;
	/*
	 * The special QP (queue pair) value that identअगरies PSM
	 * protocol packet from standard IB packets.
	 */
	__u32 bthqp;
	/* PIO credit वापस address, */
	__aligned_u64 sc_credits_addr;
	/*
	 * Base address of ग_लिखो-only pio buffers क्रम this process.
	 * Each buffer has sendpio_credits*64 bytes.
	 */
	__aligned_u64 pio_bufbase_sop;
	/*
	 * Base address of ग_लिखो-only pio buffers क्रम this process.
	 * Each buffer has sendpio_credits*64 bytes.
	 */
	__aligned_u64 pio_bufbase;
	/* address where receive buffer queue is mapped पूर्णांकo */
	__aligned_u64 rcvhdr_bufbase;
	/* base address of Eager receive buffers. */
	__aligned_u64 rcvegr_bufbase;
	/* base address of SDMA completion ring */
	__aligned_u64 sdma_comp_bufbase;
	/*
	 * User रेजिस्टर base क्रम init code, not to be used directly by
	 * protocol or applications.  Always maps real chip रेजिस्टर space.
	 * the रेजिस्टर addresses are:
	 * ur_rcvhdrhead, ur_rcvhdrtail, ur_rcvegrhead, ur_rcvegrtail,
	 * ur_rcvtidflow
	 */
	__aligned_u64 user_regbase;
	/* notअगरication events */
	__aligned_u64 events_bufbase;
	/* status page */
	__aligned_u64 status_bufbase;
	/* rcvhdrtail update */
	__aligned_u64 rcvhdrtail_base;
	/*
	 * shared memory pages क्रम subctxts अगर ctxt is shared; these cover
	 * all the processes in the group sharing a single context.
	 * all have enough space क्रम the num_subcontexts value on this job.
	 */
	__aligned_u64 subctxt_uregbase;
	__aligned_u64 subctxt_rcvegrbuf;
	__aligned_u64 subctxt_rcvhdrbuf;
पूर्ण;
#पूर्ण_अगर /* _LINIUX__HFI1_IOCTL_H */
