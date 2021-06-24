<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR MIT */
/**************************************************************************
 *
 * Copyright (c) 2009-2013 VMware, Inc., Palo Alto, CA., USA
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS, AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 **************************************************************************/
/*
 * Authors: Thomas Hellstrom <thellstrom-at-vmware-करोt-com>
 *
 * While no substantial code is shared, the prime code is inspired by
 * drm_prime.c, with
 * Authors:
 *      Dave Airlie <airlied@redhat.com>
 *      Rob Clark <rob.clark@linaro.org>
 */
/** @file tपंचांग_ref_object.c
 *
 * Base- and reference object implementation क्रम the various
 * tपंचांग objects. Implements reference counting, minimal security checks
 * and release on file बंद.
 */


#घोषणा pr_fmt(fmt) "[TTM] " fmt

#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/atomic.h>
#समावेश "ttm_object.h"

/**
 * काष्ठा tपंचांग_object_file
 *
 * @tdev: Poपूर्णांकer to the tपंचांग_object_device.
 *
 * @lock: Lock that protects the ref_list list and the
 * ref_hash hash tables.
 *
 * @ref_list: List of tपंचांग_ref_objects to be destroyed at
 * file release.
 *
 * @ref_hash: Hash tables of ref objects, one per tपंचांग_ref_type,
 * क्रम fast lookup of ref objects given a base object.
 *
 * @refcount: reference/usage count
 */
काष्ठा tपंचांग_object_file अणु
	काष्ठा tपंचांग_object_device *tdev;
	spinlock_t lock;
	काष्ठा list_head ref_list;
	काष्ठा drm_खोलो_hash ref_hash[TTM_REF_NUM];
	काष्ठा kref refcount;
पूर्ण;

/*
 * काष्ठा tपंचांग_object_device
 *
 * @object_lock: lock that protects the object_hash hash table.
 *
 * @object_hash: hash table क्रम fast lookup of object global names.
 *
 * @object_count: Per device object count.
 *
 * This is the per-device data काष्ठाure needed क्रम tपंचांग object management.
 */

काष्ठा tपंचांग_object_device अणु
	spinlock_t object_lock;
	काष्ठा drm_खोलो_hash object_hash;
	atomic_t object_count;
	काष्ठा tपंचांग_mem_global *mem_glob;
	काष्ठा dma_buf_ops ops;
	व्योम (*dmabuf_release)(काष्ठा dma_buf *dma_buf);
	माप_प्रकार dma_buf_size;
	काष्ठा idr idr;
पूर्ण;

/*
 * काष्ठा tपंचांग_ref_object
 *
 * @hash: Hash entry क्रम the per-file object reference hash.
 *
 * @head: List entry क्रम the per-file list of ref-objects.
 *
 * @kref: Ref count.
 *
 * @obj: Base object this ref object is referencing.
 *
 * @ref_type: Type of ref object.
 *
 * This is similar to an idr object, but it also has a hash table entry
 * that allows lookup with a poपूर्णांकer to the referenced object as a key. In
 * that way, one can easily detect whether a base object is referenced by
 * a particular tपंचांग_object_file. It also carries a ref count to aव्योम creating
 * multiple ref objects अगर a tपंचांग_object_file references the same base
 * object more than once.
 */

काष्ठा tपंचांग_ref_object अणु
	काष्ठा rcu_head rcu_head;
	काष्ठा drm_hash_item hash;
	काष्ठा list_head head;
	काष्ठा kref kref;
	क्रमागत tपंचांग_ref_type ref_type;
	काष्ठा tपंचांग_base_object *obj;
	काष्ठा tपंचांग_object_file *tfile;
पूर्ण;

अटल व्योम tपंचांग_prime_dmabuf_release(काष्ठा dma_buf *dma_buf);

अटल अंतरभूत काष्ठा tपंचांग_object_file *
tपंचांग_object_file_ref(काष्ठा tपंचांग_object_file *tfile)
अणु
	kref_get(&tfile->refcount);
	वापस tfile;
पूर्ण

अटल व्योम tपंचांग_object_file_destroy(काष्ठा kref *kref)
अणु
	काष्ठा tपंचांग_object_file *tfile =
		container_of(kref, काष्ठा tपंचांग_object_file, refcount);

	kमुक्त(tfile);
पूर्ण


