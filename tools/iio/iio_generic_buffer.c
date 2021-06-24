<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Industrialio buffer test code.
 *
 * Copyright (c) 2008 Jonathan Cameron
 *
 * This program is primarily पूर्णांकended as an example application.
 * Reads the current buffer setup from sysfs and starts a लघु capture
 * from the specअगरied device, pretty prपूर्णांकing the result after appropriate
 * conversion.
 *
 * Command line parameters
 * generic_buffer -n <device_name> -t <trigger_name>
 * If trigger name is not specअगरied the program assumes you want a dataपढ़ोy
 * trigger associated with the device and goes looking क्रम it.
 */

#समावेश <unistd.h>
#समावेश <मानककोष.स>
#समावेश <dirent.h>
#समावेश <fcntl.h>
#समावेश <मानकपन.स>
#समावेश <त्रुटिसं.स>
#समावेश <sys/स्थिति.स>
#समावेश <sys/सूची.स>
#समावेश <linux/types.h>
#समावेश <माला.स>
#समावेश <poll.h>
#समावेश <endian.h>
#समावेश <getopt.h>
#समावेश <पूर्णांकtypes.h>
#समावेश <stdbool.h>
#समावेश <संकेत.स>
#समावेश <sys/ioctl.h>
#समावेश <linux/iio/buffer.h>
#समावेश "iio_utils.h"

/**
 * क्रमागत स्वतःchan - state क्रम the स्वतःmatic channel enabling mechanism
 */
क्रमागत स्वतःchan अणु
	AUTOCHANNELS_DISABLED,
	AUTOCHANNELS_ENABLED,
	AUTOCHANNELS_ACTIVE,
पूर्ण;

/**
 * size_from_channelarray() - calculate the storage size of a scan
 * @channels:		the channel info array
 * @num_channels:	number of channels
 *
 * Has the side effect of filling the channels[i].location values used
 * in processing the buffer output.
 **/
अटल पूर्णांक size_from_channelarray(काष्ठा iio_channel_info *channels, पूर्णांक num_channels)
अणु
	पूर्णांक bytes = 0;
	पूर्णांक i = 0;

	जबतक (i < num_channels) अणु
		अगर (bytes % channels[i].bytes == 0)
			channels[i].location = bytes;
		अन्यथा
			channels[i].location = bytes - bytes % channels[i].bytes
					       + channels[i].bytes;

		bytes = channels[i].location + channels[i].bytes;
		i++;
	पूर्ण

	वापस bytes;
पूर्ण

अटल व्योम prपूर्णांक1byte(uपूर्णांक8_t input, काष्ठा iio_channel_info *info)
अणु
	/*
	 * Shअगरt beक्रमe conversion to aव्योम sign extension
	 * of left aligned data
	 */
	input >>= info->shअगरt;
	input &= info->mask;
	अगर (info->is_चिन्हित) अणु
		पूर्णांक8_t val = (पूर्णांक8_t)(input << (8 - info->bits_used)) >>
			     (8 - info->bits_used);
		म_लिखो("%05f ", ((भग्न)val + info->offset) * info->scale);
	पूर्ण अन्यथा अणु
		म_लिखो("%05f ", ((भग्न)input + info->offset) * info->scale);
	पूर्ण
पूर्ण

अटल व्योम prपूर्णांक2byte(uपूर्णांक16_t input, काष्ठा iio_channel_info *info)
अणु
	/* First swap अगर incorrect endian */
	अगर (info->be)
		input = be16toh(input);
	अन्यथा
		input = le16toh(input);

	/*
	 * Shअगरt beक्रमe conversion to aव्योम sign extension
	 * of left aligned data
	 */
	input >>= info->shअगरt;
	input &= info->mask;
	अगर (info->is_चिन्हित) अणु
		पूर्णांक16_t val = (पूर्णांक16_t)(input << (16 - info->bits_used)) >>
			      (16 - info->bits_used);
		म_लिखो("%05f ", ((भग्न)val + info->offset) * info->scale);
	पूर्ण अन्यथा अणु
		म_लिखो("%05f ", ((भग्न)input + info->offset) * info->scale);
	पूर्ण
पूर्ण

