<शैली गुरु>
/*
 * Copyright (c) 2004 Topspin Communications.  All rights reserved.
 * Copyright (c) 2005 Mellanox Technologies. All rights reserved.
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
#समावेश <linux/त्रुटिसं.स>

#समावेश "mthca_dev.h"
#समावेश "mthca_cmd.h"
#समावेश "mthca_memfree.h"

काष्ठा mthca_mtt अणु
	काष्ठा mthca_buddy *buddy;
	पूर्णांक                 order;
	u32                 first_seg;
पूर्ण;

/*
 * Must be packed because mtt_seg is 64 bits but only aligned to 32 bits.
 */
काष्ठा mthca_mpt_entry अणु
	__be32 flags;
	__be32 page_size;
	__be32 key;
	__be32 pd;
	__be64 start;
	__be64 length;
	__be32 lkey;
	__be32 winकरोw_count;
	__be32 winकरोw_count_limit;
	__be64 mtt_seg;
	__be32 mtt_sz;		/* Arbel only */
	u32    reserved[2];
पूर्ण __packed;

#घोषणा MTHCA_MPT_FLAG_SW_OWNS       (0xfUL << 28)
#घोषणा MTHCA_MPT_FLAG_MIO           (1 << 17)
#घोषणा MTHCA_MPT_FLAG_BIND_ENABLE   (1 << 15)
#घोषणा MTHCA_MPT_FLAG_PHYSICAL      (1 <<  9)
#घोषणा MTHCA_MPT_FLAG_REGION        (1 <<  8)

#घोषणा MTHCA_MTT_FLAG_PRESENT       1

#घोषणा MTHCA_MPT_STATUS_SW 0xF0
#घोषणा MTHCA_MPT_STATUS_HW 0x00

#घोषणा SINAI_FMR_KEY_INC 0x1000000

/*
 * Buddy allocator क्रम MTT segments (currently not very efficient
 * since it करोesn't keep a मुक्त list and just searches linearly
 * through the biपंचांगaps)
 */

अटल u32 mthca_buddy_alloc(काष्ठा mthca_buddy *buddy, पूर्णांक order)
अणु
	पूर्णांक o;
	पूर्णांक m;
	u32 seg;

	spin_lock(&buddy->lock);

	क्रम (o = order; o <= buddy->max_order; ++o)
		अगर (buddy->num_मुक्त[o]) अणु
			m = 1 << (buddy->max_order - o);
			seg = find_first_bit(buddy->bits[o], m);
			अगर (seg < m)
				जाओ found;
		पूर्ण

	spin_unlock(&buddy->lock);
	वापस -1;

 found:
	clear_bit(seg, buddy->bits[o]);
	--buddy->num_मुक्त[o];

	जबतक (o > order) अणु
		--o;
		seg <<= 1;
		set_bit(seg ^ 1, buddy->bits[o]);
		++buddy->num_मुक्त[o];
	पूर्ण

	spin_unlock(&buddy->lock);

	seg <<= order;

	वापस seg;
पूर्ण

अटल व्योम mthca_buddy_मुक्त(काष्ठा mthca_buddy *buddy, u32 seg, पूर्णांक order)
अणु
	seg >>= order;

	spin_lock(&buddy->lock);

	जबतक (test_bit(seg ^ 1, buddy->bits[order])) अणु
		clear_bit(seg ^ 1, buddy->bits[order]);
		--buddy->num_मुक्त[order];
		seg >>= 1;
		++order;
	पूर्ण

	set_bit(seg, buddy->bits[order]);
	++buddy->num_मुक्त[order];

	spin_unlock(&buddy->lock);
पूर्ण

अटल पूर्णांक mthca_buddy_init(काष्ठा mthca_buddy *buddy, पूर्णांक max_order)
अणु
	पूर्णांक i, s;

	buddy->max_order = max_order;
	spin_lock_init(&buddy->lock);

	buddy->bits = kसुस्मृति(buddy->max_order + 1, माप(दीर्घ *),
			      GFP_KERNEL);
	buddy->num_मुक्त = kसुस्मृति((buddy->max_order + 1), माप *buddy->num_मुक्त,
				  GFP_KERNEL);
	अगर (!buddy->bits || !buddy->num_मुक्त)
		जाओ err_out;

	क्रम (i = 0; i <= buddy->max_order; ++i) अणु
		s = BITS_TO_LONGS(1 << (buddy->max_order - i));
		buddy->bits[i] = kदो_स्मृति_array(s, माप(दीर्घ), GFP_KERNEL);
		अगर (!buddy->bits[i])
			जाओ err_out_मुक्त;
		biपंचांगap_zero(buddy->bits[i],
			    1 << (buddy->max_order - i));
	पूर्ण

	set_bit(0, buddy->bits[buddy->max_order]);
	buddy->num_मुक्त[buddy->max_order] = 1;

	वापस 0;

