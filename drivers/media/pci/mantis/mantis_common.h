<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
	Mantis PCI bridge driver

	Copyright (C) Manu Abraham (abraham.manu@gmail.com)

*/

#अगर_अघोषित __MANTIS_COMMON_H
#घोषणा __MANTIS_COMMON_H

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mutex.h>
#समावेश <linux/workqueue.h>

#समावेश "mantis_reg.h"
#समावेश "mantis_uart.h"

#समावेश "mantis_link.h"

#घोषणा MANTIS_ERROR		0
#घोषणा MANTIS_NOTICE		1
#घोषणा MANTIS_INFO		2
#घोषणा MANTIS_DEBUG		3
#घोषणा MANTIS_TMG		9

#घोषणा dprपूर्णांकk(y, z, क्रमmat, arg...) करो अणु								\
	अगर (z) अणु											\
		अगर	((mantis->verbose > MANTIS_ERROR) && (mantis->verbose > y))			\
			prपूर्णांकk(KERN_ERR "%s (%d): " क्रमmat "\n" , __func__ , mantis->num , ##arg);	\
		अन्यथा अगर	((mantis->verbose > MANTIS_NOTICE) && (mantis->verbose > y))			\
			prपूर्णांकk(KERN_NOTICE "%s (%d): " क्रमmat "\n" , __func__ , mantis->num , ##arg);	\
		अन्यथा अगर ((mantis->verbose > MANTIS_INFO) && (mantis->verbose > y))			\
			prपूर्णांकk(KERN_INFO "%s (%d): " क्रमmat "\n" , __func__ , mantis->num , ##arg);	\
		अन्यथा अगर ((mantis->verbose > MANTIS_DEBUG) && (mantis->verbose > y))			\
			prपूर्णांकk(KERN_DEBUG "%s (%d): " क्रमmat "\n" , __func__ , mantis->num , ##arg);	\
		अन्यथा अगर ((mantis->verbose > MANTIS_TMG) && (mantis->verbose > y))			\
			prपूर्णांकk(KERN_DEBUG "%s (%d): " क्रमmat "\n" , __func__ , mantis->num , ##arg);	\
	पूर्ण अन्यथा अणु											\
		अगर (mantis->verbose > y)								\
			prपूर्णांकk(क्रमmat , ##arg);								\
	पूर्ण												\
पूर्ण जबतक(0)

#घोषणा mग_लिखो(dat, addr)	ग_लिखोl((dat), addr)
#घोषणा mपढ़ो(addr)		पढ़ोl(addr)

#घोषणा mmग_लिखो(dat, addr)	mग_लिखो((dat), (mantis->mmio + (addr)))
#घोषणा mmपढ़ो(addr)		mपढ़ो(mantis->mmio + (addr))

#घोषणा MANTIS_TS_188		0
#घोषणा MANTIS_TS_204		1

#घोषणा TWINHAN_TECHNOLOGIES	0x1822
#घोषणा MANTIS			0x4e35

#घोषणा TECHNISAT		0x1ae4
#घोषणा TERRATEC		0x153b

#घोषणा MAKE_ENTRY(__subven, __subdev, __configptr, __rc) अणु		\
		.venकरोr		= TWINHAN_TECHNOLOGIES,			\
		.device		= MANTIS,				\
		.subvenकरोr	= (__subven),				\
		.subdevice	= (__subdev),				\
		.driver_data	= (अचिन्हित दीर्घ)			\
			&(काष्ठा mantis_pci_drvdata)अणु__configptr, __rcपूर्ण	\
पूर्ण

क्रमागत mantis_i2c_mode अणु
	MANTIS_PAGE_MODE = 0,
	MANTIS_BYTE_MODE,
पूर्ण;

काष्ठा mantis_pci;

काष्ठा mantis_hwconfig अणु
	अक्षर			*model_name;
	अक्षर			*dev_type;
	u32			ts_size;

	क्रमागत mantis_baud	baud_rate;
	क्रमागत mantis_parity	parity;
	u32			bytes;

	irqवापस_t (*irq_handler)(पूर्णांक irq, व्योम *dev_id);
	पूर्णांक (*frontend_init)(काष्ठा mantis_pci *mantis, काष्ठा dvb_frontend *fe);

	u8			घातer;
	u8			reset;

	क्रमागत mantis_i2c_mode	i2c_mode;
पूर्ण;

काष्ठा mantis_pci_drvdata अणु
	काष्ठा mantis_hwconfig *hwconfig;
	अक्षर *rc_map_name;
पूर्ण;

काष्ठा mantis_pci अणु
	अचिन्हित पूर्णांक		verbose;

	/*	PCI stuff		*/
	u16			venकरोr_id;
	u16			device_id;
	u16			subप्रणाली_venकरोr;
	u16			subप्रणाली_device;

	u8			latency;

	काष्ठा pci_dev		*pdev;

	अचिन्हित दीर्घ		mantis_addr;
	व्योम __iomem		*mmio;

	u8			irq;
	u8			revision;

	अचिन्हित पूर्णांक		num;

	/*	RISC Core		*/
	u32			busy_block;
	u32			last_block;
	u8			*buf_cpu;
	dma_addr_t		buf_dma;
	__le32			*risc_cpu;
	dma_addr_t		risc_dma;

	काष्ठा tasklet_काष्ठा	tasklet;
	spinlock_t		पूर्णांकmask_lock;

	काष्ठा i2c_adapter	adapter;
	पूर्णांक			i2c_rc;
	रुको_queue_head_t	i2c_wq;
	काष्ठा mutex		i2c_lock;

	/*	DVB stuff		*/
	काष्ठा dvb_adapter	dvb_adapter;
	काष्ठा dvb_frontend	*fe;
	काष्ठा dvb_demux	demux;
	काष्ठा dmxdev		dmxdev;
	काष्ठा dmx_frontend	fe_hw;
	काष्ठा dmx_frontend	fe_mem;
	काष्ठा dvb_net		dvbnet;

	u8			feeds;

	काष्ठा mantis_hwconfig	*hwconfig;

	u32			mantis_पूर्णांक_stat;
	u32			mantis_पूर्णांक_mask;

	/*	board specअगरic		*/
	u8			mac_address[8];
	u32			sub_venकरोr_id;
	u32			sub_device_id;

	 /*	A12 A13 A14		*/
	u32			gpio_status;

	u32			gpअगर_status;

	काष्ठा mantis_ca	*mantis_ca;

	काष्ठा work_काष्ठा	uart_work;

	काष्ठा rc_dev		*rc;
	अक्षर			device_name[80];
	अक्षर			input_phys[80];
	अक्षर			*rc_map_name;
पूर्ण;

#घोषणा MANTIS_HIF_STATUS	(mantis->gpio_status)

अटल अंतरभूत व्योम mantis_mask_पूर्णांकs(काष्ठा mantis_pci *mantis, u32 mask)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mantis->पूर्णांकmask_lock, flags);
	mmग_लिखो(mmपढ़ो(MANTIS_INT_MASK) & ~mask, MANTIS_INT_MASK);
	spin_unlock_irqrestore(&mantis->पूर्णांकmask_lock, flags);
पूर्ण

अटल अंतरभूत व्योम mantis_unmask_पूर्णांकs(काष्ठा mantis_pci *mantis, u32 mask)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mantis->पूर्णांकmask_lock, flags);
	mmग_लिखो(mmपढ़ो(MANTIS_INT_MASK) | mask, MANTIS_INT_MASK);
	spin_unlock_irqrestore(&mantis->पूर्णांकmask_lock, flags);
पूर्ण

#पूर्ण_अगर /* __MANTIS_COMMON_H */
