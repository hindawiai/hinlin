<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  HID driver क्रम UC-Logic devices not fully compliant with HID standard
 *  - tablet initialization and parameter retrieval
 *
 *  Copyright (c) 2018 Nikolai Kondrashov
 */

/*
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#समावेश "hid-uclogic-params.h"
#समावेश "hid-uclogic-rdesc.h"
#समावेश "usbhid/usbhid.h"
#समावेश "hid-ids.h"
#समावेश <linux/प्रकार.स>
#समावेश <यंत्र/unaligned.h>

/**
 * uclogic_params_pen_inrange_to_str() - Convert a pen in-range reporting type
 *                                       to a string.
 *
 * @inrange:	The in-range reporting type to convert.
 *
 * Returns:
 *	The string representing the type, or शून्य अगर the type is unknown.
 */
स्थिर अक्षर *uclogic_params_pen_inrange_to_str(
			क्रमागत uclogic_params_pen_inrange inrange)
अणु
	चयन (inrange) अणु
	हाल UCLOGIC_PARAMS_PEN_INRANGE_NORMAL:
		वापस "normal";
	हाल UCLOGIC_PARAMS_PEN_INRANGE_INVERTED:
		वापस "inverted";
	हाल UCLOGIC_PARAMS_PEN_INRANGE_NONE:
		वापस "none";
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

/**
 * uclogic_params_get_str_desc - retrieve a string descriptor from a HID
 * device पूर्णांकerface, putting it पूर्णांकo a kदो_स्मृति-allocated buffer as is, without
 * अक्षरacter encoding conversion.
 *
 * @pbuf:	Location क्रम the kदो_स्मृति-allocated buffer poपूर्णांकer containing
 *		the retrieved descriptor. Not modअगरied in हाल of error.
 *		Can be शून्य to have retrieved descriptor discarded.
 * @hdev:	The HID device of the tablet पूर्णांकerface to retrieve the string
 *		descriptor from. Cannot be शून्य.
 * @idx:	Index of the string descriptor to request from the device.
 * @len:	Length of the buffer to allocate and the data to retrieve.
 *
 * Returns:
 *	number of bytes retrieved (<= len),
 *	-EPIPE, अगर the descriptor was not found, or
 *	another negative त्रुटि_सं code in हाल of other error.
 */
अटल पूर्णांक uclogic_params_get_str_desc(__u8 **pbuf, काष्ठा hid_device *hdev,
					__u8 idx, माप_प्रकार len)
अणु
	पूर्णांक rc;
	काष्ठा usb_device *udev = hid_to_usb_dev(hdev);
	__u8 *buf = शून्य;

	/* Check arguments */
	अगर (hdev == शून्य) अणु
		rc = -EINVAL;
		जाओ cleanup;
	पूर्ण

	buf = kदो_स्मृति(len, GFP_KERNEL);
	अगर (buf == शून्य) अणु
		rc = -ENOMEM;
		जाओ cleanup;
	पूर्ण

	rc = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0),
				USB_REQ_GET_DESCRIPTOR, USB_सूची_IN,
				(USB_DT_STRING << 8) + idx,
				0x0409, buf, len,
				USB_CTRL_GET_TIMEOUT);
	अगर (rc == -EPIPE) अणु
		hid_dbg(hdev, "string descriptor #%hhu not found\n", idx);
		जाओ cleanup;
	पूर्ण अन्यथा अगर (rc < 0) अणु
		hid_err(hdev,
			"failed retrieving string descriptor #%u: %d\n",
			idx, rc);
		जाओ cleanup;
	पूर्ण

	अगर (pbuf != शून्य) अणु
		*pbuf = buf;
		buf = शून्य;
	पूर्ण

cleanup:
	kमुक्त(buf);
	वापस rc;
पूर्ण

/**
 * uclogic_params_pen_cleanup - मुक्त resources used by काष्ठा
 * uclogic_params_pen (tablet पूर्णांकerface's pen input parameters).
 * Can be called repeatedly.
 *
 * @pen:	Pen input parameters to cleanup. Cannot be शून्य.
 */
अटल व्योम uclogic_params_pen_cleanup(काष्ठा uclogic_params_pen *pen)
अणु
	kमुक्त(pen->desc_ptr);
	स_रखो(pen, 0, माप(*pen));
पूर्ण

/**
 * uclogic_params_pen_init_v1() - initialize tablet पूर्णांकerface pen
 * input and retrieve its parameters from the device, using v1 protocol.
 *
 * @pen:	Poपूर्णांकer to the pen parameters to initialize (to be
 *		cleaned up with uclogic_params_pen_cleanup()). Not modअगरied in
 *		हाल of error, or अगर parameters are not found. Cannot be शून्य.
 * @pfound:	Location क्रम a flag which is set to true अगर the parameters
 *		were found, and to false अगर not (e.g. device was
 *		incompatible). Not modअगरied in हाल of error. Cannot be शून्य.
 * @hdev:	The HID device of the tablet पूर्णांकerface to initialize and get
 *		parameters from. Cannot be शून्य.
 *
 * Returns:
 *	Zero, अगर successful. A negative त्रुटि_सं code on error.
 */
अटल पूर्णांक uclogic_params_pen_init_v1(काष्ठा uclogic_params_pen *pen,
				      bool *pfound,
				      काष्ठा hid_device *hdev)
