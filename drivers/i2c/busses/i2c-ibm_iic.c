<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * drivers/i2c/busses/i2c-ibm_iic.c
 *
 * Support क्रम the IIC peripheral on IBM PPC 4xx
 *
 * Copyright (c) 2003, 2004 Zultys Technologies.
 * Eugene Surovegin <eugene.surovegin@zultys.com> or <ebs@ebshome.net>
 *
 * Copyright (c) 2008 PIKA Technologies
 * Sean MacLennan <smaclennan@pikatech.com>
 *
 * Based on original work by
 * 	Ian DaSilva  <idasilva@mvista.com>
 *      Armin Kuster <akuster@mvista.com>
 * 	Matt Porter  <mporter@mvista.com>
 *
 *      Copyright 2000-2003 MontaVista Software Inc.
 *
 * Original driver version was highly leveraged from i2c-elektor.c
 *
 *   	Copyright 1995-97 Simon G. Vogl
 *                1998-99 Hans Berglund
 *
 *   	With some changes from Kyथघsti Mथअlkki <kmalkki@cc.hut.fi>
 *	and even Froकरो Looijaard <froकरोl@dds.nl>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/ioport.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sched/संकेत.स>

#समावेश <यंत्र/irq.h>
#समावेश <linux/पन.स>
#समावेश <linux/i2c.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश "i2c-ibm_iic.h"

#घोषणा DRIVER_VERSION "2.2"

MODULE_DESCRIPTION("IBM IIC driver v" DRIVER_VERSION);
MODULE_LICENSE("GPL");

अटल bool iic_क्रमce_poll;
module_param(iic_क्रमce_poll, bool, 0);
MODULE_PARM_DESC(iic_क्रमce_poll, "Force polling mode");

अटल bool iic_क्रमce_fast;
module_param(iic_क्रमce_fast, bool, 0);
MODULE_PARM_DESC(iic_क्रमce_fast, "Force fast mode (400 kHz)");

#घोषणा DBG_LEVEL 0

#अगर_घोषित DBG
#अघोषित DBG
#पूर्ण_अगर

#अगर_घोषित DBG2
#अघोषित DBG2
#पूर्ण_अगर

#अगर DBG_LEVEL > 0
#  define DBG(f,x...)	prपूर्णांकk(KERN_DEBUG "ibm-iic" f, ##x)
#अन्यथा
#  define DBG(f,x...)	((व्योम)0)
#पूर्ण_अगर
#अगर DBG_LEVEL > 1
#  define DBG2(f,x...) 	DBG(f, ##x)
#अन्यथा
#  define DBG2(f,x...) 	((व्योम)0)
#पूर्ण_अगर
#अगर DBG_LEVEL > 2
अटल व्योम dump_iic_regs(स्थिर अक्षर* header, काष्ठा ibm_iic_निजी* dev)
अणु
	अस्थिर काष्ठा iic_regs __iomem *iic = dev->vaddr;
	prपूर्णांकk(KERN_DEBUG "ibm-iic%d: %s\n", dev->idx, header);
	prपूर्णांकk(KERN_DEBUG
	       "  cntl     = 0x%02x, mdcntl = 0x%02x\n"
	       "  sts      = 0x%02x, extsts = 0x%02x\n"
	       "  clkdiv   = 0x%02x, xfrcnt = 0x%02x\n"
	       "  xtcntlss = 0x%02x, directcntl = 0x%02x\n",
		in_8(&iic->cntl), in_8(&iic->mdcntl), in_8(&iic->sts),
		in_8(&iic->extsts), in_8(&iic->clkभाग), in_8(&iic->xfrcnt),
		in_8(&iic->xtcntlss), in_8(&iic->directcntl));
पूर्ण
#  define DUMP_REGS(h,dev)	dump_iic_regs((h),(dev))
#अन्यथा
#  define DUMP_REGS(h,dev)	((व्योम)0)
#पूर्ण_अगर

/* Bus timings (in ns) क्रम bit-banging */
अटल काष्ठा ibm_iic_timings अणु
	अचिन्हित पूर्णांक hd_sta;
	अचिन्हित पूर्णांक su_sto;
	अचिन्हित पूर्णांक low;
	अचिन्हित पूर्णांक high;
	अचिन्हित पूर्णांक buf;
पूर्ण timings [] = अणु
/* Standard mode (100 KHz) */
अणु
	.hd_sta	= 4000,
	.su_sto	= 4000,
	.low	= 4700,
	.high	= 4000,
	.buf	= 4700,
