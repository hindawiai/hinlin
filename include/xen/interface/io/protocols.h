<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __XEN_PROTOCOLS_H__
#घोषणा __XEN_PROTOCOLS_H__

#घोषणा XEN_IO_PROTO_ABI_X86_32     "x86_32-abi"
#घोषणा XEN_IO_PROTO_ABI_X86_64     "x86_64-abi"
#घोषणा XEN_IO_PROTO_ABI_POWERPC64  "powerpc64-abi"
#घोषणा XEN_IO_PROTO_ABI_ARM        "arm-abi"

#अगर defined(__i386__)
# define XEN_IO_PROTO_ABI_NATIVE XEN_IO_PROTO_ABI_X86_32
#या_अगर defined(__x86_64__)
# define XEN_IO_PROTO_ABI_NATIVE XEN_IO_PROTO_ABI_X86_64
#या_अगर defined(__घातerpc64__)
# define XEN_IO_PROTO_ABI_NATIVE XEN_IO_PROTO_ABI_POWERPC64
#या_अगर defined(__arm__) || defined(__aarch64__)
# define XEN_IO_PROTO_ABI_NATIVE XEN_IO_PROTO_ABI_ARM
#अन्यथा
# error arch fixup needed here
#पूर्ण_अगर

#पूर्ण_अगर
