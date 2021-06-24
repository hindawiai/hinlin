<शैली गुरु>
/*
 * Copyright 2012 Red Hat Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Ben Skeggs
 */
#समावेश <core/object.h>
#समावेश <core/client.h>
#समावेश <core/engine.h>

काष्ठा nvkm_object *
nvkm_object_search(काष्ठा nvkm_client *client, u64 handle,
		   स्थिर काष्ठा nvkm_object_func *func)
अणु
	काष्ठा nvkm_object *object;

	अगर (handle) अणु
		काष्ठा rb_node *node = client->objroot.rb_node;
		जबतक (node) अणु
			object = rb_entry(node, typeof(*object), node);
			अगर (handle < object->object)
				node = node->rb_left;
			अन्यथा
			अगर (handle > object->object)
				node = node->rb_right;
			अन्यथा
				जाओ करोne;
		पूर्ण
		वापस ERR_PTR(-ENOENT);
	पूर्ण अन्यथा अणु
		object = &client->object;
	पूर्ण

करोne:
	अगर (unlikely(func && object->func != func))
		वापस ERR_PTR(-EINVAL);
	वापस object;
पूर्ण

व्योम
nvkm_object_हटाओ(काष्ठा nvkm_object *object)
अणु
	अगर (!RB_EMPTY_NODE(&object->node))
		rb_erase(&object->node, &object->client->objroot);
पूर्ण

bool
nvkm_object_insert(काष्ठा nvkm_object *object)
अणु
	काष्ठा rb_node **ptr = &object->client->objroot.rb_node;
	काष्ठा rb_node *parent = शून्य;

	जबतक (*ptr) अणु
		काष्ठा nvkm_object *this = rb_entry(*ptr, typeof(*this), node);
		parent = *ptr;
		अगर (object->object < this->object)
			ptr = &parent->rb_left;
		अन्यथा
		अगर (object->object > this->object)
			ptr = &parent->rb_right;
		अन्यथा
			वापस false;
	पूर्ण

	rb_link_node(&object->node, parent, ptr);
	rb_insert_color(&object->node, &object->client->objroot);
	वापस true;
पूर्ण

पूर्णांक
nvkm_object_mthd(काष्ठा nvkm_object *object, u32 mthd, व्योम *data, u32 size)
अणु
	अगर (likely(object->func->mthd))
		वापस object->func->mthd(object, mthd, data, size);
	वापस -ENODEV;
पूर्ण

पूर्णांक
nvkm_object_ntfy(काष्ठा nvkm_object *object, u32 mthd,
		 काष्ठा nvkm_event **pevent)
अणु
	अगर (likely(object->func->ntfy))
		वापस object->func->ntfy(object, mthd, pevent);
	वापस -ENODEV;
पूर्ण

पूर्णांक
nvkm_object_map(काष्ठा nvkm_object *object, व्योम *argv, u32 argc,
		क्रमागत nvkm_object_map *type, u64 *addr, u64 *size)
अणु
	अगर (likely(object->func->map))
		वापस object->func->map(object, argv, argc, type, addr, size);
	वापस -ENODEV;
पूर्ण

पूर्णांक
nvkm_object_unmap(काष्ठा nvkm_object *object)
अणु
	अगर (likely(object->func->unmap))
		वापस object->func->unmap(object);
	वापस -ENODEV;
पूर्ण

पूर्णांक
nvkm_object_rd08(काष्ठा nvkm_object *object, u64 addr, u8 *data)
अणु
	अगर (likely(object->func->rd08))
		वापस object->func->rd08(object, addr, data);
	वापस -ENODEV;
पूर्ण

पूर्णांक
nvkm_object_rd16(काष्ठा nvkm_object *object, u64 addr, u16 *data)
अणु
	अगर (likely(object->func->rd16))
		वापस object->func->rd16(object, addr, data);
	वापस -ENODEV;
पूर्ण

पूर्णांक
nvkm_object_rd32(काष्ठा nvkm_object *object, u64 addr, u32 *data)
अणु
	अगर (likely(object->func->rd32))
		वापस object->func->rd32(object, addr, data);
	वापस -ENODEV;
पूर्ण

पूर्णांक
nvkm_object_wr08(काष्ठा nvkm_object *object, u64 addr, u8 data)
अणु
	अगर (likely(object->func->wr08))
		वापस object->func->wr08(object, addr, data);
	वापस -ENODEV;
पूर्ण

पूर्णांक
nvkm_object_wr16(काष्ठा nvkm_object *object, u64 addr, u16 data)
अणु
	अगर (likely(object->func->wr16))
		वापस object->func->wr16(object, addr, data);
	वापस -ENODEV;
पूर्ण

पूर्णांक
nvkm_object_wr32(काष्ठा nvkm_object *object, u64 addr, u32 data)
अणु
	अगर (likely(object->func->wr32))
		वापस object->func->wr32(object, addr, data);
	वापस -ENODEV;
पूर्ण

पूर्णांक
nvkm_object_bind(काष्ठा nvkm_object *object, काष्ठा nvkm_gpuobj *gpuobj,
		 पूर्णांक align, काष्ठा nvkm_gpuobj **pgpuobj)
अणु
	अगर (object->func->bind)
		वापस object->func->bind(object, gpuobj, align, pgpuobj);
	वापस -ENODEV;
पूर्ण