अटल व्योम prपूर्णांक4byte(uपूर्णांक32_t input, काष्ठा iio_channel_info *info)
अणु
	/* First swap अगर incorrect endian */
	अगर (info->be)
		input = be32toh(input);
	अन्यथा
		input = le32toh(input);

	/*
	 * Shअगरt beक्रमe conversion to aव्योम sign extension
	 * of left aligned data
	 */
	input >>= info->shअगरt;
	input &= info->mask;
	अगर (info->is_चिन्हित) अणु
		पूर्णांक32_t val = (पूर्णांक32_t)(input << (32 - info->bits_used)) >>
			      (32 - info->bits_used);
		म_लिखो("%05f ", ((भग्न)val + info->offset) * info->scale);
	पूर्ण अन्यथा अणु
		म_लिखो("%05f ", ((भग्न)input + info->offset) * info->scale);
	पूर्ण
पूर्ण

अटल व्योम prपूर्णांक8byte(uपूर्णांक64_t input, काष्ठा iio_channel_info *info)
अणु
	/* First swap अगर incorrect endian */
	अगर (info->be)
		input = be64toh(input);
	अन्यथा
		input = le64toh(input);

	/*
	 * Shअगरt beक्रमe conversion to aव्योम sign extension
	 * of left aligned data
	 */
	input >>= info->shअगरt;
	input &= info->mask;
	अगर (info->is_चिन्हित) अणु
		पूर्णांक64_t val = (पूर्णांक64_t)(input << (64 - info->bits_used)) >>
			      (64 - info->bits_used);
		/* special हाल क्रम बारtamp */
		अगर (info->scale == 1.0f && info->offset == 0.0f)
			म_लिखो("%" PRId64 " ", val);
		अन्यथा
			म_लिखो("%05f ",
			       ((भग्न)val + info->offset) * info->scale);
	पूर्ण अन्यथा अणु
		म_लिखो("%05f ", ((भग्न)input + info->offset) * info->scale);
	पूर्ण
पूर्ण

/**
 * process_scan() - prपूर्णांक out the values in SI units
 * @data:		poपूर्णांकer to the start of the scan
 * @channels:		inक्रमmation about the channels.
 *			Note: size_from_channelarray must have been called first
 *			      to fill the location offsets.
 * @num_channels:	number of channels
 **/
अटल व्योम process_scan(अक्षर *data, काष्ठा iio_channel_info *channels,
			 पूर्णांक num_channels)
अणु
	पूर्णांक k;

	क्रम (k = 0; k < num_channels; k++)
		चयन (channels[k].bytes) अणु
			/* only a few हालs implemented so far */
		हाल 1:
			prपूर्णांक1byte(*(uपूर्णांक8_t *)(data + channels[k].location),
				   &channels[k]);
			अवरोध;
		हाल 2:
			prपूर्णांक2byte(*(uपूर्णांक16_t *)(data + channels[k].location),
				   &channels[k]);
			अवरोध;
		हाल 4:
			prपूर्णांक4byte(*(uपूर्णांक32_t *)(data + channels[k].location),
				   &channels[k]);
			अवरोध;
		हाल 8:
			prपूर्णांक8byte(*(uपूर्णांक64_t *)(data + channels[k].location),
				   &channels[k]);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	म_लिखो("\n");
पूर्ण

अटल पूर्णांक enable_disable_all_channels(अक्षर *dev_dir_name, पूर्णांक buffer_idx, पूर्णांक enable)
अणु
	स्थिर काष्ठा dirent *ent;
	अक्षर scanelemdir[256];
	सूची *dp;
	पूर्णांक ret;

	snम_लिखो(scanelemdir, माप(scanelemdir),
		 FORMAT_SCAN_ELEMENTS_सूची, dev_dir_name, buffer_idx);
	scanelemdir[माप(scanelemdir)-1] = '\0';

	dp = सूची_खोलो(scanelemdir);
	अगर (!dp) अणु
		ख_लिखो(मानक_त्रुटि, "Enabling/disabling channels: can't open %s\n",
			scanelemdir);
		वापस -EIO;
	पूर्ण

	ret = -ENOENT;
	जबतक (ent = सूची_पढ़ो(dp), ent) अणु
		अगर (iioutils_check_suffix(ent->d_name, "_en")) अणु
			म_लिखो("%sabling: %s\n",
			       enable ? "En" : "Dis",
			       ent->d_name);
			ret = ग_लिखो_sysfs_पूर्णांक(ent->d_name, scanelemdir,
					      enable);
			अगर (ret < 0)
				ख_लिखो(मानक_त्रुटि, "Failed to enable/disable %s\n",
					ent->d_name);
		पूर्ण
	पूर्ण

	अगर (बंद_सूची(dp) == -1) अणु
		लिखो_त्रुटि("Enabling/disabling channels: "
		       "Failed to close directory");
		वापस -त्रुटि_सं;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम prपूर्णांक_usage(व्योम)
