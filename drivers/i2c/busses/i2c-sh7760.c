<शैली गुरु>
/*
 * I2C bus driver क्रम the SH7760 I2C Interfaces.
 *
 * (c) 2005-2008 MSC Vertriebsges.m.b.H, Manuel Lauss <mlau@msc-ge.com>
 *
 * licensed under the terms outlined in the file COPYING.
 *
 */

#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>

#समावेश <यंत्र/घड़ी.h>
#समावेश <यंत्र/i2c-sh7760.h>

/* रेजिस्टर offsets */
#घोषणा I2CSCR		0x0		/* slave ctrl		*/
#घोषणा I2CMCR		0x4		/* master ctrl		*/
#घोषणा I2CSSR		0x8		/* slave status		*/
#घोषणा I2CMSR		0xC		/* master status	*/
#घोषणा I2CSIER		0x10		/* slave irq enable	*/
#घोषणा I2CMIER		0x14		/* master irq enable	*/
#घोषणा I2CCCR		0x18		/* घड़ी भागiders	*/
#घोषणा I2CSAR		0x1c		/* slave address	*/
#घोषणा I2CMAR		0x20		/* master address	*/
#घोषणा I2CRXTX		0x24		/* data port		*/
#घोषणा I2CFCR		0x28		/* fअगरo control		*/
#घोषणा I2CFSR		0x2C		/* fअगरo status		*/
#घोषणा I2CFIER		0x30		/* fअगरo irq enable	*/
#घोषणा I2CRFDR		0x34		/* rx fअगरo count	*/
#घोषणा I2CTFDR		0x38		/* tx fअगरo count	*/

#घोषणा REGSIZE		0x3C

#घोषणा MCR_MDBS	0x80		/* non-fअगरo mode चयन	*/
#घोषणा MCR_FSCL	0x40		/* override SCL pin	*/
#घोषणा MCR_FSDA	0x20		/* override SDA pin	*/
#घोषणा MCR_OBPC	0x10		/* override pins	*/
#घोषणा MCR_MIE		0x08		/* master अगर enable	*/
#घोषणा MCR_TSBE	0x04
#घोषणा MCR_FSB		0x02		/* क्रमce stop bit	*/
#घोषणा MCR_ESG		0x01		/* en startbit gen.	*/

#घोषणा MSR_MNR		0x40		/* nack received	*/
#घोषणा MSR_MAL		0x20		/* arbitration lost	*/
#घोषणा MSR_MST		0x10		/* sent a stop		*/
#घोषणा MSR_MDE		0x08
#घोषणा MSR_MDT		0x04
#घोषणा MSR_MDR		0x02
#घोषणा MSR_MAT		0x01		/* slave addr xfer करोne	*/

#घोषणा MIE_MNRE	0x40		/* nack irq en		*/
#घोषणा MIE_MALE	0x20		/* arblos irq en	*/
#घोषणा MIE_MSTE	0x10		/* stop irq en		*/
#घोषणा MIE_MDEE	0x08
#घोषणा MIE_MDTE	0x04
#घोषणा MIE_MDRE	0x02
#घोषणा MIE_MATE	0x01		/* address sent irq en	*/

#घोषणा FCR_RFRST	0x02		/* reset rx fअगरo	*/
#घोषणा FCR_TFRST	0x01		/* reset tx fअगरo	*/

#घोषणा FSR_TEND	0x04		/* last byte sent	*/
#घोषणा FSR_RDF		0x02		/* rx fअगरo trigger	*/
#घोषणा FSR_TDFE	0x01		/* tx fअगरo empty	*/

#घोषणा FIER_TEIE	0x04		/* tx fअगरo empty irq en	*/
#घोषणा FIER_RXIE	0x02		/* rx fअगरo trig irq en	*/
#घोषणा FIER_TXIE	0x01		/* tx fअगरo trig irq en	*/

#घोषणा FIFO_SIZE	16

काष्ठा cami2c अणु
	व्योम __iomem *iobase;
	काष्ठा i2c_adapter adap;

	/* message processing */
	काष्ठा i2c_msg	*msg;
#घोषणा IDF_SEND	1
#घोषणा IDF_RECV	2
#घोषणा IDF_STOP	4
	पूर्णांक		flags;

#घोषणा IDS_DONE	1
#घोषणा IDS_ARBLOST	2
#घोषणा IDS_NACK	4
	पूर्णांक		status;
	काष्ठा completion xfer_करोne;

	पूर्णांक irq;
	काष्ठा resource *ioarea;
