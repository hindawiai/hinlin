<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2012-2015, The Linux Foundation. All rights reserved.
 * Copyright (C) 2017 Linaro Ltd.
 */
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/soc/qcom/qmi.h>

#घोषणा QMI_ENCDEC_ENCODE_TLV(type, length, p_dst) करो अणु \
	*p_dst++ = type; \
	*p_dst++ = ((u8)((length) & 0xFF)); \
	*p_dst++ = ((u8)(((length) >> 8) & 0xFF)); \
पूर्ण जबतक (0)

#घोषणा QMI_ENCDEC_DECODE_TLV(p_type, p_length, p_src) करो अणु \
	*p_type = (u8)*p_src++; \
	*p_length = (u8)*p_src++; \
	*p_length |= ((u8)*p_src) << 8; \
पूर्ण जबतक (0)

#घोषणा QMI_ENCDEC_ENCODE_N_BYTES(p_dst, p_src, size) \
करो अणु \
	स_नकल(p_dst, p_src, size); \
	p_dst = (u8 *)p_dst + size; \
	p_src = (u8 *)p_src + size; \
पूर्ण जबतक (0)

#घोषणा QMI_ENCDEC_DECODE_N_BYTES(p_dst, p_src, size) \
करो अणु \
	स_नकल(p_dst, p_src, size); \
	p_dst = (u8 *)p_dst + size; \
	p_src = (u8 *)p_src + size; \
पूर्ण जबतक (0)

#घोषणा UPDATE_ENCODE_VARIABLES(temp_si, buf_dst, \
				encoded_bytes, tlv_len, encode_tlv, rc) \
करो अणु \
	buf_dst = (u8 *)buf_dst + rc; \
	encoded_bytes += rc; \
	tlv_len += rc; \
	temp_si = temp_si + 1; \
	encode_tlv = 1; \
पूर्ण जबतक (0)

#घोषणा UPDATE_DECODE_VARIABLES(buf_src, decoded_bytes, rc) \
करो अणु \
	buf_src = (u8 *)buf_src + rc; \
	decoded_bytes += rc; \
पूर्ण जबतक (0)

#घोषणा TLV_LEN_SIZE माप(u16)
#घोषणा TLV_TYPE_SIZE माप(u8)
#घोषणा OPTIONAL_TLV_TYPE_START 0x10

अटल पूर्णांक qmi_encode(काष्ठा qmi_elem_info *ei_array, व्योम *out_buf,
		      स्थिर व्योम *in_c_काष्ठा, u32 out_buf_len,
		      पूर्णांक enc_level);

अटल पूर्णांक qmi_decode(काष्ठा qmi_elem_info *ei_array, व्योम *out_c_काष्ठा,
		      स्थिर व्योम *in_buf, u32 in_buf_len, पूर्णांक dec_level);

/**
 * skip_to_next_elem() - Skip to next element in the काष्ठाure to be encoded
 * @ei_array: Struct info describing the element to be skipped.
 * @level: Depth level of encoding/decoding to identअगरy nested काष्ठाures.
 *
 * This function is used जबतक encoding optional elements. If the flag
 * corresponding to an optional element is not set, then encoding the
 * optional element can be skipped. This function can be used to perक्रमm
 * that operation.
 *
 * Return: काष्ठा info of the next element that can be encoded.
 */
अटल काष्ठा qmi_elem_info *skip_to_next_elem(काष्ठा qmi_elem_info *ei_array,
					       पूर्णांक level)
अणु
	काष्ठा qmi_elem_info *temp_ei = ei_array;
	u8 tlv_type;

	अगर (level > 1) अणु
		temp_ei = temp_ei + 1;
	पूर्ण अन्यथा अणु
		करो अणु
			tlv_type = temp_ei->tlv_type;
			temp_ei = temp_ei + 1;
		पूर्ण जबतक (tlv_type == temp_ei->tlv_type);
	पूर्ण

	वापस temp_ei;
पूर्ण

/**
 * qmi_calc_min_msg_len() - Calculate the minimum length of a QMI message
 * @ei_array: Struct info array describing the काष्ठाure.
 * @level: Level to identअगरy the depth of the nested काष्ठाures.
 *
 * Return: Expected minimum length of the QMI message or 0 on error.
 */
अटल पूर्णांक qmi_calc_min_msg_len(काष्ठा qmi_elem_info *ei_array,
				पूर्णांक level)
