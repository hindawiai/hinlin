<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) 2012-2019 ARM Limited (or its affiliates). */

/* \पile cc_pm.h
 */

#अगर_अघोषित __CC_POWER_MGR_H__
#घोषणा __CC_POWER_MGR_H__

#समावेश "cc_driver.h"

#घोषणा CC_SUSPEND_TIMEOUT 3000

#अगर defined(CONFIG_PM)

बाह्य स्थिर काष्ठा dev_pm_ops ccree_pm;

पूर्णांक cc_pm_get(काष्ठा device *dev);
व्योम cc_pm_put_suspend(काष्ठा device *dev);

#अन्यथा

अटल अंतरभूत पूर्णांक cc_pm_get(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम cc_pm_put_suspend(काष्ठा device *dev) अणुपूर्ण

#पूर्ण_अगर

#पूर्ण_अगर /*__POWER_MGR_H__*/
