<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Interrupt support क्रम Cirrus Logic Madera codecs
 *
 * Copyright (C) 2016-2018 Cirrus Logic, Inc. and
 *                         Cirrus Logic International Semiconductor Ltd.
 */

#अगर_अघोषित IRQCHIP_MADERA_H
#घोषणा IRQCHIP_MADERA_H

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/madera/core.h>

#घोषणा MADERA_IRQ_FLL1_LOCK		0
#घोषणा MADERA_IRQ_FLL2_LOCK		1
#घोषणा MADERA_IRQ_FLL3_LOCK		2
#घोषणा MADERA_IRQ_FLLAO_LOCK		3
#घोषणा MADERA_IRQ_CLK_SYS_ERR		4
#घोषणा MADERA_IRQ_CLK_ASYNC_ERR	5
#घोषणा MADERA_IRQ_CLK_DSP_ERR		6
#घोषणा MADERA_IRQ_HPDET		7
#घोषणा MADERA_IRQ_MICDET1		8
#घोषणा MADERA_IRQ_MICDET2		9
#घोषणा MADERA_IRQ_JD1_RISE		10
#घोषणा MADERA_IRQ_JD1_FALL		11
#घोषणा MADERA_IRQ_JD2_RISE		12
#घोषणा MADERA_IRQ_JD2_FALL		13
#घोषणा MADERA_IRQ_MICD_CLAMP_RISE	14
#घोषणा MADERA_IRQ_MICD_CLAMP_FALL	15
#घोषणा MADERA_IRQ_DRC2_SIG_DET		16
#घोषणा MADERA_IRQ_DRC1_SIG_DET		17
#घोषणा MADERA_IRQ_ASRC1_IN1_LOCK	18
#घोषणा MADERA_IRQ_ASRC1_IN2_LOCK	19
#घोषणा MADERA_IRQ_ASRC2_IN1_LOCK	20
#घोषणा MADERA_IRQ_ASRC2_IN2_LOCK	21
#घोषणा MADERA_IRQ_DSP_IRQ1		22
#घोषणा MADERA_IRQ_DSP_IRQ2		23
#घोषणा MADERA_IRQ_DSP_IRQ3		24
#घोषणा MADERA_IRQ_DSP_IRQ4		25
#घोषणा MADERA_IRQ_DSP_IRQ5		26
#घोषणा MADERA_IRQ_DSP_IRQ6		27
#घोषणा MADERA_IRQ_DSP_IRQ7		28
#घोषणा MADERA_IRQ_DSP_IRQ8		29
#घोषणा MADERA_IRQ_DSP_IRQ9		30
#घोषणा MADERA_IRQ_DSP_IRQ10		31
#घोषणा MADERA_IRQ_DSP_IRQ11		32
#घोषणा MADERA_IRQ_DSP_IRQ12		33
#घोषणा MADERA_IRQ_DSP_IRQ13		34
#घोषणा MADERA_IRQ_DSP_IRQ14		35
#घोषणा MADERA_IRQ_DSP_IRQ15		36
#घोषणा MADERA_IRQ_DSP_IRQ16		37
#घोषणा MADERA_IRQ_HP1L_SC		38
#घोषणा MADERA_IRQ_HP1R_SC		39
#घोषणा MADERA_IRQ_HP2L_SC		40
#घोषणा MADERA_IRQ_HP2R_SC		41
#घोषणा MADERA_IRQ_HP3L_SC		42
#घोषणा MADERA_IRQ_HP3R_SC		43
#घोषणा MADERA_IRQ_SPKOUTL_SC		44
#घोषणा MADERA_IRQ_SPKOUTR_SC		45
#घोषणा MADERA_IRQ_HP1L_ENABLE_DONE	46
#घोषणा MADERA_IRQ_HP1R_ENABLE_DONE	47
#घोषणा MADERA_IRQ_HP2L_ENABLE_DONE	48
#घोषणा MADERA_IRQ_HP2R_ENABLE_DONE	49
#घोषणा MADERA_IRQ_HP3L_ENABLE_DONE	50
#घोषणा MADERA_IRQ_HP3R_ENABLE_DONE	51
#घोषणा MADERA_IRQ_SPKOUTL_ENABLE_DONE	52
#घोषणा MADERA_IRQ_SPKOUTR_ENABLE_DONE	53
#घोषणा MADERA_IRQ_SPK_SHUTDOWN		54
#घोषणा MADERA_IRQ_SPK_OVERHEAT		55
#घोषणा MADERA_IRQ_SPK_OVERHEAT_WARN	56
#घोषणा MADERA_IRQ_GPIO1		57
#घोषणा MADERA_IRQ_GPIO2		58
#घोषणा MADERA_IRQ_GPIO3		59
#घोषणा MADERA_IRQ_GPIO4		60
#घोषणा MADERA_IRQ_GPIO5		61
#घोषणा MADERA_IRQ_GPIO6		62
#घोषणा MADERA_IRQ_GPIO7		63
#घोषणा MADERA_IRQ_GPIO8		64
#घोषणा MADERA_IRQ_DSP1_BUS_ERR		65
#घोषणा MADERA_IRQ_DSP2_BUS_ERR		66
#घोषणा MADERA_IRQ_DSP3_BUS_ERR		67
#घोषणा MADERA_IRQ_DSP4_BUS_ERR		68
#घोषणा MADERA_IRQ_DSP5_BUS_ERR		69
#घोषणा MADERA_IRQ_DSP6_BUS_ERR		70
#घोषणा MADERA_IRQ_DSP7_BUS_ERR		71

#घोषणा MADERA_NUM_IRQ			72

/*
 * These wrapper functions are क्रम use by other child drivers of the
 * same parent MFD.
 */
अटल अंतरभूत पूर्णांक madera_get_irq_mapping(काष्ठा madera *madera, पूर्णांक irq)
अणु
	अगर (!madera->irq_dev)
		वापस -ENODEV;

	वापस regmap_irq_get_virq(madera->irq_data, irq);
पूर्ण

अटल अंतरभूत पूर्णांक madera_request_irq(काष्ठा madera *madera, पूर्णांक irq,
				     स्थिर अक्षर *name,
				     irq_handler_t handler, व्योम *data)
अणु
	irq = madera_get_irq_mapping(madera, irq);
	अगर (irq < 0)
		वापस irq;

	वापस request_thपढ़ोed_irq(irq, शून्य, handler, IRQF_ONESHOT, name,
				    data);
पूर्ण

अटल अंतरभूत व्योम madera_मुक्त_irq(काष्ठा madera *madera, पूर्णांक irq, व्योम *data)
अणु
	irq = madera_get_irq_mapping(madera, irq);
	अगर (irq < 0)
		वापस;

	मुक्त_irq(irq, data);
पूर्ण

अटल अंतरभूत पूर्णांक madera_set_irq_wake(काष्ठा madera *madera, पूर्णांक irq, पूर्णांक on)
अणु
	irq = madera_get_irq_mapping(madera, irq);
	अगर (irq < 0)
		वापस irq;

	वापस irq_set_irq_wake(irq, on);
पूर्ण

#पूर्ण_अगर