पूर्ण;

अटल अंतरभूत व्योम OUT32(काष्ठा cami2c *cam, पूर्णांक reg, अचिन्हित दीर्घ val)
अणु
	__raw_ग_लिखोl(val, (अचिन्हित दीर्घ)cam->iobase + reg);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ IN32(काष्ठा cami2c *cam, पूर्णांक reg)
अणु
	वापस __raw_पढ़ोl((अचिन्हित दीर्घ)cam->iobase + reg);
पूर्ण

अटल irqवापस_t sh7760_i2c_irq(पूर्णांक irq, व्योम *ptr)
अणु
	काष्ठा cami2c *id = ptr;
	काष्ठा i2c_msg *msg = id->msg;
	अक्षर *data = msg->buf;
	अचिन्हित दीर्घ msr, fsr, fier, len;

	msr = IN32(id, I2CMSR);
	fsr = IN32(id, I2CFSR);

	/* arbitration lost */
	अगर (msr & MSR_MAL) अणु
		OUT32(id, I2CMCR, 0);
		OUT32(id, I2CSCR, 0);
		OUT32(id, I2CSAR, 0);
		id->status |= IDS_DONE | IDS_ARBLOST;
		जाओ out;
	पूर्ण

	अगर (msr & MSR_MNR) अणु
		/* NACK handling is very screwed up.  After receiving a
		 * NAK IRQ one has to रुको a bit  beक्रमe writing to any
		 * रेजिस्टरs, or the ctl will lock up. After that delay
		 * करो a normal i2c stop. Then रुको at least 1 ms beक्रमe
		 * attempting another transfer or ctl will stop working
		 */
		udelay(100);	/* रुको or risk ctl hang */
		OUT32(id, I2CFCR, FCR_RFRST | FCR_TFRST);
		OUT32(id, I2CMCR, MCR_MIE | MCR_FSB);
		OUT32(id, I2CFIER, 0);
		OUT32(id, I2CMIER, MIE_MSTE);
		OUT32(id, I2CSCR, 0);
		OUT32(id, I2CSAR, 0);
		id->status |= IDS_NACK;
		msr &= ~MSR_MAT;
		fsr = 0;
		/* In some हालs the MST bit is also set. */
	पूर्ण

	/* i2c-stop was sent */
	अगर (msr & MSR_MST) अणु
		id->status |= IDS_DONE;
		जाओ out;
	पूर्ण

	/* i2c slave addr was sent; set to "normal" operation */
	अगर (msr & MSR_MAT)
		OUT32(id, I2CMCR, MCR_MIE);

	fier = IN32(id, I2CFIER);

	अगर (fsr & FSR_RDF) अणु
		len = IN32(id, I2CRFDR);
		अगर (msg->len <= len) अणु
			अगर (id->flags & IDF_STOP) अणु
				OUT32(id, I2CMCR, MCR_MIE | MCR_FSB);
				OUT32(id, I2CFIER, 0);
				/* manual says: रुको >= 0.5 SCL बार */
				udelay(5);
				/* next पूर्णांक should be MST */
			पूर्ण अन्यथा अणु
				id->status |= IDS_DONE;
				/* keep the RDF bit: ctrl holds SCL low
				 * until the setup क्रम the next i2c_msg
				 * clears this bit.
				 */
				fsr &= ~FSR_RDF;
			पूर्ण
		पूर्ण
		जबतक (msg->len && len) अणु
			*data++ = IN32(id, I2CRXTX);
			msg->len--;
			len--;
		पूर्ण

		अगर (msg->len) अणु
			len = (msg->len >= FIFO_SIZE) ? FIFO_SIZE - 1
						      : msg->len - 1;

			OUT32(id, I2CFCR, FCR_TFRST | ((len & 0xf) << 4));
		पूर्ण

	पूर्ण अन्यथा अगर (id->flags & IDF_SEND) अणु
		अगर ((fsr & FSR_TEND) && (msg->len < 1)) अणु
			अगर (id->flags & IDF_STOP) अणु
				OUT32(id, I2CMCR, MCR_MIE | MCR_FSB);
			पूर्ण अन्यथा अणु
				id->status |= IDS_DONE;
				/* keep the TEND bit: ctl holds SCL low
				 * until the setup क्रम the next i2c_msg
				 * clears this bit.
				 */
				fsr &= ~FSR_TEND;
			पूर्ण
		पूर्ण
		अगर (fsr & FSR_TDFE) अणु
			जबतक (msg->len && (IN32(id, I2CTFDR) < FIFO_SIZE)) अणु
				OUT32(id, I2CRXTX, *data++);
				msg->len--;
			पूर्ण

			अगर (msg->len < 1) अणु
				fier &= ~FIER_TXIE;
				OUT32(id, I2CFIER, fier);
			पूर्ण अन्यथा अणु
				len = (msg->len >= FIFO_SIZE) ? 2 : 0;
				OUT32(id, I2CFCR,
					  FCR_RFRST | ((len & 3) << 2));
			पूर्ण
		पूर्ण
	पूर्ण
