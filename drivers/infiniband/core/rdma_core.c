<शैली गुरु>
/*
 * Copyright (c) 2016, Mellanox Technologies inc.  All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश <linux/file.h>
#समावेश <linux/anon_inodes.h>
#समावेश <linux/sched/mm.h>
#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/uverbs_types.h>
#समावेश <linux/rcupdate.h>
#समावेश <rdma/uverbs_ioctl.h>
#समावेश <rdma/rdma_user_ioctl.h>
#समावेश "uverbs.h"
#समावेश "core_priv.h"
#समावेश "rdma_core.h"

अटल व्योम uverbs_uobject_मुक्त(काष्ठा kref *ref)
अणु
	kमुक्त_rcu(container_of(ref, काष्ठा ib_uobject, ref), rcu);
पूर्ण

/*
 * In order to indicate we no दीर्घer needs this uobject, uverbs_uobject_put
 * is called. When the reference count is decreased, the uobject is मुक्तd.
 * For example, this is used when attaching a completion channel to a CQ.
 */
व्योम uverbs_uobject_put(काष्ठा ib_uobject *uobject)
अणु
	kref_put(&uobject->ref, uverbs_uobject_मुक्त);
पूर्ण
EXPORT_SYMBOL(uverbs_uobject_put);

अटल पूर्णांक uverbs_try_lock_object(काष्ठा ib_uobject *uobj,
				  क्रमागत rdma_lookup_mode mode)
अणु
	/*
	 * When a shared access is required, we use a positive counter. Each
	 * shared access request checks that the value != -1 and increment it.
	 * Exclusive access is required क्रम operations like ग_लिखो or destroy.
	 * In exclusive access mode, we check that the counter is zero (nobody
	 * claimed this object) and we set it to -1. Releasing a shared access
	 * lock is करोne simply by decreasing the counter. As क्रम exclusive
	 * access locks, since only a single one of them is is allowed
	 * concurrently, setting the counter to zero is enough क्रम releasing
	 * this lock.
	 */
	चयन (mode) अणु
	हाल UVERBS_LOOKUP_READ:
		वापस atomic_fetch_add_unless(&uobj->usecnt, 1, -1) == -1 ?
			-EBUSY : 0;
	हाल UVERBS_LOOKUP_WRITE:
		/* lock is exclusive */
		वापस atomic_cmpxchg(&uobj->usecnt, 0, -1) == 0 ? 0 : -EBUSY;
	हाल UVERBS_LOOKUP_DESTROY:
		वापस 0;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम निश्चित_uverbs_usecnt(काष्ठा ib_uobject *uobj,
				 क्रमागत rdma_lookup_mode mode)
अणु
#अगर_घोषित CONFIG_LOCKDEP
	चयन (mode) अणु
	हाल UVERBS_LOOKUP_READ:
		WARN_ON(atomic_पढ़ो(&uobj->usecnt) <= 0);
		अवरोध;
	हाल UVERBS_LOOKUP_WRITE:
		WARN_ON(atomic_पढ़ो(&uobj->usecnt) != -1);
		अवरोध;
	हाल UVERBS_LOOKUP_DESTROY:
		अवरोध;
	पूर्ण
#पूर्ण_अगर
पूर्ण

/*
 * This must be called with the hw_destroy_rwsem locked क्रम पढ़ो or ग_लिखो,
 * also the uobject itself must be locked क्रम ग_लिखो.
 *
 * Upon वापस the HW object is guaranteed to be destroyed.
 *
 * For RDMA_REMOVE_ABORT, the hw_destroy_rwsem is not required to be held,
 * however the type's allocat_commit function cannot have been called and the
 * uobject cannot be on the uobjects_lists
 *
 * For RDMA_REMOVE_DESTROY the caller should be holding a kref (eg via
 * rdma_lookup_get_uobject) and the object is left in a state where the caller
 * needs to call rdma_lookup_put_uobject.
 *
 * For all other destroy modes this function पूर्णांकernally unlocks the uobject
 * and consumes the kref on the uobj.
 */
