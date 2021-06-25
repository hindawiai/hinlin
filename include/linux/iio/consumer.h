<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Industrial I/O in kernel consumer पूर्णांकerface
 *
 * Copyright (c) 2011 Jonathan Cameron
 */
#अगर_अघोषित _IIO_INKERN_CONSUMER_H_
#घोषणा _IIO_INKERN_CONSUMER_H_

#समावेश <linux/types.h>
#समावेश <linux/iio/types.h>

काष्ठा iio_dev;
काष्ठा iio_chan_spec;
काष्ठा device;
काष्ठा device_node;

/**
 * काष्ठा iio_channel - everything needed क्रम a consumer to use a channel
 * @indio_dev:		Device on which the channel exists.
 * @channel:		Full description of the channel.
 * @data:		Data about the channel used by consumer.
 */
काष्ठा iio_channel अणु
	काष्ठा iio_dev *indio_dev;
	स्थिर काष्ठा iio_chan_spec *channel;
	व्योम *data;
पूर्ण;

/**
 * iio_channel_get() - get description of all that is needed to access channel.
 * @dev:		Poपूर्णांकer to consumer device. Device name must match
 *			the name of the device as provided in the iio_map
 *			with which the desired provider to consumer mapping
 *			was रेजिस्टरed.
 * @consumer_channel:	Unique name to identअगरy the channel on the consumer
 *			side. This typically describes the channels use within
 *			the consumer. E.g. 'battery_voltage'
 */
काष्ठा iio_channel *iio_channel_get(काष्ठा device *dev,
				    स्थिर अक्षर *consumer_channel);

/**
 * iio_channel_release() - release channels obtained via iio_channel_get
 * @chan:		The channel to be released.
 */
व्योम iio_channel_release(काष्ठा iio_channel *chan);

/**
 * devm_iio_channel_get() - Resource managed version of iio_channel_get().
 * @dev:		Poपूर्णांकer to consumer device. Device name must match
 *			the name of the device as provided in the iio_map
 *			with which the desired provider to consumer mapping
 *			was रेजिस्टरed.
 * @consumer_channel:	Unique name to identअगरy the channel on the consumer
 *			side. This typically describes the channels use within
 *			the consumer. E.g. 'battery_voltage'
 *
 * Returns a poपूर्णांकer to negative त्रुटि_सं अगर it is not able to get the iio channel
 * otherwise वापसs valid poपूर्णांकer क्रम iio channel.
 *
 * The allocated iio channel is स्वतःmatically released when the device is
 * unbound.
 */
काष्ठा iio_channel *devm_iio_channel_get(काष्ठा device *dev,
					 स्थिर अक्षर *consumer_channel);
/**
 * iio_channel_get_all() - get all channels associated with a client
 * @dev:		Poपूर्णांकer to consumer device.
 *
 * Returns an array of iio_channel काष्ठाures terminated with one with
 * null iio_dev poपूर्णांकer.
 * This function is used by fairly generic consumers to get all the
 * channels रेजिस्टरed as having this consumer.
 */
काष्ठा iio_channel *iio_channel_get_all(काष्ठा device *dev);

/**
 * iio_channel_release_all() - reverse iio_channel_get_all
 * @chan:		Array of channels to be released.
 */
व्योम iio_channel_release_all(काष्ठा iio_channel *chan);

/**
 * devm_iio_channel_get_all() - Resource managed version of
 *				iio_channel_get_all().
 * @dev: Poपूर्णांकer to consumer device.
 *
 * Returns a poपूर्णांकer to negative त्रुटि_सं अगर it is not able to get the iio channel
 * otherwise वापसs an array of iio_channel काष्ठाures terminated with one with
 * null iio_dev poपूर्णांकer.
 *
 * This function is used by fairly generic consumers to get all the
 * channels रेजिस्टरed as having this consumer.
 *
 * The allocated iio channels are स्वतःmatically released when the device is
 * unbounded.
 */
काष्ठा iio_channel *devm_iio_channel_get_all(काष्ठा device *dev);

/**
 * of_iio_channel_get_by_name() - get description of all that is needed to access channel.
 * @np:			Poपूर्णांकer to consumer device tree node
 * @consumer_channel:	Unique name to identअगरy the channel on the consumer
 *			side. This typically describes the channels use within
 *			the consumer. E.g. 'battery_voltage'
 */
#अगर_घोषित CONFIG_OF
काष्ठा iio_channel *of_iio_channel_get_by_name(काष्ठा device_node *np, स्थिर अक्षर *name);
#अन्यथा
अटल अंतरभूत काष्ठा iio_channel *
of_iio_channel_get_by_name(काष्ठा device_node *np, स्थिर अक्षर *name)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