अटल अंतरभूत व्योम tपंचांग_object_file_unref(काष्ठा tपंचांग_object_file **p_tfile)
अणु
	काष्ठा tपंचांग_object_file *tfile = *p_tfile;

	*p_tfile = शून्य;
	kref_put(&tfile->refcount, tपंचांग_object_file_destroy);
पूर्ण


पूर्णांक tपंचांग_base_object_init(काष्ठा tपंचांग_object_file *tfile,
			 काष्ठा tपंचांग_base_object *base,
			 bool shareable,
			 क्रमागत tपंचांग_object_type object_type,
			 व्योम (*refcount_release) (काष्ठा tपंचांग_base_object **),
			 व्योम (*ref_obj_release) (काष्ठा tपंचांग_base_object *,
						  क्रमागत tपंचांग_ref_type ref_type))
अणु
	काष्ठा tपंचांग_object_device *tdev = tfile->tdev;
	पूर्णांक ret;

	base->shareable = shareable;
	base->tfile = tपंचांग_object_file_ref(tfile);
	base->refcount_release = refcount_release;
	base->ref_obj_release = ref_obj_release;
	base->object_type = object_type;
	kref_init(&base->refcount);
	idr_preload(GFP_KERNEL);
	spin_lock(&tdev->object_lock);
	ret = idr_alloc(&tdev->idr, base, 1, 0, GFP_NOWAIT);
	spin_unlock(&tdev->object_lock);
	idr_preload_end();
	अगर (ret < 0)
		वापस ret;

	base->handle = ret;
	ret = tपंचांग_ref_object_add(tfile, base, TTM_REF_USAGE, शून्य, false);
	अगर (unlikely(ret != 0))
		जाओ out_err1;

	tपंचांग_base_object_unref(&base);

	वापस 0;
out_err1:
	spin_lock(&tdev->object_lock);
	idr_हटाओ(&tdev->idr, base->handle);
	spin_unlock(&tdev->object_lock);
	वापस ret;
पूर्ण

अटल व्योम tपंचांग_release_base(काष्ठा kref *kref)
अणु
	काष्ठा tपंचांग_base_object *base =
	    container_of(kref, काष्ठा tपंचांग_base_object, refcount);
	काष्ठा tपंचांग_object_device *tdev = base->tfile->tdev;

	spin_lock(&tdev->object_lock);
	idr_हटाओ(&tdev->idr, base->handle);
	spin_unlock(&tdev->object_lock);

	/*
	 * Note: We करोn't use synchronize_rcu() here because it's far
	 * too slow. It's up to the user to मुक्त the object using
	 * call_rcu() or tपंचांग_base_object_kमुक्त().
	 */

	tपंचांग_object_file_unref(&base->tfile);
	अगर (base->refcount_release)
		base->refcount_release(&base);
पूर्ण

व्योम tपंचांग_base_object_unref(काष्ठा tपंचांग_base_object **p_base)
अणु
	काष्ठा tपंचांग_base_object *base = *p_base;

	*p_base = शून्य;

	kref_put(&base->refcount, tपंचांग_release_base);
पूर्ण

/**
 * tपंचांग_base_object_noref_lookup - look up a base object without reference
 * @tfile: The काष्ठा tपंचांग_object_file the object is रेजिस्टरed with.
 * @key: The object handle.
 *
 * This function looks up a tपंचांग base object and वापसs a poपूर्णांकer to it
 * without refcounting the poपूर्णांकer. The वापसed poपूर्णांकer is only valid
 * until tपंचांग_base_object_noref_release() is called, and the object
 * poपूर्णांकed to by the वापसed poपूर्णांकer may be करोomed. Any persistent usage
 * of the object requires a refcount to be taken using kref_get_unless_zero().
 * Iff this function वापसs successfully it needs to be paired with
 * tपंचांग_base_object_noref_release() and no sleeping- or scheduling functions
 * may be called inbetween these function callse.
 *
 * Return: A poपूर्णांकer to the object अगर successful or शून्य otherwise.
 */
काष्ठा tपंचांग_base_object *
tपंचांग_base_object_noref_lookup(काष्ठा tपंचांग_object_file *tfile, uपूर्णांक32_t key)
अणु
	काष्ठा drm_hash_item *hash;
	काष्ठा drm_खोलो_hash *ht = &tfile->ref_hash[TTM_REF_USAGE];
	पूर्णांक ret;

	rcu_पढ़ो_lock();
	ret = drm_ht_find_item_rcu(ht, key, &hash);
	अगर (ret) अणु
		rcu_पढ़ो_unlock();
		वापस शून्य;
	पूर्ण

	__release(RCU);
	वापस drm_hash_entry(hash, काष्ठा tपंचांग_ref_object, hash)->obj;
