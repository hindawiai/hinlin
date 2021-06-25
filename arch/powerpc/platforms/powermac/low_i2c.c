<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * arch/घातerpc/platक्रमms/घातermac/low_i2c.c
 *
 *  Copyright (C) 2003-2005 Ben. Herrenschmidt (benh@kernel.crashing.org)
 *
 * The linux i2c layer isn't completely suitable क्रम our needs क्रम various
 * reasons ranging from too late initialisation to semantics not perfectly
 * matching some requirements of the apple platक्रमm functions etc...
 *
 * This file thus provides a simple low level unअगरied i2c पूर्णांकerface क्रम
 * घातermac that covers the various types of i2c busses used in Apple machines.
 * For now, keywest, PMU and SMU, though we could add Cuda, or other bit
 * banging busses found on older chipsets in earlier machines अगर we ever need
 * one of them.
 *
 * The drivers in this file are synchronous/blocking. In addition, the
 * keywest one is fairly slow due to the use of msleep instead of पूर्णांकerrupts
 * as the पूर्णांकerrupt is currently used by i2c-keywest. In the दीर्घ run, we
 * might want to get rid of those high-level पूर्णांकerfaces to linux i2c layer
 * either completely (converting all drivers) or replacing them all with a
 * single stub driver on top of this one. Once करोne, the पूर्णांकerrupt will be
 * available क्रम our use.
 */

#अघोषित DEBUG
#अघोषित DEBUG_LOW

#समावेश <linux/types.h>
#समावेश <linux/sched.h>
#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/adb.h>
#समावेश <linux/pmu.h>
#समावेश <linux/delay.h>
#समावेश <linux/completion.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/समयr.h>
#समावेश <linux/mutex.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/keylargo.h>
#समावेश <यंत्र/uninorth.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/smu.h>
#समावेश <यंत्र/pmac_pfunc.h>
#समावेश <यंत्र/pmac_low_i2c.h>

#अगर_घोषित DEBUG
#घोषणा DBG(x...) करो अणु\
		prपूर्णांकk(KERN_DEBUG "low_i2c:" x);	\
	पूर्ण जबतक(0)
#अन्यथा
#घोषणा DBG(x...)
#पूर्ण_अगर

#अगर_घोषित DEBUG_LOW
#घोषणा DBG_LOW(x...) करो अणु\
		prपूर्णांकk(KERN_DEBUG "low_i2c:" x);	\
	पूर्ण जबतक(0)
#अन्यथा
#घोषणा DBG_LOW(x...)
#पूर्ण_अगर


अटल पूर्णांक pmac_i2c_क्रमce_poll = 1;

/*
 * A bus काष्ठाure. Each bus in the प्रणाली has such a काष्ठाure associated.
 */
काष्ठा pmac_i2c_bus
अणु
	काष्ठा list_head	link;
	काष्ठा device_node	*controller;
	काष्ठा device_node	*busnode;
	पूर्णांक			type;
	पूर्णांक			flags;
	काष्ठा i2c_adapter	adapter;
	व्योम			*hostdata;
	पूर्णांक			channel;	/* some hosts have multiple */
	पूर्णांक			mode;		/* current mode */
	काष्ठा mutex		mutex;
	पूर्णांक			खोलोed;
	पूर्णांक			polled;		/* खोलो mode */
	काष्ठा platक्रमm_device	*platक्रमm_dev;
	काष्ठा lock_class_key   lock_key;

	/* ops */
	पूर्णांक (*खोलो)(काष्ठा pmac_i2c_bus *bus);
	व्योम (*बंद)(काष्ठा pmac_i2c_bus *bus);
	पूर्णांक (*xfer)(काष्ठा pmac_i2c_bus *bus, u8 addrdir, पूर्णांक subsize,
		    u32 subaddr, u8 *data, पूर्णांक len);
पूर्ण;

अटल LIST_HEAD(pmac_i2c_busses);

/*
 * Keywest implementation
 */

काष्ठा pmac_i2c_host_kw
अणु
	काष्ठा mutex		mutex;		/* Access mutex क्रम use by
						 * i2c-keywest */
	व्योम __iomem		*base;		/* रेजिस्टर base address */
	पूर्णांक			bsteps;		/* रेजिस्टर stepping */
	पूर्णांक			speed;		/* speed */
	पूर्णांक			irq;
	u8			*data;
	अचिन्हित		len;
	पूर्णांक			state;
	पूर्णांक			rw;
	पूर्णांक			polled;
	पूर्णांक			result;
	काष्ठा completion	complete;
	spinlock_t		lock;
	काष्ठा समयr_list	समयout_समयr;
पूर्ण;

/* Register indices */
प्रकार क्रमागत अणु
	reg_mode = 0,
	reg_control,
	reg_status,
	reg_isr,
	reg_ier,
	reg_addr,
	reg_subaddr,
	reg_data
पूर्ण reg_t;

/* The Tumbler audio equalizer can be really slow someबार */
#घोषणा KW_POLL_TIMEOUT		(2*HZ)

/* Mode रेजिस्टर */
#घोषणा KW_I2C_MODE_100KHZ	0x00
#घोषणा KW_I2C_MODE_50KHZ	0x01
#घोषणा KW_I2C_MODE_25KHZ	0x02
#घोषणा KW_I2C_MODE_DUMB	0x00
#घोषणा KW_I2C_MODE_STANDARD	0x04
#घोषणा KW_I2C_MODE_STANDARDSUB	0x08
#घोषणा KW_I2C_MODE_COMBINED	0x0C
#घोषणा KW_I2C_MODE_MODE_MASK	0x0C
#घोषणा KW_I2C_MODE_CHAN_MASK	0xF0

/* Control रेजिस्टर */
#घोषणा KW_I2C_CTL_AAK		0x01
#घोषणा KW_I2C_CTL_XADDR	0x02
#घोषणा KW_I2C_CTL_STOP		0x04
#घोषणा KW_I2C_CTL_START	0x08

/* Status रेजिस्टर */
#घोषणा KW_I2C_STAT_BUSY	0x01
#घोषणा KW_I2C_STAT_LAST_AAK	0x02
#घोषणा KW_I2C_STAT_LAST_RW	0x04
#घोषणा KW_I2C_STAT_SDA		0x08
#घोषणा KW_I2C_STAT_SCL		0x10

/* IER & ISR रेजिस्टरs */
#घोषणा KW_I2C_IRQ_DATA		0x01
#घोषणा KW_I2C_IRQ_ADDR		0x02
#घोषणा KW_I2C_IRQ_STOP		0x04
#घोषणा KW_I2C_IRQ_START	0x08
#घोषणा KW_I2C_IRQ_MASK		0x0F

/* State machine states */
क्रमागत अणु
	state_idle,
	state_addr,
	state_पढ़ो,
	state_ग_लिखो,
	state_stop,
	state_dead
पूर्ण;

#घोषणा WRONG_STATE(name) करो अणु\
		prपूर्णांकk(KERN_DEBUG "KW: wrong state. Got %s, state: %s " \
		       "(isr: %02x)\n",	\
		       name, __kw_state_names[host->state], isr); \
	पूर्ण जबतक(0)

अटल स्थिर अक्षर *__kw_state_names[] = अणु
	"state_idle",
	"state_addr",
	"state_read",
	"state_write",
	"state_stop",
	"state_dead"
