<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/*
 * Copyright (c) 2017, Mellanox Technologies inc.  All rights reserved.
 */

#अगर_अघोषित _UVERBS_STD_TYPES__
#घोषणा _UVERBS_STD_TYPES__

#समावेश <rdma/uverbs_types.h>
#समावेश <rdma/uverbs_ioctl.h>
#समावेश <rdma/ib_user_ioctl_verbs.h>

/* Returns _id, or causes a compile error अगर _id is not a u32.
 *
 * The uobj APIs should only be used with the ग_लिखो based uAPI to access
 * object IDs. The ग_लिखो API must use a u32 क्रम the object handle, which is
 * checked by this macro.
 */
#घोषणा _uobj_check_id(_id) ((_id) * typecheck(u32, _id))

#घोषणा uobj_get_type(_attrs, _object)                                         \
	uapi_get_object((_attrs)->ufile->device->uapi, _object)

#घोषणा uobj_get_पढ़ो(_type, _id, _attrs)                                      \
	rdma_lookup_get_uobject(uobj_get_type(_attrs, _type), (_attrs)->ufile, \
				_uobj_check_id(_id), UVERBS_LOOKUP_READ,       \
				_attrs)

#घोषणा ufd_get_पढ़ो(_type, _fdnum, _attrs)                                    \
	rdma_lookup_get_uobject(uobj_get_type(_attrs, _type), (_attrs)->ufile, \
				(_fdnum)*typecheck(s32, _fdnum),               \
				UVERBS_LOOKUP_READ, _attrs)

अटल अंतरभूत व्योम *_uobj_get_obj_पढ़ो(काष्ठा ib_uobject *uobj)
अणु
	अगर (IS_ERR(uobj))
		वापस शून्य;
	वापस uobj->object;
पूर्ण
#घोषणा uobj_get_obj_पढ़ो(_object, _type, _id, _attrs)                         \
	((काष्ठा ib_##_object *)_uobj_get_obj_पढ़ो(                            \
		uobj_get_पढ़ो(_type, _id, _attrs)))

#घोषणा uobj_get_ग_लिखो(_type, _id, _attrs)                                     \
	rdma_lookup_get_uobject(uobj_get_type(_attrs, _type), (_attrs)->ufile, \
				_uobj_check_id(_id), UVERBS_LOOKUP_WRITE,      \
				_attrs)

पूर्णांक __uobj_perक्रमm_destroy(स्थिर काष्ठा uverbs_api_object *obj, u32 id,
			   काष्ठा uverbs_attr_bundle *attrs);
#घोषणा uobj_perक्रमm_destroy(_type, _id, _attrs)                               \
	__uobj_perक्रमm_destroy(uobj_get_type(_attrs, _type),                   \
			       _uobj_check_id(_id), _attrs)

काष्ठा ib_uobject *__uobj_get_destroy(स्थिर काष्ठा uverbs_api_object *obj,
				      u32 id, काष्ठा uverbs_attr_bundle *attrs);

#घोषणा uobj_get_destroy(_type, _id, _attrs)                                   \
	__uobj_get_destroy(uobj_get_type(_attrs, _type), _uobj_check_id(_id),  \
			   _attrs)

अटल अंतरभूत व्योम uobj_put_destroy(काष्ठा ib_uobject *uobj)
अणु
	rdma_lookup_put_uobject(uobj, UVERBS_LOOKUP_DESTROY);
पूर्ण

अटल अंतरभूत व्योम uobj_put_पढ़ो(काष्ठा ib_uobject *uobj)
अणु
	rdma_lookup_put_uobject(uobj, UVERBS_LOOKUP_READ);
पूर्ण

#घोषणा uobj_put_obj_पढ़ो(_obj)					\
	uobj_put_पढ़ो((_obj)->uobject)

अटल अंतरभूत व्योम uobj_put_ग_लिखो(काष्ठा ib_uobject *uobj)
अणु
	rdma_lookup_put_uobject(uobj, UVERBS_LOOKUP_WRITE);
