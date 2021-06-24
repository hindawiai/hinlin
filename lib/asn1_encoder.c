<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Simple encoder primitives क्रम ASN.1 BER/DER/CER
 *
 * Copyright (C) 2019 James.Bottomley@HansenPartnership.com
 */

#समावेश <linux/asn1_encoder.h>
#समावेश <linux/bug.h>
#समावेश <linux/माला.स>
#समावेश <linux/module.h>

/**
 * asn1_encode_पूर्णांकeger() - encode positive पूर्णांकeger to ASN.1
 * @data:	poपूर्णांकer to the poपूर्णांकer to the data
 * @end_data:	end of data poपूर्णांकer, poपूर्णांकs one beyond last usable byte in @data
 * @पूर्णांकeger:	पूर्णांकeger to be encoded
 *
 * This is a simplअगरied encoder: it only currently करोes
 * positive पूर्णांकegers, but it should be simple enough to add the
 * negative हाल अगर a use comes aदीर्घ.
 */
अचिन्हित अक्षर *
asn1_encode_पूर्णांकeger(अचिन्हित अक्षर *data, स्थिर अचिन्हित अक्षर *end_data,
		    s64 पूर्णांकeger)
अणु
	पूर्णांक data_len = end_data - data;
	अचिन्हित अक्षर *d = &data[2];
	bool found = false;
	पूर्णांक i;

	अगर (WARN(पूर्णांकeger < 0,
		 "BUG: integer encode only supports positive integers"))
		वापस ERR_PTR(-EINVAL);

	अगर (IS_ERR(data))
		वापस data;

	/* need at least 3 bytes क्रम tag, length and पूर्णांकeger encoding */
	अगर (data_len < 3)
		वापस ERR_PTR(-EINVAL);

	/* reमुख्यing length where at d (the start of the पूर्णांकeger encoding) */
	data_len -= 2;

	data[0] = _tag(UNIV, PRIM, INT);
	अगर (पूर्णांकeger == 0) अणु
		*d++ = 0;
		जाओ out;
	पूर्ण

	क्रम (i = माप(पूर्णांकeger); i > 0 ; i--) अणु
		पूर्णांक byte = पूर्णांकeger >> (8 * (i - 1));

		अगर (!found && byte == 0)
			जारी;

		/*
		 * क्रम a positive number the first byte must have bit
		 * 7 clear in two's complement (otherwise it's a
		 * negative number) so prepend a leading zero अगर
		 * that's not the हाल
		 */
		अगर (!found && (byte & 0x80)) अणु
			/*
			 * no check needed here, we alपढ़ोy know we
			 * have len >= 1
			 */
			*d++ = 0;
			data_len--;
		पूर्ण

		found = true;
		अगर (data_len == 0)
			वापस ERR_PTR(-EINVAL);

		*d++ = byte;
		data_len--;
	पूर्ण

 out:
	data[1] = d - data - 2;

	वापस d;
पूर्ण
EXPORT_SYMBOL_GPL(asn1_encode_पूर्णांकeger);

/* calculate the base 128 digit values setting the top bit of the first octet */
अटल पूर्णांक asn1_encode_oid_digit(अचिन्हित अक्षर **_data, पूर्णांक *data_len, u32 oid)
अणु
	अचिन्हित अक्षर *data = *_data;
	पूर्णांक start = 7 + 7 + 7 + 7;
	पूर्णांक ret = 0;

	अगर (*data_len < 1)
		वापस -EINVAL;

	/* quick हाल */
	अगर (oid == 0) अणु
		*data++ = 0x80;
		(*data_len)--;
		जाओ out;
	पूर्ण

	जबतक (oid >> start == 0)
		start -= 7;

	जबतक (start > 0 && *data_len > 0) अणु
		u8 byte;

		byte = oid >> start;
		oid = oid - (byte << start);
		start -= 7;
		byte |= 0x80;
		*data++ = byte;
		(*data_len)--;
	पूर्ण

	अगर (*data_len > 0) अणु
		*data++ = oid;
		(*data_len)--;
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
	पूर्ण

 out:
	*_data = data;
	वापस ret;
पूर्ण

/**
 * asn1_encode_oid() - encode an oid to ASN.1
 * @data:	position to begin encoding at
 * @end_data:	end of data poपूर्णांकer, poपूर्णांकs one beyond last usable byte in @data
 * @oid:	array of oids
 * @oid_len:	length of oid array
 *
 * this encodes an OID up to ASN.1 when presented as an array of OID values
 */
अचिन्हित अक्षर *
asn1_encode_oid(अचिन्हित अक्षर *data, स्थिर अचिन्हित अक्षर *end_data,
		u32 oid[], पूर्णांक oid_len)