err_out_मुक्त:
	क्रम (i = 0; i <= buddy->max_order; ++i)
		kमुक्त(buddy->bits[i]);

err_out:
	kमुक्त(buddy->bits);
	kमुक्त(buddy->num_मुक्त);

	वापस -ENOMEM;
पूर्ण

अटल व्योम mthca_buddy_cleanup(काष्ठा mthca_buddy *buddy)
अणु
	पूर्णांक i;

	क्रम (i = 0; i <= buddy->max_order; ++i)
		kमुक्त(buddy->bits[i]);

	kमुक्त(buddy->bits);
	kमुक्त(buddy->num_मुक्त);
पूर्ण

अटल u32 mthca_alloc_mtt_range(काष्ठा mthca_dev *dev, पूर्णांक order,
				 काष्ठा mthca_buddy *buddy)
अणु
	u32 seg = mthca_buddy_alloc(buddy, order);

	अगर (seg == -1)
		वापस -1;

	अगर (mthca_is_memमुक्त(dev))
		अगर (mthca_table_get_range(dev, dev->mr_table.mtt_table, seg,
					  seg + (1 << order) - 1)) अणु
			mthca_buddy_मुक्त(buddy, seg, order);
			seg = -1;
		पूर्ण

	वापस seg;
पूर्ण

अटल काष्ठा mthca_mtt *__mthca_alloc_mtt(काष्ठा mthca_dev *dev, पूर्णांक size,
					   काष्ठा mthca_buddy *buddy)
अणु
	काष्ठा mthca_mtt *mtt;
	पूर्णांक i;

	अगर (size <= 0)
		वापस ERR_PTR(-EINVAL);

	mtt = kदो_स्मृति(माप *mtt, GFP_KERNEL);
	अगर (!mtt)
		वापस ERR_PTR(-ENOMEM);

	mtt->buddy = buddy;
	mtt->order = 0;
	क्रम (i = dev->limits.mtt_seg_size / 8; i < size; i <<= 1)
		++mtt->order;

	mtt->first_seg = mthca_alloc_mtt_range(dev, mtt->order, buddy);
	अगर (mtt->first_seg == -1) अणु
		kमुक्त(mtt);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	वापस mtt;
पूर्ण

काष्ठा mthca_mtt *mthca_alloc_mtt(काष्ठा mthca_dev *dev, पूर्णांक size)
अणु
	वापस __mthca_alloc_mtt(dev, size, &dev->mr_table.mtt_buddy);
पूर्ण

व्योम mthca_मुक्त_mtt(काष्ठा mthca_dev *dev, काष्ठा mthca_mtt *mtt)
अणु
	अगर (!mtt)
		वापस;

	mthca_buddy_मुक्त(mtt->buddy, mtt->first_seg, mtt->order);

	mthca_table_put_range(dev, dev->mr_table.mtt_table,
			      mtt->first_seg,
			      mtt->first_seg + (1 << mtt->order) - 1);

	kमुक्त(mtt);
पूर्ण

अटल पूर्णांक __mthca_ग_लिखो_mtt(काष्ठा mthca_dev *dev, काष्ठा mthca_mtt *mtt,
			     पूर्णांक start_index, u64 *buffer_list, पूर्णांक list_len)
अणु
	काष्ठा mthca_mailbox *mailbox;
	__be64 *mtt_entry;
	पूर्णांक err = 0;
	पूर्णांक i;

	mailbox = mthca_alloc_mailbox(dev, GFP_KERNEL);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);
	mtt_entry = mailbox->buf;

	जबतक (list_len > 0) अणु
		mtt_entry[0] = cpu_to_be64(dev->mr_table.mtt_base +
					   mtt->first_seg * dev->limits.mtt_seg_size +
					   start_index * 8);
		mtt_entry[1] = 0;
		क्रम (i = 0; i < list_len && i < MTHCA_MAILBOX_SIZE / 8 - 2; ++i)
			mtt_entry[i + 2] = cpu_to_be64(buffer_list[i] |
						       MTHCA_MTT_FLAG_PRESENT);

		/*
		 * If we have an odd number of entries to ग_लिखो, add
		 * one more dummy entry क्रम firmware efficiency.
		 */
		अगर (i & 1)
			mtt_entry[i + 2] = 0;

		err = mthca_WRITE_MTT(dev, mailbox, (i + 1) & ~1);
		अगर (err) अणु
			mthca_warn(dev, "WRITE_MTT failed (%d)\n", err);
			जाओ out;
		पूर्ण

		list_len    -= i;
		start_index += i;
		buffer_list += i;
	पूर्ण

