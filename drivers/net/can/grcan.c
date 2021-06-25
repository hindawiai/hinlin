<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Socket CAN driver क्रम Aeroflex Gaisler GRCAN and GRHCAN.
 *
 * 2012 (c) Aeroflex Gaisler AB
 *
 * This driver supports GRCAN and GRHCAN CAN controllers available in the GRLIB
 * VHDL IP core library.
 *
 * Full करोcumentation of the GRCAN core can be found here:
 * http://www.gaisler.com/products/grlib/grip.pdf
 *
 * See "Documentation/devicetree/bindings/net/can/grcan.txt" क्रम inक्रमmation on
 * खोलो firmware properties.
 *
 * See "Documentation/ABI/testing/sysfs-class-net-grcan" क्रम inक्रमmation on the
 * sysfs पूर्णांकerface.
 *
 * See "Documentation/admin-guide/kernel-parameters.rst" क्रम inक्रमmation on the module
 * parameters.
 *
 * Contributors: Andreas Larsson <andreas@gaisler.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/can/dev.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_irq.h>

#समावेश <linux/dma-mapping.h>

#घोषणा DRV_NAME	"grcan"

#घोषणा GRCAN_NAPI_WEIGHT	32

#घोषणा GRCAN_RESERVE_SIZE(slot1, slot2) (((slot2) - (slot1)) / 4 - 1)

काष्ठा grcan_रेजिस्टरs अणु
	u32 conf;	/* 0x00 */
	u32 stat;	/* 0x04 */
	u32 ctrl;	/* 0x08 */
	u32 __reserved1[GRCAN_RESERVE_SIZE(0x08, 0x18)];
	u32 smask;	/* 0x18 - CanMASK */
	u32 scode;	/* 0x1c - CanCODE */
	u32 __reserved2[GRCAN_RESERVE_SIZE(0x1c, 0x100)];
	u32 pimsr;	/* 0x100 */
	u32 pimr;	/* 0x104 */
	u32 pisr;	/* 0x108 */
	u32 pir;	/* 0x10C */
	u32 imr;	/* 0x110 */
	u32 picr;	/* 0x114 */
	u32 __reserved3[GRCAN_RESERVE_SIZE(0x114, 0x200)];
	u32 txctrl;	/* 0x200 */
	u32 txaddr;	/* 0x204 */
	u32 txsize;	/* 0x208 */
	u32 txwr;	/* 0x20C */
	u32 txrd;	/* 0x210 */
	u32 txirq;	/* 0x214 */
	u32 __reserved4[GRCAN_RESERVE_SIZE(0x214, 0x300)];
	u32 rxctrl;	/* 0x300 */
	u32 rxaddr;	/* 0x304 */
	u32 rxsize;	/* 0x308 */
	u32 rxwr;	/* 0x30C */
	u32 rxrd;	/* 0x310 */
	u32 rxirq;	/* 0x314 */
	u32 rxmask;	/* 0x318 */
	u32 rxcode;	/* 0x31C */
पूर्ण;

#घोषणा GRCAN_CONF_ABORT	0x00000001
#घोषणा GRCAN_CONF_ENABLE0	0x00000002
#घोषणा GRCAN_CONF_ENABLE1	0x00000004
#घोषणा GRCAN_CONF_SELECT	0x00000008
#घोषणा GRCAN_CONF_SILENT	0x00000010
#घोषणा GRCAN_CONF_SAM		0x00000020 /* Available in some hardware */
#घोषणा GRCAN_CONF_BPR		0x00000300 /* Note: not BRP */
#घोषणा GRCAN_CONF_RSJ		0x00007000
#घोषणा GRCAN_CONF_PS1		0x00f00000
#घोषणा GRCAN_CONF_PS2		0x000f0000
#घोषणा GRCAN_CONF_SCALER	0xff000000
#घोषणा GRCAN_CONF_OPERATION						\
	(GRCAN_CONF_ABORT | GRCAN_CONF_ENABLE0 | GRCAN_CONF_ENABLE1	\
	 | GRCAN_CONF_SELECT | GRCAN_CONF_SILENT | GRCAN_CONF_SAM)
#घोषणा GRCAN_CONF_TIMING						\
	(GRCAN_CONF_BPR | GRCAN_CONF_RSJ | GRCAN_CONF_PS1		\
	 | GRCAN_CONF_PS2 | GRCAN_CONF_SCALER)

#घोषणा GRCAN_CONF_RSJ_MIN	1
#घोषणा GRCAN_CONF_RSJ_MAX	4
#घोषणा GRCAN_CONF_PS1_MIN	1
#घोषणा GRCAN_CONF_PS1_MAX	15
#घोषणा GRCAN_CONF_PS2_MIN	2
#घोषणा GRCAN_CONF_PS2_MAX	8
#घोषणा GRCAN_CONF_SCALER_MIN	0
#घोषणा GRCAN_CONF_SCALER_MAX	255
#घोषणा GRCAN_CONF_SCALER_INC	1

#घोषणा GRCAN_CONF_BPR_BIT	8
#घोषणा GRCAN_CONF_RSJ_BIT	12
#घोषणा GRCAN_CONF_PS1_BIT	20
#घोषणा GRCAN_CONF_PS2_BIT	16
#घोषणा GRCAN_CONF_SCALER_BIT	24

#घोषणा GRCAN_STAT_PASS		0x000001
#घोषणा GRCAN_STAT_OFF		0x000002
#घोषणा GRCAN_STAT_OR		0x000004
#घोषणा GRCAN_STAT_AHBERR	0x000008
#घोषणा GRCAN_STAT_ACTIVE	0x000010
#घोषणा GRCAN_STAT_RXERRCNT	0x00ff00
#घोषणा GRCAN_STAT_TXERRCNT	0xff0000

#घोषणा GRCAN_STAT_ERRCTR_RELATED	(GRCAN_STAT_PASS | GRCAN_STAT_OFF)

#घोषणा GRCAN_STAT_RXERRCNT_BIT	8
#घोषणा GRCAN_STAT_TXERRCNT_BIT	16

#घोषणा GRCAN_STAT_ERRCNT_WARNING_LIMIT	96
#घोषणा GRCAN_STAT_ERRCNT_PASSIVE_LIMIT	127

#घोषणा GRCAN_CTRL_RESET	0x2
#घोषणा GRCAN_CTRL_ENABLE	0x1

#घोषणा GRCAN_TXCTRL_ENABLE	0x1
#घोषणा GRCAN_TXCTRL_ONGOING	0x2
#घोषणा GRCAN_TXCTRL_SINGLE	0x4

#घोषणा GRCAN_RXCTRL_ENABLE	0x1
#घोषणा GRCAN_RXCTRL_ONGOING	0x2

/* Relative offset of IRQ sources to AMBA Plug&Play */
#घोषणा GRCAN_IRQIX_IRQ		0
#घोषणा GRCAN_IRQIX_TXSYNC	1
#घोषणा GRCAN_IRQIX_RXSYNC	2

#घोषणा GRCAN_IRQ_PASS		0x00001
#घोषणा GRCAN_IRQ_OFF		0x00002
#घोषणा GRCAN_IRQ_OR		0x00004
#घोषणा GRCAN_IRQ_RXAHBERR	0x00008
#घोषणा GRCAN_IRQ_TXAHBERR	0x00010
#घोषणा GRCAN_IRQ_RXIRQ		0x00020
#घोषणा GRCAN_IRQ_TXIRQ		0x00040
#घोषणा GRCAN_IRQ_RXFULL	0x00080
#घोषणा GRCAN_IRQ_TXEMPTY	0x00100
#घोषणा GRCAN_IRQ_RX		0x00200
#घोषणा GRCAN_IRQ_TX		0x00400
#घोषणा GRCAN_IRQ_RXSYNC	0x00800
#घोषणा GRCAN_IRQ_TXSYNC	0x01000
#घोषणा GRCAN_IRQ_RXERRCTR	0x02000
#घोषणा GRCAN_IRQ_TXERRCTR	0x04000
#घोषणा GRCAN_IRQ_RXMISS	0x08000
#घोषणा GRCAN_IRQ_TXLOSS	0x10000

#घोषणा GRCAN_IRQ_NONE	0
#घोषणा GRCAN_IRQ_ALL							\
	(GRCAN_IRQ_PASS | GRCAN_IRQ_OFF | GRCAN_IRQ_OR			\
	 | GRCAN_IRQ_RXAHBERR | GRCAN_IRQ_TXAHBERR			\
	 | GRCAN_IRQ_RXIRQ | GRCAN_IRQ_TXIRQ				\
	 | GRCAN_IRQ_RXFULL | GRCAN_IRQ_TXEMPTY				\
	 | GRCAN_IRQ_RX | GRCAN_IRQ_TX | GRCAN_IRQ_RXSYNC		\
	 | GRCAN_IRQ_TXSYNC | GRCAN_IRQ_RXERRCTR			\
	 | GRCAN_IRQ_TXERRCTR | GRCAN_IRQ_RXMISS			\
	 | GRCAN_IRQ_TXLOSS)

#घोषणा GRCAN_IRQ_ERRCTR_RELATED (GRCAN_IRQ_RXERRCTR | GRCAN_IRQ_TXERRCTR \
				  | GRCAN_IRQ_PASS | GRCAN_IRQ_OFF)
#घोषणा GRCAN_IRQ_ERRORS (GRCAN_IRQ_ERRCTR_RELATED | GRCAN_IRQ_OR	\
			  | GRCAN_IRQ_TXAHBERR | GRCAN_IRQ_RXAHBERR	\
			  | GRCAN_IRQ_TXLOSS)
#घोषणा GRCAN_IRQ_DEFAULT (GRCAN_IRQ_RX | GRCAN_IRQ_TX | GRCAN_IRQ_ERRORS)

