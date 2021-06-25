<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * budget-ci.c: driver क्रम the SAA7146 based Budget DVB cards
 *
 * Compiled from various sources by Michael Hunold <michael@mihu.de>
 *
 *     msp430 IR support contributed by Jack Thomasson <jkt@Helius.COM>
 *     partially based on the Siemens DVB driver by Ralph+Marcus Metzler
 *
 * CI पूर्णांकerface support (c) 2004 Andrew de Quincey <adq_dvb@lidskialf.net>
 *
 * the project's page is at https://linuxtv.org
 */

#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <media/rc-core.h>

#समावेश "budget.h"

#समावेश <media/dvb_ca_en50221.h>
#समावेश "stv0299.h"
#समावेश "stv0297.h"
#समावेश "tda1004x.h"
#समावेश "stb0899_drv.h"
#समावेश "stb0899_reg.h"
#समावेश "stb0899_cfg.h"
#समावेश "stb6100.h"
#समावेश "stb6100_cfg.h"
#समावेश "lnbp21.h"
#समावेश "bsbe1.h"
#समावेश "bsru6.h"
#समावेश "tda1002x.h"
#समावेश "tda827x.h"
#समावेश "bsbe1-d01a.h"

#घोषणा MODULE_NAME "budget_ci"

/*
 * Regarding DEBIADDR_IR:
 * Some CI modules hang अगर अक्रमom addresses are पढ़ो.
 * Using address 0x4000 क्रम the IR पढ़ो means that we
 * use the same address as क्रम CI version, which should
 * be a safe शेष.
 */
#घोषणा DEBIADDR_IR		0x4000
#घोषणा DEBIADDR_CICONTROL	0x0000
#घोषणा DEBIADDR_CIVERSION	0x4000
#घोषणा DEBIADDR_IO		0x1000
#घोषणा DEBIADDR_ATTR		0x3000

#घोषणा CICONTROL_RESET		0x01
#घोषणा CICONTROL_ENABLETS	0x02
#घोषणा CICONTROL_CAMDETECT	0x08

#घोषणा DEBICICTL		0x00420000
#घोषणा DEBICICAM		0x02420000

#घोषणा SLOTSTATUS_NONE		1
#घोषणा SLOTSTATUS_PRESENT	2
#घोषणा SLOTSTATUS_RESET	4
#घोषणा SLOTSTATUS_READY	8
#घोषणा SLOTSTATUS_OCCUPIED	(SLOTSTATUS_PRESENT|SLOTSTATUS_RESET|SLOTSTATUS_READY)

/* RC5 device wildcard */
#घोषणा IR_DEVICE_ANY		255

अटल पूर्णांक rc5_device = -1;
module_param(rc5_device, पूर्णांक, 0644);
MODULE_PARM_DESC(rc5_device, "only IR commands to given RC5 device (device = 0 - 31, any device = 255, default: autodetect)");

