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
#समावेश <core/falcon.h>
#समावेश <core/firmware.h>
#समावेश <nvfw/fw.h>
#समावेश <nvfw/ls.h>

व्योम
nvkm_acr_lsfw_del(काष्ठा nvkm_acr_lsfw *lsfw)
अणु
	nvkm_blob_dtor(&lsfw->img);
	nvkm_firmware_put(lsfw->sig);
	list_del(&lsfw->head);
	kमुक्त(lsfw);
पूर्ण

व्योम
nvkm_acr_lsfw_del_all(काष्ठा nvkm_acr *acr)
अणु
	काष्ठा nvkm_acr_lsfw *lsfw, *lsft;
	list_क्रम_each_entry_safe(lsfw, lsft, &acr->lsfw, head) अणु
		nvkm_acr_lsfw_del(lsfw);
	पूर्ण
पूर्ण

अटल काष्ठा nvkm_acr_lsfw *
nvkm_acr_lsfw_get(काष्ठा nvkm_acr *acr, क्रमागत nvkm_acr_lsf_id id)
अणु
	काष्ठा nvkm_acr_lsfw *lsfw;
	list_क्रम_each_entry(lsfw, &acr->lsfw, head) अणु
		अगर (lsfw->id == id)
			वापस lsfw;
	पूर्ण
	वापस शून्य;
पूर्ण

काष्ठा nvkm_acr_lsfw *
nvkm_acr_lsfw_add(स्थिर काष्ठा nvkm_acr_lsf_func *func, काष्ठा nvkm_acr *acr,
		 काष्ठा nvkm_falcon *falcon, क्रमागत nvkm_acr_lsf_id id)
अणु
	काष्ठा nvkm_acr_lsfw *lsfw;

	अगर (!acr || list_empty(&acr->hsfw))
		वापस ERR_PTR(-ENOSYS);

	lsfw = nvkm_acr_lsfw_get(acr, id);
	अगर (lsfw && lsfw->func) अणु
		nvkm_error(&acr->subdev, "LSFW %d redefined\n", id);
		वापस ERR_PTR(-EEXIST);
	पूर्ण

	अगर (!lsfw) अणु
		अगर (!(lsfw = kzalloc(माप(*lsfw), GFP_KERNEL)))
			वापस ERR_PTR(-ENOMEM);

		lsfw->id = id;
		list_add_tail(&lsfw->head, &acr->lsfw);
	पूर्ण

	lsfw->func = func;
	lsfw->falcon = falcon;
	वापस lsfw;
पूर्ण

अटल काष्ठा nvkm_acr_lsfw *
nvkm_acr_lsfw_load_sig_image_desc_(काष्ठा nvkm_subdev *subdev,
				   काष्ठा nvkm_falcon *falcon,
				   क्रमागत nvkm_acr_lsf_id id,
				   स्थिर अक्षर *path, पूर्णांक ver,
				   स्थिर काष्ठा nvkm_acr_lsf_func *func,
				   स्थिर काष्ठा firmware **pdesc)
अणु
	काष्ठा nvkm_acr *acr = subdev->device->acr;
	काष्ठा nvkm_acr_lsfw *lsfw;
	पूर्णांक ret;

	अगर (IS_ERR((lsfw = nvkm_acr_lsfw_add(func, acr, falcon, id))))
		वापस lsfw;

	ret = nvkm_firmware_load_name(subdev, path, "sig", ver, &lsfw->sig);
	अगर (ret)
		जाओ करोne;

	ret = nvkm_firmware_load_blob(subdev, path, "image", ver, &lsfw->img);
	अगर (ret)
		जाओ करोne;

	ret = nvkm_firmware_load_name(subdev, path, "desc", ver, pdesc);
करोne:
	अगर (ret) अणु
		nvkm_acr_lsfw_del(lsfw);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस lsfw;
पूर्ण

अटल व्योम
nvkm_acr_lsfw_from_desc(स्थिर काष्ठा nvfw_ls_desc_head *desc,
			काष्ठा nvkm_acr_lsfw *lsfw)
अणु
	lsfw->bootloader_size = ALIGN(desc->bootloader_size, 256);
	lsfw->bootloader_imem_offset = desc->bootloader_imem_offset;

	lsfw->app_size = ALIGN(desc->app_size, 256);
	lsfw->app_start_offset = desc->app_start_offset;
	lsfw->app_imem_entry = desc->app_imem_entry;
	lsfw->app_resident_code_offset = desc->app_resident_code_offset;
	lsfw->app_resident_code_size = desc->app_resident_code_size;
	lsfw->app_resident_data_offset = desc->app_resident_data_offset;
	lsfw->app_resident_data_size = desc->app_resident_data_size;

	lsfw->ucode_size = ALIGN(lsfw->app_resident_data_offset, 256) +
			   lsfw->bootloader_size;
	lsfw->data_size = lsfw->app_size + lsfw->bootloader_size -
			  lsfw->ucode_size;
पूर्ण

पूर्णांक
nvkm_acr_lsfw_load_sig_image_desc(काष्ठा nvkm_subdev *subdev,
				  काष्ठा nvkm_falcon *falcon,
				  क्रमागत nvkm_acr_lsf_id id,
				  स्थिर अक्षर *path, पूर्णांक ver,
				  स्थिर काष्ठा nvkm_acr_lsf_func *func)
