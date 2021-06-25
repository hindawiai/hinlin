<शैली गुरु>
/*
 * Copyright (c) 2016 Hisilicon Limited.
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

#समावेश <linux/platक्रमm_device.h>
#समावेश "hns_roce_device.h"
#समावेश "hns_roce_hem.h"
#समावेश "hns_roce_common.h"

#घोषणा DMA_ADDR_T_SHIFT		12
#घोषणा BT_BA_SHIFT			32

#घोषणा HEM_INDEX_BUF			BIT(0)
#घोषणा HEM_INDEX_L0			BIT(1)
#घोषणा HEM_INDEX_L1			BIT(2)
काष्ठा hns_roce_hem_index अणु
	u64 buf;
	u64 l0;
	u64 l1;
	u32 inited; /* indicate which index is available */
पूर्ण;

bool hns_roce_check_whether_mhop(काष्ठा hns_roce_dev *hr_dev, u32 type)
अणु
	पूर्णांक hop_num = 0;

	चयन (type) अणु
	हाल HEM_TYPE_QPC:
		hop_num = hr_dev->caps.qpc_hop_num;
		अवरोध;
	हाल HEM_TYPE_MTPT:
		hop_num = hr_dev->caps.mpt_hop_num;
		अवरोध;
	हाल HEM_TYPE_CQC:
		hop_num = hr_dev->caps.cqc_hop_num;
		अवरोध;
	हाल HEM_TYPE_SRQC:
		hop_num = hr_dev->caps.srqc_hop_num;
		अवरोध;
	हाल HEM_TYPE_SCCC:
		hop_num = hr_dev->caps.sccc_hop_num;
		अवरोध;
	हाल HEM_TYPE_QPC_TIMER:
		hop_num = hr_dev->caps.qpc_समयr_hop_num;
		अवरोध;
	हाल HEM_TYPE_CQC_TIMER:
		hop_num = hr_dev->caps.cqc_समयr_hop_num;
		अवरोध;
	हाल HEM_TYPE_GMV:
		hop_num = hr_dev->caps.gmv_hop_num;
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	वापस hop_num ? true : false;
पूर्ण

अटल bool hns_roce_check_hem_null(काष्ठा hns_roce_hem **hem, u64 hem_idx,
				    u32 bt_chunk_num, u64 hem_max_num)
अणु
	u64 start_idx = round_करोwn(hem_idx, bt_chunk_num);
	u64 check_max_num = start_idx + bt_chunk_num;
	u64 i;

	क्रम (i = start_idx; (i < check_max_num) && (i < hem_max_num); i++)
		अगर (i != hem_idx && hem[i])
			वापस false;

	वापस true;
पूर्ण

अटल bool hns_roce_check_bt_null(u64 **bt, u64 ba_idx, u32 bt_chunk_num)
अणु
	u64 start_idx = round_करोwn(ba_idx, bt_chunk_num);
	पूर्णांक i;

	क्रम (i = 0; i < bt_chunk_num; i++)
		अगर (i != ba_idx && bt[start_idx + i])
			वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक hns_roce_get_bt_num(u32 table_type, u32 hop_num)
अणु
	अगर (check_whether_bt_num_3(table_type, hop_num))
		वापस 3;
	अन्यथा अगर (check_whether_bt_num_2(table_type, hop_num))
		वापस 2;
	अन्यथा अगर (check_whether_bt_num_1(table_type, hop_num))
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक get_hem_table_config(काष्ठा hns_roce_dev *hr_dev,
				काष्ठा hns_roce_hem_mhop *mhop,
				u32 type)
अणु
	काष्ठा device *dev = hr_dev->dev;

	चयन (type) अणु
	हाल HEM_TYPE_QPC:
		mhop->buf_chunk_size = 1 << (hr_dev->caps.qpc_buf_pg_sz
					     + PAGE_SHIFT);
		mhop->bt_chunk_size = 1 << (hr_dev->caps.qpc_ba_pg_sz
					     + PAGE_SHIFT);
		mhop->ba_l0_num = hr_dev->caps.qpc_bt_num;
		mhop->hop_num = hr_dev->caps.qpc_hop_num;
		अवरोध;
	हाल HEM_TYPE_MTPT:
		mhop->buf_chunk_size = 1 << (hr_dev->caps.mpt_buf_pg_sz
					     + PAGE_SHIFT);
		mhop->bt_chunk_size = 1 << (hr_dev->caps.mpt_ba_pg_sz
					     + PAGE_SHIFT);
		mhop->ba_l0_num = hr_dev->caps.mpt_bt_num;
		mhop->hop_num = hr_dev->caps.mpt_hop_num;
		अवरोध;
	हाल HEM_TYPE_CQC:
		mhop->buf_chunk_size = 1 << (hr_dev->caps.cqc_buf_pg_sz
					     + PAGE_SHIFT);
		mhop->bt_chunk_size = 1 << (hr_dev->caps.cqc_ba_pg_sz
					    + PAGE_SHIFT);
		mhop->ba_l0_num = hr_dev->caps.cqc_bt_num;
		mhop->hop_num = hr_dev->caps.cqc_hop_num;
		अवरोध;
	हाल HEM_TYPE_SCCC:
		mhop->buf_chunk_size = 1 << (hr_dev->caps.sccc_buf_pg_sz
					     + PAGE_SHIFT);
		mhop->bt_chunk_size = 1 << (hr_dev->caps.sccc_ba_pg_sz
					    + PAGE_SHIFT);
		mhop->ba_l0_num = hr_dev->caps.sccc_bt_num;
		mhop->hop_num = hr_dev->caps.sccc_hop_num;
		अवरोध;
	हाल HEM_TYPE_QPC_TIMER:
		mhop->buf_chunk_size = 1 << (hr_dev->caps.qpc_समयr_buf_pg_sz
					     + PAGE_SHIFT);
		mhop->bt_chunk_size = 1 << (hr_dev->caps.qpc_समयr_ba_pg_sz
					    + PAGE_SHIFT);
		mhop->ba_l0_num = hr_dev->caps.qpc_समयr_bt_num;
		mhop->hop_num = hr_dev->caps.qpc_समयr_hop_num;
		अवरोध;
	हाल HEM_TYPE_CQC_TIMER:
		mhop->buf_chunk_size = 1 << (hr_dev->caps.cqc_समयr_buf_pg_sz
					     + PAGE_SHIFT);
		mhop->bt_chunk_size = 1 << (hr_dev->caps.cqc_समयr_ba_pg_sz
					    + PAGE_SHIFT);
		mhop->ba_l0_num = hr_dev->caps.cqc_समयr_bt_num;
		mhop->hop_num = hr_dev->caps.cqc_समयr_hop_num;
		अवरोध;
	हाल HEM_TYPE_SRQC:
		mhop->buf_chunk_size = 1 << (hr_dev->caps.srqc_buf_pg_sz
					     + PAGE_SHIFT);
		mhop->bt_chunk_size = 1 << (hr_dev->caps.srqc_ba_pg_sz
					     + PAGE_SHIFT);
		mhop->ba_l0_num = hr_dev->caps.srqc_bt_num;
		mhop->hop_num = hr_dev->caps.srqc_hop_num;
		अवरोध;
	हाल HEM_TYPE_GMV:
		mhop->buf_chunk_size = 1 << (hr_dev->caps.gmv_buf_pg_sz +
					     PAGE_SHIFT);
		mhop->bt_chunk_size = 1 << (hr_dev->caps.gmv_ba_pg_sz +
					    PAGE_SHIFT);
		mhop->ba_l0_num = hr_dev->caps.gmv_bt_num;
		mhop->hop_num = hr_dev->caps.gmv_hop_num;
		अवरोध;
	शेष:
		dev_err(dev, "table %u not support multi-hop addressing!\n",
			type);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक hns_roce_calc_hem_mhop(काष्ठा hns_roce_dev *hr_dev,
			   काष्ठा hns_roce_hem_table *table, अचिन्हित दीर्घ *obj,
			   काष्ठा hns_roce_hem_mhop *mhop)
