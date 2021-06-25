<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/*
 * Copyright (c) 2016 Mellanox Technologies Ltd. All rights reserved.
 * Copyright (c) 2015 System Fabric Works, Inc. All rights reserved.
 */

#समावेश "rxe.h"
#समावेश "rxe_loc.h"

/*
 * lfsr (linear feedback shअगरt रेजिस्टर) with period 255
 */
अटल u8 rxe_get_key(व्योम)
अणु
	अटल u32 key = 1;

	key = key << 1;

	key |= (0 != (key & 0x100)) ^ (0 != (key & 0x10))
		^ (0 != (key & 0x80)) ^ (0 != (key & 0x40));

	key &= 0xff;

	वापस key;
पूर्ण

पूर्णांक mr_check_range(काष्ठा rxe_mr *mr, u64 iova, माप_प्रकार length)
अणु
	चयन (mr->type) अणु
	हाल RXE_MR_TYPE_DMA:
		वापस 0;

	हाल RXE_MR_TYPE_MR:
		अगर (iova < mr->iova || length > mr->length ||
		    iova > mr->iova + mr->length - length)
			वापस -EFAULT;
		वापस 0;

	शेष:
		वापस -EFAULT;
	पूर्ण
पूर्ण

#घोषणा IB_ACCESS_REMOTE	(IB_ACCESS_REMOTE_READ		\
				| IB_ACCESS_REMOTE_WRITE	\
				| IB_ACCESS_REMOTE_ATOMIC)

अटल व्योम rxe_mr_init(पूर्णांक access, काष्ठा rxe_mr *mr)
अणु
	u32 lkey = mr->pelem.index << 8 | rxe_get_key();
	u32 rkey = (access & IB_ACCESS_REMOTE) ? lkey : 0;

	mr->ibmr.lkey = lkey;
	mr->ibmr.rkey = rkey;
	mr->state = RXE_MR_STATE_INVALID;
	mr->type = RXE_MR_TYPE_NONE;
	mr->map_shअगरt = ilog2(RXE_BUF_PER_MAP);
पूर्ण

व्योम rxe_mr_cleanup(काष्ठा rxe_pool_entry *arg)
अणु
	काष्ठा rxe_mr *mr = container_of(arg, typeof(*mr), pelem);
	पूर्णांक i;

	ib_umem_release(mr->umem);

	अगर (mr->map) अणु
		क्रम (i = 0; i < mr->num_map; i++)
			kमुक्त(mr->map[i]);

		kमुक्त(mr->map);
	पूर्ण
पूर्ण

अटल पूर्णांक rxe_mr_alloc(काष्ठा rxe_mr *mr, पूर्णांक num_buf)
अणु
	पूर्णांक i;
	पूर्णांक num_map;
	काष्ठा rxe_map **map = mr->map;

	num_map = (num_buf + RXE_BUF_PER_MAP - 1) / RXE_BUF_PER_MAP;

	mr->map = kदो_स्मृति_array(num_map, माप(*map), GFP_KERNEL);
	अगर (!mr->map)
		जाओ err1;

	क्रम (i = 0; i < num_map; i++) अणु
		mr->map[i] = kदो_स्मृति(माप(**map), GFP_KERNEL);
		अगर (!mr->map[i])
			जाओ err2;
	पूर्ण

	BUILD_BUG_ON(!is_घातer_of_2(RXE_BUF_PER_MAP));

	mr->map_shअगरt = ilog2(RXE_BUF_PER_MAP);
	mr->map_mask = RXE_BUF_PER_MAP - 1;

	mr->num_buf = num_buf;
	mr->num_map = num_map;
	mr->max_buf = num_map * RXE_BUF_PER_MAP;

	वापस 0;

err2:
	क्रम (i--; i >= 0; i--)
		kमुक्त(mr->map[i]);

	kमुक्त(mr->map);
err1:
	वापस -ENOMEM;
पूर्ण

व्योम rxe_mr_init_dma(काष्ठा rxe_pd *pd, पूर्णांक access, काष्ठा rxe_mr *mr)
अणु
	rxe_mr_init(access, mr);

	mr->ibmr.pd = &pd->ibpd;
	mr->access = access;
	mr->state = RXE_MR_STATE_VALID;
	mr->type = RXE_MR_TYPE_DMA;
पूर्ण

