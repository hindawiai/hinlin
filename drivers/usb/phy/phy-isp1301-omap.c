<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * isp1301_omap - ISP 1301 USB transceiver, talking to OMAP OTG controller
 *
 * Copyright (C) 2004 Texas Instruments
 * Copyright (C) 2004 David Brownell
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/otg.h>
#समावेश <linux/i2c.h>
#समावेश <linux/workqueue.h>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mach-types.h>

#समावेश <mach/mux.h>

#समावेश <mach/usb.h>

#अघोषित VERBOSE


#घोषणा	DRIVER_VERSION	"24 August 2004"
#घोषणा	DRIVER_NAME	(isp1301_driver.driver.name)

MODULE_DESCRIPTION("ISP1301 USB OTG Transceiver Driver");
MODULE_LICENSE("GPL");

काष्ठा isp1301 अणु
	काष्ठा usb_phy		phy;
	काष्ठा i2c_client	*client;
	व्योम			(*i2c_release)(काष्ठा device *dev);

	पूर्णांक			irq_type;

	u32			last_otg_ctrl;
	अचिन्हित		working:1;

	काष्ठा समयr_list	समयr;

	/* use keventd context to change the state क्रम us */
	काष्ठा work_काष्ठा	work;

	अचिन्हित दीर्घ		toकरो;
#		define WORK_UPDATE_ISP	0	/* update ISP from OTG */
#		define WORK_UPDATE_OTG	1	/* update OTG from ISP */
#		define WORK_HOST_RESUME	4	/* resume host */
#		define WORK_TIMER	6	/* समयr fired */
#		define WORK_STOP	7	/* करोn't resubmit */
पूर्ण;


/* bits in OTG_CTRL */

#घोषणा	OTG_XCEIV_OUTPUTS \
	(OTG_ASESSVLD|OTG_BSESSEND|OTG_BSESSVLD|OTG_VBUSVLD|OTG_ID)
#घोषणा	OTG_XCEIV_INPUTS \
	(OTG_PULLDOWN|OTG_PULLUP|OTG_DRV_VBUS|OTG_PD_VBUS|OTG_PU_VBUS|OTG_PU_ID)
#घोषणा	OTG_CTRL_BITS \
	(OTG_A_BUSREQ|OTG_A_SETB_HNPEN|OTG_B_BUSREQ|OTG_B_HNPEN|OTG_BUSDROP)
	/* and OTG_PULLUP is someबार written */

#घोषणा	OTG_CTRL_MASK	(OTG_DRIVER_SEL| \
	OTG_XCEIV_OUTPUTS|OTG_XCEIV_INPUTS| \
	OTG_CTRL_BITS)


/*-------------------------------------------------------------------------*/

/* board-specअगरic PM hooks */

#अगर defined(CONFIG_MACH_OMAP_H2) || defined(CONFIG_MACH_OMAP_H3)

#अगर IS_REACHABLE(CONFIG_TPS65010)

#समावेश <linux/mfd/tps65010.h>

#अन्यथा

अटल अंतरभूत पूर्णांक tps65010_set_vbus_draw(अचिन्हित mA)
अणु
	pr_debug("tps65010: draw %d mA (STUB)\n", mA);
	वापस 0;
पूर्ण

#पूर्ण_अगर

अटल व्योम enable_vbus_draw(काष्ठा isp1301 *isp, अचिन्हित mA)
अणु
	पूर्णांक status = tps65010_set_vbus_draw(mA);
	अगर (status < 0)
		pr_debug("  VBUS %d mA error %d\n", mA, status);
पूर्ण

#अन्यथा

अटल व्योम enable_vbus_draw(काष्ठा isp1301 *isp, अचिन्हित mA)
अणु
	/* H4 controls this by DIP चयन S2.4; no soft control.
	 * ON means the अक्षरger is always enabled.  Leave it OFF
	 * unless the OTG port is used only in B-peripheral mode.
	 */
पूर्ण

#पूर्ण_अगर

अटल व्योम enable_vbus_source(काष्ठा isp1301 *isp)
अणु
	/* this board won't supply more than 8mA vbus घातer.
	 * some boards can चयन a 100ma "unit load" (or more).
	 */
पूर्ण


/* products will deliver OTG messages with LEDs, GUI, etc */
अटल अंतरभूत व्योम notresponding(काष्ठा isp1301 *isp)
अणु
	prपूर्णांकk(KERN_NOTICE "OTG device not responding.\n");
पूर्ण


/*-------------------------------------------------------------------------*/

अटल काष्ठा i2c_driver isp1301_driver;

/* smbus apis are used क्रम portability */

अटल अंतरभूत u8
isp1301_get_u8(काष्ठा isp1301 *isp, u8 reg)
अणु
	वापस i2c_smbus_पढ़ो_byte_data(isp->client, reg + 0);
पूर्ण

अटल अंतरभूत पूर्णांक
isp1301_get_u16(काष्ठा isp1301 *isp, u8 reg)
अणु
	वापस i2c_smbus_पढ़ो_word_data(isp->client, reg);
पूर्ण

अटल अंतरभूत पूर्णांक
isp1301_set_bits(काष्ठा isp1301 *isp, u8 reg, u8 bits)
अणु
	वापस i2c_smbus_ग_लिखो_byte_data(isp->client, reg + 0, bits);
पूर्ण

अटल अंतरभूत पूर्णांक
isp1301_clear_bits(काष्ठा isp1301 *isp, u8 reg, u8 bits)
अणु
	वापस i2c_smbus_ग_लिखो_byte_data(isp->client, reg + 1, bits);
पूर्ण

/*-------------------------------------------------------------------------*/

/* identअगरication */
#घोषणा	ISP1301_VENDOR_ID		0x00	/* u16 पढ़ो */
#घोषणा	ISP1301_PRODUCT_ID		0x02	/* u16 पढ़ो */
#घोषणा	ISP1301_BCD_DEVICE		0x14	/* u16 पढ़ो */

#घोषणा	I2C_VENDOR_ID_PHILIPS		0x04cc
#घोषणा	I2C_PRODUCT_ID_PHILIPS_1301	0x1301

/* operational रेजिस्टरs */
#घोषणा	ISP1301_MODE_CONTROL_1		0x04	/* u8 पढ़ो, set, +1 clear */
#	define	MC1_SPEED		(1 << 0)
#	define	MC1_SUSPEND		(1 << 1)
#	define	MC1_DAT_SE0		(1 << 2)
#	define	MC1_TRANSPARENT		(1 << 3)
#	define	MC1_BDIS_ACON_EN	(1 << 4)
#	define	MC1_OE_INT_EN		(1 << 5)
#	define	MC1_UART_EN		(1 << 6)
#	define	MC1_MASK		0x7f
#घोषणा	ISP1301_MODE_CONTROL_2		0x12	/* u8 पढ़ो, set, +1 clear */
#	define	MC2_GLOBAL_PWR_DN	(1 << 0)
#	define	MC2_SPD_SUSP_CTRL	(1 << 1)
#	define	MC2_BI_DI		(1 << 2)
#	define	MC2_TRANSP_Bसूची0	(1 << 3)
#	define	MC2_TRANSP_Bसूची1	(1 << 4)
#	define	MC2_AUDIO_EN		(1 << 5)
#	define	MC2_PSW_EN		(1 << 6)
#	define	MC2_EN2V7		(1 << 7)
#घोषणा	ISP1301_OTG_CONTROL_1		0x06	/* u8 पढ़ो, set, +1 clear */
#	define	OTG1_DP_PULLUP		(1 << 0)
#	define	OTG1_DM_PULLUP		(1 << 1)
#	define	OTG1_DP_PULLDOWN	(1 << 2)
#	define	OTG1_DM_PULLDOWN	(1 << 3)
#	define	OTG1_ID_PULLDOWN	(1 << 4)
#	define	OTG1_VBUS_DRV		(1 << 5)
#	define	OTG1_VBUS_DISCHRG	(1 << 6)
#	define	OTG1_VBUS_CHRG		(1 << 7)
#घोषणा	ISP1301_OTG_STATUS		0x10	/* u8 पढ़ोonly */
#	define	OTG_B_SESS_END		(1 << 6)
#	define	OTG_B_SESS_VLD		(1 << 7)

