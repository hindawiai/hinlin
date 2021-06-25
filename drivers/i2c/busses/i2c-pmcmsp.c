<शैली गुरु>
/*
 * Specअगरic bus support क्रम PMC-TWI compliant implementation on MSP71xx.
 *
 * Copyright 2005-2007 PMC-Sierra, Inc.
 *
 *  This program is मुक्त software; you can redistribute  it and/or modअगरy it
 *  under  the terms of  the GNU General  Public License as published by the
 *  Free Software Foundation;  either version 2 of the  License, or (at your
 *  option) any later version.
 *
 *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS'' AND   ANY  EXPRESS OR IMPLIED
 *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN
 *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   सूचीECT, INसूचीECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF
 *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/completion.h>
#समावेश <linux/mutex.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>

#घोषणा DRV_NAME	"pmcmsptwi"

#घोषणा MSP_TWI_SF_CLK_REG_OFFSET	0x00
#घोषणा MSP_TWI_HS_CLK_REG_OFFSET	0x04
#घोषणा MSP_TWI_CFG_REG_OFFSET		0x08
#घोषणा MSP_TWI_CMD_REG_OFFSET		0x0c
#घोषणा MSP_TWI_ADD_REG_OFFSET		0x10
#घोषणा MSP_TWI_DAT_0_REG_OFFSET	0x14
#घोषणा MSP_TWI_DAT_1_REG_OFFSET	0x18
#घोषणा MSP_TWI_INT_STS_REG_OFFSET	0x1c
#घोषणा MSP_TWI_INT_MSK_REG_OFFSET	0x20
#घोषणा MSP_TWI_BUSY_REG_OFFSET		0x24

#घोषणा MSP_TWI_INT_STS_DONE			(1 << 0)
#घोषणा MSP_TWI_INT_STS_LOST_ARBITRATION	(1 << 1)
#घोषणा MSP_TWI_INT_STS_NO_RESPONSE		(1 << 2)
#घोषणा MSP_TWI_INT_STS_DATA_COLLISION		(1 << 3)
#घोषणा MSP_TWI_INT_STS_BUSY			(1 << 4)
#घोषणा MSP_TWI_INT_STS_ALL			0x1f

#घोषणा MSP_MAX_BYTES_PER_RW		8
#घोषणा MSP_MAX_POLL			5
#घोषणा MSP_POLL_DELAY			10
#घोषणा MSP_IRQ_TIMEOUT			(MSP_MAX_POLL * MSP_POLL_DELAY)

/* IO Operation macros */
#घोषणा pmcmsptwi_पढ़ोl		__raw_पढ़ोl
#घोषणा pmcmsptwi_ग_लिखोl	__raw_ग_लिखोl

/* TWI command type */
क्रमागत pmcmsptwi_cmd_type अणु
	MSP_TWI_CMD_WRITE	= 0,	/* Write only */
	MSP_TWI_CMD_READ	= 1,	/* Read only */
	MSP_TWI_CMD_WRITE_READ	= 2,	/* Write then Read */
पूर्ण;

/* The possible results of the xferCmd */
क्रमागत pmcmsptwi_xfer_result अणु
	MSP_TWI_XFER_OK	= 0,
	MSP_TWI_XFER_TIMEOUT,
	MSP_TWI_XFER_BUSY,
	MSP_TWI_XFER_DATA_COLLISION,
	MSP_TWI_XFER_NO_RESPONSE,
	MSP_TWI_XFER_LOST_ARBITRATION,
पूर्ण;

/* Corresponds to a PMCTWI घड़ी configuration रेजिस्टर */
काष्ठा pmcmsptwi_घड़ी अणु
	u8 filter;	/* Bits 15:12,	शेष = 0x03 */
	u16 घड़ी;	/* Bits 9:0,	शेष = 0x001f */
पूर्ण;