पूर्ण;

अटल अंतरभूत u8 __kw_पढ़ो_reg(काष्ठा pmac_i2c_host_kw *host, reg_t reg)
अणु
	वापस पढ़ोb(host->base + (((अचिन्हित पूर्णांक)reg) << host->bsteps));
पूर्ण

अटल अंतरभूत व्योम __kw_ग_लिखो_reg(काष्ठा pmac_i2c_host_kw *host,
				  reg_t reg, u8 val)
अणु
	ग_लिखोb(val, host->base + (((अचिन्हित)reg) << host->bsteps));
	(व्योम)__kw_पढ़ो_reg(host, reg_subaddr);
पूर्ण

#घोषणा kw_ग_लिखो_reg(reg, val)	__kw_ग_लिखो_reg(host, reg, val)
#घोषणा kw_पढ़ो_reg(reg)	__kw_पढ़ो_reg(host, reg)

अटल u8 kw_i2c_रुको_पूर्णांकerrupt(काष्ठा pmac_i2c_host_kw *host)
अणु
	पूर्णांक i, j;
	u8 isr;
	
	क्रम (i = 0; i < 1000; i++) अणु
		isr = kw_पढ़ो_reg(reg_isr) & KW_I2C_IRQ_MASK;
		अगर (isr != 0)
			वापस isr;

		/* This code is used with the समयbase frozen, we cannot rely
		 * on udelay nor schedule when in polled mode !
		 * For now, just use a bogus loop....
		 */
		अगर (host->polled) अणु
			क्रम (j = 1; j < 100000; j++)
				mb();
		पूर्ण अन्यथा
			msleep(1);
	पूर्ण
	वापस isr;
पूर्ण

अटल व्योम kw_i2c_करो_stop(काष्ठा pmac_i2c_host_kw *host, पूर्णांक result)
अणु
	kw_ग_लिखो_reg(reg_control, KW_I2C_CTL_STOP);
	host->state = state_stop;
	host->result = result;
पूर्ण


अटल व्योम kw_i2c_handle_पूर्णांकerrupt(काष्ठा pmac_i2c_host_kw *host, u8 isr)
अणु
	u8 ack;

	DBG_LOW("kw_handle_interrupt(%s, isr: %x)\n",
		__kw_state_names[host->state], isr);

	अगर (host->state == state_idle) अणु
		prपूर्णांकk(KERN_WARNING "low_i2c: Keywest got an out of state"
		       " interrupt, ignoring\n");
		kw_ग_लिखो_reg(reg_isr, isr);
		वापस;
	पूर्ण

	अगर (isr == 0) अणु
		prपूर्णांकk(KERN_WARNING "low_i2c: Timeout in i2c transfer"
		       " on keywest !\n");
		अगर (host->state != state_stop) अणु
			kw_i2c_करो_stop(host, -EIO);
			वापस;
		पूर्ण
		ack = kw_पढ़ो_reg(reg_status);
		अगर (ack & KW_I2C_STAT_BUSY)
			kw_ग_लिखो_reg(reg_status, 0);
		host->state = state_idle;
		kw_ग_लिखो_reg(reg_ier, 0x00);
		अगर (!host->polled)
			complete(&host->complete);
		वापस;
	पूर्ण

	अगर (isr & KW_I2C_IRQ_ADDR) अणु
		ack = kw_पढ़ो_reg(reg_status);
		अगर (host->state != state_addr) अणु
			WRONG_STATE("KW_I2C_IRQ_ADDR"); 
			kw_i2c_करो_stop(host, -EIO);
		पूर्ण
		अगर ((ack & KW_I2C_STAT_LAST_AAK) == 0) अणु
			host->result = -ENXIO;
			host->state = state_stop;
			DBG_LOW("KW: NAK on address\n");
		पूर्ण अन्यथा अणु
			अगर (host->len == 0)
				kw_i2c_करो_stop(host, 0);
			अन्यथा अगर (host->rw) अणु
				host->state = state_पढ़ो;
				अगर (host->len > 1)
					kw_ग_लिखो_reg(reg_control,
						     KW_I2C_CTL_AAK);
			पूर्ण अन्यथा अणु
				host->state = state_ग_लिखो;
				kw_ग_लिखो_reg(reg_data, *(host->data++));
				host->len--;
			पूर्ण
		पूर्ण
		kw_ग_लिखो_reg(reg_isr, KW_I2C_IRQ_ADDR);
	पूर्ण

	अगर (isr & KW_I2C_IRQ_DATA) अणु
		अगर (host->state == state_पढ़ो) अणु
			*(host->data++) = kw_पढ़ो_reg(reg_data);
			host->len--;
			kw_ग_लिखो_reg(reg_isr, KW_I2C_IRQ_DATA);
			अगर (host->len == 0)
				host->state = state_stop;
			अन्यथा अगर (host->len == 1)
				kw_ग_लिखो_reg(reg_control, 0);
		पूर्ण अन्यथा अगर (host->state == state_ग_लिखो) अणु
			ack = kw_पढ़ो_reg(reg_status);
			अगर ((ack & KW_I2C_STAT_LAST_AAK) == 0) अणु
				DBG_LOW("KW: nack on data write\n");
				host->result = -EFBIG;
				host->state = state_stop;
			पूर्ण अन्यथा अगर (host->len) अणु
				kw_ग_लिखो_reg(reg_data, *(host->data++));
				host->len--;
			पूर्ण अन्यथा
				kw_i2c_करो_stop(host, 0);
		पूर्ण अन्यथा अणु
			WRONG_STATE("KW_I2C_IRQ_DATA"); 
			अगर (host->state != state_stop)
				kw_i2c_करो_stop(host, -EIO);
		पूर्ण
		kw_ग_लिखो_reg(reg_isr, KW_I2C_IRQ_DATA);
	पूर्ण

	अगर (isr & KW_I2C_IRQ_STOP) अणु
		kw_ग_लिखो_reg(reg_isr, KW_I2C_IRQ_STOP);
		अगर (host->state != state_stop) अणु
			WRONG_STATE("KW_I2C_IRQ_STOP");
			host->result = -EIO;
		पूर्ण
		host->state = state_idle;
		अगर (!host->polled)
			complete(&host->complete);
	पूर्ण

	/* Below should only happen in manual mode which we करोn't use ... */
	अगर (isr & KW_I2C_IRQ_START)
		kw_ग_लिखो_reg(reg_isr, KW_I2C_IRQ_START);

पूर्ण

/* Interrupt handler */
अटल irqवापस_t kw_i2c_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा pmac_i2c_host_kw *host = dev_id;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&host->lock, flags);
	del_समयr(&host->समयout_समयr);
	kw_i2c_handle_पूर्णांकerrupt(host, kw_पढ़ो_reg(reg_isr));
	अगर (host->state != state_idle) अणु
		host->समयout_समयr.expires = jअगरfies + KW_POLL_TIMEOUT;
		add_समयr(&host->समयout_समयr);
	पूर्ण
	spin_unlock_irqrestore(&host->lock, flags);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम kw_i2c_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा pmac_i2c_host_kw *host = from_समयr(host, t, समयout_समयr);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&host->lock, flags);

	/*
	 * If the समयr is pending, that means we raced with the
	 * irq, in which हाल we just वापस
	 */
	अगर (समयr_pending(&host->समयout_समयr))
		जाओ skip;

	kw_i2c_handle_पूर्णांकerrupt(host, kw_पढ़ो_reg(reg_isr));
	अगर (host->state != state_idle) अणु
		host->समयout_समयr.expires = jअगरfies + KW_POLL_TIMEOUT;
		add_समयr(&host->समयout_समयr);
	पूर्ण
 skip:
	spin_unlock_irqrestore(&host->lock, flags);