/**
 * devm_of_iio_channel_get_by_name() - Resource managed version of of_iio_channel_get_by_name().
 * @dev:		Poपूर्णांकer to consumer device.
 * @np:			Poपूर्णांकer to consumer device tree node
 * @consumer_channel:	Unique name to identअगरy the channel on the consumer
 *			side. This typically describes the channels use within
 *			the consumer. E.g. 'battery_voltage'
 *
 * Returns a poपूर्णांकer to negative त्रुटि_सं अगर it is not able to get the iio channel
 * otherwise वापसs valid poपूर्णांकer क्रम iio channel.
 *
 * The allocated iio channel is स्वतःmatically released when the device is
 * unbound.
 */
काष्ठा iio_channel *devm_of_iio_channel_get_by_name(काष्ठा device *dev,
						    काष्ठा device_node *np,
						    स्थिर अक्षर *consumer_channel);

काष्ठा iio_cb_buffer;
/**
 * iio_channel_get_all_cb() - रेजिस्टर callback क्रम triggered capture
 * @dev:		Poपूर्णांकer to client device.
 * @cb:			Callback function.
 * @निजी:		Private data passed to callback.
 *
 * NB right now we have no ability to mux data from multiple devices.
 * So अगर the channels requested come from dअगरferent devices this will
 * fail.
 */
काष्ठा iio_cb_buffer *iio_channel_get_all_cb(काष्ठा device *dev,
					     पूर्णांक (*cb)(स्थिर व्योम *data,
						       व्योम *निजी),
					     व्योम *निजी);
/**
 * iio_channel_cb_set_buffer_watermark() - set the buffer watermark.
 * @cb_buffer:		The callback buffer from whom we want the channel
 *			inक्रमmation.
 * @watermark: buffer watermark in bytes.
 *
 * This function allows to configure the buffer watermark.
 */
पूर्णांक iio_channel_cb_set_buffer_watermark(काष्ठा iio_cb_buffer *cb_buffer,
					माप_प्रकार watermark);

/**
 * iio_channel_release_all_cb() - release and unरेजिस्टर the callback.
 * @cb_buffer:		The callback buffer that was allocated.
 */
व्योम iio_channel_release_all_cb(काष्ठा iio_cb_buffer *cb_buffer);

/**
 * iio_channel_start_all_cb() - start the flow of data through callback.
 * @cb_buff:		The callback buffer we are starting.
 */
पूर्णांक iio_channel_start_all_cb(काष्ठा iio_cb_buffer *cb_buff);

/**
 * iio_channel_stop_all_cb() - stop the flow of data through the callback.
 * @cb_buff:		The callback buffer we are stopping.
 */
व्योम iio_channel_stop_all_cb(काष्ठा iio_cb_buffer *cb_buff);

/**
 * iio_channel_cb_get_channels() - get access to the underlying channels.
 * @cb_buffer:		The callback buffer from whom we want the channel
 *			inक्रमmation.
 *
 * This function allows one to obtain inक्रमmation about the channels.
 * Whilst this may allow direct पढ़ोing अगर all buffers are disabled, the
 * primary aim is to allow drivers that are consuming a channel to query
 * things like scaling of the channel.
 */
काष्ठा iio_channel
*iio_channel_cb_get_channels(स्थिर काष्ठा iio_cb_buffer *cb_buffer);

/**
 * iio_channel_cb_get_iio_dev() - get access to the underlying device.
 * @cb_buffer:		The callback buffer from whom we want the device
 *			inक्रमmation.
 *
 * This function allows one to obtain inक्रमmation about the device.
 * The primary aim is to allow drivers that are consuming a device to query
 * things like current trigger.
 */
काष्ठा iio_dev
*iio_channel_cb_get_iio_dev(स्थिर काष्ठा iio_cb_buffer *cb_buffer);

/**
 * iio_पढ़ो_channel_raw() - पढ़ो from a given channel
 * @chan:		The channel being queried.
 * @val:		Value पढ़ो back.
 *
 * Note raw पढ़ोs from iio channels are in adc counts and hence
 * scale will need to be applied अगर standard units required.
 */
पूर्णांक iio_पढ़ो_channel_raw(काष्ठा iio_channel *chan,
			 पूर्णांक *val);

/**
 * iio_पढ़ो_channel_average_raw() - पढ़ो from a given channel
 * @chan:		The channel being queried.
 * @val:		Value पढ़ो back.
 *
 * Note raw पढ़ोs from iio channels are in adc counts and hence
 * scale will need to be applied अगर standard units required.
 *
 * In opposit to the normal iio_पढ़ो_channel_raw this function
 * वापसs the average of multiple पढ़ोs.
 */
