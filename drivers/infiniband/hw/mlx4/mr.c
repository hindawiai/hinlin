<शैली गुरु>
/*
 * Copyright (c) 2007 Cisco Systems, Inc. All rights reserved.
 * Copyright (c) 2007, 2008 Mellanox Technologies. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
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
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश <linux/slab.h>
#समावेश <rdma/ib_user_verbs.h>

#समावेश "mlx4_ib.h"

अटल u32 convert_access(पूर्णांक acc)
अणु
	वापस (acc & IB_ACCESS_REMOTE_ATOMIC ? MLX4_PERM_ATOMIC       : 0) |
	       (acc & IB_ACCESS_REMOTE_WRITE  ? MLX4_PERM_REMOTE_WRITE : 0) |
	       (acc & IB_ACCESS_REMOTE_READ   ? MLX4_PERM_REMOTE_READ  : 0) |
	       (acc & IB_ACCESS_LOCAL_WRITE   ? MLX4_PERM_LOCAL_WRITE  : 0) |
	       (acc & IB_ACCESS_MW_BIND	      ? MLX4_PERM_BIND_MW      : 0) |
	       MLX4_PERM_LOCAL_READ;
पूर्ण

अटल क्रमागत mlx4_mw_type to_mlx4_type(क्रमागत ib_mw_type type)
अणु
	चयन (type) अणु
	हाल IB_MW_TYPE_1:	वापस MLX4_MW_TYPE_1;
	हाल IB_MW_TYPE_2:	वापस MLX4_MW_TYPE_2;
	शेष:		वापस -1;
	पूर्ण
पूर्ण

काष्ठा ib_mr *mlx4_ib_get_dma_mr(काष्ठा ib_pd *pd, पूर्णांक acc)
अणु
	काष्ठा mlx4_ib_mr *mr;
	पूर्णांक err;

	mr = kzalloc(माप(*mr), GFP_KERNEL);
	अगर (!mr)
		वापस ERR_PTR(-ENOMEM);

	err = mlx4_mr_alloc(to_mdev(pd->device)->dev, to_mpd(pd)->pdn, 0,
			    ~0ull, convert_access(acc), 0, 0, &mr->mmr);
	अगर (err)
		जाओ err_मुक्त;

	err = mlx4_mr_enable(to_mdev(pd->device)->dev, &mr->mmr);
	अगर (err)
		जाओ err_mr;

	mr->ibmr.rkey = mr->ibmr.lkey = mr->mmr.key;
	mr->umem = शून्य;

	वापस &mr->ibmr;

err_mr:
	(व्योम) mlx4_mr_मुक्त(to_mdev(pd->device)->dev, &mr->mmr);

err_मुक्त:
	kमुक्त(mr);

	वापस ERR_PTR(err);
पूर्ण

क्रमागत अणु
	MLX4_MAX_MTT_SHIFT = 31
पूर्ण;

अटल पूर्णांक mlx4_ib_umem_ग_लिखो_mtt_block(काष्ठा mlx4_ib_dev *dev,
					काष्ठा mlx4_mtt *mtt,
					u64 mtt_size, u64 mtt_shअगरt, u64 len,
					u64 cur_start_addr, u64 *pages,
					पूर्णांक *start_index, पूर्णांक *npages)
अणु
	u64 cur_end_addr = cur_start_addr + len;
	u64 cur_end_addr_aligned = 0;
	u64 mtt_entries;
	पूर्णांक err = 0;
	पूर्णांक k;

	len += (cur_start_addr & (mtt_size - 1ULL));
	cur_end_addr_aligned = round_up(cur_end_addr, mtt_size);
	len += (cur_end_addr_aligned - cur_end_addr);
	अगर (len & (mtt_size - 1ULL)) अणु
		pr_warn("write_block: len %llx is not aligned to mtt_size %llx\n",
			len, mtt_size);
		वापस -EINVAL;
	पूर्ण

	mtt_entries = (len >> mtt_shअगरt);

	/*
	 * Align the MTT start address to the mtt_size.
	 * Required to handle हालs when the MR starts in the middle of an MTT
	 * record. Was not required in old code since the physical addresses
	 * provided by the dma subप्रणाली were page aligned, which was also the
	 * MTT size.
	 */
	cur_start_addr = round_करोwn(cur_start_addr, mtt_size);
	/* A new block is started ... */
	क्रम (k = 0; k < mtt_entries; ++k) अणु
		pages[*npages] = cur_start_addr + (mtt_size * k);
		(*npages)++;
		/*
		 * Be मित्रly to mlx4_ग_लिखो_mtt() and pass it chunks of
		 * appropriate size.
		 */
		अगर (*npages == PAGE_SIZE / माप(u64)) अणु
			err = mlx4_ग_लिखो_mtt(dev->dev, mtt, *start_index,
					     *npages, pages);
			अगर (err)
				वापस err;

			(*start_index) += *npages;
			*npages = 0;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत u64 alignment_of(u64 ptr)
