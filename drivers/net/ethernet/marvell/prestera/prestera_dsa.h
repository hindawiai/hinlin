<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/* Copyright (c) 2020 Marvell International Ltd. All rights reserved. */

#अगर_अघोषित __PRESTERA_DSA_H_
#घोषणा __PRESTERA_DSA_H_

#समावेश <linux/types.h>

#घोषणा PRESTERA_DSA_HLEN	16

क्रमागत prestera_dsa_cmd अणु
	/* DSA command is "To CPU" */
	PRESTERA_DSA_CMD_TO_CPU = 0,

	/* DSA command is "From CPU" */
	PRESTERA_DSA_CMD_FROM_CPU,
पूर्ण;

काष्ठा prestera_dsa_vlan अणु
	u16 vid;
	u8 vpt;
	u8 cfi_bit;
	bool is_tagged;
पूर्ण;

काष्ठा prestera_dsa अणु
	काष्ठा prestera_dsa_vlan vlan;
	u32 hw_dev_num;
	u32 port_num;
पूर्ण;

पूर्णांक prestera_dsa_parse(काष्ठा prestera_dsa *dsa, स्थिर u8 *dsa_buf);
पूर्णांक prestera_dsa_build(स्थिर काष्ठा prestera_dsa *dsa, u8 *dsa_buf);

#पूर्ण_अगर /* _PRESTERA_DSA_H_ */
