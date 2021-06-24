<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (c) 2015-2016, IBM Corporation.
 */

#समावेश <linux/atomic.h>
#समावेश <linux/bt-bmc.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/poll.h>
#समावेश <linux/regmap.h>
#समावेश <linux/sched.h>
#समावेश <linux/समयr.h>

/*
 * This is a BMC device used to communicate to the host
 */
#घोषणा DEVICE_NAME	"ipmi-bt-host"

#घोषणा BT_IO_BASE	0xe4
#घोषणा BT_IRQ		10

#घोषणा BT_CR0		0x0
#घोषणा   BT_CR0_IO_BASE		16
#घोषणा   BT_CR0_IRQ			12
#घोषणा   BT_CR0_EN_CLR_SLV_RDP		0x8
#घोषणा   BT_CR0_EN_CLR_SLV_WRP		0x4
#घोषणा   BT_CR0_ENABLE_IBT		0x1
#घोषणा BT_CR1		0x4
#घोषणा   BT_CR1_IRQ_H2B	0x01
#घोषणा   BT_CR1_IRQ_HBUSY	0x40
#घोषणा BT_CR2		0x8
#घोषणा   BT_CR2_IRQ_H2B	0x01
#घोषणा   BT_CR2_IRQ_HBUSY	0x40
#घोषणा BT_CR3		0xc
#घोषणा BT_CTRL		0x10
#घोषणा   BT_CTRL_B_BUSY		0x80
#घोषणा   BT_CTRL_H_BUSY		0x40
#घोषणा   BT_CTRL_OEM0			0x20
#घोषणा   BT_CTRL_SMS_ATN		0x10
#घोषणा   BT_CTRL_B2H_ATN		0x08
#घोषणा   BT_CTRL_H2B_ATN		0x04
#घोषणा   BT_CTRL_CLR_RD_PTR		0x02
#घोषणा   BT_CTRL_CLR_WR_PTR		0x01
#घोषणा BT_BMC2HOST	0x14
#घोषणा BT_INTMASK	0x18
#घोषणा   BT_INTMASK_B2H_IRQEN		0x01
#घोषणा   BT_INTMASK_B2H_IRQ		0x02
#घोषणा   BT_INTMASK_BMC_HWRST		0x80

#घोषणा BT_BMC_BUFFER_SIZE 256

काष्ठा bt_bmc अणु
	काष्ठा device		dev;
	काष्ठा miscdevice	miscdev;
	काष्ठा regmap		*map;
	पूर्णांक			offset;
	पूर्णांक			irq;
	रुको_queue_head_t	queue;
	काष्ठा समयr_list	poll_समयr;
	काष्ठा mutex		mutex;
पूर्ण;

अटल atomic_t खोलो_count = ATOMIC_INIT(0);

अटल स्थिर काष्ठा regmap_config bt_regmap_cfg = अणु
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = 4,
पूर्ण;

अटल u8 bt_inb(काष्ठा bt_bmc *bt_bmc, पूर्णांक reg)
अणु
	uपूर्णांक32_t val = 0;
	पूर्णांक rc;

	rc = regmap_पढ़ो(bt_bmc->map, bt_bmc->offset + reg, &val);
	WARN(rc != 0, "regmap_read() failed: %d\n", rc);

	वापस rc == 0 ? (u8) val : 0;
पूर्ण

अटल व्योम bt_outb(काष्ठा bt_bmc *bt_bmc, u8 data, पूर्णांक reg)
अणु
	पूर्णांक rc;

	rc = regmap_ग_लिखो(bt_bmc->map, bt_bmc->offset + reg, data);
	WARN(rc != 0, "regmap_write() failed: %d\n", rc);
पूर्ण

अटल व्योम clr_rd_ptr(काष्ठा bt_bmc *bt_bmc)
अणु
	bt_outb(bt_bmc, BT_CTRL_CLR_RD_PTR, BT_CTRL);
पूर्ण

अटल व्योम clr_wr_ptr(काष्ठा bt_bmc *bt_bmc)
अणु
	bt_outb(bt_bmc, BT_CTRL_CLR_WR_PTR, BT_CTRL);
पूर्ण

अटल व्योम clr_h2b_atn(काष्ठा bt_bmc *bt_bmc)
अणु
	bt_outb(bt_bmc, BT_CTRL_H2B_ATN, BT_CTRL);
पूर्ण

अटल व्योम set_b_busy(काष्ठा bt_bmc *bt_bmc)
अणु
	अगर (!(bt_inb(bt_bmc, BT_CTRL) & BT_CTRL_B_BUSY))
		bt_outb(bt_bmc, BT_CTRL_B_BUSY, BT_CTRL);
पूर्ण