out:
	mthca_मुक्त_mailbox(dev, mailbox);
	वापस err;
पूर्ण

पूर्णांक mthca_ग_लिखो_mtt_size(काष्ठा mthca_dev *dev)
अणु
	अगर (dev->mr_table.fmr_mtt_buddy != &dev->mr_table.mtt_buddy ||
	    !(dev->mthca_flags & MTHCA_FLAG_FMR))
		/*
		 * Be मित्रly to WRITE_MTT command
		 * and leave two empty slots क्रम the
		 * index and reserved fields of the
		 * mailbox.
		 */
		वापस PAGE_SIZE / माप (u64) - 2;

	/* For Arbel, all MTTs must fit in the same page. */
	वापस mthca_is_memमुक्त(dev) ? (PAGE_SIZE / माप (u64)) : 0x7ffffff;
पूर्ण

अटल व्योम mthca_tavor_ग_लिखो_mtt_seg(काष्ठा mthca_dev *dev,
				      काष्ठा mthca_mtt *mtt, पूर्णांक start_index,
				      u64 *buffer_list, पूर्णांक list_len)
अणु
	u64 __iomem *mtts;
	पूर्णांक i;

	mtts = dev->mr_table.tavor_fmr.mtt_base + mtt->first_seg * dev->limits.mtt_seg_size +
		start_index * माप (u64);
	क्रम (i = 0; i < list_len; ++i)
		mthca_ग_लिखो64_raw(cpu_to_be64(buffer_list[i] | MTHCA_MTT_FLAG_PRESENT),
				  mtts + i);
पूर्ण

अटल व्योम mthca_arbel_ग_लिखो_mtt_seg(काष्ठा mthca_dev *dev,
				      काष्ठा mthca_mtt *mtt, पूर्णांक start_index,
				      u64 *buffer_list, पूर्णांक list_len)
अणु
	__be64 *mtts;
	dma_addr_t dma_handle;
	पूर्णांक i;
	पूर्णांक s = start_index * माप (u64);

	/* For Arbel, all MTTs must fit in the same page. */
	BUG_ON(s / PAGE_SIZE != (s + list_len * माप(u64) - 1) / PAGE_SIZE);
	/* Require full segments */
	BUG_ON(s % dev->limits.mtt_seg_size);

	mtts = mthca_table_find(dev->mr_table.mtt_table, mtt->first_seg +
				s / dev->limits.mtt_seg_size, &dma_handle);

	BUG_ON(!mtts);

	dma_sync_single_क्रम_cpu(&dev->pdev->dev, dma_handle,
				list_len * माप (u64), DMA_TO_DEVICE);

	क्रम (i = 0; i < list_len; ++i)
		mtts[i] = cpu_to_be64(buffer_list[i] | MTHCA_MTT_FLAG_PRESENT);

	dma_sync_single_क्रम_device(&dev->pdev->dev, dma_handle,
				   list_len * माप (u64), DMA_TO_DEVICE);
पूर्ण

पूर्णांक mthca_ग_लिखो_mtt(काष्ठा mthca_dev *dev, काष्ठा mthca_mtt *mtt,
		    पूर्णांक start_index, u64 *buffer_list, पूर्णांक list_len)
अणु
	पूर्णांक size = mthca_ग_लिखो_mtt_size(dev);
	पूर्णांक chunk;

	अगर (dev->mr_table.fmr_mtt_buddy != &dev->mr_table.mtt_buddy ||
	    !(dev->mthca_flags & MTHCA_FLAG_FMR))
		वापस __mthca_ग_लिखो_mtt(dev, mtt, start_index, buffer_list, list_len);

	जबतक (list_len > 0) अणु
		chunk = min(size, list_len);
		अगर (mthca_is_memमुक्त(dev))
			mthca_arbel_ग_लिखो_mtt_seg(dev, mtt, start_index,
						  buffer_list, chunk);
		अन्यथा
			mthca_tavor_ग_लिखो_mtt_seg(dev, mtt, start_index,
						  buffer_list, chunk);

		list_len    -= chunk;
		start_index += chunk;
		buffer_list += chunk;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत u32 tavor_hw_index_to_key(u32 ind)