अणु
	स्थिर काष्ठा firmware *fw;
	काष्ठा nvkm_acr_lsfw *lsfw;

	lsfw = nvkm_acr_lsfw_load_sig_image_desc_(subdev, falcon, id, path, ver,
						  func, &fw);
	अगर (IS_ERR(lsfw))
		वापस PTR_ERR(lsfw);

	nvkm_acr_lsfw_from_desc(&nvfw_ls_desc(subdev, fw->data)->head, lsfw);
	nvkm_firmware_put(fw);
	वापस 0;
पूर्ण

पूर्णांक
nvkm_acr_lsfw_load_sig_image_desc_v1(काष्ठा nvkm_subdev *subdev,
				     काष्ठा nvkm_falcon *falcon,
				     क्रमागत nvkm_acr_lsf_id id,
				     स्थिर अक्षर *path, पूर्णांक ver,
				     स्थिर काष्ठा nvkm_acr_lsf_func *func)
अणु
	स्थिर काष्ठा firmware *fw;
	काष्ठा nvkm_acr_lsfw *lsfw;

	lsfw = nvkm_acr_lsfw_load_sig_image_desc_(subdev, falcon, id, path, ver,
						  func, &fw);
	अगर (IS_ERR(lsfw))
		वापस PTR_ERR(lsfw);

	nvkm_acr_lsfw_from_desc(&nvfw_ls_desc_v1(subdev, fw->data)->head, lsfw);
	nvkm_firmware_put(fw);
	वापस 0;
पूर्ण

पूर्णांक
nvkm_acr_lsfw_load_bl_inst_data_sig(काष्ठा nvkm_subdev *subdev,
				    काष्ठा nvkm_falcon *falcon,
				    क्रमागत nvkm_acr_lsf_id id,
				    स्थिर अक्षर *path, पूर्णांक ver,
				    स्थिर काष्ठा nvkm_acr_lsf_func *func)
अणु
	काष्ठा nvkm_acr *acr = subdev->device->acr;
	काष्ठा nvkm_acr_lsfw *lsfw;
	स्थिर काष्ठा firmware *bl = शून्य, *inst = शून्य, *data = शून्य;
	स्थिर काष्ठा nvfw_bin_hdr *hdr;
	स्थिर काष्ठा nvfw_bl_desc *desc;
	u32 *bldata;
	पूर्णांक ret;

	अगर (IS_ERR((lsfw = nvkm_acr_lsfw_add(func, acr, falcon, id))))
		वापस PTR_ERR(lsfw);

	ret = nvkm_firmware_load_name(subdev, path, "bl", ver, &bl);
	अगर (ret)
		जाओ करोne;

	hdr = nvfw_bin_hdr(subdev, bl->data);
	desc = nvfw_bl_desc(subdev, bl->data + hdr->header_offset);
	bldata = (व्योम *)(bl->data + hdr->data_offset);

	ret = nvkm_firmware_load_name(subdev, path, "inst", ver, &inst);
	अगर (ret)
		जाओ करोne;

	ret = nvkm_firmware_load_name(subdev, path, "data", ver, &data);
	अगर (ret)
		जाओ करोne;

	ret = nvkm_firmware_load_name(subdev, path, "sig", ver, &lsfw->sig);
	अगर (ret)
		जाओ करोne;

	lsfw->bootloader_size = ALIGN(desc->code_size, 256);
	lsfw->bootloader_imem_offset = desc->start_tag << 8;

	lsfw->app_start_offset = lsfw->bootloader_size;
	lsfw->app_imem_entry = 0;
	lsfw->app_resident_code_offset = 0;
	lsfw->app_resident_code_size = ALIGN(inst->size, 256);
	lsfw->app_resident_data_offset = lsfw->app_resident_code_size;
	lsfw->app_resident_data_size = ALIGN(data->size, 256);
	lsfw->app_size = lsfw->app_resident_code_size +
			 lsfw->app_resident_data_size;

	lsfw->img.size = lsfw->bootloader_size + lsfw->app_size;
	अगर (!(lsfw->img.data = kzalloc(lsfw->img.size, GFP_KERNEL))) अणु
		ret = -ENOMEM;
		जाओ करोne;
	पूर्ण

	स_नकल(lsfw->img.data, bldata, lsfw->bootloader_size);
	स_नकल(lsfw->img.data + lsfw->app_start_offset +
	       lsfw->app_resident_code_offset, inst->data, inst->size);
	स_नकल(lsfw->img.data + lsfw->app_start_offset +
	       lsfw->app_resident_data_offset, data->data, data->size);

	lsfw->ucode_size = ALIGN(lsfw->app_resident_data_offset, 256) +
			   lsfw->bootloader_size;
	lsfw->data_size = lsfw->app_size + lsfw->bootloader_size -
			  lsfw->ucode_size;

करोne:
	अगर (ret)
		nvkm_acr_lsfw_del(lsfw);
	nvkm_firmware_put(data);
	nvkm_firmware_put(inst);
	nvkm_firmware_put(bl);
	वापस ret;
पूर्ण
