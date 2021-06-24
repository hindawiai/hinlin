<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम the Solos PCI ADSL2+ card, deचिन्हित to support Linux by
 *  Traverse Technologies -- https://www.traverse.com.au/
 *  Xrio Limited          -- http://www.xrio.com/
 *
 * Copyright तऊ 2008 Traverse Technologies
 * Copyright तऊ 2008 Intel Corporation
 *
 * Authors: Nathan Williams <nathan@traverse.com.au>
 *          David Woodhouse <dwmw2@infradead.org>
 *          Treker Chen <treker@xrio.com>
 */

#घोषणा DEBUG
#घोषणा VERBOSE_DEBUG

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/aपंचांग.h>
#समावेश <linux/aपंचांगdev.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/device.h>
#समावेश <linux/kobject.h>
#समावेश <linux/firmware.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/swab.h>
#समावेश <linux/slab.h>

#घोषणा VERSION "1.04"
#घोषणा DRIVER_VERSION 0x01
#घोषणा PTAG "solos-pci"

#घोषणा CONFIG_RAM_SIZE	128
#घोषणा FLAGS_ADDR	0x7C
#घोषणा IRQ_EN_ADDR	0x78
#घोषणा FPGA_VER	0x74
#घोषणा IRQ_CLEAR	0x70
#घोषणा WRITE_FLASH	0x6C
#घोषणा PORTS		0x68
#घोषणा FLASH_BLOCK	0x64
#घोषणा FLASH_BUSY	0x60
#घोषणा FPGA_MODE	0x5C
#घोषणा FLASH_MODE	0x58
#घोषणा GPIO_STATUS	0x54
#घोषणा DRIVER_VER	0x50
#घोषणा TX_DMA_ADDR(port)	(0x40 + (4 * (port)))
#घोषणा RX_DMA_ADDR(port)	(0x30 + (4 * (port)))

#घोषणा DATA_RAM_SIZE	32768
#घोषणा BUF_SIZE	2048
#घोषणा OLD_BUF_SIZE	4096 /* For FPGA versions <= 2*/
/* Old boards use ATMEL AD45DB161D flash */
#घोषणा ATMEL_FPGA_PAGE	528 /* FPGA flash page size*/
#घोषणा ATMEL_SOLOS_PAGE	512 /* Solos flash page size*/
#घोषणा ATMEL_FPGA_BLOCK	(ATMEL_FPGA_PAGE * 8) /* FPGA block size*/
#घोषणा ATMEL_SOLOS_BLOCK	(ATMEL_SOLOS_PAGE * 8) /* Solos block size*/
/* Current boards use M25P/M25PE SPI flash */
#घोषणा SPI_FLASH_BLOCK	(256 * 64)

#घोषणा RX_BUF(card, nr) ((card->buffers) + (nr)*(card->buffer_size)*2)
#घोषणा TX_BUF(card, nr) ((card->buffers) + (nr)*(card->buffer_size)*2 + (card->buffer_size))
#घोषणा FLASH_BUF ((card->buffers) + 4*(card->buffer_size)*2)

#घोषणा RX_DMA_SIZE	2048

#घोषणा FPGA_VERSION(a,b) (((a) << 8) + (b))
#घोषणा LEGACY_BUFFERS	2
#घोषणा DMA_SUPPORTED	4

अटल पूर्णांक reset = 0;
अटल पूर्णांक aपंचांगdebug = 0;
अटल पूर्णांक firmware_upgrade = 0;
अटल पूर्णांक fpga_upgrade = 0;
अटल पूर्णांक db_firmware_upgrade = 0;
अटल पूर्णांक db_fpga_upgrade = 0;

काष्ठा pkt_hdr अणु
	__le16 size;
	__le16 vpi;
	__le16 vci;
	__le16 type;
पूर्ण;

काष्ठा solos_skb_cb अणु
	काष्ठा aपंचांग_vcc *vcc;
	uपूर्णांक32_t dma_addr;
पूर्ण;


#घोषणा SKB_CB(skb)		((काष्ठा solos_skb_cb *)skb->cb)

#घोषणा PKT_DATA	0
#घोषणा PKT_COMMAND	1
#घोषणा PKT_POPEN	3
#घोषणा PKT_PCLOSE	4
#घोषणा PKT_STATUS	5

काष्ठा solos_card अणु
	व्योम __iomem *config_regs;
	व्योम __iomem *buffers;
	पूर्णांक nr_ports;
	पूर्णांक tx_mask;
	काष्ठा pci_dev *dev;
	काष्ठा aपंचांग_dev *aपंचांगdev[4];
	काष्ठा tasklet_काष्ठा tlet;
	spinlock_t tx_lock;
	spinlock_t tx_queue_lock;
	spinlock_t cli_queue_lock;
	spinlock_t param_queue_lock;
	काष्ठा list_head param_queue;
	काष्ठा sk_buff_head tx_queue[4];
	काष्ठा sk_buff_head cli_queue[4];
	काष्ठा sk_buff *tx_skb[4];
	काष्ठा sk_buff *rx_skb[4];
	अचिन्हित अक्षर *dma_bounce;
	रुको_queue_head_t param_wq;
	रुको_queue_head_t fw_wq;
	पूर्णांक using_dma;
	पूर्णांक dma_alignment;
	पूर्णांक fpga_version;
	पूर्णांक buffer_size;
	पूर्णांक aपंचांगel_flash;
पूर्ण;


काष्ठा solos_param अणु
	काष्ठा list_head list;
	pid_t pid;
	पूर्णांक port;
	काष्ठा sk_buff *response;
पूर्ण;

#घोषणा SOLOS_CHAN(aपंचांगdev) ((पूर्णांक)(अचिन्हित दीर्घ)(aपंचांगdev)->phy_data)

MODULE_AUTHOR("Traverse Technologies <support@traverse.com.au>");
MODULE_DESCRIPTION("Solos PCI driver");
MODULE_VERSION(VERSION);
MODULE_LICENSE("GPL");
MODULE_FIRMWARE("solos-FPGA.bin");
MODULE_FIRMWARE("solos-Firmware.bin");
MODULE_FIRMWARE("solos-db-FPGA.bin");
MODULE_PARM_DESC(reset, "Reset Solos chips on startup");
MODULE_PARM_DESC(aपंचांगdebug, "Print ATM data");
MODULE_PARM_DESC(firmware_upgrade, "Initiate Solos firmware upgrade");
MODULE_PARM_DESC(fpga_upgrade, "Initiate FPGA upgrade");
MODULE_PARM_DESC(db_firmware_upgrade, "Initiate daughter board Solos firmware upgrade");
MODULE_PARM_DESC(db_fpga_upgrade, "Initiate daughter board FPGA upgrade");
module_param(reset, पूर्णांक, 0444);
module_param(aपंचांगdebug, पूर्णांक, 0644);
module_param(firmware_upgrade, पूर्णांक, 0444);
module_param(fpga_upgrade, पूर्णांक, 0444);
module_param(db_firmware_upgrade, पूर्णांक, 0444);
module_param(db_fpga_upgrade, पूर्णांक, 0444);

अटल व्योम fpga_queue(काष्ठा solos_card *card, पूर्णांक port, काष्ठा sk_buff *skb,
		       काष्ठा aपंचांग_vcc *vcc);
