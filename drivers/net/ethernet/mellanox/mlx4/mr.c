<शैली गुरु>
/*
 * Copyright (c) 2004 Topspin Communications.  All rights reserved.
 * Copyright (c) 2005, 2006, 2007, 2008 Mellanox Technologies. All rights reserved.
 * Copyright (c) 2006, 2007 Cisco Systems, Inc.  All rights reserved.
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

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <linux/mlx4/cmd.h>

#समावेश "mlx4.h"
#समावेश "icm.h"

अटल u32 mlx4_buddy_alloc(काष्ठा mlx4_buddy *buddy, पूर्णांक order)
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

अटल व्योम mlx4_buddy_मुक्त(काष्ठा mlx4_buddy *buddy, u32 seg, पूर्णांक order)
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

अटल पूर्णांक mlx4_buddy_init(काष्ठा mlx4_buddy *buddy, पूर्णांक max_order)
अणु
	पूर्णांक i, s;

	buddy->max_order = max_order;
	spin_lock_init(&buddy->lock);

	buddy->bits = kसुस्मृति(buddy->max_order + 1, माप(दीर्घ *),
			      GFP_KERNEL);
	buddy->num_मुक्त = kसुस्मृति(buddy->max_order + 1, माप(*buddy->num_मुक्त),
				  GFP_KERNEL);
	अगर (!buddy->bits || !buddy->num_मुक्त)
		जाओ err_out;

	क्रम (i = 0; i <= buddy->max_order; ++i) अणु
		s = BITS_TO_LONGS(1UL << (buddy->max_order - i));
		buddy->bits[i] = kvदो_स्मृति_array(s, माप(दीर्घ), GFP_KERNEL | __GFP_ZERO);
		अगर (!buddy->bits[i])
			जाओ err_out_मुक्त;
	पूर्ण

	set_bit(0, buddy->bits[buddy->max_order]);
	buddy->num_मुक्त[buddy->max_order] = 1;

	वापस 0;

err_out_मुक्त:
	क्रम (i = 0; i <= buddy->max_order; ++i)
		kvमुक्त(buddy->bits[i]);

err_out:
	kमुक्त(buddy->bits);
	kमुक्त(buddy->num_मुक्त);

	वापस -ENOMEM;
पूर्ण

अटल व्योम mlx4_buddy_cleanup(काष्ठा mlx4_buddy *buddy)
अणु
	पूर्णांक i;

	क्रम (i = 0; i <= buddy->max_order; ++i)
		kvमुक्त(buddy->bits[i]);

	kमुक्त(buddy->bits);
	kमुक्त(buddy->num_मुक्त);
पूर्ण

u32 __mlx4_alloc_mtt_range(काष्ठा mlx4_dev *dev, पूर्णांक order)
अणु
	काष्ठा mlx4_mr_table *mr_table = &mlx4_priv(dev)->mr_table;
	u32 seg;
	पूर्णांक seg_order;
	u32 offset;

	seg_order = max_t(पूर्णांक, order - log_mtts_per_seg, 0);

	seg = mlx4_buddy_alloc(&mr_table->mtt_buddy, seg_order);
	अगर (seg == -1)
		वापस -1;

	offset = seg * (1 << log_mtts_per_seg);

	अगर (mlx4_table_get_range(dev, &mr_table->mtt_table, offset,
				 offset + (1 << order) - 1)) अणु
		mlx4_buddy_मुक्त(&mr_table->mtt_buddy, seg, seg_order);
		वापस -1;
	पूर्ण

	वापस offset;
पूर्ण

अटल u32 mlx4_alloc_mtt_range(काष्ठा mlx4_dev *dev, पूर्णांक order)
अणु
	u64 in_param = 0;
	u64 out_param;
	पूर्णांक err;

	अगर (mlx4_is_mfunc(dev)) अणु
		set_param_l(&in_param, order);
		err = mlx4_cmd_imm(dev, in_param, &out_param, RES_MTT,
						       RES_OP_RESERVE_AND_MAP,
						       MLX4_CMD_ALLOC_RES,
						       MLX4_CMD_TIME_CLASS_A,
						       MLX4_CMD_WRAPPED);
		अगर (err)
			वापस -1;
		वापस get_param_l(&out_param);
	पूर्ण
	वापस __mlx4_alloc_mtt_range(dev, order);
पूर्ण

पूर्णांक mlx4_mtt_init(काष्ठा mlx4_dev *dev, पूर्णांक npages, पूर्णांक page_shअगरt,
		  काष्ठा mlx4_mtt *mtt)
अणु
	पूर्णांक i;

	अगर (!npages) अणु
		mtt->order      = -1;
		mtt->page_shअगरt = MLX4_ICM_PAGE_SHIFT;
		वापस 0;
	पूर्ण अन्यथा
		mtt->page_shअगरt = page_shअगरt;

	क्रम (mtt->order = 0, i = 1; i < npages; i <<= 1)
		++mtt->order;

	mtt->offset = mlx4_alloc_mtt_range(dev, mtt->order);
	अगर (mtt->offset == -1)
		वापस -ENOMEM;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_mtt_init);

व्योम __mlx4_मुक्त_mtt_range(काष्ठा mlx4_dev *dev, u32 offset, पूर्णांक order)
अणु
	u32 first_seg;
	पूर्णांक seg_order;
	काष्ठा mlx4_mr_table *mr_table = &mlx4_priv(dev)->mr_table;

	seg_order = max_t(पूर्णांक, order - log_mtts_per_seg, 0);
	first_seg = offset / (1 << log_mtts_per_seg);

	mlx4_buddy_मुक्त(&mr_table->mtt_buddy, first_seg, seg_order);
	mlx4_table_put_range(dev, &mr_table->mtt_table, offset,
			     offset + (1 << order) - 1);
पूर्ण

अटल व्योम mlx4_मुक्त_mtt_range(काष्ठा mlx4_dev *dev, u32 offset, पूर्णांक order)
अणु
	u64 in_param = 0;
	पूर्णांक err;

	अगर (mlx4_is_mfunc(dev)) अणु
		set_param_l(&in_param, offset);
		set_param_h(&in_param, order);
		err = mlx4_cmd(dev, in_param, RES_MTT, RES_OP_RESERVE_AND_MAP,
						       MLX4_CMD_FREE_RES,
						       MLX4_CMD_TIME_CLASS_A,
						       MLX4_CMD_WRAPPED);
		अगर (err)
			mlx4_warn(dev, "Failed to free mtt range at:%d order:%d\n",
				  offset, order);
		वापस;
	पूर्ण
	__mlx4_मुक्त_mtt_range(dev, offset, order);
पूर्ण

व्योम mlx4_mtt_cleanup(काष्ठा mlx4_dev *dev, काष्ठा mlx4_mtt *mtt)
अणु
	अगर (mtt->order < 0)
		वापस;

	mlx4_मुक्त_mtt_range(dev, mtt->offset, mtt->order);
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_mtt_cleanup);

u64 mlx4_mtt_addr(काष्ठा mlx4_dev *dev, काष्ठा mlx4_mtt *mtt)
अणु
	वापस (u64) mtt->offset * dev->caps.mtt_entry_sz;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_mtt_addr);

अटल u32 hw_index_to_key(u32 ind)
अणु
	वापस (ind >> 24) | (ind << 8);
पूर्ण

अटल u32 key_to_hw_index(u32 key)
अणु
	वापस (key << 24) | (key >> 8);
पूर्ण

अटल पूर्णांक mlx4_SW2HW_MPT(काष्ठा mlx4_dev *dev, काष्ठा mlx4_cmd_mailbox *mailbox,
			  पूर्णांक mpt_index)
अणु
	वापस mlx4_cmd(dev, mailbox->dma, mpt_index,
			0, MLX4_CMD_SW2HW_MPT, MLX4_CMD_TIME_CLASS_B,
			MLX4_CMD_WRAPPED);
पूर्ण

अटल पूर्णांक mlx4_HW2SW_MPT(काष्ठा mlx4_dev *dev, काष्ठा mlx4_cmd_mailbox *mailbox,
			  पूर्णांक mpt_index)
अणु
	वापस mlx4_cmd_box(dev, 0, mailbox ? mailbox->dma : 0, mpt_index,
			    !mailbox, MLX4_CMD_HW2SW_MPT,
			    MLX4_CMD_TIME_CLASS_B, MLX4_CMD_WRAPPED);
पूर्ण

/* Must protect against concurrent access */
पूर्णांक mlx4_mr_hw_get_mpt(काष्ठा mlx4_dev *dev, काष्ठा mlx4_mr *mmr,
		       काष्ठा mlx4_mpt_entry ***mpt_entry)
