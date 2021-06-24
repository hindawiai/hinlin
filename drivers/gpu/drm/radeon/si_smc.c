<शैली गुरु>
/*
 * Copyright 2011 Advanced Micro Devices, Inc.
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

#समावेश <linux/firmware.h>

#समावेश "radeon.h"
#समावेश "sid.h"
#समावेश "ppsmc.h"
#समावेश "radeon_ucode.h"
#समावेश "sislands_smc.h"

अटल पूर्णांक si_set_smc_sram_address(काष्ठा radeon_device *rdev,
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

पूर्णांक si_copy_bytes_to_smc(काष्ठा radeon_device *rdev,
			 u32 smc_start_address,
			 स्थिर u8 *src, u32 byte_count, u32 limit)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;
	u32 data, original_data, addr, extra_shअगरt;

	अगर (smc_start_address & 3)
		वापस -EINVAL;
	अगर ((smc_start_address + byte_count) > limit)
		वापस -EINVAL;

	addr = smc_start_address;

	spin_lock_irqsave(&rdev->smc_idx_lock, flags);
	जबतक (byte_count >= 4) अणु
		/* SMC address space is BE */
		data = (src[0] << 24) | (src[1] << 16) | (src[2] << 8) | src[3];

		ret = si_set_smc_sram_address(rdev, addr, limit);
		अगर (ret)
			जाओ करोne;

		WREG32(SMC_IND_DATA_0, data);

		src += 4;
		byte_count -= 4;
		addr += 4;
	पूर्ण

	/* RMW क्रम the final bytes */
	अगर (byte_count > 0) अणु
		data = 0;

		ret = si_set_smc_sram_address(rdev, addr, limit);
		अगर (ret)
			जाओ करोne;

		original_data = RREG32(SMC_IND_DATA_0);

		extra_shअगरt = 8 * (4 - byte_count);

		जबतक (byte_count > 0) अणु
			/* SMC address space is BE */
			data = (data << 8) + *src++;
			byte_count--;
		पूर्ण

		data <<= extra_shअगरt;

		data |= (original_data & ~((~0UL) << extra_shअगरt));

		ret = si_set_smc_sram_address(rdev, addr, limit);
		अगर (ret)
			जाओ करोne;

		WREG32(SMC_IND_DATA_0, data);
	पूर्ण

करोne:
	spin_unlock_irqrestore(&rdev->smc_idx_lock, flags);

	वापस ret;
पूर्ण

व्योम si_start_smc(काष्ठा radeon_device *rdev)
अणु
	u32 पंचांगp = RREG32_SMC(SMC_SYSCON_RESET_CNTL);

	पंचांगp &= ~RST_REG;

	WREG32_SMC(SMC_SYSCON_RESET_CNTL, पंचांगp);
पूर्ण

व्योम si_reset_smc(काष्ठा radeon_device *rdev)
अणु
	u32 पंचांगp;

	RREG32(CB_CGTT_SCLK_CTRL);
	RREG32(CB_CGTT_SCLK_CTRL);
	RREG32(CB_CGTT_SCLK_CTRL);
	RREG32(CB_CGTT_SCLK_CTRL);

	पंचांगp = RREG32_SMC(SMC_SYSCON_RESET_CNTL);
	पंचांगp |= RST_REG;
	WREG32_SMC(SMC_SYSCON_RESET_CNTL, पंचांगp);
पूर्ण

पूर्णांक si_program_jump_on_start(काष्ठा radeon_device *rdev)
अणु
	अटल स्थिर u8 data[] = अणु 0x0E, 0x00, 0x40, 0x40 पूर्ण;

	वापस si_copy_bytes_to_smc(rdev, 0x0, data, 4, माप(data)+1);
पूर्ण

व्योम si_stop_smc_घड़ी(काष्ठा radeon_device *rdev)
अणु
	u32 पंचांगp = RREG32_SMC(SMC_SYSCON_CLOCK_CNTL_0);

	पंचांगp |= CK_DISABLE;

	WREG32_SMC(SMC_SYSCON_CLOCK_CNTL_0, पंचांगp);
पूर्ण

व्योम si_start_smc_घड़ी(काष्ठा radeon_device *rdev)
अणु
	u32 पंचांगp = RREG32_SMC(SMC_SYSCON_CLOCK_CNTL_0);

	पंचांगp &= ~CK_DISABLE;

	WREG32_SMC(SMC_SYSCON_CLOCK_CNTL_0, पंचांगp);
पूर्ण

bool si_is_smc_running(काष्ठा radeon_device *rdev)
अणु
	u32 rst = RREG32_SMC(SMC_SYSCON_RESET_CNTL);
	u32 clk = RREG32_SMC(SMC_SYSCON_CLOCK_CNTL_0);

	अगर (!(rst & RST_REG) && !(clk & CK_DISABLE))
		वापस true;

	वापस false;
पूर्ण