अटल व्योम clr_b_busy(काष्ठा bt_bmc *bt_bmc)
अणु
	अगर (bt_inb(bt_bmc, BT_CTRL) & BT_CTRL_B_BUSY)
		bt_outb(bt_bmc, BT_CTRL_B_BUSY, BT_CTRL);
पूर्ण

अटल व्योम set_b2h_atn(काष्ठा bt_bmc *bt_bmc)
अणु
	bt_outb(bt_bmc, BT_CTRL_B2H_ATN, BT_CTRL);
पूर्ण

अटल u8 bt_पढ़ो(काष्ठा bt_bmc *bt_bmc)
अणु
	वापस bt_inb(bt_bmc, BT_BMC2HOST);
पूर्ण

अटल sमाप_प्रकार bt_पढ़ोn(काष्ठा bt_bmc *bt_bmc, u8 *buf, माप_प्रकार n)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < n; i++)
		buf[i] = bt_पढ़ो(bt_bmc);
	वापस n;
पूर्ण

अटल व्योम bt_ग_लिखो(काष्ठा bt_bmc *bt_bmc, u8 c)
अणु
	bt_outb(bt_bmc, c, BT_BMC2HOST);
पूर्ण

अटल sमाप_प्रकार bt_ग_लिखोn(काष्ठा bt_bmc *bt_bmc, u8 *buf, माप_प्रकार n)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < n; i++)
		bt_ग_लिखो(bt_bmc, buf[i]);
	वापस n;
पूर्ण

अटल व्योम set_sms_atn(काष्ठा bt_bmc *bt_bmc)
अणु
	bt_outb(bt_bmc, BT_CTRL_SMS_ATN, BT_CTRL);
पूर्ण

अटल काष्ठा bt_bmc *file_bt_bmc(काष्ठा file *file)
अणु
	वापस container_of(file->निजी_data, काष्ठा bt_bmc, miscdev);
पूर्ण

अटल पूर्णांक bt_bmc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा bt_bmc *bt_bmc = file_bt_bmc(file);

	अगर (atomic_inc_वापस(&खोलो_count) == 1) अणु
		clr_b_busy(bt_bmc);
		वापस 0;
	पूर्ण

	atomic_dec(&खोलो_count);
	वापस -EBUSY;
पूर्ण

/*
 * The BT (Block Transfer) पूर्णांकerface means that entire messages are
 * buffered by the host beक्रमe a notअगरication is sent to the BMC that
 * there is data to be पढ़ो. The first byte is the length and the
 * message data follows. The पढ़ो operation just tries to capture the
 * whole beक्रमe वापसing it to userspace.
 *
 * BT Message क्रमmat :
 *
 *    Byte 1  Byte 2     Byte 3  Byte 4  Byte 5:N
 *    Length  NetFn/LUN  Seq     Cmd     Data
 *
 */
अटल sमाप_प्रकार bt_bmc_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा bt_bmc *bt_bmc = file_bt_bmc(file);
	u8 len;
	पूर्णांक len_byte = 1;
	u8 kbuffer[BT_BMC_BUFFER_SIZE];
	sमाप_प्रकार ret = 0;
	sमाप_प्रकार nपढ़ो;

	WARN_ON(*ppos);

	अगर (रुको_event_पूर्णांकerruptible(bt_bmc->queue,
				     bt_inb(bt_bmc, BT_CTRL) & BT_CTRL_H2B_ATN))
		वापस -ERESTARTSYS;

	mutex_lock(&bt_bmc->mutex);

	अगर (unlikely(!(bt_inb(bt_bmc, BT_CTRL) & BT_CTRL_H2B_ATN))) अणु
		ret = -EIO;
		जाओ out_unlock;
	पूर्ण

	set_b_busy(bt_bmc);
	clr_h2b_atn(bt_bmc);
	clr_rd_ptr(bt_bmc);

	/*
	 * The BT frames start with the message length, which करोes not
	 * include the length byte.
	 */
	kbuffer[0] = bt_पढ़ो(bt_bmc);
	len = kbuffer[0];

	/* We pass the length back to userspace as well */
	अगर (len + 1 > count)
		len = count - 1;

	जबतक (len) अणु
		nपढ़ो = min_t(sमाप_प्रकार, len, माप(kbuffer) - len_byte);

		bt_पढ़ोn(bt_bmc, kbuffer + len_byte, nपढ़ो);

		अगर (copy_to_user(buf, kbuffer, nपढ़ो + len_byte)) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण
		len -= nपढ़ो;
		buf += nपढ़ो + len_byte;
		ret += nपढ़ो + len_byte;
		len_byte = 0;
	पूर्ण

	clr_b_busy(bt_bmc);

out_unlock:
	mutex_unlock(&bt_bmc->mutex);
	वापस ret;
पूर्ण

/*
 * BT Message response क्रमmat :
 *
 *    Byte 1  Byte 2     Byte 3  Byte 4  Byte 5  Byte 6:N
 *    Length  NetFn/LUN  Seq     Cmd     Code    Data
 */
