<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * I'm tired of करोing "vsnprintf()" etc just to खोलो a
 * file, so here's a "return static buffer with printf"
 * पूर्णांकerface क्रम paths.
 *
 * It's obviously not thread-safe. Sue me. But it's quite
 * useful क्रम करोing things like
 *
 *   f = खोलो(mkpath("%s/%s.perf", base, name), O_RDONLY);
 *
 * which is what it's deचिन्हित क्रम.
 */
#समावेश "path.h"
#समावेश "cache.h"
#समावेश <linux/kernel.h>
#समावेश <सीमा.स>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <dirent.h>
#समावेश <unistd.h>

अटल अक्षर bad_path[] = "/bad-path/";
/*
 * One hack:
 */
अटल अक्षर *get_pathname(व्योम)
अणु
	अटल अक्षर pathname_array[4][PATH_MAX];
	अटल पूर्णांक idx;

	वापस pathname_array[3 & ++idx];
पूर्ण

अटल अक्षर *cleanup_path(अक्षर *path)
अणु
	/* Clean it up */
	अगर (!स_भेद(path, "./", 2)) अणु
		path += 2;
		जबतक (*path == '/')
			path++;
	पूर्ण
	वापस path;
पूर्ण

अक्षर *mkpath(स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	अचिन्हित len;
	अक्षर *pathname = get_pathname();

	बहु_शुरू(args, fmt);
	len = vsnम_लिखो(pathname, PATH_MAX, fmt, args);
	बहु_पूर्ण(args);
	अगर (len >= PATH_MAX)
		वापस bad_path;
	वापस cleanup_path(pathname);
पूर्ण

पूर्णांक path__join(अक्षर *bf, माप_प्रकार size, स्थिर अक्षर *path1, स्थिर अक्षर *path2)
अणु
	वापस scnम_लिखो(bf, size, "%s%s%s", path1, path1[0] ? "/" : "", path2);
पूर्ण

पूर्णांक path__join3(अक्षर *bf, माप_प्रकार size, स्थिर अक्षर *path1, स्थिर अक्षर *path2, स्थिर अक्षर *path3)
अणु
	वापस scnम_लिखो(bf, size, "%s%s%s%s%s", path1, path1[0] ? "/" : "",
			 path2, path2[0] ? "/" : "", path3);
पूर्ण

bool is_regular_file(स्थिर अक्षर *file)
अणु
	काष्ठा stat st;

	अगर (stat(file, &st))
		वापस false;

	वापस S_ISREG(st.st_mode);
पूर्ण

/* Helper function क्रम fileप्रणालीs that वापस a dent->d_type DT_UNKNOWN */
bool is_directory(स्थिर अक्षर *base_path, स्थिर काष्ठा dirent *dent)
अणु
	अक्षर path[PATH_MAX];
	काष्ठा stat st;

	प्र_लिखो(path, "%s/%s", base_path, dent->d_name);
	अगर (stat(path, &st))
		वापस false;

	वापस S_ISसूची(st.st_mode);
पूर्ण
