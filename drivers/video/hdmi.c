<शैली गुरु>
/*
 * Copyright (C) 2012 Avionic Design GmbH
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

#समावेश <linux/bitops.h>
#समावेश <linux/bug.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/export.h>
#समावेश <linux/hdmi.h>
#समावेश <linux/माला.स>
#समावेश <linux/device.h>

#घोषणा hdmi_log(fmt, ...) dev_prपूर्णांकk(level, dev, fmt, ##__VA_ARGS__)

अटल u8 hdmi_infoframe_checksum(स्थिर u8 *ptr, माप_प्रकार size)
अणु
	u8 csum = 0;
	माप_प्रकार i;

	/* compute checksum */
	क्रम (i = 0; i < size; i++)
		csum += ptr[i];

	वापस 256 - csum;
पूर्ण

अटल व्योम hdmi_infoframe_set_checksum(व्योम *buffer, माप_प्रकार size)
अणु
	u8 *ptr = buffer;

	ptr[3] = hdmi_infoframe_checksum(buffer, size);
पूर्ण

/**
 * hdmi_avi_infoframe_init() - initialize an HDMI AVI infoframe
 * @frame: HDMI AVI infoframe
 */
व्योम hdmi_avi_infoframe_init(काष्ठा hdmi_avi_infoframe *frame)
अणु
	स_रखो(frame, 0, माप(*frame));

	frame->type = HDMI_INFOFRAME_TYPE_AVI;
	frame->version = 2;
	frame->length = HDMI_AVI_INFOFRAME_SIZE;
पूर्ण
EXPORT_SYMBOL(hdmi_avi_infoframe_init);

अटल पूर्णांक hdmi_avi_infoframe_check_only(स्थिर काष्ठा hdmi_avi_infoframe *frame)
अणु
	अगर (frame->type != HDMI_INFOFRAME_TYPE_AVI ||
	    frame->version != 2 ||
	    frame->length != HDMI_AVI_INFOFRAME_SIZE)
		वापस -EINVAL;

	अगर (frame->picture_aspect > HDMI_PICTURE_ASPECT_16_9)
		वापस -EINVAL;

	वापस 0;
पूर्ण

/**
 * hdmi_avi_infoframe_check() - check a HDMI AVI infoframe
 * @frame: HDMI AVI infoframe
 *
 * Validates that the infoframe is consistent and updates derived fields
 * (eg. length) based on other fields.
 *
 * Returns 0 on success or a negative error code on failure.
 */
पूर्णांक hdmi_avi_infoframe_check(काष्ठा hdmi_avi_infoframe *frame)
अणु
	वापस hdmi_avi_infoframe_check_only(frame);
पूर्ण
EXPORT_SYMBOL(hdmi_avi_infoframe_check);

/**
 * hdmi_avi_infoframe_pack_only() - ग_लिखो HDMI AVI infoframe to binary buffer
 * @frame: HDMI AVI infoframe
 * @buffer: destination buffer
 * @size: size of buffer
 *
 * Packs the inक्रमmation contained in the @frame काष्ठाure पूर्णांकo a binary
 * representation that can be written पूर्णांकo the corresponding controller
 * रेजिस्टरs. Also computes the checksum as required by section 5.3.5 of
 * the HDMI 1.4 specअगरication.
 *
 * Returns the number of bytes packed पूर्णांकo the binary buffer or a negative
 * error code on failure.
 */
sमाप_प्रकार hdmi_avi_infoframe_pack_only(स्थिर काष्ठा hdmi_avi_infoframe *frame,
				     व्योम *buffer, माप_प्रकार size)
अणु
	u8 *ptr = buffer;
	माप_प्रकार length;
	पूर्णांक ret;

	ret = hdmi_avi_infoframe_check_only(frame);
	अगर (ret)
		वापस ret;

	length = HDMI_INFOFRAME_HEADER_SIZE + frame->length;

	अगर (size < length)
		वापस -ENOSPC;

	स_रखो(buffer, 0, size);

	ptr[0] = frame->type;
	ptr[1] = frame->version;
	ptr[2] = frame->length;
	ptr[3] = 0; /* checksum */

	/* start infoframe payload */
	ptr += HDMI_INFOFRAME_HEADER_SIZE;

	ptr[0] = ((frame->colorspace & 0x3) << 5) | (frame->scan_mode & 0x3);

	/*
	 * Data byte 1, bit 4 has to be set अगर we provide the active क्रमmat
	 * aspect ratio
	 */
	अगर (frame->active_aspect & 0xf)
		ptr[0] |= BIT(4);

	/* Bit 3 and 2 indicate अगर we transmit horizontal/vertical bar data */
	अगर (frame->top_bar || frame->bottom_bar)
		ptr[0] |= BIT(3);

	अगर (frame->left_bar || frame->right_bar)
		ptr[0] |= BIT(2);

	ptr[1] = ((frame->colorimetry & 0x3) << 6) |
		 ((frame->picture_aspect & 0x3) << 4) |
		 (frame->active_aspect & 0xf);

	ptr[2] = ((frame->extended_colorimetry & 0x7) << 4) |
		 ((frame->quantization_range & 0x3) << 2) |
		 (frame->nups & 0x3);

	अगर (frame->itc)
		ptr[2] |= BIT(7);

	ptr[3] = frame->video_code & 0x7f;

	ptr[4] = ((frame->ycc_quantization_range & 0x3) << 6) |
		 ((frame->content_type & 0x3) << 4) |
		 (frame->pixel_repeat & 0xf);

	ptr[5] = frame->top_bar & 0xff;
	ptr[6] = (frame->top_bar >> 8) & 0xff;
	ptr[7] = frame->bottom_bar & 0xff;
	ptr[8] = (frame->bottom_bar >> 8) & 0xff;
	ptr[9] = frame->left_bar & 0xff;
	ptr[10] = (frame->left_bar >> 8) & 0xff;
	ptr[11] = frame->right_bar & 0xff;
	ptr[12] = (frame->right_bar >> 8) & 0xff;

	hdmi_infoframe_set_checksum(buffer, length);

	वापस length;
पूर्ण
EXPORT_SYMBOL(hdmi_avi_infoframe_pack_only);

/**
 * hdmi_avi_infoframe_pack() - check a HDMI AVI infoframe,
 *                             and ग_लिखो it to binary buffer
 * @frame: HDMI AVI infoframe
 * @buffer: destination buffer
 * @size: size of buffer
 *
 * Validates that the infoframe is consistent and updates derived fields
 * (eg. length) based on other fields, after which it packs the inक्रमmation
 * contained in the @frame काष्ठाure पूर्णांकo a binary representation that
 * can be written पूर्णांकo the corresponding controller रेजिस्टरs. This function
 * also computes the checksum as required by section 5.3.5 of the HDMI 1.4
 * specअगरication.
 *
 * Returns the number of bytes packed पूर्णांकo the binary buffer or a negative
 * error code on failure.
 */
sमाप_प्रकार hdmi_avi_infoframe_pack(काष्ठा hdmi_avi_infoframe *frame,
				व्योम *buffer, माप_प्रकार size)
अणु
	पूर्णांक ret;

	ret = hdmi_avi_infoframe_check(frame);
	अगर (ret)
		वापस ret;

	वापस hdmi_avi_infoframe_pack_only(frame, buffer, size);
पूर्ण
EXPORT_SYMBOL(hdmi_avi_infoframe_pack);

/**
 * hdmi_spd_infoframe_init() - initialize an HDMI SPD infoframe
 * @frame: HDMI SPD infoframe
 * @venकरोr: venकरोr string
 * @product: product string
 *
 * Returns 0 on success or a negative error code on failure.
 */
पूर्णांक hdmi_spd_infoframe_init(काष्ठा hdmi_spd_infoframe *frame,
			    स्थिर अक्षर *venकरोr, स्थिर अक्षर *product)
अणु
	माप_प्रकार len;

	स_रखो(frame, 0, माप(*frame));

	frame->type = HDMI_INFOFRAME_TYPE_SPD;
	frame->version = 1;
	frame->length = HDMI_SPD_INFOFRAME_SIZE;

	len = म_माप(venकरोr);
	स_नकल(frame->venकरोr, venकरोr, min(len, माप(frame->venकरोr)));
	len = म_माप(product);
	स_नकल(frame->product, product, min(len, माप(frame->product)));

	वापस 0;
पूर्ण
EXPORT_SYMBOL(hdmi_spd_infoframe_init);

अटल पूर्णांक hdmi_spd_infoframe_check_only(स्थिर काष्ठा hdmi_spd_infoframe *frame)
अणु
	अगर (frame->type != HDMI_INFOFRAME_TYPE_SPD ||
	    frame->version != 1 ||
	    frame->length != HDMI_SPD_INFOFRAME_SIZE)
		वापस -EINVAL;

	वापस 0;
पूर्ण

/**
 * hdmi_spd_infoframe_check() - check a HDMI SPD infoframe
 * @frame: HDMI SPD infoframe
 *
 * Validates that the infoframe is consistent and updates derived fields
 * (eg. length) based on other fields.
 *
 * Returns 0 on success or a negative error code on failure.
 */
पूर्णांक hdmi_spd_infoframe_check(काष्ठा hdmi_spd_infoframe *frame)
अणु
	वापस hdmi_spd_infoframe_check_only(frame);
पूर्ण
EXPORT_SYMBOL(hdmi_spd_infoframe_check);

/**
 * hdmi_spd_infoframe_pack_only() - ग_लिखो HDMI SPD infoframe to binary buffer
 * @frame: HDMI SPD infoframe
 * @buffer: destination buffer
 * @size: size of buffer
 *
 * Packs the inक्रमmation contained in the @frame काष्ठाure पूर्णांकo a binary
 * representation that can be written पूर्णांकo the corresponding controller
 * रेजिस्टरs. Also computes the checksum as required by section 5.3.5 of
 * the HDMI 1.4 specअगरication.
 *
 * Returns the number of bytes packed पूर्णांकo the binary buffer or a negative
 * error code on failure.
 */