पूर्ण

अटल पूर्णांक kw_i2c_खोलो(काष्ठा pmac_i2c_bus *bus)
अणु
	काष्ठा pmac_i2c_host_kw *host = bus->hostdata;
	mutex_lock(&host->mutex);
	वापस 0;
पूर्ण

अटल व्योम kw_i2c_बंद(काष्ठा pmac_i2c_bus *bus)
अणु
	काष्ठा pmac_i2c_host_kw *host = bus->hostdata;
	mutex_unlock(&host->mutex);
पूर्ण

अटल पूर्णांक kw_i2c_xfer(काष्ठा pmac_i2c_bus *bus, u8 addrdir, पूर्णांक subsize,
		       u32 subaddr, u8 *data, पूर्णांक len)
अणु
	काष्ठा pmac_i2c_host_kw *host = bus->hostdata;
	u8 mode_reg = host->speed;
	पूर्णांक use_irq = host->irq && !bus->polled;

	/* Setup mode & subaddress अगर any */
	चयन(bus->mode) अणु
	हाल pmac_i2c_mode_dumb:
		वापस -EINVAL;
	हाल pmac_i2c_mode_std:
		mode_reg |= KW_I2C_MODE_STANDARD;
		अगर (subsize != 0)
			वापस -EINVAL;
		अवरोध;
	हाल pmac_i2c_mode_stdsub:
		mode_reg |= KW_I2C_MODE_STANDARDSUB;
		अगर (subsize != 1)
			वापस -EINVAL;
		अवरोध;
	हाल pmac_i2c_mode_combined:
		mode_reg |= KW_I2C_MODE_COMBINED;
		अगर (subsize != 1)
			वापस -EINVAL;
		अवरोध;
	पूर्ण

	/* Setup channel & clear pending irqs */
	kw_ग_लिखो_reg(reg_isr, kw_पढ़ो_reg(reg_isr));
	kw_ग_लिखो_reg(reg_mode, mode_reg | (bus->channel << 4));
	kw_ग_लिखो_reg(reg_status, 0);

	/* Set up address and r/w bit, strip possible stale bus number from
	 * address top bits
	 */
	kw_ग_लिखो_reg(reg_addr, addrdir & 0xff);

	/* Set up the sub address */
	अगर ((mode_reg & KW_I2C_MODE_MODE_MASK) == KW_I2C_MODE_STANDARDSUB
	    || (mode_reg & KW_I2C_MODE_MODE_MASK) == KW_I2C_MODE_COMBINED)
		kw_ग_लिखो_reg(reg_subaddr, subaddr);

	/* Prepare क्रम async operations */
	host->data = data;
	host->len = len;
	host->state = state_addr;
	host->result = 0;
	host->rw = (addrdir & 1);
	host->polled = bus->polled;

	/* Enable पूर्णांकerrupt अगर not using polled mode and पूर्णांकerrupt is
	 * available
	 */
	अगर (use_irq) अणु
		/* Clear completion */
		reinit_completion(&host->complete);
		/* Ack stale पूर्णांकerrupts */
		kw_ग_लिखो_reg(reg_isr, kw_पढ़ो_reg(reg_isr));
		/* Arm समयout */
		host->समयout_समयr.expires = jअगरfies + KW_POLL_TIMEOUT;
		add_समयr(&host->समयout_समयr);
		/* Enable emission */
		kw_ग_लिखो_reg(reg_ier, KW_I2C_IRQ_MASK);
	पूर्ण

	/* Start sending address */
	kw_ग_लिखो_reg(reg_control, KW_I2C_CTL_XADDR);

	/* Wait क्रम completion */
	अगर (use_irq)
		रुको_क्रम_completion(&host->complete);
	अन्यथा अणु
		जबतक(host->state != state_idle) अणु
			अचिन्हित दीर्घ flags;

			u8 isr = kw_i2c_रुको_पूर्णांकerrupt(host);
			spin_lock_irqsave(&host->lock, flags);
			kw_i2c_handle_पूर्णांकerrupt(host, isr);
			spin_unlock_irqrestore(&host->lock, flags);
		पूर्ण
	पूर्ण

	/* Disable emission */
	kw_ग_लिखो_reg(reg_ier, 0);

	वापस host->result;
पूर्ण

अटल काष्ठा pmac_i2c_host_kw *__init kw_i2c_host_init(काष्ठा device_node *np)
अणु
	काष्ठा pmac_i2c_host_kw *host;
	स्थिर u32		*psteps, *prate, *addrp;
	u32			steps;

	host = kzalloc(माप(*host), GFP_KERNEL);
	अगर (host == शून्य) अणु
		prपूर्णांकk(KERN_ERR "low_i2c: Can't allocate host for %pOF\n",
		       np);
		वापस शून्य;
	पूर्ण

	/* Apple is kind enough to provide a valid AAPL,address property
	 * on all i2c keywest nodes so far ... we would have to fallback
	 * to macio parsing अगर that wasn't the हाल
	 */
	addrp = of_get_property(np, "AAPL,address", शून्य);
	अगर (addrp == शून्य) अणु
		prपूर्णांकk(KERN_ERR "low_i2c: Can't find address for %pOF\n",
		       np);
		kमुक्त(host);
		वापस शून्य;
	पूर्ण
	mutex_init(&host->mutex);
	init_completion(&host->complete);
	spin_lock_init(&host->lock);
	समयr_setup(&host->समयout_समयr, kw_i2c_समयout, 0);

	psteps = of_get_property(np, "AAPL,address-step", शून्य);
	steps = psteps ? (*psteps) : 0x10;
	क्रम (host->bsteps = 0; (steps & 0x01) == 0; host->bsteps++)
		steps >>= 1;
	/* Select पूर्णांकerface rate */
	host->speed = KW_I2C_MODE_25KHZ;
	prate = of_get_property(np, "AAPL,i2c-rate", शून्य);
	अगर (prate) चयन(*prate) अणु
	हाल 100:
		host->speed = KW_I2C_MODE_100KHZ;
		अवरोध;
	हाल 50:
		host->speed = KW_I2C_MODE_50KHZ;
		अवरोध;
	हाल 25:
		host->speed = KW_I2C_MODE_25KHZ;
		अवरोध;
	पूर्ण	
	host->irq = irq_of_parse_and_map(np, 0);
	अगर (!host->irq)
		prपूर्णांकk(KERN_WARNING
		       "low_i2c: Failed to map interrupt for %pOF\n",
		       np);

	host->base = ioremap((*addrp), 0x1000);
	अगर (host->base == शून्य) अणु
		prपूर्णांकk(KERN_ERR "low_i2c: Can't map registers for %pOF\n",
		       np);
		kमुक्त(host);
		वापस शून्य;
	पूर्ण

	/* Make sure IRQ is disabled */
	kw_ग_लिखो_reg(reg_ier, 0);

	/* Request chip पूर्णांकerrupt. We set IRQF_NO_SUSPEND because we करोn't
	 * want that पूर्णांकerrupt disabled between the 2 passes of driver
	 * suspend or we'll have issues running the pfuncs
	 */
	अगर (request_irq(host->irq, kw_i2c_irq, IRQF_NO_SUSPEND,
			"keywest i2c", host))
		host->irq = 0;

	prपूर्णांकk(KERN_INFO "KeyWest i2c @0x%08x irq %d %pOF\n",
	       *addrp, host->irq, np);

	वापस host;
