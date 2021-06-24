<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित PERF_BUILD_ID_H_
#घोषणा PERF_BUILD_ID_H_ 1

#घोषणा BUILD_ID_SIZE	20 /* SHA-1 length in bytes */
#घोषणा BUILD_ID_MIN_SIZE	16 /* MD5/UUID/GUID length in bytes */
#घोषणा SBUILD_ID_SIZE	(BUILD_ID_SIZE * 2 + 1)
#घोषणा SBUILD_ID_MIN_SIZE	(BUILD_ID_MIN_SIZE * 2 + 1)

#समावेश "machine.h"
#समावेश "tool.h"
#समावेश <linux/types.h>

काष्ठा build_id अणु
	u8	data[BUILD_ID_SIZE];
	माप_प्रकार	size;
पूर्ण;

काष्ठा nsinfo;

बाह्य काष्ठा perf_tool build_id__mark_dso_hit_ops;
काष्ठा dso;
काष्ठा feat_fd;

व्योम build_id__init(काष्ठा build_id *bid, स्थिर u8 *data, माप_प्रकार size);
पूर्णांक build_id__प्र_लिखो(स्थिर काष्ठा build_id *build_id, अक्षर *bf);
bool build_id__is_defined(स्थिर काष्ठा build_id *bid);
पूर्णांक sysfs__प्र_लिखो_build_id(स्थिर अक्षर *root_dir, अक्षर *sbuild_id);
पूर्णांक filename__प्र_लिखो_build_id(स्थिर अक्षर *pathname, अक्षर *sbuild_id);
अक्षर *build_id_cache__kallsyms_path(स्थिर अक्षर *sbuild_id, अक्षर *bf,
				    माप_प्रकार size);

अक्षर *dso__build_id_filename(स्थिर काष्ठा dso *dso, अक्षर *bf, माप_प्रकार size,
			     bool is_debug);
अक्षर *__dso__build_id_filename(स्थिर काष्ठा dso *dso, अक्षर *bf, माप_प्रकार size,
			       bool is_debug, bool is_kallsyms);

पूर्णांक build_id__mark_dso_hit(काष्ठा perf_tool *tool, जोड़ perf_event *event,
			   काष्ठा perf_sample *sample, काष्ठा evsel *evsel,
			   काष्ठा machine *machine);

पूर्णांक dsos__hit_all(काष्ठा perf_session *session);

पूर्णांक perf_event__inject_buildid(काष्ठा perf_tool *tool, जोड़ perf_event *event,
			       काष्ठा perf_sample *sample, काष्ठा evsel *evsel,
			       काष्ठा machine *machine);

bool perf_session__पढ़ो_build_ids(काष्ठा perf_session *session, bool with_hits);
पूर्णांक perf_session__ग_लिखो_buildid_table(काष्ठा perf_session *session,
				      काष्ठा feat_fd *fd);
पूर्णांक perf_session__cache_build_ids(काष्ठा perf_session *session);
पूर्णांक __perf_session__cache_build_ids(काष्ठा perf_session *session,
				    machine__dso_t fn, व्योम *priv);

अक्षर *build_id_cache__origname(स्थिर अक्षर *sbuild_id);
अक्षर *build_id_cache__linkname(स्थिर अक्षर *sbuild_id, अक्षर *bf, माप_प्रकार size);
अक्षर *build_id_cache__cachedir(स्थिर अक्षर *sbuild_id, स्थिर अक्षर *name,
			       काष्ठा nsinfo *nsi, bool is_kallsyms,
			       bool is_vdso);

काष्ठा strlist;

काष्ठा strlist *build_id_cache__list_all(bool valiकरोnly);
अक्षर *build_id_cache__complement(स्थिर अक्षर *incomplete_sbuild_id);
पूर्णांक build_id_cache__list_build_ids(स्थिर अक्षर *pathname, काष्ठा nsinfo *nsi,
				   काष्ठा strlist **result);
bool build_id_cache__cached(स्थिर अक्षर *sbuild_id);
पूर्णांक build_id_cache__add(स्थिर अक्षर *sbuild_id, स्थिर अक्षर *name, स्थिर अक्षर *realname,
			काष्ठा nsinfo *nsi, bool is_kallsyms, bool is_vdso);
पूर्णांक build_id_cache__add_s(स्थिर अक्षर *sbuild_id,
			  स्थिर अक्षर *name, काष्ठा nsinfo *nsi,
			  bool is_kallsyms, bool is_vdso);
पूर्णांक build_id_cache__हटाओ_s(स्थिर अक्षर *sbuild_id);

बाह्य अक्षर buildid_dir[];

व्योम set_buildid_dir(स्थिर अक्षर *dir);
व्योम disable_buildid_cache(व्योम);

#पूर्ण_अगर
