<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * driver क्रम ENE KB3926 B/C/D/E/F CIR (also known as ENE0XXX)
 *
 * Copyright (C) 2010 Maxim Levitsky <maximlevitsky@gmail.com>
 */
#समावेश <linux/spinlock.h>


/* hardware address */
#घोषणा ENE_STATUS		0	/* hardware status - unused */
#घोषणा ENE_ADDR_HI		1	/* hi byte of रेजिस्टर address */
#घोषणा ENE_ADDR_LO		2	/* low byte of रेजिस्टर address */
#घोषणा ENE_IO			3	/* पढ़ो/ग_लिखो winकरोw */
#घोषणा ENE_IO_SIZE		4

/* 8 bytes of samples, भागided in 2 packets*/
#घोषणा ENE_FW_SAMPLE_BUFFER	0xF8F0	/* sample buffer */
#घोषणा ENE_FW_SAMPLE_SPACE	0x80	/* sample is space */
#घोषणा ENE_FW_PACKET_SIZE	4

/* first firmware flag रेजिस्टर */
#घोषणा ENE_FW1			0xF8F8  /* flagr */
#घोषणा	ENE_FW1_ENABLE		0x01	/* enable fw processing */
#घोषणा ENE_FW1_TXIRQ		0x02	/* TX पूर्णांकerrupt pending */
#घोषणा ENE_FW1_HAS_EXTRA_BUF	0x04	/* fw uses extra buffer*/
#घोषणा ENE_FW1_EXTRA_BUF_HND	0x08	/* extra buffer handshake bit*/
#घोषणा ENE_FW1_LED_ON		0x10	/* turn on a led */

#घोषणा ENE_FW1_WPATTERN	0x20	/* enable wake pattern */
#घोषणा ENE_FW1_WAKE		0x40	/* enable wake from S3 */
#घोषणा ENE_FW1_IRQ		0x80	/* enable पूर्णांकerrupt */

/* second firmware flag रेजिस्टर */
#घोषणा ENE_FW2			0xF8F9  /* flagw */
#घोषणा ENE_FW2_BUF_WPTR	0x01	/* which half of the buffer to पढ़ो */
#घोषणा ENE_FW2_RXIRQ		0x04	/* RX IRQ pending*/
#घोषणा ENE_FW2_GP0A		0x08	/* Use GPIO0A क्रम demodulated input */
#घोषणा ENE_FW2_EMMITER1_CONN	0x10	/* TX emmiter 1 connected */
#घोषणा ENE_FW2_EMMITER2_CONN	0x20	/* TX emmiter 2 connected */

#घोषणा ENE_FW2_FAN_INPUT	0x40	/* fan input used क्रम demodulated data*/
#घोषणा ENE_FW2_LEARNING	0x80	/* hardware supports learning and TX */

/* firmware RX poपूर्णांकer क्रम new style buffer */
#घोषणा ENE_FW_RX_POINTER	0xF8FA

/* high parts of samples क्रम fan input (8 samples)*/
#घोषणा ENE_FW_SMPL_BUF_FAN	0xF8FB
#घोषणा ENE_FW_SMPL_BUF_FAN_PLS	0x8000	/* combined sample is pulse */
#घोषणा ENE_FW_SMPL_BUF_FAN_MSK	0x0FFF  /* combined sample maximum value */
#घोषणा ENE_FW_SAMPLE_PERIOD_FAN 61	/* fan input has fixed sample period */

/* transmitter ports */
#घोषणा ENE_GPIOFS1		0xFC01
#घोषणा ENE_GPIOFS1_GPIO0D	0x20	/* enable tx output on GPIO0D */
#घोषणा ENE_GPIOFS8		0xFC08
#घोषणा ENE_GPIOFS8_GPIO41	0x02	/* enable tx output on GPIO40 */

/* IRQ रेजिस्टरs block (क्रम revision B) */
#घोषणा ENEB_IRQ		0xFD09	/* IRQ number */
#घोषणा ENEB_IRQ_UNK1		0xFD17	/* unknown setting = 1 */
#घोषणा ENEB_IRQ_STATUS		0xFD80	/* irq status */
#घोषणा ENEB_IRQ_STATUS_IR	0x20	/* IR irq */

/* fan as input settings */
#घोषणा ENE_FAN_AS_IN1		0xFE30  /* fan init reg 1 */
#घोषणा ENE_FAN_AS_IN1_EN	0xCD
#घोषणा ENE_FAN_AS_IN2		0xFE31  /* fan init reg 2 */
#घोषणा ENE_FAN_AS_IN2_EN	0x03

