<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Industrialio event test code.
 *
 * Copyright (c) 2011-2012 Lars-Peter Clausen <lars@metafoo.de>
 *
 * This program is primarily पूर्णांकended as an example application.
 * Reads the current buffer setup from sysfs and starts a लघु capture
 * from the specअगरied device, pretty prपूर्णांकing the result after appropriate
 * conversion.
 *
 * Usage:
 *	iio_event_monitor <device_name>
 */

#समावेश <unistd.h>
#समावेश <मानककोष.स>
#समावेश <dirent.h>
#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <त्रुटिसं.स>
#समावेश <माला.स>
#समावेश <poll.h>
#समावेश <fcntl.h>
#समावेश <sys/ioctl.h>
#समावेश "iio_utils.h"
#समावेश <linux/iio/events.h>
#समावेश <linux/iio/types.h>

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
	[IIO_GRAVITY] = "gravity",
	[IIO_POSITIONRELATIVE] = "positionrelative",
	[IIO_PHASE] = "phase",
	[IIO_MASSCONCENTRATION] = "massconcentration",
पूर्ण;

अटल स्थिर अक्षर * स्थिर iio_ev_type_text[] = अणु
	[IIO_EV_TYPE_THRESH] = "thresh",
	[IIO_EV_TYPE_MAG] = "mag",
	[IIO_EV_TYPE_ROC] = "roc",
	[IIO_EV_TYPE_THRESH_ADAPTIVE] = "thresh_adaptive",
	[IIO_EV_TYPE_MAG_ADAPTIVE] = "mag_adaptive",
	[IIO_EV_TYPE_CHANGE] = "change",
पूर्ण;

अटल स्थिर अक्षर * स्थिर iio_ev_dir_text[] = अणु
	[IIO_EV_सूची_EITHER] = "either",
	[IIO_EV_सूची_RISING] = "rising",
	[IIO_EV_सूची_FALLING] = "falling"
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
	[IIO_MOD_LIGHT_BOTH] = "both",
	[IIO_MOD_LIGHT_IR] = "ir",
	[IIO_MOD_ROOT_SUM_SQUARED_X_Y] = "वर्ग_मूल(x^2+y^2)",
	[IIO_MOD_SUM_SQUARED_X_Y_Z] = "x^2+y^2+z^2",
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
	[IIO_MOD_ETHANOL] = "ethanol",
	[IIO_MOD_H2] = "h2",
	[IIO_MOD_VOC] = "voc",
	[IIO_MOD_PM1] = "pm1",
	[IIO_MOD_PM2P5] = "pm2p5",
	[IIO_MOD_PM4] = "pm4",
	[IIO_MOD_PM10] = "pm10",
	[IIO_MOD_O2] = "o2",
पूर्ण;