काष्ठा pmcmsptwi_घड़ीcfg अणु
	काष्ठा pmcmsptwi_घड़ी standard;  /* The standard/fast घड़ी config */
	काष्ठा pmcmsptwi_घड़ी highspeed; /* The highspeed घड़ी config */
पूर्ण;

/* Corresponds to the मुख्य TWI configuration रेजिस्टर */
काष्ठा pmcmsptwi_cfg अणु
	u8 arbf;	/* Bits 15:12,	शेष=0x03 */
	u8 nak;		/* Bits 11:8,	शेष=0x03 */
	u8 add10;	/* Bit 7,	शेष=0x00 */
	u8 mst_code;	/* Bits 6:4,	शेष=0x00 */
	u8 arb;		/* Bit 1,	शेष=0x01 */
	u8 highspeed;	/* Bit 0,	शेष=0x00 */
पूर्ण;

/* A single pmctwi command to issue */
काष्ठा pmcmsptwi_cmd अणु
	u16 addr;	/* The slave address (7 or 10 bits) */
	क्रमागत pmcmsptwi_cmd_type type;	/* The command type */
	u8 ग_लिखो_len;	/* Number of bytes in the ग_लिखो buffer */
	u8 पढ़ो_len;	/* Number of bytes in the पढ़ो buffer */
	u8 *ग_लिखो_data;	/* Buffer of अक्षरacters to send */
	u8 *पढ़ो_data;	/* Buffer to fill with incoming data */
पूर्ण;

/* The निजी data */
काष्ठा pmcmsptwi_data अणु
	व्योम __iomem *iobase;			/* iomapped base क्रम IO */
	पूर्णांक irq;				/* IRQ to use (0 disables) */
	काष्ठा completion रुको;			/* Completion क्रम xfer */
	काष्ठा mutex lock;			/* Used क्रम thपढ़ोsafeness */
	क्रमागत pmcmsptwi_xfer_result last_result;	/* result of last xfer */
पूर्ण;

/* The शेष settings */
अटल स्थिर काष्ठा pmcmsptwi_घड़ीcfg pmcmsptwi_defघड़ीcfg = अणु
	.standard = अणु
		.filter	= 0x3,
		.घड़ी	= 0x1f,
	पूर्ण,
	.highspeed = अणु
		.filter	= 0x3,
		.घड़ी	= 0x1f,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pmcmsptwi_cfg pmcmsptwi_defcfg = अणु
	.arbf		= 0x03,
	.nak		= 0x03,
	.add10		= 0x00,
	.mst_code	= 0x00,
	.arb		= 0x01,
	.highspeed	= 0x00,
पूर्ण;

अटल काष्ठा pmcmsptwi_data pmcmsptwi_data;

अटल काष्ठा i2c_adapter pmcmsptwi_adapter;

/* अंतरभूत helper functions */
अटल अंतरभूत u32 pmcmsptwi_घड़ी_प्रकारo_reg(
			स्थिर काष्ठा pmcmsptwi_घड़ी *घड़ी)
अणु
	वापस ((घड़ी->filter & 0xf) << 12) | (घड़ी->घड़ी & 0x03ff);
पूर्ण

अटल अंतरभूत u32 pmcmsptwi_cfg_to_reg(स्थिर काष्ठा pmcmsptwi_cfg *cfg)
अणु
	वापस ((cfg->arbf & 0xf) << 12) |
		((cfg->nak & 0xf) << 8) |
		((cfg->add10 & 0x1) << 7) |
		((cfg->mst_code & 0x7) << 4) |
		((cfg->arb & 0x1) << 1) |
		(cfg->highspeed & 0x1);
पूर्ण

अटल अंतरभूत व्योम pmcmsptwi_reg_to_cfg(u32 reg, काष्ठा pmcmsptwi_cfg *cfg)
अणु
	cfg->arbf = (reg >> 12) & 0xf;
	cfg->nak = (reg >> 8) & 0xf;
	cfg->add10 = (reg >> 7) & 0x1;
	cfg->mst_code = (reg >> 4) & 0x7;
	cfg->arb = (reg >> 1) & 0x1;
	cfg->highspeed = reg & 0x1;