पूर्णांक rxe_mr_init_user(काष्ठा rxe_pd *pd, u64 start, u64 length, u64 iova,
		     पूर्णांक access, काष्ठा ib_udata *udata, काष्ठा rxe_mr *mr)
अणु
	काष्ठा rxe_map		**map;
	काष्ठा rxe_phys_buf	*buf = शून्य;
	काष्ठा ib_umem		*umem;
	काष्ठा sg_page_iter	sg_iter;
	पूर्णांक			num_buf;
	व्योम			*vaddr;
	पूर्णांक err;

	umem = ib_umem_get(pd->ibpd.device, start, length, access);
	अगर (IS_ERR(umem)) अणु
		pr_warn("err %d from rxe_umem_get\n",
			(पूर्णांक)PTR_ERR(umem));
		err = -EINVAL;
		जाओ err1;
	पूर्ण

	mr->umem = umem;
	num_buf = ib_umem_num_pages(umem);

	rxe_mr_init(access, mr);

	err = rxe_mr_alloc(mr, num_buf);
	अगर (err) अणु
		pr_warn("err %d from rxe_mr_alloc\n", err);
		ib_umem_release(umem);
		जाओ err1;
	पूर्ण

	mr->page_shअगरt = PAGE_SHIFT;
	mr->page_mask = PAGE_SIZE - 1;

	num_buf			= 0;
	map = mr->map;
	अगर (length > 0) अणु
		buf = map[0]->buf;

		क्रम_each_sg_page(umem->sg_head.sgl, &sg_iter, umem->nmap, 0) अणु
			अगर (num_buf >= RXE_BUF_PER_MAP) अणु
				map++;
				buf = map[0]->buf;
				num_buf = 0;
			पूर्ण

			vaddr = page_address(sg_page_iter_page(&sg_iter));
			अगर (!vaddr) अणु
				pr_warn("null vaddr\n");
				ib_umem_release(umem);
				err = -ENOMEM;
				जाओ err1;
			पूर्ण

			buf->addr = (uपूर्णांकptr_t)vaddr;
			buf->size = PAGE_SIZE;
			num_buf++;
			buf++;

		पूर्ण
	पूर्ण

	mr->ibmr.pd = &pd->ibpd;
	mr->umem = umem;
	mr->access = access;
	mr->length = length;
	mr->iova = iova;
	mr->va = start;
	mr->offset = ib_umem_offset(umem);
	mr->state = RXE_MR_STATE_VALID;
	mr->type = RXE_MR_TYPE_MR;

	वापस 0;

err1:
	वापस err;
पूर्ण

पूर्णांक rxe_mr_init_fast(काष्ठा rxe_pd *pd, पूर्णांक max_pages, काष्ठा rxe_mr *mr)
अणु
	पूर्णांक err;

	rxe_mr_init(0, mr);

	/* In fastreg, we also set the rkey */
	mr->ibmr.rkey = mr->ibmr.lkey;

	err = rxe_mr_alloc(mr, max_pages);
	अगर (err)
		जाओ err1;

	mr->ibmr.pd = &pd->ibpd;
	mr->max_buf = max_pages;
	mr->state = RXE_MR_STATE_FREE;
	mr->type = RXE_MR_TYPE_MR;

	वापस 0;

err1:
	वापस err;
पूर्ण

अटल व्योम lookup_iova(काष्ठा rxe_mr *mr, u64 iova, पूर्णांक *m_out, पूर्णांक *n_out,
			माप_प्रकार *offset_out)
अणु
	माप_प्रकार offset = iova - mr->iova + mr->offset;
	पूर्णांक			map_index;
	पूर्णांक			buf_index;
	u64			length;

	अगर (likely(mr->page_shअगरt)) अणु
		*offset_out = offset & mr->page_mask;
		offset >>= mr->page_shअगरt;
		*n_out = offset & mr->map_mask;
		*m_out = offset >> mr->map_shअगरt;
	पूर्ण अन्यथा अणु
		map_index = 0;
		buf_index = 0;

		length = mr->map[map_index]->buf[buf_index].size;

		जबतक (offset >= length) अणु
			offset -= length;
			buf_index++;

			अगर (buf_index == RXE_BUF_PER_MAP) अणु
				map_index++;
				buf_index = 0;
			पूर्ण
			length = mr->map[map_index]->buf[buf_index].size;
		पूर्ण

		*m_out = map_index;
		*n_out = buf_index;
		*offset_out = offset;
	पूर्ण
