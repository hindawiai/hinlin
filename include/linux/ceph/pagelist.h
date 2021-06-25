<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __FS_CEPH_PAGELIST_H
#घोषणा __FS_CEPH_PAGELIST_H

#समावेश <यंत्र/byteorder.h>
#समावेश <linux/refcount.h>
#समावेश <linux/list.h>
#समावेश <linux/types.h>

काष्ठा ceph_pagelist अणु
	काष्ठा list_head head;
	व्योम *mapped_tail;
	माप_प्रकार length;
	माप_प्रकार room;
	काष्ठा list_head मुक्त_list;
	माप_प्रकार num_pages_मुक्त;
	refcount_t refcnt;
पूर्ण;

काष्ठा ceph_pagelist_cursor अणु
	काष्ठा ceph_pagelist *pl;   /* pagelist, क्रम error checking */
	काष्ठा list_head *page_lru; /* page in list */
	माप_प्रकार room;		    /* room reमुख्यing to reset to */
पूर्ण;

काष्ठा ceph_pagelist *ceph_pagelist_alloc(gfp_t gfp_flags);

बाह्य व्योम ceph_pagelist_release(काष्ठा ceph_pagelist *pl);

बाह्य पूर्णांक ceph_pagelist_append(काष्ठा ceph_pagelist *pl, स्थिर व्योम *d, माप_प्रकार l);

बाह्य पूर्णांक ceph_pagelist_reserve(काष्ठा ceph_pagelist *pl, माप_प्रकार space);

बाह्य पूर्णांक ceph_pagelist_मुक्त_reserve(काष्ठा ceph_pagelist *pl);

बाह्य व्योम ceph_pagelist_set_cursor(काष्ठा ceph_pagelist *pl,
				     काष्ठा ceph_pagelist_cursor *c);

बाह्य पूर्णांक ceph_pagelist_truncate(काष्ठा ceph_pagelist *pl,
				  काष्ठा ceph_pagelist_cursor *c);

अटल अंतरभूत पूर्णांक ceph_pagelist_encode_64(काष्ठा ceph_pagelist *pl, u64 v)
अणु
	__le64 ev = cpu_to_le64(v);
	वापस ceph_pagelist_append(pl, &ev, माप(ev));
पूर्ण
अटल अंतरभूत पूर्णांक ceph_pagelist_encode_32(काष्ठा ceph_pagelist *pl, u32 v)
अणु
	__le32 ev = cpu_to_le32(v);
	वापस ceph_pagelist_append(pl, &ev, माप(ev));
पूर्ण
अटल अंतरभूत पूर्णांक ceph_pagelist_encode_16(काष्ठा ceph_pagelist *pl, u16 v)
अणु
	__le16 ev = cpu_to_le16(v);
	वापस ceph_pagelist_append(pl, &ev, माप(ev));
पूर्ण
अटल अंतरभूत पूर्णांक ceph_pagelist_encode_8(काष्ठा ceph_pagelist *pl, u8 v)
अणु
	वापस ceph_pagelist_append(pl, &v, 1);
पूर्ण
अटल अंतरभूत पूर्णांक ceph_pagelist_encode_string(काष्ठा ceph_pagelist *pl,
					      अक्षर *s, u32 len)
अणु
	पूर्णांक ret = ceph_pagelist_encode_32(pl, len);
	अगर (ret)
		वापस ret;
	अगर (len)
		वापस ceph_pagelist_append(pl, s, len);
	वापस 0;
पूर्ण

#पूर्ण_अगर
