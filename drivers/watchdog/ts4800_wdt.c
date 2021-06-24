<शैली गुरु>
/*
 * Watchकरोg driver क्रम TS-4800 based boards
 *
 * Copyright (c) 2015 - Savoir-faire Linux
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/watchकरोg.h>

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout,
	"Watchdog cannot be stopped once started (default="
	__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

/* possible feed values */
#घोषणा TS4800_WDT_FEED_2S       0x1
#घोषणा TS4800_WDT_FEED_10S      0x2
#घोषणा TS4800_WDT_DISABLE       0x3

काष्ठा ts4800_wdt अणु
	काष्ठा watchकरोg_device  wdd;
	काष्ठा regmap           *regmap;
	u32                     feed_offset;
	u32                     feed_val;
पूर्ण;

/*
 * TS-4800 supports the following समयout values:
 *
 *   value desc
 *   ---------------------
 *     0    feed क्रम 338ms
 *     1    feed क्रम 2.706s
 *     2    feed क्रम 10.824s
 *     3    disable watchकरोg
 *
 * Keep the regmap/समयout map ordered by समयout
 */
अटल स्थिर काष्ठा अणु
	स्थिर पूर्णांक समयout;
	स्थिर पूर्णांक regval;
पूर्ण ts4800_wdt_map[] = अणु
	अणु 2,  TS4800_WDT_FEED_2S पूर्ण,
	अणु 10, TS4800_WDT_FEED_10S पूर्ण,
पूर्ण;

#घोषणा MAX_TIMEOUT_INDEX       (ARRAY_SIZE(ts4800_wdt_map) - 1)

अटल व्योम ts4800_ग_लिखो_feed(काष्ठा ts4800_wdt *wdt, u32 val)
अणु
	regmap_ग_लिखो(wdt->regmap, wdt->feed_offset, val);
पूर्ण

अटल पूर्णांक ts4800_wdt_start(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा ts4800_wdt *wdt = watchकरोg_get_drvdata(wdd);

	ts4800_ग_लिखो_feed(wdt, wdt->feed_val);
	वापस 0;
पूर्ण

अटल पूर्णांक ts4800_wdt_stop(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा ts4800_wdt *wdt = watchकरोg_get_drvdata(wdd);

	ts4800_ग_लिखो_feed(wdt, TS4800_WDT_DISABLE);
	वापस 0;
पूर्ण

अटल पूर्णांक ts4800_wdt_set_समयout(काष्ठा watchकरोg_device *wdd,
				  अचिन्हित पूर्णांक समयout)
अणु
	काष्ठा ts4800_wdt *wdt = watchकरोg_get_drvdata(wdd);
	पूर्णांक i;

	क्रम (i = 0; i < MAX_TIMEOUT_INDEX; i++) अणु
		अगर (ts4800_wdt_map[i].समयout >= समयout)
			अवरोध;
	पूर्ण

	wdd->समयout = ts4800_wdt_map[i].समयout;
	wdt->feed_val = ts4800_wdt_map[i].regval;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_ops ts4800_wdt_ops = अणु
	.owner = THIS_MODULE,
	.start = ts4800_wdt_start,
	.stop = ts4800_wdt_stop,
	.set_समयout = ts4800_wdt_set_समयout,
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_info ts4800_wdt_info = अणु
	.options = WDIOF_SETTIMEOUT | WDIOF_MAGICCLOSE | WDIOF_KEEPALIVEPING,
	.identity = "TS-4800 Watchdog",
पूर्ण;

अटल पूर्णांक ts4800_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा device_node *syscon_np;
	काष्ठा watchकरोg_device *wdd;
	काष्ठा ts4800_wdt *wdt;
	u32 reg;
	पूर्णांक ret;

	syscon_np = of_parse_phandle(np, "syscon", 0);
	अगर (!syscon_np) अणु
		dev_err(dev, "no syscon property\n");
		वापस -ENODEV;
	पूर्ण

	ret = of_property_पढ़ो_u32_index(np, "syscon", 1, &reg);
	अगर (ret < 0) अणु
		dev_err(dev, "no offset in syscon\n");
		वापस ret;
	पूर्ण

	/* allocate memory क्रम watchकरोg काष्ठा */
	wdt = devm_kzalloc(dev, माप(*wdt), GFP_KERNEL);
	अगर (!wdt)
		वापस -ENOMEM;

	/* set regmap and offset to know where to ग_लिखो */
	wdt->feed_offset = reg;
	wdt->regmap = syscon_node_to_regmap(syscon_np);
	of_node_put(syscon_np);
	अगर (IS_ERR(wdt->regmap)) अणु
		dev_err(dev, "cannot get parent's regmap\n");
		वापस PTR_ERR(wdt->regmap);
	पूर्ण

	/* Initialize काष्ठा watchकरोg_device */
	wdd = &wdt->wdd;
	wdd->parent = dev;
	wdd->info = &ts4800_wdt_info;
	wdd->ops = &ts4800_wdt_ops;
	wdd->min_समयout = ts4800_wdt_map[0].समयout;
	wdd->max_समयout = ts4800_wdt_map[MAX_TIMEOUT_INDEX].समयout;

	watchकरोg_set_drvdata(wdd, wdt);
	watchकरोg_set_nowayout(wdd, nowayout);
	watchकरोg_init_समयout(wdd, 0, dev);

	/*
	 * As this watchकरोg supports only a few values, ts4800_wdt_set_समयout
	 * must be called to initialize समयout and feed_val with valid values.
	 * Default to maximum समयout अगर none, or an invalid one, is provided in
	 * device tree.
	 */
	अगर (!wdd->समयout)
		wdd->समयout = wdd->max_समयout;
	ts4800_wdt_set_समयout(wdd, wdd->समयout);

	/*
	 * The feed रेजिस्टर is ग_लिखो-only, so it is not possible to determine
	 * watchकरोg's state. Disable it to be in a known state.
	 */
	ts4800_wdt_stop(wdd);

	ret = devm_watchकरोg_रेजिस्टर_device(dev, wdd);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, wdt);

	dev_info(dev, "initialized (timeout = %d sec, nowayout = %d)\n",
		 wdd->समयout, nowayout);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ts4800_wdt_of_match[] = अणु
	अणु .compatible = "technologic,ts4800-wdt", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ts4800_wdt_of_match);

अटल काष्ठा platक्रमm_driver ts4800_wdt_driver = अणु
	.probe		= ts4800_wdt_probe,
	.driver		= अणु
		.name	= "ts4800_wdt",
		.of_match_table = ts4800_wdt_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(ts4800_wdt_driver);

MODULE_AUTHOR("Damien Riegel <damien.riegel@savoirfairelinux.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:ts4800_wdt");