पूर्ण


अटल व्योम __init kw_i2c_add(काष्ठा pmac_i2c_host_kw *host,
			      काष्ठा device_node *controller,
			      काष्ठा device_node *busnode,
			      पूर्णांक channel)
अणु
	काष्ठा pmac_i2c_bus *bus;

	bus = kzalloc(माप(काष्ठा pmac_i2c_bus), GFP_KERNEL);
	अगर (bus == शून्य)
		वापस;

	bus->controller = of_node_get(controller);
	bus->busnode = of_node_get(busnode);
	bus->type = pmac_i2c_bus_keywest;
	bus->hostdata = host;
	bus->channel = channel;
	bus->mode = pmac_i2c_mode_std;
	bus->खोलो = kw_i2c_खोलो;
	bus->बंद = kw_i2c_बंद;
	bus->xfer = kw_i2c_xfer;
	mutex_init(&bus->mutex);
	lockdep_set_class(&bus->mutex, &bus->lock_key);
	अगर (controller == busnode)
		bus->flags = pmac_i2c_multibus;
	list_add(&bus->link, &pmac_i2c_busses);

	prपूर्णांकk(KERN_INFO " channel %d bus %s\n", channel,
	       (controller == busnode) ? "<multibus>" : busnode->full_name);
पूर्ण

अटल व्योम __init kw_i2c_probe(व्योम)
अणु
	काष्ठा device_node *np, *child, *parent;

	/* Probe keywest-i2c busses */
	क्रम_each_compatible_node(np, "i2c","keywest-i2c") अणु
		काष्ठा pmac_i2c_host_kw *host;
		पूर्णांक multibus;

		/* Found one, init a host काष्ठाure */
		host = kw_i2c_host_init(np);
		अगर (host == शून्य)
			जारी;

		/* Now check अगर we have a multibus setup (old style) or अगर we
		 * have proper bus nodes. Note that the "new" way (proper bus
		 * nodes) might cause us to not create some busses that are
		 * kept hidden in the device-tree. In the future, we might
		 * want to work around that by creating busses without a node
		 * but not क्रम now
		 */
		child = of_get_next_child(np, शून्य);
		multibus = !of_node_name_eq(child, "i2c-bus");
		of_node_put(child);

		/* For a multibus setup, we get the bus count based on the
		 * parent type
		 */
		अगर (multibus) अणु
			पूर्णांक chans, i;

			parent = of_get_parent(np);
			अगर (parent == शून्य)
				जारी;
			chans = parent->name[0] == 'u' ? 2 : 1;
			क्रम (i = 0; i < chans; i++)
				kw_i2c_add(host, np, np, i);
		पूर्ण अन्यथा अणु
			क्रम_each_child_of_node(np, child) अणु
				स्थिर u32 *reg = of_get_property(child,
						"reg", शून्य);
				अगर (reg == शून्य)
					जारी;
				kw_i2c_add(host, np, child, *reg);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण


/*
 *
 * PMU implementation
 *
 */

#अगर_घोषित CONFIG_ADB_PMU

/*
 * i2c command block to the PMU
 */
काष्ठा pmu_i2c_hdr अणु
	u8	bus;
	u8	mode;
	u8	bus2;
	u8	address;
	u8	sub_addr;
	u8	comb_addr;
	u8	count;
	u8	data[];
पूर्ण;

अटल व्योम pmu_i2c_complete(काष्ठा adb_request *req)
अणु
	complete(req->arg);
पूर्ण

अटल पूर्णांक pmu_i2c_xfer(काष्ठा pmac_i2c_bus *bus, u8 addrdir, पूर्णांक subsize,
			u32 subaddr, u8 *data, पूर्णांक len)
अणु
	काष्ठा adb_request *req = bus->hostdata;
	काष्ठा pmu_i2c_hdr *hdr = (काष्ठा pmu_i2c_hdr *)&req->data[1];
	काष्ठा completion comp;
	पूर्णांक पढ़ो = addrdir & 1;
	पूर्णांक retry;
	पूर्णांक rc = 0;

	/* For now, limit ourselves to 16 bytes transfers */
	अगर (len > 16)
		वापस -EINVAL;

	init_completion(&comp);

	क्रम (retry = 0; retry < 16; retry++) अणु
		स_रखो(req, 0, माप(काष्ठा adb_request));
		hdr->bus = bus->channel;
		hdr->count = len;

		चयन(bus->mode) अणु
		हाल pmac_i2c_mode_std:
			अगर (subsize != 0)
				वापस -EINVAL;
			hdr->address = addrdir;
			hdr->mode = PMU_I2C_MODE_SIMPLE;
			अवरोध;
		हाल pmac_i2c_mode_stdsub:
		हाल pmac_i2c_mode_combined:
			अगर (subsize != 1)
				वापस -EINVAL;
			hdr->address = addrdir & 0xfe;
			hdr->comb_addr = addrdir;
			hdr->sub_addr = subaddr;
			अगर (bus->mode == pmac_i2c_mode_stdsub)
				hdr->mode = PMU_I2C_MODE_STDSUB;
			अन्यथा
				hdr->mode = PMU_I2C_MODE_COMBINED;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		reinit_completion(&comp);
		req->data[0] = PMU_I2C_CMD;
		req->reply[0] = 0xff;
		req->nbytes = माप(काष्ठा pmu_i2c_hdr) + 1;
		req->करोne = pmu_i2c_complete;
		req->arg = &comp;
		अगर (!पढ़ो && len) अणु
			स_नकल(hdr->data, data, len);
			req->nbytes += len;
		पूर्ण
		rc = pmu_queue_request(req);
		अगर (rc)
			वापस rc;
		रुको_क्रम_completion(&comp);
		अगर (req->reply[0] == PMU_I2C_STATUS_OK)
			अवरोध;
		msleep(15);
	पूर्ण
	अगर (req->reply[0] != PMU_I2C_STATUS_OK)
		वापस -EIO;

	क्रम (retry = 0; retry < 16; retry++) अणु
		स_रखो(req, 0, माप(काष्ठा adb_request));

		/* I know that looks like a lot, slow as hell, but darwin
		 * करोes it so let's be on the safe side क्रम now
		 */
		msleep(15);

		hdr->bus = PMU_I2C_BUS_STATUS;

		reinit_completion(&comp);
		req->data[0] = PMU_I2C_CMD;
		req->reply[0] = 0xff;
		req->nbytes = 2;
		req->करोne = pmu_i2c_complete;
		req->arg = &comp;
		rc = pmu_queue_request(req);
		अगर (rc)
			वापस rc;
		रुको_क्रम_completion(&comp);

		अगर (req->reply[0] == PMU_I2C_STATUS_OK && !पढ़ो)
			वापस 0;
		अगर (req->reply[0] == PMU_I2C_STATUS_DATAREAD && पढ़ो) अणु
			पूर्णांक rlen = req->reply_len - 1;

			अगर (rlen != len) अणु
				prपूर्णांकk(KERN_WARNING "low_i2c: PMU returned %d"
				       " bytes, expected %d !\n", rlen, len);
				वापस -EIO;
			पूर्ण
			अगर (len)
				स_नकल(data, &req->reply[1], len);
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -EIO;
पूर्ण

