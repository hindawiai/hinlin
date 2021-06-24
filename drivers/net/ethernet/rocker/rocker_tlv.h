<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * drivers/net/ethernet/rocker/rocker_tlv.h - Rocker चयन device driver
 * Copyright (c) 2014-2016 Jiri Pirko <jiri@mellanox.com>
 * Copyright (c) 2014 Scott Feldman <sfeldma@gmail.com>
 */

#अगर_अघोषित _ROCKER_TLV_H
#घोषणा _ROCKER_TLV_H

#समावेश <linux/types.h>

#समावेश "rocker_hw.h"
#समावेश "rocker.h"

#घोषणा ROCKER_TLV_ALIGNTO 8U
#घोषणा ROCKER_TLV_ALIGN(len) \
	(((len) + ROCKER_TLV_ALIGNTO - 1) & ~(ROCKER_TLV_ALIGNTO - 1))
#घोषणा ROCKER_TLV_HDRLEN ROCKER_TLV_ALIGN(माप(काष्ठा rocker_tlv))

/*  <------- ROCKER_TLV_HDRLEN -------> <--- ROCKER_TLV_ALIGN(payload) --->
 * +-----------------------------+- - -+- - - - - - - - - - - - - - -+- - -+
 * |             Header          | Pad |           Payload           | Pad |
 * |      (काष्ठा rocker_tlv)    | ing |                             | ing |
 * +-----------------------------+- - -+- - - - - - - - - - - - - - -+- - -+
 *  <--------------------------- tlv->len -------------------------->
 */

अटल अंतरभूत काष्ठा rocker_tlv *rocker_tlv_next(स्थिर काष्ठा rocker_tlv *tlv,
						 पूर्णांक *reमुख्यing)
अणु
	पूर्णांक totlen = ROCKER_TLV_ALIGN(tlv->len);

	*reमुख्यing -= totlen;
	वापस (काष्ठा rocker_tlv *) ((अक्षर *) tlv + totlen);
पूर्ण

अटल अंतरभूत पूर्णांक rocker_tlv_ok(स्थिर काष्ठा rocker_tlv *tlv, पूर्णांक reमुख्यing)
अणु
	वापस reमुख्यing >= (पूर्णांक) ROCKER_TLV_HDRLEN &&
	       tlv->len >= ROCKER_TLV_HDRLEN &&
	       tlv->len <= reमुख्यing;
पूर्ण

#घोषणा rocker_tlv_क्रम_each(pos, head, len, rem)	\
	क्रम (pos = head, rem = len;			\
	     rocker_tlv_ok(pos, rem);			\
	     pos = rocker_tlv_next(pos, &(rem)))

#घोषणा rocker_tlv_क्रम_each_nested(pos, tlv, rem)	\
	rocker_tlv_क्रम_each(pos, rocker_tlv_data(tlv),	\
			    rocker_tlv_len(tlv), rem)

अटल अंतरभूत पूर्णांक rocker_tlv_attr_size(पूर्णांक payload)
अणु
	वापस ROCKER_TLV_HDRLEN + payload;
पूर्ण

अटल अंतरभूत पूर्णांक rocker_tlv_total_size(पूर्णांक payload)
अणु
	वापस ROCKER_TLV_ALIGN(rocker_tlv_attr_size(payload));
पूर्ण

अटल अंतरभूत पूर्णांक rocker_tlv_padlen(पूर्णांक payload)
अणु
	वापस rocker_tlv_total_size(payload) - rocker_tlv_attr_size(payload);
पूर्ण

अटल अंतरभूत पूर्णांक rocker_tlv_type(स्थिर काष्ठा rocker_tlv *tlv)
अणु
	वापस tlv->type;
पूर्ण

अटल अंतरभूत व्योम *rocker_tlv_data(स्थिर काष्ठा rocker_tlv *tlv)
अणु
	वापस (अक्षर *) tlv + ROCKER_TLV_HDRLEN;
पूर्ण

अटल अंतरभूत पूर्णांक rocker_tlv_len(स्थिर काष्ठा rocker_tlv *tlv)
अणु
	वापस tlv->len - ROCKER_TLV_HDRLEN;
पूर्ण

अटल अंतरभूत u8 rocker_tlv_get_u8(स्थिर काष्ठा rocker_tlv *tlv)
अणु
	वापस *(u8 *) rocker_tlv_data(tlv);
पूर्ण

अटल अंतरभूत u16 rocker_tlv_get_u16(स्थिर काष्ठा rocker_tlv *tlv)
अणु
	वापस *(u16 *) rocker_tlv_data(tlv);
पूर्ण

अटल अंतरभूत __be16 rocker_tlv_get_be16(स्थिर काष्ठा rocker_tlv *tlv)
अणु
	वापस *(__be16 *) rocker_tlv_data(tlv);
पूर्ण

