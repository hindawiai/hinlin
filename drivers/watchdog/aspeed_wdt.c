<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2016 IBM Corporation
 *
 * Joel Stanley <joel@jms.id.au>
 */

#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/watchकरोg.h>

काष्ठा aspeed_wdt अणु
	काष्ठा watchकरोg_device	wdd;
	व्योम __iomem		*base;
	u32			ctrl;
पूर्ण;

काष्ठा aspeed_wdt_config अणु
	u32 ext_pulse_width_mask;
पूर्ण;

अटल स्थिर काष्ठा aspeed_wdt_config ast2400_config = अणु
	.ext_pulse_width_mask = 0xff,
पूर्ण;

अटल स्थिर काष्ठा aspeed_wdt_config ast2500_config = अणु
	.ext_pulse_width_mask = 0xfffff,
पूर्ण;

अटल स्थिर काष्ठा of_device_id aspeed_wdt_of_table[] = अणु
	अणु .compatible = "aspeed,ast2400-wdt", .data = &ast2400_config पूर्ण,
	अणु .compatible = "aspeed,ast2500-wdt", .data = &ast2500_config पूर्ण,
	अणु .compatible = "aspeed,ast2600-wdt", .data = &ast2500_config पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, aspeed_wdt_of_table);

#घोषणा WDT_STATUS		0x00
#घोषणा WDT_RELOAD_VALUE	0x04
#घोषणा WDT_RESTART		0x08
#घोषणा WDT_CTRL		0x0C
#घोषणा   WDT_CTRL_BOOT_SECONDARY	BIT(7)
#घोषणा   WDT_CTRL_RESET_MODE_SOC	(0x00 << 5)
#घोषणा   WDT_CTRL_RESET_MODE_FULL_CHIP	(0x01 << 5)
#घोषणा   WDT_CTRL_RESET_MODE_ARM_CPU	(0x10 << 5)
#घोषणा   WDT_CTRL_1MHZ_CLK		BIT(4)
#घोषणा   WDT_CTRL_WDT_EXT		BIT(3)
#घोषणा   WDT_CTRL_WDT_INTR		BIT(2)
#घोषणा   WDT_CTRL_RESET_SYSTEM		BIT(1)
#घोषणा   WDT_CTRL_ENABLE		BIT(0)
#घोषणा WDT_TIMEOUT_STATUS	0x10
#घोषणा   WDT_TIMEOUT_STATUS_BOOT_SECONDARY	BIT(1)
#घोषणा WDT_CLEAR_TIMEOUT_STATUS	0x14
#घोषणा   WDT_CLEAR_TIMEOUT_AND_BOOT_CODE_SELECTION	BIT(0)

/*
 * WDT_RESET_WIDTH controls the अक्षरacteristics of the बाह्यal pulse (अगर
 * enabled), specअगरically:
 *
 * * Pulse duration
 * * Drive mode: push-pull vs खोलो-drain
 * * Polarity: Active high or active low
 *
 * Pulse duration configuration is available on both the AST2400 and AST2500,
 * though the field changes between SoCs:
 *
 * AST2400: Bits 7:0
 * AST2500: Bits 19:0
 *
 * This dअगरference is captured in काष्ठा aspeed_wdt_config.
 *
 * The AST2500 exposes the drive mode and polarity options, but not in a
 * regular fashion. For पढ़ो purposes, bit 31 represents active high or low,
 * and bit 30 represents push-pull or खोलो-drain. With respect to ग_लिखो, magic
 * values need to be written to the top byte to change the state of the drive
 * mode and polarity bits. Any other value written to the top byte has no
 * effect on the state of the drive mode or polarity bits. However, the pulse
 * width value must be preserved (as desired) अगर written.
 */
#घोषणा WDT_RESET_WIDTH		0x18
#घोषणा   WDT_RESET_WIDTH_ACTIVE_HIGH	BIT(31)
#घोषणा     WDT_ACTIVE_HIGH_MAGIC	(0xA5 << 24)
#घोषणा     WDT_ACTIVE_LOW_MAGIC	(0x5A << 24)
#घोषणा   WDT_RESET_WIDTH_PUSH_PULL	BIT(30)
#घोषणा     WDT_PUSH_PULL_MAGIC		(0xA8 << 24)
#घोषणा     WDT_OPEN_DRAIN_MAGIC	(0x8A << 24)

#घोषणा WDT_RESTART_MAGIC	0x4755