अणु
	वापस ind;
पूर्ण

अटल अंतरभूत u32 tavor_key_to_hw_index(u32 key)
अणु
	वापस key;
पूर्ण

अटल अंतरभूत u32 arbel_hw_index_to_key(u32 ind)
अणु
	वापस (ind >> 24) | (ind << 8);
पूर्ण

अटल अंतरभूत u32 arbel_key_to_hw_index(u32 key)
अणु
	वापस (key << 24) | (key >> 8);
पूर्ण

अटल अंतरभूत u32 hw_index_to_key(काष्ठा mthca_dev *dev, u32 ind)
अणु
	अगर (mthca_is_memमुक्त(dev))
		वापस arbel_hw_index_to_key(ind);
	अन्यथा
		वापस tavor_hw_index_to_key(ind);
पूर्ण

अटल अंतरभूत u32 key_to_hw_index(काष्ठा mthca_dev *dev, u32 key)
अणु
	अगर (mthca_is_memमुक्त(dev))
		वापस arbel_key_to_hw_index(key);
	अन्यथा
		वापस tavor_key_to_hw_index(key);
पूर्ण

अटल अंतरभूत u32 adjust_key(काष्ठा mthca_dev *dev, u32 key)
अणु
	अगर (dev->mthca_flags & MTHCA_FLAG_SINAI_OPT)
		वापस ((key << 20) & 0x800000) | (key & 0x7fffff);
	अन्यथा
		वापस key;
पूर्ण

पूर्णांक mthca_mr_alloc(काष्ठा mthca_dev *dev, u32 pd, पूर्णांक buffer_size_shअगरt,
		   u64 iova, u64 total_size, u32 access, काष्ठा mthca_mr *mr)
अणु
	काष्ठा mthca_mailbox *mailbox;
	काष्ठा mthca_mpt_entry *mpt_entry;
	u32 key;
	पूर्णांक i;
	पूर्णांक err;

	WARN_ON(buffer_size_shअगरt >= 32);

	key = mthca_alloc(&dev->mr_table.mpt_alloc);
	अगर (key == -1)
		वापस -ENOMEM;
	key = adjust_key(dev, key);
	mr->ibmr.rkey = mr->ibmr.lkey = hw_index_to_key(dev, key);

	अगर (mthca_is_memमुक्त(dev)) अणु
		err = mthca_table_get(dev, dev->mr_table.mpt_table, key);
		अगर (err)
			जाओ err_out_mpt_मुक्त;
	पूर्ण

	mailbox = mthca_alloc_mailbox(dev, GFP_KERNEL);
	अगर (IS_ERR(mailbox)) अणु
		err = PTR_ERR(mailbox);
		जाओ err_out_table;
	पूर्ण
	mpt_entry = mailbox->buf;

	mpt_entry->flags = cpu_to_be32(MTHCA_MPT_FLAG_SW_OWNS     |
				       MTHCA_MPT_FLAG_MIO         |
				       MTHCA_MPT_FLAG_REGION      |
				       access);
	अगर (!mr->mtt)
		mpt_entry->flags |= cpu_to_be32(MTHCA_MPT_FLAG_PHYSICAL);

	mpt_entry->page_size = cpu_to_be32(buffer_size_shअगरt - 12);
	mpt_entry->key       = cpu_to_be32(key);
	mpt_entry->pd        = cpu_to_be32(pd);
	mpt_entry->start     = cpu_to_be64(iova);
	mpt_entry->length    = cpu_to_be64(total_size);

	स_रखो(&mpt_entry->lkey, 0,
	       माप *mpt_entry - दुरत्व(काष्ठा mthca_mpt_entry, lkey));

	अगर (mr->mtt)
		mpt_entry->mtt_seg =
			cpu_to_be64(dev->mr_table.mtt_base +
				    mr->mtt->first_seg * dev->limits.mtt_seg_size);

	अगर (0) अणु
		mthca_dbg(dev, "Dumping MPT entry %08x:\n", mr->ibmr.lkey);
		क्रम (i = 0; i < माप (काष्ठा mthca_mpt_entry) / 4; ++i) अणु
			अगर (i % 4 == 0)
				prपूर्णांकk("[%02x] ", i * 4);
			prपूर्णांकk(" %08x", be32_to_cpu(((__be32 *) mpt_entry)[i]));
			अगर ((i + 1) % 4 == 0)
				prपूर्णांकk("\n");
		पूर्ण
	पूर्ण

	err = mthca_SW2HW_MPT(dev, mailbox,
			      key & (dev->limits.num_mpts - 1));
	अगर (err) अणु
		mthca_warn(dev, "SW2HW_MPT failed (%d)\n", err);
		जाओ err_out_mailbox;
	पूर्ण

	mthca_मुक्त_mailbox(dev, mailbox);
	वापस err;

