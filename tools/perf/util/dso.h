<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PERF_DSO
#घोषणा __PERF_DSO

#समावेश <pthपढ़ो.h>
#समावेश <linux/refcount.h>
#समावेश <linux/types.h>
#समावेश <linux/rbtree.h>
#समावेश <sys/types.h>
#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <linux/bitops.h>
#समावेश "build-id.h"

काष्ठा machine;
काष्ठा map;
काष्ठा perf_env;

#घोषणा DSO__NAME_KALLSYMS	"[kernel.kallsyms]"
#घोषणा DSO__NAME_KCORE		"[kernel.kcore]"

क्रमागत dso_binary_type अणु
	DSO_BINARY_TYPE__KALLSYMS = 0,
	DSO_BINARY_TYPE__GUEST_KALLSYMS,
	DSO_BINARY_TYPE__VMLINUX,
	DSO_BINARY_TYPE__GUEST_VMLINUX,
	DSO_BINARY_TYPE__JAVA_JIT,
	DSO_BINARY_TYPE__DEBUGLINK,
	DSO_BINARY_TYPE__BUILD_ID_CACHE,
	DSO_BINARY_TYPE__BUILD_ID_CACHE_DEBUGINFO,
	DSO_BINARY_TYPE__FEDORA_DEBUGINFO,
	DSO_BINARY_TYPE__UBUNTU_DEBUGINFO,
	DSO_BINARY_TYPE__MIXEDUP_UBUNTU_DEBUGINFO,
	DSO_BINARY_TYPE__BUILDID_DEBUGINFO,
	DSO_BINARY_TYPE__SYSTEM_PATH_DSO,
	DSO_BINARY_TYPE__GUEST_KMODULE,
	DSO_BINARY_TYPE__GUEST_KMODULE_COMP,
	DSO_BINARY_TYPE__SYSTEM_PATH_KMODULE,
	DSO_BINARY_TYPE__SYSTEM_PATH_KMODULE_COMP,
	DSO_BINARY_TYPE__KCORE,
	DSO_BINARY_TYPE__GUEST_KCORE,
	DSO_BINARY_TYPE__OPENEMBEDDED_DEBUGINFO,
	DSO_BINARY_TYPE__BPF_PROG_INFO,
	DSO_BINARY_TYPE__BPF_IMAGE,
	DSO_BINARY_TYPE__OOL,
	DSO_BINARY_TYPE__NOT_FOUND,
पूर्ण;

क्रमागत dso_space_type अणु
	DSO_SPACE__USER = 0,
	DSO_SPACE__KERNEL,
	DSO_SPACE__KERNEL_GUEST
पूर्ण;

क्रमागत dso_swap_type अणु
	DSO_SWAP__UNSET,
	DSO_SWAP__NO,
	DSO_SWAP__YES,
पूर्ण;

क्रमागत dso_data_status अणु
	DSO_DATA_STATUS_ERROR	= -1,
	DSO_DATA_STATUS_UNKNOWN	= 0,
	DSO_DATA_STATUS_OK	= 1,
पूर्ण;

क्रमागत dso_data_status_seen अणु
	DSO_DATA_STATUS_SEEN_ITRACE,
पूर्ण;

क्रमागत dso_type अणु
	DSO__TYPE_UNKNOWN,
	DSO__TYPE_64BIT,
	DSO__TYPE_32BIT,
	DSO__TYPE_X32BIT,
पूर्ण;

क्रमागत dso_load_त्रुटि_सं अणु
	DSO_LOAD_ERRNO__SUCCESS		= 0,

	/*
	 * Choose an arbitrary negative big number not to clash with standard
	 * त्रुटि_सं since SUS requires the त्रुटि_सं has distinct positive values.
	 * See 'Issue 6' in the link below.
	 *
	 * http://pubs.खोलोgroup.org/onlinepubs/9699919799/basedefs/त्रुटिसं.स.hपंचांगl
	 */
	__DSO_LOAD_ERRNO__START		= -10000,

	DSO_LOAD_ERRNO__INTERNAL_ERROR	= __DSO_LOAD_ERRNO__START,

	/* क्रम symsrc__init() */
	DSO_LOAD_ERRNO__INVALID_ELF,
	DSO_LOAD_ERRNO__CANNOT_READ_BUILDID,
	DSO_LOAD_ERRNO__MISMATCHING_BUILDID,

	/* क्रम decompress_kmodule */
	DSO_LOAD_ERRNO__DECOMPRESSION_FAILURE,

	__DSO_LOAD_ERRNO__END,
पूर्ण;

