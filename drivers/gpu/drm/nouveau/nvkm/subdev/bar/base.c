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
#समावेश "priv.h"

व्योम
nvkm_bar_flush(काष्ठा nvkm_bar *bar)
अणु
	अगर (bar && bar->func->flush)
		bar->func->flush(bar);
पूर्ण

काष्ठा nvkm_vmm *
nvkm_bar_bar1_vmm(काष्ठा nvkm_device *device)
अणु
	वापस device->bar->func->bar1.vmm(device->bar);
पूर्ण

व्योम
nvkm_bar_bar1_reset(काष्ठा nvkm_device *device)
अणु
	काष्ठा nvkm_bar *bar = device->bar;
	अगर (bar) अणु
		bar->func->bar1.init(bar);
		bar->func->bar1.रुको(bar);
	पूर्ण
पूर्ण

काष्ठा nvkm_vmm *
nvkm_bar_bar2_vmm(काष्ठा nvkm_device *device)
अणु
	/* Denies access to BAR2 when it's not initialised, used by INSTMEM
	 * to know when object access needs to go through the BAR0 winकरोw.
	 */
	काष्ठा nvkm_bar *bar = device->bar;
	अगर (bar && bar->bar2)
		वापस bar->func->bar2.vmm(bar);
	वापस शून्य;
पूर्ण

व्योम
nvkm_bar_bar2_reset(काष्ठा nvkm_device *device)
अणु
	काष्ठा nvkm_bar *bar = device->bar;
	अगर (bar && bar->bar2) अणु
		bar->func->bar2.init(bar);
		bar->func->bar2.रुको(bar);
	पूर्ण
पूर्ण

व्योम
nvkm_bar_bar2_fini(काष्ठा nvkm_device *device)
अणु
	काष्ठा nvkm_bar *bar = device->bar;
	अगर (bar && bar->bar2) अणु
		bar->func->bar2.fini(bar);
		bar->bar2 = false;
	पूर्ण
पूर्ण

व्योम
nvkm_bar_bar2_init(काष्ठा nvkm_device *device)
अणु
	काष्ठा nvkm_bar *bar = device->bar;
	अगर (bar && bar->subdev.oneinit && !bar->bar2 && bar->func->bar2.init) अणु
		bar->func->bar2.init(bar);
		bar->func->bar2.रुको(bar);
		bar->bar2 = true;
	पूर्ण
पूर्ण

अटल पूर्णांक
nvkm_bar_fini(काष्ठा nvkm_subdev *subdev, bool suspend)
अणु
	काष्ठा nvkm_bar *bar = nvkm_bar(subdev);
	अगर (bar->func->bar1.fini)
		bar->func->bar1.fini(bar);
	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_bar_init(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_bar *bar = nvkm_bar(subdev);
	bar->func->bar1.init(bar);
	bar->func->bar1.रुको(bar);
	अगर (bar->func->init)
		bar->func->init(bar);
	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_bar_oneinit(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_bar *bar = nvkm_bar(subdev);
	वापस bar->func->oneinit(bar);
पूर्ण

अटल व्योम *
nvkm_bar_dtor(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_bar *bar = nvkm_bar(subdev);
	nvkm_bar_bar2_fini(subdev->device);
	वापस bar->func->dtor(bar);
पूर्ण

अटल स्थिर काष्ठा nvkm_subdev_func
nvkm_bar = अणु
	.dtor = nvkm_bar_dtor,
	.oneinit = nvkm_bar_oneinit,
	.init = nvkm_bar_init,
	.fini = nvkm_bar_fini,
पूर्ण;

व्योम
nvkm_bar_ctor(स्थिर काष्ठा nvkm_bar_func *func, काष्ठा nvkm_device *device,
	      क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_bar *bar)
अणु
	nvkm_subdev_ctor(&nvkm_bar, device, type, inst, &bar->subdev);
	bar->func = func;
	spin_lock_init(&bar->lock);
पूर्ण
