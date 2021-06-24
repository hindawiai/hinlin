<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause) */
/* Copyright (C) 2017-2018 Netronome Systems, Inc. */

#अगर_अघोषित __BPF_TOOL_H
#घोषणा __BPF_TOOL_H

/* BFD and kernel.h both define GCC_VERSION, dअगरferently */
#अघोषित GCC_VERSION
#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <linux/bpf.h>
#समावेश <linux/compiler.h>
#समावेश <linux/kernel.h>
#समावेश <linux/hashtable.h>
#समावेश <tools/libc_compat.h>

#समावेश <bpf/libbpf.h>

#समावेश "json_writer.h"

/* Make sure we करो not use kernel-only पूर्णांकeger प्रकारs */
#आशय GCC poison u8 u16 u32 u64 s8 s16 s32 s64

अटल अंतरभूत __u64 ptr_to_u64(स्थिर व्योम *ptr)
अणु
	वापस (__u64)(अचिन्हित दीर्घ)ptr;
पूर्ण

अटल अंतरभूत व्योम *u64_to_ptr(__u64 ptr)
अणु
	वापस (व्योम *)(अचिन्हित दीर्घ)ptr;
पूर्ण

#घोषणा NEXT_ARG()	(अणु argc--; argv++; अगर (argc < 0) usage(); पूर्ण)
#घोषणा NEXT_ARGP()	(अणु (*argc)--; (*argv)++; अगर (*argc < 0) usage(); पूर्ण)
#घोषणा BAD_ARG()	(अणु p_err("what is '%s'?", *argv); -1; पूर्ण)
#घोषणा GET_ARG()	(अणु argc--; *argv++; पूर्ण)
#घोषणा REQ_ARGS(cnt)							\
	(अणु								\
		पूर्णांक _cnt = (cnt);					\
		bool _res;						\
									\
		अगर (argc < _cnt) अणु					\
			p_err("'%s' needs at least %d arguments, %d found", \
			      argv[-1], _cnt, argc);			\
			_res = false;					\
		पूर्ण अन्यथा अणु						\
			_res = true;					\
		पूर्ण							\
		_res;							\
	पूर्ण)

#घोषणा ERR_MAX_LEN	1024

#घोषणा BPF_TAG_FMT	"%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx"

#घोषणा HELP_SPEC_PROGRAM						\
	"PROG := { id PROG_ID | pinned FILE | tag PROG_TAG | name PROG_NAME }"
#घोषणा HELP_SPEC_OPTIONS						\
	"OPTIONS := { {-j|--json} [{-p|--pretty}] | {-f|--bpffs} |\n"	\
	"\t            {-m|--mapcompat} | {-n|--nomount} }"
#घोषणा HELP_SPEC_MAP							\
	"MAP := { id MAP_ID | pinned FILE | name MAP_NAME }"
#घोषणा HELP_SPEC_LINK							\
	"LINK := { id LINK_ID | pinned FILE }"

बाह्य स्थिर अक्षर * स्थिर prog_type_name[];
बाह्य स्थिर माप_प्रकार prog_type_name_size;

बाह्य स्थिर अक्षर * स्थिर attach_type_name[__MAX_BPF_ATTACH_TYPE];

बाह्य स्थिर अक्षर * स्थिर map_type_name[];
बाह्य स्थिर माप_प्रकार map_type_name_size;

/* keep in sync with the definition in skeleton/pid_iter.bpf.c */
क्रमागत bpf_obj_type अणु
	BPF_OBJ_UNKNOWN,
	BPF_OBJ_PROG,
	BPF_OBJ_MAP,
	BPF_OBJ_LINK,
	BPF_OBJ_BTF,
पूर्ण;

बाह्य स्थिर अक्षर *bin_name;

बाह्य json_ग_लिखोr_t *json_wtr;
बाह्य bool json_output;
बाह्य bool show_pinned;
बाह्य bool show_pids;
बाह्य bool block_mount;
बाह्य bool verअगरier_logs;
बाह्य bool relaxed_maps;
बाह्य काष्ठा btf *base_btf;
बाह्य काष्ठा pinned_obj_table prog_table;
बाह्य काष्ठा pinned_obj_table map_table;
बाह्य काष्ठा pinned_obj_table link_table;
बाह्य काष्ठा obj_refs_table refs_table;

व्योम __म_लिखो(1, 2) p_err(स्थिर अक्षर *fmt, ...);
व्योम __म_लिखो(1, 2) p_info(स्थिर अक्षर *fmt, ...);