पूर्ण

अटल अंतरभूत व्योम uobj_alloc_पात(काष्ठा ib_uobject *uobj,
				    काष्ठा uverbs_attr_bundle *attrs)
अणु
	rdma_alloc_पात_uobject(uobj, attrs, false);
पूर्ण

अटल अंतरभूत व्योम uobj_finalize_uobj_create(काष्ठा ib_uobject *uobj,
					     काष्ठा uverbs_attr_bundle *attrs)
अणु
	/*
	 * Tell the core code that the ग_लिखो() handler has completed
	 * initializing the object and that the core should commit or
	 * पात this object based upon the वापस code from the ग_लिखो()
	 * method. Similar to what uverbs_finalize_uobj_create() करोes क्रम
	 * ioctl()
	 */
	WARN_ON(attrs->uobject);
	attrs->uobject = uobj;
पूर्ण

अटल अंतरभूत काष्ठा ib_uobject *
__uobj_alloc(स्थिर काष्ठा uverbs_api_object *obj,
	     काष्ठा uverbs_attr_bundle *attrs, काष्ठा ib_device **ib_dev)
अणु
	काष्ठा ib_uobject *uobj = rdma_alloc_begin_uobject(obj, attrs);

	अगर (!IS_ERR(uobj))
		*ib_dev = attrs->context->device;
	वापस uobj;
पूर्ण

#घोषणा uobj_alloc(_type, _attrs, _ib_dev)                                     \
	__uobj_alloc(uobj_get_type(_attrs, _type), _attrs, _ib_dev)

अटल अंतरभूत व्योम uverbs_flow_action_fill_action(काष्ठा ib_flow_action *action,
						  काष्ठा ib_uobject *uobj,
						  काष्ठा ib_device *ib_dev,
						  क्रमागत ib_flow_action_type type)
अणु
	atomic_set(&action->usecnt, 0);
	action->device = ib_dev;
	action->type = type;
	action->uobject = uobj;
	uobj->object = action;
पूर्ण

काष्ठा ib_uflow_resources अणु
	माप_प्रकार			max;
	माप_प्रकार			num;
	माप_प्रकार			collection_num;
	माप_प्रकार			counters_num;
	काष्ठा ib_counters	**counters;
	काष्ठा ib_flow_action	**collection;
पूर्ण;

काष्ठा ib_uflow_object अणु
	काष्ठा ib_uobject		uobject;
	काष्ठा ib_uflow_resources	*resources;
पूर्ण;

काष्ठा ib_uflow_resources *flow_resources_alloc(माप_प्रकार num_specs);
व्योम flow_resources_add(काष्ठा ib_uflow_resources *uflow_res,
			क्रमागत ib_flow_spec_type type,
			व्योम *ibobj);
व्योम ib_uverbs_flow_resources_मुक्त(काष्ठा ib_uflow_resources *uflow_res);

अटल अंतरभूत व्योम ib_set_flow(काष्ठा ib_uobject *uobj, काष्ठा ib_flow *ibflow,
			       काष्ठा ib_qp *qp, काष्ठा ib_device *device,
			       काष्ठा ib_uflow_resources *uflow_res)
अणु
	काष्ठा ib_uflow_object *uflow;

	uobj->object = ibflow;
	ibflow->uobject = uobj;

	अगर (qp) अणु
		atomic_inc(&qp->usecnt);
		ibflow->qp = qp;
	पूर्ण

	ibflow->device = device;
	uflow = container_of(uobj, typeof(*uflow), uobject);
	uflow->resources = uflow_res;
पूर्ण

काष्ठा uverbs_api_object अणु
	स्थिर काष्ठा uverbs_obj_type *type_attrs;
	स्थिर काष्ठा uverbs_obj_type_class *type_class;
	u8 disabled:1;
	u32 id;
पूर्ण;

अटल अंतरभूत u32 uobj_get_object_id(काष्ठा ib_uobject *uobj)
अणु
	वापस uobj->uapi_object->id;
पूर्ण

#पूर्ण_अगर

