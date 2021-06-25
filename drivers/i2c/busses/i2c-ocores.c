<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * i2c-ocores.c: I2C bus driver क्रम OpenCores I2C controller
 * (https://खोलोcores.org/project/i2c/overview)
 *
 * Peter Korsgaard <peter@korsgaard.com>
 *
 * Support क्रम the GRLIB port of the controller by
 * Andreas Larsson <andreas@gaisler.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/रुको.h>
#समावेश <linux/platक्रमm_data/i2c-ocores.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/log2.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/jअगरfies.h>

/*
 * 'process_lock' exists because ocores_process() and ocores_process_समयout()
 * can't run in parallel.
 */
काष्ठा ocores_i2c अणु
	व्योम __iomem *base;
	पूर्णांक iobase;
	u32 reg_shअगरt;
	u32 reg_io_width;
	अचिन्हित दीर्घ flags;
	रुको_queue_head_t रुको;
	काष्ठा i2c_adapter adap;
	काष्ठा i2c_msg *msg;
	पूर्णांक pos;
	पूर्णांक nmsgs;
	पूर्णांक state; /* see STATE_ */
	spinlock_t process_lock;
	काष्ठा clk *clk;
	पूर्णांक ip_घड़ी_khz;
	पूर्णांक bus_घड़ी_khz;
	व्योम (*setreg)(काष्ठा ocores_i2c *i2c, पूर्णांक reg, u8 value);
	u8 (*getreg)(काष्ठा ocores_i2c *i2c, पूर्णांक reg);
पूर्ण;

/* रेजिस्टरs */
#घोषणा OCI2C_PRELOW		0
#घोषणा OCI2C_PREHIGH		1
#घोषणा OCI2C_CONTROL		2
#घोषणा OCI2C_DATA		3
#घोषणा OCI2C_CMD		4 /* ग_लिखो only */
#घोषणा OCI2C_STATUS		4 /* पढ़ो only, same address as OCI2C_CMD */

#घोषणा OCI2C_CTRL_IEN		0x40
#घोषणा OCI2C_CTRL_EN		0x80

#घोषणा OCI2C_CMD_START		0x91
#घोषणा OCI2C_CMD_STOP		0x41
#घोषणा OCI2C_CMD_READ		0x21
#घोषणा OCI2C_CMD_WRITE		0x11
#घोषणा OCI2C_CMD_READ_ACK	0x21
#घोषणा OCI2C_CMD_READ_NACK	0x29
#घोषणा OCI2C_CMD_IACK		0x01

#घोषणा OCI2C_STAT_IF		0x01
#घोषणा OCI2C_STAT_TIP		0x02
#घोषणा OCI2C_STAT_ARBLOST	0x20
#घोषणा OCI2C_STAT_BUSY		0x40
#घोषणा OCI2C_STAT_NACK		0x80

#घोषणा STATE_DONE		0
#घोषणा STATE_START		1
#घोषणा STATE_WRITE		2
#घोषणा STATE_READ		3
#घोषणा STATE_ERROR		4

#घोषणा TYPE_OCORES		0
#घोषणा TYPE_GRLIB		1

#घोषणा OCORES_FLAG_BROKEN_IRQ BIT(1) /* Broken IRQ क्रम FU540-C000 SoC */

अटल व्योम oc_setreg_8(काष्ठा ocores_i2c *i2c, पूर्णांक reg, u8 value)
अणु
	ioग_लिखो8(value, i2c->base + (reg << i2c->reg_shअगरt));
पूर्ण

अटल व्योम oc_setreg_16(काष्ठा ocores_i2c *i2c, पूर्णांक reg, u8 value)
अणु
	ioग_लिखो16(value, i2c->base + (reg << i2c->reg_shअगरt));
पूर्ण

अटल व्योम oc_setreg_32(काष्ठा ocores_i2c *i2c, पूर्णांक reg, u8 value)
अणु
	ioग_लिखो32(value, i2c->base + (reg << i2c->reg_shअगरt));
पूर्ण

अटल व्योम oc_setreg_16be(काष्ठा ocores_i2c *i2c, पूर्णांक reg, u8 value)
अणु
	ioग_लिखो16be(value, i2c->base + (reg << i2c->reg_shअगरt));
पूर्ण

अटल व्योम oc_setreg_32be(काष्ठा ocores_i2c *i2c, पूर्णांक reg, u8 value)
अणु
	ioग_लिखो32be(value, i2c->base + (reg << i2c->reg_shअगरt));
पूर्ण

अटल अंतरभूत u8 oc_getreg_8(काष्ठा ocores_i2c *i2c, पूर्णांक reg)
अणु
	वापस ioपढ़ो8(i2c->base + (reg << i2c->reg_shअगरt));
पूर्ण

अटल अंतरभूत u8 oc_getreg_16(काष्ठा ocores_i2c *i2c, पूर्णांक reg)
अणु
	वापस ioपढ़ो16(i2c->base + (reg << i2c->reg_shअगरt));
पूर्ण

अटल अंतरभूत u8 oc_getreg_32(काष्ठा ocores_i2c *i2c, पूर्णांक reg)
अणु
	वापस ioपढ़ो32(i2c->base + (reg << i2c->reg_shअगरt));
पूर्ण

अटल अंतरभूत u8 oc_getreg_16be(काष्ठा ocores_i2c *i2c, पूर्णांक reg)
अणु
	वापस ioपढ़ो16be(i2c->base + (reg << i2c->reg_shअगरt));
पूर्ण

अटल अंतरभूत u8 oc_getreg_32be(काष्ठा ocores_i2c *i2c, पूर्णांक reg)
अणु
	वापस ioपढ़ो32be(i2c->base + (reg << i2c->reg_shअगरt));
पूर्ण

अटल व्योम oc_setreg_io_8(काष्ठा ocores_i2c *i2c, पूर्णांक reg, u8 value)
अणु
	outb(value, i2c->iobase + reg);
पूर्ण

अटल अंतरभूत u8 oc_getreg_io_8(काष्ठा ocores_i2c *i2c, पूर्णांक reg)
अणु
	वापस inb(i2c->iobase + reg);
पूर्ण

अटल अंतरभूत व्योम oc_setreg(काष्ठा ocores_i2c *i2c, पूर्णांक reg, u8 value)
अणु
	i2c->setreg(i2c, reg, value);
पूर्ण

अटल अंतरभूत u8 oc_getreg(काष्ठा ocores_i2c *i2c, पूर्णांक reg)
अणु
	वापस i2c->getreg(i2c, reg);
पूर्ण

अटल व्योम ocores_process(काष्ठा ocores_i2c *i2c, u8 stat)
अणु
	काष्ठा i2c_msg *msg = i2c->msg;
	अचिन्हित दीर्घ flags;

	/*
	 * If we spin here is because we are in समयout, so we are going
	 * to be in STATE_ERROR. See ocores_process_समयout()
	 */
	spin_lock_irqsave(&i2c->process_lock, flags);

	अगर ((i2c->state == STATE_DONE) || (i2c->state == STATE_ERROR)) अणु
		/* stop has been sent */
		oc_setreg(i2c, OCI2C_CMD, OCI2C_CMD_IACK);
		wake_up(&i2c->रुको);
		जाओ out;
	पूर्ण

	/* error? */
	अगर (stat & OCI2C_STAT_ARBLOST) अणु
		i2c->state = STATE_ERROR;
		oc_setreg(i2c, OCI2C_CMD, OCI2C_CMD_STOP);
		जाओ out;
	पूर्ण

	अगर ((i2c->state == STATE_START) || (i2c->state == STATE_WRITE)) अणु
		i2c->state =
			(msg->flags & I2C_M_RD) ? STATE_READ : STATE_WRITE;

		अगर (stat & OCI2C_STAT_NACK) अणु
			i2c->state = STATE_ERROR;
			oc_setreg(i2c, OCI2C_CMD, OCI2C_CMD_STOP);
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		msg->buf[i2c->pos++] = oc_getreg(i2c, OCI2C_DATA);
	पूर्ण

	/* end of msg? */
	अगर (i2c->pos == msg->len) अणु
		i2c->nmsgs--;
		i2c->msg++;
		i2c->pos = 0;
		msg = i2c->msg;

		अगर (i2c->nmsgs) अणु	/* end? */
			/* send start? */
			अगर (!(msg->flags & I2C_M_NOSTART)) अणु
				u8 addr = i2c_8bit_addr_from_msg(msg);

				i2c->state = STATE_START;

				oc_setreg(i2c, OCI2C_DATA, addr);
				oc_setreg(i2c, OCI2C_CMD, OCI2C_CMD_START);
				जाओ out;
			पूर्ण
			i2c->state = (msg->flags & I2C_M_RD)
				? STATE_READ : STATE_WRITE;
		पूर्ण अन्यथा अणु
			i2c->state = STATE_DONE;
			oc_setreg(i2c, OCI2C_CMD, OCI2C_CMD_STOP);
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (i2c->state == STATE_READ) अणु
		oc_setreg(i2c, OCI2C_CMD, i2c->pos == (msg->len-1) ?
			  OCI2C_CMD_READ_NACK : OCI2C_CMD_READ_ACK);
	पूर्ण अन्यथा अणु
		oc_setreg(i2c, OCI2C_DATA, msg->buf[i2c->pos++]);
		oc_setreg(i2c, OCI2C_CMD, OCI2C_CMD_WRITE);
	पूर्ण

out:
	spin_unlock_irqrestore(&i2c->process_lock, flags);
पूर्ण

अटल irqवापस_t ocores_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ocores_i2c *i2c = dev_id;
	u8 stat = oc_getreg(i2c, OCI2C_STATUS);

	अगर (i2c->flags & OCORES_FLAG_BROKEN_IRQ) अणु
		अगर ((stat & OCI2C_STAT_IF) && !(stat & OCI2C_STAT_BUSY))
			वापस IRQ_NONE;
	पूर्ण अन्यथा अगर (!(stat & OCI2C_STAT_IF)) अणु
		वापस IRQ_NONE;
	पूर्ण
	ocores_process(i2c, stat);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * ocores_process_समयout() - Process समयout event
 * @i2c: ocores I2C device instance
 */
अटल व्योम ocores_process_समयout(काष्ठा ocores_i2c *i2c)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&i2c->process_lock, flags);
	i2c->state = STATE_ERROR;
	oc_setreg(i2c, OCI2C_CMD, OCI2C_CMD_STOP);
	spin_unlock_irqrestore(&i2c->process_lock, flags);