पूर्ण

व्योम *iova_to_vaddr(काष्ठा rxe_mr *mr, u64 iova, पूर्णांक length)
अणु
	माप_प्रकार offset;
	पूर्णांक m, n;
	व्योम *addr;

	अगर (mr->state != RXE_MR_STATE_VALID) अणु
		pr_warn("mr not in valid state\n");
		addr = शून्य;
		जाओ out;
	पूर्ण

	अगर (!mr->map) अणु
		addr = (व्योम *)(uपूर्णांकptr_t)iova;
		जाओ out;
	पूर्ण

	अगर (mr_check_range(mr, iova, length)) अणु
		pr_warn("range violation\n");
		addr = शून्य;
		जाओ out;
	पूर्ण

	lookup_iova(mr, iova, &m, &n, &offset);

	अगर (offset + length > mr->map[m]->buf[n].size) अणु
		pr_warn("crosses page boundary\n");
		addr = शून्य;
		जाओ out;
	पूर्ण

	addr = (व्योम *)(uपूर्णांकptr_t)mr->map[m]->buf[n].addr + offset;

out:
	वापस addr;
पूर्ण

/* copy data from a range (vaddr, vaddr+length-1) to or from
 * a mr object starting at iova. Compute incremental value of
 * crc32 अगर crcp is not zero. caller must hold a reference to mr
 */
पूर्णांक rxe_mr_copy(काष्ठा rxe_mr *mr, u64 iova, व्योम *addr, पूर्णांक length,
		क्रमागत copy_direction dir, u32 *crcp)
अणु
	पूर्णांक			err;
	पूर्णांक			bytes;
	u8			*va;
	काष्ठा rxe_map		**map;
	काष्ठा rxe_phys_buf	*buf;
	पूर्णांक			m;
	पूर्णांक			i;
	माप_प्रकार			offset;
	u32			crc = crcp ? (*crcp) : 0;

	अगर (length == 0)
		वापस 0;

	अगर (mr->type == RXE_MR_TYPE_DMA) अणु
		u8 *src, *dest;

		src = (dir == to_mr_obj) ? addr : ((व्योम *)(uपूर्णांकptr_t)iova);

		dest = (dir == to_mr_obj) ? ((व्योम *)(uपूर्णांकptr_t)iova) : addr;

		स_नकल(dest, src, length);

		अगर (crcp)
			*crcp = rxe_crc32(to_rdev(mr->ibmr.device), *crcp, dest,
					  length);

		वापस 0;
	पूर्ण

	WARN_ON_ONCE(!mr->map);

	err = mr_check_range(mr, iova, length);
	अगर (err) अणु
		err = -EFAULT;
		जाओ err1;
	पूर्ण

	lookup_iova(mr, iova, &m, &i, &offset);

	map = mr->map + m;
	buf	= map[0]->buf + i;

	जबतक (length > 0) अणु
		u8 *src, *dest;

		va	= (u8 *)(uपूर्णांकptr_t)buf->addr + offset;
		src = (dir == to_mr_obj) ? addr : va;
		dest = (dir == to_mr_obj) ? va : addr;

		bytes	= buf->size - offset;

		अगर (bytes > length)
			bytes = length;

		स_नकल(dest, src, bytes);

		अगर (crcp)
			crc = rxe_crc32(to_rdev(mr->ibmr.device), crc, dest,
					bytes);

		length	-= bytes;
		addr	+= bytes;

		offset	= 0;
		buf++;
		i++;

		अगर (i == RXE_BUF_PER_MAP) अणु
			i = 0;
			map++;
			buf = map[0]->buf;
		पूर्ण
	पूर्ण

	अगर (crcp)
		*crcp = crc;

	वापस 0;

err1:
	वापस err;
पूर्ण

/* copy data in or out of a wqe, i.e. sg list
 * under the control of a dma descriptor
 */
पूर्णांक copy_data(
	काष्ठा rxe_pd		*pd,
	पूर्णांक			access,
	काष्ठा rxe_dma_info	*dma,
	व्योम			*addr,
	पूर्णांक			length,
	क्रमागत copy_direction	dir,
	u32			*crcp)
