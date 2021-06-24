<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "util.h"
#समावेश "debug.h"
#समावेश "event.h"
#समावेश <api/fs/fs.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/utsname.h>
#समावेश <dirent.h>
#समावेश <fcntl.h>
#समावेश <पूर्णांकtypes.h>
#समावेश <संकेत.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <त्रुटिसं.स>
#समावेश <सीमा.स>
#समावेश <linux/capability.h>
#समावेश <linux/kernel.h>
#समावेश <linux/log2.h>
#समावेश <linux/समय64.h>
#समावेश <unistd.h>
#समावेश "cap.h"
#समावेश "strlist.h"
#समावेश "string2.h"

/*
 * XXX We need to find a better place क्रम these things...
 */

bool perf_singlethपढ़ोed = true;

व्योम perf_set_singlethपढ़ोed(व्योम)
अणु
	perf_singlethपढ़ोed = true;
पूर्ण

व्योम perf_set_multithपढ़ोed(व्योम)
अणु
	perf_singlethपढ़ोed = false;
पूर्ण

पूर्णांक sysctl_perf_event_max_stack = PERF_MAX_STACK_DEPTH;
पूर्णांक sysctl_perf_event_max_contexts_per_stack = PERF_MAX_CONTEXTS_PER_STACK;

पूर्णांक sysctl__max_stack(व्योम)
अणु
	पूर्णांक value;

	अगर (sysctl__पढ़ो_पूर्णांक("kernel/perf_event_max_stack", &value) == 0)
		sysctl_perf_event_max_stack = value;

	अगर (sysctl__पढ़ो_पूर्णांक("kernel/perf_event_max_contexts_per_stack", &value) == 0)
		sysctl_perf_event_max_contexts_per_stack = value;

	वापस sysctl_perf_event_max_stack;
पूर्ण

bool sysctl__nmi_watchकरोg_enabled(व्योम)
अणु
	अटल bool cached;
	अटल bool nmi_watchकरोg;
	पूर्णांक value;

	अगर (cached)
		वापस nmi_watchकरोg;

	अगर (sysctl__पढ़ो_पूर्णांक("kernel/nmi_watchdog", &value) < 0)
		वापस false;

	nmi_watchकरोg = (value > 0) ? true : false;
	cached = true;

	वापस nmi_watchकरोg;
पूर्ण

bool test_attr__enabled;

bool perf_host  = true;
bool perf_guest = false;

व्योम event_attr_init(काष्ठा perf_event_attr *attr)
अणु
	अगर (!perf_host)
		attr->exclude_host  = 1;
	अगर (!perf_guest)
		attr->exclude_guest = 1;
	/* to capture ABI version */
	attr->size = माप(*attr);
पूर्ण

पूर्णांक सूची_गढ़ो_p(अक्षर *path, mode_t mode)
अणु
	काष्ठा stat st;
	पूर्णांक err;
	अक्षर *d = path;

	अगर (*d != '/')
		वापस -1;

	अगर (stat(path, &st) == 0)
		वापस 0;

	जबतक (*++d == '/');

	जबतक ((d = म_अक्षर(d, '/'))) अणु
		*d = '\0';
		err = stat(path, &st) && सूची_गढ़ो(path, mode);
		*d++ = '/';
		अगर (err)
			वापस -1;
		जबतक (*d == '/')
			++d;
	पूर्ण
	वापस (stat(path, &st) && सूची_गढ़ो(path, mode)) ? -1 : 0;
पूर्ण

अटल bool match_pat(अक्षर *file, स्थिर अक्षर **pat)
अणु
	पूर्णांक i = 0;

	अगर (!pat)
		वापस true;

	जबतक (pat[i]) अणु
		अगर (strglobmatch(file, pat[i]))
			वापस true;

		i++;
	पूर्ण

	वापस false;
पूर्ण

/*
 * The depth specअगरy how deep the removal will go.
 * 0       - will हटाओ only files under the 'path' directory
 * 1 .. x  - will भागe in x-level deep under the 'path' directory
 *
 * If specअगरied the pat is array of string patterns ended with शून्य,
 * which are checked upon every file/directory found. Only matching
 * ones are हटाओd.
 *
 * The function वापसs:
 *    0 on success
 *   -1 on removal failure with त्रुटि_सं set
 *   -2 on pattern failure
 */
