<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *
 * Copyright (C) 2010 John Crispin <john@phrozen.org>
 */

#अगर_अघोषित _LTQ_FALCON_H__
#घोषणा _LTQ_FALCON_H__

#अगर_घोषित CONFIG_SOC_FALCON

#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <lantiq.h>

/* Chip IDs */
#घोषणा SOC_ID_FALCON		0x01B8

/* SoC Types */
#घोषणा SOC_TYPE_FALCON		0x01

/*
 * during early_prपूर्णांकk no ioremap possible at this early stage
 * let's use KSEG1 instead
 */
#घोषणा LTQ_ASC0_BASE_ADDR	0x1E100C00
#घोषणा LTQ_EARLY_ASC		KSEG1ADDR(LTQ_ASC0_BASE_ADDR)

/* WDT */
#घोषणा LTQ_RST_CAUSE_WDTRST	0x0002

/* CHIP ID */
#घोषणा LTQ_STATUS_BASE_ADDR	0x1E802000

#घोषणा FALCON_CHIPID		((u32 *)(KSEG1 + LTQ_STATUS_BASE_ADDR + 0x0c))
#घोषणा FALCON_CHIPTYPE		((u32 *)(KSEG1 + LTQ_STATUS_BASE_ADDR + 0x38))
#घोषणा FALCON_CHIPCONF		((u32 *)(KSEG1 + LTQ_STATUS_BASE_ADDR + 0x40))

/* SYSCTL - start/stop/restart/configure/... dअगरferent parts of the Soc */
#घोषणा SYSCTL_SYS1		0
#घोषणा SYSCTL_SYSETH		1
#घोषणा SYSCTL_SYSGPE		2

/* BOOT_SEL - find what boot media we have */
#घोषणा BS_FLASH		0x1
#घोषणा BS_SPI			0x4

/* global रेजिस्टर ranges */
बाह्य __iomem व्योम *ltq_ebu_membase;
बाह्य __iomem व्योम *ltq_sys1_membase;
#घोषणा ltq_ebu_w32(x, y)	ltq_w32((x), ltq_ebu_membase + (y))
#घोषणा ltq_ebu_r32(x)		ltq_r32(ltq_ebu_membase + (x))

#घोषणा ltq_sys1_w32(x, y)	ltq_w32((x), ltq_sys1_membase + (y))
#घोषणा ltq_sys1_r32(x)		ltq_r32(ltq_sys1_membase + (x))
#घोषणा ltq_sys1_w32_mask(clear, set, reg)   \
	ltq_sys1_w32((ltq_sys1_r32(reg) & ~(clear)) | (set), reg)

/* allow the gpio and pinctrl drivers to talk to eachother */
बाह्य पूर्णांक pinctrl_falcon_get_range_size(पूर्णांक id);
बाह्य व्योम pinctrl_falcon_add_gpio_range(काष्ठा pinctrl_gpio_range *range);

/*
 * to keep the irq code generic we need to define this to 0 as falcon
 * has no EIU/EBU
 */
#घोषणा LTQ_EBU_PCC_ISTAT	0

#पूर्ण_अगर /* CONFIG_SOC_FALCON */
#पूर्ण_अगर /* _LTQ_XWAY_H__ */