#घोषणा	ISP1301_INTERRUPT_SOURCE	0x08	/* u8 पढ़ो */
#घोषणा	ISP1301_INTERRUPT_LATCH		0x0A	/* u8 पढ़ो, set, +1 clear */

#घोषणा	ISP1301_INTERRUPT_FALLING	0x0C	/* u8 पढ़ो, set, +1 clear */
#घोषणा	ISP1301_INTERRUPT_RISING	0x0E	/* u8 पढ़ो, set, +1 clear */

/* same bitfields in all पूर्णांकerrupt रेजिस्टरs */
#	define	INTR_VBUS_VLD		(1 << 0)
#	define	INTR_SESS_VLD		(1 << 1)
#	define	INTR_DP_HI		(1 << 2)
#	define	INTR_ID_GND		(1 << 3)
#	define	INTR_DM_HI		(1 << 4)
#	define	INTR_ID_FLOAT		(1 << 5)
#	define	INTR_BDIS_ACON		(1 << 6)
#	define	INTR_CR_INT		(1 << 7)

/*-------------------------------------------------------------------------*/

अटल अंतरभूत स्थिर अक्षर *state_name(काष्ठा isp1301 *isp)
अणु
	वापस usb_otg_state_string(isp->phy.otg->state);
पूर्ण

/*-------------------------------------------------------------------------*/

/* NOTE:  some of this ISP1301 setup is specअगरic to H2 boards;
 * not everything is guarded by board-specअगरic checks, or even using
 * omap_usb_config data to deduce MC1_DAT_SE0 and MC2_BI_DI.
 *
 * ALSO:  this currently करोesn't use ISP1301 low-घातer modes
 * जबतक OTG is running.
 */

अटल व्योम घातer_करोwn(काष्ठा isp1301 *isp)
अणु
	isp->phy.otg->state = OTG_STATE_UNDEFINED;

	// isp1301_set_bits(isp, ISP1301_MODE_CONTROL_2, MC2_GLOBAL_PWR_DN);
	isp1301_set_bits(isp, ISP1301_MODE_CONTROL_1, MC1_SUSPEND);

	isp1301_clear_bits(isp, ISP1301_OTG_CONTROL_1, OTG1_ID_PULLDOWN);
	isp1301_clear_bits(isp, ISP1301_MODE_CONTROL_1, MC1_DAT_SE0);
पूर्ण

अटल व्योम __maybe_unused घातer_up(काष्ठा isp1301 *isp)
अणु
	// isp1301_clear_bits(isp, ISP1301_MODE_CONTROL_2, MC2_GLOBAL_PWR_DN);
	isp1301_clear_bits(isp, ISP1301_MODE_CONTROL_1, MC1_SUSPEND);

	/* करो this only when cpu is driving transceiver,
	 * so host won't see a low speed device...
	 */
	isp1301_set_bits(isp, ISP1301_MODE_CONTROL_1, MC1_DAT_SE0);
पूर्ण

#घोषणा	NO_HOST_SUSPEND

अटल पूर्णांक host_suspend(काष्ठा isp1301 *isp)
अणु
#अगर_घोषित	NO_HOST_SUSPEND
	वापस 0;
#अन्यथा
	काष्ठा device	*dev;

	अगर (!isp->phy.otg->host)
		वापस -ENODEV;

	/* Currently ASSUMES only the OTG port matters;
	 * other ports could be active...
	 */
	dev = isp->phy.otg->host->controller;
	वापस dev->driver->suspend(dev, 3, 0);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक host_resume(काष्ठा isp1301 *isp)
अणु
#अगर_घोषित	NO_HOST_SUSPEND
	वापस 0;
#अन्यथा
	काष्ठा device	*dev;

	अगर (!isp->phy.otg->host)
		वापस -ENODEV;

	dev = isp->phy.otg->host->controller;
	वापस dev->driver->resume(dev, 0);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक gadget_suspend(काष्ठा isp1301 *isp)
अणु
	isp->phy.otg->gadget->b_hnp_enable = 0;
	isp->phy.otg->gadget->a_hnp_support = 0;
	isp->phy.otg->gadget->a_alt_hnp_support = 0;
	वापस usb_gadget_vbus_disconnect(isp->phy.otg->gadget);
पूर्ण

/*-------------------------------------------------------------------------*/

#घोषणा	TIMER_MINUTES	10
#घोषणा	TIMER_JIFFIES	(TIMER_MINUTES * 60 * HZ)

/* Almost all our I2C messaging comes from a work queue's task context.
 * NOTE: guaranteeing certain response बार might mean we shouldn't
 * share keventd's work queue; a realसमय task might be safest.
 */
अटल व्योम isp1301_defer_work(काष्ठा isp1301 *isp, पूर्णांक work)
अणु
	पूर्णांक status;

	अगर (isp && !test_and_set_bit(work, &isp->toकरो)) अणु
		(व्योम) get_device(&isp->client->dev);
		status = schedule_work(&isp->work);
		अगर (!status && !isp->working)
			dev_vdbg(&isp->client->dev,
				"work item %d may be lost\n", work);
	पूर्ण
पूर्ण

/* called from irq handlers */
अटल व्योम a_idle(काष्ठा isp1301 *isp, स्थिर अक्षर *tag)
अणु
	u32 l;

	अगर (isp->phy.otg->state == OTG_STATE_A_IDLE)
		वापस;

	isp->phy.otg->शेष_a = 1;
	अगर (isp->phy.otg->host) अणु
		isp->phy.otg->host->is_b_host = 0;
		host_suspend(isp);
	पूर्ण
	अगर (isp->phy.otg->gadget) अणु
		isp->phy.otg->gadget->is_a_peripheral = 1;
		gadget_suspend(isp);
	पूर्ण
	isp->phy.otg->state = OTG_STATE_A_IDLE;
	l = omap_पढ़ोl(OTG_CTRL) & OTG_XCEIV_OUTPUTS;
	omap_ग_लिखोl(l, OTG_CTRL);
	isp->last_otg_ctrl = l;
	pr_debug("  --> %s/%s\n", state_name(isp), tag);
पूर्ण

/* called from irq handlers */
अटल व्योम b_idle(काष्ठा isp1301 *isp, स्थिर अक्षर *tag)
अणु
	u32 l;

	अगर (isp->phy.otg->state == OTG_STATE_B_IDLE)
		वापस;

	isp->phy.otg->शेष_a = 0;
	अगर (isp->phy.otg->host) अणु
		isp->phy.otg->host->is_b_host = 1;
		host_suspend(isp);
	पूर्ण
	अगर (isp->phy.otg->gadget) अणु
		isp->phy.otg->gadget->is_a_peripheral = 0;
		gadget_suspend(isp);
	पूर्ण
	isp->phy.otg->state = OTG_STATE_B_IDLE;
	l = omap_पढ़ोl(OTG_CTRL) & OTG_XCEIV_OUTPUTS;
	omap_ग_लिखोl(l, OTG_CTRL);
	isp->last_otg_ctrl = l;
	pr_debug("  --> %s/%s\n", state_name(isp), tag);
पूर्ण

अटल व्योम
dump_regs(काष्ठा isp1301 *isp, स्थिर अक्षर *label)
अणु
	u8	ctrl = isp1301_get_u8(isp, ISP1301_OTG_CONTROL_1);
	u8	status = isp1301_get_u8(isp, ISP1301_OTG_STATUS);
	u8	src = isp1301_get_u8(isp, ISP1301_INTERRUPT_SOURCE);

	pr_debug("otg: %06x, %s %s, otg/%02x stat/%02x.%02x\n",
		omap_पढ़ोl(OTG_CTRL), label, state_name(isp),
		ctrl, status, src);
	/* mode control and irq enables करोn't change much */
पूर्ण

/*-------------------------------------------------------------------------*/

#अगर_घोषित	CONFIG_USB_OTG

/*
 * The OMAP OTG controller handles most of the OTG state transitions.
 *
 * We translate isp1301 outमाला_दो (mostly voltage comparator status) पूर्णांकo
 * OTG inमाला_दो; OTG outमाला_दो (mostly pullup/pullकरोwn controls) and HNP state
 * flags पूर्णांकo isp1301 inमाला_दो ... and infer state transitions.
 */

#अगर_घोषित	VERBOSE

