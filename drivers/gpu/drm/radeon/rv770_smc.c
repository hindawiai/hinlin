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
#समावेश "rv770d.h"
#समावेश "rv770_dpm.h"
#समावेश "rv770_smc.h"
#समावेश "atom.h"
#समावेश "radeon_ucode.h"

#घोषणा FIRST_SMC_INT_VECT_REG 0xFFD8
#घोषणा FIRST_INT_VECT_S19     0xFFC0

अटल स्थिर u8 rv770_smc_पूर्णांक_vectors[] =
अणु
	0x08, 0x10, 0x08, 0x10,
	0x08, 0x10, 0x08, 0x10,
	0x08, 0x10, 0x08, 0x10,
	0x08, 0x10, 0x08, 0x10,
	0x08, 0x10, 0x08, 0x10,
	0x08, 0x10, 0x08, 0x10,
	0x08, 0x10, 0x08, 0x10,
	0x08, 0x10, 0x08, 0x10,
	0x08, 0x10, 0x08, 0x10,
	0x08, 0x10, 0x08, 0x10,
	0x08, 0x10, 0x08, 0x10,
	0x08, 0x10, 0x08, 0x10,
	0x08, 0x10, 0x0C, 0xD7,
	0x08, 0x2B, 0x08, 0x10,
	0x03, 0x51, 0x03, 0x51,
	0x03, 0x51, 0x03, 0x51
पूर्ण;

अटल स्थिर u8 rv730_smc_पूर्णांक_vectors[] =
अणु
	0x08, 0x15, 0x08, 0x15,
	0x08, 0x15, 0x08, 0x15,
	0x08, 0x15, 0x08, 0x15,
	0x08, 0x15, 0x08, 0x15,
	0x08, 0x15, 0x08, 0x15,
	0x08, 0x15, 0x08, 0x15,
	0x08, 0x15, 0x08, 0x15,
	0x08, 0x15, 0x08, 0x15,
	0x08, 0x15, 0x08, 0x15,
	0x08, 0x15, 0x08, 0x15,
	0x08, 0x15, 0x08, 0x15,
	0x08, 0x15, 0x08, 0x15,
	0x08, 0x15, 0x0C, 0xBB,
	0x08, 0x30, 0x08, 0x15,
	0x03, 0x56, 0x03, 0x56,
	0x03, 0x56, 0x03, 0x56
पूर्ण;

अटल स्थिर u8 rv710_smc_पूर्णांक_vectors[] =
अणु
	0x08, 0x04, 0x08, 0x04,
	0x08, 0x04, 0x08, 0x04,
	0x08, 0x04, 0x08, 0x04,
	0x08, 0x04, 0x08, 0x04,
	0x08, 0x04, 0x08, 0x04,
	0x08, 0x04, 0x08, 0x04,
	0x08, 0x04, 0x08, 0x04,
	0x08, 0x04, 0x08, 0x04,
	0x08, 0x04, 0x08, 0x04,
	0x08, 0x04, 0x08, 0x04,
	0x08, 0x04, 0x08, 0x04,
	0x08, 0x04, 0x08, 0x04,
	0x08, 0x04, 0x0C, 0xCB,
	0x08, 0x1F, 0x08, 0x04,
	0x03, 0x51, 0x03, 0x51,
	0x03, 0x51, 0x03, 0x51
पूर्ण;

अटल स्थिर u8 rv740_smc_पूर्णांक_vectors[] =
अणु
	0x08, 0x10, 0x08, 0x10,
	0x08, 0x10, 0x08, 0x10,
	0x08, 0x10, 0x08, 0x10,
	0x08, 0x10, 0x08, 0x10,
	0x08, 0x10, 0x08, 0x10,
	0x08, 0x10, 0x08, 0x10,
	0x08, 0x10, 0x08, 0x10,
	0x08, 0x10, 0x08, 0x10,
	0x08, 0x10, 0x08, 0x10,
	0x08, 0x10, 0x08, 0x10,
	0x08, 0x10, 0x08, 0x10,
	0x08, 0x10, 0x08, 0x10,
	0x08, 0x10, 0x0C, 0xD7,
	0x08, 0x2B, 0x08, 0x10,
	0x03, 0x51, 0x03, 0x51,
	0x03, 0x51, 0x03, 0x51
पूर्ण;