अणु
	पूर्णांक rc;
	bool found = false;
	/* Buffer क्रम (part of) the string descriptor */
	__u8 *buf = शून्य;
	/* Minimum descriptor length required, maximum seen so far is 18 */
	स्थिर पूर्णांक len = 12;
	s32 resolution;
	/* Pen report descriptor ढाँचा parameters */
	s32 desc_params[UCLOGIC_RDESC_PEN_PH_ID_NUM];
	__u8 *desc_ptr = शून्य;

	/* Check arguments */
	अगर (pen == शून्य || pfound == शून्य || hdev == शून्य) अणु
		rc = -EINVAL;
		जाओ cleanup;
	पूर्ण

	/*
	 * Read string descriptor containing pen input parameters.
	 * The specअगरic string descriptor and data were discovered by snअगरfing
	 * the Winकरोws driver traffic.
	 * NOTE: This enables fully-functional tablet mode.
	 */
	rc = uclogic_params_get_str_desc(&buf, hdev, 100, len);
	अगर (rc == -EPIPE) अणु
		hid_dbg(hdev,
			"string descriptor with pen parameters not found, assuming not compatible\n");
		जाओ finish;
	पूर्ण अन्यथा अगर (rc < 0) अणु
		hid_err(hdev, "failed retrieving pen parameters: %d\n", rc);
		जाओ cleanup;
	पूर्ण अन्यथा अगर (rc != len) अणु
		hid_dbg(hdev,
			"string descriptor with pen parameters has invalid length (got %d, expected %d), assuming not compatible\n",
			rc, len);
		जाओ finish;
	पूर्ण

	/*
	 * Fill report descriptor parameters from the string descriptor
	 */
	desc_params[UCLOGIC_RDESC_PEN_PH_ID_X_LM] =
		get_unaligned_le16(buf + 2);
	desc_params[UCLOGIC_RDESC_PEN_PH_ID_Y_LM] =
		get_unaligned_le16(buf + 4);
	desc_params[UCLOGIC_RDESC_PEN_PH_ID_PRESSURE_LM] =
		get_unaligned_le16(buf + 8);
	resolution = get_unaligned_le16(buf + 10);
	अगर (resolution == 0) अणु
		desc_params[UCLOGIC_RDESC_PEN_PH_ID_X_PM] = 0;
		desc_params[UCLOGIC_RDESC_PEN_PH_ID_Y_PM] = 0;
	पूर्ण अन्यथा अणु
		desc_params[UCLOGIC_RDESC_PEN_PH_ID_X_PM] =
			desc_params[UCLOGIC_RDESC_PEN_PH_ID_X_LM] * 1000 /
			resolution;
		desc_params[UCLOGIC_RDESC_PEN_PH_ID_Y_PM] =
			desc_params[UCLOGIC_RDESC_PEN_PH_ID_Y_LM] * 1000 /
			resolution;
	पूर्ण
	kमुक्त(buf);
	buf = शून्य;

	/*
	 * Generate pen report descriptor
	 */
	desc_ptr = uclogic_rdesc_ढाँचा_apply(
				uclogic_rdesc_pen_v1_ढाँचा_arr,
				uclogic_rdesc_pen_v1_ढाँचा_size,
				desc_params, ARRAY_SIZE(desc_params));
	अगर (desc_ptr == शून्य) अणु
		rc = -ENOMEM;
		जाओ cleanup;
	पूर्ण

	/*
	 * Fill-in the parameters
	 */
	स_रखो(pen, 0, माप(*pen));
	pen->desc_ptr = desc_ptr;
	desc_ptr = शून्य;
	pen->desc_size = uclogic_rdesc_pen_v1_ढाँचा_size;
	pen->id = UCLOGIC_RDESC_PEN_V1_ID;
	pen->inrange = UCLOGIC_PARAMS_PEN_INRANGE_INVERTED;
	found = true;
finish:
	*pfound = found;
	rc = 0;
cleanup:
	kमुक्त(desc_ptr);
	kमुक्त(buf);
	वापस rc;
पूर्ण

/**
 * uclogic_params_get_le24() - get a 24-bit little-endian number from a
 * buffer.
 *
 * @p:	The poपूर्णांकer to the number buffer.
 *
 * Returns:
 *	The retrieved number
 */
अटल s32 uclogic_params_get_le24(स्थिर व्योम *p)
अणु
	स्थिर __u8 *b = p;
	वापस b[0] | (b[1] << 8UL) | (b[2] << 16UL);
पूर्ण

/**
 * uclogic_params_pen_init_v2() - initialize tablet पूर्णांकerface pen
 * input and retrieve its parameters from the device, using v2 protocol.
 *
 * @pen:	Poपूर्णांकer to the pen parameters to initialize (to be
 *		cleaned up with uclogic_params_pen_cleanup()). Not modअगरied in
 *		हाल of error, or अगर parameters are not found. Cannot be शून्य.
 * @pfound:	Location क्रम a flag which is set to true अगर the parameters
 *		were found, and to false अगर not (e.g. device was
 *		incompatible). Not modअगरied in हाल of error. Cannot be शून्य.
 * @hdev:	The HID device of the tablet पूर्णांकerface to initialize and get
 *		parameters from. Cannot be शून्य.
 *
 * Returns:
 *	Zero, अगर successful. A negative त्रुटि_सं code on error.
 */
अटल पूर्णांक uclogic_params_pen_init_v2(काष्ठा uclogic_params_pen *pen,
					bool *pfound,
					काष्ठा hid_device *hdev)