पूर्ण
EXPORT_SYMBOL(tपंचांग_base_object_noref_lookup);

काष्ठा tपंचांग_base_object *tपंचांग_base_object_lookup(काष्ठा tपंचांग_object_file *tfile,
					       uपूर्णांक32_t key)
अणु
	काष्ठा tपंचांग_base_object *base = शून्य;
	काष्ठा drm_hash_item *hash;
	काष्ठा drm_खोलो_hash *ht = &tfile->ref_hash[TTM_REF_USAGE];
	पूर्णांक ret;

	rcu_पढ़ो_lock();
	ret = drm_ht_find_item_rcu(ht, key, &hash);

	अगर (likely(ret == 0)) अणु
		base = drm_hash_entry(hash, काष्ठा tपंचांग_ref_object, hash)->obj;
		अगर (!kref_get_unless_zero(&base->refcount))
			base = शून्य;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस base;
पूर्ण

काष्ठा tपंचांग_base_object *
tपंचांग_base_object_lookup_क्रम_ref(काष्ठा tपंचांग_object_device *tdev, uपूर्णांक32_t key)
अणु
	काष्ठा tपंचांग_base_object *base;

	rcu_पढ़ो_lock();
	base = idr_find(&tdev->idr, key);

	अगर (base && !kref_get_unless_zero(&base->refcount))
		base = शून्य;
	rcu_पढ़ो_unlock();

	वापस base;
पूर्ण

/**
 * tपंचांग_ref_object_exists - Check whether a caller has a valid ref object
 * (has खोलोed) a base object.
 *
 * @tfile: Poपूर्णांकer to a काष्ठा tपंचांग_object_file identअगरying the caller.
 * @base: Poपूर्णांकer to a काष्ठा base object.
 *
 * Checks wether the caller identअगरied by @tfile has put a valid USAGE
 * reference object on the base object identअगरied by @base.
 */
bool tपंचांग_ref_object_exists(काष्ठा tपंचांग_object_file *tfile,
			   काष्ठा tपंचांग_base_object *base)
अणु
	काष्ठा drm_खोलो_hash *ht = &tfile->ref_hash[TTM_REF_USAGE];
	काष्ठा drm_hash_item *hash;
	काष्ठा tपंचांग_ref_object *ref;

	rcu_पढ़ो_lock();
	अगर (unlikely(drm_ht_find_item_rcu(ht, base->handle, &hash) != 0))
		जाओ out_false;

	/*
	 * Verअगरy that the ref object is really poपूर्णांकing to our base object.
	 * Our base object could actually be dead, and the ref object poपूर्णांकing
	 * to another base object with the same handle.
	 */
	ref = drm_hash_entry(hash, काष्ठा tपंचांग_ref_object, hash);
	अगर (unlikely(base != ref->obj))
		जाओ out_false;

	/*
	 * Verअगरy that the ref->obj poपूर्णांकer was actually valid!
	 */
	rmb();
	अगर (unlikely(kref_पढ़ो(&ref->kref) == 0))
		जाओ out_false;

	rcu_पढ़ो_unlock();
	वापस true;

 out_false:
	rcu_पढ़ो_unlock();
	वापस false;
पूर्ण

पूर्णांक tपंचांग_ref_object_add(काष्ठा tपंचांग_object_file *tfile,
		       काष्ठा tपंचांग_base_object *base,
		       क्रमागत tपंचांग_ref_type ref_type, bool *existed,
		       bool require_existed)
