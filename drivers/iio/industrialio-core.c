<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* The industrial I/O core
 *
 * Copyright (c) 2008 Jonathan Cameron
 *
 * Based on elements of hwmon and input subप्रणालीs.
 */

#घोषणा pr_fmt(fmt) "iio-core: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/idr.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/err.h>
#समावेश <linux/device.h>
#समावेश <linux/fs.h>
#समावेश <linux/poll.h>
#समावेश <linux/property.h>
#समावेश <linux/sched.h>
#समावेश <linux/रुको.h>
#समावेश <linux/cdev.h>
#समावेश <linux/slab.h>
#समावेश <linux/anon_inodes.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/mutex.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/iio-opaque.h>
#समावेश "iio_core.h"
#समावेश "iio_core_trigger.h"
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/events.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/buffer_impl.h>

/* IDA to assign each रेजिस्टरed device a unique id */
अटल DEFINE_IDA(iio_ida);

अटल dev_t iio_devt;

#घोषणा IIO_DEV_MAX 256
काष्ठा bus_type iio_bus_type = अणु
	.name = "iio",
पूर्ण;
EXPORT_SYMBOL(iio_bus_type);

अटल काष्ठा dentry *iio_debugfs_dentry;

अटल स्थिर अक्षर * स्थिर iio_direction[] = अणु
	[0] = "in",
	[1] = "out",
पूर्ण;

अटल स्थिर अक्षर * स्थिर iio_chan_type_name_spec[] = अणु
	[IIO_VOLTAGE] = "voltage",
	[IIO_CURRENT] = "current",
	[IIO_POWER] = "power",
	[IIO_ACCEL] = "accel",
	[IIO_ANGL_VEL] = "anglvel",
	[IIO_MAGN] = "magn",
	[IIO_LIGHT] = "illuminance",
	[IIO_INTENSITY] = "intensity",
	[IIO_PROXIMITY] = "proximity",
	[IIO_TEMP] = "temp",
	[IIO_INCLI] = "incli",
	[IIO_ROT] = "rot",
	[IIO_ANGL] = "angl",
	[IIO_TIMESTAMP] = "timestamp",
	[IIO_CAPACITANCE] = "capacitance",
	[IIO_ALTVOLTAGE] = "altvoltage",
	[IIO_CCT] = "cct",
	[IIO_PRESSURE] = "pressure",
	[IIO_HUMIDITYRELATIVE] = "humidityrelative",
	[IIO_ACTIVITY] = "activity",
	[IIO_STEPS] = "steps",
	[IIO_ENERGY] = "energy",
	[IIO_DISTANCE] = "distance",
	[IIO_VELOCITY] = "velocity",
	[IIO_CONCENTRATION] = "concentration",
	[IIO_RESISTANCE] = "resistance",
	[IIO_PH] = "ph",
	[IIO_UVINDEX] = "uvindex",
	[IIO_ELECTRICALCONDUCTIVITY] = "electricalconductivity",
	[IIO_COUNT] = "count",
	[IIO_INDEX] = "index",
	[IIO_GRAVITY]  = "gravity",
	[IIO_POSITIONRELATIVE]  = "positionrelative",
	[IIO_PHASE] = "phase",
	[IIO_MASSCONCENTRATION] = "massconcentration",
पूर्ण;

अटल स्थिर अक्षर * स्थिर iio_modअगरier_names[] = अणु
	[IIO_MOD_X] = "x",
	[IIO_MOD_Y] = "y",
	[IIO_MOD_Z] = "z",
	[IIO_MOD_X_AND_Y] = "x&y",
	[IIO_MOD_X_AND_Z] = "x&z",
	[IIO_MOD_Y_AND_Z] = "y&z",
	[IIO_MOD_X_AND_Y_AND_Z] = "x&y&z",
	[IIO_MOD_X_OR_Y] = "x|y",
	[IIO_MOD_X_OR_Z] = "x|z",
	[IIO_MOD_Y_OR_Z] = "y|z",
	[IIO_MOD_X_OR_Y_OR_Z] = "x|y|z",
	[IIO_MOD_ROOT_SUM_SQUARED_X_Y] = "वर्ग_मूल(x^2+y^2)",
	[IIO_MOD_SUM_SQUARED_X_Y_Z] = "x^2+y^2+z^2",
	[IIO_MOD_LIGHT_BOTH] = "both",
	[IIO_MOD_LIGHT_IR] = "ir",
	[IIO_MOD_LIGHT_CLEAR] = "clear",
	[IIO_MOD_LIGHT_RED] = "red",
	[IIO_MOD_LIGHT_GREEN] = "green",
	[IIO_MOD_LIGHT_BLUE] = "blue",
	[IIO_MOD_LIGHT_UV] = "uv",
	[IIO_MOD_LIGHT_DUV] = "duv",
	[IIO_MOD_QUATERNION] = "quaternion",
	[IIO_MOD_TEMP_AMBIENT] = "ambient",
	[IIO_MOD_TEMP_OBJECT] = "object",
	[IIO_MOD_NORTH_MAGN] = "from_north_magnetic",
	[IIO_MOD_NORTH_TRUE] = "from_north_true",
	[IIO_MOD_NORTH_MAGN_TILT_COMP] = "from_north_magnetic_tilt_comp",
	[IIO_MOD_NORTH_TRUE_TILT_COMP] = "from_north_true_tilt_comp",
	[IIO_MOD_RUNNING] = "running",
	[IIO_MOD_JOGGING] = "jogging",
	[IIO_MOD_WALKING] = "walking",
	[IIO_MOD_STILL] = "still",
	[IIO_MOD_ROOT_SUM_SQUARED_X_Y_Z] = "वर्ग_मूल(x^2+y^2+z^2)",
	[IIO_MOD_I] = "i",
	[IIO_MOD_Q] = "q",
	[IIO_MOD_CO2] = "co2",
	[IIO_MOD_VOC] = "voc",
	[IIO_MOD_PM1] = "pm1",
	[IIO_MOD_PM2P5] = "pm2p5",
	[IIO_MOD_PM4] = "pm4",
	[IIO_MOD_PM10] = "pm10",
	[IIO_MOD_ETHANOL] = "ethanol",
	[IIO_MOD_H2] = "h2",
	[IIO_MOD_O2] = "o2",
पूर्ण;

/* relies on pairs of these shared then separate */
अटल स्थिर अक्षर * स्थिर iio_chan_info_postfix[] = अणु
	[IIO_CHAN_INFO_RAW] = "raw",
	[IIO_CHAN_INFO_PROCESSED] = "input",
	[IIO_CHAN_INFO_SCALE] = "scale",
	[IIO_CHAN_INFO_OFFSET] = "offset",
	[IIO_CHAN_INFO_CALIBSCALE] = "calibscale",
	[IIO_CHAN_INFO_CALIBBIAS] = "calibbias",
	[IIO_CHAN_INFO_PEAK] = "peak_raw",
	[IIO_CHAN_INFO_PEAK_SCALE] = "peak_scale",
	[IIO_CHAN_INFO_QUADRATURE_CORRECTION_RAW] = "quadrature_correction_raw",
	[IIO_CHAN_INFO_AVERAGE_RAW] = "mean_raw",
	[IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY]
	= "filter_low_pass_3db_frequency",
	[IIO_CHAN_INFO_HIGH_PASS_FILTER_3DB_FREQUENCY]
	= "filter_high_pass_3db_frequency",
	[IIO_CHAN_INFO_SAMP_FREQ] = "sampling_frequency",
	[IIO_CHAN_INFO_FREQUENCY] = "frequency",
	[IIO_CHAN_INFO_PHASE] = "phase",
	[IIO_CHAN_INFO_HARDWAREGAIN] = "hardwaregain",
	[IIO_CHAN_INFO_HYSTERESIS] = "hysteresis",
	[IIO_CHAN_INFO_HYSTERESIS_RELATIVE] = "hysteresis_relative",
	[IIO_CHAN_INFO_INT_TIME] = "integration_time",
	[IIO_CHAN_INFO_ENABLE] = "en",
	[IIO_CHAN_INFO_CALIBHEIGHT] = "calibheight",
	[IIO_CHAN_INFO_CALIBWEIGHT] = "calibweight",
	[IIO_CHAN_INFO_DEBOUNCE_COUNT] = "debounce_count",
	[IIO_CHAN_INFO_DEBOUNCE_TIME] = "debounce_time",
	[IIO_CHAN_INFO_CALIBEMISSIVITY] = "calibemissivity",
	[IIO_CHAN_INFO_OVERSAMPLING_RATIO] = "oversampling_ratio",
	[IIO_CHAN_INFO_THERMOCOUPLE_TYPE] = "thermocouple_type",
	[IIO_CHAN_INFO_CALIBAMBIENT] = "calibambient",
पूर्ण;

/**
 * iio_sysfs_match_string_with_gaps - matches given string in an array with gaps
 * @array: array of strings
 * @n: number of strings in the array
 * @str: string to match with
 *
 * Returns index of @str in the @array or -EINVAL, similar to match_string().
 * Uses sysfs_streq instead of म_भेद क्रम matching.
 *
 * This routine will look क्रम a string in an array of strings.
 * The search will जारी until the element is found or the n-th element
 * is reached, regardless of any शून्य elements in the array.
 */
अटल पूर्णांक iio_sysfs_match_string_with_gaps(स्थिर अक्षर * स्थिर *array, माप_प्रकार n,
					    स्थिर अक्षर *str)
अणु
	स्थिर अक्षर *item;
	पूर्णांक index;

	क्रम (index = 0; index < n; index++) अणु
		item = array[index];
		अगर (!item)
			जारी;
		अगर (sysfs_streq(item, str))
			वापस index;
	पूर्ण

	वापस -EINVAL;
