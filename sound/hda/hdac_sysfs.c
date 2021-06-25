<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * sysfs support क्रम HD-audio core device
 */

#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/device.h>
#समावेश <sound/core.h>
#समावेश <sound/hdaudपन.स>
#समावेश "local.h"

काष्ठा hdac_widget_tree अणु
	काष्ठा kobject *root;
	काष्ठा kobject *afg;
	काष्ठा kobject **nodes;
पूर्ण;

#घोषणा CODEC_ATTR(type)					\
अटल sमाप_प्रकार type##_show(काष्ठा device *dev,			\
			   काष्ठा device_attribute *attr,	\
			   अक्षर *buf)				\
अणु								\
	काष्ठा hdac_device *codec = dev_to_hdac_dev(dev);	\
	वापस प्र_लिखो(buf, "0x%x\n", codec->type);		\
पूर्ण \
अटल DEVICE_ATTR_RO(type)

#घोषणा CODEC_ATTR_STR(type)					\
अटल sमाप_प्रकार type##_show(काष्ठा device *dev,			\
			     काष्ठा device_attribute *attr,	\
					अक्षर *buf)		\
अणु								\
	काष्ठा hdac_device *codec = dev_to_hdac_dev(dev);	\
	वापस प्र_लिखो(buf, "%s\n",				\
		       codec->type ? codec->type : "");		\
पूर्ण \
अटल DEVICE_ATTR_RO(type)

CODEC_ATTR(type);
CODEC_ATTR(venकरोr_id);
CODEC_ATTR(subप्रणाली_id);
CODEC_ATTR(revision_id);
CODEC_ATTR(afg);
CODEC_ATTR(mfg);
CODEC_ATTR_STR(venकरोr_name);
CODEC_ATTR_STR(chip_name);

अटल sमाप_प्रकार modalias_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	वापस snd_hdac_codec_modalias(dev_to_hdac_dev(dev), buf, 256);
पूर्ण
अटल DEVICE_ATTR_RO(modalias);

अटल काष्ठा attribute *hdac_dev_attrs[] = अणु
	&dev_attr_type.attr,
	&dev_attr_venकरोr_id.attr,
	&dev_attr_subप्रणाली_id.attr,
	&dev_attr_revision_id.attr,
	&dev_attr_afg.attr,
	&dev_attr_mfg.attr,
	&dev_attr_venकरोr_name.attr,
	&dev_attr_chip_name.attr,
	&dev_attr_modalias.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group hdac_dev_attr_group = अणु
	.attrs	= hdac_dev_attrs,
पूर्ण;

स्थिर काष्ठा attribute_group *hdac_dev_attr_groups[] = अणु
	&hdac_dev_attr_group,
	शून्य
पूर्ण;

/*
 * Widget tree sysfs
 *
 * This is a tree showing the attributes of each widget.  It appears like
 * /sys/bus/hdaudioC0D0/widमाला_लो/04/caps
 */

काष्ठा widget_attribute;

काष्ठा widget_attribute अणु
	काष्ठा attribute	attr;
	sमाप_प्रकार (*show)(काष्ठा hdac_device *codec, hda_nid_t nid,
			काष्ठा widget_attribute *attr, अक्षर *buf);
	sमाप_प्रकार (*store)(काष्ठा hdac_device *codec, hda_nid_t nid,
			 काष्ठा widget_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count);
पूर्ण;

अटल पूर्णांक get_codec_nid(काष्ठा kobject *kobj, काष्ठा hdac_device **codecp)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj->parent->parent);
	पूर्णांक nid;
	sमाप_प्रकार ret;

	ret = kstrtoपूर्णांक(kobj->name, 16, &nid);
	अगर (ret < 0)
		वापस ret;
	*codecp = dev_to_hdac_dev(dev);
	वापस nid;
पूर्ण