पूर्ण,
/* Fast mode (400 KHz) */
अणु
	.hd_sta = 600,
	.su_sto	= 600,
	.low 	= 1300,
	.high 	= 600,
	.buf	= 1300,
पूर्णपूर्ण;

/* Enable/disable पूर्णांकerrupt generation */
अटल अंतरभूत व्योम iic_पूर्णांकerrupt_mode(काष्ठा ibm_iic_निजी* dev, पूर्णांक enable)
अणु
	out_8(&dev->vaddr->पूर्णांकmsk, enable ? INTRMSK_EIMTC : 0);
पूर्ण

/*
 * Initialize IIC पूर्णांकerface.
 */
अटल व्योम iic_dev_init(काष्ठा ibm_iic_निजी* dev)
अणु
	अस्थिर काष्ठा iic_regs __iomem *iic = dev->vaddr;

	DBG("%d: init\n", dev->idx);

	/* Clear master address */
	out_8(&iic->lmadr, 0);
	out_8(&iic->hmadr, 0);

	/* Clear slave address */
	out_8(&iic->lsadr, 0);
	out_8(&iic->hsadr, 0);

	/* Clear status & extended status */
	out_8(&iic->sts, STS_SCMP | STS_IRQA);
	out_8(&iic->extsts, EXTSTS_IRQP | EXTSTS_IRQD | EXTSTS_LA
			    | EXTSTS_ICT | EXTSTS_XFRA);

	/* Set घड़ी भागider */
	out_8(&iic->clkभाग, dev->clckभाग);

	/* Clear transfer count */
	out_8(&iic->xfrcnt, 0);

	/* Clear extended control and status */
	out_8(&iic->xtcntlss, XTCNTLSS_SRC | XTCNTLSS_SRS | XTCNTLSS_SWC
			    | XTCNTLSS_SWS);

	/* Clear control रेजिस्टर */
	out_8(&iic->cntl, 0);

	/* Enable पूर्णांकerrupts अगर possible */
	iic_पूर्णांकerrupt_mode(dev, dev->irq >= 0);

	/* Set mode control */
	out_8(&iic->mdcntl, MDCNTL_FMDB | MDCNTL_EINT | MDCNTL_EUBS
			    | (dev->fast_mode ? MDCNTL_FSM : 0));

	DUMP_REGS("iic_init", dev);
पूर्ण

/*
 * Reset IIC पूर्णांकerface
 */
अटल व्योम iic_dev_reset(काष्ठा ibm_iic_निजी* dev)
अणु
	अस्थिर काष्ठा iic_regs __iomem *iic = dev->vaddr;
	पूर्णांक i;
	u8 dc;

	DBG("%d: soft reset\n", dev->idx);
	DUMP_REGS("reset", dev);

    	/* Place chip in the reset state */
	out_8(&iic->xtcntlss, XTCNTLSS_SRST);

	/* Check अगर bus is मुक्त */
	dc = in_8(&iic->directcntl);
	अगर (!सूचीCTNL_FREE(dc))अणु
		DBG("%d: trying to regain bus control\n", dev->idx);

		/* Try to set bus मुक्त state */
		out_8(&iic->directcntl, सूचीCNTL_SDAC | सूचीCNTL_SCC);

		/* Wait until we regain bus control */
		क्रम (i = 0; i < 100; ++i)अणु
			dc = in_8(&iic->directcntl);
			अगर (सूचीCTNL_FREE(dc))
				अवरोध;

			/* Toggle SCL line */
			dc ^= सूचीCNTL_SCC;
			out_8(&iic->directcntl, dc);
			udelay(10);
			dc ^= सूचीCNTL_SCC;
			out_8(&iic->directcntl, dc);

			/* be nice */
			cond_resched();
		पूर्ण
	पूर्ण

	/* Remove reset */
	out_8(&iic->xtcntlss, 0);

	/* Reinitialize पूर्णांकerface */
	iic_dev_init(dev);
पूर्ण

/*
 * Do 0-length transaction using bit-banging through IIC_सूचीECTCNTL रेजिस्टर.
 */