अटल अंतरभूत u32 rocker_tlv_get_u32(स्थिर काष्ठा rocker_tlv *tlv)
अणु
	वापस *(u32 *) rocker_tlv_data(tlv);
पूर्ण

अटल अंतरभूत u64 rocker_tlv_get_u64(स्थिर काष्ठा rocker_tlv *tlv)
अणु
	वापस *(u64 *) rocker_tlv_data(tlv);
पूर्ण

व्योम rocker_tlv_parse(स्थिर काष्ठा rocker_tlv **tb, पूर्णांक maxtype,
		      स्थिर अक्षर *buf, पूर्णांक buf_len);

अटल अंतरभूत व्योम rocker_tlv_parse_nested(स्थिर काष्ठा rocker_tlv **tb,
					   पूर्णांक maxtype,
					   स्थिर काष्ठा rocker_tlv *tlv)
अणु
	rocker_tlv_parse(tb, maxtype, rocker_tlv_data(tlv),
			 rocker_tlv_len(tlv));
पूर्ण

अटल अंतरभूत व्योम
rocker_tlv_parse_desc(स्थिर काष्ठा rocker_tlv **tb, पूर्णांक maxtype,
		      स्थिर काष्ठा rocker_desc_info *desc_info)
अणु
	rocker_tlv_parse(tb, maxtype, desc_info->data,
			 desc_info->desc->tlv_size);
पूर्ण

अटल अंतरभूत काष्ठा rocker_tlv *
rocker_tlv_start(काष्ठा rocker_desc_info *desc_info)
अणु
	वापस (काष्ठा rocker_tlv *) ((अक्षर *) desc_info->data +
					       desc_info->tlv_size);
पूर्ण

पूर्णांक rocker_tlv_put(काष्ठा rocker_desc_info *desc_info,
		   पूर्णांक attrtype, पूर्णांक attrlen, स्थिर व्योम *data);

अटल अंतरभूत पूर्णांक
rocker_tlv_put_u8(काष्ठा rocker_desc_info *desc_info, पूर्णांक attrtype, u8 value)
अणु
	u8 पंचांगp = value; /* work around GCC PR81715 */

	वापस rocker_tlv_put(desc_info, attrtype, माप(u8), &पंचांगp);
पूर्ण

अटल अंतरभूत पूर्णांक
rocker_tlv_put_u16(काष्ठा rocker_desc_info *desc_info, पूर्णांक attrtype, u16 value)
अणु
	u16 पंचांगp = value;

	वापस rocker_tlv_put(desc_info, attrtype, माप(u16), &पंचांगp);
पूर्ण

अटल अंतरभूत पूर्णांक
rocker_tlv_put_be16(काष्ठा rocker_desc_info *desc_info, पूर्णांक attrtype, __be16 value)
अणु
	__be16 पंचांगp = value;

	वापस rocker_tlv_put(desc_info, attrtype, माप(__be16), &पंचांगp);
पूर्ण

अटल अंतरभूत पूर्णांक
rocker_tlv_put_u32(काष्ठा rocker_desc_info *desc_info, पूर्णांक attrtype, u32 value)
अणु
	u32 पंचांगp = value;

	वापस rocker_tlv_put(desc_info, attrtype, माप(u32), &पंचांगp);
पूर्ण

अटल अंतरभूत पूर्णांक
rocker_tlv_put_be32(काष्ठा rocker_desc_info *desc_info, पूर्णांक attrtype, __be32 value)
अणु
	__be32 पंचांगp = value;

	वापस rocker_tlv_put(desc_info, attrtype, माप(__be32), &पंचांगp);
पूर्ण

अटल अंतरभूत पूर्णांक
rocker_tlv_put_u64(काष्ठा rocker_desc_info *desc_info, पूर्णांक attrtype, u64 value)
अणु
	u64 पंचांगp = value;

	वापस rocker_tlv_put(desc_info, attrtype, माप(u64), &पंचांगp);
पूर्ण

अटल अंतरभूत काष्ठा rocker_tlv *
rocker_tlv_nest_start(काष्ठा rocker_desc_info *desc_info, पूर्णांक attrtype)
अणु
	काष्ठा rocker_tlv *start = rocker_tlv_start(desc_info);

	अगर (rocker_tlv_put(desc_info, attrtype, 0, शून्य) < 0)
		वापस शून्य;

	वापस start;
पूर्ण

अटल अंतरभूत व्योम rocker_tlv_nest_end(काष्ठा rocker_desc_info *desc_info,
				       काष्ठा rocker_tlv *start)
अणु
	start->len = (अक्षर *) rocker_tlv_start(desc_info) - (अक्षर *) start;
पूर्ण

अटल अंतरभूत व्योम rocker_tlv_nest_cancel(काष्ठा rocker_desc_info *desc_info,
					  स्थिर काष्ठा rocker_tlv *start)
अणु
	desc_info->tlv_size = (स्थिर अक्षर *) start - desc_info->data;
पूर्ण

#पूर्ण_अगर