अणु
	पूर्णांक err;
	पूर्णांक key = key_to_hw_index(mmr->key) & (dev->caps.num_mpts - 1);
	काष्ठा mlx4_cmd_mailbox *mailbox = शून्य;

	अगर (mmr->enabled != MLX4_MPT_EN_HW)
		वापस -EINVAL;

	err = mlx4_HW2SW_MPT(dev, शून्य, key);
	अगर (err) अणु
		mlx4_warn(dev, "HW2SW_MPT failed (%d).", err);
		mlx4_warn(dev, "Most likely the MR has MWs bound to it.\n");
		वापस err;
	पूर्ण

	mmr->enabled = MLX4_MPT_EN_SW;

	अगर (!mlx4_is_mfunc(dev)) अणु
		**mpt_entry = mlx4_table_find(
				&mlx4_priv(dev)->mr_table.dmpt_table,
				key, शून्य);
	पूर्ण अन्यथा अणु
		mailbox = mlx4_alloc_cmd_mailbox(dev);
		अगर (IS_ERR(mailbox))
			वापस PTR_ERR(mailbox);

		err = mlx4_cmd_box(dev, 0, mailbox->dma, key,
				   0, MLX4_CMD_QUERY_MPT,
				   MLX4_CMD_TIME_CLASS_B,
				   MLX4_CMD_WRAPPED);
		अगर (err)
			जाओ मुक्त_mailbox;

		*mpt_entry = (काष्ठा mlx4_mpt_entry **)&mailbox->buf;
	पूर्ण

	अगर (!(*mpt_entry) || !(**mpt_entry)) अणु
		err = -ENOMEM;
		जाओ मुक्त_mailbox;
	पूर्ण

	वापस 0;