अणु
	पूर्णांक min_msg_len = 0;
	काष्ठा qmi_elem_info *temp_ei = ei_array;

	अगर (!ei_array)
		वापस min_msg_len;

	जबतक (temp_ei->data_type != QMI_EOTI) अणु
		/* Optional elements करो not count in minimum length */
		अगर (temp_ei->data_type == QMI_OPT_FLAG) अणु
			temp_ei = skip_to_next_elem(temp_ei, level);
			जारी;
		पूर्ण

		अगर (temp_ei->data_type == QMI_DATA_LEN) अणु
			min_msg_len += (temp_ei->elem_size == माप(u8) ?
					माप(u8) : माप(u16));
			temp_ei++;
			जारी;
		पूर्ण अन्यथा अगर (temp_ei->data_type == QMI_STRUCT) अणु
			min_msg_len += qmi_calc_min_msg_len(temp_ei->ei_array,
							    (level + 1));
			temp_ei++;
		पूर्ण अन्यथा अगर (temp_ei->data_type == QMI_STRING) अणु
			अगर (level > 1)
				min_msg_len += temp_ei->elem_len <= U8_MAX ?
					माप(u8) : माप(u16);
			min_msg_len += temp_ei->elem_len * temp_ei->elem_size;
			temp_ei++;
		पूर्ण अन्यथा अणु
			min_msg_len += (temp_ei->elem_len * temp_ei->elem_size);
			temp_ei++;
		पूर्ण

		/*
		 * Type & Length info. not prepended क्रम elements in the
		 * nested काष्ठाure.
		 */
		अगर (level == 1)
			min_msg_len += (TLV_TYPE_SIZE + TLV_LEN_SIZE);
	पूर्ण

	वापस min_msg_len;
पूर्ण

/**
 * qmi_encode_basic_elem() - Encodes elements of basic/primary data type
 * @buf_dst: Buffer to store the encoded inक्रमmation.
 * @buf_src: Buffer containing the elements to be encoded.
 * @elem_len: Number of elements, in the buf_src, to be encoded.
 * @elem_size: Size of a single instance of the element to be encoded.
 *
 * This function encodes the "elem_len" number of data elements, each of
 * size "elem_size" bytes from the source buffer "buf_src" and stores the
 * encoded inक्रमmation in the destination buffer "buf_dst". The elements are
 * of primary data type which include u8 - u64 or similar. This
 * function वापसs the number of bytes of encoded inक्रमmation.
 *
 * Return: The number of bytes of encoded inक्रमmation.
 */
अटल पूर्णांक qmi_encode_basic_elem(व्योम *buf_dst, स्थिर व्योम *buf_src,
				 u32 elem_len, u32 elem_size)
अणु
	u32 i, rc = 0;

	क्रम (i = 0; i < elem_len; i++) अणु
		QMI_ENCDEC_ENCODE_N_BYTES(buf_dst, buf_src, elem_size);
		rc += elem_size;
	पूर्ण

	वापस rc;
पूर्ण

/**
 * qmi_encode_काष्ठा_elem() - Encodes elements of काष्ठा data type
 * @ei_array: Struct info array descibing the काष्ठा element.
 * @buf_dst: Buffer to store the encoded inक्रमmation.
 * @buf_src: Buffer containing the elements to be encoded.
 * @elem_len: Number of elements, in the buf_src, to be encoded.
 * @out_buf_len: Available space in the encode buffer.
 * @enc_level: Depth of the nested काष्ठाure from the मुख्य काष्ठाure.
 *
 * This function encodes the "elem_len" number of काष्ठा elements, each of
 * size "ei_array->elem_size" bytes from the source buffer "buf_src" and
 * stores the encoded inक्रमmation in the destination buffer "buf_dst". The
 * elements are of काष्ठा data type which includes any C काष्ठाure. This
 * function वापसs the number of bytes of encoded inक्रमmation.
 *
 * Return: The number of bytes of encoded inक्रमmation on success or negative
 * त्रुटि_सं on error.
 */
अटल पूर्णांक qmi_encode_काष्ठा_elem(काष्ठा qmi_elem_info *ei_array,
				  व्योम *buf_dst, स्थिर व्योम *buf_src,
				  u32 elem_len, u32 out_buf_len,
				  पूर्णांक enc_level)
