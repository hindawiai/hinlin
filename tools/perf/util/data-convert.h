<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __DATA_CONVERT_H
#घोषणा __DATA_CONVERT_H

#समावेश <stdbool.h>

काष्ठा perf_data_convert_opts अणु
	bool क्रमce;
	bool all;
	bool tod;
पूर्ण;

#अगर_घोषित HAVE_LIBBABELTRACE_SUPPORT
पूर्णांक bt_convert__perf2ctf(स्थिर अक्षर *input_name, स्थिर अक्षर *to_ctf,
			 काष्ठा perf_data_convert_opts *opts);
#पूर्ण_अगर /* HAVE_LIBBABELTRACE_SUPPORT */

पूर्णांक bt_convert__perf2json(स्थिर अक्षर *input_name, स्थिर अक्षर *to_ctf,
			 काष्ठा perf_data_convert_opts *opts);

#पूर्ण_अगर /* __DATA_CONVERT_H */
