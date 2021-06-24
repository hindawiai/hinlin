<शैली गुरु>
/*
 * ti113x.h 1.16 1999/10/25 20:03:34
 *
 * The contents of this file are subject to the Mozilla Public License
 * Version 1.1 (the "License"); you may not use this file except in
 * compliance with the License. You may obtain a copy of the License
 * at http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS"
 * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See
 * the License क्रम the specअगरic language governing rights and
 * limitations under the License. 
 *
 * The initial developer of the original code is David A. Hinds
 * <dahinds@users.sourceक्रमge.net>.  Portions created by David A. Hinds
 * are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.
 *
 * Alternatively, the contents of this file may be used under the
 * terms of the GNU General Public License version 2 (the "GPL"), in which
 * हाल the provisions of the GPL are applicable instead of the
 * above.  If you wish to allow the use of your version of this file
 * only under the terms of the GPL and not to allow others to use
 * your version of this file under the MPL, indicate your decision by
 * deleting the provisions above and replace them with the notice and
 * other provisions required by the GPL.  If you करो not delete the
 * provisions above, a recipient may use your version of this file
 * under either the MPL or the GPL.
 */

#अगर_अघोषित _LINUX_TI113X_H
#घोषणा _LINUX_TI113X_H


/* Register definitions क्रम TI 113X PCI-to-CardBus bridges */

/* System Control Register */
#घोषणा TI113X_SYSTEM_CONTROL		0x0080	/* 32 bit */
#घोषणा  TI113X_SCR_SMIROUTE		0x04000000
#घोषणा  TI113X_SCR_SMISTATUS		0x02000000
#घोषणा  TI113X_SCR_SMIENB		0x01000000
#घोषणा  TI113X_SCR_VCCPROT		0x00200000
#घोषणा  TI113X_SCR_REDUCEZV		0x00100000
#घोषणा  TI113X_SCR_CDREQEN		0x00080000
#घोषणा  TI113X_SCR_CDMACHAN		0x00070000
#घोषणा  TI113X_SCR_SOCACTIVE		0x00002000
#घोषणा  TI113X_SCR_PWRSTREAM		0x00000800
#घोषणा  TI113X_SCR_DELAYUP		0x00000400
#घोषणा  TI113X_SCR_DELAYDOWN		0x00000200
#घोषणा  TI113X_SCR_INTERROGATE		0x00000100
#घोषणा  TI113X_SCR_CLKRUN_SEL		0x00000080
#घोषणा  TI113X_SCR_PWRSAVINGS		0x00000040
#घोषणा  TI113X_SCR_SUBSYSRW		0x00000020
#घोषणा  TI113X_SCR_CB_DPAR		0x00000010
#घोषणा  TI113X_SCR_CDMA_EN		0x00000008
#घोषणा  TI113X_SCR_ASYNC_IRQ		0x00000004
#घोषणा  TI113X_SCR_KEEPCLK		0x00000002
#घोषणा  TI113X_SCR_CLKRUN_ENA		0x00000001  

#घोषणा  TI122X_SCR_SER_STEP		0xc0000000
#घोषणा  TI122X_SCR_INTRTIE		0x20000000
#घोषणा  TIXX21_SCR_TIEALL		0x10000000
#घोषणा  TI122X_SCR_CBRSVD		0x00400000
#घोषणा  TI122X_SCR_MRBURSTDN		0x00008000
#घोषणा  TI122X_SCR_MRBURSTUP		0x00004000
#घोषणा  TI122X_SCR_RIMUX		0x00000001

/* Mulसमयdia Control Register */
#घोषणा TI1250_MULTIMEDIA_CTL		0x0084	/* 8 bit */
#घोषणा  TI1250_MMC_ZVOUTEN		0x80
#घोषणा  TI1250_MMC_PORTSEL		0x40
#घोषणा  TI1250_MMC_ZVEN1		0x02
#घोषणा  TI1250_MMC_ZVEN0		0x01

#घोषणा TI1250_GENERAL_STATUS		0x0085	/* 8 bit */
#घोषणा TI1250_GPIO0_CONTROL		0x0088	/* 8 bit */
#घोषणा TI1250_GPIO1_CONTROL		0x0089	/* 8 bit */
#घोषणा TI1250_GPIO2_CONTROL		0x008a	/* 8 bit */
#घोषणा TI1250_GPIO3_CONTROL		0x008b	/* 8 bit */
#घोषणा TI1250_GPIO_MODE_MASK		0xc0

/* IRQMUX/MFUNC Register */
#घोषणा TI122X_MFUNC			0x008c	/* 32 bit */
#घोषणा TI122X_MFUNC0_MASK		0x0000000f
#घोषणा TI122X_MFUNC1_MASK		0x000000f0
#घोषणा TI122X_MFUNC2_MASK		0x00000f00
#घोषणा TI122X_MFUNC3_MASK		0x0000f000
#घोषणा TI122X_MFUNC4_MASK		0x000f0000
#घोषणा TI122X_MFUNC5_MASK		0x00f00000
#घोषणा TI122X_MFUNC6_MASK		0x0f000000

#घोषणा TI122X_MFUNC0_INTA		0x00000002
#घोषणा TI125X_MFUNC0_INTB		0x00000001
#घोषणा TI122X_MFUNC1_INTB		0x00000020
#घोषणा TI122X_MFUNC3_IRQSER		0x00001000