#घोषणा GRCAN_MSG_SIZE		16

#घोषणा GRCAN_MSG_IDE		0x80000000
#घोषणा GRCAN_MSG_RTR		0x40000000
#घोषणा GRCAN_MSG_BID		0x1ffc0000
#घोषणा GRCAN_MSG_EID		0x1fffffff
#घोषणा GRCAN_MSG_IDE_BIT	31
#घोषणा GRCAN_MSG_RTR_BIT	30
#घोषणा GRCAN_MSG_BID_BIT	18
#घोषणा GRCAN_MSG_EID_BIT	0

#घोषणा GRCAN_MSG_DLC		0xf0000000
#घोषणा GRCAN_MSG_TXERRC	0x00ff0000
#घोषणा GRCAN_MSG_RXERRC	0x0000ff00
#घोषणा GRCAN_MSG_DLC_BIT	28
#घोषणा GRCAN_MSG_TXERRC_BIT	16
#घोषणा GRCAN_MSG_RXERRC_BIT	8
#घोषणा GRCAN_MSG_AHBERR	0x00000008
#घोषणा GRCAN_MSG_OR		0x00000004
#घोषणा GRCAN_MSG_OFF		0x00000002
#घोषणा GRCAN_MSG_PASS		0x00000001

#घोषणा GRCAN_MSG_DATA_SLOT_INDEX(i) (2 + (i) / 4)
#घोषणा GRCAN_MSG_DATA_SHIFT(i) ((3 - (i) % 4) * 8)

#घोषणा GRCAN_BUFFER_ALIGNMENT		1024
#घोषणा GRCAN_DEFAULT_BUFFER_SIZE	1024
#घोषणा GRCAN_VALID_TR_SIZE_MASK	0x001fffc0

#घोषणा GRCAN_INVALID_BUFFER_SIZE(s)			\
	((s) == 0 || ((s) & ~GRCAN_VALID_TR_SIZE_MASK))

#अगर GRCAN_INVALID_BUFFER_SIZE(GRCAN_DEFAULT_BUFFER_SIZE)
#त्रुटि "Invalid default buffer size"
#पूर्ण_अगर

काष्ठा grcan_dma_buffer अणु
	माप_प्रकार size;
	व्योम *buf;
	dma_addr_t handle;
पूर्ण;

काष्ठा grcan_dma अणु
	माप_प्रकार base_size;
	व्योम *base_buf;
	dma_addr_t base_handle;
	काष्ठा grcan_dma_buffer tx;
	काष्ठा grcan_dma_buffer rx;
पूर्ण;

/* GRCAN configuration parameters */
काष्ठा grcan_device_config अणु
	अचिन्हित लघु enable0;
	अचिन्हित लघु enable1;
	अचिन्हित लघु select;
	अचिन्हित पूर्णांक txsize;
	अचिन्हित पूर्णांक rxsize;
पूर्ण;

#घोषणा GRCAN_DEFAULT_DEVICE_CONFIG अणु				\
		.enable0	= 0,				\
		.enable1	= 0,				\
		.select		= 0,				\
		.txsize		= GRCAN_DEFAULT_BUFFER_SIZE,	\
		.rxsize		= GRCAN_DEFAULT_BUFFER_SIZE,	\
		पूर्ण

#घोषणा GRCAN_TXBUG_SAFE_GRLIB_VERSION	0x4100
#घोषणा GRLIB_VERSION_MASK		0xffff

/* GRCAN निजी data काष्ठाure */
काष्ठा grcan_priv अणु
	काष्ठा can_priv can;	/* must be the first member */
	काष्ठा net_device *dev;
	काष्ठा napi_काष्ठा napi;

	काष्ठा grcan_रेजिस्टरs __iomem *regs;	/* ioremap'ed रेजिस्टरs */
	काष्ठा grcan_device_config config;
	काष्ठा grcan_dma dma;

	काष्ठा sk_buff **echo_skb;	/* We allocate this on our own */
	u8 *txdlc;			/* Length of queued frames */

	/* The echo skb poपूर्णांकer, poपूर्णांकing पूर्णांकo echo_skb and indicating which
	 * frames can be echoed back. See the "Notes on the tx cyclic buffer
	 * handling"-comment क्रम grcan_start_xmit क्रम more details.
	 */
	u32 eskbp;

	/* Lock क्रम controlling changes to the netअगर tx queue state, accesses to
	 * the echo_skb poपूर्णांकer eskbp and क्रम making sure that a running reset
	 * and/or a बंद of the पूर्णांकerface is करोne without पूर्णांकerference from
	 * other parts of the code.
	 *
	 * The echo_skb poपूर्णांकer, eskbp, should only be accessed under this lock
	 * as it can be changed in several places and together with decisions on
	 * whether to wake up the tx queue.
	 *
	 * The tx queue must never be woken up अगर there is a running reset or
	 * बंद in progress.
	 *
	 * A running reset (see below on need_txbug_workaround) should never be
	 * करोne अगर the पूर्णांकerface is closing करोwn and several running resets
	 * should never be scheduled simultaneously.
	 */
	spinlock_t lock;

	/* Whether a workaround is needed due to a bug in older hardware. In
	 * this हाल, the driver both tries to prevent the bug from being
	 * triggered and recovers, अगर the bug nevertheless happens, by करोing a
	 * running reset. A running reset, resets the device and जारीs from
	 * where it were without being noticeable from outside the driver (apart
	 * from slight delays).
	 */
	bool need_txbug_workaround;

	/* To trigger initization of running reset and to trigger running reset
	 * respectively in the हाल of a hanged device due to a txbug.
	 */
	काष्ठा समयr_list hang_समयr;
	काष्ठा समयr_list rr_समयr;

	/* To aव्योम waking up the netअगर queue and restarting समयrs
	 * when a reset is scheduled or when closing of the device is
	 * undergoing
	 */
	bool resetting;
	bool closing;
पूर्ण;

/* Wait समय क्रम a लघु रुको क्रम ongoing to clear */
#घोषणा GRCAN_SHORTWAIT_USECS	10

/* Limit on the number of transmitted bits of an eff frame according to the CAN
 * specअगरication: 1 bit start of frame, 32 bits arbitration field, 6 bits
 * control field, 8 bytes data field, 16 bits crc field, 2 bits ACK field and 7
 * bits end of frame
 */
#घोषणा GRCAN_EFF_FRAME_MAX_BITS	(1+32+6+8*8+16+2+7)

#अगर defined(__BIG_ENDIAN)
अटल अंतरभूत u32 grcan_पढ़ो_reg(u32 __iomem *reg)
अणु
	वापस ioपढ़ो32be(reg);
पूर्ण

अटल अंतरभूत व्योम grcan_ग_लिखो_reg(u32 __iomem *reg, u32 val)
अणु
	ioग_लिखो32be(val, reg);
पूर्ण
#अन्यथा
अटल अंतरभूत u32 grcan_पढ़ो_reg(u32 __iomem *reg)
अणु
	वापस ioपढ़ो32(reg);
पूर्ण

अटल अंतरभूत व्योम grcan_ग_लिखो_reg(u32 __iomem *reg, u32 val)
अणु
	ioग_लिखो32(val, reg);
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम grcan_clear_bits(u32 __iomem *reg, u32 mask)
अणु
	grcan_ग_लिखो_reg(reg, grcan_पढ़ो_reg(reg) & ~mask);
पूर्ण

अटल अंतरभूत व्योम grcan_set_bits(u32 __iomem *reg, u32 mask)
अणु
	grcan_ग_लिखो_reg(reg, grcan_पढ़ो_reg(reg) | mask);
पूर्ण

अटल अंतरभूत u32 grcan_पढ़ो_bits(u32 __iomem *reg, u32 mask)
अणु
	वापस grcan_पढ़ो_reg(reg) & mask;
पूर्ण

अटल अंतरभूत व्योम grcan_ग_लिखो_bits(u32 __iomem *reg, u32 value, u32 mask)
अणु
	u32 old = grcan_पढ़ो_reg(reg);

	grcan_ग_लिखो_reg(reg, (old & ~mask) | (value & mask));
पूर्ण

/* a and b should both be in [0,size] and a == b == size should not hold */
अटल अंतरभूत u32 grcan_ring_add(u32 a, u32 b, u32 size)
अणु
	u32 sum = a + b;

	अगर (sum < size)
		वापस sum;
	अन्यथा
		वापस sum - size;
पूर्ण

/* a and b should both be in [0,size) */
अटल अंतरभूत u32 grcan_ring_sub(u32 a, u32 b, u32 size)
अणु
	वापस grcan_ring_add(a, size - b, size);
पूर्ण

/* Available slots क्रम new transmissions */
अटल अंतरभूत u32 grcan_txspace(माप_प्रकार txsize, u32 txwr, u32 eskbp)
अणु
	u32 slots = txsize / GRCAN_MSG_SIZE - 1;
	u32 used = grcan_ring_sub(txwr, eskbp, txsize) / GRCAN_MSG_SIZE;

	वापस slots - used;
पूर्ण

/* Configuration parameters that can be set via module parameters */
अटल काष्ठा grcan_device_config grcan_module_config =
	GRCAN_DEFAULT_DEVICE_CONFIG;

अटल स्थिर काष्ठा can_bittiming_स्थिर grcan_bittiming_स्थिर = अणु
	.name		= DRV_NAME,
	.tseg1_min	= GRCAN_CONF_PS1_MIN + 1,
	.tseg1_max	= GRCAN_CONF_PS1_MAX + 1,
	.tseg2_min	= GRCAN_CONF_PS2_MIN,
	.tseg2_max	= GRCAN_CONF_PS2_MAX,
	.sjw_max	= GRCAN_CONF_RSJ_MAX,
	.brp_min	= GRCAN_CONF_SCALER_MIN + 1,
	.brp_max	= GRCAN_CONF_SCALER_MAX + 1,
	.brp_inc	= GRCAN_CONF_SCALER_INC,
