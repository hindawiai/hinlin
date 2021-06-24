<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause)
/*
 * core.c - DesignWare HS OTG Controller common routines
 *
 * Copyright (C) 2004-2013 Synopsys, Inc.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer,
 *    without modअगरication.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. The names of the above-listed copyright holders may not be used
 *    to enकरोrse or promote products derived from this software without
 *    specअगरic prior written permission.
 *
 * ALTERNATIVELY, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any
 * later version.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * The Core code provides basic services क्रम accessing and managing the
 * DWC_otg hardware. These services are used by both the Host Controller
 * Driver and the Peripheral Controller Driver.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/usb.h>

#समावेश <linux/usb/hcd.h>
#समावेश <linux/usb/ch11.h>

#समावेश "core.h"
#समावेश "hcd.h"

/**
 * dwc2_backup_global_रेजिस्टरs() - Backup global controller रेजिस्टरs.
 * When suspending usb bus, रेजिस्टरs needs to be backuped
 * अगर controller घातer is disabled once suspended.
 *
 * @hsotg: Programming view of the DWC_otg controller
 */
पूर्णांक dwc2_backup_global_रेजिस्टरs(काष्ठा dwc2_hsotg *hsotg)
अणु
	काष्ठा dwc2_gregs_backup *gr;

	dev_dbg(hsotg->dev, "%s\n", __func__);

	/* Backup global regs */
	gr = &hsotg->gr_backup;

	gr->gotgctl = dwc2_पढ़ोl(hsotg, GOTGCTL);
	gr->gपूर्णांकmsk = dwc2_पढ़ोl(hsotg, GINTMSK);
	gr->gahbcfg = dwc2_पढ़ोl(hsotg, GAHBCFG);
	gr->gusbcfg = dwc2_पढ़ोl(hsotg, GUSBCFG);
	gr->grxfsiz = dwc2_पढ़ोl(hsotg, GRXFSIZ);
	gr->gnptxfsiz = dwc2_पढ़ोl(hsotg, GNPTXFSIZ);
	gr->gdfअगरocfg = dwc2_पढ़ोl(hsotg, GDFIFOCFG);
	gr->pcgcctl1 = dwc2_पढ़ोl(hsotg, PCGCCTL1);
	gr->glpmcfg = dwc2_पढ़ोl(hsotg, GLPMCFG);
	gr->gi2cctl = dwc2_पढ़ोl(hsotg, GI2CCTL);
	gr->pcgcctl = dwc2_पढ़ोl(hsotg, PCGCTL);

	gr->valid = true;
	वापस 0;
पूर्ण

/**
 * dwc2_restore_global_रेजिस्टरs() - Restore controller global रेजिस्टरs.
 * When resuming usb bus, device रेजिस्टरs needs to be restored
 * अगर controller घातer were disabled.
 *
 * @hsotg: Programming view of the DWC_otg controller
 */
पूर्णांक dwc2_restore_global_रेजिस्टरs(काष्ठा dwc2_hsotg *hsotg)
अणु
	काष्ठा dwc2_gregs_backup *gr;

	dev_dbg(hsotg->dev, "%s\n", __func__);

	/* Restore global regs */
	gr = &hsotg->gr_backup;
	अगर (!gr->valid) अणु
		dev_err(hsotg->dev, "%s: no global registers to restore\n",
			__func__);
		वापस -EINVAL;
	पूर्ण
	gr->valid = false;

	dwc2_ग_लिखोl(hsotg, 0xffffffff, GINTSTS);
	dwc2_ग_लिखोl(hsotg, gr->gotgctl, GOTGCTL);
	dwc2_ग_लिखोl(hsotg, gr->gपूर्णांकmsk, GINTMSK);
	dwc2_ग_लिखोl(hsotg, gr->gusbcfg, GUSBCFG);
	dwc2_ग_लिखोl(hsotg, gr->gahbcfg, GAHBCFG);
	dwc2_ग_लिखोl(hsotg, gr->grxfsiz, GRXFSIZ);
	dwc2_ग_लिखोl(hsotg, gr->gnptxfsiz, GNPTXFSIZ);
	dwc2_ग_लिखोl(hsotg, gr->gdfअगरocfg, GDFIFOCFG);
	dwc2_ग_लिखोl(hsotg, gr->pcgcctl1, PCGCCTL1);
	dwc2_ग_लिखोl(hsotg, gr->glpmcfg, GLPMCFG);
	dwc2_ग_लिखोl(hsotg, gr->pcgcctl, PCGCTL);
	dwc2_ग_लिखोl(hsotg, gr->gi2cctl, GI2CCTL);

	वापस 0;
पूर्ण

/**
 * dwc2_निकास_partial_घातer_करोwn() - Exit controller from Partial Power Down.
 *
 * @hsotg: Programming view of the DWC_otg controller
 * @rem_wakeup: indicates whether resume is initiated by Reset.
 * @restore: Controller रेजिस्टरs need to be restored
 */
पूर्णांक dwc2_निकास_partial_घातer_करोwn(काष्ठा dwc2_hsotg *hsotg, पूर्णांक rem_wakeup,
				 bool restore)
अणु
	काष्ठा dwc2_gregs_backup *gr;

	gr = &hsotg->gr_backup;

	/*
	 * Restore host or device regisers with the same mode core enterted
	 * to partial घातer करोwn by checking "GOTGCTL_CURMODE_HOST" backup
	 * value of the "gotgctl" रेजिस्टर.
	 */
	अगर (gr->gotgctl & GOTGCTL_CURMODE_HOST)
		वापस dwc2_host_निकास_partial_घातer_करोwn(hsotg, rem_wakeup,
							 restore);
	अन्यथा
		वापस dwc2_gadget_निकास_partial_घातer_करोwn(hsotg, restore);
पूर्ण

/**
 * dwc2_enter_partial_घातer_करोwn() - Put controller in Partial Power Down.
 *
 * @hsotg: Programming view of the DWC_otg controller
 */
पूर्णांक dwc2_enter_partial_घातer_करोwn(काष्ठा dwc2_hsotg *hsotg)
अणु
	अगर (dwc2_is_host_mode(hsotg))
		वापस dwc2_host_enter_partial_घातer_करोwn(hsotg);
	अन्यथा
		वापस dwc2_gadget_enter_partial_घातer_करोwn(hsotg);
पूर्ण

/**
 * dwc2_restore_essential_regs() - Restore essiential regs of core.
 *
 * @hsotg: Programming view of the DWC_otg controller
 * @rmode: Restore mode, enabled in हाल of remote-wakeup.
 * @is_host: Host or device mode.
 */
अटल व्योम dwc2_restore_essential_regs(काष्ठा dwc2_hsotg *hsotg, पूर्णांक rmode,
					पूर्णांक is_host)
