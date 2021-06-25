<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2013 - 2019 Intel Corporation. */

#समावेश "fm10k_tlv.h"

/**
 *  fm10k_tlv_msg_init - Initialize message block क्रम TLV data storage
 *  @msg: Poपूर्णांकer to message block
 *  @msg_id: Message ID indicating message type
 *
 *  This function वापस success अगर provided with a valid message poपूर्णांकer
 **/
s32 fm10k_tlv_msg_init(u32 *msg, u16 msg_id)
अणु
	/* verअगरy poपूर्णांकer is not शून्य */
	अगर (!msg)
		वापस FM10K_ERR_PARAM;

	*msg = (FM10K_TLV_FLAGS_MSG << FM10K_TLV_FLAGS_SHIFT) | msg_id;

	वापस 0;
पूर्ण

/**
 *  fm10k_tlv_attr_put_null_string - Place null terminated string on message
 *  @msg: Poपूर्णांकer to message block
 *  @attr_id: Attribute ID
 *  @string: Poपूर्णांकer to string to be stored in attribute
 *
 *  This function will reorder a string to be CPU endian and store it in
 *  the attribute buffer.  It will वापस success अगर provided with a valid
 *  poपूर्णांकers.
 **/
अटल s32 fm10k_tlv_attr_put_null_string(u32 *msg, u16 attr_id,
					  स्थिर अचिन्हित अक्षर *string)
अणु
	u32 attr_data = 0, len = 0;
	u32 *attr;

	/* verअगरy poपूर्णांकers are not शून्य */
	अगर (!string || !msg)
		वापस FM10K_ERR_PARAM;

	attr = &msg[FM10K_TLV_DWORD_LEN(*msg)];

	/* copy string पूर्णांकo local variable and then ग_लिखो to msg */
	करो अणु
		/* ग_लिखो data to message */
		अगर (len && !(len % 4)) अणु
			attr[len / 4] = attr_data;
			attr_data = 0;
		पूर्ण

		/* record अक्षरacter to offset location */
		attr_data |= (u32)(*string) << (8 * (len % 4));
		len++;

		/* test क्रम शून्य and then increment */
	पूर्ण जबतक (*(string++));

	/* ग_लिखो last piece of data to message */
	attr[(len + 3) / 4] = attr_data;

	/* record attribute header, update message length */
	len <<= FM10K_TLV_LEN_SHIFT;
	attr[0] = len | attr_id;

	/* add header length to length */
	len += FM10K_TLV_HDR_LEN << FM10K_TLV_LEN_SHIFT;
	*msg += FM10K_TLV_LEN_ALIGN(len);

	वापस 0;
पूर्ण

/**
 *  fm10k_tlv_attr_get_null_string - Get null terminated string from attribute
 *  @attr: Poपूर्णांकer to attribute
 *  @string: Poपूर्णांकer to location of destination string
 *
 *  This function pulls the string back out of the attribute and will place
 *  it in the array poपूर्णांकed by by string.  It will वापस success अगर provided
 *  with a valid poपूर्णांकers.
 **/
अटल s32 fm10k_tlv_attr_get_null_string(u32 *attr, अचिन्हित अक्षर *string)
अणु
	u32 len;

	/* verअगरy poपूर्णांकers are not शून्य */
	अगर (!string || !attr)
		वापस FM10K_ERR_PARAM;

	len = *attr >> FM10K_TLV_LEN_SHIFT;
	attr++;

	जबतक (len--)
		string[len] = (u8)(attr[len / 4] >> (8 * (len % 4)));

	वापस 0;
पूर्ण

/**
 *  fm10k_tlv_attr_put_mac_vlan - Store MAC/VLAN attribute in message
 *  @msg: Poपूर्णांकer to message block
 *  @attr_id: Attribute ID
 *  @mac_addr: MAC address to be stored
 *  @vlan: VLAN to be stored
 *
 *  This function will reorder a MAC address to be CPU endian and store it
 *  in the attribute buffer.  It will वापस success अगर provided with a
 *  valid poपूर्णांकers.
 **/
s32 fm10k_tlv_attr_put_mac_vlan(u32 *msg, u16 attr_id,
				स्थिर u8 *mac_addr, u16 vlan)
