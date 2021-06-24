<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */

/* The industrial I/O core
 *
 * Copyright (c) 2008 Jonathan Cameron
 */
#अगर_अघोषित _INDUSTRIAL_IO_H_
#घोषणा _INDUSTRIAL_IO_H_

#समावेश <linux/device.h>
#समावेश <linux/cdev.h>
#समावेश <linux/iio/types.h>
#समावेश <linux/of.h>
/* IIO TODO LIST */
/*
 * Provide means of adjusting समयr accuracy.
 * Currently assumes nano seconds.
 */

क्रमागत iio_shared_by अणु
	IIO_SEPARATE,
	IIO_SHARED_BY_TYPE,
	IIO_SHARED_BY_सूची,
	IIO_SHARED_BY_ALL
पूर्ण;

क्रमागत iio_endian अणु
	IIO_CPU,
	IIO_BE,
	IIO_LE,
पूर्ण;

काष्ठा iio_chan_spec;
काष्ठा iio_dev;

/**
 * काष्ठा iio_chan_spec_ext_info - Extended channel info attribute
 * @name:	Info attribute name
 * @shared:	Whether this attribute is shared between all channels.
 * @पढ़ो:	Read callback क्रम this info attribute, may be शून्य.
 * @ग_लिखो:	Write callback क्रम this info attribute, may be शून्य.
 * @निजी:	Data निजी to the driver.
 */
काष्ठा iio_chan_spec_ext_info अणु
	स्थिर अक्षर *name;
	क्रमागत iio_shared_by shared;
	sमाप_प्रकार (*पढ़ो)(काष्ठा iio_dev *, uपूर्णांकptr_t निजी,
			काष्ठा iio_chan_spec स्थिर *, अक्षर *buf);
	sमाप_प्रकार (*ग_लिखो)(काष्ठा iio_dev *, uपूर्णांकptr_t निजी,
			 काष्ठा iio_chan_spec स्थिर *, स्थिर अक्षर *buf,
			 माप_प्रकार len);
	uपूर्णांकptr_t निजी;
पूर्ण;

/**
 * काष्ठा iio_क्रमागत - Enum channel info attribute
 * @items:	An array of strings.
 * @num_items:	Length of the item array.
 * @set:	Set callback function, may be शून्य.
 * @get:	Get callback function, may be शून्य.
 *
 * The iio_क्रमागत काष्ठा can be used to implement क्रमागत style channel attributes.
 * Enum style attributes are those which have a set of strings which map to
 * अचिन्हित पूर्णांकeger values. The IIO क्रमागत helper code takes care of mapping
 * between value and string as well as generating a "_available" file which
 * contains a list of all available items. The set callback will be called when
 * the attribute is updated. The last parameter is the index to the newly
 * activated item. The get callback will be used to query the currently active
 * item and is supposed to वापस the index क्रम it.
 */
काष्ठा iio_क्रमागत अणु
	स्थिर अक्षर * स्थिर *items;
	अचिन्हित पूर्णांक num_items;
	पूर्णांक (*set)(काष्ठा iio_dev *, स्थिर काष्ठा iio_chan_spec *, अचिन्हित पूर्णांक);
	पूर्णांक (*get)(काष्ठा iio_dev *, स्थिर काष्ठा iio_chan_spec *);
पूर्ण;

sमाप_प्रकार iio_क्रमागत_available_पढ़ो(काष्ठा iio_dev *indio_dev,
	uपूर्णांकptr_t priv, स्थिर काष्ठा iio_chan_spec *chan, अक्षर *buf);
sमाप_प्रकार iio_क्रमागत_पढ़ो(काष्ठा iio_dev *indio_dev,
	uपूर्णांकptr_t priv, स्थिर काष्ठा iio_chan_spec *chan, अक्षर *buf);
sमाप_प्रकार iio_क्रमागत_ग_लिखो(काष्ठा iio_dev *indio_dev,
	uपूर्णांकptr_t priv, स्थिर काष्ठा iio_chan_spec *chan, स्थिर अक्षर *buf,
	माप_प्रकार len);

/**
 * IIO_ENUM() - Initialize क्रमागत extended channel attribute
 * @_name:	Attribute name
 * @_shared:	Whether the attribute is shared between all channels
 * @_e:		Poपूर्णांकer to an iio_क्रमागत काष्ठा
 *
 * This should usually be used together with IIO_ENUM_AVAILABLE()
 */
#घोषणा IIO_ENUM(_name, _shared, _e) \
अणु \
	.name = (_name), \
	.shared = (_shared), \
	.पढ़ो = iio_क्रमागत_पढ़ो, \
	.ग_लिखो = iio_क्रमागत_ग_लिखो, \
	.निजी = (uपूर्णांकptr_t)(_e), \