अटल uपूर्णांक32_t fpga_tx(काष्ठा solos_card *);
अटल irqवापस_t solos_irq(पूर्णांक irq, व्योम *dev_id);
अटल काष्ठा aपंचांग_vcc* find_vcc(काष्ठा aपंचांग_dev *dev, लघु vpi, पूर्णांक vci);
अटल पूर्णांक aपंचांग_init(काष्ठा solos_card *, काष्ठा device *);
अटल व्योम aपंचांग_हटाओ(काष्ठा solos_card *);
अटल पूर्णांक send_command(काष्ठा solos_card *card, पूर्णांक dev, स्थिर अक्षर *buf, माप_प्रकार size);
अटल व्योम solos_bh(अचिन्हित दीर्घ);
अटल पूर्णांक prपूर्णांक_buffer(काष्ठा sk_buff *buf);

अटल अंतरभूत व्योम solos_pop(काष्ठा aपंचांग_vcc *vcc, काष्ठा sk_buff *skb)
अणु
        अगर (vcc->pop)
                vcc->pop(vcc, skb);
        अन्यथा
                dev_kमुक्त_skb_any(skb);
पूर्ण

अटल sमाप_प्रकार solos_param_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा aपंचांग_dev *aपंचांगdev = container_of(dev, काष्ठा aपंचांग_dev, class_dev);
	काष्ठा solos_card *card = aपंचांगdev->dev_data;
	काष्ठा solos_param prm;
	काष्ठा sk_buff *skb;
	काष्ठा pkt_hdr *header;
	पूर्णांक buflen;

	buflen = म_माप(attr->attr.name) + 10;

	skb = alloc_skb(माप(*header) + buflen, GFP_KERNEL);
	अगर (!skb) अणु
		dev_warn(&card->dev->dev, "Failed to allocate sk_buff in solos_param_show()\n");
		वापस -ENOMEM;
	पूर्ण

	header = skb_put(skb, माप(*header));

	buflen = snम_लिखो((व्योम *)&header[1], buflen - 1,
			  "L%05d\n%s\n", current->pid, attr->attr.name);
	skb_put(skb, buflen);

	header->size = cpu_to_le16(buflen);
	header->vpi = cpu_to_le16(0);
	header->vci = cpu_to_le16(0);
	header->type = cpu_to_le16(PKT_COMMAND);

	prm.pid = current->pid;
	prm.response = शून्य;
	prm.port = SOLOS_CHAN(aपंचांगdev);

	spin_lock_irq(&card->param_queue_lock);
	list_add(&prm.list, &card->param_queue);
	spin_unlock_irq(&card->param_queue_lock);

	fpga_queue(card, prm.port, skb, शून्य);

	रुको_event_समयout(card->param_wq, prm.response, 5 * HZ);

	spin_lock_irq(&card->param_queue_lock);
	list_del(&prm.list);
	spin_unlock_irq(&card->param_queue_lock);

	अगर (!prm.response)
		वापस -EIO;

	buflen = prm.response->len;
	स_नकल(buf, prm.response->data, buflen);
	kमुक्त_skb(prm.response);

	वापस buflen;
पूर्ण

अटल sमाप_प्रकार solos_param_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा aपंचांग_dev *aपंचांगdev = container_of(dev, काष्ठा aपंचांग_dev, class_dev);
	काष्ठा solos_card *card = aपंचांगdev->dev_data;
	काष्ठा solos_param prm;
	काष्ठा sk_buff *skb;
	काष्ठा pkt_hdr *header;
	पूर्णांक buflen;
	sमाप_प्रकार ret;

	buflen = म_माप(attr->attr.name) + 11 + count;

	skb = alloc_skb(माप(*header) + buflen, GFP_KERNEL);
	अगर (!skb) अणु
		dev_warn(&card->dev->dev, "Failed to allocate sk_buff in solos_param_store()\n");
		वापस -ENOMEM;
	पूर्ण

	header = skb_put(skb, माप(*header));

	buflen = snम_लिखो((व्योम *)&header[1], buflen - 1,
			  "L%05d\n%s\n%s\n", current->pid, attr->attr.name, buf);

	skb_put(skb, buflen);
	header->size = cpu_to_le16(buflen);
	header->vpi = cpu_to_le16(0);
	header->vci = cpu_to_le16(0);
	header->type = cpu_to_le16(PKT_COMMAND);

	prm.pid = current->pid;
	prm.response = शून्य;
	prm.port = SOLOS_CHAN(aपंचांगdev);

	spin_lock_irq(&card->param_queue_lock);
	list_add(&prm.list, &card->param_queue);
	spin_unlock_irq(&card->param_queue_lock);

	fpga_queue(card, prm.port, skb, शून्य);

	रुको_event_समयout(card->param_wq, prm.response, 5 * HZ);

	spin_lock_irq(&card->param_queue_lock);
	list_del(&prm.list);
	spin_unlock_irq(&card->param_queue_lock);

	skb = prm.response;

	अगर (!skb)
		वापस -EIO;

	buflen = skb->len;

	/* Someबार it has a newline, someबार it करोesn't. */
	अगर (skb->data[buflen - 1] == '\n')
		buflen--;

	अगर (buflen == 2 && !म_भेदन(skb->data, "OK", 2))
		ret = count;
	अन्यथा अगर (buflen == 5 && !म_भेदन(skb->data, "ERROR", 5))
		ret = -EIO;
	अन्यथा अणु
		/* We know we have enough space allocated क्रम this; we allocated 
		   it ourselves */
		skb->data[buflen] = 0;
	
		dev_warn(&card->dev->dev, "Unexpected parameter response: '%s'\n",
			 skb->data);
		ret = -EIO;
	पूर्ण
	kमुक्त_skb(skb);

	वापस ret;
पूर्ण

अटल अक्षर *next_string(काष्ठा sk_buff *skb)
अणु
	पूर्णांक i = 0;
	अक्षर *this = skb->data;
	
	क्रम (i = 0; i < skb->len; i++) अणु
		अगर (this[i] == '\n') अणु
			this[i] = 0;
			skb_pull(skb, i + 1);
			वापस this;
		पूर्ण
		अगर (!है_छाप(this[i]))
			वापस शून्य;
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * Status packet has fields separated by \न, starting with a version number
 * क्रम the inक्रमmation therein. Fields are....
 *
 *     packet version
 *     RxBitRate	(version >= 1)
 *     TxBitRate	(version >= 1)
 *     State		(version >= 1)
 *     LocalSNRMargin	(version >= 1)
 *     LocalLineAttn	(version >= 1)
 */       
