<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <uapi/linux/unistd.h>
#समावेश <linux/kbuild.h>

#घोषणा SYSNR(_NR) DEFINE(SYS ## _NR, _NR)

व्योम syscall_defines(व्योम)
अणु
	COMMENT("Linux system call numbers.");
	SYSNR(__NR_ग_लिखो);
	SYSNR(__NR_पढ़ो);
#अगर_घोषित __NR_mmap2
	SYSNR(__NR_mmap2);
#पूर्ण_अगर
#अगर_घोषित __NR_mmap
	SYSNR(__NR_mmap);
#पूर्ण_अगर

पूर्ण
