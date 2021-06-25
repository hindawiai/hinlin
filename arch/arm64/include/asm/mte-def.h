<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2020 ARM Ltd.
 */
#अगर_अघोषित __ASM_MTE_DEF_H
#घोषणा __ASM_MTE_DEF_H

#घोषणा MTE_GRANULE_SIZE	UL(16)
#घोषणा MTE_GRANULE_MASK	(~(MTE_GRANULE_SIZE - 1))
#घोषणा MTE_TAG_SHIFT		56
#घोषणा MTE_TAG_SIZE		4
#घोषणा MTE_TAG_MASK		GENMASK((MTE_TAG_SHIFT + (MTE_TAG_SIZE - 1)), MTE_TAG_SHIFT)

#घोषणा __MTE_PREAMBLE		ARM64_ASM_PREAMBLE ".arch_extension memtag\n"

#पूर्ण_अगर /* __ASM_MTE_DEF_H  */
