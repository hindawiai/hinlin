<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2008 Michal Simek <monstr@monstr.eu>
 * Copyright (C) 2006 Aपंचांगark Techno, Inc.
 */

#अगर_अघोषित _ASM_MICROBLAZE_UNALIGNED_H
#घोषणा _ASM_MICROBLAZE_UNALIGNED_H

# अगरdef __KERNEL__

#  अगरdef __MICROBLAZEEL__
#   include <linux/unaligned/le_काष्ठा.h>
#   include <linux/unaligned/be_byteshअगरt.h>
#   define get_unaligned	__get_unaligned_le
#   define put_unaligned	__put_unaligned_le
#  अन्यथा
#   include <linux/unaligned/be_काष्ठा.h>
#   include <linux/unaligned/le_byteshअगरt.h>
#   define get_unaligned	__get_unaligned_be
#   define put_unaligned	__put_unaligned_be
#  endअगर

# include <linux/unaligned/generic.h>

# endअगर	/* __KERNEL__ */
#पूर्ण_अगर /* _ASM_MICROBLAZE_UNALIGNED_H */