अणु
	पूर्णांक i, rc, encoded_bytes = 0;
	काष्ठा qmi_elem_info *temp_ei = ei_array;

	क्रम (i = 0; i < elem_len; i++) अणु
		rc = qmi_encode(temp_ei->ei_array, buf_dst, buf_src,
				out_buf_len - encoded_bytes, enc_level);
		अगर (rc < 0) अणु
			pr_err("%s: STRUCT Encode failure\n", __func__);
			वापस rc;
		पूर्ण
		buf_dst = buf_dst + rc;
		buf_src = buf_src + temp_ei->elem_size;
		encoded_bytes += rc;
	पूर्ण

	वापस encoded_bytes;
पूर्ण

/**
 * qmi_encode_string_elem() - Encodes elements of string data type
 * @ei_array: Struct info array descibing the string element.
 * @buf_dst: Buffer to store the encoded inक्रमmation.
 * @buf_src: Buffer containing the elements to be encoded.
 * @out_buf_len: Available space in the encode buffer.
 * @enc_level: Depth of the string element from the मुख्य काष्ठाure.
 *
 * This function encodes a string element of maximum length "ei_array->elem_len"
 * bytes from the source buffer "buf_src" and stores the encoded inक्रमmation in
 * the destination buffer "buf_dst". This function वापसs the number of bytes
 * of encoded inक्रमmation.
 *
 * Return: The number of bytes of encoded inक्रमmation on success or negative
 * त्रुटि_सं on error.
 */
अटल पूर्णांक qmi_encode_string_elem(काष्ठा qmi_elem_info *ei_array,
				  व्योम *buf_dst, स्थिर व्योम *buf_src,
				  u32 out_buf_len, पूर्णांक enc_level)
अणु
	पूर्णांक rc;
	पूर्णांक encoded_bytes = 0;
	काष्ठा qmi_elem_info *temp_ei = ei_array;
	u32 string_len = 0;
	u32 string_len_sz = 0;

	string_len = म_माप(buf_src);
	string_len_sz = temp_ei->elem_len <= U8_MAX ?
			माप(u8) : माप(u16);
	अगर (string_len > temp_ei->elem_len) अणु
		pr_err("%s: String to be encoded is longer - %d > %d\n",
		       __func__, string_len, temp_ei->elem_len);
		वापस -EINVAL;
	पूर्ण

	अगर (enc_level == 1) अणु
		अगर (string_len + TLV_LEN_SIZE + TLV_TYPE_SIZE >
		    out_buf_len) अणु
			pr_err("%s: Output len %d > Out Buf len %d\n",
			       __func__, string_len, out_buf_len);
			वापस -ETOOSMALL;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (string_len + string_len_sz > out_buf_len) अणु
			pr_err("%s: Output len %d > Out Buf len %d\n",
			       __func__, string_len, out_buf_len);
			वापस -ETOOSMALL;
		पूर्ण
		rc = qmi_encode_basic_elem(buf_dst, &string_len,
					   1, string_len_sz);
		encoded_bytes += rc;
	पूर्ण

	rc = qmi_encode_basic_elem(buf_dst + encoded_bytes, buf_src,
				   string_len, temp_ei->elem_size);
	encoded_bytes += rc;

	वापस encoded_bytes;
पूर्ण

/**
 * qmi_encode() - Core Encode Function
 * @ei_array: Struct info array describing the काष्ठाure to be encoded.
 * @out_buf: Buffer to hold the encoded QMI message.
 * @in_c_काष्ठा: Poपूर्णांकer to the C काष्ठाure to be encoded.
 * @out_buf_len: Available space in the encode buffer.
 * @enc_level: Encode level to indicate the depth of the nested काष्ठाure,
 *             within the मुख्य काष्ठाure, being encoded.
 *
 * Return: The number of bytes of encoded inक्रमmation on success or negative
 * त्रुटि_सं on error.
 */
अटल पूर्णांक qmi_encode(काष्ठा qmi_elem_info *ei_array, व्योम *out_buf,
		      स्थिर व्योम *in_c_काष्ठा, u32 out_buf_len,
		      पूर्णांक enc_level)
