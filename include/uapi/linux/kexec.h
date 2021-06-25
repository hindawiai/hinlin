<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPILINUX_KEXEC_H
#घोषणा _UAPILINUX_KEXEC_H

/* kexec प्रणाली call -  It loads the new kernel to boot पूर्णांकo.
 * kexec करोes not sync, or unmount fileप्रणालीs so अगर you need
 * that to happen you need to करो that yourself.
 */

#समावेश <linux/types.h>

/* kexec flags क्रम dअगरferent usage scenarios */
#घोषणा KEXEC_ON_CRASH		0x00000001
#घोषणा KEXEC_PRESERVE_CONTEXT	0x00000002
#घोषणा KEXEC_ARCH_MASK		0xffff0000

/*
 * Kexec file load पूर्णांकerface flags.
 * KEXEC_खाता_UNLOAD : Unload alपढ़ोy loaded kexec/kdump image.
 * KEXEC_खाता_ON_CRASH : Load/unload operation beदीर्घs to kdump image.
 * KEXEC_खाता_NO_INITRAMFS : No initramfs is being loaded. Ignore the initrd
 *                           fd field.
 */
#घोषणा KEXEC_खाता_UNLOAD	0x00000001
#घोषणा KEXEC_खाता_ON_CRASH	0x00000002
#घोषणा KEXEC_खाता_NO_INITRAMFS	0x00000004

/* These values match the ELF architecture values.
 * Unless there is a good reason that should जारी to be the हाल.
 */
#घोषणा KEXEC_ARCH_DEFAULT ( 0 << 16)
#घोषणा KEXEC_ARCH_386     ( 3 << 16)
#घोषणा KEXEC_ARCH_68K     ( 4 << 16)
#घोषणा KEXEC_ARCH_PARISC  (15 << 16)
#घोषणा KEXEC_ARCH_X86_64  (62 << 16)
#घोषणा KEXEC_ARCH_PPC     (20 << 16)
#घोषणा KEXEC_ARCH_PPC64   (21 << 16)
#घोषणा KEXEC_ARCH_IA_64   (50 << 16)
#घोषणा KEXEC_ARCH_ARM     (40 << 16)
#घोषणा KEXEC_ARCH_S390    (22 << 16)
#घोषणा KEXEC_ARCH_SH      (42 << 16)
#घोषणा KEXEC_ARCH_MIPS_LE (10 << 16)
#घोषणा KEXEC_ARCH_MIPS    ( 8 << 16)
#घोषणा KEXEC_ARCH_AARCH64 (183 << 16)
#घोषणा KEXEC_ARCH_RISCV   (243 << 16)

/* The artअगरicial cap on the number of segments passed to kexec_load. */
#घोषणा KEXEC_SEGMENT_MAX 16

#अगर_अघोषित __KERNEL__
/*
 * This काष्ठाure is used to hold the arguments that are used when
 * loading  kernel binaries.
 */
काष्ठा kexec_segment अणु
	स्थिर व्योम *buf;
	माप_प्रकार bufsz;
	स्थिर व्योम *mem;
	माप_प्रकार memsz;
पूर्ण;

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* _UAPILINUX_KEXEC_H */
