<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * c67x00-ll-hpi.c: Cypress C67X00 USB Low level पूर्णांकerface using HPI
 *
 * Copyright (C) 2006-2008 Barco N.V.
 *    Derived from the Cypress cy7c67200/300 ezusb linux driver and
 *    based on multiple host controller drivers inside the linux kernel.
 */

#समावेश <यंत्र/byteorder.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/usb/c67x00.h>
#समावेश "c67x00.h"

#घोषणा COMM_REGS 14

काष्ठा c67x00_lcp_पूर्णांक_data अणु
	u16 regs[COMM_REGS];
पूर्ण;

/* -------------------------------------------------------------------------- */
/* Interface definitions */

#घोषणा COMM_ACK			0x0FED
#घोषणा COMM_NAK			0xDEAD

#घोषणा COMM_RESET			0xFA50
#घोषणा COMM_EXEC_INT			0xCE01
#घोषणा COMM_INT_NUM			0x01C2

/* Registers 0 to COMM_REGS-1 */
#घोषणा COMM_R(x)			(0x01C4 + 2 * (x))

#घोषणा HUSB_SIE_pCurrentTDPtr(x)	((x) ? 0x01B2 : 0x01B0)
#घोषणा HUSB_SIE_pTDListDone_Sem(x)	((x) ? 0x01B8 : 0x01B6)
#घोषणा HUSB_pEOT			0x01B4

/* Software पूर्णांकerrupts */
/* 114, 115: */
#घोषणा HUSB_SIE_INIT_INT(x)		((x) ? 0x0073 : 0x0072)
#घोषणा HUSB_RESET_INT			0x0074

#घोषणा SUSB_INIT_INT			0x0071
#घोषणा SUSB_INIT_INT_LOC		(SUSB_INIT_INT * 2)

/* -----------------------------------------------------------------------
 * HPI implementation
 *
 * The c67x00 chip also support control via SPI or HSS serial
 * पूर्णांकerfaces. However, this driver assumes that रेजिस्टर access can
 * be perक्रमmed from IRQ context. While this is a safe assumption with
 * the HPI पूर्णांकerface, it is not true क्रम the serial पूर्णांकerfaces.
 */

/* HPI रेजिस्टरs */
#घोषणा HPI_DATA	0
#घोषणा HPI_MAILBOX	1
#घोषणा HPI_ADDR	2
#घोषणा HPI_STATUS	3

/*
 * According to CY7C67300 specअगरication (tables 140 and 141) HPI पढ़ो and
 * ग_लिखो cycle duration Tcyc must be at least 6T दीर्घ, where T is 1/48MHz,
 * which is 125ns.
 */
#घोषणा HPI_T_CYC_NS	125

अटल अंतरभूत u16 hpi_पढ़ो_reg(काष्ठा c67x00_device *dev, पूर्णांक reg)
अणु
	ndelay(HPI_T_CYC_NS);
	वापस __raw_पढ़ोw(dev->hpi.base + reg * dev->hpi.regstep);
पूर्ण

अटल अंतरभूत व्योम hpi_ग_लिखो_reg(काष्ठा c67x00_device *dev, पूर्णांक reg, u16 value)
अणु
	ndelay(HPI_T_CYC_NS);
	__raw_ग_लिखोw(value, dev->hpi.base + reg * dev->hpi.regstep);
पूर्ण

अटल अंतरभूत u16 hpi_पढ़ो_word_nolock(काष्ठा c67x00_device *dev, u16 reg)
अणु
	hpi_ग_लिखो_reg(dev, HPI_ADDR, reg);
	वापस hpi_पढ़ो_reg(dev, HPI_DATA);
पूर्ण

अटल u16 hpi_पढ़ो_word(काष्ठा c67x00_device *dev, u16 reg)
अणु
	u16 value;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->hpi.lock, flags);
	value = hpi_पढ़ो_word_nolock(dev, reg);
	spin_unlock_irqrestore(&dev->hpi.lock, flags);

	वापस value;
पूर्ण

अटल व्योम hpi_ग_लिखो_word_nolock(काष्ठा c67x00_device *dev, u16 reg, u16 value)
अणु
	hpi_ग_लिखो_reg(dev, HPI_ADDR, reg);
	hpi_ग_लिखो_reg(dev, HPI_DATA, value);
पूर्ण

अटल व्योम hpi_ग_लिखो_word(काष्ठा c67x00_device *dev, u16 reg, u16 value)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->hpi.lock, flags);
	hpi_ग_लिखो_word_nolock(dev, reg, value);
	spin_unlock_irqrestore(&dev->hpi.lock, flags);
पूर्ण

/*
 * Only data is little endian, addr has cpu endianess
 */
