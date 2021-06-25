<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _PERF_TRACE_BEAUTY_H
#घोषणा _PERF_TRACE_BEAUTY_H

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <sys/types.h>
#समावेश <stdbool.h>

काष्ठा strarray अणु
	u64	    offset;
	पूर्णांक	    nr_entries;
	स्थिर अक्षर *prefix;
	स्थिर अक्षर **entries;
पूर्ण;

#घोषणा DEFINE_STRARRAY(array, _prefix) काष्ठा strarray strarray__##array = अणु \
	.nr_entries = ARRAY_SIZE(array), \
	.entries = array, \
	.prefix = _prefix, \
पूर्ण

#घोषणा DEFINE_STRARRAY_OFFSET(array, _prefix, off) काष्ठा strarray strarray__##array = अणु \
	.offset	    = off, \
	.nr_entries = ARRAY_SIZE(array), \
	.entries = array, \
	.prefix = _prefix, \
पूर्ण

माप_प्रकार strarray__scnम_लिखो(काष्ठा strarray *sa, अक्षर *bf, माप_प्रकार size, स्थिर अक्षर *पूर्णांकfmt, bool show_prefix, पूर्णांक val);
माप_प्रकार strarray__scnम_लिखो_suffix(काष्ठा strarray *sa, अक्षर *bf, माप_प्रकार size, स्थिर अक्षर *पूर्णांकfmt, bool show_suffix, पूर्णांक val);
माप_प्रकार strarray__scnम_लिखो_flags(काष्ठा strarray *sa, अक्षर *bf, माप_प्रकार size, bool show_prefix, अचिन्हित दीर्घ flags);

bool strarray__म_से_अदीर्घ(काष्ठा strarray *sa, अक्षर *bf, माप_प्रकार size, u64 *ret);
bool strarray__म_से_अदीर्घ_flags(काष्ठा strarray *sa, अक्षर *bf, माप_प्रकार size, u64 *ret);

काष्ठा trace;
काष्ठा thपढ़ो;

काष्ठा file अणु
	अक्षर *pathname;
	पूर्णांक  dev_maj;
पूर्ण;

काष्ठा file *thपढ़ो__files_entry(काष्ठा thपढ़ो *thपढ़ो, पूर्णांक fd);

काष्ठा strarrays अणु
	पूर्णांक		nr_entries;
	काष्ठा strarray **entries;
पूर्ण;

#घोषणा DEFINE_STRARRAYS(array) काष्ठा strarrays strarrays__##array = अणु \
	.nr_entries = ARRAY_SIZE(array), \
	.entries = array, \
पूर्ण

माप_प्रकार strarrays__scnम_लिखो(काष्ठा strarrays *sas, अक्षर *bf, माप_प्रकार size, स्थिर अक्षर *पूर्णांकfmt, bool show_prefix, पूर्णांक val);

bool strarrays__म_से_अदीर्घ(काष्ठा strarrays *sas, अक्षर *bf, माप_प्रकार size, u64 *ret);

माप_प्रकार pid__scnम_लिखो_fd(काष्ठा trace *trace, pid_t pid, पूर्णांक fd, अक्षर *bf, माप_प्रकार size);

बाह्य काष्ठा strarray strarray__socket_families;

/**
 * augmented_arg: extra payload क्रम syscall poपूर्णांकer arguments
 
 * If perf_sample->raw_size is more than what a syscall sys_enter_FOO माला_दो,
 * then its the arguments contents, so that we can show more than just a
 * poपूर्णांकer. This will be करोne initially with eBPF, the start of that is at the
 * tools/perf/examples/bpf/augmented_syscalls.c example क्रम the खोलोat, but
 * will eventually be करोne स्वतःmagically caching the running kernel tracefs
 * events data पूर्णांकo an eBPF C script, that then माला_लो compiled and its .o file
 * cached क्रम subsequent use. For अक्षर poपूर्णांकers like the ones क्रम 'open' like
 * syscalls its easy, क्रम the rest we should use DWARF or better, BTF, much
 * more compact.
 *
 * @size: 8 अगर all we need is an पूर्णांकeger, otherwise all of the augmented arg.
 * @पूर्णांक_arg: will be used क्रम पूर्णांकeger like poपूर्णांकer contents, like 'accept's 'upeer_addrlen'
 * @value: u64 aligned, क्रम काष्ठाs, pathnames
 */
काष्ठा augmented_arg अणु
	पूर्णांक  size;
	पूर्णांक  पूर्णांक_arg;
	u64  value[];
पूर्ण;

काष्ठा syscall_arg_fmt;

