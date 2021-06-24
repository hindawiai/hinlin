<शैली गुरु>
/*
 * Copyright 2015 Advanced Micro Devices, Inc.
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
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS, AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 */
/*
 * Authors:
 *    Christian Kथघnig <deathsimple@vodafone.de>
 */

#समावेश <linux/uaccess.h>

#समावेश "amdgpu.h"
#समावेश "amdgpu_trace.h"

#घोषणा AMDGPU_BO_LIST_MAX_PRIORITY	32u
#घोषणा AMDGPU_BO_LIST_NUM_BUCKETS	(AMDGPU_BO_LIST_MAX_PRIORITY + 1)

अटल व्योम amdgpu_bo_list_मुक्त_rcu(काष्ठा rcu_head *rcu)
अणु
	काष्ठा amdgpu_bo_list *list = container_of(rcu, काष्ठा amdgpu_bo_list,
						   rhead);

	kvमुक्त(list);
पूर्ण

अटल व्योम amdgpu_bo_list_मुक्त(काष्ठा kref *ref)
अणु
	काष्ठा amdgpu_bo_list *list = container_of(ref, काष्ठा amdgpu_bo_list,
						   refcount);
	काष्ठा amdgpu_bo_list_entry *e;

	amdgpu_bo_list_क्रम_each_entry(e, list) अणु
		काष्ठा amdgpu_bo *bo = tपंचांग_to_amdgpu_bo(e->tv.bo);

		amdgpu_bo_unref(&bo);
	पूर्ण

	call_rcu(&list->rhead, amdgpu_bo_list_मुक्त_rcu);
पूर्ण

पूर्णांक amdgpu_bo_list_create(काष्ठा amdgpu_device *adev, काष्ठा drm_file *filp,
			  काष्ठा drm_amdgpu_bo_list_entry *info,
			  अचिन्हित num_entries, काष्ठा amdgpu_bo_list **result)
अणु
	अचिन्हित last_entry = 0, first_userptr = num_entries;
	काष्ठा amdgpu_bo_list_entry *array;
	काष्ठा amdgpu_bo_list *list;
	uपूर्णांक64_t total_size = 0;
	माप_प्रकार size;
	अचिन्हित i;
	पूर्णांक r;

	अगर (num_entries > (SIZE_MAX - माप(काष्ठा amdgpu_bo_list))
				/ माप(काष्ठा amdgpu_bo_list_entry))
		वापस -EINVAL;

	size = माप(काष्ठा amdgpu_bo_list);
	size += num_entries * माप(काष्ठा amdgpu_bo_list_entry);
	list = kvदो_स्मृति(size, GFP_KERNEL);
	अगर (!list)
		वापस -ENOMEM;

	kref_init(&list->refcount);
	list->gds_obj = शून्य;
	list->gws_obj = शून्य;
	list->oa_obj = शून्य;

	array = amdgpu_bo_list_array_entry(list, 0);
	स_रखो(array, 0, num_entries * माप(काष्ठा amdgpu_bo_list_entry));

	क्रम (i = 0; i < num_entries; ++i) अणु
		काष्ठा amdgpu_bo_list_entry *entry;
		काष्ठा drm_gem_object *gobj;
		काष्ठा amdgpu_bo *bo;
		काष्ठा mm_काष्ठा *usermm;

		gobj = drm_gem_object_lookup(filp, info[i].bo_handle);
		अगर (!gobj) अणु
			r = -ENOENT;
			जाओ error_मुक्त;
		पूर्ण

		bo = amdgpu_bo_ref(gem_to_amdgpu_bo(gobj));
		drm_gem_object_put(gobj);

		usermm = amdgpu_tपंचांग_tt_get_usermm(bo->tbo.tपंचांग);
		अगर (usermm) अणु
			अगर (usermm != current->mm) अणु
				amdgpu_bo_unref(&bo);
				r = -EPERM;
				जाओ error_मुक्त;
			पूर्ण
			entry = &array[--first_userptr];
		पूर्ण अन्यथा अणु
			entry = &array[last_entry++];
		पूर्ण

		entry->priority = min(info[i].bo_priority,
				      AMDGPU_BO_LIST_MAX_PRIORITY);
		entry->tv.bo = &bo->tbo;

		अगर (bo->preferred_करोमुख्यs == AMDGPU_GEM_DOMAIN_GDS)
			list->gds_obj = bo;
		अगर (bo->preferred_करोमुख्यs == AMDGPU_GEM_DOMAIN_GWS)
			list->gws_obj = bo;
		अगर (bo->preferred_करोमुख्यs == AMDGPU_GEM_DOMAIN_OA)
			list->oa_obj = bo;

		total_size += amdgpu_bo_size(bo);
		trace_amdgpu_bo_list_set(list, bo);
	पूर्ण

	list->first_userptr = first_userptr;
	list->num_entries = num_entries;

	trace_amdgpu_cs_bo_status(list->num_entries, total_size);

	*result = list;
	वापस 0;

