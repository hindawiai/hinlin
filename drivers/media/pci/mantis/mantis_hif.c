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

#समावेश "mantis_hif.h"
#समावेश "mantis_link.h" /* temporary due to physical layer stuff */

#समावेश "mantis_reg.h"


अटल पूर्णांक mantis_hअगर_sbuf_opकरोne_रुको(काष्ठा mantis_ca *ca)
अणु
	काष्ठा mantis_pci *mantis = ca->ca_priv;
	पूर्णांक rc = 0;

	अगर (रुको_event_समयout(ca->hअगर_opकरोne_wq,
			       ca->hअगर_event & MANTIS_SBUF_OPDONE,
			       msecs_to_jअगरfies(500)) == -ERESTARTSYS) अणु

		dprपूर्णांकk(MANTIS_ERROR, 1, "Adapter(%d) Slot(0): Smart buffer operation timeout !", mantis->num);
		rc = -EREMOTEIO;
	पूर्ण
	dprपूर्णांकk(MANTIS_DEBUG, 1, "Smart Buffer Operation complete");
	ca->hअगर_event &= ~MANTIS_SBUF_OPDONE;
	वापस rc;
पूर्ण

अटल पूर्णांक mantis_hअगर_ग_लिखो_रुको(काष्ठा mantis_ca *ca)
अणु
	काष्ठा mantis_pci *mantis = ca->ca_priv;
	u32 opकरोne = 0, समयout = 0;
	पूर्णांक rc = 0;

	अगर (रुको_event_समयout(ca->hअगर_ग_लिखो_wq,
			       mantis->gpअगर_status & MANTIS_GPIF_WRACK,
			       msecs_to_jअगरfies(500)) == -ERESTARTSYS) अणु

		dprपूर्णांकk(MANTIS_ERROR, 1, "Adapter(%d) Slot(0): Write ACK timed out !", mantis->num);
		rc = -EREMOTEIO;
	पूर्ण
	dprपूर्णांकk(MANTIS_DEBUG, 1, "Write Acknowledged");
	mantis->gpअगर_status &= ~MANTIS_GPIF_WRACK;
	जबतक (!opकरोne) अणु
		opकरोne = (mmपढ़ो(MANTIS_GPIF_STATUS) & MANTIS_SBUF_OPDONE);
		udelay(500);
		समयout++;
		अगर (समयout > 100) अणु
			dprपूर्णांकk(MANTIS_ERROR, 1, "Adapter(%d) Slot(0): Write operation timed out!", mantis->num);
			rc = -ETIMEDOUT;
			अवरोध;
		पूर्ण
	पूर्ण
	dprपूर्णांकk(MANTIS_DEBUG, 1, "HIF Write success");
	वापस rc;
पूर्ण


पूर्णांक mantis_hअगर_पढ़ो_mem(काष्ठा mantis_ca *ca, u32 addr)
अणु
	काष्ठा mantis_pci *mantis = ca->ca_priv;
	u32 hअगर_addr = 0, data, count = 4;

	dprपूर्णांकk(MANTIS_DEBUG, 1, "Adapter(%d) Slot(0): Request HIF Mem Read", mantis->num);
	mutex_lock(&ca->ca_lock);
	hअगर_addr &= ~MANTIS_GPIF_PCMCIAREG;
	hअगर_addr &= ~MANTIS_GPIF_PCMCIAIOM;
	hअगर_addr |=  MANTIS_HIF_STATUS;
	hअगर_addr |=  addr;

	mmग_लिखो(hअगर_addr, MANTIS_GPIF_BRADDR);
	mmग_लिखो(count, MANTIS_GPIF_BRBYTES);
	udelay(20);
	mmग_लिखो(hअगर_addr | MANTIS_GPIF_HIFRDWRN, MANTIS_GPIF_ADDR);

	अगर (mantis_hअगर_sbuf_opकरोne_रुको(ca) != 0) अणु
		dprपूर्णांकk(MANTIS_ERROR, 1, "Adapter(%d) Slot(0): GPIF Smart Buffer operation failed", mantis->num);
		mutex_unlock(&ca->ca_lock);
		वापस -EREMOTEIO;
	पूर्ण
	data = mmपढ़ो(MANTIS_GPIF_DIN);
	mutex_unlock(&ca->ca_lock);
	dprपूर्णांकk(MANTIS_DEBUG, 1, "Mem Read: 0x%02x", data);
	वापस (data >> 24) & 0xff;
पूर्ण

पूर्णांक mantis_hअगर_ग_लिखो_mem(काष्ठा mantis_ca *ca, u32 addr, u8 data)
अणु
	काष्ठा mantis_slot *slot = ca->slot;
	काष्ठा mantis_pci *mantis = ca->ca_priv;
	u32 hअगर_addr = 0;

	dprपूर्णांकk(MANTIS_DEBUG, 1, "Adapter(%d) Slot(0): Request HIF Mem Write", mantis->num);
	mutex_lock(&ca->ca_lock);
	hअगर_addr &= ~MANTIS_GPIF_HIFRDWRN;
	hअगर_addr &= ~MANTIS_GPIF_PCMCIAREG;
	hअगर_addr &= ~MANTIS_GPIF_PCMCIAIOM;
	hअगर_addr |=  MANTIS_HIF_STATUS;
	hअगर_addr |=  addr;

	mmग_लिखो(slot->slave_cfg, MANTIS_GPIF_CFGSLA); /* Slot0 alone क्रम now */
	mmग_लिखो(hअगर_addr, MANTIS_GPIF_ADDR);
	mmग_लिखो(data, MANTIS_GPIF_DOUT);

	अगर (mantis_hअगर_ग_लिखो_रुको(ca) != 0) अणु
		dprपूर्णांकk(MANTIS_ERROR, 1, "Adapter(%d) Slot(0): HIF Smart Buffer operation failed", mantis->num);
		mutex_unlock(&ca->ca_lock);
		वापस -EREMOTEIO;
	पूर्ण
	dprपूर्णांकk(MANTIS_DEBUG, 1, "Mem Write: (0x%02x to 0x%02x)", data, addr);
	mutex_unlock(&ca->ca_lock);

	वापस 0;