अणु
	u32 pcgcctl;
	काष्ठा dwc2_gregs_backup *gr;
	काष्ठा dwc2_dregs_backup *dr;
	काष्ठा dwc2_hregs_backup *hr;

	gr = &hsotg->gr_backup;
	dr = &hsotg->dr_backup;
	hr = &hsotg->hr_backup;

	dev_dbg(hsotg->dev, "%s: restoring essential regs\n", __func__);

	/* Load restore values क्रम [31:14] bits */
	pcgcctl = (gr->pcgcctl & 0xffffc000);
	/* If High Speed */
	अगर (is_host) अणु
		अगर (!(pcgcctl & PCGCTL_P2HD_PRT_SPD_MASK))
			pcgcctl |= BIT(17);
	पूर्ण अन्यथा अणु
		अगर (!(pcgcctl & PCGCTL_P2HD_DEV_ENUM_SPD_MASK))
			pcgcctl |= BIT(17);
	पूर्ण
	dwc2_ग_लिखोl(hsotg, pcgcctl, PCGCTL);

	/* Umnask global Interrupt in GAHBCFG and restore it */
	dwc2_ग_लिखोl(hsotg, gr->gahbcfg | GAHBCFG_GLBL_INTR_EN, GAHBCFG);

	/* Clear all pending पूर्णांकerupts */
	dwc2_ग_लिखोl(hsotg, 0xffffffff, GINTSTS);

	/* Unmask restore करोne पूर्णांकerrupt */
	dwc2_ग_लिखोl(hsotg, GINTSTS_RESTOREDONE, GINTMSK);

	/* Restore GUSBCFG and HCFG/DCFG */
	dwc2_ग_लिखोl(hsotg, gr->gusbcfg, GUSBCFG);

	अगर (is_host) अणु
		dwc2_ग_लिखोl(hsotg, hr->hcfg, HCFG);
		अगर (rmode)
			pcgcctl |= PCGCTL_RESTOREMODE;
		dwc2_ग_लिखोl(hsotg, pcgcctl, PCGCTL);
		udelay(10);

		pcgcctl |= PCGCTL_ESS_REG_RESTORED;
		dwc2_ग_लिखोl(hsotg, pcgcctl, PCGCTL);
		udelay(10);
	पूर्ण अन्यथा अणु
		dwc2_ग_लिखोl(hsotg, dr->dcfg, DCFG);
		अगर (!rmode)
			pcgcctl |= PCGCTL_RESTOREMODE | PCGCTL_RSTPDWNMODULE;
		dwc2_ग_लिखोl(hsotg, pcgcctl, PCGCTL);
		udelay(10);

		pcgcctl |= PCGCTL_ESS_REG_RESTORED;
		dwc2_ग_लिखोl(hsotg, pcgcctl, PCGCTL);
		udelay(10);
	पूर्ण
पूर्ण

/**
 * dwc2_hib_restore_common() - Common part of restore routine.
 *
 * @hsotg: Programming view of the DWC_otg controller
 * @rem_wakeup: Remote-wakeup, enabled in हाल of remote-wakeup.
 * @is_host: Host or device mode.
 */
व्योम dwc2_hib_restore_common(काष्ठा dwc2_hsotg *hsotg, पूर्णांक rem_wakeup,
			     पूर्णांक is_host)
अणु
	u32 gpwrdn;

	/* Switch-on voltage to the core */
	gpwrdn = dwc2_पढ़ोl(hsotg, GPWRDN);
	gpwrdn &= ~GPWRDN_PWRDNSWTCH;
	dwc2_ग_लिखोl(hsotg, gpwrdn, GPWRDN);
	udelay(10);

	/* Reset core */
	gpwrdn = dwc2_पढ़ोl(hsotg, GPWRDN);
	gpwrdn &= ~GPWRDN_PWRDNRSTN;
	dwc2_ग_लिखोl(hsotg, gpwrdn, GPWRDN);
	udelay(10);

	/* Enable restore from PMU */
	gpwrdn = dwc2_पढ़ोl(hsotg, GPWRDN);
	gpwrdn |= GPWRDN_RESTORE;
	dwc2_ग_लिखोl(hsotg, gpwrdn, GPWRDN);
	udelay(10);

	/* Disable Power Down Clamp */
	gpwrdn = dwc2_पढ़ोl(hsotg, GPWRDN);
	gpwrdn &= ~GPWRDN_PWRDNCLMP;
	dwc2_ग_लिखोl(hsotg, gpwrdn, GPWRDN);
	udelay(50);

	अगर (!is_host && rem_wakeup)
		udelay(70);

	/* Deनिश्चित reset core */
	gpwrdn = dwc2_पढ़ोl(hsotg, GPWRDN);
	gpwrdn |= GPWRDN_PWRDNRSTN;
	dwc2_ग_लिखोl(hsotg, gpwrdn, GPWRDN);
	udelay(10);

	/* Disable PMU पूर्णांकerrupt */
	gpwrdn = dwc2_पढ़ोl(hsotg, GPWRDN);
	gpwrdn &= ~GPWRDN_PMUINTSEL;
	dwc2_ग_लिखोl(hsotg, gpwrdn, GPWRDN);
	udelay(10);

	/* Set Restore Essential Regs bit in PCGCCTL रेजिस्टर */
	dwc2_restore_essential_regs(hsotg, rem_wakeup, is_host);

	/*
	 * Wait For Restore_करोne Interrupt. This mechanism of polling the
	 * पूर्णांकerrupt is पूर्णांकroduced to aव्योम any possible race conditions
	 */
	अगर (dwc2_hsotg_रुको_bit_set(hsotg, GINTSTS, GINTSTS_RESTOREDONE,
				    20000)) अणु
		dev_dbg(hsotg->dev,
			"%s: Restore Done wan't generated here\n",
			__func__);
	पूर्ण अन्यथा अणु
		dev_dbg(hsotg->dev, "restore done  generated here\n");

		/*
		 * To aव्योम restore करोne पूर्णांकerrupt storm after restore is
		 * generated clear GINTSTS_RESTOREDONE bit.
		 */
		dwc2_ग_लिखोl(hsotg, GINTSTS_RESTOREDONE, GINTSTS);
	पूर्ण
पूर्ण

/**
 * dwc2_रुको_क्रम_mode() - Waits क्रम the controller mode.
 * @hsotg:	Programming view of the DWC_otg controller.
 * @host_mode:	If true, रुकोs क्रम host mode, otherwise device mode.
 */
अटल व्योम dwc2_रुको_क्रम_mode(काष्ठा dwc2_hsotg *hsotg,
			       bool host_mode)
अणु
	kसमय_प्रकार start;
	kसमय_प्रकार end;
	अचिन्हित पूर्णांक समयout = 110;

	dev_vdbg(hsotg->dev, "Waiting for %s mode\n",
		 host_mode ? "host" : "device");

	start = kसमय_get();

	जबतक (1) अणु
		s64 ms;

		अगर (dwc2_is_host_mode(hsotg) == host_mode) अणु
			dev_vdbg(hsotg->dev, "%s mode set\n",
				 host_mode ? "Host" : "Device");
			अवरोध;
		पूर्ण

		end = kसमय_get();
		ms = kसमय_प्रकारo_ms(kसमय_sub(end, start));

		अगर (ms >= (s64)समयout) अणु
			dev_warn(hsotg->dev, "%s: Couldn't set %s mode\n",
				 __func__, host_mode ? "host" : "device");
			अवरोध;
		पूर्ण

		usleep_range(1000, 2000);
	पूर्ण
