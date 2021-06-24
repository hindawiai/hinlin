<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SH SPI bus driver
 *
 * Copyright (C) 2011  Renesas Solutions Corp.
 *
 * Based on pxa2xx_spi.c:
 * Copyright (C) 2005 Stephen Street / StreetFire Sound Lअसल
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/समयr.h>
#समावेश <linux/delay.h>
#समावेश <linux/list.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/spi/spi.h>

#घोषणा SPI_SH_TBR		0x00
#घोषणा SPI_SH_RBR		0x00
#घोषणा SPI_SH_CR1		0x08
#घोषणा SPI_SH_CR2		0x10
#घोषणा SPI_SH_CR3		0x18
#घोषणा SPI_SH_CR4		0x20
#घोषणा SPI_SH_CR5		0x28

/* CR1 */
#घोषणा SPI_SH_TBE		0x80
#घोषणा SPI_SH_TBF		0x40
#घोषणा SPI_SH_RBE		0x20
#घोषणा SPI_SH_RBF		0x10
#घोषणा SPI_SH_PFONRD		0x08
#घोषणा SPI_SH_SSDB		0x04
#घोषणा SPI_SH_SSD		0x02
#घोषणा SPI_SH_SSA		0x01

/* CR2 */
#घोषणा SPI_SH_RSTF		0x80
#घोषणा SPI_SH_LOOPBK		0x40
#घोषणा SPI_SH_CPOL		0x20
#घोषणा SPI_SH_CPHA		0x10
#घोषणा SPI_SH_L1M0		0x08

/* CR3 */
#घोषणा SPI_SH_MAX_BYTE		0xFF

/* CR4 */
#घोषणा SPI_SH_TBEI		0x80
#घोषणा SPI_SH_TBFI		0x40
#घोषणा SPI_SH_RBEI		0x20
#घोषणा SPI_SH_RBFI		0x10
#घोषणा SPI_SH_WPABRT		0x04
#घोषणा SPI_SH_SSS		0x01

/* CR8 */
#घोषणा SPI_SH_P1L0		0x80
#घोषणा SPI_SH_PP1L0		0x40
#घोषणा SPI_SH_MUXI		0x20
#घोषणा SPI_SH_MUXIRQ		0x10

#घोषणा SPI_SH_FIFO_SIZE	32
#घोषणा SPI_SH_SEND_TIMEOUT	(3 * HZ)
#घोषणा SPI_SH_RECEIVE_TIMEOUT	(HZ >> 3)

#अघोषित DEBUG

काष्ठा spi_sh_data अणु
	व्योम __iomem *addr;
	पूर्णांक irq;
	काष्ठा spi_master *master;
	काष्ठा list_head queue;
	काष्ठा work_काष्ठा ws;
	अचिन्हित दीर्घ cr1;
	रुको_queue_head_t रुको;
	spinlock_t lock;
	पूर्णांक width;
पूर्ण;

अटल व्योम spi_sh_ग_लिखो(काष्ठा spi_sh_data *ss, अचिन्हित दीर्घ data,
			     अचिन्हित दीर्घ offset)
अणु
	अगर (ss->width == 8)
		ioग_लिखो8(data, ss->addr + (offset >> 2));
	अन्यथा अगर (ss->width == 32)
		ioग_लिखो32(data, ss->addr + offset);
पूर्ण

अटल अचिन्हित दीर्घ spi_sh_पढ़ो(काष्ठा spi_sh_data *ss, अचिन्हित दीर्घ offset)
अणु
	अगर (ss->width == 8)
		वापस ioपढ़ो8(ss->addr + (offset >> 2));
	अन्यथा अगर (ss->width == 32)
		वापस ioपढ़ो32(ss->addr + offset);
	अन्यथा
		वापस 0;
पूर्ण

अटल व्योम spi_sh_set_bit(काष्ठा spi_sh_data *ss, अचिन्हित दीर्घ val,
				अचिन्हित दीर्घ offset)
