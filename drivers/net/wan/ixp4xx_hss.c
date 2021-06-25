<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Intel IXP4xx HSS (synchronous serial port) driver क्रम Linux
 *
 * Copyright (C) 2007-2008 Krzysztof Haधasa <khc@pm.waw.pl>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/bitops.h>
#समावेश <linux/cdev.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/fs.h>
#समावेश <linux/hdlc.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/platक्रमm_data/wan_ixp4xx_hss.h>
#समावेश <linux/poll.h>
#समावेश <linux/slab.h>
#समावेश <linux/soc/ixp4xx/npe.h>
#समावेश <linux/soc/ixp4xx/qmgr.h>

#घोषणा DEBUG_DESC		0
#घोषणा DEBUG_RX		0
#घोषणा DEBUG_TX		0
#घोषणा DEBUG_PKT_BYTES		0
#घोषणा DEBUG_CLOSE		0

#घोषणा DRV_NAME		"ixp4xx_hss"

#घोषणा PKT_EXTRA_FLAGS		0 /* orig 1 */
#घोषणा PKT_NUM_PIPES		1 /* 1, 2 or 4 */
#घोषणा PKT_PIPE_FIFO_SIZEW	4 /* total 4 dwords per HSS */

#घोषणा RX_DESCS		16 /* also length of all RX queues */
#घोषणा TX_DESCS		16 /* also length of all TX queues */

#घोषणा POOL_ALLOC_SIZE		(माप(काष्ठा desc) * (RX_DESCS + TX_DESCS))
#घोषणा RX_SIZE			(HDLC_MAX_MRU + 4) /* NPE needs more space */
#घोषणा MAX_CLOSE_WAIT		1000 /* microseconds */
#घोषणा HSS_COUNT		2
#घोषणा FRAME_SIZE		256 /* करोesn't matter at this poपूर्णांक */
#घोषणा FRAME_OFFSET		0
#घोषणा MAX_CHANNELS		(FRAME_SIZE / 8)

#घोषणा NAPI_WEIGHT		16

/* Queue IDs */
#घोषणा HSS0_CHL_RXTRIG_QUEUE	12	/* orig size = 32 dwords */
#घोषणा HSS0_PKT_RX_QUEUE	13	/* orig size = 32 dwords */
#घोषणा HSS0_PKT_TX0_QUEUE	14	/* orig size = 16 dwords */
#घोषणा HSS0_PKT_TX1_QUEUE	15
#घोषणा HSS0_PKT_TX2_QUEUE	16
#घोषणा HSS0_PKT_TX3_QUEUE	17
#घोषणा HSS0_PKT_RXFREE0_QUEUE	18	/* orig size = 16 dwords */
#घोषणा HSS0_PKT_RXFREE1_QUEUE	19
#घोषणा HSS0_PKT_RXFREE2_QUEUE	20
#घोषणा HSS0_PKT_RXFREE3_QUEUE	21
#घोषणा HSS0_PKT_TXDONE_QUEUE	22	/* orig size = 64 dwords */

#घोषणा HSS1_CHL_RXTRIG_QUEUE	10
#घोषणा HSS1_PKT_RX_QUEUE	0
#घोषणा HSS1_PKT_TX0_QUEUE	5
#घोषणा HSS1_PKT_TX1_QUEUE	6
#घोषणा HSS1_PKT_TX2_QUEUE	7
#घोषणा HSS1_PKT_TX3_QUEUE	8
#घोषणा HSS1_PKT_RXFREE0_QUEUE	1
#घोषणा HSS1_PKT_RXFREE1_QUEUE	2
#घोषणा HSS1_PKT_RXFREE2_QUEUE	3
#घोषणा HSS1_PKT_RXFREE3_QUEUE	4
#घोषणा HSS1_PKT_TXDONE_QUEUE	9

#घोषणा NPE_PKT_MODE_HDLC		0
#घोषणा NPE_PKT_MODE_RAW		1
#घोषणा NPE_PKT_MODE_56KMODE		2
#घोषणा NPE_PKT_MODE_56KENDIAN_MSB	4

/* PKT_PIPE_HDLC_CFG_WRITE flags */
#घोषणा PKT_HDLC_IDLE_ONES		0x1 /* शेष = flags */
#घोषणा PKT_HDLC_CRC_32			0x2 /* शेष = CRC-16 */
#घोषणा PKT_HDLC_MSB_ENDIAN		0x4 /* शेष = LE */


/* hss_config, PCRs */
/* Frame sync sampling, शेष = active low */
#घोषणा PCR_FRM_SYNC_ACTIVE_HIGH	0x40000000
#घोषणा PCR_FRM_SYNC_FALLINGEDGE	0x80000000
#घोषणा PCR_FRM_SYNC_RISINGEDGE		0xC0000000

/* Frame sync pin: input (शेष) or output generated off a given clk edge */
#घोषणा PCR_FRM_SYNC_OUTPUT_FALLING	0x20000000
#घोषणा PCR_FRM_SYNC_OUTPUT_RISING	0x30000000

/* Frame and data घड़ी sampling on edge, शेष = falling */
#घोषणा PCR_FCLK_EDGE_RISING		0x08000000
#घोषणा PCR_DCLK_EDGE_RISING		0x04000000

/* Clock direction, शेष = input */
#घोषणा PCR_SYNC_CLK_सूची_OUTPUT		0x02000000

/* Generate/Receive frame pulses, शेष = enabled */
#घोषणा PCR_FRM_PULSE_DISABLED		0x01000000

 /* Data rate is full (शेष) or half the configured clk speed */
#घोषणा PCR_HALF_CLK_RATE		0x00200000

/* Invert data between NPE and HSS FIFOs? (शेष = no) */
#घोषणा PCR_DATA_POLARITY_INVERT	0x00100000

/* TX/RX endianness, शेष = LSB */
#घोषणा PCR_MSB_ENDIAN			0x00080000

/* Normal (शेष) / खोलो drain mode (TX only) */
#घोषणा PCR_TX_PINS_OPEN_DRAIN		0x00040000

/* No framing bit transmitted and expected on RX? (शेष = framing bit) */
#घोषणा PCR_SOF_NO_FBIT			0x00020000

/* Drive data pins? */
#घोषणा PCR_TX_DATA_ENABLE		0x00010000

/* Voice 56k type: drive the data pins low (शेष), high, high Z */
#घोषणा PCR_TX_V56K_HIGH		0x00002000
#घोषणा PCR_TX_V56K_HIGH_IMP		0x00004000

/* Unasचिन्हित type: drive the data pins low (शेष), high, high Z */
#घोषणा PCR_TX_UNASS_HIGH		0x00000800
#घोषणा PCR_TX_UNASS_HIGH_IMP		0x00001000

/* T1 @ 1.544MHz only: Fbit dictated in FIFO (शेष) or high Z */
#घोषणा PCR_TX_FB_HIGH_IMP		0x00000400

/* 56k data endiannes - which bit unused: high (शेष) or low */
#घोषणा PCR_TX_56KE_BIT_0_UNUSED	0x00000200

/* 56k data transmission type: 32/8 bit data (शेष) or 56K data */
#घोषणा PCR_TX_56KS_56K_DATA		0x00000100

/* hss_config, cCR */
/* Number of packetized clients, शेष = 1 */
#घोषणा CCR_NPE_HFIFO_2_HDLC		0x04000000
#घोषणा CCR_NPE_HFIFO_3_OR_4HDLC	0x08000000

/* शेष = no loopback */
#घोषणा CCR_LOOPBACK			0x02000000

/* HSS number, शेष = 0 (first) */
#घोषणा CCR_SECOND_HSS			0x01000000