पूर्ण

/**
 * ocores_रुको() - Wait until something change in a given रेजिस्टर
 * @i2c: ocores I2C device instance
 * @reg: रेजिस्टर to query
 * @mask: biपंचांगask to apply on रेजिस्टर value
 * @val: expected result
 * @समयout: समयout in jअगरfies
 *
 * Timeout is necessary to aव्योम to stay here क्रमever when the chip
 * करोes not answer correctly.
 *
 * Return: 0 on success, -ETIMEDOUT on समयout
 */
अटल पूर्णांक ocores_रुको(काष्ठा ocores_i2c *i2c,
		       पूर्णांक reg, u8 mask, u8 val,
		       स्थिर अचिन्हित दीर्घ समयout)
अणु
	अचिन्हित दीर्घ j;

	j = jअगरfies + समयout;
	जबतक (1) अणु
		u8 status = oc_getreg(i2c, reg);

		अगर ((status & mask) == val)
			अवरोध;

		अगर (समय_after(jअगरfies, j))
			वापस -ETIMEDOUT;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * ocores_poll_रुको() - Wait until is possible to process some data
 * @i2c: ocores I2C device instance
 *
 * Used when the device is in polling mode (पूर्णांकerrupts disabled).
 *
 * Return: 0 on success, -ETIMEDOUT on समयout
 */
