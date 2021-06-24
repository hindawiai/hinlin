<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/list.h>
#समावेश <linux/compiler.h>
#समावेश <linux/माला.स>
#समावेश <linux/zभाग.स>
#समावेश <subcmd/pager.h>
#समावेश <sys/types.h>
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <sys/स्थिति.स>
#समावेश <unistd.h>
#समावेश <मानकपन.स>
#समावेश <stdbool.h>
#समावेश <मानकतर्क.स>
#समावेश <dirent.h>
#समावेश <api/fs/fs.h>
#समावेश <क्षेत्र.स>
#समावेश <regex.h>
#समावेश <perf/cpumap.h>
#समावेश "debug.h"
#समावेश "evsel.h"
#समावेश "pmu.h"
#समावेश "parse-events.h"
#समावेश "header.h"
#समावेश "string2.h"
#समावेश "strbuf.h"
#समावेश "fncache.h"
#समावेश "pmu-hybrid.h"

काष्ठा perf_pmu perf_pmu__fake;

काष्ठा perf_pmu_क्रमmat अणु
	अक्षर *name;
	पूर्णांक value;
	DECLARE_BITMAP(bits, PERF_PMU_FORMAT_BITS);
	काष्ठा list_head list;
पूर्ण;

पूर्णांक perf_pmu_parse(काष्ठा list_head *list, अक्षर *name);
बाह्य खाता *perf_pmu_in;

अटल LIST_HEAD(pmus);
अटल bool hybrid_scanned;

/*
 * Parse & process all the sysfs attributes located under
 * the directory specअगरied in 'dir' parameter.
 */
पूर्णांक perf_pmu__क्रमmat_parse(अक्षर *dir, काष्ठा list_head *head)
अणु
	काष्ठा dirent *evt_ent;
	सूची *क्रमmat_dir;
	पूर्णांक ret = 0;

	क्रमmat_dir = सूची_खोलो(dir);
	अगर (!क्रमmat_dir)
		वापस -EINVAL;

	जबतक (!ret && (evt_ent = सूची_पढ़ो(क्रमmat_dir))) अणु
		अक्षर path[PATH_MAX];
		अक्षर *name = evt_ent->d_name;
		खाता *file;

		अगर (!म_भेद(name, ".") || !म_भेद(name, ".."))
			जारी;

		snम_लिखो(path, PATH_MAX, "%s/%s", dir, name);

		ret = -EINVAL;
		file = ख_खोलो(path, "r");
		अगर (!file)
			अवरोध;

		perf_pmu_in = file;
		ret = perf_pmu_parse(head, name);
		ख_बंद(file);
	पूर्ण

	बंद_सूची(क्रमmat_dir);
	वापस ret;
पूर्ण

/*
 * Reading/parsing the शेष pmu क्रमmat definition, which should be
 * located at:
 * /sys/bus/event_source/devices/<dev>/क्रमmat as sysfs group attributes.
 */
अटल पूर्णांक pmu_क्रमmat(स्थिर अक्षर *name, काष्ठा list_head *क्रमmat)
अणु
	अक्षर path[PATH_MAX];
	स्थिर अक्षर *sysfs = sysfs__mountpoपूर्णांक();

	अगर (!sysfs)
		वापस -1;

	snम_लिखो(path, PATH_MAX,
		 "%s" EVENT_SOURCE_DEVICE_PATH "%s/format", sysfs, name);

	अगर (!file_available(path))
		वापस 0;

	अगर (perf_pmu__क्रमmat_parse(path, क्रमmat))
		वापस -1;

	वापस 0;
पूर्ण

पूर्णांक perf_pmu__convert_scale(स्थिर अक्षर *scale, अक्षर **end, द्विगुन *sval)
अणु
	अक्षर *lc;
	पूर्णांक ret = 0;

	/*
	 * save current locale
	 */
	lc = रखो_क्षेत्र(LC_NUMERIC, शून्य);

	/*
	 * The lc string may be allocated in अटल storage,
	 * so get a dynamic copy to make it survive रखो_क्षेत्र
	 * call below.
	 */
	lc = strdup(lc);
	अगर (!lc) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	/*
	 * क्रमce to C locale to ensure kernel
	 * scale string is converted correctly.
	 * kernel uses शेष C locale.
	 */
	रखो_क्षेत्र(LC_NUMERIC, "C");

	*sval = म_से_भग्न(scale, end);

out:
	/* restore locale */
	रखो_क्षेत्र(LC_NUMERIC, lc);
	मुक्त(lc);
	वापस ret;
पूर्ण

अटल पूर्णांक perf_pmu__parse_scale(काष्ठा perf_pmu_alias *alias, अक्षर *dir, अक्षर *name)
अणु
	काष्ठा stat st;
	sमाप_प्रकार sret;
	अक्षर scale[128];
	पूर्णांक fd, ret = -1;
	अक्षर path[PATH_MAX];

	scnम_लिखो(path, PATH_MAX, "%s/%s.scale", dir, name);

	fd = खोलो(path, O_RDONLY);
	अगर (fd == -1)
		वापस -1;

	अगर (ख_स्थिति(fd, &st) < 0)
		जाओ error;

	sret = पढ़ो(fd, scale, माप(scale)-1);
	अगर (sret < 0)
		जाओ error;

	अगर (scale[sret - 1] == '\n')
		scale[sret - 1] = '\0';
	अन्यथा
		scale[sret] = '\0';

	ret = perf_pmu__convert_scale(scale, शून्य, &alias->scale);
error:
	बंद(fd);
	वापस ret;
पूर्ण

अटल पूर्णांक perf_pmu__parse_unit(काष्ठा perf_pmu_alias *alias, अक्षर *dir, अक्षर *name)
अणु
	अक्षर path[PATH_MAX];
	sमाप_प्रकार sret;
	पूर्णांक fd;

	scnम_लिखो(path, PATH_MAX, "%s/%s.unit", dir, name);

	fd = खोलो(path, O_RDONLY);
	अगर (fd == -1)
		वापस -1;

	sret = पढ़ो(fd, alias->unit, UNIT_MAX_LEN);
	अगर (sret < 0)
		जाओ error;

	बंद(fd);

	अगर (alias->unit[sret - 1] == '\n')
		alias->unit[sret - 1] = '\0';
	अन्यथा
		alias->unit[sret] = '\0';

	वापस 0;
error:
	बंद(fd);
	alias->unit[0] = '\0';
	वापस -1;
पूर्ण

अटल पूर्णांक
perf_pmu__parse_per_pkg(काष्ठा perf_pmu_alias *alias, अक्षर *dir, अक्षर *name)
अणु
	अक्षर path[PATH_MAX];
	पूर्णांक fd;

	scnम_लिखो(path, PATH_MAX, "%s/%s.per-pkg", dir, name);

	fd = खोलो(path, O_RDONLY);
	अगर (fd == -1)
		वापस -1;

	बंद(fd);

	alias->per_pkg = true;
	वापस 0;
पूर्ण

अटल पूर्णांक perf_pmu__parse_snapshot(काष्ठा perf_pmu_alias *alias,
				    अक्षर *dir, अक्षर *name)
अणु
	अक्षर path[PATH_MAX];
	पूर्णांक fd;

	scnम_लिखो(path, PATH_MAX, "%s/%s.snapshot", dir, name);

	fd = खोलो(path, O_RDONLY);
	अगर (fd == -1)
		वापस -1;

	alias->snapshot = true;
	बंद(fd);
	वापस 0;
पूर्ण

अटल व्योम perf_pmu_assign_str(अक्षर *name, स्थिर अक्षर *field, अक्षर **old_str,
				अक्षर **new_str)
अणु
	अगर (!*old_str)
		जाओ set_new;

	अगर (*new_str) अणु	/* Have new string, check with old */
		अगर (strहालcmp(*old_str, *new_str))
			pr_debug("alias %s differs in field '%s'\n",
				 name, field);
		zमुक्त(old_str);
	पूर्ण अन्यथा		/* Nothing new --> keep old string */
		वापस;