पूर्ण

/**
 * IIO_ENUM_AVAILABLE() - Initialize क्रमागत available extended channel attribute
 * @_name:	Attribute name ("_available" will be appended to the name)
 * @_e:		Poपूर्णांकer to an iio_क्रमागत काष्ठा
 *
 * Creates a पढ़ो only attribute which lists all the available क्रमागत items in a
 * space separated list. This should usually be used together with IIO_ENUM()
 */
#घोषणा IIO_ENUM_AVAILABLE(_name, _e) \
अणु \
	.name = (_name "_available"), \
	.shared = IIO_SHARED_BY_TYPE, \
	.पढ़ो = iio_क्रमागत_available_पढ़ो, \
	.निजी = (uपूर्णांकptr_t)(_e), \
पूर्ण

/**
 * काष्ठा iio_mount_matrix - iio mounting matrix
 * @rotation: 3 dimensional space rotation matrix defining sensor alignment with
 *            मुख्य hardware
 */
काष्ठा iio_mount_matrix अणु
	स्थिर अक्षर *rotation[9];
पूर्ण;

sमाप_प्रकार iio_show_mount_matrix(काष्ठा iio_dev *indio_dev, uपूर्णांकptr_t priv,
			      स्थिर काष्ठा iio_chan_spec *chan, अक्षर *buf);
पूर्णांक iio_पढ़ो_mount_matrix(काष्ठा device *dev, स्थिर अक्षर *propname,
			  काष्ठा iio_mount_matrix *matrix);

प्रकार स्थिर काष्ठा iio_mount_matrix *
	(iio_get_mount_matrix_t)(स्थिर काष्ठा iio_dev *indio_dev,
				 स्थिर काष्ठा iio_chan_spec *chan);

/**
 * IIO_MOUNT_MATRIX() - Initialize mount matrix extended channel attribute
 * @_shared:	Whether the attribute is shared between all channels
 * @_get:	Poपूर्णांकer to an iio_get_mount_matrix_t accessor
 */
#घोषणा IIO_MOUNT_MATRIX(_shared, _get) \
अणु \
	.name = "mount_matrix", \
	.shared = (_shared), \
	.पढ़ो = iio_show_mount_matrix, \
	.निजी = (uपूर्णांकptr_t)(_get), \
पूर्ण

/**
 * काष्ठा iio_event_spec - specअगरication क्रम a channel event
 * @type:		    Type of the event
 * @dir:		    Direction of the event
 * @mask_separate:	    Bit mask of क्रमागत iio_event_info values. Attributes
 *			    set in this mask will be रेजिस्टरed per channel.
 * @mask_shared_by_type:    Bit mask of क्रमागत iio_event_info values. Attributes
 *			    set in this mask will be shared by channel type.
 * @mask_shared_by_dir:	    Bit mask of क्रमागत iio_event_info values. Attributes
 *			    set in this mask will be shared by channel type and
 *			    direction.
 * @mask_shared_by_all:	    Bit mask of क्रमागत iio_event_info values. Attributes
 *			    set in this mask will be shared by all channels.
 */
काष्ठा iio_event_spec अणु
	क्रमागत iio_event_type type;
	क्रमागत iio_event_direction dir;
	अचिन्हित दीर्घ mask_separate;
	अचिन्हित दीर्घ mask_shared_by_type;
	अचिन्हित दीर्घ mask_shared_by_dir;
	अचिन्हित दीर्घ mask_shared_by_all;
पूर्ण;

