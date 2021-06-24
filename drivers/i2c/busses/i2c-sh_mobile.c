<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SuperH Mobile I2C Controller
 *
 * Copyright (C) 2014-19 Wolfram Sang <wsa@sang-engineering.com>
 * Copyright (C) 2008 Magnus Damm
 *
 * Portions of the code based on out-of-tree driver i2c-sh7343.c
 * Copyright (c) 2006 Carlos Munoz <carlos@kenati.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>

/* Transmit operation:                                                      */
/*                                                                          */
/* 0 byte transmit                                                          */
/* BUS:     S     A8     ACK   P(*)                                         */
/* IRQ:       DTE   WAIT                                                    */
/* ICIC:                                                                    */
/* ICCR: 0x94       0x90                                                    */
/* ICDR:      A8                                                            */
/*                                                                          */
/* 1 byte transmit                                                          */
/* BUS:     S     A8     ACK   D8(1)   ACK   P(*)                           */
/* IRQ:       DTE   WAIT         WAIT                                       */
/* ICIC:      -DTE                                                          */
/* ICCR: 0x94                    0x90                                       */
/* ICDR:      A8    D8(1)                                                   */
/*                                                                          */
/* 2 byte transmit                                                          */
/* BUS:     S     A8     ACK   D8(1)   ACK   D8(2)   ACK   P(*)             */
/* IRQ:       DTE   WAIT         WAIT          WAIT                         */
/* ICIC:      -DTE                                                          */
/* ICCR: 0x94                                  0x90                         */
/* ICDR:      A8    D8(1)        D8(2)                                      */
/*                                                                          */
/* 3 bytes or more, +---------+ माला_लो repeated                               */
/*                                                                          */
/*                                                                          */
/* Receive operation:                                                       */
/*                                                                          */
/* 0 byte receive - not supported since slave may hold SDA low              */
/*                                                                          */
/* 1 byte receive       [TX] | [RX]                                         */
/* BUS:     S     A8     ACK | D8(1)   ACK   P(*)                           */
/* IRQ:       DTE   WAIT     |   WAIT     DTE                               */
/* ICIC:      -DTE           |   +DTE                                       */
/* ICCR: 0x94       0x81     |   0xc0                                       */
/* ICDR:      A8             |            D8(1)                             */
/*                                                                          */
/* 2 byte receive        [TX]| [RX]                                         */
/* BUS:     S     A8     ACK | D8(1)   ACK   D8(2)   ACK   P(*)             */
/* IRQ:       DTE   WAIT     |   WAIT          WAIT     DTE                 */
/* ICIC:      -DTE           |                 +DTE                         */
/* ICCR: 0x94       0x81     |                 0xc0                         */
/* ICDR:      A8             |                 D8(1)    D8(2)               */
/*                                                                          */
/* 3 byte receive       [TX] | [RX]                                     (*) */
/* BUS:     S     A8     ACK | D8(1)   ACK   D8(2)   ACK   D8(3)   ACK    P */
/* IRQ:       DTE   WAIT     |   WAIT          WAIT         WAIT      DTE   */
/* ICIC:      -DTE           |                              +DTE            */
/* ICCR: 0x94       0x81     |                              0xc0            */
/* ICDR:      A8             |                 D8(1)        D8(2)     D8(3) */
/*                                                                          */
/* 4 bytes or more, this part is repeated    +---------+                    */
/*                                                                          */
/*                                                                          */
/* Interrupt order and BUSY flag                                            */
/*     ___                                                 _                */
/* SDA ___\___XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXAAAAAAAAA___/                 */
/* SCL      \_/1\_/2\_/3\_/4\_/5\_/6\_/7\_/8\___/9\_____/                   */
/*                                                                          */
/*        S   D7  D6  D5  D4  D3  D2  D1  D0              P(*)              */
/*                                           ___                            */
/* WAIT IRQ ________________________________/   \___________                */
/* TACK IRQ ____________________________________/   \_______                */
/* DTE  IRQ __________________________________________/   \_                */
/* AL   IRQ XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX                */
/*         _______________________________________________                  */
/* BUSY __/                                               \_                */
/*                                                                          */
/* (*) The STOP condition is only sent by the master at the end of the last */
/* I2C message or अगर the I2C_M_STOP flag is set. Similarly, the BUSY bit is */
/* only cleared after the STOP condition, so, between messages we have to   */
/* poll क्रम the DTE bit.                                                    */
/*                                                                          */

क्रमागत sh_mobile_i2c_op अणु
	OP_START = 0,
	OP_TX_FIRST,
	OP_TX,
	OP_TX_STOP,
	OP_TX_TO_RX,
	OP_RX,
	OP_RX_STOP,
	OP_RX_STOP_DATA,
पूर्ण;

काष्ठा sh_mobile_i2c_data अणु
	काष्ठा device *dev;
	व्योम __iomem *reg;
	काष्ठा i2c_adapter adap;
	अचिन्हित दीर्घ bus_speed;
	अचिन्हित पूर्णांक clks_per_count;
	काष्ठा clk *clk;
	u_पूर्णांक8_t icic;
	u_पूर्णांक8_t flags;
	u_पूर्णांक16_t iccl;
	u_पूर्णांक16_t icch;

	spinlock_t lock;
	रुको_queue_head_t रुको;
	काष्ठा i2c_msg *msg;
	पूर्णांक pos;
	पूर्णांक sr;
	bool send_stop;
	bool stop_after_dma;
	bool atomic_xfer;

	काष्ठा resource *res;
	काष्ठा dma_chan *dma_tx;
	काष्ठा dma_chan *dma_rx;
	काष्ठा scatterlist sg;
	क्रमागत dma_data_direction dma_direction;
	u8 *dma_buf;