अणु
	पूर्णांक rc;
	bool found = false;
	/* Buffer क्रम (part of) the string descriptor */
	__u8 *buf = शून्य;
	/* Descriptor length required */
	स्थिर पूर्णांक len = 18;
	s32 resolution;
	/* Pen report descriptor ढाँचा parameters */
	s32 desc_params[UCLOGIC_RDESC_PEN_PH_ID_NUM];
	__u8 *desc_ptr = शून्य;

	/* Check arguments */
	अगर (pen == शून्य || pfound == शून्य || hdev == शून्य) अणु
		rc = -EINVAL;
		जाओ cleanup;
	पूर्ण

	/*
	 * Read string descriptor containing pen input parameters.
	 * The specअगरic string descriptor and data were discovered by snअगरfing
	 * the Winकरोws driver traffic.
	 * NOTE: This enables fully-functional tablet mode.
	 */
	rc = uclogic_params_get_str_desc(&buf, hdev, 200, len);
	अगर (rc == -EPIPE) अणु
		hid_dbg(hdev,
			"string descriptor with pen parameters not found, assuming not compatible\n");
		जाओ finish;
	पूर्ण अन्यथा अगर (rc < 0) अणु
		hid_err(hdev, "failed retrieving pen parameters: %d\n", rc);
		जाओ cleanup;
	पूर्ण अन्यथा अगर (rc != len) अणु
		hid_dbg(hdev,
			"string descriptor with pen parameters has invalid length (got %d, expected %d), assuming not compatible\n",
			rc, len);
		जाओ finish;
	पूर्ण अन्यथा अणु
		माप_प्रकार i;
		/*
		 * Check it's not just a catch-all UTF-16LE-encoded ASCII
		 * string (such as the model name) some tablets put पूर्णांकo all
		 * unknown string descriptors.
		 */
		क्रम (i = 2;
		     i < len &&
			(buf[i] >= 0x20 && buf[i] < 0x7f && buf[i + 1] == 0);
		     i += 2);
		अगर (i >= len) अणु
			hid_dbg(hdev,
				"string descriptor with pen parameters seems to contain only text, assuming not compatible\n");
			जाओ finish;
		पूर्ण
	पूर्ण

	/*
	 * Fill report descriptor parameters from the string descriptor
	 */
	desc_params[UCLOGIC_RDESC_PEN_PH_ID_X_LM] =
		uclogic_params_get_le24(buf + 2);
	desc_params[UCLOGIC_RDESC_PEN_PH_ID_Y_LM] =
		uclogic_params_get_le24(buf + 5);
	desc_params[UCLOGIC_RDESC_PEN_PH_ID_PRESSURE_LM] =
		get_unaligned_le16(buf + 8);
	resolution = get_unaligned_le16(buf + 10);
	अगर (resolution == 0) अणु
		desc_params[UCLOGIC_RDESC_PEN_PH_ID_X_PM] = 0;
		desc_params[UCLOGIC_RDESC_PEN_PH_ID_Y_PM] = 0;
	पूर्ण अन्यथा अणु
		desc_params[UCLOGIC_RDESC_PEN_PH_ID_X_PM] =
			desc_params[UCLOGIC_RDESC_PEN_PH_ID_X_LM] * 1000 /
			resolution;
		desc_params[UCLOGIC_RDESC_PEN_PH_ID_Y_PM] =
			desc_params[UCLOGIC_RDESC_PEN_PH_ID_Y_LM] * 1000 /
			resolution;
	पूर्ण
	kमुक्त(buf);
	buf = शून्य;

	/*
	 * Generate pen report descriptor
	 */
	desc_ptr = uclogic_rdesc_ढाँचा_apply(
				uclogic_rdesc_pen_v2_ढाँचा_arr,
				uclogic_rdesc_pen_v2_ढाँचा_size,
				desc_params, ARRAY_SIZE(desc_params));
	अगर (desc_ptr == शून्य) अणु
		rc = -ENOMEM;
		जाओ cleanup;
	पूर्ण

	/*
	 * Fill-in the parameters
	 */
	स_रखो(pen, 0, माप(*pen));
	pen->desc_ptr = desc_ptr;
	desc_ptr = शून्य;
	pen->desc_size = uclogic_rdesc_pen_v2_ढाँचा_size;
	pen->id = UCLOGIC_RDESC_PEN_V2_ID;
	pen->inrange = UCLOGIC_PARAMS_PEN_INRANGE_NONE;
	pen->fragmented_hires = true;
	found = true;
finish:
	*pfound = found;
	rc = 0;
cleanup:
	kमुक्त(desc_ptr);
	kमुक्त(buf);
	वापस rc;
पूर्ण

/**
 * uclogic_params_frame_cleanup - मुक्त resources used by काष्ठा
 * uclogic_params_frame (tablet पूर्णांकerface's frame controls input parameters).
 * Can be called repeatedly.
 *
 * @frame:	Frame controls input parameters to cleanup. Cannot be शून्य.
 */
अटल व्योम uclogic_params_frame_cleanup(काष्ठा uclogic_params_frame *frame)
अणु
	kमुक्त(frame->desc_ptr);
	स_रखो(frame, 0, माप(*frame));
पूर्ण

/**
 * uclogic_params_frame_init_with_desc() - initialize tablet's frame control
 * parameters with a अटल report descriptor.
 *
 * @frame:	Poपूर्णांकer to the frame parameters to initialize (to be cleaned
 *		up with uclogic_params_frame_cleanup()). Not modअगरied in हाल
 *		of error. Cannot be शून्य.
 * @desc_ptr:	Report descriptor poपूर्णांकer. Can be शून्य, अगर desc_size is zero.
 * @desc_size:	Report descriptor size.
 * @id:		Report ID used क्रम frame reports, अगर they should be tweaked,
 *		zero अगर not.
 *
 * Returns:
 *	Zero, अगर successful. A negative त्रुटि_सं code on error.
 */
अटल पूर्णांक uclogic_params_frame_init_with_desc(
					काष्ठा uclogic_params_frame *frame,
					स्थिर __u8 *desc_ptr,
					माप_प्रकार desc_size,
					अचिन्हित पूर्णांक id)
अणु
	__u8 *copy_desc_ptr;

	अगर (frame == शून्य || (desc_ptr == शून्य && desc_size != 0))
		वापस -EINVAL;

	copy_desc_ptr = kmemdup(desc_ptr, desc_size, GFP_KERNEL);
	अगर (copy_desc_ptr == शून्य)
		वापस -ENOMEM;

	स_रखो(frame, 0, माप(*frame));
	frame->desc_ptr = copy_desc_ptr;
	frame->desc_size = desc_size;
	frame->id = id;
	वापस 0;
पूर्ण