अणु
	u32 len = ETH_ALEN << FM10K_TLV_LEN_SHIFT;
	u32 *attr;

	/* verअगरy poपूर्णांकers are not शून्य */
	अगर (!msg || !mac_addr)
		वापस FM10K_ERR_PARAM;

	attr = &msg[FM10K_TLV_DWORD_LEN(*msg)];

	/* record attribute header, update message length */
	attr[0] = len | attr_id;

	/* copy value पूर्णांकo local variable and then ग_लिखो to msg */
	attr[1] = le32_to_cpu(*(स्थिर __le32 *)&mac_addr[0]);
	attr[2] = le16_to_cpu(*(स्थिर __le16 *)&mac_addr[4]);
	attr[2] |= (u32)vlan << 16;

	/* add header length to length */
	len += FM10K_TLV_HDR_LEN << FM10K_TLV_LEN_SHIFT;
	*msg += FM10K_TLV_LEN_ALIGN(len);

	वापस 0;
पूर्ण

/**
 *  fm10k_tlv_attr_get_mac_vlan - Get MAC/VLAN stored in attribute
 *  @attr: Poपूर्णांकer to attribute
 *  @mac_addr: location of buffer to store MAC address
 *  @vlan: location of buffer to store VLAN
 *
 *  This function pulls the MAC address back out of the attribute and will
 *  place it in the array poपूर्णांकed by by mac_addr.  It will वापस success
 *  अगर provided with a valid poपूर्णांकers.
 **/
s32 fm10k_tlv_attr_get_mac_vlan(u32 *attr, u8 *mac_addr, u16 *vlan)
अणु
	/* verअगरy poपूर्णांकers are not शून्य */
	अगर (!mac_addr || !attr)
		वापस FM10K_ERR_PARAM;

	*(__le32 *)&mac_addr[0] = cpu_to_le32(attr[1]);
	*(__le16 *)&mac_addr[4] = cpu_to_le16((u16)(attr[2]));
	*vlan = (u16)(attr[2] >> 16);

	वापस 0;
पूर्ण

/**
 *  fm10k_tlv_attr_put_bool - Add header indicating value "true"
 *  @msg: Poपूर्णांकer to message block
 *  @attr_id: Attribute ID
 *
 *  This function will simply add an attribute header, the fact
 *  that the header is here means the attribute value is true, अन्यथा
 *  it is false.  The function will वापस success अगर provided with a
 *  valid poपूर्णांकers.
 **/
s32 fm10k_tlv_attr_put_bool(u32 *msg, u16 attr_id)
अणु
	/* verअगरy poपूर्णांकers are not शून्य */
	अगर (!msg)
		वापस FM10K_ERR_PARAM;

	/* record attribute header */
	msg[FM10K_TLV_DWORD_LEN(*msg)] = attr_id;

	/* add header length to length */
	*msg += FM10K_TLV_HDR_LEN << FM10K_TLV_LEN_SHIFT;

	वापस 0;
पूर्ण

/**
 *  fm10k_tlv_attr_put_value - Store पूर्णांकeger value attribute in message
 *  @msg: Poपूर्णांकer to message block
 *  @attr_id: Attribute ID
 *  @value: Value to be written
 *  @len: Size of value
 *
 *  This function will place an पूर्णांकeger value of up to 8 bytes in size
 *  in a message attribute.  The function will वापस success provided
 *  that msg is a valid poपूर्णांकer, and len is 1, 2, 4, or 8.
 **/
s32 fm10k_tlv_attr_put_value(u32 *msg, u16 attr_id, s64 value, u32 len)
अणु
	u32 *attr;

	/* verअगरy non-null msg and len is 1, 2, 4, or 8 */
	अगर (!msg || !len || len > 8 || (len & (len - 1)))
		वापस FM10K_ERR_PARAM;

	attr = &msg[FM10K_TLV_DWORD_LEN(*msg)];

	अगर (len < 4) अणु
		attr[1] = (u32)value & (BIT(8 * len) - 1);
	पूर्ण अन्यथा अणु
		attr[1] = (u32)value;
		अगर (len > 4)
			attr[2] = (u32)(value >> 32);
	पूर्ण

	/* record attribute header, update message length */
	len <<= FM10K_TLV_LEN_SHIFT;
	attr[0] = len | attr_id;

	/* add header length to length */
	len += FM10K_TLV_HDR_LEN << FM10K_TLV_LEN_SHIFT;
	*msg += FM10K_TLV_LEN_ALIGN(len);

	वापस 0;
पूर्ण

/**
 *  fm10k_tlv_attr_get_value - Get पूर्णांकeger value stored in attribute
 *  @attr: Poपूर्णांकer to attribute
 *  @value: Poपूर्णांकer to destination buffer
 *  @len: Size of value
 *
 *  This function will place an पूर्णांकeger value of up to 8 bytes in size
 *  in the offset poपूर्णांकed to by value.  The function will वापस success
 *  provided that poपूर्णांकers are valid and the len value matches the
 *  attribute length.
 **/