err_out_mailbox:
	mthca_मुक्त_mailbox(dev, mailbox);

err_out_table:
	mthca_table_put(dev, dev->mr_table.mpt_table, key);

err_out_mpt_मुक्त:
	mthca_मुक्त(&dev->mr_table.mpt_alloc, key);
	वापस err;
पूर्ण

पूर्णांक mthca_mr_alloc_notrans(काष्ठा mthca_dev *dev, u32 pd,
			   u32 access, काष्ठा mthca_mr *mr)
अणु
	mr->mtt = शून्य;
	वापस mthca_mr_alloc(dev, pd, 12, 0, ~0ULL, access, mr);
पूर्ण

पूर्णांक mthca_mr_alloc_phys(काष्ठा mthca_dev *dev, u32 pd,
			u64 *buffer_list, पूर्णांक buffer_size_shअगरt,
			पूर्णांक list_len, u64 iova, u64 total_size,
			u32 access, काष्ठा mthca_mr *mr)
अणु
	पूर्णांक err;

	mr->mtt = mthca_alloc_mtt(dev, list_len);
	अगर (IS_ERR(mr->mtt))
		वापस PTR_ERR(mr->mtt);

	err = mthca_ग_लिखो_mtt(dev, mr->mtt, 0, buffer_list, list_len);
	अगर (err) अणु
		mthca_मुक्त_mtt(dev, mr->mtt);
		वापस err;
	पूर्ण

	err = mthca_mr_alloc(dev, pd, buffer_size_shअगरt, iova,
			     total_size, access, mr);
	अगर (err)
		mthca_मुक्त_mtt(dev, mr->mtt);

	वापस err;
पूर्ण

/* Free mr */
अटल व्योम mthca_मुक्त_region(काष्ठा mthca_dev *dev, u32 lkey)
अणु
	mthca_table_put(dev, dev->mr_table.mpt_table,
			key_to_hw_index(dev, lkey));

	mthca_मुक्त(&dev->mr_table.mpt_alloc, key_to_hw_index(dev, lkey));
पूर्ण

व्योम mthca_मुक्त_mr(काष्ठा mthca_dev *dev, काष्ठा mthca_mr *mr)
अणु
	पूर्णांक err;

	err = mthca_HW2SW_MPT(dev, शून्य,
			      key_to_hw_index(dev, mr->ibmr.lkey) &
			      (dev->limits.num_mpts - 1));
	अगर (err)
		mthca_warn(dev, "HW2SW_MPT failed (%d)\n", err);

	mthca_मुक्त_region(dev, mr->ibmr.lkey);
	mthca_मुक्त_mtt(dev, mr->mtt);
पूर्ण