पूर्ण;

काष्ठा sh_mobile_dt_config अणु
	पूर्णांक clks_per_count;
	पूर्णांक (*setup)(काष्ठा sh_mobile_i2c_data *pd);
पूर्ण;

#घोषणा IIC_FLAG_HAS_ICIC67	(1 << 0)

/* Register offsets */
#घोषणा ICDR			0x00
#घोषणा ICCR			0x04
#घोषणा ICSR			0x08
#घोषणा ICIC			0x0c
#घोषणा ICCL			0x10
#घोषणा ICCH			0x14
#घोषणा ICSTART			0x70

/* Register bits */
#घोषणा ICCR_ICE		0x80
#घोषणा ICCR_RACK		0x40
#घोषणा ICCR_TRS		0x10
#घोषणा ICCR_BBSY		0x04
#घोषणा ICCR_SCP		0x01

#घोषणा ICSR_SCLM		0x80
#घोषणा ICSR_SDAM		0x40
#घोषणा SW_DONE			0x20
#घोषणा ICSR_BUSY		0x10
#घोषणा ICSR_AL			0x08
#घोषणा ICSR_TACK		0x04
#घोषणा ICSR_WAIT		0x02
#घोषणा ICSR_DTE		0x01

#घोषणा ICIC_ICCLB8		0x80
#घोषणा ICIC_ICCHB8		0x40
#घोषणा ICIC_TDMAE		0x20
#घोषणा ICIC_RDMAE		0x10
#घोषणा ICIC_ALE		0x08
#घोषणा ICIC_TACKE		0x04
#घोषणा ICIC_WAITE		0x02
#घोषणा ICIC_DTEE		0x01

#घोषणा ICSTART_ICSTART		0x10

अटल व्योम iic_wr(काष्ठा sh_mobile_i2c_data *pd, पूर्णांक offs, अचिन्हित अक्षर data)
अणु
	अगर (offs == ICIC)
		data |= pd->icic;

	ioग_लिखो8(data, pd->reg + offs);
पूर्ण

अटल अचिन्हित अक्षर iic_rd(काष्ठा sh_mobile_i2c_data *pd, पूर्णांक offs)
अणु
	वापस ioपढ़ो8(pd->reg + offs);
पूर्ण

अटल व्योम iic_set_clr(काष्ठा sh_mobile_i2c_data *pd, पूर्णांक offs,
			अचिन्हित अक्षर set, अचिन्हित अक्षर clr)
अणु
	iic_wr(pd, offs, (iic_rd(pd, offs) | set) & ~clr);
पूर्ण

अटल u32 sh_mobile_i2c_iccl(अचिन्हित दीर्घ count_khz, u32 tLOW, u32 tf)
अणु
	/*
	 * Conditional expression:
	 *   ICCL >= COUNT_CLK * (tLOW + tf)
	 *
	 * SH-Mobile IIC hardware starts counting the LOW period of
	 * the SCL संकेत (tLOW) as soon as it pulls the SCL line.
	 * In order to meet the tLOW timing spec, we need to take पूर्णांकo
	 * account the fall समय of SCL संकेत (tf).  Default tf value
	 * should be 0.3 us, क्रम safety.
	 */
	वापस (((count_khz * (tLOW + tf)) + 5000) / 10000);
पूर्ण

अटल u32 sh_mobile_i2c_icch(अचिन्हित दीर्घ count_khz, u32 tHIGH, u32 tf)
अणु
	/*
	 * Conditional expression:
	 *   ICCH >= COUNT_CLK * (tHIGH + tf)
	 *
	 * SH-Mobile IIC hardware is aware of SCL transition period 'tr',
	 * and can ignore it.  SH-Mobile IIC controller starts counting
	 * the HIGH period of the SCL संकेत (tHIGH) after the SCL input
	 * voltage increases at VIH.
	 *
	 * Afterward it turned out calculating ICCH using only tHIGH spec
	 * will result in violation of the tHD;STA timing spec.  We need
	 * to take पूर्णांकo account the fall समय of SDA संकेत (tf) at START
	 * condition, in order to meet both tHIGH and tHD;STA specs.
	 */
	वापस (((count_khz * (tHIGH + tf)) + 5000) / 10000);
पूर्ण

अटल पूर्णांक sh_mobile_i2c_check_timing(काष्ठा sh_mobile_i2c_data *pd)
अणु
	u16 max_val = pd->flags & IIC_FLAG_HAS_ICIC67 ? 0x1ff : 0xff;

	अगर (pd->iccl > max_val || pd->icch > max_val) अणु
		dev_err(pd->dev, "timing values out of range: L/H=0x%x/0x%x\n",
			pd->iccl, pd->icch);
		वापस -EINVAL;
	पूर्ण

	/* one more bit of ICCL in ICIC */
	अगर (pd->iccl & 0x100)
		pd->icic |= ICIC_ICCLB8;
	अन्यथा
		pd->icic &= ~ICIC_ICCLB8;

	/* one more bit of ICCH in ICIC */
	अगर (pd->icch & 0x100)
		pd->icic |= ICIC_ICCHB8;
	अन्यथा
		pd->icic &= ~ICIC_ICCHB8;

	dev_dbg(pd->dev, "timing values: L/H=0x%x/0x%x\n", pd->iccl, pd->icch);
	वापस 0;
