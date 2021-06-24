<शैली गुरु>
/*
 * Copyright 2013 Advanced Micro Devices, Inc.
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
 * Authors: Alex Deucher
 */

#समावेश "radeon.h"
#समावेश "cikd.h"
#समावेश "kv_dpm.h"

पूर्णांक kv_notअगरy_message_to_smu(काष्ठा radeon_device *rdev, u32 id)
अणु
	u32 i;
	u32 पंचांगp = 0;

	WREG32(SMC_MESSAGE_0, id & SMC_MSG_MASK);

	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		अगर ((RREG32(SMC_RESP_0) & SMC_RESP_MASK) != 0)
			अवरोध;
		udelay(1);
	पूर्ण
	पंचांगp = RREG32(SMC_RESP_0) & SMC_RESP_MASK;

	अगर (पंचांगp != 1) अणु
		अगर (पंचांगp == 0xFF)
			वापस -EINVAL;
		अन्यथा अगर (पंचांगp == 0xFE)
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक kv_dpm_get_enable_mask(काष्ठा radeon_device *rdev, u32 *enable_mask)
अणु
	पूर्णांक ret;

	ret = kv_notअगरy_message_to_smu(rdev, PPSMC_MSG_SCLKDPM_GetEnabledMask);

	अगर (ret == 0)
		*enable_mask = RREG32_SMC(SMC_SYSCON_MSG_ARG_0);

	वापस ret;
पूर्ण

पूर्णांक kv_send_msg_to_smc_with_parameter(काष्ठा radeon_device *rdev,
				      PPSMC_Msg msg, u32 parameter)
अणु

	WREG32(SMC_MSG_ARG_0, parameter);

	वापस kv_notअगरy_message_to_smu(rdev, msg);
पूर्ण

अटल पूर्णांक kv_set_smc_sram_address(काष्ठा radeon_device *rdev,
				   u32 smc_address, u32 limit)
अणु
	अगर (smc_address & 3)
		वापस -EINVAL;
	अगर ((smc_address + 3) > limit)
		वापस -EINVAL;

	WREG32(SMC_IND_INDEX_0, smc_address);
	WREG32_P(SMC_IND_ACCESS_CNTL, 0, ~AUTO_INCREMENT_IND_0);

	वापस 0;
पूर्ण

पूर्णांक kv_पढ़ो_smc_sram_dword(काष्ठा radeon_device *rdev, u32 smc_address,
			   u32 *value, u32 limit)
अणु
	पूर्णांक ret;

	ret = kv_set_smc_sram_address(rdev, smc_address, limit);
	अगर (ret)
		वापस ret;

	*value = RREG32(SMC_IND_DATA_0);
	वापस 0;
पूर्ण

पूर्णांक kv_smc_dpm_enable(काष्ठा radeon_device *rdev, bool enable)
अणु
	अगर (enable)
		वापस kv_notअगरy_message_to_smu(rdev, PPSMC_MSG_DPM_Enable);
	अन्यथा
		वापस kv_notअगरy_message_to_smu(rdev, PPSMC_MSG_DPM_Disable);
पूर्ण

पूर्णांक kv_smc_bapm_enable(काष्ठा radeon_device *rdev, bool enable)
अणु
	अगर (enable)
		वापस kv_notअगरy_message_to_smu(rdev, PPSMC_MSG_EnableBAPM);
	अन्यथा
		वापस kv_notअगरy_message_to_smu(rdev, PPSMC_MSG_DisableBAPM);
पूर्ण

पूर्णांक kv_copy_bytes_to_smc(काष्ठा radeon_device *rdev,
			 u32 smc_start_address,
			 स्थिर u8 *src, u32 byte_count, u32 limit)
अणु
	पूर्णांक ret;
	u32 data, original_data, addr, extra_shअगरt, t_byte, count, mask;

	अगर ((smc_start_address + byte_count) > limit)
		वापस -EINVAL;

	addr = smc_start_address;
	t_byte = addr & 3;

	/* RMW क्रम the initial bytes */
	अगर  (t_byte != 0) अणु
		addr -= t_byte;

		ret = kv_set_smc_sram_address(rdev, addr, limit);
		अगर (ret)
			वापस ret;

		original_data = RREG32(SMC_IND_DATA_0);

		data = 0;
		mask = 0;
		count = 4;
		जबतक (count > 0) अणु
			अगर (t_byte > 0) अणु
				mask = (mask << 8) | 0xff;
				t_byte--;
			पूर्ण अन्यथा अगर (byte_count > 0) अणु
				data = (data << 8) + *src++;
				byte_count--;
				mask <<= 8;
			पूर्ण अन्यथा अणु
				data <<= 8;
				mask = (mask << 8) | 0xff;
			पूर्ण
			count--;
		पूर्ण

		data |= original_data & mask;

		ret = kv_set_smc_sram_address(rdev, addr, limit);
		अगर (ret)
			वापस ret;

		WREG32(SMC_IND_DATA_0, data);

		addr += 4;
	पूर्ण

	जबतक (byte_count >= 4) अणु
		/* SMC address space is BE */
		data = (src[0] << 24) + (src[1] << 16) + (src[2] << 8) + src[3];

		ret = kv_set_smc_sram_address(rdev, addr, limit);
		अगर (ret)
			वापस ret;

		WREG32(SMC_IND_DATA_0, data);

		src += 4;
		byte_count -= 4;
		addr += 4;
	पूर्ण

	/* RMW क्रम the final bytes */
	अगर (byte_count > 0) अणु
		data = 0;

		ret = kv_set_smc_sram_address(rdev, addr, limit);
		अगर (ret)
			वापस ret;

		original_data= RREG32(SMC_IND_DATA_0);

		extra_shअगरt = 8 * (4 - byte_count);

		जबतक (byte_count > 0) अणु
			/* SMC address space is BE */
			data = (data << 8) + *src++;
			byte_count--;
		पूर्ण

		data <<= extra_shअगरt;

		data |= (original_data & ~((~0UL) << extra_shअगरt));

		ret = kv_set_smc_sram_address(rdev, addr, limit);
		अगर (ret)
			वापस ret;

		WREG32(SMC_IND_DATA_0, data);
	पूर्ण
	वापस 0;
पूर्ण

