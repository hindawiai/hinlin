<शैली गुरु>
#अगर_अघोषित _HFI1_USER_EXP_RCV_H
#घोषणा _HFI1_USER_EXP_RCV_H
/*
 * Copyright(c) 2020 - Cornelis Networks, Inc.
 * Copyright(c) 2015 - 2017 Intel Corporation.
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

#समावेश "hfi.h"
#समावेश "exp_rcv.h"

काष्ठा tid_pageset अणु
	u16 idx;
	u16 count;
पूर्ण;

काष्ठा tid_user_buf अणु
	अचिन्हित दीर्घ vaddr;
	अचिन्हित दीर्घ length;
	अचिन्हित पूर्णांक npages;
	काष्ठा page **pages;
	काष्ठा tid_pageset *psets;
	अचिन्हित पूर्णांक n_psets;
पूर्ण;

काष्ठा tid_rb_node अणु
	काष्ठा mmu_पूर्णांकerval_notअगरier notअगरier;
	काष्ठा hfi1_filedata *fdata;
	अचिन्हित दीर्घ phys;
	काष्ठा tid_group *grp;
	u32 rcventry;
	dma_addr_t dma_addr;
	bool मुक्तd;
	अचिन्हित पूर्णांक npages;
	काष्ठा page *pages[];
पूर्ण;

अटल अंतरभूत पूर्णांक num_user_pages(अचिन्हित दीर्घ addr,
				 अचिन्हित दीर्घ len)
अणु
	स्थिर अचिन्हित दीर्घ spage = addr & PAGE_MASK;
	स्थिर अचिन्हित दीर्घ epage = (addr + len - 1) & PAGE_MASK;

	वापस 1 + ((epage - spage) >> PAGE_SHIFT);
पूर्ण

पूर्णांक hfi1_user_exp_rcv_init(काष्ठा hfi1_filedata *fd,
			   काष्ठा hfi1_ctxtdata *uctxt);
व्योम hfi1_user_exp_rcv_मुक्त(काष्ठा hfi1_filedata *fd);
पूर्णांक hfi1_user_exp_rcv_setup(काष्ठा hfi1_filedata *fd,
			    काष्ठा hfi1_tid_info *tinfo);
पूर्णांक hfi1_user_exp_rcv_clear(काष्ठा hfi1_filedata *fd,
			    काष्ठा hfi1_tid_info *tinfo);
पूर्णांक hfi1_user_exp_rcv_invalid(काष्ठा hfi1_filedata *fd,
			      काष्ठा hfi1_tid_info *tinfo);

अटल अंतरभूत काष्ठा mm_काष्ठा *mm_from_tid_node(काष्ठा tid_rb_node *node)
अणु
	वापस node->notअगरier.mm;
पूर्ण

#पूर्ण_अगर /* _HFI1_USER_EXP_RCV_H */
