<शैली गुरु>
/**************************************************************************
 *
 * Copyright (c) 2006-2009 VMware, Inc., Palo Alto, CA., USA
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
 */
/** @file tपंचांग_object.h
 *
 * Base- and reference object implementation क्रम the various
 * tपंचांग objects. Implements reference counting, minimal security checks
 * and release on file बंद.
 */

#अगर_अघोषित _TTM_OBJECT_H_
#घोषणा _TTM_OBJECT_H_

#समावेश <linux/dma-buf.h>
#समावेश <linux/kref.h>
#समावेश <linux/list.h>
#समावेश <linux/rcupdate.h>

#समावेश <drm/drm_hashtab.h>

#समावेश "ttm_memory.h"

/**
 * क्रमागत tपंचांग_ref_type
 *
 * Describes what type of reference a ref object holds.
 *
 * TTM_REF_USAGE is a simple refcount on a base object.
 *
 * TTM_REF_SYNCCPU_READ is a SYNCCPU_READ reference on a
 * buffer object.
 *
 * TTM_REF_SYNCCPU_WRITE is a SYNCCPU_WRITE reference on a
 * buffer object.
 *
 */

क्रमागत tपंचांग_ref_type अणु
	TTM_REF_USAGE,
	TTM_REF_SYNCCPU_READ,
	TTM_REF_SYNCCPU_WRITE,
	TTM_REF_NUM
पूर्ण;

/**
 * क्रमागत tपंचांग_object_type
 *
 * One entry per tपंचांग object type.
 * Device-specअगरic types should use the
 * tपंचांग_driver_typex types.
 */

क्रमागत tपंचांग_object_type अणु
	tपंचांग_fence_type,
	tपंचांग_buffer_type,
	tपंचांग_lock_type,
	tपंचांग_prime_type,
	tपंचांग_driver_type0 = 256,
	tपंचांग_driver_type1,
	tपंचांग_driver_type2,
	tपंचांग_driver_type3,
	tपंचांग_driver_type4,
	tपंचांग_driver_type5
पूर्ण;

काष्ठा tपंचांग_object_file;
काष्ठा tपंचांग_object_device;

/**
 * काष्ठा tपंचांग_base_object
 *
 * @hash: hash entry क्रम the per-device object hash.
 * @type: derived type this object is base class क्रम.
 * @shareable: Other tपंचांग_object_files can access this object.
 *
 * @tfile: Poपूर्णांकer to tपंचांग_object_file of the creator.
 * शून्य अगर the object was not created by a user request.
 * (kernel object).
 *
 * @refcount: Number of references to this object, not
 * including the hash entry. A reference to a base object can
 * only be held by a ref object.
 *
 * @refcount_release: A function to be called when there are
 * no more references to this object. This function should
 * destroy the object (or make sure deकाष्ठाion eventually happens),
 * and when it is called, the object has
 * alपढ़ोy been taken out of the per-device hash. The parameter
 * "base" should be set to शून्य by the function.
 *
 * @ref_obj_release: A function to be called when a reference object
 * with another tपंचांग_ref_type than TTM_REF_USAGE is deleted.
 * This function may, क्रम example, release a lock held by a user-space
 * process.
 *
 * This काष्ठा is पूर्णांकended to be used as a base काष्ठा क्रम objects that
 * are visible to user-space. It provides a global name, race-safe
 * access and refcounting, minimal access contol and hooks क्रम unref actions.
 */

काष्ठा tपंचांग_base_object अणु
	काष्ठा rcu_head rhead;
	काष्ठा tपंचांग_object_file *tfile;
	काष्ठा kref refcount;
	व्योम (*refcount_release) (काष्ठा tपंचांग_base_object **base);
	व्योम (*ref_obj_release) (काष्ठा tपंचांग_base_object *base,
				 क्रमागत tपंचांग_ref_type ref_type);
	u32 handle;
	क्रमागत tपंचांग_object_type object_type;
	u32 shareable;
पूर्ण;


/**
 * काष्ठा tपंचांग_prime_object - Modअगरied base object that is prime-aware
 *
 * @base: काष्ठा tपंचांग_base_object that we derive from
 * @mutex: Mutex protecting the @dma_buf member.
 * @size: Size of the dma_buf associated with this object
 * @real_type: Type of the underlying object. Needed since we're setting
 * the value of @base::object_type to tपंचांग_prime_type
 * @dma_buf: Non ref-coutned poपूर्णांकer to a काष्ठा dma_buf created from this
 * object.
 * @refcount_release: The underlying object's release method. Needed since
 * we set @base::refcount_release to our own release method.
 */

काष्ठा tपंचांग_prime_object अणु
	काष्ठा tपंचांग_base_object base;
	काष्ठा mutex mutex;
	माप_प्रकार size;
	क्रमागत tपंचांग_object_type real_type;
	काष्ठा dma_buf *dma_buf;
	व्योम (*refcount_release) (काष्ठा tपंचांग_base_object **);