पूर्ण

पूर्णांक mantis_hअगर_पढ़ो_iom(काष्ठा mantis_ca *ca, u32 addr)
अणु
	काष्ठा mantis_pci *mantis = ca->ca_priv;
	u32 data, hअगर_addr = 0;

	dprपूर्णांकk(MANTIS_DEBUG, 1, "Adapter(%d) Slot(0): Request HIF I/O Read", mantis->num);
	mutex_lock(&ca->ca_lock);
	hअगर_addr &= ~MANTIS_GPIF_PCMCIAREG;
	hअगर_addr |=  MANTIS_GPIF_PCMCIAIOM;
	hअगर_addr |=  MANTIS_HIF_STATUS;
	hअगर_addr |=  addr;

	mmग_लिखो(hअगर_addr, MANTIS_GPIF_BRADDR);
	mmग_लिखो(1, MANTIS_GPIF_BRBYTES);
	udelay(20);
	mmग_लिखो(hअगर_addr | MANTIS_GPIF_HIFRDWRN, MANTIS_GPIF_ADDR);

	अगर (mantis_hअगर_sbuf_opकरोne_रुको(ca) != 0) अणु
		dprपूर्णांकk(MANTIS_ERROR, 1, "Adapter(%d) Slot(0): HIF Smart Buffer operation failed", mantis->num);
		mutex_unlock(&ca->ca_lock);
		वापस -EREMOTEIO;
	पूर्ण
	data = mmपढ़ो(MANTIS_GPIF_DIN);
	dprपूर्णांकk(MANTIS_DEBUG, 1, "I/O Read: 0x%02x", data);
	udelay(50);
	mutex_unlock(&ca->ca_lock);

	वापस (u8) data;
पूर्ण

पूर्णांक mantis_hअगर_ग_लिखो_iom(काष्ठा mantis_ca *ca, u32 addr, u8 data)
अणु
	काष्ठा mantis_pci *mantis = ca->ca_priv;
	u32 hअगर_addr = 0;

	dprपूर्णांकk(MANTIS_DEBUG, 1, "Adapter(%d) Slot(0): Request HIF I/O Write", mantis->num);
	mutex_lock(&ca->ca_lock);
	hअगर_addr &= ~MANTIS_GPIF_PCMCIAREG;
	hअगर_addr &= ~MANTIS_GPIF_HIFRDWRN;
	hअगर_addr |=  MANTIS_GPIF_PCMCIAIOM;
	hअगर_addr |=  MANTIS_HIF_STATUS;
	hअगर_addr |=  addr;

	mmग_लिखो(hअगर_addr, MANTIS_GPIF_ADDR);
	mmग_लिखो(data, MANTIS_GPIF_DOUT);

	अगर (mantis_hअगर_ग_लिखो_रुको(ca) != 0) अणु
		dprपूर्णांकk(MANTIS_ERROR, 1, "Adapter(%d) Slot(0): HIF Smart Buffer operation failed", mantis->num);
		mutex_unlock(&ca->ca_lock);
		वापस -EREMOTEIO;
	पूर्ण
	dprपूर्णांकk(MANTIS_DEBUG, 1, "I/O Write: (0x%02x to 0x%02x)", data, addr);
	mutex_unlock(&ca->ca_lock);
	udelay(50);

	वापस 0;
पूर्ण

पूर्णांक mantis_hअगर_init(काष्ठा mantis_ca *ca)
अणु
	काष्ठा mantis_slot *slot = ca->slot;
	काष्ठा mantis_pci *mantis = ca->ca_priv;
	u32 irqcfg;

	slot[0].slave_cfg = 0x70773028;
	dprपूर्णांकk(MANTIS_ERROR, 1, "Adapter(%d) Initializing Mantis Host Interface", mantis->num);

	mutex_lock(&ca->ca_lock);
	irqcfg = mmपढ़ो(MANTIS_GPIF_IRQCFG);
	irqcfg = MANTIS_MASK_BRRDY	|
		 MANTIS_MASK_WRACK	|
		 MANTIS_MASK_EXTIRQ	|
		 MANTIS_MASK_WSTO	|
		 MANTIS_MASK_OTHERR	|
		 MANTIS_MASK_OVFLW;

	mmग_लिखो(irqcfg, MANTIS_GPIF_IRQCFG);
	mutex_unlock(&ca->ca_lock);

	वापस 0;
पूर्ण

व्योम mantis_hअगर_निकास(काष्ठा mantis_ca *ca)
अणु
	काष्ठा mantis_pci *mantis = ca->ca_priv;
	u32 irqcfg;

	dprपूर्णांकk(MANTIS_ERROR, 1, "Adapter(%d) Exiting Mantis Host Interface", mantis->num);
	mutex_lock(&ca->ca_lock);
	irqcfg = mmपढ़ो(MANTIS_GPIF_IRQCFG);
	irqcfg &= ~MANTIS_MASK_BRRDY;
	mmग_लिखो(irqcfg, MANTIS_GPIF_IRQCFG);
	mutex_unlock(&ca->ca_lock);
पूर्ण
