<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2007,2008 Freescale semiconductor, Inc.
 *
 * Author: Li Yang <LeoLi@मुक्तscale.com>
 *         Jerry Huang <Chang-Ming.Huang@मुक्तscale.com>
 *
 * Initialization based on code from Shlomi Gridish.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/समयr.h>
#समावेश <linux/usb.h>
#समावेश <linux/device.h>
#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/समय.स>
#समावेश <linux/fsl_devices.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/unaligned.h>

#समावेश "phy-fsl-usb.h"

#अगर_घोषित VERBOSE
#घोषणा VDBG(fmt, args...) pr_debug("[%s]  " fmt, \
				 __func__, ## args)
#अन्यथा
#घोषणा VDBG(stuff...)	करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

#घोषणा DRIVER_VERSION "Rev. 1.55"
#घोषणा DRIVER_AUTHOR "Jerry Huang/Li Yang"
#घोषणा DRIVER_DESC "Freescale USB OTG Transceiver Driver"
#घोषणा DRIVER_INFO DRIVER_DESC " " DRIVER_VERSION

अटल स्थिर अक्षर driver_name[] = "fsl-usb2-otg";

स्थिर pm_message_t otg_suspend_state = अणु
	.event = 1,
पूर्ण;

#घोषणा HA_DATA_PULSE

अटल काष्ठा usb_dr_mmap *usb_dr_regs;
अटल काष्ठा fsl_otg *fsl_otg_dev;
अटल पूर्णांक srp_रुको_करोne;

/* FSM समयrs */
काष्ठा fsl_otg_समयr *a_रुको_vrise_पंचांगr, *a_रुको_bcon_पंचांगr, *a_aidl_bdis_पंचांगr,
	*b_ase0_brst_पंचांगr, *b_se0_srp_पंचांगr;

/* Driver specअगरic समयrs */
काष्ठा fsl_otg_समयr *b_data_pulse_पंचांगr, *b_vbus_pulse_पंचांगr, *b_srp_fail_पंचांगr,
	*b_srp_रुको_पंचांगr, *a_रुको_क्रमागत_पंचांगr;

अटल काष्ठा list_head active_समयrs;

अटल स्थिर काष्ठा fsl_otg_config fsl_otg_initdata = अणु
	.otg_port = 1,
पूर्ण;

#अगर_घोषित CONFIG_PPC32
अटल u32 _fsl_पढ़ोl_be(स्थिर अचिन्हित __iomem *p)
अणु
	वापस in_be32(p);
पूर्ण

अटल u32 _fsl_पढ़ोl_le(स्थिर अचिन्हित __iomem *p)
अणु
	वापस in_le32(p);
पूर्ण

अटल व्योम _fsl_ग_लिखोl_be(u32 v, अचिन्हित __iomem *p)
अणु
	out_be32(p, v);
पूर्ण

अटल व्योम _fsl_ग_लिखोl_le(u32 v, अचिन्हित __iomem *p)
अणु
	out_le32(p, v);
पूर्ण

अटल u32 (*_fsl_पढ़ोl)(स्थिर अचिन्हित __iomem *p);
अटल व्योम (*_fsl_ग_लिखोl)(u32 v, अचिन्हित __iomem *p);

#घोषणा fsl_पढ़ोl(p)		(*_fsl_पढ़ोl)((p))
#घोषणा fsl_ग_लिखोl(v, p)	(*_fsl_ग_लिखोl)((v), (p))

#अन्यथा
#घोषणा fsl_पढ़ोl(addr)		पढ़ोl(addr)
#घोषणा fsl_ग_लिखोl(val, addr)	ग_लिखोl(val, addr)
#पूर्ण_अगर /* CONFIG_PPC32 */

पूर्णांक ग_लिखो_ulpi(u8 addr, u8 data)
अणु
	u32 temp;

	temp = 0x60000000 | (addr << 16) | data;
	fsl_ग_लिखोl(temp, &usb_dr_regs->ulpiview);
	वापस 0;
पूर्ण

/* -------------------------------------------------------------*/
/* Operations that will be called from OTG Finite State Machine */

/* Charge vbus क्रम vbus pulsing in SRP */
व्योम fsl_otg_chrg_vbus(काष्ठा otg_fsm *fsm, पूर्णांक on)
अणु
	u32 पंचांगp;

	पंचांगp = fsl_पढ़ोl(&usb_dr_regs->otgsc) & ~OTGSC_INTSTS_MASK;

	अगर (on)
		/* stop disअक्षरging, start अक्षरging */
		पंचांगp = (पंचांगp & ~OTGSC_CTRL_VBUS_DISCHARGE) |
			OTGSC_CTRL_VBUS_CHARGE;
	अन्यथा
		/* stop अक्षरging */
		पंचांगp &= ~OTGSC_CTRL_VBUS_CHARGE;

	fsl_ग_लिखोl(पंचांगp, &usb_dr_regs->otgsc);
पूर्ण