अणु
	ख_लिखो(मानक_त्रुटि, "Usage: generic_buffer [options]...\n"
		"Capture, convert and output data from IIO device buffer\n"
		"  -a         Auto-activate all available channels\n"
		"  -A         Force-activate ALL channels\n"
		"  -b <n>     The buffer which to open (by index), default 0\n"
		"  -c <n>     Do n conversions, or loop forever if n < 0\n"
		"  -e         Disable wait for event (new data)\n"
		"  -g         Use trigger-less mode\n"
		"  -l <n>     Set buffer length to n samples\n"
		"  --device-name -n <name>\n"
		"  --device-num -N <num>\n"
		"        Set device by name or number (mandatory)\n"
		"  --trigger-name -t <name>\n"
		"  --trigger-num -T <num>\n"
		"        Set trigger by name or number\n"
		"  -w <n>     Set delay between reads in us (event-less mode)\n");
पूर्ण

अटल क्रमागत स्वतःchan स्वतःchannels = AUTOCHANNELS_DISABLED;
अटल अक्षर *dev_dir_name = शून्य;
अटल अक्षर *buf_dir_name = शून्य;
अटल पूर्णांक buffer_idx = 0;
अटल bool current_trigger_set = false;

अटल व्योम cleanup(व्योम)
अणु
	पूर्णांक ret;

	/* Disable trigger */
	अगर (dev_dir_name && current_trigger_set) अणु
		/* Disconnect the trigger - just ग_लिखो a dummy name. */
		ret = ग_लिखो_sysfs_string("trigger/current_trigger",
					 dev_dir_name, "NULL");
		अगर (ret < 0)
			ख_लिखो(मानक_त्रुटि, "Failed to disable trigger: %s\n",
				म_त्रुटि(-ret));
		current_trigger_set = false;
	पूर्ण

	/* Disable buffer */
	अगर (buf_dir_name) अणु
		ret = ग_लिखो_sysfs_पूर्णांक("enable", buf_dir_name, 0);
		अगर (ret < 0)
			ख_लिखो(मानक_त्रुटि, "Failed to disable buffer: %s\n",
				म_त्रुटि(-ret));
	पूर्ण

	/* Disable channels अगर स्वतः-enabled */
	अगर (dev_dir_name && स्वतःchannels == AUTOCHANNELS_ACTIVE) अणु
		ret = enable_disable_all_channels(dev_dir_name, buffer_idx, 0);
		अगर (ret)
			ख_लिखो(मानक_त्रुटि, "Failed to disable all channels\n");
		स्वतःchannels = AUTOCHANNELS_DISABLED;
	पूर्ण
पूर्ण

अटल व्योम sig_handler(पूर्णांक signum)
अणु
	ख_लिखो(मानक_त्रुटि, "Caught signal %d\n", signum);
	cleanup();
	निकास(-signum);
पूर्ण

अटल व्योम रेजिस्टर_cleanup(व्योम)
अणु
	काष्ठा sigaction sa = अणु .sa_handler = sig_handler पूर्ण;
	स्थिर पूर्णांक signums[] = अणु संक_विघ्न, संक_इति, SIGABRT पूर्ण;
	पूर्णांक ret, i;

	क्रम (i = 0; i < ARRAY_SIZE(signums); ++i) अणु
		ret = sigaction(signums[i], &sa, शून्य);
		अगर (ret) अणु
			लिखो_त्रुटि("Failed to register signal handler");
			निकास(-1);
		पूर्ण
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा option दीर्घopts[] = अणु
	अणु "device-name",	1, 0, 'n' पूर्ण,
	अणु "device-num",		1, 0, 'N' पूर्ण,
	अणु "trigger-name",	1, 0, 't' पूर्ण,
	अणु "trigger-num",	1, 0, 'T' पूर्ण,
	अणु पूर्ण,
