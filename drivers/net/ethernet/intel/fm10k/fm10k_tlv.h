<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2013 - 2019 Intel Corporation. */

#अगर_अघोषित _FM10K_TLV_H_
#घोषणा _FM10K_TLV_H_

/* क्रमward declaration */
काष्ठा fm10k_msg_data;

#समावेश "fm10k_type.h"

/* Message / Argument header क्रमmat
 *    3			  2		      1			  0
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |	     Length	   | Flags |	      Type / ID		   |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * The message header क्रमmat described here is used क्रम messages that are
 * passed between the PF and the VF.  To allow क्रम messages larger then
 * mailbox size we will provide a message with the above header and it
 * will be segmented and transported to the mailbox to the other side where
 * it is reassembled.  It contains the following fields:
 * Length: Length of the message in bytes excluding the message header
 * Flags: TBD
 * Type/ID: These will be the message/argument types we pass
 */
/* message data header */
#घोषणा FM10K_TLV_ID_SHIFT		0
#घोषणा FM10K_TLV_ID_SIZE		16
#घोषणा FM10K_TLV_ID_MASK		((1u << FM10K_TLV_ID_SIZE) - 1)
#घोषणा FM10K_TLV_FLAGS_SHIFT		16
#घोषणा FM10K_TLV_FLAGS_MSG		0x1
#घोषणा FM10K_TLV_FLAGS_SIZE		4
#घोषणा FM10K_TLV_LEN_SHIFT		20
#घोषणा FM10K_TLV_LEN_SIZE		12

#घोषणा FM10K_TLV_HDR_LEN		4ul
#घोषणा FM10K_TLV_LEN_ALIGN_MASK \
	((FM10K_TLV_HDR_LEN - 1) << FM10K_TLV_LEN_SHIFT)
#घोषणा FM10K_TLV_LEN_ALIGN(tlv) \
	(((tlv) + FM10K_TLV_LEN_ALIGN_MASK) & ~FM10K_TLV_LEN_ALIGN_MASK)
#घोषणा FM10K_TLV_DWORD_LEN(tlv) \
	((u16)((FM10K_TLV_LEN_ALIGN(tlv)) >> (FM10K_TLV_LEN_SHIFT + 2)) + 1)

#घोषणा FM10K_TLV_RESULTS_MAX		32

क्रमागत fm10k_tlv_type अणु
	FM10K_TLV_शून्य_STRING,
	FM10K_TLV_MAC_ADDR,
	FM10K_TLV_BOOL,
	FM10K_TLV_UNSIGNED,
	FM10K_TLV_SIGNED,
	FM10K_TLV_LE_STRUCT,
	FM10K_TLV_NESTED,
	FM10K_TLV_MAX_TYPE
पूर्ण;

#घोषणा FM10K_TLV_ERROR (~0u)

काष्ठा fm10k_tlv_attr अणु
	अचिन्हित पूर्णांक		id;
	क्रमागत fm10k_tlv_type	type;
	u16			len;
पूर्ण;

#घोषणा FM10K_TLV_ATTR_शून्य_STRING(id, len) अणु id, FM10K_TLV_शून्य_STRING, len पूर्ण
#घोषणा FM10K_TLV_ATTR_MAC_ADDR(id)	    अणु id, FM10K_TLV_MAC_ADDR, 6 पूर्ण
#घोषणा FM10K_TLV_ATTR_BOOL(id)		    अणु id, FM10K_TLV_BOOL, 0 पूर्ण
#घोषणा FM10K_TLV_ATTR_U8(id)		    अणु id, FM10K_TLV_UNSIGNED, 1 पूर्ण
#घोषणा FM10K_TLV_ATTR_U16(id)		    अणु id, FM10K_TLV_UNSIGNED, 2 पूर्ण
#घोषणा FM10K_TLV_ATTR_U32(id)		    अणु id, FM10K_TLV_UNSIGNED, 4 पूर्ण
#घोषणा FM10K_TLV_ATTR_U64(id)		    अणु id, FM10K_TLV_UNSIGNED, 8 पूर्ण
#घोषणा FM10K_TLV_ATTR_S8(id)		    अणु id, FM10K_TLV_SIGNED, 1 पूर्ण
#घोषणा FM10K_TLV_ATTR_S16(id)		    अणु id, FM10K_TLV_SIGNED, 2 पूर्ण
#घोषणा FM10K_TLV_ATTR_S32(id)		    अणु id, FM10K_TLV_SIGNED, 4 पूर्ण
#घोषणा FM10K_TLV_ATTR_S64(id)		    अणु id, FM10K_TLV_SIGNED, 8 पूर्ण
#घोषणा FM10K_TLV_ATTR_LE_STRUCT(id, len)   अणु id, FM10K_TLV_LE_STRUCT, len पूर्ण
#घोषणा FM10K_TLV_ATTR_NESTED(id)	    अणु id, FM10K_TLV_NESTED, 0 पूर्ण
#घोषणा FM10K_TLV_ATTR_LAST		    अणु FM10K_TLV_ERROR, 0, 0 पूर्ण

काष्ठा fm10k_msg_data अणु
	अचिन्हित पूर्णांक		    id;
	स्थिर काष्ठा fm10k_tlv_attr *attr;
	s32			    (*func)(काष्ठा fm10k_hw *, u32 **,
					    काष्ठा fm10k_mbx_info *);
पूर्ण;

