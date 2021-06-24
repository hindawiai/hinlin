<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright 2004-2007 Freescale Semiconductor, Inc. All Rights Reserved.
 * Copyright 2008 Juergen Beisert, kernel@pengutronix.de
 */

#अगर_अघोषित __ASM_ARCH_MXC_IIM_H__
#घोषणा __ASM_ARCH_MXC_IIM_H__

/* Register offsets */
#घोषणा MXC_IIMSTAT             0x0000
#घोषणा MXC_IIMSTATM            0x0004
#घोषणा MXC_IIMERR              0x0008
#घोषणा MXC_IIMEMASK            0x000C
#घोषणा MXC_IIMFCTL             0x0010
#घोषणा MXC_IIMUA               0x0014
#घोषणा MXC_IIMLA               0x0018
#घोषणा MXC_IIMSDAT             0x001C
#घोषणा MXC_IIMPREV             0x0020
#घोषणा MXC_IIMSREV             0x0024
#घोषणा MXC_IIMPRG_P            0x0028
#घोषणा MXC_IIMSCS0             0x002C
#घोषणा MXC_IIMSCS1             0x0030
#घोषणा MXC_IIMSCS2             0x0034
#घोषणा MXC_IIMSCS3             0x0038
#घोषणा MXC_IIMFBAC0            0x0800
#घोषणा MXC_IIMJAC              0x0804
#घोषणा MXC_IIMHWV1             0x0808
#घोषणा MXC_IIMHWV2             0x080C
#घोषणा MXC_IIMHAB0             0x0810
#घोषणा MXC_IIMHAB1             0x0814
/* Definitions क्रम i.MX27 TO2 */
#घोषणा MXC_IIMMAC              0x0814
#घोषणा MXC_IIMPREV_FUSE        0x0818
#घोषणा MXC_IIMSREV_FUSE        0x081C
#घोषणा MXC_IIMSJC_CHALL_0      0x0820
#घोषणा MXC_IIMSJC_CHALL_7      0x083C
#घोषणा MXC_IIMFB0UC17          0x0840
#घोषणा MXC_IIMFB0UC255         0x0BFC
#घोषणा MXC_IIMFBAC1            0x0C00
/* Definitions क्रम i.MX27 TO2 */
#घोषणा MXC_IIMSUID             0x0C04
#घोषणा MXC_IIMKEY0             0x0C04
#घोषणा MXC_IIMKEY20            0x0C54
#घोषणा MXC_IIMSJC_RESP_0       0x0C58
#घोषणा MXC_IIMSJC_RESP_7       0x0C74
#घोषणा MXC_IIMFB1UC30          0x0C78
#घोषणा MXC_IIMFB1UC255         0x0FFC

/* Bit definitions */

#घोषणा MXC_IIMHWV1_WLOCK               (0x1 << 7)
#घोषणा MXC_IIMHWV1_MCU_ENDIAN          (0x1 << 6)
#घोषणा MXC_IIMHWV1_DSP_ENDIAN          (0x1 << 5)
#घोषणा MXC_IIMHWV1_BOOT_INT            (0x1 << 4)
#घोषणा MXC_IIMHWV1_SCC_DISABLE         (0x1 << 3)
#घोषणा MXC_IIMHWV1_HANTRO_DISABLE      (0x1 << 2)
#घोषणा MXC_IIMHWV1_MEMSTICK_DIS        (0x1 << 1)

#घोषणा MXC_IIMHWV2_WLOCK               (0x1 << 7)
#घोषणा MXC_IIMHWV2_BP_SDMA             (0x1 << 6)
#घोषणा MXC_IIMHWV2_SCM_DCM             (0x1 << 5)

#पूर्ण_अगर /* __ASM_ARCH_MXC_IIM_H__ */