अटल पूर्णांक ocores_poll_रुको(काष्ठा ocores_i2c *i2c)
अणु
	u8 mask;
	पूर्णांक err;

	अगर (i2c->state == STATE_DONE || i2c->state == STATE_ERROR) अणु
		/* transfer is over */
		mask = OCI2C_STAT_BUSY;
	पूर्ण अन्यथा अणु
		/* on going transfer */
		mask = OCI2C_STAT_TIP;
		/*
		 * We रुको क्रम the data to be transferred (8bit),
		 * then we start polling on the ACK/NACK bit
		 */
		udelay((8 * 1000) / i2c->bus_घड़ी_khz);
	पूर्ण

	/*
	 * once we are here we expect to get the expected result immediately
	 * so अगर after 1ms we समयout then something is broken.
	 */
	err = ocores_रुको(i2c, OCI2C_STATUS, mask, 0, msecs_to_jअगरfies(1));
	अगर (err)
		dev_warn(i2c->adap.dev.parent,
			 "%s: STATUS timeout, bit 0x%x did not clear in 1ms\n",
			 __func__, mask);
	वापस err;
पूर्ण

/**
 * ocores_process_polling() - It handles an IRQ-less transfer
 * @i2c: ocores I2C device instance
 *
 * Even अगर IRQ are disabled, the I2C OpenCore IP behavior is exactly the same
 * (only that IRQ are not produced). This means that we can re-use entirely
 * ocores_isr(), we just add our polling code around it.
 *
 * It can run in atomic context
 */