/* IRQ रेजिस्टरs block (क्रम revision C,D) */
#घोषणा ENE_IRQ			0xFE9B	/* new irq settings रेजिस्टर */
#घोषणा ENE_IRQ_MASK		0x0F	/* irq number mask */
#घोषणा ENE_IRQ_UNK_EN		0x10	/* always enabled */
#घोषणा ENE_IRQ_STATUS		0x20	/* irq status and ACK */

/* CIR Config रेजिस्टर #1 */
#घोषणा ENE_CIRCFG		0xFEC0
#घोषणा ENE_CIRCFG_RX_EN	0x01	/* RX enable */
#घोषणा ENE_CIRCFG_RX_IRQ	0x02	/* Enable hardware पूर्णांकerrupt */
#घोषणा ENE_CIRCFG_REV_POL	0x04	/* Input polarity reversed */
#घोषणा ENE_CIRCFG_CARR_DEMOD	0x08	/* Enable carrier demodulator */

#घोषणा ENE_CIRCFG_TX_EN	0x10	/* TX enable */
#घोषणा ENE_CIRCFG_TX_IRQ	0x20	/* Send पूर्णांकerrupt on TX करोne */
#घोषणा ENE_CIRCFG_TX_POL_REV	0x40	/* TX polarity reversed */
#घोषणा ENE_CIRCFG_TX_CARR	0x80	/* send TX carrier or not */

/* CIR config रेजिस्टर #2 */
#घोषणा ENE_CIRCFG2		0xFEC1
#घोषणा ENE_CIRCFG2_RLC		0x00
#घोषणा ENE_CIRCFG2_RC5		0x01
#घोषणा ENE_CIRCFG2_RC6		0x02
#घोषणा ENE_CIRCFG2_NEC		0x03
#घोषणा ENE_CIRCFG2_CARR_DETECT	0x10	/* Enable carrier detection */
#घोषणा ENE_CIRCFG2_GPIO0A	0x20	/* Use GPIO0A instead of GPIO40 क्रम input */
#घोषणा ENE_CIRCFG2_FAST_SAMPL1	0x40	/* Fast leading pulse detection क्रम RC6 */
#घोषणा ENE_CIRCFG2_FAST_SAMPL2	0x80	/* Fast data detection क्रम RC6 */

/* Knobs क्रम protocol decoding - will करोcument when/अगर will use them */
#घोषणा ENE_CIRPF		0xFEC2
#घोषणा ENE_CIRHIGH		0xFEC3
#घोषणा ENE_CIRBIT		0xFEC4
#घोषणा ENE_CIRSTART		0xFEC5
#घोषणा ENE_CIRSTART2		0xFEC6

/* Actual रेजिस्टर which contains RLC RX data - पढ़ो by firmware */
#घोषणा ENE_CIRDAT_IN		0xFEC7


/* RLC configuration - sample period (1us resolution) + idle mode */
#घोषणा ENE_CIRRLC_CFG		0xFEC8
#घोषणा ENE_CIRRLC_CFG_OVERFLOW	0x80	/* पूर्णांकerrupt on overflows अगर set */
#घोषणा ENE_DEFAULT_SAMPLE_PERIOD 50

/* Two byte RLC TX buffer */
#घोषणा ENE_CIRRLC_OUT0		0xFEC9
#घोषणा ENE_CIRRLC_OUT1		0xFECA
#घोषणा ENE_CIRRLC_OUT_PULSE	0x80	/* Transmitted sample is pulse */
#घोषणा ENE_CIRRLC_OUT_MASK	0x7F


/* Carrier detect setting
 * Low nibble  - number of carrier pulses to average
 * High nibble - number of initial carrier pulses to discard
 */
#घोषणा ENE_CIRCAR_PULS		0xFECB

/* detected RX carrier period (resolution: 500 ns) */
#घोषणा ENE_CIRCAR_PRD		0xFECC
#घोषणा ENE_CIRCAR_PRD_VALID	0x80	/* data valid content valid */

/* detected RX carrier pulse width (resolution: 500 ns) */
#घोषणा ENE_CIRCAR_HPRD		0xFECD

/* TX period (resolution: 500 ns, minimum 2)*/
#घोषणा ENE_CIRMOD_PRD		0xFECE
#घोषणा ENE_CIRMOD_PRD_POL	0x80	/* TX carrier polarity*/

