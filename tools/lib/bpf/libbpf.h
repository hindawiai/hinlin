<शैली गुरु>
/* SPDX-License-Identअगरier: (LGPL-2.1 OR BSD-2-Clause) */

/*
 * Common eBPF ELF object loading operations.
 *
 * Copyright (C) 2013-2015 Alexei Starovoitov <ast@kernel.org>
 * Copyright (C) 2015 Wang Nan <wangnan0@huawei.com>
 * Copyright (C) 2015 Huawei Inc.
 */
#अगर_अघोषित __LIBBPF_LIBBPF_H
#घोषणा __LIBBPF_LIBBPF_H

#समावेश <मानकतर्क.स>
#समावेश <मानकपन.स>
#समावेश <मानक_निवेशt.h>
#समावेश <stdbool.h>
#समावेश <sys/types.h>  // क्रम माप_प्रकार
#समावेश <linux/bpf.h>

#समावेश "libbpf_common.h"

#अगर_घोषित __cplusplus
बाह्य "C" अणु
#पूर्ण_अगर

क्रमागत libbpf_त्रुटि_सं अणु
	__LIBBPF_ERRNO__START = 4000,

	/* Something wrong in libelf */
	LIBBPF_ERRNO__LIBELF = __LIBBPF_ERRNO__START,
	LIBBPF_ERRNO__FORMAT,	/* BPF object क्रमmat invalid */
	LIBBPF_ERRNO__KVERSION,	/* Incorrect or no 'version' section */
	LIBBPF_ERRNO__ENDIAN,	/* Endian mismatch */
	LIBBPF_ERRNO__INTERNAL,	/* Internal error in libbpf */
	LIBBPF_ERRNO__RELOC,	/* Relocation failed */
	LIBBPF_ERRNO__LOAD,	/* Load program failure क्रम unknown reason */
	LIBBPF_ERRNO__VERIFY,	/* Kernel verअगरier blocks program loading */
	LIBBPF_ERRNO__PROG2BIG,	/* Program too big */
	LIBBPF_ERRNO__KVER,	/* Incorrect kernel version */
	LIBBPF_ERRNO__PROGTYPE,	/* Kernel करोesn't support this program type */
	LIBBPF_ERRNO__WRNGPID,	/* Wrong pid in netlink message */
	LIBBPF_ERRNO__INVSEQ,	/* Invalid netlink sequence */
	LIBBPF_ERRNO__NLPARSE,	/* netlink parsing error */
	__LIBBPF_ERRNO__END,
पूर्ण;

LIBBPF_API पूर्णांक libbpf_म_त्रुटि(पूर्णांक err, अक्षर *buf, माप_प्रकार size);

क्रमागत libbpf_prपूर्णांक_level अणु
        LIBBPF_WARN,
        LIBBPF_INFO,
        LIBBPF_DEBUG,
पूर्ण;

प्रकार पूर्णांक (*libbpf_prपूर्णांक_fn_t)(क्रमागत libbpf_prपूर्णांक_level level,
				 स्थिर अक्षर *, बहु_सूची ap);

LIBBPF_API libbpf_prपूर्णांक_fn_t libbpf_set_prपूर्णांक(libbpf_prपूर्णांक_fn_t fn);

/* Hide पूर्णांकernal to user */
काष्ठा bpf_object;

काष्ठा bpf_object_खोलो_attr अणु
	स्थिर अक्षर *file;
	क्रमागत bpf_prog_type prog_type;
पूर्ण;

काष्ठा bpf_object_खोलो_opts अणु
	/* size of this काष्ठा, क्रम क्रमward/backward compatiblity */
	माप_प्रकार sz;
	/* object name override, अगर provided:
	 * - क्रम object खोलो from file, this will override setting object
	 *   name from file path's base name;
	 * - क्रम object खोलो from memory buffer, this will specअगरy an object
	 *   name and will override शेष "<addr>-<buf-size>" name;
	 */
	स्थिर अक्षर *object_name;
	/* parse map definitions non-strictly, allowing extra attributes/data */
	bool relaxed_maps;
	/* DEPRECATED: handle CO-RE relocations non-strictly, allowing failures.
	 * Value is ignored. Relocations always are processed non-strictly.
	 * Non-relocatable inकाष्ठाions are replaced with invalid ones to
	 * prevent accidental errors.
	 * */
	bool relaxed_core_relocs;
	/* maps that set the 'pinning' attribute in their definition will have
	 * their pin_path attribute set to a file in this directory, and be
	 * स्वतः-pinned to that path on load; शेषs to "/sys/fs/bpf".
	 */
	स्थिर अक्षर *pin_root_path;
	__u32 attach_prog_fd;
	/* Additional kernel config content that augments and overrides
	 * प्रणाली Kconfig क्रम CONFIG_xxx बाह्यs.
	 */
	स्थिर अक्षर *kconfig;
पूर्ण;
#घोषणा bpf_object_खोलो_opts__last_field kconfig

LIBBPF_API काष्ठा bpf_object *bpf_object__खोलो(स्थिर अक्षर *path);
LIBBPF_API काष्ठा bpf_object *
bpf_object__खोलो_file(स्थिर अक्षर *path, स्थिर काष्ठा bpf_object_खोलो_opts *opts);
LIBBPF_API काष्ठा bpf_object *
bpf_object__खोलो_mem(स्थिर व्योम *obj_buf, माप_प्रकार obj_buf_sz,
		     स्थिर काष्ठा bpf_object_खोलो_opts *opts);

/* deprecated bpf_object__खोलो variants */
LIBBPF_API काष्ठा bpf_object *
bpf_object__खोलो_buffer(स्थिर व्योम *obj_buf, माप_प्रकार obj_buf_sz,
			स्थिर अक्षर *name);