अणु
	काष्ठा device *dev = hr_dev->dev;
	u32 chunk_ba_num;
	u32 chunk_size;
	u32 table_idx;
	u32 bt_num;

	अगर (get_hem_table_config(hr_dev, mhop, table->type))
		वापस -EINVAL;

	अगर (!obj)
		वापस 0;

	/*
	 * QPC/MTPT/CQC/SRQC/SCCC alloc hem क्रम buffer pages.
	 * MTT/CQE alloc hem क्रम bt pages.
	 */
	bt_num = hns_roce_get_bt_num(table->type, mhop->hop_num);
	chunk_ba_num = mhop->bt_chunk_size / BA_BYTE_LEN;
	chunk_size = table->type < HEM_TYPE_MTT ? mhop->buf_chunk_size :
			      mhop->bt_chunk_size;
	table_idx = (*obj & (table->num_obj - 1)) /
		     (chunk_size / table->obj_size);
	चयन (bt_num) अणु
	हाल 3:
		mhop->l2_idx = table_idx & (chunk_ba_num - 1);
		mhop->l1_idx = table_idx / chunk_ba_num & (chunk_ba_num - 1);
		mhop->l0_idx = (table_idx / chunk_ba_num) / chunk_ba_num;
		अवरोध;
	हाल 2:
		mhop->l1_idx = table_idx & (chunk_ba_num - 1);
		mhop->l0_idx = table_idx / chunk_ba_num;
		अवरोध;
	हाल 1:
		mhop->l0_idx = table_idx;
		अवरोध;
	शेष:
		dev_err(dev, "table %u not support hop_num = %u!\n",
			table->type, mhop->hop_num);
		वापस -EINVAL;
	पूर्ण
	अगर (mhop->l0_idx >= mhop->ba_l0_num)
		mhop->l0_idx %= mhop->ba_l0_num;

	वापस 0;
पूर्ण

अटल काष्ठा hns_roce_hem *hns_roce_alloc_hem(काष्ठा hns_roce_dev *hr_dev,
					       पूर्णांक npages,
					       अचिन्हित दीर्घ hem_alloc_size,
					       gfp_t gfp_mask)
अणु
	काष्ठा hns_roce_hem_chunk *chunk = शून्य;
	काष्ठा hns_roce_hem *hem;
	काष्ठा scatterlist *mem;
	पूर्णांक order;
	व्योम *buf;

	WARN_ON(gfp_mask & __GFP_HIGHMEM);

	hem = kदो_स्मृति(माप(*hem),
		      gfp_mask & ~(__GFP_HIGHMEM | __GFP_NOWARN));
	अगर (!hem)
		वापस शून्य;

	hem->refcount = 0;
	INIT_LIST_HEAD(&hem->chunk_list);

	order = get_order(hem_alloc_size);

	जबतक (npages > 0) अणु
		अगर (!chunk) अणु
			chunk = kदो_स्मृति(माप(*chunk),
				gfp_mask & ~(__GFP_HIGHMEM | __GFP_NOWARN));
			अगर (!chunk)
				जाओ fail;

			sg_init_table(chunk->mem, HNS_ROCE_HEM_CHUNK_LEN);
			chunk->npages = 0;
			chunk->nsg = 0;
			स_रखो(chunk->buf, 0, माप(chunk->buf));
			list_add_tail(&chunk->list, &hem->chunk_list);
		पूर्ण

		जबतक (1 << order > npages)
			--order;

		/*
		 * Alloc memory one समय. If failed, करोn't alloc small block
		 * memory, directly वापस fail.
		 */
		mem = &chunk->mem[chunk->npages];
		buf = dma_alloc_coherent(hr_dev->dev, PAGE_SIZE << order,
				&sg_dma_address(mem), gfp_mask);
		अगर (!buf)
			जाओ fail;

		chunk->buf[chunk->npages] = buf;
		sg_dma_len(mem) = PAGE_SIZE << order;

		++chunk->npages;
		++chunk->nsg;
		npages -= 1 << order;
	पूर्ण

	वापस hem;

fail:
	hns_roce_मुक्त_hem(hr_dev, hem);
	वापस शून्य;
पूर्ण

व्योम hns_roce_मुक्त_hem(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_hem *hem)
अणु
	काष्ठा hns_roce_hem_chunk *chunk, *पंचांगp;
	पूर्णांक i;

	अगर (!hem)
		वापस;

	list_क्रम_each_entry_safe(chunk, पंचांगp, &hem->chunk_list, list) अणु
		क्रम (i = 0; i < chunk->npages; ++i)
			dma_मुक्त_coherent(hr_dev->dev,
				   sg_dma_len(&chunk->mem[i]),
				   chunk->buf[i],
				   sg_dma_address(&chunk->mem[i]));
		kमुक्त(chunk);
	पूर्ण

	kमुक्त(hem);
पूर्ण

अटल पूर्णांक hns_roce_set_hem(काष्ठा hns_roce_dev *hr_dev,
			    काष्ठा hns_roce_hem_table *table, अचिन्हित दीर्घ obj)
अणु
	spinlock_t *lock = &hr_dev->bt_cmd_lock;
	काष्ठा device *dev = hr_dev->dev;
	काष्ठा hns_roce_hem_iter iter;
	व्योम __iomem *bt_cmd;
	__le32 bt_cmd_val[2];
	__le32 bt_cmd_h = 0;
	अचिन्हित दीर्घ flags;
	__le32 bt_cmd_l;
	पूर्णांक ret = 0;
	u64 bt_ba;
	दीर्घ end;

	/* Find the HEM(Hardware Entry Memory) entry */
	अचिन्हित दीर्घ i = (obj & (table->num_obj - 1)) /
			  (table->table_chunk_size / table->obj_size);

	चयन (table->type) अणु
	हाल HEM_TYPE_QPC:
	हाल HEM_TYPE_MTPT:
	हाल HEM_TYPE_CQC:
	हाल HEM_TYPE_SRQC:
		roce_set_field(bt_cmd_h, ROCEE_BT_CMD_H_ROCEE_BT_CMD_MDF_M,
			ROCEE_BT_CMD_H_ROCEE_BT_CMD_MDF_S, table->type);
		अवरोध;
	शेष:
		वापस ret;
	पूर्ण

	roce_set_field(bt_cmd_h, ROCEE_BT_CMD_H_ROCEE_BT_CMD_IN_MDF_M,
		       ROCEE_BT_CMD_H_ROCEE_BT_CMD_IN_MDF_S, obj);
	roce_set_bit(bt_cmd_h, ROCEE_BT_CMD_H_ROCEE_BT_CMD_S, 0);
	roce_set_bit(bt_cmd_h, ROCEE_BT_CMD_H_ROCEE_BT_CMD_HW_SYNS_S, 1);

	/* Currently iter only a chunk */
	क्रम (hns_roce_hem_first(table->hem[i], &iter);
	     !hns_roce_hem_last(&iter); hns_roce_hem_next(&iter)) अणु
		bt_ba = hns_roce_hem_addr(&iter) >> DMA_ADDR_T_SHIFT;

		spin_lock_irqsave(lock, flags);

		bt_cmd = hr_dev->reg_base + ROCEE_BT_CMD_H_REG;

		end = HW_SYNC_TIMEOUT_MSECS;
		जबतक (end > 0) अणु
			अगर (!(पढ़ोl(bt_cmd) >> BT_CMD_SYNC_SHIFT))
				अवरोध;

			mdelay(HW_SYNC_SLEEP_TIME_INTERVAL);
			end -= HW_SYNC_SLEEP_TIME_INTERVAL;
		पूर्ण

		अगर (end <= 0) अणु
			dev_err(dev, "Write bt_cmd err,hw_sync is not zero.\n");
			spin_unlock_irqrestore(lock, flags);
			वापस -EBUSY;
		पूर्ण

		bt_cmd_l = cpu_to_le32(bt_ba);
		roce_set_field(bt_cmd_h, ROCEE_BT_CMD_H_ROCEE_BT_CMD_BA_H_M,
			       ROCEE_BT_CMD_H_ROCEE_BT_CMD_BA_H_S,
			       bt_ba >> BT_BA_SHIFT);

		bt_cmd_val[0] = bt_cmd_l;
		bt_cmd_val[1] = bt_cmd_h;
		hns_roce_ग_लिखो64_k(bt_cmd_val,
				   hr_dev->reg_base + ROCEE_BT_CMD_L_REG);
		spin_unlock_irqrestore(lock, flags);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक calc_hem_config(काष्ठा hns_roce_dev *hr_dev,
			   काष्ठा hns_roce_hem_table *table, अचिन्हित दीर्घ obj,
			   काष्ठा hns_roce_hem_mhop *mhop,
			   काष्ठा hns_roce_hem_index *index)
