<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * (C) 2001 Clemson University and The University of Chicago
 *
 * See COPYING in top-level directory.
 */

#अगर_अघोषित __ORANGEFS_BUFMAP_H
#घोषणा __ORANGEFS_BUFMAP_H

पूर्णांक orangefs_bufmap_size_query(व्योम);

पूर्णांक orangefs_bufmap_shअगरt_query(व्योम);

पूर्णांक orangefs_bufmap_initialize(काष्ठा ORANGEFS_dev_map_desc *user_desc);

व्योम orangefs_bufmap_finalize(व्योम);

व्योम orangefs_bufmap_run_करोwn(व्योम);

पूर्णांक orangefs_bufmap_get(व्योम);

व्योम orangefs_bufmap_put(पूर्णांक buffer_index);

पूर्णांक orangefs_सूची_पढ़ो_index_get(व्योम);

व्योम orangefs_सूची_पढ़ो_index_put(पूर्णांक buffer_index);

पूर्णांक orangefs_bufmap_copy_from_iovec(काष्ठा iov_iter *iter,
				पूर्णांक buffer_index,
				माप_प्रकार size);

पूर्णांक orangefs_bufmap_copy_to_iovec(काष्ठा iov_iter *iter,
			      पूर्णांक buffer_index,
			      माप_प्रकार size);

व्योम orangefs_bufmap_page_fill(व्योम *kaddr, पूर्णांक buffer_index, पूर्णांक slot_index);

#पूर्ण_अगर /* __ORANGEFS_BUFMAP_H */