/* Retry Status Register */
#घोषणा TI113X_RETRY_STATUS		0x0090	/* 8 bit */
#घोषणा  TI113X_RSR_PCIRETRY		0x80
#घोषणा  TI113X_RSR_CBRETRY		0x40
#घोषणा  TI113X_RSR_TEXP_CBB		0x20
#घोषणा  TI113X_RSR_MEXP_CBB		0x10
#घोषणा  TI113X_RSR_TEXP_CBA		0x08
#घोषणा  TI113X_RSR_MEXP_CBA		0x04
#घोषणा  TI113X_RSR_TEXP_PCI		0x02
#घोषणा  TI113X_RSR_MEXP_PCI		0x01

/* Card Control Register */
#घोषणा TI113X_CARD_CONTROL		0x0091	/* 8 bit */
#घोषणा  TI113X_CCR_RIENB		0x80
#घोषणा  TI113X_CCR_ZVENABLE		0x40
#घोषणा  TI113X_CCR_PCI_IRQ_ENA		0x20
#घोषणा  TI113X_CCR_PCI_IREQ		0x10
#घोषणा  TI113X_CCR_PCI_CSC		0x08
#घोषणा  TI113X_CCR_SPKROUTEN		0x02
#घोषणा  TI113X_CCR_IFG			0x01

#घोषणा  TI1220_CCR_PORT_SEL		0x20
#घोषणा  TI122X_CCR_AUD2MUX		0x04

/* Device Control Register */
#घोषणा TI113X_DEVICE_CONTROL		0x0092	/* 8 bit */
#घोषणा  TI113X_DCR_5V_FORCE		0x40
#घोषणा  TI113X_DCR_3V_FORCE		0x20
#घोषणा  TI113X_DCR_IMODE_MASK		0x06
#घोषणा  TI113X_DCR_IMODE_ISA		0x02
#घोषणा  TI113X_DCR_IMODE_SERIAL	0x04

#घोषणा  TI12XX_DCR_IMODE_PCI_ONLY	0x00
#घोषणा  TI12XX_DCR_IMODE_ALL_SERIAL	0x06

/* Buffer Control Register */
#घोषणा TI113X_BUFFER_CONTROL		0x0093	/* 8 bit */
#घोषणा  TI113X_BCR_CB_READ_DEPTH	0x08
#घोषणा  TI113X_BCR_CB_WRITE_DEPTH	0x04
#घोषणा  TI113X_BCR_PCI_READ_DEPTH	0x02
#घोषणा  TI113X_BCR_PCI_WRITE_DEPTH	0x01

/* Diagnostic Register */
#घोषणा TI1250_DIAGNOSTIC		0x0093	/* 8 bit */
#घोषणा  TI1250_DIAG_TRUE_VALUE		0x80
#घोषणा  TI1250_DIAG_PCI_IREQ		0x40
#घोषणा  TI1250_DIAG_PCI_CSC		0x20
#घोषणा  TI1250_DIAG_ASYNC_CSC		0x01

/* DMA Registers */
#घोषणा TI113X_DMA_0			0x0094	/* 32 bit */
#घोषणा TI113X_DMA_1			0x0098	/* 32 bit */

/* ExCA IO offset रेजिस्टरs */
#घोषणा TI113X_IO_OFFSET(map)		(0x36+((map)<<1))

/* EnE test रेजिस्टर */
#घोषणा ENE_TEST_C9			0xc9	/* 8bit */
#घोषणा ENE_TEST_C9_TLTENABLE		0x02
#घोषणा ENE_TEST_C9_PFENABLE_F0		0x04
#घोषणा ENE_TEST_C9_PFENABLE_F1		0x08
#घोषणा ENE_TEST_C9_PFENABLE		(ENE_TEST_C9_PFENABLE_F0 | ENE_TEST_C9_PFENABLE_F1)
#घोषणा ENE_TEST_C9_WPDISALBLE_F0	0x40
#घोषणा ENE_TEST_C9_WPDISALBLE_F1	0x80
#घोषणा ENE_TEST_C9_WPDISALBLE		(ENE_TEST_C9_WPDISALBLE_F0 | ENE_TEST_C9_WPDISALBLE_F1)

/*
 * Texas Instruments CardBus controller overrides.
 */
#घोषणा ti_sysctl(socket)	((socket)->निजी[0])
#घोषणा ti_cardctl(socket)	((socket)->निजी[1])
#घोषणा ti_devctl(socket)	((socket)->निजी[2])
#घोषणा ti_diag(socket)		((socket)->निजी[3])
#घोषणा ti_mfunc(socket)	((socket)->निजी[4])
#घोषणा ene_test_c9(socket)	((socket)->निजी[5])

/*
 * These are the TI specअगरic घातer management handlers.
 */
अटल व्योम ti_save_state(काष्ठा yenta_socket *socket)
अणु
	ti_sysctl(socket) = config_पढ़ोl(socket, TI113X_SYSTEM_CONTROL);
	ti_mfunc(socket) = config_पढ़ोl(socket, TI122X_MFUNC);
	ti_cardctl(socket) = config_पढ़ोb(socket, TI113X_CARD_CONTROL);
	ti_devctl(socket) = config_पढ़ोb(socket, TI113X_DEVICE_CONTROL);
	ti_diag(socket) = config_पढ़ोb(socket, TI1250_DIAGNOSTIC);

	अगर (socket->dev->venकरोr == PCI_VENDOR_ID_ENE)
		ene_test_c9(socket) = config_पढ़ोb(socket, ENE_TEST_C9);
पूर्ण