/**
 * काष्ठा iio_chan_spec - specअगरication of a single channel
 * @type:		What type of measurement is the channel making.
 * @channel:		What number करो we wish to assign the channel.
 * @channel2:		If there is a second number क्रम a dअगरferential
 *			channel then this is it. If modअगरied is set then the
 *			value here specअगरies the modअगरier.
 * @address:		Driver specअगरic identअगरier.
 * @scan_index:		Monotonic index to give ordering in scans when पढ़ो
 *			from a buffer.
 * @scan_type:		काष्ठा describing the scan type
 * @scan_type.sign:		's' or 'u' to specअगरy चिन्हित or अचिन्हित
 * @scan_type.realbits:		Number of valid bits of data
 * @scan_type.storagebits:	Realbits + padding
 * @scan_type.shअगरt:		Shअगरt right by this beक्रमe masking out
 *				realbits.
 * @scan_type.repeat:		Number of बार real/storage bits repeats.
 *				When the repeat element is more than 1, then
 *				the type element in sysfs will show a repeat
 *				value. Otherwise, the number of repetitions
 *				is omitted.
 * @scan_type.endianness:	little or big endian
 * @info_mask_separate: What inक्रमmation is to be exported that is specअगरic to
 *			this channel.
 * @info_mask_separate_available: What availability inक्रमmation is to be
 *			exported that is specअगरic to this channel.
 * @info_mask_shared_by_type: What inक्रमmation is to be exported that is shared
 *			by all channels of the same type.
 * @info_mask_shared_by_type_available: What availability inक्रमmation is to be
 *			exported that is shared by all channels of the same
 *			type.
 * @info_mask_shared_by_dir: What inक्रमmation is to be exported that is shared
 *			by all channels of the same direction.
 * @info_mask_shared_by_dir_available: What availability inक्रमmation is to be
 *			exported that is shared by all channels of the same
 *			direction.
 * @info_mask_shared_by_all: What inक्रमmation is to be exported that is shared
 *			by all channels.
 * @info_mask_shared_by_all_available: What availability inक्रमmation is to be
 *			exported that is shared by all channels.
 * @event_spec:		Array of events which should be रेजिस्टरed क्रम this
 *			channel.
 * @num_event_specs:	Size of the event_spec array.
 * @ext_info:		Array of extended info attributes क्रम this channel.
 *			The array is शून्य terminated, the last element should
 *			have its name field set to शून्य.
 * @extend_name:	Allows labeling of channel attributes with an
 *			inक्रमmative name. Note this has no effect codes etc,
 *			unlike modअगरiers.
 * @datasheet_name:	A name used in in-kernel mapping of channels. It should
 *			correspond to the first name that the channel is referred
 *			to by in the datasheet (e.g. IND), or the nearest
 *			possible compound name (e.g. IND-INC).
 * @modअगरied:		Does a modअगरier apply to this channel. What these are
 *			depends on the channel type.  Modअगरier is set in
 *			channel2. Examples are IIO_MOD_X क्रम axial sensors about
 *			the 'x' axis.
 * @indexed:		Specअगरy the channel has a numerical index. If not,
 *			the channel index number will be suppressed क्रम sysfs
 *			attributes but not क्रम event codes.
 * @output:		Channel is output.
 * @dअगरferential:	Channel is dअगरferential.
 */
काष्ठा iio_chan_spec अणु
	क्रमागत iio_chan_type	type;
	पूर्णांक			channel;
	पूर्णांक			channel2;
	अचिन्हित दीर्घ		address;
	पूर्णांक			scan_index;
	काष्ठा अणु
		अक्षर	sign;
		u8	realbits;
		u8	storagebits;
		u8	shअगरt;
		u8	repeat;
		क्रमागत iio_endian endianness;
	पूर्ण scan_type;
	दीर्घ			info_mask_separate;
	दीर्घ			info_mask_separate_available;
	दीर्घ			info_mask_shared_by_type;
	दीर्घ			info_mask_shared_by_type_available;
	दीर्घ			info_mask_shared_by_dir;
	दीर्घ			info_mask_shared_by_dir_available;
	दीर्घ			info_mask_shared_by_all;
	दीर्घ			info_mask_shared_by_all_available;
	स्थिर काष्ठा iio_event_spec *event_spec;
	अचिन्हित पूर्णांक		num_event_specs;
	स्थिर काष्ठा iio_chan_spec_ext_info *ext_info;
	स्थिर अक्षर		*extend_name;
	स्थिर अक्षर		*datasheet_name;
	अचिन्हित		modअगरied:1;
	अचिन्हित		indexed:1;
	अचिन्हित		output:1;
	अचिन्हित		dअगरferential:1;
पूर्ण;


/**
 * iio_channel_has_info() - Checks whether a channel supports a info attribute
 * @chan: The channel to be queried
 * @type: Type of the info attribute to be checked
 *
 * Returns true अगर the channels supports reporting values क्रम the given info
 * attribute type, false otherwise.
 */
अटल अंतरभूत bool iio_channel_has_info(स्थिर काष्ठा iio_chan_spec *chan,
	क्रमागत iio_chan_info_क्रमागत type)
अणु
	वापस (chan->info_mask_separate & BIT(type)) |
		(chan->info_mask_shared_by_type & BIT(type)) |
		(chan->info_mask_shared_by_dir & BIT(type)) |
		(chan->info_mask_shared_by_all & BIT(type));
पूर्ण

/**
 * iio_channel_has_available() - Checks अगर a channel has an available attribute
 * @chan: The channel to be queried
 * @type: Type of the available attribute to be checked
 *
 * Returns true अगर the channel supports reporting available values क्रम the
 * given attribute type, false otherwise.
 */
अटल अंतरभूत bool iio_channel_has_available(स्थिर काष्ठा iio_chan_spec *chan,
					     क्रमागत iio_chan_info_क्रमागत type)
