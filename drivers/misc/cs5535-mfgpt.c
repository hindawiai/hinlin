<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम the CS5535/CS5536 Multi-Function General Purpose Timers (MFGPT)
 *
 * Copyright (C) 2006, Advanced Micro Devices, Inc.
 * Copyright (C) 2007  Andres Salomon <dilinger@debian.org>
 * Copyright (C) 2009  Andres Salomon <dilinger@collabora.co.uk>
 *
 * The MFGPTs are करोcumented in AMD Geode CS5536 Companion Device Data Book.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/cs5535.h>
#समावेश <linux/slab.h>

#घोषणा DRV_NAME "cs5535-mfgpt"

अटल पूर्णांक mfgpt_reset_समयrs;
module_param_named(mfgptfix, mfgpt_reset_समयrs, पूर्णांक, 0644);
MODULE_PARM_DESC(mfgptfix, "Try to reset the MFGPT timers during init; "
		"required by some broken BIOSes (ie, TinyBIOS < 0.99) or kexec "
		"(1 = reset the MFGPT using an undocumented bit, "
		"2 = perform a soft reset by unconfiguring all timers); "
		"use what works best for you.");

काष्ठा cs5535_mfgpt_समयr अणु
	काष्ठा cs5535_mfgpt_chip *chip;
	पूर्णांक nr;
पूर्ण;

अटल काष्ठा cs5535_mfgpt_chip अणु
	DECLARE_BITMAP(avail, MFGPT_MAX_TIMERS);
	resource_माप_प्रकार base;

	काष्ठा platक्रमm_device *pdev;
	spinlock_t lock;
	पूर्णांक initialized;
पूर्ण cs5535_mfgpt_chip;

पूर्णांक cs5535_mfgpt_toggle_event(काष्ठा cs5535_mfgpt_समयr *समयr, पूर्णांक cmp,
		पूर्णांक event, पूर्णांक enable)
अणु
	uपूर्णांक32_t msr, mask, value, dummy;
	पूर्णांक shअगरt = (cmp == MFGPT_CMP1) ? 0 : 8;

	अगर (!समयr) अणु
		WARN_ON(1);
		वापस -EIO;
	पूर्ण

	/*
	 * The रेजिस्टर maps क्रम these are described in sections 6.17.1.x of
	 * the AMD Geode CS5536 Companion Device Data Book.
	 */
	चयन (event) अणु
	हाल MFGPT_EVENT_RESET:
		/*
		 * XXX: According to the करोcs, we cannot reset समयrs above
		 * 6; that is, resets क्रम 7 and 8 will be ignored.  Is this
		 * a problem?   -dilinger
		 */
		msr = MSR_MFGPT_NR;
		mask = 1 << (समयr->nr + 24);
		अवरोध;

	हाल MFGPT_EVENT_NMI:
		msr = MSR_MFGPT_NR;
		mask = 1 << (समयr->nr + shअगरt);
		अवरोध;

	हाल MFGPT_EVENT_IRQ:
		msr = MSR_MFGPT_IRQ;
		mask = 1 << (समयr->nr + shअगरt);
		अवरोध;

	शेष:
		वापस -EIO;
	पूर्ण

	rdmsr(msr, value, dummy);

	अगर (enable)
		value |= mask;
	अन्यथा
		value &= ~mask;

	wrmsr(msr, value, dummy);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(cs5535_mfgpt_toggle_event);

पूर्णांक cs5535_mfgpt_set_irq(काष्ठा cs5535_mfgpt_समयr *समयr, पूर्णांक cmp, पूर्णांक *irq,
		पूर्णांक enable)
