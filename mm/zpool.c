<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * zpool memory storage api
 *
 * Copyright (C) 2014 Dan Streeपंचांगan
 *
 * This is a common frontend क्रम memory storage pool implementations.
 * Typically, this is used to store compressed memory.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/list.h>
#समावेश <linux/types.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/module.h>
#समावेश <linux/zpool.h>

काष्ठा zpool अणु
	काष्ठा zpool_driver *driver;
	व्योम *pool;
	स्थिर काष्ठा zpool_ops *ops;
	bool evictable;
	bool can_sleep_mapped;

	काष्ठा list_head list;
पूर्ण;

अटल LIST_HEAD(drivers_head);
अटल DEFINE_SPINLOCK(drivers_lock);

अटल LIST_HEAD(pools_head);
अटल DEFINE_SPINLOCK(pools_lock);

/**
 * zpool_रेजिस्टर_driver() - रेजिस्टर a zpool implementation.
 * @driver:	driver to रेजिस्टर
 */
व्योम zpool_रेजिस्टर_driver(काष्ठा zpool_driver *driver)
अणु
	spin_lock(&drivers_lock);
	atomic_set(&driver->refcount, 0);
	list_add(&driver->list, &drivers_head);
	spin_unlock(&drivers_lock);
पूर्ण
EXPORT_SYMBOL(zpool_रेजिस्टर_driver);

/**
 * zpool_unरेजिस्टर_driver() - unरेजिस्टर a zpool implementation.
 * @driver:	driver to unरेजिस्टर.
 *
 * Module usage counting is used to prevent using a driver
 * जबतक/after unloading, so अगर this is called from module
 * निकास function, this should never fail; अगर called from
 * other than the module निकास function, and this वापसs
 * failure, the driver is in use and must reमुख्य available.
 */
