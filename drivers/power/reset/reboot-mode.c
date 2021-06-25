<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2016, Fuzhou Rockchip Electronics Co., Ltd
 */

#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/reboot.h>
#समावेश <linux/reboot-mode.h>

#घोषणा PREFIX "mode-"

काष्ठा mode_info अणु
	स्थिर अक्षर *mode;
	u32 magic;
	काष्ठा list_head list;
पूर्ण;

अटल अचिन्हित पूर्णांक get_reboot_mode_magic(काष्ठा reboot_mode_driver *reboot,
					  स्थिर अक्षर *cmd)
अणु
	स्थिर अक्षर *normal = "normal";
	पूर्णांक magic = 0;
	काष्ठा mode_info *info;

	अगर (!cmd)
		cmd = normal;

	list_क्रम_each_entry(info, &reboot->head, list) अणु
		अगर (!म_भेद(info->mode, cmd)) अणु
			magic = info->magic;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस magic;
पूर्ण

अटल पूर्णांक reboot_mode_notअगरy(काष्ठा notअगरier_block *this,
			      अचिन्हित दीर्घ mode, व्योम *cmd)
अणु
	काष्ठा reboot_mode_driver *reboot;
	अचिन्हित पूर्णांक magic;

	reboot = container_of(this, काष्ठा reboot_mode_driver, reboot_notअगरier);
	magic = get_reboot_mode_magic(reboot, cmd);
	अगर (magic)
		reboot->ग_लिखो(reboot, magic);

	वापस NOTIFY_DONE;
पूर्ण

/**
 * reboot_mode_रेजिस्टर - रेजिस्टर a reboot mode driver
 * @reboot: reboot mode driver
 *
 * Returns: 0 on success or a negative error code on failure.
 */
पूर्णांक reboot_mode_रेजिस्टर(काष्ठा reboot_mode_driver *reboot)
अणु
	काष्ठा mode_info *info;
	काष्ठा property *prop;
	काष्ठा device_node *np = reboot->dev->of_node;
	माप_प्रकार len = म_माप(PREFIX);
	पूर्णांक ret;

	INIT_LIST_HEAD(&reboot->head);

	क्रम_each_property_of_node(np, prop) अणु
		अगर (म_भेदन(prop->name, PREFIX, len))
			जारी;

		info = devm_kzalloc(reboot->dev, माप(*info), GFP_KERNEL);
		अगर (!info) अणु
			ret = -ENOMEM;
			जाओ error;
		पूर्ण

		अगर (of_property_पढ़ो_u32(np, prop->name, &info->magic)) अणु
			dev_err(reboot->dev, "reboot mode %s without magic number\n",
				info->mode);
			devm_kमुक्त(reboot->dev, info);
			जारी;
		पूर्ण

		info->mode = kstrdup_स्थिर(prop->name + len, GFP_KERNEL);
		अगर (!info->mode) अणु
			ret =  -ENOMEM;
			जाओ error;
		पूर्ण अन्यथा अगर (info->mode[0] == '\0') अणु
			kमुक्त_स्थिर(info->mode);
			ret = -EINVAL;
			dev_err(reboot->dev, "invalid mode name(%s): too short!\n",
				prop->name);
			जाओ error;
		पूर्ण

		list_add_tail(&info->list, &reboot->head);
	पूर्ण

	reboot->reboot_notअगरier.notअगरier_call = reboot_mode_notअगरy;
	रेजिस्टर_reboot_notअगरier(&reboot->reboot_notअगरier);

	वापस 0;

error:
	list_क्रम_each_entry(info, &reboot->head, list)
		kमुक्त_स्थिर(info->mode);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(reboot_mode_रेजिस्टर);

/**
 * reboot_mode_unरेजिस्टर - unरेजिस्टर a reboot mode driver
 * @reboot: reboot mode driver
 */
पूर्णांक reboot_mode_unरेजिस्टर(काष्ठा reboot_mode_driver *reboot)
अणु
	काष्ठा mode_info *info;

	unरेजिस्टर_reboot_notअगरier(&reboot->reboot_notअगरier);

	list_क्रम_each_entry(info, &reboot->head, list)
		kमुक्त_स्थिर(info->mode);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(reboot_mode_unरेजिस्टर);

अटल व्योम devm_reboot_mode_release(काष्ठा device *dev, व्योम *res)
अणु
	reboot_mode_unरेजिस्टर(*(काष्ठा reboot_mode_driver **)res);
पूर्ण

/**
 * devm_reboot_mode_रेजिस्टर() - resource managed reboot_mode_रेजिस्टर()
 * @dev: device to associate this resource with
 * @reboot: reboot mode driver
 *
 * Returns: 0 on success or a negative error code on failure.
 */
पूर्णांक devm_reboot_mode_रेजिस्टर(काष्ठा device *dev,
			      काष्ठा reboot_mode_driver *reboot)
अणु
	काष्ठा reboot_mode_driver **dr;
	पूर्णांक rc;

	dr = devres_alloc(devm_reboot_mode_release, माप(*dr), GFP_KERNEL);
	अगर (!dr)
		वापस -ENOMEM;

	rc = reboot_mode_रेजिस्टर(reboot);
	अगर (rc) अणु
		devres_मुक्त(dr);
		वापस rc;
	पूर्ण

	*dr = reboot;
	devres_add(dev, dr);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(devm_reboot_mode_रेजिस्टर);

अटल पूर्णांक devm_reboot_mode_match(काष्ठा device *dev, व्योम *res, व्योम *data)
अणु
	काष्ठा reboot_mode_driver **p = res;

	अगर (WARN_ON(!p || !*p))
		वापस 0;

	वापस *p == data;
पूर्ण

/**
 * devm_reboot_mode_unरेजिस्टर() - resource managed reboot_mode_unरेजिस्टर()
 * @dev: device to associate this resource with
 * @reboot: reboot mode driver
 */
व्योम devm_reboot_mode_unरेजिस्टर(काष्ठा device *dev,
				 काष्ठा reboot_mode_driver *reboot)
अणु
	WARN_ON(devres_release(dev,
			       devm_reboot_mode_release,
			       devm_reboot_mode_match, reboot));
पूर्ण
EXPORT_SYMBOL_GPL(devm_reboot_mode_unरेजिस्टर);

MODULE_AUTHOR("Andy Yan <andy.yan@rock-chips.com>");
MODULE_DESCRIPTION("System reboot mode core library");
MODULE_LICENSE("GPL v2");
