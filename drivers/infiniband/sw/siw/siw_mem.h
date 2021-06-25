<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 or BSD-3-Clause */

/* Authors: Bernard Metzler <bmt@zurich.ibm.com> */
/* Copyright (c) 2008-2019, IBM Corporation */

#अगर_अघोषित _SIW_MEM_H
#घोषणा _SIW_MEM_H

काष्ठा siw_umem *siw_umem_get(u64 start, u64 len, bool writable);
व्योम siw_umem_release(काष्ठा siw_umem *umem, bool dirty);
काष्ठा siw_pbl *siw_pbl_alloc(u32 num_buf);
dma_addr_t siw_pbl_get_buffer(काष्ठा siw_pbl *pbl, u64 off, पूर्णांक *len, पूर्णांक *idx);
काष्ठा siw_mem *siw_mem_id2obj(काष्ठा siw_device *sdev, पूर्णांक stag_index);
पूर्णांक siw_mem_add(काष्ठा siw_device *sdev, काष्ठा siw_mem *m);
पूर्णांक siw_invalidate_stag(काष्ठा ib_pd *pd, u32 stag);
पूर्णांक siw_check_mem(काष्ठा ib_pd *pd, काष्ठा siw_mem *mem, u64 addr,
		  क्रमागत ib_access_flags perms, पूर्णांक len);
पूर्णांक siw_check_sge(काष्ठा ib_pd *pd, काष्ठा siw_sge *sge,
		  काष्ठा siw_mem *mem[], क्रमागत ib_access_flags perms,
		  u32 off, पूर्णांक len);
व्योम siw_wqe_put_mem(काष्ठा siw_wqe *wqe, क्रमागत siw_opcode op);
पूर्णांक siw_mr_add_mem(काष्ठा siw_mr *mr, काष्ठा ib_pd *pd, व्योम *mem_obj,
		   u64 start, u64 len, पूर्णांक rights);
व्योम siw_mr_drop_mem(काष्ठा siw_mr *mr);
व्योम siw_मुक्त_mem(काष्ठा kref *ref);

अटल अंतरभूत व्योम siw_mem_put(काष्ठा siw_mem *mem)
अणु
	kref_put(&mem->ref, siw_मुक्त_mem);
पूर्ण

अटल अंतरभूत व्योम siw_unref_mem_sgl(काष्ठा siw_mem **mem, अचिन्हित पूर्णांक num_sge)
अणु
	जबतक (num_sge) अणु
		अगर (*mem == शून्य)
			अवरोध;

		siw_mem_put(*mem);
		*mem = शून्य;
		mem++;
		num_sge--;
	पूर्ण
पूर्ण

#घोषणा CHUNK_SHIFT 9 /* sets number of pages per chunk */
#घोषणा PAGES_PER_CHUNK (_AC(1, UL) << CHUNK_SHIFT)
#घोषणा CHUNK_MASK (~(PAGES_PER_CHUNK - 1))
#घोषणा PAGE_CHUNK_SIZE (PAGES_PER_CHUNK * माप(काष्ठा page *))

/*
 * siw_get_upage()
 *
 * Get page poपूर्णांकer क्रम address on given umem.
 *
 * @umem: two dimensional list of page poपूर्णांकers
 * @addr: user भव address
 */
अटल अंतरभूत काष्ठा page *siw_get_upage(काष्ठा siw_umem *umem, u64 addr)
अणु
	अचिन्हित पूर्णांक page_idx = (addr - umem->fp_addr) >> PAGE_SHIFT,
		     chunk_idx = page_idx >> CHUNK_SHIFT,
		     page_in_chunk = page_idx & ~CHUNK_MASK;

	अगर (likely(page_idx < umem->num_pages))
		वापस umem->page_chunk[chunk_idx].plist[page_in_chunk];

	वापस शून्य;
पूर्ण
#पूर्ण_अगर