/**
 * @val: value of syscall argument being क्रमmatted
 * @len: क्रम tracepoपूर्णांक dynamic arrays, अगर fmt->nr_entries == 0, then its not a fixed array, look at arg->len
 * @args: All the args, use syscall_args__val(arg, nth) to access one
 * @augmented_args: Extra data that can be collected, क्रम instance, with eBPF क्रम expanding the pathname क्रम खोलो, etc
 * @augmented_args_size: augmented_args total payload size
 * @thपढ़ो: tid state (maps, pid, tid, etc)
 * @trace: 'perf trace' पूर्णांकernals: all thपढ़ोs, etc
 * @parm: निजी area, may be an strarray, क्रम instance
 * @idx: syscall arg idx (is this the first?)
 * @mask: a syscall arg may mask another arg, see syscall_arg__scnम_लिखो_futex_op
 * @show_string_prefix: When there is a common prefix in a string table, show it or not
 */

काष्ठा syscall_arg अणु
	अचिन्हित दीर्घ val;
	अचिन्हित अक्षर *args;
	काष्ठा syscall_arg_fmt *fmt;
	काष्ठा अणु
		काष्ठा augmented_arg *args;
		पूर्णांक		     size;
	पूर्ण augmented;
	काष्ठा thपढ़ो *thपढ़ो;
	काष्ठा trace  *trace;
	व्योम	      *parm;
	u16	      len;
	u8	      idx;
	u8	      mask;
	bool	      show_string_prefix;
पूर्ण;

अचिन्हित दीर्घ syscall_arg__val(काष्ठा syscall_arg *arg, u8 idx);

माप_प्रकार syscall_arg__scnम_लिखो_strarray_flags(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg);
#घोषणा SCA_STRARRAY_FLAGS syscall_arg__scnम_लिखो_strarray_flags

bool syscall_arg__म_से_अदीर्घ_strarray(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg, u64 *ret);
#घोषणा STUL_STRARRAY syscall_arg__म_से_अदीर्घ_strarray

bool syscall_arg__म_से_अदीर्घ_strarray_flags(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg, u64 *ret);
#घोषणा STUL_STRARRAY_FLAGS syscall_arg__म_से_अदीर्घ_strarray_flags

bool syscall_arg__म_से_अदीर्घ_strarrays(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg, u64 *ret);
#घोषणा STUL_STRARRAYS syscall_arg__म_से_अदीर्घ_strarrays

माप_प्रकार syscall_arg__scnम_लिखो_x86_irq_vectors(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg);
#घोषणा SCA_X86_IRQ_VECTORS syscall_arg__scnम_लिखो_x86_irq_vectors

bool syscall_arg__म_से_अदीर्घ_x86_irq_vectors(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg, u64 *ret);
#घोषणा STUL_X86_IRQ_VECTORS syscall_arg__म_से_अदीर्घ_x86_irq_vectors

माप_प्रकार syscall_arg__scnम_लिखो_x86_MSR(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg);
#घोषणा SCA_X86_MSR syscall_arg__scnम_लिखो_x86_MSR

bool syscall_arg__म_से_अदीर्घ_x86_MSR(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg, u64 *ret);
#घोषणा STUL_X86_MSR syscall_arg__म_से_अदीर्घ_x86_MSR

माप_प्रकार syscall_arg__scnम_लिखो_strarrays(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg);
#घोषणा SCA_STRARRAYS syscall_arg__scnम_लिखो_strarrays

माप_प्रकार syscall_arg__scnम_लिखो_fd(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg);
#घोषणा SCA_FD syscall_arg__scnम_लिखो_fd

माप_प्रकार syscall_arg__scnम_लिखो_hex(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg);
#घोषणा SCA_HEX syscall_arg__scnम_लिखो_hex

माप_प्रकार syscall_arg__scnम_लिखो_ptr(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg);
#घोषणा SCA_PTR syscall_arg__scnम_लिखो_ptr

माप_प्रकार syscall_arg__scnम_लिखो_पूर्णांक(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg);
#घोषणा SCA_INT syscall_arg__scnम_लिखो_पूर्णांक

माप_प्रकार syscall_arg__scnम_लिखो_दीर्घ(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg);
#घोषणा SCA_LONG syscall_arg__scnम_लिखो_दीर्घ

माप_प्रकार syscall_arg__scnम_लिखो_pid(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg);
#घोषणा SCA_PID syscall_arg__scnम_लिखो_pid

माप_प्रकार syscall_arg__scnम_लिखो_clone_flags(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg);
#घोषणा SCA_CLONE_FLAGS syscall_arg__scnम_लिखो_clone_flags

माप_प्रकार syscall_arg__scnम_लिखो_fcntl_cmd(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg);
#घोषणा SCA_FCNTL_CMD syscall_arg__scnम_लिखो_fcntl_cmd

माप_प्रकार syscall_arg__scnम_लिखो_fcntl_arg(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg);
#घोषणा SCA_FCNTL_ARG syscall_arg__scnम_लिखो_fcntl_arg

माप_प्रकार syscall_arg__scnम_लिखो_flock(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg);
#घोषणा SCA_FLOCK syscall_arg__scnम_लिखो_flock