अटल व्योम check_state(काष्ठा isp1301 *isp, स्थिर अक्षर *tag)
अणु
	क्रमागत usb_otg_state	state = OTG_STATE_UNDEFINED;
	u8			fsm = omap_पढ़ोw(OTG_TEST) & 0x0ff;
	अचिन्हित		extra = 0;

	चयन (fsm) अणु

	/* शेष-b */
	हाल 0x0:
		state = OTG_STATE_B_IDLE;
		अवरोध;
	हाल 0x3:
	हाल 0x7:
		extra = 1;
	हाल 0x1:
		state = OTG_STATE_B_PERIPHERAL;
		अवरोध;
	हाल 0x11:
		state = OTG_STATE_B_SRP_INIT;
		अवरोध;

	/* extra dual-role शेष-b states */
	हाल 0x12:
	हाल 0x13:
	हाल 0x16:
		extra = 1;
	हाल 0x17:
		state = OTG_STATE_B_WAIT_ACON;
		अवरोध;
	हाल 0x34:
		state = OTG_STATE_B_HOST;
		अवरोध;

	/* शेष-a */
	हाल 0x36:
		state = OTG_STATE_A_IDLE;
		अवरोध;
	हाल 0x3c:
		state = OTG_STATE_A_WAIT_VFALL;
		अवरोध;
	हाल 0x7d:
		state = OTG_STATE_A_VBUS_ERR;
		अवरोध;
	हाल 0x9e:
	हाल 0x9f:
		extra = 1;
	हाल 0x89:
		state = OTG_STATE_A_PERIPHERAL;
		अवरोध;
	हाल 0xb7:
		state = OTG_STATE_A_WAIT_VRISE;
		अवरोध;
	हाल 0xb8:
		state = OTG_STATE_A_WAIT_BCON;
		अवरोध;
	हाल 0xb9:
		state = OTG_STATE_A_HOST;
		अवरोध;
	हाल 0xba:
		state = OTG_STATE_A_SUSPEND;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	अगर (isp->phy.otg->state == state && !extra)
		वापस;
	pr_debug("otg: %s FSM %s/%02x, %s, %06x\n", tag,
		usb_otg_state_string(state), fsm, state_name(isp),
		omap_पढ़ोl(OTG_CTRL));
पूर्ण

#अन्यथा

अटल अंतरभूत व्योम check_state(काष्ठा isp1301 *isp, स्थिर अक्षर *tag) अणु पूर्ण

#पूर्ण_अगर

/* outमाला_दो from ISP1301_INTERRUPT_SOURCE */
अटल व्योम update_otg1(काष्ठा isp1301 *isp, u8 पूर्णांक_src)
अणु
	u32	otg_ctrl;

	otg_ctrl = omap_पढ़ोl(OTG_CTRL) & OTG_CTRL_MASK;
	otg_ctrl &= ~OTG_XCEIV_INPUTS;
	otg_ctrl &= ~(OTG_ID|OTG_ASESSVLD|OTG_VBUSVLD);

	अगर (पूर्णांक_src & INTR_SESS_VLD)
		otg_ctrl |= OTG_ASESSVLD;
	अन्यथा अगर (isp->phy.otg->state == OTG_STATE_A_WAIT_VFALL) अणु
		a_idle(isp, "vfall");
		otg_ctrl &= ~OTG_CTRL_BITS;
	पूर्ण
	अगर (पूर्णांक_src & INTR_VBUS_VLD)
		otg_ctrl |= OTG_VBUSVLD;
	अगर (पूर्णांक_src & INTR_ID_GND) अणु		/* शेष-A */
		अगर (isp->phy.otg->state == OTG_STATE_B_IDLE
				|| isp->phy.otg->state
					== OTG_STATE_UNDEFINED) अणु
			a_idle(isp, "init");
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु				/* शेष-B */
		otg_ctrl |= OTG_ID;
		अगर (isp->phy.otg->state == OTG_STATE_A_IDLE
			|| isp->phy.otg->state == OTG_STATE_UNDEFINED) अणु
			b_idle(isp, "init");
			वापस;
		पूर्ण
	पूर्ण
	omap_ग_लिखोl(otg_ctrl, OTG_CTRL);
पूर्ण

/* outमाला_दो from ISP1301_OTG_STATUS */
अटल व्योम update_otg2(काष्ठा isp1301 *isp, u8 otg_status)
अणु
	u32	otg_ctrl;

	otg_ctrl = omap_पढ़ोl(OTG_CTRL) & OTG_CTRL_MASK;
	otg_ctrl &= ~OTG_XCEIV_INPUTS;
	otg_ctrl &= ~(OTG_BSESSVLD | OTG_BSESSEND);
	अगर (otg_status & OTG_B_SESS_VLD)
		otg_ctrl |= OTG_BSESSVLD;
	अन्यथा अगर (otg_status & OTG_B_SESS_END)
		otg_ctrl |= OTG_BSESSEND;
	omap_ग_लिखोl(otg_ctrl, OTG_CTRL);
पूर्ण

/* inमाला_दो going to ISP1301 */
अटल व्योम otg_update_isp(काष्ठा isp1301 *isp)
अणु
	u32	otg_ctrl, otg_change;
	u8	set = OTG1_DM_PULLDOWN, clr = OTG1_DM_PULLUP;

	otg_ctrl = omap_पढ़ोl(OTG_CTRL);
	otg_change = otg_ctrl ^ isp->last_otg_ctrl;
	isp->last_otg_ctrl = otg_ctrl;
	otg_ctrl = otg_ctrl & OTG_XCEIV_INPUTS;

	चयन (isp->phy.otg->state) अणु
	हाल OTG_STATE_B_IDLE:
	हाल OTG_STATE_B_PERIPHERAL:
	हाल OTG_STATE_B_SRP_INIT:
		अगर (!(otg_ctrl & OTG_PULLUP)) अणु
			// अगर (otg_ctrl & OTG_B_HNPEN) अणु
			अगर (isp->phy.otg->gadget->b_hnp_enable) अणु
				isp->phy.otg->state = OTG_STATE_B_WAIT_ACON;
				pr_debug("  --> b_wait_acon\n");
			पूर्ण
			जाओ pullकरोwn;
		पूर्ण
pullup:
		set |= OTG1_DP_PULLUP;
		clr |= OTG1_DP_PULLDOWN;
		अवरोध;
	हाल OTG_STATE_A_SUSPEND:
	हाल OTG_STATE_A_PERIPHERAL:
		अगर (otg_ctrl & OTG_PULLUP)
			जाओ pullup;
		/* FALLTHROUGH */
	// हाल OTG_STATE_B_WAIT_ACON:
	शेष:
pullकरोwn:
		set |= OTG1_DP_PULLDOWN;
		clr |= OTG1_DP_PULLUP;
		अवरोध;
	पूर्ण

#	define toggle(OTG,ISP) करो अणु \
		अगर (otg_ctrl & OTG) set |= ISP; \
		अन्यथा clr |= ISP; \
		पूर्ण जबतक (0)

	अगर (!(isp->phy.otg->host))
		otg_ctrl &= ~OTG_DRV_VBUS;

	चयन (isp->phy.otg->state) अणु
	हाल OTG_STATE_A_SUSPEND:
		अगर (otg_ctrl & OTG_DRV_VBUS) अणु
			set |= OTG1_VBUS_DRV;
			अवरोध;
		पूर्ण
		/* HNP failed क्रम some reason (A_AIDL_BDIS समयout) */
		notresponding(isp);

		fallthrough;
	हाल OTG_STATE_A_VBUS_ERR:
		isp->phy.otg->state = OTG_STATE_A_WAIT_VFALL;
		pr_debug("  --> a_wait_vfall\n");
		fallthrough;
	हाल OTG_STATE_A_WAIT_VFALL:
		/* FIXME usbcore thinks port घातer is still on ... */
		clr |= OTG1_VBUS_DRV;
		अवरोध;
	हाल OTG_STATE_A_IDLE:
		अगर (otg_ctrl & OTG_DRV_VBUS) अणु
			isp->phy.otg->state = OTG_STATE_A_WAIT_VRISE;
			pr_debug("  --> a_wait_vrise\n");
		पूर्ण
		fallthrough;
	शेष:
		toggle(OTG_DRV_VBUS, OTG1_VBUS_DRV);
	पूर्ण

	toggle(OTG_PU_VBUS, OTG1_VBUS_CHRG);
	toggle(OTG_PD_VBUS, OTG1_VBUS_DISCHRG);