#घोषणा DSO__SWAP(dso, type, val)			\
(अणु							\
	type ____r = val;				\
	BUG_ON(dso->needs_swap == DSO_SWAP__UNSET);	\
	अगर (dso->needs_swap == DSO_SWAP__YES) अणु		\
		चयन (माप(____r)) अणु		\
		हाल 2:					\
			____r = bswap_16(val);		\
			अवरोध;				\
		हाल 4:					\
			____r = bswap_32(val);		\
			अवरोध;				\
		हाल 8:					\
			____r = bswap_64(val);		\
			अवरोध;				\
		शेष:				\
			BUG_ON(1);			\
		पूर्ण					\
	पूर्ण						\
	____r;						\
पूर्ण)

#घोषणा DSO__DATA_CACHE_SIZE 4096
#घोषणा DSO__DATA_CACHE_MASK ~(DSO__DATA_CACHE_SIZE - 1)

/*
 * Data about backing storage DSO, comes from PERF_RECORD_MMAP2 meta events
 */
काष्ठा dso_id अणु
	u32	maj;
	u32	min;
	u64	ino;
	u64	ino_generation;
पूर्ण;

काष्ठा dso_cache अणु
	काष्ठा rb_node	rb_node;
	u64 offset;
	u64 size;
	अक्षर data[];
पूर्ण;

काष्ठा auxtrace_cache;

काष्ठा dso अणु
	pthपढ़ो_mutex_t	 lock;
	काष्ठा list_head node;
	काष्ठा rb_node	 rb_node;	/* rbtree node sorted by दीर्घ name */
	काष्ठा rb_root	 *root;		/* root of rbtree that rb_node is in */
	काष्ठा rb_root_cached symbols;
	काष्ठा rb_root_cached symbol_names;
	काष्ठा rb_root_cached अंतरभूतd_nodes;
	काष्ठा rb_root_cached srclines;
	काष्ठा अणु
		u64		addr;
		काष्ठा symbol	*symbol;
	पूर्ण last_find_result;
	व्योम		 *a2l;
	अक्षर		 *symsrc_filename;
	अचिन्हित पूर्णांक	 a2l_fails;
	क्रमागत dso_space_type	kernel;
	क्रमागत dso_swap_type	needs_swap;
	क्रमागत dso_binary_type	symtab_type;
	क्रमागत dso_binary_type	binary_type;
	क्रमागत dso_load_त्रुटि_सं	load_त्रुटि_सं;
	u8		 adjust_symbols:1;
	u8		 has_build_id:1;
	u8		 has_srcline:1;
	u8		 hit:1;
	u8		 annotate_warned:1;
	u8		 लघु_name_allocated:1;
	u8		 दीर्घ_name_allocated:1;
	u8		 is_64_bit:1;
	bool		 sorted_by_name;
	bool		 loaded;
	u8		 rel;
	काष्ठा build_id	 bid;
	u64		 text_offset;
	स्थिर अक्षर	 *लघु_name;
	स्थिर अक्षर	 *दीर्घ_name;
	u16		 दीर्घ_name_len;
	u16		 लघु_name_len;
	व्योम		*dwfl;			/* DWARF debug info */
	काष्ठा auxtrace_cache *auxtrace_cache;
	पूर्णांक		 comp;

	/* dso data file */
	काष्ठा अणु
		काष्ठा rb_root	 cache;
		पूर्णांक		 fd;
		पूर्णांक		 status;
		u32		 status_seen;
		माप_प्रकार		 file_size;
		काष्ठा list_head खोलो_entry;
		u64		 debug_frame_offset;
		u64		 eh_frame_hdr_offset;
	पूर्ण data;
	/* bpf prog inक्रमmation */
	काष्ठा अणु
		u32		id;
		u32		sub_id;
		काष्ठा perf_env	*env;
	पूर्ण bpf_prog;

	जोड़ अणु /* Tool specअगरic area */
		व्योम	 *priv;
		u64	 db_id;
	पूर्ण;
	काष्ठा nsinfo	*nsinfo;
	काष्ठा dso_id	 id;
	refcount_t	 refcnt;
	अक्षर		 name[];
पूर्ण;

/* dso__क्रम_each_symbol - iterate over the symbols of given type
 *
 * @dso: the 'struct dso *' in which symbols are iterated
 * @pos: the 'struct symbol *' to use as a loop cursor
 * @n: the 'struct rb_node *' to use as a temporary storage
 */
#घोषणा dso__क्रम_each_symbol(dso, pos, n)	\
	symbols__क्रम_each_entry(&(dso)->symbols, pos, n)