पूर्ण;

अटल पूर्णांक grcan_set_bittiming(काष्ठा net_device *dev)
अणु
	काष्ठा grcan_priv *priv = netdev_priv(dev);
	काष्ठा grcan_रेजिस्टरs __iomem *regs = priv->regs;
	काष्ठा can_bittiming *bt = &priv->can.bittiming;
	u32 timing = 0;
	पूर्णांक bpr, rsj, ps1, ps2, scaler;

	/* Should never happen - function will not be called when
	 * device is up
	 */
	अगर (grcan_पढ़ो_bits(&regs->ctrl, GRCAN_CTRL_ENABLE))
		वापस -EBUSY;

	bpr = 0; /* Note bpr and brp are dअगरferent concepts */
	rsj = bt->sjw;
	ps1 = (bt->prop_seg + bt->phase_seg1) - 1; /* tseg1 - 1 */
	ps2 = bt->phase_seg2;
	scaler = (bt->brp - 1);
	netdev_dbg(dev, "Request for BPR=%d, RSJ=%d, PS1=%d, PS2=%d, SCALER=%d",
		   bpr, rsj, ps1, ps2, scaler);
	अगर (!(ps1 > ps2)) अणु
		netdev_err(dev, "PS1 > PS2 must hold: PS1=%d, PS2=%d\n",
			   ps1, ps2);
		वापस -EINVAL;
	पूर्ण
	अगर (!(ps2 >= rsj)) अणु
		netdev_err(dev, "PS2 >= RSJ must hold: PS2=%d, RSJ=%d\n",
			   ps2, rsj);
		वापस -EINVAL;
	पूर्ण

	timing |= (bpr << GRCAN_CONF_BPR_BIT) & GRCAN_CONF_BPR;
	timing |= (rsj << GRCAN_CONF_RSJ_BIT) & GRCAN_CONF_RSJ;
	timing |= (ps1 << GRCAN_CONF_PS1_BIT) & GRCAN_CONF_PS1;
	timing |= (ps2 << GRCAN_CONF_PS2_BIT) & GRCAN_CONF_PS2;
	timing |= (scaler << GRCAN_CONF_SCALER_BIT) & GRCAN_CONF_SCALER;
	netdev_info(dev, "setting timing=0x%x\n", timing);
	grcan_ग_लिखो_bits(&regs->conf, timing, GRCAN_CONF_TIMING);

	वापस 0;
पूर्ण

अटल पूर्णांक grcan_get_berr_counter(स्थिर काष्ठा net_device *dev,
				  काष्ठा can_berr_counter *bec)
अणु
	काष्ठा grcan_priv *priv = netdev_priv(dev);
	काष्ठा grcan_रेजिस्टरs __iomem *regs = priv->regs;
	u32 status = grcan_पढ़ो_reg(&regs->stat);

	bec->txerr = (status & GRCAN_STAT_TXERRCNT) >> GRCAN_STAT_TXERRCNT_BIT;
	bec->rxerr = (status & GRCAN_STAT_RXERRCNT) >> GRCAN_STAT_RXERRCNT_BIT;
	वापस 0;
पूर्ण

अटल पूर्णांक grcan_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget);

/* Reset device, but keep configuration inक्रमmation */
अटल व्योम grcan_reset(काष्ठा net_device *dev)
अणु
	काष्ठा grcan_priv *priv = netdev_priv(dev);
	काष्ठा grcan_रेजिस्टरs __iomem *regs = priv->regs;
	u32 config = grcan_पढ़ो_reg(&regs->conf);

	grcan_set_bits(&regs->ctrl, GRCAN_CTRL_RESET);
	grcan_ग_लिखो_reg(&regs->conf, config);

	priv->eskbp = grcan_पढ़ो_reg(&regs->txrd);
	priv->can.state = CAN_STATE_STOPPED;

	/* Turn off hardware filtering - regs->rxcode set to 0 by reset */
	grcan_ग_लिखो_reg(&regs->rxmask, 0);
पूर्ण

/* stop device without changing any configurations */
अटल व्योम grcan_stop_hardware(काष्ठा net_device *dev)
अणु
	काष्ठा grcan_priv *priv = netdev_priv(dev);
	काष्ठा grcan_रेजिस्टरs __iomem *regs = priv->regs;

	grcan_ग_लिखो_reg(&regs->imr, GRCAN_IRQ_NONE);
	grcan_clear_bits(&regs->txctrl, GRCAN_TXCTRL_ENABLE);
	grcan_clear_bits(&regs->rxctrl, GRCAN_RXCTRL_ENABLE);
	grcan_clear_bits(&regs->ctrl, GRCAN_CTRL_ENABLE);
पूर्ण

/* Let priv->eskbp catch up to regs->txrd and echo back the skbs अगर echo
 * is true and मुक्त them otherwise.
 *
 * If budget is >= 0, stop after handling at most budget skbs. Otherwise,
 * जारी until priv->eskbp catches up to regs->txrd.
 *
 * priv->lock *must* be held when calling this function
 */
अटल पूर्णांक catch_up_echo_skb(काष्ठा net_device *dev, पूर्णांक budget, bool echo)
अणु
	काष्ठा grcan_priv *priv = netdev_priv(dev);
	काष्ठा grcan_रेजिस्टरs __iomem *regs = priv->regs;
	काष्ठा grcan_dma *dma = &priv->dma;
	काष्ठा net_device_stats *stats = &dev->stats;
	पूर्णांक i, work_करोne;

	/* Updates to priv->eskbp and wake-ups of the queue needs to
	 * be atomic towards the पढ़ोs of priv->eskbp and shut-करोwns
	 * of the queue in grcan_start_xmit.
	 */
	u32 txrd = grcan_पढ़ो_reg(&regs->txrd);

	क्रम (work_करोne = 0; work_करोne < budget || budget < 0; work_करोne++) अणु
		अगर (priv->eskbp == txrd)
			अवरोध;
		i = priv->eskbp / GRCAN_MSG_SIZE;
		अगर (echo) अणु
			/* Normal echo of messages */
			stats->tx_packets++;
			stats->tx_bytes += priv->txdlc[i];
			priv->txdlc[i] = 0;
			can_get_echo_skb(dev, i, शून्य);
		पूर्ण अन्यथा अणु
			/* For cleanup of untransmitted messages */
			can_मुक्त_echo_skb(dev, i, शून्य);
		पूर्ण

		priv->eskbp = grcan_ring_add(priv->eskbp, GRCAN_MSG_SIZE,
					     dma->tx.size);
		txrd = grcan_पढ़ो_reg(&regs->txrd);
	पूर्ण
	वापस work_करोne;
पूर्ण

अटल व्योम grcan_lost_one_shot_frame(काष्ठा net_device *dev)
अणु
	काष्ठा grcan_priv *priv = netdev_priv(dev);
	काष्ठा grcan_रेजिस्टरs __iomem *regs = priv->regs;
	काष्ठा grcan_dma *dma = &priv->dma;
	u32 txrd;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->lock, flags);

	catch_up_echo_skb(dev, -1, true);

	अगर (unlikely(grcan_पढ़ो_bits(&regs->txctrl, GRCAN_TXCTRL_ENABLE))) अणु
		/* Should never happen */
		netdev_err(dev, "TXCTRL enabled at TXLOSS in one shot mode\n");
	पूर्ण अन्यथा अणु
		/* By the समय an GRCAN_IRQ_TXLOSS is generated in
		 * one-shot mode there is no problem in writing
		 * to TXRD even in versions of the hardware in
		 * which GRCAN_TXCTRL_ONGOING is not cleared properly
		 * in one-shot mode.
		 */

		/* Skip message and discard echo-skb */
		txrd = grcan_पढ़ो_reg(&regs->txrd);
		txrd = grcan_ring_add(txrd, GRCAN_MSG_SIZE, dma->tx.size);
		grcan_ग_लिखो_reg(&regs->txrd, txrd);
		catch_up_echo_skb(dev, -1, false);

		अगर (!priv->resetting && !priv->closing &&
		    !(priv->can.ctrlmode & CAN_CTRLMODE_LISTENONLY)) अणु
			netअगर_wake_queue(dev);
			grcan_set_bits(&regs->txctrl, GRCAN_TXCTRL_ENABLE);
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&priv->lock, flags);
पूर्ण