अटल व्योम ti_restore_state(काष्ठा yenta_socket *socket)
अणु
	config_ग_लिखोl(socket, TI113X_SYSTEM_CONTROL, ti_sysctl(socket));
	config_ग_लिखोl(socket, TI122X_MFUNC, ti_mfunc(socket));
	config_ग_लिखोb(socket, TI113X_CARD_CONTROL, ti_cardctl(socket));
	config_ग_लिखोb(socket, TI113X_DEVICE_CONTROL, ti_devctl(socket));
	config_ग_लिखोb(socket, TI1250_DIAGNOSTIC, ti_diag(socket));

	अगर (socket->dev->venकरोr == PCI_VENDOR_ID_ENE)
		config_ग_लिखोb(socket, ENE_TEST_C9, ene_test_c9(socket));
पूर्ण

/*
 *	Zoom video control क्रम TI122x/113x chips
 */

अटल व्योम ti_zoom_video(काष्ठा pcmcia_socket *sock, पूर्णांक onoff)
अणु
	u8 reg;
	काष्ठा yenta_socket *socket = container_of(sock, काष्ठा yenta_socket, socket);

	/* If we करोn't have a Zoom Video चयन this is harmless,
	   we just tristate the unused (ZV) lines */
	reg = config_पढ़ोb(socket, TI113X_CARD_CONTROL);
	अगर (onoff)
		/* Zoom zoom, we will all go together, zoom zoom, zoom zoom */
		reg |= TI113X_CCR_ZVENABLE;
	अन्यथा
		reg &= ~TI113X_CCR_ZVENABLE;
	config_ग_लिखोb(socket, TI113X_CARD_CONTROL, reg);
पूर्ण

/*
 *	The 145x series can also use this. They have an additional
 *	ZV स्वतःdetect mode we करोn't use but don't actually need.
 *	FIXME: manual says its in func0 and func1 but disagrees with
 *	itself about this - करो we need to क्रमce func0, अगर so we need
 *	to know a lot more about socket pairings in pcmcia_socket than
 *	we करो now.. uggh.
 */
 
अटल व्योम ti1250_zoom_video(काष्ठा pcmcia_socket *sock, पूर्णांक onoff)
अणु	
	काष्ठा yenta_socket *socket = container_of(sock, काष्ठा yenta_socket, socket);
	पूर्णांक shअगरt = 0;
	u8 reg;

	ti_zoom_video(sock, onoff);

	reg = config_पढ़ोb(socket, TI1250_MULTIMEDIA_CTL);
	reg |= TI1250_MMC_ZVOUTEN;	/* ZV bus enable */

	अगर(PCI_FUNC(socket->dev->devfn)==1)
		shअगरt = 1;
	
	अगर(onoff)
	अणु
		reg &= ~(1<<6); 	/* Clear select bit */
		reg |= shअगरt<<6;	/* Favour our socket */
		reg |= 1<<shअगरt;	/* Socket zoom video on */
	पूर्ण
	अन्यथा
	अणु
		reg &= ~(1<<6); 	/* Clear select bit */
		reg |= (1^shअगरt)<<6;	/* Favour other socket */
		reg &= ~(1<<shअगरt);	/* Socket zoon video off */
	पूर्ण

	config_ग_लिखोb(socket, TI1250_MULTIMEDIA_CTL, reg);
पूर्ण

अटल व्योम ti_set_zv(काष्ठा yenta_socket *socket)
अणु
	अगर(socket->dev->venकरोr == PCI_VENDOR_ID_TI)
	अणु
		चयन(socket->dev->device)
		अणु
			/* There may be more .. */
			हाल PCI_DEVICE_ID_TI_1220:
			हाल PCI_DEVICE_ID_TI_1221:
			हाल PCI_DEVICE_ID_TI_1225:
			हाल PCI_DEVICE_ID_TI_4510:
				socket->socket.zoom_video = ti_zoom_video;
				अवरोध;	
			हाल PCI_DEVICE_ID_TI_1250:
			हाल PCI_DEVICE_ID_TI_1251A:
			हाल PCI_DEVICE_ID_TI_1251B:
			हाल PCI_DEVICE_ID_TI_1450:
				socket->socket.zoom_video = ti1250_zoom_video;
		पूर्ण
	पूर्ण
पूर्ण


/*
 * Generic TI init - TI has an extension क्रम the
 * INTCTL रेजिस्टर that sets the PCI CSC पूर्णांकerrupt.
 * Make sure we set it correctly at खोलो and init
 * समय
 * - override: disable the PCI CSC पूर्णांकerrupt. This makes
 *   it possible to use the CSC पूर्णांकerrupt to probe the
 *   ISA पूर्णांकerrupts.
 * - init: set the पूर्णांकerrupt to match our PCI state.
 *   This makes us correctly get PCI CSC पूर्णांकerrupt
 *   events.
 */
अटल पूर्णांक ti_init(काष्ठा yenta_socket *socket)
अणु
	u8 new, reg = exca_पढ़ोb(socket, I365_INTCTL);

	new = reg & ~I365_INTR_ENA;
	अगर (socket->dev->irq)
		new |= I365_INTR_ENA;
	अगर (new != reg)
		exca_ग_लिखोb(socket, I365_INTCTL, new);
	वापस 0;
पूर्ण

अटल पूर्णांक ti_override(काष्ठा yenta_socket *socket)
अणु
	u8 new, reg = exca_पढ़ोb(socket, I365_INTCTL);

	new = reg & ~I365_INTR_ENA;
	अगर (new != reg)
		exca_ग_लिखोb(socket, I365_INTCTL, new);

	ti_set_zv(socket);

	वापस 0;
पूर्ण

