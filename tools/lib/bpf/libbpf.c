<शैली गुरु>
// SPDX-License-Identअगरier: (LGPL-2.1 OR BSD-2-Clause)

/*
 * Common eBPF ELF object loading operations.
 *
 * Copyright (C) 2013-2015 Alexei Starovoitov <ast@kernel.org>
 * Copyright (C) 2015 Wang Nan <wangnan0@huawei.com>
 * Copyright (C) 2015 Huawei Inc.
 * Copyright (C) 2017 Nicira, Inc.
 * Copyright (C) 2019 Isovalent, Inc.
 */

#अगर_अघोषित _GNU_SOURCE
#घोषणा _GNU_SOURCE
#पूर्ण_अगर
#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश <मानकतर्क.स>
#समावेश <libgen.h>
#समावेश <पूर्णांकtypes.h>
#समावेश <सीमा.स>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <endian.h>
#समावेश <fcntl.h>
#समावेश <त्रुटिसं.स>
#समावेश <प्रकार.स>
#समावेश <यंत्र/unistd.h>
#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/bpf.h>
#समावेश <linux/btf.h>
#समावेश <linux/filter.h>
#समावेश <linux/list.h>
#समावेश <linux/सीमा.स>
#समावेश <linux/perf_event.h>
#समावेश <linux/ring_buffer.h>
#समावेश <linux/version.h>
#समावेश <sys/epoll.h>
#समावेश <sys/ioctl.h>
#समावेश <sys/mman.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/types.h>
#समावेश <sys/vfs.h>
#समावेश <sys/utsname.h>
#समावेश <sys/resource.h>
#समावेश <libelf.h>
#समावेश <gelf.h>
#समावेश <zlib.h>

#समावेश "libbpf.h"
#समावेश "bpf.h"
#समावेश "btf.h"
#समावेश "str_error.h"
#समावेश "libbpf_internal.h"
#समावेश "hashmap.h"

#अगर_अघोषित BPF_FS_MAGIC
#घोषणा BPF_FS_MAGIC		0xcafe4a11
#पूर्ण_अगर

#घोषणा BPF_INSN_SZ (माप(काष्ठा bpf_insn))

/* भम_लिखो() in __base_pr() uses nonliteral क्रमmat string. It may अवरोध
 * compilation अगर user enables corresponding warning. Disable it explicitly.
 */
#आशय GCC diagnostic ignored "-Wformat-nonliteral"

#घोषणा __म_लिखो(a, b)	__attribute__((क्रमmat(म_लिखो, a, b)))

अटल काष्ठा bpf_map *bpf_object__add_map(काष्ठा bpf_object *obj);
अटल bool prog_is_subprog(स्थिर काष्ठा bpf_object *obj, स्थिर काष्ठा bpf_program *prog);

अटल पूर्णांक __base_pr(क्रमागत libbpf_prपूर्णांक_level level, स्थिर अक्षर *क्रमmat,
		     बहु_सूची args)
अणु
	अगर (level == LIBBPF_DEBUG)
		वापस 0;

	वापस भख_लिखो(मानक_त्रुटि, क्रमmat, args);
पूर्ण

अटल libbpf_prपूर्णांक_fn_t __libbpf_pr = __base_pr;

libbpf_prपूर्णांक_fn_t libbpf_set_prपूर्णांक(libbpf_prपूर्णांक_fn_t fn)
अणु
	libbpf_prपूर्णांक_fn_t old_prपूर्णांक_fn = __libbpf_pr;

	__libbpf_pr = fn;
	वापस old_prपूर्णांक_fn;
पूर्ण

__म_लिखो(2, 3)
व्योम libbpf_prपूर्णांक(क्रमागत libbpf_prपूर्णांक_level level, स्थिर अक्षर *क्रमmat, ...)
अणु
	बहु_सूची args;

	अगर (!__libbpf_pr)
		वापस;

	बहु_शुरू(args, क्रमmat);
	__libbpf_pr(level, क्रमmat, args);
	बहु_पूर्ण(args);
पूर्ण

अटल व्योम pr_perm_msg(पूर्णांक err)
अणु
	काष्ठा rlimit limit;
	अक्षर buf[100];

	अगर (err != -EPERM || geteuid() != 0)
		वापस;

	err = getrlimit(RLIMIT_MEMLOCK, &limit);
	अगर (err)
		वापस;

	अगर (limit.rlim_cur == RLIM_अनन्त)
		वापस;

	अगर (limit.rlim_cur < 1024)
		snम_लिखो(buf, माप(buf), "%zu bytes", (माप_प्रकार)limit.rlim_cur);
	अन्यथा अगर (limit.rlim_cur < 1024*1024)
		snम_लिखो(buf, माप(buf), "%.1f KiB", (द्विगुन)limit.rlim_cur / 1024);
	अन्यथा
		snम_लिखो(buf, माप(buf), "%.1f MiB", (द्विगुन)limit.rlim_cur / (1024*1024));

	pr_warn("permission error while running as root; try raising 'ulimit -l'? current value: %s\n",
		buf);
पूर्ण

#घोषणा STRERR_बफ_मानE  128

/* Copied from tools/perf/util/util.h */
#अगर_अघोषित zमुक्त
# define zमुक्त(ptr) (अणु मुक्त(*ptr); *ptr = शून्य; पूर्ण)
#पूर्ण_अगर

#अगर_अघोषित zबंद
# define zबंद(fd) (अणु			\
	पूर्णांक ___err = 0;			\
	अगर ((fd) >= 0)			\
		___err = बंद((fd));	\
	fd = -1;			\
	___err; पूर्ण)
#पूर्ण_अगर

अटल अंतरभूत __u64 ptr_to_u64(स्थिर व्योम *ptr)
अणु
	वापस (__u64) (अचिन्हित दीर्घ) ptr;
पूर्ण

क्रमागत kern_feature_id अणु
	/* v4.14: kernel support क्रम program & map names. */
	FEAT_PROG_NAME,
	/* v5.2: kernel support क्रम global data sections. */
	FEAT_GLOBAL_DATA,
	/* BTF support */
	FEAT_BTF,
	/* BTF_KIND_FUNC and BTF_KIND_FUNC_PROTO support */
	FEAT_BTF_FUNC,
	/* BTF_KIND_VAR and BTF_KIND_DATASEC support */
	FEAT_BTF_DATASEC,
	/* BTF_FUNC_GLOBAL is supported */
	FEAT_BTF_GLOBAL_FUNC,
	/* BPF_F_MMAPABLE is supported क्रम arrays */
	FEAT_ARRAY_MMAP,
	/* kernel support क्रम expected_attach_type in BPF_PROG_LOAD */
	FEAT_EXP_ATTACH_TYPE,
	/* bpf_probe_पढ़ो_अणुkernel,userपूर्ण[_str] helpers */
	FEAT_PROBE_READ_KERN,
	/* BPF_PROG_BIND_MAP is supported */
	FEAT_PROG_BIND_MAP,
	/* Kernel support क्रम module BTFs */
	FEAT_MODULE_BTF,
	/* BTF_KIND_FLOAT support */
	FEAT_BTF_FLOAT,
	__FEAT_CNT,
पूर्ण;

अटल bool kernel_supports(क्रमागत kern_feature_id feat_id);

क्रमागत reloc_type अणु
	RELO_LD64,
	RELO_CALL,
	RELO_DATA,
	RELO_EXTERN_VAR,
	RELO_EXTERN_FUNC,
	RELO_SUBPROG_ADDR,
पूर्ण;

काष्ठा reloc_desc अणु
	क्रमागत reloc_type type;
	पूर्णांक insn_idx;
	पूर्णांक map_idx;
	पूर्णांक sym_off;
पूर्ण;

काष्ठा bpf_sec_def;

प्रकार काष्ठा bpf_link *(*attach_fn_t)(स्थिर काष्ठा bpf_sec_def *sec,
					काष्ठा bpf_program *prog);

काष्ठा bpf_sec_def अणु
	स्थिर अक्षर *sec;
	माप_प्रकार len;
	क्रमागत bpf_prog_type prog_type;
	क्रमागत bpf_attach_type expected_attach_type;
	bool is_exp_attach_type_optional;
	bool is_attachable;
	bool is_attach_btf;
	bool is_sleepable;
	attach_fn_t attach_fn;
पूर्ण;

/*
 * bpf_prog should be a better name but it has been used in
 * linux/filter.h.
 */
काष्ठा bpf_program अणु
	स्थिर काष्ठा bpf_sec_def *sec_def;
	अक्षर *sec_name;
	माप_प्रकार sec_idx;
	/* this program's inकाष्ठाion offset (in number of inकाष्ठाions)
	 * within its containing ELF section
	 */
	माप_प्रकार sec_insn_off;
	/* number of original inकाष्ठाions in ELF section beदीर्घing to this
	 * program, not taking पूर्णांकo account subprogram inकाष्ठाions possible
	 * appended later during relocation
	 */
	माप_प्रकार sec_insn_cnt;
	/* Offset (in number of inकाष्ठाions) of the start of inकाष्ठाion
	 * beदीर्घing to this BPF program  within its containing मुख्य BPF
	 * program. For the entry-poपूर्णांक (मुख्य) BPF program, this is always
	 * zero. For a sub-program, this माला_लो reset beक्रमe each of मुख्य BPF
	 * programs are processed and relocated and is used to determined
	 * whether sub-program was alपढ़ोy appended to the मुख्य program, and
	 * अगर yes, at which inकाष्ठाion offset.
	 */
	माप_प्रकार sub_insn_off;

	अक्षर *name;
	/* sec_name with / replaced by _; makes recursive pinning
	 * in bpf_object__pin_programs easier
	 */
	अक्षर *pin_name;

	/* inकाष्ठाions that beदीर्घ to BPF program; insns[0] is located at
	 * sec_insn_off inकाष्ठाion within its ELF section in ELF file, so
	 * when mapping ELF file inकाष्ठाion index to the local inकाष्ठाion,
	 * one needs to subtract sec_insn_off; and vice versa.
	 */
	काष्ठा bpf_insn *insns;
	/* actual number of inकाष्ठाion in this BPF program's image; क्रम
	 * entry-poपूर्णांक BPF programs this includes the size of मुख्य program
	 * itself plus all the used sub-programs, appended at the end
	 */
	माप_प्रकार insns_cnt;

	काष्ठा reloc_desc *reloc_desc;
	पूर्णांक nr_reloc;
	पूर्णांक log_level;

	काष्ठा अणु
		पूर्णांक nr;
		पूर्णांक *fds;
	पूर्ण instances;
	bpf_program_prep_t preprocessor;

	काष्ठा bpf_object *obj;
	व्योम *priv;
	bpf_program_clear_priv_t clear_priv;

	bool load;
	bool mark_btf_अटल;
	क्रमागत bpf_prog_type type;
	क्रमागत bpf_attach_type expected_attach_type;
	पूर्णांक prog_अगरindex;
	__u32 attach_btf_obj_fd;
	__u32 attach_btf_id;
	__u32 attach_prog_fd;
	व्योम *func_info;
	__u32 func_info_rec_size;
	__u32 func_info_cnt;

	व्योम *line_info;
	__u32 line_info_rec_size;
	__u32 line_info_cnt;
	__u32 prog_flags;
पूर्ण;

काष्ठा bpf_काष्ठा_ops अणु
	स्थिर अक्षर *tname;
	स्थिर काष्ठा btf_type *type;
	काष्ठा bpf_program **progs;
	__u32 *kern_func_off;
	/* e.g. काष्ठा tcp_congestion_ops in bpf_prog's btf क्रमmat */
	व्योम *data;
	/* e.g. काष्ठा bpf_काष्ठा_ops_tcp_congestion_ops in
	 *      btf_vmlinux's क्रमmat.
	 * काष्ठा bpf_काष्ठा_ops_tcp_congestion_ops अणु
	 *	[... some other kernel fields ...]
	 *	काष्ठा tcp_congestion_ops data;
	 * पूर्ण
	 * kern_vdata-size == माप(काष्ठा bpf_काष्ठा_ops_tcp_congestion_ops)
	 * bpf_map__init_kern_काष्ठा_ops() will populate the "kern_vdata"
	 * from "data".
	 */
	व्योम *kern_vdata;
	__u32 type_id;
पूर्ण;

#घोषणा DATA_SEC ".data"
#घोषणा BSS_SEC ".bss"
#घोषणा RODATA_SEC ".rodata"
#घोषणा KCONFIG_SEC ".kconfig"
#घोषणा KSYMS_SEC ".ksyms"
#घोषणा STRUCT_OPS_SEC ".struct_ops"

क्रमागत libbpf_map_type अणु
	LIBBPF_MAP_UNSPEC,
	LIBBPF_MAP_DATA,
	LIBBPF_MAP_BSS,
	LIBBPF_MAP_RODATA,
	LIBBPF_MAP_KCONFIG,
पूर्ण;

अटल स्थिर अक्षर * स्थिर libbpf_type_to_btf_name[] = अणु
	[LIBBPF_MAP_DATA]	= DATA_SEC,
	[LIBBPF_MAP_BSS]	= BSS_SEC,
	[LIBBPF_MAP_RODATA]	= RODATA_SEC,
	[LIBBPF_MAP_KCONFIG]	= KCONFIG_SEC,
पूर्ण;

काष्ठा bpf_map अणु
	अक्षर *name;
	पूर्णांक fd;
	पूर्णांक sec_idx;
	माप_प्रकार sec_offset;
	पूर्णांक map_अगरindex;
	पूर्णांक inner_map_fd;
	काष्ठा bpf_map_def def;
	__u32 numa_node;
	__u32 btf_var_idx;
	__u32 btf_key_type_id;
	__u32 btf_value_type_id;
	__u32 btf_vmlinux_value_type_id;
	व्योम *priv;
	bpf_map_clear_priv_t clear_priv;
	क्रमागत libbpf_map_type libbpf_type;
	व्योम *mmaped;
	काष्ठा bpf_काष्ठा_ops *st_ops;
	काष्ठा bpf_map *inner_map;
	व्योम **init_slots;
	पूर्णांक init_slots_sz;
	अक्षर *pin_path;
	bool pinned;
	bool reused;
पूर्ण;

क्रमागत बाह्य_type अणु
	EXT_UNKNOWN,
	EXT_KCFG,
	EXT_KSYM,
पूर्ण;

क्रमागत kcfg_type अणु
	KCFG_UNKNOWN,
	KCFG_CHAR,
	KCFG_BOOL,
	KCFG_INT,
	KCFG_TRISTATE,
	KCFG_CHAR_ARR,
पूर्ण;

काष्ठा बाह्य_desc अणु
	क्रमागत बाह्य_type type;
	पूर्णांक sym_idx;
	पूर्णांक btf_id;
	पूर्णांक sec_btf_id;
	स्थिर अक्षर *name;
	bool is_set;
	bool is_weak;
	जोड़ अणु
		काष्ठा अणु
			क्रमागत kcfg_type type;
			पूर्णांक sz;
			पूर्णांक align;
			पूर्णांक data_off;
			bool is_चिन्हित;
		पूर्ण kcfg;
		काष्ठा अणु
			अचिन्हित दीर्घ दीर्घ addr;

			/* target btf_id of the corresponding kernel var. */
			पूर्णांक kernel_btf_obj_fd;
			पूर्णांक kernel_btf_id;

			/* local btf_id of the ksym बाह्य's type. */
			__u32 type_id;
		पूर्ण ksym;
	पूर्ण;
पूर्ण;

अटल LIST_HEAD(bpf_objects_list);

काष्ठा module_btf अणु
	काष्ठा btf *btf;
	अक्षर *name;
	__u32 id;
	पूर्णांक fd;
पूर्ण;

काष्ठा bpf_object अणु
	अक्षर name[BPF_OBJ_NAME_LEN];
	अक्षर license[64];
	__u32 kern_version;

	काष्ठा bpf_program *programs;
	माप_प्रकार nr_programs;
	काष्ठा bpf_map *maps;
	माप_प्रकार nr_maps;
	माप_प्रकार maps_cap;

	अक्षर *kconfig;
	काष्ठा बाह्य_desc *बाह्यs;
	पूर्णांक nr_बाह्य;
	पूर्णांक kconfig_map_idx;
	पूर्णांक rodata_map_idx;

	bool loaded;
	bool has_subcalls;

	/*
	 * Inक्रमmation when करोing elf related work. Only valid अगर fd
	 * is valid.
	 */
	काष्ठा अणु
		पूर्णांक fd;
		स्थिर व्योम *obj_buf;
		माप_प्रकार obj_buf_sz;
		Elf *elf;
		GElf_Ehdr ehdr;
		Elf_Data *symbols;
		Elf_Data *data;
		Elf_Data *rodata;
		Elf_Data *bss;
		Elf_Data *st_ops_data;
		माप_प्रकार shstrndx; /* section index क्रम section name strings */
		माप_प्रकार strtabidx;
		काष्ठा अणु
			GElf_Shdr shdr;
			Elf_Data *data;
		पूर्ण *reloc_sects;
		पूर्णांक nr_reloc_sects;
		पूर्णांक maps_shndx;
		पूर्णांक btf_maps_shndx;
		__u32 btf_maps_sec_btf_id;
		पूर्णांक text_shndx;
		पूर्णांक symbols_shndx;
		पूर्णांक data_shndx;
		पूर्णांक rodata_shndx;
		पूर्णांक bss_shndx;
		पूर्णांक st_ops_shndx;
	पूर्ण efile;
	/*
	 * All loaded bpf_object is linked in a list, which is
	 * hidden to caller. bpf_objects__<func> handlers deal with
	 * all objects.
	 */
	काष्ठा list_head list;

	काष्ठा btf *btf;
	काष्ठा btf_ext *btf_ext;

	/* Parse and load BTF vmlinux अगर any of the programs in the object need
	 * it at load समय.
	 */
	काष्ठा btf *btf_vmlinux;
	/* vmlinux BTF override क्रम CO-RE relocations */
	काष्ठा btf *btf_vmlinux_override;
	/* Lazily initialized kernel module BTFs */
	काष्ठा module_btf *btf_modules;
	bool btf_modules_loaded;
	माप_प्रकार btf_module_cnt;
	माप_प्रकार btf_module_cap;

	व्योम *priv;
	bpf_object_clear_priv_t clear_priv;

	अक्षर path[];
पूर्ण;
#घोषणा obj_elf_valid(o)	((o)->efile.elf)

अटल स्थिर अक्षर *elf_sym_str(स्थिर काष्ठा bpf_object *obj, माप_प्रकार off);
अटल स्थिर अक्षर *elf_sec_str(स्थिर काष्ठा bpf_object *obj, माप_प्रकार off);
अटल Elf_Scn *elf_sec_by_idx(स्थिर काष्ठा bpf_object *obj, माप_प्रकार idx);
अटल Elf_Scn *elf_sec_by_name(स्थिर काष्ठा bpf_object *obj, स्थिर अक्षर *name);
अटल पूर्णांक elf_sec_hdr(स्थिर काष्ठा bpf_object *obj, Elf_Scn *scn, GElf_Shdr *hdr);
अटल स्थिर अक्षर *elf_sec_name(स्थिर काष्ठा bpf_object *obj, Elf_Scn *scn);
अटल Elf_Data *elf_sec_data(स्थिर काष्ठा bpf_object *obj, Elf_Scn *scn);

व्योम bpf_program__unload(काष्ठा bpf_program *prog)
अणु
	पूर्णांक i;

	अगर (!prog)
		वापस;

	/*
	 * If the object is खोलोed but the program was never loaded,
	 * it is possible that prog->instances.nr == -1.
	 */
	अगर (prog->instances.nr > 0) अणु
		क्रम (i = 0; i < prog->instances.nr; i++)
			zबंद(prog->instances.fds[i]);
	पूर्ण अन्यथा अगर (prog->instances.nr != -1) अणु
		pr_warn("Internal error: instances.nr is %d\n",
			prog->instances.nr);
	पूर्ण

	prog->instances.nr = -1;
	zमुक्त(&prog->instances.fds);

	zमुक्त(&prog->func_info);
	zमुक्त(&prog->line_info);
पूर्ण

अटल व्योम bpf_program__निकास(काष्ठा bpf_program *prog)
अणु
	अगर (!prog)
		वापस;

	अगर (prog->clear_priv)
		prog->clear_priv(prog, prog->priv);

	prog->priv = शून्य;
	prog->clear_priv = शून्य;

	bpf_program__unload(prog);
	zमुक्त(&prog->name);
	zमुक्त(&prog->sec_name);
	zमुक्त(&prog->pin_name);
	zमुक्त(&prog->insns);
	zमुक्त(&prog->reloc_desc);

	prog->nr_reloc = 0;
	prog->insns_cnt = 0;
	prog->sec_idx = -1;
पूर्ण

अटल अक्षर *__bpf_program__pin_name(काष्ठा bpf_program *prog)
अणु
	अक्षर *name, *p;

	name = p = strdup(prog->sec_name);
	जबतक ((p = म_अक्षर(p, '/')))
		*p = '_';

	वापस name;
पूर्ण

अटल bool insn_is_subprog_call(स्थिर काष्ठा bpf_insn *insn)
अणु
	वापस BPF_CLASS(insn->code) == BPF_JMP &&
	       BPF_OP(insn->code) == BPF_CALL &&
	       BPF_SRC(insn->code) == BPF_K &&
	       insn->src_reg == BPF_PSEUDO_CALL &&
	       insn->dst_reg == 0 &&
	       insn->off == 0;
पूर्ण

अटल bool is_ldimm64_insn(काष्ठा bpf_insn *insn)
अणु
	वापस insn->code == (BPF_LD | BPF_IMM | BPF_DW);
पूर्ण

अटल bool is_call_insn(स्थिर काष्ठा bpf_insn *insn)
अणु
	वापस insn->code == (BPF_JMP | BPF_CALL);
पूर्ण

अटल bool insn_is_pseuकरो_func(काष्ठा bpf_insn *insn)
अणु
	वापस is_ldimm64_insn(insn) && insn->src_reg == BPF_PSEUDO_FUNC;
पूर्ण

अटल पूर्णांक
bpf_object__init_prog(काष्ठा bpf_object *obj, काष्ठा bpf_program *prog,
		      स्थिर अक्षर *name, माप_प्रकार sec_idx, स्थिर अक्षर *sec_name,
		      माप_प्रकार sec_off, व्योम *insn_data, माप_प्रकार insn_data_sz)
अणु
	अगर (insn_data_sz == 0 || insn_data_sz % BPF_INSN_SZ || sec_off % BPF_INSN_SZ) अणु
		pr_warn("sec '%s': corrupted program '%s', offset %zu, size %zu\n",
			sec_name, name, sec_off, insn_data_sz);
		वापस -EINVAL;
	पूर्ण

	स_रखो(prog, 0, माप(*prog));
	prog->obj = obj;

	prog->sec_idx = sec_idx;
	prog->sec_insn_off = sec_off / BPF_INSN_SZ;
	prog->sec_insn_cnt = insn_data_sz / BPF_INSN_SZ;
	/* insns_cnt can later be increased by appending used subprograms */
	prog->insns_cnt = prog->sec_insn_cnt;

	prog->type = BPF_PROG_TYPE_UNSPEC;
	prog->load = true;

	prog->instances.fds = शून्य;
	prog->instances.nr = -1;

	prog->sec_name = strdup(sec_name);
	अगर (!prog->sec_name)
		जाओ errout;

	prog->name = strdup(name);
	अगर (!prog->name)
		जाओ errout;

	prog->pin_name = __bpf_program__pin_name(prog);
	अगर (!prog->pin_name)
		जाओ errout;

	prog->insns = दो_स्मृति(insn_data_sz);
	अगर (!prog->insns)
		जाओ errout;
	स_नकल(prog->insns, insn_data, insn_data_sz);

	वापस 0;
errout:
	pr_warn("sec '%s': failed to allocate memory for prog '%s'\n", sec_name, name);
	bpf_program__निकास(prog);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक
bpf_object__add_programs(काष्ठा bpf_object *obj, Elf_Data *sec_data,
			 स्थिर अक्षर *sec_name, पूर्णांक sec_idx)
अणु
	Elf_Data *symbols = obj->efile.symbols;
	काष्ठा bpf_program *prog, *progs;
	व्योम *data = sec_data->d_buf;
	माप_प्रकार sec_sz = sec_data->d_size, sec_off, prog_sz, nr_syms;
	पूर्णांक nr_progs, err, i;
	स्थिर अक्षर *name;
	GElf_Sym sym;

	progs = obj->programs;
	nr_progs = obj->nr_programs;
	nr_syms = symbols->d_size / माप(GElf_Sym);
	sec_off = 0;

	क्रम (i = 0; i < nr_syms; i++) अणु
		अगर (!gelf_माला_लोym(symbols, i, &sym))
			जारी;
		अगर (sym.st_shndx != sec_idx)
			जारी;
		अगर (GELF_ST_TYPE(sym.st_info) != STT_FUNC)
			जारी;

		prog_sz = sym.st_size;
		sec_off = sym.st_value;

		name = elf_sym_str(obj, sym.st_name);
		अगर (!name) अणु
			pr_warn("sec '%s': failed to get symbol name for offset %zu\n",
				sec_name, sec_off);
			वापस -LIBBPF_ERRNO__FORMAT;
		पूर्ण

		अगर (sec_off + prog_sz > sec_sz) अणु
			pr_warn("sec '%s': program at offset %zu crosses section boundary\n",
				sec_name, sec_off);
			वापस -LIBBPF_ERRNO__FORMAT;
		पूर्ण

		pr_debug("sec '%s': found program '%s' at insn offset %zu (%zu bytes), code size %zu insns (%zu bytes)\n",
			 sec_name, name, sec_off / BPF_INSN_SZ, sec_off, prog_sz / BPF_INSN_SZ, prog_sz);

		progs = libbpf_पुनः_स्मृतिarray(progs, nr_progs + 1, माप(*progs));
		अगर (!progs) अणु
			/*
			 * In this हाल the original obj->programs
			 * is still valid, so करोn't need special treat क्रम
			 * bpf_बंद_object().
			 */
			pr_warn("sec '%s': failed to alloc memory for new program '%s'\n",
				sec_name, name);
			वापस -ENOMEM;
		पूर्ण
		obj->programs = progs;

		prog = &progs[nr_progs];

		err = bpf_object__init_prog(obj, prog, name, sec_idx, sec_name,
					    sec_off, data + sec_off, prog_sz);
		अगर (err)
			वापस err;

		/* अगर function is a global/weak symbol, but has hidden
		 * visibility (STV_HIDDEN), mark its BTF FUNC as अटल to
		 * enable more permissive BPF verअगरication mode with more
		 * outside context available to BPF verअगरier
		 */
		अगर (GELF_ST_BIND(sym.st_info) != STB_LOCAL
		    && GELF_ST_VISIBILITY(sym.st_other) == STV_HIDDEN)
			prog->mark_btf_अटल = true;

		nr_progs++;
		obj->nr_programs = nr_progs;
	पूर्ण

	वापस 0;
पूर्ण

अटल __u32 get_kernel_version(व्योम)
अणु
	__u32 major, minor, patch;
	काष्ठा utsname info;

	uname(&info);
	अगर (माला_पूछो(info.release, "%u.%u.%u", &major, &minor, &patch) != 3)
		वापस 0;
	वापस KERNEL_VERSION(major, minor, patch);
पूर्ण

अटल स्थिर काष्ठा btf_member *
find_member_by_offset(स्थिर काष्ठा btf_type *t, __u32 bit_offset)
अणु
	काष्ठा btf_member *m;
	पूर्णांक i;

	क्रम (i = 0, m = btf_members(t); i < btf_vlen(t); i++, m++) अणु
		अगर (btf_member_bit_offset(t, i) == bit_offset)
			वापस m;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा btf_member *
find_member_by_name(स्थिर काष्ठा btf *btf, स्थिर काष्ठा btf_type *t,
		    स्थिर अक्षर *name)
अणु
	काष्ठा btf_member *m;
	पूर्णांक i;

	क्रम (i = 0, m = btf_members(t); i < btf_vlen(t); i++, m++) अणु
		अगर (!म_भेद(btf__name_by_offset(btf, m->name_off), name))
			वापस m;
	पूर्ण

	वापस शून्य;
पूर्ण

#घोषणा STRUCT_OPS_VALUE_PREFIX "bpf_struct_ops_"
अटल पूर्णांक find_btf_by_prefix_kind(स्थिर काष्ठा btf *btf, स्थिर अक्षर *prefix,
				   स्थिर अक्षर *name, __u32 kind);

अटल पूर्णांक
find_काष्ठा_ops_kern_types(स्थिर काष्ठा btf *btf, स्थिर अक्षर *tname,
			   स्थिर काष्ठा btf_type **type, __u32 *type_id,
			   स्थिर काष्ठा btf_type **vtype, __u32 *vtype_id,
			   स्थिर काष्ठा btf_member **data_member)
अणु
	स्थिर काष्ठा btf_type *kern_type, *kern_vtype;
	स्थिर काष्ठा btf_member *kern_data_member;
	__s32 kern_vtype_id, kern_type_id;
	__u32 i;

	kern_type_id = btf__find_by_name_kind(btf, tname, BTF_KIND_STRUCT);
	अगर (kern_type_id < 0) अणु
		pr_warn("struct_ops init_kern: struct %s is not found in kernel BTF\n",
			tname);
		वापस kern_type_id;
	पूर्ण
	kern_type = btf__type_by_id(btf, kern_type_id);

	/* Find the corresponding "map_value" type that will be used
	 * in map_update(BPF_MAP_TYPE_STRUCT_OPS).  For example,
	 * find "struct bpf_struct_ops_tcp_congestion_ops" from the
	 * btf_vmlinux.
	 */
	kern_vtype_id = find_btf_by_prefix_kind(btf, STRUCT_OPS_VALUE_PREFIX,
						tname, BTF_KIND_STRUCT);
	अगर (kern_vtype_id < 0) अणु
		pr_warn("struct_ops init_kern: struct %s%s is not found in kernel BTF\n",
			STRUCT_OPS_VALUE_PREFIX, tname);
		वापस kern_vtype_id;
	पूर्ण
	kern_vtype = btf__type_by_id(btf, kern_vtype_id);

	/* Find "struct tcp_congestion_ops" from
	 * काष्ठा bpf_काष्ठा_ops_tcp_congestion_ops अणु
	 *	[ ... ]
	 *	काष्ठा tcp_congestion_ops data;
	 * पूर्ण
	 */
	kern_data_member = btf_members(kern_vtype);
	क्रम (i = 0; i < btf_vlen(kern_vtype); i++, kern_data_member++) अणु
		अगर (kern_data_member->type == kern_type_id)
			अवरोध;
	पूर्ण
	अगर (i == btf_vlen(kern_vtype)) अणु
		pr_warn("struct_ops init_kern: struct %s data is not found in struct %s%s\n",
			tname, STRUCT_OPS_VALUE_PREFIX, tname);
		वापस -EINVAL;
	पूर्ण

	*type = kern_type;
	*type_id = kern_type_id;
	*vtype = kern_vtype;
	*vtype_id = kern_vtype_id;
	*data_member = kern_data_member;

	वापस 0;
पूर्ण

अटल bool bpf_map__is_काष्ठा_ops(स्थिर काष्ठा bpf_map *map)
अणु
	वापस map->def.type == BPF_MAP_TYPE_STRUCT_OPS;
पूर्ण

/* Init the map's fields that depend on kern_btf */
अटल पूर्णांक bpf_map__init_kern_काष्ठा_ops(काष्ठा bpf_map *map,
					 स्थिर काष्ठा btf *btf,
					 स्थिर काष्ठा btf *kern_btf)
अणु
	स्थिर काष्ठा btf_member *member, *kern_member, *kern_data_member;
	स्थिर काष्ठा btf_type *type, *kern_type, *kern_vtype;
	__u32 i, kern_type_id, kern_vtype_id, kern_data_off;
	काष्ठा bpf_काष्ठा_ops *st_ops;
	व्योम *data, *kern_data;
	स्थिर अक्षर *tname;
	पूर्णांक err;

	st_ops = map->st_ops;
	type = st_ops->type;
	tname = st_ops->tname;
	err = find_काष्ठा_ops_kern_types(kern_btf, tname,
					 &kern_type, &kern_type_id,
					 &kern_vtype, &kern_vtype_id,
					 &kern_data_member);
	अगर (err)
		वापस err;

	pr_debug("struct_ops init_kern %s: type_id:%u kern_type_id:%u kern_vtype_id:%u\n",
		 map->name, st_ops->type_id, kern_type_id, kern_vtype_id);

	map->def.value_size = kern_vtype->size;
	map->btf_vmlinux_value_type_id = kern_vtype_id;

	st_ops->kern_vdata = सुस्मृति(1, kern_vtype->size);
	अगर (!st_ops->kern_vdata)
		वापस -ENOMEM;

	data = st_ops->data;
	kern_data_off = kern_data_member->offset / 8;
	kern_data = st_ops->kern_vdata + kern_data_off;

	member = btf_members(type);
	क्रम (i = 0; i < btf_vlen(type); i++, member++) अणु
		स्थिर काष्ठा btf_type *mtype, *kern_mtype;
		__u32 mtype_id, kern_mtype_id;
		व्योम *mdata, *kern_mdata;
		__s64 msize, kern_msize;
		__u32 moff, kern_moff;
		__u32 kern_member_idx;
		स्थिर अक्षर *mname;

		mname = btf__name_by_offset(btf, member->name_off);
		kern_member = find_member_by_name(kern_btf, kern_type, mname);
		अगर (!kern_member) अणु
			pr_warn("struct_ops init_kern %s: Cannot find member %s in kernel BTF\n",
				map->name, mname);
			वापस -ENOTSUP;
		पूर्ण

		kern_member_idx = kern_member - btf_members(kern_type);
		अगर (btf_member_bitfield_size(type, i) ||
		    btf_member_bitfield_size(kern_type, kern_member_idx)) अणु
			pr_warn("struct_ops init_kern %s: bitfield %s is not supported\n",
				map->name, mname);
			वापस -ENOTSUP;
		पूर्ण

		moff = member->offset / 8;
		kern_moff = kern_member->offset / 8;

		mdata = data + moff;
		kern_mdata = kern_data + kern_moff;

		mtype = skip_mods_and_प्रकारs(btf, member->type, &mtype_id);
		kern_mtype = skip_mods_and_प्रकारs(kern_btf, kern_member->type,
						    &kern_mtype_id);
		अगर (BTF_INFO_KIND(mtype->info) !=
		    BTF_INFO_KIND(kern_mtype->info)) अणु
			pr_warn("struct_ops init_kern %s: Unmatched member type %s %u != %u(kernel)\n",
				map->name, mname, BTF_INFO_KIND(mtype->info),
				BTF_INFO_KIND(kern_mtype->info));
			वापस -ENOTSUP;
		पूर्ण

		अगर (btf_is_ptr(mtype)) अणु
			काष्ठा bpf_program *prog;

			prog = st_ops->progs[i];
			अगर (!prog)
				जारी;

			kern_mtype = skip_mods_and_प्रकारs(kern_btf,
							    kern_mtype->type,
							    &kern_mtype_id);

			/* mtype->type must be a func_proto which was
			 * guaranteed in bpf_object__collect_st_ops_relos(),
			 * so only check kern_mtype क्रम func_proto here.
			 */
			अगर (!btf_is_func_proto(kern_mtype)) अणु
				pr_warn("struct_ops init_kern %s: kernel member %s is not a func ptr\n",
					map->name, mname);
				वापस -ENOTSUP;
			पूर्ण

			prog->attach_btf_id = kern_type_id;
			prog->expected_attach_type = kern_member_idx;

			st_ops->kern_func_off[i] = kern_data_off + kern_moff;

			pr_debug("struct_ops init_kern %s: func ptr %s is set to prog %s from data(+%u) to kern_data(+%u)\n",
				 map->name, mname, prog->name, moff,
				 kern_moff);

			जारी;
		पूर्ण

		msize = btf__resolve_size(btf, mtype_id);
		kern_msize = btf__resolve_size(kern_btf, kern_mtype_id);
		अगर (msize < 0 || kern_msize < 0 || msize != kern_msize) अणु
			pr_warn("struct_ops init_kern %s: Error in size of member %s: %zd != %zd(kernel)\n",
				map->name, mname, (sमाप_प्रकार)msize,
				(sमाप_प्रकार)kern_msize);
			वापस -ENOTSUP;
		पूर्ण

		pr_debug("struct_ops init_kern %s: copy %s %u bytes from data(+%u) to kern_data(+%u)\n",
			 map->name, mname, (अचिन्हित पूर्णांक)msize,
			 moff, kern_moff);
		स_नकल(kern_mdata, mdata, msize);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bpf_object__init_kern_काष्ठा_ops_maps(काष्ठा bpf_object *obj)
अणु
	काष्ठा bpf_map *map;
	माप_प्रकार i;
	पूर्णांक err;

	क्रम (i = 0; i < obj->nr_maps; i++) अणु
		map = &obj->maps[i];

		अगर (!bpf_map__is_काष्ठा_ops(map))
			जारी;

		err = bpf_map__init_kern_काष्ठा_ops(map, obj->btf,
						    obj->btf_vmlinux);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bpf_object__init_काष्ठा_ops_maps(काष्ठा bpf_object *obj)
अणु
	स्थिर काष्ठा btf_type *type, *datasec;
	स्थिर काष्ठा btf_var_secinfo *vsi;
	काष्ठा bpf_काष्ठा_ops *st_ops;
	स्थिर अक्षर *tname, *var_name;
	__s32 type_id, datasec_id;
	स्थिर काष्ठा btf *btf;
	काष्ठा bpf_map *map;
	__u32 i;

	अगर (obj->efile.st_ops_shndx == -1)
		वापस 0;

	btf = obj->btf;
	datasec_id = btf__find_by_name_kind(btf, STRUCT_OPS_SEC,
					    BTF_KIND_DATASEC);
	अगर (datasec_id < 0) अणु
		pr_warn("struct_ops init: DATASEC %s not found\n",
			STRUCT_OPS_SEC);
		वापस -EINVAL;
	पूर्ण

	datasec = btf__type_by_id(btf, datasec_id);
	vsi = btf_var_secinfos(datasec);
	क्रम (i = 0; i < btf_vlen(datasec); i++, vsi++) अणु
		type = btf__type_by_id(obj->btf, vsi->type);
		var_name = btf__name_by_offset(obj->btf, type->name_off);

		type_id = btf__resolve_type(obj->btf, vsi->type);
		अगर (type_id < 0) अणु
			pr_warn("struct_ops init: Cannot resolve var type_id %u in DATASEC %s\n",
				vsi->type, STRUCT_OPS_SEC);
			वापस -EINVAL;
		पूर्ण

		type = btf__type_by_id(obj->btf, type_id);
		tname = btf__name_by_offset(obj->btf, type->name_off);
		अगर (!tname[0]) अणु
			pr_warn("struct_ops init: anonymous type is not supported\n");
			वापस -ENOTSUP;
		पूर्ण
		अगर (!btf_is_काष्ठा(type)) अणु
			pr_warn("struct_ops init: %s is not a struct\n", tname);
			वापस -EINVAL;
		पूर्ण

		map = bpf_object__add_map(obj);
		अगर (IS_ERR(map))
			वापस PTR_ERR(map);

		map->sec_idx = obj->efile.st_ops_shndx;
		map->sec_offset = vsi->offset;
		map->name = strdup(var_name);
		अगर (!map->name)
			वापस -ENOMEM;

		map->def.type = BPF_MAP_TYPE_STRUCT_OPS;
		map->def.key_size = माप(पूर्णांक);
		map->def.value_size = type->size;
		map->def.max_entries = 1;

		map->st_ops = सुस्मृति(1, माप(*map->st_ops));
		अगर (!map->st_ops)
			वापस -ENOMEM;
		st_ops = map->st_ops;
		st_ops->data = दो_स्मृति(type->size);
		st_ops->progs = सुस्मृति(btf_vlen(type), माप(*st_ops->progs));
		st_ops->kern_func_off = दो_स्मृति(btf_vlen(type) *
					       माप(*st_ops->kern_func_off));
		अगर (!st_ops->data || !st_ops->progs || !st_ops->kern_func_off)
			वापस -ENOMEM;

		अगर (vsi->offset + type->size > obj->efile.st_ops_data->d_size) अणु
			pr_warn("struct_ops init: var %s is beyond the end of DATASEC %s\n",
				var_name, STRUCT_OPS_SEC);
			वापस -EINVAL;
		पूर्ण

		स_नकल(st_ops->data,
		       obj->efile.st_ops_data->d_buf + vsi->offset,
		       type->size);
		st_ops->tname = tname;
		st_ops->type = type;
		st_ops->type_id = type_id;

		pr_debug("struct_ops init: struct %s(type_id=%u) %s found at offset %u\n",
			 tname, type_id, var_name, vsi->offset);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा bpf_object *bpf_object__new(स्थिर अक्षर *path,
					  स्थिर व्योम *obj_buf,
					  माप_प्रकार obj_buf_sz,
					  स्थिर अक्षर *obj_name)
अणु
	काष्ठा bpf_object *obj;
	अक्षर *end;

	obj = सुस्मृति(1, माप(काष्ठा bpf_object) + म_माप(path) + 1);
	अगर (!obj) अणु
		pr_warn("alloc memory failed for %s\n", path);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	म_नकल(obj->path, path);
	अगर (obj_name) अणु
		म_नकलन(obj->name, obj_name, माप(obj->name) - 1);
		obj->name[माप(obj->name) - 1] = 0;
	पूर्ण अन्यथा अणु
		/* Using basename() GNU version which करोesn't modअगरy arg. */
		म_नकलन(obj->name, basename((व्योम *)path),
			माप(obj->name) - 1);
		end = म_अक्षर(obj->name, '.');
		अगर (end)
			*end = 0;
	पूर्ण

	obj->efile.fd = -1;
	/*
	 * Caller of this function should also call
	 * bpf_object__elf_finish() after data collection to वापस
	 * obj_buf to user. If not, we should duplicate the buffer to
	 * aव्योम user मुक्तing them beक्रमe elf finish.
	 */
	obj->efile.obj_buf = obj_buf;
	obj->efile.obj_buf_sz = obj_buf_sz;
	obj->efile.maps_shndx = -1;
	obj->efile.btf_maps_shndx = -1;
	obj->efile.data_shndx = -1;
	obj->efile.rodata_shndx = -1;
	obj->efile.bss_shndx = -1;
	obj->efile.st_ops_shndx = -1;
	obj->kconfig_map_idx = -1;
	obj->rodata_map_idx = -1;

	obj->kern_version = get_kernel_version();
	obj->loaded = false;

	INIT_LIST_HEAD(&obj->list);
	list_add(&obj->list, &bpf_objects_list);
	वापस obj;
पूर्ण

अटल व्योम bpf_object__elf_finish(काष्ठा bpf_object *obj)
अणु
	अगर (!obj_elf_valid(obj))
		वापस;

	अगर (obj->efile.elf) अणु
		elf_end(obj->efile.elf);
		obj->efile.elf = शून्य;
	पूर्ण
	obj->efile.symbols = शून्य;
	obj->efile.data = शून्य;
	obj->efile.rodata = शून्य;
	obj->efile.bss = शून्य;
	obj->efile.st_ops_data = शून्य;

	zमुक्त(&obj->efile.reloc_sects);
	obj->efile.nr_reloc_sects = 0;
	zबंद(obj->efile.fd);
	obj->efile.obj_buf = शून्य;
	obj->efile.obj_buf_sz = 0;
पूर्ण

अटल पूर्णांक bpf_object__elf_init(काष्ठा bpf_object *obj)
अणु
	पूर्णांक err = 0;
	GElf_Ehdr *ep;

	अगर (obj_elf_valid(obj)) अणु
		pr_warn("elf: init internal error\n");
		वापस -LIBBPF_ERRNO__LIBELF;
	पूर्ण

	अगर (obj->efile.obj_buf_sz > 0) अणु
		/*
		 * obj_buf should have been validated by
		 * bpf_object__खोलो_buffer().
		 */
		obj->efile.elf = elf_memory((अक्षर *)obj->efile.obj_buf,
					    obj->efile.obj_buf_sz);
	पूर्ण अन्यथा अणु
		obj->efile.fd = खोलो(obj->path, O_RDONLY);
		अगर (obj->efile.fd < 0) अणु
			अक्षर errmsg[STRERR_बफ_मानE], *cp;

			err = -त्रुटि_सं;
			cp = libbpf_म_त्रुटि_r(err, errmsg, माप(errmsg));
			pr_warn("elf: failed to open %s: %s\n", obj->path, cp);
			वापस err;
		पूर्ण

		obj->efile.elf = elf_begin(obj->efile.fd, ELF_C_READ_MMAP, शून्य);
	पूर्ण

	अगर (!obj->efile.elf) अणु
		pr_warn("elf: failed to open %s as ELF file: %s\n", obj->path, elf_errmsg(-1));
		err = -LIBBPF_ERRNO__LIBELF;
		जाओ errout;
	पूर्ण

	अगर (!gelf_getehdr(obj->efile.elf, &obj->efile.ehdr)) अणु
		pr_warn("elf: failed to get ELF header from %s: %s\n", obj->path, elf_errmsg(-1));
		err = -LIBBPF_ERRNO__FORMAT;
		जाओ errout;
	पूर्ण
	ep = &obj->efile.ehdr;

	अगर (elf_माला_लोhdrstrndx(obj->efile.elf, &obj->efile.shstrndx)) अणु
		pr_warn("elf: failed to get section names section index for %s: %s\n",
			obj->path, elf_errmsg(-1));
		err = -LIBBPF_ERRNO__FORMAT;
		जाओ errout;
	पूर्ण

	/* Elf is corrupted/truncated, aव्योम calling elf_strptr. */
	अगर (!elf_rawdata(elf_माला_लोcn(obj->efile.elf, obj->efile.shstrndx), शून्य)) अणु
		pr_warn("elf: failed to get section names strings from %s: %s\n",
			obj->path, elf_errmsg(-1));
		err = -LIBBPF_ERRNO__FORMAT;
		जाओ errout;
	पूर्ण

	/* Old LLVM set e_machine to EM_NONE */
	अगर (ep->e_type != ET_REL ||
	    (ep->e_machine && ep->e_machine != EM_BPF)) अणु
		pr_warn("elf: %s is not a valid eBPF object file\n", obj->path);
		err = -LIBBPF_ERRNO__FORMAT;
		जाओ errout;
	पूर्ण

	वापस 0;
errout:
	bpf_object__elf_finish(obj);
	वापस err;
पूर्ण

अटल पूर्णांक bpf_object__check_endianness(काष्ठा bpf_object *obj)
अणु
#अगर __BYTE_ORDER == __LITTLE_ENDIAN
	अगर (obj->efile.ehdr.e_ident[EI_DATA] == ELFDATA2LSB)
		वापस 0;
#या_अगर __BYTE_ORDER == __BIG_ENDIAN
	अगर (obj->efile.ehdr.e_ident[EI_DATA] == ELFDATA2MSB)
		वापस 0;
#अन्यथा
# error "Unrecognized __BYTE_ORDER__"
#पूर्ण_अगर
	pr_warn("elf: endianness mismatch in %s.\n", obj->path);
	वापस -LIBBPF_ERRNO__ENDIAN;
पूर्ण

अटल पूर्णांक
bpf_object__init_license(काष्ठा bpf_object *obj, व्योम *data, माप_प्रकार size)
अणु
	स_नकल(obj->license, data, min(size, माप(obj->license) - 1));
	pr_debug("license of %s is %s\n", obj->path, obj->license);
	वापस 0;
पूर्ण

अटल पूर्णांक
bpf_object__init_kversion(काष्ठा bpf_object *obj, व्योम *data, माप_प्रकार size)
अणु
	__u32 kver;

	अगर (size != माप(kver)) अणु
		pr_warn("invalid kver section in %s\n", obj->path);
		वापस -LIBBPF_ERRNO__FORMAT;
	पूर्ण
	स_नकल(&kver, data, माप(kver));
	obj->kern_version = kver;
	pr_debug("kernel version of %s is %x\n", obj->path, obj->kern_version);
	वापस 0;
पूर्ण

अटल bool bpf_map_type__is_map_in_map(क्रमागत bpf_map_type type)
अणु
	अगर (type == BPF_MAP_TYPE_ARRAY_OF_MAPS ||
	    type == BPF_MAP_TYPE_HASH_OF_MAPS)
		वापस true;
	वापस false;
पूर्ण

पूर्णांक bpf_object__section_size(स्थिर काष्ठा bpf_object *obj, स्थिर अक्षर *name,
			     __u32 *size)
अणु
	पूर्णांक ret = -ENOENT;

	*size = 0;
	अगर (!name) अणु
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (!म_भेद(name, DATA_SEC)) अणु
		अगर (obj->efile.data)
			*size = obj->efile.data->d_size;
	पूर्ण अन्यथा अगर (!म_भेद(name, BSS_SEC)) अणु
		अगर (obj->efile.bss)
			*size = obj->efile.bss->d_size;
	पूर्ण अन्यथा अगर (!म_भेद(name, RODATA_SEC)) अणु
		अगर (obj->efile.rodata)
			*size = obj->efile.rodata->d_size;
	पूर्ण अन्यथा अगर (!म_भेद(name, STRUCT_OPS_SEC)) अणु
		अगर (obj->efile.st_ops_data)
			*size = obj->efile.st_ops_data->d_size;
	पूर्ण अन्यथा अणु
		Elf_Scn *scn = elf_sec_by_name(obj, name);
		Elf_Data *data = elf_sec_data(obj, scn);

		अगर (data) अणु
			ret = 0; /* found it */
			*size = data->d_size;
		पूर्ण
	पूर्ण

	वापस *size ? 0 : ret;
पूर्ण

पूर्णांक bpf_object__variable_offset(स्थिर काष्ठा bpf_object *obj, स्थिर अक्षर *name,
				__u32 *off)
अणु
	Elf_Data *symbols = obj->efile.symbols;
	स्थिर अक्षर *sname;
	माप_प्रकार si;

	अगर (!name || !off)
		वापस -EINVAL;

	क्रम (si = 0; si < symbols->d_size / माप(GElf_Sym); si++) अणु
		GElf_Sym sym;

		अगर (!gelf_माला_लोym(symbols, si, &sym))
			जारी;
		अगर (GELF_ST_BIND(sym.st_info) != STB_GLOBAL ||
		    GELF_ST_TYPE(sym.st_info) != STT_OBJECT)
			जारी;

		sname = elf_sym_str(obj, sym.st_name);
		अगर (!sname) अणु
			pr_warn("failed to get sym name string for var %s\n",
				name);
			वापस -EIO;
		पूर्ण
		अगर (म_भेद(name, sname) == 0) अणु
			*off = sym.st_value;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -ENOENT;
पूर्ण

अटल काष्ठा bpf_map *bpf_object__add_map(काष्ठा bpf_object *obj)
अणु
	काष्ठा bpf_map *new_maps;
	माप_प्रकार new_cap;
	पूर्णांक i;

	अगर (obj->nr_maps < obj->maps_cap)
		वापस &obj->maps[obj->nr_maps++];

	new_cap = max((माप_प्रकार)4, obj->maps_cap * 3 / 2);
	new_maps = libbpf_पुनः_स्मृतिarray(obj->maps, new_cap, माप(*obj->maps));
	अगर (!new_maps) अणु
		pr_warn("alloc maps for object failed\n");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	obj->maps_cap = new_cap;
	obj->maps = new_maps;

	/* zero out new maps */
	स_रखो(obj->maps + obj->nr_maps, 0,
	       (obj->maps_cap - obj->nr_maps) * माप(*obj->maps));
	/*
	 * fill all fd with -1 so won't बंद incorrect fd (fd=0 is मानक_निवेश)
	 * when failure (zबंद won't बंद negative fd)).
	 */
	क्रम (i = obj->nr_maps; i < obj->maps_cap; i++) अणु
		obj->maps[i].fd = -1;
		obj->maps[i].inner_map_fd = -1;
	पूर्ण

	वापस &obj->maps[obj->nr_maps++];
पूर्ण

अटल माप_प्रकार bpf_map_mmap_sz(स्थिर काष्ठा bpf_map *map)
अणु
	दीर्घ page_sz = sysconf(_SC_PAGE_SIZE);
	माप_प्रकार map_sz;

	map_sz = (माप_प्रकार)roundup(map->def.value_size, 8) * map->def.max_entries;
	map_sz = roundup(map_sz, page_sz);
	वापस map_sz;
पूर्ण

अटल अक्षर *पूर्णांकernal_map_name(काष्ठा bpf_object *obj,
			       क्रमागत libbpf_map_type type)
अणु
	अक्षर map_name[BPF_OBJ_NAME_LEN], *p;
	स्थिर अक्षर *sfx = libbpf_type_to_btf_name[type];
	पूर्णांक sfx_len = max((माप_प्रकार)7, म_माप(sfx));
	पूर्णांक pfx_len = min((माप_प्रकार)BPF_OBJ_NAME_LEN - sfx_len - 1,
			  म_माप(obj->name));

	snम_लिखो(map_name, माप(map_name), "%.*s%.*s", pfx_len, obj->name,
		 sfx_len, libbpf_type_to_btf_name[type]);

	/* sanitise map name to अक्षरacters allowed by kernel */
	क्रम (p = map_name; *p && p < map_name + माप(map_name); p++)
		अगर (!है_अक्षर_अंक(*p) && *p != '_' && *p != '.')
			*p = '_';

	वापस strdup(map_name);
पूर्ण

अटल पूर्णांक
bpf_object__init_पूर्णांकernal_map(काष्ठा bpf_object *obj, क्रमागत libbpf_map_type type,
			      पूर्णांक sec_idx, व्योम *data, माप_प्रकार data_sz)
अणु
	काष्ठा bpf_map_def *def;
	काष्ठा bpf_map *map;
	पूर्णांक err;

	map = bpf_object__add_map(obj);
	अगर (IS_ERR(map))
		वापस PTR_ERR(map);

	map->libbpf_type = type;
	map->sec_idx = sec_idx;
	map->sec_offset = 0;
	map->name = पूर्णांकernal_map_name(obj, type);
	अगर (!map->name) अणु
		pr_warn("failed to alloc map name\n");
		वापस -ENOMEM;
	पूर्ण

	def = &map->def;
	def->type = BPF_MAP_TYPE_ARRAY;
	def->key_size = माप(पूर्णांक);
	def->value_size = data_sz;
	def->max_entries = 1;
	def->map_flags = type == LIBBPF_MAP_RODATA || type == LIBBPF_MAP_KCONFIG
			 ? BPF_F_RDONLY_PROG : 0;
	def->map_flags |= BPF_F_MMAPABLE;

	pr_debug("map '%s' (global data): at sec_idx %d, offset %zu, flags %x.\n",
		 map->name, map->sec_idx, map->sec_offset, def->map_flags);

	map->mmaped = mmap(शून्य, bpf_map_mmap_sz(map), PROT_READ | PROT_WRITE,
			   MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	अगर (map->mmaped == MAP_FAILED) अणु
		err = -त्रुटि_सं;
		map->mmaped = शून्य;
		pr_warn("failed to alloc map '%s' content buffer: %d\n",
			map->name, err);
		zमुक्त(&map->name);
		वापस err;
	पूर्ण

	अगर (data)
		स_नकल(map->mmaped, data, data_sz);

	pr_debug("map %td is \"%s\"\n", map - obj->maps, map->name);
	वापस 0;
पूर्ण

अटल पूर्णांक bpf_object__init_global_data_maps(काष्ठा bpf_object *obj)
अणु
	पूर्णांक err;

	/*
	 * Populate obj->maps with libbpf पूर्णांकernal maps.
	 */
	अगर (obj->efile.data_shndx >= 0) अणु
		err = bpf_object__init_पूर्णांकernal_map(obj, LIBBPF_MAP_DATA,
						    obj->efile.data_shndx,
						    obj->efile.data->d_buf,
						    obj->efile.data->d_size);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (obj->efile.rodata_shndx >= 0) अणु
		err = bpf_object__init_पूर्णांकernal_map(obj, LIBBPF_MAP_RODATA,
						    obj->efile.rodata_shndx,
						    obj->efile.rodata->d_buf,
						    obj->efile.rodata->d_size);
		अगर (err)
			वापस err;

		obj->rodata_map_idx = obj->nr_maps - 1;
	पूर्ण
	अगर (obj->efile.bss_shndx >= 0) अणु
		err = bpf_object__init_पूर्णांकernal_map(obj, LIBBPF_MAP_BSS,
						    obj->efile.bss_shndx,
						    शून्य,
						    obj->efile.bss->d_size);
		अगर (err)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण


अटल काष्ठा बाह्य_desc *find_बाह्य_by_name(स्थिर काष्ठा bpf_object *obj,
					       स्थिर व्योम *name)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < obj->nr_बाह्य; i++) अणु
		अगर (म_भेद(obj->बाह्यs[i].name, name) == 0)
			वापस &obj->बाह्यs[i];
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक set_kcfg_value_tri(काष्ठा बाह्य_desc *ext, व्योम *ext_val,
			      अक्षर value)
अणु
	चयन (ext->kcfg.type) अणु
	हाल KCFG_BOOL:
		अगर (value == 'm') अणु
			pr_warn("extern (kcfg) %s=%c should be tristate or char\n",
				ext->name, value);
			वापस -EINVAL;
		पूर्ण
		*(bool *)ext_val = value == 'y' ? true : false;
		अवरोध;
	हाल KCFG_TRISTATE:
		अगर (value == 'y')
			*(क्रमागत libbpf_tristate *)ext_val = TRI_YES;
		अन्यथा अगर (value == 'm')
			*(क्रमागत libbpf_tristate *)ext_val = TRI_MODULE;
		अन्यथा /* value == 'n' */
			*(क्रमागत libbpf_tristate *)ext_val = TRI_NO;
		अवरोध;
	हाल KCFG_CHAR:
		*(अक्षर *)ext_val = value;
		अवरोध;
	हाल KCFG_UNKNOWN:
	हाल KCFG_INT:
	हाल KCFG_CHAR_ARR:
	शेष:
		pr_warn("extern (kcfg) %s=%c should be bool, tristate, or char\n",
			ext->name, value);
		वापस -EINVAL;
	पूर्ण
	ext->is_set = true;
	वापस 0;
पूर्ण

अटल पूर्णांक set_kcfg_value_str(काष्ठा बाह्य_desc *ext, अक्षर *ext_val,
			      स्थिर अक्षर *value)
अणु
	माप_प्रकार len;

	अगर (ext->kcfg.type != KCFG_CHAR_ARR) अणु
		pr_warn("extern (kcfg) %s=%s should be char array\n", ext->name, value);
		वापस -EINVAL;
	पूर्ण

	len = म_माप(value);
	अगर (value[len - 1] != '"') अणु
		pr_warn("extern (kcfg) '%s': invalid string config '%s'\n",
			ext->name, value);
		वापस -EINVAL;
	पूर्ण

	/* strip quotes */
	len -= 2;
	अगर (len >= ext->kcfg.sz) अणु
		pr_warn("extern (kcfg) '%s': long string config %s of (%zu bytes) truncated to %d bytes\n",
			ext->name, value, len, ext->kcfg.sz - 1);
		len = ext->kcfg.sz - 1;
	पूर्ण
	स_नकल(ext_val, value + 1, len);
	ext_val[len] = '\0';
	ext->is_set = true;
	वापस 0;
पूर्ण

अटल पूर्णांक parse_u64(स्थिर अक्षर *value, __u64 *res)
अणु
	अक्षर *value_end;
	पूर्णांक err;

	त्रुटि_सं = 0;
	*res = म_से_अदीर्घl(value, &value_end, 0);
	अगर (त्रुटि_सं) अणु
		err = -त्रुटि_सं;
		pr_warn("failed to parse '%s' as integer: %d\n", value, err);
		वापस err;
	पूर्ण
	अगर (*value_end) अणु
		pr_warn("failed to parse '%s' as integer completely\n", value);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल bool is_kcfg_value_in_range(स्थिर काष्ठा बाह्य_desc *ext, __u64 v)
अणु
	पूर्णांक bit_sz = ext->kcfg.sz * 8;

	अगर (ext->kcfg.sz == 8)
		वापस true;

	/* Validate that value stored in u64 fits in पूर्णांकeger of `ext->sz`
	 * bytes size without any loss of inक्रमmation. If the target पूर्णांकeger
	 * is चिन्हित, we rely on the following limits of पूर्णांकeger type of
	 * Y bits and subsequent transक्रमmation:
	 *
	 *     -2^(Y-1) <= X           <= 2^(Y-1) - 1
	 *            0 <= X + 2^(Y-1) <= 2^Y - 1
	 *            0 <= X + 2^(Y-1) <  2^Y
	 *
	 *  For अचिन्हित target पूर्णांकeger, check that all the (64 - Y) bits are
	 *  zero.
	 */
	अगर (ext->kcfg.is_चिन्हित)
		वापस v + (1ULL << (bit_sz - 1)) < (1ULL << bit_sz);
	अन्यथा
		वापस (v >> bit_sz) == 0;
पूर्ण

अटल पूर्णांक set_kcfg_value_num(काष्ठा बाह्य_desc *ext, व्योम *ext_val,
			      __u64 value)
अणु
	अगर (ext->kcfg.type != KCFG_INT && ext->kcfg.type != KCFG_CHAR) अणु
		pr_warn("extern (kcfg) %s=%llu should be integer\n",
			ext->name, (अचिन्हित दीर्घ दीर्घ)value);
		वापस -EINVAL;
	पूर्ण
	अगर (!is_kcfg_value_in_range(ext, value)) अणु
		pr_warn("extern (kcfg) %s=%llu value doesn't fit in %d bytes\n",
			ext->name, (अचिन्हित दीर्घ दीर्घ)value, ext->kcfg.sz);
		वापस -दुस्फल;
	पूर्ण
	चयन (ext->kcfg.sz) अणु
		हाल 1: *(__u8 *)ext_val = value; अवरोध;
		हाल 2: *(__u16 *)ext_val = value; अवरोध;
		हाल 4: *(__u32 *)ext_val = value; अवरोध;
		हाल 8: *(__u64 *)ext_val = value; अवरोध;
		शेष:
			वापस -EINVAL;
	पूर्ण
	ext->is_set = true;
	वापस 0;
पूर्ण

अटल पूर्णांक bpf_object__process_kconfig_line(काष्ठा bpf_object *obj,
					    अक्षर *buf, व्योम *data)
अणु
	काष्ठा बाह्य_desc *ext;
	अक्षर *sep, *value;
	पूर्णांक len, err = 0;
	व्योम *ext_val;
	__u64 num;

	अगर (म_भेदन(buf, "CONFIG_", 7))
		वापस 0;

	sep = म_अक्षर(buf, '=');
	अगर (!sep) अणु
		pr_warn("failed to parse '%s': no separator\n", buf);
		वापस -EINVAL;
	पूर्ण

	/* Trim ending '\n' */
	len = म_माप(buf);
	अगर (buf[len - 1] == '\n')
		buf[len - 1] = '\0';
	/* Split on '=' and ensure that a value is present. */
	*sep = '\0';
	अगर (!sep[1]) अणु
		*sep = '=';
		pr_warn("failed to parse '%s': no value\n", buf);
		वापस -EINVAL;
	पूर्ण

	ext = find_बाह्य_by_name(obj, buf);
	अगर (!ext || ext->is_set)
		वापस 0;

	ext_val = data + ext->kcfg.data_off;
	value = sep + 1;

	चयन (*value) अणु
	हाल 'y': case 'n': case 'm':
		err = set_kcfg_value_tri(ext, ext_val, *value);
		अवरोध;
	हाल '"':
		err = set_kcfg_value_str(ext, ext_val, value);
		अवरोध;
	शेष:
		/* assume पूर्णांकeger */
		err = parse_u64(value, &num);
		अगर (err) अणु
			pr_warn("extern (kcfg) %s=%s should be integer\n",
				ext->name, value);
			वापस err;
		पूर्ण
		err = set_kcfg_value_num(ext, ext_val, num);
		अवरोध;
	पूर्ण
	अगर (err)
		वापस err;
	pr_debug("extern (kcfg) %s=%s\n", ext->name, value);
	वापस 0;
पूर्ण

अटल पूर्णांक bpf_object__पढ़ो_kconfig_file(काष्ठा bpf_object *obj, व्योम *data)
अणु
	अक्षर buf[PATH_MAX];
	काष्ठा utsname uts;
	पूर्णांक len, err = 0;
	gzFile file;

	uname(&uts);
	len = snम_लिखो(buf, PATH_MAX, "/boot/config-%s", uts.release);
	अगर (len < 0)
		वापस -EINVAL;
	अन्यथा अगर (len >= PATH_MAX)
		वापस -ENAMETOOLONG;

	/* gzखोलो also accepts uncompressed files. */
	file = gzखोलो(buf, "r");
	अगर (!file)
		file = gzखोलो("/proc/config.gz", "r");

	अगर (!file) अणु
		pr_warn("failed to open system Kconfig\n");
		वापस -ENOENT;
	पूर्ण

	जबतक (gzमाला_लो(file, buf, माप(buf))) अणु
		err = bpf_object__process_kconfig_line(obj, buf, data);
		अगर (err) अणु
			pr_warn("error parsing system Kconfig line '%s': %d\n",
				buf, err);
			जाओ out;
		पूर्ण
	पूर्ण

out:
	gzबंद(file);
	वापस err;
पूर्ण

अटल पूर्णांक bpf_object__पढ़ो_kconfig_mem(काष्ठा bpf_object *obj,
					स्थिर अक्षर *config, व्योम *data)
अणु
	अक्षर buf[PATH_MAX];
	पूर्णांक err = 0;
	खाता *file;

	file = fmemखोलो((व्योम *)config, म_माप(config), "r");
	अगर (!file) अणु
		err = -त्रुटि_सं;
		pr_warn("failed to open in-memory Kconfig: %d\n", err);
		वापस err;
	पूर्ण

	जबतक (ख_माला_लो(buf, माप(buf), file)) अणु
		err = bpf_object__process_kconfig_line(obj, buf, data);
		अगर (err) अणु
			pr_warn("error parsing in-memory Kconfig line '%s': %d\n",
				buf, err);
			अवरोध;
		पूर्ण
	पूर्ण

	ख_बंद(file);
	वापस err;
पूर्ण

अटल पूर्णांक bpf_object__init_kconfig_map(काष्ठा bpf_object *obj)
अणु
	काष्ठा बाह्य_desc *last_ext = शून्य, *ext;
	माप_प्रकार map_sz;
	पूर्णांक i, err;

	क्रम (i = 0; i < obj->nr_बाह्य; i++) अणु
		ext = &obj->बाह्यs[i];
		अगर (ext->type == EXT_KCFG)
			last_ext = ext;
	पूर्ण

	अगर (!last_ext)
		वापस 0;

	map_sz = last_ext->kcfg.data_off + last_ext->kcfg.sz;
	err = bpf_object__init_पूर्णांकernal_map(obj, LIBBPF_MAP_KCONFIG,
					    obj->efile.symbols_shndx,
					    शून्य, map_sz);
	अगर (err)
		वापस err;

	obj->kconfig_map_idx = obj->nr_maps - 1;

	वापस 0;
पूर्ण

अटल पूर्णांक bpf_object__init_user_maps(काष्ठा bpf_object *obj, bool strict)
अणु
	Elf_Data *symbols = obj->efile.symbols;
	पूर्णांक i, map_def_sz = 0, nr_maps = 0, nr_syms;
	Elf_Data *data = शून्य;
	Elf_Scn *scn;

	अगर (obj->efile.maps_shndx < 0)
		वापस 0;

	अगर (!symbols)
		वापस -EINVAL;


	scn = elf_sec_by_idx(obj, obj->efile.maps_shndx);
	data = elf_sec_data(obj, scn);
	अगर (!scn || !data) अणु
		pr_warn("elf: failed to get legacy map definitions for %s\n",
			obj->path);
		वापस -EINVAL;
	पूर्ण

	/*
	 * Count number of maps. Each map has a name.
	 * Array of maps is not supported: only the first element is
	 * considered.
	 *
	 * TODO: Detect array of map and report error.
	 */
	nr_syms = symbols->d_size / माप(GElf_Sym);
	क्रम (i = 0; i < nr_syms; i++) अणु
		GElf_Sym sym;

		अगर (!gelf_माला_लोym(symbols, i, &sym))
			जारी;
		अगर (sym.st_shndx != obj->efile.maps_shndx)
			जारी;
		nr_maps++;
	पूर्ण
	/* Assume equally sized map definitions */
	pr_debug("elf: found %d legacy map definitions (%zd bytes) in %s\n",
		 nr_maps, data->d_size, obj->path);

	अगर (!data->d_size || nr_maps == 0 || (data->d_size % nr_maps) != 0) अणु
		pr_warn("elf: unable to determine legacy map definition size in %s\n",
			obj->path);
		वापस -EINVAL;
	पूर्ण
	map_def_sz = data->d_size / nr_maps;

	/* Fill obj->maps using data in "maps" section.  */
	क्रम (i = 0; i < nr_syms; i++) अणु
		GElf_Sym sym;
		स्थिर अक्षर *map_name;
		काष्ठा bpf_map_def *def;
		काष्ठा bpf_map *map;

		अगर (!gelf_माला_लोym(symbols, i, &sym))
			जारी;
		अगर (sym.st_shndx != obj->efile.maps_shndx)
			जारी;

		map = bpf_object__add_map(obj);
		अगर (IS_ERR(map))
			वापस PTR_ERR(map);

		map_name = elf_sym_str(obj, sym.st_name);
		अगर (!map_name) अणु
			pr_warn("failed to get map #%d name sym string for obj %s\n",
				i, obj->path);
			वापस -LIBBPF_ERRNO__FORMAT;
		पूर्ण

		map->libbpf_type = LIBBPF_MAP_UNSPEC;
		map->sec_idx = sym.st_shndx;
		map->sec_offset = sym.st_value;
		pr_debug("map '%s' (legacy): at sec_idx %d, offset %zu.\n",
			 map_name, map->sec_idx, map->sec_offset);
		अगर (sym.st_value + map_def_sz > data->d_size) अणु
			pr_warn("corrupted maps section in %s: last map \"%s\" too small\n",
				obj->path, map_name);
			वापस -EINVAL;
		पूर्ण

		map->name = strdup(map_name);
		अगर (!map->name) अणु
			pr_warn("failed to alloc map name\n");
			वापस -ENOMEM;
		पूर्ण
		pr_debug("map %d is \"%s\"\n", i, map->name);
		def = (काष्ठा bpf_map_def *)(data->d_buf + sym.st_value);
		/*
		 * If the definition of the map in the object file fits in
		 * bpf_map_def, copy it.  Any extra fields in our version
		 * of bpf_map_def will शेष to zero as a result of the
		 * सुस्मृति above.
		 */
		अगर (map_def_sz <= माप(काष्ठा bpf_map_def)) अणु
			स_नकल(&map->def, def, map_def_sz);
		पूर्ण अन्यथा अणु
			/*
			 * Here the map काष्ठाure being पढ़ो is bigger than what
			 * we expect, truncate अगर the excess bits are all zero.
			 * If they are not zero, reject this map as
			 * incompatible.
			 */
			अक्षर *b;

			क्रम (b = ((अक्षर *)def) + माप(काष्ठा bpf_map_def);
			     b < ((अक्षर *)def) + map_def_sz; b++) अणु
				अगर (*b != 0) अणु
					pr_warn("maps section in %s: \"%s\" has unrecognized, non-zero options\n",
						obj->path, map_name);
					अगर (strict)
						वापस -EINVAL;
				पूर्ण
			पूर्ण
			स_नकल(&map->def, def, माप(काष्ठा bpf_map_def));
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

स्थिर काष्ठा btf_type *
skip_mods_and_प्रकारs(स्थिर काष्ठा btf *btf, __u32 id, __u32 *res_id)
अणु
	स्थिर काष्ठा btf_type *t = btf__type_by_id(btf, id);

	अगर (res_id)
		*res_id = id;

	जबतक (btf_is_mod(t) || btf_is_प्रकार(t)) अणु
		अगर (res_id)
			*res_id = t->type;
		t = btf__type_by_id(btf, t->type);
	पूर्ण

	वापस t;
पूर्ण

अटल स्थिर काष्ठा btf_type *
resolve_func_ptr(स्थिर काष्ठा btf *btf, __u32 id, __u32 *res_id)
अणु
	स्थिर काष्ठा btf_type *t;

	t = skip_mods_and_प्रकारs(btf, id, शून्य);
	अगर (!btf_is_ptr(t))
		वापस शून्य;

	t = skip_mods_and_प्रकारs(btf, t->type, res_id);

	वापस btf_is_func_proto(t) ? t : शून्य;
पूर्ण

अटल स्थिर अक्षर *__btf_kind_str(__u16 kind)
अणु
	चयन (kind) अणु
	हाल BTF_KIND_UNKN: वापस "void";
	हाल BTF_KIND_INT: वापस "int";
	हाल BTF_KIND_PTR: वापस "ptr";
	हाल BTF_KIND_ARRAY: वापस "array";
	हाल BTF_KIND_STRUCT: वापस "struct";
	हाल BTF_KIND_UNION: वापस "union";
	हाल BTF_KIND_ENUM: वापस "enum";
	हाल BTF_KIND_FWD: वापस "fwd";
	हाल BTF_KIND_TYPEDEF: वापस "typedef";
	हाल BTF_KIND_VOLATILE: वापस "volatile";
	हाल BTF_KIND_CONST: वापस "const";
	हाल BTF_KIND_RESTRICT: वापस "restrict";
	हाल BTF_KIND_FUNC: वापस "func";
	हाल BTF_KIND_FUNC_PROTO: वापस "func_proto";
	हाल BTF_KIND_VAR: वापस "var";
	हाल BTF_KIND_DATASEC: वापस "datasec";
	हाल BTF_KIND_FLOAT: वापस "float";
	शेष: वापस "unknown";
	पूर्ण
पूर्ण

स्थिर अक्षर *btf_kind_str(स्थिर काष्ठा btf_type *t)
अणु
	वापस __btf_kind_str(btf_kind(t));
पूर्ण

/*
 * Fetch पूर्णांकeger attribute of BTF map definition. Such attributes are
 * represented using a poपूर्णांकer to an array, in which dimensionality of array
 * encodes specअगरied पूर्णांकeger value. E.g., पूर्णांक (*type)[BPF_MAP_TYPE_ARRAY];
 * encodes `type => BPF_MAP_TYPE_ARRAY` key/value pair completely using BTF
 * type definition, जबतक using only माप(व्योम *) space in ELF data section.
 */
अटल bool get_map_field_पूर्णांक(स्थिर अक्षर *map_name, स्थिर काष्ठा btf *btf,
			      स्थिर काष्ठा btf_member *m, __u32 *res)
अणु
	स्थिर काष्ठा btf_type *t = skip_mods_and_प्रकारs(btf, m->type, शून्य);
	स्थिर अक्षर *name = btf__name_by_offset(btf, m->name_off);
	स्थिर काष्ठा btf_array *arr_info;
	स्थिर काष्ठा btf_type *arr_t;

	अगर (!btf_is_ptr(t)) अणु
		pr_warn("map '%s': attr '%s': expected PTR, got %s.\n",
			map_name, name, btf_kind_str(t));
		वापस false;
	पूर्ण

	arr_t = btf__type_by_id(btf, t->type);
	अगर (!arr_t) अणु
		pr_warn("map '%s': attr '%s': type [%u] not found.\n",
			map_name, name, t->type);
		वापस false;
	पूर्ण
	अगर (!btf_is_array(arr_t)) अणु
		pr_warn("map '%s': attr '%s': expected ARRAY, got %s.\n",
			map_name, name, btf_kind_str(arr_t));
		वापस false;
	पूर्ण
	arr_info = btf_array(arr_t);
	*res = arr_info->nelems;
	वापस true;
पूर्ण

अटल पूर्णांक build_map_pin_path(काष्ठा bpf_map *map, स्थिर अक्षर *path)
अणु
	अक्षर buf[PATH_MAX];
	पूर्णांक len;

	अगर (!path)
		path = "/sys/fs/bpf";

	len = snम_लिखो(buf, PATH_MAX, "%s/%s", path, bpf_map__name(map));
	अगर (len < 0)
		वापस -EINVAL;
	अन्यथा अगर (len >= PATH_MAX)
		वापस -ENAMETOOLONG;

	वापस bpf_map__set_pin_path(map, buf);
पूर्ण

पूर्णांक parse_btf_map_def(स्थिर अक्षर *map_name, काष्ठा btf *btf,
		      स्थिर काष्ठा btf_type *def_t, bool strict,
		      काष्ठा btf_map_def *map_def, काष्ठा btf_map_def *inner_def)
अणु
	स्थिर काष्ठा btf_type *t;
	स्थिर काष्ठा btf_member *m;
	bool is_inner = inner_def == शून्य;
	पूर्णांक vlen, i;

	vlen = btf_vlen(def_t);
	m = btf_members(def_t);
	क्रम (i = 0; i < vlen; i++, m++) अणु
		स्थिर अक्षर *name = btf__name_by_offset(btf, m->name_off);

		अगर (!name) अणु
			pr_warn("map '%s': invalid field #%d.\n", map_name, i);
			वापस -EINVAL;
		पूर्ण
		अगर (म_भेद(name, "type") == 0) अणु
			अगर (!get_map_field_पूर्णांक(map_name, btf, m, &map_def->map_type))
				वापस -EINVAL;
			map_def->parts |= MAP_DEF_MAP_TYPE;
		पूर्ण अन्यथा अगर (म_भेद(name, "max_entries") == 0) अणु
			अगर (!get_map_field_पूर्णांक(map_name, btf, m, &map_def->max_entries))
				वापस -EINVAL;
			map_def->parts |= MAP_DEF_MAX_ENTRIES;
		पूर्ण अन्यथा अगर (म_भेद(name, "map_flags") == 0) अणु
			अगर (!get_map_field_पूर्णांक(map_name, btf, m, &map_def->map_flags))
				वापस -EINVAL;
			map_def->parts |= MAP_DEF_MAP_FLAGS;
		पूर्ण अन्यथा अगर (म_भेद(name, "numa_node") == 0) अणु
			अगर (!get_map_field_पूर्णांक(map_name, btf, m, &map_def->numa_node))
				वापस -EINVAL;
			map_def->parts |= MAP_DEF_NUMA_NODE;
		पूर्ण अन्यथा अगर (म_भेद(name, "key_size") == 0) अणु
			__u32 sz;

			अगर (!get_map_field_पूर्णांक(map_name, btf, m, &sz))
				वापस -EINVAL;
			अगर (map_def->key_size && map_def->key_size != sz) अणु
				pr_warn("map '%s': conflicting key size %u != %u.\n",
					map_name, map_def->key_size, sz);
				वापस -EINVAL;
			पूर्ण
			map_def->key_size = sz;
			map_def->parts |= MAP_DEF_KEY_SIZE;
		पूर्ण अन्यथा अगर (म_भेद(name, "key") == 0) अणु
			__s64 sz;

			t = btf__type_by_id(btf, m->type);
			अगर (!t) अणु
				pr_warn("map '%s': key type [%d] not found.\n",
					map_name, m->type);
				वापस -EINVAL;
			पूर्ण
			अगर (!btf_is_ptr(t)) अणु
				pr_warn("map '%s': key spec is not PTR: %s.\n",
					map_name, btf_kind_str(t));
				वापस -EINVAL;
			पूर्ण
			sz = btf__resolve_size(btf, t->type);
			अगर (sz < 0) अणु
				pr_warn("map '%s': can't determine key size for type [%u]: %zd.\n",
					map_name, t->type, (sमाप_प्रकार)sz);
				वापस sz;
			पूर्ण
			अगर (map_def->key_size && map_def->key_size != sz) अणु
				pr_warn("map '%s': conflicting key size %u != %zd.\n",
					map_name, map_def->key_size, (sमाप_प्रकार)sz);
				वापस -EINVAL;
			पूर्ण
			map_def->key_size = sz;
			map_def->key_type_id = t->type;
			map_def->parts |= MAP_DEF_KEY_SIZE | MAP_DEF_KEY_TYPE;
		पूर्ण अन्यथा अगर (म_भेद(name, "value_size") == 0) अणु
			__u32 sz;

			अगर (!get_map_field_पूर्णांक(map_name, btf, m, &sz))
				वापस -EINVAL;
			अगर (map_def->value_size && map_def->value_size != sz) अणु
				pr_warn("map '%s': conflicting value size %u != %u.\n",
					map_name, map_def->value_size, sz);
				वापस -EINVAL;
			पूर्ण
			map_def->value_size = sz;
			map_def->parts |= MAP_DEF_VALUE_SIZE;
		पूर्ण अन्यथा अगर (म_भेद(name, "value") == 0) अणु
			__s64 sz;

			t = btf__type_by_id(btf, m->type);
			अगर (!t) अणु
				pr_warn("map '%s': value type [%d] not found.\n",
					map_name, m->type);
				वापस -EINVAL;
			पूर्ण
			अगर (!btf_is_ptr(t)) अणु
				pr_warn("map '%s': value spec is not PTR: %s.\n",
					map_name, btf_kind_str(t));
				वापस -EINVAL;
			पूर्ण
			sz = btf__resolve_size(btf, t->type);
			अगर (sz < 0) अणु
				pr_warn("map '%s': can't determine value size for type [%u]: %zd.\n",
					map_name, t->type, (sमाप_प्रकार)sz);
				वापस sz;
			पूर्ण
			अगर (map_def->value_size && map_def->value_size != sz) अणु
				pr_warn("map '%s': conflicting value size %u != %zd.\n",
					map_name, map_def->value_size, (sमाप_प्रकार)sz);
				वापस -EINVAL;
			पूर्ण
			map_def->value_size = sz;
			map_def->value_type_id = t->type;
			map_def->parts |= MAP_DEF_VALUE_SIZE | MAP_DEF_VALUE_TYPE;
		पूर्ण
		अन्यथा अगर (म_भेद(name, "values") == 0) अणु
			अक्षर inner_map_name[128];
			पूर्णांक err;

			अगर (is_inner) अणु
				pr_warn("map '%s': multi-level inner maps not supported.\n",
					map_name);
				वापस -ENOTSUP;
			पूर्ण
			अगर (i != vlen - 1) अणु
				pr_warn("map '%s': '%s' member should be last.\n",
					map_name, name);
				वापस -EINVAL;
			पूर्ण
			अगर (!bpf_map_type__is_map_in_map(map_def->map_type)) अणु
				pr_warn("map '%s': should be map-in-map.\n",
					map_name);
				वापस -ENOTSUP;
			पूर्ण
			अगर (map_def->value_size && map_def->value_size != 4) अणु
				pr_warn("map '%s': conflicting value size %u != 4.\n",
					map_name, map_def->value_size);
				वापस -EINVAL;
			पूर्ण
			map_def->value_size = 4;
			t = btf__type_by_id(btf, m->type);
			अगर (!t) अणु
				pr_warn("map '%s': map-in-map inner type [%d] not found.\n",
					map_name, m->type);
				वापस -EINVAL;
			पूर्ण
			अगर (!btf_is_array(t) || btf_array(t)->nelems) अणु
				pr_warn("map '%s': map-in-map inner spec is not a zero-sized array.\n",
					map_name);
				वापस -EINVAL;
			पूर्ण
			t = skip_mods_and_प्रकारs(btf, btf_array(t)->type, शून्य);
			अगर (!btf_is_ptr(t)) अणु
				pr_warn("map '%s': map-in-map inner def is of unexpected kind %s.\n",
					map_name, btf_kind_str(t));
				वापस -EINVAL;
			पूर्ण
			t = skip_mods_and_प्रकारs(btf, t->type, शून्य);
			अगर (!btf_is_काष्ठा(t)) अणु
				pr_warn("map '%s': map-in-map inner def is of unexpected kind %s.\n",
					map_name, btf_kind_str(t));
				वापस -EINVAL;
			पूर्ण

			snम_लिखो(inner_map_name, माप(inner_map_name), "%s.inner", map_name);
			err = parse_btf_map_def(inner_map_name, btf, t, strict, inner_def, शून्य);
			अगर (err)
				वापस err;

			map_def->parts |= MAP_DEF_INNER_MAP;
		पूर्ण अन्यथा अगर (म_भेद(name, "pinning") == 0) अणु
			__u32 val;

			अगर (is_inner) अणु
				pr_warn("map '%s': inner def can't be pinned.\n", map_name);
				वापस -EINVAL;
			पूर्ण
			अगर (!get_map_field_पूर्णांक(map_name, btf, m, &val))
				वापस -EINVAL;
			अगर (val != LIBBPF_PIN_NONE && val != LIBBPF_PIN_BY_NAME) अणु
				pr_warn("map '%s': invalid pinning value %u.\n",
					map_name, val);
				वापस -EINVAL;
			पूर्ण
			map_def->pinning = val;
			map_def->parts |= MAP_DEF_PINNING;
		पूर्ण अन्यथा अणु
			अगर (strict) अणु
				pr_warn("map '%s': unknown field '%s'.\n", map_name, name);
				वापस -ENOTSUP;
			पूर्ण
			pr_debug("map '%s': ignoring unknown field '%s'.\n", map_name, name);
		पूर्ण
	पूर्ण

	अगर (map_def->map_type == BPF_MAP_TYPE_UNSPEC) अणु
		pr_warn("map '%s': map type isn't specified.\n", map_name);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम fill_map_from_def(काष्ठा bpf_map *map, स्थिर काष्ठा btf_map_def *def)
अणु
	map->def.type = def->map_type;
	map->def.key_size = def->key_size;
	map->def.value_size = def->value_size;
	map->def.max_entries = def->max_entries;
	map->def.map_flags = def->map_flags;

	map->numa_node = def->numa_node;
	map->btf_key_type_id = def->key_type_id;
	map->btf_value_type_id = def->value_type_id;

	अगर (def->parts & MAP_DEF_MAP_TYPE)
		pr_debug("map '%s': found type = %u.\n", map->name, def->map_type);

	अगर (def->parts & MAP_DEF_KEY_TYPE)
		pr_debug("map '%s': found key [%u], sz = %u.\n",
			 map->name, def->key_type_id, def->key_size);
	अन्यथा अगर (def->parts & MAP_DEF_KEY_SIZE)
		pr_debug("map '%s': found key_size = %u.\n", map->name, def->key_size);

	अगर (def->parts & MAP_DEF_VALUE_TYPE)
		pr_debug("map '%s': found value [%u], sz = %u.\n",
			 map->name, def->value_type_id, def->value_size);
	अन्यथा अगर (def->parts & MAP_DEF_VALUE_SIZE)
		pr_debug("map '%s': found value_size = %u.\n", map->name, def->value_size);

	अगर (def->parts & MAP_DEF_MAX_ENTRIES)
		pr_debug("map '%s': found max_entries = %u.\n", map->name, def->max_entries);
	अगर (def->parts & MAP_DEF_MAP_FLAGS)
		pr_debug("map '%s': found map_flags = %u.\n", map->name, def->map_flags);
	अगर (def->parts & MAP_DEF_PINNING)
		pr_debug("map '%s': found pinning = %u.\n", map->name, def->pinning);
	अगर (def->parts & MAP_DEF_NUMA_NODE)
		pr_debug("map '%s': found numa_node = %u.\n", map->name, def->numa_node);

	अगर (def->parts & MAP_DEF_INNER_MAP)
		pr_debug("map '%s': found inner map definition.\n", map->name);
पूर्ण

अटल पूर्णांक bpf_object__init_user_btf_map(काष्ठा bpf_object *obj,
					 स्थिर काष्ठा btf_type *sec,
					 पूर्णांक var_idx, पूर्णांक sec_idx,
					 स्थिर Elf_Data *data, bool strict,
					 स्थिर अक्षर *pin_root_path)
अणु
	काष्ठा btf_map_def map_def = अणुपूर्ण, inner_def = अणुपूर्ण;
	स्थिर काष्ठा btf_type *var, *def;
	स्थिर काष्ठा btf_var_secinfo *vi;
	स्थिर काष्ठा btf_var *var_extra;
	स्थिर अक्षर *map_name;
	काष्ठा bpf_map *map;
	पूर्णांक err;

	vi = btf_var_secinfos(sec) + var_idx;
	var = btf__type_by_id(obj->btf, vi->type);
	var_extra = btf_var(var);
	map_name = btf__name_by_offset(obj->btf, var->name_off);

	अगर (map_name == शून्य || map_name[0] == '\0') अणु
		pr_warn("map #%d: empty name.\n", var_idx);
		वापस -EINVAL;
	पूर्ण
	अगर ((__u64)vi->offset + vi->size > data->d_size) अणु
		pr_warn("map '%s' BTF data is corrupted.\n", map_name);
		वापस -EINVAL;
	पूर्ण
	अगर (!btf_is_var(var)) अणु
		pr_warn("map '%s': unexpected var kind %s.\n",
			map_name, btf_kind_str(var));
		वापस -EINVAL;
	पूर्ण
	अगर (var_extra->linkage != BTF_VAR_GLOBAL_ALLOCATED &&
	    var_extra->linkage != BTF_VAR_STATIC) अणु
		pr_warn("map '%s': unsupported var linkage %u.\n",
			map_name, var_extra->linkage);
		वापस -EOPNOTSUPP;
	पूर्ण

	def = skip_mods_and_प्रकारs(obj->btf, var->type, शून्य);
	अगर (!btf_is_काष्ठा(def)) अणु
		pr_warn("map '%s': unexpected def kind %s.\n",
			map_name, btf_kind_str(var));
		वापस -EINVAL;
	पूर्ण
	अगर (def->size > vi->size) अणु
		pr_warn("map '%s': invalid def size.\n", map_name);
		वापस -EINVAL;
	पूर्ण

	map = bpf_object__add_map(obj);
	अगर (IS_ERR(map))
		वापस PTR_ERR(map);
	map->name = strdup(map_name);
	अगर (!map->name) अणु
		pr_warn("map '%s': failed to alloc map name.\n", map_name);
		वापस -ENOMEM;
	पूर्ण
	map->libbpf_type = LIBBPF_MAP_UNSPEC;
	map->def.type = BPF_MAP_TYPE_UNSPEC;
	map->sec_idx = sec_idx;
	map->sec_offset = vi->offset;
	map->btf_var_idx = var_idx;
	pr_debug("map '%s': at sec_idx %d, offset %zu.\n",
		 map_name, map->sec_idx, map->sec_offset);

	err = parse_btf_map_def(map->name, obj->btf, def, strict, &map_def, &inner_def);
	अगर (err)
		वापस err;

	fill_map_from_def(map, &map_def);

	अगर (map_def.pinning == LIBBPF_PIN_BY_NAME) अणु
		err = build_map_pin_path(map, pin_root_path);
		अगर (err) अणु
			pr_warn("map '%s': couldn't build pin path.\n", map->name);
			वापस err;
		पूर्ण
	पूर्ण

	अगर (map_def.parts & MAP_DEF_INNER_MAP) अणु
		map->inner_map = सुस्मृति(1, माप(*map->inner_map));
		अगर (!map->inner_map)
			वापस -ENOMEM;
		map->inner_map->fd = -1;
		map->inner_map->sec_idx = sec_idx;
		map->inner_map->name = दो_स्मृति(म_माप(map_name) + माप(".inner") + 1);
		अगर (!map->inner_map->name)
			वापस -ENOMEM;
		प्र_लिखो(map->inner_map->name, "%s.inner", map_name);

		fill_map_from_def(map->inner_map, &inner_def);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bpf_object__init_user_btf_maps(काष्ठा bpf_object *obj, bool strict,
					  स्थिर अक्षर *pin_root_path)
अणु
	स्थिर काष्ठा btf_type *sec = शून्य;
	पूर्णांक nr_types, i, vlen, err;
	स्थिर काष्ठा btf_type *t;
	स्थिर अक्षर *name;
	Elf_Data *data;
	Elf_Scn *scn;

	अगर (obj->efile.btf_maps_shndx < 0)
		वापस 0;

	scn = elf_sec_by_idx(obj, obj->efile.btf_maps_shndx);
	data = elf_sec_data(obj, scn);
	अगर (!scn || !data) अणु
		pr_warn("elf: failed to get %s map definitions for %s\n",
			MAPS_ELF_SEC, obj->path);
		वापस -EINVAL;
	पूर्ण

	nr_types = btf__get_nr_types(obj->btf);
	क्रम (i = 1; i <= nr_types; i++) अणु
		t = btf__type_by_id(obj->btf, i);
		अगर (!btf_is_datasec(t))
			जारी;
		name = btf__name_by_offset(obj->btf, t->name_off);
		अगर (म_भेद(name, MAPS_ELF_SEC) == 0) अणु
			sec = t;
			obj->efile.btf_maps_sec_btf_id = i;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!sec) अणु
		pr_warn("DATASEC '%s' not found.\n", MAPS_ELF_SEC);
		वापस -ENOENT;
	पूर्ण

	vlen = btf_vlen(sec);
	क्रम (i = 0; i < vlen; i++) अणु
		err = bpf_object__init_user_btf_map(obj, sec, i,
						    obj->efile.btf_maps_shndx,
						    data, strict,
						    pin_root_path);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bpf_object__init_maps(काष्ठा bpf_object *obj,
				 स्थिर काष्ठा bpf_object_खोलो_opts *opts)
अणु
	स्थिर अक्षर *pin_root_path;
	bool strict;
	पूर्णांक err;

	strict = !OPTS_GET(opts, relaxed_maps, false);
	pin_root_path = OPTS_GET(opts, pin_root_path, शून्य);

	err = bpf_object__init_user_maps(obj, strict);
	err = err ?: bpf_object__init_user_btf_maps(obj, strict, pin_root_path);
	err = err ?: bpf_object__init_global_data_maps(obj);
	err = err ?: bpf_object__init_kconfig_map(obj);
	err = err ?: bpf_object__init_काष्ठा_ops_maps(obj);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल bool section_have_execinstr(काष्ठा bpf_object *obj, पूर्णांक idx)
अणु
	GElf_Shdr sh;

	अगर (elf_sec_hdr(obj, elf_sec_by_idx(obj, idx), &sh))
		वापस false;

	वापस sh.sh_flags & SHF_EXECINSTR;
पूर्ण

अटल bool btf_needs_sanitization(काष्ठा bpf_object *obj)
अणु
	bool has_func_global = kernel_supports(FEAT_BTF_GLOBAL_FUNC);
	bool has_datasec = kernel_supports(FEAT_BTF_DATASEC);
	bool has_भग्न = kernel_supports(FEAT_BTF_FLOAT);
	bool has_func = kernel_supports(FEAT_BTF_FUNC);

	वापस !has_func || !has_datasec || !has_func_global || !has_भग्न;
पूर्ण

अटल व्योम bpf_object__sanitize_btf(काष्ठा bpf_object *obj, काष्ठा btf *btf)
अणु
	bool has_func_global = kernel_supports(FEAT_BTF_GLOBAL_FUNC);
	bool has_datasec = kernel_supports(FEAT_BTF_DATASEC);
	bool has_भग्न = kernel_supports(FEAT_BTF_FLOAT);
	bool has_func = kernel_supports(FEAT_BTF_FUNC);
	काष्ठा btf_type *t;
	पूर्णांक i, j, vlen;

	क्रम (i = 1; i <= btf__get_nr_types(btf); i++) अणु
		t = (काष्ठा btf_type *)btf__type_by_id(btf, i);

		अगर (!has_datasec && btf_is_var(t)) अणु
			/* replace VAR with INT */
			t->info = BTF_INFO_ENC(BTF_KIND_INT, 0, 0);
			/*
			 * using size = 1 is the safest choice, 4 will be too
			 * big and cause kernel BTF validation failure अगर
			 * original variable took less than 4 bytes
			 */
			t->size = 1;
			*(पूर्णांक *)(t + 1) = BTF_INT_ENC(0, 0, 8);
		पूर्ण अन्यथा अगर (!has_datasec && btf_is_datasec(t)) अणु
			/* replace DATASEC with STRUCT */
			स्थिर काष्ठा btf_var_secinfo *v = btf_var_secinfos(t);
			काष्ठा btf_member *m = btf_members(t);
			काष्ठा btf_type *vt;
			अक्षर *name;

			name = (अक्षर *)btf__name_by_offset(btf, t->name_off);
			जबतक (*name) अणु
				अगर (*name == '.')
					*name = '_';
				name++;
			पूर्ण

			vlen = btf_vlen(t);
			t->info = BTF_INFO_ENC(BTF_KIND_STRUCT, 0, vlen);
			क्रम (j = 0; j < vlen; j++, v++, m++) अणु
				/* order of field assignments is important */
				m->offset = v->offset * 8;
				m->type = v->type;
				/* preserve variable name as member name */
				vt = (व्योम *)btf__type_by_id(btf, v->type);
				m->name_off = vt->name_off;
			पूर्ण
		पूर्ण अन्यथा अगर (!has_func && btf_is_func_proto(t)) अणु
			/* replace FUNC_PROTO with ENUM */
			vlen = btf_vlen(t);
			t->info = BTF_INFO_ENC(BTF_KIND_ENUM, 0, vlen);
			t->size = माप(__u32); /* kernel enक्रमced */
		पूर्ण अन्यथा अगर (!has_func && btf_is_func(t)) अणु
			/* replace FUNC with TYPEDEF */
			t->info = BTF_INFO_ENC(BTF_KIND_TYPEDEF, 0, 0);
		पूर्ण अन्यथा अगर (!has_func_global && btf_is_func(t)) अणु
			/* replace BTF_FUNC_GLOBAL with BTF_FUNC_STATIC */
			t->info = BTF_INFO_ENC(BTF_KIND_FUNC, 0, 0);
		पूर्ण अन्यथा अगर (!has_भग्न && btf_is_भग्न(t)) अणु
			/* replace FLOAT with an equally-sized empty STRUCT;
			 * since C compilers करो not accept e.g. "float" as a
			 * valid काष्ठा name, make it anonymous
			 */
			t->name_off = 0;
			t->info = BTF_INFO_ENC(BTF_KIND_STRUCT, 0, 0);
		पूर्ण
	पूर्ण
पूर्ण

अटल bool libbpf_needs_btf(स्थिर काष्ठा bpf_object *obj)
अणु
	वापस obj->efile.btf_maps_shndx >= 0 ||
	       obj->efile.st_ops_shndx >= 0 ||
	       obj->nr_बाह्य > 0;
पूर्ण

अटल bool kernel_needs_btf(स्थिर काष्ठा bpf_object *obj)
अणु
	वापस obj->efile.st_ops_shndx >= 0;
पूर्ण

अटल पूर्णांक bpf_object__init_btf(काष्ठा bpf_object *obj,
				Elf_Data *btf_data,
				Elf_Data *btf_ext_data)
अणु
	पूर्णांक err = -ENOENT;

	अगर (btf_data) अणु
		obj->btf = btf__new(btf_data->d_buf, btf_data->d_size);
		अगर (IS_ERR(obj->btf)) अणु
			err = PTR_ERR(obj->btf);
			obj->btf = शून्य;
			pr_warn("Error loading ELF section %s: %d.\n",
				BTF_ELF_SEC, err);
			जाओ out;
		पूर्ण
		/* enक्रमce 8-byte poपूर्णांकers क्रम BPF-targeted BTFs */
		btf__set_poपूर्णांकer_size(obj->btf, 8);
		err = 0;
	पूर्ण
	अगर (btf_ext_data) अणु
		अगर (!obj->btf) अणु
			pr_debug("Ignore ELF section %s because its depending ELF section %s is not found.\n",
				 BTF_EXT_ELF_SEC, BTF_ELF_SEC);
			जाओ out;
		पूर्ण
		obj->btf_ext = btf_ext__new(btf_ext_data->d_buf,
					    btf_ext_data->d_size);
		अगर (IS_ERR(obj->btf_ext)) अणु
			pr_warn("Error loading ELF section %s: %ld. Ignored and continue.\n",
				BTF_EXT_ELF_SEC, PTR_ERR(obj->btf_ext));
			obj->btf_ext = शून्य;
			जाओ out;
		पूर्ण
	पूर्ण
out:
	अगर (err && libbpf_needs_btf(obj)) अणु
		pr_warn("BTF is required, but is missing or corrupted.\n");
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक bpf_object__finalize_btf(काष्ठा bpf_object *obj)
अणु
	पूर्णांक err;

	अगर (!obj->btf)
		वापस 0;

	err = btf__finalize_data(obj, obj->btf);
	अगर (err) अणु
		pr_warn("Error finalizing %s: %d.\n", BTF_ELF_SEC, err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool prog_needs_vmlinux_btf(काष्ठा bpf_program *prog)
अणु
	अगर (prog->type == BPF_PROG_TYPE_STRUCT_OPS ||
	    prog->type == BPF_PROG_TYPE_LSM)
		वापस true;

	/* BPF_PROG_TYPE_TRACING programs which करो not attach to other programs
	 * also need vmlinux BTF
	 */
	अगर (prog->type == BPF_PROG_TYPE_TRACING && !prog->attach_prog_fd)
		वापस true;

	वापस false;
पूर्ण

अटल bool obj_needs_vmlinux_btf(स्थिर काष्ठा bpf_object *obj)
अणु
	काष्ठा bpf_program *prog;
	पूर्णांक i;

	/* CO-RE relocations need kernel BTF */
	अगर (obj->btf_ext && obj->btf_ext->core_relo_info.len)
		वापस true;

	/* Support क्रम typed ksyms needs kernel BTF */
	क्रम (i = 0; i < obj->nr_बाह्य; i++) अणु
		स्थिर काष्ठा बाह्य_desc *ext;

		ext = &obj->बाह्यs[i];
		अगर (ext->type == EXT_KSYM && ext->ksym.type_id)
			वापस true;
	पूर्ण

	bpf_object__क्रम_each_program(prog, obj) अणु
		अगर (!prog->load)
			जारी;
		अगर (prog_needs_vmlinux_btf(prog))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक bpf_object__load_vmlinux_btf(काष्ठा bpf_object *obj, bool क्रमce)
अणु
	पूर्णांक err;

	/* btf_vmlinux could be loaded earlier */
	अगर (obj->btf_vmlinux)
		वापस 0;

	अगर (!क्रमce && !obj_needs_vmlinux_btf(obj))
		वापस 0;

	obj->btf_vmlinux = libbpf_find_kernel_btf();
	अगर (IS_ERR(obj->btf_vmlinux)) अणु
		err = PTR_ERR(obj->btf_vmlinux);
		pr_warn("Error loading vmlinux BTF: %d\n", err);
		obj->btf_vmlinux = शून्य;
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक bpf_object__sanitize_and_load_btf(काष्ठा bpf_object *obj)
अणु
	काष्ठा btf *kern_btf = obj->btf;
	bool btf_mandatory, sanitize;
	पूर्णांक i, err = 0;

	अगर (!obj->btf)
		वापस 0;

	अगर (!kernel_supports(FEAT_BTF)) अणु
		अगर (kernel_needs_btf(obj)) अणु
			err = -EOPNOTSUPP;
			जाओ report;
		पूर्ण
		pr_debug("Kernel doesn't support BTF, skipping uploading it.\n");
		वापस 0;
	पूर्ण

	/* Even though some subprogs are global/weak, user might prefer more
	 * permissive BPF verअगरication process that BPF verअगरier perक्रमms क्रम
	 * अटल functions, taking पूर्णांकo account more context from the caller
	 * functions. In such हाल, they need to mark such subprogs with
	 * __attribute__((visibility("hidden"))) and libbpf will adjust
	 * corresponding FUNC BTF type to be marked as अटल and trigger more
	 * involved BPF verअगरication process.
	 */
	क्रम (i = 0; i < obj->nr_programs; i++) अणु
		काष्ठा bpf_program *prog = &obj->programs[i];
		काष्ठा btf_type *t;
		स्थिर अक्षर *name;
		पूर्णांक j, n;

		अगर (!prog->mark_btf_अटल || !prog_is_subprog(obj, prog))
			जारी;

		n = btf__get_nr_types(obj->btf);
		क्रम (j = 1; j <= n; j++) अणु
			t = btf_type_by_id(obj->btf, j);
			अगर (!btf_is_func(t) || btf_func_linkage(t) != BTF_FUNC_GLOBAL)
				जारी;

			name = btf__str_by_offset(obj->btf, t->name_off);
			अगर (म_भेद(name, prog->name) != 0)
				जारी;

			t->info = btf_type_info(BTF_KIND_FUNC, BTF_FUNC_STATIC, 0);
			अवरोध;
		पूर्ण
	पूर्ण

	sanitize = btf_needs_sanitization(obj);
	अगर (sanitize) अणु
		स्थिर व्योम *raw_data;
		__u32 sz;

		/* clone BTF to sanitize a copy and leave the original पूर्णांकact */
		raw_data = btf__get_raw_data(obj->btf, &sz);
		kern_btf = btf__new(raw_data, sz);
		अगर (IS_ERR(kern_btf))
			वापस PTR_ERR(kern_btf);

		/* enक्रमce 8-byte poपूर्णांकers क्रम BPF-targeted BTFs */
		btf__set_poपूर्णांकer_size(obj->btf, 8);
		bpf_object__sanitize_btf(obj, kern_btf);
	पूर्ण

	err = btf__load(kern_btf);
	अगर (sanitize) अणु
		अगर (!err) अणु
			/* move fd to libbpf's BTF */
			btf__set_fd(obj->btf, btf__fd(kern_btf));
			btf__set_fd(kern_btf, -1);
		पूर्ण
		btf__मुक्त(kern_btf);
	पूर्ण
report:
	अगर (err) अणु
		btf_mandatory = kernel_needs_btf(obj);
		pr_warn("Error loading .BTF into kernel: %d. %s\n", err,
			btf_mandatory ? "BTF is mandatory, can't proceed."
				      : "BTF is optional, ignoring.");
		अगर (!btf_mandatory)
			err = 0;
	पूर्ण
	वापस err;
पूर्ण

अटल स्थिर अक्षर *elf_sym_str(स्थिर काष्ठा bpf_object *obj, माप_प्रकार off)
अणु
	स्थिर अक्षर *name;

	name = elf_strptr(obj->efile.elf, obj->efile.strtabidx, off);
	अगर (!name) अणु
		pr_warn("elf: failed to get section name string at offset %zu from %s: %s\n",
			off, obj->path, elf_errmsg(-1));
		वापस शून्य;
	पूर्ण

	वापस name;
पूर्ण

अटल स्थिर अक्षर *elf_sec_str(स्थिर काष्ठा bpf_object *obj, माप_प्रकार off)
अणु
	स्थिर अक्षर *name;

	name = elf_strptr(obj->efile.elf, obj->efile.shstrndx, off);
	अगर (!name) अणु
		pr_warn("elf: failed to get section name string at offset %zu from %s: %s\n",
			off, obj->path, elf_errmsg(-1));
		वापस शून्य;
	पूर्ण

	वापस name;
पूर्ण

अटल Elf_Scn *elf_sec_by_idx(स्थिर काष्ठा bpf_object *obj, माप_प्रकार idx)
अणु
	Elf_Scn *scn;

	scn = elf_माला_लोcn(obj->efile.elf, idx);
	अगर (!scn) अणु
		pr_warn("elf: failed to get section(%zu) from %s: %s\n",
			idx, obj->path, elf_errmsg(-1));
		वापस शून्य;
	पूर्ण
	वापस scn;
पूर्ण

अटल Elf_Scn *elf_sec_by_name(स्थिर काष्ठा bpf_object *obj, स्थिर अक्षर *name)
अणु
	Elf_Scn *scn = शून्य;
	Elf *elf = obj->efile.elf;
	स्थिर अक्षर *sec_name;

	जबतक ((scn = elf_nextscn(elf, scn)) != शून्य) अणु
		sec_name = elf_sec_name(obj, scn);
		अगर (!sec_name)
			वापस शून्य;

		अगर (म_भेद(sec_name, name) != 0)
			जारी;

		वापस scn;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक elf_sec_hdr(स्थिर काष्ठा bpf_object *obj, Elf_Scn *scn, GElf_Shdr *hdr)
अणु
	अगर (!scn)
		वापस -EINVAL;

	अगर (gelf_माला_लोhdr(scn, hdr) != hdr) अणु
		pr_warn("elf: failed to get section(%zu) header from %s: %s\n",
			elf_ndxscn(scn), obj->path, elf_errmsg(-1));
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर अक्षर *elf_sec_name(स्थिर काष्ठा bpf_object *obj, Elf_Scn *scn)
अणु
	स्थिर अक्षर *name;
	GElf_Shdr sh;

	अगर (!scn)
		वापस शून्य;

	अगर (elf_sec_hdr(obj, scn, &sh))
		वापस शून्य;

	name = elf_sec_str(obj, sh.sh_name);
	अगर (!name) अणु
		pr_warn("elf: failed to get section(%zu) name from %s: %s\n",
			elf_ndxscn(scn), obj->path, elf_errmsg(-1));
		वापस शून्य;
	पूर्ण

	वापस name;
पूर्ण

अटल Elf_Data *elf_sec_data(स्थिर काष्ठा bpf_object *obj, Elf_Scn *scn)
अणु
	Elf_Data *data;

	अगर (!scn)
		वापस शून्य;

	data = elf_getdata(scn, 0);
	अगर (!data) अणु
		pr_warn("elf: failed to get section(%zu) %s data from %s: %s\n",
			elf_ndxscn(scn), elf_sec_name(obj, scn) ?: "<?>",
			obj->path, elf_errmsg(-1));
		वापस शून्य;
	पूर्ण

	वापस data;
पूर्ण

अटल bool is_sec_name_dwarf(स्थिर अक्षर *name)
अणु
	/* approximation, but the actual list is too दीर्घ */
	वापस म_भेदन(name, ".debug_", माप(".debug_") - 1) == 0;
पूर्ण

अटल bool ignore_elf_section(GElf_Shdr *hdr, स्थिर अक्षर *name)
अणु
	/* no special handling of .strtab */
	अगर (hdr->sh_type == SHT_STRTAB)
		वापस true;

	/* ignore .llvm_addrsig section as well */
	अगर (hdr->sh_type == SHT_LLVM_ADDRSIG)
		वापस true;

	/* no subprograms will lead to an empty .text section, ignore it */
	अगर (hdr->sh_type == SHT_PROGBITS && hdr->sh_size == 0 &&
	    म_भेद(name, ".text") == 0)
		वापस true;

	/* DWARF sections */
	अगर (is_sec_name_dwarf(name))
		वापस true;

	अगर (म_भेदन(name, ".rel", माप(".rel") - 1) == 0) अणु
		name += माप(".rel") - 1;
		/* DWARF section relocations */
		अगर (is_sec_name_dwarf(name))
			वापस true;

		/* .BTF and .BTF.ext करोn't need relocations */
		अगर (म_भेद(name, BTF_ELF_SEC) == 0 ||
		    म_भेद(name, BTF_EXT_ELF_SEC) == 0)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक cmp_progs(स्थिर व्योम *_a, स्थिर व्योम *_b)
अणु
	स्थिर काष्ठा bpf_program *a = _a;
	स्थिर काष्ठा bpf_program *b = _b;

	अगर (a->sec_idx != b->sec_idx)
		वापस a->sec_idx < b->sec_idx ? -1 : 1;

	/* sec_insn_off can't be the same within the section */
	वापस a->sec_insn_off < b->sec_insn_off ? -1 : 1;
पूर्ण

अटल पूर्णांक bpf_object__elf_collect(काष्ठा bpf_object *obj)
अणु
	Elf *elf = obj->efile.elf;
	Elf_Data *btf_ext_data = शून्य;
	Elf_Data *btf_data = शून्य;
	पूर्णांक idx = 0, err = 0;
	स्थिर अक्षर *name;
	Elf_Data *data;
	Elf_Scn *scn;
	GElf_Shdr sh;

	/* a bunch of ELF parsing functionality depends on processing symbols,
	 * so करो the first pass and find the symbol table
	 */
	scn = शून्य;
	जबतक ((scn = elf_nextscn(elf, scn)) != शून्य) अणु
		अगर (elf_sec_hdr(obj, scn, &sh))
			वापस -LIBBPF_ERRNO__FORMAT;

		अगर (sh.sh_type == SHT_SYMTAB) अणु
			अगर (obj->efile.symbols) अणु
				pr_warn("elf: multiple symbol tables in %s\n", obj->path);
				वापस -LIBBPF_ERRNO__FORMAT;
			पूर्ण

			data = elf_sec_data(obj, scn);
			अगर (!data)
				वापस -LIBBPF_ERRNO__FORMAT;

			obj->efile.symbols = data;
			obj->efile.symbols_shndx = elf_ndxscn(scn);
			obj->efile.strtabidx = sh.sh_link;
		पूर्ण
	पूर्ण

	scn = शून्य;
	जबतक ((scn = elf_nextscn(elf, scn)) != शून्य) अणु
		idx++;

		अगर (elf_sec_hdr(obj, scn, &sh))
			वापस -LIBBPF_ERRNO__FORMAT;

		name = elf_sec_str(obj, sh.sh_name);
		अगर (!name)
			वापस -LIBBPF_ERRNO__FORMAT;

		अगर (ignore_elf_section(&sh, name))
			जारी;

		data = elf_sec_data(obj, scn);
		अगर (!data)
			वापस -LIBBPF_ERRNO__FORMAT;

		pr_debug("elf: section(%d) %s, size %ld, link %d, flags %lx, type=%d\n",
			 idx, name, (अचिन्हित दीर्घ)data->d_size,
			 (पूर्णांक)sh.sh_link, (अचिन्हित दीर्घ)sh.sh_flags,
			 (पूर्णांक)sh.sh_type);

		अगर (म_भेद(name, "license") == 0) अणु
			err = bpf_object__init_license(obj, data->d_buf, data->d_size);
			अगर (err)
				वापस err;
		पूर्ण अन्यथा अगर (म_भेद(name, "version") == 0) अणु
			err = bpf_object__init_kversion(obj, data->d_buf, data->d_size);
			अगर (err)
				वापस err;
		पूर्ण अन्यथा अगर (म_भेद(name, "maps") == 0) अणु
			obj->efile.maps_shndx = idx;
		पूर्ण अन्यथा अगर (म_भेद(name, MAPS_ELF_SEC) == 0) अणु
			obj->efile.btf_maps_shndx = idx;
		पूर्ण अन्यथा अगर (म_भेद(name, BTF_ELF_SEC) == 0) अणु
			btf_data = data;
		पूर्ण अन्यथा अगर (म_भेद(name, BTF_EXT_ELF_SEC) == 0) अणु
			btf_ext_data = data;
		पूर्ण अन्यथा अगर (sh.sh_type == SHT_SYMTAB) अणु
			/* alपढ़ोy processed during the first pass above */
		पूर्ण अन्यथा अगर (sh.sh_type == SHT_PROGBITS && data->d_size > 0) अणु
			अगर (sh.sh_flags & SHF_EXECINSTR) अणु
				अगर (म_भेद(name, ".text") == 0)
					obj->efile.text_shndx = idx;
				err = bpf_object__add_programs(obj, data, name, idx);
				अगर (err)
					वापस err;
			पूर्ण अन्यथा अगर (म_भेद(name, DATA_SEC) == 0) अणु
				obj->efile.data = data;
				obj->efile.data_shndx = idx;
			पूर्ण अन्यथा अगर (म_भेद(name, RODATA_SEC) == 0) अणु
				obj->efile.rodata = data;
				obj->efile.rodata_shndx = idx;
			पूर्ण अन्यथा अगर (म_भेद(name, STRUCT_OPS_SEC) == 0) अणु
				obj->efile.st_ops_data = data;
				obj->efile.st_ops_shndx = idx;
			पूर्ण अन्यथा अणु
				pr_info("elf: skipping unrecognized data section(%d) %s\n",
					idx, name);
			पूर्ण
		पूर्ण अन्यथा अगर (sh.sh_type == SHT_REL) अणु
			पूर्णांक nr_sects = obj->efile.nr_reloc_sects;
			व्योम *sects = obj->efile.reloc_sects;
			पूर्णांक sec = sh.sh_info; /* poपूर्णांकs to other section */

			/* Only करो relo क्रम section with exec inकाष्ठाions */
			अगर (!section_have_execinstr(obj, sec) &&
			    म_भेद(name, ".rel" STRUCT_OPS_SEC) &&
			    म_भेद(name, ".rel" MAPS_ELF_SEC)) अणु
				pr_info("elf: skipping relo section(%d) %s for section(%d) %s\n",
					idx, name, sec,
					elf_sec_name(obj, elf_sec_by_idx(obj, sec)) ?: "<?>");
				जारी;
			पूर्ण

			sects = libbpf_पुनः_स्मृतिarray(sects, nr_sects + 1,
						    माप(*obj->efile.reloc_sects));
			अगर (!sects)
				वापस -ENOMEM;

			obj->efile.reloc_sects = sects;
			obj->efile.nr_reloc_sects++;

			obj->efile.reloc_sects[nr_sects].shdr = sh;
			obj->efile.reloc_sects[nr_sects].data = data;
		पूर्ण अन्यथा अगर (sh.sh_type == SHT_NOBITS && म_भेद(name, BSS_SEC) == 0) अणु
			obj->efile.bss = data;
			obj->efile.bss_shndx = idx;
		पूर्ण अन्यथा अणु
			pr_info("elf: skipping section(%d) %s (size %zu)\n", idx, name,
				(माप_प्रकार)sh.sh_size);
		पूर्ण
	पूर्ण

	अगर (!obj->efile.strtabidx || obj->efile.strtabidx > idx) अणु
		pr_warn("elf: symbol strings section missing or invalid in %s\n", obj->path);
		वापस -LIBBPF_ERRNO__FORMAT;
	पूर्ण

	/* sort BPF programs by section name and in-section inकाष्ठाion offset
	 * क्रम faster search */
	क्विक(obj->programs, obj->nr_programs, माप(*obj->programs), cmp_progs);

	वापस bpf_object__init_btf(obj, btf_data, btf_ext_data);
पूर्ण

अटल bool sym_is_बाह्य(स्थिर GElf_Sym *sym)
अणु
	पूर्णांक bind = GELF_ST_BIND(sym->st_info);
	/* बाह्यs are symbols w/ type=NOTYPE, bind=GLOBAL|WEAK, section=UND */
	वापस sym->st_shndx == SHN_UNDEF &&
	       (bind == STB_GLOBAL || bind == STB_WEAK) &&
	       GELF_ST_TYPE(sym->st_info) == STT_NOTYPE;
पूर्ण

अटल bool sym_is_subprog(स्थिर GElf_Sym *sym, पूर्णांक text_shndx)
अणु
	पूर्णांक bind = GELF_ST_BIND(sym->st_info);
	पूर्णांक type = GELF_ST_TYPE(sym->st_info);

	/* in .text section */
	अगर (sym->st_shndx != text_shndx)
		वापस false;

	/* local function */
	अगर (bind == STB_LOCAL && type == STT_SECTION)
		वापस true;

	/* global function */
	वापस bind == STB_GLOBAL && type == STT_FUNC;
पूर्ण

अटल पूर्णांक find_बाह्य_btf_id(स्थिर काष्ठा btf *btf, स्थिर अक्षर *ext_name)
अणु
	स्थिर काष्ठा btf_type *t;
	स्थिर अक्षर *tname;
	पूर्णांक i, n;

	अगर (!btf)
		वापस -ESRCH;

	n = btf__get_nr_types(btf);
	क्रम (i = 1; i <= n; i++) अणु
		t = btf__type_by_id(btf, i);

		अगर (!btf_is_var(t) && !btf_is_func(t))
			जारी;

		tname = btf__name_by_offset(btf, t->name_off);
		अगर (म_भेद(tname, ext_name))
			जारी;

		अगर (btf_is_var(t) &&
		    btf_var(t)->linkage != BTF_VAR_GLOBAL_EXTERN)
			वापस -EINVAL;

		अगर (btf_is_func(t) && btf_func_linkage(t) != BTF_FUNC_EXTERN)
			वापस -EINVAL;

		वापस i;
	पूर्ण

	वापस -ENOENT;
पूर्ण

अटल पूर्णांक find_बाह्य_sec_btf_id(काष्ठा btf *btf, पूर्णांक ext_btf_id) अणु
	स्थिर काष्ठा btf_var_secinfo *vs;
	स्थिर काष्ठा btf_type *t;
	पूर्णांक i, j, n;

	अगर (!btf)
		वापस -ESRCH;

	n = btf__get_nr_types(btf);
	क्रम (i = 1; i <= n; i++) अणु
		t = btf__type_by_id(btf, i);

		अगर (!btf_is_datasec(t))
			जारी;

		vs = btf_var_secinfos(t);
		क्रम (j = 0; j < btf_vlen(t); j++, vs++) अणु
			अगर (vs->type == ext_btf_id)
				वापस i;
		पूर्ण
	पूर्ण

	वापस -ENOENT;
पूर्ण

अटल क्रमागत kcfg_type find_kcfg_type(स्थिर काष्ठा btf *btf, पूर्णांक id,
				     bool *is_चिन्हित)
अणु
	स्थिर काष्ठा btf_type *t;
	स्थिर अक्षर *name;

	t = skip_mods_and_प्रकारs(btf, id, शून्य);
	name = btf__name_by_offset(btf, t->name_off);

	अगर (is_चिन्हित)
		*is_चिन्हित = false;
	चयन (btf_kind(t)) अणु
	हाल BTF_KIND_INT: अणु
		पूर्णांक enc = btf_पूर्णांक_encoding(t);

		अगर (enc & BTF_INT_BOOL)
			वापस t->size == 1 ? KCFG_BOOL : KCFG_UNKNOWN;
		अगर (is_चिन्हित)
			*is_चिन्हित = enc & BTF_INT_SIGNED;
		अगर (t->size == 1)
			वापस KCFG_CHAR;
		अगर (t->size < 1 || t->size > 8 || (t->size & (t->size - 1)))
			वापस KCFG_UNKNOWN;
		वापस KCFG_INT;
	पूर्ण
	हाल BTF_KIND_ENUM:
		अगर (t->size != 4)
			वापस KCFG_UNKNOWN;
		अगर (म_भेद(name, "libbpf_tristate"))
			वापस KCFG_UNKNOWN;
		वापस KCFG_TRISTATE;
	हाल BTF_KIND_ARRAY:
		अगर (btf_array(t)->nelems == 0)
			वापस KCFG_UNKNOWN;
		अगर (find_kcfg_type(btf, btf_array(t)->type, शून्य) != KCFG_CHAR)
			वापस KCFG_UNKNOWN;
		वापस KCFG_CHAR_ARR;
	शेष:
		वापस KCFG_UNKNOWN;
	पूर्ण
पूर्ण

अटल पूर्णांक cmp_बाह्यs(स्थिर व्योम *_a, स्थिर व्योम *_b)
अणु
	स्थिर काष्ठा बाह्य_desc *a = _a;
	स्थिर काष्ठा बाह्य_desc *b = _b;

	अगर (a->type != b->type)
		वापस a->type < b->type ? -1 : 1;

	अगर (a->type == EXT_KCFG) अणु
		/* descending order by alignment requirements */
		अगर (a->kcfg.align != b->kcfg.align)
			वापस a->kcfg.align > b->kcfg.align ? -1 : 1;
		/* ascending order by size, within same alignment class */
		अगर (a->kcfg.sz != b->kcfg.sz)
			वापस a->kcfg.sz < b->kcfg.sz ? -1 : 1;
	पूर्ण

	/* resolve ties by name */
	वापस म_भेद(a->name, b->name);
पूर्ण

अटल पूर्णांक find_पूर्णांक_btf_id(स्थिर काष्ठा btf *btf)
अणु
	स्थिर काष्ठा btf_type *t;
	पूर्णांक i, n;

	n = btf__get_nr_types(btf);
	क्रम (i = 1; i <= n; i++) अणु
		t = btf__type_by_id(btf, i);

		अगर (btf_is_पूर्णांक(t) && btf_पूर्णांक_bits(t) == 32)
			वापस i;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक add_dummy_ksym_var(काष्ठा btf *btf)
अणु
	पूर्णांक i, पूर्णांक_btf_id, sec_btf_id, dummy_var_btf_id;
	स्थिर काष्ठा btf_var_secinfo *vs;
	स्थिर काष्ठा btf_type *sec;

	अगर (!btf)
		वापस 0;

	sec_btf_id = btf__find_by_name_kind(btf, KSYMS_SEC,
					    BTF_KIND_DATASEC);
	अगर (sec_btf_id < 0)
		वापस 0;

	sec = btf__type_by_id(btf, sec_btf_id);
	vs = btf_var_secinfos(sec);
	क्रम (i = 0; i < btf_vlen(sec); i++, vs++) अणु
		स्थिर काष्ठा btf_type *vt;

		vt = btf__type_by_id(btf, vs->type);
		अगर (btf_is_func(vt))
			अवरोध;
	पूर्ण

	/* No func in ksyms sec.  No need to add dummy var. */
	अगर (i == btf_vlen(sec))
		वापस 0;

	पूर्णांक_btf_id = find_पूर्णांक_btf_id(btf);
	dummy_var_btf_id = btf__add_var(btf,
					"dummy_ksym",
					BTF_VAR_GLOBAL_ALLOCATED,
					पूर्णांक_btf_id);
	अगर (dummy_var_btf_id < 0)
		pr_warn("cannot create a dummy_ksym var\n");

	वापस dummy_var_btf_id;
पूर्ण

अटल पूर्णांक bpf_object__collect_बाह्यs(काष्ठा bpf_object *obj)
अणु
	काष्ठा btf_type *sec, *kcfg_sec = शून्य, *ksym_sec = शून्य;
	स्थिर काष्ठा btf_type *t;
	काष्ठा बाह्य_desc *ext;
	पूर्णांक i, n, off, dummy_var_btf_id;
	स्थिर अक्षर *ext_name, *sec_name;
	Elf_Scn *scn;
	GElf_Shdr sh;

	अगर (!obj->efile.symbols)
		वापस 0;

	scn = elf_sec_by_idx(obj, obj->efile.symbols_shndx);
	अगर (elf_sec_hdr(obj, scn, &sh))
		वापस -LIBBPF_ERRNO__FORMAT;

	dummy_var_btf_id = add_dummy_ksym_var(obj->btf);
	अगर (dummy_var_btf_id < 0)
		वापस dummy_var_btf_id;

	n = sh.sh_size / sh.sh_entsize;
	pr_debug("looking for externs among %d symbols...\n", n);

	क्रम (i = 0; i < n; i++) अणु
		GElf_Sym sym;

		अगर (!gelf_माला_लोym(obj->efile.symbols, i, &sym))
			वापस -LIBBPF_ERRNO__FORMAT;
		अगर (!sym_is_बाह्य(&sym))
			जारी;
		ext_name = elf_sym_str(obj, sym.st_name);
		अगर (!ext_name || !ext_name[0])
			जारी;

		ext = obj->बाह्यs;
		ext = libbpf_पुनः_स्मृतिarray(ext, obj->nr_बाह्य + 1, माप(*ext));
		अगर (!ext)
			वापस -ENOMEM;
		obj->बाह्यs = ext;
		ext = &ext[obj->nr_बाह्य];
		स_रखो(ext, 0, माप(*ext));
		obj->nr_बाह्य++;

		ext->btf_id = find_बाह्य_btf_id(obj->btf, ext_name);
		अगर (ext->btf_id <= 0) अणु
			pr_warn("failed to find BTF for extern '%s': %d\n",
				ext_name, ext->btf_id);
			वापस ext->btf_id;
		पूर्ण
		t = btf__type_by_id(obj->btf, ext->btf_id);
		ext->name = btf__name_by_offset(obj->btf, t->name_off);
		ext->sym_idx = i;
		ext->is_weak = GELF_ST_BIND(sym.st_info) == STB_WEAK;

		ext->sec_btf_id = find_बाह्य_sec_btf_id(obj->btf, ext->btf_id);
		अगर (ext->sec_btf_id <= 0) अणु
			pr_warn("failed to find BTF for extern '%s' [%d] section: %d\n",
				ext_name, ext->btf_id, ext->sec_btf_id);
			वापस ext->sec_btf_id;
		पूर्ण
		sec = (व्योम *)btf__type_by_id(obj->btf, ext->sec_btf_id);
		sec_name = btf__name_by_offset(obj->btf, sec->name_off);

		अगर (म_भेद(sec_name, KCONFIG_SEC) == 0) अणु
			अगर (btf_is_func(t)) अणु
				pr_warn("extern function %s is unsupported under %s section\n",
					ext->name, KCONFIG_SEC);
				वापस -ENOTSUP;
			पूर्ण
			kcfg_sec = sec;
			ext->type = EXT_KCFG;
			ext->kcfg.sz = btf__resolve_size(obj->btf, t->type);
			अगर (ext->kcfg.sz <= 0) अणु
				pr_warn("failed to resolve size of extern (kcfg) '%s': %d\n",
					ext_name, ext->kcfg.sz);
				वापस ext->kcfg.sz;
			पूर्ण
			ext->kcfg.align = btf__align_of(obj->btf, t->type);
			अगर (ext->kcfg.align <= 0) अणु
				pr_warn("failed to determine alignment of extern (kcfg) '%s': %d\n",
					ext_name, ext->kcfg.align);
				वापस -EINVAL;
			पूर्ण
			ext->kcfg.type = find_kcfg_type(obj->btf, t->type,
						        &ext->kcfg.is_चिन्हित);
			अगर (ext->kcfg.type == KCFG_UNKNOWN) अणु
				pr_warn("extern (kcfg) '%s' type is unsupported\n", ext_name);
				वापस -ENOTSUP;
			पूर्ण
		पूर्ण अन्यथा अगर (म_भेद(sec_name, KSYMS_SEC) == 0) अणु
			अगर (btf_is_func(t) && ext->is_weak) अणु
				pr_warn("extern weak function %s is unsupported\n",
					ext->name);
				वापस -ENOTSUP;
			पूर्ण
			ksym_sec = sec;
			ext->type = EXT_KSYM;
			skip_mods_and_प्रकारs(obj->btf, t->type,
					       &ext->ksym.type_id);
		पूर्ण अन्यथा अणु
			pr_warn("unrecognized extern section '%s'\n", sec_name);
			वापस -ENOTSUP;
		पूर्ण
	पूर्ण
	pr_debug("collected %d externs total\n", obj->nr_बाह्य);

	अगर (!obj->nr_बाह्य)
		वापस 0;

	/* sort बाह्यs by type, क्रम kcfg ones also by (align, size, name) */
	क्विक(obj->बाह्यs, obj->nr_बाह्य, माप(*ext), cmp_बाह्यs);

	/* क्रम .ksyms section, we need to turn all बाह्यs पूर्णांकo allocated
	 * variables in BTF to pass kernel verअगरication; we करो this by
	 * pretending that each बाह्य is a 8-byte variable
	 */
	अगर (ksym_sec) अणु
		/* find existing 4-byte पूर्णांकeger type in BTF to use क्रम fake
		 * बाह्य variables in DATASEC
		 */
		पूर्णांक पूर्णांक_btf_id = find_पूर्णांक_btf_id(obj->btf);
		/* For बाह्य function, a dummy_var added earlier
		 * will be used to replace the vs->type and
		 * its name string will be used to refill
		 * the missing param's name.
		 */
		स्थिर काष्ठा btf_type *dummy_var;

		dummy_var = btf__type_by_id(obj->btf, dummy_var_btf_id);
		क्रम (i = 0; i < obj->nr_बाह्य; i++) अणु
			ext = &obj->बाह्यs[i];
			अगर (ext->type != EXT_KSYM)
				जारी;
			pr_debug("extern (ksym) #%d: symbol %d, name %s\n",
				 i, ext->sym_idx, ext->name);
		पूर्ण

		sec = ksym_sec;
		n = btf_vlen(sec);
		क्रम (i = 0, off = 0; i < n; i++, off += माप(पूर्णांक)) अणु
			काष्ठा btf_var_secinfo *vs = btf_var_secinfos(sec) + i;
			काष्ठा btf_type *vt;

			vt = (व्योम *)btf__type_by_id(obj->btf, vs->type);
			ext_name = btf__name_by_offset(obj->btf, vt->name_off);
			ext = find_बाह्य_by_name(obj, ext_name);
			अगर (!ext) अणु
				pr_warn("failed to find extern definition for BTF %s '%s'\n",
					btf_kind_str(vt), ext_name);
				वापस -ESRCH;
			पूर्ण
			अगर (btf_is_func(vt)) अणु
				स्थिर काष्ठा btf_type *func_proto;
				काष्ठा btf_param *param;
				पूर्णांक j;

				func_proto = btf__type_by_id(obj->btf,
							     vt->type);
				param = btf_params(func_proto);
				/* Reuse the dummy_var string अगर the
				 * func proto करोes not have param name.
				 */
				क्रम (j = 0; j < btf_vlen(func_proto); j++)
					अगर (param[j].type && !param[j].name_off)
						param[j].name_off =
							dummy_var->name_off;
				vs->type = dummy_var_btf_id;
				vt->info &= ~0xffff;
				vt->info |= BTF_FUNC_GLOBAL;
			पूर्ण अन्यथा अणु
				btf_var(vt)->linkage = BTF_VAR_GLOBAL_ALLOCATED;
				vt->type = पूर्णांक_btf_id;
			पूर्ण
			vs->offset = off;
			vs->size = माप(पूर्णांक);
		पूर्ण
		sec->size = off;
	पूर्ण

	अगर (kcfg_sec) अणु
		sec = kcfg_sec;
		/* क्रम kcfg बाह्यs calculate their offsets within a .kconfig map */
		off = 0;
		क्रम (i = 0; i < obj->nr_बाह्य; i++) अणु
			ext = &obj->बाह्यs[i];
			अगर (ext->type != EXT_KCFG)
				जारी;

			ext->kcfg.data_off = roundup(off, ext->kcfg.align);
			off = ext->kcfg.data_off + ext->kcfg.sz;
			pr_debug("extern (kcfg) #%d: symbol %d, off %u, name %s\n",
				 i, ext->sym_idx, ext->kcfg.data_off, ext->name);
		पूर्ण
		sec->size = off;
		n = btf_vlen(sec);
		क्रम (i = 0; i < n; i++) अणु
			काष्ठा btf_var_secinfo *vs = btf_var_secinfos(sec) + i;

			t = btf__type_by_id(obj->btf, vs->type);
			ext_name = btf__name_by_offset(obj->btf, t->name_off);
			ext = find_बाह्य_by_name(obj, ext_name);
			अगर (!ext) अणु
				pr_warn("failed to find extern definition for BTF var '%s'\n",
					ext_name);
				वापस -ESRCH;
			पूर्ण
			btf_var(t)->linkage = BTF_VAR_GLOBAL_ALLOCATED;
			vs->offset = ext->kcfg.data_off;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

काष्ठा bpf_program *
bpf_object__find_program_by_title(स्थिर काष्ठा bpf_object *obj,
				  स्थिर अक्षर *title)
अणु
	काष्ठा bpf_program *pos;

	bpf_object__क्रम_each_program(pos, obj) अणु
		अगर (pos->sec_name && !म_भेद(pos->sec_name, title))
			वापस pos;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल bool prog_is_subprog(स्थिर काष्ठा bpf_object *obj,
			    स्थिर काष्ठा bpf_program *prog)
अणु
	/* For legacy reasons, libbpf supports an entry-poपूर्णांक BPF programs
	 * without SEC() attribute, i.e., those in the .text section. But अगर
	 * there are 2 or more such programs in the .text section, they all
	 * must be subprograms called from entry-poपूर्णांक BPF programs in
	 * designated SEC()'tions, otherwise there is no way to distinguish
	 * which of those programs should be loaded vs which are a subprogram.
	 * Similarly, अगर there is a function/program in .text and at least one
	 * other BPF program with custom SEC() attribute, then we just assume
	 * .text programs are subprograms (even अगर they are not called from
	 * other programs), because libbpf never explicitly supported mixing
	 * SEC()-designated BPF programs and .text entry-poपूर्णांक BPF programs.
	 */
	वापस prog->sec_idx == obj->efile.text_shndx && obj->nr_programs > 1;
पूर्ण

काष्ठा bpf_program *
bpf_object__find_program_by_name(स्थिर काष्ठा bpf_object *obj,
				 स्थिर अक्षर *name)
अणु
	काष्ठा bpf_program *prog;

	bpf_object__क्रम_each_program(prog, obj) अणु
		अगर (prog_is_subprog(obj, prog))
			जारी;
		अगर (!म_भेद(prog->name, name))
			वापस prog;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल bool bpf_object__shndx_is_data(स्थिर काष्ठा bpf_object *obj,
				      पूर्णांक shndx)
अणु
	वापस shndx == obj->efile.data_shndx ||
	       shndx == obj->efile.bss_shndx ||
	       shndx == obj->efile.rodata_shndx;
पूर्ण

अटल bool bpf_object__shndx_is_maps(स्थिर काष्ठा bpf_object *obj,
				      पूर्णांक shndx)
अणु
	वापस shndx == obj->efile.maps_shndx ||
	       shndx == obj->efile.btf_maps_shndx;
पूर्ण

अटल क्रमागत libbpf_map_type
bpf_object__section_to_libbpf_map_type(स्थिर काष्ठा bpf_object *obj, पूर्णांक shndx)
अणु
	अगर (shndx == obj->efile.data_shndx)
		वापस LIBBPF_MAP_DATA;
	अन्यथा अगर (shndx == obj->efile.bss_shndx)
		वापस LIBBPF_MAP_BSS;
	अन्यथा अगर (shndx == obj->efile.rodata_shndx)
		वापस LIBBPF_MAP_RODATA;
	अन्यथा अगर (shndx == obj->efile.symbols_shndx)
		वापस LIBBPF_MAP_KCONFIG;
	अन्यथा
		वापस LIBBPF_MAP_UNSPEC;
पूर्ण

अटल पूर्णांक bpf_program__record_reloc(काष्ठा bpf_program *prog,
				     काष्ठा reloc_desc *reloc_desc,
				     __u32 insn_idx, स्थिर अक्षर *sym_name,
				     स्थिर GElf_Sym *sym, स्थिर GElf_Rel *rel)
अणु
	काष्ठा bpf_insn *insn = &prog->insns[insn_idx];
	माप_प्रकार map_idx, nr_maps = prog->obj->nr_maps;
	काष्ठा bpf_object *obj = prog->obj;
	__u32 shdr_idx = sym->st_shndx;
	क्रमागत libbpf_map_type type;
	स्थिर अक्षर *sym_sec_name;
	काष्ठा bpf_map *map;

	अगर (!is_call_insn(insn) && !is_ldimm64_insn(insn)) अणु
		pr_warn("prog '%s': invalid relo against '%s' for insns[%d].code 0x%x\n",
			prog->name, sym_name, insn_idx, insn->code);
		वापस -LIBBPF_ERRNO__RELOC;
	पूर्ण

	अगर (sym_is_बाह्य(sym)) अणु
		पूर्णांक sym_idx = GELF_R_SYM(rel->r_info);
		पूर्णांक i, n = obj->nr_बाह्य;
		काष्ठा बाह्य_desc *ext;

		क्रम (i = 0; i < n; i++) अणु
			ext = &obj->बाह्यs[i];
			अगर (ext->sym_idx == sym_idx)
				अवरोध;
		पूर्ण
		अगर (i >= n) अणु
			pr_warn("prog '%s': extern relo failed to find extern for '%s' (%d)\n",
				prog->name, sym_name, sym_idx);
			वापस -LIBBPF_ERRNO__RELOC;
		पूर्ण
		pr_debug("prog '%s': found extern #%d '%s' (sym %d) for insn #%u\n",
			 prog->name, i, ext->name, ext->sym_idx, insn_idx);
		अगर (insn->code == (BPF_JMP | BPF_CALL))
			reloc_desc->type = RELO_EXTERN_FUNC;
		अन्यथा
			reloc_desc->type = RELO_EXTERN_VAR;
		reloc_desc->insn_idx = insn_idx;
		reloc_desc->sym_off = i; /* sym_off stores बाह्य index */
		वापस 0;
	पूर्ण

	/* sub-program call relocation */
	अगर (is_call_insn(insn)) अणु
		अगर (insn->src_reg != BPF_PSEUDO_CALL) अणु
			pr_warn("prog '%s': incorrect bpf_call opcode\n", prog->name);
			वापस -LIBBPF_ERRNO__RELOC;
		पूर्ण
		/* text_shndx can be 0, अगर no शेष "main" program exists */
		अगर (!shdr_idx || shdr_idx != obj->efile.text_shndx) अणु
			sym_sec_name = elf_sec_name(obj, elf_sec_by_idx(obj, shdr_idx));
			pr_warn("prog '%s': bad call relo against '%s' in section '%s'\n",
				prog->name, sym_name, sym_sec_name);
			वापस -LIBBPF_ERRNO__RELOC;
		पूर्ण
		अगर (sym->st_value % BPF_INSN_SZ) अणु
			pr_warn("prog '%s': bad call relo against '%s' at offset %zu\n",
				prog->name, sym_name, (माप_प्रकार)sym->st_value);
			वापस -LIBBPF_ERRNO__RELOC;
		पूर्ण
		reloc_desc->type = RELO_CALL;
		reloc_desc->insn_idx = insn_idx;
		reloc_desc->sym_off = sym->st_value;
		वापस 0;
	पूर्ण

	अगर (!shdr_idx || shdr_idx >= SHN_LORESERVE) अणु
		pr_warn("prog '%s': invalid relo against '%s' in special section 0x%x; forgot to initialize global var?..\n",
			prog->name, sym_name, shdr_idx);
		वापस -LIBBPF_ERRNO__RELOC;
	पूर्ण

	/* loading subprog addresses */
	अगर (sym_is_subprog(sym, obj->efile.text_shndx)) अणु
		/* global_func: sym->st_value = offset in the section, insn->imm = 0.
		 * local_func: sym->st_value = 0, insn->imm = offset in the section.
		 */
		अगर ((sym->st_value % BPF_INSN_SZ) || (insn->imm % BPF_INSN_SZ)) अणु
			pr_warn("prog '%s': bad subprog addr relo against '%s' at offset %zu+%d\n",
				prog->name, sym_name, (माप_प्रकार)sym->st_value, insn->imm);
			वापस -LIBBPF_ERRNO__RELOC;
		पूर्ण

		reloc_desc->type = RELO_SUBPROG_ADDR;
		reloc_desc->insn_idx = insn_idx;
		reloc_desc->sym_off = sym->st_value;
		वापस 0;
	पूर्ण

	type = bpf_object__section_to_libbpf_map_type(obj, shdr_idx);
	sym_sec_name = elf_sec_name(obj, elf_sec_by_idx(obj, shdr_idx));

	/* generic map reference relocation */
	अगर (type == LIBBPF_MAP_UNSPEC) अणु
		अगर (!bpf_object__shndx_is_maps(obj, shdr_idx)) अणु
			pr_warn("prog '%s': bad map relo against '%s' in section '%s'\n",
				prog->name, sym_name, sym_sec_name);
			वापस -LIBBPF_ERRNO__RELOC;
		पूर्ण
		क्रम (map_idx = 0; map_idx < nr_maps; map_idx++) अणु
			map = &obj->maps[map_idx];
			अगर (map->libbpf_type != type ||
			    map->sec_idx != sym->st_shndx ||
			    map->sec_offset != sym->st_value)
				जारी;
			pr_debug("prog '%s': found map %zd (%s, sec %d, off %zu) for insn #%u\n",
				 prog->name, map_idx, map->name, map->sec_idx,
				 map->sec_offset, insn_idx);
			अवरोध;
		पूर्ण
		अगर (map_idx >= nr_maps) अणु
			pr_warn("prog '%s': map relo failed to find map for section '%s', off %zu\n",
				prog->name, sym_sec_name, (माप_प्रकार)sym->st_value);
			वापस -LIBBPF_ERRNO__RELOC;
		पूर्ण
		reloc_desc->type = RELO_LD64;
		reloc_desc->insn_idx = insn_idx;
		reloc_desc->map_idx = map_idx;
		reloc_desc->sym_off = 0; /* sym->st_value determines map_idx */
		वापस 0;
	पूर्ण

	/* global data map relocation */
	अगर (!bpf_object__shndx_is_data(obj, shdr_idx)) अणु
		pr_warn("prog '%s': bad data relo against section '%s'\n",
			prog->name, sym_sec_name);
		वापस -LIBBPF_ERRNO__RELOC;
	पूर्ण
	क्रम (map_idx = 0; map_idx < nr_maps; map_idx++) अणु
		map = &obj->maps[map_idx];
		अगर (map->libbpf_type != type)
			जारी;
		pr_debug("prog '%s': found data map %zd (%s, sec %d, off %zu) for insn %u\n",
			 prog->name, map_idx, map->name, map->sec_idx,
			 map->sec_offset, insn_idx);
		अवरोध;
	पूर्ण
	अगर (map_idx >= nr_maps) अणु
		pr_warn("prog '%s': data relo failed to find map for section '%s'\n",
			prog->name, sym_sec_name);
		वापस -LIBBPF_ERRNO__RELOC;
	पूर्ण

	reloc_desc->type = RELO_DATA;
	reloc_desc->insn_idx = insn_idx;
	reloc_desc->map_idx = map_idx;
	reloc_desc->sym_off = sym->st_value;
	वापस 0;
पूर्ण

अटल bool prog_contains_insn(स्थिर काष्ठा bpf_program *prog, माप_प्रकार insn_idx)
अणु
	वापस insn_idx >= prog->sec_insn_off &&
	       insn_idx < prog->sec_insn_off + prog->sec_insn_cnt;
पूर्ण

अटल काष्ठा bpf_program *find_prog_by_sec_insn(स्थिर काष्ठा bpf_object *obj,
						 माप_प्रकार sec_idx, माप_प्रकार insn_idx)
अणु
	पूर्णांक l = 0, r = obj->nr_programs - 1, m;
	काष्ठा bpf_program *prog;

	जबतक (l < r) अणु
		m = l + (r - l + 1) / 2;
		prog = &obj->programs[m];

		अगर (prog->sec_idx < sec_idx ||
		    (prog->sec_idx == sec_idx && prog->sec_insn_off <= insn_idx))
			l = m;
		अन्यथा
			r = m - 1;
	पूर्ण
	/* matching program could be at index l, but it still might be the
	 * wrong one, so we need to द्विगुन check conditions क्रम the last समय
	 */
	prog = &obj->programs[l];
	अगर (prog->sec_idx == sec_idx && prog_contains_insn(prog, insn_idx))
		वापस prog;
	वापस शून्य;
पूर्ण

अटल पूर्णांक
bpf_object__collect_prog_relos(काष्ठा bpf_object *obj, GElf_Shdr *shdr, Elf_Data *data)
अणु
	Elf_Data *symbols = obj->efile.symbols;
	स्थिर अक्षर *relo_sec_name, *sec_name;
	माप_प्रकार sec_idx = shdr->sh_info;
	काष्ठा bpf_program *prog;
	काष्ठा reloc_desc *relos;
	पूर्णांक err, i, nrels;
	स्थिर अक्षर *sym_name;
	__u32 insn_idx;
	Elf_Scn *scn;
	Elf_Data *scn_data;
	GElf_Sym sym;
	GElf_Rel rel;

	scn = elf_sec_by_idx(obj, sec_idx);
	scn_data = elf_sec_data(obj, scn);

	relo_sec_name = elf_sec_str(obj, shdr->sh_name);
	sec_name = elf_sec_name(obj, scn);
	अगर (!relo_sec_name || !sec_name)
		वापस -EINVAL;

	pr_debug("sec '%s': collecting relocation for section(%zu) '%s'\n",
		 relo_sec_name, sec_idx, sec_name);
	nrels = shdr->sh_size / shdr->sh_entsize;

	क्रम (i = 0; i < nrels; i++) अणु
		अगर (!gelf_getrel(data, i, &rel)) अणु
			pr_warn("sec '%s': failed to get relo #%d\n", relo_sec_name, i);
			वापस -LIBBPF_ERRNO__FORMAT;
		पूर्ण
		अगर (!gelf_माला_लोym(symbols, GELF_R_SYM(rel.r_info), &sym)) अणु
			pr_warn("sec '%s': symbol 0x%zx not found for relo #%d\n",
				relo_sec_name, (माप_प्रकार)GELF_R_SYM(rel.r_info), i);
			वापस -LIBBPF_ERRNO__FORMAT;
		पूर्ण

		अगर (rel.r_offset % BPF_INSN_SZ || rel.r_offset >= scn_data->d_size) अणु
			pr_warn("sec '%s': invalid offset 0x%zx for relo #%d\n",
				relo_sec_name, (माप_प्रकार)GELF_R_SYM(rel.r_info), i);
			वापस -LIBBPF_ERRNO__FORMAT;
		पूर्ण

		insn_idx = rel.r_offset / BPF_INSN_SZ;
		/* relocations against अटल functions are recorded as
		 * relocations against the section that contains a function;
		 * in such हाल, symbol will be STT_SECTION and sym.st_name
		 * will poपूर्णांक to empty string (0), so fetch section name
		 * instead
		 */
		अगर (GELF_ST_TYPE(sym.st_info) == STT_SECTION && sym.st_name == 0)
			sym_name = elf_sec_name(obj, elf_sec_by_idx(obj, sym.st_shndx));
		अन्यथा
			sym_name = elf_sym_str(obj, sym.st_name);
		sym_name = sym_name ?: "<?";

		pr_debug("sec '%s': relo #%d: insn #%u against '%s'\n",
			 relo_sec_name, i, insn_idx, sym_name);

		prog = find_prog_by_sec_insn(obj, sec_idx, insn_idx);
		अगर (!prog) अणु
			pr_debug("sec '%s': relo #%d: couldn't find program in section '%s' for insn #%u, probably overridden weak function, skipping...\n",
				relo_sec_name, i, sec_name, insn_idx);
			जारी;
		पूर्ण

		relos = libbpf_पुनः_स्मृतिarray(prog->reloc_desc,
					    prog->nr_reloc + 1, माप(*relos));
		अगर (!relos)
			वापस -ENOMEM;
		prog->reloc_desc = relos;

		/* adjust insn_idx to local BPF program frame of reference */
		insn_idx -= prog->sec_insn_off;
		err = bpf_program__record_reloc(prog, &relos[prog->nr_reloc],
						insn_idx, sym_name, &sym, &rel);
		अगर (err)
			वापस err;

		prog->nr_reloc++;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक bpf_map_find_btf_info(काष्ठा bpf_object *obj, काष्ठा bpf_map *map)
अणु
	काष्ठा bpf_map_def *def = &map->def;
	__u32 key_type_id = 0, value_type_id = 0;
	पूर्णांक ret;

	/* अगर it's BTF-defined map, we don't need to search क्रम type IDs.
	 * For काष्ठा_ops map, it करोes not need btf_key_type_id and
	 * btf_value_type_id.
	 */
	अगर (map->sec_idx == obj->efile.btf_maps_shndx ||
	    bpf_map__is_काष्ठा_ops(map))
		वापस 0;

	अगर (!bpf_map__is_पूर्णांकernal(map)) अणु
		ret = btf__get_map_kv_tids(obj->btf, map->name, def->key_size,
					   def->value_size, &key_type_id,
					   &value_type_id);
	पूर्ण अन्यथा अणु
		/*
		 * LLVM annotates global data dअगरferently in BTF, that is,
		 * only as '.data', '.bss' or '.rodata'.
		 */
		ret = btf__find_by_name(obj->btf,
				libbpf_type_to_btf_name[map->libbpf_type]);
	पूर्ण
	अगर (ret < 0)
		वापस ret;

	map->btf_key_type_id = key_type_id;
	map->btf_value_type_id = bpf_map__is_पूर्णांकernal(map) ?
				 ret : value_type_id;
	वापस 0;
पूर्ण

पूर्णांक bpf_map__reuse_fd(काष्ठा bpf_map *map, पूर्णांक fd)
अणु
	काष्ठा bpf_map_info info = अणुपूर्ण;
	__u32 len = माप(info);
	पूर्णांक new_fd, err;
	अक्षर *new_name;

	err = bpf_obj_get_info_by_fd(fd, &info, &len);
	अगर (err)
		वापस err;

	new_name = strdup(info.name);
	अगर (!new_name)
		वापस -त्रुटि_सं;

	new_fd = खोलो("/", O_RDONLY | O_CLOEXEC);
	अगर (new_fd < 0) अणु
		err = -त्रुटि_सं;
		जाओ err_मुक्त_new_name;
	पूर्ण

	new_fd = dup3(fd, new_fd, O_CLOEXEC);
	अगर (new_fd < 0) अणु
		err = -त्रुटि_सं;
		जाओ err_बंद_new_fd;
	पूर्ण

	err = zबंद(map->fd);
	अगर (err) अणु
		err = -त्रुटि_सं;
		जाओ err_बंद_new_fd;
	पूर्ण
	मुक्त(map->name);

	map->fd = new_fd;
	map->name = new_name;
	map->def.type = info.type;
	map->def.key_size = info.key_size;
	map->def.value_size = info.value_size;
	map->def.max_entries = info.max_entries;
	map->def.map_flags = info.map_flags;
	map->btf_key_type_id = info.btf_key_type_id;
	map->btf_value_type_id = info.btf_value_type_id;
	map->reused = true;

	वापस 0;

err_बंद_new_fd:
	बंद(new_fd);
err_मुक्त_new_name:
	मुक्त(new_name);
	वापस err;
पूर्ण

__u32 bpf_map__max_entries(स्थिर काष्ठा bpf_map *map)
अणु
	वापस map->def.max_entries;
पूर्ण

काष्ठा bpf_map *bpf_map__inner_map(काष्ठा bpf_map *map)
अणु
	अगर (!bpf_map_type__is_map_in_map(map->def.type))
		वापस शून्य;

	वापस map->inner_map;
पूर्ण

पूर्णांक bpf_map__set_max_entries(काष्ठा bpf_map *map, __u32 max_entries)
अणु
	अगर (map->fd >= 0)
		वापस -EBUSY;
	map->def.max_entries = max_entries;
	वापस 0;
पूर्ण

पूर्णांक bpf_map__resize(काष्ठा bpf_map *map, __u32 max_entries)
अणु
	अगर (!map || !max_entries)
		वापस -EINVAL;

	वापस bpf_map__set_max_entries(map, max_entries);
पूर्ण

अटल पूर्णांक
bpf_object__probe_loading(काष्ठा bpf_object *obj)
अणु
	काष्ठा bpf_load_program_attr attr;
	अक्षर *cp, errmsg[STRERR_बफ_मानE];
	काष्ठा bpf_insn insns[] = अणु
		BPF_MOV64_IMM(BPF_REG_0, 0),
		BPF_EXIT_INSN(),
	पूर्ण;
	पूर्णांक ret;

	/* make sure basic loading works */

	स_रखो(&attr, 0, माप(attr));
	attr.prog_type = BPF_PROG_TYPE_SOCKET_FILTER;
	attr.insns = insns;
	attr.insns_cnt = ARRAY_SIZE(insns);
	attr.license = "GPL";

	ret = bpf_load_program_xattr(&attr, शून्य, 0);
	अगर (ret < 0) अणु
		ret = त्रुटि_सं;
		cp = libbpf_म_त्रुटि_r(ret, errmsg, माप(errmsg));
		pr_warn("Error in %s():%s(%d). Couldn't load trivial BPF "
			"program. Make sure your kernel supports BPF "
			"(CONFIG_BPF_SYSCALL=y) and/or that RLIMIT_MEMLOCK is "
			"set to big enough value.\n", __func__, cp, ret);
		वापस -ret;
	पूर्ण
	बंद(ret);

	वापस 0;
पूर्ण

अटल पूर्णांक probe_fd(पूर्णांक fd)
अणु
	अगर (fd >= 0)
		बंद(fd);
	वापस fd >= 0;
पूर्ण

अटल पूर्णांक probe_kern_prog_name(व्योम)
अणु
	काष्ठा bpf_load_program_attr attr;
	काष्ठा bpf_insn insns[] = अणु
		BPF_MOV64_IMM(BPF_REG_0, 0),
		BPF_EXIT_INSN(),
	पूर्ण;
	पूर्णांक ret;

	/* make sure loading with name works */

	स_रखो(&attr, 0, माप(attr));
	attr.prog_type = BPF_PROG_TYPE_SOCKET_FILTER;
	attr.insns = insns;
	attr.insns_cnt = ARRAY_SIZE(insns);
	attr.license = "GPL";
	attr.name = "test";
	ret = bpf_load_program_xattr(&attr, शून्य, 0);
	वापस probe_fd(ret);
पूर्ण

अटल पूर्णांक probe_kern_global_data(व्योम)
अणु
	काष्ठा bpf_load_program_attr prg_attr;
	काष्ठा bpf_create_map_attr map_attr;
	अक्षर *cp, errmsg[STRERR_बफ_मानE];
	काष्ठा bpf_insn insns[] = अणु
		BPF_LD_MAP_VALUE(BPF_REG_1, 0, 16),
		BPF_ST_MEM(BPF_DW, BPF_REG_1, 0, 42),
		BPF_MOV64_IMM(BPF_REG_0, 0),
		BPF_EXIT_INSN(),
	पूर्ण;
	पूर्णांक ret, map;

	स_रखो(&map_attr, 0, माप(map_attr));
	map_attr.map_type = BPF_MAP_TYPE_ARRAY;
	map_attr.key_size = माप(पूर्णांक);
	map_attr.value_size = 32;
	map_attr.max_entries = 1;

	map = bpf_create_map_xattr(&map_attr);
	अगर (map < 0) अणु
		ret = -त्रुटि_सं;
		cp = libbpf_म_त्रुटि_r(ret, errmsg, माप(errmsg));
		pr_warn("Error in %s():%s(%d). Couldn't create simple array map.\n",
			__func__, cp, -ret);
		वापस ret;
	पूर्ण

	insns[0].imm = map;

	स_रखो(&prg_attr, 0, माप(prg_attr));
	prg_attr.prog_type = BPF_PROG_TYPE_SOCKET_FILTER;
	prg_attr.insns = insns;
	prg_attr.insns_cnt = ARRAY_SIZE(insns);
	prg_attr.license = "GPL";

	ret = bpf_load_program_xattr(&prg_attr, शून्य, 0);
	बंद(map);
	वापस probe_fd(ret);
पूर्ण

अटल पूर्णांक probe_kern_btf(व्योम)
अणु
	अटल स्थिर अक्षर strs[] = "\0int";
	__u32 types[] = अणु
		/* पूर्णांक */
		BTF_TYPE_INT_ENC(1, BTF_INT_SIGNED, 0, 32, 4),
	पूर्ण;

	वापस probe_fd(libbpf__load_raw_btf((अक्षर *)types, माप(types),
					     strs, माप(strs)));
पूर्ण

अटल पूर्णांक probe_kern_btf_func(व्योम)
अणु
	अटल स्थिर अक्षर strs[] = "\0int\0x\0a";
	/* व्योम x(पूर्णांक a) अणुपूर्ण */
	__u32 types[] = अणु
		/* पूर्णांक */
		BTF_TYPE_INT_ENC(1, BTF_INT_SIGNED, 0, 32, 4),  /* [1] */
		/* FUNC_PROTO */                                /* [2] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_FUNC_PROTO, 0, 1), 0),
		BTF_PARAM_ENC(7, 1),
		/* FUNC x */                                    /* [3] */
		BTF_TYPE_ENC(5, BTF_INFO_ENC(BTF_KIND_FUNC, 0, 0), 2),
	पूर्ण;

	वापस probe_fd(libbpf__load_raw_btf((अक्षर *)types, माप(types),
					     strs, माप(strs)));
पूर्ण

अटल पूर्णांक probe_kern_btf_func_global(व्योम)
अणु
	अटल स्थिर अक्षर strs[] = "\0int\0x\0a";
	/* अटल व्योम x(पूर्णांक a) अणुपूर्ण */
	__u32 types[] = अणु
		/* पूर्णांक */
		BTF_TYPE_INT_ENC(1, BTF_INT_SIGNED, 0, 32, 4),  /* [1] */
		/* FUNC_PROTO */                                /* [2] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_FUNC_PROTO, 0, 1), 0),
		BTF_PARAM_ENC(7, 1),
		/* FUNC x BTF_FUNC_GLOBAL */                    /* [3] */
		BTF_TYPE_ENC(5, BTF_INFO_ENC(BTF_KIND_FUNC, 0, BTF_FUNC_GLOBAL), 2),
	पूर्ण;

	वापस probe_fd(libbpf__load_raw_btf((अक्षर *)types, माप(types),
					     strs, माप(strs)));
पूर्ण

अटल पूर्णांक probe_kern_btf_datasec(व्योम)
अणु
	अटल स्थिर अक्षर strs[] = "\0x\0.data";
	/* अटल पूर्णांक a; */
	__u32 types[] = अणु
		/* पूर्णांक */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),  /* [1] */
		/* VAR x */                                     /* [2] */
		BTF_TYPE_ENC(1, BTF_INFO_ENC(BTF_KIND_VAR, 0, 0), 1),
		BTF_VAR_STATIC,
		/* DATASEC val */                               /* [3] */
		BTF_TYPE_ENC(3, BTF_INFO_ENC(BTF_KIND_DATASEC, 0, 1), 4),
		BTF_VAR_SECINFO_ENC(2, 0, 4),
	पूर्ण;

	वापस probe_fd(libbpf__load_raw_btf((अक्षर *)types, माप(types),
					     strs, माप(strs)));
पूर्ण

अटल पूर्णांक probe_kern_btf_भग्न(व्योम)
अणु
	अटल स्थिर अक्षर strs[] = "\0float";
	__u32 types[] = अणु
		/* भग्न */
		BTF_TYPE_FLOAT_ENC(1, 4),
	पूर्ण;

	वापस probe_fd(libbpf__load_raw_btf((अक्षर *)types, माप(types),
					     strs, माप(strs)));
पूर्ण

अटल पूर्णांक probe_kern_array_mmap(व्योम)
अणु
	काष्ठा bpf_create_map_attr attr = अणु
		.map_type = BPF_MAP_TYPE_ARRAY,
		.map_flags = BPF_F_MMAPABLE,
		.key_size = माप(पूर्णांक),
		.value_size = माप(पूर्णांक),
		.max_entries = 1,
	पूर्ण;

	वापस probe_fd(bpf_create_map_xattr(&attr));
पूर्ण

अटल पूर्णांक probe_kern_exp_attach_type(व्योम)
अणु
	काष्ठा bpf_load_program_attr attr;
	काष्ठा bpf_insn insns[] = अणु
		BPF_MOV64_IMM(BPF_REG_0, 0),
		BPF_EXIT_INSN(),
	पूर्ण;

	स_रखो(&attr, 0, माप(attr));
	/* use any valid combination of program type and (optional)
	 * non-zero expected attach type (i.e., not a BPF_CGROUP_INET_INGRESS)
	 * to see अगर kernel supports expected_attach_type field क्रम
	 * BPF_PROG_LOAD command
	 */
	attr.prog_type = BPF_PROG_TYPE_CGROUP_SOCK;
	attr.expected_attach_type = BPF_CGROUP_INET_SOCK_CREATE;
	attr.insns = insns;
	attr.insns_cnt = ARRAY_SIZE(insns);
	attr.license = "GPL";

	वापस probe_fd(bpf_load_program_xattr(&attr, शून्य, 0));
पूर्ण

अटल पूर्णांक probe_kern_probe_पढ़ो_kernel(व्योम)
अणु
	काष्ठा bpf_load_program_attr attr;
	काष्ठा bpf_insn insns[] = अणु
		BPF_MOV64_REG(BPF_REG_1, BPF_REG_10),	/* r1 = r10 (fp) */
		BPF_ALU64_IMM(BPF_ADD, BPF_REG_1, -8),	/* r1 += -8 */
		BPF_MOV64_IMM(BPF_REG_2, 8),		/* r2 = 8 */
		BPF_MOV64_IMM(BPF_REG_3, 0),		/* r3 = 0 */
		BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_probe_पढ़ो_kernel),
		BPF_EXIT_INSN(),
	पूर्ण;

	स_रखो(&attr, 0, माप(attr));
	attr.prog_type = BPF_PROG_TYPE_KPROBE;
	attr.insns = insns;
	attr.insns_cnt = ARRAY_SIZE(insns);
	attr.license = "GPL";

	वापस probe_fd(bpf_load_program_xattr(&attr, शून्य, 0));
पूर्ण

अटल पूर्णांक probe_prog_bind_map(व्योम)
अणु
	काष्ठा bpf_load_program_attr prg_attr;
	काष्ठा bpf_create_map_attr map_attr;
	अक्षर *cp, errmsg[STRERR_बफ_मानE];
	काष्ठा bpf_insn insns[] = अणु
		BPF_MOV64_IMM(BPF_REG_0, 0),
		BPF_EXIT_INSN(),
	पूर्ण;
	पूर्णांक ret, map, prog;

	स_रखो(&map_attr, 0, माप(map_attr));
	map_attr.map_type = BPF_MAP_TYPE_ARRAY;
	map_attr.key_size = माप(पूर्णांक);
	map_attr.value_size = 32;
	map_attr.max_entries = 1;

	map = bpf_create_map_xattr(&map_attr);
	अगर (map < 0) अणु
		ret = -त्रुटि_सं;
		cp = libbpf_म_त्रुटि_r(ret, errmsg, माप(errmsg));
		pr_warn("Error in %s():%s(%d). Couldn't create simple array map.\n",
			__func__, cp, -ret);
		वापस ret;
	पूर्ण

	स_रखो(&prg_attr, 0, माप(prg_attr));
	prg_attr.prog_type = BPF_PROG_TYPE_SOCKET_FILTER;
	prg_attr.insns = insns;
	prg_attr.insns_cnt = ARRAY_SIZE(insns);
	prg_attr.license = "GPL";

	prog = bpf_load_program_xattr(&prg_attr, शून्य, 0);
	अगर (prog < 0) अणु
		बंद(map);
		वापस 0;
	पूर्ण

	ret = bpf_prog_bind_map(prog, map, शून्य);

	बंद(map);
	बंद(prog);

	वापस ret >= 0;
पूर्ण

अटल पूर्णांक probe_module_btf(व्योम)
अणु
	अटल स्थिर अक्षर strs[] = "\0int";
	__u32 types[] = अणु
		/* पूर्णांक */
		BTF_TYPE_INT_ENC(1, BTF_INT_SIGNED, 0, 32, 4),
	पूर्ण;
	काष्ठा bpf_btf_info info;
	__u32 len = माप(info);
	अक्षर name[16];
	पूर्णांक fd, err;

	fd = libbpf__load_raw_btf((अक्षर *)types, माप(types), strs, माप(strs));
	अगर (fd < 0)
		वापस 0; /* BTF not supported at all */

	स_रखो(&info, 0, माप(info));
	info.name = ptr_to_u64(name);
	info.name_len = माप(name);

	/* check that BPF_OBJ_GET_INFO_BY_FD supports specअगरying name poपूर्णांकer;
	 * kernel's module BTF support coincides with support क्रम
	 * name/name_len fields in काष्ठा bpf_btf_info.
	 */
	err = bpf_obj_get_info_by_fd(fd, &info, &len);
	बंद(fd);
	वापस !err;
पूर्ण

क्रमागत kern_feature_result अणु
	FEAT_UNKNOWN = 0,
	FEAT_SUPPORTED = 1,
	FEAT_MISSING = 2,
पूर्ण;

प्रकार पूर्णांक (*feature_probe_fn)(व्योम);

अटल काष्ठा kern_feature_desc अणु
	स्थिर अक्षर *desc;
	feature_probe_fn probe;
	क्रमागत kern_feature_result res;
पूर्ण feature_probes[__FEAT_CNT] = अणु
	[FEAT_PROG_NAME] = अणु
		"BPF program name", probe_kern_prog_name,
	पूर्ण,
	[FEAT_GLOBAL_DATA] = अणु
		"global variables", probe_kern_global_data,
	पूर्ण,
	[FEAT_BTF] = अणु
		"minimal BTF", probe_kern_btf,
	पूर्ण,
	[FEAT_BTF_FUNC] = अणु
		"BTF functions", probe_kern_btf_func,
	पूर्ण,
	[FEAT_BTF_GLOBAL_FUNC] = अणु
		"BTF global function", probe_kern_btf_func_global,
	पूर्ण,
	[FEAT_BTF_DATASEC] = अणु
		"BTF data section and variable", probe_kern_btf_datasec,
	पूर्ण,
	[FEAT_ARRAY_MMAP] = अणु
		"ARRAY map mmap()", probe_kern_array_mmap,
	पूर्ण,
	[FEAT_EXP_ATTACH_TYPE] = अणु
		"BPF_PROG_LOAD expected_attach_type attribute",
		probe_kern_exp_attach_type,
	पूर्ण,
	[FEAT_PROBE_READ_KERN] = अणु
		"bpf_probe_read_kernel() helper", probe_kern_probe_पढ़ो_kernel,
	पूर्ण,
	[FEAT_PROG_BIND_MAP] = अणु
		"BPF_PROG_BIND_MAP support", probe_prog_bind_map,
	पूर्ण,
	[FEAT_MODULE_BTF] = अणु
		"module BTF support", probe_module_btf,
	पूर्ण,
	[FEAT_BTF_FLOAT] = अणु
		"BTF_KIND_FLOAT support", probe_kern_btf_भग्न,
	पूर्ण,
पूर्ण;

अटल bool kernel_supports(क्रमागत kern_feature_id feat_id)
अणु
	काष्ठा kern_feature_desc *feat = &feature_probes[feat_id];
	पूर्णांक ret;

	अगर (READ_ONCE(feat->res) == FEAT_UNKNOWN) अणु
		ret = feat->probe();
		अगर (ret > 0) अणु
			WRITE_ONCE(feat->res, FEAT_SUPPORTED);
		पूर्ण अन्यथा अगर (ret == 0) अणु
			WRITE_ONCE(feat->res, FEAT_MISSING);
		पूर्ण अन्यथा अणु
			pr_warn("Detection of kernel %s support failed: %d\n", feat->desc, ret);
			WRITE_ONCE(feat->res, FEAT_MISSING);
		पूर्ण
	पूर्ण

	वापस READ_ONCE(feat->res) == FEAT_SUPPORTED;
पूर्ण

अटल bool map_is_reuse_compat(स्थिर काष्ठा bpf_map *map, पूर्णांक map_fd)
अणु
	काष्ठा bpf_map_info map_info = अणुपूर्ण;
	अक्षर msg[STRERR_बफ_मानE];
	__u32 map_info_len;

	map_info_len = माप(map_info);

	अगर (bpf_obj_get_info_by_fd(map_fd, &map_info, &map_info_len)) अणु
		pr_warn("failed to get map info for map FD %d: %s\n",
			map_fd, libbpf_म_त्रुटि_r(त्रुटि_सं, msg, माप(msg)));
		वापस false;
	पूर्ण

	वापस (map_info.type == map->def.type &&
		map_info.key_size == map->def.key_size &&
		map_info.value_size == map->def.value_size &&
		map_info.max_entries == map->def.max_entries &&
		map_info.map_flags == map->def.map_flags);
पूर्ण

अटल पूर्णांक
bpf_object__reuse_map(काष्ठा bpf_map *map)
अणु
	अक्षर *cp, errmsg[STRERR_बफ_मानE];
	पूर्णांक err, pin_fd;

	pin_fd = bpf_obj_get(map->pin_path);
	अगर (pin_fd < 0) अणु
		err = -त्रुटि_सं;
		अगर (err == -ENOENT) अणु
			pr_debug("found no pinned map to reuse at '%s'\n",
				 map->pin_path);
			वापस 0;
		पूर्ण

		cp = libbpf_म_त्रुटि_r(-err, errmsg, माप(errmsg));
		pr_warn("couldn't retrieve pinned map '%s': %s\n",
			map->pin_path, cp);
		वापस err;
	पूर्ण

	अगर (!map_is_reuse_compat(map, pin_fd)) अणु
		pr_warn("couldn't reuse pinned map at '%s': parameter mismatch\n",
			map->pin_path);
		बंद(pin_fd);
		वापस -EINVAL;
	पूर्ण

	err = bpf_map__reuse_fd(map, pin_fd);
	अगर (err) अणु
		बंद(pin_fd);
		वापस err;
	पूर्ण
	map->pinned = true;
	pr_debug("reused pinned map at '%s'\n", map->pin_path);

	वापस 0;
पूर्ण

अटल पूर्णांक
bpf_object__populate_पूर्णांकernal_map(काष्ठा bpf_object *obj, काष्ठा bpf_map *map)
अणु
	क्रमागत libbpf_map_type map_type = map->libbpf_type;
	अक्षर *cp, errmsg[STRERR_बफ_मानE];
	पूर्णांक err, zero = 0;

	err = bpf_map_update_elem(map->fd, &zero, map->mmaped, 0);
	अगर (err) अणु
		err = -त्रुटि_सं;
		cp = libbpf_म_त्रुटि_r(err, errmsg, माप(errmsg));
		pr_warn("Error setting initial map(%s) contents: %s\n",
			map->name, cp);
		वापस err;
	पूर्ण

	/* Freeze .rodata and .kconfig map as पढ़ो-only from syscall side. */
	अगर (map_type == LIBBPF_MAP_RODATA || map_type == LIBBPF_MAP_KCONFIG) अणु
		err = bpf_map_मुक्तze(map->fd);
		अगर (err) अणु
			err = -त्रुटि_सं;
			cp = libbpf_म_त्रुटि_r(err, errmsg, माप(errmsg));
			pr_warn("Error freezing map(%s) as read-only: %s\n",
				map->name, cp);
			वापस err;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम bpf_map__destroy(काष्ठा bpf_map *map);

अटल पूर्णांक bpf_object__create_map(काष्ठा bpf_object *obj, काष्ठा bpf_map *map)
अणु
	काष्ठा bpf_create_map_attr create_attr;
	काष्ठा bpf_map_def *def = &map->def;

	स_रखो(&create_attr, 0, माप(create_attr));

	अगर (kernel_supports(FEAT_PROG_NAME))
		create_attr.name = map->name;
	create_attr.map_अगरindex = map->map_अगरindex;
	create_attr.map_type = def->type;
	create_attr.map_flags = def->map_flags;
	create_attr.key_size = def->key_size;
	create_attr.value_size = def->value_size;
	create_attr.numa_node = map->numa_node;

	अगर (def->type == BPF_MAP_TYPE_PERF_EVENT_ARRAY && !def->max_entries) अणु
		पूर्णांक nr_cpus;

		nr_cpus = libbpf_num_possible_cpus();
		अगर (nr_cpus < 0) अणु
			pr_warn("map '%s': failed to determine number of system CPUs: %d\n",
				map->name, nr_cpus);
			वापस nr_cpus;
		पूर्ण
		pr_debug("map '%s': setting size to %d\n", map->name, nr_cpus);
		create_attr.max_entries = nr_cpus;
	पूर्ण अन्यथा अणु
		create_attr.max_entries = def->max_entries;
	पूर्ण

	अगर (bpf_map__is_काष्ठा_ops(map))
		create_attr.btf_vmlinux_value_type_id =
			map->btf_vmlinux_value_type_id;

	create_attr.btf_fd = 0;
	create_attr.btf_key_type_id = 0;
	create_attr.btf_value_type_id = 0;
	अगर (obj->btf && btf__fd(obj->btf) >= 0 && !bpf_map_find_btf_info(obj, map)) अणु
		create_attr.btf_fd = btf__fd(obj->btf);
		create_attr.btf_key_type_id = map->btf_key_type_id;
		create_attr.btf_value_type_id = map->btf_value_type_id;
	पूर्ण

	अगर (bpf_map_type__is_map_in_map(def->type)) अणु
		अगर (map->inner_map) अणु
			पूर्णांक err;

			err = bpf_object__create_map(obj, map->inner_map);
			अगर (err) अणु
				pr_warn("map '%s': failed to create inner map: %d\n",
					map->name, err);
				वापस err;
			पूर्ण
			map->inner_map_fd = bpf_map__fd(map->inner_map);
		पूर्ण
		अगर (map->inner_map_fd >= 0)
			create_attr.inner_map_fd = map->inner_map_fd;
	पूर्ण

	map->fd = bpf_create_map_xattr(&create_attr);
	अगर (map->fd < 0 && (create_attr.btf_key_type_id ||
			    create_attr.btf_value_type_id)) अणु
		अक्षर *cp, errmsg[STRERR_बफ_मानE];
		पूर्णांक err = -त्रुटि_सं;

		cp = libbpf_म_त्रुटि_r(err, errmsg, माप(errmsg));
		pr_warn("Error in bpf_create_map_xattr(%s):%s(%d). Retrying without BTF.\n",
			map->name, cp, err);
		create_attr.btf_fd = 0;
		create_attr.btf_key_type_id = 0;
		create_attr.btf_value_type_id = 0;
		map->btf_key_type_id = 0;
		map->btf_value_type_id = 0;
		map->fd = bpf_create_map_xattr(&create_attr);
	पूर्ण

	अगर (map->fd < 0)
		वापस -त्रुटि_सं;

	अगर (bpf_map_type__is_map_in_map(def->type) && map->inner_map) अणु
		bpf_map__destroy(map->inner_map);
		zमुक्त(&map->inner_map);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक init_map_slots(काष्ठा bpf_map *map)
अणु
	स्थिर काष्ठा bpf_map *targ_map;
	अचिन्हित पूर्णांक i;
	पूर्णांक fd, err;

	क्रम (i = 0; i < map->init_slots_sz; i++) अणु
		अगर (!map->init_slots[i])
			जारी;

		targ_map = map->init_slots[i];
		fd = bpf_map__fd(targ_map);
		err = bpf_map_update_elem(map->fd, &i, &fd, 0);
		अगर (err) अणु
			err = -त्रुटि_सं;
			pr_warn("map '%s': failed to initialize slot [%d] to map '%s' fd=%d: %d\n",
				map->name, i, targ_map->name,
				fd, err);
			वापस err;
		पूर्ण
		pr_debug("map '%s': slot [%d] set to map '%s' fd=%d\n",
			 map->name, i, targ_map->name, fd);
	पूर्ण

	zमुक्त(&map->init_slots);
	map->init_slots_sz = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक
bpf_object__create_maps(काष्ठा bpf_object *obj)
अणु
	काष्ठा bpf_map *map;
	अक्षर *cp, errmsg[STRERR_बफ_मानE];
	अचिन्हित पूर्णांक i, j;
	पूर्णांक err;

	क्रम (i = 0; i < obj->nr_maps; i++) अणु
		map = &obj->maps[i];

		अगर (map->pin_path) अणु
			err = bpf_object__reuse_map(map);
			अगर (err) अणु
				pr_warn("map '%s': error reusing pinned map\n",
					map->name);
				जाओ err_out;
			पूर्ण
		पूर्ण

		अगर (map->fd >= 0) अणु
			pr_debug("map '%s': skipping creation (preset fd=%d)\n",
				 map->name, map->fd);
		पूर्ण अन्यथा अणु
			err = bpf_object__create_map(obj, map);
			अगर (err)
				जाओ err_out;

			pr_debug("map '%s': created successfully, fd=%d\n",
				 map->name, map->fd);

			अगर (bpf_map__is_पूर्णांकernal(map)) अणु
				err = bpf_object__populate_पूर्णांकernal_map(obj, map);
				अगर (err < 0) अणु
					zबंद(map->fd);
					जाओ err_out;
				पूर्ण
			पूर्ण

			अगर (map->init_slots_sz) अणु
				err = init_map_slots(map);
				अगर (err < 0) अणु
					zबंद(map->fd);
					जाओ err_out;
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (map->pin_path && !map->pinned) अणु
			err = bpf_map__pin(map, शून्य);
			अगर (err) अणु
				pr_warn("map '%s': failed to auto-pin at '%s': %d\n",
					map->name, map->pin_path, err);
				zबंद(map->fd);
				जाओ err_out;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;

err_out:
	cp = libbpf_म_त्रुटि_r(err, errmsg, माप(errmsg));
	pr_warn("map '%s': failed to create: %s(%d)\n", map->name, cp, err);
	pr_perm_msg(err);
	क्रम (j = 0; j < i; j++)
		zबंद(obj->maps[j].fd);
	वापस err;
पूर्ण

#घोषणा BPF_CORE_SPEC_MAX_LEN 64

/* represents BPF CO-RE field or array element accessor */
काष्ठा bpf_core_accessor अणु
	__u32 type_id;		/* काष्ठा/जोड़ type or array element type */
	__u32 idx;		/* field index or array index */
	स्थिर अक्षर *name;	/* field name or शून्य क्रम array accessor */
पूर्ण;

काष्ठा bpf_core_spec अणु
	स्थिर काष्ठा btf *btf;
	/* high-level spec: named fields and array indices only */
	काष्ठा bpf_core_accessor spec[BPF_CORE_SPEC_MAX_LEN];
	/* original unresolved (no skip_mods_or_प्रकारs) root type ID */
	__u32 root_type_id;
	/* CO-RE relocation kind */
	क्रमागत bpf_core_relo_kind relo_kind;
	/* high-level spec length */
	पूर्णांक len;
	/* raw, low-level spec: 1-to-1 with accessor spec string */
	पूर्णांक raw_spec[BPF_CORE_SPEC_MAX_LEN];
	/* raw spec length */
	पूर्णांक raw_len;
	/* field bit offset represented by spec */
	__u32 bit_offset;
पूर्ण;

अटल bool str_is_empty(स्थिर अक्षर *s)
अणु
	वापस !s || !s[0];
पूर्ण

अटल bool is_flex_arr(स्थिर काष्ठा btf *btf,
			स्थिर काष्ठा bpf_core_accessor *acc,
			स्थिर काष्ठा btf_array *arr)
अणु
	स्थिर काष्ठा btf_type *t;

	/* not a flexible array, अगर not inside a काष्ठा or has non-zero size */
	अगर (!acc->name || arr->nelems > 0)
		वापस false;

	/* has to be the last member of enclosing काष्ठा */
	t = btf__type_by_id(btf, acc->type_id);
	वापस acc->idx == btf_vlen(t) - 1;
पूर्ण

अटल स्थिर अक्षर *core_relo_kind_str(क्रमागत bpf_core_relo_kind kind)
अणु
	चयन (kind) अणु
	हाल BPF_FIELD_BYTE_OFFSET: वापस "byte_off";
	हाल BPF_FIELD_BYTE_SIZE: वापस "byte_sz";
	हाल BPF_FIELD_EXISTS: वापस "field_exists";
	हाल BPF_FIELD_SIGNED: वापस "signed";
	हाल BPF_FIELD_LSHIFT_U64: वापस "lshift_u64";
	हाल BPF_FIELD_RSHIFT_U64: वापस "rshift_u64";
	हाल BPF_TYPE_ID_LOCAL: वापस "local_type_id";
	हाल BPF_TYPE_ID_TARGET: वापस "target_type_id";
	हाल BPF_TYPE_EXISTS: वापस "type_exists";
	हाल BPF_TYPE_SIZE: वापस "type_size";
	हाल BPF_ENUMVAL_EXISTS: वापस "enumval_exists";
	हाल BPF_ENUMVAL_VALUE: वापस "enumval_value";
	शेष: वापस "unknown";
	पूर्ण
पूर्ण

अटल bool core_relo_is_field_based(क्रमागत bpf_core_relo_kind kind)
अणु
	चयन (kind) अणु
	हाल BPF_FIELD_BYTE_OFFSET:
	हाल BPF_FIELD_BYTE_SIZE:
	हाल BPF_FIELD_EXISTS:
	हाल BPF_FIELD_SIGNED:
	हाल BPF_FIELD_LSHIFT_U64:
	हाल BPF_FIELD_RSHIFT_U64:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool core_relo_is_type_based(क्रमागत bpf_core_relo_kind kind)
अणु
	चयन (kind) अणु
	हाल BPF_TYPE_ID_LOCAL:
	हाल BPF_TYPE_ID_TARGET:
	हाल BPF_TYPE_EXISTS:
	हाल BPF_TYPE_SIZE:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool core_relo_is_क्रमागतval_based(क्रमागत bpf_core_relo_kind kind)
अणु
	चयन (kind) अणु
	हाल BPF_ENUMVAL_EXISTS:
	हाल BPF_ENUMVAL_VALUE:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

/*
 * Turn bpf_core_relo पूर्णांकo a low- and high-level spec representation,
 * validating correctness aदीर्घ the way, as well as calculating resulting
 * field bit offset, specअगरied by accessor string. Low-level spec captures
 * every single level of nestedness, including traversing anonymous
 * काष्ठा/जोड़ members. High-level one only captures semantically meaningful
 * "turning points": named fields and array indicies.
 * E.g., क्रम this हाल:
 *
 *   काष्ठा sample अणु
 *       पूर्णांक __unimportant;
 *       काष्ठा अणु
 *           पूर्णांक __1;
 *           पूर्णांक __2;
 *           पूर्णांक a[7];
 *       पूर्ण;
 *   पूर्ण;
 *
 *   काष्ठा sample *s = ...;
 *
 *   पूर्णांक x = &s->a[3]; // access string = '0:1:2:3'
 *
 * Low-level spec has 1:1 mapping with each element of access string (it's
 * just a parsed access string representation): [0, 1, 2, 3].
 *
 * High-level spec will capture only 3 poपूर्णांकs:
 *   - पूर्णांकial zero-index access by poपूर्णांकer (&s->... is the same as &s[0]...);
 *   - field 'a' access (corresponds to '2' in low-level spec);
 *   - array element #3 access (corresponds to '3' in low-level spec).
 *
 * Type-based relocations (TYPE_EXISTS/TYPE_SIZE,
 * TYPE_ID_LOCAL/TYPE_ID_TARGET) करोn't capture any field inक्रमmation. Their
 * spec and raw_spec are kept empty.
 *
 * Enum value-based relocations (ENUMVAL_EXISTS/ENUMVAL_VALUE) use access
 * string to specअगरy क्रमागतerator's value index that need to be relocated.
 */
अटल पूर्णांक bpf_core_parse_spec(स्थिर काष्ठा btf *btf,
			       __u32 type_id,
			       स्थिर अक्षर *spec_str,
			       क्रमागत bpf_core_relo_kind relo_kind,
			       काष्ठा bpf_core_spec *spec)
अणु
	पूर्णांक access_idx, parsed_len, i;
	काष्ठा bpf_core_accessor *acc;
	स्थिर काष्ठा btf_type *t;
	स्थिर अक्षर *name;
	__u32 id;
	__s64 sz;

	अगर (str_is_empty(spec_str) || *spec_str == ':')
		वापस -EINVAL;

	स_रखो(spec, 0, माप(*spec));
	spec->btf = btf;
	spec->root_type_id = type_id;
	spec->relo_kind = relo_kind;

	/* type-based relocations करोn't have a field access string */
	अगर (core_relo_is_type_based(relo_kind)) अणु
		अगर (म_भेद(spec_str, "0"))
			वापस -EINVAL;
		वापस 0;
	पूर्ण

	/* parse spec_str="0:1:2:3:4" पूर्णांकo array raw_spec=[0, 1, 2, 3, 4] */
	जबतक (*spec_str) अणु
		अगर (*spec_str == ':')
			++spec_str;
		अगर (माला_पूछो(spec_str, "%d%n", &access_idx, &parsed_len) != 1)
			वापस -EINVAL;
		अगर (spec->raw_len == BPF_CORE_SPEC_MAX_LEN)
			वापस -E2BIG;
		spec_str += parsed_len;
		spec->raw_spec[spec->raw_len++] = access_idx;
	पूर्ण

	अगर (spec->raw_len == 0)
		वापस -EINVAL;

	t = skip_mods_and_प्रकारs(btf, type_id, &id);
	अगर (!t)
		वापस -EINVAL;

	access_idx = spec->raw_spec[0];
	acc = &spec->spec[0];
	acc->type_id = id;
	acc->idx = access_idx;
	spec->len++;

	अगर (core_relo_is_क्रमागतval_based(relo_kind)) अणु
		अगर (!btf_is_क्रमागत(t) || spec->raw_len > 1 || access_idx >= btf_vlen(t))
			वापस -EINVAL;

		/* record क्रमागतerator name in a first accessor */
		acc->name = btf__name_by_offset(btf, btf_क्रमागत(t)[access_idx].name_off);
		वापस 0;
	पूर्ण

	अगर (!core_relo_is_field_based(relo_kind))
		वापस -EINVAL;

	sz = btf__resolve_size(btf, id);
	अगर (sz < 0)
		वापस sz;
	spec->bit_offset = access_idx * sz * 8;

	क्रम (i = 1; i < spec->raw_len; i++) अणु
		t = skip_mods_and_प्रकारs(btf, id, &id);
		अगर (!t)
			वापस -EINVAL;

		access_idx = spec->raw_spec[i];
		acc = &spec->spec[spec->len];

		अगर (btf_is_composite(t)) अणु
			स्थिर काष्ठा btf_member *m;
			__u32 bit_offset;

			अगर (access_idx >= btf_vlen(t))
				वापस -EINVAL;

			bit_offset = btf_member_bit_offset(t, access_idx);
			spec->bit_offset += bit_offset;

			m = btf_members(t) + access_idx;
			अगर (m->name_off) अणु
				name = btf__name_by_offset(btf, m->name_off);
				अगर (str_is_empty(name))
					वापस -EINVAL;

				acc->type_id = id;
				acc->idx = access_idx;
				acc->name = name;
				spec->len++;
			पूर्ण

			id = m->type;
		पूर्ण अन्यथा अगर (btf_is_array(t)) अणु
			स्थिर काष्ठा btf_array *a = btf_array(t);
			bool flex;

			t = skip_mods_and_प्रकारs(btf, a->type, &id);
			अगर (!t)
				वापस -EINVAL;

			flex = is_flex_arr(btf, acc - 1, a);
			अगर (!flex && access_idx >= a->nelems)
				वापस -EINVAL;

			spec->spec[spec->len].type_id = id;
			spec->spec[spec->len].idx = access_idx;
			spec->len++;

			sz = btf__resolve_size(btf, id);
			अगर (sz < 0)
				वापस sz;
			spec->bit_offset += access_idx * sz * 8;
		पूर्ण अन्यथा अणु
			pr_warn("relo for [%u] %s (at idx %d) captures type [%d] of unexpected kind %s\n",
				type_id, spec_str, i, id, btf_kind_str(t));
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल bool bpf_core_is_flavor_sep(स्थिर अक्षर *s)
अणु
	/* check X___Y name pattern, where X and Y are not underscores */
	वापस s[0] != '_' &&				      /* X */
	       s[1] == '_' && s[2] == '_' && s[3] == '_' &&   /* ___ */
	       s[4] != '_';				      /* Y */
पूर्ण

/* Given 'some_struct_name___with_flavor' वापस the length of a name prefix
 * beक्रमe last triple underscore. Struct name part after last triple
 * underscore is ignored by BPF CO-RE relocation during relocation matching.
 */
अटल माप_प्रकार bpf_core_essential_name_len(स्थिर अक्षर *name)
अणु
	माप_प्रकार n = म_माप(name);
	पूर्णांक i;

	क्रम (i = n - 5; i >= 0; i--) अणु
		अगर (bpf_core_is_flavor_sep(name + i))
			वापस i + 1;
	पूर्ण
	वापस n;
पूर्ण

काष्ठा core_cand
अणु
	स्थिर काष्ठा btf *btf;
	स्थिर काष्ठा btf_type *t;
	स्थिर अक्षर *name;
	__u32 id;
पूर्ण;

/* dynamically sized list of type IDs and its associated काष्ठा btf */
काष्ठा core_cand_list अणु
	काष्ठा core_cand *cands;
	पूर्णांक len;
पूर्ण;

अटल व्योम bpf_core_मुक्त_cands(काष्ठा core_cand_list *cands)
अणु
	मुक्त(cands->cands);
	मुक्त(cands);
पूर्ण

अटल पूर्णांक bpf_core_add_cands(काष्ठा core_cand *local_cand,
			      माप_प्रकार local_essent_len,
			      स्थिर काष्ठा btf *targ_btf,
			      स्थिर अक्षर *targ_btf_name,
			      पूर्णांक targ_start_id,
			      काष्ठा core_cand_list *cands)
अणु
	काष्ठा core_cand *new_cands, *cand;
	स्थिर काष्ठा btf_type *t;
	स्थिर अक्षर *targ_name;
	माप_प्रकार targ_essent_len;
	पूर्णांक n, i;

	n = btf__get_nr_types(targ_btf);
	क्रम (i = targ_start_id; i <= n; i++) अणु
		t = btf__type_by_id(targ_btf, i);
		अगर (btf_kind(t) != btf_kind(local_cand->t))
			जारी;

		targ_name = btf__name_by_offset(targ_btf, t->name_off);
		अगर (str_is_empty(targ_name))
			जारी;

		targ_essent_len = bpf_core_essential_name_len(targ_name);
		अगर (targ_essent_len != local_essent_len)
			जारी;

		अगर (म_भेदन(local_cand->name, targ_name, local_essent_len) != 0)
			जारी;

		pr_debug("CO-RE relocating [%d] %s %s: found target candidate [%d] %s %s in [%s]\n",
			 local_cand->id, btf_kind_str(local_cand->t),
			 local_cand->name, i, btf_kind_str(t), targ_name,
			 targ_btf_name);
		new_cands = libbpf_पुनः_स्मृतिarray(cands->cands, cands->len + 1,
					      माप(*cands->cands));
		अगर (!new_cands)
			वापस -ENOMEM;

		cand = &new_cands[cands->len];
		cand->btf = targ_btf;
		cand->t = t;
		cand->name = targ_name;
		cand->id = i;

		cands->cands = new_cands;
		cands->len++;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक load_module_btfs(काष्ठा bpf_object *obj)
अणु
	काष्ठा bpf_btf_info info;
	काष्ठा module_btf *mod_btf;
	काष्ठा btf *btf;
	अक्षर name[64];
	__u32 id = 0, len;
	पूर्णांक err, fd;

	अगर (obj->btf_modules_loaded)
		वापस 0;

	/* करोn't करो this again, even अगर we find no module BTFs */
	obj->btf_modules_loaded = true;

	/* kernel too old to support module BTFs */
	अगर (!kernel_supports(FEAT_MODULE_BTF))
		वापस 0;

	जबतक (true) अणु
		err = bpf_btf_get_next_id(id, &id);
		अगर (err && त्रुटि_सं == ENOENT)
			वापस 0;
		अगर (err) अणु
			err = -त्रुटि_सं;
			pr_warn("failed to iterate BTF objects: %d\n", err);
			वापस err;
		पूर्ण

		fd = bpf_btf_get_fd_by_id(id);
		अगर (fd < 0) अणु
			अगर (त्रुटि_सं == ENOENT)
				जारी; /* expected race: BTF was unloaded */
			err = -त्रुटि_सं;
			pr_warn("failed to get BTF object #%d FD: %d\n", id, err);
			वापस err;
		पूर्ण

		len = माप(info);
		स_रखो(&info, 0, माप(info));
		info.name = ptr_to_u64(name);
		info.name_len = माप(name);

		err = bpf_obj_get_info_by_fd(fd, &info, &len);
		अगर (err) अणु
			err = -त्रुटि_सं;
			pr_warn("failed to get BTF object #%d info: %d\n", id, err);
			जाओ err_out;
		पूर्ण

		/* ignore non-module BTFs */
		अगर (!info.kernel_btf || म_भेद(name, "vmlinux") == 0) अणु
			बंद(fd);
			जारी;
		पूर्ण

		btf = btf_get_from_fd(fd, obj->btf_vmlinux);
		अगर (IS_ERR(btf)) अणु
			pr_warn("failed to load module [%s]'s BTF object #%d: %ld\n",
				name, id, PTR_ERR(btf));
			err = PTR_ERR(btf);
			जाओ err_out;
		पूर्ण

		err = libbpf_ensure_mem((व्योम **)&obj->btf_modules, &obj->btf_module_cap,
				        माप(*obj->btf_modules), obj->btf_module_cnt + 1);
		अगर (err)
			जाओ err_out;

		mod_btf = &obj->btf_modules[obj->btf_module_cnt++];

		mod_btf->btf = btf;
		mod_btf->id = id;
		mod_btf->fd = fd;
		mod_btf->name = strdup(name);
		अगर (!mod_btf->name) अणु
			err = -ENOMEM;
			जाओ err_out;
		पूर्ण
		जारी;

err_out:
		बंद(fd);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा core_cand_list *
bpf_core_find_cands(काष्ठा bpf_object *obj, स्थिर काष्ठा btf *local_btf, __u32 local_type_id)
अणु
	काष्ठा core_cand local_cand = अणुपूर्ण;
	काष्ठा core_cand_list *cands;
	स्थिर काष्ठा btf *मुख्य_btf;
	माप_प्रकार local_essent_len;
	पूर्णांक err, i;

	local_cand.btf = local_btf;
	local_cand.t = btf__type_by_id(local_btf, local_type_id);
	अगर (!local_cand.t)
		वापस ERR_PTR(-EINVAL);

	local_cand.name = btf__name_by_offset(local_btf, local_cand.t->name_off);
	अगर (str_is_empty(local_cand.name))
		वापस ERR_PTR(-EINVAL);
	local_essent_len = bpf_core_essential_name_len(local_cand.name);

	cands = सुस्मृति(1, माप(*cands));
	अगर (!cands)
		वापस ERR_PTR(-ENOMEM);

	/* Attempt to find target candidates in vmlinux BTF first */
	मुख्य_btf = obj->btf_vmlinux_override ?: obj->btf_vmlinux;
	err = bpf_core_add_cands(&local_cand, local_essent_len, मुख्य_btf, "vmlinux", 1, cands);
	अगर (err)
		जाओ err_out;

	/* अगर vmlinux BTF has any candidate, करोn't got क्रम module BTFs */
	अगर (cands->len)
		वापस cands;

	/* अगर vmlinux BTF was overridden, करोn't attempt to load module BTFs */
	अगर (obj->btf_vmlinux_override)
		वापस cands;

	/* now look through module BTFs, trying to still find candidates */
	err = load_module_btfs(obj);
	अगर (err)
		जाओ err_out;

	क्रम (i = 0; i < obj->btf_module_cnt; i++) अणु
		err = bpf_core_add_cands(&local_cand, local_essent_len,
					 obj->btf_modules[i].btf,
					 obj->btf_modules[i].name,
					 btf__get_nr_types(obj->btf_vmlinux) + 1,
					 cands);
		अगर (err)
			जाओ err_out;
	पूर्ण

	वापस cands;
err_out:
	bpf_core_मुक्त_cands(cands);
	वापस ERR_PTR(err);
पूर्ण

/* Check two types क्रम compatibility क्रम the purpose of field access
 * relocation. स्थिर/अस्थिर/restrict and प्रकारs are skipped to ensure we
 * are relocating semantically compatible entities:
 *   - any two STRUCTs/UNIONs are compatible and can be mixed;
 *   - any two FWDs are compatible, अगर their names match (modulo flavor suffix);
 *   - any two PTRs are always compatible;
 *   - क्रम ENUMs, names should be the same (ignoring flavor suffix) or at
 *     least one of क्रमागतs should be anonymous;
 *   - क्रम ENUMs, check sizes, names are ignored;
 *   - क्रम INT, size and चिन्हितness are ignored;
 *   - any two FLOATs are always compatible;
 *   - क्रम ARRAY, dimensionality is ignored, element types are checked क्रम
 *     compatibility recursively;
 *   - everything अन्यथा shouldn't be ever a target of relocation.
 * These rules are not set in stone and probably will be adjusted as we get
 * more experience with using BPF CO-RE relocations.
 */
अटल पूर्णांक bpf_core_fields_are_compat(स्थिर काष्ठा btf *local_btf,
				      __u32 local_id,
				      स्थिर काष्ठा btf *targ_btf,
				      __u32 targ_id)
अणु
	स्थिर काष्ठा btf_type *local_type, *targ_type;

recur:
	local_type = skip_mods_and_प्रकारs(local_btf, local_id, &local_id);
	targ_type = skip_mods_and_प्रकारs(targ_btf, targ_id, &targ_id);
	अगर (!local_type || !targ_type)
		वापस -EINVAL;

	अगर (btf_is_composite(local_type) && btf_is_composite(targ_type))
		वापस 1;
	अगर (btf_kind(local_type) != btf_kind(targ_type))
		वापस 0;

	चयन (btf_kind(local_type)) अणु
	हाल BTF_KIND_PTR:
	हाल BTF_KIND_FLOAT:
		वापस 1;
	हाल BTF_KIND_FWD:
	हाल BTF_KIND_ENUM: अणु
		स्थिर अक्षर *local_name, *targ_name;
		माप_प्रकार local_len, targ_len;

		local_name = btf__name_by_offset(local_btf,
						 local_type->name_off);
		targ_name = btf__name_by_offset(targ_btf, targ_type->name_off);
		local_len = bpf_core_essential_name_len(local_name);
		targ_len = bpf_core_essential_name_len(targ_name);
		/* one of them is anonymous or both w/ same flavor-less names */
		वापस local_len == 0 || targ_len == 0 ||
		       (local_len == targ_len &&
			म_भेदन(local_name, targ_name, local_len) == 0);
	पूर्ण
	हाल BTF_KIND_INT:
		/* just reject deprecated bitfield-like पूर्णांकegers; all other
		 * पूर्णांकegers are by शेष compatible between each other
		 */
		वापस btf_पूर्णांक_offset(local_type) == 0 &&
		       btf_पूर्णांक_offset(targ_type) == 0;
	हाल BTF_KIND_ARRAY:
		local_id = btf_array(local_type)->type;
		targ_id = btf_array(targ_type)->type;
		जाओ recur;
	शेष:
		pr_warn("unexpected kind %d relocated, local [%d], target [%d]\n",
			btf_kind(local_type), local_id, targ_id);
		वापस 0;
	पूर्ण
पूर्ण

/*
 * Given single high-level named field accessor in local type, find
 * corresponding high-level accessor क्रम a target type. Aदीर्घ the way,
 * मुख्यtain low-level spec क्रम target as well. Also keep updating target
 * bit offset.
 *
 * Searching is perक्रमmed through recursive exhaustive क्रमागतeration of all
 * fields of a काष्ठा/जोड़. If there are any anonymous (embedded)
 * काष्ठाs/जोड़s, they are recursively searched as well. If field with
 * desired name is found, check compatibility between local and target types,
 * beक्रमe वापसing result.
 *
 * 1 is वापसed, अगर field is found.
 * 0 is वापसed अगर no compatible field is found.
 * <0 is वापसed on error.
 */
अटल पूर्णांक bpf_core_match_member(स्थिर काष्ठा btf *local_btf,
				 स्थिर काष्ठा bpf_core_accessor *local_acc,
				 स्थिर काष्ठा btf *targ_btf,
				 __u32 targ_id,
				 काष्ठा bpf_core_spec *spec,
				 __u32 *next_targ_id)
अणु
	स्थिर काष्ठा btf_type *local_type, *targ_type;
	स्थिर काष्ठा btf_member *local_member, *m;
	स्थिर अक्षर *local_name, *targ_name;
	__u32 local_id;
	पूर्णांक i, n, found;

	targ_type = skip_mods_and_प्रकारs(targ_btf, targ_id, &targ_id);
	अगर (!targ_type)
		वापस -EINVAL;
	अगर (!btf_is_composite(targ_type))
		वापस 0;

	local_id = local_acc->type_id;
	local_type = btf__type_by_id(local_btf, local_id);
	local_member = btf_members(local_type) + local_acc->idx;
	local_name = btf__name_by_offset(local_btf, local_member->name_off);

	n = btf_vlen(targ_type);
	m = btf_members(targ_type);
	क्रम (i = 0; i < n; i++, m++) अणु
		__u32 bit_offset;

		bit_offset = btf_member_bit_offset(targ_type, i);

		/* too deep काष्ठा/जोड़/array nesting */
		अगर (spec->raw_len == BPF_CORE_SPEC_MAX_LEN)
			वापस -E2BIG;

		/* speculate this member will be the good one */
		spec->bit_offset += bit_offset;
		spec->raw_spec[spec->raw_len++] = i;

		targ_name = btf__name_by_offset(targ_btf, m->name_off);
		अगर (str_is_empty(targ_name)) अणु
			/* embedded काष्ठा/जोड़, we need to go deeper */
			found = bpf_core_match_member(local_btf, local_acc,
						      targ_btf, m->type,
						      spec, next_targ_id);
			अगर (found) /* either found or error */
				वापस found;
		पूर्ण अन्यथा अगर (म_भेद(local_name, targ_name) == 0) अणु
			/* matching named field */
			काष्ठा bpf_core_accessor *targ_acc;

			targ_acc = &spec->spec[spec->len++];
			targ_acc->type_id = targ_id;
			targ_acc->idx = i;
			targ_acc->name = targ_name;

			*next_targ_id = m->type;
			found = bpf_core_fields_are_compat(local_btf,
							   local_member->type,
							   targ_btf, m->type);
			अगर (!found)
				spec->len--; /* pop accessor */
			वापस found;
		पूर्ण
		/* member turned out not to be what we looked क्रम */
		spec->bit_offset -= bit_offset;
		spec->raw_len--;
	पूर्ण

	वापस 0;
पूर्ण

/* Check local and target types क्रम compatibility. This check is used क्रम
 * type-based CO-RE relocations and follow slightly dअगरferent rules than
 * field-based relocations. This function assumes that root types were alपढ़ोy
 * checked क्रम name match. Beyond that initial root-level name check, names
 * are completely ignored. Compatibility rules are as follows:
 *   - any two STRUCTs/UNIONs/FWDs/ENUMs/INTs are considered compatible, but
 *     kind should match क्रम local and target types (i.e., STRUCT is not
 *     compatible with UNION);
 *   - क्रम ENUMs, the size is ignored;
 *   - क्रम INT, size and चिन्हितness are ignored;
 *   - क्रम ARRAY, dimensionality is ignored, element types are checked क्रम
 *     compatibility recursively;
 *   - CONST/VOLATILE/RESTRICT modअगरiers are ignored;
 *   - TYPEDEFs/PTRs are compatible अगर types they poपूर्णांकing to are compatible;
 *   - FUNC_PROTOs are compatible अगर they have compatible signature: same
 *     number of input args and compatible वापस and argument types.
 * These rules are not set in stone and probably will be adjusted as we get
 * more experience with using BPF CO-RE relocations.
 */
अटल पूर्णांक bpf_core_types_are_compat(स्थिर काष्ठा btf *local_btf, __u32 local_id,
				     स्थिर काष्ठा btf *targ_btf, __u32 targ_id)
अणु
	स्थिर काष्ठा btf_type *local_type, *targ_type;
	पूर्णांक depth = 32; /* max recursion depth */

	/* caller made sure that names match (ignoring flavor suffix) */
	local_type = btf__type_by_id(local_btf, local_id);
	targ_type = btf__type_by_id(targ_btf, targ_id);
	अगर (btf_kind(local_type) != btf_kind(targ_type))
		वापस 0;

recur:
	depth--;
	अगर (depth < 0)
		वापस -EINVAL;

	local_type = skip_mods_and_प्रकारs(local_btf, local_id, &local_id);
	targ_type = skip_mods_and_प्रकारs(targ_btf, targ_id, &targ_id);
	अगर (!local_type || !targ_type)
		वापस -EINVAL;

	अगर (btf_kind(local_type) != btf_kind(targ_type))
		वापस 0;

	चयन (btf_kind(local_type)) अणु
	हाल BTF_KIND_UNKN:
	हाल BTF_KIND_STRUCT:
	हाल BTF_KIND_UNION:
	हाल BTF_KIND_ENUM:
	हाल BTF_KIND_FWD:
		वापस 1;
	हाल BTF_KIND_INT:
		/* just reject deprecated bitfield-like पूर्णांकegers; all other
		 * पूर्णांकegers are by शेष compatible between each other
		 */
		वापस btf_पूर्णांक_offset(local_type) == 0 && btf_पूर्णांक_offset(targ_type) == 0;
	हाल BTF_KIND_PTR:
		local_id = local_type->type;
		targ_id = targ_type->type;
		जाओ recur;
	हाल BTF_KIND_ARRAY:
		local_id = btf_array(local_type)->type;
		targ_id = btf_array(targ_type)->type;
		जाओ recur;
	हाल BTF_KIND_FUNC_PROTO: अणु
		काष्ठा btf_param *local_p = btf_params(local_type);
		काष्ठा btf_param *targ_p = btf_params(targ_type);
		__u16 local_vlen = btf_vlen(local_type);
		__u16 targ_vlen = btf_vlen(targ_type);
		पूर्णांक i, err;

		अगर (local_vlen != targ_vlen)
			वापस 0;

		क्रम (i = 0; i < local_vlen; i++, local_p++, targ_p++) अणु
			skip_mods_and_प्रकारs(local_btf, local_p->type, &local_id);
			skip_mods_and_प्रकारs(targ_btf, targ_p->type, &targ_id);
			err = bpf_core_types_are_compat(local_btf, local_id, targ_btf, targ_id);
			अगर (err <= 0)
				वापस err;
		पूर्ण

		/* tail recurse क्रम वापस type check */
		skip_mods_and_प्रकारs(local_btf, local_type->type, &local_id);
		skip_mods_and_प्रकारs(targ_btf, targ_type->type, &targ_id);
		जाओ recur;
	पूर्ण
	शेष:
		pr_warn("unexpected kind %s relocated, local [%d], target [%d]\n",
			btf_kind_str(local_type), local_id, targ_id);
		वापस 0;
	पूर्ण
पूर्ण

/*
 * Try to match local spec to a target type and, अगर successful, produce full
 * target spec (high-level, low-level + bit offset).
 */
अटल पूर्णांक bpf_core_spec_match(काष्ठा bpf_core_spec *local_spec,
			       स्थिर काष्ठा btf *targ_btf, __u32 targ_id,
			       काष्ठा bpf_core_spec *targ_spec)
अणु
	स्थिर काष्ठा btf_type *targ_type;
	स्थिर काष्ठा bpf_core_accessor *local_acc;
	काष्ठा bpf_core_accessor *targ_acc;
	पूर्णांक i, sz, matched;

	स_रखो(targ_spec, 0, माप(*targ_spec));
	targ_spec->btf = targ_btf;
	targ_spec->root_type_id = targ_id;
	targ_spec->relo_kind = local_spec->relo_kind;

	अगर (core_relo_is_type_based(local_spec->relo_kind)) अणु
		वापस bpf_core_types_are_compat(local_spec->btf,
						 local_spec->root_type_id,
						 targ_btf, targ_id);
	पूर्ण

	local_acc = &local_spec->spec[0];
	targ_acc = &targ_spec->spec[0];

	अगर (core_relo_is_क्रमागतval_based(local_spec->relo_kind)) अणु
		माप_प्रकार local_essent_len, targ_essent_len;
		स्थिर काष्ठा btf_क्रमागत *e;
		स्थिर अक्षर *targ_name;

		/* has to resolve to an क्रमागत */
		targ_type = skip_mods_and_प्रकारs(targ_spec->btf, targ_id, &targ_id);
		अगर (!btf_is_क्रमागत(targ_type))
			वापस 0;

		local_essent_len = bpf_core_essential_name_len(local_acc->name);

		क्रम (i = 0, e = btf_क्रमागत(targ_type); i < btf_vlen(targ_type); i++, e++) अणु
			targ_name = btf__name_by_offset(targ_spec->btf, e->name_off);
			targ_essent_len = bpf_core_essential_name_len(targ_name);
			अगर (targ_essent_len != local_essent_len)
				जारी;
			अगर (म_भेदन(local_acc->name, targ_name, local_essent_len) == 0) अणु
				targ_acc->type_id = targ_id;
				targ_acc->idx = i;
				targ_acc->name = targ_name;
				targ_spec->len++;
				targ_spec->raw_spec[targ_spec->raw_len] = targ_acc->idx;
				targ_spec->raw_len++;
				वापस 1;
			पूर्ण
		पूर्ण
		वापस 0;
	पूर्ण

	अगर (!core_relo_is_field_based(local_spec->relo_kind))
		वापस -EINVAL;

	क्रम (i = 0; i < local_spec->len; i++, local_acc++, targ_acc++) अणु
		targ_type = skip_mods_and_प्रकारs(targ_spec->btf, targ_id,
						   &targ_id);
		अगर (!targ_type)
			वापस -EINVAL;

		अगर (local_acc->name) अणु
			matched = bpf_core_match_member(local_spec->btf,
							local_acc,
							targ_btf, targ_id,
							targ_spec, &targ_id);
			अगर (matched <= 0)
				वापस matched;
		पूर्ण अन्यथा अणु
			/* क्रम i=0, targ_id is alपढ़ोy treated as array element
			 * type (because it's the original काष्ठा), क्रम others
			 * we should find array element type first
			 */
			अगर (i > 0) अणु
				स्थिर काष्ठा btf_array *a;
				bool flex;

				अगर (!btf_is_array(targ_type))
					वापस 0;

				a = btf_array(targ_type);
				flex = is_flex_arr(targ_btf, targ_acc - 1, a);
				अगर (!flex && local_acc->idx >= a->nelems)
					वापस 0;
				अगर (!skip_mods_and_प्रकारs(targ_btf, a->type,
							    &targ_id))
					वापस -EINVAL;
			पूर्ण

			/* too deep काष्ठा/जोड़/array nesting */
			अगर (targ_spec->raw_len == BPF_CORE_SPEC_MAX_LEN)
				वापस -E2BIG;

			targ_acc->type_id = targ_id;
			targ_acc->idx = local_acc->idx;
			targ_acc->name = शून्य;
			targ_spec->len++;
			targ_spec->raw_spec[targ_spec->raw_len] = targ_acc->idx;
			targ_spec->raw_len++;

			sz = btf__resolve_size(targ_btf, targ_id);
			अगर (sz < 0)
				वापस sz;
			targ_spec->bit_offset += local_acc->idx * sz * 8;
		पूर्ण
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक bpf_core_calc_field_relo(स्थिर काष्ठा bpf_program *prog,
				    स्थिर काष्ठा bpf_core_relo *relo,
				    स्थिर काष्ठा bpf_core_spec *spec,
				    __u32 *val, __u32 *field_sz, __u32 *type_id,
				    bool *validate)
अणु
	स्थिर काष्ठा bpf_core_accessor *acc;
	स्थिर काष्ठा btf_type *t;
	__u32 byte_off, byte_sz, bit_off, bit_sz, field_type_id;
	स्थिर काष्ठा btf_member *m;
	स्थिर काष्ठा btf_type *mt;
	bool bitfield;
	__s64 sz;

	*field_sz = 0;

	अगर (relo->kind == BPF_FIELD_EXISTS) अणु
		*val = spec ? 1 : 0;
		वापस 0;
	पूर्ण

	अगर (!spec)
		वापस -EUCLEAN; /* request inकाष्ठाion poisoning */

	acc = &spec->spec[spec->len - 1];
	t = btf__type_by_id(spec->btf, acc->type_id);

	/* a[n] accessor needs special handling */
	अगर (!acc->name) अणु
		अगर (relo->kind == BPF_FIELD_BYTE_OFFSET) अणु
			*val = spec->bit_offset / 8;
			/* remember field size क्रम load/store mem size */
			sz = btf__resolve_size(spec->btf, acc->type_id);
			अगर (sz < 0)
				वापस -EINVAL;
			*field_sz = sz;
			*type_id = acc->type_id;
		पूर्ण अन्यथा अगर (relo->kind == BPF_FIELD_BYTE_SIZE) अणु
			sz = btf__resolve_size(spec->btf, acc->type_id);
			अगर (sz < 0)
				वापस -EINVAL;
			*val = sz;
		पूर्ण अन्यथा अणु
			pr_warn("prog '%s': relo %d at insn #%d can't be applied to array access\n",
				prog->name, relo->kind, relo->insn_off / 8);
			वापस -EINVAL;
		पूर्ण
		अगर (validate)
			*validate = true;
		वापस 0;
	पूर्ण

	m = btf_members(t) + acc->idx;
	mt = skip_mods_and_प्रकारs(spec->btf, m->type, &field_type_id);
	bit_off = spec->bit_offset;
	bit_sz = btf_member_bitfield_size(t, acc->idx);

	bitfield = bit_sz > 0;
	अगर (bitfield) अणु
		byte_sz = mt->size;
		byte_off = bit_off / 8 / byte_sz * byte_sz;
		/* figure out smallest पूर्णांक size necessary क्रम bitfield load */
		जबतक (bit_off + bit_sz - byte_off * 8 > byte_sz * 8) अणु
			अगर (byte_sz >= 8) अणु
				/* bitfield can't be पढ़ो with 64-bit पढ़ो */
				pr_warn("prog '%s': relo %d at insn #%d can't be satisfied for bitfield\n",
					prog->name, relo->kind, relo->insn_off / 8);
				वापस -E2BIG;
			पूर्ण
			byte_sz *= 2;
			byte_off = bit_off / 8 / byte_sz * byte_sz;
		पूर्ण
	पूर्ण अन्यथा अणु
		sz = btf__resolve_size(spec->btf, field_type_id);
		अगर (sz < 0)
			वापस -EINVAL;
		byte_sz = sz;
		byte_off = spec->bit_offset / 8;
		bit_sz = byte_sz * 8;
	पूर्ण

	/* क्रम bitfields, all the relocatable aspects are ambiguous and we
	 * might disagree with compiler, so turn off validation of expected
	 * value, except क्रम चिन्हितness
	 */
	अगर (validate)
		*validate = !bitfield;

	चयन (relo->kind) अणु
	हाल BPF_FIELD_BYTE_OFFSET:
		*val = byte_off;
		अगर (!bitfield) अणु
			*field_sz = byte_sz;
			*type_id = field_type_id;
		पूर्ण
		अवरोध;
	हाल BPF_FIELD_BYTE_SIZE:
		*val = byte_sz;
		अवरोध;
	हाल BPF_FIELD_SIGNED:
		/* क्रमागतs will be assumed अचिन्हित */
		*val = btf_is_क्रमागत(mt) ||
		       (btf_पूर्णांक_encoding(mt) & BTF_INT_SIGNED);
		अगर (validate)
			*validate = true; /* चिन्हितness is never ambiguous */
		अवरोध;
	हाल BPF_FIELD_LSHIFT_U64:
#अगर __BYTE_ORDER == __LITTLE_ENDIAN
		*val = 64 - (bit_off + bit_sz - byte_off  * 8);
#अन्यथा
		*val = (8 - byte_sz) * 8 + (bit_off - byte_off * 8);
#पूर्ण_अगर
		अवरोध;
	हाल BPF_FIELD_RSHIFT_U64:
		*val = 64 - bit_sz;
		अगर (validate)
			*validate = true; /* right shअगरt is never ambiguous */
		अवरोध;
	हाल BPF_FIELD_EXISTS:
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bpf_core_calc_type_relo(स्थिर काष्ठा bpf_core_relo *relo,
				   स्थिर काष्ठा bpf_core_spec *spec,
				   __u32 *val)
अणु
	__s64 sz;

	/* type-based relos वापस zero when target type is not found */
	अगर (!spec) अणु
		*val = 0;
		वापस 0;
	पूर्ण

	चयन (relo->kind) अणु
	हाल BPF_TYPE_ID_TARGET:
		*val = spec->root_type_id;
		अवरोध;
	हाल BPF_TYPE_EXISTS:
		*val = 1;
		अवरोध;
	हाल BPF_TYPE_SIZE:
		sz = btf__resolve_size(spec->btf, spec->root_type_id);
		अगर (sz < 0)
			वापस -EINVAL;
		*val = sz;
		अवरोध;
	हाल BPF_TYPE_ID_LOCAL:
	/* BPF_TYPE_ID_LOCAL is handled specially and shouldn't get here */
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bpf_core_calc_क्रमागतval_relo(स्थिर काष्ठा bpf_core_relo *relo,
				      स्थिर काष्ठा bpf_core_spec *spec,
				      __u32 *val)
अणु
	स्थिर काष्ठा btf_type *t;
	स्थिर काष्ठा btf_क्रमागत *e;

	चयन (relo->kind) अणु
	हाल BPF_ENUMVAL_EXISTS:
		*val = spec ? 1 : 0;
		अवरोध;
	हाल BPF_ENUMVAL_VALUE:
		अगर (!spec)
			वापस -EUCLEAN; /* request inकाष्ठाion poisoning */
		t = btf__type_by_id(spec->btf, spec->spec[0].type_id);
		e = btf_क्रमागत(t) + spec->spec[0].idx;
		*val = e->val;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा bpf_core_relo_res
अणु
	/* expected value in the inकाष्ठाion, unless validate == false */
	__u32 orig_val;
	/* new value that needs to be patched up to */
	__u32 new_val;
	/* relocation unsuccessful, poison inकाष्ठाion, but करोn't fail load */
	bool poison;
	/* some relocations can't be validated against orig_val */
	bool validate;
	/* क्रम field byte offset relocations or the क्रमms:
	 *     *(T *)(rX + <off>) = rY
	 *     rX = *(T *)(rY + <off>),
	 * we remember original and resolved field size to adjust direct
	 * memory loads of poपूर्णांकers and पूर्णांकegers; this is necessary क्रम 32-bit
	 * host kernel architectures, but also allows to स्वतःmatically
	 * relocate fields that were resized from, e.g., u32 to u64, etc.
	 */
	bool fail_memsz_adjust;
	__u32 orig_sz;
	__u32 orig_type_id;
	__u32 new_sz;
	__u32 new_type_id;
पूर्ण;

/* Calculate original and target relocation values, given local and target
 * specs and relocation kind. These values are calculated क्रम each candidate.
 * If there are multiple candidates, resulting values should all be consistent
 * with each other. Otherwise, libbpf will refuse to proceed due to ambiguity.
 * If inकाष्ठाion has to be poisoned, *poison will be set to true.
 */
अटल पूर्णांक bpf_core_calc_relo(स्थिर काष्ठा bpf_program *prog,
			      स्थिर काष्ठा bpf_core_relo *relo,
			      पूर्णांक relo_idx,
			      स्थिर काष्ठा bpf_core_spec *local_spec,
			      स्थिर काष्ठा bpf_core_spec *targ_spec,
			      काष्ठा bpf_core_relo_res *res)
अणु
	पूर्णांक err = -EOPNOTSUPP;

	res->orig_val = 0;
	res->new_val = 0;
	res->poison = false;
	res->validate = true;
	res->fail_memsz_adjust = false;
	res->orig_sz = res->new_sz = 0;
	res->orig_type_id = res->new_type_id = 0;

	अगर (core_relo_is_field_based(relo->kind)) अणु
		err = bpf_core_calc_field_relo(prog, relo, local_spec,
					       &res->orig_val, &res->orig_sz,
					       &res->orig_type_id, &res->validate);
		err = err ?: bpf_core_calc_field_relo(prog, relo, targ_spec,
						      &res->new_val, &res->new_sz,
						      &res->new_type_id, शून्य);
		अगर (err)
			जाओ करोne;
		/* Validate अगर it's safe to adjust load/store memory size.
		 * Adjusपंचांगents are perक्रमmed only अगर original and new memory
		 * sizes dअगरfer.
		 */
		res->fail_memsz_adjust = false;
		अगर (res->orig_sz != res->new_sz) अणु
			स्थिर काष्ठा btf_type *orig_t, *new_t;

			orig_t = btf__type_by_id(local_spec->btf, res->orig_type_id);
			new_t = btf__type_by_id(targ_spec->btf, res->new_type_id);

			/* There are two use हालs in which it's safe to
			 * adjust load/store's mem size:
			 *   - पढ़ोing a 32-bit kernel poपूर्णांकer, जबतक on BPF
			 *   size poपूर्णांकers are always 64-bit; in this हाल
			 *   it's safe to "downsize" inकाष्ठाion size due to
			 *   poपूर्णांकer being treated as अचिन्हित पूर्णांकeger with
			 *   zero-extended upper 32-bits;
			 *   - पढ़ोing अचिन्हित पूर्णांकegers, again due to
			 *   zero-extension is preserving the value correctly.
			 *
			 * In all other हालs it's incorrect to attempt to
			 * load/store field because पढ़ो value will be
			 * incorrect, so we poison relocated inकाष्ठाion.
			 */
			अगर (btf_is_ptr(orig_t) && btf_is_ptr(new_t))
				जाओ करोne;
			अगर (btf_is_पूर्णांक(orig_t) && btf_is_पूर्णांक(new_t) &&
			    btf_पूर्णांक_encoding(orig_t) != BTF_INT_SIGNED &&
			    btf_पूर्णांक_encoding(new_t) != BTF_INT_SIGNED)
				जाओ करोne;

			/* mark as invalid mem size adjusपंचांगent, but this will
			 * only be checked क्रम LDX/STX/ST insns
			 */
			res->fail_memsz_adjust = true;
		पूर्ण
	पूर्ण अन्यथा अगर (core_relo_is_type_based(relo->kind)) अणु
		err = bpf_core_calc_type_relo(relo, local_spec, &res->orig_val);
		err = err ?: bpf_core_calc_type_relo(relo, targ_spec, &res->new_val);
	पूर्ण अन्यथा अगर (core_relo_is_क्रमागतval_based(relo->kind)) अणु
		err = bpf_core_calc_क्रमागतval_relo(relo, local_spec, &res->orig_val);
		err = err ?: bpf_core_calc_क्रमागतval_relo(relo, targ_spec, &res->new_val);
	पूर्ण

करोne:
	अगर (err == -EUCLEAN) अणु
		/* EUCLEAN is used to संकेत inकाष्ठाion poisoning request */
		res->poison = true;
		err = 0;
	पूर्ण अन्यथा अगर (err == -EOPNOTSUPP) अणु
		/* EOPNOTSUPP means unknown/unsupported relocation */
		pr_warn("prog '%s': relo #%d: unrecognized CO-RE relocation %s (%d) at insn #%d\n",
			prog->name, relo_idx, core_relo_kind_str(relo->kind),
			relo->kind, relo->insn_off / 8);
	पूर्ण

	वापस err;
पूर्ण

/*
 * Turn inकाष्ठाion क्रम which CO_RE relocation failed पूर्णांकo invalid one with
 * distinct signature.
 */
अटल व्योम bpf_core_poison_insn(काष्ठा bpf_program *prog, पूर्णांक relo_idx,
				 पूर्णांक insn_idx, काष्ठा bpf_insn *insn)
अणु
	pr_debug("prog '%s': relo #%d: substituting insn #%d w/ invalid insn\n",
		 prog->name, relo_idx, insn_idx);
	insn->code = BPF_JMP | BPF_CALL;
	insn->dst_reg = 0;
	insn->src_reg = 0;
	insn->off = 0;
	/* अगर this inकाष्ठाion is reachable (not a dead code),
	 * verअगरier will complain with the following message:
	 * invalid func unknown#195896080
	 */
	insn->imm = 195896080; /* => 0xbad2310 => "bad relo" */
पूर्ण

अटल पूर्णांक insn_bpf_माप_प्रकारo_bytes(काष्ठा bpf_insn *insn)
अणु
	चयन (BPF_SIZE(insn->code)) अणु
	हाल BPF_DW: वापस 8;
	हाल BPF_W: वापस 4;
	हाल BPF_H: वापस 2;
	हाल BPF_B: वापस 1;
	शेष: वापस -1;
	पूर्ण
पूर्ण

अटल पूर्णांक insn_bytes_to_bpf_size(__u32 sz)
अणु
	चयन (sz) अणु
	हाल 8: वापस BPF_DW;
	हाल 4: वापस BPF_W;
	हाल 2: वापस BPF_H;
	हाल 1: वापस BPF_B;
	शेष: वापस -1;
	पूर्ण
पूर्ण

/*
 * Patch relocatable BPF inकाष्ठाion.
 *
 * Patched value is determined by relocation kind and target specअगरication.
 * For existence relocations target spec will be शून्य अगर field/type is not found.
 * Expected insn->imm value is determined using relocation kind and local
 * spec, and is checked beक्रमe patching inकाष्ठाion. If actual insn->imm value
 * is wrong, bail out with error.
 *
 * Currently supported classes of BPF inकाष्ठाion are:
 * 1. rX = <imm> (assignment with immediate opeअक्रम);
 * 2. rX += <imm> (arithmetic operations with immediate opeअक्रम);
 * 3. rX = <imm64> (load with 64-bit immediate value);
 * 4. rX = *(T *)(rY + <off>), where T is one of अणुu8, u16, u32, u64पूर्ण;
 * 5. *(T *)(rX + <off>) = rY, where T is one of अणुu8, u16, u32, u64पूर्ण;
 * 6. *(T *)(rX + <off>) = <imm>, where T is one of अणुu8, u16, u32, u64पूर्ण.
 */
अटल पूर्णांक bpf_core_patch_insn(काष्ठा bpf_program *prog,
			       स्थिर काष्ठा bpf_core_relo *relo,
			       पूर्णांक relo_idx,
			       स्थिर काष्ठा bpf_core_relo_res *res)
अणु
	__u32 orig_val, new_val;
	काष्ठा bpf_insn *insn;
	पूर्णांक insn_idx;
	__u8 class;

	अगर (relo->insn_off % BPF_INSN_SZ)
		वापस -EINVAL;
	insn_idx = relo->insn_off / BPF_INSN_SZ;
	/* adjust insn_idx from section frame of reference to the local
	 * program's frame of reference; (sub-)program code is not yet
	 * relocated, so it's enough to just subtract in-section offset
	 */
	insn_idx = insn_idx - prog->sec_insn_off;
	insn = &prog->insns[insn_idx];
	class = BPF_CLASS(insn->code);

	अगर (res->poison) अणु
poison:
		/* poison second part of ldimm64 to aव्योम confusing error from
		 * verअगरier about "unknown opcode 00"
		 */
		अगर (is_ldimm64_insn(insn))
			bpf_core_poison_insn(prog, relo_idx, insn_idx + 1, insn + 1);
		bpf_core_poison_insn(prog, relo_idx, insn_idx, insn);
		वापस 0;
	पूर्ण

	orig_val = res->orig_val;
	new_val = res->new_val;

	चयन (class) अणु
	हाल BPF_ALU:
	हाल BPF_ALU64:
		अगर (BPF_SRC(insn->code) != BPF_K)
			वापस -EINVAL;
		अगर (res->validate && insn->imm != orig_val) अणु
			pr_warn("prog '%s': relo #%d: unexpected insn #%d (ALU/ALU64) value: got %u, exp %u -> %u\n",
				prog->name, relo_idx,
				insn_idx, insn->imm, orig_val, new_val);
			वापस -EINVAL;
		पूर्ण
		orig_val = insn->imm;
		insn->imm = new_val;
		pr_debug("prog '%s': relo #%d: patched insn #%d (ALU/ALU64) imm %u -> %u\n",
			 prog->name, relo_idx, insn_idx,
			 orig_val, new_val);
		अवरोध;
	हाल BPF_LDX:
	हाल BPF_ST:
	हाल BPF_STX:
		अगर (res->validate && insn->off != orig_val) अणु
			pr_warn("prog '%s': relo #%d: unexpected insn #%d (LDX/ST/STX) value: got %u, exp %u -> %u\n",
				prog->name, relo_idx, insn_idx, insn->off, orig_val, new_val);
			वापस -EINVAL;
		पूर्ण
		अगर (new_val > लघु_उच्च) अणु
			pr_warn("prog '%s': relo #%d: insn #%d (LDX/ST/STX) value too big: %u\n",
				prog->name, relo_idx, insn_idx, new_val);
			वापस -दुस्फल;
		पूर्ण
		अगर (res->fail_memsz_adjust) अणु
			pr_warn("prog '%s': relo #%d: insn #%d (LDX/ST/STX) accesses field incorrectly. "
				"Make sure you are accessing pointers, unsigned integers, or fields of matching type and size.\n",
				prog->name, relo_idx, insn_idx);
			जाओ poison;
		पूर्ण

		orig_val = insn->off;
		insn->off = new_val;
		pr_debug("prog '%s': relo #%d: patched insn #%d (LDX/ST/STX) off %u -> %u\n",
			 prog->name, relo_idx, insn_idx, orig_val, new_val);

		अगर (res->new_sz != res->orig_sz) अणु
			पूर्णांक insn_bytes_sz, insn_bpf_sz;

			insn_bytes_sz = insn_bpf_माप_प्रकारo_bytes(insn);
			अगर (insn_bytes_sz != res->orig_sz) अणु
				pr_warn("prog '%s': relo #%d: insn #%d (LDX/ST/STX) unexpected mem size: got %d, exp %u\n",
					prog->name, relo_idx, insn_idx, insn_bytes_sz, res->orig_sz);
				वापस -EINVAL;
			पूर्ण

			insn_bpf_sz = insn_bytes_to_bpf_size(res->new_sz);
			अगर (insn_bpf_sz < 0) अणु
				pr_warn("prog '%s': relo #%d: insn #%d (LDX/ST/STX) invalid new mem size: %u\n",
					prog->name, relo_idx, insn_idx, res->new_sz);
				वापस -EINVAL;
			पूर्ण

			insn->code = BPF_MODE(insn->code) | insn_bpf_sz | BPF_CLASS(insn->code);
			pr_debug("prog '%s': relo #%d: patched insn #%d (LDX/ST/STX) mem_sz %u -> %u\n",
				 prog->name, relo_idx, insn_idx, res->orig_sz, res->new_sz);
		पूर्ण
		अवरोध;
	हाल BPF_LD: अणु
		__u64 imm;

		अगर (!is_ldimm64_insn(insn) ||
		    insn[0].src_reg != 0 || insn[0].off != 0 ||
		    insn_idx + 1 >= prog->insns_cnt ||
		    insn[1].code != 0 || insn[1].dst_reg != 0 ||
		    insn[1].src_reg != 0 || insn[1].off != 0) अणु
			pr_warn("prog '%s': relo #%d: insn #%d (LDIMM64) has unexpected form\n",
				prog->name, relo_idx, insn_idx);
			वापस -EINVAL;
		पूर्ण

		imm = insn[0].imm + ((__u64)insn[1].imm << 32);
		अगर (res->validate && imm != orig_val) अणु
			pr_warn("prog '%s': relo #%d: unexpected insn #%d (LDIMM64) value: got %llu, exp %u -> %u\n",
				prog->name, relo_idx,
				insn_idx, (अचिन्हित दीर्घ दीर्घ)imm,
				orig_val, new_val);
			वापस -EINVAL;
		पूर्ण

		insn[0].imm = new_val;
		insn[1].imm = 0; /* currently only 32-bit values are supported */
		pr_debug("prog '%s': relo #%d: patched insn #%d (LDIMM64) imm64 %llu -> %u\n",
			 prog->name, relo_idx, insn_idx,
			 (अचिन्हित दीर्घ दीर्घ)imm, new_val);
		अवरोध;
	पूर्ण
	शेष:
		pr_warn("prog '%s': relo #%d: trying to relocate unrecognized insn #%d, code:0x%x, src:0x%x, dst:0x%x, off:0x%x, imm:0x%x\n",
			prog->name, relo_idx, insn_idx, insn->code,
			insn->src_reg, insn->dst_reg, insn->off, insn->imm);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* Output spec definition in the क्रमmat:
 * [<type-id>] (<type-name>) + <raw-spec> => <offset>@<spec>,
 * where <spec> is a C-syntax view of recorded field access, e.g.: x.a[3].b
 */
अटल व्योम bpf_core_dump_spec(पूर्णांक level, स्थिर काष्ठा bpf_core_spec *spec)
अणु
	स्थिर काष्ठा btf_type *t;
	स्थिर काष्ठा btf_क्रमागत *e;
	स्थिर अक्षर *s;
	__u32 type_id;
	पूर्णांक i;

	type_id = spec->root_type_id;
	t = btf__type_by_id(spec->btf, type_id);
	s = btf__name_by_offset(spec->btf, t->name_off);

	libbpf_prपूर्णांक(level, "[%u] %s %s", type_id, btf_kind_str(t), str_is_empty(s) ? "<anon>" : s);

	अगर (core_relo_is_type_based(spec->relo_kind))
		वापस;

	अगर (core_relo_is_क्रमागतval_based(spec->relo_kind)) अणु
		t = skip_mods_and_प्रकारs(spec->btf, type_id, शून्य);
		e = btf_क्रमागत(t) + spec->raw_spec[0];
		s = btf__name_by_offset(spec->btf, e->name_off);

		libbpf_prपूर्णांक(level, "::%s = %u", s, e->val);
		वापस;
	पूर्ण

	अगर (core_relo_is_field_based(spec->relo_kind)) अणु
		क्रम (i = 0; i < spec->len; i++) अणु
			अगर (spec->spec[i].name)
				libbpf_prपूर्णांक(level, ".%s", spec->spec[i].name);
			अन्यथा अगर (i > 0 || spec->spec[i].idx > 0)
				libbpf_prपूर्णांक(level, "[%u]", spec->spec[i].idx);
		पूर्ण

		libbpf_prपूर्णांक(level, " (");
		क्रम (i = 0; i < spec->raw_len; i++)
			libbpf_prपूर्णांक(level, "%s%d", i == 0 ? "" : ":", spec->raw_spec[i]);

		अगर (spec->bit_offset % 8)
			libbpf_prपूर्णांक(level, " @ offset %u.%u)",
				     spec->bit_offset / 8, spec->bit_offset % 8);
		अन्यथा
			libbpf_prपूर्णांक(level, " @ offset %u)", spec->bit_offset / 8);
		वापस;
	पूर्ण
पूर्ण

अटल माप_प्रकार bpf_core_hash_fn(स्थिर व्योम *key, व्योम *ctx)
अणु
	वापस (माप_प्रकार)key;
पूर्ण

अटल bool bpf_core_equal_fn(स्थिर व्योम *k1, स्थिर व्योम *k2, व्योम *ctx)
अणु
	वापस k1 == k2;
पूर्ण

अटल व्योम *u32_as_hash_key(__u32 x)
अणु
	वापस (व्योम *)(uपूर्णांकptr_t)x;
पूर्ण

/*
 * CO-RE relocate single inकाष्ठाion.
 *
 * The outline and important poपूर्णांकs of the algorithm:
 * 1. For given local type, find corresponding candidate target types.
 *    Candidate type is a type with the same "essential" name, ignoring
 *    everything after last triple underscore (___). E.g., `sample`,
 *    `sample___flavor_one`, `sample___flavor_another_one`, are all candidates
 *    क्रम each other. Names with triple underscore are referred to as
 *    "flavors" and are useful, among other things, to allow to
 *    specअगरy/support incompatible variations of the same kernel काष्ठा, which
 *    might dअगरfer between dअगरferent kernel versions and/or build
 *    configurations.
 *
 *    N.B. Struct "flavors" could be generated by bpftool's BTF-to-C
 *    converter, when deduplicated BTF of a kernel still contains more than
 *    one dअगरferent types with the same name. In that हाल, ___2, ___3, etc
 *    are appended starting from second name conflict. But start flavors are
 *    also useful to be defined "locally", in BPF program, to extract same
 *    data from incompatible changes between dअगरferent kernel
 *    versions/configurations. For instance, to handle field नामs between
 *    kernel versions, one can use two flavors of the काष्ठा name with the
 *    same common name and use conditional relocations to extract that field,
 *    depending on target kernel version.
 * 2. For each candidate type, try to match local specअगरication to this
 *    candidate target type. Matching involves finding corresponding
 *    high-level spec accessors, meaning that all named fields should match,
 *    as well as all array accesses should be within the actual bounds. Also,
 *    types should be compatible (see bpf_core_fields_are_compat क्रम details).
 * 3. It is supported and expected that there might be multiple flavors
 *    matching the spec. As दीर्घ as all the specs resolve to the same set of
 *    offsets across all candidates, there is no error. If there is any
 *    ambiguity, CO-RE relocation will fail. This is necessary to accomodate
 *    imprefection of BTF deduplication, which can cause slight duplication of
 *    the same BTF type, अगर some directly or indirectly referenced (by
 *    poपूर्णांकer) type माला_लो resolved to dअगरferent actual types in dअगरferent
 *    object files. If such situation occurs, deduplicated BTF will end up
 *    with two (or more) काष्ठाurally identical types, which dअगरfer only in
 *    types they refer to through poपूर्णांकer. This should be OK in most हालs and
 *    is not an error.
 * 4. Candidate types search is perक्रमmed by linearly scanning through all
 *    types in target BTF. It is anticipated that this is overall more
 *    efficient memory-wise and not signअगरicantly worse (अगर not better)
 *    CPU-wise compared to prebuilding a map from all local type names to
 *    a list of candidate type names. It's also sped up by caching resolved
 *    list of matching candidates per each local "root" type ID, that has at
 *    least one bpf_core_relo associated with it. This list is shared
 *    between multiple relocations क्रम the same type ID and is updated as some
 *    of the candidates are pruned due to काष्ठाural incompatibility.
 */
अटल पूर्णांक bpf_core_apply_relo(काष्ठा bpf_program *prog,
			       स्थिर काष्ठा bpf_core_relo *relo,
			       पूर्णांक relo_idx,
			       स्थिर काष्ठा btf *local_btf,
			       काष्ठा hashmap *cand_cache)
अणु
	काष्ठा bpf_core_spec local_spec, cand_spec, targ_spec = अणुपूर्ण;
	स्थिर व्योम *type_key = u32_as_hash_key(relo->type_id);
	काष्ठा bpf_core_relo_res cand_res, targ_res;
	स्थिर काष्ठा btf_type *local_type;
	स्थिर अक्षर *local_name;
	काष्ठा core_cand_list *cands = शून्य;
	__u32 local_id;
	स्थिर अक्षर *spec_str;
	पूर्णांक i, j, err;

	local_id = relo->type_id;
	local_type = btf__type_by_id(local_btf, local_id);
	अगर (!local_type)
		वापस -EINVAL;

	local_name = btf__name_by_offset(local_btf, local_type->name_off);
	अगर (!local_name)
		वापस -EINVAL;

	spec_str = btf__name_by_offset(local_btf, relo->access_str_off);
	अगर (str_is_empty(spec_str))
		वापस -EINVAL;

	err = bpf_core_parse_spec(local_btf, local_id, spec_str, relo->kind, &local_spec);
	अगर (err) अणु
		pr_warn("prog '%s': relo #%d: parsing [%d] %s %s + %s failed: %d\n",
			prog->name, relo_idx, local_id, btf_kind_str(local_type),
			str_is_empty(local_name) ? "<anon>" : local_name,
			spec_str, err);
		वापस -EINVAL;
	पूर्ण

	pr_debug("prog '%s': relo #%d: kind <%s> (%d), spec is ", prog->name,
		 relo_idx, core_relo_kind_str(relo->kind), relo->kind);
	bpf_core_dump_spec(LIBBPF_DEBUG, &local_spec);
	libbpf_prपूर्णांक(LIBBPF_DEBUG, "\n");

	/* TYPE_ID_LOCAL relo is special and करोesn't need candidate search */
	अगर (relo->kind == BPF_TYPE_ID_LOCAL) अणु
		targ_res.validate = true;
		targ_res.poison = false;
		targ_res.orig_val = local_spec.root_type_id;
		targ_res.new_val = local_spec.root_type_id;
		जाओ patch_insn;
	पूर्ण

	/* libbpf करोesn't support candidate search क्रम anonymous types */
	अगर (str_is_empty(spec_str)) अणु
		pr_warn("prog '%s': relo #%d: <%s> (%d) relocation doesn't support anonymous types\n",
			prog->name, relo_idx, core_relo_kind_str(relo->kind), relo->kind);
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (!hashmap__find(cand_cache, type_key, (व्योम **)&cands)) अणु
		cands = bpf_core_find_cands(prog->obj, local_btf, local_id);
		अगर (IS_ERR(cands)) अणु
			pr_warn("prog '%s': relo #%d: target candidate search failed for [%d] %s %s: %ld\n",
				prog->name, relo_idx, local_id, btf_kind_str(local_type),
				local_name, PTR_ERR(cands));
			वापस PTR_ERR(cands);
		पूर्ण
		err = hashmap__set(cand_cache, type_key, cands, शून्य, शून्य);
		अगर (err) अणु
			bpf_core_मुक्त_cands(cands);
			वापस err;
		पूर्ण
	पूर्ण

	क्रम (i = 0, j = 0; i < cands->len; i++) अणु
		err = bpf_core_spec_match(&local_spec, cands->cands[i].btf,
					  cands->cands[i].id, &cand_spec);
		अगर (err < 0) अणु
			pr_warn("prog '%s': relo #%d: error matching candidate #%d ",
				prog->name, relo_idx, i);
			bpf_core_dump_spec(LIBBPF_WARN, &cand_spec);
			libbpf_prपूर्णांक(LIBBPF_WARN, ": %d\n", err);
			वापस err;
		पूर्ण

		pr_debug("prog '%s': relo #%d: %s candidate #%d ", prog->name,
			 relo_idx, err == 0 ? "non-matching" : "matching", i);
		bpf_core_dump_spec(LIBBPF_DEBUG, &cand_spec);
		libbpf_prपूर्णांक(LIBBPF_DEBUG, "\n");

		अगर (err == 0)
			जारी;

		err = bpf_core_calc_relo(prog, relo, relo_idx, &local_spec, &cand_spec, &cand_res);
		अगर (err)
			वापस err;

		अगर (j == 0) अणु
			targ_res = cand_res;
			targ_spec = cand_spec;
		पूर्ण अन्यथा अगर (cand_spec.bit_offset != targ_spec.bit_offset) अणु
			/* अगर there are many field relo candidates, they
			 * should all resolve to the same bit offset
			 */
			pr_warn("prog '%s': relo #%d: field offset ambiguity: %u != %u\n",
				prog->name, relo_idx, cand_spec.bit_offset,
				targ_spec.bit_offset);
			वापस -EINVAL;
		पूर्ण अन्यथा अगर (cand_res.poison != targ_res.poison || cand_res.new_val != targ_res.new_val) अणु
			/* all candidates should result in the same relocation
			 * decision and value, otherwise it's dangerous to
			 * proceed due to ambiguity
			 */
			pr_warn("prog '%s': relo #%d: relocation decision ambiguity: %s %u != %s %u\n",
				prog->name, relo_idx,
				cand_res.poison ? "failure" : "success", cand_res.new_val,
				targ_res.poison ? "failure" : "success", targ_res.new_val);
			वापस -EINVAL;
		पूर्ण

		cands->cands[j++] = cands->cands[i];
	पूर्ण

	/*
	 * For BPF_FIELD_EXISTS relo or when used BPF program has field
	 * existence checks or kernel version/config checks, it's expected
	 * that we might not find any candidates. In this हाल, अगर field
	 * wasn't found in any candidate, the list of candidates shouldn't
	 * change at all, we'll just handle relocating appropriately,
	 * depending on relo's kind.
	 */
	अगर (j > 0)
		cands->len = j;

	/*
	 * If no candidates were found, it might be both a programmer error,
	 * as well as expected हाल, depending whether inकाष्ठाion w/
	 * relocation is guarded in some way that makes it unreachable (dead
	 * code) अगर relocation can't be resolved. This is handled in
	 * bpf_core_patch_insn() unअगरormly by replacing that inकाष्ठाion with
	 * BPF helper call insn (using invalid helper ID). If that inकाष्ठाion
	 * is indeed unreachable, then it will be ignored and eliminated by
	 * verअगरier. If it was an error, then verअगरier will complain and poपूर्णांक
	 * to a specअगरic inकाष्ठाion number in its log.
	 */
	अगर (j == 0) अणु
		pr_debug("prog '%s': relo #%d: no matching targets found\n",
			 prog->name, relo_idx);

		/* calculate single target relo result explicitly */
		err = bpf_core_calc_relo(prog, relo, relo_idx, &local_spec, शून्य, &targ_res);
		अगर (err)
			वापस err;
	पूर्ण

patch_insn:
	/* bpf_core_patch_insn() should know how to handle missing targ_spec */
	err = bpf_core_patch_insn(prog, relo, relo_idx, &targ_res);
	अगर (err) अणु
		pr_warn("prog '%s': relo #%d: failed to patch insn #%zu: %d\n",
			prog->name, relo_idx, relo->insn_off / BPF_INSN_SZ, err);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
bpf_object__relocate_core(काष्ठा bpf_object *obj, स्थिर अक्षर *targ_btf_path)
अणु
	स्थिर काष्ठा btf_ext_info_sec *sec;
	स्थिर काष्ठा bpf_core_relo *rec;
	स्थिर काष्ठा btf_ext_info *seg;
	काष्ठा hashmap_entry *entry;
	काष्ठा hashmap *cand_cache = शून्य;
	काष्ठा bpf_program *prog;
	स्थिर अक्षर *sec_name;
	पूर्णांक i, err = 0, insn_idx, sec_idx;

	अगर (obj->btf_ext->core_relo_info.len == 0)
		वापस 0;

	अगर (targ_btf_path) अणु
		obj->btf_vmlinux_override = btf__parse(targ_btf_path, शून्य);
		अगर (IS_ERR_OR_शून्य(obj->btf_vmlinux_override)) अणु
			err = PTR_ERR(obj->btf_vmlinux_override);
			pr_warn("failed to parse target BTF: %d\n", err);
			वापस err;
		पूर्ण
	पूर्ण

	cand_cache = hashmap__new(bpf_core_hash_fn, bpf_core_equal_fn, शून्य);
	अगर (IS_ERR(cand_cache)) अणु
		err = PTR_ERR(cand_cache);
		जाओ out;
	पूर्ण

	seg = &obj->btf_ext->core_relo_info;
	क्रम_each_btf_ext_sec(seg, sec) अणु
		sec_name = btf__name_by_offset(obj->btf, sec->sec_name_off);
		अगर (str_is_empty(sec_name)) अणु
			err = -EINVAL;
			जाओ out;
		पूर्ण
		/* bpf_object's ELF is gone by now so it's not easy to find
		 * section index by section name, but we can find *any*
		 * bpf_program within desired section name and use it's
		 * prog->sec_idx to करो a proper search by section index and
		 * inकाष्ठाion offset
		 */
		prog = शून्य;
		क्रम (i = 0; i < obj->nr_programs; i++) अणु
			prog = &obj->programs[i];
			अगर (म_भेद(prog->sec_name, sec_name) == 0)
				अवरोध;
		पूर्ण
		अगर (!prog) अणु
			pr_warn("sec '%s': failed to find a BPF program\n", sec_name);
			वापस -ENOENT;
		पूर्ण
		sec_idx = prog->sec_idx;

		pr_debug("sec '%s': found %d CO-RE relocations\n",
			 sec_name, sec->num_info);

		क्रम_each_btf_ext_rec(seg, sec, i, rec) अणु
			insn_idx = rec->insn_off / BPF_INSN_SZ;
			prog = find_prog_by_sec_insn(obj, sec_idx, insn_idx);
			अगर (!prog) अणु
				pr_warn("sec '%s': failed to find program at insn #%d for CO-RE offset relocation #%d\n",
					sec_name, insn_idx, i);
				err = -EINVAL;
				जाओ out;
			पूर्ण
			/* no need to apply CO-RE relocation अगर the program is
			 * not going to be loaded
			 */
			अगर (!prog->load)
				जारी;

			err = bpf_core_apply_relo(prog, rec, i, obj->btf, cand_cache);
			अगर (err) अणु
				pr_warn("prog '%s': relo #%d: failed to relocate: %d\n",
					prog->name, i, err);
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

out:
	/* obj->btf_vmlinux and module BTFs are मुक्तd after object load */
	btf__मुक्त(obj->btf_vmlinux_override);
	obj->btf_vmlinux_override = शून्य;

	अगर (!IS_ERR_OR_शून्य(cand_cache)) अणु
		hashmap__क्रम_each_entry(cand_cache, entry, i) अणु
			bpf_core_मुक्त_cands(entry->value);
		पूर्ण
		hashmap__मुक्त(cand_cache);
	पूर्ण
	वापस err;
पूर्ण

/* Relocate data references within program code:
 *  - map references;
 *  - global variable references;
 *  - बाह्य references.
 */
अटल पूर्णांक
bpf_object__relocate_data(काष्ठा bpf_object *obj, काष्ठा bpf_program *prog)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < prog->nr_reloc; i++) अणु
		काष्ठा reloc_desc *relo = &prog->reloc_desc[i];
		काष्ठा bpf_insn *insn = &prog->insns[relo->insn_idx];
		काष्ठा बाह्य_desc *ext;

		चयन (relo->type) अणु
		हाल RELO_LD64:
			insn[0].src_reg = BPF_PSEUDO_MAP_FD;
			insn[0].imm = obj->maps[relo->map_idx].fd;
			अवरोध;
		हाल RELO_DATA:
			insn[0].src_reg = BPF_PSEUDO_MAP_VALUE;
			insn[1].imm = insn[0].imm + relo->sym_off;
			insn[0].imm = obj->maps[relo->map_idx].fd;
			अवरोध;
		हाल RELO_EXTERN_VAR:
			ext = &obj->बाह्यs[relo->sym_off];
			अगर (ext->type == EXT_KCFG) अणु
				insn[0].src_reg = BPF_PSEUDO_MAP_VALUE;
				insn[0].imm = obj->maps[obj->kconfig_map_idx].fd;
				insn[1].imm = ext->kcfg.data_off;
			पूर्ण अन्यथा /* EXT_KSYM */ अणु
				अगर (ext->ksym.type_id) अणु /* typed ksyms */
					insn[0].src_reg = BPF_PSEUDO_BTF_ID;
					insn[0].imm = ext->ksym.kernel_btf_id;
					insn[1].imm = ext->ksym.kernel_btf_obj_fd;
				पूर्ण अन्यथा अणु /* typeless ksyms */
					insn[0].imm = (__u32)ext->ksym.addr;
					insn[1].imm = ext->ksym.addr >> 32;
				पूर्ण
			पूर्ण
			अवरोध;
		हाल RELO_EXTERN_FUNC:
			ext = &obj->बाह्यs[relo->sym_off];
			insn[0].src_reg = BPF_PSEUDO_KFUNC_CALL;
			insn[0].imm = ext->ksym.kernel_btf_id;
			अवरोध;
		हाल RELO_SUBPROG_ADDR:
			insn[0].src_reg = BPF_PSEUDO_FUNC;
			/* will be handled as a follow up pass */
			अवरोध;
		हाल RELO_CALL:
			/* will be handled as a follow up pass */
			अवरोध;
		शेष:
			pr_warn("prog '%s': relo #%d: bad relo type %d\n",
				prog->name, i, relo->type);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adjust_prog_btf_ext_info(स्थिर काष्ठा bpf_object *obj,
				    स्थिर काष्ठा bpf_program *prog,
				    स्थिर काष्ठा btf_ext_info *ext_info,
				    व्योम **prog_info, __u32 *prog_rec_cnt,
				    __u32 *prog_rec_sz)
अणु
	व्योम *copy_start = शून्य, *copy_end = शून्य;
	व्योम *rec, *rec_end, *new_prog_info;
	स्थिर काष्ठा btf_ext_info_sec *sec;
	माप_प्रकार old_sz, new_sz;
	स्थिर अक्षर *sec_name;
	पूर्णांक i, off_adj;

	क्रम_each_btf_ext_sec(ext_info, sec) अणु
		sec_name = btf__name_by_offset(obj->btf, sec->sec_name_off);
		अगर (!sec_name)
			वापस -EINVAL;
		अगर (म_भेद(sec_name, prog->sec_name) != 0)
			जारी;

		क्रम_each_btf_ext_rec(ext_info, sec, i, rec) अणु
			__u32 insn_off = *(__u32 *)rec / BPF_INSN_SZ;

			अगर (insn_off < prog->sec_insn_off)
				जारी;
			अगर (insn_off >= prog->sec_insn_off + prog->sec_insn_cnt)
				अवरोध;

			अगर (!copy_start)
				copy_start = rec;
			copy_end = rec + ext_info->rec_size;
		पूर्ण

		अगर (!copy_start)
			वापस -ENOENT;

		/* append func/line info of a given (sub-)program to the मुख्य
		 * program func/line info
		 */
		old_sz = (माप_प्रकार)(*prog_rec_cnt) * ext_info->rec_size;
		new_sz = old_sz + (copy_end - copy_start);
		new_prog_info = पुनः_स्मृति(*prog_info, new_sz);
		अगर (!new_prog_info)
			वापस -ENOMEM;
		*prog_info = new_prog_info;
		*prog_rec_cnt = new_sz / ext_info->rec_size;
		स_नकल(new_prog_info + old_sz, copy_start, copy_end - copy_start);

		/* Kernel inकाष्ठाion offsets are in units of 8-byte
		 * inकाष्ठाions, जबतक .BTF.ext inकाष्ठाion offsets generated
		 * by Clang are in units of bytes. So convert Clang offsets
		 * पूर्णांकo kernel offsets and adjust offset according to program
		 * relocated position.
		 */
		off_adj = prog->sub_insn_off - prog->sec_insn_off;
		rec = new_prog_info + old_sz;
		rec_end = new_prog_info + new_sz;
		क्रम (; rec < rec_end; rec += ext_info->rec_size) अणु
			__u32 *insn_off = rec;

			*insn_off = *insn_off / BPF_INSN_SZ + off_adj;
		पूर्ण
		*prog_rec_sz = ext_info->rec_size;
		वापस 0;
	पूर्ण

	वापस -ENOENT;
पूर्ण

अटल पूर्णांक
reloc_prog_func_and_line_info(स्थिर काष्ठा bpf_object *obj,
			      काष्ठा bpf_program *मुख्य_prog,
			      स्थिर काष्ठा bpf_program *prog)
अणु
	पूर्णांक err;

	/* no .BTF.ext relocation अगर .BTF.ext is missing or kernel करोesn't
	 * supprot func/line info
	 */
	अगर (!obj->btf_ext || !kernel_supports(FEAT_BTF_FUNC))
		वापस 0;

	/* only attempt func info relocation अगर मुख्य program's func_info
	 * relocation was successful
	 */
	अगर (मुख्य_prog != prog && !मुख्य_prog->func_info)
		जाओ line_info;

	err = adjust_prog_btf_ext_info(obj, prog, &obj->btf_ext->func_info,
				       &मुख्य_prog->func_info,
				       &मुख्य_prog->func_info_cnt,
				       &मुख्य_prog->func_info_rec_size);
	अगर (err) अणु
		अगर (err != -ENOENT) अणु
			pr_warn("prog '%s': error relocating .BTF.ext function info: %d\n",
				prog->name, err);
			वापस err;
		पूर्ण
		अगर (मुख्य_prog->func_info) अणु
			/*
			 * Some info has alपढ़ोy been found but has problem
			 * in the last btf_ext reloc. Must have to error out.
			 */
			pr_warn("prog '%s': missing .BTF.ext function info.\n", prog->name);
			वापस err;
		पूर्ण
		/* Have problem loading the very first info. Ignore the rest. */
		pr_warn("prog '%s': missing .BTF.ext function info for the main program, skipping all of .BTF.ext func info.\n",
			prog->name);
	पूर्ण

line_info:
	/* करोn't relocate line info if main program's relocation failed */
	अगर (मुख्य_prog != prog && !मुख्य_prog->line_info)
		वापस 0;

	err = adjust_prog_btf_ext_info(obj, prog, &obj->btf_ext->line_info,
				       &मुख्य_prog->line_info,
				       &मुख्य_prog->line_info_cnt,
				       &मुख्य_prog->line_info_rec_size);
	अगर (err) अणु
		अगर (err != -ENOENT) अणु
			pr_warn("prog '%s': error relocating .BTF.ext line info: %d\n",
				prog->name, err);
			वापस err;
		पूर्ण
		अगर (मुख्य_prog->line_info) अणु
			/*
			 * Some info has alपढ़ोy been found but has problem
			 * in the last btf_ext reloc. Must have to error out.
			 */
			pr_warn("prog '%s': missing .BTF.ext line info.\n", prog->name);
			वापस err;
		पूर्ण
		/* Have problem loading the very first info. Ignore the rest. */
		pr_warn("prog '%s': missing .BTF.ext line info for the main program, skipping all of .BTF.ext line info.\n",
			prog->name);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cmp_relo_by_insn_idx(स्थिर व्योम *key, स्थिर व्योम *elem)
अणु
	माप_प्रकार insn_idx = *(स्थिर माप_प्रकार *)key;
	स्थिर काष्ठा reloc_desc *relo = elem;

	अगर (insn_idx == relo->insn_idx)
		वापस 0;
	वापस insn_idx < relo->insn_idx ? -1 : 1;
पूर्ण

अटल काष्ठा reloc_desc *find_prog_insn_relo(स्थिर काष्ठा bpf_program *prog, माप_प्रकार insn_idx)
अणु
	वापस द्वा_खोज(&insn_idx, prog->reloc_desc, prog->nr_reloc,
		       माप(*prog->reloc_desc), cmp_relo_by_insn_idx);
पूर्ण

अटल पूर्णांक
bpf_object__reloc_code(काष्ठा bpf_object *obj, काष्ठा bpf_program *मुख्य_prog,
		       काष्ठा bpf_program *prog)
अणु
	माप_प्रकार sub_insn_idx, insn_idx, new_cnt;
	काष्ठा bpf_program *subprog;
	काष्ठा bpf_insn *insns, *insn;
	काष्ठा reloc_desc *relo;
	पूर्णांक err;

	err = reloc_prog_func_and_line_info(obj, मुख्य_prog, prog);
	अगर (err)
		वापस err;

	क्रम (insn_idx = 0; insn_idx < prog->sec_insn_cnt; insn_idx++) अणु
		insn = &मुख्य_prog->insns[prog->sub_insn_off + insn_idx];
		अगर (!insn_is_subprog_call(insn) && !insn_is_pseuकरो_func(insn))
			जारी;

		relo = find_prog_insn_relo(prog, insn_idx);
		अगर (relo && relo->type != RELO_CALL && relo->type != RELO_SUBPROG_ADDR) अणु
			pr_warn("prog '%s': unexpected relo for insn #%zu, type %d\n",
				prog->name, insn_idx, relo->type);
			वापस -LIBBPF_ERRNO__RELOC;
		पूर्ण
		अगर (relo) अणु
			/* sub-program inकाष्ठाion index is a combination of
			 * an offset of a symbol poपूर्णांकed to by relocation and
			 * call inकाष्ठाion's imm field; क्रम global functions,
			 * call always has imm = -1, but क्रम अटल functions
			 * relocation is against STT_SECTION and insn->imm
			 * poपूर्णांकs to a start of a अटल function
			 *
			 * क्रम subprog addr relocation, the relo->sym_off + insn->imm is
			 * the byte offset in the corresponding section.
			 */
			अगर (relo->type == RELO_CALL)
				sub_insn_idx = relo->sym_off / BPF_INSN_SZ + insn->imm + 1;
			अन्यथा
				sub_insn_idx = (relo->sym_off + insn->imm) / BPF_INSN_SZ;
		पूर्ण अन्यथा अगर (insn_is_pseuकरो_func(insn)) अणु
			/*
			 * RELO_SUBPROG_ADDR relo is always emitted even अगर both
			 * functions are in the same section, so it shouldn't reach here.
			 */
			pr_warn("prog '%s': missing subprog addr relo for insn #%zu\n",
				prog->name, insn_idx);
			वापस -LIBBPF_ERRNO__RELOC;
		पूर्ण अन्यथा अणु
			/* अगर subprogram call is to a अटल function within
			 * the same ELF section, there won't be any relocation
			 * emitted, but it also means there is no additional
			 * offset necessary, insns->imm is relative to
			 * inकाष्ठाion's original position within the section
			 */
			sub_insn_idx = prog->sec_insn_off + insn_idx + insn->imm + 1;
		पूर्ण

		/* we enक्रमce that sub-programs should be in .text section */
		subprog = find_prog_by_sec_insn(obj, obj->efile.text_shndx, sub_insn_idx);
		अगर (!subprog) अणु
			pr_warn("prog '%s': no .text section found yet sub-program call exists\n",
				prog->name);
			वापस -LIBBPF_ERRNO__RELOC;
		पूर्ण

		/* अगर it's the first call inकाष्ठाion calling पूर्णांकo this
		 * subprogram (meaning this subprog hasn't been processed
		 * yet) within the context of current मुख्य program:
		 *   - append it at the end of मुख्य program's inकाष्ठाions blog;
		 *   - process is recursively, जबतक current program is put on hold;
		 *   - अगर that subprogram calls some other not yet processes
		 *   subprogram, same thing will happen recursively until
		 *   there are no more unprocesses subprograms left to append
		 *   and relocate.
		 */
		अगर (subprog->sub_insn_off == 0) अणु
			subprog->sub_insn_off = मुख्य_prog->insns_cnt;

			new_cnt = मुख्य_prog->insns_cnt + subprog->insns_cnt;
			insns = libbpf_पुनः_स्मृतिarray(मुख्य_prog->insns, new_cnt, माप(*insns));
			अगर (!insns) अणु
				pr_warn("prog '%s': failed to realloc prog code\n", मुख्य_prog->name);
				वापस -ENOMEM;
			पूर्ण
			मुख्य_prog->insns = insns;
			मुख्य_prog->insns_cnt = new_cnt;

			स_नकल(मुख्य_prog->insns + subprog->sub_insn_off, subprog->insns,
			       subprog->insns_cnt * माप(*insns));

			pr_debug("prog '%s': added %zu insns from sub-prog '%s'\n",
				 मुख्य_prog->name, subprog->insns_cnt, subprog->name);

			err = bpf_object__reloc_code(obj, मुख्य_prog, subprog);
			अगर (err)
				वापस err;
		पूर्ण

		/* मुख्य_prog->insns memory could have been re-allocated, so
		 * calculate poपूर्णांकer again
		 */
		insn = &मुख्य_prog->insns[prog->sub_insn_off + insn_idx];
		/* calculate correct inकाष्ठाion position within current मुख्य
		 * prog; each मुख्य prog can have a dअगरferent set of
		 * subprograms appended (potentially in dअगरferent order as
		 * well), so position of any subprog can be dअगरferent क्रम
		 * dअगरferent मुख्य programs */
		insn->imm = subprog->sub_insn_off - (prog->sub_insn_off + insn_idx) - 1;

		pr_debug("prog '%s': insn #%zu relocated, imm %d points to subprog '%s' (now at %zu offset)\n",
			 prog->name, insn_idx, insn->imm, subprog->name, subprog->sub_insn_off);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Relocate sub-program calls.
 *
 * Algorithm operates as follows. Each entry-poपूर्णांक BPF program (referred to as
 * मुख्य prog) is processed separately. For each subprog (non-entry functions,
 * that can be called from either entry progs or other subprogs) माला_लो their
 * sub_insn_off reset to zero. This serves as indicator that this subprogram
 * hasn't been yet appended and relocated within current मुख्य prog. Once its
 * relocated, sub_insn_off will poपूर्णांक at the position within current मुख्य prog
 * where given subprog was appended. This will further be used to relocate all
 * the call inकाष्ठाions jumping पूर्णांकo this subprog.
 *
 * We start with मुख्य program and process all call inकाष्ठाions. If the call
 * is पूर्णांकo a subprog that hasn't been processed (i.e., subprog->sub_insn_off
 * is zero), subprog inकाष्ठाions are appended at the end of मुख्य program's
 * inकाष्ठाion array. Then मुख्य program is "put on hold" जबतक we recursively
 * process newly appended subprogram. If that subprogram calls पूर्णांकo another
 * subprogram that hasn't been appended, new subprogram is appended again to
 * the *मुख्य* prog's instructions (subprog's inकाष्ठाions are always left
 * untouched, as they need to be in unmodअगरied state क्रम subsequent मुख्य progs
 * and subprog inकाष्ठाions are always sent only as part of a मुख्य prog) and
 * the process जारीs recursively. Once all the subprogs called from a मुख्य
 * prog or any of its subprogs are appended (and relocated), all their
 * positions within finalized inकाष्ठाions array are known, so it's easy to
 * reग_लिखो call inकाष्ठाions with correct relative offsets, corresponding to
 * desired target subprog.
 *
 * Its important to realize that some subprogs might not be called from some
 * मुख्य prog and any of its called/used subprogs. Those will keep their
 * subprog->sub_insn_off as zero at all बार and won't be appended to current
 * मुख्य prog and won't be relocated within the context of current मुख्य prog.
 * They might still be used from other मुख्य progs later.
 *
 * Visually this process can be shown as below. Suppose we have two मुख्य
 * programs मुख्यA and मुख्यB and BPF object contains three subprogs: subA,
 * subB, and subC. मुख्यA calls only subA, मुख्यB calls only subC, but subA and
 * subC both call subB:
 *
 *        +--------+ +-------+
 *        |        v v       |
 *     +--+---+ +--+-+-+ +---+--+
 *     | subA | | subB | | subC |
 *     +--+---+ +------+ +---+--+
 *        ^                  ^
 *        |                  |
 *    +---+-------+   +------+----+
 *    |   मुख्यA   |   |   मुख्यB   |
 *    +-----------+   +-----------+
 *
 * We'll start relocating मुख्यA, will find subA, append it and start
 * processing sub A recursively:
 *
 *    +-----------+------+
 *    |   मुख्यA   | subA |
 *    +-----------+------+
 *
 * At this poपूर्णांक we notice that subB is used from subA, so we append it and
 * relocate (there are no further subcalls from subB):
 *
 *    +-----------+------+------+
 *    |   मुख्यA   | subA | subB |
 *    +-----------+------+------+
 *
 * At this poपूर्णांक, we relocate subA calls, then go one level up and finish with
 * relocatin मुख्यA calls. मुख्यA is करोne.
 *
 * For मुख्यB process is similar but results in dअगरferent order. We start with
 * मुख्यB and skip subA and subB, as मुख्यB never calls them (at least
 * directly), but we see subC is needed, so we append and start processing it:
 *
 *    +-----------+------+
 *    |   मुख्यB   | subC |
 *    +-----------+------+
 * Now we see subC needs subB, so we go back to it, append and relocate it:
 *
 *    +-----------+------+------+
 *    |   मुख्यB   | subC | subB |
 *    +-----------+------+------+
 *
 * At this poपूर्णांक we unwind recursion, relocate calls in subC, then in मुख्यB.
 */
अटल पूर्णांक
bpf_object__relocate_calls(काष्ठा bpf_object *obj, काष्ठा bpf_program *prog)
अणु
	काष्ठा bpf_program *subprog;
	पूर्णांक i, err;

	/* mark all subprogs as not relocated (yet) within the context of
	 * current मुख्य program
	 */
	क्रम (i = 0; i < obj->nr_programs; i++) अणु
		subprog = &obj->programs[i];
		अगर (!prog_is_subprog(obj, subprog))
			जारी;

		subprog->sub_insn_off = 0;
	पूर्ण

	err = bpf_object__reloc_code(obj, prog, prog);
	अगर (err)
		वापस err;


	वापस 0;
पूर्ण

अटल पूर्णांक
bpf_object__relocate(काष्ठा bpf_object *obj, स्थिर अक्षर *targ_btf_path)
अणु
	काष्ठा bpf_program *prog;
	माप_प्रकार i;
	पूर्णांक err;

	अगर (obj->btf_ext) अणु
		err = bpf_object__relocate_core(obj, targ_btf_path);
		अगर (err) अणु
			pr_warn("failed to perform CO-RE relocations: %d\n",
				err);
			वापस err;
		पूर्ण
	पूर्ण
	/* relocate data references first क्रम all programs and sub-programs,
	 * as they करोn't change relative to code locations, so subsequent
	 * subprogram processing won't need to re-calculate any of them
	 */
	क्रम (i = 0; i < obj->nr_programs; i++) अणु
		prog = &obj->programs[i];
		err = bpf_object__relocate_data(obj, prog);
		अगर (err) अणु
			pr_warn("prog '%s': failed to relocate data references: %d\n",
				prog->name, err);
			वापस err;
		पूर्ण
	पूर्ण
	/* now relocate subprogram calls and append used subprograms to मुख्य
	 * programs; each copy of subprogram code needs to be relocated
	 * dअगरferently क्रम each मुख्य program, because its code location might
	 * have changed
	 */
	क्रम (i = 0; i < obj->nr_programs; i++) अणु
		prog = &obj->programs[i];
		/* sub-program's sub-calls are relocated within the context of
		 * its मुख्य program only
		 */
		अगर (prog_is_subprog(obj, prog))
			जारी;

		err = bpf_object__relocate_calls(obj, prog);
		अगर (err) अणु
			pr_warn("prog '%s': failed to relocate calls: %d\n",
				prog->name, err);
			वापस err;
		पूर्ण
	पूर्ण
	/* मुक्त up relocation descriptors */
	क्रम (i = 0; i < obj->nr_programs; i++) अणु
		prog = &obj->programs[i];
		zमुक्त(&prog->reloc_desc);
		prog->nr_reloc = 0;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक bpf_object__collect_st_ops_relos(काष्ठा bpf_object *obj,
					    GElf_Shdr *shdr, Elf_Data *data);

अटल पूर्णांक bpf_object__collect_map_relos(काष्ठा bpf_object *obj,
					 GElf_Shdr *shdr, Elf_Data *data)
अणु
	स्थिर पूर्णांक bpf_ptr_sz = 8, host_ptr_sz = माप(व्योम *);
	पूर्णांक i, j, nrels, new_sz;
	स्थिर काष्ठा btf_var_secinfo *vi = शून्य;
	स्थिर काष्ठा btf_type *sec, *var, *def;
	काष्ठा bpf_map *map = शून्य, *targ_map;
	स्थिर काष्ठा btf_member *member;
	स्थिर अक्षर *name, *mname;
	Elf_Data *symbols;
	अचिन्हित पूर्णांक moff;
	GElf_Sym sym;
	GElf_Rel rel;
	व्योम *पंचांगp;

	अगर (!obj->efile.btf_maps_sec_btf_id || !obj->btf)
		वापस -EINVAL;
	sec = btf__type_by_id(obj->btf, obj->efile.btf_maps_sec_btf_id);
	अगर (!sec)
		वापस -EINVAL;

	symbols = obj->efile.symbols;
	nrels = shdr->sh_size / shdr->sh_entsize;
	क्रम (i = 0; i < nrels; i++) अणु
		अगर (!gelf_getrel(data, i, &rel)) अणु
			pr_warn(".maps relo #%d: failed to get ELF relo\n", i);
			वापस -LIBBPF_ERRNO__FORMAT;
		पूर्ण
		अगर (!gelf_माला_लोym(symbols, GELF_R_SYM(rel.r_info), &sym)) अणु
			pr_warn(".maps relo #%d: symbol %zx not found\n",
				i, (माप_प्रकार)GELF_R_SYM(rel.r_info));
			वापस -LIBBPF_ERRNO__FORMAT;
		पूर्ण
		name = elf_sym_str(obj, sym.st_name) ?: "<?>";
		अगर (sym.st_shndx != obj->efile.btf_maps_shndx) अणु
			pr_warn(".maps relo #%d: '%s' isn't a BTF-defined map\n",
				i, name);
			वापस -LIBBPF_ERRNO__RELOC;
		पूर्ण

		pr_debug(".maps relo #%d: for %zd value %zd rel.r_offset %zu name %d ('%s')\n",
			 i, (sमाप_प्रकार)(rel.r_info >> 32), (माप_प्रकार)sym.st_value,
			 (माप_प्रकार)rel.r_offset, sym.st_name, name);

		क्रम (j = 0; j < obj->nr_maps; j++) अणु
			map = &obj->maps[j];
			अगर (map->sec_idx != obj->efile.btf_maps_shndx)
				जारी;

			vi = btf_var_secinfos(sec) + map->btf_var_idx;
			अगर (vi->offset <= rel.r_offset &&
			    rel.r_offset + bpf_ptr_sz <= vi->offset + vi->size)
				अवरोध;
		पूर्ण
		अगर (j == obj->nr_maps) अणु
			pr_warn(".maps relo #%d: cannot find map '%s' at rel.r_offset %zu\n",
				i, name, (माप_प्रकार)rel.r_offset);
			वापस -EINVAL;
		पूर्ण

		अगर (!bpf_map_type__is_map_in_map(map->def.type))
			वापस -EINVAL;
		अगर (map->def.type == BPF_MAP_TYPE_HASH_OF_MAPS &&
		    map->def.key_size != माप(पूर्णांक)) अणु
			pr_warn(".maps relo #%d: hash-of-maps '%s' should have key size %zu.\n",
				i, map->name, माप(पूर्णांक));
			वापस -EINVAL;
		पूर्ण

		targ_map = bpf_object__find_map_by_name(obj, name);
		अगर (!targ_map)
			वापस -ESRCH;

		var = btf__type_by_id(obj->btf, vi->type);
		def = skip_mods_and_प्रकारs(obj->btf, var->type, शून्य);
		अगर (btf_vlen(def) == 0)
			वापस -EINVAL;
		member = btf_members(def) + btf_vlen(def) - 1;
		mname = btf__name_by_offset(obj->btf, member->name_off);
		अगर (म_भेद(mname, "values"))
			वापस -EINVAL;

		moff = btf_member_bit_offset(def, btf_vlen(def) - 1) / 8;
		अगर (rel.r_offset - vi->offset < moff)
			वापस -EINVAL;

		moff = rel.r_offset - vi->offset - moff;
		/* here we use BPF poपूर्णांकer size, which is always 64 bit, as we
		 * are parsing ELF that was built क्रम BPF target
		 */
		अगर (moff % bpf_ptr_sz)
			वापस -EINVAL;
		moff /= bpf_ptr_sz;
		अगर (moff >= map->init_slots_sz) अणु
			new_sz = moff + 1;
			पंचांगp = libbpf_पुनः_स्मृतिarray(map->init_slots, new_sz, host_ptr_sz);
			अगर (!पंचांगp)
				वापस -ENOMEM;
			map->init_slots = पंचांगp;
			स_रखो(map->init_slots + map->init_slots_sz, 0,
			       (new_sz - map->init_slots_sz) * host_ptr_sz);
			map->init_slots_sz = new_sz;
		पूर्ण
		map->init_slots[moff] = targ_map;

		pr_debug(".maps relo #%d: map '%s' slot [%d] points to map '%s'\n",
			 i, map->name, moff, name);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cmp_relocs(स्थिर व्योम *_a, स्थिर व्योम *_b)
अणु
	स्थिर काष्ठा reloc_desc *a = _a;
	स्थिर काष्ठा reloc_desc *b = _b;

	अगर (a->insn_idx != b->insn_idx)
		वापस a->insn_idx < b->insn_idx ? -1 : 1;

	/* no two relocations should have the same insn_idx, but ... */
	अगर (a->type != b->type)
		वापस a->type < b->type ? -1 : 1;

	वापस 0;
पूर्ण

अटल पूर्णांक bpf_object__collect_relos(काष्ठा bpf_object *obj)
अणु
	पूर्णांक i, err;

	क्रम (i = 0; i < obj->efile.nr_reloc_sects; i++) अणु
		GElf_Shdr *shdr = &obj->efile.reloc_sects[i].shdr;
		Elf_Data *data = obj->efile.reloc_sects[i].data;
		पूर्णांक idx = shdr->sh_info;

		अगर (shdr->sh_type != SHT_REL) अणु
			pr_warn("internal error at %d\n", __LINE__);
			वापस -LIBBPF_ERRNO__INTERNAL;
		पूर्ण

		अगर (idx == obj->efile.st_ops_shndx)
			err = bpf_object__collect_st_ops_relos(obj, shdr, data);
		अन्यथा अगर (idx == obj->efile.btf_maps_shndx)
			err = bpf_object__collect_map_relos(obj, shdr, data);
		अन्यथा
			err = bpf_object__collect_prog_relos(obj, shdr, data);
		अगर (err)
			वापस err;
	पूर्ण

	क्रम (i = 0; i < obj->nr_programs; i++) अणु
		काष्ठा bpf_program *p = &obj->programs[i];
		
		अगर (!p->nr_reloc)
			जारी;

		क्विक(p->reloc_desc, p->nr_reloc, माप(*p->reloc_desc), cmp_relocs);
	पूर्ण
	वापस 0;
पूर्ण

अटल bool insn_is_helper_call(काष्ठा bpf_insn *insn, क्रमागत bpf_func_id *func_id)
अणु
	अगर (BPF_CLASS(insn->code) == BPF_JMP &&
	    BPF_OP(insn->code) == BPF_CALL &&
	    BPF_SRC(insn->code) == BPF_K &&
	    insn->src_reg == 0 &&
	    insn->dst_reg == 0) अणु
		    *func_id = insn->imm;
		    वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक bpf_object__sanitize_prog(काष्ठा bpf_object *obj, काष्ठा bpf_program *prog)
अणु
	काष्ठा bpf_insn *insn = prog->insns;
	क्रमागत bpf_func_id func_id;
	पूर्णांक i;

	क्रम (i = 0; i < prog->insns_cnt; i++, insn++) अणु
		अगर (!insn_is_helper_call(insn, &func_id))
			जारी;

		/* on kernels that करोn't yet support
		 * bpf_probe_पढ़ो_अणुkernel,userपूर्ण[_str] helpers, fall back
		 * to bpf_probe_पढ़ो() which works well क्रम old kernels
		 */
		चयन (func_id) अणु
		हाल BPF_FUNC_probe_पढ़ो_kernel:
		हाल BPF_FUNC_probe_पढ़ो_user:
			अगर (!kernel_supports(FEAT_PROBE_READ_KERN))
				insn->imm = BPF_FUNC_probe_पढ़ो;
			अवरोध;
		हाल BPF_FUNC_probe_पढ़ो_kernel_str:
		हाल BPF_FUNC_probe_पढ़ो_user_str:
			अगर (!kernel_supports(FEAT_PROBE_READ_KERN))
				insn->imm = BPF_FUNC_probe_पढ़ो_str;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
load_program(काष्ठा bpf_program *prog, काष्ठा bpf_insn *insns, पूर्णांक insns_cnt,
	     अक्षर *license, __u32 kern_version, पूर्णांक *pfd)
अणु
	काष्ठा bpf_prog_load_params load_attr = अणुपूर्ण;
	अक्षर *cp, errmsg[STRERR_बफ_मानE];
	माप_प्रकार log_buf_size = 0;
	अक्षर *log_buf = शून्य;
	पूर्णांक btf_fd, ret;

	अगर (prog->type == BPF_PROG_TYPE_UNSPEC) अणु
		/*
		 * The program type must be set.  Most likely we couldn't find a proper
		 * section definition at load समय, and thus we didn't infer the type.
		 */
		pr_warn("prog '%s': missing BPF prog type, check ELF section name '%s'\n",
			prog->name, prog->sec_name);
		वापस -EINVAL;
	पूर्ण

	अगर (!insns || !insns_cnt)
		वापस -EINVAL;

	load_attr.prog_type = prog->type;
	/* old kernels might not support specअगरying expected_attach_type */
	अगर (!kernel_supports(FEAT_EXP_ATTACH_TYPE) && prog->sec_def &&
	    prog->sec_def->is_exp_attach_type_optional)
		load_attr.expected_attach_type = 0;
	अन्यथा
		load_attr.expected_attach_type = prog->expected_attach_type;
	अगर (kernel_supports(FEAT_PROG_NAME))
		load_attr.name = prog->name;
	load_attr.insns = insns;
	load_attr.insn_cnt = insns_cnt;
	load_attr.license = license;
	load_attr.attach_btf_id = prog->attach_btf_id;
	अगर (prog->attach_prog_fd)
		load_attr.attach_prog_fd = prog->attach_prog_fd;
	अन्यथा
		load_attr.attach_btf_obj_fd = prog->attach_btf_obj_fd;
	load_attr.attach_btf_id = prog->attach_btf_id;
	load_attr.kern_version = kern_version;
	load_attr.prog_अगरindex = prog->prog_अगरindex;

	/* specअगरy func_info/line_info only अगर kernel supports them */
	btf_fd = bpf_object__btf_fd(prog->obj);
	अगर (btf_fd >= 0 && kernel_supports(FEAT_BTF_FUNC)) अणु
		load_attr.prog_btf_fd = btf_fd;
		load_attr.func_info = prog->func_info;
		load_attr.func_info_rec_size = prog->func_info_rec_size;
		load_attr.func_info_cnt = prog->func_info_cnt;
		load_attr.line_info = prog->line_info;
		load_attr.line_info_rec_size = prog->line_info_rec_size;
		load_attr.line_info_cnt = prog->line_info_cnt;
	पूर्ण
	load_attr.log_level = prog->log_level;
	load_attr.prog_flags = prog->prog_flags;

retry_load:
	अगर (log_buf_size) अणु
		log_buf = दो_स्मृति(log_buf_size);
		अगर (!log_buf)
			वापस -ENOMEM;

		*log_buf = 0;
	पूर्ण

	load_attr.log_buf = log_buf;
	load_attr.log_buf_sz = log_buf_size;
	ret = libbpf__bpf_prog_load(&load_attr);

	अगर (ret >= 0) अणु
		अगर (log_buf && load_attr.log_level)
			pr_debug("verifier log:\n%s", log_buf);

		अगर (prog->obj->rodata_map_idx >= 0 &&
		    kernel_supports(FEAT_PROG_BIND_MAP)) अणु
			काष्ठा bpf_map *rodata_map =
				&prog->obj->maps[prog->obj->rodata_map_idx];

			अगर (bpf_prog_bind_map(ret, bpf_map__fd(rodata_map), शून्य)) अणु
				cp = libbpf_म_त्रुटि_r(त्रुटि_सं, errmsg, माप(errmsg));
				pr_warn("prog '%s': failed to bind .rodata map: %s\n",
					prog->name, cp);
				/* Don't fail hard if can't bind rodata. */
			पूर्ण
		पूर्ण

		*pfd = ret;
		ret = 0;
		जाओ out;
	पूर्ण

	अगर (!log_buf || त्रुटि_सं == ENOSPC) अणु
		log_buf_size = max((माप_प्रकार)BPF_LOG_BUF_SIZE,
				   log_buf_size << 1);

		मुक्त(log_buf);
		जाओ retry_load;
	पूर्ण
	ret = त्रुटि_सं ? -त्रुटि_सं : -LIBBPF_ERRNO__LOAD;
	cp = libbpf_म_त्रुटि_r(त्रुटि_सं, errmsg, माप(errmsg));
	pr_warn("load bpf program failed: %s\n", cp);
	pr_perm_msg(ret);

	अगर (log_buf && log_buf[0] != '\0') अणु
		ret = -LIBBPF_ERRNO__VERIFY;
		pr_warn("-- BEGIN DUMP LOG ---\n");
		pr_warn("\n%s\n", log_buf);
		pr_warn("-- END LOG --\n");
	पूर्ण अन्यथा अगर (load_attr.insn_cnt >= BPF_MAXINSNS) अणु
		pr_warn("Program too large (%zu insns), at most %d insns\n",
			load_attr.insn_cnt, BPF_MAXINSNS);
		ret = -LIBBPF_ERRNO__PROG2BIG;
	पूर्ण अन्यथा अगर (load_attr.prog_type != BPF_PROG_TYPE_KPROBE) अणु
		/* Wrong program type? */
		पूर्णांक fd;

		load_attr.prog_type = BPF_PROG_TYPE_KPROBE;
		load_attr.expected_attach_type = 0;
		load_attr.log_buf = शून्य;
		load_attr.log_buf_sz = 0;
		fd = libbpf__bpf_prog_load(&load_attr);
		अगर (fd >= 0) अणु
			बंद(fd);
			ret = -LIBBPF_ERRNO__PROGTYPE;
			जाओ out;
		पूर्ण
	पूर्ण

out:
	मुक्त(log_buf);
	वापस ret;
पूर्ण

अटल पूर्णांक libbpf_find_attach_btf_id(काष्ठा bpf_program *prog, पूर्णांक *btf_obj_fd, पूर्णांक *btf_type_id);

पूर्णांक bpf_program__load(काष्ठा bpf_program *prog, अक्षर *license, __u32 kern_ver)
अणु
	पूर्णांक err = 0, fd, i;

	अगर (prog->obj->loaded) अणु
		pr_warn("prog '%s': can't load after object was loaded\n", prog->name);
		वापस -EINVAL;
	पूर्ण

	अगर ((prog->type == BPF_PROG_TYPE_TRACING ||
	     prog->type == BPF_PROG_TYPE_LSM ||
	     prog->type == BPF_PROG_TYPE_EXT) && !prog->attach_btf_id) अणु
		पूर्णांक btf_obj_fd = 0, btf_type_id = 0;

		err = libbpf_find_attach_btf_id(prog, &btf_obj_fd, &btf_type_id);
		अगर (err)
			वापस err;

		prog->attach_btf_obj_fd = btf_obj_fd;
		prog->attach_btf_id = btf_type_id;
	पूर्ण

	अगर (prog->instances.nr < 0 || !prog->instances.fds) अणु
		अगर (prog->preprocessor) अणु
			pr_warn("Internal error: can't load program '%s'\n",
				prog->name);
			वापस -LIBBPF_ERRNO__INTERNAL;
		पूर्ण

		prog->instances.fds = दो_स्मृति(माप(पूर्णांक));
		अगर (!prog->instances.fds) अणु
			pr_warn("Not enough memory for BPF fds\n");
			वापस -ENOMEM;
		पूर्ण
		prog->instances.nr = 1;
		prog->instances.fds[0] = -1;
	पूर्ण

	अगर (!prog->preprocessor) अणु
		अगर (prog->instances.nr != 1) अणु
			pr_warn("prog '%s': inconsistent nr(%d) != 1\n",
				prog->name, prog->instances.nr);
		पूर्ण
		err = load_program(prog, prog->insns, prog->insns_cnt,
				   license, kern_ver, &fd);
		अगर (!err)
			prog->instances.fds[0] = fd;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < prog->instances.nr; i++) अणु
		काष्ठा bpf_prog_prep_result result;
		bpf_program_prep_t preprocessor = prog->preprocessor;

		स_रखो(&result, 0, माप(result));
		err = preprocessor(prog, i, prog->insns,
				   prog->insns_cnt, &result);
		अगर (err) अणु
			pr_warn("Preprocessing the %dth instance of program '%s' failed\n",
				i, prog->name);
			जाओ out;
		पूर्ण

		अगर (!result.new_insn_ptr || !result.new_insn_cnt) अणु
			pr_debug("Skip loading the %dth instance of program '%s'\n",
				 i, prog->name);
			prog->instances.fds[i] = -1;
			अगर (result.pfd)
				*result.pfd = -1;
			जारी;
		पूर्ण

		err = load_program(prog, result.new_insn_ptr,
				   result.new_insn_cnt, license, kern_ver, &fd);
		अगर (err) अणु
			pr_warn("Loading the %dth instance of program '%s' failed\n",
				i, prog->name);
			जाओ out;
		पूर्ण

		अगर (result.pfd)
			*result.pfd = fd;
		prog->instances.fds[i] = fd;
	पूर्ण
out:
	अगर (err)
		pr_warn("failed to load program '%s'\n", prog->name);
	zमुक्त(&prog->insns);
	prog->insns_cnt = 0;
	वापस err;
पूर्ण

अटल पूर्णांक
bpf_object__load_progs(काष्ठा bpf_object *obj, पूर्णांक log_level)
अणु
	काष्ठा bpf_program *prog;
	माप_प्रकार i;
	पूर्णांक err;

	क्रम (i = 0; i < obj->nr_programs; i++) अणु
		prog = &obj->programs[i];
		err = bpf_object__sanitize_prog(obj, prog);
		अगर (err)
			वापस err;
	पूर्ण

	क्रम (i = 0; i < obj->nr_programs; i++) अणु
		prog = &obj->programs[i];
		अगर (prog_is_subprog(obj, prog))
			जारी;
		अगर (!prog->load) अणु
			pr_debug("prog '%s': skipped loading\n", prog->name);
			जारी;
		पूर्ण
		prog->log_level |= log_level;
		err = bpf_program__load(prog, obj->license, obj->kern_version);
		अगर (err)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा bpf_sec_def *find_sec_def(स्थिर अक्षर *sec_name);

अटल काष्ठा bpf_object *
__bpf_object__खोलो(स्थिर अक्षर *path, स्थिर व्योम *obj_buf, माप_प्रकार obj_buf_sz,
		   स्थिर काष्ठा bpf_object_खोलो_opts *opts)
अणु
	स्थिर अक्षर *obj_name, *kconfig;
	काष्ठा bpf_program *prog;
	काष्ठा bpf_object *obj;
	अक्षर पंचांगp_name[64];
	पूर्णांक err;

	अगर (elf_version(EV_CURRENT) == EV_NONE) अणु
		pr_warn("failed to init libelf for %s\n",
			path ? : "(mem buf)");
		वापस ERR_PTR(-LIBBPF_ERRNO__LIBELF);
	पूर्ण

	अगर (!OPTS_VALID(opts, bpf_object_खोलो_opts))
		वापस ERR_PTR(-EINVAL);

	obj_name = OPTS_GET(opts, object_name, शून्य);
	अगर (obj_buf) अणु
		अगर (!obj_name) अणु
			snम_लिखो(पंचांगp_name, माप(पंचांगp_name), "%lx-%lx",
				 (अचिन्हित दीर्घ)obj_buf,
				 (अचिन्हित दीर्घ)obj_buf_sz);
			obj_name = पंचांगp_name;
		पूर्ण
		path = obj_name;
		pr_debug("loading object '%s' from buffer\n", obj_name);
	पूर्ण

	obj = bpf_object__new(path, obj_buf, obj_buf_sz, obj_name);
	अगर (IS_ERR(obj))
		वापस obj;

	kconfig = OPTS_GET(opts, kconfig, शून्य);
	अगर (kconfig) अणु
		obj->kconfig = strdup(kconfig);
		अगर (!obj->kconfig)
			वापस ERR_PTR(-ENOMEM);
	पूर्ण

	err = bpf_object__elf_init(obj);
	err = err ? : bpf_object__check_endianness(obj);
	err = err ? : bpf_object__elf_collect(obj);
	err = err ? : bpf_object__collect_बाह्यs(obj);
	err = err ? : bpf_object__finalize_btf(obj);
	err = err ? : bpf_object__init_maps(obj, opts);
	err = err ? : bpf_object__collect_relos(obj);
	अगर (err)
		जाओ out;
	bpf_object__elf_finish(obj);

	bpf_object__क्रम_each_program(prog, obj) अणु
		prog->sec_def = find_sec_def(prog->sec_name);
		अगर (!prog->sec_def) अणु
			/* couldn't guess, but user might manually specअगरy */
			pr_debug("prog '%s': unrecognized ELF section name '%s'\n",
				prog->name, prog->sec_name);
			जारी;
		पूर्ण

		अगर (prog->sec_def->is_sleepable)
			prog->prog_flags |= BPF_F_SLEEPABLE;
		bpf_program__set_type(prog, prog->sec_def->prog_type);
		bpf_program__set_expected_attach_type(prog,
				prog->sec_def->expected_attach_type);

		अगर (prog->sec_def->prog_type == BPF_PROG_TYPE_TRACING ||
		    prog->sec_def->prog_type == BPF_PROG_TYPE_EXT)
			prog->attach_prog_fd = OPTS_GET(opts, attach_prog_fd, 0);
	पूर्ण

	वापस obj;
out:
	bpf_object__बंद(obj);
	वापस ERR_PTR(err);
पूर्ण

अटल काष्ठा bpf_object *
__bpf_object__खोलो_xattr(काष्ठा bpf_object_खोलो_attr *attr, पूर्णांक flags)
अणु
	DECLARE_LIBBPF_OPTS(bpf_object_खोलो_opts, opts,
		.relaxed_maps = flags & MAPS_RELAX_COMPAT,
	);

	/* param validation */
	अगर (!attr->file)
		वापस शून्य;

	pr_debug("loading %s\n", attr->file);
	वापस __bpf_object__खोलो(attr->file, शून्य, 0, &opts);
पूर्ण

काष्ठा bpf_object *bpf_object__खोलो_xattr(काष्ठा bpf_object_खोलो_attr *attr)
अणु
	वापस __bpf_object__खोलो_xattr(attr, 0);
पूर्ण

काष्ठा bpf_object *bpf_object__खोलो(स्थिर अक्षर *path)
अणु
	काष्ठा bpf_object_खोलो_attr attr = अणु
		.file		= path,
		.prog_type	= BPF_PROG_TYPE_UNSPEC,
	पूर्ण;

	वापस bpf_object__खोलो_xattr(&attr);
पूर्ण

काष्ठा bpf_object *
bpf_object__खोलो_file(स्थिर अक्षर *path, स्थिर काष्ठा bpf_object_खोलो_opts *opts)
अणु
	अगर (!path)
		वापस ERR_PTR(-EINVAL);

	pr_debug("loading %s\n", path);

	वापस __bpf_object__खोलो(path, शून्य, 0, opts);
पूर्ण

काष्ठा bpf_object *
bpf_object__खोलो_mem(स्थिर व्योम *obj_buf, माप_प्रकार obj_buf_sz,
		     स्थिर काष्ठा bpf_object_खोलो_opts *opts)
अणु
	अगर (!obj_buf || obj_buf_sz == 0)
		वापस ERR_PTR(-EINVAL);

	वापस __bpf_object__खोलो(शून्य, obj_buf, obj_buf_sz, opts);
पूर्ण

काष्ठा bpf_object *
bpf_object__खोलो_buffer(स्थिर व्योम *obj_buf, माप_प्रकार obj_buf_sz,
			स्थिर अक्षर *name)
अणु
	DECLARE_LIBBPF_OPTS(bpf_object_खोलो_opts, opts,
		.object_name = name,
		/* wrong शेष, but backwards-compatible */
		.relaxed_maps = true,
	);

	/* वापसing शून्य is wrong, but backwards-compatible */
	अगर (!obj_buf || obj_buf_sz == 0)
		वापस शून्य;

	वापस bpf_object__खोलो_mem(obj_buf, obj_buf_sz, &opts);
पूर्ण

पूर्णांक bpf_object__unload(काष्ठा bpf_object *obj)
अणु
	माप_प्रकार i;

	अगर (!obj)
		वापस -EINVAL;

	क्रम (i = 0; i < obj->nr_maps; i++) अणु
		zबंद(obj->maps[i].fd);
		अगर (obj->maps[i].st_ops)
			zमुक्त(&obj->maps[i].st_ops->kern_vdata);
	पूर्ण

	क्रम (i = 0; i < obj->nr_programs; i++)
		bpf_program__unload(&obj->programs[i]);

	वापस 0;
पूर्ण

अटल पूर्णांक bpf_object__sanitize_maps(काष्ठा bpf_object *obj)
अणु
	काष्ठा bpf_map *m;

	bpf_object__क्रम_each_map(m, obj) अणु
		अगर (!bpf_map__is_पूर्णांकernal(m))
			जारी;
		अगर (!kernel_supports(FEAT_GLOBAL_DATA)) अणु
			pr_warn("kernel doesn't support global data\n");
			वापस -ENOTSUP;
		पूर्ण
		अगर (!kernel_supports(FEAT_ARRAY_MMAP))
			m->def.map_flags ^= BPF_F_MMAPABLE;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bpf_object__पढ़ो_kallsyms_file(काष्ठा bpf_object *obj)
अणु
	अक्षर sym_type, sym_name[500];
	अचिन्हित दीर्घ दीर्घ sym_addr;
	स्थिर काष्ठा btf_type *t;
	काष्ठा बाह्य_desc *ext;
	पूर्णांक ret, err = 0;
	खाता *f;

	f = ख_खोलो("/proc/kallsyms", "r");
	अगर (!f) अणु
		err = -त्रुटि_सं;
		pr_warn("failed to open /proc/kallsyms: %d\n", err);
		वापस err;
	पूर्ण

	जबतक (true) अणु
		ret = ख_पूछो(f, "%llx %c %499s%*[^\न]\न",
			     &sym_addr, &sym_type, sym_name);
		अगर (ret == खातापूर्ण && ख_पूर्ण(f))
			अवरोध;
		अगर (ret != 3) अणु
			pr_warn("failed to read kallsyms entry: %d\n", ret);
			err = -EINVAL;
			जाओ out;
		पूर्ण

		ext = find_बाह्य_by_name(obj, sym_name);
		अगर (!ext || ext->type != EXT_KSYM)
			जारी;

		t = btf__type_by_id(obj->btf, ext->btf_id);
		अगर (!btf_is_var(t))
			जारी;

		अगर (ext->is_set && ext->ksym.addr != sym_addr) अणु
			pr_warn("extern (ksym) '%s' resolution is ambiguous: 0x%llx or 0x%llx\n",
				sym_name, ext->ksym.addr, sym_addr);
			err = -EINVAL;
			जाओ out;
		पूर्ण
		अगर (!ext->is_set) अणु
			ext->is_set = true;
			ext->ksym.addr = sym_addr;
			pr_debug("extern (ksym) %s=0x%llx\n", sym_name, sym_addr);
		पूर्ण
	पूर्ण

out:
	ख_बंद(f);
	वापस err;
पूर्ण

अटल पूर्णांक find_ksym_btf_id(काष्ठा bpf_object *obj, स्थिर अक्षर *ksym_name,
			    __u16 kind, काष्ठा btf **res_btf,
			    पूर्णांक *res_btf_fd)
अणु
	पूर्णांक i, id, btf_fd, err;
	काष्ठा btf *btf;

	btf = obj->btf_vmlinux;
	btf_fd = 0;
	id = btf__find_by_name_kind(btf, ksym_name, kind);

	अगर (id == -ENOENT) अणु
		err = load_module_btfs(obj);
		अगर (err)
			वापस err;

		क्रम (i = 0; i < obj->btf_module_cnt; i++) अणु
			btf = obj->btf_modules[i].btf;
			/* we assume module BTF FD is always >0 */
			btf_fd = obj->btf_modules[i].fd;
			id = btf__find_by_name_kind(btf, ksym_name, kind);
			अगर (id != -ENOENT)
				अवरोध;
		पूर्ण
	पूर्ण
	अगर (id <= 0) अणु
		pr_warn("extern (%s ksym) '%s': failed to find BTF ID in kernel BTF(s).\n",
			__btf_kind_str(kind), ksym_name);
		वापस -ESRCH;
	पूर्ण

	*res_btf = btf;
	*res_btf_fd = btf_fd;
	वापस id;
पूर्ण

अटल पूर्णांक bpf_object__resolve_ksym_var_btf_id(काष्ठा bpf_object *obj,
					       काष्ठा बाह्य_desc *ext)
अणु
	स्थिर काष्ठा btf_type *targ_var, *targ_type;
	__u32 targ_type_id, local_type_id;
	स्थिर अक्षर *targ_var_name;
	पूर्णांक id, btf_fd = 0, err;
	काष्ठा btf *btf = शून्य;

	id = find_ksym_btf_id(obj, ext->name, BTF_KIND_VAR, &btf, &btf_fd);
	अगर (id < 0)
		वापस id;

	/* find local type_id */
	local_type_id = ext->ksym.type_id;

	/* find target type_id */
	targ_var = btf__type_by_id(btf, id);
	targ_var_name = btf__name_by_offset(btf, targ_var->name_off);
	targ_type = skip_mods_and_प्रकारs(btf, targ_var->type, &targ_type_id);

	err = bpf_core_types_are_compat(obj->btf, local_type_id,
					btf, targ_type_id);
	अगर (err <= 0) अणु
		स्थिर काष्ठा btf_type *local_type;
		स्थिर अक्षर *targ_name, *local_name;

		local_type = btf__type_by_id(obj->btf, local_type_id);
		local_name = btf__name_by_offset(obj->btf, local_type->name_off);
		targ_name = btf__name_by_offset(btf, targ_type->name_off);

		pr_warn("extern (var ksym) '%s': incompatible types, expected [%d] %s %s, but kernel has [%d] %s %s\n",
			ext->name, local_type_id,
			btf_kind_str(local_type), local_name, targ_type_id,
			btf_kind_str(targ_type), targ_name);
		वापस -EINVAL;
	पूर्ण

	ext->is_set = true;
	ext->ksym.kernel_btf_obj_fd = btf_fd;
	ext->ksym.kernel_btf_id = id;
	pr_debug("extern (var ksym) '%s': resolved to [%d] %s %s\n",
		 ext->name, id, btf_kind_str(targ_var), targ_var_name);

	वापस 0;
पूर्ण

अटल पूर्णांक bpf_object__resolve_ksym_func_btf_id(काष्ठा bpf_object *obj,
						काष्ठा बाह्य_desc *ext)
अणु
	पूर्णांक local_func_proto_id, kfunc_proto_id, kfunc_id;
	स्थिर काष्ठा btf_type *kern_func;
	काष्ठा btf *kern_btf = शून्य;
	पूर्णांक ret, kern_btf_fd = 0;

	local_func_proto_id = ext->ksym.type_id;

	kfunc_id = find_ksym_btf_id(obj, ext->name, BTF_KIND_FUNC,
				    &kern_btf, &kern_btf_fd);
	अगर (kfunc_id < 0) अणु
		pr_warn("extern (func ksym) '%s': not found in kernel BTF\n",
			ext->name);
		वापस kfunc_id;
	पूर्ण

	अगर (kern_btf != obj->btf_vmlinux) अणु
		pr_warn("extern (func ksym) '%s': function in kernel module is not supported\n",
			ext->name);
		वापस -ENOTSUP;
	पूर्ण

	kern_func = btf__type_by_id(kern_btf, kfunc_id);
	kfunc_proto_id = kern_func->type;

	ret = bpf_core_types_are_compat(obj->btf, local_func_proto_id,
					kern_btf, kfunc_proto_id);
	अगर (ret <= 0) अणु
		pr_warn("extern (func ksym) '%s': func_proto [%d] incompatible with kernel [%d]\n",
			ext->name, local_func_proto_id, kfunc_proto_id);
		वापस -EINVAL;
	पूर्ण

	ext->is_set = true;
	ext->ksym.kernel_btf_obj_fd = kern_btf_fd;
	ext->ksym.kernel_btf_id = kfunc_id;
	pr_debug("extern (func ksym) '%s': resolved to kernel [%d]\n",
		 ext->name, kfunc_id);

	वापस 0;
पूर्ण

अटल पूर्णांक bpf_object__resolve_ksyms_btf_id(काष्ठा bpf_object *obj)
अणु
	स्थिर काष्ठा btf_type *t;
	काष्ठा बाह्य_desc *ext;
	पूर्णांक i, err;

	क्रम (i = 0; i < obj->nr_बाह्य; i++) अणु
		ext = &obj->बाह्यs[i];
		अगर (ext->type != EXT_KSYM || !ext->ksym.type_id)
			जारी;

		t = btf__type_by_id(obj->btf, ext->btf_id);
		अगर (btf_is_var(t))
			err = bpf_object__resolve_ksym_var_btf_id(obj, ext);
		अन्यथा
			err = bpf_object__resolve_ksym_func_btf_id(obj, ext);
		अगर (err)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक bpf_object__resolve_बाह्यs(काष्ठा bpf_object *obj,
				       स्थिर अक्षर *extra_kconfig)
अणु
	bool need_config = false, need_kallsyms = false;
	bool need_vmlinux_btf = false;
	काष्ठा बाह्य_desc *ext;
	व्योम *kcfg_data = शून्य;
	पूर्णांक err, i;

	अगर (obj->nr_बाह्य == 0)
		वापस 0;

	अगर (obj->kconfig_map_idx >= 0)
		kcfg_data = obj->maps[obj->kconfig_map_idx].mmaped;

	क्रम (i = 0; i < obj->nr_बाह्य; i++) अणु
		ext = &obj->बाह्यs[i];

		अगर (ext->type == EXT_KCFG &&
		    म_भेद(ext->name, "LINUX_KERNEL_VERSION") == 0) अणु
			व्योम *ext_val = kcfg_data + ext->kcfg.data_off;
			__u32 kver = get_kernel_version();

			अगर (!kver) अणु
				pr_warn("failed to get kernel version\n");
				वापस -EINVAL;
			पूर्ण
			err = set_kcfg_value_num(ext, ext_val, kver);
			अगर (err)
				वापस err;
			pr_debug("extern (kcfg) %s=0x%x\n", ext->name, kver);
		पूर्ण अन्यथा अगर (ext->type == EXT_KCFG &&
			   म_भेदन(ext->name, "CONFIG_", 7) == 0) अणु
			need_config = true;
		पूर्ण अन्यथा अगर (ext->type == EXT_KSYM) अणु
			अगर (ext->ksym.type_id)
				need_vmlinux_btf = true;
			अन्यथा
				need_kallsyms = true;
		पूर्ण अन्यथा अणु
			pr_warn("unrecognized extern '%s'\n", ext->name);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	अगर (need_config && extra_kconfig) अणु
		err = bpf_object__पढ़ो_kconfig_mem(obj, extra_kconfig, kcfg_data);
		अगर (err)
			वापस -EINVAL;
		need_config = false;
		क्रम (i = 0; i < obj->nr_बाह्य; i++) अणु
			ext = &obj->बाह्यs[i];
			अगर (ext->type == EXT_KCFG && !ext->is_set) अणु
				need_config = true;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (need_config) अणु
		err = bpf_object__पढ़ो_kconfig_file(obj, kcfg_data);
		अगर (err)
			वापस -EINVAL;
	पूर्ण
	अगर (need_kallsyms) अणु
		err = bpf_object__पढ़ो_kallsyms_file(obj);
		अगर (err)
			वापस -EINVAL;
	पूर्ण
	अगर (need_vmlinux_btf) अणु
		err = bpf_object__resolve_ksyms_btf_id(obj);
		अगर (err)
			वापस -EINVAL;
	पूर्ण
	क्रम (i = 0; i < obj->nr_बाह्य; i++) अणु
		ext = &obj->बाह्यs[i];

		अगर (!ext->is_set && !ext->is_weak) अणु
			pr_warn("extern %s (strong) not resolved\n", ext->name);
			वापस -ESRCH;
		पूर्ण अन्यथा अगर (!ext->is_set) अणु
			pr_debug("extern %s (weak) not resolved, defaulting to zero\n",
				 ext->name);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक bpf_object__load_xattr(काष्ठा bpf_object_load_attr *attr)
अणु
	काष्ठा bpf_object *obj;
	पूर्णांक err, i;

	अगर (!attr)
		वापस -EINVAL;
	obj = attr->obj;
	अगर (!obj)
		वापस -EINVAL;

	अगर (obj->loaded) अणु
		pr_warn("object '%s': load can't be attempted twice\n", obj->name);
		वापस -EINVAL;
	पूर्ण

	err = bpf_object__probe_loading(obj);
	err = err ? : bpf_object__load_vmlinux_btf(obj, false);
	err = err ? : bpf_object__resolve_बाह्यs(obj, obj->kconfig);
	err = err ? : bpf_object__sanitize_and_load_btf(obj);
	err = err ? : bpf_object__sanitize_maps(obj);
	err = err ? : bpf_object__init_kern_काष्ठा_ops_maps(obj);
	err = err ? : bpf_object__create_maps(obj);
	err = err ? : bpf_object__relocate(obj, attr->target_btf_path);
	err = err ? : bpf_object__load_progs(obj, attr->log_level);

	/* clean up module BTFs */
	क्रम (i = 0; i < obj->btf_module_cnt; i++) अणु
		बंद(obj->btf_modules[i].fd);
		btf__मुक्त(obj->btf_modules[i].btf);
		मुक्त(obj->btf_modules[i].name);
	पूर्ण
	मुक्त(obj->btf_modules);

	/* clean up vmlinux BTF */
	btf__मुक्त(obj->btf_vmlinux);
	obj->btf_vmlinux = शून्य;

	obj->loaded = true; /* करोesn't matter अगर successfully or not */

	अगर (err)
		जाओ out;

	वापस 0;
out:
	/* unpin any maps that were स्वतः-pinned during load */
	क्रम (i = 0; i < obj->nr_maps; i++)
		अगर (obj->maps[i].pinned && !obj->maps[i].reused)
			bpf_map__unpin(&obj->maps[i], शून्य);

	bpf_object__unload(obj);
	pr_warn("failed to load object '%s'\n", obj->path);
	वापस err;
पूर्ण

पूर्णांक bpf_object__load(काष्ठा bpf_object *obj)
अणु
	काष्ठा bpf_object_load_attr attr = अणु
		.obj = obj,
	पूर्ण;

	वापस bpf_object__load_xattr(&attr);
पूर्ण

अटल पूर्णांक make_parent_dir(स्थिर अक्षर *path)
अणु
	अक्षर *cp, errmsg[STRERR_बफ_मानE];
	अक्षर *dname, *dir;
	पूर्णांक err = 0;

	dname = strdup(path);
	अगर (dname == शून्य)
		वापस -ENOMEM;

	dir = स_नाम(dname);
	अगर (सूची_गढ़ो(dir, 0700) && त्रुटि_सं != EEXIST)
		err = -त्रुटि_सं;

	मुक्त(dname);
	अगर (err) अणु
		cp = libbpf_म_त्रुटि_r(-err, errmsg, माप(errmsg));
		pr_warn("failed to mkdir %s: %s\n", path, cp);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक check_path(स्थिर अक्षर *path)
अणु
	अक्षर *cp, errmsg[STRERR_बफ_मानE];
	काष्ठा statfs st_fs;
	अक्षर *dname, *dir;
	पूर्णांक err = 0;

	अगर (path == शून्य)
		वापस -EINVAL;

	dname = strdup(path);
	अगर (dname == शून्य)
		वापस -ENOMEM;

	dir = स_नाम(dname);
	अगर (statfs(dir, &st_fs)) अणु
		cp = libbpf_म_त्रुटि_r(त्रुटि_सं, errmsg, माप(errmsg));
		pr_warn("failed to statfs %s: %s\n", dir, cp);
		err = -त्रुटि_सं;
	पूर्ण
	मुक्त(dname);

	अगर (!err && st_fs.f_type != BPF_FS_MAGIC) अणु
		pr_warn("specified path %s is not on BPF FS\n", path);
		err = -EINVAL;
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक bpf_program__pin_instance(काष्ठा bpf_program *prog, स्थिर अक्षर *path,
			      पूर्णांक instance)
अणु
	अक्षर *cp, errmsg[STRERR_बफ_मानE];
	पूर्णांक err;

	err = make_parent_dir(path);
	अगर (err)
		वापस err;

	err = check_path(path);
	अगर (err)
		वापस err;

	अगर (prog == शून्य) अणु
		pr_warn("invalid program pointer\n");
		वापस -EINVAL;
	पूर्ण

	अगर (instance < 0 || instance >= prog->instances.nr) अणु
		pr_warn("invalid prog instance %d of prog %s (max %d)\n",
			instance, prog->name, prog->instances.nr);
		वापस -EINVAL;
	पूर्ण

	अगर (bpf_obj_pin(prog->instances.fds[instance], path)) अणु
		err = -त्रुटि_सं;
		cp = libbpf_म_त्रुटि_r(err, errmsg, माप(errmsg));
		pr_warn("failed to pin program: %s\n", cp);
		वापस err;
	पूर्ण
	pr_debug("pinned program '%s'\n", path);

	वापस 0;
पूर्ण

पूर्णांक bpf_program__unpin_instance(काष्ठा bpf_program *prog, स्थिर अक्षर *path,
				पूर्णांक instance)
अणु
	पूर्णांक err;

	err = check_path(path);
	अगर (err)
		वापस err;

	अगर (prog == शून्य) अणु
		pr_warn("invalid program pointer\n");
		वापस -EINVAL;
	पूर्ण

	अगर (instance < 0 || instance >= prog->instances.nr) अणु
		pr_warn("invalid prog instance %d of prog %s (max %d)\n",
			instance, prog->name, prog->instances.nr);
		वापस -EINVAL;
	पूर्ण

	err = unlink(path);
	अगर (err != 0)
		वापस -त्रुटि_सं;
	pr_debug("unpinned program '%s'\n", path);

	वापस 0;
पूर्ण

पूर्णांक bpf_program__pin(काष्ठा bpf_program *prog, स्थिर अक्षर *path)
अणु
	पूर्णांक i, err;

	err = make_parent_dir(path);
	अगर (err)
		वापस err;

	err = check_path(path);
	अगर (err)
		वापस err;

	अगर (prog == शून्य) अणु
		pr_warn("invalid program pointer\n");
		वापस -EINVAL;
	पूर्ण

	अगर (prog->instances.nr <= 0) अणु
		pr_warn("no instances of prog %s to pin\n", prog->name);
		वापस -EINVAL;
	पूर्ण

	अगर (prog->instances.nr == 1) अणु
		/* करोn't create subdirs when pinning single instance */
		वापस bpf_program__pin_instance(prog, path, 0);
	पूर्ण

	क्रम (i = 0; i < prog->instances.nr; i++) अणु
		अक्षर buf[PATH_MAX];
		पूर्णांक len;

		len = snम_लिखो(buf, PATH_MAX, "%s/%d", path, i);
		अगर (len < 0) अणु
			err = -EINVAL;
			जाओ err_unpin;
		पूर्ण अन्यथा अगर (len >= PATH_MAX) अणु
			err = -ENAMETOOLONG;
			जाओ err_unpin;
		पूर्ण

		err = bpf_program__pin_instance(prog, buf, i);
		अगर (err)
			जाओ err_unpin;
	पूर्ण

	वापस 0;

err_unpin:
	क्रम (i = i - 1; i >= 0; i--) अणु
		अक्षर buf[PATH_MAX];
		पूर्णांक len;

		len = snम_लिखो(buf, PATH_MAX, "%s/%d", path, i);
		अगर (len < 0)
			जारी;
		अन्यथा अगर (len >= PATH_MAX)
			जारी;

		bpf_program__unpin_instance(prog, buf, i);
	पूर्ण

	सूची_हटाओ(path);

	वापस err;
पूर्ण

पूर्णांक bpf_program__unpin(काष्ठा bpf_program *prog, स्थिर अक्षर *path)
अणु
	पूर्णांक i, err;

	err = check_path(path);
	अगर (err)
		वापस err;

	अगर (prog == शून्य) अणु
		pr_warn("invalid program pointer\n");
		वापस -EINVAL;
	पूर्ण

	अगर (prog->instances.nr <= 0) अणु
		pr_warn("no instances of prog %s to pin\n", prog->name);
		वापस -EINVAL;
	पूर्ण

	अगर (prog->instances.nr == 1) अणु
		/* करोn't create subdirs when pinning single instance */
		वापस bpf_program__unpin_instance(prog, path, 0);
	पूर्ण

	क्रम (i = 0; i < prog->instances.nr; i++) अणु
		अक्षर buf[PATH_MAX];
		पूर्णांक len;

		len = snम_लिखो(buf, PATH_MAX, "%s/%d", path, i);
		अगर (len < 0)
			वापस -EINVAL;
		अन्यथा अगर (len >= PATH_MAX)
			वापस -ENAMETOOLONG;

		err = bpf_program__unpin_instance(prog, buf, i);
		अगर (err)
			वापस err;
	पूर्ण

	err = सूची_हटाओ(path);
	अगर (err)
		वापस -त्रुटि_सं;

	वापस 0;
पूर्ण

पूर्णांक bpf_map__pin(काष्ठा bpf_map *map, स्थिर अक्षर *path)
अणु
	अक्षर *cp, errmsg[STRERR_बफ_मानE];
	पूर्णांक err;

	अगर (map == शून्य) अणु
		pr_warn("invalid map pointer\n");
		वापस -EINVAL;
	पूर्ण

	अगर (map->pin_path) अणु
		अगर (path && म_भेद(path, map->pin_path)) अणु
			pr_warn("map '%s' already has pin path '%s' different from '%s'\n",
				bpf_map__name(map), map->pin_path, path);
			वापस -EINVAL;
		पूर्ण अन्यथा अगर (map->pinned) अणु
			pr_debug("map '%s' already pinned at '%s'; not re-pinning\n",
				 bpf_map__name(map), map->pin_path);
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!path) अणु
			pr_warn("missing a path to pin map '%s' at\n",
				bpf_map__name(map));
			वापस -EINVAL;
		पूर्ण अन्यथा अगर (map->pinned) अणु
			pr_warn("map '%s' already pinned\n", bpf_map__name(map));
			वापस -EEXIST;
		पूर्ण

		map->pin_path = strdup(path);
		अगर (!map->pin_path) अणु
			err = -त्रुटि_सं;
			जाओ out_err;
		पूर्ण
	पूर्ण

	err = make_parent_dir(map->pin_path);
	अगर (err)
		वापस err;

	err = check_path(map->pin_path);
	अगर (err)
		वापस err;

	अगर (bpf_obj_pin(map->fd, map->pin_path)) अणु
		err = -त्रुटि_सं;
		जाओ out_err;
	पूर्ण

	map->pinned = true;
	pr_debug("pinned map '%s'\n", map->pin_path);

	वापस 0;

out_err:
	cp = libbpf_म_त्रुटि_r(-err, errmsg, माप(errmsg));
	pr_warn("failed to pin map: %s\n", cp);
	वापस err;
पूर्ण

पूर्णांक bpf_map__unpin(काष्ठा bpf_map *map, स्थिर अक्षर *path)
अणु
	पूर्णांक err;

	अगर (map == शून्य) अणु
		pr_warn("invalid map pointer\n");
		वापस -EINVAL;
	पूर्ण

	अगर (map->pin_path) अणु
		अगर (path && म_भेद(path, map->pin_path)) अणु
			pr_warn("map '%s' already has pin path '%s' different from '%s'\n",
				bpf_map__name(map), map->pin_path, path);
			वापस -EINVAL;
		पूर्ण
		path = map->pin_path;
	पूर्ण अन्यथा अगर (!path) अणु
		pr_warn("no path to unpin map '%s' from\n",
			bpf_map__name(map));
		वापस -EINVAL;
	पूर्ण

	err = check_path(path);
	अगर (err)
		वापस err;

	err = unlink(path);
	अगर (err != 0)
		वापस -त्रुटि_सं;

	map->pinned = false;
	pr_debug("unpinned map '%s' from '%s'\n", bpf_map__name(map), path);

	वापस 0;
पूर्ण

पूर्णांक bpf_map__set_pin_path(काष्ठा bpf_map *map, स्थिर अक्षर *path)
अणु
	अक्षर *new = शून्य;

	अगर (path) अणु
		new = strdup(path);
		अगर (!new)
			वापस -त्रुटि_सं;
	पूर्ण

	मुक्त(map->pin_path);
	map->pin_path = new;
	वापस 0;
पूर्ण

स्थिर अक्षर *bpf_map__get_pin_path(स्थिर काष्ठा bpf_map *map)
अणु
	वापस map->pin_path;
पूर्ण

bool bpf_map__is_pinned(स्थिर काष्ठा bpf_map *map)
अणु
	वापस map->pinned;
पूर्ण

अटल व्योम sanitize_pin_path(अक्षर *s)
अणु
	/* bpffs disallows periods in path names */
	जबतक (*s) अणु
		अगर (*s == '.')
			*s = '_';
		s++;
	पूर्ण
पूर्ण

पूर्णांक bpf_object__pin_maps(काष्ठा bpf_object *obj, स्थिर अक्षर *path)
अणु
	काष्ठा bpf_map *map;
	पूर्णांक err;

	अगर (!obj)
		वापस -ENOENT;

	अगर (!obj->loaded) अणु
		pr_warn("object not yet loaded; load it first\n");
		वापस -ENOENT;
	पूर्ण

	bpf_object__क्रम_each_map(map, obj) अणु
		अक्षर *pin_path = शून्य;
		अक्षर buf[PATH_MAX];

		अगर (path) अणु
			पूर्णांक len;

			len = snम_लिखो(buf, PATH_MAX, "%s/%s", path,
				       bpf_map__name(map));
			अगर (len < 0) अणु
				err = -EINVAL;
				जाओ err_unpin_maps;
			पूर्ण अन्यथा अगर (len >= PATH_MAX) अणु
				err = -ENAMETOOLONG;
				जाओ err_unpin_maps;
			पूर्ण
			sanitize_pin_path(buf);
			pin_path = buf;
		पूर्ण अन्यथा अगर (!map->pin_path) अणु
			जारी;
		पूर्ण

		err = bpf_map__pin(map, pin_path);
		अगर (err)
			जाओ err_unpin_maps;
	पूर्ण

	वापस 0;

err_unpin_maps:
	जबतक ((map = bpf_map__prev(map, obj))) अणु
		अगर (!map->pin_path)
			जारी;

		bpf_map__unpin(map, शून्य);
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक bpf_object__unpin_maps(काष्ठा bpf_object *obj, स्थिर अक्षर *path)
अणु
	काष्ठा bpf_map *map;
	पूर्णांक err;

	अगर (!obj)
		वापस -ENOENT;

	bpf_object__क्रम_each_map(map, obj) अणु
		अक्षर *pin_path = शून्य;
		अक्षर buf[PATH_MAX];

		अगर (path) अणु
			पूर्णांक len;

			len = snम_लिखो(buf, PATH_MAX, "%s/%s", path,
				       bpf_map__name(map));
			अगर (len < 0)
				वापस -EINVAL;
			अन्यथा अगर (len >= PATH_MAX)
				वापस -ENAMETOOLONG;
			sanitize_pin_path(buf);
			pin_path = buf;
		पूर्ण अन्यथा अगर (!map->pin_path) अणु
			जारी;
		पूर्ण

		err = bpf_map__unpin(map, pin_path);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक bpf_object__pin_programs(काष्ठा bpf_object *obj, स्थिर अक्षर *path)
अणु
	काष्ठा bpf_program *prog;
	पूर्णांक err;

	अगर (!obj)
		वापस -ENOENT;

	अगर (!obj->loaded) अणु
		pr_warn("object not yet loaded; load it first\n");
		वापस -ENOENT;
	पूर्ण

	bpf_object__क्रम_each_program(prog, obj) अणु
		अक्षर buf[PATH_MAX];
		पूर्णांक len;

		len = snम_लिखो(buf, PATH_MAX, "%s/%s", path,
			       prog->pin_name);
		अगर (len < 0) अणु
			err = -EINVAL;
			जाओ err_unpin_programs;
		पूर्ण अन्यथा अगर (len >= PATH_MAX) अणु
			err = -ENAMETOOLONG;
			जाओ err_unpin_programs;
		पूर्ण

		err = bpf_program__pin(prog, buf);
		अगर (err)
			जाओ err_unpin_programs;
	पूर्ण

	वापस 0;

err_unpin_programs:
	जबतक ((prog = bpf_program__prev(prog, obj))) अणु
		अक्षर buf[PATH_MAX];
		पूर्णांक len;

		len = snम_लिखो(buf, PATH_MAX, "%s/%s", path,
			       prog->pin_name);
		अगर (len < 0)
			जारी;
		अन्यथा अगर (len >= PATH_MAX)
			जारी;

		bpf_program__unpin(prog, buf);
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक bpf_object__unpin_programs(काष्ठा bpf_object *obj, स्थिर अक्षर *path)
अणु
	काष्ठा bpf_program *prog;
	पूर्णांक err;

	अगर (!obj)
		वापस -ENOENT;

	bpf_object__क्रम_each_program(prog, obj) अणु
		अक्षर buf[PATH_MAX];
		पूर्णांक len;

		len = snम_लिखो(buf, PATH_MAX, "%s/%s", path,
			       prog->pin_name);
		अगर (len < 0)
			वापस -EINVAL;
		अन्यथा अगर (len >= PATH_MAX)
			वापस -ENAMETOOLONG;

		err = bpf_program__unpin(prog, buf);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक bpf_object__pin(काष्ठा bpf_object *obj, स्थिर अक्षर *path)
अणु
	पूर्णांक err;

	err = bpf_object__pin_maps(obj, path);
	अगर (err)
		वापस err;

	err = bpf_object__pin_programs(obj, path);
	अगर (err) अणु
		bpf_object__unpin_maps(obj, path);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम bpf_map__destroy(काष्ठा bpf_map *map)
अणु
	अगर (map->clear_priv)
		map->clear_priv(map, map->priv);
	map->priv = शून्य;
	map->clear_priv = शून्य;

	अगर (map->inner_map) अणु
		bpf_map__destroy(map->inner_map);
		zमुक्त(&map->inner_map);
	पूर्ण

	zमुक्त(&map->init_slots);
	map->init_slots_sz = 0;

	अगर (map->mmaped) अणु
		munmap(map->mmaped, bpf_map_mmap_sz(map));
		map->mmaped = शून्य;
	पूर्ण

	अगर (map->st_ops) अणु
		zमुक्त(&map->st_ops->data);
		zमुक्त(&map->st_ops->progs);
		zमुक्त(&map->st_ops->kern_func_off);
		zमुक्त(&map->st_ops);
	पूर्ण

	zमुक्त(&map->name);
	zमुक्त(&map->pin_path);

	अगर (map->fd >= 0)
		zबंद(map->fd);
पूर्ण

व्योम bpf_object__बंद(काष्ठा bpf_object *obj)
अणु
	माप_प्रकार i;

	अगर (IS_ERR_OR_शून्य(obj))
		वापस;

	अगर (obj->clear_priv)
		obj->clear_priv(obj, obj->priv);

	bpf_object__elf_finish(obj);
	bpf_object__unload(obj);
	btf__मुक्त(obj->btf);
	btf_ext__मुक्त(obj->btf_ext);

	क्रम (i = 0; i < obj->nr_maps; i++)
		bpf_map__destroy(&obj->maps[i]);

	zमुक्त(&obj->kconfig);
	zमुक्त(&obj->बाह्यs);
	obj->nr_बाह्य = 0;

	zमुक्त(&obj->maps);
	obj->nr_maps = 0;

	अगर (obj->programs && obj->nr_programs) अणु
		क्रम (i = 0; i < obj->nr_programs; i++)
			bpf_program__निकास(&obj->programs[i]);
	पूर्ण
	zमुक्त(&obj->programs);

	list_del(&obj->list);
	मुक्त(obj);
पूर्ण

काष्ठा bpf_object *
bpf_object__next(काष्ठा bpf_object *prev)
अणु
	काष्ठा bpf_object *next;

	अगर (!prev)
		next = list_first_entry(&bpf_objects_list,
					काष्ठा bpf_object,
					list);
	अन्यथा
		next = list_next_entry(prev, list);

	/* Empty list is noticed here so करोn't need checking on entry. */
	अगर (&next->list == &bpf_objects_list)
		वापस शून्य;

	वापस next;
पूर्ण

स्थिर अक्षर *bpf_object__name(स्थिर काष्ठा bpf_object *obj)
अणु
	वापस obj ? obj->name : ERR_PTR(-EINVAL);
पूर्ण

अचिन्हित पूर्णांक bpf_object__kversion(स्थिर काष्ठा bpf_object *obj)
अणु
	वापस obj ? obj->kern_version : 0;
पूर्ण

काष्ठा btf *bpf_object__btf(स्थिर काष्ठा bpf_object *obj)
अणु
	वापस obj ? obj->btf : शून्य;
पूर्ण

पूर्णांक bpf_object__btf_fd(स्थिर काष्ठा bpf_object *obj)
अणु
	वापस obj->btf ? btf__fd(obj->btf) : -1;
पूर्ण

पूर्णांक bpf_object__set_kversion(काष्ठा bpf_object *obj, __u32 kern_version)
अणु
	अगर (obj->loaded)
		वापस -EINVAL;

	obj->kern_version = kern_version;

	वापस 0;
पूर्ण

पूर्णांक bpf_object__set_priv(काष्ठा bpf_object *obj, व्योम *priv,
			 bpf_object_clear_priv_t clear_priv)
अणु
	अगर (obj->priv && obj->clear_priv)
		obj->clear_priv(obj, obj->priv);

	obj->priv = priv;
	obj->clear_priv = clear_priv;
	वापस 0;
पूर्ण

व्योम *bpf_object__priv(स्थिर काष्ठा bpf_object *obj)
अणु
	वापस obj ? obj->priv : ERR_PTR(-EINVAL);
पूर्ण

अटल काष्ठा bpf_program *
__bpf_program__iter(स्थिर काष्ठा bpf_program *p, स्थिर काष्ठा bpf_object *obj,
		    bool क्रमward)
अणु
	माप_प्रकार nr_programs = obj->nr_programs;
	sमाप_प्रकार idx;

	अगर (!nr_programs)
		वापस शून्य;

	अगर (!p)
		/* Iter from the beginning */
		वापस क्रमward ? &obj->programs[0] :
			&obj->programs[nr_programs - 1];

	अगर (p->obj != obj) अणु
		pr_warn("error: program handler doesn't match object\n");
		वापस शून्य;
	पूर्ण

	idx = (p - obj->programs) + (क्रमward ? 1 : -1);
	अगर (idx >= obj->nr_programs || idx < 0)
		वापस शून्य;
	वापस &obj->programs[idx];
पूर्ण

काष्ठा bpf_program *
bpf_program__next(काष्ठा bpf_program *prev, स्थिर काष्ठा bpf_object *obj)
अणु
	काष्ठा bpf_program *prog = prev;

	करो अणु
		prog = __bpf_program__iter(prog, obj, true);
	पूर्ण जबतक (prog && prog_is_subprog(obj, prog));

	वापस prog;
पूर्ण

काष्ठा bpf_program *
bpf_program__prev(काष्ठा bpf_program *next, स्थिर काष्ठा bpf_object *obj)
अणु
	काष्ठा bpf_program *prog = next;

	करो अणु
		prog = __bpf_program__iter(prog, obj, false);
	पूर्ण जबतक (prog && prog_is_subprog(obj, prog));

	वापस prog;
पूर्ण

पूर्णांक bpf_program__set_priv(काष्ठा bpf_program *prog, व्योम *priv,
			  bpf_program_clear_priv_t clear_priv)
अणु
	अगर (prog->priv && prog->clear_priv)
		prog->clear_priv(prog, prog->priv);

	prog->priv = priv;
	prog->clear_priv = clear_priv;
	वापस 0;
पूर्ण

व्योम *bpf_program__priv(स्थिर काष्ठा bpf_program *prog)
अणु
	वापस prog ? prog->priv : ERR_PTR(-EINVAL);
पूर्ण

व्योम bpf_program__set_अगरindex(काष्ठा bpf_program *prog, __u32 अगरindex)
अणु
	prog->prog_अगरindex = अगरindex;
पूर्ण

स्थिर अक्षर *bpf_program__name(स्थिर काष्ठा bpf_program *prog)
अणु
	वापस prog->name;
पूर्ण

स्थिर अक्षर *bpf_program__section_name(स्थिर काष्ठा bpf_program *prog)
अणु
	वापस prog->sec_name;
पूर्ण

स्थिर अक्षर *bpf_program__title(स्थिर काष्ठा bpf_program *prog, bool needs_copy)
अणु
	स्थिर अक्षर *title;

	title = prog->sec_name;
	अगर (needs_copy) अणु
		title = strdup(title);
		अगर (!title) अणु
			pr_warn("failed to strdup program title\n");
			वापस ERR_PTR(-ENOMEM);
		पूर्ण
	पूर्ण

	वापस title;
पूर्ण

bool bpf_program__स्वतःload(स्थिर काष्ठा bpf_program *prog)
अणु
	वापस prog->load;
पूर्ण

पूर्णांक bpf_program__set_स्वतःload(काष्ठा bpf_program *prog, bool स्वतःload)
अणु
	अगर (prog->obj->loaded)
		वापस -EINVAL;

	prog->load = स्वतःload;
	वापस 0;
पूर्ण

पूर्णांक bpf_program__fd(स्थिर काष्ठा bpf_program *prog)
अणु
	वापस bpf_program__nth_fd(prog, 0);
पूर्ण

माप_प्रकार bpf_program__size(स्थिर काष्ठा bpf_program *prog)
अणु
	वापस prog->insns_cnt * BPF_INSN_SZ;
पूर्ण

पूर्णांक bpf_program__set_prep(काष्ठा bpf_program *prog, पूर्णांक nr_instances,
			  bpf_program_prep_t prep)
अणु
	पूर्णांक *instances_fds;

	अगर (nr_instances <= 0 || !prep)
		वापस -EINVAL;

	अगर (prog->instances.nr > 0 || prog->instances.fds) अणु
		pr_warn("Can't set pre-processor after loading\n");
		वापस -EINVAL;
	पूर्ण

	instances_fds = दो_स्मृति(माप(पूर्णांक) * nr_instances);
	अगर (!instances_fds) अणु
		pr_warn("alloc memory failed for fds\n");
		वापस -ENOMEM;
	पूर्ण

	/* fill all fd with -1 */
	स_रखो(instances_fds, -1, माप(पूर्णांक) * nr_instances);

	prog->instances.nr = nr_instances;
	prog->instances.fds = instances_fds;
	prog->preprocessor = prep;
	वापस 0;
पूर्ण

पूर्णांक bpf_program__nth_fd(स्थिर काष्ठा bpf_program *prog, पूर्णांक n)
अणु
	पूर्णांक fd;

	अगर (!prog)
		वापस -EINVAL;

	अगर (n >= prog->instances.nr || n < 0) अणु
		pr_warn("Can't get the %dth fd from program %s: only %d instances\n",
			n, prog->name, prog->instances.nr);
		वापस -EINVAL;
	पूर्ण

	fd = prog->instances.fds[n];
	अगर (fd < 0) अणु
		pr_warn("%dth instance of program '%s' is invalid\n",
			n, prog->name);
		वापस -ENOENT;
	पूर्ण

	वापस fd;
पूर्ण

क्रमागत bpf_prog_type bpf_program__get_type(स्थिर काष्ठा bpf_program *prog)
अणु
	वापस prog->type;
पूर्ण

व्योम bpf_program__set_type(काष्ठा bpf_program *prog, क्रमागत bpf_prog_type type)
अणु
	prog->type = type;
पूर्ण

अटल bool bpf_program__is_type(स्थिर काष्ठा bpf_program *prog,
				 क्रमागत bpf_prog_type type)
अणु
	वापस prog ? (prog->type == type) : false;
पूर्ण

#घोषणा BPF_PROG_TYPE_FNS(NAME, TYPE)				\
पूर्णांक bpf_program__set_##NAME(काष्ठा bpf_program *prog)		\
अणु								\
	अगर (!prog)						\
		वापस -EINVAL;					\
	bpf_program__set_type(prog, TYPE);			\
	वापस 0;						\
पूर्ण								\
								\
bool bpf_program__is_##NAME(स्थिर काष्ठा bpf_program *prog)	\
अणु								\
	वापस bpf_program__is_type(prog, TYPE);		\
पूर्ण								\

BPF_PROG_TYPE_FNS(socket_filter, BPF_PROG_TYPE_SOCKET_FILTER);
BPF_PROG_TYPE_FNS(lsm, BPF_PROG_TYPE_LSM);
BPF_PROG_TYPE_FNS(kprobe, BPF_PROG_TYPE_KPROBE);
BPF_PROG_TYPE_FNS(sched_cls, BPF_PROG_TYPE_SCHED_CLS);
BPF_PROG_TYPE_FNS(sched_act, BPF_PROG_TYPE_SCHED_ACT);
BPF_PROG_TYPE_FNS(tracepoपूर्णांक, BPF_PROG_TYPE_TRACEPOINT);
BPF_PROG_TYPE_FNS(raw_tracepoपूर्णांक, BPF_PROG_TYPE_RAW_TRACEPOINT);
BPF_PROG_TYPE_FNS(xdp, BPF_PROG_TYPE_XDP);
BPF_PROG_TYPE_FNS(perf_event, BPF_PROG_TYPE_PERF_EVENT);
BPF_PROG_TYPE_FNS(tracing, BPF_PROG_TYPE_TRACING);
BPF_PROG_TYPE_FNS(काष्ठा_ops, BPF_PROG_TYPE_STRUCT_OPS);
BPF_PROG_TYPE_FNS(extension, BPF_PROG_TYPE_EXT);
BPF_PROG_TYPE_FNS(sk_lookup, BPF_PROG_TYPE_SK_LOOKUP);

क्रमागत bpf_attach_type
bpf_program__get_expected_attach_type(स्थिर काष्ठा bpf_program *prog)
अणु
	वापस prog->expected_attach_type;
पूर्ण

व्योम bpf_program__set_expected_attach_type(काष्ठा bpf_program *prog,
					   क्रमागत bpf_attach_type type)
अणु
	prog->expected_attach_type = type;
पूर्ण

#घोषणा BPF_PROG_SEC_IMPL(string, ptype, eatype, eatype_optional,	    \
			  attachable, attach_btf)			    \
	अणु								    \
		.sec = string,						    \
		.len = माप(string) - 1,				    \
		.prog_type = ptype,					    \
		.expected_attach_type = eatype,				    \
		.is_exp_attach_type_optional = eatype_optional,		    \
		.is_attachable = attachable,				    \
		.is_attach_btf = attach_btf,				    \
	पूर्ण

/* Programs that can NOT be attached. */
#घोषणा BPF_PROG_SEC(string, ptype) BPF_PROG_SEC_IMPL(string, ptype, 0, 0, 0, 0)

/* Programs that can be attached. */
#घोषणा BPF_APROG_SEC(string, ptype, atype) \
	BPF_PROG_SEC_IMPL(string, ptype, atype, true, 1, 0)

/* Programs that must specअगरy expected attach type at load समय. */
#घोषणा BPF_EAPROG_SEC(string, ptype, eatype) \
	BPF_PROG_SEC_IMPL(string, ptype, eatype, false, 1, 0)

/* Programs that use BTF to identअगरy attach poपूर्णांक */
#घोषणा BPF_PROG_BTF(string, ptype, eatype) \
	BPF_PROG_SEC_IMPL(string, ptype, eatype, false, 0, 1)

/* Programs that can be attached but attach type can't be identअगरied by section
 * name. Kept क्रम backward compatibility.
 */
#घोषणा BPF_APROG_COMPAT(string, ptype) BPF_PROG_SEC(string, ptype)

#घोषणा SEC_DEF(sec_pfx, ptype, ...) अणु					    \
	.sec = sec_pfx,							    \
	.len = माप(sec_pfx) - 1,					    \
	.prog_type = BPF_PROG_TYPE_##ptype,				    \
	__VA_ARGS__							    \
पूर्ण

अटल काष्ठा bpf_link *attach_kprobe(स्थिर काष्ठा bpf_sec_def *sec,
				      काष्ठा bpf_program *prog);
अटल काष्ठा bpf_link *attach_tp(स्थिर काष्ठा bpf_sec_def *sec,
				  काष्ठा bpf_program *prog);
अटल काष्ठा bpf_link *attach_raw_tp(स्थिर काष्ठा bpf_sec_def *sec,
				      काष्ठा bpf_program *prog);
अटल काष्ठा bpf_link *attach_trace(स्थिर काष्ठा bpf_sec_def *sec,
				     काष्ठा bpf_program *prog);
अटल काष्ठा bpf_link *attach_lsm(स्थिर काष्ठा bpf_sec_def *sec,
				   काष्ठा bpf_program *prog);
अटल काष्ठा bpf_link *attach_iter(स्थिर काष्ठा bpf_sec_def *sec,
				    काष्ठा bpf_program *prog);

अटल स्थिर काष्ठा bpf_sec_def section_defs[] = अणु
	BPF_PROG_SEC("socket",			BPF_PROG_TYPE_SOCKET_FILTER),
	BPF_PROG_SEC("sk_reuseport",		BPF_PROG_TYPE_SK_REUSEPORT),
	SEC_DEF("kprobe/", KPROBE,
		.attach_fn = attach_kprobe),
	BPF_PROG_SEC("uprobe/",			BPF_PROG_TYPE_KPROBE),
	SEC_DEF("kretprobe/", KPROBE,
		.attach_fn = attach_kprobe),
	BPF_PROG_SEC("uretprobe/",		BPF_PROG_TYPE_KPROBE),
	BPF_PROG_SEC("classifier",		BPF_PROG_TYPE_SCHED_CLS),
	BPF_PROG_SEC("action",			BPF_PROG_TYPE_SCHED_ACT),
	SEC_DEF("tracepoint/", TRACEPOINT,
		.attach_fn = attach_tp),
	SEC_DEF("tp/", TRACEPOINT,
		.attach_fn = attach_tp),
	SEC_DEF("raw_tracepoint/", RAW_TRACEPOINT,
		.attach_fn = attach_raw_tp),
	SEC_DEF("raw_tp/", RAW_TRACEPOINT,
		.attach_fn = attach_raw_tp),
	SEC_DEF("tp_btf/", TRACING,
		.expected_attach_type = BPF_TRACE_RAW_TP,
		.is_attach_btf = true,
		.attach_fn = attach_trace),
	SEC_DEF("fentry/", TRACING,
		.expected_attach_type = BPF_TRACE_FENTRY,
		.is_attach_btf = true,
		.attach_fn = attach_trace),
	SEC_DEF("fmod_ret/", TRACING,
		.expected_attach_type = BPF_MODIFY_RETURN,
		.is_attach_btf = true,
		.attach_fn = attach_trace),
	SEC_DEF("fexit/", TRACING,
		.expected_attach_type = BPF_TRACE_FEXIT,
		.is_attach_btf = true,
		.attach_fn = attach_trace),
	SEC_DEF("fentry.s/", TRACING,
		.expected_attach_type = BPF_TRACE_FENTRY,
		.is_attach_btf = true,
		.is_sleepable = true,
		.attach_fn = attach_trace),
	SEC_DEF("fmod_ret.s/", TRACING,
		.expected_attach_type = BPF_MODIFY_RETURN,
		.is_attach_btf = true,
		.is_sleepable = true,
		.attach_fn = attach_trace),
	SEC_DEF("fexit.s/", TRACING,
		.expected_attach_type = BPF_TRACE_FEXIT,
		.is_attach_btf = true,
		.is_sleepable = true,
		.attach_fn = attach_trace),
	SEC_DEF("freplace/", EXT,
		.is_attach_btf = true,
		.attach_fn = attach_trace),
	SEC_DEF("lsm/", LSM,
		.is_attach_btf = true,
		.expected_attach_type = BPF_LSM_MAC,
		.attach_fn = attach_lsm),
	SEC_DEF("lsm.s/", LSM,
		.is_attach_btf = true,
		.is_sleepable = true,
		.expected_attach_type = BPF_LSM_MAC,
		.attach_fn = attach_lsm),
	SEC_DEF("iter/", TRACING,
		.expected_attach_type = BPF_TRACE_ITER,
		.is_attach_btf = true,
		.attach_fn = attach_iter),
	BPF_EAPROG_SEC("xdp_devmap/",		BPF_PROG_TYPE_XDP,
						BPF_XDP_DEVMAP),
	BPF_EAPROG_SEC("xdp_cpumap/",		BPF_PROG_TYPE_XDP,
						BPF_XDP_CPUMAP),
	BPF_APROG_SEC("xdp",			BPF_PROG_TYPE_XDP,
						BPF_XDP),
	BPF_PROG_SEC("perf_event",		BPF_PROG_TYPE_PERF_EVENT),
	BPF_PROG_SEC("lwt_in",			BPF_PROG_TYPE_LWT_IN),
	BPF_PROG_SEC("lwt_out",			BPF_PROG_TYPE_LWT_OUT),
	BPF_PROG_SEC("lwt_xmit",		BPF_PROG_TYPE_LWT_XMIT),
	BPF_PROG_SEC("lwt_seg6local",		BPF_PROG_TYPE_LWT_SEG6LOCAL),
	BPF_APROG_SEC("cgroup_skb/ingress",	BPF_PROG_TYPE_CGROUP_SKB,
						BPF_CGROUP_INET_INGRESS),
	BPF_APROG_SEC("cgroup_skb/egress",	BPF_PROG_TYPE_CGROUP_SKB,
						BPF_CGROUP_INET_EGRESS),
	BPF_APROG_COMPAT("cgroup/skb",		BPF_PROG_TYPE_CGROUP_SKB),
	BPF_EAPROG_SEC("cgroup/sock_create",	BPF_PROG_TYPE_CGROUP_SOCK,
						BPF_CGROUP_INET_SOCK_CREATE),
	BPF_EAPROG_SEC("cgroup/sock_release",	BPF_PROG_TYPE_CGROUP_SOCK,
						BPF_CGROUP_INET_SOCK_RELEASE),
	BPF_APROG_SEC("cgroup/sock",		BPF_PROG_TYPE_CGROUP_SOCK,
						BPF_CGROUP_INET_SOCK_CREATE),
	BPF_EAPROG_SEC("cgroup/post_bind4",	BPF_PROG_TYPE_CGROUP_SOCK,
						BPF_CGROUP_INET4_POST_BIND),
	BPF_EAPROG_SEC("cgroup/post_bind6",	BPF_PROG_TYPE_CGROUP_SOCK,
						BPF_CGROUP_INET6_POST_BIND),
	BPF_APROG_SEC("cgroup/dev",		BPF_PROG_TYPE_CGROUP_DEVICE,
						BPF_CGROUP_DEVICE),
	BPF_APROG_SEC("sockops",		BPF_PROG_TYPE_SOCK_OPS,
						BPF_CGROUP_SOCK_OPS),
	BPF_APROG_SEC("sk_skb/stream_parser",	BPF_PROG_TYPE_SK_SKB,
						BPF_SK_SKB_STREAM_PARSER),
	BPF_APROG_SEC("sk_skb/stream_verdict",	BPF_PROG_TYPE_SK_SKB,
						BPF_SK_SKB_STREAM_VERDICT),
	BPF_APROG_COMPAT("sk_skb",		BPF_PROG_TYPE_SK_SKB),
	BPF_APROG_SEC("sk_msg",			BPF_PROG_TYPE_SK_MSG,
						BPF_SK_MSG_VERDICT),
	BPF_APROG_SEC("lirc_mode2",		BPF_PROG_TYPE_LIRC_MODE2,
						BPF_LIRC_MODE2),
	BPF_APROG_SEC("flow_dissector",		BPF_PROG_TYPE_FLOW_DISSECTOR,
						BPF_FLOW_DISSECTOR),
	BPF_EAPROG_SEC("cgroup/bind4",		BPF_PROG_TYPE_CGROUP_SOCK_ADDR,
						BPF_CGROUP_INET4_BIND),
	BPF_EAPROG_SEC("cgroup/bind6",		BPF_PROG_TYPE_CGROUP_SOCK_ADDR,
						BPF_CGROUP_INET6_BIND),
	BPF_EAPROG_SEC("cgroup/connect4",	BPF_PROG_TYPE_CGROUP_SOCK_ADDR,
						BPF_CGROUP_INET4_CONNECT),
	BPF_EAPROG_SEC("cgroup/connect6",	BPF_PROG_TYPE_CGROUP_SOCK_ADDR,
						BPF_CGROUP_INET6_CONNECT),
	BPF_EAPROG_SEC("cgroup/sendmsg4",	BPF_PROG_TYPE_CGROUP_SOCK_ADDR,
						BPF_CGROUP_UDP4_SENDMSG),
	BPF_EAPROG_SEC("cgroup/sendmsg6",	BPF_PROG_TYPE_CGROUP_SOCK_ADDR,
						BPF_CGROUP_UDP6_SENDMSG),
	BPF_EAPROG_SEC("cgroup/recvmsg4",	BPF_PROG_TYPE_CGROUP_SOCK_ADDR,
						BPF_CGROUP_UDP4_RECVMSG),
	BPF_EAPROG_SEC("cgroup/recvmsg6",	BPF_PROG_TYPE_CGROUP_SOCK_ADDR,
						BPF_CGROUP_UDP6_RECVMSG),
	BPF_EAPROG_SEC("cgroup/getpeername4",	BPF_PROG_TYPE_CGROUP_SOCK_ADDR,
						BPF_CGROUP_INET4_GETPEERNAME),
	BPF_EAPROG_SEC("cgroup/getpeername6",	BPF_PROG_TYPE_CGROUP_SOCK_ADDR,
						BPF_CGROUP_INET6_GETPEERNAME),
	BPF_EAPROG_SEC("cgroup/getsockname4",	BPF_PROG_TYPE_CGROUP_SOCK_ADDR,
						BPF_CGROUP_INET4_GETSOCKNAME),
	BPF_EAPROG_SEC("cgroup/getsockname6",	BPF_PROG_TYPE_CGROUP_SOCK_ADDR,
						BPF_CGROUP_INET6_GETSOCKNAME),
	BPF_EAPROG_SEC("cgroup/sysctl",		BPF_PROG_TYPE_CGROUP_SYSCTL,
						BPF_CGROUP_SYSCTL),
	BPF_EAPROG_SEC("cgroup/getsockopt",	BPF_PROG_TYPE_CGROUP_SOCKOPT,
						BPF_CGROUP_GETSOCKOPT),
	BPF_EAPROG_SEC("cgroup/setsockopt",	BPF_PROG_TYPE_CGROUP_SOCKOPT,
						BPF_CGROUP_SETSOCKOPT),
	BPF_PROG_SEC("struct_ops",		BPF_PROG_TYPE_STRUCT_OPS),
	BPF_EAPROG_SEC("sk_lookup/",		BPF_PROG_TYPE_SK_LOOKUP,
						BPF_SK_LOOKUP),
पूर्ण;

#अघोषित BPF_PROG_SEC_IMPL
#अघोषित BPF_PROG_SEC
#अघोषित BPF_APROG_SEC
#अघोषित BPF_EAPROG_SEC
#अघोषित BPF_APROG_COMPAT
#अघोषित SEC_DEF

#घोषणा MAX_TYPE_NAME_SIZE 32

अटल स्थिर काष्ठा bpf_sec_def *find_sec_def(स्थिर अक्षर *sec_name)
अणु
	पूर्णांक i, n = ARRAY_SIZE(section_defs);

	क्रम (i = 0; i < n; i++) अणु
		अगर (म_भेदन(sec_name,
			    section_defs[i].sec, section_defs[i].len))
			जारी;
		वापस &section_defs[i];
	पूर्ण
	वापस शून्य;
पूर्ण

अटल अक्षर *libbpf_get_type_names(bool attach_type)
अणु
	पूर्णांक i, len = ARRAY_SIZE(section_defs) * MAX_TYPE_NAME_SIZE;
	अक्षर *buf;

	buf = दो_स्मृति(len);
	अगर (!buf)
		वापस शून्य;

	buf[0] = '\0';
	/* Forge string buf with all available names */
	क्रम (i = 0; i < ARRAY_SIZE(section_defs); i++) अणु
		अगर (attach_type && !section_defs[i].is_attachable)
			जारी;

		अगर (म_माप(buf) + म_माप(section_defs[i].sec) + 2 > len) अणु
			मुक्त(buf);
			वापस शून्य;
		पूर्ण
		म_जोड़ो(buf, " ");
		म_जोड़ो(buf, section_defs[i].sec);
	पूर्ण

	वापस buf;
पूर्ण

पूर्णांक libbpf_prog_type_by_name(स्थिर अक्षर *name, क्रमागत bpf_prog_type *prog_type,
			     क्रमागत bpf_attach_type *expected_attach_type)
अणु
	स्थिर काष्ठा bpf_sec_def *sec_def;
	अक्षर *type_names;

	अगर (!name)
		वापस -EINVAL;

	sec_def = find_sec_def(name);
	अगर (sec_def) अणु
		*prog_type = sec_def->prog_type;
		*expected_attach_type = sec_def->expected_attach_type;
		वापस 0;
	पूर्ण

	pr_debug("failed to guess program type from ELF section '%s'\n", name);
	type_names = libbpf_get_type_names(false);
	अगर (type_names != शून्य) अणु
		pr_debug("supported section(type) names are:%s\n", type_names);
		मुक्त(type_names);
	पूर्ण

	वापस -ESRCH;
पूर्ण

अटल काष्ठा bpf_map *find_काष्ठा_ops_map_by_offset(काष्ठा bpf_object *obj,
						     माप_प्रकार offset)
अणु
	काष्ठा bpf_map *map;
	माप_प्रकार i;

	क्रम (i = 0; i < obj->nr_maps; i++) अणु
		map = &obj->maps[i];
		अगर (!bpf_map__is_काष्ठा_ops(map))
			जारी;
		अगर (map->sec_offset <= offset &&
		    offset - map->sec_offset < map->def.value_size)
			वापस map;
	पूर्ण

	वापस शून्य;
पूर्ण

/* Collect the reloc from ELF and populate the st_ops->progs[] */
अटल पूर्णांक bpf_object__collect_st_ops_relos(काष्ठा bpf_object *obj,
					    GElf_Shdr *shdr, Elf_Data *data)
अणु
	स्थिर काष्ठा btf_member *member;
	काष्ठा bpf_काष्ठा_ops *st_ops;
	काष्ठा bpf_program *prog;
	अचिन्हित पूर्णांक shdr_idx;
	स्थिर काष्ठा btf *btf;
	काष्ठा bpf_map *map;
	Elf_Data *symbols;
	अचिन्हित पूर्णांक moff, insn_idx;
	स्थिर अक्षर *name;
	__u32 member_idx;
	GElf_Sym sym;
	GElf_Rel rel;
	पूर्णांक i, nrels;

	symbols = obj->efile.symbols;
	btf = obj->btf;
	nrels = shdr->sh_size / shdr->sh_entsize;
	क्रम (i = 0; i < nrels; i++) अणु
		अगर (!gelf_getrel(data, i, &rel)) अणु
			pr_warn("struct_ops reloc: failed to get %d reloc\n", i);
			वापस -LIBBPF_ERRNO__FORMAT;
		पूर्ण

		अगर (!gelf_माला_लोym(symbols, GELF_R_SYM(rel.r_info), &sym)) अणु
			pr_warn("struct_ops reloc: symbol %zx not found\n",
				(माप_प्रकार)GELF_R_SYM(rel.r_info));
			वापस -LIBBPF_ERRNO__FORMAT;
		पूर्ण

		name = elf_sym_str(obj, sym.st_name) ?: "<?>";
		map = find_काष्ठा_ops_map_by_offset(obj, rel.r_offset);
		अगर (!map) अणु
			pr_warn("struct_ops reloc: cannot find map at rel.r_offset %zu\n",
				(माप_प्रकार)rel.r_offset);
			वापस -EINVAL;
		पूर्ण

		moff = rel.r_offset - map->sec_offset;
		shdr_idx = sym.st_shndx;
		st_ops = map->st_ops;
		pr_debug("struct_ops reloc %s: for %lld value %lld shdr_idx %u rel.r_offset %zu map->sec_offset %zu name %d (\'%s\')\n",
			 map->name,
			 (दीर्घ दीर्घ)(rel.r_info >> 32),
			 (दीर्घ दीर्घ)sym.st_value,
			 shdr_idx, (माप_प्रकार)rel.r_offset,
			 map->sec_offset, sym.st_name, name);

		अगर (shdr_idx >= SHN_LORESERVE) अणु
			pr_warn("struct_ops reloc %s: rel.r_offset %zu shdr_idx %u unsupported non-static function\n",
				map->name, (माप_प्रकार)rel.r_offset, shdr_idx);
			वापस -LIBBPF_ERRNO__RELOC;
		पूर्ण
		अगर (sym.st_value % BPF_INSN_SZ) अणु
			pr_warn("struct_ops reloc %s: invalid target program offset %llu\n",
				map->name, (अचिन्हित दीर्घ दीर्घ)sym.st_value);
			वापस -LIBBPF_ERRNO__FORMAT;
		पूर्ण
		insn_idx = sym.st_value / BPF_INSN_SZ;

		member = find_member_by_offset(st_ops->type, moff * 8);
		अगर (!member) अणु
			pr_warn("struct_ops reloc %s: cannot find member at moff %u\n",
				map->name, moff);
			वापस -EINVAL;
		पूर्ण
		member_idx = member - btf_members(st_ops->type);
		name = btf__name_by_offset(btf, member->name_off);

		अगर (!resolve_func_ptr(btf, member->type, शून्य)) अणु
			pr_warn("struct_ops reloc %s: cannot relocate non func ptr %s\n",
				map->name, name);
			वापस -EINVAL;
		पूर्ण

		prog = find_prog_by_sec_insn(obj, shdr_idx, insn_idx);
		अगर (!prog) अणु
			pr_warn("struct_ops reloc %s: cannot find prog at shdr_idx %u to relocate func ptr %s\n",
				map->name, shdr_idx, name);
			वापस -EINVAL;
		पूर्ण

		अगर (prog->type == BPF_PROG_TYPE_UNSPEC) अणु
			स्थिर काष्ठा bpf_sec_def *sec_def;

			sec_def = find_sec_def(prog->sec_name);
			अगर (sec_def &&
			    sec_def->prog_type != BPF_PROG_TYPE_STRUCT_OPS) अणु
				/* क्रम pr_warn */
				prog->type = sec_def->prog_type;
				जाओ invalid_prog;
			पूर्ण

			prog->type = BPF_PROG_TYPE_STRUCT_OPS;
			prog->attach_btf_id = st_ops->type_id;
			prog->expected_attach_type = member_idx;
		पूर्ण अन्यथा अगर (prog->type != BPF_PROG_TYPE_STRUCT_OPS ||
			   prog->attach_btf_id != st_ops->type_id ||
			   prog->expected_attach_type != member_idx) अणु
			जाओ invalid_prog;
		पूर्ण
		st_ops->progs[member_idx] = prog;
	पूर्ण

	वापस 0;

invalid_prog:
	pr_warn("struct_ops reloc %s: cannot use prog %s in sec %s with type %u attach_btf_id %u expected_attach_type %u for func ptr %s\n",
		map->name, prog->name, prog->sec_name, prog->type,
		prog->attach_btf_id, prog->expected_attach_type, name);
	वापस -EINVAL;
पूर्ण

#घोषणा BTF_TRACE_PREFIX "btf_trace_"
#घोषणा BTF_LSM_PREFIX "bpf_lsm_"
#घोषणा BTF_ITER_PREFIX "bpf_iter_"
#घोषणा BTF_MAX_NAME_SIZE 128

अटल पूर्णांक find_btf_by_prefix_kind(स्थिर काष्ठा btf *btf, स्थिर अक्षर *prefix,
				   स्थिर अक्षर *name, __u32 kind)
अणु
	अक्षर btf_type_name[BTF_MAX_NAME_SIZE];
	पूर्णांक ret;

	ret = snम_लिखो(btf_type_name, माप(btf_type_name),
		       "%s%s", prefix, name);
	/* snम_लिखो वापसs the number of अक्षरacters written excluding the
	 * the terminating null. So, अगर >= BTF_MAX_NAME_SIZE are written, it
	 * indicates truncation.
	 */
	अगर (ret < 0 || ret >= माप(btf_type_name))
		वापस -ENAMETOOLONG;
	वापस btf__find_by_name_kind(btf, btf_type_name, kind);
पूर्ण

अटल अंतरभूत पूर्णांक find_attach_btf_id(काष्ठा btf *btf, स्थिर अक्षर *name,
				     क्रमागत bpf_attach_type attach_type)
अणु
	पूर्णांक err;

	अगर (attach_type == BPF_TRACE_RAW_TP)
		err = find_btf_by_prefix_kind(btf, BTF_TRACE_PREFIX, name,
					      BTF_KIND_TYPEDEF);
	अन्यथा अगर (attach_type == BPF_LSM_MAC)
		err = find_btf_by_prefix_kind(btf, BTF_LSM_PREFIX, name,
					      BTF_KIND_FUNC);
	अन्यथा अगर (attach_type == BPF_TRACE_ITER)
		err = find_btf_by_prefix_kind(btf, BTF_ITER_PREFIX, name,
					      BTF_KIND_FUNC);
	अन्यथा
		err = btf__find_by_name_kind(btf, name, BTF_KIND_FUNC);

	वापस err;
पूर्ण

पूर्णांक libbpf_find_vmlinux_btf_id(स्थिर अक्षर *name,
			       क्रमागत bpf_attach_type attach_type)
अणु
	काष्ठा btf *btf;
	पूर्णांक err;

	btf = libbpf_find_kernel_btf();
	अगर (IS_ERR(btf)) अणु
		pr_warn("vmlinux BTF is not found\n");
		वापस -EINVAL;
	पूर्ण

	err = find_attach_btf_id(btf, name, attach_type);
	अगर (err <= 0)
		pr_warn("%s is not found in vmlinux BTF\n", name);

	btf__मुक्त(btf);
	वापस err;
पूर्ण

अटल पूर्णांक libbpf_find_prog_btf_id(स्थिर अक्षर *name, __u32 attach_prog_fd)
अणु
	काष्ठा bpf_prog_info_linear *info_linear;
	काष्ठा bpf_prog_info *info;
	काष्ठा btf *btf = शून्य;
	पूर्णांक err = -EINVAL;

	info_linear = bpf_program__get_prog_info_linear(attach_prog_fd, 0);
	अगर (IS_ERR_OR_शून्य(info_linear)) अणु
		pr_warn("failed get_prog_info_linear for FD %d\n",
			attach_prog_fd);
		वापस -EINVAL;
	पूर्ण
	info = &info_linear->info;
	अगर (!info->btf_id) अणु
		pr_warn("The target program doesn't have BTF\n");
		जाओ out;
	पूर्ण
	अगर (btf__get_from_id(info->btf_id, &btf)) अणु
		pr_warn("Failed to get BTF of the program\n");
		जाओ out;
	पूर्ण
	err = btf__find_by_name_kind(btf, name, BTF_KIND_FUNC);
	btf__मुक्त(btf);
	अगर (err <= 0) अणु
		pr_warn("%s is not found in prog's BTF\n", name);
		जाओ out;
	पूर्ण
out:
	मुक्त(info_linear);
	वापस err;
पूर्ण

अटल पूर्णांक find_kernel_btf_id(काष्ठा bpf_object *obj, स्थिर अक्षर *attach_name,
			      क्रमागत bpf_attach_type attach_type,
			      पूर्णांक *btf_obj_fd, पूर्णांक *btf_type_id)
अणु
	पूर्णांक ret, i;

	ret = find_attach_btf_id(obj->btf_vmlinux, attach_name, attach_type);
	अगर (ret > 0) अणु
		*btf_obj_fd = 0; /* vmlinux BTF */
		*btf_type_id = ret;
		वापस 0;
	पूर्ण
	अगर (ret != -ENOENT)
		वापस ret;

	ret = load_module_btfs(obj);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < obj->btf_module_cnt; i++) अणु
		स्थिर काष्ठा module_btf *mod = &obj->btf_modules[i];

		ret = find_attach_btf_id(mod->btf, attach_name, attach_type);
		अगर (ret > 0) अणु
			*btf_obj_fd = mod->fd;
			*btf_type_id = ret;
			वापस 0;
		पूर्ण
		अगर (ret == -ENOENT)
			जारी;

		वापस ret;
	पूर्ण

	वापस -ESRCH;
पूर्ण

अटल पूर्णांक libbpf_find_attach_btf_id(काष्ठा bpf_program *prog, पूर्णांक *btf_obj_fd, पूर्णांक *btf_type_id)
अणु
	क्रमागत bpf_attach_type attach_type = prog->expected_attach_type;
	__u32 attach_prog_fd = prog->attach_prog_fd;
	स्थिर अक्षर *name = prog->sec_name, *attach_name;
	स्थिर काष्ठा bpf_sec_def *sec = शून्य;
	पूर्णांक i, err;

	अगर (!name)
		वापस -EINVAL;

	क्रम (i = 0; i < ARRAY_SIZE(section_defs); i++) अणु
		अगर (!section_defs[i].is_attach_btf)
			जारी;
		अगर (म_भेदन(name, section_defs[i].sec, section_defs[i].len))
			जारी;

		sec = &section_defs[i];
		अवरोध;
	पूर्ण

	अगर (!sec) अणु
		pr_warn("failed to identify BTF ID based on ELF section name '%s'\n", name);
		वापस -ESRCH;
	पूर्ण
	attach_name = name + sec->len;

	/* BPF program's BTF ID */
	अगर (attach_prog_fd) अणु
		err = libbpf_find_prog_btf_id(attach_name, attach_prog_fd);
		अगर (err < 0) अणु
			pr_warn("failed to find BPF program (FD %d) BTF ID for '%s': %d\n",
				 attach_prog_fd, attach_name, err);
			वापस err;
		पूर्ण
		*btf_obj_fd = 0;
		*btf_type_id = err;
		वापस 0;
	पूर्ण

	/* kernel/module BTF ID */
	err = find_kernel_btf_id(prog->obj, attach_name, attach_type, btf_obj_fd, btf_type_id);
	अगर (err) अणु
		pr_warn("failed to find kernel BTF type ID of '%s': %d\n", attach_name, err);
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक libbpf_attach_type_by_name(स्थिर अक्षर *name,
			       क्रमागत bpf_attach_type *attach_type)
अणु
	अक्षर *type_names;
	पूर्णांक i;

	अगर (!name)
		वापस -EINVAL;

	क्रम (i = 0; i < ARRAY_SIZE(section_defs); i++) अणु
		अगर (म_भेदन(name, section_defs[i].sec, section_defs[i].len))
			जारी;
		अगर (!section_defs[i].is_attachable)
			वापस -EINVAL;
		*attach_type = section_defs[i].expected_attach_type;
		वापस 0;
	पूर्ण
	pr_debug("failed to guess attach type based on ELF section name '%s'\n", name);
	type_names = libbpf_get_type_names(true);
	अगर (type_names != शून्य) अणु
		pr_debug("attachable section(type) names are:%s\n", type_names);
		मुक्त(type_names);
	पूर्ण

	वापस -EINVAL;
पूर्ण

पूर्णांक bpf_map__fd(स्थिर काष्ठा bpf_map *map)
अणु
	वापस map ? map->fd : -EINVAL;
पूर्ण

स्थिर काष्ठा bpf_map_def *bpf_map__def(स्थिर काष्ठा bpf_map *map)
अणु
	वापस map ? &map->def : ERR_PTR(-EINVAL);
पूर्ण

स्थिर अक्षर *bpf_map__name(स्थिर काष्ठा bpf_map *map)
अणु
	वापस map ? map->name : शून्य;
पूर्ण

क्रमागत bpf_map_type bpf_map__type(स्थिर काष्ठा bpf_map *map)
अणु
	वापस map->def.type;
पूर्ण

पूर्णांक bpf_map__set_type(काष्ठा bpf_map *map, क्रमागत bpf_map_type type)
अणु
	अगर (map->fd >= 0)
		वापस -EBUSY;
	map->def.type = type;
	वापस 0;
पूर्ण

__u32 bpf_map__map_flags(स्थिर काष्ठा bpf_map *map)
अणु
	वापस map->def.map_flags;
पूर्ण

पूर्णांक bpf_map__set_map_flags(काष्ठा bpf_map *map, __u32 flags)
अणु
	अगर (map->fd >= 0)
		वापस -EBUSY;
	map->def.map_flags = flags;
	वापस 0;
पूर्ण

__u32 bpf_map__numa_node(स्थिर काष्ठा bpf_map *map)
अणु
	वापस map->numa_node;
पूर्ण

पूर्णांक bpf_map__set_numa_node(काष्ठा bpf_map *map, __u32 numa_node)
अणु
	अगर (map->fd >= 0)
		वापस -EBUSY;
	map->numa_node = numa_node;
	वापस 0;
पूर्ण

__u32 bpf_map__key_size(स्थिर काष्ठा bpf_map *map)
अणु
	वापस map->def.key_size;
पूर्ण

पूर्णांक bpf_map__set_key_size(काष्ठा bpf_map *map, __u32 size)
अणु
	अगर (map->fd >= 0)
		वापस -EBUSY;
	map->def.key_size = size;
	वापस 0;
पूर्ण

__u32 bpf_map__value_size(स्थिर काष्ठा bpf_map *map)
अणु
	वापस map->def.value_size;
पूर्ण

पूर्णांक bpf_map__set_value_size(काष्ठा bpf_map *map, __u32 size)
अणु
	अगर (map->fd >= 0)
		वापस -EBUSY;
	map->def.value_size = size;
	वापस 0;
पूर्ण

__u32 bpf_map__btf_key_type_id(स्थिर काष्ठा bpf_map *map)
अणु
	वापस map ? map->btf_key_type_id : 0;
पूर्ण

__u32 bpf_map__btf_value_type_id(स्थिर काष्ठा bpf_map *map)
अणु
	वापस map ? map->btf_value_type_id : 0;
पूर्ण

पूर्णांक bpf_map__set_priv(काष्ठा bpf_map *map, व्योम *priv,
		     bpf_map_clear_priv_t clear_priv)
अणु
	अगर (!map)
		वापस -EINVAL;

	अगर (map->priv) अणु
		अगर (map->clear_priv)
			map->clear_priv(map, map->priv);
	पूर्ण

	map->priv = priv;
	map->clear_priv = clear_priv;
	वापस 0;
पूर्ण

व्योम *bpf_map__priv(स्थिर काष्ठा bpf_map *map)
अणु
	वापस map ? map->priv : ERR_PTR(-EINVAL);
पूर्ण

पूर्णांक bpf_map__set_initial_value(काष्ठा bpf_map *map,
			       स्थिर व्योम *data, माप_प्रकार size)
अणु
	अगर (!map->mmaped || map->libbpf_type == LIBBPF_MAP_KCONFIG ||
	    size != map->def.value_size || map->fd >= 0)
		वापस -EINVAL;

	स_नकल(map->mmaped, data, size);
	वापस 0;
पूर्ण

bool bpf_map__is_offload_neutral(स्थिर काष्ठा bpf_map *map)
अणु
	वापस map->def.type == BPF_MAP_TYPE_PERF_EVENT_ARRAY;
पूर्ण

bool bpf_map__is_पूर्णांकernal(स्थिर काष्ठा bpf_map *map)
अणु
	वापस map->libbpf_type != LIBBPF_MAP_UNSPEC;
पूर्ण

__u32 bpf_map__अगरindex(स्थिर काष्ठा bpf_map *map)
अणु
	वापस map->map_अगरindex;
पूर्ण

पूर्णांक bpf_map__set_अगरindex(काष्ठा bpf_map *map, __u32 अगरindex)
अणु
	अगर (map->fd >= 0)
		वापस -EBUSY;
	map->map_अगरindex = अगरindex;
	वापस 0;
पूर्ण

पूर्णांक bpf_map__set_inner_map_fd(काष्ठा bpf_map *map, पूर्णांक fd)
अणु
	अगर (!bpf_map_type__is_map_in_map(map->def.type)) अणु
		pr_warn("error: unsupported map type\n");
		वापस -EINVAL;
	पूर्ण
	अगर (map->inner_map_fd != -1) अणु
		pr_warn("error: inner_map_fd already specified\n");
		वापस -EINVAL;
	पूर्ण
	zमुक्त(&map->inner_map);
	map->inner_map_fd = fd;
	वापस 0;
पूर्ण

अटल काष्ठा bpf_map *
__bpf_map__iter(स्थिर काष्ठा bpf_map *m, स्थिर काष्ठा bpf_object *obj, पूर्णांक i)
अणु
	sमाप_प्रकार idx;
	काष्ठा bpf_map *s, *e;

	अगर (!obj || !obj->maps)
		वापस शून्य;

	s = obj->maps;
	e = obj->maps + obj->nr_maps;

	अगर ((m < s) || (m >= e)) अणु
		pr_warn("error in %s: map handler doesn't belong to object\n",
			 __func__);
		वापस शून्य;
	पूर्ण

	idx = (m - obj->maps) + i;
	अगर (idx >= obj->nr_maps || idx < 0)
		वापस शून्य;
	वापस &obj->maps[idx];
पूर्ण

काष्ठा bpf_map *
bpf_map__next(स्थिर काष्ठा bpf_map *prev, स्थिर काष्ठा bpf_object *obj)
अणु
	अगर (prev == शून्य)
		वापस obj->maps;

	वापस __bpf_map__iter(prev, obj, 1);
पूर्ण

काष्ठा bpf_map *
bpf_map__prev(स्थिर काष्ठा bpf_map *next, स्थिर काष्ठा bpf_object *obj)
अणु
	अगर (next == शून्य) अणु
		अगर (!obj->nr_maps)
			वापस शून्य;
		वापस obj->maps + obj->nr_maps - 1;
	पूर्ण

	वापस __bpf_map__iter(next, obj, -1);
पूर्ण

काष्ठा bpf_map *
bpf_object__find_map_by_name(स्थिर काष्ठा bpf_object *obj, स्थिर अक्षर *name)
अणु
	काष्ठा bpf_map *pos;

	bpf_object__क्रम_each_map(pos, obj) अणु
		अगर (pos->name && !म_भेद(pos->name, name))
			वापस pos;
	पूर्ण
	वापस शून्य;
पूर्ण

पूर्णांक
bpf_object__find_map_fd_by_name(स्थिर काष्ठा bpf_object *obj, स्थिर अक्षर *name)
अणु
	वापस bpf_map__fd(bpf_object__find_map_by_name(obj, name));
पूर्ण

काष्ठा bpf_map *
bpf_object__find_map_by_offset(काष्ठा bpf_object *obj, माप_प्रकार offset)
अणु
	वापस ERR_PTR(-ENOTSUP);
पूर्ण

दीर्घ libbpf_get_error(स्थिर व्योम *ptr)
अणु
	वापस PTR_ERR_OR_ZERO(ptr);
पूर्ण

पूर्णांक bpf_prog_load(स्थिर अक्षर *file, क्रमागत bpf_prog_type type,
		  काष्ठा bpf_object **pobj, पूर्णांक *prog_fd)
अणु
	काष्ठा bpf_prog_load_attr attr;

	स_रखो(&attr, 0, माप(काष्ठा bpf_prog_load_attr));
	attr.file = file;
	attr.prog_type = type;
	attr.expected_attach_type = 0;

	वापस bpf_prog_load_xattr(&attr, pobj, prog_fd);
पूर्ण

पूर्णांक bpf_prog_load_xattr(स्थिर काष्ठा bpf_prog_load_attr *attr,
			काष्ठा bpf_object **pobj, पूर्णांक *prog_fd)
अणु
	काष्ठा bpf_object_खोलो_attr खोलो_attr = अणुपूर्ण;
	काष्ठा bpf_program *prog, *first_prog = शून्य;
	काष्ठा bpf_object *obj;
	काष्ठा bpf_map *map;
	पूर्णांक err;

	अगर (!attr)
		वापस -EINVAL;
	अगर (!attr->file)
		वापस -EINVAL;

	खोलो_attr.file = attr->file;
	खोलो_attr.prog_type = attr->prog_type;

	obj = bpf_object__खोलो_xattr(&खोलो_attr);
	अगर (IS_ERR_OR_शून्य(obj))
		वापस -ENOENT;

	bpf_object__क्रम_each_program(prog, obj) अणु
		क्रमागत bpf_attach_type attach_type = attr->expected_attach_type;
		/*
		 * to preserve backwards compatibility, bpf_prog_load treats
		 * attr->prog_type, अगर specअगरied, as an override to whatever
		 * bpf_object__खोलो guessed
		 */
		अगर (attr->prog_type != BPF_PROG_TYPE_UNSPEC) अणु
			bpf_program__set_type(prog, attr->prog_type);
			bpf_program__set_expected_attach_type(prog,
							      attach_type);
		पूर्ण
		अगर (bpf_program__get_type(prog) == BPF_PROG_TYPE_UNSPEC) अणु
			/*
			 * we haven't guessed from section name and user
			 * didn't provide a fallback type, too bad...
			 */
			bpf_object__बंद(obj);
			वापस -EINVAL;
		पूर्ण

		prog->prog_अगरindex = attr->अगरindex;
		prog->log_level = attr->log_level;
		prog->prog_flags |= attr->prog_flags;
		अगर (!first_prog)
			first_prog = prog;
	पूर्ण

	bpf_object__क्रम_each_map(map, obj) अणु
		अगर (!bpf_map__is_offload_neutral(map))
			map->map_अगरindex = attr->अगरindex;
	पूर्ण

	अगर (!first_prog) अणु
		pr_warn("object file doesn't contain bpf program\n");
		bpf_object__बंद(obj);
		वापस -ENOENT;
	पूर्ण

	err = bpf_object__load(obj);
	अगर (err) अणु
		bpf_object__बंद(obj);
		वापस err;
	पूर्ण

	*pobj = obj;
	*prog_fd = bpf_program__fd(first_prog);
	वापस 0;
पूर्ण

काष्ठा bpf_link अणु
	पूर्णांक (*detach)(काष्ठा bpf_link *link);
	पूर्णांक (*destroy)(काष्ठा bpf_link *link);
	अक्षर *pin_path;		/* शून्य, अगर not pinned */
	पूर्णांक fd;			/* hook FD, -1 अगर not applicable */
	bool disconnected;
पूर्ण;

/* Replace link's underlying BPF program with the new one */
पूर्णांक bpf_link__update_program(काष्ठा bpf_link *link, काष्ठा bpf_program *prog)
अणु
	वापस bpf_link_update(bpf_link__fd(link), bpf_program__fd(prog), शून्य);
पूर्ण

/* Release "ownership" of underlying BPF resource (typically, BPF program
 * attached to some BPF hook, e.g., tracepoपूर्णांक, kprobe, etc). Disconnected
 * link, when deकाष्ठाed through bpf_link__destroy() call won't attempt to
 * detach/unregisted that BPF resource. This is useful in situations where,
 * say, attached BPF program has to outlive userspace program that attached it
 * in the प्रणाली. Depending on type of BPF program, though, there might be
 * additional steps (like pinning BPF program in BPF FS) necessary to ensure
 * निकास of userspace program करोesn't trigger स्वतःmatic detachment and clean up
 * inside the kernel.
 */
व्योम bpf_link__disconnect(काष्ठा bpf_link *link)
अणु
	link->disconnected = true;
पूर्ण

पूर्णांक bpf_link__destroy(काष्ठा bpf_link *link)
अणु
	पूर्णांक err = 0;

	अगर (IS_ERR_OR_शून्य(link))
		वापस 0;

	अगर (!link->disconnected && link->detach)
		err = link->detach(link);
	अगर (link->destroy)
		link->destroy(link);
	अगर (link->pin_path)
		मुक्त(link->pin_path);
	मुक्त(link);

	वापस err;
पूर्ण

पूर्णांक bpf_link__fd(स्थिर काष्ठा bpf_link *link)
अणु
	वापस link->fd;
पूर्ण

स्थिर अक्षर *bpf_link__pin_path(स्थिर काष्ठा bpf_link *link)
अणु
	वापस link->pin_path;
पूर्ण

अटल पूर्णांक bpf_link__detach_fd(काष्ठा bpf_link *link)
अणु
	वापस बंद(link->fd);
पूर्ण

काष्ठा bpf_link *bpf_link__खोलो(स्थिर अक्षर *path)
अणु
	काष्ठा bpf_link *link;
	पूर्णांक fd;

	fd = bpf_obj_get(path);
	अगर (fd < 0) अणु
		fd = -त्रुटि_सं;
		pr_warn("failed to open link at %s: %d\n", path, fd);
		वापस ERR_PTR(fd);
	पूर्ण

	link = सुस्मृति(1, माप(*link));
	अगर (!link) अणु
		बंद(fd);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	link->detach = &bpf_link__detach_fd;
	link->fd = fd;

	link->pin_path = strdup(path);
	अगर (!link->pin_path) अणु
		bpf_link__destroy(link);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	वापस link;
पूर्ण

पूर्णांक bpf_link__detach(काष्ठा bpf_link *link)
अणु
	वापस bpf_link_detach(link->fd) ? -त्रुटि_सं : 0;
पूर्ण

पूर्णांक bpf_link__pin(काष्ठा bpf_link *link, स्थिर अक्षर *path)
अणु
	पूर्णांक err;

	अगर (link->pin_path)
		वापस -EBUSY;
	err = make_parent_dir(path);
	अगर (err)
		वापस err;
	err = check_path(path);
	अगर (err)
		वापस err;

	link->pin_path = strdup(path);
	अगर (!link->pin_path)
		वापस -ENOMEM;

	अगर (bpf_obj_pin(link->fd, link->pin_path)) अणु
		err = -त्रुटि_सं;
		zमुक्त(&link->pin_path);
		वापस err;
	पूर्ण

	pr_debug("link fd=%d: pinned at %s\n", link->fd, link->pin_path);
	वापस 0;
पूर्ण

पूर्णांक bpf_link__unpin(काष्ठा bpf_link *link)
अणु
	पूर्णांक err;

	अगर (!link->pin_path)
		वापस -EINVAL;

	err = unlink(link->pin_path);
	अगर (err != 0)
		वापस -त्रुटि_सं;

	pr_debug("link fd=%d: unpinned from %s\n", link->fd, link->pin_path);
	zमुक्त(&link->pin_path);
	वापस 0;
पूर्ण

अटल पूर्णांक bpf_link__detach_perf_event(काष्ठा bpf_link *link)
अणु
	पूर्णांक err;

	err = ioctl(link->fd, PERF_EVENT_IOC_DISABLE, 0);
	अगर (err)
		err = -त्रुटि_सं;

	बंद(link->fd);
	वापस err;
पूर्ण

काष्ठा bpf_link *bpf_program__attach_perf_event(काष्ठा bpf_program *prog,
						पूर्णांक pfd)
अणु
	अक्षर errmsg[STRERR_बफ_मानE];
	काष्ठा bpf_link *link;
	पूर्णांक prog_fd, err;

	अगर (pfd < 0) अणु
		pr_warn("prog '%s': invalid perf event FD %d\n",
			prog->name, pfd);
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	prog_fd = bpf_program__fd(prog);
	अगर (prog_fd < 0) अणु
		pr_warn("prog '%s': can't attach BPF program w/o FD (did you load it?)\n",
			prog->name);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	link = सुस्मृति(1, माप(*link));
	अगर (!link)
		वापस ERR_PTR(-ENOMEM);
	link->detach = &bpf_link__detach_perf_event;
	link->fd = pfd;

	अगर (ioctl(pfd, PERF_EVENT_IOC_SET_BPF, prog_fd) < 0) अणु
		err = -त्रुटि_सं;
		मुक्त(link);
		pr_warn("prog '%s': failed to attach to pfd %d: %s\n",
			prog->name, pfd, libbpf_म_त्रुटि_r(err, errmsg, माप(errmsg)));
		अगर (err == -EPROTO)
			pr_warn("prog '%s': try add PERF_SAMPLE_CALLCHAIN to or remove exclude_callchain_[kernel|user] from pfd %d\n",
				prog->name, pfd);
		वापस ERR_PTR(err);
	पूर्ण
	अगर (ioctl(pfd, PERF_EVENT_IOC_ENABLE, 0) < 0) अणु
		err = -त्रुटि_सं;
		मुक्त(link);
		pr_warn("prog '%s': failed to enable pfd %d: %s\n",
			prog->name, pfd, libbpf_म_त्रुटि_r(err, errmsg, माप(errmsg)));
		वापस ERR_PTR(err);
	पूर्ण
	वापस link;
पूर्ण

/*
 * this function is expected to parse पूर्णांकeger in the range of [0, 2^31-1] from
 * given file using म_पूछो क्रमmat string fmt. If actual parsed value is
 * negative, the result might be indistinguishable from error
 */
अटल पूर्णांक parse_uपूर्णांक_from_file(स्थिर अक्षर *file, स्थिर अक्षर *fmt)
अणु
	अक्षर buf[STRERR_बफ_मानE];
	पूर्णांक err, ret;
	खाता *f;

	f = ख_खोलो(file, "r");
	अगर (!f) अणु
		err = -त्रुटि_सं;
		pr_debug("failed to open '%s': %s\n", file,
			 libbpf_म_त्रुटि_r(err, buf, माप(buf)));
		वापस err;
	पूर्ण
	err = ख_पूछो(f, fmt, &ret);
	अगर (err != 1) अणु
		err = err == खातापूर्ण ? -EIO : -त्रुटि_सं;
		pr_debug("failed to parse '%s': %s\n", file,
			libbpf_म_त्रुटि_r(err, buf, माप(buf)));
		ख_बंद(f);
		वापस err;
	पूर्ण
	ख_बंद(f);
	वापस ret;
पूर्ण

अटल पूर्णांक determine_kprobe_perf_type(व्योम)
अणु
	स्थिर अक्षर *file = "/sys/bus/event_source/devices/kprobe/type";

	वापस parse_uपूर्णांक_from_file(file, "%d\n");
पूर्ण

अटल पूर्णांक determine_uprobe_perf_type(व्योम)
अणु
	स्थिर अक्षर *file = "/sys/bus/event_source/devices/uprobe/type";

	वापस parse_uपूर्णांक_from_file(file, "%d\n");
पूर्ण

अटल पूर्णांक determine_kprobe_retprobe_bit(व्योम)
अणु
	स्थिर अक्षर *file = "/sys/bus/event_source/devices/kprobe/format/retprobe";

	वापस parse_uपूर्णांक_from_file(file, "config:%d\n");
पूर्ण

अटल पूर्णांक determine_uprobe_retprobe_bit(व्योम)
अणु
	स्थिर अक्षर *file = "/sys/bus/event_source/devices/uprobe/format/retprobe";

	वापस parse_uपूर्णांक_from_file(file, "config:%d\n");
पूर्ण

अटल पूर्णांक perf_event_खोलो_probe(bool uprobe, bool retprobe, स्थिर अक्षर *name,
				 uपूर्णांक64_t offset, पूर्णांक pid)
अणु
	काष्ठा perf_event_attr attr = अणुपूर्ण;
	अक्षर errmsg[STRERR_बफ_मानE];
	पूर्णांक type, pfd, err;

	type = uprobe ? determine_uprobe_perf_type()
		      : determine_kprobe_perf_type();
	अगर (type < 0) अणु
		pr_warn("failed to determine %s perf type: %s\n",
			uprobe ? "uprobe" : "kprobe",
			libbpf_म_त्रुटि_r(type, errmsg, माप(errmsg)));
		वापस type;
	पूर्ण
	अगर (retprobe) अणु
		पूर्णांक bit = uprobe ? determine_uprobe_retprobe_bit()
				 : determine_kprobe_retprobe_bit();

		अगर (bit < 0) अणु
			pr_warn("failed to determine %s retprobe bit: %s\n",
				uprobe ? "uprobe" : "kprobe",
				libbpf_म_त्रुटि_r(bit, errmsg, माप(errmsg)));
			वापस bit;
		पूर्ण
		attr.config |= 1 << bit;
	पूर्ण
	attr.size = माप(attr);
	attr.type = type;
	attr.config1 = ptr_to_u64(name); /* kprobe_func or uprobe_path */
	attr.config2 = offset;		 /* kprobe_addr or probe_offset */

	/* pid filter is meaningful only क्रम uprobes */
	pfd = syscall(__NR_perf_event_खोलो, &attr,
		      pid < 0 ? -1 : pid /* pid */,
		      pid == -1 ? 0 : -1 /* cpu */,
		      -1 /* group_fd */, PERF_FLAG_FD_CLOEXEC);
	अगर (pfd < 0) अणु
		err = -त्रुटि_सं;
		pr_warn("%s perf_event_open() failed: %s\n",
			uprobe ? "uprobe" : "kprobe",
			libbpf_म_त्रुटि_r(err, errmsg, माप(errmsg)));
		वापस err;
	पूर्ण
	वापस pfd;
पूर्ण

काष्ठा bpf_link *bpf_program__attach_kprobe(काष्ठा bpf_program *prog,
					    bool retprobe,
					    स्थिर अक्षर *func_name)
अणु
	अक्षर errmsg[STRERR_बफ_मानE];
	काष्ठा bpf_link *link;
	पूर्णांक pfd, err;

	pfd = perf_event_खोलो_probe(false /* uprobe */, retprobe, func_name,
				    0 /* offset */, -1 /* pid */);
	अगर (pfd < 0) अणु
		pr_warn("prog '%s': failed to create %s '%s' perf event: %s\n",
			prog->name, retprobe ? "kretprobe" : "kprobe", func_name,
			libbpf_म_त्रुटि_r(pfd, errmsg, माप(errmsg)));
		वापस ERR_PTR(pfd);
	पूर्ण
	link = bpf_program__attach_perf_event(prog, pfd);
	अगर (IS_ERR(link)) अणु
		बंद(pfd);
		err = PTR_ERR(link);
		pr_warn("prog '%s': failed to attach to %s '%s': %s\n",
			prog->name, retprobe ? "kretprobe" : "kprobe", func_name,
			libbpf_म_त्रुटि_r(err, errmsg, माप(errmsg)));
		वापस link;
	पूर्ण
	वापस link;
पूर्ण

अटल काष्ठा bpf_link *attach_kprobe(स्थिर काष्ठा bpf_sec_def *sec,
				      काष्ठा bpf_program *prog)
अणु
	स्थिर अक्षर *func_name;
	bool retprobe;

	func_name = prog->sec_name + sec->len;
	retprobe = म_भेद(sec->sec, "kretprobe/") == 0;

	वापस bpf_program__attach_kprobe(prog, retprobe, func_name);
पूर्ण

काष्ठा bpf_link *bpf_program__attach_uprobe(काष्ठा bpf_program *prog,
					    bool retprobe, pid_t pid,
					    स्थिर अक्षर *binary_path,
					    माप_प्रकार func_offset)
अणु
	अक्षर errmsg[STRERR_बफ_मानE];
	काष्ठा bpf_link *link;
	पूर्णांक pfd, err;

	pfd = perf_event_खोलो_probe(true /* uprobe */, retprobe,
				    binary_path, func_offset, pid);
	अगर (pfd < 0) अणु
		pr_warn("prog '%s': failed to create %s '%s:0x%zx' perf event: %s\n",
			prog->name, retprobe ? "uretprobe" : "uprobe",
			binary_path, func_offset,
			libbpf_म_त्रुटि_r(pfd, errmsg, माप(errmsg)));
		वापस ERR_PTR(pfd);
	पूर्ण
	link = bpf_program__attach_perf_event(prog, pfd);
	अगर (IS_ERR(link)) अणु
		बंद(pfd);
		err = PTR_ERR(link);
		pr_warn("prog '%s': failed to attach to %s '%s:0x%zx': %s\n",
			prog->name, retprobe ? "uretprobe" : "uprobe",
			binary_path, func_offset,
			libbpf_म_त्रुटि_r(err, errmsg, माप(errmsg)));
		वापस link;
	पूर्ण
	वापस link;
पूर्ण

अटल पूर्णांक determine_tracepoपूर्णांक_id(स्थिर अक्षर *tp_category,
				   स्थिर अक्षर *tp_name)
अणु
	अक्षर file[PATH_MAX];
	पूर्णांक ret;

	ret = snम_लिखो(file, माप(file),
		       "/sys/kernel/debug/tracing/events/%s/%s/id",
		       tp_category, tp_name);
	अगर (ret < 0)
		वापस -त्रुटि_सं;
	अगर (ret >= माप(file)) अणु
		pr_debug("tracepoint %s/%s path is too long\n",
			 tp_category, tp_name);
		वापस -E2BIG;
	पूर्ण
	वापस parse_uपूर्णांक_from_file(file, "%d\n");
पूर्ण

अटल पूर्णांक perf_event_खोलो_tracepoपूर्णांक(स्थिर अक्षर *tp_category,
				      स्थिर अक्षर *tp_name)
अणु
	काष्ठा perf_event_attr attr = अणुपूर्ण;
	अक्षर errmsg[STRERR_बफ_मानE];
	पूर्णांक tp_id, pfd, err;

	tp_id = determine_tracepoपूर्णांक_id(tp_category, tp_name);
	अगर (tp_id < 0) अणु
		pr_warn("failed to determine tracepoint '%s/%s' perf event ID: %s\n",
			tp_category, tp_name,
			libbpf_म_त्रुटि_r(tp_id, errmsg, माप(errmsg)));
		वापस tp_id;
	पूर्ण

	attr.type = PERF_TYPE_TRACEPOINT;
	attr.size = माप(attr);
	attr.config = tp_id;

	pfd = syscall(__NR_perf_event_खोलो, &attr, -1 /* pid */, 0 /* cpu */,
		      -1 /* group_fd */, PERF_FLAG_FD_CLOEXEC);
	अगर (pfd < 0) अणु
		err = -त्रुटि_सं;
		pr_warn("tracepoint '%s/%s' perf_event_open() failed: %s\n",
			tp_category, tp_name,
			libbpf_म_त्रुटि_r(err, errmsg, माप(errmsg)));
		वापस err;
	पूर्ण
	वापस pfd;
पूर्ण

काष्ठा bpf_link *bpf_program__attach_tracepoपूर्णांक(काष्ठा bpf_program *prog,
						स्थिर अक्षर *tp_category,
						स्थिर अक्षर *tp_name)
अणु
	अक्षर errmsg[STRERR_बफ_मानE];
	काष्ठा bpf_link *link;
	पूर्णांक pfd, err;

	pfd = perf_event_खोलो_tracepoपूर्णांक(tp_category, tp_name);
	अगर (pfd < 0) अणु
		pr_warn("prog '%s': failed to create tracepoint '%s/%s' perf event: %s\n",
			prog->name, tp_category, tp_name,
			libbpf_म_त्रुटि_r(pfd, errmsg, माप(errmsg)));
		वापस ERR_PTR(pfd);
	पूर्ण
	link = bpf_program__attach_perf_event(prog, pfd);
	अगर (IS_ERR(link)) अणु
		बंद(pfd);
		err = PTR_ERR(link);
		pr_warn("prog '%s': failed to attach to tracepoint '%s/%s': %s\n",
			prog->name, tp_category, tp_name,
			libbpf_म_त्रुटि_r(err, errmsg, माप(errmsg)));
		वापस link;
	पूर्ण
	वापस link;
पूर्ण

अटल काष्ठा bpf_link *attach_tp(स्थिर काष्ठा bpf_sec_def *sec,
				  काष्ठा bpf_program *prog)
अणु
	अक्षर *sec_name, *tp_cat, *tp_name;
	काष्ठा bpf_link *link;

	sec_name = strdup(prog->sec_name);
	अगर (!sec_name)
		वापस ERR_PTR(-ENOMEM);

	/* extract "tp/<category>/<name>" */
	tp_cat = sec_name + sec->len;
	tp_name = म_अक्षर(tp_cat, '/');
	अगर (!tp_name) अणु
		link = ERR_PTR(-EINVAL);
		जाओ out;
	पूर्ण
	*tp_name = '\0';
	tp_name++;

	link = bpf_program__attach_tracepoपूर्णांक(prog, tp_cat, tp_name);
out:
	मुक्त(sec_name);
	वापस link;
पूर्ण

काष्ठा bpf_link *bpf_program__attach_raw_tracepoपूर्णांक(काष्ठा bpf_program *prog,
						    स्थिर अक्षर *tp_name)
अणु
	अक्षर errmsg[STRERR_बफ_मानE];
	काष्ठा bpf_link *link;
	पूर्णांक prog_fd, pfd;

	prog_fd = bpf_program__fd(prog);
	अगर (prog_fd < 0) अणु
		pr_warn("prog '%s': can't attach before loaded\n", prog->name);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	link = सुस्मृति(1, माप(*link));
	अगर (!link)
		वापस ERR_PTR(-ENOMEM);
	link->detach = &bpf_link__detach_fd;

	pfd = bpf_raw_tracepoपूर्णांक_खोलो(tp_name, prog_fd);
	अगर (pfd < 0) अणु
		pfd = -त्रुटि_सं;
		मुक्त(link);
		pr_warn("prog '%s': failed to attach to raw tracepoint '%s': %s\n",
			prog->name, tp_name, libbpf_म_त्रुटि_r(pfd, errmsg, माप(errmsg)));
		वापस ERR_PTR(pfd);
	पूर्ण
	link->fd = pfd;
	वापस link;
पूर्ण

अटल काष्ठा bpf_link *attach_raw_tp(स्थिर काष्ठा bpf_sec_def *sec,
				      काष्ठा bpf_program *prog)
अणु
	स्थिर अक्षर *tp_name = prog->sec_name + sec->len;

	वापस bpf_program__attach_raw_tracepoपूर्णांक(prog, tp_name);
पूर्ण

/* Common logic क्रम all BPF program types that attach to a btf_id */
अटल काष्ठा bpf_link *bpf_program__attach_btf_id(काष्ठा bpf_program *prog)
अणु
	अक्षर errmsg[STRERR_बफ_मानE];
	काष्ठा bpf_link *link;
	पूर्णांक prog_fd, pfd;

	prog_fd = bpf_program__fd(prog);
	अगर (prog_fd < 0) अणु
		pr_warn("prog '%s': can't attach before loaded\n", prog->name);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	link = सुस्मृति(1, माप(*link));
	अगर (!link)
		वापस ERR_PTR(-ENOMEM);
	link->detach = &bpf_link__detach_fd;

	pfd = bpf_raw_tracepoपूर्णांक_खोलो(शून्य, prog_fd);
	अगर (pfd < 0) अणु
		pfd = -त्रुटि_सं;
		मुक्त(link);
		pr_warn("prog '%s': failed to attach: %s\n",
			prog->name, libbpf_म_त्रुटि_r(pfd, errmsg, माप(errmsg)));
		वापस ERR_PTR(pfd);
	पूर्ण
	link->fd = pfd;
	वापस (काष्ठा bpf_link *)link;
पूर्ण

काष्ठा bpf_link *bpf_program__attach_trace(काष्ठा bpf_program *prog)
अणु
	वापस bpf_program__attach_btf_id(prog);
पूर्ण

काष्ठा bpf_link *bpf_program__attach_lsm(काष्ठा bpf_program *prog)
अणु
	वापस bpf_program__attach_btf_id(prog);
पूर्ण

अटल काष्ठा bpf_link *attach_trace(स्थिर काष्ठा bpf_sec_def *sec,
				     काष्ठा bpf_program *prog)
अणु
	वापस bpf_program__attach_trace(prog);
पूर्ण

अटल काष्ठा bpf_link *attach_lsm(स्थिर काष्ठा bpf_sec_def *sec,
				   काष्ठा bpf_program *prog)
अणु
	वापस bpf_program__attach_lsm(prog);
पूर्ण

अटल काष्ठा bpf_link *attach_iter(स्थिर काष्ठा bpf_sec_def *sec,
				    काष्ठा bpf_program *prog)
अणु
	वापस bpf_program__attach_iter(prog, शून्य);
पूर्ण

अटल काष्ठा bpf_link *
bpf_program__attach_fd(काष्ठा bpf_program *prog, पूर्णांक target_fd, पूर्णांक btf_id,
		       स्थिर अक्षर *target_name)
अणु
	DECLARE_LIBBPF_OPTS(bpf_link_create_opts, opts,
			    .target_btf_id = btf_id);
	क्रमागत bpf_attach_type attach_type;
	अक्षर errmsg[STRERR_बफ_मानE];
	काष्ठा bpf_link *link;
	पूर्णांक prog_fd, link_fd;

	prog_fd = bpf_program__fd(prog);
	अगर (prog_fd < 0) अणु
		pr_warn("prog '%s': can't attach before loaded\n", prog->name);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	link = सुस्मृति(1, माप(*link));
	अगर (!link)
		वापस ERR_PTR(-ENOMEM);
	link->detach = &bpf_link__detach_fd;

	attach_type = bpf_program__get_expected_attach_type(prog);
	link_fd = bpf_link_create(prog_fd, target_fd, attach_type, &opts);
	अगर (link_fd < 0) अणु
		link_fd = -त्रुटि_सं;
		मुक्त(link);
		pr_warn("prog '%s': failed to attach to %s: %s\n",
			prog->name, target_name,
			libbpf_म_त्रुटि_r(link_fd, errmsg, माप(errmsg)));
		वापस ERR_PTR(link_fd);
	पूर्ण
	link->fd = link_fd;
	वापस link;
पूर्ण

काष्ठा bpf_link *
bpf_program__attach_cgroup(काष्ठा bpf_program *prog, पूर्णांक cgroup_fd)
अणु
	वापस bpf_program__attach_fd(prog, cgroup_fd, 0, "cgroup");
पूर्ण

काष्ठा bpf_link *
bpf_program__attach_netns(काष्ठा bpf_program *prog, पूर्णांक netns_fd)
अणु
	वापस bpf_program__attach_fd(prog, netns_fd, 0, "netns");
पूर्ण

काष्ठा bpf_link *bpf_program__attach_xdp(काष्ठा bpf_program *prog, पूर्णांक अगरindex)
अणु
	/* target_fd/target_अगरindex use the same field in LINK_CREATE */
	वापस bpf_program__attach_fd(prog, अगरindex, 0, "xdp");
पूर्ण

काष्ठा bpf_link *bpf_program__attach_freplace(काष्ठा bpf_program *prog,
					      पूर्णांक target_fd,
					      स्थिर अक्षर *attach_func_name)
अणु
	पूर्णांक btf_id;

	अगर (!!target_fd != !!attach_func_name) अणु
		pr_warn("prog '%s': supply none or both of target_fd and attach_func_name\n",
			prog->name);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (prog->type != BPF_PROG_TYPE_EXT) अणु
		pr_warn("prog '%s': only BPF_PROG_TYPE_EXT can attach as freplace",
			prog->name);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (target_fd) अणु
		btf_id = libbpf_find_prog_btf_id(attach_func_name, target_fd);
		अगर (btf_id < 0)
			वापस ERR_PTR(btf_id);

		वापस bpf_program__attach_fd(prog, target_fd, btf_id, "freplace");
	पूर्ण अन्यथा अणु
		/* no target, so use raw_tracepoपूर्णांक_खोलो क्रम compatibility
		 * with old kernels
		 */
		वापस bpf_program__attach_trace(prog);
	पूर्ण
पूर्ण

काष्ठा bpf_link *
bpf_program__attach_iter(काष्ठा bpf_program *prog,
			 स्थिर काष्ठा bpf_iter_attach_opts *opts)
अणु
	DECLARE_LIBBPF_OPTS(bpf_link_create_opts, link_create_opts);
	अक्षर errmsg[STRERR_बफ_मानE];
	काष्ठा bpf_link *link;
	पूर्णांक prog_fd, link_fd;
	__u32 target_fd = 0;

	अगर (!OPTS_VALID(opts, bpf_iter_attach_opts))
		वापस ERR_PTR(-EINVAL);

	link_create_opts.iter_info = OPTS_GET(opts, link_info, (व्योम *)0);
	link_create_opts.iter_info_len = OPTS_GET(opts, link_info_len, 0);

	prog_fd = bpf_program__fd(prog);
	अगर (prog_fd < 0) अणु
		pr_warn("prog '%s': can't attach before loaded\n", prog->name);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	link = सुस्मृति(1, माप(*link));
	अगर (!link)
		वापस ERR_PTR(-ENOMEM);
	link->detach = &bpf_link__detach_fd;

	link_fd = bpf_link_create(prog_fd, target_fd, BPF_TRACE_ITER,
				  &link_create_opts);
	अगर (link_fd < 0) अणु
		link_fd = -त्रुटि_सं;
		मुक्त(link);
		pr_warn("prog '%s': failed to attach to iterator: %s\n",
			prog->name, libbpf_म_त्रुटि_r(link_fd, errmsg, माप(errmsg)));
		वापस ERR_PTR(link_fd);
	पूर्ण
	link->fd = link_fd;
	वापस link;
पूर्ण

काष्ठा bpf_link *bpf_program__attach(काष्ठा bpf_program *prog)
अणु
	स्थिर काष्ठा bpf_sec_def *sec_def;

	sec_def = find_sec_def(prog->sec_name);
	अगर (!sec_def || !sec_def->attach_fn)
		वापस ERR_PTR(-ESRCH);

	वापस sec_def->attach_fn(sec_def, prog);
पूर्ण

अटल पूर्णांक bpf_link__detach_काष्ठा_ops(काष्ठा bpf_link *link)
अणु
	__u32 zero = 0;

	अगर (bpf_map_delete_elem(link->fd, &zero))
		वापस -त्रुटि_सं;

	वापस 0;
पूर्ण

काष्ठा bpf_link *bpf_map__attach_काष्ठा_ops(काष्ठा bpf_map *map)
अणु
	काष्ठा bpf_काष्ठा_ops *st_ops;
	काष्ठा bpf_link *link;
	__u32 i, zero = 0;
	पूर्णांक err;

	अगर (!bpf_map__is_काष्ठा_ops(map) || map->fd == -1)
		वापस ERR_PTR(-EINVAL);

	link = सुस्मृति(1, माप(*link));
	अगर (!link)
		वापस ERR_PTR(-EINVAL);

	st_ops = map->st_ops;
	क्रम (i = 0; i < btf_vlen(st_ops->type); i++) अणु
		काष्ठा bpf_program *prog = st_ops->progs[i];
		व्योम *kern_data;
		पूर्णांक prog_fd;

		अगर (!prog)
			जारी;

		prog_fd = bpf_program__fd(prog);
		kern_data = st_ops->kern_vdata + st_ops->kern_func_off[i];
		*(अचिन्हित दीर्घ *)kern_data = prog_fd;
	पूर्ण

	err = bpf_map_update_elem(map->fd, &zero, st_ops->kern_vdata, 0);
	अगर (err) अणु
		err = -त्रुटि_सं;
		मुक्त(link);
		वापस ERR_PTR(err);
	पूर्ण

	link->detach = bpf_link__detach_काष्ठा_ops;
	link->fd = map->fd;

	वापस link;
पूर्ण

क्रमागत bpf_perf_event_ret
bpf_perf_event_पढ़ो_simple(व्योम *mmap_mem, माप_प्रकार mmap_size, माप_प्रकार page_size,
			   व्योम **copy_mem, माप_प्रकार *copy_size,
			   bpf_perf_event_prपूर्णांक_t fn, व्योम *निजी_data)
अणु
	काष्ठा perf_event_mmap_page *header = mmap_mem;
	__u64 data_head = ring_buffer_पढ़ो_head(header);
	__u64 data_tail = header->data_tail;
	व्योम *base = ((__u8 *)header) + page_size;
	पूर्णांक ret = LIBBPF_PERF_EVENT_CONT;
	काष्ठा perf_event_header *ehdr;
	माप_प्रकार ehdr_size;

	जबतक (data_head != data_tail) अणु
		ehdr = base + (data_tail & (mmap_size - 1));
		ehdr_size = ehdr->size;

		अगर (((व्योम *)ehdr) + ehdr_size > base + mmap_size) अणु
			व्योम *copy_start = ehdr;
			माप_प्रकार len_first = base + mmap_size - copy_start;
			माप_प्रकार len_secnd = ehdr_size - len_first;

			अगर (*copy_size < ehdr_size) अणु
				मुक्त(*copy_mem);
				*copy_mem = दो_स्मृति(ehdr_size);
				अगर (!*copy_mem) अणु
					*copy_size = 0;
					ret = LIBBPF_PERF_EVENT_ERROR;
					अवरोध;
				पूर्ण
				*copy_size = ehdr_size;
			पूर्ण

			स_नकल(*copy_mem, copy_start, len_first);
			स_नकल(*copy_mem + len_first, base, len_secnd);
			ehdr = *copy_mem;
		पूर्ण

		ret = fn(ehdr, निजी_data);
		data_tail += ehdr_size;
		अगर (ret != LIBBPF_PERF_EVENT_CONT)
			अवरोध;
	पूर्ण

	ring_buffer_ग_लिखो_tail(header, data_tail);
	वापस ret;
पूर्ण

काष्ठा perf_buffer;

काष्ठा perf_buffer_params अणु
	काष्ठा perf_event_attr *attr;
	/* अगर event_cb is specअगरied, it takes precendence */
	perf_buffer_event_fn event_cb;
	/* sample_cb and lost_cb are higher-level common-हाल callbacks */
	perf_buffer_sample_fn sample_cb;
	perf_buffer_lost_fn lost_cb;
	व्योम *ctx;
	पूर्णांक cpu_cnt;
	पूर्णांक *cpus;
	पूर्णांक *map_keys;
पूर्ण;

काष्ठा perf_cpu_buf अणु
	काष्ठा perf_buffer *pb;
	व्योम *base; /* mmap()'ed memory */
	व्योम *buf; /* क्रम reस्थिरructing segmented data */
	माप_प्रकार buf_size;
	पूर्णांक fd;
	पूर्णांक cpu;
	पूर्णांक map_key;
पूर्ण;

काष्ठा perf_buffer अणु
	perf_buffer_event_fn event_cb;
	perf_buffer_sample_fn sample_cb;
	perf_buffer_lost_fn lost_cb;
	व्योम *ctx; /* passed पूर्णांकo callbacks */

	माप_प्रकार page_size;
	माप_प्रकार mmap_size;
	काष्ठा perf_cpu_buf **cpu_bufs;
	काष्ठा epoll_event *events;
	पूर्णांक cpu_cnt; /* number of allocated CPU buffers */
	पूर्णांक epoll_fd; /* perf event FD */
	पूर्णांक map_fd; /* BPF_MAP_TYPE_PERF_EVENT_ARRAY BPF map FD */
पूर्ण;

अटल व्योम perf_buffer__मुक्त_cpu_buf(काष्ठा perf_buffer *pb,
				      काष्ठा perf_cpu_buf *cpu_buf)
अणु
	अगर (!cpu_buf)
		वापस;
	अगर (cpu_buf->base &&
	    munmap(cpu_buf->base, pb->mmap_size + pb->page_size))
		pr_warn("failed to munmap cpu_buf #%d\n", cpu_buf->cpu);
	अगर (cpu_buf->fd >= 0) अणु
		ioctl(cpu_buf->fd, PERF_EVENT_IOC_DISABLE, 0);
		बंद(cpu_buf->fd);
	पूर्ण
	मुक्त(cpu_buf->buf);
	मुक्त(cpu_buf);
पूर्ण

व्योम perf_buffer__मुक्त(काष्ठा perf_buffer *pb)
अणु
	पूर्णांक i;

	अगर (IS_ERR_OR_शून्य(pb))
		वापस;
	अगर (pb->cpu_bufs) अणु
		क्रम (i = 0; i < pb->cpu_cnt; i++) अणु
			काष्ठा perf_cpu_buf *cpu_buf = pb->cpu_bufs[i];

			अगर (!cpu_buf)
				जारी;

			bpf_map_delete_elem(pb->map_fd, &cpu_buf->map_key);
			perf_buffer__मुक्त_cpu_buf(pb, cpu_buf);
		पूर्ण
		मुक्त(pb->cpu_bufs);
	पूर्ण
	अगर (pb->epoll_fd >= 0)
		बंद(pb->epoll_fd);
	मुक्त(pb->events);
	मुक्त(pb);
पूर्ण

अटल काष्ठा perf_cpu_buf *
perf_buffer__खोलो_cpu_buf(काष्ठा perf_buffer *pb, काष्ठा perf_event_attr *attr,
			  पूर्णांक cpu, पूर्णांक map_key)
अणु
	काष्ठा perf_cpu_buf *cpu_buf;
	अक्षर msg[STRERR_बफ_मानE];
	पूर्णांक err;

	cpu_buf = सुस्मृति(1, माप(*cpu_buf));
	अगर (!cpu_buf)
		वापस ERR_PTR(-ENOMEM);

	cpu_buf->pb = pb;
	cpu_buf->cpu = cpu;
	cpu_buf->map_key = map_key;

	cpu_buf->fd = syscall(__NR_perf_event_खोलो, attr, -1 /* pid */, cpu,
			      -1, PERF_FLAG_FD_CLOEXEC);
	अगर (cpu_buf->fd < 0) अणु
		err = -त्रुटि_सं;
		pr_warn("failed to open perf buffer event on cpu #%d: %s\n",
			cpu, libbpf_म_त्रुटि_r(err, msg, माप(msg)));
		जाओ error;
	पूर्ण

	cpu_buf->base = mmap(शून्य, pb->mmap_size + pb->page_size,
			     PROT_READ | PROT_WRITE, MAP_SHARED,
			     cpu_buf->fd, 0);
	अगर (cpu_buf->base == MAP_FAILED) अणु
		cpu_buf->base = शून्य;
		err = -त्रुटि_सं;
		pr_warn("failed to mmap perf buffer on cpu #%d: %s\n",
			cpu, libbpf_म_त्रुटि_r(err, msg, माप(msg)));
		जाओ error;
	पूर्ण

	अगर (ioctl(cpu_buf->fd, PERF_EVENT_IOC_ENABLE, 0) < 0) अणु
		err = -त्रुटि_सं;
		pr_warn("failed to enable perf buffer event on cpu #%d: %s\n",
			cpu, libbpf_म_त्रुटि_r(err, msg, माप(msg)));
		जाओ error;
	पूर्ण

	वापस cpu_buf;

error:
	perf_buffer__मुक्त_cpu_buf(pb, cpu_buf);
	वापस (काष्ठा perf_cpu_buf *)ERR_PTR(err);
पूर्ण

अटल काष्ठा perf_buffer *__perf_buffer__new(पूर्णांक map_fd, माप_प्रकार page_cnt,
					      काष्ठा perf_buffer_params *p);

काष्ठा perf_buffer *perf_buffer__new(पूर्णांक map_fd, माप_प्रकार page_cnt,
				     स्थिर काष्ठा perf_buffer_opts *opts)
अणु
	काष्ठा perf_buffer_params p = अणुपूर्ण;
	काष्ठा perf_event_attr attr = अणु 0, पूर्ण;

	attr.config = PERF_COUNT_SW_BPF_OUTPUT;
	attr.type = PERF_TYPE_SOFTWARE;
	attr.sample_type = PERF_SAMPLE_RAW;
	attr.sample_period = 1;
	attr.wakeup_events = 1;

	p.attr = &attr;
	p.sample_cb = opts ? opts->sample_cb : शून्य;
	p.lost_cb = opts ? opts->lost_cb : शून्य;
	p.ctx = opts ? opts->ctx : शून्य;

	वापस __perf_buffer__new(map_fd, page_cnt, &p);
पूर्ण

काष्ठा perf_buffer *
perf_buffer__new_raw(पूर्णांक map_fd, माप_प्रकार page_cnt,
		     स्थिर काष्ठा perf_buffer_raw_opts *opts)
अणु
	काष्ठा perf_buffer_params p = अणुपूर्ण;

	p.attr = opts->attr;
	p.event_cb = opts->event_cb;
	p.ctx = opts->ctx;
	p.cpu_cnt = opts->cpu_cnt;
	p.cpus = opts->cpus;
	p.map_keys = opts->map_keys;

	वापस __perf_buffer__new(map_fd, page_cnt, &p);
पूर्ण

अटल काष्ठा perf_buffer *__perf_buffer__new(पूर्णांक map_fd, माप_प्रकार page_cnt,
					      काष्ठा perf_buffer_params *p)
अणु
	स्थिर अक्षर *online_cpus_file = "/sys/devices/system/cpu/online";
	काष्ठा bpf_map_info map;
	अक्षर msg[STRERR_बफ_मानE];
	काष्ठा perf_buffer *pb;
	bool *online = शून्य;
	__u32 map_info_len;
	पूर्णांक err, i, j, n;

	अगर (page_cnt & (page_cnt - 1)) अणु
		pr_warn("page count should be power of two, but is %zu\n",
			page_cnt);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	/* best-efक्रमt sanity checks */
	स_रखो(&map, 0, माप(map));
	map_info_len = माप(map);
	err = bpf_obj_get_info_by_fd(map_fd, &map, &map_info_len);
	अगर (err) अणु
		err = -त्रुटि_सं;
		/* अगर BPF_OBJ_GET_INFO_BY_FD is supported, will वापस
		 * -EBADFD, -EFAULT, or -E2BIG on real error
		 */
		अगर (err != -EINVAL) अणु
			pr_warn("failed to get map info for map FD %d: %s\n",
				map_fd, libbpf_म_त्रुटि_r(err, msg, माप(msg)));
			वापस ERR_PTR(err);
		पूर्ण
		pr_debug("failed to get map info for FD %d; API not supported? Ignoring...\n",
			 map_fd);
	पूर्ण अन्यथा अणु
		अगर (map.type != BPF_MAP_TYPE_PERF_EVENT_ARRAY) अणु
			pr_warn("map '%s' should be BPF_MAP_TYPE_PERF_EVENT_ARRAY\n",
				map.name);
			वापस ERR_PTR(-EINVAL);
		पूर्ण
	पूर्ण

	pb = सुस्मृति(1, माप(*pb));
	अगर (!pb)
		वापस ERR_PTR(-ENOMEM);

	pb->event_cb = p->event_cb;
	pb->sample_cb = p->sample_cb;
	pb->lost_cb = p->lost_cb;
	pb->ctx = p->ctx;

	pb->page_size = getpagesize();
	pb->mmap_size = pb->page_size * page_cnt;
	pb->map_fd = map_fd;

	pb->epoll_fd = epoll_create1(EPOLL_CLOEXEC);
	अगर (pb->epoll_fd < 0) अणु
		err = -त्रुटि_सं;
		pr_warn("failed to create epoll instance: %s\n",
			libbpf_म_त्रुटि_r(err, msg, माप(msg)));
		जाओ error;
	पूर्ण

	अगर (p->cpu_cnt > 0) अणु
		pb->cpu_cnt = p->cpu_cnt;
	पूर्ण अन्यथा अणु
		pb->cpu_cnt = libbpf_num_possible_cpus();
		अगर (pb->cpu_cnt < 0) अणु
			err = pb->cpu_cnt;
			जाओ error;
		पूर्ण
		अगर (map.max_entries && map.max_entries < pb->cpu_cnt)
			pb->cpu_cnt = map.max_entries;
	पूर्ण

	pb->events = सुस्मृति(pb->cpu_cnt, माप(*pb->events));
	अगर (!pb->events) अणु
		err = -ENOMEM;
		pr_warn("failed to allocate events: out of memory\n");
		जाओ error;
	पूर्ण
	pb->cpu_bufs = सुस्मृति(pb->cpu_cnt, माप(*pb->cpu_bufs));
	अगर (!pb->cpu_bufs) अणु
		err = -ENOMEM;
		pr_warn("failed to allocate buffers: out of memory\n");
		जाओ error;
	पूर्ण

	err = parse_cpu_mask_file(online_cpus_file, &online, &n);
	अगर (err) अणु
		pr_warn("failed to get online CPU mask: %d\n", err);
		जाओ error;
	पूर्ण

	क्रम (i = 0, j = 0; i < pb->cpu_cnt; i++) अणु
		काष्ठा perf_cpu_buf *cpu_buf;
		पूर्णांक cpu, map_key;

		cpu = p->cpu_cnt > 0 ? p->cpus[i] : i;
		map_key = p->cpu_cnt > 0 ? p->map_keys[i] : i;

		/* in हाल user didn't explicitly requested particular CPUs to
		 * be attached to, skip offline/not present CPUs
		 */
		अगर (p->cpu_cnt <= 0 && (cpu >= n || !online[cpu]))
			जारी;

		cpu_buf = perf_buffer__खोलो_cpu_buf(pb, p->attr, cpu, map_key);
		अगर (IS_ERR(cpu_buf)) अणु
			err = PTR_ERR(cpu_buf);
			जाओ error;
		पूर्ण

		pb->cpu_bufs[j] = cpu_buf;

		err = bpf_map_update_elem(pb->map_fd, &map_key,
					  &cpu_buf->fd, 0);
		अगर (err) अणु
			err = -त्रुटि_सं;
			pr_warn("failed to set cpu #%d, key %d -> perf FD %d: %s\n",
				cpu, map_key, cpu_buf->fd,
				libbpf_म_त्रुटि_r(err, msg, माप(msg)));
			जाओ error;
		पूर्ण

		pb->events[j].events = EPOLLIN;
		pb->events[j].data.ptr = cpu_buf;
		अगर (epoll_ctl(pb->epoll_fd, EPOLL_CTL_ADD, cpu_buf->fd,
			      &pb->events[j]) < 0) अणु
			err = -त्रुटि_सं;
			pr_warn("failed to epoll_ctl cpu #%d perf FD %d: %s\n",
				cpu, cpu_buf->fd,
				libbpf_म_त्रुटि_r(err, msg, माप(msg)));
			जाओ error;
		पूर्ण
		j++;
	पूर्ण
	pb->cpu_cnt = j;
	मुक्त(online);

	वापस pb;

error:
	मुक्त(online);
	अगर (pb)
		perf_buffer__मुक्त(pb);
	वापस ERR_PTR(err);
पूर्ण

काष्ठा perf_sample_raw अणु
	काष्ठा perf_event_header header;
	uपूर्णांक32_t size;
	अक्षर data[];
पूर्ण;

काष्ठा perf_sample_lost अणु
	काष्ठा perf_event_header header;
	uपूर्णांक64_t id;
	uपूर्णांक64_t lost;
	uपूर्णांक64_t sample_id;
पूर्ण;

अटल क्रमागत bpf_perf_event_ret
perf_buffer__process_record(काष्ठा perf_event_header *e, व्योम *ctx)
अणु
	काष्ठा perf_cpu_buf *cpu_buf = ctx;
	काष्ठा perf_buffer *pb = cpu_buf->pb;
	व्योम *data = e;

	/* user wants full control over parsing perf event */
	अगर (pb->event_cb)
		वापस pb->event_cb(pb->ctx, cpu_buf->cpu, e);

	चयन (e->type) अणु
	हाल PERF_RECORD_SAMPLE: अणु
		काष्ठा perf_sample_raw *s = data;

		अगर (pb->sample_cb)
			pb->sample_cb(pb->ctx, cpu_buf->cpu, s->data, s->size);
		अवरोध;
	पूर्ण
	हाल PERF_RECORD_LOST: अणु
		काष्ठा perf_sample_lost *s = data;

		अगर (pb->lost_cb)
			pb->lost_cb(pb->ctx, cpu_buf->cpu, s->lost);
		अवरोध;
	पूर्ण
	शेष:
		pr_warn("unknown perf sample type %d\n", e->type);
		वापस LIBBPF_PERF_EVENT_ERROR;
	पूर्ण
	वापस LIBBPF_PERF_EVENT_CONT;
पूर्ण

अटल पूर्णांक perf_buffer__process_records(काष्ठा perf_buffer *pb,
					काष्ठा perf_cpu_buf *cpu_buf)
अणु
	क्रमागत bpf_perf_event_ret ret;

	ret = bpf_perf_event_पढ़ो_simple(cpu_buf->base, pb->mmap_size,
					 pb->page_size, &cpu_buf->buf,
					 &cpu_buf->buf_size,
					 perf_buffer__process_record, cpu_buf);
	अगर (ret != LIBBPF_PERF_EVENT_CONT)
		वापस ret;
	वापस 0;
पूर्ण

पूर्णांक perf_buffer__epoll_fd(स्थिर काष्ठा perf_buffer *pb)
अणु
	वापस pb->epoll_fd;
पूर्ण

पूर्णांक perf_buffer__poll(काष्ठा perf_buffer *pb, पूर्णांक समयout_ms)
अणु
	पूर्णांक i, cnt, err;

	cnt = epoll_रुको(pb->epoll_fd, pb->events, pb->cpu_cnt, समयout_ms);
	क्रम (i = 0; i < cnt; i++) अणु
		काष्ठा perf_cpu_buf *cpu_buf = pb->events[i].data.ptr;

		err = perf_buffer__process_records(pb, cpu_buf);
		अगर (err) अणु
			pr_warn("error while processing records: %d\n", err);
			वापस err;
		पूर्ण
	पूर्ण
	वापस cnt < 0 ? -त्रुटि_सं : cnt;
पूर्ण

/* Return number of PERF_EVENT_ARRAY map slots set up by this perf_buffer
 * manager.
 */
माप_प्रकार perf_buffer__buffer_cnt(स्थिर काष्ठा perf_buffer *pb)
अणु
	वापस pb->cpu_cnt;
पूर्ण

/*
 * Return perf_event FD of a ring buffer in *buf_idx* slot of
 * PERF_EVENT_ARRAY BPF map. This FD can be polled क्रम new data using
 * select()/poll()/epoll() Linux syscalls.
 */
पूर्णांक perf_buffer__buffer_fd(स्थिर काष्ठा perf_buffer *pb, माप_प्रकार buf_idx)
अणु
	काष्ठा perf_cpu_buf *cpu_buf;

	अगर (buf_idx >= pb->cpu_cnt)
		वापस -EINVAL;

	cpu_buf = pb->cpu_bufs[buf_idx];
	अगर (!cpu_buf)
		वापस -ENOENT;

	वापस cpu_buf->fd;
पूर्ण

/*
 * Consume data from perf ring buffer corresponding to slot *buf_idx* in
 * PERF_EVENT_ARRAY BPF map without रुकोing/polling. If there is no data to
 * consume, करो nothing and वापस success.
 * Returns:
 *   - 0 on success;
 *   - <0 on failure.
 */
पूर्णांक perf_buffer__consume_buffer(काष्ठा perf_buffer *pb, माप_प्रकार buf_idx)
अणु
	काष्ठा perf_cpu_buf *cpu_buf;

	अगर (buf_idx >= pb->cpu_cnt)
		वापस -EINVAL;

	cpu_buf = pb->cpu_bufs[buf_idx];
	अगर (!cpu_buf)
		वापस -ENOENT;

	वापस perf_buffer__process_records(pb, cpu_buf);
पूर्ण

पूर्णांक perf_buffer__consume(काष्ठा perf_buffer *pb)
अणु
	पूर्णांक i, err;

	क्रम (i = 0; i < pb->cpu_cnt; i++) अणु
		काष्ठा perf_cpu_buf *cpu_buf = pb->cpu_bufs[i];

		अगर (!cpu_buf)
			जारी;

		err = perf_buffer__process_records(pb, cpu_buf);
		अगर (err) अणु
			pr_warn("perf_buffer: failed to process records in buffer #%d: %d\n", i, err);
			वापस err;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

काष्ठा bpf_prog_info_array_desc अणु
	पूर्णांक	array_offset;	/* e.g. offset of jited_prog_insns */
	पूर्णांक	count_offset;	/* e.g. offset of jited_prog_len */
	पूर्णांक	size_offset;	/* > 0: offset of rec size,
				 * < 0: fix size of -size_offset
				 */
पूर्ण;

अटल काष्ठा bpf_prog_info_array_desc bpf_prog_info_array_desc[] = अणु
	[BPF_PROG_INFO_JITED_INSNS] = अणु
		दुरत्व(काष्ठा bpf_prog_info, jited_prog_insns),
		दुरत्व(काष्ठा bpf_prog_info, jited_prog_len),
		-1,
	पूर्ण,
	[BPF_PROG_INFO_XLATED_INSNS] = अणु
		दुरत्व(काष्ठा bpf_prog_info, xlated_prog_insns),
		दुरत्व(काष्ठा bpf_prog_info, xlated_prog_len),
		-1,
	पूर्ण,
	[BPF_PROG_INFO_MAP_IDS] = अणु
		दुरत्व(काष्ठा bpf_prog_info, map_ids),
		दुरत्व(काष्ठा bpf_prog_info, nr_map_ids),
		-(पूर्णांक)माप(__u32),
	पूर्ण,
	[BPF_PROG_INFO_JITED_KSYMS] = अणु
		दुरत्व(काष्ठा bpf_prog_info, jited_ksyms),
		दुरत्व(काष्ठा bpf_prog_info, nr_jited_ksyms),
		-(पूर्णांक)माप(__u64),
	पूर्ण,
	[BPF_PROG_INFO_JITED_FUNC_LENS] = अणु
		दुरत्व(काष्ठा bpf_prog_info, jited_func_lens),
		दुरत्व(काष्ठा bpf_prog_info, nr_jited_func_lens),
		-(पूर्णांक)माप(__u32),
	पूर्ण,
	[BPF_PROG_INFO_FUNC_INFO] = अणु
		दुरत्व(काष्ठा bpf_prog_info, func_info),
		दुरत्व(काष्ठा bpf_prog_info, nr_func_info),
		दुरत्व(काष्ठा bpf_prog_info, func_info_rec_size),
	पूर्ण,
	[BPF_PROG_INFO_LINE_INFO] = अणु
		दुरत्व(काष्ठा bpf_prog_info, line_info),
		दुरत्व(काष्ठा bpf_prog_info, nr_line_info),
		दुरत्व(काष्ठा bpf_prog_info, line_info_rec_size),
	पूर्ण,
	[BPF_PROG_INFO_JITED_LINE_INFO] = अणु
		दुरत्व(काष्ठा bpf_prog_info, jited_line_info),
		दुरत्व(काष्ठा bpf_prog_info, nr_jited_line_info),
		दुरत्व(काष्ठा bpf_prog_info, jited_line_info_rec_size),
	पूर्ण,
	[BPF_PROG_INFO_PROG_TAGS] = अणु
		दुरत्व(काष्ठा bpf_prog_info, prog_tags),
		दुरत्व(काष्ठा bpf_prog_info, nr_prog_tags),
		-(पूर्णांक)माप(__u8) * BPF_TAG_SIZE,
	पूर्ण,

पूर्ण;

अटल __u32 bpf_prog_info_पढ़ो_offset_u32(काष्ठा bpf_prog_info *info,
					   पूर्णांक offset)
अणु
	__u32 *array = (__u32 *)info;

	अगर (offset >= 0)
		वापस array[offset / माप(__u32)];
	वापस -(पूर्णांक)offset;
पूर्ण

अटल __u64 bpf_prog_info_पढ़ो_offset_u64(काष्ठा bpf_prog_info *info,
					   पूर्णांक offset)
अणु
	__u64 *array = (__u64 *)info;

	अगर (offset >= 0)
		वापस array[offset / माप(__u64)];
	वापस -(पूर्णांक)offset;
पूर्ण

अटल व्योम bpf_prog_info_set_offset_u32(काष्ठा bpf_prog_info *info, पूर्णांक offset,
					 __u32 val)
अणु
	__u32 *array = (__u32 *)info;

	अगर (offset >= 0)
		array[offset / माप(__u32)] = val;
पूर्ण

अटल व्योम bpf_prog_info_set_offset_u64(काष्ठा bpf_prog_info *info, पूर्णांक offset,
					 __u64 val)
अणु
	__u64 *array = (__u64 *)info;

	अगर (offset >= 0)
		array[offset / माप(__u64)] = val;
पूर्ण

काष्ठा bpf_prog_info_linear *
bpf_program__get_prog_info_linear(पूर्णांक fd, __u64 arrays)
अणु
	काष्ठा bpf_prog_info_linear *info_linear;
	काष्ठा bpf_prog_info info = अणुपूर्ण;
	__u32 info_len = माप(info);
	__u32 data_len = 0;
	पूर्णांक i, err;
	व्योम *ptr;

	अगर (arrays >> BPF_PROG_INFO_LAST_ARRAY)
		वापस ERR_PTR(-EINVAL);

	/* step 1: get array dimensions */
	err = bpf_obj_get_info_by_fd(fd, &info, &info_len);
	अगर (err) अणु
		pr_debug("can't get prog info: %s", म_त्रुटि(त्रुटि_सं));
		वापस ERR_PTR(-EFAULT);
	पूर्ण

	/* step 2: calculate total size of all arrays */
	क्रम (i = BPF_PROG_INFO_FIRST_ARRAY; i < BPF_PROG_INFO_LAST_ARRAY; ++i) अणु
		bool include_array = (arrays & (1UL << i)) > 0;
		काष्ठा bpf_prog_info_array_desc *desc;
		__u32 count, size;

		desc = bpf_prog_info_array_desc + i;

		/* kernel is too old to support this field */
		अगर (info_len < desc->array_offset + माप(__u32) ||
		    info_len < desc->count_offset + माप(__u32) ||
		    (desc->size_offset > 0 && info_len < desc->size_offset))
			include_array = false;

		अगर (!include_array) अणु
			arrays &= ~(1UL << i);	/* clear the bit */
			जारी;
		पूर्ण

		count = bpf_prog_info_पढ़ो_offset_u32(&info, desc->count_offset);
		size  = bpf_prog_info_पढ़ो_offset_u32(&info, desc->size_offset);

		data_len += count * size;
	पूर्ण

	/* step 3: allocate continuous memory */
	data_len = roundup(data_len, माप(__u64));
	info_linear = दो_स्मृति(माप(काष्ठा bpf_prog_info_linear) + data_len);
	अगर (!info_linear)
		वापस ERR_PTR(-ENOMEM);

	/* step 4: fill data to info_linear->info */
	info_linear->arrays = arrays;
	स_रखो(&info_linear->info, 0, माप(info));
	ptr = info_linear->data;

	क्रम (i = BPF_PROG_INFO_FIRST_ARRAY; i < BPF_PROG_INFO_LAST_ARRAY; ++i) अणु
		काष्ठा bpf_prog_info_array_desc *desc;
		__u32 count, size;

		अगर ((arrays & (1UL << i)) == 0)
			जारी;

		desc  = bpf_prog_info_array_desc + i;
		count = bpf_prog_info_पढ़ो_offset_u32(&info, desc->count_offset);
		size  = bpf_prog_info_पढ़ो_offset_u32(&info, desc->size_offset);
		bpf_prog_info_set_offset_u32(&info_linear->info,
					     desc->count_offset, count);
		bpf_prog_info_set_offset_u32(&info_linear->info,
					     desc->size_offset, size);
		bpf_prog_info_set_offset_u64(&info_linear->info,
					     desc->array_offset,
					     ptr_to_u64(ptr));
		ptr += count * size;
	पूर्ण

	/* step 5: call syscall again to get required arrays */
	err = bpf_obj_get_info_by_fd(fd, &info_linear->info, &info_len);
	अगर (err) अणु
		pr_debug("can't get prog info: %s", म_त्रुटि(त्रुटि_सं));
		मुक्त(info_linear);
		वापस ERR_PTR(-EFAULT);
	पूर्ण

	/* step 6: verअगरy the data */
	क्रम (i = BPF_PROG_INFO_FIRST_ARRAY; i < BPF_PROG_INFO_LAST_ARRAY; ++i) अणु
		काष्ठा bpf_prog_info_array_desc *desc;
		__u32 v1, v2;

		अगर ((arrays & (1UL << i)) == 0)
			जारी;

		desc = bpf_prog_info_array_desc + i;
		v1 = bpf_prog_info_पढ़ो_offset_u32(&info, desc->count_offset);
		v2 = bpf_prog_info_पढ़ो_offset_u32(&info_linear->info,
						   desc->count_offset);
		अगर (v1 != v2)
			pr_warn("%s: mismatch in element count\n", __func__);

		v1 = bpf_prog_info_पढ़ो_offset_u32(&info, desc->size_offset);
		v2 = bpf_prog_info_पढ़ो_offset_u32(&info_linear->info,
						   desc->size_offset);
		अगर (v1 != v2)
			pr_warn("%s: mismatch in rec size\n", __func__);
	पूर्ण

	/* step 7: update info_len and data_len */
	info_linear->info_len = माप(काष्ठा bpf_prog_info);
	info_linear->data_len = data_len;

	वापस info_linear;
पूर्ण

व्योम bpf_program__bpil_addr_to_offs(काष्ठा bpf_prog_info_linear *info_linear)
अणु
	पूर्णांक i;

	क्रम (i = BPF_PROG_INFO_FIRST_ARRAY; i < BPF_PROG_INFO_LAST_ARRAY; ++i) अणु
		काष्ठा bpf_prog_info_array_desc *desc;
		__u64 addr, offs;

		अगर ((info_linear->arrays & (1UL << i)) == 0)
			जारी;

		desc = bpf_prog_info_array_desc + i;
		addr = bpf_prog_info_पढ़ो_offset_u64(&info_linear->info,
						     desc->array_offset);
		offs = addr - ptr_to_u64(info_linear->data);
		bpf_prog_info_set_offset_u64(&info_linear->info,
					     desc->array_offset, offs);
	पूर्ण
पूर्ण

व्योम bpf_program__bpil_offs_to_addr(काष्ठा bpf_prog_info_linear *info_linear)
अणु
	पूर्णांक i;

	क्रम (i = BPF_PROG_INFO_FIRST_ARRAY; i < BPF_PROG_INFO_LAST_ARRAY; ++i) अणु
		काष्ठा bpf_prog_info_array_desc *desc;
		__u64 addr, offs;

		अगर ((info_linear->arrays & (1UL << i)) == 0)
			जारी;

		desc = bpf_prog_info_array_desc + i;
		offs = bpf_prog_info_पढ़ो_offset_u64(&info_linear->info,
						     desc->array_offset);
		addr = offs + ptr_to_u64(info_linear->data);
		bpf_prog_info_set_offset_u64(&info_linear->info,
					     desc->array_offset, addr);
	पूर्ण
पूर्ण

पूर्णांक bpf_program__set_attach_target(काष्ठा bpf_program *prog,
				   पूर्णांक attach_prog_fd,
				   स्थिर अक्षर *attach_func_name)
अणु
	पूर्णांक btf_obj_fd = 0, btf_id = 0, err;

	अगर (!prog || attach_prog_fd < 0 || !attach_func_name)
		वापस -EINVAL;

	अगर (prog->obj->loaded)
		वापस -EINVAL;

	अगर (attach_prog_fd) अणु
		btf_id = libbpf_find_prog_btf_id(attach_func_name,
						 attach_prog_fd);
		अगर (btf_id < 0)
			वापस btf_id;
	पूर्ण अन्यथा अणु
		/* load btf_vmlinux, अगर not yet */
		err = bpf_object__load_vmlinux_btf(prog->obj, true);
		अगर (err)
			वापस err;
		err = find_kernel_btf_id(prog->obj, attach_func_name,
					 prog->expected_attach_type,
					 &btf_obj_fd, &btf_id);
		अगर (err)
			वापस err;
	पूर्ण

	prog->attach_btf_id = btf_id;
	prog->attach_btf_obj_fd = btf_obj_fd;
	prog->attach_prog_fd = attach_prog_fd;
	वापस 0;
पूर्ण

पूर्णांक parse_cpu_mask_str(स्थिर अक्षर *s, bool **mask, पूर्णांक *mask_sz)
अणु
	पूर्णांक err = 0, n, len, start, end = -1;
	bool *पंचांगp;

	*mask = शून्य;
	*mask_sz = 0;

	/* Each sub string separated by ',' has क्रमmat \d+-\d+ or \d+ */
	जबतक (*s) अणु
		अगर (*s == ',' || *s == '\n') अणु
			s++;
			जारी;
		पूर्ण
		n = माला_पूछो(s, "%d%n-%d%n", &start, &len, &end, &len);
		अगर (n <= 0 || n > 2) अणु
			pr_warn("Failed to get CPU range %s: %d\n", s, n);
			err = -EINVAL;
			जाओ cleanup;
		पूर्ण अन्यथा अगर (n == 1) अणु
			end = start;
		पूर्ण
		अगर (start < 0 || start > end) अणु
			pr_warn("Invalid CPU range [%d,%d] in %s\n",
				start, end, s);
			err = -EINVAL;
			जाओ cleanup;
		पूर्ण
		पंचांगp = पुनः_स्मृति(*mask, end + 1);
		अगर (!पंचांगp) अणु
			err = -ENOMEM;
			जाओ cleanup;
		पूर्ण
		*mask = पंचांगp;
		स_रखो(पंचांगp + *mask_sz, 0, start - *mask_sz);
		स_रखो(पंचांगp + start, 1, end - start + 1);
		*mask_sz = end + 1;
		s += len;
	पूर्ण
	अगर (!*mask_sz) अणु
		pr_warn("Empty CPU range\n");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
cleanup:
	मुक्त(*mask);
	*mask = शून्य;
	वापस err;
पूर्ण

पूर्णांक parse_cpu_mask_file(स्थिर अक्षर *fcpu, bool **mask, पूर्णांक *mask_sz)
अणु
	पूर्णांक fd, err = 0, len;
	अक्षर buf[128];

	fd = खोलो(fcpu, O_RDONLY);
	अगर (fd < 0) अणु
		err = -त्रुटि_सं;
		pr_warn("Failed to open cpu mask file %s: %d\n", fcpu, err);
		वापस err;
	पूर्ण
	len = पढ़ो(fd, buf, माप(buf));
	बंद(fd);
	अगर (len <= 0) अणु
		err = len ? -त्रुटि_सं : -EINVAL;
		pr_warn("Failed to read cpu mask from %s: %d\n", fcpu, err);
		वापस err;
	पूर्ण
	अगर (len >= माप(buf)) अणु
		pr_warn("CPU mask is too big in file %s\n", fcpu);
		वापस -E2BIG;
	पूर्ण
	buf[len] = '\0';

	वापस parse_cpu_mask_str(buf, mask, mask_sz);
पूर्ण

पूर्णांक libbpf_num_possible_cpus(व्योम)
अणु
	अटल स्थिर अक्षर *fcpu = "/sys/devices/system/cpu/possible";
	अटल पूर्णांक cpus;
	पूर्णांक err, n, i, पंचांगp_cpus;
	bool *mask;

	पंचांगp_cpus = READ_ONCE(cpus);
	अगर (पंचांगp_cpus > 0)
		वापस पंचांगp_cpus;

	err = parse_cpu_mask_file(fcpu, &mask, &n);
	अगर (err)
		वापस err;

	पंचांगp_cpus = 0;
	क्रम (i = 0; i < n; i++) अणु
		अगर (mask[i])
			पंचांगp_cpus++;
	पूर्ण
	मुक्त(mask);

	WRITE_ONCE(cpus, पंचांगp_cpus);
	वापस पंचांगp_cpus;
पूर्ण

पूर्णांक bpf_object__खोलो_skeleton(काष्ठा bpf_object_skeleton *s,
			      स्थिर काष्ठा bpf_object_खोलो_opts *opts)
अणु
	DECLARE_LIBBPF_OPTS(bpf_object_खोलो_opts, skel_opts,
		.object_name = s->name,
	);
	काष्ठा bpf_object *obj;
	पूर्णांक i;

	/* Attempt to preserve opts->object_name, unless overriden by user
	 * explicitly. Overwriting object name क्रम skeletons is discouraged,
	 * as it अवरोधs global data maps, because they contain object name
	 * prefix as their own map name prefix. When skeleton is generated,
	 * bpftool is making an assumption that this name will stay the same.
	 */
	अगर (opts) अणु
		स_नकल(&skel_opts, opts, माप(*opts));
		अगर (!opts->object_name)
			skel_opts.object_name = s->name;
	पूर्ण

	obj = bpf_object__खोलो_mem(s->data, s->data_sz, &skel_opts);
	अगर (IS_ERR(obj)) अणु
		pr_warn("failed to initialize skeleton BPF object '%s': %ld\n",
			s->name, PTR_ERR(obj));
		वापस PTR_ERR(obj);
	पूर्ण

	*s->obj = obj;

	क्रम (i = 0; i < s->map_cnt; i++) अणु
		काष्ठा bpf_map **map = s->maps[i].map;
		स्थिर अक्षर *name = s->maps[i].name;
		व्योम **mmaped = s->maps[i].mmaped;

		*map = bpf_object__find_map_by_name(obj, name);
		अगर (!*map) अणु
			pr_warn("failed to find skeleton map '%s'\n", name);
			वापस -ESRCH;
		पूर्ण

		/* बाह्यs shouldn't be pre-setup from user code */
		अगर (mmaped && (*map)->libbpf_type != LIBBPF_MAP_KCONFIG)
			*mmaped = (*map)->mmaped;
	पूर्ण

	क्रम (i = 0; i < s->prog_cnt; i++) अणु
		काष्ठा bpf_program **prog = s->progs[i].prog;
		स्थिर अक्षर *name = s->progs[i].name;

		*prog = bpf_object__find_program_by_name(obj, name);
		अगर (!*prog) अणु
			pr_warn("failed to find skeleton program '%s'\n", name);
			वापस -ESRCH;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक bpf_object__load_skeleton(काष्ठा bpf_object_skeleton *s)
अणु
	पूर्णांक i, err;

	err = bpf_object__load(*s->obj);
	अगर (err) अणु
		pr_warn("failed to load BPF skeleton '%s': %d\n", s->name, err);
		वापस err;
	पूर्ण

	क्रम (i = 0; i < s->map_cnt; i++) अणु
		काष्ठा bpf_map *map = *s->maps[i].map;
		माप_प्रकार mmap_sz = bpf_map_mmap_sz(map);
		पूर्णांक prot, map_fd = bpf_map__fd(map);
		व्योम **mmaped = s->maps[i].mmaped;

		अगर (!mmaped)
			जारी;

		अगर (!(map->def.map_flags & BPF_F_MMAPABLE)) अणु
			*mmaped = शून्य;
			जारी;
		पूर्ण

		अगर (map->def.map_flags & BPF_F_RDONLY_PROG)
			prot = PROT_READ;
		अन्यथा
			prot = PROT_READ | PROT_WRITE;

		/* Remap anonymous mmap()-ed "map initialization image" as
		 * a BPF map-backed mmap()-ed memory, but preserving the same
		 * memory address. This will cause kernel to change process'
		 * page table to poपूर्णांक to a dअगरferent piece of kernel memory,
		 * but from userspace poपूर्णांक of view memory address (and its
		 * contents, being identical at this poपूर्णांक) will stay the
		 * same. This mapping will be released by bpf_object__बंद()
		 * as per normal clean up procedure, so we करोn't need to worry
		 * about it from skeleton's clean up perspective.
		 */
		*mmaped = mmap(map->mmaped, mmap_sz, prot,
				MAP_SHARED | MAP_FIXED, map_fd, 0);
		अगर (*mmaped == MAP_FAILED) अणु
			err = -त्रुटि_सं;
			*mmaped = शून्य;
			pr_warn("failed to re-mmap() map '%s': %d\n",
				 bpf_map__name(map), err);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक bpf_object__attach_skeleton(काष्ठा bpf_object_skeleton *s)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < s->prog_cnt; i++) अणु
		काष्ठा bpf_program *prog = *s->progs[i].prog;
		काष्ठा bpf_link **link = s->progs[i].link;
		स्थिर काष्ठा bpf_sec_def *sec_def;

		अगर (!prog->load)
			जारी;

		sec_def = find_sec_def(prog->sec_name);
		अगर (!sec_def || !sec_def->attach_fn)
			जारी;

		*link = sec_def->attach_fn(sec_def, prog);
		अगर (IS_ERR(*link)) अणु
			pr_warn("failed to auto-attach program '%s': %ld\n",
				bpf_program__name(prog), PTR_ERR(*link));
			वापस PTR_ERR(*link);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

व्योम bpf_object__detach_skeleton(काष्ठा bpf_object_skeleton *s)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < s->prog_cnt; i++) अणु
		काष्ठा bpf_link **link = s->progs[i].link;

		bpf_link__destroy(*link);
		*link = शून्य;
	पूर्ण
पूर्ण

व्योम bpf_object__destroy_skeleton(काष्ठा bpf_object_skeleton *s)
अणु
	अगर (s->progs)
		bpf_object__detach_skeleton(s);
	अगर (s->obj)
		bpf_object__बंद(*s->obj);
	मुक्त(s->maps);
	मुक्त(s->progs);
	मुक्त(s);
पूर्ण
