<शैली गुरु>
/*
 * Copyright तऊ 2016 Intel Corporation
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
 */

#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/export.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>

#समावेश <drm/drm_dp_dual_mode_helper.h>
#समावेश <drm/drm_prपूर्णांक.h>

/**
 * DOC: dp dual mode helpers
 *
 * Helper functions to deal with DP dual mode (aka. DP++) adaptors.
 *
 * Type 1:
 * Adaptor रेजिस्टरs (अगर any) and the sink DDC bus may be accessed via I2C.
 *
 * Type 2:
 * Adaptor रेजिस्टरs and sink DDC bus can be accessed either via I2C or
 * I2C-over-AUX. Source devices may choose to implement either of these
 * access methods.
 */

#घोषणा DP_DUAL_MODE_SLAVE_ADDRESS 0x40

/**
 * drm_dp_dual_mode_पढ़ो - Read from the DP dual mode adaptor रेजिस्टर(s)
 * @adapter: I2C adapter क्रम the DDC bus
 * @offset: रेजिस्टर offset
 * @buffer: buffer क्रम वापस data
 * @size: sizo of the buffer
 *
 * Reads @size bytes from the DP dual mode adaptor रेजिस्टरs
 * starting at @offset.
 *
 * Returns:
 * 0 on success, negative error code on failure
 */
sमाप_प्रकार drm_dp_dual_mode_पढ़ो(काष्ठा i2c_adapter *adapter,
			      u8 offset, व्योम *buffer, माप_प्रकार size)
अणु
	काष्ठा i2c_msg msgs[] = अणु
		अणु
			.addr = DP_DUAL_MODE_SLAVE_ADDRESS,
			.flags = 0,
			.len = 1,
			.buf = &offset,
		पूर्ण,
		अणु
			.addr = DP_DUAL_MODE_SLAVE_ADDRESS,
			.flags = I2C_M_RD,
			.len = size,
			.buf = buffer,
		पूर्ण,
	पूर्ण;
	पूर्णांक ret;

	ret = i2c_transfer(adapter, msgs, ARRAY_SIZE(msgs));
	अगर (ret < 0)
		वापस ret;
	अगर (ret != ARRAY_SIZE(msgs))
		वापस -EPROTO;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_dp_dual_mode_पढ़ो);

/**
 * drm_dp_dual_mode_ग_लिखो - Write to the DP dual mode adaptor रेजिस्टर(s)
 * @adapter: I2C adapter क्रम the DDC bus
 * @offset: रेजिस्टर offset
 * @buffer: buffer क्रम ग_लिखो data
 * @size: sizo of the buffer
 *
 * Writes @size bytes to the DP dual mode adaptor रेजिस्टरs
 * starting at @offset.
 *
 * Returns:
 * 0 on success, negative error code on failure
 */
sमाप_प्रकार drm_dp_dual_mode_ग_लिखो(काष्ठा i2c_adapter *adapter,
			       u8 offset, स्थिर व्योम *buffer, माप_प्रकार size)
अणु
	काष्ठा i2c_msg msg = अणु
		.addr = DP_DUAL_MODE_SLAVE_ADDRESS,
		.flags = 0,
		.len = 1 + size,
		.buf = शून्य,
	पूर्ण;
	व्योम *data;
	पूर्णांक ret;

	data = kदो_स्मृति(msg.len, GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	msg.buf = data;

	स_नकल(data, &offset, 1);
	स_नकल(data + 1, buffer, size);

	ret = i2c_transfer(adapter, &msg, 1);

	kमुक्त(data);

	अगर (ret < 0)
		वापस ret;
	अगर (ret != 1)
		वापस -EPROTO;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_dp_dual_mode_ग_लिखो);

अटल bool is_hdmi_adaptor(स्थिर अक्षर hdmi_id[DP_DUAL_MODE_HDMI_ID_LEN])
अणु
	अटल स्थिर अक्षर dp_dual_mode_hdmi_id[DP_DUAL_MODE_HDMI_ID_LEN] =
		"DP-HDMI ADAPTOR\x04";

	वापस स_भेद(hdmi_id, dp_dual_mode_hdmi_id,
		      माप(dp_dual_mode_hdmi_id)) == 0;
पूर्ण