अणु
	वापस ilog2(ptr & (~(ptr - 1)));
पूर्ण

अटल पूर्णांक mlx4_ib_umem_calc_block_mtt(u64 next_block_start,
				       u64 current_block_end,
				       u64 block_shअगरt)
अणु
	/* Check whether the alignment of the new block is aligned as well as
	 * the previous block.
	 * Block address must start with zeros till size of entity_size.
	 */
	अगर ((next_block_start & ((1ULL << block_shअगरt) - 1ULL)) != 0)
		/*
		 * It is not as well aligned as the previous block-reduce the
		 * mtt size accordingly. Here we take the last right bit which
		 * is 1.
		 */
		block_shअगरt = alignment_of(next_block_start);

	/*
	 * Check whether the alignment of the end of previous block - is it
	 * aligned as well as the start of the block
	 */
	अगर (((current_block_end) & ((1ULL << block_shअगरt) - 1ULL)) != 0)
		/*
		 * It is not as well aligned as the start of the block -
		 * reduce the mtt size accordingly.
		 */
		block_shअगरt = alignment_of(current_block_end);

	वापस block_shअगरt;
पूर्ण

पूर्णांक mlx4_ib_umem_ग_लिखो_mtt(काष्ठा mlx4_ib_dev *dev, काष्ठा mlx4_mtt *mtt,
			   काष्ठा ib_umem *umem)
अणु
	u64 *pages;
	u64 len = 0;
	पूर्णांक err = 0;
	u64 mtt_size;
	u64 cur_start_addr = 0;
	u64 mtt_shअगरt;
	पूर्णांक start_index = 0;
	पूर्णांक npages = 0;
	काष्ठा scatterlist *sg;
	पूर्णांक i;

	pages = (u64 *) __get_मुक्त_page(GFP_KERNEL);
	अगर (!pages)
		वापस -ENOMEM;

	mtt_shअगरt = mtt->page_shअगरt;
	mtt_size = 1ULL << mtt_shअगरt;

	क्रम_each_sg(umem->sg_head.sgl, sg, umem->nmap, i) अणु
		अगर (cur_start_addr + len == sg_dma_address(sg)) अणु
			/* still the same block */
			len += sg_dma_len(sg);
			जारी;
		पूर्ण
		/*
		 * A new block is started ...
		 * If len is malaligned, ग_लिखो an extra mtt entry to cover the
		 * misaligned area (round up the भागision)
		 */
		err = mlx4_ib_umem_ग_लिखो_mtt_block(dev, mtt, mtt_size,
						   mtt_shअगरt, len,
						   cur_start_addr,
						   pages, &start_index,
						   &npages);
		अगर (err)
			जाओ out;

		cur_start_addr = sg_dma_address(sg);
		len = sg_dma_len(sg);
	पूर्ण

	/* Handle the last block */
	अगर (len > 0) अणु
		/*
		 * If len is malaligned, ग_लिखो an extra mtt entry to cover
		 * the misaligned area (round up the भागision)
		 */
		err = mlx4_ib_umem_ग_लिखो_mtt_block(dev, mtt, mtt_size,
						   mtt_shअगरt, len,
						   cur_start_addr, pages,
						   &start_index, &npages);
		अगर (err)
			जाओ out;
	पूर्ण

	अगर (npages)
		err = mlx4_ग_लिखो_mtt(dev->dev, mtt, start_index, npages, pages);