मुक्त_mailbox:
	mlx4_मुक्त_cmd_mailbox(dev, mailbox);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_mr_hw_get_mpt);

पूर्णांक mlx4_mr_hw_ग_लिखो_mpt(काष्ठा mlx4_dev *dev, काष्ठा mlx4_mr *mmr,
			 काष्ठा mlx4_mpt_entry **mpt_entry)
अणु
	पूर्णांक err;

	अगर (!mlx4_is_mfunc(dev)) अणु
		/* Make sure any changes to this entry are flushed */
		wmb();

		*(u8 *)(*mpt_entry) = MLX4_MPT_STATUS_HW;

		/* Make sure the new status is written */
		wmb();

		err = mlx4_SYNC_TPT(dev);
	पूर्ण अन्यथा अणु
		पूर्णांक key = key_to_hw_index(mmr->key) & (dev->caps.num_mpts - 1);

		काष्ठा mlx4_cmd_mailbox *mailbox =
			container_of((व्योम *)mpt_entry, काष्ठा mlx4_cmd_mailbox,
				     buf);

		(*mpt_entry)->lkey = 0;
		err = mlx4_SW2HW_MPT(dev, mailbox, key);
	पूर्ण

	अगर (!err) अणु
		mmr->pd = be32_to_cpu((*mpt_entry)->pd_flags) & MLX4_MPT_PD_MASK;
		mmr->enabled = MLX4_MPT_EN_HW;
	पूर्ण
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_mr_hw_ग_लिखो_mpt);

व्योम mlx4_mr_hw_put_mpt(काष्ठा mlx4_dev *dev,
			काष्ठा mlx4_mpt_entry **mpt_entry)
अणु
	अगर (mlx4_is_mfunc(dev)) अणु
		काष्ठा mlx4_cmd_mailbox *mailbox =
			container_of((व्योम *)mpt_entry, काष्ठा mlx4_cmd_mailbox,
				     buf);
		mlx4_मुक्त_cmd_mailbox(dev, mailbox);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_mr_hw_put_mpt);

पूर्णांक mlx4_mr_hw_change_pd(काष्ठा mlx4_dev *dev, काष्ठा mlx4_mpt_entry *mpt_entry,
			 u32 pdn)
अणु
	u32 pd_flags = be32_to_cpu(mpt_entry->pd_flags) & ~MLX4_MPT_PD_MASK;
	/* The wrapper function will put the slave's id here */
	अगर (mlx4_is_mfunc(dev))
		pd_flags &= ~MLX4_MPT_PD_VF_MASK;

	mpt_entry->pd_flags = cpu_to_be32(pd_flags |
					  (pdn & MLX4_MPT_PD_MASK)
					  | MLX4_MPT_PD_FLAG_EN_INV);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_mr_hw_change_pd);

पूर्णांक mlx4_mr_hw_change_access(काष्ठा mlx4_dev *dev,
			     काष्ठा mlx4_mpt_entry *mpt_entry,
			     u32 access)
अणु
	u32 flags = (be32_to_cpu(mpt_entry->flags) & ~MLX4_PERM_MASK) |
		    (access & MLX4_PERM_MASK);

	mpt_entry->flags = cpu_to_be32(flags);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_mr_hw_change_access);

अटल पूर्णांक mlx4_mr_alloc_reserved(काष्ठा mlx4_dev *dev, u32 mridx, u32 pd,
			   u64 iova, u64 size, u32 access, पूर्णांक npages,
			   पूर्णांक page_shअगरt, काष्ठा mlx4_mr *mr)
