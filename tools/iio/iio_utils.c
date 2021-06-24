<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* IIO - useful set of util functionality
 *
 * Copyright (c) 2008 Jonathan Cameron
 */
#समावेश <माला.स>
#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश <मानक_निवेशt.h>
#समावेश <dirent.h>
#समावेश <त्रुटिसं.स>
#समावेश <प्रकार.स>
#समावेश "iio_utils.h"

स्थिर अक्षर *iio_dir = "/sys/bus/iio/devices/";

अटल अक्षर * स्थिर iio_direction[] = अणु
	"in",
	"out",
पूर्ण;

/**
 * iioutils_अवरोध_up_name() - extract generic name from full channel name
 * @full_name: the full channel name
 * @generic_name: the output generic channel name
 *
 * Returns 0 on success, or a negative error code अगर string extraction failed.
 **/
पूर्णांक iioutils_अवरोध_up_name(स्थिर अक्षर *full_name, अक्षर **generic_name)
अणु
	अक्षर *current;
	अक्षर *w, *r;
	अक्षर *working, *prefix = "";
	पूर्णांक i, ret;

	क्रम (i = 0; i < ARRAY_SIZE(iio_direction); i++)
		अगर (!म_भेदन(full_name, iio_direction[i],
			     म_माप(iio_direction[i]))) अणु
			prefix = iio_direction[i];
			अवरोध;
		पूर्ण

	current = strdup(full_name + म_माप(prefix) + 1);
	अगर (!current)
		वापस -ENOMEM;

	working = म_मोहर(current, "_\0");
	अगर (!working) अणु
		मुक्त(current);
		वापस -EINVAL;
	पूर्ण

	w = working;
	r = working;

	जबतक (*r != '\0') अणु
		अगर (!है_अंक(*r)) अणु
			*w = *r;
			w++;
		पूर्ण

		r++;
	पूर्ण
	*w = '\0';
	ret = aप्र_लिखो(generic_name, "%s_%s", prefix, working);
	मुक्त(current);

	वापस (ret == -1) ? -ENOMEM : 0;
पूर्ण

/**
 * iioutils_get_type() - find and process _type attribute data
 * @is_चिन्हित: output whether channel is चिन्हित
 * @bytes: output how many bytes the channel storage occupies
 * @bits_used: output number of valid bits of data
 * @shअगरt: output amount of bits to shअगरt right data beक्रमe applying bit mask
 * @mask: output a bit mask क्रम the raw data
 * @be: output अगर data in big endian
 * @device_dir: the IIO device directory
 * @buffer_idx: the IIO buffer index
 * @name: the channel name
 * @generic_name: the channel type name
 *
 * Returns a value >= 0 on success, otherwise a negative error code.
 **/
अटल पूर्णांक iioutils_get_type(अचिन्हित पूर्णांक *is_चिन्हित, अचिन्हित पूर्णांक *bytes,
			     अचिन्हित पूर्णांक *bits_used, अचिन्हित पूर्णांक *shअगरt,
			     uपूर्णांक64_t *mask, अचिन्हित पूर्णांक *be,
			     स्थिर अक्षर *device_dir, पूर्णांक buffer_idx,
			     स्थिर अक्षर *name, स्थिर अक्षर *generic_name)