s32 fm10k_tlv_attr_get_value(u32 *attr, व्योम *value, u32 len)
अणु
	/* verअगरy poपूर्णांकers are not शून्य */
	अगर (!attr || !value)
		वापस FM10K_ERR_PARAM;

	अगर ((*attr >> FM10K_TLV_LEN_SHIFT) != len)
		वापस FM10K_ERR_PARAM;

	अगर (len == 8)
		*(u64 *)value = ((u64)attr[2] << 32) | attr[1];
	अन्यथा अगर (len == 4)
		*(u32 *)value = attr[1];
	अन्यथा अगर (len == 2)
		*(u16 *)value = (u16)attr[1];
	अन्यथा
		*(u8 *)value = (u8)attr[1];

	वापस 0;
पूर्ण

/**
 *  fm10k_tlv_attr_put_le_काष्ठा - Store little endian काष्ठाure in message
 *  @msg: Poपूर्णांकer to message block
 *  @attr_id: Attribute ID
 *  @le_काष्ठा: Poपूर्णांकer to काष्ठाure to be written
 *  @len: Size of le_काष्ठा
 *
 *  This function will place a little endian काष्ठाure value in a message
 *  attribute.  The function will वापस success provided that all poपूर्णांकers
 *  are valid and length is a non-zero multiple of 4.
 **/
s32 fm10k_tlv_attr_put_le_काष्ठा(u32 *msg, u16 attr_id,
				 स्थिर व्योम *le_काष्ठा, u32 len)
अणु
	स्थिर __le32 *le32_ptr = (स्थिर __le32 *)le_काष्ठा;
	u32 *attr;
	u32 i;

	/* verअगरy non-null msg and len is in 32 bit words */
	अगर (!msg || !len || (len % 4))
		वापस FM10K_ERR_PARAM;

	attr = &msg[FM10K_TLV_DWORD_LEN(*msg)];

	/* copy le32 काष्ठाure पूर्णांकo host byte order at 32b boundaries */
	क्रम (i = 0; i < (len / 4); i++)
		attr[i + 1] = le32_to_cpu(le32_ptr[i]);

	/* record attribute header, update message length */
	len <<= FM10K_TLV_LEN_SHIFT;
	attr[0] = len | attr_id;

	/* add header length to length */
	len += FM10K_TLV_HDR_LEN << FM10K_TLV_LEN_SHIFT;
	*msg += FM10K_TLV_LEN_ALIGN(len);

	वापस 0;
पूर्ण

/**
 *  fm10k_tlv_attr_get_le_काष्ठा - Get little endian काष्ठा क्रमm attribute
 *  @attr: Poपूर्णांकer to attribute
 *  @le_काष्ठा: Poपूर्णांकer to काष्ठाure to be written
 *  @len: Size of काष्ठाure
 *
 *  This function will place a little endian काष्ठाure in the buffer
 *  poपूर्णांकed to by le_काष्ठा.  The function will वापस success
 *  provided that poपूर्णांकers are valid and the len value matches the
 *  attribute length.
 **/
s32 fm10k_tlv_attr_get_le_काष्ठा(u32 *attr, व्योम *le_काष्ठा, u32 len)
अणु
	__le32 *le32_ptr = (__le32 *)le_काष्ठा;
	u32 i;

	/* verअगरy poपूर्णांकers are not शून्य */
	अगर (!le_काष्ठा || !attr)
		वापस FM10K_ERR_PARAM;

	अगर ((*attr >> FM10K_TLV_LEN_SHIFT) != len)
		वापस FM10K_ERR_PARAM;

	attr++;

	क्रम (i = 0; len; i++, len -= 4)
		le32_ptr[i] = cpu_to_le32(attr[i]);

	वापस 0;
पूर्ण

/**
 *  fm10k_tlv_attr_nest_start - Start a set of nested attributes
 *  @msg: Poपूर्णांकer to message block
 *  @attr_id: Attribute ID
 *
 *  This function will mark off a new nested region क्रम encapsulating
 *  a given set of attributes.  The idea is अगर you wish to place a secondary
 *  काष्ठाure within the message this mechanism allows क्रम that.  The
 *  function will वापस शून्य on failure, and a poपूर्णांकer to the start
 *  of the nested attributes on success.
 **/
