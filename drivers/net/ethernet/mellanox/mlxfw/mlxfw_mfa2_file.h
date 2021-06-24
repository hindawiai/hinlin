<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/* Copyright (c) 2017-2019 Mellanox Technologies. All rights reserved */

#अगर_अघोषित _MLXFW_MFA2_खाता_H
#घोषणा _MLXFW_MFA2_खाता_H

#समावेश <linux/firmware.h>
#समावेश <linux/kernel.h>

काष्ठा mlxfw_mfa2_file अणु
	स्थिर काष्ठा firmware *fw;
	स्थिर काष्ठा mlxfw_mfa2_tlv *first_dev;
	u16 dev_count;
	स्थिर काष्ठा mlxfw_mfa2_tlv *first_component;
	u16 component_count;
	स्थिर व्योम *cb; /* components block */
	u32 cb_archive_size; /* size of compressed components block */
पूर्ण;

अटल अंतरभूत bool mlxfw_mfa2_valid_ptr(स्थिर काष्ठा mlxfw_mfa2_file *mfa2_file,
					स्थिर व्योम *ptr)
अणु
	स्थिर व्योम *valid_to = mfa2_file->fw->data + mfa2_file->fw->size;
	स्थिर व्योम *valid_from = mfa2_file->fw->data;

	वापस ptr > valid_from && ptr < valid_to;
पूर्ण

#पूर्ण_अगर
