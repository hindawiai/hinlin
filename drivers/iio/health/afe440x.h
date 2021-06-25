<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * AFE440X Heart Rate Monitors and Low-Cost Pulse Oximeters
 *
 * Copyright (C) 2015 Texas Instruments Incorporated - https://www.ti.com/
 *	Andrew F. Davis <afd@ti.com>
 */

#अगर_अघोषित _AFE440X_H
#घोषणा _AFE440X_H

/* AFE440X रेजिस्टरs */
#घोषणा AFE440X_CONTROL0		0x00
#घोषणा AFE440X_LED2STC			0x01
#घोषणा AFE440X_LED2ENDC		0x02
#घोषणा AFE440X_LED1LEDSTC		0x03
#घोषणा AFE440X_LED1LEDENDC		0x04
#घोषणा AFE440X_ALED2STC		0x05
#घोषणा AFE440X_ALED2ENDC		0x06
#घोषणा AFE440X_LED1STC			0x07
#घोषणा AFE440X_LED1ENDC		0x08
#घोषणा AFE440X_LED2LEDSTC		0x09
#घोषणा AFE440X_LED2LEDENDC		0x0a
#घोषणा AFE440X_ALED1STC		0x0b
#घोषणा AFE440X_ALED1ENDC		0x0c
#घोषणा AFE440X_LED2CONVST		0x0d
#घोषणा AFE440X_LED2CONVEND		0x0e
#घोषणा AFE440X_ALED2CONVST		0x0f
#घोषणा AFE440X_ALED2CONVEND		0x10
#घोषणा AFE440X_LED1CONVST		0x11
#घोषणा AFE440X_LED1CONVEND		0x12
#घोषणा AFE440X_ALED1CONVST		0x13
#घोषणा AFE440X_ALED1CONVEND		0x14
#घोषणा AFE440X_ADCRSTSTCT0		0x15
#घोषणा AFE440X_ADCRSTENDCT0		0x16
#घोषणा AFE440X_ADCRSTSTCT1		0x17
#घोषणा AFE440X_ADCRSTENDCT1		0x18
#घोषणा AFE440X_ADCRSTSTCT2		0x19
#घोषणा AFE440X_ADCRSTENDCT2		0x1a
#घोषणा AFE440X_ADCRSTSTCT3		0x1b
#घोषणा AFE440X_ADCRSTENDCT3		0x1c
#घोषणा AFE440X_PRPCOUNT		0x1d
#घोषणा AFE440X_CONTROL1		0x1e
#घोषणा AFE440X_LEDCNTRL		0x22
#घोषणा AFE440X_CONTROL2		0x23
#घोषणा AFE440X_ALARM			0x29
#घोषणा AFE440X_LED2VAL			0x2a
#घोषणा AFE440X_ALED2VAL		0x2b
#घोषणा AFE440X_LED1VAL			0x2c
#घोषणा AFE440X_ALED1VAL		0x2d
#घोषणा AFE440X_LED2_ALED2VAL		0x2e
#घोषणा AFE440X_LED1_ALED1VAL		0x2f
#घोषणा AFE440X_CONTROL3		0x31
#घोषणा AFE440X_PDNCYCLESTC		0x32
#घोषणा AFE440X_PDNCYCLEENDC		0x33

/* CONTROL0 रेजिस्टर fields */
#घोषणा AFE440X_CONTROL0_REG_READ	BIT(0)
#घोषणा AFE440X_CONTROL0_TM_COUNT_RST	BIT(1)
#घोषणा AFE440X_CONTROL0_SW_RESET	BIT(3)

/* CONTROL1 रेजिस्टर fields */
#घोषणा AFE440X_CONTROL1_TIMEREN	BIT(8)

/* TIAGAIN रेजिस्टर fields */
#घोषणा AFE440X_TIAGAIN_ENSEPGAIN	BIT(15)

/* CONTROL2 रेजिस्टर fields */
#घोषणा AFE440X_CONTROL2_PDN_AFE	BIT(0)
#घोषणा AFE440X_CONTROL2_PDN_RX		BIT(1)
#घोषणा AFE440X_CONTROL2_DYNAMIC4	BIT(3)
#घोषणा AFE440X_CONTROL2_DYNAMIC3	BIT(4)
#घोषणा AFE440X_CONTROL2_DYNAMIC2	BIT(14)
#घोषणा AFE440X_CONTROL2_DYNAMIC1	BIT(20)

/* CONTROL3 रेजिस्टर fields */
#घोषणा AFE440X_CONTROL3_CLKDIV		GENMASK(2, 0)

/* CONTROL0 values */
#घोषणा AFE440X_CONTROL0_WRITE		0x0
#घोषणा AFE440X_CONTROL0_READ		0x1

#घोषणा AFE440X_INTENSITY_CHAN(_index, _mask)			\
	अणु							\
		.type = IIO_INTENSITY,				\
		.channel = _index,				\
		.address = _index,				\
		.scan_index = _index,				\
		.scan_type = अणु					\
				.sign = 's',			\
				.realbits = 24,			\
				.storagebits = 32,		\
				.endianness = IIO_CPU,		\
		पूर्ण,						\
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |	\
			_mask,					\
		.indexed = true,				\
	पूर्ण

#घोषणा AFE440X_CURRENT_CHAN(_index)				\
	अणु							\
		.type = IIO_CURRENT,				\
		.channel = _index,				\
		.address = _index,				\
		.scan_index = -1,				\
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |	\
			BIT(IIO_CHAN_INFO_SCALE),		\
		.indexed = true,				\
		.output = true,					\
	पूर्ण

काष्ठा afe440x_val_table अणु
	पूर्णांक पूर्णांकeger;
	पूर्णांक fract;
पूर्ण;

#घोषणा AFE440X_TABLE_ATTR(_name, _table)				\
अटल sमाप_प्रकार _name ## _show(काष्ठा device *dev,			\
			      काष्ठा device_attribute *attr, अक्षर *buf)	\
अणु									\
	sमाप_प्रकार len = 0;						\
	पूर्णांक i;								\
									\
	क्रम (i = 0; i < ARRAY_SIZE(_table); i++)			\
		len += scnम_लिखो(buf + len, PAGE_SIZE - len, "%d.%06u ", \
				 _table[i].पूर्णांकeger,			\
				 _table[i].fract);			\
									\
	buf[len - 1] = '\n';						\
									\
	वापस len;							\
पूर्ण									\
अटल DEVICE_ATTR_RO(_name)

काष्ठा afe440x_attr अणु
	काष्ठा device_attribute dev_attr;
	अचिन्हित पूर्णांक field;
	स्थिर काष्ठा afe440x_val_table *val_table;
	अचिन्हित पूर्णांक table_size;
पूर्ण;

#घोषणा to_afe440x_attr(_dev_attr)				\
	container_of(_dev_attr, काष्ठा afe440x_attr, dev_attr)

#घोषणा AFE440X_ATTR(_name, _field, _table)			\
	काष्ठा afe440x_attr afe440x_attr_##_name = अणु		\
		.dev_attr = __ATTR(_name, (S_IRUGO | S_IWUSR),	\
				   afe440x_show_रेजिस्टर,	\
				   afe440x_store_रेजिस्टर),	\
		.field = _field,				\
		.val_table = _table,				\
		.table_size = ARRAY_SIZE(_table),		\
	पूर्ण

#पूर्ण_अगर /* _AFE440X_H */