अटल स्थिर u8 cedar_smc_पूर्णांक_vectors[] =
अणु
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x11, 0x8B,
	0x0B, 0x20, 0x0B, 0x05,
	0x04, 0xF6, 0x04, 0xF6,
	0x04, 0xF6, 0x04, 0xF6
पूर्ण;

अटल स्थिर u8 redwood_smc_पूर्णांक_vectors[] =
अणु
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x11, 0x8B,
	0x0B, 0x20, 0x0B, 0x05,
	0x04, 0xF6, 0x04, 0xF6,
	0x04, 0xF6, 0x04, 0xF6
पूर्ण;

अटल स्थिर u8 juniper_smc_पूर्णांक_vectors[] =
अणु
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x11, 0x8B,
	0x0B, 0x20, 0x0B, 0x05,
	0x04, 0xF6, 0x04, 0xF6,
	0x04, 0xF6, 0x04, 0xF6
पूर्ण;

अटल स्थिर u8 cypress_smc_पूर्णांक_vectors[] =
अणु
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x11, 0x8B,
	0x0B, 0x20, 0x0B, 0x05,
	0x04, 0xF6, 0x04, 0xF6,
	0x04, 0xF6, 0x04, 0xF6
पूर्ण;

अटल स्थिर u8 barts_smc_पूर्णांक_vectors[] =
अणु
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x12, 0xAA,
	0x0C, 0x2F, 0x15, 0xF6,
	0x15, 0xF6, 0x05, 0x0A,
	0x05, 0x0A, 0x05, 0x0A
पूर्ण;

अटल स्थिर u8 turks_smc_पूर्णांक_vectors[] =
अणु
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x12, 0xAA,
	0x0C, 0x2F, 0x15, 0xF6,
	0x15, 0xF6, 0x05, 0x0A,
	0x05, 0x0A, 0x05, 0x0A
पूर्ण;

अटल स्थिर u8 caicos_smc_पूर्णांक_vectors[] =
अणु
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x12, 0xAA,
	0x0C, 0x2F, 0x15, 0xF6,
	0x15, 0xF6, 0x05, 0x0A,
	0x05, 0x0A, 0x05, 0x0A
पूर्ण;

अटल स्थिर u8 cayman_smc_पूर्णांक_vectors[] =
अणु
	0x12, 0x05, 0x12, 0x05,
	0x12, 0x05, 0x12, 0x05,
	0x12, 0x05, 0x12, 0x05,
	0x12, 0x05, 0x12, 0x05,
	0x12, 0x05, 0x12, 0x05,
	0x12, 0x05, 0x12, 0x05,
	0x12, 0x05, 0x12, 0x05,
	0x12, 0x05, 0x12, 0x05,
	0x12, 0x05, 0x12, 0x05,
	0x12, 0x05, 0x12, 0x05,
	0x12, 0x05, 0x12, 0x05,
	0x12, 0x05, 0x12, 0x05,
	0x12, 0x05, 0x18, 0xEA,
	0x12, 0x20, 0x1C, 0x34,
	0x1C, 0x34, 0x08, 0x72,
	0x08, 0x72, 0x08, 0x72
पूर्ण;

अटल पूर्णांक rv770_set_smc_sram_address(काष्ठा radeon_device *rdev,
				      u16 smc_address, u16 limit)
अणु
	u32 addr;

	अगर (smc_address & 3)
		वापस -EINVAL;
	अगर ((smc_address + 3) > limit)
		वापस -EINVAL;

	addr = smc_address;
	addr |= SMC_SRAM_AUTO_INC_DIS;

	WREG32(SMC_SRAM_ADDR, addr);

	वापस 0;
पूर्ण

पूर्णांक rv770_copy_bytes_to_smc(काष्ठा radeon_device *rdev,
			    u16 smc_start_address, स्थिर u8 *src,
			    u16 byte_count, u16 limit)