LIBBPF_API काष्ठा bpf_object *
bpf_object__खोलो_xattr(काष्ठा bpf_object_खोलो_attr *attr);

क्रमागत libbpf_pin_type अणु
	LIBBPF_PIN_NONE,
	/* PIN_BY_NAME: pin maps by name (in /sys/fs/bpf by शेष) */
	LIBBPF_PIN_BY_NAME,
पूर्ण;

/* pin_maps and unpin_maps can both be called with a शून्य path, in which हाल
 * they will use the pin_path attribute of each map (and ignore all maps that
 * करोn't have a pin_path set).
 */
LIBBPF_API पूर्णांक bpf_object__pin_maps(काष्ठा bpf_object *obj, स्थिर अक्षर *path);
LIBBPF_API पूर्णांक bpf_object__unpin_maps(काष्ठा bpf_object *obj,
				      स्थिर अक्षर *path);
LIBBPF_API पूर्णांक bpf_object__pin_programs(काष्ठा bpf_object *obj,
					स्थिर अक्षर *path);
LIBBPF_API पूर्णांक bpf_object__unpin_programs(काष्ठा bpf_object *obj,
					  स्थिर अक्षर *path);
LIBBPF_API पूर्णांक bpf_object__pin(काष्ठा bpf_object *object, स्थिर अक्षर *path);
LIBBPF_API व्योम bpf_object__बंद(काष्ठा bpf_object *object);

काष्ठा bpf_object_load_attr अणु
	काष्ठा bpf_object *obj;
	पूर्णांक log_level;
	स्थिर अक्षर *target_btf_path;
पूर्ण;

/* Load/unload object पूर्णांकo/from kernel */
LIBBPF_API पूर्णांक bpf_object__load(काष्ठा bpf_object *obj);
LIBBPF_API पूर्णांक bpf_object__load_xattr(काष्ठा bpf_object_load_attr *attr);
LIBBPF_API पूर्णांक bpf_object__unload(काष्ठा bpf_object *obj);

LIBBPF_API स्थिर अक्षर *bpf_object__name(स्थिर काष्ठा bpf_object *obj);
LIBBPF_API अचिन्हित पूर्णांक bpf_object__kversion(स्थिर काष्ठा bpf_object *obj);
LIBBPF_API पूर्णांक bpf_object__set_kversion(काष्ठा bpf_object *obj, __u32 kern_version);

काष्ठा btf;
LIBBPF_API काष्ठा btf *bpf_object__btf(स्थिर काष्ठा bpf_object *obj);
LIBBPF_API पूर्णांक bpf_object__btf_fd(स्थिर काष्ठा bpf_object *obj);

LIBBPF_API काष्ठा bpf_program *
bpf_object__find_program_by_title(स्थिर काष्ठा bpf_object *obj,
				  स्थिर अक्षर *title);
LIBBPF_API काष्ठा bpf_program *
bpf_object__find_program_by_name(स्थिर काष्ठा bpf_object *obj,
				 स्थिर अक्षर *name);

LIBBPF_API काष्ठा bpf_object *bpf_object__next(काष्ठा bpf_object *prev);
#घोषणा bpf_object__क्रम_each_safe(pos, पंचांगp)			\
	क्रम ((pos) = bpf_object__next(शून्य),		\
		(पंचांगp) = bpf_object__next(pos);		\
	     (pos) != शून्य;				\
	     (pos) = (पंचांगp), (पंचांगp) = bpf_object__next(पंचांगp))

प्रकार व्योम (*bpf_object_clear_priv_t)(काष्ठा bpf_object *, व्योम *);
LIBBPF_API पूर्णांक bpf_object__set_priv(काष्ठा bpf_object *obj, व्योम *priv,
				    bpf_object_clear_priv_t clear_priv);
LIBBPF_API व्योम *bpf_object__priv(स्थिर काष्ठा bpf_object *prog);

LIBBPF_API पूर्णांक
libbpf_prog_type_by_name(स्थिर अक्षर *name, क्रमागत bpf_prog_type *prog_type,
			 क्रमागत bpf_attach_type *expected_attach_type);
LIBBPF_API पूर्णांक libbpf_attach_type_by_name(स्थिर अक्षर *name,
					  क्रमागत bpf_attach_type *attach_type);
LIBBPF_API पूर्णांक libbpf_find_vmlinux_btf_id(स्थिर अक्षर *name,
					  क्रमागत bpf_attach_type attach_type);

/* Accessors of bpf_program */
काष्ठा bpf_program;
LIBBPF_API काष्ठा bpf_program *bpf_program__next(काष्ठा bpf_program *prog,
						 स्थिर काष्ठा bpf_object *obj);

#घोषणा bpf_object__क्रम_each_program(pos, obj)		\
	क्रम ((pos) = bpf_program__next(शून्य, (obj));	\
	     (pos) != शून्य;				\
	     (pos) = bpf_program__next((pos), (obj)))

LIBBPF_API काष्ठा bpf_program *bpf_program__prev(काष्ठा bpf_program *prog,
						 स्थिर काष्ठा bpf_object *obj);

प्रकार व्योम (*bpf_program_clear_priv_t)(काष्ठा bpf_program *, व्योम *);

LIBBPF_API पूर्णांक bpf_program__set_priv(काष्ठा bpf_program *prog, व्योम *priv,
				     bpf_program_clear_priv_t clear_priv);

LIBBPF_API व्योम *bpf_program__priv(स्थिर काष्ठा bpf_program *prog);
LIBBPF_API व्योम bpf_program__set_अगरindex(काष्ठा bpf_program *prog,
					 __u32 अगरindex);