set_new:
	*old_str = *new_str;
	*new_str = शून्य;
पूर्ण

अटल व्योम perf_pmu_update_alias(काष्ठा perf_pmu_alias *old,
				  काष्ठा perf_pmu_alias *newalias)
अणु
	perf_pmu_assign_str(old->name, "desc", &old->desc, &newalias->desc);
	perf_pmu_assign_str(old->name, "long_desc", &old->दीर्घ_desc,
			    &newalias->दीर्घ_desc);
	perf_pmu_assign_str(old->name, "topic", &old->topic, &newalias->topic);
	perf_pmu_assign_str(old->name, "metric_expr", &old->metric_expr,
			    &newalias->metric_expr);
	perf_pmu_assign_str(old->name, "metric_name", &old->metric_name,
			    &newalias->metric_name);
	perf_pmu_assign_str(old->name, "value", &old->str, &newalias->str);
	old->scale = newalias->scale;
	old->per_pkg = newalias->per_pkg;
	old->snapshot = newalias->snapshot;
	स_नकल(old->unit, newalias->unit, माप(old->unit));
पूर्ण

/* Delete an alias entry. */
व्योम perf_pmu_मुक्त_alias(काष्ठा perf_pmu_alias *newalias)
अणु
	zमुक्त(&newalias->name);
	zमुक्त(&newalias->desc);
	zमुक्त(&newalias->दीर्घ_desc);
	zमुक्त(&newalias->topic);
	zमुक्त(&newalias->str);
	zमुक्त(&newalias->metric_expr);
	zमुक्त(&newalias->metric_name);
	zमुक्त(&newalias->pmu_name);
	parse_events_terms__purge(&newalias->terms);
	मुक्त(newalias);
पूर्ण

/* Merge an alias, search in alias list. If this name is alपढ़ोy
 * present merge both of them to combine all inक्रमmation.
 */
अटल bool perf_pmu_merge_alias(काष्ठा perf_pmu_alias *newalias,
				 काष्ठा list_head *alist)
अणु
	काष्ठा perf_pmu_alias *a;

	list_क्रम_each_entry(a, alist, list) अणु
		अगर (!strहालcmp(newalias->name, a->name)) अणु
			अगर (newalias->pmu_name && a->pmu_name &&
			    !strहालcmp(newalias->pmu_name, a->pmu_name)) अणु
				जारी;
			पूर्ण
			perf_pmu_update_alias(a, newalias);
			perf_pmu_मुक्त_alias(newalias);
			वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक __perf_pmu__new_alias(काष्ठा list_head *list, अक्षर *dir, अक्षर *name,
				 अक्षर *desc, अक्षर *val, काष्ठा pmu_event *pe)
अणु
	काष्ठा parse_events_term *term;
	काष्ठा perf_pmu_alias *alias;
	पूर्णांक ret;
	पूर्णांक num;
	अक्षर newval[256];
	अक्षर *दीर्घ_desc = शून्य, *topic = शून्य, *unit = शून्य, *perpkg = शून्य,
	     *metric_expr = शून्य, *metric_name = शून्य, *deprecated = शून्य,
	     *pmu_name = शून्य;

	अगर (pe) अणु
		दीर्घ_desc = (अक्षर *)pe->दीर्घ_desc;
		topic = (अक्षर *)pe->topic;
		unit = (अक्षर *)pe->unit;
		perpkg = (अक्षर *)pe->perpkg;
		metric_expr = (अक्षर *)pe->metric_expr;
		metric_name = (अक्षर *)pe->metric_name;
		deprecated = (अक्षर *)pe->deprecated;
		pmu_name = (अक्षर *)pe->pmu;
	पूर्ण

	alias = दो_स्मृति(माप(*alias));
	अगर (!alias)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&alias->terms);
	alias->scale = 1.0;
	alias->unit[0] = '\0';
	alias->per_pkg = false;
	alias->snapshot = false;
	alias->deprecated = false;

	ret = parse_events_terms(&alias->terms, val);
	अगर (ret) अणु
		pr_err("Cannot parse alias %s: %d\n", val, ret);
		मुक्त(alias);
		वापस ret;
	पूर्ण

	/* Scan event and हटाओ leading zeroes, spaces, newlines, some
	 * platक्रमms have terms specअगरied as
	 * event=0x0091 (पढ़ो from files ../<PMU>/events/<खाता>
	 * and terms specअगरied as event=0x91 (पढ़ो from JSON files).
	 *
	 * Rebuild string to make alias->str member comparable.
	 */
	स_रखो(newval, 0, माप(newval));
	ret = 0;
	list_क्रम_each_entry(term, &alias->terms, list) अणु
		अगर (ret)
			ret += scnम_लिखो(newval + ret, माप(newval) - ret,
					 ",");
		अगर (term->type_val == PARSE_EVENTS__TERM_TYPE_NUM)
			ret += scnम_लिखो(newval + ret, माप(newval) - ret,
					 "%s=%#x", term->config, term->val.num);
		अन्यथा अगर (term->type_val == PARSE_EVENTS__TERM_TYPE_STR)
			ret += scnम_लिखो(newval + ret, माप(newval) - ret,
					 "%s=%s", term->config, term->val.str);
	पूर्ण

	alias->name = strdup(name);
	अगर (dir) अणु
		/*
		 * load unit name and scale अगर available
		 */
		perf_pmu__parse_unit(alias, dir, name);
		perf_pmu__parse_scale(alias, dir, name);
		perf_pmu__parse_per_pkg(alias, dir, name);
		perf_pmu__parse_snapshot(alias, dir, name);
	पूर्ण

	alias->metric_expr = metric_expr ? strdup(metric_expr) : शून्य;
	alias->metric_name = metric_name ? strdup(metric_name): शून्य;
	alias->desc = desc ? strdup(desc) : शून्य;
	alias->दीर्घ_desc = दीर्घ_desc ? strdup(दीर्घ_desc) :
				desc ? strdup(desc) : शून्य;
	alias->topic = topic ? strdup(topic) : शून्य;
	अगर (unit) अणु
		अगर (perf_pmu__convert_scale(unit, &unit, &alias->scale) < 0)
			वापस -1;
		snम_लिखो(alias->unit, माप(alias->unit), "%s", unit);
	पूर्ण
	alias->per_pkg = perpkg && माला_पूछो(perpkg, "%d", &num) == 1 && num == 1;
	alias->str = strdup(newval);
	alias->pmu_name = pmu_name ? strdup(pmu_name) : शून्य;

	अगर (deprecated)
		alias->deprecated = true;

	अगर (!perf_pmu_merge_alias(alias, list))
		list_add_tail(&alias->list, list);

	वापस 0;
पूर्ण

अटल पूर्णांक perf_pmu__new_alias(काष्ठा list_head *list, अक्षर *dir, अक्षर *name, खाता *file)
अणु
	अक्षर buf[256];
	पूर्णांक ret;

	ret = ख_पढ़ो(buf, 1, माप(buf), file);
	अगर (ret == 0)
		वापस -EINVAL;

	buf[ret] = 0;

	/* Remove trailing newline from sysfs file */
	strim(buf);

	वापस __perf_pmu__new_alias(list, dir, name, शून्य, buf, शून्य);
पूर्ण

अटल अंतरभूत bool pmu_alias_info_file(अक्षर *name)
अणु
	माप_प्रकार len;

	len = म_माप(name);
	अगर (len > 5 && !म_भेद(name + len - 5, ".unit"))
		वापस true;
	अगर (len > 6 && !म_भेद(name + len - 6, ".scale"))
		वापस true;
	अगर (len > 8 && !म_भेद(name + len - 8, ".per-pkg"))
		वापस true;
	अगर (len > 9 && !म_भेद(name + len - 9, ".snapshot"))
		वापस true;

	वापस false;
पूर्ण

/*
 * Process all the sysfs attributes located under the directory
 * specअगरied in 'dir' parameter.
 */