अटल पूर्णांक uverbs_destroy_uobject(काष्ठा ib_uobject *uobj,
				  क्रमागत rdma_हटाओ_reason reason,
				  काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uverbs_file *ufile = attrs->ufile;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	lockdep_निश्चित_held(&ufile->hw_destroy_rwsem);
	निश्चित_uverbs_usecnt(uobj, UVERBS_LOOKUP_WRITE);

	अगर (reason == RDMA_REMOVE_ABORT) अणु
		WARN_ON(!list_empty(&uobj->list));
		WARN_ON(!uobj->context);
		uobj->uapi_object->type_class->alloc_पात(uobj);
	पूर्ण अन्यथा अगर (uobj->object) अणु
		ret = uobj->uapi_object->type_class->destroy_hw(uobj, reason,
								attrs);
		अगर (ret)
			/* Nothing to be करोne, रुको till ucontext will clean it */
			वापस ret;

		uobj->object = शून्य;
	पूर्ण

	uobj->context = शून्य;

	/*
	 * For DESTROY the usecnt is not changed, the caller is expected to
	 * manage it via uobj_put_destroy(). Only DESTROY can हटाओ the IDR
	 * handle.
	 */
	अगर (reason != RDMA_REMOVE_DESTROY)
		atomic_set(&uobj->usecnt, 0);
	अन्यथा
		uobj->uapi_object->type_class->हटाओ_handle(uobj);

	अगर (!list_empty(&uobj->list)) अणु
		spin_lock_irqsave(&ufile->uobjects_lock, flags);
		list_del_init(&uobj->list);
		spin_unlock_irqrestore(&ufile->uobjects_lock, flags);

		/*
		 * Pairs with the get in rdma_alloc_commit_uobject(), could
		 * destroy uobj.
		 */
		uverbs_uobject_put(uobj);
	पूर्ण

	/*
	 * When पातing the stack kref reमुख्यs owned by the core code, and is
	 * not transferred पूर्णांकo the type. Pairs with the get in alloc_uobj
	 */
	अगर (reason == RDMA_REMOVE_ABORT)
		uverbs_uobject_put(uobj);

	वापस 0;
पूर्ण

/*
 * This calls uverbs_destroy_uobject() using the RDMA_REMOVE_DESTROY
 * sequence. It should only be used from command callbacks. On success the
 * caller must pair this with uobj_put_destroy(). This
 * version requires the caller to have alपढ़ोy obtained an
 * LOOKUP_DESTROY uobject kref.
 */
पूर्णांक uobj_destroy(काष्ठा ib_uobject *uobj, काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uverbs_file *ufile = attrs->ufile;
	पूर्णांक ret;

	करोwn_पढ़ो(&ufile->hw_destroy_rwsem);

	/*
	 * Once the uobject is destroyed by RDMA_REMOVE_DESTROY then it is left
	 * ग_लिखो locked as the callers put it back with UVERBS_LOOKUP_DESTROY.
	 * This is because any other concurrent thपढ़ो can still see the object
	 * in the xarray due to RCU. Leaving it locked ensures nothing अन्यथा will
	 * touch it.
	 */
	ret = uverbs_try_lock_object(uobj, UVERBS_LOOKUP_WRITE);
	अगर (ret)
		जाओ out_unlock;

	ret = uverbs_destroy_uobject(uobj, RDMA_REMOVE_DESTROY, attrs);
	अगर (ret) अणु
		atomic_set(&uobj->usecnt, 0);
		जाओ out_unlock;
	पूर्ण

out_unlock:
	up_पढ़ो(&ufile->hw_destroy_rwsem);
	वापस ret;
पूर्ण

/*
 * uobj_get_destroy destroys the HW object and वापसs a handle to the uobj
 * with a शून्य object poपूर्णांकer. The caller must pair this with
 * uobj_put_destroy().
 */
काष्ठा ib_uobject *__uobj_get_destroy(स्थिर काष्ठा uverbs_api_object *obj,
				      u32 id, काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uobject *uobj;
	पूर्णांक ret;

	uobj = rdma_lookup_get_uobject(obj, attrs->ufile, id,
				       UVERBS_LOOKUP_DESTROY, attrs);
	अगर (IS_ERR(uobj))
		वापस uobj;

	ret = uobj_destroy(uobj, attrs);
	अगर (ret) अणु
		rdma_lookup_put_uobject(uobj, UVERBS_LOOKUP_DESTROY);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस uobj;
पूर्ण

/*
 * Does both uobj_get_destroy() and uobj_put_destroy().  Returns 0 on success
 * (negative त्रुटि_सं on failure). For use by callers that करो not need the uobj.
 */
पूर्णांक __uobj_perक्रमm_destroy(स्थिर काष्ठा uverbs_api_object *obj, u32 id,
			   काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uobject *uobj;

	uobj = __uobj_get_destroy(obj, id, attrs);
	अगर (IS_ERR(uobj))
		वापस PTR_ERR(uobj);
	uobj_put_destroy(uobj);
	वापस 0;
पूर्ण

/* alloc_uobj must be unकरोne by uverbs_destroy_uobject() */
अटल काष्ठा ib_uobject *alloc_uobj(काष्ठा uverbs_attr_bundle *attrs,
				     स्थिर काष्ठा uverbs_api_object *obj)
अणु
	काष्ठा ib_uverbs_file *ufile = attrs->ufile;
	काष्ठा ib_uobject *uobj;

	अगर (!attrs->context) अणु
		काष्ठा ib_ucontext *ucontext =
			ib_uverbs_get_ucontext_file(ufile);

		अगर (IS_ERR(ucontext))
			वापस ERR_CAST(ucontext);
		attrs->context = ucontext;
	पूर्ण

	uobj = kzalloc(obj->type_attrs->obj_size, GFP_KERNEL);
	अगर (!uobj)
		वापस ERR_PTR(-ENOMEM);
	/*
	 * user_handle should be filled by the handler,
	 * The object is added to the list in the commit stage.
	 */
	uobj->ufile = ufile;
	uobj->context = attrs->context;
	INIT_LIST_HEAD(&uobj->list);
	uobj->uapi_object = obj;
	/*
	 * Allocated objects start out as ग_लिखो locked to deny any other
	 * syscalls from accessing them until they are committed. See
	 * rdma_alloc_commit_uobject
	 */
	atomic_set(&uobj->usecnt, -1);
	kref_init(&uobj->ref);

	वापस uobj;
पूर्ण

अटल पूर्णांक idr_add_uobj(काष्ठा ib_uobject *uobj)
अणु
       /*
        * We start with allocating an idr poपूर्णांकing to शून्य. This represents an
        * object which isn't initialized yet. We'll replace it later on with
        * the real object once we commit.
        */
	वापस xa_alloc(&uobj->ufile->idr, &uobj->id, शून्य, xa_limit_32b,
			GFP_KERNEL);
पूर्ण

/* Returns the ib_uobject or an error. The caller should check क्रम IS_ERR. */
अटल काष्ठा ib_uobject *
lookup_get_idr_uobject(स्थिर काष्ठा uverbs_api_object *obj,
		       काष्ठा ib_uverbs_file *ufile, s64 id,
		       क्रमागत rdma_lookup_mode mode)
अणु
	काष्ठा ib_uobject *uobj;

	अगर (id < 0 || id > अच_दीर्घ_उच्च)
		वापस ERR_PTR(-EINVAL);

	rcu_पढ़ो_lock();
	/*
	 * The idr_find is guaranteed to वापस a poपूर्णांकer to something that
	 * isn't मुक्तd yet, or शून्य, as the मुक्त after idr_हटाओ goes through
	 * kमुक्त_rcu(). However the object may still have been released and
	 * kमुक्त() could be called at any समय.
	 */
	uobj = xa_load(&ufile->idr, id);
	अगर (!uobj || !kref_get_unless_zero(&uobj->ref))
		uobj = ERR_PTR(-ENOENT);
	rcu_पढ़ो_unlock();
	वापस uobj;
पूर्ण

अटल काष्ठा ib_uobject *
lookup_get_fd_uobject(स्थिर काष्ठा uverbs_api_object *obj,
		      काष्ठा ib_uverbs_file *ufile, s64 id,
		      क्रमागत rdma_lookup_mode mode)
अणु
	स्थिर काष्ठा uverbs_obj_fd_type *fd_type;
	काष्ठा file *f;
	काष्ठा ib_uobject *uobject;
	पूर्णांक fdno = id;

	अगर (fdno != id)
		वापस ERR_PTR(-EINVAL);

	अगर (mode != UVERBS_LOOKUP_READ)
		वापस ERR_PTR(-EOPNOTSUPP);

	अगर (!obj->type_attrs)
		वापस ERR_PTR(-EIO);
	fd_type =
		container_of(obj->type_attrs, काष्ठा uverbs_obj_fd_type, type);

	f = fget(fdno);
	अगर (!f)
		वापस ERR_PTR(-EBADF);

	uobject = f->निजी_data;
	/*
	 * fget(id) ensures we are not currently running
	 * uverbs_uobject_fd_release(), and the caller is expected to ensure
	 * that release is never करोne जबतक a call to lookup is possible.
	 */
	अगर (f->f_op != fd_type->fops || uobject->ufile != ufile) अणु
		fput(f);
		वापस ERR_PTR(-EBADF);
	पूर्ण

	uverbs_uobject_get(uobject);
	वापस uobject;
पूर्ण

काष्ठा ib_uobject *rdma_lookup_get_uobject(स्थिर काष्ठा uverbs_api_object *obj,
					   काष्ठा ib_uverbs_file *ufile, s64 id,
					   क्रमागत rdma_lookup_mode mode,
					   काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uobject *uobj;
	पूर्णांक ret;

	अगर (obj == ERR_PTR(-ENOMSG)) अणु
		/* must be UVERBS_IDR_ANY_OBJECT, see uapi_get_object() */
		uobj = lookup_get_idr_uobject(शून्य, ufile, id, mode);
		अगर (IS_ERR(uobj))
			वापस uobj;
	पूर्ण अन्यथा अणु
		अगर (IS_ERR(obj))
			वापस ERR_PTR(-EINVAL);

		uobj = obj->type_class->lookup_get(obj, ufile, id, mode);
		अगर (IS_ERR(uobj))
			वापस uobj;

		अगर (uobj->uapi_object != obj) अणु
			ret = -EINVAL;
			जाओ मुक्त;
		पूर्ण
	पूर्ण

	/*
	 * If we have been disassociated block every command except क्रम
	 * DESTROY based commands.
	 */
	अगर (mode != UVERBS_LOOKUP_DESTROY &&
	    !srcu_dereference(ufile->device->ib_dev,
			      &ufile->device->disassociate_srcu)) अणु
		ret = -EIO;
		जाओ मुक्त;
	पूर्ण

	ret = uverbs_try_lock_object(uobj, mode);
	अगर (ret)
		जाओ मुक्त;
	अगर (attrs)
		attrs->context = uobj->context;

	वापस uobj;
मुक्त:
	uobj->uapi_object->type_class->lookup_put(uobj, mode);
	uverbs_uobject_put(uobj);
	वापस ERR_PTR(ret);
पूर्ण

अटल काष्ठा ib_uobject *
alloc_begin_idr_uobject(स्थिर काष्ठा uverbs_api_object *obj,
			काष्ठा uverbs_attr_bundle *attrs)
अणु
	पूर्णांक ret;
	काष्ठा ib_uobject *uobj;

	uobj = alloc_uobj(attrs, obj);
	अगर (IS_ERR(uobj))
		वापस uobj;

	ret = idr_add_uobj(uobj);
	अगर (ret)
		जाओ uobj_put;

	ret = ib_rdmacg_try_अक्षरge(&uobj->cg_obj, uobj->context->device,
				   RDMACG_RESOURCE_HCA_OBJECT);
	अगर (ret)
		जाओ हटाओ;

	वापस uobj;

हटाओ:
	xa_erase(&attrs->ufile->idr, uobj->id);
uobj_put:
	uverbs_uobject_put(uobj);
	वापस ERR_PTR(ret);
पूर्ण

अटल काष्ठा ib_uobject *
alloc_begin_fd_uobject(स्थिर काष्ठा uverbs_api_object *obj,
		       काष्ठा uverbs_attr_bundle *attrs)
अणु
	स्थिर काष्ठा uverbs_obj_fd_type *fd_type;
	पूर्णांक new_fd;
	काष्ठा ib_uobject *uobj, *ret;
	काष्ठा file *filp;

	uobj = alloc_uobj(attrs, obj);
	अगर (IS_ERR(uobj))
		वापस uobj;

	fd_type =
		container_of(obj->type_attrs, काष्ठा uverbs_obj_fd_type, type);
	अगर (WARN_ON(fd_type->fops->release != &uverbs_uobject_fd_release &&
		    fd_type->fops->release != &uverbs_async_event_release)) अणु
		ret = ERR_PTR(-EINVAL);
		जाओ err_fd;
	पूर्ण

	new_fd = get_unused_fd_flags(O_CLOEXEC);
	अगर (new_fd < 0) अणु
		ret = ERR_PTR(new_fd);
		जाओ err_fd;
	पूर्ण

	/* Note that uverbs_uobject_fd_release() is called during पात */
	filp = anon_inode_getfile(fd_type->name, fd_type->fops, शून्य,
				  fd_type->flags);
	अगर (IS_ERR(filp)) अणु
		ret = ERR_CAST(filp);
		जाओ err_getfile;
	पूर्ण
	uobj->object = filp;

	uobj->id = new_fd;
	वापस uobj;

err_getfile:
	put_unused_fd(new_fd);
err_fd:
	uverbs_uobject_put(uobj);
	वापस ret;
पूर्ण

काष्ठा ib_uobject *rdma_alloc_begin_uobject(स्थिर काष्ठा uverbs_api_object *obj,
					    काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uverbs_file *ufile = attrs->ufile;
	काष्ठा ib_uobject *ret;

	अगर (IS_ERR(obj))
		वापस ERR_PTR(-EINVAL);

	/*
	 * The hw_destroy_rwsem is held across the entire object creation and
	 * released during rdma_alloc_commit_uobject or
	 * rdma_alloc_पात_uobject
	 */
	अगर (!करोwn_पढ़ो_trylock(&ufile->hw_destroy_rwsem))
		वापस ERR_PTR(-EIO);

	ret = obj->type_class->alloc_begin(obj, attrs);
	अगर (IS_ERR(ret)) अणु
		up_पढ़ो(&ufile->hw_destroy_rwsem);
		वापस ret;
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम alloc_पात_idr_uobject(काष्ठा ib_uobject *uobj)
अणु
	ib_rdmacg_unअक्षरge(&uobj->cg_obj, uobj->context->device,
			   RDMACG_RESOURCE_HCA_OBJECT);

	xa_erase(&uobj->ufile->idr, uobj->id);
पूर्ण

अटल पूर्णांक __must_check destroy_hw_idr_uobject(काष्ठा ib_uobject *uobj,
					       क्रमागत rdma_हटाओ_reason why,
					       काष्ठा uverbs_attr_bundle *attrs)
अणु
	स्थिर काष्ठा uverbs_obj_idr_type *idr_type =
		container_of(uobj->uapi_object->type_attrs,
			     काष्ठा uverbs_obj_idr_type, type);
	पूर्णांक ret = idr_type->destroy_object(uobj, why, attrs);

	अगर (ret)
		वापस ret;

	अगर (why == RDMA_REMOVE_ABORT)
		वापस 0;

	ib_rdmacg_unअक्षरge(&uobj->cg_obj, uobj->context->device,
			   RDMACG_RESOURCE_HCA_OBJECT);

	वापस 0;
पूर्ण

अटल व्योम हटाओ_handle_idr_uobject(काष्ठा ib_uobject *uobj)
अणु
	xa_erase(&uobj->ufile->idr, uobj->id);
	/* Matches the kref in alloc_commit_idr_uobject */
	uverbs_uobject_put(uobj);
पूर्ण

अटल व्योम alloc_पात_fd_uobject(काष्ठा ib_uobject *uobj)
अणु
	काष्ठा file *filp = uobj->object;

	fput(filp);
	put_unused_fd(uobj->id);
पूर्ण

अटल पूर्णांक __must_check destroy_hw_fd_uobject(काष्ठा ib_uobject *uobj,
					      क्रमागत rdma_हटाओ_reason why,
					      काष्ठा uverbs_attr_bundle *attrs)
अणु
	स्थिर काष्ठा uverbs_obj_fd_type *fd_type = container_of(
		uobj->uapi_object->type_attrs, काष्ठा uverbs_obj_fd_type, type);

	fd_type->destroy_object(uobj, why);
	वापस 0;
पूर्ण

अटल व्योम हटाओ_handle_fd_uobject(काष्ठा ib_uobject *uobj)
अणु
पूर्ण

अटल व्योम alloc_commit_idr_uobject(काष्ठा ib_uobject *uobj)
अणु
	काष्ठा ib_uverbs_file *ufile = uobj->ufile;
	व्योम *old;

	/*
	 * We alपढ़ोy allocated this IDR with a शून्य object, so
	 * this shouldn't fail.
	 *
	 * NOTE: Storing the uobj transfers our kref on uobj to the XArray.
	 * It will be put by हटाओ_commit_idr_uobject()
	 */
	old = xa_store(&ufile->idr, uobj->id, uobj, GFP_KERNEL);
	WARN_ON(old != शून्य);
पूर्ण

अटल व्योम swap_idr_uobjects(काष्ठा ib_uobject *obj_old,
			     काष्ठा ib_uobject *obj_new)
अणु
	काष्ठा ib_uverbs_file *ufile = obj_old->ufile;
	व्योम *old;

	/*
	 * New must be an object that been allocated but not yet committed, this
	 * moves the pre-committed state to obj_old, new still must be comitted.
	 */
	old = xa_cmpxchg(&ufile->idr, obj_old->id, obj_old, XA_ZERO_ENTRY,
			 GFP_KERNEL);
	अगर (WARN_ON(old != obj_old))
		वापस;

	swap(obj_old->id, obj_new->id);

	old = xa_cmpxchg(&ufile->idr, obj_old->id, शून्य, obj_old, GFP_KERNEL);
	WARN_ON(old != शून्य);
पूर्ण

अटल व्योम alloc_commit_fd_uobject(काष्ठा ib_uobject *uobj)
अणु
	पूर्णांक fd = uobj->id;
	काष्ठा file *filp = uobj->object;

	/* Matching put will be करोne in uverbs_uobject_fd_release() */
	kref_get(&uobj->ufile->ref);

	/* This shouldn't be used anymore. Use the file object instead */
	uobj->id = 0;

	/*
	 * NOTE: Once we install the file we loose ownership of our kref on
	 * uobj. It will be put by uverbs_uobject_fd_release()
	 */
	filp->निजी_data = uobj;
	fd_install(fd, filp);
पूर्ण

/*
 * In all हालs rdma_alloc_commit_uobject() consumes the kref to uobj and the
 * caller can no दीर्घer assume uobj is valid. If this function fails it
 * destroys the uboject, including the attached HW object.
 */
व्योम rdma_alloc_commit_uobject(काष्ठा ib_uobject *uobj,
			       काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uverbs_file *ufile = attrs->ufile;

	/* kref is held so दीर्घ as the uobj is on the uobj list. */
	uverbs_uobject_get(uobj);
	spin_lock_irq(&ufile->uobjects_lock);
	list_add(&uobj->list, &ufile->uobjects);
	spin_unlock_irq(&ufile->uobjects_lock);

	/* matches atomic_set(-1) in alloc_uobj */
	atomic_set(&uobj->usecnt, 0);

	/* alloc_commit consumes the uobj kref */
	uobj->uapi_object->type_class->alloc_commit(uobj);

	/* Matches the करोwn_पढ़ो in rdma_alloc_begin_uobject */
	up_पढ़ो(&ufile->hw_destroy_rwsem);
पूर्ण

/*
 * new_uobj will be asचिन्हित to the handle currently used by to_uobj, and
 * to_uobj will be destroyed.
 *
 * Upon वापस the caller must करो:
 *    rdma_alloc_commit_uobject(new_uobj)
 *    uobj_put_destroy(to_uobj)
 *
 * to_uobj must have a ग_लिखो get but the put mode चयनes to destroy once
 * this is called.
 */
व्योम rdma_assign_uobject(काष्ठा ib_uobject *to_uobj, काष्ठा ib_uobject *new_uobj,
			काष्ठा uverbs_attr_bundle *attrs)
अणु
	निश्चित_uverbs_usecnt(new_uobj, UVERBS_LOOKUP_WRITE);

	अगर (WARN_ON(to_uobj->uapi_object != new_uobj->uapi_object ||
		    !to_uobj->uapi_object->type_class->swap_uobjects))
		वापस;

	to_uobj->uapi_object->type_class->swap_uobjects(to_uobj, new_uobj);

	/*
	 * If this fails then the uobject is still completely valid (though with
	 * a new ID) and we leak it until context बंद.
	 */
	uverbs_destroy_uobject(to_uobj, RDMA_REMOVE_DESTROY, attrs);
पूर्ण

/*
 * This consumes the kref क्रम uobj. It is up to the caller to unwind the HW
 * object and anything अन्यथा connected to uobj beक्रमe calling this.
 */
व्योम rdma_alloc_पात_uobject(काष्ठा ib_uobject *uobj,
			      काष्ठा uverbs_attr_bundle *attrs,
			      bool hw_obj_valid)
अणु
	काष्ठा ib_uverbs_file *ufile = uobj->ufile;
	पूर्णांक ret;

	अगर (hw_obj_valid) अणु
		ret = uobj->uapi_object->type_class->destroy_hw(
			uobj, RDMA_REMOVE_ABORT, attrs);
		/*
		 * If the driver couldn't destroy the object then go ahead and
		 * commit it. Leaking objects that can't be destroyed is only
		 * करोne during FD बंद after the driver has a few more tries to
		 * destroy it.
		 */
		अगर (WARN_ON(ret))
			वापस rdma_alloc_commit_uobject(uobj, attrs);
	पूर्ण

	uverbs_destroy_uobject(uobj, RDMA_REMOVE_ABORT, attrs);

	/* Matches the करोwn_पढ़ो in rdma_alloc_begin_uobject */
	up_पढ़ो(&ufile->hw_destroy_rwsem);
पूर्ण

अटल व्योम lookup_put_idr_uobject(काष्ठा ib_uobject *uobj,
				   क्रमागत rdma_lookup_mode mode)
अणु
पूर्ण

अटल व्योम lookup_put_fd_uobject(काष्ठा ib_uobject *uobj,
				  क्रमागत rdma_lookup_mode mode)
अणु
	काष्ठा file *filp = uobj->object;

	WARN_ON(mode != UVERBS_LOOKUP_READ);
	/*
	 * This indirectly calls uverbs_uobject_fd_release() and मुक्त the
	 * object
	 */
	fput(filp);
पूर्ण

व्योम rdma_lookup_put_uobject(काष्ठा ib_uobject *uobj,
			     क्रमागत rdma_lookup_mode mode)
अणु
	निश्चित_uverbs_usecnt(uobj, mode);
	/*
	 * In order to unlock an object, either decrease its usecnt क्रम
	 * पढ़ो access or zero it in हाल of exclusive access. See
	 * uverbs_try_lock_object क्रम locking schema inक्रमmation.
	 */
	चयन (mode) अणु
	हाल UVERBS_LOOKUP_READ:
		atomic_dec(&uobj->usecnt);
		अवरोध;
	हाल UVERBS_LOOKUP_WRITE:
		atomic_set(&uobj->usecnt, 0);
		अवरोध;
	हाल UVERBS_LOOKUP_DESTROY:
		अवरोध;
	पूर्ण

	uobj->uapi_object->type_class->lookup_put(uobj, mode);
	/* Pairs with the kref obtained by type->lookup_get */
	uverbs_uobject_put(uobj);
पूर्ण

व्योम setup_ufile_idr_uobject(काष्ठा ib_uverbs_file *ufile)
अणु
	xa_init_flags(&ufile->idr, XA_FLAGS_ALLOC);
पूर्ण

व्योम release_ufile_idr_uobject(काष्ठा ib_uverbs_file *ufile)
अणु
	काष्ठा ib_uobject *entry;
	अचिन्हित दीर्घ id;

	/*
	 * At this poपूर्णांक uverbs_cleanup_ufile() is guaranteed to have run, and
	 * there are no HW objects left, however the xarray is still populated
	 * with anything that has not been cleaned up by userspace. Since the
	 * kref on ufile is 0, nothing is allowed to call lookup_get.
	 *
	 * This is an optimized equivalent to हटाओ_handle_idr_uobject
	 */
	xa_क्रम_each(&ufile->idr, id, entry) अणु
		WARN_ON(entry->object);
		uverbs_uobject_put(entry);
	पूर्ण

	xa_destroy(&ufile->idr);
पूर्ण

स्थिर काष्ठा uverbs_obj_type_class uverbs_idr_class = अणु
	.alloc_begin = alloc_begin_idr_uobject,
	.lookup_get = lookup_get_idr_uobject,
	.alloc_commit = alloc_commit_idr_uobject,
	.alloc_पात = alloc_पात_idr_uobject,
	.lookup_put = lookup_put_idr_uobject,
	.destroy_hw = destroy_hw_idr_uobject,
	.हटाओ_handle = हटाओ_handle_idr_uobject,
	.swap_uobjects = swap_idr_uobjects,
पूर्ण;
EXPORT_SYMBOL(uverbs_idr_class);

/*
 * Users of UVERBS_TYPE_ALLOC_FD should set this function as the काष्ठा
 * file_operations release method.
 */
पूर्णांक uverbs_uobject_fd_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा ib_uverbs_file *ufile;
	काष्ठा ib_uobject *uobj;

	/*
	 * This can only happen अगर the fput came from alloc_पात_fd_uobject()
	 */
	अगर (!filp->निजी_data)
		वापस 0;
	uobj = filp->निजी_data;
	ufile = uobj->ufile;

	अगर (करोwn_पढ़ो_trylock(&ufile->hw_destroy_rwsem)) अणु
		काष्ठा uverbs_attr_bundle attrs = अणु
			.context = uobj->context,
			.ufile = ufile,
		पूर्ण;

		/*
		 * lookup_get_fd_uobject holds the kref on the काष्ठा file any
		 * समय a FD uobj is locked, which prevents this release
		 * method from being invoked. Meaning we can always get the
		 * ग_लिखो lock here, or we have a kernel bug.
		 */
		WARN_ON(uverbs_try_lock_object(uobj, UVERBS_LOOKUP_WRITE));
		uverbs_destroy_uobject(uobj, RDMA_REMOVE_CLOSE, &attrs);
		up_पढ़ो(&ufile->hw_destroy_rwsem);
	पूर्ण

	/* Matches the get in alloc_commit_fd_uobject() */
	kref_put(&ufile->ref, ib_uverbs_release_file);

	/* Pairs with filp->निजी_data in alloc_begin_fd_uobject */
	uverbs_uobject_put(uobj);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(uverbs_uobject_fd_release);

/*
 * Drop the ucontext off the ufile and completely disconnect it from the
 * ib_device
 */
अटल व्योम ufile_destroy_ucontext(काष्ठा ib_uverbs_file *ufile,
				   क्रमागत rdma_हटाओ_reason reason)
अणु
	काष्ठा ib_ucontext *ucontext = ufile->ucontext;
	काष्ठा ib_device *ib_dev = ucontext->device;

	/*
	 * If we are closing the FD then the user mmap VMAs must have
	 * alपढ़ोy been destroyed as they hold on to the filep, otherwise
	 * they need to be zap'd.
	 */
	अगर (reason == RDMA_REMOVE_DRIVER_REMOVE) अणु
		uverbs_user_mmap_disassociate(ufile);
		अगर (ib_dev->ops.disassociate_ucontext)
			ib_dev->ops.disassociate_ucontext(ucontext);
	पूर्ण

	ib_rdmacg_unअक्षरge(&ucontext->cg_obj, ib_dev,
			   RDMACG_RESOURCE_HCA_HANDLE);

	rdma_restrack_del(&ucontext->res);

	ib_dev->ops.dealloc_ucontext(ucontext);
	WARN_ON(!xa_empty(&ucontext->mmap_xa));
	kमुक्त(ucontext);

	ufile->ucontext = शून्य;
पूर्ण

अटल पूर्णांक __uverbs_cleanup_ufile(काष्ठा ib_uverbs_file *ufile,
				  क्रमागत rdma_हटाओ_reason reason)
अणु
	काष्ठा ib_uobject *obj, *next_obj;
	पूर्णांक ret = -EINVAL;
	काष्ठा uverbs_attr_bundle attrs = अणु .ufile = ufile पूर्ण;

	/*
	 * This shouldn't run जबतक executing other commands on this
	 * context. Thus, the only thing we should take care of is
	 * releasing a FD जबतक traversing this list. The FD could be
	 * बंदd and released from the _release fop of this FD.
	 * In order to mitigate this, we add a lock.
	 * We take and release the lock per traversal in order to let
	 * other thपढ़ोs (which might still use the FDs) chance to run.
	 */
	list_क्रम_each_entry_safe(obj, next_obj, &ufile->uobjects, list) अणु
		attrs.context = obj->context;
		/*
		 * अगर we hit this WARN_ON, that means we are
		 * racing with a lookup_get.
		 */
		WARN_ON(uverbs_try_lock_object(obj, UVERBS_LOOKUP_WRITE));
		अगर (reason == RDMA_REMOVE_DRIVER_FAILURE)
			obj->object = शून्य;
		अगर (!uverbs_destroy_uobject(obj, reason, &attrs))
			ret = 0;
		अन्यथा
			atomic_set(&obj->usecnt, 0);
	पूर्ण

	अगर (reason == RDMA_REMOVE_DRIVER_FAILURE) अणु
		WARN_ON(!list_empty(&ufile->uobjects));
		वापस 0;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Destroy the ucontext and every uobject associated with it.
 *
 * This is पूर्णांकernally locked and can be called in parallel from multiple
 * contexts.
 */
व्योम uverbs_destroy_ufile_hw(काष्ठा ib_uverbs_file *ufile,
			     क्रमागत rdma_हटाओ_reason reason)
अणु
	करोwn_ग_लिखो(&ufile->hw_destroy_rwsem);

	/*
	 * If a ucontext was never created then we can't have any uobjects to
	 * cleanup, nothing to करो.
	 */
	अगर (!ufile->ucontext)
		जाओ करोne;

	जबतक (!list_empty(&ufile->uobjects) &&
	       !__uverbs_cleanup_ufile(ufile, reason)) अणु
	पूर्ण

	अगर (WARN_ON(!list_empty(&ufile->uobjects)))
		__uverbs_cleanup_ufile(ufile, RDMA_REMOVE_DRIVER_FAILURE);
	ufile_destroy_ucontext(ufile, reason);

करोne:
	up_ग_लिखो(&ufile->hw_destroy_rwsem);
पूर्ण

स्थिर काष्ठा uverbs_obj_type_class uverbs_fd_class = अणु
	.alloc_begin = alloc_begin_fd_uobject,
	.lookup_get = lookup_get_fd_uobject,
	.alloc_commit = alloc_commit_fd_uobject,
	.alloc_पात = alloc_पात_fd_uobject,
	.lookup_put = lookup_put_fd_uobject,
	.destroy_hw = destroy_hw_fd_uobject,
	.हटाओ_handle = हटाओ_handle_fd_uobject,
पूर्ण;
EXPORT_SYMBOL(uverbs_fd_class);

काष्ठा ib_uobject *
uverbs_get_uobject_from_file(u16 object_id, क्रमागत uverbs_obj_access access,
			     s64 id, काष्ठा uverbs_attr_bundle *attrs)
अणु
	स्थिर काष्ठा uverbs_api_object *obj =
		uapi_get_object(attrs->ufile->device->uapi, object_id);

	चयन (access) अणु
	हाल UVERBS_ACCESS_READ:
		वापस rdma_lookup_get_uobject(obj, attrs->ufile, id,
					       UVERBS_LOOKUP_READ, attrs);
	हाल UVERBS_ACCESS_DESTROY:
		/* Actual deकाष्ठाion is करोne inside uverbs_handle_method */
		वापस rdma_lookup_get_uobject(obj, attrs->ufile, id,
					       UVERBS_LOOKUP_DESTROY, attrs);
	हाल UVERBS_ACCESS_WRITE:
		वापस rdma_lookup_get_uobject(obj, attrs->ufile, id,
					       UVERBS_LOOKUP_WRITE, attrs);
	हाल UVERBS_ACCESS_NEW:
		वापस rdma_alloc_begin_uobject(obj, attrs);
	शेष:
		WARN_ON(true);
		वापस ERR_PTR(-EOPNOTSUPP);
	पूर्ण
पूर्ण

व्योम uverbs_finalize_object(काष्ठा ib_uobject *uobj,
			    क्रमागत uverbs_obj_access access, bool hw_obj_valid,
			    bool commit, काष्ठा uverbs_attr_bundle *attrs)
अणु
	/*
	 * refcounts should be handled at the object level and not at the
	 * uobject level. Refcounts of the objects themselves are करोne in
	 * handlers.
	 */

	चयन (access) अणु
	हाल UVERBS_ACCESS_READ:
		rdma_lookup_put_uobject(uobj, UVERBS_LOOKUP_READ);
		अवरोध;
	हाल UVERBS_ACCESS_WRITE:
		rdma_lookup_put_uobject(uobj, UVERBS_LOOKUP_WRITE);
		अवरोध;
	हाल UVERBS_ACCESS_DESTROY:
		अगर (uobj)
			rdma_lookup_put_uobject(uobj, UVERBS_LOOKUP_DESTROY);
		अवरोध;
	हाल UVERBS_ACCESS_NEW:
		अगर (commit)
			rdma_alloc_commit_uobject(uobj, attrs);
		अन्यथा
			rdma_alloc_पात_uobject(uobj, attrs, hw_obj_valid);
		अवरोध;
	शेष:
		WARN_ON(true);
	पूर्ण
पूर्ण
