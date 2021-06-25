<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * core.c - Implementation of core module of MOST Linux driver stack
 *
 * Copyright (C) 2013-2020 Microchip Technology Germany II GmbH & Co. KG
 */

#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/list.h>
#समावेश <linux/poll.h>
#समावेश <linux/रुको.h>
#समावेश <linux/kobject.h>
#समावेश <linux/mutex.h>
#समावेश <linux/completion.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/idr.h>
#समावेश <linux/most.h>

#घोषणा MAX_CHANNELS	64
#घोषणा STRING_SIZE	80

अटल काष्ठा ida mdev_id;
अटल पूर्णांक dummy_num_buffers;
अटल काष्ठा list_head comp_list;

काष्ठा pipe अणु
	काष्ठा most_component *comp;
	पूर्णांक refs;
	पूर्णांक num_buffers;
पूर्ण;

काष्ठा most_channel अणु
	काष्ठा device dev;
	काष्ठा completion cleanup;
	atomic_t mbo_ref;
	atomic_t mbo_nq_level;
	u16 channel_id;
	अक्षर name[STRING_SIZE];
	bool is_poisoned;
	काष्ठा mutex start_mutex; /* channel activation synchronization */
	काष्ठा mutex nq_mutex; /* nq thपढ़ो synchronization */
	पूर्णांक is_starving;
	काष्ठा most_पूर्णांकerface *अगरace;
	काष्ठा most_channel_config cfg;
	bool keep_mbo;
	bool enqueue_halt;
	काष्ठा list_head fअगरo;
	spinlock_t fअगरo_lock; /* fअगरo access synchronization */
	काष्ठा list_head halt_fअगरo;
	काष्ठा list_head list;
	काष्ठा pipe pipe0;
	काष्ठा pipe pipe1;
	काष्ठा list_head trash_fअगरo;
	काष्ठा task_काष्ठा *hdm_enqueue_task;
	रुको_queue_head_t hdm_fअगरo_wq;

पूर्ण;

#घोषणा to_channel(d) container_of(d, काष्ठा most_channel, dev)

काष्ठा पूर्णांकerface_निजी अणु
	पूर्णांक dev_id;
	अक्षर name[STRING_SIZE];
	काष्ठा most_channel *channel[MAX_CHANNELS];
	काष्ठा list_head channel_list;
पूर्ण;

अटल स्थिर काष्ठा अणु
	पूर्णांक most_ch_data_type;
	स्थिर अक्षर *name;
पूर्ण ch_data_type[] = अणु
	अणु MOST_CH_CONTROL, "control" पूर्ण,
	अणु MOST_CH_ASYNC, "async" पूर्ण,
	अणु MOST_CH_SYNC, "sync" पूर्ण,
	अणु MOST_CH_ISOC, "isoc"पूर्ण,
	अणु MOST_CH_ISOC, "isoc_avp"पूर्ण,
पूर्ण;

/**
 * list_pop_mbo - retrieves the first MBO of the list and हटाओs it
 * @ptr: the list head to grab the MBO from.
 */
#घोषणा list_pop_mbo(ptr)						\
(अणु									\
	काष्ठा mbo *_mbo = list_first_entry(ptr, काष्ठा mbo, list);	\
	list_del(&_mbo->list);						\
	_mbo;								\
पूर्ण)

/**
 * most_मुक्त_mbo_coherent - मुक्त an MBO and its coherent buffer
 * @mbo: most buffer
 */
अटल व्योम most_मुक्त_mbo_coherent(काष्ठा mbo *mbo)
अणु
	काष्ठा most_channel *c = mbo->context;
	u16 स्थिर coherent_buf_size = c->cfg.buffer_size + c->cfg.extra_len;

	अगर (c->अगरace->dma_मुक्त)
		c->अगरace->dma_मुक्त(mbo, coherent_buf_size);
	अन्यथा
		kमुक्त(mbo->virt_address);
	kमुक्त(mbo);
	अगर (atomic_sub_and_test(1, &c->mbo_ref))
		complete(&c->cleanup);
पूर्ण

/**
 * flush_channel_fअगरos - clear the channel fअगरos
 * @c: poपूर्णांकer to channel object
 */
अटल व्योम flush_channel_fअगरos(काष्ठा most_channel *c)
अणु
	अचिन्हित दीर्घ flags, hf_flags;
	काष्ठा mbo *mbo, *पंचांगp;

	अगर (list_empty(&c->fअगरo) && list_empty(&c->halt_fअगरo))
		वापस;

	spin_lock_irqsave(&c->fअगरo_lock, flags);
	list_क्रम_each_entry_safe(mbo, पंचांगp, &c->fअगरo, list) अणु
		list_del(&mbo->list);
		spin_unlock_irqrestore(&c->fअगरo_lock, flags);
		most_मुक्त_mbo_coherent(mbo);
		spin_lock_irqsave(&c->fअगरo_lock, flags);
	पूर्ण
	spin_unlock_irqrestore(&c->fअगरo_lock, flags);

	spin_lock_irqsave(&c->fअगरo_lock, hf_flags);
	list_क्रम_each_entry_safe(mbo, पंचांगp, &c->halt_fअगरo, list) अणु
		list_del(&mbo->list);
		spin_unlock_irqrestore(&c->fअगरo_lock, hf_flags);
		most_मुक्त_mbo_coherent(mbo);
		spin_lock_irqsave(&c->fअगरo_lock, hf_flags);
	पूर्ण
	spin_unlock_irqrestore(&c->fअगरo_lock, hf_flags);

	अगर (unlikely((!list_empty(&c->fअगरo) || !list_empty(&c->halt_fअगरo))))
		dev_warn(&c->dev, "Channel or trash fifo not empty\n");
पूर्ण

/**
 * flush_trash_fअगरo - clear the trash fअगरo
 * @c: poपूर्णांकer to channel object
 */