अटल पूर्णांक process_status(काष्ठा solos_card *card, पूर्णांक port, काष्ठा sk_buff *skb)
अणु
	अक्षर *str, *state_str, *snr, *attn;
	पूर्णांक ver, rate_up, rate_करोwn, err;

	अगर (!card->aपंचांगdev[port])
		वापस -ENODEV;

	str = next_string(skb);
	अगर (!str)
		वापस -EIO;

	err = kstrtoपूर्णांक(str, 10, &ver);
	अगर (err) अणु
		dev_warn(&card->dev->dev, "Unexpected status interrupt version\n");
		वापस err;
	पूर्ण
	अगर (ver < 1) अणु
		dev_warn(&card->dev->dev, "Unexpected status interrupt version %d\n",
			 ver);
		वापस -EIO;
	पूर्ण

	str = next_string(skb);
	अगर (!str)
		वापस -EIO;
	अगर (!म_भेद(str, "ERROR")) अणु
		dev_dbg(&card->dev->dev, "Status packet indicated Solos error on port %d (starting up?)\n",
			 port);
		वापस 0;
	पूर्ण

	err = kstrtoपूर्णांक(str, 10, &rate_करोwn);
	अगर (err)
		वापस err;

	str = next_string(skb);
	अगर (!str)
		वापस -EIO;
	err = kstrtoपूर्णांक(str, 10, &rate_up);
	अगर (err)
		वापस err;

	state_str = next_string(skb);
	अगर (!state_str)
		वापस -EIO;

	/* Anything but 'Showtime' is करोwn */
	अगर (म_भेद(state_str, "Showtime")) अणु
		aपंचांग_dev_संकेत_change(card->aपंचांगdev[port], ATM_PHY_SIG_LOST);
		dev_info(&card->dev->dev, "Port %d: %s\n", port, state_str);
		वापस 0;
	पूर्ण

	snr = next_string(skb);
	अगर (!snr)
		वापस -EIO;
	attn = next_string(skb);
	अगर (!attn)
		वापस -EIO;

	dev_info(&card->dev->dev, "Port %d: %s @%d/%d kb/s%s%s%s%s\n",
		 port, state_str, rate_करोwn/1000, rate_up/1000,
		 snr[0]?", SNR ":"", snr, attn[0]?", Attn ":"", attn);
	
	card->aपंचांगdev[port]->link_rate = rate_करोwn / 424;
	aपंचांग_dev_संकेत_change(card->aपंचांगdev[port], ATM_PHY_SIG_FOUND);

	वापस 0;
पूर्ण

अटल पूर्णांक process_command(काष्ठा solos_card *card, पूर्णांक port, काष्ठा sk_buff *skb)
अणु
	काष्ठा solos_param *prm;
	अचिन्हित दीर्घ flags;
	पूर्णांक cmdpid;
	पूर्णांक found = 0, err;

	अगर (skb->len < 7)
		वापस 0;

	अगर (skb->data[0] != 'L'    || !है_अंक(skb->data[1]) ||
	    !है_अंक(skb->data[2]) || !है_अंक(skb->data[3]) ||
	    !है_अंक(skb->data[4]) || !है_अंक(skb->data[5]) ||
	    skb->data[6] != '\n')
		वापस 0;

	err = kstrtoपूर्णांक(&skb->data[1], 10, &cmdpid);
	अगर (err)
		वापस err;

	spin_lock_irqsave(&card->param_queue_lock, flags);
	list_क्रम_each_entry(prm, &card->param_queue, list) अणु
		अगर (prm->port == port && prm->pid == cmdpid) अणु
			prm->response = skb;
			skb_pull(skb, 7);
			wake_up(&card->param_wq);
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&card->param_queue_lock, flags);
	वापस found;
पूर्ण

अटल sमाप_प्रकार console_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा aपंचांग_dev *aपंचांगdev = container_of(dev, काष्ठा aपंचांग_dev, class_dev);
	काष्ठा solos_card *card = aपंचांगdev->dev_data;
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक len;

	spin_lock(&card->cli_queue_lock);
	skb = skb_dequeue(&card->cli_queue[SOLOS_CHAN(aपंचांगdev)]);
	spin_unlock(&card->cli_queue_lock);
	अगर(skb == शून्य)
		वापस प्र_लिखो(buf, "No data.\n");

	len = skb->len;
	स_नकल(buf, skb->data, len);

	kमुक्त_skb(skb);
	वापस len;
पूर्ण