अटल bool is_type1_adaptor(uपूर्णांक8_t adaptor_id)
अणु
	वापस adaptor_id == 0 || adaptor_id == 0xff;
पूर्ण

अटल bool is_type2_adaptor(uपूर्णांक8_t adaptor_id)
अणु
	वापस adaptor_id == (DP_DUAL_MODE_TYPE_TYPE2 |
			      DP_DUAL_MODE_REV_TYPE2);
पूर्ण

अटल bool is_lspcon_adaptor(स्थिर अक्षर hdmi_id[DP_DUAL_MODE_HDMI_ID_LEN],
			      स्थिर uपूर्णांक8_t adaptor_id)
अणु
	वापस is_hdmi_adaptor(hdmi_id) &&
		(adaptor_id == (DP_DUAL_MODE_TYPE_TYPE2 |
		 DP_DUAL_MODE_TYPE_HAS_DPCD));
पूर्ण

/**
 * drm_dp_dual_mode_detect - Identअगरy the DP dual mode adaptor
 * @adapter: I2C adapter क्रम the DDC bus
 *
 * Attempt to identअगरy the type of the DP dual mode adaptor used.
 *
 * Note that when the answer is @DRM_DP_DUAL_MODE_UNKNOWN it's not
 * certain whether we're dealing with a native HDMI port or
 * a type 1 DVI dual mode adaptor. The driver will have to use
 * some other hardware/driver specअगरic mechanism to make that
 * distinction.
 *
 * Returns:
 * The type of the DP dual mode adaptor used
 */
क्रमागत drm_dp_dual_mode_type drm_dp_dual_mode_detect(काष्ठा i2c_adapter *adapter)
अणु
	अक्षर hdmi_id[DP_DUAL_MODE_HDMI_ID_LEN] = अणुपूर्ण;
	uपूर्णांक8_t adaptor_id = 0x00;
	sमाप_प्रकार ret;

	/*
	 * Let's see अगर the adaptor is there the by पढ़ोing the
	 * HDMI ID रेजिस्टरs.
	 *
	 * Note that type 1 DVI adaptors are not required to implemnt
	 * any रेजिस्टरs, and that presents a problem क्रम detection.
	 * If the i2c transfer is nacked, we may or may not be dealing
	 * with a type 1 DVI adaptor. Some other mechanism of detecting
	 * the presence of the adaptor is required. One way would be
	 * to check the state of the CONFIG1 pin, Another method would
	 * simply require the driver to know whether the port is a DP++
	 * port or a native HDMI port. Both of these methods are entirely
	 * hardware/driver specअगरic so we can't deal with them here.
	 */
	ret = drm_dp_dual_mode_पढ़ो(adapter, DP_DUAL_MODE_HDMI_ID,
				    hdmi_id, माप(hdmi_id));
	DRM_DEBUG_KMS("DP dual mode HDMI ID: %*pE (err %zd)\n",
		      ret ? 0 : (पूर्णांक)माप(hdmi_id), hdmi_id, ret);
	अगर (ret)
		वापस DRM_DP_DUAL_MODE_UNKNOWN;

	/*
	 * Sigh. Some (maybe all?) type 1 adaptors are broken and ack
	 * the offset but ignore it, and instead they just always वापस
	 * data from the start of the HDMI ID buffer. So क्रम a broken
	 * type 1 HDMI adaptor a single byte पढ़ो will always give us
	 * 0x44, and क्रम a type 1 DVI adaptor it should give 0x00
	 * (assuming it implements any रेजिस्टरs). Fortunately neither
	 * of those values will match the type 2 signature of the
	 * DP_DUAL_MODE_ADAPTOR_ID रेजिस्टर so we can proceed with
	 * the type 2 adaptor detection safely even in the presence
	 * of broken type 1 adaptors.
	 */
	ret = drm_dp_dual_mode_पढ़ो(adapter, DP_DUAL_MODE_ADAPTOR_ID,
				    &adaptor_id, माप(adaptor_id));
	DRM_DEBUG_KMS("DP dual mode adaptor ID: %02x (err %zd)\n",
		      adaptor_id, ret);
	अगर (ret == 0) अणु
		अगर (is_lspcon_adaptor(hdmi_id, adaptor_id))
			वापस DRM_DP_DUAL_MODE_LSPCON;
		अगर (is_type2_adaptor(adaptor_id)) अणु
			अगर (is_hdmi_adaptor(hdmi_id))
				वापस DRM_DP_DUAL_MODE_TYPE2_HDMI;
			अन्यथा
				वापस DRM_DP_DUAL_MODE_TYPE2_DVI;
		पूर्ण
		/*
		 * If neither a proper type 1 ID nor a broken type 1 adaptor
		 * as described above, assume type 1, but let the user know
		 * that we may have misdetected the type.
		 */
		अगर (!is_type1_adaptor(adaptor_id) && adaptor_id != hdmi_id[0])
			DRM_ERROR("Unexpected DP dual mode adaptor ID %02x\n",
				  adaptor_id);

	पूर्ण

	अगर (is_hdmi_adaptor(hdmi_id))
		वापस DRM_DP_DUAL_MODE_TYPE1_HDMI;
	अन्यथा
		वापस DRM_DP_DUAL_MODE_TYPE1_DVI;