अटल u32 *fm10k_tlv_attr_nest_start(u32 *msg, u16 attr_id)
अणु
	u32 *attr;

	/* verअगरy poपूर्णांकer is not शून्य */
	अगर (!msg)
		वापस शून्य;

	attr = &msg[FM10K_TLV_DWORD_LEN(*msg)];

	attr[0] = attr_id;

	/* वापस poपूर्णांकer to nest header */
	वापस attr;
पूर्ण

/**
 *  fm10k_tlv_attr_nest_stop - Stop a set of nested attributes
 *  @msg: Poपूर्णांकer to message block
 *
 *  This function बंदs off an existing set of nested attributes.  The
 *  message poपूर्णांकer should be poपूर्णांकing to the parent of the nest.  So in
 *  the हाल of a nest within the nest this would be the outer nest poपूर्णांकer.
 *  This function will वापस success provided all poपूर्णांकers are valid.
 **/
अटल s32 fm10k_tlv_attr_nest_stop(u32 *msg)
अणु
	u32 *attr;
	u32 len;

	/* verअगरy poपूर्णांकer is not शून्य */
	अगर (!msg)
		वापस FM10K_ERR_PARAM;

	/* locate the nested header and retrieve its length */
	attr = &msg[FM10K_TLV_DWORD_LEN(*msg)];
	len = (attr[0] >> FM10K_TLV_LEN_SHIFT) << FM10K_TLV_LEN_SHIFT;

	/* only include nest अगर data was added to it */
	अगर (len) अणु
		len += FM10K_TLV_HDR_LEN << FM10K_TLV_LEN_SHIFT;
		*msg += len;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  fm10k_tlv_attr_validate - Validate attribute metadata
 *  @attr: Poपूर्णांकer to attribute
 *  @tlv_attr: Type and length info क्रम attribute
 *
 *  This function करोes some basic validation of the input TLV.  It
 *  verअगरies the length, and in the हाल of null terminated strings
 *  it verअगरies that the last byte is null.  The function will
 *  वापस FM10K_ERR_PARAM अगर any attribute is malक्रमmed, otherwise
 *  it वापसs 0.
 **/
अटल s32 fm10k_tlv_attr_validate(u32 *attr,
				   स्थिर काष्ठा fm10k_tlv_attr *tlv_attr)
अणु
	u32 attr_id = *attr & FM10K_TLV_ID_MASK;
	u16 len = *attr >> FM10K_TLV_LEN_SHIFT;

	/* verअगरy this is an attribute and not a message */
	अगर (*attr & (FM10K_TLV_FLAGS_MSG << FM10K_TLV_FLAGS_SHIFT))
		वापस FM10K_ERR_PARAM;

	/* search through the list of attributes to find a matching ID */
	जबतक (tlv_attr->id < attr_id)
		tlv_attr++;

	/* अगर didn't find a match then we should निकास */
	अगर (tlv_attr->id != attr_id)
		वापस FM10K_NOT_IMPLEMENTED;

	/* move to start of attribute data */
	attr++;

	चयन (tlv_attr->type) अणु
	हाल FM10K_TLV_शून्य_STRING:
		अगर (!len ||
		    (attr[(len - 1) / 4] & (0xFF << (8 * ((len - 1) % 4)))))
			वापस FM10K_ERR_PARAM;
		अगर (len > tlv_attr->len)
			वापस FM10K_ERR_PARAM;
		अवरोध;
	हाल FM10K_TLV_MAC_ADDR:
		अगर (len != ETH_ALEN)
			वापस FM10K_ERR_PARAM;
		अवरोध;
	हाल FM10K_TLV_BOOL:
		अगर (len)
			वापस FM10K_ERR_PARAM;
		अवरोध;
	हाल FM10K_TLV_UNSIGNED:
	हाल FM10K_TLV_SIGNED:
		अगर (len != tlv_attr->len)
			वापस FM10K_ERR_PARAM;
		अवरोध;
	हाल FM10K_TLV_LE_STRUCT:
		/* काष्ठा must be 4 byte aligned */
		अगर ((len % 4) || len != tlv_attr->len)
			वापस FM10K_ERR_PARAM;
		अवरोध;
	हाल FM10K_TLV_NESTED:
		/* nested attributes must be 4 byte aligned */
		अगर (len % 4)
			वापस FM10K_ERR_PARAM;
		अवरोध;
	शेष:
		/* attribute id is mapped to bad value */
		वापस FM10K_ERR_PARAM;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  fm10k_tlv_attr_parse - Parses stream of attribute data
 *  @attr: Poपूर्णांकer to attribute list
 *  @results: Poपूर्णांकer array to store poपूर्णांकers to attributes
 *  @tlv_attr: Type and length info क्रम attributes
 *
 *  This function validates a stream of attributes and parses them
 *  up पूर्णांकo an array of poपूर्णांकers stored in results.  The function will
 *  वापस FM10K_ERR_PARAM on any input or message error,
 *  FM10K_NOT_IMPLEMENTED क्रम any attribute that is outside of the array
 *  and 0 on success. Any attributes not found in tlv_attr will be silently
 *  ignored.
 **/
