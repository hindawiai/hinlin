<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
	Mantis PCI bridge driver

	Copyright (C) Manu Abraham (abraham.manu@gmail.com)

*/

#समावेश <linux/kernel.h>

#समावेश <linux/संकेत.स>
#समावेश <linux/sched.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <यंत्र/पन.स>

#समावेश <media/dmxdev.h>
#समावेश <media/dvbdev.h>
#समावेश <media/dvb_demux.h>
#समावेश <media/dvb_frontend.h>
#समावेश <media/dvb_net.h>

#समावेश "mantis_common.h"
#समावेश "mantis_link.h" /* temporary due to physical layer stuff */
#समावेश "mantis_reg.h"

/*
 * If Slot state is alपढ़ोy PLUG_IN event and we are called
 * again, definitely it is jitter alone
 */
व्योम mantis_event_cam_plugin(काष्ठा mantis_ca *ca)
अणु
	काष्ठा mantis_pci *mantis = ca->ca_priv;

	u32 gpअगर_irqcfg;

	अगर (ca->slot_state == MODULE_XTRACTED) अणु
		dprपूर्णांकk(MANTIS_DEBUG, 1, "Event: CAM Plugged IN: Adapter(%d) Slot(0)", mantis->num);
		udelay(50);
		mmग_लिखो(0xda000000, MANTIS_CARD_RESET);
		gpअगर_irqcfg  = mmपढ़ो(MANTIS_GPIF_IRQCFG);
		gpअगर_irqcfg |= MANTIS_MASK_PLUGOUT;
		gpअगर_irqcfg &= ~MANTIS_MASK_PLUGIN;
		mmग_लिखो(gpअगर_irqcfg, MANTIS_GPIF_IRQCFG);
		udelay(500);
		ca->slot_state = MODULE_INSERTED;
	पूर्ण
	udelay(100);
पूर्ण

/*
 * If Slot state is alपढ़ोy UN_PLUG event and we are called
 * again, definitely it is jitter alone
 */
व्योम mantis_event_cam_unplug(काष्ठा mantis_ca *ca)
अणु
	काष्ठा mantis_pci *mantis = ca->ca_priv;

	u32 gpअगर_irqcfg;

	अगर (ca->slot_state == MODULE_INSERTED) अणु
		dprपूर्णांकk(MANTIS_DEBUG, 1, "Event: CAM Unplugged: Adapter(%d) Slot(0)", mantis->num);
		udelay(50);
		mmग_लिखो(0x00da0000, MANTIS_CARD_RESET);
		gpअगर_irqcfg  = mmपढ़ो(MANTIS_GPIF_IRQCFG);
		gpअगर_irqcfg |= MANTIS_MASK_PLUGIN;
		gpअगर_irqcfg &= ~MANTIS_MASK_PLUGOUT;
		mmग_लिखो(gpअगर_irqcfg, MANTIS_GPIF_IRQCFG);
		udelay(500);
		ca->slot_state = MODULE_XTRACTED;
	पूर्ण
	udelay(100);
पूर्ण

पूर्णांक mantis_pcmcia_init(काष्ठा mantis_ca *ca)
अणु
	काष्ठा mantis_pci *mantis = ca->ca_priv;

	u32 gpअगर_stat, card_stat;

	mantis_unmask_पूर्णांकs(mantis, MANTIS_INT_IRQ0);
	gpअगर_stat = mmपढ़ो(MANTIS_GPIF_STATUS);
	card_stat = mmपढ़ो(MANTIS_GPIF_IRQCFG);

	अगर (gpअगर_stat & MANTIS_GPIF_DETSTAT) अणु
		dprपूर्णांकk(MANTIS_DEBUG, 1, "CAM found on Adapter(%d) Slot(0)", mantis->num);
		mmग_लिखो(card_stat | MANTIS_MASK_PLUGOUT, MANTIS_GPIF_IRQCFG);
		ca->slot_state = MODULE_INSERTED;
		dvb_ca_en50221_camchange_irq(&ca->en50221,
					     0,
					     DVB_CA_EN50221_CAMCHANGE_INSERTED);
	पूर्ण अन्यथा अणु
		dprपूर्णांकk(MANTIS_DEBUG, 1, "Empty Slot on Adapter(%d) Slot(0)", mantis->num);
		mmग_लिखो(card_stat | MANTIS_MASK_PLUGIN, MANTIS_GPIF_IRQCFG);
		ca->slot_state = MODULE_XTRACTED;
		dvb_ca_en50221_camchange_irq(&ca->en50221,
					     0,
					     DVB_CA_EN50221_CAMCHANGE_REMOVED);
	पूर्ण

	वापस 0;
पूर्ण

व्योम mantis_pcmcia_निकास(काष्ठा mantis_ca *ca)
अणु
	काष्ठा mantis_pci *mantis = ca->ca_priv;

	mmग_लिखो(mmपढ़ो(MANTIS_GPIF_STATUS) & (~MANTIS_CARD_PLUGOUT | ~MANTIS_CARD_PLUGIN), MANTIS_GPIF_STATUS);
	mantis_mask_पूर्णांकs(mantis, MANTIS_INT_IRQ0);
पूर्ण