अणु
	काष्ठा drm_खोलो_hash *ht = &tfile->ref_hash[ref_type];
	काष्ठा tपंचांग_ref_object *ref;
	काष्ठा drm_hash_item *hash;
	काष्ठा tपंचांग_mem_global *mem_glob = tfile->tdev->mem_glob;
	काष्ठा tपंचांग_operation_ctx ctx = अणु
		.पूर्णांकerruptible = false,
		.no_रुको_gpu = false
	पूर्ण;
	पूर्णांक ret = -EINVAL;

	अगर (base->tfile != tfile && !base->shareable)
		वापस -EPERM;

	अगर (existed != शून्य)
		*existed = true;

	जबतक (ret == -EINVAL) अणु
		rcu_पढ़ो_lock();
		ret = drm_ht_find_item_rcu(ht, base->handle, &hash);

		अगर (ret == 0) अणु
			ref = drm_hash_entry(hash, काष्ठा tपंचांग_ref_object, hash);
			अगर (kref_get_unless_zero(&ref->kref)) अणु
				rcu_पढ़ो_unlock();
				अवरोध;
			पूर्ण
		पूर्ण

		rcu_पढ़ो_unlock();
		अगर (require_existed)
			वापस -EPERM;

		ret = tपंचांग_mem_global_alloc(mem_glob, माप(*ref),
					   &ctx);
		अगर (unlikely(ret != 0))
			वापस ret;
		ref = kदो_स्मृति(माप(*ref), GFP_KERNEL);
		अगर (unlikely(ref == शून्य)) अणु
			tपंचांग_mem_global_मुक्त(mem_glob, माप(*ref));
			वापस -ENOMEM;
		पूर्ण

		ref->hash.key = base->handle;
		ref->obj = base;
		ref->tfile = tfile;
		ref->ref_type = ref_type;
		kref_init(&ref->kref);

		spin_lock(&tfile->lock);
		ret = drm_ht_insert_item_rcu(ht, &ref->hash);

		अगर (likely(ret == 0)) अणु
			list_add_tail(&ref->head, &tfile->ref_list);
			kref_get(&base->refcount);
			spin_unlock(&tfile->lock);
			अगर (existed != शून्य)
				*existed = false;
			अवरोध;
		पूर्ण

		spin_unlock(&tfile->lock);
		BUG_ON(ret != -EINVAL);

		tपंचांग_mem_global_मुक्त(mem_glob, माप(*ref));
		kमुक्त(ref);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम __releases(tfile->lock) __acquires(tfile->lock)
tपंचांग_ref_object_release(काष्ठा kref *kref)
अणु
	काष्ठा tपंचांग_ref_object *ref =
	    container_of(kref, काष्ठा tपंचांग_ref_object, kref);
	काष्ठा tपंचांग_base_object *base = ref->obj;
	काष्ठा tपंचांग_object_file *tfile = ref->tfile;
	काष्ठा drm_खोलो_hash *ht;
	काष्ठा tपंचांग_mem_global *mem_glob = tfile->tdev->mem_glob;

	ht = &tfile->ref_hash[ref->ref_type];
	(व्योम)drm_ht_हटाओ_item_rcu(ht, &ref->hash);
	list_del(&ref->head);
	spin_unlock(&tfile->lock);

	अगर (ref->ref_type != TTM_REF_USAGE && base->ref_obj_release)
		base->ref_obj_release(base, ref->ref_type);

	tपंचांग_base_object_unref(&ref->obj);
	tपंचांग_mem_global_मुक्त(mem_glob, माप(*ref));
	kमुक्त_rcu(ref, rcu_head);
	spin_lock(&tfile->lock);
पूर्ण

पूर्णांक tपंचांग_ref_object_base_unref(काष्ठा tपंचांग_object_file *tfile,
			      अचिन्हित दीर्घ key, क्रमागत tपंचांग_ref_type ref_type)
अणु
	काष्ठा drm_खोलो_hash *ht = &tfile->ref_hash[ref_type];
	काष्ठा tपंचांग_ref_object *ref;
	काष्ठा drm_hash_item *hash;
	पूर्णांक ret;

	spin_lock(&tfile->lock);
	ret = drm_ht_find_item(ht, key, &hash);
	अगर (unlikely(ret != 0)) अणु
		spin_unlock(&tfile->lock);
		वापस -EINVAL;
	पूर्ण
	ref = drm_hash_entry(hash, काष्ठा tपंचांग_ref_object, hash);
	kref_put(&ref->kref, tपंचांग_ref_object_release);
	spin_unlock(&tfile->lock);
	वापस 0;
पूर्ण