पूर्ण

/**
 * dwc2_iddig_filter_enabled() - Returns true अगर the IDDIG debounce
 * filter is enabled.
 *
 * @hsotg: Programming view of DWC_otg controller
 */
अटल bool dwc2_iddig_filter_enabled(काष्ठा dwc2_hsotg *hsotg)
अणु
	u32 gsnpsid;
	u32 ghwcfg4;

	अगर (!dwc2_hw_is_otg(hsotg))
		वापस false;

	/* Check अगर core configuration includes the IDDIG filter. */
	ghwcfg4 = dwc2_पढ़ोl(hsotg, GHWCFG4);
	अगर (!(ghwcfg4 & GHWCFG4_IDDIG_FILT_EN))
		वापस false;

	/*
	 * Check अगर the IDDIG debounce filter is bypassed. Available
	 * in core version >= 3.10a.
	 */
	gsnpsid = dwc2_पढ़ोl(hsotg, GSNPSID);
	अगर (gsnpsid >= DWC2_CORE_REV_3_10a) अणु
		u32 gotgctl = dwc2_पढ़ोl(hsotg, GOTGCTL);

		अगर (gotgctl & GOTGCTL_DBNCE_FLTR_BYPASS)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

/*
 * dwc2_enter_hibernation() - Common function to enter hibernation.
 *
 * @hsotg: Programming view of the DWC_otg controller
 * @is_host: True अगर core is in host mode.
 *
 * Return: 0 अगर successful, negative error code otherwise
 */
पूर्णांक dwc2_enter_hibernation(काष्ठा dwc2_hsotg *hsotg, पूर्णांक is_host)
अणु
	अगर (is_host)
		वापस dwc2_host_enter_hibernation(hsotg);
	अन्यथा
		वापस dwc2_gadget_enter_hibernation(hsotg);
पूर्ण

/*
 * dwc2_निकास_hibernation() - Common function to निकास from hibernation.
 *
 * @hsotg: Programming view of the DWC_otg controller
 * @rem_wakeup: Remote-wakeup, enabled in हाल of remote-wakeup.
 * @reset: Enabled in हाल of restore with reset.
 * @is_host: True अगर core is in host mode.
 *
 * Return: 0 अगर successful, negative error code otherwise
 */
पूर्णांक dwc2_निकास_hibernation(काष्ठा dwc2_hsotg *hsotg, पूर्णांक rem_wakeup,
			  पूर्णांक reset, पूर्णांक is_host)
अणु
	अगर (is_host)
		वापस dwc2_host_निकास_hibernation(hsotg, rem_wakeup, reset);
	अन्यथा
		वापस dwc2_gadget_निकास_hibernation(hsotg, rem_wakeup, reset);
पूर्ण

/*
 * Do core a soft reset of the core.  Be careful with this because it
 * resets all the पूर्णांकernal state machines of the core.
 */
पूर्णांक dwc2_core_reset(काष्ठा dwc2_hsotg *hsotg, bool skip_रुको)
अणु
	u32 greset;
	bool रुको_क्रम_host_mode = false;

	dev_vdbg(hsotg->dev, "%s()\n", __func__);

	/*
	 * If the current mode is host, either due to the क्रमce mode
	 * bit being set (which persists after core reset) or the
	 * connector id pin, a core soft reset will temporarily reset
	 * the mode to device. A delay from the IDDIG debounce filter
	 * will occur beक्रमe going back to host mode.
	 *
	 * Determine whether we will go back पूर्णांकo host mode after a
	 * reset and account क्रम this delay after the reset.
	 */
	अगर (dwc2_iddig_filter_enabled(hsotg)) अणु
		u32 gotgctl = dwc2_पढ़ोl(hsotg, GOTGCTL);
		u32 gusbcfg = dwc2_पढ़ोl(hsotg, GUSBCFG);

		अगर (!(gotgctl & GOTGCTL_CONID_B) ||
		    (gusbcfg & GUSBCFG_FORCEHOSTMODE)) अणु
			रुको_क्रम_host_mode = true;
		पूर्ण
	पूर्ण

	/* Core Soft Reset */
	greset = dwc2_पढ़ोl(hsotg, GRSTCTL);
	greset |= GRSTCTL_CSFTRST;
	dwc2_ग_लिखोl(hsotg, greset, GRSTCTL);

	अगर ((hsotg->hw_params.snpsid & DWC2_CORE_REV_MASK) <
		(DWC2_CORE_REV_4_20a & DWC2_CORE_REV_MASK)) अणु
		अगर (dwc2_hsotg_रुको_bit_clear(hsotg, GRSTCTL,
					      GRSTCTL_CSFTRST, 10000)) अणु
			dev_warn(hsotg->dev, "%s: HANG! Soft Reset timeout GRSTCTL_CSFTRST\n",
				 __func__);
			वापस -EBUSY;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (dwc2_hsotg_रुको_bit_set(hsotg, GRSTCTL,
					    GRSTCTL_CSFTRST_DONE, 10000)) अणु
			dev_warn(hsotg->dev, "%s: HANG! Soft Reset timeout GRSTCTL_CSFTRST_DONE\n",
				 __func__);
			वापस -EBUSY;
		पूर्ण
		greset = dwc2_पढ़ोl(hsotg, GRSTCTL);
		greset &= ~GRSTCTL_CSFTRST;
		greset |= GRSTCTL_CSFTRST_DONE;
		dwc2_ग_लिखोl(hsotg, greset, GRSTCTL);
	पूर्ण

	/*
	 * Switching from device mode to host mode by disconnecting
	 * device cable core enters and निकासs क्रमm hibernation.
	 * However, the fअगरo map reमुख्यs not cleared. It results
	 * to a WARNING (WARNING: CPU: 5 PID: 0 at drivers/usb/dwc2/
	 * gadget.c:307 dwc2_hsotg_init_fअगरo+0x12/0x152 [dwc2])
	 * अगर in host mode we disconnect the micro a to b host
	 * cable. Because core reset occurs.
	 * To aव्योम the WARNING, fअगरo_map should be cleared
	 * in dwc2_core_reset() function by taking पूर्णांकo account configs.
	 * fअगरo_map must be cleared only अगर driver is configured in
	 * "CONFIG_USB_DWC2_PERIPHERAL" or "CONFIG_USB_DWC2_DUAL_ROLE"
	 * mode.
	 */
	dwc2_clear_fअगरo_map(hsotg);

	/* Wait क्रम AHB master IDLE state */
	अगर (dwc2_hsotg_रुको_bit_set(hsotg, GRSTCTL, GRSTCTL_AHBIDLE, 10000)) अणु
		dev_warn(hsotg->dev, "%s: HANG! AHB Idle timeout GRSTCTL GRSTCTL_AHBIDLE\n",
			 __func__);
		वापस -EBUSY;
	पूर्ण

	अगर (रुको_क्रम_host_mode && !skip_रुको)
		dwc2_रुको_क्रम_mode(hsotg, true);

	वापस 0;