#	undef toggle

	isp1301_set_bits(isp, ISP1301_OTG_CONTROL_1, set);
	isp1301_clear_bits(isp, ISP1301_OTG_CONTROL_1, clr);

	/* HNP चयन to host or peripheral; and SRP */
	अगर (otg_change & OTG_PULLUP) अणु
		u32 l;

		चयन (isp->phy.otg->state) अणु
		हाल OTG_STATE_B_IDLE:
			अगर (clr & OTG1_DP_PULLUP)
				अवरोध;
			isp->phy.otg->state = OTG_STATE_B_PERIPHERAL;
			pr_debug("  --> b_peripheral\n");
			अवरोध;
		हाल OTG_STATE_A_SUSPEND:
			अगर (clr & OTG1_DP_PULLUP)
				अवरोध;
			isp->phy.otg->state = OTG_STATE_A_PERIPHERAL;
			pr_debug("  --> a_peripheral\n");
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		l = omap_पढ़ोl(OTG_CTRL);
		l |= OTG_PULLUP;
		omap_ग_लिखोl(l, OTG_CTRL);
	पूर्ण

	check_state(isp, __func__);
	dump_regs(isp, "otg->isp1301");
पूर्ण

अटल irqवापस_t omap_otg_irq(पूर्णांक irq, व्योम *_isp)
अणु
	u16		otg_irq = omap_पढ़ोw(OTG_IRQ_SRC);
	u32		otg_ctrl;
	पूर्णांक		ret = IRQ_NONE;
	काष्ठा isp1301	*isp = _isp;
	काष्ठा usb_otg	*otg = isp->phy.otg;

	/* update ISP1301 transceiver from OTG controller */
	अगर (otg_irq & OPRT_CHG) अणु
		omap_ग_लिखोw(OPRT_CHG, OTG_IRQ_SRC);
		isp1301_defer_work(isp, WORK_UPDATE_ISP);
		ret = IRQ_HANDLED;

	/* SRP to become b_peripheral failed */
	पूर्ण अन्यथा अगर (otg_irq & B_SRP_TMROUT) अणु
		pr_debug("otg: B_SRP_TIMEOUT, %06x\n", omap_पढ़ोl(OTG_CTRL));
		notresponding(isp);

		/* gadget drivers that care should monitor all kinds of
		 * remote wakeup (SRP, normal) using their own समयr
		 * to give "check cable and A-device" messages.
		 */
		अगर (isp->phy.otg->state == OTG_STATE_B_SRP_INIT)
			b_idle(isp, "srp_timeout");

		omap_ग_लिखोw(B_SRP_TMROUT, OTG_IRQ_SRC);
		ret = IRQ_HANDLED;

	/* HNP to become b_host failed */
	पूर्ण अन्यथा अगर (otg_irq & B_HNP_FAIL) अणु
		pr_debug("otg: %s B_HNP_FAIL, %06x\n",
				state_name(isp), omap_पढ़ोl(OTG_CTRL));
		notresponding(isp);

		otg_ctrl = omap_पढ़ोl(OTG_CTRL);
		otg_ctrl |= OTG_BUSDROP;
		otg_ctrl &= OTG_CTRL_MASK & ~OTG_XCEIV_INPUTS;
		omap_ग_लिखोl(otg_ctrl, OTG_CTRL);

		/* subset of b_peripheral()... */
		isp->phy.otg->state = OTG_STATE_B_PERIPHERAL;
		pr_debug("  --> b_peripheral\n");

		omap_ग_लिखोw(B_HNP_FAIL, OTG_IRQ_SRC);
		ret = IRQ_HANDLED;

	/* detect SRP from B-device ... */
	पूर्ण अन्यथा अगर (otg_irq & A_SRP_DETECT) अणु
		pr_debug("otg: %s SRP_DETECT, %06x\n",
				state_name(isp), omap_पढ़ोl(OTG_CTRL));

		isp1301_defer_work(isp, WORK_UPDATE_OTG);
		चयन (isp->phy.otg->state) अणु
		हाल OTG_STATE_A_IDLE:
			अगर (!otg->host)
				अवरोध;
			isp1301_defer_work(isp, WORK_HOST_RESUME);
			otg_ctrl = omap_पढ़ोl(OTG_CTRL);
			otg_ctrl |= OTG_A_BUSREQ;
			otg_ctrl &= ~(OTG_BUSDROP|OTG_B_BUSREQ)
					& ~OTG_XCEIV_INPUTS
					& OTG_CTRL_MASK;
			omap_ग_लिखोl(otg_ctrl, OTG_CTRL);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		omap_ग_लिखोw(A_SRP_DETECT, OTG_IRQ_SRC);
		ret = IRQ_HANDLED;

	/* समयr expired:  T(a_रुको_bcon) and maybe T(a_रुको_vrise)
	 * we करोn't track them separately
	 */
	पूर्ण अन्यथा अगर (otg_irq & A_REQ_TMROUT) अणु
		otg_ctrl = omap_पढ़ोl(OTG_CTRL);
		pr_info("otg: BCON_TMOUT from %s, %06x\n",
				state_name(isp), otg_ctrl);
		notresponding(isp);

		otg_ctrl |= OTG_BUSDROP;
		otg_ctrl &= ~OTG_A_BUSREQ & OTG_CTRL_MASK & ~OTG_XCEIV_INPUTS;
		omap_ग_लिखोl(otg_ctrl, OTG_CTRL);
		isp->phy.otg->state = OTG_STATE_A_WAIT_VFALL;

		omap_ग_लिखोw(A_REQ_TMROUT, OTG_IRQ_SRC);
		ret = IRQ_HANDLED;

	/* A-supplied voltage fell too low; overcurrent */
	पूर्ण अन्यथा अगर (otg_irq & A_VBUS_ERR) अणु
		otg_ctrl = omap_पढ़ोl(OTG_CTRL);
		prपूर्णांकk(KERN_ERR "otg: %s, VBUS_ERR %04x ctrl %06x\n",
			state_name(isp), otg_irq, otg_ctrl);

		otg_ctrl |= OTG_BUSDROP;
		otg_ctrl &= ~OTG_A_BUSREQ & OTG_CTRL_MASK & ~OTG_XCEIV_INPUTS;
		omap_ग_लिखोl(otg_ctrl, OTG_CTRL);
		isp->phy.otg->state = OTG_STATE_A_VBUS_ERR;

		omap_ग_लिखोw(A_VBUS_ERR, OTG_IRQ_SRC);
		ret = IRQ_HANDLED;

	/* चयन driver; the transceiver code activates it,
	 * ungating the udc घड़ी or resuming OHCI.
	 */
	पूर्ण अन्यथा अगर (otg_irq & DRIVER_SWITCH) अणु
		पूर्णांक	kick = 0;

		otg_ctrl = omap_पढ़ोl(OTG_CTRL);
		prपूर्णांकk(KERN_NOTICE "otg: %s, SWITCH to %s, ctrl %06x\n",
				state_name(isp),
				(otg_ctrl & OTG_DRIVER_SEL)
					? "gadget" : "host",
				otg_ctrl);
		isp1301_defer_work(isp, WORK_UPDATE_ISP);

		/* role is peripheral */
		अगर (otg_ctrl & OTG_DRIVER_SEL) अणु
			चयन (isp->phy.otg->state) अणु
			हाल OTG_STATE_A_IDLE:
				b_idle(isp, __func__);
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
			isp1301_defer_work(isp, WORK_UPDATE_ISP);

		/* role is host */
		पूर्ण अन्यथा अणु
			अगर (!(otg_ctrl & OTG_ID)) अणु
				otg_ctrl &= OTG_CTRL_MASK & ~OTG_XCEIV_INPUTS;
				omap_ग_लिखोl(otg_ctrl | OTG_A_BUSREQ, OTG_CTRL);
			पूर्ण

			अगर (otg->host) अणु
				चयन (isp->phy.otg->state) अणु
				हाल OTG_STATE_B_WAIT_ACON:
					isp->phy.otg->state = OTG_STATE_B_HOST;
					pr_debug("  --> b_host\n");
					kick = 1;
					अवरोध;
				हाल OTG_STATE_A_WAIT_BCON:
					isp->phy.otg->state = OTG_STATE_A_HOST;
					pr_debug("  --> a_host\n");
					अवरोध;
				हाल OTG_STATE_A_PERIPHERAL:
					isp->phy.otg->state = OTG_STATE_A_WAIT_BCON;
					pr_debug("  --> a_wait_bcon\n");
					अवरोध;
				शेष:
					अवरोध;
				पूर्ण
				isp1301_defer_work(isp, WORK_HOST_RESUME);
			पूर्ण
		पूर्ण

		omap_ग_लिखोw(DRIVER_SWITCH, OTG_IRQ_SRC);
		ret = IRQ_HANDLED;

		अगर (kick)
			usb_bus_start_क्रमागत(otg->host, otg->host->otg_port);
	पूर्ण

	check_state(isp, __func__);
	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_device *otg_dev;