अणु
	खाता *sysfsfp;
	पूर्णांक ret;
	सूची *dp;
	अक्षर *scan_el_dir, *builtname, *builtname_generic, *filename = 0;
	अक्षर signअक्षर, endianअक्षर;
	अचिन्हित padपूर्णांक;
	स्थिर काष्ठा dirent *ent;

	ret = aप्र_लिखो(&scan_el_dir, FORMAT_SCAN_ELEMENTS_सूची, device_dir, buffer_idx);
	अगर (ret < 0)
		वापस -ENOMEM;

	ret = aप्र_लिखो(&builtname, FORMAT_TYPE_खाता, name);
	अगर (ret < 0) अणु
		ret = -ENOMEM;
		जाओ error_मुक्त_scan_el_dir;
	पूर्ण
	ret = aप्र_लिखो(&builtname_generic, FORMAT_TYPE_खाता, generic_name);
	अगर (ret < 0) अणु
		ret = -ENOMEM;
		जाओ error_मुक्त_builtname;
	पूर्ण

	dp = सूची_खोलो(scan_el_dir);
	अगर (!dp) अणु
		ret = -त्रुटि_सं;
		जाओ error_मुक्त_builtname_generic;
	पूर्ण

	ret = -ENOENT;
	जबतक (ent = सूची_पढ़ो(dp), ent)
		अगर ((म_भेद(builtname, ent->d_name) == 0) ||
		    (म_भेद(builtname_generic, ent->d_name) == 0)) अणु
			ret = aप्र_लिखो(&filename,
				       "%s/%s", scan_el_dir, ent->d_name);
			अगर (ret < 0) अणु
				ret = -ENOMEM;
				जाओ error_बंद_सूची;
			पूर्ण

			sysfsfp = ख_खोलो(filename, "r");
			अगर (!sysfsfp) अणु
				ret = -त्रुटि_सं;
				ख_लिखो(मानक_त्रुटि, "failed to open %s\n",
					filename);
				जाओ error_मुक्त_filename;
			पूर्ण

			ret = ख_पूछो(sysfsfp,
				     "%ce:%c%u/%u>>%u",
				     &endianअक्षर,
				     &signअक्षर,
				     bits_used,
				     &padपूर्णांक, shअगरt);
			अगर (ret < 0) अणु
				ret = -त्रुटि_सं;
				ख_लिखो(मानक_त्रुटि,
					"failed to pass scan type description\n");
				जाओ error_बंद_sysfsfp;
			पूर्ण अन्यथा अगर (ret != 5) अणु
				ret = -EIO;
				ख_लिखो(मानक_त्रुटि,
					"scan type description didn't match\n");
				जाओ error_बंद_sysfsfp;
			पूर्ण

			*be = (endianअक्षर == 'b');
			*bytes = padपूर्णांक / 8;
			अगर (*bits_used == 64)
				*mask = ~(0ULL);
			अन्यथा
				*mask = (1ULL << *bits_used) - 1ULL;

			*is_चिन्हित = (signअक्षर == 's');
			अगर (ख_बंद(sysfsfp)) अणु
				ret = -त्रुटि_सं;
				ख_लिखो(मानक_त्रुटि, "Failed to close %s\n",
					filename);
				जाओ error_मुक्त_filename;
			पूर्ण

			sysfsfp = 0;
			मुक्त(filename);
			filename = 0;

			/*
			 * Aव्योम having a more generic entry overwriting
			 * the settings.
			 */
			अगर (म_भेद(builtname, ent->d_name) == 0)
				अवरोध;
		पूर्ण

error_बंद_sysfsfp:
	अगर (sysfsfp)
		अगर (ख_बंद(sysfsfp))
			लिखो_त्रुटि("iioutils_get_type(): Failed to close file");

error_मुक्त_filename:
	अगर (filename)
		मुक्त(filename);

error_बंद_सूची:
	अगर (बंद_सूची(dp) == -1)
		लिखो_त्रुटि("iioutils_get_type(): Failed to close directory");

error_मुक्त_builtname_generic:
	मुक्त(builtname_generic);
error_मुक्त_builtname:
	मुक्त(builtname);
error_मुक्त_scan_el_dir:
	मुक्त(scan_el_dir);

	वापस ret;
पूर्ण

/**
 * iioutils_get_param_भग्न() - पढ़ो a भग्न value from a channel parameter
 * @output: output the भग्न value
 * @param_name: the parameter name to पढ़ो
 * @device_dir: the IIO device directory in sysfs
 * @name: the channel name
 * @generic_name: the channel type name
 *
 * Returns a value >= 0 on success, otherwise a negative error code.
 **/
पूर्णांक iioutils_get_param_भग्न(भग्न *output, स्थिर अक्षर *param_name,
			     स्थिर अक्षर *device_dir, स्थिर अक्षर *name,
			     स्थिर अक्षर *generic_name)
