<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
	Mantis PCI bridge driver

	Copyright (C) Manu Abraham (abraham.manu@gmail.com)

*/

#समावेश <linux/संकेत.स>
#समावेश <linux/slab.h>
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

#समावेश "mantis_ca.h"

अटल पूर्णांक mantis_ca_पढ़ो_attr_mem(काष्ठा dvb_ca_en50221 *en50221, पूर्णांक slot, पूर्णांक addr)
अणु
	काष्ठा mantis_ca *ca = en50221->data;
	काष्ठा mantis_pci *mantis = ca->ca_priv;

	dprपूर्णांकk(MANTIS_DEBUG, 1, "Slot(%d): Request Attribute Mem Read", slot);

	अगर (slot != 0)
		वापस -EINVAL;

	वापस mantis_hअगर_पढ़ो_mem(ca, addr);
पूर्ण

अटल पूर्णांक mantis_ca_ग_लिखो_attr_mem(काष्ठा dvb_ca_en50221 *en50221, पूर्णांक slot, पूर्णांक addr, u8 data)
अणु
	काष्ठा mantis_ca *ca = en50221->data;
	काष्ठा mantis_pci *mantis = ca->ca_priv;

	dprपूर्णांकk(MANTIS_DEBUG, 1, "Slot(%d): Request Attribute Mem Write", slot);

	अगर (slot != 0)
		वापस -EINVAL;

	वापस mantis_hअगर_ग_लिखो_mem(ca, addr, data);
पूर्ण

अटल पूर्णांक mantis_ca_पढ़ो_cam_ctl(काष्ठा dvb_ca_en50221 *en50221, पूर्णांक slot, u8 addr)
अणु
	काष्ठा mantis_ca *ca = en50221->data;
	काष्ठा mantis_pci *mantis = ca->ca_priv;

	dprपूर्णांकk(MANTIS_DEBUG, 1, "Slot(%d): Request CAM control Read", slot);

	अगर (slot != 0)
		वापस -EINVAL;

	वापस mantis_hअगर_पढ़ो_iom(ca, addr);
पूर्ण

अटल पूर्णांक mantis_ca_ग_लिखो_cam_ctl(काष्ठा dvb_ca_en50221 *en50221, पूर्णांक slot, u8 addr, u8 data)
अणु
	काष्ठा mantis_ca *ca = en50221->data;
	काष्ठा mantis_pci *mantis = ca->ca_priv;

	dprपूर्णांकk(MANTIS_DEBUG, 1, "Slot(%d): Request CAM control Write", slot);

	अगर (slot != 0)
		वापस -EINVAL;

	वापस mantis_hअगर_ग_लिखो_iom(ca, addr, data);
पूर्ण