LIBBPF_API स्थिर अक्षर *bpf_program__name(स्थिर काष्ठा bpf_program *prog);
LIBBPF_API स्थिर अक्षर *bpf_program__section_name(स्थिर काष्ठा bpf_program *prog);
LIBBPF_API LIBBPF_DEPRECATED("BPF program title is confusing term; please use bpf_program__section_name() instead")
स्थिर अक्षर *bpf_program__title(स्थिर काष्ठा bpf_program *prog, bool needs_copy);
LIBBPF_API bool bpf_program__स्वतःload(स्थिर काष्ठा bpf_program *prog);
LIBBPF_API पूर्णांक bpf_program__set_स्वतःload(काष्ठा bpf_program *prog, bool स्वतःload);

/* वापसs program size in bytes */
LIBBPF_API माप_प्रकार bpf_program__size(स्थिर काष्ठा bpf_program *prog);

LIBBPF_API पूर्णांक bpf_program__load(काष्ठा bpf_program *prog, अक्षर *license,
				 __u32 kern_version);
LIBBPF_API पूर्णांक bpf_program__fd(स्थिर काष्ठा bpf_program *prog);
LIBBPF_API पूर्णांक bpf_program__pin_instance(काष्ठा bpf_program *prog,
					 स्थिर अक्षर *path,
					 पूर्णांक instance);
LIBBPF_API पूर्णांक bpf_program__unpin_instance(काष्ठा bpf_program *prog,
					   स्थिर अक्षर *path,
					   पूर्णांक instance);
LIBBPF_API पूर्णांक bpf_program__pin(काष्ठा bpf_program *prog, स्थिर अक्षर *path);
LIBBPF_API पूर्णांक bpf_program__unpin(काष्ठा bpf_program *prog, स्थिर अक्षर *path);
LIBBPF_API व्योम bpf_program__unload(काष्ठा bpf_program *prog);

काष्ठा bpf_link;

LIBBPF_API काष्ठा bpf_link *bpf_link__खोलो(स्थिर अक्षर *path);
LIBBPF_API पूर्णांक bpf_link__fd(स्थिर काष्ठा bpf_link *link);
LIBBPF_API स्थिर अक्षर *bpf_link__pin_path(स्थिर काष्ठा bpf_link *link);
LIBBPF_API पूर्णांक bpf_link__pin(काष्ठा bpf_link *link, स्थिर अक्षर *path);
LIBBPF_API पूर्णांक bpf_link__unpin(काष्ठा bpf_link *link);
LIBBPF_API पूर्णांक bpf_link__update_program(काष्ठा bpf_link *link,
					काष्ठा bpf_program *prog);
LIBBPF_API व्योम bpf_link__disconnect(काष्ठा bpf_link *link);
LIBBPF_API पूर्णांक bpf_link__detach(काष्ठा bpf_link *link);
LIBBPF_API पूर्णांक bpf_link__destroy(काष्ठा bpf_link *link);

LIBBPF_API काष्ठा bpf_link *
bpf_program__attach(काष्ठा bpf_program *prog);
LIBBPF_API काष्ठा bpf_link *
bpf_program__attach_perf_event(काष्ठा bpf_program *prog, पूर्णांक pfd);
LIBBPF_API काष्ठा bpf_link *
bpf_program__attach_kprobe(काष्ठा bpf_program *prog, bool retprobe,
			   स्थिर अक्षर *func_name);
LIBBPF_API काष्ठा bpf_link *
bpf_program__attach_uprobe(काष्ठा bpf_program *prog, bool retprobe,
			   pid_t pid, स्थिर अक्षर *binary_path,
			   माप_प्रकार func_offset);
LIBBPF_API काष्ठा bpf_link *
bpf_program__attach_tracepoपूर्णांक(काष्ठा bpf_program *prog,
			       स्थिर अक्षर *tp_category,
			       स्थिर अक्षर *tp_name);
LIBBPF_API काष्ठा bpf_link *
bpf_program__attach_raw_tracepoपूर्णांक(काष्ठा bpf_program *prog,
				   स्थिर अक्षर *tp_name);
LIBBPF_API काष्ठा bpf_link *
bpf_program__attach_trace(काष्ठा bpf_program *prog);
LIBBPF_API काष्ठा bpf_link *
bpf_program__attach_lsm(काष्ठा bpf_program *prog);
LIBBPF_API काष्ठा bpf_link *
bpf_program__attach_cgroup(काष्ठा bpf_program *prog, पूर्णांक cgroup_fd);
LIBBPF_API काष्ठा bpf_link *
bpf_program__attach_netns(काष्ठा bpf_program *prog, पूर्णांक netns_fd);
LIBBPF_API काष्ठा bpf_link *
bpf_program__attach_xdp(काष्ठा bpf_program *prog, पूर्णांक अगरindex);
LIBBPF_API काष्ठा bpf_link *
bpf_program__attach_freplace(काष्ठा bpf_program *prog,
			     पूर्णांक target_fd, स्थिर अक्षर *attach_func_name);

काष्ठा bpf_map;

LIBBPF_API काष्ठा bpf_link *bpf_map__attach_काष्ठा_ops(काष्ठा bpf_map *map);

काष्ठा bpf_iter_attach_opts अणु
	माप_प्रकार sz; /* size of this काष्ठा क्रम क्रमward/backward compatibility */
	जोड़ bpf_iter_link_info *link_info;
	__u32 link_info_len;
पूर्ण;
#घोषणा bpf_iter_attach_opts__last_field link_info_len

LIBBPF_API काष्ठा bpf_link *
bpf_program__attach_iter(काष्ठा bpf_program *prog,
			 स्थिर काष्ठा bpf_iter_attach_opts *opts);

काष्ठा bpf_insn;