अटल व्योम ti113x_use_isa_irq(काष्ठा yenta_socket *socket)
अणु
	पूर्णांक isa_irq = -1;
	u8 पूर्णांकctl;
	u32 isa_irq_mask = 0;

	अगर (!isa_probe)
		वापस;

	/* get a मुक्त isa पूर्णांक */
	isa_irq_mask = yenta_probe_irq(socket, isa_पूर्णांकerrupts);
	अगर (!isa_irq_mask)
		वापस; /* no useable isa irq found */

	/* choose highest available */
	क्रम (; isa_irq_mask; isa_irq++)
		isa_irq_mask >>= 1;
	socket->cb_irq = isa_irq;

	exca_ग_लिखोb(socket, I365_CSCINT, (isa_irq << 4));

	पूर्णांकctl = exca_पढ़ोb(socket, I365_INTCTL);
	पूर्णांकctl &= ~(I365_INTR_ENA | I365_IRQ_MASK);     /* CSC Enable */
	exca_ग_लिखोb(socket, I365_INTCTL, पूर्णांकctl);

	dev_info(&socket->dev->dev,
		"Yenta TI113x: using isa irq %d for CardBus\n", isa_irq);
पूर्ण


अटल पूर्णांक ti113x_override(काष्ठा yenta_socket *socket)
अणु
	u8 cardctl;

	cardctl = config_पढ़ोb(socket, TI113X_CARD_CONTROL);
	cardctl &= ~(TI113X_CCR_PCI_IRQ_ENA | TI113X_CCR_PCI_IREQ | TI113X_CCR_PCI_CSC);
	अगर (socket->dev->irq)
		cardctl |= TI113X_CCR_PCI_IRQ_ENA | TI113X_CCR_PCI_CSC | TI113X_CCR_PCI_IREQ;
	अन्यथा
		ti113x_use_isa_irq(socket);

	config_ग_लिखोb(socket, TI113X_CARD_CONTROL, cardctl);

	वापस ti_override(socket);
पूर्ण


/* irqrouting क्रम func0, probes PCI पूर्णांकerrupt and ISA पूर्णांकerrupts */
अटल व्योम ti12xx_irqroute_func0(काष्ठा yenta_socket *socket)
अणु
	u32 mfunc, mfunc_old, devctl;
	u8 gpio3, gpio3_old;
	पूर्णांक pci_irq_status;

	mfunc = mfunc_old = config_पढ़ोl(socket, TI122X_MFUNC);
	devctl = config_पढ़ोb(socket, TI113X_DEVICE_CONTROL);
	dev_info(&socket->dev->dev, "TI: mfunc 0x%08x, devctl 0x%02x\n",
		 mfunc, devctl);

	/* make sure PCI पूर्णांकerrupts are enabled beक्रमe probing */
	ti_init(socket);

	/* test PCI पूर्णांकerrupts first. only try fixing अगर वापस value is 0! */
	pci_irq_status = yenta_probe_cb_irq(socket);
	अगर (pci_irq_status)
		जाओ out;

	/*
	 * We're here which means PCI पूर्णांकerrupts are _not_ delivered. try to
	 * find the right setting (all serial or parallel)
	 */
	dev_info(&socket->dev->dev,
		 "TI: probing PCI interrupt failed, trying to fix\n");

	/* क्रम serial PCI make sure MFUNC3 is set to IRQSER */
	अगर ((devctl & TI113X_DCR_IMODE_MASK) == TI12XX_DCR_IMODE_ALL_SERIAL) अणु
		चयन (socket->dev->device) अणु
		हाल PCI_DEVICE_ID_TI_1250:
		हाल PCI_DEVICE_ID_TI_1251A:
		हाल PCI_DEVICE_ID_TI_1251B:
		हाल PCI_DEVICE_ID_TI_1450:
		हाल PCI_DEVICE_ID_TI_1451A:
		हाल PCI_DEVICE_ID_TI_4450:
		हाल PCI_DEVICE_ID_TI_4451:
			/* these chips have no IRQSER setting in MFUNC3  */
			अवरोध;

		शेष:
			mfunc = (mfunc & ~TI122X_MFUNC3_MASK) | TI122X_MFUNC3_IRQSER;

			/* ग_लिखो करोwn अगर changed, probe */
			अगर (mfunc != mfunc_old) अणु
				config_ग_लिखोl(socket, TI122X_MFUNC, mfunc);

				pci_irq_status = yenta_probe_cb_irq(socket);
				अगर (pci_irq_status == 1) अणु
					dev_info(&socket->dev->dev,
						 "TI: all-serial interrupts ok\n");
					mfunc_old = mfunc;
					जाओ out;
				पूर्ण

				/* not working, back to old value */
				mfunc = mfunc_old;
				config_ग_लिखोl(socket, TI122X_MFUNC, mfunc);

				अगर (pci_irq_status == -1)
					जाओ out;
			पूर्ण
		पूर्ण

		/* serial PCI पूर्णांकerrupts not working fall back to parallel */
		dev_info(&socket->dev->dev,
			 "TI: falling back to parallel PCI interrupts\n");
		devctl &= ~TI113X_DCR_IMODE_MASK;
		devctl |= TI113X_DCR_IMODE_SERIAL; /* serial ISA could be right */
		config_ग_लिखोb(socket, TI113X_DEVICE_CONTROL, devctl);
	पूर्ण

	/* parallel PCI पूर्णांकerrupts: route INTA */
	चयन (socket->dev->device) अणु
	हाल PCI_DEVICE_ID_TI_1250:
	हाल PCI_DEVICE_ID_TI_1251A:
	हाल PCI_DEVICE_ID_TI_1251B:
	हाल PCI_DEVICE_ID_TI_1450:
		/* make sure GPIO3 is set to INTA */
		gpio3 = gpio3_old = config_पढ़ोb(socket, TI1250_GPIO3_CONTROL);
		gpio3 &= ~TI1250_GPIO_MODE_MASK;
		अगर (gpio3 != gpio3_old)
			config_ग_लिखोb(socket, TI1250_GPIO3_CONTROL, gpio3);
		अवरोध;

	शेष:
		gpio3 = gpio3_old = 0;

		mfunc = (mfunc & ~TI122X_MFUNC0_MASK) | TI122X_MFUNC0_INTA;
		अगर (mfunc != mfunc_old)
			config_ग_लिखोl(socket, TI122X_MFUNC, mfunc);
	पूर्ण

	/* समय to probe again */
	pci_irq_status = yenta_probe_cb_irq(socket);
	अगर (pci_irq_status == 1) अणु
		mfunc_old = mfunc;
		dev_info(&socket->dev->dev, "TI: parallel PCI interrupts ok\n");
	पूर्ण अन्यथा अणु
		/* not working, back to old value */
		mfunc = mfunc_old;
		config_ग_लिखोl(socket, TI122X_MFUNC, mfunc);
		अगर (gpio3 != gpio3_old)
			config_ग_लिखोb(socket, TI1250_GPIO3_CONTROL, gpio3_old);
	पूर्ण