अटल व्योम __init pmu_i2c_probe(व्योम)
अणु
	काष्ठा pmac_i2c_bus *bus;
	काष्ठा device_node *busnode;
	पूर्णांक channel, sz;

	अगर (!pmu_present())
		वापस;

	/* There might or might not be a "pmu-i2c" node, we use that
	 * or via-pmu itself, whatever we find. I haven't seen a machine
	 * with separate bus nodes, so we assume a multibus setup
	 */
	busnode = of_find_node_by_name(शून्य, "pmu-i2c");
	अगर (busnode == शून्य)
		busnode = of_find_node_by_name(शून्य, "via-pmu");
	अगर (busnode == शून्य)
		वापस;

	prपूर्णांकk(KERN_INFO "PMU i2c %pOF\n", busnode);

	/*
	 * We add bus 1 and 2 only क्रम now, bus 0 is "special"
	 */
	क्रम (channel = 1; channel <= 2; channel++) अणु
		sz = माप(काष्ठा pmac_i2c_bus) + माप(काष्ठा adb_request);
		bus = kzalloc(sz, GFP_KERNEL);
		अगर (bus == शून्य)
			वापस;

		bus->controller = busnode;
		bus->busnode = busnode;
		bus->type = pmac_i2c_bus_pmu;
		bus->channel = channel;
		bus->mode = pmac_i2c_mode_std;
		bus->hostdata = bus + 1;
		bus->xfer = pmu_i2c_xfer;
		mutex_init(&bus->mutex);
		lockdep_set_class(&bus->mutex, &bus->lock_key);
		bus->flags = pmac_i2c_multibus;
		list_add(&bus->link, &pmac_i2c_busses);

		prपूर्णांकk(KERN_INFO " channel %d bus <multibus>\n", channel);
	पूर्ण
पूर्ण

#पूर्ण_अगर /* CONFIG_ADB_PMU */


/*
 *
 * SMU implementation
 *
 */

#अगर_घोषित CONFIG_PMAC_SMU

अटल व्योम smu_i2c_complete(काष्ठा smu_i2c_cmd *cmd, व्योम *misc)
अणु
	complete(misc);
पूर्ण

अटल पूर्णांक smu_i2c_xfer(काष्ठा pmac_i2c_bus *bus, u8 addrdir, पूर्णांक subsize,
			u32 subaddr, u8 *data, पूर्णांक len)
अणु
	काष्ठा smu_i2c_cmd *cmd = bus->hostdata;
	काष्ठा completion comp;
	पूर्णांक पढ़ो = addrdir & 1;
	पूर्णांक rc = 0;

	अगर ((पढ़ो && len > SMU_I2C_READ_MAX) ||
	    ((!पढ़ो) && len > SMU_I2C_WRITE_MAX))
		वापस -EINVAL;

	स_रखो(cmd, 0, माप(काष्ठा smu_i2c_cmd));
	cmd->info.bus = bus->channel;
	cmd->info.devaddr = addrdir;
	cmd->info.datalen = len;

	चयन(bus->mode) अणु
	हाल pmac_i2c_mode_std:
		अगर (subsize != 0)
			वापस -EINVAL;
		cmd->info.type = SMU_I2C_TRANSFER_SIMPLE;
		अवरोध;
	हाल pmac_i2c_mode_stdsub:
	हाल pmac_i2c_mode_combined:
		अगर (subsize > 3 || subsize < 1)
			वापस -EINVAL;
		cmd->info.sublen = subsize;
		/* that's big-endian only but heh ! */
		स_नकल(&cmd->info.subaddr, ((अक्षर *)&subaddr) + (4 - subsize),
		       subsize);
		अगर (bus->mode == pmac_i2c_mode_stdsub)
			cmd->info.type = SMU_I2C_TRANSFER_STDSUB;
		अन्यथा
			cmd->info.type = SMU_I2C_TRANSFER_COMBINED;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	अगर (!पढ़ो && len)
		स_नकल(cmd->info.data, data, len);

	init_completion(&comp);
	cmd->करोne = smu_i2c_complete;
	cmd->misc = &comp;
	rc = smu_queue_i2c(cmd);
	अगर (rc < 0)
		वापस rc;
	रुको_क्रम_completion(&comp);
	rc = cmd->status;

	अगर (पढ़ो && len)
		स_नकल(data, cmd->info.data, len);
	वापस rc < 0 ? rc : 0;
पूर्ण

अटल व्योम __init smu_i2c_probe(व्योम)
अणु
	काष्ठा device_node *controller, *busnode;
	काष्ठा pmac_i2c_bus *bus;
	स्थिर u32 *reg;
	पूर्णांक sz;

	अगर (!smu_present())
		वापस;

	controller = of_find_node_by_name(शून्य, "smu-i2c-control");
	अगर (controller == शून्य)
		controller = of_find_node_by_name(शून्य, "smu");
	अगर (controller == शून्य)
		वापस;

	prपूर्णांकk(KERN_INFO "SMU i2c %pOF\n", controller);

	/* Look क्रम childs, note that they might not be of the right
	 * type as older device trees mix i2c busses and other things
	 * at the same level
	 */
	क्रम_each_child_of_node(controller, busnode) अणु
		अगर (!of_node_is_type(busnode, "i2c") &&
		    !of_node_is_type(busnode, "i2c-bus"))
			जारी;
		reg = of_get_property(busnode, "reg", शून्य);
		अगर (reg == शून्य)
			जारी;

		sz = माप(काष्ठा pmac_i2c_bus) + माप(काष्ठा smu_i2c_cmd);
		bus = kzalloc(sz, GFP_KERNEL);
		अगर (bus == शून्य)
			वापस;

		bus->controller = controller;
		bus->busnode = of_node_get(busnode);
		bus->type = pmac_i2c_bus_smu;
		bus->channel = *reg;
		bus->mode = pmac_i2c_mode_std;
		bus->hostdata = bus + 1;
		bus->xfer = smu_i2c_xfer;
		mutex_init(&bus->mutex);
		lockdep_set_class(&bus->mutex, &bus->lock_key);
		bus->flags = 0;
		list_add(&bus->link, &pmac_i2c_busses);

		prपूर्णांकk(KERN_INFO " channel %x bus %pOF\n",
		       bus->channel, busnode);
	पूर्ण
पूर्ण

#पूर्ण_अगर /* CONFIG_PMAC_SMU */

/*
 *
 * Core code
 *
 */