पूर्ण

अटल पूर्णांक sh_mobile_i2c_init(काष्ठा sh_mobile_i2c_data *pd)
अणु
	अचिन्हित दीर्घ i2c_clk_khz;
	u32 tHIGH, tLOW, tf;

	i2c_clk_khz = clk_get_rate(pd->clk) / 1000 / pd->clks_per_count;

	अगर (pd->bus_speed == I2C_MAX_STANDARD_MODE_FREQ) अणु
		tLOW	= 47;	/* tLOW = 4.7 us */
		tHIGH	= 40;	/* tHD;STA = tHIGH = 4.0 us */
		tf	= 3;	/* tf = 0.3 us */
	पूर्ण अन्यथा अगर (pd->bus_speed == I2C_MAX_FAST_MODE_FREQ) अणु
		tLOW	= 13;	/* tLOW = 1.3 us */
		tHIGH	= 6;	/* tHD;STA = tHIGH = 0.6 us */
		tf	= 3;	/* tf = 0.3 us */
	पूर्ण अन्यथा अणु
		dev_err(pd->dev, "unrecognized bus speed %lu Hz\n",
			pd->bus_speed);
		वापस -EINVAL;
	पूर्ण

	pd->iccl = sh_mobile_i2c_iccl(i2c_clk_khz, tLOW, tf);
	pd->icch = sh_mobile_i2c_icch(i2c_clk_khz, tHIGH, tf);

	वापस sh_mobile_i2c_check_timing(pd);
पूर्ण

अटल पूर्णांक sh_mobile_i2c_v2_init(काष्ठा sh_mobile_i2c_data *pd)
अणु
	अचिन्हित दीर्घ clks_per_cycle;

	/* L = 5, H = 4, L + H = 9 */
	clks_per_cycle = clk_get_rate(pd->clk) / pd->bus_speed;
	pd->iccl = DIV_ROUND_UP(clks_per_cycle * 5 / 9 - 1, pd->clks_per_count);
	pd->icch = DIV_ROUND_UP(clks_per_cycle * 4 / 9 - 5, pd->clks_per_count);

	वापस sh_mobile_i2c_check_timing(pd);
पूर्ण

