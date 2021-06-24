<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause) */
/*
 * Copyright 2013-2016 Freescale Semiconductor Inc.
 * Copyright 2016 NXP
 *
 */
#अगर_अघोषित _FSL_DPIO_CMD_H
#घोषणा _FSL_DPIO_CMD_H

/* DPIO Version */
#घोषणा DPIO_VER_MAJOR			4
#घोषणा DPIO_VER_MINOR			2

/* Command Versioning */

#घोषणा DPIO_CMD_ID_OFFSET		4
#घोषणा DPIO_CMD_BASE_VERSION		1

#घोषणा DPIO_CMD(id)	(((id) << DPIO_CMD_ID_OFFSET) | DPIO_CMD_BASE_VERSION)

/* Command IDs */
#घोषणा DPIO_CMDID_CLOSE				DPIO_CMD(0x800)
#घोषणा DPIO_CMDID_OPEN					DPIO_CMD(0x803)
#घोषणा DPIO_CMDID_GET_API_VERSION			DPIO_CMD(0xa03)
#घोषणा DPIO_CMDID_ENABLE				DPIO_CMD(0x002)
#घोषणा DPIO_CMDID_DISABLE				DPIO_CMD(0x003)
#घोषणा DPIO_CMDID_GET_ATTR				DPIO_CMD(0x004)
#घोषणा DPIO_CMDID_RESET				DPIO_CMD(0x005)
#घोषणा DPIO_CMDID_SET_STASHING_DEST			DPIO_CMD(0x120)

काष्ठा dpio_cmd_खोलो अणु
	__le32 dpio_id;
पूर्ण;

#घोषणा DPIO_CHANNEL_MODE_MASK		0x3

काष्ठा dpio_rsp_get_attr अणु
	/* cmd word 0 */
	__le32 id;
	__le16 qbman_portal_id;
	u8 num_priorities;
	u8 channel_mode;
	/* cmd word 1 */
	__le64 qbman_portal_ce_addr;
	/* cmd word 2 */
	__le64 qbman_portal_ci_addr;
	/* cmd word 3 */
	__le32 qbman_version;
पूर्ण;

काष्ठा dpio_stashing_dest अणु
	u8 sdest;
पूर्ण;

#पूर्ण_अगर /* _FSL_DPIO_CMD_H */
