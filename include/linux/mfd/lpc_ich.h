<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  linux/drivers/mfd/lpc_ich.h
 *
 *  Copyright (c) 2012 Extreme Engineering Solution, Inc.
 *  Author: Aaron Sierra <asierra@xes-inc.com>
 */
#अगर_अघोषित LPC_ICH_H
#घोषणा LPC_ICH_H

#समावेश <linux/platक्रमm_data/x86/पूर्णांकel-spi.h>

/* GPIO resources */
#घोषणा ICH_RES_GPIO	0
#घोषणा ICH_RES_GPE0	1

/* GPIO compatibility */
क्रमागत अणु
	ICH_I3100_GPIO,
	ICH_V5_GPIO,
	ICH_V6_GPIO,
	ICH_V7_GPIO,
	ICH_V9_GPIO,
	ICH_V10CORP_GPIO,
	ICH_V10CONS_GPIO,
	AVOTON_GPIO,
पूर्ण;

काष्ठा lpc_ich_info अणु
	अक्षर name[32];
	अचिन्हित पूर्णांक iTCO_version;
	अचिन्हित पूर्णांक gpio_version;
	क्रमागत पूर्णांकel_spi_type spi_type;
	u8 use_gpio;
पूर्ण;

#पूर्ण_अगर
