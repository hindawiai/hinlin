<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright 2008-2009 Freescale Semiconductor, Inc. All Rights Reserved.
 * Copyright 2010 Orex Computed Radiography
 */

/*
 * This driver uses the 47-bit 32 kHz counter in the Freescale DryIce block
 * to implement a Linux RTC. Times and alarms are truncated to seconds.
 * Since the RTC framework perक्रमms API locking via rtc->ops_lock the
 * only simultaneous accesses we need to deal with is updating DryIce
 * रेजिस्टरs जबतक servicing an alarm.
 *
 * Note that पढ़ोing the DSR (DryIce Status Register) स्वतःmatically clears
 * the WCF (Write Complete Flag). All DryIce ग_लिखोs are synchronized to the
 * LP (Low Power) करोमुख्य and set the WCF upon completion. Writes to the
 * DIER (DryIce Interrupt Enable Register) are the only exception. These
 * occur at normal bus speeds and करो not set WCF.  Periodic पूर्णांकerrupts are
 * not supported by the hardware.
 */

#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/rtc.h>
#समावेश <linux/sched.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/of.h>

/* DryIce Register Definitions */

#घोषणा DTCMR     0x00           /* Time Counter MSB Reg */
#घोषणा DTCLR     0x04           /* Time Counter LSB Reg */

#घोषणा DCAMR     0x08           /* Clock Alarm MSB Reg */
#घोषणा DCALR     0x0c           /* Clock Alarm LSB Reg */
#घोषणा DCAMR_UNSET  0xFFFFFFFF  /* करोomsday - 1 sec */

#घोषणा DCR       0x10           /* Control Reg */
#घोषणा DCR_TDCHL (1 << 30)      /* Tamper-detect configuration hard lock */
#घोषणा DCR_TDCSL (1 << 29)      /* Tamper-detect configuration soft lock */
#घोषणा DCR_KSSL  (1 << 27)      /* Key-select soft lock */
#घोषणा DCR_MCHL  (1 << 20)      /* Monotonic-counter hard lock */
#घोषणा DCR_MCSL  (1 << 19)      /* Monotonic-counter soft lock */
#घोषणा DCR_TCHL  (1 << 18)      /* Timer-counter hard lock */
#घोषणा DCR_TCSL  (1 << 17)      /* Timer-counter soft lock */
#घोषणा DCR_FSHL  (1 << 16)      /* Failure state hard lock */
#घोषणा DCR_TCE   (1 << 3)       /* Time Counter Enable */
#घोषणा DCR_MCE   (1 << 2)       /* Monotonic Counter Enable */

#घोषणा DSR       0x14           /* Status Reg */
#घोषणा DSR_WTD   (1 << 23)      /* Wire-mesh tamper detected */
#घोषणा DSR_ETBD  (1 << 22)      /* External tamper B detected */
#घोषणा DSR_ETAD  (1 << 21)      /* External tamper A detected */
#घोषणा DSR_EBD   (1 << 20)      /* External boot detected */
#घोषणा DSR_SAD   (1 << 19)      /* SCC alarm detected */
#घोषणा DSR_TTD   (1 << 18)      /* Temperature tamper detected */
#घोषणा DSR_CTD   (1 << 17)      /* Clock tamper detected */
#घोषणा DSR_VTD   (1 << 16)      /* Voltage tamper detected */
#घोषणा DSR_WBF   (1 << 10)      /* Write Busy Flag (synchronous) */
#घोषणा DSR_WNF   (1 << 9)       /* Write Next Flag (synchronous) */
#घोषणा DSR_WCF   (1 << 8)       /* Write Complete Flag (synchronous)*/
#घोषणा DSR_WEF   (1 << 7)       /* Write Error Flag */
#घोषणा DSR_CAF   (1 << 4)       /* Clock Alarm Flag */
#घोषणा DSR_MCO   (1 << 3)       /* monotonic counter overflow */
#घोषणा DSR_TCO   (1 << 2)       /* समय counter overflow */
#घोषणा DSR_NVF   (1 << 1)       /* Non-Valid Flag */
#घोषणा DSR_SVF   (1 << 0)       /* Security Violation Flag */

#घोषणा DIER      0x18           /* Interrupt Enable Reg (synchronous) */
#घोषणा DIER_WNIE (1 << 9)       /* Write Next Interrupt Enable */
#घोषणा DIER_WCIE (1 << 8)       /* Write Complete Interrupt Enable */
#घोषणा DIER_WEIE (1 << 7)       /* Write Error Interrupt Enable */
#घोषणा DIER_CAIE (1 << 4)       /* Clock Alarm Interrupt Enable */
#घोषणा DIER_SVIE (1 << 0)       /* Security-violation Interrupt Enable */

#घोषणा DMCR      0x1c           /* DryIce Monotonic Counter Reg */

#घोषणा DTCR      0x28           /* DryIce Tamper Configuration Reg */
#घोषणा DTCR_MOE  (1 << 9)       /* monotonic overflow enabled */
#घोषणा DTCR_TOE  (1 << 8)       /* समय overflow enabled */
#घोषणा DTCR_WTE  (1 << 7)       /* wire-mesh tamper enabled */
#घोषणा DTCR_ETBE (1 << 6)       /* बाह्यal B tamper enabled */
#घोषणा DTCR_ETAE (1 << 5)       /* बाह्यal A tamper enabled */
#घोषणा DTCR_EBE  (1 << 4)       /* बाह्यal boot tamper enabled */
#घोषणा DTCR_SAIE (1 << 3)       /* SCC enabled */
#घोषणा DTCR_TTE  (1 << 2)       /* temperature tamper enabled */
#घोषणा DTCR_CTE  (1 << 1)       /* घड़ी tamper enabled */
#घोषणा DTCR_VTE  (1 << 0)       /* voltage tamper enabled */

#घोषणा DGPR      0x3c           /* DryIce General Purpose Reg */

/**
 * काष्ठा imxdi_dev - निजी imxdi rtc data
 * @pdev: poपूर्णांकer to platक्रमm dev
 * @rtc: poपूर्णांकer to rtc काष्ठा
 * @ioaddr: IO रेजिस्टरs poपूर्णांकer
 * @clk: input reference घड़ी
 * @dsr: copy of the DSR रेजिस्टर
 * @irq_lock: पूर्णांकerrupt enable रेजिस्टर (DIER) lock
 * @ग_लिखो_रुको: रेजिस्टरs ग_लिखो complete queue
 * @ग_लिखो_mutex: serialize रेजिस्टरs ग_लिखो
 * @work: schedule alarm work
 */
काष्ठा imxdi_dev अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा rtc_device *rtc;
	व्योम __iomem *ioaddr;
	काष्ठा clk *clk;
	u32 dsr;
	spinlock_t irq_lock;
	रुको_queue_head_t ग_लिखो_रुको;
	काष्ठा mutex ग_लिखो_mutex;
	काष्ठा work_काष्ठा work;
पूर्ण;

/* Some background:
 *
 * The DryIce unit is a complex security/tamper monitor device. To be able करो
 * its job in a useful manner it runs a bigger statemachine to bring it पूर्णांकo
 * security/tamper failure state and once again to bring it out of this state.
 *
 * This unit can be in one of three states:
 *
 * - "NON-VALID STATE"
 *   always after the battery घातer was हटाओd
 * - "FAILURE STATE"
 *   अगर one of the enabled security events has happened
 * - "VALID STATE"
 *   अगर the unit works as expected
 *
 * Everything stops when the unit enters the failure state including the RTC
 * counter (to be able to detect the समय the security event happened).
 *
 * The following events (when enabled) let the DryIce unit enter the failure
 * state:
 *
 * - wire-mesh-tamper detect
 * - बाह्यal tamper B detect
 * - बाह्यal tamper A detect
 * - temperature tamper detect
 * - घड़ी tamper detect
 * - voltage tamper detect
 * - RTC counter overflow
 * - monotonic counter overflow
 * - बाह्यal boot
 *
 * If we find the DryIce unit in "FAILURE STATE" and the TDCHL cleared, we
 * can only detect this state. In this हाल the unit is completely locked and
 * must क्रमce a second "SYSTEM POR" to bring the DryIce पूर्णांकo the
 * "NON-VALID STATE" + "FAILURE STATE" where a recovery is possible.
 * If the TDCHL is set in the "FAILURE STATE" we are out of luck. In this हाल
 * a battery घातer cycle is required.
 *
 * In the "NON-VALID STATE" + "FAILURE STATE" we can clear the "FAILURE STATE"
 * and recover the DryIce unit. By clearing the "NON-VALID STATE" as the last
 * task, we bring back this unit पूर्णांकo lअगरe.
 */

/*
 * Do a ग_लिखो पूर्णांकo the unit without पूर्णांकerrupt support.
 * We करो not need to check the WEF here, because the only reason this kind of
 * ग_लिखो error can happen is अगर we ग_लिखो to the unit twice within the 122 us
 * पूर्णांकerval. This cannot happen, since we are using this function only जबतक
 * setting up the unit.
 */
अटल व्योम di_ग_लिखो_busy_रुको(स्थिर काष्ठा imxdi_dev *imxdi, u32 val,
			       अचिन्हित reg)
अणु
	/* करो the रेजिस्टर ग_लिखो */
	ग_लिखोl(val, imxdi->ioaddr + reg);

	/*
	 * now it takes four 32,768 kHz घड़ी cycles to take
	 * the change पूर्णांकo effect = 122 us
	 */
	usleep_range(130, 200);
पूर्ण

अटल व्योम di_report_tamper_info(काष्ठा imxdi_dev *imxdi,  u32 dsr)
अणु
	u32 dtcr;

	dtcr = पढ़ोl(imxdi->ioaddr + DTCR);

	dev_emerg(&imxdi->pdev->dev, "DryIce tamper event detected\n");
	/* the following flags क्रमce a transition पूर्णांकo the "FAILURE STATE" */
	अगर (dsr & DSR_VTD)
		dev_emerg(&imxdi->pdev->dev, "%sVoltage Tamper Event\n",
			  dtcr & DTCR_VTE ? "" : "Spurious ");

	अगर (dsr & DSR_CTD)
		dev_emerg(&imxdi->pdev->dev, "%s32768 Hz Clock Tamper Event\n",
			  dtcr & DTCR_CTE ? "" : "Spurious ");

	अगर (dsr & DSR_TTD)
		dev_emerg(&imxdi->pdev->dev, "%sTemperature Tamper Event\n",
			  dtcr & DTCR_TTE ? "" : "Spurious ");

	अगर (dsr & DSR_SAD)
		dev_emerg(&imxdi->pdev->dev,
			  "%sSecure Controller Alarm Event\n",
			  dtcr & DTCR_SAIE ? "" : "Spurious ");

	अगर (dsr & DSR_EBD)
		dev_emerg(&imxdi->pdev->dev, "%sExternal Boot Tamper Event\n",
			  dtcr & DTCR_EBE ? "" : "Spurious ");

	अगर (dsr & DSR_ETAD)
		dev_emerg(&imxdi->pdev->dev, "%sExternal Tamper A Event\n",
			  dtcr & DTCR_ETAE ? "" : "Spurious ");

	अगर (dsr & DSR_ETBD)
		dev_emerg(&imxdi->pdev->dev, "%sExternal Tamper B Event\n",
			  dtcr & DTCR_ETBE ? "" : "Spurious ");

	अगर (dsr & DSR_WTD)
		dev_emerg(&imxdi->pdev->dev, "%sWire-mesh Tamper Event\n",
			  dtcr & DTCR_WTE ? "" : "Spurious ");

	अगर (dsr & DSR_MCO)
		dev_emerg(&imxdi->pdev->dev,
			  "%sMonotonic-counter Overflow Event\n",
			  dtcr & DTCR_MOE ? "" : "Spurious ");

	अगर (dsr & DSR_TCO)
		dev_emerg(&imxdi->pdev->dev, "%sTimer-counter Overflow Event\n",
			  dtcr & DTCR_TOE ? "" : "Spurious ");
पूर्ण

अटल व्योम di_what_is_to_be_करोne(काष्ठा imxdi_dev *imxdi,
				  स्थिर अक्षर *घातer_supply)
अणु
	dev_emerg(&imxdi->pdev->dev, "Please cycle the %s power supply in order to get the DryIce/RTC unit working again\n",
		  घातer_supply);
पूर्ण

अटल पूर्णांक di_handle_failure_state(काष्ठा imxdi_dev *imxdi, u32 dsr)
अणु
	u32 dcr;

	dev_dbg(&imxdi->pdev->dev, "DSR register reports: %08X\n", dsr);

	/* report the cause */
	di_report_tamper_info(imxdi, dsr);

	dcr = पढ़ोl(imxdi->ioaddr + DCR);

	अगर (dcr & DCR_FSHL) अणु
		/* we are out of luck */
		di_what_is_to_be_करोne(imxdi, "battery");
		वापस -ENODEV;
	पूर्ण
	/*
	 * with the next SYSTEM POR we will transit from the "FAILURE STATE"
	 * पूर्णांकo the "NON-VALID STATE" + "FAILURE STATE"
	 */
	di_what_is_to_be_करोne(imxdi, "main");

	वापस -ENODEV;
पूर्ण

अटल पूर्णांक di_handle_valid_state(काष्ठा imxdi_dev *imxdi, u32 dsr)
अणु
	/* initialize alarm */
	di_ग_लिखो_busy_रुको(imxdi, DCAMR_UNSET, DCAMR);
	di_ग_लिखो_busy_रुको(imxdi, 0, DCALR);

	/* clear alarm flag */
	अगर (dsr & DSR_CAF)
		di_ग_लिखो_busy_रुको(imxdi, DSR_CAF, DSR);

	वापस 0;
पूर्ण

अटल पूर्णांक di_handle_invalid_state(काष्ठा imxdi_dev *imxdi, u32 dsr)
अणु
	u32 dcr, sec;

	/*
	 * lets disable all sources which can क्रमce the DryIce unit पूर्णांकo
	 * the "FAILURE STATE" क्रम now
	 */
	di_ग_लिखो_busy_रुको(imxdi, 0x00000000, DTCR);
	/* and lets protect them at runसमय from any change */
	di_ग_लिखो_busy_रुको(imxdi, DCR_TDCSL, DCR);

	sec = पढ़ोl(imxdi->ioaddr + DTCMR);
	अगर (sec != 0)
		dev_warn(&imxdi->pdev->dev,
			 "The security violation has happened at %u seconds\n",
			 sec);
	/*
	 * the समयr cannot be set/modअगरied अगर
	 * - the TCHL or TCSL bit is set in DCR
	 */
	dcr = पढ़ोl(imxdi->ioaddr + DCR);
	अगर (!(dcr & DCR_TCE)) अणु
		अगर (dcr & DCR_TCHL) अणु
			/* we are out of luck */
			di_what_is_to_be_करोne(imxdi, "battery");
			वापस -ENODEV;
		पूर्ण
		अगर (dcr & DCR_TCSL) अणु
			di_what_is_to_be_करोne(imxdi, "main");
			वापस -ENODEV;
		पूर्ण
	पूर्ण
	/*
	 * - the समयr counter stops/is stopped अगर
	 *   - its overflow flag is set (TCO in DSR)
	 *      -> clear overflow bit to make it count again
	 *   - NVF is set in DSR
	 *      -> clear non-valid bit to make it count again
	 *   - its TCE (DCR) is cleared
	 *      -> set TCE to make it count
	 *   - it was never set beक्रमe
	 *      -> ग_लिखो a समय पूर्णांकo it (required again अगर the NVF was set)
	 */
	/* state handled */
	di_ग_लिखो_busy_रुको(imxdi, DSR_NVF, DSR);
	/* clear overflow flag */
	di_ग_लिखो_busy_रुको(imxdi, DSR_TCO, DSR);
	/* enable the counter */
	di_ग_लिखो_busy_रुको(imxdi, dcr | DCR_TCE, DCR);
	/* set and trigger it to make it count */
	di_ग_लिखो_busy_रुको(imxdi, sec, DTCMR);

	/* now prepare क्रम the valid state */
	वापस di_handle_valid_state(imxdi, __raw_पढ़ोl(imxdi->ioaddr + DSR));
पूर्ण

अटल पूर्णांक di_handle_invalid_and_failure_state(काष्ठा imxdi_dev *imxdi, u32 dsr)
अणु
	u32 dcr;

	/*
	 * now we must first हटाओ the tamper sources in order to get the
	 * device out of the "FAILURE STATE"
	 * To disable any of the following sources we need to modअगरy the DTCR
	 */
	अगर (dsr & (DSR_WTD | DSR_ETBD | DSR_ETAD | DSR_EBD | DSR_SAD |
			DSR_TTD | DSR_CTD | DSR_VTD | DSR_MCO | DSR_TCO)) अणु
		dcr = __raw_पढ़ोl(imxdi->ioaddr + DCR);
		अगर (dcr & DCR_TDCHL) अणु
			/*
			 * the tamper रेजिस्टर is locked. We cannot disable the
			 * tamper detection. The TDCHL can only be reset by a
			 * DRYICE POR, but we cannot क्रमce a DRYICE POR in
			 * software because we are still in "FAILURE STATE".
			 * We need a DRYICE POR via battery घातer cycling....
			 */
			/*
			 * out of luck!
			 * we cannot disable them without a DRYICE POR
			 */
			di_what_is_to_be_करोne(imxdi, "battery");
			वापस -ENODEV;
		पूर्ण
		अगर (dcr & DCR_TDCSL) अणु
			/* a soft lock can be हटाओd by a SYSTEM POR */
			di_what_is_to_be_करोne(imxdi, "main");
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	/* disable all sources */
	di_ग_लिखो_busy_रुको(imxdi, 0x00000000, DTCR);

	/* clear the status bits now */
	di_ग_लिखो_busy_रुको(imxdi, dsr & (DSR_WTD | DSR_ETBD | DSR_ETAD |
			DSR_EBD | DSR_SAD | DSR_TTD | DSR_CTD | DSR_VTD |
			DSR_MCO | DSR_TCO), DSR);

	dsr = पढ़ोl(imxdi->ioaddr + DSR);
	अगर ((dsr & ~(DSR_NVF | DSR_SVF | DSR_WBF | DSR_WNF |
			DSR_WCF | DSR_WEF)) != 0)
		dev_warn(&imxdi->pdev->dev,
			 "There are still some sources of pain in DSR: %08x!\n",
			 dsr & ~(DSR_NVF | DSR_SVF | DSR_WBF | DSR_WNF |
				 DSR_WCF | DSR_WEF));

	/*
	 * now we are trying to clear the "Security-violation flag" to
	 * get the DryIce out of this state
	 */
	di_ग_लिखो_busy_रुको(imxdi, DSR_SVF, DSR);

	/* success? */
	dsr = पढ़ोl(imxdi->ioaddr + DSR);
	अगर (dsr & DSR_SVF) अणु
		dev_crit(&imxdi->pdev->dev,
			 "Cannot clear the security violation flag. We are ending up in an endless loop!\n");
		/* last resort */
		di_what_is_to_be_करोne(imxdi, "battery");
		वापस -ENODEV;
	पूर्ण

	/*
	 * now we have left the "FAILURE STATE" and ending up in the
	 * "NON-VALID STATE" समय to recover everything
	 */
	वापस di_handle_invalid_state(imxdi, dsr);
पूर्ण

अटल पूर्णांक di_handle_state(काष्ठा imxdi_dev *imxdi)
अणु
	पूर्णांक rc;
	u32 dsr;

	dsr = पढ़ोl(imxdi->ioaddr + DSR);

	चयन (dsr & (DSR_NVF | DSR_SVF)) अणु
	हाल DSR_NVF:
		dev_warn(&imxdi->pdev->dev, "Invalid stated unit detected\n");
		rc = di_handle_invalid_state(imxdi, dsr);
		अवरोध;
	हाल DSR_SVF:
		dev_warn(&imxdi->pdev->dev, "Failure stated unit detected\n");
		rc = di_handle_failure_state(imxdi, dsr);
		अवरोध;
	हाल DSR_NVF | DSR_SVF:
		dev_warn(&imxdi->pdev->dev,
			 "Failure+Invalid stated unit detected\n");
		rc = di_handle_invalid_and_failure_state(imxdi, dsr);
		अवरोध;
	शेष:
		dev_notice(&imxdi->pdev->dev, "Unlocked unit detected\n");
		rc = di_handle_valid_state(imxdi, dsr);
	पूर्ण

	वापस rc;
पूर्ण

/*
 * enable a dryice पूर्णांकerrupt
 */
अटल व्योम di_पूर्णांक_enable(काष्ठा imxdi_dev *imxdi, u32 पूर्णांकr)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&imxdi->irq_lock, flags);
	ग_लिखोl(पढ़ोl(imxdi->ioaddr + DIER) | पूर्णांकr,
	       imxdi->ioaddr + DIER);
	spin_unlock_irqrestore(&imxdi->irq_lock, flags);
पूर्ण

/*
 * disable a dryice पूर्णांकerrupt
 */
अटल व्योम di_पूर्णांक_disable(काष्ठा imxdi_dev *imxdi, u32 पूर्णांकr)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&imxdi->irq_lock, flags);
	ग_लिखोl(पढ़ोl(imxdi->ioaddr + DIER) & ~पूर्णांकr,
	       imxdi->ioaddr + DIER);
	spin_unlock_irqrestore(&imxdi->irq_lock, flags);
पूर्ण

/*
 * This function attempts to clear the dryice ग_लिखो-error flag.
 *
 * A dryice ग_लिखो error is similar to a bus fault and should not occur in
 * normal operation.  Clearing the flag requires another ग_लिखो, so the root
 * cause of the problem may need to be fixed beक्रमe the flag can be cleared.
 */
अटल व्योम clear_ग_लिखो_error(काष्ठा imxdi_dev *imxdi)
अणु
	पूर्णांक cnt;

	dev_warn(&imxdi->pdev->dev, "WARNING: Register write error!\n");

	/* clear the ग_लिखो error flag */
	ग_लिखोl(DSR_WEF, imxdi->ioaddr + DSR);

	/* रुको क्रम it to take effect */
	क्रम (cnt = 0; cnt < 1000; cnt++) अणु
		अगर ((पढ़ोl(imxdi->ioaddr + DSR) & DSR_WEF) == 0)
			वापस;
		udelay(10);
	पूर्ण
	dev_err(&imxdi->pdev->dev,
			"ERROR: Cannot clear write-error flag!\n");
पूर्ण

/*
 * Write a dryice रेजिस्टर and रुको until it completes.
 *
 * This function uses पूर्णांकerrupts to determine when the
 * ग_लिखो has completed.
 */
अटल पूर्णांक di_ग_लिखो_रुको(काष्ठा imxdi_dev *imxdi, u32 val, पूर्णांक reg)
अणु
	पूर्णांक ret;
	पूर्णांक rc = 0;

	/* serialize रेजिस्टर ग_लिखोs */
	mutex_lock(&imxdi->ग_लिखो_mutex);

	/* enable the ग_लिखो-complete पूर्णांकerrupt */
	di_पूर्णांक_enable(imxdi, DIER_WCIE);

	imxdi->dsr = 0;

	/* करो the रेजिस्टर ग_लिखो */
	ग_लिखोl(val, imxdi->ioaddr + reg);

	/* रुको क्रम the ग_लिखो to finish */
	ret = रुको_event_पूर्णांकerruptible_समयout(imxdi->ग_लिखो_रुको,
			imxdi->dsr & (DSR_WCF | DSR_WEF), msecs_to_jअगरfies(1));
	अगर (ret < 0) अणु
		rc = ret;
		जाओ out;
	पूर्ण अन्यथा अगर (ret == 0) अणु
		dev_warn(&imxdi->pdev->dev,
				"Write-wait timeout "
				"val = 0x%08x reg = 0x%08x\n", val, reg);
	पूर्ण

	/* check क्रम ग_लिखो error */
	अगर (imxdi->dsr & DSR_WEF) अणु
		clear_ग_लिखो_error(imxdi);
		rc = -EIO;
	पूर्ण

out:
	mutex_unlock(&imxdi->ग_लिखो_mutex);

	वापस rc;
पूर्ण

/*
 * पढ़ो the seconds portion of the current समय from the dryice समय counter
 */
अटल पूर्णांक dryice_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा imxdi_dev *imxdi = dev_get_drvdata(dev);
	अचिन्हित दीर्घ now;

	now = पढ़ोl(imxdi->ioaddr + DTCMR);
	rtc_समय64_to_पंचांग(now, पंचांग);

	वापस 0;
पूर्ण

/*
 * set the seconds portion of dryice समय counter and clear the
 * fractional part.
 */
अटल पूर्णांक dryice_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा imxdi_dev *imxdi = dev_get_drvdata(dev);
	u32 dcr, dsr;
	पूर्णांक rc;

	dcr = पढ़ोl(imxdi->ioaddr + DCR);
	dsr = पढ़ोl(imxdi->ioaddr + DSR);

	अगर (!(dcr & DCR_TCE) || (dsr & DSR_SVF)) अणु
		अगर (dcr & DCR_TCHL) अणु
			/* we are even more out of luck */
			di_what_is_to_be_करोne(imxdi, "battery");
			वापस -EPERM;
		पूर्ण
		अगर ((dcr & DCR_TCSL) || (dsr & DSR_SVF)) अणु
			/* we are out of luck क्रम now */
			di_what_is_to_be_करोne(imxdi, "main");
			वापस -EPERM;
		पूर्ण
	पूर्ण

	/* zero the fractional part first */
	rc = di_ग_लिखो_रुको(imxdi, 0, DTCLR);
	अगर (rc != 0)
		वापस rc;

	rc = di_ग_लिखो_रुको(imxdi, rtc_पंचांग_to_समय64(पंचांग), DTCMR);
	अगर (rc != 0)
		वापस rc;

	वापस di_ग_लिखो_रुको(imxdi, पढ़ोl(imxdi->ioaddr + DCR) | DCR_TCE, DCR);
पूर्ण

अटल पूर्णांक dryice_rtc_alarm_irq_enable(काष्ठा device *dev,
		अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा imxdi_dev *imxdi = dev_get_drvdata(dev);

	अगर (enabled)
		di_पूर्णांक_enable(imxdi, DIER_CAIE);
	अन्यथा
		di_पूर्णांक_disable(imxdi, DIER_CAIE);

	वापस 0;
पूर्ण

/*
 * पढ़ो the seconds portion of the alarm रेजिस्टर.
 * the fractional part of the alarm रेजिस्टर is always zero.
 */
अटल पूर्णांक dryice_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alarm)
अणु
	काष्ठा imxdi_dev *imxdi = dev_get_drvdata(dev);
	u32 dcamr;

	dcamr = पढ़ोl(imxdi->ioaddr + DCAMR);
	rtc_समय64_to_पंचांग(dcamr, &alarm->समय);

	/* alarm is enabled अगर the पूर्णांकerrupt is enabled */
	alarm->enabled = (पढ़ोl(imxdi->ioaddr + DIER) & DIER_CAIE) != 0;

	/* करोn't allow the DSR पढ़ो to mess up DSR_WCF */
	mutex_lock(&imxdi->ग_लिखो_mutex);

	/* alarm is pending अगर the alarm flag is set */
	alarm->pending = (पढ़ोl(imxdi->ioaddr + DSR) & DSR_CAF) != 0;

	mutex_unlock(&imxdi->ग_लिखो_mutex);

	वापस 0;
पूर्ण

/*
 * set the seconds portion of dryice alarm रेजिस्टर
 */
अटल पूर्णांक dryice_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alarm)
अणु
	काष्ठा imxdi_dev *imxdi = dev_get_drvdata(dev);
	पूर्णांक rc;

	/* ग_लिखो the new alarm समय */
	rc = di_ग_लिखो_रुको(imxdi, rtc_पंचांग_to_समय64(&alarm->समय), DCAMR);
	अगर (rc)
		वापस rc;

	अगर (alarm->enabled)
		di_पूर्णांक_enable(imxdi, DIER_CAIE);  /* enable alarm पूर्णांकr */
	अन्यथा
		di_पूर्णांक_disable(imxdi, DIER_CAIE); /* disable alarm पूर्णांकr */

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops dryice_rtc_ops = अणु
	.पढ़ो_समय		= dryice_rtc_पढ़ो_समय,
	.set_समय		= dryice_rtc_set_समय,
	.alarm_irq_enable	= dryice_rtc_alarm_irq_enable,
	.पढ़ो_alarm		= dryice_rtc_पढ़ो_alarm,
	.set_alarm		= dryice_rtc_set_alarm,
पूर्ण;

/*
 * पूर्णांकerrupt handler क्रम dryice "normal" and security violation पूर्णांकerrupt
 */
अटल irqवापस_t dryice_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा imxdi_dev *imxdi = dev_id;
	u32 dsr, dier;
	irqवापस_t rc = IRQ_NONE;

	dier = पढ़ोl(imxdi->ioaddr + DIER);
	dsr = पढ़ोl(imxdi->ioaddr + DSR);

	/* handle the security violation event */
	अगर (dier & DIER_SVIE) अणु
		अगर (dsr & DSR_SVF) अणु
			/*
			 * Disable the पूर्णांकerrupt when this kind of event has
			 * happened.
			 * There cannot be more than one event of this type,
			 * because it needs a complex state change
			 * including a मुख्य घातer cycle to get again out of
			 * this state.
			 */
			di_पूर्णांक_disable(imxdi, DIER_SVIE);
			/* report the violation */
			di_report_tamper_info(imxdi, dsr);
			rc = IRQ_HANDLED;
		पूर्ण
	पूर्ण

	/* handle ग_लिखो complete and ग_लिखो error हालs */
	अगर (dier & DIER_WCIE) अणु
		/*If the ग_लिखो रुको queue is empty then there is no pending
		  operations. It means the पूर्णांकerrupt is क्रम DryIce -Security.
		  IRQ must be वापसed as none.*/
		अगर (list_empty_careful(&imxdi->ग_लिखो_रुको.head))
			वापस rc;

		/* DSR_WCF clears itself on DSR पढ़ो */
		अगर (dsr & (DSR_WCF | DSR_WEF)) अणु
			/* mask the पूर्णांकerrupt */
			di_पूर्णांक_disable(imxdi, DIER_WCIE);

			/* save the dsr value क्रम the रुको queue */
			imxdi->dsr |= dsr;

			wake_up_पूर्णांकerruptible(&imxdi->ग_लिखो_रुको);
			rc = IRQ_HANDLED;
		पूर्ण
	पूर्ण

	/* handle the alarm हाल */
	अगर (dier & DIER_CAIE) अणु
		/* DSR_WCF clears itself on DSR पढ़ो */
		अगर (dsr & DSR_CAF) अणु
			/* mask the पूर्णांकerrupt */
			di_पूर्णांक_disable(imxdi, DIER_CAIE);

			/* finish alarm in user context */
			schedule_work(&imxdi->work);
			rc = IRQ_HANDLED;
		पूर्ण
	पूर्ण
	वापस rc;
पूर्ण

/*
 * post the alarm event from user context so it can sleep
 * on the ग_लिखो completion.
 */
अटल व्योम dryice_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा imxdi_dev *imxdi = container_of(work,
			काष्ठा imxdi_dev, work);

	/* dismiss the पूर्णांकerrupt (ignore error) */
	di_ग_लिखो_रुको(imxdi, DSR_CAF, DSR);

	/* pass the alarm event to the rtc framework. */
	rtc_update_irq(imxdi->rtc, 1, RTC_AF | RTC_IRQF);
पूर्ण

/*
 * probe क्रम dryice rtc device
 */
अटल पूर्णांक __init dryice_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा imxdi_dev *imxdi;
	पूर्णांक norm_irq, sec_irq;
	पूर्णांक rc;

	imxdi = devm_kzalloc(&pdev->dev, माप(*imxdi), GFP_KERNEL);
	अगर (!imxdi)
		वापस -ENOMEM;

	imxdi->pdev = pdev;

	imxdi->ioaddr = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(imxdi->ioaddr))
		वापस PTR_ERR(imxdi->ioaddr);

	spin_lock_init(&imxdi->irq_lock);

	norm_irq = platक्रमm_get_irq(pdev, 0);
	अगर (norm_irq < 0)
		वापस norm_irq;

	/* the 2nd irq is the security violation irq
	 * make this optional, करोn't अवरोध the device tree ABI
	 */
	sec_irq = platक्रमm_get_irq(pdev, 1);
	अगर (sec_irq <= 0)
		sec_irq = IRQ_NOTCONNECTED;

	init_रुकोqueue_head(&imxdi->ग_लिखो_रुको);

	INIT_WORK(&imxdi->work, dryice_work);

	mutex_init(&imxdi->ग_लिखो_mutex);

	imxdi->rtc = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(imxdi->rtc))
		वापस PTR_ERR(imxdi->rtc);

	imxdi->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(imxdi->clk))
		वापस PTR_ERR(imxdi->clk);
	rc = clk_prepare_enable(imxdi->clk);
	अगर (rc)
		वापस rc;

	/*
	 * Initialize dryice hardware
	 */

	/* mask all पूर्णांकerrupts */
	ग_लिखोl(0, imxdi->ioaddr + DIER);

	rc = di_handle_state(imxdi);
	अगर (rc != 0)
		जाओ err;

	rc = devm_request_irq(&pdev->dev, norm_irq, dryice_irq,
			      IRQF_SHARED, pdev->name, imxdi);
	अगर (rc) अणु
		dev_warn(&pdev->dev, "interrupt not available.\n");
		जाओ err;
	पूर्ण

	rc = devm_request_irq(&pdev->dev, sec_irq, dryice_irq,
			      IRQF_SHARED, pdev->name, imxdi);
	अगर (rc) अणु
		dev_warn(&pdev->dev, "security violation interrupt not available.\n");
		/* this is not an error, see above */
	पूर्ण

	platक्रमm_set_drvdata(pdev, imxdi);

	imxdi->rtc->ops = &dryice_rtc_ops;
	imxdi->rtc->range_max = U32_MAX;

	rc = devm_rtc_रेजिस्टर_device(imxdi->rtc);
	अगर (rc)
		जाओ err;

	वापस 0;

err:
	clk_disable_unprepare(imxdi->clk);

	वापस rc;
पूर्ण

अटल पूर्णांक __निकास dryice_rtc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा imxdi_dev *imxdi = platक्रमm_get_drvdata(pdev);

	flush_work(&imxdi->work);

	/* mask all पूर्णांकerrupts */
	ग_लिखोl(0, imxdi->ioaddr + DIER);

	clk_disable_unprepare(imxdi->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id dryice_dt_ids[] = अणु
	अणु .compatible = "fsl,imx25-rtc" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, dryice_dt_ids);

अटल काष्ठा platक्रमm_driver dryice_rtc_driver = अणु
	.driver = अणु
		   .name = "imxdi_rtc",
		   .of_match_table = dryice_dt_ids,
		   पूर्ण,
	.हटाओ = __निकास_p(dryice_rtc_हटाओ),
पूर्ण;

module_platक्रमm_driver_probe(dryice_rtc_driver, dryice_rtc_probe);

MODULE_AUTHOR("Freescale Semiconductor, Inc.");
MODULE_AUTHOR("Baruch Siach <baruch@tkos.co.il>");
MODULE_DESCRIPTION("IMX DryIce Realtime Clock Driver (RTC)");
MODULE_LICENSE("GPL");
