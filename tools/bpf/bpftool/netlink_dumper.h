<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause) */
// Copyright (C) 2018 Facebook

#अगर_अघोषित _NETLINK_DUMPER_H_
#घोषणा _NETLINK_DUMPER_H_

#घोषणा NET_START_OBJECT				\
अणु							\
	अगर (json_output)				\
		jsonw_start_object(json_wtr);		\
पूर्ण

#घोषणा NET_START_OBJECT_NESTED(name)			\
अणु							\
	अगर (json_output) अणु				\
		jsonw_name(json_wtr, name);		\
		jsonw_start_object(json_wtr);		\
	पूर्ण अन्यथा अणु					\
		ख_लिखो(मानक_निकास, "%s {", name);		\
	पूर्ण						\
पूर्ण

#घोषणा NET_START_OBJECT_NESTED2			\
अणु							\
	अगर (json_output)				\
		jsonw_start_object(json_wtr);		\
	अन्यथा						\
		ख_लिखो(मानक_निकास, "{");			\
पूर्ण

#घोषणा NET_END_OBJECT_NESTED				\
अणु							\
	अगर (json_output)				\
		jsonw_end_object(json_wtr);		\
	अन्यथा						\
		ख_लिखो(मानक_निकास, "}");			\
पूर्ण

#घोषणा NET_END_OBJECT					\
अणु							\
	अगर (json_output)				\
		jsonw_end_object(json_wtr);		\
पूर्ण

#घोषणा NET_END_OBJECT_FINAL				\
अणु							\
	अगर (json_output)				\
		jsonw_end_object(json_wtr);		\
	अन्यथा						\
		ख_लिखो(मानक_निकास, "\n");			\
पूर्ण

#घोषणा NET_START_ARRAY(name, fmt_str)			\
अणु							\
	अगर (json_output) अणु				\
		jsonw_name(json_wtr, name);		\
		jsonw_start_array(json_wtr);		\
	पूर्ण अन्यथा अणु					\
		ख_लिखो(मानक_निकास, fmt_str, name);		\
	पूर्ण						\
पूर्ण

#घोषणा NET_END_ARRAY(endstr)				\
अणु							\
	अगर (json_output)				\
		jsonw_end_array(json_wtr);		\
	अन्यथा						\
		ख_लिखो(मानक_निकास, "%s", endstr);		\
पूर्ण

#घोषणा NET_DUMP_UINT(name, fmt_str, val)		\
अणु							\
	अगर (json_output)				\
		jsonw_uपूर्णांक_field(json_wtr, name, val);	\
	अन्यथा						\
		ख_लिखो(मानक_निकास, fmt_str, val);		\
पूर्ण

#घोषणा NET_DUMP_STR(name, fmt_str, str)		\
अणु							\
	अगर (json_output)				\
		jsonw_string_field(json_wtr, name, str);\
	अन्यथा						\
		ख_लिखो(मानक_निकास, fmt_str, str);		\
पूर्ण

#घोषणा NET_DUMP_STR_ONLY(str)				\
अणु							\
	अगर (json_output)				\
		jsonw_string(json_wtr, str);		\
	अन्यथा						\
		ख_लिखो(मानक_निकास, "%s ", str);		\
पूर्ण

#पूर्ण_अगर
