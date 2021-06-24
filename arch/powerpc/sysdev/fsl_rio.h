<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Freescale MPC85xx/MPC86xx RapidIO support
 *
 * Copyright 2009 Sysgo AG
 * Thomas Moll <thomas.moll@sysgo.com>
 * - fixed मुख्यtenance access routines, check क्रम aligned access
 *
 * Copyright 2009 Integrated Device Technology, Inc.
 * Alex Bounine <alexandre.bounine@idt.com>
 * - Added Port-Write message handling
 * - Added Machine Check exception handling
 *
 * Copyright (C) 2007, 2008, 2010, 2011 Freescale Semiconductor, Inc.
 * Zhang Wei <wei.zhang@मुक्तscale.com>
 * Lian Minghuan-B31939 <Minghuan.Lian@मुक्तscale.com>
 * Liu Gang <Gang.Liu@मुक्तscale.com>
 *
 * Copyright 2005 MontaVista Software, Inc.
 * Matt Porter <mporter@kernel.crashing.org>
 */

#अगर_अघोषित __FSL_RIO_H
#घोषणा __FSL_RIO_H

#समावेश <linux/rपन.स>
#समावेश <linux/rio_drv.h>
#समावेश <linux/kfअगरo.h>

#घोषणा RIO_REGS_WIN(mport)	(((काष्ठा rio_priv *)(mport->priv))->regs_win)

#घोषणा RIO_MAINT_WIN_SIZE	0x400000
#घोषणा RIO_LTLEDCSR		0x0608

#घोषणा DOORBELL_ROWAR_EN	0x80000000
#घोषणा DOORBELL_ROWAR_TFLOWLV	0x08000000 /* highest priority level */
#घोषणा DOORBELL_ROWAR_PCI	0x02000000 /* PCI winकरोw */
#घोषणा DOORBELL_ROWAR_NREAD	0x00040000 /* NREAD */
#घोषणा DOORBELL_ROWAR_MAINTRD	0x00070000  /* मुख्यtenance पढ़ो */
#घोषणा DOORBELL_ROWAR_RES	0x00002000 /* wrtpy: reserved */
#घोषणा DOORBELL_ROWAR_MAINTWD	0x00007000
#घोषणा DOORBELL_ROWAR_SIZE	0x0000000b /* winकरोw size is 4k */

#घोषणा RIO_ATMU_REGS_PORT1_OFFSET	0x10c00
#घोषणा RIO_ATMU_REGS_PORT2_OFFSET	0x10e00
#घोषणा RIO_S_DBELL_REGS_OFFSET	0x13400
#घोषणा RIO_S_PW_REGS_OFFSET	0x134e0
#घोषणा RIO_ATMU_REGS_DBELL_OFFSET	0x10C40
#घोषणा RIO_INB_ATMU_REGS_PORT1_OFFSET 0x10d60
#घोषणा RIO_INB_ATMU_REGS_PORT2_OFFSET 0x10f60

#घोषणा MAX_MSG_UNIT_NUM	2
#घोषणा MAX_PORT_NUM		4
#घोषणा RIO_INB_ATMU_COUNT	4

काष्ठा rio_aपंचांगu_regs अणु
	 u32 rowtar;
	 u32 rowtear;
	 u32 rowbar;
	 u32 pad1;
	 u32 rowar;
	 u32 pad2[3];
पूर्ण;

काष्ठा rio_inb_aपंचांगu_regs अणु
	u32 riwtar;
	u32 pad1;
	u32 riwbar;
	u32 pad2;
	u32 riwar;
	u32 pad3[3];
पूर्ण;

काष्ठा rio_dbell_ring अणु
	व्योम *virt;
	dma_addr_t phys;
पूर्ण;

काष्ठा rio_port_ग_लिखो_msg अणु
	 व्योम *virt;
	 dma_addr_t phys;
	 u32 msg_count;
	 u32 err_count;
	 u32 discard_count;
पूर्ण;

काष्ठा fsl_rio_dbell अणु
	काष्ठा rio_mport *mport[MAX_PORT_NUM];
	काष्ठा device *dev;
	काष्ठा rio_dbell_regs __iomem *dbell_regs;
	काष्ठा rio_dbell_ring dbell_ring;
	पूर्णांक bellirq;
पूर्ण;

काष्ठा fsl_rio_pw अणु
	काष्ठा rio_mport *mport[MAX_PORT_NUM];
	काष्ठा device *dev;
	काष्ठा rio_pw_regs __iomem *pw_regs;
	काष्ठा rio_port_ग_लिखो_msg port_ग_लिखो_msg;
	पूर्णांक pwirq;
	काष्ठा work_काष्ठा pw_work;
	काष्ठा kfअगरo pw_fअगरo;
	spinlock_t pw_fअगरo_lock;
पूर्ण;

काष्ठा rio_priv अणु
	काष्ठा device *dev;
	व्योम __iomem *regs_win;
	काष्ठा rio_aपंचांगu_regs __iomem *aपंचांगu_regs;
	काष्ठा rio_aपंचांगu_regs __iomem *मुख्यt_aपंचांगu_regs;
	काष्ठा rio_inb_aपंचांगu_regs __iomem *inb_aपंचांगu_regs;
	व्योम __iomem *मुख्यt_win;
	व्योम *rmm_handle; /* RapidIO message manager(unit) Handle */
पूर्ण;

बाह्य व्योम __iomem *rio_regs_win;
बाह्य व्योम __iomem *rmu_regs_win;

बाह्य resource_माप_प्रकार rio_law_start;

बाह्य काष्ठा fsl_rio_dbell *dbell;
बाह्य काष्ठा fsl_rio_pw *pw;

बाह्य पूर्णांक fsl_rio_setup_rmu(काष्ठा rio_mport *mport,
	काष्ठा device_node *node);
बाह्य पूर्णांक fsl_rio_port_ग_लिखो_init(काष्ठा fsl_rio_pw *pw);
बाह्य पूर्णांक fsl_rio_pw_enable(काष्ठा rio_mport *mport, पूर्णांक enable);
बाह्य व्योम fsl_rio_port_error_handler(पूर्णांक offset);
बाह्य पूर्णांक fsl_rio_करोorbell_init(काष्ठा fsl_rio_dbell *dbell);

बाह्य पूर्णांक fsl_rio_करोorbell_send(काष्ठा rio_mport *mport,
				पूर्णांक index, u16 destid, u16 data);
बाह्य पूर्णांक fsl_add_outb_message(काष्ठा rio_mport *mport,
	काष्ठा rio_dev *rdev,
	पूर्णांक mbox, व्योम *buffer, माप_प्रकार len);
बाह्य पूर्णांक fsl_खोलो_outb_mbox(काष्ठा rio_mport *mport,
	व्योम *dev_id, पूर्णांक mbox, पूर्णांक entries);
बाह्य व्योम fsl_बंद_outb_mbox(काष्ठा rio_mport *mport, पूर्णांक mbox);
बाह्य पूर्णांक fsl_खोलो_inb_mbox(काष्ठा rio_mport *mport,
	व्योम *dev_id, पूर्णांक mbox, पूर्णांक entries);
बाह्य व्योम fsl_बंद_inb_mbox(काष्ठा rio_mport *mport, पूर्णांक mbox);
बाह्य पूर्णांक fsl_add_inb_buffer(काष्ठा rio_mport *mport, पूर्णांक mbox, व्योम *buf);
बाह्य व्योम *fsl_get_inb_message(काष्ठा rio_mport *mport, पूर्णांक mbox);

#पूर्ण_अगर