अटल पूर्णांक rm_rf_depth_pat(स्थिर अक्षर *path, पूर्णांक depth, स्थिर अक्षर **pat)
अणु
	सूची *dir;
	पूर्णांक ret;
	काष्ठा dirent *d;
	अक्षर namebuf[PATH_MAX];
	काष्ठा stat statbuf;

	/* Do not fail अगर there's no file. */
	ret = lstat(path, &statbuf);
	अगर (ret)
		वापस 0;

	/* Try to हटाओ any file we get. */
	अगर (!(statbuf.st_mode & S_IFसूची))
		वापस unlink(path);

	/* We have directory in path. */
	dir = सूची_खोलो(path);
	अगर (dir == शून्य)
		वापस -1;

	जबतक ((d = सूची_पढ़ो(dir)) != शून्य && !ret) अणु

		अगर (!म_भेद(d->d_name, ".") || !म_भेद(d->d_name, ".."))
			जारी;

		अगर (!match_pat(d->d_name, pat)) अणु
			ret =  -2;
			अवरोध;
		पूर्ण

		scnम_लिखो(namebuf, माप(namebuf), "%s/%s",
			  path, d->d_name);

		/* We have to check symbolic link itself */
		ret = lstat(namebuf, &statbuf);
		अगर (ret < 0) अणु
			pr_debug("stat failed: %s\n", namebuf);
			अवरोध;
		पूर्ण

		अगर (S_ISसूची(statbuf.st_mode))
			ret = depth ? rm_rf_depth_pat(namebuf, depth - 1, pat) : 0;
		अन्यथा
			ret = unlink(namebuf);
	पूर्ण
	बंद_सूची(dir);

	अगर (ret < 0)
		वापस ret;

	वापस सूची_हटाओ(path);
पूर्ण

अटल पूर्णांक rm_rf_kcore_dir(स्थिर अक्षर *path)
अणु
	अक्षर kcore_dir_path[PATH_MAX];
	स्थिर अक्षर *pat[] = अणु
		"kcore",
		"kallsyms",
		"modules",
		शून्य,
	पूर्ण;

	snम_लिखो(kcore_dir_path, माप(kcore_dir_path), "%s/kcore_dir", path);

	वापस rm_rf_depth_pat(kcore_dir_path, 0, pat);
पूर्ण

पूर्णांक rm_rf_perf_data(स्थिर अक्षर *path)
अणु
	स्थिर अक्षर *pat[] = अणु
		"data",
		"data.*",
		शून्य,
	पूर्ण;

	rm_rf_kcore_dir(path);

	वापस rm_rf_depth_pat(path, 0, pat);
पूर्ण

पूर्णांक rm_rf(स्थिर अक्षर *path)
अणु
	वापस rm_rf_depth_pat(path, पूर्णांक_उच्च, शून्य);
पूर्ण

/* A filter which हटाओs करोt files */
bool lsdir_no_करोt_filter(स्थिर अक्षर *name __maybe_unused, काष्ठा dirent *d)
अणु
	वापस d->d_name[0] != '.';
पूर्ण

/* lsdir पढ़ोs a directory and store it in strlist */
काष्ठा strlist *lsdir(स्थिर अक्षर *name,
		      bool (*filter)(स्थिर अक्षर *, काष्ठा dirent *))
अणु
	काष्ठा strlist *list = शून्य;
	सूची *dir;
	काष्ठा dirent *d;

	dir = सूची_खोलो(name);
	अगर (!dir)
		वापस शून्य;

	list = strlist__new(शून्य, शून्य);
	अगर (!list) अणु
		त्रुटि_सं = ENOMEM;
		जाओ out;
	पूर्ण

	जबतक ((d = सूची_पढ़ो(dir)) != शून्य) अणु
		अगर (!filter || filter(name, d))
			strlist__add(list, d->d_name);
	पूर्ण

out:
	बंद_सूची(dir);
	वापस list;
पूर्ण

माप_प्रकार hex_width(u64 v)
अणु
	माप_प्रकार n = 1;

	जबतक ((v >>= 4))
		++n;

	वापस n;
पूर्ण

पूर्णांक perf_event_paranoid(व्योम)
अणु
	पूर्णांक value;

	अगर (sysctl__पढ़ो_पूर्णांक("kernel/perf_event_paranoid", &value))
		वापस पूर्णांक_उच्च;

	वापस value;
पूर्ण