पूर्ण

/**
 * dwc2_क्रमce_mode() - Force the mode of the controller.
 *
 * Forcing the mode is needed क्रम two हालs:
 *
 * 1) If the dr_mode is set to either HOST or PERIPHERAL we क्रमce the
 * controller to stay in a particular mode regardless of ID pin
 * changes. We करो this once during probe.
 *
 * 2) During probe we want to पढ़ो reset values of the hw
 * configuration रेजिस्टरs that are only available in either host or
 * device mode. We may need to क्रमce the mode अगर the current mode करोes
 * not allow us to access the रेजिस्टर in the mode that we want.
 *
 * In either हाल it only makes sense to क्रमce the mode अगर the
 * controller hardware is OTG capable.
 *
 * Checks are करोne in this function to determine whether करोing a क्रमce
 * would be valid or not.
 *
 * If a क्रमce is करोne, it requires a IDDIG debounce filter delay अगर
 * the filter is configured and enabled. We poll the current mode of
 * the controller to account क्रम this delay.
 *
 * @hsotg: Programming view of DWC_otg controller
 * @host: Host mode flag
 */
व्योम dwc2_क्रमce_mode(काष्ठा dwc2_hsotg *hsotg, bool host)
अणु
	u32 gusbcfg;
	u32 set;
	u32 clear;

	dev_dbg(hsotg->dev, "Forcing mode to %s\n", host ? "host" : "device");

	/*
	 * Force mode has no effect अगर the hardware is not OTG.
	 */
	अगर (!dwc2_hw_is_otg(hsotg))
		वापस;

	/*
	 * If dr_mode is either peripheral or host only, there is no
	 * need to ever क्रमce the mode to the opposite mode.
	 */
	अगर (WARN_ON(host && hsotg->dr_mode == USB_DR_MODE_PERIPHERAL))
		वापस;

	अगर (WARN_ON(!host && hsotg->dr_mode == USB_DR_MODE_HOST))
		वापस;

	gusbcfg = dwc2_पढ़ोl(hsotg, GUSBCFG);

	set = host ? GUSBCFG_FORCEHOSTMODE : GUSBCFG_FORCEDEVMODE;
	clear = host ? GUSBCFG_FORCEDEVMODE : GUSBCFG_FORCEHOSTMODE;

	gusbcfg &= ~clear;
	gusbcfg |= set;
	dwc2_ग_लिखोl(hsotg, gusbcfg, GUSBCFG);

	dwc2_रुको_क्रम_mode(hsotg, host);
	वापस;
पूर्ण

/**
 * dwc2_clear_क्रमce_mode() - Clears the क्रमce mode bits.
 *
 * After clearing the bits, रुको up to 100 ms to account क्रम any
 * potential IDDIG filter delay. We can't know अगर we expect this delay
 * or not because the value of the connector ID status is affected by
 * the क्रमce mode. We only need to call this once during probe अगर
 * dr_mode == OTG.
 *
 * @hsotg: Programming view of DWC_otg controller
 */
अटल व्योम dwc2_clear_क्रमce_mode(काष्ठा dwc2_hsotg *hsotg)
अणु
	u32 gusbcfg;

	अगर (!dwc2_hw_is_otg(hsotg))
		वापस;

	dev_dbg(hsotg->dev, "Clearing force mode bits\n");

	gusbcfg = dwc2_पढ़ोl(hsotg, GUSBCFG);
	gusbcfg &= ~GUSBCFG_FORCEHOSTMODE;
	gusbcfg &= ~GUSBCFG_FORCEDEVMODE;
	dwc2_ग_लिखोl(hsotg, gusbcfg, GUSBCFG);

	अगर (dwc2_iddig_filter_enabled(hsotg))
		msleep(100);
पूर्ण

/*
 * Sets or clears क्रमce mode based on the dr_mode parameter.
 */
व्योम dwc2_क्रमce_dr_mode(काष्ठा dwc2_hsotg *hsotg)
अणु
	चयन (hsotg->dr_mode) अणु
	हाल USB_DR_MODE_HOST:
		/*
		 * NOTE: This is required क्रम some rockchip soc based
		 * platक्रमms on their host-only dwc2.
		 */
		अगर (!dwc2_hw_is_otg(hsotg))
			msleep(50);

		अवरोध;
	हाल USB_DR_MODE_PERIPHERAL:
		dwc2_क्रमce_mode(hsotg, false);
		अवरोध;
	हाल USB_DR_MODE_OTG:
		dwc2_clear_क्रमce_mode(hsotg);
		अवरोध;
	शेष:
		dev_warn(hsotg->dev, "%s() Invalid dr_mode=%d\n",
			 __func__, hsotg->dr_mode);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * dwc2_enable_acg - enable active घड़ी gating feature
 */
व्योम dwc2_enable_acg(काष्ठा dwc2_hsotg *hsotg)
अणु
	अगर (hsotg->params.acg_enable) अणु
		u32 pcgcctl1 = dwc2_पढ़ोl(hsotg, PCGCCTL1);

		dev_dbg(hsotg->dev, "Enabling Active Clock Gating\n");
		pcgcctl1 |= PCGCCTL1_GATEEN;
		dwc2_ग_लिखोl(hsotg, pcgcctl1, PCGCCTL1);
	पूर्ण
पूर्ण

/**
 * dwc2_dump_host_रेजिस्टरs() - Prपूर्णांकs the host रेजिस्टरs
 *
 * @hsotg: Programming view of DWC_otg controller
 *
 * NOTE: This function will be हटाओd once the peripheral controller code
 * is पूर्णांकegrated and the driver is stable
 */