अणु
	खाता *sysfsfp;
	पूर्णांक ret;
	सूची *dp;
	अक्षर *builtname, *builtname_generic;
	अक्षर *filename = शून्य;
	स्थिर काष्ठा dirent *ent;

	ret = aप्र_लिखो(&builtname, "%s_%s", name, param_name);
	अगर (ret < 0)
		वापस -ENOMEM;

	ret = aप्र_लिखो(&builtname_generic,
		       "%s_%s", generic_name, param_name);
	अगर (ret < 0) अणु
		ret = -ENOMEM;
		जाओ error_मुक्त_builtname;
	पूर्ण

	dp = सूची_खोलो(device_dir);
	अगर (!dp) अणु
		ret = -त्रुटि_सं;
		जाओ error_मुक्त_builtname_generic;
	पूर्ण

	ret = -ENOENT;
	जबतक (ent = सूची_पढ़ो(dp), ent)
		अगर ((म_भेद(builtname, ent->d_name) == 0) ||
		    (म_भेद(builtname_generic, ent->d_name) == 0)) अणु
			ret = aप्र_लिखो(&filename,
				       "%s/%s", device_dir, ent->d_name);
			अगर (ret < 0) अणु
				ret = -ENOMEM;
				जाओ error_बंद_सूची;
			पूर्ण

			sysfsfp = ख_खोलो(filename, "r");
			अगर (!sysfsfp) अणु
				ret = -त्रुटि_सं;
				जाओ error_मुक्त_filename;
			पूर्ण

			त्रुटि_सं = 0;
			अगर (ख_पूछो(sysfsfp, "%f", output) != 1)
				ret = त्रुटि_सं ? -त्रुटि_सं : -ENODATA;

			अवरोध;
		पूर्ण
error_मुक्त_filename:
	अगर (filename)
		मुक्त(filename);

error_बंद_सूची:
	अगर (बंद_सूची(dp) == -1)
		लिखो_त्रुटि("iioutils_get_param_float(): Failed to close directory");

error_मुक्त_builtname_generic:
	मुक्त(builtname_generic);
error_मुक्त_builtname:
	मुक्त(builtname);

	वापस ret;
पूर्ण

/**
 * bsort_channel_array_by_index() - sort the array in index order
 * @ci_array: the iio_channel_info array to be sorted
 * @cnt: the amount of array elements
 **/

व्योम bsort_channel_array_by_index(काष्ठा iio_channel_info *ci_array, पूर्णांक cnt)
अणु
	काष्ठा iio_channel_info temp;
	पूर्णांक x, y;

	क्रम (x = 0; x < cnt; x++)
		क्रम (y = 0; y < (cnt - 1); y++)
			अगर (ci_array[y].index > ci_array[y + 1].index) अणु
				temp = ci_array[y + 1];
				ci_array[y + 1] = ci_array[y];
				ci_array[y] = temp;
			पूर्ण
पूर्ण

/**
 * build_channel_array() - function to figure out what channels are present
 * @device_dir: the IIO device directory in sysfs
 * @buffer_idx: the IIO buffer क्रम this channel array
 * @ci_array: output the resulting array of iio_channel_info
 * @counter: output the amount of array elements
 *
 * Returns 0 on success, otherwise a negative error code.
 **/
पूर्णांक build_channel_array(स्थिर अक्षर *device_dir, पूर्णांक buffer_idx,
			काष्ठा iio_channel_info **ci_array, पूर्णांक *counter)