अणु
	वापस (chan->info_mask_separate_available & BIT(type)) |
		(chan->info_mask_shared_by_type_available & BIT(type)) |
		(chan->info_mask_shared_by_dir_available & BIT(type)) |
		(chan->info_mask_shared_by_all_available & BIT(type));
पूर्ण

#घोषणा IIO_CHAN_SOFT_TIMESTAMP(_si) अणु					\
	.type = IIO_TIMESTAMP,						\
	.channel = -1,							\
	.scan_index = _si,						\
	.scan_type = अणु							\
		.sign = 's',						\
		.realbits = 64,					\
		.storagebits = 64,					\
		पूर्ण,							\
पूर्ण

s64 iio_get_समय_ns(स्थिर काष्ठा iio_dev *indio_dev);
अचिन्हित पूर्णांक iio_get_समय_res(स्थिर काष्ठा iio_dev *indio_dev);

/* Device operating modes */
#घोषणा INDIO_सूचीECT_MODE		0x01
#घोषणा INDIO_BUFFER_TRIGGERED		0x02
#घोषणा INDIO_BUFFER_SOFTWARE		0x04
#घोषणा INDIO_BUFFER_HARDWARE		0x08
#घोषणा INDIO_EVENT_TRIGGERED		0x10
#घोषणा INDIO_HARDWARE_TRIGGERED	0x20

#घोषणा INDIO_ALL_BUFFER_MODES					\
	(INDIO_BUFFER_TRIGGERED | INDIO_BUFFER_HARDWARE | INDIO_BUFFER_SOFTWARE)

#घोषणा INDIO_ALL_TRIGGERED_MODES	\
	(INDIO_BUFFER_TRIGGERED		\
	 | INDIO_EVENT_TRIGGERED	\
	 | INDIO_HARDWARE_TRIGGERED)

#घोषणा INDIO_MAX_RAW_ELEMENTS		4

काष्ठा iio_trigger; /* क्रमward declaration */

/**
 * काष्ठा iio_info - स्थिरant inक्रमmation about device
 * @event_attrs:	event control attributes
 * @attrs:		general purpose device attributes
 * @पढ़ो_raw:		function to request a value from the device.
 *			mask specअगरies which value. Note 0 means a पढ़ोing of
 *			the channel in question.  Return value will specअगरy the
 *			type of value वापसed by the device. val and val2 will
 *			contain the elements making up the वापसed value.
 * @पढ़ो_raw_multi:	function to वापस values from the device.
 *			mask specअगरies which value. Note 0 means a पढ़ोing of
 *			the channel in question.  Return value will specअगरy the
 *			type of value वापसed by the device. vals poपूर्णांकer
 *			contain the elements making up the वापसed value.
 *			max_len specअगरies maximum number of elements
 *			vals poपूर्णांकer can contain. val_len is used to वापस
 *			length of valid elements in vals.
 * @पढ़ो_avail:		function to वापस the available values from the device.
 *			mask specअगरies which value. Note 0 means the available
 *			values क्रम the channel in question.  Return value
 *			specअगरies अगर a IIO_AVAIL_LIST or a IIO_AVAIL_RANGE is
 *			वापसed in vals. The type of the vals are वापसed in
 *			type and the number of vals is वापसed in length. For
 *			ranges, there are always three vals वापसed; min, step
 *			and max. For lists, all possible values are क्रमागतerated.
 * @ग_लिखो_raw:		function to ग_लिखो a value to the device.
 *			Parameters are the same as क्रम पढ़ो_raw.
 * @पढ़ो_label:		function to request label name क्रम a specअगरied label,
 *			क्रम better channel identअगरication.
 * @ग_लिखो_raw_get_fmt:	callback function to query the expected
 *			क्रमmat/precision. If not set by the driver, ग_लिखो_raw
 *			वापसs IIO_VAL_INT_PLUS_MICRO.
 * @पढ़ो_event_config:	find out अगर the event is enabled.
 * @ग_लिखो_event_config:	set अगर the event is enabled.
 * @पढ़ो_event_value:	पढ़ो a configuration value associated with the event.
 * @ग_लिखो_event_value:	ग_लिखो a configuration value क्रम the event.
 * @validate_trigger:	function to validate the trigger when the
 *			current trigger माला_लो changed.
 * @update_scan_mode:	function to configure device and scan buffer when
 *			channels have changed
 * @debugfs_reg_access:	function to पढ़ो or ग_लिखो रेजिस्टर value of device
 * @of_xlate:		function poपूर्णांकer to obtain channel specअगरier index.
 *			When #iio-cells is greater than '0', the driver could
 *			provide a custom of_xlate function that पढ़ोs the
 *			*args* and वापसs the appropriate index in रेजिस्टरed
 *			IIO channels array.
 * @hwfअगरo_set_watermark: function poपूर्णांकer to set the current hardware
 *			fअगरo watermark level; see hwfअगरo_* entries in
 *			Documentation/ABI/testing/sysfs-bus-iio क्रम details on
 *			how the hardware fअगरo operates
 * @hwfअगरo_flush_to_buffer: function poपूर्णांकer to flush the samples stored
 *			in the hardware fअगरo to the device buffer. The driver
 *			should not flush more than count samples. The function
 *			must वापस the number of samples flushed, 0 अगर no
 *			samples were flushed or a negative पूर्णांकeger अगर no samples
 *			were flushed and there was an error.
 **/