अणु
	काष्ठा ib_device *ibdev = &hr_dev->ib_dev;
	अचिन्हित दीर्घ mhop_obj = obj;
	u32 l0_idx, l1_idx, l2_idx;
	u32 chunk_ba_num;
	u32 bt_num;
	पूर्णांक ret;

	ret = hns_roce_calc_hem_mhop(hr_dev, table, &mhop_obj, mhop);
	अगर (ret)
		वापस ret;

	l0_idx = mhop->l0_idx;
	l1_idx = mhop->l1_idx;
	l2_idx = mhop->l2_idx;
	chunk_ba_num = mhop->bt_chunk_size / BA_BYTE_LEN;
	bt_num = hns_roce_get_bt_num(table->type, mhop->hop_num);
	चयन (bt_num) अणु
	हाल 3:
		index->l1 = l0_idx * chunk_ba_num + l1_idx;
		index->l0 = l0_idx;
		index->buf = l0_idx * chunk_ba_num * chunk_ba_num +
			     l1_idx * chunk_ba_num + l2_idx;
		अवरोध;
	हाल 2:
		index->l0 = l0_idx;
		index->buf = l0_idx * chunk_ba_num + l1_idx;
		अवरोध;
	हाल 1:
		index->buf = l0_idx;
		अवरोध;
	शेष:
		ibdev_err(ibdev, "table %u not support mhop.hop_num = %u!\n",
			  table->type, mhop->hop_num);
		वापस -EINVAL;
	पूर्ण

	अगर (unlikely(index->buf >= table->num_hem)) अणु
		ibdev_err(ibdev, "table %u exceed hem limt idx %llu, max %lu!\n",
			  table->type, index->buf, table->num_hem);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम मुक्त_mhop_hem(काष्ठा hns_roce_dev *hr_dev,
			  काष्ठा hns_roce_hem_table *table,
			  काष्ठा hns_roce_hem_mhop *mhop,
			  काष्ठा hns_roce_hem_index *index)
अणु
	u32 bt_size = mhop->bt_chunk_size;
	काष्ठा device *dev = hr_dev->dev;

	अगर (index->inited & HEM_INDEX_BUF) अणु
		hns_roce_मुक्त_hem(hr_dev, table->hem[index->buf]);
		table->hem[index->buf] = शून्य;
	पूर्ण

	अगर (index->inited & HEM_INDEX_L1) अणु
		dma_मुक्त_coherent(dev, bt_size, table->bt_l1[index->l1],
				  table->bt_l1_dma_addr[index->l1]);
		table->bt_l1[index->l1] = शून्य;
	पूर्ण

	अगर (index->inited & HEM_INDEX_L0) अणु
		dma_मुक्त_coherent(dev, bt_size, table->bt_l0[index->l0],
				  table->bt_l0_dma_addr[index->l0]);
		table->bt_l0[index->l0] = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक alloc_mhop_hem(काष्ठा hns_roce_dev *hr_dev,
			  काष्ठा hns_roce_hem_table *table,
			  काष्ठा hns_roce_hem_mhop *mhop,
			  काष्ठा hns_roce_hem_index *index)
अणु
	u32 bt_size = mhop->bt_chunk_size;
	काष्ठा device *dev = hr_dev->dev;
	काष्ठा hns_roce_hem_iter iter;
	gfp_t flag;
	u64 bt_ba;
	u32 size;
	पूर्णांक ret;

	/* alloc L1 BA's chunk */
	अगर ((check_whether_bt_num_3(table->type, mhop->hop_num) ||
	     check_whether_bt_num_2(table->type, mhop->hop_num)) &&
	     !table->bt_l0[index->l0]) अणु
		table->bt_l0[index->l0] = dma_alloc_coherent(dev, bt_size,
					    &table->bt_l0_dma_addr[index->l0],
					    GFP_KERNEL);
		अगर (!table->bt_l0[index->l0]) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण
		index->inited |= HEM_INDEX_L0;
	पूर्ण

	/* alloc L2 BA's chunk */
	अगर (check_whether_bt_num_3(table->type, mhop->hop_num) &&
	    !table->bt_l1[index->l1])  अणु
		table->bt_l1[index->l1] = dma_alloc_coherent(dev, bt_size,
					    &table->bt_l1_dma_addr[index->l1],
					    GFP_KERNEL);
		अगर (!table->bt_l1[index->l1]) अणु
			ret = -ENOMEM;
			जाओ err_alloc_hem;
		पूर्ण
		index->inited |= HEM_INDEX_L1;
		*(table->bt_l0[index->l0] + mhop->l1_idx) =
					       table->bt_l1_dma_addr[index->l1];
	पूर्ण

	/*
	 * alloc buffer space chunk क्रम QPC/MTPT/CQC/SRQC/SCCC.
	 * alloc bt space chunk क्रम MTT/CQE.
	 */
	size = table->type < HEM_TYPE_MTT ? mhop->buf_chunk_size : bt_size;
	flag = (table->lowmem ? GFP_KERNEL : GFP_HIGHUSER) | __GFP_NOWARN;
	table->hem[index->buf] = hns_roce_alloc_hem(hr_dev, size >> PAGE_SHIFT,
						    size, flag);
	अगर (!table->hem[index->buf]) अणु
		ret = -ENOMEM;
		जाओ err_alloc_hem;
	पूर्ण

	index->inited |= HEM_INDEX_BUF;
	hns_roce_hem_first(table->hem[index->buf], &iter);
	bt_ba = hns_roce_hem_addr(&iter);
	अगर (table->type < HEM_TYPE_MTT) अणु
		अगर (mhop->hop_num == 2)
			*(table->bt_l1[index->l1] + mhop->l2_idx) = bt_ba;
		अन्यथा अगर (mhop->hop_num == 1)
			*(table->bt_l0[index->l0] + mhop->l1_idx) = bt_ba;
	पूर्ण अन्यथा अगर (mhop->hop_num == 2) अणु
		*(table->bt_l0[index->l0] + mhop->l1_idx) = bt_ba;
	पूर्ण

	वापस 0;
