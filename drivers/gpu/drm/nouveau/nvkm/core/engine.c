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
#समावेश <core/engine.h>
#समावेश <core/device.h>
#समावेश <core/option.h>

#समावेश <subdev/fb.h>

bool
nvkm_engine_chsw_load(काष्ठा nvkm_engine *engine)
अणु
	अगर (engine->func->chsw_load)
		वापस engine->func->chsw_load(engine);
	वापस false;
पूर्ण

व्योम
nvkm_engine_unref(काष्ठा nvkm_engine **pengine)
अणु
	काष्ठा nvkm_engine *engine = *pengine;
	अगर (engine) अणु
		अगर (refcount_dec_and_mutex_lock(&engine->use.refcount, &engine->use.mutex)) अणु
			nvkm_subdev_fini(&engine->subdev, false);
			engine->use.enabled = false;
			mutex_unlock(&engine->use.mutex);
		पूर्ण
		*pengine = शून्य;
	पूर्ण
पूर्ण

काष्ठा nvkm_engine *
nvkm_engine_ref(काष्ठा nvkm_engine *engine)
अणु
	पूर्णांक ret;
	अगर (engine) अणु
		अगर (!refcount_inc_not_zero(&engine->use.refcount)) अणु
			mutex_lock(&engine->use.mutex);
			अगर (!refcount_inc_not_zero(&engine->use.refcount)) अणु
				engine->use.enabled = true;
				अगर ((ret = nvkm_subdev_init(&engine->subdev))) अणु
					engine->use.enabled = false;
					mutex_unlock(&engine->use.mutex);
					वापस ERR_PTR(ret);
				पूर्ण
				refcount_set(&engine->use.refcount, 1);
			पूर्ण
			mutex_unlock(&engine->use.mutex);
		पूर्ण
	पूर्ण
	वापस engine;
पूर्ण

व्योम
nvkm_engine_tile(काष्ठा nvkm_engine *engine, पूर्णांक region)
अणु
	काष्ठा nvkm_fb *fb = engine->subdev.device->fb;
	अगर (engine->func->tile)
		engine->func->tile(engine, region, &fb->tile.region[region]);
पूर्ण

अटल व्योम
nvkm_engine_पूर्णांकr(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_engine *engine = nvkm_engine(subdev);
	अगर (engine->func->पूर्णांकr)
		engine->func->पूर्णांकr(engine);
पूर्ण

अटल पूर्णांक
nvkm_engine_info(काष्ठा nvkm_subdev *subdev, u64 mthd, u64 *data)
अणु
	काष्ठा nvkm_engine *engine = nvkm_engine(subdev);
	अगर (engine->func->info) अणु
		अगर (!IS_ERR((engine = nvkm_engine_ref(engine)))) अणु
			पूर्णांक ret = engine->func->info(engine, mthd, data);
			nvkm_engine_unref(&engine);
			वापस ret;
		पूर्ण
		वापस PTR_ERR(engine);
	पूर्ण
	वापस -ENOSYS;
पूर्ण

अटल पूर्णांक
nvkm_engine_fini(काष्ठा nvkm_subdev *subdev, bool suspend)
अणु
	काष्ठा nvkm_engine *engine = nvkm_engine(subdev);
	अगर (engine->func->fini)
		वापस engine->func->fini(engine, suspend);
	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_engine_init(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_engine *engine = nvkm_engine(subdev);
	काष्ठा nvkm_fb *fb = subdev->device->fb;
	पूर्णांक ret = 0, i;
	s64 समय;

	अगर (!engine->use.enabled) अणु
		nvkm_trace(subdev, "init skipped, engine has no users\n");
		वापस ret;
	पूर्ण

	अगर (engine->func->oneinit && !engine->subdev.oneinit) अणु
		nvkm_trace(subdev, "one-time init running...\n");
		समय = kसमय_प्रकारo_us(kसमय_get());
		ret = engine->func->oneinit(engine);
		अगर (ret) अणु
			nvkm_trace(subdev, "one-time init failed, %d\n", ret);
			वापस ret;
		पूर्ण

		engine->subdev.oneinit = true;
		समय = kसमय_प्रकारo_us(kसमय_get()) - समय;
		nvkm_trace(subdev, "one-time init completed in %lldus\n", समय);
	पूर्ण

	अगर (engine->func->init)
		ret = engine->func->init(engine);

	क्रम (i = 0; fb && i < fb->tile.regions; i++)
		nvkm_engine_tile(engine, i);
	वापस ret;
पूर्ण

अटल पूर्णांक
nvkm_engine_preinit(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_engine *engine = nvkm_engine(subdev);
	अगर (engine->func->preinit)
		engine->func->preinit(engine);
	वापस 0;
पूर्ण

अटल व्योम *
nvkm_engine_dtor(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_engine *engine = nvkm_engine(subdev);
	अगर (engine->func->dtor)
		वापस engine->func->dtor(engine);
	mutex_destroy(&engine->use.mutex);
	वापस engine;
पूर्ण

स्थिर काष्ठा nvkm_subdev_func
nvkm_engine = अणु
	.dtor = nvkm_engine_dtor,
	.preinit = nvkm_engine_preinit,
	.init = nvkm_engine_init,
	.fini = nvkm_engine_fini,
	.info = nvkm_engine_info,
	.पूर्णांकr = nvkm_engine_पूर्णांकr,
पूर्ण;

पूर्णांक
nvkm_engine_ctor(स्थिर काष्ठा nvkm_engine_func *func, काष्ठा nvkm_device *device,
		 क्रमागत nvkm_subdev_type type, पूर्णांक inst, bool enable, काष्ठा nvkm_engine *engine)
अणु
	nvkm_subdev_ctor(&nvkm_engine, device, type, inst, &engine->subdev);
	engine->func = func;
	refcount_set(&engine->use.refcount, 0);
	mutex_init(&engine->use.mutex);

	अगर (!nvkm_boolopt(device->cfgopt, engine->subdev.name, enable)) अणु
		nvkm_debug(&engine->subdev, "disabled\n");
		वापस -ENODEV;
	पूर्ण

	spin_lock_init(&engine->lock);
	वापस 0;
पूर्ण

पूर्णांक
nvkm_engine_new_(स्थिर काष्ठा nvkm_engine_func *func, काष्ठा nvkm_device *device,
		 क्रमागत nvkm_subdev_type type, पूर्णांक inst, bool enable,
		 काष्ठा nvkm_engine **pengine)
अणु
	अगर (!(*pengine = kzalloc(माप(**pengine), GFP_KERNEL)))
		वापस -ENOMEM;
	वापस nvkm_engine_ctor(func, device, type, inst, enable, *pengine);
पूर्ण