अटल पूर्णांक pmu_aliases_parse(अक्षर *dir, काष्ठा list_head *head)
अणु
	काष्ठा dirent *evt_ent;
	सूची *event_dir;

	event_dir = सूची_खोलो(dir);
	अगर (!event_dir)
		वापस -EINVAL;

	जबतक ((evt_ent = सूची_पढ़ो(event_dir))) अणु
		अक्षर path[PATH_MAX];
		अक्षर *name = evt_ent->d_name;
		खाता *file;

		अगर (!म_भेद(name, ".") || !म_भेद(name, ".."))
			जारी;

		/*
		 * skip info files parsed in perf_pmu__new_alias()
		 */
		अगर (pmu_alias_info_file(name))
			जारी;

		scnम_लिखो(path, PATH_MAX, "%s/%s", dir, name);

		file = ख_खोलो(path, "r");
		अगर (!file) अणु
			pr_debug("Cannot open %s\n", path);
			जारी;
		पूर्ण

		अगर (perf_pmu__new_alias(head, dir, name, file) < 0)
			pr_debug("Cannot set up %s\n", name);
		ख_बंद(file);
	पूर्ण

	बंद_सूची(event_dir);
	वापस 0;
पूर्ण

/*
 * Reading the pmu event aliases definition, which should be located at:
 * /sys/bus/event_source/devices/<dev>/events as sysfs group attributes.
 */
अटल पूर्णांक pmu_aliases(स्थिर अक्षर *name, काष्ठा list_head *head)
अणु
	अक्षर path[PATH_MAX];
	स्थिर अक्षर *sysfs = sysfs__mountpoपूर्णांक();

	अगर (!sysfs)
		वापस -1;

	snम_लिखो(path, PATH_MAX,
		 "%s/bus/event_source/devices/%s/events", sysfs, name);

	अगर (!file_available(path))
		वापस 0;

	अगर (pmu_aliases_parse(path, head))
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक pmu_alias_terms(काष्ठा perf_pmu_alias *alias,
			   काष्ठा list_head *terms)
अणु
	काष्ठा parse_events_term *term, *cloned;
	LIST_HEAD(list);
	पूर्णांक ret;

	list_क्रम_each_entry(term, &alias->terms, list) अणु
		ret = parse_events_term__clone(&cloned, term);
		अगर (ret) अणु
			parse_events_terms__purge(&list);
			वापस ret;
		पूर्ण
		/*
		 * Weak terms करोn't override command line options,
		 * which we करोn't want क्रम implicit terms in aliases.
		 */
		cloned->weak = true;
		list_add_tail(&cloned->list, &list);
	पूर्ण
	list_splice(&list, terms);
	वापस 0;
पूर्ण

/*
 * Reading/parsing the शेष pmu type value, which should be
 * located at:
 * /sys/bus/event_source/devices/<dev>/type as sysfs attribute.
 */
अटल पूर्णांक pmu_type(स्थिर अक्षर *name, __u32 *type)
अणु
	अक्षर path[PATH_MAX];
	खाता *file;
	पूर्णांक ret = 0;
	स्थिर अक्षर *sysfs = sysfs__mountpoपूर्णांक();

	अगर (!sysfs)
		वापस -1;

	snम_लिखो(path, PATH_MAX,
		 "%s" EVENT_SOURCE_DEVICE_PATH "%s/type", sysfs, name);

	अगर (access(path, R_OK) < 0)
		वापस -1;

	file = ख_खोलो(path, "r");
	अगर (!file)
		वापस -EINVAL;

	अगर (1 != ख_पूछो(file, "%u", type))
		ret = -1;

	ख_बंद(file);
	वापस ret;
पूर्ण

/* Add all pmus in sysfs to pmu list: */
अटल व्योम pmu_पढ़ो_sysfs(व्योम)
अणु
	अक्षर path[PATH_MAX];
	सूची *dir;
	काष्ठा dirent *dent;
	स्थिर अक्षर *sysfs = sysfs__mountpoपूर्णांक();

	अगर (!sysfs)
		वापस;

	snम_लिखो(path, PATH_MAX,
		 "%s" EVENT_SOURCE_DEVICE_PATH, sysfs);

	dir = सूची_खोलो(path);
	अगर (!dir)
		वापस;

	जबतक ((dent = सूची_पढ़ो(dir))) अणु
		अगर (!म_भेद(dent->d_name, ".") || !म_भेद(dent->d_name, ".."))
			जारी;
		/* add to अटल LIST_HEAD(pmus): */
		perf_pmu__find(dent->d_name);
	पूर्ण

	बंद_सूची(dir);
पूर्ण

अटल काष्ठा perf_cpu_map *__pmu_cpumask(स्थिर अक्षर *path)
अणु
	खाता *file;
	काष्ठा perf_cpu_map *cpus;

	file = ख_खोलो(path, "r");
	अगर (!file)
		वापस शून्य;

	cpus = perf_cpu_map__पढ़ो(file);
	ख_बंद(file);
	वापस cpus;
पूर्ण

/*
 * Uncore PMUs have a "cpumask" file under sysfs. CPU PMUs (e.g. on arm/arm64)
 * may have a "cpus" file.
 */
#घोषणा SYS_TEMPLATE_ID	"./bus/event_source/devices/%s/identifier"
#घोषणा CPUS_TEMPLATE_UNCORE	"%s/bus/event_source/devices/%s/cpumask"

अटल काष्ठा perf_cpu_map *pmu_cpumask(स्थिर अक्षर *name)
अणु
	अक्षर path[PATH_MAX];
	काष्ठा perf_cpu_map *cpus;
	स्थिर अक्षर *sysfs = sysfs__mountpoपूर्णांक();
	स्थिर अक्षर *ढाँचाs[] = अणु
		CPUS_TEMPLATE_UNCORE,
		CPUS_TEMPLATE_CPU,
		शून्य
	पूर्ण;
	स्थिर अक्षर **ढाँचा;

	अगर (!sysfs)
		वापस शून्य;

	क्रम (ढाँचा = ढाँचाs; *ढाँचा; ढाँचा++) अणु
		snम_लिखो(path, PATH_MAX, *ढाँचा, sysfs, name);
		cpus = __pmu_cpumask(path);
		अगर (cpus)
			वापस cpus;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल bool pmu_is_uncore(स्थिर अक्षर *name)
अणु
	अक्षर path[PATH_MAX];
	स्थिर अक्षर *sysfs;

	अगर (perf_pmu__hybrid_mounted(name))
		वापस false;

	sysfs = sysfs__mountpoपूर्णांक();
	snम_लिखो(path, PATH_MAX, CPUS_TEMPLATE_UNCORE, sysfs, name);
	वापस file_available(path);
पूर्ण

अटल अक्षर *pmu_id(स्थिर अक्षर *name)
अणु
	अक्षर path[PATH_MAX], *str;
	माप_प्रकार len;

	snम_लिखो(path, PATH_MAX, SYS_TEMPLATE_ID, name);

	अगर (sysfs__पढ़ो_str(path, &str, &len) < 0)
		वापस शून्य;

	str[len - 1] = 0; /* हटाओ line feed */

	वापस str;
पूर्ण

/*
 *  PMU CORE devices have dअगरferent name other than cpu in sysfs on some
 *  platक्रमms.
 *  Looking क्रम possible sysfs files to identअगरy the arm core device.
 */
अटल पूर्णांक is_arm_pmu_core(स्थिर अक्षर *name)
अणु
	अक्षर path[PATH_MAX];
	स्थिर अक्षर *sysfs = sysfs__mountpoपूर्णांक();

	अगर (!sysfs)
		वापस 0;

	/* Look क्रम cpu sysfs (specअगरic to arm) */
	scnम_लिखो(path, PATH_MAX, "%s/bus/event_source/devices/%s/cpus",
				sysfs, name);
	वापस file_available(path);
पूर्ण