अटल पूर्णांक send_command(काष्ठा solos_card *card, पूर्णांक dev, स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा pkt_hdr *header;

	अगर (size > (BUF_SIZE - माप(*header))) अणु
		dev_dbg(&card->dev->dev, "Command is too big.  Dropping request\n");
		वापस 0;
	पूर्ण
	skb = alloc_skb(size + माप(*header), GFP_ATOMIC);
	अगर (!skb) अणु
		dev_warn(&card->dev->dev, "Failed to allocate sk_buff in send_command()\n");
		वापस 0;
	पूर्ण

	header = skb_put(skb, माप(*header));

	header->size = cpu_to_le16(size);
	header->vpi = cpu_to_le16(0);
	header->vci = cpu_to_le16(0);
	header->type = cpu_to_le16(PKT_COMMAND);

	skb_put_data(skb, buf, size);

	fpga_queue(card, dev, skb, शून्य);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार console_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा aपंचांग_dev *aपंचांगdev = container_of(dev, काष्ठा aपंचांग_dev, class_dev);
	काष्ठा solos_card *card = aपंचांगdev->dev_data;
	पूर्णांक err;

	err = send_command(card, SOLOS_CHAN(aपंचांगdev), buf, count);

	वापस err?:count;
पूर्ण

काष्ठा geos_gpio_attr अणु
	काष्ठा device_attribute attr;
	पूर्णांक offset;
पूर्ण;

#घोषणा SOLOS_GPIO_ATTR(_name, _mode, _show, _store, _offset)	\
	काष्ठा geos_gpio_attr gpio_attr_##_name = अणु		\
		.attr = __ATTR(_name, _mode, _show, _store),	\
		.offset = _offset पूर्ण

अटल sमाप_प्रकार geos_gpio_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा geos_gpio_attr *gattr = container_of(attr, काष्ठा geos_gpio_attr, attr);
	काष्ठा solos_card *card = dev_get_drvdata(dev);
	uपूर्णांक32_t data32;

	अगर (count != 1 && (count != 2 || buf[1] != '\n'))
		वापस -EINVAL;

	spin_lock_irq(&card->param_queue_lock);
	data32 = ioपढ़ो32(card->config_regs + GPIO_STATUS);
	अगर (buf[0] == '1') अणु
		data32 |= 1 << gattr->offset;
		ioग_लिखो32(data32, card->config_regs + GPIO_STATUS);
	पूर्ण अन्यथा अगर (buf[0] == '0') अणु
		data32 &= ~(1 << gattr->offset);
		ioग_लिखो32(data32, card->config_regs + GPIO_STATUS);
	पूर्ण अन्यथा अणु
		count = -EINVAL;
	पूर्ण
	spin_unlock_irq(&card->param_queue_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार geos_gpio_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा geos_gpio_attr *gattr = container_of(attr, काष्ठा geos_gpio_attr, attr);
	काष्ठा solos_card *card = dev_get_drvdata(dev);
	uपूर्णांक32_t data32;

	data32 = ioपढ़ो32(card->config_regs + GPIO_STATUS);
	data32 = (data32 >> gattr->offset) & 1;

	वापस प्र_लिखो(buf, "%d\n", data32);
पूर्ण

अटल sमाप_प्रकार hardware_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा geos_gpio_attr *gattr = container_of(attr, काष्ठा geos_gpio_attr, attr);
	काष्ठा solos_card *card = dev_get_drvdata(dev);
	uपूर्णांक32_t data32;

	data32 = ioपढ़ो32(card->config_regs + GPIO_STATUS);
	चयन (gattr->offset) अणु
	हाल 0:
		/* HardwareVersion */
		data32 = data32 & 0x1F;
		अवरोध;
	हाल 1:
		/* HardwareVariant */
		data32 = (data32 >> 5) & 0x0F;
		अवरोध;
	पूर्ण
	वापस प्र_लिखो(buf, "%d\n", data32);
पूर्ण

अटल DEVICE_ATTR_RW(console);


#घोषणा SOLOS_ATTR_RO(x) अटल DEVICE_ATTR(x, 0444, solos_param_show, शून्य);
#घोषणा SOLOS_ATTR_RW(x) अटल DEVICE_ATTR(x, 0644, solos_param_show, solos_param_store);

#समावेश "solos-attrlist.c"

अटल SOLOS_GPIO_ATTR(GPIO1, 0644, geos_gpio_show, geos_gpio_store, 9);
अटल SOLOS_GPIO_ATTR(GPIO2, 0644, geos_gpio_show, geos_gpio_store, 10);
अटल SOLOS_GPIO_ATTR(GPIO3, 0644, geos_gpio_show, geos_gpio_store, 11);
अटल SOLOS_GPIO_ATTR(GPIO4, 0644, geos_gpio_show, geos_gpio_store, 12);
अटल SOLOS_GPIO_ATTR(GPIO5, 0644, geos_gpio_show, geos_gpio_store, 13);
अटल SOLOS_GPIO_ATTR(PushButton, 0444, geos_gpio_show, शून्य, 14);
अटल SOLOS_GPIO_ATTR(HardwareVersion, 0444, hardware_show, शून्य, 0);
अटल SOLOS_GPIO_ATTR(HardwareVariant, 0444, hardware_show, शून्य, 1);
#अघोषित SOLOS_ATTR_RO
#अघोषित SOLOS_ATTR_RW

#घोषणा SOLOS_ATTR_RO(x) &dev_attr_##x.attr,
#घोषणा SOLOS_ATTR_RW(x) &dev_attr_##x.attr,

अटल काष्ठा attribute *solos_attrs[] = अणु
#समावेश "solos-attrlist.c"
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group solos_attr_group = अणु
	.attrs = solos_attrs,
	.name = "parameters",
पूर्ण;

अटल काष्ठा attribute *gpio_attrs[] = अणु
	&gpio_attr_GPIO1.attr.attr,
	&gpio_attr_GPIO2.attr.attr,
	&gpio_attr_GPIO3.attr.attr,
	&gpio_attr_GPIO4.attr.attr,
	&gpio_attr_GPIO5.attr.attr,
	&gpio_attr_PushButton.attr.attr,
	&gpio_attr_HardwareVersion.attr.attr,
	&gpio_attr_HardwareVariant.attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group gpio_attr_group = अणु
	.attrs = gpio_attrs,
	.name = "gpio",
पूर्ण;

अटल पूर्णांक flash_upgrade(काष्ठा solos_card *card, पूर्णांक chip)
अणु
	स्थिर काष्ठा firmware *fw;
	स्थिर अक्षर *fw_name;
	पूर्णांक blocksize = 0;
	पूर्णांक numblocks = 0;
	पूर्णांक offset;

	चयन (chip) अणु
	हाल 0:
		fw_name = "solos-FPGA.bin";
		अगर (card->aपंचांगel_flash)
			blocksize = ATMEL_FPGA_BLOCK;
		अन्यथा
			blocksize = SPI_FLASH_BLOCK;
		अवरोध;
	हाल 1:
		fw_name = "solos-Firmware.bin";
		अगर (card->aपंचांगel_flash)
			blocksize = ATMEL_SOLOS_BLOCK;
		अन्यथा
			blocksize = SPI_FLASH_BLOCK;
		अवरोध;
	हाल 2:
		अगर (card->fpga_version > LEGACY_BUFFERS)अणु
			fw_name = "solos-db-FPGA.bin";
			अगर (card->aपंचांगel_flash)
				blocksize = ATMEL_FPGA_BLOCK;
			अन्यथा
				blocksize = SPI_FLASH_BLOCK;
		पूर्ण अन्यथा अणु
			dev_info(&card->dev->dev, "FPGA version doesn't support"
					" daughter board upgrades\n");
			वापस -EPERM;
		पूर्ण
		अवरोध;
	हाल 3:
		अगर (card->fpga_version > LEGACY_BUFFERS)अणु
			fw_name = "solos-Firmware.bin";
			अगर (card->aपंचांगel_flash)
				blocksize = ATMEL_SOLOS_BLOCK;
			अन्यथा
				blocksize = SPI_FLASH_BLOCK;
		पूर्ण अन्यथा अणु
			dev_info(&card->dev->dev, "FPGA version doesn't support"
					" daughter board upgrades\n");
			वापस -EPERM;
		पूर्ण
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण

	अगर (request_firmware(&fw, fw_name, &card->dev->dev))
		वापस -ENOENT;

	dev_info(&card->dev->dev, "Flash upgrade starting\n");

	/* New FPGAs require driver version beक्रमe permitting flash upgrades */
	ioग_लिखो32(DRIVER_VERSION, card->config_regs + DRIVER_VER);

	numblocks = fw->size / blocksize;
	dev_info(&card->dev->dev, "Firmware size: %zd\n", fw->size);
	dev_info(&card->dev->dev, "Number of blocks: %d\n", numblocks);
	
	dev_info(&card->dev->dev, "Changing FPGA to Update mode\n");
	ioग_लिखो32(1, card->config_regs + FPGA_MODE);
	(व्योम) ioपढ़ो32(card->config_regs + FPGA_MODE); 

	/* Set mode to Chip Erase */
	अगर(chip == 0 || chip == 2)
		dev_info(&card->dev->dev, "Set FPGA Flash mode to FPGA Chip Erase\n");
	अगर(chip == 1 || chip == 3)
		dev_info(&card->dev->dev, "Set FPGA Flash mode to Solos Chip Erase\n");
	ioग_लिखो32((chip * 2), card->config_regs + FLASH_MODE);


	ioग_लिखो32(1, card->config_regs + WRITE_FLASH);
	रुको_event(card->fw_wq, !ioपढ़ो32(card->config_regs + FLASH_BUSY));

	क्रम (offset = 0; offset < fw->size; offset += blocksize) अणु
		पूर्णांक i;

		/* Clear ग_लिखो flag */
		ioग_लिखो32(0, card->config_regs + WRITE_FLASH);

		/* Set mode to Block Write */
		/* dev_info(&card->dev->dev, "Set FPGA Flash mode to Block Write\n"); */
		ioग_लिखो32(((chip * 2) + 1), card->config_regs + FLASH_MODE);

		/* Copy block to buffer, swapping each 16 bits क्रम Aपंचांगel flash */
		क्रम(i = 0; i < blocksize; i += 4) अणु
			uपूर्णांक32_t word;
			अगर (card->aपंचांगel_flash)
				word = swahb32p((uपूर्णांक32_t *)(fw->data + offset + i));
			अन्यथा
				word = *(uपूर्णांक32_t *)(fw->data + offset + i);
			अगर(card->fpga_version > LEGACY_BUFFERS)
				ioग_लिखो32(word, FLASH_BUF + i);
			अन्यथा
				ioग_लिखो32(word, RX_BUF(card, 3) + i);
		पूर्ण

		/* Specअगरy block number and then trigger flash ग_लिखो */
		ioग_लिखो32(offset / blocksize, card->config_regs + FLASH_BLOCK);
		ioग_लिखो32(1, card->config_regs + WRITE_FLASH);
		रुको_event(card->fw_wq, !ioपढ़ो32(card->config_regs + FLASH_BUSY));
	पूर्ण

	release_firmware(fw);
	ioग_लिखो32(0, card->config_regs + WRITE_FLASH);
	ioग_लिखो32(0, card->config_regs + FPGA_MODE);
	ioग_लिखो32(0, card->config_regs + FLASH_MODE);
	dev_info(&card->dev->dev, "Returning FPGA to Data mode\n");
	वापस 0;
पूर्ण

अटल irqवापस_t solos_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा solos_card *card = dev_id;
	पूर्णांक handled = 1;

	ioग_लिखो32(0, card->config_regs + IRQ_CLEAR);

	/* If we're up and running, just kick the tasklet to process TX/RX */
	अगर (card->aपंचांगdev[0])
		tasklet_schedule(&card->tlet);
	अन्यथा
		wake_up(&card->fw_wq);

	वापस IRQ_RETVAL(handled);
पूर्ण

अटल व्योम solos_bh(अचिन्हित दीर्घ card_arg)
अणु
	काष्ठा solos_card *card = (व्योम *)card_arg;
	uपूर्णांक32_t card_flags;
	uपूर्णांक32_t rx_करोne = 0;
	पूर्णांक port;

	/*
	 * Since fpga_tx() is going to need to पढ़ो the flags under its lock,
	 * it can वापस them to us so that we करोn't have to hit PCI MMIO
	 * again क्रम the same inक्रमmation
	 */
	card_flags = fpga_tx(card);

	क्रम (port = 0; port < card->nr_ports; port++) अणु
		अगर (card_flags & (0x10 << port)) अणु
			काष्ठा pkt_hdr _hdr, *header;
			काष्ठा sk_buff *skb;
			काष्ठा aपंचांग_vcc *vcc;
			पूर्णांक size;

			अगर (card->using_dma) अणु
				skb = card->rx_skb[port];
				card->rx_skb[port] = शून्य;

				dma_unmap_single(&card->dev->dev, SKB_CB(skb)->dma_addr,
						 RX_DMA_SIZE, DMA_FROM_DEVICE);

				header = (व्योम *)skb->data;
				size = le16_to_cpu(header->size);
				skb_put(skb, size + माप(*header));
				skb_pull(skb, माप(*header));
			पूर्ण अन्यथा अणु
				header = &_hdr;

				rx_करोne |= 0x10 << port;

				स_नकल_fromio(header, RX_BUF(card, port), माप(*header));

				size = le16_to_cpu(header->size);
				अगर (size > (card->buffer_size - माप(*header)))अणु
					dev_warn(&card->dev->dev, "Invalid buffer size\n");
					जारी;
				पूर्ण

				/* Use netdev_alloc_skb() because it adds NET_SKB_PAD of
				 * headroom, and ensures we can route packets back out an
				 * Ethernet पूर्णांकerface (क्रम example) without having to
				 * पुनः_स्मृतिate. Adding NET_IP_ALIGN also ensures that both
				 * PPPoATM and PPPoEoBR2684 packets end up aligned. */
				skb = netdev_alloc_skb_ip_align(शून्य, size + 1);
				अगर (!skb) अणु
					अगर (net_ratelimit())
						dev_warn(&card->dev->dev, "Failed to allocate sk_buff for RX\n");
					जारी;
				पूर्ण

				स_नकल_fromio(skb_put(skb, size),
					      RX_BUF(card, port) + माप(*header),
					      size);
			पूर्ण
			अगर (aपंचांगdebug) अणु
				dev_info(&card->dev->dev, "Received: port %d\n", port);
				dev_info(&card->dev->dev, "size: %d VPI: %d VCI: %d\n",
					 size, le16_to_cpu(header->vpi),
					 le16_to_cpu(header->vci));
				prपूर्णांक_buffer(skb);
			पूर्ण

			चयन (le16_to_cpu(header->type)) अणु
			हाल PKT_DATA:
				vcc = find_vcc(card->aपंचांगdev[port], le16_to_cpu(header->vpi),
					       le16_to_cpu(header->vci));
				अगर (!vcc) अणु
					अगर (net_ratelimit())
						dev_warn(&card->dev->dev, "Received packet for unknown VPI.VCI %d.%d on port %d\n",
							 le16_to_cpu(header->vpi), le16_to_cpu(header->vci),
							 port);
					dev_kमुक्त_skb_any(skb);
					अवरोध;
				पूर्ण
				aपंचांग_अक्षरge(vcc, skb->truesize);
				vcc->push(vcc, skb);
				atomic_inc(&vcc->stats->rx);
				अवरोध;

			हाल PKT_STATUS:
				अगर (process_status(card, port, skb) &&
				    net_ratelimit()) अणु
					dev_warn(&card->dev->dev, "Bad status packet of %d bytes on port %d:\n", skb->len, port);
					prपूर्णांक_buffer(skb);
				पूर्ण
				dev_kमुक्त_skb_any(skb);
				अवरोध;

			हाल PKT_COMMAND:
			शेष: /* FIXME: Not really, surely? */
				अगर (process_command(card, port, skb))
					अवरोध;
				spin_lock(&card->cli_queue_lock);
				अगर (skb_queue_len(&card->cli_queue[port]) > 10) अणु
					अगर (net_ratelimit())
						dev_warn(&card->dev->dev, "Dropping console response on port %d\n",
							 port);
					dev_kमुक्त_skb_any(skb);
				पूर्ण अन्यथा
					skb_queue_tail(&card->cli_queue[port], skb);
				spin_unlock(&card->cli_queue_lock);
				अवरोध;
			पूर्ण
		पूर्ण
		/* Allocate RX skbs क्रम any ports which need them */
		अगर (card->using_dma && card->aपंचांगdev[port] &&
		    !card->rx_skb[port]) अणु
			/* Unlike the MMIO हाल (qv) we can't add NET_IP_ALIGN
			 * here; the FPGA can only DMA to addresses which are
			 * aligned to 4 bytes. */
			काष्ठा sk_buff *skb = dev_alloc_skb(RX_DMA_SIZE);
			अगर (skb) अणु
				SKB_CB(skb)->dma_addr =
					dma_map_single(&card->dev->dev, skb->data,
						       RX_DMA_SIZE, DMA_FROM_DEVICE);
				ioग_लिखो32(SKB_CB(skb)->dma_addr,
					  card->config_regs + RX_DMA_ADDR(port));
				card->rx_skb[port] = skb;
			पूर्ण अन्यथा अणु
				अगर (net_ratelimit())
					dev_warn(&card->dev->dev, "Failed to allocate RX skb");

				/* We'll have to try again later */
				tasklet_schedule(&card->tlet);
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (rx_करोne)
		ioग_लिखो32(rx_करोne, card->config_regs + FLAGS_ADDR);

	वापस;
पूर्ण

अटल काष्ठा aपंचांग_vcc *find_vcc(काष्ठा aपंचांग_dev *dev, लघु vpi, पूर्णांक vci)
अणु
	काष्ठा hlist_head *head;
	काष्ठा aपंचांग_vcc *vcc = शून्य;
	काष्ठा sock *s;

	पढ़ो_lock(&vcc_sklist_lock);
	head = &vcc_hash[vci & (VCC_HTABLE_SIZE -1)];
	sk_क्रम_each(s, head) अणु
		vcc = aपंचांग_sk(s);
		अगर (vcc->dev == dev && vcc->vci == vci &&
		    vcc->vpi == vpi && vcc->qos.rxtp.traffic_class != ATM_NONE &&
		    test_bit(ATM_VF_READY, &vcc->flags))
			जाओ out;
	पूर्ण
	vcc = शून्य;
 out:
	पढ़ो_unlock(&vcc_sklist_lock);
	वापस vcc;
पूर्ण

अटल पूर्णांक pखोलो(काष्ठा aपंचांग_vcc *vcc)
अणु
	काष्ठा solos_card *card = vcc->dev->dev_data;
	काष्ठा sk_buff *skb;
	काष्ठा pkt_hdr *header;

	अगर (vcc->qos.aal != ATM_AAL5) अणु
		dev_warn(&card->dev->dev, "Unsupported ATM type %d\n",
			 vcc->qos.aal);
		वापस -EINVAL;
	पूर्ण

	skb = alloc_skb(माप(*header), GFP_KERNEL);
	अगर (!skb) अणु
		अगर (net_ratelimit())
			dev_warn(&card->dev->dev, "Failed to allocate sk_buff in popen()\n");
		वापस -ENOMEM;
	पूर्ण
	header = skb_put(skb, माप(*header));

	header->size = cpu_to_le16(0);
	header->vpi = cpu_to_le16(vcc->vpi);
	header->vci = cpu_to_le16(vcc->vci);
	header->type = cpu_to_le16(PKT_POPEN);

	fpga_queue(card, SOLOS_CHAN(vcc->dev), skb, शून्य);

	set_bit(ATM_VF_ADDR, &vcc->flags);
	set_bit(ATM_VF_READY, &vcc->flags);

	वापस 0;
पूर्ण

अटल व्योम pबंद(काष्ठा aपंचांग_vcc *vcc)
अणु
	काष्ठा solos_card *card = vcc->dev->dev_data;
	अचिन्हित अक्षर port = SOLOS_CHAN(vcc->dev);
	काष्ठा sk_buff *skb, *पंचांगpskb;
	काष्ठा pkt_hdr *header;

	/* Remove any yet-to-be-transmitted packets from the pending queue */
	spin_lock(&card->tx_queue_lock);
	skb_queue_walk_safe(&card->tx_queue[port], skb, पंचांगpskb) अणु
		अगर (SKB_CB(skb)->vcc == vcc) अणु
			skb_unlink(skb, &card->tx_queue[port]);
			solos_pop(vcc, skb);
		पूर्ण
	पूर्ण
	spin_unlock(&card->tx_queue_lock);

	skb = alloc_skb(माप(*header), GFP_KERNEL);
	अगर (!skb) अणु
		dev_warn(&card->dev->dev, "Failed to allocate sk_buff in pclose()\n");
		वापस;
	पूर्ण
	header = skb_put(skb, माप(*header));

	header->size = cpu_to_le16(0);
	header->vpi = cpu_to_le16(vcc->vpi);
	header->vci = cpu_to_le16(vcc->vci);
	header->type = cpu_to_le16(PKT_PCLOSE);

	skb_get(skb);
	fpga_queue(card, port, skb, शून्य);

	अगर (!रुको_event_समयout(card->param_wq, !skb_shared(skb), 5 * HZ))
		dev_warn(&card->dev->dev,
			 "Timeout waiting for VCC close on port %d\n", port);

	dev_kमुक्त_skb(skb);

	/* Hold up vcc_destroy_socket() (our caller) until solos_bh() in the
	   tasklet has finished processing any incoming packets (and, more to
	   the poपूर्णांक, using the vcc poपूर्णांकer). */
	tasklet_unlock_रुको(&card->tlet);

	clear_bit(ATM_VF_ADDR, &vcc->flags);

	वापस;
पूर्ण

अटल पूर्णांक prपूर्णांक_buffer(काष्ठा sk_buff *buf)
अणु
	पूर्णांक len,i;
	अक्षर msg[500];
	अक्षर item[10];

	len = buf->len;
	क्रम (i = 0; i < len; i++)अणु
		अगर(i % 8 == 0)
			प्र_लिखो(msg, "%02X: ", i);

		प्र_लिखो(item,"%02X ",*(buf->data + i));
		म_जोड़ो(msg, item);
		अगर(i % 8 == 7) अणु
			प्र_लिखो(item, "\n");
			म_जोड़ो(msg, item);
			prपूर्णांकk(KERN_DEBUG "%s", msg);
		पूर्ण
	पूर्ण
	अगर (i % 8 != 0) अणु
		प्र_लिखो(item, "\n");
		म_जोड़ो(msg, item);
		prपूर्णांकk(KERN_DEBUG "%s", msg);
	पूर्ण
	prपूर्णांकk(KERN_DEBUG "\n");

	वापस 0;
पूर्ण

अटल व्योम fpga_queue(काष्ठा solos_card *card, पूर्णांक port, काष्ठा sk_buff *skb,
		       काष्ठा aपंचांग_vcc *vcc)
अणु
	पूर्णांक old_len;
	अचिन्हित दीर्घ flags;

	SKB_CB(skb)->vcc = vcc;

	spin_lock_irqsave(&card->tx_queue_lock, flags);
	old_len = skb_queue_len(&card->tx_queue[port]);
	skb_queue_tail(&card->tx_queue[port], skb);
	अगर (!old_len)
		card->tx_mask |= (1 << port);
	spin_unlock_irqrestore(&card->tx_queue_lock, flags);

	/* Theoretically we could just schedule the tasklet here, but
	   that पूर्णांकroduces latency we करोn't want -- it's noticeable */
	अगर (!old_len)
		fpga_tx(card);
पूर्ण

अटल uपूर्णांक32_t fpga_tx(काष्ठा solos_card *card)
अणु
	uपूर्णांक32_t tx_pending, card_flags;
	uपूर्णांक32_t tx_started = 0;
	काष्ठा sk_buff *skb;
	काष्ठा aपंचांग_vcc *vcc;
	अचिन्हित अक्षर port;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&card->tx_lock, flags);
	
	card_flags = ioपढ़ो32(card->config_regs + FLAGS_ADDR);
	/*
	 * The queue lock is required क्रम _writing_ to tx_mask, but we're
	 * OK to पढ़ो it here without locking. The only potential update
	 * that we could race with is in fpga_queue() where it sets a bit
	 * क्रम a new port... but it's going to call this function again अगर
	 * it's करोing that, anyway.
	 */
	tx_pending = card->tx_mask & ~card_flags;

	क्रम (port = 0; tx_pending; tx_pending >>= 1, port++) अणु
		अगर (tx_pending & 1) अणु
			काष्ठा sk_buff *oldskb = card->tx_skb[port];
			अगर (oldskb) अणु
				dma_unmap_single(&card->dev->dev, SKB_CB(oldskb)->dma_addr,
						 oldskb->len, DMA_TO_DEVICE);
				card->tx_skb[port] = शून्य;
			पूर्ण
			spin_lock(&card->tx_queue_lock);
			skb = skb_dequeue(&card->tx_queue[port]);
			अगर (!skb)
				card->tx_mask &= ~(1 << port);
			spin_unlock(&card->tx_queue_lock);

			अगर (skb && !card->using_dma) अणु
				स_नकल_toio(TX_BUF(card, port), skb->data, skb->len);
				tx_started |= 1 << port;
				oldskb = skb; /* We're करोne with this skb alपढ़ोy */
			पूर्ण अन्यथा अगर (skb && card->using_dma) अणु
				अचिन्हित अक्षर *data = skb->data;
				अगर ((अचिन्हित दीर्घ)data & card->dma_alignment) अणु
					data = card->dma_bounce + (BUF_SIZE * port);
					स_नकल(data, skb->data, skb->len);
				पूर्ण
				SKB_CB(skb)->dma_addr = dma_map_single(&card->dev->dev, data,
								       skb->len, DMA_TO_DEVICE);
				card->tx_skb[port] = skb;
				ioग_लिखो32(SKB_CB(skb)->dma_addr,
					  card->config_regs + TX_DMA_ADDR(port));
			पूर्ण

			अगर (!oldskb)
				जारी;

			/* Clean up and मुक्त oldskb now it's gone */
			अगर (aपंचांगdebug) अणु
				काष्ठा pkt_hdr *header = (व्योम *)oldskb->data;
				पूर्णांक size = le16_to_cpu(header->size);

				skb_pull(oldskb, माप(*header));
				dev_info(&card->dev->dev, "Transmitted: port %d\n",
					 port);
				dev_info(&card->dev->dev, "size: %d VPI: %d VCI: %d\n",
					 size, le16_to_cpu(header->vpi),
					 le16_to_cpu(header->vci));
				prपूर्णांक_buffer(oldskb);
			पूर्ण

			vcc = SKB_CB(oldskb)->vcc;

			अगर (vcc) अणु
				atomic_inc(&vcc->stats->tx);
				solos_pop(vcc, oldskb);
			पूर्ण अन्यथा अणु
				dev_kमुक्त_skb_irq(oldskb);
				wake_up(&card->param_wq);
			पूर्ण
		पूर्ण
	पूर्ण
	/* For non-DMA TX, ग_लिखो the 'TX start' bit क्रम all four ports simultaneously */
	अगर (tx_started)
		ioग_लिखो32(tx_started, card->config_regs + FLAGS_ADDR);

	spin_unlock_irqrestore(&card->tx_lock, flags);
	वापस card_flags;
पूर्ण

अटल पूर्णांक psend(काष्ठा aपंचांग_vcc *vcc, काष्ठा sk_buff *skb)
अणु
	काष्ठा solos_card *card = vcc->dev->dev_data;
	काष्ठा pkt_hdr *header;
	पूर्णांक pktlen;

	pktlen = skb->len;
	अगर (pktlen > (BUF_SIZE - माप(*header))) अणु
		dev_warn(&card->dev->dev, "Length of PDU is too large. Dropping PDU.\n");
		solos_pop(vcc, skb);
		वापस 0;
	पूर्ण

	अगर (!skb_clone_writable(skb, माप(*header))) अणु
		पूर्णांक expand_by = 0;
		पूर्णांक ret;

		अगर (skb_headroom(skb) < माप(*header))
			expand_by = माप(*header) - skb_headroom(skb);

		ret = pskb_expand_head(skb, expand_by, 0, GFP_ATOMIC);
		अगर (ret) अणु
			dev_warn(&card->dev->dev, "pskb_expand_head failed.\n");
			solos_pop(vcc, skb);
			वापस ret;
		पूर्ण
	पूर्ण

	header = skb_push(skb, माप(*header));

	/* This करोes _not_ include the size of the header */
	header->size = cpu_to_le16(pktlen);
	header->vpi = cpu_to_le16(vcc->vpi);
	header->vci = cpu_to_le16(vcc->vci);
	header->type = cpu_to_le16(PKT_DATA);

	fpga_queue(card, SOLOS_CHAN(vcc->dev), skb, vcc);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा aपंचांगdev_ops fpga_ops = अणु
	.खोलो =		pखोलो,
	.बंद =	pबंद,
	.ioctl =	शून्य,
	.send =		psend,
	.send_oam =	शून्य,
	.phy_put =	शून्य,
	.phy_get =	शून्य,
	.change_qos =	शून्य,
	.proc_पढ़ो =	शून्य,
	.owner =	THIS_MODULE
पूर्ण;

अटल पूर्णांक fpga_probe(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	पूर्णांक err;
	uपूर्णांक16_t fpga_ver;
	uपूर्णांक8_t major_ver, minor_ver;
	uपूर्णांक32_t data32;
	काष्ठा solos_card *card;

	card = kzalloc(माप(*card), GFP_KERNEL);
	अगर (!card)
		वापस -ENOMEM;

	card->dev = dev;
	init_रुकोqueue_head(&card->fw_wq);
	init_रुकोqueue_head(&card->param_wq);

	err = pci_enable_device(dev);
	अगर (err) अणु
		dev_warn(&dev->dev,  "Failed to enable PCI device\n");
		जाओ out;
	पूर्ण

	err = dma_set_mask_and_coherent(&dev->dev, DMA_BIT_MASK(32));
	अगर (err) अणु
		dev_warn(&dev->dev, "Failed to set 32-bit DMA mask\n");
		जाओ out;
	पूर्ण

	err = pci_request_regions(dev, "solos");
	अगर (err) अणु
		dev_warn(&dev->dev, "Failed to request regions\n");
		जाओ out;
	पूर्ण

	card->config_regs = pci_iomap(dev, 0, CONFIG_RAM_SIZE);
	अगर (!card->config_regs) अणु
		dev_warn(&dev->dev, "Failed to ioremap config registers\n");
		err = -ENOMEM;
		जाओ out_release_regions;
	पूर्ण
	card->buffers = pci_iomap(dev, 1, DATA_RAM_SIZE);
	अगर (!card->buffers) अणु
		dev_warn(&dev->dev, "Failed to ioremap data buffers\n");
		err = -ENOMEM;
		जाओ out_unmap_config;
	पूर्ण

	अगर (reset) अणु
		ioग_लिखो32(1, card->config_regs + FPGA_MODE);
		ioपढ़ो32(card->config_regs + FPGA_MODE);

		ioग_लिखो32(0, card->config_regs + FPGA_MODE);
		ioपढ़ो32(card->config_regs + FPGA_MODE);
	पूर्ण

	data32 = ioपढ़ो32(card->config_regs + FPGA_VER);
	fpga_ver = (data32 & 0x0000FFFF);
	major_ver = ((data32 & 0xFF000000) >> 24);
	minor_ver = ((data32 & 0x00FF0000) >> 16);
	card->fpga_version = FPGA_VERSION(major_ver,minor_ver);
	अगर (card->fpga_version > LEGACY_BUFFERS)
		card->buffer_size = BUF_SIZE;
	अन्यथा
		card->buffer_size = OLD_BUF_SIZE;
	dev_info(&dev->dev, "Solos FPGA Version %d.%02d svn-%d\n",
		 major_ver, minor_ver, fpga_ver);

	अगर (fpga_ver < 37 && (fpga_upgrade || firmware_upgrade ||
			      db_fpga_upgrade || db_firmware_upgrade)) अणु
		dev_warn(&dev->dev,
			 "FPGA too old; cannot upgrade flash. Use JTAG.\n");
		fpga_upgrade = firmware_upgrade = 0;
		db_fpga_upgrade = db_firmware_upgrade = 0;
	पूर्ण

	/* Stopped using Aपंचांगel flash after 0.03-38 */
	अगर (fpga_ver < 39)
		card->aपंचांगel_flash = 1;
	अन्यथा
		card->aपंचांगel_flash = 0;

	data32 = ioपढ़ो32(card->config_regs + PORTS);
	card->nr_ports = (data32 & 0x000000FF);

	अगर (card->fpga_version >= DMA_SUPPORTED) अणु
		pci_set_master(dev);
		card->using_dma = 1;
		अगर (1) अणु /* All known FPGA versions so far */
			card->dma_alignment = 3;
			card->dma_bounce = kदो_स्मृति_array(card->nr_ports,
							 BUF_SIZE, GFP_KERNEL);
			अगर (!card->dma_bounce) अणु
				dev_warn(&card->dev->dev, "Failed to allocate DMA bounce buffers\n");
				err = -ENOMEM;
				/* Fallback to MMIO करोesn't work */
				जाओ out_unmap_both;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		card->using_dma = 0;
		/* Set RX empty flag क्रम all ports */
		ioग_लिखो32(0xF0, card->config_regs + FLAGS_ADDR);
	पूर्ण

	pci_set_drvdata(dev, card);

	tasklet_init(&card->tlet, solos_bh, (अचिन्हित दीर्घ)card);
	spin_lock_init(&card->tx_lock);
	spin_lock_init(&card->tx_queue_lock);
	spin_lock_init(&card->cli_queue_lock);
	spin_lock_init(&card->param_queue_lock);
	INIT_LIST_HEAD(&card->param_queue);

	err = request_irq(dev->irq, solos_irq, IRQF_SHARED,
			  "solos-pci", card);
	अगर (err) अणु
		dev_dbg(&card->dev->dev, "Failed to request interrupt IRQ: %d\n", dev->irq);
		जाओ out_unmap_both;
	पूर्ण

	ioग_लिखो32(1, card->config_regs + IRQ_EN_ADDR);

	अगर (fpga_upgrade)
		flash_upgrade(card, 0);

	अगर (firmware_upgrade)
		flash_upgrade(card, 1);

	अगर (db_fpga_upgrade)
		flash_upgrade(card, 2);

	अगर (db_firmware_upgrade)
		flash_upgrade(card, 3);

	err = aपंचांग_init(card, &dev->dev);
	अगर (err)
		जाओ out_मुक्त_irq;

	अगर (card->fpga_version >= DMA_SUPPORTED &&
	    sysfs_create_group(&card->dev->dev.kobj, &gpio_attr_group))
		dev_err(&card->dev->dev, "Could not register parameter group for GPIOs\n");

	वापस 0;

 out_मुक्त_irq:
	ioग_लिखो32(0, card->config_regs + IRQ_EN_ADDR);
	मुक्त_irq(dev->irq, card);
	tasklet_समाप्त(&card->tlet);
	
 out_unmap_both:
	kमुक्त(card->dma_bounce);
	pci_iounmap(dev, card->buffers);
 out_unmap_config:
	pci_iounmap(dev, card->config_regs);
 out_release_regions:
	pci_release_regions(dev);
 out:
	kमुक्त(card);
	वापस err;
पूर्ण

अटल पूर्णांक aपंचांग_init(काष्ठा solos_card *card, काष्ठा device *parent)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < card->nr_ports; i++) अणु
		काष्ठा sk_buff *skb;
		काष्ठा pkt_hdr *header;

		skb_queue_head_init(&card->tx_queue[i]);
		skb_queue_head_init(&card->cli_queue[i]);

		card->aपंचांगdev[i] = aपंचांग_dev_रेजिस्टर("solos-pci", parent, &fpga_ops, -1, शून्य);
		अगर (!card->aपंचांगdev[i]) अणु
			dev_err(&card->dev->dev, "Could not register ATM device %d\n", i);
			aपंचांग_हटाओ(card);
			वापस -ENODEV;
		पूर्ण
		अगर (device_create_file(&card->aपंचांगdev[i]->class_dev, &dev_attr_console))
			dev_err(&card->dev->dev, "Could not register console for ATM device %d\n", i);
		अगर (sysfs_create_group(&card->aपंचांगdev[i]->class_dev.kobj, &solos_attr_group))
			dev_err(&card->dev->dev, "Could not register parameter group for ATM device %d\n", i);

		dev_info(&card->dev->dev, "Registered ATM device %d\n", card->aपंचांगdev[i]->number);

		card->aपंचांगdev[i]->ci_range.vpi_bits = 8;
		card->aपंचांगdev[i]->ci_range.vci_bits = 16;
		card->aपंचांगdev[i]->dev_data = card;
		card->aपंचांगdev[i]->phy_data = (व्योम *)(अचिन्हित दीर्घ)i;
		aपंचांग_dev_संकेत_change(card->aपंचांगdev[i], ATM_PHY_SIG_FOUND);

		skb = alloc_skb(माप(*header), GFP_KERNEL);
		अगर (!skb) अणु
			dev_warn(&card->dev->dev, "Failed to allocate sk_buff in atm_init()\n");
			जारी;
		पूर्ण

		header = skb_put(skb, माप(*header));

		header->size = cpu_to_le16(0);
		header->vpi = cpu_to_le16(0);
		header->vci = cpu_to_le16(0);
		header->type = cpu_to_le16(PKT_STATUS);

		fpga_queue(card, i, skb, शून्य);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम aपंचांग_हटाओ(काष्ठा solos_card *card)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < card->nr_ports; i++) अणु
		अगर (card->aपंचांगdev[i]) अणु
			काष्ठा sk_buff *skb;

			dev_info(&card->dev->dev, "Unregistering ATM device %d\n", card->aपंचांगdev[i]->number);

			sysfs_हटाओ_group(&card->aपंचांगdev[i]->class_dev.kobj, &solos_attr_group);
			aपंचांग_dev_deरेजिस्टर(card->aपंचांगdev[i]);

			skb = card->rx_skb[i];
			अगर (skb) अणु
				dma_unmap_single(&card->dev->dev, SKB_CB(skb)->dma_addr,
						 RX_DMA_SIZE, DMA_FROM_DEVICE);
				dev_kमुक्त_skb(skb);
			पूर्ण
			skb = card->tx_skb[i];
			अगर (skb) अणु
				dma_unmap_single(&card->dev->dev, SKB_CB(skb)->dma_addr,
						 skb->len, DMA_TO_DEVICE);
				dev_kमुक्त_skb(skb);
			पूर्ण
			जबतक ((skb = skb_dequeue(&card->tx_queue[i])))
				dev_kमुक्त_skb(skb);
 
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम fpga_हटाओ(काष्ठा pci_dev *dev)
अणु
	काष्ठा solos_card *card = pci_get_drvdata(dev);
	
	/* Disable IRQs */
	ioग_लिखो32(0, card->config_regs + IRQ_EN_ADDR);

	/* Reset FPGA */
	ioग_लिखो32(1, card->config_regs + FPGA_MODE);
	(व्योम)ioपढ़ो32(card->config_regs + FPGA_MODE); 

	अगर (card->fpga_version >= DMA_SUPPORTED)
		sysfs_हटाओ_group(&card->dev->dev.kobj, &gpio_attr_group);

	aपंचांग_हटाओ(card);

	मुक्त_irq(dev->irq, card);
	tasklet_समाप्त(&card->tlet);

	kमुक्त(card->dma_bounce);

	/* Release device from reset */
	ioग_लिखो32(0, card->config_regs + FPGA_MODE);
	(व्योम)ioपढ़ो32(card->config_regs + FPGA_MODE); 

	pci_iounmap(dev, card->buffers);
	pci_iounmap(dev, card->config_regs);

	pci_release_regions(dev);
	pci_disable_device(dev);

	kमुक्त(card);
पूर्ण

अटल स्थिर काष्ठा pci_device_id fpga_pci_tbl[] = अणु
	अणु 0x10ee, 0x0300, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci,fpga_pci_tbl);

अटल काष्ठा pci_driver fpga_driver = अणु
	.name =		"solos",
	.id_table =	fpga_pci_tbl,
	.probe =	fpga_probe,
	.हटाओ =	fpga_हटाओ,
पूर्ण;


अटल पूर्णांक __init solos_pci_init(व्योम)
अणु
	BUILD_BUG_ON(माप(काष्ठा solos_skb_cb) > माप(((काष्ठा sk_buff *)0)->cb));

	prपूर्णांकk(KERN_INFO "Solos PCI Driver Version %s\n", VERSION);
	वापस pci_रेजिस्टर_driver(&fpga_driver);
पूर्ण

अटल व्योम __निकास solos_pci_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&fpga_driver);
	prपूर्णांकk(KERN_INFO "Solos PCI Driver %s Unloaded\n", VERSION);
पूर्ण

module_init(solos_pci_init);
module_निकास(solos_pci_निकास);