out:
	अगर (pci_irq_status < 1) अणु
		socket->cb_irq = 0;
		dev_info(&socket->dev->dev,
			 "Yenta TI: no PCI interrupts. Fish. Please report.\n");
	पूर्ण
पूर्ण


/* changes the irq of func1 to match that of func0 */
अटल पूर्णांक ti12xx_align_irqs(काष्ठा yenta_socket *socket, पूर्णांक *old_irq)
अणु
	काष्ठा pci_dev *func0;

	/* find func0 device */
	func0 = pci_get_slot(socket->dev->bus, socket->dev->devfn & ~0x07);
	अगर (!func0)
		वापस 0;

	अगर (old_irq)
		*old_irq = socket->cb_irq;
	socket->cb_irq = socket->dev->irq = func0->irq;

	pci_dev_put(func0);

	वापस 1;
पूर्ण

/*
 * ties INTA and INTB together. also changes the devices irq to that of
 * the function 0 device. call from func1 only.
 * वापसs 1 अगर INTRTIE changed, 0 otherwise.
 */
अटल पूर्णांक ti12xx_tie_पूर्णांकerrupts(काष्ठा yenta_socket *socket, पूर्णांक *old_irq)
अणु
	u32 sysctl;
	पूर्णांक ret;

	sysctl = config_पढ़ोl(socket, TI113X_SYSTEM_CONTROL);
	अगर (sysctl & TI122X_SCR_INTRTIE)
		वापस 0;

	/* align */
	ret = ti12xx_align_irqs(socket, old_irq);
	अगर (!ret)
		वापस 0;

	/* tie */
	sysctl |= TI122X_SCR_INTRTIE;
	config_ग_लिखोl(socket, TI113X_SYSTEM_CONTROL, sysctl);

	वापस 1;
पूर्ण

/* unकरो what ti12xx_tie_पूर्णांकerrupts() did */
अटल व्योम ti12xx_untie_पूर्णांकerrupts(काष्ठा yenta_socket *socket, पूर्णांक old_irq)
अणु
	u32 sysctl = config_पढ़ोl(socket, TI113X_SYSTEM_CONTROL);
	sysctl &= ~TI122X_SCR_INTRTIE;
	config_ग_लिखोl(socket, TI113X_SYSTEM_CONTROL, sysctl);

	socket->cb_irq = socket->dev->irq = old_irq;
पूर्ण

/* 
 * irqrouting क्रम func1, plays with INTB routing
 * only touches MFUNC क्रम INTB routing. all other bits are taken
 * care of in func0 alपढ़ोy.
 */