/*
 * Libbpf allows callers to adjust BPF programs beक्रमe being loaded
 * पूर्णांकo kernel. One program in an object file can be transक्रमmed पूर्णांकo
 * multiple variants to be attached to dअगरferent hooks.
 *
 * bpf_program_prep_t, bpf_program__set_prep and bpf_program__nth_fd
 * क्रमm an API क्रम this purpose.
 *
 * - bpf_program_prep_t:
 *   Defines a 'preprocessor', which is a caller defined function
 *   passed to libbpf through bpf_program__set_prep(), and will be
 *   called beक्रमe program is loaded. The processor should adjust
 *   the program one समय क्रम each instance according to the instance id
 *   passed to it.
 *
 * - bpf_program__set_prep:
 *   Attaches a preprocessor to a BPF program. The number of instances
 *   that should be created is also passed through this function.
 *
 * - bpf_program__nth_fd:
 *   After the program is loaded, get resulting FD of a given instance
 *   of the BPF program.
 *
 * If bpf_program__set_prep() is not used, the program would be loaded
 * without adjusपंचांगent during bpf_object__load(). The program has only
 * one instance. In this हाल bpf_program__fd(prog) is equal to
 * bpf_program__nth_fd(prog, 0).
 */

काष्ठा bpf_prog_prep_result अणु
	/*
	 * If not शून्य, load new inकाष्ठाion array.
	 * If set to शून्य, करोn't load this instance.
	 */
	काष्ठा bpf_insn *new_insn_ptr;
	पूर्णांक new_insn_cnt;

	/* If not शून्य, result FD is written to it. */
	पूर्णांक *pfd;
पूर्ण;

/*
 * Parameters of bpf_program_prep_t:
 *  - prog:	The bpf_program being loaded.
 *  - n:	Index of instance being generated.
 *  - insns:	BPF inकाष्ठाions array.
 *  - insns_cnt:Number of inकाष्ठाions in insns.
 *  - res:	Output parameter, result of transक्रमmation.
 *
 * Return value:
 *  - Zero:	pre-processing success.
 *  - Non-zero:	pre-processing error, stop loading.
 */
प्रकार पूर्णांक (*bpf_program_prep_t)(काष्ठा bpf_program *prog, पूर्णांक n,
				  काष्ठा bpf_insn *insns, पूर्णांक insns_cnt,
				  काष्ठा bpf_prog_prep_result *res);

LIBBPF_API पूर्णांक bpf_program__set_prep(काष्ठा bpf_program *prog, पूर्णांक nr_instance,
				     bpf_program_prep_t prep);

LIBBPF_API पूर्णांक bpf_program__nth_fd(स्थिर काष्ठा bpf_program *prog, पूर्णांक n);

/*
 * Adjust type of BPF program. Default is kprobe.
 */
LIBBPF_API पूर्णांक bpf_program__set_socket_filter(काष्ठा bpf_program *prog);
LIBBPF_API पूर्णांक bpf_program__set_tracepoपूर्णांक(काष्ठा bpf_program *prog);
LIBBPF_API पूर्णांक bpf_program__set_raw_tracepoपूर्णांक(काष्ठा bpf_program *prog);
LIBBPF_API पूर्णांक bpf_program__set_kprobe(काष्ठा bpf_program *prog);
LIBBPF_API पूर्णांक bpf_program__set_lsm(काष्ठा bpf_program *prog);
LIBBPF_API पूर्णांक bpf_program__set_sched_cls(काष्ठा bpf_program *prog);
LIBBPF_API पूर्णांक bpf_program__set_sched_act(काष्ठा bpf_program *prog);
LIBBPF_API पूर्णांक bpf_program__set_xdp(काष्ठा bpf_program *prog);
LIBBPF_API पूर्णांक bpf_program__set_perf_event(काष्ठा bpf_program *prog);
LIBBPF_API पूर्णांक bpf_program__set_tracing(काष्ठा bpf_program *prog);
LIBBPF_API पूर्णांक bpf_program__set_काष्ठा_ops(काष्ठा bpf_program *prog);
LIBBPF_API पूर्णांक bpf_program__set_extension(काष्ठा bpf_program *prog);
LIBBPF_API पूर्णांक bpf_program__set_sk_lookup(काष्ठा bpf_program *prog);

LIBBPF_API क्रमागत bpf_prog_type bpf_program__get_type(स्थिर काष्ठा bpf_program *prog);
LIBBPF_API व्योम bpf_program__set_type(काष्ठा bpf_program *prog,
				      क्रमागत bpf_prog_type type);

LIBBPF_API क्रमागत bpf_attach_type
bpf_program__get_expected_attach_type(स्थिर काष्ठा bpf_program *prog);
LIBBPF_API व्योम
bpf_program__set_expected_attach_type(काष्ठा bpf_program *prog,
				      क्रमागत bpf_attach_type type);

LIBBPF_API पूर्णांक
bpf_program__set_attach_target(काष्ठा bpf_program *prog, पूर्णांक attach_prog_fd,
			       स्थिर अक्षर *attach_func_name);

LIBBPF_API bool bpf_program__is_socket_filter(स्थिर काष्ठा bpf_program *prog);
LIBBPF_API bool bpf_program__is_tracepoपूर्णांक(स्थिर काष्ठा bpf_program *prog);
LIBBPF_API bool bpf_program__is_raw_tracepoपूर्णांक(स्थिर काष्ठा bpf_program *prog);
LIBBPF_API bool bpf_program__is_kprobe(स्थिर काष्ठा bpf_program *prog);
LIBBPF_API bool bpf_program__is_lsm(स्थिर काष्ठा bpf_program *prog);
LIBBPF_API bool bpf_program__is_sched_cls(स्थिर काष्ठा bpf_program *prog);
LIBBPF_API bool bpf_program__is_sched_act(स्थिर काष्ठा bpf_program *prog);
LIBBPF_API bool bpf_program__is_xdp(स्थिर काष्ठा bpf_program *prog);
LIBBPF_API bool bpf_program__is_perf_event(स्थिर काष्ठा bpf_program *prog);
LIBBPF_API bool bpf_program__is_tracing(स्थिर काष्ठा bpf_program *prog);
LIBBPF_API bool bpf_program__is_काष्ठा_ops(स्थिर काष्ठा bpf_program *prog);
LIBBPF_API bool bpf_program__is_extension(स्थिर काष्ठा bpf_program *prog);
LIBBPF_API bool bpf_program__is_sk_lookup(स्थिर काष्ठा bpf_program *prog);

