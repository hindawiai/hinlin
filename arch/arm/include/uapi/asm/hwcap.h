<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI__ASMARM_HWCAP_H
#घोषणा _UAPI__ASMARM_HWCAP_H

/*
 * HWCAP flags - क्रम elf_hwcap (in kernel) and AT_HWCAP
 */
#घोषणा HWCAP_SWP	(1 << 0)
#घोषणा HWCAP_HALF	(1 << 1)
#घोषणा HWCAP_THUMB	(1 << 2)
#घोषणा HWCAP_26BIT	(1 << 3)	/* Play it safe */
#घोषणा HWCAP_FAST_MULT	(1 << 4)
#घोषणा HWCAP_FPA	(1 << 5)
#घोषणा HWCAP_VFP	(1 << 6)
#घोषणा HWCAP_EDSP	(1 << 7)
#घोषणा HWCAP_JAVA	(1 << 8)
#घोषणा HWCAP_IWMMXT	(1 << 9)
#घोषणा HWCAP_CRUNCH	(1 << 10)
#घोषणा HWCAP_THUMBEE	(1 << 11)
#घोषणा HWCAP_NEON	(1 << 12)
#घोषणा HWCAP_VFPv3	(1 << 13)
#घोषणा HWCAP_VFPv3D16	(1 << 14)	/* also set क्रम VFPv4-D16 */
#घोषणा HWCAP_TLS	(1 << 15)
#घोषणा HWCAP_VFPv4	(1 << 16)
#घोषणा HWCAP_IDIVA	(1 << 17)
#घोषणा HWCAP_IDIVT	(1 << 18)
#घोषणा HWCAP_VFPD32	(1 << 19)	/* set अगर VFP has 32 regs (not 16) */
#घोषणा HWCAP_IDIV	(HWCAP_IDIVA | HWCAP_IDIVT)
#घोषणा HWCAP_LPAE	(1 << 20)
#घोषणा HWCAP_EVTSTRM	(1 << 21)

/*
 * HWCAP2 flags - क्रम elf_hwcap2 (in kernel) and AT_HWCAP2
 */
#घोषणा HWCAP2_AES	(1 << 0)
#घोषणा HWCAP2_PMULL	(1 << 1)
#घोषणा HWCAP2_SHA1	(1 << 2)
#घोषणा HWCAP2_SHA2	(1 << 3)
#घोषणा HWCAP2_CRC32	(1 << 4)

#पूर्ण_अगर /* _UAPI__ASMARM_HWCAP_H */
