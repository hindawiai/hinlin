<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <यंत्र/bug.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/zभाग.स>
#समावेश <sys/समय.स>
#समावेश <sys/resource.h>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <unistd.h>
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <मानककोष.स>
#अगर_घोषित HAVE_LIBBPF_SUPPORT
#समावेश <bpf/libbpf.h>
#समावेश "bpf-event.h"
#पूर्ण_अगर
#समावेश "compress.h"
#समावेश "env.h"
#समावेश "namespaces.h"
#समावेश "path.h"
#समावेश "map.h"
#समावेश "symbol.h"
#समावेश "srcline.h"
#समावेश "dso.h"
#समावेश "dsos.h"
#समावेश "machine.h"
#समावेश "auxtrace.h"
#समावेश "util.h" /* O_CLOEXEC क्रम older प्रणालीs */
#समावेश "debug.h"
#समावेश "string2.h"
#समावेश "vdso.h"

अटल स्थिर अक्षर * स्थिर debuglink_paths[] = अणु
	"%.0s%s",
	"%s/%s",
	"%s/.debug/%s",
	"/usr/lib/debug%s/%s"
पूर्ण;

अक्षर dso__symtab_origin(स्थिर काष्ठा dso *dso)
अणु
	अटल स्थिर अक्षर origin[] = अणु
		[DSO_BINARY_TYPE__KALLSYMS]			= 'k',
		[DSO_BINARY_TYPE__VMLINUX]			= 'v',
		[DSO_BINARY_TYPE__JAVA_JIT]			= 'j',
		[DSO_BINARY_TYPE__DEBUGLINK]			= 'l',
		[DSO_BINARY_TYPE__BUILD_ID_CACHE]		= 'B',
		[DSO_BINARY_TYPE__BUILD_ID_CACHE_DEBUGINFO]	= 'D',
		[DSO_BINARY_TYPE__FEDORA_DEBUGINFO]		= 'f',
		[DSO_BINARY_TYPE__UBUNTU_DEBUGINFO]		= 'u',
		[DSO_BINARY_TYPE__MIXEDUP_UBUNTU_DEBUGINFO]	= 'x',
		[DSO_BINARY_TYPE__OPENEMBEDDED_DEBUGINFO]	= 'o',
		[DSO_BINARY_TYPE__BUILDID_DEBUGINFO]		= 'b',
		[DSO_BINARY_TYPE__SYSTEM_PATH_DSO]		= 'd',
		[DSO_BINARY_TYPE__SYSTEM_PATH_KMODULE]		= 'K',
		[DSO_BINARY_TYPE__SYSTEM_PATH_KMODULE_COMP]	= 'm',
		[DSO_BINARY_TYPE__GUEST_KALLSYMS]		= 'g',
		[DSO_BINARY_TYPE__GUEST_KMODULE]		= 'G',
		[DSO_BINARY_TYPE__GUEST_KMODULE_COMP]		= 'M',
		[DSO_BINARY_TYPE__GUEST_VMLINUX]		= 'V',
	पूर्ण;

	अगर (dso == शून्य || dso->symtab_type == DSO_BINARY_TYPE__NOT_FOUND)
		वापस '!';
	वापस origin[dso->symtab_type];
पूर्ण

पूर्णांक dso__पढ़ो_binary_type_filename(स्थिर काष्ठा dso *dso,
				   क्रमागत dso_binary_type type,
				   अक्षर *root_dir, अक्षर *filename, माप_प्रकार size)
अणु
	अक्षर build_id_hex[SBUILD_ID_SIZE];
	पूर्णांक ret = 0;
	माप_प्रकार len;

	चयन (type) अणु
	हाल DSO_BINARY_TYPE__DEBUGLINK:
	अणु
		स्थिर अक्षर *last_slash;
		अक्षर dso_dir[PATH_MAX];
		अक्षर symfile[PATH_MAX];
		अचिन्हित पूर्णांक i;

		len = __symbol__join_symfs(filename, size, dso->दीर्घ_name);
		last_slash = filename + len;
		जबतक (last_slash != filename && *last_slash != '/')
			last_slash--;

		म_नकलन(dso_dir, filename, last_slash - filename);
		dso_dir[last_slash-filename] = '\0';

		अगर (!is_regular_file(filename)) अणु
			ret = -1;
			अवरोध;
		पूर्ण

		ret = filename__पढ़ो_debuglink(filename, symfile, PATH_MAX);
		अगर (ret)
			अवरोध;

		/* Check predefined locations where debug file might reside */
		ret = -1;
		क्रम (i = 0; i < ARRAY_SIZE(debuglink_paths); i++) अणु
			snम_लिखो(filename, size,
					debuglink_paths[i], dso_dir, symfile);
			अगर (is_regular_file(filename)) अणु
				ret = 0;
				अवरोध;
			पूर्ण
		पूर्ण

		अवरोध;
	पूर्ण
	हाल DSO_BINARY_TYPE__BUILD_ID_CACHE:
		अगर (dso__build_id_filename(dso, filename, size, false) == शून्य)
			ret = -1;
		अवरोध;

	हाल DSO_BINARY_TYPE__BUILD_ID_CACHE_DEBUGINFO:
		अगर (dso__build_id_filename(dso, filename, size, true) == शून्य)
			ret = -1;
		अवरोध;

	हाल DSO_BINARY_TYPE__FEDORA_DEBUGINFO:
		len = __symbol__join_symfs(filename, size, "/usr/lib/debug");
		snम_लिखो(filename + len, size - len, "%s.debug", dso->दीर्घ_name);
		अवरोध;

	हाल DSO_BINARY_TYPE__UBUNTU_DEBUGINFO:
		len = __symbol__join_symfs(filename, size, "/usr/lib/debug");
		snम_लिखो(filename + len, size - len, "%s", dso->दीर्घ_name);
		अवरोध;

	हाल DSO_BINARY_TYPE__MIXEDUP_UBUNTU_DEBUGINFO:
		/*
		 * Ubuntu can mixup /usr/lib with /lib, putting debuginfo in
		 * /usr/lib/debug/lib when it is expected to be in
		 * /usr/lib/debug/usr/lib
		 */
		अगर (म_माप(dso->दीर्घ_name) < 9 ||
		    म_भेदन(dso->दीर्घ_name, "/usr/lib/", 9)) अणु
			ret = -1;
			अवरोध;
		पूर्ण
		len = __symbol__join_symfs(filename, size, "/usr/lib/debug");
		snम_लिखो(filename + len, size - len, "%s", dso->दीर्घ_name + 4);
		अवरोध;

	हाल DSO_BINARY_TYPE__OPENEMBEDDED_DEBUGINFO:
	अणु
		स्थिर अक्षर *last_slash;
		माप_प्रकार dir_size;

		last_slash = dso->दीर्घ_name + dso->दीर्घ_name_len;
		जबतक (last_slash != dso->दीर्घ_name && *last_slash != '/')
			last_slash--;

		len = __symbol__join_symfs(filename, size, "");
		dir_size = last_slash - dso->दीर्घ_name + 2;
		अगर (dir_size > (size - len)) अणु
			ret = -1;
			अवरोध;
		पूर्ण
		len += scnम_लिखो(filename + len, dir_size, "%s",  dso->दीर्घ_name);
		len += scnम_लिखो(filename + len , size - len, ".debug%s",
								last_slash);
		अवरोध;
	पूर्ण

	हाल DSO_BINARY_TYPE__BUILDID_DEBUGINFO:
		अगर (!dso->has_build_id) अणु
			ret = -1;
			अवरोध;
		पूर्ण

		build_id__प्र_लिखो(&dso->bid, build_id_hex);
		len = __symbol__join_symfs(filename, size, "/usr/lib/debug/.build-id/");
		snम_लिखो(filename + len, size - len, "%.2s/%s.debug",
			 build_id_hex, build_id_hex + 2);
		अवरोध;

	हाल DSO_BINARY_TYPE__VMLINUX:
	हाल DSO_BINARY_TYPE__GUEST_VMLINUX:
	हाल DSO_BINARY_TYPE__SYSTEM_PATH_DSO:
		__symbol__join_symfs(filename, size, dso->दीर्घ_name);
		अवरोध;

	हाल DSO_BINARY_TYPE__GUEST_KMODULE:
	हाल DSO_BINARY_TYPE__GUEST_KMODULE_COMP:
		path__join3(filename, size, symbol_conf.symfs,
			    root_dir, dso->दीर्घ_name);
		अवरोध;

	हाल DSO_BINARY_TYPE__SYSTEM_PATH_KMODULE:
	हाल DSO_BINARY_TYPE__SYSTEM_PATH_KMODULE_COMP:
		__symbol__join_symfs(filename, size, dso->दीर्घ_name);
		अवरोध;

	हाल DSO_BINARY_TYPE__KCORE:
	हाल DSO_BINARY_TYPE__GUEST_KCORE:
		snम_लिखो(filename, size, "%s", dso->दीर्घ_name);
		अवरोध;

	शेष:
	हाल DSO_BINARY_TYPE__KALLSYMS:
	हाल DSO_BINARY_TYPE__GUEST_KALLSYMS:
	हाल DSO_BINARY_TYPE__JAVA_JIT:
	हाल DSO_BINARY_TYPE__BPF_PROG_INFO:
	हाल DSO_BINARY_TYPE__BPF_IMAGE:
	हाल DSO_BINARY_TYPE__OOL:
	हाल DSO_BINARY_TYPE__NOT_FOUND:
		ret = -1;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