out:
	मुक्त_page((अचिन्हित दीर्घ) pages);
	वापस err;
पूर्ण

/*
 * Calculate optimal mtt size based on contiguous pages.
 * Function will वापस also the number of pages that are not aligned to the
 * calculated mtt_size to be added to total number of pages. For that we should
 * check the first chunk length & last chunk length and अगर not aligned to
 * mtt_size we should increment the non_aligned_pages number. All chunks in the
 * middle alपढ़ोy handled as part of mtt shअगरt calculation क्रम both their start
 * & end addresses.
 */
पूर्णांक mlx4_ib_umem_calc_optimal_mtt_size(काष्ठा ib_umem *umem, u64 start_va,
				       पूर्णांक *num_of_mtts)
अणु
	u64 block_shअगरt = MLX4_MAX_MTT_SHIFT;
	u64 min_shअगरt = PAGE_SHIFT;
	u64 last_block_aligned_end = 0;
	u64 current_block_start = 0;
	u64 first_block_start = 0;
	u64 current_block_len = 0;
	u64 last_block_end = 0;
	काष्ठा scatterlist *sg;
	u64 current_block_end;
	u64 misalignment_bits;
	u64 next_block_start;
	u64 total_len = 0;
	पूर्णांक i;

	*num_of_mtts = ib_umem_num_dma_blocks(umem, PAGE_SIZE);

	क्रम_each_sg(umem->sg_head.sgl, sg, umem->nmap, i) अणु
		/*
		 * Initialization - save the first chunk start as the
		 * current_block_start - block means contiguous pages.
		 */
		अगर (current_block_len == 0 && current_block_start == 0) अणु
			current_block_start = sg_dma_address(sg);
			first_block_start = current_block_start;
			/*
			 * Find the bits that are dअगरferent between the physical
			 * address and the भव address क्रम the start of the
			 * MR.
			 * umem_get aligned the start_va to a page boundary.
			 * Thereक्रमe, we need to align the start va to the same
			 * boundary.
			 * misalignment_bits is needed to handle the  हाल of a
			 * single memory region. In this हाल, the rest of the
			 * logic will not reduce the block size.  If we use a
			 * block size which is bigger than the alignment of the
			 * misalignment bits, we might use the भव page
			 * number instead of the physical page number, resulting
			 * in access to the wrong data.
			 */
			misalignment_bits =
				(start_va & (~(((u64)(PAGE_SIZE)) - 1ULL))) ^
				current_block_start;
			block_shअगरt = min(alignment_of(misalignment_bits),
					  block_shअगरt);
		पूर्ण

		/*
		 * Go over the scatter entries and check अगर they जारी the
		 * previous scatter entry.
		 */
		next_block_start = sg_dma_address(sg);
		current_block_end = current_block_start	+ current_block_len;
		/* If we have a split (non-contig.) between two blocks */
		अगर (current_block_end != next_block_start) अणु
			block_shअगरt = mlx4_ib_umem_calc_block_mtt
					(next_block_start,
					 current_block_end,
					 block_shअगरt);

			/*
			 * If we reached the minimum shअगरt क्रम 4k page we stop
			 * the loop.
			 */
			अगर (block_shअगरt <= min_shअगरt)
				जाओ end;

			/*
			 * If not saved yet we are in first block - we save the
			 * length of first block to calculate the
			 * non_aligned_pages number at the end.
			 */
			total_len += current_block_len;

			/* Start a new block */
			current_block_start = next_block_start;
			current_block_len = sg_dma_len(sg);
			जारी;
		पूर्ण
		/* The scatter entry is another part of the current block,
		 * increase the block size.
		 * An entry in the scatter can be larger than 4k (page) as of
		 * dma mapping which merge some blocks together.
		 */
		current_block_len += sg_dma_len(sg);
	पूर्ण

	/* Account क्रम the last block in the total len */
	total_len += current_block_len;
	/* Add to the first block the misalignment that it suffers from. */
	total_len += (first_block_start & ((1ULL << block_shअगरt) - 1ULL));
	last_block_end = current_block_start + current_block_len;
	last_block_aligned_end = round_up(last_block_end, 1ULL << block_shअगरt);
	total_len += (last_block_aligned_end - last_block_end);

	अगर (total_len & ((1ULL << block_shअगरt) - 1ULL))
		pr_warn("misaligned total length detected (%llu, %llu)!",
			total_len, block_shअगरt);

	*num_of_mtts = total_len >> block_shअगरt;
