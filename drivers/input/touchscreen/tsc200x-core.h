<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _TSC200X_CORE_H
#घोषणा _TSC200X_CORE_H

/* control byte 1 */
#घोषणा TSC200X_CMD			0x80
#घोषणा TSC200X_CMD_NORMAL		0x00
#घोषणा TSC200X_CMD_STOP		0x01
#घोषणा TSC200X_CMD_12BIT		0x04

/* control byte 0 */
#घोषणा TSC200X_REG_READ		0x01 /* R/W access */
#घोषणा TSC200X_REG_PND0		0x02 /* Power Not Down Control */
#घोषणा TSC200X_REG_X			(0x0 << 3)
#घोषणा TSC200X_REG_Y			(0x1 << 3)
#घोषणा TSC200X_REG_Z1			(0x2 << 3)
#घोषणा TSC200X_REG_Z2			(0x3 << 3)
#घोषणा TSC200X_REG_AUX			(0x4 << 3)
#घोषणा TSC200X_REG_TEMP1		(0x5 << 3)
#घोषणा TSC200X_REG_TEMP2		(0x6 << 3)
#घोषणा TSC200X_REG_STATUS		(0x7 << 3)
#घोषणा TSC200X_REG_AUX_HIGH		(0x8 << 3)
#घोषणा TSC200X_REG_AUX_LOW		(0x9 << 3)
#घोषणा TSC200X_REG_TEMP_HIGH		(0xA << 3)
#घोषणा TSC200X_REG_TEMP_LOW		(0xB << 3)
#घोषणा TSC200X_REG_CFR0		(0xC << 3)
#घोषणा TSC200X_REG_CFR1		(0xD << 3)
#घोषणा TSC200X_REG_CFR2		(0xE << 3)
#घोषणा TSC200X_REG_CONV_FUNC		(0xF << 3)

/* configuration रेजिस्टर 0 */
#घोषणा TSC200X_CFR0_PRECHARGE_276US	0x0040
#घोषणा TSC200X_CFR0_STABTIME_1MS	0x0300
#घोषणा TSC200X_CFR0_CLOCK_1MHZ		0x1000
#घोषणा TSC200X_CFR0_RESOLUTION12	0x2000
#घोषणा TSC200X_CFR0_PENMODE		0x8000
#घोषणा TSC200X_CFR0_INITVALUE		(TSC200X_CFR0_STABTIME_1MS    | \
					 TSC200X_CFR0_CLOCK_1MHZ      | \
					 TSC200X_CFR0_RESOLUTION12    | \
					 TSC200X_CFR0_PRECHARGE_276US | \
					 TSC200X_CFR0_PENMODE)

/* bits common to both पढ़ो and ग_लिखो of configuration रेजिस्टर 0 */
#घोषणा	TSC200X_CFR0_RW_MASK		0x3fff

/* configuration रेजिस्टर 1 */
#घोषणा TSC200X_CFR1_BATCHDELAY_4MS	0x0003
#घोषणा TSC200X_CFR1_INITVALUE		TSC200X_CFR1_BATCHDELAY_4MS

/* configuration रेजिस्टर 2 */
#घोषणा TSC200X_CFR2_MAVE_Z		0x0004
#घोषणा TSC200X_CFR2_MAVE_Y		0x0008
#घोषणा TSC200X_CFR2_MAVE_X		0x0010
#घोषणा TSC200X_CFR2_AVG_7		0x0800
#घोषणा TSC200X_CFR2_MEDIUM_15		0x3000
#घोषणा TSC200X_CFR2_INITVALUE		(TSC200X_CFR2_MAVE_X	| \
					 TSC200X_CFR2_MAVE_Y	| \
					 TSC200X_CFR2_MAVE_Z	| \
					 TSC200X_CFR2_MEDIUM_15	| \
					 TSC200X_CFR2_AVG_7)

#घोषणा MAX_12BIT			0xfff
#घोषणा TSC200X_DEF_X_FUZZ		4
#घोषणा TSC200X_DEF_Y_FUZZ		8
#घोषणा TSC200X_DEF_P_FUZZ		2
#घोषणा TSC200X_DEF_RESISTOR		280

#घोषणा TSC2005_SPI_MAX_SPEED_HZ	10000000
#घोषणा TSC200X_PENUP_TIME_MS		40

बाह्य स्थिर काष्ठा regmap_config tsc200x_regmap_config;
बाह्य स्थिर काष्ठा dev_pm_ops tsc200x_pm_ops;

पूर्णांक tsc200x_probe(काष्ठा device *dev, पूर्णांक irq, स्थिर काष्ठा input_id *tsc_id,
		  काष्ठा regmap *regmap,
		  पूर्णांक (*tsc200x_cmd)(काष्ठा device *dev, u8 cmd));
पूर्णांक tsc200x_हटाओ(काष्ठा device *dev);

#पूर्ण_अगर
