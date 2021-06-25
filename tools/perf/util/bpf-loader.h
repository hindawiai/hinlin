<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2015, Wang Nan <wangnan0@huawei.com>
 * Copyright (C) 2015, Huawei Inc.
 */
#अगर_अघोषित __BPF_LOADER_H
#घोषणा __BPF_LOADER_H

#समावेश <linux/compiler.h>
#समावेश <linux/err.h>

#अगर_घोषित HAVE_LIBBPF_SUPPORT
#समावेश <bpf/libbpf.h>

क्रमागत bpf_loader_त्रुटि_सं अणु
	__BPF_LOADER_ERRNO__START = __LIBBPF_ERRNO__START - 100,
	/* Invalid config string */
	BPF_LOADER_ERRNO__CONFIG = __BPF_LOADER_ERRNO__START,
	BPF_LOADER_ERRNO__GROUP,	/* Invalid group name */
	BPF_LOADER_ERRNO__EVENTNAME,	/* Event name is missing */
	BPF_LOADER_ERRNO__INTERNAL,	/* BPF loader पूर्णांकernal error */
	BPF_LOADER_ERRNO__COMPILE,	/* Error when compiling BPF scriptlet */
	BPF_LOADER_ERRNO__PROGCONF_TERM,/* Invalid program config term in config string */
	BPF_LOADER_ERRNO__PROLOGUE,	/* Failed to generate prologue */
	BPF_LOADER_ERRNO__PROLOGUE2BIG,	/* Prologue too big क्रम program */
	BPF_LOADER_ERRNO__PROLOGUEOOB,	/* Offset out of bound क्रम prologue */
	BPF_LOADER_ERRNO__OBJCONF_OPT,	/* Invalid object config option */
	BPF_LOADER_ERRNO__OBJCONF_CONF,	/* Config value not set (lost '=')) */
	BPF_LOADER_ERRNO__OBJCONF_MAP_OPT,	/* Invalid object map config option */
	BPF_LOADER_ERRNO__OBJCONF_MAP_NOTEXIST,	/* Target map not exist */
	BPF_LOADER_ERRNO__OBJCONF_MAP_VALUE,	/* Incorrect value type क्रम map */
	BPF_LOADER_ERRNO__OBJCONF_MAP_TYPE,	/* Incorrect map type */
	BPF_LOADER_ERRNO__OBJCONF_MAP_KEYSIZE,	/* Incorrect map key size */
	BPF_LOADER_ERRNO__OBJCONF_MAP_VALUESIZE,/* Incorrect map value size */
	BPF_LOADER_ERRNO__OBJCONF_MAP_NOEVT,	/* Event not found क्रम map setting */
	BPF_LOADER_ERRNO__OBJCONF_MAP_MAPSIZE,	/* Invalid map size क्रम event setting */
	BPF_LOADER_ERRNO__OBJCONF_MAP_EVTDIM,	/* Event dimension too large */
	BPF_LOADER_ERRNO__OBJCONF_MAP_EVTINH,	/* Doesn't support inherit event */
	BPF_LOADER_ERRNO__OBJCONF_MAP_EVTTYPE,	/* Wrong event type क्रम map */
	BPF_LOADER_ERRNO__OBJCONF_MAP_IDX2BIG,	/* Index too large */
	__BPF_LOADER_ERRNO__END,
पूर्ण;
#पूर्ण_अगर // HAVE_LIBBPF_SUPPORT

काष्ठा evsel;
काष्ठा evlist;
काष्ठा bpf_object;
काष्ठा parse_events_term;
#घोषणा PERF_BPF_PROBE_GROUP "perf_bpf_probe"

प्रकार पूर्णांक (*bpf_prog_iter_callback_t)(स्थिर अक्षर *group, स्थिर अक्षर *event,
					पूर्णांक fd, काष्ठा bpf_object *obj, व्योम *arg);

#अगर_घोषित HAVE_LIBBPF_SUPPORT
काष्ठा bpf_object *bpf__prepare_load(स्थिर अक्षर *filename, bool source);
पूर्णांक bpf__म_त्रुटि_prepare_load(स्थिर अक्षर *filename, bool source,
			       पूर्णांक err, अक्षर *buf, माप_प्रकार size);

काष्ठा bpf_object *bpf__prepare_load_buffer(व्योम *obj_buf, माप_प्रकार obj_buf_sz,
					    स्थिर अक्षर *name);

व्योम bpf__clear(व्योम);

पूर्णांक bpf__probe(काष्ठा bpf_object *obj);
पूर्णांक bpf__unprobe(काष्ठा bpf_object *obj);
पूर्णांक bpf__म_त्रुटि_probe(काष्ठा bpf_object *obj, पूर्णांक err,
			अक्षर *buf, माप_प्रकार size);

पूर्णांक bpf__load(काष्ठा bpf_object *obj);
पूर्णांक bpf__म_त्रुटि_load(काष्ठा bpf_object *obj, पूर्णांक err,
		       अक्षर *buf, माप_प्रकार size);
पूर्णांक bpf__क्रमeach_event(काष्ठा bpf_object *obj,
		       bpf_prog_iter_callback_t func, व्योम *arg);

पूर्णांक bpf__config_obj(काष्ठा bpf_object *obj, काष्ठा parse_events_term *term,
		    काष्ठा evlist *evlist, पूर्णांक *error_pos);
पूर्णांक bpf__म_त्रुटि_config_obj(काष्ठा bpf_object *obj,
			     काष्ठा parse_events_term *term,
			     काष्ठा evlist *evlist,
			     पूर्णांक *error_pos, पूर्णांक err, अक्षर *buf,
			     माप_प्रकार size);