अटल पूर्णांक isp1301_otg_init(काष्ठा isp1301 *isp)
अणु
	u32 l;

	अगर (!otg_dev)
		वापस -ENODEV;

	dump_regs(isp, __func__);
	/* some of these values are board-specअगरic... */
	l = omap_पढ़ोl(OTG_SYSCON_2);
	l |= OTG_EN
		/* क्रम B-device: */
		| SRP_GPDATA		/* 9msec Bdev D+ pulse */
		| SRP_GPDVBUS		/* disअक्षरge after VBUS pulse */
		// | (3 << 24)		/* 2msec VBUS pulse */
		/* क्रम A-device: */
		| (0 << 20)		/* 200ms nominal A_WAIT_VRISE समयr */
		| SRP_DPW		/* detect 167+ns SRP pulses */
		| SRP_DATA | SRP_VBUS	/* accept both kinds of SRP pulse */
		;
	omap_ग_लिखोl(l, OTG_SYSCON_2);

	update_otg1(isp, isp1301_get_u8(isp, ISP1301_INTERRUPT_SOURCE));
	update_otg2(isp, isp1301_get_u8(isp, ISP1301_OTG_STATUS));

	check_state(isp, __func__);
	pr_debug("otg: %s, %s %06x\n",
			state_name(isp), __func__, omap_पढ़ोl(OTG_CTRL));

	omap_ग_लिखोw(DRIVER_SWITCH | OPRT_CHG
			| B_SRP_TMROUT | B_HNP_FAIL
			| A_VBUS_ERR | A_SRP_DETECT | A_REQ_TMROUT, OTG_IRQ_EN);

	l = omap_पढ़ोl(OTG_SYSCON_2);
	l |= OTG_EN;
	omap_ग_लिखोl(l, OTG_SYSCON_2);

	वापस 0;
पूर्ण

अटल पूर्णांक otg_probe(काष्ठा platक्रमm_device *dev)
अणु
	// काष्ठा omap_usb_config *config = dev->platक्रमm_data;

	otg_dev = dev;
	वापस 0;
पूर्ण

अटल पूर्णांक otg_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	otg_dev = शून्य;
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver omap_otg_driver = अणु
	.probe		= otg_probe,
	.हटाओ		= otg_हटाओ,
	.driver		= अणु
		.name	= "omap_otg",
	पूर्ण,
पूर्ण;

अटल पूर्णांक otg_bind(काष्ठा isp1301 *isp)
अणु
	पूर्णांक	status;

	अगर (otg_dev)
		वापस -EBUSY;

	status = platक्रमm_driver_रेजिस्टर(&omap_otg_driver);
	अगर (status < 0)
		वापस status;

	अगर (otg_dev)
		status = request_irq(otg_dev->resource[1].start, omap_otg_irq,
				0, DRIVER_NAME, isp);
	अन्यथा
		status = -ENODEV;

	अगर (status < 0)
		platक्रमm_driver_unरेजिस्टर(&omap_otg_driver);
	वापस status;
पूर्ण

अटल व्योम otg_unbind(काष्ठा isp1301 *isp)
अणु
	अगर (!otg_dev)
		वापस;
	मुक्त_irq(otg_dev->resource[1].start, isp);
पूर्ण

#अन्यथा

/* OTG controller isn't घड़ीed */

#पूर्ण_अगर	/* CONFIG_USB_OTG */

/*-------------------------------------------------------------------------*/

अटल व्योम b_peripheral(काष्ठा isp1301 *isp)
अणु
	u32 l;

	l = omap_पढ़ोl(OTG_CTRL) & OTG_XCEIV_OUTPUTS;
	omap_ग_लिखोl(l, OTG_CTRL);

	usb_gadget_vbus_connect(isp->phy.otg->gadget);

#अगर_घोषित	CONFIG_USB_OTG
	enable_vbus_draw(isp, 8);
	otg_update_isp(isp);
#अन्यथा
	enable_vbus_draw(isp, 100);
	/* UDC driver just set OTG_BSESSVLD */
	isp1301_set_bits(isp, ISP1301_OTG_CONTROL_1, OTG1_DP_PULLUP);
	isp1301_clear_bits(isp, ISP1301_OTG_CONTROL_1, OTG1_DP_PULLDOWN);
	isp->phy.otg->state = OTG_STATE_B_PERIPHERAL;
	pr_debug("  --> b_peripheral\n");
	dump_regs(isp, "2periph");
#पूर्ण_अगर
पूर्ण

अटल व्योम isp_update_otg(काष्ठा isp1301 *isp, u8 stat)
अणु
	काष्ठा usb_otg		*otg = isp->phy.otg;
	u8			isp_stat, isp_bstat;
	क्रमागत usb_otg_state	state = isp->phy.otg->state;

	अगर (stat & INTR_BDIS_ACON)
		pr_debug("OTG:  BDIS_ACON, %s\n", state_name(isp));

	/* start certain state transitions right away */
	isp_stat = isp1301_get_u8(isp, ISP1301_INTERRUPT_SOURCE);
	अगर (isp_stat & INTR_ID_GND) अणु
		अगर (otg->शेष_a) अणु
			चयन (state) अणु
			हाल OTG_STATE_B_IDLE:
				a_idle(isp, "idle");
				fallthrough;
			हाल OTG_STATE_A_IDLE:
				enable_vbus_source(isp);
				fallthrough;
			हाल OTG_STATE_A_WAIT_VRISE:
				/* we skip over OTG_STATE_A_WAIT_BCON, since
				 * the HC will transition to A_HOST (or
				 * A_SUSPEND!) without our noticing except
				 * when HNP is used.
				 */
				अगर (isp_stat & INTR_VBUS_VLD)
					isp->phy.otg->state = OTG_STATE_A_HOST;
				अवरोध;
			हाल OTG_STATE_A_WAIT_VFALL:
				अगर (!(isp_stat & INTR_SESS_VLD))
					a_idle(isp, "vfell");
				अवरोध;
			शेष:
				अगर (!(isp_stat & INTR_VBUS_VLD))
					isp->phy.otg->state = OTG_STATE_A_VBUS_ERR;
				अवरोध;
			पूर्ण
			isp_bstat = isp1301_get_u8(isp, ISP1301_OTG_STATUS);
		पूर्ण अन्यथा अणु
			चयन (state) अणु
			हाल OTG_STATE_B_PERIPHERAL:
			हाल OTG_STATE_B_HOST:
			हाल OTG_STATE_B_WAIT_ACON:
				usb_gadget_vbus_disconnect(otg->gadget);
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
			अगर (state != OTG_STATE_A_IDLE)
				a_idle(isp, "id");
			अगर (otg->host && state == OTG_STATE_A_IDLE)
				isp1301_defer_work(isp, WORK_HOST_RESUME);
			isp_bstat = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		u32 l;

		/* अगर user unplugged mini-A end of cable,
		 * करोn't bypass A_WAIT_VFALL.
		 */
		अगर (otg->शेष_a) अणु
			चयन (state) अणु
			शेष:
				isp->phy.otg->state = OTG_STATE_A_WAIT_VFALL;
				अवरोध;
			हाल OTG_STATE_A_WAIT_VFALL:
				state = OTG_STATE_A_IDLE;
				/* hub_wq may take a जबतक to notice and
				 * handle this disconnect, so करोn't go
				 * to B_IDLE quite yet.
				 */
				अवरोध;
			हाल OTG_STATE_A_IDLE:
				host_suspend(isp);
				isp1301_clear_bits(isp, ISP1301_MODE_CONTROL_1,
						MC1_BDIS_ACON_EN);
				isp->phy.otg->state = OTG_STATE_B_IDLE;
				l = omap_पढ़ोl(OTG_CTRL) & OTG_CTRL_MASK;
				l &= ~OTG_CTRL_BITS;
				omap_ग_लिखोl(l, OTG_CTRL);
				अवरोध;
			हाल OTG_STATE_B_IDLE:
				अवरोध;
			पूर्ण
		पूर्ण
		isp_bstat = isp1301_get_u8(isp, ISP1301_OTG_STATUS);

		चयन (isp->phy.otg->state) अणु
		हाल OTG_STATE_B_PERIPHERAL:
		हाल OTG_STATE_B_WAIT_ACON:
		हाल OTG_STATE_B_HOST:
			अगर (likely(isp_bstat & OTG_B_SESS_VLD))
				अवरोध;
			enable_vbus_draw(isp, 0);
