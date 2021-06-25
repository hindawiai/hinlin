<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2018-2019 Intel Corporation
 * Copyright (C) 2012 Freescale Semiconductor, Inc.
 * Copyright (C) 2012 Linaro Ltd.
 */

#अगर_अघोषित __LINUX_MFD_ALTERA_SYSMGR_H__
#घोषणा __LINUX_MFD_ALTERA_SYSMGR_H__

#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/firmware/पूर्णांकel/stratix10-smc.h>

काष्ठा device_node;

#अगर_घोषित CONFIG_MFD_ALTERA_SYSMGR
काष्ठा regmap *altr_sysmgr_regmap_lookup_by_phandle(काष्ठा device_node *np,
						    स्थिर अक्षर *property);
#अन्यथा
अटल अंतरभूत काष्ठा regmap *
altr_sysmgr_regmap_lookup_by_phandle(काष्ठा device_node *np,
				     स्थिर अक्षर *property)
अणु
	वापस ERR_PTR(-ENOTSUPP);
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __LINUX_MFD_ALTERA_SYSMGR_H__ */
