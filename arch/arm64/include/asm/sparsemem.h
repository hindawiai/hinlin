<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 ARM Ltd.
 */
#अगर_अघोषित __ASM_SPARSEMEM_H
#घोषणा __ASM_SPARSEMEM_H

#घोषणा MAX_PHYSMEM_BITS	CONFIG_ARM64_PA_BITS

/*
 * Section size must be at least 512MB क्रम 64K base
 * page size config. Otherwise it will be less than
 * (MAX_ORDER - 1) and the build process will fail.
 */
#अगर_घोषित CONFIG_ARM64_64K_PAGES
#घोषणा SECTION_SIZE_BITS 29

#अन्यथा

/*
 * Section size must be at least 128MB क्रम 4K base
 * page size config. Otherwise PMD based huge page
 * entries could not be created क्रम vmemmap mappings.
 * 16K follows 4K क्रम simplicity.
 */
#घोषणा SECTION_SIZE_BITS 27
#पूर्ण_अगर /* CONFIG_ARM64_64K_PAGES */

#पूर्ण_अगर
