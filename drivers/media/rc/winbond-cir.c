<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  winbond-cir.c - Driver क्रम the Consumer IR functionality of Winbond
 *                  SuperI/O chips.
 *
 *  Currently supports the Winbond WPCD376i chip (PNP id WEC1022), but
 *  could probably support others (Winbond WEC102X, NatSemi, etc)
 *  with minor modअगरications.
 *
 *  Original Author: David Hथअrdeman <david@hardeman.nu>
 *     Copyright (C) 2012 Sean Young <sean@mess.org>
 *     Copyright (C) 2009 - 2011 David Hथअrdeman <david@hardeman.nu>
 *
 *  Dedicated to my daughter Matilda, without whose loving attention this
 *  driver would have been finished in half the समय and with a fraction
 *  of the bugs.
 *
 *  Written using:
 *    o Winbond WPCD376I datasheet helpfully provided by Jesse Barnes at Intel
 *    o NatSemi PC87338/PC97338 datasheet (क्रम the serial port stuff)
 *    o DSDT dumps
 *
 *  Supported features:
 *    o IR Receive
 *    o IR Transmit
 *    o Wake-On-CIR functionality
 *    o Carrier detection
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/pnp.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/समयr.h>
#समावेश <linux/leds.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/पन.स>
#समावेश <linux/bitrev.h>
#समावेश <linux/slab.h>
#समावेश <linux/रुको.h>
#समावेश <linux/sched.h>
#समावेश <media/rc-core.h>

#घोषणा DRVNAME "winbond-cir"

/* CEIR Wake-Up Registers, relative to data->wbase                      */
#घोषणा WBCIR_REG_WCEIR_CTL	0x03 /* CEIR Receiver Control		*/
#घोषणा WBCIR_REG_WCEIR_STS	0x04 /* CEIR Receiver Status		*/
#घोषणा WBCIR_REG_WCEIR_EV_EN	0x05 /* CEIR Receiver Event Enable	*/
#घोषणा WBCIR_REG_WCEIR_CNTL	0x06 /* CEIR Receiver Counter Low	*/
#घोषणा WBCIR_REG_WCEIR_CNTH	0x07 /* CEIR Receiver Counter High	*/
#घोषणा WBCIR_REG_WCEIR_INDEX	0x08 /* CEIR Receiver Index		*/
#घोषणा WBCIR_REG_WCEIR_DATA	0x09 /* CEIR Receiver Data		*/
#घोषणा WBCIR_REG_WCEIR_CSL	0x0A /* CEIR Re. Compare Strlen		*/
#घोषणा WBCIR_REG_WCEIR_CFG1	0x0B /* CEIR Re. Configuration 1	*/
#घोषणा WBCIR_REG_WCEIR_CFG2	0x0C /* CEIR Re. Configuration 2	*/

/* CEIR Enhanced Functionality Registers, relative to data->ebase       */
#घोषणा WBCIR_REG_ECEIR_CTS	0x00 /* Enhanced IR Control Status	*/
#घोषणा WBCIR_REG_ECEIR_CCTL	0x01 /* Infrared Counter Control	*/
#घोषणा WBCIR_REG_ECEIR_CNT_LO	0x02 /* Infrared Counter LSB		*/
#घोषणा WBCIR_REG_ECEIR_CNT_HI	0x03 /* Infrared Counter MSB		*/
#घोषणा WBCIR_REG_ECEIR_IREM	0x04 /* Infrared Emitter Status		*/

/* SP3 Banked Registers, relative to data->sbase                        */
#घोषणा WBCIR_REG_SP3_BSR	0x03 /* Bank Select, all banks		*/
				      /* Bank 0				*/
#घोषणा WBCIR_REG_SP3_RXDATA	0x00 /* FIFO RX data (r)		*/
#घोषणा WBCIR_REG_SP3_TXDATA	0x00 /* FIFO TX data (w)		*/
#घोषणा WBCIR_REG_SP3_IER	0x01 /* Interrupt Enable		*/
#घोषणा WBCIR_REG_SP3_EIR	0x02 /* Event Identअगरication (r)	*/
#घोषणा WBCIR_REG_SP3_FCR	0x02 /* FIFO Control (w)		*/
#घोषणा WBCIR_REG_SP3_MCR	0x04 /* Mode Control			*/
#घोषणा WBCIR_REG_SP3_LSR	0x05 /* Link Status			*/
#घोषणा WBCIR_REG_SP3_MSR	0x06 /* Modem Status			*/
#घोषणा WBCIR_REG_SP3_ASCR	0x07 /* Aux Status and Control		*/
				      /* Bank 2				*/
#घोषणा WBCIR_REG_SP3_BGDL	0x00 /* Baud Divisor LSB		*/
#घोषणा WBCIR_REG_SP3_BGDH	0x01 /* Baud Divisor MSB		*/
#घोषणा WBCIR_REG_SP3_EXCR1	0x02 /* Extended Control 1		*/
#घोषणा WBCIR_REG_SP3_EXCR2	0x04 /* Extended Control 2		*/
#घोषणा WBCIR_REG_SP3_TXFLV	0x06 /* TX FIFO Level			*/
#घोषणा WBCIR_REG_SP3_RXFLV	0x07 /* RX FIFO Level			*/
				      /* Bank 3				*/
#घोषणा WBCIR_REG_SP3_MRID	0x00 /* Module Identअगरication		*/
#घोषणा WBCIR_REG_SP3_SH_LCR	0x01 /* LCR Shaकरोw			*/
#घोषणा WBCIR_REG_SP3_SH_FCR	0x02 /* FCR Shaकरोw			*/
				      /* Bank 4				*/
#घोषणा WBCIR_REG_SP3_IRCR1	0x02 /* Infrared Control 1		*/
				      /* Bank 5				*/
#घोषणा WBCIR_REG_SP3_IRCR2	0x04 /* Infrared Control 2		*/
				      /* Bank 6				*/
#घोषणा WBCIR_REG_SP3_IRCR3	0x00 /* Infrared Control 3		*/
#घोषणा WBCIR_REG_SP3_SIR_PW	0x02 /* SIR Pulse Width			*/
				      /* Bank 7				*/
#घोषणा WBCIR_REG_SP3_IRRXDC	0x00 /* IR RX Demod Control		*/
#घोषणा WBCIR_REG_SP3_IRTXMC	0x01 /* IR TX Mod Control		*/
#घोषणा WBCIR_REG_SP3_RCCFG	0x02 /* CEIR Config			*/
#घोषणा WBCIR_REG_SP3_IRCFG1	0x04 /* Infrared Config 1		*/
#घोषणा WBCIR_REG_SP3_IRCFG4	0x07 /* Infrared Config 4		*/

