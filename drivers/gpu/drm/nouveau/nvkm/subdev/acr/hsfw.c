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

#समावेश <nvfw/fw.h>
#समावेश <nvfw/hs.h>

अटल व्योम
nvkm_acr_hsfw_del(काष्ठा nvkm_acr_hsfw *hsfw)
अणु
	list_del(&hsfw->head);
	kमुक्त(hsfw->imem);
	kमुक्त(hsfw->image);
	kमुक्त(hsfw->sig.prod.data);
	kमुक्त(hsfw->sig.dbg.data);
	kमुक्त(hsfw);
पूर्ण

व्योम
nvkm_acr_hsfw_del_all(काष्ठा nvkm_acr *acr)
अणु
	काष्ठा nvkm_acr_hsfw *hsfw, *hsft;
	list_क्रम_each_entry_safe(hsfw, hsft, &acr->hsfw, head) अणु
		nvkm_acr_hsfw_del(hsfw);
	पूर्ण
पूर्ण

अटल पूर्णांक
nvkm_acr_hsfw_load_image(काष्ठा nvkm_acr *acr, स्थिर अक्षर *name, पूर्णांक ver,
			 काष्ठा nvkm_acr_hsfw *hsfw)
अणु
	काष्ठा nvkm_subdev *subdev = &acr->subdev;
	स्थिर काष्ठा firmware *fw;
	स्थिर काष्ठा nvfw_bin_hdr *hdr;
	स्थिर काष्ठा nvfw_hs_header *fwhdr;
	स्थिर काष्ठा nvfw_hs_load_header *lhdr;
	u32 loc, sig;
	पूर्णांक ret;

	ret = nvkm_firmware_get(subdev, name, ver, &fw);
	अगर (ret < 0)
		वापस ret;

	hdr = nvfw_bin_hdr(subdev, fw->data);
	fwhdr = nvfw_hs_header(subdev, fw->data + hdr->header_offset);

	/* Earlier FW releases by NVIDIA क्रम Nouveau's use aren't in NVIDIA's
	 * standard क्रमmat, and करोn't have the indirection seen in the 0x10de
	 * हाल.
	 */
	चयन (hdr->bin_magic) अणु
	हाल 0x000010de:
		loc = *(u32 *)(fw->data + fwhdr->patch_loc);
		sig = *(u32 *)(fw->data + fwhdr->patch_sig);
		अवरोध;
	हाल 0x3b1d14f0:
		loc = fwhdr->patch_loc;
		sig = fwhdr->patch_sig;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	lhdr = nvfw_hs_load_header(subdev, fw->data + fwhdr->hdr_offset);

	अगर (!(hsfw->image = kदो_स्मृति(hdr->data_size, GFP_KERNEL))) अणु
		ret = -ENOMEM;
		जाओ करोne;
	पूर्ण

	स_नकल(hsfw->image, fw->data + hdr->data_offset, hdr->data_size);
	hsfw->image_size = hdr->data_size;
	hsfw->non_sec_addr = lhdr->non_sec_code_off;
	hsfw->non_sec_size = lhdr->non_sec_code_size;
	hsfw->sec_addr = lhdr->apps[0];
	hsfw->sec_size = lhdr->apps[lhdr->num_apps];
	hsfw->data_addr = lhdr->data_dma_base;
	hsfw->data_size = lhdr->data_size;

	hsfw->sig.prod.size = fwhdr->sig_prod_size;
	hsfw->sig.prod.data = kmemdup(fw->data + fwhdr->sig_prod_offset + sig,
				      hsfw->sig.prod.size, GFP_KERNEL);
	अगर (!hsfw->sig.prod.data) अणु
		ret = -ENOMEM;
		जाओ करोne;
	पूर्ण

	hsfw->sig.dbg.size = fwhdr->sig_dbg_size;
	hsfw->sig.dbg.data = kmemdup(fw->data + fwhdr->sig_dbg_offset + sig,
				     hsfw->sig.dbg.size, GFP_KERNEL);
	अगर (!hsfw->sig.dbg.data) अणु
		ret = -ENOMEM;
		जाओ करोne;
	पूर्ण

	hsfw->sig.patch_loc = loc;
करोne:
	nvkm_firmware_put(fw);
	वापस ret;
पूर्ण

अटल पूर्णांक
nvkm_acr_hsfw_load_bl(काष्ठा nvkm_acr *acr, स्थिर अक्षर *name, पूर्णांक ver,
		      काष्ठा nvkm_acr_hsfw *hsfw)
अणु
	काष्ठा nvkm_subdev *subdev = &acr->subdev;
	स्थिर काष्ठा nvfw_bin_hdr *hdr;
	स्थिर काष्ठा nvfw_bl_desc *desc;
	स्थिर काष्ठा firmware *fw;
	u8 *data;
	पूर्णांक ret;

	ret = nvkm_firmware_get(subdev, name, ver, &fw);
	अगर (ret)
		वापस ret;

	hdr = nvfw_bin_hdr(subdev, fw->data);
	desc = nvfw_bl_desc(subdev, fw->data + hdr->header_offset);
	data = (व्योम *)fw->data + hdr->data_offset;

	hsfw->imem_size = desc->code_size;
	hsfw->imem_tag = desc->start_tag;
	hsfw->imem = kदो_स्मृति(desc->code_size, GFP_KERNEL);
	स_नकल(hsfw->imem, data + desc->code_off, desc->code_size);

	nvkm_firmware_put(fw);
	वापस 0;
पूर्ण

पूर्णांक
nvkm_acr_hsfw_load(काष्ठा nvkm_acr *acr, स्थिर अक्षर *bl, स्थिर अक्षर *fw,
		   स्थिर अक्षर *name, पूर्णांक version,
		   स्थिर काष्ठा nvkm_acr_hsf_fwअगर *fwअगर)
अणु
	काष्ठा nvkm_acr_hsfw *hsfw;
	पूर्णांक ret;

	अगर (!(hsfw = kzalloc(माप(*hsfw), GFP_KERNEL)))
		वापस -ENOMEM;

	hsfw->func = fwअगर->func;
	hsfw->name = name;
	list_add_tail(&hsfw->head, &acr->hsfw);

	ret = nvkm_acr_hsfw_load_bl(acr, bl, version, hsfw);
	अगर (ret)
		जाओ करोne;

	ret = nvkm_acr_hsfw_load_image(acr, fw, version, hsfw);
करोne:
	अगर (ret)
		nvkm_acr_hsfw_del(hsfw);
	वापस ret;
पूर्ण
