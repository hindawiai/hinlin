<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * IIO multiplexer driver
 *
 * Copyright (C) 2017 Axentia Technologies AB
 *
 * Author: Peter Rosin <peda@axentia.se>
 */

#समावेश <linux/err.h>
#समावेश <linux/iio/consumer.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/mux/consumer.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>

काष्ठा mux_ext_info_cache अणु
	अक्षर *data;
	sमाप_प्रकार size;
पूर्ण;

काष्ठा mux_child अणु
	काष्ठा mux_ext_info_cache *ext_info_cache;
पूर्ण;

काष्ठा mux अणु
	पूर्णांक cached_state;
	काष्ठा mux_control *control;
	काष्ठा iio_channel *parent;
	काष्ठा iio_dev *indio_dev;
	काष्ठा iio_chan_spec *chan;
	काष्ठा iio_chan_spec_ext_info *ext_info;
	काष्ठा mux_child *child;
पूर्ण;

अटल पूर्णांक iio_mux_select(काष्ठा mux *mux, पूर्णांक idx)
अणु
	काष्ठा mux_child *child = &mux->child[idx];
	काष्ठा iio_chan_spec स्थिर *chan = &mux->chan[idx];
	पूर्णांक ret;
	पूर्णांक i;

	ret = mux_control_select(mux->control, chan->channel);
	अगर (ret < 0) अणु
		mux->cached_state = -1;
		वापस ret;
	पूर्ण

	अगर (mux->cached_state == chan->channel)
		वापस 0;

	अगर (chan->ext_info) अणु
		क्रम (i = 0; chan->ext_info[i].name; ++i) अणु
			स्थिर अक्षर *attr = chan->ext_info[i].name;
			काष्ठा mux_ext_info_cache *cache;

			cache = &child->ext_info_cache[i];

			अगर (cache->size < 0)
				जारी;

			ret = iio_ग_लिखो_channel_ext_info(mux->parent, attr,
							 cache->data,
							 cache->size);

			अगर (ret < 0) अणु
				mux_control_deselect(mux->control);
				mux->cached_state = -1;
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण
	mux->cached_state = chan->channel;

	वापस 0;
पूर्ण

अटल व्योम iio_mux_deselect(काष्ठा mux *mux)
अणु
	mux_control_deselect(mux->control);
पूर्ण

अटल पूर्णांक mux_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			काष्ठा iio_chan_spec स्थिर *chan,
			पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा mux *mux = iio_priv(indio_dev);
	पूर्णांक idx = chan - mux->chan;
	पूर्णांक ret;

	ret = iio_mux_select(mux, idx);
	अगर (ret < 0)
		वापस ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = iio_पढ़ो_channel_raw(mux->parent, val);
		अवरोध;

	हाल IIO_CHAN_INFO_SCALE:
		ret = iio_पढ़ो_channel_scale(mux->parent, val, val2);
		अवरोध;

	शेष:
		ret = -EINVAL;
	पूर्ण

	iio_mux_deselect(mux);

	वापस ret;
पूर्ण

अटल पूर्णांक mux_पढ़ो_avail(काष्ठा iio_dev *indio_dev,
			  काष्ठा iio_chan_spec स्थिर *chan,
			  स्थिर पूर्णांक **vals, पूर्णांक *type, पूर्णांक *length,
			  दीर्घ mask)
अणु
	काष्ठा mux *mux = iio_priv(indio_dev);
	पूर्णांक idx = chan - mux->chan;
	पूर्णांक ret;

	ret = iio_mux_select(mux, idx);
	अगर (ret < 0)
		वापस ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		*type = IIO_VAL_INT;
		ret = iio_पढ़ो_avail_channel_raw(mux->parent, vals, length);
		अवरोध;

	शेष:
		ret = -EINVAL;
	पूर्ण

	iio_mux_deselect(mux);

	वापस ret;
पूर्ण

अटल पूर्णांक mux_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			 काष्ठा iio_chan_spec स्थिर *chan,
			 पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा mux *mux = iio_priv(indio_dev);
	पूर्णांक idx = chan - mux->chan;
	पूर्णांक ret;

	ret = iio_mux_select(mux, idx);
	अगर (ret < 0)
		वापस ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = iio_ग_लिखो_channel_raw(mux->parent, val);
		अवरोध;

	शेष:
		ret = -EINVAL;
	पूर्ण

	iio_mux_deselect(mux);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_info mux_info = अणु
	.पढ़ो_raw = mux_पढ़ो_raw,
	.पढ़ो_avail = mux_पढ़ो_avail,
	.ग_लिखो_raw = mux_ग_लिखो_raw,
पूर्ण;

अटल sमाप_प्रकार mux_पढ़ो_ext_info(काष्ठा iio_dev *indio_dev, uपूर्णांकptr_t निजी,
				 काष्ठा iio_chan_spec स्थिर *chan, अक्षर *buf)
