<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* bbc_i2c.c: I2C low-level driver क्रम BBC device on UltraSPARC-III
 *            platक्रमms.
 *
 * Copyright (C) 2001, 2008 David S. Miller (davem@davemloft.net)
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/रुको.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <यंत्र/bbc.h>
#समावेश <यंत्र/पन.स>

#समावेश "bbc_i2c.h"

/* Convert this driver to use i2c bus layer someday... */
#घोषणा I2C_PCF_PIN	0x80
#घोषणा I2C_PCF_ESO	0x40
#घोषणा I2C_PCF_ES1	0x20
#घोषणा I2C_PCF_ES2	0x10
#घोषणा I2C_PCF_ENI	0x08
#घोषणा I2C_PCF_STA	0x04
#घोषणा I2C_PCF_STO	0x02
#घोषणा I2C_PCF_ACK	0x01

#घोषणा I2C_PCF_START    (I2C_PCF_PIN | I2C_PCF_ESO | I2C_PCF_ENI | I2C_PCF_STA | I2C_PCF_ACK)
#घोषणा I2C_PCF_STOP     (I2C_PCF_PIN | I2C_PCF_ESO | I2C_PCF_STO | I2C_PCF_ACK)
#घोषणा I2C_PCF_REPSTART (              I2C_PCF_ESO | I2C_PCF_STA | I2C_PCF_ACK)
#घोषणा I2C_PCF_IDLE     (I2C_PCF_PIN | I2C_PCF_ESO               | I2C_PCF_ACK)

#घोषणा I2C_PCF_INI 0x40   /* 1 अगर not initialized */
#घोषणा I2C_PCF_STS 0x20
#घोषणा I2C_PCF_BER 0x10
#घोषणा I2C_PCF_AD0 0x08
#घोषणा I2C_PCF_LRB 0x08
#घोषणा I2C_PCF_AAS 0x04
#घोषणा I2C_PCF_LAB 0x02
#घोषणा I2C_PCF_BB  0x01

/* The BBC devices have two I2C controllers.  The first I2C controller
 * connects मुख्यly to configuration proms (NVRAM, cpu configuration,
 * dimm types, etc.).  Whereas the second I2C controller connects to
 * environmental control devices such as fans and temperature sensors.
 * The second controller also connects to the smartcard पढ़ोer, अगर present.
 */

अटल व्योम set_device_claimage(काष्ठा bbc_i2c_bus *bp, काष्ठा platक्रमm_device *op, पूर्णांक val)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NUM_CHILDREN; i++) अणु
		अगर (bp->devs[i].device == op) अणु
			bp->devs[i].client_claimed = val;
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

#घोषणा claim_device(BP,ECHILD)		set_device_claimage(BP,ECHILD,1)
#घोषणा release_device(BP,ECHILD)	set_device_claimage(BP,ECHILD,0)

काष्ठा platक्रमm_device *bbc_i2c_getdev(काष्ठा bbc_i2c_bus *bp, पूर्णांक index)
अणु
	काष्ठा platक्रमm_device *op = शून्य;
	पूर्णांक curidx = 0, i;

	क्रम (i = 0; i < NUM_CHILDREN; i++) अणु
		अगर (!(op = bp->devs[i].device))
			अवरोध;
		अगर (curidx == index)
			जाओ out;
		op = शून्य;
		curidx++;
	पूर्ण

out:
	अगर (curidx == index)
		वापस op;
	वापस शून्य;
पूर्ण

काष्ठा bbc_i2c_client *bbc_i2c_attach(काष्ठा bbc_i2c_bus *bp, काष्ठा platक्रमm_device *op)
अणु
	काष्ठा bbc_i2c_client *client;
	स्थिर u32 *reg;

	client = kzalloc(माप(*client), GFP_KERNEL);
	अगर (!client)
		वापस शून्य;
	client->bp = bp;
	client->op = op;

	reg = of_get_property(op->dev.of_node, "reg", शून्य);
	अगर (!reg) अणु
		kमुक्त(client);
		वापस शून्य;
	पूर्ण

	client->bus = reg[0];
	client->address = reg[1];

	claim_device(bp, op);

	वापस client;
