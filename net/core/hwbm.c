<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Support क्रम hardware buffer manager.
 *
 * Copyright (C) 2016 Marvell
 *
 * Gregory CLEMENT <gregory.clement@मुक्त-electrons.com>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/skbuff.h>
#समावेश <net/hwbm.h>

व्योम hwbm_buf_मुक्त(काष्ठा hwbm_pool *bm_pool, व्योम *buf)
अणु
	अगर (likely(bm_pool->frag_size <= PAGE_SIZE))
		skb_मुक्त_frag(buf);
	अन्यथा
		kमुक्त(buf);
पूर्ण
EXPORT_SYMBOL_GPL(hwbm_buf_मुक्त);

/* Refill processing क्रम HW buffer management */
पूर्णांक hwbm_pool_refill(काष्ठा hwbm_pool *bm_pool, gfp_t gfp)
अणु
	पूर्णांक frag_size = bm_pool->frag_size;
	व्योम *buf;

	अगर (likely(frag_size <= PAGE_SIZE))
		buf = netdev_alloc_frag(frag_size);
	अन्यथा
		buf = kदो_स्मृति(frag_size, gfp);

	अगर (!buf)
		वापस -ENOMEM;

	अगर (bm_pool->स्थिरruct)
		अगर (bm_pool->स्थिरruct(bm_pool, buf)) अणु
			hwbm_buf_मुक्त(bm_pool, buf);
			वापस -ENOMEM;
		पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(hwbm_pool_refill);

पूर्णांक hwbm_pool_add(काष्ठा hwbm_pool *bm_pool, अचिन्हित पूर्णांक buf_num)
अणु
	पूर्णांक err, i;

	mutex_lock(&bm_pool->buf_lock);
	अगर (bm_pool->buf_num == bm_pool->size) अणु
		pr_warn("pool already filled\n");
		mutex_unlock(&bm_pool->buf_lock);
		वापस bm_pool->buf_num;
	पूर्ण

	अगर (buf_num + bm_pool->buf_num > bm_pool->size) अणु
		pr_warn("cannot allocate %d buffers for pool\n",
			buf_num);
		mutex_unlock(&bm_pool->buf_lock);
		वापस 0;
	पूर्ण

	अगर ((buf_num + bm_pool->buf_num) < bm_pool->buf_num) अणु
		pr_warn("Adding %d buffers to the %d current buffers will overflow\n",
			buf_num,  bm_pool->buf_num);
		mutex_unlock(&bm_pool->buf_lock);
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < buf_num; i++) अणु
		err = hwbm_pool_refill(bm_pool, GFP_KERNEL);
		अगर (err < 0)
			अवरोध;
	पूर्ण

	/* Update BM driver with number of buffers added to pool */
	bm_pool->buf_num += i;

	pr_debug("hwpm pool: %d of %d buffers added\n", i, buf_num);
	mutex_unlock(&bm_pool->buf_lock);

	वापस i;
पूर्ण
EXPORT_SYMBOL_GPL(hwbm_pool_add);
