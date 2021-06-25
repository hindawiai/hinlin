<शैली गुरु>
/*
 * Copyright 2019 Red Hat Inc.
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
#समावेश "priv.h"

#समावेश <core/firmware.h>
#समावेश <core/memory.h>
#समावेश <subdev/mmu.h>

अटल काष्ठा nvkm_acr_hsf *
nvkm_acr_hsf_find(काष्ठा nvkm_acr *acr, स्थिर अक्षर *name)
अणु
	काष्ठा nvkm_acr_hsf *hsf;
	list_क्रम_each_entry(hsf, &acr->hsf, head) अणु
		अगर (!म_भेद(hsf->name, name))
			वापस hsf;
	पूर्ण
	वापस शून्य;
पूर्ण

पूर्णांक
nvkm_acr_hsf_boot(काष्ठा nvkm_acr *acr, स्थिर अक्षर *name)
अणु
	काष्ठा nvkm_subdev *subdev = &acr->subdev;
	काष्ठा nvkm_acr_hsf *hsf;
	पूर्णांक ret;

	hsf = nvkm_acr_hsf_find(acr, name);
	अगर (!hsf)
		वापस -EINVAL;

	nvkm_debug(subdev, "executing %s binary\n", hsf->name);
	ret = nvkm_falcon_get(hsf->falcon, subdev);
	अगर (ret)
		वापस ret;

	ret = hsf->func->boot(acr, hsf);
	nvkm_falcon_put(hsf->falcon, subdev);
	अगर (ret) अणु
		nvkm_error(subdev, "%s binary failed\n", hsf->name);
		वापस ret;
	पूर्ण

	nvkm_debug(subdev, "%s binary completed successfully\n", hsf->name);
	वापस 0;
पूर्ण

अटल व्योम
nvkm_acr_unload(काष्ठा nvkm_acr *acr)
अणु
	अगर (acr->करोne) अणु
		nvkm_acr_hsf_boot(acr, "unload");
		acr->करोne = false;
	पूर्ण
पूर्ण

अटल पूर्णांक
nvkm_acr_load(काष्ठा nvkm_acr *acr)
अणु
	काष्ठा nvkm_subdev *subdev = &acr->subdev;
	काष्ठा nvkm_acr_lsf *lsf;
	u64 start, limit;
	पूर्णांक ret;

	अगर (list_empty(&acr->lsf)) अणु
		nvkm_debug(subdev, "No LSF(s) present.\n");
		वापस 0;
	पूर्ण

	ret = acr->func->init(acr);
	अगर (ret)
		वापस ret;

	acr->func->wpr_check(acr, &start, &limit);

	अगर (start != acr->wpr_start || limit != acr->wpr_end) अणु
		nvkm_error(subdev, "WPR not configured as expected: "
				   "%016llx-%016llx vs %016llx-%016llx\n",
			   acr->wpr_start, acr->wpr_end, start, limit);
		वापस -EIO;
	पूर्ण

	acr->करोne = true;

	list_क्रम_each_entry(lsf, &acr->lsf, head) अणु
		अगर (lsf->func->boot) अणु
			ret = lsf->func->boot(lsf->falcon);
			अगर (ret)
				अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
nvkm_acr_reload(काष्ठा nvkm_acr *acr)
अणु
	nvkm_acr_unload(acr);
	वापस nvkm_acr_load(acr);
पूर्ण

अटल काष्ठा nvkm_acr_lsf *
nvkm_acr_falcon(काष्ठा nvkm_device *device)
अणु
	काष्ठा nvkm_acr *acr = device->acr;
	काष्ठा nvkm_acr_lsf *lsf;

	अगर (acr) अणु
		list_क्रम_each_entry(lsf, &acr->lsf, head) अणु
			अगर (lsf->func->bootstrap_falcon)
				वापस lsf;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

पूर्णांक
nvkm_acr_bootstrap_falcons(काष्ठा nvkm_device *device, अचिन्हित दीर्घ mask)
अणु
	काष्ठा nvkm_acr_lsf *acrflcn = nvkm_acr_falcon(device);
	काष्ठा nvkm_acr *acr = device->acr;
	अचिन्हित दीर्घ id;

	/* If there's no LS FW managing bootstrapping of other LS falcons,
	 * we depend on the HS firmware being able to करो it instead.
	 */
	अगर (!acrflcn) अणु
		/* Which isn't possible everywhere... */
		अगर ((mask & acr->func->bootstrap_falcons) == mask) अणु
			पूर्णांक ret = nvkm_acr_reload(acr);
			अगर (ret)
				वापस ret;

			वापस acr->करोne ? 0 : -EINVAL;
		पूर्ण
		वापस -ENOSYS;
	पूर्ण

	अगर ((mask & acrflcn->func->bootstrap_falcons) != mask)
		वापस -ENOSYS;

	अगर (acrflcn->func->bootstrap_multiple_falcons) अणु
		वापस acrflcn->func->
			bootstrap_multiple_falcons(acrflcn->falcon, mask);
	पूर्ण

	क्रम_each_set_bit(id, &mask, NVKM_ACR_LSF_NUM) अणु
		पूर्णांक ret = acrflcn->func->bootstrap_falcon(acrflcn->falcon, id);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