अटल व्योम hpi_ग_लिखो_words_le16(काष्ठा c67x00_device *dev, u16 addr,
				 __le16 *data, u16 count)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	spin_lock_irqsave(&dev->hpi.lock, flags);

	hpi_ग_लिखो_reg(dev, HPI_ADDR, addr);
	क्रम (i = 0; i < count; i++)
		hpi_ग_लिखो_reg(dev, HPI_DATA, le16_to_cpu(*data++));

	spin_unlock_irqrestore(&dev->hpi.lock, flags);
पूर्ण

/*
 * Only data is little endian, addr has cpu endianess
 */
अटल व्योम hpi_पढ़ो_words_le16(काष्ठा c67x00_device *dev, u16 addr,
				__le16 *data, u16 count)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	spin_lock_irqsave(&dev->hpi.lock, flags);
	hpi_ग_लिखो_reg(dev, HPI_ADDR, addr);
	क्रम (i = 0; i < count; i++)
		*data++ = cpu_to_le16(hpi_पढ़ो_reg(dev, HPI_DATA));

	spin_unlock_irqrestore(&dev->hpi.lock, flags);
पूर्ण

अटल व्योम hpi_set_bits(काष्ठा c67x00_device *dev, u16 reg, u16 mask)
अणु
	u16 value;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->hpi.lock, flags);
	value = hpi_पढ़ो_word_nolock(dev, reg);
	hpi_ग_लिखो_word_nolock(dev, reg, value | mask);
	spin_unlock_irqrestore(&dev->hpi.lock, flags);
पूर्ण

अटल व्योम hpi_clear_bits(काष्ठा c67x00_device *dev, u16 reg, u16 mask)
अणु
	u16 value;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->hpi.lock, flags);
	value = hpi_पढ़ो_word_nolock(dev, reg);
	hpi_ग_लिखो_word_nolock(dev, reg, value & ~mask);
	spin_unlock_irqrestore(&dev->hpi.lock, flags);
पूर्ण

अटल u16 hpi_recv_mbox(काष्ठा c67x00_device *dev)
अणु
	u16 value;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->hpi.lock, flags);
	value = hpi_पढ़ो_reg(dev, HPI_MAILBOX);
	spin_unlock_irqrestore(&dev->hpi.lock, flags);

	वापस value;
पूर्ण

अटल u16 hpi_send_mbox(काष्ठा c67x00_device *dev, u16 value)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->hpi.lock, flags);
	hpi_ग_लिखो_reg(dev, HPI_MAILBOX, value);
	spin_unlock_irqrestore(&dev->hpi.lock, flags);

	वापस value;
पूर्ण

u16 c67x00_ll_hpi_status(काष्ठा c67x00_device *dev)
अणु
	u16 value;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->hpi.lock, flags);
	value = hpi_पढ़ो_reg(dev, HPI_STATUS);
	spin_unlock_irqrestore(&dev->hpi.lock, flags);

	वापस value;
पूर्ण

व्योम c67x00_ll_hpi_reg_init(काष्ठा c67x00_device *dev)
अणु
	पूर्णांक i;

	hpi_recv_mbox(dev);
	c67x00_ll_hpi_status(dev);
	hpi_ग_लिखो_word(dev, HPI_IRQ_ROUTING_REG, 0);

	क्रम (i = 0; i < C67X00_SIES; i++) अणु
		hpi_ग_लिखो_word(dev, SIEMSG_REG(i), 0);
		hpi_पढ़ो_word(dev, SIEMSG_REG(i));
	पूर्ण
पूर्ण

व्योम c67x00_ll_hpi_enable_sofeop(काष्ठा c67x00_sie *sie)
अणु
	hpi_set_bits(sie->dev, HPI_IRQ_ROUTING_REG,
		     SOFEOP_TO_HPI_EN(sie->sie_num));
पूर्ण

व्योम c67x00_ll_hpi_disable_sofeop(काष्ठा c67x00_sie *sie)
अणु
	hpi_clear_bits(sie->dev, HPI_IRQ_ROUTING_REG,
		       SOFEOP_TO_HPI_EN(sie->sie_num));
पूर्ण

/* -------------------------------------------------------------------------- */
/* Transactions */

अटल अंतरभूत पूर्णांक ll_recv_msg(काष्ठा c67x00_device *dev)
अणु
	u16 res;

	res = रुको_क्रम_completion_समयout(&dev->hpi.lcp.msg_received, 5 * HZ);
	WARN_ON(!res);

	वापस (res == 0) ? -EIO : 0;
पूर्ण

/* -------------------------------------------------------------------------- */
/* General functions */

u16 c67x00_ll_fetch_siemsg(काष्ठा c67x00_device *dev, पूर्णांक sie_num)
अणु
	u16 val;

	val = hpi_पढ़ो_word(dev, SIEMSG_REG(sie_num));
	/* clear रेजिस्टर to allow next message */
	hpi_ग_लिखो_word(dev, SIEMSG_REG(sie_num), 0);

	वापस val;