/*
 * Magic values follow
 */

/* No पूर्णांकerrupts क्रम WBCIR_REG_SP3_IER and WBCIR_REG_SP3_EIR */
#घोषणा WBCIR_IRQ_NONE		0x00
/* RX data bit क्रम WBCIR_REG_SP3_IER and WBCIR_REG_SP3_EIR */
#घोषणा WBCIR_IRQ_RX		0x01
/* TX data low bit क्रम WBCIR_REG_SP3_IER and WBCIR_REG_SP3_EIR */
#घोषणा WBCIR_IRQ_TX_LOW	0x02
/* Over/Under-flow bit क्रम WBCIR_REG_SP3_IER and WBCIR_REG_SP3_EIR */
#घोषणा WBCIR_IRQ_ERR		0x04
/* TX data empty bit क्रम WBCEIR_REG_SP3_IER and WBCIR_REG_SP3_EIR */
#घोषणा WBCIR_IRQ_TX_EMPTY	0x20
/* Led enable/disable bit क्रम WBCIR_REG_ECEIR_CTS */
#घोषणा WBCIR_LED_ENABLE	0x80
/* RX data available bit क्रम WBCIR_REG_SP3_LSR */
#घोषणा WBCIR_RX_AVAIL		0x01
/* RX data overrun error bit क्रम WBCIR_REG_SP3_LSR */
#घोषणा WBCIR_RX_OVERRUN	0x02
/* TX End-Of-Transmission bit क्रम WBCIR_REG_SP3_ASCR */
#घोषणा WBCIR_TX_EOT		0x04
/* RX disable bit क्रम WBCIR_REG_SP3_ASCR */
#घोषणा WBCIR_RX_DISABLE	0x20
/* TX data underrun error bit क्रम WBCIR_REG_SP3_ASCR */
#घोषणा WBCIR_TX_UNDERRUN	0x40
/* Extended mode enable bit क्रम WBCIR_REG_SP3_EXCR1 */
#घोषणा WBCIR_EXT_ENABLE	0x01
/* Select compare रेजिस्टर in WBCIR_REG_WCEIR_INDEX (bits 5 & 6) */
#घोषणा WBCIR_REGSEL_COMPARE	0x10
/* Select mask रेजिस्टर in WBCIR_REG_WCEIR_INDEX (bits 5 & 6) */
#घोषणा WBCIR_REGSEL_MASK	0x20
/* Starting address of selected रेजिस्टर in WBCIR_REG_WCEIR_INDEX */
#घोषणा WBCIR_REG_ADDR0		0x00
/* Enable carrier counter */
#घोषणा WBCIR_CNTR_EN		0x01
/* Reset carrier counter */
#घोषणा WBCIR_CNTR_R		0x02
/* Invert TX */
#घोषणा WBCIR_IRTX_INV		0x04
/* Receiver oversampling */
#घोषणा WBCIR_RX_T_OV		0x40

/* Valid banks क्रम the SP3 UART */
क्रमागत wbcir_bank अणु
	WBCIR_BANK_0          = 0x00,
	WBCIR_BANK_1          = 0x80,
	WBCIR_BANK_2          = 0xE0,
	WBCIR_BANK_3          = 0xE4,
	WBCIR_BANK_4          = 0xE8,
	WBCIR_BANK_5          = 0xEC,
	WBCIR_BANK_6          = 0xF0,
	WBCIR_BANK_7          = 0xF4,
पूर्ण;

/* Supported घातer-on IR Protocols */
क्रमागत wbcir_protocol अणु
	IR_PROTOCOL_RC5          = 0x0,
	IR_PROTOCOL_NEC          = 0x1,
	IR_PROTOCOL_RC6          = 0x2,
पूर्ण;

/* Possible states क्रम IR reception */
क्रमागत wbcir_rxstate अणु
	WBCIR_RXSTATE_INACTIVE = 0,
	WBCIR_RXSTATE_ACTIVE,
	WBCIR_RXSTATE_ERROR
पूर्ण;

/* Possible states क्रम IR transmission */
क्रमागत wbcir_txstate अणु
	WBCIR_TXSTATE_INACTIVE = 0,
	WBCIR_TXSTATE_ACTIVE,
	WBCIR_TXSTATE_ERROR
पूर्ण;

/* Misc */
#घोषणा WBCIR_NAME	"Winbond CIR"
#घोषणा WBCIR_ID_FAMILY          0xF1 /* Family ID क्रम the WPCD376I	*/
#घोषणा	WBCIR_ID_CHIP            0x04 /* Chip ID क्रम the WPCD376I	*/
#घोषणा WAKEUP_IOMEM_LEN         0x10 /* Wake-Up I/O Reg Len		*/
#घोषणा EHFUNC_IOMEM_LEN         0x10 /* Enhanced Func I/O Reg Len	*/
#घोषणा SP_IOMEM_LEN             0x08 /* Serial Port 3 (IR) Reg Len	*/

/* Per-device data */
काष्ठा wbcir_data अणु
	spinlock_t spinlock;
	काष्ठा rc_dev *dev;
	काष्ठा led_classdev led;

	अचिन्हित दीर्घ wbase;        /* Wake-Up Baseaddr		*/
	अचिन्हित दीर्घ ebase;        /* Enhanced Func. Baseaddr	*/
	अचिन्हित दीर्घ sbase;        /* Serial Port Baseaddr	*/
	अचिन्हित पूर्णांक  irq;          /* Serial Port IRQ		*/
	u8 irqmask;

	/* RX state */
	क्रमागत wbcir_rxstate rxstate;
	पूर्णांक carrier_report_enabled;
	u32 pulse_duration;

	/* TX state */
	क्रमागत wbcir_txstate txstate;
	u32 txlen;
	u32 txoff;
	u32 *txbuf;
	u8 txmask;
	u32 txcarrier;
पूर्ण;

अटल bool invert; /* शेष = 0 */
module_param(invert, bool, 0444);
MODULE_PARM_DESC(invert, "Invert the signal from the IR receiver");

अटल bool txandrx; /* शेष = 0 */
module_param(txandrx, bool, 0444);
MODULE_PARM_DESC(txandrx, "Allow simultaneous TX and RX");


/*****************************************************************************
 *
 * UTILITY FUNCTIONS
 *
 *****************************************************************************/

/* Caller needs to hold wbcir_lock */
अटल व्योम
wbcir_set_bits(अचिन्हित दीर्घ addr, u8 bits, u8 mask)
अणु
	u8 val;

	val = inb(addr);
	val = ((val & ~mask) | (bits & mask));
	outb(val, addr);
पूर्ण