पूर्ण;

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	दीर्घ दीर्घ num_loops = 2;
	अचिन्हित दीर्घ समयdelay = 1000000;
	अचिन्हित दीर्घ buf_len = 128;

	sमाप_प्रकार i;
	अचिन्हित दीर्घ दीर्घ j;
	अचिन्हित दीर्घ toपढ़ो;
	पूर्णांक ret, c;
	काष्ठा stat st;
	पूर्णांक fd = -1;
	पूर्णांक buf_fd = -1;

	पूर्णांक num_channels = 0;
	अक्षर *trigger_name = शून्य, *device_name = शून्य;

	अक्षर *data = शून्य;
	sमाप_प्रकार पढ़ो_size;
	पूर्णांक dev_num = -1, trig_num = -1;
	अक्षर *buffer_access = शून्य;
	पूर्णांक scan_size;
	पूर्णांक noevents = 0;
	पूर्णांक notrigger = 0;
	अक्षर *dummy;
	bool क्रमce_स्वतःchannels = false;

	काष्ठा iio_channel_info *channels = शून्य;

	रेजिस्टर_cleanup();

	जबतक ((c = getopt_दीर्घ(argc, argv, "aAb:c:egl:n:N:t:T:w:?", दीर्घopts,
				शून्य)) != -1) अणु
		चयन (c) अणु
		हाल 'a':
			स्वतःchannels = AUTOCHANNELS_ENABLED;
			अवरोध;
		हाल 'A':
			स्वतःchannels = AUTOCHANNELS_ENABLED;
			क्रमce_स्वतःchannels = true;
			अवरोध;
		हाल 'b':
			त्रुटि_सं = 0;
			buffer_idx = म_से_दीर्घl(optarg, &dummy, 10);
			अगर (त्रुटि_सं) अणु
				ret = -त्रुटि_सं;
				जाओ error;
			पूर्ण
			अगर (buffer_idx < 0) अणु
				ret = -दुस्फल;
				जाओ error;
			पूर्ण

			अवरोध;
		हाल 'c':
			त्रुटि_सं = 0;
			num_loops = म_से_दीर्घl(optarg, &dummy, 10);
			अगर (त्रुटि_सं) अणु
				ret = -त्रुटि_सं;
				जाओ error;
			पूर्ण

			अवरोध;
		हाल 'e':
			noevents = 1;
			अवरोध;
		हाल 'g':
			notrigger = 1;
			अवरोध;
		हाल 'l':
			त्रुटि_सं = 0;
			buf_len = म_से_अदीर्घ(optarg, &dummy, 10);
			अगर (त्रुटि_सं) अणु
				ret = -त्रुटि_सं;
				जाओ error;
			पूर्ण

			अवरोध;
		हाल 'n':
			device_name = strdup(optarg);
			अवरोध;
		हाल 'N':
			त्रुटि_सं = 0;
			dev_num = म_से_अदीर्घ(optarg, &dummy, 10);
			अगर (त्रुटि_सं) अणु
				ret = -त्रुटि_सं;
				जाओ error;
			पूर्ण
			अवरोध;
		हाल 't':
			trigger_name = strdup(optarg);
			अवरोध;
		हाल 'T':
			त्रुटि_सं = 0;
			trig_num = म_से_अदीर्घ(optarg, &dummy, 10);
			अगर (त्रुटि_सं)
				वापस -त्रुटि_सं;
			अवरोध;
		हाल 'w':
			त्रुटि_सं = 0;
			समयdelay = म_से_अदीर्घ(optarg, &dummy, 10);
			अगर (त्रुटि_सं) अणु
				ret = -त्रुटि_सं;
				जाओ error;
			पूर्ण
			अवरोध;
		हाल '?':
			prपूर्णांक_usage();
			ret = -1;
			जाओ error;
		पूर्ण
	पूर्ण

	/* Find the device requested */
	अगर (dev_num < 0 && !device_name) अणु
		ख_लिखो(मानक_त्रुटि, "Device not set\n");
		prपूर्णांक_usage();
		ret = -1;
		जाओ error;
	पूर्ण अन्यथा अगर (dev_num >= 0 && device_name) अणु
		ख_लिखो(मानक_त्रुटि, "Only one of --device-num or --device-name needs to be set\n");
		prपूर्णांक_usage();
		ret = -1;
		जाओ error;
	पूर्ण अन्यथा अगर (dev_num < 0) अणु
		dev_num = find_type_by_name(device_name, "iio:device");
		अगर (dev_num < 0) अणु
			ख_लिखो(मानक_त्रुटि, "Failed to find the %s\n", device_name);
			ret = dev_num;
			जाओ error;
		पूर्ण
	पूर्ण
	म_लिखो("iio device number being used is %d\n", dev_num);

	ret = aप्र_लिखो(&dev_dir_name, "%siio:device%d", iio_dir, dev_num);
	अगर (ret < 0)
		वापस -ENOMEM;
	/* Fetch device_name अगर specअगरied by number */
	अगर (!device_name) अणु
		device_name = दो_स्मृति(IIO_MAX_NAME_LENGTH);
		अगर (!device_name) अणु
			ret = -ENOMEM;
			जाओ error;
		पूर्ण
		ret = पढ़ो_sysfs_string("name", dev_dir_name, device_name);
		अगर (ret < 0) अणु
			ख_लिखो(मानक_त्रुटि, "Failed to read name of device %d\n", dev_num);
			जाओ error;
		पूर्ण
	पूर्ण

	अगर (notrigger) अणु
		म_लिखो("trigger-less mode selected\n");
	पूर्ण अन्यथा अगर (trig_num >= 0) अणु
		अक्षर *trig_dev_name;
		ret = aप्र_लिखो(&trig_dev_name, "%strigger%d", iio_dir, trig_num);
		अगर (ret < 0) अणु
			वापस -ENOMEM;
		पूर्ण
		trigger_name = दो_स्मृति(IIO_MAX_NAME_LENGTH);
		ret = पढ़ो_sysfs_string("name", trig_dev_name, trigger_name);
		मुक्त(trig_dev_name);
		अगर (ret < 0) अणु
			ख_लिखो(मानक_त्रुटि, "Failed to read trigger%d name from\n", trig_num);
			वापस ret;
		पूर्ण
		म_लिखो("iio trigger number being used is %d\n", trig_num);
	पूर्ण अन्यथा अणु
		अगर (!trigger_name) अणु
			/*
			 * Build the trigger name. If it is device associated
			 * its name is <device_name>_dev[n] where n matches
			 * the device number found above.
			 */
			ret = aप्र_लिखो(&trigger_name,
				       "%s-dev%d", device_name, dev_num);
			अगर (ret < 0) अणु
				ret = -ENOMEM;
				जाओ error;
			पूर्ण
		पूर्ण

		/* Look क्रम this "-devN" trigger */
		trig_num = find_type_by_name(trigger_name, "trigger");
		अगर (trig_num < 0) अणु
			/* OK try the simpler "-trigger" suffix instead */
			मुक्त(trigger_name);
			ret = aप्र_लिखो(&trigger_name,
				       "%s-trigger", device_name);
			अगर (ret < 0) अणु
				ret = -ENOMEM;
				जाओ error;
			पूर्ण
		पूर्ण

		trig_num = find_type_by_name(trigger_name, "trigger");
		अगर (trig_num < 0) अणु
			ख_लिखो(मानक_त्रुटि, "Failed to find the trigger %s\n",
				trigger_name);
			ret = trig_num;
			जाओ error;
		पूर्ण

		म_लिखो("iio trigger number being used is %d\n", trig_num);
	पूर्ण

	/*
	 * Parse the files in scan_elements to identअगरy what channels are
	 * present
	 */
	ret = build_channel_array(dev_dir_name, buffer_idx, &channels, &num_channels);
	अगर (ret) अणु
		ख_लिखो(मानक_त्रुटि, "Problem reading scan element information\n"
			"diag %s\n", dev_dir_name);
		जाओ error;
	पूर्ण
	अगर (num_channels && स्वतःchannels == AUTOCHANNELS_ENABLED &&
	    !क्रमce_स्वतःchannels) अणु
		ख_लिखो(मानक_त्रुटि, "Auto-channels selected but some channels "
			"are already activated in sysfs\n");
		ख_लिखो(मानक_त्रुटि, "Proceeding without activating any channels\n");
	पूर्ण

	अगर ((!num_channels && स्वतःchannels == AUTOCHANNELS_ENABLED) ||
	    (स्वतःchannels == AUTOCHANNELS_ENABLED && क्रमce_स्वतःchannels)) अणु
		ख_लिखो(मानक_त्रुटि, "Enabling all channels\n");

		ret = enable_disable_all_channels(dev_dir_name, buffer_idx, 1);
		अगर (ret) अणु
			ख_लिखो(मानक_त्रुटि, "Failed to enable all channels\n");
			जाओ error;
		पूर्ण

		/* This flags that we need to disable the channels again */
		स्वतःchannels = AUTOCHANNELS_ACTIVE;

		ret = build_channel_array(dev_dir_name, buffer_idx, &channels,
					  &num_channels);
		अगर (ret) अणु
			ख_लिखो(मानक_त्रुटि, "Problem reading scan element "
				"information\n"
				"diag %s\n", dev_dir_name);
			जाओ error;
		पूर्ण
		अगर (!num_channels) अणु
			ख_लिखो(मानक_त्रुटि, "Still no channels after "
				"auto-enabling, giving up\n");
			जाओ error;
		पूर्ण
	पूर्ण

	अगर (!num_channels && स्वतःchannels == AUTOCHANNELS_DISABLED) अणु
		ख_लिखो(मानक_त्रुटि,
			"No channels are enabled, we have nothing to scan.\n");
		ख_लिखो(मानक_त्रुटि, "Enable channels manually in "
			FORMAT_SCAN_ELEMENTS_सूची
			"/*_en or pass -a to autoenable channels and "
			"try again.\n", dev_dir_name, buffer_idx);
		ret = -ENOENT;
		जाओ error;
	पूर्ण

	/*
	 * Conकाष्ठा the directory name क्रम the associated buffer.
	 * As we know that the lis3l02dq has only one buffer this may
	 * be built rather than found.
	 */
	ret = aप्र_लिखो(&buf_dir_name,
		       "%siio:device%d/buffer%d", iio_dir, dev_num, buffer_idx);
	अगर (ret < 0) अणु
		ret = -ENOMEM;
		जाओ error;
	पूर्ण

	अगर (stat(buf_dir_name, &st)) अणु
		ख_लिखो(मानक_त्रुटि, "Could not stat() '%s', got error %d: %s\n",
			buf_dir_name, त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
		ret = -त्रुटि_सं;
		जाओ error;
	पूर्ण

	अगर (!S_ISसूची(st.st_mode)) अणु
		ख_लिखो(मानक_त्रुटि, "File '%s' is not a directory\n", buf_dir_name);
		ret = -EFAULT;
		जाओ error;
	पूर्ण

	अगर (!notrigger) अणु
		म_लिखो("%s %s\n", dev_dir_name, trigger_name);
		/*
		 * Set the device trigger to be the data पढ़ोy trigger found
		 * above
		 */
		ret = ग_लिखो_sysfs_string_and_verअगरy("trigger/current_trigger",
						    dev_dir_name,
						    trigger_name);
		अगर (ret < 0) अणु
			ख_लिखो(मानक_त्रुटि,
				"Failed to write current_trigger file\n");
			जाओ error;
		पूर्ण
	पूर्ण

	ret = aप्र_लिखो(&buffer_access, "/dev/iio:device%d", dev_num);
	अगर (ret < 0) अणु
		ret = -ENOMEM;
		जाओ error;
	पूर्ण

	/* Attempt to खोलो non blocking the access dev */
	fd = खोलो(buffer_access, O_RDONLY | O_NONBLOCK);
	अगर (fd == -1) अणु /* TODO: If it isn't there make the node */
		ret = -त्रुटि_सं;
		ख_लिखो(मानक_त्रुटि, "Failed to open %s\n", buffer_access);
		जाओ error;
	पूर्ण

	/* specअगरy क्रम which buffer index we want an FD */
	buf_fd = buffer_idx;

	ret = ioctl(fd, IIO_BUFFER_GET_FD_IOCTL, &buf_fd);
	अगर (ret == -1 || buf_fd == -1) अणु
		ret = -त्रुटि_सं;
		अगर (ret == -ENODEV || ret == -EINVAL)
			ख_लिखो(मानक_त्रुटि,
				"Device does not have this many buffers\n");
		अन्यथा
			ख_लिखो(मानक_त्रुटि, "Failed to retrieve buffer fd\n");

		जाओ error;
	पूर्ण

	/* Setup ring buffer parameters */
	ret = ग_लिखो_sysfs_पूर्णांक("length", buf_dir_name, buf_len);
	अगर (ret < 0)
		जाओ error;

	/* Enable the buffer */
	ret = ग_लिखो_sysfs_पूर्णांक("enable", buf_dir_name, 1);
	अगर (ret < 0) अणु
		ख_लिखो(मानक_त्रुटि,
			"Failed to enable buffer '%s': %s\n",
			buf_dir_name, म_त्रुटि(-ret));
		जाओ error;
	पूर्ण

	scan_size = size_from_channelarray(channels, num_channels);
	data = दो_स्मृति(scan_size * buf_len);
	अगर (!data) अणु
		ret = -ENOMEM;
		जाओ error;
	पूर्ण

	/**
	 * This check is being करोne here क्रम sanity reasons, however it
	 * should be omitted under normal operation.
	 * If this is buffer0, we check that we get EBUSY after this poपूर्णांक.
	 */
	अगर (buffer_idx == 0) अणु
		त्रुटि_सं = 0;
		पढ़ो_size = पढ़ो(fd, data, 1);
		अगर (पढ़ो_size > -1 || त्रुटि_सं != EBUSY) अणु
			ret = -EFAULT;
			लिखो_त्रुटि("Reading from '%s' should not be possible after ioctl()");
			जाओ error;
		पूर्ण
	पूर्ण

	/* बंद now the मुख्य अक्षरdev FD and let the buffer FD work */
	अगर (बंद(fd) == -1)
		लिखो_त्रुटि("Failed to close character device file");
	fd = -1;

	क्रम (j = 0; j < num_loops || num_loops < 0; j++) अणु
		अगर (!noevents) अणु
			काष्ठा pollfd pfd = अणु
				.fd = buf_fd,
				.events = POLLIN,
			पूर्ण;

			ret = poll(&pfd, 1, -1);
			अगर (ret < 0) अणु
				ret = -त्रुटि_सं;
				जाओ error;
			पूर्ण अन्यथा अगर (ret == 0) अणु
				जारी;
			पूर्ण

			toपढ़ो = buf_len;
		पूर्ण अन्यथा अणु
			usleep(समयdelay);
			toपढ़ो = 64;
		पूर्ण

		पढ़ो_size = पढ़ो(buf_fd, data, toपढ़ो * scan_size);
		अगर (पढ़ो_size < 0) अणु
			अगर (त्रुटि_सं == EAGAIN) अणु
				ख_लिखो(मानक_त्रुटि, "nothing available\n");
				जारी;
			पूर्ण अन्यथा अणु
				अवरोध;
			पूर्ण
		पूर्ण
		क्रम (i = 0; i < पढ़ो_size / scan_size; i++)
			process_scan(data + scan_size * i, channels,
				     num_channels);
	पूर्ण

error:
	cleanup();

	अगर (fd >= 0 && बंद(fd) == -1)
		लिखो_त्रुटि("Failed to close character device");
	अगर (buf_fd >= 0 && बंद(buf_fd) == -1)
		लिखो_त्रुटि("Failed to close buffer");
	मुक्त(buffer_access);
	मुक्त(data);
	मुक्त(buf_dir_name);
	क्रम (i = num_channels - 1; i >= 0; i--) अणु
		मुक्त(channels[i].name);
		मुक्त(channels[i].generic_name);
	पूर्ण
	मुक्त(channels);
	मुक्त(trigger_name);
	मुक्त(device_name);
	मुक्त(dev_dir_name);

	वापस ret;
पूर्ण