अटल व्योम grcan_err(काष्ठा net_device *dev, u32 sources, u32 status)
अणु
	काष्ठा grcan_priv *priv = netdev_priv(dev);
	काष्ठा grcan_रेजिस्टरs __iomem *regs = priv->regs;
	काष्ठा grcan_dma *dma = &priv->dma;
	काष्ठा net_device_stats *stats = &dev->stats;
	काष्ठा can_frame cf;

	/* Zero potential error_frame */
	स_रखो(&cf, 0, माप(cf));

	/* Message lost पूर्णांकerrupt. This might be due to arbitration error, but
	 * is also triggered when there is no one अन्यथा on the can bus or when
	 * there is a problem with the hardware पूर्णांकerface or the bus itself. As
	 * arbitration errors can not be singled out, no error frames are
	 * generated reporting this event as an arbitration error.
	 */
	अगर (sources & GRCAN_IRQ_TXLOSS) अणु
		/* Take care of failed one-shot transmit */
		अगर (priv->can.ctrlmode & CAN_CTRLMODE_ONE_SHOT)
			grcan_lost_one_shot_frame(dev);

		/* Stop prपूर्णांकing as soon as error passive or bus off is in
		 * effect to limit the amount of txloss debug prपूर्णांकouts.
		 */
		अगर (!(status & GRCAN_STAT_ERRCTR_RELATED)) अणु
			netdev_dbg(dev, "tx message lost\n");
			stats->tx_errors++;
		पूर्ण
	पूर्ण

	/* Conditions dealing with the error counters. There is no पूर्णांकerrupt क्रम
	 * error warning, but there are पूर्णांकerrupts क्रम increases of the error
	 * counters.
	 */
	अगर ((sources & GRCAN_IRQ_ERRCTR_RELATED) ||
	    (status & GRCAN_STAT_ERRCTR_RELATED)) अणु
		क्रमागत can_state state = priv->can.state;
		क्रमागत can_state oldstate = state;
		u32 txerr = (status & GRCAN_STAT_TXERRCNT)
			>> GRCAN_STAT_TXERRCNT_BIT;
		u32 rxerr = (status & GRCAN_STAT_RXERRCNT)
			>> GRCAN_STAT_RXERRCNT_BIT;

		/* Figure out current state */
		अगर (status & GRCAN_STAT_OFF) अणु
			state = CAN_STATE_BUS_OFF;
		पूर्ण अन्यथा अगर (status & GRCAN_STAT_PASS) अणु
			state = CAN_STATE_ERROR_PASSIVE;
		पूर्ण अन्यथा अगर (txerr >= GRCAN_STAT_ERRCNT_WARNING_LIMIT ||
			   rxerr >= GRCAN_STAT_ERRCNT_WARNING_LIMIT) अणु
			state = CAN_STATE_ERROR_WARNING;
		पूर्ण अन्यथा अणु
			state = CAN_STATE_ERROR_ACTIVE;
		पूर्ण

		/* Handle and report state changes */
		अगर (state != oldstate) अणु
			चयन (state) अणु
			हाल CAN_STATE_BUS_OFF:
				netdev_dbg(dev, "bus-off\n");
				netअगर_carrier_off(dev);
				priv->can.can_stats.bus_off++;

				/* Prevent the hardware from recovering from bus
				 * off on its own अगर restart is disabled.
				 */
				अगर (!priv->can.restart_ms)
					grcan_stop_hardware(dev);

				cf.can_id |= CAN_ERR_BUSOFF;
				अवरोध;

			हाल CAN_STATE_ERROR_PASSIVE:
				netdev_dbg(dev, "Error passive condition\n");
				priv->can.can_stats.error_passive++;

				cf.can_id |= CAN_ERR_CRTL;
				अगर (txerr >= GRCAN_STAT_ERRCNT_PASSIVE_LIMIT)
					cf.data[1] |= CAN_ERR_CRTL_TX_PASSIVE;
				अगर (rxerr >= GRCAN_STAT_ERRCNT_PASSIVE_LIMIT)
					cf.data[1] |= CAN_ERR_CRTL_RX_PASSIVE;
				अवरोध;

			हाल CAN_STATE_ERROR_WARNING:
				netdev_dbg(dev, "Error warning condition\n");
				priv->can.can_stats.error_warning++;

				cf.can_id |= CAN_ERR_CRTL;
				अगर (txerr >= GRCAN_STAT_ERRCNT_WARNING_LIMIT)
					cf.data[1] |= CAN_ERR_CRTL_TX_WARNING;
				अगर (rxerr >= GRCAN_STAT_ERRCNT_WARNING_LIMIT)
					cf.data[1] |= CAN_ERR_CRTL_RX_WARNING;
				अवरोध;

			हाल CAN_STATE_ERROR_ACTIVE:
				netdev_dbg(dev, "Error active condition\n");
				cf.can_id |= CAN_ERR_CRTL;
				अवरोध;

			शेष:
				/* There are no others at this poपूर्णांक */
				अवरोध;
			पूर्ण
			cf.data[6] = txerr;
			cf.data[7] = rxerr;
			priv->can.state = state;
		पूर्ण

		/* Report स्वतःmatic restarts */
		अगर (priv->can.restart_ms && oldstate == CAN_STATE_BUS_OFF) अणु
			अचिन्हित दीर्घ flags;

			cf.can_id |= CAN_ERR_RESTARTED;
			netdev_dbg(dev, "restarted\n");
			priv->can.can_stats.restarts++;
			netअगर_carrier_on(dev);

			spin_lock_irqsave(&priv->lock, flags);

			अगर (!priv->resetting && !priv->closing) अणु
				u32 txwr = grcan_पढ़ो_reg(&regs->txwr);

				अगर (grcan_txspace(dma->tx.size, txwr,
						  priv->eskbp))
					netअगर_wake_queue(dev);
			पूर्ण

			spin_unlock_irqrestore(&priv->lock, flags);
		पूर्ण
	पूर्ण

	/* Data overrun पूर्णांकerrupt */
	अगर ((sources & GRCAN_IRQ_OR) || (status & GRCAN_STAT_OR)) अणु
		netdev_dbg(dev, "got data overrun interrupt\n");
		stats->rx_over_errors++;
		stats->rx_errors++;

		cf.can_id |= CAN_ERR_CRTL;
		cf.data[1] |= CAN_ERR_CRTL_RX_OVERFLOW;
	पूर्ण

	/* AHB bus error पूर्णांकerrupts (not CAN bus errors) - shut करोwn the
	 * device.
	 */
	अगर (sources & (GRCAN_IRQ_TXAHBERR | GRCAN_IRQ_RXAHBERR) ||
	    (status & GRCAN_STAT_AHBERR)) अणु
		अक्षर *txrx = "";
		अचिन्हित दीर्घ flags;

		अगर (sources & GRCAN_IRQ_TXAHBERR) अणु
			txrx = "on tx ";
			stats->tx_errors++;
		पूर्ण अन्यथा अगर (sources & GRCAN_IRQ_RXAHBERR) अणु
			txrx = "on rx ";
			stats->rx_errors++;
		पूर्ण
		netdev_err(dev, "Fatal AHB bus error %s- halting device\n",
			   txrx);

		spin_lock_irqsave(&priv->lock, flags);

		/* Prevent anything to be enabled again and halt device */
		priv->closing = true;
		netअगर_stop_queue(dev);
		grcan_stop_hardware(dev);
		priv->can.state = CAN_STATE_STOPPED;

		spin_unlock_irqrestore(&priv->lock, flags);
	पूर्ण

	/* Pass on error frame अगर something to report,
	 * i.e. id contains some inक्रमmation
	 */
	अगर (cf.can_id) अणु
		काष्ठा can_frame *skb_cf;
		काष्ठा sk_buff *skb = alloc_can_err_skb(dev, &skb_cf);

		अगर (skb == शून्य) अणु
			netdev_dbg(dev, "could not allocate error frame\n");
			वापस;
		पूर्ण
		skb_cf->can_id |= cf.can_id;
		स_नकल(skb_cf->data, cf.data, माप(cf.data));

		netअगर_rx(skb);
	पूर्ण
पूर्ण

अटल irqवापस_t grcan_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	काष्ठा grcan_priv *priv = netdev_priv(dev);
	काष्ठा grcan_रेजिस्टरs __iomem *regs = priv->regs;
	u32 sources, status;

	/* Find out the source */
	sources = grcan_पढ़ो_reg(&regs->pimsr);
	अगर (!sources)
		वापस IRQ_NONE;
	grcan_ग_लिखो_reg(&regs->picr, sources);
	status = grcan_पढ़ो_reg(&regs->stat);

	/* If we got TX progress, the device has not hanged,
	 * so disable the hang समयr
	 */
	अगर (priv->need_txbug_workaround &&
	    (sources & (GRCAN_IRQ_TX | GRCAN_IRQ_TXLOSS))) अणु
		del_समयr(&priv->hang_समयr);
	पूर्ण

	/* Frame(s) received or transmitted */
	अगर (sources & (GRCAN_IRQ_TX | GRCAN_IRQ_RX)) अणु
		/* Disable tx/rx पूर्णांकerrupts and schedule poll(). No need क्रम
		 * locking as पूर्णांकerference from a running reset at worst leads
		 * to an extra पूर्णांकerrupt.
		 */
		grcan_clear_bits(&regs->imr, GRCAN_IRQ_TX | GRCAN_IRQ_RX);
		napi_schedule(&priv->napi);
	पूर्ण

	/* (Potential) error conditions to take care of */
	अगर (sources & GRCAN_IRQ_ERRORS)
		grcan_err(dev, sources, status);

	वापस IRQ_HANDLED;
पूर्ण

/* Reset device and restart operations from where they were.
 *
 * This assumes that RXCTRL & RXCTRL is properly disabled and that RX
 * is not ONGOING (TX might be stuck in ONGOING due to a harwrware bug
 * क्रम single shot)
 */
