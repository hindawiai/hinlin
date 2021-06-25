<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * bpf-script-test-prologue.c
 * Test BPF prologue
 */
#अगर_अघोषित LINUX_VERSION_CODE
# error Need LINUX_VERSION_CODE
# error Example: क्रम 4.2 kernel, put 'clang-opt="-DLINUX_VERSION_CODE=0x40200" into llvm section of ~/.perfconfig'
#पूर्ण_अगर
#घोषणा SEC(NAME) __attribute__((section(NAME), used))

#समावेश <uapi/linux/fs.h>

/*
 * If CONFIG_PROखाता_ALL_BRANCHES is selected,
 * 'if' is redefined after include kernel header.
 * Recover 'if' क्रम BPF object code.
 */
#अगर_घोषित अगर
# undef अगर
#पूर्ण_अगर

#घोषणा FMODE_READ		0x1
#घोषणा FMODE_WRITE		0x2

अटल व्योम (*bpf_trace_prपूर्णांकk)(स्थिर अक्षर *fmt, पूर्णांक fmt_size, ...) =
	(व्योम *) 6;

SEC("func=null_lseek file->f_mode offset orig")
पूर्णांक bpf_func__null_lseek(व्योम *ctx, पूर्णांक err, अचिन्हित दीर्घ _f_mode,
			 अचिन्हित दीर्घ offset, अचिन्हित दीर्घ orig)
अणु
	भ_शेषe_t f_mode = (भ_शेषe_t)_f_mode;

	अगर (err)
		वापस 0;
	अगर (f_mode & FMODE_WRITE)
		वापस 0;
	अगर (offset & 1)
		वापस 0;
	अगर (orig == प्रस्तुत_से)
		वापस 0;
	वापस 1;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
पूर्णांक _version SEC("version") = LINUX_VERSION_CODE;