अटल पूर्णांक mantis_ca_slot_reset(काष्ठा dvb_ca_en50221 *en50221, पूर्णांक slot)
अणु
	काष्ठा mantis_ca *ca = en50221->data;
	काष्ठा mantis_pci *mantis = ca->ca_priv;

	dprपूर्णांकk(MANTIS_DEBUG, 1, "Slot(%d): Slot RESET", slot);
	udelay(500); /* Wait.. */
	mmग_लिखो(0xda, MANTIS_PCMCIA_RESET); /* Leading edge निश्चित */
	udelay(500);
	mmग_लिखो(0x00, MANTIS_PCMCIA_RESET); /* Trailing edge deनिश्चित */
	msleep(1000);
	dvb_ca_en50221_camपढ़ोy_irq(&ca->en50221, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक mantis_ca_slot_shutकरोwn(काष्ठा dvb_ca_en50221 *en50221, पूर्णांक slot)
अणु
	काष्ठा mantis_ca *ca = en50221->data;
	काष्ठा mantis_pci *mantis = ca->ca_priv;

	dprपूर्णांकk(MANTIS_DEBUG, 1, "Slot(%d): Slot shutdown", slot);

	वापस 0;
पूर्ण

अटल पूर्णांक mantis_ts_control(काष्ठा dvb_ca_en50221 *en50221, पूर्णांक slot)
अणु
	काष्ठा mantis_ca *ca = en50221->data;
	काष्ठा mantis_pci *mantis = ca->ca_priv;

	dprपूर्णांकk(MANTIS_DEBUG, 1, "Slot(%d): TS control", slot);

	वापस 0;
पूर्ण

अटल पूर्णांक mantis_slot_status(काष्ठा dvb_ca_en50221 *en50221, पूर्णांक slot, पूर्णांक खोलो)
अणु
	काष्ठा mantis_ca *ca = en50221->data;
	काष्ठा mantis_pci *mantis = ca->ca_priv;

	dprपूर्णांकk(MANTIS_DEBUG, 1, "Slot(%d): Poll Slot status", slot);

	अगर (ca->slot_state == MODULE_INSERTED) अणु
		dprपूर्णांकk(MANTIS_DEBUG, 1, "CA Module present and ready");
		वापस DVB_CA_EN50221_POLL_CAM_PRESENT | DVB_CA_EN50221_POLL_CAM_READY;
	पूर्ण अन्यथा अणु
		dprपूर्णांकk(MANTIS_DEBUG, 1, "CA Module not present or not ready");
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mantis_ca_init(काष्ठा mantis_pci *mantis)
अणु
	काष्ठा dvb_adapter *dvb_adapter	= &mantis->dvb_adapter;
	काष्ठा mantis_ca *ca;
	पूर्णांक ca_flags = 0, result;

	dprपूर्णांकk(MANTIS_DEBUG, 1, "Initializing Mantis CA");
	ca = kzalloc(माप(काष्ठा mantis_ca), GFP_KERNEL);
	अगर (!ca) अणु
		dprपूर्णांकk(MANTIS_ERROR, 1, "Out of memory!, exiting ..");
		result = -ENOMEM;
		जाओ err;
	पूर्ण

	ca->ca_priv		= mantis;
	mantis->mantis_ca	= ca;
	ca_flags		= DVB_CA_EN50221_FLAG_IRQ_CAMCHANGE;
	/* रेजिस्टर CA पूर्णांकerface */
	ca->en50221.owner		= THIS_MODULE;
	ca->en50221.पढ़ो_attribute_mem	= mantis_ca_पढ़ो_attr_mem;
	ca->en50221.ग_लिखो_attribute_mem	= mantis_ca_ग_लिखो_attr_mem;
	ca->en50221.पढ़ो_cam_control	= mantis_ca_पढ़ो_cam_ctl;
	ca->en50221.ग_लिखो_cam_control	= mantis_ca_ग_लिखो_cam_ctl;
	ca->en50221.slot_reset		= mantis_ca_slot_reset;
	ca->en50221.slot_shutकरोwn	= mantis_ca_slot_shutकरोwn;
	ca->en50221.slot_ts_enable	= mantis_ts_control;
	ca->en50221.poll_slot_status	= mantis_slot_status;
	ca->en50221.data		= ca;

	mutex_init(&ca->ca_lock);

	init_रुकोqueue_head(&ca->hअगर_data_wq);
	init_रुकोqueue_head(&ca->hअगर_opकरोne_wq);
	init_रुकोqueue_head(&ca->hअगर_ग_लिखो_wq);

	dprपूर्णांकk(MANTIS_ERROR, 1, "Registering EN50221 device");
	result = dvb_ca_en50221_init(dvb_adapter, &ca->en50221, ca_flags, 1);
	अगर (result != 0) अणु
		dprपूर्णांकk(MANTIS_ERROR, 1, "EN50221: Initialization failed <%d>", result);
		जाओ err;
	पूर्ण
	dprपूर्णांकk(MANTIS_ERROR, 1, "Registered EN50221 device");
	mantis_evmgr_init(ca);
	वापस 0;
err:
	kमुक्त(ca);
	वापस result;
पूर्ण
EXPORT_SYMBOL_GPL(mantis_ca_init);

व्योम mantis_ca_निकास(काष्ठा mantis_pci *mantis)
अणु
	काष्ठा mantis_ca *ca = mantis->mantis_ca;

	dprपूर्णांकk(MANTIS_DEBUG, 1, "Mantis CA exit");
	अगर (!ca)
		वापस;

	mantis_evmgr_निकास(ca);
	dprपूर्णांकk(MANTIS_ERROR, 1, "Unregistering EN50221 device");
	dvb_ca_en50221_release(&ca->en50221);

	kमुक्त(ca);
पूर्ण
EXPORT_SYMBOL_GPL(mantis_ca_निकास);
