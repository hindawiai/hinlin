<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __ASM_GENERIC_MMAN_H
#घोषणा __ASM_GENERIC_MMAN_H

#समावेश <यंत्र-generic/mman-common-tools.h>

#घोषणा MAP_GROWSDOWN	0x0100		/* stack-like segment */
#घोषणा MAP_DENYWRITE	0x0800		/* ETXTBSY */
#घोषणा MAP_EXECUTABLE	0x1000		/* mark it as an executable */
#घोषणा MAP_LOCKED	0x2000		/* pages are locked */
#घोषणा MAP_NORESERVE	0x4000		/* करोn't check क्रम reservations */

/*
 * Bits [26:31] are reserved, see यंत्र-generic/hugetlb_encode.h
 * क्रम MAP_HUGETLB usage
 */

#घोषणा MCL_CURRENT	1		/* lock all current mappings */
#घोषणा MCL_FUTURE	2		/* lock all future mappings */
#घोषणा MCL_ONFAULT	4		/* lock all pages that are faulted in */

#पूर्ण_अगर /* __ASM_GENERIC_MMAN_H */