अटल पूर्णांक flush_trash_fअगरo(काष्ठा most_channel *c)
अणु
	काष्ठा mbo *mbo, *पंचांगp;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&c->fअगरo_lock, flags);
	list_क्रम_each_entry_safe(mbo, पंचांगp, &c->trash_fअगरo, list) अणु
		list_del(&mbo->list);
		spin_unlock_irqrestore(&c->fअगरo_lock, flags);
		most_मुक्त_mbo_coherent(mbo);
		spin_lock_irqsave(&c->fअगरo_lock, flags);
	पूर्ण
	spin_unlock_irqrestore(&c->fअगरo_lock, flags);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार available_directions_show(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	काष्ठा most_channel *c = to_channel(dev);
	अचिन्हित पूर्णांक i = c->channel_id;

	म_नकल(buf, "");
	अगर (c->अगरace->channel_vector[i].direction & MOST_CH_RX)
		म_जोड़ो(buf, "rx ");
	अगर (c->अगरace->channel_vector[i].direction & MOST_CH_TX)
		म_जोड़ो(buf, "tx ");
	म_जोड़ो(buf, "\n");
	वापस म_माप(buf);
पूर्ण

अटल sमाप_प्रकार available_datatypes_show(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा most_channel *c = to_channel(dev);
	अचिन्हित पूर्णांक i = c->channel_id;

	म_नकल(buf, "");
	अगर (c->अगरace->channel_vector[i].data_type & MOST_CH_CONTROL)
		म_जोड़ो(buf, "control ");
	अगर (c->अगरace->channel_vector[i].data_type & MOST_CH_ASYNC)
		म_जोड़ो(buf, "async ");
	अगर (c->अगरace->channel_vector[i].data_type & MOST_CH_SYNC)
		म_जोड़ो(buf, "sync ");
	अगर (c->अगरace->channel_vector[i].data_type & MOST_CH_ISOC)
		म_जोड़ो(buf, "isoc ");
	म_जोड़ो(buf, "\n");
	वापस म_माप(buf);
पूर्ण

अटल sमाप_प्रकार number_of_packet_buffers_show(काष्ठा device *dev,
					     काष्ठा device_attribute *attr,
					     अक्षर *buf)
अणु
	काष्ठा most_channel *c = to_channel(dev);
	अचिन्हित पूर्णांक i = c->channel_id;

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n",
			c->अगरace->channel_vector[i].num_buffers_packet);
पूर्ण

अटल sमाप_प्रकार number_of_stream_buffers_show(काष्ठा device *dev,
					     काष्ठा device_attribute *attr,
					     अक्षर *buf)
अणु
	काष्ठा most_channel *c = to_channel(dev);
	अचिन्हित पूर्णांक i = c->channel_id;

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n",
			c->अगरace->channel_vector[i].num_buffers_streaming);
पूर्ण

अटल sमाप_प्रकार size_of_packet_buffer_show(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  अक्षर *buf)
अणु
	काष्ठा most_channel *c = to_channel(dev);
	अचिन्हित पूर्णांक i = c->channel_id;

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n",
			c->अगरace->channel_vector[i].buffer_size_packet);
पूर्ण

अटल sमाप_प्रकार size_of_stream_buffer_show(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  अक्षर *buf)
अणु
	काष्ठा most_channel *c = to_channel(dev);
	अचिन्हित पूर्णांक i = c->channel_id;

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n",
			c->अगरace->channel_vector[i].buffer_size_streaming);
पूर्ण

अटल sमाप_प्रकार channel_starving_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     अक्षर *buf)
अणु
	काष्ठा most_channel *c = to_channel(dev);

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", c->is_starving);
पूर्ण

अटल sमाप_प्रकार set_number_of_buffers_show(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  अक्षर *buf)
अणु
	काष्ठा most_channel *c = to_channel(dev);

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", c->cfg.num_buffers);
पूर्ण

अटल sमाप_प्रकार set_buffer_size_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    अक्षर *buf)
अणु
	काष्ठा most_channel *c = to_channel(dev);

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", c->cfg.buffer_size);
पूर्ण

अटल sमाप_प्रकार set_direction_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  अक्षर *buf)
अणु
	काष्ठा most_channel *c = to_channel(dev);

	अगर (c->cfg.direction & MOST_CH_TX)
		वापस snम_लिखो(buf, PAGE_SIZE, "tx\n");
	अन्यथा अगर (c->cfg.direction & MOST_CH_RX)
		वापस snम_लिखो(buf, PAGE_SIZE, "rx\n");
	वापस snम_लिखो(buf, PAGE_SIZE, "unconfigured\n");
पूर्ण

अटल sमाप_प्रकार set_datatype_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 अक्षर *buf)
अणु
	पूर्णांक i;
	काष्ठा most_channel *c = to_channel(dev);

	क्रम (i = 0; i < ARRAY_SIZE(ch_data_type); i++) अणु
		अगर (c->cfg.data_type & ch_data_type[i].most_ch_data_type)
			वापस snम_लिखो(buf, PAGE_SIZE, "%s",
					ch_data_type[i].name);
	पूर्ण
	वापस snम_लिखो(buf, PAGE_SIZE, "unconfigured\n");
पूर्ण

अटल sमाप_प्रकार set_subbuffer_size_show(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       अक्षर *buf)
अणु
	काष्ठा most_channel *c = to_channel(dev);

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", c->cfg.subbuffer_size);
पूर्ण