अटल s32 fm10k_tlv_attr_parse(u32 *attr, u32 **results,
				स्थिर काष्ठा fm10k_tlv_attr *tlv_attr)
अणु
	u32 i, attr_id, offset = 0;
	s32 err;
	u16 len;

	/* verअगरy poपूर्णांकers are not शून्य */
	अगर (!attr || !results)
		वापस FM10K_ERR_PARAM;

	/* initialize results to शून्य */
	क्रम (i = 0; i < FM10K_TLV_RESULTS_MAX; i++)
		results[i] = शून्य;

	/* pull length from the message header */
	len = *attr >> FM10K_TLV_LEN_SHIFT;

	/* no attributes to parse अगर there is no length */
	अगर (!len)
		वापस 0;

	/* no attributes to parse, just raw data, message becomes attribute */
	अगर (!tlv_attr) अणु
		results[0] = attr;
		वापस 0;
	पूर्ण

	/* move to start of attribute data */
	attr++;

	/* run through list parsing all attributes */
	जबतक (offset < len) अणु
		attr_id = *attr & FM10K_TLV_ID_MASK;

		अगर (attr_id >= FM10K_TLV_RESULTS_MAX)
			वापस FM10K_NOT_IMPLEMENTED;

		err = fm10k_tlv_attr_validate(attr, tlv_attr);
		अगर (err == FM10K_NOT_IMPLEMENTED)
			; /* silently ignore non-implemented attributes */
		अन्यथा अगर (err)
			वापस err;
		अन्यथा
			results[attr_id] = attr;

		/* update offset */
		offset += FM10K_TLV_DWORD_LEN(*attr) * 4;

		/* move to next attribute */
		attr = &attr[FM10K_TLV_DWORD_LEN(*attr)];
	पूर्ण

	/* we should find ourselves at the end of the list */
	अगर (offset != len)
		वापस FM10K_ERR_PARAM;

	वापस 0;
पूर्ण

/**
 *  fm10k_tlv_msg_parse - Parses message header and calls function handler
 *  @hw: Poपूर्णांकer to hardware काष्ठाure
 *  @msg: Poपूर्णांकer to message
 *  @mbx: Poपूर्णांकer to mailbox inक्रमmation काष्ठाure
 *  @data: Poपूर्णांकer to message handler data काष्ठाure
 *
 *  This function should be the first function called upon receiving a
 *  message.  The handler will identअगरy the message type and call the correct
 *  handler क्रम the given message.  It will वापस the value from the function
 *  call on a recognized message type, otherwise it will वापस
 *  FM10K_NOT_IMPLEMENTED on an unrecognized type.
 **/
s32 fm10k_tlv_msg_parse(काष्ठा fm10k_hw *hw, u32 *msg,
			काष्ठा fm10k_mbx_info *mbx,
			स्थिर काष्ठा fm10k_msg_data *data)
अणु
	u32 *results[FM10K_TLV_RESULTS_MAX];
	u32 msg_id;
	s32 err;

	/* verअगरy poपूर्णांकer is not शून्य */
	अगर (!msg || !data)
		वापस FM10K_ERR_PARAM;

	/* verअगरy this is a message and not an attribute */
	अगर (!(*msg & (FM10K_TLV_FLAGS_MSG << FM10K_TLV_FLAGS_SHIFT)))
		वापस FM10K_ERR_PARAM;

	/* grab message ID */
	msg_id = *msg & FM10K_TLV_ID_MASK;

	जबतक (data->id < msg_id)
		data++;

	/* अगर we didn't find it then pass it up as an error */
	अगर (data->id != msg_id) अणु
		जबतक (data->id != FM10K_TLV_ERROR)
			data++;
	पूर्ण

	/* parse the attributes पूर्णांकo the results list */
	err = fm10k_tlv_attr_parse(msg, results, data->attr);
	अगर (err < 0)
		वापस err;

	वापस data->func(hw, results, mbx);
पूर्ण