/*
 * No need क्रम __attribute__((packed)), all members of 'bpf_map_def'
 * are all aligned.  In addition, using __attribute__((packed))
 * would trigger a -Wpacked warning message, and lead to an error
 * अगर -Werror is set.
 */
काष्ठा bpf_map_def अणु
	अचिन्हित पूर्णांक type;
	अचिन्हित पूर्णांक key_size;
	अचिन्हित पूर्णांक value_size;
	अचिन्हित पूर्णांक max_entries;
	अचिन्हित पूर्णांक map_flags;
पूर्ण;

/*
 * The 'struct bpf_map' in include/linux/bpf.h is पूर्णांकernal to the kernel,
 * so no need to worry about a name clash.
 */
LIBBPF_API काष्ठा bpf_map *
bpf_object__find_map_by_name(स्थिर काष्ठा bpf_object *obj, स्थिर अक्षर *name);

LIBBPF_API पूर्णांक
bpf_object__find_map_fd_by_name(स्थिर काष्ठा bpf_object *obj, स्थिर अक्षर *name);

/*
 * Get bpf_map through the offset of corresponding काष्ठा bpf_map_def
 * in the BPF object file.
 */
LIBBPF_API काष्ठा bpf_map *
bpf_object__find_map_by_offset(काष्ठा bpf_object *obj, माप_प्रकार offset);

LIBBPF_API काष्ठा bpf_map *
bpf_map__next(स्थिर काष्ठा bpf_map *map, स्थिर काष्ठा bpf_object *obj);
#घोषणा bpf_object__क्रम_each_map(pos, obj)		\
	क्रम ((pos) = bpf_map__next(शून्य, (obj));	\
	     (pos) != शून्य;				\
	     (pos) = bpf_map__next((pos), (obj)))
#घोषणा bpf_map__क्रम_each bpf_object__क्रम_each_map

LIBBPF_API काष्ठा bpf_map *
bpf_map__prev(स्थिर काष्ठा bpf_map *map, स्थिर काष्ठा bpf_object *obj);

/* get/set map FD */
LIBBPF_API पूर्णांक bpf_map__fd(स्थिर काष्ठा bpf_map *map);
LIBBPF_API पूर्णांक bpf_map__reuse_fd(काष्ठा bpf_map *map, पूर्णांक fd);
/* get map definition */
LIBBPF_API स्थिर काष्ठा bpf_map_def *bpf_map__def(स्थिर काष्ठा bpf_map *map);
/* get map name */
LIBBPF_API स्थिर अक्षर *bpf_map__name(स्थिर काष्ठा bpf_map *map);
/* get/set map type */
LIBBPF_API क्रमागत bpf_map_type bpf_map__type(स्थिर काष्ठा bpf_map *map);
LIBBPF_API पूर्णांक bpf_map__set_type(काष्ठा bpf_map *map, क्रमागत bpf_map_type type);
/* get/set map size (max_entries) */
LIBBPF_API __u32 bpf_map__max_entries(स्थिर काष्ठा bpf_map *map);
LIBBPF_API पूर्णांक bpf_map__set_max_entries(काष्ठा bpf_map *map, __u32 max_entries);
LIBBPF_API पूर्णांक bpf_map__resize(काष्ठा bpf_map *map, __u32 max_entries);
/* get/set map flags */
LIBBPF_API __u32 bpf_map__map_flags(स्थिर काष्ठा bpf_map *map);
LIBBPF_API पूर्णांक bpf_map__set_map_flags(काष्ठा bpf_map *map, __u32 flags);
/* get/set map NUMA node */
LIBBPF_API __u32 bpf_map__numa_node(स्थिर काष्ठा bpf_map *map);
LIBBPF_API पूर्णांक bpf_map__set_numa_node(काष्ठा bpf_map *map, __u32 numa_node);
/* get/set map key size */
LIBBPF_API __u32 bpf_map__key_size(स्थिर काष्ठा bpf_map *map);
LIBBPF_API पूर्णांक bpf_map__set_key_size(काष्ठा bpf_map *map, __u32 size);
/* get/set map value size */
LIBBPF_API __u32 bpf_map__value_size(स्थिर काष्ठा bpf_map *map);
LIBBPF_API पूर्णांक bpf_map__set_value_size(काष्ठा bpf_map *map, __u32 size);
/* get map key/value BTF type IDs */
LIBBPF_API __u32 bpf_map__btf_key_type_id(स्थिर काष्ठा bpf_map *map);
LIBBPF_API __u32 bpf_map__btf_value_type_id(स्थिर काष्ठा bpf_map *map);
/* get/set map अगर_index */
LIBBPF_API __u32 bpf_map__अगरindex(स्थिर काष्ठा bpf_map *map);
LIBBPF_API पूर्णांक bpf_map__set_अगरindex(काष्ठा bpf_map *map, __u32 अगरindex);

प्रकार व्योम (*bpf_map_clear_priv_t)(काष्ठा bpf_map *, व्योम *);
LIBBPF_API पूर्णांक bpf_map__set_priv(काष्ठा bpf_map *map, व्योम *priv,
				 bpf_map_clear_priv_t clear_priv);
