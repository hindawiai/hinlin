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
 */
#समावेश <core/ramht.h>
#समावेश <core/engine.h>
#समावेश <core/object.h>

अटल u32
nvkm_ramht_hash(काष्ठा nvkm_ramht *ramht, पूर्णांक chid, u32 handle)
अणु
	u32 hash = 0;

	जबतक (handle) अणु
		hash ^= (handle & ((1 << ramht->bits) - 1));
		handle >>= ramht->bits;
	पूर्ण

	hash ^= chid << (ramht->bits - 4);
	वापस hash;
पूर्ण

काष्ठा nvkm_gpuobj *
nvkm_ramht_search(काष्ठा nvkm_ramht *ramht, पूर्णांक chid, u32 handle)
अणु
	u32 co, ho;

	co = ho = nvkm_ramht_hash(ramht, chid, handle);
	करो अणु
		अगर (ramht->data[co].chid == chid) अणु
			अगर (ramht->data[co].handle == handle)
				वापस ramht->data[co].inst;
		पूर्ण

		अगर (++co >= ramht->size)
			co = 0;
	पूर्ण जबतक (co != ho);

	वापस शून्य;
पूर्ण

अटल पूर्णांक
nvkm_ramht_update(काष्ठा nvkm_ramht *ramht, पूर्णांक co, काष्ठा nvkm_object *object,
		  पूर्णांक chid, पूर्णांक addr, u32 handle, u32 context)
अणु
	काष्ठा nvkm_ramht_data *data = &ramht->data[co];
	u64 inst = 0x00000040; /* just non-zero क्रम <=g8x fअगरo ramht */
	पूर्णांक ret;

	nvkm_gpuobj_del(&data->inst);
	data->chid = chid;
	data->handle = handle;

	अगर (object) अणु
		ret = nvkm_object_bind(object, ramht->parent, 16, &data->inst);
		अगर (ret) अणु
			अगर (ret != -ENODEV) अणु
				data->chid = -1;
				वापस ret;
			पूर्ण
			data->inst = शून्य;
		पूर्ण

		अगर (data->inst) अणु
			अगर (ramht->device->card_type >= NV_50)
				inst = data->inst->node->offset;
			अन्यथा
				inst = data->inst->addr;
		पूर्ण

		अगर (addr < 0) context |= inst << -addr;
		अन्यथा          context |= inst >>  addr;
	पूर्ण

	nvkm_kmap(ramht->gpuobj);
	nvkm_wo32(ramht->gpuobj, (co << 3) + 0, handle);
	nvkm_wo32(ramht->gpuobj, (co << 3) + 4, context);
	nvkm_करोne(ramht->gpuobj);
	वापस co + 1;
पूर्ण

व्योम
nvkm_ramht_हटाओ(काष्ठा nvkm_ramht *ramht, पूर्णांक cookie)
अणु
	अगर (--cookie >= 0)
		nvkm_ramht_update(ramht, cookie, शून्य, -1, 0, 0, 0);
पूर्ण

पूर्णांक
nvkm_ramht_insert(काष्ठा nvkm_ramht *ramht, काष्ठा nvkm_object *object,
		  पूर्णांक chid, पूर्णांक addr, u32 handle, u32 context)
अणु
	u32 co, ho;

	अगर (nvkm_ramht_search(ramht, chid, handle))
		वापस -EEXIST;

	co = ho = nvkm_ramht_hash(ramht, chid, handle);
	करो अणु
		अगर (ramht->data[co].chid < 0) अणु
			वापस nvkm_ramht_update(ramht, co, object, chid,
						 addr, handle, context);
		पूर्ण

		अगर (++co >= ramht->size)
			co = 0;
	पूर्ण जबतक (co != ho);

	वापस -ENOSPC;
पूर्ण

व्योम
nvkm_ramht_del(काष्ठा nvkm_ramht **pramht)
अणु
	काष्ठा nvkm_ramht *ramht = *pramht;
	अगर (ramht) अणु
		nvkm_gpuobj_del(&ramht->gpuobj);
		vमुक्त(*pramht);
		*pramht = शून्य;
	पूर्ण
पूर्ण

पूर्णांक
nvkm_ramht_new(काष्ठा nvkm_device *device, u32 size, u32 align,
	       काष्ठा nvkm_gpuobj *parent, काष्ठा nvkm_ramht **pramht)
अणु
	काष्ठा nvkm_ramht *ramht;
	पूर्णांक ret, i;

	अगर (!(ramht = *pramht = vzalloc(काष्ठा_size(ramht, data, (size >> 3)))))
		वापस -ENOMEM;

	ramht->device = device;
	ramht->parent = parent;
	ramht->size = size >> 3;
	ramht->bits = order_base_2(ramht->size);
	क्रम (i = 0; i < ramht->size; i++)
		ramht->data[i].chid = -1;

	ret = nvkm_gpuobj_new(ramht->device, size, align, true,
			      ramht->parent, &ramht->gpuobj);
	अगर (ret)
		nvkm_ramht_del(pramht);
	वापस ret;
पूर्ण