end:
	अगर (block_shअगरt < min_shअगरt) अणु
		/*
		 * If shअगरt is less than the min we set a warning and वापस the
		 * min shअगरt.
		 */
		pr_warn("umem_calc_optimal_mtt_size - unexpected shift %lld\n", block_shअगरt);

		block_shअगरt = min_shअगरt;
	पूर्ण
	वापस block_shअगरt;
पूर्ण

अटल काष्ठा ib_umem *mlx4_get_umem_mr(काष्ठा ib_device *device, u64 start,
					u64 length, पूर्णांक access_flags)
अणु
	/*
	 * Force रेजिस्टरing the memory as writable अगर the underlying pages
	 * are writable.  This is so rereg can change the access permissions
	 * from पढ़ोable to writable without having to run through ib_umem_get
	 * again
	 */
	अगर (!ib_access_writable(access_flags)) अणु
		अचिन्हित दीर्घ untagged_start = untagged_addr(start);
		काष्ठा vm_area_काष्ठा *vma;

		mmap_पढ़ो_lock(current->mm);
		/*
		 * FIXME: Ideally this would iterate over all the vmas that
		 * cover the memory, but क्रम now it requires a single vma to
		 * entirely cover the MR to support RO mappings.
		 */
		vma = find_vma(current->mm, untagged_start);
		अगर (vma && vma->vm_end >= untagged_start + length &&
		    vma->vm_start <= untagged_start) अणु
			अगर (vma->vm_flags & VM_WRITE)
				access_flags |= IB_ACCESS_LOCAL_WRITE;
		पूर्ण अन्यथा अणु
			access_flags |= IB_ACCESS_LOCAL_WRITE;
		पूर्ण

		mmap_पढ़ो_unlock(current->mm);
	पूर्ण

	वापस ib_umem_get(device, start, length, access_flags);
पूर्ण

काष्ठा ib_mr *mlx4_ib_reg_user_mr(काष्ठा ib_pd *pd, u64 start, u64 length,
				  u64 virt_addr, पूर्णांक access_flags,
				  काष्ठा ib_udata *udata)