अणु
	पूर्णांक			bytes;
	काष्ठा rxe_sge		*sge	= &dma->sge[dma->cur_sge];
	पूर्णांक			offset	= dma->sge_offset;
	पूर्णांक			resid	= dma->resid;
	काष्ठा rxe_mr		*mr	= शून्य;
	u64			iova;
	पूर्णांक			err;

	अगर (length == 0)
		वापस 0;

	अगर (length > resid) अणु
		err = -EINVAL;
		जाओ err2;
	पूर्ण

	अगर (sge->length && (offset < sge->length)) अणु
		mr = lookup_mr(pd, access, sge->lkey, lookup_local);
		अगर (!mr) अणु
			err = -EINVAL;
			जाओ err1;
		पूर्ण
	पूर्ण

	जबतक (length > 0) अणु
		bytes = length;

		अगर (offset >= sge->length) अणु
			अगर (mr) अणु
				rxe_drop_ref(mr);
				mr = शून्य;
			पूर्ण
			sge++;
			dma->cur_sge++;
			offset = 0;

			अगर (dma->cur_sge >= dma->num_sge) अणु
				err = -ENOSPC;
				जाओ err2;
			पूर्ण

			अगर (sge->length) अणु
				mr = lookup_mr(pd, access, sge->lkey,
					       lookup_local);
				अगर (!mr) अणु
					err = -EINVAL;
					जाओ err1;
				पूर्ण
			पूर्ण अन्यथा अणु
				जारी;
			पूर्ण
		पूर्ण

		अगर (bytes > sge->length - offset)
			bytes = sge->length - offset;

		अगर (bytes > 0) अणु
			iova = sge->addr + offset;

			err = rxe_mr_copy(mr, iova, addr, bytes, dir, crcp);
			अगर (err)
				जाओ err2;

			offset	+= bytes;
			resid	-= bytes;
			length	-= bytes;
			addr	+= bytes;
		पूर्ण
	पूर्ण

	dma->sge_offset = offset;
	dma->resid	= resid;

	अगर (mr)
		rxe_drop_ref(mr);

	वापस 0;

err2:
	अगर (mr)
		rxe_drop_ref(mr);
err1:
	वापस err;
पूर्ण

पूर्णांक advance_dma_data(काष्ठा rxe_dma_info *dma, अचिन्हित पूर्णांक length)
अणु
	काष्ठा rxe_sge		*sge	= &dma->sge[dma->cur_sge];
	पूर्णांक			offset	= dma->sge_offset;
	पूर्णांक			resid	= dma->resid;

	जबतक (length) अणु
		अचिन्हित पूर्णांक bytes;

		अगर (offset >= sge->length) अणु
			sge++;
			dma->cur_sge++;
			offset = 0;
			अगर (dma->cur_sge >= dma->num_sge)
				वापस -ENOSPC;
		पूर्ण

		bytes = length;

		अगर (bytes > sge->length - offset)
			bytes = sge->length - offset;

		offset	+= bytes;
		resid	-= bytes;
		length	-= bytes;
	पूर्ण

	dma->sge_offset = offset;
	dma->resid	= resid;

	वापस 0;
पूर्ण

/* (1) find the mr corresponding to lkey/rkey
 *     depending on lookup_type
 * (2) verअगरy that the (qp) pd matches the mr pd
 * (3) verअगरy that the mr can support the requested access
 * (4) verअगरy that mr state is valid
 */
काष्ठा rxe_mr *lookup_mr(काष्ठा rxe_pd *pd, पूर्णांक access, u32 key,
			 क्रमागत lookup_type type)
अणु
	काष्ठा rxe_mr *mr;
	काष्ठा rxe_dev *rxe = to_rdev(pd->ibpd.device);
	पूर्णांक index = key >> 8;

	mr = rxe_pool_get_index(&rxe->mr_pool, index);
	अगर (!mr)
		वापस शून्य;

	अगर (unlikely((type == lookup_local && mr_lkey(mr) != key) ||
		     (type == lookup_remote && mr_rkey(mr) != key) ||
		     mr_pd(mr) != pd || (access && !(access & mr->access)) ||
		     mr->state != RXE_MR_STATE_VALID)) अणु
		rxe_drop_ref(mr);
		mr = शून्य;
	पूर्ण

	वापस mr;
पूर्ण