err_alloc_hem:
	मुक्त_mhop_hem(hr_dev, table, mhop, index);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक set_mhop_hem(काष्ठा hns_roce_dev *hr_dev,
			काष्ठा hns_roce_hem_table *table, अचिन्हित दीर्घ obj,
			काष्ठा hns_roce_hem_mhop *mhop,
			काष्ठा hns_roce_hem_index *index)
अणु
	काष्ठा ib_device *ibdev = &hr_dev->ib_dev;
	पूर्णांक step_idx;
	पूर्णांक ret = 0;

	अगर (index->inited & HEM_INDEX_L0) अणु
		ret = hr_dev->hw->set_hem(hr_dev, table, obj, 0);
		अगर (ret) अणु
			ibdev_err(ibdev, "set HEM step 0 failed!\n");
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (index->inited & HEM_INDEX_L1) अणु
		ret = hr_dev->hw->set_hem(hr_dev, table, obj, 1);
		अगर (ret) अणु
			ibdev_err(ibdev, "set HEM step 1 failed!\n");
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (index->inited & HEM_INDEX_BUF) अणु
		अगर (mhop->hop_num == HNS_ROCE_HOP_NUM_0)
			step_idx = 0;
		अन्यथा
			step_idx = mhop->hop_num;
		ret = hr_dev->hw->set_hem(hr_dev, table, obj, step_idx);
		अगर (ret)
			ibdev_err(ibdev, "set HEM step last failed!\n");
	पूर्ण
out:
	वापस ret;
पूर्ण

अटल पूर्णांक hns_roce_table_mhop_get(काष्ठा hns_roce_dev *hr_dev,
				   काष्ठा hns_roce_hem_table *table,
				   अचिन्हित दीर्घ obj)
अणु
	काष्ठा ib_device *ibdev = &hr_dev->ib_dev;
	काष्ठा hns_roce_hem_index index = अणुपूर्ण;
	काष्ठा hns_roce_hem_mhop mhop = अणुपूर्ण;
	पूर्णांक ret;

	ret = calc_hem_config(hr_dev, table, obj, &mhop, &index);
	अगर (ret) अणु
		ibdev_err(ibdev, "calc hem config failed!\n");
		वापस ret;
	पूर्ण

	mutex_lock(&table->mutex);
	अगर (table->hem[index.buf]) अणु
		++table->hem[index.buf]->refcount;
		जाओ out;
	पूर्ण

	ret = alloc_mhop_hem(hr_dev, table, &mhop, &index);
	अगर (ret) अणु
		ibdev_err(ibdev, "alloc mhop hem failed!\n");
		जाओ out;
	पूर्ण

	/* set HEM base address to hardware */
	अगर (table->type < HEM_TYPE_MTT) अणु
		ret = set_mhop_hem(hr_dev, table, obj, &mhop, &index);
		अगर (ret) अणु
			ibdev_err(ibdev, "set HEM address to HW failed!\n");
			जाओ err_alloc;
		पूर्ण
	पूर्ण

	++table->hem[index.buf]->refcount;
	जाओ out;

err_alloc:
	मुक्त_mhop_hem(hr_dev, table, &mhop, &index);
out:
	mutex_unlock(&table->mutex);
	वापस ret;
पूर्ण

पूर्णांक hns_roce_table_get(काष्ठा hns_roce_dev *hr_dev,
		       काष्ठा hns_roce_hem_table *table, अचिन्हित दीर्घ obj)
अणु
	काष्ठा device *dev = hr_dev->dev;
	अचिन्हित दीर्घ i;
	पूर्णांक ret = 0;

	अगर (hns_roce_check_whether_mhop(hr_dev, table->type))
		वापस hns_roce_table_mhop_get(hr_dev, table, obj);

	i = (obj & (table->num_obj - 1)) / (table->table_chunk_size /
	     table->obj_size);

	mutex_lock(&table->mutex);

	अगर (table->hem[i]) अणु
		++table->hem[i]->refcount;
		जाओ out;
	पूर्ण

	table->hem[i] = hns_roce_alloc_hem(hr_dev,
				       table->table_chunk_size >> PAGE_SHIFT,
				       table->table_chunk_size,
				       (table->lowmem ? GFP_KERNEL :
					GFP_HIGHUSER) | __GFP_NOWARN);
	अगर (!table->hem[i]) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	/* Set HEM base address(128K/page, pa) to Hardware */
	अगर (hns_roce_set_hem(hr_dev, table, obj)) अणु
		hns_roce_मुक्त_hem(hr_dev, table->hem[i]);
		table->hem[i] = शून्य;
		ret = -ENODEV;
		dev_err(dev, "set HEM base address to HW failed.\n");
		जाओ out;
	पूर्ण

	++table->hem[i]->refcount;
out:
	mutex_unlock(&table->mutex);
	वापस ret;
पूर्ण

अटल व्योम clear_mhop_hem(काष्ठा hns_roce_dev *hr_dev,
			   काष्ठा hns_roce_hem_table *table, अचिन्हित दीर्घ obj,
			   काष्ठा hns_roce_hem_mhop *mhop,
			   काष्ठा hns_roce_hem_index *index)
अणु
	काष्ठा ib_device *ibdev = &hr_dev->ib_dev;
	u32 hop_num = mhop->hop_num;
	u32 chunk_ba_num;
	पूर्णांक step_idx;

	index->inited = HEM_INDEX_BUF;
	chunk_ba_num = mhop->bt_chunk_size / BA_BYTE_LEN;
	अगर (check_whether_bt_num_2(table->type, hop_num)) अणु
		अगर (hns_roce_check_hem_null(table->hem, index->buf,
					    chunk_ba_num, table->num_hem))
			index->inited |= HEM_INDEX_L0;
	पूर्ण अन्यथा अगर (check_whether_bt_num_3(table->type, hop_num)) अणु
		अगर (hns_roce_check_hem_null(table->hem, index->buf,
					    chunk_ba_num, table->num_hem)) अणु
			index->inited |= HEM_INDEX_L1;
			अगर (hns_roce_check_bt_null(table->bt_l1, index->l1,
						   chunk_ba_num))
				index->inited |= HEM_INDEX_L0;
		पूर्ण
	पूर्ण

	अगर (table->type < HEM_TYPE_MTT) अणु
		अगर (hop_num == HNS_ROCE_HOP_NUM_0)
			step_idx = 0;
		अन्यथा
			step_idx = hop_num;

		अगर (hr_dev->hw->clear_hem(hr_dev, table, obj, step_idx))
			ibdev_warn(ibdev, "failed to clear hop%u HEM.\n", hop_num);

		अगर (index->inited & HEM_INDEX_L1)
			अगर (hr_dev->hw->clear_hem(hr_dev, table, obj, 1))
				ibdev_warn(ibdev, "failed to clear HEM step 1.\n");

		अगर (index->inited & HEM_INDEX_L0)
			अगर (hr_dev->hw->clear_hem(hr_dev, table, obj, 0))
				ibdev_warn(ibdev, "failed to clear HEM step 0.\n");
	पूर्ण
पूर्ण

अटल व्योम hns_roce_table_mhop_put(काष्ठा hns_roce_dev *hr_dev,
				    काष्ठा hns_roce_hem_table *table,
				    अचिन्हित दीर्घ obj,
				    पूर्णांक check_refcount)