काष्ठा iio_info अणु
	स्थिर काष्ठा attribute_group	*event_attrs;
	स्थिर काष्ठा attribute_group	*attrs;

	पूर्णांक (*पढ़ो_raw)(काष्ठा iio_dev *indio_dev,
			काष्ठा iio_chan_spec स्थिर *chan,
			पूर्णांक *val,
			पूर्णांक *val2,
			दीर्घ mask);

	पूर्णांक (*पढ़ो_raw_multi)(काष्ठा iio_dev *indio_dev,
			काष्ठा iio_chan_spec स्थिर *chan,
			पूर्णांक max_len,
			पूर्णांक *vals,
			पूर्णांक *val_len,
			दीर्घ mask);

	पूर्णांक (*पढ़ो_avail)(काष्ठा iio_dev *indio_dev,
			  काष्ठा iio_chan_spec स्थिर *chan,
			  स्थिर पूर्णांक **vals,
			  पूर्णांक *type,
			  पूर्णांक *length,
			  दीर्घ mask);

	पूर्णांक (*ग_लिखो_raw)(काष्ठा iio_dev *indio_dev,
			 काष्ठा iio_chan_spec स्थिर *chan,
			 पूर्णांक val,
			 पूर्णांक val2,
			 दीर्घ mask);

	पूर्णांक (*पढ़ो_label)(काष्ठा iio_dev *indio_dev,
			 काष्ठा iio_chan_spec स्थिर *chan,
			 अक्षर *label);

	पूर्णांक (*ग_लिखो_raw_get_fmt)(काष्ठा iio_dev *indio_dev,
			 काष्ठा iio_chan_spec स्थिर *chan,
			 दीर्घ mask);

	पूर्णांक (*पढ़ो_event_config)(काष्ठा iio_dev *indio_dev,
				 स्थिर काष्ठा iio_chan_spec *chan,
				 क्रमागत iio_event_type type,
				 क्रमागत iio_event_direction dir);

	पूर्णांक (*ग_लिखो_event_config)(काष्ठा iio_dev *indio_dev,
				  स्थिर काष्ठा iio_chan_spec *chan,
				  क्रमागत iio_event_type type,
				  क्रमागत iio_event_direction dir,
				  पूर्णांक state);

	पूर्णांक (*पढ़ो_event_value)(काष्ठा iio_dev *indio_dev,
				स्थिर काष्ठा iio_chan_spec *chan,
				क्रमागत iio_event_type type,
				क्रमागत iio_event_direction dir,
				क्रमागत iio_event_info info, पूर्णांक *val, पूर्णांक *val2);

	पूर्णांक (*ग_लिखो_event_value)(काष्ठा iio_dev *indio_dev,
				 स्थिर काष्ठा iio_chan_spec *chan,
				 क्रमागत iio_event_type type,
				 क्रमागत iio_event_direction dir,
				 क्रमागत iio_event_info info, पूर्णांक val, पूर्णांक val2);

	पूर्णांक (*validate_trigger)(काष्ठा iio_dev *indio_dev,
				काष्ठा iio_trigger *trig);
	पूर्णांक (*update_scan_mode)(काष्ठा iio_dev *indio_dev,
				स्थिर अचिन्हित दीर्घ *scan_mask);
	पूर्णांक (*debugfs_reg_access)(काष्ठा iio_dev *indio_dev,
				  अचिन्हित reg, अचिन्हित ग_लिखोval,
				  अचिन्हित *पढ़ोval);
	पूर्णांक (*of_xlate)(काष्ठा iio_dev *indio_dev,
			स्थिर काष्ठा of_phandle_args *iiospec);
	पूर्णांक (*hwfअगरo_set_watermark)(काष्ठा iio_dev *indio_dev, अचिन्हित val);
	पूर्णांक (*hwfअगरo_flush_to_buffer)(काष्ठा iio_dev *indio_dev,
				      अचिन्हित count);