अणु
	uपूर्णांक32_t zsel, lpc, dummy;
	पूर्णांक shअगरt;

	अगर (!समयr) अणु
		WARN_ON(1);
		वापस -EIO;
	पूर्ण

	/*
	 * Unक्रमtunately, MFGPTs come in pairs sharing their IRQ lines. If VSA
	 * is using the same CMP of the समयr's Siamese twin, the IRQ is set to
	 * 2, and we mustn't use nor change it.
	 * XXX: Likewise, 2 Linux drivers might clash अगर the 2nd overग_लिखोs the
	 * IRQ of the 1st. This can only happen अगर क्रमcing an IRQ, calling this
	 * with *irq==0 is safe. Currently there _are_ no 2 drivers.
	 */
	rdmsr(MSR_PIC_ZSEL_LOW, zsel, dummy);
	shअगरt = ((cmp == MFGPT_CMP1 ? 0 : 4) + समयr->nr % 4) * 4;
	अगर (((zsel >> shअगरt) & 0xF) == 2)
		वापस -EIO;

	/* Choose IRQ: अगर none supplied, keep IRQ alपढ़ोy set or use शेष */
	अगर (!*irq)
		*irq = (zsel >> shअगरt) & 0xF;
	अगर (!*irq)
		*irq = CONFIG_CS5535_MFGPT_DEFAULT_IRQ;

	/* Can't use IRQ if it's 0 (=disabled), 2, or routed to LPC */
	अगर (*irq < 1 || *irq == 2 || *irq > 15)
		वापस -EIO;
	rdmsr(MSR_PIC_IRQM_LPC, lpc, dummy);
	अगर (lpc & (1 << *irq))
		वापस -EIO;

	/* All chosen and checked - go क्रम it */
	अगर (cs5535_mfgpt_toggle_event(समयr, cmp, MFGPT_EVENT_IRQ, enable))
		वापस -EIO;
	अगर (enable) अणु
		zsel = (zsel & ~(0xF << shअगरt)) | (*irq << shअगरt);
		wrmsr(MSR_PIC_ZSEL_LOW, zsel, dummy);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(cs5535_mfgpt_set_irq);

काष्ठा cs5535_mfgpt_समयr *cs5535_mfgpt_alloc_समयr(पूर्णांक समयr_nr, पूर्णांक करोमुख्य)
अणु
	काष्ठा cs5535_mfgpt_chip *mfgpt = &cs5535_mfgpt_chip;
	काष्ठा cs5535_mfgpt_समयr *समयr = शून्य;
	अचिन्हित दीर्घ flags;
	पूर्णांक max;

	अगर (!mfgpt->initialized)
		जाओ करोne;

	/* only allocate समयrs from the working करोमुख्य अगर requested */
	अगर (करोमुख्य == MFGPT_DOMAIN_WORKING)
		max = 6;
	अन्यथा
		max = MFGPT_MAX_TIMERS;

	अगर (समयr_nr >= max) अणु
		/* programmer error.  silly programmers! */
		WARN_ON(1);
		जाओ करोne;
	पूर्ण

	spin_lock_irqsave(&mfgpt->lock, flags);
	अगर (समयr_nr < 0) अणु
		अचिन्हित दीर्घ t;

		/* try to find any available समयr */
		t = find_first_bit(mfgpt->avail, max);
		/* set समयr_nr to -1 अगर no समयrs available */
		समयr_nr = t < max ? (पूर्णांक) t : -1;
	पूर्ण अन्यथा अणु
		/* check अगर the requested समयr's available */
		अगर (!test_bit(समयr_nr, mfgpt->avail))
			समयr_nr = -1;
	पूर्ण

	अगर (समयr_nr >= 0)
		/* अगर समयr_nr is not -1, it's an available समयr */
		__clear_bit(समयr_nr, mfgpt->avail);
	spin_unlock_irqrestore(&mfgpt->lock, flags);

	अगर (समयr_nr < 0)
		जाओ करोne;

	समयr = kदो_स्मृति(माप(*समयr), GFP_KERNEL);
	अगर (!समयr) अणु
		/* aw hell */
		spin_lock_irqsave(&mfgpt->lock, flags);
		__set_bit(समयr_nr, mfgpt->avail);
		spin_unlock_irqrestore(&mfgpt->lock, flags);
		जाओ करोne;
	पूर्ण
	समयr->chip = mfgpt;
	समयr->nr = समयr_nr;
	dev_info(&mfgpt->pdev->dev, "registered timer %d\n", समयr_nr);

