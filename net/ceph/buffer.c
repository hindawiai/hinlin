<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/ceph/ceph_debug.h>

#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश <linux/ceph/buffer.h>
#समावेश <linux/ceph/decode.h>
#समावेश <linux/ceph/libceph.h> /* क्रम ceph_kvदो_स्मृति */

काष्ठा ceph_buffer *ceph_buffer_new(माप_प्रकार len, gfp_t gfp)
अणु
	काष्ठा ceph_buffer *b;

	b = kदो_स्मृति(माप(*b), gfp);
	अगर (!b)
		वापस शून्य;

	b->vec.iov_base = ceph_kvदो_स्मृति(len, gfp);
	अगर (!b->vec.iov_base) अणु
		kमुक्त(b);
		वापस शून्य;
	पूर्ण

	kref_init(&b->kref);
	b->alloc_len = len;
	b->vec.iov_len = len;
	करोut("buffer_new %p\n", b);
	वापस b;
पूर्ण
EXPORT_SYMBOL(ceph_buffer_new);

व्योम ceph_buffer_release(काष्ठा kref *kref)
अणु
	काष्ठा ceph_buffer *b = container_of(kref, काष्ठा ceph_buffer, kref);

	करोut("buffer_release %p\n", b);
	kvमुक्त(b->vec.iov_base);
	kमुक्त(b);
पूर्ण
EXPORT_SYMBOL(ceph_buffer_release);

पूर्णांक ceph_decode_buffer(काष्ठा ceph_buffer **b, व्योम **p, व्योम *end)
अणु
	माप_प्रकार len;

	ceph_decode_need(p, end, माप(u32), bad);
	len = ceph_decode_32(p);
	करोut("decode_buffer len %d\n", (पूर्णांक)len);
	ceph_decode_need(p, end, len, bad);
	*b = ceph_buffer_new(len, GFP_NOFS);
	अगर (!*b)
		वापस -ENOMEM;
	ceph_decode_copy(p, (*b)->vec.iov_base, len);
	वापस 0;
bad:
	वापस -EINVAL;
पूर्ण