पूर्ण;

/**
 * काष्ठा iio_buffer_setup_ops - buffer setup related callbacks
 * @preenable:		[DRIVER] function to run prior to marking buffer enabled
 * @postenable:		[DRIVER] function to run after marking buffer enabled
 * @predisable:		[DRIVER] function to run prior to marking buffer
 *			disabled
 * @postdisable:	[DRIVER] function to run after marking buffer disabled
 * @validate_scan_mask: [DRIVER] function callback to check whether a given
 *			scan mask is valid क्रम the device.
 */
काष्ठा iio_buffer_setup_ops अणु
	पूर्णांक (*preenable)(काष्ठा iio_dev *);
	पूर्णांक (*postenable)(काष्ठा iio_dev *);
	पूर्णांक (*predisable)(काष्ठा iio_dev *);
	पूर्णांक (*postdisable)(काष्ठा iio_dev *);
	bool (*validate_scan_mask)(काष्ठा iio_dev *indio_dev,
				   स्थिर अचिन्हित दीर्घ *scan_mask);
पूर्ण;

/**
 * काष्ठा iio_dev - industrial I/O device
 * @id:			[INTERN] used to identअगरy device पूर्णांकernally
 * @driver_module:	[INTERN] used to make it harder to undercut users
 * @modes:		[DRIVER] operating modes supported by device
 * @currenपंचांगode:	[DRIVER] current operating mode
 * @dev:		[DRIVER] device काष्ठाure, should be asचिन्हित a parent
 *			and owner
 * @buffer:		[DRIVER] any buffer present
 * @scan_bytes:		[INTERN] num bytes captured to be fed to buffer demux
 * @mlock:		[INTERN] lock used to prevent simultaneous device state
 *			changes
 * @available_scan_masks: [DRIVER] optional array of allowed biपंचांगasks
 * @masklength:		[INTERN] the length of the mask established from
 *			channels
 * @active_scan_mask:	[INTERN] जोड़ of all scan masks requested by buffers
 * @scan_बारtamp:	[INTERN] set अगर any buffers have requested बारtamp
 * @scan_index_बारtamp:[INTERN] cache of the index to the बारtamp
 * @trig:		[INTERN] current device trigger (buffer modes)
 * @trig_पढ़ोonly:	[INTERN] mark the current trigger immutable
 * @pollfunc:		[DRIVER] function run on trigger being received
 * @pollfunc_event:	[DRIVER] function run on events trigger being received
 * @channels:		[DRIVER] channel specअगरication काष्ठाure table
 * @num_channels:	[DRIVER] number of channels specअगरied in @channels.
 * @name:		[DRIVER] name of the device.
 * @label:              [DRIVER] unique name to identअगरy which device this is
 * @info:		[DRIVER] callbacks and स्थिरant info from driver
 * @घड़ी_id:		[INTERN] बारtamping घड़ी posix identअगरier
 * @info_exist_lock:	[INTERN] lock to prevent use during removal
 * @setup_ops:		[DRIVER] callbacks to call beक्रमe and after buffer
 *			enable/disable
 * @chrdev:		[INTERN] associated अक्षरacter device
 * @flags:		[INTERN] file ops related flags including busy flag.
 * @priv:		[DRIVER] reference to driver's निजी inक्रमmation
 *			**MUST** be accessed **ONLY** via iio_priv() helper
 */
काष्ठा iio_dev अणु
	पूर्णांक				id;
	काष्ठा module			*driver_module;

	पूर्णांक				modes;
	पूर्णांक				currenपंचांगode;
	काष्ठा device			dev;

	काष्ठा iio_buffer		*buffer;
	पूर्णांक				scan_bytes;
	काष्ठा mutex			mlock;

	स्थिर अचिन्हित दीर्घ		*available_scan_masks;
	अचिन्हित			masklength;
	स्थिर अचिन्हित दीर्घ		*active_scan_mask;
	bool				scan_बारtamp;
	अचिन्हित			scan_index_बारtamp;
	काष्ठा iio_trigger		*trig;
	bool				trig_पढ़ोonly;
	काष्ठा iio_poll_func		*pollfunc;
	काष्ठा iio_poll_func		*pollfunc_event;

	काष्ठा iio_chan_spec स्थिर	*channels;
	पूर्णांक				num_channels;

	स्थिर अक्षर			*name;
	स्थिर अक्षर			*label;
	स्थिर काष्ठा iio_info		*info;
	घड़ीid_t			घड़ी_id;
	काष्ठा mutex			info_exist_lock;
	स्थिर काष्ठा iio_buffer_setup_ops	*setup_ops;
	काष्ठा cdev			chrdev;

	अचिन्हित दीर्घ			flags;
	व्योम				*priv;