क्रमागत अणु
	COMP_ID__NONE = 0,
पूर्ण;

अटल स्थिर काष्ठा अणु
	स्थिर अक्षर *fmt;
	पूर्णांक (*decompress)(स्थिर अक्षर *input, पूर्णांक output);
	bool (*is_compressed)(स्थिर अक्षर *input);
पूर्ण compressions[] = अणु
	[COMP_ID__NONE] = अणु .fmt = शून्य, पूर्ण,
#अगर_घोषित HAVE_ZLIB_SUPPORT
	अणु "gz", gzip_decompress_to_file, gzip_is_compressed पूर्ण,
#पूर्ण_अगर
#अगर_घोषित HAVE_LZMA_SUPPORT
	अणु "xz", lzma_decompress_to_file, lzma_is_compressed पूर्ण,
#पूर्ण_अगर
	अणु शून्य, शून्य, शून्य पूर्ण,
पूर्ण;

अटल पूर्णांक is_supported_compression(स्थिर अक्षर *ext)
अणु
	अचिन्हित i;

	क्रम (i = 1; compressions[i].fmt; i++) अणु
		अगर (!म_भेद(ext, compressions[i].fmt))
			वापस i;
	पूर्ण
	वापस COMP_ID__NONE;
पूर्ण

bool is_kernel_module(स्थिर अक्षर *pathname, पूर्णांक cpumode)
अणु
	काष्ठा kmod_path m;
	पूर्णांक mode = cpumode & PERF_RECORD_MISC_CPUMODE_MASK;

	WARN_ONCE(mode != cpumode,
		  "Internal error: passing unmasked cpumode (%x) to is_kernel_module",
		  cpumode);

	चयन (mode) अणु
	हाल PERF_RECORD_MISC_USER:
	हाल PERF_RECORD_MISC_HYPERVISOR:
	हाल PERF_RECORD_MISC_GUEST_USER:
		वापस false;
	/* Treat PERF_RECORD_MISC_CPUMODE_UNKNOWN as kernel */
	शेष:
		अगर (kmod_path__parse(&m, pathname)) अणु
			pr_err("Failed to check whether %s is a kernel module or not. Assume it is.",
					pathname);
			वापस true;
		पूर्ण
	पूर्ण

	वापस m.kmod;
पूर्ण

bool dso__needs_decompress(काष्ठा dso *dso)
अणु
	वापस dso->symtab_type == DSO_BINARY_TYPE__SYSTEM_PATH_KMODULE_COMP ||
		dso->symtab_type == DSO_BINARY_TYPE__GUEST_KMODULE_COMP;
पूर्ण

पूर्णांक filename__decompress(स्थिर अक्षर *name, अक्षर *pathname,
			 माप_प्रकार len, पूर्णांक comp, पूर्णांक *err)
अणु
	अक्षर पंचांगpbuf[] = KMOD_DECOMP_NAME;
	पूर्णांक fd = -1;

	/*
	 * We have proper compression id क्रम DSO and yet the file
	 * behind the 'name' can still be plain uncompressed object.
	 *
	 * The reason is behind the logic we खोलो the DSO object files,
	 * when we try all possible 'debug' objects until we find the
	 * data. So even अगर the DSO is represented by 'krava.xz' module,
	 * we can end up here खोलोing ~/.debug/....23432432/debug' file
	 * which is not compressed.
	 *
	 * To keep this transparent, we detect this and वापस the file
	 * descriptor to the uncompressed file.
	 */
	अगर (!compressions[comp].is_compressed(name))
		वापस खोलो(name, O_RDONLY);

	fd = mkstemp(पंचांगpbuf);
	अगर (fd < 0) अणु
		*err = त्रुटि_सं;
		वापस -1;
	पूर्ण

	अगर (compressions[comp].decompress(name, fd)) अणु
		*err = DSO_LOAD_ERRNO__DECOMPRESSION_FAILURE;
		बंद(fd);
		fd = -1;
	पूर्ण

	अगर (!pathname || (fd < 0))
		unlink(पंचांगpbuf);

	अगर (pathname && (fd >= 0))
		strlcpy(pathname, पंचांगpbuf, len);

	वापस fd;