अटल sमाप_प्रकार widget_attr_show(काष्ठा kobject *kobj, काष्ठा attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा widget_attribute *wid_attr =
		container_of(attr, काष्ठा widget_attribute, attr);
	काष्ठा hdac_device *codec;
	पूर्णांक nid;

	अगर (!wid_attr->show)
		वापस -EIO;
	nid = get_codec_nid(kobj, &codec);
	अगर (nid < 0)
		वापस nid;
	वापस wid_attr->show(codec, nid, wid_attr, buf);
पूर्ण

अटल sमाप_प्रकार widget_attr_store(काष्ठा kobject *kobj, काष्ठा attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा widget_attribute *wid_attr =
		container_of(attr, काष्ठा widget_attribute, attr);
	काष्ठा hdac_device *codec;
	पूर्णांक nid;

	अगर (!wid_attr->store)
		वापस -EIO;
	nid = get_codec_nid(kobj, &codec);
	अगर (nid < 0)
		वापस nid;
	वापस wid_attr->store(codec, nid, wid_attr, buf, count);
पूर्ण

अटल स्थिर काष्ठा sysfs_ops widget_sysfs_ops = अणु
	.show	= widget_attr_show,
	.store	= widget_attr_store,
पूर्ण;

अटल व्योम widget_release(काष्ठा kobject *kobj)
अणु
	kमुक्त(kobj);
पूर्ण

अटल काष्ठा kobj_type widget_ktype = अणु
	.release	= widget_release,
	.sysfs_ops	= &widget_sysfs_ops,
पूर्ण;

#घोषणा WIDGET_ATTR_RO(_name) \
	काष्ठा widget_attribute wid_attr_##_name = __ATTR_RO(_name)
#घोषणा WIDGET_ATTR_RW(_name) \
	काष्ठा widget_attribute wid_attr_##_name = __ATTR_RW(_name)

अटल sमाप_प्रकार caps_show(काष्ठा hdac_device *codec, hda_nid_t nid,
			काष्ठा widget_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "0x%08x\n", get_wcaps(codec, nid));
पूर्ण

अटल sमाप_प्रकार pin_caps_show(काष्ठा hdac_device *codec, hda_nid_t nid,
			     काष्ठा widget_attribute *attr, अक्षर *buf)
अणु
	अगर (get_wcaps_type(get_wcaps(codec, nid)) != AC_WID_PIN)
		वापस 0;
	वापस प्र_लिखो(buf, "0x%08x\n",
		       snd_hdac_पढ़ो_parm(codec, nid, AC_PAR_PIN_CAP));
पूर्ण

अटल sमाप_प्रकार pin_cfg_show(काष्ठा hdac_device *codec, hda_nid_t nid,
			    काष्ठा widget_attribute *attr, अक्षर *buf)
अणु
	अचिन्हित पूर्णांक val;

	अगर (get_wcaps_type(get_wcaps(codec, nid)) != AC_WID_PIN)
		वापस 0;
	अगर (snd_hdac_पढ़ो(codec, nid, AC_VERB_GET_CONFIG_DEFAULT, 0, &val))
		वापस 0;
	वापस प्र_लिखो(buf, "0x%08x\n", val);
पूर्ण

अटल bool has_pcm_cap(काष्ठा hdac_device *codec, hda_nid_t nid)
अणु
	अगर (nid == codec->afg || nid == codec->mfg)
		वापस true;
	चयन (get_wcaps_type(get_wcaps(codec, nid))) अणु
	हाल AC_WID_AUD_OUT:
	हाल AC_WID_AUD_IN:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल sमाप_प्रकार pcm_caps_show(काष्ठा hdac_device *codec, hda_nid_t nid,
			     काष्ठा widget_attribute *attr, अक्षर *buf)
अणु
	अगर (!has_pcm_cap(codec, nid))
		वापस 0;
	वापस प्र_लिखो(buf, "0x%08x\n",
		       snd_hdac_पढ़ो_parm(codec, nid, AC_PAR_PCM));
पूर्ण

अटल sमाप_प्रकार pcm_क्रमmats_show(काष्ठा hdac_device *codec, hda_nid_t nid,
				काष्ठा widget_attribute *attr, अक्षर *buf)
अणु
	अगर (!has_pcm_cap(codec, nid))
		वापस 0;
	वापस प्र_लिखो(buf, "0x%08x\n",
		       snd_hdac_पढ़ो_parm(codec, nid, AC_PAR_STREAM));
पूर्ण

अटल sमाप_प्रकार amp_in_caps_show(काष्ठा hdac_device *codec, hda_nid_t nid,
				काष्ठा widget_attribute *attr, अक्षर *buf)
अणु
	अगर (nid != codec->afg && !(get_wcaps(codec, nid) & AC_WCAP_IN_AMP))
		वापस 0;
	वापस प्र_लिखो(buf, "0x%08x\n",
		       snd_hdac_पढ़ो_parm(codec, nid, AC_PAR_AMP_IN_CAP));
पूर्ण

अटल sमाप_प्रकार amp_out_caps_show(काष्ठा hdac_device *codec, hda_nid_t nid,
				 काष्ठा widget_attribute *attr, अक्षर *buf)
अणु
	अगर (nid != codec->afg && !(get_wcaps(codec, nid) & AC_WCAP_OUT_AMP))
		वापस 0;
	वापस प्र_लिखो(buf, "0x%08x\n",
		       snd_hdac_पढ़ो_parm(codec, nid, AC_PAR_AMP_OUT_CAP));
पूर्ण

अटल sमाप_प्रकार घातer_caps_show(काष्ठा hdac_device *codec, hda_nid_t nid,
			       काष्ठा widget_attribute *attr, अक्षर *buf)
अणु
	अगर (nid != codec->afg && !(get_wcaps(codec, nid) & AC_WCAP_POWER))
		वापस 0;
	वापस प्र_लिखो(buf, "0x%08x\n",
		       snd_hdac_पढ़ो_parm(codec, nid, AC_PAR_POWER_STATE));
पूर्ण

अटल sमाप_प्रकार gpio_caps_show(काष्ठा hdac_device *codec, hda_nid_t nid,
			      काष्ठा widget_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "0x%08x\n",
		       snd_hdac_पढ़ो_parm(codec, nid, AC_PAR_GPIO_CAP));
पूर्ण

अटल sमाप_प्रकार connections_show(काष्ठा hdac_device *codec, hda_nid_t nid,
				काष्ठा widget_attribute *attr, अक्षर *buf)
अणु
	hda_nid_t list[32];
	पूर्णांक i, nconns;
	sमाप_प्रकार ret = 0;

	nconns = snd_hdac_get_connections(codec, nid, list, ARRAY_SIZE(list));
	अगर (nconns <= 0)
		वापस nconns;
	क्रम (i = 0; i < nconns; i++)
		ret += प्र_लिखो(buf + ret, "%s0x%02x", i ? " " : "", list[i]);
	ret += प्र_लिखो(buf + ret, "\n");
	वापस ret;
पूर्ण

अटल WIDGET_ATTR_RO(caps);
अटल WIDGET_ATTR_RO(pin_caps);
अटल WIDGET_ATTR_RO(pin_cfg);
अटल WIDGET_ATTR_RO(pcm_caps);
अटल WIDGET_ATTR_RO(pcm_क्रमmats);
अटल WIDGET_ATTR_RO(amp_in_caps);
अटल WIDGET_ATTR_RO(amp_out_caps);
अटल WIDGET_ATTR_RO(घातer_caps);
अटल WIDGET_ATTR_RO(gpio_caps);
अटल WIDGET_ATTR_RO(connections);

अटल काष्ठा attribute *widget_node_attrs[] = अणु
	&wid_attr_caps.attr,
	&wid_attr_pin_caps.attr,
	&wid_attr_pin_cfg.attr,
	&wid_attr_pcm_caps.attr,
	&wid_attr_pcm_क्रमmats.attr,
	&wid_attr_amp_in_caps.attr,
	&wid_attr_amp_out_caps.attr,
	&wid_attr_घातer_caps.attr,
	&wid_attr_connections.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute *widget_afg_attrs[] = अणु
	&wid_attr_pcm_caps.attr,
	&wid_attr_pcm_क्रमmats.attr,
	&wid_attr_amp_in_caps.attr,
	&wid_attr_amp_out_caps.attr,
	&wid_attr_घातer_caps.attr,
	&wid_attr_gpio_caps.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group widget_node_group = अणु
	.attrs = widget_node_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group widget_afg_group = अणु
	.attrs = widget_afg_attrs,
पूर्ण;

अटल व्योम मुक्त_widget_node(काष्ठा kobject *kobj,
			     स्थिर काष्ठा attribute_group *group)
अणु
	अगर (kobj) अणु
		sysfs_हटाओ_group(kobj, group);
		kobject_put(kobj);
	पूर्ण
पूर्ण

अटल व्योम widget_tree_मुक्त(काष्ठा hdac_device *codec)
अणु
	काष्ठा hdac_widget_tree *tree = codec->widमाला_लो;
	काष्ठा kobject **p;

	अगर (!tree)
		वापस;
	मुक्त_widget_node(tree->afg, &widget_afg_group);
	अगर (tree->nodes) अणु
		क्रम (p = tree->nodes; *p; p++)
			मुक्त_widget_node(*p, &widget_node_group);
		kमुक्त(tree->nodes);
	पूर्ण
	kobject_put(tree->root);
	kमुक्त(tree);
	codec->widमाला_लो = शून्य;
पूर्ण

अटल पूर्णांक add_widget_node(काष्ठा kobject *parent, hda_nid_t nid,
			   स्थिर काष्ठा attribute_group *group,
			   काष्ठा kobject **res)
अणु
	काष्ठा kobject *kobj = kzalloc(माप(*kobj), GFP_KERNEL);
	पूर्णांक err;

	अगर (!kobj)
		वापस -ENOMEM;
	kobject_init(kobj, &widget_ktype);
	err = kobject_add(kobj, parent, "%02x", nid);
	अगर (err < 0)
		वापस err;
	err = sysfs_create_group(kobj, group);
	अगर (err < 0) अणु
		kobject_put(kobj);
		वापस err;
	पूर्ण

	*res = kobj;
	वापस 0;
पूर्ण

अटल पूर्णांक widget_tree_create(काष्ठा hdac_device *codec)
अणु
	काष्ठा hdac_widget_tree *tree;
	पूर्णांक i, err;
	hda_nid_t nid;

	tree = codec->widमाला_लो = kzalloc(माप(*tree), GFP_KERNEL);
	अगर (!tree)
		वापस -ENOMEM;

	tree->root = kobject_create_and_add("widgets", &codec->dev.kobj);
	अगर (!tree->root)
		वापस -ENOMEM;

	tree->nodes = kसुस्मृति(codec->num_nodes + 1, माप(*tree->nodes),
			      GFP_KERNEL);
	अगर (!tree->nodes)
		वापस -ENOMEM;

	क्रम (i = 0, nid = codec->start_nid; i < codec->num_nodes; i++, nid++) अणु
		err = add_widget_node(tree->root, nid, &widget_node_group,
				      &tree->nodes[i]);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (codec->afg) अणु
		err = add_widget_node(tree->root, codec->afg,
				      &widget_afg_group, &tree->afg);
		अगर (err < 0)
			वापस err;
	पूर्ण

	kobject_uevent(tree->root, KOBJ_CHANGE);
	वापस 0;
पूर्ण

/* call with codec->widget_lock held */
पूर्णांक hda_widget_sysfs_init(काष्ठा hdac_device *codec)
अणु
	पूर्णांक err;

	अगर (codec->widमाला_लो)
		वापस 0; /* alपढ़ोy created */

	err = widget_tree_create(codec);
	अगर (err < 0) अणु
		widget_tree_मुक्त(codec);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/* call with codec->widget_lock held */
व्योम hda_widget_sysfs_निकास(काष्ठा hdac_device *codec)
अणु
	widget_tree_मुक्त(codec);
पूर्ण

/* call with codec->widget_lock held */
पूर्णांक hda_widget_sysfs_reinit(काष्ठा hdac_device *codec,
			    hda_nid_t start_nid, पूर्णांक num_nodes)
अणु
	काष्ठा hdac_widget_tree *tree;
	hda_nid_t end_nid = start_nid + num_nodes;
	hda_nid_t nid;
	पूर्णांक i;

	अगर (!codec->widमाला_लो)
		वापस 0;

	tree = kmemdup(codec->widमाला_लो, माप(*tree), GFP_KERNEL);
	अगर (!tree)
		वापस -ENOMEM;

	tree->nodes = kसुस्मृति(num_nodes + 1, माप(*tree->nodes), GFP_KERNEL);
	अगर (!tree->nodes) अणु
		kमुक्त(tree);
		वापस -ENOMEM;
	पूर्ण

	/* prune non-existing nodes */
	क्रम (i = 0, nid = codec->start_nid; i < codec->num_nodes; i++, nid++) अणु
		अगर (nid < start_nid || nid >= end_nid)
			मुक्त_widget_node(codec->widमाला_लो->nodes[i],
					 &widget_node_group);
	पूर्ण

	/* add new nodes */
	क्रम (i = 0, nid = start_nid; i < num_nodes; i++, nid++) अणु
		अगर (nid < codec->start_nid || nid >= codec->end_nid)
			add_widget_node(tree->root, nid, &widget_node_group,
					&tree->nodes[i]);
		अन्यथा
			tree->nodes[i] =
				codec->widमाला_लो->nodes[nid - codec->start_nid];
	पूर्ण

	/* replace with the new tree */
	kमुक्त(codec->widमाला_लो->nodes);
	kमुक्त(codec->widमाला_लो);
	codec->widमाला_लो = tree;

	kobject_uevent(tree->root, KOBJ_CHANGE);
	वापस 0;
पूर्ण
