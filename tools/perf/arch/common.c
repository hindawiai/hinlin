<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <सीमा.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश "common.h"
#समावेश "../util/env.h"
#समावेश "../util/debug.h"
#समावेश <linux/zभाग.स>

स्थिर अक्षर *स्थिर arc_triplets[] = अणु
	"arc-linux-",
	"arc-snps-linux-uclibc-",
	"arc-snps-linux-gnu-",
	शून्य
पूर्ण;

स्थिर अक्षर *स्थिर arm_triplets[] = अणु
	"arm-eabi-",
	"arm-linux-androideabi-",
	"arm-unknown-linux-",
	"arm-unknown-linux-gnu-",
	"arm-unknown-linux-gnueabi-",
	"arm-linux-gnu-",
	"arm-linux-gnueabihf-",
	"arm-none-eabi-",
	शून्य
पूर्ण;

स्थिर अक्षर *स्थिर arm64_triplets[] = अणु
	"aarch64-linux-android-",
	"aarch64-linux-gnu-",
	शून्य
पूर्ण;

स्थिर अक्षर *स्थिर घातerpc_triplets[] = अणु
	"powerpc-unknown-linux-gnu-",
	"powerpc-linux-gnu-",
	"powerpc64-unknown-linux-gnu-",
	"powerpc64-linux-gnu-",
	"powerpc64le-linux-gnu-",
	शून्य
पूर्ण;

स्थिर अक्षर *स्थिर s390_triplets[] = अणु
	"s390-ibm-linux-",
	"s390x-linux-gnu-",
	शून्य
पूर्ण;

स्थिर अक्षर *स्थिर sh_triplets[] = अणु
	"sh-unknown-linux-gnu-",
	"sh64-unknown-linux-gnu-",
	"sh-linux-gnu-",
	"sh64-linux-gnu-",
	शून्य
पूर्ण;

स्थिर अक्षर *स्थिर sparc_triplets[] = अणु
	"sparc-unknown-linux-gnu-",
	"sparc64-unknown-linux-gnu-",
	"sparc64-linux-gnu-",
	शून्य
पूर्ण;

स्थिर अक्षर *स्थिर x86_triplets[] = अणु
	"x86_64-pc-linux-gnu-",
	"x86_64-unknown-linux-gnu-",
	"i686-pc-linux-gnu-",
	"i586-pc-linux-gnu-",
	"i486-pc-linux-gnu-",
	"i386-pc-linux-gnu-",
	"i686-linux-android-",
	"i686-android-linux-",
	"x86_64-linux-gnu-",
	"i586-linux-gnu-",
	शून्य
पूर्ण;

स्थिर अक्षर *स्थिर mips_triplets[] = अणु
	"mips-unknown-linux-gnu-",
	"mipsel-linux-android-",
	"mips-linux-gnu-",
	"mips64-linux-gnu-",
	"mips64el-linux-gnuabi64-",
	"mips64-linux-gnuabi64-",
	"mipsel-linux-gnu-",
	शून्य
पूर्ण;

अटल bool lookup_path(अक्षर *name)
अणु
	bool found = false;
	अक्षर *path, *पंचांगp = शून्य;
	अक्षर buf[PATH_MAX];
	अक्षर *env = दो_पर्या("PATH");

	अगर (!env)
		वापस false;

	env = strdup(env);
	अगर (!env)
		वापस false;

	path = म_मोहर_r(env, ":", &पंचांगp);
	जबतक (path) अणु
		scnम_लिखो(buf, माप(buf), "%s/%s", path, name);
		अगर (access(buf, F_OK) == 0) अणु
			found = true;
			अवरोध;
		पूर्ण
		path = म_मोहर_r(शून्य, ":", &पंचांगp);
	पूर्ण
	मुक्त(env);
	वापस found;
पूर्ण

