<शैली गुरु>
/*
 * Copyright 2018 Advanced Micro Devices, Inc.
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

#समावेश "smumgr.h"
#समावेश "smu9_smumgr.h"
#समावेश "vega10_inc.h"
#समावेश "soc15_common.h"
#समावेश "pp_debug.h"


/* MP Apertures */
#घोषणा MP0_Public                  0x03800000
#घोषणा MP0_SRAM                    0x03900000
#घोषणा MP1_Public                  0x03b00000
#घोषणा MP1_SRAM                    0x03c00004

#घोषणा smnMP1_FIRMWARE_FLAGS                                                                           0x3010028

bool smu9_is_smc_ram_running(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	uपूर्णांक32_t mp1_fw_flags;

	mp1_fw_flags = RREG32_PCIE(MP1_Public |
				   (smnMP1_FIRMWARE_FLAGS & 0xffffffff));

	अगर (mp1_fw_flags & MP1_FIRMWARE_FLAGS__INTERRUPTS_ENABLED_MASK)
		वापस true;

	वापस false;
पूर्ण

/*
 * Check अगर SMC has responded to previous message.
 *
 * @param    smumgr  the address of the घातerplay hardware manager.
 * @वापस   TRUE    SMC has responded, FALSE otherwise.
 */
अटल uपूर्णांक32_t smu9_रुको_क्रम_response(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	uपूर्णांक32_t reg;
	uपूर्णांक32_t ret;

	अगर (hwmgr->pp_one_vf) अणु
		reg = SOC15_REG_OFFSET(MP1, 0, mmMP1_SMN_C2PMSG_103);

		ret = phm_रुको_क्रम_रेजिस्टर_unequal(hwmgr, reg,
				0, MP1_C2PMSG_103__CONTENT_MASK);

		अगर (ret)
			pr_err("No response from smu\n");

		वापस RREG32_SOC15(MP1, 0, mmMP1_SMN_C2PMSG_103);
	पूर्ण अन्यथा अणु
		reg = SOC15_REG_OFFSET(MP1, 0, mmMP1_SMN_C2PMSG_90);

		ret = phm_रुको_क्रम_रेजिस्टर_unequal(hwmgr, reg,
				0, MP1_C2PMSG_90__CONTENT_MASK);

		अगर (ret)
			pr_err("No response from smu\n");
		वापस RREG32_SOC15(MP1, 0, mmMP1_SMN_C2PMSG_90);
	पूर्ण
पूर्ण

/*
 * Send a message to the SMC, and करो not रुको क्रम its response.
 * @param    smumgr  the address of the घातerplay hardware manager.
 * @param    msg the message to send.
 * @वापस   Always वापस 0.
 */
अटल पूर्णांक smu9_send_msg_to_smc_without_रुकोing(काष्ठा pp_hwmgr *hwmgr,
						uपूर्णांक16_t msg)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;

	अगर (hwmgr->pp_one_vf) अणु
		WREG32_SOC15(MP1, 0, mmMP1_SMN_C2PMSG_101, msg);
	पूर्ण अन्यथा अणु
		WREG32_SOC15(MP1, 0, mmMP1_SMN_C2PMSG_66, msg);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Send a message to the SMC, and रुको क्रम its response.
 * @param    hwmgr  the address of the घातerplay hardware manager.
 * @param    msg the message to send.
 * @वापस   Always वापस 0.
 */
पूर्णांक smu9_send_msg_to_smc(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक16_t msg)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	uपूर्णांक32_t ret;

	smu9_रुको_क्रम_response(hwmgr);

	अगर (hwmgr->pp_one_vf)
		WREG32_SOC15(MP1, 0, mmMP1_SMN_C2PMSG_103, 0);
	अन्यथा
		WREG32_SOC15(MP1, 0, mmMP1_SMN_C2PMSG_90, 0);

	smu9_send_msg_to_smc_without_रुकोing(hwmgr, msg);

	ret = smu9_रुको_क्रम_response(hwmgr);
	अगर (ret != 1)
		pr_err("Failed to send message: 0x%x, ret value: 0x%x\n", msg, ret);

	वापस 0;
पूर्ण

/*
 * Send a message to the SMC with parameter
 * @param    hwmgr:  the address of the घातerplay hardware manager.
 * @param    msg: the message to send.
 * @param    parameter: the parameter to send
 * @वापस   Always वापस 0.
 */
पूर्णांक smu9_send_msg_to_smc_with_parameter(काष्ठा pp_hwmgr *hwmgr,
					uपूर्णांक16_t msg, uपूर्णांक32_t parameter)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	uपूर्णांक32_t ret;

	smu9_रुको_क्रम_response(hwmgr);

	अगर (hwmgr->pp_one_vf) अणु
		WREG32_SOC15(MP1, 0, mmMP1_SMN_C2PMSG_103, 0);
		WREG32_SOC15(MP1, 0, mmMP1_SMN_C2PMSG_102, parameter);
	पूर्ण अन्यथा अणु
		WREG32_SOC15(MP1, 0, mmMP1_SMN_C2PMSG_90, 0);
		WREG32_SOC15(MP1, 0, mmMP1_SMN_C2PMSG_82, parameter);
	पूर्ण

	smu9_send_msg_to_smc_without_रुकोing(hwmgr, msg);

	ret = smu9_रुको_क्रम_response(hwmgr);
	अगर (ret != 1)
		pr_err("Failed message: 0x%x, input parameter: 0x%x, error code: 0x%x\n", msg, parameter, ret);

	वापस 0;
पूर्ण

uपूर्णांक32_t smu9_get_argument(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;

	अगर (hwmgr->pp_one_vf)
		वापस RREG32_SOC15(MP1, 0, mmMP1_SMN_C2PMSG_102);
	अन्यथा
		वापस RREG32_SOC15(MP1, 0, mmMP1_SMN_C2PMSG_82);
पूर्ण