अणु
	अचिन्हित दीर्घ पंचांगp;

	पंचांगp = spi_sh_पढ़ो(ss, offset);
	पंचांगp |= val;
	spi_sh_ग_लिखो(ss, पंचांगp, offset);
पूर्ण

अटल व्योम spi_sh_clear_bit(काष्ठा spi_sh_data *ss, अचिन्हित दीर्घ val,
				अचिन्हित दीर्घ offset)
अणु
	अचिन्हित दीर्घ पंचांगp;

	पंचांगp = spi_sh_पढ़ो(ss, offset);
	पंचांगp &= ~val;
	spi_sh_ग_लिखो(ss, पंचांगp, offset);
पूर्ण

अटल व्योम clear_fअगरo(काष्ठा spi_sh_data *ss)
अणु
	spi_sh_set_bit(ss, SPI_SH_RSTF, SPI_SH_CR2);
	spi_sh_clear_bit(ss, SPI_SH_RSTF, SPI_SH_CR2);
पूर्ण

अटल पूर्णांक spi_sh_रुको_receive_buffer(काष्ठा spi_sh_data *ss)
अणु
	पूर्णांक समयout = 100000;

	जबतक (spi_sh_पढ़ो(ss, SPI_SH_CR1) & SPI_SH_RBE) अणु
		udelay(10);
		अगर (समयout-- < 0)
			वापस -ETIMEDOUT;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक spi_sh_रुको_ग_लिखो_buffer_empty(काष्ठा spi_sh_data *ss)
अणु
	पूर्णांक समयout = 100000;

	जबतक (!(spi_sh_पढ़ो(ss, SPI_SH_CR1) & SPI_SH_TBE)) अणु
		udelay(10);
		अगर (समयout-- < 0)
			वापस -ETIMEDOUT;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक spi_sh_send(काष्ठा spi_sh_data *ss, काष्ठा spi_message *mesg,
			काष्ठा spi_transfer *t)
अणु
	पूर्णांक i, retval = 0;
	पूर्णांक reमुख्य = t->len;
	पूर्णांक cur_len;
	अचिन्हित अक्षर *data;
	दीर्घ ret;

	अगर (t->len)
		spi_sh_set_bit(ss, SPI_SH_SSA, SPI_SH_CR1);

	data = (अचिन्हित अक्षर *)t->tx_buf;
	जबतक (reमुख्य > 0) अणु
		cur_len = min(SPI_SH_FIFO_SIZE, reमुख्य);
		क्रम (i = 0; i < cur_len &&
				!(spi_sh_पढ़ो(ss, SPI_SH_CR4) &
							SPI_SH_WPABRT) &&
				!(spi_sh_पढ़ो(ss, SPI_SH_CR1) & SPI_SH_TBF);
				i++)
			spi_sh_ग_लिखो(ss, (अचिन्हित दीर्घ)data[i], SPI_SH_TBR);

		अगर (spi_sh_पढ़ो(ss, SPI_SH_CR4) & SPI_SH_WPABRT) अणु
			/* Abort SPI operation */
			spi_sh_set_bit(ss, SPI_SH_WPABRT, SPI_SH_CR4);
			retval = -EIO;
			अवरोध;
		पूर्ण

		cur_len = i;

		reमुख्य -= cur_len;
		data += cur_len;

		अगर (reमुख्य > 0) अणु
			ss->cr1 &= ~SPI_SH_TBE;
			spi_sh_set_bit(ss, SPI_SH_TBE, SPI_SH_CR4);
			ret = रुको_event_पूर्णांकerruptible_समयout(ss->रुको,
						 ss->cr1 & SPI_SH_TBE,
						 SPI_SH_SEND_TIMEOUT);
			अगर (ret == 0 && !(ss->cr1 & SPI_SH_TBE)) अणु
				prपूर्णांकk(KERN_ERR "%s: timeout\n", __func__);
				वापस -ETIMEDOUT;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (list_is_last(&t->transfer_list, &mesg->transfers)) अणु
		spi_sh_clear_bit(ss, SPI_SH_SSD | SPI_SH_SSDB, SPI_SH_CR1);
		spi_sh_set_bit(ss, SPI_SH_SSA, SPI_SH_CR1);

		ss->cr1 &= ~SPI_SH_TBE;
		spi_sh_set_bit(ss, SPI_SH_TBE, SPI_SH_CR4);
		ret = रुको_event_पूर्णांकerruptible_समयout(ss->रुको,
					 ss->cr1 & SPI_SH_TBE,
					 SPI_SH_SEND_TIMEOUT);
		अगर (ret == 0 && (ss->cr1 & SPI_SH_TBE)) अणु
			prपूर्णांकk(KERN_ERR "%s: timeout\n", __func__);
			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण

	वापस retval;
