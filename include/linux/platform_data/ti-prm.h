<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * TI PRM (Power & Reset Manager) platक्रमm data
 *
 * Copyright (C) 2019 Texas Instruments, Inc.
 *
 * Tero Kristo <t-kristo@ti.com>
 */

#अगर_अघोषित _LINUX_PLATFORM_DATA_TI_PRM_H
#घोषणा _LINUX_PLATFORM_DATA_TI_PRM_H

काष्ठा घड़ीकरोमुख्य;

काष्ठा ti_prm_platक्रमm_data अणु
	व्योम (*clkdm_deny_idle)(काष्ठा घड़ीकरोमुख्य *clkdm);
	व्योम (*clkdm_allow_idle)(काष्ठा घड़ीकरोमुख्य *clkdm);
	काष्ठा घड़ीकरोमुख्य * (*clkdm_lookup)(स्थिर अक्षर *name);
पूर्ण;

#पूर्ण_अगर /* _LINUX_PLATFORM_DATA_TI_PRM_H */
