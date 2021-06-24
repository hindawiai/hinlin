<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2018 Arm Limited. All rights reserved.
 *
 * Author: Suzuki K Poulose <suzuki.poulose@arm.com>
 */

#अगर_अघोषित _CORESIGHT_CATU_H
#घोषणा _CORESIGHT_CATU_H

#समावेश "coresight-priv.h"

/* Register offset from base */
#घोषणा CATU_CONTROL		0x000
#घोषणा CATU_MODE		0x004
#घोषणा CATU_AXICTRL		0x008
#घोषणा CATU_IRQEN		0x00c
#घोषणा CATU_SLADDRLO		0x020
#घोषणा CATU_SLADDRHI		0x024
#घोषणा CATU_INADDRLO		0x028
#घोषणा CATU_INADDRHI		0x02c
#घोषणा CATU_STATUS		0x100
#घोषणा CATU_DEVARCH		0xfbc

#घोषणा CATU_CONTROL_ENABLE	0

#घोषणा CATU_MODE_PASS_THROUGH	0U
#घोषणा CATU_MODE_TRANSLATE	1U

#घोषणा CATU_AXICTRL_ARCACHE_SHIFT	4
#घोषणा CATU_AXICTRL_ARCACHE_MASK	0xf
#घोषणा CATU_AXICTRL_ARPROT_MASK	0x3
#घोषणा CATU_AXICTRL_ARCACHE(arcache)		\
	(((arcache) & CATU_AXICTRL_ARCACHE_MASK) << CATU_AXICTRL_ARCACHE_SHIFT)

#घोषणा CATU_AXICTRL_VAL(arcache, arprot)	\
	(CATU_AXICTRL_ARCACHE(arcache) | ((arprot) & CATU_AXICTRL_ARPROT_MASK))

#घोषणा AXI3_AxCACHE_WB_READ_ALLOC	0x7
/*
 * AXI - ARPROT bits:
 * See AMBA AXI & ACE Protocol specअगरication (ARM IHI 0022E)
 * sectionA4.7 Access Permissions.
 *
 * Bit 0: 0 - Unprivileged access, 1 - Privileged access
 * Bit 1: 0 - Secure access, 1 - Non-secure access.
 * Bit 2: 0 - Data access, 1 - inकाष्ठाion access.
 *
 * CATU AXICTRL:ARPROT[2] is res0 as we always access data.
 */
#घोषणा CATU_OS_ARPROT			0x2

#घोषणा CATU_OS_AXICTRL		\
	CATU_AXICTRL_VAL(AXI3_AxCACHE_WB_READ_ALLOC, CATU_OS_ARPROT)

#घोषणा CATU_STATUS_READY	8
#घोषणा CATU_STATUS_ADRERR	0
#घोषणा CATU_STATUS_AXIERR	4

#घोषणा CATU_IRQEN_ON		0x1
#घोषणा CATU_IRQEN_OFF		0x0

काष्ठा catu_drvdata अणु
	व्योम __iomem *base;
	काष्ठा coresight_device *csdev;
	पूर्णांक irq;
पूर्ण;

#घोषणा CATU_REG32(name, offset)					\
अटल अंतरभूत u32							\
catu_पढ़ो_##name(काष्ठा catu_drvdata *drvdata)				\
अणु									\
	वापस coresight_पढ़ो_reg_pair(drvdata->base, offset, -1);	\
पूर्ण									\
अटल अंतरभूत व्योम							\
catu_ग_लिखो_##name(काष्ठा catu_drvdata *drvdata, u32 val)		\
अणु									\
	coresight_ग_लिखो_reg_pair(drvdata->base, val, offset, -1);	\
पूर्ण

#घोषणा CATU_REG_PAIR(name, lo_off, hi_off)				\
अटल अंतरभूत u64							\
catu_पढ़ो_##name(काष्ठा catu_drvdata *drvdata)				\
अणु									\
	वापस coresight_पढ़ो_reg_pair(drvdata->base, lo_off, hi_off);	\
पूर्ण									\
अटल अंतरभूत व्योम							\
catu_ग_लिखो_##name(काष्ठा catu_drvdata *drvdata, u64 val)		\
अणु									\
	coresight_ग_लिखो_reg_pair(drvdata->base, val, lo_off, hi_off);	\
पूर्ण

CATU_REG32(control, CATU_CONTROL);
CATU_REG32(mode, CATU_MODE);
CATU_REG32(irqen, CATU_IRQEN);
CATU_REG32(axictrl, CATU_AXICTRL);
CATU_REG_PAIR(sladdr, CATU_SLADDRLO, CATU_SLADDRHI)
CATU_REG_PAIR(inaddr, CATU_INADDRLO, CATU_INADDRHI)

अटल अंतरभूत bool coresight_is_catu_device(काष्ठा coresight_device *csdev)
अणु
	अगर (!IS_ENABLED(CONFIG_CORESIGHT_CATU))
		वापस false;
	अगर (csdev->type != CORESIGHT_DEV_TYPE_HELPER)
		वापस false;
	अगर (csdev->subtype.helper_subtype != CORESIGHT_DEV_SUBTYPE_HELPER_CATU)
		वापस false;
	वापस true;
पूर्ण

#पूर्ण_अगर