sमाप_प्रकार hdmi_spd_infoframe_pack_only(स्थिर काष्ठा hdmi_spd_infoframe *frame,
				     व्योम *buffer, माप_प्रकार size)
अणु
	u8 *ptr = buffer;
	माप_प्रकार length;
	पूर्णांक ret;

	ret = hdmi_spd_infoframe_check_only(frame);
	अगर (ret)
		वापस ret;

	length = HDMI_INFOFRAME_HEADER_SIZE + frame->length;

	अगर (size < length)
		वापस -ENOSPC;

	स_रखो(buffer, 0, size);

	ptr[0] = frame->type;
	ptr[1] = frame->version;
	ptr[2] = frame->length;
	ptr[3] = 0; /* checksum */

	/* start infoframe payload */
	ptr += HDMI_INFOFRAME_HEADER_SIZE;

	स_नकल(ptr, frame->venकरोr, माप(frame->venकरोr));
	स_नकल(ptr + 8, frame->product, माप(frame->product));

	ptr[24] = frame->sdi;

	hdmi_infoframe_set_checksum(buffer, length);

	वापस length;
पूर्ण
EXPORT_SYMBOL(hdmi_spd_infoframe_pack_only);

/**
 * hdmi_spd_infoframe_pack() - check a HDMI SPD infoframe,
 *                             and ग_लिखो it to binary buffer
 * @frame: HDMI SPD infoframe
 * @buffer: destination buffer
 * @size: size of buffer
 *
 * Validates that the infoframe is consistent and updates derived fields
 * (eg. length) based on other fields, after which it packs the inक्रमmation
 * contained in the @frame काष्ठाure पूर्णांकo a binary representation that
 * can be written पूर्णांकo the corresponding controller रेजिस्टरs. This function
 * also computes the checksum as required by section 5.3.5 of the HDMI 1.4
 * specअगरication.
 *
 * Returns the number of bytes packed पूर्णांकo the binary buffer or a negative
 * error code on failure.
 */
sमाप_प्रकार hdmi_spd_infoframe_pack(काष्ठा hdmi_spd_infoframe *frame,
				व्योम *buffer, माप_प्रकार size)
अणु
	पूर्णांक ret;

	ret = hdmi_spd_infoframe_check(frame);
	अगर (ret)
		वापस ret;

	वापस hdmi_spd_infoframe_pack_only(frame, buffer, size);
पूर्ण
EXPORT_SYMBOL(hdmi_spd_infoframe_pack);

/**
 * hdmi_audio_infoframe_init() - initialize an HDMI audio infoframe
 * @frame: HDMI audio infoframe
 *
 * Returns 0 on success or a negative error code on failure.
 */
पूर्णांक hdmi_audio_infoframe_init(काष्ठा hdmi_audio_infoframe *frame)
अणु
	स_रखो(frame, 0, माप(*frame));

	frame->type = HDMI_INFOFRAME_TYPE_AUDIO;
	frame->version = 1;
	frame->length = HDMI_AUDIO_INFOFRAME_SIZE;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(hdmi_audio_infoframe_init);

अटल पूर्णांक hdmi_audio_infoframe_check_only(स्थिर काष्ठा hdmi_audio_infoframe *frame)
अणु
	अगर (frame->type != HDMI_INFOFRAME_TYPE_AUDIO ||
	    frame->version != 1 ||
	    frame->length != HDMI_AUDIO_INFOFRAME_SIZE)
		वापस -EINVAL;

	वापस 0;
पूर्ण

/**
 * hdmi_audio_infoframe_check() - check a HDMI audio infoframe
 * @frame: HDMI audio infoframe
 *
 * Validates that the infoframe is consistent and updates derived fields
 * (eg. length) based on other fields.
 *
 * Returns 0 on success or a negative error code on failure.
 */
पूर्णांक hdmi_audio_infoframe_check(काष्ठा hdmi_audio_infoframe *frame)
अणु
	वापस hdmi_audio_infoframe_check_only(frame);
पूर्ण
EXPORT_SYMBOL(hdmi_audio_infoframe_check);

/**
 * hdmi_audio_infoframe_pack_only() - ग_लिखो HDMI audio infoframe to binary buffer
 * @frame: HDMI audio infoframe
 * @buffer: destination buffer
 * @size: size of buffer
 *
 * Packs the inक्रमmation contained in the @frame काष्ठाure पूर्णांकo a binary
 * representation that can be written पूर्णांकo the corresponding controller
 * रेजिस्टरs. Also computes the checksum as required by section 5.3.5 of
 * the HDMI 1.4 specअगरication.
 *
 * Returns the number of bytes packed पूर्णांकo the binary buffer or a negative
 * error code on failure.
 */
sमाप_प्रकार hdmi_audio_infoframe_pack_only(स्थिर काष्ठा hdmi_audio_infoframe *frame,
				       व्योम *buffer, माप_प्रकार size)
अणु
	अचिन्हित अक्षर channels;
	u8 *ptr = buffer;
	माप_प्रकार length;
	पूर्णांक ret;

	ret = hdmi_audio_infoframe_check_only(frame);
	अगर (ret)
		वापस ret;

	length = HDMI_INFOFRAME_HEADER_SIZE + frame->length;

	अगर (size < length)
		वापस -ENOSPC;

	स_रखो(buffer, 0, size);

	अगर (frame->channels >= 2)
		channels = frame->channels - 1;
	अन्यथा
		channels = 0;

	ptr[0] = frame->type;
	ptr[1] = frame->version;
	ptr[2] = frame->length;
	ptr[3] = 0; /* checksum */

	/* start infoframe payload */
	ptr += HDMI_INFOFRAME_HEADER_SIZE;

	ptr[0] = ((frame->coding_type & 0xf) << 4) | (channels & 0x7);
	ptr[1] = ((frame->sample_frequency & 0x7) << 2) |
		 (frame->sample_size & 0x3);
	ptr[2] = frame->coding_type_ext & 0x1f;
	ptr[3] = frame->channel_allocation;
	ptr[4] = (frame->level_shअगरt_value & 0xf) << 3;

	अगर (frame->करोwnmix_inhibit)
		ptr[4] |= BIT(7);

	hdmi_infoframe_set_checksum(buffer, length);

	वापस length;
पूर्ण
EXPORT_SYMBOL(hdmi_audio_infoframe_pack_only);

/**
 * hdmi_audio_infoframe_pack() - check a HDMI Audio infoframe,
 *                               and ग_लिखो it to binary buffer
 * @frame: HDMI Audio infoframe
 * @buffer: destination buffer
 * @size: size of buffer
 *
 * Validates that the infoframe is consistent and updates derived fields
 * (eg. length) based on other fields, after which it packs the inक्रमmation
 * contained in the @frame काष्ठाure पूर्णांकo a binary representation that
 * can be written पूर्णांकo the corresponding controller रेजिस्टरs. This function
 * also computes the checksum as required by section 5.3.5 of the HDMI 1.4
 * specअगरication.
 *
 * Returns the number of bytes packed पूर्णांकo the binary buffer or a negative
 * error code on failure.
 */
sमाप_प्रकार hdmi_audio_infoframe_pack(काष्ठा hdmi_audio_infoframe *frame,
				  व्योम *buffer, माप_प्रकार size)
अणु
	पूर्णांक ret;

	ret = hdmi_audio_infoframe_check(frame);
	अगर (ret)
		वापस ret;

	वापस hdmi_audio_infoframe_pack_only(frame, buffer, size);
पूर्ण
EXPORT_SYMBOL(hdmi_audio_infoframe_pack);

/**
 * hdmi_venकरोr_infoframe_init() - initialize an HDMI venकरोr infoframe
 * @frame: HDMI venकरोr infoframe
 *
 * Returns 0 on success or a negative error code on failure.
 */
पूर्णांक hdmi_venकरोr_infoframe_init(काष्ठा hdmi_venकरोr_infoframe *frame)
अणु
	स_रखो(frame, 0, माप(*frame));

	frame->type = HDMI_INFOFRAME_TYPE_VENDOR;
	frame->version = 1;

	frame->oui = HDMI_IEEE_OUI;

	/*
	 * 0 is a valid value क्रम s3d_काष्ठा, so we use a special "not set"
	 * value
	 */
	frame->s3d_काष्ठा = HDMI_3D_STRUCTURE_INVALID;
	frame->length = HDMI_VENDOR_INFOFRAME_SIZE;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(hdmi_venकरोr_infoframe_init);

अटल पूर्णांक hdmi_venकरोr_infoframe_length(स्थिर काष्ठा hdmi_venकरोr_infoframe *frame)
अणु
	/* क्रम side by side (half) we also need to provide 3D_Ext_Data */
	अगर (frame->s3d_काष्ठा >= HDMI_3D_STRUCTURE_SIDE_BY_SIDE_HALF)
		वापस 6;
	अन्यथा अगर (frame->vic != 0 || frame->s3d_काष्ठा != HDMI_3D_STRUCTURE_INVALID)
		वापस 5;
	अन्यथा
		वापस 4;
पूर्ण

अटल पूर्णांक hdmi_venकरोr_infoframe_check_only(स्थिर काष्ठा hdmi_venकरोr_infoframe *frame)
अणु
	अगर (frame->type != HDMI_INFOFRAME_TYPE_VENDOR ||
	    frame->version != 1 ||
	    frame->oui != HDMI_IEEE_OUI)
		वापस -EINVAL;

	/* only one of those can be supplied */
	अगर (frame->vic != 0 && frame->s3d_काष्ठा != HDMI_3D_STRUCTURE_INVALID)
		वापस -EINVAL;

	अगर (frame->length != hdmi_venकरोr_infoframe_length(frame))
		वापस -EINVAL;

	वापस 0;