अटल sमाप_प्रकार bt_bmc_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा bt_bmc *bt_bmc = file_bt_bmc(file);
	u8 kbuffer[BT_BMC_BUFFER_SIZE];
	sमाप_प्रकार ret = 0;
	sमाप_प्रकार nwritten;

	/*
	 * send a minimum response size
	 */
	अगर (count < 5)
		वापस -EINVAL;

	WARN_ON(*ppos);

	/*
	 * There's no पूर्णांकerrupt क्रम clearing bmc busy so we have to
	 * poll
	 */
	अगर (रुको_event_पूर्णांकerruptible(bt_bmc->queue,
				     !(bt_inb(bt_bmc, BT_CTRL) &
				       (BT_CTRL_H_BUSY | BT_CTRL_B2H_ATN))))
		वापस -ERESTARTSYS;

	mutex_lock(&bt_bmc->mutex);

	अगर (unlikely(bt_inb(bt_bmc, BT_CTRL) &
		     (BT_CTRL_H_BUSY | BT_CTRL_B2H_ATN))) अणु
		ret = -EIO;
		जाओ out_unlock;
	पूर्ण

	clr_wr_ptr(bt_bmc);

	जबतक (count) अणु
		nwritten = min_t(sमाप_प्रकार, count, माप(kbuffer));
		अगर (copy_from_user(&kbuffer, buf, nwritten)) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण

		bt_ग_लिखोn(bt_bmc, kbuffer, nwritten);

		count -= nwritten;
		buf += nwritten;
		ret += nwritten;
	पूर्ण

	set_b2h_atn(bt_bmc);

out_unlock:
	mutex_unlock(&bt_bmc->mutex);
	वापस ret;
पूर्ण

अटल दीर्घ bt_bmc_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			 अचिन्हित दीर्घ param)
अणु
	काष्ठा bt_bmc *bt_bmc = file_bt_bmc(file);

	चयन (cmd) अणु
	हाल BT_BMC_IOCTL_SMS_ATN:
		set_sms_atn(bt_bmc);
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक bt_bmc_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा bt_bmc *bt_bmc = file_bt_bmc(file);

	atomic_dec(&खोलो_count);
	set_b_busy(bt_bmc);
	वापस 0;
पूर्ण

अटल __poll_t bt_bmc_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा bt_bmc *bt_bmc = file_bt_bmc(file);
	__poll_t mask = 0;
	u8 ctrl;

	poll_रुको(file, &bt_bmc->queue, रुको);

	ctrl = bt_inb(bt_bmc, BT_CTRL);

	अगर (ctrl & BT_CTRL_H2B_ATN)
		mask |= EPOLLIN;

	अगर (!(ctrl & (BT_CTRL_H_BUSY | BT_CTRL_B2H_ATN)))
		mask |= EPOLLOUT;

	वापस mask;
पूर्ण

अटल स्थिर काष्ठा file_operations bt_bmc_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= bt_bmc_खोलो,
	.पढ़ो		= bt_bmc_पढ़ो,
	.ग_लिखो		= bt_bmc_ग_लिखो,
	.release	= bt_bmc_release,
	.poll		= bt_bmc_poll,
	.unlocked_ioctl	= bt_bmc_ioctl,
पूर्ण;

अटल व्योम poll_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा bt_bmc *bt_bmc = from_समयr(bt_bmc, t, poll_समयr);

	bt_bmc->poll_समयr.expires += msecs_to_jअगरfies(500);
	wake_up(&bt_bmc->queue);
	add_समयr(&bt_bmc->poll_समयr);
पूर्ण

