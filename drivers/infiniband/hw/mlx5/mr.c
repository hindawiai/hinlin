<शैली गुरु>
/*
 * Copyright (c) 2013-2015, Mellanox Technologies. All rights reserved.
 * Copyright (c) 2020, Intel Corporation. All rights reserved.
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


#समावेश <linux/kref.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/export.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-buf.h>
#समावेश <linux/dma-resv.h>
#समावेश <rdma/ib_uस्मृति.स>
#समावेश <rdma/ib_umem_odp.h>
#समावेश <rdma/ib_verbs.h>
#समावेश "dm.h"
#समावेश "mlx5_ib.h"

/*
 * We can't use an array for xlt_emergency_page because dma_map_single doesn't
 * work on kernel modules memory
 */
व्योम *xlt_emergency_page;
अटल DEFINE_MUTEX(xlt_emergency_page_mutex);

क्रमागत अणु
	MAX_PENDING_REG_MR = 8,
पूर्ण;

#घोषणा MLX5_UMR_ALIGN 2048

अटल व्योम
create_mkey_callback(पूर्णांक status, काष्ठा mlx5_async_work *context);
अटल काष्ठा mlx5_ib_mr *reg_create(काष्ठा ib_pd *pd, काष्ठा ib_umem *umem,
				     u64 iova, पूर्णांक access_flags,
				     अचिन्हित पूर्णांक page_size, bool populate);

अटल व्योम set_mkc_access_pd_addr_fields(व्योम *mkc, पूर्णांक acc, u64 start_addr,
					  काष्ठा ib_pd *pd)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(pd->device);

	MLX5_SET(mkc, mkc, a, !!(acc & IB_ACCESS_REMOTE_ATOMIC));
	MLX5_SET(mkc, mkc, rw, !!(acc & IB_ACCESS_REMOTE_WRITE));
	MLX5_SET(mkc, mkc, rr, !!(acc & IB_ACCESS_REMOTE_READ));
	MLX5_SET(mkc, mkc, lw, !!(acc & IB_ACCESS_LOCAL_WRITE));
	MLX5_SET(mkc, mkc, lr, 1);

	अगर (MLX5_CAP_GEN(dev->mdev, relaxed_ordering_ग_लिखो))
		MLX5_SET(mkc, mkc, relaxed_ordering_ग_लिखो,
			 !!(acc & IB_ACCESS_RELAXED_ORDERING));
	अगर (MLX5_CAP_GEN(dev->mdev, relaxed_ordering_पढ़ो))
		MLX5_SET(mkc, mkc, relaxed_ordering_पढ़ो,
			 !!(acc & IB_ACCESS_RELAXED_ORDERING));

	MLX5_SET(mkc, mkc, pd, to_mpd(pd)->pdn);
	MLX5_SET(mkc, mkc, qpn, 0xffffff);
	MLX5_SET64(mkc, mkc, start_addr, start_addr);
पूर्ण

अटल व्योम
assign_mkey_variant(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_core_mkey *mkey,
		    u32 *in)
अणु
	u8 key = atomic_inc_वापस(&dev->mkey_var);
	व्योम *mkc;

	mkc = MLX5_ADDR_OF(create_mkey_in, in, memory_key_mkey_entry);
	MLX5_SET(mkc, mkc, mkey_7_0, key);
	mkey->key = key;
पूर्ण

अटल पूर्णांक
mlx5_ib_create_mkey(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_core_mkey *mkey,
		    u32 *in, पूर्णांक inlen)
अणु
	assign_mkey_variant(dev, mkey, in);
	वापस mlx5_core_create_mkey(dev->mdev, mkey, in, inlen);
पूर्ण

अटल पूर्णांक
mlx5_ib_create_mkey_cb(काष्ठा mlx5_ib_dev *dev,
		       काष्ठा mlx5_core_mkey *mkey,
		       काष्ठा mlx5_async_ctx *async_ctx,
		       u32 *in, पूर्णांक inlen, u32 *out, पूर्णांक outlen,
		       काष्ठा mlx5_async_work *context)
अणु
	MLX5_SET(create_mkey_in, in, opcode, MLX5_CMD_OP_CREATE_MKEY);
	assign_mkey_variant(dev, mkey, in);
	वापस mlx5_cmd_exec_cb(async_ctx, in, inlen, out, outlen,
				create_mkey_callback, context);
पूर्ण

अटल पूर्णांक mr_cache_max_order(काष्ठा mlx5_ib_dev *dev);
अटल व्योम queue_adjust_cache_locked(काष्ठा mlx5_cache_ent *ent);

अटल bool umr_can_use_indirect_mkey(काष्ठा mlx5_ib_dev *dev)
अणु
	वापस !MLX5_CAP_GEN(dev->mdev, umr_indirect_mkey_disabled);
पूर्ण

अटल पूर्णांक destroy_mkey(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_ib_mr *mr)
अणु
	WARN_ON(xa_load(&dev->odp_mkeys, mlx5_base_mkey(mr->mmkey.key)));

	वापस mlx5_core_destroy_mkey(dev->mdev, &mr->mmkey);
पूर्ण

अटल व्योम create_mkey_callback(पूर्णांक status, काष्ठा mlx5_async_work *context)
अणु
	काष्ठा mlx5_ib_mr *mr =
		container_of(context, काष्ठा mlx5_ib_mr, cb_work);
	काष्ठा mlx5_cache_ent *ent = mr->cache_ent;
	काष्ठा mlx5_ib_dev *dev = ent->dev;
	अचिन्हित दीर्घ flags;

	अगर (status) अणु
		mlx5_ib_warn(dev, "async reg mr failed. status %d\n", status);
		kमुक्त(mr);
		spin_lock_irqsave(&ent->lock, flags);
		ent->pending--;
		WRITE_ONCE(dev->fill_delay, 1);
		spin_unlock_irqrestore(&ent->lock, flags);
		mod_समयr(&dev->delay_समयr, jअगरfies + HZ);
		वापस;
	पूर्ण

	mr->mmkey.type = MLX5_MKEY_MR;
	mr->mmkey.key |= mlx5_idx_to_mkey(
		MLX5_GET(create_mkey_out, mr->out, mkey_index));
	init_रुकोqueue_head(&mr->mmkey.रुको);

	WRITE_ONCE(dev->cache.last_add, jअगरfies);

	spin_lock_irqsave(&ent->lock, flags);
	list_add_tail(&mr->list, &ent->head);
	ent->available_mrs++;
	ent->total_mrs++;
	/* If we are करोing fill_to_high_water then keep going. */
	queue_adjust_cache_locked(ent);
	ent->pending--;
	spin_unlock_irqrestore(&ent->lock, flags);
पूर्ण

अटल काष्ठा mlx5_ib_mr *alloc_cache_mr(काष्ठा mlx5_cache_ent *ent, व्योम *mkc)
अणु
	काष्ठा mlx5_ib_mr *mr;

	mr = kzalloc(माप(*mr), GFP_KERNEL);
	अगर (!mr)
		वापस शून्य;
	mr->cache_ent = ent;

	set_mkc_access_pd_addr_fields(mkc, 0, 0, ent->dev->umrc.pd);
	MLX5_SET(mkc, mkc, मुक्त, 1);
	MLX5_SET(mkc, mkc, umr_en, 1);
	MLX5_SET(mkc, mkc, access_mode_1_0, ent->access_mode & 0x3);
	MLX5_SET(mkc, mkc, access_mode_4_2, (ent->access_mode >> 2) & 0x7);

	MLX5_SET(mkc, mkc, translations_octword_size, ent->xlt);
	MLX5_SET(mkc, mkc, log_page_size, ent->page);
	वापस mr;
पूर्ण

/* Asynchronously schedule new MRs to be populated in the cache. */
अटल पूर्णांक add_keys(काष्ठा mlx5_cache_ent *ent, अचिन्हित पूर्णांक num)
अणु
	माप_प्रकार inlen = MLX5_ST_SZ_BYTES(create_mkey_in);
	काष्ठा mlx5_ib_mr *mr;
	व्योम *mkc;
	u32 *in;
	पूर्णांक err = 0;
	पूर्णांक i;

	in = kzalloc(inlen, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	mkc = MLX5_ADDR_OF(create_mkey_in, in, memory_key_mkey_entry);
	क्रम (i = 0; i < num; i++) अणु
		mr = alloc_cache_mr(ent, mkc);
		अगर (!mr) अणु
			err = -ENOMEM;
			अवरोध;
		पूर्ण
		spin_lock_irq(&ent->lock);
		अगर (ent->pending >= MAX_PENDING_REG_MR) अणु
			err = -EAGAIN;
			spin_unlock_irq(&ent->lock);
			kमुक्त(mr);
			अवरोध;
		पूर्ण
		ent->pending++;
		spin_unlock_irq(&ent->lock);
		err = mlx5_ib_create_mkey_cb(ent->dev, &mr->mmkey,
					     &ent->dev->async_ctx, in, inlen,
					     mr->out, माप(mr->out),
					     &mr->cb_work);
		अगर (err) अणु
			spin_lock_irq(&ent->lock);
			ent->pending--;
			spin_unlock_irq(&ent->lock);
			mlx5_ib_warn(ent->dev, "create mkey failed %d\n", err);
			kमुक्त(mr);
			अवरोध;
		पूर्ण
	पूर्ण

	kमुक्त(in);
	वापस err;
पूर्ण

/* Synchronously create a MR in the cache */
अटल काष्ठा mlx5_ib_mr *create_cache_mr(काष्ठा mlx5_cache_ent *ent)
अणु
	माप_प्रकार inlen = MLX5_ST_SZ_BYTES(create_mkey_in);
	काष्ठा mlx5_ib_mr *mr;
	व्योम *mkc;
	u32 *in;
	पूर्णांक err;

	in = kzalloc(inlen, GFP_KERNEL);
	अगर (!in)
		वापस ERR_PTR(-ENOMEM);
	mkc = MLX5_ADDR_OF(create_mkey_in, in, memory_key_mkey_entry);

	mr = alloc_cache_mr(ent, mkc);
	अगर (!mr) अणु
		err = -ENOMEM;
		जाओ मुक्त_in;
	पूर्ण

	err = mlx5_core_create_mkey(ent->dev->mdev, &mr->mmkey, in, inlen);
	अगर (err)
		जाओ मुक्त_mr;

	mr->mmkey.type = MLX5_MKEY_MR;
	WRITE_ONCE(ent->dev->cache.last_add, jअगरfies);
	spin_lock_irq(&ent->lock);
	ent->total_mrs++;
	spin_unlock_irq(&ent->lock);
	kमुक्त(in);
	वापस mr;
मुक्त_mr:
	kमुक्त(mr);
मुक्त_in:
	kमुक्त(in);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम हटाओ_cache_mr_locked(काष्ठा mlx5_cache_ent *ent)
अणु
	काष्ठा mlx5_ib_mr *mr;

	lockdep_निश्चित_held(&ent->lock);
	अगर (list_empty(&ent->head))
		वापस;
	mr = list_first_entry(&ent->head, काष्ठा mlx5_ib_mr, list);
	list_del(&mr->list);
	ent->available_mrs--;
	ent->total_mrs--;
	spin_unlock_irq(&ent->lock);
	mlx5_core_destroy_mkey(ent->dev->mdev, &mr->mmkey);
	kमुक्त(mr);
	spin_lock_irq(&ent->lock);
पूर्ण

अटल पूर्णांक resize_available_mrs(काष्ठा mlx5_cache_ent *ent, अचिन्हित पूर्णांक target,
				bool limit_fill)
अणु
	पूर्णांक err;

	lockdep_निश्चित_held(&ent->lock);

	जबतक (true) अणु
		अगर (limit_fill)
			target = ent->limit * 2;
		अगर (target == ent->available_mrs + ent->pending)
			वापस 0;
		अगर (target > ent->available_mrs + ent->pending) अणु
			u32 toकरो = target - (ent->available_mrs + ent->pending);

			spin_unlock_irq(&ent->lock);
			err = add_keys(ent, toकरो);
			अगर (err == -EAGAIN)
				usleep_range(3000, 5000);
			spin_lock_irq(&ent->lock);
			अगर (err) अणु
				अगर (err != -EAGAIN)
					वापस err;
			पूर्ण अन्यथा
				वापस 0;
		पूर्ण अन्यथा अणु
			हटाओ_cache_mr_locked(ent);
		पूर्ण
	पूर्ण
पूर्ण

अटल sमाप_प्रकार size_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *buf,
			  माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा mlx5_cache_ent *ent = filp->निजी_data;
	u32 target;
	पूर्णांक err;

	err = kstrtou32_from_user(buf, count, 0, &target);
	अगर (err)
		वापस err;

	/*
	 * Target is the new value of total_mrs the user requests, however we
	 * cannot मुक्त MRs that are in use. Compute the target value क्रम
	 * available_mrs.
	 */
	spin_lock_irq(&ent->lock);
	अगर (target < ent->total_mrs - ent->available_mrs) अणु
		err = -EINVAL;
		जाओ err_unlock;
	पूर्ण
	target = target - (ent->total_mrs - ent->available_mrs);
	अगर (target < ent->limit || target > ent->limit*2) अणु
		err = -EINVAL;
		जाओ err_unlock;
	पूर्ण
	err = resize_available_mrs(ent, target, false);
	अगर (err)
		जाओ err_unlock;
	spin_unlock_irq(&ent->lock);

	वापस count;

err_unlock:
	spin_unlock_irq(&ent->lock);
	वापस err;
पूर्ण

अटल sमाप_प्रकार size_पढ़ो(काष्ठा file *filp, अक्षर __user *buf, माप_प्रकार count,
			 loff_t *pos)
अणु
	काष्ठा mlx5_cache_ent *ent = filp->निजी_data;
	अक्षर lbuf[20];
	पूर्णांक err;

	err = snम_लिखो(lbuf, माप(lbuf), "%d\n", ent->total_mrs);
	अगर (err < 0)
		वापस err;

	वापस simple_पढ़ो_from_buffer(buf, count, pos, lbuf, err);
पूर्ण

अटल स्थिर काष्ठा file_operations size_fops = अणु
	.owner	= THIS_MODULE,
	.खोलो	= simple_खोलो,
	.ग_लिखो	= size_ग_लिखो,
	.पढ़ो	= size_पढ़ो,
पूर्ण;

अटल sमाप_प्रकार limit_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *buf,
			   माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा mlx5_cache_ent *ent = filp->निजी_data;
	u32 var;
	पूर्णांक err;

	err = kstrtou32_from_user(buf, count, 0, &var);
	अगर (err)
		वापस err;

	/*
	 * Upon set we immediately fill the cache to high water mark implied by
	 * the limit.
	 */
	spin_lock_irq(&ent->lock);
	ent->limit = var;
	err = resize_available_mrs(ent, 0, true);
	spin_unlock_irq(&ent->lock);
	अगर (err)
		वापस err;
	वापस count;
पूर्ण

अटल sमाप_प्रकार limit_पढ़ो(काष्ठा file *filp, अक्षर __user *buf, माप_प्रकार count,
			  loff_t *pos)
अणु
	काष्ठा mlx5_cache_ent *ent = filp->निजी_data;
	अक्षर lbuf[20];
	पूर्णांक err;

	err = snम_लिखो(lbuf, माप(lbuf), "%d\n", ent->limit);
	अगर (err < 0)
		वापस err;

	वापस simple_पढ़ो_from_buffer(buf, count, pos, lbuf, err);
पूर्ण

अटल स्थिर काष्ठा file_operations limit_fops = अणु
	.owner	= THIS_MODULE,
	.खोलो	= simple_खोलो,
	.ग_लिखो	= limit_ग_लिखो,
	.पढ़ो	= limit_पढ़ो,
पूर्ण;

अटल bool someone_adding(काष्ठा mlx5_mr_cache *cache)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < MAX_MR_CACHE_ENTRIES; i++) अणु
		काष्ठा mlx5_cache_ent *ent = &cache->ent[i];
		bool ret;

		spin_lock_irq(&ent->lock);
		ret = ent->available_mrs < ent->limit;
		spin_unlock_irq(&ent->lock);
		अगर (ret)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