पूर्ण

/**
 * hdmi_venकरोr_infoframe_check() - check a HDMI venकरोr infoframe
 * @frame: HDMI infoframe
 *
 * Validates that the infoframe is consistent and updates derived fields
 * (eg. length) based on other fields.
 *
 * Returns 0 on success or a negative error code on failure.
 */
पूर्णांक hdmi_venकरोr_infoframe_check(काष्ठा hdmi_venकरोr_infoframe *frame)
अणु
	frame->length = hdmi_venकरोr_infoframe_length(frame);

	वापस hdmi_venकरोr_infoframe_check_only(frame);
पूर्ण
EXPORT_SYMBOL(hdmi_venकरोr_infoframe_check);

/**
 * hdmi_venकरोr_infoframe_pack_only() - ग_लिखो a HDMI venकरोr infoframe to binary buffer
 * @frame: HDMI infoframe
 * @buffer: destination buffer
 * @size: size of buffer
 *
 * Packs the inक्रमmation contained in the @frame काष्ठाure पूर्णांकo a binary
 * representation that can be written पूर्णांकo the corresponding controller
 * रेजिस्टरs. Also computes the checksum as required by section 5.3.5 of
 * the HDMI 1.4 specअगरication.
 *
 * Returns the number of bytes packed पूर्णांकo the binary buffer or a negative
 * error code on failure.
 */
sमाप_प्रकार hdmi_venकरोr_infoframe_pack_only(स्थिर काष्ठा hdmi_venकरोr_infoframe *frame,
					व्योम *buffer, माप_प्रकार size)
अणु
	u8 *ptr = buffer;
	माप_प्रकार length;
	पूर्णांक ret;

	ret = hdmi_venकरोr_infoframe_check_only(frame);
	अगर (ret)
		वापस ret;

	length = HDMI_INFOFRAME_HEADER_SIZE + frame->length;

	अगर (size < length)
		वापस -ENOSPC;

	स_रखो(buffer, 0, size);

	ptr[0] = frame->type;
	ptr[1] = frame->version;
	ptr[2] = frame->length;
	ptr[3] = 0; /* checksum */

	/* HDMI OUI */
	ptr[4] = 0x03;
	ptr[5] = 0x0c;
	ptr[6] = 0x00;

	अगर (frame->s3d_काष्ठा != HDMI_3D_STRUCTURE_INVALID) अणु
		ptr[7] = 0x2 << 5;	/* video क्रमmat */
		ptr[8] = (frame->s3d_काष्ठा & 0xf) << 4;
		अगर (frame->s3d_काष्ठा >= HDMI_3D_STRUCTURE_SIDE_BY_SIDE_HALF)
			ptr[9] = (frame->s3d_ext_data & 0xf) << 4;
	पूर्ण अन्यथा अगर (frame->vic) अणु
		ptr[7] = 0x1 << 5;	/* video क्रमmat */
		ptr[8] = frame->vic;
	पूर्ण अन्यथा अणु
		ptr[7] = 0x0 << 5;	/* video क्रमmat */
	पूर्ण

	hdmi_infoframe_set_checksum(buffer, length);

	वापस length;
पूर्ण
EXPORT_SYMBOL(hdmi_venकरोr_infoframe_pack_only);

/**
 * hdmi_venकरोr_infoframe_pack() - check a HDMI Venकरोr infoframe,
 *                                and ग_लिखो it to binary buffer
 * @frame: HDMI Venकरोr infoframe
 * @buffer: destination buffer
 * @size: size of buffer
 *
 * Validates that the infoframe is consistent and updates derived fields
 * (eg. length) based on other fields, after which it packs the inक्रमmation
 * contained in the @frame काष्ठाure पूर्णांकo a binary representation that
 * can be written पूर्णांकo the corresponding controller रेजिस्टरs. This function
 * also computes the checksum as required by section 5.3.5 of the HDMI 1.4
 * specअगरication.
 *
 * Returns the number of bytes packed पूर्णांकo the binary buffer or a negative
 * error code on failure.
 */
sमाप_प्रकार hdmi_venकरोr_infoframe_pack(काष्ठा hdmi_venकरोr_infoframe *frame,
				   व्योम *buffer, माप_प्रकार size)
अणु
	पूर्णांक ret;

	ret = hdmi_venकरोr_infoframe_check(frame);
	अगर (ret)
		वापस ret;

	वापस hdmi_venकरोr_infoframe_pack_only(frame, buffer, size);
पूर्ण
EXPORT_SYMBOL(hdmi_venकरोr_infoframe_pack);

अटल पूर्णांक
hdmi_venकरोr_any_infoframe_check_only(स्थिर जोड़ hdmi_venकरोr_any_infoframe *frame)
अणु
	अगर (frame->any.type != HDMI_INFOFRAME_TYPE_VENDOR ||
	    frame->any.version != 1)
		वापस -EINVAL;

	वापस 0;
पूर्ण

/**
 * hdmi_drm_infoframe_init() - initialize an HDMI Dynaminc Range and
 * mastering infoframe
 * @frame: HDMI DRM infoframe
 *
 * Returns 0 on success or a negative error code on failure.
 */
पूर्णांक hdmi_drm_infoframe_init(काष्ठा hdmi_drm_infoframe *frame)
अणु
	स_रखो(frame, 0, माप(*frame));

	frame->type = HDMI_INFOFRAME_TYPE_DRM;
	frame->version = 1;
	frame->length = HDMI_DRM_INFOFRAME_SIZE;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(hdmi_drm_infoframe_init);

अटल पूर्णांक hdmi_drm_infoframe_check_only(स्थिर काष्ठा hdmi_drm_infoframe *frame)
अणु
	अगर (frame->type != HDMI_INFOFRAME_TYPE_DRM ||
	    frame->version != 1)
		वापस -EINVAL;

	अगर (frame->length != HDMI_DRM_INFOFRAME_SIZE)
		वापस -EINVAL;

	वापस 0;
पूर्ण

/**
 * hdmi_drm_infoframe_check() - check a HDMI DRM infoframe
 * @frame: HDMI DRM infoframe
 *
 * Validates that the infoframe is consistent.
 * Returns 0 on success or a negative error code on failure.
 */
पूर्णांक hdmi_drm_infoframe_check(काष्ठा hdmi_drm_infoframe *frame)
अणु
	वापस hdmi_drm_infoframe_check_only(frame);
पूर्ण
EXPORT_SYMBOL(hdmi_drm_infoframe_check);

/**
 * hdmi_drm_infoframe_pack_only() - ग_लिखो HDMI DRM infoframe to binary buffer
 * @frame: HDMI DRM infoframe
 * @buffer: destination buffer
 * @size: size of buffer
 *
 * Packs the inक्रमmation contained in the @frame काष्ठाure पूर्णांकo a binary
 * representation that can be written पूर्णांकo the corresponding controller
 * रेजिस्टरs. Also computes the checksum as required by section 5.3.5 of
 * the HDMI 1.4 specअगरication.
 *
 * Returns the number of bytes packed पूर्णांकo the binary buffer or a negative
 * error code on failure.
 */
sमाप_प्रकार hdmi_drm_infoframe_pack_only(स्थिर काष्ठा hdmi_drm_infoframe *frame,
				     व्योम *buffer, माप_प्रकार size)
अणु
	u8 *ptr = buffer;
	माप_प्रकार length;
	पूर्णांक i;

	length = HDMI_INFOFRAME_HEADER_SIZE + frame->length;

	अगर (size < length)
		वापस -ENOSPC;

	स_रखो(buffer, 0, size);

	ptr[0] = frame->type;
	ptr[1] = frame->version;
	ptr[2] = frame->length;
	ptr[3] = 0; /* checksum */

	/* start infoframe payload */
	ptr += HDMI_INFOFRAME_HEADER_SIZE;

	*ptr++ = frame->eotf;
	*ptr++ = frame->metadata_type;

	क्रम (i = 0; i < 3; i++) अणु
		*ptr++ = frame->display_primaries[i].x;
		*ptr++ = frame->display_primaries[i].x >> 8;
		*ptr++ = frame->display_primaries[i].y;
		*ptr++ = frame->display_primaries[i].y >> 8;
	पूर्ण

	*ptr++ = frame->white_poपूर्णांक.x;
	*ptr++ = frame->white_poपूर्णांक.x >> 8;

	*ptr++ = frame->white_poपूर्णांक.y;
	*ptr++ = frame->white_poपूर्णांक.y >> 8;

	*ptr++ = frame->max_display_mastering_luminance;
	*ptr++ = frame->max_display_mastering_luminance >> 8;

	*ptr++ = frame->min_display_mastering_luminance;
	*ptr++ = frame->min_display_mastering_luminance >> 8;

	*ptr++ = frame->max_cll;
	*ptr++ = frame->max_cll >> 8;

	*ptr++ = frame->max_fall;
	*ptr++ = frame->max_fall >> 8;

	hdmi_infoframe_set_checksum(buffer, length);

	वापस length;
पूर्ण
EXPORT_SYMBOL(hdmi_drm_infoframe_pack_only);

/**
 * hdmi_drm_infoframe_pack() - check a HDMI DRM infoframe,
 *                             and ग_लिखो it to binary buffer
 * @frame: HDMI DRM infoframe
 * @buffer: destination buffer
 * @size: size of buffer
 *
 * Validates that the infoframe is consistent and updates derived fields
 * (eg. length) based on other fields, after which it packs the inक्रमmation
 * contained in the @frame काष्ठाure पूर्णांकo a binary representation that
 * can be written पूर्णांकo the corresponding controller रेजिस्टरs. This function
 * also computes the checksum as required by section 5.3.5 of the HDMI 1.4
 * specअगरication.
 *
 * Returns the number of bytes packed पूर्णांकo the binary buffer or a negative
 * error code on failure.
 */
