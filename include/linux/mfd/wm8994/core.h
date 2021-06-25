<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * include/linux/mfd/wm8994/core.h -- Core पूर्णांकerface क्रम WM8994
 *
 * Copyright 2009 Wolfson Microelectronics PLC.
 *
 * Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 */

#अगर_अघोषित __MFD_WM8994_CORE_H__
#घोषणा __MFD_WM8994_CORE_H__

#समावेश <linux/mutex.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/regmap.h>

#समावेश <linux/mfd/wm8994/pdata.h>

क्रमागत wm8994_type अणु
	WM8994 = 0,
	WM8958 = 1,
	WM1811 = 2,
पूर्ण;

काष्ठा regulator_dev;
काष्ठा regulator_bulk_data;
काष्ठा irq_करोमुख्य;

#घोषणा WM8994_NUM_GPIO_REGS 11
#घोषणा WM8994_NUM_LDO_REGS   2
#घोषणा WM8994_NUM_IRQ_REGS   2

#घोषणा WM8994_IRQ_TEMP_SHUT		0
#घोषणा WM8994_IRQ_MIC1_DET		1
#घोषणा WM8994_IRQ_MIC1_SHRT		2
#घोषणा WM8994_IRQ_MIC2_DET		3
#घोषणा WM8994_IRQ_MIC2_SHRT		4
#घोषणा WM8994_IRQ_FLL1_LOCK		5
#घोषणा WM8994_IRQ_FLL2_LOCK		6
#घोषणा WM8994_IRQ_SRC1_LOCK		7
#घोषणा WM8994_IRQ_SRC2_LOCK		8
#घोषणा WM8994_IRQ_AIF1DRC1_SIG_DET	9
#घोषणा WM8994_IRQ_AIF1DRC2_SIG_DET	10
#घोषणा WM8994_IRQ_AIF2DRC_SIG_DET	11
#घोषणा WM8994_IRQ_FIFOS_ERR		12
#घोषणा WM8994_IRQ_WSEQ_DONE		13
#घोषणा WM8994_IRQ_DCS_DONE		14
#घोषणा WM8994_IRQ_TEMP_WARN		15

/* GPIOs in the chip are numbered from 1-11 */
#घोषणा WM8994_IRQ_GPIO(x) (x + WM8994_IRQ_TEMP_WARN)

काष्ठा wm8994 अणु
	काष्ठा wm8994_pdata pdata;

	क्रमागत wm8994_type type;
	पूर्णांक revision;
	पूर्णांक cust_id;

	काष्ठा device *dev;
	काष्ठा regmap *regmap;

	bool lकरो_ena_always_driven;

	पूर्णांक gpio_base;
	पूर्णांक irq_base;

	पूर्णांक irq;
	काष्ठा regmap_irq_chip_data *irq_data;
	काष्ठा irq_करोमुख्य *edge_irq;

	/* Used over suspend/resume */
	bool suspended;

	काष्ठा regulator_dev *dbvdd;
	पूर्णांक num_supplies;
	काष्ठा regulator_bulk_data *supplies;
पूर्ण;

/* Device I/O API */

अटल अंतरभूत पूर्णांक wm8994_reg_पढ़ो(काष्ठा wm8994 *wm8994, अचिन्हित लघु reg)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(wm8994->regmap, reg, &val);

	अगर (ret < 0)
		वापस ret;
	अन्यथा
		वापस val;
पूर्ण

अटल अंतरभूत पूर्णांक wm8994_reg_ग_लिखो(काष्ठा wm8994 *wm8994, अचिन्हित लघु reg,
				   अचिन्हित लघु val)
अणु
	वापस regmap_ग_लिखो(wm8994->regmap, reg, val);
पूर्ण

अटल अंतरभूत पूर्णांक wm8994_bulk_पढ़ो(काष्ठा wm8994 *wm8994, अचिन्हित लघु reg,
				   पूर्णांक count, u16 *buf)
अणु
	वापस regmap_bulk_पढ़ो(wm8994->regmap, reg, buf, count);
पूर्ण

अटल अंतरभूत पूर्णांक wm8994_bulk_ग_लिखो(काष्ठा wm8994 *wm8994, अचिन्हित लघु reg,
				    पूर्णांक count, स्थिर u16 *buf)
अणु
	वापस regmap_raw_ग_लिखो(wm8994->regmap, reg, buf, count * माप(u16));
पूर्ण

अटल अंतरभूत पूर्णांक wm8994_set_bits(काष्ठा wm8994 *wm8994, अचिन्हित लघु reg,
		    अचिन्हित लघु mask, अचिन्हित लघु val)
अणु
	वापस regmap_update_bits(wm8994->regmap, reg, mask, val);
पूर्ण

/* Helper to save on boilerplate */
अटल अंतरभूत पूर्णांक wm8994_request_irq(काष्ठा wm8994 *wm8994, पूर्णांक irq,
				     irq_handler_t handler, स्थिर अक्षर *name,
				     व्योम *data)
अणु
	अगर (!wm8994->irq_data)
		वापस -EINVAL;
	वापस request_thपढ़ोed_irq(regmap_irq_get_virq(wm8994->irq_data, irq),
				    शून्य, handler, IRQF_TRIGGER_RISING, name,
				    data);
पूर्ण
अटल अंतरभूत व्योम wm8994_मुक्त_irq(काष्ठा wm8994 *wm8994, पूर्णांक irq, व्योम *data)
अणु
	अगर (!wm8994->irq_data)
		वापस;
	मुक्त_irq(regmap_irq_get_virq(wm8994->irq_data, irq), data);
पूर्ण

पूर्णांक wm8994_irq_init(काष्ठा wm8994 *wm8994);
व्योम wm8994_irq_निकास(काष्ठा wm8994 *wm8994);

#पूर्ण_अगर