अटल व्योम grcan_running_reset(काष्ठा समयr_list *t)
अणु
	काष्ठा grcan_priv *priv = from_समयr(priv, t, rr_समयr);
	काष्ठा net_device *dev = priv->dev;
	काष्ठा grcan_रेजिस्टरs __iomem *regs = priv->regs;
	अचिन्हित दीर्घ flags;

	/* This temporarily messes with eskbp, so we need to lock
	 * priv->lock
	 */
	spin_lock_irqsave(&priv->lock, flags);

	priv->resetting = false;
	del_समयr(&priv->hang_समयr);
	del_समयr(&priv->rr_समयr);

	अगर (!priv->closing) अणु
		/* Save and reset - config रेजिस्टर preserved by grcan_reset */
		u32 imr = grcan_पढ़ो_reg(&regs->imr);

		u32 txaddr = grcan_पढ़ो_reg(&regs->txaddr);
		u32 txsize = grcan_पढ़ो_reg(&regs->txsize);
		u32 txwr = grcan_पढ़ो_reg(&regs->txwr);
		u32 txrd = grcan_पढ़ो_reg(&regs->txrd);
		u32 eskbp = priv->eskbp;

		u32 rxaddr = grcan_पढ़ो_reg(&regs->rxaddr);
		u32 rxsize = grcan_पढ़ो_reg(&regs->rxsize);
		u32 rxwr = grcan_पढ़ो_reg(&regs->rxwr);
		u32 rxrd = grcan_पढ़ो_reg(&regs->rxrd);

		grcan_reset(dev);

		/* Restore */
		grcan_ग_लिखो_reg(&regs->txaddr, txaddr);
		grcan_ग_लिखो_reg(&regs->txsize, txsize);
		grcan_ग_लिखो_reg(&regs->txwr, txwr);
		grcan_ग_लिखो_reg(&regs->txrd, txrd);
		priv->eskbp = eskbp;

		grcan_ग_लिखो_reg(&regs->rxaddr, rxaddr);
		grcan_ग_लिखो_reg(&regs->rxsize, rxsize);
		grcan_ग_लिखो_reg(&regs->rxwr, rxwr);
		grcan_ग_लिखो_reg(&regs->rxrd, rxrd);

		/* Turn on device again */
		grcan_ग_लिखो_reg(&regs->imr, imr);
		priv->can.state = CAN_STATE_ERROR_ACTIVE;
		grcan_ग_लिखो_reg(&regs->txctrl, GRCAN_TXCTRL_ENABLE
				| (priv->can.ctrlmode & CAN_CTRLMODE_ONE_SHOT
				   ? GRCAN_TXCTRL_SINGLE : 0));
		grcan_ग_लिखो_reg(&regs->rxctrl, GRCAN_RXCTRL_ENABLE);
		grcan_ग_लिखो_reg(&regs->ctrl, GRCAN_CTRL_ENABLE);

		/* Start queue अगर there is size and listen-onle mode is not
		 * enabled
		 */
		अगर (grcan_txspace(priv->dma.tx.size, txwr, priv->eskbp) &&
		    !(priv->can.ctrlmode & CAN_CTRLMODE_LISTENONLY))
			netअगर_wake_queue(dev);
	पूर्ण

	spin_unlock_irqrestore(&priv->lock, flags);

	netdev_err(dev, "Device reset and restored\n");
पूर्ण

/* Waiting समय in usecs corresponding to the transmission of three maximum
 * sized can frames in the given bitrate (in bits/sec). Waiting क्रम this amount
 * of समय makes sure that the can controller have समय to finish sending or
 * receiving a frame with a good margin.
 *
 * usecs/sec * number of frames * bits/frame / bits/sec
 */
अटल अंतरभूत u32 grcan_ongoing_रुको_usecs(__u32 bitrate)
अणु
	वापस 1000000 * 3 * GRCAN_EFF_FRAME_MAX_BITS / bitrate;
पूर्ण

/* Set समयr so that it will not fire until after a period in which the can
 * controller have a good margin to finish transmitting a frame unless it has
 * hanged
 */
अटल अंतरभूत व्योम grcan_reset_समयr(काष्ठा समयr_list *समयr, __u32 bitrate)
अणु
	u32 रुको_jअगरfies = usecs_to_jअगरfies(grcan_ongoing_रुको_usecs(bitrate));

	mod_समयr(समयr, jअगरfies + रुको_jअगरfies);
पूर्ण

/* Disable channels and schedule a running reset */
अटल व्योम grcan_initiate_running_reset(काष्ठा समयr_list *t)
अणु
	काष्ठा grcan_priv *priv = from_समयr(priv, t, hang_समयr);
	काष्ठा net_device *dev = priv->dev;
	काष्ठा grcan_रेजिस्टरs __iomem *regs = priv->regs;
	अचिन्हित दीर्घ flags;

	netdev_err(dev, "Device seems hanged - reset scheduled\n");

	spin_lock_irqsave(&priv->lock, flags);

	/* The मुख्य body of this function must never be executed again
	 * until after an execution of grcan_running_reset
	 */
	अगर (!priv->resetting && !priv->closing) अणु
		priv->resetting = true;
		netअगर_stop_queue(dev);
		grcan_clear_bits(&regs->txctrl, GRCAN_TXCTRL_ENABLE);
		grcan_clear_bits(&regs->rxctrl, GRCAN_RXCTRL_ENABLE);
		grcan_reset_समयr(&priv->rr_समयr, priv->can.bittiming.bitrate);
	पूर्ण

	spin_unlock_irqrestore(&priv->lock, flags);
पूर्ण

अटल व्योम grcan_मुक्त_dma_buffers(काष्ठा net_device *dev)
अणु
	काष्ठा grcan_priv *priv = netdev_priv(dev);
	काष्ठा grcan_dma *dma = &priv->dma;

	dma_मुक्त_coherent(&dev->dev, dma->base_size, dma->base_buf,
			  dma->base_handle);
	स_रखो(dma, 0, माप(*dma));
पूर्ण

अटल पूर्णांक grcan_allocate_dma_buffers(काष्ठा net_device *dev,
				      माप_प्रकार tsize, माप_प्रकार rsize)
अणु
	काष्ठा grcan_priv *priv = netdev_priv(dev);
	काष्ठा grcan_dma *dma = &priv->dma;
	काष्ठा grcan_dma_buffer *large = rsize > tsize ? &dma->rx : &dma->tx;
	काष्ठा grcan_dma_buffer *small = rsize > tsize ? &dma->tx : &dma->rx;
	माप_प्रकार shअगरt;

	/* Need a whole number of GRCAN_BUFFER_ALIGNMENT क्रम the large,
	 * i.e. first buffer
	 */
	माप_प्रकार maxs = max(tsize, rsize);
	माप_प्रकार lsize = ALIGN(maxs, GRCAN_BUFFER_ALIGNMENT);

	/* Put the small buffer after that */
	माप_प्रकार ssize = min(tsize, rsize);

	/* Extra GRCAN_BUFFER_ALIGNMENT to allow क्रम alignment */
	dma->base_size = lsize + ssize + GRCAN_BUFFER_ALIGNMENT;
	dma->base_buf = dma_alloc_coherent(&dev->dev,
					   dma->base_size,
					   &dma->base_handle,
					   GFP_KERNEL);

	अगर (!dma->base_buf)
		वापस -ENOMEM;

	dma->tx.size = tsize;
	dma->rx.size = rsize;

	large->handle = ALIGN(dma->base_handle, GRCAN_BUFFER_ALIGNMENT);
	small->handle = large->handle + lsize;
	shअगरt = large->handle - dma->base_handle;

	large->buf = dma->base_buf + shअगरt;
	small->buf = large->buf + lsize;

	वापस 0;
पूर्ण

/* priv->lock *must* be held when calling this function */
अटल पूर्णांक grcan_start(काष्ठा net_device *dev)
अणु
	काष्ठा grcan_priv *priv = netdev_priv(dev);
	काष्ठा grcan_रेजिस्टरs __iomem *regs = priv->regs;
	u32 confop, txctrl;

	grcan_reset(dev);

	grcan_ग_लिखो_reg(&regs->txaddr, priv->dma.tx.handle);
	grcan_ग_लिखो_reg(&regs->txsize, priv->dma.tx.size);
	/* regs->txwr, regs->txrd and priv->eskbp alपढ़ोy set to 0 by reset */

	grcan_ग_लिखो_reg(&regs->rxaddr, priv->dma.rx.handle);
	grcan_ग_लिखो_reg(&regs->rxsize, priv->dma.rx.size);
	/* regs->rxwr and regs->rxrd alपढ़ोy set to 0 by reset */

	/* Enable पूर्णांकerrupts */
	grcan_पढ़ो_reg(&regs->pir);
	grcan_ग_लिखो_reg(&regs->imr, GRCAN_IRQ_DEFAULT);

	/* Enable पूर्णांकerfaces, channels and device */
	confop = GRCAN_CONF_ABORT
		| (priv->config.enable0 ? GRCAN_CONF_ENABLE0 : 0)
		| (priv->config.enable1 ? GRCAN_CONF_ENABLE1 : 0)
		| (priv->config.select ? GRCAN_CONF_SELECT : 0)
		| (priv->can.ctrlmode & CAN_CTRLMODE_LISTENONLY ?
		   GRCAN_CONF_SILENT : 0)
		| (priv->can.ctrlmode & CAN_CTRLMODE_3_SAMPLES ?
		   GRCAN_CONF_SAM : 0);
	grcan_ग_लिखो_bits(&regs->conf, confop, GRCAN_CONF_OPERATION);
	txctrl = GRCAN_TXCTRL_ENABLE
		| (priv->can.ctrlmode & CAN_CTRLMODE_ONE_SHOT
		   ? GRCAN_TXCTRL_SINGLE : 0);
	grcan_ग_लिखो_reg(&regs->txctrl, txctrl);
	grcan_ग_लिखो_reg(&regs->rxctrl, GRCAN_RXCTRL_ENABLE);
	grcan_ग_लिखो_reg(&regs->ctrl, GRCAN_CTRL_ENABLE);

	priv->can.state = CAN_STATE_ERROR_ACTIVE;

	वापस 0;
पूर्ण