व्योम dwc2_dump_host_रेजिस्टरs(काष्ठा dwc2_hsotg *hsotg)
अणु
#अगर_घोषित DEBUG
	u32 __iomem *addr;
	पूर्णांक i;

	dev_dbg(hsotg->dev, "Host Global Registers\n");
	addr = hsotg->regs + HCFG;
	dev_dbg(hsotg->dev, "HCFG	 @0x%08lX : 0x%08X\n",
		(अचिन्हित दीर्घ)addr, dwc2_पढ़ोl(hsotg, HCFG));
	addr = hsotg->regs + HFIR;
	dev_dbg(hsotg->dev, "HFIR	 @0x%08lX : 0x%08X\n",
		(अचिन्हित दीर्घ)addr, dwc2_पढ़ोl(hsotg, HFIR));
	addr = hsotg->regs + HFNUM;
	dev_dbg(hsotg->dev, "HFNUM	 @0x%08lX : 0x%08X\n",
		(अचिन्हित दीर्घ)addr, dwc2_पढ़ोl(hsotg, HFNUM));
	addr = hsotg->regs + HPTXSTS;
	dev_dbg(hsotg->dev, "HPTXSTS	 @0x%08lX : 0x%08X\n",
		(अचिन्हित दीर्घ)addr, dwc2_पढ़ोl(hsotg, HPTXSTS));
	addr = hsotg->regs + HAINT;
	dev_dbg(hsotg->dev, "HAINT	 @0x%08lX : 0x%08X\n",
		(अचिन्हित दीर्घ)addr, dwc2_पढ़ोl(hsotg, HAINT));
	addr = hsotg->regs + HAINTMSK;
	dev_dbg(hsotg->dev, "HAINTMSK	 @0x%08lX : 0x%08X\n",
		(अचिन्हित दीर्घ)addr, dwc2_पढ़ोl(hsotg, HAINTMSK));
	अगर (hsotg->params.dma_desc_enable) अणु
		addr = hsotg->regs + HFLBADDR;
		dev_dbg(hsotg->dev, "HFLBADDR @0x%08lX : 0x%08X\n",
			(अचिन्हित दीर्घ)addr, dwc2_पढ़ोl(hsotg, HFLBADDR));
	पूर्ण

	addr = hsotg->regs + HPRT0;
	dev_dbg(hsotg->dev, "HPRT0	 @0x%08lX : 0x%08X\n",
		(अचिन्हित दीर्घ)addr, dwc2_पढ़ोl(hsotg, HPRT0));

	क्रम (i = 0; i < hsotg->params.host_channels; i++) अणु
		dev_dbg(hsotg->dev, "Host Channel %d Specific Registers\n", i);
		addr = hsotg->regs + HCCHAR(i);
		dev_dbg(hsotg->dev, "HCCHAR	 @0x%08lX : 0x%08X\n",
			(अचिन्हित दीर्घ)addr, dwc2_पढ़ोl(hsotg, HCCHAR(i)));
		addr = hsotg->regs + HCSPLT(i);
		dev_dbg(hsotg->dev, "HCSPLT	 @0x%08lX : 0x%08X\n",
			(अचिन्हित दीर्घ)addr, dwc2_पढ़ोl(hsotg, HCSPLT(i)));
		addr = hsotg->regs + HCINT(i);
		dev_dbg(hsotg->dev, "HCINT	 @0x%08lX : 0x%08X\n",
			(अचिन्हित दीर्घ)addr, dwc2_पढ़ोl(hsotg, HCINT(i)));
		addr = hsotg->regs + HCINTMSK(i);
		dev_dbg(hsotg->dev, "HCINTMSK	 @0x%08lX : 0x%08X\n",
			(अचिन्हित दीर्घ)addr, dwc2_पढ़ोl(hsotg, HCINTMSK(i)));
		addr = hsotg->regs + HCTSIZ(i);
		dev_dbg(hsotg->dev, "HCTSIZ	 @0x%08lX : 0x%08X\n",
			(अचिन्हित दीर्घ)addr, dwc2_पढ़ोl(hsotg, HCTSIZ(i)));
		addr = hsotg->regs + HCDMA(i);
		dev_dbg(hsotg->dev, "HCDMA	 @0x%08lX : 0x%08X\n",
			(अचिन्हित दीर्घ)addr, dwc2_पढ़ोl(hsotg, HCDMA(i)));
		अगर (hsotg->params.dma_desc_enable) अणु
			addr = hsotg->regs + HCDMAB(i);
			dev_dbg(hsotg->dev, "HCDMAB	 @0x%08lX : 0x%08X\n",
				(अचिन्हित दीर्घ)addr, dwc2_पढ़ोl(hsotg,
								HCDMAB(i)));
		पूर्ण
	पूर्ण
#पूर्ण_अगर
पूर्ण

/**
 * dwc2_dump_global_रेजिस्टरs() - Prपूर्णांकs the core global रेजिस्टरs
 *
 * @hsotg: Programming view of DWC_otg controller
 *
 * NOTE: This function will be हटाओd once the peripheral controller code
 * is पूर्णांकegrated and the driver is stable
 */
