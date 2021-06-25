<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित _IIO_UTILS_H_
#घोषणा _IIO_UTILS_H_

/* IIO - useful set of util functionality
 *
 * Copyright (c) 2008 Jonathan Cameron
 */

#समावेश <मानक_निवेशt.h>

/* Made up value to limit allocation sizes */
#घोषणा IIO_MAX_NAME_LENGTH 64

#घोषणा FORMAT_SCAN_ELEMENTS_सूची "%s/buffer%d"
#घोषणा FORMAT_EVENTS_सूची "%s/events"
#घोषणा FORMAT_TYPE_खाता "%s_type"

#घोषणा ARRAY_SIZE(arr) (माप(arr) / माप(arr[0]))

बाह्य स्थिर अक्षर *iio_dir;

/**
 * काष्ठा iio_channel_info - inक्रमmation about a given channel
 * @name: channel name
 * @generic_name: general name क्रम channel type
 * @scale: scale factor to be applied क्रम conversion to si units
 * @offset: offset to be applied क्रम conversion to si units
 * @index: the channel index in the buffer output
 * @bytes: number of bytes occupied in buffer output
 * @bits_used: number of valid bits of data
 * @shअगरt: amount of bits to shअगरt right data beक्रमe applying bit mask
 * @mask: a bit mask क्रम the raw output
 * @be: flag अगर data is big endian
 * @is_चिन्हित: is the raw value stored चिन्हित
 * @location: data offset क्रम this channel inside the buffer (in bytes)
 **/
काष्ठा iio_channel_info अणु
	अक्षर *name;
	अक्षर *generic_name;
	भग्न scale;
	भग्न offset;
	अचिन्हित index;
	अचिन्हित bytes;
	अचिन्हित bits_used;
	अचिन्हित shअगरt;
	uपूर्णांक64_t mask;
	अचिन्हित be;
	अचिन्हित is_चिन्हित;
	अचिन्हित location;
पूर्ण;

अटल अंतरभूत पूर्णांक iioutils_check_suffix(स्थिर अक्षर *str, स्थिर अक्षर *suffix)
अणु
	वापस म_माप(str) >= म_माप(suffix) &&
		म_भेदन(str+म_माप(str)-म_माप(suffix),
			suffix, म_माप(suffix)) == 0;
पूर्ण

पूर्णांक iioutils_अवरोध_up_name(स्थिर अक्षर *full_name, अक्षर **generic_name);
पूर्णांक iioutils_get_param_भग्न(भग्न *output, स्थिर अक्षर *param_name,
			     स्थिर अक्षर *device_dir, स्थिर अक्षर *name,
			     स्थिर अक्षर *generic_name);
व्योम bsort_channel_array_by_index(काष्ठा iio_channel_info *ci_array, पूर्णांक cnt);
पूर्णांक build_channel_array(स्थिर अक्षर *device_dir, पूर्णांक buffer_idx,
			काष्ठा iio_channel_info **ci_array, पूर्णांक *counter);
पूर्णांक find_type_by_name(स्थिर अक्षर *name, स्थिर अक्षर *type);
पूर्णांक ग_लिखो_sysfs_पूर्णांक(स्थिर अक्षर *filename, स्थिर अक्षर *basedir, पूर्णांक val);
पूर्णांक ग_लिखो_sysfs_पूर्णांक_and_verअगरy(स्थिर अक्षर *filename, स्थिर अक्षर *basedir,
			       पूर्णांक val);
पूर्णांक ग_लिखो_sysfs_string_and_verअगरy(स्थिर अक्षर *filename, स्थिर अक्षर *basedir,
				  स्थिर अक्षर *val);
पूर्णांक ग_लिखो_sysfs_string(स्थिर अक्षर *filename, स्थिर अक्षर *basedir,
		       स्थिर अक्षर *val);
पूर्णांक पढ़ो_sysfs_posपूर्णांक(स्थिर अक्षर *filename, स्थिर अक्षर *basedir);
पूर्णांक पढ़ो_sysfs_भग्न(स्थिर अक्षर *filename, स्थिर अक्षर *basedir, भग्न *val);
पूर्णांक पढ़ो_sysfs_string(स्थिर अक्षर *filename, स्थिर अक्षर *basedir, अक्षर *str);

#पूर्ण_अगर /* _IIO_UTILS_H_ */
