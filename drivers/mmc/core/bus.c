<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/drivers/mmc/core/bus.c
 *
 *  Copyright (C) 2003 Russell King, All Rights Reserved.
 *  Copyright (C) 2007 Pierre Ossman
 *
 *  MMC card bus driver model
 */

#समावेश <linux/export.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/of.h>
#समावेश <linux/pm_runसमय.स>

#समावेश <linux/mmc/card.h>
#समावेश <linux/mmc/host.h>

#समावेश "core.h"
#समावेश "card.h"
#समावेश "host.h"
#समावेश "sdio_cis.h"
#समावेश "bus.h"

#घोषणा to_mmc_driver(d)	container_of(d, काष्ठा mmc_driver, drv)

अटल sमाप_प्रकार type_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mmc_card *card = mmc_dev_to_card(dev);

	चयन (card->type) अणु
	हाल MMC_TYPE_MMC:
		वापस प्र_लिखो(buf, "MMC\n");
	हाल MMC_TYPE_SD:
		वापस प्र_लिखो(buf, "SD\n");
	हाल MMC_TYPE_SDIO:
		वापस प्र_लिखो(buf, "SDIO\n");
	हाल MMC_TYPE_SD_COMBO:
		वापस प्र_लिखो(buf, "SDcombo\n");
	शेष:
		वापस -EFAULT;
	पूर्ण
पूर्ण
अटल DEVICE_ATTR_RO(type);

अटल काष्ठा attribute *mmc_dev_attrs[] = अणु
	&dev_attr_type.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(mmc_dev);

/*
 * This currently matches any MMC driver to any MMC card - drivers
 * themselves make the decision whether to drive this card in their
 * probe method.
 */
अटल पूर्णांक mmc_bus_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	वापस 1;
पूर्ण

अटल पूर्णांक
mmc_bus_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा mmc_card *card = mmc_dev_to_card(dev);
	स्थिर अक्षर *type;
	अचिन्हित पूर्णांक i;
	पूर्णांक retval = 0;

	चयन (card->type) अणु
	हाल MMC_TYPE_MMC:
		type = "MMC";
		अवरोध;
	हाल MMC_TYPE_SD:
		type = "SD";
		अवरोध;
	हाल MMC_TYPE_SDIO:
		type = "SDIO";
		अवरोध;
	हाल MMC_TYPE_SD_COMBO:
		type = "SDcombo";
		अवरोध;
	शेष:
		type = शून्य;
	पूर्ण

	अगर (type) अणु
		retval = add_uevent_var(env, "MMC_TYPE=%s", type);
		अगर (retval)
			वापस retval;
	पूर्ण

	अगर (card->type == MMC_TYPE_SDIO || card->type == MMC_TYPE_SD_COMBO) अणु
		retval = add_uevent_var(env, "SDIO_ID=%04X:%04X",
					card->cis.venकरोr, card->cis.device);
		अगर (retval)
			वापस retval;

		retval = add_uevent_var(env, "SDIO_REVISION=%u.%u",
					card->major_rev, card->minor_rev);
		अगर (retval)
			वापस retval;

		क्रम (i = 0; i < card->num_info; i++) अणु
			retval = add_uevent_var(env, "SDIO_INFO%u=%s", i+1, card->info[i]);
			अगर (retval)
				वापस retval;
		पूर्ण
	पूर्ण

	/*
	 * SDIO (non-combo) cards are not handled by mmc_block driver and करो not
	 * have accessible CID रेजिस्टर which used by mmc_card_name() function.
	 */
	अगर (card->type == MMC_TYPE_SDIO)
		वापस 0;

	retval = add_uevent_var(env, "MMC_NAME=%s", mmc_card_name(card));
	अगर (retval)
		वापस retval;

	/*
	 * Request the mmc_block device.  Note: that this is a direct request
	 * क्रम the module it carries no inक्रमmation as to what is inserted.
	 */
	retval = add_uevent_var(env, "MODALIAS=mmc:block");

	वापस retval;
पूर्ण

अटल पूर्णांक mmc_bus_probe(काष्ठा device *dev)
अणु
	काष्ठा mmc_driver *drv = to_mmc_driver(dev->driver);
	काष्ठा mmc_card *card = mmc_dev_to_card(dev);

	वापस drv->probe(card);
पूर्ण

अटल पूर्णांक mmc_bus_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा mmc_driver *drv = to_mmc_driver(dev->driver);
	काष्ठा mmc_card *card = mmc_dev_to_card(dev);

	drv->हटाओ(card);

	वापस 0;
पूर्ण