/*
 * Check अगर the bucket is outside the high/low water mark and schedule an async
 * update. The cache refill has hysteresis, once the low water mark is hit it is
 * refilled up to the high mark.
 */
अटल व्योम queue_adjust_cache_locked(काष्ठा mlx5_cache_ent *ent)
अणु
	lockdep_निश्चित_held(&ent->lock);

	अगर (ent->disabled || READ_ONCE(ent->dev->fill_delay))
		वापस;
	अगर (ent->available_mrs < ent->limit) अणु
		ent->fill_to_high_water = true;
		queue_work(ent->dev->cache.wq, &ent->work);
	पूर्ण अन्यथा अगर (ent->fill_to_high_water &&
		   ent->available_mrs + ent->pending < 2 * ent->limit) अणु
		/*
		 * Once we start populating due to hitting a low water mark
		 * जारी until we pass the high water mark.
		 */
		queue_work(ent->dev->cache.wq, &ent->work);
	पूर्ण अन्यथा अगर (ent->available_mrs == 2 * ent->limit) अणु
		ent->fill_to_high_water = false;
	पूर्ण अन्यथा अगर (ent->available_mrs > 2 * ent->limit) अणु
		/* Queue deletion of excess entries */
		ent->fill_to_high_water = false;
		अगर (ent->pending)
			queue_delayed_work(ent->dev->cache.wq, &ent->dwork,
					   msecs_to_jअगरfies(1000));
		अन्यथा
			queue_work(ent->dev->cache.wq, &ent->work);
	पूर्ण
पूर्ण

अटल व्योम __cache_work_func(काष्ठा mlx5_cache_ent *ent)
अणु
	काष्ठा mlx5_ib_dev *dev = ent->dev;
	काष्ठा mlx5_mr_cache *cache = &dev->cache;
	पूर्णांक err;

	spin_lock_irq(&ent->lock);
	अगर (ent->disabled)
		जाओ out;

	अगर (ent->fill_to_high_water &&
	    ent->available_mrs + ent->pending < 2 * ent->limit &&
	    !READ_ONCE(dev->fill_delay)) अणु
		spin_unlock_irq(&ent->lock);
		err = add_keys(ent, 1);
		spin_lock_irq(&ent->lock);
		अगर (ent->disabled)
			जाओ out;
		अगर (err) अणु
			/*
			 * EAGAIN only happens अगर pending is positive, so we
			 * will be rescheduled from reg_mr_callback(). The only
			 * failure path here is ENOMEM.
			 */
			अगर (err != -EAGAIN) अणु
				mlx5_ib_warn(
					dev,
					"command failed order %d, err %d\n",
					ent->order, err);
				queue_delayed_work(cache->wq, &ent->dwork,
						   msecs_to_jअगरfies(1000));
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (ent->available_mrs > 2 * ent->limit) अणु
		bool need_delay;

		/*
		 * The हटाओ_cache_mr() logic is perक्रमmed as garbage
		 * collection task. Such task is पूर्णांकended to be run when no
		 * other active processes are running.
		 *
		 * The need_resched() will वापस TRUE अगर there are user tasks
		 * to be activated in near future.
		 *
		 * In such हाल, we करोn't execute हटाओ_cache_mr() and postpone
		 * the garbage collection work to try to run in next cycle, in
		 * order to मुक्त CPU resources to other tasks.
		 */
		spin_unlock_irq(&ent->lock);
		need_delay = need_resched() || someone_adding(cache) ||
			     समय_after(jअगरfies,
					READ_ONCE(cache->last_add) + 300 * HZ);
		spin_lock_irq(&ent->lock);
		अगर (ent->disabled)
			जाओ out;
		अगर (need_delay)
			queue_delayed_work(cache->wq, &ent->dwork, 300 * HZ);
		हटाओ_cache_mr_locked(ent);
		queue_adjust_cache_locked(ent);
	पूर्ण
out:
	spin_unlock_irq(&ent->lock);
पूर्ण