अटल अंतरभूत व्योम dso__set_loaded(काष्ठा dso *dso)
अणु
	dso->loaded = true;
पूर्ण

काष्ठा dso *dso__new_id(स्थिर अक्षर *name, काष्ठा dso_id *id);
काष्ठा dso *dso__new(स्थिर अक्षर *name);
व्योम dso__delete(काष्ठा dso *dso);

पूर्णांक dso__cmp_id(काष्ठा dso *a, काष्ठा dso *b);
व्योम dso__set_लघु_name(काष्ठा dso *dso, स्थिर अक्षर *name, bool name_allocated);
व्योम dso__set_दीर्घ_name(काष्ठा dso *dso, स्थिर अक्षर *name, bool name_allocated);

पूर्णांक dso__name_len(स्थिर काष्ठा dso *dso);

काष्ठा dso *dso__get(काष्ठा dso *dso);
व्योम dso__put(काष्ठा dso *dso);

अटल अंतरभूत व्योम __dso__zput(काष्ठा dso **dso)
अणु
	dso__put(*dso);
	*dso = शून्य;
पूर्ण

#घोषणा dso__zput(dso) __dso__zput(&dso)

bool dso__loaded(स्थिर काष्ठा dso *dso);

अटल अंतरभूत bool dso__has_symbols(स्थिर काष्ठा dso *dso)
अणु
	वापस !RB_EMPTY_ROOT(&dso->symbols.rb_root);
पूर्ण

bool dso__sorted_by_name(स्थिर काष्ठा dso *dso);
व्योम dso__set_sorted_by_name(काष्ठा dso *dso);
व्योम dso__sort_by_name(काष्ठा dso *dso);

व्योम dso__set_build_id(काष्ठा dso *dso, काष्ठा build_id *bid);
bool dso__build_id_equal(स्थिर काष्ठा dso *dso, काष्ठा build_id *bid);
व्योम dso__पढ़ो_running_kernel_build_id(काष्ठा dso *dso,
				       काष्ठा machine *machine);
पूर्णांक dso__kernel_module_get_build_id(काष्ठा dso *dso, स्थिर अक्षर *root_dir);

अक्षर dso__symtab_origin(स्थिर काष्ठा dso *dso);
पूर्णांक dso__पढ़ो_binary_type_filename(स्थिर काष्ठा dso *dso, क्रमागत dso_binary_type type,
				   अक्षर *root_dir, अक्षर *filename, माप_प्रकार size);
bool is_kernel_module(स्थिर अक्षर *pathname, पूर्णांक cpumode);
bool dso__needs_decompress(काष्ठा dso *dso);
पूर्णांक dso__decompress_kmodule_fd(काष्ठा dso *dso, स्थिर अक्षर *name);
पूर्णांक dso__decompress_kmodule_path(काष्ठा dso *dso, स्थिर अक्षर *name,
				 अक्षर *pathname, माप_प्रकार len);
पूर्णांक filename__decompress(स्थिर अक्षर *name, अक्षर *pathname,
			 माप_प्रकार len, पूर्णांक comp, पूर्णांक *err);

#घोषणा KMOD_DECOMP_NAME  "/tmp/perf-kmod-XXXXXX"
#घोषणा KMOD_DECOMP_LEN   माप(KMOD_DECOMP_NAME)

काष्ठा kmod_path अणु
	अक्षर *name;
	पूर्णांक   comp;
	bool  kmod;
पूर्ण;

पूर्णांक __kmod_path__parse(काष्ठा kmod_path *m, स्थिर अक्षर *path,
		     bool alloc_name);

#घोषणा kmod_path__parse(__m, __p)      __kmod_path__parse(__m, __p, false)
#घोषणा kmod_path__parse_name(__m, __p) __kmod_path__parse(__m, __p, true)

व्योम dso__set_module_info(काष्ठा dso *dso, काष्ठा kmod_path *m,
			  काष्ठा machine *machine);