/* hss_config, clkCR: मुख्य:10, num:10, denom:12 */
#घोषणा CLK42X_SPEED_EXP	((0x3FF << 22) | (  2 << 12) |   15) /*65 KHz*/

#घोषणा CLK42X_SPEED_512KHZ	((  130 << 22) | (  2 << 12) |   15)
#घोषणा CLK42X_SPEED_1536KHZ	((   43 << 22) | ( 18 << 12) |   47)
#घोषणा CLK42X_SPEED_1544KHZ	((   43 << 22) | ( 33 << 12) |  192)
#घोषणा CLK42X_SPEED_2048KHZ	((   32 << 22) | ( 34 << 12) |   63)
#घोषणा CLK42X_SPEED_4096KHZ	((   16 << 22) | ( 34 << 12) |  127)
#घोषणा CLK42X_SPEED_8192KHZ	((    8 << 22) | ( 34 << 12) |  255)

#घोषणा CLK46X_SPEED_512KHZ	((  130 << 22) | ( 24 << 12) |  127)
#घोषणा CLK46X_SPEED_1536KHZ	((   43 << 22) | (152 << 12) |  383)
#घोषणा CLK46X_SPEED_1544KHZ	((   43 << 22) | ( 66 << 12) |  385)
#घोषणा CLK46X_SPEED_2048KHZ	((   32 << 22) | (280 << 12) |  511)
#घोषणा CLK46X_SPEED_4096KHZ	((   16 << 22) | (280 << 12) | 1023)
#घोषणा CLK46X_SPEED_8192KHZ	((    8 << 22) | (280 << 12) | 2047)

/*
 * HSS_CONFIG_CLOCK_CR रेजिस्टर consists of 3 parts:
 *     A (10 bits), B (10 bits) and C (12 bits).
 * IXP42x HSS घड़ी generator operation (verअगरied with an oscilloscope):
 * Each घड़ी bit takes 7.5 ns (1 / 133.xx MHz).
 * The घड़ी sequence consists of (C - B) states of 0s and 1s, each state is
 * A bits wide. It's followed by (B + 1) states of 0s and 1s, each state is
 * (A + 1) bits wide.
 *
 * The resulting average घड़ी frequency (assuming 33.333 MHz oscillator) is:
 * freq = 66.666 MHz / (A + (B + 1) / (C + 1))
 * minimum freq = 66.666 MHz / (A + 1)
 * maximum freq = 66.666 MHz / A
 *
 * Example: A = 2, B = 2, C = 7, CLOCK_CR रेजिस्टर = 2 << 22 | 2 << 12 | 7
 * freq = 66.666 MHz / (2 + (2 + 1) / (7 + 1)) = 28.07 MHz (Mb/s).
 * The घड़ी sequence is: 1100110011 (5 द्विगुनs) 000111000 (3 triples).
 * The sequence takes (C - B) * A + (B + 1) * (A + 1) = 5 * 2 + 3 * 3 bits
 * = 19 bits (each 7.5 ns दीर्घ) = 142.5 ns (then the sequence repeats).
 * The sequence consists of 4 complete घड़ी periods, thus the average
 * frequency (= घड़ी rate) is 4 / 142.5 ns = 28.07 MHz (Mb/s).
 * (max specअगरied घड़ी rate क्रम IXP42x HSS is 8.192 Mb/s).
 */

/* hss_config, LUT entries */
#घोषणा TDMMAP_UNASSIGNED	0
#घोषणा TDMMAP_HDLC		1	/* HDLC - packetized */
#घोषणा TDMMAP_VOICE56K		2	/* Voice56K - 7-bit channelized */
#घोषणा TDMMAP_VOICE64K		3	/* Voice64K - 8-bit channelized */

/* offsets पूर्णांकo HSS config */
#घोषणा HSS_CONFIG_TX_PCR	0x00 /* port configuration रेजिस्टरs */
#घोषणा HSS_CONFIG_RX_PCR	0x04
#घोषणा HSS_CONFIG_CORE_CR	0x08 /* loopback control, HSS# */
#घोषणा HSS_CONFIG_CLOCK_CR	0x0C /* घड़ी generator control */
#घोषणा HSS_CONFIG_TX_FCR	0x10 /* frame configuration रेजिस्टरs */
#घोषणा HSS_CONFIG_RX_FCR	0x14
#घोषणा HSS_CONFIG_TX_LUT	0x18 /* channel look-up tables */
#घोषणा HSS_CONFIG_RX_LUT	0x38


/* NPE command codes */
/* ग_लिखोs the ConfigWord value to the location specअगरied by offset */
#घोषणा PORT_CONFIG_WRITE		0x40

/* triggers the NPE to load the contents of the configuration table */
#घोषणा PORT_CONFIG_LOAD		0x41

/* triggers the NPE to वापस an HssErrorReadResponse message */
#घोषणा PORT_ERROR_READ			0x42

/* triggers the NPE to reset पूर्णांकernal status and enable the HssPacketized
   operation क्रम the flow specअगरied by pPipe */
#घोषणा PKT_PIPE_FLOW_ENABLE		0x50
#घोषणा PKT_PIPE_FLOW_DISABLE		0x51
#घोषणा PKT_NUM_PIPES_WRITE		0x52
#घोषणा PKT_PIPE_FIFO_SIZEW_WRITE	0x53
#घोषणा PKT_PIPE_HDLC_CFG_WRITE		0x54
#घोषणा PKT_PIPE_IDLE_PATTERN_WRITE	0x55
#घोषणा PKT_PIPE_RX_SIZE_WRITE		0x56
#घोषणा PKT_PIPE_MODE_WRITE		0x57

/* HDLC packet status values - desc->status */
#घोषणा ERR_SHUTDOWN		1 /* stop or shutकरोwn occurrence */
#घोषणा ERR_HDLC_ALIGN		2 /* HDLC alignment error */
#घोषणा ERR_HDLC_FCS		3 /* HDLC Frame Check Sum error */
#घोषणा ERR_RXFREE_Q_EMPTY	4 /* RX-मुक्त queue became empty जबतक receiving
				     this packet (अगर buf_len < pkt_len) */
#घोषणा ERR_HDLC_TOO_LONG	5 /* HDLC frame size too दीर्घ */
#घोषणा ERR_HDLC_ABORT		6 /* पात sequence received */
#घोषणा ERR_DISCONNECTING	7 /* disconnect is in progress */


#अगर_घोषित __ARMEB__
प्रकार काष्ठा sk_buff buffer_t;
#घोषणा मुक्त_buffer dev_kमुक्त_skb
#घोषणा मुक्त_buffer_irq dev_consume_skb_irq
#अन्यथा
प्रकार व्योम buffer_t;
#घोषणा मुक्त_buffer kमुक्त
#घोषणा मुक्त_buffer_irq kमुक्त
#पूर्ण_अगर

काष्ठा port अणु
	काष्ठा device *dev;
	काष्ठा npe *npe;
	काष्ठा net_device *netdev;
	काष्ठा napi_काष्ठा napi;
	काष्ठा hss_plat_info *plat;
	buffer_t *rx_buff_tab[RX_DESCS], *tx_buff_tab[TX_DESCS];
	काष्ठा desc *desc_tab;	/* coherent */
	dma_addr_t desc_tab_phys;
	अचिन्हित पूर्णांक id;
	अचिन्हित पूर्णांक घड़ी_प्रकारype, घड़ी_rate, loopback;
	अचिन्हित पूर्णांक initialized, carrier;
	u8 hdlc_cfg;
	u32 घड़ी_reg;
पूर्ण;