पूर्ण

व्योम bbc_i2c_detach(काष्ठा bbc_i2c_client *client)
अणु
	काष्ठा bbc_i2c_bus *bp = client->bp;
	काष्ठा platक्रमm_device *op = client->op;

	release_device(bp, op);
	kमुक्त(client);
पूर्ण

अटल पूर्णांक रुको_क्रम_pin(काष्ठा bbc_i2c_bus *bp, u8 *status)
अणु
	DECLARE_WAITQUEUE(रुको, current);
	पूर्णांक limit = 32;
	पूर्णांक ret = 1;

	bp->रुकोing = 1;
	add_रुको_queue(&bp->wq, &रुको);
	जबतक (limit-- > 0) अणु
		दीर्घ val;

		val = रुको_event_पूर्णांकerruptible_समयout(
				bp->wq,
				(((*status = पढ़ोb(bp->i2c_control_regs + 0))
				  & I2C_PCF_PIN) == 0),
				msecs_to_jअगरfies(250));
		अगर (val > 0) अणु
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	हटाओ_रुको_queue(&bp->wq, &रुको);
	bp->रुकोing = 0;

	वापस ret;
पूर्ण

पूर्णांक bbc_i2c_ग_लिखोb(काष्ठा bbc_i2c_client *client, अचिन्हित अक्षर val, पूर्णांक off)
अणु
	काष्ठा bbc_i2c_bus *bp = client->bp;
	पूर्णांक address = client->address;
	u8 status;
	पूर्णांक ret = -1;

	अगर (bp->i2c_bussel_reg != शून्य)
		ग_लिखोb(client->bus, bp->i2c_bussel_reg);

	ग_लिखोb(address, bp->i2c_control_regs + 0x1);
	ग_लिखोb(I2C_PCF_START, bp->i2c_control_regs + 0x0);
	अगर (रुको_क्रम_pin(bp, &status))
		जाओ out;

	ग_लिखोb(off, bp->i2c_control_regs + 0x1);
	अगर (रुको_क्रम_pin(bp, &status) ||
	    (status & I2C_PCF_LRB) != 0)
		जाओ out;

	ग_लिखोb(val, bp->i2c_control_regs + 0x1);
	अगर (रुको_क्रम_pin(bp, &status))
		जाओ out;

	ret = 0;

out:
	ग_लिखोb(I2C_PCF_STOP, bp->i2c_control_regs + 0x0);
	वापस ret;
पूर्ण

पूर्णांक bbc_i2c_पढ़ोb(काष्ठा bbc_i2c_client *client, अचिन्हित अक्षर *byte, पूर्णांक off)
अणु
	काष्ठा bbc_i2c_bus *bp = client->bp;
	अचिन्हित अक्षर address = client->address, status;
	पूर्णांक ret = -1;

	अगर (bp->i2c_bussel_reg != शून्य)
		ग_लिखोb(client->bus, bp->i2c_bussel_reg);

	ग_लिखोb(address, bp->i2c_control_regs + 0x1);
	ग_लिखोb(I2C_PCF_START, bp->i2c_control_regs + 0x0);
	अगर (रुको_क्रम_pin(bp, &status))
		जाओ out;

	ग_लिखोb(off, bp->i2c_control_regs + 0x1);
	अगर (रुको_क्रम_pin(bp, &status) ||
	    (status & I2C_PCF_LRB) != 0)
		जाओ out;

	ग_लिखोb(I2C_PCF_STOP, bp->i2c_control_regs + 0x0);

	address |= 0x1; /* READ */

	ग_लिखोb(address, bp->i2c_control_regs + 0x1);
	ग_लिखोb(I2C_PCF_START, bp->i2c_control_regs + 0x0);
	अगर (रुको_क्रम_pin(bp, &status))
		जाओ out;

	/* Set PIN back to one so the device sends the first
	 * byte.
	 */
	(व्योम) पढ़ोb(bp->i2c_control_regs + 0x1);
	अगर (रुको_क्रम_pin(bp, &status))
		जाओ out;

	ग_लिखोb(I2C_PCF_ESO | I2C_PCF_ENI, bp->i2c_control_regs + 0x0);
	*byte = पढ़ोb(bp->i2c_control_regs + 0x1);
	अगर (रुको_क्रम_pin(bp, &status))
		जाओ out;

	ret = 0;

