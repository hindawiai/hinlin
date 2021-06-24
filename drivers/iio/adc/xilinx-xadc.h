<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Xilinx XADC driver
 *
 * Copyright 2013 Analog Devices Inc.
 *  Author: Lars-Peter Clausen <lars@metafoo.de>
 */

#अगर_अघोषित __IIO_XILINX_XADC__
#घोषणा __IIO_XILINX_XADC__

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mutex.h>
#समावेश <linux/spinlock.h>

काष्ठा iio_dev;
काष्ठा clk;
काष्ठा xadc_ops;
काष्ठा platक्रमm_device;

व्योम xadc_handle_events(काष्ठा iio_dev *indio_dev, अचिन्हित दीर्घ events);

पूर्णांक xadc_पढ़ो_event_config(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan, क्रमागत iio_event_type type,
	क्रमागत iio_event_direction dir);
पूर्णांक xadc_ग_लिखो_event_config(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan, क्रमागत iio_event_type type,
	क्रमागत iio_event_direction dir, पूर्णांक state);
पूर्णांक xadc_पढ़ो_event_value(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan, क्रमागत iio_event_type type,
	क्रमागत iio_event_direction dir, क्रमागत iio_event_info info,
	पूर्णांक *val, पूर्णांक *val2);
पूर्णांक xadc_ग_लिखो_event_value(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan, क्रमागत iio_event_type type,
	क्रमागत iio_event_direction dir, क्रमागत iio_event_info info,
	पूर्णांक val, पूर्णांक val2);

क्रमागत xadc_बाह्यal_mux_mode अणु
	XADC_EXTERNAL_MUX_NONE,
	XADC_EXTERNAL_MUX_SINGLE,
	XADC_EXTERNAL_MUX_DUAL,
पूर्ण;

काष्ठा xadc अणु
	व्योम __iomem *base;
	काष्ठा clk *clk;

	स्थिर काष्ठा xadc_ops *ops;

	uपूर्णांक16_t threshold[16];
	uपूर्णांक16_t temp_hysteresis;
	अचिन्हित पूर्णांक alarm_mask;

	uपूर्णांक16_t *data;

	काष्ठा iio_trigger *trigger;
	काष्ठा iio_trigger *convst_trigger;
	काष्ठा iio_trigger *samplerate_trigger;

	क्रमागत xadc_बाह्यal_mux_mode बाह्यal_mux_mode;

	अचिन्हित पूर्णांक zynq_masked_alarm;
	अचिन्हित पूर्णांक zynq_पूर्णांकmask;
	काष्ठा delayed_work zynq_unmask_work;

	काष्ठा mutex mutex;
	spinlock_t lock;

	काष्ठा completion completion;
	पूर्णांक irq;
पूर्ण;

क्रमागत xadc_type अणु
	XADC_TYPE_S7, /* Series 7 */
	XADC_TYPE_US, /* UltraScale and UltraScale+ */
पूर्ण;

काष्ठा xadc_ops अणु
	पूर्णांक (*पढ़ो)(काष्ठा xadc *xadc, अचिन्हित पूर्णांक reg, uपूर्णांक16_t *val);
	पूर्णांक (*ग_लिखो)(काष्ठा xadc *xadc, अचिन्हित पूर्णांक reg, uपूर्णांक16_t val);
	पूर्णांक (*setup)(काष्ठा platक्रमm_device *pdev, काष्ठा iio_dev *indio_dev,
			पूर्णांक irq);
	व्योम (*update_alarm)(काष्ठा xadc *xadc, अचिन्हित पूर्णांक alarm);
	अचिन्हित दीर्घ (*get_dclk_rate)(काष्ठा xadc *xadc);
	irqवापस_t (*पूर्णांकerrupt_handler)(पूर्णांक irq, व्योम *devid);

	अचिन्हित पूर्णांक flags;
	क्रमागत xadc_type type;
पूर्ण;

अटल अंतरभूत पूर्णांक _xadc_पढ़ो_adc_reg(काष्ठा xadc *xadc, अचिन्हित पूर्णांक reg,
	uपूर्णांक16_t *val)
अणु
	lockdep_निश्चित_held(&xadc->mutex);
	वापस xadc->ops->पढ़ो(xadc, reg, val);
पूर्ण

अटल अंतरभूत पूर्णांक _xadc_ग_लिखो_adc_reg(काष्ठा xadc *xadc, अचिन्हित पूर्णांक reg,
	uपूर्णांक16_t val)
अणु
	lockdep_निश्चित_held(&xadc->mutex);
	वापस xadc->ops->ग_लिखो(xadc, reg, val);
पूर्ण

अटल अंतरभूत पूर्णांक xadc_पढ़ो_adc_reg(काष्ठा xadc *xadc, अचिन्हित पूर्णांक reg,
	uपूर्णांक16_t *val)
अणु
	पूर्णांक ret;

	mutex_lock(&xadc->mutex);
	ret = _xadc_पढ़ो_adc_reg(xadc, reg, val);
	mutex_unlock(&xadc->mutex);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक xadc_ग_लिखो_adc_reg(काष्ठा xadc *xadc, अचिन्हित पूर्णांक reg,
	uपूर्णांक16_t val)
अणु
	पूर्णांक ret;

	mutex_lock(&xadc->mutex);
	ret = _xadc_ग_लिखो_adc_reg(xadc, reg, val);
	mutex_unlock(&xadc->mutex);
	वापस ret;
पूर्ण