अणु
	पूर्णांक data_len = end_data - data;
	अचिन्हित अक्षर *d = data + 2;
	पूर्णांक i, ret;

	अगर (WARN(oid_len < 2, "OID must have at least two elements"))
		वापस ERR_PTR(-EINVAL);

	अगर (WARN(oid_len > 32, "OID is too large"))
		वापस ERR_PTR(-EINVAL);

	अगर (IS_ERR(data))
		वापस data;


	/* need at least 3 bytes क्रम tag, length and OID encoding */
	अगर (data_len < 3)
		वापस ERR_PTR(-EINVAL);

	data[0] = _tag(UNIV, PRIM, OID);
	*d++ = oid[0] * 40 + oid[1];

	data_len -= 3;

	ret = 0;

	क्रम (i = 2; i < oid_len; i++) अणु
		ret = asn1_encode_oid_digit(&d, &data_len, oid[i]);
		अगर (ret < 0)
			वापस ERR_PTR(ret);
	पूर्ण

	data[1] = d - data - 2;

	वापस d;
पूर्ण
EXPORT_SYMBOL_GPL(asn1_encode_oid);

/**
 * asn1_encode_length() - encode a length to follow an ASN.1 tag
 * @data: poपूर्णांकer to encode at
 * @data_len: poपूर्णांकer to remaning length (adjusted by routine)
 * @len: length to encode
 *
 * This routine can encode lengths up to 65535 using the ASN.1 rules.
 * It will accept a negative length and place a zero length tag
 * instead (to keep the ASN.1 valid).  This convention allows other
 * encoder primitives to accept negative lengths as singalling the
 * sequence will be re-encoded when the length is known.
 */
अटल पूर्णांक asn1_encode_length(अचिन्हित अक्षर **data, पूर्णांक *data_len, पूर्णांक len)
अणु
	अगर (*data_len < 1)
		वापस -EINVAL;

	अगर (len < 0) अणु
		*((*data)++) = 0;
		(*data_len)--;
		वापस 0;
	पूर्ण

	अगर (len <= 0x7f) अणु
		*((*data)++) = len;
		(*data_len)--;
		वापस 0;
	पूर्ण

	अगर (*data_len < 2)
		वापस -EINVAL;

	अगर (len <= 0xff) अणु
		*((*data)++) = 0x81;
		*((*data)++) = len & 0xff;
		*data_len -= 2;
		वापस 0;
	पूर्ण

	अगर (*data_len < 3)
		वापस -EINVAL;

	अगर (len <= 0xffff) अणु
		*((*data)++) = 0x82;
		*((*data)++) = (len >> 8) & 0xff;
		*((*data)++) = len & 0xff;
		*data_len -= 3;
		वापस 0;
	पूर्ण

	अगर (WARN(len > 0xffffff, "ASN.1 length can't be > 0xffffff"))
		वापस -EINVAL;

	अगर (*data_len < 4)
		वापस -EINVAL;
	*((*data)++) = 0x83;
	*((*data)++) = (len >> 16) & 0xff;
	*((*data)++) = (len >> 8) & 0xff;
	*((*data)++) = len & 0xff;
	*data_len -= 4;

	वापस 0;
पूर्ण

/**
 * asn1_encode_tag() - add a tag क्रम optional or explicit value
 * @data:	poपूर्णांकer to place tag at
 * @end_data:	end of data poपूर्णांकer, poपूर्णांकs one beyond last usable byte in @data
 * @tag:	tag to be placed
 * @string:	the data to be tagged
 * @len:	the length of the data to be tagged
 *
 * Note this currently only handles लघु क्रमm tags < 31.
 *
 * Standard usage is to pass in a @tag, @string and @length and the
 * @string will be ASN.1 encoded with @tag and placed पूर्णांकo @data.  If
 * the encoding would put data past @end_data then an error is
 * वापसed, otherwise a poपूर्णांकer to a position one beyond the encoding
 * is वापसed.
 *
 * To encode in place pass a शून्य @string and -1 क्रम @len and the
 * maximum allowable beginning and end of the data; all this will करो
 * is add the current maximum length and update the data poपूर्णांकer to
 * the place where the tag contents should be placed is वापसed.  The
 * data should be copied in by the calling routine which should then
 * repeat the prior statement but now with the known length.  In order
 * to aव्योम having to keep both beक्रमe and after poपूर्णांकers, the repeat
 * expects to be called with @data poपूर्णांकing to where the first encode
 * वापसed it and still शून्य क्रम @string but the real length in @len.
 */
अचिन्हित अक्षर *
asn1_encode_tag(अचिन्हित अक्षर *data, स्थिर अचिन्हित अक्षर *end_data,
		u32 tag, स्थिर अचिन्हित अक्षर *string, पूर्णांक len)
अणु
	पूर्णांक data_len = end_data - data;
	पूर्णांक ret;

	अगर (WARN(tag > 30, "ASN.1 tag can't be > 30"))
		वापस ERR_PTR(-EINVAL);

	अगर (!string && WARN(len > 127,
			    "BUG: recode tag is too big (>127)"))
		वापस ERR_PTR(-EINVAL);

	अगर (IS_ERR(data))
		वापस data;

	अगर (!string && len > 0) अणु
		/*
		 * we're recoding, so move back to the start of the
		 * tag and install a dummy length because the real
		 * data_len should be शून्य
		 */
		data -= 2;
		data_len = 2;
	पूर्ण

	अगर (data_len < 2)
		वापस ERR_PTR(-EINVAL);

	*(data++) = _tagn(CONT, CONS, tag);
	data_len--;
	ret = asn1_encode_length(&data, &data_len, len);
	अगर (ret < 0)
		वापस ERR_PTR(ret);

	अगर (!string)
		वापस data;

	अगर (data_len < len)
		वापस ERR_PTR(-EINVAL);

	स_नकल(data, string, len);
	data += len;

	वापस data;