अणु
	काष्ठा qmi_elem_info *temp_ei = ei_array;
	u8 opt_flag_value = 0;
	u32 data_len_value = 0, data_len_sz;
	u8 *buf_dst = (u8 *)out_buf;
	u8 *tlv_poपूर्णांकer;
	u32 tlv_len;
	u8 tlv_type;
	u32 encoded_bytes = 0;
	स्थिर व्योम *buf_src;
	पूर्णांक encode_tlv = 0;
	पूर्णांक rc;

	अगर (!ei_array)
		वापस 0;

	tlv_poपूर्णांकer = buf_dst;
	tlv_len = 0;
	अगर (enc_level == 1)
		buf_dst = buf_dst + (TLV_LEN_SIZE + TLV_TYPE_SIZE);

	जबतक (temp_ei->data_type != QMI_EOTI) अणु
		buf_src = in_c_काष्ठा + temp_ei->offset;
		tlv_type = temp_ei->tlv_type;

		अगर (temp_ei->array_type == NO_ARRAY) अणु
			data_len_value = 1;
		पूर्ण अन्यथा अगर (temp_ei->array_type == STATIC_ARRAY) अणु
			data_len_value = temp_ei->elem_len;
		पूर्ण अन्यथा अगर (data_len_value <= 0 ||
			    temp_ei->elem_len < data_len_value) अणु
			pr_err("%s: Invalid data length\n", __func__);
			वापस -EINVAL;
		पूर्ण

		चयन (temp_ei->data_type) अणु
		हाल QMI_OPT_FLAG:
			rc = qmi_encode_basic_elem(&opt_flag_value, buf_src,
						   1, माप(u8));
			अगर (opt_flag_value)
				temp_ei = temp_ei + 1;
			अन्यथा
				temp_ei = skip_to_next_elem(temp_ei, enc_level);
			अवरोध;

		हाल QMI_DATA_LEN:
			स_नकल(&data_len_value, buf_src, temp_ei->elem_size);
			data_len_sz = temp_ei->elem_size == माप(u8) ?
					माप(u8) : माप(u16);
			/* Check to aव्योम out of range buffer access */
			अगर ((data_len_sz + encoded_bytes + TLV_LEN_SIZE +
			    TLV_TYPE_SIZE) > out_buf_len) अणु
				pr_err("%s: Too Small Buffer @DATA_LEN\n",
				       __func__);
				वापस -ETOOSMALL;
			पूर्ण
			rc = qmi_encode_basic_elem(buf_dst, &data_len_value,
						   1, data_len_sz);
			UPDATE_ENCODE_VARIABLES(temp_ei, buf_dst,
						encoded_bytes, tlv_len,
						encode_tlv, rc);
			अगर (!data_len_value)
				temp_ei = skip_to_next_elem(temp_ei, enc_level);
			अन्यथा
				encode_tlv = 0;
			अवरोध;

		हाल QMI_UNSIGNED_1_BYTE:
		हाल QMI_UNSIGNED_2_BYTE:
		हाल QMI_UNSIGNED_4_BYTE:
		हाल QMI_UNSIGNED_8_BYTE:
		हाल QMI_SIGNED_2_BYTE_ENUM:
		हाल QMI_SIGNED_4_BYTE_ENUM:
			/* Check to aव्योम out of range buffer access */
			अगर (((data_len_value * temp_ei->elem_size) +
			    encoded_bytes + TLV_LEN_SIZE + TLV_TYPE_SIZE) >
			    out_buf_len) अणु
				pr_err("%s: Too Small Buffer @data_type:%d\n",
				       __func__, temp_ei->data_type);
				वापस -ETOOSMALL;
			पूर्ण
			rc = qmi_encode_basic_elem(buf_dst, buf_src,
						   data_len_value,
						   temp_ei->elem_size);
			UPDATE_ENCODE_VARIABLES(temp_ei, buf_dst,
						encoded_bytes, tlv_len,
						encode_tlv, rc);
			अवरोध;

		हाल QMI_STRUCT:
			rc = qmi_encode_काष्ठा_elem(temp_ei, buf_dst, buf_src,
						    data_len_value,
						    out_buf_len - encoded_bytes,
						    enc_level + 1);
			अगर (rc < 0)
				वापस rc;
			UPDATE_ENCODE_VARIABLES(temp_ei, buf_dst,
						encoded_bytes, tlv_len,
						encode_tlv, rc);
			अवरोध;

		हाल QMI_STRING:
			rc = qmi_encode_string_elem(temp_ei, buf_dst, buf_src,
						    out_buf_len - encoded_bytes,
						    enc_level);
			अगर (rc < 0)
				वापस rc;
			UPDATE_ENCODE_VARIABLES(temp_ei, buf_dst,
						encoded_bytes, tlv_len,
						encode_tlv, rc);
			अवरोध;
		शेष:
			pr_err("%s: Unrecognized data type\n", __func__);
			वापस -EINVAL;
		पूर्ण

		अगर (encode_tlv && enc_level == 1) अणु
			QMI_ENCDEC_ENCODE_TLV(tlv_type, tlv_len, tlv_poपूर्णांकer);
			encoded_bytes += (TLV_TYPE_SIZE + TLV_LEN_SIZE);
			tlv_poपूर्णांकer = buf_dst;
			tlv_len = 0;
			buf_dst = buf_dst + TLV_LEN_SIZE + TLV_TYPE_SIZE;
			encode_tlv = 0;
		पूर्ण
	पूर्ण

	वापस encoded_bytes;
