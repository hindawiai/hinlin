<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __FS_CEPH_BUFFER_H
#घोषणा __FS_CEPH_BUFFER_H

#समावेश <linux/kref.h>
#समावेश <linux/mm.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/types.h>
#समावेश <linux/uपन.स>

/*
 * a simple reference counted buffer.
 *
 * use kदो_स्मृति क्रम smaller sizes, vदो_स्मृति क्रम larger sizes.
 */
काष्ठा ceph_buffer अणु
	काष्ठा kref kref;
	काष्ठा kvec vec;
	माप_प्रकार alloc_len;
पूर्ण;

बाह्य काष्ठा ceph_buffer *ceph_buffer_new(माप_प्रकार len, gfp_t gfp);
बाह्य व्योम ceph_buffer_release(काष्ठा kref *kref);

अटल अंतरभूत काष्ठा ceph_buffer *ceph_buffer_get(काष्ठा ceph_buffer *b)
अणु
	kref_get(&b->kref);
	वापस b;
पूर्ण

अटल अंतरभूत व्योम ceph_buffer_put(काष्ठा ceph_buffer *b)
अणु
	अगर (b)
		kref_put(&b->kref, ceph_buffer_release);
पूर्ण

बाह्य पूर्णांक ceph_decode_buffer(काष्ठा ceph_buffer **b, व्योम **p, व्योम *end);

#पूर्ण_अगर