/*
 * The dso__data_* बाह्यal पूर्णांकerface provides following functions:
 *   dso__data_get_fd
 *   dso__data_put_fd
 *   dso__data_बंद
 *   dso__data_size
 *   dso__data_पढ़ो_offset
 *   dso__data_पढ़ो_addr
 *   dso__data_ग_लिखो_cache_offs
 *   dso__data_ग_लिखो_cache_addr
 *
 * Please refer to the dso.c object code क्रम each function and
 * arguments करोcumentation. Following text tries to explain the
 * dso file descriptor caching.
 *
 * The dso__data* पूर्णांकerface allows caching of खोलोed file descriptors
 * to speed up the dso data accesses. The idea is to leave the file
 * descriptor खोलोed ideally क्रम the whole lअगरe of the dso object.
 *
 * The current usage of the dso__data_* पूर्णांकerface is as follows:
 *
 * Get DSO's fd:
 *   पूर्णांक fd = dso__data_get_fd(dso, machine);
 *   अगर (fd >= 0) अणु
 *       USE 'fd' SOMEHOW
 *       dso__data_put_fd(dso);
 *   पूर्ण
 *
 * Read DSO's data:
 *   n = dso__data_पढ़ो_offset(dso_0, &machine, 0, buf, बफ_मानE);
 *   n = dso__data_पढ़ो_addr(dso_0, &machine, 0, buf, बफ_मानE);
 *
 * Eventually बंद DSO's fd:
 *   dso__data_बंद(dso);
 *
 * It is not necessary to बंद the DSO object data file. Each समय new
 * DSO data file is खोलोed, the limit (RLIMIT_NOखाता/2) is checked. Once
 * it is crossed, the oldest खोलोed DSO object is बंदd.
 *
 * The dso__delete function calls बंद_dso function to ensure the
 * data file descriptor माला_लो बंदd/unmapped beक्रमe the dso object
 * is मुक्तd.
 *
 * TODO
*/
पूर्णांक dso__data_get_fd(काष्ठा dso *dso, काष्ठा machine *machine);
व्योम dso__data_put_fd(काष्ठा dso *dso);
व्योम dso__data_बंद(काष्ठा dso *dso);

पूर्णांक dso__data_file_size(काष्ठा dso *dso, काष्ठा machine *machine);
off_t dso__data_size(काष्ठा dso *dso, काष्ठा machine *machine);
sमाप_प्रकार dso__data_पढ़ो_offset(काष्ठा dso *dso, काष्ठा machine *machine,
			      u64 offset, u8 *data, sमाप_प्रकार size);
sमाप_प्रकार dso__data_पढ़ो_addr(काष्ठा dso *dso, काष्ठा map *map,
			    काष्ठा machine *machine, u64 addr,
			    u8 *data, sमाप_प्रकार size);
bool dso__data_status_seen(काष्ठा dso *dso, क्रमागत dso_data_status_seen by);
sमाप_प्रकार dso__data_ग_लिखो_cache_offs(काष्ठा dso *dso, काष्ठा machine *machine,
				   u64 offset, स्थिर u8 *data, sमाप_प्रकार size);
sमाप_प्रकार dso__data_ग_लिखो_cache_addr(काष्ठा dso *dso, काष्ठा map *map,
				   काष्ठा machine *machine, u64 addr,
				   स्थिर u8 *data, sमाप_प्रकार size);

काष्ठा map *dso__new_map(स्थिर अक्षर *name);
काष्ठा dso *machine__findnew_kernel(काष्ठा machine *machine, स्थिर अक्षर *name,
				    स्थिर अक्षर *लघु_name, पूर्णांक dso_type);

व्योम dso__reset_find_symbol_cache(काष्ठा dso *dso);

माप_प्रकार dso__ख_लिखो_symbols_by_name(काष्ठा dso *dso, खाता *fp);
माप_प्रकार dso__ख_लिखो(काष्ठा dso *dso, खाता *fp);

अटल अंतरभूत bool dso__is_vmlinux(काष्ठा dso *dso)
अणु
	वापस dso->binary_type == DSO_BINARY_TYPE__VMLINUX ||
	       dso->binary_type == DSO_BINARY_TYPE__GUEST_VMLINUX;
पूर्ण

अटल अंतरभूत bool dso__is_kcore(काष्ठा dso *dso)
अणु
	वापस dso->binary_type == DSO_BINARY_TYPE__KCORE ||
	       dso->binary_type == DSO_BINARY_TYPE__GUEST_KCORE;
पूर्ण

अटल अंतरभूत bool dso__is_kallsyms(काष्ठा dso *dso)
अणु
	वापस dso->kernel && dso->दीर्घ_name[0] != '/';
पूर्ण

व्योम dso__मुक्त_a2l(काष्ठा dso *dso);

क्रमागत dso_type dso__type(काष्ठा dso *dso, काष्ठा machine *machine);

पूर्णांक dso__म_त्रुटि_load(काष्ठा dso *dso, अक्षर *buf, माप_प्रकार buflen);

व्योम reset_fd_limit(व्योम);

#पूर्ण_अगर /* __PERF_DSO */