अणु
	mr->iova       = iova;
	mr->size       = size;
	mr->pd	       = pd;
	mr->access     = access;
	mr->enabled    = MLX4_MPT_DISABLED;
	mr->key	       = hw_index_to_key(mridx);

	वापस mlx4_mtt_init(dev, npages, page_shअगरt, &mr->mtt);
पूर्ण

अटल पूर्णांक mlx4_WRITE_MTT(काष्ठा mlx4_dev *dev,
			  काष्ठा mlx4_cmd_mailbox *mailbox,
			  पूर्णांक num_entries)
अणु
	वापस mlx4_cmd(dev, mailbox->dma, num_entries, 0, MLX4_CMD_WRITE_MTT,
			MLX4_CMD_TIME_CLASS_A,  MLX4_CMD_WRAPPED);
पूर्ण

पूर्णांक __mlx4_mpt_reserve(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);

	वापस mlx4_biपंचांगap_alloc(&priv->mr_table.mpt_biपंचांगap);
पूर्ण

अटल पूर्णांक mlx4_mpt_reserve(काष्ठा mlx4_dev *dev)
अणु
	u64 out_param;

	अगर (mlx4_is_mfunc(dev)) अणु
		अगर (mlx4_cmd_imm(dev, 0, &out_param, RES_MPT, RES_OP_RESERVE,
				   MLX4_CMD_ALLOC_RES,
				   MLX4_CMD_TIME_CLASS_A, MLX4_CMD_WRAPPED))
			वापस -1;
		वापस get_param_l(&out_param);
	पूर्ण
	वापस  __mlx4_mpt_reserve(dev);
पूर्ण

व्योम __mlx4_mpt_release(काष्ठा mlx4_dev *dev, u32 index)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);

	mlx4_biपंचांगap_मुक्त(&priv->mr_table.mpt_biपंचांगap, index, MLX4_NO_RR);
पूर्ण

अटल व्योम mlx4_mpt_release(काष्ठा mlx4_dev *dev, u32 index)
अणु
	u64 in_param = 0;

	अगर (mlx4_is_mfunc(dev)) अणु
		set_param_l(&in_param, index);
		अगर (mlx4_cmd(dev, in_param, RES_MPT, RES_OP_RESERVE,
			       MLX4_CMD_FREE_RES,
			       MLX4_CMD_TIME_CLASS_A, MLX4_CMD_WRAPPED))
			mlx4_warn(dev, "Failed to release mr index:%d\n",
				  index);
		वापस;
	पूर्ण
	__mlx4_mpt_release(dev, index);
पूर्ण

पूर्णांक __mlx4_mpt_alloc_icm(काष्ठा mlx4_dev *dev, u32 index)
अणु
	काष्ठा mlx4_mr_table *mr_table = &mlx4_priv(dev)->mr_table;

	वापस mlx4_table_get(dev, &mr_table->dmpt_table, index);
पूर्ण

अटल पूर्णांक mlx4_mpt_alloc_icm(काष्ठा mlx4_dev *dev, u32 index)
अणु
	u64 param = 0;

	अगर (mlx4_is_mfunc(dev)) अणु
		set_param_l(&param, index);
		वापस mlx4_cmd_imm(dev, param, &param, RES_MPT, RES_OP_MAP_ICM,
							MLX4_CMD_ALLOC_RES,
							MLX4_CMD_TIME_CLASS_A,
							MLX4_CMD_WRAPPED);
	पूर्ण
	वापस __mlx4_mpt_alloc_icm(dev, index);
पूर्ण

व्योम __mlx4_mpt_मुक्त_icm(काष्ठा mlx4_dev *dev, u32 index)
अणु
	काष्ठा mlx4_mr_table *mr_table = &mlx4_priv(dev)->mr_table;

	mlx4_table_put(dev, &mr_table->dmpt_table, index);
पूर्ण

अटल व्योम mlx4_mpt_मुक्त_icm(काष्ठा mlx4_dev *dev, u32 index)
अणु
	u64 in_param = 0;

	अगर (mlx4_is_mfunc(dev)) अणु
		set_param_l(&in_param, index);
		अगर (mlx4_cmd(dev, in_param, RES_MPT, RES_OP_MAP_ICM,
			     MLX4_CMD_FREE_RES, MLX4_CMD_TIME_CLASS_A,
			     MLX4_CMD_WRAPPED))
			mlx4_warn(dev, "Failed to free icm of mr index:%d\n",
				  index);
		वापस;
	पूर्ण
	वापस __mlx4_mpt_मुक्त_icm(dev, index);
पूर्ण