पूर्णांक iio_पढ़ो_channel_average_raw(काष्ठा iio_channel *chan, पूर्णांक *val);

/**
 * iio_पढ़ो_channel_processed() - पढ़ो processed value from a given channel
 * @chan:		The channel being queried.
 * @val:		Value पढ़ो back.
 *
 * Returns an error code or 0.
 *
 * This function will पढ़ो a processed value from a channel. A processed value
 * means that this value will have the correct unit and not some device पूर्णांकernal
 * representation. If the device करोes not support reporting a processed value
 * the function will query the raw value and the channels scale and offset and
 * करो the appropriate transक्रमmation.
 */
पूर्णांक iio_पढ़ो_channel_processed(काष्ठा iio_channel *chan, पूर्णांक *val);

/**
 * iio_पढ़ो_channel_processed_scale() - पढ़ो and scale a processed value
 * @chan:		The channel being queried.
 * @val:		Value पढ़ो back.
 * @scale:		Scale factor to apply during the conversion
 *
 * Returns an error code or 0.
 *
 * This function will पढ़ो a processed value from a channel. This will work
 * like @iio_पढ़ो_channel_processed() but also scale with an additional
 * scale factor जबतक attempting to minimize any precision loss.
 */
पूर्णांक iio_पढ़ो_channel_processed_scale(काष्ठा iio_channel *chan, पूर्णांक *val,
				     अचिन्हित पूर्णांक scale);

/**
 * iio_ग_लिखो_channel_attribute() - Write values to the device attribute.
 * @chan:	The channel being queried.
 * @val:	Value being written.
 * @val2:	Value being written.val2 use depends on attribute type.
 * @attribute:	info attribute to be पढ़ो.
 *
 * Returns an error code or 0.
 */
पूर्णांक iio_ग_लिखो_channel_attribute(काष्ठा iio_channel *chan, पूर्णांक val,
				पूर्णांक val2, क्रमागत iio_chan_info_क्रमागत attribute);

/**
 * iio_पढ़ो_channel_attribute() - Read values from the device attribute.
 * @chan:	The channel being queried.
 * @val:	Value being written.
 * @val2:	Value being written.Val2 use depends on attribute type.
 * @attribute:	info attribute to be written.
 *
 * Returns an error code अगर failed. Else वापसs a description of what is in val
 * and val2, such as IIO_VAL_INT_PLUS_MICRO telling us we have a value of val
 * + val2/1e6
 */
पूर्णांक iio_पढ़ो_channel_attribute(काष्ठा iio_channel *chan, पूर्णांक *val,
			       पूर्णांक *val2, क्रमागत iio_chan_info_क्रमागत attribute);

/**
 * iio_ग_लिखो_channel_raw() - ग_लिखो to a given channel
 * @chan:		The channel being queried.
 * @val:		Value being written.
 *
 * Note raw ग_लिखोs to iio channels are in dac counts and hence
 * scale will need to be applied अगर standard units required.
 */
पूर्णांक iio_ग_लिखो_channel_raw(काष्ठा iio_channel *chan, पूर्णांक val);

/**
 * iio_पढ़ो_max_channel_raw() - पढ़ो maximum available raw value from a given
 *				channel, i.e. the maximum possible value.
 * @chan:		The channel being queried.
 * @val:		Value पढ़ो back.
 *
 * Note raw पढ़ोs from iio channels are in adc counts and hence
 * scale will need to be applied अगर standard units are required.
 */
पूर्णांक iio_पढ़ो_max_channel_raw(काष्ठा iio_channel *chan, पूर्णांक *val);

/**
 * iio_पढ़ो_avail_channel_raw() - पढ़ो available raw values from a given channel
 * @chan:		The channel being queried.
 * @vals:		Available values पढ़ो back.
 * @length:		Number of entries in vals.
 *
 * Returns an error code, IIO_AVAIL_RANGE or IIO_AVAIL_LIST.
 *
 * For ranges, three vals are always वापसed; min, step and max.
 * For lists, all the possible values are क्रमागतerated.
 *
 * Note raw available values from iio channels are in adc counts and
 * hence scale will need to be applied अगर standard units are required.
 */
पूर्णांक iio_पढ़ो_avail_channel_raw(काष्ठा iio_channel *chan,
			       स्थिर पूर्णांक **vals, पूर्णांक *length);

/**
 * iio_पढ़ो_avail_channel_attribute() - पढ़ो available channel attribute values
 * @chan:		The channel being queried.
 * @vals:		Available values पढ़ो back.
 * @type:		Type of values पढ़ो back.
 * @length:		Number of entries in vals.
 * @attribute:		info attribute to be पढ़ो back.
 *
 * Returns an error code, IIO_AVAIL_RANGE or IIO_AVAIL_LIST.
 */