काष्ठा pmac_i2c_bus *pmac_i2c_find_bus(काष्ठा device_node *node)
अणु
	काष्ठा device_node *p = of_node_get(node);
	काष्ठा device_node *prev = शून्य;
	काष्ठा pmac_i2c_bus *bus;

	जबतक(p) अणु
		list_क्रम_each_entry(bus, &pmac_i2c_busses, link) अणु
			अगर (p == bus->busnode) अणु
				अगर (prev && bus->flags & pmac_i2c_multibus) अणु
					स्थिर u32 *reg;
					reg = of_get_property(prev, "reg",
								शून्य);
					अगर (!reg)
						जारी;
					अगर (((*reg) >> 8) != bus->channel)
						जारी;
				पूर्ण
				of_node_put(p);
				of_node_put(prev);
				वापस bus;
			पूर्ण
		पूर्ण
		of_node_put(prev);
		prev = p;
		p = of_get_parent(p);
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(pmac_i2c_find_bus);

u8 pmac_i2c_get_dev_addr(काष्ठा device_node *device)
अणु
	स्थिर u32 *reg = of_get_property(device, "reg", शून्य);

	अगर (reg == शून्य)
		वापस 0;

	वापस (*reg) & 0xff;
पूर्ण
EXPORT_SYMBOL_GPL(pmac_i2c_get_dev_addr);

काष्ठा device_node *pmac_i2c_get_controller(काष्ठा pmac_i2c_bus *bus)
अणु
	वापस bus->controller;
पूर्ण
EXPORT_SYMBOL_GPL(pmac_i2c_get_controller);

काष्ठा device_node *pmac_i2c_get_bus_node(काष्ठा pmac_i2c_bus *bus)
अणु
	वापस bus->busnode;
पूर्ण
EXPORT_SYMBOL_GPL(pmac_i2c_get_bus_node);

पूर्णांक pmac_i2c_get_type(काष्ठा pmac_i2c_bus *bus)
अणु
	वापस bus->type;
पूर्ण
EXPORT_SYMBOL_GPL(pmac_i2c_get_type);

पूर्णांक pmac_i2c_get_flags(काष्ठा pmac_i2c_bus *bus)
अणु
	वापस bus->flags;
पूर्ण
EXPORT_SYMBOL_GPL(pmac_i2c_get_flags);

पूर्णांक pmac_i2c_get_channel(काष्ठा pmac_i2c_bus *bus)
अणु
	वापस bus->channel;
पूर्ण
EXPORT_SYMBOL_GPL(pmac_i2c_get_channel);


काष्ठा i2c_adapter *pmac_i2c_get_adapter(काष्ठा pmac_i2c_bus *bus)
अणु
	वापस &bus->adapter;
पूर्ण
EXPORT_SYMBOL_GPL(pmac_i2c_get_adapter);

काष्ठा pmac_i2c_bus *pmac_i2c_adapter_to_bus(काष्ठा i2c_adapter *adapter)
अणु
	काष्ठा pmac_i2c_bus *bus;

	list_क्रम_each_entry(bus, &pmac_i2c_busses, link)
		अगर (&bus->adapter == adapter)
			वापस bus;
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(pmac_i2c_adapter_to_bus);

पूर्णांक pmac_i2c_match_adapter(काष्ठा device_node *dev, काष्ठा i2c_adapter *adapter)
अणु
	काष्ठा pmac_i2c_bus *bus = pmac_i2c_find_bus(dev);

	अगर (bus == शून्य)
		वापस 0;
	वापस (&bus->adapter == adapter);
पूर्ण
EXPORT_SYMBOL_GPL(pmac_i2c_match_adapter);

पूर्णांक pmac_low_i2c_lock(काष्ठा device_node *np)
अणु
	काष्ठा pmac_i2c_bus *bus, *found = शून्य;

	list_क्रम_each_entry(bus, &pmac_i2c_busses, link) अणु
		अगर (np == bus->controller) अणु
			found = bus;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!found)
		वापस -ENODEV;
	वापस pmac_i2c_खोलो(bus, 0);
पूर्ण
EXPORT_SYMBOL_GPL(pmac_low_i2c_lock);

पूर्णांक pmac_low_i2c_unlock(काष्ठा device_node *np)
अणु
	काष्ठा pmac_i2c_bus *bus, *found = शून्य;

	list_क्रम_each_entry(bus, &pmac_i2c_busses, link) अणु
		अगर (np == bus->controller) अणु
			found = bus;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!found)
		वापस -ENODEV;
	pmac_i2c_बंद(bus);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pmac_low_i2c_unlock);


पूर्णांक pmac_i2c_खोलो(काष्ठा pmac_i2c_bus *bus, पूर्णांक polled)
अणु
	पूर्णांक rc;

	mutex_lock(&bus->mutex);
	bus->polled = polled || pmac_i2c_क्रमce_poll;
	bus->खोलोed = 1;
	bus->mode = pmac_i2c_mode_std;
	अगर (bus->खोलो && (rc = bus->खोलो(bus)) != 0) अणु
		bus->खोलोed = 0;
		mutex_unlock(&bus->mutex);
		वापस rc;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pmac_i2c_खोलो);

व्योम pmac_i2c_बंद(काष्ठा pmac_i2c_bus *bus)
अणु
	WARN_ON(!bus->खोलोed);
	अगर (bus->बंद)
		bus->बंद(bus);
	bus->खोलोed = 0;
	mutex_unlock(&bus->mutex);
पूर्ण
EXPORT_SYMBOL_GPL(pmac_i2c_बंद);

पूर्णांक pmac_i2c_seपंचांगode(काष्ठा pmac_i2c_bus *bus, पूर्णांक mode)
अणु
	WARN_ON(!bus->खोलोed);

	/* Report me अगर you see the error below as there might be a new
	 * "combined4" mode that I need to implement क्रम the SMU bus
	 */
	अगर (mode < pmac_i2c_mode_dumb || mode > pmac_i2c_mode_combined) अणु
		prपूर्णांकk(KERN_ERR "low_i2c: Invalid mode %d requested on"
		       " bus %pOF !\n", mode, bus->busnode);
		वापस -EINVAL;
	पूर्ण
	bus->mode = mode;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pmac_i2c_seपंचांगode);

पूर्णांक pmac_i2c_xfer(काष्ठा pmac_i2c_bus *bus, u8 addrdir, पूर्णांक subsize,
		  u32 subaddr, u8 *data, पूर्णांक len)
अणु
	पूर्णांक rc;

	WARN_ON(!bus->खोलोed);

	DBG("xfer() chan=%d, addrdir=0x%x, mode=%d, subsize=%d, subaddr=0x%x,"
	    " %d bytes, bus %pOF\n", bus->channel, addrdir, bus->mode, subsize,
	    subaddr, len, bus->busnode);

	rc = bus->xfer(bus, addrdir, subsize, subaddr, data, len);

#अगर_घोषित DEBUG
	अगर (rc)
		DBG("xfer error %d\n", rc);
#पूर्ण_अगर
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(pmac_i2c_xfer);

/* some quirks क्रम platक्रमm function decoding */
क्रमागत अणु
	pmac_i2c_quirk_invmask = 0x00000001u,
	pmac_i2c_quirk_skip = 0x00000002u,
पूर्ण;

अटल व्योम pmac_i2c_devscan(व्योम (*callback)(काष्ठा device_node *dev,
					      पूर्णांक quirks))