/* Disअक्षरge vbus through a resistor to ground */
व्योम fsl_otg_dischrg_vbus(पूर्णांक on)
अणु
	u32 पंचांगp;

	पंचांगp = fsl_पढ़ोl(&usb_dr_regs->otgsc) & ~OTGSC_INTSTS_MASK;

	अगर (on)
		/* stop अक्षरging, start disअक्षरging */
		पंचांगp = (पंचांगp & ~OTGSC_CTRL_VBUS_CHARGE) |
			OTGSC_CTRL_VBUS_DISCHARGE;
	अन्यथा
		/* stop disअक्षरging */
		पंचांगp &= ~OTGSC_CTRL_VBUS_DISCHARGE;

	fsl_ग_लिखोl(पंचांगp, &usb_dr_regs->otgsc);
पूर्ण

/* A-device driver vbus, controlled through PP bit in PORTSC */
व्योम fsl_otg_drv_vbus(काष्ठा otg_fsm *fsm, पूर्णांक on)
अणु
	u32 पंचांगp;

	अगर (on) अणु
		पंचांगp = fsl_पढ़ोl(&usb_dr_regs->portsc) & ~PORTSC_W1C_BITS;
		fsl_ग_लिखोl(पंचांगp | PORTSC_PORT_POWER, &usb_dr_regs->portsc);
	पूर्ण अन्यथा अणु
		पंचांगp = fsl_पढ़ोl(&usb_dr_regs->portsc) &
		      ~PORTSC_W1C_BITS & ~PORTSC_PORT_POWER;
		fsl_ग_लिखोl(पंचांगp, &usb_dr_regs->portsc);
	पूर्ण
पूर्ण

/*
 * Pull-up D+, संकेतling connect by periperal. Also used in
 * data-line pulsing in SRP
 */
व्योम fsl_otg_loc_conn(काष्ठा otg_fsm *fsm, पूर्णांक on)
अणु
	u32 पंचांगp;

	पंचांगp = fsl_पढ़ोl(&usb_dr_regs->otgsc) & ~OTGSC_INTSTS_MASK;

	अगर (on)
		पंचांगp |= OTGSC_CTRL_DATA_PULSING;
	अन्यथा
		पंचांगp &= ~OTGSC_CTRL_DATA_PULSING;

	fsl_ग_लिखोl(पंचांगp, &usb_dr_regs->otgsc);
पूर्ण

/*
 * Generate SOF by host.  This is controlled through suspend/resume the
 * port.  In host mode, controller will स्वतःmatically send SOF.
 * Suspend will block the data on the port.
 */
व्योम fsl_otg_loc_sof(काष्ठा otg_fsm *fsm, पूर्णांक on)
अणु
	u32 पंचांगp;

	पंचांगp = fsl_पढ़ोl(&fsl_otg_dev->dr_mem_map->portsc) & ~PORTSC_W1C_BITS;
	अगर (on)
		पंचांगp |= PORTSC_PORT_FORCE_RESUME;
	अन्यथा
		पंचांगp |= PORTSC_PORT_SUSPEND;

	fsl_ग_लिखोl(पंचांगp, &fsl_otg_dev->dr_mem_map->portsc);

पूर्ण

/* Start SRP pulsing by data-line pulsing, followed with v-bus pulsing. */
व्योम fsl_otg_start_pulse(काष्ठा otg_fsm *fsm)
अणु
	u32 पंचांगp;

	srp_रुको_करोne = 0;
#अगर_घोषित HA_DATA_PULSE
	पंचांगp = fsl_पढ़ोl(&usb_dr_regs->otgsc) & ~OTGSC_INTSTS_MASK;
	पंचांगp |= OTGSC_HA_DATA_PULSE;
	fsl_ग_लिखोl(पंचांगp, &usb_dr_regs->otgsc);
#अन्यथा
	fsl_otg_loc_conn(1);
#पूर्ण_अगर

	fsl_otg_add_समयr(fsm, b_data_pulse_पंचांगr);
पूर्ण

व्योम b_data_pulse_end(अचिन्हित दीर्घ foo)
अणु
#अगर_घोषित HA_DATA_PULSE
#अन्यथा
	fsl_otg_loc_conn(0);
#पूर्ण_अगर

	/* Do VBUS pulse after data pulse */
	fsl_otg_pulse_vbus();
पूर्ण

व्योम fsl_otg_pulse_vbus(व्योम)
अणु
	srp_रुको_करोne = 0;
	fsl_otg_chrg_vbus(&fsl_otg_dev->fsm, 1);
	/* start the समयr to end vbus अक्षरge */
	fsl_otg_add_समयr(&fsl_otg_dev->fsm, b_vbus_pulse_पंचांगr);
पूर्ण

व्योम b_vbus_pulse_end(अचिन्हित दीर्घ foo)
अणु
	fsl_otg_chrg_vbus(&fsl_otg_dev->fsm, 0);

	/*
	 * As USB3300 using the same a_sess_vld and b_sess_vld voltage
	 * we need to disअक्षरge the bus क्रम a जबतक to distinguish
	 * residual voltage of vbus pulsing and A device pull up
	 */
	fsl_otg_dischrg_vbus(1);
	fsl_otg_add_समयr(&fsl_otg_dev->fsm, b_srp_रुको_पंचांगr);
पूर्ण