bool
nvkm_acr_managed_falcon(काष्ठा nvkm_device *device, क्रमागत nvkm_acr_lsf_id id)
अणु
	काष्ठा nvkm_acr *acr = device->acr;

	अगर (acr) अणु
		अगर (acr->managed_falcons & BIT_ULL(id))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक
nvkm_acr_fini(काष्ठा nvkm_subdev *subdev, bool suspend)
अणु
	nvkm_acr_unload(nvkm_acr(subdev));
	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_acr_init(काष्ठा nvkm_subdev *subdev)
अणु
	अगर (!nvkm_acr_falcon(subdev->device))
		वापस 0;

	वापस nvkm_acr_load(nvkm_acr(subdev));
पूर्ण

अटल व्योम
nvkm_acr_cleanup(काष्ठा nvkm_acr *acr)
अणु
	nvkm_acr_lsfw_del_all(acr);
	nvkm_acr_hsfw_del_all(acr);
	nvkm_firmware_put(acr->wpr_fw);
	acr->wpr_fw = शून्य;
पूर्ण

अटल पूर्णांक
nvkm_acr_oneinit(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_device *device = subdev->device;
	काष्ठा nvkm_acr *acr = nvkm_acr(subdev);
	काष्ठा nvkm_acr_hsfw *hsfw;
	काष्ठा nvkm_acr_lsfw *lsfw, *lsft;
	काष्ठा nvkm_acr_lsf *lsf;
	u32 wpr_size = 0;
	u64 falcons;
	पूर्णांक ret, i;

	अगर (list_empty(&acr->hsfw)) अणु
		nvkm_debug(subdev, "No HSFW(s)\n");
		nvkm_acr_cleanup(acr);
		वापस 0;
	पूर्ण

	/* Determine layout/size of WPR image up-front, as we need to know
	 * it to allocate memory beक्रमe we begin स्थिरructing it.
	 */
	list_क्रम_each_entry_safe(lsfw, lsft, &acr->lsfw, head) अणु
		/* Cull unknown falcons that are present in WPR image. */
		अगर (acr->wpr_fw) अणु
			अगर (!lsfw->func) अणु
				nvkm_acr_lsfw_del(lsfw);
				जारी;
			पूर्ण

			wpr_size = acr->wpr_fw->size;
		पूर्ण

		/* Ensure we've fetched falcon configuration. */
		ret = nvkm_falcon_get(lsfw->falcon, subdev);
		अगर (ret)
			वापस ret;

		nvkm_falcon_put(lsfw->falcon, subdev);

		अगर (!(lsf = kदो_स्मृति(माप(*lsf), GFP_KERNEL)))
			वापस -ENOMEM;
		lsf->func = lsfw->func;
		lsf->falcon = lsfw->falcon;
		lsf->id = lsfw->id;
		list_add_tail(&lsf->head, &acr->lsf);
		acr->managed_falcons |= BIT_ULL(lsf->id);
	पूर्ण

	/* Ensure the falcon that'll provide ACR functions is booted first. */
	lsf = nvkm_acr_falcon(device);
	अगर (lsf) अणु
		falcons = lsf->func->bootstrap_falcons;
		list_move(&lsf->head, &acr->lsf);
	पूर्ण अन्यथा अणु
		falcons = acr->func->bootstrap_falcons;
	पूर्ण

	/* Cull falcons that can't be bootstrapped, or the HSFW can fail to
	 * boot and leave the GPU in a weird state.
	 */
	list_क्रम_each_entry_safe(lsfw, lsft, &acr->lsfw, head) अणु
		अगर (!(falcons & BIT_ULL(lsfw->id))) अणु
			nvkm_warn(subdev, "%s falcon cannot be bootstrapped\n",
				  nvkm_acr_lsf_id(lsfw->id));
			nvkm_acr_lsfw_del(lsfw);
		पूर्ण
	पूर्ण

	अगर (!acr->wpr_fw || acr->wpr_comp)
		wpr_size = acr->func->wpr_layout(acr);

	/* Allocate/Locate WPR + fill ucode blob poपूर्णांकer.
	 *
	 *  dGPU: allocate WPR + shaकरोw blob
	 * Tegra: locate WPR with regs, ensure size is sufficient,
	 *        allocate ucode blob.
	 */
	ret = acr->func->wpr_alloc(acr, wpr_size);
	अगर (ret)
		वापस ret;

	nvkm_debug(subdev, "WPR region is from 0x%llx-0x%llx (shadow 0x%llx)\n",
		   acr->wpr_start, acr->wpr_end, acr->shaकरोw_start);

	/* Write WPR to ucode blob. */
	nvkm_kmap(acr->wpr);
	अगर (acr->wpr_fw && !acr->wpr_comp)
		nvkm_wobj(acr->wpr, 0, acr->wpr_fw->data, acr->wpr_fw->size);

	अगर (!acr->wpr_fw || acr->wpr_comp)
		acr->func->wpr_build(acr, nvkm_acr_falcon(device));
	acr->func->wpr_patch(acr, (s64)acr->wpr_start - acr->wpr_prev);

	अगर (acr->wpr_fw && acr->wpr_comp) अणु
		nvkm_kmap(acr->wpr);
		क्रम (i = 0; i < acr->wpr_fw->size; i += 4) अणु
			u32 us = nvkm_ro32(acr->wpr, i);
			u32 fw = ((u32 *)acr->wpr_fw->data)[i/4];
			अगर (fw != us) अणु
				nvkm_warn(subdev, "%08x: %08x %08x\n",
					  i, us, fw);
			पूर्ण
		पूर्ण
		वापस -EINVAL;
	पूर्ण
	nvkm_करोne(acr->wpr);

	/* Allocate instance block क्रम ACR-related stuff. */
	ret = nvkm_memory_new(device, NVKM_MEM_TARGET_INST, 0x1000, 0, true,
			      &acr->inst);
	अगर (ret)
		वापस ret;

	ret = nvkm_vmm_new(device, 0, 0, शून्य, 0, शून्य, "acr", &acr->vmm);
	अगर (ret)
		वापस ret;

	acr->vmm->debug = acr->subdev.debug;

	ret = nvkm_vmm_join(acr->vmm, acr->inst);
	अगर (ret)
		वापस ret;

	/* Load HS firmware blobs पूर्णांकo ACR VMM. */
	list_क्रम_each_entry(hsfw, &acr->hsfw, head) अणु
		nvkm_debug(subdev, "loading %s fw\n", hsfw->name);
		ret = hsfw->func->load(acr, hsfw);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Kill temporary data. */
	nvkm_acr_cleanup(acr);
	वापस 0;
पूर्ण

अटल व्योम *
nvkm_acr_dtor(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_acr *acr = nvkm_acr(subdev);
	काष्ठा nvkm_acr_hsf *hsf, *hst;
	काष्ठा nvkm_acr_lsf *lsf, *lst;

	list_क्रम_each_entry_safe(hsf, hst, &acr->hsf, head) अणु
		nvkm_vmm_put(acr->vmm, &hsf->vma);
		nvkm_memory_unref(&hsf->ucode);
		kमुक्त(hsf->imem);
		list_del(&hsf->head);
		kमुक्त(hsf);
	पूर्ण

	nvkm_vmm_part(acr->vmm, acr->inst);
	nvkm_vmm_unref(&acr->vmm);
	nvkm_memory_unref(&acr->inst);

	nvkm_memory_unref(&acr->wpr);

	list_क्रम_each_entry_safe(lsf, lst, &acr->lsf, head) अणु
		list_del(&lsf->head);
		kमुक्त(lsf);
	पूर्ण

	nvkm_acr_cleanup(acr);
	वापस acr;
पूर्ण

अटल स्थिर काष्ठा nvkm_subdev_func
nvkm_acr = अणु
	.dtor = nvkm_acr_dtor,
	.oneinit = nvkm_acr_oneinit,
	.init = nvkm_acr_init,
	.fini = nvkm_acr_fini,
पूर्ण;

अटल पूर्णांक
nvkm_acr_ctor_wpr(काष्ठा nvkm_acr *acr, पूर्णांक ver)
अणु
	काष्ठा nvkm_subdev *subdev = &acr->subdev;
	काष्ठा nvkm_device *device = subdev->device;
	पूर्णांक ret;

	ret = nvkm_firmware_get(subdev, "acr/wpr", ver, &acr->wpr_fw);
	अगर (ret < 0)
		वापस ret;

	/* Pre-add LSFs in the order they appear in the FW WPR image so that
	 * we're able to करो a binary comparison with our own generator.
	 */
	ret = acr->func->wpr_parse(acr);
	अगर (ret)
		वापस ret;

	acr->wpr_comp = nvkm_boolopt(device->cfgopt, "NvAcrWprCompare", false);
	acr->wpr_prev = nvkm_दीर्घopt(device->cfgopt, "NvAcrWprPrevAddr", 0);
	वापस 0;
पूर्ण

पूर्णांक
nvkm_acr_new_(स्थिर काष्ठा nvkm_acr_fwअगर *fwअगर, काष्ठा nvkm_device *device,
	      क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_acr **pacr)
अणु
	काष्ठा nvkm_acr *acr;
	दीर्घ wprfw;

	अगर (!(acr = *pacr = kzalloc(माप(*acr), GFP_KERNEL)))
		वापस -ENOMEM;
	nvkm_subdev_ctor(&nvkm_acr, device, type, inst, &acr->subdev);
	INIT_LIST_HEAD(&acr->hsfw);
	INIT_LIST_HEAD(&acr->lsfw);
	INIT_LIST_HEAD(&acr->hsf);
	INIT_LIST_HEAD(&acr->lsf);

	fwअगर = nvkm_firmware_load(&acr->subdev, fwअगर, "Acr", acr);
	अगर (IS_ERR(fwअगर))
		वापस PTR_ERR(fwअगर);

	acr->func = fwअगर->func;

	wprfw = nvkm_दीर्घopt(device->cfgopt, "NvAcrWpr", -1);
	अगर (wprfw >= 0) अणु
		पूर्णांक ret = nvkm_acr_ctor_wpr(acr, wprfw);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