व्योम dwc2_dump_global_रेजिस्टरs(काष्ठा dwc2_hsotg *hsotg)
अणु
#अगर_घोषित DEBUG
	u32 __iomem *addr;

	dev_dbg(hsotg->dev, "Core Global Registers\n");
	addr = hsotg->regs + GOTGCTL;
	dev_dbg(hsotg->dev, "GOTGCTL	 @0x%08lX : 0x%08X\n",
		(अचिन्हित दीर्घ)addr, dwc2_पढ़ोl(hsotg, GOTGCTL));
	addr = hsotg->regs + GOTGINT;
	dev_dbg(hsotg->dev, "GOTGINT	 @0x%08lX : 0x%08X\n",
		(अचिन्हित दीर्घ)addr, dwc2_पढ़ोl(hsotg, GOTGINT));
	addr = hsotg->regs + GAHBCFG;
	dev_dbg(hsotg->dev, "GAHBCFG	 @0x%08lX : 0x%08X\n",
		(अचिन्हित दीर्घ)addr, dwc2_पढ़ोl(hsotg, GAHBCFG));
	addr = hsotg->regs + GUSBCFG;
	dev_dbg(hsotg->dev, "GUSBCFG	 @0x%08lX : 0x%08X\n",
		(अचिन्हित दीर्घ)addr, dwc2_पढ़ोl(hsotg, GUSBCFG));
	addr = hsotg->regs + GRSTCTL;
	dev_dbg(hsotg->dev, "GRSTCTL	 @0x%08lX : 0x%08X\n",
		(अचिन्हित दीर्घ)addr, dwc2_पढ़ोl(hsotg, GRSTCTL));
	addr = hsotg->regs + GINTSTS;
	dev_dbg(hsotg->dev, "GINTSTS	 @0x%08lX : 0x%08X\n",
		(अचिन्हित दीर्घ)addr, dwc2_पढ़ोl(hsotg, GINTSTS));
	addr = hsotg->regs + GINTMSK;
	dev_dbg(hsotg->dev, "GINTMSK	 @0x%08lX : 0x%08X\n",
		(अचिन्हित दीर्घ)addr, dwc2_पढ़ोl(hsotg, GINTMSK));
	addr = hsotg->regs + GRXSTSR;
	dev_dbg(hsotg->dev, "GRXSTSR	 @0x%08lX : 0x%08X\n",
		(अचिन्हित दीर्घ)addr, dwc2_पढ़ोl(hsotg, GRXSTSR));
	addr = hsotg->regs + GRXFSIZ;
	dev_dbg(hsotg->dev, "GRXFSIZ	 @0x%08lX : 0x%08X\n",
		(अचिन्हित दीर्घ)addr, dwc2_पढ़ोl(hsotg, GRXFSIZ));
	addr = hsotg->regs + GNPTXFSIZ;
	dev_dbg(hsotg->dev, "GNPTXFSIZ	 @0x%08lX : 0x%08X\n",
		(अचिन्हित दीर्घ)addr, dwc2_पढ़ोl(hsotg, GNPTXFSIZ));
	addr = hsotg->regs + GNPTXSTS;
	dev_dbg(hsotg->dev, "GNPTXSTS	 @0x%08lX : 0x%08X\n",
		(अचिन्हित दीर्घ)addr, dwc2_पढ़ोl(hsotg, GNPTXSTS));
	addr = hsotg->regs + GI2CCTL;
	dev_dbg(hsotg->dev, "GI2CCTL	 @0x%08lX : 0x%08X\n",
		(अचिन्हित दीर्घ)addr, dwc2_पढ़ोl(hsotg, GI2CCTL));
	addr = hsotg->regs + GPVNDCTL;
	dev_dbg(hsotg->dev, "GPVNDCTL	 @0x%08lX : 0x%08X\n",
		(अचिन्हित दीर्घ)addr, dwc2_पढ़ोl(hsotg, GPVNDCTL));
	addr = hsotg->regs + GGPIO;
	dev_dbg(hsotg->dev, "GGPIO	 @0x%08lX : 0x%08X\n",
		(अचिन्हित दीर्घ)addr, dwc2_पढ़ोl(hsotg, GGPIO));
	addr = hsotg->regs + GUID;
	dev_dbg(hsotg->dev, "GUID	 @0x%08lX : 0x%08X\n",
		(अचिन्हित दीर्घ)addr, dwc2_पढ़ोl(hsotg, GUID));
	addr = hsotg->regs + GSNPSID;
	dev_dbg(hsotg->dev, "GSNPSID	 @0x%08lX : 0x%08X\n",
		(अचिन्हित दीर्घ)addr, dwc2_पढ़ोl(hsotg, GSNPSID));
	addr = hsotg->regs + GHWCFG1;
	dev_dbg(hsotg->dev, "GHWCFG1	 @0x%08lX : 0x%08X\n",
		(अचिन्हित दीर्घ)addr, dwc2_पढ़ोl(hsotg, GHWCFG1));
	addr = hsotg->regs + GHWCFG2;
	dev_dbg(hsotg->dev, "GHWCFG2	 @0x%08lX : 0x%08X\n",
		(अचिन्हित दीर्घ)addr, dwc2_पढ़ोl(hsotg, GHWCFG2));
	addr = hsotg->regs + GHWCFG3;
	dev_dbg(hsotg->dev, "GHWCFG3	 @0x%08lX : 0x%08X\n",
		(अचिन्हित दीर्घ)addr, dwc2_पढ़ोl(hsotg, GHWCFG3));
	addr = hsotg->regs + GHWCFG4;
	dev_dbg(hsotg->dev, "GHWCFG4	 @0x%08lX : 0x%08X\n",
		(अचिन्हित दीर्घ)addr, dwc2_पढ़ोl(hsotg, GHWCFG4));
	addr = hsotg->regs + GLPMCFG;
	dev_dbg(hsotg->dev, "GLPMCFG	 @0x%08lX : 0x%08X\n",
		(अचिन्हित दीर्घ)addr, dwc2_पढ़ोl(hsotg, GLPMCFG));
	addr = hsotg->regs + GPWRDN;
	dev_dbg(hsotg->dev, "GPWRDN	 @0x%08lX : 0x%08X\n",
		(अचिन्हित दीर्घ)addr, dwc2_पढ़ोl(hsotg, GPWRDN));
	addr = hsotg->regs + GDFIFOCFG;
	dev_dbg(hsotg->dev, "GDFIFOCFG	 @0x%08lX : 0x%08X\n",
		(अचिन्हित दीर्घ)addr, dwc2_पढ़ोl(hsotg, GDFIFOCFG));
	addr = hsotg->regs + HPTXFSIZ;
	dev_dbg(hsotg->dev, "HPTXFSIZ	 @0x%08lX : 0x%08X\n",
		(अचिन्हित दीर्घ)addr, dwc2_पढ़ोl(hsotg, HPTXFSIZ));

	addr = hsotg->regs + PCGCTL;
	dev_dbg(hsotg->dev, "PCGCTL	 @0x%08lX : 0x%08X\n",
		(अचिन्हित दीर्घ)addr, dwc2_पढ़ोl(hsotg, PCGCTL));
#पूर्ण_अगर
पूर्ण

/**
 * dwc2_flush_tx_fअगरo() - Flushes a Tx FIFO
 *
 * @hsotg: Programming view of DWC_otg controller
 * @num:   Tx FIFO to flush
 */
व्योम dwc2_flush_tx_fअगरo(काष्ठा dwc2_hsotg *hsotg, स्थिर पूर्णांक num)
अणु
	u32 greset;

	dev_vdbg(hsotg->dev, "Flush Tx FIFO %d\n", num);

	/* Wait क्रम AHB master IDLE state */
	अगर (dwc2_hsotg_रुको_bit_set(hsotg, GRSTCTL, GRSTCTL_AHBIDLE, 10000))
		dev_warn(hsotg->dev, "%s:  HANG! AHB Idle GRSCTL\n",
			 __func__);

	greset = GRSTCTL_TXFFLSH;
	greset |= num << GRSTCTL_TXFNUM_SHIFT & GRSTCTL_TXFNUM_MASK;
	dwc2_ग_लिखोl(hsotg, greset, GRSTCTL);

	अगर (dwc2_hsotg_रुको_bit_clear(hsotg, GRSTCTL, GRSTCTL_TXFFLSH, 10000))
		dev_warn(hsotg->dev, "%s:  HANG! timeout GRSTCTL GRSTCTL_TXFFLSH\n",
			 __func__);

	/* Wait क्रम at least 3 PHY Clocks */
	udelay(1);
पूर्ण

/**
 * dwc2_flush_rx_fअगरo() - Flushes the Rx FIFO
 *
 * @hsotg: Programming view of DWC_otg controller
 */
व्योम dwc2_flush_rx_fअगरo(काष्ठा dwc2_hsotg *hsotg)
अणु
	u32 greset;

	dev_vdbg(hsotg->dev, "%s()\n", __func__);

	/* Wait क्रम AHB master IDLE state */
	अगर (dwc2_hsotg_रुको_bit_set(hsotg, GRSTCTL, GRSTCTL_AHBIDLE, 10000))
		dev_warn(hsotg->dev, "%s:  HANG! AHB Idle GRSCTL\n",
			 __func__);

	greset = GRSTCTL_RXFFLSH;
	dwc2_ग_लिखोl(hsotg, greset, GRSTCTL);

	/* Wait क्रम RxFIFO flush करोne */
	अगर (dwc2_hsotg_रुको_bit_clear(hsotg, GRSTCTL, GRSTCTL_RXFFLSH, 10000))
		dev_warn(hsotg->dev, "%s: HANG! timeout GRSTCTL GRSTCTL_RXFFLSH\n",
			 __func__);

	/* Wait क्रम at least 3 PHY Clocks */
	udelay(1);
पूर्ण

bool dwc2_is_controller_alive(काष्ठा dwc2_hsotg *hsotg)
अणु
	अगर (dwc2_पढ़ोl(hsotg, GSNPSID) == 0xffffffff)
		वापस false;
	अन्यथा
		वापस true;
पूर्ण

/**
 * dwc2_enable_global_पूर्णांकerrupts() - Enables the controller's Global
 * Interrupt in the AHB Config रेजिस्टर
 *
 * @hsotg: Programming view of DWC_otg controller
 */
