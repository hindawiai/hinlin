<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/export.h>
#समावेश <linux/delay.h>
#समावेश <linux/hpet.h>
#समावेश <linux/cpu.h>
#समावेश <linux/irq.h>

#समावेश <यंत्र/irq_remapping.h>
#समावेश <यंत्र/hpet.h>
#समावेश <यंत्र/समय.स>

#अघोषित  pr_fmt
#घोषणा pr_fmt(fmt) "hpet: " fmt

क्रमागत hpet_mode अणु
	HPET_MODE_UNUSED,
	HPET_MODE_LEGACY,
	HPET_MODE_CLOCKEVT,
	HPET_MODE_DEVICE,
पूर्ण;

काष्ठा hpet_channel अणु
	काष्ठा घड़ी_event_device	evt;
	अचिन्हित पूर्णांक			num;
	अचिन्हित पूर्णांक			cpu;
	अचिन्हित पूर्णांक			irq;
	अचिन्हित पूर्णांक			in_use;
	क्रमागत hpet_mode			mode;
	अचिन्हित पूर्णांक			boot_cfg;
	अक्षर				name[10];
पूर्ण;

काष्ठा hpet_base अणु
	अचिन्हित पूर्णांक			nr_channels;
	अचिन्हित पूर्णांक			nr_घड़ीevents;
	अचिन्हित पूर्णांक			boot_cfg;
	काष्ठा hpet_channel		*channels;
पूर्ण;

#घोषणा HPET_MASK			CLOCKSOURCE_MASK(32)

#घोषणा HPET_MIN_CYCLES			128
#घोषणा HPET_MIN_PROG_DELTA		(HPET_MIN_CYCLES + (HPET_MIN_CYCLES >> 1))

/*
 * HPET address is set in acpi/boot.c, when an ACPI entry exists
 */
अचिन्हित दीर्घ				hpet_address;
u8					hpet_blockid; /* OS समयr block num */
bool					hpet_msi_disable;

#अगर_घोषित CONFIG_GENERIC_MSI_IRQ
अटल DEFINE_PER_CPU(काष्ठा hpet_channel *, cpu_hpet_channel);
अटल काष्ठा irq_करोमुख्य		*hpet_करोमुख्य;
#पूर्ण_अगर

अटल व्योम __iomem			*hpet_virt_address;

अटल काष्ठा hpet_base			hpet_base;

अटल bool				hpet_legacy_पूर्णांक_enabled;
अटल अचिन्हित दीर्घ			hpet_freq;

bool					boot_hpet_disable;
bool					hpet_क्रमce_user;
अटल bool				hpet_verbose;

अटल अंतरभूत
काष्ठा hpet_channel *घड़ीevent_to_channel(काष्ठा घड़ी_event_device *evt)
अणु
	वापस container_of(evt, काष्ठा hpet_channel, evt);
पूर्ण

अंतरभूत अचिन्हित पूर्णांक hpet_पढ़ोl(अचिन्हित पूर्णांक a)
अणु
	वापस पढ़ोl(hpet_virt_address + a);
पूर्ण

अटल अंतरभूत व्योम hpet_ग_लिखोl(अचिन्हित पूर्णांक d, अचिन्हित पूर्णांक a)
अणु
	ग_लिखोl(d, hpet_virt_address + a);
पूर्ण

अटल अंतरभूत व्योम hpet_set_mapping(व्योम)
अणु
	hpet_virt_address = ioremap(hpet_address, HPET_MMAP_SIZE);
पूर्ण

अटल अंतरभूत व्योम hpet_clear_mapping(व्योम)
अणु
	iounmap(hpet_virt_address);
	hpet_virt_address = शून्य;
पूर्ण

/*
 * HPET command line enable / disable
 */
अटल पूर्णांक __init hpet_setup(अक्षर *str)
अणु
	जबतक (str) अणु
		अक्षर *next = म_अक्षर(str, ',');

		अगर (next)
			*next++ = 0;
		अगर (!म_भेदन("disable", str, 7))
			boot_hpet_disable = true;
		अगर (!म_भेदन("force", str, 5))
			hpet_क्रमce_user = true;
		अगर (!म_भेदन("verbose", str, 7))
			hpet_verbose = true;
		str = next;
	पूर्ण
	वापस 1;
पूर्ण
__setup("hpet=", hpet_setup);

अटल पूर्णांक __init disable_hpet(अक्षर *str)
अणु
	boot_hpet_disable = true;
	वापस 1;
पूर्ण
__setup("nohpet", disable_hpet);

अटल अंतरभूत पूर्णांक is_hpet_capable(व्योम)
अणु
	वापस !boot_hpet_disable && hpet_address;
पूर्ण

/**
 * is_hpet_enabled - Check whether the legacy HPET समयr पूर्णांकerrupt is enabled
 */
पूर्णांक is_hpet_enabled(व्योम)
अणु
	वापस is_hpet_capable() && hpet_legacy_पूर्णांक_enabled;
पूर्ण
EXPORT_SYMBOL_GPL(is_hpet_enabled);

अटल व्योम _hpet_prपूर्णांक_config(स्थिर अक्षर *function, पूर्णांक line)
अणु
	u32 i, id, period, cfg, status, channels, l, h;

	pr_info("%s(%d):\n", function, line);

	id = hpet_पढ़ोl(HPET_ID);
	period = hpet_पढ़ोl(HPET_PERIOD);
	pr_info("ID: 0x%x, PERIOD: 0x%x\n", id, period);

	cfg = hpet_पढ़ोl(HPET_CFG);
	status = hpet_पढ़ोl(HPET_STATUS);
	pr_info("CFG: 0x%x, STATUS: 0x%x\n", cfg, status);

	l = hpet_पढ़ोl(HPET_COUNTER);
	h = hpet_पढ़ोl(HPET_COUNTER+4);
	pr_info("COUNTER_l: 0x%x, COUNTER_h: 0x%x\n", l, h);

	channels = ((id & HPET_ID_NUMBER) >> HPET_ID_NUMBER_SHIFT) + 1;

	क्रम (i = 0; i < channels; i++) अणु
		l = hpet_पढ़ोl(HPET_Tn_CFG(i));
		h = hpet_पढ़ोl(HPET_Tn_CFG(i)+4);
		pr_info("T%d: CFG_l: 0x%x, CFG_h: 0x%x\n", i, l, h);

		l = hpet_पढ़ोl(HPET_Tn_CMP(i));
		h = hpet_पढ़ोl(HPET_Tn_CMP(i)+4);
		pr_info("T%d: CMP_l: 0x%x, CMP_h: 0x%x\n", i, l, h);

		l = hpet_पढ़ोl(HPET_Tn_ROUTE(i));
		h = hpet_पढ़ोl(HPET_Tn_ROUTE(i)+4);
		pr_info("T%d ROUTE_l: 0x%x, ROUTE_h: 0x%x\n", i, l, h);
	पूर्ण
पूर्ण