पूर्ण

/**
 * qmi_decode_basic_elem() - Decodes elements of basic/primary data type
 * @buf_dst: Buffer to store the decoded element.
 * @buf_src: Buffer containing the elements in QMI wire क्रमmat.
 * @elem_len: Number of elements to be decoded.
 * @elem_size: Size of a single instance of the element to be decoded.
 *
 * This function decodes the "elem_len" number of elements in QMI wire क्रमmat,
 * each of size "elem_size" bytes from the source buffer "buf_src" and stores
 * the decoded elements in the destination buffer "buf_dst". The elements are
 * of primary data type which include u8 - u64 or similar. This
 * function वापसs the number of bytes of decoded inक्रमmation.
 *
 * Return: The total size of the decoded data elements, in bytes.
 */
अटल पूर्णांक qmi_decode_basic_elem(व्योम *buf_dst, स्थिर व्योम *buf_src,
				 u32 elem_len, u32 elem_size)
अणु
	u32 i, rc = 0;

	क्रम (i = 0; i < elem_len; i++) अणु
		QMI_ENCDEC_DECODE_N_BYTES(buf_dst, buf_src, elem_size);
		rc += elem_size;
	पूर्ण

	वापस rc;
पूर्ण

/**
 * qmi_decode_काष्ठा_elem() - Decodes elements of काष्ठा data type
 * @ei_array: Struct info array describing the काष्ठा element.
 * @buf_dst: Buffer to store the decoded element.
 * @buf_src: Buffer containing the elements in QMI wire क्रमmat.
 * @elem_len: Number of elements to be decoded.
 * @tlv_len: Total size of the encoded inक्रमmation corresponding to
 *           this काष्ठा element.
 * @dec_level: Depth of the nested काष्ठाure from the मुख्य काष्ठाure.
 *
 * This function decodes the "elem_len" number of elements in QMI wire क्रमmat,
 * each of size "(tlv_len/elem_len)" bytes from the source buffer "buf_src"
 * and stores the decoded elements in the destination buffer "buf_dst". The
 * elements are of काष्ठा data type which includes any C काष्ठाure. This
 * function वापसs the number of bytes of decoded inक्रमmation.
 *
 * Return: The total size of the decoded data elements on success, negative
 * त्रुटि_सं on error.
 */
अटल पूर्णांक qmi_decode_काष्ठा_elem(काष्ठा qmi_elem_info *ei_array,
				  व्योम *buf_dst, स्थिर व्योम *buf_src,
				  u32 elem_len, u32 tlv_len,
				  पूर्णांक dec_level)
अणु
	पूर्णांक i, rc, decoded_bytes = 0;
	काष्ठा qmi_elem_info *temp_ei = ei_array;

	क्रम (i = 0; i < elem_len && decoded_bytes < tlv_len; i++) अणु
		rc = qmi_decode(temp_ei->ei_array, buf_dst, buf_src,
				tlv_len - decoded_bytes, dec_level);
		अगर (rc < 0)
			वापस rc;
		buf_src = buf_src + rc;
		buf_dst = buf_dst + temp_ei->elem_size;
		decoded_bytes += rc;
	पूर्ण

	अगर ((dec_level <= 2 && decoded_bytes != tlv_len) ||
	    (dec_level > 2 && (i < elem_len || decoded_bytes > tlv_len))) अणु
		pr_err("%s: Fault in decoding: dl(%d), db(%d), tl(%d), i(%d), el(%d)\n",
		       __func__, dec_level, decoded_bytes, tlv_len,
		       i, elem_len);
		वापस -EFAULT;
	पूर्ण

	वापस decoded_bytes;
पूर्ण