पूर्णांक mlx4_mr_alloc(काष्ठा mlx4_dev *dev, u32 pd, u64 iova, u64 size, u32 access,
		  पूर्णांक npages, पूर्णांक page_shअगरt, काष्ठा mlx4_mr *mr)
अणु
	u32 index;
	पूर्णांक err;

	index = mlx4_mpt_reserve(dev);
	अगर (index == -1)
		वापस -ENOMEM;

	err = mlx4_mr_alloc_reserved(dev, index, pd, iova, size,
				     access, npages, page_shअगरt, mr);
	अगर (err)
		mlx4_mpt_release(dev, index);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_mr_alloc);

अटल पूर्णांक mlx4_mr_मुक्त_reserved(काष्ठा mlx4_dev *dev, काष्ठा mlx4_mr *mr)
अणु
	पूर्णांक err;

	अगर (mr->enabled == MLX4_MPT_EN_HW) अणु
		err = mlx4_HW2SW_MPT(dev, शून्य,
				     key_to_hw_index(mr->key) &
				     (dev->caps.num_mpts - 1));
		अगर (err) अणु
			mlx4_warn(dev, "HW2SW_MPT failed (%d), MR has MWs bound to it\n",
				  err);
			वापस err;
		पूर्ण

		mr->enabled = MLX4_MPT_EN_SW;
	पूर्ण
	mlx4_mtt_cleanup(dev, &mr->mtt);

	वापस 0;
पूर्ण

पूर्णांक mlx4_mr_मुक्त(काष्ठा mlx4_dev *dev, काष्ठा mlx4_mr *mr)
अणु
	पूर्णांक ret;

	ret = mlx4_mr_मुक्त_reserved(dev, mr);
	अगर (ret)
		वापस ret;
	अगर (mr->enabled)
		mlx4_mpt_मुक्त_icm(dev, key_to_hw_index(mr->key));
	mlx4_mpt_release(dev, key_to_hw_index(mr->key));

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_mr_मुक्त);

व्योम mlx4_mr_rereg_mem_cleanup(काष्ठा mlx4_dev *dev, काष्ठा mlx4_mr *mr)
अणु
	mlx4_mtt_cleanup(dev, &mr->mtt);
	mr->mtt.order = -1;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_mr_rereg_mem_cleanup);

पूर्णांक mlx4_mr_rereg_mem_ग_लिखो(काष्ठा mlx4_dev *dev, काष्ठा mlx4_mr *mr,
			    u64 iova, u64 size, पूर्णांक npages,
			    पूर्णांक page_shअगरt, काष्ठा mlx4_mpt_entry *mpt_entry)
अणु
	पूर्णांक err;

	err = mlx4_mtt_init(dev, npages, page_shअगरt, &mr->mtt);
	अगर (err)
		वापस err;

	mpt_entry->start       = cpu_to_be64(iova);
	mpt_entry->length      = cpu_to_be64(size);
	mpt_entry->entity_size = cpu_to_be32(page_shअगरt);
	mpt_entry->flags    &= ~(cpu_to_be32(MLX4_MPT_FLAG_FREE |
					   MLX4_MPT_FLAG_SW_OWNS));
	अगर (mr->mtt.order < 0) अणु
		mpt_entry->flags |= cpu_to_be32(MLX4_MPT_FLAG_PHYSICAL);
		mpt_entry->mtt_addr = 0;
	पूर्ण अन्यथा अणु
		mpt_entry->mtt_addr = cpu_to_be64(mlx4_mtt_addr(dev,
						  &mr->mtt));
		अगर (mr->mtt.page_shअगरt == 0)
			mpt_entry->mtt_sz    = cpu_to_be32(1 << mr->mtt.order);
	पूर्ण
	अगर (mr->mtt.order >= 0 && mr->mtt.page_shअगरt == 0) अणु
		/* fast रेजिस्टर MR in मुक्त state */
		mpt_entry->flags    |= cpu_to_be32(MLX4_MPT_FLAG_FREE);
		mpt_entry->pd_flags |= cpu_to_be32(MLX4_MPT_PD_FLAG_FAST_REG |
						   MLX4_MPT_PD_FLAG_RAE);
	पूर्ण अन्यथा अणु
		mpt_entry->flags    |= cpu_to_be32(MLX4_MPT_FLAG_SW_OWNS);
	पूर्ण
	mr->enabled = MLX4_MPT_EN_SW;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_mr_rereg_mem_ग_लिखो);

