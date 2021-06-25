<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Renesas R-Mobile Reset Driver
 *
 * Copyright (C) 2014 Glider bvba
 */

#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/reboot.h>

/* SYSC Register Bank 2 */
#घोषणा RESCNT2		0x20		/* Reset Control Register 2 */

/* Reset Control Register 2 */
#घोषणा RESCNT2_PRES	0x80000000	/* Soft घातer-on reset */

अटल व्योम __iomem *sysc_base2;

अटल पूर्णांक rmobile_reset_handler(काष्ठा notअगरier_block *this,
				 अचिन्हित दीर्घ mode, व्योम *cmd)
अणु
	pr_debug("%s %lu\n", __func__, mode);

	/* Let's assume we have acquired the HPB semaphore */
	ग_लिखोl(RESCNT2_PRES, sysc_base2 + RESCNT2);

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block rmobile_reset_nb = अणु
	.notअगरier_call = rmobile_reset_handler,
	.priority = 192,
पूर्ण;

अटल पूर्णांक rmobile_reset_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक error;

	sysc_base2 = of_iomap(pdev->dev.of_node, 1);
	अगर (!sysc_base2)
		वापस -ENODEV;

	error = रेजिस्टर_restart_handler(&rmobile_reset_nb);
	अगर (error) अणु
		dev_err(&pdev->dev,
			"cannot register restart handler (err=%d)\n", error);
		जाओ fail_unmap;
	पूर्ण

	वापस 0;

fail_unmap:
	iounmap(sysc_base2);
	वापस error;
पूर्ण

अटल पूर्णांक rmobile_reset_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	unरेजिस्टर_restart_handler(&rmobile_reset_nb);
	iounmap(sysc_base2);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id rmobile_reset_of_match[] = अणु
	अणु .compatible = "renesas,sysc-rmobile", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, rmobile_reset_of_match);

अटल काष्ठा platक्रमm_driver rmobile_reset_driver = अणु
	.probe = rmobile_reset_probe,
	.हटाओ = rmobile_reset_हटाओ,
	.driver = अणु
		.name = "rmobile_reset",
		.of_match_table = rmobile_reset_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(rmobile_reset_driver);

MODULE_DESCRIPTION("Renesas R-Mobile Reset Driver");
MODULE_AUTHOR("Geert Uytterhoeven <geert+renesas@glider.be>");
MODULE_LICENSE("GPL v2");
