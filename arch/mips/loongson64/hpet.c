<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/percpu.h>
#समावेश <linux/delay.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <यंत्र/hpet.h>
#समावेश <यंत्र/समय.स>

#घोषणा SMBUS_CFG_BASE		(loongson_sysconf.ht_control_base + 0x0300a000)
#घोषणा SMBUS_PCI_REG40		0x40
#घोषणा SMBUS_PCI_REG64		0x64
#घोषणा SMBUS_PCI_REGB4		0xb4

#घोषणा HPET_MIN_CYCLES		16
#घोषणा HPET_MIN_PROG_DELTA	(HPET_MIN_CYCLES * 12)

अटल DEFINE_SPINLOCK(hpet_lock);
DEFINE_PER_CPU(काष्ठा घड़ी_event_device, hpet_घड़ीevent_device);

अटल अचिन्हित पूर्णांक smbus_पढ़ो(पूर्णांक offset)
अणु
	वापस *(अस्थिर अचिन्हित पूर्णांक *)(SMBUS_CFG_BASE + offset);
पूर्ण

अटल व्योम smbus_ग_लिखो(पूर्णांक offset, पूर्णांक data)
अणु
	*(अस्थिर अचिन्हित पूर्णांक *)(SMBUS_CFG_BASE + offset) = data;
पूर्ण

अटल व्योम smbus_enable(पूर्णांक offset, पूर्णांक bit)
अणु
	अचिन्हित पूर्णांक cfg = smbus_पढ़ो(offset);

	cfg |= bit;
	smbus_ग_लिखो(offset, cfg);
पूर्ण

अटल पूर्णांक hpet_पढ़ो(पूर्णांक offset)
अणु
	वापस *(अस्थिर अचिन्हित पूर्णांक *)(HPET_MMIO_ADDR + offset);
पूर्ण

अटल व्योम hpet_ग_लिखो(पूर्णांक offset, पूर्णांक data)
अणु
	*(अस्थिर अचिन्हित पूर्णांक *)(HPET_MMIO_ADDR + offset) = data;
पूर्ण

अटल व्योम hpet_start_counter(व्योम)
अणु
	अचिन्हित पूर्णांक cfg = hpet_पढ़ो(HPET_CFG);

	cfg |= HPET_CFG_ENABLE;
	hpet_ग_लिखो(HPET_CFG, cfg);
पूर्ण

अटल व्योम hpet_stop_counter(व्योम)
अणु
	अचिन्हित पूर्णांक cfg = hpet_पढ़ो(HPET_CFG);

	cfg &= ~HPET_CFG_ENABLE;
	hpet_ग_लिखो(HPET_CFG, cfg);
पूर्ण

अटल व्योम hpet_reset_counter(व्योम)
अणु
	hpet_ग_लिखो(HPET_COUNTER, 0);
	hpet_ग_लिखो(HPET_COUNTER + 4, 0);
पूर्ण

अटल व्योम hpet_restart_counter(व्योम)
अणु
	hpet_stop_counter();
	hpet_reset_counter();
	hpet_start_counter();
पूर्ण

अटल व्योम hpet_enable_legacy_पूर्णांक(व्योम)
अणु
	/* Do nothing on Loongson-3 */
पूर्ण