व्योम tपंचांग_object_file_release(काष्ठा tपंचांग_object_file **p_tfile)
अणु
	काष्ठा tपंचांग_ref_object *ref;
	काष्ठा list_head *list;
	अचिन्हित पूर्णांक i;
	काष्ठा tपंचांग_object_file *tfile = *p_tfile;

	*p_tfile = शून्य;
	spin_lock(&tfile->lock);

	/*
	 * Since we release the lock within the loop, we have to
	 * restart it from the beginning each समय.
	 */

	जबतक (!list_empty(&tfile->ref_list)) अणु
		list = tfile->ref_list.next;
		ref = list_entry(list, काष्ठा tपंचांग_ref_object, head);
		tपंचांग_ref_object_release(&ref->kref);
	पूर्ण

	spin_unlock(&tfile->lock);
	क्रम (i = 0; i < TTM_REF_NUM; ++i)
		drm_ht_हटाओ(&tfile->ref_hash[i]);

	tपंचांग_object_file_unref(&tfile);
पूर्ण

काष्ठा tपंचांग_object_file *tपंचांग_object_file_init(काष्ठा tपंचांग_object_device *tdev,
					     अचिन्हित पूर्णांक hash_order)
अणु
	काष्ठा tपंचांग_object_file *tfile = kदो_स्मृति(माप(*tfile), GFP_KERNEL);
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक j = 0;
	पूर्णांक ret;

	अगर (unlikely(tfile == शून्य))
		वापस शून्य;

	spin_lock_init(&tfile->lock);
	tfile->tdev = tdev;
	kref_init(&tfile->refcount);
	INIT_LIST_HEAD(&tfile->ref_list);

	क्रम (i = 0; i < TTM_REF_NUM; ++i) अणु
		ret = drm_ht_create(&tfile->ref_hash[i], hash_order);
		अगर (ret) अणु
			j = i;
			जाओ out_err;
		पूर्ण
	पूर्ण

	वापस tfile;
out_err:
	क्रम (i = 0; i < j; ++i)
		drm_ht_हटाओ(&tfile->ref_hash[i]);

	kमुक्त(tfile);

	वापस शून्य;
पूर्ण

काष्ठा tपंचांग_object_device *
tपंचांग_object_device_init(काष्ठा tपंचांग_mem_global *mem_glob,
		       अचिन्हित पूर्णांक hash_order,
		       स्थिर काष्ठा dma_buf_ops *ops)
अणु
	काष्ठा tपंचांग_object_device *tdev = kदो_स्मृति(माप(*tdev), GFP_KERNEL);
	पूर्णांक ret;

	अगर (unlikely(tdev == शून्य))
		वापस शून्य;

	tdev->mem_glob = mem_glob;
	spin_lock_init(&tdev->object_lock);
	atomic_set(&tdev->object_count, 0);
	ret = drm_ht_create(&tdev->object_hash, hash_order);
	अगर (ret != 0)
		जाओ out_no_object_hash;

	idr_init(&tdev->idr);
	tdev->ops = *ops;
	tdev->dmabuf_release = tdev->ops.release;
	tdev->ops.release = tपंचांग_prime_dmabuf_release;
	tdev->dma_buf_size = tपंचांग_round_pot(माप(काष्ठा dma_buf)) +
		tपंचांग_round_pot(माप(काष्ठा file));
	वापस tdev;

out_no_object_hash:
	kमुक्त(tdev);
	वापस शून्य;
पूर्ण

व्योम tपंचांग_object_device_release(काष्ठा tपंचांग_object_device **p_tdev)
अणु
	काष्ठा tपंचांग_object_device *tdev = *p_tdev;

	*p_tdev = शून्य;

	WARN_ON_ONCE(!idr_is_empty(&tdev->idr));
	idr_destroy(&tdev->idr);
	drm_ht_हटाओ(&tdev->object_hash);

	kमुक्त(tdev);
पूर्ण

/**
 * get_dma_buf_unless_करोomed - get a dma_buf reference अगर possible.
 *
 * @dmabuf: Non-refcounted poपूर्णांकer to a काष्ठा dma-buf.
 *
 * Obtain a file reference from a lookup काष्ठाure that करोesn't refcount
 * the file, but synchronizes with its release method to make sure it has
 * not been मुक्तd yet. See क्रम example kref_get_unless_zero करोcumentation.
 * Returns true अगर refcounting succeeds, false otherwise.
 *
 * Nobody really wants this as a खुला API yet, so let it mature here
 * क्रम some समय...
 */
