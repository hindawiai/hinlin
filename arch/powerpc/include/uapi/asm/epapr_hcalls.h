<शैली गुरु>
/* SPDX-License-Identअगरier: ((GPL-2.0+ WITH Linux-syscall-note) OR BSD-3-Clause) */
/*
 * ePAPR hcall पूर्णांकerface
 *
 * Copyright 2008-2011 Freescale Semiconductor, Inc.
 *
 * Author: Timur Tabi <timur@मुक्तscale.com>
 *
 * This file is provided under a dual BSD/GPL license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary क्रमm must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       करोcumentation and/or other materials provided with the distribution.
 *     * Neither the name of Freescale Semiconductor nor the
 *       names of its contributors may be used to enकरोrse or promote products
 *       derived from this software without specअगरic prior written permission.
 *
 *
 * ALTERNATIVELY, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") as published by the Free Software
 * Foundation, either version 2 of that License or (at your option) any
 * later version.
 *
 * THIS SOFTWARE IS PROVIDED BY Freescale Semiconductor ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Freescale Semiconductor BE LIABLE FOR ANY
 * सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#अगर_अघोषित _UAPI_ASM_POWERPC_EPAPR_HCALLS_H
#घोषणा _UAPI_ASM_POWERPC_EPAPR_HCALLS_H

#घोषणा EV_BYTE_CHANNEL_SEND		1
#घोषणा EV_BYTE_CHANNEL_RECEIVE		2
#घोषणा EV_BYTE_CHANNEL_POLL		3
#घोषणा EV_INT_SET_CONFIG		4
#घोषणा EV_INT_GET_CONFIG		5
#घोषणा EV_INT_SET_MASK			6
#घोषणा EV_INT_GET_MASK			7
#घोषणा EV_INT_IACK			9
#घोषणा EV_INT_EOI			10
#घोषणा EV_INT_SEND_IPI			11
#घोषणा EV_INT_SET_TASK_PRIORITY	12
#घोषणा EV_INT_GET_TASK_PRIORITY	13
#घोषणा EV_DOORBELL_SEND		14
#घोषणा EV_MSGSND			15
#घोषणा EV_IDLE				16

/* venकरोr ID: epapr */
#घोषणा EV_LOCAL_VENDOR_ID		0	/* क्रम निजी use */
#घोषणा EV_EPAPR_VENDOR_ID		1
#घोषणा EV_FSL_VENDOR_ID		2	/* Freescale Semiconductor */
#घोषणा EV_IBM_VENDOR_ID		3	/* IBM */
#घोषणा EV_GHS_VENDOR_ID		4	/* Green Hills Software */
#घोषणा EV_ENEA_VENDOR_ID		5	/* Enea */
#घोषणा EV_WR_VENDOR_ID			6	/* Wind River Systems */
#घोषणा EV_AMCC_VENDOR_ID		7	/* Applied Micro Circuits */
#घोषणा EV_KVM_VENDOR_ID		42	/* KVM */

/* The max number of bytes that a byte channel can send or receive per call */
#घोषणा EV_BYTE_CHANNEL_MAX_BYTES	16


#घोषणा _EV_HCALL_TOKEN(id, num) (((id) << 16) | (num))
#घोषणा EV_HCALL_TOKEN(hcall_num) _EV_HCALL_TOKEN(EV_EPAPR_VENDOR_ID, hcall_num)

/* epapr वापस codes */
#घोषणा EV_SUCCESS		0
#घोषणा EV_EPERM		1	/* Operation not permitted */
#घोषणा EV_ENOENT		2	/*  Entry Not Found */
#घोषणा EV_EIO			3	/* I/O error occurred */
#घोषणा EV_EAGAIN		4	/* The operation had insufficient
					 * resources to complete and should be
					 * retried
					 */
#घोषणा EV_ENOMEM		5	/* There was insufficient memory to
					 * complete the operation */
#घोषणा EV_EFAULT		6	/* Bad guest address */
#घोषणा EV_ENODEV		7	/* No such device */
#घोषणा EV_EINVAL		8	/* An argument supplied to the hcall
					   was out of range or invalid */
#घोषणा EV_INTERNAL		9	/* An पूर्णांकernal error occurred */
#घोषणा EV_CONFIG		10	/* A configuration error was detected */
#घोषणा EV_INVALID_STATE	11	/* The object is in an invalid state */
#घोषणा EV_UNIMPLEMENTED	12	/* Unimplemented hypercall */
#घोषणा EV_BUFFER_OVERFLOW	13	/* Caller-supplied buffer too small */

#पूर्ण_अगर /* _UAPI_ASM_POWERPC_EPAPR_HCALLS_H */
