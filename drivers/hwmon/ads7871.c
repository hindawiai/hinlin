<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  ads7871 - driver क्रम TI ADS7871 A/D converter
 *
 *  Copyright (c) 2010 Paul Thomas <pthomas8589@gmail.com>
 *
 *	You need to have something like this in काष्ठा spi_board_info
 *	अणु
 *		.modalias	= "ads7871",
 *		.max_speed_hz	= 2*1000*1000,
 *		.chip_select	= 0,
 *		.bus_num	= 1,
 *	पूर्ण,
 */

/*From figure 18 in the datasheet*/
/*Register addresses*/
#घोषणा REG_LS_BYTE	0 /*A/D Output Data, LS Byte*/
#घोषणा REG_MS_BYTE	1 /*A/D Output Data, MS Byte*/
#घोषणा REG_PGA_VALID	2 /*PGA Valid Register*/
#घोषणा REG_AD_CONTROL	3 /*A/D Control Register*/
#घोषणा REG_GAIN_MUX	4 /*Gain/Mux Register*/
#घोषणा REG_IO_STATE	5 /*Digital I/O State Register*/
#घोषणा REG_IO_CONTROL	6 /*Digital I/O Control Register*/
#घोषणा REG_OSC_CONTROL	7 /*Rev/Oscillator Control Register*/
#घोषणा REG_SER_CONTROL 24 /*Serial Interface Control Register*/
#घोषणा REG_ID		31 /*ID Register*/

/*
 * From figure 17 in the datasheet
 * These bits get ORed with the address to क्रमm
 * the inकाष्ठाion byte
 */
/*Inकाष्ठाion Bit masks*/
#घोषणा INST_MODE_BM	(1 << 7)
#घोषणा INST_READ_BM	(1 << 6)
#घोषणा INST_16BIT_BM	(1 << 5)

/*From figure 18 in the datasheet*/
/*bit masks क्रम Rev/Oscillator Control Register*/
#घोषणा MUX_CNV_BV	7
#घोषणा MUX_CNV_BM	(1 << MUX_CNV_BV)
#घोषणा MUX_M3_BM	(1 << 3) /*M3 selects single ended*/
#घोषणा MUX_G_BV	4 /*allows क्रम reg = (gain << MUX_G_BV) | ...*/

/*From figure 18 in the datasheet*/
/*bit masks क्रम Rev/Oscillator Control Register*/
#घोषणा OSC_OSCR_BM	(1 << 5)
#घोषणा OSC_OSCE_BM	(1 << 4)
#घोषणा OSC_REFE_BM	(1 << 3)
#घोषणा OSC_BUFE_BM	(1 << 2)
#घोषणा OSC_R2V_BM	(1 << 1)
#घोषणा OSC_RBG_BM	(1 << 0)

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/err.h>
#समावेश <linux/delay.h>

#घोषणा DEVICE_NAME	"ads7871"

काष्ठा ads7871_data अणु
	काष्ठा spi_device *spi;
पूर्ण;

अटल पूर्णांक ads7871_पढ़ो_reg8(काष्ठा spi_device *spi, पूर्णांक reg)
अणु
	पूर्णांक ret;
	reg = reg | INST_READ_BM;
	ret = spi_w8r8(spi, reg);
	वापस ret;
पूर्ण

अटल पूर्णांक ads7871_पढ़ो_reg16(काष्ठा spi_device *spi, पूर्णांक reg)
अणु
	पूर्णांक ret;
	reg = reg | INST_READ_BM | INST_16BIT_BM;
	ret = spi_w8r16(spi, reg);
	वापस ret;
पूर्ण

अटल पूर्णांक ads7871_ग_लिखो_reg8(काष्ठा spi_device *spi, पूर्णांक reg, u8 val)
अणु
	u8 पंचांगp[2] = अणुreg, valपूर्ण;
	वापस spi_ग_लिखो(spi, पंचांगp, माप(पंचांगp));
पूर्ण

अटल sमाप_प्रकार voltage_show(काष्ठा device *dev, काष्ठा device_attribute *da,
			    अक्षर *buf)