अटल पूर्णांक grcan_set_mode(काष्ठा net_device *dev, क्रमागत can_mode mode)
अणु
	काष्ठा grcan_priv *priv = netdev_priv(dev);
	अचिन्हित दीर्घ flags;
	पूर्णांक err = 0;

	अगर (mode == CAN_MODE_START) अणु
		/* This might be called to restart the device to recover from
		 * bus off errors
		 */
		spin_lock_irqsave(&priv->lock, flags);
		अगर (priv->closing || priv->resetting) अणु
			err = -EBUSY;
		पूर्ण अन्यथा अणु
			netdev_info(dev, "Restarting device\n");
			grcan_start(dev);
			अगर (!(priv->can.ctrlmode & CAN_CTRLMODE_LISTENONLY))
				netअगर_wake_queue(dev);
		पूर्ण
		spin_unlock_irqrestore(&priv->lock, flags);
		वापस err;
	पूर्ण
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक grcan_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा grcan_priv *priv = netdev_priv(dev);
	काष्ठा grcan_dma *dma = &priv->dma;
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	/* Allocate memory */
	err = grcan_allocate_dma_buffers(dev, priv->config.txsize,
					 priv->config.rxsize);
	अगर (err) अणु
		netdev_err(dev, "could not allocate DMA buffers\n");
		वापस err;
	पूर्ण

	priv->echo_skb = kसुस्मृति(dma->tx.size, माप(*priv->echo_skb),
				 GFP_KERNEL);
	अगर (!priv->echo_skb) अणु
		err = -ENOMEM;
		जाओ निकास_मुक्त_dma_buffers;
	पूर्ण
	priv->can.echo_skb_max = dma->tx.size;
	priv->can.echo_skb = priv->echo_skb;

	priv->txdlc = kसुस्मृति(dma->tx.size, माप(*priv->txdlc), GFP_KERNEL);
	अगर (!priv->txdlc) अणु
		err = -ENOMEM;
		जाओ निकास_मुक्त_echo_skb;
	पूर्ण

	/* Get can device up */
	err = खोलो_candev(dev);
	अगर (err)
		जाओ निकास_मुक्त_txdlc;

	err = request_irq(dev->irq, grcan_पूर्णांकerrupt, IRQF_SHARED,
			  dev->name, dev);
	अगर (err)
		जाओ निकास_बंद_candev;

	spin_lock_irqsave(&priv->lock, flags);

	napi_enable(&priv->napi);
	grcan_start(dev);
	अगर (!(priv->can.ctrlmode & CAN_CTRLMODE_LISTENONLY))
		netअगर_start_queue(dev);
	priv->resetting = false;
	priv->closing = false;

	spin_unlock_irqrestore(&priv->lock, flags);

	वापस 0;

निकास_बंद_candev:
	बंद_candev(dev);
निकास_मुक्त_txdlc:
	kमुक्त(priv->txdlc);
निकास_मुक्त_echo_skb:
	kमुक्त(priv->echo_skb);
निकास_मुक्त_dma_buffers:
	grcan_मुक्त_dma_buffers(dev);
	वापस err;
पूर्ण

अटल पूर्णांक grcan_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा grcan_priv *priv = netdev_priv(dev);
	अचिन्हित दीर्घ flags;

	napi_disable(&priv->napi);

	spin_lock_irqsave(&priv->lock, flags);

	priv->closing = true;
	अगर (priv->need_txbug_workaround) अणु
		del_समयr_sync(&priv->hang_समयr);
		del_समयr_sync(&priv->rr_समयr);
	पूर्ण
	netअगर_stop_queue(dev);
	grcan_stop_hardware(dev);
	priv->can.state = CAN_STATE_STOPPED;

	spin_unlock_irqrestore(&priv->lock, flags);

	मुक्त_irq(dev->irq, dev);
	बंद_candev(dev);

	grcan_मुक्त_dma_buffers(dev);
	priv->can.echo_skb_max = 0;
	priv->can.echo_skb = शून्य;
	kमुक्त(priv->echo_skb);
	kमुक्त(priv->txdlc);

	वापस 0;
पूर्ण

अटल पूर्णांक grcan_transmit_catch_up(काष्ठा net_device *dev, पूर्णांक budget)
अणु
	काष्ठा grcan_priv *priv = netdev_priv(dev);
	अचिन्हित दीर्घ flags;
	पूर्णांक work_करोne;

	spin_lock_irqsave(&priv->lock, flags);

	work_करोne = catch_up_echo_skb(dev, budget, true);
	अगर (work_करोne) अणु
		अगर (!priv->resetting && !priv->closing &&
		    !(priv->can.ctrlmode & CAN_CTRLMODE_LISTENONLY))
			netअगर_wake_queue(dev);

		/* With napi we करोn't get TX पूर्णांकerrupts क्रम a जबतक,
		 * so prevent a running reset जबतक catching up
		 */
		अगर (priv->need_txbug_workaround)
			del_समयr(&priv->hang_समयr);
	पूर्ण

	spin_unlock_irqrestore(&priv->lock, flags);

	वापस work_करोne;
पूर्ण

अटल पूर्णांक grcan_receive(काष्ठा net_device *dev, पूर्णांक budget)
अणु
	काष्ठा grcan_priv *priv = netdev_priv(dev);
	काष्ठा grcan_रेजिस्टरs __iomem *regs = priv->regs;
	काष्ठा grcan_dma *dma = &priv->dma;
	काष्ठा net_device_stats *stats = &dev->stats;
	काष्ठा can_frame *cf;
	काष्ठा sk_buff *skb;
	u32 wr, rd, startrd;
	u32 *slot;
	u32 i, rtr, eff, j, shअगरt;
	पूर्णांक work_करोne = 0;

	rd = grcan_पढ़ो_reg(&regs->rxrd);
	startrd = rd;
	क्रम (work_करोne = 0; work_करोne < budget; work_करोne++) अणु
		/* Check क्रम packet to receive */
		wr = grcan_पढ़ो_reg(&regs->rxwr);
		अगर (rd == wr)
			अवरोध;

		/* Take care of packet */
		skb = alloc_can_skb(dev, &cf);
		अगर (skb == शून्य) अणु
			netdev_err(dev,
				   "dropping frame: skb allocation failed\n");
			stats->rx_dropped++;
			जारी;
		पूर्ण

		slot = dma->rx.buf + rd;
		eff = slot[0] & GRCAN_MSG_IDE;
		rtr = slot[0] & GRCAN_MSG_RTR;
		अगर (eff) अणु
			cf->can_id = ((slot[0] & GRCAN_MSG_EID)
				      >> GRCAN_MSG_EID_BIT);
			cf->can_id |= CAN_EFF_FLAG;
		पूर्ण अन्यथा अणु
			cf->can_id = ((slot[0] & GRCAN_MSG_BID)
				      >> GRCAN_MSG_BID_BIT);
		पूर्ण
		cf->len = can_cc_dlc2len((slot[1] & GRCAN_MSG_DLC)
					  >> GRCAN_MSG_DLC_BIT);
		अगर (rtr) अणु
			cf->can_id |= CAN_RTR_FLAG;
		पूर्ण अन्यथा अणु
			क्रम (i = 0; i < cf->len; i++) अणु
				j = GRCAN_MSG_DATA_SLOT_INDEX(i);
				shअगरt = GRCAN_MSG_DATA_SHIFT(i);
				cf->data[i] = (u8)(slot[j] >> shअगरt);
			पूर्ण
		पूर्ण

		/* Update statistics and पढ़ो poपूर्णांकer */
		stats->rx_packets++;
		stats->rx_bytes += cf->len;
		netअगर_receive_skb(skb);

		rd = grcan_ring_add(rd, GRCAN_MSG_SIZE, dma->rx.size);
	पूर्ण

	/* Make sure everything is पढ़ो beक्रमe allowing hardware to
	 * use the memory
	 */
	mb();

	/* Update पढ़ो poपूर्णांकer - no need to check क्रम ongoing */
	अगर (likely(rd != startrd))
		grcan_ग_लिखो_reg(&regs->rxrd, rd);

	वापस work_करोne;
पूर्ण

अटल पूर्णांक grcan_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा grcan_priv *priv = container_of(napi, काष्ठा grcan_priv, napi);
	काष्ठा net_device *dev = priv->dev;
	काष्ठा grcan_रेजिस्टरs __iomem *regs = priv->regs;
	अचिन्हित दीर्घ flags;
	पूर्णांक tx_work_करोne, rx_work_करोne;
	पूर्णांक rx_budget = budget / 2;
	पूर्णांक tx_budget = budget - rx_budget;

	/* Half of the budget क्रम receiving messages */
	rx_work_करोne = grcan_receive(dev, rx_budget);

	/* Half of the budget क्रम transmitting messages as that can trigger echo
	 * frames being received
	 */
	tx_work_करोne = grcan_transmit_catch_up(dev, tx_budget);

	अगर (rx_work_करोne < rx_budget && tx_work_करोne < tx_budget) अणु
		napi_complete(napi);

		/* Guarantee no पूर्णांकerference with a running reset that otherwise
		 * could turn off पूर्णांकerrupts.
		 */
		spin_lock_irqsave(&priv->lock, flags);

		/* Enable tx and rx पूर्णांकerrupts again. No need to check
		 * priv->closing as napi_disable in grcan_बंद is रुकोing क्रम
		 * scheduled napi calls to finish.
		 */
		grcan_set_bits(&regs->imr, GRCAN_IRQ_TX | GRCAN_IRQ_RX);

		spin_unlock_irqrestore(&priv->lock, flags);
	पूर्ण

	वापस rx_work_करोne + tx_work_करोne;
पूर्ण

/* Work tx bug by रुकोing जबतक क्रम the risky situation to clear. If that fails,
 * drop a frame in one-shot mode or indicate a busy device otherwise.
 *
 * Returns 0 on successful रुको. Otherwise it sets *netdev_tx_status to the
 * value that should be वापसed by grcan_start_xmit when पातing the xmit.
 */
अटल पूर्णांक grcan_txbug_workaround(काष्ठा net_device *dev, काष्ठा sk_buff *skb,
				  u32 txwr, u32 oneshoपंचांगode,
				  netdev_tx_t *netdev_tx_status)