पूर्ण

/*
 * Sets the current घड़ी configuration
 */
अटल व्योम pmcmsptwi_set_घड़ी_config(स्थिर काष्ठा pmcmsptwi_घड़ीcfg *cfg,
					काष्ठा pmcmsptwi_data *data)
अणु
	mutex_lock(&data->lock);
	pmcmsptwi_ग_लिखोl(pmcmsptwi_घड़ी_प्रकारo_reg(&cfg->standard),
				data->iobase + MSP_TWI_SF_CLK_REG_OFFSET);
	pmcmsptwi_ग_लिखोl(pmcmsptwi_घड़ी_प्रकारo_reg(&cfg->highspeed),
				data->iobase + MSP_TWI_HS_CLK_REG_OFFSET);
	mutex_unlock(&data->lock);
पूर्ण

/*
 * Gets the current TWI bus configuration
 */
अटल व्योम pmcmsptwi_get_twi_config(काष्ठा pmcmsptwi_cfg *cfg,
					काष्ठा pmcmsptwi_data *data)
अणु
	mutex_lock(&data->lock);
	pmcmsptwi_reg_to_cfg(pmcmsptwi_पढ़ोl(
				data->iobase + MSP_TWI_CFG_REG_OFFSET), cfg);
	mutex_unlock(&data->lock);
पूर्ण

/*
 * Sets the current TWI bus configuration
 */
अटल व्योम pmcmsptwi_set_twi_config(स्थिर काष्ठा pmcmsptwi_cfg *cfg,
					काष्ठा pmcmsptwi_data *data)
अणु
	mutex_lock(&data->lock);
	pmcmsptwi_ग_लिखोl(pmcmsptwi_cfg_to_reg(cfg),
				data->iobase + MSP_TWI_CFG_REG_OFFSET);
	mutex_unlock(&data->lock);
पूर्ण

/*
 * Parses the 'int_sts' रेजिस्टर and वापसs a well-defined error code
 */
अटल क्रमागत pmcmsptwi_xfer_result pmcmsptwi_get_result(u32 reg)
अणु
	अगर (reg & MSP_TWI_INT_STS_LOST_ARBITRATION) अणु
		dev_dbg(&pmcmsptwi_adapter.dev,
			"Result: Lost arbitration\n");
		वापस MSP_TWI_XFER_LOST_ARBITRATION;
	पूर्ण अन्यथा अगर (reg & MSP_TWI_INT_STS_NO_RESPONSE) अणु
		dev_dbg(&pmcmsptwi_adapter.dev,
			"Result: No response\n");
		वापस MSP_TWI_XFER_NO_RESPONSE;
	पूर्ण अन्यथा अगर (reg & MSP_TWI_INT_STS_DATA_COLLISION) अणु
		dev_dbg(&pmcmsptwi_adapter.dev,
			"Result: Data collision\n");
		वापस MSP_TWI_XFER_DATA_COLLISION;
	पूर्ण अन्यथा अगर (reg & MSP_TWI_INT_STS_BUSY) अणु
		dev_dbg(&pmcmsptwi_adapter.dev,
			"Result: Bus busy\n");
		वापस MSP_TWI_XFER_BUSY;
	पूर्ण

	dev_dbg(&pmcmsptwi_adapter.dev, "Result: Operation succeeded\n");
	वापस MSP_TWI_XFER_OK;
पूर्ण

/*
 * In पूर्णांकerrupt mode, handle the पूर्णांकerrupt.
 * NOTE: Assumes data->lock is held.
 */
