<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम high-speed SCC boards (those with DMA support)
 * Copyright (C) 1997-2000 Klaus Kudielka
 *
 * S5SCC/DMA support by Janko Koleznik S52HI
 */


#समावेश <linux/module.h>
#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/in.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/slab.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/sockios.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/atomic.h>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <linux/uaccess.h>
#समावेश <net/ax25.h>
#समावेश "z8530.h"


/* Number of buffers per channel */

#घोषणा NUM_TX_BUF      2	/* NUM_TX_BUF >= 1 (min. 2 recommended) */
#घोषणा NUM_RX_BUF      6	/* NUM_RX_BUF >= 1 (min. 2 recommended) */
#घोषणा BUF_SIZE        1576	/* BUF_SIZE >= mtu + hard_header_len */


/* Cards supported */

#घोषणा HW_PI           अणु "Ottawa PI", 0x300, 0x20, 0x10, 8, \
                            0, 8, 1843200, 3686400 पूर्ण
#घोषणा HW_PI2          अणु "Ottawa PI2", 0x300, 0x20, 0x10, 8, \
			    0, 8, 3686400, 7372800 पूर्ण
#घोषणा HW_TWIN         अणु "Gracilis PackeTwin", 0x200, 0x10, 0x10, 32, \
			    0, 4, 6144000, 6144000 पूर्ण
#घोषणा HW_S5           अणु "S5SCC/DMA", 0x200, 0x10, 0x10, 32, \
                          0, 8, 4915200, 9830400 पूर्ण

#घोषणा HARDWARE        अणु HW_PI, HW_PI2, HW_TWIN, HW_S5 पूर्ण

#घोषणा TMR_0_HZ        25600	/* Frequency of समयr 0 */

#घोषणा TYPE_PI         0
#घोषणा TYPE_PI2        1
#घोषणा TYPE_TWIN       2
#घोषणा TYPE_S5         3
#घोषणा NUM_TYPES       4

#घोषणा MAX_NUM_DEVS    32


/* SCC chips supported */

#घोषणा Z8530           0
#घोषणा Z85C30          1
#घोषणा Z85230          2

#घोषणा CHIPNAMES       अणु "Z8530", "Z85C30", "Z85230" पूर्ण


/* I/O रेजिस्टरs */

/* 8530 रेजिस्टरs relative to card base */
#घोषणा SCCB_CMD        0x00
#घोषणा SCCB_DATA       0x01
#घोषणा SCCA_CMD        0x02
#घोषणा SCCA_DATA       0x03

/* 8253/8254 रेजिस्टरs relative to card base */
#घोषणा TMR_CNT0        0x00
#घोषणा TMR_CNT1        0x01
#घोषणा TMR_CNT2        0x02
#घोषणा TMR_CTRL        0x03

/* Additional PI/PI2 रेजिस्टरs relative to card base */
#घोषणा PI_DREQ_MASK    0x04

/* Additional PackeTwin रेजिस्टरs relative to card base */
#घोषणा TWIN_INT_REG    0x08
#घोषणा TWIN_CLR_TMR1   0x09
#घोषणा TWIN_CLR_TMR2   0x0a
#घोषणा TWIN_SPARE_1    0x0b
#घोषणा TWIN_DMA_CFG    0x08
#घोषणा TWIN_SERIAL_CFG 0x09
#घोषणा TWIN_DMA_CLR_FF 0x0a
#घोषणा TWIN_SPARE_2    0x0b


/* PackeTwin I/O रेजिस्टर values */

/* INT_REG */
#घोषणा TWIN_SCC_MSK       0x01
#घोषणा TWIN_TMR1_MSK      0x02
#घोषणा TWIN_TMR2_MSK      0x04
#घोषणा TWIN_INT_MSK       0x07

/* SERIAL_CFG */
#घोषणा TWIN_DTRA_ON       0x01
#घोषणा TWIN_DTRB_ON       0x02
#घोषणा TWIN_EXTCLKA       0x04
#घोषणा TWIN_EXTCLKB       0x08
#घोषणा TWIN_LOOPA_ON      0x10
#घोषणा TWIN_LOOPB_ON      0x20
#घोषणा TWIN_EI            0x80

/* DMA_CFG */
#घोषणा TWIN_DMA_HDX_T1    0x08
#घोषणा TWIN_DMA_HDX_R1    0x0a
#घोषणा TWIN_DMA_HDX_T3    0x14
#घोषणा TWIN_DMA_HDX_R3    0x16
#घोषणा TWIN_DMA_FDX_T3R1  0x1b
#घोषणा TWIN_DMA_FDX_T1R3  0x1d


/* Status values */

#घोषणा IDLE      0
#घोषणा TX_HEAD   1
#घोषणा TX_DATA   2
#घोषणा TX_PAUSE  3
#घोषणा TX_TAIL   4
#घोषणा RTS_OFF   5
#घोषणा WAIT      6
#घोषणा DCD_ON    7
#घोषणा RX_ON     8
#घोषणा DCD_OFF   9


/* Ioctls */

#घोषणा SIOCGSCCPARAM SIOCDEVPRIVATE
#घोषणा SIOCSSCCPARAM (SIOCDEVPRIVATE+1)


/* Data types */

काष्ठा scc_param अणु
	पूर्णांक pclk_hz;		/* frequency of BRG input (करोn't change) */
	पूर्णांक brg_tc;		/* BRG terminal count; BRG disabled अगर < 0 */
	पूर्णांक nrzi;		/* 0 (nrz), 1 (nrzi) */
	पूर्णांक घड़ीs;		/* see dmascc_cfg करोcumentation */
	पूर्णांक txdelay;		/* [1/TMR_0_HZ] */
	पूर्णांक txसमयout;		/* [1/HZ] */
	पूर्णांक txtail;		/* [1/TMR_0_HZ] */
	पूर्णांक रुकोसमय;		/* [1/TMR_0_HZ] */
	पूर्णांक slotसमय;		/* [1/TMR_0_HZ] */
	पूर्णांक persist;		/* 1 ... 256 */
	पूर्णांक dma;		/* -1 (disable), 0, 1, 3 */
	पूर्णांक txछोड़ो;		/* [1/TMR_0_HZ] */
	पूर्णांक rtsoff;		/* [1/TMR_0_HZ] */
	पूर्णांक dcकरोn;		/* [1/TMR_0_HZ] */
	पूर्णांक dcकरोff;		/* [1/TMR_0_HZ] */
पूर्ण;

काष्ठा scc_hardware अणु
	अक्षर *name;
	पूर्णांक io_region;
	पूर्णांक io_delta;
	पूर्णांक io_size;
	पूर्णांक num_devs;
	पूर्णांक scc_offset;
	पूर्णांक पंचांगr_offset;
	पूर्णांक पंचांगr_hz;
	पूर्णांक pclk_hz;
पूर्ण;

काष्ठा scc_priv अणु
	पूर्णांक type;
	पूर्णांक chip;
	काष्ठा net_device *dev;
	काष्ठा scc_info *info;

	पूर्णांक channel;
	पूर्णांक card_base, scc_cmd, scc_data;
	पूर्णांक पंचांगr_cnt, पंचांगr_ctrl, पंचांगr_mode;
	काष्ठा scc_param param;
	अक्षर rx_buf[NUM_RX_BUF][BUF_SIZE];
	पूर्णांक rx_len[NUM_RX_BUF];
	पूर्णांक rx_ptr;
	काष्ठा work_काष्ठा rx_work;
	पूर्णांक rx_head, rx_tail, rx_count;
	पूर्णांक rx_over;
	अक्षर tx_buf[NUM_TX_BUF][BUF_SIZE];
	पूर्णांक tx_len[NUM_TX_BUF];
	पूर्णांक tx_ptr;
	पूर्णांक tx_head, tx_tail, tx_count;
	पूर्णांक state;
	अचिन्हित दीर्घ tx_start;
	पूर्णांक rr0;
	spinlock_t *रेजिस्टर_lock;	/* Per scc_info */
	spinlock_t ring_lock;