#घोषणा hpet_prपूर्णांक_config()					\
करो अणु								\
	अगर (hpet_verbose)					\
		_hpet_prपूर्णांक_config(__func__, __LINE__);	\
पूर्ण जबतक (0)

/*
 * When the HPET driver (/dev/hpet) is enabled, we need to reserve
 * समयr 0 and समयr 1 in हाल of RTC emulation.
 */
#अगर_घोषित CONFIG_HPET

अटल व्योम __init hpet_reserve_platक्रमm_समयrs(व्योम)
अणु
	काष्ठा hpet_data hd;
	अचिन्हित पूर्णांक i;

	स_रखो(&hd, 0, माप(hd));
	hd.hd_phys_address	= hpet_address;
	hd.hd_address		= hpet_virt_address;
	hd.hd_nirqs		= hpet_base.nr_channels;

	/*
	 * NOTE that hd_irq[] reflects IOAPIC input pins (LEGACY_8254
	 * is wrong क्रम i8259!) not the output IRQ.  Many BIOS ग_लिखोrs
	 * करोn't bother configuring *any* comparator पूर्णांकerrupts.
	 */
	hd.hd_irq[0] = HPET_LEGACY_8254;
	hd.hd_irq[1] = HPET_LEGACY_RTC;

	क्रम (i = 0; i < hpet_base.nr_channels; i++) अणु
		काष्ठा hpet_channel *hc = hpet_base.channels + i;

		अगर (i >= 2)
			hd.hd_irq[i] = hc->irq;

		चयन (hc->mode) अणु
		हाल HPET_MODE_UNUSED:
		हाल HPET_MODE_DEVICE:
			hc->mode = HPET_MODE_DEVICE;
			अवरोध;
		हाल HPET_MODE_CLOCKEVT:
		हाल HPET_MODE_LEGACY:
			hpet_reserve_समयr(&hd, hc->num);
			अवरोध;
		पूर्ण
	पूर्ण

	hpet_alloc(&hd);
पूर्ण

अटल व्योम __init hpet_select_device_channel(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < hpet_base.nr_channels; i++) अणु
		काष्ठा hpet_channel *hc = hpet_base.channels + i;

		/* Associate the first unused channel to /dev/hpet */
		अगर (hc->mode == HPET_MODE_UNUSED) अणु
			hc->mode = HPET_MODE_DEVICE;
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