व्योम dwc2_enable_global_पूर्णांकerrupts(काष्ठा dwc2_hsotg *hsotg)
अणु
	u32 ahbcfg = dwc2_पढ़ोl(hsotg, GAHBCFG);

	ahbcfg |= GAHBCFG_GLBL_INTR_EN;
	dwc2_ग_लिखोl(hsotg, ahbcfg, GAHBCFG);
पूर्ण

/**
 * dwc2_disable_global_पूर्णांकerrupts() - Disables the controller's Global
 * Interrupt in the AHB Config रेजिस्टर
 *
 * @hsotg: Programming view of DWC_otg controller
 */
व्योम dwc2_disable_global_पूर्णांकerrupts(काष्ठा dwc2_hsotg *hsotg)
अणु
	u32 ahbcfg = dwc2_पढ़ोl(hsotg, GAHBCFG);

	ahbcfg &= ~GAHBCFG_GLBL_INTR_EN;
	dwc2_ग_लिखोl(hsotg, ahbcfg, GAHBCFG);
पूर्ण

/* Returns the controller's GHWCFG2.OTG_MODE. */
अचिन्हित पूर्णांक dwc2_op_mode(काष्ठा dwc2_hsotg *hsotg)
अणु
	u32 ghwcfg2 = dwc2_पढ़ोl(hsotg, GHWCFG2);

	वापस (ghwcfg2 & GHWCFG2_OP_MODE_MASK) >>
		GHWCFG2_OP_MODE_SHIFT;
पूर्ण

/* Returns true अगर the controller is capable of DRD. */
bool dwc2_hw_is_otg(काष्ठा dwc2_hsotg *hsotg)
अणु
	अचिन्हित पूर्णांक op_mode = dwc2_op_mode(hsotg);

	वापस (op_mode == GHWCFG2_OP_MODE_HNP_SRP_CAPABLE) ||
		(op_mode == GHWCFG2_OP_MODE_SRP_ONLY_CAPABLE) ||
		(op_mode == GHWCFG2_OP_MODE_NO_HNP_SRP_CAPABLE);
पूर्ण

/* Returns true अगर the controller is host-only. */
bool dwc2_hw_is_host(काष्ठा dwc2_hsotg *hsotg)
अणु
	अचिन्हित पूर्णांक op_mode = dwc2_op_mode(hsotg);

	वापस (op_mode == GHWCFG2_OP_MODE_SRP_CAPABLE_HOST) ||
		(op_mode == GHWCFG2_OP_MODE_NO_SRP_CAPABLE_HOST);
पूर्ण

/* Returns true अगर the controller is device-only. */
bool dwc2_hw_is_device(काष्ठा dwc2_hsotg *hsotg)
अणु
	अचिन्हित पूर्णांक op_mode = dwc2_op_mode(hsotg);

	वापस (op_mode == GHWCFG2_OP_MODE_SRP_CAPABLE_DEVICE) ||
		(op_mode == GHWCFG2_OP_MODE_NO_SRP_CAPABLE_DEVICE);
पूर्ण

/**
 * dwc2_hsotg_रुको_bit_set - Waits क्रम bit to be set.
 * @hsotg: Programming view of DWC_otg controller.
 * @offset: Register's offset where bit/bits must be set.
 * @mask: Mask of the bit/bits which must be set.
 * @समयout: Timeout to रुको.
 *
 * Return: 0 अगर bit/bits are set or -ETIMEDOUT in हाल of समयout.
 */
पूर्णांक dwc2_hsotg_रुको_bit_set(काष्ठा dwc2_hsotg *hsotg, u32 offset, u32 mask,
			    u32 समयout)
अणु
	u32 i;

	क्रम (i = 0; i < समयout; i++) अणु
		अगर (dwc2_पढ़ोl(hsotg, offset) & mask)
			वापस 0;
		udelay(1);
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

/**
 * dwc2_hsotg_रुको_bit_clear - Waits क्रम bit to be clear.
 * @hsotg: Programming view of DWC_otg controller.
 * @offset: Register's offset where bit/bits must be set.
 * @mask: Mask of the bit/bits which must be set.
 * @समयout: Timeout to रुको.
 *
 * Return: 0 अगर bit/bits are set or -ETIMEDOUT in हाल of समयout.
 */
पूर्णांक dwc2_hsotg_रुको_bit_clear(काष्ठा dwc2_hsotg *hsotg, u32 offset, u32 mask,
			      u32 समयout)
अणु
	u32 i;

	क्रम (i = 0; i < समयout; i++) अणु
		अगर (!(dwc2_पढ़ोl(hsotg, offset) & mask))
			वापस 0;
		udelay(1);
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

/*
 * Initializes the FSLSPClkSel field of the HCFG रेजिस्टर depending on the
 * PHY type
 */
व्योम dwc2_init_fs_ls_pclk_sel(काष्ठा dwc2_hsotg *hsotg)
अणु
	u32 hcfg, val;

	अगर ((hsotg->hw_params.hs_phy_type == GHWCFG2_HS_PHY_TYPE_ULPI &&
	     hsotg->hw_params.fs_phy_type == GHWCFG2_FS_PHY_TYPE_DEDICATED &&
	     hsotg->params.ulpi_fs_ls) ||
	    hsotg->params.phy_type == DWC2_PHY_TYPE_PARAM_FS) अणु
		/* Full speed PHY */
		val = HCFG_FSLSPCLKSEL_48_MHZ;
	पूर्ण अन्यथा अणु
		/* High speed PHY running at full speed or high speed */
		val = HCFG_FSLSPCLKSEL_30_60_MHZ;
	पूर्ण

	dev_dbg(hsotg->dev, "Initializing HCFG.FSLSPClkSel to %08x\n", val);
	hcfg = dwc2_पढ़ोl(hsotg, HCFG);
	hcfg &= ~HCFG_FSLSPCLKSEL_MASK;
	hcfg |= val << HCFG_FSLSPCLKSEL_SHIFT;
	dwc2_ग_लिखोl(hsotg, hcfg, HCFG);
पूर्ण

