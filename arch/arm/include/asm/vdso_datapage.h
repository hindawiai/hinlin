<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Adapted from arm64 version.
 *
 * Copyright (C) 2012 ARM Limited
 */
#अगर_अघोषित __ASM_VDSO_DATAPAGE_H
#घोषणा __ASM_VDSO_DATAPAGE_H

#अगर_घोषित __KERNEL__

#अगर_अघोषित __ASSEMBLY__

#समावेश <vdso/datapage.h>
#समावेश <यंत्र/page.h>

जोड़ vdso_data_store अणु
	काष्ठा vdso_data	data[CS_BASES];
	u8			page[PAGE_SIZE];
पूर्ण;

#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* __ASM_VDSO_DATAPAGE_H */