अटल व्योम mmc_bus_shutकरोwn(काष्ठा device *dev)
अणु
	काष्ठा mmc_driver *drv = to_mmc_driver(dev->driver);
	काष्ठा mmc_card *card = mmc_dev_to_card(dev);
	काष्ठा mmc_host *host = card->host;
	पूर्णांक ret;

	अगर (dev->driver && drv->shutकरोwn)
		drv->shutकरोwn(card);

	अगर (host->bus_ops->shutकरोwn) अणु
		ret = host->bus_ops->shutकरोwn(host);
		अगर (ret)
			pr_warn("%s: error %d during shutdown\n",
				mmc_hostname(host), ret);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक mmc_bus_suspend(काष्ठा device *dev)
अणु
	काष्ठा mmc_card *card = mmc_dev_to_card(dev);
	काष्ठा mmc_host *host = card->host;
	पूर्णांक ret;

	ret = pm_generic_suspend(dev);
	अगर (ret)
		वापस ret;

	ret = host->bus_ops->suspend(host);
	अगर (ret)
		pm_generic_resume(dev);

	वापस ret;
पूर्ण

अटल पूर्णांक mmc_bus_resume(काष्ठा device *dev)
अणु
	काष्ठा mmc_card *card = mmc_dev_to_card(dev);
	काष्ठा mmc_host *host = card->host;
	पूर्णांक ret;

	ret = host->bus_ops->resume(host);
	अगर (ret)
		pr_warn("%s: error %d during resume (card was removed?)\n",
			mmc_hostname(host), ret);

	ret = pm_generic_resume(dev);
	वापस ret;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM
अटल पूर्णांक mmc_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा mmc_card *card = mmc_dev_to_card(dev);
	काष्ठा mmc_host *host = card->host;

	वापस host->bus_ops->runसमय_suspend(host);
पूर्ण

अटल पूर्णांक mmc_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा mmc_card *card = mmc_dev_to_card(dev);
	काष्ठा mmc_host *host = card->host;

	वापस host->bus_ops->runसमय_resume(host);
पूर्ण
#पूर्ण_अगर /* !CONFIG_PM */