अटल व्योम ti12xx_irqroute_func1(काष्ठा yenta_socket *socket)
अणु
	u32 mfunc, mfunc_old, devctl, sysctl;
	पूर्णांक pci_irq_status;

	mfunc = mfunc_old = config_पढ़ोl(socket, TI122X_MFUNC);
	devctl = config_पढ़ोb(socket, TI113X_DEVICE_CONTROL);
	dev_info(&socket->dev->dev, "TI: mfunc 0x%08x, devctl 0x%02x\n",
		 mfunc, devctl);

	/* अगर IRQs are configured as tied, align irq of func1 with func0 */
	sysctl = config_पढ़ोl(socket, TI113X_SYSTEM_CONTROL);
	अगर (sysctl & TI122X_SCR_INTRTIE)
		ti12xx_align_irqs(socket, शून्य);

	/* make sure PCI पूर्णांकerrupts are enabled beक्रमe probing */
	ti_init(socket);

	/* test PCI पूर्णांकerrupts first. only try fixing अगर वापस value is 0! */
	pci_irq_status = yenta_probe_cb_irq(socket);
	अगर (pci_irq_status)
		जाओ out;

	/*
	 * We're here which means PCI पूर्णांकerrupts are _not_ delivered. try to
	 * find the right setting
	 */
	dev_info(&socket->dev->dev,
		 "TI: probing PCI interrupt failed, trying to fix\n");

	/* अगर all serial: set INTRTIE, probe again */
	अगर ((devctl & TI113X_DCR_IMODE_MASK) == TI12XX_DCR_IMODE_ALL_SERIAL) अणु
		पूर्णांक old_irq;

		अगर (ti12xx_tie_पूर्णांकerrupts(socket, &old_irq)) अणु
			pci_irq_status = yenta_probe_cb_irq(socket);
			अगर (pci_irq_status == 1) अणु
				dev_info(&socket->dev->dev,
					 "TI: all-serial interrupts, tied ok\n");
				जाओ out;
			पूर्ण

			ti12xx_untie_पूर्णांकerrupts(socket, old_irq);
		पूर्ण
	पूर्ण
	/* parallel PCI: route INTB, probe again */
	अन्यथा अणु
		पूर्णांक old_irq;

		चयन (socket->dev->device) अणु
		हाल PCI_DEVICE_ID_TI_1250:
			/* the 1250 has one pin क्रम IRQSER/INTB depending on devctl */
			अवरोध;

		हाल PCI_DEVICE_ID_TI_1251A:
		हाल PCI_DEVICE_ID_TI_1251B:
		हाल PCI_DEVICE_ID_TI_1450:
			/*
			 *  those have a pin क्रम IRQSER/INTB plus INTB in MFUNC0
			 *  we alपढ़ो probed the shared pin, now go क्रम MFUNC0
			 */
			mfunc = (mfunc & ~TI122X_MFUNC0_MASK) | TI125X_MFUNC0_INTB;
			अवरोध;

		शेष:
			mfunc = (mfunc & ~TI122X_MFUNC1_MASK) | TI122X_MFUNC1_INTB;
			अवरोध;
		पूर्ण

		/* ग_लिखो, probe */
		अगर (mfunc != mfunc_old) अणु
			config_ग_लिखोl(socket, TI122X_MFUNC, mfunc);

			pci_irq_status = yenta_probe_cb_irq(socket);
			अगर (pci_irq_status == 1) अणु
				dev_info(&socket->dev->dev,
					 "TI: parallel PCI interrupts ok\n");
				जाओ out;
			पूर्ण

			mfunc = mfunc_old;
			config_ग_लिखोl(socket, TI122X_MFUNC, mfunc);

			अगर (pci_irq_status == -1)
				जाओ out;
		पूर्ण

		/* still nothing: set INTRTIE */
		अगर (ti12xx_tie_पूर्णांकerrupts(socket, &old_irq)) अणु
			pci_irq_status = yenta_probe_cb_irq(socket);
			अगर (pci_irq_status == 1) अणु
				dev_info(&socket->dev->dev,
					 "TI: parallel PCI interrupts, tied ok\n");
				जाओ out;
			पूर्ण

			ti12xx_untie_पूर्णांकerrupts(socket, old_irq);
		पूर्ण
	पूर्ण

out:
	अगर (pci_irq_status < 1) अणु
		socket->cb_irq = 0;
		dev_info(&socket->dev->dev,
			 "TI: no PCI interrupts. Fish. Please report.\n");
	पूर्ण
पूर्ण


/* Returns true value अगर the second slot of a two-slot controller is empty */
अटल पूर्णांक ti12xx_2nd_slot_empty(काष्ठा yenta_socket *socket)
अणु
	काष्ठा pci_dev *func;
	काष्ठा yenta_socket *slot2;
	पूर्णांक devfn;
	अचिन्हित पूर्णांक state;
	पूर्णांक ret = 1;
	u32 sysctl;

	/* catch the two-slot controllers */
	चयन (socket->dev->device) अणु
	हाल PCI_DEVICE_ID_TI_1220:
	हाल PCI_DEVICE_ID_TI_1221:
	हाल PCI_DEVICE_ID_TI_1225:
	हाल PCI_DEVICE_ID_TI_1251A:
	हाल PCI_DEVICE_ID_TI_1251B:
	हाल PCI_DEVICE_ID_TI_1420:
	हाल PCI_DEVICE_ID_TI_1450:
	हाल PCI_DEVICE_ID_TI_1451A:
	हाल PCI_DEVICE_ID_TI_1520:
	हाल PCI_DEVICE_ID_TI_1620:
	हाल PCI_DEVICE_ID_TI_4520:
	हाल PCI_DEVICE_ID_TI_4450:
	हाल PCI_DEVICE_ID_TI_4451:
		/*
		 * there are way more, but they need to be added in yenta_socket.c
		 * and pci_ids.h first anyway.
		 */
		अवरोध;

	हाल PCI_DEVICE_ID_TI_XX12:
	हाल PCI_DEVICE_ID_TI_X515:
	हाल PCI_DEVICE_ID_TI_X420:
	हाल PCI_DEVICE_ID_TI_X620:
	हाल PCI_DEVICE_ID_TI_XX21_XX11:
	हाल PCI_DEVICE_ID_TI_7410:
	हाल PCI_DEVICE_ID_TI_7610:
		/*
		 * those are either single or dual slot CB with additional functions
		 * like 1394, smartcard पढ़ोer, etc. check the TIEALL flag क्रम them
		 * the TIEALL flag binds the IRQ of all functions together.
		 * we catch the single slot variants later.
		 */
		sysctl = config_पढ़ोl(socket, TI113X_SYSTEM_CONTROL);
		अगर (sysctl & TIXX21_SCR_TIEALL)
			वापस 0;

		अवरोध;

	/* single-slot controllers have the 2nd slot empty always :) */
	शेष:
		वापस 1;
	पूर्ण

	/* get other slot */
	devfn = socket->dev->devfn & ~0x07;
	func = pci_get_slot(socket->dev->bus,
	                    (socket->dev->devfn & 0x07) ? devfn : devfn | 0x01);
	अगर (!func)
		वापस 1;

	/*
	 * check that the device id of both slots match. this is needed क्रम the
	 * XX21 and the XX11 controller that share the same device id क्रम single
	 * and dual slot controllers. वापस '2nd slot empty'. we alपढ़ोy checked
	 * अगर the पूर्णांकerrupt is tied to another function.
	 */
	अगर (socket->dev->device != func->device)
		जाओ out;

	slot2 = pci_get_drvdata(func);
	अगर (!slot2)
		जाओ out;

	/* check state */
	yenta_get_status(&slot2->socket, &state);
	अगर (state & SS_DETECT) अणु
		ret = 0;
		जाओ out;
	पूर्ण