#अगर_अघोषित	CONFIG_USB_OTG
			/* UDC driver will clear OTG_BSESSVLD */
			isp1301_set_bits(isp, ISP1301_OTG_CONTROL_1,
						OTG1_DP_PULLDOWN);
			isp1301_clear_bits(isp, ISP1301_OTG_CONTROL_1,
						OTG1_DP_PULLUP);
			dump_regs(isp, __func__);
#पूर्ण_अगर
			fallthrough;
		हाल OTG_STATE_B_SRP_INIT:
			b_idle(isp, __func__);
			l = omap_पढ़ोl(OTG_CTRL) & OTG_XCEIV_OUTPUTS;
			omap_ग_लिखोl(l, OTG_CTRL);
			fallthrough;
		हाल OTG_STATE_B_IDLE:
			अगर (otg->gadget && (isp_bstat & OTG_B_SESS_VLD)) अणु
#अगर_घोषित	CONFIG_USB_OTG
				update_otg1(isp, isp_stat);
				update_otg2(isp, isp_bstat);
#पूर्ण_अगर
				b_peripheral(isp);
			पूर्ण अन्यथा अगर (!(isp_stat & (INTR_VBUS_VLD|INTR_SESS_VLD)))
				isp_bstat |= OTG_B_SESS_END;
			अवरोध;
		हाल OTG_STATE_A_WAIT_VFALL:
			अवरोध;
		शेष:
			pr_debug("otg: unsupported b-device %s\n",
				state_name(isp));
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (state != isp->phy.otg->state)
		pr_debug("  isp, %s -> %s\n",
				usb_otg_state_string(state), state_name(isp));

#अगर_घोषित	CONFIG_USB_OTG
	/* update the OTG controller state to match the isp1301; may
	 * trigger OPRT_CHG irqs क्रम changes going to the isp1301.
	 */
	update_otg1(isp, isp_stat);
	update_otg2(isp, isp_bstat);
	check_state(isp, __func__);
#पूर्ण_अगर

	dump_regs(isp, "isp1301->otg");
पूर्ण

/*-------------------------------------------------------------------------*/

अटल u8 isp1301_clear_latch(काष्ठा isp1301 *isp)
अणु
	u8 latch = isp1301_get_u8(isp, ISP1301_INTERRUPT_LATCH);
	isp1301_clear_bits(isp, ISP1301_INTERRUPT_LATCH, latch);
	वापस latch;
पूर्ण

अटल व्योम
isp1301_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा isp1301	*isp = container_of(work, काष्ठा isp1301, work);
	पूर्णांक		stop;

	/* implicit lock:  we're the only task using this device */
	isp->working = 1;
	करो अणु
		stop = test_bit(WORK_STOP, &isp->toकरो);

#अगर_घोषित	CONFIG_USB_OTG
		/* transfer state from otg engine to isp1301 */
		अगर (test_and_clear_bit(WORK_UPDATE_ISP, &isp->toकरो)) अणु
			otg_update_isp(isp);
			put_device(&isp->client->dev);
		पूर्ण
#पूर्ण_अगर
		/* transfer state from isp1301 to otg engine */
		अगर (test_and_clear_bit(WORK_UPDATE_OTG, &isp->toकरो)) अणु
			u8		stat = isp1301_clear_latch(isp);

			isp_update_otg(isp, stat);
			put_device(&isp->client->dev);
		पूर्ण

		अगर (test_and_clear_bit(WORK_HOST_RESUME, &isp->toकरो)) अणु
			u32	otg_ctrl;

			/*
			 * skip A_WAIT_VRISE; hc transitions invisibly
			 * skip A_WAIT_BCON; same.
			 */
			चयन (isp->phy.otg->state) अणु
			हाल OTG_STATE_A_WAIT_BCON:
			हाल OTG_STATE_A_WAIT_VRISE:
				isp->phy.otg->state = OTG_STATE_A_HOST;
				pr_debug("  --> a_host\n");
				otg_ctrl = omap_पढ़ोl(OTG_CTRL);
				otg_ctrl |= OTG_A_BUSREQ;
				otg_ctrl &= ~(OTG_BUSDROP|OTG_B_BUSREQ)
						& OTG_CTRL_MASK;
				omap_ग_लिखोl(otg_ctrl, OTG_CTRL);
				अवरोध;
			हाल OTG_STATE_B_WAIT_ACON:
				isp->phy.otg->state = OTG_STATE_B_HOST;
				pr_debug("  --> b_host (acon)\n");
				अवरोध;
			हाल OTG_STATE_B_HOST:
			हाल OTG_STATE_B_IDLE:
			हाल OTG_STATE_A_IDLE:
				अवरोध;
			शेष:
				pr_debug("  host resume in %s\n",
						state_name(isp));
			पूर्ण
			host_resume(isp);
			// mdelay(10);
			put_device(&isp->client->dev);
		पूर्ण

		अगर (test_and_clear_bit(WORK_TIMER, &isp->toकरो)) अणु
#अगर_घोषित	VERBOSE
			dump_regs(isp, "timer");
			अगर (!stop)
				mod_समयr(&isp->समयr, jअगरfies + TIMER_JIFFIES);
#पूर्ण_अगर
			put_device(&isp->client->dev);
		पूर्ण

		अगर (isp->toकरो)
			dev_vdbg(&isp->client->dev,
				"work done, todo = 0x%lx\n",
				isp->toकरो);
		अगर (stop) अणु
			dev_dbg(&isp->client->dev, "stop\n");
			अवरोध;
		पूर्ण
	पूर्ण जबतक (isp->toकरो);
	isp->working = 0;
पूर्ण

अटल irqवापस_t isp1301_irq(पूर्णांक irq, व्योम *isp)
अणु
	isp1301_defer_work(isp, WORK_UPDATE_OTG);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम isp1301_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा isp1301 *isp = from_समयr(isp, t, समयr);

	isp1301_defer_work(isp, WORK_TIMER);
पूर्ण

/*-------------------------------------------------------------------------*/

अटल व्योम isp1301_release(काष्ठा device *dev)
अणु
	काष्ठा isp1301	*isp;

	isp = dev_get_drvdata(dev);

	/* FIXME -- not with a "new style" driver, it करोesn't!! */

	/* ugly -- i2c hijacks our memory hook to रुको_क्रम_completion() */
	अगर (isp->i2c_release)
		isp->i2c_release(dev);
	kमुक्त(isp->phy.otg);
	kमुक्त (isp);
पूर्ण

अटल काष्ठा isp1301 *the_transceiver;

अटल पूर्णांक isp1301_हटाओ(काष्ठा i2c_client *i2c)
अणु
	काष्ठा isp1301	*isp;

	isp = i2c_get_clientdata(i2c);

	isp1301_clear_bits(isp, ISP1301_INTERRUPT_FALLING, ~0);
	isp1301_clear_bits(isp, ISP1301_INTERRUPT_RISING, ~0);
	मुक्त_irq(i2c->irq, isp);
#अगर_घोषित	CONFIG_USB_OTG
	otg_unbind(isp);
#पूर्ण_अगर
	set_bit(WORK_STOP, &isp->toकरो);
	del_समयr_sync(&isp->समयr);
	flush_work(&isp->work);

	put_device(&i2c->dev);
	the_transceiver = शून्य;

	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/