पूर्ण;

स्थिर काष्ठा iio_chan_spec
*iio_find_channel_from_si(काष्ठा iio_dev *indio_dev, पूर्णांक si);
/**
 * iio_device_रेजिस्टर() - रेजिस्टर a device with the IIO subप्रणाली
 * @indio_dev:		Device काष्ठाure filled by the device driver
 **/
#घोषणा iio_device_रेजिस्टर(indio_dev) \
	__iio_device_रेजिस्टर((indio_dev), THIS_MODULE)
पूर्णांक __iio_device_रेजिस्टर(काष्ठा iio_dev *indio_dev, काष्ठा module *this_mod);
व्योम iio_device_unरेजिस्टर(काष्ठा iio_dev *indio_dev);
/**
 * devm_iio_device_रेजिस्टर - Resource-managed iio_device_रेजिस्टर()
 * @dev:	Device to allocate iio_dev क्रम
 * @indio_dev:	Device काष्ठाure filled by the device driver
 *
 * Managed iio_device_रेजिस्टर.  The IIO device रेजिस्टरed with this
 * function is स्वतःmatically unरेजिस्टरed on driver detach. This function
 * calls iio_device_रेजिस्टर() पूर्णांकernally. Refer to that function क्रम more
 * inक्रमmation.
 *
 * RETURNS:
 * 0 on success, negative error number on failure.
 */
#घोषणा devm_iio_device_रेजिस्टर(dev, indio_dev) \
	__devm_iio_device_रेजिस्टर((dev), (indio_dev), THIS_MODULE)
पूर्णांक __devm_iio_device_रेजिस्टर(काष्ठा device *dev, काष्ठा iio_dev *indio_dev,
			       काष्ठा module *this_mod);
पूर्णांक iio_push_event(काष्ठा iio_dev *indio_dev, u64 ev_code, s64 बारtamp);
पूर्णांक iio_device_claim_direct_mode(काष्ठा iio_dev *indio_dev);
व्योम iio_device_release_direct_mode(काष्ठा iio_dev *indio_dev);

बाह्य काष्ठा bus_type iio_bus_type;

/**
 * iio_device_put() - reference counted deallocation of काष्ठा device
 * @indio_dev: IIO device काष्ठाure containing the device
 **/
अटल अंतरभूत व्योम iio_device_put(काष्ठा iio_dev *indio_dev)
अणु
	अगर (indio_dev)
		put_device(&indio_dev->dev);
पूर्ण

/**
 * iio_device_get_घड़ी() - Retrieve current बारtamping घड़ी क्रम the device
 * @indio_dev: IIO device काष्ठाure containing the device
 */
अटल अंतरभूत घड़ीid_t iio_device_get_घड़ी(स्थिर काष्ठा iio_dev *indio_dev)
अणु
	वापस indio_dev->घड़ी_id;
पूर्ण

पूर्णांक iio_device_set_घड़ी(काष्ठा iio_dev *indio_dev, घड़ीid_t घड़ी_id);

/**
 * dev_to_iio_dev() - Get IIO device काष्ठा from a device काष्ठा
 * @dev: 		The device embedded in the IIO device
 *
 * Note: The device must be a IIO device, otherwise the result is undefined.
 */
अटल अंतरभूत काष्ठा iio_dev *dev_to_iio_dev(काष्ठा device *dev)
अणु
	वापस container_of(dev, काष्ठा iio_dev, dev);
पूर्ण

/**
 * iio_device_get() - increment reference count क्रम the device
 * @indio_dev: 		IIO device काष्ठाure
 *
 * Returns: The passed IIO device
 **/
अटल अंतरभूत काष्ठा iio_dev *iio_device_get(काष्ठा iio_dev *indio_dev)
अणु
	वापस indio_dev ? dev_to_iio_dev(get_device(&indio_dev->dev)) : शून्य;
पूर्ण

/**
 * iio_device_set_parent() - assign parent device to the IIO device object
 * @indio_dev: 		IIO device काष्ठाure
 * @parent:		reference to parent device object
 *
 * This utility must be called between IIO device allocation
 * (via devm_iio_device_alloc()) & IIO device registration
 * (via iio_device_रेजिस्टर() and devm_iio_device_रेजिस्टर())).
 * By शेष, the device allocation will also assign a parent device to
 * the IIO device object. In हालs where devm_iio_device_alloc() is used,
 * someबार the parent device must be dअगरferent than the device used to
 * manage the allocation.
 * In that हाल, this helper should be used to change the parent, hence the
 * requirement to call this between allocation & registration.
 **/