पूर्ण

u16 c67x00_ll_get_usb_ctl(काष्ठा c67x00_sie *sie)
अणु
	वापस hpi_पढ़ो_word(sie->dev, USB_CTL_REG(sie->sie_num));
पूर्ण

/*
 * c67x00_ll_usb_clear_status - clear the USB status bits
 */
व्योम c67x00_ll_usb_clear_status(काष्ठा c67x00_sie *sie, u16 bits)
अणु
	hpi_ग_लिखो_word(sie->dev, USB_STAT_REG(sie->sie_num), bits);
पूर्ण

u16 c67x00_ll_usb_get_status(काष्ठा c67x00_sie *sie)
अणु
	वापस hpi_पढ़ो_word(sie->dev, USB_STAT_REG(sie->sie_num));
पूर्ण

/* -------------------------------------------------------------------------- */

अटल पूर्णांक c67x00_comm_exec_पूर्णांक(काष्ठा c67x00_device *dev, u16 nr,
				काष्ठा c67x00_lcp_पूर्णांक_data *data)
अणु
	पूर्णांक i, rc;

	mutex_lock(&dev->hpi.lcp.mutex);
	hpi_ग_लिखो_word(dev, COMM_INT_NUM, nr);
	क्रम (i = 0; i < COMM_REGS; i++)
		hpi_ग_लिखो_word(dev, COMM_R(i), data->regs[i]);
	hpi_send_mbox(dev, COMM_EXEC_INT);
	rc = ll_recv_msg(dev);
	mutex_unlock(&dev->hpi.lcp.mutex);

	वापस rc;
पूर्ण

/* -------------------------------------------------------------------------- */
/* Host specअगरic functions */

व्योम c67x00_ll_set_husb_eot(काष्ठा c67x00_device *dev, u16 value)
अणु
	mutex_lock(&dev->hpi.lcp.mutex);
	hpi_ग_लिखो_word(dev, HUSB_pEOT, value);
	mutex_unlock(&dev->hpi.lcp.mutex);
पूर्ण

अटल अंतरभूत व्योम c67x00_ll_husb_sie_init(काष्ठा c67x00_sie *sie)
अणु
	काष्ठा c67x00_device *dev = sie->dev;
	काष्ठा c67x00_lcp_पूर्णांक_data data;
	पूर्णांक rc;

	rc = c67x00_comm_exec_पूर्णांक(dev, HUSB_SIE_INIT_INT(sie->sie_num), &data);
	BUG_ON(rc); /* No वापस path क्रम error code; crash spectacularly */
पूर्ण

व्योम c67x00_ll_husb_reset(काष्ठा c67x00_sie *sie, पूर्णांक port)
अणु
	काष्ठा c67x00_device *dev = sie->dev;
	काष्ठा c67x00_lcp_पूर्णांक_data data;
	पूर्णांक rc;

	data.regs[0] = 50;	/* Reset USB port क्रम 50ms */
	data.regs[1] = port | (sie->sie_num << 1);
	rc = c67x00_comm_exec_पूर्णांक(dev, HUSB_RESET_INT, &data);
	BUG_ON(rc); /* No वापस path क्रम error code; crash spectacularly */
पूर्ण

व्योम c67x00_ll_husb_set_current_td(काष्ठा c67x00_sie *sie, u16 addr)
अणु
	hpi_ग_लिखो_word(sie->dev, HUSB_SIE_pCurrentTDPtr(sie->sie_num), addr);
पूर्ण

u16 c67x00_ll_husb_get_current_td(काष्ठा c67x00_sie *sie)
अणु
	वापस hpi_पढ़ो_word(sie->dev, HUSB_SIE_pCurrentTDPtr(sie->sie_num));
पूर्ण

u16 c67x00_ll_husb_get_frame(काष्ठा c67x00_sie *sie)
अणु
	वापस hpi_पढ़ो_word(sie->dev, HOST_FRAME_REG(sie->sie_num));
पूर्ण

व्योम c67x00_ll_husb_init_host_port(काष्ठा c67x00_sie *sie)
अणु
	/* Set port पूर्णांकo host mode */
	hpi_set_bits(sie->dev, USB_CTL_REG(sie->sie_num), HOST_MODE);
	c67x00_ll_husb_sie_init(sie);
	/* Clear पूर्णांकerrupts */
	c67x00_ll_usb_clear_status(sie, HOST_STAT_MASK);
	/* Check */
	अगर (!(hpi_पढ़ो_word(sie->dev, USB_CTL_REG(sie->sie_num)) & HOST_MODE))
		dev_warn(sie_dev(sie),
			 "SIE %d not set to host mode\n", sie->sie_num);
