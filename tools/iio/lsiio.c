<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Industrial I/O utilities - lsiio.c
 *
 * Copyright (c) 2010 Manuel Stahl <manuel.stahl@iis.fraunhofer.de>
 */

#समावेश <माला.स>
#समावेश <dirent.h>
#समावेश <मानकपन.स>
#समावेश <त्रुटिसं.स>
#समावेश <मानक_निवेशt.h>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/सूची.स>
#समावेश "iio_utils.h"

अटल क्रमागत verbosity अणु
	VERBLEVEL_DEFAULT,	/* 0 gives lspci behaviour */
	VERBLEVEL_SENSORS,	/* 1 lists sensors */
पूर्ण verblevel = VERBLEVEL_DEFAULT;

स्थिर अक्षर *type_device = "iio:device";
स्थिर अक्षर *type_trigger = "trigger";

अटल अंतरभूत पूर्णांक check_prefix(स्थिर अक्षर *str, स्थिर अक्षर *prefix)
अणु
	वापस म_माप(str) > म_माप(prefix) &&
	       म_भेदन(str, prefix, म_माप(prefix)) == 0;
पूर्ण

अटल अंतरभूत पूर्णांक check_postfix(स्थिर अक्षर *str, स्थिर अक्षर *postfix)
अणु
	वापस म_माप(str) > म_माप(postfix) &&
	       म_भेद(str + म_माप(str) - म_माप(postfix), postfix) == 0;
पूर्ण

अटल पूर्णांक dump_channels(स्थिर अक्षर *dev_dir_name)
अणु
	सूची *dp;
	स्थिर काष्ठा dirent *ent;

	dp = सूची_खोलो(dev_dir_name);
	अगर (!dp)
		वापस -त्रुटि_सं;

	जबतक (ent = सूची_पढ़ो(dp), ent)
		अगर (check_prefix(ent->d_name, "in_") &&
		   (check_postfix(ent->d_name, "_raw") ||
		    check_postfix(ent->d_name, "_input")))
			म_लिखो("   %-10s\n", ent->d_name);

	वापस (बंद_सूची(dp) == -1) ? -त्रुटि_सं : 0;
पूर्ण

अटल पूर्णांक dump_one_device(स्थिर अक्षर *dev_dir_name)
अणु
	अक्षर name[IIO_MAX_NAME_LENGTH];
	पूर्णांक dev_idx;
	पूर्णांक ret;

	ret = माला_पूछो(dev_dir_name + म_माप(iio_dir) + म_माप(type_device), "%i",
		     &dev_idx);
	अगर (ret != 1)
		वापस -EINVAL;

	ret = पढ़ो_sysfs_string("name", dev_dir_name, name);
	अगर (ret < 0)
		वापस ret;

	म_लिखो("Device %03d: %s\n", dev_idx, name);

	अगर (verblevel >= VERBLEVEL_SENSORS)
		वापस dump_channels(dev_dir_name);

	वापस 0;
पूर्ण

अटल पूर्णांक dump_one_trigger(स्थिर अक्षर *dev_dir_name)
अणु
	अक्षर name[IIO_MAX_NAME_LENGTH];
	पूर्णांक dev_idx;
	पूर्णांक ret;

	ret = माला_पूछो(dev_dir_name + म_माप(iio_dir) + म_माप(type_trigger),
		     "%i", &dev_idx);
	अगर (ret != 1)
		वापस -EINVAL;

	ret = पढ़ो_sysfs_string("name", dev_dir_name, name);
	अगर (ret < 0)
		वापस ret;

	म_लिखो("Trigger %03d: %s\n", dev_idx, name);

	वापस 0;
पूर्ण

अटल पूर्णांक dump_devices(व्योम)
अणु
	स्थिर काष्ठा dirent *ent;
	पूर्णांक ret;
	सूची *dp;

	dp = सूची_खोलो(iio_dir);
	अगर (!dp) अणु
		ख_लिखो(मानक_त्रुटि, "No industrial I/O devices available\n");
		वापस -ENODEV;
	पूर्ण

	जबतक (ent = सूची_पढ़ो(dp), ent) अणु
		अगर (check_prefix(ent->d_name, type_device)) अणु
			अक्षर *dev_dir_name;

			अगर (aप्र_लिखो(&dev_dir_name, "%s%s", iio_dir,
				     ent->d_name) < 0) अणु
				ret = -ENOMEM;
				जाओ error_बंद_dir;
			पूर्ण

			ret = dump_one_device(dev_dir_name);
			अगर (ret) अणु
				मुक्त(dev_dir_name);
				जाओ error_बंद_dir;
			पूर्ण

			मुक्त(dev_dir_name);
			अगर (verblevel >= VERBLEVEL_SENSORS)
				म_लिखो("\n");
		पूर्ण
	पूर्ण
	सूची_शुरु(dp);
	जबतक (ent = सूची_पढ़ो(dp), ent) अणु
		अगर (check_prefix(ent->d_name, type_trigger)) अणु
			अक्षर *dev_dir_name;

			अगर (aप्र_लिखो(&dev_dir_name, "%s%s", iio_dir,
				     ent->d_name) < 0) अणु
				ret = -ENOMEM;
				जाओ error_बंद_dir;
			पूर्ण

			ret = dump_one_trigger(dev_dir_name);
			अगर (ret) अणु
				मुक्त(dev_dir_name);
				जाओ error_बंद_dir;
			पूर्ण

			मुक्त(dev_dir_name);
		पूर्ण
	पूर्ण

	वापस (बंद_सूची(dp) == -1) ? -त्रुटि_सं : 0;

error_बंद_dir:
	अगर (बंद_सूची(dp) == -1)
		लिखो_त्रुटि("dump_devices(): Failed to close directory");

	वापस ret;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक c, err = 0;

	जबतक ((c = getopt(argc, argv, "v")) != खातापूर्ण) अणु
		चयन (c) अणु
		हाल 'v':
			verblevel++;
			अवरोध;

		हाल '?':
		शेष:
			err++;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (err || argc > optind) अणु
		ख_लिखो(मानक_त्रुटि, "Usage: lsiio [options]...\n"
			"List industrial I/O devices\n"
			"  -v  Increase verbosity (may be given multiple times)\n");
		निकास(1);
	पूर्ण

	वापस dump_devices();
पूर्ण
