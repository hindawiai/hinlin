<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2018 MediaTek Inc.
 *
 */

#अगर_अघोषित __MTK_CMDQ_MAILBOX_H__
#घोषणा __MTK_CMDQ_MAILBOX_H__

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

#घोषणा CMDQ_INST_SIZE			8 /* inकाष्ठाion is 64-bit */
#घोषणा CMDQ_SUBSYS_SHIFT		16
#घोषणा CMDQ_OP_CODE_SHIFT		24
#घोषणा CMDQ_JUMP_PASS			CMDQ_INST_SIZE

#घोषणा CMDQ_WFE_UPDATE			BIT(31)
#घोषणा CMDQ_WFE_UPDATE_VALUE		BIT(16)
#घोषणा CMDQ_WFE_WAIT			BIT(15)
#घोषणा CMDQ_WFE_WAIT_VALUE		0x1

/*
 * WFE arg_b
 * bit 0-11: रुको value
 * bit 15: 1 - रुको, 0 - no रुको
 * bit 16-27: update value
 * bit 31: 1 - update, 0 - no update
 */
#घोषणा CMDQ_WFE_OPTION			(CMDQ_WFE_WAIT | CMDQ_WFE_WAIT_VALUE)

/** cmdq event maximum */
#घोषणा CMDQ_MAX_EVENT			0x3ff

/*
 * CMDQ_CODE_MASK:
 *   set ग_लिखो mask
 *   क्रमmat: op mask
 * CMDQ_CODE_WRITE:
 *   ग_लिखो value पूर्णांकo target रेजिस्टर
 *   क्रमmat: op subsys address value
 * CMDQ_CODE_JUMP:
 *   jump by offset
 *   क्रमmat: op offset
 * CMDQ_CODE_WFE:
 *   रुको क्रम event and clear
 *   it is just clear अगर no रुको
 *   क्रमmat: [रुको]  op event update:1 to_रुको:1 रुको:1
 *           [clear] op event update:1 to_रुको:0 रुको:0
 * CMDQ_CODE_EOC:
 *   end of command
 *   क्रमmat: op irq_flag
 */
क्रमागत cmdq_code अणु
	CMDQ_CODE_MASK = 0x02,
	CMDQ_CODE_WRITE = 0x04,
	CMDQ_CODE_POLL = 0x08,
	CMDQ_CODE_JUMP = 0x10,
	CMDQ_CODE_WFE = 0x20,
	CMDQ_CODE_EOC = 0x40,
	CMDQ_CODE_READ_S = 0x80,
	CMDQ_CODE_WRITE_S = 0x90,
	CMDQ_CODE_WRITE_S_MASK = 0x91,
	CMDQ_CODE_LOGIC = 0xa0,
पूर्ण;

क्रमागत cmdq_cb_status अणु
	CMDQ_CB_NORMAL = 0,
	CMDQ_CB_ERROR
पूर्ण;

काष्ठा cmdq_cb_data अणु
	क्रमागत cmdq_cb_status	sta;
	व्योम			*data;
पूर्ण;

प्रकार व्योम (*cmdq_async_flush_cb)(काष्ठा cmdq_cb_data data);

काष्ठा cmdq_task_cb अणु
	cmdq_async_flush_cb	cb;
	व्योम			*data;
पूर्ण;

काष्ठा cmdq_pkt अणु
	व्योम			*va_base;
	dma_addr_t		pa_base;
	माप_प्रकार			cmd_buf_size; /* command occupied size */
	माप_प्रकार			buf_size; /* real buffer size */
	काष्ठा cmdq_task_cb	cb;
	काष्ठा cmdq_task_cb	async_cb;
	व्योम			*cl;
पूर्ण;

u8 cmdq_get_shअगरt_pa(काष्ठा mbox_chan *chan);

#पूर्ण_अगर /* __MTK_CMDQ_MAILBOX_H__ */