अटल bool event_is_known(काष्ठा iio_event_data *event)
अणु
	क्रमागत iio_chan_type type = IIO_EVENT_CODE_EXTRACT_CHAN_TYPE(event->id);
	क्रमागत iio_modअगरier mod = IIO_EVENT_CODE_EXTRACT_MODIFIER(event->id);
	क्रमागत iio_event_type ev_type = IIO_EVENT_CODE_EXTRACT_TYPE(event->id);
	क्रमागत iio_event_direction dir = IIO_EVENT_CODE_EXTRACT_सूची(event->id);

	चयन (type) अणु
	हाल IIO_VOLTAGE:
	हाल IIO_CURRENT:
	हाल IIO_POWER:
	हाल IIO_ACCEL:
	हाल IIO_ANGL_VEL:
	हाल IIO_MAGN:
	हाल IIO_LIGHT:
	हाल IIO_INTENSITY:
	हाल IIO_PROXIMITY:
	हाल IIO_TEMP:
	हाल IIO_INCLI:
	हाल IIO_ROT:
	हाल IIO_ANGL:
	हाल IIO_TIMESTAMP:
	हाल IIO_CAPACITANCE:
	हाल IIO_ALTVOLTAGE:
	हाल IIO_CCT:
	हाल IIO_PRESSURE:
	हाल IIO_HUMIDITYRELATIVE:
	हाल IIO_ACTIVITY:
	हाल IIO_STEPS:
	हाल IIO_ENERGY:
	हाल IIO_DISTANCE:
	हाल IIO_VELOCITY:
	हाल IIO_CONCENTRATION:
	हाल IIO_RESISTANCE:
	हाल IIO_PH:
	हाल IIO_UVINDEX:
	हाल IIO_GRAVITY:
	हाल IIO_POSITIONRELATIVE:
	हाल IIO_PHASE:
	हाल IIO_MASSCONCENTRATION:
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	चयन (mod) अणु
	हाल IIO_NO_MOD:
	हाल IIO_MOD_X:
	हाल IIO_MOD_Y:
	हाल IIO_MOD_Z:
	हाल IIO_MOD_X_AND_Y:
	हाल IIO_MOD_X_AND_Z:
	हाल IIO_MOD_Y_AND_Z:
	हाल IIO_MOD_X_AND_Y_AND_Z:
	हाल IIO_MOD_X_OR_Y:
	हाल IIO_MOD_X_OR_Z:
	हाल IIO_MOD_Y_OR_Z:
	हाल IIO_MOD_X_OR_Y_OR_Z:
	हाल IIO_MOD_LIGHT_BOTH:
	हाल IIO_MOD_LIGHT_IR:
	हाल IIO_MOD_ROOT_SUM_SQUARED_X_Y:
	हाल IIO_MOD_SUM_SQUARED_X_Y_Z:
	हाल IIO_MOD_LIGHT_CLEAR:
	हाल IIO_MOD_LIGHT_RED:
	हाल IIO_MOD_LIGHT_GREEN:
	हाल IIO_MOD_LIGHT_BLUE:
	हाल IIO_MOD_LIGHT_UV:
	हाल IIO_MOD_LIGHT_DUV:
	हाल IIO_MOD_QUATERNION:
	हाल IIO_MOD_TEMP_AMBIENT:
	हाल IIO_MOD_TEMP_OBJECT:
	हाल IIO_MOD_NORTH_MAGN:
	हाल IIO_MOD_NORTH_TRUE:
	हाल IIO_MOD_NORTH_MAGN_TILT_COMP:
	हाल IIO_MOD_NORTH_TRUE_TILT_COMP:
	हाल IIO_MOD_RUNNING:
	हाल IIO_MOD_JOGGING:
	हाल IIO_MOD_WALKING:
	हाल IIO_MOD_STILL:
	हाल IIO_MOD_ROOT_SUM_SQUARED_X_Y_Z:
	हाल IIO_MOD_I:
	हाल IIO_MOD_Q:
	हाल IIO_MOD_CO2:
	हाल IIO_MOD_ETHANOL:
	हाल IIO_MOD_H2:
	हाल IIO_MOD_VOC:
	हाल IIO_MOD_PM1:
	हाल IIO_MOD_PM2P5:
	हाल IIO_MOD_PM4:
	हाल IIO_MOD_PM10:
	हाल IIO_MOD_O2:
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	चयन (ev_type) अणु
	हाल IIO_EV_TYPE_THRESH:
	हाल IIO_EV_TYPE_MAG:
	हाल IIO_EV_TYPE_ROC:
	हाल IIO_EV_TYPE_THRESH_ADAPTIVE:
	हाल IIO_EV_TYPE_MAG_ADAPTIVE:
	हाल IIO_EV_TYPE_CHANGE:
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	चयन (dir) अणु
	हाल IIO_EV_सूची_EITHER:
	हाल IIO_EV_सूची_RISING:
	हाल IIO_EV_सूची_FALLING:
	हाल IIO_EV_सूची_NONE:
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम prपूर्णांक_event(काष्ठा iio_event_data *event)
अणु
	क्रमागत iio_chan_type type = IIO_EVENT_CODE_EXTRACT_CHAN_TYPE(event->id);
	क्रमागत iio_modअगरier mod = IIO_EVENT_CODE_EXTRACT_MODIFIER(event->id);
	क्रमागत iio_event_type ev_type = IIO_EVENT_CODE_EXTRACT_TYPE(event->id);
	क्रमागत iio_event_direction dir = IIO_EVENT_CODE_EXTRACT_सूची(event->id);
	पूर्णांक chan = IIO_EVENT_CODE_EXTRACT_CHAN(event->id);
	पूर्णांक chan2 = IIO_EVENT_CODE_EXTRACT_CHAN2(event->id);
	bool dअगरf = IIO_EVENT_CODE_EXTRACT_DIFF(event->id);

	अगर (!event_is_known(event)) अणु
		ख_लिखो(मानक_त्रुटि, "Unknown event: time: %lld, id: %llx\n",
			event->बारtamp, event->id);

		वापस;
	पूर्ण

	म_लिखो("Event: time: %lld, type: %s", event->बारtamp,
	       iio_chan_type_name_spec[type]);

	अगर (mod != IIO_NO_MOD)
		म_लिखो("(%s)", iio_modअगरier_names[mod]);

	अगर (chan >= 0) अणु
		म_लिखो(", channel: %d", chan);
		अगर (dअगरf && chan2 >= 0)
			म_लिखो("-%d", chan2);
	पूर्ण

	म_लिखो(", evtype: %s", iio_ev_type_text[ev_type]);

	अगर (dir != IIO_EV_सूची_NONE)
		म_लिखो(", direction: %s", iio_ev_dir_text[dir]);

	म_लिखो("\n");
पूर्ण