अटल irqवापस_t pmcmsptwi_पूर्णांकerrupt(पूर्णांक irq, व्योम *ptr)
अणु
	काष्ठा pmcmsptwi_data *data = ptr;

	u32 reason = pmcmsptwi_पढ़ोl(data->iobase +
					MSP_TWI_INT_STS_REG_OFFSET);
	pmcmsptwi_ग_लिखोl(reason, data->iobase + MSP_TWI_INT_STS_REG_OFFSET);

	dev_dbg(&pmcmsptwi_adapter.dev, "Got interrupt 0x%08x\n", reason);
	अगर (!(reason & MSP_TWI_INT_STS_DONE))
		वापस IRQ_NONE;

	data->last_result = pmcmsptwi_get_result(reason);
	complete(&data->रुको);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * Probe क्रम and रेजिस्टर the device and वापस 0 अगर there is one.
 */
अटल पूर्णांक pmcmsptwi_probe(काष्ठा platक्रमm_device *pldev)
अणु
	काष्ठा resource *res;
	पूर्णांक rc = -ENODEV;

	/* get the अटल platक्रमm resources */
	res = platक्रमm_get_resource(pldev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		dev_err(&pldev->dev, "IOMEM resource not found\n");
		जाओ ret_err;
	पूर्ण

	/* reserve the memory region */
	अगर (!request_mem_region(res->start, resource_size(res),
				pldev->name)) अणु
		dev_err(&pldev->dev,
			"Unable to get memory/io address region %pap\n",
			&res->start);
		rc = -EBUSY;
		जाओ ret_err;
	पूर्ण

	/* remap the memory */
	pmcmsptwi_data.iobase = ioremap(res->start,
						resource_size(res));
	अगर (!pmcmsptwi_data.iobase) अणु
		dev_err(&pldev->dev,
			"Unable to ioremap address %pap\n", &res->start);
		rc = -EIO;
		जाओ ret_unreserve;
	पूर्ण

	/* request the irq */
	pmcmsptwi_data.irq = platक्रमm_get_irq(pldev, 0);
	अगर (pmcmsptwi_data.irq) अणु
		rc = request_irq(pmcmsptwi_data.irq, &pmcmsptwi_पूर्णांकerrupt,
				 IRQF_SHARED, pldev->name, &pmcmsptwi_data);
		अगर (rc == 0) अणु
			/*
			 * Enable 'DONE' पूर्णांकerrupt only.
			 *
			 * If you enable all पूर्णांकerrupts, you will get one on
			 * error and another when the operation completes.
			 * This way you only have to handle one पूर्णांकerrupt,
			 * but you can still check all result flags.
			 */
			pmcmsptwi_ग_लिखोl(MSP_TWI_INT_STS_DONE,
					pmcmsptwi_data.iobase +
					MSP_TWI_INT_MSK_REG_OFFSET);
		पूर्ण अन्यथा अणु
			dev_warn(&pldev->dev,
				"Could not assign TWI IRQ handler "
				"to irq %d (continuing with poll)\n",
				pmcmsptwi_data.irq);
			pmcmsptwi_data.irq = 0;
		पूर्ण
	पूर्ण

	init_completion(&pmcmsptwi_data.रुको);
	mutex_init(&pmcmsptwi_data.lock);

	pmcmsptwi_set_घड़ी_config(&pmcmsptwi_defघड़ीcfg, &pmcmsptwi_data);
	pmcmsptwi_set_twi_config(&pmcmsptwi_defcfg, &pmcmsptwi_data);

	prपूर्णांकk(KERN_INFO DRV_NAME ": Registering MSP71xx I2C adapter\n");

	pmcmsptwi_adapter.dev.parent = &pldev->dev;
	platक्रमm_set_drvdata(pldev, &pmcmsptwi_adapter);
	i2c_set_adapdata(&pmcmsptwi_adapter, &pmcmsptwi_data);

	rc = i2c_add_adapter(&pmcmsptwi_adapter);
	अगर (rc)
		जाओ ret_unmap;

	वापस 0;

ret_unmap:
	अगर (pmcmsptwi_data.irq) अणु
		pmcmsptwi_ग_लिखोl(0,
			pmcmsptwi_data.iobase + MSP_TWI_INT_MSK_REG_OFFSET);
		मुक्त_irq(pmcmsptwi_data.irq, &pmcmsptwi_data);
	पूर्ण

	iounmap(pmcmsptwi_data.iobase);

ret_unreserve:
	release_mem_region(res->start, resource_size(res));

ret_err:
	वापस rc;
पूर्ण

/*
 * Release the device and वापस 0 अगर there is one.
 */
अटल पूर्णांक pmcmsptwi_हटाओ(काष्ठा platक्रमm_device *pldev)
अणु
	काष्ठा resource *res;

	i2c_del_adapter(&pmcmsptwi_adapter);

	अगर (pmcmsptwi_data.irq) अणु
		pmcmsptwi_ग_लिखोl(0,
			pmcmsptwi_data.iobase + MSP_TWI_INT_MSK_REG_OFFSET);
		मुक्त_irq(pmcmsptwi_data.irq, &pmcmsptwi_data);
	पूर्ण

	iounmap(pmcmsptwi_data.iobase);

	res = platक्रमm_get_resource(pldev, IORESOURCE_MEM, 0);
	release_mem_region(res->start, resource_size(res));

	वापस 0;
पूर्ण

/*
 * Polls the 'busy' रेजिस्टर until the command is complete.
 * NOTE: Assumes data->lock is held.
 */
अटल व्योम pmcmsptwi_poll_complete(काष्ठा pmcmsptwi_data *data)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MSP_MAX_POLL; i++) अणु
		u32 val = pmcmsptwi_पढ़ोl(data->iobase +
						MSP_TWI_BUSY_REG_OFFSET);
		अगर (val == 0) अणु
			u32 reason = pmcmsptwi_पढ़ोl(data->iobase +
						MSP_TWI_INT_STS_REG_OFFSET);
			pmcmsptwi_ग_लिखोl(reason, data->iobase +
						MSP_TWI_INT_STS_REG_OFFSET);
			data->last_result = pmcmsptwi_get_result(reason);
			वापस;
		पूर्ण
		udelay(MSP_POLL_DELAY);
	पूर्ण

	dev_dbg(&pmcmsptwi_adapter.dev, "Result: Poll timeout\n");
	data->last_result = MSP_TWI_XFER_TIMEOUT;