LIBBPF_API व्योम *bpf_map__priv(स्थिर काष्ठा bpf_map *map);
LIBBPF_API पूर्णांक bpf_map__set_initial_value(काष्ठा bpf_map *map,
					  स्थिर व्योम *data, माप_प्रकार size);
LIBBPF_API bool bpf_map__is_offload_neutral(स्थिर काष्ठा bpf_map *map);
LIBBPF_API bool bpf_map__is_पूर्णांकernal(स्थिर काष्ठा bpf_map *map);
LIBBPF_API पूर्णांक bpf_map__set_pin_path(काष्ठा bpf_map *map, स्थिर अक्षर *path);
LIBBPF_API स्थिर अक्षर *bpf_map__get_pin_path(स्थिर काष्ठा bpf_map *map);
LIBBPF_API bool bpf_map__is_pinned(स्थिर काष्ठा bpf_map *map);
LIBBPF_API पूर्णांक bpf_map__pin(काष्ठा bpf_map *map, स्थिर अक्षर *path);
LIBBPF_API पूर्णांक bpf_map__unpin(काष्ठा bpf_map *map, स्थिर अक्षर *path);

LIBBPF_API पूर्णांक bpf_map__set_inner_map_fd(काष्ठा bpf_map *map, पूर्णांक fd);
LIBBPF_API काष्ठा bpf_map *bpf_map__inner_map(काष्ठा bpf_map *map);

LIBBPF_API दीर्घ libbpf_get_error(स्थिर व्योम *ptr);

काष्ठा bpf_prog_load_attr अणु
	स्थिर अक्षर *file;
	क्रमागत bpf_prog_type prog_type;
	क्रमागत bpf_attach_type expected_attach_type;
	पूर्णांक अगरindex;
	पूर्णांक log_level;
	पूर्णांक prog_flags;
पूर्ण;

LIBBPF_API पूर्णांक bpf_prog_load_xattr(स्थिर काष्ठा bpf_prog_load_attr *attr,
				   काष्ठा bpf_object **pobj, पूर्णांक *prog_fd);
LIBBPF_API पूर्णांक bpf_prog_load(स्थिर अक्षर *file, क्रमागत bpf_prog_type type,
			     काष्ठा bpf_object **pobj, पूर्णांक *prog_fd);

काष्ठा xdp_link_info अणु
	__u32 prog_id;
	__u32 drv_prog_id;
	__u32 hw_prog_id;
	__u32 skb_prog_id;
	__u8 attach_mode;
पूर्ण;

काष्ठा bpf_xdp_set_link_opts अणु
	माप_प्रकार sz;
	पूर्णांक old_fd;
	माप_प्रकार :0;
पूर्ण;
#घोषणा bpf_xdp_set_link_opts__last_field old_fd

LIBBPF_API पूर्णांक bpf_set_link_xdp_fd(पूर्णांक अगरindex, पूर्णांक fd, __u32 flags);
LIBBPF_API पूर्णांक bpf_set_link_xdp_fd_opts(पूर्णांक अगरindex, पूर्णांक fd, __u32 flags,
					स्थिर काष्ठा bpf_xdp_set_link_opts *opts);
LIBBPF_API पूर्णांक bpf_get_link_xdp_id(पूर्णांक अगरindex, __u32 *prog_id, __u32 flags);
LIBBPF_API पूर्णांक bpf_get_link_xdp_info(पूर्णांक अगरindex, काष्ठा xdp_link_info *info,
				     माप_प्रकार info_size, __u32 flags);

/* Ring buffer APIs */
काष्ठा ring_buffer;

प्रकार पूर्णांक (*ring_buffer_sample_fn)(व्योम *ctx, व्योम *data, माप_प्रकार size);

काष्ठा ring_buffer_opts अणु
	माप_प्रकार sz; /* size of this काष्ठा, क्रम क्रमward/backward compatiblity */
पूर्ण;

#घोषणा ring_buffer_opts__last_field sz

LIBBPF_API काष्ठा ring_buffer *
ring_buffer__new(पूर्णांक map_fd, ring_buffer_sample_fn sample_cb, व्योम *ctx,
		 स्थिर काष्ठा ring_buffer_opts *opts);
LIBBPF_API व्योम ring_buffer__मुक्त(काष्ठा ring_buffer *rb);
LIBBPF_API पूर्णांक ring_buffer__add(काष्ठा ring_buffer *rb, पूर्णांक map_fd,
				ring_buffer_sample_fn sample_cb, व्योम *ctx);
LIBBPF_API पूर्णांक ring_buffer__poll(काष्ठा ring_buffer *rb, पूर्णांक समयout_ms);
LIBBPF_API पूर्णांक ring_buffer__consume(काष्ठा ring_buffer *rb);
LIBBPF_API पूर्णांक ring_buffer__epoll_fd(स्थिर काष्ठा ring_buffer *rb);

/* Perf buffer APIs */
काष्ठा perf_buffer;

प्रकार व्योम (*perf_buffer_sample_fn)(व्योम *ctx, पूर्णांक cpu,
				      व्योम *data, __u32 size);
प्रकार व्योम (*perf_buffer_lost_fn)(व्योम *ctx, पूर्णांक cpu, __u64 cnt);

/* common use perf buffer options */
काष्ठा perf_buffer_opts अणु
	/* अगर specअगरied, sample_cb is called क्रम each sample */
	perf_buffer_sample_fn sample_cb;
	/* अगर specअगरied, lost_cb is called क्रम each batch of lost samples */
	perf_buffer_lost_fn lost_cb;
	/* ctx is provided to sample_cb and lost_cb */
	व्योम *ctx;
पूर्ण;