अणु
	काष्ठा ib_device *ibdev = &hr_dev->ib_dev;
	काष्ठा hns_roce_hem_index index = अणुपूर्ण;
	काष्ठा hns_roce_hem_mhop mhop = अणुपूर्ण;
	पूर्णांक ret;

	ret = calc_hem_config(hr_dev, table, obj, &mhop, &index);
	अगर (ret) अणु
		ibdev_err(ibdev, "calc hem config failed!\n");
		वापस;
	पूर्ण

	mutex_lock(&table->mutex);
	अगर (check_refcount && (--table->hem[index.buf]->refcount > 0)) अणु
		mutex_unlock(&table->mutex);
		वापस;
	पूर्ण

	clear_mhop_hem(hr_dev, table, obj, &mhop, &index);
	मुक्त_mhop_hem(hr_dev, table, &mhop, &index);

	mutex_unlock(&table->mutex);
पूर्ण

व्योम hns_roce_table_put(काष्ठा hns_roce_dev *hr_dev,
			काष्ठा hns_roce_hem_table *table, अचिन्हित दीर्घ obj)
अणु
	काष्ठा device *dev = hr_dev->dev;
	अचिन्हित दीर्घ i;

	अगर (hns_roce_check_whether_mhop(hr_dev, table->type)) अणु
		hns_roce_table_mhop_put(hr_dev, table, obj, 1);
		वापस;
	पूर्ण

	i = (obj & (table->num_obj - 1)) /
	    (table->table_chunk_size / table->obj_size);

	mutex_lock(&table->mutex);

	अगर (--table->hem[i]->refcount == 0) अणु
		/* Clear HEM base address */
		अगर (hr_dev->hw->clear_hem(hr_dev, table, obj, 0))
			dev_warn(dev, "Clear HEM base address failed.\n");

		hns_roce_मुक्त_hem(hr_dev, table->hem[i]);
		table->hem[i] = शून्य;
	पूर्ण

	mutex_unlock(&table->mutex);
पूर्ण

व्योम *hns_roce_table_find(काष्ठा hns_roce_dev *hr_dev,
			  काष्ठा hns_roce_hem_table *table,
			  अचिन्हित दीर्घ obj, dma_addr_t *dma_handle)
अणु
	काष्ठा hns_roce_hem_chunk *chunk;
	काष्ठा hns_roce_hem_mhop mhop;
	काष्ठा hns_roce_hem *hem;
	अचिन्हित दीर्घ mhop_obj = obj;
	अचिन्हित दीर्घ obj_per_chunk;
	अचिन्हित दीर्घ idx_offset;
	पूर्णांक offset, dma_offset;
	व्योम *addr = शून्य;
	u32 hem_idx = 0;
	पूर्णांक length;
	पूर्णांक i, j;

	अगर (!table->lowmem)
		वापस शून्य;

	mutex_lock(&table->mutex);

	अगर (!hns_roce_check_whether_mhop(hr_dev, table->type)) अणु
		obj_per_chunk = table->table_chunk_size / table->obj_size;
		hem = table->hem[(obj & (table->num_obj - 1)) / obj_per_chunk];
		idx_offset = (obj & (table->num_obj - 1)) % obj_per_chunk;
		dma_offset = offset = idx_offset * table->obj_size;
	पूर्ण अन्यथा अणु
		u32 seg_size = 64; /* 8 bytes per BA and 8 BA per segment */

		अगर (hns_roce_calc_hem_mhop(hr_dev, table, &mhop_obj, &mhop))
			जाओ out;
		/* mtt mhop */
		i = mhop.l0_idx;
		j = mhop.l1_idx;
		अगर (mhop.hop_num == 2)
			hem_idx = i * (mhop.bt_chunk_size / BA_BYTE_LEN) + j;
		अन्यथा अगर (mhop.hop_num == 1 ||
			 mhop.hop_num == HNS_ROCE_HOP_NUM_0)
			hem_idx = i;

		hem = table->hem[hem_idx];
		dma_offset = offset = (obj & (table->num_obj - 1)) * seg_size %
				       mhop.bt_chunk_size;
		अगर (mhop.hop_num == 2)
			dma_offset = offset = 0;
	पूर्ण

	अगर (!hem)
		जाओ out;

	list_क्रम_each_entry(chunk, &hem->chunk_list, list) अणु
		क्रम (i = 0; i < chunk->npages; ++i) अणु
			length = sg_dma_len(&chunk->mem[i]);
			अगर (dma_handle && dma_offset >= 0) अणु
				अगर (length > (u32)dma_offset)
					*dma_handle = sg_dma_address(
						&chunk->mem[i]) + dma_offset;
				dma_offset -= length;
			पूर्ण

			अगर (length > (u32)offset) अणु
				addr = chunk->buf[i] + offset;
				जाओ out;
			पूर्ण
			offset -= length;
		पूर्ण
	पूर्ण

out:
	mutex_unlock(&table->mutex);
	वापस addr;
पूर्ण

पूर्णांक hns_roce_init_hem_table(काष्ठा hns_roce_dev *hr_dev,
			    काष्ठा hns_roce_hem_table *table, u32 type,
			    अचिन्हित दीर्घ obj_size, अचिन्हित दीर्घ nobj,
			    पूर्णांक use_lowmem)
अणु
	अचिन्हित दीर्घ obj_per_chunk;
	अचिन्हित दीर्घ num_hem;

	अगर (!hns_roce_check_whether_mhop(hr_dev, type)) अणु
		table->table_chunk_size = hr_dev->caps.chunk_sz;
		obj_per_chunk = table->table_chunk_size / obj_size;
		num_hem = (nobj + obj_per_chunk - 1) / obj_per_chunk;

		table->hem = kसुस्मृति(num_hem, माप(*table->hem), GFP_KERNEL);
		अगर (!table->hem)
			वापस -ENOMEM;
	पूर्ण अन्यथा अणु
		काष्ठा hns_roce_hem_mhop mhop = अणुपूर्ण;
		अचिन्हित दीर्घ buf_chunk_size;
		अचिन्हित दीर्घ bt_chunk_size;
		अचिन्हित दीर्घ bt_chunk_num;
		अचिन्हित दीर्घ num_bt_l0;
		u32 hop_num;

		अगर (get_hem_table_config(hr_dev, &mhop, type))
			वापस -EINVAL;

		buf_chunk_size = mhop.buf_chunk_size;
		bt_chunk_size = mhop.bt_chunk_size;
		num_bt_l0 = mhop.ba_l0_num;
		hop_num = mhop.hop_num;

		obj_per_chunk = buf_chunk_size / obj_size;
		num_hem = (nobj + obj_per_chunk - 1) / obj_per_chunk;
		bt_chunk_num = bt_chunk_size / BA_BYTE_LEN;
		अगर (type >= HEM_TYPE_MTT)
			num_bt_l0 = bt_chunk_num;

		table->hem = kसुस्मृति(num_hem, माप(*table->hem),
					 GFP_KERNEL);
		अगर (!table->hem)
			जाओ err_kसुस्मृति_hem_buf;

		अगर (check_whether_bt_num_3(type, hop_num)) अणु
			अचिन्हित दीर्घ num_bt_l1;

			num_bt_l1 = (num_hem + bt_chunk_num - 1) /
					     bt_chunk_num;
			table->bt_l1 = kसुस्मृति(num_bt_l1,
					       माप(*table->bt_l1),
					       GFP_KERNEL);
			अगर (!table->bt_l1)
				जाओ err_kसुस्मृति_bt_l1;

			table->bt_l1_dma_addr = kसुस्मृति(num_bt_l1,
						 माप(*table->bt_l1_dma_addr),
						 GFP_KERNEL);

			अगर (!table->bt_l1_dma_addr)
				जाओ err_kसुस्मृति_l1_dma;
		पूर्ण

		अगर (check_whether_bt_num_2(type, hop_num) ||
			check_whether_bt_num_3(type, hop_num)) अणु
			table->bt_l0 = kसुस्मृति(num_bt_l0, माप(*table->bt_l0),
					       GFP_KERNEL);
			अगर (!table->bt_l0)
				जाओ err_kसुस्मृति_bt_l0;

			table->bt_l0_dma_addr = kसुस्मृति(num_bt_l0,
						 माप(*table->bt_l0_dma_addr),
						 GFP_KERNEL);
			अगर (!table->bt_l0_dma_addr)
				जाओ err_kसुस्मृति_l0_dma;
		पूर्ण
	पूर्ण

	table->type = type;
	table->num_hem = num_hem;
	table->num_obj = nobj;
	table->obj_size = obj_size;
	table->lowmem = use_lowmem;
	mutex_init(&table->mutex);

	वापस 0;

