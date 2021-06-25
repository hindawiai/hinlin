<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) 2019 Arm Ltd. */

#अगर_अघोषित __ASM_PVCLOCK_ABI_H
#घोषणा __ASM_PVCLOCK_ABI_H

/* The below काष्ठाure is defined in ARM DEN0057A */

काष्ठा pvघड़ी_vcpu_stolen_समय अणु
	__le32 revision;
	__le32 attributes;
	__le64 stolen_समय;
	/* Structure must be 64 byte aligned, pad to that size */
	u8 padding[48];
पूर्ण __packed;

#पूर्ण_अगर