पूर्ण

अटल पूर्णांक decompress_kmodule(काष्ठा dso *dso, स्थिर अक्षर *name,
			      अक्षर *pathname, माप_प्रकार len)
अणु
	अगर (!dso__needs_decompress(dso))
		वापस -1;

	अगर (dso->comp == COMP_ID__NONE)
		वापस -1;

	वापस filename__decompress(name, pathname, len, dso->comp,
				    &dso->load_त्रुटि_सं);
पूर्ण

पूर्णांक dso__decompress_kmodule_fd(काष्ठा dso *dso, स्थिर अक्षर *name)
अणु
	वापस decompress_kmodule(dso, name, शून्य, 0);
पूर्ण

पूर्णांक dso__decompress_kmodule_path(काष्ठा dso *dso, स्थिर अक्षर *name,
				 अक्षर *pathname, माप_प्रकार len)
अणु
	पूर्णांक fd = decompress_kmodule(dso, name, pathname, len);

	बंद(fd);
	वापस fd >= 0 ? 0 : -1;
पूर्ण

/*
 * Parses kernel module specअगरied in @path and updates
 * @m argument like:
 *
 *    @comp - true अगर @path contains supported compression suffix,
 *            false otherwise
 *    @kmod - true अगर @path contains '.ko' suffix in right position,
 *            false otherwise
 *    @name - अगर (@alloc_name && @kmod) is true, it contains strdup-ed base name
 *            of the kernel module without suffixes, otherwise strudup-ed
 *            base name of @path
 *    @ext  - अगर (@alloc_ext && @comp) is true, it contains strdup-ed string
 *            the compression suffix
 *
 * Returns 0 अगर there's no strdup error, -ENOMEM otherwise.
 */
पूर्णांक __kmod_path__parse(काष्ठा kmod_path *m, स्थिर अक्षर *path,
		       bool alloc_name)
अणु
	स्थिर अक्षर *name = म_खोजप(path, '/');
	स्थिर अक्षर *ext  = म_खोजप(path, '.');
	bool is_simple_name = false;

	स_रखो(m, 0x0, माप(*m));
	name = name ? name + 1 : path;

	/*
	 * '.' is also a valid अक्षरacter क्रम module name. For example:
	 * [aaa.bbb] is a valid module name. '[' should have higher
	 * priority than '.ko' suffix.
	 *
	 * The kernel names are from machine__mmap_name. Such
	 * name should beदीर्घ to kernel itself, not kernel module.
	 */
	अगर (name[0] == '[') अणु
		is_simple_name = true;
		अगर ((म_भेदन(name, "[kernel.kallsyms]", 17) == 0) ||
		    (म_भेदन(name, "[guest.kernel.kallsyms", 22) == 0) ||
		    (म_भेदन(name, "[vdso]", 6) == 0) ||
		    (म_भेदन(name, "[vdso32]", 8) == 0) ||
		    (म_भेदन(name, "[vdsox32]", 9) == 0) ||
		    (म_भेदन(name, "[vsyscall]", 10) == 0)) अणु
			m->kmod = false;

		पूर्ण अन्यथा
			m->kmod = true;
	पूर्ण

	/* No extension, just वापस name. */
	अगर ((ext == शून्य) || is_simple_name) अणु
		अगर (alloc_name) अणु
			m->name = strdup(name);
			वापस m->name ? 0 : -ENOMEM;
		पूर्ण
		वापस 0;
	पूर्ण

	m->comp = is_supported_compression(ext + 1);
	अगर (m->comp > COMP_ID__NONE)
		ext -= 3;

	/* Check .ko extension only अगर there's enough name left. */
	अगर (ext > name)
		m->kmod = !म_भेदन(ext, ".ko", 3);

	अगर (alloc_name) अणु
		अगर (m->kmod) अणु
			अगर (aप्र_लिखो(&m->name, "[%.*s]", (पूर्णांक) (ext - name), name) == -1)
				वापस -ENOMEM;
		पूर्ण अन्यथा अणु
			अगर (aप्र_लिखो(&m->name, "%s", name) == -1)
				वापस -ENOMEM;
		पूर्ण

		strreplace(m->name, '-', '_');
	पूर्ण

	वापस 0;
पूर्ण

व्योम dso__set_module_info(काष्ठा dso *dso, काष्ठा kmod_path *m,
			  काष्ठा machine *machine)
अणु
	अगर (machine__is_host(machine))
		dso->symtab_type = DSO_BINARY_TYPE__SYSTEM_PATH_KMODULE;
	अन्यथा
		dso->symtab_type = DSO_BINARY_TYPE__GUEST_KMODULE;

	/* _KMODULE_COMP should be next to _KMODULE */
	अगर (m->kmod && m->comp) अणु
		dso->symtab_type++;
		dso->comp = m->comp;
	पूर्ण

	dso__set_लघु_name(dso, strdup(m->name), true);
पूर्ण

/*
 * Global list of खोलो DSOs and the counter.
 */
अटल LIST_HEAD(dso__data_खोलो);
अटल दीर्घ dso__data_खोलो_cnt;
अटल pthपढ़ो_mutex_t dso__data_खोलो_lock = PTHREAD_MUTEX_INITIALIZER;

अटल व्योम dso__list_add(काष्ठा dso *dso)
अणु
	list_add_tail(&dso->data.खोलो_entry, &dso__data_खोलो);
	dso__data_खोलो_cnt++;
पूर्ण

अटल व्योम dso__list_del(काष्ठा dso *dso)
अणु
	list_del_init(&dso->data.खोलो_entry);
	WARN_ONCE(dso__data_खोलो_cnt <= 0,
		  "DSO data fd counter out of bounds.");
	dso__data_खोलो_cnt--;
पूर्ण

अटल व्योम बंद_first_dso(व्योम);

अटल पूर्णांक करो_खोलो(अक्षर *name)
अणु
	पूर्णांक fd;
	अक्षर sbuf[STRERR_बफ_मानE];

	करो अणु
		fd = खोलो(name, O_RDONLY|O_CLOEXEC);
		अगर (fd >= 0)
			वापस fd;

		pr_debug("dso open failed: %s\n",
			 str_error_r(त्रुटि_सं, sbuf, माप(sbuf)));
		अगर (!dso__data_खोलो_cnt || त्रुटि_सं != EMखाता)
			अवरोध;

		बंद_first_dso();
	पूर्ण जबतक (1);

	वापस -1;
पूर्ण

