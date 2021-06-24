<शैली गुरु>
#अगर_अघोषित DEF_RVTMR_H
#घोषणा DEF_RVTMR_H

/*
 * Copyright(c) 2016 Intel Corporation.
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

#समावेश <rdma/rdma_vt.h>

काष्ठा rvt_mr अणु
	काष्ठा ib_mr ibmr;
	काष्ठा ib_umem *umem;
	काष्ठा rvt_mregion mr;  /* must be last */
पूर्ण;

अटल अंतरभूत काष्ठा rvt_mr *to_imr(काष्ठा ib_mr *ibmr)
अणु
	वापस container_of(ibmr, काष्ठा rvt_mr, ibmr);
पूर्ण

पूर्णांक rvt_driver_mr_init(काष्ठा rvt_dev_info *rdi);
व्योम rvt_mr_निकास(काष्ठा rvt_dev_info *rdi);

/* Mem Regions */
काष्ठा ib_mr *rvt_get_dma_mr(काष्ठा ib_pd *pd, पूर्णांक acc);
काष्ठा ib_mr *rvt_reg_user_mr(काष्ठा ib_pd *pd, u64 start, u64 length,
			      u64 virt_addr, पूर्णांक mr_access_flags,
			      काष्ठा ib_udata *udata);
पूर्णांक rvt_dereg_mr(काष्ठा ib_mr *ibmr, काष्ठा ib_udata *udata);
काष्ठा ib_mr *rvt_alloc_mr(काष्ठा ib_pd *pd, क्रमागत ib_mr_type mr_type,
			   u32 max_num_sg);
पूर्णांक rvt_map_mr_sg(काष्ठा ib_mr *ibmr, काष्ठा scatterlist *sg,
		  पूर्णांक sg_nents, अचिन्हित पूर्णांक *sg_offset);

#पूर्ण_अगर          /* DEF_RVTMR_H */