PPSMC_Result si_send_msg_to_smc(काष्ठा radeon_device *rdev, PPSMC_Msg msg)
अणु
	u32 पंचांगp;
	पूर्णांक i;

	अगर (!si_is_smc_running(rdev))
		वापस PPSMC_Result_Failed;

	WREG32(SMC_MESSAGE_0, msg);

	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		पंचांगp = RREG32(SMC_RESP_0);
		अगर (पंचांगp != 0)
			अवरोध;
		udelay(1);
	पूर्ण
	पंचांगp = RREG32(SMC_RESP_0);

	वापस (PPSMC_Result)पंचांगp;
पूर्ण

PPSMC_Result si_रुको_क्रम_smc_inactive(काष्ठा radeon_device *rdev)
अणु
	u32 पंचांगp;
	पूर्णांक i;

	अगर (!si_is_smc_running(rdev))
		वापस PPSMC_Result_OK;

	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		पंचांगp = RREG32_SMC(SMC_SYSCON_CLOCK_CNTL_0);
		अगर ((पंचांगp & CKEN) == 0)
			अवरोध;
		udelay(1);
	पूर्ण

	वापस PPSMC_Result_OK;
पूर्ण

पूर्णांक si_load_smc_ucode(काष्ठा radeon_device *rdev, u32 limit)
अणु
	अचिन्हित दीर्घ flags;
	u32 ucode_start_address;
	u32 ucode_size;
	स्थिर u8 *src;
	u32 data;

	अगर (!rdev->smc_fw)
		वापस -EINVAL;

	अगर (rdev->new_fw) अणु
		स्थिर काष्ठा smc_firmware_header_v1_0 *hdr =
			(स्थिर काष्ठा smc_firmware_header_v1_0 *)rdev->smc_fw->data;

		radeon_ucode_prपूर्णांक_smc_hdr(&hdr->header);

		ucode_start_address = le32_to_cpu(hdr->ucode_start_addr);
		ucode_size = le32_to_cpu(hdr->header.ucode_size_bytes);
		src = (स्थिर u8 *)
			(rdev->smc_fw->data + le32_to_cpu(hdr->header.ucode_array_offset_bytes));
	पूर्ण अन्यथा अणु
		चयन (rdev->family) अणु
		हाल CHIP_TAHITI:
			ucode_start_address = TAHITI_SMC_UCODE_START;
			ucode_size = TAHITI_SMC_UCODE_SIZE;
			अवरोध;
		हाल CHIP_PITCAIRN:
			ucode_start_address = PITCAIRN_SMC_UCODE_START;
			ucode_size = PITCAIRN_SMC_UCODE_SIZE;
			अवरोध;
		हाल CHIP_VERDE:
			ucode_start_address = VERDE_SMC_UCODE_START;
			ucode_size = VERDE_SMC_UCODE_SIZE;
			अवरोध;
		हाल CHIP_OLAND:
			ucode_start_address = OLAND_SMC_UCODE_START;
			ucode_size = OLAND_SMC_UCODE_SIZE;
			अवरोध;
		हाल CHIP_HAIन_अंक:
			ucode_start_address = HAIन_अंक_SMC_UCODE_START;
			ucode_size = HAIन_अंक_SMC_UCODE_SIZE;
			अवरोध;
		शेष:
			DRM_ERROR("unknown asic in smc ucode loader\n");
			BUG();
		पूर्ण
		src = (स्थिर u8 *)rdev->smc_fw->data;
	पूर्ण

	अगर (ucode_size & 3)
		वापस -EINVAL;

	spin_lock_irqsave(&rdev->smc_idx_lock, flags);
	WREG32(SMC_IND_INDEX_0, ucode_start_address);
	WREG32_P(SMC_IND_ACCESS_CNTL, AUTO_INCREMENT_IND_0, ~AUTO_INCREMENT_IND_0);
	जबतक (ucode_size >= 4) अणु
		/* SMC address space is BE */
		data = (src[0] << 24) | (src[1] << 16) | (src[2] << 8) | src[3];

		WREG32(SMC_IND_DATA_0, data);

		src += 4;
		ucode_size -= 4;
	पूर्ण
	WREG32_P(SMC_IND_ACCESS_CNTL, 0, ~AUTO_INCREMENT_IND_0);
	spin_unlock_irqrestore(&rdev->smc_idx_lock, flags);

	वापस 0;
पूर्ण

पूर्णांक si_पढ़ो_smc_sram_dword(काष्ठा radeon_device *rdev, u32 smc_address,
			   u32 *value, u32 limit)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&rdev->smc_idx_lock, flags);
	ret = si_set_smc_sram_address(rdev, smc_address, limit);
	अगर (ret == 0)
		*value = RREG32(SMC_IND_DATA_0);
	spin_unlock_irqrestore(&rdev->smc_idx_lock, flags);

	वापस ret;
पूर्ण

पूर्णांक si_ग_लिखो_smc_sram_dword(काष्ठा radeon_device *rdev, u32 smc_address,
			    u32 value, u32 limit)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&rdev->smc_idx_lock, flags);
	ret = si_set_smc_sram_address(rdev, smc_address, limit);
	अगर (ret == 0)
		WREG32(SMC_IND_DATA_0, value);
	spin_unlock_irqrestore(&rdev->smc_idx_lock, flags);

	वापस ret;
पूर्ण
