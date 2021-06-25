<शैली गुरु>
/*
 * Copyright 2020 Advanced Micro Devices, Inc.
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
 *
 */
#समावेश <linux/debugfs.h>
#समावेश <linux/pm_runसमय.स>

#समावेश "amdgpu.h"
#समावेश "amdgpu_rap.h"

/**
 * DOC: AMDGPU RAP debugfs test पूर्णांकerface
 *
 * how to use?
 * echo opcode > <debugfs_dir>/dri/xxx/rap_test
 *
 * opcode:
 * currently, only 2 is supported by Linux host driver,
 * opcode 2 stands क्रम TA_CMD_RAP__VALIDATE_L0, used to
 * trigger L0 policy validation, you can refer more detail
 * from header file ta_rap_अगर.h
 *
 */
अटल sमाप_प्रकार amdgpu_rap_debugfs_ग_लिखो(काष्ठा file *f, स्थिर अक्षर __user *buf,
		माप_प्रकार size, loff_t *pos)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)file_inode(f)->i_निजी;
	काष्ठा ta_rap_shared_memory *rap_shared_mem;
	काष्ठा ta_rap_cmd_output_data *rap_cmd_output;
	काष्ठा drm_device *dev = adev_to_drm(adev);
	uपूर्णांक32_t op;
	क्रमागत ta_rap_status status;
	पूर्णांक ret;

	अगर (*pos || size != 2)
		वापस -EINVAL;

	ret = kstrtouपूर्णांक_from_user(buf, size, *pos, &op);
	अगर (ret)
		वापस ret;

	ret = pm_runसमय_get_sync(dev->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_स्वतःsuspend(dev->dev);
		वापस ret;
	पूर्ण

	/* make sure gfx core is on, RAP TA cann't handle
	 * GFX OFF हाल currently.
	 */
	amdgpu_gfx_off_ctrl(adev, false);

	चयन (op) अणु
	हाल 2:
		ret = psp_rap_invoke(&adev->psp, op, &status);
		अगर (!ret && status == TA_RAP_STATUS__SUCCESS) अणु
			dev_info(adev->dev, "RAP L0 validate test success.\n");
		पूर्ण अन्यथा अणु
			rap_shared_mem = (काष्ठा ta_rap_shared_memory *)
					 adev->psp.rap_context.rap_shared_buf;
			rap_cmd_output = &(rap_shared_mem->rap_out_message.output);

			dev_info(adev->dev, "RAP test failed, the output is:\n");
			dev_info(adev->dev, "\tlast_subsection: 0x%08x.\n",
				 rap_cmd_output->last_subsection);
			dev_info(adev->dev, "\tnum_total_validate: 0x%08x.\n",
				 rap_cmd_output->num_total_validate);
			dev_info(adev->dev, "\tnum_valid: 0x%08x.\n",
				 rap_cmd_output->num_valid);
			dev_info(adev->dev, "\tlast_validate_addr: 0x%08x.\n",
				 rap_cmd_output->last_validate_addr);
			dev_info(adev->dev, "\tlast_validate_val: 0x%08x.\n",
				 rap_cmd_output->last_validate_val);
			dev_info(adev->dev, "\tlast_validate_val_exptd: 0x%08x.\n",
				 rap_cmd_output->last_validate_val_exptd);
		पूर्ण
		अवरोध;
	शेष:
		dev_info(adev->dev, "Unsupported op id: %d, ", op);
		dev_info(adev->dev, "Only support op 2(L0 validate test).\n");
		अवरोध;
	पूर्ण

	amdgpu_gfx_off_ctrl(adev, true);
	pm_runसमय_mark_last_busy(dev->dev);
	pm_runसमय_put_स्वतःsuspend(dev->dev);

	वापस size;
पूर्ण

अटल स्थिर काष्ठा file_operations amdgpu_rap_debugfs_ops = अणु
	.owner = THIS_MODULE,
	.पढ़ो = शून्य,
	.ग_लिखो = amdgpu_rap_debugfs_ग_लिखो,
	.llseek = शेष_llseek
पूर्ण;

व्योम amdgpu_rap_debugfs_init(काष्ठा amdgpu_device *adev)
अणु
#अगर defined(CONFIG_DEBUG_FS)
	काष्ठा drm_minor *minor = adev_to_drm(adev)->primary;

	अगर (!adev->psp.rap_context.rap_initialized)
		वापस;

	debugfs_create_file("rap_test", S_IWUSR, minor->debugfs_root,
				adev, &amdgpu_rap_debugfs_ops);
#पूर्ण_अगर
पूर्ण