अटल अक्षर *perf_pmu__अ_लोpuid(काष्ठा perf_pmu *pmu)
अणु
	अक्षर *cpuid;
	अटल bool prपूर्णांकed;

	cpuid = दो_पर्या("PERF_CPUID");
	अगर (cpuid)
		cpuid = strdup(cpuid);
	अगर (!cpuid)
		cpuid = get_cpuid_str(pmu);
	अगर (!cpuid)
		वापस शून्य;

	अगर (!prपूर्णांकed) अणु
		pr_debug("Using CPUID %s\n", cpuid);
		prपूर्णांकed = true;
	पूर्ण
	वापस cpuid;
पूर्ण

काष्ठा pmu_events_map *perf_pmu__find_map(काष्ठा perf_pmu *pmu)
अणु
	काष्ठा pmu_events_map *map;
	अक्षर *cpuid = perf_pmu__अ_लोpuid(pmu);
	पूर्णांक i;

	/* on some platक्रमms which uses cpus map, cpuid can be शून्य क्रम
	 * PMUs other than CORE PMUs.
	 */
	अगर (!cpuid)
		वापस शून्य;

	i = 0;
	क्रम (;;) अणु
		map = &pmu_events_map[i++];
		अगर (!map->table) अणु
			map = शून्य;
			अवरोध;
		पूर्ण

		अगर (!म_भेद_cpuid_str(map->cpuid, cpuid))
			अवरोध;
	पूर्ण
	मुक्त(cpuid);
	वापस map;
पूर्ण

काष्ठा pmu_events_map *__weak pmu_events_map__find(व्योम)
अणु
	वापस perf_pmu__find_map(शून्य);
पूर्ण

bool pmu_uncore_alias_match(स्थिर अक्षर *pmu_name, स्थिर अक्षर *name)
अणु
	अक्षर *पंचांगp = शून्य, *tok, *str;
	bool res;

	str = strdup(pmu_name);
	अगर (!str)
		वापस false;

	/*
	 * uncore alias may be from dअगरferent PMU with common prefix
	 */
	tok = म_मोहर_r(str, ",", &पंचांगp);
	अगर (म_भेदन(pmu_name, tok, म_माप(tok))) अणु
		res = false;
		जाओ out;
	पूर्ण

	/*
	 * Match more complex aliases where the alias name is a comma-delimited
	 * list of tokens, orderly contained in the matching PMU name.
	 *
	 * Example: For alias "socket,pmuname" and PMU "socketX_pmunameY", we
	 *	    match "socket" in "socketX_pmunameY" and then "pmuname" in
	 *	    "pmunameY".
	 */
	क्रम (; tok; name += म_माप(tok), tok = म_मोहर_r(शून्य, ",", &पंचांगp)) अणु
		name = म_माला(name, tok);
		अगर (!name) अणु
			res = false;
			जाओ out;
		पूर्ण
	पूर्ण

	res = true;
out:
	मुक्त(str);
	वापस res;
पूर्ण

/*
 * From the pmu_events_map, find the table of PMU events that corresponds
 * to the current running CPU. Then, add all PMU events from that table
 * as aliases.
 */
व्योम pmu_add_cpu_aliases_map(काष्ठा list_head *head, काष्ठा perf_pmu *pmu,
			     काष्ठा pmu_events_map *map)
अणु
	पूर्णांक i;
	स्थिर अक्षर *name = pmu->name;
	/*
	 * Found a matching PMU events table. Create aliases
	 */
	i = 0;
	जबतक (1) अणु
		स्थिर अक्षर *cpu_name = is_arm_pmu_core(name) ? name : "cpu";
		काष्ठा pmu_event *pe = &map->table[i++];
		स्थिर अक्षर *pname = pe->pmu ? pe->pmu : cpu_name;

		अगर (!pe->name) अणु
			अगर (pe->metric_group || pe->metric_name)
				जारी;
			अवरोध;
		पूर्ण

		अगर (pmu_is_uncore(name) &&
		    pmu_uncore_alias_match(pname, name))
			जाओ new_alias;

		अगर (म_भेद(pname, name))
			जारी;

new_alias:
		/* need type casts to override 'const' */
		__perf_pmu__new_alias(head, शून्य, (अक्षर *)pe->name,
				(अक्षर *)pe->desc, (अक्षर *)pe->event,
				pe);
	पूर्ण
पूर्ण

अटल व्योम pmu_add_cpu_aliases(काष्ठा list_head *head, काष्ठा perf_pmu *pmu)
अणु
	काष्ठा pmu_events_map *map;

	map = perf_pmu__find_map(pmu);
	अगर (!map)
		वापस;

	pmu_add_cpu_aliases_map(head, pmu, map);
पूर्ण

व्योम pmu_क्रम_each_sys_event(pmu_sys_event_iter_fn fn, व्योम *data)
अणु
	पूर्णांक i = 0;

	जबतक (1) अणु
		काष्ठा pmu_sys_events *event_table;
		पूर्णांक j = 0;

		event_table = &pmu_sys_event_tables[i++];

		अगर (!event_table->table)
			अवरोध;

		जबतक (1) अणु
			काष्ठा pmu_event *pe = &event_table->table[j++];
			पूर्णांक ret;

			अगर (!pe->name && !pe->metric_group && !pe->metric_name)
				अवरोध;

			ret = fn(pe, data);
			अगर (ret)
				अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

काष्ठा pmu_sys_event_iter_data अणु
	काष्ठा list_head *head;
	काष्ठा perf_pmu *pmu;
पूर्ण;

अटल पूर्णांक pmu_add_sys_aliases_iter_fn(काष्ठा pmu_event *pe, व्योम *data)
अणु
	काष्ठा pmu_sys_event_iter_data *idata = data;
	काष्ठा perf_pmu *pmu = idata->pmu;

	अगर (!pe->name) अणु
		अगर (pe->metric_group || pe->metric_name)
			वापस 0;
		वापस -EINVAL;
	पूर्ण

	अगर (!pe->compat || !pe->pmu)
		वापस 0;

	अगर (!म_भेद(pmu->id, pe->compat) &&
	    pmu_uncore_alias_match(pe->pmu, pmu->name)) अणु
		__perf_pmu__new_alias(idata->head, शून्य,
				      (अक्षर *)pe->name,
				      (अक्षर *)pe->desc,
				      (अक्षर *)pe->event,
				      pe);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम pmu_add_sys_aliases(काष्ठा list_head *head, काष्ठा perf_pmu *pmu)
अणु
	काष्ठा pmu_sys_event_iter_data idata = अणु
		.head = head,
		.pmu = pmu,
	पूर्ण;

	अगर (!pmu->id)
		वापस;

	pmu_क्रम_each_sys_event(pmu_add_sys_aliases_iter_fn, &idata);
पूर्ण

काष्ठा perf_event_attr * __weak
perf_pmu__get_शेष_config(काष्ठा perf_pmu *pmu __maybe_unused)
अणु
	वापस शून्य;
पूर्ण

अटल पूर्णांक pmu_max_precise(स्थिर अक्षर *name)
अणु
	अक्षर path[PATH_MAX];
	पूर्णांक max_precise = -1;

	scnम_लिखो(path, PATH_MAX,
		 "bus/event_source/devices/%s/caps/max_precise",
		 name);

	sysfs__पढ़ो_पूर्णांक(path, &max_precise);
	वापस max_precise;
पूर्ण

अटल काष्ठा perf_pmu *pmu_lookup(स्थिर अक्षर *name)
अणु
	काष्ठा perf_pmu *pmu;
	LIST_HEAD(क्रमmat);
	LIST_HEAD(aliases);
	__u32 type;

	/*
	 * The pmu data we store & need consists of the pmu
	 * type value and क्रमmat definitions. Load both right
	 * now.
	 */
	अगर (pmu_क्रमmat(name, &क्रमmat))
		वापस शून्य;

	/*
	 * Check the type first to aव्योम unnecessary work.
	 */
	अगर (pmu_type(name, &type))
		वापस शून्य;

	अगर (pmu_aliases(name, &aliases))
		वापस शून्य;

	pmu = zalloc(माप(*pmu));
	अगर (!pmu)
		वापस शून्य;

	pmu->cpus = pmu_cpumask(name);
	pmu->name = strdup(name);
	pmu->type = type;
	pmu->is_uncore = pmu_is_uncore(name);
	अगर (pmu->is_uncore)
		pmu->id = pmu_id(name);
	pmu->is_hybrid = perf_pmu__hybrid_mounted(name);
	pmu->max_precise = pmu_max_precise(name);
	pmu_add_cpu_aliases(&aliases, pmu);
	pmu_add_sys_aliases(&aliases, pmu);

	INIT_LIST_HEAD(&pmu->क्रमmat);
	INIT_LIST_HEAD(&pmu->aliases);
	INIT_LIST_HEAD(&pmu->caps);
	list_splice(&क्रमmat, &pmu->क्रमmat);
	list_splice(&aliases, &pmu->aliases);
	list_add_tail(&pmu->list, &pmus);

	अगर (pmu->is_hybrid)
		list_add_tail(&pmu->hybrid_list, &perf_pmu__hybrid_pmus);

	pmu->शेष_config = perf_pmu__get_शेष_config(pmu);

	वापस pmu;