पूर्णांक zpool_unरेजिस्टर_driver(काष्ठा zpool_driver *driver)
अणु
	पूर्णांक ret = 0, refcount;

	spin_lock(&drivers_lock);
	refcount = atomic_पढ़ो(&driver->refcount);
	WARN_ON(refcount < 0);
	अगर (refcount > 0)
		ret = -EBUSY;
	अन्यथा
		list_del(&driver->list);
	spin_unlock(&drivers_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(zpool_unरेजिस्टर_driver);

/* this assumes @type is null-terminated. */
अटल काष्ठा zpool_driver *zpool_get_driver(स्थिर अक्षर *type)
अणु
	काष्ठा zpool_driver *driver;

	spin_lock(&drivers_lock);
	list_क्रम_each_entry(driver, &drivers_head, list) अणु
		अगर (!म_भेद(driver->type, type)) अणु
			bool got = try_module_get(driver->owner);

			अगर (got)
				atomic_inc(&driver->refcount);
			spin_unlock(&drivers_lock);
			वापस got ? driver : शून्य;
		पूर्ण
	पूर्ण

	spin_unlock(&drivers_lock);
	वापस शून्य;
पूर्ण

अटल व्योम zpool_put_driver(काष्ठा zpool_driver *driver)
अणु
	atomic_dec(&driver->refcount);
	module_put(driver->owner);
पूर्ण

/**
 * zpool_has_pool() - Check अगर the pool driver is available
 * @type:	The type of the zpool to check (e.g. zbud, zsदो_स्मृति)
 *
 * This checks अगर the @type pool driver is available.  This will try to load
 * the requested module, अगर needed, but there is no guarantee the module will
 * still be loaded and available immediately after calling.  If this वापसs
 * true, the caller should assume the pool is available, but must be prepared
 * to handle the @zpool_create_pool() वापसing failure.  However अगर this
 * वापसs false, the caller should assume the requested pool type is not
 * available; either the requested pool type module करोes not exist, or could
 * not be loaded, and calling @zpool_create_pool() with the pool type will
 * fail.
 *
 * The @type string must be null-terminated.
 *
 * Returns: true अगर @type pool is available, false अगर not
 */
bool zpool_has_pool(अक्षर *type)
अणु
	काष्ठा zpool_driver *driver = zpool_get_driver(type);

	अगर (!driver) अणु
		request_module("zpool-%s", type);
		driver = zpool_get_driver(type);
	पूर्ण

	अगर (!driver)
		वापस false;

	zpool_put_driver(driver);
	वापस true;
पूर्ण
EXPORT_SYMBOL(zpool_has_pool);

/**
 * zpool_create_pool() - Create a new zpool
 * @type:	The type of the zpool to create (e.g. zbud, zsदो_स्मृति)
 * @name:	The name of the zpool (e.g. zram0, zswap)
 * @gfp:	The GFP flags to use when allocating the pool.
 * @ops:	The optional ops callback.
 *
 * This creates a new zpool of the specअगरied type.  The gfp flags will be
 * used when allocating memory, अगर the implementation supports it.  If the
 * ops param is शून्य, then the created zpool will not be evictable.
 *
 * Implementations must guarantee this to be thपढ़ो-safe.
 *
 * The @type and @name strings must be null-terminated.
 *
 * Returns: New zpool on success, शून्य on failure.
 */
काष्ठा zpool *zpool_create_pool(स्थिर अक्षर *type, स्थिर अक्षर *name, gfp_t gfp,
		स्थिर काष्ठा zpool_ops *ops)
अणु
	काष्ठा zpool_driver *driver;
	काष्ठा zpool *zpool;

	pr_debug("creating pool type %s\n", type);

	driver = zpool_get_driver(type);

	अगर (!driver) अणु
		request_module("zpool-%s", type);
		driver = zpool_get_driver(type);
	पूर्ण

	अगर (!driver) अणु
		pr_err("no driver for type %s\n", type);
		वापस शून्य;
	पूर्ण

	zpool = kदो_स्मृति(माप(*zpool), gfp);
	अगर (!zpool) अणु
		pr_err("couldn't create zpool - out of memory\n");
		zpool_put_driver(driver);
		वापस शून्य;
	पूर्ण

	zpool->driver = driver;
	zpool->pool = driver->create(name, gfp, ops, zpool);
	zpool->ops = ops;
	zpool->evictable = driver->shrink && ops && ops->evict;
	zpool->can_sleep_mapped = driver->sleep_mapped;

	अगर (!zpool->pool) अणु
		pr_err("couldn't create %s pool\n", type);
		zpool_put_driver(driver);
		kमुक्त(zpool);
		वापस शून्य;
	पूर्ण

	pr_debug("created pool type %s\n", type);

	spin_lock(&pools_lock);
	list_add(&zpool->list, &pools_head);
	spin_unlock(&pools_lock);

	वापस zpool;
पूर्ण

/**
 * zpool_destroy_pool() - Destroy a zpool
 * @zpool:	The zpool to destroy.
 *
 * Implementations must guarantee this to be thपढ़ो-safe,
 * however only when destroying dअगरferent pools.  The same
 * pool should only be destroyed once, and should not be used
 * after it is destroyed.
 *
 * This destroys an existing zpool.  The zpool should not be in use.
 */
व्योम zpool_destroy_pool(काष्ठा zpool *zpool)
अणु
	pr_debug("destroying pool type %s\n", zpool->driver->type);

	spin_lock(&pools_lock);
	list_del(&zpool->list);
	spin_unlock(&pools_lock);
	zpool->driver->destroy(zpool->pool);
	zpool_put_driver(zpool->driver);
	kमुक्त(zpool);
पूर्ण

/**
 * zpool_get_type() - Get the type of the zpool
 * @zpool:	The zpool to check
 *
 * This वापसs the type of the pool.
 *
 * Implementations must guarantee this to be thपढ़ो-safe.
 *
 * Returns: The type of zpool.
 */
स्थिर अक्षर *zpool_get_type(काष्ठा zpool *zpool)
अणु
	वापस zpool->driver->type;
पूर्ण

/**
 * zpool_दो_स्मृति_support_movable() - Check अगर the zpool supports
 *	allocating movable memory
 * @zpool:	The zpool to check
 *
 * This वापसs अगर the zpool supports allocating movable memory.
 *
 * Implementations must guarantee this to be thपढ़ो-safe.
 *
 * Returns: true अगर the zpool supports allocating movable memory, false अगर not
 */
bool zpool_दो_स्मृति_support_movable(काष्ठा zpool *zpool)
अणु
	वापस zpool->driver->दो_स्मृति_support_movable;
पूर्ण

/**
 * zpool_दो_स्मृति() - Allocate memory
 * @zpool:	The zpool to allocate from.
 * @size:	The amount of memory to allocate.
 * @gfp:	The GFP flags to use when allocating memory.
 * @handle:	Poपूर्णांकer to the handle to set
 *
 * This allocates the requested amount of memory from the pool.
 * The gfp flags will be used when allocating memory, अगर the
 * implementation supports it.  The provided @handle will be
 * set to the allocated object handle.
 *
 * Implementations must guarantee this to be thपढ़ो-safe.
 *
 * Returns: 0 on success, negative value on error.
 */
पूर्णांक zpool_दो_स्मृति(काष्ठा zpool *zpool, माप_प्रकार size, gfp_t gfp,
			अचिन्हित दीर्घ *handle)
अणु
	वापस zpool->driver->दो_स्मृति(zpool->pool, size, gfp, handle);
पूर्ण

/**
 * zpool_मुक्त() - Free previously allocated memory
 * @zpool:	The zpool that allocated the memory.
 * @handle:	The handle to the memory to मुक्त.
 *
 * This मुक्तs previously allocated memory.  This करोes not guarantee
 * that the pool will actually मुक्त memory, only that the memory
 * in the pool will become available क्रम use by the pool.
 *
 * Implementations must guarantee this to be thपढ़ो-safe,
 * however only when मुक्तing dअगरferent handles.  The same
 * handle should only be मुक्तd once, and should not be used
 * after मुक्तing.
 */
व्योम zpool_मुक्त(काष्ठा zpool *zpool, अचिन्हित दीर्घ handle)
अणु
	zpool->driver->मुक्त(zpool->pool, handle);
पूर्ण

/**
 * zpool_shrink() - Shrink the pool size
 * @zpool:	The zpool to shrink.
 * @pages:	The number of pages to shrink the pool.
 * @reclaimed:	The number of pages successfully evicted.
 *
 * This attempts to shrink the actual memory size of the pool
 * by evicting currently used handle(s).  If the pool was
 * created with no zpool_ops, or the evict call fails क्रम any
 * of the handles, this will fail.  If non-शून्य, the @reclaimed
 * parameter will be set to the number of pages reclaimed,
 * which may be more than the number of pages requested.
 *
 * Implementations must guarantee this to be thपढ़ो-safe.
 *
 * Returns: 0 on success, negative value on error/failure.
 */
पूर्णांक zpool_shrink(काष्ठा zpool *zpool, अचिन्हित पूर्णांक pages,
			अचिन्हित पूर्णांक *reclaimed)
अणु
	वापस zpool->driver->shrink ?
	       zpool->driver->shrink(zpool->pool, pages, reclaimed) : -EINVAL;
पूर्ण

/**
 * zpool_map_handle() - Map a previously allocated handle पूर्णांकo memory
 * @zpool:	The zpool that the handle was allocated from
 * @handle:	The handle to map
 * @mapmode:	How the memory should be mapped
 *
 * This maps a previously allocated handle पूर्णांकo memory.  The @mapmode
 * param indicates to the implementation how the memory will be
 * used, i.e. पढ़ो-only, ग_लिखो-only, पढ़ो-ग_लिखो.  If the
 * implementation करोes not support it, the memory will be treated
 * as पढ़ो-ग_लिखो.
 *
 * This may hold locks, disable पूर्णांकerrupts, and/or preemption,
 * and the zpool_unmap_handle() must be called to unकरो those
 * actions.  The code that uses the mapped handle should complete
 * its operations on the mapped handle memory quickly and unmap
 * as soon as possible.  As the implementation may use per-cpu
 * data, multiple handles should not be mapped concurrently on
 * any cpu.
 *
 * Returns: A poपूर्णांकer to the handle's mapped memory area.
 */
व्योम *zpool_map_handle(काष्ठा zpool *zpool, अचिन्हित दीर्घ handle,
			क्रमागत zpool_mapmode mapmode)
अणु
	वापस zpool->driver->map(zpool->pool, handle, mapmode);
पूर्ण

/**
 * zpool_unmap_handle() - Unmap a previously mapped handle
 * @zpool:	The zpool that the handle was allocated from
 * @handle:	The handle to unmap
 *
 * This unmaps a previously mapped handle.  Any locks or other
 * actions that the implementation took in zpool_map_handle()
 * will be unकरोne here.  The memory area वापसed from
 * zpool_map_handle() should no दीर्घer be used after this.
 */
व्योम zpool_unmap_handle(काष्ठा zpool *zpool, अचिन्हित दीर्घ handle)
अणु
	zpool->driver->unmap(zpool->pool, handle);
पूर्ण

/**
 * zpool_get_total_size() - The total size of the pool
 * @zpool:	The zpool to check
 *
 * This वापसs the total size in bytes of the pool.
 *
 * Returns: Total size of the zpool in bytes.
 */
u64 zpool_get_total_size(काष्ठा zpool *zpool)
अणु
	वापस zpool->driver->total_size(zpool->pool);
पूर्ण

/**
 * zpool_evictable() - Test अगर zpool is potentially evictable
 * @zpool:	The zpool to test
 *
 * Zpool is only potentially evictable when it's created with काष्ठा
 * zpool_ops.evict and its driver implements काष्ठा zpool_driver.shrink.
 *
 * However, it करोesn't necessarily mean driver will use zpool_ops.evict
 * in its implementation of zpool_driver.shrink. It could करो पूर्णांकernal
 * defragmentation instead.
 *
 * Returns: true अगर potentially evictable; false otherwise.
 */
bool zpool_evictable(काष्ठा zpool *zpool)
अणु
	वापस zpool->evictable;
पूर्ण

/**
 * zpool_can_sleep_mapped - Test अगर zpool can sleep when करो mapped.
 * @zpool:	The zpool to test
 *
 * Returns: true अगर zpool can sleep; false otherwise.
 */
bool zpool_can_sleep_mapped(काष्ठा zpool *zpool)
अणु
	वापस zpool->can_sleep_mapped;
पूर्ण

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Dan Streetman <ddstreet@ieee.org>");
MODULE_DESCRIPTION("Common API for compressed memory storage");