अणु
	सूची *dp;
	खाता *sysfsfp;
	पूर्णांक count = 0, i;
	काष्ठा iio_channel_info *current;
	पूर्णांक ret;
	स्थिर काष्ठा dirent *ent;
	अक्षर *scan_el_dir;
	अक्षर *filename;

	*counter = 0;
	ret = aप्र_लिखो(&scan_el_dir, FORMAT_SCAN_ELEMENTS_सूची, device_dir, buffer_idx);
	अगर (ret < 0)
		वापस -ENOMEM;

	dp = सूची_खोलो(scan_el_dir);
	अगर (!dp) अणु
		ret = -त्रुटि_सं;
		जाओ error_मुक्त_name;
	पूर्ण

	जबतक (ent = सूची_पढ़ो(dp), ent)
		अगर (म_भेद(ent->d_name + म_माप(ent->d_name) - म_माप("_en"),
			   "_en") == 0) अणु
			ret = aप्र_लिखो(&filename,
				       "%s/%s", scan_el_dir, ent->d_name);
			अगर (ret < 0) अणु
				ret = -ENOMEM;
				जाओ error_बंद_dir;
			पूर्ण

			sysfsfp = ख_खोलो(filename, "r");
			अगर (!sysfsfp) अणु
				ret = -त्रुटि_सं;
				मुक्त(filename);
				जाओ error_बंद_dir;
			पूर्ण

			त्रुटि_सं = 0;
			अगर (ख_पूछो(sysfsfp, "%i", &ret) != 1) अणु
				ret = त्रुटि_सं ? -त्रुटि_सं : -ENODATA;
				अगर (ख_बंद(sysfsfp))
					लिखो_त्रुटि("build_channel_array(): Failed to close file");

				मुक्त(filename);
				जाओ error_बंद_dir;
			पूर्ण
			अगर (ret == 1)
				(*counter)++;

			अगर (ख_बंद(sysfsfp)) अणु
				ret = -त्रुटि_सं;
				मुक्त(filename);
				जाओ error_बंद_dir;
			पूर्ण

			मुक्त(filename);
		पूर्ण

	*ci_array = दो_स्मृति(माप(**ci_array) * (*counter));
	अगर (!*ci_array) अणु
		ret = -ENOMEM;
		जाओ error_बंद_dir;
	पूर्ण

	seekdir(dp, 0);
	जबतक (ent = सूची_पढ़ो(dp), ent) अणु
		अगर (म_भेद(ent->d_name + म_माप(ent->d_name) - म_माप("_en"),
			   "_en") == 0) अणु
			पूर्णांक current_enabled = 0;

			current = &(*ci_array)[count++];
			ret = aप्र_लिखो(&filename,
				       "%s/%s", scan_el_dir, ent->d_name);
			अगर (ret < 0) अणु
				ret = -ENOMEM;
				/* decrement count to aव्योम मुक्तing name */
				count--;
				जाओ error_cleanup_array;
			पूर्ण

			sysfsfp = ख_खोलो(filename, "r");
			अगर (!sysfsfp) अणु
				ret = -त्रुटि_सं;
				मुक्त(filename);
				count--;
				जाओ error_cleanup_array;
			पूर्ण

			त्रुटि_सं = 0;
			अगर (ख_पूछो(sysfsfp, "%i", &current_enabled) != 1) अणु
				ret = त्रुटि_सं ? -त्रुटि_सं : -ENODATA;
				मुक्त(filename);
				count--;
				जाओ error_cleanup_array;
			पूर्ण

			अगर (ख_बंद(sysfsfp)) अणु
				ret = -त्रुटि_सं;
				मुक्त(filename);
				count--;
				जाओ error_cleanup_array;
			पूर्ण

			अगर (!current_enabled) अणु
				मुक्त(filename);
				count--;
				जारी;
			पूर्ण

			current->scale = 1.0;
			current->offset = 0;
			current->name = strndup(ent->d_name,
						म_माप(ent->d_name) -
						म_माप("_en"));
			अगर (!current->name) अणु
				मुक्त(filename);
				ret = -ENOMEM;
				count--;
				जाओ error_cleanup_array;
			पूर्ण

			/* Get the generic and specअगरic name elements */
			ret = iioutils_अवरोध_up_name(current->name,
						     &current->generic_name);
			अगर (ret) अणु
				मुक्त(filename);
				मुक्त(current->name);
				count--;
				जाओ error_cleanup_array;
			पूर्ण

			ret = aप्र_लिखो(&filename,
				       "%s/%s_index",
				       scan_el_dir,
				       current->name);
			अगर (ret < 0) अणु
				मुक्त(filename);
				ret = -ENOMEM;
				जाओ error_cleanup_array;
			पूर्ण

			sysfsfp = ख_खोलो(filename, "r");
			अगर (!sysfsfp) अणु
				ret = -त्रुटि_सं;
				ख_लिखो(मानक_त्रुटि, "failed to open %s\n",
					filename);
				मुक्त(filename);
				जाओ error_cleanup_array;
			पूर्ण

			त्रुटि_सं = 0;
			अगर (ख_पूछो(sysfsfp, "%u", &current->index) != 1) अणु
				ret = त्रुटि_सं ? -त्रुटि_सं : -ENODATA;
				अगर (ख_बंद(sysfsfp))
					लिखो_त्रुटि("build_channel_array(): Failed to close file");

				मुक्त(filename);
				जाओ error_cleanup_array;
			पूर्ण

			अगर (ख_बंद(sysfsfp)) अणु
				ret = -त्रुटि_सं;
				मुक्त(filename);
				जाओ error_cleanup_array;
			पूर्ण

			मुक्त(filename);
			/* Find the scale */
			ret = iioutils_get_param_भग्न(&current->scale,
						       "scale",
						       device_dir,
						       current->name,
						       current->generic_name);
			अगर ((ret < 0) && (ret != -ENOENT))
				जाओ error_cleanup_array;

			ret = iioutils_get_param_भग्न(&current->offset,
						       "offset",
						       device_dir,
						       current->name,
						       current->generic_name);
			अगर ((ret < 0) && (ret != -ENOENT))
				जाओ error_cleanup_array;

			ret = iioutils_get_type(&current->is_चिन्हित,
						&current->bytes,
						&current->bits_used,
						&current->shअगरt,
						&current->mask,
						&current->be,
						device_dir,
						buffer_idx,
						current->name,
						current->generic_name);
			अगर (ret < 0)
				जाओ error_cleanup_array;
		पूर्ण
	पूर्ण

	अगर (बंद_सूची(dp) == -1) अणु
		ret = -त्रुटि_सं;
		जाओ error_cleanup_array;
	पूर्ण

	मुक्त(scan_el_dir);
	/* reorder so that the array is in index order */
	bsort_channel_array_by_index(*ci_array, *counter);

	वापस 0;