पूर्णांक mthca_init_mr_table(काष्ठा mthca_dev *dev)
अणु
	phys_addr_t addr;
	पूर्णांक mpts, mtts, err, i;

	err = mthca_alloc_init(&dev->mr_table.mpt_alloc,
			       dev->limits.num_mpts,
			       ~0, dev->limits.reserved_mrws);
	अगर (err)
		वापस err;

	अगर (!mthca_is_memमुक्त(dev) &&
	    (dev->mthca_flags & MTHCA_FLAG_DDR_HIDDEN))
		dev->limits.fmr_reserved_mtts = 0;
	अन्यथा
		dev->mthca_flags |= MTHCA_FLAG_FMR;

	अगर (dev->mthca_flags & MTHCA_FLAG_SINAI_OPT)
		mthca_dbg(dev, "Memory key throughput optimization activated.\n");

	err = mthca_buddy_init(&dev->mr_table.mtt_buddy,
			       fls(dev->limits.num_mtt_segs - 1));

	अगर (err)
		जाओ err_mtt_buddy;

	dev->mr_table.tavor_fmr.mpt_base = शून्य;
	dev->mr_table.tavor_fmr.mtt_base = शून्य;

	अगर (dev->limits.fmr_reserved_mtts) अणु
		i = fls(dev->limits.fmr_reserved_mtts - 1);

		अगर (i >= 31) अणु
			mthca_warn(dev, "Unable to reserve 2^31 FMR MTTs.\न");
			err = -EINVAL;
			जाओ err_fmr_mpt;
		पूर्ण
		mpts = mtts = 1 << i;
	पूर्ण अन्यथा अणु
		mtts = dev->limits.num_mtt_segs;
		mpts = dev->limits.num_mpts;
	पूर्ण

	अगर (!mthca_is_memमुक्त(dev) &&
	    (dev->mthca_flags & MTHCA_FLAG_FMR)) अणु

		addr = pci_resource_start(dev->pdev, 4) +
			((pci_resource_len(dev->pdev, 4) - 1) &
			 dev->mr_table.mpt_base);

		dev->mr_table.tavor_fmr.mpt_base =
			ioremap(addr, mpts * माप(काष्ठा mthca_mpt_entry));

		अगर (!dev->mr_table.tavor_fmr.mpt_base) अणु
			mthca_warn(dev, "MPT ioremap for FMR failed.\n");
			err = -ENOMEM;
			जाओ err_fmr_mpt;
		पूर्ण

		addr = pci_resource_start(dev->pdev, 4) +
			((pci_resource_len(dev->pdev, 4) - 1) &
			 dev->mr_table.mtt_base);

		dev->mr_table.tavor_fmr.mtt_base =
			ioremap(addr, mtts * dev->limits.mtt_seg_size);
		अगर (!dev->mr_table.tavor_fmr.mtt_base) अणु
			mthca_warn(dev, "MTT ioremap for FMR failed.\n");
			err = -ENOMEM;
			जाओ err_fmr_mtt;
		पूर्ण
	पूर्ण

	अगर (dev->limits.fmr_reserved_mtts) अणु
		err = mthca_buddy_init(&dev->mr_table.tavor_fmr.mtt_buddy, fls(mtts - 1));
		अगर (err)
			जाओ err_fmr_mtt_buddy;

		/* Prevent regular MRs from using FMR keys */
		err = mthca_buddy_alloc(&dev->mr_table.mtt_buddy, fls(mtts - 1));
		अगर (err)
			जाओ err_reserve_fmr;

		dev->mr_table.fmr_mtt_buddy =
			&dev->mr_table.tavor_fmr.mtt_buddy;
	पूर्ण अन्यथा
		dev->mr_table.fmr_mtt_buddy = &dev->mr_table.mtt_buddy;

	/* FMR table is always the first, take reserved MTTs out of there */
	अगर (dev->limits.reserved_mtts) अणु
		i = fls(dev->limits.reserved_mtts - 1);

		अगर (mthca_alloc_mtt_range(dev, i,
					  dev->mr_table.fmr_mtt_buddy) == -1) अणु
			mthca_warn(dev, "MTT table of order %d is too small.\n",
				  dev->mr_table.fmr_mtt_buddy->max_order);
			err = -ENOMEM;
			जाओ err_reserve_mtts;
		पूर्ण
	पूर्ण

	वापस 0;

err_reserve_mtts:
err_reserve_fmr:
	अगर (dev->limits.fmr_reserved_mtts)
		mthca_buddy_cleanup(&dev->mr_table.tavor_fmr.mtt_buddy);

err_fmr_mtt_buddy:
	अगर (dev->mr_table.tavor_fmr.mtt_base)
		iounmap(dev->mr_table.tavor_fmr.mtt_base);

err_fmr_mtt:
	अगर (dev->mr_table.tavor_fmr.mpt_base)
		iounmap(dev->mr_table.tavor_fmr.mpt_base);

err_fmr_mpt:
	mthca_buddy_cleanup(&dev->mr_table.mtt_buddy);

err_mtt_buddy:
	mthca_alloc_cleanup(&dev->mr_table.mpt_alloc);

	वापस err;
पूर्ण

व्योम mthca_cleanup_mr_table(काष्ठा mthca_dev *dev)
अणु
	/* XXX check अगर any MRs are still allocated? */
	अगर (dev->limits.fmr_reserved_mtts)
		mthca_buddy_cleanup(&dev->mr_table.tavor_fmr.mtt_buddy);

	mthca_buddy_cleanup(&dev->mr_table.mtt_buddy);

	अगर (dev->mr_table.tavor_fmr.mtt_base)
		iounmap(dev->mr_table.tavor_fmr.mtt_base);
	अगर (dev->mr_table.tavor_fmr.mpt_base)
		iounmap(dev->mr_table.tavor_fmr.mpt_base);

	mthca_alloc_cleanup(&dev->mr_table.mpt_alloc);
पूर्ण
