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
#समावेश "mantis_link.h"
#समावेश "mantis_hif.h"
#समावेश "mantis_reg.h"

अटल व्योम mantis_hअगरevm_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mantis_ca *ca = container_of(work, काष्ठा mantis_ca, hअगर_evm_work);
	काष्ठा mantis_pci *mantis = ca->ca_priv;

	u32 gpअगर_stat;

	gpअगर_stat = mmपढ़ो(MANTIS_GPIF_STATUS);

	अगर (gpअगर_stat & MANTIS_GPIF_DETSTAT) अणु
		अगर (gpअगर_stat & MANTIS_CARD_PLUGIN) अणु
			dprपूर्णांकk(MANTIS_DEBUG, 1, "Event Mgr: Adapter(%d) Slot(0): CAM Plugin", mantis->num);
			mmग_लिखो(0xdada0000, MANTIS_CARD_RESET);
			mantis_event_cam_plugin(ca);
			dvb_ca_en50221_camchange_irq(&ca->en50221,
						     0,
						     DVB_CA_EN50221_CAMCHANGE_INSERTED);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (gpअगर_stat & MANTIS_CARD_PLUGOUT) अणु
			dprपूर्णांकk(MANTIS_DEBUG, 1, "Event Mgr: Adapter(%d) Slot(0): CAM Unplug", mantis->num);
			mmग_लिखो(0xdada0000, MANTIS_CARD_RESET);
			mantis_event_cam_unplug(ca);
			dvb_ca_en50221_camchange_irq(&ca->en50221,
						     0,
						     DVB_CA_EN50221_CAMCHANGE_REMOVED);
		पूर्ण
	पूर्ण

	अगर (mantis->gpअगर_status & MANTIS_GPIF_EXTIRQ)
		dprपूर्णांकk(MANTIS_DEBUG, 1, "Event Mgr: Adapter(%d) Slot(0): Ext IRQ", mantis->num);

	अगर (mantis->gpअगर_status & MANTIS_SBUF_WSTO)
		dprपूर्णांकk(MANTIS_DEBUG, 1, "Event Mgr: Adapter(%d) Slot(0): Smart Buffer Timeout", mantis->num);

	अगर (mantis->gpअगर_status & MANTIS_GPIF_OTHERR)
		dprपूर्णांकk(MANTIS_DEBUG, 1, "Event Mgr: Adapter(%d) Slot(0): Alignment Error", mantis->num);

	अगर (gpअगर_stat & MANTIS_SBUF_OVFLW)
		dprपूर्णांकk(MANTIS_DEBUG, 1, "Event Mgr: Adapter(%d) Slot(0): Smart Buffer Overflow", mantis->num);

	अगर (gpअगर_stat & MANTIS_GPIF_BRRDY)
		dprपूर्णांकk(MANTIS_DEBUG, 1, "Event Mgr: Adapter(%d) Slot(0): Smart Buffer Read Ready", mantis->num);

	अगर (gpअगर_stat & MANTIS_GPIF_INTSTAT)
		dprपूर्णांकk(MANTIS_DEBUG, 1, "Event Mgr: Adapter(%d) Slot(0): GPIF IRQ", mantis->num);

	अगर (gpअगर_stat & MANTIS_SBUF_EMPTY)
		dprपूर्णांकk(MANTIS_DEBUG, 1, "Event Mgr: Adapter(%d) Slot(0): Smart Buffer Empty", mantis->num);

	अगर (gpअगर_stat & MANTIS_SBUF_OPDONE) अणु
		dprपूर्णांकk(MANTIS_DEBUG, 1, "Event Mgr: Adapter(%d) Slot(0): Smart Buffer operation complete", mantis->num);
		ca->sbuf_status = MANTIS_SBUF_DATA_AVAIL;
		ca->hअगर_event = MANTIS_SBUF_OPDONE;
		wake_up(&ca->hअगर_opकरोne_wq);
	पूर्ण
पूर्ण

पूर्णांक mantis_evmgr_init(काष्ठा mantis_ca *ca)
अणु
	काष्ठा mantis_pci *mantis = ca->ca_priv;

	dprपूर्णांकk(MANTIS_DEBUG, 1, "Initializing Mantis Host I/F Event manager");
	INIT_WORK(&ca->hअगर_evm_work, mantis_hअगरevm_work);
	mantis_pcmcia_init(ca);
	schedule_work(&ca->hअगर_evm_work);
	mantis_hअगर_init(ca);
	वापस 0;
पूर्ण

व्योम mantis_evmgr_निकास(काष्ठा mantis_ca *ca)
अणु
	काष्ठा mantis_pci *mantis = ca->ca_priv;

	dprपूर्णांकk(MANTIS_DEBUG, 1, "Mantis Host I/F Event manager exiting");
	flush_work(&ca->hअगर_evm_work);
	mantis_hअगर_निकास(ca);
	mantis_pcmcia_निकास(ca);
पूर्ण