अणु
	काष्ठा mlx4_ib_dev *dev = to_mdev(pd->device);
	काष्ठा mlx4_ib_mr *mr;
	पूर्णांक shअगरt;
	पूर्णांक err;
	पूर्णांक n;

	mr = kzalloc(माप(*mr), GFP_KERNEL);
	अगर (!mr)
		वापस ERR_PTR(-ENOMEM);

	mr->umem = mlx4_get_umem_mr(pd->device, start, length, access_flags);
	अगर (IS_ERR(mr->umem)) अणु
		err = PTR_ERR(mr->umem);
		जाओ err_मुक्त;
	पूर्ण

	shअगरt = mlx4_ib_umem_calc_optimal_mtt_size(mr->umem, start, &n);

	err = mlx4_mr_alloc(dev->dev, to_mpd(pd)->pdn, virt_addr, length,
			    convert_access(access_flags), n, shअगरt, &mr->mmr);
	अगर (err)
		जाओ err_umem;

	err = mlx4_ib_umem_ग_लिखो_mtt(dev, &mr->mmr.mtt, mr->umem);
	अगर (err)
		जाओ err_mr;

	err = mlx4_mr_enable(dev->dev, &mr->mmr);
	अगर (err)
		जाओ err_mr;

	mr->ibmr.rkey = mr->ibmr.lkey = mr->mmr.key;
	mr->ibmr.length = length;
	mr->ibmr.page_size = 1U << shअगरt;

	वापस &mr->ibmr;

err_mr:
	(व्योम) mlx4_mr_मुक्त(to_mdev(pd->device)->dev, &mr->mmr);

err_umem:
	ib_umem_release(mr->umem);

err_मुक्त:
	kमुक्त(mr);

	वापस ERR_PTR(err);
पूर्ण

काष्ठा ib_mr *mlx4_ib_rereg_user_mr(काष्ठा ib_mr *mr, पूर्णांक flags, u64 start,
				    u64 length, u64 virt_addr,
				    पूर्णांक mr_access_flags, काष्ठा ib_pd *pd,
				    काष्ठा ib_udata *udata)
अणु
	काष्ठा mlx4_ib_dev *dev = to_mdev(mr->device);
	काष्ठा mlx4_ib_mr *mmr = to_mmr(mr);
	काष्ठा mlx4_mpt_entry *mpt_entry;
	काष्ठा mlx4_mpt_entry **pmpt_entry = &mpt_entry;
	पूर्णांक err;

	/* Since we synchronize this call and mlx4_ib_dereg_mr via uverbs,
	 * we assume that the calls can't run concurrently. Otherwise, a
	 * race exists.
	 */
	err =  mlx4_mr_hw_get_mpt(dev->dev, &mmr->mmr, &pmpt_entry);
	अगर (err)
		वापस ERR_PTR(err);

	अगर (flags & IB_MR_REREG_PD) अणु
		err = mlx4_mr_hw_change_pd(dev->dev, *pmpt_entry,
					   to_mpd(pd)->pdn);

		अगर (err)
			जाओ release_mpt_entry;
	पूर्ण

	अगर (flags & IB_MR_REREG_ACCESS) अणु
		अगर (ib_access_writable(mr_access_flags) &&
		    !mmr->umem->writable) अणु
			err = -EPERM;
			जाओ release_mpt_entry;
		पूर्ण

		err = mlx4_mr_hw_change_access(dev->dev, *pmpt_entry,
					       convert_access(mr_access_flags));

		अगर (err)
			जाओ release_mpt_entry;
	पूर्ण

	अगर (flags & IB_MR_REREG_TRANS) अणु
		पूर्णांक shअगरt;
		पूर्णांक n;

		mlx4_mr_rereg_mem_cleanup(dev->dev, &mmr->mmr);
		ib_umem_release(mmr->umem);
		mmr->umem = mlx4_get_umem_mr(mr->device, start, length,
					     mr_access_flags);
		अगर (IS_ERR(mmr->umem)) अणु
			err = PTR_ERR(mmr->umem);
			/* Prevent mlx4_ib_dereg_mr from मुक्त'ing invalid poपूर्णांकer */
			mmr->umem = शून्य;
			जाओ release_mpt_entry;
		पूर्ण
		n = ib_umem_num_dma_blocks(mmr->umem, PAGE_SIZE);
		shअगरt = PAGE_SHIFT;

		err = mlx4_mr_rereg_mem_ग_लिखो(dev->dev, &mmr->mmr,
					      virt_addr, length, n, shअगरt,
					      *pmpt_entry);
		अगर (err) अणु
			ib_umem_release(mmr->umem);
			जाओ release_mpt_entry;
		पूर्ण
		mmr->mmr.iova       = virt_addr;
		mmr->mmr.size       = length;

		err = mlx4_ib_umem_ग_लिखो_mtt(dev, &mmr->mmr.mtt, mmr->umem);
		अगर (err) अणु
			mlx4_mr_rereg_mem_cleanup(dev->dev, &mmr->mmr);
			ib_umem_release(mmr->umem);
			जाओ release_mpt_entry;
		पूर्ण
	पूर्ण

	/* If we couldn't transfer the MR to the HCA, just remember to
	 * वापस a failure. But dereg_mr will मुक्त the resources.
	 */
	err = mlx4_mr_hw_ग_लिखो_mpt(dev->dev, &mmr->mmr, pmpt_entry);
	अगर (!err && flags & IB_MR_REREG_ACCESS)
		mmr->mmr.access = mr_access_flags;