पूर्ण
EXPORT_SYMBOL(drm_dp_dual_mode_detect);

/**
 * drm_dp_dual_mode_max_पंचांगds_घड़ी - Max TMDS घड़ी क्रम DP dual mode adaptor
 * @type: DP dual mode adaptor type
 * @adapter: I2C adapter क्रम the DDC bus
 *
 * Determine the max TMDS घड़ी the adaptor supports based on the
 * type of the dual mode adaptor and the DP_DUAL_MODE_MAX_TMDS_CLOCK
 * रेजिस्टर (on type2 adaptors). As some type 1 adaptors have
 * problems with रेजिस्टरs (see comments in drm_dp_dual_mode_detect())
 * we करोn't पढ़ो the रेजिस्टर on those, instead we simply assume
 * a 165 MHz limit based on the specअगरication.
 *
 * Returns:
 * Maximum supported TMDS घड़ी rate क्रम the DP dual mode adaptor in kHz.
 */
पूर्णांक drm_dp_dual_mode_max_पंचांगds_घड़ी(क्रमागत drm_dp_dual_mode_type type,
				    काष्ठा i2c_adapter *adapter)
अणु
	uपूर्णांक8_t max_पंचांगds_घड़ी;
	sमाप_प्रकार ret;

	/* native HDMI so no limit */
	अगर (type == DRM_DP_DUAL_MODE_NONE)
		वापस 0;

	/*
	 * Type 1 adaptors are limited to 165MHz
	 * Type 2 adaptors can tells us their limit
	 */
	अगर (type < DRM_DP_DUAL_MODE_TYPE2_DVI)
		वापस 165000;

	ret = drm_dp_dual_mode_पढ़ो(adapter, DP_DUAL_MODE_MAX_TMDS_CLOCK,
				    &max_पंचांगds_घड़ी, माप(max_पंचांगds_घड़ी));
	अगर (ret || max_पंचांगds_घड़ी == 0x00 || max_पंचांगds_घड़ी == 0xff) अणु
		DRM_DEBUG_KMS("Failed to query max TMDS clock\n");
		वापस 165000;
	पूर्ण

	वापस max_पंचांगds_घड़ी * 5000 / 2;
पूर्ण
EXPORT_SYMBOL(drm_dp_dual_mode_max_पंचांगds_घड़ी);

/**
 * drm_dp_dual_mode_get_पंचांगds_output - Get the state of the TMDS output buffers in the DP dual mode adaptor
 * @type: DP dual mode adaptor type
 * @adapter: I2C adapter क्रम the DDC bus
 * @enabled: current state of the TMDS output buffers
 *
 * Get the state of the TMDS output buffers in the adaptor. For
 * type2 adaptors this is queried from the DP_DUAL_MODE_TMDS_OEN
 * रेजिस्टर. As some type 1 adaptors have problems with रेजिस्टरs
 * (see comments in drm_dp_dual_mode_detect()) we करोn't पढ़ो the
 * रेजिस्टर on those, instead we simply assume that the buffers
 * are always enabled.
 *
 * Returns:
 * 0 on success, negative error code on failure
 */
पूर्णांक drm_dp_dual_mode_get_पंचांगds_output(क्रमागत drm_dp_dual_mode_type type,
				     काष्ठा i2c_adapter *adapter,
				     bool *enabled)