sमाप_प्रकार hdmi_drm_infoframe_pack(काष्ठा hdmi_drm_infoframe *frame,
				व्योम *buffer, माप_प्रकार size)
अणु
	पूर्णांक ret;

	ret = hdmi_drm_infoframe_check(frame);
	अगर (ret)
		वापस ret;

	वापस hdmi_drm_infoframe_pack_only(frame, buffer, size);
पूर्ण
EXPORT_SYMBOL(hdmi_drm_infoframe_pack);

/*
 * hdmi_venकरोr_any_infoframe_check() - check a venकरोr infoframe
 */
अटल पूर्णांक
hdmi_venकरोr_any_infoframe_check(जोड़ hdmi_venकरोr_any_infoframe *frame)
अणु
	पूर्णांक ret;

	ret = hdmi_venकरोr_any_infoframe_check_only(frame);
	अगर (ret)
		वापस ret;

	/* we only know about HDMI venकरोr infoframes */
	अगर (frame->any.oui != HDMI_IEEE_OUI)
		वापस -EINVAL;

	वापस hdmi_venकरोr_infoframe_check(&frame->hdmi);
पूर्ण

/*
 * hdmi_venकरोr_any_infoframe_pack_only() - ग_लिखो a venकरोr infoframe to binary buffer
 */
अटल sमाप_प्रकार
hdmi_venकरोr_any_infoframe_pack_only(स्थिर जोड़ hdmi_venकरोr_any_infoframe *frame,
				    व्योम *buffer, माप_प्रकार size)
अणु
	पूर्णांक ret;

	ret = hdmi_venकरोr_any_infoframe_check_only(frame);
	अगर (ret)
		वापस ret;

	/* we only know about HDMI venकरोr infoframes */
	अगर (frame->any.oui != HDMI_IEEE_OUI)
		वापस -EINVAL;

	वापस hdmi_venकरोr_infoframe_pack_only(&frame->hdmi, buffer, size);
पूर्ण

/*
 * hdmi_venकरोr_any_infoframe_pack() - check a venकरोr infoframe,
 *                                    and ग_लिखो it to binary buffer
 */
अटल sमाप_प्रकार
hdmi_venकरोr_any_infoframe_pack(जोड़ hdmi_venकरोr_any_infoframe *frame,
			       व्योम *buffer, माप_प्रकार size)
अणु
	पूर्णांक ret;

	ret = hdmi_venकरोr_any_infoframe_check(frame);
	अगर (ret)
		वापस ret;

	वापस hdmi_venकरोr_any_infoframe_pack_only(frame, buffer, size);
पूर्ण

/**
 * hdmi_infoframe_check() - check a HDMI infoframe
 * @frame: HDMI infoframe
 *
 * Validates that the infoframe is consistent and updates derived fields
 * (eg. length) based on other fields.
 *
 * Returns 0 on success or a negative error code on failure.
 */
पूर्णांक
hdmi_infoframe_check(जोड़ hdmi_infoframe *frame)
अणु
	चयन (frame->any.type) अणु
	हाल HDMI_INFOFRAME_TYPE_AVI:
		वापस hdmi_avi_infoframe_check(&frame->avi);
	हाल HDMI_INFOFRAME_TYPE_SPD:
		वापस hdmi_spd_infoframe_check(&frame->spd);
	हाल HDMI_INFOFRAME_TYPE_AUDIO:
		वापस hdmi_audio_infoframe_check(&frame->audio);
	हाल HDMI_INFOFRAME_TYPE_VENDOR:
		वापस hdmi_venकरोr_any_infoframe_check(&frame->venकरोr);
	शेष:
		WARN(1, "Bad infoframe type %d\n", frame->any.type);
		वापस -EINVAL;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(hdmi_infoframe_check);

/**
 * hdmi_infoframe_pack_only() - ग_लिखो a HDMI infoframe to binary buffer
 * @frame: HDMI infoframe
 * @buffer: destination buffer
 * @size: size of buffer
 *
 * Packs the inक्रमmation contained in the @frame काष्ठाure पूर्णांकo a binary
 * representation that can be written पूर्णांकo the corresponding controller
 * रेजिस्टरs. Also computes the checksum as required by section 5.3.5 of
 * the HDMI 1.4 specअगरication.
 *
 * Returns the number of bytes packed पूर्णांकo the binary buffer or a negative
 * error code on failure.
 */
sमाप_प्रकार
hdmi_infoframe_pack_only(स्थिर जोड़ hdmi_infoframe *frame, व्योम *buffer, माप_प्रकार size)
अणु
	sमाप_प्रकार length;

	चयन (frame->any.type) अणु
	हाल HDMI_INFOFRAME_TYPE_AVI:
		length = hdmi_avi_infoframe_pack_only(&frame->avi,
						      buffer, size);
		अवरोध;
	हाल HDMI_INFOFRAME_TYPE_DRM:
		length = hdmi_drm_infoframe_pack_only(&frame->drm,
						      buffer, size);
		अवरोध;
	हाल HDMI_INFOFRAME_TYPE_SPD:
		length = hdmi_spd_infoframe_pack_only(&frame->spd,
						      buffer, size);
		अवरोध;
	हाल HDMI_INFOFRAME_TYPE_AUDIO:
		length = hdmi_audio_infoframe_pack_only(&frame->audio,
							buffer, size);
		अवरोध;
	हाल HDMI_INFOFRAME_TYPE_VENDOR:
		length = hdmi_venकरोr_any_infoframe_pack_only(&frame->venकरोr,
							     buffer, size);
		अवरोध;
	शेष:
		WARN(1, "Bad infoframe type %d\n", frame->any.type);
		length = -EINVAL;
	पूर्ण

	वापस length;
पूर्ण
EXPORT_SYMBOL(hdmi_infoframe_pack_only);

/**
 * hdmi_infoframe_pack() - check a HDMI infoframe,
 *                         and ग_लिखो it to binary buffer
 * @frame: HDMI infoframe
 * @buffer: destination buffer
 * @size: size of buffer
 *
 * Validates that the infoframe is consistent and updates derived fields
 * (eg. length) based on other fields, after which it packs the inक्रमmation
 * contained in the @frame काष्ठाure पूर्णांकo a binary representation that
 * can be written पूर्णांकo the corresponding controller रेजिस्टरs. This function
 * also computes the checksum as required by section 5.3.5 of the HDMI 1.4
 * specअगरication.
 *
 * Returns the number of bytes packed पूर्णांकo the binary buffer or a negative
 * error code on failure.
 */
sमाप_प्रकार
hdmi_infoframe_pack(जोड़ hdmi_infoframe *frame,
		    व्योम *buffer, माप_प्रकार size)
अणु
	sमाप_प्रकार length;

	चयन (frame->any.type) अणु
	हाल HDMI_INFOFRAME_TYPE_AVI:
		length = hdmi_avi_infoframe_pack(&frame->avi, buffer, size);
		अवरोध;
	हाल HDMI_INFOFRAME_TYPE_DRM:
		length = hdmi_drm_infoframe_pack(&frame->drm, buffer, size);
		अवरोध;
	हाल HDMI_INFOFRAME_TYPE_SPD:
		length = hdmi_spd_infoframe_pack(&frame->spd, buffer, size);
		अवरोध;
	हाल HDMI_INFOFRAME_TYPE_AUDIO:
		length = hdmi_audio_infoframe_pack(&frame->audio, buffer, size);
		अवरोध;
	हाल HDMI_INFOFRAME_TYPE_VENDOR:
		length = hdmi_venकरोr_any_infoframe_pack(&frame->venकरोr,
							buffer, size);
		अवरोध;
	शेष:
		WARN(1, "Bad infoframe type %d\n", frame->any.type);
		length = -EINVAL;
	पूर्ण

	वापस length;
पूर्ण
EXPORT_SYMBOL(hdmi_infoframe_pack);

अटल स्थिर अक्षर *hdmi_infoframe_type_get_name(क्रमागत hdmi_infoframe_type type)
अणु
	अगर (type < 0x80 || type > 0x9f)
		वापस "Invalid";
	चयन (type) अणु
	हाल HDMI_INFOFRAME_TYPE_VENDOR:
		वापस "Vendor";
	हाल HDMI_INFOFRAME_TYPE_AVI:
		वापस "Auxiliary Video Information (AVI)";
	हाल HDMI_INFOFRAME_TYPE_SPD:
		वापस "Source Product Description (SPD)";
	हाल HDMI_INFOFRAME_TYPE_AUDIO:
		वापस "Audio";
	हाल HDMI_INFOFRAME_TYPE_DRM:
		वापस "Dynamic Range and Mastering";
	पूर्ण
	वापस "Reserved";
पूर्ण

अटल व्योम hdmi_infoframe_log_header(स्थिर अक्षर *level,
				      काष्ठा device *dev,
				      स्थिर काष्ठा hdmi_any_infoframe *frame)
अणु
	hdmi_log("HDMI infoframe: %s, version %u, length %u\n",
		hdmi_infoframe_type_get_name(frame->type),
		frame->version, frame->length);
पूर्ण

अटल स्थिर अक्षर *hdmi_colorspace_get_name(क्रमागत hdmi_colorspace colorspace)
अणु
	चयन (colorspace) अणु
	हाल HDMI_COLORSPACE_RGB:
		वापस "RGB";
	हाल HDMI_COLORSPACE_YUV422:
		वापस "YCbCr 4:2:2";
	हाल HDMI_COLORSPACE_YUV444:
		वापस "YCbCr 4:4:4";
	हाल HDMI_COLORSPACE_YUV420:
		वापस "YCbCr 4:2:0";
	हाल HDMI_COLORSPACE_RESERVED4:
		वापस "Reserved (4)";
	हाल HDMI_COLORSPACE_RESERVED5:
		वापस "Reserved (5)";
	हाल HDMI_COLORSPACE_RESERVED6:
		वापस "Reserved (6)";
	हाल HDMI_COLORSPACE_IDO_DEFINED:
		वापस "IDO Defined";
	पूर्ण
	वापस "Invalid";
