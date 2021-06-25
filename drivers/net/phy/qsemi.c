<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * drivers/net/phy/qsemi.c
 *
 * Driver क्रम Quality Semiconductor PHYs
 *
 * Author: Andy Fleming
 *
 * Copyright (c) 2004 Freescale Semiconductor, Inc.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/unistd.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/mii.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/phy.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <linux/uaccess.h>

/* ------------------------------------------------------------------------- */
/* The Quality Semiconductor QS6612 is used on the RPX CLLF                  */

/* रेजिस्टर definitions */

#घोषणा MII_QS6612_MCR		17  /* Mode Control Register      */
#घोषणा MII_QS6612_FTR		27  /* Factory Test Register      */
#घोषणा MII_QS6612_MCO		28  /* Misc. Control Register     */
#घोषणा MII_QS6612_ISR		29  /* Interrupt Source Register  */
#घोषणा MII_QS6612_IMR		30  /* Interrupt Mask Register    */
#घोषणा MII_QS6612_IMR_INIT	0x003a
#घोषणा MII_QS6612_PCR		31  /* 100BaseTx PHY Control Reg. */

#घोषणा QS6612_PCR_AN_COMPLETE	0x1000
#घोषणा QS6612_PCR_RLBEN	0x0200
#घोषणा QS6612_PCR_DCREN	0x0100
#घोषणा QS6612_PCR_4B5BEN	0x0040
#घोषणा QS6612_PCR_TX_ISOLATE	0x0020
#घोषणा QS6612_PCR_MLT3_DIS	0x0002
#घोषणा QS6612_PCR_SCRM_DESCRM	0x0001

MODULE_DESCRIPTION("Quality Semiconductor PHY driver");
MODULE_AUTHOR("Andy Fleming");
MODULE_LICENSE("GPL");

/* Returns 0, unless there's a ग_लिखो error */
अटल पूर्णांक qs6612_config_init(काष्ठा phy_device *phydev)
अणु
	/* The PHY घातers up isolated on the RPX,
	 * so send a command to allow operation.
	 * XXX - My करोcs indicate this should be 0x0940
	 * ...or something.  The current value sets three
	 * reserved bits, bit 11, which specअगरies it should be
	 * set to one, bit 10, which specअगरies it should be set
	 * to 0, and bit 7, which करोesn't specअगरy.  However, my
	 * करोcs are preliminary, and I will leave it like this
	 * until someone more knowledgable corrects me or it.
	 * -- Andy Fleming
	 */
	वापस phy_ग_लिखो(phydev, MII_QS6612_PCR, 0x0dc0);
पूर्ण

अटल पूर्णांक qs6612_ack_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;

	/* The Interrupt Source रेजिस्टर is not self-clearing, bits 4 and 5 are
	 * cleared when MII_BMSR is पढ़ो and bits 1 and 3 are cleared when
	 * MII_EXPANSION is पढ़ो
	 */
	err = phy_पढ़ो(phydev, MII_QS6612_ISR);

	अगर (err < 0)
		वापस err;

	err = phy_पढ़ो(phydev, MII_BMSR);

	अगर (err < 0)
		वापस err;

	err = phy_पढ़ो(phydev, MII_EXPANSION);

	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक qs6612_config_पूर्णांकr(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;
	अगर (phydev->पूर्णांकerrupts == PHY_INTERRUPT_ENABLED) अणु
		/* clear any पूर्णांकerrupts beक्रमe enabling them */
		err = qs6612_ack_पूर्णांकerrupt(phydev);
		अगर (err)
			वापस err;

		err = phy_ग_लिखो(phydev, MII_QS6612_IMR,
				MII_QS6612_IMR_INIT);
	पूर्ण अन्यथा अणु
		err = phy_ग_लिखो(phydev, MII_QS6612_IMR, 0);
		अगर (err)
			वापस err;

		/* clear any leftover पूर्णांकerrupts */
		err = qs6612_ack_पूर्णांकerrupt(phydev);
	पूर्ण

	वापस err;

पूर्ण

अटल irqवापस_t qs6612_handle_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	पूर्णांक irq_status;

	irq_status = phy_पढ़ो(phydev, MII_QS6612_ISR);
	अगर (irq_status < 0) अणु
		phy_error(phydev);
		वापस IRQ_NONE;
	पूर्ण

	अगर (!(irq_status & MII_QS6612_IMR_INIT))
		वापस IRQ_NONE;

	/* the पूर्णांकerrupt source रेजिस्टर is not self-clearing */
	qs6612_ack_पूर्णांकerrupt(phydev);

	phy_trigger_machine(phydev);

	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा phy_driver qs6612_driver[] = अणु अणु
	.phy_id		= 0x00181440,
	.name		= "QS6612",
	.phy_id_mask	= 0xfffffff0,
	/* PHY_BASIC_FEATURES */
	.config_init	= qs6612_config_init,
	.config_पूर्णांकr	= qs6612_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = qs6612_handle_पूर्णांकerrupt,
पूर्ण पूर्ण;

module_phy_driver(qs6612_driver);

अटल काष्ठा mdio_device_id __maybe_unused qs6612_tbl[] = अणु
	अणु 0x00181440, 0xfffffff0 पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(mdio, qs6612_tbl);
