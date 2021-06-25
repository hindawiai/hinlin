<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * bpf-script-test-kbuild.c
 * Test include from kernel header
 */
#अगर_अघोषित LINUX_VERSION_CODE
# error Need LINUX_VERSION_CODE
# error Example: क्रम 4.2 kernel, put 'clang-opt="-DLINUX_VERSION_CODE=0x40200" into llvm section of ~/.perfconfig'
#पूर्ण_अगर
#घोषणा SEC(NAME) __attribute__((section(NAME), used))

#समावेश <uapi/linux/fs.h>

SEC("func=vfs_llseek")
पूर्णांक bpf_func__vfs_llseek(व्योम *ctx)
अणु
	वापस 0;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
पूर्णांक _version SEC("version") = LINUX_VERSION_CODE;
