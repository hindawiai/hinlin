<शैली गुरु>
/*
 * Copyright 2019 Advanced Micro Devices, Inc.
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
 */

#समावेश "amdgpu_ras.h"

पूर्णांक amdgpu_umc_ras_late_init(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक r;
	काष्ठा ras_fs_अगर fs_info = अणु
		.sysfs_name = "umc_err_count",
	पूर्ण;
	काष्ठा ras_ih_अगर ih_info = अणु
		.cb = amdgpu_umc_process_ras_data_cb,
	पूर्ण;

	अगर (!adev->umc.ras_अगर) अणु
		adev->umc.ras_अगर =
			kदो_स्मृति(माप(काष्ठा ras_common_अगर), GFP_KERNEL);
		अगर (!adev->umc.ras_अगर)
			वापस -ENOMEM;
		adev->umc.ras_अगर->block = AMDGPU_RAS_BLOCK__UMC;
		adev->umc.ras_अगर->type = AMDGPU_RAS_ERROR__MULTI_UNCORRECTABLE;
		adev->umc.ras_अगर->sub_block_index = 0;
		म_नकल(adev->umc.ras_अगर->name, "umc");
	पूर्ण
	ih_info.head = fs_info.head = *adev->umc.ras_अगर;

	r = amdgpu_ras_late_init(adev, adev->umc.ras_अगर,
				 &fs_info, &ih_info);
	अगर (r)
		जाओ मुक्त;

	अगर (amdgpu_ras_is_supported(adev, adev->umc.ras_अगर->block)) अणु
		r = amdgpu_irq_get(adev, &adev->gmc.ecc_irq, 0);
		अगर (r)
			जाओ late_fini;
	पूर्ण अन्यथा अणु
		r = 0;
		जाओ मुक्त;
	पूर्ण

	/* ras init of specअगरic umc version */
	अगर (adev->umc.ras_funcs &&
	    adev->umc.ras_funcs->err_cnt_init)
		adev->umc.ras_funcs->err_cnt_init(adev);

	वापस 0;

late_fini:
	amdgpu_ras_late_fini(adev, adev->umc.ras_अगर, &ih_info);
मुक्त:
	kमुक्त(adev->umc.ras_अगर);
	adev->umc.ras_अगर = शून्य;
	वापस r;
पूर्ण

व्योम amdgpu_umc_ras_fini(काष्ठा amdgpu_device *adev)
अणु
	अगर (amdgpu_ras_is_supported(adev, AMDGPU_RAS_BLOCK__UMC) &&
			adev->umc.ras_अगर) अणु
		काष्ठा ras_common_अगर *ras_अगर = adev->umc.ras_अगर;
		काष्ठा ras_ih_अगर ih_info = अणु
			.head = *ras_अगर,
			.cb = amdgpu_umc_process_ras_data_cb,
		पूर्ण;

		amdgpu_ras_late_fini(adev, ras_अगर, &ih_info);
		kमुक्त(ras_अगर);
	पूर्ण
पूर्ण

पूर्णांक amdgpu_umc_process_ras_data_cb(काष्ठा amdgpu_device *adev,
		व्योम *ras_error_status,
		काष्ठा amdgpu_iv_entry *entry)
अणु
	काष्ठा ras_err_data *err_data = (काष्ठा ras_err_data *)ras_error_status;

	kgd2kfd_set_sram_ecc_flag(adev->kfd.dev);
	अगर (adev->umc.ras_funcs &&
	    adev->umc.ras_funcs->query_ras_error_count)
	    adev->umc.ras_funcs->query_ras_error_count(adev, ras_error_status);

	अगर (adev->umc.ras_funcs &&
	    adev->umc.ras_funcs->query_ras_error_address &&
	    adev->umc.max_ras_err_cnt_per_query) अणु
		err_data->err_addr =
			kसुस्मृति(adev->umc.max_ras_err_cnt_per_query,
				माप(काष्ठा eeprom_table_record), GFP_KERNEL);

		/* still call query_ras_error_address to clear error status
		 * even NOMEM error is encountered
		 */
		अगर(!err_data->err_addr)
			dev_warn(adev->dev, "Failed to alloc memory for "
					"umc error address record!\n");

		/* umc query_ras_error_address is also responsible क्रम clearing
		 * error status
		 */
		adev->umc.ras_funcs->query_ras_error_address(adev, ras_error_status);
	पूर्ण

	/* only uncorrectable error needs gpu reset */
	अगर (err_data->ue_count) अणु
		dev_info(adev->dev, "%ld uncorrectable hardware errors "
				"detected in UMC block\n",
				err_data->ue_count);

		अगर ((amdgpu_bad_page_threshold != 0) &&
			err_data->err_addr_cnt) अणु
			amdgpu_ras_add_bad_pages(adev, err_data->err_addr,
						err_data->err_addr_cnt);
			amdgpu_ras_save_bad_pages(adev);
		पूर्ण

		amdgpu_ras_reset_gpu(adev);
	पूर्ण

	kमुक्त(err_data->err_addr);
	वापस AMDGPU_RAS_SUCCESS;
पूर्ण

पूर्णांक amdgpu_umc_process_ecc_irq(काष्ठा amdgpu_device *adev,
		काष्ठा amdgpu_irq_src *source,
		काष्ठा amdgpu_iv_entry *entry)
अणु
	काष्ठा ras_common_अगर *ras_अगर = adev->umc.ras_अगर;
	काष्ठा ras_dispatch_अगर ih_data = अणु
		.entry = entry,
	पूर्ण;

	अगर (!ras_अगर)
		वापस 0;

	ih_data.head = *ras_अगर;

	amdgpu_ras_पूर्णांकerrupt_dispatch(adev, &ih_data);
	वापस 0;
पूर्ण