अटल पूर्णांक __खोलो_dso(काष्ठा dso *dso, काष्ठा machine *machine)
अणु
	पूर्णांक fd = -EINVAL;
	अक्षर *root_dir = (अक्षर *)"";
	अक्षर *name = दो_स्मृति(PATH_MAX);
	bool decomp = false;

	अगर (!name)
		वापस -ENOMEM;

	अगर (machine)
		root_dir = machine->root_dir;

	अगर (dso__पढ़ो_binary_type_filename(dso, dso->binary_type,
					    root_dir, name, PATH_MAX))
		जाओ out;

	अगर (!is_regular_file(name))
		जाओ out;

	अगर (dso__needs_decompress(dso)) अणु
		अक्षर newpath[KMOD_DECOMP_LEN];
		माप_प्रकार len = माप(newpath);

		अगर (dso__decompress_kmodule_path(dso, name, newpath, len) < 0) अणु
			fd = -dso->load_त्रुटि_सं;
			जाओ out;
		पूर्ण

		decomp = true;
		म_नकल(name, newpath);
	पूर्ण

	fd = करो_खोलो(name);

	अगर (decomp)
		unlink(name);

out:
	मुक्त(name);
	वापस fd;
पूर्ण

अटल व्योम check_data_बंद(व्योम);

/**
 * dso_बंद - Open DSO data file
 * @dso: dso object
 *
 * Open @dso's data file descriptor and updates
 * list/count of खोलो DSO objects.
 */
अटल पूर्णांक खोलो_dso(काष्ठा dso *dso, काष्ठा machine *machine)
अणु
	पूर्णांक fd;
	काष्ठा nscookie nsc;

	अगर (dso->binary_type != DSO_BINARY_TYPE__BUILD_ID_CACHE)
		nsinfo__mountns_enter(dso->nsinfo, &nsc);
	fd = __खोलो_dso(dso, machine);
	अगर (dso->binary_type != DSO_BINARY_TYPE__BUILD_ID_CACHE)
		nsinfo__mountns_निकास(&nsc);

	अगर (fd >= 0) अणु
		dso__list_add(dso);
		/*
		 * Check अगर we crossed the allowed number
		 * of खोलोed DSOs and बंद one अगर needed.
		 */
		check_data_बंद();
	पूर्ण

	वापस fd;
पूर्ण

अटल व्योम बंद_data_fd(काष्ठा dso *dso)
अणु
	अगर (dso->data.fd >= 0) अणु
		बंद(dso->data.fd);
		dso->data.fd = -1;
		dso->data.file_size = 0;
		dso__list_del(dso);
	पूर्ण
पूर्ण

/**
 * dso_बंद - Close DSO data file
 * @dso: dso object
 *
 * Close @dso's data file descriptor and updates
 * list/count of खोलो DSO objects.
 */
अटल व्योम बंद_dso(काष्ठा dso *dso)
अणु
	बंद_data_fd(dso);
पूर्ण

अटल व्योम बंद_first_dso(व्योम)
अणु
	काष्ठा dso *dso;

	dso = list_first_entry(&dso__data_खोलो, काष्ठा dso, data.खोलो_entry);
	बंद_dso(dso);
पूर्ण

अटल rlim_t get_fd_limit(व्योम)
अणु
	काष्ठा rlimit l;
	rlim_t limit = 0;

	/* Allow half of the current खोलो fd limit. */
	अगर (getrlimit(RLIMIT_NOखाता, &l) == 0) अणु
		अगर (l.rlim_cur == RLIM_अनन्त)
			limit = l.rlim_cur;
		अन्यथा
			limit = l.rlim_cur / 2;
	पूर्ण अन्यथा अणु
		pr_err("failed to get fd limit\n");
		limit = 1;
	पूर्ण

	वापस limit;
पूर्ण

अटल rlim_t fd_limit;

/*
 * Used only by tests/dso-data.c to reset the environment
 * क्रम tests. I करोnt expect we should change this during
 * standard runसमय.
 */
व्योम reset_fd_limit(व्योम)
अणु
	fd_limit = 0;
पूर्ण

अटल bool may_cache_fd(व्योम)
अणु
	अगर (!fd_limit)
		fd_limit = get_fd_limit();

	अगर (fd_limit == RLIM_अनन्त)
		वापस true;

	वापस fd_limit > (rlim_t) dso__data_खोलो_cnt;
पूर्ण

/*
 * Check and बंद LRU dso अगर we crossed allowed limit
 * क्रम खोलोed dso file descriptors. The limit is half
 * of the RLIMIT_NOखाता files खोलोed.
*/
अटल व्योम check_data_बंद(व्योम)
अणु
	bool cache_fd = may_cache_fd();

	अगर (!cache_fd)
		बंद_first_dso();
पूर्ण

/**
 * dso__data_बंद - Close DSO data file
 * @dso: dso object
 *
 * External पूर्णांकerface to बंद @dso's data file descriptor.
 */
व्योम dso__data_बंद(काष्ठा dso *dso)
अणु
	pthपढ़ो_mutex_lock(&dso__data_खोलो_lock);
	बंद_dso(dso);
	pthपढ़ो_mutex_unlock(&dso__data_खोलो_lock);
पूर्ण

अटल व्योम try_to_खोलो_dso(काष्ठा dso *dso, काष्ठा machine *machine)
अणु
	क्रमागत dso_binary_type binary_type_data[] = अणु
		DSO_BINARY_TYPE__BUILD_ID_CACHE,
		DSO_BINARY_TYPE__SYSTEM_PATH_DSO,
		DSO_BINARY_TYPE__NOT_FOUND,
	पूर्ण;
	पूर्णांक i = 0;

	अगर (dso->data.fd >= 0)
		वापस;

	अगर (dso->binary_type != DSO_BINARY_TYPE__NOT_FOUND) अणु
		dso->data.fd = खोलो_dso(dso, machine);
		जाओ out;
	पूर्ण

	करो अणु
		dso->binary_type = binary_type_data[i++];

		dso->data.fd = खोलो_dso(dso, machine);
		अगर (dso->data.fd >= 0)
			जाओ out;

	पूर्ण जबतक (dso->binary_type != DSO_BINARY_TYPE__NOT_FOUND);
out:
	अगर (dso->data.fd >= 0)
		dso->data.status = DSO_DATA_STATUS_OK;
	अन्यथा
		dso->data.status = DSO_DATA_STATUS_ERROR;
पूर्ण

/**
 * dso__data_get_fd - Get dso's data file descriptor
 * @dso: dso object
 * @machine: machine object
 *
 * External पूर्णांकerface to find dso's file, खोलो it and
 * वापसs file descriptor.  It should be paired with
 * dso__data_put_fd() अगर it वापसs non-negative value.
 */
पूर्णांक dso__data_get_fd(काष्ठा dso *dso, काष्ठा machine *machine)
अणु
	अगर (dso->data.status == DSO_DATA_STATUS_ERROR)
		वापस -1;

	अगर (pthपढ़ो_mutex_lock(&dso__data_खोलो_lock) < 0)
		वापस -1;

	try_to_खोलो_dso(dso, machine);

	अगर (dso->data.fd < 0)
		pthपढ़ो_mutex_unlock(&dso__data_खोलो_lock);

	वापस dso->data.fd;