माप_प्रकार syscall_arg__scnम_लिखो_fsmount_attr_flags(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg);
#घोषणा SCA_FSMOUNT_ATTR_FLAGS syscall_arg__scnम_लिखो_fsmount_attr_flags

माप_प्रकार syscall_arg__scnम_लिखो_fspick_flags(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg);
#घोषणा SCA_FSPICK_FLAGS syscall_arg__scnम_लिखो_fspick_flags

माप_प्रकार syscall_arg__scnम_लिखो_ioctl_cmd(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg);
#घोषणा SCA_IOCTL_CMD syscall_arg__scnम_लिखो_ioctl_cmd

माप_प्रकार syscall_arg__scnम_लिखो_kcmp_type(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg);
#घोषणा SCA_KCMP_TYPE syscall_arg__scnम_लिखो_kcmp_type

माप_प्रकार syscall_arg__scnम_लिखो_kcmp_idx(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg);
#घोषणा SCA_KCMP_IDX syscall_arg__scnम_लिखो_kcmp_idx

अचिन्हित दीर्घ syscall_arg__mask_val_mount_flags(काष्ठा syscall_arg *arg, अचिन्हित दीर्घ flags);
#घोषणा SCAMV_MOUNT_FLAGS syscall_arg__mask_val_mount_flags

माप_प्रकार syscall_arg__scnम_लिखो_mount_flags(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg);
#घोषणा SCA_MOUNT_FLAGS syscall_arg__scnम_लिखो_mount_flags

माप_प्रकार syscall_arg__scnम_लिखो_move_mount_flags(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg);
#घोषणा SCA_MOVE_MOUNT_FLAGS syscall_arg__scnम_लिखो_move_mount_flags

माप_प्रकार syscall_arg__scnम_लिखो_pkey_alloc_access_rights(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg);
#घोषणा SCA_PKEY_ALLOC_ACCESS_RIGHTS syscall_arg__scnम_लिखो_pkey_alloc_access_rights

माप_प्रकार syscall_arg__scnम_लिखो_खोलो_flags(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg);
#घोषणा SCA_OPEN_FLAGS syscall_arg__scnम_लिखो_खोलो_flags

माप_प्रकार syscall_arg__scnम_लिखो_x86_arch_prctl_code(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg);
#घोषणा SCA_X86_ARCH_PRCTL_CODE syscall_arg__scnम_लिखो_x86_arch_prctl_code

माप_प्रकार syscall_arg__scnम_लिखो_prctl_option(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg);
#घोषणा SCA_PRCTL_OPTION syscall_arg__scnम_लिखो_prctl_option

बाह्य काष्ठा strarray strarray__prctl_options;

माप_प्रकार syscall_arg__scnम_लिखो_prctl_arg2(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg);
#घोषणा SCA_PRCTL_ARG2 syscall_arg__scnम_लिखो_prctl_arg2

माप_प्रकार syscall_arg__scnम_लिखो_prctl_arg3(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg);
#घोषणा SCA_PRCTL_ARG3 syscall_arg__scnम_लिखो_prctl_arg3

माप_प्रकार syscall_arg__scnम_लिखो_नामat2_flags(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg);
#घोषणा SCA_RENAMEAT2_FLAGS syscall_arg__scnम_लिखो_नामat2_flags

माप_प्रकार syscall_arg__scnम_लिखो_sockaddr(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg);
#घोषणा SCA_SOCKADDR syscall_arg__scnम_लिखो_sockaddr

माप_प्रकार syscall_arg__scnम_लिखो_socket_protocol(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg);
#घोषणा SCA_SK_PROTO syscall_arg__scnम_लिखो_socket_protocol

माप_प्रकार syscall_arg__scnम_लिखो_statx_flags(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg);
#घोषणा SCA_STATX_FLAGS syscall_arg__scnम_लिखो_statx_flags

माप_प्रकार syscall_arg__scnम_लिखो_statx_mask(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg);
#घोषणा SCA_STATX_MASK syscall_arg__scnम_लिखो_statx_mask

माप_प्रकार syscall_arg__scnम_लिखो_sync_file_range_flags(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg);
#घोषणा SCA_SYNC_खाता_RANGE_FLAGS syscall_arg__scnम_लिखो_sync_file_range_flags

माप_प्रकार खोलो__scnम_लिखो_flags(अचिन्हित दीर्घ flags, अक्षर *bf, माप_प्रकार size, bool show_prefix);

व्योम syscall_arg__set_ret_scnम_लिखो(काष्ठा syscall_arg *arg,
				    माप_प्रकार (*ret_scnम_लिखो)(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg));

स्थिर अक्षर *arch_syscalls__strत्रुटि_सं(स्थिर अक्षर *arch, पूर्णांक err);

#पूर्ण_अगर /* _PERF_TRACE_BEAUTY_H */