/**
 * uclogic_params_frame_init_v1_buttonpad() - initialize असलtract buttonpad
 * on a v1 tablet पूर्णांकerface.
 *
 * @frame:	Poपूर्णांकer to the frame parameters to initialize (to be cleaned
 *		up with uclogic_params_frame_cleanup()). Not modअगरied in हाल
 *		of error, or अगर parameters are not found. Cannot be शून्य.
 * @pfound:	Location क्रम a flag which is set to true अगर the parameters
 *		were found, and to false अगर not (e.g. device was
 *		incompatible). Not modअगरied in हाल of error. Cannot be शून्य.
 * @hdev:	The HID device of the tablet पूर्णांकerface to initialize and get
 *		parameters from. Cannot be शून्य.
 *
 * Returns:
 *	Zero, अगर successful. A negative त्रुटि_सं code on error.
 */
अटल पूर्णांक uclogic_params_frame_init_v1_buttonpad(
					काष्ठा uclogic_params_frame *frame,
					bool *pfound,
					काष्ठा hid_device *hdev)
अणु
	पूर्णांक rc;
	bool found = false;
	काष्ठा usb_device *usb_dev = hid_to_usb_dev(hdev);
	अक्षर *str_buf = शून्य;
	स्थिर माप_प्रकार str_len = 16;

	/* Check arguments */
	अगर (frame == शून्य || pfound == शून्य || hdev == शून्य) अणु
		rc = -EINVAL;
		जाओ cleanup;
	पूर्ण

	/*
	 * Enable generic button mode
	 */
	str_buf = kzalloc(str_len, GFP_KERNEL);
	अगर (str_buf == शून्य) अणु
		rc = -ENOMEM;
		जाओ cleanup;
	पूर्ण

	rc = usb_string(usb_dev, 123, str_buf, str_len);
	अगर (rc == -EPIPE) अणु
		hid_dbg(hdev,
			"generic button -enabling string descriptor not found\n");
	पूर्ण अन्यथा अगर (rc < 0) अणु
		जाओ cleanup;
	पूर्ण अन्यथा अगर (म_भेदन(str_buf, "HK On", rc) != 0) अणु
		hid_dbg(hdev,
			"invalid response to enabling generic buttons: \"%s\"\n",
			str_buf);
	पूर्ण अन्यथा अणु
		hid_dbg(hdev, "generic buttons enabled\n");
		rc = uclogic_params_frame_init_with_desc(
				frame,
				uclogic_rdesc_buttonpad_v1_arr,
				uclogic_rdesc_buttonpad_v1_size,
				UCLOGIC_RDESC_BUTTONPAD_V1_ID);
		अगर (rc != 0)
			जाओ cleanup;
		found = true;
	पूर्ण

	*pfound = found;
	rc = 0;
cleanup:
	kमुक्त(str_buf);
	वापस rc;
पूर्ण

/**
 * uclogic_params_cleanup - मुक्त resources used by काष्ठा uclogic_params
 * (tablet पूर्णांकerface's parameters).
 * Can be called repeatedly.
 *
 * @params:	Input parameters to cleanup. Cannot be शून्य.
 */
व्योम uclogic_params_cleanup(काष्ठा uclogic_params *params)
अणु
	अगर (!params->invalid) अणु
		kमुक्त(params->desc_ptr);
		अगर (!params->pen_unused)
			uclogic_params_pen_cleanup(&params->pen);
		uclogic_params_frame_cleanup(&params->frame);
		स_रखो(params, 0, माप(*params));
	पूर्ण
पूर्ण

/**
 * uclogic_params_get_desc() - Get a replacement report descriptor क्रम a
 *                             tablet's पूर्णांकerface.
 *
 * @params:	The parameters of a tablet पूर्णांकerface to get report
 *		descriptor क्रम. Cannot be शून्य.
 * @pdesc:	Location क्रम the resulting, kदो_स्मृति-allocated report
 *		descriptor poपूर्णांकer, or क्रम शून्य, अगर there's no replacement
 *		report descriptor. Not modअगरied in हाल of error. Cannot be
 *		शून्य.
 * @psize:	Location क्रम the resulting report descriptor size, not set अगर
 *		there's no replacement report descriptor. Not modअगरied in हाल
 *		of error. Cannot be शून्य.
 *
 * Returns:
 *	Zero, अगर successful.
 *	-EINVAL, अगर invalid arguments are supplied.
 *	-ENOMEM, अगर failed to allocate memory.
 */
पूर्णांक uclogic_params_get_desc(स्थिर काष्ठा uclogic_params *params,
				__u8 **pdesc,
				अचिन्हित पूर्णांक *psize)
अणु
	bool common_present;
	bool pen_present;
	bool frame_present;
	अचिन्हित पूर्णांक size;
	__u8 *desc = शून्य;

	/* Check arguments */
	अगर (params == शून्य || pdesc == शून्य || psize == शून्य)
		वापस -EINVAL;

	size = 0;

	common_present = (params->desc_ptr != शून्य);
	pen_present = (!params->pen_unused && params->pen.desc_ptr != शून्य);
	frame_present = (params->frame.desc_ptr != शून्य);

	अगर (common_present)
		size += params->desc_size;
	अगर (pen_present)
		size += params->pen.desc_size;
	अगर (frame_present)
		size += params->frame.desc_size;

	अगर (common_present || pen_present || frame_present) अणु
		__u8 *p;

		desc = kदो_स्मृति(size, GFP_KERNEL);
		अगर (desc == शून्य)
			वापस -ENOMEM;
		p = desc;

		अगर (common_present) अणु
			स_नकल(p, params->desc_ptr,
				params->desc_size);
			p += params->desc_size;
		पूर्ण
		अगर (pen_present) अणु
			स_नकल(p, params->pen.desc_ptr,
				params->pen.desc_size);
			p += params->pen.desc_size;
		पूर्ण
		अगर (frame_present) अणु
			स_नकल(p, params->frame.desc_ptr,
				params->frame.desc_size);
			p += params->frame.desc_size;
		पूर्ण

		WARN_ON(p != desc + size);

		*psize = size;
	पूर्ण

	*pdesc = desc;
	वापस 0;