व्योम b_srp_end(अचिन्हित दीर्घ foo)
अणु
	fsl_otg_dischrg_vbus(0);
	srp_रुको_करोne = 1;

	अगर ((fsl_otg_dev->phy.otg->state == OTG_STATE_B_SRP_INIT) &&
	    fsl_otg_dev->fsm.b_sess_vld)
		fsl_otg_dev->fsm.b_srp_करोne = 1;
पूर्ण

/*
 * Workaround क्रम a_host suspending too fast.  When a_bus_req=0,
 * a_host will start by SRP.  It needs to set b_hnp_enable beक्रमe
 * actually suspending to start HNP
 */
व्योम a_रुको_क्रमागत(अचिन्हित दीर्घ foo)
अणु
	VDBG("a_wait_enum timeout\n");
	अगर (!fsl_otg_dev->phy.otg->host->b_hnp_enable)
		fsl_otg_add_समयr(&fsl_otg_dev->fsm, a_रुको_क्रमागत_पंचांगr);
	अन्यथा
		otg_statemachine(&fsl_otg_dev->fsm);
पूर्ण

/* The समयout callback function to set समय out bit */
व्योम set_पंचांगout(अचिन्हित दीर्घ indicator)
अणु
	*(पूर्णांक *)indicator = 1;
पूर्ण

/* Initialize समयrs */
पूर्णांक fsl_otg_init_समयrs(काष्ठा otg_fsm *fsm)
अणु
	/* FSM used समयrs */
	a_रुको_vrise_पंचांगr = otg_समयr_initializer(&set_पंचांगout, TA_WAIT_VRISE,
				(अचिन्हित दीर्घ)&fsm->a_रुको_vrise_पंचांगout);
	अगर (!a_रुको_vrise_पंचांगr)
		वापस -ENOMEM;

	a_रुको_bcon_पंचांगr = otg_समयr_initializer(&set_पंचांगout, TA_WAIT_BCON,
				(अचिन्हित दीर्घ)&fsm->a_रुको_bcon_पंचांगout);
	अगर (!a_रुको_bcon_पंचांगr)
		वापस -ENOMEM;

	a_aidl_bdis_पंचांगr = otg_समयr_initializer(&set_पंचांगout, TA_AIDL_BDIS,
				(अचिन्हित दीर्घ)&fsm->a_aidl_bdis_पंचांगout);
	अगर (!a_aidl_bdis_पंचांगr)
		वापस -ENOMEM;

	b_ase0_brst_पंचांगr = otg_समयr_initializer(&set_पंचांगout, TB_ASE0_BRST,
				(अचिन्हित दीर्घ)&fsm->b_ase0_brst_पंचांगout);
	अगर (!b_ase0_brst_पंचांगr)
		वापस -ENOMEM;

	b_se0_srp_पंचांगr = otg_समयr_initializer(&set_पंचांगout, TB_SE0_SRP,
				(अचिन्हित दीर्घ)&fsm->b_se0_srp);
	अगर (!b_se0_srp_पंचांगr)
		वापस -ENOMEM;

	b_srp_fail_पंचांगr = otg_समयr_initializer(&set_पंचांगout, TB_SRP_FAIL,
				(अचिन्हित दीर्घ)&fsm->b_srp_करोne);
	अगर (!b_srp_fail_पंचांगr)
		वापस -ENOMEM;

	a_रुको_क्रमागत_पंचांगr = otg_समयr_initializer(&a_रुको_क्रमागत, 10,
				(अचिन्हित दीर्घ)&fsm);
	अगर (!a_रुको_क्रमागत_पंचांगr)
		वापस -ENOMEM;

	/* device driver used समयrs */
	b_srp_रुको_पंचांगr = otg_समयr_initializer(&b_srp_end, TB_SRP_WAIT, 0);
	अगर (!b_srp_रुको_पंचांगr)
		वापस -ENOMEM;

	b_data_pulse_पंचांगr = otg_समयr_initializer(&b_data_pulse_end,
				TB_DATA_PLS, 0);
	अगर (!b_data_pulse_पंचांगr)
		वापस -ENOMEM;

	b_vbus_pulse_पंचांगr = otg_समयr_initializer(&b_vbus_pulse_end,
				TB_VBUS_PLS, 0);
	अगर (!b_vbus_pulse_पंचांगr)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

/* Uninitialize समयrs */
व्योम fsl_otg_uninit_समयrs(व्योम)
अणु
	/* FSM used समयrs */
	kमुक्त(a_रुको_vrise_पंचांगr);
	kमुक्त(a_रुको_bcon_पंचांगr);
	kमुक्त(a_aidl_bdis_पंचांगr);
	kमुक्त(b_ase0_brst_पंचांगr);
	kमुक्त(b_se0_srp_पंचांगr);
	kमुक्त(b_srp_fail_पंचांगr);
	kमुक्त(a_रुको_क्रमागत_पंचांगr);

	/* device driver used समयrs */
	kमुक्त(b_srp_रुको_पंचांगr);
	kमुक्त(b_data_pulse_पंचांगr);
	kमुक्त(b_vbus_pulse_पंचांगr);