अणु
	काष्ठा mux *mux = iio_priv(indio_dev);
	पूर्णांक idx = chan - mux->chan;
	sमाप_प्रकार ret;

	ret = iio_mux_select(mux, idx);
	अगर (ret < 0)
		वापस ret;

	ret = iio_पढ़ो_channel_ext_info(mux->parent,
					mux->ext_info[निजी].name,
					buf);

	iio_mux_deselect(mux);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार mux_ग_लिखो_ext_info(काष्ठा iio_dev *indio_dev, uपूर्णांकptr_t निजी,
				  काष्ठा iio_chan_spec स्थिर *chan,
				  स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा device *dev = indio_dev->dev.parent;
	काष्ठा mux *mux = iio_priv(indio_dev);
	पूर्णांक idx = chan - mux->chan;
	अक्षर *new;
	sमाप_प्रकार ret;

	अगर (len >= PAGE_SIZE)
		वापस -EINVAL;

	ret = iio_mux_select(mux, idx);
	अगर (ret < 0)
		वापस ret;

	new = devm_kmemdup(dev, buf, len + 1, GFP_KERNEL);
	अगर (!new) अणु
		iio_mux_deselect(mux);
		वापस -ENOMEM;
	पूर्ण

	new[len] = 0;

	ret = iio_ग_लिखो_channel_ext_info(mux->parent,
					 mux->ext_info[निजी].name,
					 buf, len);
	अगर (ret < 0) अणु
		iio_mux_deselect(mux);
		devm_kमुक्त(dev, new);
		वापस ret;
	पूर्ण

	devm_kमुक्त(dev, mux->child[idx].ext_info_cache[निजी].data);
	mux->child[idx].ext_info_cache[निजी].data = new;
	mux->child[idx].ext_info_cache[निजी].size = len;

	iio_mux_deselect(mux);

	वापस ret;
पूर्ण

अटल पूर्णांक mux_configure_channel(काष्ठा device *dev, काष्ठा mux *mux,
				 u32 state, स्थिर अक्षर *label, पूर्णांक idx)
अणु
	काष्ठा mux_child *child = &mux->child[idx];
	काष्ठा iio_chan_spec *chan = &mux->chan[idx];
	काष्ठा iio_chan_spec स्थिर *pchan = mux->parent->channel;
	अक्षर *page = शून्य;
	पूर्णांक num_ext_info;
	पूर्णांक i;
	पूर्णांक ret;

	chan->indexed = 1;
	chan->output = pchan->output;
	chan->datasheet_name = label;
	chan->ext_info = mux->ext_info;

	ret = iio_get_channel_type(mux->parent, &chan->type);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to get parent channel type\n");
		वापस ret;
	पूर्ण

	अगर (iio_channel_has_info(pchan, IIO_CHAN_INFO_RAW))
		chan->info_mask_separate |= BIT(IIO_CHAN_INFO_RAW);
	अगर (iio_channel_has_info(pchan, IIO_CHAN_INFO_SCALE))
		chan->info_mask_separate |= BIT(IIO_CHAN_INFO_SCALE);

	अगर (iio_channel_has_available(pchan, IIO_CHAN_INFO_RAW))
		chan->info_mask_separate_available |= BIT(IIO_CHAN_INFO_RAW);

	अगर (state >= mux_control_states(mux->control)) अणु
		dev_err(dev, "too many channels\n");
		वापस -EINVAL;
	पूर्ण

	chan->channel = state;

	num_ext_info = iio_get_channel_ext_info_count(mux->parent);
	अगर (num_ext_info) अणु
		page = devm_kzalloc(dev, PAGE_SIZE, GFP_KERNEL);
		अगर (!page)
			वापस -ENOMEM;
	पूर्ण
	child->ext_info_cache = devm_kसुस्मृति(dev,
					     num_ext_info,
					     माप(*child->ext_info_cache),
					     GFP_KERNEL);
	अगर (!child->ext_info_cache)
		वापस -ENOMEM;

	क्रम (i = 0; i < num_ext_info; ++i) अणु
		child->ext_info_cache[i].size = -1;

		अगर (!pchan->ext_info[i].ग_लिखो)
			जारी;
		अगर (!pchan->ext_info[i].पढ़ो)
			जारी;

		ret = iio_पढ़ो_channel_ext_info(mux->parent,
						mux->ext_info[i].name,
						page);
		अगर (ret < 0) अणु
			dev_err(dev, "failed to get ext_info '%s'\n",
				pchan->ext_info[i].name);
			वापस ret;
		पूर्ण
		अगर (ret >= PAGE_SIZE) अणु
			dev_err(dev, "too large ext_info '%s'\n",
				pchan->ext_info[i].name);
			वापस -EINVAL;
		पूर्ण

		child->ext_info_cache[i].data = devm_kmemdup(dev, page, ret + 1,
							     GFP_KERNEL);
		अगर (!child->ext_info_cache[i].data)
			वापस -ENOMEM;

		child->ext_info_cache[i].data[ret] = 0;
		child->ext_info_cache[i].size = ret;
	पूर्ण

	अगर (page)
		devm_kमुक्त(dev, page);

	वापस 0;
पूर्ण

/*
 * Same as of_property_क्रम_each_string(), but also keeps track of the
 * index of each string.
 */
#घोषणा of_property_क्रम_each_string_index(np, propname, prop, s, i)	\
	क्रम (prop = of_find_property(np, propname, शून्य),		\
	     s = of_prop_next_string(prop, शून्य),			\
	     i = 0;							\
	     s;								\
	     s = of_prop_next_string(prop, s),				\
	     i++)

अटल पूर्णांक mux_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा iio_dev *indio_dev;
	काष्ठा iio_channel *parent;
	काष्ठा mux *mux;
	काष्ठा property *prop;
	स्थिर अक्षर *label;
	u32 state;
	पूर्णांक माप_ext_info;
	पूर्णांक children;
	पूर्णांक माप_priv;
	पूर्णांक i;
	पूर्णांक ret;

	अगर (!np)
		वापस -ENODEV;

	parent = devm_iio_channel_get(dev, "parent");
	अगर (IS_ERR(parent))
		वापस dev_err_probe(dev, PTR_ERR(parent),
				     "failed to get parent channel\n");

	माप_ext_info = iio_get_channel_ext_info_count(parent);
	अगर (माप_ext_info) अणु
		माप_ext_info += 1; /* one extra entry क्रम the sentinel */
		माप_ext_info *= माप(*mux->ext_info);
	पूर्ण

	children = 0;
	of_property_क्रम_each_string(np, "channels", prop, label) अणु
		अगर (*label)
			children++;
	पूर्ण
	अगर (children <= 0) अणु
		dev_err(dev, "not even a single child\n");
		वापस -EINVAL;
	पूर्ण

	माप_priv = माप(*mux);
	माप_priv += माप(*mux->child) * children;
	माप_priv += माप(*mux->chan) * children;
	माप_priv += माप_ext_info;

	indio_dev = devm_iio_device_alloc(dev, माप_priv);
	अगर (!indio_dev)
		वापस -ENOMEM;

	mux = iio_priv(indio_dev);
	mux->child = (काष्ठा mux_child *)(mux + 1);
	mux->chan = (काष्ठा iio_chan_spec *)(mux->child + children);

	platक्रमm_set_drvdata(pdev, indio_dev);

	mux->parent = parent;
	mux->cached_state = -1;

	indio_dev->name = dev_name(dev);
	indio_dev->info = &mux_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = mux->chan;
	indio_dev->num_channels = children;
	अगर (माप_ext_info) अणु
		mux->ext_info = devm_kmemdup(dev,
					     parent->channel->ext_info,
					     माप_ext_info, GFP_KERNEL);
		अगर (!mux->ext_info)
			वापस -ENOMEM;

		क्रम (i = 0; mux->ext_info[i].name; ++i) अणु
			अगर (parent->channel->ext_info[i].पढ़ो)
				mux->ext_info[i].पढ़ो = mux_पढ़ो_ext_info;
			अगर (parent->channel->ext_info[i].ग_लिखो)
				mux->ext_info[i].ग_लिखो = mux_ग_लिखो_ext_info;
			mux->ext_info[i].निजी = i;
		पूर्ण
	पूर्ण

	mux->control = devm_mux_control_get(dev, शून्य);
	अगर (IS_ERR(mux->control)) अणु
		अगर (PTR_ERR(mux->control) != -EPROBE_DEFER)
			dev_err(dev, "failed to get control-mux\n");
		वापस PTR_ERR(mux->control);
	पूर्ण

	i = 0;
	of_property_क्रम_each_string_index(np, "channels", prop, label, state) अणु
		अगर (!*label)
			जारी;

		ret = mux_configure_channel(dev, mux, state, label, i++);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	ret = devm_iio_device_रेजिस्टर(dev, indio_dev);
	अगर (ret) अणु
		dev_err(dev, "failed to register iio device\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mux_match[] = अणु
	अणु .compatible = "io-channel-mux" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mux_match);

अटल काष्ठा platक्रमm_driver mux_driver = अणु
	.probe = mux_probe,
	.driver = अणु
		.name = "iio-mux",
		.of_match_table = mux_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(mux_driver);

MODULE_DESCRIPTION("IIO multiplexer driver");
MODULE_AUTHOR("Peter Rosin <peda@axentia.se>");
MODULE_LICENSE("GPL v2");
