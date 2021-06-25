<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/*
 * Copyright (c) 2017, Mellanox Technologies inc.  All rights reserved.
 */

#अगर_अघोषित _UVERBS_TYPES_
#घोषणा _UVERBS_TYPES_

#समावेश <linux/kernel.h>
#समावेश <rdma/ib_verbs.h>

काष्ठा uverbs_obj_type;
काष्ठा uverbs_api_object;

क्रमागत rdma_lookup_mode अणु
	UVERBS_LOOKUP_READ,
	UVERBS_LOOKUP_WRITE,
	/*
	 * Destroy is like LOOKUP_WRITE, except that the uobject is not
	 * locked.  uobj_destroy is used to convert a LOOKUP_DESTROY lock पूर्णांकo
	 * a LOOKUP_WRITE lock.
	 */
	UVERBS_LOOKUP_DESTROY,
पूर्ण;

/*
 * The following sequences are valid:
 * Success flow:
 *   alloc_begin
 *   alloc_commit
 *    [..]
 * Access flow:
 *   lookup_get(exclusive=false) & uverbs_try_lock_object
 *   lookup_put(exclusive=false) via rdma_lookup_put_uobject
 * Deकाष्ठाion flow:
 *   lookup_get(exclusive=true) & uverbs_try_lock_object
 *   हटाओ_commit
 *   हटाओ_handle (optional)
 *   lookup_put(exclusive=true) via rdma_lookup_put_uobject
 *
 * Allocate Error flow #1
 *   alloc_begin
 *   alloc_पात
 * Allocate Error flow #2
 *   alloc_begin
 *   हटाओ_commit
 *   alloc_पात
 * Allocate Error flow #3
 *   alloc_begin
 *   alloc_commit (fails)
 *   हटाओ_commit
 *   alloc_पात
 *
 * In all हालs the caller must hold the ufile kref until alloc_commit or
 * alloc_पात वापसs.
 */
काष्ठा uverbs_obj_type_class अणु
	काष्ठा ib_uobject *(*alloc_begin)(स्थिर काष्ठा uverbs_api_object *obj,
					  काष्ठा uverbs_attr_bundle *attrs);
	/* This consumes the kref on uobj */
	व्योम (*alloc_commit)(काष्ठा ib_uobject *uobj);
	/* This करोes not consume the kref on uobj */
	व्योम (*alloc_पात)(काष्ठा ib_uobject *uobj);

	काष्ठा ib_uobject *(*lookup_get)(स्थिर काष्ठा uverbs_api_object *obj,
					 काष्ठा ib_uverbs_file *ufile, s64 id,
					 क्रमागत rdma_lookup_mode mode);
	व्योम (*lookup_put)(काष्ठा ib_uobject *uobj, क्रमागत rdma_lookup_mode mode);
	/* This करोes not consume the kref on uobj */
	पूर्णांक __must_check (*destroy_hw)(काष्ठा ib_uobject *uobj,
				       क्रमागत rdma_हटाओ_reason why,
				       काष्ठा uverbs_attr_bundle *attrs);
	व्योम (*हटाओ_handle)(काष्ठा ib_uobject *uobj);
	व्योम (*swap_uobjects)(काष्ठा ib_uobject *obj_old,
			      काष्ठा ib_uobject *obj_new);
पूर्ण;

काष्ठा uverbs_obj_type अणु
	स्थिर काष्ठा uverbs_obj_type_class * स्थिर type_class;
	माप_प्रकार	     obj_size;
पूर्ण;

/*
 * Objects type classes which support a detach state (object is still alive but
 * it's not attached to any context need to make sure:
 * (a) no call through to a driver after a detach is called
 * (b) detach isn't called concurrently with context_cleanup
 */

काष्ठा uverbs_obj_idr_type अणु
	/*
	 * In idr based objects, uverbs_obj_type_class poपूर्णांकs to a generic
	 * idr operations. In order to specialize the underlying types (e.g. CQ,
	 * QPs, etc.), we add destroy_object specअगरic callbacks.
	 */
	काष्ठा uverbs_obj_type  type;

	/* Free driver resources from the uobject, make the driver uncallable,
	 * and move the uobject to the detached state. If the object was
	 * destroyed by the user's request, a failure should leave the uobject
	 * completely unchanged.
	 */
	पूर्णांक __must_check (*destroy_object)(काष्ठा ib_uobject *uobj,
					   क्रमागत rdma_हटाओ_reason why,
					   काष्ठा uverbs_attr_bundle *attrs);