पूर्ण

/*
 * Do the transfer (low level):
 *   May use पूर्णांकerrupt-driven or polling, depending on अगर an IRQ is
 *   presently रेजिस्टरed.
 * NOTE: Assumes data->lock is held.
 */
अटल क्रमागत pmcmsptwi_xfer_result pmcmsptwi_करो_xfer(
			u32 reg, काष्ठा pmcmsptwi_data *data)
अणु
	dev_dbg(&pmcmsptwi_adapter.dev, "Writing cmd reg 0x%08x\n", reg);
	pmcmsptwi_ग_लिखोl(reg, data->iobase + MSP_TWI_CMD_REG_OFFSET);
	अगर (data->irq) अणु
		अचिन्हित दीर्घ समयleft = रुको_क्रम_completion_समयout(
						&data->रुको, MSP_IRQ_TIMEOUT);
		अगर (समयleft == 0) अणु
			dev_dbg(&pmcmsptwi_adapter.dev,
				"Result: IRQ timeout\n");
			complete(&data->रुको);
			data->last_result = MSP_TWI_XFER_TIMEOUT;
		पूर्ण
	पूर्ण अन्यथा
		pmcmsptwi_poll_complete(data);

	वापस data->last_result;
पूर्ण

/*
 * Helper routine, converts 'pmctwi_cmd' काष्ठा to रेजिस्टर क्रमmat
 */
अटल अंतरभूत u32 pmcmsptwi_cmd_to_reg(स्थिर काष्ठा pmcmsptwi_cmd *cmd)
अणु
	वापस ((cmd->type & 0x3) << 8) |
		(((cmd->ग_लिखो_len - 1) & 0x7) << 4) |
		((cmd->पढ़ो_len - 1) & 0x7);
