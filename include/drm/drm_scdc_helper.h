<शैली गुरु>
/*
 * Copyright (c) 2015 NVIDIA Corporation. All rights reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sub license,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#अगर_अघोषित DRM_SCDC_HELPER_H
#घोषणा DRM_SCDC_HELPER_H

#समावेश <linux/i2c.h>
#समावेश <linux/types.h>

#घोषणा SCDC_SINK_VERSION 0x01

#घोषणा SCDC_SOURCE_VERSION 0x02

#घोषणा SCDC_UPDATE_0 0x10
#घोषणा  SCDC_READ_REQUEST_TEST (1 << 2)
#घोषणा  SCDC_CED_UPDATE (1 << 1)
#घोषणा  SCDC_STATUS_UPDATE (1 << 0)

#घोषणा SCDC_UPDATE_1 0x11

#घोषणा SCDC_TMDS_CONFIG 0x20
#घोषणा  SCDC_TMDS_BIT_CLOCK_RATIO_BY_40 (1 << 1)
#घोषणा  SCDC_TMDS_BIT_CLOCK_RATIO_BY_10 (0 << 1)
#घोषणा  SCDC_SCRAMBLING_ENABLE (1 << 0)

#घोषणा SCDC_SCRAMBLER_STATUS 0x21
#घोषणा  SCDC_SCRAMBLING_STATUS (1 << 0)

#घोषणा SCDC_CONFIG_0 0x30
#घोषणा  SCDC_READ_REQUEST_ENABLE (1 << 0)

#घोषणा SCDC_STATUS_FLAGS_0 0x40
#घोषणा  SCDC_CH2_LOCK (1 << 3)
#घोषणा  SCDC_CH1_LOCK (1 << 2)
#घोषणा  SCDC_CH0_LOCK (1 << 1)
#घोषणा  SCDC_CH_LOCK_MASK (SCDC_CH2_LOCK | SCDC_CH1_LOCK | SCDC_CH0_LOCK)
#घोषणा  SCDC_CLOCK_DETECT (1 << 0)

#घोषणा SCDC_STATUS_FLAGS_1 0x41

#घोषणा SCDC_ERR_DET_0_L 0x50
#घोषणा SCDC_ERR_DET_0_H 0x51
#घोषणा SCDC_ERR_DET_1_L 0x52
#घोषणा SCDC_ERR_DET_1_H 0x53
#घोषणा SCDC_ERR_DET_2_L 0x54
#घोषणा SCDC_ERR_DET_2_H 0x55
#घोषणा  SCDC_CHANNEL_VALID (1 << 7)

#घोषणा SCDC_ERR_DET_CHECKSUM 0x56

#घोषणा SCDC_TEST_CONFIG_0 0xc0
#घोषणा  SCDC_TEST_READ_REQUEST (1 << 7)
#घोषणा  SCDC_TEST_READ_REQUEST_DELAY(x) ((x) & 0x7f)

#घोषणा SCDC_MANUFACTURER_IEEE_OUI 0xd0
#घोषणा SCDC_MANUFACTURER_IEEE_OUI_SIZE 3

#घोषणा SCDC_DEVICE_ID 0xd3
#घोषणा SCDC_DEVICE_ID_SIZE 8

#घोषणा SCDC_DEVICE_HARDWARE_REVISION 0xdb
#घोषणा  SCDC_GET_DEVICE_HARDWARE_REVISION_MAJOR(x) (((x) >> 4) & 0xf)
#घोषणा  SCDC_GET_DEVICE_HARDWARE_REVISION_MINOR(x) (((x) >> 0) & 0xf)

#घोषणा SCDC_DEVICE_SOFTWARE_MAJOR_REVISION 0xdc
#घोषणा SCDC_DEVICE_SOFTWARE_MINOR_REVISION 0xdd

#घोषणा SCDC_MANUFACTURER_SPECIFIC 0xde
#घोषणा SCDC_MANUFACTURER_SPECIFIC_SIZE 34

sमाप_प्रकार drm_scdc_पढ़ो(काष्ठा i2c_adapter *adapter, u8 offset, व्योम *buffer,
		      माप_प्रकार size);
sमाप_प्रकार drm_scdc_ग_लिखो(काष्ठा i2c_adapter *adapter, u8 offset,
		       स्थिर व्योम *buffer, माप_प्रकार size);

/**
 * drm_scdc_पढ़ोb - पढ़ो a single byte from SCDC
 * @adapter: I2C adapter
 * @offset: offset of रेजिस्टर to पढ़ो
 * @value: वापस location क्रम the रेजिस्टर value
 *
 * Reads a single byte from SCDC. This is a convenience wrapper around the
 * drm_scdc_पढ़ो() function.
 *
 * Returns:
 * 0 on success or a negative error code on failure.
 */
अटल अंतरभूत पूर्णांक drm_scdc_पढ़ोb(काष्ठा i2c_adapter *adapter, u8 offset,
				 u8 *value)
अणु
	वापस drm_scdc_पढ़ो(adapter, offset, value, माप(*value));
पूर्ण

/**
 * drm_scdc_ग_लिखोb - ग_लिखो a single byte to SCDC
 * @adapter: I2C adapter
 * @offset: offset of रेजिस्टर to पढ़ो
 * @value: वापस location क्रम the रेजिस्टर value
 *
 * Writes a single byte to SCDC. This is a convenience wrapper around the
 * drm_scdc_ग_लिखो() function.
 *
 * Returns:
 * 0 on success or a negative error code on failure.
 */
अटल अंतरभूत पूर्णांक drm_scdc_ग_लिखोb(काष्ठा i2c_adapter *adapter, u8 offset,
				  u8 value)
अणु
	वापस drm_scdc_ग_लिखो(adapter, offset, &value, माप(value));
पूर्ण

bool drm_scdc_get_scrambling_status(काष्ठा i2c_adapter *adapter);

bool drm_scdc_set_scrambling(काष्ठा i2c_adapter *adapter, bool enable);
bool drm_scdc_set_high_पंचांगds_घड़ी_ratio(काष्ठा i2c_adapter *adapter, bool set);
#पूर्ण_अगर