पूर्ण

अटल स्थिर अक्षर *hdmi_scan_mode_get_name(क्रमागत hdmi_scan_mode scan_mode)
अणु
	चयन (scan_mode) अणु
	हाल HDMI_SCAN_MODE_NONE:
		वापस "No Data";
	हाल HDMI_SCAN_MODE_OVERSCAN:
		वापस "Overscan";
	हाल HDMI_SCAN_MODE_UNDERSCAN:
		वापस "Underscan";
	हाल HDMI_SCAN_MODE_RESERVED:
		वापस "Reserved";
	पूर्ण
	वापस "Invalid";
पूर्ण

अटल स्थिर अक्षर *hdmi_colorimetry_get_name(क्रमागत hdmi_colorimetry colorimetry)
अणु
	चयन (colorimetry) अणु
	हाल HDMI_COLORIMETRY_NONE:
		वापस "No Data";
	हाल HDMI_COLORIMETRY_ITU_601:
		वापस "ITU601";
	हाल HDMI_COLORIMETRY_ITU_709:
		वापस "ITU709";
	हाल HDMI_COLORIMETRY_EXTENDED:
		वापस "Extended";
	पूर्ण
	वापस "Invalid";
पूर्ण

अटल स्थिर अक्षर *
hdmi_picture_aspect_get_name(क्रमागत hdmi_picture_aspect picture_aspect)
अणु
	चयन (picture_aspect) अणु
	हाल HDMI_PICTURE_ASPECT_NONE:
		वापस "No Data";
	हाल HDMI_PICTURE_ASPECT_4_3:
		वापस "4:3";
	हाल HDMI_PICTURE_ASPECT_16_9:
		वापस "16:9";
	हाल HDMI_PICTURE_ASPECT_64_27:
		वापस "64:27";
	हाल HDMI_PICTURE_ASPECT_256_135:
		वापस "256:135";
	हाल HDMI_PICTURE_ASPECT_RESERVED:
		वापस "Reserved";
	पूर्ण
	वापस "Invalid";
पूर्ण

अटल स्थिर अक्षर *
hdmi_active_aspect_get_name(क्रमागत hdmi_active_aspect active_aspect)
अणु
	अगर (active_aspect < 0 || active_aspect > 0xf)
		वापस "Invalid";

	चयन (active_aspect) अणु
	हाल HDMI_ACTIVE_ASPECT_16_9_TOP:
		वापस "16:9 Top";
	हाल HDMI_ACTIVE_ASPECT_14_9_TOP:
		वापस "14:9 Top";
	हाल HDMI_ACTIVE_ASPECT_16_9_CENTER:
		वापस "16:9 Center";
	हाल HDMI_ACTIVE_ASPECT_PICTURE:
		वापस "Same as Picture";
	हाल HDMI_ACTIVE_ASPECT_4_3:
		वापस "4:3";
	हाल HDMI_ACTIVE_ASPECT_16_9:
		वापस "16:9";
	हाल HDMI_ACTIVE_ASPECT_14_9:
		वापस "14:9";
	हाल HDMI_ACTIVE_ASPECT_4_3_SP_14_9:
		वापस "4:3 SP 14:9";
	हाल HDMI_ACTIVE_ASPECT_16_9_SP_14_9:
		वापस "16:9 SP 14:9";
	हाल HDMI_ACTIVE_ASPECT_16_9_SP_4_3:
		वापस "16:9 SP 4:3";
	पूर्ण
	वापस "Reserved";
पूर्ण

अटल स्थिर अक्षर *
hdmi_extended_colorimetry_get_name(क्रमागत hdmi_extended_colorimetry ext_col)
अणु
	चयन (ext_col) अणु
	हाल HDMI_EXTENDED_COLORIMETRY_XV_YCC_601:
		वापस "xvYCC 601";
	हाल HDMI_EXTENDED_COLORIMETRY_XV_YCC_709:
		वापस "xvYCC 709";
	हाल HDMI_EXTENDED_COLORIMETRY_S_YCC_601:
		वापस "sYCC 601";
	हाल HDMI_EXTENDED_COLORIMETRY_OPYCC_601:
		वापस "opYCC 601";
	हाल HDMI_EXTENDED_COLORIMETRY_OPRGB:
		वापस "opRGB";
	हाल HDMI_EXTENDED_COLORIMETRY_BT2020_CONST_LUM:
		वापस "BT.2020 Constant Luminance";
	हाल HDMI_EXTENDED_COLORIMETRY_BT2020:
		वापस "BT.2020";
	हाल HDMI_EXTENDED_COLORIMETRY_RESERVED:
		वापस "Reserved";
	पूर्ण
	वापस "Invalid";
पूर्ण

अटल स्थिर अक्षर *
hdmi_quantization_range_get_name(क्रमागत hdmi_quantization_range qrange)
अणु
	चयन (qrange) अणु
	हाल HDMI_QUANTIZATION_RANGE_DEFAULT:
		वापस "Default";
	हाल HDMI_QUANTIZATION_RANGE_LIMITED:
		वापस "Limited";
	हाल HDMI_QUANTIZATION_RANGE_FULL:
		वापस "Full";
	हाल HDMI_QUANTIZATION_RANGE_RESERVED:
		वापस "Reserved";
	पूर्ण
	वापस "Invalid";
पूर्ण

अटल स्थिर अक्षर *hdmi_nups_get_name(क्रमागत hdmi_nups nups)
अणु
	चयन (nups) अणु
	हाल HDMI_NUPS_UNKNOWN:
		वापस "Unknown Non-uniform Scaling";
	हाल HDMI_NUPS_HORIZONTAL:
		वापस "Horizontally Scaled";
	हाल HDMI_NUPS_VERTICAL:
		वापस "Vertically Scaled";
	हाल HDMI_NUPS_BOTH:
		वापस "Horizontally and Vertically Scaled";
	पूर्ण
	वापस "Invalid";
पूर्ण

अटल स्थिर अक्षर *
hdmi_ycc_quantization_range_get_name(क्रमागत hdmi_ycc_quantization_range qrange)
अणु
	चयन (qrange) अणु
	हाल HDMI_YCC_QUANTIZATION_RANGE_LIMITED:
		वापस "Limited";
	हाल HDMI_YCC_QUANTIZATION_RANGE_FULL:
		वापस "Full";
	पूर्ण
	वापस "Invalid";
पूर्ण

अटल स्थिर अक्षर *
hdmi_content_type_get_name(क्रमागत hdmi_content_type content_type)
अणु
	चयन (content_type) अणु
	हाल HDMI_CONTENT_TYPE_GRAPHICS:
		वापस "Graphics";
	हाल HDMI_CONTENT_TYPE_PHOTO:
		वापस "Photo";
	हाल HDMI_CONTENT_TYPE_CINEMA:
		वापस "Cinema";
	हाल HDMI_CONTENT_TYPE_GAME:
		वापस "Game";
	पूर्ण
	वापस "Invalid";
पूर्ण

अटल व्योम hdmi_avi_infoframe_log(स्थिर अक्षर *level,
				   काष्ठा device *dev,
				   स्थिर काष्ठा hdmi_avi_infoframe *frame)
अणु
	hdmi_infoframe_log_header(level, dev,
				  (स्थिर काष्ठा hdmi_any_infoframe *)frame);

	hdmi_log("    colorspace: %s\n",
			hdmi_colorspace_get_name(frame->colorspace));
	hdmi_log("    scan mode: %s\n",
			hdmi_scan_mode_get_name(frame->scan_mode));
	hdmi_log("    colorimetry: %s\n",
			hdmi_colorimetry_get_name(frame->colorimetry));
	hdmi_log("    picture aspect: %s\n",
			hdmi_picture_aspect_get_name(frame->picture_aspect));
	hdmi_log("    active aspect: %s\n",
			hdmi_active_aspect_get_name(frame->active_aspect));
	hdmi_log("    itc: %s\n", frame->itc ? "IT Content" : "No Data");
	hdmi_log("    extended colorimetry: %s\n",
			hdmi_extended_colorimetry_get_name(frame->extended_colorimetry));
	hdmi_log("    quantization range: %s\n",
			hdmi_quantization_range_get_name(frame->quantization_range));
	hdmi_log("    nups: %s\n", hdmi_nups_get_name(frame->nups));
	hdmi_log("    video code: %u\n", frame->video_code);
	hdmi_log("    ycc quantization range: %s\n",
			hdmi_ycc_quantization_range_get_name(frame->ycc_quantization_range));
	hdmi_log("    hdmi content type: %s\n",
			hdmi_content_type_get_name(frame->content_type));
	hdmi_log("    pixel repeat: %u\n", frame->pixel_repeat);
	hdmi_log("    bar top %u, bottom %u, left %u, right %u\n",
			frame->top_bar, frame->bottom_bar,
			frame->left_bar, frame->right_bar);
पूर्ण