/**
 *  fm10k_tlv_msg_error - Default handler क्रम unrecognized TLV message IDs
 *  @hw: Poपूर्णांकer to hardware काष्ठाure
 *  @results: Poपूर्णांकer array to message, results[0] is poपूर्णांकer to message
 *  @mbx: Unused mailbox poपूर्णांकer
 *
 *  This function is a शेष handler क्रम unrecognized messages.  At a
 *  a minimum it just indicates that the message requested was
 *  unimplemented.
 **/
s32 fm10k_tlv_msg_error(काष्ठा fm10k_hw __always_unused *hw,
			u32 __always_unused **results,
			काष्ठा fm10k_mbx_info __always_unused *mbx)
अणु
	वापस FM10K_NOT_IMPLEMENTED;
पूर्ण

अटल स्थिर अचिन्हित अक्षर test_str[] =	"fm10k";
अटल स्थिर अचिन्हित अक्षर test_mac[ETH_ALEN] = अणु 0x12, 0x34, 0x56,
						  0x78, 0x9a, 0xbc पूर्ण;
अटल स्थिर u16 test_vlan = 0x0FED;
अटल स्थिर u64 test_u64 = 0xfedcba9876543210ull;
अटल स्थिर u32 test_u32 = 0x87654321;
अटल स्थिर u16 test_u16 = 0x8765;
अटल स्थिर u8  test_u8  = 0x87;
अटल स्थिर s64 test_s64 = -0x123456789abcdef0ll;
अटल स्थिर s32 test_s32 = -0x1235678;
अटल स्थिर s16 test_s16 = -0x1234;
अटल स्थिर s8  test_s8  = -0x12;
अटल स्थिर __le32 test_le[2] = अणु cpu_to_le32(0x12345678),
				   cpu_to_le32(0x9abcdef0)पूर्ण;

/* The message below is meant to be used as a test message to demonstrate
 * how to use the TLV पूर्णांकerface and to test the types.  Normally this code
 * be compiled out by stripping the code wrapped in FM10K_TLV_TEST_MSG
 */
स्थिर काष्ठा fm10k_tlv_attr fm10k_tlv_msg_test_attr[] = अणु
	FM10K_TLV_ATTR_शून्य_STRING(FM10K_TEST_MSG_STRING, 80),
	FM10K_TLV_ATTR_MAC_ADDR(FM10K_TEST_MSG_MAC_ADDR),
	FM10K_TLV_ATTR_U8(FM10K_TEST_MSG_U8),
	FM10K_TLV_ATTR_U16(FM10K_TEST_MSG_U16),
	FM10K_TLV_ATTR_U32(FM10K_TEST_MSG_U32),
	FM10K_TLV_ATTR_U64(FM10K_TEST_MSG_U64),
	FM10K_TLV_ATTR_S8(FM10K_TEST_MSG_S8),
	FM10K_TLV_ATTR_S16(FM10K_TEST_MSG_S16),
	FM10K_TLV_ATTR_S32(FM10K_TEST_MSG_S32),
	FM10K_TLV_ATTR_S64(FM10K_TEST_MSG_S64),
	FM10K_TLV_ATTR_LE_STRUCT(FM10K_TEST_MSG_LE_STRUCT, 8),
	FM10K_TLV_ATTR_NESTED(FM10K_TEST_MSG_NESTED),
	FM10K_TLV_ATTR_S32(FM10K_TEST_MSG_RESULT),
	FM10K_TLV_ATTR_LAST
पूर्ण;

/**
 *  fm10k_tlv_msg_test_generate_data - Stuff message with data
 *  @msg: Poपूर्णांकer to message
 *  @attr_flags: List of flags indicating what attributes to add
 *
 *  This function is meant to load a message buffer with attribute data
 **/