पूर्णांक
nvkm_object_fini(काष्ठा nvkm_object *object, bool suspend)
अणु
	स्थिर अक्षर *action = suspend ? "suspend" : "fini";
	काष्ठा nvkm_object *child;
	s64 समय;
	पूर्णांक ret;

	nvअगर_debug(object, "%s children...\n", action);
	समय = kसमय_प्रकारo_us(kसमय_get());
	list_क्रम_each_entry(child, &object->tree, head) अणु
		ret = nvkm_object_fini(child, suspend);
		अगर (ret && suspend)
			जाओ fail_child;
	पूर्ण

	nvअगर_debug(object, "%s running...\n", action);
	अगर (object->func->fini) अणु
		ret = object->func->fini(object, suspend);
		अगर (ret) अणु
			nvअगर_error(object, "%s failed with %d\n", action, ret);
			अगर (suspend)
				जाओ fail;
		पूर्ण
	पूर्ण

	समय = kसमय_प्रकारo_us(kसमय_get()) - समय;
	nvअगर_debug(object, "%s completed in %lldus\n", action, समय);
	वापस 0;

fail:
	अगर (object->func->init) अणु
		पूर्णांक rret = object->func->init(object);
		अगर (rret)
			nvअगर_fatal(object, "failed to restart, %d\n", rret);
	पूर्ण
fail_child:
	list_क्रम_each_entry_जारी_reverse(child, &object->tree, head) अणु
		nvkm_object_init(child);
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक
nvkm_object_init(काष्ठा nvkm_object *object)
अणु
	काष्ठा nvkm_object *child;
	s64 समय;
	पूर्णांक ret;

	nvअगर_debug(object, "init running...\n");
	समय = kसमय_प्रकारo_us(kसमय_get());
	अगर (object->func->init) अणु
		ret = object->func->init(object);
		अगर (ret)
			जाओ fail;
	पूर्ण

	nvअगर_debug(object, "init children...\n");
	list_क्रम_each_entry(child, &object->tree, head) अणु
		ret = nvkm_object_init(child);
		अगर (ret)
			जाओ fail_child;
	पूर्ण

	समय = kसमय_प्रकारo_us(kसमय_get()) - समय;
	nvअगर_debug(object, "init completed in %lldus\n", समय);
	वापस 0;

fail_child:
	list_क्रम_each_entry_जारी_reverse(child, &object->tree, head)
		nvkm_object_fini(child, false);
fail:
	nvअगर_error(object, "init failed with %d\n", ret);
	अगर (object->func->fini)
		object->func->fini(object, false);
	वापस ret;
पूर्ण

व्योम *
nvkm_object_dtor(काष्ठा nvkm_object *object)
अणु
	काष्ठा nvkm_object *child, *ctemp;
	व्योम *data = object;
	s64 समय;

	nvअगर_debug(object, "destroy children...\n");
	समय = kसमय_प्रकारo_us(kसमय_get());
	list_क्रम_each_entry_safe(child, ctemp, &object->tree, head) अणु
		nvkm_object_del(&child);
	पूर्ण

	nvअगर_debug(object, "destroy running...\n");
	nvkm_object_unmap(object);
	अगर (object->func->dtor)
		data = object->func->dtor(object);
	nvkm_engine_unref(&object->engine);
	समय = kसमय_प्रकारo_us(kसमय_get()) - समय;
	nvअगर_debug(object, "destroy completed in %lldus...\n", समय);
	वापस data;
पूर्ण

व्योम
nvkm_object_del(काष्ठा nvkm_object **pobject)
अणु
	काष्ठा nvkm_object *object = *pobject;
	अगर (object && !WARN_ON(!object->func)) अणु
		*pobject = nvkm_object_dtor(object);
		nvkm_object_हटाओ(object);
		list_del(&object->head);
		kमुक्त(*pobject);
		*pobject = शून्य;
	पूर्ण
पूर्ण

व्योम
nvkm_object_ctor(स्थिर काष्ठा nvkm_object_func *func,
		 स्थिर काष्ठा nvkm_oclass *oclass, काष्ठा nvkm_object *object)
अणु
	object->func = func;
	object->client = oclass->client;
	object->engine = nvkm_engine_ref(oclass->engine);
	object->oclass = oclass->base.oclass;
	object->handle = oclass->handle;
	object->route  = oclass->route;
	object->token  = oclass->token;
	object->object = oclass->object;
	INIT_LIST_HEAD(&object->head);
	INIT_LIST_HEAD(&object->tree);
	RB_CLEAR_NODE(&object->node);
	WARN_ON(IS_ERR(object->engine));
पूर्ण

पूर्णांक
nvkm_object_new_(स्थिर काष्ठा nvkm_object_func *func,
		 स्थिर काष्ठा nvkm_oclass *oclass, व्योम *data, u32 size,
		 काष्ठा nvkm_object **pobject)
अणु
	अगर (size == 0) अणु
		अगर (!(*pobject = kzalloc(माप(**pobject), GFP_KERNEL)))
			वापस -ENOMEM;
		nvkm_object_ctor(func, oclass, *pobject);
		वापस 0;
	पूर्ण
	वापस -ENOSYS;
पूर्ण

अटल स्थिर काष्ठा nvkm_object_func
nvkm_object_func = अणु
पूर्ण;

पूर्णांक
nvkm_object_new(स्थिर काष्ठा nvkm_oclass *oclass, व्योम *data, u32 size,
		काष्ठा nvkm_object **pobject)
अणु
	स्थिर काष्ठा nvkm_object_func *func =
		oclass->base.func ? oclass->base.func : &nvkm_object_func;
	वापस nvkm_object_new_(func, oclass, data, size, pobject);
पूर्ण