पूर्ण

अटल काष्ठा perf_pmu *pmu_find(स्थिर अक्षर *name)
अणु
	काष्ठा perf_pmu *pmu;

	list_क्रम_each_entry(pmu, &pmus, list)
		अगर (!म_भेद(pmu->name, name))
			वापस pmu;

	वापस शून्य;
पूर्ण

काष्ठा perf_pmu *perf_pmu__find_by_type(अचिन्हित पूर्णांक type)
अणु
	काष्ठा perf_pmu *pmu;

	list_क्रम_each_entry(pmu, &pmus, list)
		अगर (pmu->type == type)
			वापस pmu;

	वापस शून्य;
पूर्ण

काष्ठा perf_pmu *perf_pmu__scan(काष्ठा perf_pmu *pmu)
अणु
	/*
	 * pmu iterator: If pmu is शून्य, we start at the begin,
	 * otherwise वापस the next pmu. Returns शून्य on end.
	 */
	अगर (!pmu) अणु
		pmu_पढ़ो_sysfs();
		pmu = list_prepare_entry(pmu, &pmus, list);
	पूर्ण
	list_क्रम_each_entry_जारी(pmu, &pmus, list)
		वापस pmu;
	वापस शून्य;
पूर्ण

काष्ठा perf_pmu *evsel__find_pmu(काष्ठा evsel *evsel)
अणु
	काष्ठा perf_pmu *pmu = शून्य;

	जबतक ((pmu = perf_pmu__scan(pmu)) != शून्य) अणु
		अगर (pmu->type == evsel->core.attr.type)
			अवरोध;
	पूर्ण

	वापस pmu;
पूर्ण

bool evsel__is_aux_event(काष्ठा evsel *evsel)
अणु
	काष्ठा perf_pmu *pmu = evsel__find_pmu(evsel);

	वापस pmu && pmu->auxtrace;
पूर्ण

काष्ठा perf_pmu *perf_pmu__find(स्थिर अक्षर *name)
अणु
	काष्ठा perf_pmu *pmu;

	/*
	 * Once PMU is loaded it stays in the list,
	 * so we keep us from multiple पढ़ोing/parsing
	 * the pmu क्रमmat definitions.
	 */
	pmu = pmu_find(name);
	अगर (pmu)
		वापस pmu;

	वापस pmu_lookup(name);
पूर्ण

अटल काष्ठा perf_pmu_क्रमmat *
pmu_find_क्रमmat(काष्ठा list_head *क्रमmats, स्थिर अक्षर *name)
अणु
	काष्ठा perf_pmu_क्रमmat *क्रमmat;

	list_क्रम_each_entry(क्रमmat, क्रमmats, list)
		अगर (!म_भेद(क्रमmat->name, name))
			वापस क्रमmat;

	वापस शून्य;
पूर्ण

__u64 perf_pmu__क्रमmat_bits(काष्ठा list_head *क्रमmats, स्थिर अक्षर *name)
अणु
	काष्ठा perf_pmu_क्रमmat *क्रमmat = pmu_find_क्रमmat(क्रमmats, name);
	__u64 bits = 0;
	पूर्णांक fbit;

	अगर (!क्रमmat)
		वापस 0;

	क्रम_each_set_bit(fbit, क्रमmat->bits, PERF_PMU_FORMAT_BITS)
		bits |= 1ULL << fbit;

	वापस bits;
पूर्ण

पूर्णांक perf_pmu__क्रमmat_type(काष्ठा list_head *क्रमmats, स्थिर अक्षर *name)
अणु
	काष्ठा perf_pmu_क्रमmat *क्रमmat = pmu_find_क्रमmat(क्रमmats, name);

	अगर (!क्रमmat)
		वापस -1;

	वापस क्रमmat->value;
पूर्ण

/*
 * Sets value based on the क्रमmat definition (क्रमmat parameter)
 * and unक्रमmatted value (value parameter).
 */
अटल व्योम pmu_क्रमmat_value(अचिन्हित दीर्घ *क्रमmat, __u64 value, __u64 *v,
			     bool zero)
अणु
	अचिन्हित दीर्घ fbit, vbit;

	क्रम (fbit = 0, vbit = 0; fbit < PERF_PMU_FORMAT_BITS; fbit++) अणु

		अगर (!test_bit(fbit, क्रमmat))
			जारी;

		अगर (value & (1llu << vbit++))
			*v |= (1llu << fbit);
		अन्यथा अगर (zero)
			*v &= ~(1llu << fbit);
	पूर्ण
पूर्ण

अटल __u64 pmu_क्रमmat_max_value(स्थिर अचिन्हित दीर्घ *क्रमmat)
अणु
	पूर्णांक w;

	w = biपंचांगap_weight(क्रमmat, PERF_PMU_FORMAT_BITS);
	अगर (!w)
		वापस 0;
	अगर (w < 64)
		वापस (1ULL << w) - 1;
	वापस -1;
पूर्ण

/*
 * Term is a string term, and might be a param-term. Try to look up it's value
 * in the reमुख्यing terms.
 * - We have a term like "base-or-format-term=param-term",
 * - We need to find the value supplied क्रम "param-term" (with param-term named
 *   in a config string) later on in the term list.
 */
अटल पूर्णांक pmu_resolve_param_term(काष्ठा parse_events_term *term,
				  काष्ठा list_head *head_terms,
				  __u64 *value)
अणु
	काष्ठा parse_events_term *t;

	list_क्रम_each_entry(t, head_terms, list) अणु
		अगर (t->type_val == PARSE_EVENTS__TERM_TYPE_NUM &&
		    t->config && !म_भेद(t->config, term->config)) अणु
			t->used = true;
			*value = t->val.num;
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (verbose > 0)
		म_लिखो("Required parameter '%s' not specified\n", term->config);

	वापस -1;
पूर्ण

अटल अक्षर *pmu_क्रमmats_string(काष्ठा list_head *क्रमmats)
अणु
	काष्ठा perf_pmu_क्रमmat *क्रमmat;
	अक्षर *str = शून्य;
	काष्ठा strbuf buf = STRBUF_INIT;
	अचिन्हित i = 0;

	अगर (!क्रमmats)
		वापस शून्य;

	/* sysfs exported terms */
	list_क्रम_each_entry(क्रमmat, क्रमmats, list)
		अगर (strbuf_addf(&buf, i++ ? ",%s" : "%s", क्रमmat->name) < 0)
			जाओ error;

	str = strbuf_detach(&buf, शून्य);
error:
	strbuf_release(&buf);

	वापस str;
पूर्ण

/*
 * Setup one of config[12] attr members based on the
 * user input data - term parameter.
 */
अटल पूर्णांक pmu_config_term(स्थिर अक्षर *pmu_name,
			   काष्ठा list_head *क्रमmats,
			   काष्ठा perf_event_attr *attr,
			   काष्ठा parse_events_term *term,
			   काष्ठा list_head *head_terms,
			   bool zero, काष्ठा parse_events_error *err)
