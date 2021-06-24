<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * netup_unidvb.h
 *
 * Data type definitions क्रम NetUP Universal Dual DVB-CI
 *
 * Copyright (C) 2014 NetUP Inc.
 * Copyright (C) 2014 Sergey Kozlov <serjk@netup.ru>
 * Copyright (C) 2014 Abylay Ospan <aospan@netup.ru>
 */

#समावेश <linux/pci.h>
#समावेश <linux/i2c.h>
#समावेश <linux/workqueue.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/videobuf2-dvb.h>
#समावेश <media/dvb_ca_en50221.h>

#घोषणा NETUP_UNIDVB_NAME	"netup_unidvb"
#घोषणा NETUP_UNIDVB_VERSION	"0.0.1"
#घोषणा NETUP_VENDOR_ID		0x1b55
#घोषणा NETUP_PCI_DEV_REVISION  0x2

/* IRQ-related regisers */
#घोषणा REG_ISR			0x4890
#घोषणा REG_ISR_MASKED		0x4892
#घोषणा REG_IMASK_SET		0x4894
#घोषणा REG_IMASK_CLEAR		0x4896
/* REG_ISR रेजिस्टर bits */
#घोषणा NETUP_UNIDVB_IRQ_SPI	(1 << 0)
#घोषणा NETUP_UNIDVB_IRQ_I2C0	(1 << 1)
#घोषणा NETUP_UNIDVB_IRQ_I2C1	(1 << 2)
#घोषणा NETUP_UNIDVB_IRQ_FRA0	(1 << 4)
#घोषणा NETUP_UNIDVB_IRQ_FRA1	(1 << 5)
#घोषणा NETUP_UNIDVB_IRQ_FRB0	(1 << 6)
#घोषणा NETUP_UNIDVB_IRQ_FRB1	(1 << 7)
#घोषणा NETUP_UNIDVB_IRQ_DMA1	(1 << 8)
#घोषणा NETUP_UNIDVB_IRQ_DMA2	(1 << 9)
#घोषणा NETUP_UNIDVB_IRQ_CI	(1 << 10)
#घोषणा NETUP_UNIDVB_IRQ_CAM0	(1 << 11)
#घोषणा NETUP_UNIDVB_IRQ_CAM1	(1 << 12)

/* NetUP Universal DVB card hardware revisions and it's PCI device id's:
 * 1.3 - CXD2841ER demod, ASCOT2E and HORUS3A tuners
 * 1.4 - CXD2854ER demod, HELENE tuner
*/
क्रमागत netup_hw_rev अणु
	NETUP_HW_REV_1_3 = 0x18F6,
	NETUP_HW_REV_1_4 = 0x18F7
पूर्ण;

काष्ठा netup_dma अणु
	u8			num;
	spinlock_t		lock;
	काष्ठा netup_unidvb_dev	*ndev;
	काष्ठा netup_dma_regs __iomem *regs;
	u32			ring_buffer_size;
	u8			*addr_virt;
	dma_addr_t		addr_phys;
	u64			addr_last;
	u32			high_addr;
	u32			data_offset;
	u32			data_size;
	काष्ठा list_head	मुक्त_buffers;
	काष्ठा work_काष्ठा	work;
	काष्ठा समयr_list	समयout;
पूर्ण;

क्रमागत netup_i2c_state अणु
	STATE_DONE,
	STATE_WAIT,
	STATE_WANT_READ,
	STATE_WANT_WRITE,
	STATE_ERROR
पूर्ण;

काष्ठा netup_i2c_regs;

काष्ठा netup_i2c अणु
	spinlock_t			lock;
	रुको_queue_head_t		wq;
	काष्ठा i2c_adapter		adap;
	काष्ठा netup_unidvb_dev		*dev;
	काष्ठा netup_i2c_regs __iomem	*regs;
	काष्ठा i2c_msg			*msg;
	क्रमागत netup_i2c_state		state;
	u32				xmit_size;
पूर्ण;

काष्ठा netup_ci_state अणु
	काष्ठा dvb_ca_en50221		ca;
	u8 __iomem			*membase8_config;
	u8 __iomem			*membase8_io;
	काष्ठा netup_unidvb_dev		*dev;
	पूर्णांक status;
	पूर्णांक nr;
पूर्ण;

काष्ठा netup_spi;

काष्ठा netup_unidvb_dev अणु
	काष्ठा pci_dev			*pci_dev;
	पूर्णांक				pci_bus;
	पूर्णांक				pci_slot;
	पूर्णांक				pci_func;
	पूर्णांक				board_num;
	पूर्णांक				old_fw;
	u32 __iomem			*lmmio0;
	u8 __iomem			*bmmio0;
	u32 __iomem			*lmmio1;
	u8 __iomem			*bmmio1;
	u8				*dma_virt;
	dma_addr_t			dma_phys;
	u32				dma_size;
	काष्ठा vb2_dvb_frontends	frontends[2];
	काष्ठा netup_i2c		i2c[2];
	काष्ठा workqueue_काष्ठा		*wq;
	काष्ठा netup_dma		dma[2];
	काष्ठा netup_ci_state		ci[2];
	काष्ठा netup_spi		*spi;
	क्रमागत netup_hw_rev		rev;
पूर्ण;

पूर्णांक netup_i2c_रेजिस्टर(काष्ठा netup_unidvb_dev *ndev);
व्योम netup_i2c_unरेजिस्टर(काष्ठा netup_unidvb_dev *ndev);
irqवापस_t netup_ci_पूर्णांकerrupt(काष्ठा netup_unidvb_dev *ndev);
irqवापस_t netup_i2c_पूर्णांकerrupt(काष्ठा netup_i2c *i2c);
irqवापस_t netup_spi_पूर्णांकerrupt(काष्ठा netup_spi *spi);
पूर्णांक netup_unidvb_ci_रेजिस्टर(काष्ठा netup_unidvb_dev *dev,
			     पूर्णांक num, काष्ठा pci_dev *pci_dev);
व्योम netup_unidvb_ci_unरेजिस्टर(काष्ठा netup_unidvb_dev *dev, पूर्णांक num);
पूर्णांक netup_spi_init(काष्ठा netup_unidvb_dev *ndev);
व्योम netup_spi_release(काष्ठा netup_unidvb_dev *ndev);