अटल पूर्णांक lookup_triplets(स्थिर अक्षर *स्थिर *triplets, स्थिर अक्षर *name)
अणु
	पूर्णांक i;
	अक्षर buf[PATH_MAX];

	क्रम (i = 0; triplets[i] != शून्य; i++) अणु
		scnम_लिखो(buf, माप(buf), "%s%s", triplets[i], name);
		अगर (lookup_path(buf))
			वापस i;
	पूर्ण
	वापस -1;
पूर्ण

अटल पूर्णांक perf_env__lookup_binutils_path(काष्ठा perf_env *env,
					  स्थिर अक्षर *name, स्थिर अक्षर **path)
अणु
	पूर्णांक idx;
	स्थिर अक्षर *arch = perf_env__arch(env), *cross_env;
	स्थिर अक्षर *स्थिर *path_list;
	अक्षर *buf = शून्य;

	/*
	 * We करोn't need to try to find objdump path क्रम native प्रणाली.
	 * Just use शेष binutils path (e.g.: "objdump").
	 */
	अगर (!म_भेद(perf_env__arch(शून्य), arch))
		जाओ out;

	cross_env = दो_पर्या("CROSS_COMPILE");
	अगर (cross_env) अणु
		अगर (aप्र_लिखो(&buf, "%s%s", cross_env, name) < 0)
			जाओ out_error;
		अगर (buf[0] == '/') अणु
			अगर (access(buf, F_OK) == 0)
				जाओ out;
			जाओ out_error;
		पूर्ण
		अगर (lookup_path(buf))
			जाओ out;
		zमुक्त(&buf);
	पूर्ण

	अगर (!म_भेद(arch, "arc"))
		path_list = arc_triplets;
	अन्यथा अगर (!म_भेद(arch, "arm"))
		path_list = arm_triplets;
	अन्यथा अगर (!म_भेद(arch, "arm64"))
		path_list = arm64_triplets;
	अन्यथा अगर (!म_भेद(arch, "powerpc"))
		path_list = घातerpc_triplets;
	अन्यथा अगर (!म_भेद(arch, "sh"))
		path_list = sh_triplets;
	अन्यथा अगर (!म_भेद(arch, "s390"))
		path_list = s390_triplets;
	अन्यथा अगर (!म_भेद(arch, "sparc"))
		path_list = sparc_triplets;
	अन्यथा अगर (!म_भेद(arch, "x86"))
		path_list = x86_triplets;
	अन्यथा अगर (!म_भेद(arch, "mips"))
		path_list = mips_triplets;
	अन्यथा अणु
		ui__error("binutils for %s not supported.\n", arch);
		जाओ out_error;
	पूर्ण

	idx = lookup_triplets(path_list, name);
	अगर (idx < 0) अणु
		ui__error("Please install %s for %s.\n"
			  "You can add it to PATH, set CROSS_COMPILE or "
			  "override the default using --%s.\n",
			  name, arch, name);
		जाओ out_error;
	पूर्ण

	अगर (aप्र_लिखो(&buf, "%s%s", path_list[idx], name) < 0)
		जाओ out_error;

out:
	*path = buf;
	वापस 0;
out_error:
	मुक्त(buf);
	*path = शून्य;
	वापस -1;
पूर्ण

पूर्णांक perf_env__lookup_objdump(काष्ठा perf_env *env, स्थिर अक्षर **path)
अणु
	/*
	 * For live mode, env->arch will be शून्य and we can use
	 * the native objdump tool.
	 */
	अगर (env->arch == शून्य)
		वापस 0;

	वापस perf_env__lookup_binutils_path(env, "objdump", path);
पूर्ण

/*
 * Some architectures have a single address space क्रम kernel and user addresses,
 * which makes it possible to determine अगर an address is in kernel space or user
 * space.
 */
bool perf_env__single_address_space(काष्ठा perf_env *env)
अणु
	वापस म_भेद(perf_env__arch(env), "sparc");
पूर्ण
