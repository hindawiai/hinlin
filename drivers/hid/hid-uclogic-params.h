<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
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

#अगर_अघोषित _HID_UCLOGIC_PARAMS_H
#घोषणा _HID_UCLOGIC_PARAMS_H

#समावेश <linux/usb.h>
#समावेश <linux/hid.h>

/* Types of pen in-range reporting */
क्रमागत uclogic_params_pen_inrange अणु
	/* Normal reports: zero - out of proximity, one - in proximity */
	UCLOGIC_PARAMS_PEN_INRANGE_NORMAL = 0,
	/* Inverted reports: zero - in proximity, one - out of proximity */
	UCLOGIC_PARAMS_PEN_INRANGE_INVERTED,
	/* No reports */
	UCLOGIC_PARAMS_PEN_INRANGE_NONE,
पूर्ण;

/* Convert a pen in-range reporting type to a string */
बाह्य स्थिर अक्षर *uclogic_params_pen_inrange_to_str(
			क्रमागत uclogic_params_pen_inrange inrange);

/*
 * Tablet पूर्णांकerface's pen input parameters.
 *
 * Must use declarative (descriptive) language, not imperative, to simplअगरy
 * understanding and मुख्यtain consistency.
 *
 * Noop (preserving functionality) when filled with zeroes.
 */
काष्ठा uclogic_params_pen अणु
	/*
	 * Poपूर्णांकer to report descriptor describing the inमाला_दो.
	 * Allocated with kदो_स्मृति.
	 */
	__u8 *desc_ptr;
	/*
	 * Size of the report descriptor.
	 * Only valid, अगर "desc_ptr" is not शून्य.
	 */
	अचिन्हित पूर्णांक desc_size;
	/* Report ID, अगर reports should be tweaked, zero अगर not */
	अचिन्हित पूर्णांक id;
	/* Type of in-range reporting, only valid अगर "id" is not zero */
	क्रमागत uclogic_params_pen_inrange inrange;
	/*
	 * True, अगर reports include fragmented high resolution coords, with
	 * high-order X and then Y bytes following the pressure field.
	 * Only valid अगर "id" is not zero.
	 */
	bool fragmented_hires;
पूर्ण;

/*
 * Parameters of frame control inमाला_दो of a tablet पूर्णांकerface.
 *
 * Must use declarative (descriptive) language, not imperative, to simplअगरy
 * understanding and मुख्यtain consistency.
 *
 * Noop (preserving functionality) when filled with zeroes.
 */
काष्ठा uclogic_params_frame अणु
	/*
	 * Poपूर्णांकer to report descriptor describing the inमाला_दो.
	 * Allocated with kदो_स्मृति.
	 */
	__u8 *desc_ptr;
	/*
	 * Size of the report descriptor.
	 * Only valid, अगर "desc_ptr" is not शून्य.
	 */
	अचिन्हित पूर्णांक desc_size;
	/*
	 * Report ID, अगर reports should be tweaked, zero अगर not.
	 */
	अचिन्हित पूर्णांक id;
	/*
	 * Number of the least-signअगरicant bit of the 2-bit state of a rotary
	 * encoder, in the report. Cannot poपूर्णांक to a 2-bit field crossing a
	 * byte boundary. Zero अगर not present. Only valid अगर "id" is not zero.
	 */
	अचिन्हित पूर्णांक re_lsb;
	/*
	 * Offset of the Wacom-style device ID byte in the report, to be set
	 * to pad device ID (0xf), क्रम compatibility with Wacom drivers. Zero
	 * अगर no changes to the report should be made. Only valid अगर "id" is
	 * not zero.
	 */
	अचिन्हित पूर्णांक dev_id_byte;
पूर्ण;

/*
 * Tablet पूर्णांकerface report parameters.
 *
 * Must use declarative (descriptive) language, not imperative, to simplअगरy
 * understanding and मुख्यtain consistency.
 *
 * When filled with zeros represents a "noop" configuration - passes all
 * reports unchanged and lets the generic HID driver handle everything.
 *
 * The resulting device report descriptor is assembled from all the report
 * descriptor parts referenced by the काष्ठाure. No order of assembly should
 * be assumed. The काष्ठाure represents original device report descriptor अगर
 * all the parts are शून्य.
 */