bool is_prefix(स्थिर अक्षर *pfx, स्थिर अक्षर *str);
पूर्णांक detect_common_prefix(स्थिर अक्षर *arg, ...);
व्योम fprपूर्णांक_hex(खाता *f, व्योम *arg, अचिन्हित पूर्णांक n, स्थिर अक्षर *sep);
व्योम usage(व्योम) __noवापस;

व्योम set_max_rlimit(व्योम);

पूर्णांक mount_tracefs(स्थिर अक्षर *target);

काष्ठा pinned_obj_table अणु
	DECLARE_HASHTABLE(table, 16);
पूर्ण;

काष्ठा pinned_obj अणु
	__u32 id;
	अक्षर *path;
	काष्ठा hlist_node hash;
पूर्ण;

काष्ठा obj_refs_table अणु
	DECLARE_HASHTABLE(table, 16);
पूर्ण;

काष्ठा obj_ref अणु
	पूर्णांक pid;
	अक्षर comm[16];
पूर्ण;

काष्ठा obj_refs अणु
	काष्ठा hlist_node node;
	__u32 id;
	पूर्णांक ref_cnt;
	काष्ठा obj_ref *refs;
पूर्ण;

काष्ठा btf;
काष्ठा bpf_line_info;

पूर्णांक build_pinned_obj_table(काष्ठा pinned_obj_table *table,
			   क्रमागत bpf_obj_type type);
व्योम delete_pinned_obj_table(काष्ठा pinned_obj_table *tab);
__weak पूर्णांक build_obj_refs_table(काष्ठा obj_refs_table *table,
				क्रमागत bpf_obj_type type);
__weak व्योम delete_obj_refs_table(काष्ठा obj_refs_table *table);
__weak व्योम emit_obj_refs_json(काष्ठा obj_refs_table *table, __u32 id,
			       json_ग_लिखोr_t *json_wtr);
__weak व्योम emit_obj_refs_plain(काष्ठा obj_refs_table *table, __u32 id,
				स्थिर अक्षर *prefix);
व्योम prपूर्णांक_dev_plain(__u32 अगरindex, __u64 ns_dev, __u64 ns_inode);
व्योम prपूर्णांक_dev_json(__u32 अगरindex, __u64 ns_dev, __u64 ns_inode);

काष्ठा cmd अणु
	स्थिर अक्षर *cmd;
	पूर्णांक (*func)(पूर्णांक argc, अक्षर **argv);
पूर्ण;

पूर्णांक cmd_select(स्थिर काष्ठा cmd *cmds, पूर्णांक argc, अक्षर **argv,
	       पूर्णांक (*help)(पूर्णांक argc, अक्षर **argv));

पूर्णांक get_fd_type(पूर्णांक fd);
स्थिर अक्षर *get_fd_type_name(क्रमागत bpf_obj_type type);
अक्षर *get_fdinfo(पूर्णांक fd, स्थिर अक्षर *key);
पूर्णांक खोलो_obj_pinned(स्थिर अक्षर *path, bool quiet);
पूर्णांक खोलो_obj_pinned_any(स्थिर अक्षर *path, क्रमागत bpf_obj_type exp_type);
पूर्णांक mount_bpffs_क्रम_pin(स्थिर अक्षर *name);
पूर्णांक करो_pin_any(पूर्णांक argc, अक्षर **argv, पूर्णांक (*get_fd_by_id)(पूर्णांक *, अक्षर ***));
पूर्णांक करो_pin_fd(पूर्णांक fd, स्थिर अक्षर *name);

/* commands available in bootstrap mode */
पूर्णांक करो_gen(पूर्णांक argc, अक्षर **argv);
पूर्णांक करो_btf(पूर्णांक argc, अक्षर **argv);

/* non-bootstrap only commands */
पूर्णांक करो_prog(पूर्णांक argc, अक्षर **arg) __weak;
पूर्णांक करो_map(पूर्णांक argc, अक्षर **arg) __weak;
पूर्णांक करो_link(पूर्णांक argc, अक्षर **arg) __weak;
पूर्णांक करो_event_pipe(पूर्णांक argc, अक्षर **argv) __weak;
पूर्णांक करो_cgroup(पूर्णांक argc, अक्षर **arg) __weak;
पूर्णांक करो_perf(पूर्णांक argc, अक्षर **arg) __weak;
पूर्णांक करो_net(पूर्णांक argc, अक्षर **arg) __weak;
पूर्णांक करो_tracelog(पूर्णांक argc, अक्षर **arg) __weak;
पूर्णांक करो_feature(पूर्णांक argc, अक्षर **argv) __weak;
पूर्णांक करो_काष्ठा_ops(पूर्णांक argc, अक्षर **argv) __weak;
पूर्णांक करो_iter(पूर्णांक argc, अक्षर **argv) __weak;

