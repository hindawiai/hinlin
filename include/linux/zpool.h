<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * zpool memory storage api
 *
 * Copyright (C) 2014 Dan Streeपंचांगan
 *
 * This is a common frontend क्रम the zbud and zsदो_स्मृति memory
 * storage pool implementations.  Typically, this is used to
 * store compressed memory.
 */

#अगर_अघोषित _ZPOOL_H_
#घोषणा _ZPOOL_H_

काष्ठा zpool;

काष्ठा zpool_ops अणु
	पूर्णांक (*evict)(काष्ठा zpool *pool, अचिन्हित दीर्घ handle);
पूर्ण;

/*
 * Control how a handle is mapped.  It will be ignored अगर the
 * implementation करोes not support it.  Its use is optional.
 * Note that this करोes not refer to memory protection, it
 * refers to how the memory will be copied in/out अगर copying
 * is necessary during mapping; पढ़ो-ग_लिखो is the safest as
 * it copies the existing memory in on map, and copies the
 * changed memory back out on unmap.  Write-only करोes not copy
 * in the memory and should only be used क्रम initialization.
 * If in करोubt, use ZPOOL_MM_DEFAULT which is पढ़ो-ग_लिखो.
 */
क्रमागत zpool_mapmode अणु
	ZPOOL_MM_RW, /* normal पढ़ो-ग_लिखो mapping */
	ZPOOL_MM_RO, /* पढ़ो-only (no copy-out at unmap समय) */
	ZPOOL_MM_WO, /* ग_लिखो-only (no copy-in at map समय) */

	ZPOOL_MM_DEFAULT = ZPOOL_MM_RW
पूर्ण;

bool zpool_has_pool(अक्षर *type);

काष्ठा zpool *zpool_create_pool(स्थिर अक्षर *type, स्थिर अक्षर *name,
			gfp_t gfp, स्थिर काष्ठा zpool_ops *ops);

स्थिर अक्षर *zpool_get_type(काष्ठा zpool *pool);

व्योम zpool_destroy_pool(काष्ठा zpool *pool);

bool zpool_दो_स्मृति_support_movable(काष्ठा zpool *pool);

पूर्णांक zpool_दो_स्मृति(काष्ठा zpool *pool, माप_प्रकार size, gfp_t gfp,
			अचिन्हित दीर्घ *handle);

व्योम zpool_मुक्त(काष्ठा zpool *pool, अचिन्हित दीर्घ handle);

पूर्णांक zpool_shrink(काष्ठा zpool *pool, अचिन्हित पूर्णांक pages,
			अचिन्हित पूर्णांक *reclaimed);

व्योम *zpool_map_handle(काष्ठा zpool *pool, अचिन्हित दीर्घ handle,
			क्रमागत zpool_mapmode mm);

व्योम zpool_unmap_handle(काष्ठा zpool *pool, अचिन्हित दीर्घ handle);

u64 zpool_get_total_size(काष्ठा zpool *pool);


/**
 * काष्ठा zpool_driver - driver implementation क्रम zpool
 * @type:	name of the driver.
 * @list:	entry in the list of zpool drivers.
 * @create:	create a new pool.
 * @destroy:	destroy a pool.
 * @दो_स्मृति:	allocate mem from a pool.
 * @मुक्त:	मुक्त mem from a pool.
 * @shrink:	shrink the pool.
 * @sleep_mapped: whether zpool driver can sleep during map.
 * @map:	map a handle.
 * @unmap:	unmap a handle.
 * @total_size:	get total size of a pool.
 *
 * This is created by a zpool implementation and रेजिस्टरed
 * with zpool.
 */
काष्ठा zpool_driver अणु
	अक्षर *type;
	काष्ठा module *owner;
	atomic_t refcount;
	काष्ठा list_head list;

	व्योम *(*create)(स्थिर अक्षर *name,
			gfp_t gfp,
			स्थिर काष्ठा zpool_ops *ops,
			काष्ठा zpool *zpool);
	व्योम (*destroy)(व्योम *pool);

	bool दो_स्मृति_support_movable;
	पूर्णांक (*दो_स्मृति)(व्योम *pool, माप_प्रकार size, gfp_t gfp,
				अचिन्हित दीर्घ *handle);
	व्योम (*मुक्त)(व्योम *pool, अचिन्हित दीर्घ handle);

	पूर्णांक (*shrink)(व्योम *pool, अचिन्हित पूर्णांक pages,
				अचिन्हित पूर्णांक *reclaimed);

	bool sleep_mapped;
	व्योम *(*map)(व्योम *pool, अचिन्हित दीर्घ handle,
				क्रमागत zpool_mapmode mm);
	व्योम (*unmap)(व्योम *pool, अचिन्हित दीर्घ handle);

	u64 (*total_size)(व्योम *pool);
पूर्ण;

व्योम zpool_रेजिस्टर_driver(काष्ठा zpool_driver *driver);

पूर्णांक zpool_unरेजिस्टर_driver(काष्ठा zpool_driver *driver);

bool zpool_evictable(काष्ठा zpool *pool);
bool zpool_can_sleep_mapped(काष्ठा zpool *pool);

#पूर्ण_अगर