/**
 * qmi_decode_string_elem() - Decodes elements of string data type
 * @ei_array: Struct info array describing the string element.
 * @buf_dst: Buffer to store the decoded element.
 * @buf_src: Buffer containing the elements in QMI wire क्रमmat.
 * @tlv_len: Total size of the encoded inक्रमmation corresponding to
 *           this string element.
 * @dec_level: Depth of the string element from the मुख्य काष्ठाure.
 *
 * This function decodes the string element of maximum length
 * "ei_array->elem_len" from the source buffer "buf_src" and माला_दो it पूर्णांकo
 * the destination buffer "buf_dst". This function वापसs number of bytes
 * decoded from the input buffer.
 *
 * Return: The total size of the decoded data elements on success, negative
 * त्रुटि_सं on error.
 */
अटल पूर्णांक qmi_decode_string_elem(काष्ठा qmi_elem_info *ei_array,
				  व्योम *buf_dst, स्थिर व्योम *buf_src,
				  u32 tlv_len, पूर्णांक dec_level)
अणु
	पूर्णांक rc;
	पूर्णांक decoded_bytes = 0;
	u32 string_len = 0;
	u32 string_len_sz = 0;
	काष्ठा qmi_elem_info *temp_ei = ei_array;

	अगर (dec_level == 1) अणु
		string_len = tlv_len;
	पूर्ण अन्यथा अणु
		string_len_sz = temp_ei->elem_len <= U8_MAX ?
				माप(u8) : माप(u16);
		rc = qmi_decode_basic_elem(&string_len, buf_src,
					   1, string_len_sz);
		decoded_bytes += rc;
	पूर्ण

	अगर (string_len > temp_ei->elem_len) अणु
		pr_err("%s: String len %d > Max Len %d\n",
		       __func__, string_len, temp_ei->elem_len);
		वापस -ETOOSMALL;
	पूर्ण अन्यथा अगर (string_len > tlv_len) अणु
		pr_err("%s: String len %d > Input Buffer Len %d\n",
		       __func__, string_len, tlv_len);
		वापस -EFAULT;
	पूर्ण

	rc = qmi_decode_basic_elem(buf_dst, buf_src + decoded_bytes,
				   string_len, temp_ei->elem_size);
	*((अक्षर *)buf_dst + string_len) = '\0';
	decoded_bytes += rc;

	वापस decoded_bytes;
पूर्ण

/**
 * find_ei() - Find element info corresponding to TLV Type
 * @ei_array: Struct info array of the message being decoded.
 * @type: TLV Type of the element being searched.
 *
 * Every element that got encoded in the QMI message will have a type
 * inक्रमmation associated with it. While decoding the QMI message,
 * this function is used to find the काष्ठा info regarding the element
 * that corresponds to the type being decoded.
 *
 * Return: Poपूर्णांकer to काष्ठा info, अगर found
 */
अटल काष्ठा qmi_elem_info *find_ei(काष्ठा qmi_elem_info *ei_array,
				     u32 type)
अणु
	काष्ठा qmi_elem_info *temp_ei = ei_array;

	जबतक (temp_ei->data_type != QMI_EOTI) अणु
		अगर (temp_ei->tlv_type == (u8)type)
			वापस temp_ei;
		temp_ei = temp_ei + 1;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * qmi_decode() - Core Decode Function
 * @ei_array: Struct info array describing the काष्ठाure to be decoded.
 * @out_c_काष्ठा: Buffer to hold the decoded C काष्ठा
 * @in_buf: Buffer containing the QMI message to be decoded
 * @in_buf_len: Length of the QMI message to be decoded
 * @dec_level: Decode level to indicate the depth of the nested काष्ठाure,
 *             within the मुख्य काष्ठाure, being decoded
 *
 * Return: The number of bytes of decoded inक्रमmation on success, negative
 * त्रुटि_सं on error.
 */
अटल पूर्णांक qmi_decode(काष्ठा qmi_elem_info *ei_array, व्योम *out_c_काष्ठा,
		      स्थिर व्योम *in_buf, u32 in_buf_len,
		      पूर्णांक dec_level)