पूर्ण

व्योम dso__data_put_fd(काष्ठा dso *dso __maybe_unused)
अणु
	pthपढ़ो_mutex_unlock(&dso__data_खोलो_lock);
पूर्ण

bool dso__data_status_seen(काष्ठा dso *dso, क्रमागत dso_data_status_seen by)
अणु
	u32 flag = 1 << by;

	अगर (dso->data.status_seen & flag)
		वापस true;

	dso->data.status_seen |= flag;

	वापस false;
पूर्ण

#अगर_घोषित HAVE_LIBBPF_SUPPORT
अटल sमाप_प्रकार bpf_पढ़ो(काष्ठा dso *dso, u64 offset, अक्षर *data)
अणु
	काष्ठा bpf_prog_info_node *node;
	sमाप_प्रकार size = DSO__DATA_CACHE_SIZE;
	u64 len;
	u8 *buf;

	node = perf_env__find_bpf_prog_info(dso->bpf_prog.env, dso->bpf_prog.id);
	अगर (!node || !node->info_linear) अणु
		dso->data.status = DSO_DATA_STATUS_ERROR;
		वापस -1;
	पूर्ण

	len = node->info_linear->info.jited_prog_len;
	buf = (u8 *)(uपूर्णांकptr_t)node->info_linear->info.jited_prog_insns;

	अगर (offset >= len)
		वापस -1;

	size = (sमाप_प्रकार)min(len - offset, (u64)size);
	स_नकल(data, buf + offset, size);
	वापस size;
पूर्ण

अटल पूर्णांक bpf_size(काष्ठा dso *dso)
अणु
	काष्ठा bpf_prog_info_node *node;

	node = perf_env__find_bpf_prog_info(dso->bpf_prog.env, dso->bpf_prog.id);
	अगर (!node || !node->info_linear) अणु
		dso->data.status = DSO_DATA_STATUS_ERROR;
		वापस -1;
	पूर्ण

	dso->data.file_size = node->info_linear->info.jited_prog_len;
	वापस 0;
पूर्ण
#पूर्ण_अगर // HAVE_LIBBPF_SUPPORT

अटल व्योम
dso_cache__मुक्त(काष्ठा dso *dso)
अणु
	काष्ठा rb_root *root = &dso->data.cache;
	काष्ठा rb_node *next = rb_first(root);

	pthपढ़ो_mutex_lock(&dso->lock);
	जबतक (next) अणु
		काष्ठा dso_cache *cache;

		cache = rb_entry(next, काष्ठा dso_cache, rb_node);
		next = rb_next(&cache->rb_node);
		rb_erase(&cache->rb_node, root);
		मुक्त(cache);
	पूर्ण
	pthपढ़ो_mutex_unlock(&dso->lock);
पूर्ण

अटल काष्ठा dso_cache *__dso_cache__find(काष्ठा dso *dso, u64 offset)
अणु
	स्थिर काष्ठा rb_root *root = &dso->data.cache;
	काष्ठा rb_node * स्थिर *p = &root->rb_node;
	स्थिर काष्ठा rb_node *parent = शून्य;
	काष्ठा dso_cache *cache;

	जबतक (*p != शून्य) अणु
		u64 end;

		parent = *p;
		cache = rb_entry(parent, काष्ठा dso_cache, rb_node);
		end = cache->offset + DSO__DATA_CACHE_SIZE;

		अगर (offset < cache->offset)
			p = &(*p)->rb_left;
		अन्यथा अगर (offset >= end)
			p = &(*p)->rb_right;
		अन्यथा
			वापस cache;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा dso_cache *
dso_cache__insert(काष्ठा dso *dso, काष्ठा dso_cache *new)
अणु
	काष्ठा rb_root *root = &dso->data.cache;
	काष्ठा rb_node **p = &root->rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा dso_cache *cache;
	u64 offset = new->offset;

	pthपढ़ो_mutex_lock(&dso->lock);
	जबतक (*p != शून्य) अणु
		u64 end;

		parent = *p;
		cache = rb_entry(parent, काष्ठा dso_cache, rb_node);
		end = cache->offset + DSO__DATA_CACHE_SIZE;

		अगर (offset < cache->offset)
			p = &(*p)->rb_left;
		अन्यथा अगर (offset >= end)
			p = &(*p)->rb_right;
		अन्यथा
			जाओ out;
	पूर्ण

	rb_link_node(&new->rb_node, parent, p);
	rb_insert_color(&new->rb_node, root);

	cache = शून्य;
out:
	pthपढ़ो_mutex_unlock(&dso->lock);
	वापस cache;
पूर्ण

अटल sमाप_प्रकार dso_cache__स_नकल(काष्ठा dso_cache *cache, u64 offset, u8 *data,
				 u64 size, bool out)
अणु
	u64 cache_offset = offset - cache->offset;
	u64 cache_size   = min(cache->size - cache_offset, size);

	अगर (out)
		स_नकल(data, cache->data + cache_offset, cache_size);
	अन्यथा
		स_नकल(cache->data + cache_offset, data, cache_size);
	वापस cache_size;
पूर्ण

अटल sमाप_प्रकार file_पढ़ो(काष्ठा dso *dso, काष्ठा machine *machine,
			 u64 offset, अक्षर *data)
अणु
	sमाप_प्रकार ret;

	pthपढ़ो_mutex_lock(&dso__data_खोलो_lock);

	/*
	 * dso->data.fd might be बंदd अगर other thपढ़ो खोलोed another
	 * file (dso) due to खोलो file limit (RLIMIT_NOखाता).
	 */
	try_to_खोलो_dso(dso, machine);

	अगर (dso->data.fd < 0) अणु
		dso->data.status = DSO_DATA_STATUS_ERROR;
		ret = -त्रुटि_सं;
		जाओ out;
	पूर्ण

	ret = pपढ़ो(dso->data.fd, data, DSO__DATA_CACHE_SIZE, offset);
out:
	pthपढ़ो_mutex_unlock(&dso__data_खोलो_lock);
	वापस ret;
पूर्ण

अटल काष्ठा dso_cache *dso_cache__populate(काष्ठा dso *dso,
					     काष्ठा machine *machine,
					     u64 offset, sमाप_प्रकार *ret)
अणु
	u64 cache_offset = offset & DSO__DATA_CACHE_MASK;
	काष्ठा dso_cache *cache;
	काष्ठा dso_cache *old;

	cache = zalloc(माप(*cache) + DSO__DATA_CACHE_SIZE);
	अगर (!cache) अणु
		*ret = -ENOMEM;
		वापस शून्य;
	पूर्ण
