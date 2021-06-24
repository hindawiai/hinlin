<शैली गुरु>
/*
 * Copyright 2021 Advanced Micro Devices, Inc.
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

#समावेश "aldebaran.h"
#समावेश "amdgpu_reset.h"
#समावेश "amdgpu_amdkfd.h"
#समावेश "amdgpu_dpm.h"
#समावेश "amdgpu_job.h"
#समावेश "amdgpu_ring.h"
#समावेश "amdgpu_ras.h"
#समावेश "amdgpu_psp.h"
#समावेश "amdgpu_xgmi.h"

अटल काष्ठा amdgpu_reset_handler *
aldebaran_get_reset_handler(काष्ठा amdgpu_reset_control *reset_ctl,
			    काष्ठा amdgpu_reset_context *reset_context)
अणु
	काष्ठा amdgpu_reset_handler *handler;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)reset_ctl->handle;

	अगर (reset_context->method != AMD_RESET_METHOD_NONE) अणु
		dev_dbg(adev->dev, "Getting reset handler for method %d\n",
			reset_context->method);
		list_क्रम_each_entry(handler, &reset_ctl->reset_handlers,
				     handler_list) अणु
			अगर (handler->reset_method == reset_context->method)
				वापस handler;
		पूर्ण
	पूर्ण

	अगर (adev->gmc.xgmi.connected_to_cpu) अणु
		list_क्रम_each_entry(handler, &reset_ctl->reset_handlers,
				     handler_list) अणु
			अगर (handler->reset_method == AMD_RESET_METHOD_MODE2) अणु
				reset_context->method = AMD_RESET_METHOD_MODE2;
				वापस handler;
			पूर्ण
		पूर्ण
	पूर्ण

	dev_dbg(adev->dev, "Reset handler not found!\n");

	वापस शून्य;
पूर्ण

अटल पूर्णांक aldebaran_mode2_suspend_ip(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक r, i;

	amdgpu_device_set_pg_state(adev, AMD_PG_STATE_UNGATE);
	amdgpu_device_set_cg_state(adev, AMD_CG_STATE_UNGATE);

	क्रम (i = adev->num_ip_blocks - 1; i >= 0; i--) अणु
		अगर (!(adev->ip_blocks[i].version->type ==
			      AMD_IP_BLOCK_TYPE_GFX ||
		      adev->ip_blocks[i].version->type ==
			      AMD_IP_BLOCK_TYPE_SDMA))
			जारी;

		r = adev->ip_blocks[i].version->funcs->suspend(adev);

		अगर (r) अणु
			dev_err(adev->dev,
				"suspend of IP block <%s> failed %d\n",
				adev->ip_blocks[i].version->funcs->name, r);
			वापस r;
		पूर्ण

		adev->ip_blocks[i].status.hw = false;
	पूर्ण

	वापस r;
पूर्ण

अटल पूर्णांक
aldebaran_mode2_prepare_hwcontext(काष्ठा amdgpu_reset_control *reset_ctl,
				  काष्ठा amdgpu_reset_context *reset_context)
अणु
	पूर्णांक r = 0;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)reset_ctl->handle;

	dev_dbg(adev->dev, "Aldebaran prepare hw context\n");
	/* Don't suspend on bare metal अगर we are not going to HW reset the ASIC */
	अगर (!amdgpu_sriov_vf(adev))
		r = aldebaran_mode2_suspend_ip(adev);

	वापस r;
पूर्ण

अटल व्योम aldebaran_async_reset(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा amdgpu_reset_handler *handler;
	काष्ठा amdgpu_reset_control *reset_ctl =
		container_of(work, काष्ठा amdgpu_reset_control, reset_work);
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)reset_ctl->handle;

	list_क्रम_each_entry(handler, &reset_ctl->reset_handlers,
			     handler_list) अणु
		अगर (handler->reset_method == reset_ctl->active_reset) अणु
			dev_dbg(adev->dev, "Resetting device\n");
			handler->करो_reset(adev);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक aldebaran_mode2_reset(काष्ठा amdgpu_device *adev)