पूर्णांक parse_u32_arg(पूर्णांक *argc, अक्षर ***argv, __u32 *val, स्थिर अक्षर *what);
पूर्णांक prog_parse_fd(पूर्णांक *argc, अक्षर ***argv);
पूर्णांक prog_parse_fds(पूर्णांक *argc, अक्षर ***argv, पूर्णांक **fds);
पूर्णांक map_parse_fd(पूर्णांक *argc, अक्षर ***argv);
पूर्णांक map_parse_fds(पूर्णांक *argc, अक्षर ***argv, पूर्णांक **fds);
पूर्णांक map_parse_fd_and_info(पूर्णांक *argc, अक्षर ***argv, व्योम *info, __u32 *info_len);

काष्ठा bpf_prog_linfo;
#अगर_घोषित HAVE_LIBBFD_SUPPORT
व्योम disयंत्र_prपूर्णांक_insn(अचिन्हित अक्षर *image, sमाप_प्रकार len, पूर्णांक opcodes,
		       स्थिर अक्षर *arch, स्थिर अक्षर *disassembler_options,
		       स्थिर काष्ठा btf *btf,
		       स्थिर काष्ठा bpf_prog_linfo *prog_linfo,
		       __u64 func_ksym, अचिन्हित पूर्णांक func_idx,
		       bool linum);
पूर्णांक disयंत्र_init(व्योम);
#अन्यथा
अटल अंतरभूत
व्योम disयंत्र_prपूर्णांक_insn(अचिन्हित अक्षर *image, sमाप_प्रकार len, पूर्णांक opcodes,
		       स्थिर अक्षर *arch, स्थिर अक्षर *disassembler_options,
		       स्थिर काष्ठा btf *btf,
		       स्थिर काष्ठा bpf_prog_linfo *prog_linfo,
		       __u64 func_ksym, अचिन्हित पूर्णांक func_idx,
		       bool linum)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक disयंत्र_init(व्योम)
अणु
	p_err("No libbfd support");
	वापस -1;
पूर्ण
#पूर्ण_अगर
व्योम prपूर्णांक_data_json(uपूर्णांक8_t *data, माप_प्रकार len);
व्योम prपूर्णांक_hex_data_json(uपूर्णांक8_t *data, माप_प्रकार len);

अचिन्हित पूर्णांक get_page_size(व्योम);
अचिन्हित पूर्णांक get_possible_cpus(व्योम);
स्थिर अक्षर *
अगरindex_to_bfd_params(__u32 अगरindex, __u64 ns_dev, __u64 ns_ino,
		      स्थिर अक्षर **opt);

काष्ठा btf_dumper अणु
	स्थिर काष्ठा btf *btf;
	json_ग_लिखोr_t *jw;
	bool is_plain_text;
	bool prog_id_as_func_ptr;
पूर्ण;

/* btf_dumper_type - prपूर्णांक data aदीर्घ with type inक्रमmation
 * @d: an instance containing context क्रम dumping types
 * @type_id: index in btf->types array. this poपूर्णांकs to the type to be dumped
 * @data: poपूर्णांकer the actual data, i.e. the values to be prपूर्णांकed
 *
 * Returns zero on success and negative error code otherwise
 */
पूर्णांक btf_dumper_type(स्थिर काष्ठा btf_dumper *d, __u32 type_id,
		    स्थिर व्योम *data);
व्योम btf_dumper_type_only(स्थिर काष्ठा btf *btf, __u32 func_type_id,
			  अक्षर *func_only, पूर्णांक size);

व्योम btf_dump_linfo_plain(स्थिर काष्ठा btf *btf,
			  स्थिर काष्ठा bpf_line_info *linfo,
			  स्थिर अक्षर *prefix, bool linum);
व्योम btf_dump_linfo_json(स्थिर काष्ठा btf *btf,
			 स्थिर काष्ठा bpf_line_info *linfo, bool linum);

काष्ठा nlattr;
काष्ठा अगरinfomsg;
काष्ठा tcmsg;
पूर्णांक करो_xdp_dump(काष्ठा अगरinfomsg *अगरinfo, काष्ठा nlattr **tb);
पूर्णांक करो_filter_dump(काष्ठा tcmsg *अगरinfo, काष्ठा nlattr **tb, स्थिर अक्षर *kind,
		   स्थिर अक्षर *devname, पूर्णांक अगरindex);

पूर्णांक prपूर्णांक_all_levels(__maybe_unused क्रमागत libbpf_prपूर्णांक_level level,
		     स्थिर अक्षर *क्रमmat, बहु_सूची args);
#पूर्ण_अगर