पूर्ण

/*
 * Do the transfer (high level)
 */
अटल क्रमागत pmcmsptwi_xfer_result pmcmsptwi_xfer_cmd(
			काष्ठा pmcmsptwi_cmd *cmd,
			काष्ठा pmcmsptwi_data *data)
अणु
	क्रमागत pmcmsptwi_xfer_result retval;

	mutex_lock(&data->lock);
	dev_dbg(&pmcmsptwi_adapter.dev,
		"Setting address to 0x%04x\n", cmd->addr);
	pmcmsptwi_ग_लिखोl(cmd->addr, data->iobase + MSP_TWI_ADD_REG_OFFSET);

	अगर (cmd->type == MSP_TWI_CMD_WRITE ||
	    cmd->type == MSP_TWI_CMD_WRITE_READ) अणु
		u64 पंचांगp = be64_to_cpup((__be64 *)cmd->ग_लिखो_data);
		पंचांगp >>= (MSP_MAX_BYTES_PER_RW - cmd->ग_लिखो_len) * 8;
		dev_dbg(&pmcmsptwi_adapter.dev, "Writing 0x%016llx\n", पंचांगp);
		pmcmsptwi_ग_लिखोl(पंचांगp & 0x00000000ffffffffLL,
				data->iobase + MSP_TWI_DAT_0_REG_OFFSET);
		अगर (cmd->ग_लिखो_len > 4)
			pmcmsptwi_ग_लिखोl(पंचांगp >> 32,
				data->iobase + MSP_TWI_DAT_1_REG_OFFSET);
	पूर्ण

	retval = pmcmsptwi_करो_xfer(pmcmsptwi_cmd_to_reg(cmd), data);
	अगर (retval != MSP_TWI_XFER_OK)
		जाओ xfer_err;

	अगर (cmd->type == MSP_TWI_CMD_READ ||
	    cmd->type == MSP_TWI_CMD_WRITE_READ) अणु
		पूर्णांक i;
		u64 rmsk = ~(0xffffffffffffffffLL << (cmd->पढ़ो_len * 8));
		u64 पंचांगp = (u64)pmcmsptwi_पढ़ोl(data->iobase +
					MSP_TWI_DAT_0_REG_OFFSET);
		अगर (cmd->पढ़ो_len > 4)
			पंचांगp |= (u64)pmcmsptwi_पढ़ोl(data->iobase +
					MSP_TWI_DAT_1_REG_OFFSET) << 32;
		पंचांगp &= rmsk;
		dev_dbg(&pmcmsptwi_adapter.dev, "Read 0x%016llx\n", पंचांगp);

		क्रम (i = 0; i < cmd->पढ़ो_len; i++)
			cmd->पढ़ो_data[i] = पंचांगp >> i;
	पूर्ण

xfer_err:
	mutex_unlock(&data->lock);

	वापस retval;
पूर्ण

/* -- Algorithm functions -- */

/*
 * Sends an i2c command out on the adapter
 */
अटल पूर्णांक pmcmsptwi_master_xfer(काष्ठा i2c_adapter *adap,
				काष्ठा i2c_msg *msg, पूर्णांक num)