#घोषणा FM10K_MSG_HANDLER(id, attr, func) अणु id, attr, func पूर्ण

s32 fm10k_tlv_msg_init(u32 *, u16);
s32 fm10k_tlv_attr_put_mac_vlan(u32 *, u16, स्थिर u8 *, u16);
s32 fm10k_tlv_attr_get_mac_vlan(u32 *, u8 *, u16 *);
s32 fm10k_tlv_attr_put_bool(u32 *, u16);
s32 fm10k_tlv_attr_put_value(u32 *, u16, s64, u32);
#घोषणा fm10k_tlv_attr_put_u8(msg, attr_id, val) \
		fm10k_tlv_attr_put_value(msg, attr_id, val, 1)
#घोषणा fm10k_tlv_attr_put_u16(msg, attr_id, val) \
		fm10k_tlv_attr_put_value(msg, attr_id, val, 2)
#घोषणा fm10k_tlv_attr_put_u32(msg, attr_id, val) \
		fm10k_tlv_attr_put_value(msg, attr_id, val, 4)
#घोषणा fm10k_tlv_attr_put_u64(msg, attr_id, val) \
		fm10k_tlv_attr_put_value(msg, attr_id, val, 8)
#घोषणा fm10k_tlv_attr_put_s8(msg, attr_id, val) \
		fm10k_tlv_attr_put_value(msg, attr_id, val, 1)
#घोषणा fm10k_tlv_attr_put_s16(msg, attr_id, val) \
		fm10k_tlv_attr_put_value(msg, attr_id, val, 2)
#घोषणा fm10k_tlv_attr_put_s32(msg, attr_id, val) \
		fm10k_tlv_attr_put_value(msg, attr_id, val, 4)
#घोषणा fm10k_tlv_attr_put_s64(msg, attr_id, val) \
		fm10k_tlv_attr_put_value(msg, attr_id, val, 8)
s32 fm10k_tlv_attr_get_value(u32 *, व्योम *, u32);
#घोषणा fm10k_tlv_attr_get_u8(attr, ptr) \
		fm10k_tlv_attr_get_value(attr, ptr, माप(u8))
#घोषणा fm10k_tlv_attr_get_u16(attr, ptr) \
		fm10k_tlv_attr_get_value(attr, ptr, माप(u16))
#घोषणा fm10k_tlv_attr_get_u32(attr, ptr) \
		fm10k_tlv_attr_get_value(attr, ptr, माप(u32))
#घोषणा fm10k_tlv_attr_get_u64(attr, ptr) \
		fm10k_tlv_attr_get_value(attr, ptr, माप(u64))
#घोषणा fm10k_tlv_attr_get_s8(attr, ptr) \
		fm10k_tlv_attr_get_value(attr, ptr, माप(s8))
#घोषणा fm10k_tlv_attr_get_s16(attr, ptr) \
		fm10k_tlv_attr_get_value(attr, ptr, माप(s16))
#घोषणा fm10k_tlv_attr_get_s32(attr, ptr) \
		fm10k_tlv_attr_get_value(attr, ptr, माप(s32))
#घोषणा fm10k_tlv_attr_get_s64(attr, ptr) \
		fm10k_tlv_attr_get_value(attr, ptr, माप(s64))
s32 fm10k_tlv_attr_put_le_काष्ठा(u32 *, u16, स्थिर व्योम *, u32);
s32 fm10k_tlv_attr_get_le_काष्ठा(u32 *, व्योम *, u32);
s32 fm10k_tlv_msg_parse(काष्ठा fm10k_hw *, u32 *, काष्ठा fm10k_mbx_info *,
			स्थिर काष्ठा fm10k_msg_data *);
s32 fm10k_tlv_msg_error(काष्ठा fm10k_hw *hw, u32 **results,
			काष्ठा fm10k_mbx_info *);

#घोषणा FM10K_TLV_MSG_ID_TEST	0

क्रमागत fm10k_tlv_test_attr_id अणु
	FM10K_TEST_MSG_UNSET,
	FM10K_TEST_MSG_STRING,
	FM10K_TEST_MSG_MAC_ADDR,
	FM10K_TEST_MSG_U8,
	FM10K_TEST_MSG_U16,
	FM10K_TEST_MSG_U32,
	FM10K_TEST_MSG_U64,
	FM10K_TEST_MSG_S8,
	FM10K_TEST_MSG_S16,
	FM10K_TEST_MSG_S32,
	FM10K_TEST_MSG_S64,
	FM10K_TEST_MSG_LE_STRUCT,
	FM10K_TEST_MSG_NESTED,
	FM10K_TEST_MSG_RESULT,
	FM10K_TEST_MSG_MAX
पूर्ण;

बाह्य स्थिर काष्ठा fm10k_tlv_attr fm10k_tlv_msg_test_attr[];
व्योम fm10k_tlv_msg_test_create(u32 *, u32);
s32 fm10k_tlv_msg_test(काष्ठा fm10k_hw *, u32 **, काष्ठा fm10k_mbx_info *);

#घोषणा FM10K_TLV_MSG_TEST_HANDLER(func) \
	FM10K_MSG_HANDLER(FM10K_TLV_MSG_ID_TEST, fm10k_tlv_msg_test_attr, func)
#घोषणा FM10K_TLV_MSG_ERROR_HANDLER(func) \
	FM10K_MSG_HANDLER(FM10K_TLV_ERROR, शून्य, func)
#पूर्ण_अगर /* _FM10K_MSG_H_ */
