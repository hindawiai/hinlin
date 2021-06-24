<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * drivers/net/ethernet/rocker/rocker_tlv.c - Rocker चयन device driver
 * Copyright (c) 2014-2016 Jiri Pirko <jiri@mellanox.com>
 * Copyright (c) 2014 Scott Feldman <sfeldma@gmail.com>
 */

#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>

#समावेश "rocker_hw.h"
#समावेश "rocker_tlv.h"

व्योम rocker_tlv_parse(स्थिर काष्ठा rocker_tlv **tb, पूर्णांक maxtype,
		      स्थिर अक्षर *buf, पूर्णांक buf_len)
अणु
	स्थिर काष्ठा rocker_tlv *tlv;
	स्थिर काष्ठा rocker_tlv *head = (स्थिर काष्ठा rocker_tlv *) buf;
	पूर्णांक rem;

	स_रखो(tb, 0, माप(काष्ठा rocker_tlv *) * (maxtype + 1));

	rocker_tlv_क्रम_each(tlv, head, buf_len, rem) अणु
		u32 type = rocker_tlv_type(tlv);

		अगर (type > 0 && type <= maxtype)
			tb[type] = tlv;
	पूर्ण
पूर्ण

पूर्णांक rocker_tlv_put(काष्ठा rocker_desc_info *desc_info,
		   पूर्णांक attrtype, पूर्णांक attrlen, स्थिर व्योम *data)
अणु
	पूर्णांक tail_room = desc_info->data_size - desc_info->tlv_size;
	पूर्णांक total_size = rocker_tlv_total_size(attrlen);
	काष्ठा rocker_tlv *tlv;

	अगर (unlikely(tail_room < total_size))
		वापस -EMSGSIZE;

	tlv = rocker_tlv_start(desc_info);
	desc_info->tlv_size += total_size;
	tlv->type = attrtype;
	tlv->len = rocker_tlv_attr_size(attrlen);
	स_नकल(rocker_tlv_data(tlv), data, attrlen);
	स_रखो((अक्षर *) tlv + tlv->len, 0, rocker_tlv_padlen(attrlen));
	वापस 0;
पूर्ण