out:
	pci_dev_put(func);
	वापस ret;
पूर्ण

/*
 * TI specअगरiy parts क्रम the घातer hook.
 *
 * some TI's with some CB's produces पूर्णांकerrupt storm on घातer on. it has been
 * seen with atheros wlan cards on TI1225 and TI1410. solution is simply to
 * disable any CB पूर्णांकerrupts during this समय.
 */
अटल पूर्णांक ti12xx_घातer_hook(काष्ठा pcmcia_socket *sock, पूर्णांक operation)
अणु
	काष्ठा yenta_socket *socket = container_of(sock, काष्ठा yenta_socket, socket);
	u32 mfunc, devctl, sysctl;
	u8 gpio3;

	/* only POWER_PRE and POWER_POST are पूर्णांकeresting */
	अगर ((operation != HOOK_POWER_PRE) && (operation != HOOK_POWER_POST))
		वापस 0;

	devctl = config_पढ़ोb(socket, TI113X_DEVICE_CONTROL);
	sysctl = config_पढ़ोl(socket, TI113X_SYSTEM_CONTROL);
	mfunc = config_पढ़ोl(socket, TI122X_MFUNC);

	/*
	 * all serial/tied: only disable when modparm set. always करोing it
	 * would mean a regression क्रम working setups 'cos it disables the
	 * पूर्णांकerrupts क्रम both both slots on 2-slot controllers
	 * (and users of single slot controllers where it's save have to
	 * live with setting the modparm, most करोn't have to anyway)
	 */
	अगर (((devctl & TI113X_DCR_IMODE_MASK) == TI12XX_DCR_IMODE_ALL_SERIAL) &&
	    (pwr_irqs_off || ti12xx_2nd_slot_empty(socket))) अणु
		चयन (socket->dev->device) अणु
		हाल PCI_DEVICE_ID_TI_1250:
		हाल PCI_DEVICE_ID_TI_1251A:
		हाल PCI_DEVICE_ID_TI_1251B:
		हाल PCI_DEVICE_ID_TI_1450:
		हाल PCI_DEVICE_ID_TI_1451A:
		हाल PCI_DEVICE_ID_TI_4450:
		हाल PCI_DEVICE_ID_TI_4451:
			/* these chips have no IRQSER setting in MFUNC3  */
			अवरोध;

		शेष:
			अगर (operation == HOOK_POWER_PRE)
				mfunc = (mfunc & ~TI122X_MFUNC3_MASK);
			अन्यथा
				mfunc = (mfunc & ~TI122X_MFUNC3_MASK) | TI122X_MFUNC3_IRQSER;
		पूर्ण

		वापस 0;
	पूर्ण

	/* करो the job dअगरferently क्रम func0/1 */
	अगर ((PCI_FUNC(socket->dev->devfn) == 0) ||
	    ((sysctl & TI122X_SCR_INTRTIE) &&
	     (pwr_irqs_off || ti12xx_2nd_slot_empty(socket)))) अणु
		/* some bridges are dअगरferent */
		चयन (socket->dev->device) अणु
		हाल PCI_DEVICE_ID_TI_1250:
		हाल PCI_DEVICE_ID_TI_1251A:
		हाल PCI_DEVICE_ID_TI_1251B:
		हाल PCI_DEVICE_ID_TI_1450:
			/* those oldies use gpio3 क्रम INTA */
			gpio3 = config_पढ़ोb(socket, TI1250_GPIO3_CONTROL);
			अगर (operation == HOOK_POWER_PRE)
				gpio3 = (gpio3 & ~TI1250_GPIO_MODE_MASK) | 0x40;
			अन्यथा
				gpio3 &= ~TI1250_GPIO_MODE_MASK;
			config_ग_लिखोb(socket, TI1250_GPIO3_CONTROL, gpio3);
			अवरोध;

		शेष:
			/* all new bridges are the same */
			अगर (operation == HOOK_POWER_PRE)
				mfunc &= ~TI122X_MFUNC0_MASK;
			अन्यथा
				mfunc |= TI122X_MFUNC0_INTA;
			config_ग_लिखोl(socket, TI122X_MFUNC, mfunc);
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (socket->dev->device) अणु
		हाल PCI_DEVICE_ID_TI_1251A:
		हाल PCI_DEVICE_ID_TI_1251B:
		हाल PCI_DEVICE_ID_TI_1450:
			/* those have INTA अन्यथाwhere and INTB in MFUNC0 */
			अगर (operation == HOOK_POWER_PRE)
				mfunc &= ~TI122X_MFUNC0_MASK;
			अन्यथा
				mfunc |= TI125X_MFUNC0_INTB;
			config_ग_लिखोl(socket, TI122X_MFUNC, mfunc);

			अवरोध;

		शेष:
			/* all new bridges are the same */
			अगर (operation == HOOK_POWER_PRE)
				mfunc &= ~TI122X_MFUNC1_MASK;
			अन्यथा
				mfunc |= TI122X_MFUNC1_INTB;
			config_ग_लिखोl(socket, TI122X_MFUNC, mfunc);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ti12xx_override(काष्ठा yenta_socket *socket)