पूर्ण;

काष्ठा ib_uobject *rdma_lookup_get_uobject(स्थिर काष्ठा uverbs_api_object *obj,
					   काष्ठा ib_uverbs_file *ufile, s64 id,
					   क्रमागत rdma_lookup_mode mode,
					   काष्ठा uverbs_attr_bundle *attrs);
व्योम rdma_lookup_put_uobject(काष्ठा ib_uobject *uobj,
			     क्रमागत rdma_lookup_mode mode);
काष्ठा ib_uobject *rdma_alloc_begin_uobject(स्थिर काष्ठा uverbs_api_object *obj,
					    काष्ठा uverbs_attr_bundle *attrs);
व्योम rdma_alloc_पात_uobject(काष्ठा ib_uobject *uobj,
			      काष्ठा uverbs_attr_bundle *attrs,
			      bool hw_obj_valid);
व्योम rdma_alloc_commit_uobject(काष्ठा ib_uobject *uobj,
			       काष्ठा uverbs_attr_bundle *attrs);
व्योम rdma_assign_uobject(काष्ठा ib_uobject *to_uobj,
			 काष्ठा ib_uobject *new_uobj,
			 काष्ठा uverbs_attr_bundle *attrs);

/*
 * uverbs_uobject_get is called in order to increase the reference count on
 * an uobject. This is useful when a handler wants to keep the uobject's memory
 * alive, regardless अगर this uobject is still alive in the context's objects
 * repository. Objects are put via uverbs_uobject_put.
 */
अटल अंतरभूत व्योम uverbs_uobject_get(काष्ठा ib_uobject *uobject)
अणु
	kref_get(&uobject->ref);
पूर्ण
व्योम uverbs_uobject_put(काष्ठा ib_uobject *uobject);

काष्ठा uverbs_obj_fd_type अणु
	/*
	 * In fd based objects, uverbs_obj_type_ops poपूर्णांकs to generic
	 * fd operations. In order to specialize the underlying types (e.g.
	 * completion_channel), we use fops, name and flags क्रम fd creation.
	 * destroy_object is called when the uobject is to be destroyed,
	 * because the driver is हटाओd or the FD is बंदd.
	 */
	काष्ठा uverbs_obj_type  type;
	व्योम (*destroy_object)(काष्ठा ib_uobject *uobj,
			       क्रमागत rdma_हटाओ_reason why);
	स्थिर काष्ठा file_operations	*fops;
	स्थिर अक्षर			*name;
	पूर्णांक				flags;
पूर्ण;

बाह्य स्थिर काष्ठा uverbs_obj_type_class uverbs_idr_class;
बाह्य स्थिर काष्ठा uverbs_obj_type_class uverbs_fd_class;
पूर्णांक uverbs_uobject_fd_release(काष्ठा inode *inode, काष्ठा file *filp);

#घोषणा UVERBS_BUILD_BUG_ON(cond) (माप(अक्षर[1 - 2 * !!(cond)]) -	\
				   माप(अक्षर))
#घोषणा UVERBS_TYPE_ALLOC_FD(_obj_size, _destroy_object, _fops, _name, _flags) \
	((&((स्थिर काष्ठा uverbs_obj_fd_type)				\
	 अणु.type = अणु							\
		.type_class = &uverbs_fd_class,				\
		.obj_size = (_obj_size) +				\
			UVERBS_BUILD_BUG_ON((_obj_size) <               \
					    माप(काष्ठा ib_uobject)), \
	 पूर्ण,								\
	 .destroy_object = _destroy_object,				\
	 .fops = _fops,							\
	 .name = _name,							\
	 .flags = _flagsपूर्ण))->type)
#घोषणा UVERBS_TYPE_ALLOC_IDR_SZ(_size, _destroy_object)	\
	((&((स्थिर काष्ठा uverbs_obj_idr_type)				\
	 अणु.type = अणु							\
		.type_class = &uverbs_idr_class,			\
		.obj_size = (_size) +					\
			UVERBS_BUILD_BUG_ON((_size) <			\
					    माप(काष्ठा ib_uobject))	\
	 पूर्ण,								\
	 .destroy_object = _destroy_object,पूर्ण))->type)
#घोषणा UVERBS_TYPE_ALLOC_IDR(_destroy_object)			\
	 UVERBS_TYPE_ALLOC_IDR_SZ(माप(काष्ठा ib_uobject),	\
				  _destroy_object)

#पूर्ण_अगर