अटल व्योम delayed_cache_work_func(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlx5_cache_ent *ent;

	ent = container_of(work, काष्ठा mlx5_cache_ent, dwork.work);
	__cache_work_func(ent);
पूर्ण

अटल व्योम cache_work_func(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlx5_cache_ent *ent;

	ent = container_of(work, काष्ठा mlx5_cache_ent, work);
	__cache_work_func(ent);
पूर्ण

/* Allocate a special entry from the cache */
काष्ठा mlx5_ib_mr *mlx5_mr_cache_alloc(काष्ठा mlx5_ib_dev *dev,
				       अचिन्हित पूर्णांक entry, पूर्णांक access_flags)
अणु
	काष्ठा mlx5_mr_cache *cache = &dev->cache;
	काष्ठा mlx5_cache_ent *ent;
	काष्ठा mlx5_ib_mr *mr;

	अगर (WARN_ON(entry <= MR_CACHE_LAST_STD_ENTRY ||
		    entry >= ARRAY_SIZE(cache->ent)))
		वापस ERR_PTR(-EINVAL);

	/* Matches access in alloc_cache_mr() */
	अगर (!mlx5_ib_can_reconfig_with_umr(dev, 0, access_flags))
		वापस ERR_PTR(-EOPNOTSUPP);

	ent = &cache->ent[entry];
	spin_lock_irq(&ent->lock);
	अगर (list_empty(&ent->head)) अणु
		spin_unlock_irq(&ent->lock);
		mr = create_cache_mr(ent);
		अगर (IS_ERR(mr))
			वापस mr;
	पूर्ण अन्यथा अणु
		mr = list_first_entry(&ent->head, काष्ठा mlx5_ib_mr, list);
		list_del(&mr->list);
		ent->available_mrs--;
		queue_adjust_cache_locked(ent);
		spin_unlock_irq(&ent->lock);

		mlx5_clear_mr(mr);
	पूर्ण
	mr->access_flags = access_flags;
	वापस mr;
पूर्ण

/* Return a MR alपढ़ोy available in the cache */
अटल काष्ठा mlx5_ib_mr *get_cache_mr(काष्ठा mlx5_cache_ent *req_ent)
अणु
	काष्ठा mlx5_ib_dev *dev = req_ent->dev;
	काष्ठा mlx5_ib_mr *mr = शून्य;
	काष्ठा mlx5_cache_ent *ent = req_ent;

	/* Try larger MR pools from the cache to satisfy the allocation */
	क्रम (; ent != &dev->cache.ent[MR_CACHE_LAST_STD_ENTRY + 1]; ent++) अणु
		mlx5_ib_dbg(dev, "order %u, cache index %zu\n", ent->order,
			    ent - dev->cache.ent);

		spin_lock_irq(&ent->lock);
		अगर (!list_empty(&ent->head)) अणु
			mr = list_first_entry(&ent->head, काष्ठा mlx5_ib_mr,
					      list);
			list_del(&mr->list);
			ent->available_mrs--;
			queue_adjust_cache_locked(ent);
			spin_unlock_irq(&ent->lock);
			mlx5_clear_mr(mr);
			वापस mr;
		पूर्ण
		queue_adjust_cache_locked(ent);
		spin_unlock_irq(&ent->lock);
	पूर्ण
	req_ent->miss++;
	वापस शून्य;
पूर्ण

अटल व्योम mlx5_mr_cache_मुक्त(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_ib_mr *mr)
अणु
	काष्ठा mlx5_cache_ent *ent = mr->cache_ent;

	spin_lock_irq(&ent->lock);
	list_add_tail(&mr->list, &ent->head);
	ent->available_mrs++;
	queue_adjust_cache_locked(ent);
	spin_unlock_irq(&ent->lock);
पूर्ण

अटल व्योम clean_keys(काष्ठा mlx5_ib_dev *dev, पूर्णांक c)
अणु
	काष्ठा mlx5_mr_cache *cache = &dev->cache;
	काष्ठा mlx5_cache_ent *ent = &cache->ent[c];
	काष्ठा mlx5_ib_mr *पंचांगp_mr;
	काष्ठा mlx5_ib_mr *mr;
	LIST_HEAD(del_list);

	cancel_delayed_work(&ent->dwork);
	जबतक (1) अणु
		spin_lock_irq(&ent->lock);
		अगर (list_empty(&ent->head)) अणु
			spin_unlock_irq(&ent->lock);
			अवरोध;
		पूर्ण
		mr = list_first_entry(&ent->head, काष्ठा mlx5_ib_mr, list);
		list_move(&mr->list, &del_list);
		ent->available_mrs--;
		ent->total_mrs--;
		spin_unlock_irq(&ent->lock);
		mlx5_core_destroy_mkey(dev->mdev, &mr->mmkey);
	पूर्ण

	list_क्रम_each_entry_safe(mr, पंचांगp_mr, &del_list, list) अणु
		list_del(&mr->list);
		kमुक्त(mr);
	पूर्ण
पूर्ण

अटल व्योम mlx5_mr_cache_debugfs_cleanup(काष्ठा mlx5_ib_dev *dev)
अणु
	अगर (!mlx5_debugfs_root || dev->is_rep)
		वापस;

	debugfs_हटाओ_recursive(dev->cache.root);
	dev->cache.root = शून्य;
पूर्ण

अटल व्योम mlx5_mr_cache_debugfs_init(काष्ठा mlx5_ib_dev *dev)
अणु
	काष्ठा mlx5_mr_cache *cache = &dev->cache;
	काष्ठा mlx5_cache_ent *ent;
	काष्ठा dentry *dir;
	पूर्णांक i;

	अगर (!mlx5_debugfs_root || dev->is_rep)
		वापस;

	cache->root = debugfs_create_dir("mr_cache", dev->mdev->priv.dbg_root);

	क्रम (i = 0; i < MAX_MR_CACHE_ENTRIES; i++) अणु
		ent = &cache->ent[i];
		प्र_लिखो(ent->name, "%d", ent->order);
		dir = debugfs_create_dir(ent->name, cache->root);
		debugfs_create_file("size", 0600, dir, ent, &size_fops);
		debugfs_create_file("limit", 0600, dir, ent, &limit_fops);
		debugfs_create_u32("cur", 0400, dir, &ent->available_mrs);
		debugfs_create_u32("miss", 0600, dir, &ent->miss);
	पूर्ण
पूर्ण

अटल व्योम delay_समय_func(काष्ठा समयr_list *t)
अणु
	काष्ठा mlx5_ib_dev *dev = from_समयr(dev, t, delay_समयr);

	WRITE_ONCE(dev->fill_delay, 0);
पूर्ण

पूर्णांक mlx5_mr_cache_init(काष्ठा mlx5_ib_dev *dev)
अणु
	काष्ठा mlx5_mr_cache *cache = &dev->cache;
	काष्ठा mlx5_cache_ent *ent;
	पूर्णांक i;

	mutex_init(&dev->slow_path_mutex);
	cache->wq = alloc_ordered_workqueue("mkey_cache", WQ_MEM_RECLAIM);
	अगर (!cache->wq) अणु
		mlx5_ib_warn(dev, "failed to create work queue\n");
		वापस -ENOMEM;
	पूर्ण

	mlx5_cmd_init_async_ctx(dev->mdev, &dev->async_ctx);
	समयr_setup(&dev->delay_समयr, delay_समय_func, 0);
	क्रम (i = 0; i < MAX_MR_CACHE_ENTRIES; i++) अणु
		ent = &cache->ent[i];
		INIT_LIST_HEAD(&ent->head);
		spin_lock_init(&ent->lock);
		ent->order = i + 2;
		ent->dev = dev;
		ent->limit = 0;

		INIT_WORK(&ent->work, cache_work_func);
		INIT_DELAYED_WORK(&ent->dwork, delayed_cache_work_func);

		अगर (i > MR_CACHE_LAST_STD_ENTRY) अणु
			mlx5_odp_init_mr_cache_entry(ent);
			जारी;
		पूर्ण

		अगर (ent->order > mr_cache_max_order(dev))
			जारी;

		ent->page = PAGE_SHIFT;
		ent->xlt = (1 << ent->order) * माप(काष्ठा mlx5_mtt) /
			   MLX5_IB_UMR_OCTOWORD;
		ent->access_mode = MLX5_MKC_ACCESS_MODE_MTT;
		अगर ((dev->mdev->profile.mask & MLX5_PROF_MASK_MR_CACHE) &&
		    !dev->is_rep && mlx5_core_is_pf(dev->mdev) &&
		    mlx5_ib_can_load_pas_with_umr(dev, 0))
			ent->limit = dev->mdev->profile.mr_cache[i].limit;
		अन्यथा
			ent->limit = 0;
		spin_lock_irq(&ent->lock);
		queue_adjust_cache_locked(ent);
		spin_unlock_irq(&ent->lock);
	पूर्ण

	mlx5_mr_cache_debugfs_init(dev);

	वापस 0;
पूर्ण

पूर्णांक mlx5_mr_cache_cleanup(काष्ठा mlx5_ib_dev *dev)
अणु
	अचिन्हित पूर्णांक i;

	अगर (!dev->cache.wq)
		वापस 0;

	क्रम (i = 0; i < MAX_MR_CACHE_ENTRIES; i++) अणु
		काष्ठा mlx5_cache_ent *ent = &dev->cache.ent[i];

		spin_lock_irq(&ent->lock);
		ent->disabled = true;
		spin_unlock_irq(&ent->lock);
		cancel_work_sync(&ent->work);
		cancel_delayed_work_sync(&ent->dwork);
	पूर्ण

	mlx5_mr_cache_debugfs_cleanup(dev);
	mlx5_cmd_cleanup_async_ctx(&dev->async_ctx);

	क्रम (i = 0; i < MAX_MR_CACHE_ENTRIES; i++)
		clean_keys(dev, i);

	destroy_workqueue(dev->cache.wq);
	del_समयr_sync(&dev->delay_समयr);

	वापस 0;
पूर्ण

काष्ठा ib_mr *mlx5_ib_get_dma_mr(काष्ठा ib_pd *pd, पूर्णांक acc)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(pd->device);
	पूर्णांक inlen = MLX5_ST_SZ_BYTES(create_mkey_in);
	काष्ठा mlx5_ib_mr *mr;
	व्योम *mkc;
	u32 *in;
	पूर्णांक err;

	mr = kzalloc(माप(*mr), GFP_KERNEL);
	अगर (!mr)
		वापस ERR_PTR(-ENOMEM);

	in = kzalloc(inlen, GFP_KERNEL);
	अगर (!in) अणु
		err = -ENOMEM;
		जाओ err_मुक्त;
	पूर्ण

	mkc = MLX5_ADDR_OF(create_mkey_in, in, memory_key_mkey_entry);

	MLX5_SET(mkc, mkc, access_mode_1_0, MLX5_MKC_ACCESS_MODE_PA);
	MLX5_SET(mkc, mkc, length64, 1);
	set_mkc_access_pd_addr_fields(mkc, acc, 0, pd);

	err = mlx5_ib_create_mkey(dev, &mr->mmkey, in, inlen);
	अगर (err)
		जाओ err_in;

	kमुक्त(in);
	mr->mmkey.type = MLX5_MKEY_MR;
	mr->ibmr.lkey = mr->mmkey.key;
	mr->ibmr.rkey = mr->mmkey.key;
	mr->umem = शून्य;

	वापस &mr->ibmr;

err_in:
	kमुक्त(in);

err_मुक्त:
	kमुक्त(mr);

	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक get_octo_len(u64 addr, u64 len, पूर्णांक page_shअगरt)
अणु
	u64 page_size = 1ULL << page_shअगरt;
	u64 offset;
	पूर्णांक npages;

	offset = addr & (page_size - 1);
	npages = ALIGN(len + offset, page_size) >> page_shअगरt;
	वापस (npages + 1) / 2;
पूर्ण

अटल पूर्णांक mr_cache_max_order(काष्ठा mlx5_ib_dev *dev)
अणु
	अगर (MLX5_CAP_GEN(dev->mdev, umr_extended_translation_offset))
		वापस MR_CACHE_LAST_STD_ENTRY + 2;
	वापस MLX5_MAX_UMR_SHIFT;
पूर्ण

अटल व्योम mlx5_ib_umr_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	काष्ठा mlx5_ib_umr_context *context =
		container_of(wc->wr_cqe, काष्ठा mlx5_ib_umr_context, cqe);

	context->status = wc->status;
	complete(&context->करोne);
पूर्ण

अटल अंतरभूत व्योम mlx5_ib_init_umr_context(काष्ठा mlx5_ib_umr_context *context)
अणु
	context->cqe.करोne = mlx5_ib_umr_करोne;
	context->status = -1;
	init_completion(&context->करोne);
पूर्ण

अटल पूर्णांक mlx5_ib_post_send_रुको(काष्ठा mlx5_ib_dev *dev,
				  काष्ठा mlx5_umr_wr *umrwr)
अणु
	काष्ठा umr_common *umrc = &dev->umrc;
	स्थिर काष्ठा ib_send_wr *bad;
	पूर्णांक err;
	काष्ठा mlx5_ib_umr_context umr_context;

	mlx5_ib_init_umr_context(&umr_context);
	umrwr->wr.wr_cqe = &umr_context.cqe;

	करोwn(&umrc->sem);
	err = ib_post_send(umrc->qp, &umrwr->wr, &bad);
	अगर (err) अणु
		mlx5_ib_warn(dev, "UMR post send failed, err %d\n", err);
	पूर्ण अन्यथा अणु
		रुको_क्रम_completion(&umr_context.करोne);
		अगर (umr_context.status != IB_WC_SUCCESS) अणु
			mlx5_ib_warn(dev, "reg umr failed (%u)\n",
				     umr_context.status);
			err = -EFAULT;
		पूर्ण
	पूर्ण
	up(&umrc->sem);
	वापस err;
पूर्ण

अटल काष्ठा mlx5_cache_ent *mr_cache_ent_from_order(काष्ठा mlx5_ib_dev *dev,
						      अचिन्हित पूर्णांक order)
अणु
	काष्ठा mlx5_mr_cache *cache = &dev->cache;

	अगर (order < cache->ent[0].order)
		वापस &cache->ent[0];
	order = order - cache->ent[0].order;
	अगर (order > MR_CACHE_LAST_STD_ENTRY)
		वापस शून्य;
	वापस &cache->ent[order];
पूर्ण

अटल व्योम set_mr_fields(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_ib_mr *mr,
			  u64 length, पूर्णांक access_flags)
अणु
	mr->ibmr.lkey = mr->mmkey.key;
	mr->ibmr.rkey = mr->mmkey.key;
	mr->ibmr.length = length;
	mr->ibmr.device = &dev->ib_dev;
	mr->access_flags = access_flags;
पूर्ण

अटल अचिन्हित पूर्णांक mlx5_umem_dmabuf_शेष_pgsz(काष्ठा ib_umem *umem,
						  u64 iova)
अणु
	/*
	 * The alignment of iova has alपढ़ोy been checked upon entering
	 * UVERBS_METHOD_REG_DMABUF_MR
	 */
	umem->iova = iova;
	वापस PAGE_SIZE;
पूर्ण

अटल काष्ठा mlx5_ib_mr *alloc_cacheable_mr(काष्ठा ib_pd *pd,
					     काष्ठा ib_umem *umem, u64 iova,
					     पूर्णांक access_flags)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(pd->device);
	काष्ठा mlx5_cache_ent *ent;
	काष्ठा mlx5_ib_mr *mr;
	अचिन्हित पूर्णांक page_size;

	अगर (umem->is_dmabuf)
		page_size = mlx5_umem_dmabuf_शेष_pgsz(umem, iova);
	अन्यथा
		page_size = mlx5_umem_find_best_pgsz(umem, mkc, log_page_size,
						     0, iova);
	अगर (WARN_ON(!page_size))
		वापस ERR_PTR(-EINVAL);
	ent = mr_cache_ent_from_order(
		dev, order_base_2(ib_umem_num_dma_blocks(umem, page_size)));
	/*
	 * Matches access in alloc_cache_mr(). If the MR can't come from the
	 * cache then synchronously create an uncached one.
	 */
	अगर (!ent || ent->limit == 0 ||
	    !mlx5_ib_can_reconfig_with_umr(dev, 0, access_flags)) अणु
		mutex_lock(&dev->slow_path_mutex);
		mr = reg_create(pd, umem, iova, access_flags, page_size, false);
		mutex_unlock(&dev->slow_path_mutex);
		वापस mr;
	पूर्ण

	mr = get_cache_mr(ent);
	अगर (!mr) अणु
		mr = create_cache_mr(ent);
		/*
		 * The above alपढ़ोy tried to करो the same stuff as reg_create(),
		 * no reason to try it again.
		 */
		अगर (IS_ERR(mr))
			वापस mr;
	पूर्ण

	mr->ibmr.pd = pd;
	mr->umem = umem;
	mr->mmkey.iova = iova;
	mr->mmkey.size = umem->length;
	mr->mmkey.pd = to_mpd(pd)->pdn;
	mr->page_shअगरt = order_base_2(page_size);
	set_mr_fields(dev, mr, umem->length, access_flags);

	वापस mr;
पूर्ण

#घोषणा MLX5_MAX_UMR_CHUNK ((1 << (MLX5_MAX_UMR_SHIFT + 4)) - \
			    MLX5_UMR_MTT_ALIGNMENT)
#घोषणा MLX5_SPARE_UMR_CHUNK 0x10000

/*
 * Allocate a temporary buffer to hold the per-page inक्रमmation to transfer to
 * HW. For efficiency this should be as large as it can be, but buffer
 * allocation failure is not allowed, so try smaller sizes.
 */
अटल व्योम *mlx5_ib_alloc_xlt(माप_प्रकार *nents, माप_प्रकार ent_size, gfp_t gfp_mask)
अणु
	स्थिर माप_प्रकार xlt_chunk_align =
		MLX5_UMR_MTT_ALIGNMENT / माप(ent_size);
	माप_प्रकार size;
	व्योम *res = शून्य;

	अटल_निश्चित(PAGE_SIZE % MLX5_UMR_MTT_ALIGNMENT == 0);

	/*
	 * MLX5_IB_UPD_XLT_ATOMIC करोesn't संकेत an atomic context just that the
	 * allocation can't trigger any kind of reclaim.
	 */
	might_sleep();

	gfp_mask |= __GFP_ZERO | __GFP_NORETRY;

	/*
	 * If the प्रणाली alपढ़ोy has a suitable high order page then just use
	 * that, but करोn't try hard to create one. This max is about 1M, so a
	 * मुक्त x86 huge page will satisfy it.
	 */
	size = min_t(माप_प्रकार, ent_size * ALIGN(*nents, xlt_chunk_align),
		     MLX5_MAX_UMR_CHUNK);
	*nents = size / ent_size;
	res = (व्योम *)__get_मुक्त_pages(gfp_mask | __GFP_NOWARN,
				       get_order(size));
	अगर (res)
		वापस res;

	अगर (size > MLX5_SPARE_UMR_CHUNK) अणु
		size = MLX5_SPARE_UMR_CHUNK;
		*nents = get_order(size) / ent_size;
		res = (व्योम *)__get_मुक्त_pages(gfp_mask | __GFP_NOWARN,
					       get_order(size));
		अगर (res)
			वापस res;
	पूर्ण

	*nents = PAGE_SIZE / ent_size;
	res = (व्योम *)__get_मुक्त_page(gfp_mask);
	अगर (res)
		वापस res;

	mutex_lock(&xlt_emergency_page_mutex);
	स_रखो(xlt_emergency_page, 0, PAGE_SIZE);
	वापस xlt_emergency_page;
पूर्ण

अटल व्योम mlx5_ib_मुक्त_xlt(व्योम *xlt, माप_प्रकार length)
अणु
	अगर (xlt == xlt_emergency_page) अणु
		mutex_unlock(&xlt_emergency_page_mutex);
		वापस;
	पूर्ण

	मुक्त_pages((अचिन्हित दीर्घ)xlt, get_order(length));
पूर्ण

/*
 * Create a MLX5_IB_SEND_UMR_UPDATE_XLT work request and XLT buffer पढ़ोy क्रम
 * submission.
 */
अटल व्योम *mlx5_ib_create_xlt_wr(काष्ठा mlx5_ib_mr *mr,
				   काष्ठा mlx5_umr_wr *wr, काष्ठा ib_sge *sg,
				   माप_प्रकार nents, माप_प्रकार ent_size,
				   अचिन्हित पूर्णांक flags)
अणु
	काष्ठा mlx5_ib_dev *dev = mr_to_mdev(mr);
	काष्ठा device *ddev = &dev->mdev->pdev->dev;
	dma_addr_t dma;
	व्योम *xlt;

	xlt = mlx5_ib_alloc_xlt(&nents, ent_size,
				flags & MLX5_IB_UPD_XLT_ATOMIC ? GFP_ATOMIC :
								 GFP_KERNEL);
	sg->length = nents * ent_size;
	dma = dma_map_single(ddev, xlt, sg->length, DMA_TO_DEVICE);
	अगर (dma_mapping_error(ddev, dma)) अणु
		mlx5_ib_err(dev, "unable to map DMA during XLT update.\n");
		mlx5_ib_मुक्त_xlt(xlt, sg->length);
		वापस शून्य;
	पूर्ण
	sg->addr = dma;
	sg->lkey = dev->umrc.pd->local_dma_lkey;

	स_रखो(wr, 0, माप(*wr));
	wr->wr.send_flags = MLX5_IB_SEND_UMR_UPDATE_XLT;
	अगर (!(flags & MLX5_IB_UPD_XLT_ENABLE))
		wr->wr.send_flags |= MLX5_IB_SEND_UMR_FAIL_IF_FREE;
	wr->wr.sg_list = sg;
	wr->wr.num_sge = 1;
	wr->wr.opcode = MLX5_IB_WR_UMR;
	wr->pd = mr->ibmr.pd;
	wr->mkey = mr->mmkey.key;
	wr->length = mr->mmkey.size;
	wr->virt_addr = mr->mmkey.iova;
	wr->access_flags = mr->access_flags;
	wr->page_shअगरt = mr->page_shअगरt;
	wr->xlt_size = sg->length;
	वापस xlt;
पूर्ण

अटल व्योम mlx5_ib_unmap_मुक्त_xlt(काष्ठा mlx5_ib_dev *dev, व्योम *xlt,
				   काष्ठा ib_sge *sg)
अणु
	काष्ठा device *ddev = &dev->mdev->pdev->dev;

	dma_unmap_single(ddev, sg->addr, sg->length, DMA_TO_DEVICE);
	mlx5_ib_मुक्त_xlt(xlt, sg->length);
पूर्ण

अटल अचिन्हित पूर्णांक xlt_wr_final_send_flags(अचिन्हित पूर्णांक flags)
अणु
	अचिन्हित पूर्णांक res = 0;

	अगर (flags & MLX5_IB_UPD_XLT_ENABLE)
		res |= MLX5_IB_SEND_UMR_ENABLE_MR |
		       MLX5_IB_SEND_UMR_UPDATE_PD_ACCESS |
		       MLX5_IB_SEND_UMR_UPDATE_TRANSLATION;
	अगर (flags & MLX5_IB_UPD_XLT_PD || flags & MLX5_IB_UPD_XLT_ACCESS)
		res |= MLX5_IB_SEND_UMR_UPDATE_PD_ACCESS;
	अगर (flags & MLX5_IB_UPD_XLT_ADDR)
		res |= MLX5_IB_SEND_UMR_UPDATE_TRANSLATION;
	वापस res;
पूर्ण

पूर्णांक mlx5_ib_update_xlt(काष्ठा mlx5_ib_mr *mr, u64 idx, पूर्णांक npages,
		       पूर्णांक page_shअगरt, पूर्णांक flags)
अणु
	काष्ठा mlx5_ib_dev *dev = mr_to_mdev(mr);
	काष्ठा device *ddev = &dev->mdev->pdev->dev;
	व्योम *xlt;
	काष्ठा mlx5_umr_wr wr;
	काष्ठा ib_sge sg;
	पूर्णांक err = 0;
	पूर्णांक desc_size = (flags & MLX5_IB_UPD_XLT_INसूचीECT)
			       ? माप(काष्ठा mlx5_klm)
			       : माप(काष्ठा mlx5_mtt);
	स्थिर पूर्णांक page_align = MLX5_UMR_MTT_ALIGNMENT / desc_size;
	स्थिर पूर्णांक page_mask = page_align - 1;
	माप_प्रकार pages_mapped = 0;
	माप_प्रकार pages_to_map = 0;
	माप_प्रकार pages_iter;
	माप_प्रकार माप_प्रकारo_map = 0;
	माप_प्रकार orig_sg_length;

	अगर ((flags & MLX5_IB_UPD_XLT_INसूचीECT) &&
	    !umr_can_use_indirect_mkey(dev))
		वापस -EPERM;

	अगर (WARN_ON(!mr->umem->is_odp))
		वापस -EINVAL;

	/* UMR copies MTTs in units of MLX5_UMR_MTT_ALIGNMENT bytes,
	 * so we need to align the offset and length accordingly
	 */
	अगर (idx & page_mask) अणु
		npages += idx & page_mask;
		idx &= ~page_mask;
	पूर्ण
	pages_to_map = ALIGN(npages, page_align);

	xlt = mlx5_ib_create_xlt_wr(mr, &wr, &sg, npages, desc_size, flags);
	अगर (!xlt)
		वापस -ENOMEM;
	pages_iter = sg.length / desc_size;
	orig_sg_length = sg.length;

	अगर (!(flags & MLX5_IB_UPD_XLT_INसूचीECT)) अणु
		काष्ठा ib_umem_odp *odp = to_ib_umem_odp(mr->umem);
		माप_प्रकार max_pages = ib_umem_odp_num_pages(odp) - idx;

		pages_to_map = min_t(माप_प्रकार, pages_to_map, max_pages);
	पूर्ण

	wr.page_shअगरt = page_shअगरt;

	क्रम (pages_mapped = 0;
	     pages_mapped < pages_to_map && !err;
	     pages_mapped += pages_iter, idx += pages_iter) अणु
		npages = min_t(पूर्णांक, pages_iter, pages_to_map - pages_mapped);
		माप_प्रकारo_map = npages * desc_size;
		dma_sync_single_क्रम_cpu(ddev, sg.addr, sg.length,
					DMA_TO_DEVICE);
		mlx5_odp_populate_xlt(xlt, idx, npages, mr, flags);
		dma_sync_single_क्रम_device(ddev, sg.addr, sg.length,
					   DMA_TO_DEVICE);

		sg.length = ALIGN(माप_प्रकारo_map, MLX5_UMR_MTT_ALIGNMENT);

		अगर (pages_mapped + pages_iter >= pages_to_map)
			wr.wr.send_flags |= xlt_wr_final_send_flags(flags);

		wr.offset = idx * desc_size;
		wr.xlt_size = sg.length;

		err = mlx5_ib_post_send_रुको(dev, &wr);
	पूर्ण
	sg.length = orig_sg_length;
	mlx5_ib_unmap_मुक्त_xlt(dev, xlt, &sg);
	वापस err;
पूर्ण

/*
 * Send the DMA list to the HW क्रम a normal MR using UMR.
 * Dmabuf MR is handled in a similar way, except that the MLX5_IB_UPD_XLT_ZAP
 * flag may be used.
 */
पूर्णांक mlx5_ib_update_mr_pas(काष्ठा mlx5_ib_mr *mr, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा mlx5_ib_dev *dev = mr_to_mdev(mr);
	काष्ठा device *ddev = &dev->mdev->pdev->dev;
	काष्ठा ib_block_iter biter;
	काष्ठा mlx5_mtt *cur_mtt;
	काष्ठा mlx5_umr_wr wr;
	माप_प्रकार orig_sg_length;
	काष्ठा mlx5_mtt *mtt;
	माप_प्रकार final_size;
	काष्ठा ib_sge sg;
	पूर्णांक err = 0;

	अगर (WARN_ON(mr->umem->is_odp))
		वापस -EINVAL;

	mtt = mlx5_ib_create_xlt_wr(mr, &wr, &sg,
				    ib_umem_num_dma_blocks(mr->umem,
							   1 << mr->page_shअगरt),
				    माप(*mtt), flags);
	अगर (!mtt)
		वापस -ENOMEM;
	orig_sg_length = sg.length;

	cur_mtt = mtt;
	rdma_क्रम_each_block (mr->umem->sg_head.sgl, &biter, mr->umem->nmap,
			     BIT(mr->page_shअगरt)) अणु
		अगर (cur_mtt == (व्योम *)mtt + sg.length) अणु
			dma_sync_single_क्रम_device(ddev, sg.addr, sg.length,
						   DMA_TO_DEVICE);
			err = mlx5_ib_post_send_रुको(dev, &wr);
			अगर (err)
				जाओ err;
			dma_sync_single_क्रम_cpu(ddev, sg.addr, sg.length,
						DMA_TO_DEVICE);
			wr.offset += sg.length;
			cur_mtt = mtt;
		पूर्ण

		cur_mtt->ptag =
			cpu_to_be64(rdma_block_iter_dma_address(&biter) |
				    MLX5_IB_MTT_PRESENT);

		अगर (mr->umem->is_dmabuf && (flags & MLX5_IB_UPD_XLT_ZAP))
			cur_mtt->ptag = 0;

		cur_mtt++;
	पूर्ण

	final_size = (व्योम *)cur_mtt - (व्योम *)mtt;
	sg.length = ALIGN(final_size, MLX5_UMR_MTT_ALIGNMENT);
	स_रखो(cur_mtt, 0, sg.length - final_size);
	wr.wr.send_flags |= xlt_wr_final_send_flags(flags);
	wr.xlt_size = sg.length;

	dma_sync_single_क्रम_device(ddev, sg.addr, sg.length, DMA_TO_DEVICE);
	err = mlx5_ib_post_send_रुको(dev, &wr);

err:
	sg.length = orig_sg_length;
	mlx5_ib_unmap_मुक्त_xlt(dev, mtt, &sg);
	वापस err;
पूर्ण

/*
 * If ibmr is शून्य it will be allocated by reg_create.
 * Else, the given ibmr will be used.
 */
अटल काष्ठा mlx5_ib_mr *reg_create(काष्ठा ib_pd *pd, काष्ठा ib_umem *umem,
				     u64 iova, पूर्णांक access_flags,
				     अचिन्हित पूर्णांक page_size, bool populate)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(pd->device);
	काष्ठा mlx5_ib_mr *mr;
	__be64 *pas;
	व्योम *mkc;
	पूर्णांक inlen;
	u32 *in;
	पूर्णांक err;
	bool pg_cap = !!(MLX5_CAP_GEN(dev->mdev, pg));

	अगर (!page_size)
		वापस ERR_PTR(-EINVAL);
	mr = kzalloc(माप(*mr), GFP_KERNEL);
	अगर (!mr)
		वापस ERR_PTR(-ENOMEM);

	mr->ibmr.pd = pd;
	mr->access_flags = access_flags;
	mr->page_shअगरt = order_base_2(page_size);

	inlen = MLX5_ST_SZ_BYTES(create_mkey_in);
	अगर (populate)
		inlen += माप(*pas) *
			 roundup(ib_umem_num_dma_blocks(umem, page_size), 2);
	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in) अणु
		err = -ENOMEM;
		जाओ err_1;
	पूर्ण
	pas = (__be64 *)MLX5_ADDR_OF(create_mkey_in, in, klm_pas_mtt);
	अगर (populate) अणु
		अगर (WARN_ON(access_flags & IB_ACCESS_ON_DEMAND)) अणु
			err = -EINVAL;
			जाओ err_2;
		पूर्ण
		mlx5_ib_populate_pas(umem, 1UL << mr->page_shअगरt, pas,
				     pg_cap ? MLX5_IB_MTT_PRESENT : 0);
	पूर्ण

	/* The pg_access bit allows setting the access flags
	 * in the page list submitted with the command. */
	MLX5_SET(create_mkey_in, in, pg_access, !!(pg_cap));

	mkc = MLX5_ADDR_OF(create_mkey_in, in, memory_key_mkey_entry);
	set_mkc_access_pd_addr_fields(mkc, access_flags, iova,
				      populate ? pd : dev->umrc.pd);
	MLX5_SET(mkc, mkc, मुक्त, !populate);
	MLX5_SET(mkc, mkc, access_mode_1_0, MLX5_MKC_ACCESS_MODE_MTT);
	MLX5_SET(mkc, mkc, umr_en, 1);

	MLX5_SET64(mkc, mkc, len, umem->length);
	MLX5_SET(mkc, mkc, bsf_octword_size, 0);
	MLX5_SET(mkc, mkc, translations_octword_size,
		 get_octo_len(iova, umem->length, mr->page_shअगरt));
	MLX5_SET(mkc, mkc, log_page_size, mr->page_shअगरt);
	अगर (populate) अणु
		MLX5_SET(create_mkey_in, in, translations_octword_actual_size,
			 get_octo_len(iova, umem->length, mr->page_shअगरt));
	पूर्ण

	err = mlx5_ib_create_mkey(dev, &mr->mmkey, in, inlen);
	अगर (err) अणु
		mlx5_ib_warn(dev, "create mkey failed\n");
		जाओ err_2;
	पूर्ण
	mr->mmkey.type = MLX5_MKEY_MR;
	mr->desc_size = माप(काष्ठा mlx5_mtt);
	mr->umem = umem;
	set_mr_fields(dev, mr, umem->length, access_flags);
	kvमुक्त(in);

	mlx5_ib_dbg(dev, "mkey = 0x%x\n", mr->mmkey.key);

	वापस mr;

err_2:
	kvमुक्त(in);
err_1:
	kमुक्त(mr);
	वापस ERR_PTR(err);
पूर्ण

अटल काष्ठा ib_mr *mlx5_ib_get_dm_mr(काष्ठा ib_pd *pd, u64 start_addr,
				       u64 length, पूर्णांक acc, पूर्णांक mode)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(pd->device);
	पूर्णांक inlen = MLX5_ST_SZ_BYTES(create_mkey_in);
	काष्ठा mlx5_ib_mr *mr;
	व्योम *mkc;
	u32 *in;
	पूर्णांक err;

	mr = kzalloc(माप(*mr), GFP_KERNEL);
	अगर (!mr)
		वापस ERR_PTR(-ENOMEM);

	in = kzalloc(inlen, GFP_KERNEL);
	अगर (!in) अणु
		err = -ENOMEM;
		जाओ err_मुक्त;
	पूर्ण

	mkc = MLX5_ADDR_OF(create_mkey_in, in, memory_key_mkey_entry);

	MLX5_SET(mkc, mkc, access_mode_1_0, mode & 0x3);
	MLX5_SET(mkc, mkc, access_mode_4_2, (mode >> 2) & 0x7);
	MLX5_SET64(mkc, mkc, len, length);
	set_mkc_access_pd_addr_fields(mkc, acc, start_addr, pd);

	err = mlx5_ib_create_mkey(dev, &mr->mmkey, in, inlen);
	अगर (err)
		जाओ err_in;

	kमुक्त(in);

	set_mr_fields(dev, mr, length, acc);

	वापस &mr->ibmr;

err_in:
	kमुक्त(in);

err_मुक्त:
	kमुक्त(mr);

	वापस ERR_PTR(err);
पूर्ण

पूर्णांक mlx5_ib_advise_mr(काष्ठा ib_pd *pd,
		      क्रमागत ib_uverbs_advise_mr_advice advice,
		      u32 flags,
		      काष्ठा ib_sge *sg_list,
		      u32 num_sge,
		      काष्ठा uverbs_attr_bundle *attrs)
अणु
	अगर (advice != IB_UVERBS_ADVISE_MR_ADVICE_PREFETCH &&
	    advice != IB_UVERBS_ADVISE_MR_ADVICE_PREFETCH_WRITE &&
	    advice != IB_UVERBS_ADVISE_MR_ADVICE_PREFETCH_NO_FAULT)
		वापस -EOPNOTSUPP;

	वापस mlx5_ib_advise_mr_prefetch(pd, advice, flags,
					 sg_list, num_sge);
पूर्ण

काष्ठा ib_mr *mlx5_ib_reg_dm_mr(काष्ठा ib_pd *pd, काष्ठा ib_dm *dm,
				काष्ठा ib_dm_mr_attr *attr,
				काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा mlx5_ib_dm *mdm = to_mdm(dm);
	काष्ठा mlx5_core_dev *dev = to_mdev(dm->device)->mdev;
	u64 start_addr = mdm->dev_addr + attr->offset;
	पूर्णांक mode;

	चयन (mdm->type) अणु
	हाल MLX5_IB_UAPI_DM_TYPE_MEMIC:
		अगर (attr->access_flags & ~MLX5_IB_DM_MEMIC_ALLOWED_ACCESS)
			वापस ERR_PTR(-EINVAL);

		mode = MLX5_MKC_ACCESS_MODE_MEMIC;
		start_addr -= pci_resource_start(dev->pdev, 0);
		अवरोध;
	हाल MLX5_IB_UAPI_DM_TYPE_STEERING_SW_ICM:
	हाल MLX5_IB_UAPI_DM_TYPE_HEADER_MODIFY_SW_ICM:
		अगर (attr->access_flags & ~MLX5_IB_DM_SW_ICM_ALLOWED_ACCESS)
			वापस ERR_PTR(-EINVAL);

		mode = MLX5_MKC_ACCESS_MODE_SW_ICM;
		अवरोध;
	शेष:
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस mlx5_ib_get_dm_mr(pd, start_addr, attr->length,
				 attr->access_flags, mode);
पूर्ण

अटल काष्ठा ib_mr *create_real_mr(काष्ठा ib_pd *pd, काष्ठा ib_umem *umem,
				    u64 iova, पूर्णांक access_flags)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(pd->device);
	काष्ठा mlx5_ib_mr *mr = शून्य;
	bool xlt_with_umr;
	पूर्णांक err;

	xlt_with_umr = mlx5_ib_can_load_pas_with_umr(dev, umem->length);
	अगर (xlt_with_umr) अणु
		mr = alloc_cacheable_mr(pd, umem, iova, access_flags);
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक page_size = mlx5_umem_find_best_pgsz(
			umem, mkc, log_page_size, 0, iova);

		mutex_lock(&dev->slow_path_mutex);
		mr = reg_create(pd, umem, iova, access_flags, page_size, true);
		mutex_unlock(&dev->slow_path_mutex);
	पूर्ण
	अगर (IS_ERR(mr)) अणु
		ib_umem_release(umem);
		वापस ERR_CAST(mr);
	पूर्ण

	mlx5_ib_dbg(dev, "mkey 0x%x\n", mr->mmkey.key);

	atomic_add(ib_umem_num_pages(umem), &dev->mdev->priv.reg_pages);

	अगर (xlt_with_umr) अणु
		/*
		 * If the MR was created with reg_create then it will be
		 * configured properly but left disabled. It is safe to go ahead
		 * and configure it again via UMR जबतक enabling it.
		 */
		err = mlx5_ib_update_mr_pas(mr, MLX5_IB_UPD_XLT_ENABLE);
		अगर (err) अणु
			mlx5_ib_dereg_mr(&mr->ibmr, शून्य);
			वापस ERR_PTR(err);
		पूर्ण
	पूर्ण
	वापस &mr->ibmr;
पूर्ण

अटल काष्ठा ib_mr *create_user_odp_mr(काष्ठा ib_pd *pd, u64 start, u64 length,
					u64 iova, पूर्णांक access_flags,
					काष्ठा ib_udata *udata)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(pd->device);
	काष्ठा ib_umem_odp *odp;
	काष्ठा mlx5_ib_mr *mr;
	पूर्णांक err;

	अगर (!IS_ENABLED(CONFIG_INFINIBAND_ON_DEMAND_PAGING))
		वापस ERR_PTR(-EOPNOTSUPP);

	err = mlx5r_odp_create_eq(dev, &dev->odp_pf_eq);
	अगर (err)
		वापस ERR_PTR(err);
	अगर (!start && length == U64_MAX) अणु
		अगर (iova != 0)
			वापस ERR_PTR(-EINVAL);
		अगर (!(dev->odp_caps.general_caps & IB_ODP_SUPPORT_IMPLICIT))
			वापस ERR_PTR(-EINVAL);

		mr = mlx5_ib_alloc_implicit_mr(to_mpd(pd), udata, access_flags);
		अगर (IS_ERR(mr))
			वापस ERR_CAST(mr);
		वापस &mr->ibmr;
	पूर्ण

	/* ODP requires xlt update via umr to work. */
	अगर (!mlx5_ib_can_load_pas_with_umr(dev, length))
		वापस ERR_PTR(-EINVAL);

	odp = ib_umem_odp_get(&dev->ib_dev, start, length, access_flags,
			      &mlx5_mn_ops);
	अगर (IS_ERR(odp))
		वापस ERR_CAST(odp);

	mr = alloc_cacheable_mr(pd, &odp->umem, iova, access_flags);
	अगर (IS_ERR(mr)) अणु
		ib_umem_release(&odp->umem);
		वापस ERR_CAST(mr);
	पूर्ण

	odp->निजी = mr;
	err = mlx5r_store_odp_mkey(dev, &mr->mmkey);
	अगर (err)
		जाओ err_dereg_mr;

	err = mlx5_ib_init_odp_mr(mr);
	अगर (err)
		जाओ err_dereg_mr;
	वापस &mr->ibmr;

err_dereg_mr:
	mlx5_ib_dereg_mr(&mr->ibmr, शून्य);
	वापस ERR_PTR(err);
पूर्ण

काष्ठा ib_mr *mlx5_ib_reg_user_mr(काष्ठा ib_pd *pd, u64 start, u64 length,
				  u64 iova, पूर्णांक access_flags,
				  काष्ठा ib_udata *udata)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(pd->device);
	काष्ठा ib_umem *umem;

	अगर (!IS_ENABLED(CONFIG_INFINIBAND_USER_MEM))
		वापस ERR_PTR(-EOPNOTSUPP);

	mlx5_ib_dbg(dev, "start 0x%llx, iova 0x%llx, length 0x%llx, access_flags 0x%x\n",
		    start, iova, length, access_flags);

	अगर (access_flags & IB_ACCESS_ON_DEMAND)
		वापस create_user_odp_mr(pd, start, length, iova, access_flags,
					  udata);
	umem = ib_umem_get(&dev->ib_dev, start, length, access_flags);
	अगर (IS_ERR(umem))
		वापस ERR_CAST(umem);
	वापस create_real_mr(pd, umem, iova, access_flags);
पूर्ण

अटल व्योम mlx5_ib_dmabuf_invalidate_cb(काष्ठा dma_buf_attachment *attach)
अणु
	काष्ठा ib_umem_dmabuf *umem_dmabuf = attach->importer_priv;
	काष्ठा mlx5_ib_mr *mr = umem_dmabuf->निजी;

	dma_resv_निश्चित_held(umem_dmabuf->attach->dmabuf->resv);

	अगर (!umem_dmabuf->sgt)
		वापस;

	mlx5_ib_update_mr_pas(mr, MLX5_IB_UPD_XLT_ZAP);
	ib_umem_dmabuf_unmap_pages(umem_dmabuf);
पूर्ण

अटल काष्ठा dma_buf_attach_ops mlx5_ib_dmabuf_attach_ops = अणु
	.allow_peer2peer = 1,
	.move_notअगरy = mlx5_ib_dmabuf_invalidate_cb,
पूर्ण;

काष्ठा ib_mr *mlx5_ib_reg_user_mr_dmabuf(काष्ठा ib_pd *pd, u64 offset,
					 u64 length, u64 virt_addr,
					 पूर्णांक fd, पूर्णांक access_flags,
					 काष्ठा ib_udata *udata)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(pd->device);
	काष्ठा mlx5_ib_mr *mr = शून्य;
	काष्ठा ib_umem_dmabuf *umem_dmabuf;
	पूर्णांक err;

	अगर (!IS_ENABLED(CONFIG_INFINIBAND_USER_MEM) ||
	    !IS_ENABLED(CONFIG_INFINIBAND_ON_DEMAND_PAGING))
		वापस ERR_PTR(-EOPNOTSUPP);

	mlx5_ib_dbg(dev,
		    "offset 0x%llx, virt_addr 0x%llx, length 0x%llx, fd %d, access_flags 0x%x\n",
		    offset, virt_addr, length, fd, access_flags);

	/* dmabuf requires xlt update via umr to work. */
	अगर (!mlx5_ib_can_load_pas_with_umr(dev, length))
		वापस ERR_PTR(-EINVAL);

	umem_dmabuf = ib_umem_dmabuf_get(&dev->ib_dev, offset, length, fd,
					 access_flags,
					 &mlx5_ib_dmabuf_attach_ops);
	अगर (IS_ERR(umem_dmabuf)) अणु
		mlx5_ib_dbg(dev, "umem_dmabuf get failed (%ld)\n",
			    PTR_ERR(umem_dmabuf));
		वापस ERR_CAST(umem_dmabuf);
	पूर्ण

	mr = alloc_cacheable_mr(pd, &umem_dmabuf->umem, virt_addr,
				access_flags);
	अगर (IS_ERR(mr)) अणु
		ib_umem_release(&umem_dmabuf->umem);
		वापस ERR_CAST(mr);
	पूर्ण

	mlx5_ib_dbg(dev, "mkey 0x%x\n", mr->mmkey.key);

	atomic_add(ib_umem_num_pages(mr->umem), &dev->mdev->priv.reg_pages);
	umem_dmabuf->निजी = mr;
	err = mlx5r_store_odp_mkey(dev, &mr->mmkey);
	अगर (err)
		जाओ err_dereg_mr;

	err = mlx5_ib_init_dmabuf_mr(mr);
	अगर (err)
		जाओ err_dereg_mr;
	वापस &mr->ibmr;

err_dereg_mr:
	mlx5_ib_dereg_mr(&mr->ibmr, शून्य);
	वापस ERR_PTR(err);
पूर्ण

/**
 * revoke_mr - Fence all DMA on the MR
 * @mr: The MR to fence
 *
 * Upon वापस the NIC will not be करोing any DMA to the pages under the MR,
 * and any DMA in progress will be completed. Failure of this function
 * indicates the HW has failed catastrophically.
 */
अटल पूर्णांक revoke_mr(काष्ठा mlx5_ib_mr *mr)
अणु
	काष्ठा mlx5_umr_wr umrwr = अणुपूर्ण;

	अगर (mr_to_mdev(mr)->mdev->state == MLX5_DEVICE_STATE_INTERNAL_ERROR)
		वापस 0;

	umrwr.wr.send_flags = MLX5_IB_SEND_UMR_DISABLE_MR |
			      MLX5_IB_SEND_UMR_UPDATE_PD_ACCESS;
	umrwr.wr.opcode = MLX5_IB_WR_UMR;
	umrwr.pd = mr_to_mdev(mr)->umrc.pd;
	umrwr.mkey = mr->mmkey.key;
	umrwr.ignore_मुक्त_state = 1;

	वापस mlx5_ib_post_send_रुको(mr_to_mdev(mr), &umrwr);
पूर्ण

/*
 * True अगर the change in access flags can be करोne via UMR, only some access
 * flags can be updated.
 */
अटल bool can_use_umr_rereg_access(काष्ठा mlx5_ib_dev *dev,
				     अचिन्हित पूर्णांक current_access_flags,
				     अचिन्हित पूर्णांक target_access_flags)
अणु
	अचिन्हित पूर्णांक dअगरfs = current_access_flags ^ target_access_flags;

	अगर (dअगरfs & ~(IB_ACCESS_LOCAL_WRITE | IB_ACCESS_REMOTE_WRITE |
		      IB_ACCESS_REMOTE_READ | IB_ACCESS_RELAXED_ORDERING))
		वापस false;
	वापस mlx5_ib_can_reconfig_with_umr(dev, current_access_flags,
					     target_access_flags);
पूर्ण

अटल पूर्णांक umr_rereg_pd_access(काष्ठा mlx5_ib_mr *mr, काष्ठा ib_pd *pd,
			       पूर्णांक access_flags)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(mr->ibmr.device);
	काष्ठा mlx5_umr_wr umrwr = अणु
		.wr = अणु
			.send_flags = MLX5_IB_SEND_UMR_FAIL_IF_FREE |
				      MLX5_IB_SEND_UMR_UPDATE_PD_ACCESS,
			.opcode = MLX5_IB_WR_UMR,
		पूर्ण,
		.mkey = mr->mmkey.key,
		.pd = pd,
		.access_flags = access_flags,
	पूर्ण;
	पूर्णांक err;

	err = mlx5_ib_post_send_रुको(dev, &umrwr);
	अगर (err)
		वापस err;

	mr->access_flags = access_flags;
	mr->mmkey.pd = to_mpd(pd)->pdn;
	वापस 0;
पूर्ण

अटल bool can_use_umr_rereg_pas(काष्ठा mlx5_ib_mr *mr,
				  काष्ठा ib_umem *new_umem,
				  पूर्णांक new_access_flags, u64 iova,
				  अचिन्हित दीर्घ *page_size)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(mr->ibmr.device);

	/* We only track the allocated sizes of MRs from the cache */
	अगर (!mr->cache_ent)
		वापस false;
	अगर (!mlx5_ib_can_load_pas_with_umr(dev, new_umem->length))
		वापस false;

	*page_size =
		mlx5_umem_find_best_pgsz(new_umem, mkc, log_page_size, 0, iova);
	अगर (WARN_ON(!*page_size))
		वापस false;
	वापस (1ULL << mr->cache_ent->order) >=
	       ib_umem_num_dma_blocks(new_umem, *page_size);
पूर्ण

अटल पूर्णांक umr_rereg_pas(काष्ठा mlx5_ib_mr *mr, काष्ठा ib_pd *pd,
			 पूर्णांक access_flags, पूर्णांक flags, काष्ठा ib_umem *new_umem,
			 u64 iova, अचिन्हित दीर्घ page_size)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(mr->ibmr.device);
	पूर्णांक upd_flags = MLX5_IB_UPD_XLT_ADDR | MLX5_IB_UPD_XLT_ENABLE;
	काष्ठा ib_umem *old_umem = mr->umem;
	पूर्णांक err;

	/*
	 * To keep everything simple the MR is revoked beक्रमe we start to mess
	 * with it. This ensure the change is atomic relative to any use of the
	 * MR.
	 */
	err = revoke_mr(mr);
	अगर (err)
		वापस err;

	अगर (flags & IB_MR_REREG_PD) अणु
		mr->ibmr.pd = pd;
		mr->mmkey.pd = to_mpd(pd)->pdn;
		upd_flags |= MLX5_IB_UPD_XLT_PD;
	पूर्ण
	अगर (flags & IB_MR_REREG_ACCESS) अणु
		mr->access_flags = access_flags;
		upd_flags |= MLX5_IB_UPD_XLT_ACCESS;
	पूर्ण

	mr->ibmr.length = new_umem->length;
	mr->mmkey.iova = iova;
	mr->mmkey.size = new_umem->length;
	mr->page_shअगरt = order_base_2(page_size);
	mr->umem = new_umem;
	err = mlx5_ib_update_mr_pas(mr, upd_flags);
	अगर (err) अणु
		/*
		 * The MR is revoked at this poपूर्णांक so there is no issue to मुक्त
		 * new_umem.
		 */
		mr->umem = old_umem;
		वापस err;
	पूर्ण

	atomic_sub(ib_umem_num_pages(old_umem), &dev->mdev->priv.reg_pages);
	ib_umem_release(old_umem);
	atomic_add(ib_umem_num_pages(new_umem), &dev->mdev->priv.reg_pages);
	वापस 0;
पूर्ण

काष्ठा ib_mr *mlx5_ib_rereg_user_mr(काष्ठा ib_mr *ib_mr, पूर्णांक flags, u64 start,
				    u64 length, u64 iova, पूर्णांक new_access_flags,
				    काष्ठा ib_pd *new_pd,
				    काष्ठा ib_udata *udata)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(ib_mr->device);
	काष्ठा mlx5_ib_mr *mr = to_mmr(ib_mr);
	पूर्णांक err;

	अगर (!IS_ENABLED(CONFIG_INFINIBAND_USER_MEM))
		वापस ERR_PTR(-EOPNOTSUPP);

	mlx5_ib_dbg(
		dev,
		"start 0x%llx, iova 0x%llx, length 0x%llx, access_flags 0x%x\n",
		start, iova, length, new_access_flags);

	अगर (flags & ~(IB_MR_REREG_TRANS | IB_MR_REREG_PD | IB_MR_REREG_ACCESS))
		वापस ERR_PTR(-EOPNOTSUPP);

	अगर (!(flags & IB_MR_REREG_ACCESS))
		new_access_flags = mr->access_flags;
	अगर (!(flags & IB_MR_REREG_PD))
		new_pd = ib_mr->pd;

	अगर (!(flags & IB_MR_REREG_TRANS)) अणु
		काष्ठा ib_umem *umem;

		/* Fast path क्रम PD/access change */
		अगर (can_use_umr_rereg_access(dev, mr->access_flags,
					     new_access_flags)) अणु
			err = umr_rereg_pd_access(mr, new_pd, new_access_flags);
			अगर (err)
				वापस ERR_PTR(err);
			वापस शून्य;
		पूर्ण
		/* DM or ODP MR's don't have a normal umem so we can't re-use it */
		अगर (!mr->umem || is_odp_mr(mr) || is_dmabuf_mr(mr))
			जाओ recreate;

		/*
		 * Only one active MR can refer to a umem at one समय, revoke
		 * the old MR beक्रमe assigning the umem to the new one.
		 */
		err = revoke_mr(mr);
		अगर (err)
			वापस ERR_PTR(err);
		umem = mr->umem;
		mr->umem = शून्य;
		atomic_sub(ib_umem_num_pages(umem), &dev->mdev->priv.reg_pages);

		वापस create_real_mr(new_pd, umem, mr->mmkey.iova,
				      new_access_flags);
	पूर्ण

	/*
	 * DM करोesn't have a PAS list so we can't re-use it, odp/dmabuf करोes
	 * but the logic around releasing the umem is dअगरferent
	 */
	अगर (!mr->umem || is_odp_mr(mr) || is_dmabuf_mr(mr))
		जाओ recreate;

	अगर (!(new_access_flags & IB_ACCESS_ON_DEMAND) &&
	    can_use_umr_rereg_access(dev, mr->access_flags, new_access_flags)) अणु
		काष्ठा ib_umem *new_umem;
		अचिन्हित दीर्घ page_size;

		new_umem = ib_umem_get(&dev->ib_dev, start, length,
				       new_access_flags);
		अगर (IS_ERR(new_umem))
			वापस ERR_CAST(new_umem);

		/* Fast path क्रम PAS change */
		अगर (can_use_umr_rereg_pas(mr, new_umem, new_access_flags, iova,
					  &page_size)) अणु
			err = umr_rereg_pas(mr, new_pd, new_access_flags, flags,
					    new_umem, iova, page_size);
			अगर (err) अणु
				ib_umem_release(new_umem);
				वापस ERR_PTR(err);
			पूर्ण
			वापस शून्य;
		पूर्ण
		वापस create_real_mr(new_pd, new_umem, iova, new_access_flags);
	पूर्ण

	/*
	 * Everything अन्यथा has no state we can preserve, just create a new MR
	 * from scratch
	 */
recreate:
	वापस mlx5_ib_reg_user_mr(new_pd, start, length, iova,
				   new_access_flags, udata);
पूर्ण

अटल पूर्णांक
mlx5_alloc_priv_descs(काष्ठा ib_device *device,
		      काष्ठा mlx5_ib_mr *mr,
		      पूर्णांक ndescs,
		      पूर्णांक desc_size)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(device);
	काष्ठा device *ddev = &dev->mdev->pdev->dev;
	पूर्णांक size = ndescs * desc_size;
	पूर्णांक add_size;
	पूर्णांक ret;

	add_size = max_t(पूर्णांक, MLX5_UMR_ALIGN - ARCH_KMALLOC_MINALIGN, 0);

	mr->descs_alloc = kzalloc(size + add_size, GFP_KERNEL);
	अगर (!mr->descs_alloc)
		वापस -ENOMEM;

	mr->descs = PTR_ALIGN(mr->descs_alloc, MLX5_UMR_ALIGN);

	mr->desc_map = dma_map_single(ddev, mr->descs, size, DMA_TO_DEVICE);
	अगर (dma_mapping_error(ddev, mr->desc_map)) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	वापस 0;
err:
	kमुक्त(mr->descs_alloc);

	वापस ret;
पूर्ण

अटल व्योम
mlx5_मुक्त_priv_descs(काष्ठा mlx5_ib_mr *mr)
अणु
	अगर (!mr->umem && mr->descs) अणु
		काष्ठा ib_device *device = mr->ibmr.device;
		पूर्णांक size = mr->max_descs * mr->desc_size;
		काष्ठा mlx5_ib_dev *dev = to_mdev(device);

		dma_unmap_single(&dev->mdev->pdev->dev, mr->desc_map, size,
				 DMA_TO_DEVICE);
		kमुक्त(mr->descs_alloc);
		mr->descs = शून्य;
	पूर्ण
पूर्ण

पूर्णांक mlx5_ib_dereg_mr(काष्ठा ib_mr *ibmr, काष्ठा ib_udata *udata)
अणु
	काष्ठा mlx5_ib_mr *mr = to_mmr(ibmr);
	काष्ठा mlx5_ib_dev *dev = to_mdev(ibmr->device);
	पूर्णांक rc;

	/*
	 * Any async use of the mr must hold the refcount, once the refcount
	 * goes to zero no other thपढ़ो, such as ODP page faults, prefetch, any
	 * UMR activity, etc can touch the mkey. Thus it is safe to destroy it.
	 */
	अगर (IS_ENABLED(CONFIG_INFINIBAND_ON_DEMAND_PAGING) &&
	    refcount_पढ़ो(&mr->mmkey.usecount) != 0 &&
	    xa_erase(&mr_to_mdev(mr)->odp_mkeys, mlx5_base_mkey(mr->mmkey.key)))
		mlx5r_deref_रुको_odp_mkey(&mr->mmkey);

	अगर (ibmr->type == IB_MR_TYPE_INTEGRITY) अणु
		xa_cmpxchg(&dev->sig_mrs, mlx5_base_mkey(mr->mmkey.key),
			   mr->sig, शून्य, GFP_KERNEL);

		अगर (mr->mtt_mr) अणु
			rc = mlx5_ib_dereg_mr(&mr->mtt_mr->ibmr, शून्य);
			अगर (rc)
				वापस rc;
			mr->mtt_mr = शून्य;
		पूर्ण
		अगर (mr->klm_mr) अणु
			rc = mlx5_ib_dereg_mr(&mr->klm_mr->ibmr, शून्य);
			अगर (rc)
				वापस rc;
			mr->klm_mr = शून्य;
		पूर्ण

		अगर (mlx5_core_destroy_psv(dev->mdev,
					  mr->sig->psv_memory.psv_idx))
			mlx5_ib_warn(dev, "failed to destroy mem psv %d\n",
				     mr->sig->psv_memory.psv_idx);
		अगर (mlx5_core_destroy_psv(dev->mdev, mr->sig->psv_wire.psv_idx))
			mlx5_ib_warn(dev, "failed to destroy wire psv %d\n",
				     mr->sig->psv_wire.psv_idx);
		kमुक्त(mr->sig);
		mr->sig = शून्य;
	पूर्ण

	/* Stop DMA */
	अगर (mr->cache_ent) अणु
		अगर (revoke_mr(mr)) अणु
			spin_lock_irq(&mr->cache_ent->lock);
			mr->cache_ent->total_mrs--;
			spin_unlock_irq(&mr->cache_ent->lock);
			mr->cache_ent = शून्य;
		पूर्ण
	पूर्ण
	अगर (!mr->cache_ent) अणु
		rc = destroy_mkey(to_mdev(mr->ibmr.device), mr);
		अगर (rc)
			वापस rc;
	पूर्ण

	अगर (mr->umem) अणु
		bool is_odp = is_odp_mr(mr);

		अगर (!is_odp)
			atomic_sub(ib_umem_num_pages(mr->umem),
				   &dev->mdev->priv.reg_pages);
		ib_umem_release(mr->umem);
		अगर (is_odp)
			mlx5_ib_मुक्त_odp_mr(mr);
	पूर्ण

	अगर (mr->cache_ent) अणु
		mlx5_mr_cache_मुक्त(dev, mr);
	पूर्ण अन्यथा अणु
		mlx5_मुक्त_priv_descs(mr);
		kमुक्त(mr);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम mlx5_set_umr_मुक्त_mkey(काष्ठा ib_pd *pd, u32 *in, पूर्णांक ndescs,
				   पूर्णांक access_mode, पूर्णांक page_shअगरt)
अणु
	व्योम *mkc;

	mkc = MLX5_ADDR_OF(create_mkey_in, in, memory_key_mkey_entry);

	/* This is only used from the kernel, so setting the PD is OK. */
	set_mkc_access_pd_addr_fields(mkc, 0, 0, pd);
	MLX5_SET(mkc, mkc, मुक्त, 1);
	MLX5_SET(mkc, mkc, translations_octword_size, ndescs);
	MLX5_SET(mkc, mkc, access_mode_1_0, access_mode & 0x3);
	MLX5_SET(mkc, mkc, access_mode_4_2, (access_mode >> 2) & 0x7);
	MLX5_SET(mkc, mkc, umr_en, 1);
	MLX5_SET(mkc, mkc, log_page_size, page_shअगरt);
पूर्ण

अटल पूर्णांक _mlx5_alloc_mkey_descs(काष्ठा ib_pd *pd, काष्ठा mlx5_ib_mr *mr,
				  पूर्णांक ndescs, पूर्णांक desc_size, पूर्णांक page_shअगरt,
				  पूर्णांक access_mode, u32 *in, पूर्णांक inlen)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(pd->device);
	पूर्णांक err;

	mr->access_mode = access_mode;
	mr->desc_size = desc_size;
	mr->max_descs = ndescs;

	err = mlx5_alloc_priv_descs(pd->device, mr, ndescs, desc_size);
	अगर (err)
		वापस err;

	mlx5_set_umr_मुक्त_mkey(pd, in, ndescs, access_mode, page_shअगरt);

	err = mlx5_ib_create_mkey(dev, &mr->mmkey, in, inlen);
	अगर (err)
		जाओ err_मुक्त_descs;

	mr->mmkey.type = MLX5_MKEY_MR;
	mr->ibmr.lkey = mr->mmkey.key;
	mr->ibmr.rkey = mr->mmkey.key;

	वापस 0;

err_मुक्त_descs:
	mlx5_मुक्त_priv_descs(mr);
	वापस err;
पूर्ण

अटल काष्ठा mlx5_ib_mr *mlx5_ib_alloc_pi_mr(काष्ठा ib_pd *pd,
				u32 max_num_sg, u32 max_num_meta_sg,
				पूर्णांक desc_size, पूर्णांक access_mode)
अणु
	पूर्णांक inlen = MLX5_ST_SZ_BYTES(create_mkey_in);
	पूर्णांक ndescs = ALIGN(max_num_sg + max_num_meta_sg, 4);
	पूर्णांक page_shअगरt = 0;
	काष्ठा mlx5_ib_mr *mr;
	u32 *in;
	पूर्णांक err;

	mr = kzalloc(माप(*mr), GFP_KERNEL);
	अगर (!mr)
		वापस ERR_PTR(-ENOMEM);

	mr->ibmr.pd = pd;
	mr->ibmr.device = pd->device;

	in = kzalloc(inlen, GFP_KERNEL);
	अगर (!in) अणु
		err = -ENOMEM;
		जाओ err_मुक्त;
	पूर्ण

	अगर (access_mode == MLX5_MKC_ACCESS_MODE_MTT)
		page_shअगरt = PAGE_SHIFT;

	err = _mlx5_alloc_mkey_descs(pd, mr, ndescs, desc_size, page_shअगरt,
				     access_mode, in, inlen);
	अगर (err)
		जाओ err_मुक्त_in;

	mr->umem = शून्य;
	kमुक्त(in);

	वापस mr;

err_मुक्त_in:
	kमुक्त(in);
err_मुक्त:
	kमुक्त(mr);
	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक mlx5_alloc_mem_reg_descs(काष्ठा ib_pd *pd, काष्ठा mlx5_ib_mr *mr,
				    पूर्णांक ndescs, u32 *in, पूर्णांक inlen)
अणु
	वापस _mlx5_alloc_mkey_descs(pd, mr, ndescs, माप(काष्ठा mlx5_mtt),
				      PAGE_SHIFT, MLX5_MKC_ACCESS_MODE_MTT, in,
				      inlen);
पूर्ण

अटल पूर्णांक mlx5_alloc_sg_gaps_descs(काष्ठा ib_pd *pd, काष्ठा mlx5_ib_mr *mr,
				    पूर्णांक ndescs, u32 *in, पूर्णांक inlen)
अणु
	वापस _mlx5_alloc_mkey_descs(pd, mr, ndescs, माप(काष्ठा mlx5_klm),
				      0, MLX5_MKC_ACCESS_MODE_KLMS, in, inlen);
पूर्ण

अटल पूर्णांक mlx5_alloc_पूर्णांकegrity_descs(काष्ठा ib_pd *pd, काष्ठा mlx5_ib_mr *mr,
				      पूर्णांक max_num_sg, पूर्णांक max_num_meta_sg,
				      u32 *in, पूर्णांक inlen)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(pd->device);
	u32 psv_index[2];
	व्योम *mkc;
	पूर्णांक err;

	mr->sig = kzalloc(माप(*mr->sig), GFP_KERNEL);
	अगर (!mr->sig)
		वापस -ENOMEM;

	/* create mem & wire PSVs */
	err = mlx5_core_create_psv(dev->mdev, to_mpd(pd)->pdn, 2, psv_index);
	अगर (err)
		जाओ err_मुक्त_sig;

	mr->sig->psv_memory.psv_idx = psv_index[0];
	mr->sig->psv_wire.psv_idx = psv_index[1];

	mr->sig->sig_status_checked = true;
	mr->sig->sig_err_exists = false;
	/* Next UMR, Arm SIGERR */
	++mr->sig->sigerr_count;
	mr->klm_mr = mlx5_ib_alloc_pi_mr(pd, max_num_sg, max_num_meta_sg,
					 माप(काष्ठा mlx5_klm),
					 MLX5_MKC_ACCESS_MODE_KLMS);
	अगर (IS_ERR(mr->klm_mr)) अणु
		err = PTR_ERR(mr->klm_mr);
		जाओ err_destroy_psv;
	पूर्ण
	mr->mtt_mr = mlx5_ib_alloc_pi_mr(pd, max_num_sg, max_num_meta_sg,
					 माप(काष्ठा mlx5_mtt),
					 MLX5_MKC_ACCESS_MODE_MTT);
	अगर (IS_ERR(mr->mtt_mr)) अणु
		err = PTR_ERR(mr->mtt_mr);
		जाओ err_मुक्त_klm_mr;
	पूर्ण

	/* Set bsf descriptors क्रम mkey */
	mkc = MLX5_ADDR_OF(create_mkey_in, in, memory_key_mkey_entry);
	MLX5_SET(mkc, mkc, bsf_en, 1);
	MLX5_SET(mkc, mkc, bsf_octword_size, MLX5_MKEY_BSF_OCTO_SIZE);

	err = _mlx5_alloc_mkey_descs(pd, mr, 4, माप(काष्ठा mlx5_klm), 0,
				     MLX5_MKC_ACCESS_MODE_KLMS, in, inlen);
	अगर (err)
		जाओ err_मुक्त_mtt_mr;

	err = xa_err(xa_store(&dev->sig_mrs, mlx5_base_mkey(mr->mmkey.key),
			      mr->sig, GFP_KERNEL));
	अगर (err)
		जाओ err_मुक्त_descs;
	वापस 0;

err_मुक्त_descs:
	destroy_mkey(dev, mr);
	mlx5_मुक्त_priv_descs(mr);
err_मुक्त_mtt_mr:
	mlx5_ib_dereg_mr(&mr->mtt_mr->ibmr, शून्य);
	mr->mtt_mr = शून्य;
err_मुक्त_klm_mr:
	mlx5_ib_dereg_mr(&mr->klm_mr->ibmr, शून्य);
	mr->klm_mr = शून्य;
err_destroy_psv:
	अगर (mlx5_core_destroy_psv(dev->mdev, mr->sig->psv_memory.psv_idx))
		mlx5_ib_warn(dev, "failed to destroy mem psv %d\n",
			     mr->sig->psv_memory.psv_idx);
	अगर (mlx5_core_destroy_psv(dev->mdev, mr->sig->psv_wire.psv_idx))
		mlx5_ib_warn(dev, "failed to destroy wire psv %d\n",
			     mr->sig->psv_wire.psv_idx);
err_मुक्त_sig:
	kमुक्त(mr->sig);

	वापस err;
पूर्ण

अटल काष्ठा ib_mr *__mlx5_ib_alloc_mr(काष्ठा ib_pd *pd,
					क्रमागत ib_mr_type mr_type, u32 max_num_sg,
					u32 max_num_meta_sg)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(pd->device);
	पूर्णांक inlen = MLX5_ST_SZ_BYTES(create_mkey_in);
	पूर्णांक ndescs = ALIGN(max_num_sg, 4);
	काष्ठा mlx5_ib_mr *mr;
	u32 *in;
	पूर्णांक err;

	mr = kzalloc(माप(*mr), GFP_KERNEL);
	अगर (!mr)
		वापस ERR_PTR(-ENOMEM);

	in = kzalloc(inlen, GFP_KERNEL);
	अगर (!in) अणु
		err = -ENOMEM;
		जाओ err_मुक्त;
	पूर्ण

	mr->ibmr.device = pd->device;
	mr->umem = शून्य;

	चयन (mr_type) अणु
	हाल IB_MR_TYPE_MEM_REG:
		err = mlx5_alloc_mem_reg_descs(pd, mr, ndescs, in, inlen);
		अवरोध;
	हाल IB_MR_TYPE_SG_GAPS:
		err = mlx5_alloc_sg_gaps_descs(pd, mr, ndescs, in, inlen);
		अवरोध;
	हाल IB_MR_TYPE_INTEGRITY:
		err = mlx5_alloc_पूर्णांकegrity_descs(pd, mr, max_num_sg,
						 max_num_meta_sg, in, inlen);
		अवरोध;
	शेष:
		mlx5_ib_warn(dev, "Invalid mr type %d\n", mr_type);
		err = -EINVAL;
	पूर्ण

	अगर (err)
		जाओ err_मुक्त_in;

	kमुक्त(in);

	वापस &mr->ibmr;

err_मुक्त_in:
	kमुक्त(in);
err_मुक्त:
	kमुक्त(mr);
	वापस ERR_PTR(err);
पूर्ण

काष्ठा ib_mr *mlx5_ib_alloc_mr(काष्ठा ib_pd *pd, क्रमागत ib_mr_type mr_type,
			       u32 max_num_sg)
अणु
	वापस __mlx5_ib_alloc_mr(pd, mr_type, max_num_sg, 0);
पूर्ण

काष्ठा ib_mr *mlx5_ib_alloc_mr_पूर्णांकegrity(काष्ठा ib_pd *pd,
					 u32 max_num_sg, u32 max_num_meta_sg)
अणु
	वापस __mlx5_ib_alloc_mr(pd, IB_MR_TYPE_INTEGRITY, max_num_sg,
				  max_num_meta_sg);
पूर्ण

पूर्णांक mlx5_ib_alloc_mw(काष्ठा ib_mw *ibmw, काष्ठा ib_udata *udata)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(ibmw->device);
	पूर्णांक inlen = MLX5_ST_SZ_BYTES(create_mkey_in);
	काष्ठा mlx5_ib_mw *mw = to_mmw(ibmw);
	u32 *in = शून्य;
	व्योम *mkc;
	पूर्णांक ndescs;
	पूर्णांक err;
	काष्ठा mlx5_ib_alloc_mw req = अणुपूर्ण;
	काष्ठा अणु
		__u32	comp_mask;
		__u32	response_length;
	पूर्ण resp = अणुपूर्ण;

	err = ib_copy_from_udata(&req, udata, min(udata->inlen, माप(req)));
	अगर (err)
		वापस err;

	अगर (req.comp_mask || req.reserved1 || req.reserved2)
		वापस -EOPNOTSUPP;

	अगर (udata->inlen > माप(req) &&
	    !ib_is_udata_cleared(udata, माप(req),
				 udata->inlen - माप(req)))
		वापस -EOPNOTSUPP;

	ndescs = req.num_klms ? roundup(req.num_klms, 4) : roundup(1, 4);

	in = kzalloc(inlen, GFP_KERNEL);
	अगर (!in) अणु
		err = -ENOMEM;
		जाओ मुक्त;
	पूर्ण

	mkc = MLX5_ADDR_OF(create_mkey_in, in, memory_key_mkey_entry);

	MLX5_SET(mkc, mkc, मुक्त, 1);
	MLX5_SET(mkc, mkc, translations_octword_size, ndescs);
	MLX5_SET(mkc, mkc, pd, to_mpd(ibmw->pd)->pdn);
	MLX5_SET(mkc, mkc, umr_en, 1);
	MLX5_SET(mkc, mkc, lr, 1);
	MLX5_SET(mkc, mkc, access_mode_1_0, MLX5_MKC_ACCESS_MODE_KLMS);
	MLX5_SET(mkc, mkc, en_rinval, !!((ibmw->type == IB_MW_TYPE_2)));
	MLX5_SET(mkc, mkc, qpn, 0xffffff);

	err = mlx5_ib_create_mkey(dev, &mw->mmkey, in, inlen);
	अगर (err)
		जाओ मुक्त;

	mw->mmkey.type = MLX5_MKEY_MW;
	ibmw->rkey = mw->mmkey.key;
	mw->ndescs = ndescs;

	resp.response_length =
		min(दुरत्वend(typeof(resp), response_length), udata->outlen);
	अगर (resp.response_length) अणु
		err = ib_copy_to_udata(udata, &resp, resp.response_length);
		अगर (err)
			जाओ मुक्त_mkey;
	पूर्ण

	अगर (IS_ENABLED(CONFIG_INFINIBAND_ON_DEMAND_PAGING)) अणु
		err = mlx5r_store_odp_mkey(dev, &mw->mmkey);
		अगर (err)
			जाओ मुक्त_mkey;
	पूर्ण

	kमुक्त(in);
	वापस 0;

मुक्त_mkey:
	mlx5_core_destroy_mkey(dev->mdev, &mw->mmkey);
मुक्त:
	kमुक्त(in);
	वापस err;
पूर्ण

पूर्णांक mlx5_ib_dealloc_mw(काष्ठा ib_mw *mw)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(mw->device);
	काष्ठा mlx5_ib_mw *mmw = to_mmw(mw);

	अगर (IS_ENABLED(CONFIG_INFINIBAND_ON_DEMAND_PAGING) &&
	    xa_erase(&dev->odp_mkeys, mlx5_base_mkey(mmw->mmkey.key)))
		/*
		 * pagefault_single_data_segment() may be accessing mmw
		 * अगर the user bound an ODP MR to this MW.
		 */
		mlx5r_deref_रुको_odp_mkey(&mmw->mmkey);

	वापस mlx5_core_destroy_mkey(dev->mdev, &mmw->mmkey);
पूर्ण

पूर्णांक mlx5_ib_check_mr_status(काष्ठा ib_mr *ibmr, u32 check_mask,
			    काष्ठा ib_mr_status *mr_status)
अणु
	काष्ठा mlx5_ib_mr *mmr = to_mmr(ibmr);
	पूर्णांक ret = 0;

	अगर (check_mask & ~IB_MR_CHECK_SIG_STATUS) अणु
		pr_err("Invalid status check mask\n");
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	mr_status->fail_status = 0;
	अगर (check_mask & IB_MR_CHECK_SIG_STATUS) अणु
		अगर (!mmr->sig) अणु
			ret = -EINVAL;
			pr_err("signature status check requested on a non-signature enabled MR\n");
			जाओ करोne;
		पूर्ण

		mmr->sig->sig_status_checked = true;
		अगर (!mmr->sig->sig_err_exists)
			जाओ करोne;

		अगर (ibmr->lkey == mmr->sig->err_item.key)
			स_नकल(&mr_status->sig_err, &mmr->sig->err_item,
			       माप(mr_status->sig_err));
		अन्यथा अणु
			mr_status->sig_err.err_type = IB_SIG_BAD_GUARD;
			mr_status->sig_err.sig_err_offset = 0;
			mr_status->sig_err.key = mmr->sig->err_item.key;
		पूर्ण

		mmr->sig->sig_err_exists = false;
		mr_status->fail_status |= IB_MR_CHECK_SIG_STATUS;
	पूर्ण

करोne:
	वापस ret;
पूर्ण

अटल पूर्णांक
mlx5_ib_map_pa_mr_sg_pi(काष्ठा ib_mr *ibmr, काष्ठा scatterlist *data_sg,
			पूर्णांक data_sg_nents, अचिन्हित पूर्णांक *data_sg_offset,
			काष्ठा scatterlist *meta_sg, पूर्णांक meta_sg_nents,
			अचिन्हित पूर्णांक *meta_sg_offset)
अणु
	काष्ठा mlx5_ib_mr *mr = to_mmr(ibmr);
	अचिन्हित पूर्णांक sg_offset = 0;
	पूर्णांक n = 0;

	mr->meta_length = 0;
	अगर (data_sg_nents == 1) अणु
		n++;
		mr->ndescs = 1;
		अगर (data_sg_offset)
			sg_offset = *data_sg_offset;
		mr->data_length = sg_dma_len(data_sg) - sg_offset;
		mr->data_iova = sg_dma_address(data_sg) + sg_offset;
		अगर (meta_sg_nents == 1) अणु
			n++;
			mr->meta_ndescs = 1;
			अगर (meta_sg_offset)
				sg_offset = *meta_sg_offset;
			अन्यथा
				sg_offset = 0;
			mr->meta_length = sg_dma_len(meta_sg) - sg_offset;
			mr->pi_iova = sg_dma_address(meta_sg) + sg_offset;
		पूर्ण
		ibmr->length = mr->data_length + mr->meta_length;
	पूर्ण

	वापस n;
पूर्ण

अटल पूर्णांक
mlx5_ib_sg_to_klms(काष्ठा mlx5_ib_mr *mr,
		   काष्ठा scatterlist *sgl,
		   अचिन्हित लघु sg_nents,
		   अचिन्हित पूर्णांक *sg_offset_p,
		   काष्ठा scatterlist *meta_sgl,
		   अचिन्हित लघु meta_sg_nents,
		   अचिन्हित पूर्णांक *meta_sg_offset_p)
अणु
	काष्ठा scatterlist *sg = sgl;
	काष्ठा mlx5_klm *klms = mr->descs;
	अचिन्हित पूर्णांक sg_offset = sg_offset_p ? *sg_offset_p : 0;
	u32 lkey = mr->ibmr.pd->local_dma_lkey;
	पूर्णांक i, j = 0;

	mr->ibmr.iova = sg_dma_address(sg) + sg_offset;
	mr->ibmr.length = 0;

	क्रम_each_sg(sgl, sg, sg_nents, i) अणु
		अगर (unlikely(i >= mr->max_descs))
			अवरोध;
		klms[i].va = cpu_to_be64(sg_dma_address(sg) + sg_offset);
		klms[i].bcount = cpu_to_be32(sg_dma_len(sg) - sg_offset);
		klms[i].key = cpu_to_be32(lkey);
		mr->ibmr.length += sg_dma_len(sg) - sg_offset;

		sg_offset = 0;
	पूर्ण

	अगर (sg_offset_p)
		*sg_offset_p = sg_offset;

	mr->ndescs = i;
	mr->data_length = mr->ibmr.length;

	अगर (meta_sg_nents) अणु
		sg = meta_sgl;
		sg_offset = meta_sg_offset_p ? *meta_sg_offset_p : 0;
		क्रम_each_sg(meta_sgl, sg, meta_sg_nents, j) अणु
			अगर (unlikely(i + j >= mr->max_descs))
				अवरोध;
			klms[i + j].va = cpu_to_be64(sg_dma_address(sg) +
						     sg_offset);
			klms[i + j].bcount = cpu_to_be32(sg_dma_len(sg) -
							 sg_offset);
			klms[i + j].key = cpu_to_be32(lkey);
			mr->ibmr.length += sg_dma_len(sg) - sg_offset;

			sg_offset = 0;
		पूर्ण
		अगर (meta_sg_offset_p)
			*meta_sg_offset_p = sg_offset;

		mr->meta_ndescs = j;
		mr->meta_length = mr->ibmr.length - mr->data_length;
	पूर्ण

	वापस i + j;
पूर्ण

अटल पूर्णांक mlx5_set_page(काष्ठा ib_mr *ibmr, u64 addr)
अणु
	काष्ठा mlx5_ib_mr *mr = to_mmr(ibmr);
	__be64 *descs;

	अगर (unlikely(mr->ndescs == mr->max_descs))
		वापस -ENOMEM;

	descs = mr->descs;
	descs[mr->ndescs++] = cpu_to_be64(addr | MLX5_EN_RD | MLX5_EN_WR);

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5_set_page_pi(काष्ठा ib_mr *ibmr, u64 addr)
अणु
	काष्ठा mlx5_ib_mr *mr = to_mmr(ibmr);
	__be64 *descs;

	अगर (unlikely(mr->ndescs + mr->meta_ndescs == mr->max_descs))
		वापस -ENOMEM;

	descs = mr->descs;
	descs[mr->ndescs + mr->meta_ndescs++] =
		cpu_to_be64(addr | MLX5_EN_RD | MLX5_EN_WR);

	वापस 0;
पूर्ण

अटल पूर्णांक
mlx5_ib_map_mtt_mr_sg_pi(काष्ठा ib_mr *ibmr, काष्ठा scatterlist *data_sg,
			 पूर्णांक data_sg_nents, अचिन्हित पूर्णांक *data_sg_offset,
			 काष्ठा scatterlist *meta_sg, पूर्णांक meta_sg_nents,
			 अचिन्हित पूर्णांक *meta_sg_offset)
अणु
	काष्ठा mlx5_ib_mr *mr = to_mmr(ibmr);
	काष्ठा mlx5_ib_mr *pi_mr = mr->mtt_mr;
	पूर्णांक n;

	pi_mr->ndescs = 0;
	pi_mr->meta_ndescs = 0;
	pi_mr->meta_length = 0;

	ib_dma_sync_single_क्रम_cpu(ibmr->device, pi_mr->desc_map,
				   pi_mr->desc_size * pi_mr->max_descs,
				   DMA_TO_DEVICE);

	pi_mr->ibmr.page_size = ibmr->page_size;
	n = ib_sg_to_pages(&pi_mr->ibmr, data_sg, data_sg_nents, data_sg_offset,
			   mlx5_set_page);
	अगर (n != data_sg_nents)
		वापस n;

	pi_mr->data_iova = pi_mr->ibmr.iova;
	pi_mr->data_length = pi_mr->ibmr.length;
	pi_mr->ibmr.length = pi_mr->data_length;
	ibmr->length = pi_mr->data_length;

	अगर (meta_sg_nents) अणु
		u64 page_mask = ~((u64)ibmr->page_size - 1);
		u64 iova = pi_mr->data_iova;

		n += ib_sg_to_pages(&pi_mr->ibmr, meta_sg, meta_sg_nents,
				    meta_sg_offset, mlx5_set_page_pi);

		pi_mr->meta_length = pi_mr->ibmr.length;
		/*
		 * PI address क्रम the HW is the offset of the metadata address
		 * relative to the first data page address.
		 * It equals to first data page address + size of data pages +
		 * metadata offset at the first metadata page
		 */
		pi_mr->pi_iova = (iova & page_mask) +
				 pi_mr->ndescs * ibmr->page_size +
				 (pi_mr->ibmr.iova & ~page_mask);
		/*
		 * In order to use one MTT MR क्रम data and metadata, we रेजिस्टर
		 * also the gaps between the end of the data and the start of
		 * the metadata (the sig MR will verअगरy that the HW will access
		 * to right addresses). This mapping is safe because we use
		 * पूर्णांकernal mkey क्रम the registration.
		 */
		pi_mr->ibmr.length = pi_mr->pi_iova + pi_mr->meta_length - iova;
		pi_mr->ibmr.iova = iova;
		ibmr->length += pi_mr->meta_length;
	पूर्ण

	ib_dma_sync_single_क्रम_device(ibmr->device, pi_mr->desc_map,
				      pi_mr->desc_size * pi_mr->max_descs,
				      DMA_TO_DEVICE);

	वापस n;
पूर्ण

अटल पूर्णांक
mlx5_ib_map_klm_mr_sg_pi(काष्ठा ib_mr *ibmr, काष्ठा scatterlist *data_sg,
			 पूर्णांक data_sg_nents, अचिन्हित पूर्णांक *data_sg_offset,
			 काष्ठा scatterlist *meta_sg, पूर्णांक meta_sg_nents,
			 अचिन्हित पूर्णांक *meta_sg_offset)
अणु
	काष्ठा mlx5_ib_mr *mr = to_mmr(ibmr);
	काष्ठा mlx5_ib_mr *pi_mr = mr->klm_mr;
	पूर्णांक n;

	pi_mr->ndescs = 0;
	pi_mr->meta_ndescs = 0;
	pi_mr->meta_length = 0;

	ib_dma_sync_single_क्रम_cpu(ibmr->device, pi_mr->desc_map,
				   pi_mr->desc_size * pi_mr->max_descs,
				   DMA_TO_DEVICE);

	n = mlx5_ib_sg_to_klms(pi_mr, data_sg, data_sg_nents, data_sg_offset,
			       meta_sg, meta_sg_nents, meta_sg_offset);

	ib_dma_sync_single_क्रम_device(ibmr->device, pi_mr->desc_map,
				      pi_mr->desc_size * pi_mr->max_descs,
				      DMA_TO_DEVICE);

	/* This is zero-based memory region */
	pi_mr->data_iova = 0;
	pi_mr->ibmr.iova = 0;
	pi_mr->pi_iova = pi_mr->data_length;
	ibmr->length = pi_mr->ibmr.length;

	वापस n;
पूर्ण

पूर्णांक mlx5_ib_map_mr_sg_pi(काष्ठा ib_mr *ibmr, काष्ठा scatterlist *data_sg,
			 पूर्णांक data_sg_nents, अचिन्हित पूर्णांक *data_sg_offset,
			 काष्ठा scatterlist *meta_sg, पूर्णांक meta_sg_nents,
			 अचिन्हित पूर्णांक *meta_sg_offset)
अणु
	काष्ठा mlx5_ib_mr *mr = to_mmr(ibmr);
	काष्ठा mlx5_ib_mr *pi_mr = शून्य;
	पूर्णांक n;

	WARN_ON(ibmr->type != IB_MR_TYPE_INTEGRITY);

	mr->ndescs = 0;
	mr->data_length = 0;
	mr->data_iova = 0;
	mr->meta_ndescs = 0;
	mr->pi_iova = 0;
	/*
	 * As a perक्रमmance optimization, अगर possible, there is no need to
	 * perक्रमm UMR operation to रेजिस्टर the data/metadata buffers.
	 * First try to map the sg lists to PA descriptors with local_dma_lkey.
	 * Fallback to UMR only in हाल of a failure.
	 */
	n = mlx5_ib_map_pa_mr_sg_pi(ibmr, data_sg, data_sg_nents,
				    data_sg_offset, meta_sg, meta_sg_nents,
				    meta_sg_offset);
	अगर (n == data_sg_nents + meta_sg_nents)
		जाओ out;
	/*
	 * As a perक्रमmance optimization, अगर possible, there is no need to map
	 * the sg lists to KLM descriptors. First try to map the sg lists to MTT
	 * descriptors and fallback to KLM only in हाल of a failure.
	 * It's more efficient क्रम the HW to work with MTT descriptors
	 * (especially in high load).
	 * Use KLM (indirect access) only अगर it's mandatory.
	 */
	pi_mr = mr->mtt_mr;
	n = mlx5_ib_map_mtt_mr_sg_pi(ibmr, data_sg, data_sg_nents,
				     data_sg_offset, meta_sg, meta_sg_nents,
				     meta_sg_offset);
	अगर (n == data_sg_nents + meta_sg_nents)
		जाओ out;

	pi_mr = mr->klm_mr;
	n = mlx5_ib_map_klm_mr_sg_pi(ibmr, data_sg, data_sg_nents,
				     data_sg_offset, meta_sg, meta_sg_nents,
				     meta_sg_offset);
	अगर (unlikely(n != data_sg_nents + meta_sg_nents))
		वापस -ENOMEM;

out:
	/* This is zero-based memory region */
	ibmr->iova = 0;
	mr->pi_mr = pi_mr;
	अगर (pi_mr)
		ibmr->sig_attrs->meta_length = pi_mr->meta_length;
	अन्यथा
		ibmr->sig_attrs->meta_length = mr->meta_length;

	वापस 0;
पूर्ण

पूर्णांक mlx5_ib_map_mr_sg(काष्ठा ib_mr *ibmr, काष्ठा scatterlist *sg, पूर्णांक sg_nents,
		      अचिन्हित पूर्णांक *sg_offset)
अणु
	काष्ठा mlx5_ib_mr *mr = to_mmr(ibmr);
	पूर्णांक n;

	mr->ndescs = 0;

	ib_dma_sync_single_क्रम_cpu(ibmr->device, mr->desc_map,
				   mr->desc_size * mr->max_descs,
				   DMA_TO_DEVICE);

	अगर (mr->access_mode == MLX5_MKC_ACCESS_MODE_KLMS)
		n = mlx5_ib_sg_to_klms(mr, sg, sg_nents, sg_offset, शून्य, 0,
				       शून्य);
	अन्यथा
		n = ib_sg_to_pages(ibmr, sg, sg_nents, sg_offset,
				mlx5_set_page);

	ib_dma_sync_single_क्रम_device(ibmr->device, mr->desc_map,
				      mr->desc_size * mr->max_descs,
				      DMA_TO_DEVICE);

	वापस n;
पूर्ण