अटल स्थिर अक्षर *hdmi_spd_sdi_get_name(क्रमागत hdmi_spd_sdi sdi)
अणु
	अगर (sdi < 0 || sdi > 0xff)
		वापस "Invalid";
	चयन (sdi) अणु
	हाल HDMI_SPD_SDI_UNKNOWN:
		वापस "Unknown";
	हाल HDMI_SPD_SDI_DSTB:
		वापस "Digital STB";
	हाल HDMI_SPD_SDI_DVDP:
		वापस "DVD Player";
	हाल HDMI_SPD_SDI_DVHS:
		वापस "D-VHS";
	हाल HDMI_SPD_SDI_HDDVR:
		वापस "HDD Videorecorder";
	हाल HDMI_SPD_SDI_DVC:
		वापस "DVC";
	हाल HDMI_SPD_SDI_DSC:
		वापस "DSC";
	हाल HDMI_SPD_SDI_VCD:
		वापस "Video CD";
	हाल HDMI_SPD_SDI_GAME:
		वापस "Game";
	हाल HDMI_SPD_SDI_PC:
		वापस "PC General";
	हाल HDMI_SPD_SDI_BD:
		वापस "Blu-Ray Disc (BD)";
	हाल HDMI_SPD_SDI_SACD:
		वापस "Super Audio CD";
	हाल HDMI_SPD_SDI_HDDVD:
		वापस "HD DVD";
	हाल HDMI_SPD_SDI_PMP:
		वापस "PMP";
	पूर्ण
	वापस "Reserved";
पूर्ण

अटल व्योम hdmi_spd_infoframe_log(स्थिर अक्षर *level,
				   काष्ठा device *dev,
				   स्थिर काष्ठा hdmi_spd_infoframe *frame)
अणु
	u8 buf[17];

	hdmi_infoframe_log_header(level, dev,
				  (स्थिर काष्ठा hdmi_any_infoframe *)frame);

	स_रखो(buf, 0, माप(buf));

	म_नकलन(buf, frame->venकरोr, 8);
	hdmi_log("    vendor: %s\n", buf);
	म_नकलन(buf, frame->product, 16);
	hdmi_log("    product: %s\n", buf);
	hdmi_log("    source device information: %s (0x%x)\n",
		hdmi_spd_sdi_get_name(frame->sdi), frame->sdi);
पूर्ण

अटल स्थिर अक्षर *
hdmi_audio_coding_type_get_name(क्रमागत hdmi_audio_coding_type coding_type)
अणु
	चयन (coding_type) अणु
	हाल HDMI_AUDIO_CODING_TYPE_STREAM:
		वापस "Refer to Stream Header";
	हाल HDMI_AUDIO_CODING_TYPE_PCM:
		वापस "PCM";
	हाल HDMI_AUDIO_CODING_TYPE_AC3:
		वापस "AC-3";
	हाल HDMI_AUDIO_CODING_TYPE_MPEG1:
		वापस "MPEG1";
	हाल HDMI_AUDIO_CODING_TYPE_MP3:
		वापस "MP3";
	हाल HDMI_AUDIO_CODING_TYPE_MPEG2:
		वापस "MPEG2";
	हाल HDMI_AUDIO_CODING_TYPE_AAC_LC:
		वापस "AAC";
	हाल HDMI_AUDIO_CODING_TYPE_DTS:
		वापस "DTS";
	हाल HDMI_AUDIO_CODING_TYPE_ATRAC:
		वापस "ATRAC";
	हाल HDMI_AUDIO_CODING_TYPE_DSD:
		वापस "One Bit Audio";
	हाल HDMI_AUDIO_CODING_TYPE_EAC3:
		वापस "Dolby Digital +";
	हाल HDMI_AUDIO_CODING_TYPE_DTS_HD:
		वापस "DTS-HD";
	हाल HDMI_AUDIO_CODING_TYPE_MLP:
		वापस "MAT (MLP)";
	हाल HDMI_AUDIO_CODING_TYPE_DST:
		वापस "DST";
	हाल HDMI_AUDIO_CODING_TYPE_WMA_PRO:
		वापस "WMA PRO";
	हाल HDMI_AUDIO_CODING_TYPE_CXT:
		वापस "Refer to CXT";
	पूर्ण
	वापस "Invalid";
पूर्ण

अटल स्थिर अक्षर *
hdmi_audio_sample_size_get_name(क्रमागत hdmi_audio_sample_size sample_size)
अणु
	चयन (sample_size) अणु
	हाल HDMI_AUDIO_SAMPLE_SIZE_STREAM:
		वापस "Refer to Stream Header";
	हाल HDMI_AUDIO_SAMPLE_SIZE_16:
		वापस "16 bit";
	हाल HDMI_AUDIO_SAMPLE_SIZE_20:
		वापस "20 bit";
	हाल HDMI_AUDIO_SAMPLE_SIZE_24:
		वापस "24 bit";
	पूर्ण
	वापस "Invalid";
पूर्ण

अटल स्थिर अक्षर *
hdmi_audio_sample_frequency_get_name(क्रमागत hdmi_audio_sample_frequency freq)
अणु
	चयन (freq) अणु
	हाल HDMI_AUDIO_SAMPLE_FREQUENCY_STREAM:
		वापस "Refer to Stream Header";
	हाल HDMI_AUDIO_SAMPLE_FREQUENCY_32000:
		वापस "32 kHz";
	हाल HDMI_AUDIO_SAMPLE_FREQUENCY_44100:
		वापस "44.1 kHz (CD)";
	हाल HDMI_AUDIO_SAMPLE_FREQUENCY_48000:
		वापस "48 kHz";
	हाल HDMI_AUDIO_SAMPLE_FREQUENCY_88200:
		वापस "88.2 kHz";
	हाल HDMI_AUDIO_SAMPLE_FREQUENCY_96000:
		वापस "96 kHz";
	हाल HDMI_AUDIO_SAMPLE_FREQUENCY_176400:
		वापस "176.4 kHz";
	हाल HDMI_AUDIO_SAMPLE_FREQUENCY_192000:
		वापस "192 kHz";
	पूर्ण
	वापस "Invalid";
पूर्ण

अटल स्थिर अक्षर *
hdmi_audio_coding_type_ext_get_name(क्रमागत hdmi_audio_coding_type_ext ctx)
अणु
	अगर (ctx < 0 || ctx > 0x1f)
		वापस "Invalid";

	चयन (ctx) अणु
	हाल HDMI_AUDIO_CODING_TYPE_EXT_CT:
		वापस "Refer to CT";
	हाल HDMI_AUDIO_CODING_TYPE_EXT_HE_AAC:
		वापस "HE AAC";
	हाल HDMI_AUDIO_CODING_TYPE_EXT_HE_AAC_V2:
		वापस "HE AAC v2";
	हाल HDMI_AUDIO_CODING_TYPE_EXT_MPEG_SURROUND:
		वापस "MPEG SURROUND";
	हाल HDMI_AUDIO_CODING_TYPE_EXT_MPEG4_HE_AAC:
		वापस "MPEG-4 HE AAC";
	हाल HDMI_AUDIO_CODING_TYPE_EXT_MPEG4_HE_AAC_V2:
		वापस "MPEG-4 HE AAC v2";
	हाल HDMI_AUDIO_CODING_TYPE_EXT_MPEG4_AAC_LC:
		वापस "MPEG-4 AAC LC";
	हाल HDMI_AUDIO_CODING_TYPE_EXT_DRA:
		वापस "DRA";
	हाल HDMI_AUDIO_CODING_TYPE_EXT_MPEG4_HE_AAC_SURROUND:
		वापस "MPEG-4 HE AAC + MPEG Surround";
	हाल HDMI_AUDIO_CODING_TYPE_EXT_MPEG4_AAC_LC_SURROUND:
		वापस "MPEG-4 AAC LC + MPEG Surround";
	पूर्ण
	वापस "Reserved";
पूर्ण

अटल व्योम hdmi_audio_infoframe_log(स्थिर अक्षर *level,
				     काष्ठा device *dev,
				     स्थिर काष्ठा hdmi_audio_infoframe *frame)
अणु
	hdmi_infoframe_log_header(level, dev,
				  (स्थिर काष्ठा hdmi_any_infoframe *)frame);

	अगर (frame->channels)
		hdmi_log("    channels: %u\n", frame->channels - 1);
	अन्यथा
		hdmi_log("    channels: Refer to stream header\n");
	hdmi_log("    coding type: %s\n",
			hdmi_audio_coding_type_get_name(frame->coding_type));
	hdmi_log("    sample size: %s\n",
			hdmi_audio_sample_size_get_name(frame->sample_size));
	hdmi_log("    sample frequency: %s\n",
			hdmi_audio_sample_frequency_get_name(frame->sample_frequency));
	hdmi_log("    coding type ext: %s\n",
			hdmi_audio_coding_type_ext_get_name(frame->coding_type_ext));
	hdmi_log("    channel allocation: 0x%x\n",
			frame->channel_allocation);
	hdmi_log("    level shift value: %u dB\n",
			frame->level_shअगरt_value);
	hdmi_log("    downmix inhibit: %s\n",
			frame->करोwnmix_inhibit ? "Yes" : "No");
पूर्ण

अटल व्योम hdmi_drm_infoframe_log(स्थिर अक्षर *level,
				   काष्ठा device *dev,
				   स्थिर काष्ठा hdmi_drm_infoframe *frame)
अणु
	पूर्णांक i;

	hdmi_infoframe_log_header(level, dev,
				  (काष्ठा hdmi_any_infoframe *)frame);
	hdmi_log("length: %d\n", frame->length);
	hdmi_log("metadata type: %d\n", frame->metadata_type);
	hdmi_log("eotf: %d\n", frame->eotf);
	क्रम (i = 0; i < 3; i++) अणु
		hdmi_log("x[%d]: %d\n", i, frame->display_primaries[i].x);
		hdmi_log("y[%d]: %d\n", i, frame->display_primaries[i].y);
	पूर्ण

	hdmi_log("white point x: %d\n", frame->white_poपूर्णांक.x);
	hdmi_log("white point y: %d\n", frame->white_poपूर्णांक.y);

	hdmi_log("max_display_mastering_luminance: %d\n",
		 frame->max_display_mastering_luminance);
	hdmi_log("min_display_mastering_luminance: %d\n",
		 frame->min_display_mastering_luminance);

	hdmi_log("max_cll: %d\n", frame->max_cll);
	hdmi_log("max_fall: %d\n", frame->max_fall);
