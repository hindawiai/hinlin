<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2012, NVIDIA CORPORATION.  All rights reserved.
 */

#अगर_अघोषित __MACH_TEGRA_IRAMMAP_H
#घोषणा __MACH_TEGRA_IRAMMAP_H

#समावेश <linux/sizes.h>

/* The first 1K of IRAM is permanently reserved क्रम the CPU reset handler */
#घोषणा TEGRA_IRAM_RESET_HANDLER_OFFSET	0
#घोषणा TEGRA_IRAM_RESET_HANDLER_SIZE	SZ_1K

/*
 * This area is used क्रम LPx resume vector, only जबतक LPx घातer state is
 * active. At other बार, the AVP may use this area क्रम arbitrary purposes
 */
#घोषणा TEGRA_IRAM_LPx_RESUME_AREA	(TEGRA_IRAM_BASE + SZ_4K)

#पूर्ण_अगर