अणु
	काष्ठा grcan_priv *priv = netdev_priv(dev);
	काष्ठा grcan_रेजिस्टरs __iomem *regs = priv->regs;
	काष्ठा grcan_dma *dma = &priv->dma;
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	/* Wait a जबतक क्रम ongoing to be cleared or पढ़ो poपूर्णांकer to catch up to
	 * ग_लिखो poपूर्णांकer. The latter is needed due to a bug in older versions of
	 * GRCAN in which ONGOING is not cleared properly one-shot mode when a
	 * transmission fails.
	 */
	क्रम (i = 0; i < GRCAN_SHORTWAIT_USECS; i++) अणु
		udelay(1);
		अगर (!grcan_पढ़ो_bits(&regs->txctrl, GRCAN_TXCTRL_ONGOING) ||
		    grcan_पढ़ो_reg(&regs->txrd) == txwr) अणु
			वापस 0;
		पूर्ण
	पूर्ण

	/* Clean up, in हाल the situation was not resolved */
	spin_lock_irqsave(&priv->lock, flags);
	अगर (!priv->resetting && !priv->closing) अणु
		/* Queue might have been stopped earlier in grcan_start_xmit */
		अगर (grcan_txspace(dma->tx.size, txwr, priv->eskbp))
			netअगर_wake_queue(dev);
		/* Set a समयr to resolve a hanged tx controller */
		अगर (!समयr_pending(&priv->hang_समयr))
			grcan_reset_समयr(&priv->hang_समयr,
					  priv->can.bittiming.bitrate);
	पूर्ण
	spin_unlock_irqrestore(&priv->lock, flags);

	अगर (oneshoपंचांगode) अणु
		/* In one-shot mode we should never end up here because
		 * then the पूर्णांकerrupt handler increases txrd on TXLOSS,
		 * but it is consistent with one-shot mode to drop the
		 * frame in this हाल.
		 */
		kमुक्त_skb(skb);
		*netdev_tx_status = NETDEV_TX_OK;
	पूर्ण अन्यथा अणु
		/* In normal mode the socket-can transmission queue get
		 * to keep the frame so that it can be retransmitted
		 * later
		 */
		*netdev_tx_status = NETDEV_TX_BUSY;
	पूर्ण
	वापस -EBUSY;
पूर्ण

/* Notes on the tx cyclic buffer handling:
 *
 * regs->txwr	- the next slot क्रम the driver to put data to be sent
 * regs->txrd	- the next slot क्रम the device to पढ़ो data
 * priv->eskbp	- the next slot क्रम the driver to call can_put_echo_skb क्रम
 *
 * grcan_start_xmit can enter more messages as दीर्घ as regs->txwr करोes
 * not reach priv->eskbp (within 1 message gap)
 *
 * The device sends messages until regs->txrd reaches regs->txwr
 *
 * The पूर्णांकerrupt calls handler calls can_put_echo_skb until
 * priv->eskbp reaches regs->txrd
 */
अटल netdev_tx_t grcan_start_xmit(काष्ठा sk_buff *skb,
				    काष्ठा net_device *dev)
अणु
	काष्ठा grcan_priv *priv = netdev_priv(dev);
	काष्ठा grcan_रेजिस्टरs __iomem *regs = priv->regs;
	काष्ठा grcan_dma *dma = &priv->dma;
	काष्ठा can_frame *cf = (काष्ठा can_frame *)skb->data;
	u32 id, txwr, txrd, space, txctrl;
	पूर्णांक slotindex;
	u32 *slot;
	u32 i, rtr, eff, dlc, पंचांगp, err;
	पूर्णांक j, shअगरt;
	अचिन्हित दीर्घ flags;
	u32 oneshoपंचांगode = priv->can.ctrlmode & CAN_CTRLMODE_ONE_SHOT;

	अगर (can_dropped_invalid_skb(dev, skb))
		वापस NETDEV_TX_OK;

	/* Trying to transmit in silent mode will generate error पूर्णांकerrupts, but
	 * this should never happen - the queue should not have been started.
	 */
	अगर (priv->can.ctrlmode & CAN_CTRLMODE_LISTENONLY)
		वापस NETDEV_TX_BUSY;

	/* Reads of priv->eskbp and shut-करोwns of the queue needs to
	 * be atomic towards the updates to priv->eskbp and wake-ups
	 * of the queue in the पूर्णांकerrupt handler.
	 */
	spin_lock_irqsave(&priv->lock, flags);

	txwr = grcan_पढ़ो_reg(&regs->txwr);
	space = grcan_txspace(dma->tx.size, txwr, priv->eskbp);

	slotindex = txwr / GRCAN_MSG_SIZE;
	slot = dma->tx.buf + txwr;

	अगर (unlikely(space == 1))
		netअगर_stop_queue(dev);

	spin_unlock_irqrestore(&priv->lock, flags);
	/* End of critical section*/

	/* This should never happen. If circular buffer is full, the
	 * netअगर_stop_queue should have been stopped alपढ़ोy.
	 */
	अगर (unlikely(!space)) अणु
		netdev_err(dev, "No buffer space, but queue is non-stopped.\n");
		वापस NETDEV_TX_BUSY;
	पूर्ण

	/* Convert and ग_लिखो CAN message to DMA buffer */
	eff = cf->can_id & CAN_EFF_FLAG;
	rtr = cf->can_id & CAN_RTR_FLAG;
	id = cf->can_id & (eff ? CAN_EFF_MASK : CAN_SFF_MASK);
	dlc = cf->len;
	अगर (eff)
		पंचांगp = (id << GRCAN_MSG_EID_BIT) & GRCAN_MSG_EID;
	अन्यथा
		पंचांगp = (id << GRCAN_MSG_BID_BIT) & GRCAN_MSG_BID;
	slot[0] = (eff ? GRCAN_MSG_IDE : 0) | (rtr ? GRCAN_MSG_RTR : 0) | पंचांगp;

	slot[1] = ((dlc << GRCAN_MSG_DLC_BIT) & GRCAN_MSG_DLC);
	slot[2] = 0;
	slot[3] = 0;
	क्रम (i = 0; i < dlc; i++) अणु
		j = GRCAN_MSG_DATA_SLOT_INDEX(i);
		shअगरt = GRCAN_MSG_DATA_SHIFT(i);
		slot[j] |= cf->data[i] << shअगरt;
	पूर्ण

	/* Checking that channel has not been disabled. These हालs
	 * should never happen
	 */
	txctrl = grcan_पढ़ो_reg(&regs->txctrl);
	अगर (!(txctrl & GRCAN_TXCTRL_ENABLE))
		netdev_err(dev, "tx channel spuriously disabled\n");

	अगर (oneshoपंचांगode && !(txctrl & GRCAN_TXCTRL_SINGLE))
		netdev_err(dev, "one-shot mode spuriously disabled\n");

	/* Bug workaround क्रम old version of grcan where updating txwr
	 * in the same घड़ी cycle as the controller updates txrd to
	 * the current txwr could hang the can controller
	 */
	अगर (priv->need_txbug_workaround) अणु
		txrd = grcan_पढ़ो_reg(&regs->txrd);
		अगर (unlikely(grcan_ring_sub(txwr, txrd, dma->tx.size) == 1)) अणु
			netdev_tx_t txstatus;

			err = grcan_txbug_workaround(dev, skb, txwr,
						     oneshoपंचांगode, &txstatus);
			अगर (err)
				वापस txstatus;
		पूर्ण
	पूर्ण

	/* Prepare skb क्रम echoing. This must be after the bug workaround above
	 * as ownership of the skb is passed on by calling can_put_echo_skb.
	 * Returning NETDEV_TX_BUSY or accessing skb or cf after a call to
	 * can_put_echo_skb would be an error unless other measures are
	 * taken.
	 */
	priv->txdlc[slotindex] = cf->len; /* Store dlc क्रम statistics */
	can_put_echo_skb(skb, dev, slotindex, 0);

	/* Make sure everything is written beक्रमe allowing hardware to
	 * पढ़ो from the memory
	 */
	wmb();

	/* Update ग_लिखो poपूर्णांकer to start transmission */
	grcan_ग_लिखो_reg(&regs->txwr,
			grcan_ring_add(txwr, GRCAN_MSG_SIZE, dma->tx.size));

	वापस NETDEV_TX_OK;
पूर्ण

/* ========== Setting up sysfs पूर्णांकerface and module parameters ========== */

#घोषणा GRCAN_NOT_BOOL(अचिन्हित_val) ((अचिन्हित_val) > 1)

