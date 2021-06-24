<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Copyright (C) 2012 ARM Limited
 */

#समावेश <linux/delay.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reboot.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/vexpress.h>

अटल व्योम vexpress_reset_करो(काष्ठा device *dev, स्थिर अक्षर *what)
अणु
	पूर्णांक err = -ENOENT;
	काष्ठा regmap *reg = dev_get_drvdata(dev);

	अगर (reg) अणु
		err = regmap_ग_लिखो(reg, 0, 0);
		अगर (!err)
			mdelay(1000);
	पूर्ण

	dev_emerg(dev, "Unable to %s (%d)\n", what, err);
पूर्ण

अटल काष्ठा device *vexpress_घातer_off_device;
अटल atomic_t vexpress_restart_nb_refcnt = ATOMIC_INIT(0);

अटल व्योम vexpress_घातer_off(व्योम)
अणु
	vexpress_reset_करो(vexpress_घातer_off_device, "power off");
पूर्ण

अटल काष्ठा device *vexpress_restart_device;

अटल पूर्णांक vexpress_restart(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ mode,
			     व्योम *cmd)
अणु
	vexpress_reset_करो(vexpress_restart_device, "restart");

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block vexpress_restart_nb = अणु
	.notअगरier_call = vexpress_restart,
	.priority = 128,
पूर्ण;

अटल sमाप_प्रकार vexpress_reset_active_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", vexpress_restart_device == dev);
पूर्ण

अटल sमाप_प्रकार vexpress_reset_active_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	दीर्घ value;
	पूर्णांक err = kम_से_दीर्घ(buf, 0, &value);

	अगर (!err && value)
		vexpress_restart_device = dev;

	वापस err ? err : count;
पूर्ण

अटल DEVICE_ATTR(active, S_IRUGO | S_IWUSR, vexpress_reset_active_show,
		   vexpress_reset_active_store);


क्रमागत vexpress_reset_func अणु FUNC_RESET, FUNC_SHUTDOWN, FUNC_REBOOT पूर्ण;

अटल स्थिर काष्ठा of_device_id vexpress_reset_of_match[] = अणु
	अणु
		.compatible = "arm,vexpress-reset",
		.data = (व्योम *)FUNC_RESET,
	पूर्ण, अणु
		.compatible = "arm,vexpress-shutdown",
		.data = (व्योम *)FUNC_SHUTDOWN
	पूर्ण, अणु
		.compatible = "arm,vexpress-reboot",
		.data = (व्योम *)FUNC_REBOOT
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक _vexpress_रेजिस्टर_restart_handler(काष्ठा device *dev)
अणु
	पूर्णांक err;

	vexpress_restart_device = dev;
	अगर (atomic_inc_वापस(&vexpress_restart_nb_refcnt) == 1) अणु
		err = रेजिस्टर_restart_handler(&vexpress_restart_nb);
		अगर (err) अणु
			dev_err(dev, "cannot register restart handler (err=%d)\n", err);
			atomic_dec(&vexpress_restart_nb_refcnt);
			वापस err;
		पूर्ण
	पूर्ण
	device_create_file(dev, &dev_attr_active);

	वापस 0;
पूर्ण

अटल पूर्णांक vexpress_reset_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *match =
			of_match_device(vexpress_reset_of_match, &pdev->dev);
	काष्ठा regmap *regmap;
	पूर्णांक ret = 0;

	अगर (!match)
		वापस -EINVAL;

	regmap = devm_regmap_init_vexpress_config(&pdev->dev);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);
	dev_set_drvdata(&pdev->dev, regmap);

	चयन ((क्रमागत vexpress_reset_func)match->data) अणु
	हाल FUNC_SHUTDOWN:
		vexpress_घातer_off_device = &pdev->dev;
		pm_घातer_off = vexpress_घातer_off;
		अवरोध;
	हाल FUNC_RESET:
		अगर (!vexpress_restart_device)
			ret = _vexpress_रेजिस्टर_restart_handler(&pdev->dev);
		अवरोध;
	हाल FUNC_REBOOT:
		ret = _vexpress_रेजिस्टर_restart_handler(&pdev->dev);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver vexpress_reset_driver = अणु
	.probe = vexpress_reset_probe,
	.driver = अणु
		.name = "vexpress-reset",
		.of_match_table = vexpress_reset_of_match,
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(vexpress_reset_driver);
