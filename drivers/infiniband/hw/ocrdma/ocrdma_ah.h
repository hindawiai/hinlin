<शैली गुरु>
/* This file is part of the Emulex RoCE Device Driver क्रम
 * RoCE (RDMA over Converged Ethernet) adapters.
 * Copyright (C) 2012-2015 Emulex. All rights reserved.
 * EMULEX and SLI are trademarks of Emulex.
 * www.emulex.com
 *
 * This software is available to you under a choice of one of two licenses.
 * You may choose to be licensed under the terms of the GNU General Public
 * License (GPL) Version 2, available from the file COPYING in the मुख्य
 * directory of this source tree, or the BSD license below:
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 *
 * - Redistributions in binary क्रमm must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in
 *   the करोcumentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Contact Inक्रमmation:
 * linux-drivers@emulex.com
 *
 * Emulex
 * 3333 Susan Street
 * Costa Mesa, CA 92626
 */

#अगर_अघोषित __OCRDMA_AH_H__
#घोषणा __OCRDMA_AH_H__

क्रमागत अणु
	OCRDMA_AH_ID_MASK		= 0x3FF,
	OCRDMA_AH_VLAN_VALID_MASK	= 0x01,
	OCRDMA_AH_VLAN_VALID_SHIFT	= 0x1F,
	OCRDMA_AH_L3_TYPE_MASK		= 0x03,
	OCRDMA_AH_L3_TYPE_SHIFT		= 0x1D /* 29 bits */
पूर्ण;

पूर्णांक ocrdma_create_ah(काष्ठा ib_ah *ah, काष्ठा rdma_ah_init_attr *init_attr,
		     काष्ठा ib_udata *udata);
पूर्णांक ocrdma_destroy_ah(काष्ठा ib_ah *ah, u32 flags);
पूर्णांक ocrdma_query_ah(काष्ठा ib_ah *ah, काष्ठा rdma_ah_attr *ah_attr);

पूर्णांक ocrdma_process_mad(काष्ठा ib_device *dev, पूर्णांक process_mad_flags,
		       u32 port_num, स्थिर काष्ठा ib_wc *in_wc,
		       स्थिर काष्ठा ib_grh *in_grh, स्थिर काष्ठा ib_mad *in,
		       काष्ठा ib_mad *out, माप_प्रकार *out_mad_size,
		       u16 *out_mad_pkey_index);
#पूर्ण_अगर				/* __OCRDMA_AH_H__ */