पूर्णांक mlx4_mr_enable(काष्ठा mlx4_dev *dev, काष्ठा mlx4_mr *mr)
अणु
	काष्ठा mlx4_cmd_mailbox *mailbox;
	काष्ठा mlx4_mpt_entry *mpt_entry;
	पूर्णांक err;

	err = mlx4_mpt_alloc_icm(dev, key_to_hw_index(mr->key));
	अगर (err)
		वापस err;

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(mailbox)) अणु
		err = PTR_ERR(mailbox);
		जाओ err_table;
	पूर्ण
	mpt_entry = mailbox->buf;
	mpt_entry->flags = cpu_to_be32(MLX4_MPT_FLAG_MIO	 |
				       MLX4_MPT_FLAG_REGION	 |
				       mr->access);

	mpt_entry->key	       = cpu_to_be32(key_to_hw_index(mr->key));
	mpt_entry->pd_flags    = cpu_to_be32(mr->pd | MLX4_MPT_PD_FLAG_EN_INV);
	mpt_entry->start       = cpu_to_be64(mr->iova);
	mpt_entry->length      = cpu_to_be64(mr->size);
	mpt_entry->entity_size = cpu_to_be32(mr->mtt.page_shअगरt);

	अगर (mr->mtt.order < 0) अणु
		mpt_entry->flags |= cpu_to_be32(MLX4_MPT_FLAG_PHYSICAL);
		mpt_entry->mtt_addr = 0;
	पूर्ण अन्यथा अणु
		mpt_entry->mtt_addr = cpu_to_be64(mlx4_mtt_addr(dev,
						  &mr->mtt));
	पूर्ण

	अगर (mr->mtt.order >= 0 && mr->mtt.page_shअगरt == 0) अणु
		/* fast रेजिस्टर MR in मुक्त state */
		mpt_entry->flags    |= cpu_to_be32(MLX4_MPT_FLAG_FREE);
		mpt_entry->pd_flags |= cpu_to_be32(MLX4_MPT_PD_FLAG_FAST_REG |
						   MLX4_MPT_PD_FLAG_RAE);
		mpt_entry->mtt_sz    = cpu_to_be32(1 << mr->mtt.order);
	पूर्ण अन्यथा अणु
		mpt_entry->flags    |= cpu_to_be32(MLX4_MPT_FLAG_SW_OWNS);
	पूर्ण

	err = mlx4_SW2HW_MPT(dev, mailbox,
			     key_to_hw_index(mr->key) & (dev->caps.num_mpts - 1));
	अगर (err) अणु
		mlx4_warn(dev, "SW2HW_MPT failed (%d)\n", err);
		जाओ err_cmd;
	पूर्ण
	mr->enabled = MLX4_MPT_EN_HW;

	mlx4_मुक्त_cmd_mailbox(dev, mailbox);

	वापस 0;

err_cmd:
	mlx4_मुक्त_cmd_mailbox(dev, mailbox);

err_table:
	mlx4_mpt_मुक्त_icm(dev, key_to_hw_index(mr->key));
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_mr_enable);

अटल पूर्णांक mlx4_ग_लिखो_mtt_chunk(काष्ठा mlx4_dev *dev, काष्ठा mlx4_mtt *mtt,
				पूर्णांक start_index, पूर्णांक npages, u64 *page_list)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	__be64 *mtts;
	dma_addr_t dma_handle;
	पूर्णांक i;

	mtts = mlx4_table_find(&priv->mr_table.mtt_table, mtt->offset +
			       start_index, &dma_handle);

	अगर (!mtts)
		वापस -ENOMEM;

	dma_sync_single_क्रम_cpu(&dev->persist->pdev->dev, dma_handle,
				npages * माप(u64), DMA_TO_DEVICE);

	क्रम (i = 0; i < npages; ++i)
		mtts[i] = cpu_to_be64(page_list[i] | MLX4_MTT_FLAG_PRESENT);

	dma_sync_single_क्रम_device(&dev->persist->pdev->dev, dma_handle,
				   npages * माप(u64), DMA_TO_DEVICE);

	वापस 0;
पूर्ण

पूर्णांक __mlx4_ग_लिखो_mtt(काष्ठा mlx4_dev *dev, काष्ठा mlx4_mtt *mtt,
		     पूर्णांक start_index, पूर्णांक npages, u64 *page_list)
अणु
	पूर्णांक err = 0;
	पूर्णांक chunk;
	पूर्णांक mtts_per_page;
	पूर्णांक max_mtts_first_page;

	/* compute how may mtts fit in the first page */
	mtts_per_page = PAGE_SIZE / माप(u64);
	max_mtts_first_page = mtts_per_page - (mtt->offset + start_index)
			      % mtts_per_page;

	chunk = min_t(पूर्णांक, max_mtts_first_page, npages);

	जबतक (npages > 0) अणु
		err = mlx4_ग_लिखो_mtt_chunk(dev, mtt, start_index, chunk, page_list);
		अगर (err)
			वापस err;
		npages      -= chunk;
		start_index += chunk;
		page_list   += chunk;

		chunk = min_t(पूर्णांक, mtts_per_page, npages);
	पूर्ण
	वापस err;