err_kसुस्मृति_l0_dma:
	kमुक्त(table->bt_l0);
	table->bt_l0 = शून्य;

err_kसुस्मृति_bt_l0:
	kमुक्त(table->bt_l1_dma_addr);
	table->bt_l1_dma_addr = शून्य;

err_kसुस्मृति_l1_dma:
	kमुक्त(table->bt_l1);
	table->bt_l1 = शून्य;

err_kसुस्मृति_bt_l1:
	kमुक्त(table->hem);
	table->hem = शून्य;

err_kसुस्मृति_hem_buf:
	वापस -ENOMEM;
पूर्ण

अटल व्योम hns_roce_cleanup_mhop_hem_table(काष्ठा hns_roce_dev *hr_dev,
					    काष्ठा hns_roce_hem_table *table)
अणु
	काष्ठा hns_roce_hem_mhop mhop;
	u32 buf_chunk_size;
	u64 obj;
	पूर्णांक i;

	अगर (hns_roce_calc_hem_mhop(hr_dev, table, शून्य, &mhop))
		वापस;
	buf_chunk_size = table->type < HEM_TYPE_MTT ? mhop.buf_chunk_size :
					mhop.bt_chunk_size;

	क्रम (i = 0; i < table->num_hem; ++i) अणु
		obj = i * buf_chunk_size / table->obj_size;
		अगर (table->hem[i])
			hns_roce_table_mhop_put(hr_dev, table, obj, 0);
	पूर्ण

	kमुक्त(table->hem);
	table->hem = शून्य;
	kमुक्त(table->bt_l1);
	table->bt_l1 = शून्य;
	kमुक्त(table->bt_l1_dma_addr);
	table->bt_l1_dma_addr = शून्य;
	kमुक्त(table->bt_l0);
	table->bt_l0 = शून्य;
	kमुक्त(table->bt_l0_dma_addr);
	table->bt_l0_dma_addr = शून्य;
पूर्ण

व्योम hns_roce_cleanup_hem_table(काष्ठा hns_roce_dev *hr_dev,
				काष्ठा hns_roce_hem_table *table)
अणु
	काष्ठा device *dev = hr_dev->dev;
	अचिन्हित दीर्घ i;

	अगर (hns_roce_check_whether_mhop(hr_dev, table->type)) अणु
		hns_roce_cleanup_mhop_hem_table(hr_dev, table);
		वापस;
	पूर्ण

	क्रम (i = 0; i < table->num_hem; ++i)
		अगर (table->hem[i]) अणु
			अगर (hr_dev->hw->clear_hem(hr_dev, table,
			    i * table->table_chunk_size / table->obj_size, 0))
				dev_err(dev, "Clear HEM base address failed.\n");

			hns_roce_मुक्त_hem(hr_dev, table->hem[i]);
		पूर्ण

	kमुक्त(table->hem);
पूर्ण

व्योम hns_roce_cleanup_hem(काष्ठा hns_roce_dev *hr_dev)
अणु
	अगर (hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_SRQ)
		hns_roce_cleanup_hem_table(hr_dev,
					   &hr_dev->srq_table.table);
	hns_roce_cleanup_hem_table(hr_dev, &hr_dev->cq_table.table);
	अगर (hr_dev->caps.qpc_समयr_entry_sz)
		hns_roce_cleanup_hem_table(hr_dev,
					   &hr_dev->qpc_समयr_table);
	अगर (hr_dev->caps.cqc_समयr_entry_sz)
		hns_roce_cleanup_hem_table(hr_dev,
					   &hr_dev->cqc_समयr_table);
	अगर (hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_QP_FLOW_CTRL)
		hns_roce_cleanup_hem_table(hr_dev,
					   &hr_dev->qp_table.sccc_table);
	अगर (hr_dev->caps.trrl_entry_sz)
		hns_roce_cleanup_hem_table(hr_dev,
					   &hr_dev->qp_table.trrl_table);

	अगर (hr_dev->caps.gmv_entry_sz)
		hns_roce_cleanup_hem_table(hr_dev, &hr_dev->gmv_table);

	hns_roce_cleanup_hem_table(hr_dev, &hr_dev->qp_table.irrl_table);
	hns_roce_cleanup_hem_table(hr_dev, &hr_dev->qp_table.qp_table);
	hns_roce_cleanup_hem_table(hr_dev, &hr_dev->mr_table.mtpt_table);
पूर्ण

काष्ठा roce_hem_item अणु
	काष्ठा list_head list; /* link all hems in the same bt level */
	काष्ठा list_head sibling; /* link all hems in last hop क्रम mtt */
	व्योम *addr;
	dma_addr_t dma_addr;
	माप_प्रकार count; /* max ba numbers */
	पूर्णांक start; /* start buf offset in this hem */
	पूर्णांक end; /* end buf offset in this hem */
पूर्ण;

अटल काष्ठा roce_hem_item *hem_list_alloc_item(काष्ठा hns_roce_dev *hr_dev,
						   पूर्णांक start, पूर्णांक end,
						   पूर्णांक count, bool exist_bt,
						   पूर्णांक bt_level)
अणु
	काष्ठा roce_hem_item *hem;

	hem = kzalloc(माप(*hem), GFP_KERNEL);
	अगर (!hem)
		वापस शून्य;

	अगर (exist_bt) अणु
		hem->addr = dma_alloc_coherent(hr_dev->dev, count * BA_BYTE_LEN,
					       &hem->dma_addr, GFP_KERNEL);
		अगर (!hem->addr) अणु
			kमुक्त(hem);
			वापस शून्य;
		पूर्ण
	पूर्ण

	hem->count = count;
	hem->start = start;
	hem->end = end;
	INIT_LIST_HEAD(&hem->list);
	INIT_LIST_HEAD(&hem->sibling);

	वापस hem;
पूर्ण

अटल व्योम hem_list_मुक्त_item(काष्ठा hns_roce_dev *hr_dev,
			       काष्ठा roce_hem_item *hem, bool exist_bt)
अणु
	अगर (exist_bt)
		dma_मुक्त_coherent(hr_dev->dev, hem->count * BA_BYTE_LEN,
				  hem->addr, hem->dma_addr);
	kमुक्त(hem);
पूर्ण

अटल व्योम hem_list_मुक्त_all(काष्ठा hns_roce_dev *hr_dev,
			      काष्ठा list_head *head, bool exist_bt)
अणु
	काष्ठा roce_hem_item *hem, *temp_hem;

	list_क्रम_each_entry_safe(hem, temp_hem, head, list) अणु
		list_del(&hem->list);
		hem_list_मुक्त_item(hr_dev, hem, exist_bt);
	पूर्ण
पूर्ण

अटल व्योम hem_list_link_bt(काष्ठा hns_roce_dev *hr_dev, व्योम *base_addr,
			     u64 table_addr)
अणु
	*(u64 *)(base_addr) = table_addr;
पूर्ण

