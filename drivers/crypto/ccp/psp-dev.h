<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * AMD Platक्रमm Security Processor (PSP) पूर्णांकerface driver
 *
 * Copyright (C) 2017-2019 Advanced Micro Devices, Inc.
 *
 * Author: Brijesh Singh <brijesh.singh@amd.com>
 */

#अगर_अघोषित __PSP_DEV_H__
#घोषणा __PSP_DEV_H__

#समावेश <linux/device.h>
#समावेश <linux/list.h>
#समावेश <linux/bits.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "sp-dev.h"

#घोषणा PSP_CMDRESP_RESP		BIT(31)
#घोषणा PSP_CMDRESP_ERR_MASK		0xffff

#घोषणा MAX_PSP_NAME_LEN		16

बाह्य काष्ठा psp_device *psp_master;

प्रकार व्योम (*psp_irq_handler_t)(पूर्णांक, व्योम *, अचिन्हित पूर्णांक);

काष्ठा psp_device अणु
	काष्ठा list_head entry;

	काष्ठा psp_vdata *vdata;
	अक्षर name[MAX_PSP_NAME_LEN];

	काष्ठा device *dev;
	काष्ठा sp_device *sp;

	व्योम __iomem *io_regs;

	psp_irq_handler_t sev_irq_handler;
	व्योम *sev_irq_data;

	psp_irq_handler_t tee_irq_handler;
	व्योम *tee_irq_data;

	व्योम *sev_data;
	व्योम *tee_data;
पूर्ण;

व्योम psp_set_sev_irq_handler(काष्ठा psp_device *psp, psp_irq_handler_t handler,
			     व्योम *data);
व्योम psp_clear_sev_irq_handler(काष्ठा psp_device *psp);

व्योम psp_set_tee_irq_handler(काष्ठा psp_device *psp, psp_irq_handler_t handler,
			     व्योम *data);
व्योम psp_clear_tee_irq_handler(काष्ठा psp_device *psp);

काष्ठा psp_device *psp_get_master_device(व्योम);

#पूर्ण_अगर /* __PSP_DEV_H */