out:
	ग_लिखोb(I2C_PCF_STOP, bp->i2c_control_regs + 0x0);
	(व्योम) पढ़ोb(bp->i2c_control_regs + 0x1);

	वापस ret;
पूर्ण

पूर्णांक bbc_i2c_ग_लिखो_buf(काष्ठा bbc_i2c_client *client,
		      अक्षर *buf, पूर्णांक len, पूर्णांक off)
अणु
	पूर्णांक ret = 0;

	जबतक (len > 0) अणु
		ret = bbc_i2c_ग_लिखोb(client, *buf, off);
		अगर (ret < 0)
			अवरोध;
		len--;
		buf++;
		off++;
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक bbc_i2c_पढ़ो_buf(काष्ठा bbc_i2c_client *client,
		     अक्षर *buf, पूर्णांक len, पूर्णांक off)
अणु
	पूर्णांक ret = 0;

	जबतक (len > 0) अणु
		ret = bbc_i2c_पढ़ोb(client, buf, off);
		अगर (ret < 0)
			अवरोध;
		len--;
		buf++;
		off++;
	पूर्ण

	वापस ret;
पूर्ण

EXPORT_SYMBOL(bbc_i2c_getdev);
EXPORT_SYMBOL(bbc_i2c_attach);
EXPORT_SYMBOL(bbc_i2c_detach);
EXPORT_SYMBOL(bbc_i2c_ग_लिखोb);
EXPORT_SYMBOL(bbc_i2c_पढ़ोb);
EXPORT_SYMBOL(bbc_i2c_ग_लिखो_buf);
EXPORT_SYMBOL(bbc_i2c_पढ़ो_buf);

अटल irqवापस_t bbc_i2c_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा bbc_i2c_bus *bp = dev_id;

	/* PIN going from set to clear is the only event which
	 * makes the i2c निश्चित an पूर्णांकerrupt.
	 */
	अगर (bp->रुकोing &&
	    !(पढ़ोb(bp->i2c_control_regs + 0x0) & I2C_PCF_PIN))
		wake_up_पूर्णांकerruptible(&bp->wq);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम reset_one_i2c(काष्ठा bbc_i2c_bus *bp)
अणु
	ग_लिखोb(I2C_PCF_PIN, bp->i2c_control_regs + 0x0);
	ग_लिखोb(bp->own, bp->i2c_control_regs + 0x1);
	ग_लिखोb(I2C_PCF_PIN | I2C_PCF_ES1, bp->i2c_control_regs + 0x0);
	ग_लिखोb(bp->घड़ी, bp->i2c_control_regs + 0x1);
	ग_लिखोb(I2C_PCF_IDLE, bp->i2c_control_regs + 0x0);
पूर्ण

