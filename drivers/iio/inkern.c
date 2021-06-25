<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* The industrial I/O core in kernel channel mapping
 *
 * Copyright (c) 2011 Jonathan Cameron
 */
#समावेश <linux/err.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>

#समावेश <linux/iio/iपन.स>
#समावेश "iio_core.h"
#समावेश <linux/iio/machine.h>
#समावेश <linux/iio/driver.h>
#समावेश <linux/iio/consumer.h>

काष्ठा iio_map_पूर्णांकernal अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा iio_map *map;
	काष्ठा list_head l;
पूर्ण;

अटल LIST_HEAD(iio_map_list);
अटल DEFINE_MUTEX(iio_map_list_lock);

अटल पूर्णांक iio_map_array_unरेजिस्टर_locked(काष्ठा iio_dev *indio_dev)
अणु
	पूर्णांक ret = -ENODEV;
	काष्ठा iio_map_पूर्णांकernal *mapi, *next;

	list_क्रम_each_entry_safe(mapi, next, &iio_map_list, l) अणु
		अगर (indio_dev == mapi->indio_dev) अणु
			list_del(&mapi->l);
			kमुक्त(mapi);
			ret = 0;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक iio_map_array_रेजिस्टर(काष्ठा iio_dev *indio_dev, काष्ठा iio_map *maps)
अणु
	पूर्णांक i = 0, ret = 0;
	काष्ठा iio_map_पूर्णांकernal *mapi;

	अगर (maps == शून्य)
		वापस 0;

	mutex_lock(&iio_map_list_lock);
	जबतक (maps[i].consumer_dev_name != शून्य) अणु
		mapi = kzalloc(माप(*mapi), GFP_KERNEL);
		अगर (mapi == शून्य) अणु
			ret = -ENOMEM;
			जाओ error_ret;
		पूर्ण
		mapi->map = &maps[i];
		mapi->indio_dev = indio_dev;
		list_add_tail(&mapi->l, &iio_map_list);
		i++;
	पूर्ण