LIBBPF_API काष्ठा perf_buffer *
perf_buffer__new(पूर्णांक map_fd, माप_प्रकार page_cnt,
		 स्थिर काष्ठा perf_buffer_opts *opts);

क्रमागत bpf_perf_event_ret अणु
	LIBBPF_PERF_EVENT_DONE	= 0,
	LIBBPF_PERF_EVENT_ERROR	= -1,
	LIBBPF_PERF_EVENT_CONT	= -2,
पूर्ण;

काष्ठा perf_event_header;

प्रकार क्रमागत bpf_perf_event_ret
(*perf_buffer_event_fn)(व्योम *ctx, पूर्णांक cpu, काष्ठा perf_event_header *event);

/* raw perf buffer options, giving most घातer and control */
काष्ठा perf_buffer_raw_opts अणु
	/* perf event attrs passed directly पूर्णांकo perf_event_खोलो() */
	काष्ठा perf_event_attr *attr;
	/* raw event callback */
	perf_buffer_event_fn event_cb;
	/* ctx is provided to event_cb */
	व्योम *ctx;
	/* अगर cpu_cnt == 0, खोलो all on all possible CPUs (up to the number of
	 * max_entries of given PERF_EVENT_ARRAY map)
	 */
	पूर्णांक cpu_cnt;
	/* अगर cpu_cnt > 0, cpus is an array of CPUs to खोलो ring buffers on */
	पूर्णांक *cpus;
	/* अगर cpu_cnt > 0, map_keys specअगरy map keys to set per-CPU FDs क्रम */
	पूर्णांक *map_keys;
पूर्ण;

LIBBPF_API काष्ठा perf_buffer *
perf_buffer__new_raw(पूर्णांक map_fd, माप_प्रकार page_cnt,
		     स्थिर काष्ठा perf_buffer_raw_opts *opts);

LIBBPF_API व्योम perf_buffer__मुक्त(काष्ठा perf_buffer *pb);
LIBBPF_API पूर्णांक perf_buffer__epoll_fd(स्थिर काष्ठा perf_buffer *pb);
LIBBPF_API पूर्णांक perf_buffer__poll(काष्ठा perf_buffer *pb, पूर्णांक समयout_ms);
LIBBPF_API पूर्णांक perf_buffer__consume(काष्ठा perf_buffer *pb);
LIBBPF_API पूर्णांक perf_buffer__consume_buffer(काष्ठा perf_buffer *pb, माप_प्रकार buf_idx);
LIBBPF_API माप_प्रकार perf_buffer__buffer_cnt(स्थिर काष्ठा perf_buffer *pb);
LIBBPF_API पूर्णांक perf_buffer__buffer_fd(स्थिर काष्ठा perf_buffer *pb, माप_प्रकार buf_idx);

प्रकार क्रमागत bpf_perf_event_ret
	(*bpf_perf_event_prपूर्णांक_t)(काष्ठा perf_event_header *hdr,
				  व्योम *निजी_data);
LIBBPF_API क्रमागत bpf_perf_event_ret
bpf_perf_event_पढ़ो_simple(व्योम *mmap_mem, माप_प्रकार mmap_size, माप_प्रकार page_size,
			   व्योम **copy_mem, माप_प्रकार *copy_size,
			   bpf_perf_event_prपूर्णांक_t fn, व्योम *निजी_data);

काष्ठा bpf_prog_linfo;
काष्ठा bpf_prog_info;

LIBBPF_API व्योम bpf_prog_linfo__मुक्त(काष्ठा bpf_prog_linfo *prog_linfo);
LIBBPF_API काष्ठा bpf_prog_linfo *
bpf_prog_linfo__new(स्थिर काष्ठा bpf_prog_info *info);
LIBBPF_API स्थिर काष्ठा bpf_line_info *
bpf_prog_linfo__lfind_addr_func(स्थिर काष्ठा bpf_prog_linfo *prog_linfo,
				__u64 addr, __u32 func_idx, __u32 nr_skip);
LIBBPF_API स्थिर काष्ठा bpf_line_info *
bpf_prog_linfo__lfind(स्थिर काष्ठा bpf_prog_linfo *prog_linfo,
		      __u32 insn_off, __u32 nr_skip);

/*
 * Probe क्रम supported प्रणाली features
 *
 * Note that running many of these probes in a लघु amount of समय can cause
 * the kernel to reach the maximal size of lockable memory allowed क्रम the
 * user, causing subsequent probes to fail. In this हाल, the caller may want
 * to adjust that limit with setrlimit().
 */
LIBBPF_API bool bpf_probe_prog_type(क्रमागत bpf_prog_type prog_type,
				    __u32 अगरindex);
LIBBPF_API bool bpf_probe_map_type(क्रमागत bpf_map_type map_type, __u32 अगरindex);
LIBBPF_API bool bpf_probe_helper(क्रमागत bpf_func_id id,
				 क्रमागत bpf_prog_type prog_type, __u32 अगरindex);
LIBBPF_API bool bpf_probe_large_insn_limit(__u32 अगरindex);

/*
 * Get bpf_prog_info in continuous memory
 *
 * काष्ठा bpf_prog_info has multiple arrays. The user has option to choose
 * arrays to fetch from kernel. The following APIs provide an unअगरorm way to
 * fetch these data. All arrays in bpf_prog_info are stored in a single
 * continuous memory region. This makes it easy to store the info in a
 * file.
 *
 * Beक्रमe writing bpf_prog_info_linear to files, it is necessary to
 * translate poपूर्णांकers in bpf_prog_info to offsets. Helper functions
 * bpf_program__bpil_addr_to_offs() and bpf_program__bpil_offs_to_addr()
 * are पूर्णांकroduced to चयन between poपूर्णांकers and offsets.
 *
 * Examples:
 *   # To fetch map_ids and prog_tags:
 *   __u64 arrays = (1UL << BPF_PROG_INFO_MAP_IDS) |
 *           (1UL << BPF_PROG_INFO_PROG_TAGS);
 *   काष्ठा bpf_prog_info_linear *info_linear =
 *           bpf_program__get_prog_info_linear(fd, arrays);
 *
 *   # To save data in file
 *   bpf_program__bpil_addr_to_offs(info_linear);
 *   ग_लिखो(f, info_linear, माप(*info_linear) + info_linear->data_len);
 *
 *   # To पढ़ो data from file
 *   पढ़ो(f, info_linear, <proper_size>);
 *   bpf_program__bpil_offs_to_addr(info_linear);
 */
