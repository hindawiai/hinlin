<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * vpd_decode.c
 *
 * Google VPD decoding routines.
 *
 * Copyright 2017 Google Inc.
 */

#समावेश "vpd_decode.h"

अटल पूर्णांक vpd_decode_len(स्थिर u32 max_len, स्थिर u8 *in,
			  u32 *length, u32 *decoded_len)
अणु
	u8 more;
	पूर्णांक i = 0;

	अगर (!length || !decoded_len)
		वापस VPD_FAIL;

	*length = 0;
	करो अणु
		अगर (i >= max_len)
			वापस VPD_FAIL;

		more = in[i] & 0x80;
		*length <<= 7;
		*length |= in[i] & 0x7f;
		++i;
	पूर्ण जबतक (more);

	*decoded_len = i;
	वापस VPD_OK;
पूर्ण

अटल पूर्णांक vpd_decode_entry(स्थिर u32 max_len, स्थिर u8 *input_buf,
			    u32 *_consumed, स्थिर u8 **entry, u32 *entry_len)
अणु
	u32 decoded_len;
	u32 consumed = *_consumed;

	अगर (vpd_decode_len(max_len - consumed, &input_buf[consumed],
			   entry_len, &decoded_len) != VPD_OK)
		वापस VPD_FAIL;
	अगर (max_len - consumed < decoded_len)
		वापस VPD_FAIL;

	consumed += decoded_len;
	*entry = input_buf + consumed;

	/* entry_len is untrusted data and must be checked again. */
	अगर (max_len - consumed < *entry_len)
		वापस VPD_FAIL;

	consumed += *entry_len;
	*_consumed = consumed;
	वापस VPD_OK;
पूर्ण

पूर्णांक vpd_decode_string(स्थिर u32 max_len, स्थिर u8 *input_buf, u32 *consumed,
		      vpd_decode_callback callback, व्योम *callback_arg)
अणु
	पूर्णांक type;
	u32 key_len;
	u32 value_len;
	स्थिर u8 *key;
	स्थिर u8 *value;

	/* type */
	अगर (*consumed >= max_len)
		वापस VPD_FAIL;

	type = input_buf[*consumed];

	चयन (type) अणु
	हाल VPD_TYPE_INFO:
	हाल VPD_TYPE_STRING:
		(*consumed)++;

		अगर (vpd_decode_entry(max_len, input_buf, consumed, &key,
				     &key_len) != VPD_OK)
			वापस VPD_FAIL;

		अगर (vpd_decode_entry(max_len, input_buf, consumed, &value,
				     &value_len) != VPD_OK)
			वापस VPD_FAIL;

		अगर (type == VPD_TYPE_STRING)
			वापस callback(key, key_len, value, value_len,
					callback_arg);
		अवरोध;

	शेष:
		वापस VPD_FAIL;
	पूर्ण

	वापस VPD_OK;
पूर्ण