/* assign L0 table address to hem from root bt */
अटल व्योम hem_list_assign_bt(काष्ठा hns_roce_dev *hr_dev,
			       काष्ठा roce_hem_item *hem, व्योम *cpu_addr,
			       u64 phy_addr)
अणु
	hem->addr = cpu_addr;
	hem->dma_addr = (dma_addr_t)phy_addr;
पूर्ण

अटल अंतरभूत bool hem_list_page_is_in_range(काष्ठा roce_hem_item *hem,
					     पूर्णांक offset)
अणु
	वापस (hem->start <= offset && offset <= hem->end);
पूर्ण

अटल काष्ठा roce_hem_item *hem_list_search_item(काष्ठा list_head *ba_list,
						    पूर्णांक page_offset)
अणु
	काष्ठा roce_hem_item *hem, *temp_hem;
	काष्ठा roce_hem_item *found = शून्य;

	list_क्रम_each_entry_safe(hem, temp_hem, ba_list, list) अणु
		अगर (hem_list_page_is_in_range(hem, page_offset)) अणु
			found = hem;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस found;
पूर्ण

अटल bool hem_list_is_bottom_bt(पूर्णांक hopnum, पूर्णांक bt_level)
अणु
	/*
	 * hopnum    base address table levels
	 * 0		L0(buf)
	 * 1		L0 -> buf
	 * 2		L0 -> L1 -> buf
	 * 3		L0 -> L1 -> L2 -> buf
	 */
	वापस bt_level >= (hopnum ? hopnum - 1 : hopnum);
पूर्ण

/**
 * calc base address entries num
 * @hopnum: num of mutihop addressing
 * @bt_level: base address table level
 * @unit: ba entries per bt page
 */
अटल u32 hem_list_calc_ba_range(पूर्णांक hopnum, पूर्णांक bt_level, पूर्णांक unit)
अणु
	u32 step;
	पूर्णांक max;
	पूर्णांक i;

	अगर (hopnum <= bt_level)
		वापस 0;
	/*
	 * hopnum  bt_level   range
	 * 1	      0       unit
	 * ------------
	 * 2	      0       unit * unit
	 * 2	      1       unit
	 * ------------
	 * 3	      0       unit * unit * unit
	 * 3	      1       unit * unit
	 * 3	      2       unit
	 */
	step = 1;
	max = hopnum - bt_level;
	क्रम (i = 0; i < max; i++)
		step = step * unit;

	वापस step;
पूर्ण

/**
 * calc the root ba entries which could cover all regions
 * @regions: buf region array
 * @region_cnt: array size of @regions
 * @unit: ba entries per bt page
 */
पूर्णांक hns_roce_hem_list_calc_root_ba(स्थिर काष्ठा hns_roce_buf_region *regions,
				   पूर्णांक region_cnt, पूर्णांक unit)
अणु
	काष्ठा hns_roce_buf_region *r;
	पूर्णांक total = 0;
	पूर्णांक step;
	पूर्णांक i;

	क्रम (i = 0; i < region_cnt; i++) अणु
		r = (काष्ठा hns_roce_buf_region *)&regions[i];
		अगर (r->hopnum > 1) अणु
			step = hem_list_calc_ba_range(r->hopnum, 1, unit);
			अगर (step > 0)
				total += (r->count + step - 1) / step;
		पूर्ण अन्यथा अणु
			total += r->count;
		पूर्ण
	पूर्ण

	वापस total;
पूर्ण

अटल पूर्णांक hem_list_alloc_mid_bt(काष्ठा hns_roce_dev *hr_dev,
				 स्थिर काष्ठा hns_roce_buf_region *r, पूर्णांक unit,
				 पूर्णांक offset, काष्ठा list_head *mid_bt,
				 काष्ठा list_head *bपंचांग_bt)
अणु
	काष्ठा roce_hem_item *hem_ptrs[HNS_ROCE_MAX_BT_LEVEL] = अणु शून्य पूर्ण;
	काष्ठा list_head temp_list[HNS_ROCE_MAX_BT_LEVEL];
	काष्ठा roce_hem_item *cur, *pre;
	स्थिर पूर्णांक hopnum = r->hopnum;
	पूर्णांक start_aligned;
	पूर्णांक distance;
	पूर्णांक ret = 0;
	पूर्णांक max_ofs;
	पूर्णांक level;
	u32 step;
	पूर्णांक end;

	अगर (hopnum <= 1)
		वापस 0;

	अगर (hopnum > HNS_ROCE_MAX_BT_LEVEL) अणु
		dev_err(hr_dev->dev, "invalid hopnum %d!\n", hopnum);
		वापस -EINVAL;
	पूर्ण

	अगर (offset < r->offset) अणु
		dev_err(hr_dev->dev, "invalid offset %d, min %u!\n",
			offset, r->offset);
		वापस -EINVAL;
	पूर्ण

	distance = offset - r->offset;
	max_ofs = r->offset + r->count - 1;
	क्रम (level = 0; level < hopnum; level++)
		INIT_LIST_HEAD(&temp_list[level]);

	/* config L1 bt to last bt and link them to corresponding parent */
	क्रम (level = 1; level < hopnum; level++) अणु
		cur = hem_list_search_item(&mid_bt[level], offset);
		अगर (cur) अणु
			hem_ptrs[level] = cur;
			जारी;
		पूर्ण

		step = hem_list_calc_ba_range(hopnum, level, unit);
		अगर (step < 1) अणु
			ret = -EINVAL;
			जाओ err_निकास;
		पूर्ण

		start_aligned = (distance / step) * step + r->offset;
		end = min_t(पूर्णांक, start_aligned + step - 1, max_ofs);
		cur = hem_list_alloc_item(hr_dev, start_aligned, end, unit,
					  true, level);
		अगर (!cur) अणु
			ret = -ENOMEM;
			जाओ err_निकास;
		पूर्ण
		hem_ptrs[level] = cur;
		list_add(&cur->list, &temp_list[level]);
		अगर (hem_list_is_bottom_bt(hopnum, level))
			list_add(&cur->sibling, &temp_list[0]);

		/* link bt to parent bt */
		अगर (level > 1) अणु
			pre = hem_ptrs[level - 1];
			step = (cur->start - pre->start) / step * BA_BYTE_LEN;
			hem_list_link_bt(hr_dev, pre->addr + step,
					 cur->dma_addr);
		पूर्ण
	पूर्ण

	list_splice(&temp_list[0], bपंचांग_bt);
	क्रम (level = 1; level < hopnum; level++)
		list_splice(&temp_list[level], &mid_bt[level]);

	वापस 0;

err_निकास:
	क्रम (level = 1; level < hopnum; level++)
		hem_list_मुक्त_all(hr_dev, &temp_list[level], true);

	वापस ret;
पूर्ण

अटल पूर्णांक hem_list_alloc_root_bt(काष्ठा hns_roce_dev *hr_dev,
				  काष्ठा hns_roce_hem_list *hem_list, पूर्णांक unit,
				  स्थिर काष्ठा hns_roce_buf_region *regions,
				  पूर्णांक region_cnt)
