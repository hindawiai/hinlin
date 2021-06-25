<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PROBE_खाता_H
#घोषणा __PROBE_खाता_H

#समावेश "probe-event.h"

काष्ठा strlist;
काष्ठा strfilter;

/* Cache of probe definitions */
काष्ठा probe_cache_entry अणु
	काष्ठा list_head	node;
	bool			sdt;
	काष्ठा perf_probe_event pev;
	अक्षर			*spev;
	काष्ठा strlist		*tevlist;
पूर्ण;

काष्ठा probe_cache अणु
	पूर्णांक	fd;
	काष्ठा list_head entries;
पूर्ण;

क्रमागत probe_type अणु
	PROBE_TYPE_U = 0,
	PROBE_TYPE_S,
	PROBE_TYPE_X,
	PROBE_TYPE_STRING,
	PROBE_TYPE_BITFIELD,
	PROBE_TYPE_END,
पूर्ण;

#घोषणा PF_FL_UPROBE	1
#घोषणा PF_FL_RW	2
#घोषणा क्रम_each_probe_cache_entry(entry, pcache) \
	list_क्रम_each_entry(entry, &pcache->entries, node)

/* probe-file.c depends on libelf */
#अगर_घोषित HAVE_LIBELF_SUPPORT
पूर्णांक खोलो_trace_file(स्थिर अक्षर *trace_file, bool पढ़ोग_लिखो);
पूर्णांक probe_file__खोलो(पूर्णांक flag);
पूर्णांक probe_file__खोलो_both(पूर्णांक *kfd, पूर्णांक *ufd, पूर्णांक flag);
काष्ठा strlist *probe_file__get_namelist(पूर्णांक fd);
काष्ठा strlist *probe_file__get_rawlist(पूर्णांक fd);
पूर्णांक probe_file__add_event(पूर्णांक fd, काष्ठा probe_trace_event *tev);

पूर्णांक probe_file__del_events(पूर्णांक fd, काष्ठा strfilter *filter);
पूर्णांक probe_file__get_events(पूर्णांक fd, काष्ठा strfilter *filter,
				  काष्ठा strlist *plist);
पूर्णांक probe_file__del_strlist(पूर्णांक fd, काष्ठा strlist *namelist);

पूर्णांक probe_cache_entry__get_event(काष्ठा probe_cache_entry *entry,
				 काष्ठा probe_trace_event **tevs);

काष्ठा probe_cache *probe_cache__new(स्थिर अक्षर *target, काष्ठा nsinfo *nsi);
पूर्णांक probe_cache__add_entry(काष्ठा probe_cache *pcache,
			   काष्ठा perf_probe_event *pev,
			   काष्ठा probe_trace_event *tevs, पूर्णांक ntevs);
पूर्णांक probe_cache__scan_sdt(काष्ठा probe_cache *pcache, स्थिर अक्षर *pathname);
पूर्णांक probe_cache__commit(काष्ठा probe_cache *pcache);
व्योम probe_cache__purge(काष्ठा probe_cache *pcache);
व्योम probe_cache__delete(काष्ठा probe_cache *pcache);
पूर्णांक probe_cache__filter_purge(काष्ठा probe_cache *pcache,
			      काष्ठा strfilter *filter);
काष्ठा probe_cache_entry *probe_cache__find(काष्ठा probe_cache *pcache,
					    काष्ठा perf_probe_event *pev);
काष्ठा probe_cache_entry *probe_cache__find_by_name(काष्ठा probe_cache *pcache,
					स्थिर अक्षर *group, स्थिर अक्षर *event);
पूर्णांक probe_cache__show_all_caches(काष्ठा strfilter *filter);
bool probe_type_is_available(क्रमागत probe_type type);
bool kretprobe_offset_is_supported(व्योम);
bool uprobe_ref_ctr_is_supported(व्योम);
bool user_access_is_supported(व्योम);
bool multiprobe_event_is_supported(व्योम);
bool immediate_value_is_supported(व्योम);
#अन्यथा	/* ! HAVE_LIBELF_SUPPORT */
अटल अंतरभूत काष्ठा probe_cache *probe_cache__new(स्थिर अक्षर *tgt __maybe_unused, काष्ठा nsinfo *nsi __maybe_unused)
अणु
	वापस शून्य;
पूर्ण
#घोषणा probe_cache__delete(pcache) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर
#पूर्ण_अगर