क्रमागत bpf_prog_info_array अणु
	BPF_PROG_INFO_FIRST_ARRAY = 0,
	BPF_PROG_INFO_JITED_INSNS = 0,
	BPF_PROG_INFO_XLATED_INSNS,
	BPF_PROG_INFO_MAP_IDS,
	BPF_PROG_INFO_JITED_KSYMS,
	BPF_PROG_INFO_JITED_FUNC_LENS,
	BPF_PROG_INFO_FUNC_INFO,
	BPF_PROG_INFO_LINE_INFO,
	BPF_PROG_INFO_JITED_LINE_INFO,
	BPF_PROG_INFO_PROG_TAGS,
	BPF_PROG_INFO_LAST_ARRAY,
पूर्ण;

काष्ठा bpf_prog_info_linear अणु
	/* size of काष्ठा bpf_prog_info, when the tool is compiled */
	__u32			info_len;
	/* total bytes allocated क्रम data, round up to 8 bytes */
	__u32			data_len;
	/* which arrays are included in data */
	__u64			arrays;
	काष्ठा bpf_prog_info	info;
	__u8			data[];
पूर्ण;

LIBBPF_API काष्ठा bpf_prog_info_linear *
bpf_program__get_prog_info_linear(पूर्णांक fd, __u64 arrays);

LIBBPF_API व्योम
bpf_program__bpil_addr_to_offs(काष्ठा bpf_prog_info_linear *info_linear);

LIBBPF_API व्योम
bpf_program__bpil_offs_to_addr(काष्ठा bpf_prog_info_linear *info_linear);

/*
 * A helper function to get the number of possible CPUs beक्रमe looking up
 * per-CPU maps. Negative त्रुटि_सं is वापसed on failure.
 *
 * Example usage:
 *
 *     पूर्णांक ncpus = libbpf_num_possible_cpus();
 *     अगर (ncpus < 0) अणु
 *          // error handling
 *     पूर्ण
 *     दीर्घ values[ncpus];
 *     bpf_map_lookup_elem(per_cpu_map_fd, key, values);
 *
 */
LIBBPF_API पूर्णांक libbpf_num_possible_cpus(व्योम);

काष्ठा bpf_map_skeleton अणु
	स्थिर अक्षर *name;
	काष्ठा bpf_map **map;
	व्योम **mmaped;
पूर्ण;

काष्ठा bpf_prog_skeleton अणु
	स्थिर अक्षर *name;
	काष्ठा bpf_program **prog;
	काष्ठा bpf_link **link;
पूर्ण;

काष्ठा bpf_object_skeleton अणु
	माप_प्रकार sz; /* size of this काष्ठा, क्रम क्रमward/backward compatibility */

	स्थिर अक्षर *name;
	व्योम *data;
	माप_प्रकार data_sz;

	काष्ठा bpf_object **obj;

	पूर्णांक map_cnt;
	पूर्णांक map_skel_sz; /* माप(काष्ठा bpf_skeleton_map) */
	काष्ठा bpf_map_skeleton *maps;

	पूर्णांक prog_cnt;
	पूर्णांक prog_skel_sz; /* माप(काष्ठा bpf_skeleton_prog) */
	काष्ठा bpf_prog_skeleton *progs;
पूर्ण;

LIBBPF_API पूर्णांक
bpf_object__खोलो_skeleton(काष्ठा bpf_object_skeleton *s,
			  स्थिर काष्ठा bpf_object_खोलो_opts *opts);
LIBBPF_API पूर्णांक bpf_object__load_skeleton(काष्ठा bpf_object_skeleton *s);
LIBBPF_API पूर्णांक bpf_object__attach_skeleton(काष्ठा bpf_object_skeleton *s);
LIBBPF_API व्योम bpf_object__detach_skeleton(काष्ठा bpf_object_skeleton *s);
LIBBPF_API व्योम bpf_object__destroy_skeleton(काष्ठा bpf_object_skeleton *s);

क्रमागत libbpf_tristate अणु
	TRI_NO = 0,
	TRI_YES = 1,
	TRI_MODULE = 2,
पूर्ण;

काष्ठा bpf_linker_opts अणु
	/* size of this काष्ठा, क्रम क्रमward/backward compatiblity */
	माप_प्रकार sz;
पूर्ण;
#घोषणा bpf_linker_opts__last_field sz

काष्ठा bpf_linker;

LIBBPF_API काष्ठा bpf_linker *bpf_linker__new(स्थिर अक्षर *filename, काष्ठा bpf_linker_opts *opts);
LIBBPF_API पूर्णांक bpf_linker__add_file(काष्ठा bpf_linker *linker, स्थिर अक्षर *filename);
LIBBPF_API पूर्णांक bpf_linker__finalize(काष्ठा bpf_linker *linker);
LIBBPF_API व्योम bpf_linker__मुक्त(काष्ठा bpf_linker *linker);

#अगर_घोषित __cplusplus
पूर्ण /* बाह्य "C" */
#पूर्ण_अगर

#पूर्ण_अगर /* __LIBBPF_LIBBPF_H */