पूर्ण

अटल पूर्णांक spi_sh_receive(काष्ठा spi_sh_data *ss, काष्ठा spi_message *mesg,
			  काष्ठा spi_transfer *t)
अणु
	पूर्णांक i;
	पूर्णांक reमुख्य = t->len;
	पूर्णांक cur_len;
	अचिन्हित अक्षर *data;
	दीर्घ ret;

	अगर (t->len > SPI_SH_MAX_BYTE)
		spi_sh_ग_लिखो(ss, SPI_SH_MAX_BYTE, SPI_SH_CR3);
	अन्यथा
		spi_sh_ग_लिखो(ss, t->len, SPI_SH_CR3);

	spi_sh_clear_bit(ss, SPI_SH_SSD | SPI_SH_SSDB, SPI_SH_CR1);
	spi_sh_set_bit(ss, SPI_SH_SSA, SPI_SH_CR1);

	spi_sh_रुको_ग_लिखो_buffer_empty(ss);

	data = (अचिन्हित अक्षर *)t->rx_buf;
	जबतक (reमुख्य > 0) अणु
		अगर (reमुख्य >= SPI_SH_FIFO_SIZE) अणु
			ss->cr1 &= ~SPI_SH_RBF;
			spi_sh_set_bit(ss, SPI_SH_RBF, SPI_SH_CR4);
			ret = रुको_event_पूर्णांकerruptible_समयout(ss->रुको,
						 ss->cr1 & SPI_SH_RBF,
						 SPI_SH_RECEIVE_TIMEOUT);
			अगर (ret == 0 &&
			    spi_sh_पढ़ो(ss, SPI_SH_CR1) & SPI_SH_RBE) अणु
				prपूर्णांकk(KERN_ERR "%s: timeout\n", __func__);
				वापस -ETIMEDOUT;
			पूर्ण
		पूर्ण

		cur_len = min(SPI_SH_FIFO_SIZE, reमुख्य);
		क्रम (i = 0; i < cur_len; i++) अणु
			अगर (spi_sh_रुको_receive_buffer(ss))
				अवरोध;
			data[i] = (अचिन्हित अक्षर)spi_sh_पढ़ो(ss, SPI_SH_RBR);
		पूर्ण

		reमुख्य -= cur_len;
		data += cur_len;
	पूर्ण

	/* deनिश्चित CS when SPI is receiving. */
	अगर (t->len > SPI_SH_MAX_BYTE) अणु
		clear_fअगरo(ss);
		spi_sh_ग_लिखो(ss, 1, SPI_SH_CR3);
	पूर्ण अन्यथा अणु
		spi_sh_ग_लिखो(ss, 0, SPI_SH_CR3);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम spi_sh_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा spi_sh_data *ss = container_of(work, काष्ठा spi_sh_data, ws);
	काष्ठा spi_message *mesg;
	काष्ठा spi_transfer *t;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	pr_debug("%s: enter\n", __func__);

	spin_lock_irqsave(&ss->lock, flags);
	जबतक (!list_empty(&ss->queue)) अणु
		mesg = list_entry(ss->queue.next, काष्ठा spi_message, queue);
		list_del_init(&mesg->queue);

		spin_unlock_irqrestore(&ss->lock, flags);
		list_क्रम_each_entry(t, &mesg->transfers, transfer_list) अणु
			pr_debug("tx_buf = %p, rx_buf = %p\n",
					t->tx_buf, t->rx_buf);
			pr_debug("len = %d, delay.value = %d\n",
					t->len, t->delay.value);

			अगर (t->tx_buf) अणु
				ret = spi_sh_send(ss, mesg, t);
				अगर (ret < 0)
					जाओ error;
			पूर्ण
			अगर (t->rx_buf) अणु
				ret = spi_sh_receive(ss, mesg, t);
				अगर (ret < 0)
					जाओ error;
			पूर्ण
			mesg->actual_length += t->len;
		पूर्ण
		spin_lock_irqsave(&ss->lock, flags);

		mesg->status = 0;
		अगर (mesg->complete)
			mesg->complete(mesg->context);
	पूर्ण

	clear_fअगरo(ss);
	spi_sh_set_bit(ss, SPI_SH_SSD, SPI_SH_CR1);
	udelay(100);

	spi_sh_clear_bit(ss, SPI_SH_SSA | SPI_SH_SSDB | SPI_SH_SSD,
			 SPI_SH_CR1);

	clear_fअगरo(ss);

	spin_unlock_irqrestore(&ss->lock, flags);

	वापस;

 error:
	mesg->status = ret;
	अगर (mesg->complete)
		mesg->complete(mesg->context);

	spi_sh_clear_bit(ss, SPI_SH_SSA | SPI_SH_SSDB | SPI_SH_SSD,
			 SPI_SH_CR1);
	clear_fअगरo(ss);