पूर्ण

अटल स्थिर अक्षर *
hdmi_3d_काष्ठाure_get_name(क्रमागत hdmi_3d_काष्ठाure s3d_काष्ठा)
अणु
	अगर (s3d_काष्ठा < 0 || s3d_काष्ठा > 0xf)
		वापस "Invalid";

	चयन (s3d_काष्ठा) अणु
	हाल HDMI_3D_STRUCTURE_FRAME_PACKING:
		वापस "Frame Packing";
	हाल HDMI_3D_STRUCTURE_FIELD_ALTERNATIVE:
		वापस "Field Alternative";
	हाल HDMI_3D_STRUCTURE_LINE_ALTERNATIVE:
		वापस "Line Alternative";
	हाल HDMI_3D_STRUCTURE_SIDE_BY_SIDE_FULL:
		वापस "Side-by-side (Full)";
	हाल HDMI_3D_STRUCTURE_L_DEPTH:
		वापस "L + Depth";
	हाल HDMI_3D_STRUCTURE_L_DEPTH_GFX_GFX_DEPTH:
		वापस "L + Depth + Graphics + Graphics-depth";
	हाल HDMI_3D_STRUCTURE_TOP_AND_BOTTOM:
		वापस "Top-and-Bottom";
	हाल HDMI_3D_STRUCTURE_SIDE_BY_SIDE_HALF:
		वापस "Side-by-side (Half)";
	शेष:
		अवरोध;
	पूर्ण
	वापस "Reserved";
पूर्ण

अटल व्योम
hdmi_venकरोr_any_infoframe_log(स्थिर अक्षर *level,
			      काष्ठा device *dev,
			      स्थिर जोड़ hdmi_venकरोr_any_infoframe *frame)
अणु
	स्थिर काष्ठा hdmi_venकरोr_infoframe *hvf = &frame->hdmi;

	hdmi_infoframe_log_header(level, dev,
				  (स्थिर काष्ठा hdmi_any_infoframe *)frame);

	अगर (frame->any.oui != HDMI_IEEE_OUI) अणु
		hdmi_log("    not a HDMI vendor infoframe\n");
		वापस;
	पूर्ण
	अगर (hvf->vic == 0 && hvf->s3d_काष्ठा == HDMI_3D_STRUCTURE_INVALID) अणु
		hdmi_log("    empty frame\n");
		वापस;
	पूर्ण

	अगर (hvf->vic)
		hdmi_log("    HDMI VIC: %u\n", hvf->vic);
	अगर (hvf->s3d_काष्ठा != HDMI_3D_STRUCTURE_INVALID) अणु
		hdmi_log("    3D structure: %s\n",
				hdmi_3d_काष्ठाure_get_name(hvf->s3d_काष्ठा));
		अगर (hvf->s3d_काष्ठा >= HDMI_3D_STRUCTURE_SIDE_BY_SIDE_HALF)
			hdmi_log("    3D extension data: %d\n",
					hvf->s3d_ext_data);
	पूर्ण
पूर्ण

/**
 * hdmi_infoframe_log() - log info of HDMI infoframe
 * @level: logging level
 * @dev: device
 * @frame: HDMI infoframe
 */
व्योम hdmi_infoframe_log(स्थिर अक्षर *level,
			काष्ठा device *dev,
			स्थिर जोड़ hdmi_infoframe *frame)
अणु
	चयन (frame->any.type) अणु
	हाल HDMI_INFOFRAME_TYPE_AVI:
		hdmi_avi_infoframe_log(level, dev, &frame->avi);
		अवरोध;
	हाल HDMI_INFOFRAME_TYPE_SPD:
		hdmi_spd_infoframe_log(level, dev, &frame->spd);
		अवरोध;
	हाल HDMI_INFOFRAME_TYPE_AUDIO:
		hdmi_audio_infoframe_log(level, dev, &frame->audio);
		अवरोध;
	हाल HDMI_INFOFRAME_TYPE_VENDOR:
		hdmi_venकरोr_any_infoframe_log(level, dev, &frame->venकरोr);
		अवरोध;
	हाल HDMI_INFOFRAME_TYPE_DRM:
		hdmi_drm_infoframe_log(level, dev, &frame->drm);
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(hdmi_infoframe_log);

/**
 * hdmi_avi_infoframe_unpack() - unpack binary buffer to a HDMI AVI infoframe
 * @frame: HDMI AVI infoframe
 * @buffer: source buffer
 * @size: size of buffer
 *
 * Unpacks the inक्रमmation contained in binary @buffer पूर्णांकo a काष्ठाured
 * @frame of the HDMI Auxiliary Video (AVI) inक्रमmation frame.
 * Also verअगरies the checksum as required by section 5.3.5 of the HDMI 1.4
 * specअगरication.
 *
 * Returns 0 on success or a negative error code on failure.
 */
अटल पूर्णांक hdmi_avi_infoframe_unpack(काष्ठा hdmi_avi_infoframe *frame,
				     स्थिर व्योम *buffer, माप_प्रकार size)
अणु
	स्थिर u8 *ptr = buffer;

	अगर (size < HDMI_INFOFRAME_SIZE(AVI))
		वापस -EINVAL;

	अगर (ptr[0] != HDMI_INFOFRAME_TYPE_AVI ||
	    ptr[1] != 2 ||
	    ptr[2] != HDMI_AVI_INFOFRAME_SIZE)
		वापस -EINVAL;

	अगर (hdmi_infoframe_checksum(buffer, HDMI_INFOFRAME_SIZE(AVI)) != 0)
		वापस -EINVAL;

	hdmi_avi_infoframe_init(frame);

	ptr += HDMI_INFOFRAME_HEADER_SIZE;

	frame->colorspace = (ptr[0] >> 5) & 0x3;
	अगर (ptr[0] & 0x10)
		frame->active_aspect = ptr[1] & 0xf;
	अगर (ptr[0] & 0x8) अणु
		frame->top_bar = (ptr[6] << 8) | ptr[5];
		frame->bottom_bar = (ptr[8] << 8) | ptr[7];
	पूर्ण
	अगर (ptr[0] & 0x4) अणु
		frame->left_bar = (ptr[10] << 8) | ptr[9];
		frame->right_bar = (ptr[12] << 8) | ptr[11];
	पूर्ण
	frame->scan_mode = ptr[0] & 0x3;

	frame->colorimetry = (ptr[1] >> 6) & 0x3;
	frame->picture_aspect = (ptr[1] >> 4) & 0x3;
	frame->active_aspect = ptr[1] & 0xf;

	frame->itc = ptr[2] & 0x80 ? true : false;
	frame->extended_colorimetry = (ptr[2] >> 4) & 0x7;
	frame->quantization_range = (ptr[2] >> 2) & 0x3;
	frame->nups = ptr[2] & 0x3;

	frame->video_code = ptr[3] & 0x7f;
	frame->ycc_quantization_range = (ptr[4] >> 6) & 0x3;
	frame->content_type = (ptr[4] >> 4) & 0x3;

	frame->pixel_repeat = ptr[4] & 0xf;

	वापस 0;
पूर्ण

/**
 * hdmi_spd_infoframe_unpack() - unpack binary buffer to a HDMI SPD infoframe
 * @frame: HDMI SPD infoframe
 * @buffer: source buffer
 * @size: size of buffer
 *
 * Unpacks the inक्रमmation contained in binary @buffer पूर्णांकo a काष्ठाured
 * @frame of the HDMI Source Product Description (SPD) inक्रमmation frame.
 * Also verअगरies the checksum as required by section 5.3.5 of the HDMI 1.4
 * specअगरication.
 *
 * Returns 0 on success or a negative error code on failure.
 */
अटल पूर्णांक hdmi_spd_infoframe_unpack(काष्ठा hdmi_spd_infoframe *frame,
				     स्थिर व्योम *buffer, माप_प्रकार size)
अणु
	स्थिर u8 *ptr = buffer;
	पूर्णांक ret;

	अगर (size < HDMI_INFOFRAME_SIZE(SPD))
		वापस -EINVAL;

	अगर (ptr[0] != HDMI_INFOFRAME_TYPE_SPD ||
	    ptr[1] != 1 ||
	    ptr[2] != HDMI_SPD_INFOFRAME_SIZE) अणु
		वापस -EINVAL;
	पूर्ण

	अगर (hdmi_infoframe_checksum(buffer, HDMI_INFOFRAME_SIZE(SPD)) != 0)
		वापस -EINVAL;

	ptr += HDMI_INFOFRAME_HEADER_SIZE;

	ret = hdmi_spd_infoframe_init(frame, ptr, ptr + 8);
	अगर (ret)
		वापस ret;

	frame->sdi = ptr[24];

	वापस 0;
पूर्ण

/**
 * hdmi_audio_infoframe_unpack() - unpack binary buffer to a HDMI AUDIO infoframe
 * @frame: HDMI Audio infoframe
 * @buffer: source buffer
 * @size: size of buffer
 *
 * Unpacks the inक्रमmation contained in binary @buffer पूर्णांकo a काष्ठाured
 * @frame of the HDMI Audio inक्रमmation frame.
 * Also verअगरies the checksum as required by section 5.3.5 of the HDMI 1.4
 * specअगरication.
 *
 * Returns 0 on success or a negative error code on failure.
 */
अटल पूर्णांक hdmi_audio_infoframe_unpack(काष्ठा hdmi_audio_infoframe *frame,
				       स्थिर व्योम *buffer, माप_प्रकार size)