अणु
	/* disable BM */
	pci_clear_master(adev->pdev);
	adev->asic_reset_res = amdgpu_dpm_mode2_reset(adev);
	वापस adev->asic_reset_res;
पूर्ण

अटल पूर्णांक
aldebaran_mode2_perक्रमm_reset(काष्ठा amdgpu_reset_control *reset_ctl,
			      काष्ठा amdgpu_reset_context *reset_context)
अणु
	काष्ठा amdgpu_device *पंचांगp_adev = शून्य;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)reset_ctl->handle;
	पूर्णांक r = 0;

	dev_dbg(adev->dev, "aldebaran perform hw reset\n");
	अगर (reset_context->hive == शून्य) अणु
		/* Wrong context, वापस error */
		वापस -EINVAL;
	पूर्ण

	list_क्रम_each_entry(पंचांगp_adev, &reset_context->hive->device_list,
			     gmc.xgmi.head) अणु
		mutex_lock(&पंचांगp_adev->reset_cntl->reset_lock);
		पंचांगp_adev->reset_cntl->active_reset = AMD_RESET_METHOD_MODE2;
	पूर्ण
	/*
	 * Mode2 reset करोesn't need any sync between nodes in XGMI hive, instead launch
	 * them together so that they can be completed asynchronously on multiple nodes
	 */
	list_क्रम_each_entry(पंचांगp_adev, &reset_context->hive->device_list,
			     gmc.xgmi.head) अणु
		/* For XGMI run all resets in parallel to speed up the process */
		अगर (पंचांगp_adev->gmc.xgmi.num_physical_nodes > 1) अणु
			अगर (!queue_work(प्रणाली_unbound_wq,
					&पंचांगp_adev->reset_cntl->reset_work))
				r = -EALREADY;
		पूर्ण अन्यथा
			r = aldebaran_mode2_reset(पंचांगp_adev);
		अगर (r) अणु
			dev_err(पंचांगp_adev->dev,
				"ASIC reset failed with error, %d for drm dev, %s",
				r, adev_to_drm(पंचांगp_adev)->unique);
			अवरोध;
		पूर्ण
	पूर्ण

	/* For XGMI रुको क्रम all resets to complete beक्रमe proceed */
	अगर (!r) अणु
		list_क्रम_each_entry(पंचांगp_adev,
				     &reset_context->hive->device_list,
				     gmc.xgmi.head) अणु
			अगर (पंचांगp_adev->gmc.xgmi.num_physical_nodes > 1) अणु
				flush_work(&पंचांगp_adev->reset_cntl->reset_work);
				r = पंचांगp_adev->asic_reset_res;
				अगर (r)
					अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(पंचांगp_adev, &reset_context->hive->device_list,
			     gmc.xgmi.head) अणु
		mutex_unlock(&पंचांगp_adev->reset_cntl->reset_lock);
		पंचांगp_adev->reset_cntl->active_reset = AMD_RESET_METHOD_NONE;
	पूर्ण

	वापस r;
पूर्ण