error_cleanup_array:
	क्रम (i = count - 1;  i >= 0; i--) अणु
		मुक्त((*ci_array)[i].name);
		मुक्त((*ci_array)[i].generic_name);
	पूर्ण
	मुक्त(*ci_array);
	*ci_array = शून्य;
	*counter = 0;
error_बंद_dir:
	अगर (dp)
		अगर (बंद_सूची(dp) == -1)
			लिखो_त्रुटि("build_channel_array(): Failed to close dir");

error_मुक्त_name:
	मुक्त(scan_el_dir);

	वापस ret;
पूर्ण

अटल पूर्णांक calc_digits(पूर्णांक num)
अणु
	पूर्णांक count = 0;

	जबतक (num != 0) अणु
		num /= 10;
		count++;
	पूर्ण

	वापस count;
पूर्ण

/**
 * find_type_by_name() - function to match top level types by name
 * @name: top level type instance name
 * @type: the type of top level instance being searched
 *
 * Returns the device number of a matched IIO device on success, otherwise a
 * negative error code.
 * Typical types this is used क्रम are device and trigger.
 **/
पूर्णांक find_type_by_name(स्थिर अक्षर *name, स्थिर अक्षर *type)
अणु
	स्थिर काष्ठा dirent *ent;
	पूर्णांक number, numम_माप, ret;

	खाता *namefp;
	सूची *dp;
	अक्षर thisname[IIO_MAX_NAME_LENGTH];
	अक्षर *filename;

	dp = सूची_खोलो(iio_dir);
	अगर (!dp) अणु
		ख_लिखो(मानक_त्रुटि, "No industrialio devices available\n");
		वापस -ENODEV;
	पूर्ण

	जबतक (ent = सूची_पढ़ो(dp), ent) अणु
		अगर (म_भेद(ent->d_name, ".") != 0 &&
		    म_भेद(ent->d_name, "..") != 0 &&
		    म_माप(ent->d_name) > म_माप(type) &&
		    म_भेदन(ent->d_name, type, म_माप(type)) == 0) अणु
			त्रुटि_सं = 0;
			ret = माला_पूछो(ent->d_name + म_माप(type), "%d", &number);
			अगर (ret < 0) अणु
				ret = -त्रुटि_सं;
				ख_लिखो(मानक_त्रुटि,
					"failed to read element number\n");
				जाओ error_बंद_dir;
			पूर्ण अन्यथा अगर (ret != 1) अणु
				ret = -EIO;
				ख_लिखो(मानक_त्रुटि,
					"failed to match element number\n");
				जाओ error_बंद_dir;
			पूर्ण

			numम_माप = calc_digits(number);
			/* verअगरy the next अक्षरacter is not a colon */
			अगर (म_भेदन(ent->d_name + म_माप(type) + numम_माप,
			    ":", 1) != 0) अणु
				filename = दो_स्मृति(म_माप(iio_dir) + म_माप(type)
						  + numम_माप + 6);
				अगर (!filename) अणु
					ret = -ENOMEM;
					जाओ error_बंद_dir;
				पूर्ण

				ret = प्र_लिखो(filename, "%s%s%d/name", iio_dir,
					      type, number);
				अगर (ret < 0) अणु
					मुक्त(filename);
					जाओ error_बंद_dir;
				पूर्ण

				namefp = ख_खोलो(filename, "r");
				अगर (!namefp) अणु
					मुक्त(filename);
					जारी;
				पूर्ण

				मुक्त(filename);
				त्रुटि_सं = 0;
				अगर (ख_पूछो(namefp, "%s", thisname) != 1) अणु
					ret = त्रुटि_सं ? -त्रुटि_सं : -ENODATA;
					जाओ error_बंद_dir;
				पूर्ण

				अगर (ख_बंद(namefp)) अणु
					ret = -त्रुटि_सं;
					जाओ error_बंद_dir;
				पूर्ण

				अगर (म_भेद(name, thisname) == 0) अणु
					अगर (बंद_सूची(dp) == -1)
						वापस -त्रुटि_सं;

					वापस number;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (बंद_सूची(dp) == -1)
		वापस -त्रुटि_सं;

	वापस -ENODEV;

