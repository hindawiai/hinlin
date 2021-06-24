<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/*
 * Copyright (c) 2007 Cisco Systems.  All rights reserved.
 * Copyright (c) 2020 Intel Corporation.  All rights reserved.
 */

#अगर_अघोषित IB_UMEM_H
#घोषणा IB_UMEM_H

#समावेश <linux/list.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/workqueue.h>
#समावेश <rdma/ib_verbs.h>

काष्ठा ib_ucontext;
काष्ठा ib_umem_odp;
काष्ठा dma_buf_attach_ops;

काष्ठा ib_umem अणु
	काष्ठा ib_device       *ibdev;
	काष्ठा mm_काष्ठा       *owning_mm;
	u64 iova;
	माप_प्रकार			length;
	अचिन्हित दीर्घ		address;
	u32 writable : 1;
	u32 is_odp : 1;
	u32 is_dmabuf : 1;
	काष्ठा work_काष्ठा	work;
	काष्ठा sg_table sg_head;
	पूर्णांक             nmap;
	अचिन्हित पूर्णांक    sg_nents;
पूर्ण;

काष्ठा ib_umem_dmabuf अणु
	काष्ठा ib_umem umem;
	काष्ठा dma_buf_attachment *attach;
	काष्ठा sg_table *sgt;
	काष्ठा scatterlist *first_sg;
	काष्ठा scatterlist *last_sg;
	अचिन्हित दीर्घ first_sg_offset;
	अचिन्हित दीर्घ last_sg_trim;
	व्योम *निजी;
पूर्ण;

अटल अंतरभूत काष्ठा ib_umem_dmabuf *to_ib_umem_dmabuf(काष्ठा ib_umem *umem)
अणु
	वापस container_of(umem, काष्ठा ib_umem_dmabuf, umem);
पूर्ण

/* Returns the offset of the umem start relative to the first page. */
अटल अंतरभूत पूर्णांक ib_umem_offset(काष्ठा ib_umem *umem)
अणु
	वापस umem->address & ~PAGE_MASK;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ ib_umem_dma_offset(काष्ठा ib_umem *umem,
					       अचिन्हित दीर्घ pgsz)
अणु
	वापस (sg_dma_address(umem->sg_head.sgl) + ib_umem_offset(umem)) &
	       (pgsz - 1);
पूर्ण

अटल अंतरभूत माप_प्रकार ib_umem_num_dma_blocks(काष्ठा ib_umem *umem,
					    अचिन्हित दीर्घ pgsz)
अणु
	वापस (माप_प्रकार)((ALIGN(umem->iova + umem->length, pgsz) -
			 ALIGN_DOWN(umem->iova, pgsz))) /
	       pgsz;
पूर्ण

अटल अंतरभूत माप_प्रकार ib_umem_num_pages(काष्ठा ib_umem *umem)
अणु
	वापस ib_umem_num_dma_blocks(umem, PAGE_SIZE);
पूर्ण

अटल अंतरभूत व्योम __rdma_umem_block_iter_start(काष्ठा ib_block_iter *biter,
						काष्ठा ib_umem *umem,
						अचिन्हित दीर्घ pgsz)
अणु
	__rdma_block_iter_start(biter, umem->sg_head.sgl, umem->nmap, pgsz);
पूर्ण

/**
 * rdma_umem_क्रम_each_dma_block - iterate over contiguous DMA blocks of the umem
 * @umem: umem to iterate over
 * @pgsz: Page size to split the list पूर्णांकo
 *
 * pgsz must be <= PAGE_SIZE or computed by ib_umem_find_best_pgsz(). The
 * वापसed DMA blocks will be aligned to pgsz and span the range:
 * ALIGN_DOWN(umem->address, pgsz) to ALIGN(umem->address + umem->length, pgsz)
 *
 * Perक्रमms exactly ib_umem_num_dma_blocks() iterations.
 */
#घोषणा rdma_umem_क्रम_each_dma_block(umem, biter, pgsz)                        \
	क्रम (__rdma_umem_block_iter_start(biter, umem, pgsz);                  \
	     __rdma_block_iter_next(biter);)

#अगर_घोषित CONFIG_INFINIBAND_USER_MEM

काष्ठा ib_umem *ib_umem_get(काष्ठा ib_device *device, अचिन्हित दीर्घ addr,
			    माप_प्रकार size, पूर्णांक access);
व्योम ib_umem_release(काष्ठा ib_umem *umem);
पूर्णांक ib_umem_copy_from(व्योम *dst, काष्ठा ib_umem *umem, माप_प्रकार offset,
		      माप_प्रकार length);