अटल व्योम fm10k_tlv_msg_test_generate_data(u32 *msg, u32 attr_flags)
अणु
	अगर (attr_flags & BIT(FM10K_TEST_MSG_STRING))
		fm10k_tlv_attr_put_null_string(msg, FM10K_TEST_MSG_STRING,
					       test_str);
	अगर (attr_flags & BIT(FM10K_TEST_MSG_MAC_ADDR))
		fm10k_tlv_attr_put_mac_vlan(msg, FM10K_TEST_MSG_MAC_ADDR,
					    test_mac, test_vlan);
	अगर (attr_flags & BIT(FM10K_TEST_MSG_U8))
		fm10k_tlv_attr_put_u8(msg, FM10K_TEST_MSG_U8,  test_u8);
	अगर (attr_flags & BIT(FM10K_TEST_MSG_U16))
		fm10k_tlv_attr_put_u16(msg, FM10K_TEST_MSG_U16, test_u16);
	अगर (attr_flags & BIT(FM10K_TEST_MSG_U32))
		fm10k_tlv_attr_put_u32(msg, FM10K_TEST_MSG_U32, test_u32);
	अगर (attr_flags & BIT(FM10K_TEST_MSG_U64))
		fm10k_tlv_attr_put_u64(msg, FM10K_TEST_MSG_U64, test_u64);
	अगर (attr_flags & BIT(FM10K_TEST_MSG_S8))
		fm10k_tlv_attr_put_s8(msg, FM10K_TEST_MSG_S8,  test_s8);
	अगर (attr_flags & BIT(FM10K_TEST_MSG_S16))
		fm10k_tlv_attr_put_s16(msg, FM10K_TEST_MSG_S16, test_s16);
	अगर (attr_flags & BIT(FM10K_TEST_MSG_S32))
		fm10k_tlv_attr_put_s32(msg, FM10K_TEST_MSG_S32, test_s32);
	अगर (attr_flags & BIT(FM10K_TEST_MSG_S64))
		fm10k_tlv_attr_put_s64(msg, FM10K_TEST_MSG_S64, test_s64);
	अगर (attr_flags & BIT(FM10K_TEST_MSG_LE_STRUCT))
		fm10k_tlv_attr_put_le_काष्ठा(msg, FM10K_TEST_MSG_LE_STRUCT,
					     test_le, 8);
पूर्ण

/**
 *  fm10k_tlv_msg_test_create - Create a test message testing all attributes
 *  @msg: Poपूर्णांकer to message
 *  @attr_flags: List of flags indicating what attributes to add
 *
 *  This function is meant to load a message buffer with all attribute types
 *  including a nested attribute.
 **/
व्योम fm10k_tlv_msg_test_create(u32 *msg, u32 attr_flags)
अणु
	u32 *nest = शून्य;

	fm10k_tlv_msg_init(msg, FM10K_TLV_MSG_ID_TEST);

	fm10k_tlv_msg_test_generate_data(msg, attr_flags);

	/* check क्रम nested attributes */
	attr_flags >>= FM10K_TEST_MSG_NESTED;

	अगर (attr_flags) अणु
		nest = fm10k_tlv_attr_nest_start(msg, FM10K_TEST_MSG_NESTED);

		fm10k_tlv_msg_test_generate_data(nest, attr_flags);

		fm10k_tlv_attr_nest_stop(msg);
	पूर्ण
पूर्ण

/**
 *  fm10k_tlv_msg_test - Validate all results on test message receive
 *  @hw: Poपूर्णांकer to hardware काष्ठाure
 *  @results: Poपूर्णांकer array to attributes in the message
 *  @mbx: Poपूर्णांकer to mailbox inक्रमmation काष्ठाure
 *
 *  This function करोes a check to verअगरy all attributes match what the test
 *  message placed in the message buffer.  It is the शेष handler
 *  क्रम TLV test messages.
 **/
s32 fm10k_tlv_msg_test(काष्ठा fm10k_hw *hw, u32 **results,
		       काष्ठा fm10k_mbx_info *mbx)
अणु
	u32 *nest_results[FM10K_TLV_RESULTS_MAX];
	अचिन्हित अक्षर result_str[80];
	अचिन्हित अक्षर result_mac[ETH_ALEN];
	s32 err = 0;
	__le32 result_le[2];
	u16 result_vlan;
	u64 result_u64;
	u32 result_u32;
	u16 result_u16;
	u8  result_u8;
	s64 result_s64;
	s32 result_s32;
	s16 result_s16;
	s8  result_s8;
	u32 reply[3];

	/* retrieve results of a previous test */
	अगर (!!results[FM10K_TEST_MSG_RESULT])
		वापस fm10k_tlv_attr_get_s32(results[FM10K_TEST_MSG_RESULT],
					      &mbx->test_result);