error_ret:
	अगर (ret)
		iio_map_array_unरेजिस्टर_locked(indio_dev);
	mutex_unlock(&iio_map_list_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(iio_map_array_रेजिस्टर);


/*
 * Remove all map entries associated with the given iio device
 */
पूर्णांक iio_map_array_unरेजिस्टर(काष्ठा iio_dev *indio_dev)
अणु
	पूर्णांक ret;

	mutex_lock(&iio_map_list_lock);
	ret = iio_map_array_unरेजिस्टर_locked(indio_dev);
	mutex_unlock(&iio_map_list_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(iio_map_array_unरेजिस्टर);

अटल स्थिर काष्ठा iio_chan_spec
*iio_chan_spec_from_name(स्थिर काष्ठा iio_dev *indio_dev, स्थिर अक्षर *name)
अणु
	पूर्णांक i;
	स्थिर काष्ठा iio_chan_spec *chan = शून्य;

	क्रम (i = 0; i < indio_dev->num_channels; i++)
		अगर (indio_dev->channels[i].datasheet_name &&
		    म_भेद(name, indio_dev->channels[i].datasheet_name) == 0) अणु
			chan = &indio_dev->channels[i];
			अवरोध;
		पूर्ण
	वापस chan;
पूर्ण

#अगर_घोषित CONFIG_OF

अटल पूर्णांक iio_dev_node_match(काष्ठा device *dev, स्थिर व्योम *data)
अणु
	वापस dev->of_node == data && dev->type == &iio_device_type;
पूर्ण

/**
 * __of_iio_simple_xlate - translate iiospec to the IIO channel index
 * @indio_dev:	poपूर्णांकer to the iio_dev काष्ठाure
 * @iiospec:	IIO specअगरier as found in the device tree
 *
 * This is simple translation function, suitable क्रम the most 1:1 mapped
 * channels in IIO chips. This function perक्रमms only one sanity check:
 * whether IIO index is less than num_channels (that is specअगरied in the
 * iio_dev).
 */
अटल पूर्णांक __of_iio_simple_xlate(काष्ठा iio_dev *indio_dev,
				स्थिर काष्ठा of_phandle_args *iiospec)
अणु
	अगर (!iiospec->args_count)
		वापस 0;

	अगर (iiospec->args[0] >= indio_dev->num_channels) अणु
		dev_err(&indio_dev->dev, "invalid channel index %u\n",
			iiospec->args[0]);
		वापस -EINVAL;
	पूर्ण

	वापस iiospec->args[0];
पूर्ण

अटल पूर्णांक __of_iio_channel_get(काष्ठा iio_channel *channel,
				काष्ठा device_node *np, पूर्णांक index)
अणु
	काष्ठा device *idev;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक err;
	काष्ठा of_phandle_args iiospec;

	err = of_parse_phandle_with_args(np, "io-channels",
					 "#io-channel-cells",
					 index, &iiospec);
	अगर (err)
		वापस err;

	idev = bus_find_device(&iio_bus_type, शून्य, iiospec.np,
			       iio_dev_node_match);
	of_node_put(iiospec.np);
	अगर (idev == शून्य)
		वापस -EPROBE_DEFER;

	indio_dev = dev_to_iio_dev(idev);
	channel->indio_dev = indio_dev;
	अगर (indio_dev->info->of_xlate)
		index = indio_dev->info->of_xlate(indio_dev, &iiospec);
	अन्यथा
		index = __of_iio_simple_xlate(indio_dev, &iiospec);
	अगर (index < 0)
		जाओ err_put;
	channel->channel = &indio_dev->channels[index];

	वापस 0;

err_put:
	iio_device_put(indio_dev);
	वापस index;
पूर्ण

अटल काष्ठा iio_channel *of_iio_channel_get(काष्ठा device_node *np, पूर्णांक index)
अणु
	काष्ठा iio_channel *channel;
	पूर्णांक err;

	अगर (index < 0)
		वापस ERR_PTR(-EINVAL);

	channel = kzalloc(माप(*channel), GFP_KERNEL);
	अगर (channel == शून्य)
		वापस ERR_PTR(-ENOMEM);

	err = __of_iio_channel_get(channel, np, index);
	अगर (err)
		जाओ err_मुक्त_channel;

	वापस channel;

err_मुक्त_channel:
	kमुक्त(channel);
	वापस ERR_PTR(err);
पूर्ण

काष्ठा iio_channel *of_iio_channel_get_by_name(काष्ठा device_node *np,
					       स्थिर अक्षर *name)
अणु
	काष्ठा iio_channel *chan = शून्य;

	/* Walk up the tree of devices looking क्रम a matching iio channel */
	जबतक (np) अणु
		पूर्णांक index = 0;

		/*
		 * For named iio channels, first look up the name in the
		 * "io-channel-names" property.  If it cannot be found, the
		 * index will be an error code, and of_iio_channel_get()
		 * will fail.
		 */
		अगर (name)
			index = of_property_match_string(np, "io-channel-names",
							 name);
		chan = of_iio_channel_get(np, index);
		अगर (!IS_ERR(chan) || PTR_ERR(chan) == -EPROBE_DEFER)
			अवरोध;
		अन्यथा अगर (name && index >= 0) अणु
			pr_err("ERROR: could not get IIO channel %pOF:%s(%i)\n",
				np, name ? name : "", index);
			वापस शून्य;
		पूर्ण

		/*
		 * No matching IIO channel found on this node.
		 * If the parent node has a "io-channel-ranges" property,
		 * then we can try one of its channels.
		 */
		np = np->parent;
		अगर (np && !of_get_property(np, "io-channel-ranges", शून्य))
			वापस शून्य;
	पूर्ण

	वापस chan;
पूर्ण
EXPORT_SYMBOL_GPL(of_iio_channel_get_by_name);

अटल काष्ठा iio_channel *of_iio_channel_get_all(काष्ठा device *dev)
अणु
	काष्ठा iio_channel *chans;
	पूर्णांक i, mapind, nummaps = 0;
	पूर्णांक ret;

	करो अणु
		ret = of_parse_phandle_with_args(dev->of_node,
						 "io-channels",
						 "#io-channel-cells",
						 nummaps, शून्य);
		अगर (ret < 0)
			अवरोध;
	पूर्ण जबतक (++nummaps);

	अगर (nummaps == 0)	/* no error, वापस शून्य to search map table */
		वापस शून्य;

	/* शून्य terminated array to save passing size */
	chans = kसुस्मृति(nummaps + 1, माप(*chans), GFP_KERNEL);
	अगर (chans == शून्य)
		वापस ERR_PTR(-ENOMEM);

	/* Search क्रम OF matches */
	क्रम (mapind = 0; mapind < nummaps; mapind++) अणु
		ret = __of_iio_channel_get(&chans[mapind], dev->of_node,
					   mapind);
		अगर (ret)
			जाओ error_मुक्त_chans;
	पूर्ण
	वापस chans;

error_मुक्त_chans:
	क्रम (i = 0; i < mapind; i++)
		iio_device_put(chans[i].indio_dev);
	kमुक्त(chans);
	वापस ERR_PTR(ret);
पूर्ण

#अन्यथा /* CONFIG_OF */

अटल अंतरभूत काष्ठा iio_channel *of_iio_channel_get_all(काष्ठा device *dev)
अणु
	वापस शून्य;
पूर्ण

#पूर्ण_अगर /* CONFIG_OF */

अटल काष्ठा iio_channel *iio_channel_get_sys(स्थिर अक्षर *name,
					       स्थिर अक्षर *channel_name)
अणु
	काष्ठा iio_map_पूर्णांकernal *c_i = शून्य, *c = शून्य;
	काष्ठा iio_channel *channel;
	पूर्णांक err;

	अगर (name == शून्य && channel_name == शून्य)
		वापस ERR_PTR(-ENODEV);

	/* first find matching entry the channel map */
	mutex_lock(&iio_map_list_lock);
	list_क्रम_each_entry(c_i, &iio_map_list, l) अणु
		अगर ((name && म_भेद(name, c_i->map->consumer_dev_name) != 0) ||
		    (channel_name &&
		     म_भेद(channel_name, c_i->map->consumer_channel) != 0))
			जारी;
		c = c_i;
		iio_device_get(c->indio_dev);
		अवरोध;
	पूर्ण
	mutex_unlock(&iio_map_list_lock);
	अगर (c == शून्य)
		वापस ERR_PTR(-ENODEV);

	channel = kzalloc(माप(*channel), GFP_KERNEL);
	अगर (channel == शून्य) अणु
		err = -ENOMEM;
		जाओ error_no_mem;
	पूर्ण

	channel->indio_dev = c->indio_dev;

	अगर (c->map->adc_channel_label) अणु
		channel->channel =
			iio_chan_spec_from_name(channel->indio_dev,
						c->map->adc_channel_label);

		अगर (channel->channel == शून्य) अणु
			err = -EINVAL;
			जाओ error_no_chan;
		पूर्ण
	पूर्ण

	वापस channel;

error_no_chan:
	kमुक्त(channel);
error_no_mem:
	iio_device_put(c->indio_dev);
	वापस ERR_PTR(err);
पूर्ण

काष्ठा iio_channel *iio_channel_get(काष्ठा device *dev,
				    स्थिर अक्षर *channel_name)
अणु
	स्थिर अक्षर *name = dev ? dev_name(dev) : शून्य;
	काष्ठा iio_channel *channel;

	अगर (dev) अणु
		channel = of_iio_channel_get_by_name(dev->of_node,
						     channel_name);
		अगर (channel != शून्य)
			वापस channel;
	पूर्ण

	वापस iio_channel_get_sys(name, channel_name);
पूर्ण
EXPORT_SYMBOL_GPL(iio_channel_get);

व्योम iio_channel_release(काष्ठा iio_channel *channel)
अणु
	अगर (!channel)
		वापस;
	iio_device_put(channel->indio_dev);
	kमुक्त(channel);
पूर्ण
EXPORT_SYMBOL_GPL(iio_channel_release);

अटल व्योम devm_iio_channel_मुक्त(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा iio_channel *channel = *(काष्ठा iio_channel **)res;

	iio_channel_release(channel);
पूर्ण

काष्ठा iio_channel *devm_iio_channel_get(काष्ठा device *dev,
					 स्थिर अक्षर *channel_name)
अणु
	काष्ठा iio_channel **ptr, *channel;

	ptr = devres_alloc(devm_iio_channel_मुक्त, माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस ERR_PTR(-ENOMEM);

	channel = iio_channel_get(dev, channel_name);
	अगर (IS_ERR(channel)) अणु
		devres_मुक्त(ptr);
		वापस channel;
	पूर्ण

	*ptr = channel;
	devres_add(dev, ptr);

	वापस channel;
पूर्ण
EXPORT_SYMBOL_GPL(devm_iio_channel_get);

काष्ठा iio_channel *devm_of_iio_channel_get_by_name(काष्ठा device *dev,
						    काष्ठा device_node *np,
						    स्थिर अक्षर *channel_name)
अणु
	काष्ठा iio_channel **ptr, *channel;

	ptr = devres_alloc(devm_iio_channel_मुक्त, माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस ERR_PTR(-ENOMEM);

	channel = of_iio_channel_get_by_name(np, channel_name);
	अगर (IS_ERR(channel)) अणु
		devres_मुक्त(ptr);
		वापस channel;
	पूर्ण

	*ptr = channel;
	devres_add(dev, ptr);

	वापस channel;
पूर्ण
EXPORT_SYMBOL_GPL(devm_of_iio_channel_get_by_name);

काष्ठा iio_channel *iio_channel_get_all(काष्ठा device *dev)
अणु
	स्थिर अक्षर *name;
	काष्ठा iio_channel *chans;
	काष्ठा iio_map_पूर्णांकernal *c = शून्य;
	पूर्णांक nummaps = 0;
	पूर्णांक mapind = 0;
	पूर्णांक i, ret;

	अगर (dev == शून्य)
		वापस ERR_PTR(-EINVAL);

	chans = of_iio_channel_get_all(dev);
	अगर (chans)
		वापस chans;

	name = dev_name(dev);

	mutex_lock(&iio_map_list_lock);
	/* first count the matching maps */
	list_क्रम_each_entry(c, &iio_map_list, l)
		अगर (name && म_भेद(name, c->map->consumer_dev_name) != 0)
			जारी;
		अन्यथा
			nummaps++;

	अगर (nummaps == 0) अणु
		ret = -ENODEV;
		जाओ error_ret;
	पूर्ण

	/* शून्य terminated array to save passing size */
	chans = kसुस्मृति(nummaps + 1, माप(*chans), GFP_KERNEL);
	अगर (chans == शून्य) अणु
		ret = -ENOMEM;
		जाओ error_ret;
	पूर्ण

	/* क्रम each map fill in the chans element */
	list_क्रम_each_entry(c, &iio_map_list, l) अणु
		अगर (name && म_भेद(name, c->map->consumer_dev_name) != 0)
			जारी;
		chans[mapind].indio_dev = c->indio_dev;
		chans[mapind].data = c->map->consumer_data;
		chans[mapind].channel =
			iio_chan_spec_from_name(chans[mapind].indio_dev,
						c->map->adc_channel_label);
		अगर (chans[mapind].channel == शून्य) अणु
			ret = -EINVAL;
			जाओ error_मुक्त_chans;
		पूर्ण
		iio_device_get(chans[mapind].indio_dev);
		mapind++;
	पूर्ण
	अगर (mapind == 0) अणु
		ret = -ENODEV;
		जाओ error_मुक्त_chans;
	पूर्ण
	mutex_unlock(&iio_map_list_lock);

	वापस chans;

error_मुक्त_chans:
	क्रम (i = 0; i < nummaps; i++)
		iio_device_put(chans[i].indio_dev);
	kमुक्त(chans);
error_ret:
	mutex_unlock(&iio_map_list_lock);

	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL_GPL(iio_channel_get_all);

व्योम iio_channel_release_all(काष्ठा iio_channel *channels)
अणु
	काष्ठा iio_channel *chan = &channels[0];

	जबतक (chan->indio_dev) अणु
		iio_device_put(chan->indio_dev);
		chan++;
	पूर्ण
	kमुक्त(channels);
पूर्ण
EXPORT_SYMBOL_GPL(iio_channel_release_all);

अटल व्योम devm_iio_channel_मुक्त_all(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा iio_channel *channels = *(काष्ठा iio_channel **)res;

	iio_channel_release_all(channels);
पूर्ण

काष्ठा iio_channel *devm_iio_channel_get_all(काष्ठा device *dev)
अणु
	काष्ठा iio_channel **ptr, *channels;

	ptr = devres_alloc(devm_iio_channel_मुक्त_all, माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस ERR_PTR(-ENOMEM);

	channels = iio_channel_get_all(dev);
	अगर (IS_ERR(channels)) अणु
		devres_मुक्त(ptr);
		वापस channels;
	पूर्ण

	*ptr = channels;
	devres_add(dev, ptr);

	वापस channels;
पूर्ण
EXPORT_SYMBOL_GPL(devm_iio_channel_get_all);

अटल पूर्णांक iio_channel_पढ़ो(काष्ठा iio_channel *chan, पूर्णांक *val, पूर्णांक *val2,
	क्रमागत iio_chan_info_क्रमागत info)
अणु
	पूर्णांक unused;
	पूर्णांक vals[INDIO_MAX_RAW_ELEMENTS];
	पूर्णांक ret;
	पूर्णांक val_len = 2;

	अगर (val2 == शून्य)
		val2 = &unused;

	अगर (!iio_channel_has_info(chan->channel, info))
		वापस -EINVAL;

	अगर (chan->indio_dev->info->पढ़ो_raw_multi) अणु
		ret = chan->indio_dev->info->पढ़ो_raw_multi(chan->indio_dev,
					chan->channel, INDIO_MAX_RAW_ELEMENTS,
					vals, &val_len, info);
		*val = vals[0];
		*val2 = vals[1];
	पूर्ण अन्यथा
		ret = chan->indio_dev->info->पढ़ो_raw(chan->indio_dev,
					chan->channel, val, val2, info);

	वापस ret;
पूर्ण

पूर्णांक iio_पढ़ो_channel_raw(काष्ठा iio_channel *chan, पूर्णांक *val)
अणु
	पूर्णांक ret;

	mutex_lock(&chan->indio_dev->info_exist_lock);
	अगर (chan->indio_dev->info == शून्य) अणु
		ret = -ENODEV;
		जाओ err_unlock;
	पूर्ण

	ret = iio_channel_पढ़ो(chan, val, शून्य, IIO_CHAN_INFO_RAW);
err_unlock:
	mutex_unlock(&chan->indio_dev->info_exist_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(iio_पढ़ो_channel_raw);

पूर्णांक iio_पढ़ो_channel_average_raw(काष्ठा iio_channel *chan, पूर्णांक *val)
अणु
	पूर्णांक ret;

	mutex_lock(&chan->indio_dev->info_exist_lock);
	अगर (chan->indio_dev->info == शून्य) अणु
		ret = -ENODEV;
		जाओ err_unlock;
	पूर्ण

	ret = iio_channel_पढ़ो(chan, val, शून्य, IIO_CHAN_INFO_AVERAGE_RAW);
err_unlock:
	mutex_unlock(&chan->indio_dev->info_exist_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(iio_पढ़ो_channel_average_raw);

अटल पूर्णांक iio_convert_raw_to_processed_unlocked(काष्ठा iio_channel *chan,
	पूर्णांक raw, पूर्णांक *processed, अचिन्हित पूर्णांक scale)
अणु
	पूर्णांक scale_type, scale_val, scale_val2, offset;
	s64 raw64 = raw;
	पूर्णांक ret;

	ret = iio_channel_पढ़ो(chan, &offset, शून्य, IIO_CHAN_INFO_OFFSET);
	अगर (ret >= 0)
		raw64 += offset;

	scale_type = iio_channel_पढ़ो(chan, &scale_val, &scale_val2,
					IIO_CHAN_INFO_SCALE);
	अगर (scale_type < 0) अणु
		/*
		 * Just pass raw values as processed अगर no scaling is
		 * available.
		 */
		*processed = raw;
		वापस 0;
	पूर्ण

	चयन (scale_type) अणु
	हाल IIO_VAL_INT:
		*processed = raw64 * scale_val;
		अवरोध;
	हाल IIO_VAL_INT_PLUS_MICRO:
		अगर (scale_val2 < 0)
			*processed = -raw64 * scale_val;
		अन्यथा
			*processed = raw64 * scale_val;
		*processed += भाग_s64(raw64 * (s64)scale_val2 * scale,
				      1000000LL);
		अवरोध;
	हाल IIO_VAL_INT_PLUS_न_अंकO:
		अगर (scale_val2 < 0)
			*processed = -raw64 * scale_val;
		अन्यथा
			*processed = raw64 * scale_val;
		*processed += भाग_s64(raw64 * (s64)scale_val2 * scale,
				      1000000000LL);
		अवरोध;
	हाल IIO_VAL_FRACTIONAL:
		*processed = भाग_s64(raw64 * (s64)scale_val * scale,
				     scale_val2);
		अवरोध;
	हाल IIO_VAL_FRACTIONAL_LOG2:
		*processed = (raw64 * (s64)scale_val * scale) >> scale_val2;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक iio_convert_raw_to_processed(काष्ठा iio_channel *chan, पूर्णांक raw,
	पूर्णांक *processed, अचिन्हित पूर्णांक scale)
अणु
	पूर्णांक ret;

	mutex_lock(&chan->indio_dev->info_exist_lock);
	अगर (chan->indio_dev->info == शून्य) अणु
		ret = -ENODEV;
		जाओ err_unlock;
	पूर्ण

	ret = iio_convert_raw_to_processed_unlocked(chan, raw, processed,
							scale);
err_unlock:
	mutex_unlock(&chan->indio_dev->info_exist_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(iio_convert_raw_to_processed);

पूर्णांक iio_पढ़ो_channel_attribute(काष्ठा iio_channel *chan, पूर्णांक *val, पूर्णांक *val2,
			       क्रमागत iio_chan_info_क्रमागत attribute)
अणु
	पूर्णांक ret;

	mutex_lock(&chan->indio_dev->info_exist_lock);
	अगर (chan->indio_dev->info == शून्य) अणु
		ret = -ENODEV;
		जाओ err_unlock;
	पूर्ण

	ret = iio_channel_पढ़ो(chan, val, val2, attribute);
err_unlock:
	mutex_unlock(&chan->indio_dev->info_exist_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(iio_पढ़ो_channel_attribute);

पूर्णांक iio_पढ़ो_channel_offset(काष्ठा iio_channel *chan, पूर्णांक *val, पूर्णांक *val2)
अणु
	वापस iio_पढ़ो_channel_attribute(chan, val, val2, IIO_CHAN_INFO_OFFSET);
पूर्ण
EXPORT_SYMBOL_GPL(iio_पढ़ो_channel_offset);

पूर्णांक iio_पढ़ो_channel_processed_scale(काष्ठा iio_channel *chan, पूर्णांक *val,
				     अचिन्हित पूर्णांक scale)
अणु
	पूर्णांक ret;

	mutex_lock(&chan->indio_dev->info_exist_lock);
	अगर (chan->indio_dev->info == शून्य) अणु
		ret = -ENODEV;
		जाओ err_unlock;
	पूर्ण

	अगर (iio_channel_has_info(chan->channel, IIO_CHAN_INFO_PROCESSED)) अणु
		ret = iio_channel_पढ़ो(chan, val, शून्य,
				       IIO_CHAN_INFO_PROCESSED);
		अगर (ret < 0)
			जाओ err_unlock;
		*val *= scale;
	पूर्ण अन्यथा अणु
		ret = iio_channel_पढ़ो(chan, val, शून्य, IIO_CHAN_INFO_RAW);
		अगर (ret < 0)
			जाओ err_unlock;
		ret = iio_convert_raw_to_processed_unlocked(chan, *val, val,
							    scale);
	पूर्ण

err_unlock:
	mutex_unlock(&chan->indio_dev->info_exist_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(iio_पढ़ो_channel_processed_scale);

पूर्णांक iio_पढ़ो_channel_processed(काष्ठा iio_channel *chan, पूर्णांक *val)
अणु
	/* This is just a special हाल with scale factor 1 */
	वापस iio_पढ़ो_channel_processed_scale(chan, val, 1);
पूर्ण
EXPORT_SYMBOL_GPL(iio_पढ़ो_channel_processed);

पूर्णांक iio_पढ़ो_channel_scale(काष्ठा iio_channel *chan, पूर्णांक *val, पूर्णांक *val2)
अणु
	वापस iio_पढ़ो_channel_attribute(chan, val, val2, IIO_CHAN_INFO_SCALE);
पूर्ण
EXPORT_SYMBOL_GPL(iio_पढ़ो_channel_scale);

अटल पूर्णांक iio_channel_पढ़ो_avail(काष्ठा iio_channel *chan,
				  स्थिर पूर्णांक **vals, पूर्णांक *type, पूर्णांक *length,
				  क्रमागत iio_chan_info_क्रमागत info)
अणु
	अगर (!iio_channel_has_available(chan->channel, info))
		वापस -EINVAL;

	वापस chan->indio_dev->info->पढ़ो_avail(chan->indio_dev, chan->channel,
						 vals, type, length, info);
पूर्ण

पूर्णांक iio_पढ़ो_avail_channel_attribute(काष्ठा iio_channel *chan,
				     स्थिर पूर्णांक **vals, पूर्णांक *type, पूर्णांक *length,
				     क्रमागत iio_chan_info_क्रमागत attribute)
अणु
	पूर्णांक ret;

	mutex_lock(&chan->indio_dev->info_exist_lock);
	अगर (!chan->indio_dev->info) अणु
		ret = -ENODEV;
		जाओ err_unlock;
	पूर्ण

	ret = iio_channel_पढ़ो_avail(chan, vals, type, length, attribute);
err_unlock:
	mutex_unlock(&chan->indio_dev->info_exist_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(iio_पढ़ो_avail_channel_attribute);

पूर्णांक iio_पढ़ो_avail_channel_raw(काष्ठा iio_channel *chan,
			       स्थिर पूर्णांक **vals, पूर्णांक *length)
अणु
	पूर्णांक ret;
	पूर्णांक type;

	ret = iio_पढ़ो_avail_channel_attribute(chan, vals, &type, length,
					 IIO_CHAN_INFO_RAW);

	अगर (ret >= 0 && type != IIO_VAL_INT)
		/* raw values are assumed to be IIO_VAL_INT */
		ret = -EINVAL;

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(iio_पढ़ो_avail_channel_raw);

अटल पूर्णांक iio_channel_पढ़ो_max(काष्ठा iio_channel *chan,
				पूर्णांक *val, पूर्णांक *val2, पूर्णांक *type,
				क्रमागत iio_chan_info_क्रमागत info)
अणु
	पूर्णांक unused;
	स्थिर पूर्णांक *vals;
	पूर्णांक length;
	पूर्णांक ret;

	अगर (!val2)
		val2 = &unused;

	ret = iio_channel_पढ़ो_avail(chan, &vals, type, &length, info);
	चयन (ret) अणु
	हाल IIO_AVAIL_RANGE:
		चयन (*type) अणु
		हाल IIO_VAL_INT:
			*val = vals[2];
			अवरोध;
		शेष:
			*val = vals[4];
			*val2 = vals[5];
		पूर्ण
		वापस 0;

	हाल IIO_AVAIL_LIST:
		अगर (length <= 0)
			वापस -EINVAL;
		चयन (*type) अणु
		हाल IIO_VAL_INT:
			*val = vals[--length];
			जबतक (length) अणु
				अगर (vals[--length] > *val)
					*val = vals[length];
			पूर्ण
			अवरोध;
		शेष:
			/* FIXME: learn about max क्रम other iio values */
			वापस -EINVAL;
		पूर्ण
		वापस 0;

	शेष:
		वापस ret;
	पूर्ण
पूर्ण

पूर्णांक iio_पढ़ो_max_channel_raw(काष्ठा iio_channel *chan, पूर्णांक *val)
अणु
	पूर्णांक ret;
	पूर्णांक type;

	mutex_lock(&chan->indio_dev->info_exist_lock);
	अगर (!chan->indio_dev->info) अणु
		ret = -ENODEV;
		जाओ err_unlock;
	पूर्ण

	ret = iio_channel_पढ़ो_max(chan, val, शून्य, &type, IIO_CHAN_INFO_RAW);
err_unlock:
	mutex_unlock(&chan->indio_dev->info_exist_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(iio_पढ़ो_max_channel_raw);

पूर्णांक iio_get_channel_type(काष्ठा iio_channel *chan, क्रमागत iio_chan_type *type)
अणु
	पूर्णांक ret = 0;
	/* Need to verअगरy underlying driver has not gone away */

	mutex_lock(&chan->indio_dev->info_exist_lock);
	अगर (chan->indio_dev->info == शून्य) अणु
		ret = -ENODEV;
		जाओ err_unlock;
	पूर्ण

	*type = chan->channel->type;
err_unlock:
	mutex_unlock(&chan->indio_dev->info_exist_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(iio_get_channel_type);

अटल पूर्णांक iio_channel_ग_लिखो(काष्ठा iio_channel *chan, पूर्णांक val, पूर्णांक val2,
			     क्रमागत iio_chan_info_क्रमागत info)
अणु
	वापस chan->indio_dev->info->ग_लिखो_raw(chan->indio_dev,
						chan->channel, val, val2, info);
पूर्ण

पूर्णांक iio_ग_लिखो_channel_attribute(काष्ठा iio_channel *chan, पूर्णांक val, पूर्णांक val2,
				क्रमागत iio_chan_info_क्रमागत attribute)
अणु
	पूर्णांक ret;

	mutex_lock(&chan->indio_dev->info_exist_lock);
	अगर (chan->indio_dev->info == शून्य) अणु
		ret = -ENODEV;
		जाओ err_unlock;
	पूर्ण

	ret = iio_channel_ग_लिखो(chan, val, val2, attribute);
err_unlock:
	mutex_unlock(&chan->indio_dev->info_exist_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(iio_ग_लिखो_channel_attribute);

पूर्णांक iio_ग_लिखो_channel_raw(काष्ठा iio_channel *chan, पूर्णांक val)
अणु
	वापस iio_ग_लिखो_channel_attribute(chan, val, 0, IIO_CHAN_INFO_RAW);
पूर्ण
EXPORT_SYMBOL_GPL(iio_ग_लिखो_channel_raw);

अचिन्हित पूर्णांक iio_get_channel_ext_info_count(काष्ठा iio_channel *chan)
अणु
	स्थिर काष्ठा iio_chan_spec_ext_info *ext_info;
	अचिन्हित पूर्णांक i = 0;

	अगर (!chan->channel->ext_info)
		वापस i;

	क्रम (ext_info = chan->channel->ext_info; ext_info->name; ext_info++)
		++i;

	वापस i;
पूर्ण
EXPORT_SYMBOL_GPL(iio_get_channel_ext_info_count);

अटल स्थिर काष्ठा iio_chan_spec_ext_info *iio_lookup_ext_info(
						स्थिर काष्ठा iio_channel *chan,
						स्थिर अक्षर *attr)
अणु
	स्थिर काष्ठा iio_chan_spec_ext_info *ext_info;

	अगर (!chan->channel->ext_info)
		वापस शून्य;

	क्रम (ext_info = chan->channel->ext_info; ext_info->name; ++ext_info) अणु
		अगर (!म_भेद(attr, ext_info->name))
			वापस ext_info;
	पूर्ण

	वापस शून्य;
पूर्ण

sमाप_प्रकार iio_पढ़ो_channel_ext_info(काष्ठा iio_channel *chan,
				  स्थिर अक्षर *attr, अक्षर *buf)
अणु
	स्थिर काष्ठा iio_chan_spec_ext_info *ext_info;

	ext_info = iio_lookup_ext_info(chan, attr);
	अगर (!ext_info)
		वापस -EINVAL;

	वापस ext_info->पढ़ो(chan->indio_dev, ext_info->निजी,
			      chan->channel, buf);
पूर्ण
EXPORT_SYMBOL_GPL(iio_पढ़ो_channel_ext_info);

sमाप_प्रकार iio_ग_लिखो_channel_ext_info(काष्ठा iio_channel *chan, स्थिर अक्षर *attr,
				   स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	स्थिर काष्ठा iio_chan_spec_ext_info *ext_info;

	ext_info = iio_lookup_ext_info(chan, attr);
	अगर (!ext_info)
		वापस -EINVAL;

	वापस ext_info->ग_लिखो(chan->indio_dev, ext_info->निजी,
			       chan->channel, buf, len);
पूर्ण
EXPORT_SYMBOL_GPL(iio_ग_लिखो_channel_ext_info);