error_मुक्त:
	क्रम (i = 0; i < last_entry; ++i) अणु
		काष्ठा amdgpu_bo *bo = tपंचांग_to_amdgpu_bo(array[i].tv.bo);

		amdgpu_bo_unref(&bo);
	पूर्ण
	क्रम (i = first_userptr; i < num_entries; ++i) अणु
		काष्ठा amdgpu_bo *bo = tपंचांग_to_amdgpu_bo(array[i].tv.bo);

		amdgpu_bo_unref(&bo);
	पूर्ण
	kvमुक्त(list);
	वापस r;

पूर्ण

अटल व्योम amdgpu_bo_list_destroy(काष्ठा amdgpu_fpriv *fpriv, पूर्णांक id)
अणु
	काष्ठा amdgpu_bo_list *list;

	mutex_lock(&fpriv->bo_list_lock);
	list = idr_हटाओ(&fpriv->bo_list_handles, id);
	mutex_unlock(&fpriv->bo_list_lock);
	अगर (list)
		kref_put(&list->refcount, amdgpu_bo_list_मुक्त);
पूर्ण

पूर्णांक amdgpu_bo_list_get(काष्ठा amdgpu_fpriv *fpriv, पूर्णांक id,
		       काष्ठा amdgpu_bo_list **result)
अणु
	rcu_पढ़ो_lock();
	*result = idr_find(&fpriv->bo_list_handles, id);

	अगर (*result && kref_get_unless_zero(&(*result)->refcount)) अणु
		rcu_पढ़ो_unlock();
		वापस 0;
	पूर्ण

	rcu_पढ़ो_unlock();
	वापस -ENOENT;
पूर्ण

व्योम amdgpu_bo_list_get_list(काष्ठा amdgpu_bo_list *list,
			     काष्ठा list_head *validated)
अणु
	/* This is based on the bucket sort with O(n) समय complनिकासy.
	 * An item with priority "i" is added to bucket[i]. The lists are then
	 * concatenated in descending order.
	 */
	काष्ठा list_head bucket[AMDGPU_BO_LIST_NUM_BUCKETS];
	काष्ठा amdgpu_bo_list_entry *e;
	अचिन्हित i;

	क्रम (i = 0; i < AMDGPU_BO_LIST_NUM_BUCKETS; i++)
		INIT_LIST_HEAD(&bucket[i]);

	/* Since buffers which appear sooner in the relocation list are
	 * likely to be used more often than buffers which appear later
	 * in the list, the sort mustn't change the ordering of buffers
	 * with the same priority, i.e. it must be stable.
	 */
	amdgpu_bo_list_क्रम_each_entry(e, list) अणु
		काष्ठा amdgpu_bo *bo = tपंचांग_to_amdgpu_bo(e->tv.bo);
		अचिन्हित priority = e->priority;

		अगर (!bo->parent)
			list_add_tail(&e->tv.head, &bucket[priority]);

		e->user_pages = शून्य;
	पूर्ण

	/* Connect the sorted buckets in the output list. */
	क्रम (i = 0; i < AMDGPU_BO_LIST_NUM_BUCKETS; i++)
		list_splice(&bucket[i], validated);
पूर्ण