पूर्ण

अटल काष्ठा fsl_otg_समयr *fsl_otg_get_समयr(क्रमागत otg_fsm_समयr t)
अणु
	काष्ठा fsl_otg_समयr *समयr;

	/* REVISIT: use array of poपूर्णांकers to समयrs instead */
	चयन (t) अणु
	हाल A_WAIT_VRISE:
		समयr = a_रुको_vrise_पंचांगr;
		अवरोध;
	हाल A_WAIT_BCON:
		समयr = a_रुको_vrise_पंचांगr;
		अवरोध;
	हाल A_AIDL_BDIS:
		समयr = a_रुको_vrise_पंचांगr;
		अवरोध;
	हाल B_ASE0_BRST:
		समयr = a_रुको_vrise_पंचांगr;
		अवरोध;
	हाल B_SE0_SRP:
		समयr = a_रुको_vrise_पंचांगr;
		अवरोध;
	हाल B_SRP_FAIL:
		समयr = a_रुको_vrise_पंचांगr;
		अवरोध;
	हाल A_WAIT_ENUM:
		समयr = a_रुको_vrise_पंचांगr;
		अवरोध;
	शेष:
		समयr = शून्य;
	पूर्ण

	वापस समयr;
पूर्ण

/* Add समयr to समयr list */
व्योम fsl_otg_add_समयr(काष्ठा otg_fsm *fsm, व्योम *gसमयr)
अणु
	काष्ठा fsl_otg_समयr *समयr = gसमयr;
	काष्ठा fsl_otg_समयr *पंचांगp_समयr;

	/*
	 * Check अगर the समयr is alपढ़ोy in the active list,
	 * अगर so update समयr count
	 */
	list_क्रम_each_entry(पंचांगp_समयr, &active_समयrs, list)
	    अगर (पंचांगp_समयr == समयr) अणु
		समयr->count = समयr->expires;
		वापस;
	पूर्ण
	समयr->count = समयr->expires;
	list_add_tail(&समयr->list, &active_समयrs);
पूर्ण

अटल व्योम fsl_otg_fsm_add_समयr(काष्ठा otg_fsm *fsm, क्रमागत otg_fsm_समयr t)
अणु
	काष्ठा fsl_otg_समयr *समयr;

	समयr = fsl_otg_get_समयr(t);
	अगर (!समयr)
		वापस;

	fsl_otg_add_समयr(fsm, समयr);
पूर्ण

/* Remove समयr from the समयr list; clear समयout status */
व्योम fsl_otg_del_समयr(काष्ठा otg_fsm *fsm, व्योम *gसमयr)
अणु
	काष्ठा fsl_otg_समयr *समयr = gसमयr;
	काष्ठा fsl_otg_समयr *पंचांगp_समयr, *del_पंचांगp;

	list_क्रम_each_entry_safe(पंचांगp_समयr, del_पंचांगp, &active_समयrs, list)
		अगर (पंचांगp_समयr == समयr)
			list_del(&समयr->list);
पूर्ण

अटल व्योम fsl_otg_fsm_del_समयr(काष्ठा otg_fsm *fsm, क्रमागत otg_fsm_समयr t)
अणु
	काष्ठा fsl_otg_समयr *समयr;

	समयr = fsl_otg_get_समयr(t);
	अगर (!समयr)
		वापस;

	fsl_otg_del_समयr(fsm, समयr);
पूर्ण

/* Reset controller, not reset the bus */
व्योम otg_reset_controller(व्योम)
अणु
	u32 command;

	command = fsl_पढ़ोl(&usb_dr_regs->usbcmd);
	command |= (1 << 1);
	fsl_ग_लिखोl(command, &usb_dr_regs->usbcmd);
	जबतक (fsl_पढ़ोl(&usb_dr_regs->usbcmd) & (1 << 1))
		;
पूर्ण

/* Call suspend/resume routines in host driver */
पूर्णांक fsl_otg_start_host(काष्ठा otg_fsm *fsm, पूर्णांक on)
अणु
	काष्ठा usb_otg *otg = fsm->otg;
	काष्ठा device *dev;
	काष्ठा fsl_otg *otg_dev =
		container_of(otg->usb_phy, काष्ठा fsl_otg, phy);
	u32 retval = 0;

	अगर (!otg->host)
		वापस -ENODEV;
	dev = otg->host->controller;

	/*
	 * Update a_vbus_vld state as a_vbus_vld पूर्णांक is disabled
	 * in device mode
	 */
	fsm->a_vbus_vld =
		!!(fsl_पढ़ोl(&usb_dr_regs->otgsc) & OTGSC_STS_A_VBUS_VALID);
	अगर (on) अणु
		/* start fsl usb host controller */
		अगर (otg_dev->host_working)
			जाओ end;
		अन्यथा अणु
			otg_reset_controller();
			VDBG("host on......\n");
			अगर (dev->driver->pm && dev->driver->pm->resume) अणु
				retval = dev->driver->pm->resume(dev);
				अगर (fsm->id) अणु
					/* शेष-b */
					fsl_otg_drv_vbus(fsm, 1);
					/*
					 * Workaround: b_host can't driver
					 * vbus, but PP in PORTSC needs to
					 * be 1 क्रम host to work.
					 * So we set drv_vbus bit in
					 * transceiver to 0 thru ULPI.
					 */
					ग_लिखो_ulpi(0x0c, 0x20);
				पूर्ण
			पूर्ण

			otg_dev->host_working = 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* stop fsl usb host controller */
		अगर (!otg_dev->host_working)
			जाओ end;
		अन्यथा अणु
			VDBG("host off......\n");
			अगर (dev && dev->driver) अणु
				अगर (dev->driver->pm && dev->driver->pm->suspend)
					retval = dev->driver->pm->suspend(dev);
				अगर (fsm->id)
					/* शेष-b */
					fsl_otg_drv_vbus(fsm, 0);
			पूर्ण
			otg_dev->host_working = 0;
		पूर्ण
	पूर्ण