पूर्ण;

काष्ठा scc_info अणु
	पूर्णांक irq_used;
	पूर्णांक twin_serial_cfg;
	काष्ठा net_device *dev[2];
	काष्ठा scc_priv priv[2];
	काष्ठा scc_info *next;
	spinlock_t रेजिस्टर_lock;	/* Per device रेजिस्टर lock */
पूर्ण;


/* Function declarations */
अटल पूर्णांक setup_adapter(पूर्णांक card_base, पूर्णांक type, पूर्णांक n) __init;

अटल व्योम ग_लिखो_scc(काष्ठा scc_priv *priv, पूर्णांक reg, पूर्णांक val);
अटल व्योम ग_लिखो_scc_data(काष्ठा scc_priv *priv, पूर्णांक val, पूर्णांक fast);
अटल पूर्णांक पढ़ो_scc(काष्ठा scc_priv *priv, पूर्णांक reg);
अटल पूर्णांक पढ़ो_scc_data(काष्ठा scc_priv *priv);

अटल पूर्णांक scc_खोलो(काष्ठा net_device *dev);
अटल पूर्णांक scc_बंद(काष्ठा net_device *dev);
अटल पूर्णांक scc_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd);
अटल पूर्णांक scc_send_packet(काष्ठा sk_buff *skb, काष्ठा net_device *dev);
अटल पूर्णांक scc_set_mac_address(काष्ठा net_device *dev, व्योम *sa);

अटल अंतरभूत व्योम tx_on(काष्ठा scc_priv *priv);
अटल अंतरभूत व्योम rx_on(काष्ठा scc_priv *priv);
अटल अंतरभूत व्योम rx_off(काष्ठा scc_priv *priv);
अटल व्योम start_समयr(काष्ठा scc_priv *priv, पूर्णांक t, पूर्णांक r15);
अटल अंतरभूत अचिन्हित अक्षर अक्रमom(व्योम);

अटल अंतरभूत व्योम z8530_isr(काष्ठा scc_info *info);
अटल irqवापस_t scc_isr(पूर्णांक irq, व्योम *dev_id);
अटल व्योम rx_isr(काष्ठा scc_priv *priv);
अटल व्योम special_condition(काष्ठा scc_priv *priv, पूर्णांक rc);
अटल व्योम rx_bh(काष्ठा work_काष्ठा *);
अटल व्योम tx_isr(काष्ठा scc_priv *priv);
अटल व्योम es_isr(काष्ठा scc_priv *priv);
अटल व्योम पंचांग_isr(काष्ठा scc_priv *priv);


/* Initialization variables */

अटल पूर्णांक io[MAX_NUM_DEVS] __initdata = अणु 0, पूर्ण;

/* Beware! hw[] is also used in dmascc_निकास(). */
अटल काष्ठा scc_hardware hw[NUM_TYPES] = HARDWARE;


/* Global variables */

अटल काष्ठा scc_info *first;
अटल अचिन्हित दीर्घ अक्रम;


MODULE_AUTHOR("Klaus Kudielka");
MODULE_DESCRIPTION("Driver for high-speed SCC boards");
module_param_hw_array(io, पूर्णांक, ioport, शून्य, 0);
MODULE_LICENSE("GPL");

अटल व्योम __निकास dmascc_निकास(व्योम)
अणु
	पूर्णांक i;
	काष्ठा scc_info *info;

	जबतक (first) अणु
		info = first;

		/* Unरेजिस्टर devices */
		क्रम (i = 0; i < 2; i++)
			unरेजिस्टर_netdev(info->dev[i]);

		/* Reset board */
		अगर (info->priv[0].type == TYPE_TWIN)
			outb(0, info->dev[0]->base_addr + TWIN_SERIAL_CFG);
		ग_लिखो_scc(&info->priv[0], R9, FHWRES);
		release_region(info->dev[0]->base_addr,
			       hw[info->priv[0].type].io_size);

		क्रम (i = 0; i < 2; i++)
			मुक्त_netdev(info->dev[i]);

		/* Free memory */
		first = info->next;
		kमुक्त(info);
	पूर्ण
पूर्ण

अटल पूर्णांक __init dmascc_init(व्योम)
अणु
	पूर्णांक h, i, j, n;
	पूर्णांक base[MAX_NUM_DEVS], tcmd[MAX_NUM_DEVS], t0[MAX_NUM_DEVS],
	    t1[MAX_NUM_DEVS];
	अचिन्हित t_val;
	अचिन्हित दीर्घ समय, start[MAX_NUM_DEVS], delay[MAX_NUM_DEVS],
	    counting[MAX_NUM_DEVS];

	/* Initialize अक्रमom number generator */
	अक्रम = jअगरfies;
	/* Cards found = 0 */
	n = 0;
	/* Warning message */
	अगर (!io[0])
		prपूर्णांकk(KERN_INFO "dmascc: autoprobing (dangerous)\n");

	/* Run स्वतःdetection क्रम each card type */
	क्रम (h = 0; h < NUM_TYPES; h++) अणु

		अगर (io[0]) अणु
			/* User-specअगरied I/O address regions */
			क्रम (i = 0; i < hw[h].num_devs; i++)
				base[i] = 0;
			क्रम (i = 0; i < MAX_NUM_DEVS && io[i]; i++) अणु
				j = (io[i] -
				     hw[h].io_region) / hw[h].io_delta;
				अगर (j >= 0 && j < hw[h].num_devs &&
				    hw[h].io_region +
				    j * hw[h].io_delta == io[i]) अणु
					base[j] = io[i];
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Default I/O address regions */
			क्रम (i = 0; i < hw[h].num_devs; i++) अणु
				base[i] =
				    hw[h].io_region + i * hw[h].io_delta;
			पूर्ण
		पूर्ण

		/* Check valid I/O address regions */
		क्रम (i = 0; i < hw[h].num_devs; i++)
			अगर (base[i]) अणु
				अगर (!request_region
				    (base[i], hw[h].io_size, "dmascc"))
					base[i] = 0;
				अन्यथा अणु
					tcmd[i] =
					    base[i] + hw[h].पंचांगr_offset +
					    TMR_CTRL;
					t0[i] =
					    base[i] + hw[h].पंचांगr_offset +
					    TMR_CNT0;
					t1[i] =
					    base[i] + hw[h].पंचांगr_offset +
					    TMR_CNT1;
				पूर्ण
			पूर्ण

		/* Start समयrs */
		क्रम (i = 0; i < hw[h].num_devs; i++)
			अगर (base[i]) अणु
				/* Timer 0: LSB+MSB, Mode 3, TMR_0_HZ */
				outb(0x36, tcmd[i]);
				outb((hw[h].पंचांगr_hz / TMR_0_HZ) & 0xFF,
				     t0[i]);
				outb((hw[h].पंचांगr_hz / TMR_0_HZ) >> 8,
				     t0[i]);
				/* Timer 1: LSB+MSB, Mode 0, HZ/10 */
				outb(0x70, tcmd[i]);
				outb((TMR_0_HZ / HZ * 10) & 0xFF, t1[i]);
				outb((TMR_0_HZ / HZ * 10) >> 8, t1[i]);
				start[i] = jअगरfies;
				delay[i] = 0;
				counting[i] = 1;
				/* Timer 2: LSB+MSB, Mode 0 */
				outb(0xb0, tcmd[i]);
			पूर्ण
		समय = jअगरfies;
		/* Wait until counter रेजिस्टरs are loaded */
		udelay(2000000 / TMR_0_HZ);

		/* Timing loop */
		जबतक (jअगरfies - समय < 13) अणु
			क्रम (i = 0; i < hw[h].num_devs; i++)
				अगर (base[i] && counting[i]) अणु
					/* Read back Timer 1: latch; पढ़ो LSB; पढ़ो MSB */
					outb(0x40, tcmd[i]);
					t_val =
					    inb(t1[i]) + (inb(t1[i]) << 8);
					/* Also check whether counter did wrap */
					अगर (t_val == 0 ||
					    t_val > TMR_0_HZ / HZ * 10)
						counting[i] = 0;
					delay[i] = jअगरfies - start[i];
				पूर्ण
		पूर्ण

		/* Evaluate measurements */
		क्रम (i = 0; i < hw[h].num_devs; i++)
			अगर (base[i]) अणु
				अगर ((delay[i] >= 9 && delay[i] <= 11) &&
				    /* Ok, we have found an adapter */
				    (setup_adapter(base[i], h, n) == 0))
					n++;
				अन्यथा
					release_region(base[i],
						       hw[h].io_size);
			पूर्ण

	पूर्ण			/* NUM_TYPES */

	/* If any adapter was successfully initialized, वापस ok */
	अगर (n)
		वापस 0;

	/* If no adapter found, वापस error */
	prपूर्णांकk(KERN_INFO "dmascc: no adapters found\n");
	वापस -EIO;