पूर्ण

/**
 * uclogic_params_init_invalid() - initialize tablet पूर्णांकerface parameters,
 * specअगरying the पूर्णांकerface is invalid.
 *
 * @params:		Parameters to initialize (to be cleaned with
 *			uclogic_params_cleanup()). Cannot be शून्य.
 */
अटल व्योम uclogic_params_init_invalid(काष्ठा uclogic_params *params)
अणु
	params->invalid = true;
पूर्ण

/**
 * uclogic_params_init_with_opt_desc() - initialize tablet पूर्णांकerface
 * parameters with an optional replacement report descriptor. Only modअगरy
 * report descriptor, अगर the original report descriptor matches the expected
 * size.
 *
 * @params:		Parameters to initialize (to be cleaned with
 *			uclogic_params_cleanup()). Not modअगरied in हाल of
 *			error. Cannot be शून्य.
 * @hdev:		The HID device of the tablet पूर्णांकerface create the
 *			parameters क्रम. Cannot be शून्य.
 * @orig_desc_size:	Expected size of the original report descriptor to
 *			be replaced.
 * @desc_ptr:		Poपूर्णांकer to the replacement report descriptor.
 *			Can be शून्य, अगर desc_size is zero.
 * @desc_size:		Size of the replacement report descriptor.
 *
 * Returns:
 *	Zero, अगर successful. -EINVAL अगर an invalid argument was passed.
 *	-ENOMEM, अगर failed to allocate memory.
 */
अटल पूर्णांक uclogic_params_init_with_opt_desc(काष्ठा uclogic_params *params,
					     काष्ठा hid_device *hdev,
					     अचिन्हित पूर्णांक orig_desc_size,
					     __u8 *desc_ptr,
					     अचिन्हित पूर्णांक desc_size)
अणु
	__u8 *desc_copy_ptr = शून्य;
	अचिन्हित पूर्णांक desc_copy_size;
	पूर्णांक rc;

	/* Check arguments */
	अगर (params == शून्य || hdev == शून्य ||
	    (desc_ptr == शून्य && desc_size != 0)) अणु
		rc = -EINVAL;
		जाओ cleanup;
	पूर्ण

	/* Replace report descriptor, अगर it matches */
	अगर (hdev->dev_rsize == orig_desc_size) अणु
		hid_dbg(hdev,
			"device report descriptor matches the expected size, replacing\n");
		desc_copy_ptr = kmemdup(desc_ptr, desc_size, GFP_KERNEL);
		अगर (desc_copy_ptr == शून्य) अणु
			rc = -ENOMEM;
			जाओ cleanup;
		पूर्ण
		desc_copy_size = desc_size;
	पूर्ण अन्यथा अणु
		hid_dbg(hdev,
			"device report descriptor doesn't match the expected size (%u != %u), preserving\n",
			hdev->dev_rsize, orig_desc_size);
		desc_copy_ptr = शून्य;
		desc_copy_size = 0;
	पूर्ण

	/* Output parameters */
	स_रखो(params, 0, माप(*params));
	params->desc_ptr = desc_copy_ptr;
	desc_copy_ptr = शून्य;
	params->desc_size = desc_copy_size;

	rc = 0;
cleanup:
	kमुक्त(desc_copy_ptr);
	वापस rc;
पूर्ण

/**
 * uclogic_params_init_with_pen_unused() - initialize tablet पूर्णांकerface
 * parameters preserving original reports and generic HID processing, but
 * disabling pen usage.
 *
 * @params:		Parameters to initialize (to be cleaned with
 *			uclogic_params_cleanup()). Not modअगरied in हाल of
 *			error. Cannot be शून्य.
 */
अटल व्योम uclogic_params_init_with_pen_unused(काष्ठा uclogic_params *params)
अणु
	स_रखो(params, 0, माप(*params));
	params->pen_unused = true;
पूर्ण

/**
 * uclogic_params_huion_init() - initialize a Huion tablet पूर्णांकerface and discover
 * its parameters.
 *
 * @params:	Parameters to fill in (to be cleaned with
 *		uclogic_params_cleanup()). Not modअगरied in हाल of error.
 *		Cannot be शून्य.
 * @hdev:	The HID device of the tablet पूर्णांकerface to initialize and get
 *		parameters from. Cannot be शून्य.
 *
 * Returns:
 *	Zero, अगर successful. A negative त्रुटि_सं code on error.
 */
अटल पूर्णांक uclogic_params_huion_init(काष्ठा uclogic_params *params,
				     काष्ठा hid_device *hdev)
