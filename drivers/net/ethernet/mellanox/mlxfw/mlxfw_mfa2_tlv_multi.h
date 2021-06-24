<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/* Copyright (c) 2017-2019 Mellanox Technologies. All rights reserved */

#अगर_अघोषित _MLXFW_MFA2_TLV_MULTI_H
#घोषणा _MLXFW_MFA2_TLV_MULTI_H

#समावेश "mlxfw_mfa2_tlv.h"
#समावेश "mlxfw_mfa2_format.h"
#समावेश "mlxfw_mfa2_file.h"

स्थिर काष्ठा mlxfw_mfa2_tlv *
mlxfw_mfa2_tlv_multi_child(स्थिर काष्ठा mlxfw_mfa2_file *mfa2_file,
			   स्थिर काष्ठा mlxfw_mfa2_tlv_multi *multi);

स्थिर काष्ठा mlxfw_mfa2_tlv *
mlxfw_mfa2_tlv_next(स्थिर काष्ठा mlxfw_mfa2_file *mfa2_file,
		    स्थिर काष्ठा mlxfw_mfa2_tlv *tlv);

स्थिर काष्ठा mlxfw_mfa2_tlv *
mlxfw_mfa2_tlv_advance(स्थिर काष्ठा mlxfw_mfa2_file *mfa2_file,
		       स्थिर काष्ठा mlxfw_mfa2_tlv *from_tlv, u16 count);

स्थिर काष्ठा mlxfw_mfa2_tlv *
mlxfw_mfa2_tlv_multi_child_find(स्थिर काष्ठा mlxfw_mfa2_file *mfa2_file,
				स्थिर काष्ठा mlxfw_mfa2_tlv_multi *multi,
				क्रमागत mlxfw_mfa2_tlv_type type, u16 index);

पूर्णांक mlxfw_mfa2_tlv_multi_child_count(स्थिर काष्ठा mlxfw_mfa2_file *mfa2_file,
				     स्थिर काष्ठा mlxfw_mfa2_tlv_multi *multi,
				     क्रमागत mlxfw_mfa2_tlv_type type,
				     u16 *p_count);

#घोषणा mlxfw_mfa2_tlv_क्रमeach(mfa2_file, tlv, idx, from_tlv, count) \
	क्रम (idx = 0, tlv = from_tlv; idx < (count); \
	     idx++, tlv = mlxfw_mfa2_tlv_next(mfa2_file, tlv))

#घोषणा mlxfw_mfa2_tlv_multi_क्रमeach(mfa2_file, tlv, idx, multi) \
	mlxfw_mfa2_tlv_क्रमeach(mfa2_file, tlv, idx, \
			       mlxfw_mfa2_tlv_multi_child(mfa2_file, multi), \
			       be16_to_cpu(multi->num_extensions) + 1)
#पूर्ण_अगर