अणु
	काष्ठा pmac_i2c_bus *bus;
	काष्ठा device_node *np;
	अटल काष्ठा whitelist_ent अणु
		अक्षर *name;
		अक्षर *compatible;
		पूर्णांक quirks;
	पूर्ण whitelist[] = अणु
		/* XXX Study device-tree's & apple drivers are get the quirks
		 * right !
		 */
		/* Workaround: It seems that running the घड़ीspपढ़ोing
		 * properties on the eMac will cause lockups during boot.
		 * The machine seems to work fine without that. So क्रम now,
		 * let's make sure i2c-hwclock doesn't match about "imic"
		 * घड़ीs and we'll figure out अगर we really need to करो
		 * something special about those later.
		 */
		अणु "i2c-hwclock", "imic5002", pmac_i2c_quirk_skip पूर्ण,
		अणु "i2c-hwclock", "imic5003", pmac_i2c_quirk_skip पूर्ण,
		अणु "i2c-hwclock", शून्य, pmac_i2c_quirk_invmask पूर्ण,
		अणु "i2c-cpu-voltage", शून्य, 0पूर्ण,
		अणु  "temp-monitor", शून्य, 0 पूर्ण,
		अणु  "supply-monitor", शून्य, 0 पूर्ण,
		अणु शून्य, शून्य, 0 पूर्ण,
	पूर्ण;

	/* Only some devices need to have platक्रमm functions instantiated
	 * here. For now, we have a table. Others, like 9554 i2c GPIOs used
	 * on Xserve, अगर we ever करो a driver क्रम them, will use their own
	 * platक्रमm function instance
	 */
	list_क्रम_each_entry(bus, &pmac_i2c_busses, link) अणु
		क्रम_each_child_of_node(bus->busnode, np) अणु
			काष्ठा whitelist_ent *p;
			/* If multibus, check अगर device is on that bus */
			अगर (bus->flags & pmac_i2c_multibus)
				अगर (bus != pmac_i2c_find_bus(np))
					जारी;
			क्रम (p = whitelist; p->name != शून्य; p++) अणु
				अगर (!of_node_name_eq(np, p->name))
					जारी;
				अगर (p->compatible &&
				    !of_device_is_compatible(np, p->compatible))
					जारी;
				अगर (p->quirks & pmac_i2c_quirk_skip)
					अवरोध;
				callback(np, p->quirks);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

#घोषणा MAX_I2C_DATA	64

काष्ठा pmac_i2c_pf_inst
अणु
	काष्ठा pmac_i2c_bus	*bus;
	u8			addr;
	u8			buffer[MAX_I2C_DATA];
	u8			scratch[MAX_I2C_DATA];
	पूर्णांक			bytes;
	पूर्णांक			quirks;
पूर्ण;

अटल व्योम* pmac_i2c_करो_begin(काष्ठा pmf_function *func, काष्ठा pmf_args *args)
अणु
	काष्ठा pmac_i2c_pf_inst *inst;
	काष्ठा pmac_i2c_bus	*bus;

	bus = pmac_i2c_find_bus(func->node);
	अगर (bus == शून्य) अणु
		prपूर्णांकk(KERN_ERR "low_i2c: Can't find bus for %pOF (pfunc)\n",
		       func->node);
		वापस शून्य;
	पूर्ण
	अगर (pmac_i2c_खोलो(bus, 0)) अणु
		prपूर्णांकk(KERN_ERR "low_i2c: Can't open i2c bus for %pOF (pfunc)\n",
		       func->node);
		वापस शून्य;
	पूर्ण

	/* XXX might need GFP_ATOMIC when called during the suspend process,
	 * but then, there are alपढ़ोy lots of issues with suspending when
	 * near OOM that need to be resolved, the allocator itself should
	 * probably make GFP_NOIO implicit during suspend
	 */
	inst = kzalloc(माप(काष्ठा pmac_i2c_pf_inst), GFP_KERNEL);
	अगर (inst == शून्य) अणु
		pmac_i2c_बंद(bus);
		वापस शून्य;
	पूर्ण
	inst->bus = bus;
	inst->addr = pmac_i2c_get_dev_addr(func->node);
	inst->quirks = (पूर्णांक)(दीर्घ)func->driver_data;
	वापस inst;
पूर्ण

अटल व्योम pmac_i2c_करो_end(काष्ठा pmf_function *func, व्योम *instdata)
अणु
	काष्ठा pmac_i2c_pf_inst *inst = instdata;

	अगर (inst == शून्य)
		वापस;
	pmac_i2c_बंद(inst->bus);
	kमुक्त(inst);
पूर्ण

अटल पूर्णांक pmac_i2c_करो_पढ़ो(PMF_STD_ARGS, u32 len)
अणु
	काष्ठा pmac_i2c_pf_inst *inst = instdata;

	inst->bytes = len;
	वापस pmac_i2c_xfer(inst->bus, inst->addr | pmac_i2c_पढ़ो, 0, 0,
			     inst->buffer, len);
पूर्ण

अटल पूर्णांक pmac_i2c_करो_ग_लिखो(PMF_STD_ARGS, u32 len, स्थिर u8 *data)
अणु
	काष्ठा pmac_i2c_pf_inst *inst = instdata;

	वापस pmac_i2c_xfer(inst->bus, inst->addr | pmac_i2c_ग_लिखो, 0, 0,
			     (u8 *)data, len);
पूर्ण

/* This function is used to करो the masking & OR'ing क्रम the "rmw" type
 * callbacks. Ze should apply the mask and OR in the values in the
 * buffer beक्रमe writing back. The problem is that it seems that
 * various darwin drivers implement the mask/or dअगरferently, thus
 * we need to check the quirks first
 */
अटल व्योम pmac_i2c_करो_apply_rmw(काष्ठा pmac_i2c_pf_inst *inst,
				  u32 len, स्थिर u8 *mask, स्थिर u8 *val)
अणु
	पूर्णांक i;

	अगर (inst->quirks & pmac_i2c_quirk_invmask) अणु
		क्रम (i = 0; i < len; i ++)
			inst->scratch[i] = (inst->buffer[i] & mask[i]) | val[i];
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < len; i ++)
			inst->scratch[i] = (inst->buffer[i] & ~mask[i])
				| (val[i] & mask[i]);
	पूर्ण
पूर्ण

अटल पूर्णांक pmac_i2c_करो_rmw(PMF_STD_ARGS, u32 masklen, u32 valuelen,
			   u32 totallen, स्थिर u8 *maskdata,
			   स्थिर u8 *valuedata)
अणु
	काष्ठा pmac_i2c_pf_inst *inst = instdata;

	अगर (masklen > inst->bytes || valuelen > inst->bytes ||
	    totallen > inst->bytes || valuelen > masklen)
		वापस -EINVAL;

	pmac_i2c_करो_apply_rmw(inst, masklen, maskdata, valuedata);

	वापस pmac_i2c_xfer(inst->bus, inst->addr | pmac_i2c_ग_लिखो, 0, 0,
			     inst->scratch, totallen);
पूर्ण

अटल पूर्णांक pmac_i2c_करो_पढ़ो_sub(PMF_STD_ARGS, u8 subaddr, u32 len)
अणु
	काष्ठा pmac_i2c_pf_inst *inst = instdata;

	inst->bytes = len;
	वापस pmac_i2c_xfer(inst->bus, inst->addr | pmac_i2c_पढ़ो, 1, subaddr,
			     inst->buffer, len);
पूर्ण

अटल पूर्णांक pmac_i2c_करो_ग_लिखो_sub(PMF_STD_ARGS, u8 subaddr, u32 len,
				     स्थिर u8 *data)