अटल अंतरभूत व्योम iio_device_set_parent(काष्ठा iio_dev *indio_dev,
					 काष्ठा device *parent)
अणु
	indio_dev->dev.parent = parent;
पूर्ण

/**
 * iio_device_set_drvdata() - Set device driver data
 * @indio_dev: IIO device काष्ठाure
 * @data: Driver specअगरic data
 *
 * Allows to attach an arbitrary poपूर्णांकer to an IIO device, which can later be
 * retrieved by iio_device_get_drvdata().
 */
अटल अंतरभूत व्योम iio_device_set_drvdata(काष्ठा iio_dev *indio_dev, व्योम *data)
अणु
	dev_set_drvdata(&indio_dev->dev, data);
पूर्ण

/**
 * iio_device_get_drvdata() - Get device driver data
 * @indio_dev: IIO device काष्ठाure
 *
 * Returns the data previously set with iio_device_set_drvdata()
 */
अटल अंतरभूत व्योम *iio_device_get_drvdata(स्थिर काष्ठा iio_dev *indio_dev)
अणु
	वापस dev_get_drvdata(&indio_dev->dev);
पूर्ण

/* Can we make this smaller? */
#घोषणा IIO_ALIGN L1_CACHE_BYTES
काष्ठा iio_dev *iio_device_alloc(काष्ठा device *parent, पूर्णांक माप_priv);

/* The inक्रमmation at the वापसed address is guaranteed to be cacheline aligned */
अटल अंतरभूत व्योम *iio_priv(स्थिर काष्ठा iio_dev *indio_dev)
अणु
	वापस indio_dev->priv;
पूर्ण

व्योम iio_device_मुक्त(काष्ठा iio_dev *indio_dev);
काष्ठा iio_dev *devm_iio_device_alloc(काष्ठा device *parent, पूर्णांक माप_priv);
__म_लिखो(2, 3)
काष्ठा iio_trigger *devm_iio_trigger_alloc(काष्ठा device *parent,
					   स्थिर अक्षर *fmt, ...);
/**
 * iio_buffer_enabled() - helper function to test अगर the buffer is enabled
 * @indio_dev:		IIO device काष्ठाure क्रम device
 **/
अटल अंतरभूत bool iio_buffer_enabled(काष्ठा iio_dev *indio_dev)
अणु
	वापस indio_dev->currenपंचांगode
		& (INDIO_BUFFER_TRIGGERED | INDIO_BUFFER_HARDWARE |
		   INDIO_BUFFER_SOFTWARE);
पूर्ण

/**
 * iio_get_debugfs_dentry() - helper function to get the debugfs_dentry
 * @indio_dev:		IIO device काष्ठाure क्रम device
 **/
#अगर defined(CONFIG_DEBUG_FS)
काष्ठा dentry *iio_get_debugfs_dentry(काष्ठा iio_dev *indio_dev);
#अन्यथा
अटल अंतरभूत काष्ठा dentry *iio_get_debugfs_dentry(काष्ठा iio_dev *indio_dev)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

sमाप_प्रकार iio_क्रमmat_value(अक्षर *buf, अचिन्हित पूर्णांक type, पूर्णांक size, पूर्णांक *vals);

पूर्णांक iio_str_to_fixpoपूर्णांक(स्थिर अक्षर *str, पूर्णांक fract_mult, पूर्णांक *पूर्णांकeger,
	पूर्णांक *fract);

/**
 * IIO_DEGREE_TO_RAD() - Convert degree to rad
 * @deg: A value in degree
 *
 * Returns the given value converted from degree to rad
 */
#घोषणा IIO_DEGREE_TO_RAD(deg) (((deg) * 314159ULL + 9000000ULL) / 18000000ULL)

/**
 * IIO_RAD_TO_DEGREE() - Convert rad to degree
 * @rad: A value in rad
 *
 * Returns the given value converted from rad to degree
 */
#घोषणा IIO_RAD_TO_DEGREE(rad) \
	(((rad) * 18000000ULL + 314159ULL / 2) / 314159ULL)

/**
 * IIO_G_TO_M_S_2() - Convert g to meter / second**2
 * @g: A value in g
 *
 * Returns the given value converted from g to meter / second**2
 */
#घोषणा IIO_G_TO_M_S_2(g) ((g) * 980665ULL / 100000ULL)

/**
 * IIO_M_S_2_TO_G() - Convert meter / second**2 to g
 * @ms2: A value in meter / second**2
 *
 * Returns the given value converted from meter / second**2 to g
 */
#घोषणा IIO_M_S_2_TO_G(ms2) (((ms2) * 100000ULL + 980665ULL / 2) / 980665ULL)

#पूर्ण_अगर /* _INDUSTRIAL_IO_H_ */