अणु
	अचिन्हित दीर्घ flags;
	u32 data, original_data, extra_shअगरt;
	u16 addr;
	पूर्णांक ret = 0;

	अगर (smc_start_address & 3)
		वापस -EINVAL;
	अगर ((smc_start_address + byte_count) > limit)
		वापस -EINVAL;

	addr = smc_start_address;

	spin_lock_irqsave(&rdev->smc_idx_lock, flags);
	जबतक (byte_count >= 4) अणु
		/* SMC address space is BE */
		data = (src[0] << 24) | (src[1] << 16) | (src[2] << 8) | src[3];

		ret = rv770_set_smc_sram_address(rdev, addr, limit);
		अगर (ret)
			जाओ करोne;

		WREG32(SMC_SRAM_DATA, data);

		src += 4;
		byte_count -= 4;
		addr += 4;
	पूर्ण

	/* RMW क्रम final bytes */
	अगर (byte_count > 0) अणु
		data = 0;

		ret = rv770_set_smc_sram_address(rdev, addr, limit);
		अगर (ret)
			जाओ करोne;

		original_data = RREG32(SMC_SRAM_DATA);

		extra_shअगरt = 8 * (4 - byte_count);

		जबतक (byte_count > 0) अणु
			/* SMC address space is BE */
			data = (data << 8) + *src++;
			byte_count--;
		पूर्ण

		data <<= extra_shअगरt;

		data |= (original_data & ~((~0UL) << extra_shअगरt));

		ret = rv770_set_smc_sram_address(rdev, addr, limit);
		अगर (ret)
			जाओ करोne;

		WREG32(SMC_SRAM_DATA, data);
	पूर्ण

