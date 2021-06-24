<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __HWMON_ADT7X10_H__
#घोषणा __HWMON_ADT7X10_H__

#समावेश <linux/types.h>
#समावेश <linux/pm.h>

/* ADT7410 रेजिस्टरs definition */
#घोषणा ADT7X10_TEMPERATURE		0
#घोषणा ADT7X10_STATUS			2
#घोषणा ADT7X10_CONFIG			3
#घोषणा ADT7X10_T_ALARM_HIGH		4
#घोषणा ADT7X10_T_ALARM_LOW		6
#घोषणा ADT7X10_T_CRIT			8
#घोषणा ADT7X10_T_HYST			0xA
#घोषणा ADT7X10_ID			0xB

काष्ठा device;

काष्ठा adt7x10_ops अणु
	पूर्णांक (*पढ़ो_byte)(काष्ठा device *, u8 reg);
	पूर्णांक (*ग_लिखो_byte)(काष्ठा device *, u8 reg, u8 data);
	पूर्णांक (*पढ़ो_word)(काष्ठा device *, u8 reg);
	पूर्णांक (*ग_लिखो_word)(काष्ठा device *, u8 reg, u16 data);
पूर्ण;

पूर्णांक adt7x10_probe(काष्ठा device *dev, स्थिर अक्षर *name, पूर्णांक irq,
	स्थिर काष्ठा adt7x10_ops *ops);
पूर्णांक adt7x10_हटाओ(काष्ठा device *dev, पूर्णांक irq);

#अगर_घोषित CONFIG_PM_SLEEP
बाह्य स्थिर काष्ठा dev_pm_ops adt7x10_dev_pm_ops;
#घोषणा ADT7X10_DEV_PM_OPS (&adt7x10_dev_pm_ops)
#अन्यथा
#घोषणा ADT7X10_DEV_PM_OPS शून्य
#पूर्ण_अगर

#पूर्ण_अगर