#अगर_घोषित HAVE_LIBBPF_SUPPORT
	अगर (dso->binary_type == DSO_BINARY_TYPE__BPF_PROG_INFO)
		*ret = bpf_पढ़ो(dso, cache_offset, cache->data);
	अन्यथा
#पूर्ण_अगर
	अगर (dso->binary_type == DSO_BINARY_TYPE__OOL)
		*ret = DSO__DATA_CACHE_SIZE;
	अन्यथा
		*ret = file_पढ़ो(dso, machine, cache_offset, cache->data);

	अगर (*ret <= 0) अणु
		मुक्त(cache);
		वापस शून्य;
	पूर्ण

	cache->offset = cache_offset;
	cache->size   = *ret;

	old = dso_cache__insert(dso, cache);
	अगर (old) अणु
		/* we lose the race */
		मुक्त(cache);
		cache = old;
	पूर्ण

	वापस cache;
पूर्ण

अटल काष्ठा dso_cache *dso_cache__find(काष्ठा dso *dso,
					 काष्ठा machine *machine,
					 u64 offset,
					 sमाप_प्रकार *ret)
अणु
	काष्ठा dso_cache *cache = __dso_cache__find(dso, offset);

	वापस cache ? cache : dso_cache__populate(dso, machine, offset, ret);
पूर्ण

अटल sमाप_प्रकार dso_cache_io(काष्ठा dso *dso, काष्ठा machine *machine,
			    u64 offset, u8 *data, sमाप_प्रकार size, bool out)
अणु
	काष्ठा dso_cache *cache;
	sमाप_प्रकार ret = 0;

	cache = dso_cache__find(dso, machine, offset, &ret);
	अगर (!cache)
		वापस ret;

	वापस dso_cache__स_नकल(cache, offset, data, size, out);
पूर्ण

/*
 * Reads and caches dso data DSO__DATA_CACHE_SIZE size chunks
 * in the rb_tree. Any पढ़ो to alपढ़ोy cached data is served
 * by cached data. Writes update the cache only, not the backing file.
 */
अटल sमाप_प्रकार cached_io(काष्ठा dso *dso, काष्ठा machine *machine,
			 u64 offset, u8 *data, sमाप_प्रकार size, bool out)
अणु
	sमाप_प्रकार r = 0;
	u8 *p = data;

	करो अणु
		sमाप_प्रकार ret;

		ret = dso_cache_io(dso, machine, offset, p, size, out);
		अगर (ret < 0)
			वापस ret;

		/* Reached खातापूर्ण, वापस what we have. */
		अगर (!ret)
			अवरोध;

		BUG_ON(ret > size);

		r      += ret;
		p      += ret;
		offset += ret;
		size   -= ret;

	पूर्ण जबतक (size);

	वापस r;
पूर्ण

अटल पूर्णांक file_size(काष्ठा dso *dso, काष्ठा machine *machine)
अणु
	पूर्णांक ret = 0;
	काष्ठा stat st;
	अक्षर sbuf[STRERR_बफ_मानE];

	pthपढ़ो_mutex_lock(&dso__data_खोलो_lock);

	/*
	 * dso->data.fd might be बंदd अगर other thपढ़ो खोलोed another
	 * file (dso) due to खोलो file limit (RLIMIT_NOखाता).
	 */
	try_to_खोलो_dso(dso, machine);

	अगर (dso->data.fd < 0) अणु
		ret = -त्रुटि_सं;
		dso->data.status = DSO_DATA_STATUS_ERROR;
		जाओ out;
	पूर्ण

	अगर (ख_स्थिति(dso->data.fd, &st) < 0) अणु
		ret = -त्रुटि_सं;
		pr_err("dso cache fstat failed: %s\n",
		       str_error_r(त्रुटि_सं, sbuf, माप(sbuf)));
		dso->data.status = DSO_DATA_STATUS_ERROR;
		जाओ out;
	पूर्ण
	dso->data.file_size = st.st_size;

out:
	pthपढ़ो_mutex_unlock(&dso__data_खोलो_lock);
	वापस ret;
पूर्ण

पूर्णांक dso__data_file_size(काष्ठा dso *dso, काष्ठा machine *machine)
अणु
	अगर (dso->data.file_size)
		वापस 0;

	अगर (dso->data.status == DSO_DATA_STATUS_ERROR)
		वापस -1;
#अगर_घोषित HAVE_LIBBPF_SUPPORT
	अगर (dso->binary_type == DSO_BINARY_TYPE__BPF_PROG_INFO)
		वापस bpf_size(dso);
#पूर्ण_अगर
	वापस file_size(dso, machine);
पूर्ण

/**
 * dso__data_size - Return dso data size
 * @dso: dso object
 * @machine: machine object
 *
 * Return: dso data size
 */
off_t dso__data_size(काष्ठा dso *dso, काष्ठा machine *machine)
अणु
	अगर (dso__data_file_size(dso, machine))
		वापस -1;

	/* For now just estimate dso data size is बंद to file size */
	वापस dso->data.file_size;
पूर्ण

अटल sमाप_प्रकार data_पढ़ो_ग_लिखो_offset(काष्ठा dso *dso, काष्ठा machine *machine,
				      u64 offset, u8 *data, sमाप_प्रकार size,
				      bool out)
अणु
	अगर (dso__data_file_size(dso, machine))
		वापस -1;

	/* Check the offset sanity. */
	अगर (offset > dso->data.file_size)
		वापस -1;

	अगर (offset + size < offset)
		वापस -1;

	वापस cached_io(dso, machine, offset, data, size, out);
पूर्ण

/**
 * dso__data_पढ़ो_offset - Read data from dso file offset
 * @dso: dso object
 * @machine: machine object
 * @offset: file offset
 * @data: buffer to store data
 * @size: size of the @data buffer
 *
 * External पूर्णांकerface to पढ़ो data from dso file offset. Open
 * dso data file and use cached_पढ़ो to get the data.
 */
sमाप_प्रकार dso__data_पढ़ो_offset(काष्ठा dso *dso, काष्ठा machine *machine,
			      u64 offset, u8 *data, sमाप_प्रकार size)
अणु
	अगर (dso->data.status == DSO_DATA_STATUS_ERROR)
		वापस -1;

	वापस data_पढ़ो_ग_लिखो_offset(dso, machine, offset, data, size, true);
पूर्ण

/**
 * dso__data_पढ़ो_addr - Read data from dso address
 * @dso: dso object
 * @machine: machine object
 * @add: भव memory address
 * @data: buffer to store data
 * @size: size of the @data buffer
 *
 * External पूर्णांकerface to पढ़ो data from dso address.
 */
