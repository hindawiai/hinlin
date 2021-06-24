<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2010 Broadcom Corporation
 */

#अगर_अघोषित	_BRCM_SOC_H
#घोषणा	_BRCM_SOC_H

#घोषणा SI_ENUM_BASE		0x18000000	/* Enumeration space base */

/* Common core control flags */
#घोषणा	SICF_BIST_EN		0x8000
#घोषणा	SICF_PME_EN		0x4000
#घोषणा	SICF_CORE_BITS		0x3ffc
#घोषणा	SICF_FGC		0x0002
#घोषणा	SICF_CLOCK_EN		0x0001

/* Common core status flags */
#घोषणा	SISF_BIST_DONE		0x8000
#घोषणा	SISF_BIST_ERROR		0x4000
#घोषणा	SISF_GATED_CLK		0x2000
#घोषणा	SISF_DMA64		0x1000
#घोषणा	SISF_CORE_BITS		0x0fff

#पूर्ण_अगर				/* _BRCM_SOC_H */
