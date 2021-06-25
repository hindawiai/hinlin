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
 *
 */
#समावेश <linux/debugfs.h>
#समावेश <linux/pm_runसमय.स>

#समावेश "amdgpu.h"
#समावेश "amdgpu_securedisplay.h"

/**
 * DOC: AMDGPU SECUREDISPLAY debugfs test पूर्णांकerface
 *
 * how to use?
 * echo opcode <value> > <debugfs_dir>/dri/xxx/securedisplay_test
 * eg. echo 1 > <debugfs_dir>/dri/xxx/securedisplay_test
 * eg. echo 2 phy_id > <debugfs_dir>/dri/xxx/securedisplay_test
 *
 * opcode:
 * 1oञQuery whether TA is responding used only क्रम validation pupose
 * 2: Send region of Interest and CRC value to I2C. (uपूर्णांक32)phy_id is
 * send to determine which DIO scratch रेजिस्टर should be used to get
 * ROI and receive i2c_buf as the output.
 *
 * You can refer more detail from header file ta_securedisplay_अगर.h
 *
 */

व्योम psp_securedisplay_parse_resp_status(काष्ठा psp_context *psp,
	क्रमागत ta_securedisplay_status status)
अणु
	चयन (status) अणु
	हाल TA_SECUREDISPLAY_STATUS__SUCCESS:
		अवरोध;
	हाल TA_SECUREDISPLAY_STATUS__GENERIC_FAILURE:
		dev_err(psp->adev->dev, "Secure display: Generic Failure.");
		अवरोध;
	हाल TA_SECUREDISPLAY_STATUS__INVALID_PARAMETER:
		dev_err(psp->adev->dev, "Secure display: Invalid Parameter.");
		अवरोध;
	हाल TA_SECUREDISPLAY_STATUS__शून्य_POINTER:
		dev_err(psp->adev->dev, "Secure display: Null Pointer.");
		अवरोध;
	हाल TA_SECUREDISPLAY_STATUS__I2C_WRITE_ERROR:
		dev_err(psp->adev->dev, "Secure display: Failed to write to I2C.");
		अवरोध;
	हाल TA_SECUREDISPLAY_STATUS__READ_DIO_SCRATCH_ERROR:
		dev_err(psp->adev->dev, "Secure display: Failed to Read DIO Scratch Register.");
		अवरोध;
	हाल TA_SECUREDISPLAY_STATUS__READ_CRC_ERROR:
		dev_err(psp->adev->dev, "Secure display: Failed to Read CRC");
		अवरोध;
	हाल TA_SECUREDISPLAY_STATUS__I2C_INIT_ERROR:
		dev_err(psp->adev->dev, "Secure display: Failed to initialize I2C.");
		अवरोध;
	शेष:
		dev_err(psp->adev->dev, "Secure display: Failed to parse status: %d\n", status);
	पूर्ण
पूर्ण

व्योम psp_prep_securedisplay_cmd_buf(काष्ठा psp_context *psp, काष्ठा securedisplay_cmd **cmd,
	क्रमागत ta_securedisplay_command command_id)
अणु
	*cmd = (काष्ठा securedisplay_cmd *)psp->securedisplay_context.securedisplay_shared_buf;
	स_रखो(*cmd, 0, माप(काष्ठा securedisplay_cmd));
	(*cmd)->status = TA_SECUREDISPLAY_STATUS__GENERIC_FAILURE;
	(*cmd)->cmd_id = command_id;
पूर्ण

अटल sमाप_प्रकार amdgpu_securedisplay_debugfs_ग_लिखो(काष्ठा file *f, स्थिर अक्षर __user *buf,
		माप_प्रकार size, loff_t *pos)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)file_inode(f)->i_निजी;
	काष्ठा psp_context *psp = &adev->psp;
	काष्ठा securedisplay_cmd *securedisplay_cmd;
	काष्ठा drm_device *dev = adev_to_drm(adev);
	uपूर्णांक32_t phy_id;
	uपूर्णांक32_t op;
	अक्षर str[64];
	पूर्णांक ret;

	अगर (*pos || size > माप(str) - 1)
		वापस -EINVAL;

	स_रखो(str,  0, माप(str));
	ret = copy_from_user(str, buf, size);
	अगर (ret)
		वापस -EFAULT;

	ret = pm_runसमय_get_sync(dev->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_स्वतःsuspend(dev->dev);
		वापस ret;
	पूर्ण

	अगर (size < 3)
		माला_पूछो(str, "%u ", &op);
	अन्यथा
		माला_पूछो(str, "%u %u", &op, &phy_id);

	चयन (op) अणु
	हाल 1:
		psp_prep_securedisplay_cmd_buf(psp, &securedisplay_cmd,
			TA_SECUREDISPLAY_COMMAND__QUERY_TA);
		ret = psp_securedisplay_invoke(psp, TA_SECUREDISPLAY_COMMAND__QUERY_TA);
		अगर (!ret) अणु
			अगर (securedisplay_cmd->status == TA_SECUREDISPLAY_STATUS__SUCCESS)
				dev_info(adev->dev, "SECUREDISPLAY: query securedisplay TA ret is 0x%X\n",
					securedisplay_cmd->securedisplay_out_message.query_ta.query_cmd_ret);
			अन्यथा
				psp_securedisplay_parse_resp_status(psp, securedisplay_cmd->status);
		पूर्ण
		अवरोध;
	हाल 2:
		psp_prep_securedisplay_cmd_buf(psp, &securedisplay_cmd,
			TA_SECUREDISPLAY_COMMAND__SEND_ROI_CRC);
		securedisplay_cmd->securedisplay_in_message.send_roi_crc.phy_id = phy_id;
		ret = psp_securedisplay_invoke(psp, TA_SECUREDISPLAY_COMMAND__SEND_ROI_CRC);
		अगर (!ret) अणु
			अगर (securedisplay_cmd->status == TA_SECUREDISPLAY_STATUS__SUCCESS) अणु
				dev_info(adev->dev, "SECUREDISPLAY: I2C buffer out put is: %*ph\n",
					 TA_SECUREDISPLAY_I2C_BUFFER_SIZE,
					 securedisplay_cmd->securedisplay_out_message.send_roi_crc.i2c_buf);
			पूर्ण अन्यथा अणु
				psp_securedisplay_parse_resp_status(psp, securedisplay_cmd->status);
			पूर्ण
		पूर्ण
		अवरोध;
	शेष:
		dev_err(adev->dev, "Invalid input: %s\n", str);
	पूर्ण

	pm_runसमय_mark_last_busy(dev->dev);
	pm_runसमय_put_स्वतःsuspend(dev->dev);

	वापस size;
पूर्ण

अटल स्थिर काष्ठा file_operations amdgpu_securedisplay_debugfs_ops = अणु
	.owner = THIS_MODULE,
	.पढ़ो = शून्य,
	.ग_लिखो = amdgpu_securedisplay_debugfs_ग_लिखो,
	.llseek = शेष_llseek
पूर्ण;

व्योम amdgpu_securedisplay_debugfs_init(काष्ठा amdgpu_device *adev)
अणु
#अगर defined(CONFIG_DEBUG_FS)

	अगर (!adev->psp.securedisplay_context.securedisplay_initialized)
		वापस;

	debugfs_create_file("securedisplay_test", S_IWUSR, adev_to_drm(adev)->primary->debugfs_root,
				adev, &amdgpu_securedisplay_debugfs_ops);
#पूर्ण_अगर
पूर्ण