पूर्णांक iio_पढ़ो_avail_channel_attribute(काष्ठा iio_channel *chan,
				     स्थिर पूर्णांक **vals, पूर्णांक *type, पूर्णांक *length,
				     क्रमागत iio_chan_info_क्रमागत attribute);

/**
 * iio_get_channel_type() - get the type of a channel
 * @channel:		The channel being queried.
 * @type:		The type of the channel.
 *
 * वापसs the क्रमागत iio_chan_type of the channel
 */
पूर्णांक iio_get_channel_type(काष्ठा iio_channel *channel,
			 क्रमागत iio_chan_type *type);

/**
 * iio_पढ़ो_channel_offset() - पढ़ो the offset value क्रम a channel
 * @chan:		The channel being queried.
 * @val:		First part of value पढ़ो back.
 * @val2:		Second part of value पढ़ो back.
 *
 * Note वापसs a description of what is in val and val2, such
 * as IIO_VAL_INT_PLUS_MICRO telling us we have a value of val
 * + val2/1e6
 */
पूर्णांक iio_पढ़ो_channel_offset(काष्ठा iio_channel *chan, पूर्णांक *val,
			   पूर्णांक *val2);

/**
 * iio_पढ़ो_channel_scale() - पढ़ो the scale value क्रम a channel
 * @chan:		The channel being queried.
 * @val:		First part of value पढ़ो back.
 * @val2:		Second part of value पढ़ो back.
 *
 * Note वापसs a description of what is in val and val2, such
 * as IIO_VAL_INT_PLUS_MICRO telling us we have a value of val
 * + val2/1e6
 */
पूर्णांक iio_पढ़ो_channel_scale(काष्ठा iio_channel *chan, पूर्णांक *val,
			   पूर्णांक *val2);

/**
 * iio_convert_raw_to_processed() - Converts a raw value to a processed value
 * @chan:		The channel being queried
 * @raw:		The raw IIO to convert
 * @processed:		The result of the conversion
 * @scale:		Scale factor to apply during the conversion
 *
 * Returns an error code or 0.
 *
 * This function converts a raw value to processed value क्रम a specअगरic channel.
 * A raw value is the device पूर्णांकernal representation of a sample and the value
 * वापसed by iio_पढ़ो_channel_raw, so the unit of that value is device
 * depended. A processed value on the other hand is value has a normed unit
 * according with the IIO specअगरication.
 *
 * The scale factor allows to increase the precession of the वापसed value. For
 * a scale factor of 1 the function will वापस the result in the normal IIO
 * unit क्रम the channel type. E.g. millivolt क्रम voltage channels, अगर you want
 * nanovolts instead pass 1000000 as the scale factor.
 */
पूर्णांक iio_convert_raw_to_processed(काष्ठा iio_channel *chan, पूर्णांक raw,
	पूर्णांक *processed, अचिन्हित पूर्णांक scale);

/**
 * iio_get_channel_ext_info_count() - get number of ext_info attributes
 *				      connected to the channel.
 * @chan:		The channel being queried
 *
 * Returns the number of ext_info attributes
 */
अचिन्हित पूर्णांक iio_get_channel_ext_info_count(काष्ठा iio_channel *chan);

/**
 * iio_पढ़ो_channel_ext_info() - पढ़ो ext_info attribute from a given channel
 * @chan:		The channel being queried.
 * @attr:		The ext_info attribute to पढ़ो.
 * @buf:		Where to store the attribute value. Assumed to hold
 *			at least PAGE_SIZE bytes.
 *
 * Returns the number of bytes written to buf (perhaps w/o zero termination;
 * it need not even be a string), or an error code.
 */
sमाप_प्रकार iio_पढ़ो_channel_ext_info(काष्ठा iio_channel *chan,
				  स्थिर अक्षर *attr, अक्षर *buf);

/**
 * iio_ग_लिखो_channel_ext_info() - ग_लिखो ext_info attribute from a given channel
 * @chan:		The channel being queried.
 * @attr:		The ext_info attribute to पढ़ो.
 * @buf:		The new attribute value. Strings needs to be zero-
 *			terminated, but the terminator should not be included
 *			in the below len.
 * @len:		The size of the new attribute value.
 *
 * Returns the number of accepted bytes, which should be the same as len.
 * An error code can also be वापसed.
 */
sमाप_प्रकार iio_ग_लिखो_channel_ext_info(काष्ठा iio_channel *chan, स्थिर अक्षर *attr,
				   स्थिर अक्षर *buf, माप_प्रकार len);

#पूर्ण_अगर