अणु
	काष्ठा perf_pmu_क्रमmat *क्रमmat;
	__u64 *vp;
	__u64 val, max_val;

	/*
	 * If this is a parameter we've alपढ़ोy used क्रम parameterized-eval,
	 * skip it in normal eval.
	 */
	अगर (term->used)
		वापस 0;

	/*
	 * Hardcoded terms should be alपढ़ोy in, so nothing
	 * to be करोne क्रम them.
	 */
	अगर (parse_events__is_hardcoded_term(term))
		वापस 0;

	क्रमmat = pmu_find_क्रमmat(क्रमmats, term->config);
	अगर (!क्रमmat) अणु
		अक्षर *pmu_term = pmu_क्रमmats_string(क्रमmats);
		अक्षर *unknown_term;
		अक्षर *help_msg;

		अगर (aप्र_लिखो(&unknown_term,
				"unknown term '%s' for pmu '%s'",
				term->config, pmu_name) < 0)
			unknown_term = शून्य;
		help_msg = parse_events_क्रमmats_error_string(pmu_term);
		अगर (err) अणु
			parse_events__handle_error(err, term->err_term,
						   unknown_term,
						   help_msg);
		पूर्ण अन्यथा अणु
			pr_debug("%s (%s)\n", unknown_term, help_msg);
			मुक्त(unknown_term);
		पूर्ण
		मुक्त(pmu_term);
		वापस -EINVAL;
	पूर्ण

	चयन (क्रमmat->value) अणु
	हाल PERF_PMU_FORMAT_VALUE_CONFIG:
		vp = &attr->config;
		अवरोध;
	हाल PERF_PMU_FORMAT_VALUE_CONFIG1:
		vp = &attr->config1;
		अवरोध;
	हाल PERF_PMU_FORMAT_VALUE_CONFIG2:
		vp = &attr->config2;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/*
	 * Either directly use a numeric term, or try to translate string terms
	 * using event parameters.
	 */
	अगर (term->type_val == PARSE_EVENTS__TERM_TYPE_NUM) अणु
		अगर (term->no_value &&
		    biपंचांगap_weight(क्रमmat->bits, PERF_PMU_FORMAT_BITS) > 1) अणु
			अगर (err) अणु
				parse_events__handle_error(err, term->err_val,
					   strdup("no value assigned for term"),
					   शून्य);
			पूर्ण
			वापस -EINVAL;
		पूर्ण

		val = term->val.num;
	पूर्ण अन्यथा अगर (term->type_val == PARSE_EVENTS__TERM_TYPE_STR) अणु
		अगर (म_भेद(term->val.str, "?")) अणु
			अगर (verbose > 0) अणु
				pr_info("Invalid sysfs entry %s=%s\n",
						term->config, term->val.str);
			पूर्ण
			अगर (err) अणु
				parse_events__handle_error(err, term->err_val,
					strdup("expected numeric value"),
					शून्य);
			पूर्ण
			वापस -EINVAL;
		पूर्ण

		अगर (pmu_resolve_param_term(term, head_terms, &val))
			वापस -EINVAL;
	पूर्ण अन्यथा
		वापस -EINVAL;

	max_val = pmu_क्रमmat_max_value(क्रमmat->bits);
	अगर (val > max_val) अणु
		अगर (err) अणु
			अक्षर *err_str;

			parse_events__handle_error(err, term->err_val,
				aप्र_लिखो(&err_str,
				    "value too big for format, maximum is %llu",
				    (अचिन्हित दीर्घ दीर्घ)max_val) < 0
				    ? strdup("value too big for format")
				    : err_str,
				    शून्य);
			वापस -EINVAL;
		पूर्ण
		/*
		 * Assume we करोn't care अगर !err, in which हाल the value will be
		 * silently truncated.
		 */
	पूर्ण

	pmu_क्रमmat_value(क्रमmat->bits, val, vp, zero);
	वापस 0;
पूर्ण

पूर्णांक perf_pmu__config_terms(स्थिर अक्षर *pmu_name, काष्ठा list_head *क्रमmats,
			   काष्ठा perf_event_attr *attr,
			   काष्ठा list_head *head_terms,
			   bool zero, काष्ठा parse_events_error *err)
अणु
	काष्ठा parse_events_term *term;

	list_क्रम_each_entry(term, head_terms, list) अणु
		अगर (pmu_config_term(pmu_name, क्रमmats, attr, term, head_terms,
				    zero, err))
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Configures event's 'attr' parameter based on the:
 * 1) users input - specअगरied in terms parameter
 * 2) pmu क्रमmat definitions - specअगरied by pmu parameter
 */
पूर्णांक perf_pmu__config(काष्ठा perf_pmu *pmu, काष्ठा perf_event_attr *attr,
		     काष्ठा list_head *head_terms,
		     काष्ठा parse_events_error *err)
अणु
	bool zero = !!pmu->शेष_config;

	attr->type = pmu->type;
	वापस perf_pmu__config_terms(pmu->name, &pmu->क्रमmat, attr,
				      head_terms, zero, err);
पूर्ण

अटल काष्ठा perf_pmu_alias *pmu_find_alias(काष्ठा perf_pmu *pmu,
					     काष्ठा parse_events_term *term)
अणु
	काष्ठा perf_pmu_alias *alias;
	अक्षर *name;

	अगर (parse_events__is_hardcoded_term(term))
		वापस शून्य;

	अगर (term->type_val == PARSE_EVENTS__TERM_TYPE_NUM) अणु
		अगर (term->val.num != 1)
			वापस शून्य;
		अगर (pmu_find_क्रमmat(&pmu->क्रमmat, term->config))
			वापस शून्य;
		name = term->config;
	पूर्ण अन्यथा अगर (term->type_val == PARSE_EVENTS__TERM_TYPE_STR) अणु
		अगर (strहालcmp(term->config, "event"))
			वापस शून्य;
		name = term->val.str;
	पूर्ण अन्यथा अणु
		वापस शून्य;
	पूर्ण

	list_क्रम_each_entry(alias, &pmu->aliases, list) अणु
		अगर (!strहालcmp(alias->name, name))
			वापस alias;
	पूर्ण
	वापस शून्य;
पूर्ण


अटल पूर्णांक check_info_data(काष्ठा perf_pmu_alias *alias,
			   काष्ठा perf_pmu_info *info)
अणु
	/*
	 * Only one term in event definition can
	 * define unit, scale and snapshot, fail
	 * अगर there's more than one.
	 */
	अगर ((info->unit && alias->unit[0]) ||
	    (info->scale && alias->scale) ||
	    (info->snapshot && alias->snapshot))
		वापस -EINVAL;

	अगर (alias->unit[0])
		info->unit = alias->unit;

	अगर (alias->scale)
		info->scale = alias->scale;

	अगर (alias->snapshot)
		info->snapshot = alias->snapshot;

	वापस 0;
पूर्ण

/*
 * Find alias in the terms list and replace it with the terms
 * defined क्रम the alias
 */
पूर्णांक perf_pmu__check_alias(काष्ठा perf_pmu *pmu, काष्ठा list_head *head_terms,
			  काष्ठा perf_pmu_info *info)
अणु
	काष्ठा parse_events_term *term, *h;
	काष्ठा perf_pmu_alias *alias;
	पूर्णांक ret;

	info->per_pkg = false;

	/*
	 * Mark unit and scale as not set
	 * (dअगरferent from शेष values, see below)
	 */
	info->unit     = शून्य;
	info->scale    = 0.0;
	info->snapshot = false;
	info->metric_expr = शून्य;
	info->metric_name = शून्य;

	list_क्रम_each_entry_safe(term, h, head_terms, list) अणु
		alias = pmu_find_alias(pmu, term);
		अगर (!alias)
			जारी;
		ret = pmu_alias_terms(alias, &term->list);
		अगर (ret)
			वापस ret;

		ret = check_info_data(alias, info);
		अगर (ret)
			वापस ret;

		अगर (alias->per_pkg)
			info->per_pkg = true;
		info->metric_expr = alias->metric_expr;
		info->metric_name = alias->metric_name;

		list_del_init(&term->list);
		parse_events_term__delete(term);
	पूर्ण

	/*
	 * अगर no unit or scale found in aliases, then
	 * set शेषs as क्रम evsel
	 * unit cannot left to शून्य
	 */
	अगर (info->unit == शून्य)
		info->unit   = "";

	अगर (info->scale == 0.0)
		info->scale  = 1.0;

	वापस 0;