/* Enable or disable events in sysfs अगर the knob is available */
अटल व्योम enable_events(अक्षर *dev_dir, पूर्णांक enable)
अणु
	स्थिर काष्ठा dirent *ent;
	अक्षर evdir[256];
	पूर्णांक ret;
	सूची *dp;

	snम_लिखो(evdir, माप(evdir), FORMAT_EVENTS_सूची, dev_dir);
	evdir[माप(evdir)-1] = '\0';

	dp = सूची_खोलो(evdir);
	अगर (!dp) अणु
		ख_लिखो(मानक_त्रुटि, "Enabling/disabling events: can't open %s\n",
			evdir);
		वापस;
	पूर्ण

	जबतक (ent = सूची_पढ़ो(dp), ent) अणु
		अगर (iioutils_check_suffix(ent->d_name, "_en")) अणु
			म_लिखो("%sabling: %s\n",
			       enable ? "En" : "Dis",
			       ent->d_name);
			ret = ग_लिखो_sysfs_पूर्णांक(ent->d_name, evdir,
					      enable);
			अगर (ret < 0)
				ख_लिखो(मानक_त्रुटि, "Failed to enable/disable %s\n",
					ent->d_name);
		पूर्ण
	पूर्ण

	अगर (बंद_सूची(dp) == -1) अणु
		लिखो_त्रुटि("Enabling/disabling channels: "
		       "Failed to close directory");
		वापस;
	पूर्ण
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा iio_event_data event;
	स्थिर अक्षर *device_name;
	अक्षर *dev_dir_name = शून्य;
	अक्षर *chrdev_name;
	पूर्णांक ret;
	पूर्णांक dev_num;
	पूर्णांक fd, event_fd;
	bool all_events = false;

	अगर (argc == 2) अणु
		device_name = argv[1];
	पूर्ण अन्यथा अगर (argc == 3) अणु
		device_name = argv[2];
		अगर (!म_भेद(argv[1], "-a"))
			all_events = true;
	पूर्ण अन्यथा अणु
		ख_लिखो(मानक_त्रुटि,
			"Usage: iio_event_monitor [options] <device_name>\n"
			"Listen and display events from IIO devices\n"
			"  -a         Auto-activate all available events\n");
		वापस -1;
	पूर्ण

	dev_num = find_type_by_name(device_name, "iio:device");
	अगर (dev_num >= 0) अणु
		म_लिखो("Found IIO device with name %s with device number %d\n",
		       device_name, dev_num);
		ret = aप्र_लिखो(&chrdev_name, "/dev/iio:device%d", dev_num);
		अगर (ret < 0)
			वापस -ENOMEM;
		/* Look up sysfs dir as well अगर we can */
		ret = aप्र_लिखो(&dev_dir_name, "%siio:device%d", iio_dir, dev_num);
		अगर (ret < 0)
			वापस -ENOMEM;
	पूर्ण अन्यथा अणु
		/*
		 * If we can't find an IIO device by name assume device_name is
		 * an IIO chrdev
		 */
		chrdev_name = strdup(device_name);
		अगर (!chrdev_name)
			वापस -ENOMEM;
	पूर्ण

	अगर (all_events && dev_dir_name)
		enable_events(dev_dir_name, 1);

	fd = खोलो(chrdev_name, 0);
	अगर (fd == -1) अणु
		ret = -त्रुटि_सं;
		ख_लिखो(मानक_त्रुटि, "Failed to open %s\n", chrdev_name);
		जाओ error_मुक्त_chrdev_name;
	पूर्ण

	ret = ioctl(fd, IIO_GET_EVENT_FD_IOCTL, &event_fd);
	अगर (ret == -1 || event_fd == -1) अणु
		ret = -त्रुटि_सं;
		अगर (ret == -ENODEV)
			ख_लिखो(मानक_त्रुटि,
				"This device does not support events\n");
		अन्यथा
			ख_लिखो(मानक_त्रुटि, "Failed to retrieve event fd\n");
		अगर (बंद(fd) == -1)
			लिखो_त्रुटि("Failed to close character device file");

		जाओ error_मुक्त_chrdev_name;
	पूर्ण

	अगर (बंद(fd) == -1)  अणु
		ret = -त्रुटि_सं;
		जाओ error_मुक्त_chrdev_name;
	पूर्ण

	जबतक (true) अणु
		ret = पढ़ो(event_fd, &event, माप(event));
		अगर (ret == -1) अणु
			अगर (त्रुटि_सं == EAGAIN) अणु
				ख_लिखो(मानक_त्रुटि, "nothing available\n");
				जारी;
			पूर्ण अन्यथा अणु
				ret = -त्रुटि_सं;
				लिखो_त्रुटि("Failed to read event from device");
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (ret != माप(event)) अणु
			ख_लिखो(मानक_त्रुटि, "Reading event failed!\n");
			ret = -EIO;
			अवरोध;
		पूर्ण

		prपूर्णांक_event(&event);
	पूर्ण

	अगर (बंद(event_fd) == -1)
		लिखो_त्रुटि("Failed to close event file");

error_मुक्त_chrdev_name:
	/* Disable events after use */
	अगर (all_events && dev_dir_name)
		enable_events(dev_dir_name, 0);

	मुक्त(chrdev_name);

	वापस ret;
पूर्ण