#घोषणा ENE_CIRMOD_PRD_MAX	0x7F	/* 15.87 kHz */
#घोषणा ENE_CIRMOD_PRD_MIN	0x02	/* 1 Mhz */

/* TX pulse width (resolution: 500 ns)*/
#घोषणा ENE_CIRMOD_HPRD		0xFECF

/* Hardware versions */
#घोषणा ENE_ECHV		0xFF00	/* hardware revision */
#घोषणा ENE_PLLFRH		0xFF16
#घोषणा ENE_PLLFRL		0xFF17
#घोषणा ENE_DEFAULT_PLL_FREQ	1000

#घोषणा ENE_ECSTS		0xFF1D
#घोषणा ENE_ECSTS_RSRVD		0x04

#घोषणा ENE_ECVER_MAJOR		0xFF1E	/* chip version */
#घोषणा ENE_ECVER_MINOR		0xFF1F
#घोषणा ENE_HW_VER_OLD		0xFD00

/******************************************************************************/

#घोषणा ENE_DRIVER_NAME		"ene_ir"

#घोषणा ENE_IRQ_RX		1
#घोषणा ENE_IRQ_TX		2

#घोषणा  ENE_HW_B		1	/* 3926B */
#घोषणा  ENE_HW_C		2	/* 3926C */
#घोषणा  ENE_HW_D		3	/* 3926D or later */

#घोषणा __dbg(level, क्रमmat, ...)				\
करो अणु								\
	अगर (debug >= level)					\
		pr_info(क्रमmat "\n", ## __VA_ARGS__);		\
पूर्ण जबतक (0)

#घोषणा dbg(क्रमmat, ...)		__dbg(1, क्रमmat, ## __VA_ARGS__)
#घोषणा dbg_verbose(क्रमmat, ...)	__dbg(2, क्रमmat, ## __VA_ARGS__)
#घोषणा dbg_regs(क्रमmat, ...)		__dbg(3, क्रमmat, ## __VA_ARGS__)

काष्ठा ene_device अणु
	काष्ठा pnp_dev *pnp_dev;
	काष्ठा rc_dev *rdev;

	/* hw IO settings */
	दीर्घ hw_io;
	पूर्णांक irq;
	spinlock_t hw_lock;

	/* HW features */
	पूर्णांक hw_revision;			/* hardware revision */
	bool hw_use_gpio_0a;			/* gpio0a is demodulated input*/
	bool hw_extra_buffer;			/* hardware has 'extra buffer' */
	bool hw_fan_input;			/* fan input is IR data source */
	bool hw_learning_and_tx_capable;	/* learning & tx capable */
	पूर्णांक  pll_freq;
	पूर्णांक buffer_len;

	/* Extra RX buffer location */
	पूर्णांक extra_buf1_address;
	पूर्णांक extra_buf1_len;
	पूर्णांक extra_buf2_address;
	पूर्णांक extra_buf2_len;

	/* HW state*/
	पूर्णांक r_poपूर्णांकer;				/* poपूर्णांकer to next sample to पढ़ो */
	पूर्णांक w_poपूर्णांकer;				/* poपूर्णांकer to next sample hw will ग_लिखो */
	bool rx_fan_input_inuse;		/* is fan input in use क्रम rx*/
	पूर्णांक tx_reg;				/* current reg used क्रम TX */
	u8  saved_conf1;			/* saved FEC0 reg */
	अचिन्हित पूर्णांक tx_sample;			/* current sample क्रम TX */
	bool tx_sample_pulse;			/* current sample is pulse */

	/* TX buffer */
	अचिन्हित *tx_buffer;			/* input samples buffer*/
	पूर्णांक tx_pos;				/* position in that buffer */
	पूर्णांक tx_len;				/* current len of tx buffer */
	पूर्णांक tx_करोne;				/* करोne transmitting */
						/* one more sample pending*/
	काष्ठा completion tx_complete;		/* TX completion */
	काष्ठा समयr_list tx_sim_समयr;

	/* TX settings */
	पूर्णांक tx_period;
	पूर्णांक tx_duty_cycle;
	पूर्णांक transmitter_mask;

	/* RX settings */
	bool learning_mode_enabled;		/* learning input enabled */
	bool carrier_detect_enabled;		/* carrier detect enabled */
	पूर्णांक rx_period_adjust;
	bool rx_enabled;
पूर्ण;

अटल पूर्णांक ene_irq_status(काष्ठा ene_device *dev);
अटल व्योम ene_rx_पढ़ो_hw_poपूर्णांकer(काष्ठा ene_device *dev);
