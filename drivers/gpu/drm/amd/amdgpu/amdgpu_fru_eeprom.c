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
#समावेश <linux/pci.h>

#समावेश "amdgpu.h"
#समावेश "amdgpu_i2c.h"
#समावेश "smu_v11_0_i2c.h"
#समावेश "atom.h"
#समावेश "amdgpu_fru_eeprom.h"

#घोषणा I2C_PRODUCT_INFO_ADDR		0xAC
#घोषणा I2C_PRODUCT_INFO_ADDR_SIZE	0x2
#घोषणा I2C_PRODUCT_INFO_OFFSET		0xC0

अटल bool is_fru_eeprom_supported(काष्ठा amdgpu_device *adev)
अणु
	/* Only server cards have the FRU EEPROM
	 * TODO: See अगर we can figure this out dynamically instead of
	 * having to parse VBIOS versions.
	 */
	काष्ठा atom_context *atom_ctx = adev->mode_info.atom_context;

	/* VBIOS is of the क्रमmat ###-DXXXYY-##. For SKU identअगरication,
	 * we can use just the "DXXX" portion. If there were more models, we
	 * could convert the 3 अक्षरacters to a hex पूर्णांकeger and use a चयन
	 * क्रम ease/speed/पढ़ोability. For now, 2 string comparisons are
	 * reasonable and not too expensive
	 */
	चयन (adev->asic_type) अणु
	हाल CHIP_VEGA20:
		/* D161 and D163 are the VG20 server SKUs */
		अगर (strnstr(atom_ctx->vbios_version, "D161",
			    माप(atom_ctx->vbios_version)) ||
		    strnstr(atom_ctx->vbios_version, "D163",
			    माप(atom_ctx->vbios_version)))
			वापस true;
		अन्यथा
			वापस false;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक amdgpu_fru_पढ़ो_eeprom(काष्ठा amdgpu_device *adev, uपूर्णांक32_t addrptr,
			   अचिन्हित अक्षर *buff)
अणु
	पूर्णांक ret, size;
	काष्ठा i2c_msg msg = अणु
			.addr   = I2C_PRODUCT_INFO_ADDR,
			.flags  = I2C_M_RD,
			.buf    = buff,
	पूर्ण;
	buff[0] = 0;
	buff[1] = addrptr;
	msg.len = I2C_PRODUCT_INFO_ADDR_SIZE + 1;
	ret = i2c_transfer(&adev->pm.smu_i2c, &msg, 1);

	अगर (ret < 1) अणु
		DRM_WARN("FRU: Failed to get size field");
		वापस ret;
	पूर्ण

	/* The size वापसed by the i2c requires subtraction of 0xC0 since the
	 * size apparently always reports as 0xC0+actual size.
	 */
	size = buff[2] - I2C_PRODUCT_INFO_OFFSET;
	/* Add 1 since address field was 1 byte */
	buff[1] = addrptr + 1;

	msg.len = I2C_PRODUCT_INFO_ADDR_SIZE + size;
	ret = i2c_transfer(&adev->pm.smu_i2c, &msg, 1);

	अगर (ret < 1) अणु
		DRM_WARN("FRU: Failed to get data field");
		वापस ret;
	पूर्ण

	वापस size;
पूर्ण

पूर्णांक amdgpu_fru_get_product_info(काष्ठा amdgpu_device *adev)
अणु
	अचिन्हित अक्षर buff[34];
	पूर्णांक addrptr, size;
	पूर्णांक len;

	अगर (!is_fru_eeprom_supported(adev))
		वापस 0;

	/* If algo exists, it means that the i2c_adapter's initialized */
	अगर (!adev->pm.smu_i2c.algo) अणु
		DRM_WARN("Cannot access FRU, EEPROM accessor not initialized");
		वापस -ENODEV;
	पूर्ण

	/* There's a lot of repetition here. This is due to the FRU having
	 * variable-length fields. To get the inक्रमmation, we have to find the
	 * size of each field, and then keep पढ़ोing aदीर्घ and पढ़ोing aदीर्घ
	 * until we get all of the data that we want. We use addrptr to track
	 * the address as we go
	 */

	/* The first fields are all of size 1-byte, from 0-7 are offsets that
	 * contain inक्रमmation that isn't useful to us.
	 * Bytes 8-a are all 1-byte and refer to the size of the entire काष्ठा,
	 * and the language field, so just start from 0xb, manufacturer size
	 */
	addrptr = 0xb;
	size = amdgpu_fru_पढ़ो_eeprom(adev, addrptr, buff);
	अगर (size < 1) अणु
		DRM_ERROR("Failed to read FRU Manufacturer, ret:%d", size);
		वापस -EINVAL;
	पूर्ण

	/* Increment the addrptr by the size of the field, and 1 due to the
	 * size field being 1 byte. This pattern जारीs below.
	 */
	addrptr += size + 1;
	size = amdgpu_fru_पढ़ो_eeprom(adev, addrptr, buff);
	अगर (size < 1) अणु
		DRM_ERROR("Failed to read FRU product name, ret:%d", size);
		वापस -EINVAL;
	पूर्ण

	len = size;
	/* Product name should only be 32 अक्षरacters. Any more,
	 * and something could be wrong. Cap it at 32 to be safe
	 */
	अगर (len >= माप(adev->product_name)) अणु
		DRM_WARN("FRU Product Number is larger than 32 characters. This is likely a mistake");
		len = माप(adev->product_name) - 1;
	पूर्ण
	/* Start at 2 due to buff using fields 0 and 1 क्रम the address */
	स_नकल(adev->product_name, &buff[2], len);
	adev->product_name[len] = '\0';

	addrptr += size + 1;
	size = amdgpu_fru_पढ़ो_eeprom(adev, addrptr, buff);
	अगर (size < 1) अणु
		DRM_ERROR("Failed to read FRU product number, ret:%d", size);
		वापस -EINVAL;
	पूर्ण

	len = size;
	/* Product number should only be 16 अक्षरacters. Any more,
	 * and something could be wrong. Cap it at 16 to be safe
	 */
	अगर (len >= माप(adev->product_number)) अणु
		DRM_WARN("FRU Product Number is larger than 16 characters. This is likely a mistake");
		len = माप(adev->product_number) - 1;
	पूर्ण
	स_नकल(adev->product_number, &buff[2], len);
	adev->product_number[len] = '\0';

	addrptr += size + 1;
	size = amdgpu_fru_पढ़ो_eeprom(adev, addrptr, buff);

	अगर (size < 1) अणु
		DRM_ERROR("Failed to read FRU product version, ret:%d", size);
		वापस -EINVAL;
	पूर्ण

	addrptr += size + 1;
	size = amdgpu_fru_पढ़ो_eeprom(adev, addrptr, buff);

	अगर (size < 1) अणु
		DRM_ERROR("Failed to read FRU serial number, ret:%d", size);
		वापस -EINVAL;
	पूर्ण

	len = size;
	/* Serial number should only be 16 अक्षरacters. Any more,
	 * and something could be wrong. Cap it at 16 to be safe
	 */
	अगर (len >= माप(adev->serial)) अणु
		DRM_WARN("FRU Serial Number is larger than 16 characters. This is likely a mistake");
		len = माप(adev->serial) - 1;
	पूर्ण
	स_नकल(adev->serial, &buff[2], len);
	adev->serial[len] = '\0';

	वापस 0;
पूर्ण
