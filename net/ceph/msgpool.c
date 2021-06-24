<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/ceph/ceph_debug.h>

#समावेश <linux/err.h>
#समावेश <linux/sched.h>
#समावेश <linux/types.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <linux/ceph/messenger.h>
#समावेश <linux/ceph/msgpool.h>

अटल व्योम *msgpool_alloc(gfp_t gfp_mask, व्योम *arg)
अणु
	काष्ठा ceph_msgpool *pool = arg;
	काष्ठा ceph_msg *msg;

	msg = ceph_msg_new2(pool->type, pool->front_len, pool->max_data_items,
			    gfp_mask, true);
	अगर (!msg) अणु
		करोut("msgpool_alloc %s failed\n", pool->name);
	पूर्ण अन्यथा अणु
		करोut("msgpool_alloc %s %p\n", pool->name, msg);
		msg->pool = pool;
	पूर्ण
	वापस msg;
पूर्ण

अटल व्योम msgpool_मुक्त(व्योम *element, व्योम *arg)
अणु
	काष्ठा ceph_msgpool *pool = arg;
	काष्ठा ceph_msg *msg = element;

	करोut("msgpool_release %s %p\n", pool->name, msg);
	msg->pool = शून्य;
	ceph_msg_put(msg);
पूर्ण

पूर्णांक ceph_msgpool_init(काष्ठा ceph_msgpool *pool, पूर्णांक type,
		      पूर्णांक front_len, पूर्णांक max_data_items, पूर्णांक size,
		      स्थिर अक्षर *name)
अणु
	करोut("msgpool %s init\n", name);
	pool->type = type;
	pool->front_len = front_len;
	pool->max_data_items = max_data_items;
	pool->pool = mempool_create(size, msgpool_alloc, msgpool_मुक्त, pool);
	अगर (!pool->pool)
		वापस -ENOMEM;
	pool->name = name;
	वापस 0;
पूर्ण

व्योम ceph_msgpool_destroy(काष्ठा ceph_msgpool *pool)
अणु
	करोut("msgpool %s destroy\n", pool->name);
	mempool_destroy(pool->pool);
पूर्ण

काष्ठा ceph_msg *ceph_msgpool_get(काष्ठा ceph_msgpool *pool, पूर्णांक front_len,
				  पूर्णांक max_data_items)
अणु
	काष्ठा ceph_msg *msg;

	अगर (front_len > pool->front_len ||
	    max_data_items > pool->max_data_items) अणु
		pr_warn_ratelimited("%s need %d/%d, pool %s has %d/%d\n",
		    __func__, front_len, max_data_items, pool->name,
		    pool->front_len, pool->max_data_items);
		WARN_ON_ONCE(1);

		/* try to alloc a fresh message */
		वापस ceph_msg_new2(pool->type, front_len, max_data_items,
				     GFP_NOFS, false);
	पूर्ण

	msg = mempool_alloc(pool->pool, GFP_NOFS);
	करोut("msgpool_get %s %p\n", pool->name, msg);
	वापस msg;
पूर्ण

व्योम ceph_msgpool_put(काष्ठा ceph_msgpool *pool, काष्ठा ceph_msg *msg)
अणु
	करोut("msgpool_put %s %p\n", pool->name, msg);

	/* reset msg front_len; user may have changed it */
	msg->front.iov_len = pool->front_len;
	msg->hdr.front_len = cpu_to_le32(pool->front_len);

	msg->data_length = 0;
	msg->num_data_items = 0;

	kref_init(&msg->kref);  /* retake single ref */
	mempool_मुक्त(msg, pool->pool);
पूर्ण