parse_nested:
	अगर (!!results[FM10K_TEST_MSG_STRING]) अणु
		err = fm10k_tlv_attr_get_null_string(
					results[FM10K_TEST_MSG_STRING],
					result_str);
		अगर (!err && स_भेद(test_str, result_str, माप(test_str)))
			err = FM10K_ERR_INVALID_VALUE;
		अगर (err)
			जाओ report_result;
	पूर्ण
	अगर (!!results[FM10K_TEST_MSG_MAC_ADDR]) अणु
		err = fm10k_tlv_attr_get_mac_vlan(
					results[FM10K_TEST_MSG_MAC_ADDR],
					result_mac, &result_vlan);
		अगर (!err && !ether_addr_equal(test_mac, result_mac))
			err = FM10K_ERR_INVALID_VALUE;
		अगर (!err && test_vlan != result_vlan)
			err = FM10K_ERR_INVALID_VALUE;
		अगर (err)
			जाओ report_result;
	पूर्ण
	अगर (!!results[FM10K_TEST_MSG_U8]) अणु
		err = fm10k_tlv_attr_get_u8(results[FM10K_TEST_MSG_U8],
					    &result_u8);
		अगर (!err && test_u8 != result_u8)
			err = FM10K_ERR_INVALID_VALUE;
		अगर (err)
			जाओ report_result;
	पूर्ण
	अगर (!!results[FM10K_TEST_MSG_U16]) अणु
		err = fm10k_tlv_attr_get_u16(results[FM10K_TEST_MSG_U16],
					     &result_u16);
		अगर (!err && test_u16 != result_u16)
			err = FM10K_ERR_INVALID_VALUE;
		अगर (err)
			जाओ report_result;
	पूर्ण
	अगर (!!results[FM10K_TEST_MSG_U32]) अणु
		err = fm10k_tlv_attr_get_u32(results[FM10K_TEST_MSG_U32],
					     &result_u32);
		अगर (!err && test_u32 != result_u32)
			err = FM10K_ERR_INVALID_VALUE;
		अगर (err)
			जाओ report_result;
	पूर्ण
	अगर (!!results[FM10K_TEST_MSG_U64]) अणु
		err = fm10k_tlv_attr_get_u64(results[FM10K_TEST_MSG_U64],
					     &result_u64);
		अगर (!err && test_u64 != result_u64)
			err = FM10K_ERR_INVALID_VALUE;
		अगर (err)
			जाओ report_result;
	पूर्ण
	अगर (!!results[FM10K_TEST_MSG_S8]) अणु
		err = fm10k_tlv_attr_get_s8(results[FM10K_TEST_MSG_S8],
					    &result_s8);
		अगर (!err && test_s8 != result_s8)
			err = FM10K_ERR_INVALID_VALUE;
		अगर (err)
			जाओ report_result;
	पूर्ण
	अगर (!!results[FM10K_TEST_MSG_S16]) अणु
		err = fm10k_tlv_attr_get_s16(results[FM10K_TEST_MSG_S16],
					     &result_s16);
		अगर (!err && test_s16 != result_s16)
			err = FM10K_ERR_INVALID_VALUE;
		अगर (err)
			जाओ report_result;
	पूर्ण
	अगर (!!results[FM10K_TEST_MSG_S32]) अणु
		err = fm10k_tlv_attr_get_s32(results[FM10K_TEST_MSG_S32],
					     &result_s32);
		अगर (!err && test_s32 != result_s32)
			err = FM10K_ERR_INVALID_VALUE;
		अगर (err)
			जाओ report_result;
	पूर्ण
	अगर (!!results[FM10K_TEST_MSG_S64]) अणु
		err = fm10k_tlv_attr_get_s64(results[FM10K_TEST_MSG_S64],
					     &result_s64);
		अगर (!err && test_s64 != result_s64)
			err = FM10K_ERR_INVALID_VALUE;
		अगर (err)
			जाओ report_result;
	पूर्ण
	अगर (!!results[FM10K_TEST_MSG_LE_STRUCT]) अणु
		err = fm10k_tlv_attr_get_le_काष्ठा(
					results[FM10K_TEST_MSG_LE_STRUCT],
					result_le,
					माप(result_le));
		अगर (!err && स_भेद(test_le, result_le, माप(test_le)))
			err = FM10K_ERR_INVALID_VALUE;
		अगर (err)
			जाओ report_result;
	पूर्ण

	अगर (!!results[FM10K_TEST_MSG_NESTED]) अणु
		/* clear any poपूर्णांकers */
		स_रखो(nest_results, 0, माप(nest_results));

		/* parse the nested attributes पूर्णांकo the nest results list */
		err = fm10k_tlv_attr_parse(results[FM10K_TEST_MSG_NESTED],
					   nest_results,
					   fm10k_tlv_msg_test_attr);
		अगर (err)
			जाओ report_result;

		/* loop back through to the start */
		results = nest_results;
		जाओ parse_nested;
	पूर्ण

report_result:
	/* generate reply with test result */
	fm10k_tlv_msg_init(reply, FM10K_TLV_MSG_ID_TEST);
	fm10k_tlv_attr_put_s32(reply, FM10K_TEST_MSG_RESULT, err);

	/* load onto outgoing mailbox */
	वापस mbx->ops.enqueue_tx(hw, mbx, reply);
पूर्ण