अटल व्योम ocores_process_polling(काष्ठा ocores_i2c *i2c)
अणु
	जबतक (1) अणु
		irqवापस_t ret;
		पूर्णांक err;

		err = ocores_poll_रुको(i2c);
		अगर (err) अणु
			i2c->state = STATE_ERROR;
			अवरोध; /* समयout */
		पूर्ण

		ret = ocores_isr(-1, i2c);
		अगर (ret == IRQ_NONE)
			अवरोध; /* all messages have been transferred */
		अन्यथा अणु
			अगर (i2c->flags & OCORES_FLAG_BROKEN_IRQ)
				अगर (i2c->state == STATE_DONE)
					अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक ocores_xfer_core(काष्ठा ocores_i2c *i2c,
			    काष्ठा i2c_msg *msgs, पूर्णांक num,
			    bool polling)
अणु
	पूर्णांक ret;
	u8 ctrl;

	ctrl = oc_getreg(i2c, OCI2C_CONTROL);
	अगर (polling)
		oc_setreg(i2c, OCI2C_CONTROL, ctrl & ~OCI2C_CTRL_IEN);
	अन्यथा
		oc_setreg(i2c, OCI2C_CONTROL, ctrl | OCI2C_CTRL_IEN);

	i2c->msg = msgs;
	i2c->pos = 0;
	i2c->nmsgs = num;
	i2c->state = STATE_START;

	oc_setreg(i2c, OCI2C_DATA, i2c_8bit_addr_from_msg(i2c->msg));
	oc_setreg(i2c, OCI2C_CMD, OCI2C_CMD_START);

	अगर (polling) अणु
		ocores_process_polling(i2c);
	पूर्ण अन्यथा अणु
		ret = रुको_event_समयout(i2c->रुको,
					 (i2c->state == STATE_ERROR) ||
					 (i2c->state == STATE_DONE), HZ);
		अगर (ret == 0) अणु
			ocores_process_समयout(i2c);
			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण

	वापस (i2c->state == STATE_DONE) ? num : -EIO;
पूर्ण

