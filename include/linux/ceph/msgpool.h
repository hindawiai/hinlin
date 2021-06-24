<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _FS_CEPH_MSGPOOL
#घोषणा _FS_CEPH_MSGPOOL

#समावेश <linux/mempool.h>

/*
 * we use memory pools क्रम pपुनः_स्मृतिating messages we may receive, to
 * aव्योम unexpected OOM conditions.
 */
काष्ठा ceph_msgpool अणु
	स्थिर अक्षर *name;
	mempool_t *pool;
	पूर्णांक type;               /* pपुनः_स्मृतिated message type */
	पूर्णांक front_len;          /* pपुनः_स्मृतिated payload size */
	पूर्णांक max_data_items;
पूर्ण;

पूर्णांक ceph_msgpool_init(काष्ठा ceph_msgpool *pool, पूर्णांक type,
		      पूर्णांक front_len, पूर्णांक max_data_items, पूर्णांक size,
		      स्थिर अक्षर *name);
बाह्य व्योम ceph_msgpool_destroy(काष्ठा ceph_msgpool *pool);
काष्ठा ceph_msg *ceph_msgpool_get(काष्ठा ceph_msgpool *pool, पूर्णांक front_len,
				  पूर्णांक max_data_items);
बाह्य व्योम ceph_msgpool_put(काष्ठा ceph_msgpool *, काष्ठा ceph_msg *);

#पूर्ण_अगर