पूर्ण

#अगर defined(CONFIG_DEBUG_FS)
/*
 * There's also a CONFIG_DEBUG_FS guard in include/linux/iio/iपन.स क्रम
 * iio_get_debugfs_dentry() to make it अंतरभूत अगर CONFIG_DEBUG_FS is undefined
 */
काष्ठा dentry *iio_get_debugfs_dentry(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	वापस iio_dev_opaque->debugfs_dentry;
पूर्ण
EXPORT_SYMBOL_GPL(iio_get_debugfs_dentry);
#पूर्ण_अगर

/**
 * iio_find_channel_from_si() - get channel from its scan index
 * @indio_dev:		device
 * @si:			scan index to match
 */
स्थिर काष्ठा iio_chan_spec
*iio_find_channel_from_si(काष्ठा iio_dev *indio_dev, पूर्णांक si)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < indio_dev->num_channels; i++)
		अगर (indio_dev->channels[i].scan_index == si)
			वापस &indio_dev->channels[i];
	वापस शून्य;
पूर्ण

/* This turns up an awful lot */
sमाप_प्रकार iio_पढ़ो_स्थिर_attr(काष्ठा device *dev,
			    काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%s\n", to_iio_स्थिर_attr(attr)->string);
पूर्ण
EXPORT_SYMBOL(iio_पढ़ो_स्थिर_attr);

/**
 * iio_device_set_घड़ी() - Set current बारtamping घड़ी क्रम the device
 * @indio_dev: IIO device काष्ठाure containing the device
 * @घड़ी_id: बारtamping घड़ी posix identअगरier to set.
 */
पूर्णांक iio_device_set_घड़ी(काष्ठा iio_dev *indio_dev, घड़ीid_t घड़ी_id)
अणु
	पूर्णांक ret;
	काष्ठा iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	स्थिर काष्ठा iio_event_पूर्णांकerface *ev_पूर्णांक = iio_dev_opaque->event_पूर्णांकerface;

	ret = mutex_lock_पूर्णांकerruptible(&indio_dev->mlock);
	अगर (ret)
		वापस ret;
	अगर ((ev_पूर्णांक && iio_event_enabled(ev_पूर्णांक)) ||
	    iio_buffer_enabled(indio_dev)) अणु
		mutex_unlock(&indio_dev->mlock);
		वापस -EBUSY;
	पूर्ण
	indio_dev->घड़ी_id = घड़ी_id;
	mutex_unlock(&indio_dev->mlock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(iio_device_set_घड़ी);

/**
 * iio_get_समय_ns() - utility function to get a समय stamp क्रम events etc
 * @indio_dev: device
 */
s64 iio_get_समय_ns(स्थिर काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा बारpec64 tp;

	चयन (iio_device_get_घड़ी(indio_dev)) अणु
	हाल CLOCK_REALTIME:
		वापस kसमय_get_real_ns();
	हाल CLOCK_MONOTONIC:
		वापस kसमय_get_ns();
	हाल CLOCK_MONOTONIC_RAW:
		वापस kसमय_get_raw_ns();
	हाल CLOCK_REALTIME_COARSE:
		वापस kसमय_प्रकारo_ns(kसमय_get_coarse_real());
	हाल CLOCK_MONOTONIC_COARSE:
		kसमय_get_coarse_ts64(&tp);
		वापस बारpec64_to_ns(&tp);
	हाल CLOCK_BOOTTIME:
		वापस kसमय_get_bootसमय_ns();
	हाल CLOCK_TAI:
		वापस kसमय_get_घड़ीtai_ns();
	शेष:
		BUG();
	पूर्ण
पूर्ण
EXPORT_SYMBOL(iio_get_समय_ns);

/**
 * iio_get_समय_res() - utility function to get समय stamp घड़ी resolution in
 *                      nano seconds.
 * @indio_dev: device
 */
अचिन्हित पूर्णांक iio_get_समय_res(स्थिर काष्ठा iio_dev *indio_dev)
अणु
	चयन (iio_device_get_घड़ी(indio_dev)) अणु
	हाल CLOCK_REALTIME:
	हाल CLOCK_MONOTONIC:
	हाल CLOCK_MONOTONIC_RAW:
	हाल CLOCK_BOOTTIME:
	हाल CLOCK_TAI:
		वापस hrसमयr_resolution;
	हाल CLOCK_REALTIME_COARSE:
	हाल CLOCK_MONOTONIC_COARSE:
		वापस LOW_RES_NSEC;
	शेष:
		BUG();
	पूर्ण
पूर्ण
EXPORT_SYMBOL(iio_get_समय_res);

अटल पूर्णांक __init iio_init(व्योम)
अणु
	पूर्णांक ret;

	/* Register sysfs bus */
	ret  = bus_रेजिस्टर(&iio_bus_type);
	अगर (ret < 0) अणु
		pr_err("could not register bus type\n");
		जाओ error_nothing;
	पूर्ण

	ret = alloc_chrdev_region(&iio_devt, 0, IIO_DEV_MAX, "iio");
	अगर (ret < 0) अणु
		pr_err("failed to allocate char dev region\n");
		जाओ error_unरेजिस्टर_bus_type;
	पूर्ण

	iio_debugfs_dentry = debugfs_create_dir("iio", शून्य);

	वापस 0;

error_unरेजिस्टर_bus_type:
	bus_unरेजिस्टर(&iio_bus_type);
error_nothing:
	वापस ret;
पूर्ण

अटल व्योम __निकास iio_निकास(व्योम)
अणु
	अगर (iio_devt)
		unरेजिस्टर_chrdev_region(iio_devt, IIO_DEV_MAX);
	bus_unरेजिस्टर(&iio_bus_type);
	debugfs_हटाओ(iio_debugfs_dentry);
पूर्ण

#अगर defined(CONFIG_DEBUG_FS)
अटल sमाप_प्रकार iio_debugfs_पढ़ो_reg(काष्ठा file *file, अक्षर __user *userbuf,
			      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iio_dev *indio_dev = file->निजी_data;
	काष्ठा iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	अचिन्हित val = 0;
	पूर्णांक ret;

	अगर (*ppos > 0)
		वापस simple_पढ़ो_from_buffer(userbuf, count, ppos,
					       iio_dev_opaque->पढ़ो_buf,
					       iio_dev_opaque->पढ़ो_buf_len);

	ret = indio_dev->info->debugfs_reg_access(indio_dev,
						  iio_dev_opaque->cached_reg_addr,
						  0, &val);
	अगर (ret) अणु
		dev_err(indio_dev->dev.parent, "%s: read failed\n", __func__);
		वापस ret;
	पूर्ण

	iio_dev_opaque->पढ़ो_buf_len = snम_लिखो(iio_dev_opaque->पढ़ो_buf,
					      माप(iio_dev_opaque->पढ़ो_buf),
					      "0x%X\n", val);

	वापस simple_पढ़ो_from_buffer(userbuf, count, ppos,
				       iio_dev_opaque->पढ़ो_buf,
				       iio_dev_opaque->पढ़ो_buf_len);
पूर्ण

अटल sमाप_प्रकार iio_debugfs_ग_लिखो_reg(काष्ठा file *file,
		     स्थिर अक्षर __user *userbuf, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iio_dev *indio_dev = file->निजी_data;
	काष्ठा iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	अचिन्हित reg, val;
	अक्षर buf[80];
	पूर्णांक ret;

	count = min_t(माप_प्रकार, count, (माप(buf)-1));
	अगर (copy_from_user(buf, userbuf, count))
		वापस -EFAULT;

	buf[count] = 0;

	ret = माला_पूछो(buf, "%i %i", &reg, &val);

	चयन (ret) अणु
	हाल 1:
		iio_dev_opaque->cached_reg_addr = reg;
		अवरोध;
	हाल 2:
		iio_dev_opaque->cached_reg_addr = reg;
		ret = indio_dev->info->debugfs_reg_access(indio_dev, reg,
							  val, शून्य);
		अगर (ret) अणु
			dev_err(indio_dev->dev.parent, "%s: write failed\n",
				__func__);
			वापस ret;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations iio_debugfs_reg_fops = अणु
	.खोलो = simple_खोलो,
	.पढ़ो = iio_debugfs_पढ़ो_reg,
	.ग_लिखो = iio_debugfs_ग_लिखो_reg,
पूर्ण;

अटल व्योम iio_device_unरेजिस्टर_debugfs(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	debugfs_हटाओ_recursive(iio_dev_opaque->debugfs_dentry);
पूर्ण

अटल व्योम iio_device_रेजिस्टर_debugfs(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा iio_dev_opaque *iio_dev_opaque;

	अगर (indio_dev->info->debugfs_reg_access == शून्य)
		वापस;

	अगर (!iio_debugfs_dentry)
		वापस;

	iio_dev_opaque = to_iio_dev_opaque(indio_dev);

	iio_dev_opaque->debugfs_dentry =
		debugfs_create_dir(dev_name(&indio_dev->dev),
				   iio_debugfs_dentry);

	debugfs_create_file("direct_reg_access", 0644,
			    iio_dev_opaque->debugfs_dentry, indio_dev,
			    &iio_debugfs_reg_fops);
पूर्ण
#अन्यथा
अटल व्योम iio_device_रेजिस्टर_debugfs(काष्ठा iio_dev *indio_dev)
अणु
पूर्ण

अटल व्योम iio_device_unरेजिस्टर_debugfs(काष्ठा iio_dev *indio_dev)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_DEBUG_FS */

अटल sमाप_प्रकार iio_पढ़ो_channel_ext_info(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	स्थिर काष्ठा iio_chan_spec_ext_info *ext_info;

	ext_info = &this_attr->c->ext_info[this_attr->address];

	वापस ext_info->पढ़ो(indio_dev, ext_info->निजी, this_attr->c, buf);
पूर्ण

अटल sमाप_प्रकार iio_ग_लिखो_channel_ext_info(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf,
					 माप_प्रकार len)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	स्थिर काष्ठा iio_chan_spec_ext_info *ext_info;

	ext_info = &this_attr->c->ext_info[this_attr->address];

	वापस ext_info->ग_लिखो(indio_dev, ext_info->निजी,
			       this_attr->c, buf, len);
पूर्ण

sमाप_प्रकार iio_क्रमागत_available_पढ़ो(काष्ठा iio_dev *indio_dev,
	uपूर्णांकptr_t priv, स्थिर काष्ठा iio_chan_spec *chan, अक्षर *buf)
अणु
	स्थिर काष्ठा iio_क्रमागत *e = (स्थिर काष्ठा iio_क्रमागत *)priv;
	अचिन्हित पूर्णांक i;
	माप_प्रकार len = 0;

	अगर (!e->num_items)
		वापस 0;

	क्रम (i = 0; i < e->num_items; ++i) अणु
		अगर (!e->items[i])
			जारी;
		len += sysfs_emit_at(buf, len, "%s ", e->items[i]);
	पूर्ण

	/* replace last space with a newline */
	buf[len - 1] = '\n';

	वापस len;
पूर्ण
EXPORT_SYMBOL_GPL(iio_क्रमागत_available_पढ़ो);

sमाप_प्रकार iio_क्रमागत_पढ़ो(काष्ठा iio_dev *indio_dev,
	uपूर्णांकptr_t priv, स्थिर काष्ठा iio_chan_spec *chan, अक्षर *buf)
अणु
	स्थिर काष्ठा iio_क्रमागत *e = (स्थिर काष्ठा iio_क्रमागत *)priv;
	पूर्णांक i;

	अगर (!e->get)
		वापस -EINVAL;

	i = e->get(indio_dev, chan);
	अगर (i < 0)
		वापस i;
	अन्यथा अगर (i >= e->num_items || !e->items[i])
		वापस -EINVAL;

	वापस sysfs_emit(buf, "%s\n", e->items[i]);
पूर्ण
EXPORT_SYMBOL_GPL(iio_क्रमागत_पढ़ो);

sमाप_प्रकार iio_क्रमागत_ग_लिखो(काष्ठा iio_dev *indio_dev,
	uपूर्णांकptr_t priv, स्थिर काष्ठा iio_chan_spec *chan, स्थिर अक्षर *buf,
	माप_प्रकार len)
अणु
	स्थिर काष्ठा iio_क्रमागत *e = (स्थिर काष्ठा iio_क्रमागत *)priv;
	पूर्णांक ret;

	अगर (!e->set)
		वापस -EINVAL;

	ret = iio_sysfs_match_string_with_gaps(e->items, e->num_items, buf);
	अगर (ret < 0)
		वापस ret;

	ret = e->set(indio_dev, chan, ret);
	वापस ret ? ret : len;
पूर्ण
EXPORT_SYMBOL_GPL(iio_क्रमागत_ग_लिखो);

अटल स्थिर काष्ठा iio_mount_matrix iio_mount_idmatrix = अणु
	.rotation = अणु
		"1", "0", "0",
		"0", "1", "0",
		"0", "0", "1"
	पूर्ण
पूर्ण;

अटल पूर्णांक iio_setup_mount_idmatrix(स्थिर काष्ठा device *dev,
				    काष्ठा iio_mount_matrix *matrix)
अणु
	*matrix = iio_mount_idmatrix;
	dev_info(dev, "mounting matrix not found: using identity...\n");
	वापस 0;
पूर्ण

sमाप_प्रकार iio_show_mount_matrix(काष्ठा iio_dev *indio_dev, uपूर्णांकptr_t priv,
			      स्थिर काष्ठा iio_chan_spec *chan, अक्षर *buf)
अणु
	स्थिर काष्ठा iio_mount_matrix *mtx = ((iio_get_mount_matrix_t *)
					      priv)(indio_dev, chan);

	अगर (IS_ERR(mtx))
		वापस PTR_ERR(mtx);

	अगर (!mtx)
		mtx = &iio_mount_idmatrix;

	वापस sysfs_emit(buf, "%s, %s, %s; %s, %s, %s; %s, %s, %s\n",
			  mtx->rotation[0], mtx->rotation[1], mtx->rotation[2],
			  mtx->rotation[3], mtx->rotation[4], mtx->rotation[5],
			  mtx->rotation[6], mtx->rotation[7], mtx->rotation[8]);
पूर्ण
EXPORT_SYMBOL_GPL(iio_show_mount_matrix);

/**
 * iio_पढ़ो_mount_matrix() - retrieve iio device mounting matrix from
 *                           device "mount-matrix" property
 * @dev:	device the mounting matrix property is asचिन्हित to
 * @propname:	device specअगरic mounting matrix property name
 * @matrix:	where to store retrieved matrix
 *
 * If device is asचिन्हित no mounting matrix property, a शेष 3x3 identity
 * matrix will be filled in.
 *
 * Return: 0 अगर success, or a negative error code on failure.
 */
पूर्णांक iio_पढ़ो_mount_matrix(काष्ठा device *dev, स्थिर अक्षर *propname,
			  काष्ठा iio_mount_matrix *matrix)
अणु
	माप_प्रकार len = ARRAY_SIZE(iio_mount_idmatrix.rotation);
	पूर्णांक err;

	err = device_property_पढ़ो_string_array(dev, propname,
						matrix->rotation, len);
	अगर (err == len)
		वापस 0;

	अगर (err >= 0)
		/* Invalid number of matrix entries. */
		वापस -EINVAL;

	अगर (err != -EINVAL)
		/* Invalid matrix declaration क्रमmat. */
		वापस err;

	/* Matrix was not declared at all: fallback to identity. */
	वापस iio_setup_mount_idmatrix(dev, matrix);
पूर्ण
EXPORT_SYMBOL(iio_पढ़ो_mount_matrix);

अटल sमाप_प्रकार __iio_क्रमmat_value(अक्षर *buf, माप_प्रकार offset, अचिन्हित पूर्णांक type,
				  पूर्णांक size, स्थिर पूर्णांक *vals)
अणु
	पूर्णांक पंचांगp0, पंचांगp1;
	s64 पंचांगp2;
	bool scale_db = false;

	चयन (type) अणु
	हाल IIO_VAL_INT:
		वापस sysfs_emit_at(buf, offset, "%d", vals[0]);
	हाल IIO_VAL_INT_PLUS_MICRO_DB:
		scale_db = true;
		fallthrough;
	हाल IIO_VAL_INT_PLUS_MICRO:
		अगर (vals[1] < 0)
			वापस sysfs_emit_at(buf, offset, "-%d.%06u%s",
					     असल(vals[0]), -vals[1],
					     scale_db ? " dB" : "");
		अन्यथा
			वापस sysfs_emit_at(buf, offset, "%d.%06u%s", vals[0],
					     vals[1], scale_db ? " dB" : "");
	हाल IIO_VAL_INT_PLUS_न_अंकO:
		अगर (vals[1] < 0)
			वापस sysfs_emit_at(buf, offset, "-%d.%09u",
					     असल(vals[0]), -vals[1]);
		अन्यथा
			वापस sysfs_emit_at(buf, offset, "%d.%09u", vals[0],
					     vals[1]);
	हाल IIO_VAL_FRACTIONAL:
		पंचांगp2 = भाग_s64((s64)vals[0] * 1000000000LL, vals[1]);
		पंचांगp1 = vals[1];
		पंचांगp0 = (पूर्णांक)भाग_s64_rem(पंचांगp2, 1000000000, &पंचांगp1);
		अगर ((पंचांगp2 < 0) && (पंचांगp0 == 0))
			वापस sysfs_emit_at(buf, offset, "-0.%09u", असल(पंचांगp1));
		अन्यथा
			वापस sysfs_emit_at(buf, offset, "%d.%09u", पंचांगp0,
					     असल(पंचांगp1));
	हाल IIO_VAL_FRACTIONAL_LOG2:
		पंचांगp2 = shअगरt_right((s64)vals[0] * 1000000000LL, vals[1]);
		पंचांगp0 = (पूर्णांक)भाग_s64_rem(पंचांगp2, 1000000000LL, &पंचांगp1);
		अगर (पंचांगp0 == 0 && पंचांगp2 < 0)
			वापस sysfs_emit_at(buf, offset, "-0.%09u", असल(पंचांगp1));
		अन्यथा
			वापस sysfs_emit_at(buf, offset, "%d.%09u", पंचांगp0,
					     असल(पंचांगp1));
	हाल IIO_VAL_INT_MULTIPLE:
	अणु
		पूर्णांक i;
		पूर्णांक l = 0;

		क्रम (i = 0; i < size; ++i)
			l += sysfs_emit_at(buf, offset + l, "%d ", vals[i]);
		वापस l;
	पूर्ण
	हाल IIO_VAL_CHAR:
		वापस sysfs_emit_at(buf, offset, "%c", (अक्षर)vals[0]);
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

/**
 * iio_क्रमmat_value() - Formats a IIO value पूर्णांकo its string representation
 * @buf:	The buffer to which the क्रमmatted value माला_लो written
 *		which is assumed to be big enough (i.e. PAGE_SIZE).
 * @type:	One of the IIO_VAL_* स्थिरants. This decides how the val
 *		and val2 parameters are क्रमmatted.
 * @size:	Number of IIO value entries contained in vals
 * @vals:	Poपूर्णांकer to the values, exact meaning depends on the
 *		type parameter.
 *
 * Return: 0 by शेष, a negative number on failure or the
 *	   total number of अक्षरacters written क्रम a type that beदीर्घs
 *	   to the IIO_VAL_* स्थिरant.
 */
sमाप_प्रकार iio_क्रमmat_value(अक्षर *buf, अचिन्हित पूर्णांक type, पूर्णांक size, पूर्णांक *vals)
अणु
	sमाप_प्रकार len;

	len = __iio_क्रमmat_value(buf, 0, type, size, vals);
	अगर (len >= PAGE_SIZE - 1)
		वापस -EFBIG;

	वापस len + sysfs_emit_at(buf, len, "\n");
पूर्ण
EXPORT_SYMBOL_GPL(iio_क्रमmat_value);

अटल sमाप_प्रकार iio_पढ़ो_channel_label(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा iio_dev_attr *this_attr = to_iio_dev_attr(attr);

	अगर (!indio_dev->info->पढ़ो_label)
		वापस -EINVAL;

	वापस indio_dev->info->पढ़ो_label(indio_dev, this_attr->c, buf);
पूर्ण

अटल sमाप_प्रकार iio_पढ़ो_channel_info(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	पूर्णांक vals[INDIO_MAX_RAW_ELEMENTS];
	पूर्णांक ret;
	पूर्णांक val_len = 2;

	अगर (indio_dev->info->पढ़ो_raw_multi)
		ret = indio_dev->info->पढ़ो_raw_multi(indio_dev, this_attr->c,
							INDIO_MAX_RAW_ELEMENTS,
							vals, &val_len,
							this_attr->address);
	अन्यथा
		ret = indio_dev->info->पढ़ो_raw(indio_dev, this_attr->c,
				    &vals[0], &vals[1], this_attr->address);

	अगर (ret < 0)
		वापस ret;

	वापस iio_क्रमmat_value(buf, ret, val_len, vals);
पूर्ण

अटल sमाप_प्रकार iio_क्रमmat_list(अक्षर *buf, स्थिर पूर्णांक *vals, पूर्णांक type, पूर्णांक length,
			       स्थिर अक्षर *prefix, स्थिर अक्षर *suffix)
अणु
	sमाप_प्रकार len;
	पूर्णांक stride;
	पूर्णांक i;

	चयन (type) अणु
	हाल IIO_VAL_INT:
		stride = 1;
		अवरोध;
	शेष:
		stride = 2;
		अवरोध;
	पूर्ण

	len = sysfs_emit(buf, prefix);

	क्रम (i = 0; i <= length - stride; i += stride) अणु
		अगर (i != 0) अणु
			len += sysfs_emit_at(buf, len, " ");
			अगर (len >= PAGE_SIZE)
				वापस -EFBIG;
		पूर्ण

		len += __iio_क्रमmat_value(buf, len, type, stride, &vals[i]);
		अगर (len >= PAGE_SIZE)
			वापस -EFBIG;
	पूर्ण

	len += sysfs_emit_at(buf, len, "%s\n", suffix);

	वापस len;
पूर्ण

अटल sमाप_प्रकार iio_क्रमmat_avail_list(अक्षर *buf, स्थिर पूर्णांक *vals,
				     पूर्णांक type, पूर्णांक length)
अणु

	वापस iio_क्रमmat_list(buf, vals, type, length, "", "");
पूर्ण

अटल sमाप_प्रकार iio_क्रमmat_avail_range(अक्षर *buf, स्थिर पूर्णांक *vals, पूर्णांक type)
अणु
	वापस iio_क्रमmat_list(buf, vals, type, 3, "[", "]");
पूर्ण

अटल sमाप_प्रकार iio_पढ़ो_channel_info_avail(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	स्थिर पूर्णांक *vals;
	पूर्णांक ret;
	पूर्णांक length;
	पूर्णांक type;

	ret = indio_dev->info->पढ़ो_avail(indio_dev, this_attr->c,
					  &vals, &type, &length,
					  this_attr->address);

	अगर (ret < 0)
		वापस ret;
	चयन (ret) अणु
	हाल IIO_AVAIL_LIST:
		वापस iio_क्रमmat_avail_list(buf, vals, type, length);
	हाल IIO_AVAIL_RANGE:
		वापस iio_क्रमmat_avail_range(buf, vals, type);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/**
 * __iio_str_to_fixpoपूर्णांक() - Parse a fixed-poपूर्णांक number from a string
 * @str: The string to parse
 * @fract_mult: Multiplier क्रम the first decimal place, should be a घातer of 10
 * @पूर्णांकeger: The पूर्णांकeger part of the number
 * @fract: The fractional part of the number
 * @scale_db: True अगर this should parse as dB
 *
 * Returns 0 on success, or a negative error code अगर the string could not be
 * parsed.
 */
अटल पूर्णांक __iio_str_to_fixpoपूर्णांक(स्थिर अक्षर *str, पूर्णांक fract_mult,
				 पूर्णांक *पूर्णांकeger, पूर्णांक *fract, bool scale_db)
अणु
	पूर्णांक i = 0, f = 0;
	bool पूर्णांकeger_part = true, negative = false;

	अगर (fract_mult == 0) अणु
		*fract = 0;

		वापस kstrtoपूर्णांक(str, 0, पूर्णांकeger);
	पूर्ण

	अगर (str[0] == '-') अणु
		negative = true;
		str++;
	पूर्ण अन्यथा अगर (str[0] == '+') अणु
		str++;
	पूर्ण

	जबतक (*str) अणु
		अगर ('0' <= *str && *str <= '9') अणु
			अगर (पूर्णांकeger_part) अणु
				i = i * 10 + *str - '0';
			पूर्ण अन्यथा अणु
				f += fract_mult * (*str - '0');
				fract_mult /= 10;
			पूर्ण
		पूर्ण अन्यथा अगर (*str == '\n') अणु
			अगर (*(str + 1) == '\0')
				अवरोध;
			अन्यथा
				वापस -EINVAL;
		पूर्ण अन्यथा अगर (!म_भेदन(str, " dB", माप(" dB") - 1) && scale_db) अणु
			/* Ignore the dB suffix */
			str += माप(" dB") - 1;
			जारी;
		पूर्ण अन्यथा अगर (!म_भेदन(str, "dB", माप("dB") - 1) && scale_db) अणु
			/* Ignore the dB suffix */
			str += माप("dB") - 1;
			जारी;
		पूर्ण अन्यथा अगर (*str == '.' && पूर्णांकeger_part) अणु
			पूर्णांकeger_part = false;
		पूर्ण अन्यथा अणु
			वापस -EINVAL;
		पूर्ण
		str++;
	पूर्ण

	अगर (negative) अणु
		अगर (i)
			i = -i;
		अन्यथा
			f = -f;
	पूर्ण

	*पूर्णांकeger = i;
	*fract = f;

	वापस 0;
पूर्ण

/**
 * iio_str_to_fixpoपूर्णांक() - Parse a fixed-poपूर्णांक number from a string
 * @str: The string to parse
 * @fract_mult: Multiplier क्रम the first decimal place, should be a घातer of 10
 * @पूर्णांकeger: The पूर्णांकeger part of the number
 * @fract: The fractional part of the number
 *
 * Returns 0 on success, or a negative error code अगर the string could not be
 * parsed.
 */
पूर्णांक iio_str_to_fixpoपूर्णांक(स्थिर अक्षर *str, पूर्णांक fract_mult,
			पूर्णांक *पूर्णांकeger, पूर्णांक *fract)
अणु
	वापस __iio_str_to_fixpoपूर्णांक(str, fract_mult, पूर्णांकeger, fract, false);
पूर्ण
EXPORT_SYMBOL_GPL(iio_str_to_fixpoपूर्णांक);

अटल sमाप_प्रकार iio_ग_लिखो_channel_info(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      स्थिर अक्षर *buf,
				      माप_प्रकार len)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	पूर्णांक ret, fract_mult = 100000;
	पूर्णांक पूर्णांकeger, fract = 0;
	bool is_अक्षर = false;
	bool scale_db = false;

	/* Assumes decimal - precision based on number of digits */
	अगर (!indio_dev->info->ग_लिखो_raw)
		वापस -EINVAL;

	अगर (indio_dev->info->ग_लिखो_raw_get_fmt)
		चयन (indio_dev->info->ग_लिखो_raw_get_fmt(indio_dev,
			this_attr->c, this_attr->address)) अणु
		हाल IIO_VAL_INT:
			fract_mult = 0;
			अवरोध;
		हाल IIO_VAL_INT_PLUS_MICRO_DB:
			scale_db = true;
			fallthrough;
		हाल IIO_VAL_INT_PLUS_MICRO:
			fract_mult = 100000;
			अवरोध;
		हाल IIO_VAL_INT_PLUS_न_अंकO:
			fract_mult = 100000000;
			अवरोध;
		हाल IIO_VAL_CHAR:
			is_अक्षर = true;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

	अगर (is_अक्षर) अणु
		अक्षर ch;

		अगर (माला_पूछो(buf, "%c", &ch) != 1)
			वापस -EINVAL;
		पूर्णांकeger = ch;
	पूर्ण अन्यथा अणु
		ret = __iio_str_to_fixpoपूर्णांक(buf, fract_mult, &पूर्णांकeger, &fract,
					    scale_db);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = indio_dev->info->ग_लिखो_raw(indio_dev, this_attr->c,
					 पूर्णांकeger, fract, this_attr->address);
	अगर (ret)
		वापस ret;

	वापस len;
पूर्ण

अटल
पूर्णांक __iio_device_attr_init(काष्ठा device_attribute *dev_attr,
			   स्थिर अक्षर *postfix,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   sमाप_प्रकार (*पढ़ोfunc)(काष्ठा device *dev,
					       काष्ठा device_attribute *attr,
					       अक्षर *buf),
			   sमाप_प्रकार (*ग_लिखोfunc)(काष्ठा device *dev,
						काष्ठा device_attribute *attr,
						स्थिर अक्षर *buf,
						माप_प्रकार len),
			   क्रमागत iio_shared_by shared_by)
अणु
	पूर्णांक ret = 0;
	अक्षर *name = शून्य;
	अक्षर *full_postfix;
	sysfs_attr_init(&dev_attr->attr);

	/* Build up postfix of <extend_name>_<modअगरier>_postfix */
	अगर (chan->modअगरied && (shared_by == IIO_SEPARATE)) अणु
		अगर (chan->extend_name)
			full_postfix = kaप्र_लिखो(GFP_KERNEL, "%s_%s_%s",
						 iio_modअगरier_names[chan
								    ->channel2],
						 chan->extend_name,
						 postfix);
		अन्यथा
			full_postfix = kaप्र_लिखो(GFP_KERNEL, "%s_%s",
						 iio_modअगरier_names[chan
								    ->channel2],
						 postfix);
	पूर्ण अन्यथा अणु
		अगर (chan->extend_name == शून्य || shared_by != IIO_SEPARATE)
			full_postfix = kstrdup(postfix, GFP_KERNEL);
		अन्यथा
			full_postfix = kaप्र_लिखो(GFP_KERNEL,
						 "%s_%s",
						 chan->extend_name,
						 postfix);
	पूर्ण
	अगर (full_postfix == शून्य)
		वापस -ENOMEM;

	अगर (chan->dअगरferential) अणु /* Dअगरferential can not have modअगरier */
		चयन (shared_by) अणु
		हाल IIO_SHARED_BY_ALL:
			name = kaप्र_लिखो(GFP_KERNEL, "%s", full_postfix);
			अवरोध;
		हाल IIO_SHARED_BY_सूची:
			name = kaप्र_लिखो(GFP_KERNEL, "%s_%s",
						iio_direction[chan->output],
						full_postfix);
			अवरोध;
		हाल IIO_SHARED_BY_TYPE:
			name = kaप्र_लिखो(GFP_KERNEL, "%s_%s-%s_%s",
					    iio_direction[chan->output],
					    iio_chan_type_name_spec[chan->type],
					    iio_chan_type_name_spec[chan->type],
					    full_postfix);
			अवरोध;
		हाल IIO_SEPARATE:
			अगर (!chan->indexed) अणु
				WARN(1, "Differential channels must be indexed\n");
				ret = -EINVAL;
				जाओ error_मुक्त_full_postfix;
			पूर्ण
			name = kaप्र_लिखो(GFP_KERNEL,
					    "%s_%s%d-%s%d_%s",
					    iio_direction[chan->output],
					    iio_chan_type_name_spec[chan->type],
					    chan->channel,
					    iio_chan_type_name_spec[chan->type],
					    chan->channel2,
					    full_postfix);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु /* Single ended */
		चयन (shared_by) अणु
		हाल IIO_SHARED_BY_ALL:
			name = kaप्र_लिखो(GFP_KERNEL, "%s", full_postfix);
			अवरोध;
		हाल IIO_SHARED_BY_सूची:
			name = kaप्र_लिखो(GFP_KERNEL, "%s_%s",
						iio_direction[chan->output],
						full_postfix);
			अवरोध;
		हाल IIO_SHARED_BY_TYPE:
			name = kaप्र_लिखो(GFP_KERNEL, "%s_%s_%s",
					    iio_direction[chan->output],
					    iio_chan_type_name_spec[chan->type],
					    full_postfix);
			अवरोध;

		हाल IIO_SEPARATE:
			अगर (chan->indexed)
				name = kaप्र_लिखो(GFP_KERNEL, "%s_%s%d_%s",
						    iio_direction[chan->output],
						    iio_chan_type_name_spec[chan->type],
						    chan->channel,
						    full_postfix);
			अन्यथा
				name = kaप्र_लिखो(GFP_KERNEL, "%s_%s_%s",
						    iio_direction[chan->output],
						    iio_chan_type_name_spec[chan->type],
						    full_postfix);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (name == शून्य) अणु
		ret = -ENOMEM;
		जाओ error_मुक्त_full_postfix;
	पूर्ण
	dev_attr->attr.name = name;

	अगर (पढ़ोfunc) अणु
		dev_attr->attr.mode |= S_IRUGO;
		dev_attr->show = पढ़ोfunc;
	पूर्ण

	अगर (ग_लिखोfunc) अणु
		dev_attr->attr.mode |= S_IWUSR;
		dev_attr->store = ग_लिखोfunc;
	पूर्ण

error_मुक्त_full_postfix:
	kमुक्त(full_postfix);

	वापस ret;
पूर्ण

अटल व्योम __iio_device_attr_deinit(काष्ठा device_attribute *dev_attr)
अणु
	kमुक्त(dev_attr->attr.name);
पूर्ण

पूर्णांक __iio_add_chan_devattr(स्थिर अक्षर *postfix,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   sमाप_प्रकार (*पढ़ोfunc)(काष्ठा device *dev,
					       काष्ठा device_attribute *attr,
					       अक्षर *buf),
			   sमाप_प्रकार (*ग_लिखोfunc)(काष्ठा device *dev,
						काष्ठा device_attribute *attr,
						स्थिर अक्षर *buf,
						माप_प्रकार len),
			   u64 mask,
			   क्रमागत iio_shared_by shared_by,
			   काष्ठा device *dev,
			   काष्ठा iio_buffer *buffer,
			   काष्ठा list_head *attr_list)
अणु
	पूर्णांक ret;
	काष्ठा iio_dev_attr *iio_attr, *t;

	iio_attr = kzalloc(माप(*iio_attr), GFP_KERNEL);
	अगर (iio_attr == शून्य)
		वापस -ENOMEM;
	ret = __iio_device_attr_init(&iio_attr->dev_attr,
				     postfix, chan,
				     पढ़ोfunc, ग_लिखोfunc, shared_by);
	अगर (ret)
		जाओ error_iio_dev_attr_मुक्त;
	iio_attr->c = chan;
	iio_attr->address = mask;
	iio_attr->buffer = buffer;
	list_क्रम_each_entry(t, attr_list, l)
		अगर (म_भेद(t->dev_attr.attr.name,
			   iio_attr->dev_attr.attr.name) == 0) अणु
			अगर (shared_by == IIO_SEPARATE)
				dev_err(dev, "tried to double register : %s\n",
					t->dev_attr.attr.name);
			ret = -EBUSY;
			जाओ error_device_attr_deinit;
		पूर्ण
	list_add(&iio_attr->l, attr_list);

	वापस 0;

error_device_attr_deinit:
	__iio_device_attr_deinit(&iio_attr->dev_attr);
error_iio_dev_attr_मुक्त:
	kमुक्त(iio_attr);
	वापस ret;
पूर्ण

अटल पूर्णांक iio_device_add_channel_label(काष्ठा iio_dev *indio_dev,
					 काष्ठा iio_chan_spec स्थिर *chan)
अणु
	काष्ठा iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	पूर्णांक ret;

	अगर (!indio_dev->info->पढ़ो_label)
		वापस 0;

	ret = __iio_add_chan_devattr("label",
				     chan,
				     &iio_पढ़ो_channel_label,
				     शून्य,
				     0,
				     IIO_SEPARATE,
				     &indio_dev->dev,
				     शून्य,
				     &iio_dev_opaque->channel_attr_list);
	अगर (ret < 0)
		वापस ret;

	वापस 1;
पूर्ण

अटल पूर्णांक iio_device_add_info_mask_type(काष्ठा iio_dev *indio_dev,
					 काष्ठा iio_chan_spec स्थिर *chan,
					 क्रमागत iio_shared_by shared_by,
					 स्थिर दीर्घ *infomask)
अणु
	काष्ठा iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	पूर्णांक i, ret, attrcount = 0;

	क्रम_each_set_bit(i, infomask, माप(*infomask)*8) अणु
		अगर (i >= ARRAY_SIZE(iio_chan_info_postfix))
			वापस -EINVAL;
		ret = __iio_add_chan_devattr(iio_chan_info_postfix[i],
					     chan,
					     &iio_पढ़ो_channel_info,
					     &iio_ग_लिखो_channel_info,
					     i,
					     shared_by,
					     &indio_dev->dev,
					     शून्य,
					     &iio_dev_opaque->channel_attr_list);
		अगर ((ret == -EBUSY) && (shared_by != IIO_SEPARATE))
			जारी;
		अन्यथा अगर (ret < 0)
			वापस ret;
		attrcount++;
	पूर्ण

	वापस attrcount;
पूर्ण

अटल पूर्णांक iio_device_add_info_mask_type_avail(काष्ठा iio_dev *indio_dev,
					       काष्ठा iio_chan_spec स्थिर *chan,
					       क्रमागत iio_shared_by shared_by,
					       स्थिर दीर्घ *infomask)
अणु
	काष्ठा iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	पूर्णांक i, ret, attrcount = 0;
	अक्षर *avail_postfix;

	क्रम_each_set_bit(i, infomask, माप(*infomask) * 8) अणु
		अगर (i >= ARRAY_SIZE(iio_chan_info_postfix))
			वापस -EINVAL;
		avail_postfix = kaप्र_लिखो(GFP_KERNEL,
					  "%s_available",
					  iio_chan_info_postfix[i]);
		अगर (!avail_postfix)
			वापस -ENOMEM;

		ret = __iio_add_chan_devattr(avail_postfix,
					     chan,
					     &iio_पढ़ो_channel_info_avail,
					     शून्य,
					     i,
					     shared_by,
					     &indio_dev->dev,
					     शून्य,
					     &iio_dev_opaque->channel_attr_list);
		kमुक्त(avail_postfix);
		अगर ((ret == -EBUSY) && (shared_by != IIO_SEPARATE))
			जारी;
		अन्यथा अगर (ret < 0)
			वापस ret;
		attrcount++;
	पूर्ण

	वापस attrcount;
पूर्ण

अटल पूर्णांक iio_device_add_channel_sysfs(काष्ठा iio_dev *indio_dev,
					काष्ठा iio_chan_spec स्थिर *chan)
अणु
	काष्ठा iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	पूर्णांक ret, attrcount = 0;
	स्थिर काष्ठा iio_chan_spec_ext_info *ext_info;

	अगर (chan->channel < 0)
		वापस 0;
	ret = iio_device_add_info_mask_type(indio_dev, chan,
					    IIO_SEPARATE,
					    &chan->info_mask_separate);
	अगर (ret < 0)
		वापस ret;
	attrcount += ret;

	ret = iio_device_add_info_mask_type_avail(indio_dev, chan,
						  IIO_SEPARATE,
						  &chan->
						  info_mask_separate_available);
	अगर (ret < 0)
		वापस ret;
	attrcount += ret;

	ret = iio_device_add_info_mask_type(indio_dev, chan,
					    IIO_SHARED_BY_TYPE,
					    &chan->info_mask_shared_by_type);
	अगर (ret < 0)
		वापस ret;
	attrcount += ret;

	ret = iio_device_add_info_mask_type_avail(indio_dev, chan,
						  IIO_SHARED_BY_TYPE,
						  &chan->
						  info_mask_shared_by_type_available);
	अगर (ret < 0)
		वापस ret;
	attrcount += ret;

	ret = iio_device_add_info_mask_type(indio_dev, chan,
					    IIO_SHARED_BY_सूची,
					    &chan->info_mask_shared_by_dir);
	अगर (ret < 0)
		वापस ret;
	attrcount += ret;

	ret = iio_device_add_info_mask_type_avail(indio_dev, chan,
						  IIO_SHARED_BY_सूची,
						  &chan->info_mask_shared_by_dir_available);
	अगर (ret < 0)
		वापस ret;
	attrcount += ret;

	ret = iio_device_add_info_mask_type(indio_dev, chan,
					    IIO_SHARED_BY_ALL,
					    &chan->info_mask_shared_by_all);
	अगर (ret < 0)
		वापस ret;
	attrcount += ret;

	ret = iio_device_add_info_mask_type_avail(indio_dev, chan,
						  IIO_SHARED_BY_ALL,
						  &chan->info_mask_shared_by_all_available);
	अगर (ret < 0)
		वापस ret;
	attrcount += ret;

	ret = iio_device_add_channel_label(indio_dev, chan);
	अगर (ret < 0)
		वापस ret;
	attrcount += ret;

	अगर (chan->ext_info) अणु
		अचिन्हित पूर्णांक i = 0;
		क्रम (ext_info = chan->ext_info; ext_info->name; ext_info++) अणु
			ret = __iio_add_chan_devattr(ext_info->name,
					chan,
					ext_info->पढ़ो ?
					    &iio_पढ़ो_channel_ext_info : शून्य,
					ext_info->ग_लिखो ?
					    &iio_ग_लिखो_channel_ext_info : शून्य,
					i,
					ext_info->shared,
					&indio_dev->dev,
					शून्य,
					&iio_dev_opaque->channel_attr_list);
			i++;
			अगर (ret == -EBUSY && ext_info->shared)
				जारी;

			अगर (ret)
				वापस ret;

			attrcount++;
		पूर्ण
	पूर्ण

	वापस attrcount;
पूर्ण

/**
 * iio_मुक्त_chan_devattr_list() - Free a list of IIO device attributes
 * @attr_list: List of IIO device attributes
 *
 * This function मुक्तs the memory allocated क्रम each of the IIO device
 * attributes in the list.
 */
व्योम iio_मुक्त_chan_devattr_list(काष्ठा list_head *attr_list)
अणु
	काष्ठा iio_dev_attr *p, *n;

	list_क्रम_each_entry_safe(p, n, attr_list, l) अणु
		kमुक्त_स्थिर(p->dev_attr.attr.name);
		list_del(&p->l);
		kमुक्त(p);
	पूर्ण
पूर्ण

अटल sमाप_प्रकार iio_show_dev_name(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	वापस sysfs_emit(buf, "%s\n", indio_dev->name);
पूर्ण

अटल DEVICE_ATTR(name, S_IRUGO, iio_show_dev_name, शून्य);

अटल sमाप_प्रकार iio_show_dev_label(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	वापस sysfs_emit(buf, "%s\n", indio_dev->label);
पूर्ण

अटल DEVICE_ATTR(label, S_IRUGO, iio_show_dev_label, शून्य);

अटल sमाप_प्रकार iio_show_बारtamp_घड़ी(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	स्थिर काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	स्थिर घड़ीid_t clk = iio_device_get_घड़ी(indio_dev);
	स्थिर अक्षर *name;
	sमाप_प्रकार sz;

	चयन (clk) अणु
	हाल CLOCK_REALTIME:
		name = "realtime\n";
		sz = माप("realtime\n");
		अवरोध;
	हाल CLOCK_MONOTONIC:
		name = "monotonic\n";
		sz = माप("monotonic\n");
		अवरोध;
	हाल CLOCK_MONOTONIC_RAW:
		name = "monotonic_raw\n";
		sz = माप("monotonic_raw\n");
		अवरोध;
	हाल CLOCK_REALTIME_COARSE:
		name = "realtime_coarse\n";
		sz = माप("realtime_coarse\n");
		अवरोध;
	हाल CLOCK_MONOTONIC_COARSE:
		name = "monotonic_coarse\n";
		sz = माप("monotonic_coarse\n");
		अवरोध;
	हाल CLOCK_BOOTTIME:
		name = "boottime\n";
		sz = माप("boottime\n");
		अवरोध;
	हाल CLOCK_TAI:
		name = "tai\n";
		sz = माप("tai\n");
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	स_नकल(buf, name, sz);
	वापस sz;
पूर्ण

अटल sमाप_प्रकार iio_store_बारtamp_घड़ी(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	घड़ीid_t clk;
	पूर्णांक ret;

	अगर (sysfs_streq(buf, "realtime"))
		clk = CLOCK_REALTIME;
	अन्यथा अगर (sysfs_streq(buf, "monotonic"))
		clk = CLOCK_MONOTONIC;
	अन्यथा अगर (sysfs_streq(buf, "monotonic_raw"))
		clk = CLOCK_MONOTONIC_RAW;
	अन्यथा अगर (sysfs_streq(buf, "realtime_coarse"))
		clk = CLOCK_REALTIME_COARSE;
	अन्यथा अगर (sysfs_streq(buf, "monotonic_coarse"))
		clk = CLOCK_MONOTONIC_COARSE;
	अन्यथा अगर (sysfs_streq(buf, "boottime"))
		clk = CLOCK_BOOTTIME;
	अन्यथा अगर (sysfs_streq(buf, "tai"))
		clk = CLOCK_TAI;
	अन्यथा
		वापस -EINVAL;

	ret = iio_device_set_घड़ी(dev_to_iio_dev(dev), clk);
	अगर (ret)
		वापस ret;

	वापस len;
पूर्ण

पूर्णांक iio_device_रेजिस्टर_sysfs_group(काष्ठा iio_dev *indio_dev,
				    स्थिर काष्ठा attribute_group *group)
अणु
	काष्ठा iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	स्थिर काष्ठा attribute_group **new, **old = iio_dev_opaque->groups;
	अचिन्हित पूर्णांक cnt = iio_dev_opaque->groupcounter;

	new = kपुनः_स्मृति(old, माप(*new) * (cnt + 2), GFP_KERNEL);
	अगर (!new)
		वापस -ENOMEM;

	new[iio_dev_opaque->groupcounter++] = group;
	new[iio_dev_opaque->groupcounter] = शून्य;

	iio_dev_opaque->groups = new;

	वापस 0;
पूर्ण

अटल DEVICE_ATTR(current_बारtamp_घड़ी, S_IRUGO | S_IWUSR,
		   iio_show_बारtamp_घड़ी, iio_store_बारtamp_घड़ी);

अटल पूर्णांक iio_device_रेजिस्टर_sysfs(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	पूर्णांक i, ret = 0, attrcount, attrn, attrcount_orig = 0;
	काष्ठा iio_dev_attr *p;
	काष्ठा attribute **attr, *clk = शून्य;

	/* First count elements in any existing group */
	अगर (indio_dev->info->attrs) अणु
		attr = indio_dev->info->attrs->attrs;
		जबतक (*attr++ != शून्य)
			attrcount_orig++;
	पूर्ण
	attrcount = attrcount_orig;
	/*
	 * New channel registration method - relies on the fact a group करोes
	 * not need to be initialized अगर its name is शून्य.
	 */
	अगर (indio_dev->channels)
		क्रम (i = 0; i < indio_dev->num_channels; i++) अणु
			स्थिर काष्ठा iio_chan_spec *chan =
				&indio_dev->channels[i];

			अगर (chan->type == IIO_TIMESTAMP)
				clk = &dev_attr_current_बारtamp_घड़ी.attr;

			ret = iio_device_add_channel_sysfs(indio_dev, chan);
			अगर (ret < 0)
				जाओ error_clear_attrs;
			attrcount += ret;
		पूर्ण

	अगर (iio_dev_opaque->event_पूर्णांकerface)
		clk = &dev_attr_current_बारtamp_घड़ी.attr;

	अगर (indio_dev->name)
		attrcount++;
	अगर (indio_dev->label)
		attrcount++;
	अगर (clk)
		attrcount++;

	iio_dev_opaque->chan_attr_group.attrs =
		kसुस्मृति(attrcount + 1,
			माप(iio_dev_opaque->chan_attr_group.attrs[0]),
			GFP_KERNEL);
	अगर (iio_dev_opaque->chan_attr_group.attrs == शून्य) अणु
		ret = -ENOMEM;
		जाओ error_clear_attrs;
	पूर्ण
	/* Copy across original attributes */
	अगर (indio_dev->info->attrs) अणु
		स_नकल(iio_dev_opaque->chan_attr_group.attrs,
		       indio_dev->info->attrs->attrs,
		       माप(iio_dev_opaque->chan_attr_group.attrs[0])
		       *attrcount_orig);
		iio_dev_opaque->chan_attr_group.is_visible =
			indio_dev->info->attrs->is_visible;
	पूर्ण
	attrn = attrcount_orig;
	/* Add all elements from the list. */
	list_क्रम_each_entry(p, &iio_dev_opaque->channel_attr_list, l)
		iio_dev_opaque->chan_attr_group.attrs[attrn++] = &p->dev_attr.attr;
	अगर (indio_dev->name)
		iio_dev_opaque->chan_attr_group.attrs[attrn++] = &dev_attr_name.attr;
	अगर (indio_dev->label)
		iio_dev_opaque->chan_attr_group.attrs[attrn++] = &dev_attr_label.attr;
	अगर (clk)
		iio_dev_opaque->chan_attr_group.attrs[attrn++] = clk;

	ret = iio_device_रेजिस्टर_sysfs_group(indio_dev,
					      &iio_dev_opaque->chan_attr_group);
	अगर (ret)
		जाओ error_clear_attrs;

	वापस 0;

error_clear_attrs:
	iio_मुक्त_chan_devattr_list(&iio_dev_opaque->channel_attr_list);

	वापस ret;
पूर्ण

अटल व्योम iio_device_unरेजिस्टर_sysfs(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);

	iio_मुक्त_chan_devattr_list(&iio_dev_opaque->channel_attr_list);
	kमुक्त(iio_dev_opaque->chan_attr_group.attrs);
	iio_dev_opaque->chan_attr_group.attrs = शून्य;
	kमुक्त(iio_dev_opaque->groups);
पूर्ण

अटल व्योम iio_dev_release(काष्ठा device *device)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(device);
	काष्ठा iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);

	अगर (indio_dev->modes & INDIO_ALL_TRIGGERED_MODES)
		iio_device_unरेजिस्टर_trigger_consumer(indio_dev);
	iio_device_unरेजिस्टर_eventset(indio_dev);
	iio_device_unरेजिस्टर_sysfs(indio_dev);

	iio_device_detach_buffers(indio_dev);

	ida_simple_हटाओ(&iio_ida, indio_dev->id);
	kमुक्त(iio_dev_opaque);
पूर्ण

काष्ठा device_type iio_device_type = अणु
	.name = "iio_device",
	.release = iio_dev_release,
पूर्ण;

/**
 * iio_device_alloc() - allocate an iio_dev from a driver
 * @parent:		Parent device.
 * @माप_priv:	Space to allocate क्रम निजी काष्ठाure.
 **/
काष्ठा iio_dev *iio_device_alloc(काष्ठा device *parent, पूर्णांक माप_priv)
अणु
	काष्ठा iio_dev_opaque *iio_dev_opaque;
	काष्ठा iio_dev *indio_dev;
	माप_प्रकार alloc_size;

	alloc_size = माप(काष्ठा iio_dev_opaque);
	अगर (माप_priv) अणु
		alloc_size = ALIGN(alloc_size, IIO_ALIGN);
		alloc_size += माप_priv;
	पूर्ण

	iio_dev_opaque = kzalloc(alloc_size, GFP_KERNEL);
	अगर (!iio_dev_opaque)
		वापस शून्य;

	indio_dev = &iio_dev_opaque->indio_dev;
	indio_dev->priv = (अक्षर *)iio_dev_opaque +
		ALIGN(माप(काष्ठा iio_dev_opaque), IIO_ALIGN);

	indio_dev->dev.parent = parent;
	indio_dev->dev.type = &iio_device_type;
	indio_dev->dev.bus = &iio_bus_type;
	device_initialize(&indio_dev->dev);
	iio_device_set_drvdata(indio_dev, (व्योम *)indio_dev);
	mutex_init(&indio_dev->mlock);
	mutex_init(&indio_dev->info_exist_lock);
	INIT_LIST_HEAD(&iio_dev_opaque->channel_attr_list);

	indio_dev->id = ida_simple_get(&iio_ida, 0, 0, GFP_KERNEL);
	अगर (indio_dev->id < 0) अणु
		/* cannot use a dev_err as the name isn't available */
		pr_err("failed to get device id\n");
		kमुक्त(iio_dev_opaque);
		वापस शून्य;
	पूर्ण
	dev_set_name(&indio_dev->dev, "iio:device%d", indio_dev->id);
	INIT_LIST_HEAD(&iio_dev_opaque->buffer_list);
	INIT_LIST_HEAD(&iio_dev_opaque->ioctl_handlers);

	वापस indio_dev;
पूर्ण
EXPORT_SYMBOL(iio_device_alloc);

/**
 * iio_device_मुक्त() - मुक्त an iio_dev from a driver
 * @dev:		the iio_dev associated with the device
 **/
व्योम iio_device_मुक्त(काष्ठा iio_dev *dev)
अणु
	अगर (dev)
		put_device(&dev->dev);
पूर्ण
EXPORT_SYMBOL(iio_device_मुक्त);

अटल व्योम devm_iio_device_release(काष्ठा device *dev, व्योम *res)
अणु
	iio_device_मुक्त(*(काष्ठा iio_dev **)res);
पूर्ण

/**
 * devm_iio_device_alloc - Resource-managed iio_device_alloc()
 * @parent:		Device to allocate iio_dev क्रम, and parent क्रम this IIO device
 * @माप_priv:	Space to allocate क्रम निजी काष्ठाure.
 *
 * Managed iio_device_alloc. iio_dev allocated with this function is
 * स्वतःmatically मुक्तd on driver detach.
 *
 * RETURNS:
 * Poपूर्णांकer to allocated iio_dev on success, शून्य on failure.
 */
काष्ठा iio_dev *devm_iio_device_alloc(काष्ठा device *parent, पूर्णांक माप_priv)
अणु
	काष्ठा iio_dev **ptr, *iio_dev;

	ptr = devres_alloc(devm_iio_device_release, माप(*ptr),
			   GFP_KERNEL);
	अगर (!ptr)
		वापस शून्य;

	iio_dev = iio_device_alloc(parent, माप_priv);
	अगर (iio_dev) अणु
		*ptr = iio_dev;
		devres_add(parent, ptr);
	पूर्ण अन्यथा अणु
		devres_मुक्त(ptr);
	पूर्ण

	वापस iio_dev;
पूर्ण
EXPORT_SYMBOL_GPL(devm_iio_device_alloc);

/**
 * iio_chrdev_खोलो() - chrdev file खोलो क्रम buffer access and ioctls
 * @inode:	Inode काष्ठाure क्रम identअगरying the device in the file प्रणाली
 * @filp:	File काष्ठाure क्रम iio device used to keep and later access
 *		निजी data
 *
 * Return: 0 on success or -EBUSY अगर the device is alपढ़ोy खोलोed
 **/
अटल पूर्णांक iio_chrdev_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा iio_dev *indio_dev = container_of(inode->i_cdev,
						काष्ठा iio_dev, chrdev);
	काष्ठा iio_dev_buffer_pair *ib;

	अगर (test_and_set_bit(IIO_BUSY_BIT_POS, &indio_dev->flags))
		वापस -EBUSY;

	iio_device_get(indio_dev);

	ib = kदो_स्मृति(माप(*ib), GFP_KERNEL);
	अगर (!ib) अणु
		iio_device_put(indio_dev);
		clear_bit(IIO_BUSY_BIT_POS, &indio_dev->flags);
		वापस -ENOMEM;
	पूर्ण

	ib->indio_dev = indio_dev;
	ib->buffer = indio_dev->buffer;

	filp->निजी_data = ib;

	वापस 0;
पूर्ण

/**
 * iio_chrdev_release() - chrdev file बंद buffer access and ioctls
 * @inode:	Inode काष्ठाure poपूर्णांकer क्रम the अक्षर device
 * @filp:	File काष्ठाure poपूर्णांकer क्रम the अक्षर device
 *
 * Return: 0 क्रम successful release
 */
अटल पूर्णांक iio_chrdev_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा iio_dev_buffer_pair *ib = filp->निजी_data;
	काष्ठा iio_dev *indio_dev = container_of(inode->i_cdev,
						काष्ठा iio_dev, chrdev);
	kमुक्त(ib);
	clear_bit(IIO_BUSY_BIT_POS, &indio_dev->flags);
	iio_device_put(indio_dev);

	वापस 0;
पूर्ण

व्योम iio_device_ioctl_handler_रेजिस्टर(काष्ठा iio_dev *indio_dev,
				       काष्ठा iio_ioctl_handler *h)
अणु
	काष्ठा iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);

	list_add_tail(&h->entry, &iio_dev_opaque->ioctl_handlers);
पूर्ण

व्योम iio_device_ioctl_handler_unरेजिस्टर(काष्ठा iio_ioctl_handler *h)
अणु
	list_del(&h->entry);
पूर्ण

अटल दीर्घ iio_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा iio_dev_buffer_pair *ib = filp->निजी_data;
	काष्ठा iio_dev *indio_dev = ib->indio_dev;
	काष्ठा iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	काष्ठा iio_ioctl_handler *h;
	पूर्णांक ret = -ENODEV;

	mutex_lock(&indio_dev->info_exist_lock);

	/**
	 * The शून्य check here is required to prevent crashing when a device
	 * is being हटाओd जबतक userspace would still have खोलो file handles
	 * to try to access this device.
	 */
	अगर (!indio_dev->info)
		जाओ out_unlock;

	list_क्रम_each_entry(h, &iio_dev_opaque->ioctl_handlers, entry) अणु
		ret = h->ioctl(indio_dev, filp, cmd, arg);
		अगर (ret != IIO_IOCTL_UNHANDLED)
			अवरोध;
	पूर्ण

	अगर (ret == IIO_IOCTL_UNHANDLED)
		ret = -ENODEV;

out_unlock:
	mutex_unlock(&indio_dev->info_exist_lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations iio_buffer_fileops = अणु
	.owner = THIS_MODULE,
	.llseek = noop_llseek,
	.पढ़ो = iio_buffer_पढ़ो_outer_addr,
	.poll = iio_buffer_poll_addr,
	.unlocked_ioctl = iio_ioctl,
	.compat_ioctl = compat_ptr_ioctl,
	.खोलो = iio_chrdev_खोलो,
	.release = iio_chrdev_release,
पूर्ण;

अटल स्थिर काष्ठा file_operations iio_event_fileops = अणु
	.owner = THIS_MODULE,
	.llseek = noop_llseek,
	.unlocked_ioctl = iio_ioctl,
	.compat_ioctl = compat_ptr_ioctl,
	.खोलो = iio_chrdev_खोलो,
	.release = iio_chrdev_release,
पूर्ण;

अटल पूर्णांक iio_check_unique_scan_index(काष्ठा iio_dev *indio_dev)
अणु
	पूर्णांक i, j;
	स्थिर काष्ठा iio_chan_spec *channels = indio_dev->channels;

	अगर (!(indio_dev->modes & INDIO_ALL_BUFFER_MODES))
		वापस 0;

	क्रम (i = 0; i < indio_dev->num_channels - 1; i++) अणु
		अगर (channels[i].scan_index < 0)
			जारी;
		क्रम (j = i + 1; j < indio_dev->num_channels; j++)
			अगर (channels[i].scan_index == channels[j].scan_index) अणु
				dev_err(&indio_dev->dev,
					"Duplicate scan index %d\n",
					channels[i].scan_index);
				वापस -EINVAL;
			पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iio_buffer_setup_ops noop_ring_setup_ops;

पूर्णांक __iio_device_रेजिस्टर(काष्ठा iio_dev *indio_dev, काष्ठा module *this_mod)
अणु
	काष्ठा iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	स्थिर अक्षर *label;
	पूर्णांक ret;

	अगर (!indio_dev->info)
		वापस -EINVAL;

	indio_dev->driver_module = this_mod;
	/* If the calling driver did not initialize of_node, करो it here */
	अगर (!indio_dev->dev.of_node && indio_dev->dev.parent)
		indio_dev->dev.of_node = indio_dev->dev.parent->of_node;

	label = of_get_property(indio_dev->dev.of_node, "label", शून्य);
	अगर (label)
		indio_dev->label = label;

	ret = iio_check_unique_scan_index(indio_dev);
	अगर (ret < 0)
		वापस ret;

	iio_device_रेजिस्टर_debugfs(indio_dev);

	ret = iio_buffers_alloc_sysfs_and_mask(indio_dev);
	अगर (ret) अणु
		dev_err(indio_dev->dev.parent,
			"Failed to create buffer sysfs interfaces\n");
		जाओ error_unreg_debugfs;
	पूर्ण

	ret = iio_device_रेजिस्टर_sysfs(indio_dev);
	अगर (ret) अणु
		dev_err(indio_dev->dev.parent,
			"Failed to register sysfs interfaces\n");
		जाओ error_buffer_मुक्त_sysfs;
	पूर्ण
	ret = iio_device_रेजिस्टर_eventset(indio_dev);
	अगर (ret) अणु
		dev_err(indio_dev->dev.parent,
			"Failed to register event set\n");
		जाओ error_मुक्त_sysfs;
	पूर्ण
	अगर (indio_dev->modes & INDIO_ALL_TRIGGERED_MODES)
		iio_device_रेजिस्टर_trigger_consumer(indio_dev);

	अगर ((indio_dev->modes & INDIO_ALL_BUFFER_MODES) &&
		indio_dev->setup_ops == शून्य)
		indio_dev->setup_ops = &noop_ring_setup_ops;

	अगर (iio_dev_opaque->attached_buffers_cnt)
		cdev_init(&indio_dev->chrdev, &iio_buffer_fileops);
	अन्यथा अगर (iio_dev_opaque->event_पूर्णांकerface)
		cdev_init(&indio_dev->chrdev, &iio_event_fileops);

	अगर (iio_dev_opaque->attached_buffers_cnt || iio_dev_opaque->event_पूर्णांकerface) अणु
		indio_dev->dev.devt = MKDEV(MAJOR(iio_devt), indio_dev->id);
		indio_dev->chrdev.owner = this_mod;
	पूर्ण

	/* assign device groups now; they should be all रेजिस्टरed now */
	indio_dev->dev.groups = iio_dev_opaque->groups;

	ret = cdev_device_add(&indio_dev->chrdev, &indio_dev->dev);
	अगर (ret < 0)
		जाओ error_unreg_eventset;

	वापस 0;

error_unreg_eventset:
	iio_device_unरेजिस्टर_eventset(indio_dev);
error_मुक्त_sysfs:
	iio_device_unरेजिस्टर_sysfs(indio_dev);
error_buffer_मुक्त_sysfs:
	iio_buffers_मुक्त_sysfs_and_mask(indio_dev);
error_unreg_debugfs:
	iio_device_unरेजिस्टर_debugfs(indio_dev);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(__iio_device_रेजिस्टर);

/**
 * iio_device_unरेजिस्टर() - unरेजिस्टर a device from the IIO subप्रणाली
 * @indio_dev:		Device काष्ठाure representing the device.
 **/
व्योम iio_device_unरेजिस्टर(काष्ठा iio_dev *indio_dev)
अणु
	cdev_device_del(&indio_dev->chrdev, &indio_dev->dev);

	mutex_lock(&indio_dev->info_exist_lock);

	iio_device_unरेजिस्टर_debugfs(indio_dev);

	iio_disable_all_buffers(indio_dev);

	indio_dev->info = शून्य;

	iio_device_wakeup_eventset(indio_dev);
	iio_buffer_wakeup_poll(indio_dev);

	mutex_unlock(&indio_dev->info_exist_lock);

	iio_buffers_मुक्त_sysfs_and_mask(indio_dev);
पूर्ण
EXPORT_SYMBOL(iio_device_unरेजिस्टर);

अटल व्योम devm_iio_device_unreg(काष्ठा device *dev, व्योम *res)
अणु
	iio_device_unरेजिस्टर(*(काष्ठा iio_dev **)res);
पूर्ण

पूर्णांक __devm_iio_device_रेजिस्टर(काष्ठा device *dev, काष्ठा iio_dev *indio_dev,
			       काष्ठा module *this_mod)
अणु
	काष्ठा iio_dev **ptr;
	पूर्णांक ret;

	ptr = devres_alloc(devm_iio_device_unreg, माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस -ENOMEM;

	*ptr = indio_dev;
	ret = __iio_device_रेजिस्टर(indio_dev, this_mod);
	अगर (!ret)
		devres_add(dev, ptr);
	अन्यथा
		devres_मुक्त(ptr);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(__devm_iio_device_रेजिस्टर);

/**
 * iio_device_claim_direct_mode - Keep device in direct mode
 * @indio_dev:	the iio_dev associated with the device
 *
 * If the device is in direct mode it is guaranteed to stay
 * that way until iio_device_release_direct_mode() is called.
 *
 * Use with iio_device_release_direct_mode()
 *
 * Returns: 0 on success, -EBUSY on failure
 */
पूर्णांक iio_device_claim_direct_mode(काष्ठा iio_dev *indio_dev)
अणु
	mutex_lock(&indio_dev->mlock);

	अगर (iio_buffer_enabled(indio_dev)) अणु
		mutex_unlock(&indio_dev->mlock);
		वापस -EBUSY;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(iio_device_claim_direct_mode);

/**
 * iio_device_release_direct_mode - releases claim on direct mode
 * @indio_dev:	the iio_dev associated with the device
 *
 * Release the claim. Device is no दीर्घer guaranteed to stay
 * in direct mode.
 *
 * Use with iio_device_claim_direct_mode()
 */
व्योम iio_device_release_direct_mode(काष्ठा iio_dev *indio_dev)
अणु
	mutex_unlock(&indio_dev->mlock);
पूर्ण
EXPORT_SYMBOL_GPL(iio_device_release_direct_mode);

subsys_initcall(iio_init);
module_निकास(iio_निकास);

MODULE_AUTHOR("Jonathan Cameron <jic23@kernel.org>");
MODULE_DESCRIPTION("Industrial I/O core");
MODULE_LICENSE("GPL");
