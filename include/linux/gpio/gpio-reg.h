<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित GPIO_REG_H
#घोषणा GPIO_REG_H

काष्ठा device;
काष्ठा irq_करोमुख्य;

काष्ठा gpio_chip *gpio_reg_init(काष्ठा device *dev, व्योम __iomem *reg,
	पूर्णांक base, पूर्णांक num, स्थिर अक्षर *label, u32 direction, u32 def_out,
	स्थिर अक्षर *स्थिर *names, काष्ठा irq_करोमुख्य *irqकरोm, स्थिर पूर्णांक *irqs);

पूर्णांक gpio_reg_resume(काष्ठा gpio_chip *gc);

#पूर्ण_अगर /* GPIO_REG_H */
