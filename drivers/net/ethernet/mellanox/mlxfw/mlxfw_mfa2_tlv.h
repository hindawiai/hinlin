<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/* Copyright (c) 2017-2019 Mellanox Technologies. All rights reserved */

#अगर_अघोषित _MLXFW_MFA2_TLV_H
#घोषणा _MLXFW_MFA2_TLV_H

#समावेश <linux/kernel.h>
#समावेश "mlxfw_mfa2_file.h"

काष्ठा mlxfw_mfa2_tlv अणु
	u8 version;
	u8 type;
	__be16 len;
	u8 data[];
पूर्ण __packed;

अटल अंतरभूत स्थिर काष्ठा mlxfw_mfa2_tlv *
mlxfw_mfa2_tlv_get(स्थिर काष्ठा mlxfw_mfa2_file *mfa2_file, स्थिर व्योम *ptr)
अणु
	अगर (!mlxfw_mfa2_valid_ptr(mfa2_file, ptr) ||
	    !mlxfw_mfa2_valid_ptr(mfa2_file, ptr + माप(काष्ठा mlxfw_mfa2_tlv)))
		वापस शून्य;
	वापस ptr;
पूर्ण

अटल अंतरभूत स्थिर व्योम *
mlxfw_mfa2_tlv_payload_get(स्थिर काष्ठा mlxfw_mfa2_file *mfa2_file,
			   स्थिर काष्ठा mlxfw_mfa2_tlv *tlv, u8 payload_type,
			   माप_प्रकार payload_size, bool varsize)
अणु
	व्योम *tlv_top;

	tlv_top = (व्योम *) tlv + be16_to_cpu(tlv->len) - 1;
	अगर (!mlxfw_mfa2_valid_ptr(mfa2_file, tlv) ||
	    !mlxfw_mfa2_valid_ptr(mfa2_file, tlv_top))
		वापस शून्य;
	अगर (tlv->type != payload_type)
		वापस शून्य;
	अगर (varsize && (be16_to_cpu(tlv->len) < payload_size))
		वापस शून्य;
	अगर (!varsize && (be16_to_cpu(tlv->len) != payload_size))
		वापस शून्य;

	वापस tlv->data;
पूर्ण

#घोषणा MLXFW_MFA2_TLV(name, payload_type, tlv_type)			       \
अटल अंतरभूत स्थिर payload_type *					       \
mlxfw_mfa2_tlv_ ## name ## _get(स्थिर काष्ठा mlxfw_mfa2_file *mfa2_file,       \
				स्थिर काष्ठा mlxfw_mfa2_tlv *tlv)	       \
अणु									       \
	वापस mlxfw_mfa2_tlv_payload_get(mfa2_file, tlv,		       \
					  tlv_type, माप(payload_type),      \
					  false);			       \
पूर्ण

#घोषणा MLXFW_MFA2_TLV_VARSIZE(name, payload_type, tlv_type)		       \
अटल अंतरभूत स्थिर payload_type *					       \
mlxfw_mfa2_tlv_ ## name ## _get(स्थिर काष्ठा mlxfw_mfa2_file *mfa2_file,       \
				स्थिर काष्ठा mlxfw_mfa2_tlv *tlv)	       \
अणु									       \
	वापस mlxfw_mfa2_tlv_payload_get(mfa2_file, tlv,		       \
					  tlv_type, माप(payload_type),      \
					  true);			       \
पूर्ण

#पूर्ण_अगर