पूर्ण;

/**
 * tपंचांग_base_object_init
 *
 * @tfile: Poपूर्णांकer to a काष्ठा tपंचांग_object_file.
 * @base: The काष्ठा tपंचांग_base_object to initialize.
 * @shareable: This object is shareable with other applcations.
 * (dअगरferent @tfile poपूर्णांकers.)
 * @type: The object type.
 * @refcount_release: See the काष्ठा tपंचांग_base_object description.
 * @ref_obj_release: See the काष्ठा tपंचांग_base_object description.
 *
 * Initializes a काष्ठा tपंचांग_base_object.
 */

बाह्य पूर्णांक tपंचांग_base_object_init(काष्ठा tपंचांग_object_file *tfile,
				काष्ठा tपंचांग_base_object *base,
				bool shareable,
				क्रमागत tपंचांग_object_type type,
				व्योम (*refcount_release) (काष्ठा tपंचांग_base_object
							  **),
				व्योम (*ref_obj_release) (काष्ठा tपंचांग_base_object
							 *,
							 क्रमागत tपंचांग_ref_type
							 ref_type));

/**
 * tपंचांग_base_object_lookup
 *
 * @tfile: Poपूर्णांकer to a काष्ठा tपंचांग_object_file.
 * @key: Hash key
 *
 * Looks up a काष्ठा tपंचांग_base_object with the key @key.
 */

बाह्य काष्ठा tपंचांग_base_object *tपंचांग_base_object_lookup(काष्ठा tपंचांग_object_file
						      *tfile, uपूर्णांक32_t key);

/**
 * tपंचांग_base_object_lookup_क्रम_ref
 *
 * @tdev: Poपूर्णांकer to a काष्ठा tपंचांग_object_device.
 * @key: Hash key
 *
 * Looks up a काष्ठा tपंचांग_base_object with the key @key.
 * This function should only be used when the काष्ठा tfile associated with the
 * caller करोesn't yet have a reference to the base object.
 */

बाह्य काष्ठा tपंचांग_base_object *
tपंचांग_base_object_lookup_क्रम_ref(काष्ठा tपंचांग_object_device *tdev, uपूर्णांक32_t key);

/**
 * tपंचांग_base_object_unref
 *
 * @p_base: Poपूर्णांकer to a poपूर्णांकer referencing a काष्ठा tपंचांग_base_object.
 *
 * Decrements the base object refcount and clears the poपूर्णांकer poपूर्णांकed to by
 * p_base.
 */

बाह्य व्योम tपंचांग_base_object_unref(काष्ठा tपंचांग_base_object **p_base);

/**
 * tपंचांग_ref_object_add.
 *
 * @tfile: A काष्ठा tपंचांग_object_file representing the application owning the
 * ref_object.
 * @base: The base object to reference.
 * @ref_type: The type of reference.
 * @existed: Upon completion, indicates that an identical reference object
 * alपढ़ोy existed, and the refcount was upped on that object instead.
 * @require_existed: Fail with -EPERM अगर an identical ref object didn't
 * alपढ़ोy exist.
 *
 * Checks that the base object is shareable and adds a ref object to it.
 *
 * Adding a ref object to a base object is basically like referencing the
 * base object, but a user-space application holds the reference. When the
 * file corresponding to @tfile is बंदd, all its reference objects are
 * deleted. A reference object can have dअगरferent types depending on what
 * it's पूर्णांकended क्रम. It can be refcounting to prevent object deकाष्ठाion,
 * When user-space takes a lock, it can add a ref object to that lock to
 * make sure the lock is released अगर the application dies. A ref object
 * will hold a single reference on a base object.
 */
बाह्य पूर्णांक tपंचांग_ref_object_add(काष्ठा tपंचांग_object_file *tfile,
			      काष्ठा tपंचांग_base_object *base,
			      क्रमागत tपंचांग_ref_type ref_type, bool *existed,
			      bool require_existed);

बाह्य bool tपंचांग_ref_object_exists(काष्ठा tपंचांग_object_file *tfile,
				  काष्ठा tपंचांग_base_object *base);

/**
 * tपंचांग_ref_object_base_unref
 *
 * @key: Key representing the base object.
 * @ref_type: Ref type of the ref object to be dereferenced.
 *
 * Unreference a ref object with type @ref_type
 * on the base object identअगरied by @key. If there are no duplicate
 * references, the ref object will be destroyed and the base object
 * will be unreferenced.
 */
बाह्य पूर्णांक tपंचांग_ref_object_base_unref(काष्ठा tपंचांग_object_file *tfile,
				     अचिन्हित दीर्घ key,
				     क्रमागत tपंचांग_ref_type ref_type);