अटल पूर्णांक aldebaran_mode2_restore_ip(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_firmware_info *ucode_list[AMDGPU_UCODE_ID_MAXIMUM];
	काष्ठा amdgpu_firmware_info *ucode;
	काष्ठा amdgpu_ip_block *cmn_block;
	पूर्णांक ucode_count = 0;
	पूर्णांक i, r;

	dev_dbg(adev->dev, "Reloading ucodes after reset\n");
	क्रम (i = 0; i < adev->firmware.max_ucodes; i++) अणु
		ucode = &adev->firmware.ucode[i];
		अगर (!ucode->fw)
			जारी;
		चयन (ucode->ucode_id) अणु
		हाल AMDGPU_UCODE_ID_SDMA0:
		हाल AMDGPU_UCODE_ID_SDMA1:
		हाल AMDGPU_UCODE_ID_SDMA2:
		हाल AMDGPU_UCODE_ID_SDMA3:
		हाल AMDGPU_UCODE_ID_SDMA4:
		हाल AMDGPU_UCODE_ID_SDMA5:
		हाल AMDGPU_UCODE_ID_SDMA6:
		हाल AMDGPU_UCODE_ID_SDMA7:
		हाल AMDGPU_UCODE_ID_CP_MEC1:
		हाल AMDGPU_UCODE_ID_CP_MEC1_JT:
		हाल AMDGPU_UCODE_ID_RLC_RESTORE_LIST_CNTL:
		हाल AMDGPU_UCODE_ID_RLC_RESTORE_LIST_GPM_MEM:
		हाल AMDGPU_UCODE_ID_RLC_RESTORE_LIST_SRM_MEM:
		हाल AMDGPU_UCODE_ID_RLC_G:
			ucode_list[ucode_count++] = ucode;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण;
	पूर्ण

	/* Reinit NBIF block */
	cmn_block =
		amdgpu_device_ip_get_ip_block(adev, AMD_IP_BLOCK_TYPE_COMMON);
	अगर (unlikely(!cmn_block)) अणु
		dev_err(adev->dev, "Failed to get BIF handle\n");
		वापस -EINVAL;
	पूर्ण
	r = cmn_block->version->funcs->resume(adev);
	अगर (r)
		वापस r;

	/* Reinit GFXHUB */
	adev->gfxhub.funcs->init(adev);
	r = adev->gfxhub.funcs->gart_enable(adev);
	अगर (r) अणु
		dev_err(adev->dev, "GFXHUB gart reenable failed after reset\n");
		वापस r;
	पूर्ण

	/* Reload GFX firmware */
	r = psp_load_fw_list(&adev->psp, ucode_list, ucode_count);
	अगर (r) अणु
		dev_err(adev->dev, "GFX ucode load failed after reset\n");
		वापस r;
	पूर्ण

	/* Resume RLC, FW needs RLC alive to complete reset process */
	adev->gfx.rlc.funcs->resume(adev);

	/* Wait क्रम FW reset event complete */
	r = smu_रुको_क्रम_event(adev, SMU_EVENT_RESET_COMPLETE, 0);
	अगर (r) अणु
		dev_err(adev->dev,
			"Failed to get response from firmware after reset\n");
		वापस r;
	पूर्ण

	क्रम (i = 0; i < adev->num_ip_blocks; i++) अणु
		अगर (!(adev->ip_blocks[i].version->type ==
			      AMD_IP_BLOCK_TYPE_GFX ||
		      adev->ip_blocks[i].version->type ==
			      AMD_IP_BLOCK_TYPE_SDMA))
			जारी;
		r = adev->ip_blocks[i].version->funcs->resume(adev);
		अगर (r) अणु
			dev_err(adev->dev,
				"resume of IP block <%s> failed %d\n",
				adev->ip_blocks[i].version->funcs->name, r);
			वापस r;
		पूर्ण

		adev->ip_blocks[i].status.hw = true;
	पूर्ण

	क्रम (i = 0; i < adev->num_ip_blocks; i++) अणु
		अगर (!(adev->ip_blocks[i].version->type ==
			      AMD_IP_BLOCK_TYPE_GFX ||
		      adev->ip_blocks[i].version->type ==
			      AMD_IP_BLOCK_TYPE_SDMA ||
		      adev->ip_blocks[i].version->type ==
			      AMD_IP_BLOCK_TYPE_COMMON))
			जारी;

		अगर (adev->ip_blocks[i].version->funcs->late_init) अणु
			r = adev->ip_blocks[i].version->funcs->late_init(
				(व्योम *)adev);
			अगर (r) अणु
				dev_err(adev->dev,
					"late_init of IP block <%s> failed %d after reset\n",
					adev->ip_blocks[i].version->funcs->name,
					r);
				वापस r;
			पूर्ण
		पूर्ण
		adev->ip_blocks[i].status.late_initialized = true;
	पूर्ण

	amdgpu_device_set_cg_state(adev, AMD_CG_STATE_GATE);
	amdgpu_device_set_pg_state(adev, AMD_PG_STATE_GATE);

	वापस r;
पूर्ण

अटल पूर्णांक
aldebaran_mode2_restore_hwcontext(काष्ठा amdgpu_reset_control *reset_ctl,
				  काष्ठा amdgpu_reset_context *reset_context)
अणु
	पूर्णांक r;
	काष्ठा amdgpu_device *पंचांगp_adev = शून्य;

	अगर (reset_context->hive == शून्य) अणु
		/* Wrong context, वापस error */
		वापस -EINVAL;
	पूर्ण

	list_क्रम_each_entry(पंचांगp_adev, &reset_context->hive->device_list,
			     gmc.xgmi.head) अणु
		dev_info(पंचांगp_adev->dev,
			 "GPU reset succeeded, trying to resume\n");
		r = aldebaran_mode2_restore_ip(पंचांगp_adev);
		अगर (r)
			जाओ end;

		/*
		 * Add this ASIC as tracked as reset was alपढ़ोy
		 * complete successfully.
		 */
		amdgpu_रेजिस्टर_gpu_instance(पंचांगp_adev);

		/* Resume RAS */
		amdgpu_ras_resume(पंचांगp_adev);

		/* Update PSP FW topology after reset */
		अगर (reset_context->hive &&
		    पंचांगp_adev->gmc.xgmi.num_physical_nodes > 1)
			r = amdgpu_xgmi_update_topology(reset_context->hive,
							पंचांगp_adev);

		अगर (!r) अणु
			amdgpu_irq_gpu_reset_resume_helper(पंचांगp_adev);

			r = amdgpu_ib_ring_tests(पंचांगp_adev);
			अगर (r) अणु
				dev_err(पंचांगp_adev->dev,
					"ib ring test failed (%d).\n", r);
				r = -EAGAIN;
				पंचांगp_adev->asic_reset_res = r;
				जाओ end;
			पूर्ण
		पूर्ण
	पूर्ण

end:
	वापस r;
पूर्ण

अटल काष्ठा amdgpu_reset_handler aldebaran_mode2_handler = अणु
	.reset_method		= AMD_RESET_METHOD_MODE2,
	.prepare_env		= शून्य,
	.prepare_hwcontext	= aldebaran_mode2_prepare_hwcontext,
	.perक्रमm_reset		= aldebaran_mode2_perक्रमm_reset,
	.restore_hwcontext	= aldebaran_mode2_restore_hwcontext,
	.restore_env		= शून्य,
	.करो_reset		= aldebaran_mode2_reset,
पूर्ण;

पूर्णांक aldebaran_reset_init(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_reset_control *reset_ctl;

	reset_ctl = kzalloc(माप(*reset_ctl), GFP_KERNEL);
	अगर (!reset_ctl)
		वापस -ENOMEM;

	reset_ctl->handle = adev;
	reset_ctl->async_reset = aldebaran_async_reset;
	reset_ctl->active_reset = AMD_RESET_METHOD_NONE;
	reset_ctl->get_reset_handler = aldebaran_get_reset_handler;

	INIT_LIST_HEAD(&reset_ctl->reset_handlers);
	INIT_WORK(&reset_ctl->reset_work, reset_ctl->async_reset);
	/* Only mode2 is handled through reset control now */
	amdgpu_reset_add_handler(reset_ctl, &aldebaran_mode2_handler);

	adev->reset_cntl = reset_ctl;

	वापस 0;
पूर्ण

पूर्णांक aldebaran_reset_fini(काष्ठा amdgpu_device *adev)
अणु
	kमुक्त(adev->reset_cntl);
	adev->reset_cntl = शून्य;
	वापस 0;
पूर्ण
