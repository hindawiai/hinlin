<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _ASMARM_STATFS_H
#घोषणा _ASMARM_STATFS_H

/*
 * With EABI there is 4 bytes of padding added to this काष्ठाure.
 * Let's pack it so the padding goes away to simplअगरy dual ABI support.
 * Note that user space करोes NOT have to pack this काष्ठाure.
 */
#घोषणा ARCH_PACK_STATFS64 __attribute__((packed,aligned(4)))

#समावेश <यंत्र-generic/statfs.h>
#पूर्ण_अगर