पूर्ण

पूर्णांक mlx4_ग_लिखो_mtt(काष्ठा mlx4_dev *dev, काष्ठा mlx4_mtt *mtt,
		   पूर्णांक start_index, पूर्णांक npages, u64 *page_list)
अणु
	काष्ठा mlx4_cmd_mailbox *mailbox = शून्य;
	__be64 *inbox = शून्य;
	पूर्णांक chunk;
	पूर्णांक err = 0;
	पूर्णांक i;

	अगर (mtt->order < 0)
		वापस -EINVAL;

	अगर (mlx4_is_mfunc(dev)) अणु
		mailbox = mlx4_alloc_cmd_mailbox(dev);
		अगर (IS_ERR(mailbox))
			वापस PTR_ERR(mailbox);
		inbox = mailbox->buf;

		जबतक (npages > 0) अणु
			chunk = min_t(पूर्णांक, MLX4_MAILBOX_SIZE / माप(u64) - 2,
				      npages);
			inbox[0] = cpu_to_be64(mtt->offset + start_index);
			inbox[1] = 0;
			क्रम (i = 0; i < chunk; ++i)
				inbox[i + 2] = cpu_to_be64(page_list[i] |
					       MLX4_MTT_FLAG_PRESENT);
			err = mlx4_WRITE_MTT(dev, mailbox, chunk);
			अगर (err) अणु
				mlx4_मुक्त_cmd_mailbox(dev, mailbox);
				वापस err;
			पूर्ण

			npages      -= chunk;
			start_index += chunk;
			page_list   += chunk;
		पूर्ण
		mlx4_मुक्त_cmd_mailbox(dev, mailbox);
		वापस err;
	पूर्ण

	वापस __mlx4_ग_लिखो_mtt(dev, mtt, start_index, npages, page_list);
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_ग_लिखो_mtt);

पूर्णांक mlx4_buf_ग_लिखो_mtt(काष्ठा mlx4_dev *dev, काष्ठा mlx4_mtt *mtt,
		       काष्ठा mlx4_buf *buf)
अणु
	u64 *page_list;
	पूर्णांक err;
	पूर्णांक i;

	page_list = kसुस्मृति(buf->npages, माप(*page_list), GFP_KERNEL);
	अगर (!page_list)
		वापस -ENOMEM;

	क्रम (i = 0; i < buf->npages; ++i)
		अगर (buf->nbufs == 1)
			page_list[i] = buf->direct.map + (i << buf->page_shअगरt);
		अन्यथा
			page_list[i] = buf->page_list[i].map;

	err = mlx4_ग_लिखो_mtt(dev, mtt, 0, buf->npages, page_list);

	kमुक्त(page_list);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_buf_ग_लिखो_mtt);

पूर्णांक mlx4_mw_alloc(काष्ठा mlx4_dev *dev, u32 pd, क्रमागत mlx4_mw_type type,
		  काष्ठा mlx4_mw *mw)
अणु
	u32 index;

	अगर ((type == MLX4_MW_TYPE_1 &&
	     !(dev->caps.flags & MLX4_DEV_CAP_FLAG_MEM_WINDOW)) ||
	     (type == MLX4_MW_TYPE_2 &&
	     !(dev->caps.bmme_flags & MLX4_BMME_FLAG_TYPE_2_WIN)))
		वापस -EOPNOTSUPP;

	index = mlx4_mpt_reserve(dev);
	अगर (index == -1)
		वापस -ENOMEM;

	mw->key	    = hw_index_to_key(index);
	mw->pd      = pd;
	mw->type    = type;
	mw->enabled = MLX4_MPT_DISABLED;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_mw_alloc);