#घोषणा GRCAN_MODULE_PARAM(name, mtype, valcheckf, desc)		\
	अटल व्योम grcan_sanitize_##name(काष्ठा platक्रमm_device *pd)	\
	अणु								\
		काष्ठा grcan_device_config grcan_शेष_config		\
			= GRCAN_DEFAULT_DEVICE_CONFIG;			\
		अगर (valcheckf(grcan_module_config.name)) अणु		\
			dev_err(&pd->dev,				\
				"Invalid module parameter value for "	\
				#name " - setting default\n");		\
			grcan_module_config.name =			\
				grcan_शेष_config.name;		\
		पूर्ण							\
	पूर्ण								\
	module_param_named(name, grcan_module_config.name,		\
			   mtype, 0444);				\
	MODULE_PARM_DESC(name, desc)

#घोषणा GRCAN_CONFIG_ATTR(name, desc)					\
	अटल sमाप_प्रकार grcan_store_##name(काष्ठा device *sdev,		\
					  काष्ठा device_attribute *att,	\
					  स्थिर अक्षर *buf,		\
					  माप_प्रकार count)			\
	अणु								\
		काष्ठा net_device *dev = to_net_dev(sdev);		\
		काष्ठा grcan_priv *priv = netdev_priv(dev);		\
		u8 val;							\
		पूर्णांक ret;						\
		अगर (dev->flags & IFF_UP)				\
			वापस -EBUSY;					\
		ret = kstrtou8(buf, 0, &val);				\
		अगर (ret < 0 || val > 1)					\
			वापस -EINVAL;					\
		priv->config.name = val;				\
		वापस count;						\
	पूर्ण								\
	अटल sमाप_प्रकार grcan_show_##name(काष्ठा device *sdev,		\
					 काष्ठा device_attribute *att,	\
					 अक्षर *buf)			\
	अणु								\
		काष्ठा net_device *dev = to_net_dev(sdev);		\
		काष्ठा grcan_priv *priv = netdev_priv(dev);		\
		वापस प्र_लिखो(buf, "%d\n", priv->config.name);		\
	पूर्ण								\
	अटल DEVICE_ATTR(name, 0644,					\
			   grcan_show_##name,				\
			   grcan_store_##name);				\
	GRCAN_MODULE_PARAM(name, uलघु, GRCAN_NOT_BOOL, desc)

/* The following configuration options are made available both via module
 * parameters and writable sysfs files. See the chapter about GRCAN in the
 * करोcumentation क्रम the GRLIB VHDL library क्रम further details.
 */
GRCAN_CONFIG_ATTR(enable0,
		  "Configuration of physical interface 0. Determines\n"	\
		  "the \"Enable 0\" bit of the configuration register.\n" \
		  "Format: 0 | 1\nDefault: 0\n");

GRCAN_CONFIG_ATTR(enable1,
		  "Configuration of physical interface 1. Determines\n"	\
		  "the \"Enable 1\" bit of the configuration register.\n" \
		  "Format: 0 | 1\nDefault: 0\n");

GRCAN_CONFIG_ATTR(select,
		  "Select which physical interface to use.\n"	\
		  "Format: 0 | 1\nDefault: 0\n");

/* The tx and rx buffer size configuration options are only available via module
 * parameters.
 */
GRCAN_MODULE_PARAM(txsize, uपूर्णांक, GRCAN_INVALID_BUFFER_SIZE,
		   "Sets the size of the tx buffer.\n"			\
		   "Format: <unsigned int> where (txsize & ~0x1fffc0) == 0\n" \
		   "Default: 1024\n");
GRCAN_MODULE_PARAM(rxsize, uपूर्णांक, GRCAN_INVALID_BUFFER_SIZE,
		   "Sets the size of the rx buffer.\n"			\
		   "Format: <unsigned int> where (size & ~0x1fffc0) == 0\n" \
		   "Default: 1024\n");

/* Function that makes sure that configuration करोne using
 * module parameters are set to valid values
 */
अटल व्योम grcan_sanitize_module_config(काष्ठा platक्रमm_device *ofdev)
अणु
	grcan_sanitize_enable0(ofdev);
	grcan_sanitize_enable1(ofdev);
	grcan_sanitize_select(ofdev);
	grcan_sanitize_txsize(ofdev);
	grcan_sanitize_rxsize(ofdev);
पूर्ण

अटल स्थिर काष्ठा attribute *स्थिर sysfs_grcan_attrs[] = अणु
	/* Config attrs */
	&dev_attr_enable0.attr,
	&dev_attr_enable1.attr,
	&dev_attr_select.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group sysfs_grcan_group = अणु
	.name	= "grcan",
	.attrs	= (काष्ठा attribute **)sysfs_grcan_attrs,
पूर्ण;

/* ========== Setting up the driver ========== */

अटल स्थिर काष्ठा net_device_ops grcan_netdev_ops = अणु
	.nकरो_खोलो	= grcan_खोलो,
	.nकरो_stop	= grcan_बंद,
	.nकरो_start_xmit	= grcan_start_xmit,
	.nकरो_change_mtu = can_change_mtu,
पूर्ण;

अटल पूर्णांक grcan_setup_netdev(काष्ठा platक्रमm_device *ofdev,
			      व्योम __iomem *base,
			      पूर्णांक irq, u32 ambafreq, bool txbug)
अणु
	काष्ठा net_device *dev;
	काष्ठा grcan_priv *priv;
	काष्ठा grcan_रेजिस्टरs __iomem *regs;
	पूर्णांक err;

	dev = alloc_candev(माप(काष्ठा grcan_priv), 0);
	अगर (!dev)
		वापस -ENOMEM;

	dev->irq = irq;
	dev->flags |= IFF_ECHO;
	dev->netdev_ops = &grcan_netdev_ops;
	dev->sysfs_groups[0] = &sysfs_grcan_group;

	priv = netdev_priv(dev);
	स_नकल(&priv->config, &grcan_module_config,
	       माप(काष्ठा grcan_device_config));
	priv->dev = dev;
	priv->regs = base;
	priv->can.bittiming_स्थिर = &grcan_bittiming_स्थिर;
	priv->can.करो_set_bittiming = grcan_set_bittiming;
	priv->can.करो_set_mode = grcan_set_mode;
	priv->can.करो_get_berr_counter = grcan_get_berr_counter;
	priv->can.घड़ी.freq = ambafreq;
	priv->can.ctrlmode_supported =
		CAN_CTRLMODE_LISTENONLY | CAN_CTRLMODE_ONE_SHOT;
	priv->need_txbug_workaround = txbug;

	/* Discover अगर triple sampling is supported by hardware */
	regs = priv->regs;
	grcan_set_bits(&regs->ctrl, GRCAN_CTRL_RESET);
	grcan_set_bits(&regs->conf, GRCAN_CONF_SAM);
	अगर (grcan_पढ़ो_bits(&regs->conf, GRCAN_CONF_SAM)) अणु
		priv->can.ctrlmode_supported |= CAN_CTRLMODE_3_SAMPLES;
		dev_dbg(&ofdev->dev, "Hardware supports triple-sampling\n");
	पूर्ण

	spin_lock_init(&priv->lock);

	अगर (priv->need_txbug_workaround) अणु
		समयr_setup(&priv->rr_समयr, grcan_running_reset, 0);
		समयr_setup(&priv->hang_समयr, grcan_initiate_running_reset, 0);
	पूर्ण

	netअगर_napi_add(dev, &priv->napi, grcan_poll, GRCAN_NAPI_WEIGHT);

	SET_NETDEV_DEV(dev, &ofdev->dev);
	dev_info(&ofdev->dev, "regs=0x%p, irq=%d, clock=%d\n",
		 priv->regs, dev->irq, priv->can.घड़ी.freq);

	err = रेजिस्टर_candev(dev);
	अगर (err)
		जाओ निकास_मुक्त_candev;

	platक्रमm_set_drvdata(ofdev, dev);

	/* Reset device to allow bit-timing to be set. No need to call
	 * grcan_reset at this stage. That is करोne in grcan_खोलो.
	 */
	grcan_ग_लिखो_reg(&regs->ctrl, GRCAN_CTRL_RESET);

	वापस 0;
निकास_मुक्त_candev:
	मुक्त_candev(dev);
	वापस err;
पूर्ण

अटल पूर्णांक grcan_probe(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा device_node *np = ofdev->dev.of_node;
	u32 sysid, ambafreq;
	पूर्णांक irq, err;
	व्योम __iomem *base;
	bool txbug = true;

	/* Compare GRLIB version number with the first that करोes not
	 * have the tx bug (see start_xmit)
	 */
	err = of_property_पढ़ो_u32(np, "systemid", &sysid);
	अगर (!err && ((sysid & GRLIB_VERSION_MASK)
		     >= GRCAN_TXBUG_SAFE_GRLIB_VERSION))
		txbug = false;

	err = of_property_पढ़ो_u32(np, "freq", &ambafreq);
	अगर (err) अणु
		dev_err(&ofdev->dev, "unable to fetch \"freq\" property\n");
		जाओ निकास_error;
	पूर्ण

	base = devm_platक्रमm_ioremap_resource(ofdev, 0);
	अगर (IS_ERR(base)) अणु
		err = PTR_ERR(base);
		जाओ निकास_error;
	पूर्ण

	irq = irq_of_parse_and_map(np, GRCAN_IRQIX_IRQ);
	अगर (!irq) अणु
		dev_err(&ofdev->dev, "no irq found\n");
		err = -ENODEV;
		जाओ निकास_error;
	पूर्ण

	grcan_sanitize_module_config(ofdev);

	err = grcan_setup_netdev(ofdev, base, irq, ambafreq, txbug);
	अगर (err)
		जाओ निकास_dispose_irq;

	वापस 0;

निकास_dispose_irq:
	irq_dispose_mapping(irq);
निकास_error:
	dev_err(&ofdev->dev,
		"%s socket CAN driver initialization failed with error %d\n",
		DRV_NAME, err);
	वापस err;
पूर्ण

अटल पूर्णांक grcan_हटाओ(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा net_device *dev = platक्रमm_get_drvdata(ofdev);
	काष्ठा grcan_priv *priv = netdev_priv(dev);

	unरेजिस्टर_candev(dev); /* Will in turn call grcan_बंद */

	irq_dispose_mapping(dev->irq);
	netअगर_napi_del(&priv->napi);
	मुक्त_candev(dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id grcan_match[] = अणु
	अणु.name = "GAISLER_GRCAN"पूर्ण,
	अणु.name = "01_03d"पूर्ण,
	अणु.name = "GAISLER_GRHCAN"पूर्ण,
	अणु.name = "01_034"पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, grcan_match);

अटल काष्ठा platक्रमm_driver grcan_driver = अणु
	.driver = अणु
		.name = DRV_NAME,
		.of_match_table = grcan_match,
	पूर्ण,
	.probe = grcan_probe,
	.हटाओ = grcan_हटाओ,
पूर्ण;

module_platक्रमm_driver(grcan_driver);

MODULE_AUTHOR("Aeroflex Gaisler AB.");
MODULE_DESCRIPTION("Socket CAN driver for Aeroflex Gaisler GRCAN");
MODULE_LICENSE("GPL");