अणु
	uपूर्णांक8_t पंचांगds_oen;
	sमाप_प्रकार ret;

	अगर (type < DRM_DP_DUAL_MODE_TYPE2_DVI) अणु
		*enabled = true;
		वापस 0;
	पूर्ण

	ret = drm_dp_dual_mode_पढ़ो(adapter, DP_DUAL_MODE_TMDS_OEN,
				    &पंचांगds_oen, माप(पंचांगds_oen));
	अगर (ret) अणु
		DRM_DEBUG_KMS("Failed to query state of TMDS output buffers\n");
		वापस ret;
	पूर्ण

	*enabled = !(पंचांगds_oen & DP_DUAL_MODE_TMDS_DISABLE);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_dp_dual_mode_get_पंचांगds_output);

/**
 * drm_dp_dual_mode_set_पंचांगds_output - Enable/disable TMDS output buffers in the DP dual mode adaptor
 * @type: DP dual mode adaptor type
 * @adapter: I2C adapter क्रम the DDC bus
 * @enable: enable (as opposed to disable) the TMDS output buffers
 *
 * Set the state of the TMDS output buffers in the adaptor. For
 * type2 this is set via the DP_DUAL_MODE_TMDS_OEN रेजिस्टर. As
 * some type 1 adaptors have problems with रेजिस्टरs (see comments
 * in drm_dp_dual_mode_detect()) we aव्योम touching the रेजिस्टर,
 * making this function a no-op on type 1 adaptors.
 *
 * Returns:
 * 0 on success, negative error code on failure
 */
पूर्णांक drm_dp_dual_mode_set_पंचांगds_output(क्रमागत drm_dp_dual_mode_type type,
				     काष्ठा i2c_adapter *adapter, bool enable)
अणु
	uपूर्णांक8_t पंचांगds_oen = enable ? 0 : DP_DUAL_MODE_TMDS_DISABLE;
	sमाप_प्रकार ret;
	पूर्णांक retry;

	अगर (type < DRM_DP_DUAL_MODE_TYPE2_DVI)
		वापस 0;

	/*
	 * LSPCON adapters in low-घातer state may ignore the first ग_लिखो, so
	 * पढ़ो back and verअगरy the written value a few बार.
	 */
	क्रम (retry = 0; retry < 3; retry++) अणु
		uपूर्णांक8_t पंचांगp;

		ret = drm_dp_dual_mode_ग_लिखो(adapter, DP_DUAL_MODE_TMDS_OEN,
					     &पंचांगds_oen, माप(पंचांगds_oen));
		अगर (ret) अणु
			DRM_DEBUG_KMS("Failed to %s TMDS output buffers (%d attempts)\n",
				      enable ? "enable" : "disable",
				      retry + 1);
			वापस ret;
		पूर्ण

		ret = drm_dp_dual_mode_पढ़ो(adapter, DP_DUAL_MODE_TMDS_OEN,
					    &पंचांगp, माप(पंचांगp));
		अगर (ret) अणु
			DRM_DEBUG_KMS("I2C read failed during TMDS output buffer %s (%d attempts)\n",
				      enable ? "enabling" : "disabling",
				      retry + 1);
			वापस ret;
		पूर्ण

		अगर (पंचांगp == पंचांगds_oen)
			वापस 0;
	पूर्ण

	DRM_DEBUG_KMS("I2C write value mismatch during TMDS output buffer %s\n",
		      enable ? "enabling" : "disabling");

	वापस -EIO;
पूर्ण
EXPORT_SYMBOL(drm_dp_dual_mode_set_पंचांगds_output);

/**
 * drm_dp_get_dual_mode_type_name - Get the name of the DP dual mode adaptor type as a string
 * @type: DP dual mode adaptor type
 *
 * Returns:
 * String representation of the DP dual mode adaptor type
 */