पूर्ण

व्योम c67x00_ll_husb_reset_port(काष्ठा c67x00_sie *sie, पूर्णांक port)
अणु
	/* Clear connect change */
	c67x00_ll_usb_clear_status(sie, PORT_CONNECT_CHANGE(port));

	/* Enable पूर्णांकerrupts */
	hpi_set_bits(sie->dev, HPI_IRQ_ROUTING_REG,
		     SOFEOP_TO_CPU_EN(sie->sie_num));
	hpi_set_bits(sie->dev, HOST_IRQ_EN_REG(sie->sie_num),
		     SOF_EOP_IRQ_EN | DONE_IRQ_EN);

	/* Enable pull करोwn transistors */
	hpi_set_bits(sie->dev, USB_CTL_REG(sie->sie_num), PORT_RES_EN(port));
पूर्ण

/* -------------------------------------------------------------------------- */

व्योम c67x00_ll_irq(काष्ठा c67x00_device *dev, u16 पूर्णांक_status)
अणु
	अगर ((पूर्णांक_status & MBX_OUT_FLG) == 0)
		वापस;

	dev->hpi.lcp.last_msg = hpi_recv_mbox(dev);
	complete(&dev->hpi.lcp.msg_received);
पूर्ण

/* -------------------------------------------------------------------------- */

पूर्णांक c67x00_ll_reset(काष्ठा c67x00_device *dev)
अणु
	पूर्णांक rc;

	mutex_lock(&dev->hpi.lcp.mutex);
	hpi_send_mbox(dev, COMM_RESET);
	rc = ll_recv_msg(dev);
	mutex_unlock(&dev->hpi.lcp.mutex);

	वापस rc;
पूर्ण

/* -------------------------------------------------------------------------- */

/*
 * c67x00_ll_ग_लिखो_mem_le16 - ग_लिखो पूर्णांकo c67x00 memory
 * Only data is little endian, addr has cpu endianess.
 */
व्योम c67x00_ll_ग_लिखो_mem_le16(काष्ठा c67x00_device *dev, u16 addr,
			      व्योम *data, पूर्णांक len)
अणु
	u8 *buf = data;

	/* Sanity check */
	अगर (addr + len > 0xffff) अणु
		dev_err(&dev->pdev->dev,
			"Trying to write beyond writable region!\n");
		वापस;
	पूर्ण

	अगर (addr & 0x01) अणु
		/* unaligned access */
		u16 पंचांगp;
		पंचांगp = hpi_पढ़ो_word(dev, addr - 1);
		पंचांगp = (पंचांगp & 0x00ff) | (*buf++ << 8);
		hpi_ग_लिखो_word(dev, addr - 1, पंचांगp);
		addr++;
		len--;
	पूर्ण

	hpi_ग_लिखो_words_le16(dev, addr, (__le16 *)buf, len / 2);
	buf += len & ~0x01;
	addr += len & ~0x01;
	len &= 0x01;

	अगर (len) अणु
		u16 पंचांगp;
		पंचांगp = hpi_पढ़ो_word(dev, addr);
		पंचांगp = (पंचांगp & 0xff00) | *buf;
		hpi_ग_लिखो_word(dev, addr, पंचांगp);
	पूर्ण
पूर्ण

/*
 * c67x00_ll_पढ़ो_mem_le16 - पढ़ो from c67x00 memory
 * Only data is little endian, addr has cpu endianess.
 */
व्योम c67x00_ll_पढ़ो_mem_le16(काष्ठा c67x00_device *dev, u16 addr,
			     व्योम *data, पूर्णांक len)
अणु
	u8 *buf = data;

	अगर (addr & 0x01) अणु
		/* unaligned access */
		u16 पंचांगp;
		पंचांगp = hpi_पढ़ो_word(dev, addr - 1);
		*buf++ = (पंचांगp >> 8) & 0x00ff;
		addr++;
		len--;
	पूर्ण

	hpi_पढ़ो_words_le16(dev, addr, (__le16 *)buf, len / 2);
	buf += len & ~0x01;
	addr += len & ~0x01;
	len &= 0x01;

	अगर (len) अणु
		u16 पंचांगp;
		पंचांगp = hpi_पढ़ो_word(dev, addr);
		*buf = पंचांगp & 0x00ff;
	पूर्ण
पूर्ण

/* -------------------------------------------------------------------------- */

व्योम c67x00_ll_init(काष्ठा c67x00_device *dev)
अणु
	mutex_init(&dev->hpi.lcp.mutex);
	init_completion(&dev->hpi.lcp.msg_received);
पूर्ण

व्योम c67x00_ll_release(काष्ठा c67x00_device *dev)
अणु
पूर्ण