bool perf_event_paranoid_check(पूर्णांक max_level)
अणु
	वापस perf_cap__capable(CAP_SYS_ADMIN) ||
			perf_cap__capable(CAP_PERFMON) ||
			perf_event_paranoid() <= max_level;
पूर्ण

अटल पूर्णांक
fetch_ubuntu_kernel_version(अचिन्हित पूर्णांक *puपूर्णांक)
अणु
	sमाप_प्रकार len;
	माप_प्रकार line_len = 0;
	अक्षर *ptr, *line = शून्य;
	पूर्णांक version, patchlevel, sublevel, err;
	खाता *vsig;

	अगर (!puपूर्णांक)
		वापस 0;

	vsig = ख_खोलो("/proc/version_signature", "r");
	अगर (!vsig) अणु
		pr_debug("Open /proc/version_signature failed: %s\n",
			 म_त्रुटि(त्रुटि_सं));
		वापस -1;
	पूर्ण

	len = getline(&line, &line_len, vsig);
	ख_बंद(vsig);
	err = -1;
	अगर (len <= 0) अणु
		pr_debug("Reading from /proc/version_signature failed: %s\n",
			 म_त्रुटि(त्रुटि_सं));
		जाओ errout;
	पूर्ण

	ptr = म_खोजप(line, ' ');
	अगर (!ptr) अणु
		pr_debug("Parsing /proc/version_signature failed: %s\n", line);
		जाओ errout;
	पूर्ण

	err = माला_पूछो(ptr + 1, "%d.%d.%d",
		     &version, &patchlevel, &sublevel);
	अगर (err != 3) अणु
		pr_debug("Unable to get kernel version from /proc/version_signature '%s'\n",
			 line);
		जाओ errout;
	पूर्ण

	*puपूर्णांक = (version << 16) + (patchlevel << 8) + sublevel;
	err = 0;
errout:
	मुक्त(line);
	वापस err;
पूर्ण

पूर्णांक
fetch_kernel_version(अचिन्हित पूर्णांक *puपूर्णांक, अक्षर *str,
		     माप_प्रकार str_size)
अणु
	काष्ठा utsname utsname;
	पूर्णांक version, patchlevel, sublevel, err;
	bool पूर्णांक_ver_पढ़ोy = false;

	अगर (access("/proc/version_signature", R_OK) == 0)
		अगर (!fetch_ubuntu_kernel_version(puपूर्णांक))
			पूर्णांक_ver_पढ़ोy = true;

	अगर (uname(&utsname))
		वापस -1;

	अगर (str && str_size) अणु
		म_नकलन(str, utsname.release, str_size);
		str[str_size - 1] = '\0';
	पूर्ण

	अगर (!puपूर्णांक || पूर्णांक_ver_पढ़ोy)
		वापस 0;

	err = माला_पूछो(utsname.release, "%d.%d.%d",
		     &version, &patchlevel, &sublevel);

	अगर (err != 3) अणु
		pr_debug("Unable to get kernel version from uname '%s'\n",
			 utsname.release);
		वापस -1;
	पूर्ण

	*puपूर्णांक = (version << 16) + (patchlevel << 8) + sublevel;
	वापस 0;
पूर्ण

स्थिर अक्षर *perf_tip(स्थिर अक्षर *dirpath)
अणु
	काष्ठा strlist *tips;
	काष्ठा str_node *node;
	अक्षर *tip = शून्य;
	काष्ठा strlist_config conf = अणु
		.स_नाम = dirpath,
		.file_only = true,
	पूर्ण;

	tips = strlist__new("tips.txt", &conf);
	अगर (tips == शून्य)
		वापस त्रुटि_सं == ENOENT ? शून्य :
			"Tip: check path of tips.txt or get more memory! ;-p";

	अगर (strlist__nr_entries(tips) == 0)
		जाओ out;

	node = strlist__entry(tips, अक्रमom() % strlist__nr_entries(tips));
	अगर (aप्र_लिखो(&tip, "Tip: %s", node->s) < 0)
		tip = (अक्षर *)"Tip: get more memory! ;-)";

out:
	strlist__delete(tips);

	वापस tip;
पूर्ण

अक्षर *perf_exe(अक्षर *buf, पूर्णांक len)
अणु
	पूर्णांक n = पढ़ोlink("/proc/self/exe", buf, len);
	अगर (n > 0) अणु
		buf[n] = 0;
		वापस buf;
	पूर्ण
	वापस म_नकल(buf, "perf");
पूर्ण