out:
	अगर (id->status & IDS_DONE) अणु
		OUT32(id, I2CMIER, 0);
		OUT32(id, I2CFIER, 0);
		id->msg = शून्य;
		complete(&id->xfer_करोne);
	पूर्ण
	/* clear status flags and ctrl resumes work */
	OUT32(id, I2CMSR, ~msr);
	OUT32(id, I2CFSR, ~fsr);
	OUT32(id, I2CSSR, 0);

	वापस IRQ_HANDLED;
पूर्ण


/* prepare and start a master receive operation */
अटल व्योम sh7760_i2c_mrecv(काष्ठा cami2c *id)
अणु
	पूर्णांक len;

	id->flags |= IDF_RECV;

	/* set the slave addr reg; otherwise rcv wont work! */
	OUT32(id, I2CSAR, 0xfe);
	OUT32(id, I2CMAR, (id->msg->addr << 1) | 1);

	/* adjust rx fअगरo trigger */
	अगर (id->msg->len >= FIFO_SIZE)
		len = FIFO_SIZE - 1;	/* trigger at fअगरo full */
	अन्यथा
		len = id->msg->len - 1;	/* trigger beक्रमe all received */

	OUT32(id, I2CFCR, FCR_RFRST | FCR_TFRST);
	OUT32(id, I2CFCR, FCR_TFRST | ((len & 0xF) << 4));

	OUT32(id, I2CMSR, 0);
	OUT32(id, I2CMCR, MCR_MIE | MCR_ESG);
	OUT32(id, I2CMIER, MIE_MNRE | MIE_MALE | MIE_MSTE | MIE_MATE);
	OUT32(id, I2CFIER, FIER_RXIE);
पूर्ण

/* prepare and start a master send operation */
अटल व्योम sh7760_i2c_msend(काष्ठा cami2c *id)
अणु
	पूर्णांक len;

	id->flags |= IDF_SEND;

	/* set the slave addr reg; otherwise xmit wont work! */
	OUT32(id, I2CSAR, 0xfe);
	OUT32(id, I2CMAR, (id->msg->addr << 1) | 0);

	/* adjust tx fअगरo trigger */
	अगर (id->msg->len >= FIFO_SIZE)
		len = 2;	/* trig: 2 bytes left in TX fअगरo */
	अन्यथा
		len = 0;	/* trig: 8 bytes left in TX fअगरo */

	OUT32(id, I2CFCR, FCR_RFRST | FCR_TFRST);
	OUT32(id, I2CFCR, FCR_RFRST | ((len & 3) << 2));

	जबतक (id->msg->len && IN32(id, I2CTFDR) < FIFO_SIZE) अणु
		OUT32(id, I2CRXTX, *(id->msg->buf));
		(id->msg->len)--;
		(id->msg->buf)++;
	पूर्ण

	OUT32(id, I2CMSR, 0);
	OUT32(id, I2CMCR, MCR_MIE | MCR_ESG);
	OUT32(id, I2CFSR, 0);
	OUT32(id, I2CMIER, MIE_MNRE | MIE_MALE | MIE_MSTE | MIE_MATE);
	OUT32(id, I2CFIER, FIER_TEIE | (id->msg->len ? FIER_TXIE : 0));
पूर्ण

अटल अंतरभूत पूर्णांक sh7760_i2c_busy_check(काष्ठा cami2c *id)
अणु
	वापस (IN32(id, I2CMCR) & MCR_FSDA);
पूर्ण

अटल पूर्णांक sh7760_i2c_master_xfer(काष्ठा i2c_adapter *adap,
				  काष्ठा i2c_msg *msgs,
				  पूर्णांक num)