end:
	वापस retval;
पूर्ण

/*
 * Call suspend and resume function in udc driver
 * to stop and start udc driver.
 */
पूर्णांक fsl_otg_start_gadget(काष्ठा otg_fsm *fsm, पूर्णांक on)
अणु
	काष्ठा usb_otg *otg = fsm->otg;
	काष्ठा device *dev;

	अगर (!otg->gadget || !otg->gadget->dev.parent)
		वापस -ENODEV;

	VDBG("gadget %s\n", on ? "on" : "off");
	dev = otg->gadget->dev.parent;

	अगर (on) अणु
		अगर (dev->driver->resume)
			dev->driver->resume(dev);
	पूर्ण अन्यथा अणु
		अगर (dev->driver->suspend)
			dev->driver->suspend(dev, otg_suspend_state);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Called by initialization code of host driver.  Register host controller
 * to the OTG.  Suspend host क्रम OTG role detection.
 */
अटल पूर्णांक fsl_otg_set_host(काष्ठा usb_otg *otg, काष्ठा usb_bus *host)
अणु
	काष्ठा fsl_otg *otg_dev;

	अगर (!otg)
		वापस -ENODEV;

	otg_dev = container_of(otg->usb_phy, काष्ठा fsl_otg, phy);
	अगर (otg_dev != fsl_otg_dev)
		वापस -ENODEV;

	otg->host = host;

	otg_dev->fsm.a_bus_drop = 0;
	otg_dev->fsm.a_bus_req = 1;

	अगर (host) अणु
		VDBG("host off......\n");

		otg->host->otg_port = fsl_otg_initdata.otg_port;
		otg->host->is_b_host = otg_dev->fsm.id;
		/*
		 * must leave समय क्रम hub_wq to finish its thing
		 * beक्रमe yanking the host driver out from under it,
		 * so suspend the host after a लघु delay.
		 */
		otg_dev->host_working = 1;
		schedule_delayed_work(&otg_dev->otg_event, 100);
		वापस 0;
	पूर्ण अन्यथा अणु
		/* host driver going away */
		अगर (!(fsl_पढ़ोl(&otg_dev->dr_mem_map->otgsc) &
		      OTGSC_STS_USB_ID)) अणु
			/* Mini-A cable connected */
			काष्ठा otg_fsm *fsm = &otg_dev->fsm;

			otg->state = OTG_STATE_UNDEFINED;
			fsm->protocol = PROTO_UNDEF;
		पूर्ण
	पूर्ण

	otg_dev->host_working = 0;

	otg_statemachine(&otg_dev->fsm);

	वापस 0;
पूर्ण

/* Called by initialization code of udc.  Register udc to OTG. */
अटल पूर्णांक fsl_otg_set_peripheral(काष्ठा usb_otg *otg,
					काष्ठा usb_gadget *gadget)
अणु
	काष्ठा fsl_otg *otg_dev;

	अगर (!otg)
		वापस -ENODEV;

	otg_dev = container_of(otg->usb_phy, काष्ठा fsl_otg, phy);
	VDBG("otg_dev 0x%x\n", (पूर्णांक)otg_dev);
	VDBG("fsl_otg_dev 0x%x\n", (पूर्णांक)fsl_otg_dev);
	अगर (otg_dev != fsl_otg_dev)
		वापस -ENODEV;

	अगर (!gadget) अणु
		अगर (!otg->शेष_a)
			otg->gadget->ops->vbus_draw(otg->gadget, 0);
		usb_gadget_vbus_disconnect(otg->gadget);
		otg->gadget = 0;
		otg_dev->fsm.b_bus_req = 0;
		otg_statemachine(&otg_dev->fsm);
		वापस 0;
	पूर्ण

	otg->gadget = gadget;
	otg->gadget->is_a_peripheral = !otg_dev->fsm.id;

	otg_dev->fsm.b_bus_req = 1;

	/* start the gadget right away अगर the ID pin says Mini-B */
	pr_debug("ID pin=%d\n", otg_dev->fsm.id);
	अगर (otg_dev->fsm.id == 1) अणु
		fsl_otg_start_host(&otg_dev->fsm, 0);
		otg_drv_vbus(&otg_dev->fsm, 0);
		fsl_otg_start_gadget(&otg_dev->fsm, 1);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Delayed pin detect पूर्णांकerrupt processing.
 *
 * When the Mini-A cable is disconnected from the board,
 * the pin-detect पूर्णांकerrupt happens beक्रमe the disconnect
 * पूर्णांकerrupts क्रम the connected device(s).  In order to
 * process the disconnect पूर्णांकerrupt(s) prior to चयनing
 * roles, the pin-detect पूर्णांकerrupts are delayed, and handled
 * by this routine.
 */