/* 32 bits at 1MHz, in milliseconds */
#घोषणा WDT_MAX_TIMEOUT_MS	4294967
#घोषणा WDT_DEFAULT_TIMEOUT	30
#घोषणा WDT_RATE_1MHZ		1000000

अटल काष्ठा aspeed_wdt *to_aspeed_wdt(काष्ठा watchकरोg_device *wdd)
अणु
	वापस container_of(wdd, काष्ठा aspeed_wdt, wdd);
पूर्ण

अटल व्योम aspeed_wdt_enable(काष्ठा aspeed_wdt *wdt, पूर्णांक count)
अणु
	wdt->ctrl |= WDT_CTRL_ENABLE;

	ग_लिखोl(0, wdt->base + WDT_CTRL);
	ग_लिखोl(count, wdt->base + WDT_RELOAD_VALUE);
	ग_लिखोl(WDT_RESTART_MAGIC, wdt->base + WDT_RESTART);
	ग_लिखोl(wdt->ctrl, wdt->base + WDT_CTRL);
पूर्ण

अटल पूर्णांक aspeed_wdt_start(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा aspeed_wdt *wdt = to_aspeed_wdt(wdd);

	aspeed_wdt_enable(wdt, wdd->समयout * WDT_RATE_1MHZ);

	वापस 0;
पूर्ण

अटल पूर्णांक aspeed_wdt_stop(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा aspeed_wdt *wdt = to_aspeed_wdt(wdd);

	wdt->ctrl &= ~WDT_CTRL_ENABLE;
	ग_लिखोl(wdt->ctrl, wdt->base + WDT_CTRL);

	वापस 0;
पूर्ण

अटल पूर्णांक aspeed_wdt_ping(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा aspeed_wdt *wdt = to_aspeed_wdt(wdd);

	ग_लिखोl(WDT_RESTART_MAGIC, wdt->base + WDT_RESTART);

	वापस 0;
पूर्ण

अटल पूर्णांक aspeed_wdt_set_समयout(काष्ठा watchकरोg_device *wdd,
				  अचिन्हित पूर्णांक समयout)
अणु
	काष्ठा aspeed_wdt *wdt = to_aspeed_wdt(wdd);
	u32 actual;

	wdd->समयout = समयout;

	actual = min(समयout, wdd->max_hw_heartbeat_ms * 1000);

	ग_लिखोl(actual * WDT_RATE_1MHZ, wdt->base + WDT_RELOAD_VALUE);
	ग_लिखोl(WDT_RESTART_MAGIC, wdt->base + WDT_RESTART);

	वापस 0;
पूर्ण

अटल पूर्णांक aspeed_wdt_restart(काष्ठा watchकरोg_device *wdd,
			      अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा aspeed_wdt *wdt = to_aspeed_wdt(wdd);

	wdt->ctrl &= ~WDT_CTRL_BOOT_SECONDARY;
	aspeed_wdt_enable(wdt, 128 * WDT_RATE_1MHZ / 1000);

	mdelay(1000);

	वापस 0;
पूर्ण

/* access_cs0 shows अगर cs0 is accessible, hence the reverted bit */
अटल sमाप_प्रकार access_cs0_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा aspeed_wdt *wdt = dev_get_drvdata(dev);
	u32 status = पढ़ोl(wdt->base + WDT_TIMEOUT_STATUS);

	वापस प्र_लिखो(buf, "%u\n",
		      !(status & WDT_TIMEOUT_STATUS_BOOT_SECONDARY));
पूर्ण

अटल sमाप_प्रकार access_cs0_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
				माप_प्रकार size)
अणु
	काष्ठा aspeed_wdt *wdt = dev_get_drvdata(dev);
	अचिन्हित दीर्घ val;

	अगर (kम_से_अदीर्घ(buf, 10, &val))
		वापस -EINVAL;

	अगर (val)
		ग_लिखोl(WDT_CLEAR_TIMEOUT_AND_BOOT_CODE_SELECTION,
		       wdt->base + WDT_CLEAR_TIMEOUT_STATUS);

	वापस size;
पूर्ण

/*
 * This attribute exists only अगर the प्रणाली has booted from the alternate
 * flash with 'alt-boot' option.
 *
 * At alternate flash the 'access_cs0' sysfs node provides:
 *   ast2400: a way to get access to the primary SPI flash chip at CS0
 *            after booting from the alternate chip at CS1.
 *   ast2500: a way to restore the normal address mapping from
 *            (CS0->CS1, CS1->CS0) to (CS0->CS0, CS1->CS1).
 *
 * Clearing the boot code selection and समयout counter also resets to the
 * initial state the chip select line mapping. When the SoC is in normal
 * mapping state (i.e. booted from CS0), clearing those bits करोes nothing क्रम
 * both versions of the SoC. For alternate boot mode (booted from CS1 due to
 * wdt2 expiration) the behavior dअगरfers as described above.
 *
 * This option can be used with wdt2 (watchकरोg1) only.
 */
अटल DEVICE_ATTR_RW(access_cs0);

अटल काष्ठा attribute *bचयन_attrs[] = अणु
	&dev_attr_access_cs0.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(bचयन);

अटल स्थिर काष्ठा watchकरोg_ops aspeed_wdt_ops = अणु
	.start		= aspeed_wdt_start,
	.stop		= aspeed_wdt_stop,
	.ping		= aspeed_wdt_ping,
	.set_समयout	= aspeed_wdt_set_समयout,
	.restart	= aspeed_wdt_restart,
	.owner		= THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_info aspeed_wdt_info = अणु
	.options	= WDIOF_KEEPALIVEPING
			| WDIOF_MAGICCLOSE
			| WDIOF_SETTIMEOUT,
	.identity	= KBUILD_MODNAME,
पूर्ण;

अटल पूर्णांक aspeed_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा aspeed_wdt_config *config;
	स्थिर काष्ठा of_device_id *ofdid;
	काष्ठा aspeed_wdt *wdt;
	काष्ठा device_node *np;
	स्थिर अक्षर *reset_type;
	u32 duration;
	u32 status;
	पूर्णांक ret;

	wdt = devm_kzalloc(dev, माप(*wdt), GFP_KERNEL);
	अगर (!wdt)
		वापस -ENOMEM;

	wdt->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(wdt->base))
		वापस PTR_ERR(wdt->base);

	wdt->wdd.info = &aspeed_wdt_info;
	wdt->wdd.ops = &aspeed_wdt_ops;
	wdt->wdd.max_hw_heartbeat_ms = WDT_MAX_TIMEOUT_MS;
	wdt->wdd.parent = dev;

	wdt->wdd.समयout = WDT_DEFAULT_TIMEOUT;
	watchकरोg_init_समयout(&wdt->wdd, 0, dev);

	np = dev->of_node;

	ofdid = of_match_node(aspeed_wdt_of_table, np);
	अगर (!ofdid)
		वापस -EINVAL;
	config = ofdid->data;

	/*
	 * On घड़ी rates:
	 *  - ast2400 wdt can run at PCLK, or 1MHz
	 *  - ast2500 only runs at 1MHz, hard coding bit 4 to 1
	 *  - ast2600 always runs at 1MHz
	 *
	 * Set the ast2400 to run at 1MHz as it simplअगरies the driver.
	 */
	अगर (of_device_is_compatible(np, "aspeed,ast2400-wdt"))
		wdt->ctrl = WDT_CTRL_1MHZ_CLK;

	/*
	 * Control reset on a per-device basis to ensure the
	 * host is not affected by a BMC reboot
	 */
	ret = of_property_पढ़ो_string(np, "aspeed,reset-type", &reset_type);
	अगर (ret) अणु
		wdt->ctrl |= WDT_CTRL_RESET_MODE_SOC | WDT_CTRL_RESET_SYSTEM;
	पूर्ण अन्यथा अणु
		अगर (!म_भेद(reset_type, "cpu"))
			wdt->ctrl |= WDT_CTRL_RESET_MODE_ARM_CPU |
				     WDT_CTRL_RESET_SYSTEM;
		अन्यथा अगर (!म_भेद(reset_type, "soc"))
			wdt->ctrl |= WDT_CTRL_RESET_MODE_SOC |
				     WDT_CTRL_RESET_SYSTEM;
		अन्यथा अगर (!म_भेद(reset_type, "system"))
			wdt->ctrl |= WDT_CTRL_RESET_MODE_FULL_CHIP |
				     WDT_CTRL_RESET_SYSTEM;
		अन्यथा अगर (म_भेद(reset_type, "none"))
			वापस -EINVAL;
	पूर्ण
	अगर (of_property_पढ़ो_bool(np, "aspeed,external-signal"))
		wdt->ctrl |= WDT_CTRL_WDT_EXT;
	अगर (of_property_पढ़ो_bool(np, "aspeed,alt-boot"))
		wdt->ctrl |= WDT_CTRL_BOOT_SECONDARY;

	अगर (पढ़ोl(wdt->base + WDT_CTRL) & WDT_CTRL_ENABLE)  अणु
		/*
		 * The watchकरोg is running, but invoke aspeed_wdt_start() to
		 * ग_लिखो wdt->ctrl to WDT_CTRL to ensure the watchकरोg's
		 * configuration conक्रमms to the driver's expectations.
		 * Primarily, ensure we're using the 1MHz घड़ी source.
		 */
		aspeed_wdt_start(&wdt->wdd);
		set_bit(WDOG_HW_RUNNING, &wdt->wdd.status);
	पूर्ण

	अगर ((of_device_is_compatible(np, "aspeed,ast2500-wdt")) ||
		(of_device_is_compatible(np, "aspeed,ast2600-wdt"))) अणु
		u32 reg = पढ़ोl(wdt->base + WDT_RESET_WIDTH);

		reg &= config->ext_pulse_width_mask;
		अगर (of_property_पढ़ो_bool(np, "aspeed,ext-push-pull"))
			reg |= WDT_PUSH_PULL_MAGIC;
		अन्यथा
			reg |= WDT_OPEN_DRAIN_MAGIC;

		ग_लिखोl(reg, wdt->base + WDT_RESET_WIDTH);

		reg &= config->ext_pulse_width_mask;
		अगर (of_property_पढ़ो_bool(np, "aspeed,ext-active-high"))
			reg |= WDT_ACTIVE_HIGH_MAGIC;
		अन्यथा
			reg |= WDT_ACTIVE_LOW_MAGIC;

		ग_लिखोl(reg, wdt->base + WDT_RESET_WIDTH);
	पूर्ण

	अगर (!of_property_पढ़ो_u32(np, "aspeed,ext-pulse-duration", &duration)) अणु
		u32 max_duration = config->ext_pulse_width_mask + 1;

		अगर (duration == 0 || duration > max_duration) अणु
			dev_err(dev, "Invalid pulse duration: %uus\n",
				duration);
			duration = max(1U, min(max_duration, duration));
			dev_info(dev, "Pulse duration set to %uus\n",
				 duration);
		पूर्ण

		/*
		 * The watchकरोg is always configured with a 1MHz source, so
		 * there is no need to scale the microsecond value. However we
		 * need to offset it - from the datasheet:
		 *
		 * "This रेजिस्टर decides the निश्चितing duration of wdt_ext and
		 * wdt_rstarm संकेत. The शेष value is 0xFF. It means the
		 * शेष निश्चितing duration of wdt_ext and wdt_rstarm is
		 * 256us."
		 *
		 * This implies a value of 0 gives a 1us pulse.
		 */
		ग_लिखोl(duration - 1, wdt->base + WDT_RESET_WIDTH);
	पूर्ण

	status = पढ़ोl(wdt->base + WDT_TIMEOUT_STATUS);
	अगर (status & WDT_TIMEOUT_STATUS_BOOT_SECONDARY) अणु
		wdt->wdd.bootstatus = WDIOF_CARDRESET;

		अगर (of_device_is_compatible(np, "aspeed,ast2400-wdt") ||
		    of_device_is_compatible(np, "aspeed,ast2500-wdt"))
			wdt->wdd.groups = bचयन_groups;
	पूर्ण

	dev_set_drvdata(dev, wdt);

	वापस devm_watchकरोg_रेजिस्टर_device(dev, &wdt->wdd);
पूर्ण

अटल काष्ठा platक्रमm_driver aspeed_watchकरोg_driver = अणु
	.probe = aspeed_wdt_probe,
	.driver = अणु
		.name = KBUILD_MODNAME,
		.of_match_table = of_match_ptr(aspeed_wdt_of_table),
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init aspeed_wdt_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&aspeed_watchकरोg_driver);
पूर्ण
arch_initcall(aspeed_wdt_init);

अटल व्योम __निकास aspeed_wdt_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&aspeed_watchकरोg_driver);
पूर्ण
module_निकास(aspeed_wdt_निकास);

MODULE_DESCRIPTION("Aspeed Watchdog Driver");
MODULE_LICENSE("GPL");