/* XADC hardmacro रेजिस्टर definitions */
#घोषणा XADC_REG_TEMP		0x00
#घोषणा XADC_REG_VCCINT		0x01
#घोषणा XADC_REG_VCCAUX		0x02
#घोषणा XADC_REG_VPVN		0x03
#घोषणा XADC_REG_VREFP		0x04
#घोषणा XADC_REG_VREFN		0x05
#घोषणा XADC_REG_VCCBRAM	0x06

#घोषणा XADC_REG_VCCPINT	0x0d
#घोषणा XADC_REG_VCCPAUX	0x0e
#घोषणा XADC_REG_VCCO_DDR	0x0f
#घोषणा XADC_REG_VAUX(x)	(0x10 + (x))

#घोषणा XADC_REG_MAX_TEMP	0x20
#घोषणा XADC_REG_MAX_VCCINT	0x21
#घोषणा XADC_REG_MAX_VCCAUX	0x22
#घोषणा XADC_REG_MAX_VCCBRAM	0x23
#घोषणा XADC_REG_MIN_TEMP	0x24
#घोषणा XADC_REG_MIN_VCCINT	0x25
#घोषणा XADC_REG_MIN_VCCAUX	0x26
#घोषणा XADC_REG_MIN_VCCBRAM	0x27
#घोषणा XADC_REG_MAX_VCCPINT	0x28
#घोषणा XADC_REG_MAX_VCCPAUX	0x29
#घोषणा XADC_REG_MAX_VCCO_DDR	0x2a
#घोषणा XADC_REG_MIN_VCCPINT	0x2c
#घोषणा XADC_REG_MIN_VCCPAUX	0x2d
#घोषणा XADC_REG_MIN_VCCO_DDR	0x2e

#घोषणा XADC_REG_CONF0		0x40
#घोषणा XADC_REG_CONF1		0x41
#घोषणा XADC_REG_CONF2		0x42
#घोषणा XADC_REG_SEQ(x)		(0x48 + (x))
#घोषणा XADC_REG_INPUT_MODE(x)	(0x4c + (x))
#घोषणा XADC_REG_THRESHOLD(x)	(0x50 + (x))

#घोषणा XADC_REG_FLAG		0x3f

#घोषणा XADC_CONF0_EC			BIT(9)
#घोषणा XADC_CONF0_ACQ			BIT(8)
#घोषणा XADC_CONF0_MUX			BIT(11)
#घोषणा XADC_CONF0_CHAN(x)		(x)

#घोषणा XADC_CONF1_SEQ_MASK		(0xf << 12)
#घोषणा XADC_CONF1_SEQ_DEFAULT		(0 << 12)
#घोषणा XADC_CONF1_SEQ_SINGLE_PASS	(1 << 12)
#घोषणा XADC_CONF1_SEQ_CONTINUOUS	(2 << 12)
#घोषणा XADC_CONF1_SEQ_SINGLE_CHANNEL	(3 << 12)
#घोषणा XADC_CONF1_SEQ_SIMULTANEOUS	(4 << 12)
#घोषणा XADC_CONF1_SEQ_INDEPENDENT	(8 << 12)
#घोषणा XADC_CONF1_ALARM_MASK		0x0f0f

#घोषणा XADC_CONF2_DIV_MASK	0xff00
#घोषणा XADC_CONF2_DIV_OFFSET	8

#घोषणा XADC_CONF2_PD_MASK	(0x3 << 4)
#घोषणा XADC_CONF2_PD_NONE	(0x0 << 4)
#घोषणा XADC_CONF2_PD_ADC_B	(0x2 << 4)
#घोषणा XADC_CONF2_PD_BOTH	(0x3 << 4)

#घोषणा XADC_ALARM_TEMP_MASK		BIT(0)
#घोषणा XADC_ALARM_VCCINT_MASK		BIT(1)
#घोषणा XADC_ALARM_VCCAUX_MASK		BIT(2)
#घोषणा XADC_ALARM_OT_MASK		BIT(3)
#घोषणा XADC_ALARM_VCCBRAM_MASK		BIT(4)
#घोषणा XADC_ALARM_VCCPINT_MASK		BIT(5)
#घोषणा XADC_ALARM_VCCPAUX_MASK		BIT(6)
#घोषणा XADC_ALARM_VCCODDR_MASK		BIT(7)

#घोषणा XADC_THRESHOLD_TEMP_MAX		0x0
#घोषणा XADC_THRESHOLD_VCCपूर्णांक_उच्च	0x1
#घोषणा XADC_THRESHOLD_VCCAUX_MAX	0x2
#घोषणा XADC_THRESHOLD_OT_MAX		0x3
#घोषणा XADC_THRESHOLD_TEMP_MIN		0x4
#घोषणा XADC_THRESHOLD_VCCपूर्णांक_न्यून	0x5
#घोषणा XADC_THRESHOLD_VCCAUX_MIN	0x6
#घोषणा XADC_THRESHOLD_OT_MIN		0x7
#घोषणा XADC_THRESHOLD_VCCBRAM_MAX	0x8
#घोषणा XADC_THRESHOLD_VCCPपूर्णांक_उच्च	0x9
#घोषणा XADC_THRESHOLD_VCCPAUX_MAX	0xa
#घोषणा XADC_THRESHOLD_VCCODDR_MAX	0xb
#घोषणा XADC_THRESHOLD_VCCBRAM_MIN	0xc
#घोषणा XADC_THRESHOLD_VCCPपूर्णांक_न्यून	0xd
#घोषणा XADC_THRESHOLD_VCCPAUX_MIN	0xe
#घोषणा XADC_THRESHOLD_VCCODDR_MIN	0xf

#पूर्ण_अगर