अटल व्योम fsl_otg_event(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fsl_otg *og = container_of(work, काष्ठा fsl_otg, otg_event.work);
	काष्ठा otg_fsm *fsm = &og->fsm;

	अगर (fsm->id) अणु		/* चयन to gadget */
		fsl_otg_start_host(fsm, 0);
		otg_drv_vbus(fsm, 0);
		fsl_otg_start_gadget(fsm, 1);
	पूर्ण
पूर्ण

/* B-device start SRP */
अटल पूर्णांक fsl_otg_start_srp(काष्ठा usb_otg *otg)
अणु
	काष्ठा fsl_otg *otg_dev;

	अगर (!otg || otg->state != OTG_STATE_B_IDLE)
		वापस -ENODEV;

	otg_dev = container_of(otg->usb_phy, काष्ठा fsl_otg, phy);
	अगर (otg_dev != fsl_otg_dev)
		वापस -ENODEV;

	otg_dev->fsm.b_bus_req = 1;
	otg_statemachine(&otg_dev->fsm);

	वापस 0;
पूर्ण

/* A_host suspend will call this function to start hnp */
अटल पूर्णांक fsl_otg_start_hnp(काष्ठा usb_otg *otg)
अणु
	काष्ठा fsl_otg *otg_dev;

	अगर (!otg)
		वापस -ENODEV;

	otg_dev = container_of(otg->usb_phy, काष्ठा fsl_otg, phy);
	अगर (otg_dev != fsl_otg_dev)
		वापस -ENODEV;

	pr_debug("start_hnp...\n");

	/* clear a_bus_req to enter a_suspend state */
	otg_dev->fsm.a_bus_req = 0;
	otg_statemachine(&otg_dev->fsm);

	वापस 0;
पूर्ण

/*
 * Interrupt handler.  OTG/host/peripheral share the same पूर्णांक line.
 * OTG driver clears OTGSC पूर्णांकerrupts and leaves USB पूर्णांकerrupts
 * पूर्णांकact.  It needs to have knowledge of some USB पूर्णांकerrupts
 * such as port change.
 */
irqवापस_t fsl_otg_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा otg_fsm *fsm = &((काष्ठा fsl_otg *)dev_id)->fsm;
	काष्ठा usb_otg *otg = ((काष्ठा fsl_otg *)dev_id)->phy.otg;
	u32 otg_पूर्णांक_src, otg_sc;

	otg_sc = fsl_पढ़ोl(&usb_dr_regs->otgsc);
	otg_पूर्णांक_src = otg_sc & OTGSC_INTSTS_MASK & (otg_sc >> 8);

	/* Only clear otg पूर्णांकerrupts */
	fsl_ग_लिखोl(otg_sc, &usb_dr_regs->otgsc);

	/*FIXME: ID change not generate when init to 0 */
	fsm->id = (otg_sc & OTGSC_STS_USB_ID) ? 1 : 0;
	otg->शेष_a = (fsm->id == 0);

	/* process OTG पूर्णांकerrupts */
	अगर (otg_पूर्णांक_src) अणु
		अगर (otg_पूर्णांक_src & OTGSC_INTSTS_USB_ID) अणु
			fsm->id = (otg_sc & OTGSC_STS_USB_ID) ? 1 : 0;
			otg->शेष_a = (fsm->id == 0);
			/* clear conn inक्रमmation */
			अगर (fsm->id)
				fsm->b_conn = 0;
			अन्यथा
				fsm->a_conn = 0;

			अगर (otg->host)
				otg->host->is_b_host = fsm->id;
			अगर (otg->gadget)
				otg->gadget->is_a_peripheral = !fsm->id;
			VDBG("ID int (ID is %d)\n", fsm->id);

			अगर (fsm->id) अणु	/* चयन to gadget */
				schedule_delayed_work(
					&((काष्ठा fsl_otg *)dev_id)->otg_event,
					100);
			पूर्ण अन्यथा अणु	/* चयन to host */
				cancel_delayed_work(&
						    ((काष्ठा fsl_otg *)dev_id)->
						    otg_event);
				fsl_otg_start_gadget(fsm, 0);
				otg_drv_vbus(fsm, 1);
				fsl_otg_start_host(fsm, 1);
			पूर्ण
			वापस IRQ_HANDLED;
		पूर्ण
	पूर्ण
	वापस IRQ_NONE;
पूर्ण

अटल काष्ठा otg_fsm_ops fsl_otg_ops = अणु
	.chrg_vbus = fsl_otg_chrg_vbus,
	.drv_vbus = fsl_otg_drv_vbus,
	.loc_conn = fsl_otg_loc_conn,
	.loc_sof = fsl_otg_loc_sof,
	.start_pulse = fsl_otg_start_pulse,

	.add_समयr = fsl_otg_fsm_add_समयr,
	.del_समयr = fsl_otg_fsm_del_समयr,

	.start_host = fsl_otg_start_host,
	.start_gadget = fsl_otg_start_gadget,
पूर्ण;

/* Initialize the global variable fsl_otg_dev and request IRQ क्रम OTG */
अटल पूर्णांक fsl_otg_conf(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fsl_otg *fsl_otg_tc;
	पूर्णांक status;

	अगर (fsl_otg_dev)
		वापस 0;

	/* allocate space to fsl otg device */
	fsl_otg_tc = kzalloc(माप(काष्ठा fsl_otg), GFP_KERNEL);
	अगर (!fsl_otg_tc)
		वापस -ENOMEM;

	fsl_otg_tc->phy.otg = kzalloc(माप(काष्ठा usb_otg), GFP_KERNEL);
	अगर (!fsl_otg_tc->phy.otg) अणु
		kमुक्त(fsl_otg_tc);
		वापस -ENOMEM;
	पूर्ण

	INIT_DELAYED_WORK(&fsl_otg_tc->otg_event, fsl_otg_event);

	INIT_LIST_HEAD(&active_समयrs);
	status = fsl_otg_init_समयrs(&fsl_otg_tc->fsm);
	अगर (status) अणु
		pr_info("Couldn't init OTG timers\n");
		जाओ err;
	पूर्ण
	mutex_init(&fsl_otg_tc->fsm.lock);

	/* Set OTG state machine operations */
	fsl_otg_tc->fsm.ops = &fsl_otg_ops;

	/* initialize the otg काष्ठाure */
	fsl_otg_tc->phy.label = DRIVER_DESC;
	fsl_otg_tc->phy.dev = &pdev->dev;

	fsl_otg_tc->phy.otg->usb_phy = &fsl_otg_tc->phy;
	fsl_otg_tc->phy.otg->set_host = fsl_otg_set_host;
	fsl_otg_tc->phy.otg->set_peripheral = fsl_otg_set_peripheral;
	fsl_otg_tc->phy.otg->start_hnp = fsl_otg_start_hnp;
	fsl_otg_tc->phy.otg->start_srp = fsl_otg_start_srp;

	fsl_otg_dev = fsl_otg_tc;

	/* Store the otg transceiver */
	status = usb_add_phy(&fsl_otg_tc->phy, USB_PHY_TYPE_USB2);
	अगर (status) अणु
		pr_warn(FSL_OTG_NAME ": unable to register OTG transceiver.\n");
		जाओ err;
	पूर्ण

	वापस 0;
err:
	fsl_otg_uninit_समयrs();
	kमुक्त(fsl_otg_tc->phy.otg);
	kमुक्त(fsl_otg_tc);
	वापस status;
पूर्ण

/* OTG Initialization */
पूर्णांक usb_otg_start(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fsl_otg *p_otg;
	काष्ठा usb_phy *otg_trans = usb_get_phy(USB_PHY_TYPE_USB2);
	काष्ठा otg_fsm *fsm;
	पूर्णांक status;
	काष्ठा resource *res;
	u32 temp;
	काष्ठा fsl_usb2_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);

	p_otg = container_of(otg_trans, काष्ठा fsl_otg, phy);
	fsm = &p_otg->fsm;

	/* Initialize the state machine काष्ठाure with शेष values */
	SET_OTG_STATE(otg_trans, OTG_STATE_UNDEFINED);
	fsm->otg = p_otg->phy.otg;

	/* We करोn't require predefined MEM/IRQ resource index */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENXIO;

	/* We करोn't request_mem_region here to enable resource sharing
	 * with host/device */

	usb_dr_regs = ioremap(res->start, माप(काष्ठा usb_dr_mmap));
	p_otg->dr_mem_map = (काष्ठा usb_dr_mmap *)usb_dr_regs;
	pdata->regs = (व्योम *)usb_dr_regs;

	अगर (pdata->init && pdata->init(pdev) != 0)
		वापस -EINVAL;

#अगर_घोषित CONFIG_PPC32
	अगर (pdata->big_endian_mmio) अणु
		_fsl_पढ़ोl = _fsl_पढ़ोl_be;
		_fsl_ग_लिखोl = _fsl_ग_लिखोl_be;
	पूर्ण अन्यथा अणु
		_fsl_पढ़ोl = _fsl_पढ़ोl_le;
		_fsl_ग_लिखोl = _fsl_ग_लिखोl_le;
	पूर्ण
#पूर्ण_अगर

	/* request irq */
	p_otg->irq = platक्रमm_get_irq(pdev, 0);
	status = request_irq(p_otg->irq, fsl_otg_isr,
				IRQF_SHARED, driver_name, p_otg);
	अगर (status) अणु
		dev_dbg(p_otg->phy.dev, "can't get IRQ %d, error %d\n",
			p_otg->irq, status);
		iounmap(p_otg->dr_mem_map);
		kमुक्त(p_otg->phy.otg);
		kमुक्त(p_otg);
		वापस status;
	पूर्ण

	/* stop the controller */
	temp = fsl_पढ़ोl(&p_otg->dr_mem_map->usbcmd);
	temp &= ~USB_CMD_RUN_STOP;
	fsl_ग_लिखोl(temp, &p_otg->dr_mem_map->usbcmd);

	/* reset the controller */
	temp = fsl_पढ़ोl(&p_otg->dr_mem_map->usbcmd);
	temp |= USB_CMD_CTRL_RESET;
	fsl_ग_लिखोl(temp, &p_otg->dr_mem_map->usbcmd);

	/* रुको reset completed */
	जबतक (fsl_पढ़ोl(&p_otg->dr_mem_map->usbcmd) & USB_CMD_CTRL_RESET)
		;

	/* configure the VBUSHS as IDLE(both host and device) */
	temp = USB_MODE_STREAM_DISABLE | (pdata->es ? USB_MODE_ES : 0);
	fsl_ग_लिखोl(temp, &p_otg->dr_mem_map->usbmode);

	/* configure PHY पूर्णांकerface */
	temp = fsl_पढ़ोl(&p_otg->dr_mem_map->portsc);
	temp &= ~(PORTSC_PHY_TYPE_SEL | PORTSC_PTW);
	चयन (pdata->phy_mode) अणु
	हाल FSL_USB2_PHY_ULPI:
		temp |= PORTSC_PTS_ULPI;
		अवरोध;
	हाल FSL_USB2_PHY_UTMI_WIDE:
		temp |= PORTSC_PTW_16BIT;
		fallthrough;
	हाल FSL_USB2_PHY_UTMI:
		temp |= PORTSC_PTS_UTMI;
		fallthrough;
	शेष:
		अवरोध;
	पूर्ण
	fsl_ग_लिखोl(temp, &p_otg->dr_mem_map->portsc);

	अगर (pdata->have_sysअगर_regs) अणु
		/* configure control enable IO output, big endian रेजिस्टर */
		temp = __raw_पढ़ोl(&p_otg->dr_mem_map->control);
		temp |= USB_CTRL_IOENB;
		__raw_ग_लिखोl(temp, &p_otg->dr_mem_map->control);
	पूर्ण

	/* disable all पूर्णांकerrupt and clear all OTGSC status */
	temp = fsl_पढ़ोl(&p_otg->dr_mem_map->otgsc);
	temp &= ~OTGSC_INTERRUPT_ENABLE_BITS_MASK;
	temp |= OTGSC_INTERRUPT_STATUS_BITS_MASK | OTGSC_CTRL_VBUS_DISCHARGE;
	fsl_ग_लिखोl(temp, &p_otg->dr_mem_map->otgsc);

	/*
	 * The identअगरication (id) input is FALSE when a Mini-A plug is inserted
	 * in the devices Mini-AB receptacle. Otherwise, this input is TRUE.
	 * Also: record initial state of ID pin
	 */
	अगर (fsl_पढ़ोl(&p_otg->dr_mem_map->otgsc) & OTGSC_STS_USB_ID) अणु
		p_otg->phy.otg->state = OTG_STATE_UNDEFINED;
		p_otg->fsm.id = 1;
	पूर्ण अन्यथा अणु
		p_otg->phy.otg->state = OTG_STATE_A_IDLE;
		p_otg->fsm.id = 0;
	पूर्ण

	pr_debug("initial ID pin=%d\n", p_otg->fsm.id);

	/* enable OTG ID pin पूर्णांकerrupt */
	temp = fsl_पढ़ोl(&p_otg->dr_mem_map->otgsc);
	temp |= OTGSC_INTR_USB_ID_EN;
	temp &= ~(OTGSC_CTRL_VBUS_DISCHARGE | OTGSC_INTR_1MS_TIMER_EN);
	fsl_ग_लिखोl(temp, &p_otg->dr_mem_map->otgsc);

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_otg_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;

	अगर (!dev_get_platdata(&pdev->dev))
		वापस -ENODEV;

	/* configure the OTG */
	ret = fsl_otg_conf(pdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Couldn't configure OTG module\n");
		वापस ret;
	पूर्ण

	/* start OTG */
	ret = usb_otg_start(pdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Can't init FSL OTG device\n");
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक fsl_otg_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fsl_usb2_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);

	usb_हटाओ_phy(&fsl_otg_dev->phy);
	मुक्त_irq(fsl_otg_dev->irq, fsl_otg_dev);

	iounmap((व्योम *)usb_dr_regs);

	fsl_otg_uninit_समयrs();
	kमुक्त(fsl_otg_dev->phy.otg);
	kमुक्त(fsl_otg_dev);

	अगर (pdata->निकास)
		pdata->निकास(pdev);

	वापस 0;
पूर्ण

काष्ठा platक्रमm_driver fsl_otg_driver = अणु
	.probe = fsl_otg_probe,
	.हटाओ = fsl_otg_हटाओ,
	.driver = अणु
		.name = driver_name,
		.owner = THIS_MODULE,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(fsl_otg_driver);

MODULE_DESCRIPTION(DRIVER_INFO);
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_LICENSE("GPL");