/* NPE message काष्ठाure */
काष्ठा msg अणु
#अगर_घोषित __ARMEB__
	u8 cmd, unused, hss_port, index;
	जोड़ अणु
		काष्ठा अणु u8 data8a, data8b, data8c, data8d; पूर्ण;
		काष्ठा अणु u16 data16a, data16b; पूर्ण;
		काष्ठा अणु u32 data32; पूर्ण;
	पूर्ण;
#अन्यथा
	u8 index, hss_port, unused, cmd;
	जोड़ अणु
		काष्ठा अणु u8 data8d, data8c, data8b, data8a; पूर्ण;
		काष्ठा अणु u16 data16b, data16a; पूर्ण;
		काष्ठा अणु u32 data32; पूर्ण;
	पूर्ण;
#पूर्ण_अगर
पूर्ण;

/* HDLC packet descriptor */
काष्ठा desc अणु
	u32 next;		/* poपूर्णांकer to next buffer, unused */

#अगर_घोषित __ARMEB__
	u16 buf_len;		/* buffer length */
	u16 pkt_len;		/* packet length */
	u32 data;		/* poपूर्णांकer to data buffer in RAM */
	u8 status;
	u8 error_count;
	u16 __reserved;
#अन्यथा
	u16 pkt_len;		/* packet length */
	u16 buf_len;		/* buffer length */
	u32 data;		/* poपूर्णांकer to data buffer in RAM */
	u16 __reserved;
	u8 error_count;
	u8 status;
#पूर्ण_अगर
	u32 __reserved1[4];
पूर्ण;


#घोषणा rx_desc_phys(port, n)	((port)->desc_tab_phys +		\
				 (n) * माप(काष्ठा desc))
#घोषणा rx_desc_ptr(port, n)	(&(port)->desc_tab[n])

#घोषणा tx_desc_phys(port, n)	((port)->desc_tab_phys +		\
				 ((n) + RX_DESCS) * माप(काष्ठा desc))
#घोषणा tx_desc_ptr(port, n)	(&(port)->desc_tab[(n) + RX_DESCS])

/*****************************************************************************
 * global variables
 ****************************************************************************/

अटल पूर्णांक ports_खोलो;
अटल काष्ठा dma_pool *dma_pool;
अटल DEFINE_SPINLOCK(npe_lock);

अटल स्थिर काष्ठा अणु
	पूर्णांक tx, txकरोne, rx, rxमुक्त;
पूर्णqueue_ids[2] = अणुअणुHSS0_PKT_TX0_QUEUE, HSS0_PKT_TXDONE_QUEUE, HSS0_PKT_RX_QUEUE,
		  HSS0_PKT_RXFREE0_QUEUEपूर्ण,
		 अणुHSS1_PKT_TX0_QUEUE, HSS1_PKT_TXDONE_QUEUE, HSS1_PKT_RX_QUEUE,
		  HSS1_PKT_RXFREE0_QUEUEपूर्ण,
पूर्ण;

/*****************************************************************************
 * utility functions
 ****************************************************************************/

अटल अंतरभूत काष्ठा port* dev_to_port(काष्ठा net_device *dev)
अणु
	वापस dev_to_hdlc(dev)->priv;
पूर्ण

#अगर_अघोषित __ARMEB__
अटल अंतरभूत व्योम स_नकल_swab32(u32 *dest, u32 *src, पूर्णांक cnt)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < cnt; i++)
		dest[i] = swab32(src[i]);
पूर्ण
#पूर्ण_अगर

/*****************************************************************************
 * HSS access
 ****************************************************************************/

अटल व्योम hss_npe_send(काष्ठा port *port, काष्ठा msg *msg, स्थिर अक्षर* what)
अणु
	u32 *val = (u32*)msg;
	अगर (npe_send_message(port->npe, msg, what)) अणु
		pr_crit("HSS-%i: unable to send command [%08X:%08X] to %s\n",
			port->id, val[0], val[1], npe_name(port->npe));
		BUG();
	पूर्ण
पूर्ण

अटल व्योम hss_config_set_lut(काष्ठा port *port)
अणु
	काष्ठा msg msg;
	पूर्णांक ch;

	स_रखो(&msg, 0, माप(msg));
	msg.cmd = PORT_CONFIG_WRITE;
	msg.hss_port = port->id;

	क्रम (ch = 0; ch < MAX_CHANNELS; ch++) अणु
		msg.data32 >>= 2;
		msg.data32 |= TDMMAP_HDLC << 30;

		अगर (ch % 16 == 15) अणु
			msg.index = HSS_CONFIG_TX_LUT + ((ch / 4) & ~3);
			hss_npe_send(port, &msg, "HSS_SET_TX_LUT");

			msg.index += HSS_CONFIG_RX_LUT - HSS_CONFIG_TX_LUT;
			hss_npe_send(port, &msg, "HSS_SET_RX_LUT");
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम hss_config(काष्ठा port *port)
अणु
	काष्ठा msg msg;

	स_रखो(&msg, 0, माप(msg));
	msg.cmd = PORT_CONFIG_WRITE;
	msg.hss_port = port->id;
	msg.index = HSS_CONFIG_TX_PCR;
	msg.data32 = PCR_FRM_PULSE_DISABLED | PCR_MSB_ENDIAN |
		PCR_TX_DATA_ENABLE | PCR_SOF_NO_FBIT;
	अगर (port->घड़ी_प्रकारype == CLOCK_INT)
		msg.data32 |= PCR_SYNC_CLK_सूची_OUTPUT;
	hss_npe_send(port, &msg, "HSS_SET_TX_PCR");

	msg.index = HSS_CONFIG_RX_PCR;
	msg.data32 ^= PCR_TX_DATA_ENABLE | PCR_DCLK_EDGE_RISING;
	hss_npe_send(port, &msg, "HSS_SET_RX_PCR");

	स_रखो(&msg, 0, माप(msg));
	msg.cmd = PORT_CONFIG_WRITE;
	msg.hss_port = port->id;
	msg.index = HSS_CONFIG_CORE_CR;
	msg.data32 = (port->loopback ? CCR_LOOPBACK : 0) |
		(port->id ? CCR_SECOND_HSS : 0);
	hss_npe_send(port, &msg, "HSS_SET_CORE_CR");

	स_रखो(&msg, 0, माप(msg));
	msg.cmd = PORT_CONFIG_WRITE;
	msg.hss_port = port->id;
	msg.index = HSS_CONFIG_CLOCK_CR;
	msg.data32 = port->घड़ी_reg;
	hss_npe_send(port, &msg, "HSS_SET_CLOCK_CR");

	स_रखो(&msg, 0, माप(msg));
	msg.cmd = PORT_CONFIG_WRITE;
	msg.hss_port = port->id;
	msg.index = HSS_CONFIG_TX_FCR;
	msg.data16a = FRAME_OFFSET;
	msg.data16b = FRAME_SIZE - 1;
	hss_npe_send(port, &msg, "HSS_SET_TX_FCR");

	स_रखो(&msg, 0, माप(msg));
	msg.cmd = PORT_CONFIG_WRITE;
	msg.hss_port = port->id;
	msg.index = HSS_CONFIG_RX_FCR;
	msg.data16a = FRAME_OFFSET;
	msg.data16b = FRAME_SIZE - 1;
	hss_npe_send(port, &msg, "HSS_SET_RX_FCR");

	hss_config_set_lut(port);

	स_रखो(&msg, 0, माप(msg));
	msg.cmd = PORT_CONFIG_LOAD;
	msg.hss_port = port->id;
	hss_npe_send(port, &msg, "HSS_LOAD_CONFIG");

	अगर (npe_recv_message(port->npe, &msg, "HSS_LOAD_CONFIG") ||
	    /* HSS_LOAD_CONFIG क्रम port #1 वापसs port_id = #4 */
	    msg.cmd != PORT_CONFIG_LOAD || msg.data32) अणु
		pr_crit("HSS-%i: HSS_LOAD_CONFIG failed\n", port->id);
		BUG();
	पूर्ण

	/* HDLC may stop working without this - check FIXME */
	npe_recv_message(port->npe, &msg, "FLUSH_IT");
