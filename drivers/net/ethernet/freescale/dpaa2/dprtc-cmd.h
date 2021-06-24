<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright 2013-2016 Freescale Semiconductor Inc.
 * Copyright 2016-2018 NXP
 */

#अगर_अघोषित _FSL_DPRTC_CMD_H
#घोषणा _FSL_DPRTC_CMD_H

/* Command versioning */
#घोषणा DPRTC_CMD_BASE_VERSION		1
#घोषणा DPRTC_CMD_VERSION_2		2
#घोषणा DPRTC_CMD_ID_OFFSET		4

#घोषणा DPRTC_CMD(id)	(((id) << DPRTC_CMD_ID_OFFSET) | DPRTC_CMD_BASE_VERSION)
#घोषणा DPRTC_CMD_V2(id) (((id) << DPRTC_CMD_ID_OFFSET) | DPRTC_CMD_VERSION_2)

/* Command IDs */
#घोषणा DPRTC_CMDID_CLOSE			DPRTC_CMD(0x800)
#घोषणा DPRTC_CMDID_OPEN			DPRTC_CMD(0x810)

#घोषणा DPRTC_CMDID_SET_IRQ_ENABLE		DPRTC_CMD(0x012)
#घोषणा DPRTC_CMDID_GET_IRQ_ENABLE		DPRTC_CMD(0x013)
#घोषणा DPRTC_CMDID_SET_IRQ_MASK		DPRTC_CMD_V2(0x014)
#घोषणा DPRTC_CMDID_GET_IRQ_MASK		DPRTC_CMD(0x015)
#घोषणा DPRTC_CMDID_GET_IRQ_STATUS		DPRTC_CMD(0x016)
#घोषणा DPRTC_CMDID_CLEAR_IRQ_STATUS		DPRTC_CMD(0x017)

#आशय pack(push, 1)
काष्ठा dprtc_cmd_खोलो अणु
	__le32 dprtc_id;
पूर्ण;

काष्ठा dprtc_cmd_get_irq अणु
	__le32 pad;
	u8 irq_index;
पूर्ण;

काष्ठा dprtc_cmd_set_irq_enable अणु
	u8 en;
	u8 pad[3];
	u8 irq_index;
पूर्ण;

काष्ठा dprtc_rsp_get_irq_enable अणु
	u8 en;
पूर्ण;

काष्ठा dprtc_cmd_set_irq_mask अणु
	__le32 mask;
	u8 irq_index;
पूर्ण;

काष्ठा dprtc_rsp_get_irq_mask अणु
	__le32 mask;
पूर्ण;

काष्ठा dprtc_cmd_get_irq_status अणु
	__le32 status;
	u8 irq_index;
पूर्ण;

काष्ठा dprtc_rsp_get_irq_status अणु
	__le32 status;
पूर्ण;

काष्ठा dprtc_cmd_clear_irq_status अणु
	__le32 status;
	u8 irq_index;
पूर्ण;

#आशय pack(pop)

#पूर्ण_अगर /* _FSL_DPRTC_CMD_H */