अणु
	काष्ठा pmcmsptwi_data *data = i2c_get_adapdata(adap);
	काष्ठा pmcmsptwi_cmd cmd;
	काष्ठा pmcmsptwi_cfg oldcfg, newcfg;
	पूर्णांक ret;

	अगर (num == 2) अणु
		काष्ठा i2c_msg *nexपंचांगsg = msg + 1;

		cmd.type = MSP_TWI_CMD_WRITE_READ;
		cmd.ग_लिखो_len = msg->len;
		cmd.ग_लिखो_data = msg->buf;
		cmd.पढ़ो_len = nexपंचांगsg->len;
		cmd.पढ़ो_data = nexपंचांगsg->buf;
	पूर्ण अन्यथा अगर (msg->flags & I2C_M_RD) अणु
		cmd.type = MSP_TWI_CMD_READ;
		cmd.पढ़ो_len = msg->len;
		cmd.पढ़ो_data = msg->buf;
		cmd.ग_लिखो_len = 0;
		cmd.ग_लिखो_data = शून्य;
	पूर्ण अन्यथा अणु
		cmd.type = MSP_TWI_CMD_WRITE;
		cmd.पढ़ो_len = 0;
		cmd.पढ़ो_data = शून्य;
		cmd.ग_लिखो_len = msg->len;
		cmd.ग_लिखो_data = msg->buf;
	पूर्ण

	cmd.addr = msg->addr;

	अगर (msg->flags & I2C_M_TEN) अणु
		pmcmsptwi_get_twi_config(&newcfg, data);
		स_नकल(&oldcfg, &newcfg, माप(oldcfg));

		/* Set the special 10-bit address flag */
		newcfg.add10 = 1;

		pmcmsptwi_set_twi_config(&newcfg, data);
	पूर्ण

	/* Execute the command */
	ret = pmcmsptwi_xfer_cmd(&cmd, data);

	अगर (msg->flags & I2C_M_TEN)
		pmcmsptwi_set_twi_config(&oldcfg, data);

	dev_dbg(&adap->dev, "I2C %s of %d bytes %s\n",
		(msg->flags & I2C_M_RD) ? "read" : "write", msg->len,
		(ret == MSP_TWI_XFER_OK) ? "succeeded" : "failed");

	अगर (ret != MSP_TWI_XFER_OK) अणु
		/*
		 * TODO: We could potentially loop and retry in the हाल
		 * of MSP_TWI_XFER_TIMEOUT.
		 */
		वापस -EIO;
	पूर्ण

	वापस num;
पूर्ण

अटल u32 pmcmsptwi_i2c_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_10BIT_ADDR |
		I2C_FUNC_SMBUS_BYTE | I2C_FUNC_SMBUS_BYTE_DATA |
		I2C_FUNC_SMBUS_WORD_DATA | I2C_FUNC_SMBUS_PROC_CALL;
पूर्ण

अटल स्थिर काष्ठा i2c_adapter_quirks pmcmsptwi_i2c_quirks = अणु
	.flags = I2C_AQ_COMB_WRITE_THEN_READ | I2C_AQ_NO_ZERO_LEN,
	.max_ग_लिखो_len = MSP_MAX_BYTES_PER_RW,
	.max_पढ़ो_len = MSP_MAX_BYTES_PER_RW,
	.max_comb_1st_msg_len = MSP_MAX_BYTES_PER_RW,
	.max_comb_2nd_msg_len = MSP_MAX_BYTES_PER_RW,
पूर्ण;

/* -- Initialization -- */

अटल स्थिर काष्ठा i2c_algorithm pmcmsptwi_algo = अणु
	.master_xfer	= pmcmsptwi_master_xfer,
	.functionality	= pmcmsptwi_i2c_func,
पूर्ण;

अटल काष्ठा i2c_adapter pmcmsptwi_adapter = अणु
	.owner		= THIS_MODULE,
	.class		= I2C_CLASS_HWMON | I2C_CLASS_SPD,
	.algo		= &pmcmsptwi_algo,
	.quirks		= &pmcmsptwi_i2c_quirks,
	.name		= DRV_NAME,
पूर्ण;

अटल काष्ठा platक्रमm_driver pmcmsptwi_driver = अणु
	.probe  = pmcmsptwi_probe,
	.हटाओ	= pmcmsptwi_हटाओ,
	.driver = अणु
		.name	= DRV_NAME,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(pmcmsptwi_driver);

MODULE_DESCRIPTION("PMC MSP TWI/SMBus/I2C driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRV_NAME);