करोne:
	spin_unlock_irqrestore(&rdev->smc_idx_lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक rv770_program_पूर्णांकerrupt_vectors(काष्ठा radeon_device *rdev,
					   u32 smc_first_vector, स्थिर u8 *src,
					   u32 byte_count)
अणु
	u32 पंचांगp, i;

	अगर (byte_count % 4)
		वापस -EINVAL;

	अगर (smc_first_vector < FIRST_SMC_INT_VECT_REG) अणु
		पंचांगp = FIRST_SMC_INT_VECT_REG - smc_first_vector;

		अगर (पंचांगp > byte_count)
			वापस 0;

		byte_count -= पंचांगp;
		src += पंचांगp;
		smc_first_vector = FIRST_SMC_INT_VECT_REG;
	पूर्ण

	क्रम (i = 0; i < byte_count; i += 4) अणु
		/* SMC address space is BE */
		पंचांगp = (src[i] << 24) | (src[i + 1] << 16) | (src[i + 2] << 8) | src[i + 3];

		WREG32(SMC_ISR_FFD8_FFDB + i, पंचांगp);
	पूर्ण

	वापस 0;
पूर्ण

व्योम rv770_start_smc(काष्ठा radeon_device *rdev)
अणु
	WREG32_P(SMC_IO, SMC_RST_N, ~SMC_RST_N);
पूर्ण

व्योम rv770_reset_smc(काष्ठा radeon_device *rdev)
अणु
	WREG32_P(SMC_IO, 0, ~SMC_RST_N);
पूर्ण

व्योम rv770_stop_smc_घड़ी(काष्ठा radeon_device *rdev)
अणु
	WREG32_P(SMC_IO, 0, ~SMC_CLK_EN);
पूर्ण

व्योम rv770_start_smc_घड़ी(काष्ठा radeon_device *rdev)
अणु
	WREG32_P(SMC_IO, SMC_CLK_EN, ~SMC_CLK_EN);
पूर्ण

bool rv770_is_smc_running(काष्ठा radeon_device *rdev)
अणु
	u32 पंचांगp;

	पंचांगp = RREG32(SMC_IO);

	अगर ((पंचांगp & SMC_RST_N) && (पंचांगp & SMC_CLK_EN))
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

PPSMC_Result rv770_send_msg_to_smc(काष्ठा radeon_device *rdev, PPSMC_Msg msg)
अणु
	u32 पंचांगp;
	पूर्णांक i;
	PPSMC_Result result;

	अगर (!rv770_is_smc_running(rdev))
		वापस PPSMC_Result_Failed;

	WREG32_P(SMC_MSG, HOST_SMC_MSG(msg), ~HOST_SMC_MSG_MASK);

	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		पंचांगp = RREG32(SMC_MSG) & HOST_SMC_RESP_MASK;
		पंचांगp >>= HOST_SMC_RESP_SHIFT;
		अगर (पंचांगp != 0)
			अवरोध;
		udelay(1);
	पूर्ण

	पंचांगp = RREG32(SMC_MSG) & HOST_SMC_RESP_MASK;
	पंचांगp >>= HOST_SMC_RESP_SHIFT;

	result = (PPSMC_Result)पंचांगp;
	वापस result;
पूर्ण

PPSMC_Result rv770_रुको_क्रम_smc_inactive(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक i;
	PPSMC_Result result = PPSMC_Result_OK;

	अगर (!rv770_is_smc_running(rdev))
		वापस result;

	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		अगर (RREG32(SMC_IO) & SMC_STOP_MODE)
			अवरोध;
		udelay(1);
	पूर्ण

	वापस result;
पूर्ण

अटल व्योम rv770_clear_smc_sram(काष्ठा radeon_device *rdev, u16 limit)
अणु
	अचिन्हित दीर्घ flags;
	u16 i;

	spin_lock_irqsave(&rdev->smc_idx_lock, flags);
	क्रम (i = 0;  i < limit; i += 4) अणु
		rv770_set_smc_sram_address(rdev, i, limit);
		WREG32(SMC_SRAM_DATA, 0);
	पूर्ण
	spin_unlock_irqrestore(&rdev->smc_idx_lock, flags);
पूर्ण

पूर्णांक rv770_load_smc_ucode(काष्ठा radeon_device *rdev,
			 u16 limit)
अणु
	पूर्णांक ret;
	स्थिर u8 *पूर्णांक_vect;
	u16 पूर्णांक_vect_start_address;
	u16 पूर्णांक_vect_size;
	स्थिर u8 *ucode_data;
	u16 ucode_start_address;
	u16 ucode_size;

	अगर (!rdev->smc_fw)
		वापस -EINVAL;

	rv770_clear_smc_sram(rdev, limit);

	चयन (rdev->family) अणु
	हाल CHIP_RV770:
		ucode_start_address = RV770_SMC_UCODE_START;
		ucode_size = RV770_SMC_UCODE_SIZE;
		पूर्णांक_vect = (स्थिर u8 *)&rv770_smc_पूर्णांक_vectors;
		पूर्णांक_vect_start_address = RV770_SMC_INT_VECTOR_START;
		पूर्णांक_vect_size = RV770_SMC_INT_VECTOR_SIZE;
		अवरोध;
	हाल CHIP_RV730:
		ucode_start_address = RV730_SMC_UCODE_START;
		ucode_size = RV730_SMC_UCODE_SIZE;
		पूर्णांक_vect = (स्थिर u8 *)&rv730_smc_पूर्णांक_vectors;
		पूर्णांक_vect_start_address = RV730_SMC_INT_VECTOR_START;
		पूर्णांक_vect_size = RV730_SMC_INT_VECTOR_SIZE;
		अवरोध;
	हाल CHIP_RV710:
		ucode_start_address = RV710_SMC_UCODE_START;
		ucode_size = RV710_SMC_UCODE_SIZE;
		पूर्णांक_vect = (स्थिर u8 *)&rv710_smc_पूर्णांक_vectors;
		पूर्णांक_vect_start_address = RV710_SMC_INT_VECTOR_START;
		पूर्णांक_vect_size = RV710_SMC_INT_VECTOR_SIZE;
		अवरोध;
	हाल CHIP_RV740:
		ucode_start_address = RV740_SMC_UCODE_START;
		ucode_size = RV740_SMC_UCODE_SIZE;
		पूर्णांक_vect = (स्थिर u8 *)&rv740_smc_पूर्णांक_vectors;
		पूर्णांक_vect_start_address = RV740_SMC_INT_VECTOR_START;
		पूर्णांक_vect_size = RV740_SMC_INT_VECTOR_SIZE;
		अवरोध;
	हाल CHIP_CEDAR:
		ucode_start_address = CEDAR_SMC_UCODE_START;
		ucode_size = CEDAR_SMC_UCODE_SIZE;
		पूर्णांक_vect = (स्थिर u8 *)&cedar_smc_पूर्णांक_vectors;
		पूर्णांक_vect_start_address = CEDAR_SMC_INT_VECTOR_START;
		पूर्णांक_vect_size = CEDAR_SMC_INT_VECTOR_SIZE;
		अवरोध;
	हाल CHIP_REDWOOD:
		ucode_start_address = REDWOOD_SMC_UCODE_START;
		ucode_size = REDWOOD_SMC_UCODE_SIZE;
		पूर्णांक_vect = (स्थिर u8 *)&redwood_smc_पूर्णांक_vectors;
		पूर्णांक_vect_start_address = REDWOOD_SMC_INT_VECTOR_START;
		पूर्णांक_vect_size = REDWOOD_SMC_INT_VECTOR_SIZE;
		अवरोध;
	हाल CHIP_JUNIPER:
		ucode_start_address = JUNIPER_SMC_UCODE_START;
		ucode_size = JUNIPER_SMC_UCODE_SIZE;
		पूर्णांक_vect = (स्थिर u8 *)&juniper_smc_पूर्णांक_vectors;
		पूर्णांक_vect_start_address = JUNIPER_SMC_INT_VECTOR_START;
		पूर्णांक_vect_size = JUNIPER_SMC_INT_VECTOR_SIZE;
		अवरोध;
	हाल CHIP_CYPRESS:
	हाल CHIP_HEMLOCK:
		ucode_start_address = CYPRESS_SMC_UCODE_START;
		ucode_size = CYPRESS_SMC_UCODE_SIZE;
		पूर्णांक_vect = (स्थिर u8 *)&cypress_smc_पूर्णांक_vectors;
		पूर्णांक_vect_start_address = CYPRESS_SMC_INT_VECTOR_START;
		पूर्णांक_vect_size = CYPRESS_SMC_INT_VECTOR_SIZE;
		अवरोध;
	हाल CHIP_BARTS:
		ucode_start_address = BARTS_SMC_UCODE_START;
		ucode_size = BARTS_SMC_UCODE_SIZE;
		पूर्णांक_vect = (स्थिर u8 *)&barts_smc_पूर्णांक_vectors;
		पूर्णांक_vect_start_address = BARTS_SMC_INT_VECTOR_START;
		पूर्णांक_vect_size = BARTS_SMC_INT_VECTOR_SIZE;
		अवरोध;
	हाल CHIP_TURKS:
		ucode_start_address = TURKS_SMC_UCODE_START;
		ucode_size = TURKS_SMC_UCODE_SIZE;
		पूर्णांक_vect = (स्थिर u8 *)&turks_smc_पूर्णांक_vectors;
		पूर्णांक_vect_start_address = TURKS_SMC_INT_VECTOR_START;
		पूर्णांक_vect_size = TURKS_SMC_INT_VECTOR_SIZE;
		अवरोध;
	हाल CHIP_CAICOS:
		ucode_start_address = CAICOS_SMC_UCODE_START;
		ucode_size = CAICOS_SMC_UCODE_SIZE;
		पूर्णांक_vect = (स्थिर u8 *)&caicos_smc_पूर्णांक_vectors;
		पूर्णांक_vect_start_address = CAICOS_SMC_INT_VECTOR_START;
		पूर्णांक_vect_size = CAICOS_SMC_INT_VECTOR_SIZE;
		अवरोध;
	हाल CHIP_CAYMAN:
		ucode_start_address = CAYMAN_SMC_UCODE_START;
		ucode_size = CAYMAN_SMC_UCODE_SIZE;
		पूर्णांक_vect = (स्थिर u8 *)&cayman_smc_पूर्णांक_vectors;
		पूर्णांक_vect_start_address = CAYMAN_SMC_INT_VECTOR_START;
		पूर्णांक_vect_size = CAYMAN_SMC_INT_VECTOR_SIZE;
		अवरोध;
	शेष:
		DRM_ERROR("unknown asic in smc ucode loader\n");
		BUG();
	पूर्ण

	/* load the ucode */
	ucode_data = (स्थिर u8 *)rdev->smc_fw->data;
	ret = rv770_copy_bytes_to_smc(rdev, ucode_start_address,
				      ucode_data, ucode_size, limit);
	अगर (ret)
		वापस ret;

	/* set up the पूर्णांक vectors */
	ret = rv770_program_पूर्णांकerrupt_vectors(rdev, पूर्णांक_vect_start_address,
					      पूर्णांक_vect, पूर्णांक_vect_size);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

पूर्णांक rv770_पढ़ो_smc_sram_dword(काष्ठा radeon_device *rdev,
			      u16 smc_address, u32 *value, u16 limit)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&rdev->smc_idx_lock, flags);
	ret = rv770_set_smc_sram_address(rdev, smc_address, limit);
	अगर (ret == 0)
		*value = RREG32(SMC_SRAM_DATA);
	spin_unlock_irqrestore(&rdev->smc_idx_lock, flags);

	वापस ret;
पूर्ण

पूर्णांक rv770_ग_लिखो_smc_sram_dword(काष्ठा radeon_device *rdev,
			       u16 smc_address, u32 value, u16 limit)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&rdev->smc_idx_lock, flags);
	ret = rv770_set_smc_sram_address(rdev, smc_address, limit);
	अगर (ret == 0)
		WREG32(SMC_SRAM_DATA, value);
	spin_unlock_irqrestore(&rdev->smc_idx_lock, flags);

	वापस ret;
पूर्ण