पूर्ण

module_init(dmascc_init);
module_निकास(dmascc_निकास);

अटल व्योम __init dev_setup(काष्ठा net_device *dev)
अणु
	dev->type = ARPHRD_AX25;
	dev->hard_header_len = AX25_MAX_HEADER_LEN;
	dev->mtu = 1500;
	dev->addr_len = AX25_ADDR_LEN;
	dev->tx_queue_len = 64;
	स_नकल(dev->broadcast, &ax25_bcast, AX25_ADDR_LEN);
	स_नकल(dev->dev_addr, &ax25_defaddr, AX25_ADDR_LEN);
पूर्ण

अटल स्थिर काष्ठा net_device_ops scc_netdev_ops = अणु
	.nकरो_खोलो = scc_खोलो,
	.nकरो_stop = scc_बंद,
	.nकरो_start_xmit = scc_send_packet,
	.nकरो_करो_ioctl = scc_ioctl,
	.nकरो_set_mac_address = scc_set_mac_address,
पूर्ण;

अटल पूर्णांक __init setup_adapter(पूर्णांक card_base, पूर्णांक type, पूर्णांक n)
अणु
	पूर्णांक i, irq, chip, err;
	काष्ठा scc_info *info;
	काष्ठा net_device *dev;
	काष्ठा scc_priv *priv;
	अचिन्हित दीर्घ समय;
	अचिन्हित पूर्णांक irqs;
	पूर्णांक पंचांगr_base = card_base + hw[type].पंचांगr_offset;
	पूर्णांक scc_base = card_base + hw[type].scc_offset;
	अक्षर *chipnames[] = CHIPNAMES;

	/* Initialize what is necessary क्रम ग_लिखो_scc and ग_लिखो_scc_data */
	info = kzalloc(माप(काष्ठा scc_info), GFP_KERNEL | GFP_DMA);
	अगर (!info) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	info->dev[0] = alloc_netdev(0, "", NET_NAME_UNKNOWN, dev_setup);
	अगर (!info->dev[0]) अणु
		prपूर्णांकk(KERN_ERR "dmascc: "
		       "could not allocate memory for %s at %#3x\n",
		       hw[type].name, card_base);
		err = -ENOMEM;
		जाओ out1;
	पूर्ण

	info->dev[1] = alloc_netdev(0, "", NET_NAME_UNKNOWN, dev_setup);
	अगर (!info->dev[1]) अणु
		prपूर्णांकk(KERN_ERR "dmascc: "
		       "could not allocate memory for %s at %#3x\n",
		       hw[type].name, card_base);
		err = -ENOMEM;
		जाओ out2;
	पूर्ण
	spin_lock_init(&info->रेजिस्टर_lock);

	priv = &info->priv[0];
	priv->type = type;
	priv->card_base = card_base;
	priv->scc_cmd = scc_base + SCCA_CMD;
	priv->scc_data = scc_base + SCCA_DATA;
	priv->रेजिस्टर_lock = &info->रेजिस्टर_lock;

	/* Reset SCC */
	ग_लिखो_scc(priv, R9, FHWRES | MIE | NV);

	/* Determine type of chip by enabling SDLC/HDLC enhancements */
	ग_लिखो_scc(priv, R15, SHDLCE);
	अगर (!पढ़ो_scc(priv, R15)) अणु
		/* WR7' not present. This is an ordinary Z8530 SCC. */
		chip = Z8530;
	पूर्ण अन्यथा अणु
		/* Put one अक्षरacter in TX FIFO */
		ग_लिखो_scc_data(priv, 0, 0);
		अगर (पढ़ो_scc(priv, R0) & Tx_BUF_EMP) अणु
			/* TX FIFO not full. This is a Z85230 ESCC with a 4-byte FIFO. */
			chip = Z85230;
		पूर्ण अन्यथा अणु
			/* TX FIFO full. This is a Z85C30 SCC with a 1-byte FIFO. */
			chip = Z85C30;
		पूर्ण
	पूर्ण
	ग_लिखो_scc(priv, R15, 0);

	/* Start IRQ स्वतः-detection */
	irqs = probe_irq_on();

	/* Enable पूर्णांकerrupts */
	अगर (type == TYPE_TWIN) अणु
		outb(0, card_base + TWIN_DMA_CFG);
		inb(card_base + TWIN_CLR_TMR1);
		inb(card_base + TWIN_CLR_TMR2);
		info->twin_serial_cfg = TWIN_EI;
		outb(info->twin_serial_cfg, card_base + TWIN_SERIAL_CFG);
	पूर्ण अन्यथा अणु
		ग_लिखो_scc(priv, R15, CTSIE);
		ग_लिखो_scc(priv, R0, RES_EXT_INT);
		ग_लिखो_scc(priv, R1, EXT_INT_ENAB);
	पूर्ण

	/* Start समयr */
	outb(1, पंचांगr_base + TMR_CNT1);
	outb(0, पंचांगr_base + TMR_CNT1);

	/* Wait and detect IRQ */
	समय = jअगरfies;
	जबतक (jअगरfies - समय < 2 + HZ / TMR_0_HZ);
	irq = probe_irq_off(irqs);

	/* Clear pending पूर्णांकerrupt, disable पूर्णांकerrupts */
	अगर (type == TYPE_TWIN) अणु
		inb(card_base + TWIN_CLR_TMR1);
	पूर्ण अन्यथा अणु
		ग_लिखो_scc(priv, R1, 0);
		ग_लिखो_scc(priv, R15, 0);
		ग_लिखो_scc(priv, R0, RES_EXT_INT);
	पूर्ण

	अगर (irq <= 0) अणु
		prपूर्णांकk(KERN_ERR
		       "dmascc: could not find irq of %s at %#3x (irq=%d)\n",
		       hw[type].name, card_base, irq);
		err = -ENODEV;
		जाओ out3;
	पूर्ण

	/* Set up data काष्ठाures */
	क्रम (i = 0; i < 2; i++) अणु
		dev = info->dev[i];
		priv = &info->priv[i];
		priv->type = type;
		priv->chip = chip;
		priv->dev = dev;
		priv->info = info;
		priv->channel = i;
		spin_lock_init(&priv->ring_lock);
		priv->रेजिस्टर_lock = &info->रेजिस्टर_lock;
		priv->card_base = card_base;
		priv->scc_cmd = scc_base + (i ? SCCB_CMD : SCCA_CMD);
		priv->scc_data = scc_base + (i ? SCCB_DATA : SCCA_DATA);
		priv->पंचांगr_cnt = पंचांगr_base + (i ? TMR_CNT2 : TMR_CNT1);
		priv->पंचांगr_ctrl = पंचांगr_base + TMR_CTRL;
		priv->पंचांगr_mode = i ? 0xb0 : 0x70;
		priv->param.pclk_hz = hw[type].pclk_hz;
		priv->param.brg_tc = -1;
		priv->param.घड़ीs = TCTRxCP | RCRTxCP;
		priv->param.persist = 256;
		priv->param.dma = -1;
		INIT_WORK(&priv->rx_work, rx_bh);
		dev->ml_priv = priv;
		snम_लिखो(dev->name, माप(dev->name), "dmascc%i", 2 * n + i);
		dev->base_addr = card_base;
		dev->irq = irq;
		dev->netdev_ops = &scc_netdev_ops;
		dev->header_ops = &ax25_header_ops;
	पूर्ण
	अगर (रेजिस्टर_netdev(info->dev[0])) अणु
		prपूर्णांकk(KERN_ERR "dmascc: could not register %s\n",
		       info->dev[0]->name);
		err = -ENODEV;
		जाओ out3;
	पूर्ण
	अगर (रेजिस्टर_netdev(info->dev[1])) अणु
		prपूर्णांकk(KERN_ERR "dmascc: could not register %s\n",
		       info->dev[1]->name);
		err = -ENODEV;
		जाओ out4;
	पूर्ण


	info->next = first;
	first = info;
	prपूर्णांकk(KERN_INFO "dmascc: found %s (%s) at %#3x, irq %d\n",
	       hw[type].name, chipnames[chip], card_base, irq);
	वापस 0;

      out4:
	unरेजिस्टर_netdev(info->dev[0]);
      out3:
	अगर (info->priv[0].type == TYPE_TWIN)
		outb(0, info->dev[0]->base_addr + TWIN_SERIAL_CFG);
	ग_लिखो_scc(&info->priv[0], R9, FHWRES);
	मुक्त_netdev(info->dev[1]);
      out2:
	मुक्त_netdev(info->dev[0]);
      out1:
	kमुक्त(info);
      out:
	वापस err;