release_mpt_entry:
	mlx4_mr_hw_put_mpt(dev->dev, pmpt_entry);
	अगर (err)
		वापस ERR_PTR(err);
	वापस शून्य;
पूर्ण

अटल पूर्णांक
mlx4_alloc_priv_pages(काष्ठा ib_device *device,
		      काष्ठा mlx4_ib_mr *mr,
		      पूर्णांक max_pages)
अणु
	पूर्णांक ret;

	/* Ensure that size is aligned to DMA cacheline
	 * requirements.
	 * max_pages is limited to MLX4_MAX_FAST_REG_PAGES
	 * so page_map_size will never cross PAGE_SIZE.
	 */
	mr->page_map_size = roundup(max_pages * माप(u64),
				    MLX4_MR_PAGES_ALIGN);

	/* Prevent cross page boundary allocation. */
	mr->pages = (__be64 *)get_zeroed_page(GFP_KERNEL);
	अगर (!mr->pages)
		वापस -ENOMEM;

	mr->page_map = dma_map_single(device->dev.parent, mr->pages,
				      mr->page_map_size, DMA_TO_DEVICE);

	अगर (dma_mapping_error(device->dev.parent, mr->page_map)) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	वापस 0;

err:
	मुक्त_page((अचिन्हित दीर्घ)mr->pages);
	वापस ret;
पूर्ण

अटल व्योम
mlx4_मुक्त_priv_pages(काष्ठा mlx4_ib_mr *mr)
अणु
	अगर (mr->pages) अणु
		काष्ठा ib_device *device = mr->ibmr.device;

		dma_unmap_single(device->dev.parent, mr->page_map,
				 mr->page_map_size, DMA_TO_DEVICE);
		मुक्त_page((अचिन्हित दीर्घ)mr->pages);
		mr->pages = शून्य;
	पूर्ण
पूर्ण

पूर्णांक mlx4_ib_dereg_mr(काष्ठा ib_mr *ibmr, काष्ठा ib_udata *udata)
अणु
	काष्ठा mlx4_ib_mr *mr = to_mmr(ibmr);
	पूर्णांक ret;

	mlx4_मुक्त_priv_pages(mr);

	ret = mlx4_mr_मुक्त(to_mdev(ibmr->device)->dev, &mr->mmr);
	अगर (ret)
		वापस ret;
	अगर (mr->umem)
		ib_umem_release(mr->umem);
	kमुक्त(mr);

	वापस 0;
पूर्ण

