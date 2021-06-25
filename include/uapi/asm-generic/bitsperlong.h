<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI__ASM_GENERIC_BITS_PER_LONG
#घोषणा _UAPI__ASM_GENERIC_BITS_PER_LONG

/*
 * There seems to be no way of detecting this स्वतःmatically from user
 * space, so 64 bit architectures should override this in their
 * bitsperदीर्घ.h. In particular, an architecture that supports
 * both 32 and 64 bit user space must not rely on CONFIG_64BIT
 * to decide it, but rather check a compiler provided macro.
 */
#अगर_अघोषित __BITS_PER_LONG
#घोषणा __BITS_PER_LONG 32
#पूर्ण_अगर

#पूर्ण_अगर /* _UAPI__ASM_GENERIC_BITS_PER_LONG */