पूर्ण


/* Driver functions */

अटल व्योम ग_लिखो_scc(काष्ठा scc_priv *priv, पूर्णांक reg, पूर्णांक val)
अणु
	अचिन्हित दीर्घ flags;
	चयन (priv->type) अणु
	हाल TYPE_S5:
		अगर (reg)
			outb(reg, priv->scc_cmd);
		outb(val, priv->scc_cmd);
		वापस;
	हाल TYPE_TWIN:
		अगर (reg)
			outb_p(reg, priv->scc_cmd);
		outb_p(val, priv->scc_cmd);
		वापस;
	शेष:
		spin_lock_irqsave(priv->रेजिस्टर_lock, flags);
		outb_p(0, priv->card_base + PI_DREQ_MASK);
		अगर (reg)
			outb_p(reg, priv->scc_cmd);
		outb_p(val, priv->scc_cmd);
		outb(1, priv->card_base + PI_DREQ_MASK);
		spin_unlock_irqrestore(priv->रेजिस्टर_lock, flags);
		वापस;
	पूर्ण
पूर्ण


अटल व्योम ग_लिखो_scc_data(काष्ठा scc_priv *priv, पूर्णांक val, पूर्णांक fast)
अणु
	अचिन्हित दीर्घ flags;
	चयन (priv->type) अणु
	हाल TYPE_S5:
		outb(val, priv->scc_data);
		वापस;
	हाल TYPE_TWIN:
		outb_p(val, priv->scc_data);
		वापस;
	शेष:
		अगर (fast)
			outb_p(val, priv->scc_data);
		अन्यथा अणु
			spin_lock_irqsave(priv->रेजिस्टर_lock, flags);
			outb_p(0, priv->card_base + PI_DREQ_MASK);
			outb_p(val, priv->scc_data);
			outb(1, priv->card_base + PI_DREQ_MASK);
			spin_unlock_irqrestore(priv->रेजिस्टर_lock, flags);
		पूर्ण
		वापस;
	पूर्ण
पूर्ण


अटल पूर्णांक पढ़ो_scc(काष्ठा scc_priv *priv, पूर्णांक reg)
अणु
	पूर्णांक rc;
	अचिन्हित दीर्घ flags;
	चयन (priv->type) अणु
	हाल TYPE_S5:
		अगर (reg)
			outb(reg, priv->scc_cmd);
		वापस inb(priv->scc_cmd);
	हाल TYPE_TWIN:
		अगर (reg)
			outb_p(reg, priv->scc_cmd);
		वापस inb_p(priv->scc_cmd);
	शेष:
		spin_lock_irqsave(priv->रेजिस्टर_lock, flags);
		outb_p(0, priv->card_base + PI_DREQ_MASK);
		अगर (reg)
			outb_p(reg, priv->scc_cmd);
		rc = inb_p(priv->scc_cmd);
		outb(1, priv->card_base + PI_DREQ_MASK);
		spin_unlock_irqrestore(priv->रेजिस्टर_lock, flags);
		वापस rc;
	पूर्ण
पूर्ण


अटल पूर्णांक पढ़ो_scc_data(काष्ठा scc_priv *priv)
अणु
	पूर्णांक rc;
	अचिन्हित दीर्घ flags;
	चयन (priv->type) अणु
	हाल TYPE_S5:
		वापस inb(priv->scc_data);
	हाल TYPE_TWIN:
		वापस inb_p(priv->scc_data);
	शेष:
		spin_lock_irqsave(priv->रेजिस्टर_lock, flags);
		outb_p(0, priv->card_base + PI_DREQ_MASK);
		rc = inb_p(priv->scc_data);
		outb(1, priv->card_base + PI_DREQ_MASK);
		spin_unlock_irqrestore(priv->रेजिस्टर_lock, flags);
		वापस rc;
	पूर्ण
पूर्ण