अणु
	काष्ठा qmi_elem_info *temp_ei = ei_array;
	u8 opt_flag_value = 1;
	u32 data_len_value = 0, data_len_sz = 0;
	u8 *buf_dst = out_c_काष्ठा;
	स्थिर u8 *tlv_poपूर्णांकer;
	u32 tlv_len = 0;
	u32 tlv_type;
	u32 decoded_bytes = 0;
	स्थिर व्योम *buf_src = in_buf;
	पूर्णांक rc;

	जबतक (decoded_bytes < in_buf_len) अणु
		अगर (dec_level >= 2 && temp_ei->data_type == QMI_EOTI)
			वापस decoded_bytes;

		अगर (dec_level == 1) अणु
			tlv_poपूर्णांकer = buf_src;
			QMI_ENCDEC_DECODE_TLV(&tlv_type,
					      &tlv_len, tlv_poपूर्णांकer);
			buf_src += (TLV_TYPE_SIZE + TLV_LEN_SIZE);
			decoded_bytes += (TLV_TYPE_SIZE + TLV_LEN_SIZE);
			temp_ei = find_ei(ei_array, tlv_type);
			अगर (!temp_ei && tlv_type < OPTIONAL_TLV_TYPE_START) अणु
				pr_err("%s: Inval element info\n", __func__);
				वापस -EINVAL;
			पूर्ण अन्यथा अगर (!temp_ei) अणु
				UPDATE_DECODE_VARIABLES(buf_src,
							decoded_bytes, tlv_len);
				जारी;
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * No length inक्रमmation क्रम elements in nested
			 * काष्ठाures. So use reमुख्यing decodable buffer space.
			 */
			tlv_len = in_buf_len - decoded_bytes;
		पूर्ण

		buf_dst = out_c_काष्ठा + temp_ei->offset;
		अगर (temp_ei->data_type == QMI_OPT_FLAG) अणु
			स_नकल(buf_dst, &opt_flag_value, माप(u8));
			temp_ei = temp_ei + 1;
			buf_dst = out_c_काष्ठा + temp_ei->offset;
		पूर्ण

		अगर (temp_ei->data_type == QMI_DATA_LEN) अणु
			data_len_sz = temp_ei->elem_size == माप(u8) ?
					माप(u8) : माप(u16);
			rc = qmi_decode_basic_elem(&data_len_value, buf_src,
						   1, data_len_sz);
			स_नकल(buf_dst, &data_len_value, माप(u32));
			temp_ei = temp_ei + 1;
			buf_dst = out_c_काष्ठा + temp_ei->offset;
			tlv_len -= data_len_sz;
			UPDATE_DECODE_VARIABLES(buf_src, decoded_bytes, rc);
		पूर्ण

		अगर (temp_ei->array_type == NO_ARRAY) अणु
			data_len_value = 1;
		पूर्ण अन्यथा अगर (temp_ei->array_type == STATIC_ARRAY) अणु
			data_len_value = temp_ei->elem_len;
		पूर्ण अन्यथा अगर (data_len_value > temp_ei->elem_len) अणु
			pr_err("%s: Data len %d > max spec %d\n",
			       __func__, data_len_value, temp_ei->elem_len);
			वापस -ETOOSMALL;
		पूर्ण

		चयन (temp_ei->data_type) अणु
		हाल QMI_UNSIGNED_1_BYTE:
		हाल QMI_UNSIGNED_2_BYTE:
		हाल QMI_UNSIGNED_4_BYTE:
		हाल QMI_UNSIGNED_8_BYTE:
		हाल QMI_SIGNED_2_BYTE_ENUM:
		हाल QMI_SIGNED_4_BYTE_ENUM:
			rc = qmi_decode_basic_elem(buf_dst, buf_src,
						   data_len_value,
						   temp_ei->elem_size);
			UPDATE_DECODE_VARIABLES(buf_src, decoded_bytes, rc);
			अवरोध;

		हाल QMI_STRUCT:
			rc = qmi_decode_काष्ठा_elem(temp_ei, buf_dst, buf_src,
						    data_len_value, tlv_len,
						    dec_level + 1);
			अगर (rc < 0)
				वापस rc;
			UPDATE_DECODE_VARIABLES(buf_src, decoded_bytes, rc);
			अवरोध;

		हाल QMI_STRING:
			rc = qmi_decode_string_elem(temp_ei, buf_dst, buf_src,
						    tlv_len, dec_level);
			अगर (rc < 0)
				वापस rc;
			UPDATE_DECODE_VARIABLES(buf_src, decoded_bytes, rc);
			अवरोध;

		शेष:
			pr_err("%s: Unrecognized data type\n", __func__);
			वापस -EINVAL;
		पूर्ण
		temp_ei = temp_ei + 1;
	पूर्ण

	वापस decoded_bytes;
