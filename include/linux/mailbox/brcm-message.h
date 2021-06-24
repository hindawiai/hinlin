<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  Copyright (C) 2016 Broadcom
 *
 * Common header क्रम Broadcom mailbox messages which is shared across
 * Broadcom SoCs and Broadcom mailbox client drivers.
 */

#अगर_अघोषित _LINUX_BRCM_MESSAGE_H_
#घोषणा _LINUX_BRCM_MESSAGE_H_

#समावेश <linux/scatterlist.h>

क्रमागत brcm_message_type अणु
	BRCM_MESSAGE_UNKNOWN = 0,
	BRCM_MESSAGE_BATCH,
	BRCM_MESSAGE_SPU,
	BRCM_MESSAGE_SBA,
	BRCM_MESSAGE_MAX,
पूर्ण;

काष्ठा brcm_sba_command अणु
	u64 cmd;
	u64 *cmd_dma;
	dma_addr_t cmd_dma_addr;
#घोषणा BRCM_SBA_CMD_TYPE_A		BIT(0)
#घोषणा BRCM_SBA_CMD_TYPE_B		BIT(1)
#घोषणा BRCM_SBA_CMD_TYPE_C		BIT(2)
#घोषणा BRCM_SBA_CMD_HAS_RESP		BIT(3)
#घोषणा BRCM_SBA_CMD_HAS_OUTPUT		BIT(4)
	u64 flags;
	dma_addr_t resp;
	माप_प्रकार resp_len;
	dma_addr_t data;
	माप_प्रकार data_len;
पूर्ण;

काष्ठा brcm_message अणु
	क्रमागत brcm_message_type type;
	जोड़ अणु
		काष्ठा अणु
			काष्ठा brcm_message *msgs;
			अचिन्हित पूर्णांक msgs_queued;
			अचिन्हित पूर्णांक msgs_count;
		पूर्ण batch;
		काष्ठा अणु
			काष्ठा scatterlist *src;
			काष्ठा scatterlist *dst;
		पूर्ण spu;
		काष्ठा अणु
			काष्ठा brcm_sba_command *cmds;
			अचिन्हित पूर्णांक cmds_count;
		पूर्ण sba;
	पूर्ण;
	व्योम *ctx;
	पूर्णांक error;
पूर्ण;

#पूर्ण_अगर /* _LINUX_BRCM_MESSAGE_H_ */