अटल sमाप_प्रकार set_packets_per_xact_show(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	काष्ठा most_channel *c = to_channel(dev);

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", c->cfg.packets_per_xact);
पूर्ण

अटल sमाप_प्रकार set_dbr_size_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा most_channel *c = to_channel(dev);

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", c->cfg.dbr_size);
पूर्ण

#घोषणा to_dev_attr(a) container_of(a, काष्ठा device_attribute, attr)
अटल umode_t channel_attr_is_visible(काष्ठा kobject *kobj,
				       काष्ठा attribute *attr, पूर्णांक index)
अणु
	काष्ठा device_attribute *dev_attr = to_dev_attr(attr);
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा most_channel *c = to_channel(dev);

	अगर (!म_भेद(dev_attr->attr.name, "set_dbr_size") &&
	    (c->अगरace->पूर्णांकerface != ITYPE_MEDIALB_DIM2))
		वापस 0;
	अगर (!म_भेद(dev_attr->attr.name, "set_packets_per_xact") &&
	    (c->अगरace->पूर्णांकerface != ITYPE_USB))
		वापस 0;

	वापस attr->mode;
पूर्ण

#घोषणा DEV_ATTR(_name)  (&dev_attr_##_name.attr)

अटल DEVICE_ATTR_RO(available_directions);
अटल DEVICE_ATTR_RO(available_datatypes);
अटल DEVICE_ATTR_RO(number_of_packet_buffers);
अटल DEVICE_ATTR_RO(number_of_stream_buffers);
अटल DEVICE_ATTR_RO(size_of_stream_buffer);
अटल DEVICE_ATTR_RO(size_of_packet_buffer);
अटल DEVICE_ATTR_RO(channel_starving);
अटल DEVICE_ATTR_RO(set_buffer_size);
अटल DEVICE_ATTR_RO(set_number_of_buffers);
अटल DEVICE_ATTR_RO(set_direction);
अटल DEVICE_ATTR_RO(set_datatype);
अटल DEVICE_ATTR_RO(set_subbuffer_size);
अटल DEVICE_ATTR_RO(set_packets_per_xact);
अटल DEVICE_ATTR_RO(set_dbr_size);

अटल काष्ठा attribute *channel_attrs[] = अणु
	DEV_ATTR(available_directions),
	DEV_ATTR(available_datatypes),
	DEV_ATTR(number_of_packet_buffers),
	DEV_ATTR(number_of_stream_buffers),
	DEV_ATTR(size_of_stream_buffer),
	DEV_ATTR(size_of_packet_buffer),
	DEV_ATTR(channel_starving),
	DEV_ATTR(set_buffer_size),
	DEV_ATTR(set_number_of_buffers),
	DEV_ATTR(set_direction),
	DEV_ATTR(set_datatype),
	DEV_ATTR(set_subbuffer_size),
	DEV_ATTR(set_packets_per_xact),
	DEV_ATTR(set_dbr_size),
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group channel_attr_group = अणु
	.attrs = channel_attrs,
	.is_visible = channel_attr_is_visible,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *channel_attr_groups[] = अणु
	&channel_attr_group,
	शून्य,
पूर्ण;

अटल sमाप_प्रकार description_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा most_पूर्णांकerface *अगरace = dev_get_drvdata(dev);

	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n", अगरace->description);
पूर्ण

अटल sमाप_प्रकार पूर्णांकerface_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा most_पूर्णांकerface *अगरace = dev_get_drvdata(dev);

	चयन (अगरace->पूर्णांकerface) अणु
	हाल ITYPE_LOOPBACK:
		वापस snम_लिखो(buf, PAGE_SIZE, "loopback\n");
	हाल ITYPE_I2C:
		वापस snम_लिखो(buf, PAGE_SIZE, "i2c\n");
	हाल ITYPE_I2S:
		वापस snम_लिखो(buf, PAGE_SIZE, "i2s\n");
	हाल ITYPE_TSI:
		वापस snम_लिखो(buf, PAGE_SIZE, "tsi\n");
	हाल ITYPE_HBI:
		वापस snम_लिखो(buf, PAGE_SIZE, "hbi\n");
	हाल ITYPE_MEDIALB_DIM:
		वापस snम_लिखो(buf, PAGE_SIZE, "mlb_dim\n");
	हाल ITYPE_MEDIALB_DIM2:
		वापस snम_लिखो(buf, PAGE_SIZE, "mlb_dim2\n");
	हाल ITYPE_USB:
		वापस snम_लिखो(buf, PAGE_SIZE, "usb\n");
	हाल ITYPE_PCIE:
		वापस snम_लिखो(buf, PAGE_SIZE, "pcie\n");
	पूर्ण
	वापस snम_लिखो(buf, PAGE_SIZE, "unknown\n");
पूर्ण

अटल DEVICE_ATTR_RO(description);
अटल DEVICE_ATTR_RO(पूर्णांकerface);

अटल काष्ठा attribute *पूर्णांकerface_attrs[] = अणु
	DEV_ATTR(description),
	DEV_ATTR(पूर्णांकerface),
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group पूर्णांकerface_attr_group = अणु
	.attrs = पूर्णांकerface_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *पूर्णांकerface_attr_groups[] = अणु
	&पूर्णांकerface_attr_group,
	शून्य,
पूर्ण;

अटल काष्ठा most_component *match_component(अक्षर *name)
अणु
	काष्ठा most_component *comp;

	list_क्रम_each_entry(comp, &comp_list, list) अणु
		अगर (!म_भेद(comp->name, name))
			वापस comp;
	पूर्ण
	वापस शून्य;
पूर्ण

काष्ठा show_links_data अणु
	पूर्णांक offs;
	अक्षर *buf;
पूर्ण;

अटल पूर्णांक prपूर्णांक_links(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा show_links_data *d = data;
	पूर्णांक offs = d->offs;
	अक्षर *buf = d->buf;
	काष्ठा most_channel *c;
	काष्ठा most_पूर्णांकerface *अगरace = dev_get_drvdata(dev);

	list_क्रम_each_entry(c, &अगरace->p->channel_list, list) अणु
		अगर (c->pipe0.comp) अणु
			offs += scnम_लिखो(buf + offs,
					 PAGE_SIZE - offs,
					 "%s:%s:%s\n",
					 c->pipe0.comp->name,
					 dev_name(अगरace->dev),
					 dev_name(&c->dev));
		पूर्ण
		अगर (c->pipe1.comp) अणु
			offs += scnम_लिखो(buf + offs,
					 PAGE_SIZE - offs,
					 "%s:%s:%s\n",
					 c->pipe1.comp->name,
					 dev_name(अगरace->dev),
					 dev_name(&c->dev));
		पूर्ण
	पूर्ण
	d->offs = offs;
	वापस 0;
पूर्ण

अटल पूर्णांक most_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	अगर (!म_भेद(dev_name(dev), "most"))
		वापस 0;
	अन्यथा
		वापस 1;
पूर्ण

अटल काष्ठा bus_type mostbus = अणु
	.name = "most",
	.match = most_match,
पूर्ण;

अटल sमाप_प्रकार links_show(काष्ठा device_driver *drv, अक्षर *buf)
अणु
	काष्ठा show_links_data d = अणु .buf = buf पूर्ण;

	bus_क्रम_each_dev(&mostbus, शून्य, &d, prपूर्णांक_links);
	वापस d.offs;
पूर्ण

अटल sमाप_प्रकार components_show(काष्ठा device_driver *drv, अक्षर *buf)
अणु
	काष्ठा most_component *comp;
	पूर्णांक offs = 0;

	list_क्रम_each_entry(comp, &comp_list, list) अणु
		offs += scnम_लिखो(buf + offs, PAGE_SIZE - offs, "%s\n",
				 comp->name);
	पूर्ण
	वापस offs;
पूर्ण

/**
 * get_channel - get poपूर्णांकer to channel
 * @mdev: name of the device पूर्णांकerface
 * @mdev_ch: name of channel
 */
अटल काष्ठा most_channel *get_channel(अक्षर *mdev, अक्षर *mdev_ch)
अणु
	काष्ठा device *dev = शून्य;
	काष्ठा most_पूर्णांकerface *अगरace;
	काष्ठा most_channel *c, *पंचांगp;

	dev = bus_find_device_by_name(&mostbus, शून्य, mdev);
	अगर (!dev)
		वापस शून्य;
	put_device(dev);
	अगरace = dev_get_drvdata(dev);
	list_क्रम_each_entry_safe(c, पंचांगp, &अगरace->p->channel_list, list) अणु
		अगर (!म_भेद(dev_name(&c->dev), mdev_ch))
			वापस c;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल
अंतरभूत पूर्णांक link_channel_to_component(काष्ठा most_channel *c,
				     काष्ठा most_component *comp,
				     अक्षर *name,
				     अक्षर *comp_param)
अणु
	पूर्णांक ret;
	काष्ठा most_component **comp_ptr;

	अगर (!c->pipe0.comp)
		comp_ptr = &c->pipe0.comp;
	अन्यथा अगर (!c->pipe1.comp)
		comp_ptr = &c->pipe1.comp;
	अन्यथा
		वापस -ENOSPC;

	*comp_ptr = comp;
	ret = comp->probe_channel(c->अगरace, c->channel_id, &c->cfg, name,
				  comp_param);
	अगर (ret) अणु
		*comp_ptr = शून्य;
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक most_set_cfg_buffer_size(अक्षर *mdev, अक्षर *mdev_ch, u16 val)
अणु
	काष्ठा most_channel *c = get_channel(mdev, mdev_ch);

	अगर (!c)
		वापस -ENODEV;
	c->cfg.buffer_size = val;
	वापस 0;
पूर्ण

पूर्णांक most_set_cfg_subbuffer_size(अक्षर *mdev, अक्षर *mdev_ch, u16 val)
अणु
	काष्ठा most_channel *c = get_channel(mdev, mdev_ch);

	अगर (!c)
		वापस -ENODEV;
	c->cfg.subbuffer_size = val;
	वापस 0;
पूर्ण

पूर्णांक most_set_cfg_dbr_size(अक्षर *mdev, अक्षर *mdev_ch, u16 val)
अणु
	काष्ठा most_channel *c = get_channel(mdev, mdev_ch);

	अगर (!c)
		वापस -ENODEV;
	c->cfg.dbr_size = val;
	वापस 0;
पूर्ण

पूर्णांक most_set_cfg_num_buffers(अक्षर *mdev, अक्षर *mdev_ch, u16 val)
अणु
	काष्ठा most_channel *c = get_channel(mdev, mdev_ch);

	अगर (!c)
		वापस -ENODEV;
	c->cfg.num_buffers = val;
	वापस 0;
पूर्ण

पूर्णांक most_set_cfg_datatype(अक्षर *mdev, अक्षर *mdev_ch, अक्षर *buf)
अणु
	पूर्णांक i;
	काष्ठा most_channel *c = get_channel(mdev, mdev_ch);

	अगर (!c)
		वापस -ENODEV;
	क्रम (i = 0; i < ARRAY_SIZE(ch_data_type); i++) अणु
		अगर (!म_भेद(buf, ch_data_type[i].name)) अणु
			c->cfg.data_type = ch_data_type[i].most_ch_data_type;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i == ARRAY_SIZE(ch_data_type))
		dev_warn(&c->dev, "Invalid attribute settings\n");
	वापस 0;
पूर्ण

पूर्णांक most_set_cfg_direction(अक्षर *mdev, अक्षर *mdev_ch, अक्षर *buf)
अणु
	काष्ठा most_channel *c = get_channel(mdev, mdev_ch);

	अगर (!c)
		वापस -ENODEV;
	अगर (!म_भेद(buf, "dir_rx")) अणु
		c->cfg.direction = MOST_CH_RX;
	पूर्ण अन्यथा अगर (!म_भेद(buf, "rx")) अणु
		c->cfg.direction = MOST_CH_RX;
	पूर्ण अन्यथा अगर (!म_भेद(buf, "dir_tx")) अणु
		c->cfg.direction = MOST_CH_TX;
	पूर्ण अन्यथा अगर (!म_भेद(buf, "tx")) अणु
		c->cfg.direction = MOST_CH_TX;
	पूर्ण अन्यथा अणु
		dev_err(&c->dev, "Invalid direction\n");
		वापस -ENODATA;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक most_set_cfg_packets_xact(अक्षर *mdev, अक्षर *mdev_ch, u16 val)
अणु
	काष्ठा most_channel *c = get_channel(mdev, mdev_ch);

	अगर (!c)
		वापस -ENODEV;
	c->cfg.packets_per_xact = val;
	वापस 0;
पूर्ण

पूर्णांक most_cfg_complete(अक्षर *comp_name)
अणु
	काष्ठा most_component *comp;

	comp = match_component(comp_name);
	अगर (!comp)
		वापस -ENODEV;

	वापस comp->cfg_complete();
पूर्ण

पूर्णांक most_add_link(अक्षर *mdev, अक्षर *mdev_ch, अक्षर *comp_name, अक्षर *link_name,
		  अक्षर *comp_param)
अणु
	काष्ठा most_channel *c = get_channel(mdev, mdev_ch);
	काष्ठा most_component *comp = match_component(comp_name);

	अगर (!c || !comp)
		वापस -ENODEV;

	वापस link_channel_to_component(c, comp, link_name, comp_param);
पूर्ण

पूर्णांक most_हटाओ_link(अक्षर *mdev, अक्षर *mdev_ch, अक्षर *comp_name)
अणु
	काष्ठा most_channel *c;
	काष्ठा most_component *comp;

	comp = match_component(comp_name);
	अगर (!comp)
		वापस -ENODEV;
	c = get_channel(mdev, mdev_ch);
	अगर (!c)
		वापस -ENODEV;

	अगर (comp->disconnect_channel(c->अगरace, c->channel_id))
		वापस -EIO;
	अगर (c->pipe0.comp == comp)
		c->pipe0.comp = शून्य;
	अगर (c->pipe1.comp == comp)
		c->pipe1.comp = शून्य;
	वापस 0;
पूर्ण

#घोषणा DRV_ATTR(_name)  (&driver_attr_##_name.attr)

अटल DRIVER_ATTR_RO(links);
अटल DRIVER_ATTR_RO(components);

अटल काष्ठा attribute *mc_attrs[] = अणु
	DRV_ATTR(links),
	DRV_ATTR(components),
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group mc_attr_group = अणु
	.attrs = mc_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *mc_attr_groups[] = अणु
	&mc_attr_group,
	शून्य,
पूर्ण;

अटल काष्ठा device_driver mostbus_driver = अणु
	.name = "most_core",
	.bus = &mostbus,
	.groups = mc_attr_groups,
पूर्ण;

अटल अंतरभूत व्योम trash_mbo(काष्ठा mbo *mbo)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा most_channel *c = mbo->context;

	spin_lock_irqsave(&c->fअगरo_lock, flags);
	list_add(&mbo->list, &c->trash_fअगरo);
	spin_unlock_irqrestore(&c->fअगरo_lock, flags);
पूर्ण

अटल bool hdm_mbo_पढ़ोy(काष्ठा most_channel *c)
अणु
	bool empty;

	अगर (c->enqueue_halt)
		वापस false;

	spin_lock_irq(&c->fअगरo_lock);
	empty = list_empty(&c->halt_fअगरo);
	spin_unlock_irq(&c->fअगरo_lock);

	वापस !empty;
पूर्ण

अटल व्योम nq_hdm_mbo(काष्ठा mbo *mbo)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा most_channel *c = mbo->context;

	spin_lock_irqsave(&c->fअगरo_lock, flags);
	list_add_tail(&mbo->list, &c->halt_fअगरo);
	spin_unlock_irqrestore(&c->fअगरo_lock, flags);
	wake_up_पूर्णांकerruptible(&c->hdm_fअगरo_wq);
पूर्ण

अटल पूर्णांक hdm_enqueue_thपढ़ो(व्योम *data)
अणु
	काष्ठा most_channel *c = data;
	काष्ठा mbo *mbo;
	पूर्णांक ret;
	typeof(c->अगरace->enqueue) enqueue = c->अगरace->enqueue;

	जबतक (likely(!kthपढ़ो_should_stop())) अणु
		रुको_event_पूर्णांकerruptible(c->hdm_fअगरo_wq,
					 hdm_mbo_पढ़ोy(c) ||
					 kthपढ़ो_should_stop());

		mutex_lock(&c->nq_mutex);
		spin_lock_irq(&c->fअगरo_lock);
		अगर (unlikely(c->enqueue_halt || list_empty(&c->halt_fअगरo))) अणु
			spin_unlock_irq(&c->fअगरo_lock);
			mutex_unlock(&c->nq_mutex);
			जारी;
		पूर्ण

		mbo = list_pop_mbo(&c->halt_fअगरo);
		spin_unlock_irq(&c->fअगरo_lock);

		अगर (c->cfg.direction == MOST_CH_RX)
			mbo->buffer_length = c->cfg.buffer_size;

		ret = enqueue(mbo->अगरp, mbo->hdm_channel_id, mbo);
		mutex_unlock(&c->nq_mutex);

		अगर (unlikely(ret)) अणु
			dev_err(&c->dev, "Buffer enqueue failed\n");
			nq_hdm_mbo(mbo);
			c->hdm_enqueue_task = शून्य;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक run_enqueue_thपढ़ो(काष्ठा most_channel *c, पूर्णांक channel_id)
अणु
	काष्ठा task_काष्ठा *task =
		kthपढ़ो_run(hdm_enqueue_thपढ़ो, c, "hdm_fifo_%d",
			    channel_id);

	अगर (IS_ERR(task))
		वापस PTR_ERR(task);

	c->hdm_enqueue_task = task;
	वापस 0;
पूर्ण

/**
 * arm_mbo - recycle MBO क्रम further usage
 * @mbo: most buffer
 *
 * This माला_दो an MBO back to the list to have it पढ़ोy क्रम up coming
 * tx transactions.
 *
 * In हाल the MBO beदीर्घs to a channel that recently has been
 * poisoned, the MBO is scheduled to be trashed.
 * Calls the completion handler of an attached component.
 */
अटल व्योम arm_mbo(काष्ठा mbo *mbo)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा most_channel *c;

	c = mbo->context;

	अगर (c->is_poisoned) अणु
		trash_mbo(mbo);
		वापस;
	पूर्ण

	spin_lock_irqsave(&c->fअगरo_lock, flags);
	++*mbo->num_buffers_ptr;
	list_add_tail(&mbo->list, &c->fअगरo);
	spin_unlock_irqrestore(&c->fअगरo_lock, flags);

	अगर (c->pipe0.refs && c->pipe0.comp->tx_completion)
		c->pipe0.comp->tx_completion(c->अगरace, c->channel_id);

	अगर (c->pipe1.refs && c->pipe1.comp->tx_completion)
		c->pipe1.comp->tx_completion(c->अगरace, c->channel_id);
पूर्ण

/**
 * arm_mbo_chain - helper function that arms an MBO chain क्रम the HDM
 * @c: poपूर्णांकer to पूर्णांकerface channel
 * @dir: direction of the channel
 * @compl: poपूर्णांकer to completion function
 *
 * This allocates buffer objects including the containing DMA coherent
 * buffer and माला_दो them in the fअगरo.
 * Buffers of Rx channels are put in the kthपढ़ो fअगरo, hence immediately
 * submitted to the HDM.
 *
 * Returns the number of allocated and enqueued MBOs.
 */
अटल पूर्णांक arm_mbo_chain(काष्ठा most_channel *c, पूर्णांक dir,
			 व्योम (*compl)(काष्ठा mbo *))
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा mbo *mbo;
	अचिन्हित दीर्घ flags;
	u32 coherent_buf_size = c->cfg.buffer_size + c->cfg.extra_len;

	atomic_set(&c->mbo_nq_level, 0);

	क्रम (i = 0; i < c->cfg.num_buffers; i++) अणु
		mbo = kzalloc(माप(*mbo), GFP_KERNEL);
		अगर (!mbo)
			जाओ flush_fअगरos;

		mbo->context = c;
		mbo->अगरp = c->अगरace;
		mbo->hdm_channel_id = c->channel_id;
		अगर (c->अगरace->dma_alloc) अणु
			mbo->virt_address =
				c->अगरace->dma_alloc(mbo, coherent_buf_size);
		पूर्ण अन्यथा अणु
			mbo->virt_address =
				kzalloc(coherent_buf_size, GFP_KERNEL);
		पूर्ण
		अगर (!mbo->virt_address)
			जाओ release_mbo;

		mbo->complete = compl;
		mbo->num_buffers_ptr = &dummy_num_buffers;
		अगर (dir == MOST_CH_RX) अणु
			nq_hdm_mbo(mbo);
			atomic_inc(&c->mbo_nq_level);
		पूर्ण अन्यथा अणु
			spin_lock_irqsave(&c->fअगरo_lock, flags);
			list_add_tail(&mbo->list, &c->fअगरo);
			spin_unlock_irqrestore(&c->fअगरo_lock, flags);
		पूर्ण
	पूर्ण
	वापस c->cfg.num_buffers;

release_mbo:
	kमुक्त(mbo);

flush_fअगरos:
	flush_channel_fअगरos(c);
	वापस 0;
पूर्ण

/**
 * most_submit_mbo - submits an MBO to fअगरo
 * @mbo: most buffer
 */
व्योम most_submit_mbo(काष्ठा mbo *mbo)
अणु
	अगर (WARN_ONCE(!mbo || !mbo->context,
		      "Bad buffer or missing channel reference\n"))
		वापस;

	nq_hdm_mbo(mbo);
पूर्ण
EXPORT_SYMBOL_GPL(most_submit_mbo);

/**
 * most_ग_लिखो_completion - ग_लिखो completion handler
 * @mbo: most buffer
 *
 * This recycles the MBO क्रम further usage. In हाल the channel has been
 * poisoned, the MBO is scheduled to be trashed.
 */
अटल व्योम most_ग_लिखो_completion(काष्ठा mbo *mbo)
अणु
	काष्ठा most_channel *c;

	c = mbo->context;
	अगर (unlikely(c->is_poisoned || (mbo->status == MBO_E_CLOSE)))
		trash_mbo(mbo);
	अन्यथा
		arm_mbo(mbo);
पूर्ण

पूर्णांक channel_has_mbo(काष्ठा most_पूर्णांकerface *अगरace, पूर्णांक id,
		    काष्ठा most_component *comp)
अणु
	काष्ठा most_channel *c = अगरace->p->channel[id];
	अचिन्हित दीर्घ flags;
	पूर्णांक empty;

	अगर (unlikely(!c))
		वापस -EINVAL;

	अगर (c->pipe0.refs && c->pipe1.refs &&
	    ((comp == c->pipe0.comp && c->pipe0.num_buffers <= 0) ||
	     (comp == c->pipe1.comp && c->pipe1.num_buffers <= 0)))
		वापस 0;

	spin_lock_irqsave(&c->fअगरo_lock, flags);
	empty = list_empty(&c->fअगरo);
	spin_unlock_irqrestore(&c->fअगरo_lock, flags);
	वापस !empty;
पूर्ण
EXPORT_SYMBOL_GPL(channel_has_mbo);

/**
 * most_get_mbo - get poपूर्णांकer to an MBO of pool
 * @अगरace: poपूर्णांकer to पूर्णांकerface instance
 * @id: channel ID
 * @comp: driver component
 *
 * This attempts to get a मुक्त buffer out of the channel fअगरo.
 * Returns a poपूर्णांकer to MBO on success or शून्य otherwise.
 */
काष्ठा mbo *most_get_mbo(काष्ठा most_पूर्णांकerface *अगरace, पूर्णांक id,
			 काष्ठा most_component *comp)
अणु
	काष्ठा mbo *mbo;
	काष्ठा most_channel *c;
	अचिन्हित दीर्घ flags;
	पूर्णांक *num_buffers_ptr;

	c = अगरace->p->channel[id];
	अगर (unlikely(!c))
		वापस शून्य;

	अगर (c->pipe0.refs && c->pipe1.refs &&
	    ((comp == c->pipe0.comp && c->pipe0.num_buffers <= 0) ||
	     (comp == c->pipe1.comp && c->pipe1.num_buffers <= 0)))
		वापस शून्य;

	अगर (comp == c->pipe0.comp)
		num_buffers_ptr = &c->pipe0.num_buffers;
	अन्यथा अगर (comp == c->pipe1.comp)
		num_buffers_ptr = &c->pipe1.num_buffers;
	अन्यथा
		num_buffers_ptr = &dummy_num_buffers;

	spin_lock_irqsave(&c->fअगरo_lock, flags);
	अगर (list_empty(&c->fअगरo)) अणु
		spin_unlock_irqrestore(&c->fअगरo_lock, flags);
		वापस शून्य;
	पूर्ण
	mbo = list_pop_mbo(&c->fअगरo);
	--*num_buffers_ptr;
	spin_unlock_irqrestore(&c->fअगरo_lock, flags);

	mbo->num_buffers_ptr = num_buffers_ptr;
	mbo->buffer_length = c->cfg.buffer_size;
	वापस mbo;
पूर्ण
EXPORT_SYMBOL_GPL(most_get_mbo);

/**
 * most_put_mbo - वापस buffer to pool
 * @mbo: most buffer
 */
व्योम most_put_mbo(काष्ठा mbo *mbo)
अणु
	काष्ठा most_channel *c = mbo->context;

	अगर (c->cfg.direction == MOST_CH_TX) अणु
		arm_mbo(mbo);
		वापस;
	पूर्ण
	nq_hdm_mbo(mbo);
	atomic_inc(&c->mbo_nq_level);
पूर्ण
EXPORT_SYMBOL_GPL(most_put_mbo);

/**
 * most_पढ़ो_completion - पढ़ो completion handler
 * @mbo: most buffer
 *
 * This function is called by the HDM when data has been received from the
 * hardware and copied to the buffer of the MBO.
 *
 * In हाल the channel has been poisoned it माला_दो the buffer in the trash queue.
 * Otherwise, it passes the buffer to an component क्रम further processing.
 */
अटल व्योम most_पढ़ो_completion(काष्ठा mbo *mbo)
अणु
	काष्ठा most_channel *c = mbo->context;

	अगर (unlikely(c->is_poisoned || (mbo->status == MBO_E_CLOSE))) अणु
		trash_mbo(mbo);
		वापस;
	पूर्ण

	अगर (mbo->status == MBO_E_INVAL) अणु
		nq_hdm_mbo(mbo);
		atomic_inc(&c->mbo_nq_level);
		वापस;
	पूर्ण

	अगर (atomic_sub_and_test(1, &c->mbo_nq_level))
		c->is_starving = 1;

	अगर (c->pipe0.refs && c->pipe0.comp->rx_completion &&
	    c->pipe0.comp->rx_completion(mbo) == 0)
		वापस;

	अगर (c->pipe1.refs && c->pipe1.comp->rx_completion &&
	    c->pipe1.comp->rx_completion(mbo) == 0)
		वापस;

	most_put_mbo(mbo);
पूर्ण

/**
 * most_start_channel - prepares a channel क्रम communication
 * @अगरace: poपूर्णांकer to पूर्णांकerface instance
 * @id: channel ID
 * @comp: driver component
 *
 * This prepares the channel क्रम usage. Cross-checks whether the
 * channel's been properly configured.
 *
 * Returns 0 on success or error code otherwise.
 */
पूर्णांक most_start_channel(काष्ठा most_पूर्णांकerface *अगरace, पूर्णांक id,
		       काष्ठा most_component *comp)
अणु
	पूर्णांक num_buffer;
	पूर्णांक ret;
	काष्ठा most_channel *c = अगरace->p->channel[id];

	अगर (unlikely(!c))
		वापस -EINVAL;

	mutex_lock(&c->start_mutex);
	अगर (c->pipe0.refs + c->pipe1.refs > 0)
		जाओ out; /* alपढ़ोy started by another component */

	अगर (!try_module_get(अगरace->mod)) अणु
		dev_err(&c->dev, "Failed to acquire HDM lock\n");
		mutex_unlock(&c->start_mutex);
		वापस -ENOLCK;
	पूर्ण

	c->cfg.extra_len = 0;
	अगर (c->अगरace->configure(c->अगरace, c->channel_id, &c->cfg)) अणु
		dev_err(&c->dev, "Channel configuration failed. Go check settings...\n");
		ret = -EINVAL;
		जाओ err_put_module;
	पूर्ण

	init_रुकोqueue_head(&c->hdm_fअगरo_wq);

	अगर (c->cfg.direction == MOST_CH_RX)
		num_buffer = arm_mbo_chain(c, c->cfg.direction,
					   most_पढ़ो_completion);
	अन्यथा
		num_buffer = arm_mbo_chain(c, c->cfg.direction,
					   most_ग_लिखो_completion);
	अगर (unlikely(!num_buffer)) अणु
		ret = -ENOMEM;
		जाओ err_put_module;
	पूर्ण

	ret = run_enqueue_thपढ़ो(c, id);
	अगर (ret)
		जाओ err_put_module;

	c->is_starving = 0;
	c->pipe0.num_buffers = c->cfg.num_buffers / 2;
	c->pipe1.num_buffers = c->cfg.num_buffers - c->pipe0.num_buffers;
	atomic_set(&c->mbo_ref, num_buffer);

out:
	अगर (comp == c->pipe0.comp)
		c->pipe0.refs++;
	अगर (comp == c->pipe1.comp)
		c->pipe1.refs++;
	mutex_unlock(&c->start_mutex);
	वापस 0;

err_put_module:
	module_put(अगरace->mod);
	mutex_unlock(&c->start_mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(most_start_channel);

/**
 * most_stop_channel - stops a running channel
 * @अगरace: poपूर्णांकer to पूर्णांकerface instance
 * @id: channel ID
 * @comp: driver component
 */
पूर्णांक most_stop_channel(काष्ठा most_पूर्णांकerface *अगरace, पूर्णांक id,
		      काष्ठा most_component *comp)
अणु
	काष्ठा most_channel *c;

	अगर (unlikely((!अगरace) || (id >= अगरace->num_channels) || (id < 0))) अणु
		pr_err("Bad interface or index out of range\n");
		वापस -EINVAL;
	पूर्ण
	c = अगरace->p->channel[id];
	अगर (unlikely(!c))
		वापस -EINVAL;

	mutex_lock(&c->start_mutex);
	अगर (c->pipe0.refs + c->pipe1.refs >= 2)
		जाओ out;

	अगर (c->hdm_enqueue_task)
		kthपढ़ो_stop(c->hdm_enqueue_task);
	c->hdm_enqueue_task = शून्य;

	अगर (अगरace->mod)
		module_put(अगरace->mod);

	c->is_poisoned = true;
	अगर (c->अगरace->poison_channel(c->अगरace, c->channel_id)) अणु
		dev_err(&c->dev, "Failed to stop channel %d of interface %s\n", c->channel_id,
			c->अगरace->description);
		mutex_unlock(&c->start_mutex);
		वापस -EAGAIN;
	पूर्ण
	flush_trash_fअगरo(c);
	flush_channel_fअगरos(c);

#अगर_घोषित CMPL_INTERRUPTIBLE
	अगर (रुको_क्रम_completion_पूर्णांकerruptible(&c->cleanup)) अणु
		dev_err(&c->dev, "Interrupted while cleaning up channel %d\n", c->channel_id);
		mutex_unlock(&c->start_mutex);
		वापस -EINTR;
	पूर्ण
#अन्यथा
	रुको_क्रम_completion(&c->cleanup);
#पूर्ण_अगर
	c->is_poisoned = false;

out:
	अगर (comp == c->pipe0.comp)
		c->pipe0.refs--;
	अगर (comp == c->pipe1.comp)
		c->pipe1.refs--;
	mutex_unlock(&c->start_mutex);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(most_stop_channel);

/**
 * most_रेजिस्टर_component - रेजिस्टरs a driver component with the core
 * @comp: driver component
 */
पूर्णांक most_रेजिस्टर_component(काष्ठा most_component *comp)
अणु
	अगर (!comp) अणु
		pr_err("Bad component\n");
		वापस -EINVAL;
	पूर्ण
	list_add_tail(&comp->list, &comp_list);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(most_रेजिस्टर_component);

अटल पूर्णांक disconnect_channels(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा most_पूर्णांकerface *अगरace;
	काष्ठा most_channel *c, *पंचांगp;
	काष्ठा most_component *comp = data;

	अगरace = dev_get_drvdata(dev);
	list_क्रम_each_entry_safe(c, पंचांगp, &अगरace->p->channel_list, list) अणु
		अगर (c->pipe0.comp == comp || c->pipe1.comp == comp)
			comp->disconnect_channel(c->अगरace, c->channel_id);
		अगर (c->pipe0.comp == comp)
			c->pipe0.comp = शून्य;
		अगर (c->pipe1.comp == comp)
			c->pipe1.comp = शून्य;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * most_deरेजिस्टर_component - deरेजिस्टरs a driver component with the core
 * @comp: driver component
 */
पूर्णांक most_deरेजिस्टर_component(काष्ठा most_component *comp)
अणु
	अगर (!comp) अणु
		pr_err("Bad component\n");
		वापस -EINVAL;
	पूर्ण

	bus_क्रम_each_dev(&mostbus, शून्य, comp, disconnect_channels);
	list_del(&comp->list);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(most_deरेजिस्टर_component);

अटल व्योम release_channel(काष्ठा device *dev)
अणु
	काष्ठा most_channel *c = to_channel(dev);

	kमुक्त(c);
पूर्ण

/**
 * most_रेजिस्टर_पूर्णांकerface - रेजिस्टरs an पूर्णांकerface with core
 * @अगरace: device पूर्णांकerface
 *
 * Allocates and initializes a new पूर्णांकerface instance and all of its channels.
 * Returns a poपूर्णांकer to kobject or an error poपूर्णांकer.
 */
पूर्णांक most_रेजिस्टर_पूर्णांकerface(काष्ठा most_पूर्णांकerface *अगरace)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक id;
	काष्ठा most_channel *c;

	अगर (!अगरace || !अगरace->enqueue || !अगरace->configure ||
	    !अगरace->poison_channel || (अगरace->num_channels > MAX_CHANNELS))
		वापस -EINVAL;

	id = ida_simple_get(&mdev_id, 0, 0, GFP_KERNEL);
	अगर (id < 0) अणु
		dev_err(अगरace->dev, "Failed to allocate device ID\n");
		वापस id;
	पूर्ण

	अगरace->p = kzalloc(माप(*अगरace->p), GFP_KERNEL);
	अगर (!अगरace->p) अणु
		ida_simple_हटाओ(&mdev_id, id);
		वापस -ENOMEM;
	पूर्ण

	INIT_LIST_HEAD(&अगरace->p->channel_list);
	अगरace->p->dev_id = id;
	strscpy(अगरace->p->name, अगरace->description, माप(अगरace->p->name));
	अगरace->dev->bus = &mostbus;
	अगरace->dev->groups = पूर्णांकerface_attr_groups;
	dev_set_drvdata(अगरace->dev, अगरace);
	अगर (device_रेजिस्टर(अगरace->dev)) अणु
		dev_err(अगरace->dev, "Failed to register interface device\n");
		kमुक्त(अगरace->p);
		put_device(अगरace->dev);
		ida_simple_हटाओ(&mdev_id, id);
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < अगरace->num_channels; i++) अणु
		स्थिर अक्षर *name_suffix = अगरace->channel_vector[i].name_suffix;

		c = kzalloc(माप(*c), GFP_KERNEL);
		अगर (!c)
			जाओ err_मुक्त_resources;
		अगर (!name_suffix)
			snम_लिखो(c->name, STRING_SIZE, "ch%d", i);
		अन्यथा
			snम_लिखो(c->name, STRING_SIZE, "%s", name_suffix);
		c->dev.init_name = c->name;
		c->dev.parent = अगरace->dev;
		c->dev.groups = channel_attr_groups;
		c->dev.release = release_channel;
		अगरace->p->channel[i] = c;
		c->is_starving = 0;
		c->अगरace = अगरace;
		c->channel_id = i;
		c->keep_mbo = false;
		c->enqueue_halt = false;
		c->is_poisoned = false;
		c->cfg.direction = 0;
		c->cfg.data_type = 0;
		c->cfg.num_buffers = 0;
		c->cfg.buffer_size = 0;
		c->cfg.subbuffer_size = 0;
		c->cfg.packets_per_xact = 0;
		spin_lock_init(&c->fअगरo_lock);
		INIT_LIST_HEAD(&c->fअगरo);
		INIT_LIST_HEAD(&c->trash_fअगरo);
		INIT_LIST_HEAD(&c->halt_fअगरo);
		init_completion(&c->cleanup);
		atomic_set(&c->mbo_ref, 0);
		mutex_init(&c->start_mutex);
		mutex_init(&c->nq_mutex);
		list_add_tail(&c->list, &अगरace->p->channel_list);
		अगर (device_रेजिस्टर(&c->dev)) अणु
			dev_err(&c->dev, "Failed to register channel device\n");
			जाओ err_मुक्त_most_channel;
		पूर्ण
	पूर्ण
	most_पूर्णांकerface_रेजिस्टर_notअगरy(अगरace->description);
	वापस 0;

err_मुक्त_most_channel:
	put_device(&c->dev);

err_मुक्त_resources:
	जबतक (i > 0) अणु
		c = अगरace->p->channel[--i];
		device_unरेजिस्टर(&c->dev);
	पूर्ण
	kमुक्त(अगरace->p);
	device_unरेजिस्टर(अगरace->dev);
	ida_simple_हटाओ(&mdev_id, id);
	वापस -ENOMEM;
पूर्ण
EXPORT_SYMBOL_GPL(most_रेजिस्टर_पूर्णांकerface);

/**
 * most_deरेजिस्टर_पूर्णांकerface - deरेजिस्टरs an पूर्णांकerface with core
 * @अगरace: device पूर्णांकerface
 *
 * Beक्रमe removing an पूर्णांकerface instance from the list, all running
 * channels are stopped and poisoned.
 */
व्योम most_deरेजिस्टर_पूर्णांकerface(काष्ठा most_पूर्णांकerface *अगरace)
अणु
	पूर्णांक i;
	काष्ठा most_channel *c;

	क्रम (i = 0; i < अगरace->num_channels; i++) अणु
		c = अगरace->p->channel[i];
		अगर (c->pipe0.comp)
			c->pipe0.comp->disconnect_channel(c->अगरace,
							c->channel_id);
		अगर (c->pipe1.comp)
			c->pipe1.comp->disconnect_channel(c->अगरace,
							c->channel_id);
		c->pipe0.comp = शून्य;
		c->pipe1.comp = शून्य;
		list_del(&c->list);
		device_unरेजिस्टर(&c->dev);
	पूर्ण

	ida_simple_हटाओ(&mdev_id, अगरace->p->dev_id);
	kमुक्त(अगरace->p);
	device_unरेजिस्टर(अगरace->dev);
पूर्ण
EXPORT_SYMBOL_GPL(most_deरेजिस्टर_पूर्णांकerface);

/**
 * most_stop_enqueue - prevents core from enqueueing MBOs
 * @अगरace: poपूर्णांकer to पूर्णांकerface
 * @id: channel id
 *
 * This is called by an HDM that _cannot_ attend to its duties and
 * is imminent to get run over by the core. The core is not going to
 * enqueue any further packets unless the flagging HDM calls
 * most_resume enqueue().
 */
व्योम most_stop_enqueue(काष्ठा most_पूर्णांकerface *अगरace, पूर्णांक id)
अणु
	काष्ठा most_channel *c = अगरace->p->channel[id];

	अगर (!c)
		वापस;

	mutex_lock(&c->nq_mutex);
	c->enqueue_halt = true;
	mutex_unlock(&c->nq_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(most_stop_enqueue);

/**
 * most_resume_enqueue - allow core to enqueue MBOs again
 * @अगरace: poपूर्णांकer to पूर्णांकerface
 * @id: channel id
 *
 * This clears the enqueue halt flag and enqueues all MBOs currently
 * sitting in the रुको fअगरo.
 */
व्योम most_resume_enqueue(काष्ठा most_पूर्णांकerface *अगरace, पूर्णांक id)
अणु
	काष्ठा most_channel *c = अगरace->p->channel[id];

	अगर (!c)
		वापस;

	mutex_lock(&c->nq_mutex);
	c->enqueue_halt = false;
	mutex_unlock(&c->nq_mutex);

	wake_up_पूर्णांकerruptible(&c->hdm_fअगरo_wq);
पूर्ण
EXPORT_SYMBOL_GPL(most_resume_enqueue);

अटल पूर्णांक __init most_init(व्योम)
अणु
	पूर्णांक err;

	INIT_LIST_HEAD(&comp_list);
	ida_init(&mdev_id);

	err = bus_रेजिस्टर(&mostbus);
	अगर (err) अणु
		pr_err("Failed to register most bus\n");
		वापस err;
	पूर्ण
	err = driver_रेजिस्टर(&mostbus_driver);
	अगर (err) अणु
		pr_err("Failed to register core driver\n");
		जाओ err_unरेजिस्टर_bus;
	पूर्ण
	configfs_init();
	वापस 0;

err_unरेजिस्टर_bus:
	bus_unरेजिस्टर(&mostbus);
	वापस err;
पूर्ण

अटल व्योम __निकास most_निकास(व्योम)
अणु
	driver_unरेजिस्टर(&mostbus_driver);
	bus_unरेजिस्टर(&mostbus);
	ida_destroy(&mdev_id);
पूर्ण

subsys_initcall(most_init);
module_निकास(most_निकास);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Christian Gromm <christian.gromm@microchip.com>");
MODULE_DESCRIPTION("Core module of stacked MOST Linux driver");
