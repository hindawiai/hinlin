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

#समावेश <linux/slab.h>
#समावेश <linux/delay.h>

#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_scdc_helper.h>

/**
 * DOC: scdc helpers
 *
 * Status and Control Data Channel (SCDC) is a mechanism पूर्णांकroduced by the
 * HDMI 2.0 specअगरication. It is a poपूर्णांक-to-poपूर्णांक protocol that allows the
 * HDMI source and HDMI sink to exchange data. The same I2C पूर्णांकerface that
 * is used to access EDID serves as the transport mechanism क्रम SCDC.
 */

#घोषणा SCDC_I2C_SLAVE_ADDRESS 0x54

/**
 * drm_scdc_पढ़ो - पढ़ो a block of data from SCDC
 * @adapter: I2C controller
 * @offset: start offset of block to पढ़ो
 * @buffer: वापस location क्रम the block to पढ़ो
 * @size: size of the block to पढ़ो
 *
 * Reads a block of data from SCDC, starting at a given offset.
 *
 * Returns:
 * 0 on success, negative error code on failure.
 */
sमाप_प्रकार drm_scdc_पढ़ो(काष्ठा i2c_adapter *adapter, u8 offset, व्योम *buffer,
		      माप_प्रकार size)
अणु
	पूर्णांक ret;
	काष्ठा i2c_msg msgs[2] = अणु
		अणु
			.addr = SCDC_I2C_SLAVE_ADDRESS,
			.flags = 0,
			.len = 1,
			.buf = &offset,
		पूर्ण, अणु
			.addr = SCDC_I2C_SLAVE_ADDRESS,
			.flags = I2C_M_RD,
			.len = size,
			.buf = buffer,
		पूर्ण
	पूर्ण;

	ret = i2c_transfer(adapter, msgs, ARRAY_SIZE(msgs));
	अगर (ret < 0)
		वापस ret;
	अगर (ret != ARRAY_SIZE(msgs))
		वापस -EPROTO;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_scdc_पढ़ो);

/**
 * drm_scdc_ग_लिखो - ग_लिखो a block of data to SCDC
 * @adapter: I2C controller
 * @offset: start offset of block to ग_लिखो
 * @buffer: block of data to ग_लिखो
 * @size: size of the block to ग_लिखो
 *
 * Writes a block of data to SCDC, starting at a given offset.
 *
 * Returns:
 * 0 on success, negative error code on failure.
 */
sमाप_प्रकार drm_scdc_ग_लिखो(काष्ठा i2c_adapter *adapter, u8 offset,
		       स्थिर व्योम *buffer, माप_प्रकार size)
अणु
	काष्ठा i2c_msg msg = अणु
		.addr = SCDC_I2C_SLAVE_ADDRESS,
		.flags = 0,
		.len = 1 + size,
		.buf = शून्य,
	पूर्ण;
	व्योम *data;
	पूर्णांक err;

	data = kदो_स्मृति(1 + size, GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	msg.buf = data;

	स_नकल(data, &offset, माप(offset));
	स_नकल(data + 1, buffer, size);

	err = i2c_transfer(adapter, &msg, 1);

	kमुक्त(data);

	अगर (err < 0)
		वापस err;
	अगर (err != 1)
		वापस -EPROTO;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_scdc_ग_लिखो);

/**
 * drm_scdc_get_scrambling_status - what is status of scrambling?
 * @adapter: I2C adapter क्रम DDC channel
 *
 * Reads the scrambler status over SCDC, and checks the
 * scrambling status.
 *
 * Returns:
 * True अगर the scrambling is enabled, false otherwise.
 */
bool drm_scdc_get_scrambling_status(काष्ठा i2c_adapter *adapter)
अणु
	u8 status;
	पूर्णांक ret;

	ret = drm_scdc_पढ़ोb(adapter, SCDC_SCRAMBLER_STATUS, &status);
	अगर (ret < 0) अणु
		DRM_DEBUG_KMS("Failed to read scrambling status: %d\n", ret);
		वापस false;
	पूर्ण

	वापस status & SCDC_SCRAMBLING_STATUS;