अणु
	पूर्णांक rc;
	काष्ठा usb_device *udev = hid_to_usb_dev(hdev);
	काष्ठा usb_पूर्णांकerface *अगरace = to_usb_पूर्णांकerface(hdev->dev.parent);
	__u8 bInterfaceNumber = अगरace->cur_altsetting->desc.bInterfaceNumber;
	bool found;
	/* The resulting parameters (noop) */
	काष्ठा uclogic_params p = अणु0, पूर्ण;
	अटल स्थिर अक्षर transition_ver[] = "HUION_T153_160607";
	अक्षर *ver_ptr = शून्य;
	स्थिर माप_प्रकार ver_len = माप(transition_ver) + 1;

	/* Check arguments */
	अगर (params == शून्य || hdev == शून्य) अणु
		rc = -EINVAL;
		जाओ cleanup;
	पूर्ण

	/* If it's not a pen पूर्णांकerface */
	अगर (bInterfaceNumber != 0) अणु
		/* TODO: Consider marking the पूर्णांकerface invalid */
		uclogic_params_init_with_pen_unused(&p);
		जाओ output;
	पूर्ण

	/* Try to get firmware version */
	ver_ptr = kzalloc(ver_len, GFP_KERNEL);
	अगर (ver_ptr == शून्य) अणु
		rc = -ENOMEM;
		जाओ cleanup;
	पूर्ण
	rc = usb_string(udev, 201, ver_ptr, ver_len);
	अगर (rc == -EPIPE) अणु
		*ver_ptr = '\0';
	पूर्ण अन्यथा अगर (rc < 0) अणु
		hid_err(hdev,
			"failed retrieving Huion firmware version: %d\n", rc);
		जाओ cleanup;
	पूर्ण

	/* If this is a transition firmware */
	अगर (म_भेद(ver_ptr, transition_ver) == 0) अणु
		hid_dbg(hdev,
			"transition firmware detected, not probing pen v2 parameters\n");
	पूर्ण अन्यथा अणु
		/* Try to probe v2 pen parameters */
		rc = uclogic_params_pen_init_v2(&p.pen, &found, hdev);
		अगर (rc != 0) अणु
			hid_err(hdev,
				"failed probing pen v2 parameters: %d\n", rc);
			जाओ cleanup;
		पूर्ण अन्यथा अगर (found) अणु
			hid_dbg(hdev, "pen v2 parameters found\n");
			/* Create v2 buttonpad parameters */
			rc = uclogic_params_frame_init_with_desc(
					&p.frame,
					uclogic_rdesc_buttonpad_v2_arr,
					uclogic_rdesc_buttonpad_v2_size,
					UCLOGIC_RDESC_BUTTONPAD_V2_ID);
			अगर (rc != 0) अणु
				hid_err(hdev,
					"failed creating v2 buttonpad parameters: %d\n",
					rc);
				जाओ cleanup;
			पूर्ण
			/* Set biपंचांगask marking frame reports in pen reports */
			p.pen_frame_flag = 0x20;
			जाओ output;
		पूर्ण
		hid_dbg(hdev, "pen v2 parameters not found\n");
	पूर्ण

	/* Try to probe v1 pen parameters */
	rc = uclogic_params_pen_init_v1(&p.pen, &found, hdev);
	अगर (rc != 0) अणु
		hid_err(hdev,
			"failed probing pen v1 parameters: %d\n", rc);
		जाओ cleanup;
	पूर्ण अन्यथा अगर (found) अणु
		hid_dbg(hdev, "pen v1 parameters found\n");
		/* Try to probe v1 buttonpad */
		rc = uclogic_params_frame_init_v1_buttonpad(
						&p.frame,
						&found, hdev);
		अगर (rc != 0) अणु
			hid_err(hdev, "v1 buttonpad probing failed: %d\n", rc);
			जाओ cleanup;
		पूर्ण
		hid_dbg(hdev, "buttonpad v1 parameters%s found\n",
			(found ? "" : " not"));
		अगर (found) अणु
			/* Set biपंचांगask marking frame reports */
			p.pen_frame_flag = 0x20;
		पूर्ण
		जाओ output;
	पूर्ण
	hid_dbg(hdev, "pen v1 parameters not found\n");

	uclogic_params_init_invalid(&p);

output:
	/* Output parameters */
	स_नकल(params, &p, माप(*params));
	स_रखो(&p, 0, माप(p));
	rc = 0;
cleanup:
	kमुक्त(ver_ptr);
	uclogic_params_cleanup(&p);
	वापस rc;
पूर्ण

/**
 * uclogic_params_init() - initialize a tablet पूर्णांकerface and discover its
 * parameters.
 *
 * @params:	Parameters to fill in (to be cleaned with
 *		uclogic_params_cleanup()). Not modअगरied in हाल of error.
 *		Cannot be शून्य.
 * @hdev:	The HID device of the tablet पूर्णांकerface to initialize and get
 *		parameters from. Cannot be शून्य. Must be using the USB low-level
 *		driver, i.e. be an actual USB tablet.
 *
 * Returns:
 *	Zero, अगर successful. A negative त्रुटि_सं code on error.
 */
पूर्णांक uclogic_params_init(काष्ठा uclogic_params *params,
			काष्ठा hid_device *hdev)
अणु
	पूर्णांक rc;
	काष्ठा usb_device *udev = hid_to_usb_dev(hdev);
	__u8  bNumInterfaces = udev->config->desc.bNumInterfaces;
	काष्ठा usb_पूर्णांकerface *अगरace = to_usb_पूर्णांकerface(hdev->dev.parent);
	__u8 bInterfaceNumber = अगरace->cur_altsetting->desc.bInterfaceNumber;
	bool found;
	/* The resulting parameters (noop) */
	काष्ठा uclogic_params p = अणु0, पूर्ण;

	/* Check arguments */
	अगर (params == शून्य || hdev == शून्य ||
	    !hid_is_using_ll_driver(hdev, &usb_hid_driver)) अणु
		rc = -EINVAL;
		जाओ cleanup;
	पूर्ण

	/*
	 * Set replacement report descriptor अगर the original matches the
	 * specअगरied size. Otherwise keep पूर्णांकerface unchanged.
	 */