व्योम amdgpu_bo_list_put(काष्ठा amdgpu_bo_list *list)
अणु
	kref_put(&list->refcount, amdgpu_bo_list_मुक्त);
पूर्ण

पूर्णांक amdgpu_bo_create_list_entry_array(काष्ठा drm_amdgpu_bo_list_in *in,
				      काष्ठा drm_amdgpu_bo_list_entry **info_param)
अणु
	स्थिर व्योम __user *uptr = u64_to_user_ptr(in->bo_info_ptr);
	स्थिर uपूर्णांक32_t info_size = माप(काष्ठा drm_amdgpu_bo_list_entry);
	काष्ठा drm_amdgpu_bo_list_entry *info;
	पूर्णांक r;

	info = kvदो_स्मृति_array(in->bo_number, info_size, GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	/* copy the handle array from userspace to a kernel buffer */
	r = -EFAULT;
	अगर (likely(info_size == in->bo_info_size)) अणु
		अचिन्हित दीर्घ bytes = in->bo_number *
			in->bo_info_size;

		अगर (copy_from_user(info, uptr, bytes))
			जाओ error_मुक्त;

	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ bytes = min(in->bo_info_size, info_size);
		अचिन्हित i;

		स_रखो(info, 0, in->bo_number * info_size);
		क्रम (i = 0; i < in->bo_number; ++i) अणु
			अगर (copy_from_user(&info[i], uptr, bytes))
				जाओ error_मुक्त;

			uptr += in->bo_info_size;
		पूर्ण
	पूर्ण

	*info_param = info;
	वापस 0;

error_मुक्त:
	kvमुक्त(info);
	वापस r;
पूर्ण

पूर्णांक amdgpu_bo_list_ioctl(काष्ठा drm_device *dev, व्योम *data,
				काष्ठा drm_file *filp)
अणु
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा amdgpu_fpriv *fpriv = filp->driver_priv;
	जोड़ drm_amdgpu_bo_list *args = data;
	uपूर्णांक32_t handle = args->in.list_handle;
	काष्ठा drm_amdgpu_bo_list_entry *info = शून्य;
	काष्ठा amdgpu_bo_list *list, *old;
	पूर्णांक r;

	r = amdgpu_bo_create_list_entry_array(&args->in, &info);
	अगर (r)
		वापस r;

	चयन (args->in.operation) अणु
	हाल AMDGPU_BO_LIST_OP_CREATE:
		r = amdgpu_bo_list_create(adev, filp, info, args->in.bo_number,
					  &list);
		अगर (r)
			जाओ error_मुक्त;

		mutex_lock(&fpriv->bo_list_lock);
		r = idr_alloc(&fpriv->bo_list_handles, list, 1, 0, GFP_KERNEL);
		mutex_unlock(&fpriv->bo_list_lock);
		अगर (r < 0) अणु
			जाओ error_put_list;
		पूर्ण

		handle = r;
		अवरोध;

	हाल AMDGPU_BO_LIST_OP_DESTROY:
		amdgpu_bo_list_destroy(fpriv, handle);
		handle = 0;
		अवरोध;

	हाल AMDGPU_BO_LIST_OP_UPDATE:
		r = amdgpu_bo_list_create(adev, filp, info, args->in.bo_number,
					  &list);
		अगर (r)
			जाओ error_मुक्त;

		mutex_lock(&fpriv->bo_list_lock);
		old = idr_replace(&fpriv->bo_list_handles, list, handle);
		mutex_unlock(&fpriv->bo_list_lock);

		अगर (IS_ERR(old)) अणु
			r = PTR_ERR(old);
			जाओ error_put_list;
		पूर्ण

		amdgpu_bo_list_put(old);
		अवरोध;

	शेष:
		r = -EINVAL;
		जाओ error_मुक्त;
	पूर्ण

	स_रखो(args, 0, माप(*args));
	args->out.list_handle = handle;
	kvमुक्त(info);

	वापस 0;

error_put_list:
	amdgpu_bo_list_put(list);

error_मुक्त:
	kvमुक्त(info);
	वापस r;
पूर्ण
