<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * configfs.c - Implementation of configfs पूर्णांकerface to the driver stack
 *
 * Copyright (C) 2013-2015 Microchip Technology Germany II GmbH & Co. KG
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/configfs.h>
#समावेश <linux/most.h>

#घोषणा MAX_STRING_SIZE 80

काष्ठा mdev_link अणु
	काष्ठा config_item item;
	काष्ठा list_head list;
	bool create_link;
	bool destroy_link;
	u16 num_buffers;
	u16 buffer_size;
	u16 subbuffer_size;
	u16 packets_per_xact;
	u16 dbr_size;
	अक्षर datatype[MAX_STRING_SIZE];
	अक्षर direction[MAX_STRING_SIZE];
	अक्षर name[MAX_STRING_SIZE];
	अक्षर device[MAX_STRING_SIZE];
	अक्षर channel[MAX_STRING_SIZE];
	अक्षर comp[MAX_STRING_SIZE];
	अक्षर comp_params[MAX_STRING_SIZE];
पूर्ण;

अटल काष्ठा list_head mdev_link_list;

अटल पूर्णांक set_cfg_buffer_size(काष्ठा mdev_link *link)
अणु
	वापस most_set_cfg_buffer_size(link->device, link->channel,
					link->buffer_size);
पूर्ण

अटल पूर्णांक set_cfg_subbuffer_size(काष्ठा mdev_link *link)
अणु
	वापस most_set_cfg_subbuffer_size(link->device, link->channel,
					   link->subbuffer_size);
पूर्ण

अटल पूर्णांक set_cfg_dbr_size(काष्ठा mdev_link *link)
अणु
	वापस most_set_cfg_dbr_size(link->device, link->channel,
				     link->dbr_size);
पूर्ण

अटल पूर्णांक set_cfg_num_buffers(काष्ठा mdev_link *link)
अणु
	वापस most_set_cfg_num_buffers(link->device, link->channel,
					link->num_buffers);
पूर्ण

अटल पूर्णांक set_cfg_packets_xact(काष्ठा mdev_link *link)
अणु
	वापस most_set_cfg_packets_xact(link->device, link->channel,
					 link->packets_per_xact);
पूर्ण

अटल पूर्णांक set_cfg_direction(काष्ठा mdev_link *link)
अणु
	वापस most_set_cfg_direction(link->device, link->channel,
				      link->direction);
पूर्ण

अटल पूर्णांक set_cfg_datatype(काष्ठा mdev_link *link)
अणु
	वापस most_set_cfg_datatype(link->device, link->channel,
				     link->datatype);
पूर्ण

अटल पूर्णांक (*set_config_val[])(काष्ठा mdev_link *link) = अणु
	set_cfg_buffer_size,
	set_cfg_subbuffer_size,
	set_cfg_dbr_size,
	set_cfg_num_buffers,
	set_cfg_packets_xact,
	set_cfg_direction,
	set_cfg_datatype,
पूर्ण;

अटल काष्ठा mdev_link *to_mdev_link(काष्ठा config_item *item)
अणु
	वापस container_of(item, काष्ठा mdev_link, item);
पूर्ण

अटल पूर्णांक set_config_and_add_link(काष्ठा mdev_link *mdev_link)
अणु
	पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < ARRAY_SIZE(set_config_val); i++) अणु
		ret = set_config_val[i](mdev_link);
		अगर (ret < 0 && ret != -ENODEV) अणु
			pr_err("Config failed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस most_add_link(mdev_link->device, mdev_link->channel,
			     mdev_link->comp, mdev_link->name,
			     mdev_link->comp_params);
पूर्ण

