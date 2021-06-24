<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause)
/*
 * core_पूर्णांकr.c - DesignWare HS OTG Controller common पूर्णांकerrupt handling
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
 * This file contains the common पूर्णांकerrupt handlers
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/usb.h>

#समावेश <linux/usb/hcd.h>
#समावेश <linux/usb/ch11.h>

#समावेश "core.h"
#समावेश "hcd.h"

अटल स्थिर अक्षर *dwc2_op_state_str(काष्ठा dwc2_hsotg *hsotg)
अणु
	चयन (hsotg->op_state) अणु
	हाल OTG_STATE_A_HOST:
		वापस "a_host";
	हाल OTG_STATE_A_SUSPEND:
		वापस "a_suspend";
	हाल OTG_STATE_A_PERIPHERAL:
		वापस "a_peripheral";
	हाल OTG_STATE_B_PERIPHERAL:
		वापस "b_peripheral";
	हाल OTG_STATE_B_HOST:
		वापस "b_host";
	शेष:
		वापस "unknown";
	पूर्ण
पूर्ण

/**
 * dwc2_handle_usb_port_पूर्णांकr - handles OTG PRTINT पूर्णांकerrupts.
 * When the PRTINT पूर्णांकerrupt fires, there are certain status bits in the Host
 * Port that needs to get cleared.
 *
 * @hsotg: Programming view of DWC_otg controller
 */
अटल व्योम dwc2_handle_usb_port_पूर्णांकr(काष्ठा dwc2_hsotg *hsotg)
अणु
	u32 hprt0 = dwc2_पढ़ोl(hsotg, HPRT0);

	अगर (hprt0 & HPRT0_ENACHG) अणु
		hprt0 &= ~HPRT0_ENA;
		dwc2_ग_लिखोl(hsotg, hprt0, HPRT0);
	पूर्ण
पूर्ण

/**
 * dwc2_handle_mode_mismatch_पूर्णांकr() - Logs a mode mismatch warning message
 *
 * @hsotg: Programming view of DWC_otg controller
 */
अटल व्योम dwc2_handle_mode_mismatch_पूर्णांकr(काष्ठा dwc2_hsotg *hsotg)
अणु
	/* Clear पूर्णांकerrupt */
	dwc2_ग_लिखोl(hsotg, GINTSTS_MODEMIS, GINTSTS);

	dev_warn(hsotg->dev, "Mode Mismatch Interrupt: currently in %s mode\n",
		 dwc2_is_host_mode(hsotg) ? "Host" : "Device");
पूर्ण

/**
 * dwc2_handle_otg_पूर्णांकr() - Handles the OTG Interrupts. It पढ़ोs the OTG
 * Interrupt Register (GOTGINT) to determine what पूर्णांकerrupt has occurred.
 *
 * @hsotg: Programming view of DWC_otg controller
 */
अटल व्योम dwc2_handle_otg_पूर्णांकr(काष्ठा dwc2_hsotg *hsotg)
अणु
	u32 gotgपूर्णांक;
	u32 gotgctl;
	u32 gपूर्णांकmsk;

	gotgपूर्णांक = dwc2_पढ़ोl(hsotg, GOTGINT);
	gotgctl = dwc2_पढ़ोl(hsotg, GOTGCTL);
	dev_dbg(hsotg->dev, "++OTG Interrupt gotgint=%0x [%s]\n", gotgपूर्णांक,
		dwc2_op_state_str(hsotg));

	अगर (gotgपूर्णांक & GOTGINT_SES_END_DET) अणु
		dev_dbg(hsotg->dev,
			" ++OTG Interrupt: Session End Detected++ (%s)\n",
			dwc2_op_state_str(hsotg));
		gotgctl = dwc2_पढ़ोl(hsotg, GOTGCTL);

		अगर (dwc2_is_device_mode(hsotg))
			dwc2_hsotg_disconnect(hsotg);

		अगर (hsotg->op_state == OTG_STATE_B_HOST) अणु
			hsotg->op_state = OTG_STATE_B_PERIPHERAL;
		पूर्ण अन्यथा अणु
			/*
			 * If not B_HOST and Device HNP still set, HNP did
			 * not succeed!
			 */
			अगर (gotgctl & GOTGCTL_DEVHNPEN) अणु
				dev_dbg(hsotg->dev, "Session End Detected\n");
				dev_err(hsotg->dev,
					"Device Not Connected/Responding!\n");
			पूर्ण

			/*
			 * If Session End Detected the B-Cable has been
			 * disconnected
			 */
			/* Reset to a clean state */
			hsotg->lx_state = DWC2_L0;
		पूर्ण

		gotgctl = dwc2_पढ़ोl(hsotg, GOTGCTL);
		gotgctl &= ~GOTGCTL_DEVHNPEN;
		dwc2_ग_लिखोl(hsotg, gotgctl, GOTGCTL);
	पूर्ण

	अगर (gotgपूर्णांक & GOTGINT_SES_REQ_SUC_STS_CHNG) अणु
		dev_dbg(hsotg->dev,
			" ++OTG Interrupt: Session Request Success Status Change++\n");
		gotgctl = dwc2_पढ़ोl(hsotg, GOTGCTL);
		अगर (gotgctl & GOTGCTL_SESREQSCS) अणु
			अगर (hsotg->params.phy_type == DWC2_PHY_TYPE_PARAM_FS &&
			    hsotg->params.i2c_enable) अणु
				hsotg->srp_success = 1;
			पूर्ण अन्यथा अणु
				/* Clear Session Request */
				gotgctl = dwc2_पढ़ोl(hsotg, GOTGCTL);
				gotgctl &= ~GOTGCTL_SESREQ;
				dwc2_ग_लिखोl(hsotg, gotgctl, GOTGCTL);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (gotgपूर्णांक & GOTGINT_HST_NEG_SUC_STS_CHNG) अणु
		/*
		 * Prपूर्णांक statements during the HNP पूर्णांकerrupt handling
		 * can cause it to fail
		 */
		gotgctl = dwc2_पढ़ोl(hsotg, GOTGCTL);
		/*
		 * WA क्रम 3.00a- HW is not setting cur_mode, even someबार
		 * this करोes not help
		 */
		अगर (hsotg->hw_params.snpsid >= DWC2_CORE_REV_3_00a)
			udelay(100);
		अगर (gotgctl & GOTGCTL_HSTNEGSCS) अणु
			अगर (dwc2_is_host_mode(hsotg)) अणु
				hsotg->op_state = OTG_STATE_B_HOST;
				/*
				 * Need to disable SOF पूर्णांकerrupt immediately.
				 * When चयनing from device to host, the PCD
				 * पूर्णांकerrupt handler won't handle the पूर्णांकerrupt
				 * अगर host mode is alपढ़ोy set. The HCD
				 * पूर्णांकerrupt handler won't get called अगर the
				 * HCD state is HALT. This means that the
				 * पूर्णांकerrupt करोes not get handled and Linux
				 * complains loudly.
				 */
				gपूर्णांकmsk = dwc2_पढ़ोl(hsotg, GINTMSK);
				gपूर्णांकmsk &= ~GINTSTS_SOF;
				dwc2_ग_लिखोl(hsotg, gपूर्णांकmsk, GINTMSK);

				/*
				 * Call callback function with spin lock
				 * released
				 */
				spin_unlock(&hsotg->lock);

				/* Initialize the Core क्रम Host mode */
				dwc2_hcd_start(hsotg);
				spin_lock(&hsotg->lock);
				hsotg->op_state = OTG_STATE_B_HOST;
			पूर्ण
		पूर्ण अन्यथा अणु
			gotgctl = dwc2_पढ़ोl(hsotg, GOTGCTL);
			gotgctl &= ~(GOTGCTL_HNPREQ | GOTGCTL_DEVHNPEN);
			dwc2_ग_लिखोl(hsotg, gotgctl, GOTGCTL);
			dev_dbg(hsotg->dev, "HNP Failed\n");
			dev_err(hsotg->dev,
				"Device Not Connected/Responding\n");
		पूर्ण
	पूर्ण

	अगर (gotgपूर्णांक & GOTGINT_HST_NEG_DET) अणु
		/*
		 * The disconnect पूर्णांकerrupt is set at the same समय as
		 * Host Negotiation Detected. During the mode चयन all
		 * पूर्णांकerrupts are cleared so the disconnect पूर्णांकerrupt
		 * handler will not get executed.
		 */
		dev_dbg(hsotg->dev,
			" ++OTG Interrupt: Host Negotiation Detected++ (%s)\n",
			(dwc2_is_host_mode(hsotg) ? "Host" : "Device"));
		अगर (dwc2_is_device_mode(hsotg)) अणु
			dev_dbg(hsotg->dev, "a_suspend->a_peripheral (%d)\n",
				hsotg->op_state);
			spin_unlock(&hsotg->lock);
			dwc2_hcd_disconnect(hsotg, false);
			spin_lock(&hsotg->lock);
			hsotg->op_state = OTG_STATE_A_PERIPHERAL;
		पूर्ण अन्यथा अणु
			/* Need to disable SOF पूर्णांकerrupt immediately */
			gपूर्णांकmsk = dwc2_पढ़ोl(hsotg, GINTMSK);
			gपूर्णांकmsk &= ~GINTSTS_SOF;
			dwc2_ग_लिखोl(hsotg, gपूर्णांकmsk, GINTMSK);
			spin_unlock(&hsotg->lock);
			dwc2_hcd_start(hsotg);
			spin_lock(&hsotg->lock);
			hsotg->op_state = OTG_STATE_A_HOST;
		पूर्ण
	पूर्ण

	अगर (gotgपूर्णांक & GOTGINT_A_DEV_TOUT_CHG)
		dev_dbg(hsotg->dev,
			" ++OTG Interrupt: A-Device Timeout Change++\n");
	अगर (gotgपूर्णांक & GOTGINT_DBNCE_DONE)
		dev_dbg(hsotg->dev, " ++OTG Interrupt: Debounce Done++\n");

	/* Clear GOTGINT */
	dwc2_ग_लिखोl(hsotg, gotgपूर्णांक, GOTGINT);
पूर्ण

/**
 * dwc2_handle_conn_id_status_change_पूर्णांकr() - Handles the Connector ID Status
 * Change Interrupt
 *
 * @hsotg: Programming view of DWC_otg controller
 *
 * Reads the OTG Interrupt Register (GOTCTL) to determine whether this is a
 * Device to Host Mode transition or a Host to Device Mode transition. This only
 * occurs when the cable is connected/हटाओd from the PHY connector.
 */
अटल व्योम dwc2_handle_conn_id_status_change_पूर्णांकr(काष्ठा dwc2_hsotg *hsotg)
अणु
	u32 gपूर्णांकmsk;

	/* Clear पूर्णांकerrupt */
	dwc2_ग_लिखोl(hsotg, GINTSTS_CONIDSTSCHNG, GINTSTS);

	/* Need to disable SOF पूर्णांकerrupt immediately */
	gपूर्णांकmsk = dwc2_पढ़ोl(hsotg, GINTMSK);
	gपूर्णांकmsk &= ~GINTSTS_SOF;
	dwc2_ग_लिखोl(hsotg, gपूर्णांकmsk, GINTMSK);

	dev_dbg(hsotg->dev, " ++Connector ID Status Change Interrupt++  (%s)\n",
		dwc2_is_host_mode(hsotg) ? "Host" : "Device");

	/*
	 * Need to schedule a work, as there are possible DELAY function calls.
	 */
	अगर (hsotg->wq_otg)
		queue_work(hsotg->wq_otg, &hsotg->wf_otg);
पूर्ण

/**
 * dwc2_handle_session_req_पूर्णांकr() - This पूर्णांकerrupt indicates that a device is
 * initiating the Session Request Protocol to request the host to turn on bus
 * घातer so a new session can begin
 *
 * @hsotg: Programming view of DWC_otg controller
 *
 * This handler responds by turning on bus घातer. If the DWC_otg controller is
 * in low घातer mode, this handler brings the controller out of low घातer mode
 * beक्रमe turning on bus घातer.
 */
अटल व्योम dwc2_handle_session_req_पूर्णांकr(काष्ठा dwc2_hsotg *hsotg)
अणु
	पूर्णांक ret;
	u32 hprt0;

	/* Clear पूर्णांकerrupt */
	dwc2_ग_लिखोl(hsotg, GINTSTS_SESSREQINT, GINTSTS);

	dev_dbg(hsotg->dev, "Session request interrupt - lx_state=%d\n",
		hsotg->lx_state);

	अगर (dwc2_is_device_mode(hsotg)) अणु
		अगर (hsotg->lx_state == DWC2_L2) अणु
			अगर (hsotg->in_ppd) अणु
				ret = dwc2_निकास_partial_घातer_करोwn(hsotg, 0,
								   true);
				अगर (ret)
					dev_err(hsotg->dev,
						"exit power_down failed\n");
			पूर्ण

			/* Exit gadget mode घड़ी gating. */
			अगर (hsotg->params.घातer_करोwn ==
			    DWC2_POWER_DOWN_PARAM_NONE && hsotg->bus_suspended)
				dwc2_gadget_निकास_घड़ी_gating(hsotg, 0);
		पूर्ण

		/*
		 * Report disconnect अगर there is any previous session
		 * established
		 */
		dwc2_hsotg_disconnect(hsotg);
	पूर्ण अन्यथा अणु
		/* Turn on the port घातer bit. */
		hprt0 = dwc2_पढ़ो_hprt0(hsotg);
		hprt0 |= HPRT0_PWR;
		dwc2_ग_लिखोl(hsotg, hprt0, HPRT0);
		/* Connect hcd after port घातer is set. */
		dwc2_hcd_connect(hsotg);
	पूर्ण
पूर्ण

/**
 * dwc2_wakeup_from_lpm_l1 - Exit the device from LPM L1 state
 *
 * @hsotg: Programming view of DWC_otg controller
 *
 */
अटल व्योम dwc2_wakeup_from_lpm_l1(काष्ठा dwc2_hsotg *hsotg)
अणु
	u32 glpmcfg;
	u32 i = 0;

	अगर (hsotg->lx_state != DWC2_L1) अणु
		dev_err(hsotg->dev, "Core isn't in DWC2_L1 state\n");
		वापस;
	पूर्ण

	glpmcfg = dwc2_पढ़ोl(hsotg, GLPMCFG);
	अगर (dwc2_is_device_mode(hsotg)) अणु
		dev_dbg(hsotg->dev, "Exit from L1 state\n");
		glpmcfg &= ~GLPMCFG_ENBLSLPM;
		glpmcfg &= ~GLPMCFG_HIRD_THRES_EN;
		dwc2_ग_लिखोl(hsotg, glpmcfg, GLPMCFG);

		करो अणु
			glpmcfg = dwc2_पढ़ोl(hsotg, GLPMCFG);

			अगर (!(glpmcfg & (GLPMCFG_COREL1RES_MASK |
					 GLPMCFG_L1RESUMEOK | GLPMCFG_SLPSTS)))
				अवरोध;

			udelay(1);
		पूर्ण जबतक (++i < 200);

		अगर (i == 200) अणु
			dev_err(hsotg->dev, "Failed to exit L1 sleep state in 200us.\n");
			वापस;
		पूर्ण
		dwc2_gadget_init_lpm(hsotg);
	पूर्ण अन्यथा अणु
		/* TODO */
		dev_err(hsotg->dev, "Host side LPM is not supported.\n");
		वापस;
	पूर्ण

	/* Change to L0 state */
	hsotg->lx_state = DWC2_L0;

	/* Inक्रमm gadget to निकास from L1 */
	call_gadget(hsotg, resume);
पूर्ण

/*
 * This पूर्णांकerrupt indicates that the DWC_otg controller has detected a
 * resume or remote wakeup sequence. If the DWC_otg controller is in
 * low घातer mode, the handler must brings the controller out of low
 * घातer mode. The controller स्वतःmatically begins resume संकेतing.
 * The handler schedules a समय to stop resume संकेतing.
 */
अटल व्योम dwc2_handle_wakeup_detected_पूर्णांकr(काष्ठा dwc2_hsotg *hsotg)
अणु
	पूर्णांक ret;

	/* Clear पूर्णांकerrupt */
	dwc2_ग_लिखोl(hsotg, GINTSTS_WKUPINT, GINTSTS);

	dev_dbg(hsotg->dev, "++Resume or Remote Wakeup Detected Interrupt++\n");
	dev_dbg(hsotg->dev, "%s lxstate = %d\n", __func__, hsotg->lx_state);

	अगर (hsotg->lx_state == DWC2_L1) अणु
		dwc2_wakeup_from_lpm_l1(hsotg);
		वापस;
	पूर्ण

	अगर (dwc2_is_device_mode(hsotg)) अणु
		dev_dbg(hsotg->dev, "DSTS=0x%0x\n",
			dwc2_पढ़ोl(hsotg, DSTS));
		अगर (hsotg->lx_state == DWC2_L2) अणु
			अगर (hsotg->in_ppd) अणु
				u32 dctl = dwc2_पढ़ोl(hsotg, DCTL);
				/* Clear Remote Wakeup Signaling */
				dctl &= ~DCTL_RMTWKUPSIG;
				dwc2_ग_लिखोl(hsotg, dctl, DCTL);
				ret = dwc2_निकास_partial_घातer_करोwn(hsotg, 1,
								   true);
				अगर (ret)
					dev_err(hsotg->dev,
						"exit partial_power_down failed\n");
				call_gadget(hsotg, resume);
			पूर्ण

			/* Exit gadget mode घड़ी gating. */
			अगर (hsotg->params.घातer_करोwn ==
			    DWC2_POWER_DOWN_PARAM_NONE && hsotg->bus_suspended)
				dwc2_gadget_निकास_घड़ी_gating(hsotg, 0);
		पूर्ण अन्यथा अणु
			/* Change to L0 state */
			hsotg->lx_state = DWC2_L0;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (hsotg->lx_state == DWC2_L2) अणु
			अगर (hsotg->in_ppd) अणु
				ret = dwc2_निकास_partial_घातer_करोwn(hsotg, 1,
								   true);
				अगर (ret)
					dev_err(hsotg->dev,
						"exit partial_power_down failed\n");
			पूर्ण

			अगर (hsotg->params.घातer_करोwn ==
			    DWC2_POWER_DOWN_PARAM_NONE && hsotg->bus_suspended)
				dwc2_host_निकास_घड़ी_gating(hsotg, 1);

			/*
			 * If we've got this quirk then the PHY is stuck upon
			 * wakeup.  Assert reset.  This will propagate out and
			 * eventually we'll re-क्रमागतerate the device.  Not great
			 * but the best we can करो.  We can't call phy_reset()
			 * at पूर्णांकerrupt समय but there's no hurry, so we'll
			 * schedule it क्रम later.
			 */
			अगर (hsotg->reset_phy_on_wake)
				dwc2_host_schedule_phy_reset(hsotg);

			mod_समयr(&hsotg->wkp_समयr,
				  jअगरfies + msecs_to_jअगरfies(71));
		पूर्ण अन्यथा अणु
			/* Change to L0 state */
			hsotg->lx_state = DWC2_L0;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * This पूर्णांकerrupt indicates that a device has been disconnected from the
 * root port
 */
अटल व्योम dwc2_handle_disconnect_पूर्णांकr(काष्ठा dwc2_hsotg *hsotg)
अणु
	dwc2_ग_लिखोl(hsotg, GINTSTS_DISCONNINT, GINTSTS);

	dev_dbg(hsotg->dev, "++Disconnect Detected Interrupt++ (%s) %s\n",
		dwc2_is_host_mode(hsotg) ? "Host" : "Device",
		dwc2_op_state_str(hsotg));

	अगर (hsotg->op_state == OTG_STATE_A_HOST)
		dwc2_hcd_disconnect(hsotg, false);
पूर्ण

/*
 * This पूर्णांकerrupt indicates that SUSPEND state has been detected on the USB.
 *
 * For HNP the USB Suspend पूर्णांकerrupt संकेतs the change from "a_peripheral"
 * to "a_host".
 *
 * When घातer management is enabled the core will be put in low घातer mode.
 */
अटल व्योम dwc2_handle_usb_suspend_पूर्णांकr(काष्ठा dwc2_hsotg *hsotg)
अणु
	u32 dsts;
	पूर्णांक ret;

	/* Clear पूर्णांकerrupt */
	dwc2_ग_लिखोl(hsotg, GINTSTS_USBSUSP, GINTSTS);

	dev_dbg(hsotg->dev, "USB SUSPEND\n");

	अगर (dwc2_is_device_mode(hsotg)) अणु
		/*
		 * Check the Device status रेजिस्टर to determine अगर the Suspend
		 * state is active
		 */
		dsts = dwc2_पढ़ोl(hsotg, DSTS);
		dev_dbg(hsotg->dev, "%s: DSTS=0x%0x\n", __func__, dsts);
		dev_dbg(hsotg->dev,
			"DSTS.Suspend Status=%d HWCFG4.Power Optimize=%d HWCFG4.Hibernation=%d\n",
			!!(dsts & DSTS_SUSPSTS),
			hsotg->hw_params.घातer_optimized,
			hsotg->hw_params.hibernation);

		/* Ignore suspend request beक्रमe क्रमागतeration */
		अगर (!dwc2_is_device_connected(hsotg)) अणु
			dev_dbg(hsotg->dev,
				"ignore suspend request before enumeration\n");
			वापस;
		पूर्ण
		अगर (dsts & DSTS_SUSPSTS) अणु
			चयन (hsotg->params.घातer_करोwn) अणु
			हाल DWC2_POWER_DOWN_PARAM_PARTIAL:
				ret = dwc2_enter_partial_घातer_करोwn(hsotg);
				अगर (ret)
					dev_err(hsotg->dev,
						"enter partial_power_down failed\n");

				udelay(100);

				/* Ask phy to be suspended */
				अगर (!IS_ERR_OR_शून्य(hsotg->uphy))
					usb_phy_set_suspend(hsotg->uphy, true);
				अवरोध;
			हाल DWC2_POWER_DOWN_PARAM_HIBERNATION:
				ret = dwc2_enter_hibernation(hsotg, 0);
				अगर (ret)
					dev_err(hsotg->dev,
						"enter hibernation failed\n");
				अवरोध;
			हाल DWC2_POWER_DOWN_PARAM_NONE:
				/*
				 * If neither hibernation nor partial घातer करोwn are supported,
				 * घड़ी gating is used to save घातer.
				 */
				dwc2_gadget_enter_घड़ी_gating(hsotg);
			पूर्ण

			/*
			 * Change to L2 (suspend) state beक्रमe releasing
			 * spinlock
			 */
			hsotg->lx_state = DWC2_L2;

			/* Call gadget suspend callback */
			call_gadget(hsotg, suspend);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (hsotg->op_state == OTG_STATE_A_PERIPHERAL) अणु
			dev_dbg(hsotg->dev, "a_peripheral->a_host\n");

			/* Change to L2 (suspend) state */
			hsotg->lx_state = DWC2_L2;
			/* Clear the a_peripheral flag, back to a_host */
			spin_unlock(&hsotg->lock);
			dwc2_hcd_start(hsotg);
			spin_lock(&hsotg->lock);
			hsotg->op_state = OTG_STATE_A_HOST;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * dwc2_handle_lpm_पूर्णांकr - GINTSTS_LPMTRANRCVD Interrupt handler
 *
 * @hsotg: Programming view of DWC_otg controller
 *
 */
अटल व्योम dwc2_handle_lpm_पूर्णांकr(काष्ठा dwc2_hsotg *hsotg)
अणु
	u32 glpmcfg;
	u32 pcgcctl;
	u32 hird;
	u32 hird_thres;
	u32 hird_thres_en;
	u32 enslpm;

	/* Clear पूर्णांकerrupt */
	dwc2_ग_लिखोl(hsotg, GINTSTS_LPMTRANRCVD, GINTSTS);

	glpmcfg = dwc2_पढ़ोl(hsotg, GLPMCFG);

	अगर (!(glpmcfg & GLPMCFG_LPMCAP)) अणु
		dev_err(hsotg->dev, "Unexpected LPM interrupt\n");
		वापस;
	पूर्ण

	hird = (glpmcfg & GLPMCFG_HIRD_MASK) >> GLPMCFG_HIRD_SHIFT;
	hird_thres = (glpmcfg & GLPMCFG_HIRD_THRES_MASK &
			~GLPMCFG_HIRD_THRES_EN) >> GLPMCFG_HIRD_THRES_SHIFT;
	hird_thres_en = glpmcfg & GLPMCFG_HIRD_THRES_EN;
	enslpm = glpmcfg & GLPMCFG_ENBLSLPM;

	अगर (dwc2_is_device_mode(hsotg)) अणु
		dev_dbg(hsotg->dev, "HIRD_THRES_EN = %d\n", hird_thres_en);

		अगर (hird_thres_en && hird >= hird_thres) अणु
			dev_dbg(hsotg->dev, "L1 with utmi_l1_suspend_n\n");
		पूर्ण अन्यथा अगर (enslpm) अणु
			dev_dbg(hsotg->dev, "L1 with utmi_sleep_n\n");
		पूर्ण अन्यथा अणु
			dev_dbg(hsotg->dev, "Entering Sleep with L1 Gating\n");

			pcgcctl = dwc2_पढ़ोl(hsotg, PCGCTL);
			pcgcctl |= PCGCTL_ENBL_SLEEP_GATING;
			dwc2_ग_लिखोl(hsotg, pcgcctl, PCGCTL);
		पूर्ण
		/**
		 * Examine prt_sleep_sts after TL1TokenTetry period max (10 us)
		 */
		udelay(10);

		glpmcfg = dwc2_पढ़ोl(hsotg, GLPMCFG);

		अगर (glpmcfg & GLPMCFG_SLPSTS) अणु
			/* Save the current state */
			hsotg->lx_state = DWC2_L1;
			dev_dbg(hsotg->dev,
				"Core is in L1 sleep glpmcfg=%08x\n", glpmcfg);

			/* Inक्रमm gadget that we are in L1 state */
			call_gadget(hsotg, suspend);
		पूर्ण
	पूर्ण
पूर्ण

#घोषणा GINTMSK_COMMON	(GINTSTS_WKUPINT | GINTSTS_SESSREQINT |		\
			 GINTSTS_CONIDSTSCHNG | GINTSTS_OTGINT |	\
			 GINTSTS_MODEMIS | GINTSTS_DISCONNINT |		\
			 GINTSTS_USBSUSP | GINTSTS_PRTINT |		\
			 GINTSTS_LPMTRANRCVD)

/*
 * This function वापसs the Core Interrupt रेजिस्टर
 */
अटल u32 dwc2_पढ़ो_common_पूर्णांकr(काष्ठा dwc2_hsotg *hsotg)
अणु
	u32 gपूर्णांकsts;
	u32 gपूर्णांकmsk;
	u32 gahbcfg;
	u32 gपूर्णांकmsk_common = GINTMSK_COMMON;

	gपूर्णांकsts = dwc2_पढ़ोl(hsotg, GINTSTS);
	gपूर्णांकmsk = dwc2_पढ़ोl(hsotg, GINTMSK);
	gahbcfg = dwc2_पढ़ोl(hsotg, GAHBCFG);

	/* If any common पूर्णांकerrupts set */
	अगर (gपूर्णांकsts & gपूर्णांकmsk_common)
		dev_dbg(hsotg->dev, "gintsts=%08x  gintmsk=%08x\n",
			gपूर्णांकsts, gपूर्णांकmsk);

	अगर (gahbcfg & GAHBCFG_GLBL_INTR_EN)
		वापस gपूर्णांकsts & gपूर्णांकmsk & gपूर्णांकmsk_common;
	अन्यथा
		वापस 0;
पूर्ण

/**
 * dwc_handle_gpwrdn_disc_det() - Handles the gpwrdn disconnect detect.
 * Exits hibernation without restoring रेजिस्टरs.
 *
 * @hsotg: Programming view of DWC_otg controller
 * @gpwrdn: GPWRDN रेजिस्टर
 */
अटल अंतरभूत व्योम dwc_handle_gpwrdn_disc_det(काष्ठा dwc2_hsotg *hsotg,
					      u32 gpwrdn)
अणु
	u32 gpwrdn_पंचांगp;

	/* Switch-on voltage to the core */
	gpwrdn_पंचांगp = dwc2_पढ़ोl(hsotg, GPWRDN);
	gpwrdn_पंचांगp &= ~GPWRDN_PWRDNSWTCH;
	dwc2_ग_लिखोl(hsotg, gpwrdn_पंचांगp, GPWRDN);
	udelay(5);

	/* Reset core */
	gpwrdn_पंचांगp = dwc2_पढ़ोl(hsotg, GPWRDN);
	gpwrdn_पंचांगp &= ~GPWRDN_PWRDNRSTN;
	dwc2_ग_लिखोl(hsotg, gpwrdn_पंचांगp, GPWRDN);
	udelay(5);

	/* Disable Power Down Clamp */
	gpwrdn_पंचांगp = dwc2_पढ़ोl(hsotg, GPWRDN);
	gpwrdn_पंचांगp &= ~GPWRDN_PWRDNCLMP;
	dwc2_ग_लिखोl(hsotg, gpwrdn_पंचांगp, GPWRDN);
	udelay(5);

	/* Deनिश्चित reset core */
	gpwrdn_पंचांगp = dwc2_पढ़ोl(hsotg, GPWRDN);
	gpwrdn_पंचांगp |= GPWRDN_PWRDNRSTN;
	dwc2_ग_लिखोl(hsotg, gpwrdn_पंचांगp, GPWRDN);
	udelay(5);

	/* Disable PMU पूर्णांकerrupt */
	gpwrdn_पंचांगp = dwc2_पढ़ोl(hsotg, GPWRDN);
	gpwrdn_पंचांगp &= ~GPWRDN_PMUINTSEL;
	dwc2_ग_लिखोl(hsotg, gpwrdn_पंचांगp, GPWRDN);

	/* De-निश्चित Wakeup Logic */
	gpwrdn_पंचांगp = dwc2_पढ़ोl(hsotg, GPWRDN);
	gpwrdn_पंचांगp &= ~GPWRDN_PMUACTV;
	dwc2_ग_लिखोl(hsotg, gpwrdn_पंचांगp, GPWRDN);

	hsotg->hibernated = 0;
	hsotg->bus_suspended = 0;

	अगर (gpwrdn & GPWRDN_IDSTS) अणु
		hsotg->op_state = OTG_STATE_B_PERIPHERAL;
		dwc2_core_init(hsotg, false);
		dwc2_enable_global_पूर्णांकerrupts(hsotg);
		dwc2_hsotg_core_init_disconnected(hsotg, false);
		dwc2_hsotg_core_connect(hsotg);
	पूर्ण अन्यथा अणु
		hsotg->op_state = OTG_STATE_A_HOST;

		/* Initialize the Core क्रम Host mode */
		dwc2_core_init(hsotg, false);
		dwc2_enable_global_पूर्णांकerrupts(hsotg);
		dwc2_hcd_start(hsotg);
	पूर्ण
पूर्ण

/*
 * GPWRDN पूर्णांकerrupt handler.
 *
 * The GPWRDN पूर्णांकerrupts are those that occur in both Host and
 * Device mode जबतक core is in hibernated state.
 */
अटल पूर्णांक dwc2_handle_gpwrdn_पूर्णांकr(काष्ठा dwc2_hsotg *hsotg)
अणु
	u32 gpwrdn;
	पूर्णांक linestate;
	पूर्णांक ret = 0;

	gpwrdn = dwc2_पढ़ोl(hsotg, GPWRDN);
	/* clear all पूर्णांकerrupt */
	dwc2_ग_लिखोl(hsotg, gpwrdn, GPWRDN);
	linestate = (gpwrdn & GPWRDN_LINESTATE_MASK) >> GPWRDN_LINESTATE_SHIFT;
	dev_dbg(hsotg->dev,
		"%s: dwc2_handle_gpwrdwn_intr called gpwrdn= %08x\n", __func__,
		gpwrdn);

	अगर ((gpwrdn & GPWRDN_DISCONN_DET) &&
	    (gpwrdn & GPWRDN_DISCONN_DET_MSK) && !linestate) अणु
		dev_dbg(hsotg->dev, "%s: GPWRDN_DISCONN_DET\n", __func__);
		/*
		 * Call disconnect detect function to निकास from
		 * hibernation
		 */
		dwc_handle_gpwrdn_disc_det(hsotg, gpwrdn);
	पूर्ण अन्यथा अगर ((gpwrdn & GPWRDN_LNSTSCHG) &&
		   (gpwrdn & GPWRDN_LNSTSCHG_MSK) && linestate) अणु
		dev_dbg(hsotg->dev, "%s: GPWRDN_LNSTSCHG\n", __func__);
		अगर (hsotg->hw_params.hibernation &&
		    hsotg->hibernated) अणु
			अगर (gpwrdn & GPWRDN_IDSTS) अणु
				ret = dwc2_निकास_hibernation(hsotg, 0, 0, 0);
				अगर (ret)
					dev_err(hsotg->dev,
						"exit hibernation failed.\n");
				call_gadget(hsotg, resume);
			पूर्ण अन्यथा अणु
				ret = dwc2_निकास_hibernation(hsotg, 1, 0, 1);
				अगर (ret)
					dev_err(hsotg->dev,
						"exit hibernation failed.\n");
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर ((gpwrdn & GPWRDN_RST_DET) &&
		   (gpwrdn & GPWRDN_RST_DET_MSK)) अणु
		dev_dbg(hsotg->dev, "%s: GPWRDN_RST_DET\n", __func__);
		अगर (!linestate) अणु
			ret = dwc2_निकास_hibernation(hsotg, 0, 1, 0);
			अगर (ret)
				dev_err(hsotg->dev,
					"exit hibernation failed.\n");
		पूर्ण
	पूर्ण अन्यथा अगर ((gpwrdn & GPWRDN_STS_CHGINT) &&
		   (gpwrdn & GPWRDN_STS_CHGINT_MSK)) अणु
		dev_dbg(hsotg->dev, "%s: GPWRDN_STS_CHGINT\n", __func__);
		/*
		 * As GPWRDN_STS_CHGINT निकास from hibernation flow is
		 * the same as in GPWRDN_DISCONN_DET flow. Call
		 * disconnect detect helper function to निकास from
		 * hibernation.
		 */
		dwc_handle_gpwrdn_disc_det(hsotg, gpwrdn);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Common पूर्णांकerrupt handler
 *
 * The common पूर्णांकerrupts are those that occur in both Host and Device mode.
 * This handler handles the following पूर्णांकerrupts:
 * - Mode Mismatch Interrupt
 * - OTG Interrupt
 * - Connector ID Status Change Interrupt
 * - Disconnect Interrupt
 * - Session Request Interrupt
 * - Resume / Remote Wakeup Detected Interrupt
 * - Suspend Interrupt
 */
irqवापस_t dwc2_handle_common_पूर्णांकr(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा dwc2_hsotg *hsotg = dev;
	u32 gपूर्णांकsts;
	irqवापस_t retval = IRQ_NONE;

	spin_lock(&hsotg->lock);

	अगर (!dwc2_is_controller_alive(hsotg)) अणु
		dev_warn(hsotg->dev, "Controller is dead\n");
		जाओ out;
	पूर्ण

	/* Reading current frame number value in device or host modes. */
	अगर (dwc2_is_device_mode(hsotg))
		hsotg->frame_number = (dwc2_पढ़ोl(hsotg, DSTS)
				       & DSTS_SOFFN_MASK) >> DSTS_SOFFN_SHIFT;
	अन्यथा
		hsotg->frame_number = (dwc2_पढ़ोl(hsotg, HFNUM)
				       & HFNUM_FRNUM_MASK) >> HFNUM_FRNUM_SHIFT;

	gपूर्णांकsts = dwc2_पढ़ो_common_पूर्णांकr(hsotg);
	अगर (gपूर्णांकsts & ~GINTSTS_PRTINT)
		retval = IRQ_HANDLED;

	/* In हाल of hibernated state gपूर्णांकsts must not work */
	अगर (hsotg->hibernated) अणु
		dwc2_handle_gpwrdn_पूर्णांकr(hsotg);
		retval = IRQ_HANDLED;
		जाओ out;
	पूर्ण

	अगर (gपूर्णांकsts & GINTSTS_MODEMIS)
		dwc2_handle_mode_mismatch_पूर्णांकr(hsotg);
	अगर (gपूर्णांकsts & GINTSTS_OTGINT)
		dwc2_handle_otg_पूर्णांकr(hsotg);
	अगर (gपूर्णांकsts & GINTSTS_CONIDSTSCHNG)
		dwc2_handle_conn_id_status_change_पूर्णांकr(hsotg);
	अगर (gपूर्णांकsts & GINTSTS_DISCONNINT)
		dwc2_handle_disconnect_पूर्णांकr(hsotg);
	अगर (gपूर्णांकsts & GINTSTS_SESSREQINT)
		dwc2_handle_session_req_पूर्णांकr(hsotg);
	अगर (gपूर्णांकsts & GINTSTS_WKUPINT)
		dwc2_handle_wakeup_detected_पूर्णांकr(hsotg);
	अगर (gपूर्णांकsts & GINTSTS_USBSUSP)
		dwc2_handle_usb_suspend_पूर्णांकr(hsotg);
	अगर (gपूर्णांकsts & GINTSTS_LPMTRANRCVD)
		dwc2_handle_lpm_पूर्णांकr(hsotg);

	अगर (gपूर्णांकsts & GINTSTS_PRTINT) अणु
		/*
		 * The port पूर्णांकerrupt occurs जबतक in device mode with HPRT0
		 * Port Enable/Disable
		 */
		अगर (dwc2_is_device_mode(hsotg)) अणु
			dev_dbg(hsotg->dev,
				" --Port interrupt received in Device mode--\n");
			dwc2_handle_usb_port_पूर्णांकr(hsotg);
			retval = IRQ_HANDLED;
		पूर्ण
	पूर्ण

out:
	spin_unlock(&hsotg->lock);
	वापस retval;
पूर्ण