अटल bool __must_check get_dma_buf_unless_करोomed(काष्ठा dma_buf *dmabuf)
अणु
	वापस atomic_दीर्घ_inc_not_zero(&dmabuf->file->f_count) != 0L;
पूर्ण

/**
 * tपंचांग_prime_refcount_release - refcount release method क्रम a prime object.
 *
 * @p_base: Poपूर्णांकer to tपंचांग_base_object poपूर्णांकer.
 *
 * This is a wrapper that calls the refcount_release founction of the
 * underlying object. At the same समय it cleans up the prime object.
 * This function is called when all references to the base object we
 * derive from are gone.
 */
अटल व्योम tपंचांग_prime_refcount_release(काष्ठा tपंचांग_base_object **p_base)
अणु
	काष्ठा tपंचांग_base_object *base = *p_base;
	काष्ठा tपंचांग_prime_object *prime;

	*p_base = शून्य;
	prime = container_of(base, काष्ठा tपंचांग_prime_object, base);
	BUG_ON(prime->dma_buf != शून्य);
	mutex_destroy(&prime->mutex);
	अगर (prime->refcount_release)
		prime->refcount_release(&base);
पूर्ण

/**
 * tपंचांग_prime_dmabuf_release - Release method क्रम the dma-bufs we export
 *
 * @dma_buf:
 *
 * This function first calls the dma_buf release method the driver
 * provides. Then it cleans up our dma_buf poपूर्णांकer used क्रम lookup,
 * and finally releases the reference the dma_buf has on our base
 * object.
 */
अटल व्योम tपंचांग_prime_dmabuf_release(काष्ठा dma_buf *dma_buf)
अणु
	काष्ठा tपंचांग_prime_object *prime =
		(काष्ठा tपंचांग_prime_object *) dma_buf->priv;
	काष्ठा tपंचांग_base_object *base = &prime->base;
	काष्ठा tपंचांग_object_device *tdev = base->tfile->tdev;

	अगर (tdev->dmabuf_release)
		tdev->dmabuf_release(dma_buf);
	mutex_lock(&prime->mutex);
	अगर (prime->dma_buf == dma_buf)
		prime->dma_buf = शून्य;
	mutex_unlock(&prime->mutex);
	tपंचांग_mem_global_मुक्त(tdev->mem_glob, tdev->dma_buf_size);
	tपंचांग_base_object_unref(&base);
पूर्ण

/**
 * tपंचांग_prime_fd_to_handle - Get a base object handle from a prime fd
 *
 * @tfile: A काष्ठा tपंचांग_object_file identअगरying the caller.
 * @fd: The prime / dmabuf fd.
 * @handle: The वापसed handle.
 *
 * This function वापसs a handle to an object that previously exported
 * a dma-buf. Note that we करोn't handle imports yet, because we simply
 * have no consumers of that implementation.
 */
पूर्णांक tपंचांग_prime_fd_to_handle(काष्ठा tपंचांग_object_file *tfile,
			   पूर्णांक fd, u32 *handle)
अणु
	काष्ठा tपंचांग_object_device *tdev = tfile->tdev;
	काष्ठा dma_buf *dma_buf;
	काष्ठा tपंचांग_prime_object *prime;
	काष्ठा tपंचांग_base_object *base;
	पूर्णांक ret;

	dma_buf = dma_buf_get(fd);
	अगर (IS_ERR(dma_buf))
		वापस PTR_ERR(dma_buf);

	अगर (dma_buf->ops != &tdev->ops)
		वापस -ENOSYS;

	prime = (काष्ठा tपंचांग_prime_object *) dma_buf->priv;
	base = &prime->base;
	*handle = base->handle;
	ret = tपंचांग_ref_object_add(tfile, base, TTM_REF_USAGE, शून्य, false);

	dma_buf_put(dma_buf);

	वापस ret;
पूर्ण

/**
 * tपंचांग_prime_handle_to_fd - Return a dma_buf fd from a tपंचांग prime object
 *
 * @tfile: Struct tपंचांग_object_file identअगरying the caller.
 * @handle: Handle to the object we're exporting from.
 * @flags: flags क्रम dma-buf creation. We just pass them on.
 * @prime_fd: The वापसed file descriptor.
 *
 */
पूर्णांक tपंचांग_prime_handle_to_fd(काष्ठा tपंचांग_object_file *tfile,
			   uपूर्णांक32_t handle, uपूर्णांक32_t flags,
			   पूर्णांक *prime_fd)