अटल पूर्णांक hpet_set_state_periodic(काष्ठा घड़ी_event_device *evt)
अणु
	पूर्णांक cfg;

	spin_lock(&hpet_lock);

	pr_info("set clock event to periodic mode!\n");
	/* stop counter */
	hpet_stop_counter();

	/* enables the समयr0 to generate a periodic पूर्णांकerrupt */
	cfg = hpet_पढ़ो(HPET_T0_CFG);
	cfg &= ~HPET_TN_LEVEL;
	cfg |= HPET_TN_ENABLE | HPET_TN_PERIODIC | HPET_TN_SETVAL |
		HPET_TN_32BIT;
	hpet_ग_लिखो(HPET_T0_CFG, cfg);

	/* set the comparator */
	hpet_ग_लिखो(HPET_T0_CMP, HPET_COMPARE_VAL);
	udelay(1);
	hpet_ग_लिखो(HPET_T0_CMP, HPET_COMPARE_VAL);

	/* start counter */
	hpet_start_counter();

	spin_unlock(&hpet_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक hpet_set_state_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	पूर्णांक cfg;

	spin_lock(&hpet_lock);

	cfg = hpet_पढ़ो(HPET_T0_CFG);
	cfg &= ~HPET_TN_ENABLE;
	hpet_ग_लिखो(HPET_T0_CFG, cfg);

	spin_unlock(&hpet_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक hpet_set_state_oneshot(काष्ठा घड़ी_event_device *evt)
अणु
	पूर्णांक cfg;

	spin_lock(&hpet_lock);

	pr_info("set clock event to one shot mode!\n");
	cfg = hpet_पढ़ो(HPET_T0_CFG);
	/*
	 * set समयr0 type
	 * 1 : periodic पूर्णांकerrupt
	 * 0 : non-periodic(oneshot) पूर्णांकerrupt
	 */
	cfg &= ~HPET_TN_PERIODIC;
	cfg |= HPET_TN_ENABLE | HPET_TN_32BIT;
	hpet_ग_लिखो(HPET_T0_CFG, cfg);

	spin_unlock(&hpet_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक hpet_tick_resume(काष्ठा घड़ी_event_device *evt)
अणु
	spin_lock(&hpet_lock);
	hpet_enable_legacy_पूर्णांक();
	spin_unlock(&hpet_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक hpet_next_event(अचिन्हित दीर्घ delta,
		काष्ठा घड़ी_event_device *evt)
अणु
	u32 cnt;
	s32 res;

	cnt = hpet_पढ़ो(HPET_COUNTER);
	cnt += (u32) delta;
	hpet_ग_लिखो(HPET_T0_CMP, cnt);

	res = (s32)(cnt - hpet_पढ़ो(HPET_COUNTER));

	वापस res < HPET_MIN_CYCLES ? -ETIME : 0;
पूर्ण

अटल irqवापस_t hpet_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	पूर्णांक is_irq;
	काष्ठा घड़ी_event_device *cd;
	अचिन्हित पूर्णांक cpu = smp_processor_id();

	is_irq = hpet_पढ़ो(HPET_STATUS);
	अगर (is_irq & HPET_T0_IRS) अणु
		/* clear the TIMER0 irq status रेजिस्टर */
		hpet_ग_लिखो(HPET_STATUS, HPET_T0_IRS);
		cd = &per_cpu(hpet_घड़ीevent_device, cpu);
		cd->event_handler(cd);
		वापस IRQ_HANDLED;
	पूर्ण
	वापस IRQ_NONE;
पूर्ण

/*
 * hpet address assignation and irq setting should be करोne in bios.
 * but pmon करोn't करो this, we just setup here directly.
 * The operation under is normal. unक्रमtunately, hpet_setup process
 * is beक्रमe pci initialize.
 *
 * अणु
 *	काष्ठा pci_dev *pdev;
 *
 *	pdev = pci_get_device(PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_SBX00_SMBUS, शून्य);
 *	pci_ग_लिखो_config_word(pdev, SMBUS_PCI_REGB4, HPET_ADDR);
 *
 *	...
 * पूर्ण
 */
अटल व्योम hpet_setup(व्योम)
अणु
	/* set hpet base address */
	smbus_ग_लिखो(SMBUS_PCI_REGB4, HPET_ADDR);

	/* enable decoding of access to HPET MMIO*/
	smbus_enable(SMBUS_PCI_REG40, (1 << 28));

	/* HPET irq enable */
	smbus_enable(SMBUS_PCI_REG64, (1 << 10));

	hpet_enable_legacy_पूर्णांक();
पूर्ण

व्योम __init setup_hpet_समयr(व्योम)
अणु
	अचिन्हित दीर्घ flags = IRQF_NOBALANCING | IRQF_TIMER;
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	काष्ठा घड़ी_event_device *cd;

	hpet_setup();

	cd = &per_cpu(hpet_घड़ीevent_device, cpu);
	cd->name = "hpet";
	cd->rating = 100;
	cd->features = CLOCK_EVT_FEAT_PERIODIC | CLOCK_EVT_FEAT_ONESHOT;
	cd->set_state_shutकरोwn = hpet_set_state_shutकरोwn;
	cd->set_state_periodic = hpet_set_state_periodic;
	cd->set_state_oneshot = hpet_set_state_oneshot;
	cd->tick_resume = hpet_tick_resume;
	cd->set_next_event = hpet_next_event;
	cd->irq = HPET_T0_IRQ;
	cd->cpumask = cpumask_of(cpu);
	घड़ीevent_set_घड़ी(cd, HPET_FREQ);
	cd->max_delta_ns = घड़ीevent_delta2ns(0x7fffffff, cd);
	cd->max_delta_ticks = 0x7fffffff;
	cd->min_delta_ns = घड़ीevent_delta2ns(HPET_MIN_PROG_DELTA, cd);
	cd->min_delta_ticks = HPET_MIN_PROG_DELTA;

	घड़ीevents_रेजिस्टर_device(cd);
	अगर (request_irq(HPET_T0_IRQ, hpet_irq_handler, flags, "hpet", शून्य))
		pr_err("Failed to request irq %d (hpet)\n", HPET_T0_IRQ);
	pr_info("hpet clock event device register\n");
पूर्ण

अटल u64 hpet_पढ़ो_counter(काष्ठा घड़ीsource *cs)
अणु
	वापस (u64)hpet_पढ़ो(HPET_COUNTER);
पूर्ण

अटल व्योम hpet_suspend(काष्ठा घड़ीsource *cs)
अणु
पूर्ण

अटल व्योम hpet_resume(काष्ठा घड़ीsource *cs)
अणु
	hpet_setup();
	hpet_restart_counter();
पूर्ण

अटल काष्ठा घड़ीsource csrc_hpet = अणु
	.name = "hpet",
	/* mips घड़ीsource rating is less than 300, so hpet is better. */
	.rating = 300,
	.पढ़ो = hpet_पढ़ो_counter,
	.mask = CLOCKSOURCE_MASK(32),
	/* oneshot mode work normal with this flag */
	.flags = CLOCK_SOURCE_IS_CONTINUOUS,
	.suspend = hpet_suspend,
	.resume = hpet_resume,
	.mult = 0,
	.shअगरt = 10,
पूर्ण;

पूर्णांक __init init_hpet_घड़ीsource(व्योम)
अणु
	csrc_hpet.mult = घड़ीsource_hz2mult(HPET_FREQ, csrc_hpet.shअगरt);
	वापस घड़ीsource_रेजिस्टर_hz(&csrc_hpet, HPET_FREQ);
पूर्ण

arch_initcall(init_hpet_घड़ीsource);