अणु
	स्थिर u8 *ptr = buffer;
	पूर्णांक ret;

	अगर (size < HDMI_INFOFRAME_SIZE(AUDIO))
		वापस -EINVAL;

	अगर (ptr[0] != HDMI_INFOFRAME_TYPE_AUDIO ||
	    ptr[1] != 1 ||
	    ptr[2] != HDMI_AUDIO_INFOFRAME_SIZE) अणु
		वापस -EINVAL;
	पूर्ण

	अगर (hdmi_infoframe_checksum(buffer, HDMI_INFOFRAME_SIZE(AUDIO)) != 0)
		वापस -EINVAL;

	ret = hdmi_audio_infoframe_init(frame);
	अगर (ret)
		वापस ret;

	ptr += HDMI_INFOFRAME_HEADER_SIZE;

	frame->channels = ptr[0] & 0x7;
	frame->coding_type = (ptr[0] >> 4) & 0xf;
	frame->sample_size = ptr[1] & 0x3;
	frame->sample_frequency = (ptr[1] >> 2) & 0x7;
	frame->coding_type_ext = ptr[2] & 0x1f;
	frame->channel_allocation = ptr[3];
	frame->level_shअगरt_value = (ptr[4] >> 3) & 0xf;
	frame->करोwnmix_inhibit = ptr[4] & 0x80 ? true : false;

	वापस 0;
पूर्ण

/**
 * hdmi_venकरोr_any_infoframe_unpack() - unpack binary buffer to a HDMI
 * 	venकरोr infoframe
 * @frame: HDMI Venकरोr infoframe
 * @buffer: source buffer
 * @size: size of buffer
 *
 * Unpacks the inक्रमmation contained in binary @buffer पूर्णांकo a काष्ठाured
 * @frame of the HDMI Venकरोr inक्रमmation frame.
 * Also verअगरies the checksum as required by section 5.3.5 of the HDMI 1.4
 * specअगरication.
 *
 * Returns 0 on success or a negative error code on failure.
 */
अटल पूर्णांक
hdmi_venकरोr_any_infoframe_unpack(जोड़ hdmi_venकरोr_any_infoframe *frame,
				 स्थिर व्योम *buffer, माप_प्रकार size)
अणु
	स्थिर u8 *ptr = buffer;
	माप_प्रकार length;
	पूर्णांक ret;
	u8 hdmi_video_क्रमmat;
	काष्ठा hdmi_venकरोr_infoframe *hvf = &frame->hdmi;

	अगर (size < HDMI_INFOFRAME_HEADER_SIZE)
		वापस -EINVAL;

	अगर (ptr[0] != HDMI_INFOFRAME_TYPE_VENDOR ||
	    ptr[1] != 1 ||
	    (ptr[2] != 4 && ptr[2] != 5 && ptr[2] != 6))
		वापस -EINVAL;

	length = ptr[2];

	अगर (size < HDMI_INFOFRAME_HEADER_SIZE + length)
		वापस -EINVAL;

	अगर (hdmi_infoframe_checksum(buffer,
				    HDMI_INFOFRAME_HEADER_SIZE + length) != 0)
		वापस -EINVAL;

	ptr += HDMI_INFOFRAME_HEADER_SIZE;

	/* HDMI OUI */
	अगर ((ptr[0] != 0x03) ||
	    (ptr[1] != 0x0c) ||
	    (ptr[2] != 0x00))
		वापस -EINVAL;

	hdmi_video_क्रमmat = ptr[3] >> 5;

	अगर (hdmi_video_क्रमmat > 0x2)
		वापस -EINVAL;

	ret = hdmi_venकरोr_infoframe_init(hvf);
	अगर (ret)
		वापस ret;

	hvf->length = length;

	अगर (hdmi_video_क्रमmat == 0x2) अणु
		अगर (length != 5 && length != 6)
			वापस -EINVAL;
		hvf->s3d_काष्ठा = ptr[4] >> 4;
		अगर (hvf->s3d_काष्ठा >= HDMI_3D_STRUCTURE_SIDE_BY_SIDE_HALF) अणु
			अगर (length != 6)
				वापस -EINVAL;
			hvf->s3d_ext_data = ptr[5] >> 4;
		पूर्ण
	पूर्ण अन्यथा अगर (hdmi_video_क्रमmat == 0x1) अणु
		अगर (length != 5)
			वापस -EINVAL;
		hvf->vic = ptr[4];
	पूर्ण अन्यथा अणु
		अगर (length != 4)
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * hdmi_drm_infoframe_unpack_only() - unpack binary buffer of CTA-861-G DRM
 *                                    infoframe DataBytes to a HDMI DRM
 *                                    infoframe
 * @frame: HDMI DRM infoframe
 * @buffer: source buffer
 * @size: size of buffer
 *
 * Unpacks CTA-861-G DRM infoframe DataBytes contained in the binary @buffer
 * पूर्णांकo a काष्ठाured @frame of the HDMI Dynamic Range and Mastering (DRM)
 * infoframe.
 *
 * Returns 0 on success or a negative error code on failure.
 */
पूर्णांक hdmi_drm_infoframe_unpack_only(काष्ठा hdmi_drm_infoframe *frame,
				   स्थिर व्योम *buffer, माप_प्रकार size)
अणु
	स्थिर u8 *ptr = buffer;
	स्थिर u8 *temp;
	u8 x_lsb, x_msb;
	u8 y_lsb, y_msb;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (size < HDMI_DRM_INFOFRAME_SIZE)
		वापस -EINVAL;

	ret = hdmi_drm_infoframe_init(frame);
	अगर (ret)
		वापस ret;

	frame->eotf = ptr[0] & 0x7;
	frame->metadata_type = ptr[1] & 0x7;

	temp = ptr + 2;
	क्रम (i = 0; i < 3; i++) अणु
		x_lsb = *temp++;
		x_msb = *temp++;
		frame->display_primaries[i].x = (x_msb << 8) | x_lsb;
		y_lsb = *temp++;
		y_msb = *temp++;
		frame->display_primaries[i].y = (y_msb << 8) | y_lsb;
	पूर्ण

	frame->white_poपूर्णांक.x = (ptr[15] << 8) | ptr[14];
	frame->white_poपूर्णांक.y = (ptr[17] << 8) | ptr[16];

	frame->max_display_mastering_luminance = (ptr[19] << 8) | ptr[18];
	frame->min_display_mastering_luminance = (ptr[21] << 8) | ptr[20];
	frame->max_cll = (ptr[23] << 8) | ptr[22];
	frame->max_fall = (ptr[25] << 8) | ptr[24];

	वापस 0;
पूर्ण
EXPORT_SYMBOL(hdmi_drm_infoframe_unpack_only);

/**
 * hdmi_drm_infoframe_unpack() - unpack binary buffer to a HDMI DRM infoframe
 * @frame: HDMI DRM infoframe
 * @buffer: source buffer
 * @size: size of buffer
 *
 * Unpacks the CTA-861-G DRM infoframe contained in the binary @buffer पूर्णांकo
 * a काष्ठाured @frame of the HDMI Dynamic Range and Mastering (DRM)
 * infoframe. It also verअगरies the checksum as required by section 5.3.5 of
 * the HDMI 1.4 specअगरication.
 *
 * Returns 0 on success or a negative error code on failure.
 */
अटल पूर्णांक hdmi_drm_infoframe_unpack(काष्ठा hdmi_drm_infoframe *frame,
				     स्थिर व्योम *buffer, माप_प्रकार size)
अणु
	स्थिर u8 *ptr = buffer;
	पूर्णांक ret;

	अगर (size < HDMI_INFOFRAME_SIZE(DRM))
		वापस -EINVAL;

	अगर (ptr[0] != HDMI_INFOFRAME_TYPE_DRM ||
	    ptr[1] != 1 ||
	    ptr[2] != HDMI_DRM_INFOFRAME_SIZE)
		वापस -EINVAL;

	अगर (hdmi_infoframe_checksum(buffer, HDMI_INFOFRAME_SIZE(DRM)) != 0)
		वापस -EINVAL;

	ret = hdmi_drm_infoframe_unpack_only(frame, ptr + HDMI_INFOFRAME_HEADER_SIZE,
					     size - HDMI_INFOFRAME_HEADER_SIZE);
	वापस ret;
पूर्ण

/**
 * hdmi_infoframe_unpack() - unpack binary buffer to a HDMI infoframe
 * @frame: HDMI infoframe
 * @buffer: source buffer
 * @size: size of buffer
 *
 * Unpacks the inक्रमmation contained in binary buffer @buffer पूर्णांकo a काष्ठाured
 * @frame of a HDMI infoframe.
 * Also verअगरies the checksum as required by section 5.3.5 of the HDMI 1.4
 * specअगरication.
 *
 * Returns 0 on success or a negative error code on failure.
 */
पूर्णांक hdmi_infoframe_unpack(जोड़ hdmi_infoframe *frame,
			  स्थिर व्योम *buffer, माप_प्रकार size)
अणु
	पूर्णांक ret;
	स्थिर u8 *ptr = buffer;

	अगर (size < HDMI_INFOFRAME_HEADER_SIZE)
		वापस -EINVAL;

	चयन (ptr[0]) अणु
	हाल HDMI_INFOFRAME_TYPE_AVI:
		ret = hdmi_avi_infoframe_unpack(&frame->avi, buffer, size);
		अवरोध;
	हाल HDMI_INFOFRAME_TYPE_DRM:
		ret = hdmi_drm_infoframe_unpack(&frame->drm, buffer, size);
		अवरोध;
	हाल HDMI_INFOFRAME_TYPE_SPD:
		ret = hdmi_spd_infoframe_unpack(&frame->spd, buffer, size);
		अवरोध;
	हाल HDMI_INFOFRAME_TYPE_AUDIO:
		ret = hdmi_audio_infoframe_unpack(&frame->audio, buffer, size);
		अवरोध;
	हाल HDMI_INFOFRAME_TYPE_VENDOR:
		ret = hdmi_venकरोr_any_infoframe_unpack(&frame->venकरोr, buffer, size);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(hdmi_infoframe_unpack);