/* Selects the रेजिस्टर bank क्रम the serial port */
अटल अंतरभूत व्योम
wbcir_select_bank(काष्ठा wbcir_data *data, क्रमागत wbcir_bank bank)
अणु
	outb(bank, data->sbase + WBCIR_REG_SP3_BSR);
पूर्ण

अटल अंतरभूत व्योम
wbcir_set_irqmask(काष्ठा wbcir_data *data, u8 irqmask)
अणु
	अगर (data->irqmask == irqmask)
		वापस;

	wbcir_select_bank(data, WBCIR_BANK_0);
	outb(irqmask, data->sbase + WBCIR_REG_SP3_IER);
	data->irqmask = irqmask;
पूर्ण

अटल क्रमागत led_brightness
wbcir_led_brightness_get(काष्ठा led_classdev *led_cdev)
अणु
	काष्ठा wbcir_data *data = container_of(led_cdev,
					       काष्ठा wbcir_data,
					       led);

	अगर (inb(data->ebase + WBCIR_REG_ECEIR_CTS) & WBCIR_LED_ENABLE)
		वापस LED_FULL;
	अन्यथा
		वापस LED_OFF;
पूर्ण

अटल व्योम
wbcir_led_brightness_set(काष्ठा led_classdev *led_cdev,
			 क्रमागत led_brightness brightness)
अणु
	काष्ठा wbcir_data *data = container_of(led_cdev,
					       काष्ठा wbcir_data,
					       led);

	wbcir_set_bits(data->ebase + WBCIR_REG_ECEIR_CTS,
		       brightness == LED_OFF ? 0x00 : WBCIR_LED_ENABLE,
		       WBCIR_LED_ENABLE);
पूर्ण

/* Manchester encodes bits to RC6 message cells (see wbcir_shutकरोwn) */
अटल u8
wbcir_to_rc6cells(u8 val)
अणु
	u8 coded = 0x00;
	पूर्णांक i;

	val &= 0x0F;
	क्रम (i = 0; i < 4; i++) अणु
		अगर (val & 0x01)
			coded |= 0x02 << (i * 2);
		अन्यथा
			coded |= 0x01 << (i * 2);
		val >>= 1;
	पूर्ण

	वापस coded;
पूर्ण

/*****************************************************************************
 *
 * INTERRUPT FUNCTIONS
 *
 *****************************************************************************/

अटल व्योम
wbcir_carrier_report(काष्ठा wbcir_data *data)
अणु
	अचिन्हित counter = inb(data->ebase + WBCIR_REG_ECEIR_CNT_LO) |
			inb(data->ebase + WBCIR_REG_ECEIR_CNT_HI) << 8;

	अगर (counter > 0 && counter < 0xffff) अणु
		काष्ठा ir_raw_event ev = अणु
			.carrier_report = 1,
			.carrier = DIV_ROUND_CLOSEST(counter * 1000000u,
						data->pulse_duration)
		पूर्ण;

		ir_raw_event_store(data->dev, &ev);
	पूर्ण

	/* reset and restart the counter */
	data->pulse_duration = 0;
	wbcir_set_bits(data->ebase + WBCIR_REG_ECEIR_CCTL, WBCIR_CNTR_R,
						WBCIR_CNTR_EN | WBCIR_CNTR_R);
	wbcir_set_bits(data->ebase + WBCIR_REG_ECEIR_CCTL, WBCIR_CNTR_EN,
						WBCIR_CNTR_EN | WBCIR_CNTR_R);
पूर्ण

अटल व्योम
wbcir_idle_rx(काष्ठा rc_dev *dev, bool idle)
अणु
	काष्ठा wbcir_data *data = dev->priv;

	अगर (!idle && data->rxstate == WBCIR_RXSTATE_INACTIVE)
		data->rxstate = WBCIR_RXSTATE_ACTIVE;

	अगर (idle && data->rxstate != WBCIR_RXSTATE_INACTIVE) अणु
		data->rxstate = WBCIR_RXSTATE_INACTIVE;

		अगर (data->carrier_report_enabled)
			wbcir_carrier_report(data);

		/* Tell hardware to go idle by setting RXINACTIVE */
		outb(WBCIR_RX_DISABLE, data->sbase + WBCIR_REG_SP3_ASCR);
	पूर्ण
पूर्ण

अटल व्योम
wbcir_irq_rx(काष्ठा wbcir_data *data, काष्ठा pnp_dev *device)
अणु
	u8 irdata;
	काष्ठा ir_raw_event rawir = अणुपूर्ण;

	/* Since RXHDLEV is set, at least 8 bytes are in the FIFO */
	जबतक (inb(data->sbase + WBCIR_REG_SP3_LSR) & WBCIR_RX_AVAIL) अणु
		irdata = inb(data->sbase + WBCIR_REG_SP3_RXDATA);
		अगर (data->rxstate == WBCIR_RXSTATE_ERROR)
			जारी;

		rawir.duration = ((irdata & 0x7F) + 1) *
			(data->carrier_report_enabled ? 2 : 10);
		rawir.pulse = irdata & 0x80 ? false : true;

		अगर (rawir.pulse)
			data->pulse_duration += rawir.duration;

		ir_raw_event_store_with_filter(data->dev, &rawir);
	पूर्ण

	ir_raw_event_handle(data->dev);
पूर्ण