अणु
	काष्ठा pmac_i2c_pf_inst *inst = instdata;

	वापस pmac_i2c_xfer(inst->bus, inst->addr | pmac_i2c_ग_लिखो, 1,
			     subaddr, (u8 *)data, len);
पूर्ण

अटल पूर्णांक pmac_i2c_करो_set_mode(PMF_STD_ARGS, पूर्णांक mode)
अणु
	काष्ठा pmac_i2c_pf_inst *inst = instdata;

	वापस pmac_i2c_seपंचांगode(inst->bus, mode);
पूर्ण

अटल पूर्णांक pmac_i2c_करो_rmw_sub(PMF_STD_ARGS, u8 subaddr, u32 masklen,
			       u32 valuelen, u32 totallen, स्थिर u8 *maskdata,
			       स्थिर u8 *valuedata)
अणु
	काष्ठा pmac_i2c_pf_inst *inst = instdata;

	अगर (masklen > inst->bytes || valuelen > inst->bytes ||
	    totallen > inst->bytes || valuelen > masklen)
		वापस -EINVAL;

	pmac_i2c_करो_apply_rmw(inst, masklen, maskdata, valuedata);

	वापस pmac_i2c_xfer(inst->bus, inst->addr | pmac_i2c_ग_लिखो, 1,
			     subaddr, inst->scratch, totallen);
पूर्ण

अटल पूर्णांक pmac_i2c_करो_mask_and_comp(PMF_STD_ARGS, u32 len,
				     स्थिर u8 *maskdata,
				     स्थिर u8 *valuedata)
अणु
	काष्ठा pmac_i2c_pf_inst *inst = instdata;
	पूर्णांक i, match;

	/* Get वापस value poपूर्णांकer, it's assumed to be a u32 */
	अगर (!args || !args->count || !args->u[0].p)
		वापस -EINVAL;

	/* Check buffer */
	अगर (len > inst->bytes)
		वापस -EINVAL;

	क्रम (i = 0, match = 1; match && i < len; i ++)
		अगर ((inst->buffer[i] & maskdata[i]) != valuedata[i])
			match = 0;
	*args->u[0].p = match;
	वापस 0;
पूर्ण

अटल पूर्णांक pmac_i2c_करो_delay(PMF_STD_ARGS, u32 duration)
अणु
	msleep((duration + 999) / 1000);
	वापस 0;
पूर्ण


अटल काष्ठा pmf_handlers pmac_i2c_pfunc_handlers = अणु
	.begin			= pmac_i2c_करो_begin,
	.end			= pmac_i2c_करो_end,
	.पढ़ो_i2c		= pmac_i2c_करो_पढ़ो,
	.ग_लिखो_i2c		= pmac_i2c_करो_ग_लिखो,
	.rmw_i2c		= pmac_i2c_करो_rmw,
	.पढ़ो_i2c_sub		= pmac_i2c_करो_पढ़ो_sub,
	.ग_लिखो_i2c_sub		= pmac_i2c_करो_ग_लिखो_sub,
	.rmw_i2c_sub		= pmac_i2c_करो_rmw_sub,
	.set_i2c_mode		= pmac_i2c_करो_set_mode,
	.mask_and_compare	= pmac_i2c_करो_mask_and_comp,
	.delay			= pmac_i2c_करो_delay,
पूर्ण;

अटल व्योम __init pmac_i2c_dev_create(काष्ठा device_node *np, पूर्णांक quirks)
अणु
	DBG("dev_create(%pOF)\n", np);

	pmf_रेजिस्टर_driver(np, &pmac_i2c_pfunc_handlers,
			    (व्योम *)(दीर्घ)quirks);
पूर्ण

अटल व्योम __init pmac_i2c_dev_init(काष्ठा device_node *np, पूर्णांक quirks)
अणु
	DBG("dev_create(%pOF)\n", np);

	pmf_करो_functions(np, शून्य, 0, PMF_FLAGS_ON_INIT, शून्य);
पूर्ण

अटल व्योम pmac_i2c_dev_suspend(काष्ठा device_node *np, पूर्णांक quirks)
अणु
	DBG("dev_suspend(%pOF)\n", np);
	pmf_करो_functions(np, शून्य, 0, PMF_FLAGS_ON_SLEEP, शून्य);
पूर्ण

अटल व्योम pmac_i2c_dev_resume(काष्ठा device_node *np, पूर्णांक quirks)
अणु
	DBG("dev_resume(%pOF)\n", np);
	pmf_करो_functions(np, शून्य, 0, PMF_FLAGS_ON_WAKE, शून्य);
पूर्ण

व्योम pmac_pfunc_i2c_suspend(व्योम)
अणु
	pmac_i2c_devscan(pmac_i2c_dev_suspend);
पूर्ण

व्योम pmac_pfunc_i2c_resume(व्योम)
अणु
	pmac_i2c_devscan(pmac_i2c_dev_resume);
पूर्ण

/*
 * Initialize us: probe all i2c busses on the machine, instantiate
 * busses and platक्रमm functions as needed.
 */
/* This is non-अटल as it might be called early by smp code */
पूर्णांक __init pmac_i2c_init(व्योम)
अणु
	अटल पूर्णांक i2c_inited;

	अगर (i2c_inited)
		वापस 0;
	i2c_inited = 1;

	/* Probe keywest-i2c busses */
	kw_i2c_probe();

#अगर_घोषित CONFIG_ADB_PMU
	/* Probe PMU i2c busses */
	pmu_i2c_probe();
#पूर्ण_अगर

#अगर_घोषित CONFIG_PMAC_SMU
	/* Probe SMU i2c busses */
	smu_i2c_probe();
#पूर्ण_अगर

	/* Now add plaक्रमm functions क्रम some known devices */
	pmac_i2c_devscan(pmac_i2c_dev_create);

	वापस 0;
पूर्ण
machine_arch_initcall(घातermac, pmac_i2c_init);

/* Since pmac_i2c_init can be called too early क्रम the platक्रमm device
 * registration, we need to करो it at a later समय. In our हाल, subsys
 * happens to fit well, though I agree it's a bit of a hack...
 */
अटल पूर्णांक __init pmac_i2c_create_platक्रमm_devices(व्योम)
अणु
	काष्ठा pmac_i2c_bus *bus;
	पूर्णांक i = 0;

	/* In the हाल where we are initialized from smp_init(), we must
	 * not use the समयr (and thus the irq). It's safe from now on
	 * though
	 */
	pmac_i2c_क्रमce_poll = 0;

	/* Create platक्रमm devices */
	list_क्रम_each_entry(bus, &pmac_i2c_busses, link) अणु
		bus->platक्रमm_dev =
			platक्रमm_device_alloc("i2c-powermac", i++);
		अगर (bus->platक्रमm_dev == शून्य)
			वापस -ENOMEM;
		bus->platक्रमm_dev->dev.platक्रमm_data = bus;
		bus->platक्रमm_dev->dev.of_node = bus->busnode;
		platक्रमm_device_add(bus->platक्रमm_dev);
	पूर्ण

	/* Now call platक्रमm "init" functions */
	pmac_i2c_devscan(pmac_i2c_dev_init);

	वापस 0;
पूर्ण
machine_subsys_initcall(घातermac, pmac_i2c_create_platक्रमm_devices);
