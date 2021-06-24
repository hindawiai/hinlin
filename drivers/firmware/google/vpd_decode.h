<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * vpd_decode.h
 *
 * Google VPD decoding routines.
 *
 * Copyright 2017 Google Inc.
 */

#अगर_अघोषित __VPD_DECODE_H
#घोषणा __VPD_DECODE_H

#समावेश <linux/types.h>

क्रमागत अणु
	VPD_OK = 0,
	VPD_FAIL,
पूर्ण;

क्रमागत अणु
	VPD_TYPE_TERMINATOR = 0,
	VPD_TYPE_STRING,
	VPD_TYPE_INFO                = 0xfe,
	VPD_TYPE_IMPLICIT_TERMINATOR = 0xff,
पूर्ण;

/* Callback क्रम vpd_decode_string to invoke. */
प्रकार पूर्णांक vpd_decode_callback(स्थिर u8 *key, u32 key_len,
				स्थिर u8 *value, u32 value_len,
				व्योम *arg);

/*
 * vpd_decode_string
 *
 * Given the encoded string, this function invokes callback with extracted
 * (key, value). The *consumed will be plused the number of bytes consumed in
 * this function.
 *
 * The input_buf poपूर्णांकs to the first byte of the input buffer.
 *
 * The *consumed starts from 0, which is actually the next byte to be decoded.
 * It can be non-zero to be used in multiple calls.
 *
 * If one entry is successfully decoded, sends it to callback and वापसs the
 * result.
 */
पूर्णांक vpd_decode_string(स्थिर u32 max_len, स्थिर u8 *input_buf, u32 *consumed,
		      vpd_decode_callback callback, व्योम *callback_arg);

#पूर्ण_अगर  /* __VPD_DECODE_H */
