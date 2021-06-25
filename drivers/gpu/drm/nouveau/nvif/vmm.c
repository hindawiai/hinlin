<शैली गुरु>
/*
 * Copyright 2017 Red Hat Inc.
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
#समावेश <nvअगर/vmm.h>
#समावेश <nvअगर/स्मृति.स>

#समावेश <nvअगर/अगर000c.h>

पूर्णांक
nvअगर_vmm_unmap(काष्ठा nvअगर_vmm *vmm, u64 addr)
अणु
	वापस nvअगर_object_mthd(&vmm->object, NVIF_VMM_V0_UNMAP,
				&(काष्ठा nvअगर_vmm_unmap_v0) अणु .addr = addr पूर्ण,
				माप(काष्ठा nvअगर_vmm_unmap_v0));
पूर्ण

पूर्णांक
nvअगर_vmm_map(काष्ठा nvअगर_vmm *vmm, u64 addr, u64 size, व्योम *argv, u32 argc,
	     काष्ठा nvअगर_mem *mem, u64 offset)
अणु
	काष्ठा nvअगर_vmm_map_v0 *args;
	u8 stack[48];
	पूर्णांक ret;

	अगर (माप(*args) + argc > माप(stack)) अणु
		अगर (!(args = kदो_स्मृति(माप(*args) + argc, GFP_KERNEL)))
			वापस -ENOMEM;
	पूर्ण अन्यथा अणु
		args = (व्योम *)stack;
	पूर्ण

	args->version = 0;
	args->addr = addr;
	args->size = size;
	args->memory = nvअगर_handle(&mem->object);
	args->offset = offset;
	स_नकल(args->data, argv, argc);

	ret = nvअगर_object_mthd(&vmm->object, NVIF_VMM_V0_MAP,
			       args, माप(*args) + argc);
	अगर (args != (व्योम *)stack)
		kमुक्त(args);
	वापस ret;
पूर्ण

व्योम
nvअगर_vmm_put(काष्ठा nvअगर_vmm *vmm, काष्ठा nvअगर_vma *vma)
अणु
	अगर (vma->size) अणु
		WARN_ON(nvअगर_object_mthd(&vmm->object, NVIF_VMM_V0_PUT,
					 &(काष्ठा nvअगर_vmm_put_v0) अणु
						.addr = vma->addr,
					 पूर्ण, माप(काष्ठा nvअगर_vmm_put_v0)));
		vma->size = 0;
	पूर्ण
पूर्ण

पूर्णांक
nvअगर_vmm_get(काष्ठा nvअगर_vmm *vmm, क्रमागत nvअगर_vmm_get type, bool sparse,
	     u8 page, u8 align, u64 size, काष्ठा nvअगर_vma *vma)
अणु
	काष्ठा nvअगर_vmm_get_v0 args;
	पूर्णांक ret;

	args.version = vma->size = 0;
	args.sparse = sparse;
	args.page = page;
	args.align = align;
	args.size = size;

	चयन (type) अणु
	हाल ADDR: args.type = NVIF_VMM_GET_V0_ADDR; अवरोध;
	हाल PTES: args.type = NVIF_VMM_GET_V0_PTES; अवरोध;
	हाल LAZY: args.type = NVIF_VMM_GET_V0_LAZY; अवरोध;
	शेष:
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण

	ret = nvअगर_object_mthd(&vmm->object, NVIF_VMM_V0_GET,
			       &args, माप(args));
	अगर (ret == 0) अणु
		vma->addr = args.addr;
		vma->size = args.size;
	पूर्ण
	वापस ret;
पूर्ण

व्योम
nvअगर_vmm_dtor(काष्ठा nvअगर_vmm *vmm)
अणु
	kमुक्त(vmm->page);
	nvअगर_object_dtor(&vmm->object);
पूर्ण

पूर्णांक
nvअगर_vmm_ctor(काष्ठा nvअगर_mmu *mmu, स्थिर अक्षर *name, s32 oclass, bool managed,
	      u64 addr, u64 size, व्योम *argv, u32 argc, काष्ठा nvअगर_vmm *vmm)
अणु
	काष्ठा nvअगर_vmm_v0 *args;
	u32 argn = माप(*args) + argc;
	पूर्णांक ret = -ENOSYS, i;

	vmm->object.client = शून्य;
	vmm->page = शून्य;

	अगर (!(args = kदो_स्मृति(argn, GFP_KERNEL)))
		वापस -ENOMEM;
	args->version = 0;
	args->managed = managed;
	args->addr = addr;
	args->size = size;
	स_नकल(args->data, argv, argc);

	ret = nvअगर_object_ctor(&mmu->object, name ? name : "nvifVmm", 0,
			       oclass, args, argn, &vmm->object);
	अगर (ret)
		जाओ करोne;

	vmm->start = args->addr;
	vmm->limit = args->size;

	vmm->page_nr = args->page_nr;
	vmm->page = kदो_स्मृति_array(vmm->page_nr, माप(*vmm->page),
				  GFP_KERNEL);
	अगर (!vmm->page) अणु
		ret = -ENOMEM;
		जाओ करोne;
	पूर्ण

	क्रम (i = 0; i < vmm->page_nr; i++) अणु
		काष्ठा nvअगर_vmm_page_v0 args = अणु .index = i पूर्ण;

		ret = nvअगर_object_mthd(&vmm->object, NVIF_VMM_V0_PAGE,
				       &args, माप(args));
		अगर (ret)
			अवरोध;

		vmm->page[i].shअगरt = args.shअगरt;
		vmm->page[i].sparse = args.sparse;
		vmm->page[i].vram = args.vram;
		vmm->page[i].host = args.host;
		vmm->page[i].comp = args.comp;
	पूर्ण

करोne:
	अगर (ret)
		nvअगर_vmm_dtor(vmm);
	kमुक्त(args);
	वापस ret;
पूर्ण