अटल sमाप_प्रकार mdev_link_create_link_store(काष्ठा config_item *item,
					   स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा mdev_link *mdev_link = to_mdev_link(item);
	bool पंचांगp;
	पूर्णांक ret;

	ret = kstrtobool(page, &पंचांगp);
	अगर (ret)
		वापस ret;
	अगर (!पंचांगp)
		वापस count;
	ret = set_config_and_add_link(mdev_link);
	अगर (ret && ret != -ENODEV)
		वापस ret;
	list_add_tail(&mdev_link->list, &mdev_link_list);
	mdev_link->create_link = पंचांगp;
	mdev_link->destroy_link = false;

	वापस count;
पूर्ण

अटल sमाप_प्रकार mdev_link_destroy_link_store(काष्ठा config_item *item,
					    स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा mdev_link *mdev_link = to_mdev_link(item);
	bool पंचांगp;
	पूर्णांक ret;

	ret = kstrtobool(page, &पंचांगp);
	अगर (ret)
		वापस ret;
	अगर (!पंचांगp)
		वापस count;

	ret = most_हटाओ_link(mdev_link->device, mdev_link->channel,
			       mdev_link->comp);
	अगर (ret)
		वापस ret;
	अगर (!list_empty(&mdev_link_list))
		list_del(&mdev_link->list);

	mdev_link->destroy_link = पंचांगp;

	वापस count;
पूर्ण

अटल sमाप_प्रकार mdev_link_direction_show(काष्ठा config_item *item, अक्षर *page)
अणु
	वापस snम_लिखो(page, PAGE_SIZE, "%s\n", to_mdev_link(item)->direction);
पूर्ण

अटल sमाप_प्रकार mdev_link_direction_store(काष्ठा config_item *item,
					 स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा mdev_link *mdev_link = to_mdev_link(item);

	अगर (!sysfs_streq(page, "dir_rx") && !sysfs_streq(page, "rx") &&
	    !sysfs_streq(page, "dir_tx") && !sysfs_streq(page, "tx"))
		वापस -EINVAL;
	म_नकल(mdev_link->direction, page);
	strim(mdev_link->direction);
	वापस count;
पूर्ण

अटल sमाप_प्रकार mdev_link_datatype_show(काष्ठा config_item *item, अक्षर *page)
अणु
	वापस snम_लिखो(page, PAGE_SIZE, "%s\n", to_mdev_link(item)->datatype);
पूर्ण

अटल sमाप_प्रकार mdev_link_datatype_store(काष्ठा config_item *item,
					स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा mdev_link *mdev_link = to_mdev_link(item);

	अगर (!sysfs_streq(page, "control") && !sysfs_streq(page, "async") &&
	    !sysfs_streq(page, "sync") && !sysfs_streq(page, "isoc") &&
	    !sysfs_streq(page, "isoc_avp"))
		वापस -EINVAL;
	म_नकल(mdev_link->datatype, page);
	strim(mdev_link->datatype);
	वापस count;
पूर्ण

अटल sमाप_प्रकार mdev_link_device_show(काष्ठा config_item *item, अक्षर *page)
अणु
	वापस snम_लिखो(page, PAGE_SIZE, "%s\n", to_mdev_link(item)->device);
पूर्ण

अटल sमाप_प्रकार mdev_link_device_store(काष्ठा config_item *item,
				      स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा mdev_link *mdev_link = to_mdev_link(item);

	strlcpy(mdev_link->device, page, माप(mdev_link->device));
	strim(mdev_link->device);
	वापस count;
पूर्ण

अटल sमाप_प्रकार mdev_link_channel_show(काष्ठा config_item *item, अक्षर *page)
अणु
	वापस snम_लिखो(page, PAGE_SIZE, "%s\n", to_mdev_link(item)->channel);
पूर्ण

अटल sमाप_प्रकार mdev_link_channel_store(काष्ठा config_item *item,
				       स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा mdev_link *mdev_link = to_mdev_link(item);

	strlcpy(mdev_link->channel, page, माप(mdev_link->channel));
	strim(mdev_link->channel);
	वापस count;
पूर्ण

अटल sमाप_प्रकार mdev_link_comp_show(काष्ठा config_item *item, अक्षर *page)
अणु
	वापस snम_लिखो(page, PAGE_SIZE, "%s\n", to_mdev_link(item)->comp);
पूर्ण

अटल sमाप_प्रकार mdev_link_comp_store(काष्ठा config_item *item,
				    स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा mdev_link *mdev_link = to_mdev_link(item);

	strlcpy(mdev_link->comp, page, माप(mdev_link->comp));
	strim(mdev_link->comp);
	वापस count;
पूर्ण

अटल sमाप_प्रकार mdev_link_comp_params_show(काष्ठा config_item *item, अक्षर *page)
अणु
	वापस snम_लिखो(page, PAGE_SIZE, "%s\n",
			to_mdev_link(item)->comp_params);
पूर्ण

अटल sमाप_प्रकार mdev_link_comp_params_store(काष्ठा config_item *item,
					   स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा mdev_link *mdev_link = to_mdev_link(item);

	strlcpy(mdev_link->comp_params, page, माप(mdev_link->comp_params));
	strim(mdev_link->comp_params);
	वापस count;
पूर्ण

अटल sमाप_प्रकार mdev_link_num_buffers_show(काष्ठा config_item *item, अक्षर *page)
अणु
	वापस snम_लिखो(page, PAGE_SIZE, "%d\n",
			to_mdev_link(item)->num_buffers);
पूर्ण

अटल sमाप_प्रकार mdev_link_num_buffers_store(काष्ठा config_item *item,
					   स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा mdev_link *mdev_link = to_mdev_link(item);
	पूर्णांक ret;

	ret = kstrtou16(page, 0, &mdev_link->num_buffers);
	अगर (ret)
		वापस ret;
	वापस count;
पूर्ण

अटल sमाप_प्रकार mdev_link_buffer_size_show(काष्ठा config_item *item, अक्षर *page)
अणु
	वापस snम_लिखो(page, PAGE_SIZE, "%d\n",
			to_mdev_link(item)->buffer_size);
पूर्ण

अटल sमाप_प्रकार mdev_link_buffer_size_store(काष्ठा config_item *item,
					   स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा mdev_link *mdev_link = to_mdev_link(item);
	पूर्णांक ret;

	ret = kstrtou16(page, 0, &mdev_link->buffer_size);
	अगर (ret)
		वापस ret;
	वापस count;
पूर्ण

अटल sमाप_प्रकार mdev_link_subbuffer_size_show(काष्ठा config_item *item,
					     अक्षर *page)
अणु
	वापस snम_लिखो(page, PAGE_SIZE, "%d\n",
			to_mdev_link(item)->subbuffer_size);
पूर्ण

अटल sमाप_प्रकार mdev_link_subbuffer_size_store(काष्ठा config_item *item,
					      स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा mdev_link *mdev_link = to_mdev_link(item);
	पूर्णांक ret;

	ret = kstrtou16(page, 0, &mdev_link->subbuffer_size);
	अगर (ret)
		वापस ret;
	वापस count;
पूर्ण

अटल sमाप_प्रकार mdev_link_packets_per_xact_show(काष्ठा config_item *item,
					       अक्षर *page)
अणु
	वापस snम_लिखो(page, PAGE_SIZE, "%d\n",
			to_mdev_link(item)->packets_per_xact);
पूर्ण

अटल sमाप_प्रकार mdev_link_packets_per_xact_store(काष्ठा config_item *item,
						स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा mdev_link *mdev_link = to_mdev_link(item);
	पूर्णांक ret;

	ret = kstrtou16(page, 0, &mdev_link->packets_per_xact);
	अगर (ret)
		वापस ret;
	वापस count;
पूर्ण

अटल sमाप_प्रकार mdev_link_dbr_size_show(काष्ठा config_item *item, अक्षर *page)
अणु
	वापस snम_लिखो(page, PAGE_SIZE, "%d\n", to_mdev_link(item)->dbr_size);
पूर्ण

अटल sमाप_प्रकार mdev_link_dbr_size_store(काष्ठा config_item *item,
					स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा mdev_link *mdev_link = to_mdev_link(item);
	पूर्णांक ret;

	ret = kstrtou16(page, 0, &mdev_link->dbr_size);
	अगर (ret)
		वापस ret;
	वापस count;
पूर्ण

CONFIGFS_ATTR_WO(mdev_link_, create_link);
CONFIGFS_ATTR_WO(mdev_link_, destroy_link);
CONFIGFS_ATTR(mdev_link_, device);
CONFIGFS_ATTR(mdev_link_, channel);
CONFIGFS_ATTR(mdev_link_, comp);
CONFIGFS_ATTR(mdev_link_, comp_params);
CONFIGFS_ATTR(mdev_link_, num_buffers);
CONFIGFS_ATTR(mdev_link_, buffer_size);
CONFIGFS_ATTR(mdev_link_, subbuffer_size);
CONFIGFS_ATTR(mdev_link_, packets_per_xact);
CONFIGFS_ATTR(mdev_link_, datatype);
CONFIGFS_ATTR(mdev_link_, direction);
CONFIGFS_ATTR(mdev_link_, dbr_size);

अटल काष्ठा configfs_attribute *mdev_link_attrs[] = अणु
	&mdev_link_attr_create_link,
	&mdev_link_attr_destroy_link,
	&mdev_link_attr_device,
	&mdev_link_attr_channel,
	&mdev_link_attr_comp,
	&mdev_link_attr_comp_params,
	&mdev_link_attr_num_buffers,
	&mdev_link_attr_buffer_size,
	&mdev_link_attr_subbuffer_size,
	&mdev_link_attr_packets_per_xact,
	&mdev_link_attr_datatype,
	&mdev_link_attr_direction,
	&mdev_link_attr_dbr_size,
	शून्य,
पूर्ण;

अटल व्योम mdev_link_release(काष्ठा config_item *item)
अणु
	काष्ठा mdev_link *mdev_link = to_mdev_link(item);
	पूर्णांक ret;

	अगर (mdev_link->destroy_link)
		जाओ मुक्त_item;

	ret = most_हटाओ_link(mdev_link->device, mdev_link->channel,
			       mdev_link->comp);
	अगर (ret) अणु
		pr_err("Removing link failed.\n");
		जाओ मुक्त_item;
	पूर्ण

	अगर (!list_empty(&mdev_link_list))
		list_del(&mdev_link->list);

मुक्त_item:
	kमुक्त(to_mdev_link(item));
पूर्ण

अटल काष्ठा configfs_item_operations mdev_link_item_ops = अणु
	.release		= mdev_link_release,
पूर्ण;

अटल स्थिर काष्ठा config_item_type mdev_link_type = अणु
	.ct_item_ops	= &mdev_link_item_ops,
	.ct_attrs	= mdev_link_attrs,
	.ct_owner	= THIS_MODULE,
पूर्ण;

काष्ठा most_common अणु
	काष्ठा config_group group;
	काष्ठा module *mod;
	काष्ठा configfs_subप्रणाली subsys;
पूर्ण;

अटल काष्ठा most_common *to_most_common(काष्ठा configfs_subप्रणाली *subsys)
अणु
	वापस container_of(subsys, काष्ठा most_common, subsys);
पूर्ण

अटल काष्ठा config_item *most_common_make_item(काष्ठा config_group *group,
						 स्थिर अक्षर *name)
अणु
	काष्ठा mdev_link *mdev_link;
	काष्ठा most_common *mc = to_most_common(group->cg_subsys);

	mdev_link = kzalloc(माप(*mdev_link), GFP_KERNEL);
	अगर (!mdev_link)
		वापस ERR_PTR(-ENOMEM);

	अगर (!try_module_get(mc->mod)) अणु
		kमुक्त(mdev_link);
		वापस ERR_PTR(-ENOLCK);
	पूर्ण
	config_item_init_type_name(&mdev_link->item, name,
				   &mdev_link_type);

	अगर (!म_भेद(group->cg_item.ci_namebuf, "most_cdev"))
		म_नकल(mdev_link->comp, "cdev");
	अन्यथा अगर (!म_भेद(group->cg_item.ci_namebuf, "most_net"))
		म_नकल(mdev_link->comp, "net");
	अन्यथा अगर (!म_भेद(group->cg_item.ci_namebuf, "most_video"))
		म_नकल(mdev_link->comp, "video");
	म_नकल(mdev_link->name, name);
	वापस &mdev_link->item;
पूर्ण

अटल व्योम most_common_release(काष्ठा config_item *item)
अणु
	काष्ठा config_group *group = to_config_group(item);

	kमुक्त(to_most_common(group->cg_subsys));
पूर्ण

अटल काष्ठा configfs_item_operations most_common_item_ops = अणु
	.release	= most_common_release,
पूर्ण;

अटल व्योम most_common_disconnect(काष्ठा config_group *group,
				   काष्ठा config_item *item)
अणु
	काष्ठा most_common *mc = to_most_common(group->cg_subsys);

	module_put(mc->mod);
पूर्ण

अटल काष्ठा configfs_group_operations most_common_group_ops = अणु
	.make_item	= most_common_make_item,
	.disconnect_notअगरy = most_common_disconnect,
पूर्ण;

अटल स्थिर काष्ठा config_item_type most_common_type = अणु
	.ct_item_ops	= &most_common_item_ops,
	.ct_group_ops	= &most_common_group_ops,
	.ct_owner	= THIS_MODULE,
पूर्ण;

अटल काष्ठा most_common most_cdev = अणु
	.subsys = अणु
		.su_group = अणु
			.cg_item = अणु
				.ci_namebuf = "most_cdev",
				.ci_type = &most_common_type,
			पूर्ण,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा most_common most_net = अणु
	.subsys = अणु
		.su_group = अणु
			.cg_item = अणु
				.ci_namebuf = "most_net",
				.ci_type = &most_common_type,
			पूर्ण,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा most_common most_video = अणु
	.subsys = अणु
		.su_group = अणु
			.cg_item = अणु
				.ci_namebuf = "most_video",
				.ci_type = &most_common_type,
			पूर्ण,
		पूर्ण,
	पूर्ण,
पूर्ण;

काष्ठा most_snd_grp अणु
	काष्ठा config_group group;
	bool create_card;
	काष्ठा list_head list;
पूर्ण;

अटल काष्ठा most_snd_grp *to_most_snd_grp(काष्ठा config_item *item)
अणु
	वापस container_of(to_config_group(item), काष्ठा most_snd_grp, group);
पूर्ण

अटल काष्ठा config_item *most_snd_grp_make_item(काष्ठा config_group *group,
						  स्थिर अक्षर *name)
अणु
	काष्ठा mdev_link *mdev_link;

	mdev_link = kzalloc(माप(*mdev_link), GFP_KERNEL);
	अगर (!mdev_link)
		वापस ERR_PTR(-ENOMEM);

	config_item_init_type_name(&mdev_link->item, name, &mdev_link_type);
	mdev_link->create_link = false;
	म_नकल(mdev_link->name, name);
	म_नकल(mdev_link->comp, "sound");
	वापस &mdev_link->item;
पूर्ण

अटल sमाप_प्रकार most_snd_grp_create_card_store(काष्ठा config_item *item,
					      स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा most_snd_grp *snd_grp = to_most_snd_grp(item);
	पूर्णांक ret;
	bool पंचांगp;

	ret = kstrtobool(page, &पंचांगp);
	अगर (ret)
		वापस ret;
	अगर (पंचांगp) अणु
		ret = most_cfg_complete("sound");
		अगर (ret)
			वापस ret;
	पूर्ण
	snd_grp->create_card = पंचांगp;
	वापस count;
पूर्ण

CONFIGFS_ATTR_WO(most_snd_grp_, create_card);

अटल काष्ठा configfs_attribute *most_snd_grp_attrs[] = अणु
	&most_snd_grp_attr_create_card,
	शून्य,
पूर्ण;

अटल व्योम most_snd_grp_release(काष्ठा config_item *item)
अणु
	काष्ठा most_snd_grp *group = to_most_snd_grp(item);

	list_del(&group->list);
	kमुक्त(group);
पूर्ण

अटल काष्ठा configfs_item_operations most_snd_grp_item_ops = अणु
	.release	= most_snd_grp_release,
पूर्ण;

अटल काष्ठा configfs_group_operations most_snd_grp_group_ops = अणु
	.make_item	= most_snd_grp_make_item,
पूर्ण;

अटल स्थिर काष्ठा config_item_type most_snd_grp_type = अणु
	.ct_item_ops	= &most_snd_grp_item_ops,
	.ct_group_ops	= &most_snd_grp_group_ops,
	.ct_attrs	= most_snd_grp_attrs,
	.ct_owner	= THIS_MODULE,
पूर्ण;

काष्ठा most_sound अणु
	काष्ठा configfs_subप्रणाली subsys;
	काष्ठा list_head soundcard_list;
	काष्ठा module *mod;
पूर्ण;

अटल काष्ठा config_group *most_sound_make_group(काष्ठा config_group *group,
						  स्थिर अक्षर *name)
अणु
	काष्ठा most_snd_grp *most;
	काष्ठा most_sound *ms = container_of(group->cg_subsys,
					     काष्ठा most_sound, subsys);

	list_क्रम_each_entry(most, &ms->soundcard_list, list) अणु
		अगर (!most->create_card) अणु
			pr_info("adapter configuration still in progress.\n");
			वापस ERR_PTR(-EPROTO);
		पूर्ण
	पूर्ण
	अगर (!try_module_get(ms->mod))
		वापस ERR_PTR(-ENOLCK);
	most = kzalloc(माप(*most), GFP_KERNEL);
	अगर (!most) अणु
		module_put(ms->mod);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	config_group_init_type_name(&most->group, name, &most_snd_grp_type);
	list_add_tail(&most->list, &ms->soundcard_list);
	वापस &most->group;
पूर्ण

अटल व्योम most_sound_disconnect(काष्ठा config_group *group,
				  काष्ठा config_item *item)
अणु
	काष्ठा most_sound *ms = container_of(group->cg_subsys,
					     काष्ठा most_sound, subsys);
	module_put(ms->mod);
पूर्ण

अटल काष्ठा configfs_group_operations most_sound_group_ops = अणु
	.make_group	= most_sound_make_group,
	.disconnect_notअगरy = most_sound_disconnect,
पूर्ण;

अटल स्थिर काष्ठा config_item_type most_sound_type = अणु
	.ct_group_ops	= &most_sound_group_ops,
	.ct_owner	= THIS_MODULE,
पूर्ण;

अटल काष्ठा most_sound most_sound_subsys = अणु
	.subsys = अणु
		.su_group = अणु
			.cg_item = अणु
				.ci_namebuf = "most_sound",
				.ci_type = &most_sound_type,
			पूर्ण,
		पूर्ण,
	पूर्ण,
पूर्ण;

पूर्णांक most_रेजिस्टर_configfs_subsys(काष्ठा most_component *c)
अणु
	पूर्णांक ret;

	अगर (!म_भेद(c->name, "cdev")) अणु
		most_cdev.mod = c->mod;
		ret = configfs_रेजिस्टर_subप्रणाली(&most_cdev.subsys);
	पूर्ण अन्यथा अगर (!म_भेद(c->name, "net")) अणु
		most_net.mod = c->mod;
		ret = configfs_रेजिस्टर_subप्रणाली(&most_net.subsys);
	पूर्ण अन्यथा अगर (!म_भेद(c->name, "video")) अणु
		most_video.mod = c->mod;
		ret = configfs_रेजिस्टर_subप्रणाली(&most_video.subsys);
	पूर्ण अन्यथा अगर (!म_भेद(c->name, "sound")) अणु
		most_sound_subsys.mod = c->mod;
		ret = configfs_रेजिस्टर_subप्रणाली(&most_sound_subsys.subsys);
	पूर्ण अन्यथा अणु
		वापस -ENODEV;
	पूर्ण

	अगर (ret) अणु
		pr_err("Error %d while registering subsystem %s\n",
		       ret, c->name);
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(most_रेजिस्टर_configfs_subsys);

व्योम most_पूर्णांकerface_रेजिस्टर_notअगरy(स्थिर अक्षर *mdev)
अणु
	bool रेजिस्टर_snd_card = false;
	काष्ठा mdev_link *mdev_link;

	list_क्रम_each_entry(mdev_link, &mdev_link_list, list) अणु
		अगर (!म_भेद(mdev_link->device, mdev)) अणु
			set_config_and_add_link(mdev_link);
			अगर (!म_भेद(mdev_link->comp, "sound"))
				रेजिस्टर_snd_card = true;
		पूर्ण
	पूर्ण
	अगर (रेजिस्टर_snd_card)
		most_cfg_complete("sound");
पूर्ण

व्योम most_deरेजिस्टर_configfs_subsys(काष्ठा most_component *c)
अणु
	अगर (!म_भेद(c->name, "cdev"))
		configfs_unरेजिस्टर_subप्रणाली(&most_cdev.subsys);
	अन्यथा अगर (!म_भेद(c->name, "net"))
		configfs_unरेजिस्टर_subप्रणाली(&most_net.subsys);
	अन्यथा अगर (!म_भेद(c->name, "video"))
		configfs_unरेजिस्टर_subप्रणाली(&most_video.subsys);
	अन्यथा अगर (!म_भेद(c->name, "sound"))
		configfs_unरेजिस्टर_subप्रणाली(&most_sound_subsys.subsys);
पूर्ण
EXPORT_SYMBOL_GPL(most_deरेजिस्टर_configfs_subsys);

पूर्णांक __init configfs_init(व्योम)
अणु
	config_group_init(&most_cdev.subsys.su_group);
	mutex_init(&most_cdev.subsys.su_mutex);

	config_group_init(&most_net.subsys.su_group);
	mutex_init(&most_net.subsys.su_mutex);

	config_group_init(&most_video.subsys.su_group);
	mutex_init(&most_video.subsys.su_mutex);

	config_group_init(&most_sound_subsys.subsys.su_group);
	mutex_init(&most_sound_subsys.subsys.su_mutex);

	INIT_LIST_HEAD(&most_sound_subsys.soundcard_list);
	INIT_LIST_HEAD(&mdev_link_list);

	वापस 0;
पूर्ण