काष्ठा uclogic_params अणु
	/*
	 * True अगर the whole पूर्णांकerface is invalid, false otherwise.
	 */
	bool invalid;
	/*
	 * Poपूर्णांकer to the common part of the replacement report descriptor,
	 * allocated with kदो_स्मृति. शून्य अगर no common part is needed.
	 * Only valid, अगर "invalid" is false.
	 */
	__u8 *desc_ptr;
	/*
	 * Size of the common part of the replacement report descriptor.
	 * Only valid, अगर "desc_ptr" is not शून्य.
	 */
	अचिन्हित पूर्णांक desc_size;
	/*
	 * True, अगर pen usage in report descriptor is invalid, when present.
	 * Only valid, अगर "invalid" is false.
	 */
	bool pen_unused;
	/*
	 * Pen parameters and optional report descriptor part.
	 * Only valid अगर "pen_unused" is valid and false.
	 */
	काष्ठा uclogic_params_pen pen;
	/*
	 * Frame control parameters and optional report descriptor part.
	 * Only valid, अगर "invalid" is false.
	 */
	काष्ठा uclogic_params_frame frame;
	/*
	 * Biपंचांगask matching frame controls "sub-report" flag in the second
	 * byte of the pen report, or zero अगर it's not expected.
	 * Only valid अगर both "pen" and "frame" are valid, and "frame.id" is
	 * not zero.
	 */
	__u8 pen_frame_flag;
पूर्ण;

/* Initialize a tablet पूर्णांकerface and discover its parameters */
बाह्य पूर्णांक uclogic_params_init(काष्ठा uclogic_params *params,
				काष्ठा hid_device *hdev);

/* Tablet पूर्णांकerface parameters *म_लिखो क्रमmat string */
#घोषणा UCLOGIC_PARAMS_FMT_STR \
		".invalid = %s\n"                   \
		".desc_ptr = %p\n"                  \
		".desc_size = %u\n"                 \
		".pen_unused = %s\n"                \
		".pen.desc_ptr = %p\n"              \
		".pen.desc_size = %u\n"             \
		".pen.id = %u\n"                    \
		".pen.inrange = %s\n"               \
		".pen.fragmented_hires = %s\n"      \
		".frame.desc_ptr = %p\n"            \
		".frame.desc_size = %u\n"           \
		".frame.id = %u\n"                  \
		".frame.re_lsb = %u\n"              \
		".frame.dev_id_byte = %u\n"         \
		".pen_frame_flag = 0x%02x\n"

/* Tablet पूर्णांकerface parameters *म_लिखो क्रमmat arguments */
#घोषणा UCLOGIC_PARAMS_FMT_ARGS(_params) \
		((_params)->invalid ? "true" : "false"),                    \
		(_params)->desc_ptr,                                        \
		(_params)->desc_size,                                       \
		((_params)->pen_unused ? "true" : "false"),                 \
		(_params)->pen.desc_ptr,                                    \
		(_params)->pen.desc_size,                                   \
		(_params)->pen.id,                                          \
		uclogic_params_pen_inrange_to_str((_params)->pen.inrange),  \
		((_params)->pen.fragmented_hires ? "true" : "false"),       \
		(_params)->frame.desc_ptr,                                  \
		(_params)->frame.desc_size,                                 \
		(_params)->frame.id,                                        \
		(_params)->frame.re_lsb,                                    \
		(_params)->frame.dev_id_byte,                               \
		(_params)->pen_frame_flag

/* Get a replacement report descriptor क्रम a tablet's पूर्णांकerface. */
बाह्य पूर्णांक uclogic_params_get_desc(स्थिर काष्ठा uclogic_params *params,
					__u8 **pdesc,
					अचिन्हित पूर्णांक *psize);

/* Free resources used by tablet पूर्णांकerface's parameters */
बाह्य व्योम uclogic_params_cleanup(काष्ठा uclogic_params *params);

#पूर्ण_अगर /* _HID_UCLOGIC_PARAMS_H */
