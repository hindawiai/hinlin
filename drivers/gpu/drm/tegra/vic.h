<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2015, NVIDIA Corporation.
 */

#अगर_अघोषित TEGRA_VIC_H
#घोषणा TEGRA_VIC_H

/* VIC methods */

#घोषणा VIC_SET_APPLICATION_ID			0x00000200
#घोषणा VIC_SET_FCE_UCODE_SIZE			0x0000071C
#घोषणा VIC_SET_FCE_UCODE_OFFSET		0x0000072C

/* VIC रेजिस्टरs */

#घोषणा VIC_THI_STREAMID0	0x00000030
#घोषणा VIC_THI_STREAMID1	0x00000034

#घोषणा NV_PVIC_MISC_PRI_VIC_CG			0x000016d0
#घोषणा CG_IDLE_CG_DLY_CNT(val)			((val & 0x3f) << 0)
#घोषणा CG_IDLE_CG_EN				(1 << 6)
#घोषणा CG_WAKEUP_DLY_CNT(val)			((val & 0xf) << 16)

#घोषणा VIC_TFBIF_TRANSCFG	0x00002044
#घोषणा  TRANSCFG_ATT(i, v)	(((v) & 0x3) << (i * 4))
#घोषणा  TRANSCFG_SID_HW	0
#घोषणा  TRANSCFG_SID_PHY	1
#घोषणा  TRANSCFG_SID_FALCON	2

/* Firmware offsets */

#घोषणा VIC_UCODE_FCE_HEADER_OFFSET		(6*4)
#घोषणा VIC_UCODE_FCE_DATA_OFFSET		(7*4)
#घोषणा FCE_UCODE_SIZE_OFFSET			(2*4)

#पूर्ण_अगर /* TEGRA_VIC_H */