अणु
	काष्ठा list_head temp_list[HNS_ROCE_MAX_BT_REGION];
	काष्ठा roce_hem_item *hem, *temp_hem, *root_hem;
	स्थिर काष्ठा hns_roce_buf_region *r;
	काष्ठा list_head temp_root;
	काष्ठा list_head temp_bपंचांग;
	व्योम *cpu_base;
	u64 phy_base;
	पूर्णांक ret = 0;
	पूर्णांक ba_num;
	पूर्णांक offset;
	पूर्णांक total;
	पूर्णांक step;
	पूर्णांक i;

	r = &regions[0];
	root_hem = hem_list_search_item(&hem_list->root_bt, r->offset);
	अगर (root_hem)
		वापस 0;

	ba_num = hns_roce_hem_list_calc_root_ba(regions, region_cnt, unit);
	अगर (ba_num < 1)
		वापस -ENOMEM;

	अगर (ba_num > unit)
		वापस -ENOBUFS;

	ba_num = min_t(पूर्णांक, ba_num, unit);
	INIT_LIST_HEAD(&temp_root);
	offset = r->offset;
	/* indicate to last region */
	r = &regions[region_cnt - 1];
	root_hem = hem_list_alloc_item(hr_dev, offset, r->offset + r->count - 1,
				       ba_num, true, 0);
	अगर (!root_hem)
		वापस -ENOMEM;
	list_add(&root_hem->list, &temp_root);

	hem_list->root_ba = root_hem->dma_addr;

	INIT_LIST_HEAD(&temp_bपंचांग);
	क्रम (i = 0; i < region_cnt; i++)
		INIT_LIST_HEAD(&temp_list[i]);

	total = 0;
	क्रम (i = 0; i < region_cnt && total < ba_num; i++) अणु
		r = &regions[i];
		अगर (!r->count)
			जारी;

		/* all regions's mid[x][0] shared the root_bt's trunk */
		cpu_base = root_hem->addr + total * BA_BYTE_LEN;
		phy_base = root_hem->dma_addr + total * BA_BYTE_LEN;

		/* अगर hopnum is 0 or 1, cut a new fake hem from the root bt
		 * which's address share to all regions.
		 */
		अगर (hem_list_is_bottom_bt(r->hopnum, 0)) अणु
			hem = hem_list_alloc_item(hr_dev, r->offset,
						  r->offset + r->count - 1,
						  r->count, false, 0);
			अगर (!hem) अणु
				ret = -ENOMEM;
				जाओ err_निकास;
			पूर्ण
			hem_list_assign_bt(hr_dev, hem, cpu_base, phy_base);
			list_add(&hem->list, &temp_list[i]);
			list_add(&hem->sibling, &temp_bपंचांग);
			total += r->count;
		पूर्ण अन्यथा अणु
			step = hem_list_calc_ba_range(r->hopnum, 1, unit);
			अगर (step < 1) अणु
				ret = -EINVAL;
				जाओ err_निकास;
			पूर्ण
			/* अगर exist mid bt, link L1 to L0 */
			list_क्रम_each_entry_safe(hem, temp_hem,
					  &hem_list->mid_bt[i][1], list) अणु
				offset = (hem->start - r->offset) / step *
					  BA_BYTE_LEN;
				hem_list_link_bt(hr_dev, cpu_base + offset,
						 hem->dma_addr);
				total++;
			पूर्ण
		पूर्ण
	पूर्ण

	list_splice(&temp_bपंचांग, &hem_list->bपंचांग_bt);
	list_splice(&temp_root, &hem_list->root_bt);
	क्रम (i = 0; i < region_cnt; i++)
		list_splice(&temp_list[i], &hem_list->mid_bt[i][0]);

	वापस 0;

err_निकास:
	क्रम (i = 0; i < region_cnt; i++)
		hem_list_मुक्त_all(hr_dev, &temp_list[i], false);

	hem_list_मुक्त_all(hr_dev, &temp_root, true);

	वापस ret;
पूर्ण

/* स्थिरruct the base address table and link them by address hop config */
पूर्णांक hns_roce_hem_list_request(काष्ठा hns_roce_dev *hr_dev,
			      काष्ठा hns_roce_hem_list *hem_list,
			      स्थिर काष्ठा hns_roce_buf_region *regions,
			      पूर्णांक region_cnt, अचिन्हित पूर्णांक bt_pg_shअगरt)
अणु
	स्थिर काष्ठा hns_roce_buf_region *r;
	पूर्णांक ofs, end;
	पूर्णांक unit;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (region_cnt > HNS_ROCE_MAX_BT_REGION) अणु
		dev_err(hr_dev->dev, "invalid region region_cnt %d!\n",
			region_cnt);
		वापस -EINVAL;
	पूर्ण

	unit = (1 << bt_pg_shअगरt) / BA_BYTE_LEN;
	क्रम (i = 0; i < region_cnt; i++) अणु
		r = &regions[i];
		अगर (!r->count)
			जारी;

		end = r->offset + r->count;
		क्रम (ofs = r->offset; ofs < end; ofs += unit) अणु
			ret = hem_list_alloc_mid_bt(hr_dev, r, unit, ofs,
						    hem_list->mid_bt[i],
						    &hem_list->bपंचांग_bt);
			अगर (ret) अणु
				dev_err(hr_dev->dev,
					"alloc hem trunk fail ret=%d!\n", ret);
				जाओ err_alloc;
			पूर्ण
		पूर्ण
	पूर्ण

	ret = hem_list_alloc_root_bt(hr_dev, hem_list, unit, regions,
				     region_cnt);
	अगर (ret)
		dev_err(hr_dev->dev, "alloc hem root fail ret=%d!\n", ret);
	अन्यथा
		वापस 0;

err_alloc:
	hns_roce_hem_list_release(hr_dev, hem_list);

	वापस ret;
पूर्ण

व्योम hns_roce_hem_list_release(काष्ठा hns_roce_dev *hr_dev,
			       काष्ठा hns_roce_hem_list *hem_list)
अणु
	पूर्णांक i, j;

	क्रम (i = 0; i < HNS_ROCE_MAX_BT_REGION; i++)
		क्रम (j = 0; j < HNS_ROCE_MAX_BT_LEVEL; j++)
			hem_list_मुक्त_all(hr_dev, &hem_list->mid_bt[i][j],
					  j != 0);

	hem_list_मुक्त_all(hr_dev, &hem_list->root_bt, true);
	INIT_LIST_HEAD(&hem_list->bपंचांग_bt);
	hem_list->root_ba = 0;
पूर्ण

व्योम hns_roce_hem_list_init(काष्ठा hns_roce_hem_list *hem_list)
अणु
	पूर्णांक i, j;

	INIT_LIST_HEAD(&hem_list->root_bt);
	INIT_LIST_HEAD(&hem_list->bपंचांग_bt);
	क्रम (i = 0; i < HNS_ROCE_MAX_BT_REGION; i++)
		क्रम (j = 0; j < HNS_ROCE_MAX_BT_LEVEL; j++)
			INIT_LIST_HEAD(&hem_list->mid_bt[i][j]);
पूर्ण

व्योम *hns_roce_hem_list_find_mtt(काष्ठा hns_roce_dev *hr_dev,
				 काष्ठा hns_roce_hem_list *hem_list,
				 पूर्णांक offset, पूर्णांक *mtt_cnt, u64 *phy_addr)
अणु
	काष्ठा list_head *head = &hem_list->bपंचांग_bt;
	काष्ठा roce_hem_item *hem, *temp_hem;
	व्योम *cpu_base = शून्य;
	u64 phy_base = 0;
	पूर्णांक nr = 0;

	list_क्रम_each_entry_safe(hem, temp_hem, head, sibling) अणु
		अगर (hem_list_page_is_in_range(hem, offset)) अणु
			nr = offset - hem->start;
			cpu_base = hem->addr + nr * BA_BYTE_LEN;
			phy_base = hem->dma_addr + nr * BA_BYTE_LEN;
			nr = hem->end + 1 - offset;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (mtt_cnt)
		*mtt_cnt = nr;

	अगर (phy_addr)
		*phy_addr = phy_base;

	वापस cpu_base;
पूर्ण
