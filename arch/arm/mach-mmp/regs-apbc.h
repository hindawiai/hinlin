<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *   Application Peripheral Bus Clock Unit
 */

#अगर_अघोषित __ASM_MACH_REGS_APBC_H
#घोषणा __ASM_MACH_REGS_APBC_H

#समावेश "addr-map.h"

/* Common APB घड़ी रेजिस्टर bit definitions */
#घोषणा APBC_APBCLK	(1 << 0)  /* APB Bus Clock Enable */
#घोषणा APBC_FNCLK	(1 << 1)  /* Functional Clock Enable */
#घोषणा APBC_RST	(1 << 2)  /* Reset Generation */

/* Functional Clock Selection Mask */
#घोषणा APBC_FNCLKSEL(x)	(((x) & 0xf) << 4)

#पूर्ण_अगर /* __ASM_MACH_REGS_APBC_H */
