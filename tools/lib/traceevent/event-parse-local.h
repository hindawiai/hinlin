<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1
/*
 * Copyright (C) 2009, 2010 Red Hat Inc, Steven Rostedt <srostedt@redhat.com>
 *
 */

#अगर_अघोषित _PARSE_EVENTS_INT_H
#घोषणा _PARSE_EVENTS_INT_H

काष्ठा tep_cmdline;
काष्ठा cmdline_list;
काष्ठा func_map;
काष्ठा func_list;
काष्ठा event_handler;
काष्ठा func_resolver;
काष्ठा tep_plugins_dir;

#घोषणा __hidden __attribute__((visibility ("hidden")))

काष्ठा tep_handle अणु
	पूर्णांक ref_count;

	पूर्णांक header_page_ts_offset;
	पूर्णांक header_page_ts_size;
	पूर्णांक header_page_size_offset;
	पूर्णांक header_page_size_size;
	पूर्णांक header_page_data_offset;
	पूर्णांक header_page_data_size;
	पूर्णांक header_page_overग_लिखो;

	क्रमागत tep_endian file_bigendian;
	क्रमागत tep_endian host_bigendian;

	पूर्णांक old_क्रमmat;

	पूर्णांक cpus;
	पूर्णांक दीर्घ_size;
	पूर्णांक page_size;

	काष्ठा tep_cmdline *cmdlines;
	काष्ठा cmdline_list *cmdlist;
	पूर्णांक cmdline_count;

	काष्ठा func_map *func_map;
	काष्ठा func_resolver *func_resolver;
	काष्ठा func_list *funclist;
	अचिन्हित पूर्णांक func_count;

	काष्ठा prपूर्णांकk_map *prपूर्णांकk_map;
	काष्ठा prपूर्णांकk_list *prपूर्णांकklist;
	अचिन्हित पूर्णांक prपूर्णांकk_count;

	काष्ठा tep_event **events;
	पूर्णांक nr_events;
	काष्ठा tep_event **sort_events;
	क्रमागत tep_event_sort_type last_type;

	पूर्णांक type_offset;
	पूर्णांक type_size;

	पूर्णांक pid_offset;
	पूर्णांक pid_size;

	पूर्णांक pc_offset;
	पूर्णांक pc_size;

	पूर्णांक flags_offset;
	पूर्णांक flags_size;

	पूर्णांक ld_offset;
	पूर्णांक ld_size;

	पूर्णांक test_filters;

	पूर्णांक flags;

	काष्ठा tep_क्रमmat_field *bprपूर्णांक_ip_field;
	काष्ठा tep_क्रमmat_field *bprपूर्णांक_fmt_field;
	काष्ठा tep_क्रमmat_field *bprपूर्णांक_buf_field;

	काष्ठा event_handler *handlers;
	काष्ठा tep_function_handler *func_handlers;

	/* cache */
	काष्ठा tep_event *last_event;

	काष्ठा tep_plugins_dir *plugins_dir;
पूर्ण;

क्रमागत tep_prपूर्णांक_parse_type अणु
	PRINT_FMT_STRING,
	PRINT_FMT_ARG_DIGIT,
	PRINT_FMT_ARG_POINTER,
	PRINT_FMT_ARG_STRING,
पूर्ण;

काष्ठा tep_prपूर्णांक_parse अणु
	काष्ठा tep_prपूर्णांक_parse	*next;

	अक्षर				*क्रमmat;
	पूर्णांक				ls;
	क्रमागत tep_prपूर्णांक_parse_type	type;
	काष्ठा tep_prपूर्णांक_arg		*arg;
	काष्ठा tep_prपूर्णांक_arg		*len_as_arg;
पूर्ण;

व्योम मुक्त_tep_event(काष्ठा tep_event *event);
व्योम मुक्त_tep_क्रमmat_field(काष्ठा tep_क्रमmat_field *field);
व्योम मुक्त_tep_plugin_paths(काष्ठा tep_handle *tep);

अचिन्हित लघु data2host2(काष्ठा tep_handle *tep, अचिन्हित लघु data);
अचिन्हित पूर्णांक data2host4(काष्ठा tep_handle *tep, अचिन्हित पूर्णांक data);
अचिन्हित दीर्घ दीर्घ data2host8(काष्ठा tep_handle *tep, अचिन्हित दीर्घ दीर्घ data);

/* access to the पूर्णांकernal parser */
पूर्णांक peek_अक्षर(व्योम);
व्योम init_input_buf(स्थिर अक्षर *buf, अचिन्हित दीर्घ दीर्घ size);
अचिन्हित दीर्घ दीर्घ get_input_buf_ptr(व्योम);
स्थिर अक्षर *get_input_buf(व्योम);
क्रमागत tep_event_type पढ़ो_token(अक्षर **tok);
व्योम मुक्त_token(अक्षर *tok);

#पूर्ण_अगर /* _PARSE_EVENTS_INT_H */