अणु
	काष्ठा tपंचांग_object_device *tdev = tfile->tdev;
	काष्ठा tपंचांग_base_object *base;
	काष्ठा dma_buf *dma_buf;
	काष्ठा tपंचांग_prime_object *prime;
	पूर्णांक ret;

	base = tपंचांग_base_object_lookup(tfile, handle);
	अगर (unlikely(base == शून्य ||
		     base->object_type != tपंचांग_prime_type)) अणु
		ret = -ENOENT;
		जाओ out_unref;
	पूर्ण

	prime = container_of(base, काष्ठा tपंचांग_prime_object, base);
	अगर (unlikely(!base->shareable)) अणु
		ret = -EPERM;
		जाओ out_unref;
	पूर्ण

	ret = mutex_lock_पूर्णांकerruptible(&prime->mutex);
	अगर (unlikely(ret != 0)) अणु
		ret = -ERESTARTSYS;
		जाओ out_unref;
	पूर्ण

	dma_buf = prime->dma_buf;
	अगर (!dma_buf || !get_dma_buf_unless_करोomed(dma_buf)) अणु
		DEFINE_DMA_BUF_EXPORT_INFO(exp_info);
		काष्ठा tपंचांग_operation_ctx ctx = अणु
			.पूर्णांकerruptible = true,
			.no_रुको_gpu = false
		पूर्ण;
		exp_info.ops = &tdev->ops;
		exp_info.size = prime->size;
		exp_info.flags = flags;
		exp_info.priv = prime;

		/*
		 * Need to create a new dma_buf, with memory accounting.
		 */
		ret = tपंचांग_mem_global_alloc(tdev->mem_glob, tdev->dma_buf_size,
					   &ctx);
		अगर (unlikely(ret != 0)) अणु
			mutex_unlock(&prime->mutex);
			जाओ out_unref;
		पूर्ण

		dma_buf = dma_buf_export(&exp_info);
		अगर (IS_ERR(dma_buf)) अणु
			ret = PTR_ERR(dma_buf);
			tपंचांग_mem_global_मुक्त(tdev->mem_glob,
					    tdev->dma_buf_size);
			mutex_unlock(&prime->mutex);
			जाओ out_unref;
		पूर्ण

		/*
		 * dma_buf has taken the base object reference
		 */
		base = शून्य;
		prime->dma_buf = dma_buf;
	पूर्ण
	mutex_unlock(&prime->mutex);

	ret = dma_buf_fd(dma_buf, flags);
	अगर (ret >= 0) अणु
		*prime_fd = ret;
		ret = 0;
	पूर्ण अन्यथा
		dma_buf_put(dma_buf);

out_unref:
	अगर (base)
		tपंचांग_base_object_unref(&base);
	वापस ret;
पूर्ण

/**
 * tपंचांग_prime_object_init - Initialize a tपंचांग_prime_object
 *
 * @tfile: काष्ठा tपंचांग_object_file identअगरying the caller
 * @size: The size of the dma_bufs we export.
 * @prime: The object to be initialized.
 * @shareable: See tपंचांग_base_object_init
 * @type: See tपंचांग_base_object_init
 * @refcount_release: See tपंचांग_base_object_init
 * @ref_obj_release: See tपंचांग_base_object_init
 *
 * Initializes an object which is compatible with the drm_prime model
 * क्रम data sharing between processes and devices.
 */
पूर्णांक tपंचांग_prime_object_init(काष्ठा tपंचांग_object_file *tfile, माप_प्रकार size,
			  काष्ठा tपंचांग_prime_object *prime, bool shareable,
			  क्रमागत tपंचांग_object_type type,
			  व्योम (*refcount_release) (काष्ठा tपंचांग_base_object **),
			  व्योम (*ref_obj_release) (काष्ठा tपंचांग_base_object *,
						   क्रमागत tपंचांग_ref_type ref_type))
अणु
	mutex_init(&prime->mutex);
	prime->size = PAGE_ALIGN(size);
	prime->real_type = type;
	prime->dma_buf = शून्य;
	prime->refcount_release = refcount_release;
	वापस tपंचांग_base_object_init(tfile, &prime->base, shareable,
				    tपंचांग_prime_type,
				    tपंचांग_prime_refcount_release,
				    ref_obj_release);
पूर्ण
