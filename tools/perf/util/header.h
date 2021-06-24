<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PERF_HEADER_H
#घोषणा __PERF_HEADER_H

#समावेश <linux/मानकघोष.स>
#समावेश <linux/perf_event.h>
#समावेश <sys/types.h>
#समावेश <मानकपन.स> // खाता
#समावेश <stdbool.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/types.h>
#समावेश "env.h"
#समावेश "pmu.h"

क्रमागत अणु
	HEADER_RESERVED		= 0,	/* always cleared */
	HEADER_FIRST_FEATURE	= 1,
	HEADER_TRACING_DATA	= 1,
	HEADER_BUILD_ID,

	HEADER_HOSTNAME,
	HEADER_OSRELEASE,
	HEADER_VERSION,
	HEADER_ARCH,
	HEADER_NRCPUS,
	HEADER_CPUDESC,
	HEADER_CPUID,
	HEADER_TOTAL_MEM,
	HEADER_CMDLINE,
	HEADER_EVENT_DESC,
	HEADER_CPU_TOPOLOGY,
	HEADER_NUMA_TOPOLOGY,
	HEADER_BRANCH_STACK,
	HEADER_PMU_MAPPINGS,
	HEADER_GROUP_DESC,
	HEADER_AUXTRACE,
	HEADER_STAT,
	HEADER_CACHE,
	HEADER_SAMPLE_TIME,
	HEADER_MEM_TOPOLOGY,
	HEADER_CLOCKID,
	HEADER_सूची_FORMAT,
	HEADER_BPF_PROG_INFO,
	HEADER_BPF_BTF,
	HEADER_COMPRESSED,
	HEADER_CPU_PMU_CAPS,
	HEADER_CLOCK_DATA,
	HEADER_LAST_FEATURE,
	HEADER_FEAT_BITS	= 256,
पूर्ण;

क्रमागत perf_header_version अणु
	PERF_HEADER_VERSION_1,
	PERF_HEADER_VERSION_2,
पूर्ण;

काष्ठा perf_file_section अणु
	u64 offset;
	u64 size;
पूर्ण;

काष्ठा perf_file_header अणु
	u64				magic;
	u64				size;
	u64				attr_size;
	काष्ठा perf_file_section	attrs;
	काष्ठा perf_file_section	data;
	/* event_types is ignored */
	काष्ठा perf_file_section	event_types;
	DECLARE_BITMAP(adds_features, HEADER_FEAT_BITS);
पूर्ण;

काष्ठा perf_pipe_file_header अणु
	u64				magic;
	u64				size;
पूर्ण;

काष्ठा perf_header;

पूर्णांक perf_file_header__पढ़ो(काष्ठा perf_file_header *header,
			   काष्ठा perf_header *ph, पूर्णांक fd);

काष्ठा perf_header अणु
	क्रमागत perf_header_version	version;
	bool				needs_swap;
	u64				data_offset;
	u64				data_size;
	u64				feat_offset;
	DECLARE_BITMAP(adds_features, HEADER_FEAT_BITS);
	काष्ठा perf_env 	env;
पूर्ण;

काष्ठा feat_fd अणु
	काष्ठा perf_header *ph;
	पूर्णांक		   fd;
	व्योम		   *buf;	/* Either buf != शून्य or fd >= 0 */
	sमाप_प्रकार		   offset;
	माप_प्रकार		   size;
	काष्ठा evsel	   *events;
पूर्ण;

काष्ठा perf_header_feature_ops अणु
	पूर्णांक	   (*ग_लिखो)(काष्ठा feat_fd *ff, काष्ठा evlist *evlist);
	व्योम	   (*prपूर्णांक)(काष्ठा feat_fd *ff, खाता *fp);
	पूर्णांक	   (*process)(काष्ठा feat_fd *ff, व्योम *data);
	स्थिर अक्षर *name;
	bool	   full_only;
	bool	   synthesize;
पूर्ण;

काष्ठा evlist;
काष्ठा perf_session;
काष्ठा perf_tool;
जोड़ perf_event;

पूर्णांक perf_session__पढ़ो_header(काष्ठा perf_session *session);
पूर्णांक perf_session__ग_लिखो_header(काष्ठा perf_session *session,
			       काष्ठा evlist *evlist,
			       पूर्णांक fd, bool at_निकास);
पूर्णांक perf_header__ग_लिखो_pipe(पूर्णांक fd);

व्योम perf_header__set_feat(काष्ठा perf_header *header, पूर्णांक feat);
व्योम perf_header__clear_feat(काष्ठा perf_header *header, पूर्णांक feat);
bool perf_header__has_feat(स्थिर काष्ठा perf_header *header, पूर्णांक feat);

पूर्णांक perf_header__set_cmdline(पूर्णांक argc, स्थिर अक्षर **argv);

पूर्णांक perf_header__process_sections(काष्ठा perf_header *header, पूर्णांक fd,
				  व्योम *data,
				  पूर्णांक (*process)(काष्ठा perf_file_section *section,
				  काष्ठा perf_header *ph,
				  पूर्णांक feat, पूर्णांक fd, व्योम *data));

पूर्णांक perf_header__ख_लिखो_info(काष्ठा perf_session *s, खाता *fp, bool full);

पूर्णांक perf_event__process_feature(काष्ठा perf_session *session,
				जोड़ perf_event *event);
पूर्णांक perf_event__process_attr(काष्ठा perf_tool *tool, जोड़ perf_event *event,
			     काष्ठा evlist **pevlist);
पूर्णांक perf_event__process_event_update(काष्ठा perf_tool *tool,
				     जोड़ perf_event *event,
				     काष्ठा evlist **pevlist);
माप_प्रकार perf_event__ख_लिखो_event_update(जोड़ perf_event *event, खाता *fp);
पूर्णांक perf_event__process_tracing_data(काष्ठा perf_session *session,
				     जोड़ perf_event *event);
पूर्णांक perf_event__process_build_id(काष्ठा perf_session *session,
				 जोड़ perf_event *event);
bool is_perf_magic(u64 magic);

#घोषणा NAME_ALIGN 64

काष्ठा feat_fd;

पूर्णांक करो_ग_लिखो(काष्ठा feat_fd *fd, स्थिर व्योम *buf, माप_प्रकार size);

पूर्णांक ग_लिखो_padded(काष्ठा feat_fd *fd, स्थिर व्योम *bf,
		 माप_प्रकार count, माप_प्रकार count_aligned);

/*
 * arch specअगरic callback
 */
पूर्णांक get_cpuid(अक्षर *buffer, माप_प्रकार sz);

अक्षर *get_cpuid_str(काष्ठा perf_pmu *pmu __maybe_unused);
पूर्णांक म_भेद_cpuid_str(स्थिर अक्षर *s1, स्थिर अक्षर *s2);
#पूर्ण_अगर /* __PERF_HEADER_H */
