<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "builtin.h"
#समावेश "perf.h"
#समावेश "color.h"
#समावेश <tools/config.h>
#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <subcmd/parse-options.h>

पूर्णांक version_verbose;

काष्ठा version अणु
	bool	build_options;
पूर्ण;

अटल काष्ठा version version;

अटल काष्ठा option version_options[] = अणु
	OPT_BOOLEAN(0, "build-options", &version.build_options,
		    "display the build options"),
	OPT_END(),
पूर्ण;

अटल स्थिर अक्षर * स्थिर version_usage[] = अणु
	"perf version [<options>]",
	शून्य
पूर्ण;

अटल व्योम on_off_prपूर्णांक(स्थिर अक्षर *status)
अणु
	म_लिखो("[ ");

	अगर (!म_भेद(status, "OFF"))
		color_ख_लिखो(मानक_निकास, PERF_COLOR_RED, "%-3s", status);
	अन्यथा
		color_ख_लिखो(मानक_निकास, PERF_COLOR_GREEN, "%-3s", status);

	म_लिखो(" ]");
पूर्ण

अटल व्योम status_prपूर्णांक(स्थिर अक्षर *name, स्थिर अक्षर *macro,
			 स्थिर अक्षर *status)
अणु
	म_लिखो("%22s: ", name);
	on_off_prपूर्णांक(status);
	म_लिखो("  # %s\n", macro);
पूर्ण

#घोषणा STATUS(__d, __m)				\
करो अणु							\
	अगर (IS_BUILTIN(__d))				\
		status_prपूर्णांक(#__m, #__d, "on");		\
	अन्यथा						\
		status_prपूर्णांक(#__m, #__d, "OFF");	\
पूर्ण जबतक (0)

अटल व्योम library_status(व्योम)
अणु
	STATUS(HAVE_DWARF_SUPPORT, dwarf);
	STATUS(HAVE_DWARF_GETLOCATIONS_SUPPORT, dwarf_getlocations);
	STATUS(HAVE_GLIBC_SUPPORT, glibc);
#अगर_अघोषित HAVE_SYSCALL_TABLE_SUPPORT
	STATUS(HAVE_LIBAUDIT_SUPPORT, libaudit);
#पूर्ण_अगर
	STATUS(HAVE_SYSCALL_TABLE_SUPPORT, syscall_table);
	STATUS(HAVE_LIBBFD_SUPPORT, libbfd);
	STATUS(HAVE_LIBELF_SUPPORT, libelf);
	STATUS(HAVE_LIBNUMA_SUPPORT, libnuma);
	STATUS(HAVE_LIBNUMA_SUPPORT, numa_num_possible_cpus);
	STATUS(HAVE_LIBPERL_SUPPORT, libperl);
	STATUS(HAVE_LIBPYTHON_SUPPORT, libpython);
	STATUS(HAVE_SLANG_SUPPORT, libslang);
	STATUS(HAVE_LIBCRYPTO_SUPPORT, libcrypto);
	STATUS(HAVE_LIBUNWIND_SUPPORT, libunwind);
	STATUS(HAVE_DWARF_SUPPORT, libdw-dwarf-unwind);
	STATUS(HAVE_ZLIB_SUPPORT, zlib);
	STATUS(HAVE_LZMA_SUPPORT, lzma);
	STATUS(HAVE_AUXTRACE_SUPPORT, get_cpuid);
	STATUS(HAVE_LIBBPF_SUPPORT, bpf);
	STATUS(HAVE_AIO_SUPPORT, aio);
	STATUS(HAVE_ZSTD_SUPPORT, zstd);
	STATUS(HAVE_LIBPFM, libpfm4);
पूर्ण

पूर्णांक cmd_version(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	argc = parse_options(argc, argv, version_options, version_usage,
			     PARSE_OPT_STOP_AT_NON_OPTION);

	म_लिखो("perf version %s\n", perf_version_string);

	अगर (version.build_options || version_verbose == 1)
		library_status();

	वापस 0;
पूर्ण