अणु
	काष्ठा cami2c *id = adap->algo_data;
	पूर्णांक i, retr;

	अगर (sh7760_i2c_busy_check(id)) अणु
		dev_err(&adap->dev, "sh7760-i2c%d: bus busy!\n", adap->nr);
		वापस -EBUSY;
	पूर्ण

	i = 0;
	जबतक (i < num) अणु
		retr = adap->retries;
retry:
		id->flags = ((i == (num-1)) ? IDF_STOP : 0);
		id->status = 0;
		id->msg = msgs;
		init_completion(&id->xfer_करोne);

		अगर (msgs->flags & I2C_M_RD)
			sh7760_i2c_mrecv(id);
		अन्यथा
			sh7760_i2c_msend(id);

		रुको_क्रम_completion(&id->xfer_करोne);

		अगर (id->status == 0) अणु
			num = -EIO;
			अवरोध;
		पूर्ण

		अगर (id->status & IDS_NACK) अणु
			/* रुको a bit or i2c module stops working */
			mdelay(1);
			num = -EREMOTEIO;
			अवरोध;
		पूर्ण

		अगर (id->status & IDS_ARBLOST) अणु
			अगर (retr--) अणु
				mdelay(2);
				जाओ retry;
			पूर्ण
			num = -EREMOTEIO;
			अवरोध;
		पूर्ण

		msgs++;
		i++;
	पूर्ण

	id->msg = शून्य;
	id->flags = 0;
	id->status = 0;

	OUT32(id, I2CMCR, 0);
	OUT32(id, I2CMSR, 0);
	OUT32(id, I2CMIER, 0);
	OUT32(id, I2CFIER, 0);

	/* reset slave module रेजिस्टरs too: master mode enables slave
	 * module क्रम receive ops (ack, data). Without this reset,
	 * eternal bus activity might be reported after NACK / ARBLOST.
	 */
	OUT32(id, I2CSCR, 0);
	OUT32(id, I2CSAR, 0);
	OUT32(id, I2CSSR, 0);

	वापस num;
पूर्ण

