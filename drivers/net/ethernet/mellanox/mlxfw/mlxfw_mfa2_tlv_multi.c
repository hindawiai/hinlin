<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/* Copyright (c) 2017-2019 Mellanox Technologies. All rights reserved */

#घोषणा pr_fmt(fmt) "MFA2: " fmt

#समावेश "mlxfw_mfa2_tlv_multi.h"
#समावेश <uapi/linux/netlink.h>

#घोषणा MLXFW_MFA2_TLV_TOTAL_SIZE(tlv) \
	NLA_ALIGN(माप(*(tlv)) + be16_to_cpu((tlv)->len))

स्थिर काष्ठा mlxfw_mfa2_tlv *
mlxfw_mfa2_tlv_multi_child(स्थिर काष्ठा mlxfw_mfa2_file *mfa2_file,
			   स्थिर काष्ठा mlxfw_mfa2_tlv_multi *multi)
अणु
	माप_प्रकार multi_len;

	multi_len = NLA_ALIGN(माप(काष्ठा mlxfw_mfa2_tlv_multi));
	वापस mlxfw_mfa2_tlv_get(mfa2_file, (व्योम *) multi + multi_len);
पूर्ण

स्थिर काष्ठा mlxfw_mfa2_tlv *
mlxfw_mfa2_tlv_next(स्थिर काष्ठा mlxfw_mfa2_file *mfa2_file,
		    स्थिर काष्ठा mlxfw_mfa2_tlv *tlv)
अणु
	स्थिर काष्ठा mlxfw_mfa2_tlv_multi *multi;
	u16 tlv_len;
	व्योम *next;

	tlv_len = MLXFW_MFA2_TLV_TOTAL_SIZE(tlv);

	अगर (tlv->type == MLXFW_MFA2_TLV_MULTI_PART) अणु
		multi = mlxfw_mfa2_tlv_multi_get(mfa2_file, tlv);
		tlv_len = NLA_ALIGN(tlv_len + be16_to_cpu(multi->total_len));
	पूर्ण

	next = (व्योम *) tlv + tlv_len;
	वापस mlxfw_mfa2_tlv_get(mfa2_file, next);
पूर्ण

स्थिर काष्ठा mlxfw_mfa2_tlv *
mlxfw_mfa2_tlv_advance(स्थिर काष्ठा mlxfw_mfa2_file *mfa2_file,
		       स्थिर काष्ठा mlxfw_mfa2_tlv *from_tlv, u16 count)
अणु
	स्थिर काष्ठा mlxfw_mfa2_tlv *tlv;
	u16 idx;

	mlxfw_mfa2_tlv_क्रमeach(mfa2_file, tlv, idx, from_tlv, count)
		अगर (!tlv)
			वापस शून्य;
	वापस tlv;
पूर्ण

स्थिर काष्ठा mlxfw_mfa2_tlv *
mlxfw_mfa2_tlv_multi_child_find(स्थिर काष्ठा mlxfw_mfa2_file *mfa2_file,
				स्थिर काष्ठा mlxfw_mfa2_tlv_multi *multi,
				क्रमागत mlxfw_mfa2_tlv_type type, u16 index)
अणु
	स्थिर काष्ठा mlxfw_mfa2_tlv *tlv;
	u16 skip = 0;
	u16 idx;

	mlxfw_mfa2_tlv_multi_क्रमeach(mfa2_file, tlv, idx, multi) अणु
		अगर (!tlv) अणु
			pr_err("TLV parsing error\n");
			वापस शून्य;
		पूर्ण
		अगर (tlv->type == type)
			अगर (skip++ == index)
				वापस tlv;
	पूर्ण
	वापस शून्य;
पूर्ण

पूर्णांक mlxfw_mfa2_tlv_multi_child_count(स्थिर काष्ठा mlxfw_mfa2_file *mfa2_file,
				     स्थिर काष्ठा mlxfw_mfa2_tlv_multi *multi,
				     क्रमागत mlxfw_mfa2_tlv_type type,
				     u16 *p_count)
अणु
	स्थिर काष्ठा mlxfw_mfa2_tlv *tlv;
	u16 count = 0;
	u16 idx;

	mlxfw_mfa2_tlv_multi_क्रमeach(mfa2_file, tlv, idx, multi) अणु
		अगर (!tlv) अणु
			pr_err("TLV parsing error\n");
			वापस -EINVAL;
		पूर्ण

		अगर (tlv->type == type)
			count++;
	पूर्ण
	*p_count = count;
	वापस 0;
पूर्ण