स्थिर अक्षर *drm_dp_get_dual_mode_type_name(क्रमागत drm_dp_dual_mode_type type)
अणु
	चयन (type) अणु
	हाल DRM_DP_DUAL_MODE_NONE:
		वापस "none";
	हाल DRM_DP_DUAL_MODE_TYPE1_DVI:
		वापस "type 1 DVI";
	हाल DRM_DP_DUAL_MODE_TYPE1_HDMI:
		वापस "type 1 HDMI";
	हाल DRM_DP_DUAL_MODE_TYPE2_DVI:
		वापस "type 2 DVI";
	हाल DRM_DP_DUAL_MODE_TYPE2_HDMI:
		वापस "type 2 HDMI";
	हाल DRM_DP_DUAL_MODE_LSPCON:
		वापस "lspcon";
	शेष:
		WARN_ON(type != DRM_DP_DUAL_MODE_UNKNOWN);
		वापस "unknown";
	पूर्ण
पूर्ण
EXPORT_SYMBOL(drm_dp_get_dual_mode_type_name);

/**
 * drm_lspcon_get_mode: Get LSPCON's current mode of operation by
 * पढ़ोing offset (0x80, 0x41)
 * @adapter: I2C-over-aux adapter
 * @mode: current lspcon mode of operation output variable
 *
 * Returns:
 * 0 on success, sets the current_mode value to appropriate mode
 * -error on failure
 */
पूर्णांक drm_lspcon_get_mode(काष्ठा i2c_adapter *adapter,
			क्रमागत drm_lspcon_mode *mode)
अणु
	u8 data;
	पूर्णांक ret = 0;
	पूर्णांक retry;

	अगर (!mode) अणु
		DRM_ERROR("NULL input\n");
		वापस -EINVAL;
	पूर्ण

	/* Read Status: i2c over aux */
	क्रम (retry = 0; retry < 6; retry++) अणु
		अगर (retry)
			usleep_range(500, 1000);

		ret = drm_dp_dual_mode_पढ़ो(adapter,
					    DP_DUAL_MODE_LSPCON_CURRENT_MODE,
					    &data, माप(data));
		अगर (!ret)
			अवरोध;
	पूर्ण

	अगर (ret < 0) अणु
		DRM_DEBUG_KMS("LSPCON read(0x80, 0x41) failed\n");
		वापस -EFAULT;
	पूर्ण

	अगर (data & DP_DUAL_MODE_LSPCON_MODE_PCON)
		*mode = DRM_LSPCON_MODE_PCON;
	अन्यथा
		*mode = DRM_LSPCON_MODE_LS;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_lspcon_get_mode);

/**
 * drm_lspcon_set_mode: Change LSPCON's mode of operation by
 * writing offset (0x80, 0x40)
 * @adapter: I2C-over-aux adapter
 * @mode: required mode of operation
 *
 * Returns:
 * 0 on success, -error on failure/समयout
 */
पूर्णांक drm_lspcon_set_mode(काष्ठा i2c_adapter *adapter,
			क्रमागत drm_lspcon_mode mode)
अणु
	u8 data = 0;
	पूर्णांक ret;
	पूर्णांक समय_out = 200;
	क्रमागत drm_lspcon_mode current_mode;

	अगर (mode == DRM_LSPCON_MODE_PCON)
		data = DP_DUAL_MODE_LSPCON_MODE_PCON;

	/* Change mode */
	ret = drm_dp_dual_mode_ग_लिखो(adapter, DP_DUAL_MODE_LSPCON_MODE_CHANGE,
				     &data, माप(data));
	अगर (ret < 0) अणु
		DRM_ERROR("LSPCON mode change failed\n");
		वापस ret;
	पूर्ण

	/*
	 * Confirm mode change by पढ़ोing the status bit.
	 * Someबार, it takes a जबतक to change the mode,
	 * so रुको and retry until समय out or करोne.
	 */
	करो अणु
		ret = drm_lspcon_get_mode(adapter, &current_mode);
		अगर (ret) अणु
			DRM_ERROR("can't confirm LSPCON mode change\n");
			वापस ret;
		पूर्ण अन्यथा अणु
			अगर (current_mode != mode) अणु
				msleep(10);
				समय_out -= 10;
			पूर्ण अन्यथा अणु
				DRM_DEBUG_KMS("LSPCON mode changed to %s\n",
						mode == DRM_LSPCON_MODE_LS ?
						"LS" : "PCON");
				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण जबतक (समय_out);

	DRM_ERROR("LSPCON mode change timed out\n");
	वापस -ETIMEDOUT;
पूर्ण
EXPORT_SYMBOL(drm_lspcon_set_mode);