/* Wait क्रम SCL and/or SDA to be high */
अटल पूर्णांक iic_dc_रुको(अस्थिर काष्ठा iic_regs __iomem *iic, u8 mask)
अणु
	अचिन्हित दीर्घ x = jअगरfies + HZ / 28 + 2;
	जबतक ((in_8(&iic->directcntl) & mask) != mask)अणु
		अगर (unlikely(समय_after(jअगरfies, x)))
			वापस -1;
		cond_resched();
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक iic_smbus_quick(काष्ठा ibm_iic_निजी* dev, स्थिर काष्ठा i2c_msg* p)
अणु
	अस्थिर काष्ठा iic_regs __iomem *iic = dev->vaddr;
	स्थिर काष्ठा ibm_iic_timings *t = &timings[dev->fast_mode ? 1 : 0];
	u8 mask, v, sda;
	पूर्णांक i, res;

	/* Only 7-bit addresses are supported */
	अगर (unlikely(p->flags & I2C_M_TEN))अणु
		DBG("%d: smbus_quick - 10 bit addresses are not supported\n",
			dev->idx);
		वापस -EINVAL;
	पूर्ण

	DBG("%d: smbus_quick(0x%02x)\n", dev->idx, p->addr);

	/* Reset IIC पूर्णांकerface */
	out_8(&iic->xtcntlss, XTCNTLSS_SRST);

	/* Wait क्रम bus to become मुक्त */
	out_8(&iic->directcntl, सूचीCNTL_SDAC | सूचीCNTL_SCC);
	अगर (unlikely(iic_dc_रुको(iic, सूचीCNTL_MSDA | सूचीCNTL_MSC)))
		जाओ err;
	ndelay(t->buf);

	/* START */
	out_8(&iic->directcntl, सूचीCNTL_SCC);
	sda = 0;
	ndelay(t->hd_sta);

	/* Send address */
	v = i2c_8bit_addr_from_msg(p);
	क्रम (i = 0, mask = 0x80; i < 8; ++i, mask >>= 1)अणु
		out_8(&iic->directcntl, sda);
		ndelay(t->low / 2);
		sda = (v & mask) ? सूचीCNTL_SDAC : 0;
		out_8(&iic->directcntl, sda);
		ndelay(t->low / 2);

		out_8(&iic->directcntl, सूचीCNTL_SCC | sda);
		अगर (unlikely(iic_dc_रुको(iic, सूचीCNTL_MSC)))
			जाओ err;
		ndelay(t->high);
	पूर्ण

	/* ACK */
	out_8(&iic->directcntl, sda);
	ndelay(t->low / 2);
	out_8(&iic->directcntl, सूचीCNTL_SDAC);
	ndelay(t->low / 2);
	out_8(&iic->directcntl, सूचीCNTL_SDAC | सूचीCNTL_SCC);
	अगर (unlikely(iic_dc_रुको(iic, सूचीCNTL_MSC)))
		जाओ err;
	res = (in_8(&iic->directcntl) & सूचीCNTL_MSDA) ? -EREMOTEIO : 1;
	ndelay(t->high);

	/* STOP */
	out_8(&iic->directcntl, 0);
	ndelay(t->low);
	out_8(&iic->directcntl, सूचीCNTL_SCC);
	अगर (unlikely(iic_dc_रुको(iic, सूचीCNTL_MSC)))
		जाओ err;
	ndelay(t->su_sto);
	out_8(&iic->directcntl, सूचीCNTL_SDAC | सूचीCNTL_SCC);

	ndelay(t->buf);

	DBG("%d: smbus_quick -> %s\n", dev->idx, res ? "NACK" : "ACK");
out:
	/* Remove reset */
	out_8(&iic->xtcntlss, 0);

	/* Reinitialize पूर्णांकerface */
	iic_dev_init(dev);

	वापस res;
err:
	DBG("%d: smbus_quick - bus is stuck\n", dev->idx);
	res = -EREMOTEIO;
	जाओ out;
पूर्ण

/*
 * IIC पूर्णांकerrupt handler
 */
अटल irqवापस_t iic_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ibm_iic_निजी* dev = (काष्ठा ibm_iic_निजी*)dev_id;
	अस्थिर काष्ठा iic_regs __iomem *iic = dev->vaddr;

	DBG2("%d: irq handler, STS = 0x%02x, EXTSTS = 0x%02x\n",
	     dev->idx, in_8(&iic->sts), in_8(&iic->extsts));

	/* Acknowledge IRQ and wakeup iic_रुको_क्रम_tc */
	out_8(&iic->sts, STS_IRQA | STS_SCMP);
	wake_up_पूर्णांकerruptible(&dev->wq);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * Get master transfer result and clear errors अगर any.
 * Returns the number of actually transferred bytes or error (<0)
 */