/**
 * tपंचांग_object_file_init - initialize a काष्ठा tपंचांग_object file
 *
 * @tdev: A काष्ठा tपंचांग_object device this file is initialized on.
 * @hash_order: Order of the hash table used to hold the reference objects.
 *
 * This is typically called by the file_ops::खोलो function.
 */

बाह्य काष्ठा tपंचांग_object_file *tपंचांग_object_file_init(काष्ठा tपंचांग_object_device
						    *tdev,
						    अचिन्हित पूर्णांक hash_order);

/**
 * tपंचांग_object_file_release - release data held by a tपंचांग_object_file
 *
 * @p_tfile: Poपूर्णांकer to poपूर्णांकer to the tपंचांग_object_file object to release.
 * *p_tfile will be set to शून्य by this function.
 *
 * Releases all data associated by a tपंचांग_object_file.
 * Typically called from file_ops::release. The caller must
 * ensure that there are no concurrent users of tfile.
 */

बाह्य व्योम tपंचांग_object_file_release(काष्ठा tपंचांग_object_file **p_tfile);

/**
 * tपंचांग_object device init - initialize a काष्ठा tपंचांग_object_device
 *
 * @mem_glob: काष्ठा tपंचांग_mem_global क्रम memory accounting.
 * @hash_order: Order of hash table used to hash the base objects.
 * @ops: DMA buf ops क्रम prime objects of this device.
 *
 * This function is typically called on device initialization to prepare
 * data काष्ठाures needed क्रम tपंचांग base and ref objects.
 */

बाह्य काष्ठा tपंचांग_object_device *
tपंचांग_object_device_init(काष्ठा tपंचांग_mem_global *mem_glob,
		       अचिन्हित पूर्णांक hash_order,
		       स्थिर काष्ठा dma_buf_ops *ops);

/**
 * tपंचांग_object_device_release - release data held by a tपंचांग_object_device
 *
 * @p_tdev: Poपूर्णांकer to poपूर्णांकer to the tपंचांग_object_device object to release.
 * *p_tdev will be set to शून्य by this function.
 *
 * Releases all data associated by a tपंचांग_object_device.
 * Typically called from driver::unload beक्रमe the deकाष्ठाion of the
 * device निजी data काष्ठाure.
 */

बाह्य व्योम tपंचांग_object_device_release(काष्ठा tपंचांग_object_device **p_tdev);

#घोषणा tपंचांग_base_object_kमुक्त(__object, __base)\
	kमुक्त_rcu(__object, __base.rhead)

बाह्य पूर्णांक tपंचांग_prime_object_init(काष्ठा tपंचांग_object_file *tfile,
				 माप_प्रकार size,
				 काष्ठा tपंचांग_prime_object *prime,
				 bool shareable,
				 क्रमागत tपंचांग_object_type type,
				 व्योम (*refcount_release)
				 (काष्ठा tपंचांग_base_object **),
				 व्योम (*ref_obj_release)
				 (काष्ठा tपंचांग_base_object *,
				  क्रमागत tपंचांग_ref_type ref_type));

अटल अंतरभूत क्रमागत tपंचांग_object_type
tपंचांग_base_object_type(काष्ठा tपंचांग_base_object *base)
अणु
	वापस (base->object_type == tपंचांग_prime_type) ?
		container_of(base, काष्ठा tपंचांग_prime_object, base)->real_type :
		base->object_type;
पूर्ण
बाह्य पूर्णांक tपंचांग_prime_fd_to_handle(काष्ठा tपंचांग_object_file *tfile,
				  पूर्णांक fd, u32 *handle);
बाह्य पूर्णांक tपंचांग_prime_handle_to_fd(काष्ठा tपंचांग_object_file *tfile,
				  uपूर्णांक32_t handle, uपूर्णांक32_t flags,
				  पूर्णांक *prime_fd);

#घोषणा tपंचांग_prime_object_kमुक्त(__obj, __prime)		\
	kमुक्त_rcu(__obj, __prime.base.rhead)

/*
 * Extra memory required by the base object's idr storage, which is allocated
 * separately from the base object itself. We estimate an on-average 128 bytes
 * per idr.
 */
#घोषणा TTM_OBJ_EXTRA_SIZE 128

काष्ठा tपंचांग_base_object *
tपंचांग_base_object_noref_lookup(काष्ठा tपंचांग_object_file *tfile, uपूर्णांक32_t key);

/**
 * tपंचांग_base_object_noref_release - release a base object poपूर्णांकer looked up
 * without reference
 *
 * Releases a base object poपूर्णांकer looked up with tपंचांग_base_object_noref_lookup().
 */
अटल अंतरभूत व्योम tपंचांग_base_object_noref_release(व्योम)
अणु
	__acquire(RCU);
	rcu_पढ़ो_unlock();
पूर्ण
#पूर्ण_अगर
