<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause) */
/* Copyright 2013-2016 Freescale Semiconductor Inc.
 * Copyright 2019 NXP
 */
#अगर_अघोषित _FSL_DPMAC_CMD_H
#घोषणा _FSL_DPMAC_CMD_H

/* DPMAC Version */
#घोषणा DPMAC_VER_MAJOR				4
#घोषणा DPMAC_VER_MINOR				4
#घोषणा DPMAC_CMD_BASE_VERSION			1
#घोषणा DPMAC_CMD_2ND_VERSION			2
#घोषणा DPMAC_CMD_ID_OFFSET			4

#घोषणा DPMAC_CMD(id)	(((id) << DPMAC_CMD_ID_OFFSET) | DPMAC_CMD_BASE_VERSION)
#घोषणा DPMAC_CMD_V2(id) (((id) << DPMAC_CMD_ID_OFFSET) | DPMAC_CMD_2ND_VERSION)

/* Command IDs */
#घोषणा DPMAC_CMDID_CLOSE		DPMAC_CMD(0x800)
#घोषणा DPMAC_CMDID_OPEN		DPMAC_CMD(0x80c)

#घोषणा DPMAC_CMDID_GET_ATTR		DPMAC_CMD(0x004)
#घोषणा DPMAC_CMDID_SET_LINK_STATE	DPMAC_CMD_V2(0x0c3)

#घोषणा DPMAC_CMDID_GET_COUNTER		DPMAC_CMD(0x0c4)

/* Macros क्रम accessing command fields smaller than 1byte */
#घोषणा DPMAC_MASK(field)        \
	GENMASK(DPMAC_##field##_SHIFT + DPMAC_##field##_SIZE - 1, \
		DPMAC_##field##_SHIFT)

#घोषणा dpmac_set_field(var, field, val) \
	((var) |= (((val) << DPMAC_##field##_SHIFT) & DPMAC_MASK(field)))
#घोषणा dpmac_get_field(var, field)      \
	(((var) & DPMAC_MASK(field)) >> DPMAC_##field##_SHIFT)

काष्ठा dpmac_cmd_खोलो अणु
	__le32 dpmac_id;
पूर्ण;

काष्ठा dpmac_rsp_get_attributes अणु
	u8 eth_अगर;
	u8 link_type;
	__le16 id;
	__le32 max_rate;
पूर्ण;

#घोषणा DPMAC_STATE_SIZE	1
#घोषणा DPMAC_STATE_SHIFT	0
#घोषणा DPMAC_STATE_VALID_SIZE	1
#घोषणा DPMAC_STATE_VALID_SHIFT	1

काष्ठा dpmac_cmd_set_link_state अणु
	__le64 options;
	__le32 rate;
	__le32 pad0;
	/* from lsb: up:1, state_valid:1 */
	u8 state;
	u8 pad1[7];
	__le64 supported;
	__le64 advertising;
पूर्ण;

काष्ठा dpmac_cmd_get_counter अणु
	u8 id;
पूर्ण;

काष्ठा dpmac_rsp_get_counter अणु
	__le64 pad;
	__le64 counter;
पूर्ण;

#पूर्ण_अगर /* _FSL_DPMAC_CMD_H */
