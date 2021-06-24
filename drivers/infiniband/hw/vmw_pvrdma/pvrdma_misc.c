<शैली गुरु>
/*
 * Copyright (c) 2012-2016 VMware, Inc.  All rights reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of EITHER the GNU General Public License
 * version 2 as published by the Free Software Foundation or the BSD
 * 2-Clause License. This program is distributed in the hope that it
 * will be useful, but WITHOUT ANY WARRANTY; WITHOUT EVEN THE IMPLIED
 * WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License version 2 क्रम more details at
 * http://www.gnu.org/licenses/old-licenses/gpl-2.0.en.hपंचांगl.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program available in the file COPYING in the मुख्य
 * directory of this source tree.
 *
 * The BSD 2-Clause License
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
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT,
 * INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/biपंचांगap.h>

#समावेश "pvrdma.h"

पूर्णांक pvrdma_page_dir_init(काष्ठा pvrdma_dev *dev, काष्ठा pvrdma_page_dir *pdir,
			 u64 npages, bool alloc_pages)
अणु
	u64 i;

	अगर (npages > PVRDMA_PAGE_सूची_MAX_PAGES)
		वापस -EINVAL;

	स_रखो(pdir, 0, माप(*pdir));

	pdir->dir = dma_alloc_coherent(&dev->pdev->dev, PAGE_SIZE,
				       &pdir->dir_dma, GFP_KERNEL);
	अगर (!pdir->dir)
		जाओ err;

	pdir->ntables = PVRDMA_PAGE_सूची_TABLE(npages - 1) + 1;
	pdir->tables = kसुस्मृति(pdir->ntables, माप(*pdir->tables),
			       GFP_KERNEL);
	अगर (!pdir->tables)
		जाओ err;

	क्रम (i = 0; i < pdir->ntables; i++) अणु
		pdir->tables[i] = dma_alloc_coherent(&dev->pdev->dev, PAGE_SIZE,
						(dma_addr_t *)&pdir->dir[i],
						GFP_KERNEL);
		अगर (!pdir->tables[i])
			जाओ err;
	पूर्ण

	pdir->npages = npages;

	अगर (alloc_pages) अणु
		pdir->pages = kसुस्मृति(npages, माप(*pdir->pages),
				      GFP_KERNEL);
		अगर (!pdir->pages)
			जाओ err;

		क्रम (i = 0; i < pdir->npages; i++) अणु
			dma_addr_t page_dma;

			pdir->pages[i] = dma_alloc_coherent(&dev->pdev->dev,
							    PAGE_SIZE,
							    &page_dma,
							    GFP_KERNEL);
			अगर (!pdir->pages[i])
				जाओ err;

			pvrdma_page_dir_insert_dma(pdir, i, page_dma);
		पूर्ण
	पूर्ण

	वापस 0;

err:
	pvrdma_page_dir_cleanup(dev, pdir);

	वापस -ENOMEM;
पूर्ण

अटल u64 *pvrdma_page_dir_table(काष्ठा pvrdma_page_dir *pdir, u64 idx)
अणु
	वापस pdir->tables[PVRDMA_PAGE_सूची_TABLE(idx)];
पूर्ण

dma_addr_t pvrdma_page_dir_get_dma(काष्ठा pvrdma_page_dir *pdir, u64 idx)
अणु
	वापस pvrdma_page_dir_table(pdir, idx)[PVRDMA_PAGE_सूची_PAGE(idx)];
पूर्ण

अटल व्योम pvrdma_page_dir_cleanup_pages(काष्ठा pvrdma_dev *dev,
					  काष्ठा pvrdma_page_dir *pdir)
अणु
	अगर (pdir->pages) अणु
		u64 i;

		क्रम (i = 0; i < pdir->npages && pdir->pages[i]; i++) अणु
			dma_addr_t page_dma = pvrdma_page_dir_get_dma(pdir, i);

			dma_मुक्त_coherent(&dev->pdev->dev, PAGE_SIZE,
					  pdir->pages[i], page_dma);
		पूर्ण

		kमुक्त(pdir->pages);
	पूर्ण
पूर्ण

अटल व्योम pvrdma_page_dir_cleanup_tables(काष्ठा pvrdma_dev *dev,
					   काष्ठा pvrdma_page_dir *pdir)
अणु
	अगर (pdir->tables) अणु
		पूर्णांक i;

		pvrdma_page_dir_cleanup_pages(dev, pdir);

		क्रम (i = 0; i < pdir->ntables; i++) अणु
			u64 *table = pdir->tables[i];

			अगर (table)
				dma_मुक्त_coherent(&dev->pdev->dev, PAGE_SIZE,
						  table, pdir->dir[i]);
		पूर्ण

		kमुक्त(pdir->tables);
	पूर्ण
पूर्ण

व्योम pvrdma_page_dir_cleanup(काष्ठा pvrdma_dev *dev,
			     काष्ठा pvrdma_page_dir *pdir)
अणु
	अगर (pdir->dir) अणु
		pvrdma_page_dir_cleanup_tables(dev, pdir);
		dma_मुक्त_coherent(&dev->pdev->dev, PAGE_SIZE,
				  pdir->dir, pdir->dir_dma);
	पूर्ण
पूर्ण

पूर्णांक pvrdma_page_dir_insert_dma(काष्ठा pvrdma_page_dir *pdir, u64 idx,
			       dma_addr_t daddr)
अणु
	u64 *table;

	अगर (idx >= pdir->npages)
		वापस -EINVAL;

	table = pvrdma_page_dir_table(pdir, idx);
	table[PVRDMA_PAGE_सूची_PAGE(idx)] = daddr;

	वापस 0;
पूर्ण

पूर्णांक pvrdma_page_dir_insert_umem(काष्ठा pvrdma_page_dir *pdir,
				काष्ठा ib_umem *umem, u64 offset)
अणु
	काष्ठा ib_block_iter biter;
	u64 i = offset;
	पूर्णांक ret = 0;

	अगर (offset >= pdir->npages)
		वापस -EINVAL;

	rdma_umem_क्रम_each_dma_block (umem, &biter, PAGE_SIZE) अणु
		ret = pvrdma_page_dir_insert_dma(
			pdir, i, rdma_block_iter_dma_address(&biter));
		अगर (ret)
			जाओ निकास;

		i++;
	पूर्ण

निकास:
	वापस ret;
पूर्ण

पूर्णांक pvrdma_page_dir_insert_page_list(काष्ठा pvrdma_page_dir *pdir,
				     u64 *page_list,
				     पूर्णांक num_pages)
अणु
	पूर्णांक i;
	पूर्णांक ret;

	अगर (num_pages > pdir->npages)
		वापस -EINVAL;

	क्रम (i = 0; i < num_pages; i++) अणु
		ret = pvrdma_page_dir_insert_dma(pdir, i, page_list[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

व्योम pvrdma_qp_cap_to_ib(काष्ठा ib_qp_cap *dst, स्थिर काष्ठा pvrdma_qp_cap *src)
अणु
	dst->max_send_wr = src->max_send_wr;
	dst->max_recv_wr = src->max_recv_wr;
	dst->max_send_sge = src->max_send_sge;
	dst->max_recv_sge = src->max_recv_sge;
	dst->max_अंतरभूत_data = src->max_अंतरभूत_data;
पूर्ण

व्योम ib_qp_cap_to_pvrdma(काष्ठा pvrdma_qp_cap *dst, स्थिर काष्ठा ib_qp_cap *src)
अणु
	dst->max_send_wr = src->max_send_wr;
	dst->max_recv_wr = src->max_recv_wr;
	dst->max_send_sge = src->max_send_sge;
	dst->max_recv_sge = src->max_recv_sge;
	dst->max_अंतरभूत_data = src->max_अंतरभूत_data;
पूर्ण

व्योम pvrdma_gid_to_ib(जोड़ ib_gid *dst, स्थिर जोड़ pvrdma_gid *src)
अणु
	BUILD_BUG_ON(माप(जोड़ pvrdma_gid) != माप(जोड़ ib_gid));
	स_नकल(dst, src, माप(*src));
पूर्ण

व्योम ib_gid_to_pvrdma(जोड़ pvrdma_gid *dst, स्थिर जोड़ ib_gid *src)
अणु
	BUILD_BUG_ON(माप(जोड़ pvrdma_gid) != माप(जोड़ ib_gid));
	स_नकल(dst, src, माप(*src));
पूर्ण

व्योम pvrdma_global_route_to_ib(काष्ठा ib_global_route *dst,
			       स्थिर काष्ठा pvrdma_global_route *src)
अणु
	pvrdma_gid_to_ib(&dst->dgid, &src->dgid);
	dst->flow_label = src->flow_label;
	dst->sgid_index = src->sgid_index;
	dst->hop_limit = src->hop_limit;
	dst->traffic_class = src->traffic_class;
पूर्ण

व्योम ib_global_route_to_pvrdma(काष्ठा pvrdma_global_route *dst,
			       स्थिर काष्ठा ib_global_route *src)
अणु
	ib_gid_to_pvrdma(&dst->dgid, &src->dgid);
	dst->flow_label = src->flow_label;
	dst->sgid_index = src->sgid_index;
	dst->hop_limit = src->hop_limit;
	dst->traffic_class = src->traffic_class;
पूर्ण

व्योम pvrdma_ah_attr_to_rdma(काष्ठा rdma_ah_attr *dst,
			    स्थिर काष्ठा pvrdma_ah_attr *src)
अणु
	dst->type = RDMA_AH_ATTR_TYPE_ROCE;
	pvrdma_global_route_to_ib(rdma_ah_retrieve_grh(dst), &src->grh);
	rdma_ah_set_dlid(dst, src->dlid);
	rdma_ah_set_sl(dst, src->sl);
	rdma_ah_set_path_bits(dst, src->src_path_bits);
	rdma_ah_set_अटल_rate(dst, src->अटल_rate);
	rdma_ah_set_ah_flags(dst, src->ah_flags);
	rdma_ah_set_port_num(dst, src->port_num);
	स_नकल(dst->roce.dmac, &src->dmac, ETH_ALEN);
पूर्ण

व्योम rdma_ah_attr_to_pvrdma(काष्ठा pvrdma_ah_attr *dst,
			    स्थिर काष्ठा rdma_ah_attr *src)
अणु
	ib_global_route_to_pvrdma(&dst->grh, rdma_ah_पढ़ो_grh(src));
	dst->dlid = rdma_ah_get_dlid(src);
	dst->sl = rdma_ah_get_sl(src);
	dst->src_path_bits = rdma_ah_get_path_bits(src);
	dst->अटल_rate = rdma_ah_get_अटल_rate(src);
	dst->ah_flags = rdma_ah_get_ah_flags(src);
	dst->port_num = rdma_ah_get_port_num(src);
	स_नकल(&dst->dmac, src->roce.dmac, माप(dst->dmac));
पूर्ण

u8 ib_gid_type_to_pvrdma(क्रमागत ib_gid_type gid_type)
अणु
	वापस (gid_type == IB_GID_TYPE_ROCE_UDP_ENCAP) ?
		PVRDMA_GID_TYPE_FLAG_ROCE_V2 :
		PVRDMA_GID_TYPE_FLAG_ROCE_V1;
पूर्ण