पूर्ण
EXPORT_SYMBOL(drm_scdc_get_scrambling_status);

/**
 * drm_scdc_set_scrambling - enable scrambling
 * @adapter: I2C adapter क्रम DDC channel
 * @enable: bool to indicate अगर scrambling is to be enabled/disabled
 *
 * Writes the TMDS config रेजिस्टर over SCDC channel, and:
 * enables scrambling when enable = 1
 * disables scrambling when enable = 0
 *
 * Returns:
 * True अगर scrambling is set/reset successfully, false otherwise.
 */
bool drm_scdc_set_scrambling(काष्ठा i2c_adapter *adapter, bool enable)
अणु
	u8 config;
	पूर्णांक ret;

	ret = drm_scdc_पढ़ोb(adapter, SCDC_TMDS_CONFIG, &config);
	अगर (ret < 0) अणु
		DRM_DEBUG_KMS("Failed to read TMDS config: %d\n", ret);
		वापस false;
	पूर्ण

	अगर (enable)
		config |= SCDC_SCRAMBLING_ENABLE;
	अन्यथा
		config &= ~SCDC_SCRAMBLING_ENABLE;

	ret = drm_scdc_ग_लिखोb(adapter, SCDC_TMDS_CONFIG, config);
	अगर (ret < 0) अणु
		DRM_DEBUG_KMS("Failed to enable scrambling: %d\n", ret);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण
EXPORT_SYMBOL(drm_scdc_set_scrambling);

/**
 * drm_scdc_set_high_पंचांगds_घड़ी_ratio - set TMDS घड़ी ratio
 * @adapter: I2C adapter क्रम DDC channel
 * @set: ret or reset the high घड़ी ratio
 *
 *
 *	TMDS घड़ी ratio calculations go like this:
 *		TMDS अक्षरacter = 10 bit TMDS encoded value
 *
 *		TMDS अक्षरacter rate = The rate at which TMDS अक्षरacters are
 *		transmitted (Mcsc)
 *
 *		TMDS bit rate = 10x TMDS अक्षरacter rate
 *
 *	As per the spec:
 *		TMDS घड़ी rate क्रम pixel घड़ी < 340 MHz = 1x the अक्षरacter
 *		rate = 1/10 pixel घड़ी rate
 *
 *		TMDS घड़ी rate क्रम pixel घड़ी > 340 MHz = 0.25x the अक्षरacter
 *		rate = 1/40 pixel घड़ी rate
 *
 *	Writes to the TMDS config रेजिस्टर over SCDC channel, and:
 *		sets TMDS घड़ी ratio to 1/40 when set = 1
 *
 *		sets TMDS घड़ी ratio to 1/10 when set = 0
 *
 * Returns:
 * True अगर ग_लिखो is successful, false otherwise.
 */
bool drm_scdc_set_high_पंचांगds_घड़ी_ratio(काष्ठा i2c_adapter *adapter, bool set)
अणु
	u8 config;
	पूर्णांक ret;

	ret = drm_scdc_पढ़ोb(adapter, SCDC_TMDS_CONFIG, &config);
	अगर (ret < 0) अणु
		DRM_DEBUG_KMS("Failed to read TMDS config: %d\n", ret);
		वापस false;
	पूर्ण

	अगर (set)
		config |= SCDC_TMDS_BIT_CLOCK_RATIO_BY_40;
	अन्यथा
		config &= ~SCDC_TMDS_BIT_CLOCK_RATIO_BY_40;

	ret = drm_scdc_ग_लिखोb(adapter, SCDC_TMDS_CONFIG, config);
	अगर (ret < 0) अणु
		DRM_DEBUG_KMS("Failed to set TMDS clock ratio: %d\n", ret);
		वापस false;
	पूर्ण

	/*
	 * The spec says that a source should रुको minimum 1ms and maximum
	 * 100ms after writing the TMDS config क्रम घड़ी ratio. Lets allow a
	 * रुको of upto 2ms here.
	 */
	usleep_range(1000, 2000);
	वापस true;
पूर्ण
EXPORT_SYMBOL(drm_scdc_set_high_पंचांगds_घड़ी_ratio);