#घोषणा WITH_OPT_DESC(_orig_desc_token, _new_desc_token) \
	uclogic_params_init_with_opt_desc(                  \
		&p, hdev,                                   \
		UCLOGIC_RDESC_##_orig_desc_token##_SIZE,    \
		uclogic_rdesc_##_new_desc_token##_arr,      \
		uclogic_rdesc_##_new_desc_token##_size)

#घोषणा VID_PID(_vid, _pid) \
	(((__u32)(_vid) << 16) | ((__u32)(_pid) & U16_MAX))

	/*
	 * Handle specअगरic पूर्णांकerfaces क्रम specअगरic tablets.
	 *
	 * Observe the following logic:
	 *
	 * If the पूर्णांकerface is recognized as producing certain useful input:
	 *	Mark पूर्णांकerface as valid.
	 *	Output पूर्णांकerface parameters.
	 * Else, अगर the पूर्णांकerface is recognized as *not* producing any useful
	 * input:
	 *	Mark पूर्णांकerface as invalid.
	 * Else:
	 *	Mark पूर्णांकerface as valid.
	 *	Output noop parameters.
	 *
	 * Rule of thumb: it is better to disable a broken पूर्णांकerface than let
	 *		  it spew garbage input.
	 */

	चयन (VID_PID(hdev->venकरोr, hdev->product)) अणु
	हाल VID_PID(USB_VENDOR_ID_UCLOGIC,
		     USB_DEVICE_ID_UCLOGIC_TABLET_PF1209):
		rc = WITH_OPT_DESC(PF1209_ORIG, pf1209_fixed);
		अगर (rc != 0)
			जाओ cleanup;
		अवरोध;
	हाल VID_PID(USB_VENDOR_ID_UCLOGIC,
		     USB_DEVICE_ID_UCLOGIC_TABLET_WP4030U):
		rc = WITH_OPT_DESC(WPXXXXU_ORIG, wp4030u_fixed);
		अगर (rc != 0)
			जाओ cleanup;
		अवरोध;
	हाल VID_PID(USB_VENDOR_ID_UCLOGIC,
		     USB_DEVICE_ID_UCLOGIC_TABLET_WP5540U):
		अगर (hdev->dev_rsize == UCLOGIC_RDESC_WP5540U_V2_ORIG_SIZE) अणु
			अगर (bInterfaceNumber == 0) अणु
				/* Try to probe v1 pen parameters */
				rc = uclogic_params_pen_init_v1(&p.pen,
								&found, hdev);
				अगर (rc != 0) अणु
					hid_err(hdev,
						"pen probing failed: %d\n",
						rc);
					जाओ cleanup;
				पूर्ण
				अगर (!found) अणु
					hid_warn(hdev,
						 "pen parameters not found");
				पूर्ण
			पूर्ण अन्यथा अणु
				uclogic_params_init_invalid(&p);
			पूर्ण
		पूर्ण अन्यथा अणु
			rc = WITH_OPT_DESC(WPXXXXU_ORIG, wp5540u_fixed);
			अगर (rc != 0)
				जाओ cleanup;
		पूर्ण
		अवरोध;
	हाल VID_PID(USB_VENDOR_ID_UCLOGIC,
		     USB_DEVICE_ID_UCLOGIC_TABLET_WP8060U):
		rc = WITH_OPT_DESC(WPXXXXU_ORIG, wp8060u_fixed);
		अगर (rc != 0)
			जाओ cleanup;
		अवरोध;
	हाल VID_PID(USB_VENDOR_ID_UCLOGIC,
		     USB_DEVICE_ID_UCLOGIC_TABLET_WP1062):
		rc = WITH_OPT_DESC(WP1062_ORIG, wp1062_fixed);
		अगर (rc != 0)
			जाओ cleanup;
		अवरोध;
	हाल VID_PID(USB_VENDOR_ID_UCLOGIC,
		     USB_DEVICE_ID_UCLOGIC_WIRELESS_TABLET_TWHL850):
		चयन (bInterfaceNumber) अणु
		हाल 0:
			rc = WITH_OPT_DESC(TWHL850_ORIG0, twhl850_fixed0);
			अगर (rc != 0)
				जाओ cleanup;
			अवरोध;
		हाल 1:
			rc = WITH_OPT_DESC(TWHL850_ORIG1, twhl850_fixed1);
			अगर (rc != 0)
				जाओ cleanup;
			अवरोध;
		हाल 2:
			rc = WITH_OPT_DESC(TWHL850_ORIG2, twhl850_fixed2);
			अगर (rc != 0)
				जाओ cleanup;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल VID_PID(USB_VENDOR_ID_UCLOGIC,
		     USB_DEVICE_ID_UCLOGIC_TABLET_TWHA60):
		/*
		 * If it is not a three-पूर्णांकerface version, which is known to
		 * respond to initialization.
		 */
		अगर (bNumInterfaces != 3) अणु
			चयन (bInterfaceNumber) अणु
			हाल 0:
				rc = WITH_OPT_DESC(TWHA60_ORIG0,
							twha60_fixed0);
				अगर (rc != 0)
					जाओ cleanup;
				अवरोध;
			हाल 1:
				rc = WITH_OPT_DESC(TWHA60_ORIG1,
							twha60_fixed1);
				अगर (rc != 0)
					जाओ cleanup;
				अवरोध;
			पूर्ण
			अवरोध;
		पूर्ण
		fallthrough;
	हाल VID_PID(USB_VENDOR_ID_HUION,
		     USB_DEVICE_ID_HUION_TABLET):
	हाल VID_PID(USB_VENDOR_ID_HUION,
		     USB_DEVICE_ID_HUION_HS64):
	हाल VID_PID(USB_VENDOR_ID_UCLOGIC,
		     USB_DEVICE_ID_HUION_TABLET):
	हाल VID_PID(USB_VENDOR_ID_UCLOGIC,
		     USB_DEVICE_ID_YIYNOVA_TABLET):
	हाल VID_PID(USB_VENDOR_ID_UCLOGIC,
		     USB_DEVICE_ID_UCLOGIC_UGEE_TABLET_81):
	हाल VID_PID(USB_VENDOR_ID_UCLOGIC,
		     USB_DEVICE_ID_UCLOGIC_DRAWIMAGE_G3):
	हाल VID_PID(USB_VENDOR_ID_UCLOGIC,
		     USB_DEVICE_ID_UCLOGIC_UGEE_TABLET_45):
	हाल VID_PID(USB_VENDOR_ID_UCLOGIC,
		     USB_DEVICE_ID_UCLOGIC_UGEE_TABLET_47):
		rc = uclogic_params_huion_init(&p, hdev);
		अगर (rc != 0)
			जाओ cleanup;
		अवरोध;
	हाल VID_PID(USB_VENDOR_ID_UGTIZER,
		     USB_DEVICE_ID_UGTIZER_TABLET_GP0610):
	हाल VID_PID(USB_VENDOR_ID_UGTIZER,
		     USB_DEVICE_ID_UGTIZER_TABLET_GT5040):
	हाल VID_PID(USB_VENDOR_ID_UGEE,
		     USB_DEVICE_ID_UGEE_XPPEN_TABLET_G540):
	हाल VID_PID(USB_VENDOR_ID_UGEE,
		     USB_DEVICE_ID_UGEE_XPPEN_TABLET_G640):
	हाल VID_PID(USB_VENDOR_ID_UGEE,
		     USB_DEVICE_ID_UGEE_TABLET_RAINBOW_CV720):
		/* If this is the pen पूर्णांकerface */
		अगर (bInterfaceNumber == 1) अणु
			/* Probe v1 pen parameters */
			rc = uclogic_params_pen_init_v1(&p.pen, &found, hdev);
			अगर (rc != 0) अणु
				hid_err(hdev, "pen probing failed: %d\n", rc);
				जाओ cleanup;
			पूर्ण
			अगर (!found) अणु
				hid_warn(hdev, "pen parameters not found");
				uclogic_params_init_invalid(&p);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* TODO: Consider marking the पूर्णांकerface invalid */
			uclogic_params_init_with_pen_unused(&p);
		पूर्ण
		अवरोध;
	हाल VID_PID(USB_VENDOR_ID_UGEE,
		     USB_DEVICE_ID_UGEE_XPPEN_TABLET_DECO01):
		/* If this is the pen and frame पूर्णांकerface */
		अगर (bInterfaceNumber == 1) अणु
			/* Probe v1 pen parameters */
			rc = uclogic_params_pen_init_v1(&p.pen, &found, hdev);
			अगर (rc != 0) अणु
				hid_err(hdev, "pen probing failed: %d\n", rc);
				जाओ cleanup;
			पूर्ण
			/* Initialize frame parameters */
			rc = uclogic_params_frame_init_with_desc(
				&p.frame,
				uclogic_rdesc_xppen_deco01_frame_arr,
				uclogic_rdesc_xppen_deco01_frame_size,
				0);
			अगर (rc != 0)
				जाओ cleanup;
		पूर्ण अन्यथा अणु
			/* TODO: Consider marking the पूर्णांकerface invalid */
			uclogic_params_init_with_pen_unused(&p);
		पूर्ण
		अवरोध;
	हाल VID_PID(USB_VENDOR_ID_TRUST,
		     USB_DEVICE_ID_TRUST_PANORA_TABLET):
	हाल VID_PID(USB_VENDOR_ID_UGEE,
		     USB_DEVICE_ID_UGEE_TABLET_G5):
		/* Ignore non-pen पूर्णांकerfaces */
		अगर (bInterfaceNumber != 1) अणु
			uclogic_params_init_invalid(&p);
			अवरोध;
		पूर्ण

		rc = uclogic_params_pen_init_v1(&p.pen, &found, hdev);
		अगर (rc != 0) अणु
			hid_err(hdev, "pen probing failed: %d\n", rc);
			जाओ cleanup;
		पूर्ण अन्यथा अगर (found) अणु
			rc = uclogic_params_frame_init_with_desc(
				&p.frame,
				uclogic_rdesc_ugee_g5_frame_arr,
				uclogic_rdesc_ugee_g5_frame_size,
				UCLOGIC_RDESC_UGEE_G5_FRAME_ID);
			अगर (rc != 0) अणु
				hid_err(hdev,
					"failed creating buttonpad parameters: %d\n",
					rc);
				जाओ cleanup;
			पूर्ण
			p.frame.re_lsb =
				UCLOGIC_RDESC_UGEE_G5_FRAME_RE_LSB;
			p.frame.dev_id_byte =
				UCLOGIC_RDESC_UGEE_G5_FRAME_DEV_ID_BYTE;
		पूर्ण अन्यथा अणु
			hid_warn(hdev, "pen parameters not found");
			uclogic_params_init_invalid(&p);
		पूर्ण

		अवरोध;
	हाल VID_PID(USB_VENDOR_ID_UGEE,
		     USB_DEVICE_ID_UGEE_TABLET_EX07S):
		/* Ignore non-pen पूर्णांकerfaces */
		अगर (bInterfaceNumber != 1) अणु
			uclogic_params_init_invalid(&p);
			अवरोध;
		पूर्ण

		rc = uclogic_params_pen_init_v1(&p.pen, &found, hdev);
		अगर (rc != 0) अणु
			hid_err(hdev, "pen probing failed: %d\n", rc);
			जाओ cleanup;
		पूर्ण अन्यथा अगर (found) अणु
			rc = uclogic_params_frame_init_with_desc(
				&p.frame,
				uclogic_rdesc_ugee_ex07_buttonpad_arr,
				uclogic_rdesc_ugee_ex07_buttonpad_size,
				0);
			अगर (rc != 0) अणु
				hid_err(hdev,
					"failed creating buttonpad parameters: %d\n",
					rc);
				जाओ cleanup;
			पूर्ण
		पूर्ण अन्यथा अणु
			hid_warn(hdev, "pen parameters not found");
			uclogic_params_init_invalid(&p);
		पूर्ण

		अवरोध;
	पूर्ण

#अघोषित VID_PID
#अघोषित WITH_OPT_DESC

	/* Output parameters */
	स_नकल(params, &p, माप(*params));
	स_रखो(&p, 0, माप(p));
	rc = 0;
cleanup:
	uclogic_params_cleanup(&p);
	वापस rc;
पूर्ण