करोne:
	वापस समयr;
पूर्ण
EXPORT_SYMBOL_GPL(cs5535_mfgpt_alloc_समयr);

/*
 * XXX: This मुक्तs the समयr memory, but never resets the actual hardware
 * समयr.  The old geode_mfgpt code did this; it would be good to figure
 * out a way to actually release the hardware समयr.  See comments below.
 */
व्योम cs5535_mfgpt_मुक्त_समयr(काष्ठा cs5535_mfgpt_समयr *समयr)
अणु
	अचिन्हित दीर्घ flags;
	uपूर्णांक16_t val;

	/* समयr can be made available again only अगर never set up */
	val = cs5535_mfgpt_पढ़ो(समयr, MFGPT_REG_SETUP);
	अगर (!(val & MFGPT_SETUP_SETUP)) अणु
		spin_lock_irqsave(&समयr->chip->lock, flags);
		__set_bit(समयr->nr, समयr->chip->avail);
		spin_unlock_irqrestore(&समयr->chip->lock, flags);
	पूर्ण

	kमुक्त(समयr);
पूर्ण
EXPORT_SYMBOL_GPL(cs5535_mfgpt_मुक्त_समयr);

uपूर्णांक16_t cs5535_mfgpt_पढ़ो(काष्ठा cs5535_mfgpt_समयr *समयr, uपूर्णांक16_t reg)
अणु
	वापस inw(समयr->chip->base + reg + (समयr->nr * 8));
पूर्ण
EXPORT_SYMBOL_GPL(cs5535_mfgpt_पढ़ो);

व्योम cs5535_mfgpt_ग_लिखो(काष्ठा cs5535_mfgpt_समयr *समयr, uपूर्णांक16_t reg,
		uपूर्णांक16_t value)
अणु
	outw(value, समयr->chip->base + reg + (समयr->nr * 8));
पूर्ण
EXPORT_SYMBOL_GPL(cs5535_mfgpt_ग_लिखो);

/*
 * This is a sledgehammer that resets all MFGPT समयrs. This is required by
 * some broken BIOSes which leave the प्रणाली in an unstable state
 * (TinyBIOS 0.98, क्रम example; fixed in 0.99).  It's uncertain as to
 * whether or not this secret MSR can be used to release inभागidual समयrs.
 * Jordan tells me that he and Mitch once played w/ it, but it's unclear
 * what the results of that were (and they experienced some instability).
 */
अटल व्योम reset_all_समयrs(व्योम)
अणु
	uपूर्णांक32_t val, dummy;

	/* The following unकरोcumented bit resets the MFGPT समयrs */
	val = 0xFF; dummy = 0;
	wrmsr(MSR_MFGPT_SETUP, val, dummy);
पूर्ण

/*
 * This is another sledgehammer to reset all MFGPT समयrs.
 * Instead of using the unकरोcumented bit method it clears
 * IRQ, NMI and RESET settings.
 */
अटल व्योम soft_reset(व्योम)
अणु
	पूर्णांक i;
	काष्ठा cs5535_mfgpt_समयr t;

	क्रम (i = 0; i < MFGPT_MAX_TIMERS; i++) अणु
		t.nr = i;

		cs5535_mfgpt_toggle_event(&t, MFGPT_CMP1, MFGPT_EVENT_RESET, 0);
		cs5535_mfgpt_toggle_event(&t, MFGPT_CMP2, MFGPT_EVENT_RESET, 0);
		cs5535_mfgpt_toggle_event(&t, MFGPT_CMP1, MFGPT_EVENT_NMI, 0);
		cs5535_mfgpt_toggle_event(&t, MFGPT_CMP2, MFGPT_EVENT_NMI, 0);
		cs5535_mfgpt_toggle_event(&t, MFGPT_CMP1, MFGPT_EVENT_IRQ, 0);
		cs5535_mfgpt_toggle_event(&t, MFGPT_CMP2, MFGPT_EVENT_IRQ, 0);
	पूर्ण