पूर्ण

/**
 * qmi_encode_message() - Encode C काष्ठाure as QMI encoded message
 * @type:	Type of QMI message
 * @msg_id:	Message ID of the message
 * @len:	Passed as max length of the message, updated to actual size
 * @txn_id:	Transaction ID
 * @ei:		QMI message descriptor
 * @c_काष्ठा:	Reference to काष्ठाure to encode
 *
 * Return: Buffer with encoded message, or negative ERR_PTR() on error
 */
व्योम *qmi_encode_message(पूर्णांक type, अचिन्हित पूर्णांक msg_id, माप_प्रकार *len,
			 अचिन्हित पूर्णांक txn_id, काष्ठा qmi_elem_info *ei,
			 स्थिर व्योम *c_काष्ठा)
अणु
	काष्ठा qmi_header *hdr;
	sमाप_प्रकार msglen = 0;
	व्योम *msg;
	पूर्णांक ret;

	/* Check the possibility of a zero length QMI message */
	अगर (!c_काष्ठा) अणु
		ret = qmi_calc_min_msg_len(ei, 1);
		अगर (ret) अणु
			pr_err("%s: Calc. len %d != 0, but NULL c_struct\n",
			       __func__, ret);
			वापस ERR_PTR(-EINVAL);
		पूर्ण
	पूर्ण

	msg = kzalloc(माप(*hdr) + *len, GFP_KERNEL);
	अगर (!msg)
		वापस ERR_PTR(-ENOMEM);

	/* Encode message, अगर we have a message */
	अगर (c_काष्ठा) अणु
		msglen = qmi_encode(ei, msg + माप(*hdr), c_काष्ठा, *len, 1);
		अगर (msglen < 0) अणु
			kमुक्त(msg);
			वापस ERR_PTR(msglen);
		पूर्ण
	पूर्ण

	hdr = msg;
	hdr->type = type;
	hdr->txn_id = txn_id;
	hdr->msg_id = msg_id;
	hdr->msg_len = msglen;

	*len = माप(*hdr) + msglen;

	वापस msg;
पूर्ण
EXPORT_SYMBOL(qmi_encode_message);

/**
 * qmi_decode_message() - Decode QMI encoded message to C काष्ठाure
 * @buf:	Buffer with encoded message
 * @len:	Amount of data in @buf
 * @ei:		QMI message descriptor
 * @c_काष्ठा:	Reference to काष्ठाure to decode पूर्णांकo
 *
 * Return: The number of bytes of decoded inक्रमmation on success, negative
 * त्रुटि_सं on error.
 */
पूर्णांक qmi_decode_message(स्थिर व्योम *buf, माप_प्रकार len,
		       काष्ठा qmi_elem_info *ei, व्योम *c_काष्ठा)
अणु
	अगर (!ei)
		वापस -EINVAL;

	अगर (!c_काष्ठा || !buf || !len)
		वापस -EINVAL;

	वापस qmi_decode(ei, c_काष्ठा, buf + माप(काष्ठा qmi_header),
			  len - माप(काष्ठा qmi_header), 1);
पूर्ण
EXPORT_SYMBOL(qmi_decode_message);

/* Common header in all QMI responses */
काष्ठा qmi_elem_info qmi_response_type_v01_ei[] = अणु
	अणु
		.data_type	= QMI_SIGNED_2_BYTE_ENUM,
		.elem_len	= 1,
		.elem_size	= माप(u16),
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
		.offset		= दुरत्व(काष्ठा qmi_response_type_v01, result),
		.ei_array	= शून्य,
	पूर्ण,
	अणु
		.data_type	= QMI_SIGNED_2_BYTE_ENUM,
		.elem_len	= 1,
		.elem_size	= माप(u16),
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
		.offset		= दुरत्व(काष्ठा qmi_response_type_v01, error),
		.ei_array	= शून्य,
	पूर्ण,
	अणु
		.data_type	= QMI_EOTI,
		.elem_len	= 0,
		.elem_size	= 0,
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
		.offset		= 0,
		.ei_array	= शून्य,
	पूर्ण,
पूर्ण;
EXPORT_SYMBOL(qmi_response_type_v01_ei);

MODULE_DESCRIPTION("QMI encoder/decoder helper");
MODULE_LICENSE("GPL v2");