पूर्ण
EXPORT_SYMBOL_GPL(asn1_encode_tag);

/**
 * asn1_encode_octet_string() - encode an ASN.1 OCTET STRING
 * @data:	poपूर्णांकer to encode at
 * @end_data:	end of data poपूर्णांकer, poपूर्णांकs one beyond last usable byte in @data
 * @string:	string to be encoded
 * @len:	length of string
 *
 * Note ASN.1 octet strings may contain zeros, so the length is obligatory.
 */
अचिन्हित अक्षर *
asn1_encode_octet_string(अचिन्हित अक्षर *data,
			 स्थिर अचिन्हित अक्षर *end_data,
			 स्थिर अचिन्हित अक्षर *string, u32 len)
अणु
	पूर्णांक data_len = end_data - data;
	पूर्णांक ret;

	अगर (IS_ERR(data))
		वापस data;

	/* need minimum of 2 bytes क्रम tag and length of zero length string */
	अगर (data_len < 2)
		वापस ERR_PTR(-EINVAL);

	*(data++) = _tag(UNIV, PRIM, OTS);
	data_len--;

	ret = asn1_encode_length(&data, &data_len, len);
	अगर (ret)
		वापस ERR_PTR(ret);

	अगर (data_len < len)
		वापस ERR_PTR(-EINVAL);

	स_नकल(data, string, len);
	data += len;

	वापस data;
पूर्ण
EXPORT_SYMBOL_GPL(asn1_encode_octet_string);

/**
 * asn1_encode_sequence() - wrap a byte stream in an ASN.1 SEQUENCE
 * @data:	poपूर्णांकer to encode at
 * @end_data:	end of data poपूर्णांकer, poपूर्णांकs one beyond last usable byte in @data
 * @seq:	data to be encoded as a sequence
 * @len:	length of the data to be encoded as a sequence
 *
 * Fill in a sequence.  To encode in place, pass शून्य क्रम @seq and -1
 * क्रम @len; then call again once the length is known (still with शून्य
 * क्रम @seq). In order to aव्योम having to keep both beक्रमe and after
 * poपूर्णांकers, the repeat expects to be called with @data poपूर्णांकing to
 * where the first encode placed it.
 */
अचिन्हित अक्षर *
asn1_encode_sequence(अचिन्हित अक्षर *data, स्थिर अचिन्हित अक्षर *end_data,
		     स्थिर अचिन्हित अक्षर *seq, पूर्णांक len)
अणु
	पूर्णांक data_len = end_data - data;
	पूर्णांक ret;

	अगर (!seq && WARN(len > 127,
			 "BUG: recode sequence is too big (>127)"))
		वापस ERR_PTR(-EINVAL);

	अगर (IS_ERR(data))
		वापस data;

	अगर (!seq && len >= 0) अणु
		/*
		 * we're recoding, so move back to the start of the
		 * sequence and install a dummy length because the
		 * real length should be शून्य
		 */
		data -= 2;
		data_len = 2;
	पूर्ण

	अगर (data_len < 2)
		वापस ERR_PTR(-EINVAL);

	*(data++) = _tag(UNIV, CONS, SEQ);
	data_len--;

	ret = asn1_encode_length(&data, &data_len, len);
	अगर (ret)
		वापस ERR_PTR(ret);

	अगर (!seq)
		वापस data;

	अगर (data_len < len)
		वापस ERR_PTR(-EINVAL);

	स_नकल(data, seq, len);
	data += len;

	वापस data;
पूर्ण
EXPORT_SYMBOL_GPL(asn1_encode_sequence);

/**
 * asn1_encode_boolean() - encode a boolean value to ASN.1
 * @data:	poपूर्णांकer to encode at
 * @end_data:	end of data poपूर्णांकer, poपूर्णांकs one beyond last usable byte in @data
 * @val:	the boolean true/false value
 */
अचिन्हित अक्षर *
asn1_encode_boolean(अचिन्हित अक्षर *data, स्थिर अचिन्हित अक्षर *end_data,
		    bool val)
अणु
	पूर्णांक data_len = end_data - data;

	अगर (IS_ERR(data))
		वापस data;

	/* booleans are 3 bytes: tag, length == 1 and value == 0 or 1 */
	अगर (data_len < 3)
		वापस ERR_PTR(-EINVAL);

	*(data++) = _tag(UNIV, PRIM, BOOL);
	data_len--;

	asn1_encode_length(&data, &data_len, 1);

	अगर (val)
		*(data++) = 1;
	अन्यथा
		*(data++) = 0;

	वापस data;
पूर्ण
EXPORT_SYMBOL_GPL(asn1_encode_boolean);

MODULE_LICENSE("GPL");