अचिन्हित दीर्घ ib_umem_find_best_pgsz(काष्ठा ib_umem *umem,
				     अचिन्हित दीर्घ pgsz_biपंचांगap,
				     अचिन्हित दीर्घ virt);

/**
 * ib_umem_find_best_pgoff - Find best HW page size
 *
 * @umem: umem काष्ठा
 * @pgsz_biपंचांगap biपंचांगap of HW supported page sizes
 * @pgoff_biपंचांगask: Mask of bits that can be represented with an offset
 *
 * This is very similar to ib_umem_find_best_pgsz() except instead of accepting
 * an IOVA it accepts a biपंचांगask specअगरying what address bits can be represented
 * with a page offset.
 *
 * For instance अगर the HW has multiple page sizes, requires 64 byte alignemnt,
 * and can support aligned offsets up to 4032 then pgoff_biपंचांगask would be
 * "111111000000".
 *
 * If the pgoff_biपंचांगask requires either alignment in the low bit or an
 * unavailable page size क्रम the high bits, this function वापसs 0.
 */
अटल अंतरभूत अचिन्हित दीर्घ ib_umem_find_best_pgoff(काष्ठा ib_umem *umem,
						    अचिन्हित दीर्घ pgsz_biपंचांगap,
						    u64 pgoff_biपंचांगask)
अणु
	काष्ठा scatterlist *sg = umem->sg_head.sgl;
	dma_addr_t dma_addr;

	dma_addr = sg_dma_address(sg) + (umem->address & ~PAGE_MASK);
	वापस ib_umem_find_best_pgsz(umem, pgsz_biपंचांगap,
				      dma_addr & pgoff_biपंचांगask);
पूर्ण

काष्ठा ib_umem_dmabuf *ib_umem_dmabuf_get(काष्ठा ib_device *device,
					  अचिन्हित दीर्घ offset, माप_प्रकार size,
					  पूर्णांक fd, पूर्णांक access,
					  स्थिर काष्ठा dma_buf_attach_ops *ops);
पूर्णांक ib_umem_dmabuf_map_pages(काष्ठा ib_umem_dmabuf *umem_dmabuf);
व्योम ib_umem_dmabuf_unmap_pages(काष्ठा ib_umem_dmabuf *umem_dmabuf);
व्योम ib_umem_dmabuf_release(काष्ठा ib_umem_dmabuf *umem_dmabuf);

#अन्यथा /* CONFIG_INFINIBAND_USER_MEM */

#समावेश <linux/err.h>

अटल अंतरभूत काष्ठा ib_umem *ib_umem_get(काष्ठा ib_device *device,
					  अचिन्हित दीर्घ addr, माप_प्रकार size,
					  पूर्णांक access)
अणु
	वापस ERR_PTR(-EOPNOTSUPP);
पूर्ण
अटल अंतरभूत व्योम ib_umem_release(काष्ठा ib_umem *umem) अणु पूर्ण
अटल अंतरभूत पूर्णांक ib_umem_copy_from(व्योम *dst, काष्ठा ib_umem *umem, माप_प्रकार offset,
		      		    माप_प्रकार length) अणु
	वापस -EOPNOTSUPP;
पूर्ण
अटल अंतरभूत अचिन्हित दीर्घ ib_umem_find_best_pgsz(काष्ठा ib_umem *umem,
						   अचिन्हित दीर्घ pgsz_biपंचांगap,
						   अचिन्हित दीर्घ virt)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत अचिन्हित दीर्घ ib_umem_find_best_pgoff(काष्ठा ib_umem *umem,
						    अचिन्हित दीर्घ pgsz_biपंचांगap,
						    u64 pgoff_biपंचांगask)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत
काष्ठा ib_umem_dmabuf *ib_umem_dmabuf_get(काष्ठा ib_device *device,
					  अचिन्हित दीर्घ offset,
					  माप_प्रकार size, पूर्णांक fd,
					  पूर्णांक access,
					  काष्ठा dma_buf_attach_ops *ops)
अणु
	वापस ERR_PTR(-EOPNOTSUPP);
पूर्ण
अटल अंतरभूत पूर्णांक ib_umem_dmabuf_map_pages(काष्ठा ib_umem_dmabuf *umem_dmabuf)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
अटल अंतरभूत व्योम ib_umem_dmabuf_unmap_pages(काष्ठा ib_umem_dmabuf *umem_dmabuf) अणु पूर्ण
अटल अंतरभूत व्योम ib_umem_dmabuf_release(काष्ठा ib_umem_dmabuf *umem_dmabuf) अणु पूर्ण

#पूर्ण_अगर /* CONFIG_INFINIBAND_USER_MEM */
#पूर्ण_अगर /* IB_UMEM_H */