अटल पूर्णांक ocores_xfer_polling(काष्ठा i2c_adapter *adap,
			       काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	वापस ocores_xfer_core(i2c_get_adapdata(adap), msgs, num, true);
पूर्ण

अटल पूर्णांक ocores_xfer(काष्ठा i2c_adapter *adap,
		       काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	वापस ocores_xfer_core(i2c_get_adapdata(adap), msgs, num, false);
पूर्ण

अटल पूर्णांक ocores_init(काष्ठा device *dev, काष्ठा ocores_i2c *i2c)
अणु
	पूर्णांक prescale;
	पूर्णांक dअगरf;
	u8 ctrl = oc_getreg(i2c, OCI2C_CONTROL);

	/* make sure the device is disabled */
	ctrl &= ~(OCI2C_CTRL_EN | OCI2C_CTRL_IEN);
	oc_setreg(i2c, OCI2C_CONTROL, ctrl);

	prescale = (i2c->ip_घड़ी_khz / (5 * i2c->bus_घड़ी_khz)) - 1;
	prescale = clamp(prescale, 0, 0xffff);

	dअगरf = i2c->ip_घड़ी_khz / (5 * (prescale + 1)) - i2c->bus_घड़ी_khz;
	अगर (असल(dअगरf) > i2c->bus_घड़ी_khz / 10) अणु
		dev_err(dev,
			"Unsupported clock settings: core: %d KHz, bus: %d KHz\n",
			i2c->ip_घड़ी_khz, i2c->bus_घड़ी_khz);
		वापस -EINVAL;
	पूर्ण

	oc_setreg(i2c, OCI2C_PRELOW, prescale & 0xff);
	oc_setreg(i2c, OCI2C_PREHIGH, prescale >> 8);

	/* Init the device */
	oc_setreg(i2c, OCI2C_CMD, OCI2C_CMD_IACK);
	oc_setreg(i2c, OCI2C_CONTROL, ctrl | OCI2C_CTRL_EN);

	वापस 0;
पूर्ण


अटल u32 ocores_func(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;
पूर्ण

अटल काष्ठा i2c_algorithm ocores_algorithm = अणु
	.master_xfer = ocores_xfer,
	.master_xfer_atomic = ocores_xfer_polling,
	.functionality = ocores_func,
पूर्ण;

अटल स्थिर काष्ठा i2c_adapter ocores_adapter = अणु
	.owner = THIS_MODULE,
	.name = "i2c-ocores",
	.class = I2C_CLASS_DEPRECATED,
	.algo = &ocores_algorithm,
पूर्ण;

अटल स्थिर काष्ठा of_device_id ocores_i2c_match[] = अणु
	अणु
		.compatible = "opencores,i2c-ocores",
		.data = (व्योम *)TYPE_OCORES,
	पूर्ण,
	अणु
		.compatible = "aeroflexgaisler,i2cmst",
		.data = (व्योम *)TYPE_GRLIB,
	पूर्ण,
	अणु
		.compatible = "sifive,fu540-c000-i2c",
	पूर्ण,
	अणु
		.compatible = "sifive,i2c0",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ocores_i2c_match);

#अगर_घोषित CONFIG_OF
/*
 * Read and ग_लिखो functions क्रम the GRLIB port of the controller. Registers are
 * 32-bit big endian and the PRELOW and PREHIGH रेजिस्टरs are merged पूर्णांकo one
 * रेजिस्टर. The subsequent रेजिस्टरs have their offsets decreased accordingly.
 */
अटल u8 oc_getreg_grlib(काष्ठा ocores_i2c *i2c, पूर्णांक reg)
अणु
	u32 rd;
	पूर्णांक rreg = reg;

	अगर (reg != OCI2C_PRELOW)
		rreg--;
	rd = ioपढ़ो32be(i2c->base + (rreg << i2c->reg_shअगरt));
	अगर (reg == OCI2C_PREHIGH)
		वापस (u8)(rd >> 8);
	अन्यथा
		वापस (u8)rd;
पूर्ण

अटल व्योम oc_setreg_grlib(काष्ठा ocores_i2c *i2c, पूर्णांक reg, u8 value)
अणु
	u32 curr, wr;
	पूर्णांक rreg = reg;

	अगर (reg != OCI2C_PRELOW)
		rreg--;
	अगर (reg == OCI2C_PRELOW || reg == OCI2C_PREHIGH) अणु
		curr = ioपढ़ो32be(i2c->base + (rreg << i2c->reg_shअगरt));
		अगर (reg == OCI2C_PRELOW)
			wr = (curr & 0xff00) | value;
		अन्यथा
			wr = (((u32)value) << 8) | (curr & 0xff);
	पूर्ण अन्यथा अणु
		wr = value;
	पूर्ण
	ioग_लिखो32be(wr, i2c->base + (rreg << i2c->reg_shअगरt));
पूर्ण

अटल पूर्णांक ocores_i2c_of_probe(काष्ठा platक्रमm_device *pdev,
				काष्ठा ocores_i2c *i2c)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	स्थिर काष्ठा of_device_id *match;
	u32 val;
	u32 घड़ी_frequency;
	bool घड़ी_frequency_present;

	अगर (of_property_पढ़ो_u32(np, "reg-shift", &i2c->reg_shअगरt)) अणु
		/* no 'reg-shift', check for deprecated 'regstep' */
		अगर (!of_property_पढ़ो_u32(np, "regstep", &val)) अणु
			अगर (!is_घातer_of_2(val)) अणु
				dev_err(&pdev->dev, "invalid regstep %d\n",
					val);
				वापस -EINVAL;
			पूर्ण
			i2c->reg_shअगरt = ilog2(val);
			dev_warn(&pdev->dev,
				"regstep property deprecated, use reg-shift\n");
		पूर्ण
	पूर्ण

	घड़ी_frequency_present = !of_property_पढ़ो_u32(np, "clock-frequency",
							&घड़ी_frequency);
	i2c->bus_घड़ी_khz = 100;

	i2c->clk = devm_clk_get(&pdev->dev, शून्य);

	अगर (!IS_ERR(i2c->clk)) अणु
		पूर्णांक ret = clk_prepare_enable(i2c->clk);

		अगर (ret) अणु
			dev_err(&pdev->dev,
				"clk_prepare_enable failed: %d\n", ret);
			वापस ret;
		पूर्ण
		i2c->ip_घड़ी_khz = clk_get_rate(i2c->clk) / 1000;
		अगर (घड़ी_frequency_present)
			i2c->bus_घड़ी_khz = घड़ी_frequency / 1000;
	पूर्ण

	अगर (i2c->ip_घड़ी_khz == 0) अणु
		अगर (of_property_पढ़ो_u32(np, "opencores,ip-clock-frequency",
						&val)) अणु
			अगर (!घड़ी_frequency_present) अणु
				dev_err(&pdev->dev,
					"Missing required parameter 'opencores,ip-clock-frequency'\n");
				clk_disable_unprepare(i2c->clk);
				वापस -ENODEV;
			पूर्ण
			i2c->ip_घड़ी_khz = घड़ी_frequency / 1000;
			dev_warn(&pdev->dev,
				 "Deprecated usage of the 'clock-frequency' property, please update to 'opencores,ip-clock-frequency'\n");
		पूर्ण अन्यथा अणु
			i2c->ip_घड़ी_khz = val / 1000;
			अगर (घड़ी_frequency_present)
				i2c->bus_घड़ी_khz = घड़ी_frequency / 1000;
		पूर्ण
	पूर्ण

	of_property_पढ़ो_u32(pdev->dev.of_node, "reg-io-width",
				&i2c->reg_io_width);

	match = of_match_node(ocores_i2c_match, pdev->dev.of_node);
	अगर (match && (दीर्घ)match->data == TYPE_GRLIB) अणु
		dev_dbg(&pdev->dev, "GRLIB variant of i2c-ocores\n");
		i2c->setreg = oc_setreg_grlib;
		i2c->getreg = oc_getreg_grlib;
	पूर्ण

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा ocores_i2c_of_probe(pdev, i2c) -ENODEV
#पूर्ण_अगर

अटल पूर्णांक ocores_i2c_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ocores_i2c *i2c;
	काष्ठा ocores_i2c_platक्रमm_data *pdata;
	काष्ठा resource *res;
	पूर्णांक irq;
	पूर्णांक ret;
	पूर्णांक i;

	i2c = devm_kzalloc(&pdev->dev, माप(*i2c), GFP_KERNEL);
	अगर (!i2c)
		वापस -ENOMEM;

	spin_lock_init(&i2c->process_lock);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (res) अणु
		i2c->base = devm_ioremap_resource(&pdev->dev, res);
		अगर (IS_ERR(i2c->base))
			वापस PTR_ERR(i2c->base);
	पूर्ण अन्यथा अणु
		res = platक्रमm_get_resource(pdev, IORESOURCE_IO, 0);
		अगर (!res)
			वापस -EINVAL;
		i2c->iobase = res->start;
		अगर (!devm_request_region(&pdev->dev, res->start,
					 resource_size(res),
					 pdev->name)) अणु
			dev_err(&pdev->dev, "Can't get I/O resource.\n");
			वापस -EBUSY;
		पूर्ण
		i2c->setreg = oc_setreg_io_8;
		i2c->getreg = oc_getreg_io_8;
	पूर्ण

	pdata = dev_get_platdata(&pdev->dev);
	अगर (pdata) अणु
		i2c->reg_shअगरt = pdata->reg_shअगरt;
		i2c->reg_io_width = pdata->reg_io_width;
		i2c->ip_घड़ी_khz = pdata->घड़ी_khz;
		अगर (pdata->bus_khz)
			i2c->bus_घड़ी_khz = pdata->bus_khz;
		अन्यथा
			i2c->bus_घड़ी_khz = 100;
	पूर्ण अन्यथा अणु
		ret = ocores_i2c_of_probe(pdev, i2c);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (i2c->reg_io_width == 0)
		i2c->reg_io_width = 1; /* Set to शेष value */

	अगर (!i2c->setreg || !i2c->getreg) अणु
		bool be = pdata ? pdata->big_endian :
			of_device_is_big_endian(pdev->dev.of_node);

		चयन (i2c->reg_io_width) अणु
		हाल 1:
			i2c->setreg = oc_setreg_8;
			i2c->getreg = oc_getreg_8;
			अवरोध;

		हाल 2:
			i2c->setreg = be ? oc_setreg_16be : oc_setreg_16;
			i2c->getreg = be ? oc_getreg_16be : oc_getreg_16;
			अवरोध;

		हाल 4:
			i2c->setreg = be ? oc_setreg_32be : oc_setreg_32;
			i2c->getreg = be ? oc_getreg_32be : oc_getreg_32;
			अवरोध;

		शेष:
			dev_err(&pdev->dev, "Unsupported I/O width (%d)\n",
				i2c->reg_io_width);
			ret = -EINVAL;
			जाओ err_clk;
		पूर्ण
	पूर्ण

	init_रुकोqueue_head(&i2c->रुको);

	irq = platक्रमm_get_irq_optional(pdev, 0);
	/*
	 * Since the SoC करोes have an पूर्णांकerrupt, its DT has an पूर्णांकerrupt
	 * property - But this should be bypassed as the IRQ logic in this
	 * SoC is broken.
	 */
	अगर (of_device_is_compatible(pdev->dev.of_node,
				    "sifive,fu540-c000-i2c")) अणु
		i2c->flags |= OCORES_FLAG_BROKEN_IRQ;
		irq = -ENXIO;
	पूर्ण

	अगर (irq == -ENXIO) अणु
		ocores_algorithm.master_xfer = ocores_xfer_polling;
	पूर्ण अन्यथा अणु
		अगर (irq < 0)
			वापस irq;
	पूर्ण

	अगर (ocores_algorithm.master_xfer != ocores_xfer_polling) अणु
		ret = devm_request_any_context_irq(&pdev->dev, irq,
						   ocores_isr, 0,
						   pdev->name, i2c);
		अगर (ret) अणु
			dev_err(&pdev->dev, "Cannot claim IRQ\n");
			जाओ err_clk;
		पूर्ण
	पूर्ण

	ret = ocores_init(&pdev->dev, i2c);
	अगर (ret)
		जाओ err_clk;

	/* hook up driver to tree */
	platक्रमm_set_drvdata(pdev, i2c);
	i2c->adap = ocores_adapter;
	i2c_set_adapdata(&i2c->adap, i2c);
	i2c->adap.dev.parent = &pdev->dev;
	i2c->adap.dev.of_node = pdev->dev.of_node;

	/* add i2c adapter to i2c tree */
	ret = i2c_add_adapter(&i2c->adap);
	अगर (ret)
		जाओ err_clk;

	/* add in known devices to the bus */
	अगर (pdata) अणु
		क्रम (i = 0; i < pdata->num_devices; i++)
			i2c_new_client_device(&i2c->adap, pdata->devices + i);
	पूर्ण

	वापस 0;

err_clk:
	clk_disable_unprepare(i2c->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक ocores_i2c_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ocores_i2c *i2c = platक्रमm_get_drvdata(pdev);
	u8 ctrl = oc_getreg(i2c, OCI2C_CONTROL);

	/* disable i2c logic */
	ctrl &= ~(OCI2C_CTRL_EN | OCI2C_CTRL_IEN);
	oc_setreg(i2c, OCI2C_CONTROL, ctrl);

	/* हटाओ adapter & data */
	i2c_del_adapter(&i2c->adap);

	अगर (!IS_ERR(i2c->clk))
		clk_disable_unprepare(i2c->clk);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक ocores_i2c_suspend(काष्ठा device *dev)
अणु
	काष्ठा ocores_i2c *i2c = dev_get_drvdata(dev);
	u8 ctrl = oc_getreg(i2c, OCI2C_CONTROL);

	/* make sure the device is disabled */
	ctrl &= ~(OCI2C_CTRL_EN | OCI2C_CTRL_IEN);
	oc_setreg(i2c, OCI2C_CONTROL, ctrl);

	अगर (!IS_ERR(i2c->clk))
		clk_disable_unprepare(i2c->clk);
	वापस 0;
पूर्ण

अटल पूर्णांक ocores_i2c_resume(काष्ठा device *dev)
अणु
	काष्ठा ocores_i2c *i2c = dev_get_drvdata(dev);

	अगर (!IS_ERR(i2c->clk)) अणु
		अचिन्हित दीर्घ rate;
		पूर्णांक ret = clk_prepare_enable(i2c->clk);

		अगर (ret) अणु
			dev_err(dev,
				"clk_prepare_enable failed: %d\n", ret);
			वापस ret;
		पूर्ण
		rate = clk_get_rate(i2c->clk) / 1000;
		अगर (rate)
			i2c->ip_घड़ी_khz = rate;
	पूर्ण
	वापस ocores_init(dev, i2c);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(ocores_i2c_pm, ocores_i2c_suspend, ocores_i2c_resume);
#घोषणा OCORES_I2C_PM	(&ocores_i2c_pm)
#अन्यथा
#घोषणा OCORES_I2C_PM	शून्य
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver ocores_i2c_driver = अणु
	.probe   = ocores_i2c_probe,
	.हटाओ  = ocores_i2c_हटाओ,
	.driver  = अणु
		.name = "ocores-i2c",
		.of_match_table = ocores_i2c_match,
		.pm = OCORES_I2C_PM,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(ocores_i2c_driver);

MODULE_AUTHOR("Peter Korsgaard <peter@korsgaard.com>");
MODULE_DESCRIPTION("OpenCores I2C bus driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:ocores-i2c");
