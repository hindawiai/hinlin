<शैली गुरु>
/*
 * pm_wakeirq.h - Device wakeirq helper functions
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#अगर_अघोषित _LINUX_PM_WAKEIRQ_H
#घोषणा _LINUX_PM_WAKEIRQ_H

#अगर_घोषित CONFIG_PM

बाह्य पूर्णांक dev_pm_set_wake_irq(काष्ठा device *dev, पूर्णांक irq);
बाह्य पूर्णांक dev_pm_set_dedicated_wake_irq(काष्ठा device *dev,
					 पूर्णांक irq);
बाह्य व्योम dev_pm_clear_wake_irq(काष्ठा device *dev);
बाह्य व्योम dev_pm_enable_wake_irq(काष्ठा device *dev);
बाह्य व्योम dev_pm_disable_wake_irq(काष्ठा device *dev);

#अन्यथा	/* !CONFIG_PM */

अटल अंतरभूत पूर्णांक dev_pm_set_wake_irq(काष्ठा device *dev, पूर्णांक irq)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक dev_pm_set_dedicated_wake_irq(काष्ठा device *dev, पूर्णांक irq)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम dev_pm_clear_wake_irq(काष्ठा device *dev)
अणु
पूर्ण

अटल अंतरभूत व्योम dev_pm_enable_wake_irq(काष्ठा device *dev)
अणु
पूर्ण

अटल अंतरभूत व्योम dev_pm_disable_wake_irq(काष्ठा device *dev)
अणु
पूर्ण

#पूर्ण_अगर	/* CONFIG_PM */
#पूर्ण_अगर	/* _LINUX_PM_WAKEIRQ_H */