पूर्ण

अटल व्योम hss_set_hdlc_cfg(काष्ठा port *port)
अणु
	काष्ठा msg msg;

	स_रखो(&msg, 0, माप(msg));
	msg.cmd = PKT_PIPE_HDLC_CFG_WRITE;
	msg.hss_port = port->id;
	msg.data8a = port->hdlc_cfg; /* rx_cfg */
	msg.data8b = port->hdlc_cfg | (PKT_EXTRA_FLAGS << 3); /* tx_cfg */
	hss_npe_send(port, &msg, "HSS_SET_HDLC_CFG");
पूर्ण

अटल u32 hss_get_status(काष्ठा port *port)
अणु
	काष्ठा msg msg;

	स_रखो(&msg, 0, माप(msg));
	msg.cmd = PORT_ERROR_READ;
	msg.hss_port = port->id;
	hss_npe_send(port, &msg, "PORT_ERROR_READ");
	अगर (npe_recv_message(port->npe, &msg, "PORT_ERROR_READ")) अणु
		pr_crit("HSS-%i: unable to read HSS status\n", port->id);
		BUG();
	पूर्ण

	वापस msg.data32;
पूर्ण

अटल व्योम hss_start_hdlc(काष्ठा port *port)
अणु
	काष्ठा msg msg;

	स_रखो(&msg, 0, माप(msg));
	msg.cmd = PKT_PIPE_FLOW_ENABLE;
	msg.hss_port = port->id;
	msg.data32 = 0;
	hss_npe_send(port, &msg, "HSS_ENABLE_PKT_PIPE");
पूर्ण

अटल व्योम hss_stop_hdlc(काष्ठा port *port)
अणु
	काष्ठा msg msg;

	स_रखो(&msg, 0, माप(msg));
	msg.cmd = PKT_PIPE_FLOW_DISABLE;
	msg.hss_port = port->id;
	hss_npe_send(port, &msg, "HSS_DISABLE_PKT_PIPE");
	hss_get_status(port); /* make sure it's halted */
पूर्ण

अटल पूर्णांक hss_load_firmware(काष्ठा port *port)
अणु
	काष्ठा msg msg;
	पूर्णांक err;

	अगर (port->initialized)
		वापस 0;

	अगर (!npe_running(port->npe) &&
	    (err = npe_load_firmware(port->npe, npe_name(port->npe),
				     port->dev)))
		वापस err;

	/* HDLC mode configuration */
	स_रखो(&msg, 0, माप(msg));
	msg.cmd = PKT_NUM_PIPES_WRITE;
	msg.hss_port = port->id;
	msg.data8a = PKT_NUM_PIPES;
	hss_npe_send(port, &msg, "HSS_SET_PKT_PIPES");

	msg.cmd = PKT_PIPE_FIFO_SIZEW_WRITE;
	msg.data8a = PKT_PIPE_FIFO_SIZEW;
	hss_npe_send(port, &msg, "HSS_SET_PKT_FIFO");

	msg.cmd = PKT_PIPE_MODE_WRITE;
	msg.data8a = NPE_PKT_MODE_HDLC;
	/* msg.data8b = inv_mask */
	/* msg.data8c = or_mask */
	hss_npe_send(port, &msg, "HSS_SET_PKT_MODE");

	msg.cmd = PKT_PIPE_RX_SIZE_WRITE;
	msg.data16a = HDLC_MAX_MRU; /* including CRC */
	hss_npe_send(port, &msg, "HSS_SET_PKT_RX_SIZE");

	msg.cmd = PKT_PIPE_IDLE_PATTERN_WRITE;
	msg.data32 = 0x7F7F7F7F; /* ??? FIXME */
	hss_npe_send(port, &msg, "HSS_SET_PKT_IDLE");

	port->initialized = 1;
	वापस 0;
पूर्ण

/*****************************************************************************
 * packetized (HDLC) operation
 ****************************************************************************/

अटल अंतरभूत व्योम debug_pkt(काष्ठा net_device *dev, स्थिर अक्षर *func,
			     u8 *data, पूर्णांक len)
अणु
#अगर DEBUG_PKT_BYTES
	पूर्णांक i;

	prपूर्णांकk(KERN_DEBUG "%s: %s(%i)", dev->name, func, len);
	क्रम (i = 0; i < len; i++) अणु
		अगर (i >= DEBUG_PKT_BYTES)
			अवरोध;
		prपूर्णांकk("%s%02X", !(i % 4) ? " " : "", data[i]);
	पूर्ण
	prपूर्णांकk("\n");
#पूर्ण_अगर
पूर्ण


अटल अंतरभूत व्योम debug_desc(u32 phys, काष्ठा desc *desc)
अणु
#अगर DEBUG_DESC
	prपूर्णांकk(KERN_DEBUG "%X: %X %3X %3X %08X %X %X\n",
	       phys, desc->next, desc->buf_len, desc->pkt_len,
	       desc->data, desc->status, desc->error_count);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत पूर्णांक queue_get_desc(अचिन्हित पूर्णांक queue, काष्ठा port *port,
				 पूर्णांक is_tx)
अणु
	u32 phys, tab_phys, n_desc;
	काष्ठा desc *tab;

	अगर (!(phys = qmgr_get_entry(queue)))
		वापस -1;

	BUG_ON(phys & 0x1F);
	tab_phys = is_tx ? tx_desc_phys(port, 0) : rx_desc_phys(port, 0);
	tab = is_tx ? tx_desc_ptr(port, 0) : rx_desc_ptr(port, 0);
	n_desc = (phys - tab_phys) / माप(काष्ठा desc);
	BUG_ON(n_desc >= (is_tx ? TX_DESCS : RX_DESCS));
	debug_desc(phys, &tab[n_desc]);
	BUG_ON(tab[n_desc].next);
	वापस n_desc;
पूर्ण

अटल अंतरभूत व्योम queue_put_desc(अचिन्हित पूर्णांक queue, u32 phys,
				  काष्ठा desc *desc)
अणु
	debug_desc(phys, desc);
	BUG_ON(phys & 0x1F);
	qmgr_put_entry(queue, phys);
	/* Don't check for queue overflow here, we've allocated sufficient
	   length and queues >= 32 करोn't support this check anyway. */
पूर्ण


अटल अंतरभूत व्योम dma_unmap_tx(काष्ठा port *port, काष्ठा desc *desc)
अणु
#अगर_घोषित __ARMEB__
	dma_unmap_single(&port->netdev->dev, desc->data,
			 desc->buf_len, DMA_TO_DEVICE);
#अन्यथा
	dma_unmap_single(&port->netdev->dev, desc->data & ~3,
			 ALIGN((desc->data & 3) + desc->buf_len, 4),
			 DMA_TO_DEVICE);
#पूर्ण_अगर
पूर्ण


अटल व्योम hss_hdlc_set_carrier(व्योम *pdev, पूर्णांक carrier)
अणु
	काष्ठा net_device *netdev = pdev;
	काष्ठा port *port = dev_to_port(netdev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&npe_lock, flags);
	port->carrier = carrier;
	अगर (!port->loopback) अणु
		अगर (carrier)
			netअगर_carrier_on(netdev);
		अन्यथा
			netअगर_carrier_off(netdev);
	पूर्ण
	spin_unlock_irqrestore(&npe_lock, flags);
