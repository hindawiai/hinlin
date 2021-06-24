<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Reset driver क्रम Axxia devices
 *
 * Copyright (C) 2014 LSI
 */
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reboot.h>
#समावेश <linux/regmap.h>

#घोषणा SC_CRIT_WRITE_KEY	0x1000
#घोषणा SC_LATCH_ON_RESET	0x1004
#घोषणा SC_RESET_CONTROL	0x1008
#घोषणा   RSTCTL_RST_ZERO	(1<<3)
#घोषणा   RSTCTL_RST_FAB	(1<<2)
#घोषणा   RSTCTL_RST_CHIP	(1<<1)
#घोषणा   RSTCTL_RST_SYS	(1<<0)
#घोषणा SC_EFUSE_INT_STATUS	0x180c
#घोषणा   EFUSE_READ_DONE	(1<<31)

अटल काष्ठा regmap *syscon;

अटल पूर्णांक axxia_restart_handler(काष्ठा notअगरier_block *this,
				 अचिन्हित दीर्घ mode, व्योम *cmd)
अणु
	/* Access Key (0xab) */
	regmap_ग_लिखो(syscon, SC_CRIT_WRITE_KEY, 0xab);
	/* Select पूर्णांकernal boot from 0xffff0000 */
	regmap_ग_लिखो(syscon, SC_LATCH_ON_RESET, 0x00000040);
	/* Assert ResetReadDone (to aव्योम hanging in boot ROM) */
	regmap_ग_लिखो(syscon, SC_EFUSE_INT_STATUS, EFUSE_READ_DONE);
	/* Assert chip reset */
	regmap_update_bits(syscon, SC_RESET_CONTROL,
			   RSTCTL_RST_CHIP, RSTCTL_RST_CHIP);

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block axxia_restart_nb = अणु
	.notअगरier_call = axxia_restart_handler,
	.priority = 128,
पूर्ण;

अटल पूर्णांक axxia_reset_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक err;

	syscon = syscon_regmap_lookup_by_phandle(dev->of_node, "syscon");
	अगर (IS_ERR(syscon)) अणु
		pr_err("%pOFn: syscon lookup failed\n", dev->of_node);
		वापस PTR_ERR(syscon);
	पूर्ण

	err = रेजिस्टर_restart_handler(&axxia_restart_nb);
	अगर (err)
		dev_err(dev, "cannot register restart handler (err=%d)\n", err);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_axxia_reset_match[] = अणु
	अणु .compatible = "lsi,axm55xx-reset", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, of_axxia_reset_match);

अटल काष्ठा platक्रमm_driver axxia_reset_driver = अणु
	.probe = axxia_reset_probe,
	.driver = अणु
		.name = "axxia-reset",
		.of_match_table = of_match_ptr(of_axxia_reset_match),
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init axxia_reset_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&axxia_reset_driver);
पूर्ण
device_initcall(axxia_reset_init);