अटल पूर्णांक ir_debug;
module_param(ir_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(ir_debug, "enable debugging information for IR decoding");

DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

काष्ठा budget_ci_ir अणु
	काष्ठा rc_dev *dev;
	काष्ठा tasklet_काष्ठा msp430_irq_tasklet;
	अक्षर name[72]; /* 40 + 32 क्रम (काष्ठा saa7146_dev).name */
	अक्षर phys[32];
	पूर्णांक rc5_device;
	u32 ir_key;
	bool have_command;
	bool full_rc5;		/* Outमाला_दो a full RC5 code */
पूर्ण;

काष्ठा budget_ci अणु
	काष्ठा budget budget;
	काष्ठा tasklet_काष्ठा ciपूर्णांकf_irq_tasklet;
	पूर्णांक slot_status;
	पूर्णांक ci_irq;
	काष्ठा dvb_ca_en50221 ca;
	काष्ठा budget_ci_ir ir;
	u8 tuner_pll_address; /* used क्रम philips_tdm1316l configs */
पूर्ण;

अटल व्योम msp430_ir_पूर्णांकerrupt(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा budget_ci_ir *ir = from_tasklet(ir, t, msp430_irq_tasklet);
	काष्ठा budget_ci *budget_ci = container_of(ir, typeof(*budget_ci), ir);
	काष्ठा rc_dev *dev = budget_ci->ir.dev;
	u32 command = ttpci_budget_debiपढ़ो(&budget_ci->budget, DEBINOSWAP, DEBIADDR_IR, 2, 1, 0) >> 8;

	/*
	 * The msp430 chip can generate two dअगरferent bytes, command and device
	 *
	 * type1: X1CCCCCC, C = command bits (0 - 63)
	 * type2: X0TDDDDD, D = device bits (0 - 31), T = RC5 toggle bit
	 *
	 * Each संकेत from the remote control can generate one or more command
	 * bytes and one or more device bytes. For the repeated bytes, the
	 * highest bit (X) is set. The first command byte is always generated
	 * beक्रमe the first device byte. Other than that, no specअगरic order
	 * seems to apply. To make lअगरe पूर्णांकeresting, bytes can also be lost.
	 *
	 * Only when we have a command and device byte, a keypress is
	 * generated.
	 */

	अगर (ir_debug)
		prपूर्णांकk("budget_ci: received byte 0x%02x\n", command);

	/* Remove repeat bit, we use every command */
	command = command & 0x7f;

	/* Is this a RC5 command byte? */
	अगर (command & 0x40) अणु
		budget_ci->ir.have_command = true;
		budget_ci->ir.ir_key = command & 0x3f;
		वापस;
	पूर्ण

	/* It's a RC5 device byte */
	अगर (!budget_ci->ir.have_command)
		वापस;
	budget_ci->ir.have_command = false;

	अगर (budget_ci->ir.rc5_device != IR_DEVICE_ANY &&
	    budget_ci->ir.rc5_device != (command & 0x1f))
		वापस;

	अगर (budget_ci->ir.full_rc5) अणु
		rc_keyकरोwn(dev, RC_PROTO_RC5,
			   RC_SCANCODE_RC5(budget_ci->ir.rc5_device, budget_ci->ir.ir_key),
			   !!(command & 0x20));
		वापस;
	पूर्ण

	/* FIXME: We should generate complete scancodes क्रम all devices */
	rc_keyकरोwn(dev, RC_PROTO_UNKNOWN, budget_ci->ir.ir_key,
		   !!(command & 0x20));
पूर्ण

अटल पूर्णांक msp430_ir_init(काष्ठा budget_ci *budget_ci)
अणु
	काष्ठा saa7146_dev *saa = budget_ci->budget.dev;
	काष्ठा rc_dev *dev;
	पूर्णांक error;

	dev = rc_allocate_device(RC_DRIVER_SCANCODE);
	अगर (!dev) अणु
		prपूर्णांकk(KERN_ERR "budget_ci: IR interface initialisation failed\n");
		वापस -ENOMEM;
	पूर्ण

	snम_लिखो(budget_ci->ir.name, माप(budget_ci->ir.name),
		 "Budget-CI dvb ir receiver %s", saa->name);
	snम_लिखो(budget_ci->ir.phys, माप(budget_ci->ir.phys),
		 "pci-%s/ir0", pci_name(saa->pci));

	dev->driver_name = MODULE_NAME;
	dev->device_name = budget_ci->ir.name;
	dev->input_phys = budget_ci->ir.phys;
	dev->input_id.bustype = BUS_PCI;
	dev->input_id.version = 1;
	अगर (saa->pci->subप्रणाली_venकरोr) अणु
		dev->input_id.venकरोr = saa->pci->subप्रणाली_venकरोr;
		dev->input_id.product = saa->pci->subप्रणाली_device;
	पूर्ण अन्यथा अणु
		dev->input_id.venकरोr = saa->pci->venकरोr;
		dev->input_id.product = saa->pci->device;
	पूर्ण
	dev->dev.parent = &saa->pci->dev;

	अगर (rc5_device < 0)
		budget_ci->ir.rc5_device = IR_DEVICE_ANY;
	अन्यथा
		budget_ci->ir.rc5_device = rc5_device;

	/* Select keymap and address */
	चयन (budget_ci->budget.dev->pci->subप्रणाली_device) अणु
	हाल 0x100c:
	हाल 0x100f:
	हाल 0x1011:
	हाल 0x1012:
		/* The hauppauge keymap is a superset of these remotes */
		dev->map_name = RC_MAP_HAUPPAUGE;
		budget_ci->ir.full_rc5 = true;

		अगर (rc5_device < 0)
			budget_ci->ir.rc5_device = 0x1f;
		अवरोध;
	हाल 0x1010:
	हाल 0x1017:
	हाल 0x1019:
	हाल 0x101a:
	हाल 0x101b:
		/* क्रम the Technotrend 1500 bundled remote */
		dev->map_name = RC_MAP_TT_1500;
		अवरोध;
	शेष:
		/* unknown remote */
		dev->map_name = RC_MAP_BUDGET_CI_OLD;
		अवरोध;
	पूर्ण
	अगर (!budget_ci->ir.full_rc5)
		dev->scancode_mask = 0xff;

	error = rc_रेजिस्टर_device(dev);
	अगर (error) अणु
		prपूर्णांकk(KERN_ERR "budget_ci: could not init driver for IR device (code %d)\n", error);
		rc_मुक्त_device(dev);
		वापस error;
	पूर्ण

	budget_ci->ir.dev = dev;

	tasklet_setup(&budget_ci->ir.msp430_irq_tasklet, msp430_ir_पूर्णांकerrupt);

	SAA7146_IER_ENABLE(saa, MASK_06);
	saa7146_setgpio(saa, 3, SAA7146_GPIO_IRQHI);

	वापस 0;
पूर्ण

अटल व्योम msp430_ir_deinit(काष्ठा budget_ci *budget_ci)
अणु
	काष्ठा saa7146_dev *saa = budget_ci->budget.dev;

	SAA7146_IER_DISABLE(saa, MASK_06);
	saa7146_setgpio(saa, 3, SAA7146_GPIO_INPUT);
	tasklet_समाप्त(&budget_ci->ir.msp430_irq_tasklet);

	rc_unरेजिस्टर_device(budget_ci->ir.dev);
पूर्ण

अटल पूर्णांक ciपूर्णांकf_पढ़ो_attribute_mem(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot, पूर्णांक address)
अणु
	काष्ठा budget_ci *budget_ci = (काष्ठा budget_ci *) ca->data;

	अगर (slot != 0)
		वापस -EINVAL;

	वापस ttpci_budget_debiपढ़ो(&budget_ci->budget, DEBICICAM,
				     DEBIADDR_ATTR | (address & 0xfff), 1, 1, 0);
पूर्ण

अटल पूर्णांक ciपूर्णांकf_ग_लिखो_attribute_mem(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot, पूर्णांक address, u8 value)
अणु
	काष्ठा budget_ci *budget_ci = (काष्ठा budget_ci *) ca->data;

	अगर (slot != 0)
		वापस -EINVAL;

	वापस ttpci_budget_debiग_लिखो(&budget_ci->budget, DEBICICAM,
				      DEBIADDR_ATTR | (address & 0xfff), 1, value, 1, 0);
पूर्ण

अटल पूर्णांक ciपूर्णांकf_पढ़ो_cam_control(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot, u8 address)
अणु
	काष्ठा budget_ci *budget_ci = (काष्ठा budget_ci *) ca->data;

	अगर (slot != 0)
		वापस -EINVAL;

	वापस ttpci_budget_debiपढ़ो(&budget_ci->budget, DEBICICAM,
				     DEBIADDR_IO | (address & 3), 1, 1, 0);
पूर्ण

अटल पूर्णांक ciपूर्णांकf_ग_लिखो_cam_control(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot, u8 address, u8 value)
अणु
	काष्ठा budget_ci *budget_ci = (काष्ठा budget_ci *) ca->data;

	अगर (slot != 0)
		वापस -EINVAL;

	वापस ttpci_budget_debiग_लिखो(&budget_ci->budget, DEBICICAM,
				      DEBIADDR_IO | (address & 3), 1, value, 1, 0);
पूर्ण

अटल पूर्णांक ciपूर्णांकf_slot_reset(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot)
अणु
	काष्ठा budget_ci *budget_ci = (काष्ठा budget_ci *) ca->data;
	काष्ठा saa7146_dev *saa = budget_ci->budget.dev;

	अगर (slot != 0)
		वापस -EINVAL;

	अगर (budget_ci->ci_irq) अणु
		// trigger on RISING edge during reset so we know when READY is re-निश्चितed
		saa7146_setgpio(saa, 0, SAA7146_GPIO_IRQHI);
	पूर्ण
	budget_ci->slot_status = SLOTSTATUS_RESET;
	ttpci_budget_debiग_लिखो(&budget_ci->budget, DEBICICTL, DEBIADDR_CICONTROL, 1, 0, 1, 0);
	msleep(1);
	ttpci_budget_debiग_लिखो(&budget_ci->budget, DEBICICTL, DEBIADDR_CICONTROL, 1,
			       CICONTROL_RESET, 1, 0);

	saa7146_setgpio(saa, 1, SAA7146_GPIO_OUTHI);
	ttpci_budget_set_video_port(saa, BUDGET_VIDEO_PORTB);
	वापस 0;
पूर्ण

अटल पूर्णांक ciपूर्णांकf_slot_shutकरोwn(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot)
अणु
	काष्ठा budget_ci *budget_ci = (काष्ठा budget_ci *) ca->data;
	काष्ठा saa7146_dev *saa = budget_ci->budget.dev;

	अगर (slot != 0)
		वापस -EINVAL;

	saa7146_setgpio(saa, 1, SAA7146_GPIO_OUTHI);
	ttpci_budget_set_video_port(saa, BUDGET_VIDEO_PORTB);
	वापस 0;
पूर्ण

अटल पूर्णांक ciपूर्णांकf_slot_ts_enable(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot)
अणु
	काष्ठा budget_ci *budget_ci = (काष्ठा budget_ci *) ca->data;
	काष्ठा saa7146_dev *saa = budget_ci->budget.dev;
	पूर्णांक पंचांगp;

	अगर (slot != 0)
		वापस -EINVAL;

	saa7146_setgpio(saa, 1, SAA7146_GPIO_OUTLO);

	पंचांगp = ttpci_budget_debiपढ़ो(&budget_ci->budget, DEBICICTL, DEBIADDR_CICONTROL, 1, 1, 0);
	ttpci_budget_debiग_लिखो(&budget_ci->budget, DEBICICTL, DEBIADDR_CICONTROL, 1,
			       पंचांगp | CICONTROL_ENABLETS, 1, 0);

	ttpci_budget_set_video_port(saa, BUDGET_VIDEO_PORTA);
	वापस 0;
पूर्ण

अटल व्योम ciपूर्णांकf_पूर्णांकerrupt(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा budget_ci *budget_ci = from_tasklet(budget_ci, t,
						   ciपूर्णांकf_irq_tasklet);
	काष्ठा saa7146_dev *saa = budget_ci->budget.dev;
	अचिन्हित पूर्णांक flags;

	// ensure we करोn't get spurious IRQs during initialisation
	अगर (!budget_ci->budget.ci_present)
		वापस;

	// पढ़ो the CAM status
	flags = ttpci_budget_debiपढ़ो(&budget_ci->budget, DEBICICTL, DEBIADDR_CICONTROL, 1, 1, 0);
	अगर (flags & CICONTROL_CAMDETECT) अणु

		// GPIO should be set to trigger on falling edge अगर a CAM is present
		saa7146_setgpio(saa, 0, SAA7146_GPIO_IRQLO);

		अगर (budget_ci->slot_status & SLOTSTATUS_NONE) अणु
			// CAM insertion IRQ
			budget_ci->slot_status = SLOTSTATUS_PRESENT;
			dvb_ca_en50221_camchange_irq(&budget_ci->ca, 0,
						     DVB_CA_EN50221_CAMCHANGE_INSERTED);

		पूर्ण अन्यथा अगर (budget_ci->slot_status & SLOTSTATUS_RESET) अणु
			// CAM पढ़ोy (reset completed)
			budget_ci->slot_status = SLOTSTATUS_READY;
			dvb_ca_en50221_camपढ़ोy_irq(&budget_ci->ca, 0);

		पूर्ण अन्यथा अगर (budget_ci->slot_status & SLOTSTATUS_READY) अणु
			// FR/DA IRQ
			dvb_ca_en50221_frda_irq(&budget_ci->ca, 0);
		पूर्ण
	पूर्ण अन्यथा अणु

		// trigger on rising edge अगर a CAM is not present - when a CAM is inserted, we
		// only want to get the IRQ when it sets READY. If we trigger on the falling edge,
		// the CAM might not actually be पढ़ोy yet.
		saa7146_setgpio(saa, 0, SAA7146_GPIO_IRQHI);

		// generate a CAM removal IRQ अगर we haven't alपढ़ोy
		अगर (budget_ci->slot_status & SLOTSTATUS_OCCUPIED) अणु
			// CAM removal IRQ
			budget_ci->slot_status = SLOTSTATUS_NONE;
			dvb_ca_en50221_camchange_irq(&budget_ci->ca, 0,
						     DVB_CA_EN50221_CAMCHANGE_REMOVED);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक ciपूर्णांकf_poll_slot_status(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot, पूर्णांक खोलो)
अणु
	काष्ठा budget_ci *budget_ci = (काष्ठा budget_ci *) ca->data;
	अचिन्हित पूर्णांक flags;

	// ensure we करोn't get spurious IRQs during initialisation
	अगर (!budget_ci->budget.ci_present)
		वापस -EINVAL;

	// पढ़ो the CAM status
	flags = ttpci_budget_debiपढ़ो(&budget_ci->budget, DEBICICTL, DEBIADDR_CICONTROL, 1, 1, 0);
	अगर (flags & CICONTROL_CAMDETECT) अणु
		// mark it as present अगर it wasn't beक्रमe
		अगर (budget_ci->slot_status & SLOTSTATUS_NONE) अणु
			budget_ci->slot_status = SLOTSTATUS_PRESENT;
		पूर्ण

		// during a RESET, we check अगर we can पढ़ो from IO memory to see when CAM is पढ़ोy
		अगर (budget_ci->slot_status & SLOTSTATUS_RESET) अणु
			अगर (ciपूर्णांकf_पढ़ो_attribute_mem(ca, slot, 0) == 0x1d) अणु
				budget_ci->slot_status = SLOTSTATUS_READY;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		budget_ci->slot_status = SLOTSTATUS_NONE;
	पूर्ण

	अगर (budget_ci->slot_status != SLOTSTATUS_NONE) अणु
		अगर (budget_ci->slot_status & SLOTSTATUS_READY) अणु
			वापस DVB_CA_EN50221_POLL_CAM_PRESENT | DVB_CA_EN50221_POLL_CAM_READY;
		पूर्ण
		वापस DVB_CA_EN50221_POLL_CAM_PRESENT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ciपूर्णांकf_init(काष्ठा budget_ci *budget_ci)
अणु
	काष्ठा saa7146_dev *saa = budget_ci->budget.dev;
	पूर्णांक flags;
	पूर्णांक result;
	पूर्णांक ci_version;
	पूर्णांक ca_flags;

	स_रखो(&budget_ci->ca, 0, माप(काष्ठा dvb_ca_en50221));

	// enable DEBI pins
	saa7146_ग_लिखो(saa, MC1, MASK_27 | MASK_11);

	// test अगर it is there
	ci_version = ttpci_budget_debiपढ़ो(&budget_ci->budget, DEBICICTL, DEBIADDR_CIVERSION, 1, 1, 0);
	अगर ((ci_version & 0xa0) != 0xa0) अणु
		result = -ENODEV;
		जाओ error;
	पूर्ण

	// determine whether a CAM is present or not
	flags = ttpci_budget_debiपढ़ो(&budget_ci->budget, DEBICICTL, DEBIADDR_CICONTROL, 1, 1, 0);
	budget_ci->slot_status = SLOTSTATUS_NONE;
	अगर (flags & CICONTROL_CAMDETECT)
		budget_ci->slot_status = SLOTSTATUS_PRESENT;

	// version 0xa2 of the CI firmware करोesn't generate पूर्णांकerrupts
	अगर (ci_version == 0xa2) अणु
		ca_flags = 0;
		budget_ci->ci_irq = 0;
	पूर्ण अन्यथा अणु
		ca_flags = DVB_CA_EN50221_FLAG_IRQ_CAMCHANGE |
				DVB_CA_EN50221_FLAG_IRQ_FR |
				DVB_CA_EN50221_FLAG_IRQ_DA;
		budget_ci->ci_irq = 1;
	पूर्ण

	// रेजिस्टर CI पूर्णांकerface
	budget_ci->ca.owner = THIS_MODULE;
	budget_ci->ca.पढ़ो_attribute_mem = ciपूर्णांकf_पढ़ो_attribute_mem;
	budget_ci->ca.ग_लिखो_attribute_mem = ciपूर्णांकf_ग_लिखो_attribute_mem;
	budget_ci->ca.पढ़ो_cam_control = ciपूर्णांकf_पढ़ो_cam_control;
	budget_ci->ca.ग_लिखो_cam_control = ciपूर्णांकf_ग_लिखो_cam_control;
	budget_ci->ca.slot_reset = ciपूर्णांकf_slot_reset;
	budget_ci->ca.slot_shutकरोwn = ciपूर्णांकf_slot_shutकरोwn;
	budget_ci->ca.slot_ts_enable = ciपूर्णांकf_slot_ts_enable;
	budget_ci->ca.poll_slot_status = ciपूर्णांकf_poll_slot_status;
	budget_ci->ca.data = budget_ci;
	अगर ((result = dvb_ca_en50221_init(&budget_ci->budget.dvb_adapter,
					  &budget_ci->ca,
					  ca_flags, 1)) != 0) अणु
		prपूर्णांकk("budget_ci: CI interface detected, but initialisation failed.\n");
		जाओ error;
	पूर्ण

	// Setup CI slot IRQ
	अगर (budget_ci->ci_irq) अणु
		tasklet_setup(&budget_ci->ciपूर्णांकf_irq_tasklet, ciपूर्णांकf_पूर्णांकerrupt);
		अगर (budget_ci->slot_status != SLOTSTATUS_NONE) अणु
			saa7146_setgpio(saa, 0, SAA7146_GPIO_IRQLO);
		पूर्ण अन्यथा अणु
			saa7146_setgpio(saa, 0, SAA7146_GPIO_IRQHI);
		पूर्ण
		SAA7146_IER_ENABLE(saa, MASK_03);
	पूर्ण

	// enable पूर्णांकerface
	ttpci_budget_debiग_लिखो(&budget_ci->budget, DEBICICTL, DEBIADDR_CICONTROL, 1,
			       CICONTROL_RESET, 1, 0);

	// success!
	prपूर्णांकk("budget_ci: CI interface initialised\n");
	budget_ci->budget.ci_present = 1;

	// क्रमge a fake CI IRQ so the CAM state is setup correctly
	अगर (budget_ci->ci_irq) अणु
		flags = DVB_CA_EN50221_CAMCHANGE_REMOVED;
		अगर (budget_ci->slot_status != SLOTSTATUS_NONE)
			flags = DVB_CA_EN50221_CAMCHANGE_INSERTED;
		dvb_ca_en50221_camchange_irq(&budget_ci->ca, 0, flags);
	पूर्ण

	वापस 0;

error:
	saa7146_ग_लिखो(saa, MC1, MASK_27);
	वापस result;
पूर्ण

अटल व्योम ciपूर्णांकf_deinit(काष्ठा budget_ci *budget_ci)
अणु
	काष्ठा saa7146_dev *saa = budget_ci->budget.dev;

	// disable CI पूर्णांकerrupts
	अगर (budget_ci->ci_irq) अणु
		SAA7146_IER_DISABLE(saa, MASK_03);
		saa7146_setgpio(saa, 0, SAA7146_GPIO_INPUT);
		tasklet_समाप्त(&budget_ci->ciपूर्णांकf_irq_tasklet);
	पूर्ण

	// reset पूर्णांकerface
	ttpci_budget_debiग_लिखो(&budget_ci->budget, DEBICICTL, DEBIADDR_CICONTROL, 1, 0, 1, 0);
	msleep(1);
	ttpci_budget_debiग_लिखो(&budget_ci->budget, DEBICICTL, DEBIADDR_CICONTROL, 1,
			       CICONTROL_RESET, 1, 0);

	// disable TS data stream to CI पूर्णांकerface
	saa7146_setgpio(saa, 1, SAA7146_GPIO_INPUT);

	// release the CA device
	dvb_ca_en50221_release(&budget_ci->ca);

	// disable DEBI pins
	saa7146_ग_लिखो(saa, MC1, MASK_27);
पूर्ण

अटल व्योम budget_ci_irq(काष्ठा saa7146_dev *dev, u32 * isr)
अणु
	काष्ठा budget_ci *budget_ci = (काष्ठा budget_ci *) dev->ext_priv;

	dprपूर्णांकk(8, "dev: %p, budget_ci: %p\n", dev, budget_ci);

	अगर (*isr & MASK_06)
		tasklet_schedule(&budget_ci->ir.msp430_irq_tasklet);

	अगर (*isr & MASK_10)
		ttpci_budget_irq10_handler(dev, isr);

	अगर ((*isr & MASK_03) && (budget_ci->budget.ci_present) && (budget_ci->ci_irq))
		tasklet_schedule(&budget_ci->ciपूर्णांकf_irq_tasklet);
पूर्ण

अटल u8 philips_su1278_tt_inittab[] = अणु
	0x01, 0x0f,
	0x02, 0x30,
	0x03, 0x00,
	0x04, 0x5b,
	0x05, 0x85,
	0x06, 0x02,
	0x07, 0x00,
	0x08, 0x02,
	0x09, 0x00,
	0x0C, 0x01,
	0x0D, 0x81,
	0x0E, 0x44,
	0x0f, 0x14,
	0x10, 0x3c,
	0x11, 0x84,
	0x12, 0xda,
	0x13, 0x97,
	0x14, 0x95,
	0x15, 0xc9,
	0x16, 0x19,
	0x17, 0x8c,
	0x18, 0x59,
	0x19, 0xf8,
	0x1a, 0xfe,
	0x1c, 0x7f,
	0x1d, 0x00,
	0x1e, 0x00,
	0x1f, 0x50,
	0x20, 0x00,
	0x21, 0x00,
	0x22, 0x00,
	0x23, 0x00,
	0x28, 0x00,
	0x29, 0x28,
	0x2a, 0x14,
	0x2b, 0x0f,
	0x2c, 0x09,
	0x2d, 0x09,
	0x31, 0x1f,
	0x32, 0x19,
	0x33, 0xfc,
	0x34, 0x93,
	0xff, 0xff
पूर्ण;

अटल पूर्णांक philips_su1278_tt_set_symbol_rate(काष्ठा dvb_frontend *fe, u32 srate, u32 ratio)
अणु
	stv0299_ग_लिखोreg(fe, 0x0e, 0x44);
	अगर (srate >= 10000000) अणु
		stv0299_ग_लिखोreg(fe, 0x13, 0x97);
		stv0299_ग_लिखोreg(fe, 0x14, 0x95);
		stv0299_ग_लिखोreg(fe, 0x15, 0xc9);
		stv0299_ग_लिखोreg(fe, 0x17, 0x8c);
		stv0299_ग_लिखोreg(fe, 0x1a, 0xfe);
		stv0299_ग_लिखोreg(fe, 0x1c, 0x7f);
		stv0299_ग_लिखोreg(fe, 0x2d, 0x09);
	पूर्ण अन्यथा अणु
		stv0299_ग_लिखोreg(fe, 0x13, 0x99);
		stv0299_ग_लिखोreg(fe, 0x14, 0x8d);
		stv0299_ग_लिखोreg(fe, 0x15, 0xce);
		stv0299_ग_लिखोreg(fe, 0x17, 0x43);
		stv0299_ग_लिखोreg(fe, 0x1a, 0x1d);
		stv0299_ग_लिखोreg(fe, 0x1c, 0x12);
		stv0299_ग_लिखोreg(fe, 0x2d, 0x05);
	पूर्ण
	stv0299_ग_लिखोreg(fe, 0x0e, 0x23);
	stv0299_ग_लिखोreg(fe, 0x0f, 0x94);
	stv0299_ग_लिखोreg(fe, 0x10, 0x39);
	stv0299_ग_लिखोreg(fe, 0x15, 0xc9);

	stv0299_ग_लिखोreg(fe, 0x1f, (ratio >> 16) & 0xff);
	stv0299_ग_लिखोreg(fe, 0x20, (ratio >> 8) & 0xff);
	stv0299_ग_लिखोreg(fe, 0x21, (ratio) & 0xf0);

	वापस 0;
पूर्ण

अटल पूर्णांक philips_su1278_tt_tuner_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा budget_ci *budget_ci = (काष्ठा budget_ci *) fe->dvb->priv;
	u32 भाग;
	u8 buf[4];
	काष्ठा i2c_msg msg = अणु.addr = 0x60,.flags = 0,.buf = buf,.len = माप(buf) पूर्ण;

	अगर ((p->frequency < 950000) || (p->frequency > 2150000))
		वापस -EINVAL;

	भाग = (p->frequency + (500 - 1)) / 500;	/* round correctly */
	buf[0] = (भाग >> 8) & 0x7f;
	buf[1] = भाग & 0xff;
	buf[2] = 0x80 | ((भाग & 0x18000) >> 10) | 2;
	buf[3] = 0x20;

	अगर (p->symbol_rate < 4000000)
		buf[3] |= 1;

	अगर (p->frequency < 1250000)
		buf[3] |= 0;
	अन्यथा अगर (p->frequency < 1550000)
		buf[3] |= 0x40;
	अन्यथा अगर (p->frequency < 2050000)
		buf[3] |= 0x80;
	अन्यथा अगर (p->frequency < 2150000)
		buf[3] |= 0xC0;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	अगर (i2c_transfer(&budget_ci->budget.i2c_adap, &msg, 1) != 1)
		वापस -EIO;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा stv0299_config philips_su1278_tt_config = अणु

	.demod_address = 0x68,
	.inittab = philips_su1278_tt_inittab,
	.mclk = 64000000UL,
	.invert = 0,
	.skip_reinit = 1,
	.lock_output = STV0299_LOCKOUTPUT_1,
	.volt13_op0_op1 = STV0299_VOLT13_OP1,
	.min_delay_ms = 50,
	.set_symbol_rate = philips_su1278_tt_set_symbol_rate,
पूर्ण;



अटल पूर्णांक philips_tdm1316l_tuner_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा budget_ci *budget_ci = (काष्ठा budget_ci *) fe->dvb->priv;
	अटल u8 td1316_init[] = अणु 0x0b, 0xf5, 0x85, 0xab पूर्ण;
	अटल u8 disable_mc44BC374c[] = अणु 0x1d, 0x74, 0xa0, 0x68 पूर्ण;
	काष्ठा i2c_msg tuner_msg = अणु.addr = budget_ci->tuner_pll_address,.flags = 0,.buf = td1316_init,.len =
			माप(td1316_init) पूर्ण;

	// setup PLL configuration
	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	अगर (i2c_transfer(&budget_ci->budget.i2c_adap, &tuner_msg, 1) != 1)
		वापस -EIO;
	msleep(1);

	// disable the mc44BC374c (करो not check क्रम errors)
	tuner_msg.addr = 0x65;
	tuner_msg.buf = disable_mc44BC374c;
	tuner_msg.len = माप(disable_mc44BC374c);
	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	अगर (i2c_transfer(&budget_ci->budget.i2c_adap, &tuner_msg, 1) != 1) अणु
		अगर (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 1);
		i2c_transfer(&budget_ci->budget.i2c_adap, &tuner_msg, 1);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक philips_tdm1316l_tuner_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा budget_ci *budget_ci = (काष्ठा budget_ci *) fe->dvb->priv;
	u8 tuner_buf[4];
	काष्ठा i2c_msg tuner_msg = अणु.addr = budget_ci->tuner_pll_address,.flags = 0,.buf = tuner_buf,.len = माप(tuner_buf) पूर्ण;
	पूर्णांक tuner_frequency = 0;
	u8 band, cp, filter;

	// determine अक्षरge pump
	tuner_frequency = p->frequency + 36130000;
	अगर (tuner_frequency < 87000000)
		वापस -EINVAL;
	अन्यथा अगर (tuner_frequency < 130000000)
		cp = 3;
	अन्यथा अगर (tuner_frequency < 160000000)
		cp = 5;
	अन्यथा अगर (tuner_frequency < 200000000)
		cp = 6;
	अन्यथा अगर (tuner_frequency < 290000000)
		cp = 3;
	अन्यथा अगर (tuner_frequency < 420000000)
		cp = 5;
	अन्यथा अगर (tuner_frequency < 480000000)
		cp = 6;
	अन्यथा अगर (tuner_frequency < 620000000)
		cp = 3;
	अन्यथा अगर (tuner_frequency < 830000000)
		cp = 5;
	अन्यथा अगर (tuner_frequency < 895000000)
		cp = 7;
	अन्यथा
		वापस -EINVAL;

	// determine band
	अगर (p->frequency < 49000000)
		वापस -EINVAL;
	अन्यथा अगर (p->frequency < 159000000)
		band = 1;
	अन्यथा अगर (p->frequency < 444000000)
		band = 2;
	अन्यथा अगर (p->frequency < 861000000)
		band = 4;
	अन्यथा
		वापस -EINVAL;

	// setup PLL filter and TDA9889
	चयन (p->bandwidth_hz) अणु
	हाल 6000000:
		tda1004x_ग_लिखोreg(fe, 0x0C, 0x14);
		filter = 0;
		अवरोध;

	हाल 7000000:
		tda1004x_ग_लिखोreg(fe, 0x0C, 0x80);
		filter = 0;
		अवरोध;

	हाल 8000000:
		tda1004x_ग_लिखोreg(fe, 0x0C, 0x14);
		filter = 1;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	// calculate भागisor
	// ((36130000+((1000000/6)/2)) + Finput)/(1000000/6)
	tuner_frequency = (((p->frequency / 1000) * 6) + 217280) / 1000;

	// setup tuner buffer
	tuner_buf[0] = tuner_frequency >> 8;
	tuner_buf[1] = tuner_frequency & 0xff;
	tuner_buf[2] = 0xca;
	tuner_buf[3] = (cp << 5) | (filter << 3) | band;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	अगर (i2c_transfer(&budget_ci->budget.i2c_adap, &tuner_msg, 1) != 1)
		वापस -EIO;

	msleep(1);
	वापस 0;
पूर्ण

अटल पूर्णांक philips_tdm1316l_request_firmware(काष्ठा dvb_frontend *fe,
					     स्थिर काष्ठा firmware **fw, अक्षर *name)
अणु
	काष्ठा budget_ci *budget_ci = (काष्ठा budget_ci *) fe->dvb->priv;

	वापस request_firmware(fw, name, &budget_ci->budget.dev->pci->dev);
पूर्ण

अटल काष्ठा tda1004x_config philips_tdm1316l_config = अणु

	.demod_address = 0x8,
	.invert = 0,
	.invert_oclk = 0,
	.xtal_freq = TDA10046_XTAL_4M,
	.agc_config = TDA10046_AGC_DEFAULT,
	.अगर_freq = TDA10046_FREQ_3617,
	.request_firmware = philips_tdm1316l_request_firmware,
पूर्ण;

अटल काष्ठा tda1004x_config philips_tdm1316l_config_invert = अणु

	.demod_address = 0x8,
	.invert = 1,
	.invert_oclk = 0,
	.xtal_freq = TDA10046_XTAL_4M,
	.agc_config = TDA10046_AGC_DEFAULT,
	.अगर_freq = TDA10046_FREQ_3617,
	.request_firmware = philips_tdm1316l_request_firmware,
पूर्ण;

अटल पूर्णांक dvbc_philips_tdm1316l_tuner_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा budget_ci *budget_ci = (काष्ठा budget_ci *) fe->dvb->priv;
	u8 tuner_buf[5];
	काष्ठा i2c_msg tuner_msg = अणु.addr = budget_ci->tuner_pll_address,
				    .flags = 0,
				    .buf = tuner_buf,
				    .len = माप(tuner_buf) पूर्ण;
	पूर्णांक tuner_frequency = 0;
	u8 band, cp, filter;

	// determine अक्षरge pump
	tuner_frequency = p->frequency + 36125000;
	अगर (tuner_frequency < 87000000)
		वापस -EINVAL;
	अन्यथा अगर (tuner_frequency < 130000000) अणु
		cp = 3;
		band = 1;
	पूर्ण अन्यथा अगर (tuner_frequency < 160000000) अणु
		cp = 5;
		band = 1;
	पूर्ण अन्यथा अगर (tuner_frequency < 200000000) अणु
		cp = 6;
		band = 1;
	पूर्ण अन्यथा अगर (tuner_frequency < 290000000) अणु
		cp = 3;
		band = 2;
	पूर्ण अन्यथा अगर (tuner_frequency < 420000000) अणु
		cp = 5;
		band = 2;
	पूर्ण अन्यथा अगर (tuner_frequency < 480000000) अणु
		cp = 6;
		band = 2;
	पूर्ण अन्यथा अगर (tuner_frequency < 620000000) अणु
		cp = 3;
		band = 4;
	पूर्ण अन्यथा अगर (tuner_frequency < 830000000) अणु
		cp = 5;
		band = 4;
	पूर्ण अन्यथा अगर (tuner_frequency < 895000000) अणु
		cp = 7;
		band = 4;
	पूर्ण अन्यथा
		वापस -EINVAL;

	// assume PLL filter should always be 8MHz क्रम the moment.
	filter = 1;

	// calculate भागisor
	tuner_frequency = (p->frequency + 36125000 + (62500/2)) / 62500;

	// setup tuner buffer
	tuner_buf[0] = tuner_frequency >> 8;
	tuner_buf[1] = tuner_frequency & 0xff;
	tuner_buf[2] = 0xc8;
	tuner_buf[3] = (cp << 5) | (filter << 3) | band;
	tuner_buf[4] = 0x80;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	अगर (i2c_transfer(&budget_ci->budget.i2c_adap, &tuner_msg, 1) != 1)
		वापस -EIO;

	msleep(50);

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	अगर (i2c_transfer(&budget_ci->budget.i2c_adap, &tuner_msg, 1) != 1)
		वापस -EIO;

	msleep(1);

	वापस 0;
पूर्ण

अटल u8 dvbc_philips_tdm1316l_inittab[] = अणु
	0x80, 0x01,
	0x80, 0x00,
	0x81, 0x01,
	0x81, 0x00,
	0x00, 0x09,
	0x01, 0x69,
	0x03, 0x00,
	0x04, 0x00,
	0x07, 0x00,
	0x08, 0x00,
	0x20, 0x00,
	0x21, 0x40,
	0x22, 0x00,
	0x23, 0x00,
	0x24, 0x40,
	0x25, 0x88,
	0x30, 0xff,
	0x31, 0x00,
	0x32, 0xff,
	0x33, 0x00,
	0x34, 0x50,
	0x35, 0x7f,
	0x36, 0x00,
	0x37, 0x20,
	0x38, 0x00,
	0x40, 0x1c,
	0x41, 0xff,
	0x42, 0x29,
	0x43, 0x20,
	0x44, 0xff,
	0x45, 0x00,
	0x46, 0x00,
	0x49, 0x04,
	0x4a, 0x00,
	0x4b, 0x7b,
	0x52, 0x30,
	0x55, 0xae,
	0x56, 0x47,
	0x57, 0xe1,
	0x58, 0x3a,
	0x5a, 0x1e,
	0x5b, 0x34,
	0x60, 0x00,
	0x63, 0x00,
	0x64, 0x00,
	0x65, 0x00,
	0x66, 0x00,
	0x67, 0x00,
	0x68, 0x00,
	0x69, 0x00,
	0x6a, 0x02,
	0x6b, 0x00,
	0x70, 0xff,
	0x71, 0x00,
	0x72, 0x00,
	0x73, 0x00,
	0x74, 0x0c,
	0x80, 0x00,
	0x81, 0x00,
	0x82, 0x00,
	0x83, 0x00,
	0x84, 0x04,
	0x85, 0x80,
	0x86, 0x24,
	0x87, 0x78,
	0x88, 0x10,
	0x89, 0x00,
	0x90, 0x01,
	0x91, 0x01,
	0xa0, 0x04,
	0xa1, 0x00,
	0xa2, 0x00,
	0xb0, 0x91,
	0xb1, 0x0b,
	0xc0, 0x53,
	0xc1, 0x70,
	0xc2, 0x12,
	0xd0, 0x00,
	0xd1, 0x00,
	0xd2, 0x00,
	0xd3, 0x00,
	0xd4, 0x00,
	0xd5, 0x00,
	0xde, 0x00,
	0xdf, 0x00,
	0x61, 0x38,
	0x62, 0x0a,
	0x53, 0x13,
	0x59, 0x08,
	0xff, 0xff,
पूर्ण;

अटल काष्ठा stv0297_config dvbc_philips_tdm1316l_config = अणु
	.demod_address = 0x1c,
	.inittab = dvbc_philips_tdm1316l_inittab,
	.invert = 0,
	.stop_during_पढ़ो = 1,
पूर्ण;

अटल काष्ठा tda10023_config tda10023_config = अणु
	.demod_address = 0xc,
	.invert = 0,
	.xtal = 16000000,
	.pll_m = 11,
	.pll_p = 3,
	.pll_n = 1,
	.deltaf = 0xa511,
पूर्ण;

अटल काष्ठा tda827x_config tda827x_config = अणु
	.config = 0,
पूर्ण;

/* TT S2-3200 DVB-S (STB0899) Inittab */
अटल स्थिर काष्ठा stb0899_s1_reg tt3200_stb0899_s1_init_1[] = अणु

	अणु STB0899_DEV_ID		, 0x81 पूर्ण,
	अणु STB0899_DISCNTRL1		, 0x32 पूर्ण,
	अणु STB0899_DISCNTRL2		, 0x80 पूर्ण,
	अणु STB0899_DISRX_ST0		, 0x04 पूर्ण,
	अणु STB0899_DISRX_ST1		, 0x00 पूर्ण,
	अणु STB0899_DISPARITY		, 0x00 पूर्ण,
	अणु STB0899_DISSTATUS		, 0x20 पूर्ण,
	अणु STB0899_DISF22		, 0x8c पूर्ण,
	अणु STB0899_DISF22RX		, 0x9a पूर्ण,
	अणु STB0899_SYSREG		, 0x0b पूर्ण,
	अणु STB0899_ACRPRESC		, 0x11 पूर्ण,
	अणु STB0899_ACRDIV1		, 0x0a पूर्ण,
	अणु STB0899_ACRDIV2		, 0x05 पूर्ण,
	अणु STB0899_DACR1			, 0x00 पूर्ण,
	अणु STB0899_DACR2			, 0x00 पूर्ण,
	अणु STB0899_OUTCFG		, 0x00 पूर्ण,
	अणु STB0899_MODECFG		, 0x00 पूर्ण,
	अणु STB0899_IRQSTATUS_3		, 0x30 पूर्ण,
	अणु STB0899_IRQSTATUS_2		, 0x00 पूर्ण,
	अणु STB0899_IRQSTATUS_1		, 0x00 पूर्ण,
	अणु STB0899_IRQSTATUS_0		, 0x00 पूर्ण,
	अणु STB0899_IRQMSK_3		, 0xf3 पूर्ण,
	अणु STB0899_IRQMSK_2		, 0xfc पूर्ण,
	अणु STB0899_IRQMSK_1		, 0xff पूर्ण,
	अणु STB0899_IRQMSK_0		, 0xff पूर्ण,
	अणु STB0899_IRQCFG		, 0x00 पूर्ण,
	अणु STB0899_I2CCFG		, 0x88 पूर्ण,
	अणु STB0899_I2CRPT		, 0x48 पूर्ण, /* 12k Pullup, Repeater=16, Stop=disabled */
	अणु STB0899_IOPVALUE5		, 0x00 पूर्ण,
	अणु STB0899_IOPVALUE4		, 0x20 पूर्ण,
	अणु STB0899_IOPVALUE3		, 0xc9 पूर्ण,
	अणु STB0899_IOPVALUE2		, 0x90 पूर्ण,
	अणु STB0899_IOPVALUE1		, 0x40 पूर्ण,
	अणु STB0899_IOPVALUE0		, 0x00 पूर्ण,
	अणु STB0899_GPIO00CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO01CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO02CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO03CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO04CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO05CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO06CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO07CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO08CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO09CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO10CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO11CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO12CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO13CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO14CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO15CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO16CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO17CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO18CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO19CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO20CFG		, 0x82 पूर्ण,
	अणु STB0899_SDATCFG		, 0xb8 पूर्ण,
	अणु STB0899_SCLTCFG		, 0xba पूर्ण,
	अणु STB0899_AGCRFCFG		, 0x1c पूर्ण, /* 0x11 */
	अणु STB0899_GPIO22		, 0x82 पूर्ण, /* AGCBB2CFG */
	अणु STB0899_GPIO21		, 0x91 पूर्ण, /* AGCBB1CFG */
	अणु STB0899_सूचीCLKCFG		, 0x82 पूर्ण,
	अणु STB0899_CLKOUT27CFG		, 0x7e पूर्ण,
	अणु STB0899_STDBYCFG		, 0x82 पूर्ण,
	अणु STB0899_CS0CFG		, 0x82 पूर्ण,
	अणु STB0899_CS1CFG		, 0x82 पूर्ण,
	अणु STB0899_DISEQCOCFG		, 0x20 पूर्ण,
	अणु STB0899_GPIO32CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO33CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO34CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO35CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO36CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO37CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO38CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO39CFG		, 0x82 पूर्ण,
	अणु STB0899_NCOARSE		, 0x15 पूर्ण, /* 0x15 = 27 Mhz Clock, F/3 = 198MHz, F/6 = 99MHz */
	अणु STB0899_SYNTCTRL		, 0x02 पूर्ण, /* 0x00 = CLK from CLKI, 0x02 = CLK from XTALI */
	अणु STB0899_FILTCTRL		, 0x00 पूर्ण,
	अणु STB0899_SYSCTRL		, 0x00 पूर्ण,
	अणु STB0899_STOPCLK1		, 0x20 पूर्ण,
	अणु STB0899_STOPCLK2		, 0x00 पूर्ण,
	अणु STB0899_INTBUFSTATUS		, 0x00 पूर्ण,
	अणु STB0899_INTBUFCTRL		, 0x0a पूर्ण,
	अणु 0xffff			, 0xff पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा stb0899_s1_reg tt3200_stb0899_s1_init_3[] = अणु
	अणु STB0899_DEMOD			, 0x00 पूर्ण,
	अणु STB0899_RCOMPC		, 0xc9 पूर्ण,
	अणु STB0899_AGC1CN		, 0x41 पूर्ण,
	अणु STB0899_AGC1REF		, 0x10 पूर्ण,
	अणु STB0899_RTC			, 0x7a पूर्ण,
	अणु STB0899_TMGCFG		, 0x4e पूर्ण,
	अणु STB0899_AGC2REF		, 0x34 पूर्ण,
	अणु STB0899_TLSR			, 0x84 पूर्ण,
	अणु STB0899_CFD			, 0xc7 पूर्ण,
	अणु STB0899_ACLC			, 0x87 पूर्ण,
	अणु STB0899_BCLC			, 0x94 पूर्ण,
	अणु STB0899_EQON			, 0x41 पूर्ण,
	अणु STB0899_LDT			, 0xdd पूर्ण,
	अणु STB0899_LDT2			, 0xc9 पूर्ण,
	अणु STB0899_EQUALREF		, 0xb4 पूर्ण,
	अणु STB0899_TMGRAMP		, 0x10 पूर्ण,
	अणु STB0899_TMGTHD		, 0x30 पूर्ण,
	अणु STB0899_IDCCOMP		, 0xfb पूर्ण,
	अणु STB0899_QDCCOMP		, 0x03 पूर्ण,
	अणु STB0899_POWERI		, 0x3b पूर्ण,
	अणु STB0899_POWERQ		, 0x3d पूर्ण,
	अणु STB0899_RCOMP			, 0x81 पूर्ण,
	अणु STB0899_AGCIQIN		, 0x80 पूर्ण,
	अणु STB0899_AGC2I1		, 0x04 पूर्ण,
	अणु STB0899_AGC2I2		, 0xf5 पूर्ण,
	अणु STB0899_TLIR			, 0x25 पूर्ण,
	अणु STB0899_RTF			, 0x80 पूर्ण,
	अणु STB0899_DSTATUS		, 0x00 पूर्ण,
	अणु STB0899_LDI			, 0xca पूर्ण,
	अणु STB0899_CFRM			, 0xf1 पूर्ण,
	अणु STB0899_CFRL			, 0xf3 पूर्ण,
	अणु STB0899_NIRM			, 0x2a पूर्ण,
	अणु STB0899_NIRL			, 0x05 पूर्ण,
	अणु STB0899_ISYMB			, 0x17 पूर्ण,
	अणु STB0899_QSYMB			, 0xfa पूर्ण,
	अणु STB0899_SFRH			, 0x2f पूर्ण,
	अणु STB0899_SFRM			, 0x68 पूर्ण,
	अणु STB0899_SFRL			, 0x40 पूर्ण,
	अणु STB0899_SFRUPH		, 0x2f पूर्ण,
	अणु STB0899_SFRUPM		, 0x68 पूर्ण,
	अणु STB0899_SFRUPL		, 0x40 पूर्ण,
	अणु STB0899_EQUAI1		, 0xfd पूर्ण,
	अणु STB0899_EQUAQ1		, 0x04 पूर्ण,
	अणु STB0899_EQUAI2		, 0x0f पूर्ण,
	अणु STB0899_EQUAQ2		, 0xff पूर्ण,
	अणु STB0899_EQUAI3		, 0xdf पूर्ण,
	अणु STB0899_EQUAQ3		, 0xfa पूर्ण,
	अणु STB0899_EQUAI4		, 0x37 पूर्ण,
	अणु STB0899_EQUAQ4		, 0x0d पूर्ण,
	अणु STB0899_EQUAI5		, 0xbd पूर्ण,
	अणु STB0899_EQUAQ5		, 0xf7 पूर्ण,
	अणु STB0899_DSTATUS2		, 0x00 पूर्ण,
	अणु STB0899_VSTATUS		, 0x00 पूर्ण,
	अणु STB0899_VERROR		, 0xff पूर्ण,
	अणु STB0899_IQSWAP		, 0x2a पूर्ण,
	अणु STB0899_ECNT1M		, 0x00 पूर्ण,
	अणु STB0899_ECNT1L		, 0x00 पूर्ण,
	अणु STB0899_ECNT2M		, 0x00 पूर्ण,
	अणु STB0899_ECNT2L		, 0x00 पूर्ण,
	अणु STB0899_ECNT3M		, 0x00 पूर्ण,
	अणु STB0899_ECNT3L		, 0x00 पूर्ण,
	अणु STB0899_FECAUTO1		, 0x06 पूर्ण,
	अणु STB0899_FECM			, 0x01 पूर्ण,
	अणु STB0899_VTH12			, 0xf0 पूर्ण,
	अणु STB0899_VTH23			, 0xa0 पूर्ण,
	अणु STB0899_VTH34			, 0x78 पूर्ण,
	अणु STB0899_VTH56			, 0x4e पूर्ण,
	अणु STB0899_VTH67			, 0x48 पूर्ण,
	अणु STB0899_VTH78			, 0x38 पूर्ण,
	अणु STB0899_PRVIT			, 0xff पूर्ण,
	अणु STB0899_VITSYNC		, 0x19 पूर्ण,
	अणु STB0899_RSULC			, 0xb1 पूर्ण, /* DVB = 0xb1, DSS = 0xa1 */
	अणु STB0899_TSULC			, 0x42 पूर्ण,
	अणु STB0899_RSLLC			, 0x40 पूर्ण,
	अणु STB0899_TSLPL			, 0x12 पूर्ण,
	अणु STB0899_TSCFGH		, 0x0c पूर्ण,
	अणु STB0899_TSCFGM		, 0x00 पूर्ण,
	अणु STB0899_TSCFGL		, 0x0c पूर्ण,
	अणु STB0899_TSOUT			, 0x4d पूर्ण, /* 0x0d क्रम CAM */
	अणु STB0899_RSSYNCDEL		, 0x00 पूर्ण,
	अणु STB0899_TSINHDELH		, 0x02 पूर्ण,
	अणु STB0899_TSINHDELM		, 0x00 पूर्ण,
	अणु STB0899_TSINHDELL		, 0x00 पूर्ण,
	अणु STB0899_TSLLSTKM		, 0x00 पूर्ण,
	अणु STB0899_TSLLSTKL		, 0x00 पूर्ण,
	अणु STB0899_TSULSTKM		, 0x00 पूर्ण,
	अणु STB0899_TSULSTKL		, 0xab पूर्ण,
	अणु STB0899_PCKLENUL		, 0x00 पूर्ण,
	अणु STB0899_PCKLENLL		, 0xcc पूर्ण,
	अणु STB0899_RSPCKLEN		, 0xcc पूर्ण,
	अणु STB0899_TSSTATUS		, 0x80 पूर्ण,
	अणु STB0899_ERRCTRL1		, 0xb6 पूर्ण,
	अणु STB0899_ERRCTRL2		, 0x96 पूर्ण,
	अणु STB0899_ERRCTRL3		, 0x89 पूर्ण,
	अणु STB0899_DMONMSK1		, 0x27 पूर्ण,
	अणु STB0899_DMONMSK0		, 0x03 पूर्ण,
	अणु STB0899_DEMAPVIT		, 0x5c पूर्ण,
	अणु STB0899_PLPARM		, 0x1f पूर्ण,
	अणु STB0899_PDELCTRL		, 0x48 पूर्ण,
	अणु STB0899_PDELCTRL2		, 0x00 पूर्ण,
	अणु STB0899_BBHCTRL1		, 0x00 पूर्ण,
	अणु STB0899_BBHCTRL2		, 0x00 पूर्ण,
	अणु STB0899_HYSTTHRESH		, 0x77 पूर्ण,
	अणु STB0899_MATCSTM		, 0x00 पूर्ण,
	अणु STB0899_MATCSTL		, 0x00 पूर्ण,
	अणु STB0899_UPLCSTM		, 0x00 पूर्ण,
	अणु STB0899_UPLCSTL		, 0x00 पूर्ण,
	अणु STB0899_DFLCSTM		, 0x00 पूर्ण,
	अणु STB0899_DFLCSTL		, 0x00 पूर्ण,
	अणु STB0899_SYNCCST		, 0x00 पूर्ण,
	अणु STB0899_SYNCDCSTM		, 0x00 पूर्ण,
	अणु STB0899_SYNCDCSTL		, 0x00 पूर्ण,
	अणु STB0899_ISI_ENTRY		, 0x00 पूर्ण,
	अणु STB0899_ISI_BIT_EN		, 0x00 पूर्ण,
	अणु STB0899_MATSTRM		, 0x00 पूर्ण,
	अणु STB0899_MATSTRL		, 0x00 पूर्ण,
	अणु STB0899_UPLSTRM		, 0x00 पूर्ण,
	अणु STB0899_UPLSTRL		, 0x00 पूर्ण,
	अणु STB0899_DFLSTRM		, 0x00 पूर्ण,
	अणु STB0899_DFLSTRL		, 0x00 पूर्ण,
	अणु STB0899_SYNCSTR		, 0x00 पूर्ण,
	अणु STB0899_SYNCDSTRM		, 0x00 पूर्ण,
	अणु STB0899_SYNCDSTRL		, 0x00 पूर्ण,
	अणु STB0899_CFGPDELSTATUS1	, 0x10 पूर्ण,
	अणु STB0899_CFGPDELSTATUS2	, 0x00 पूर्ण,
	अणु STB0899_BBFERRORM		, 0x00 पूर्ण,
	अणु STB0899_BBFERRORL		, 0x00 पूर्ण,
	अणु STB0899_UPKTERRORM		, 0x00 पूर्ण,
	अणु STB0899_UPKTERRORL		, 0x00 पूर्ण,
	अणु 0xffff			, 0xff पूर्ण,
पूर्ण;

अटल काष्ठा stb0899_config tt3200_config = अणु
	.init_dev		= tt3200_stb0899_s1_init_1,
	.init_s2_demod		= stb0899_s2_init_2,
	.init_s1_demod		= tt3200_stb0899_s1_init_3,
	.init_s2_fec		= stb0899_s2_init_4,
	.init_tst		= stb0899_s1_init_5,

	.postproc		= शून्य,

	.demod_address		= 0x68,

	.xtal_freq		= 27000000,
	.inversion		= IQ_SWAP_ON,

	.lo_clk			= 76500000,
	.hi_clk			= 99000000,

	.esno_ave		= STB0899_DVBS2_ESNO_AVE,
	.esno_quant		= STB0899_DVBS2_ESNO_QUANT,
	.avframes_coarse	= STB0899_DVBS2_AVFRAMES_COARSE,
	.avframes_fine		= STB0899_DVBS2_AVFRAMES_FINE,
	.miss_threshold		= STB0899_DVBS2_MISS_THRESHOLD,
	.uwp_threshold_acq	= STB0899_DVBS2_UWP_THRESHOLD_ACQ,
	.uwp_threshold_track	= STB0899_DVBS2_UWP_THRESHOLD_TRACK,
	.uwp_threshold_sof	= STB0899_DVBS2_UWP_THRESHOLD_SOF,
	.sof_search_समयout	= STB0899_DVBS2_SOF_SEARCH_TIMEOUT,

	.btr_nco_bits		= STB0899_DVBS2_BTR_NCO_BITS,
	.btr_gain_shअगरt_offset	= STB0899_DVBS2_BTR_GAIN_SHIFT_OFFSET,
	.crl_nco_bits		= STB0899_DVBS2_CRL_NCO_BITS,
	.ldpc_max_iter		= STB0899_DVBS2_LDPC_MAX_ITER,

	.tuner_get_frequency	= stb6100_get_frequency,
	.tuner_set_frequency	= stb6100_set_frequency,
	.tuner_set_bandwidth	= stb6100_set_bandwidth,
	.tuner_get_bandwidth	= stb6100_get_bandwidth,
	.tuner_set_rfsiggain	= शून्य
पूर्ण;

अटल काष्ठा stb6100_config tt3200_stb6100_config = अणु
	.tuner_address	= 0x60,
	.refघड़ी	= 27000000,
पूर्ण;

अटल व्योम frontend_init(काष्ठा budget_ci *budget_ci)
अणु
	चयन (budget_ci->budget.dev->pci->subप्रणाली_device) अणु
	हाल 0x100c:		// Hauppauge/TT Nova-CI budget (stv0299/ALPS BSRU6(tsa5059))
		budget_ci->budget.dvb_frontend =
			dvb_attach(stv0299_attach, &alps_bsru6_config, &budget_ci->budget.i2c_adap);
		अगर (budget_ci->budget.dvb_frontend) अणु
			budget_ci->budget.dvb_frontend->ops.tuner_ops.set_params = alps_bsru6_tuner_set_params;
			budget_ci->budget.dvb_frontend->tuner_priv = &budget_ci->budget.i2c_adap;
			अवरोध;
		पूर्ण
		अवरोध;

	हाल 0x100f:		// Hauppauge/TT Nova-CI budget (stv0299b/Philips su1278(tsa5059))
		budget_ci->budget.dvb_frontend =
			dvb_attach(stv0299_attach, &philips_su1278_tt_config, &budget_ci->budget.i2c_adap);
		अगर (budget_ci->budget.dvb_frontend) अणु
			budget_ci->budget.dvb_frontend->ops.tuner_ops.set_params = philips_su1278_tt_tuner_set_params;
			अवरोध;
		पूर्ण
		अवरोध;

	हाल 0x1010:		// TT DVB-C CI budget (stv0297/Philips tdm1316l(tda6651tt))
		budget_ci->tuner_pll_address = 0x61;
		budget_ci->budget.dvb_frontend =
			dvb_attach(stv0297_attach, &dvbc_philips_tdm1316l_config, &budget_ci->budget.i2c_adap);
		अगर (budget_ci->budget.dvb_frontend) अणु
			budget_ci->budget.dvb_frontend->ops.tuner_ops.set_params = dvbc_philips_tdm1316l_tuner_set_params;
			अवरोध;
		पूर्ण
		अवरोध;

	हाल 0x1011:		// Hauppauge/TT Nova-T budget (tda10045/Philips tdm1316l(tda6651tt) + TDA9889)
		budget_ci->tuner_pll_address = 0x63;
		budget_ci->budget.dvb_frontend =
			dvb_attach(tda10045_attach, &philips_tdm1316l_config, &budget_ci->budget.i2c_adap);
		अगर (budget_ci->budget.dvb_frontend) अणु
			budget_ci->budget.dvb_frontend->ops.tuner_ops.init = philips_tdm1316l_tuner_init;
			budget_ci->budget.dvb_frontend->ops.tuner_ops.set_params = philips_tdm1316l_tuner_set_params;
			अवरोध;
		पूर्ण
		अवरोध;

	हाल 0x1012:		// TT DVB-T CI budget (tda10046/Philips tdm1316l(tda6651tt))
		budget_ci->tuner_pll_address = 0x60;
		budget_ci->budget.dvb_frontend =
			dvb_attach(tda10046_attach, &philips_tdm1316l_config_invert, &budget_ci->budget.i2c_adap);
		अगर (budget_ci->budget.dvb_frontend) अणु
			budget_ci->budget.dvb_frontend->ops.tuner_ops.init = philips_tdm1316l_tuner_init;
			budget_ci->budget.dvb_frontend->ops.tuner_ops.set_params = philips_tdm1316l_tuner_set_params;
			अवरोध;
		पूर्ण
		अवरोध;

	हाल 0x1017:		// TT S-1500 PCI
		budget_ci->budget.dvb_frontend = dvb_attach(stv0299_attach, &alps_bsbe1_config, &budget_ci->budget.i2c_adap);
		अगर (budget_ci->budget.dvb_frontend) अणु
			budget_ci->budget.dvb_frontend->ops.tuner_ops.set_params = alps_bsbe1_tuner_set_params;
			budget_ci->budget.dvb_frontend->tuner_priv = &budget_ci->budget.i2c_adap;

			budget_ci->budget.dvb_frontend->ops.dishnetwork_send_legacy_command = शून्य;
			अगर (dvb_attach(lnbp21_attach, budget_ci->budget.dvb_frontend, &budget_ci->budget.i2c_adap, LNBP21_LLC, 0) == शून्य) अणु
				prपूर्णांकk("%s: No LNBP21 found!\n", __func__);
				dvb_frontend_detach(budget_ci->budget.dvb_frontend);
				budget_ci->budget.dvb_frontend = शून्य;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल 0x101a: /* TT Budget-C-1501 (philips tda10023/philips tda8274A) */
		budget_ci->budget.dvb_frontend = dvb_attach(tda10023_attach, &tda10023_config, &budget_ci->budget.i2c_adap, 0x48);
		अगर (budget_ci->budget.dvb_frontend) अणु
			अगर (dvb_attach(tda827x_attach, budget_ci->budget.dvb_frontend, 0x61, &budget_ci->budget.i2c_adap, &tda827x_config) == शून्य) अणु
				prपूर्णांकk(KERN_ERR "%s: No tda827x found!\n", __func__);
				dvb_frontend_detach(budget_ci->budget.dvb_frontend);
				budget_ci->budget.dvb_frontend = शून्य;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल 0x101b: /* TT S-1500B (BSBE1-D01A - STV0288/STB6000/LNBP21) */
		budget_ci->budget.dvb_frontend = dvb_attach(stv0288_attach, &stv0288_bsbe1_d01a_config, &budget_ci->budget.i2c_adap);
		अगर (budget_ci->budget.dvb_frontend) अणु
			अगर (dvb_attach(stb6000_attach, budget_ci->budget.dvb_frontend, 0x63, &budget_ci->budget.i2c_adap)) अणु
				अगर (!dvb_attach(lnbp21_attach, budget_ci->budget.dvb_frontend, &budget_ci->budget.i2c_adap, 0, 0)) अणु
					prपूर्णांकk(KERN_ERR "%s: No LNBP21 found!\n", __func__);
					dvb_frontend_detach(budget_ci->budget.dvb_frontend);
					budget_ci->budget.dvb_frontend = शून्य;
				पूर्ण
			पूर्ण अन्यथा अणु
				prपूर्णांकk(KERN_ERR "%s: No STB6000 found!\n", __func__);
				dvb_frontend_detach(budget_ci->budget.dvb_frontend);
				budget_ci->budget.dvb_frontend = शून्य;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल 0x1019:		// TT S2-3200 PCI
		/*
		 * NOTE! on some STB0899 versions, the पूर्णांकernal PLL takes a दीर्घer समय
		 * to settle, aka LOCK. On the older revisions of the chip, we करोn't see
		 * this, as a result on the newer chips the entire घड़ी tree, will not
		 * be stable after a freshly POWER 'ed up situation.
		 * In this हाल, we should RESET the STB0899 (Active LOW) and रुको क्रम
		 * PLL stabilization.
		 *
		 * On the TT S2 3200 and clones, the STB0899 demodulator's RESETB is
		 * connected to the SAA7146 GPIO, GPIO2, Pin 142
		 */
		/* Reset Demodulator */
		saa7146_setgpio(budget_ci->budget.dev, 2, SAA7146_GPIO_OUTLO);
		/* Wait क्रम everything to die */
		msleep(50);
		/* Pull it up out of Reset state */
		saa7146_setgpio(budget_ci->budget.dev, 2, SAA7146_GPIO_OUTHI);
		/* Wait क्रम PLL to stabilize */
		msleep(250);
		/*
		 * PLL state should be stable now. Ideally, we should check
		 * क्रम PLL LOCK status. But well, never mind!
		 */
		budget_ci->budget.dvb_frontend = dvb_attach(stb0899_attach, &tt3200_config, &budget_ci->budget.i2c_adap);
		अगर (budget_ci->budget.dvb_frontend) अणु
			अगर (dvb_attach(stb6100_attach, budget_ci->budget.dvb_frontend, &tt3200_stb6100_config, &budget_ci->budget.i2c_adap)) अणु
				अगर (!dvb_attach(lnbp21_attach, budget_ci->budget.dvb_frontend, &budget_ci->budget.i2c_adap, 0, 0)) अणु
					prपूर्णांकk("%s: No LNBP21 found!\n", __func__);
					dvb_frontend_detach(budget_ci->budget.dvb_frontend);
					budget_ci->budget.dvb_frontend = शून्य;
				पूर्ण
			पूर्ण अन्यथा अणु
					dvb_frontend_detach(budget_ci->budget.dvb_frontend);
					budget_ci->budget.dvb_frontend = शून्य;
			पूर्ण
		पूर्ण
		अवरोध;

	पूर्ण

	अगर (budget_ci->budget.dvb_frontend == शून्य) अणु
		prपूर्णांकk("budget-ci: A frontend driver was not found for device [%04x:%04x] subsystem [%04x:%04x]\n",
		       budget_ci->budget.dev->pci->venकरोr,
		       budget_ci->budget.dev->pci->device,
		       budget_ci->budget.dev->pci->subप्रणाली_venकरोr,
		       budget_ci->budget.dev->pci->subप्रणाली_device);
	पूर्ण अन्यथा अणु
		अगर (dvb_रेजिस्टर_frontend
		    (&budget_ci->budget.dvb_adapter, budget_ci->budget.dvb_frontend)) अणु
			prपूर्णांकk("budget-ci: Frontend registration failed!\n");
			dvb_frontend_detach(budget_ci->budget.dvb_frontend);
			budget_ci->budget.dvb_frontend = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक budget_ci_attach(काष्ठा saa7146_dev *dev, काष्ठा saa7146_pci_extension_data *info)
अणु
	काष्ठा budget_ci *budget_ci;
	पूर्णांक err;

	budget_ci = kzalloc(माप(काष्ठा budget_ci), GFP_KERNEL);
	अगर (!budget_ci) अणु
		err = -ENOMEM;
		जाओ out1;
	पूर्ण

	dprपूर्णांकk(2, "budget_ci: %p\n", budget_ci);

	dev->ext_priv = budget_ci;

	err = ttpci_budget_init(&budget_ci->budget, dev, info, THIS_MODULE,
				adapter_nr);
	अगर (err)
		जाओ out2;

	err = msp430_ir_init(budget_ci);
	अगर (err)
		जाओ out3;

	ciपूर्णांकf_init(budget_ci);

	budget_ci->budget.dvb_adapter.priv = budget_ci;
	frontend_init(budget_ci);

	ttpci_budget_init_hooks(&budget_ci->budget);

	वापस 0;

out3:
	ttpci_budget_deinit(&budget_ci->budget);
out2:
	kमुक्त(budget_ci);
out1:
	वापस err;
पूर्ण

अटल पूर्णांक budget_ci_detach(काष्ठा saa7146_dev *dev)
अणु
	काष्ठा budget_ci *budget_ci = (काष्ठा budget_ci *) dev->ext_priv;
	काष्ठा saa7146_dev *saa = budget_ci->budget.dev;
	पूर्णांक err;

	अगर (budget_ci->budget.ci_present)
		ciपूर्णांकf_deinit(budget_ci);
	msp430_ir_deinit(budget_ci);
	अगर (budget_ci->budget.dvb_frontend) अणु
		dvb_unरेजिस्टर_frontend(budget_ci->budget.dvb_frontend);
		dvb_frontend_detach(budget_ci->budget.dvb_frontend);
	पूर्ण
	err = ttpci_budget_deinit(&budget_ci->budget);

	// disable frontend and CI पूर्णांकerface
	saa7146_setgpio(saa, 2, SAA7146_GPIO_INPUT);

	kमुक्त(budget_ci);

	वापस err;
पूर्ण

अटल काष्ठा saa7146_extension budget_extension;

MAKE_BUDGET_INFO(ttbs2, "TT-Budget/S-1500 PCI", BUDGET_TT);
MAKE_BUDGET_INFO(ttbci, "TT-Budget/WinTV-NOVA-CI PCI", BUDGET_TT_HW_DISEQC);
MAKE_BUDGET_INFO(ttbt2, "TT-Budget/WinTV-NOVA-T	 PCI", BUDGET_TT);
MAKE_BUDGET_INFO(ttbtci, "TT-Budget-T-CI PCI", BUDGET_TT);
MAKE_BUDGET_INFO(ttbcci, "TT-Budget-C-CI PCI", BUDGET_TT);
MAKE_BUDGET_INFO(ttc1501, "TT-Budget C-1501 PCI", BUDGET_TT);
MAKE_BUDGET_INFO(tt3200, "TT-Budget S2-3200 PCI", BUDGET_TT);
MAKE_BUDGET_INFO(ttbs1500b, "TT-Budget S-1500B PCI", BUDGET_TT);

अटल स्थिर काष्ठा pci_device_id pci_tbl[] = अणु
	MAKE_EXTENSION_PCI(ttbci, 0x13c2, 0x100c),
	MAKE_EXTENSION_PCI(ttbci, 0x13c2, 0x100f),
	MAKE_EXTENSION_PCI(ttbcci, 0x13c2, 0x1010),
	MAKE_EXTENSION_PCI(ttbt2, 0x13c2, 0x1011),
	MAKE_EXTENSION_PCI(ttbtci, 0x13c2, 0x1012),
	MAKE_EXTENSION_PCI(ttbs2, 0x13c2, 0x1017),
	MAKE_EXTENSION_PCI(ttc1501, 0x13c2, 0x101a),
	MAKE_EXTENSION_PCI(tt3200, 0x13c2, 0x1019),
	MAKE_EXTENSION_PCI(ttbs1500b, 0x13c2, 0x101b),
	अणु
	 .venकरोr = 0,
	 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, pci_tbl);

अटल काष्ठा saa7146_extension budget_extension = अणु
	.name = "budget_ci dvb",
	.flags = SAA7146_USE_I2C_IRQ,

	.module = THIS_MODULE,
	.pci_tbl = &pci_tbl[0],
	.attach = budget_ci_attach,
	.detach = budget_ci_detach,

	.irq_mask = MASK_03 | MASK_06 | MASK_10,
	.irq_func = budget_ci_irq,
पूर्ण;

अटल पूर्णांक __init budget_ci_init(व्योम)
अणु
	वापस saa7146_रेजिस्टर_extension(&budget_extension);
पूर्ण

अटल व्योम __निकास budget_ci_निकास(व्योम)
अणु
	saa7146_unरेजिस्टर_extension(&budget_extension);
पूर्ण

module_init(budget_ci_init);
module_निकास(budget_ci_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Michael Hunold, Jack Thomasson, Andrew de Quincey, others");
MODULE_DESCRIPTION("driver for the SAA7146 based so-called budget PCI DVB cards w/ CI-module produced by Siemens, Technotrend, Hauppauge");