अटल पूर्णांक iic_xfer_result(काष्ठा ibm_iic_निजी* dev)
अणु
	अस्थिर काष्ठा iic_regs __iomem *iic = dev->vaddr;

	अगर (unlikely(in_8(&iic->sts) & STS_ERR))अणु
		DBG("%d: xfer error, EXTSTS = 0x%02x\n", dev->idx,
			in_8(&iic->extsts));

		/* Clear errors and possible pending IRQs */
		out_8(&iic->extsts, EXTSTS_IRQP | EXTSTS_IRQD |
			EXTSTS_LA | EXTSTS_ICT | EXTSTS_XFRA);

		/* Flush master data buffer */
		out_8(&iic->mdcntl, in_8(&iic->mdcntl) | MDCNTL_FMDB);

		/* Is bus मुक्त?
		 * If error happened during combined xfer
		 * IIC पूर्णांकerface is usually stuck in some strange
		 * state, the only way out - soft reset.
		 */
		अगर ((in_8(&iic->extsts) & EXTSTS_BCS_MASK) != EXTSTS_BCS_FREE)अणु
			DBG("%d: bus is stuck, resetting\n", dev->idx);
			iic_dev_reset(dev);
		पूर्ण
		वापस -EREMOTEIO;
	पूर्ण
	अन्यथा
		वापस in_8(&iic->xfrcnt) & XFRCNT_MTC_MASK;
पूर्ण

/*
 * Try to पात active transfer.
 */
अटल व्योम iic_पात_xfer(काष्ठा ibm_iic_निजी* dev)
अणु
	अस्थिर काष्ठा iic_regs __iomem *iic = dev->vaddr;
	अचिन्हित दीर्घ x;

	DBG("%d: iic_abort_xfer\n", dev->idx);

	out_8(&iic->cntl, CNTL_HMT);

	/*
	 * Wait क्रम the पात command to complete.
	 * It's not worth to be optimized, just poll (समयout >= 1 tick)
	 */
	x = jअगरfies + 2;
	जबतक ((in_8(&iic->extsts) & EXTSTS_BCS_MASK) != EXTSTS_BCS_FREE)अणु
		अगर (समय_after(jअगरfies, x))अणु
			DBG("%d: abort timeout, resetting...\n", dev->idx);
			iic_dev_reset(dev);
			वापस;
		पूर्ण
		schedule();
	पूर्ण

	/* Just to clear errors */
	iic_xfer_result(dev);
पूर्ण

/*
 * Wait क्रम master transfer to complete.
 * It माला_दो current process to sleep until we get पूर्णांकerrupt or समयout expires.
 * Returns the number of transferred bytes or error (<0)
 */
अटल पूर्णांक iic_रुको_क्रम_tc(काष्ठा ibm_iic_निजी* dev)अणु

	अस्थिर काष्ठा iic_regs __iomem *iic = dev->vaddr;
	पूर्णांक ret = 0;

	अगर (dev->irq >= 0)अणु
		/* Interrupt mode */
		ret = रुको_event_पूर्णांकerruptible_समयout(dev->wq,
			!(in_8(&iic->sts) & STS_PT), dev->adap.समयout);

		अगर (unlikely(ret < 0))
			DBG("%d: wait interrupted\n", dev->idx);
		अन्यथा अगर (unlikely(in_8(&iic->sts) & STS_PT))अणु
			DBG("%d: wait timeout\n", dev->idx);
			ret = -ETIMEDOUT;
		पूर्ण
	पूर्ण
	अन्यथा अणु
		/* Polling mode */
		अचिन्हित दीर्घ x = jअगरfies + dev->adap.समयout;

		जबतक (in_8(&iic->sts) & STS_PT)अणु
			अगर (unlikely(समय_after(jअगरfies, x)))अणु
				DBG("%d: poll timeout\n", dev->idx);
				ret = -ETIMEDOUT;
				अवरोध;
			पूर्ण

			अगर (संकेत_pending(current))अणु
				DBG("%d: poll interrupted\n", dev->idx);
				ret = -ERESTARTSYS;
				अवरोध;
			पूर्ण
			schedule();
		पूर्ण
	पूर्ण

	अगर (unlikely(ret < 0))
		iic_पात_xfer(dev);
	अन्यथा
		ret = iic_xfer_result(dev);

	DBG2("%d: iic_wait_for_tc -> %d\n", dev->idx, ret);

	वापस ret;
