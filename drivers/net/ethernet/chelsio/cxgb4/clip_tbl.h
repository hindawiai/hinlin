<शैली गुरु>
/*
 *  This file is part of the Chelsio T4 Ethernet driver क्रम Linux.
 *  Copyright (C) 2003-2014 Chelsio Communications.  All rights reserved.
 *
 *  Written by Deepak (deepak.s@chelsio.com)
 *
 *  This program is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the LICENSE file included in this
 *  release क्रम licensing terms and conditions.
 */

#समावेश <linux/refcount.h>

काष्ठा clip_entry अणु
	spinlock_t lock;	/* Hold जबतक modअगरying clip reference */
	refcount_t refcnt;
	काष्ठा list_head list;
	जोड़ अणु
		काष्ठा sockaddr_in addr;
		काष्ठा sockaddr_in6 addr6;
	पूर्ण;
पूर्ण;

काष्ठा clip_tbl अणु
	अचिन्हित पूर्णांक clipt_start;
	अचिन्हित पूर्णांक clipt_size;
	rwlock_t lock;
	atomic_t nमुक्त;
	काष्ठा list_head ce_मुक्त_head;
	व्योम *cl_list;
	काष्ठा list_head hash_list[];
पूर्ण;

क्रमागत अणु
	CLIPT_MIN_HASH_BUCKETS = 2,
पूर्ण;

काष्ठा clip_tbl *t4_init_clip_tbl(अचिन्हित पूर्णांक clipt_start,
				  अचिन्हित पूर्णांक clipt_end);
पूर्णांक cxgb4_clip_get(स्थिर काष्ठा net_device *dev, स्थिर u32 *lip, u8 v6);
व्योम cxgb4_clip_release(स्थिर काष्ठा net_device *dev, स्थिर u32 *lip, u8 v6);
पूर्णांक clip_tbl_show(काष्ठा seq_file *seq, व्योम *v);
पूर्णांक cxgb4_update_root_dev_clip(काष्ठा net_device *dev);
व्योम t4_cleanup_clip_tbl(काष्ठा adapter *adap);