sमाप_प्रकार dso__data_पढ़ो_addr(काष्ठा dso *dso, काष्ठा map *map,
			    काष्ठा machine *machine, u64 addr,
			    u8 *data, sमाप_प्रकार size)
अणु
	u64 offset = map->map_ip(map, addr);
	वापस dso__data_पढ़ो_offset(dso, machine, offset, data, size);
पूर्ण

/**
 * dso__data_ग_लिखो_cache_offs - Write data to dso data cache at file offset
 * @dso: dso object
 * @machine: machine object
 * @offset: file offset
 * @data: buffer to ग_लिखो
 * @size: size of the @data buffer
 *
 * Write पूर्णांकo the dso file data cache, but करो not change the file itself.
 */
sमाप_प्रकार dso__data_ग_लिखो_cache_offs(काष्ठा dso *dso, काष्ठा machine *machine,
				   u64 offset, स्थिर u8 *data_in, sमाप_प्रकार size)
अणु
	u8 *data = (u8 *)data_in; /* cast away स्थिर to use same fns क्रम r/w */

	अगर (dso->data.status == DSO_DATA_STATUS_ERROR)
		वापस -1;

	वापस data_पढ़ो_ग_लिखो_offset(dso, machine, offset, data, size, false);
पूर्ण

/**
 * dso__data_ग_लिखो_cache_addr - Write data to dso data cache at dso address
 * @dso: dso object
 * @machine: machine object
 * @add: भव memory address
 * @data: buffer to ग_लिखो
 * @size: size of the @data buffer
 *
 * External पूर्णांकerface to ग_लिखो पूर्णांकo the dso file data cache, but करो not change
 * the file itself.
 */
sमाप_प्रकार dso__data_ग_लिखो_cache_addr(काष्ठा dso *dso, काष्ठा map *map,
				   काष्ठा machine *machine, u64 addr,
				   स्थिर u8 *data, sमाप_प्रकार size)
अणु
	u64 offset = map->map_ip(map, addr);
	वापस dso__data_ग_लिखो_cache_offs(dso, machine, offset, data, size);
पूर्ण

काष्ठा map *dso__new_map(स्थिर अक्षर *name)
अणु
	काष्ठा map *map = शून्य;
	काष्ठा dso *dso = dso__new(name);

	अगर (dso)
		map = map__new2(0, dso);

	वापस map;
पूर्ण

काष्ठा dso *machine__findnew_kernel(काष्ठा machine *machine, स्थिर अक्षर *name,
				    स्थिर अक्षर *लघु_name, पूर्णांक dso_type)
अणु
	/*
	 * The kernel dso could be created by build_id processing.
	 */
	काष्ठा dso *dso = machine__findnew_dso(machine, name);

	/*
	 * We need to run this in all हालs, since during the build_id
	 * processing we had no idea this was the kernel dso.
	 */
	अगर (dso != शून्य) अणु
		dso__set_लघु_name(dso, लघु_name, false);
		dso->kernel = dso_type;
	पूर्ण

	वापस dso;
पूर्ण

अटल व्योम dso__set_दीर्घ_name_id(काष्ठा dso *dso, स्थिर अक्षर *name, काष्ठा dso_id *id, bool name_allocated)
अणु
	काष्ठा rb_root *root = dso->root;

	अगर (name == शून्य)
		वापस;

	अगर (dso->दीर्घ_name_allocated)
		मुक्त((अक्षर *)dso->दीर्घ_name);

	अगर (root) अणु
		rb_erase(&dso->rb_node, root);
		/*
		 * __dsos__findnew_link_by_दीर्घname_id() isn't guaranteed to
		 * add it back, so a clean removal is required here.
		 */
		RB_CLEAR_NODE(&dso->rb_node);
		dso->root = शून्य;
	पूर्ण

	dso->दीर्घ_name		 = name;
	dso->दीर्घ_name_len	 = म_माप(name);
	dso->दीर्घ_name_allocated = name_allocated;

	अगर (root)
		__dsos__findnew_link_by_दीर्घname_id(root, dso, शून्य, id);
पूर्ण

व्योम dso__set_दीर्घ_name(काष्ठा dso *dso, स्थिर अक्षर *name, bool name_allocated)
अणु
	dso__set_दीर्घ_name_id(dso, name, शून्य, name_allocated);
पूर्ण

व्योम dso__set_लघु_name(काष्ठा dso *dso, स्थिर अक्षर *name, bool name_allocated)
अणु
	अगर (name == शून्य)
		वापस;

	अगर (dso->लघु_name_allocated)
		मुक्त((अक्षर *)dso->लघु_name);

	dso->लघु_name		  = name;
	dso->लघु_name_len	  = म_माप(name);
	dso->लघु_name_allocated = name_allocated;
पूर्ण

पूर्णांक dso__name_len(स्थिर काष्ठा dso *dso)
अणु
	अगर (!dso)
		वापस म_माप("[unknown]");
	अगर (verbose > 0)
		वापस dso->दीर्घ_name_len;

	वापस dso->लघु_name_len;
पूर्ण

bool dso__loaded(स्थिर काष्ठा dso *dso)
अणु
	वापस dso->loaded;
पूर्ण

bool dso__sorted_by_name(स्थिर काष्ठा dso *dso)
अणु
	वापस dso->sorted_by_name;
पूर्ण

व्योम dso__set_sorted_by_name(काष्ठा dso *dso)
अणु
	dso->sorted_by_name = true;
पूर्ण

काष्ठा dso *dso__new_id(स्थिर अक्षर *name, काष्ठा dso_id *id)
अणु
	काष्ठा dso *dso = सुस्मृति(1, माप(*dso) + म_माप(name) + 1);

	अगर (dso != शून्य) अणु
		म_नकल(dso->name, name);
		अगर (id)
			dso->id = *id;
		dso__set_दीर्घ_name_id(dso, dso->name, id, false);
		dso__set_लघु_name(dso, dso->name, false);
		dso->symbols = dso->symbol_names = RB_ROOT_CACHED;
		dso->data.cache = RB_ROOT;
		dso->अंतरभूतd_nodes = RB_ROOT_CACHED;
		dso->srclines = RB_ROOT_CACHED;
		dso->data.fd = -1;
		dso->data.status = DSO_DATA_STATUS_UNKNOWN;
		dso->symtab_type = DSO_BINARY_TYPE__NOT_FOUND;
		dso->binary_type = DSO_BINARY_TYPE__NOT_FOUND;
		dso->is_64_bit = (माप(व्योम *) == 8);
		dso->loaded = 0;
		dso->rel = 0;
		dso->sorted_by_name = 0;
		dso->has_build_id = 0;
		dso->has_srcline = 1;
		dso->a2l_fails = 1;
		dso->kernel = DSO_SPACE__USER;
		dso->needs_swap = DSO_SWAP__UNSET;
		dso->comp = COMP_ID__NONE;
		RB_CLEAR_NODE(&dso->rb_node);
		dso->root = शून्य;
		INIT_LIST_HEAD(&dso->node);
		INIT_LIST_HEAD(&dso->data.खोलो_entry);
		pthपढ़ो_mutex_init(&dso->lock, शून्य);
		refcount_set(&dso->refcnt, 1);
	पूर्ण

	वापस dso;