पूर्ण

अटल पूर्णांक spi_sh_setup(काष्ठा spi_device *spi)
अणु
	काष्ठा spi_sh_data *ss = spi_master_get_devdata(spi->master);

	pr_debug("%s: enter\n", __func__);

	spi_sh_ग_लिखो(ss, 0xfe, SPI_SH_CR1);	/* SPI sycle stop */
	spi_sh_ग_लिखो(ss, 0x00, SPI_SH_CR1);	/* CR1 init */
	spi_sh_ग_लिखो(ss, 0x00, SPI_SH_CR3);	/* CR3 init */

	clear_fअगरo(ss);

	/* 1/8 घड़ी */
	spi_sh_ग_लिखो(ss, spi_sh_पढ़ो(ss, SPI_SH_CR2) | 0x07, SPI_SH_CR2);
	udelay(10);

	वापस 0;
पूर्ण

अटल पूर्णांक spi_sh_transfer(काष्ठा spi_device *spi, काष्ठा spi_message *mesg)
अणु
	काष्ठा spi_sh_data *ss = spi_master_get_devdata(spi->master);
	अचिन्हित दीर्घ flags;

	pr_debug("%s: enter\n", __func__);
	pr_debug("\tmode = %02x\n", spi->mode);

	spin_lock_irqsave(&ss->lock, flags);

	mesg->actual_length = 0;
	mesg->status = -EINPROGRESS;

	spi_sh_clear_bit(ss, SPI_SH_SSA, SPI_SH_CR1);

	list_add_tail(&mesg->queue, &ss->queue);
	schedule_work(&ss->ws);

	spin_unlock_irqrestore(&ss->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम spi_sh_cleanup(काष्ठा spi_device *spi)
अणु
	काष्ठा spi_sh_data *ss = spi_master_get_devdata(spi->master);

	pr_debug("%s: enter\n", __func__);

	spi_sh_clear_bit(ss, SPI_SH_SSA | SPI_SH_SSDB | SPI_SH_SSD,
			 SPI_SH_CR1);
पूर्ण

अटल irqवापस_t spi_sh_irq(पूर्णांक irq, व्योम *_ss)
अणु
	काष्ठा spi_sh_data *ss = (काष्ठा spi_sh_data *)_ss;
	अचिन्हित दीर्घ cr1;

	cr1 = spi_sh_पढ़ो(ss, SPI_SH_CR1);
	अगर (cr1 & SPI_SH_TBE)
		ss->cr1 |= SPI_SH_TBE;
	अगर (cr1 & SPI_SH_TBF)
		ss->cr1 |= SPI_SH_TBF;
	अगर (cr1 & SPI_SH_RBE)
		ss->cr1 |= SPI_SH_RBE;
	अगर (cr1 & SPI_SH_RBF)
		ss->cr1 |= SPI_SH_RBF;

	अगर (ss->cr1) अणु
		spi_sh_clear_bit(ss, ss->cr1, SPI_SH_CR4);
		wake_up(&ss->रुको);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक spi_sh_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_sh_data *ss = platक्रमm_get_drvdata(pdev);

	spi_unरेजिस्टर_master(ss->master);
	flush_work(&ss->ws);
	मुक्त_irq(ss->irq, ss);

	वापस 0;
पूर्ण

अटल पूर्णांक spi_sh_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	काष्ठा spi_master *master;
	काष्ठा spi_sh_data *ss;
	पूर्णांक ret, irq;

	/* get base addr */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (unlikely(res == शून्य)) अणु
		dev_err(&pdev->dev, "invalid resource\n");
		वापस -EINVAL;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	master = devm_spi_alloc_master(&pdev->dev, माप(काष्ठा spi_sh_data));
	अगर (master == शून्य) अणु
		dev_err(&pdev->dev, "spi_alloc_master error.\n");
		वापस -ENOMEM;
	पूर्ण

	ss = spi_master_get_devdata(master);
	platक्रमm_set_drvdata(pdev, ss);

	चयन (res->flags & IORESOURCE_MEM_TYPE_MASK) अणु
	हाल IORESOURCE_MEM_8BIT:
		ss->width = 8;
		अवरोध;
	हाल IORESOURCE_MEM_32BIT:
		ss->width = 32;
		अवरोध;
	शेष:
		dev_err(&pdev->dev, "No support width\n");
		वापस -ENODEV;
	पूर्ण
	ss->irq = irq;
	ss->master = master;
	ss->addr = devm_ioremap(&pdev->dev, res->start, resource_size(res));
	अगर (ss->addr == शून्य) अणु
		dev_err(&pdev->dev, "ioremap error.\n");
		वापस -ENOMEM;
	पूर्ण
	INIT_LIST_HEAD(&ss->queue);
	spin_lock_init(&ss->lock);
	INIT_WORK(&ss->ws, spi_sh_work);
	init_रुकोqueue_head(&ss->रुको);

	ret = request_irq(irq, spi_sh_irq, 0, "spi_sh", ss);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "request_irq error\n");
		वापस ret;
	पूर्ण

	master->num_chipselect = 2;
	master->bus_num = pdev->id;
	master->setup = spi_sh_setup;
	master->transfer = spi_sh_transfer;
	master->cleanup = spi_sh_cleanup;

	ret = spi_रेजिस्टर_master(master);
	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_ERR "spi_register_master error.\n");
		जाओ error3;
	पूर्ण

	वापस 0;

 error3:
	मुक्त_irq(irq, ss);
	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver spi_sh_driver = अणु
	.probe = spi_sh_probe,
	.हटाओ = spi_sh_हटाओ,
	.driver = अणु
		.name = "sh_spi",
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(spi_sh_driver);

MODULE_DESCRIPTION("SH SPI bus driver");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Yoshihiro Shimoda");
MODULE_ALIAS("platform:sh_spi");