अटल irqवापस_t bt_bmc_irq(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा bt_bmc *bt_bmc = arg;
	u32 reg;
	पूर्णांक rc;

	rc = regmap_पढ़ो(bt_bmc->map, bt_bmc->offset + BT_CR2, &reg);
	अगर (rc)
		वापस IRQ_NONE;

	reg &= BT_CR2_IRQ_H2B | BT_CR2_IRQ_HBUSY;
	अगर (!reg)
		वापस IRQ_NONE;

	/* ack pending IRQs */
	regmap_ग_लिखो(bt_bmc->map, bt_bmc->offset + BT_CR2, reg);

	wake_up(&bt_bmc->queue);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक bt_bmc_config_irq(काष्ठा bt_bmc *bt_bmc,
			     काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक rc;

	bt_bmc->irq = platक्रमm_get_irq_optional(pdev, 0);
	अगर (bt_bmc->irq < 0)
		वापस bt_bmc->irq;

	rc = devm_request_irq(dev, bt_bmc->irq, bt_bmc_irq, IRQF_SHARED,
			      DEVICE_NAME, bt_bmc);
	अगर (rc < 0) अणु
		dev_warn(dev, "Unable to request IRQ %d\n", bt_bmc->irq);
		bt_bmc->irq = rc;
		वापस rc;
	पूर्ण

	/*
	 * Configure IRQs on the bmc clearing the H2B and HBUSY bits;
	 * H2B will be निश्चितed when the bmc has data क्रम us; HBUSY
	 * will be cleared (aदीर्घ with B2H) when we can ग_लिखो the next
	 * message to the BT buffer
	 */
	rc = regmap_update_bits(bt_bmc->map, bt_bmc->offset + BT_CR1,
				(BT_CR1_IRQ_H2B | BT_CR1_IRQ_HBUSY),
				(BT_CR1_IRQ_H2B | BT_CR1_IRQ_HBUSY));

	वापस rc;
पूर्ण

अटल पूर्णांक bt_bmc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bt_bmc *bt_bmc;
	काष्ठा device *dev;
	पूर्णांक rc;

	dev = &pdev->dev;
	dev_info(dev, "Found bt bmc device\n");

	bt_bmc = devm_kzalloc(dev, माप(*bt_bmc), GFP_KERNEL);
	अगर (!bt_bmc)
		वापस -ENOMEM;

	dev_set_drvdata(&pdev->dev, bt_bmc);

	bt_bmc->map = syscon_node_to_regmap(pdev->dev.parent->of_node);
	अगर (IS_ERR(bt_bmc->map)) अणु
		व्योम __iomem *base;

		/*
		 * Assume it's not the MFD-based devicetree description, in
		 * which हाल generate a regmap ourselves
		 */
		base = devm_platक्रमm_ioremap_resource(pdev, 0);
		अगर (IS_ERR(base))
			वापस PTR_ERR(base);

		bt_bmc->map = devm_regmap_init_mmio(dev, base, &bt_regmap_cfg);
		bt_bmc->offset = 0;
	पूर्ण अन्यथा अणु
		rc = of_property_पढ़ो_u32(dev->of_node, "reg", &bt_bmc->offset);
		अगर (rc)
			वापस rc;
	पूर्ण

	mutex_init(&bt_bmc->mutex);
	init_रुकोqueue_head(&bt_bmc->queue);

	bt_bmc->miscdev.minor	= MISC_DYNAMIC_MINOR;
	bt_bmc->miscdev.name	= DEVICE_NAME;
	bt_bmc->miscdev.fops	= &bt_bmc_fops;
	bt_bmc->miscdev.parent = dev;
	rc = misc_रेजिस्टर(&bt_bmc->miscdev);
	अगर (rc) अणु
		dev_err(dev, "Unable to register misc device\n");
		वापस rc;
	पूर्ण

	bt_bmc_config_irq(bt_bmc, pdev);

	अगर (bt_bmc->irq >= 0) अणु
		dev_info(dev, "Using IRQ %d\n", bt_bmc->irq);
	पूर्ण अन्यथा अणु
		dev_info(dev, "No IRQ; using timer\n");
		समयr_setup(&bt_bmc->poll_समयr, poll_समयr, 0);
		bt_bmc->poll_समयr.expires = jअगरfies + msecs_to_jअगरfies(10);
		add_समयr(&bt_bmc->poll_समयr);
	पूर्ण

	regmap_ग_लिखो(bt_bmc->map, bt_bmc->offset + BT_CR0,
		     (BT_IO_BASE << BT_CR0_IO_BASE) |
		     (BT_IRQ << BT_CR0_IRQ) |
		     BT_CR0_EN_CLR_SLV_RDP |
		     BT_CR0_EN_CLR_SLV_WRP |
		     BT_CR0_ENABLE_IBT);

	clr_b_busy(bt_bmc);

	वापस 0;
पूर्ण

अटल पूर्णांक bt_bmc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bt_bmc *bt_bmc = dev_get_drvdata(&pdev->dev);

	misc_deरेजिस्टर(&bt_bmc->miscdev);
	अगर (bt_bmc->irq < 0)
		del_समयr_sync(&bt_bmc->poll_समयr);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id bt_bmc_match[] = अणु
	अणु .compatible = "aspeed,ast2400-ibt-bmc" पूर्ण,
	अणु .compatible = "aspeed,ast2500-ibt-bmc" पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver bt_bmc_driver = अणु
	.driver = अणु
		.name		= DEVICE_NAME,
		.of_match_table = bt_bmc_match,
	पूर्ण,
	.probe = bt_bmc_probe,
	.हटाओ = bt_bmc_हटाओ,
पूर्ण;

module_platक्रमm_driver(bt_bmc_driver);

MODULE_DEVICE_TABLE(of, bt_bmc_match);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Alistair Popple <alistair@popple.id.au>");
MODULE_DESCRIPTION("Linux device interface to the IPMI BT interface");