पूर्ण

/*
 * Check whether any MFGPTs are available क्रम the kernel to use.  In most
 * हालs, firmware that uses AMD's VSA code will claim all समयrs during
 * bootup; we certainly करोn't want to take them if they're alपढ़ोy in use.
 * In other हालs (such as with VSAless OpenFirmware), the प्रणाली firmware
 * leaves समयrs available क्रम us to use.
 */
अटल पूर्णांक scan_समयrs(काष्ठा cs5535_mfgpt_chip *mfgpt)
अणु
	काष्ठा cs5535_mfgpt_समयr समयr = अणु .chip = mfgpt पूर्ण;
	अचिन्हित दीर्घ flags;
	पूर्णांक समयrs = 0;
	uपूर्णांक16_t val;
	पूर्णांक i;

	/* bios workaround */
	अगर (mfgpt_reset_समयrs == 1)
		reset_all_समयrs();
	अन्यथा अगर (mfgpt_reset_समयrs == 2)
		soft_reset();

	/* just to be safe, protect this section w/ lock */
	spin_lock_irqsave(&mfgpt->lock, flags);
	क्रम (i = 0; i < MFGPT_MAX_TIMERS; i++) अणु
		समयr.nr = i;
		val = cs5535_mfgpt_पढ़ो(&समयr, MFGPT_REG_SETUP);
		अगर (!(val & MFGPT_SETUP_SETUP) || mfgpt_reset_समयrs == 2) अणु
			__set_bit(i, mfgpt->avail);
			समयrs++;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&mfgpt->lock, flags);

	वापस समयrs;
पूर्ण

अटल पूर्णांक cs5535_mfgpt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	पूर्णांक err = -EIO, t;

	अगर (mfgpt_reset_समयrs < 0 || mfgpt_reset_समयrs > 2) अणु
		dev_err(&pdev->dev, "Bad mfgpt_reset_timers value: %i\n",
			mfgpt_reset_समयrs);
		जाओ करोne;
	पूर्ण

	/* There are two ways to get the MFGPT base address; one is by
	 * fetching it from MSR_LBAR_MFGPT, the other is by पढ़ोing the
	 * PCI BAR info.  The latter method is easier (especially across
	 * dअगरferent architectures), so we'll stick with that क्रम now.  If
	 * it turns out to be unreliable in the face of crappy BIOSes, we
	 * can always go back to using MSRs.. */

	res = platक्रमm_get_resource(pdev, IORESOURCE_IO, 0);
	अगर (!res) अणु
		dev_err(&pdev->dev, "can't fetch device resource info\n");
		जाओ करोne;
	पूर्ण

	अगर (!request_region(res->start, resource_size(res), pdev->name)) अणु
		dev_err(&pdev->dev, "can't request region\n");
		जाओ करोne;
	पूर्ण

	/* set up the driver-specअगरic काष्ठा */
	cs5535_mfgpt_chip.base = res->start;
	cs5535_mfgpt_chip.pdev = pdev;
	spin_lock_init(&cs5535_mfgpt_chip.lock);

	dev_info(&pdev->dev, "reserved resource region %pR\n", res);

	/* detect the available समयrs */
	t = scan_समयrs(&cs5535_mfgpt_chip);
	dev_info(&pdev->dev, "%d MFGPT timers available\n", t);
	cs5535_mfgpt_chip.initialized = 1;
	वापस 0;

करोne:
	वापस err;
पूर्ण

अटल काष्ठा platक्रमm_driver cs5535_mfgpt_driver = अणु
	.driver = अणु
		.name = DRV_NAME,
	पूर्ण,
	.probe = cs5535_mfgpt_probe,
पूर्ण;


अटल पूर्णांक __init cs5535_mfgpt_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&cs5535_mfgpt_driver);
पूर्ण

module_init(cs5535_mfgpt_init);

MODULE_AUTHOR("Andres Salomon <dilinger@queued.net>");
MODULE_DESCRIPTION("CS5535/CS5536 MFGPT timer driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRV_NAME);