अटल स्थिर काष्ठा dev_pm_ops mmc_bus_pm_ops = अणु
	SET_RUNTIME_PM_OPS(mmc_runसमय_suspend, mmc_runसमय_resume, शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(mmc_bus_suspend, mmc_bus_resume)
पूर्ण;

अटल काष्ठा bus_type mmc_bus_type = अणु
	.name		= "mmc",
	.dev_groups	= mmc_dev_groups,
	.match		= mmc_bus_match,
	.uevent		= mmc_bus_uevent,
	.probe		= mmc_bus_probe,
	.हटाओ		= mmc_bus_हटाओ,
	.shutकरोwn	= mmc_bus_shutकरोwn,
	.pm		= &mmc_bus_pm_ops,
पूर्ण;

पूर्णांक mmc_रेजिस्टर_bus(व्योम)
अणु
	वापस bus_रेजिस्टर(&mmc_bus_type);
पूर्ण

व्योम mmc_unरेजिस्टर_bus(व्योम)
अणु
	bus_unरेजिस्टर(&mmc_bus_type);
पूर्ण

/**
 *	mmc_रेजिस्टर_driver - रेजिस्टर a media driver
 *	@drv: MMC media driver
 */
पूर्णांक mmc_रेजिस्टर_driver(काष्ठा mmc_driver *drv)
अणु
	drv->drv.bus = &mmc_bus_type;
	वापस driver_रेजिस्टर(&drv->drv);
पूर्ण

EXPORT_SYMBOL(mmc_रेजिस्टर_driver);

/**
 *	mmc_unरेजिस्टर_driver - unरेजिस्टर a media driver
 *	@drv: MMC media driver
 */
व्योम mmc_unरेजिस्टर_driver(काष्ठा mmc_driver *drv)
अणु
	drv->drv.bus = &mmc_bus_type;
	driver_unरेजिस्टर(&drv->drv);
पूर्ण

EXPORT_SYMBOL(mmc_unरेजिस्टर_driver);

अटल व्योम mmc_release_card(काष्ठा device *dev)
अणु
	काष्ठा mmc_card *card = mmc_dev_to_card(dev);

	sdio_मुक्त_common_cis(card);

	kमुक्त(card->info);

	kमुक्त(card);
पूर्ण

/*
 * Allocate and initialise a new MMC card काष्ठाure.
 */
काष्ठा mmc_card *mmc_alloc_card(काष्ठा mmc_host *host, काष्ठा device_type *type)
अणु
	काष्ठा mmc_card *card;

	card = kzalloc(माप(काष्ठा mmc_card), GFP_KERNEL);
	अगर (!card)
		वापस ERR_PTR(-ENOMEM);

	card->host = host;

	device_initialize(&card->dev);

	card->dev.parent = mmc_classdev(host);
	card->dev.bus = &mmc_bus_type;
	card->dev.release = mmc_release_card;
	card->dev.type = type;

	वापस card;
पूर्ण

/*
 * Register a new MMC card with the driver model.
 */
पूर्णांक mmc_add_card(काष्ठा mmc_card *card)
अणु
	पूर्णांक ret;
	स्थिर अक्षर *type;
	स्थिर अक्षर *uhs_bus_speed_mode = "";
	अटल स्थिर अक्षर *स्थिर uhs_speeds[] = अणु
		[UHS_SDR12_BUS_SPEED] = "SDR12 ",
		[UHS_SDR25_BUS_SPEED] = "SDR25 ",
		[UHS_SDR50_BUS_SPEED] = "SDR50 ",
		[UHS_SDR104_BUS_SPEED] = "SDR104 ",
		[UHS_DDR50_BUS_SPEED] = "DDR50 ",
	पूर्ण;


	dev_set_name(&card->dev, "%s:%04x", mmc_hostname(card->host), card->rca);

	चयन (card->type) अणु
	हाल MMC_TYPE_MMC:
		type = "MMC";
		अवरोध;
	हाल MMC_TYPE_SD:
		type = "SD";
		अगर (mmc_card_blockaddr(card)) अणु
			अगर (mmc_card_ext_capacity(card))
				type = "SDXC";
			अन्यथा
				type = "SDHC";
		पूर्ण
		अवरोध;
	हाल MMC_TYPE_SDIO:
		type = "SDIO";
		अवरोध;
	हाल MMC_TYPE_SD_COMBO:
		type = "SD-combo";
		अगर (mmc_card_blockaddr(card))
			type = "SDHC-combo";
		अवरोध;
	शेष:
		type = "?";
		अवरोध;
	पूर्ण

	अगर (mmc_card_uhs(card) &&
		(card->sd_bus_speed < ARRAY_SIZE(uhs_speeds)))
		uhs_bus_speed_mode = uhs_speeds[card->sd_bus_speed];

	अगर (mmc_host_is_spi(card->host)) अणु
		pr_info("%s: new %s%s%s card on SPI\n",
			mmc_hostname(card->host),
			mmc_card_hs(card) ? "high speed " : "",
			mmc_card_ddr52(card) ? "DDR " : "",
			type);
	पूर्ण अन्यथा अणु
		pr_info("%s: new %s%s%s%s%s%s card at address %04x\n",
			mmc_hostname(card->host),
			mmc_card_uhs(card) ? "ultra high speed " :
			(mmc_card_hs(card) ? "high speed " : ""),
			mmc_card_hs400(card) ? "HS400 " :
			(mmc_card_hs200(card) ? "HS200 " : ""),
			mmc_card_hs400es(card) ? "Enhanced strobe " : "",
			mmc_card_ddr52(card) ? "DDR " : "",
			uhs_bus_speed_mode, type, card->rca);
	पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
	mmc_add_card_debugfs(card);
#पूर्ण_अगर
	card->dev.of_node = mmc_of_find_child_device(card->host, 0);

	device_enable_async_suspend(&card->dev);

	ret = device_add(&card->dev);
	अगर (ret)
		वापस ret;

	mmc_card_set_present(card);

	वापस 0;
पूर्ण

/*
 * Unरेजिस्टर a new MMC card with the driver model, and
 * (eventually) मुक्त it.
 */
व्योम mmc_हटाओ_card(काष्ठा mmc_card *card)
अणु
	काष्ठा mmc_host *host = card->host;

#अगर_घोषित CONFIG_DEBUG_FS
	mmc_हटाओ_card_debugfs(card);
#पूर्ण_अगर

	अगर (mmc_card_present(card)) अणु
		अगर (mmc_host_is_spi(card->host)) अणु
			pr_info("%s: SPI card removed\n",
				mmc_hostname(card->host));
		पूर्ण अन्यथा अणु
			pr_info("%s: card %04x removed\n",
				mmc_hostname(card->host), card->rca);
		पूर्ण
		device_del(&card->dev);
		of_node_put(card->dev.of_node);
	पूर्ण

	अगर (host->cqe_enabled) अणु
		host->cqe_ops->cqe_disable(host);
		host->cqe_enabled = false;
	पूर्ण

	put_device(&card->dev);
पूर्ण