अटल व्योम
wbcir_irq_tx(काष्ठा wbcir_data *data)
अणु
	अचिन्हित पूर्णांक space;
	अचिन्हित पूर्णांक used;
	u8 bytes[16];
	u8 byte;

	अगर (!data->txbuf)
		वापस;

	चयन (data->txstate) अणु
	हाल WBCIR_TXSTATE_INACTIVE:
		/* TX FIFO empty */
		space = 16;
		अवरोध;
	हाल WBCIR_TXSTATE_ACTIVE:
		/* TX FIFO low (3 bytes or less) */
		space = 13;
		अवरोध;
	हाल WBCIR_TXSTATE_ERROR:
		space = 0;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	/*
	 * TX data is run-length coded in bytes: YXXXXXXX
	 * Y = space (1) or pulse (0)
	 * X = duration, encoded as (X + 1) * 10us (i.e 10 to 1280 us)
	 */
	क्रम (used = 0; used < space && data->txoff != data->txlen; used++) अणु
		अगर (data->txbuf[data->txoff] == 0) अणु
			data->txoff++;
			जारी;
		पूर्ण
		byte = min((u32)0x80, data->txbuf[data->txoff]);
		data->txbuf[data->txoff] -= byte;
		byte--;
		byte |= (data->txoff % 2 ? 0x80 : 0x00); /* pulse/space */
		bytes[used] = byte;
	पूर्ण

	जबतक (data->txoff != data->txlen && data->txbuf[data->txoff] == 0)
		data->txoff++;

	अगर (used == 0) अणु
		/* Finished */
		अगर (data->txstate == WBCIR_TXSTATE_ERROR)
			/* Clear TX underrun bit */
			outb(WBCIR_TX_UNDERRUN, data->sbase + WBCIR_REG_SP3_ASCR);
		wbcir_set_irqmask(data, WBCIR_IRQ_RX | WBCIR_IRQ_ERR);
		kमुक्त(data->txbuf);
		data->txbuf = शून्य;
		data->txstate = WBCIR_TXSTATE_INACTIVE;
	पूर्ण अन्यथा अगर (data->txoff == data->txlen) अणु
		/* At the end of transmission, tell the hw beक्रमe last byte */
		outsb(data->sbase + WBCIR_REG_SP3_TXDATA, bytes, used - 1);
		outb(WBCIR_TX_EOT, data->sbase + WBCIR_REG_SP3_ASCR);
		outb(bytes[used - 1], data->sbase + WBCIR_REG_SP3_TXDATA);
		wbcir_set_irqmask(data, WBCIR_IRQ_RX | WBCIR_IRQ_ERR |
				  WBCIR_IRQ_TX_EMPTY);
	पूर्ण अन्यथा अणु
		/* More data to follow... */
		outsb(data->sbase + WBCIR_REG_SP3_RXDATA, bytes, used);
		अगर (data->txstate == WBCIR_TXSTATE_INACTIVE) अणु
			wbcir_set_irqmask(data, WBCIR_IRQ_RX | WBCIR_IRQ_ERR |
					  WBCIR_IRQ_TX_LOW);
			data->txstate = WBCIR_TXSTATE_ACTIVE;
		पूर्ण
	पूर्ण
पूर्ण

अटल irqवापस_t
wbcir_irq_handler(पूर्णांक irqno, व्योम *cookie)
अणु
	काष्ठा pnp_dev *device = cookie;
	काष्ठा wbcir_data *data = pnp_get_drvdata(device);
	अचिन्हित दीर्घ flags;
	u8 status;

	spin_lock_irqsave(&data->spinlock, flags);
	wbcir_select_bank(data, WBCIR_BANK_0);
	status = inb(data->sbase + WBCIR_REG_SP3_EIR);
	status &= data->irqmask;

	अगर (!status) अणु
		spin_unlock_irqrestore(&data->spinlock, flags);
		वापस IRQ_NONE;
	पूर्ण

	अगर (status & WBCIR_IRQ_ERR) अणु
		/* RX overflow? (पढ़ो clears bit) */
		अगर (inb(data->sbase + WBCIR_REG_SP3_LSR) & WBCIR_RX_OVERRUN) अणु
			data->rxstate = WBCIR_RXSTATE_ERROR;
			ir_raw_event_reset(data->dev);
		पूर्ण

		/* TX underflow? */
		अगर (inb(data->sbase + WBCIR_REG_SP3_ASCR) & WBCIR_TX_UNDERRUN)
			data->txstate = WBCIR_TXSTATE_ERROR;
	पूर्ण

	अगर (status & WBCIR_IRQ_RX)
		wbcir_irq_rx(data, device);

	अगर (status & (WBCIR_IRQ_TX_LOW | WBCIR_IRQ_TX_EMPTY))
		wbcir_irq_tx(data);

	spin_unlock_irqrestore(&data->spinlock, flags);
	वापस IRQ_HANDLED;
पूर्ण

/*****************************************************************************
 *
 * RC-CORE INTERFACE FUNCTIONS
 *
 *****************************************************************************/