पूर्ण

काष्ठा dso *dso__new(स्थिर अक्षर *name)
अणु
	वापस dso__new_id(name, शून्य);
पूर्ण

व्योम dso__delete(काष्ठा dso *dso)
अणु
	अगर (!RB_EMPTY_NODE(&dso->rb_node))
		pr_err("DSO %s is still in rbtree when being deleted!\n",
		       dso->दीर्घ_name);

	/* मुक्त अंतरभूतs first, as they reference symbols */
	अंतरभूतs__tree_delete(&dso->अंतरभूतd_nodes);
	srcline__tree_delete(&dso->srclines);
	symbols__delete(&dso->symbols);

	अगर (dso->लघु_name_allocated) अणु
		zमुक्त((अक्षर **)&dso->लघु_name);
		dso->लघु_name_allocated = false;
	पूर्ण

	अगर (dso->दीर्घ_name_allocated) अणु
		zमुक्त((अक्षर **)&dso->दीर्घ_name);
		dso->दीर्घ_name_allocated = false;
	पूर्ण

	dso__data_बंद(dso);
	auxtrace_cache__मुक्त(dso->auxtrace_cache);
	dso_cache__मुक्त(dso);
	dso__मुक्त_a2l(dso);
	zमुक्त(&dso->symsrc_filename);
	nsinfo__zput(dso->nsinfo);
	pthपढ़ो_mutex_destroy(&dso->lock);
	मुक्त(dso);
पूर्ण

काष्ठा dso *dso__get(काष्ठा dso *dso)
अणु
	अगर (dso)
		refcount_inc(&dso->refcnt);
	वापस dso;
पूर्ण

व्योम dso__put(काष्ठा dso *dso)
अणु
	अगर (dso && refcount_dec_and_test(&dso->refcnt))
		dso__delete(dso);
पूर्ण

व्योम dso__set_build_id(काष्ठा dso *dso, काष्ठा build_id *bid)
अणु
	dso->bid = *bid;
	dso->has_build_id = 1;
पूर्ण

bool dso__build_id_equal(स्थिर काष्ठा dso *dso, काष्ठा build_id *bid)
अणु
	वापस dso->bid.size == bid->size &&
	       स_भेद(dso->bid.data, bid->data, dso->bid.size) == 0;
पूर्ण

व्योम dso__पढ़ो_running_kernel_build_id(काष्ठा dso *dso, काष्ठा machine *machine)
अणु
	अक्षर path[PATH_MAX];

	अगर (machine__is_शेष_guest(machine))
		वापस;
	प्र_लिखो(path, "%s/sys/kernel/notes", machine->root_dir);
	अगर (sysfs__पढ़ो_build_id(path, &dso->bid) == 0)
		dso->has_build_id = true;
पूर्ण

पूर्णांक dso__kernel_module_get_build_id(काष्ठा dso *dso,
				    स्थिर अक्षर *root_dir)
अणु
	अक्षर filename[PATH_MAX];
	/*
	 * kernel module लघु names are of the क्रमm "[module]" and
	 * we need just "module" here.
	 */
	स्थिर अक्षर *name = dso->लघु_name + 1;

	snम_लिखो(filename, माप(filename),
		 "%s/sys/module/%.*s/notes/.note.gnu.build-id",
		 root_dir, (पूर्णांक)म_माप(name) - 1, name);

	अगर (sysfs__पढ़ो_build_id(filename, &dso->bid) == 0)
		dso->has_build_id = true;

	वापस 0;
पूर्ण

अटल माप_प्रकार dso__ख_लिखो_buildid(काष्ठा dso *dso, खाता *fp)
अणु
	अक्षर sbuild_id[SBUILD_ID_SIZE];

	build_id__प्र_लिखो(&dso->bid, sbuild_id);
	वापस ख_लिखो(fp, "%s", sbuild_id);
पूर्ण

माप_प्रकार dso__ख_लिखो(काष्ठा dso *dso, खाता *fp)
अणु
	काष्ठा rb_node *nd;
	माप_प्रकार ret = ख_लिखो(fp, "dso: %s (", dso->लघु_name);

	अगर (dso->लघु_name != dso->दीर्घ_name)
		ret += ख_लिखो(fp, "%s, ", dso->दीर्घ_name);
	ret += ख_लिखो(fp, "%sloaded, ", dso__loaded(dso) ? "" : "NOT ");
	ret += dso__ख_लिखो_buildid(dso, fp);
	ret += ख_लिखो(fp, ")\n");
	क्रम (nd = rb_first_cached(&dso->symbols); nd; nd = rb_next(nd)) अणु
		काष्ठा symbol *pos = rb_entry(nd, काष्ठा symbol, rb_node);
		ret += symbol__ख_लिखो(pos, fp);
	पूर्ण

	वापस ret;
पूर्ण

क्रमागत dso_type dso__type(काष्ठा dso *dso, काष्ठा machine *machine)
अणु
	पूर्णांक fd;
	क्रमागत dso_type type = DSO__TYPE_UNKNOWN;

	fd = dso__data_get_fd(dso, machine);
	अगर (fd >= 0) अणु
		type = dso__type_fd(fd);
		dso__data_put_fd(dso);
	पूर्ण

	वापस type;
पूर्ण

पूर्णांक dso__म_त्रुटि_load(काष्ठा dso *dso, अक्षर *buf, माप_प्रकार buflen)
अणु
	पूर्णांक idx, errnum = dso->load_त्रुटि_सं;
	/*
	 * This must have a same ordering as the क्रमागत dso_load_त्रुटि_सं.
	 */
	अटल स्थिर अक्षर *dso_load__error_str[] = अणु
	"Internal tools/perf/ library error",
	"Invalid ELF file",
	"Can not read build id",
	"Mismatching build id",
	"Decompression failure",
	पूर्ण;

	BUG_ON(buflen == 0);

	अगर (errnum >= 0) अणु
		स्थिर अक्षर *err = str_error_r(errnum, buf, buflen);

		अगर (err != buf)
			scnम_लिखो(buf, buflen, "%s", err);

		वापस 0;
	पूर्ण

	अगर (errnum <  __DSO_LOAD_ERRNO__START || errnum >= __DSO_LOAD_ERRNO__END)
		वापस -1;

	idx = errnum - __DSO_LOAD_ERRNO__START;
	scnम_लिखो(buf, buflen, "%s", dso_load__error_str[idx]);
	वापस 0;
पूर्ण