अटल पूर्णांक dwc2_fs_phy_init(काष्ठा dwc2_hsotg *hsotg, bool select_phy)
अणु
	u32 usbcfg, ggpio, i2cctl;
	पूर्णांक retval = 0;

	/*
	 * core_init() is now called on every चयन so only call the
	 * following क्रम the first समय through
	 */
	अगर (select_phy) अणु
		dev_dbg(hsotg->dev, "FS PHY selected\n");

		usbcfg = dwc2_पढ़ोl(hsotg, GUSBCFG);
		अगर (!(usbcfg & GUSBCFG_PHYSEL)) अणु
			usbcfg |= GUSBCFG_PHYSEL;
			dwc2_ग_लिखोl(hsotg, usbcfg, GUSBCFG);

			/* Reset after a PHY select */
			retval = dwc2_core_reset(hsotg, false);

			अगर (retval) अणु
				dev_err(hsotg->dev,
					"%s: Reset failed, aborting", __func__);
				वापस retval;
			पूर्ण
		पूर्ण

		अगर (hsotg->params.activate_sपंचांग_fs_transceiver) अणु
			ggpio = dwc2_पढ़ोl(hsotg, GGPIO);
			अगर (!(ggpio & GGPIO_STM32_OTG_GCCFG_PWRDWN)) अणु
				dev_dbg(hsotg->dev, "Activating transceiver\n");
				/*
				 * STM32F4x9 uses the GGPIO रेजिस्टर as general
				 * core configuration रेजिस्टर.
				 */
				ggpio |= GGPIO_STM32_OTG_GCCFG_PWRDWN;
				dwc2_ग_लिखोl(hsotg, ggpio, GGPIO);
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * Program DCFG.DevSpd or HCFG.FSLSPclkSel to 48Mhz in FS. Also
	 * करो this on HNP Dev/Host mode चयनes (करोne in dev_init and
	 * host_init).
	 */
	अगर (dwc2_is_host_mode(hsotg))
		dwc2_init_fs_ls_pclk_sel(hsotg);

	अगर (hsotg->params.i2c_enable) अणु
		dev_dbg(hsotg->dev, "FS PHY enabling I2C\n");

		/* Program GUSBCFG.OtgUपंचांगiFsSel to I2C */
		usbcfg = dwc2_पढ़ोl(hsotg, GUSBCFG);
		usbcfg |= GUSBCFG_OTG_UTMI_FS_SEL;
		dwc2_ग_लिखोl(hsotg, usbcfg, GUSBCFG);

		/* Program GI2CCTL.I2CEn */
		i2cctl = dwc2_पढ़ोl(hsotg, GI2CCTL);
		i2cctl &= ~GI2CCTL_I2CDEVADDR_MASK;
		i2cctl |= 1 << GI2CCTL_I2CDEVADDR_SHIFT;
		i2cctl &= ~GI2CCTL_I2CEN;
		dwc2_ग_लिखोl(hsotg, i2cctl, GI2CCTL);
		i2cctl |= GI2CCTL_I2CEN;
		dwc2_ग_लिखोl(hsotg, i2cctl, GI2CCTL);
	पूर्ण

	वापस retval;
पूर्ण

अटल पूर्णांक dwc2_hs_phy_init(काष्ठा dwc2_hsotg *hsotg, bool select_phy)
अणु
	u32 usbcfg, usbcfg_old;
	पूर्णांक retval = 0;

	अगर (!select_phy)
		वापस 0;

	usbcfg = dwc2_पढ़ोl(hsotg, GUSBCFG);
	usbcfg_old = usbcfg;

	/*
	 * HS PHY parameters. These parameters are preserved during soft reset
	 * so only program the first समय. Do a soft reset immediately after
	 * setting phyअगर.
	 */
	चयन (hsotg->params.phy_type) अणु
	हाल DWC2_PHY_TYPE_PARAM_ULPI:
		/* ULPI पूर्णांकerface */
		dev_dbg(hsotg->dev, "HS ULPI PHY selected\n");
		usbcfg |= GUSBCFG_ULPI_UTMI_SEL;
		usbcfg &= ~(GUSBCFG_PHYIF16 | GUSBCFG_DDRSEL);
		अगर (hsotg->params.phy_ulpi_ddr)
			usbcfg |= GUSBCFG_DDRSEL;

		/* Set बाह्यal VBUS indicator as needed. */
		अगर (hsotg->params.oc_disable)
			usbcfg |= (GUSBCFG_ULPI_INT_VBUS_IND |
				   GUSBCFG_INDICATORPASSTHROUGH);
		अवरोध;
	हाल DWC2_PHY_TYPE_PARAM_UTMI:
		/* UTMI+ पूर्णांकerface */
		dev_dbg(hsotg->dev, "HS UTMI+ PHY selected\n");
		usbcfg &= ~(GUSBCFG_ULPI_UTMI_SEL | GUSBCFG_PHYIF16);
		अगर (hsotg->params.phy_uपंचांगi_width == 16)
			usbcfg |= GUSBCFG_PHYIF16;

		/* Set turnaround समय */
		अगर (dwc2_is_device_mode(hsotg)) अणु
			usbcfg &= ~GUSBCFG_USBTRDTIM_MASK;
			अगर (hsotg->params.phy_uपंचांगi_width == 16)
				usbcfg |= 5 << GUSBCFG_USBTRDTIM_SHIFT;
			अन्यथा
				usbcfg |= 9 << GUSBCFG_USBTRDTIM_SHIFT;
		पूर्ण
		अवरोध;
	शेष:
		dev_err(hsotg->dev, "FS PHY selected at HS!\n");
		अवरोध;
	पूर्ण

	अगर (usbcfg != usbcfg_old) अणु
		dwc2_ग_लिखोl(hsotg, usbcfg, GUSBCFG);

		/* Reset after setting the PHY parameters */
		retval = dwc2_core_reset(hsotg, false);
		अगर (retval) अणु
			dev_err(hsotg->dev,
				"%s: Reset failed, aborting", __func__);
			वापस retval;
		पूर्ण
	पूर्ण

	वापस retval;
पूर्ण

पूर्णांक dwc2_phy_init(काष्ठा dwc2_hsotg *hsotg, bool select_phy)
अणु
	u32 usbcfg;
	पूर्णांक retval = 0;

	अगर ((hsotg->params.speed == DWC2_SPEED_PARAM_FULL ||
	     hsotg->params.speed == DWC2_SPEED_PARAM_LOW) &&
	    hsotg->params.phy_type == DWC2_PHY_TYPE_PARAM_FS) अणु
		/* If FS/LS mode with FS/LS PHY */
		retval = dwc2_fs_phy_init(hsotg, select_phy);
		अगर (retval)
			वापस retval;
	पूर्ण अन्यथा अणु
		/* High speed PHY */
		retval = dwc2_hs_phy_init(hsotg, select_phy);
		अगर (retval)
			वापस retval;
	पूर्ण

	अगर (hsotg->hw_params.hs_phy_type == GHWCFG2_HS_PHY_TYPE_ULPI &&
	    hsotg->hw_params.fs_phy_type == GHWCFG2_FS_PHY_TYPE_DEDICATED &&
	    hsotg->params.ulpi_fs_ls) अणु
		dev_dbg(hsotg->dev, "Setting ULPI FSLS\n");
		usbcfg = dwc2_पढ़ोl(hsotg, GUSBCFG);
		usbcfg |= GUSBCFG_ULPI_FS_LS;
		usbcfg |= GUSBCFG_ULPI_CLK_SUSP_M;
		dwc2_ग_लिखोl(hsotg, usbcfg, GUSBCFG);
	पूर्ण अन्यथा अणु
		usbcfg = dwc2_पढ़ोl(hsotg, GUSBCFG);
		usbcfg &= ~GUSBCFG_ULPI_FS_LS;
		usbcfg &= ~GUSBCFG_ULPI_CLK_SUSP_M;
		dwc2_ग_लिखोl(hsotg, usbcfg, GUSBCFG);
	पूर्ण

	वापस retval;
पूर्ण

MODULE_DESCRIPTION("DESIGNWARE HS OTG Core");
MODULE_AUTHOR("Synopsys, Inc.");
MODULE_LICENSE("Dual BSD/GPL");
