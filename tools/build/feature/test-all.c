<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * test-all.c: Try to build all the मुख्य testहालs at once.
 *
 * A well-configured प्रणाली will have all the prereqs installed, so we can speed
 * up स्वतः-detection on such प्रणालीs.
 */

/*
 * Quirk: Python and Perl headers cannot be in arbitrary places, so keep
 * these 3 testहालs at the top:
 */
#घोषणा मुख्य मुख्य_test_libpython
# include "test-libpython.c"
#अघोषित मुख्य

#घोषणा मुख्य मुख्य_test_libpython_version
# include "test-libpython-version.c"
#अघोषित मुख्य

#घोषणा मुख्य मुख्य_test_libperl
# include "test-libperl.c"
#अघोषित मुख्य

#घोषणा मुख्य मुख्य_test_hello
# include "test-hello.c"
#अघोषित मुख्य

#घोषणा मुख्य मुख्य_test_libelf
# include "test-libelf.c"
#अघोषित मुख्य

#घोषणा मुख्य मुख्य_test_get_current_dir_name
# include "test-get_current_dir_name.c"
#अघोषित मुख्य

#घोषणा मुख्य मुख्य_test_gettid
# include "test-gettid.c"
#अघोषित मुख्य

#घोषणा मुख्य मुख्य_test_glibc
# include "test-glibc.c"
#अघोषित मुख्य

#घोषणा मुख्य मुख्य_test_dwarf
# include "test-dwarf.c"
#अघोषित मुख्य

#घोषणा मुख्य मुख्य_test_dwarf_getlocations
# include "test-dwarf_getlocations.c"
#अघोषित मुख्य

#घोषणा मुख्य मुख्य_test_eventfd
# include "test-eventfd.c"
#अघोषित मुख्य

#घोषणा मुख्य मुख्य_test_libelf_getphdrnum
# include "test-libelf-getphdrnum.c"
#अघोषित मुख्य

#घोषणा मुख्य मुख्य_test_libelf_gelf_getnote
# include "test-libelf-gelf_getnote.c"
#अघोषित मुख्य

#घोषणा मुख्य मुख्य_test_libelf_माला_लोhdrstrndx
# include "test-libelf-getshdrstrndx.c"
#अघोषित मुख्य

#घोषणा मुख्य मुख्य_test_libunwind
# include "test-libunwind.c"
#अघोषित मुख्य

#घोषणा मुख्य मुख्य_test_libslang
# include "test-libslang.c"
#अघोषित मुख्य

#घोषणा मुख्य मुख्य_test_libbfd
# include "test-libbfd.c"
#अघोषित मुख्य

#घोषणा मुख्य मुख्य_test_libbfd_buildid
# include "test-libbfd-buildid.c"
#अघोषित मुख्य

#घोषणा मुख्य मुख्य_test_backtrace
# include "test-backtrace.c"
#अघोषित मुख्य

#घोषणा मुख्य मुख्य_test_libnuma
# include "test-libnuma.c"
#अघोषित मुख्य

#घोषणा मुख्य मुख्य_test_numa_num_possible_cpus
# include "test-numa_num_possible_cpus.c"
#अघोषित मुख्य

#घोषणा मुख्य मुख्य_test_समयrfd
# include "test-timerfd.c"
#अघोषित मुख्य

#घोषणा मुख्य मुख्य_test_stackprotector_all
# include "test-stackprotector-all.c"
#अघोषित मुख्य

#घोषणा मुख्य मुख्य_test_libdw_dwarf_unwind
# include "test-libdw-dwarf-unwind.c"
#अघोषित मुख्य

#घोषणा मुख्य मुख्य_test_sync_compare_and_swap
# include "test-sync-compare-and-swap.c"
#अघोषित मुख्य

#घोषणा मुख्य मुख्य_test_zlib
# include "test-zlib.c"
#अघोषित मुख्य

#घोषणा मुख्य मुख्य_test_pthपढ़ो_attr_setaffinity_np
# include "test-pthread-attr-setaffinity-np.c"
#अघोषित मुख्य

#घोषणा मुख्य मुख्य_test_pthपढ़ो_barrier
# include "test-pthread-barrier.c"
#अघोषित मुख्य

#घोषणा मुख्य मुख्य_test_sched_अ_लोpu
# include "test-sched_getcpu.c"
#अघोषित मुख्य

# अगर 0
/*
 * Disable libbabeltrace check क्रम test-all, because the requested
 * library version is not released yet in most distributions. Will
 * reenable later.
 */

#घोषणा मुख्य मुख्य_test_libbabeltrace
# include "test-libbabeltrace.c"
#अघोषित मुख्य
#पूर्ण_अगर

#घोषणा मुख्य मुख्य_test_lzma
# include "test-lzma.c"
#अघोषित मुख्य

#घोषणा मुख्य मुख्य_test_get_cpuid
# include "test-get_cpuid.c"
#अघोषित मुख्य

#घोषणा मुख्य मुख्य_test_bpf
# include "test-bpf.c"
#अघोषित मुख्य

#घोषणा मुख्य मुख्य_test_libcrypto
# include "test-libcrypto.c"
#अघोषित मुख्य

#घोषणा मुख्य मुख्य_test_sdt
# include "test-sdt.c"
#अघोषित मुख्य

#घोषणा मुख्य मुख्य_test_setns
# include "test-setns.c"
#अघोषित मुख्य

#घोषणा मुख्य मुख्य_test_libaio
# include "test-libaio.c"
#अघोषित मुख्य

#घोषणा मुख्य मुख्य_test_पुनः_स्मृतिarray
# include "test-reallocarray.c"
#अघोषित मुख्य

#घोषणा मुख्य मुख्य_test_disassembler_four_args
# include "test-disassembler-four-args.c"
#अघोषित मुख्य

#घोषणा मुख्य मुख्य_test_libzstd
# include "test-libzstd.c"
#अघोषित मुख्य

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	मुख्य_test_libpython();
	मुख्य_test_libpython_version();
	मुख्य_test_libperl();
	मुख्य_test_hello();
	मुख्य_test_libelf();
	मुख्य_test_get_current_dir_name();
	मुख्य_test_gettid();
	मुख्य_test_glibc();
	मुख्य_test_dwarf();
	मुख्य_test_dwarf_getlocations();
	मुख्य_test_eventfd();
	मुख्य_test_libelf_getphdrnum();
	मुख्य_test_libelf_gelf_getnote();
	मुख्य_test_libelf_माला_लोhdrstrndx();
	मुख्य_test_libunwind();
	मुख्य_test_libslang();
	मुख्य_test_libbfd();
	मुख्य_test_libbfd_buildid();
	मुख्य_test_backtrace();
	मुख्य_test_libnuma();
	मुख्य_test_numa_num_possible_cpus();
	मुख्य_test_समयrfd();
	मुख्य_test_stackprotector_all();
	मुख्य_test_libdw_dwarf_unwind();
	मुख्य_test_sync_compare_and_swap(argc, argv);
	मुख्य_test_zlib();
	मुख्य_test_pthपढ़ो_attr_setaffinity_np();
	मुख्य_test_pthपढ़ो_barrier();
	मुख्य_test_lzma();
	मुख्य_test_get_cpuid();
	मुख्य_test_bpf();
	मुख्य_test_libcrypto();
	मुख्य_test_sched_अ_लोpu();
	मुख्य_test_sdt();
	मुख्य_test_setns();
	मुख्य_test_libaio();
	मुख्य_test_पुनः_स्मृतिarray();
	मुख्य_test_disassembler_four_args();
	मुख्य_test_libzstd();

	वापस 0;
पूर्ण
