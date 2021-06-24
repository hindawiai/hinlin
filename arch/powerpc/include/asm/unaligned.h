<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_UNALIGNED_H
#घोषणा _ASM_POWERPC_UNALIGNED_H

#अगर_घोषित __KERNEL__

/*
 * The PowerPC can करो unaligned accesses itself based on its endian mode.
 */
#समावेश <linux/unaligned/access_ok.h>
#समावेश <linux/unaligned/generic.h>

#अगर_घोषित __LITTLE_ENDIAN__
#घोषणा get_unaligned	__get_unaligned_le
#घोषणा put_unaligned	__put_unaligned_le
#अन्यथा
#घोषणा get_unaligned	__get_unaligned_be
#घोषणा put_unaligned	__put_unaligned_be
#पूर्ण_अगर

#पूर्ण_अगर	/* __KERNEL__ */
#पूर्ण_अगर	/* _ASM_POWERPC_UNALIGNED_H */