अणु
	u32 val, val_orig;

	/* make sure that memory burst is active */
	val_orig = val = config_पढ़ोl(socket, TI113X_SYSTEM_CONTROL);
	अगर (disable_clkrun && PCI_FUNC(socket->dev->devfn) == 0) अणु
		dev_info(&socket->dev->dev, "Disabling CLKRUN feature\n");
		val |= TI113X_SCR_KEEPCLK;
	पूर्ण
	अगर (!(val & TI122X_SCR_MRBURSTUP)) अणु
		dev_info(&socket->dev->dev,
			 "Enabling burst memory read transactions\n");
		val |= TI122X_SCR_MRBURSTUP;
	पूर्ण
	अगर (val_orig != val)
		config_ग_लिखोl(socket, TI113X_SYSTEM_CONTROL, val);

	/*
	 * Yenta expects controllers to use CSCINT to route
	 * CSC पूर्णांकerrupts to PCI rather than INTVAL.
	 */
	val = config_पढ़ोb(socket, TI1250_DIAGNOSTIC);
	dev_info(&socket->dev->dev, "Using %s to route CSC interrupts to PCI\n",
		 (val & TI1250_DIAG_PCI_CSC) ? "CSCINT" : "INTVAL");
	dev_info(&socket->dev->dev, "Routing CardBus interrupts to %s\n",
		 (val & TI1250_DIAG_PCI_IREQ) ? "PCI" : "ISA");

	/* करो irqrouting, depending on function */
	अगर (PCI_FUNC(socket->dev->devfn) == 0)
		ti12xx_irqroute_func0(socket);
	अन्यथा
		ti12xx_irqroute_func1(socket);

	/* install घातer hook */
	socket->socket.घातer_hook = ti12xx_घातer_hook;

	वापस ti_override(socket);
पूर्ण


अटल पूर्णांक ti1250_override(काष्ठा yenta_socket *socket)
अणु
	u8 old, diag;

	old = config_पढ़ोb(socket, TI1250_DIAGNOSTIC);
	diag = old & ~(TI1250_DIAG_PCI_CSC | TI1250_DIAG_PCI_IREQ);
	अगर (socket->cb_irq)
		diag |= TI1250_DIAG_PCI_CSC | TI1250_DIAG_PCI_IREQ;

	अगर (diag != old) अणु
		dev_info(&socket->dev->dev,
			 "adjusting diagnostic: %02x -> %02x\n",
			 old, diag);
		config_ग_लिखोb(socket, TI1250_DIAGNOSTIC, diag);
	पूर्ण

	वापस ti12xx_override(socket);
पूर्ण


/**
 * EnE specअगरic part. EnE bridges are रेजिस्टर compatible with TI bridges but
 * have their own test रेजिस्टरs and more important their own little problems.
 * Some fixup code to make everybody happy (TM).
 */

#अगर_घोषित CONFIG_YENTA_ENE_TUNE
/*
 * set/clear various test bits:
 * Defaults to clear the bit.
 * - mask (u8) defines what bits to change
 * - bits (u8) is the values to change them to
 * -> it's
 * 	current = (current & ~mask) | bits
 */
/* pci ids of devices that wants to have the bit set */
#घोषणा DEVID(_vend,_dev,_subvend,_subdev,mask,bits) अणु		\
		.venकरोr		= _vend,			\
		.device		= _dev,				\
		.subvenकरोr	= _subvend,			\
		.subdevice	= _subdev,			\
		.driver_data	= ((mask) << 8 | (bits)),	\
	पूर्ण
अटल काष्ठा pci_device_id ene_tune_tbl[] = अणु
	/* Echo Audio products based on motorola DSP56301 and DSP56361 */
	DEVID(PCI_VENDOR_ID_MOTOROLA, 0x1801, 0xECC0, PCI_ANY_ID,
		ENE_TEST_C9_TLTENABLE | ENE_TEST_C9_PFENABLE, ENE_TEST_C9_TLTENABLE),
	DEVID(PCI_VENDOR_ID_MOTOROLA, 0x3410, 0xECC0, PCI_ANY_ID,
		ENE_TEST_C9_TLTENABLE | ENE_TEST_C9_PFENABLE, ENE_TEST_C9_TLTENABLE),

	अणुपूर्ण
पूर्ण;

अटल व्योम ene_tune_bridge(काष्ठा pcmcia_socket *sock, काष्ठा pci_bus *bus)
अणु
	काष्ठा yenta_socket *socket = container_of(sock, काष्ठा yenta_socket, socket);
	काष्ठा pci_dev *dev;
	काष्ठा pci_device_id *id = शून्य;
	u8 test_c9, old_c9, mask, bits;

	list_क्रम_each_entry(dev, &bus->devices, bus_list) अणु
		id = (काष्ठा pci_device_id *) pci_match_id(ene_tune_tbl, dev);
		अगर (id)
			अवरोध;
	पूर्ण

	test_c9 = old_c9 = config_पढ़ोb(socket, ENE_TEST_C9);
	अगर (id) अणु
		mask = (id->driver_data >> 8) & 0xFF;
		bits = id->driver_data & 0xFF;

		test_c9 = (test_c9 & ~mask) | bits;
	पूर्ण
	अन्यथा
		/* शेष to clear TLTEnable bit, old behaviour */
		test_c9 &= ~ENE_TEST_C9_TLTENABLE;

	dev_info(&socket->dev->dev,
		 "EnE: changing testregister 0xC9, %02x -> %02x\n",
		 old_c9, test_c9);
	config_ग_लिखोb(socket, ENE_TEST_C9, test_c9);
पूर्ण

अटल पूर्णांक ene_override(काष्ठा yenta_socket *socket)
अणु
	/* install tune_bridge() function */
	socket->socket.tune_bridge = ene_tune_bridge;

	वापस ti1250_override(socket);
पूर्ण
#अन्यथा
#  define ene_override ti1250_override
#पूर्ण_अगर /* !CONFIG_YENTA_ENE_TUNE */

#पूर्ण_अगर /* _LINUX_TI113X_H */