पूर्ण

पूर्णांक perf_pmu__new_क्रमmat(काष्ठा list_head *list, अक्षर *name,
			 पूर्णांक config, अचिन्हित दीर्घ *bits)
अणु
	काष्ठा perf_pmu_क्रमmat *क्रमmat;

	क्रमmat = zalloc(माप(*क्रमmat));
	अगर (!क्रमmat)
		वापस -ENOMEM;

	क्रमmat->name = strdup(name);
	क्रमmat->value = config;
	स_नकल(क्रमmat->bits, bits, माप(क्रमmat->bits));

	list_add_tail(&क्रमmat->list, list);
	वापस 0;
पूर्ण

व्योम perf_pmu__set_क्रमmat(अचिन्हित दीर्घ *bits, दीर्घ from, दीर्घ to)
अणु
	दीर्घ b;

	अगर (!to)
		to = from;

	स_रखो(bits, 0, BITS_TO_BYTES(PERF_PMU_FORMAT_BITS));
	क्रम (b = from; b <= to; b++)
		set_bit(b, bits);
पूर्ण

व्योम perf_pmu__del_क्रमmats(काष्ठा list_head *क्रमmats)
अणु
	काष्ठा perf_pmu_क्रमmat *fmt, *पंचांगp;

	list_क्रम_each_entry_safe(fmt, पंचांगp, क्रमmats, list) अणु
		list_del(&fmt->list);
		मुक्त(fmt->name);
		मुक्त(fmt);
	पूर्ण
पूर्ण

अटल पूर्णांक sub_non_neg(पूर्णांक a, पूर्णांक b)
अणु
	अगर (b > a)
		वापस 0;
	वापस a - b;
पूर्ण

अटल अक्षर *क्रमmat_alias(अक्षर *buf, पूर्णांक len, काष्ठा perf_pmu *pmu,
			  काष्ठा perf_pmu_alias *alias)
अणु
	काष्ठा parse_events_term *term;
	पूर्णांक used = snम_लिखो(buf, len, "%s/%s", pmu->name, alias->name);

	list_क्रम_each_entry(term, &alias->terms, list) अणु
		अगर (term->type_val == PARSE_EVENTS__TERM_TYPE_STR)
			used += snम_लिखो(buf + used, sub_non_neg(len, used),
					",%s=%s", term->config,
					term->val.str);
	पूर्ण

	अगर (sub_non_neg(len, used) > 0) अणु
		buf[used] = '/';
		used++;
	पूर्ण
	अगर (sub_non_neg(len, used) > 0) अणु
		buf[used] = '\0';
		used++;
	पूर्ण अन्यथा
		buf[len - 1] = '\0';

	वापस buf;
पूर्ण

अटल अक्षर *क्रमmat_alias_or(अक्षर *buf, पूर्णांक len, काष्ठा perf_pmu *pmu,
			     काष्ठा perf_pmu_alias *alias)
अणु
	snम_लिखो(buf, len, "%s OR %s/%s/", alias->name, pmu->name, alias->name);
	वापस buf;
पूर्ण

काष्ठा sevent अणु
	अक्षर *name;
	अक्षर *desc;
	अक्षर *topic;
	अक्षर *str;
	अक्षर *pmu;
	अक्षर *metric_expr;
	अक्षर *metric_name;
	पूर्णांक is_cpu;
पूर्ण;