पूर्णांक bpf__apply_obj_config(व्योम);
पूर्णांक bpf__म_त्रुटि_apply_obj_config(पूर्णांक err, अक्षर *buf, माप_प्रकार size);

पूर्णांक bpf__setup_मानक_निकास(काष्ठा evlist *evlist);
काष्ठा evsel *bpf__setup_output_event(काष्ठा evlist *evlist, स्थिर अक्षर *name);
पूर्णांक bpf__म_त्रुटि_setup_output_event(काष्ठा evlist *evlist, पूर्णांक err, अक्षर *buf, माप_प्रकार size);
#अन्यथा
#समावेश <त्रुटिसं.स>
#समावेश <माला.स>
#समावेश "debug.h"

अटल अंतरभूत काष्ठा bpf_object *
bpf__prepare_load(स्थिर अक्षर *filename __maybe_unused,
		  bool source __maybe_unused)
अणु
	pr_debug("ERROR: eBPF object loading is disabled during compiling.\n");
	वापस ERR_PTR(-ENOTSUP);
पूर्ण

अटल अंतरभूत काष्ठा bpf_object *
bpf__prepare_load_buffer(व्योम *obj_buf __maybe_unused,
					   माप_प्रकार obj_buf_sz __maybe_unused)
अणु
	वापस ERR_PTR(-ENOTSUP);
पूर्ण

अटल अंतरभूत व्योम bpf__clear(व्योम) अणु पूर्ण

अटल अंतरभूत पूर्णांक bpf__probe(काष्ठा bpf_object *obj __maybe_unused) अणु वापस 0;पूर्ण
अटल अंतरभूत पूर्णांक bpf__unprobe(काष्ठा bpf_object *obj __maybe_unused) अणु वापस 0;पूर्ण
अटल अंतरभूत पूर्णांक bpf__load(काष्ठा bpf_object *obj __maybe_unused) अणु वापस 0; पूर्ण

अटल अंतरभूत पूर्णांक
bpf__क्रमeach_event(काष्ठा bpf_object *obj __maybe_unused,
		   bpf_prog_iter_callback_t func __maybe_unused,
		   व्योम *arg __maybe_unused)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
bpf__config_obj(काष्ठा bpf_object *obj __maybe_unused,
		काष्ठा parse_events_term *term __maybe_unused,
		काष्ठा evlist *evlist __maybe_unused,
		पूर्णांक *error_pos __maybe_unused)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
bpf__apply_obj_config(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
bpf__setup_मानक_निकास(काष्ठा evlist *evlist __maybe_unused)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा evsel *
bpf__setup_output_event(काष्ठा evlist *evlist __maybe_unused, स्थिर अक्षर *name __maybe_unused)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक
__bpf_म_त्रुटि(अक्षर *buf, माप_प्रकार size)
अणु
	अगर (!size)
		वापस 0;
	म_नकलन(buf,
		"ERROR: eBPF object loading is disabled during compiling.\n",
		size);
	buf[size - 1] = '\0';
	वापस 0;
पूर्ण

अटल अंतरभूत
पूर्णांक bpf__म_त्रुटि_prepare_load(स्थिर अक्षर *filename __maybe_unused,
			       bool source __maybe_unused,
			       पूर्णांक err __maybe_unused,
			       अक्षर *buf, माप_प्रकार size)
अणु
	वापस __bpf_म_त्रुटि(buf, size);
पूर्ण

अटल अंतरभूत पूर्णांक
bpf__म_त्रुटि_probe(काष्ठा bpf_object *obj __maybe_unused,
		    पूर्णांक err __maybe_unused,
		    अक्षर *buf, माप_प्रकार size)
अणु
	वापस __bpf_म_त्रुटि(buf, size);
पूर्ण

अटल अंतरभूत पूर्णांक bpf__म_त्रुटि_load(काष्ठा bpf_object *obj __maybe_unused,
				     पूर्णांक err __maybe_unused,
				     अक्षर *buf, माप_प्रकार size)
अणु
	वापस __bpf_म_त्रुटि(buf, size);
पूर्ण

अटल अंतरभूत पूर्णांक
bpf__म_त्रुटि_config_obj(काष्ठा bpf_object *obj __maybe_unused,
			 काष्ठा parse_events_term *term __maybe_unused,
			 काष्ठा evlist *evlist __maybe_unused,
			 पूर्णांक *error_pos __maybe_unused,
			 पूर्णांक err __maybe_unused,
			 अक्षर *buf, माप_प्रकार size)
अणु
	वापस __bpf_म_त्रुटि(buf, size);
पूर्ण

अटल अंतरभूत पूर्णांक
bpf__म_त्रुटि_apply_obj_config(पूर्णांक err __maybe_unused,
			       अक्षर *buf, माप_प्रकार size)
अणु
	वापस __bpf_म_त्रुटि(buf, size);
पूर्ण

अटल अंतरभूत पूर्णांक
bpf__म_त्रुटि_setup_output_event(काष्ठा evlist *evlist __maybe_unused,
				 पूर्णांक err __maybe_unused, अक्षर *buf, माप_प्रकार size)
अणु
	वापस __bpf_म_त्रुटि(buf, size);
पूर्ण

#पूर्ण_अगर

अटल अंतरभूत पूर्णांक bpf__म_त्रुटि_setup_मानक_निकास(काष्ठा evlist *evlist, पूर्णांक err, अक्षर *buf, माप_प्रकार size)
अणु
	वापस bpf__म_त्रुटि_setup_output_event(evlist, err, buf, size);
पूर्ण
#पूर्ण_अगर
