<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/* Copyright (c) 2017-2019 Mellanox Technologies. All rights reserved */

#अगर_अघोषित _MLXFW_MFA2_H
#घोषणा _MLXFW_MFA2_H

#समावेश <linux/firmware.h>
#समावेश "mlxfw.h"

काष्ठा mlxfw_mfa2_component अणु
	u16 index;
	u32 data_size;
	u8 *data;
पूर्ण;

काष्ठा mlxfw_mfa2_file;

bool mlxfw_mfa2_check(स्थिर काष्ठा firmware *fw);

काष्ठा mlxfw_mfa2_file *mlxfw_mfa2_file_init(स्थिर काष्ठा firmware *fw);

पूर्णांक mlxfw_mfa2_file_component_count(स्थिर काष्ठा mlxfw_mfa2_file *mfa2_file,
				    स्थिर अक्षर *psid, u32 psid_size,
				    u32 *p_count);

काष्ठा mlxfw_mfa2_component *
mlxfw_mfa2_file_component_get(स्थिर काष्ठा mlxfw_mfa2_file *mfa2_file,
			      स्थिर अक्षर *psid, पूर्णांक psid_size,
			      पूर्णांक component_index);

व्योम mlxfw_mfa2_file_component_put(काष्ठा mlxfw_mfa2_component *component);

व्योम mlxfw_mfa2_file_fini(काष्ठा mlxfw_mfa2_file *mfa2_file);

#पूर्ण_अगर