अटल u32 sh7760_i2c_func(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | (I2C_FUNC_SMBUS_EMUL & ~I2C_FUNC_SMBUS_QUICK);
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm sh7760_i2c_algo = अणु
	.master_xfer	= sh7760_i2c_master_xfer,
	.functionality	= sh7760_i2c_func,
पूर्ण;

/* calculate CCR रेजिस्टर setting क्रम a desired scl घड़ी.  SCL घड़ी is
 * derived from I2C module घड़ी  (iclk)  which in turn is derived from
 * peripheral module घड़ी (mclk, usually around 33MHz):
 * iclk = mclk/(CDF + 1).  iclk must be < 20MHz.
 * scl = iclk/(SCGD*8 + 20).
 */
अटल पूर्णांक calc_CCR(अचिन्हित दीर्घ scl_hz)
अणु
	काष्ठा clk *mclk;
	अचिन्हित दीर्घ mck, m1, dff, odff, iclk;
	चिन्हित अक्षर cdf, cdfm;
	पूर्णांक scgd, scgdm, scgds;

	mclk = clk_get(शून्य, "peripheral_clk");
	अगर (IS_ERR(mclk)) अणु
		वापस PTR_ERR(mclk);
	पूर्ण अन्यथा अणु
		mck = mclk->rate;
		clk_put(mclk);
	पूर्ण

	odff = scl_hz;
	scgdm = cdfm = m1 = 0;
	क्रम (cdf = 3; cdf >= 0; cdf--) अणु
		iclk = mck / (1 + cdf);
		अगर (iclk >= 20000000)
			जारी;
		scgds = ((iclk / scl_hz) - 20) >> 3;
		क्रम (scgd = scgds; (scgd < 63) && scgd <= scgds + 1; scgd++) अणु
			m1 = iclk / (20 + (scgd << 3));
			dff = असल(scl_hz - m1);
			अगर (dff < odff) अणु
				odff = dff;
				cdfm = cdf;
				scgdm = scgd;
			पूर्ण
		पूर्ण
	पूर्ण
	/* fail अगर more than 25% off of requested SCL */
	अगर (odff > (scl_hz >> 2))
		वापस -EINVAL;

	/* create a CCR रेजिस्टर value */
	वापस ((scgdm << 2) | cdfm);
पूर्ण

अटल पूर्णांक sh7760_i2c_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sh7760_i2c_platdata *pd;
	काष्ठा resource *res;
	काष्ठा cami2c *id;
	पूर्णांक ret;

	pd = dev_get_platdata(&pdev->dev);
	अगर (!pd) अणु
		dev_err(&pdev->dev, "no platform_data!\n");
		ret = -ENODEV;
		जाओ out0;
	पूर्ण

	id = kzalloc(माप(काष्ठा cami2c), GFP_KERNEL);
	अगर (!id) अणु
		dev_err(&pdev->dev, "no mem for private data\n");
		ret = -ENOMEM;
		जाओ out0;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		dev_err(&pdev->dev, "no mmio resources\n");
		ret = -ENODEV;
		जाओ out1;
	पूर्ण

	id->ioarea = request_mem_region(res->start, REGSIZE, pdev->name);
	अगर (!id->ioarea) अणु
		dev_err(&pdev->dev, "mmio already reserved\n");
		ret = -EBUSY;
		जाओ out1;
	पूर्ण

	id->iobase = ioremap(res->start, REGSIZE);
	अगर (!id->iobase) अणु
		dev_err(&pdev->dev, "cannot ioremap\n");
		ret = -ENODEV;
		जाओ out2;
	पूर्ण

	ret = platक्रमm_get_irq(pdev, 0);
	अगर (ret < 0)
		जाओ out3;
	id->irq = ret;

	id->adap.nr = pdev->id;
	id->adap.algo = &sh7760_i2c_algo;
	id->adap.class = I2C_CLASS_HWMON | I2C_CLASS_SPD;
	id->adap.retries = 3;
	id->adap.algo_data = id;
	id->adap.dev.parent = &pdev->dev;
	snम_लिखो(id->adap.name, माप(id->adap.name),
		"SH7760 I2C at %08lx", (अचिन्हित दीर्घ)res->start);

	OUT32(id, I2CMCR, 0);
	OUT32(id, I2CMSR, 0);
	OUT32(id, I2CMIER, 0);
	OUT32(id, I2CMAR, 0);
	OUT32(id, I2CSIER, 0);
	OUT32(id, I2CSAR, 0);
	OUT32(id, I2CSCR, 0);
	OUT32(id, I2CSSR, 0);
	OUT32(id, I2CFIER, 0);
	OUT32(id, I2CFCR, FCR_RFRST | FCR_TFRST);
	OUT32(id, I2CFSR, 0);

	ret = calc_CCR(pd->speed_khz * 1000);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "invalid SCL clock: %dkHz\n",
			pd->speed_khz);
		जाओ out3;
	पूर्ण
	OUT32(id, I2CCCR, ret);

	अगर (request_irq(id->irq, sh7760_i2c_irq, 0,
			SH7760_I2C_DEVNAME, id)) अणु
		dev_err(&pdev->dev, "cannot get irq %d\n", id->irq);
		ret = -EBUSY;
		जाओ out3;
	पूर्ण

	ret = i2c_add_numbered_adapter(&id->adap);
	अगर (ret < 0)
		जाओ out4;

	platक्रमm_set_drvdata(pdev, id);

	dev_info(&pdev->dev, "%d kHz mmio %08x irq %d\n",
		 pd->speed_khz, res->start, id->irq);

	वापस 0;

out4:
	मुक्त_irq(id->irq, id);
out3:
	iounmap(id->iobase);
out2:
	release_resource(id->ioarea);
	kमुक्त(id->ioarea);
out1:
	kमुक्त(id);
out0:
	वापस ret;
पूर्ण

अटल पूर्णांक sh7760_i2c_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cami2c *id = platक्रमm_get_drvdata(pdev);

	i2c_del_adapter(&id->adap);
	मुक्त_irq(id->irq, id);
	iounmap(id->iobase);
	release_resource(id->ioarea);
	kमुक्त(id->ioarea);
	kमुक्त(id);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver sh7760_i2c_drv = अणु
	.driver	= अणु
		.name	= SH7760_I2C_DEVNAME,
	पूर्ण,
	.probe		= sh7760_i2c_probe,
	.हटाओ		= sh7760_i2c_हटाओ,
पूर्ण;

module_platक्रमm_driver(sh7760_i2c_drv);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("SH7760 I2C bus driver");
MODULE_AUTHOR("Manuel Lauss <mano@roarinelk.homelinux.net>");
