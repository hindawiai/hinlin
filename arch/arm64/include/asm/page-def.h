<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Based on arch/arm/include/यंत्र/page.h
 *
 * Copyright (C) 1995-2003 Russell King
 * Copyright (C) 2017 ARM Ltd.
 */
#अगर_अघोषित __ASM_PAGE_DEF_H
#घोषणा __ASM_PAGE_DEF_H

#समावेश <linux/स्थिर.h>

/* PAGE_SHIFT determines the page size */
#घोषणा PAGE_SHIFT		CONFIG_ARM64_PAGE_SHIFT
#घोषणा PAGE_SIZE		(_AC(1, UL) << PAGE_SHIFT)
#घोषणा PAGE_MASK		(~(PAGE_SIZE-1))

#पूर्ण_अगर /* __ASM_PAGE_DEF_H */
