<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ZBUD_H_
#घोषणा _ZBUD_H_

#समावेश <linux/types.h>

काष्ठा zbud_pool;

काष्ठा zbud_ops अणु
	पूर्णांक (*evict)(काष्ठा zbud_pool *pool, अचिन्हित दीर्घ handle);
पूर्ण;

काष्ठा zbud_pool *zbud_create_pool(gfp_t gfp, स्थिर काष्ठा zbud_ops *ops);
व्योम zbud_destroy_pool(काष्ठा zbud_pool *pool);
पूर्णांक zbud_alloc(काष्ठा zbud_pool *pool, माप_प्रकार size, gfp_t gfp,
	अचिन्हित दीर्घ *handle);
व्योम zbud_मुक्त(काष्ठा zbud_pool *pool, अचिन्हित दीर्घ handle);
पूर्णांक zbud_reclaim_page(काष्ठा zbud_pool *pool, अचिन्हित पूर्णांक retries);
व्योम *zbud_map(काष्ठा zbud_pool *pool, अचिन्हित दीर्घ handle);
व्योम zbud_unmap(काष्ठा zbud_pool *pool, अचिन्हित दीर्घ handle);
u64 zbud_get_pool_size(काष्ठा zbud_pool *pool);

#पूर्ण_अगर /* _ZBUD_H_ */