पूर्ण

अटल व्योम hss_hdlc_rx_irq(व्योम *pdev)
अणु
	काष्ठा net_device *dev = pdev;
	काष्ठा port *port = dev_to_port(dev);

#अगर DEBUG_RX
	prपूर्णांकk(KERN_DEBUG "%s: hss_hdlc_rx_irq\n", dev->name);
#पूर्ण_अगर
	qmgr_disable_irq(queue_ids[port->id].rx);
	napi_schedule(&port->napi);
पूर्ण

अटल पूर्णांक hss_hdlc_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा port *port = container_of(napi, काष्ठा port, napi);
	काष्ठा net_device *dev = port->netdev;
	अचिन्हित पूर्णांक rxq = queue_ids[port->id].rx;
	अचिन्हित पूर्णांक rxमुक्तq = queue_ids[port->id].rxमुक्त;
	पूर्णांक received = 0;

#अगर DEBUG_RX
	prपूर्णांकk(KERN_DEBUG "%s: hss_hdlc_poll\n", dev->name);
#पूर्ण_अगर

	जबतक (received < budget) अणु
		काष्ठा sk_buff *skb;
		काष्ठा desc *desc;
		पूर्णांक n;
#अगर_घोषित __ARMEB__
		काष्ठा sk_buff *temp;
		u32 phys;
#पूर्ण_अगर

		अगर ((n = queue_get_desc(rxq, port, 0)) < 0) अणु
#अगर DEBUG_RX
			prपूर्णांकk(KERN_DEBUG "%s: hss_hdlc_poll"
			       " napi_complete\n", dev->name);
#पूर्ण_अगर
			napi_complete(napi);
			qmgr_enable_irq(rxq);
			अगर (!qmgr_stat_empty(rxq) &&
			    napi_reschedule(napi)) अणु
#अगर DEBUG_RX
				prपूर्णांकk(KERN_DEBUG "%s: hss_hdlc_poll"
				       " napi_reschedule succeeded\n",
				       dev->name);
#पूर्ण_अगर
				qmgr_disable_irq(rxq);
				जारी;
			पूर्ण
#अगर DEBUG_RX
			prपूर्णांकk(KERN_DEBUG "%s: hss_hdlc_poll all done\n",
			       dev->name);
#पूर्ण_अगर
			वापस received; /* all work करोne */
		पूर्ण

		desc = rx_desc_ptr(port, n);
#अगर 0 /* FIXME - error_count counts modulo 256, perhaps we should use it */
		अगर (desc->error_count)
			prपूर्णांकk(KERN_DEBUG "%s: hss_hdlc_poll status 0x%02X"
			       " errors %u\n", dev->name, desc->status,
			       desc->error_count);
#पूर्ण_अगर
		skb = शून्य;
		चयन (desc->status) अणु
		हाल 0:
#अगर_घोषित __ARMEB__
			अगर ((skb = netdev_alloc_skb(dev, RX_SIZE)) != शून्य) अणु
				phys = dma_map_single(&dev->dev, skb->data,
						      RX_SIZE,
						      DMA_FROM_DEVICE);
				अगर (dma_mapping_error(&dev->dev, phys)) अणु
					dev_kमुक्त_skb(skb);
					skb = शून्य;
				पूर्ण
			पूर्ण
#अन्यथा
			skb = netdev_alloc_skb(dev, desc->pkt_len);
#पूर्ण_अगर
			अगर (!skb)
				dev->stats.rx_dropped++;
			अवरोध;
		हाल ERR_HDLC_ALIGN:
		हाल ERR_HDLC_ABORT:
			dev->stats.rx_frame_errors++;
			dev->stats.rx_errors++;
			अवरोध;
		हाल ERR_HDLC_FCS:
			dev->stats.rx_crc_errors++;
			dev->stats.rx_errors++;
			अवरोध;
		हाल ERR_HDLC_TOO_LONG:
			dev->stats.rx_length_errors++;
			dev->stats.rx_errors++;
			अवरोध;
		शेष:	/* FIXME - हटाओ prपूर्णांकk */
			netdev_err(dev, "hss_hdlc_poll: status 0x%02X errors %u\n",
				   desc->status, desc->error_count);
			dev->stats.rx_errors++;
		पूर्ण

		अगर (!skb) अणु
			/* put the desc back on RX-पढ़ोy queue */
			desc->buf_len = RX_SIZE;
			desc->pkt_len = desc->status = 0;
			queue_put_desc(rxमुक्तq, rx_desc_phys(port, n), desc);
			जारी;
		पूर्ण

		/* process received frame */
#अगर_घोषित __ARMEB__
		temp = skb;
		skb = port->rx_buff_tab[n];
		dma_unmap_single(&dev->dev, desc->data,
				 RX_SIZE, DMA_FROM_DEVICE);
#अन्यथा
		dma_sync_single_क्रम_cpu(&dev->dev, desc->data,
					RX_SIZE, DMA_FROM_DEVICE);
		स_नकल_swab32((u32 *)skb->data, (u32 *)port->rx_buff_tab[n],
			      ALIGN(desc->pkt_len, 4) / 4);
#पूर्ण_अगर
		skb_put(skb, desc->pkt_len);

		debug_pkt(dev, "hss_hdlc_poll", skb->data, skb->len);

		skb->protocol = hdlc_type_trans(skb, dev);
		dev->stats.rx_packets++;
		dev->stats.rx_bytes += skb->len;
		netअगर_receive_skb(skb);

		/* put the new buffer on RX-मुक्त queue */
#अगर_घोषित __ARMEB__
		port->rx_buff_tab[n] = temp;
		desc->data = phys;
#पूर्ण_अगर
		desc->buf_len = RX_SIZE;
		desc->pkt_len = 0;
		queue_put_desc(rxमुक्तq, rx_desc_phys(port, n), desc);
		received++;
	पूर्ण
#अगर DEBUG_RX
	prपूर्णांकk(KERN_DEBUG "hss_hdlc_poll: end, not all work done\n");
#पूर्ण_अगर
	वापस received;	/* not all work करोne */
पूर्ण


अटल व्योम hss_hdlc_txकरोne_irq(व्योम *pdev)
अणु
	काष्ठा net_device *dev = pdev;
	काष्ठा port *port = dev_to_port(dev);
	पूर्णांक n_desc;

#अगर DEBUG_TX
	prपूर्णांकk(KERN_DEBUG DRV_NAME ": hss_hdlc_txdone_irq\n");
#पूर्ण_अगर
	जबतक ((n_desc = queue_get_desc(queue_ids[port->id].txकरोne,
					port, 1)) >= 0) अणु
		काष्ठा desc *desc;
		पूर्णांक start;

		desc = tx_desc_ptr(port, n_desc);

		dev->stats.tx_packets++;
		dev->stats.tx_bytes += desc->pkt_len;

		dma_unmap_tx(port, desc);
#अगर DEBUG_TX
		prपूर्णांकk(KERN_DEBUG "%s: hss_hdlc_txdone_irq free %p\n",
		       dev->name, port->tx_buff_tab[n_desc]);
#पूर्ण_अगर
		मुक्त_buffer_irq(port->tx_buff_tab[n_desc]);
		port->tx_buff_tab[n_desc] = शून्य;

		start = qmgr_stat_below_low_watermark(port->plat->txपढ़ोyq);
		queue_put_desc(port->plat->txपढ़ोyq,
			       tx_desc_phys(port, n_desc), desc);
		अगर (start) अणु /* TX-पढ़ोy queue was empty */