अटल पूर्णांक scc_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा scc_priv *priv = dev->ml_priv;
	काष्ठा scc_info *info = priv->info;
	पूर्णांक card_base = priv->card_base;

	/* Request IRQ अगर not alपढ़ोy used by other channel */
	अगर (!info->irq_used) अणु
		अगर (request_irq(dev->irq, scc_isr, 0, "dmascc", info)) अणु
			वापस -EAGAIN;
		पूर्ण
	पूर्ण
	info->irq_used++;

	/* Request DMA अगर required */
	अगर (priv->param.dma >= 0) अणु
		अगर (request_dma(priv->param.dma, "dmascc")) अणु
			अगर (--info->irq_used == 0)
				मुक्त_irq(dev->irq, info);
			वापस -EAGAIN;
		पूर्ण अन्यथा अणु
			अचिन्हित दीर्घ flags = claim_dma_lock();
			clear_dma_ff(priv->param.dma);
			release_dma_lock(flags);
		पूर्ण
	पूर्ण

	/* Initialize local variables */
	priv->rx_ptr = 0;
	priv->rx_over = 0;
	priv->rx_head = priv->rx_tail = priv->rx_count = 0;
	priv->state = IDLE;
	priv->tx_head = priv->tx_tail = priv->tx_count = 0;
	priv->tx_ptr = 0;

	/* Reset channel */
	ग_लिखो_scc(priv, R9, (priv->channel ? CHRB : CHRA) | MIE | NV);
	/* X1 घड़ी, SDLC mode */
	ग_लिखो_scc(priv, R4, SDLC | X1CLK);
	/* DMA */
	ग_लिखो_scc(priv, R1, EXT_INT_ENAB | WT_FN_RDYFN);
	/* 8 bit RX अक्षर, RX disable */
	ग_लिखो_scc(priv, R3, Rx8);
	/* 8 bit TX अक्षर, TX disable */
	ग_लिखो_scc(priv, R5, Tx8);
	/* SDLC address field */
	ग_लिखो_scc(priv, R6, 0);
	/* SDLC flag */
	ग_लिखो_scc(priv, R7, FLAG);
	चयन (priv->chip) अणु
	हाल Z85C30:
		/* Select WR7' */
		ग_लिखो_scc(priv, R15, SHDLCE);
		/* Auto EOM reset */
		ग_लिखो_scc(priv, R7, AUTOEOM);
		ग_लिखो_scc(priv, R15, 0);
		अवरोध;
	हाल Z85230:
		/* Select WR7' */
		ग_लिखो_scc(priv, R15, SHDLCE);
		/* The following bits are set (see 2.5.2.1):
		   - Automatic EOM reset
		   - Interrupt request अगर RX FIFO is half full
		   This bit should be ignored in DMA mode (according to the
		   करोcumentation), but actually isn't. The receiver doesn't work अगर
		   it is set. Thus, we have to clear it in DMA mode.
		   - Interrupt/DMA request अगर TX FIFO is completely empty
		   a) If set, the ESCC behaves as अगर it had no TX FIFO (Z85C30
		   compatibility).
		   b) If cleared, DMA requests may follow each other very quickly,
		   filling up the TX FIFO.
		   Advantage: TX works even in हाल of high bus latency.
		   Disadvantage: Edge-triggered DMA request circuitry may miss
		   a request. No more data is delivered, resulting
		   in a TX FIFO underrun.
		   Both PI2 and S5SCC/DMA seem to work fine with TXFIFOE cleared.
		   The PackeTwin करोesn't. I don't know about the PI, but let's
		   assume it behaves like the PI2.
		 */
		अगर (priv->param.dma >= 0) अणु
			अगर (priv->type == TYPE_TWIN)
				ग_लिखो_scc(priv, R7, AUTOEOM | TXFIFOE);
			अन्यथा
				ग_लिखो_scc(priv, R7, AUTOEOM);
		पूर्ण अन्यथा अणु
			ग_लिखो_scc(priv, R7, AUTOEOM | RXFIFOH);
		पूर्ण
		ग_लिखो_scc(priv, R15, 0);
		अवरोध;
	पूर्ण
	/* Preset CRC, NRZ(I) encoding */
	ग_लिखो_scc(priv, R10, CRCPS | (priv->param.nrzi ? NRZI : NRZ));

	/* Configure baud rate generator */
	अगर (priv->param.brg_tc >= 0) अणु
		/* Program BR generator */
		ग_लिखो_scc(priv, R12, priv->param.brg_tc & 0xFF);
		ग_लिखो_scc(priv, R13, (priv->param.brg_tc >> 8) & 0xFF);
		/* BRG source = SYS CLK; enable BRG; DTR REQ function (required by
		   PackeTwin, not connected on the PI2); set DPLL source to BRG */
		ग_लिखो_scc(priv, R14, SSBR | DTRREQ | BRSRC | BRENABL);
		/* Enable DPLL */
		ग_लिखो_scc(priv, R14, SEARCH | DTRREQ | BRSRC | BRENABL);
	पूर्ण अन्यथा अणु
		/* Disable BR generator */
		ग_लिखो_scc(priv, R14, DTRREQ | BRSRC);
	पूर्ण

	/* Configure घड़ीs */
	अगर (priv->type == TYPE_TWIN) अणु
		/* Disable बाह्यal TX घड़ी receiver */
		outb((info->twin_serial_cfg &=
		      ~(priv->channel ? TWIN_EXTCLKB : TWIN_EXTCLKA)),
		     card_base + TWIN_SERIAL_CFG);
	पूर्ण
	ग_लिखो_scc(priv, R11, priv->param.घड़ीs);
	अगर ((priv->type == TYPE_TWIN) && !(priv->param.घड़ीs & TRxCOI)) अणु
		/* Enable बाह्यal TX घड़ी receiver */
		outb((info->twin_serial_cfg |=
		      (priv->channel ? TWIN_EXTCLKB : TWIN_EXTCLKA)),
		     card_base + TWIN_SERIAL_CFG);
	पूर्ण

	/* Configure PackeTwin */
	अगर (priv->type == TYPE_TWIN) अणु
		/* Assert DTR, enable पूर्णांकerrupts */
		outb((info->twin_serial_cfg |= TWIN_EI |
		      (priv->channel ? TWIN_DTRB_ON : TWIN_DTRA_ON)),
		     card_base + TWIN_SERIAL_CFG);
	पूर्ण

	/* Read current status */
	priv->rr0 = पढ़ो_scc(priv, R0);
	/* Enable DCD पूर्णांकerrupt */
	ग_लिखो_scc(priv, R15, DCDIE);

	netअगर_start_queue(dev);

	वापस 0;
पूर्ण


अटल पूर्णांक scc_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा scc_priv *priv = dev->ml_priv;
	काष्ठा scc_info *info = priv->info;
	पूर्णांक card_base = priv->card_base;

	netअगर_stop_queue(dev);

	अगर (priv->type == TYPE_TWIN) अणु
		/* Drop DTR */
		outb((info->twin_serial_cfg &=
		      (priv->channel ? ~TWIN_DTRB_ON : ~TWIN_DTRA_ON)),
		     card_base + TWIN_SERIAL_CFG);
	पूर्ण

	/* Reset channel, मुक्त DMA and IRQ */
	ग_लिखो_scc(priv, R9, (priv->channel ? CHRB : CHRA) | MIE | NV);
	अगर (priv->param.dma >= 0) अणु
		अगर (priv->type == TYPE_TWIN)
			outb(0, card_base + TWIN_DMA_CFG);
		मुक्त_dma(priv->param.dma);
	पूर्ण
	अगर (--info->irq_used == 0)
		मुक्त_irq(dev->irq, info);

	वापस 0;
पूर्ण


अटल पूर्णांक scc_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा scc_priv *priv = dev->ml_priv;

	चयन (cmd) अणु
	हाल SIOCGSCCPARAM:
		अगर (copy_to_user
		    (अगरr->अगरr_data, &priv->param,
		     माप(काष्ठा scc_param)))
			वापस -EFAULT;
		वापस 0;
	हाल SIOCSSCCPARAM:
		अगर (!capable(CAP_NET_ADMIN))
			वापस -EPERM;
		अगर (netअगर_running(dev))
			वापस -EAGAIN;
		अगर (copy_from_user
		    (&priv->param, अगरr->अगरr_data,
		     माप(काष्ठा scc_param)))
			वापस -EFAULT;
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण


अटल पूर्णांक scc_send_packet(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा scc_priv *priv = dev->ml_priv;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	अगर (skb->protocol == htons(ETH_P_IP))
		वापस ax25_ip_xmit(skb);

	/* Temporarily stop the scheduler feeding us packets */
	netअगर_stop_queue(dev);

	/* Transfer data to DMA buffer */
	i = priv->tx_head;
	skb_copy_from_linear_data_offset(skb, 1, priv->tx_buf[i], skb->len - 1);
	priv->tx_len[i] = skb->len - 1;

	/* Clear पूर्णांकerrupts जबतक we touch our circular buffers */

	spin_lock_irqsave(&priv->ring_lock, flags);
	/* Move the ring buffer's head */
	priv->tx_head = (i + 1) % NUM_TX_BUF;
	priv->tx_count++;

	/* If we just filled up the last buffer, leave queue stopped.
	   The higher layers must रुको until we have a DMA buffer
	   to accept the data. */
	अगर (priv->tx_count < NUM_TX_BUF)
		netअगर_wake_queue(dev);

	/* Set new TX state */
	अगर (priv->state == IDLE) अणु
		/* Assert RTS, start समयr */
		priv->state = TX_HEAD;
		priv->tx_start = jअगरfies;
		ग_लिखो_scc(priv, R5, TxCRC_ENAB | RTS | TxENAB | Tx8);
		ग_लिखो_scc(priv, R15, 0);
		start_समयr(priv, priv->param.txdelay, 0);
	पूर्ण

	/* Turn पूर्णांकerrupts back on and मुक्त buffer */
	spin_unlock_irqrestore(&priv->ring_lock, flags);
	dev_kमुक्त_skb(skb);

	वापस NETDEV_TX_OK;
पूर्ण


अटल पूर्णांक scc_set_mac_address(काष्ठा net_device *dev, व्योम *sa)
अणु
	स_नकल(dev->dev_addr, ((काष्ठा sockaddr *) sa)->sa_data,
	       dev->addr_len);
	वापस 0;
पूर्ण


अटल अंतरभूत व्योम tx_on(काष्ठा scc_priv *priv)
अणु
	पूर्णांक i, n;
	अचिन्हित दीर्घ flags;

	अगर (priv->param.dma >= 0) अणु
		n = (priv->chip == Z85230) ? 3 : 1;
		/* Program DMA controller */
		flags = claim_dma_lock();
		set_dma_mode(priv->param.dma, DMA_MODE_WRITE);
		set_dma_addr(priv->param.dma,
			     (पूर्णांक) priv->tx_buf[priv->tx_tail] + n);
		set_dma_count(priv->param.dma,
			      priv->tx_len[priv->tx_tail] - n);
		release_dma_lock(flags);
		/* Enable TX underrun पूर्णांकerrupt */
		ग_लिखो_scc(priv, R15, TxUIE);
		/* Configure DREQ */
		अगर (priv->type == TYPE_TWIN)
			outb((priv->param.dma ==
			      1) ? TWIN_DMA_HDX_T1 : TWIN_DMA_HDX_T3,
			     priv->card_base + TWIN_DMA_CFG);
		अन्यथा
			ग_लिखो_scc(priv, R1,
				  EXT_INT_ENAB | WT_FN_RDYFN |
				  WT_RDY_ENAB);
		/* Write first byte(s) */
		spin_lock_irqsave(priv->रेजिस्टर_lock, flags);
		क्रम (i = 0; i < n; i++)
			ग_लिखो_scc_data(priv,
				       priv->tx_buf[priv->tx_tail][i], 1);
		enable_dma(priv->param.dma);
		spin_unlock_irqrestore(priv->रेजिस्टर_lock, flags);
	पूर्ण अन्यथा अणु
		ग_लिखो_scc(priv, R15, TxUIE);
		ग_लिखो_scc(priv, R1,
			  EXT_INT_ENAB | WT_FN_RDYFN | TxINT_ENAB);
		tx_isr(priv);
	पूर्ण
	/* Reset EOM latch अगर we करो not have the AUTOEOM feature */
	अगर (priv->chip == Z8530)
		ग_लिखो_scc(priv, R0, RES_EOM_L);
पूर्ण


अटल अंतरभूत व्योम rx_on(काष्ठा scc_priv *priv)
अणु
	अचिन्हित दीर्घ flags;

	/* Clear RX FIFO */
	जबतक (पढ़ो_scc(priv, R0) & Rx_CH_AV)
		पढ़ो_scc_data(priv);
	priv->rx_over = 0;
	अगर (priv->param.dma >= 0) अणु
		/* Program DMA controller */
		flags = claim_dma_lock();
		set_dma_mode(priv->param.dma, DMA_MODE_READ);
		set_dma_addr(priv->param.dma,
			     (पूर्णांक) priv->rx_buf[priv->rx_head]);
		set_dma_count(priv->param.dma, BUF_SIZE);
		release_dma_lock(flags);
		enable_dma(priv->param.dma);
		/* Configure PackeTwin DMA */
		अगर (priv->type == TYPE_TWIN) अणु
			outb((priv->param.dma ==
			      1) ? TWIN_DMA_HDX_R1 : TWIN_DMA_HDX_R3,
			     priv->card_base + TWIN_DMA_CFG);
		पूर्ण
		/* Sp. cond. पूर्णांकr. only, ext पूर्णांक enable, RX DMA enable */
		ग_लिखो_scc(priv, R1, EXT_INT_ENAB | INT_ERR_Rx |
			  WT_RDY_RT | WT_FN_RDYFN | WT_RDY_ENAB);
	पूर्ण अन्यथा अणु
		/* Reset current frame */
		priv->rx_ptr = 0;
		/* Intr. on all Rx अक्षरacters and Sp. cond., ext पूर्णांक enable */
		ग_लिखो_scc(priv, R1, EXT_INT_ENAB | INT_ALL_Rx | WT_RDY_RT |
			  WT_FN_RDYFN);
	पूर्ण
	ग_लिखो_scc(priv, R0, ERR_RES);
	ग_लिखो_scc(priv, R3, RxENABLE | Rx8 | RxCRC_ENAB);
पूर्ण


अटल अंतरभूत व्योम rx_off(काष्ठा scc_priv *priv)
अणु
	/* Disable receiver */
	ग_लिखो_scc(priv, R3, Rx8);
	/* Disable DREQ / RX पूर्णांकerrupt */
	अगर (priv->param.dma >= 0 && priv->type == TYPE_TWIN)
		outb(0, priv->card_base + TWIN_DMA_CFG);
	अन्यथा
		ग_लिखो_scc(priv, R1, EXT_INT_ENAB | WT_FN_RDYFN);
	/* Disable DMA */
	अगर (priv->param.dma >= 0)
		disable_dma(priv->param.dma);
पूर्ण


अटल व्योम start_समयr(काष्ठा scc_priv *priv, पूर्णांक t, पूर्णांक r15)
अणु
	outb(priv->पंचांगr_mode, priv->पंचांगr_ctrl);
	अगर (t == 0) अणु
		पंचांग_isr(priv);
	पूर्ण अन्यथा अगर (t > 0) अणु
		outb(t & 0xFF, priv->पंचांगr_cnt);
		outb((t >> 8) & 0xFF, priv->पंचांगr_cnt);
		अगर (priv->type != TYPE_TWIN) अणु
			ग_लिखो_scc(priv, R15, r15 | CTSIE);
			priv->rr0 |= CTS;
		पूर्ण
	पूर्ण
पूर्ण


अटल अंतरभूत अचिन्हित अक्षर अक्रमom(व्योम)
अणु
	/* See "Numerical Recipes in C", second edition, p. 284 */
	अक्रम = अक्रम * 1664525L + 1013904223L;
	वापस (अचिन्हित अक्षर) (अक्रम >> 24);
पूर्ण

अटल अंतरभूत व्योम z8530_isr(काष्ठा scc_info *info)
अणु
	पूर्णांक is, i = 100;

	जबतक ((is = पढ़ो_scc(&info->priv[0], R3)) && i--) अणु
		अगर (is & CHARxIP) अणु
			rx_isr(&info->priv[0]);
		पूर्ण अन्यथा अगर (is & CHATxIP) अणु
			tx_isr(&info->priv[0]);
		पूर्ण अन्यथा अगर (is & CHAEXT) अणु
			es_isr(&info->priv[0]);
		पूर्ण अन्यथा अगर (is & CHBRxIP) अणु
			rx_isr(&info->priv[1]);
		पूर्ण अन्यथा अगर (is & CHBTxIP) अणु
			tx_isr(&info->priv[1]);
		पूर्ण अन्यथा अणु
			es_isr(&info->priv[1]);
		पूर्ण
		ग_लिखो_scc(&info->priv[0], R0, RES_H_IUS);
		i++;
	पूर्ण
	अगर (i < 0) अणु
		prपूर्णांकk(KERN_ERR "dmascc: stuck in ISR with RR3=0x%02x.\n",
		       is);
	पूर्ण
	/* Ok, no पूर्णांकerrupts pending from this 8530. The INT line should
	   be inactive now. */
पूर्ण


अटल irqवापस_t scc_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा scc_info *info = dev_id;

	spin_lock(info->priv[0].रेजिस्टर_lock);
	/* At this poपूर्णांक पूर्णांकerrupts are enabled, and the पूर्णांकerrupt under service
	   is alपढ़ोy acknowledged, but masked off.

	   Interrupt processing: We loop until we know that the IRQ line is
	   low. If another positive edge occurs afterwards during the ISR,
	   another पूर्णांकerrupt will be triggered by the पूर्णांकerrupt controller
	   as soon as the IRQ level is enabled again (see यंत्र/irq.h).

	   Bottom-half handlers will be processed after scc_isr(). This is
	   important, since we only have small ringbuffers and want new data
	   to be fetched/delivered immediately. */

	अगर (info->priv[0].type == TYPE_TWIN) अणु
		पूर्णांक is, card_base = info->priv[0].card_base;
		जबतक ((is = ~inb(card_base + TWIN_INT_REG)) &
		       TWIN_INT_MSK) अणु
			अगर (is & TWIN_SCC_MSK) अणु
				z8530_isr(info);
			पूर्ण अन्यथा अगर (is & TWIN_TMR1_MSK) अणु
				inb(card_base + TWIN_CLR_TMR1);
				पंचांग_isr(&info->priv[0]);
			पूर्ण अन्यथा अणु
				inb(card_base + TWIN_CLR_TMR2);
				पंचांग_isr(&info->priv[1]);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा
		z8530_isr(info);
	spin_unlock(info->priv[0].रेजिस्टर_lock);
	वापस IRQ_HANDLED;
पूर्ण


अटल व्योम rx_isr(काष्ठा scc_priv *priv)
अणु
	अगर (priv->param.dma >= 0) अणु
		/* Check special condition and perक्रमm error reset. See 2.4.7.5. */
		special_condition(priv, पढ़ो_scc(priv, R1));
		ग_लिखो_scc(priv, R0, ERR_RES);
	पूर्ण अन्यथा अणु
		/* Check special condition क्रम each अक्षरacter. Error reset not necessary.
		   Same algorithm क्रम SCC and ESCC. See 2.4.7.1 and 2.4.7.4. */
		पूर्णांक rc;
		जबतक (पढ़ो_scc(priv, R0) & Rx_CH_AV) अणु
			rc = पढ़ो_scc(priv, R1);
			अगर (priv->rx_ptr < BUF_SIZE)
				priv->rx_buf[priv->rx_head][priv->
							    rx_ptr++] =
				    पढ़ो_scc_data(priv);
			अन्यथा अणु
				priv->rx_over = 2;
				पढ़ो_scc_data(priv);
			पूर्ण
			special_condition(priv, rc);
		पूर्ण
	पूर्ण
पूर्ण


अटल व्योम special_condition(काष्ठा scc_priv *priv, पूर्णांक rc)
अणु
	पूर्णांक cb;
	अचिन्हित दीर्घ flags;

	/* See Figure 2-15. Only overrun and खातापूर्ण need to be checked. */

	अगर (rc & Rx_OVR) अणु
		/* Receiver overrun */
		priv->rx_over = 1;
		अगर (priv->param.dma < 0)
			ग_लिखो_scc(priv, R0, ERR_RES);
	पूर्ण अन्यथा अगर (rc & END_FR) अणु
		/* End of frame. Get byte count */
		अगर (priv->param.dma >= 0) अणु
			flags = claim_dma_lock();
			cb = BUF_SIZE - get_dma_residue(priv->param.dma) -
			    2;
			release_dma_lock(flags);
		पूर्ण अन्यथा अणु
			cb = priv->rx_ptr - 2;
		पूर्ण
		अगर (priv->rx_over) अणु
			/* We had an overrun */
			priv->dev->stats.rx_errors++;
			अगर (priv->rx_over == 2)
				priv->dev->stats.rx_length_errors++;
			अन्यथा
				priv->dev->stats.rx_fअगरo_errors++;
			priv->rx_over = 0;
		पूर्ण अन्यथा अगर (rc & CRC_ERR) अणु
			/* Count invalid CRC only अगर packet length >= minimum */
			अगर (cb >= 15) अणु
				priv->dev->stats.rx_errors++;
				priv->dev->stats.rx_crc_errors++;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (cb >= 15) अणु
				अगर (priv->rx_count < NUM_RX_BUF - 1) अणु
					/* Put good frame in FIFO */
					priv->rx_len[priv->rx_head] = cb;
					priv->rx_head =
					    (priv->rx_head +
					     1) % NUM_RX_BUF;
					priv->rx_count++;
					schedule_work(&priv->rx_work);
				पूर्ण अन्यथा अणु
					priv->dev->stats.rx_errors++;
					priv->dev->stats.rx_over_errors++;
				पूर्ण
			पूर्ण
		पूर्ण
		/* Get पढ़ोy क्रम new frame */
		अगर (priv->param.dma >= 0) अणु
			flags = claim_dma_lock();
			set_dma_addr(priv->param.dma,
				     (पूर्णांक) priv->rx_buf[priv->rx_head]);
			set_dma_count(priv->param.dma, BUF_SIZE);
			release_dma_lock(flags);
		पूर्ण अन्यथा अणु
			priv->rx_ptr = 0;
		पूर्ण
	पूर्ण
पूर्ण


अटल व्योम rx_bh(काष्ठा work_काष्ठा *ugli_api)
अणु
	काष्ठा scc_priv *priv = container_of(ugli_api, काष्ठा scc_priv, rx_work);
	पूर्णांक i = priv->rx_tail;
	पूर्णांक cb;
	अचिन्हित दीर्घ flags;
	काष्ठा sk_buff *skb;
	अचिन्हित अक्षर *data;

	spin_lock_irqsave(&priv->ring_lock, flags);
	जबतक (priv->rx_count) अणु
		spin_unlock_irqrestore(&priv->ring_lock, flags);
		cb = priv->rx_len[i];
		/* Allocate buffer */
		skb = dev_alloc_skb(cb + 1);
		अगर (skb == शून्य) अणु
			/* Drop packet */
			priv->dev->stats.rx_dropped++;
		पूर्ण अन्यथा अणु
			/* Fill buffer */
			data = skb_put(skb, cb + 1);
			data[0] = 0;
			स_नकल(&data[1], priv->rx_buf[i], cb);
			skb->protocol = ax25_type_trans(skb, priv->dev);
			netअगर_rx(skb);
			priv->dev->stats.rx_packets++;
			priv->dev->stats.rx_bytes += cb;
		पूर्ण
		spin_lock_irqsave(&priv->ring_lock, flags);
		/* Move tail */
		priv->rx_tail = i = (i + 1) % NUM_RX_BUF;
		priv->rx_count--;
	पूर्ण
	spin_unlock_irqrestore(&priv->ring_lock, flags);
पूर्ण


अटल व्योम tx_isr(काष्ठा scc_priv *priv)
अणु
	पूर्णांक i = priv->tx_tail, p = priv->tx_ptr;

	/* Suspend TX पूर्णांकerrupts अगर we करोn't want to send anything.
	   See Figure 2-22. */
	अगर (p == priv->tx_len[i]) अणु
		ग_लिखो_scc(priv, R0, RES_Tx_P);
		वापस;
	पूर्ण

	/* Write अक्षरacters */
	जबतक ((पढ़ो_scc(priv, R0) & Tx_BUF_EMP) && p < priv->tx_len[i]) अणु
		ग_लिखो_scc_data(priv, priv->tx_buf[i][p++], 0);
	पूर्ण

	/* Reset EOM latch of Z8530 */
	अगर (!priv->tx_ptr && p && priv->chip == Z8530)
		ग_लिखो_scc(priv, R0, RES_EOM_L);

	priv->tx_ptr = p;
पूर्ण


अटल व्योम es_isr(काष्ठा scc_priv *priv)
अणु
	पूर्णांक i, rr0, drr0, res;
	अचिन्हित दीर्घ flags;

	/* Read status, reset पूर्णांकerrupt bit (खोलो latches) */
	rr0 = पढ़ो_scc(priv, R0);
	ग_लिखो_scc(priv, R0, RES_EXT_INT);
	drr0 = priv->rr0 ^ rr0;
	priv->rr0 = rr0;

	/* Transmit underrun (2.4.9.6). We can't check the TxEOM flag, since
	   it might have alपढ़ोy been cleared again by AUTOEOM. */
	अगर (priv->state == TX_DATA) अणु
		/* Get reमुख्यing bytes */
		i = priv->tx_tail;
		अगर (priv->param.dma >= 0) अणु
			disable_dma(priv->param.dma);
			flags = claim_dma_lock();
			res = get_dma_residue(priv->param.dma);
			release_dma_lock(flags);
		पूर्ण अन्यथा अणु
			res = priv->tx_len[i] - priv->tx_ptr;
			priv->tx_ptr = 0;
		पूर्ण
		/* Disable DREQ / TX पूर्णांकerrupt */
		अगर (priv->param.dma >= 0 && priv->type == TYPE_TWIN)
			outb(0, priv->card_base + TWIN_DMA_CFG);
		अन्यथा
			ग_लिखो_scc(priv, R1, EXT_INT_ENAB | WT_FN_RDYFN);
		अगर (res) अणु
			/* Update packet statistics */
			priv->dev->stats.tx_errors++;
			priv->dev->stats.tx_fअगरo_errors++;
			/* Other underrun पूर्णांकerrupts may alपढ़ोy be रुकोing */
			ग_लिखो_scc(priv, R0, RES_EXT_INT);
			ग_लिखो_scc(priv, R0, RES_EXT_INT);
		पूर्ण अन्यथा अणु
			/* Update packet statistics */
			priv->dev->stats.tx_packets++;
			priv->dev->stats.tx_bytes += priv->tx_len[i];
			/* Remove frame from FIFO */
			priv->tx_tail = (i + 1) % NUM_TX_BUF;
			priv->tx_count--;
			/* Inक्रमm upper layers */
			netअगर_wake_queue(priv->dev);
		पूर्ण
		/* Switch state */
		ग_लिखो_scc(priv, R15, 0);
		अगर (priv->tx_count &&
		    (jअगरfies - priv->tx_start) < priv->param.txसमयout) अणु
			priv->state = TX_PAUSE;
			start_समयr(priv, priv->param.txछोड़ो, 0);
		पूर्ण अन्यथा अणु
			priv->state = TX_TAIL;
			start_समयr(priv, priv->param.txtail, 0);
		पूर्ण
	पूर्ण

	/* DCD transition */
	अगर (drr0 & DCD) अणु
		अगर (rr0 & DCD) अणु
			चयन (priv->state) अणु
			हाल IDLE:
			हाल WAIT:
				priv->state = DCD_ON;
				ग_लिखो_scc(priv, R15, 0);
				start_समयr(priv, priv->param.dcकरोn, 0);
			पूर्ण
		पूर्ण अन्यथा अणु
			चयन (priv->state) अणु
			हाल RX_ON:
				rx_off(priv);
				priv->state = DCD_OFF;
				ग_लिखो_scc(priv, R15, 0);
				start_समयr(priv, priv->param.dcकरोff, 0);
			पूर्ण
		पूर्ण
	पूर्ण

	/* CTS transition */
	अगर ((drr0 & CTS) && (~rr0 & CTS) && priv->type != TYPE_TWIN)
		पंचांग_isr(priv);

पूर्ण


अटल व्योम पंचांग_isr(काष्ठा scc_priv *priv)
अणु
	चयन (priv->state) अणु
	हाल TX_HEAD:
	हाल TX_PAUSE:
		tx_on(priv);
		priv->state = TX_DATA;
		अवरोध;
	हाल TX_TAIL:
		ग_लिखो_scc(priv, R5, TxCRC_ENAB | Tx8);
		priv->state = RTS_OFF;
		अगर (priv->type != TYPE_TWIN)
			ग_लिखो_scc(priv, R15, 0);
		start_समयr(priv, priv->param.rtsoff, 0);
		अवरोध;
	हाल RTS_OFF:
		ग_लिखो_scc(priv, R15, DCDIE);
		priv->rr0 = पढ़ो_scc(priv, R0);
		अगर (priv->rr0 & DCD) अणु
			priv->dev->stats.collisions++;
			rx_on(priv);
			priv->state = RX_ON;
		पूर्ण अन्यथा अणु
			priv->state = WAIT;
			start_समयr(priv, priv->param.रुकोसमय, DCDIE);
		पूर्ण
		अवरोध;
	हाल WAIT:
		अगर (priv->tx_count) अणु
			priv->state = TX_HEAD;
			priv->tx_start = jअगरfies;
			ग_लिखो_scc(priv, R5,
				  TxCRC_ENAB | RTS | TxENAB | Tx8);
			ग_लिखो_scc(priv, R15, 0);
			start_समयr(priv, priv->param.txdelay, 0);
		पूर्ण अन्यथा अणु
			priv->state = IDLE;
			अगर (priv->type != TYPE_TWIN)
				ग_लिखो_scc(priv, R15, DCDIE);
		पूर्ण
		अवरोध;
	हाल DCD_ON:
	हाल DCD_OFF:
		ग_लिखो_scc(priv, R15, DCDIE);
		priv->rr0 = पढ़ो_scc(priv, R0);
		अगर (priv->rr0 & DCD) अणु
			rx_on(priv);
			priv->state = RX_ON;
		पूर्ण अन्यथा अणु
			priv->state = WAIT;
			start_समयr(priv,
				    अक्रमom() / priv->param.persist *
				    priv->param.slotसमय, DCDIE);
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण
