<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 1999 - 2018 Intel Corporation. */

/* PTP 1588 Hardware Clock (PHC)
 * Derived from PTP Hardware Clock driver क्रम Intel 82576 and 82580 (igb)
 * Copyright (C) 2011 Riअक्षरd Cochran <riअक्षरdcochran@gmail.com>
 */

#समावेश "e1000.h"

#अगर_घोषित CONFIG_E1000E_HWTS
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/kसमय.स>
#समावेश <यंत्र/tsc.h>
#पूर्ण_अगर

/**
 * e1000e_phc_adjfreq - adjust the frequency of the hardware घड़ी
 * @ptp: ptp घड़ी काष्ठाure
 * @delta: Desired frequency change in parts per billion
 *
 * Adjust the frequency of the PHC cycle counter by the indicated delta from
 * the base frequency.
 **/
अटल पूर्णांक e1000e_phc_adjfreq(काष्ठा ptp_घड़ी_info *ptp, s32 delta)
अणु
	काष्ठा e1000_adapter *adapter = container_of(ptp, काष्ठा e1000_adapter,
						     ptp_घड़ी_info);
	काष्ठा e1000_hw *hw = &adapter->hw;
	bool neg_adj = false;
	अचिन्हित दीर्घ flags;
	u64 adjusपंचांगent;
	u32 timinca, incvalue;
	s32 ret_val;

	अगर ((delta > ptp->max_adj) || (delta <= -1000000000))
		वापस -EINVAL;

	अगर (delta < 0) अणु
		neg_adj = true;
		delta = -delta;
	पूर्ण

	/* Get the System Time Register SYSTIM base frequency */
	ret_val = e1000e_get_base_timinca(adapter, &timinca);
	अगर (ret_val)
		वापस ret_val;

	spin_lock_irqsave(&adapter->systim_lock, flags);

	incvalue = timinca & E1000_TIMINCA_INCVALUE_MASK;

	adjusपंचांगent = incvalue;
	adjusपंचांगent *= delta;
	adjusपंचांगent = भाग_u64(adjusपंचांगent, 1000000000);

	incvalue = neg_adj ? (incvalue - adjusपंचांगent) : (incvalue + adjusपंचांगent);

	timinca &= ~E1000_TIMINCA_INCVALUE_MASK;
	timinca |= incvalue;

	ew32(TIMINCA, timinca);

	adapter->ptp_delta = delta;

	spin_unlock_irqrestore(&adapter->systim_lock, flags);

	वापस 0;
पूर्ण

/**
 * e1000e_phc_adjसमय - Shअगरt the समय of the hardware घड़ी
 * @ptp: ptp घड़ी काष्ठाure
 * @delta: Desired change in nanoseconds
 *
 * Adjust the समयr by resetting the समयcounter काष्ठाure.
 **/
अटल पूर्णांक e1000e_phc_adjसमय(काष्ठा ptp_घड़ी_info *ptp, s64 delta)
अणु
	काष्ठा e1000_adapter *adapter = container_of(ptp, काष्ठा e1000_adapter,
						     ptp_घड़ी_info);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&adapter->systim_lock, flags);
	समयcounter_adjसमय(&adapter->tc, delta);
	spin_unlock_irqrestore(&adapter->systim_lock, flags);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_E1000E_HWTS
#घोषणा MAX_HW_WAIT_COUNT (3)

/**
 * e1000e_phc_get_syncdeviceसमय - Callback given to समयkeeping code पढ़ोs प्रणाली/device रेजिस्टरs
 * @device: current device समय
 * @प्रणाली: प्रणाली counter value पढ़ो synchronously with device समय
 * @ctx: context provided by समयkeeping code
 *
 * Read device and प्रणाली (ART) घड़ी simultaneously and वापस the corrected
 * घड़ी values in ns.
 **/
अटल पूर्णांक e1000e_phc_get_syncdeviceसमय(kसमय_प्रकार *device,
					 काष्ठा प्रणाली_counterval_t *प्रणाली,
					 व्योम *ctx)
अणु
	काष्ठा e1000_adapter *adapter = (काष्ठा e1000_adapter *)ctx;
	काष्ठा e1000_hw *hw = &adapter->hw;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;
	u32 tsync_ctrl;
	u64 dev_cycles;
	u64 sys_cycles;

	tsync_ctrl = er32(TSYNCTXCTL);
	tsync_ctrl |= E1000_TSYNCTXCTL_START_SYNC |
		E1000_TSYNCTXCTL_MAX_ALLOWED_DLY_MASK;
	ew32(TSYNCTXCTL, tsync_ctrl);
	क्रम (i = 0; i < MAX_HW_WAIT_COUNT; ++i) अणु
		udelay(1);
		tsync_ctrl = er32(TSYNCTXCTL);
		अगर (tsync_ctrl & E1000_TSYNCTXCTL_SYNC_COMP)
			अवरोध;
	पूर्ण

	अगर (i == MAX_HW_WAIT_COUNT)
		वापस -ETIMEDOUT;

	dev_cycles = er32(SYSSTMPH);
	dev_cycles <<= 32;
	dev_cycles |= er32(SYSSTMPL);
	spin_lock_irqsave(&adapter->systim_lock, flags);
	*device = ns_to_kसमय(समयcounter_cyc2समय(&adapter->tc, dev_cycles));
	spin_unlock_irqrestore(&adapter->systim_lock, flags);

	sys_cycles = er32(PLTSTMPH);
	sys_cycles <<= 32;
	sys_cycles |= er32(PLTSTMPL);
	*प्रणाली = convert_art_to_tsc(sys_cycles);

	वापस 0;
पूर्ण

/**
 * e1000e_phc_अ_लोrosststamp - Reads the current प्रणाली/device cross बारtamp
 * @ptp: ptp घड़ी काष्ठाure
 * @xtstamp: काष्ठाure containing बारtamp
 *
 * Read device and प्रणाली (ART) घड़ी simultaneously and वापस the scaled
 * घड़ी values in ns.
 **/
अटल पूर्णांक e1000e_phc_अ_लोrosststamp(काष्ठा ptp_घड़ी_info *ptp,
				     काष्ठा प्रणाली_device_crosststamp *xtstamp)
अणु
	काष्ठा e1000_adapter *adapter = container_of(ptp, काष्ठा e1000_adapter,
						     ptp_घड़ी_info);

	वापस get_device_प्रणाली_crosststamp(e1000e_phc_get_syncdeviceसमय,
						adapter, शून्य, xtstamp);
पूर्ण
#पूर्ण_अगर/*CONFIG_E1000E_HWTS*/

/**
 * e1000e_phc_समय_लोx - Reads the current समय from the hardware घड़ी and
 *                       प्रणाली घड़ी
 * @ptp: ptp घड़ी काष्ठाure
 * @ts: बारpec काष्ठाure to hold the current PHC समय
 * @sts: काष्ठाure to hold the current प्रणाली समय
 *
 * Read the समयcounter and वापस the correct value in ns after converting
 * it पूर्णांकo a काष्ठा बारpec.
 **/
अटल पूर्णांक e1000e_phc_समय_लोx(काष्ठा ptp_घड़ी_info *ptp,
			       काष्ठा बारpec64 *ts,
			       काष्ठा ptp_प्रणाली_बारtamp *sts)
अणु
	काष्ठा e1000_adapter *adapter = container_of(ptp, काष्ठा e1000_adapter,
						     ptp_घड़ी_info);
	अचिन्हित दीर्घ flags;
	u64 cycles, ns;

	spin_lock_irqsave(&adapter->systim_lock, flags);

	/* NOTE: Non-monotonic SYSTIM पढ़ोings may be वापसed */
	cycles = e1000e_पढ़ो_systim(adapter, sts);
	ns = समयcounter_cyc2समय(&adapter->tc, cycles);

	spin_unlock_irqrestore(&adapter->systim_lock, flags);

	*ts = ns_to_बारpec64(ns);

	वापस 0;
पूर्ण

/**
 * e1000e_phc_समय_रखो - Set the current समय on the hardware घड़ी
 * @ptp: ptp घड़ी काष्ठाure
 * @ts: बारpec containing the new समय क्रम the cycle counter
 *
 * Reset the समयcounter to use a new base value instead of the kernel
 * wall समयr value.
 **/
अटल पूर्णांक e1000e_phc_समय_रखो(काष्ठा ptp_घड़ी_info *ptp,
			      स्थिर काष्ठा बारpec64 *ts)
अणु
	काष्ठा e1000_adapter *adapter = container_of(ptp, काष्ठा e1000_adapter,
						     ptp_घड़ी_info);
	अचिन्हित दीर्घ flags;
	u64 ns;

	ns = बारpec64_to_ns(ts);

	/* reset the समयcounter */
	spin_lock_irqsave(&adapter->systim_lock, flags);
	समयcounter_init(&adapter->tc, &adapter->cc, ns);
	spin_unlock_irqrestore(&adapter->systim_lock, flags);

	वापस 0;
पूर्ण

/**
 * e1000e_phc_enable - enable or disable an ancillary feature
 * @ptp: ptp घड़ी काष्ठाure
 * @request: Desired resource to enable or disable
 * @on: Caller passes one to enable or zero to disable
 *
 * Enable (or disable) ancillary features of the PHC subप्रणाली.
 * Currently, no ancillary features are supported.
 **/
अटल पूर्णांक e1000e_phc_enable(काष्ठा ptp_घड़ी_info __always_unused *ptp,
			     काष्ठा ptp_घड़ी_request __always_unused *request,
			     पूर्णांक __always_unused on)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल व्योम e1000e_systim_overflow_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा e1000_adapter *adapter = container_of(work, काष्ठा e1000_adapter,
						     systim_overflow_work.work);
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा बारpec64 ts;
	u64 ns;

	/* Update the समयcounter */
	ns = समयcounter_पढ़ो(&adapter->tc);

	ts = ns_to_बारpec64(ns);
	e_dbg("SYSTIM overflow check at %lld.%09lu\n",
	      (दीर्घ दीर्घ) ts.tv_sec, ts.tv_nsec);

	schedule_delayed_work(&adapter->systim_overflow_work,
			      E1000_SYSTIM_OVERFLOW_PERIOD);
पूर्ण

अटल स्थिर काष्ठा ptp_घड़ी_info e1000e_ptp_घड़ी_info = अणु
	.owner		= THIS_MODULE,
	.n_alarm	= 0,
	.n_ext_ts	= 0,
	.n_per_out	= 0,
	.n_pins		= 0,
	.pps		= 0,
	.adjfreq	= e1000e_phc_adjfreq,
	.adjसमय	= e1000e_phc_adjसमय,
	.समय_लोx64	= e1000e_phc_समय_लोx,
	.समय_रखो64	= e1000e_phc_समय_रखो,
	.enable		= e1000e_phc_enable,
पूर्ण;

/**
 * e1000e_ptp_init - initialize PTP क्रम devices which support it
 * @adapter: board निजी काष्ठाure
 *
 * This function perक्रमms the required steps क्रम enabling PTP support.
 * If PTP support has alपढ़ोy been loaded it simply calls the cyclecounter
 * init routine and निकासs.
 **/
व्योम e1000e_ptp_init(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;

	adapter->ptp_घड़ी = शून्य;

	अगर (!(adapter->flags & FLAG_HAS_HW_TIMESTAMP))
		वापस;

	adapter->ptp_घड़ी_info = e1000e_ptp_घड़ी_info;

	snम_लिखो(adapter->ptp_घड़ी_info.name,
		 माप(adapter->ptp_घड़ी_info.name), "%pm",
		 adapter->netdev->perm_addr);

	चयन (hw->mac.type) अणु
	हाल e1000_pch2lan:
	हाल e1000_pch_lpt:
	हाल e1000_pch_spt:
	हाल e1000_pch_cnp:
	हाल e1000_pch_tgp:
	हाल e1000_pch_adp:
	हाल e1000_pch_mtp:
		अगर ((hw->mac.type < e1000_pch_lpt) ||
		    (er32(TSYNCRXCTL) & E1000_TSYNCRXCTL_SYSCFI)) अणु
			adapter->ptp_घड़ी_info.max_adj = 24000000 - 1;
			अवरोध;
		पूर्ण
		fallthrough;
	हाल e1000_82574:
	हाल e1000_82583:
		adapter->ptp_घड़ी_info.max_adj = 600000000 - 1;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

#अगर_घोषित CONFIG_E1000E_HWTS
	/* CPU must have ART and GBe must be from Sunrise Poपूर्णांक or greater */
	अगर (hw->mac.type >= e1000_pch_spt && boot_cpu_has(X86_FEATURE_ART))
		adapter->ptp_घड़ी_info.अ_लोrosststamp =
			e1000e_phc_अ_लोrosststamp;
#पूर्ण_अगर/*CONFIG_E1000E_HWTS*/

	INIT_DELAYED_WORK(&adapter->systim_overflow_work,
			  e1000e_systim_overflow_work);

	schedule_delayed_work(&adapter->systim_overflow_work,
			      E1000_SYSTIM_OVERFLOW_PERIOD);

	adapter->ptp_घड़ी = ptp_घड़ी_रेजिस्टर(&adapter->ptp_घड़ी_info,
						&adapter->pdev->dev);
	अगर (IS_ERR(adapter->ptp_घड़ी)) अणु
		adapter->ptp_घड़ी = शून्य;
		e_err("ptp_clock_register failed\n");
	पूर्ण अन्यथा अगर (adapter->ptp_घड़ी) अणु
		e_info("registered PHC clock\n");
	पूर्ण
पूर्ण

/**
 * e1000e_ptp_हटाओ - disable PTP device and stop the overflow check
 * @adapter: board निजी काष्ठाure
 *
 * Stop the PTP support, and cancel the delayed work.
 **/
व्योम e1000e_ptp_हटाओ(काष्ठा e1000_adapter *adapter)
अणु
	अगर (!(adapter->flags & FLAG_HAS_HW_TIMESTAMP))
		वापस;

	cancel_delayed_work_sync(&adapter->systim_overflow_work);

	अगर (adapter->ptp_घड़ी) अणु
		ptp_घड़ी_unरेजिस्टर(adapter->ptp_घड़ी);
		adapter->ptp_घड़ी = शून्य;
		e_info("removed PHC\n");
	पूर्ण
पूर्ण