पूर्ण

/*
 * Low level master transfer routine
 */
अटल पूर्णांक iic_xfer_bytes(काष्ठा ibm_iic_निजी* dev, काष्ठा i2c_msg* pm,
			  पूर्णांक combined_xfer)
अणु
	अस्थिर काष्ठा iic_regs __iomem *iic = dev->vaddr;
	अक्षर* buf = pm->buf;
	पूर्णांक i, j, loops, ret = 0;
	पूर्णांक len = pm->len;

	u8 cntl = (in_8(&iic->cntl) & CNTL_AMD) | CNTL_PT;
	अगर (pm->flags & I2C_M_RD)
		cntl |= CNTL_RW;

	loops = (len + 3) / 4;
	क्रम (i = 0; i < loops; ++i, len -= 4)अणु
		पूर्णांक count = len > 4 ? 4 : len;
		u8 cmd = cntl | ((count - 1) << CNTL_TCT_SHIFT);

		अगर (!(cntl & CNTL_RW))
			क्रम (j = 0; j < count; ++j)
				out_8((व्योम __iomem *)&iic->mdbuf, *buf++);

		अगर (i < loops - 1)
			cmd |= CNTL_CHT;
		अन्यथा अगर (combined_xfer)
			cmd |= CNTL_RPST;

		DBG2("%d: xfer_bytes, %d, CNTL = 0x%02x\n", dev->idx, count, cmd);

		/* Start transfer */
		out_8(&iic->cntl, cmd);

		/* Wait क्रम completion */
		ret = iic_रुको_क्रम_tc(dev);

		अगर (unlikely(ret < 0))
			अवरोध;
		अन्यथा अगर (unlikely(ret != count))अणु
			DBG("%d: xfer_bytes, requested %d, transferred %d\n",
				dev->idx, count, ret);

			/* If it's not a last part of xfer, पात it */
			अगर (combined_xfer || (i < loops - 1))
    				iic_पात_xfer(dev);

			ret = -EREMOTEIO;
			अवरोध;
		पूर्ण

		अगर (cntl & CNTL_RW)
			क्रम (j = 0; j < count; ++j)
				*buf++ = in_8((व्योम __iomem *)&iic->mdbuf);
	पूर्ण

	वापस ret > 0 ? 0 : ret;
पूर्ण

/*
 * Set target slave address क्रम master transfer
 */
अटल अंतरभूत व्योम iic_address(काष्ठा ibm_iic_निजी* dev, काष्ठा i2c_msg* msg)
अणु
	अस्थिर काष्ठा iic_regs __iomem *iic = dev->vaddr;
	u16 addr = msg->addr;

	DBG2("%d: iic_address, 0x%03x (%d-bit)\n", dev->idx,
		addr, msg->flags & I2C_M_TEN ? 10 : 7);

	अगर (msg->flags & I2C_M_TEN)अणु
	    out_8(&iic->cntl, CNTL_AMD);
	    out_8(&iic->lmadr, addr);
	    out_8(&iic->hmadr, 0xf0 | ((addr >> 7) & 0x06));
	पूर्ण
	अन्यथा अणु
	    out_8(&iic->cntl, 0);
	    out_8(&iic->lmadr, addr << 1);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक iic_invalid_address(स्थिर काष्ठा i2c_msg* p)
अणु
	वापस (p->addr > 0x3ff) || (!(p->flags & I2C_M_TEN) && (p->addr > 0x7f));
पूर्ण

अटल अंतरभूत पूर्णांक iic_address_neq(स्थिर काष्ठा i2c_msg* p1,
				  स्थिर काष्ठा i2c_msg* p2)
अणु
	वापस (p1->addr != p2->addr)
		|| ((p1->flags & I2C_M_TEN) != (p2->flags & I2C_M_TEN));
पूर्ण

/*
 * Generic master transfer entrypoपूर्णांक.
 * Returns the number of processed messages or error (<0)
 */