पूर्णांक mlx4_mw_enable(काष्ठा mlx4_dev *dev, काष्ठा mlx4_mw *mw)
अणु
	काष्ठा mlx4_cmd_mailbox *mailbox;
	काष्ठा mlx4_mpt_entry *mpt_entry;
	पूर्णांक err;

	err = mlx4_mpt_alloc_icm(dev, key_to_hw_index(mw->key));
	अगर (err)
		वापस err;

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(mailbox)) अणु
		err = PTR_ERR(mailbox);
		जाओ err_table;
	पूर्ण
	mpt_entry = mailbox->buf;

	/* Note that the MLX4_MPT_FLAG_REGION bit in mpt_entry->flags is turned
	 * off, thus creating a memory winकरोw and not a memory region.
	 */
	mpt_entry->key	       = cpu_to_be32(key_to_hw_index(mw->key));
	mpt_entry->pd_flags    = cpu_to_be32(mw->pd);
	अगर (mw->type == MLX4_MW_TYPE_2) अणु
		mpt_entry->flags    |= cpu_to_be32(MLX4_MPT_FLAG_FREE);
		mpt_entry->qpn       = cpu_to_be32(MLX4_MPT_QP_FLAG_BOUND_QP);
		mpt_entry->pd_flags |= cpu_to_be32(MLX4_MPT_PD_FLAG_EN_INV);
	पूर्ण

	err = mlx4_SW2HW_MPT(dev, mailbox,
			     key_to_hw_index(mw->key) &
			     (dev->caps.num_mpts - 1));
	अगर (err) अणु
		mlx4_warn(dev, "SW2HW_MPT failed (%d)\n", err);
		जाओ err_cmd;
	पूर्ण
	mw->enabled = MLX4_MPT_EN_HW;

	mlx4_मुक्त_cmd_mailbox(dev, mailbox);

	वापस 0;

err_cmd:
	mlx4_मुक्त_cmd_mailbox(dev, mailbox);

err_table:
	mlx4_mpt_मुक्त_icm(dev, key_to_hw_index(mw->key));
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_mw_enable);

व्योम mlx4_mw_मुक्त(काष्ठा mlx4_dev *dev, काष्ठा mlx4_mw *mw)
अणु
	पूर्णांक err;

	अगर (mw->enabled == MLX4_MPT_EN_HW) अणु
		err = mlx4_HW2SW_MPT(dev, शून्य,
				     key_to_hw_index(mw->key) &
				     (dev->caps.num_mpts - 1));
		अगर (err)
			mlx4_warn(dev, "xxx HW2SW_MPT failed (%d)\n", err);

		mw->enabled = MLX4_MPT_EN_SW;
	पूर्ण
	अगर (mw->enabled)
		mlx4_mpt_मुक्त_icm(dev, key_to_hw_index(mw->key));
	mlx4_mpt_release(dev, key_to_hw_index(mw->key));
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_mw_मुक्त);

पूर्णांक mlx4_init_mr_table(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_mr_table *mr_table = &priv->mr_table;
	पूर्णांक err;

	/* Nothing to करो क्रम slaves - all MR handling is क्रमwarded
	* to the master */
	अगर (mlx4_is_slave(dev))
		वापस 0;

	अगर (!is_घातer_of_2(dev->caps.num_mpts))
		वापस -EINVAL;

	err = mlx4_biपंचांगap_init(&mr_table->mpt_biपंचांगap, dev->caps.num_mpts,
			       ~0, dev->caps.reserved_mrws, 0);
	अगर (err)
		वापस err;

	err = mlx4_buddy_init(&mr_table->mtt_buddy,
			      ilog2((u32)dev->caps.num_mtts /
			      (1 << log_mtts_per_seg)));
	अगर (err)
		जाओ err_buddy;

	अगर (dev->caps.reserved_mtts) अणु
		priv->reserved_mtts =
			mlx4_alloc_mtt_range(dev,
					     fls(dev->caps.reserved_mtts - 1));
		अगर (priv->reserved_mtts < 0) अणु
			mlx4_warn(dev, "MTT table of order %u is too small\n",
				  mr_table->mtt_buddy.max_order);
			err = -ENOMEM;
			जाओ err_reserve_mtts;
		पूर्ण
	पूर्ण

	वापस 0;

err_reserve_mtts:
	mlx4_buddy_cleanup(&mr_table->mtt_buddy);

err_buddy:
	mlx4_biपंचांगap_cleanup(&mr_table->mpt_biपंचांगap);

	वापस err;
पूर्ण

व्योम mlx4_cleanup_mr_table(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_mr_table *mr_table = &priv->mr_table;

	अगर (mlx4_is_slave(dev))
		वापस;
	अगर (priv->reserved_mtts >= 0)
		mlx4_मुक्त_mtt_range(dev, priv->reserved_mtts,
				    fls(dev->caps.reserved_mtts - 1));
	mlx4_buddy_cleanup(&mr_table->mtt_buddy);
	mlx4_biपंचांगap_cleanup(&mr_table->mpt_biपंचांगap);
पूर्ण

पूर्णांक mlx4_SYNC_TPT(काष्ठा mlx4_dev *dev)
अणु
	वापस mlx4_cmd(dev, 0, 0, 0, MLX4_CMD_SYNC_TPT,
			MLX4_CMD_TIME_CLASS_A, MLX4_CMD_NATIVE);
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_SYNC_TPT);