#अगर DEBUG_TX
			prपूर्णांकk(KERN_DEBUG "%s: hss_hdlc_txdone_irq xmit"
			       " ready\n", dev->name);
#पूर्ण_अगर
			netअगर_wake_queue(dev);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक hss_hdlc_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा port *port = dev_to_port(dev);
	अचिन्हित पूर्णांक txपढ़ोyq = port->plat->txपढ़ोyq;
	पूर्णांक len, offset, bytes, n;
	व्योम *mem;
	u32 phys;
	काष्ठा desc *desc;

#अगर DEBUG_TX
	prपूर्णांकk(KERN_DEBUG "%s: hss_hdlc_xmit\n", dev->name);
#पूर्ण_अगर

	अगर (unlikely(skb->len > HDLC_MAX_MRU)) अणु
		dev_kमुक्त_skb(skb);
		dev->stats.tx_errors++;
		वापस NETDEV_TX_OK;
	पूर्ण

	debug_pkt(dev, "hss_hdlc_xmit", skb->data, skb->len);

	len = skb->len;
#अगर_घोषित __ARMEB__
	offset = 0; /* no need to keep alignment */
	bytes = len;
	mem = skb->data;
#अन्यथा
	offset = (पूर्णांक)skb->data & 3; /* keep 32-bit alignment */
	bytes = ALIGN(offset + len, 4);
	अगर (!(mem = kदो_स्मृति(bytes, GFP_ATOMIC))) अणु
		dev_kमुक्त_skb(skb);
		dev->stats.tx_dropped++;
		वापस NETDEV_TX_OK;
	पूर्ण
	स_नकल_swab32(mem, (u32 *)((uपूर्णांकptr_t)skb->data & ~3), bytes / 4);
	dev_kमुक्त_skb(skb);
#पूर्ण_अगर

	phys = dma_map_single(&dev->dev, mem, bytes, DMA_TO_DEVICE);
	अगर (dma_mapping_error(&dev->dev, phys)) अणु
#अगर_घोषित __ARMEB__
		dev_kमुक्त_skb(skb);
#अन्यथा
		kमुक्त(mem);
#पूर्ण_अगर
		dev->stats.tx_dropped++;
		वापस NETDEV_TX_OK;
	पूर्ण

	n = queue_get_desc(txपढ़ोyq, port, 1);
	BUG_ON(n < 0);
	desc = tx_desc_ptr(port, n);

#अगर_घोषित __ARMEB__
	port->tx_buff_tab[n] = skb;
#अन्यथा
	port->tx_buff_tab[n] = mem;
#पूर्ण_अगर
	desc->data = phys + offset;
	desc->buf_len = desc->pkt_len = len;

	wmb();
	queue_put_desc(queue_ids[port->id].tx, tx_desc_phys(port, n), desc);

	अगर (qmgr_stat_below_low_watermark(txपढ़ोyq)) अणु /* empty */
#अगर DEBUG_TX
		prपूर्णांकk(KERN_DEBUG "%s: hss_hdlc_xmit queue full\n", dev->name);
#पूर्ण_अगर
		netअगर_stop_queue(dev);
		/* we could miss TX पढ़ोy पूर्णांकerrupt */
		अगर (!qmgr_stat_below_low_watermark(txपढ़ोyq)) अणु
#अगर DEBUG_TX
			prपूर्णांकk(KERN_DEBUG "%s: hss_hdlc_xmit ready again\n",
			       dev->name);
#पूर्ण_अगर
			netअगर_wake_queue(dev);
		पूर्ण
	पूर्ण

#अगर DEBUG_TX
	prपूर्णांकk(KERN_DEBUG "%s: hss_hdlc_xmit end\n", dev->name);
#पूर्ण_अगर
	वापस NETDEV_TX_OK;
पूर्ण


अटल पूर्णांक request_hdlc_queues(काष्ठा port *port)
अणु
	पूर्णांक err;

	err = qmgr_request_queue(queue_ids[port->id].rxमुक्त, RX_DESCS, 0, 0,
				 "%s:RX-free", port->netdev->name);
	अगर (err)
		वापस err;

	err = qmgr_request_queue(queue_ids[port->id].rx, RX_DESCS, 0, 0,
				 "%s:RX", port->netdev->name);
	अगर (err)
		जाओ rel_rxमुक्त;

	err = qmgr_request_queue(queue_ids[port->id].tx, TX_DESCS, 0, 0,
				 "%s:TX", port->netdev->name);
	अगर (err)
		जाओ rel_rx;

	err = qmgr_request_queue(port->plat->txपढ़ोyq, TX_DESCS, 0, 0,
				 "%s:TX-ready", port->netdev->name);
	अगर (err)
		जाओ rel_tx;

	err = qmgr_request_queue(queue_ids[port->id].txकरोne, TX_DESCS, 0, 0,
				 "%s:TX-done", port->netdev->name);
	अगर (err)
		जाओ rel_txपढ़ोy;
	वापस 0;

rel_txपढ़ोy:
	qmgr_release_queue(port->plat->txपढ़ोyq);
rel_tx:
	qmgr_release_queue(queue_ids[port->id].tx);
rel_rx:
	qmgr_release_queue(queue_ids[port->id].rx);
rel_rxमुक्त:
	qmgr_release_queue(queue_ids[port->id].rxमुक्त);
	prपूर्णांकk(KERN_DEBUG "%s: unable to request hardware queues\n",
	       port->netdev->name);
	वापस err;
पूर्ण

अटल व्योम release_hdlc_queues(काष्ठा port *port)
अणु
	qmgr_release_queue(queue_ids[port->id].rxमुक्त);
	qmgr_release_queue(queue_ids[port->id].rx);
	qmgr_release_queue(queue_ids[port->id].txकरोne);
	qmgr_release_queue(queue_ids[port->id].tx);
	qmgr_release_queue(port->plat->txपढ़ोyq);
पूर्ण

अटल पूर्णांक init_hdlc_queues(काष्ठा port *port)
अणु
	पूर्णांक i;

	अगर (!ports_खोलो) अणु
		dma_pool = dma_pool_create(DRV_NAME, &port->netdev->dev,
					   POOL_ALLOC_SIZE, 32, 0);
		अगर (!dma_pool)
			वापस -ENOMEM;
	पूर्ण

	अगर (!(port->desc_tab = dma_pool_alloc(dma_pool, GFP_KERNEL,
					      &port->desc_tab_phys)))
		वापस -ENOMEM;
	स_रखो(port->desc_tab, 0, POOL_ALLOC_SIZE);
	स_रखो(port->rx_buff_tab, 0, माप(port->rx_buff_tab)); /* tables */
	स_रखो(port->tx_buff_tab, 0, माप(port->tx_buff_tab));

	/* Setup RX buffers */
	क्रम (i = 0; i < RX_DESCS; i++) अणु
		काष्ठा desc *desc = rx_desc_ptr(port, i);
		buffer_t *buff;
		व्योम *data;
#अगर_घोषित __ARMEB__
		अगर (!(buff = netdev_alloc_skb(port->netdev, RX_SIZE)))
			वापस -ENOMEM;
		data = buff->data;
#अन्यथा
		अगर (!(buff = kदो_स्मृति(RX_SIZE, GFP_KERNEL)))
			वापस -ENOMEM;
		data = buff;
#पूर्ण_अगर
		desc->buf_len = RX_SIZE;
		desc->data = dma_map_single(&port->netdev->dev, data,
					    RX_SIZE, DMA_FROM_DEVICE);
		अगर (dma_mapping_error(&port->netdev->dev, desc->data)) अणु
			मुक्त_buffer(buff);
			वापस -EIO;
		पूर्ण
		port->rx_buff_tab[i] = buff;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम destroy_hdlc_queues(काष्ठा port *port)