अटल पूर्णांक iic_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
    	काष्ठा ibm_iic_निजी* dev = (काष्ठा ibm_iic_निजी*)(i2c_get_adapdata(adap));
	अस्थिर काष्ठा iic_regs __iomem *iic = dev->vaddr;
	पूर्णांक i, ret = 0;

	DBG2("%d: iic_xfer, %d msg(s)\n", dev->idx, num);

	/* Check the sanity of the passed messages.
	 * Uhh, generic i2c layer is more suitable place क्रम such code...
	 */
	अगर (unlikely(iic_invalid_address(&msgs[0])))अणु
		DBG("%d: invalid address 0x%03x (%d-bit)\n", dev->idx,
			msgs[0].addr, msgs[0].flags & I2C_M_TEN ? 10 : 7);
		वापस -EINVAL;
	पूर्ण
	क्रम (i = 0; i < num; ++i)अणु
		अगर (unlikely(msgs[i].len <= 0))अणु
			अगर (num == 1 && !msgs[0].len)अणु
				/* Special हाल क्रम I2C_SMBUS_QUICK emulation.
				 * IBM IIC करोesn't support 0-length transactions
				 * so we have to emulate them using bit-banging.
				 */
				वापस iic_smbus_quick(dev, &msgs[0]);
			पूर्ण
			DBG("%d: invalid len %d in msg[%d]\n", dev->idx,
				msgs[i].len, i);
			वापस -EINVAL;
		पूर्ण
		अगर (unlikely(iic_address_neq(&msgs[0], &msgs[i])))अणु
			DBG("%d: invalid addr in msg[%d]\n", dev->idx, i);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* Check bus state */
	अगर (unlikely((in_8(&iic->extsts) & EXTSTS_BCS_MASK) != EXTSTS_BCS_FREE))अणु
		DBG("%d: iic_xfer, bus is not free\n", dev->idx);

		/* Usually it means something serious has happened.
		 * We *cannot* have unfinished previous transfer
		 * so it करोesn't make any sense to try to stop it.
		 * Probably we were not able to recover from the
		 * previous error.
		 * The only *reasonable* thing I can think of here
		 * is soft reset.  --ebs
		 */
		iic_dev_reset(dev);

		अगर ((in_8(&iic->extsts) & EXTSTS_BCS_MASK) != EXTSTS_BCS_FREE)अणु
			DBG("%d: iic_xfer, bus is still not free\n", dev->idx);
			वापस -EREMOTEIO;
		पूर्ण
	पूर्ण
	अन्यथा अणु
		/* Flush master data buffer (just in हाल) */
		out_8(&iic->mdcntl, in_8(&iic->mdcntl) | MDCNTL_FMDB);
	पूर्ण

	/* Load slave address */
	iic_address(dev, &msgs[0]);

	/* Do real transfer */
    	क्रम (i = 0; i < num && !ret; ++i)
		ret = iic_xfer_bytes(dev, &msgs[i], i < num - 1);

	वापस ret < 0 ? ret : num;
पूर्ण