अटल पूर्णांक
wbcir_set_carrier_report(काष्ठा rc_dev *dev, पूर्णांक enable)
अणु
	काष्ठा wbcir_data *data = dev->priv;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&data->spinlock, flags);

	अगर (data->carrier_report_enabled == enable) अणु
		spin_unlock_irqrestore(&data->spinlock, flags);
		वापस 0;
	पूर्ण

	data->pulse_duration = 0;
	wbcir_set_bits(data->ebase + WBCIR_REG_ECEIR_CCTL, WBCIR_CNTR_R,
						WBCIR_CNTR_EN | WBCIR_CNTR_R);

	अगर (enable && data->dev->idle)
		wbcir_set_bits(data->ebase + WBCIR_REG_ECEIR_CCTL,
				WBCIR_CNTR_EN, WBCIR_CNTR_EN | WBCIR_CNTR_R);

	/* Set a higher sampling resolution अगर carrier reports are enabled */
	wbcir_select_bank(data, WBCIR_BANK_2);
	data->dev->rx_resolution = enable ? 2 : 10;
	outb(enable ? 0x03 : 0x0f, data->sbase + WBCIR_REG_SP3_BGDL);
	outb(0x00, data->sbase + WBCIR_REG_SP3_BGDH);

	/* Enable oversampling अगर carrier reports are enabled */
	wbcir_select_bank(data, WBCIR_BANK_7);
	wbcir_set_bits(data->sbase + WBCIR_REG_SP3_RCCFG,
				enable ? WBCIR_RX_T_OV : 0, WBCIR_RX_T_OV);

	data->carrier_report_enabled = enable;
	spin_unlock_irqrestore(&data->spinlock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक
wbcir_txcarrier(काष्ठा rc_dev *dev, u32 carrier)
अणु
	काष्ठा wbcir_data *data = dev->priv;
	अचिन्हित दीर्घ flags;
	u8 val;
	u32 freq;

	freq = DIV_ROUND_CLOSEST(carrier, 1000);
	अगर (freq < 30 || freq > 60)
		वापस -EINVAL;

	चयन (freq) अणु
	हाल 58:
	हाल 59:
	हाल 60:
		val = freq - 58;
		freq *= 1000;
		अवरोध;
	हाल 57:
		val = freq - 27;
		freq = 56900;
		अवरोध;
	शेष:
		val = freq - 27;
		freq *= 1000;
		अवरोध;
	पूर्ण

	spin_lock_irqsave(&data->spinlock, flags);
	अगर (data->txstate != WBCIR_TXSTATE_INACTIVE) अणु
		spin_unlock_irqrestore(&data->spinlock, flags);
		वापस -EBUSY;
	पूर्ण

	अगर (data->txcarrier != freq) अणु
		wbcir_select_bank(data, WBCIR_BANK_7);
		wbcir_set_bits(data->sbase + WBCIR_REG_SP3_IRTXMC, val, 0x1F);
		data->txcarrier = freq;
	पूर्ण

	spin_unlock_irqrestore(&data->spinlock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक
wbcir_txmask(काष्ठा rc_dev *dev, u32 mask)
अणु
	काष्ठा wbcir_data *data = dev->priv;
	अचिन्हित दीर्घ flags;
	u8 val;

	/* वापस the number of transmitters */
	अगर (mask > 15)
		वापस 4;

	/* Four outमाला_दो, only one output can be enabled at a समय */
	चयन (mask) अणु
	हाल 0x1:
		val = 0x0;
		अवरोध;
	हाल 0x2:
		val = 0x1;
		अवरोध;
	हाल 0x4:
		val = 0x2;
		अवरोध;
	हाल 0x8:
		val = 0x3;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	spin_lock_irqsave(&data->spinlock, flags);
	अगर (data->txstate != WBCIR_TXSTATE_INACTIVE) अणु
		spin_unlock_irqrestore(&data->spinlock, flags);
		वापस -EBUSY;
	पूर्ण

	अगर (data->txmask != mask) अणु
		wbcir_set_bits(data->ebase + WBCIR_REG_ECEIR_CTS, val, 0x0c);
		data->txmask = mask;
	पूर्ण

	spin_unlock_irqrestore(&data->spinlock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक
wbcir_tx(काष्ठा rc_dev *dev, अचिन्हित *b, अचिन्हित count)
अणु
	काष्ठा wbcir_data *data = dev->priv;
	अचिन्हित *buf;
	अचिन्हित i;
	अचिन्हित दीर्घ flags;

	buf = kदो_स्मृति_array(count, माप(*b), GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	/* Convert values to multiples of 10us */
	क्रम (i = 0; i < count; i++)
		buf[i] = DIV_ROUND_CLOSEST(b[i], 10);

	/* Not sure अगर this is possible, but better safe than sorry */
	spin_lock_irqsave(&data->spinlock, flags);
	अगर (data->txstate != WBCIR_TXSTATE_INACTIVE) अणु
		spin_unlock_irqrestore(&data->spinlock, flags);
		kमुक्त(buf);
		वापस -EBUSY;
	पूर्ण

	/* Fill the TX fअगरo once, the irq handler will करो the rest */
	data->txbuf = buf;
	data->txlen = count;
	data->txoff = 0;
	wbcir_irq_tx(data);

	/* We're करोne */
	spin_unlock_irqrestore(&data->spinlock, flags);
	वापस count;
पूर्ण

/*****************************************************************************
 *
 * SETUP/INIT/SUSPEND/RESUME FUNCTIONS
 *
 *****************************************************************************/

अटल व्योम
wbcir_shutकरोwn(काष्ठा pnp_dev *device)
अणु
	काष्ठा device *dev = &device->dev;
	काष्ठा wbcir_data *data = pnp_get_drvdata(device);
	काष्ठा rc_dev *rc = data->dev;
	bool करो_wake = true;
	u8 match[11];
	u8 mask[11];
	u8 rc6_csl = 0;
	u8 proto;
	u32 wake_sc = rc->scancode_wakeup_filter.data;
	u32 mask_sc = rc->scancode_wakeup_filter.mask;
	पूर्णांक i;

	स_रखो(match, 0, माप(match));
	स_रखो(mask, 0, माप(mask));

	अगर (!mask_sc || !device_may_wakeup(dev)) अणु
		करो_wake = false;
		जाओ finish;
	पूर्ण

	चयन (rc->wakeup_protocol) अणु
	हाल RC_PROTO_RC5:
		/* Mask = 13 bits, ex toggle */
		mask[0]  = (mask_sc & 0x003f);
		mask[0] |= (mask_sc & 0x0300) >> 2;
		mask[1]  = (mask_sc & 0x1c00) >> 10;
		अगर (mask_sc & 0x0040)		      /* 2nd start bit  */
			match[1] |= 0x10;

		match[0]  = (wake_sc & 0x003F);       /* 6 command bits */
		match[0] |= (wake_sc & 0x0300) >> 2;  /* 2 address bits */
		match[1]  = (wake_sc & 0x1c00) >> 10; /* 3 address bits */
		अगर (!(wake_sc & 0x0040))	      /* 2nd start bit  */
			match[1] |= 0x10;

		proto = IR_PROTOCOL_RC5;
		अवरोध;

	हाल RC_PROTO_NEC:
		mask[1] = bitrev8(mask_sc);
		mask[0] = mask[1];
		mask[3] = bitrev8(mask_sc >> 8);
		mask[2] = mask[3];

		match[1] = bitrev8(wake_sc);
		match[0] = ~match[1];
		match[3] = bitrev8(wake_sc >> 8);
		match[2] = ~match[3];

		proto = IR_PROTOCOL_NEC;
		अवरोध;

	हाल RC_PROTO_NECX:
		mask[1] = bitrev8(mask_sc);
		mask[0] = mask[1];
		mask[2] = bitrev8(mask_sc >> 8);
		mask[3] = bitrev8(mask_sc >> 16);

		match[1] = bitrev8(wake_sc);
		match[0] = ~match[1];
		match[2] = bitrev8(wake_sc >> 8);
		match[3] = bitrev8(wake_sc >> 16);

		proto = IR_PROTOCOL_NEC;
		अवरोध;

	हाल RC_PROTO_NEC32:
		mask[0] = bitrev8(mask_sc);
		mask[1] = bitrev8(mask_sc >> 8);
		mask[2] = bitrev8(mask_sc >> 16);
		mask[3] = bitrev8(mask_sc >> 24);

		match[0] = bitrev8(wake_sc);
		match[1] = bitrev8(wake_sc >> 8);
		match[2] = bitrev8(wake_sc >> 16);
		match[3] = bitrev8(wake_sc >> 24);

		proto = IR_PROTOCOL_NEC;
		अवरोध;

	हाल RC_PROTO_RC6_0:
		/* Command */
		match[0] = wbcir_to_rc6cells(wake_sc >> 0);
		mask[0]  = wbcir_to_rc6cells(mask_sc >> 0);
		match[1] = wbcir_to_rc6cells(wake_sc >> 4);
		mask[1]  = wbcir_to_rc6cells(mask_sc >> 4);

		/* Address */
		match[2] = wbcir_to_rc6cells(wake_sc >>  8);
		mask[2]  = wbcir_to_rc6cells(mask_sc >>  8);
		match[3] = wbcir_to_rc6cells(wake_sc >> 12);
		mask[3]  = wbcir_to_rc6cells(mask_sc >> 12);

		/* Header */
		match[4] = 0x50; /* mode1 = mode0 = 0, ignore toggle */
		mask[4]  = 0xF0;
		match[5] = 0x09; /* start bit = 1, mode2 = 0 */
		mask[5]  = 0x0F;

		rc6_csl = 44;
		proto = IR_PROTOCOL_RC6;
		अवरोध;

	हाल RC_PROTO_RC6_6A_24:
	हाल RC_PROTO_RC6_6A_32:
	हाल RC_PROTO_RC6_MCE:
		i = 0;

		/* Command */
		match[i]  = wbcir_to_rc6cells(wake_sc >>  0);
		mask[i++] = wbcir_to_rc6cells(mask_sc >>  0);
		match[i]  = wbcir_to_rc6cells(wake_sc >>  4);
		mask[i++] = wbcir_to_rc6cells(mask_sc >>  4);

		/* Address + Toggle */
		match[i]  = wbcir_to_rc6cells(wake_sc >>  8);
		mask[i++] = wbcir_to_rc6cells(mask_sc >>  8);
		match[i]  = wbcir_to_rc6cells(wake_sc >> 12);
		mask[i++] = wbcir_to_rc6cells(mask_sc >> 12);

		/* Customer bits 7 - 0 */
		match[i]  = wbcir_to_rc6cells(wake_sc >> 16);
		mask[i++] = wbcir_to_rc6cells(mask_sc >> 16);

		अगर (rc->wakeup_protocol == RC_PROTO_RC6_6A_20) अणु
			rc6_csl = 52;
		पूर्ण अन्यथा अणु
			match[i]  = wbcir_to_rc6cells(wake_sc >> 20);
			mask[i++] = wbcir_to_rc6cells(mask_sc >> 20);

			अगर (rc->wakeup_protocol == RC_PROTO_RC6_6A_24) अणु
				rc6_csl = 60;
			पूर्ण अन्यथा अणु
				/* Customer range bit and bits 15 - 8 */
				match[i]  = wbcir_to_rc6cells(wake_sc >> 24);
				mask[i++] = wbcir_to_rc6cells(mask_sc >> 24);
				match[i]  = wbcir_to_rc6cells(wake_sc >> 28);
				mask[i++] = wbcir_to_rc6cells(mask_sc >> 28);
				rc6_csl = 76;
			पूर्ण
		पूर्ण

		/* Header */
		match[i]  = 0x93; /* mode1 = mode0 = 1, submode = 0 */
		mask[i++] = 0xFF;
		match[i]  = 0x0A; /* start bit = 1, mode2 = 1 */
		mask[i++] = 0x0F;
		proto = IR_PROTOCOL_RC6;
		अवरोध;
	शेष:
		करो_wake = false;
		अवरोध;
	पूर्ण

finish:
	अगर (करो_wake) अणु
		/* Set compare and compare mask */
		wbcir_set_bits(data->wbase + WBCIR_REG_WCEIR_INDEX,
			       WBCIR_REGSEL_COMPARE | WBCIR_REG_ADDR0,
			       0x3F);
		outsb(data->wbase + WBCIR_REG_WCEIR_DATA, match, 11);
		wbcir_set_bits(data->wbase + WBCIR_REG_WCEIR_INDEX,
			       WBCIR_REGSEL_MASK | WBCIR_REG_ADDR0,
			       0x3F);
		outsb(data->wbase + WBCIR_REG_WCEIR_DATA, mask, 11);

		/* RC6 Compare String Len */
		outb(rc6_csl, data->wbase + WBCIR_REG_WCEIR_CSL);

		/* Clear status bits NEC_REP, BUFF, MSG_END, MATCH */
		wbcir_set_bits(data->wbase + WBCIR_REG_WCEIR_STS, 0x17, 0x17);

		/* Clear BUFF_EN, Clear END_EN, Set MATCH_EN */
		wbcir_set_bits(data->wbase + WBCIR_REG_WCEIR_EV_EN, 0x01, 0x07);

		/* Set CEIR_EN */
		wbcir_set_bits(data->wbase + WBCIR_REG_WCEIR_CTL,
			       (proto << 4) | 0x01, 0x31);

	पूर्ण अन्यथा अणु
		/* Clear BUFF_EN, Clear END_EN, Clear MATCH_EN */
		wbcir_set_bits(data->wbase + WBCIR_REG_WCEIR_EV_EN, 0x00, 0x07);

		/* Clear CEIR_EN */
		wbcir_set_bits(data->wbase + WBCIR_REG_WCEIR_CTL, 0x00, 0x01);
	पूर्ण

	/*
	 * ACPI will set the HW disable bit क्रम SP3 which means that the
	 * output संकेतs are left in an undefined state which may cause
	 * spurious पूर्णांकerrupts which we need to ignore until the hardware
	 * is reinitialized.
	 */
	wbcir_set_irqmask(data, WBCIR_IRQ_NONE);
	disable_irq(data->irq);
पूर्ण

/*
 * Wakeup handling is करोne on shutकरोwn.
 */
अटल पूर्णांक
wbcir_set_wakeup_filter(काष्ठा rc_dev *rc, काष्ठा rc_scancode_filter *filter)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक
wbcir_suspend(काष्ठा pnp_dev *device, pm_message_t state)
अणु
	काष्ठा wbcir_data *data = pnp_get_drvdata(device);
	led_classdev_suspend(&data->led);
	wbcir_shutकरोwn(device);
	वापस 0;
पूर्ण

अटल व्योम
wbcir_init_hw(काष्ठा wbcir_data *data)
अणु
	/* Disable पूर्णांकerrupts */
	wbcir_set_irqmask(data, WBCIR_IRQ_NONE);

	/* Set RX_INV, Clear CEIR_EN (needed क्रम the led) */
	wbcir_set_bits(data->wbase + WBCIR_REG_WCEIR_CTL, invert ? 8 : 0, 0x09);

	/* Clear status bits NEC_REP, BUFF, MSG_END, MATCH */
	wbcir_set_bits(data->wbase + WBCIR_REG_WCEIR_STS, 0x17, 0x17);

	/* Clear BUFF_EN, Clear END_EN, Clear MATCH_EN */
	wbcir_set_bits(data->wbase + WBCIR_REG_WCEIR_EV_EN, 0x00, 0x07);

	/* Set RC5 cell समय to correspond to 36 kHz */
	wbcir_set_bits(data->wbase + WBCIR_REG_WCEIR_CFG1, 0x4A, 0x7F);

	/* Set IRTX_INV */
	अगर (invert)
		outb(WBCIR_IRTX_INV, data->ebase + WBCIR_REG_ECEIR_CCTL);
	अन्यथा
		outb(0x00, data->ebase + WBCIR_REG_ECEIR_CCTL);

	/*
	 * Clear IR LED, set SP3 घड़ी to 24Mhz, set TX mask to IRTX1,
	 * set SP3_IRRX_SW to binary 01, helpfully not करोcumented
	 */
	outb(0x10, data->ebase + WBCIR_REG_ECEIR_CTS);
	data->txmask = 0x1;

	/* Enable extended mode */
	wbcir_select_bank(data, WBCIR_BANK_2);
	outb(WBCIR_EXT_ENABLE, data->sbase + WBCIR_REG_SP3_EXCR1);

	/*
	 * Configure baud generator, IR data will be sampled at
	 * a bitrate of: (24Mhz * prescaler) / (भागisor * 16).
	 *
	 * The ECIR रेजिस्टरs include a flag to change the
	 * 24Mhz घड़ी freq to 48Mhz.
	 *
	 * It's not करोcumented in the specs, but fअगरo levels
	 * other than 16 seems to be unsupported.
	 */

	/* prescaler 1.0, tx/rx fअगरo lvl 16 */
	outb(0x30, data->sbase + WBCIR_REG_SP3_EXCR2);

	/* Set baud भागisor to sample every 10 us */
	outb(0x0f, data->sbase + WBCIR_REG_SP3_BGDL);
	outb(0x00, data->sbase + WBCIR_REG_SP3_BGDH);

	/* Set CEIR mode */
	wbcir_select_bank(data, WBCIR_BANK_0);
	outb(0xC0, data->sbase + WBCIR_REG_SP3_MCR);
	inb(data->sbase + WBCIR_REG_SP3_LSR); /* Clear LSR */
	inb(data->sbase + WBCIR_REG_SP3_MSR); /* Clear MSR */

	/* Disable RX demod, enable run-length enc/dec, set freq span */
	wbcir_select_bank(data, WBCIR_BANK_7);
	outb(0x90, data->sbase + WBCIR_REG_SP3_RCCFG);

	/* Disable समयr */
	wbcir_select_bank(data, WBCIR_BANK_4);
	outb(0x00, data->sbase + WBCIR_REG_SP3_IRCR1);

	/* Disable MSR पूर्णांकerrupt, clear AUX_IRX, mask RX during TX? */
	wbcir_select_bank(data, WBCIR_BANK_5);
	outb(txandrx ? 0x03 : 0x02, data->sbase + WBCIR_REG_SP3_IRCR2);

	/* Disable CRC */
	wbcir_select_bank(data, WBCIR_BANK_6);
	outb(0x20, data->sbase + WBCIR_REG_SP3_IRCR3);

	/* Set RX demodulation freq, not really used */
	wbcir_select_bank(data, WBCIR_BANK_7);
	outb(0xF2, data->sbase + WBCIR_REG_SP3_IRRXDC);

	/* Set TX modulation, 36kHz, 7us pulse width */
	outb(0x69, data->sbase + WBCIR_REG_SP3_IRTXMC);
	data->txcarrier = 36000;

	/* Set invert and pin direction */
	अगर (invert)
		outb(0x10, data->sbase + WBCIR_REG_SP3_IRCFG4);
	अन्यथा
		outb(0x00, data->sbase + WBCIR_REG_SP3_IRCFG4);

	/* Set FIFO thresholds (RX = 8, TX = 3), reset RX/TX */
	wbcir_select_bank(data, WBCIR_BANK_0);
	outb(0x97, data->sbase + WBCIR_REG_SP3_FCR);

	/* Clear AUX status bits */
	outb(0xE0, data->sbase + WBCIR_REG_SP3_ASCR);

	/* Clear RX state */
	data->rxstate = WBCIR_RXSTATE_INACTIVE;
	wbcir_idle_rx(data->dev, true);

	/* Clear TX state */
	अगर (data->txstate == WBCIR_TXSTATE_ACTIVE) अणु
		kमुक्त(data->txbuf);
		data->txbuf = शून्य;
		data->txstate = WBCIR_TXSTATE_INACTIVE;
	पूर्ण

	/* Enable पूर्णांकerrupts */
	wbcir_set_irqmask(data, WBCIR_IRQ_RX | WBCIR_IRQ_ERR);
पूर्ण

अटल पूर्णांक
wbcir_resume(काष्ठा pnp_dev *device)
अणु
	काष्ठा wbcir_data *data = pnp_get_drvdata(device);

	wbcir_init_hw(data);
	ir_raw_event_reset(data->dev);
	enable_irq(data->irq);
	led_classdev_resume(&data->led);

	वापस 0;
पूर्ण

अटल पूर्णांक
wbcir_probe(काष्ठा pnp_dev *device, स्थिर काष्ठा pnp_device_id *dev_id)
अणु
	काष्ठा device *dev = &device->dev;
	काष्ठा wbcir_data *data;
	पूर्णांक err;

	अगर (!(pnp_port_len(device, 0) == EHFUNC_IOMEM_LEN &&
	      pnp_port_len(device, 1) == WAKEUP_IOMEM_LEN &&
	      pnp_port_len(device, 2) == SP_IOMEM_LEN)) अणु
		dev_err(dev, "Invalid resources\n");
		वापस -ENODEV;
	पूर्ण

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data) अणु
		err = -ENOMEM;
		जाओ निकास;
	पूर्ण

	pnp_set_drvdata(device, data);

	spin_lock_init(&data->spinlock);
	data->ebase = pnp_port_start(device, 0);
	data->wbase = pnp_port_start(device, 1);
	data->sbase = pnp_port_start(device, 2);
	data->irq = pnp_irq(device, 0);

	अगर (data->wbase == 0 || data->ebase == 0 ||
	    data->sbase == 0 || data->irq == -1) अणु
		err = -ENODEV;
		dev_err(dev, "Invalid resources\n");
		जाओ निकास_मुक्त_data;
	पूर्ण

	dev_dbg(&device->dev, "Found device (w: 0x%lX, e: 0x%lX, s: 0x%lX, i: %u)\n",
		data->wbase, data->ebase, data->sbase, data->irq);

	data->led.name = "cir::activity";
	data->led.शेष_trigger = "rc-feedback";
	data->led.brightness_set = wbcir_led_brightness_set;
	data->led.brightness_get = wbcir_led_brightness_get;
	err = led_classdev_रेजिस्टर(&device->dev, &data->led);
	अगर (err)
		जाओ निकास_मुक्त_data;

	data->dev = rc_allocate_device(RC_DRIVER_IR_RAW);
	अगर (!data->dev) अणु
		err = -ENOMEM;
		जाओ निकास_unरेजिस्टर_led;
	पूर्ण

	data->dev->driver_name = DRVNAME;
	data->dev->device_name = WBCIR_NAME;
	data->dev->input_phys = "wbcir/cir0";
	data->dev->input_id.bustype = BUS_HOST;
	data->dev->input_id.venकरोr = PCI_VENDOR_ID_WINBOND;
	data->dev->input_id.product = WBCIR_ID_FAMILY;
	data->dev->input_id.version = WBCIR_ID_CHIP;
	data->dev->map_name = RC_MAP_RC6_MCE;
	data->dev->s_idle = wbcir_idle_rx;
	data->dev->s_carrier_report = wbcir_set_carrier_report;
	data->dev->s_tx_mask = wbcir_txmask;
	data->dev->s_tx_carrier = wbcir_txcarrier;
	data->dev->tx_ir = wbcir_tx;
	data->dev->priv = data;
	data->dev->dev.parent = &device->dev;
	data->dev->min_समयout = 1;
	data->dev->समयout = IR_DEFAULT_TIMEOUT;
	data->dev->max_समयout = 10 * IR_DEFAULT_TIMEOUT;
	data->dev->rx_resolution = 2;
	data->dev->allowed_protocols = RC_PROTO_BIT_ALL_IR_DECODER;
	data->dev->allowed_wakeup_protocols = RC_PROTO_BIT_NEC |
		RC_PROTO_BIT_NECX | RC_PROTO_BIT_NEC32 | RC_PROTO_BIT_RC5 |
		RC_PROTO_BIT_RC6_0 | RC_PROTO_BIT_RC6_6A_20 |
		RC_PROTO_BIT_RC6_6A_24 | RC_PROTO_BIT_RC6_6A_32 |
		RC_PROTO_BIT_RC6_MCE;
	data->dev->wakeup_protocol = RC_PROTO_RC6_MCE;
	data->dev->scancode_wakeup_filter.data = 0x800f040c;
	data->dev->scancode_wakeup_filter.mask = 0xffff7fff;
	data->dev->s_wakeup_filter = wbcir_set_wakeup_filter;

	err = rc_रेजिस्टर_device(data->dev);
	अगर (err)
		जाओ निकास_मुक्त_rc;

	अगर (!request_region(data->wbase, WAKEUP_IOMEM_LEN, DRVNAME)) अणु
		dev_err(dev, "Region 0x%lx-0x%lx already in use!\n",
			data->wbase, data->wbase + WAKEUP_IOMEM_LEN - 1);
		err = -EBUSY;
		जाओ निकास_unरेजिस्टर_device;
	पूर्ण

	अगर (!request_region(data->ebase, EHFUNC_IOMEM_LEN, DRVNAME)) अणु
		dev_err(dev, "Region 0x%lx-0x%lx already in use!\n",
			data->ebase, data->ebase + EHFUNC_IOMEM_LEN - 1);
		err = -EBUSY;
		जाओ निकास_release_wbase;
	पूर्ण

	अगर (!request_region(data->sbase, SP_IOMEM_LEN, DRVNAME)) अणु
		dev_err(dev, "Region 0x%lx-0x%lx already in use!\n",
			data->sbase, data->sbase + SP_IOMEM_LEN - 1);
		err = -EBUSY;
		जाओ निकास_release_ebase;
	पूर्ण

	err = request_irq(data->irq, wbcir_irq_handler,
			  0, DRVNAME, device);
	अगर (err) अणु
		dev_err(dev, "Failed to claim IRQ %u\n", data->irq);
		err = -EBUSY;
		जाओ निकास_release_sbase;
	पूर्ण

	device_init_wakeup(&device->dev, 1);

	wbcir_init_hw(data);

	वापस 0;

निकास_release_sbase:
	release_region(data->sbase, SP_IOMEM_LEN);
निकास_release_ebase:
	release_region(data->ebase, EHFUNC_IOMEM_LEN);
निकास_release_wbase:
	release_region(data->wbase, WAKEUP_IOMEM_LEN);
निकास_unरेजिस्टर_device:
	rc_unरेजिस्टर_device(data->dev);
	data->dev = शून्य;
निकास_मुक्त_rc:
	rc_मुक्त_device(data->dev);
निकास_unरेजिस्टर_led:
	led_classdev_unरेजिस्टर(&data->led);
निकास_मुक्त_data:
	kमुक्त(data);
	pnp_set_drvdata(device, शून्य);
निकास:
	वापस err;
पूर्ण

अटल व्योम
wbcir_हटाओ(काष्ठा pnp_dev *device)
अणु
	काष्ठा wbcir_data *data = pnp_get_drvdata(device);

	/* Disable पूर्णांकerrupts */
	wbcir_set_irqmask(data, WBCIR_IRQ_NONE);
	मुक्त_irq(data->irq, device);

	/* Clear status bits NEC_REP, BUFF, MSG_END, MATCH */
	wbcir_set_bits(data->wbase + WBCIR_REG_WCEIR_STS, 0x17, 0x17);

	/* Clear CEIR_EN */
	wbcir_set_bits(data->wbase + WBCIR_REG_WCEIR_CTL, 0x00, 0x01);

	/* Clear BUFF_EN, END_EN, MATCH_EN */
	wbcir_set_bits(data->wbase + WBCIR_REG_WCEIR_EV_EN, 0x00, 0x07);

	rc_unरेजिस्टर_device(data->dev);

	led_classdev_unरेजिस्टर(&data->led);

	/* This is ok since &data->led isn't actually used */
	wbcir_led_brightness_set(&data->led, LED_OFF);

	release_region(data->wbase, WAKEUP_IOMEM_LEN);
	release_region(data->ebase, EHFUNC_IOMEM_LEN);
	release_region(data->sbase, SP_IOMEM_LEN);

	kमुक्त(data);

	pnp_set_drvdata(device, शून्य);
पूर्ण

अटल स्थिर काष्ठा pnp_device_id wbcir_ids[] = अणु
	अणु "WEC1022", 0 पूर्ण,
	अणु "", 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pnp, wbcir_ids);

अटल काष्ठा pnp_driver wbcir_driver = अणु
	.name     = DRVNAME,
	.id_table = wbcir_ids,
	.probe    = wbcir_probe,
	.हटाओ   = wbcir_हटाओ,
	.suspend  = wbcir_suspend,
	.resume   = wbcir_resume,
	.shutकरोwn = wbcir_shutकरोwn
पूर्ण;

अटल पूर्णांक __init
wbcir_init(व्योम)
अणु
	पूर्णांक ret;

	ret = pnp_रेजिस्टर_driver(&wbcir_driver);
	अगर (ret)
		pr_err("Unable to register driver\n");

	वापस ret;
पूर्ण

अटल व्योम __निकास
wbcir_निकास(व्योम)
अणु
	pnp_unरेजिस्टर_driver(&wbcir_driver);
पूर्ण

module_init(wbcir_init);
module_निकास(wbcir_निकास);

MODULE_AUTHOR("David Hथअrdeman <david@hardeman.nu>");
MODULE_DESCRIPTION("Winbond SuperI/O Consumer IR Driver");
MODULE_LICENSE("GPL");