अणु
	पूर्णांक i;

	अगर (port->desc_tab) अणु
		क्रम (i = 0; i < RX_DESCS; i++) अणु
			काष्ठा desc *desc = rx_desc_ptr(port, i);
			buffer_t *buff = port->rx_buff_tab[i];
			अगर (buff) अणु
				dma_unmap_single(&port->netdev->dev,
						 desc->data, RX_SIZE,
						 DMA_FROM_DEVICE);
				मुक्त_buffer(buff);
			पूर्ण
		पूर्ण
		क्रम (i = 0; i < TX_DESCS; i++) अणु
			काष्ठा desc *desc = tx_desc_ptr(port, i);
			buffer_t *buff = port->tx_buff_tab[i];
			अगर (buff) अणु
				dma_unmap_tx(port, desc);
				मुक्त_buffer(buff);
			पूर्ण
		पूर्ण
		dma_pool_मुक्त(dma_pool, port->desc_tab, port->desc_tab_phys);
		port->desc_tab = शून्य;
	पूर्ण

	अगर (!ports_खोलो && dma_pool) अणु
		dma_pool_destroy(dma_pool);
		dma_pool = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक hss_hdlc_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा port *port = dev_to_port(dev);
	अचिन्हित दीर्घ flags;
	पूर्णांक i, err = 0;

	अगर ((err = hdlc_खोलो(dev)))
		वापस err;

	अगर ((err = hss_load_firmware(port)))
		जाओ err_hdlc_बंद;

	अगर ((err = request_hdlc_queues(port)))
		जाओ err_hdlc_बंद;

	अगर ((err = init_hdlc_queues(port)))
		जाओ err_destroy_queues;

	spin_lock_irqsave(&npe_lock, flags);
	अगर (port->plat->खोलो)
		अगर ((err = port->plat->खोलो(port->id, dev,
					    hss_hdlc_set_carrier)))
			जाओ err_unlock;
	spin_unlock_irqrestore(&npe_lock, flags);

	/* Populate queues with buffers, no failure after this poपूर्णांक */
	क्रम (i = 0; i < TX_DESCS; i++)
		queue_put_desc(port->plat->txपढ़ोyq,
			       tx_desc_phys(port, i), tx_desc_ptr(port, i));

	क्रम (i = 0; i < RX_DESCS; i++)
		queue_put_desc(queue_ids[port->id].rxमुक्त,
			       rx_desc_phys(port, i), rx_desc_ptr(port, i));

	napi_enable(&port->napi);
	netअगर_start_queue(dev);

	qmgr_set_irq(queue_ids[port->id].rx, QUEUE_IRQ_SRC_NOT_EMPTY,
		     hss_hdlc_rx_irq, dev);

	qmgr_set_irq(queue_ids[port->id].txकरोne, QUEUE_IRQ_SRC_NOT_EMPTY,
		     hss_hdlc_txकरोne_irq, dev);
	qmgr_enable_irq(queue_ids[port->id].txकरोne);

	ports_खोलो++;

	hss_set_hdlc_cfg(port);
	hss_config(port);

	hss_start_hdlc(port);

	/* we may alपढ़ोy have RX data, enables IRQ */
	napi_schedule(&port->napi);
	वापस 0;

err_unlock:
	spin_unlock_irqrestore(&npe_lock, flags);
err_destroy_queues:
	destroy_hdlc_queues(port);
	release_hdlc_queues(port);
err_hdlc_बंद:
	hdlc_बंद(dev);
	वापस err;
पूर्ण

अटल पूर्णांक hss_hdlc_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा port *port = dev_to_port(dev);
	अचिन्हित दीर्घ flags;
	पूर्णांक i, buffs = RX_DESCS; /* allocated RX buffers */

	spin_lock_irqsave(&npe_lock, flags);
	ports_खोलो--;
	qmgr_disable_irq(queue_ids[port->id].rx);
	netअगर_stop_queue(dev);
	napi_disable(&port->napi);

	hss_stop_hdlc(port);

	जबतक (queue_get_desc(queue_ids[port->id].rxमुक्त, port, 0) >= 0)
		buffs--;
	जबतक (queue_get_desc(queue_ids[port->id].rx, port, 0) >= 0)
		buffs--;

	अगर (buffs)
		netdev_crit(dev, "unable to drain RX queue, %i buffer(s) left in NPE\n",
			    buffs);

	buffs = TX_DESCS;
	जबतक (queue_get_desc(queue_ids[port->id].tx, port, 1) >= 0)
		buffs--; /* cancel TX */

	i = 0;
	करो अणु
		जबतक (queue_get_desc(port->plat->txपढ़ोyq, port, 1) >= 0)
			buffs--;
		अगर (!buffs)
			अवरोध;
	पूर्ण जबतक (++i < MAX_CLOSE_WAIT);

	अगर (buffs)
		netdev_crit(dev, "unable to drain TX queue, %i buffer(s) left in NPE\n",
			    buffs);
#अगर DEBUG_CLOSE
	अगर (!buffs)
		prपूर्णांकk(KERN_DEBUG "Draining TX queues took %i cycles\n", i);
#पूर्ण_अगर
	qmgr_disable_irq(queue_ids[port->id].txकरोne);

	अगर (port->plat->बंद)
		port->plat->बंद(port->id, dev);
	spin_unlock_irqrestore(&npe_lock, flags);

	destroy_hdlc_queues(port);
	release_hdlc_queues(port);
	hdlc_बंद(dev);
	वापस 0;
पूर्ण


अटल पूर्णांक hss_hdlc_attach(काष्ठा net_device *dev, अचिन्हित लघु encoding,
			   अचिन्हित लघु parity)
अणु
	काष्ठा port *port = dev_to_port(dev);

	अगर (encoding != ENCODING_NRZ)
		वापस -EINVAL;

	चयन(parity) अणु
	हाल PARITY_CRC16_PR1_CCITT:
		port->hdlc_cfg = 0;
		वापस 0;

	हाल PARITY_CRC32_PR1_CCITT:
		port->hdlc_cfg = PKT_HDLC_CRC_32;
		वापस 0;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल u32 check_घड़ी(u32 समयr_freq, u32 rate, u32 a, u32 b, u32 c,
		       u32 *best, u32 *best_dअगरf, u32 *reg)
अणु
	/* a is 10-bit, b is 10-bit, c is 12-bit */
	u64 new_rate;
	u32 new_dअगरf;

	new_rate = समयr_freq * (u64)(c + 1);
	करो_भाग(new_rate, a * (c + 1) + b + 1);
	new_dअगरf = असल((u32)new_rate - rate);

	अगर (new_dअगरf < *best_dअगरf) अणु
		*best = new_rate;
		*best_dअगरf = new_dअगरf;
		*reg = (a << 22) | (b << 12) | c;
	पूर्ण
	वापस new_dअगरf;
पूर्ण

अटल व्योम find_best_घड़ी(u32 समयr_freq, u32 rate, u32 *best, u32 *reg)
अणु
	u32 a, b, dअगरf = 0xFFFFFFFF;

	a = समयr_freq / rate;

	अगर (a > 0x3FF) अणु /* 10-bit value - we can go as slow as ca. 65 kb/s */
		check_घड़ी(समयr_freq, rate, 0x3FF, 1, 1, best, &dअगरf, reg);
		वापस;
	पूर्ण
	अगर (a == 0) अणु /* > 66.666 MHz */
		a = 1; /* minimum भागider is 1 (a = 0, b = 1, c = 1) */
		rate = समयr_freq;
	पूर्ण

	अगर (rate * a == समयr_freq) अणु /* करोn't भागide by 0 later */
		check_घड़ी(समयr_freq, rate, a - 1, 1, 1, best, &dअगरf, reg);
		वापस;
	पूर्ण

	क्रम (b = 0; b < 0x400; b++) अणु
		u64 c = (b + 1) * (u64)rate;
		करो_भाग(c, समयr_freq - rate * a);
		c--;
		अगर (c >= 0xFFF) अणु /* 12-bit - no need to check more 'b's */
			अगर (b == 0 && /* also try a bit higher rate */
			    !check_घड़ी(समयr_freq, rate, a - 1, 1, 1, best,
					 &dअगरf, reg))
				वापस;
			check_घड़ी(समयr_freq, rate, a, b, 0xFFF, best,
				    &dअगरf, reg);
			वापस;
		पूर्ण
		अगर (!check_घड़ी(समयr_freq, rate, a, b, c, best, &dअगरf, reg))
			वापस;
		अगर (!check_घड़ी(समयr_freq, rate, a, b, c + 1, best, &dअगरf,
				 reg))
			वापस;
	पूर्ण
पूर्ण

अटल पूर्णांक hss_hdlc_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	स्थिर माप_प्रकार size = माप(sync_serial_settings);
	sync_serial_settings new_line;
	sync_serial_settings __user *line = अगरr->अगरr_settings.अगरs_अगरsu.sync;
	काष्ठा port *port = dev_to_port(dev);
	अचिन्हित दीर्घ flags;
	पूर्णांक clk;

	अगर (cmd != SIOCWANDEV)
		वापस hdlc_ioctl(dev, अगरr, cmd);

	चयन(अगरr->अगरr_settings.type) अणु
	हाल IF_GET_IFACE:
		अगरr->अगरr_settings.type = IF_IFACE_V35;
		अगर (अगरr->अगरr_settings.size < size) अणु
			अगरr->अगरr_settings.size = size; /* data size wanted */
			वापस -ENOBUFS;
		पूर्ण
		स_रखो(&new_line, 0, माप(new_line));
		new_line.घड़ी_प्रकारype = port->घड़ी_प्रकारype;
		new_line.घड़ी_rate = port->घड़ी_rate;
		new_line.loopback = port->loopback;
		अगर (copy_to_user(line, &new_line, size))
			वापस -EFAULT;
		वापस 0;

	हाल IF_IFACE_SYNC_SERIAL:
	हाल IF_IFACE_V35:
		अगर(!capable(CAP_NET_ADMIN))
			वापस -EPERM;
		अगर (copy_from_user(&new_line, line, size))
			वापस -EFAULT;

		clk = new_line.घड़ी_प्रकारype;
		अगर (port->plat->set_घड़ी)
			clk = port->plat->set_घड़ी(port->id, clk);

		अगर (clk != CLOCK_EXT && clk != CLOCK_INT)
			वापस -EINVAL;	/* No such घड़ी setting */

		अगर (new_line.loopback != 0 && new_line.loopback != 1)
			वापस -EINVAL;

		port->घड़ी_प्रकारype = clk; /* Update settings */
		अगर (clk == CLOCK_INT)
			find_best_घड़ी(port->plat->समयr_freq,
					new_line.घड़ी_rate,
					&port->घड़ी_rate, &port->घड़ी_reg);
		अन्यथा अणु
			port->घड़ी_rate = 0;
			port->घड़ी_reg = CLK42X_SPEED_2048KHZ;
		पूर्ण
		port->loopback = new_line.loopback;

		spin_lock_irqsave(&npe_lock, flags);

		अगर (dev->flags & IFF_UP)
			hss_config(port);

		अगर (port->loopback || port->carrier)
			netअगर_carrier_on(port->netdev);
		अन्यथा
			netअगर_carrier_off(port->netdev);
		spin_unlock_irqrestore(&npe_lock, flags);

		वापस 0;

	शेष:
		वापस hdlc_ioctl(dev, अगरr, cmd);
	पूर्ण
पूर्ण

/*****************************************************************************
 * initialization
 ****************************************************************************/

अटल स्थिर काष्ठा net_device_ops hss_hdlc_ops = अणु
	.nकरो_खोलो       = hss_hdlc_खोलो,
	.nकरो_stop       = hss_hdlc_बंद,
	.nकरो_start_xmit = hdlc_start_xmit,
	.nकरो_करो_ioctl   = hss_hdlc_ioctl,
पूर्ण;

अटल पूर्णांक hss_init_one(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा port *port;
	काष्ठा net_device *dev;
	hdlc_device *hdlc;
	पूर्णांक err;

	अगर ((port = kzalloc(माप(*port), GFP_KERNEL)) == शून्य)
		वापस -ENOMEM;

	अगर ((port->npe = npe_request(0)) == शून्य) अणु
		err = -ENODEV;
		जाओ err_मुक्त;
	पूर्ण

	अगर ((port->netdev = dev = alloc_hdlcdev(port)) == शून्य) अणु
		err = -ENOMEM;
		जाओ err_plat;
	पूर्ण

	SET_NETDEV_DEV(dev, &pdev->dev);
	hdlc = dev_to_hdlc(dev);
	hdlc->attach = hss_hdlc_attach;
	hdlc->xmit = hss_hdlc_xmit;
	dev->netdev_ops = &hss_hdlc_ops;
	dev->tx_queue_len = 100;
	port->घड़ी_प्रकारype = CLOCK_EXT;
	port->घड़ी_rate = 0;
	port->घड़ी_reg = CLK42X_SPEED_2048KHZ;
	port->id = pdev->id;
	port->dev = &pdev->dev;
	port->plat = pdev->dev.platक्रमm_data;
	netअगर_napi_add(dev, &port->napi, hss_hdlc_poll, NAPI_WEIGHT);

	अगर ((err = रेजिस्टर_hdlc_device(dev)))
		जाओ err_मुक्त_netdev;

	platक्रमm_set_drvdata(pdev, port);

	netdev_info(dev, "initialized\n");
	वापस 0;

err_मुक्त_netdev:
	मुक्त_netdev(dev);
err_plat:
	npe_release(port->npe);
err_मुक्त:
	kमुक्त(port);
	वापस err;
पूर्ण

अटल पूर्णांक hss_हटाओ_one(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा port *port = platक्रमm_get_drvdata(pdev);

	unरेजिस्टर_hdlc_device(port->netdev);
	मुक्त_netdev(port->netdev);
	npe_release(port->npe);
	kमुक्त(port);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ixp4xx_hss_driver = अणु
	.driver.name	= DRV_NAME,
	.probe		= hss_init_one,
	.हटाओ		= hss_हटाओ_one,
पूर्ण;

अटल पूर्णांक __init hss_init_module(व्योम)
अणु
	अगर ((ixp4xx_पढ़ो_feature_bits() &
	     (IXP4XX_FEATURE_HDLC | IXP4XX_FEATURE_HSS)) !=
	    (IXP4XX_FEATURE_HDLC | IXP4XX_FEATURE_HSS))
		वापस -ENODEV;

	वापस platक्रमm_driver_रेजिस्टर(&ixp4xx_hss_driver);
पूर्ण

अटल व्योम __निकास hss_cleanup_module(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&ixp4xx_hss_driver);
पूर्ण

MODULE_AUTHOR("Krzysztof Halasa");
MODULE_DESCRIPTION("Intel IXP4xx HSS driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:ixp4xx_hss");
module_init(hss_init_module);
module_निकास(hss_cleanup_module);
