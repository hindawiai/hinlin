<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * AMD Platक्रमm Security Processor (PSP) पूर्णांकerface driver
 *
 * Copyright (C) 2017-2019 Advanced Micro Devices, Inc.
 *
 * Author: Brijesh Singh <brijesh.singh@amd.com>
 */

#अगर_अघोषित __SEV_DEV_H__
#घोषणा __SEV_DEV_H__

#समावेश <linux/device.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mutex.h>
#समावेश <linux/list.h>
#समावेश <linux/रुको.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/hw_अक्रमom.h>
#समावेश <linux/bitops.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqवापस.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/psp-sev.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/capability.h>

#घोषणा SEV_CMD_COMPLETE		BIT(1)
#घोषणा SEV_CMDRESP_CMD_SHIFT		16
#घोषणा SEV_CMDRESP_IOC			BIT(0)

काष्ठा sev_misc_dev अणु
	काष्ठा kref refcount;
	काष्ठा miscdevice misc;
पूर्ण;

काष्ठा sev_device अणु
	काष्ठा device *dev;
	काष्ठा psp_device *psp;

	व्योम __iomem *io_regs;

	काष्ठा sev_vdata *vdata;

	पूर्णांक state;
	अचिन्हित पूर्णांक पूर्णांक_rcvd;
	रुको_queue_head_t पूर्णांक_queue;
	काष्ठा sev_misc_dev *misc;

	u8 api_major;
	u8 api_minor;
	u8 build;

	व्योम *cmd_buf;
पूर्ण;

पूर्णांक sev_dev_init(काष्ठा psp_device *psp);
व्योम sev_dev_destroy(काष्ठा psp_device *psp);

व्योम sev_pci_init(व्योम);
व्योम sev_pci_निकास(व्योम);

#पूर्ण_अगर /* __SEV_DEV_H */