अटल अचिन्हित अक्षर i2c_op(काष्ठा sh_mobile_i2c_data *pd, क्रमागत sh_mobile_i2c_op op)
अणु
	अचिन्हित अक्षर ret = 0;
	अचिन्हित दीर्घ flags;

	dev_dbg(pd->dev, "op %d\n", op);

	spin_lock_irqsave(&pd->lock, flags);

	चयन (op) अणु
	हाल OP_START: /* issue start and trigger DTE पूर्णांकerrupt */
		iic_wr(pd, ICCR, ICCR_ICE | ICCR_TRS | ICCR_BBSY);
		अवरोध;
	हाल OP_TX_FIRST: /* disable DTE पूर्णांकerrupt and ग_लिखो client address */
		iic_wr(pd, ICIC, ICIC_WAITE | ICIC_ALE | ICIC_TACKE);
		iic_wr(pd, ICDR, i2c_8bit_addr_from_msg(pd->msg));
		अवरोध;
	हाल OP_TX: /* ग_लिखो data */
		iic_wr(pd, ICDR, pd->msg->buf[pd->pos]);
		अवरोध;
	हाल OP_TX_STOP: /* issue a stop (or rep_start) */
		iic_wr(pd, ICCR, pd->send_stop ? ICCR_ICE | ICCR_TRS
					       : ICCR_ICE | ICCR_TRS | ICCR_BBSY);
		अवरोध;
	हाल OP_TX_TO_RX: /* select पढ़ो mode */
		iic_wr(pd, ICCR, ICCR_ICE | ICCR_SCP);
		अवरोध;
	हाल OP_RX: /* just पढ़ो data */
		ret = iic_rd(pd, ICDR);
		अवरोध;
	हाल OP_RX_STOP: /* enable DTE पूर्णांकerrupt, issue stop */
		अगर (!pd->atomic_xfer)
			iic_wr(pd, ICIC,
			       ICIC_DTEE | ICIC_WAITE | ICIC_ALE | ICIC_TACKE);
		iic_wr(pd, ICCR, ICCR_ICE | ICCR_RACK);
		अवरोध;
	हाल OP_RX_STOP_DATA: /* enable DTE पूर्णांकerrupt, पढ़ो data, issue stop */
		अगर (!pd->atomic_xfer)
			iic_wr(pd, ICIC,
			       ICIC_DTEE | ICIC_WAITE | ICIC_ALE | ICIC_TACKE);
		ret = iic_rd(pd, ICDR);
		iic_wr(pd, ICCR, ICCR_ICE | ICCR_RACK);
		अवरोध;
	पूर्ण

	spin_unlock_irqrestore(&pd->lock, flags);

	dev_dbg(pd->dev, "op %d, data out 0x%02x\n", op, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक sh_mobile_i2c_isr_tx(काष्ठा sh_mobile_i2c_data *pd)
अणु
	अगर (pd->pos == pd->msg->len) अणु
		i2c_op(pd, OP_TX_STOP);
		वापस 1;
	पूर्ण

	अगर (pd->pos == -1)
		i2c_op(pd, OP_TX_FIRST);
	अन्यथा
		i2c_op(pd, OP_TX);

	pd->pos++;
	वापस 0;
पूर्ण

अटल पूर्णांक sh_mobile_i2c_isr_rx(काष्ठा sh_mobile_i2c_data *pd)
अणु
	पूर्णांक real_pos;

	/* चयन from TX (address) to RX (data) adds two पूर्णांकerrupts */
	real_pos = pd->pos - 2;

	अगर (pd->pos == -1) अणु
		i2c_op(pd, OP_TX_FIRST);
	पूर्ण अन्यथा अगर (pd->pos == 0) अणु
		i2c_op(pd, OP_TX_TO_RX);
	पूर्ण अन्यथा अगर (pd->pos == pd->msg->len) अणु
		अगर (pd->stop_after_dma) अणु
			/* Simulate PIO end condition after DMA transfer */
			i2c_op(pd, OP_RX_STOP);
			pd->pos++;
			जाओ करोne;
		पूर्ण

		अगर (real_pos < 0)
			i2c_op(pd, OP_RX_STOP);
		अन्यथा
			pd->msg->buf[real_pos] = i2c_op(pd, OP_RX_STOP_DATA);
	पूर्ण अन्यथा अगर (real_pos >= 0) अणु
		pd->msg->buf[real_pos] = i2c_op(pd, OP_RX);
	पूर्ण

 करोne:
	pd->pos++;
	वापस pd->pos == (pd->msg->len + 2);
पूर्ण

अटल irqवापस_t sh_mobile_i2c_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sh_mobile_i2c_data *pd = dev_id;
	अचिन्हित अक्षर sr;
	पूर्णांक wakeup = 0;

	sr = iic_rd(pd, ICSR);
	pd->sr |= sr; /* remember state */

	dev_dbg(pd->dev, "i2c_isr 0x%02x 0x%02x %s %d %d!\n", sr, pd->sr,
	       (pd->msg->flags & I2C_M_RD) ? "read" : "write",
	       pd->pos, pd->msg->len);

	/* Kick off TxDMA after preface was करोne */
	अगर (pd->dma_direction == DMA_TO_DEVICE && pd->pos == 0)
		iic_set_clr(pd, ICIC, ICIC_TDMAE, 0);
	अन्यथा अगर (sr & (ICSR_AL | ICSR_TACK))
		/* करोn't पूर्णांकerrupt transaction - जारी to issue stop */
		iic_wr(pd, ICSR, sr & ~(ICSR_AL | ICSR_TACK));
	अन्यथा अगर (pd->msg->flags & I2C_M_RD)
		wakeup = sh_mobile_i2c_isr_rx(pd);
	अन्यथा
		wakeup = sh_mobile_i2c_isr_tx(pd);

	/* Kick off RxDMA after preface was करोne */
	अगर (pd->dma_direction == DMA_FROM_DEVICE && pd->pos == 1)
		iic_set_clr(pd, ICIC, ICIC_RDMAE, 0);

	अगर (sr & ICSR_WAIT) /* TODO: add delay here to support slow acks */
		iic_wr(pd, ICSR, sr & ~ICSR_WAIT);

	अगर (wakeup) अणु
		pd->sr |= SW_DONE;
		अगर (!pd->atomic_xfer)
			wake_up(&pd->रुको);
	पूर्ण

	/* defeat ग_लिखो posting to aव्योम spurious WAIT पूर्णांकerrupts */
	iic_rd(pd, ICSR);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम sh_mobile_i2c_dma_unmap(काष्ठा sh_mobile_i2c_data *pd)
अणु
	काष्ठा dma_chan *chan = pd->dma_direction == DMA_FROM_DEVICE
				? pd->dma_rx : pd->dma_tx;

	dma_unmap_single(chan->device->dev, sg_dma_address(&pd->sg),
			 pd->msg->len, pd->dma_direction);

	pd->dma_direction = DMA_NONE;
पूर्ण

अटल व्योम sh_mobile_i2c_cleanup_dma(काष्ठा sh_mobile_i2c_data *pd)
अणु
	अगर (pd->dma_direction == DMA_NONE)
		वापस;
	अन्यथा अगर (pd->dma_direction == DMA_FROM_DEVICE)
		dmaengine_terminate_all(pd->dma_rx);
	अन्यथा अगर (pd->dma_direction == DMA_TO_DEVICE)
		dmaengine_terminate_all(pd->dma_tx);

	sh_mobile_i2c_dma_unmap(pd);
पूर्ण

अटल व्योम sh_mobile_i2c_dma_callback(व्योम *data)
अणु
	काष्ठा sh_mobile_i2c_data *pd = data;

	sh_mobile_i2c_dma_unmap(pd);
	pd->pos = pd->msg->len;
	pd->stop_after_dma = true;

	iic_set_clr(pd, ICIC, 0, ICIC_TDMAE | ICIC_RDMAE);
पूर्ण

अटल काष्ठा dma_chan *sh_mobile_i2c_request_dma_chan(काष्ठा device *dev,
				क्रमागत dma_transfer_direction dir, dma_addr_t port_addr)
अणु
	काष्ठा dma_chan *chan;
	काष्ठा dma_slave_config cfg;
	अक्षर *chan_name = dir == DMA_MEM_TO_DEV ? "tx" : "rx";
	पूर्णांक ret;

	chan = dma_request_chan(dev, chan_name);
	अगर (IS_ERR(chan)) अणु
		dev_dbg(dev, "request_channel failed for %s (%ld)\n", chan_name,
			PTR_ERR(chan));
		वापस chan;
	पूर्ण

	स_रखो(&cfg, 0, माप(cfg));
	cfg.direction = dir;
	अगर (dir == DMA_MEM_TO_DEV) अणु
		cfg.dst_addr = port_addr;
		cfg.dst_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
	पूर्ण अन्यथा अणु
		cfg.src_addr = port_addr;
		cfg.src_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
	पूर्ण

	ret = dmaengine_slave_config(chan, &cfg);
	अगर (ret) अणु
		dev_dbg(dev, "slave_config failed for %s (%d)\n", chan_name, ret);
		dma_release_channel(chan);
		वापस ERR_PTR(ret);
	पूर्ण

	dev_dbg(dev, "got DMA channel for %s\n", chan_name);
	वापस chan;
पूर्ण

अटल व्योम sh_mobile_i2c_xfer_dma(काष्ठा sh_mobile_i2c_data *pd)
अणु
	bool पढ़ो = pd->msg->flags & I2C_M_RD;
	क्रमागत dma_data_direction dir = पढ़ो ? DMA_FROM_DEVICE : DMA_TO_DEVICE;
	काष्ठा dma_chan *chan = पढ़ो ? pd->dma_rx : pd->dma_tx;
	काष्ठा dma_async_tx_descriptor *txdesc;
	dma_addr_t dma_addr;
	dma_cookie_t cookie;

	अगर (PTR_ERR(chan) == -EPROBE_DEFER) अणु
		अगर (पढ़ो)
			chan = pd->dma_rx = sh_mobile_i2c_request_dma_chan(pd->dev, DMA_DEV_TO_MEM,
									   pd->res->start + ICDR);
		अन्यथा
			chan = pd->dma_tx = sh_mobile_i2c_request_dma_chan(pd->dev, DMA_MEM_TO_DEV,
									   pd->res->start + ICDR);
	पूर्ण

	अगर (IS_ERR(chan))
		वापस;

	dma_addr = dma_map_single(chan->device->dev, pd->dma_buf, pd->msg->len, dir);
	अगर (dma_mapping_error(chan->device->dev, dma_addr)) अणु
		dev_dbg(pd->dev, "dma map failed, using PIO\n");
		वापस;
	पूर्ण

	sg_dma_len(&pd->sg) = pd->msg->len;
	sg_dma_address(&pd->sg) = dma_addr;

	pd->dma_direction = dir;

	txdesc = dmaengine_prep_slave_sg(chan, &pd->sg, 1,
					 पढ़ो ? DMA_DEV_TO_MEM : DMA_MEM_TO_DEV,
					 DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	अगर (!txdesc) अणु
		dev_dbg(pd->dev, "dma prep slave sg failed, using PIO\n");
		sh_mobile_i2c_cleanup_dma(pd);
		वापस;
	पूर्ण

	txdesc->callback = sh_mobile_i2c_dma_callback;
	txdesc->callback_param = pd;

	cookie = dmaengine_submit(txdesc);
	अगर (dma_submit_error(cookie)) अणु
		dev_dbg(pd->dev, "submitting dma failed, using PIO\n");
		sh_mobile_i2c_cleanup_dma(pd);
		वापस;
	पूर्ण

	dma_async_issue_pending(chan);
पूर्ण

अटल व्योम start_ch(काष्ठा sh_mobile_i2c_data *pd, काष्ठा i2c_msg *usr_msg,
		     bool करो_init)
अणु
	अगर (करो_init) अणु
		/* Initialize channel रेजिस्टरs */
		iic_wr(pd, ICCR, ICCR_SCP);

		/* Enable channel and configure rx ack */
		iic_wr(pd, ICCR, ICCR_ICE | ICCR_SCP);

		/* Set the घड़ी */
		iic_wr(pd, ICCL, pd->iccl & 0xff);
		iic_wr(pd, ICCH, pd->icch & 0xff);
	पूर्ण

	pd->msg = usr_msg;
	pd->pos = -1;
	pd->sr = 0;

	अगर (pd->atomic_xfer)
		वापस;

	pd->dma_buf = i2c_get_dma_safe_msg_buf(pd->msg, 8);
	अगर (pd->dma_buf)
		sh_mobile_i2c_xfer_dma(pd);

	/* Enable all पूर्णांकerrupts to begin with */
	iic_wr(pd, ICIC, ICIC_DTEE | ICIC_WAITE | ICIC_ALE | ICIC_TACKE);
पूर्ण

अटल पूर्णांक poll_dte(काष्ठा sh_mobile_i2c_data *pd)
अणु
	पूर्णांक i;

	क्रम (i = 1000; i; i--) अणु
		u_पूर्णांक8_t val = iic_rd(pd, ICSR);

		अगर (val & ICSR_DTE)
			अवरोध;

		अगर (val & ICSR_TACK)
			वापस -ENXIO;

		udelay(10);
	पूर्ण

	वापस i ? 0 : -ETIMEDOUT;
पूर्ण

अटल पूर्णांक poll_busy(काष्ठा sh_mobile_i2c_data *pd)
अणु
	पूर्णांक i;

	क्रम (i = 1000; i; i--) अणु
		u_पूर्णांक8_t val = iic_rd(pd, ICSR);

		dev_dbg(pd->dev, "val 0x%02x pd->sr 0x%02x\n", val, pd->sr);

		/* the पूर्णांकerrupt handler may wake us up beक्रमe the
		 * transfer is finished, so poll the hardware
		 * until we're करोne.
		 */
		अगर (!(val & ICSR_BUSY)) अणु
			/* handle missing acknowledge and arbitration lost */
			val |= pd->sr;
			अगर (val & ICSR_TACK)
				वापस -ENXIO;
			अगर (val & ICSR_AL)
				वापस -EAGAIN;
			अवरोध;
		पूर्ण

		udelay(10);
	पूर्ण

	वापस i ? 0 : -ETIMEDOUT;
पूर्ण

अटल पूर्णांक sh_mobile_xfer(काष्ठा sh_mobile_i2c_data *pd,
			 काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	काष्ठा i2c_msg	*msg;
	पूर्णांक err = 0;
	पूर्णांक i;
	दीर्घ समय_left;

	/* Wake up device and enable घड़ी */
	pm_runसमय_get_sync(pd->dev);

	/* Process all messages */
	क्रम (i = 0; i < num; i++) अणु
		bool करो_start = pd->send_stop || !i;
		msg = &msgs[i];
		pd->send_stop = i == num - 1 || msg->flags & I2C_M_STOP;
		pd->stop_after_dma = false;

		start_ch(pd, msg, करो_start);

		अगर (करो_start)
			i2c_op(pd, OP_START);

		अगर (pd->atomic_xfer) अणु
			अचिन्हित दीर्घ j = jअगरfies + pd->adap.समयout;

			समय_left = समय_beक्रमe_eq(jअगरfies, j);
			जबतक (समय_left &&
			       !(pd->sr & (ICSR_TACK | SW_DONE))) अणु
				अचिन्हित अक्षर sr = iic_rd(pd, ICSR);

				अगर (sr & (ICSR_AL   | ICSR_TACK |
					  ICSR_WAIT | ICSR_DTE)) अणु
					sh_mobile_i2c_isr(0, pd);
					udelay(150);
				पूर्ण अन्यथा अणु
					cpu_relax();
				पूर्ण
				समय_left = समय_beक्रमe_eq(jअगरfies, j);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* The पूर्णांकerrupt handler takes care of the rest... */
			समय_left = रुको_event_समयout(pd->रुको,
					pd->sr & (ICSR_TACK | SW_DONE),
					pd->adap.समयout);

			/* 'stop_after_dma' tells अगर DMA xfer was complete */
			i2c_put_dma_safe_msg_buf(pd->dma_buf, pd->msg,
						 pd->stop_after_dma);
		पूर्ण

		अगर (!समय_left) अणु
			dev_err(pd->dev, "Transfer request timed out\n");
			अगर (pd->dma_direction != DMA_NONE)
				sh_mobile_i2c_cleanup_dma(pd);

			err = -ETIMEDOUT;
			अवरोध;
		पूर्ण

		अगर (pd->send_stop)
			err = poll_busy(pd);
		अन्यथा
			err = poll_dte(pd);
		अगर (err < 0)
			अवरोध;
	पूर्ण

	/* Disable channel */
	iic_wr(pd, ICCR, ICCR_SCP);

	/* Disable घड़ी and mark device as idle */
	pm_runसमय_put_sync(pd->dev);

	वापस err ?: num;
पूर्ण

अटल पूर्णांक sh_mobile_i2c_xfer(काष्ठा i2c_adapter *adapter,
			      काष्ठा i2c_msg *msgs,
			      पूर्णांक num)
अणु
	काष्ठा sh_mobile_i2c_data *pd = i2c_get_adapdata(adapter);

	pd->atomic_xfer = false;
	वापस sh_mobile_xfer(pd, msgs, num);
पूर्ण

अटल पूर्णांक sh_mobile_i2c_xfer_atomic(काष्ठा i2c_adapter *adapter,
				     काष्ठा i2c_msg *msgs,
				     पूर्णांक num)
अणु
	काष्ठा sh_mobile_i2c_data *pd = i2c_get_adapdata(adapter);

	pd->atomic_xfer = true;
	वापस sh_mobile_xfer(pd, msgs, num);
पूर्ण

अटल u32 sh_mobile_i2c_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL | I2C_FUNC_PROTOCOL_MANGLING;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm sh_mobile_i2c_algorithm = अणु
	.functionality = sh_mobile_i2c_func,
	.master_xfer = sh_mobile_i2c_xfer,
	.master_xfer_atomic = sh_mobile_i2c_xfer_atomic,
पूर्ण;

अटल स्थिर काष्ठा i2c_adapter_quirks sh_mobile_i2c_quirks = अणु
	.flags = I2C_AQ_NO_ZERO_LEN_READ,
पूर्ण;

/*
 * r8a7740 has an errata regarding I2C I/O pad reset needing this workaround.
 */
अटल पूर्णांक sh_mobile_i2c_r8a7740_workaround(काष्ठा sh_mobile_i2c_data *pd)
अणु
	iic_set_clr(pd, ICCR, ICCR_ICE, 0);
	iic_rd(pd, ICCR); /* dummy पढ़ो */

	iic_set_clr(pd, ICSTART, ICSTART_ICSTART, 0);
	iic_rd(pd, ICSTART); /* dummy पढ़ो */

	udelay(10);

	iic_wr(pd, ICCR, ICCR_SCP);
	iic_wr(pd, ICSTART, 0);

	udelay(10);

	iic_wr(pd, ICCR, ICCR_TRS);
	udelay(10);
	iic_wr(pd, ICCR, 0);
	udelay(10);
	iic_wr(pd, ICCR, ICCR_TRS);
	udelay(10);

	वापस sh_mobile_i2c_init(pd);
पूर्ण

अटल स्थिर काष्ठा sh_mobile_dt_config शेष_dt_config = अणु
	.clks_per_count = 1,
	.setup = sh_mobile_i2c_init,
पूर्ण;

अटल स्थिर काष्ठा sh_mobile_dt_config fast_घड़ी_dt_config = अणु
	.clks_per_count = 2,
	.setup = sh_mobile_i2c_init,
पूर्ण;

अटल स्थिर काष्ठा sh_mobile_dt_config v2_freq_calc_dt_config = अणु
	.clks_per_count = 2,
	.setup = sh_mobile_i2c_v2_init,
पूर्ण;

अटल स्थिर काष्ठा sh_mobile_dt_config r8a7740_dt_config = अणु
	.clks_per_count = 1,
	.setup = sh_mobile_i2c_r8a7740_workaround,
पूर्ण;

अटल स्थिर काष्ठा of_device_id sh_mobile_i2c_dt_ids[] = अणु
	अणु .compatible = "renesas,iic-r8a73a4", .data = &fast_घड़ी_dt_config पूर्ण,
	अणु .compatible = "renesas,iic-r8a7740", .data = &r8a7740_dt_config पूर्ण,
	अणु .compatible = "renesas,iic-r8a774c0", .data = &v2_freq_calc_dt_config पूर्ण,
	अणु .compatible = "renesas,iic-r8a7790", .data = &v2_freq_calc_dt_config पूर्ण,
	अणु .compatible = "renesas,iic-r8a7791", .data = &v2_freq_calc_dt_config पूर्ण,
	अणु .compatible = "renesas,iic-r8a7792", .data = &v2_freq_calc_dt_config पूर्ण,
	अणु .compatible = "renesas,iic-r8a7793", .data = &v2_freq_calc_dt_config पूर्ण,
	अणु .compatible = "renesas,iic-r8a7794", .data = &v2_freq_calc_dt_config पूर्ण,
	अणु .compatible = "renesas,iic-r8a7795", .data = &v2_freq_calc_dt_config पूर्ण,
	अणु .compatible = "renesas,iic-r8a77990", .data = &v2_freq_calc_dt_config पूर्ण,
	अणु .compatible = "renesas,iic-sh73a0", .data = &fast_घड़ी_dt_config पूर्ण,
	अणु .compatible = "renesas,rcar-gen2-iic", .data = &v2_freq_calc_dt_config पूर्ण,
	अणु .compatible = "renesas,rcar-gen3-iic", .data = &v2_freq_calc_dt_config पूर्ण,
	अणु .compatible = "renesas,rmobile-iic", .data = &शेष_dt_config पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sh_mobile_i2c_dt_ids);

अटल व्योम sh_mobile_i2c_release_dma(काष्ठा sh_mobile_i2c_data *pd)
अणु
	अगर (!IS_ERR(pd->dma_tx)) अणु
		dma_release_channel(pd->dma_tx);
		pd->dma_tx = ERR_PTR(-EPROBE_DEFER);
	पूर्ण

	अगर (!IS_ERR(pd->dma_rx)) अणु
		dma_release_channel(pd->dma_rx);
		pd->dma_rx = ERR_PTR(-EPROBE_DEFER);
	पूर्ण
पूर्ण

अटल पूर्णांक sh_mobile_i2c_hook_irqs(काष्ठा platक्रमm_device *dev, काष्ठा sh_mobile_i2c_data *pd)
अणु
	काष्ठा resource *res;
	resource_माप_प्रकार n;
	पूर्णांक k = 0, ret;

	जबतक ((res = platक्रमm_get_resource(dev, IORESOURCE_IRQ, k))) अणु
		क्रम (n = res->start; n <= res->end; n++) अणु
			ret = devm_request_irq(&dev->dev, n, sh_mobile_i2c_isr,
					  0, dev_name(&dev->dev), pd);
			अगर (ret) अणु
				dev_err(&dev->dev, "cannot request IRQ %pa\n", &n);
				वापस ret;
			पूर्ण
		पूर्ण
		k++;
	पूर्ण

	वापस k > 0 ? 0 : -ENOENT;
पूर्ण

अटल पूर्णांक sh_mobile_i2c_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा sh_mobile_i2c_data *pd;
	काष्ठा i2c_adapter *adap;
	काष्ठा resource *res;
	स्थिर काष्ठा sh_mobile_dt_config *config;
	पूर्णांक ret;
	u32 bus_speed;

	pd = devm_kzalloc(&dev->dev, माप(काष्ठा sh_mobile_i2c_data), GFP_KERNEL);
	अगर (!pd)
		वापस -ENOMEM;

	pd->clk = devm_clk_get(&dev->dev, शून्य);
	अगर (IS_ERR(pd->clk)) अणु
		dev_err(&dev->dev, "cannot get clock\n");
		वापस PTR_ERR(pd->clk);
	पूर्ण

	ret = sh_mobile_i2c_hook_irqs(dev, pd);
	अगर (ret)
		वापस ret;

	pd->dev = &dev->dev;
	platक्रमm_set_drvdata(dev, pd);

	res = platक्रमm_get_resource(dev, IORESOURCE_MEM, 0);

	pd->res = res;
	pd->reg = devm_ioremap_resource(&dev->dev, res);
	अगर (IS_ERR(pd->reg))
		वापस PTR_ERR(pd->reg);

	ret = of_property_पढ़ो_u32(dev->dev.of_node, "clock-frequency", &bus_speed);
	pd->bus_speed = (ret || !bus_speed) ? I2C_MAX_STANDARD_MODE_FREQ : bus_speed;
	pd->clks_per_count = 1;

	/* Newer variants come with two new bits in ICIC */
	अगर (resource_size(res) > 0x17)
		pd->flags |= IIC_FLAG_HAS_ICIC67;

	pm_runसमय_enable(&dev->dev);
	pm_runसमय_get_sync(&dev->dev);

	config = of_device_get_match_data(&dev->dev);
	अगर (config) अणु
		pd->clks_per_count = config->clks_per_count;
		ret = config->setup(pd);
	पूर्ण अन्यथा अणु
		ret = sh_mobile_i2c_init(pd);
	पूर्ण

	pm_runसमय_put_sync(&dev->dev);
	अगर (ret)
		वापस ret;

	/* Init DMA */
	sg_init_table(&pd->sg, 1);
	pd->dma_direction = DMA_NONE;
	pd->dma_rx = pd->dma_tx = ERR_PTR(-EPROBE_DEFER);

	/* setup the निजी data */
	adap = &pd->adap;
	i2c_set_adapdata(adap, pd);

	adap->owner = THIS_MODULE;
	adap->algo = &sh_mobile_i2c_algorithm;
	adap->quirks = &sh_mobile_i2c_quirks;
	adap->dev.parent = &dev->dev;
	adap->retries = 5;
	adap->nr = dev->id;
	adap->dev.of_node = dev->dev.of_node;

	strlcpy(adap->name, dev->name, माप(adap->name));

	spin_lock_init(&pd->lock);
	init_रुकोqueue_head(&pd->रुको);

	ret = i2c_add_numbered_adapter(adap);
	अगर (ret < 0) अणु
		sh_mobile_i2c_release_dma(pd);
		वापस ret;
	पूर्ण

	dev_info(&dev->dev, "I2C adapter %d, bus speed %lu Hz\n", adap->nr, pd->bus_speed);

	वापस 0;
पूर्ण

अटल पूर्णांक sh_mobile_i2c_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा sh_mobile_i2c_data *pd = platक्रमm_get_drvdata(dev);

	i2c_del_adapter(&pd->adap);
	sh_mobile_i2c_release_dma(pd);
	pm_runसमय_disable(&dev->dev);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक sh_mobile_i2c_suspend(काष्ठा device *dev)
अणु
	काष्ठा sh_mobile_i2c_data *pd = dev_get_drvdata(dev);

	i2c_mark_adapter_suspended(&pd->adap);
	वापस 0;
पूर्ण

अटल पूर्णांक sh_mobile_i2c_resume(काष्ठा device *dev)
अणु
	काष्ठा sh_mobile_i2c_data *pd = dev_get_drvdata(dev);

	i2c_mark_adapter_resumed(&pd->adap);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops sh_mobile_i2c_pm_ops = अणु
	SET_NOIRQ_SYSTEM_SLEEP_PM_OPS(sh_mobile_i2c_suspend,
				      sh_mobile_i2c_resume)
पूर्ण;

#घोषणा DEV_PM_OPS (&sh_mobile_i2c_pm_ops)
#अन्यथा
#घोषणा DEV_PM_OPS शून्य
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल काष्ठा platक्रमm_driver sh_mobile_i2c_driver = अणु
	.driver		= अणु
		.name		= "i2c-sh_mobile",
		.of_match_table = sh_mobile_i2c_dt_ids,
		.pm	= DEV_PM_OPS,
	पूर्ण,
	.probe		= sh_mobile_i2c_probe,
	.हटाओ		= sh_mobile_i2c_हटाओ,
पूर्ण;

अटल पूर्णांक __init sh_mobile_i2c_adap_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&sh_mobile_i2c_driver);
पूर्ण
subsys_initcall(sh_mobile_i2c_adap_init);

अटल व्योम __निकास sh_mobile_i2c_adap_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&sh_mobile_i2c_driver);
पूर्ण
module_निकास(sh_mobile_i2c_adap_निकास);

MODULE_DESCRIPTION("SuperH Mobile I2C Bus Controller driver");
MODULE_AUTHOR("Magnus Damm");
MODULE_AUTHOR("Wolfram Sang");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:i2c-sh_mobile");