अटल काष्ठा bbc_i2c_bus * attach_one_i2c(काष्ठा platक्रमm_device *op, पूर्णांक index)
अणु
	काष्ठा bbc_i2c_bus *bp;
	काष्ठा device_node *dp;
	पूर्णांक entry;

	bp = kzalloc(माप(*bp), GFP_KERNEL);
	अगर (!bp)
		वापस शून्य;

	INIT_LIST_HEAD(&bp->temps);
	INIT_LIST_HEAD(&bp->fans);

	bp->i2c_control_regs = of_ioremap(&op->resource[0], 0, 0x2, "bbc_i2c_regs");
	अगर (!bp->i2c_control_regs)
		जाओ fail;

	अगर (op->num_resources == 2) अणु
		bp->i2c_bussel_reg = of_ioremap(&op->resource[1], 0, 0x1, "bbc_i2c_bussel");
		अगर (!bp->i2c_bussel_reg)
			जाओ fail;
	पूर्ण

	bp->रुकोing = 0;
	init_रुकोqueue_head(&bp->wq);
	अगर (request_irq(op->archdata.irqs[0], bbc_i2c_पूर्णांकerrupt,
			IRQF_SHARED, "bbc_i2c", bp))
		जाओ fail;

	bp->index = index;
	bp->op = op;

	spin_lock_init(&bp->lock);

	entry = 0;
	क्रम (dp = op->dev.of_node->child;
	     dp && entry < 8;
	     dp = dp->sibling, entry++) अणु
		काष्ठा platक्रमm_device *child_op;

		child_op = of_find_device_by_node(dp);
		bp->devs[entry].device = child_op;
		bp->devs[entry].client_claimed = 0;
	पूर्ण

	ग_लिखोb(I2C_PCF_PIN, bp->i2c_control_regs + 0x0);
	bp->own = पढ़ोb(bp->i2c_control_regs + 0x01);
	ग_लिखोb(I2C_PCF_PIN | I2C_PCF_ES1, bp->i2c_control_regs + 0x0);
	bp->घड़ी = पढ़ोb(bp->i2c_control_regs + 0x01);

	prपूर्णांकk(KERN_INFO "i2c-%d: Regs at %p, %d devices, own %02x, clock %02x.\n",
	       bp->index, bp->i2c_control_regs, entry, bp->own, bp->घड़ी);

	reset_one_i2c(bp);

	वापस bp;

fail:
	अगर (bp->i2c_bussel_reg)
		of_iounmap(&op->resource[1], bp->i2c_bussel_reg, 1);
	अगर (bp->i2c_control_regs)
		of_iounmap(&op->resource[0], bp->i2c_control_regs, 2);
	kमुक्त(bp);
	वापस शून्य;
पूर्ण

बाह्य पूर्णांक bbc_envctrl_init(काष्ठा bbc_i2c_bus *bp);
बाह्य व्योम bbc_envctrl_cleanup(काष्ठा bbc_i2c_bus *bp);

अटल पूर्णांक bbc_i2c_probe(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा bbc_i2c_bus *bp;
	पूर्णांक err, index = 0;

	bp = attach_one_i2c(op, index);
	अगर (!bp)
		वापस -EINVAL;

	err = bbc_envctrl_init(bp);
	अगर (err) अणु
		मुक्त_irq(op->archdata.irqs[0], bp);
		अगर (bp->i2c_bussel_reg)
			of_iounmap(&op->resource[0], bp->i2c_bussel_reg, 1);
		अगर (bp->i2c_control_regs)
			of_iounmap(&op->resource[1], bp->i2c_control_regs, 2);
		kमुक्त(bp);
	पूर्ण अन्यथा अणु
		dev_set_drvdata(&op->dev, bp);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक bbc_i2c_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा bbc_i2c_bus *bp = dev_get_drvdata(&op->dev);

	bbc_envctrl_cleanup(bp);

	मुक्त_irq(op->archdata.irqs[0], bp);

	अगर (bp->i2c_bussel_reg)
		of_iounmap(&op->resource[0], bp->i2c_bussel_reg, 1);
	अगर (bp->i2c_control_regs)
		of_iounmap(&op->resource[1], bp->i2c_control_regs, 2);

	kमुक्त(bp);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id bbc_i2c_match[] = अणु
	अणु
		.name = "i2c",
		.compatible = "SUNW,bbc-i2c",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, bbc_i2c_match);

अटल काष्ठा platक्रमm_driver bbc_i2c_driver = अणु
	.driver = अणु
		.name = "bbc_i2c",
		.of_match_table = bbc_i2c_match,
	पूर्ण,
	.probe		= bbc_i2c_probe,
	.हटाओ		= bbc_i2c_हटाओ,
पूर्ण;

module_platक्रमm_driver(bbc_i2c_driver);

MODULE_LICENSE("GPL");