error_बंद_dir:
	अगर (बंद_सूची(dp) == -1)
		लिखो_त्रुटि("find_type_by_name(): Failed to close directory");

	वापस ret;
पूर्ण

अटल पूर्णांक _ग_लिखो_sysfs_पूर्णांक(स्थिर अक्षर *filename, स्थिर अक्षर *basedir, पूर्णांक val,
			    पूर्णांक verअगरy)
अणु
	पूर्णांक ret = 0;
	खाता *sysfsfp;
	पूर्णांक test;
	अक्षर *temp = दो_स्मृति(म_माप(basedir) + म_माप(filename) + 2);

	अगर (!temp)
		वापस -ENOMEM;

	ret = प्र_लिखो(temp, "%s/%s", basedir, filename);
	अगर (ret < 0)
		जाओ error_मुक्त;

	sysfsfp = ख_खोलो(temp, "w");
	अगर (!sysfsfp) अणु
		ret = -त्रुटि_सं;
		ख_लिखो(मानक_त्रुटि, "failed to open %s\n", temp);
		जाओ error_मुक्त;
	पूर्ण

	ret = ख_लिखो(sysfsfp, "%d", val);
	अगर (ret < 0) अणु
		अगर (ख_बंद(sysfsfp))
			लिखो_त्रुटि("_write_sysfs_int(): Failed to close dir");

		जाओ error_मुक्त;
	पूर्ण

	अगर (ख_बंद(sysfsfp)) अणु
		ret = -त्रुटि_सं;
		जाओ error_मुक्त;
	पूर्ण

	अगर (verअगरy) अणु
		sysfsfp = ख_खोलो(temp, "r");
		अगर (!sysfsfp) अणु
			ret = -त्रुटि_सं;
			ख_लिखो(मानक_त्रुटि, "failed to open %s\n", temp);
			जाओ error_मुक्त;
		पूर्ण

		अगर (ख_पूछो(sysfsfp, "%d", &test) != 1) अणु
			ret = त्रुटि_सं ? -त्रुटि_सं : -ENODATA;
			अगर (ख_बंद(sysfsfp))
				लिखो_त्रुटि("_write_sysfs_int(): Failed to close dir");

			जाओ error_मुक्त;
		पूर्ण

		अगर (ख_बंद(sysfsfp)) अणु
			ret = -त्रुटि_सं;
			जाओ error_मुक्त;
		पूर्ण

		अगर (test != val) अणु
			ख_लिखो(मानक_त्रुटि,
				"Possible failure in int write %d to %s/%s\n",
				val, basedir, filename);
			ret = -1;
		पूर्ण
	पूर्ण

error_मुक्त:
	मुक्त(temp);
	वापस ret;
पूर्ण

/**
 * ग_लिखो_sysfs_पूर्णांक() - ग_लिखो an पूर्णांकeger value to a sysfs file
 * @filename: name of the file to ग_लिखो to
 * @basedir: the sysfs directory in which the file is to be found
 * @val: पूर्णांकeger value to ग_लिखो to file
 *
 * Returns a value >= 0 on success, otherwise a negative error code.
 **/
पूर्णांक ग_लिखो_sysfs_पूर्णांक(स्थिर अक्षर *filename, स्थिर अक्षर *basedir, पूर्णांक val)
अणु
	वापस _ग_लिखो_sysfs_पूर्णांक(filename, basedir, val, 0);
पूर्ण

/**
 * ग_लिखो_sysfs_पूर्णांक_and_verअगरy() - ग_लिखो an पूर्णांकeger value to a sysfs file
 *				  and verअगरy
 * @filename: name of the file to ग_लिखो to
 * @basedir: the sysfs directory in which the file is to be found
 * @val: पूर्णांकeger value to ग_लिखो to file
 *
 * Returns a value >= 0 on success, otherwise a negative error code.
 **/
पूर्णांक ग_लिखो_sysfs_पूर्णांक_and_verअगरy(स्थिर अक्षर *filename, स्थिर अक्षर *basedir,
			       पूर्णांक val)
अणु
	वापस _ग_लिखो_sysfs_पूर्णांक(filename, basedir, val, 1);
पूर्ण

अटल पूर्णांक _ग_लिखो_sysfs_string(स्थिर अक्षर *filename, स्थिर अक्षर *basedir,
			       स्थिर अक्षर *val, पूर्णांक verअगरy)