अणु
	काष्ठा ads7871_data *pdata = dev_get_drvdata(dev);
	काष्ठा spi_device *spi = pdata->spi;
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	पूर्णांक ret, val, i = 0;
	uपूर्णांक8_t channel, mux_cnv;

	channel = attr->index;
	/*
	 * TODO: add support क्रम conversions
	 * other than single ended with a gain of 1
	 */
	/*MUX_M3_BM क्रमces single ended*/
	/*This is also where the gain of the PGA would be set*/
	ads7871_ग_लिखो_reg8(spi, REG_GAIN_MUX,
		(MUX_CNV_BM | MUX_M3_BM | channel));

	ret = ads7871_पढ़ो_reg8(spi, REG_GAIN_MUX);
	mux_cnv = ((ret & MUX_CNV_BM) >> MUX_CNV_BV);
	/*
	 * on 400MHz arm9 platक्रमm the conversion
	 * is alपढ़ोy करोne when we करो this test
	 */
	जबतक ((i < 2) && mux_cnv) अणु
		i++;
		ret = ads7871_पढ़ो_reg8(spi, REG_GAIN_MUX);
		mux_cnv = ((ret & MUX_CNV_BM) >> MUX_CNV_BV);
		msleep_पूर्णांकerruptible(1);
	पूर्ण

	अगर (mux_cnv == 0) अणु
		val = ads7871_पढ़ो_reg16(spi, REG_LS_BYTE);
		/*result in volts*10000 = (val/8192)*2.5*10000*/
		val = ((val >> 2) * 25000) / 8192;
		वापस प्र_लिखो(buf, "%d\n", val);
	पूर्ण अन्यथा अणु
		वापस -1;
	पूर्ण
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(in0_input, voltage, 0);
अटल SENSOR_DEVICE_ATTR_RO(in1_input, voltage, 1);
अटल SENSOR_DEVICE_ATTR_RO(in2_input, voltage, 2);
अटल SENSOR_DEVICE_ATTR_RO(in3_input, voltage, 3);
अटल SENSOR_DEVICE_ATTR_RO(in4_input, voltage, 4);
अटल SENSOR_DEVICE_ATTR_RO(in5_input, voltage, 5);
अटल SENSOR_DEVICE_ATTR_RO(in6_input, voltage, 6);
अटल SENSOR_DEVICE_ATTR_RO(in7_input, voltage, 7);

अटल काष्ठा attribute *ads7871_attrs[] = अणु
	&sensor_dev_attr_in0_input.dev_attr.attr,
	&sensor_dev_attr_in1_input.dev_attr.attr,
	&sensor_dev_attr_in2_input.dev_attr.attr,
	&sensor_dev_attr_in3_input.dev_attr.attr,
	&sensor_dev_attr_in4_input.dev_attr.attr,
	&sensor_dev_attr_in5_input.dev_attr.attr,
	&sensor_dev_attr_in6_input.dev_attr.attr,
	&sensor_dev_attr_in7_input.dev_attr.attr,
	शून्य
पूर्ण;

ATTRIBUTE_GROUPS(ads7871);

अटल पूर्णांक ads7871_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा device *dev = &spi->dev;
	पूर्णांक ret;
	uपूर्णांक8_t val;
	काष्ठा ads7871_data *pdata;
	काष्ठा device *hwmon_dev;

	/* Configure the SPI bus */
	spi->mode = (SPI_MODE_0);
	spi->bits_per_word = 8;
	spi_setup(spi);

	ads7871_ग_लिखो_reg8(spi, REG_SER_CONTROL, 0);
	ads7871_ग_लिखो_reg8(spi, REG_AD_CONTROL, 0);

	val = (OSC_OSCR_BM | OSC_OSCE_BM | OSC_REFE_BM | OSC_BUFE_BM);
	ads7871_ग_लिखो_reg8(spi, REG_OSC_CONTROL, val);
	ret = ads7871_पढ़ो_reg8(spi, REG_OSC_CONTROL);

	dev_dbg(dev, "REG_OSC_CONTROL write:%x, read:%x\n", val, ret);
	/*
	 * because there is no other error checking on an SPI bus
	 * we need to make sure we really have a chip
	 */
	अगर (val != ret)
		वापस -ENODEV;

	pdata = devm_kzalloc(dev, माप(काष्ठा ads7871_data), GFP_KERNEL);
	अगर (!pdata)
		वापस -ENOMEM;

	pdata->spi = spi;

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev, spi->modalias,
							   pdata,
							   ads7871_groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल काष्ठा spi_driver ads7871_driver = अणु
	.driver = अणु
		.name = DEVICE_NAME,
	पूर्ण,
	.probe = ads7871_probe,
पूर्ण;

module_spi_driver(ads7871_driver);

MODULE_AUTHOR("Paul Thomas <pthomas8589@gmail.com>");
MODULE_DESCRIPTION("TI ADS7871 A/D driver");
MODULE_LICENSE("GPL");