/* NOTE:  three modes are possible here, only one of which
 * will be standards-conक्रमmant on any given प्रणाली:
 *
 *  - OTG mode (dual-role), required अगर there's a Mini-AB connector
 *  - HOST mode, क्रम when there's one or more A (host) connectors
 *  - DEVICE mode, क्रम when there's a B/Mini-B (device) connector
 *
 * As a rule, you won't have an isp1301 chip unless it's there to
 * support the OTG mode.  Other modes help testing USB controllers
 * in isolation from (full) OTG support, or maybe so later board
 * revisions can help to support those feature.
 */

#अगर_घोषित	CONFIG_USB_OTG

अटल पूर्णांक isp1301_otg_enable(काष्ठा isp1301 *isp)
अणु
	घातer_up(isp);
	isp1301_otg_init(isp);

	/* NOTE:  since we करोn't change this, this provides
	 * a few more पूर्णांकerrupts than are strictly needed.
	 */
	isp1301_set_bits(isp, ISP1301_INTERRUPT_RISING,
		INTR_VBUS_VLD | INTR_SESS_VLD | INTR_ID_GND);
	isp1301_set_bits(isp, ISP1301_INTERRUPT_FALLING,
		INTR_VBUS_VLD | INTR_SESS_VLD | INTR_ID_GND);

	dev_info(&isp->client->dev, "ready for dual-role USB ...\n");

	वापस 0;
पूर्ण

#पूर्ण_अगर

/* add or disable the host device+driver */
अटल पूर्णांक
isp1301_set_host(काष्ठा usb_otg *otg, काष्ठा usb_bus *host)
अणु
	काष्ठा isp1301	*isp = container_of(otg->usb_phy, काष्ठा isp1301, phy);

	अगर (isp != the_transceiver)
		वापस -ENODEV;

	अगर (!host) अणु
		omap_ग_लिखोw(0, OTG_IRQ_EN);
		घातer_करोwn(isp);
		otg->host = शून्य;
		वापस 0;
	पूर्ण

#अगर_घोषित	CONFIG_USB_OTG
	otg->host = host;
	dev_dbg(&isp->client->dev, "registered host\n");
	host_suspend(isp);
	अगर (otg->gadget)
		वापस isp1301_otg_enable(isp);
	वापस 0;

#या_अगर !IS_ENABLED(CONFIG_USB_OMAP)
	// FIXME update its refcount
	otg->host = host;

	घातer_up(isp);

	अगर (machine_is_omap_h2())
		isp1301_set_bits(isp, ISP1301_MODE_CONTROL_1, MC1_DAT_SE0);

	dev_info(&isp->client->dev, "A-Host sessions ok\n");
	isp1301_set_bits(isp, ISP1301_INTERRUPT_RISING,
		INTR_ID_GND);
	isp1301_set_bits(isp, ISP1301_INTERRUPT_FALLING,
		INTR_ID_GND);

	/* If this has a Mini-AB connector, this mode is highly
	 * nonstandard ... but can be handy क्रम testing, especially with
	 * the Mini-A end of an OTG cable.  (Or something nonstandard
	 * like MiniB-to-StandardB, maybe built with a gender mender.)
	 */
	isp1301_set_bits(isp, ISP1301_OTG_CONTROL_1, OTG1_VBUS_DRV);

	dump_regs(isp, __func__);

	वापस 0;

#अन्यथा
	dev_dbg(&isp->client->dev, "host sessions not allowed\n");
	वापस -EINVAL;
#पूर्ण_अगर

पूर्ण

अटल पूर्णांक
isp1301_set_peripheral(काष्ठा usb_otg *otg, काष्ठा usb_gadget *gadget)
अणु
	काष्ठा isp1301	*isp = container_of(otg->usb_phy, काष्ठा isp1301, phy);

	अगर (isp != the_transceiver)
		वापस -ENODEV;

	अगर (!gadget) अणु
		omap_ग_लिखोw(0, OTG_IRQ_EN);
		अगर (!otg->शेष_a)
			enable_vbus_draw(isp, 0);
		usb_gadget_vbus_disconnect(otg->gadget);
		otg->gadget = शून्य;
		घातer_करोwn(isp);
		वापस 0;
	पूर्ण

#अगर_घोषित	CONFIG_USB_OTG
	otg->gadget = gadget;
	dev_dbg(&isp->client->dev, "registered gadget\n");
	/* gadget driver may be suspended until vbus_connect () */
	अगर (otg->host)
		वापस isp1301_otg_enable(isp);
	वापस 0;

#या_अगर	!defined(CONFIG_USB_OHCI_HCD) && !defined(CONFIG_USB_OHCI_HCD_MODULE)
	otg->gadget = gadget;
	// FIXME update its refcount

	अणु
		u32 l;

		l = omap_पढ़ोl(OTG_CTRL) & OTG_CTRL_MASK;
		l &= ~(OTG_XCEIV_OUTPUTS|OTG_CTRL_BITS);
		l |= OTG_ID;
		omap_ग_लिखोl(l, OTG_CTRL);
	पूर्ण

	घातer_up(isp);
	isp->phy.otg->state = OTG_STATE_B_IDLE;

	अगर (machine_is_omap_h2() || machine_is_omap_h3())
		isp1301_set_bits(isp, ISP1301_MODE_CONTROL_1, MC1_DAT_SE0);

	isp1301_set_bits(isp, ISP1301_INTERRUPT_RISING,
		INTR_SESS_VLD);
	isp1301_set_bits(isp, ISP1301_INTERRUPT_FALLING,
		INTR_VBUS_VLD);
	dev_info(&isp->client->dev, "B-Peripheral sessions ok\n");
	dump_regs(isp, __func__);

	/* If this has a Mini-AB connector, this mode is highly
	 * nonstandard ... but can be handy क्रम testing, so दीर्घ
	 * as you करोn't plug a Mini-A cable पूर्णांकo the jack.
	 */
	अगर (isp1301_get_u8(isp, ISP1301_INTERRUPT_SOURCE) & INTR_VBUS_VLD)
		b_peripheral(isp);

	वापस 0;

#अन्यथा
	dev_dbg(&isp->client->dev, "peripheral sessions not allowed\n");
	वापस -EINVAL;
#पूर्ण_अगर
पूर्ण


/*-------------------------------------------------------------------------*/

अटल पूर्णांक
isp1301_set_घातer(काष्ठा usb_phy *dev, अचिन्हित mA)
अणु
	अगर (!the_transceiver)
		वापस -ENODEV;
	अगर (dev->otg->state == OTG_STATE_B_PERIPHERAL)
		enable_vbus_draw(the_transceiver, mA);
	वापस 0;
पूर्ण

अटल पूर्णांक
isp1301_start_srp(काष्ठा usb_otg *otg)
अणु
	काष्ठा isp1301	*isp = container_of(otg->usb_phy, काष्ठा isp1301, phy);
	u32		otg_ctrl;

	अगर (isp != the_transceiver || isp->phy.otg->state != OTG_STATE_B_IDLE)
		वापस -ENODEV;

	otg_ctrl = omap_पढ़ोl(OTG_CTRL);
	अगर (!(otg_ctrl & OTG_BSESSEND))
		वापस -EINVAL;

	otg_ctrl |= OTG_B_BUSREQ;
	otg_ctrl &= ~OTG_A_BUSREQ & OTG_CTRL_MASK;
	omap_ग_लिखोl(otg_ctrl, OTG_CTRL);
	isp->phy.otg->state = OTG_STATE_B_SRP_INIT;

	pr_debug("otg: SRP, %s ... %06x\n", state_name(isp),
			omap_पढ़ोl(OTG_CTRL));
#अगर_घोषित	CONFIG_USB_OTG
	check_state(isp, __func__);
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक
isp1301_start_hnp(काष्ठा usb_otg *otg)
अणु
#अगर_घोषित	CONFIG_USB_OTG
	काष्ठा isp1301	*isp = container_of(otg->usb_phy, काष्ठा isp1301, phy);
	u32 l;

	अगर (isp != the_transceiver)
		वापस -ENODEV;
	अगर (otg->शेष_a && (otg->host == शून्य || !otg->host->b_hnp_enable))
		वापस -ENOTCONN;
	अगर (!otg->शेष_a && (otg->gadget == शून्य
			|| !otg->gadget->b_hnp_enable))
		वापस -ENOTCONN;

	/* We want hardware to manage most HNP protocol timings.
	 * So करो this part as early as possible...
	 */
	चयन (isp->phy.otg->state) अणु
	हाल OTG_STATE_B_HOST:
		isp->phy.otg->state = OTG_STATE_B_PERIPHERAL;
		/* caller will suspend next */
		अवरोध;
	हाल OTG_STATE_A_HOST:
#अगर 0
		/* स्वतःconnect mode aव्योमs irq latency bugs */
		isp1301_set_bits(isp, ISP1301_MODE_CONTROL_1,
				MC1_BDIS_ACON_EN);
#पूर्ण_अगर
		/* caller must suspend then clear A_BUSREQ */
		usb_gadget_vbus_connect(otg->gadget);
		l = omap_पढ़ोl(OTG_CTRL);
		l |= OTG_A_SETB_HNPEN;
		omap_ग_लिखोl(l, OTG_CTRL);

		अवरोध;
	हाल OTG_STATE_A_PERIPHERAL:
		/* initiated by B-Host suspend */
		अवरोध;
	शेष:
		वापस -EILSEQ;
	पूर्ण
	pr_debug("otg: HNP %s, %06x ...\n",
		state_name(isp), omap_पढ़ोl(OTG_CTRL));
	check_state(isp, __func__);
	वापस 0;
#अन्यथा
	/* srp-only */
	वापस -EINVAL;
#पूर्ण_अगर
पूर्ण

/*-------------------------------------------------------------------------*/

अटल पूर्णांक
isp1301_probe(काष्ठा i2c_client *i2c, स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक			status;
	काष्ठा isp1301		*isp;
	पूर्णांक irq;

	अगर (the_transceiver)
		वापस 0;

	isp = kzalloc(माप *isp, GFP_KERNEL);
	अगर (!isp)
		वापस 0;

	isp->phy.otg = kzalloc(माप *isp->phy.otg, GFP_KERNEL);
	अगर (!isp->phy.otg) अणु
		kमुक्त(isp);
		वापस 0;
	पूर्ण

	INIT_WORK(&isp->work, isp1301_work);
	समयr_setup(&isp->समयr, isp1301_समयr, 0);

	i2c_set_clientdata(i2c, isp);
	isp->client = i2c;

	/* verअगरy the chip (shouldn't be necessary) */
	status = isp1301_get_u16(isp, ISP1301_VENDOR_ID);
	अगर (status != I2C_VENDOR_ID_PHILIPS) अणु
		dev_dbg(&i2c->dev, "not philips id: %d\n", status);
		जाओ fail;
	पूर्ण
	status = isp1301_get_u16(isp, ISP1301_PRODUCT_ID);
	अगर (status != I2C_PRODUCT_ID_PHILIPS_1301) अणु
		dev_dbg(&i2c->dev, "not isp1301, %d\n", status);
		जाओ fail;
	पूर्ण
	isp->i2c_release = i2c->dev.release;
	i2c->dev.release = isp1301_release;

	/* initial development used chiprev 2.00 */
	status = i2c_smbus_पढ़ो_word_data(i2c, ISP1301_BCD_DEVICE);
	dev_info(&i2c->dev, "chiprev %x.%02x, driver " DRIVER_VERSION "\n",
		status >> 8, status & 0xff);

	/* make like घातer-on reset */
	isp1301_clear_bits(isp, ISP1301_MODE_CONTROL_1, MC1_MASK);

	isp1301_set_bits(isp, ISP1301_MODE_CONTROL_2, MC2_BI_DI);
	isp1301_clear_bits(isp, ISP1301_MODE_CONTROL_2, ~MC2_BI_DI);

	isp1301_set_bits(isp, ISP1301_OTG_CONTROL_1,
				OTG1_DM_PULLDOWN | OTG1_DP_PULLDOWN);
	isp1301_clear_bits(isp, ISP1301_OTG_CONTROL_1,
				~(OTG1_DM_PULLDOWN | OTG1_DP_PULLDOWN));

	isp1301_clear_bits(isp, ISP1301_INTERRUPT_LATCH, ~0);
	isp1301_clear_bits(isp, ISP1301_INTERRUPT_FALLING, ~0);
	isp1301_clear_bits(isp, ISP1301_INTERRUPT_RISING, ~0);

#अगर_घोषित	CONFIG_USB_OTG
	status = otg_bind(isp);
	अगर (status < 0) अणु
		dev_dbg(&i2c->dev, "can't bind OTG\n");
		जाओ fail;
	पूर्ण
#पूर्ण_अगर

	अगर (machine_is_omap_h2()) अणु
		काष्ठा gpio_desc *gpiod;

		/* full speed संकेतing by शेष */
		isp1301_set_bits(isp, ISP1301_MODE_CONTROL_1,
			MC1_SPEED);
		isp1301_set_bits(isp, ISP1301_MODE_CONTROL_2,
			MC2_SPD_SUSP_CTRL);

		gpiod = devm_gpiod_get(&i2c->dev, शून्य, GPIOD_IN);
		अगर (IS_ERR(gpiod)) अणु
			dev_err(&i2c->dev, "cannot obtain H2 GPIO\n");
			जाओ fail;
		पूर्ण
		gpiod_set_consumer_name(gpiod, "isp1301");
		irq = gpiod_to_irq(gpiod);
		isp->irq_type = IRQF_TRIGGER_FALLING;
	पूर्ण अन्यथा अणु
		irq = i2c->irq;
	पूर्ण

	status = request_irq(irq, isp1301_irq,
			isp->irq_type, DRIVER_NAME, isp);
	अगर (status < 0) अणु
		dev_dbg(&i2c->dev, "can't get IRQ %d, err %d\n",
				i2c->irq, status);
		जाओ fail;
	पूर्ण

	isp->phy.dev = &i2c->dev;
	isp->phy.label = DRIVER_NAME;
	isp->phy.set_घातer = isp1301_set_घातer;

	isp->phy.otg->usb_phy = &isp->phy;
	isp->phy.otg->set_host = isp1301_set_host;
	isp->phy.otg->set_peripheral = isp1301_set_peripheral;
	isp->phy.otg->start_srp = isp1301_start_srp;
	isp->phy.otg->start_hnp = isp1301_start_hnp;

	enable_vbus_draw(isp, 0);
	घातer_करोwn(isp);
	the_transceiver = isp;

#अगर_घोषित	CONFIG_USB_OTG
	update_otg1(isp, isp1301_get_u8(isp, ISP1301_INTERRUPT_SOURCE));
	update_otg2(isp, isp1301_get_u8(isp, ISP1301_OTG_STATUS));
#पूर्ण_अगर

	dump_regs(isp, __func__);

#अगर_घोषित	VERBOSE
	mod_समयr(&isp->समयr, jअगरfies + TIMER_JIFFIES);
	dev_dbg(&i2c->dev, "scheduled timer, %d min\n", TIMER_MINUTES);
#पूर्ण_अगर

	status = usb_add_phy(&isp->phy, USB_PHY_TYPE_USB2);
	अगर (status < 0)
		dev_err(&i2c->dev, "can't register transceiver, %d\n",
			status);

	वापस 0;

fail:
	kमुक्त(isp->phy.otg);
	kमुक्त(isp);
	वापस -ENODEV;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id isp1301_id[] = अणु
	अणु "isp1301_omap", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, isp1301_id);

अटल काष्ठा i2c_driver isp1301_driver = अणु
	.driver = अणु
		.name	= "isp1301_omap",
	पूर्ण,
	.probe		= isp1301_probe,
	.हटाओ		= isp1301_हटाओ,
	.id_table	= isp1301_id,
पूर्ण;

/*-------------------------------------------------------------------------*/

अटल पूर्णांक __init isp_init(व्योम)
अणु
	वापस i2c_add_driver(&isp1301_driver);
पूर्ण
subsys_initcall(isp_init);

अटल व्योम __निकास isp_निकास(व्योम)
अणु
	अगर (the_transceiver)
		usb_हटाओ_phy(&the_transceiver->phy);
	i2c_del_driver(&isp1301_driver);
पूर्ण
module_निकास(isp_निकास);