अटल u32 iic_func(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL | I2C_FUNC_10BIT_ADDR;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm iic_algo = अणु
	.master_xfer 	= iic_xfer,
	.functionality	= iic_func
पूर्ण;

/*
 * Calculates IICx_CLCKDIV value क्रम a specअगरic OPB घड़ी frequency
 */
अटल अंतरभूत u8 iic_clckभाग(अचिन्हित पूर्णांक opb)
अणु
	/* Compatibility kludge, should go away after all cards
	 * are fixed to fill correct value क्रम opbfreq.
	 * Previous driver version used hardcoded भागider value 4,
	 * it corresponds to OPB frequency from the range (40, 50] MHz
	 */
	अगर (!opb)अणु
		prपूर्णांकk(KERN_WARNING "ibm-iic: using compatibility value for OPB freq,"
			" fix your board specific setup\n");
		opb = 50000000;
	पूर्ण

	/* Convert to MHz */
	opb /= 1000000;

	अगर (opb < 20 || opb > 150)अणु
		prपूर्णांकk(KERN_WARNING "ibm-iic: invalid OPB clock frequency %u MHz\n",
			opb);
		opb = opb < 20 ? 20 : 150;
	पूर्ण
	वापस (u8)((opb + 9) / 10 - 1);
पूर्ण

अटल पूर्णांक iic_request_irq(काष्ठा platक्रमm_device *ofdev,
				     काष्ठा ibm_iic_निजी *dev)
अणु
	काष्ठा device_node *np = ofdev->dev.of_node;
	पूर्णांक irq;

	अगर (iic_क्रमce_poll)
		वापस 0;

	irq = irq_of_parse_and_map(np, 0);
	अगर (!irq) अणु
		dev_err(&ofdev->dev, "irq_of_parse_and_map failed\n");
		वापस 0;
	पूर्ण

	/* Disable पूर्णांकerrupts until we finish initialization, assumes
	 *  level-sensitive IRQ setup...
	 */
	iic_पूर्णांकerrupt_mode(dev, 0);
	अगर (request_irq(irq, iic_handler, 0, "IBM IIC", dev)) अणु
		dev_err(&ofdev->dev, "request_irq %d failed\n", irq);
		/* Fallback to the polling mode */
		वापस 0;
	पूर्ण

	वापस irq;
पूर्ण

/*
 * Register single IIC पूर्णांकerface
 */
अटल पूर्णांक iic_probe(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा device_node *np = ofdev->dev.of_node;
	काष्ठा ibm_iic_निजी *dev;
	काष्ठा i2c_adapter *adap;
	स्थिर u32 *freq;
	पूर्णांक ret;

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev) अणु
		dev_err(&ofdev->dev, "failed to allocate device data\n");
		वापस -ENOMEM;
	पूर्ण

	platक्रमm_set_drvdata(ofdev, dev);

	dev->vaddr = of_iomap(np, 0);
	अगर (dev->vaddr == शून्य) अणु
		dev_err(&ofdev->dev, "failed to iomap device\n");
		ret = -ENXIO;
		जाओ error_cleanup;
	पूर्ण

	init_रुकोqueue_head(&dev->wq);

	dev->irq = iic_request_irq(ofdev, dev);
	अगर (!dev->irq)
		dev_warn(&ofdev->dev, "using polling mode\n");

	/* Board specअगरic settings */
	अगर (iic_क्रमce_fast || of_get_property(np, "fast-mode", शून्य))
		dev->fast_mode = 1;

	freq = of_get_property(np, "clock-frequency", शून्य);
	अगर (freq == शून्य) अणु
		freq = of_get_property(np->parent, "clock-frequency", शून्य);
		अगर (freq == शून्य) अणु
			dev_err(&ofdev->dev, "Unable to get bus frequency\n");
			ret = -EINVAL;
			जाओ error_cleanup;
		पूर्ण
	पूर्ण

	dev->clckभाग = iic_clckभाग(*freq);
	dev_dbg(&ofdev->dev, "clckdiv = %d\n", dev->clckभाग);

	/* Initialize IIC पूर्णांकerface */
	iic_dev_init(dev);

	/* Register it with i2c layer */
	adap = &dev->adap;
	adap->dev.parent = &ofdev->dev;
	adap->dev.of_node = of_node_get(np);
	strlcpy(adap->name, "IBM IIC", माप(adap->name));
	i2c_set_adapdata(adap, dev);
	adap->class = I2C_CLASS_HWMON | I2C_CLASS_SPD;
	adap->algo = &iic_algo;
	adap->समयout = HZ;

	ret = i2c_add_adapter(adap);
	अगर (ret  < 0)
		जाओ error_cleanup;

	dev_info(&ofdev->dev, "using %s mode\n",
		 dev->fast_mode ? "fast (400 kHz)" : "standard (100 kHz)");

	वापस 0;

error_cleanup:
	अगर (dev->irq) अणु
		iic_पूर्णांकerrupt_mode(dev, 0);
		मुक्त_irq(dev->irq, dev);
	पूर्ण

	अगर (dev->vaddr)
		iounmap(dev->vaddr);

	kमुक्त(dev);
	वापस ret;
पूर्ण

/*
 * Cleanup initialized IIC पूर्णांकerface
 */
अटल पूर्णांक iic_हटाओ(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा ibm_iic_निजी *dev = platक्रमm_get_drvdata(ofdev);

	i2c_del_adapter(&dev->adap);

	अगर (dev->irq) अणु
		iic_पूर्णांकerrupt_mode(dev, 0);
		मुक्त_irq(dev->irq, dev);
	पूर्ण

	iounmap(dev->vaddr);
	kमुक्त(dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ibm_iic_match[] = अणु
	अणु .compatible = "ibm,iic", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ibm_iic_match);

अटल काष्ठा platक्रमm_driver ibm_iic_driver = अणु
	.driver = अणु
		.name = "ibm-iic",
		.of_match_table = ibm_iic_match,
	पूर्ण,
	.probe	= iic_probe,
	.हटाओ	= iic_हटाओ,
पूर्ण;

module_platक्रमm_driver(ibm_iic_driver);