#अन्यथा
अटल अंतरभूत व्योम hpet_reserve_platक्रमm_समयrs(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम hpet_select_device_channel(व्योम) अणुपूर्ण
#पूर्ण_अगर

/* Common HPET functions */
अटल व्योम hpet_stop_counter(व्योम)
अणु
	u32 cfg = hpet_पढ़ोl(HPET_CFG);

	cfg &= ~HPET_CFG_ENABLE;
	hpet_ग_लिखोl(cfg, HPET_CFG);
पूर्ण

अटल व्योम hpet_reset_counter(व्योम)
अणु
	hpet_ग_लिखोl(0, HPET_COUNTER);
	hpet_ग_लिखोl(0, HPET_COUNTER + 4);
पूर्ण

अटल व्योम hpet_start_counter(व्योम)
अणु
	अचिन्हित पूर्णांक cfg = hpet_पढ़ोl(HPET_CFG);

	cfg |= HPET_CFG_ENABLE;
	hpet_ग_लिखोl(cfg, HPET_CFG);
पूर्ण

अटल व्योम hpet_restart_counter(व्योम)
अणु
	hpet_stop_counter();
	hpet_reset_counter();
	hpet_start_counter();
पूर्ण

अटल व्योम hpet_resume_device(व्योम)
अणु
	क्रमce_hpet_resume();
पूर्ण

अटल व्योम hpet_resume_counter(काष्ठा घड़ीsource *cs)
अणु
	hpet_resume_device();
	hpet_restart_counter();
पूर्ण

अटल व्योम hpet_enable_legacy_पूर्णांक(व्योम)
अणु
	अचिन्हित पूर्णांक cfg = hpet_पढ़ोl(HPET_CFG);

	cfg |= HPET_CFG_LEGACY;
	hpet_ग_लिखोl(cfg, HPET_CFG);
	hpet_legacy_पूर्णांक_enabled = true;
पूर्ण

अटल पूर्णांक hpet_clkevt_set_state_periodic(काष्ठा घड़ी_event_device *evt)
अणु
	अचिन्हित पूर्णांक channel = घड़ीevent_to_channel(evt)->num;
	अचिन्हित पूर्णांक cfg, cmp, now;
	uपूर्णांक64_t delta;

	hpet_stop_counter();
	delta = ((uपूर्णांक64_t)(NSEC_PER_SEC / HZ)) * evt->mult;
	delta >>= evt->shअगरt;
	now = hpet_पढ़ोl(HPET_COUNTER);
	cmp = now + (अचिन्हित पूर्णांक)delta;
	cfg = hpet_पढ़ोl(HPET_Tn_CFG(channel));
	cfg |= HPET_TN_ENABLE | HPET_TN_PERIODIC | HPET_TN_SETVAL |
	       HPET_TN_32BIT;
	hpet_ग_लिखोl(cfg, HPET_Tn_CFG(channel));
	hpet_ग_लिखोl(cmp, HPET_Tn_CMP(channel));
	udelay(1);
	/*
	 * HPET on AMD 81xx needs a second ग_लिखो (with HPET_TN_SETVAL
	 * cleared) to T0_CMP to set the period. The HPET_TN_SETVAL
	 * bit is स्वतःmatically cleared after the first ग_लिखो.
	 * (See AMD-8111 HyperTransport I/O Hub Data Sheet,
	 * Publication # 24674)
	 */
	hpet_ग_लिखोl((अचिन्हित पूर्णांक)delta, HPET_Tn_CMP(channel));
	hpet_start_counter();
	hpet_prपूर्णांक_config();

	वापस 0;
पूर्ण

अटल पूर्णांक hpet_clkevt_set_state_oneshot(काष्ठा घड़ी_event_device *evt)
अणु
	अचिन्हित पूर्णांक channel = घड़ीevent_to_channel(evt)->num;
	अचिन्हित पूर्णांक cfg;

	cfg = hpet_पढ़ोl(HPET_Tn_CFG(channel));
	cfg &= ~HPET_TN_PERIODIC;
	cfg |= HPET_TN_ENABLE | HPET_TN_32BIT;
	hpet_ग_लिखोl(cfg, HPET_Tn_CFG(channel));

	वापस 0;
पूर्ण

अटल पूर्णांक hpet_clkevt_set_state_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	अचिन्हित पूर्णांक channel = घड़ीevent_to_channel(evt)->num;
	अचिन्हित पूर्णांक cfg;

	cfg = hpet_पढ़ोl(HPET_Tn_CFG(channel));
	cfg &= ~HPET_TN_ENABLE;
	hpet_ग_लिखोl(cfg, HPET_Tn_CFG(channel));

	वापस 0;
पूर्ण

अटल पूर्णांक hpet_clkevt_legacy_resume(काष्ठा घड़ी_event_device *evt)
अणु
	hpet_enable_legacy_पूर्णांक();
	hpet_prपूर्णांक_config();
	वापस 0;
पूर्ण

अटल पूर्णांक
hpet_clkevt_set_next_event(अचिन्हित दीर्घ delta, काष्ठा घड़ी_event_device *evt)
अणु
	अचिन्हित पूर्णांक channel = घड़ीevent_to_channel(evt)->num;
	u32 cnt;
	s32 res;

	cnt = hpet_पढ़ोl(HPET_COUNTER);
	cnt += (u32) delta;
	hpet_ग_लिखोl(cnt, HPET_Tn_CMP(channel));

	/*
	 * HPETs are a complete disaster. The compare रेजिस्टर is
	 * based on a equal comparison and neither provides a less
	 * than or equal functionality (which would require to take
	 * the wraparound पूर्णांकo account) nor a simple count करोwn event
	 * mode. Further the ग_लिखो to the comparator रेजिस्टर is
	 * delayed पूर्णांकernally up to two HPET घड़ी cycles in certain
	 * chipsets (ATI, ICH9,10). Some newer AMD chipsets have even
	 * दीर्घer delays. We worked around that by पढ़ोing back the
	 * compare रेजिस्टर, but that required another workaround क्रम
	 * ICH9,10 chips where the first पढ़ोout after ग_लिखो can
	 * वापस the old stale value. We alपढ़ोy had a minimum
	 * programming delta of 5us enक्रमced, but a NMI or SMI hitting
	 * between the counter पढ़ोout and the comparator ग_लिखो can
	 * move us behind that poपूर्णांक easily. Now instead of पढ़ोing
	 * the compare रेजिस्टर back several बार, we make the ETIME
	 * decision based on the following: Return ETIME अगर the
	 * counter value after the ग_लिखो is less than HPET_MIN_CYCLES
	 * away from the event or अगर the counter is alपढ़ोy ahead of
	 * the event. The minimum programming delta क्रम the generic
	 * घड़ीevents code is set to 1.5 * HPET_MIN_CYCLES.
	 */
	res = (s32)(cnt - hpet_पढ़ोl(HPET_COUNTER));

	वापस res < HPET_MIN_CYCLES ? -ETIME : 0;
पूर्ण

अटल व्योम hpet_init_घड़ीevent(काष्ठा hpet_channel *hc, अचिन्हित पूर्णांक rating)
अणु
	काष्ठा घड़ी_event_device *evt = &hc->evt;

	evt->rating		= rating;
	evt->irq		= hc->irq;
	evt->name		= hc->name;
	evt->cpumask		= cpumask_of(hc->cpu);
	evt->set_state_oneshot	= hpet_clkevt_set_state_oneshot;
	evt->set_next_event	= hpet_clkevt_set_next_event;
	evt->set_state_shutकरोwn	= hpet_clkevt_set_state_shutकरोwn;

	evt->features = CLOCK_EVT_FEAT_ONESHOT;
	अगर (hc->boot_cfg & HPET_TN_PERIODIC) अणु
		evt->features		|= CLOCK_EVT_FEAT_PERIODIC;
		evt->set_state_periodic	= hpet_clkevt_set_state_periodic;
	पूर्ण
पूर्ण

अटल व्योम __init hpet_legacy_घड़ीevent_रेजिस्टर(काष्ठा hpet_channel *hc)
अणु
	/*
	 * Start HPET with the boot CPU's cpumask and make it global after
	 * the IO_APIC has been initialized.
	 */
	hc->cpu = boot_cpu_data.cpu_index;
	म_नकलन(hc->name, "hpet", माप(hc->name));
	hpet_init_घड़ीevent(hc, 50);

	hc->evt.tick_resume	= hpet_clkevt_legacy_resume;

	/*
	 * Legacy horrors and sins from the past. HPET used periodic mode
	 * unconditionally क्रमever on the legacy channel 0. Removing the
	 * below hack and using the conditional in hpet_init_घड़ीevent()
	 * makes at least Qemu and one hardware machine fail to boot.
	 * There are two issues which cause the boot failure:
	 *
	 * #1 After the समयr delivery test in IOAPIC and the IOAPIC setup
	 *    the next पूर्णांकerrupt is not delivered despite the HPET channel
	 *    being programmed correctly. Reprogramming the HPET after
	 *    चयनing to IOAPIC makes it work again. After fixing this,
	 *    the next issue surfaces:
	 *
	 * #2 Due to the unconditional periodic mode availability the Local
	 *    APIC समयr calibration can hijack the global घड़ीevents
	 *    event handler without causing damage. Using oneshot at this
	 *    stage makes अगर hang because the HPET करोes not get
	 *    reprogrammed due to the handler hijacking. Duh, stupid me!
	 *
	 * Both issues require major surgery and especially the kick HPET
	 * again after enabling IOAPIC results in really nasty hackery.
	 * This 'assume periodic works' magic has survived since HPET
	 * support got added, so it's questionable whether this should be
	 * fixed. Both Qemu and the failing hardware machine support
	 * periodic mode despite the fact that both करोn't advertise it in
	 * the configuration रेजिस्टर and both need that extra kick after
	 * चयनing to IOAPIC. Seems to be a feature...
	 */
	hc->evt.features		|= CLOCK_EVT_FEAT_PERIODIC;
	hc->evt.set_state_periodic	= hpet_clkevt_set_state_periodic;

	/* Start HPET legacy पूर्णांकerrupts */
	hpet_enable_legacy_पूर्णांक();

	घड़ीevents_config_and_रेजिस्टर(&hc->evt, hpet_freq,
					HPET_MIN_PROG_DELTA, 0x7FFFFFFF);
	global_घड़ी_event = &hc->evt;
	pr_debug("Clockevent registered\n");
पूर्ण

/*
 * HPET MSI Support
 */
#अगर_घोषित CONFIG_GENERIC_MSI_IRQ
अटल व्योम hpet_msi_unmask(काष्ठा irq_data *data)
अणु
	काष्ठा hpet_channel *hc = irq_data_get_irq_handler_data(data);
	अचिन्हित पूर्णांक cfg;

	cfg = hpet_पढ़ोl(HPET_Tn_CFG(hc->num));
	cfg |= HPET_TN_ENABLE | HPET_TN_FSB;
	hpet_ग_लिखोl(cfg, HPET_Tn_CFG(hc->num));
पूर्ण

अटल व्योम hpet_msi_mask(काष्ठा irq_data *data)
अणु
	काष्ठा hpet_channel *hc = irq_data_get_irq_handler_data(data);
	अचिन्हित पूर्णांक cfg;

	cfg = hpet_पढ़ोl(HPET_Tn_CFG(hc->num));
	cfg &= ~(HPET_TN_ENABLE | HPET_TN_FSB);
	hpet_ग_लिखोl(cfg, HPET_Tn_CFG(hc->num));
पूर्ण

अटल व्योम hpet_msi_ग_लिखो(काष्ठा hpet_channel *hc, काष्ठा msi_msg *msg)
अणु
	hpet_ग_लिखोl(msg->data, HPET_Tn_ROUTE(hc->num));
	hpet_ग_लिखोl(msg->address_lo, HPET_Tn_ROUTE(hc->num) + 4);
पूर्ण

अटल व्योम hpet_msi_ग_लिखो_msg(काष्ठा irq_data *data, काष्ठा msi_msg *msg)
अणु
	hpet_msi_ग_लिखो(irq_data_get_irq_handler_data(data), msg);
पूर्ण

अटल काष्ठा irq_chip hpet_msi_controller __ro_after_init = अणु
	.name = "HPET-MSI",
	.irq_unmask = hpet_msi_unmask,
	.irq_mask = hpet_msi_mask,
	.irq_ack = irq_chip_ack_parent,
	.irq_set_affinity = msi_करोमुख्य_set_affinity,
	.irq_retrigger = irq_chip_retrigger_hierarchy,
	.irq_ग_लिखो_msi_msg = hpet_msi_ग_लिखो_msg,
	.flags = IRQCHIP_SKIP_SET_WAKE,
पूर्ण;

अटल पूर्णांक hpet_msi_init(काष्ठा irq_करोमुख्य *करोमुख्य,
			 काष्ठा msi_करोमुख्य_info *info, अचिन्हित पूर्णांक virq,
			 irq_hw_number_t hwirq, msi_alloc_info_t *arg)
अणु
	irq_set_status_flags(virq, IRQ_MOVE_PCNTXT);
	irq_करोमुख्य_set_info(करोमुख्य, virq, arg->hwirq, info->chip, शून्य,
			    handle_edge_irq, arg->data, "edge");

	वापस 0;
पूर्ण

अटल व्योम hpet_msi_मुक्त(काष्ठा irq_करोमुख्य *करोमुख्य,
			  काष्ठा msi_करोमुख्य_info *info, अचिन्हित पूर्णांक virq)
अणु
	irq_clear_status_flags(virq, IRQ_MOVE_PCNTXT);
पूर्ण

अटल काष्ठा msi_करोमुख्य_ops hpet_msi_करोमुख्य_ops = अणु
	.msi_init	= hpet_msi_init,
	.msi_मुक्त	= hpet_msi_मुक्त,
पूर्ण;

अटल काष्ठा msi_करोमुख्य_info hpet_msi_करोमुख्य_info = अणु
	.ops		= &hpet_msi_करोमुख्य_ops,
	.chip		= &hpet_msi_controller,
	.flags		= MSI_FLAG_USE_DEF_DOM_OPS,
पूर्ण;

अटल काष्ठा irq_करोमुख्य *hpet_create_irq_करोमुख्य(पूर्णांक hpet_id)
अणु
	काष्ठा msi_करोमुख्य_info *करोमुख्य_info;
	काष्ठा irq_करोमुख्य *parent, *d;
	काष्ठा fwnode_handle *fn;
	काष्ठा irq_fwspec fwspec;

	अगर (x86_vector_करोमुख्य == शून्य)
		वापस शून्य;

	करोमुख्य_info = kzalloc(माप(*करोमुख्य_info), GFP_KERNEL);
	अगर (!करोमुख्य_info)
		वापस शून्य;

	*करोमुख्य_info = hpet_msi_करोमुख्य_info;
	करोमुख्य_info->data = (व्योम *)(दीर्घ)hpet_id;

	fn = irq_करोमुख्य_alloc_named_id_fwnode(hpet_msi_controller.name,
					      hpet_id);
	अगर (!fn) अणु
		kमुक्त(करोमुख्य_info);
		वापस शून्य;
	पूर्ण

	fwspec.fwnode = fn;
	fwspec.param_count = 1;
	fwspec.param[0] = hpet_id;

	parent = irq_find_matching_fwspec(&fwspec, DOMAIN_BUS_ANY);
	अगर (!parent) अणु
		irq_करोमुख्य_मुक्त_fwnode(fn);
		kमुक्त(करोमुख्य_info);
		वापस शून्य;
	पूर्ण
	अगर (parent != x86_vector_करोमुख्य)
		hpet_msi_controller.name = "IR-HPET-MSI";

	d = msi_create_irq_करोमुख्य(fn, करोमुख्य_info, parent);
	अगर (!d) अणु
		irq_करोमुख्य_मुक्त_fwnode(fn);
		kमुक्त(करोमुख्य_info);
	पूर्ण
	वापस d;
पूर्ण

अटल अंतरभूत पूर्णांक hpet_dev_id(काष्ठा irq_करोमुख्य *करोमुख्य)
अणु
	काष्ठा msi_करोमुख्य_info *info = msi_get_करोमुख्य_info(करोमुख्य);

	वापस (पूर्णांक)(दीर्घ)info->data;
पूर्ण

अटल पूर्णांक hpet_assign_irq(काष्ठा irq_करोमुख्य *करोमुख्य, काष्ठा hpet_channel *hc,
			   पूर्णांक dev_num)
अणु
	काष्ठा irq_alloc_info info;

	init_irq_alloc_info(&info, शून्य);
	info.type = X86_IRQ_ALLOC_TYPE_HPET;
	info.data = hc;
	info.devid = hpet_dev_id(करोमुख्य);
	info.hwirq = dev_num;

	वापस irq_करोमुख्य_alloc_irqs(करोमुख्य, 1, NUMA_NO_NODE, &info);
पूर्ण

अटल पूर्णांक hpet_clkevt_msi_resume(काष्ठा घड़ी_event_device *evt)
अणु
	काष्ठा hpet_channel *hc = घड़ीevent_to_channel(evt);
	काष्ठा irq_data *data = irq_get_irq_data(hc->irq);
	काष्ठा msi_msg msg;

	/* Restore the MSI msg and unmask the पूर्णांकerrupt */
	irq_chip_compose_msi_msg(data, &msg);
	hpet_msi_ग_लिखो(hc, &msg);
	hpet_msi_unmask(data);
	वापस 0;
पूर्ण

अटल irqवापस_t hpet_msi_पूर्णांकerrupt_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा hpet_channel *hc = data;
	काष्ठा घड़ी_event_device *evt = &hc->evt;

	अगर (!evt->event_handler) अणु
		pr_info("Spurious interrupt HPET channel %d\n", hc->num);
		वापस IRQ_HANDLED;
	पूर्ण

	evt->event_handler(evt);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक hpet_setup_msi_irq(काष्ठा hpet_channel *hc)
अणु
	अगर (request_irq(hc->irq, hpet_msi_पूर्णांकerrupt_handler,
			IRQF_TIMER | IRQF_NOBALANCING,
			hc->name, hc))
		वापस -1;

	disable_irq(hc->irq);
	irq_set_affinity(hc->irq, cpumask_of(hc->cpu));
	enable_irq(hc->irq);

	pr_debug("%s irq %u for MSI\n", hc->name, hc->irq);

	वापस 0;
पूर्ण

/* Invoked from the hotplug callback on @cpu */
अटल व्योम init_one_hpet_msi_घड़ीevent(काष्ठा hpet_channel *hc, पूर्णांक cpu)
अणु
	काष्ठा घड़ी_event_device *evt = &hc->evt;

	hc->cpu = cpu;
	per_cpu(cpu_hpet_channel, cpu) = hc;
	hpet_setup_msi_irq(hc);

	hpet_init_घड़ीevent(hc, 110);
	evt->tick_resume = hpet_clkevt_msi_resume;

	घड़ीevents_config_and_रेजिस्टर(evt, hpet_freq, HPET_MIN_PROG_DELTA,
					0x7FFFFFFF);
पूर्ण

अटल काष्ठा hpet_channel *hpet_get_unused_घड़ीevent(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < hpet_base.nr_channels; i++) अणु
		काष्ठा hpet_channel *hc = hpet_base.channels + i;

		अगर (hc->mode != HPET_MODE_CLOCKEVT || hc->in_use)
			जारी;
		hc->in_use = 1;
		वापस hc;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक hpet_cpuhp_online(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा hpet_channel *hc = hpet_get_unused_घड़ीevent();

	अगर (hc)
		init_one_hpet_msi_घड़ीevent(hc, cpu);
	वापस 0;
पूर्ण

अटल पूर्णांक hpet_cpuhp_dead(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा hpet_channel *hc = per_cpu(cpu_hpet_channel, cpu);

	अगर (!hc)
		वापस 0;
	मुक्त_irq(hc->irq, hc);
	hc->in_use = 0;
	per_cpu(cpu_hpet_channel, cpu) = शून्य;
	वापस 0;
पूर्ण

अटल व्योम __init hpet_select_घड़ीevents(व्योम)
अणु
	अचिन्हित पूर्णांक i;

	hpet_base.nr_घड़ीevents = 0;

	/* No poपूर्णांक अगर MSI is disabled or CPU has an Always Runing APIC Timer */
	अगर (hpet_msi_disable || boot_cpu_has(X86_FEATURE_ARAT))
		वापस;

	hpet_prपूर्णांक_config();

	hpet_करोमुख्य = hpet_create_irq_करोमुख्य(hpet_blockid);
	अगर (!hpet_करोमुख्य)
		वापस;

	क्रम (i = 0; i < hpet_base.nr_channels; i++) अणु
		काष्ठा hpet_channel *hc = hpet_base.channels + i;
		पूर्णांक irq;

		अगर (hc->mode != HPET_MODE_UNUSED)
			जारी;

		/* Only consider HPET channel with MSI support */
		अगर (!(hc->boot_cfg & HPET_TN_FSB_CAP))
			जारी;

		प्र_लिखो(hc->name, "hpet%d", i);

		irq = hpet_assign_irq(hpet_करोमुख्य, hc, hc->num);
		अगर (irq <= 0)
			जारी;

		hc->irq = irq;
		hc->mode = HPET_MODE_CLOCKEVT;

		अगर (++hpet_base.nr_घड़ीevents == num_possible_cpus())
			अवरोध;
	पूर्ण

	pr_info("%d channels of %d reserved for per-cpu timers\n",
		hpet_base.nr_channels, hpet_base.nr_घड़ीevents);
पूर्ण

#अन्यथा

अटल अंतरभूत व्योम hpet_select_घड़ीevents(व्योम) अणु पूर्ण

#घोषणा hpet_cpuhp_online	शून्य
#घोषणा hpet_cpuhp_dead		शून्य

#पूर्ण_अगर

/*
 * Clock source related code
 */
#अगर defined(CONFIG_SMP) && defined(CONFIG_64BIT)
/*
 * Reading the HPET counter is a very slow operation. If a large number of
 * CPUs are trying to access the HPET counter simultaneously, it can cause
 * massive delays and slow करोwn प्रणाली perक्रमmance dramatically. This may
 * happen when HPET is the शेष घड़ी source instead of TSC. For a
 * really large प्रणाली with hundreds of CPUs, the slowकरोwn may be so
 * severe, that it can actually crash the प्रणाली because of a NMI watchकरोg
 * soft lockup, क्रम example.
 *
 * If multiple CPUs are trying to access the HPET counter at the same समय,
 * we करोn't actually need to पढ़ो the counter multiple बार. Instead, the
 * other CPUs can use the counter value पढ़ो by the first CPU in the group.
 *
 * This special feature is only enabled on x86-64 प्रणालीs. It is unlikely
 * that 32-bit x86 प्रणालीs will have enough CPUs to require this feature
 * with its associated locking overhead. We also need 64-bit atomic पढ़ो.
 *
 * The lock and the HPET value are stored together and can be पढ़ो in a
 * single atomic 64-bit पढ़ो. It is explicitly assumed that arch_spinlock_t
 * is 32 bits in size.
 */
जोड़ hpet_lock अणु
	काष्ठा अणु
		arch_spinlock_t lock;
		u32 value;
	पूर्ण;
	u64 lockval;
पूर्ण;

अटल जोड़ hpet_lock hpet __cacheline_aligned = अणु
	अणु .lock = __ARCH_SPIN_LOCK_UNLOCKED, पूर्ण,
पूर्ण;

अटल u64 पढ़ो_hpet(काष्ठा घड़ीsource *cs)
अणु
	अचिन्हित दीर्घ flags;
	जोड़ hpet_lock old, new;

	BUILD_BUG_ON(माप(जोड़ hpet_lock) != 8);

	/*
	 * Read HPET directly अगर in NMI.
	 */
	अगर (in_nmi())
		वापस (u64)hpet_पढ़ोl(HPET_COUNTER);

	/*
	 * Read the current state of the lock and HPET value atomically.
	 */
	old.lockval = READ_ONCE(hpet.lockval);

	अगर (arch_spin_is_locked(&old.lock))
		जाओ contended;

	local_irq_save(flags);
	अगर (arch_spin_trylock(&hpet.lock)) अणु
		new.value = hpet_पढ़ोl(HPET_COUNTER);
		/*
		 * Use WRITE_ONCE() to prevent store tearing.
		 */
		WRITE_ONCE(hpet.value, new.value);
		arch_spin_unlock(&hpet.lock);
		local_irq_restore(flags);
		वापस (u64)new.value;
	पूर्ण
	local_irq_restore(flags);

contended:
	/*
	 * Contended हाल
	 * --------------
	 * Wait until the HPET value change or the lock is मुक्त to indicate
	 * its value is up-to-date.
	 *
	 * It is possible that old.value has alपढ़ोy contained the latest
	 * HPET value जबतक the lock holder was in the process of releasing
	 * the lock. Checking क्रम lock state change will enable us to वापस
	 * the value immediately instead of रुकोing क्रम the next HPET पढ़ोer
	 * to come aदीर्घ.
	 */
	करो अणु
		cpu_relax();
		new.lockval = READ_ONCE(hpet.lockval);
	पूर्ण जबतक ((new.value == old.value) && arch_spin_is_locked(&new.lock));

	वापस (u64)new.value;
पूर्ण
#अन्यथा
/*
 * For UP or 32-bit.
 */
अटल u64 पढ़ो_hpet(काष्ठा घड़ीsource *cs)
अणु
	वापस (u64)hpet_पढ़ोl(HPET_COUNTER);
पूर्ण
#पूर्ण_अगर

अटल काष्ठा घड़ीsource घड़ीsource_hpet = अणु
	.name		= "hpet",
	.rating		= 250,
	.पढ़ो		= पढ़ो_hpet,
	.mask		= HPET_MASK,
	.flags		= CLOCK_SOURCE_IS_CONTINUOUS,
	.resume		= hpet_resume_counter,
पूर्ण;

/*
 * AMD SB700 based प्रणालीs with spपढ़ो spectrum enabled use a SMM based
 * HPET emulation to provide proper frequency setting.
 *
 * On such प्रणालीs the SMM code is initialized with the first HPET रेजिस्टर
 * access and takes some समय to complete. During this समय the config
 * रेजिस्टर पढ़ोs 0xffffffff. We check क्रम max 1000 loops whether the
 * config रेजिस्टर पढ़ोs a non-0xffffffff value to make sure that the
 * HPET is up and running beक्रमe we proceed any further.
 *
 * A counting loop is safe, as the HPET access takes thousands of CPU cycles.
 *
 * On non-SB700 based machines this check is only करोne once and has no
 * side effects.
 */
अटल bool __init hpet_cfg_working(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 1000; i++) अणु
		अगर (hpet_पढ़ोl(HPET_CFG) != 0xFFFFFFFF)
			वापस true;
	पूर्ण

	pr_warn("Config register invalid. Disabling HPET\n");
	वापस false;
पूर्ण

अटल bool __init hpet_counting(व्योम)
अणु
	u64 start, now, t1;

	hpet_restart_counter();

	t1 = hpet_पढ़ोl(HPET_COUNTER);
	start = rdtsc();

	/*
	 * We करोn't know the TSC frequency yet, but रुकोing क्रम
	 * 200000 TSC cycles is safe:
	 * 4 GHz == 50us
	 * 1 GHz == 200us
	 */
	करो अणु
		अगर (t1 != hpet_पढ़ोl(HPET_COUNTER))
			वापस true;
		now = rdtsc();
	पूर्ण जबतक ((now - start) < 200000UL);

	pr_warn("Counter not counting. HPET disabled\n");
	वापस false;
पूर्ण

/**
 * hpet_enable - Try to setup the HPET समयr. Returns 1 on success.
 */
पूर्णांक __init hpet_enable(व्योम)
अणु
	u32 hpet_period, cfg, id, irq;
	अचिन्हित पूर्णांक i, channels;
	काष्ठा hpet_channel *hc;
	u64 freq;

	अगर (!is_hpet_capable())
		वापस 0;

	hpet_set_mapping();
	अगर (!hpet_virt_address)
		वापस 0;

	/* Validate that the config रेजिस्टर is working */
	अगर (!hpet_cfg_working())
		जाओ out_nohpet;

	/*
	 * Read the period and check क्रम a sane value:
	 */
	hpet_period = hpet_पढ़ोl(HPET_PERIOD);
	अगर (hpet_period < HPET_MIN_PERIOD || hpet_period > HPET_MAX_PERIOD)
		जाओ out_nohpet;

	/* The period is a femtoseconds value. Convert it to a frequency. */
	freq = FSEC_PER_SEC;
	करो_भाग(freq, hpet_period);
	hpet_freq = freq;

	/*
	 * Read the HPET ID रेजिस्टर to retrieve the IRQ routing
	 * inक्रमmation and the number of channels
	 */
	id = hpet_पढ़ोl(HPET_ID);
	hpet_prपूर्णांक_config();

	/* This is the HPET channel number which is zero based */
	channels = ((id & HPET_ID_NUMBER) >> HPET_ID_NUMBER_SHIFT) + 1;

	/*
	 * The legacy routing mode needs at least two channels, tick समयr
	 * and the rtc emulation channel.
	 */
	अगर (IS_ENABLED(CONFIG_HPET_EMULATE_RTC) && channels < 2)
		जाओ out_nohpet;

	hc = kसुस्मृति(channels, माप(*hc), GFP_KERNEL);
	अगर (!hc) अणु
		pr_warn("Disabling HPET.\n");
		जाओ out_nohpet;
	पूर्ण
	hpet_base.channels = hc;
	hpet_base.nr_channels = channels;

	/* Read, store and sanitize the global configuration */
	cfg = hpet_पढ़ोl(HPET_CFG);
	hpet_base.boot_cfg = cfg;
	cfg &= ~(HPET_CFG_ENABLE | HPET_CFG_LEGACY);
	hpet_ग_लिखोl(cfg, HPET_CFG);
	अगर (cfg)
		pr_warn("Global config: Unknown bits %#x\n", cfg);

	/* Read, store and sanitize the per channel configuration */
	क्रम (i = 0; i < channels; i++, hc++) अणु
		hc->num = i;

		cfg = hpet_पढ़ोl(HPET_Tn_CFG(i));
		hc->boot_cfg = cfg;
		irq = (cfg & Tn_INT_ROUTE_CNF_MASK) >> Tn_INT_ROUTE_CNF_SHIFT;
		hc->irq = irq;

		cfg &= ~(HPET_TN_ENABLE | HPET_TN_LEVEL | HPET_TN_FSB);
		hpet_ग_लिखोl(cfg, HPET_Tn_CFG(i));

		cfg &= ~(HPET_TN_PERIODIC | HPET_TN_PERIODIC_CAP
			 | HPET_TN_64BIT_CAP | HPET_TN_32BIT | HPET_TN_ROUTE
			 | HPET_TN_FSB | HPET_TN_FSB_CAP);
		अगर (cfg)
			pr_warn("Channel #%u config: Unknown bits %#x\n", i, cfg);
	पूर्ण
	hpet_prपूर्णांक_config();

	/*
	 * Validate that the counter is counting. This needs to be करोne
	 * after sanitizing the config रेजिस्टरs to properly deal with
	 * क्रमce enabled HPETs.
	 */
	अगर (!hpet_counting())
		जाओ out_nohpet;

	घड़ीsource_रेजिस्टर_hz(&घड़ीsource_hpet, (u32)hpet_freq);

	अगर (id & HPET_ID_LEGSUP) अणु
		hpet_legacy_घड़ीevent_रेजिस्टर(&hpet_base.channels[0]);
		hpet_base.channels[0].mode = HPET_MODE_LEGACY;
		अगर (IS_ENABLED(CONFIG_HPET_EMULATE_RTC))
			hpet_base.channels[1].mode = HPET_MODE_LEGACY;
		वापस 1;
	पूर्ण
	वापस 0;

out_nohpet:
	kमुक्त(hpet_base.channels);
	hpet_base.channels = शून्य;
	hpet_base.nr_channels = 0;
	hpet_clear_mapping();
	hpet_address = 0;
	वापस 0;
पूर्ण

/*
 * The late initialization runs after the PCI quirks have been invoked
 * which might have detected a प्रणाली on which the HPET can be enक्रमced.
 *
 * Also, the MSI machinery is not working yet when the HPET is initialized
 * early.
 *
 * If the HPET is enabled, then:
 *
 *  1) Reserve one channel क्रम /dev/hpet अगर CONFIG_HPET=y
 *  2) Reserve up to num_possible_cpus() channels as per CPU घड़ीevents
 *  3) Setup /dev/hpet अगर CONFIG_HPET=y
 *  4) Register hotplug callbacks when घड़ीevents are available
 */
अटल __init पूर्णांक hpet_late_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (!hpet_address) अणु
		अगर (!क्रमce_hpet_address)
			वापस -ENODEV;

		hpet_address = क्रमce_hpet_address;
		hpet_enable();
	पूर्ण

	अगर (!hpet_virt_address)
		वापस -ENODEV;

	hpet_select_device_channel();
	hpet_select_घड़ीevents();
	hpet_reserve_platक्रमm_समयrs();
	hpet_prपूर्णांक_config();

	अगर (!hpet_base.nr_घड़ीevents)
		वापस 0;

	ret = cpuhp_setup_state(CPUHP_AP_X86_HPET_ONLINE, "x86/hpet:online",
				hpet_cpuhp_online, शून्य);
	अगर (ret)
		वापस ret;
	ret = cpuhp_setup_state(CPUHP_X86_HPET_DEAD, "x86/hpet:dead", शून्य,
				hpet_cpuhp_dead);
	अगर (ret)
		जाओ err_cpuhp;
	वापस 0;

err_cpuhp:
	cpuhp_हटाओ_state(CPUHP_AP_X86_HPET_ONLINE);
	वापस ret;
पूर्ण
fs_initcall(hpet_late_init);

व्योम hpet_disable(व्योम)
अणु
	अचिन्हित पूर्णांक i;
	u32 cfg;

	अगर (!is_hpet_capable() || !hpet_virt_address)
		वापस;

	/* Restore boot configuration with the enable bit cleared */
	cfg = hpet_base.boot_cfg;
	cfg &= ~HPET_CFG_ENABLE;
	hpet_ग_लिखोl(cfg, HPET_CFG);

	/* Restore the channel boot configuration */
	क्रम (i = 0; i < hpet_base.nr_channels; i++)
		hpet_ग_लिखोl(hpet_base.channels[i].boot_cfg, HPET_Tn_CFG(i));

	/* If the HPET was enabled at boot समय, reenable it */
	अगर (hpet_base.boot_cfg & HPET_CFG_ENABLE)
		hpet_ग_लिखोl(hpet_base.boot_cfg, HPET_CFG);
पूर्ण

#अगर_घोषित CONFIG_HPET_EMULATE_RTC

/*
 * HPET in LegacyReplacement mode eats up the RTC पूर्णांकerrupt line. When HPET
 * is enabled, we support RTC पूर्णांकerrupt functionality in software.
 *
 * RTC has 3 kinds of पूर्णांकerrupts:
 *
 *  1) Update Interrupt - generate an पूर्णांकerrupt, every second, when the
 *     RTC घड़ी is updated
 *  2) Alarm Interrupt - generate an पूर्णांकerrupt at a specअगरic समय of day
 *  3) Periodic Interrupt - generate periodic पूर्णांकerrupt, with frequencies
 *     2Hz-8192Hz (2Hz-64Hz क्रम non-root user) (all frequencies in घातers of 2)
 *
 * (1) and (2) above are implemented using polling at a frequency of 64 Hz:
 * DEFAULT_RTC_INT_FREQ.
 *
 * The exact frequency is a tradeoff between accuracy and पूर्णांकerrupt overhead.
 *
 * For (3), we use पूर्णांकerrupts at 64 Hz, or the user specअगरied periodic frequency,
 * अगर it's higher.
 */
#समावेश <linux/mc146818rtc.h>
#समावेश <linux/rtc.h>

#घोषणा DEFAULT_RTC_INT_FREQ	64
#घोषणा DEFAULT_RTC_SHIFT	6
#घोषणा RTC_NUM_INTS		1

अटल अचिन्हित दीर्घ hpet_rtc_flags;
अटल पूर्णांक hpet_prev_update_sec;
अटल काष्ठा rtc_समय hpet_alarm_समय;
अटल अचिन्हित दीर्घ hpet_pie_count;
अटल u32 hpet_t1_cmp;
अटल u32 hpet_शेष_delta;
अटल u32 hpet_pie_delta;
अटल अचिन्हित दीर्घ hpet_pie_limit;

अटल rtc_irq_handler irq_handler;

/*
 * Check that the HPET counter c1 is ahead of c2
 */
अटल अंतरभूत पूर्णांक hpet_cnt_ahead(u32 c1, u32 c2)
अणु
	वापस (s32)(c2 - c1) < 0;
पूर्ण

/*
 * Registers a IRQ handler.
 */
पूर्णांक hpet_रेजिस्टर_irq_handler(rtc_irq_handler handler)
अणु
	अगर (!is_hpet_enabled())
		वापस -ENODEV;
	अगर (irq_handler)
		वापस -EBUSY;

	irq_handler = handler;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(hpet_रेजिस्टर_irq_handler);

/*
 * Deरेजिस्टरs the IRQ handler रेजिस्टरed with hpet_रेजिस्टर_irq_handler()
 * and करोes cleanup.
 */
व्योम hpet_unरेजिस्टर_irq_handler(rtc_irq_handler handler)
अणु
	अगर (!is_hpet_enabled())
		वापस;

	irq_handler = शून्य;
	hpet_rtc_flags = 0;
पूर्ण
EXPORT_SYMBOL_GPL(hpet_unरेजिस्टर_irq_handler);

/*
 * Channel 1 क्रम RTC emulation. We use one shot mode, as periodic mode
 * is not supported by all HPET implementations क्रम channel 1.
 *
 * hpet_rtc_समयr_init() is called when the rtc is initialized.
 */
पूर्णांक hpet_rtc_समयr_init(व्योम)
अणु
	अचिन्हित पूर्णांक cfg, cnt, delta;
	अचिन्हित दीर्घ flags;

	अगर (!is_hpet_enabled())
		वापस 0;

	अगर (!hpet_शेष_delta) अणु
		काष्ठा घड़ी_event_device *evt = &hpet_base.channels[0].evt;
		uपूर्णांक64_t clc;

		clc = (uपूर्णांक64_t) evt->mult * NSEC_PER_SEC;
		clc >>= evt->shअगरt + DEFAULT_RTC_SHIFT;
		hpet_शेष_delta = clc;
	पूर्ण

	अगर (!(hpet_rtc_flags & RTC_PIE) || hpet_pie_limit)
		delta = hpet_शेष_delta;
	अन्यथा
		delta = hpet_pie_delta;

	local_irq_save(flags);

	cnt = delta + hpet_पढ़ोl(HPET_COUNTER);
	hpet_ग_लिखोl(cnt, HPET_T1_CMP);
	hpet_t1_cmp = cnt;

	cfg = hpet_पढ़ोl(HPET_T1_CFG);
	cfg &= ~HPET_TN_PERIODIC;
	cfg |= HPET_TN_ENABLE | HPET_TN_32BIT;
	hpet_ग_लिखोl(cfg, HPET_T1_CFG);

	local_irq_restore(flags);

	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(hpet_rtc_समयr_init);

अटल व्योम hpet_disable_rtc_channel(व्योम)
अणु
	u32 cfg = hpet_पढ़ोl(HPET_T1_CFG);

	cfg &= ~HPET_TN_ENABLE;
	hpet_ग_लिखोl(cfg, HPET_T1_CFG);
पूर्ण

/*
 * The functions below are called from rtc driver.
 * Return 0 अगर HPET is not being used.
 * Otherwise करो the necessary changes and वापस 1.
 */
पूर्णांक hpet_mask_rtc_irq_bit(अचिन्हित दीर्घ bit_mask)
अणु
	अगर (!is_hpet_enabled())
		वापस 0;

	hpet_rtc_flags &= ~bit_mask;
	अगर (unlikely(!hpet_rtc_flags))
		hpet_disable_rtc_channel();

	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(hpet_mask_rtc_irq_bit);

पूर्णांक hpet_set_rtc_irq_bit(अचिन्हित दीर्घ bit_mask)
अणु
	अचिन्हित दीर्घ oldbits = hpet_rtc_flags;

	अगर (!is_hpet_enabled())
		वापस 0;

	hpet_rtc_flags |= bit_mask;

	अगर ((bit_mask & RTC_UIE) && !(oldbits & RTC_UIE))
		hpet_prev_update_sec = -1;

	अगर (!oldbits)
		hpet_rtc_समयr_init();

	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(hpet_set_rtc_irq_bit);

पूर्णांक hpet_set_alarm_समय(अचिन्हित अक्षर hrs, अचिन्हित अक्षर min, अचिन्हित अक्षर sec)
अणु
	अगर (!is_hpet_enabled())
		वापस 0;

	hpet_alarm_समय.पंचांग_hour = hrs;
	hpet_alarm_समय.पंचांग_min = min;
	hpet_alarm_समय.पंचांग_sec = sec;

	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(hpet_set_alarm_समय);

पूर्णांक hpet_set_periodic_freq(अचिन्हित दीर्घ freq)
अणु
	uपूर्णांक64_t clc;

	अगर (!is_hpet_enabled())
		वापस 0;

	अगर (freq <= DEFAULT_RTC_INT_FREQ) अणु
		hpet_pie_limit = DEFAULT_RTC_INT_FREQ / freq;
	पूर्ण अन्यथा अणु
		काष्ठा घड़ी_event_device *evt = &hpet_base.channels[0].evt;

		clc = (uपूर्णांक64_t) evt->mult * NSEC_PER_SEC;
		करो_भाग(clc, freq);
		clc >>= evt->shअगरt;
		hpet_pie_delta = clc;
		hpet_pie_limit = 0;
	पूर्ण

	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(hpet_set_periodic_freq);

पूर्णांक hpet_rtc_dropped_irq(व्योम)
अणु
	वापस is_hpet_enabled();
पूर्ण
EXPORT_SYMBOL_GPL(hpet_rtc_dropped_irq);

अटल व्योम hpet_rtc_समयr_reinit(व्योम)
अणु
	अचिन्हित पूर्णांक delta;
	पूर्णांक lost_पूर्णांकs = -1;

	अगर (unlikely(!hpet_rtc_flags))
		hpet_disable_rtc_channel();

	अगर (!(hpet_rtc_flags & RTC_PIE) || hpet_pie_limit)
		delta = hpet_शेष_delta;
	अन्यथा
		delta = hpet_pie_delta;

	/*
	 * Increment the comparator value until we are ahead of the
	 * current count.
	 */
	करो अणु
		hpet_t1_cmp += delta;
		hpet_ग_लिखोl(hpet_t1_cmp, HPET_T1_CMP);
		lost_पूर्णांकs++;
	पूर्ण जबतक (!hpet_cnt_ahead(hpet_t1_cmp, hpet_पढ़ोl(HPET_COUNTER)));

	अगर (lost_पूर्णांकs) अणु
		अगर (hpet_rtc_flags & RTC_PIE)
			hpet_pie_count += lost_पूर्णांकs;
		अगर (prपूर्णांकk_ratelimit())
			pr_warn("Lost %d RTC interrupts\n", lost_पूर्णांकs);
	पूर्ण
पूर्ण

irqवापस_t hpet_rtc_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा rtc_समय curr_समय;
	अचिन्हित दीर्घ rtc_पूर्णांक_flag = 0;

	hpet_rtc_समयr_reinit();
	स_रखो(&curr_समय, 0, माप(काष्ठा rtc_समय));

	अगर (hpet_rtc_flags & (RTC_UIE | RTC_AIE))
		mc146818_get_समय(&curr_समय);

	अगर (hpet_rtc_flags & RTC_UIE &&
	    curr_समय.पंचांग_sec != hpet_prev_update_sec) अणु
		अगर (hpet_prev_update_sec >= 0)
			rtc_पूर्णांक_flag = RTC_UF;
		hpet_prev_update_sec = curr_समय.पंचांग_sec;
	पूर्ण

	अगर (hpet_rtc_flags & RTC_PIE && ++hpet_pie_count >= hpet_pie_limit) अणु
		rtc_पूर्णांक_flag |= RTC_PF;
		hpet_pie_count = 0;
	पूर्ण

	अगर (hpet_rtc_flags & RTC_AIE &&
	    (curr_समय.पंचांग_sec == hpet_alarm_समय.पंचांग_sec) &&
	    (curr_समय.पंचांग_min == hpet_alarm_समय.पंचांग_min) &&
	    (curr_समय.पंचांग_hour == hpet_alarm_समय.पंचांग_hour))
		rtc_पूर्णांक_flag |= RTC_AF;

	अगर (rtc_पूर्णांक_flag) अणु
		rtc_पूर्णांक_flag |= (RTC_IRQF | (RTC_NUM_INTS << 8));
		अगर (irq_handler)
			irq_handler(rtc_पूर्णांक_flag, dev_id);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण
EXPORT_SYMBOL_GPL(hpet_rtc_पूर्णांकerrupt);
#पूर्ण_अगर