पूर्णांक mlx4_ib_alloc_mw(काष्ठा ib_mw *ibmw, काष्ठा ib_udata *udata)
अणु
	काष्ठा mlx4_ib_dev *dev = to_mdev(ibmw->device);
	काष्ठा mlx4_ib_mw *mw = to_mmw(ibmw);
	पूर्णांक err;

	err = mlx4_mw_alloc(dev->dev, to_mpd(ibmw->pd)->pdn,
			    to_mlx4_type(ibmw->type), &mw->mmw);
	अगर (err)
		वापस err;

	err = mlx4_mw_enable(dev->dev, &mw->mmw);
	अगर (err)
		जाओ err_mw;

	ibmw->rkey = mw->mmw.key;
	वापस 0;

err_mw:
	mlx4_mw_मुक्त(dev->dev, &mw->mmw);
	वापस err;
पूर्ण

पूर्णांक mlx4_ib_dealloc_mw(काष्ठा ib_mw *ibmw)
अणु
	काष्ठा mlx4_ib_mw *mw = to_mmw(ibmw);

	mlx4_mw_मुक्त(to_mdev(ibmw->device)->dev, &mw->mmw);
	वापस 0;
पूर्ण

काष्ठा ib_mr *mlx4_ib_alloc_mr(काष्ठा ib_pd *pd, क्रमागत ib_mr_type mr_type,
			       u32 max_num_sg)
अणु
	काष्ठा mlx4_ib_dev *dev = to_mdev(pd->device);
	काष्ठा mlx4_ib_mr *mr;
	पूर्णांक err;

	अगर (mr_type != IB_MR_TYPE_MEM_REG ||
	    max_num_sg > MLX4_MAX_FAST_REG_PAGES)
		वापस ERR_PTR(-EINVAL);

	mr = kzalloc(माप(*mr), GFP_KERNEL);
	अगर (!mr)
		वापस ERR_PTR(-ENOMEM);

	err = mlx4_mr_alloc(dev->dev, to_mpd(pd)->pdn, 0, 0, 0,
			    max_num_sg, 0, &mr->mmr);
	अगर (err)
		जाओ err_मुक्त;

	err = mlx4_alloc_priv_pages(pd->device, mr, max_num_sg);
	अगर (err)
		जाओ err_मुक्त_mr;

	mr->max_pages = max_num_sg;
	err = mlx4_mr_enable(dev->dev, &mr->mmr);
	अगर (err)
		जाओ err_मुक्त_pl;

	mr->ibmr.rkey = mr->ibmr.lkey = mr->mmr.key;
	mr->umem = शून्य;

	वापस &mr->ibmr;

err_मुक्त_pl:
	mr->ibmr.device = pd->device;
	mlx4_मुक्त_priv_pages(mr);
err_मुक्त_mr:
	(व्योम) mlx4_mr_मुक्त(dev->dev, &mr->mmr);
err_मुक्त:
	kमुक्त(mr);
	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक mlx4_set_page(काष्ठा ib_mr *ibmr, u64 addr)
अणु
	काष्ठा mlx4_ib_mr *mr = to_mmr(ibmr);

	अगर (unlikely(mr->npages == mr->max_pages))
		वापस -ENOMEM;

	mr->pages[mr->npages++] = cpu_to_be64(addr | MLX4_MTT_FLAG_PRESENT);

	वापस 0;
पूर्ण

पूर्णांक mlx4_ib_map_mr_sg(काष्ठा ib_mr *ibmr, काष्ठा scatterlist *sg, पूर्णांक sg_nents,
		      अचिन्हित पूर्णांक *sg_offset)
अणु
	काष्ठा mlx4_ib_mr *mr = to_mmr(ibmr);
	पूर्णांक rc;

	mr->npages = 0;

	ib_dma_sync_single_क्रम_cpu(ibmr->device, mr->page_map,
				   mr->page_map_size, DMA_TO_DEVICE);

	rc = ib_sg_to_pages(ibmr, sg, sg_nents, sg_offset, mlx4_set_page);

	ib_dma_sync_single_क्रम_device(ibmr->device, mr->page_map,
				      mr->page_map_size, DMA_TO_DEVICE);

	वापस rc;
पूर्ण