अणु
	पूर्णांक ret = 0;
	खाता  *sysfsfp;
	अक्षर *temp = दो_स्मृति(म_माप(basedir) + म_माप(filename) + 2);

	अगर (!temp) अणु
		ख_लिखो(मानक_त्रुटि, "Memory allocation failed\n");
		वापस -ENOMEM;
	पूर्ण

	ret = प्र_लिखो(temp, "%s/%s", basedir, filename);
	अगर (ret < 0)
		जाओ error_मुक्त;

	sysfsfp = ख_खोलो(temp, "w");
	अगर (!sysfsfp) अणु
		ret = -त्रुटि_सं;
		ख_लिखो(मानक_त्रुटि, "Could not open %s\n", temp);
		जाओ error_मुक्त;
	पूर्ण

	ret = ख_लिखो(sysfsfp, "%s", val);
	अगर (ret < 0) अणु
		अगर (ख_बंद(sysfsfp))
			लिखो_त्रुटि("_write_sysfs_string(): Failed to close dir");

		जाओ error_मुक्त;
	पूर्ण

	अगर (ख_बंद(sysfsfp)) अणु
		ret = -त्रुटि_सं;
		जाओ error_मुक्त;
	पूर्ण

	अगर (verअगरy) अणु
		sysfsfp = ख_खोलो(temp, "r");
		अगर (!sysfsfp) अणु
			ret = -त्रुटि_सं;
			ख_लिखो(मानक_त्रुटि, "Could not open file to verify\n");
			जाओ error_मुक्त;
		पूर्ण

		अगर (ख_पूछो(sysfsfp, "%s", temp) != 1) अणु
			ret = त्रुटि_सं ? -त्रुटि_सं : -ENODATA;
			अगर (ख_बंद(sysfsfp))
				लिखो_त्रुटि("_write_sysfs_string(): Failed to close dir");

			जाओ error_मुक्त;
		पूर्ण

		अगर (ख_बंद(sysfsfp)) अणु
			ret = -त्रुटि_सं;
			जाओ error_मुक्त;
		पूर्ण

		अगर (म_भेद(temp, val) != 0) अणु
			ख_लिखो(मानक_त्रुटि,
				"Possible failure in string write of %s "
				"Should be %s written to %s/%s\n", temp, val,
				basedir, filename);
			ret = -1;
		पूर्ण
	पूर्ण

error_मुक्त:
	मुक्त(temp);

	वापस ret;
पूर्ण

/**
 * ग_लिखो_sysfs_string_and_verअगरy() - string ग_लिखो, पढ़ोback and verअगरy
 * @filename: name of file to ग_लिखो to
 * @basedir: the sysfs directory in which the file is to be found
 * @val: the string to ग_लिखो
 *
 * Returns a value >= 0 on success, otherwise a negative error code.
 **/
पूर्णांक ग_लिखो_sysfs_string_and_verअगरy(स्थिर अक्षर *filename, स्थिर अक्षर *basedir,
				  स्थिर अक्षर *val)
अणु
	वापस _ग_लिखो_sysfs_string(filename, basedir, val, 1);
पूर्ण

/**
 * ग_लिखो_sysfs_string() - ग_लिखो string to a sysfs file
 * @filename: name of file to ग_लिखो to
 * @basedir: the sysfs directory in which the file is to be found
 * @val: the string to ग_लिखो
 *
 * Returns a value >= 0 on success, otherwise a negative error code.
 **/
पूर्णांक ग_लिखो_sysfs_string(स्थिर अक्षर *filename, स्थिर अक्षर *basedir,
		       स्थिर अक्षर *val)
अणु
	वापस _ग_लिखो_sysfs_string(filename, basedir, val, 0);
पूर्ण

/**
 * पढ़ो_sysfs_posपूर्णांक() - पढ़ो an पूर्णांकeger value from file
 * @filename: name of file to पढ़ो from
 * @basedir: the sysfs directory in which the file is to be found
 *
 * Returns the पढ़ो पूर्णांकeger value >= 0 on success, otherwise a negative error
 * code.
 **/