अटल पूर्णांक cmp_sevent(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	स्थिर काष्ठा sevent *as = a;
	स्थिर काष्ठा sevent *bs = b;

	/* Put extra events last */
	अगर (!!as->desc != !!bs->desc)
		वापस !!as->desc - !!bs->desc;
	अगर (as->topic && bs->topic) अणु
		पूर्णांक n = म_भेद(as->topic, bs->topic);

		अगर (n)
			वापस n;
	पूर्ण

	/* Order CPU core events to be first */
	अगर (as->is_cpu != bs->is_cpu)
		वापस bs->is_cpu - as->is_cpu;

	वापस म_भेद(as->name, bs->name);
पूर्ण

अटल व्योम wordwrap(अक्षर *s, पूर्णांक start, पूर्णांक max, पूर्णांक corr)
अणु
	पूर्णांक column = start;
	पूर्णांक n;

	जबतक (*s) अणु
		पूर्णांक wlen = म_खोज(s, " \t");

		अगर (column + wlen >= max && column > start) अणु
			म_लिखो("\n%*s", start, "");
			column = start + corr;
		पूर्ण
		n = म_लिखो("%s%.*s", column > start ? " " : "", wlen, s);
		अगर (n <= 0)
			अवरोध;
		s += wlen;
		column += n;
		s = skip_spaces(s);
	पूर्ण
पूर्ण

bool is_pmu_core(स्थिर अक्षर *name)
अणु
	वापस !म_भेद(name, "cpu") || is_arm_pmu_core(name);
पूर्ण

व्योम prपूर्णांक_pmu_events(स्थिर अक्षर *event_glob, bool name_only, bool quiet_flag,
			bool दीर्घ_desc, bool details_flag, bool deprecated)
अणु
	काष्ठा perf_pmu *pmu;
	काष्ठा perf_pmu_alias *alias;
	अक्षर buf[1024];
	पूर्णांक prपूर्णांकed = 0;
	पूर्णांक len, j;
	काष्ठा sevent *aliases;
	पूर्णांक numdesc = 0;
	पूर्णांक columns = pager_get_columns();
	अक्षर *topic = शून्य;

	pmu = शून्य;
	len = 0;
	जबतक ((pmu = perf_pmu__scan(pmu)) != शून्य) अणु
		list_क्रम_each_entry(alias, &pmu->aliases, list)
			len++;
		अगर (pmu->selectable)
			len++;
	पूर्ण
	aliases = zalloc(माप(काष्ठा sevent) * len);
	अगर (!aliases)
		जाओ out_enomem;
	pmu = शून्य;
	j = 0;
	जबतक ((pmu = perf_pmu__scan(pmu)) != शून्य) अणु
		list_क्रम_each_entry(alias, &pmu->aliases, list) अणु
			अक्षर *name = alias->desc ? alias->name :
				क्रमmat_alias(buf, माप(buf), pmu, alias);
			bool is_cpu = is_pmu_core(pmu->name);

			अगर (alias->deprecated && !deprecated)
				जारी;

			अगर (event_glob != शून्य &&
			    !(strglobmatch_noहाल(name, event_glob) ||
			      (!is_cpu && strglobmatch_noहाल(alias->name,
						       event_glob)) ||
			      (alias->topic &&
			       strglobmatch_noहाल(alias->topic, event_glob))))
				जारी;

			अगर (is_cpu && !name_only && !alias->desc)
				name = क्रमmat_alias_or(buf, माप(buf), pmu, alias);

			aliases[j].name = name;
			अगर (is_cpu && !name_only && !alias->desc)
				aliases[j].name = क्रमmat_alias_or(buf,
								  माप(buf),
								  pmu, alias);
			aliases[j].name = strdup(aliases[j].name);
			अगर (!aliases[j].name)
				जाओ out_enomem;

			aliases[j].desc = दीर्घ_desc ? alias->दीर्घ_desc :
						alias->desc;
			aliases[j].topic = alias->topic;
			aliases[j].str = alias->str;
			aliases[j].pmu = pmu->name;
			aliases[j].metric_expr = alias->metric_expr;
			aliases[j].metric_name = alias->metric_name;
			aliases[j].is_cpu = is_cpu;
			j++;
		पूर्ण
		अगर (pmu->selectable &&
		    (event_glob == शून्य || strglobmatch(pmu->name, event_glob))) अणु
			अक्षर *s;
			अगर (aप्र_लिखो(&s, "%s//", pmu->name) < 0)
				जाओ out_enomem;
			aliases[j].name = s;
			j++;
		पूर्ण
	पूर्ण
	len = j;
	क्विक(aliases, len, माप(काष्ठा sevent), cmp_sevent);
	क्रम (j = 0; j < len; j++) अणु
		/* Skip duplicates */
		अगर (j > 0 && !म_भेद(aliases[j].name, aliases[j - 1].name))
			जारी;
		अगर (name_only) अणु
			म_लिखो("%s ", aliases[j].name);
			जारी;
		पूर्ण
		अगर (aliases[j].desc && !quiet_flag) अणु
			अगर (numdesc++ == 0)
				म_लिखो("\n");
			अगर (aliases[j].topic && (!topic ||
					म_भेद(topic, aliases[j].topic))) अणु
				म_लिखो("%s%s:\n", topic ? "\n" : "",
						aliases[j].topic);
				topic = aliases[j].topic;
			पूर्ण
			म_लिखो("  %-50s\n", aliases[j].name);
			म_लिखो("%*s", 8, "[");
			wordwrap(aliases[j].desc, 8, columns, 0);
			म_लिखो("]\n");
			अगर (details_flag) अणु
				म_लिखो("%*s%s/%s/ ", 8, "", aliases[j].pmu, aliases[j].str);
				अगर (aliases[j].metric_name)
					म_लिखो(" MetricName: %s", aliases[j].metric_name);
				अगर (aliases[j].metric_expr)
					म_लिखो(" MetricExpr: %s", aliases[j].metric_expr);
				अक्षर_दो('\n');
			पूर्ण
		पूर्ण अन्यथा
			म_लिखो("  %-50s [Kernel PMU event]\n", aliases[j].name);
		prपूर्णांकed++;
	पूर्ण
	अगर (prपूर्णांकed && pager_in_use())
		म_लिखो("\n");
out_मुक्त:
	क्रम (j = 0; j < len; j++)
		zमुक्त(&aliases[j].name);
	zमुक्त(&aliases);
	वापस;

out_enomem:
	म_लिखो("FATAL: not enough memory to print PMU events\n");
	अगर (aliases)
		जाओ out_मुक्त;
पूर्ण

bool pmu_have_event(स्थिर अक्षर *pname, स्थिर अक्षर *name)
अणु
	काष्ठा perf_pmu *pmu;
	काष्ठा perf_pmu_alias *alias;

	pmu = शून्य;
	जबतक ((pmu = perf_pmu__scan(pmu)) != शून्य) अणु
		अगर (म_भेद(pname, pmu->name))
			जारी;
		list_क्रम_each_entry(alias, &pmu->aliases, list)
			अगर (!म_भेद(alias->name, name))
				वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल खाता *perf_pmu__खोलो_file(काष्ठा perf_pmu *pmu, स्थिर अक्षर *name)
अणु
	अक्षर path[PATH_MAX];
	स्थिर अक्षर *sysfs;

	sysfs = sysfs__mountpoपूर्णांक();
	अगर (!sysfs)
		वापस शून्य;

	snम_लिखो(path, PATH_MAX,
		 "%s" EVENT_SOURCE_DEVICE_PATH "%s/%s", sysfs, pmu->name, name);
	अगर (!file_available(path))
		वापस शून्य;
	वापस ख_खोलो(path, "r");
पूर्ण

पूर्णांक perf_pmu__scan_file(काष्ठा perf_pmu *pmu, स्थिर अक्षर *name, स्थिर अक्षर *fmt,
			...)
अणु
	बहु_सूची args;
	खाता *file;
	पूर्णांक ret = खातापूर्ण;

	बहु_शुरू(args, fmt);
	file = perf_pmu__खोलो_file(pmu, name);
	अगर (file) अणु
		ret = vख_पूछो(file, fmt, args);
		ख_बंद(file);
	पूर्ण
	बहु_पूर्ण(args);
	वापस ret;
पूर्ण

अटल पूर्णांक perf_pmu__new_caps(काष्ठा list_head *list, अक्षर *name, अक्षर *value)
अणु
	काष्ठा perf_pmu_caps *caps = zalloc(माप(*caps));

	अगर (!caps)
		वापस -ENOMEM;

	caps->name = strdup(name);
	अगर (!caps->name)
		जाओ मुक्त_caps;
	caps->value = strndup(value, म_माप(value) - 1);
	अगर (!caps->value)
		जाओ मुक्त_name;
	list_add_tail(&caps->list, list);
	वापस 0;

मुक्त_name:
	zमुक्त(caps->name);
मुक्त_caps:
	मुक्त(caps);

	वापस -ENOMEM;
पूर्ण

/*
 * Reading/parsing the given pmu capabilities, which should be located at:
 * /sys/bus/event_source/devices/<dev>/caps as sysfs group attributes.
 * Return the number of capabilities
 */
पूर्णांक perf_pmu__caps_parse(काष्ठा perf_pmu *pmu)
अणु
	काष्ठा stat st;
	अक्षर caps_path[PATH_MAX];
	स्थिर अक्षर *sysfs = sysfs__mountpoपूर्णांक();
	सूची *caps_dir;
	काष्ठा dirent *evt_ent;
	पूर्णांक nr_caps = 0;

	अगर (!sysfs)
		वापस -1;

	snम_लिखो(caps_path, PATH_MAX,
		 "%s" EVENT_SOURCE_DEVICE_PATH "%s/caps", sysfs, pmu->name);

	अगर (stat(caps_path, &st) < 0)
		वापस 0;	/* no error अगर caps करोes not exist */

	caps_dir = सूची_खोलो(caps_path);
	अगर (!caps_dir)
		वापस -EINVAL;

	जबतक ((evt_ent = सूची_पढ़ो(caps_dir)) != शून्य) अणु
		अक्षर path[PATH_MAX + NAME_MAX + 1];
		अक्षर *name = evt_ent->d_name;
		अक्षर value[128];
		खाता *file;

		अगर (!म_भेद(name, ".") || !म_भेद(name, ".."))
			जारी;

		snम_लिखो(path, माप(path), "%s/%s", caps_path, name);

		file = ख_खोलो(path, "r");
		अगर (!file)
			जारी;

		अगर (!ख_माला_लो(value, माप(value), file) ||
		    (perf_pmu__new_caps(&pmu->caps, name, value) < 0)) अणु
			ख_बंद(file);
			जारी;
		पूर्ण

		nr_caps++;
		ख_बंद(file);
	पूर्ण

	बंद_सूची(caps_dir);

	वापस nr_caps;
पूर्ण

व्योम perf_pmu__warn_invalid_config(काष्ठा perf_pmu *pmu, __u64 config,
				   अक्षर *name)
अणु
	काष्ठा perf_pmu_क्रमmat *क्रमmat;
	__u64 masks = 0, bits;
	अक्षर buf[100];
	अचिन्हित पूर्णांक i;

	list_क्रम_each_entry(क्रमmat, &pmu->क्रमmat, list)	अणु
		अगर (क्रमmat->value != PERF_PMU_FORMAT_VALUE_CONFIG)
			जारी;

		क्रम_each_set_bit(i, क्रमmat->bits, PERF_PMU_FORMAT_BITS)
			masks |= 1ULL << i;
	पूर्ण

	/*
	 * Kernel करोesn't export any valid क्रमmat bits.
	 */
	अगर (masks == 0)
		वापस;

	bits = config & ~masks;
	अगर (bits == 0)
		वापस;

	biपंचांगap_scnम_लिखो((अचिन्हित दीर्घ *)&bits, माप(bits) * 8, buf, माप(buf));

	pr_warning("WARNING: event '%s' not valid (bits %s of config "
		   "'%llx' not supported by kernel)!\n",
		   name ?: "N/A", buf, config);
पूर्ण

bool perf_pmu__has_hybrid(व्योम)
अणु
	अगर (!hybrid_scanned) अणु
		hybrid_scanned = true;
		perf_pmu__scan(शून्य);
	पूर्ण

	वापस !list_empty(&perf_pmu__hybrid_pmus);
पूर्ण