पूर्णांक पढ़ो_sysfs_posपूर्णांक(स्थिर अक्षर *filename, स्थिर अक्षर *basedir)
अणु
	पूर्णांक ret;
	खाता  *sysfsfp;
	अक्षर *temp = दो_स्मृति(म_माप(basedir) + म_माप(filename) + 2);

	अगर (!temp) अणु
		ख_लिखो(मानक_त्रुटि, "Memory allocation failed");
		वापस -ENOMEM;
	पूर्ण

	ret = प्र_लिखो(temp, "%s/%s", basedir, filename);
	अगर (ret < 0)
		जाओ error_मुक्त;

	sysfsfp = ख_खोलो(temp, "r");
	अगर (!sysfsfp) अणु
		ret = -त्रुटि_सं;
		जाओ error_मुक्त;
	पूर्ण

	त्रुटि_सं = 0;
	अगर (ख_पूछो(sysfsfp, "%d\n", &ret) != 1) अणु
		ret = त्रुटि_सं ? -त्रुटि_सं : -ENODATA;
		अगर (ख_बंद(sysfsfp))
			लिखो_त्रुटि("read_sysfs_posint(): Failed to close dir");

		जाओ error_मुक्त;
	पूर्ण

	अगर (ख_बंद(sysfsfp))
		ret = -त्रुटि_सं;

error_मुक्त:
	मुक्त(temp);

	वापस ret;
पूर्ण

/**
 * पढ़ो_sysfs_भग्न() - पढ़ो a भग्न value from file
 * @filename: name of file to पढ़ो from
 * @basedir: the sysfs directory in which the file is to be found
 * @val: output the पढ़ो भग्न value
 *
 * Returns a value >= 0 on success, otherwise a negative error code.
 **/
पूर्णांक पढ़ो_sysfs_भग्न(स्थिर अक्षर *filename, स्थिर अक्षर *basedir, भग्न *val)
अणु
	पूर्णांक ret = 0;
	खाता  *sysfsfp;
	अक्षर *temp = दो_स्मृति(म_माप(basedir) + म_माप(filename) + 2);

	अगर (!temp) अणु
		ख_लिखो(मानक_त्रुटि, "Memory allocation failed");
		वापस -ENOMEM;
	पूर्ण

	ret = प्र_लिखो(temp, "%s/%s", basedir, filename);
	अगर (ret < 0)
		जाओ error_मुक्त;

	sysfsfp = ख_खोलो(temp, "r");
	अगर (!sysfsfp) अणु
		ret = -त्रुटि_सं;
		जाओ error_मुक्त;
	पूर्ण

	त्रुटि_सं = 0;
	अगर (ख_पूछो(sysfsfp, "%f\n", val) != 1) अणु
		ret = त्रुटि_सं ? -त्रुटि_सं : -ENODATA;
		अगर (ख_बंद(sysfsfp))
			लिखो_त्रुटि("read_sysfs_float(): Failed to close dir");

		जाओ error_मुक्त;
	पूर्ण

	अगर (ख_बंद(sysfsfp))
		ret = -त्रुटि_सं;

error_मुक्त:
	मुक्त(temp);

	वापस ret;
पूर्ण

/**
 * पढ़ो_sysfs_string() - पढ़ो a string from file
 * @filename: name of file to पढ़ो from
 * @basedir: the sysfs directory in which the file is to be found
 * @str: output the पढ़ो string
 *
 * Returns a value >= 0 on success, otherwise a negative error code.
 **/
पूर्णांक पढ़ो_sysfs_string(स्थिर अक्षर *filename, स्थिर अक्षर *basedir, अक्षर *str)
अणु
	पूर्णांक ret = 0;
	खाता  *sysfsfp;
	अक्षर *temp = दो_स्मृति(म_माप(basedir) + म_माप(filename) + 2);

	अगर (!temp) अणु
		ख_लिखो(मानक_त्रुटि, "Memory allocation failed");
		वापस -ENOMEM;
	पूर्ण

	ret = प्र_लिखो(temp, "%s/%s", basedir, filename);
	अगर (ret < 0)
		जाओ error_मुक्त;

	sysfsfp = ख_खोलो(temp, "r");
	अगर (!sysfsfp) अणु
		ret = -त्रुटि_सं;
		जाओ error_मुक्त;
	पूर्ण

	त्रुटि_सं = 0;
	अगर (ख_पूछो(sysfsfp, "%s\n", str) != 1) अणु
		ret = त्रुटि_सं ? -त्रुटि_सं : -ENODATA;
		अगर (ख_बंद(sysfsfp))
			लिखो_त्रुटि("read_sysfs_string(): Failed to close dir");

		जाओ error_मुक्त;
	पूर्ण

	अगर (ख_बंद(sysfsfp))
		ret = -त्रुटि_सं;

error_मुक्त:
	मुक्त(temp);

	वापस ret;
पूर्ण
