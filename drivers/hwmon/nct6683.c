<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * nct6683 - Driver क्रम the hardware monitoring functionality of
 *	     Nuvoton NCT6683D/NCT6686D/NCT6687D eSIO
 *
 * Copyright (C) 2013  Guenter Roeck <linux@roeck-us.net>
 *
 * Derived from nct6775 driver
 * Copyright (C) 2012, 2013  Guenter Roeck <linux@roeck-us.net>
 *
 * Supports the following chips:
 *
 * Chip        #vin    #fan    #pwm    #temp  chip ID
 * nct6683d     21(1)   16      8       32(1) 0xc730
 * nct6686d     21(1)   16      8       32(1) 0xd440
 * nct6687d     21(1)   16      8       32(1) 0xd590
 *
 * Notes:
 *	(1) Total number of vin and temp inमाला_दो is 32.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/acpi.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

क्रमागत kinds अणु nct6683, nct6686, nct6687 पूर्ण;

अटल bool क्रमce;
module_param(क्रमce, bool, 0);
MODULE_PARM_DESC(क्रमce, "Set to one to enable support for unknown vendors");

अटल स्थिर अक्षर * स्थिर nct6683_device_names[] = अणु
	"nct6683",
	"nct6686",
	"nct6687",
पूर्ण;

अटल स्थिर अक्षर * स्थिर nct6683_chip_names[] = अणु
	"NCT6683D",
	"NCT6686D",
	"NCT6687D",
पूर्ण;

#घोषणा DRVNAME "nct6683"

/*
 * Super-I/O स्थिरants and functions
 */

#घोषणा NCT6683_LD_ACPI		0x0a
#घोषणा NCT6683_LD_HWM		0x0b
#घोषणा NCT6683_LD_VID		0x0d

#घोषणा SIO_REG_LDSEL		0x07	/* Logical device select */
#घोषणा SIO_REG_DEVID		0x20	/* Device ID (2 bytes) */
#घोषणा SIO_REG_ENABLE		0x30	/* Logical device enable */
#घोषणा SIO_REG_ADDR		0x60	/* Logical device address (2 bytes) */

#घोषणा SIO_NCT6681_ID		0xb270	/* क्रम later */
#घोषणा SIO_NCT6683_ID		0xc730
#घोषणा SIO_NCT6686_ID		0xd440
#घोषणा SIO_NCT6687_ID		0xd590
#घोषणा SIO_ID_MASK		0xFFF0

अटल अंतरभूत व्योम
superio_outb(पूर्णांक ioreg, पूर्णांक reg, पूर्णांक val)
अणु
	outb(reg, ioreg);
	outb(val, ioreg + 1);
पूर्ण

अटल अंतरभूत पूर्णांक
superio_inb(पूर्णांक ioreg, पूर्णांक reg)
अणु
	outb(reg, ioreg);
	वापस inb(ioreg + 1);
पूर्ण

अटल अंतरभूत व्योम
superio_select(पूर्णांक ioreg, पूर्णांक ld)
अणु
	outb(SIO_REG_LDSEL, ioreg);
	outb(ld, ioreg + 1);
पूर्ण

अटल अंतरभूत पूर्णांक
superio_enter(पूर्णांक ioreg)
अणु
	/*
	 * Try to reserve <ioreg> and <ioreg + 1> क्रम exclusive access.
	 */
	अगर (!request_muxed_region(ioreg, 2, DRVNAME))
		वापस -EBUSY;

	outb(0x87, ioreg);
	outb(0x87, ioreg);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
superio_निकास(पूर्णांक ioreg)
अणु
	outb(0xaa, ioreg);
	outb(0x02, ioreg);
	outb(0x02, ioreg + 1);
	release_region(ioreg, 2);
पूर्ण

/*
 * ISA स्थिरants
 */

#घोषणा IOREGION_ALIGNMENT	(~7)
#घोषणा IOREGION_OFFSET		4	/* Use EC port 1 */
#घोषणा IOREGION_LENGTH		4

#घोषणा EC_PAGE_REG		0
#घोषणा EC_INDEX_REG		1
#घोषणा EC_DATA_REG		2
#घोषणा EC_EVENT_REG		3

/* Common and NCT6683 specअगरic data */

#घोषणा NCT6683_NUM_REG_MON		32
#घोषणा NCT6683_NUM_REG_FAN		16
#घोषणा NCT6683_NUM_REG_PWM		8

#घोषणा NCT6683_REG_MON(x)		(0x100 + (x) * 2)
#घोषणा NCT6683_REG_FAN_RPM(x)		(0x140 + (x) * 2)
#घोषणा NCT6683_REG_PWM(x)		(0x160 + (x))
#घोषणा NCT6683_REG_PWM_WRITE(x)	(0xa28 + (x))

#घोषणा NCT6683_REG_MON_STS(x)		(0x174 + (x))
#घोषणा NCT6683_REG_IDLE(x)		(0x178 + (x))

#घोषणा NCT6683_REG_FAN_STS(x)		(0x17c + (x))
#घोषणा NCT6683_REG_FAN_ERRSTS		0x17e
#घोषणा NCT6683_REG_FAN_INITSTS		0x17f

#घोषणा NCT6683_HWM_CFG			0x180

#घोषणा NCT6683_REG_MON_CFG(x)		(0x1a0 + (x))
#घोषणा NCT6683_REG_FANIN_CFG(x)	(0x1c0 + (x))
#घोषणा NCT6683_REG_FANOUT_CFG(x)	(0x1d0 + (x))

#घोषणा NCT6683_REG_INTEL_TEMP_MAX(x)	(0x901 + (x) * 16)
#घोषणा NCT6683_REG_INTEL_TEMP_CRIT(x)	(0x90d + (x) * 16)

#घोषणा NCT6683_REG_TEMP_HYST(x)	(0x330 + (x))		/* 8 bit */
#घोषणा NCT6683_REG_TEMP_MAX(x)		(0x350 + (x))		/* 8 bit */
#घोषणा NCT6683_REG_MON_HIGH(x)		(0x370 + (x) * 2)	/* 8 bit */
#घोषणा NCT6683_REG_MON_LOW(x)		(0x371 + (x) * 2)	/* 8 bit */

#घोषणा NCT6683_REG_FAN_MIN(x)		(0x3b8 + (x) * 2)	/* 16 bit */

#घोषणा NCT6683_REG_FAN_CFG_CTRL	0xa01
#घोषणा NCT6683_FAN_CFG_REQ		0x80
#घोषणा NCT6683_FAN_CFG_DONE		0x40

#घोषणा NCT6683_REG_CUSTOMER_ID		0x602
#घोषणा NCT6683_CUSTOMER_ID_INTEL	0x805
#घोषणा NCT6683_CUSTOMER_ID_MITAC	0xa0e
#घोषणा NCT6683_CUSTOMER_ID_MSI		0x201
#घोषणा NCT6683_CUSTOMER_ID_ASROCK		0xe2c

#घोषणा NCT6683_REG_BUILD_YEAR		0x604
#घोषणा NCT6683_REG_BUILD_MONTH		0x605
#घोषणा NCT6683_REG_BUILD_DAY		0x606
#घोषणा NCT6683_REG_SERIAL		0x607
#घोषणा NCT6683_REG_VERSION_HI		0x608
#घोषणा NCT6683_REG_VERSION_LO		0x609

#घोषणा NCT6683_REG_CR_CASEOPEN		0xe8
#घोषणा NCT6683_CR_CASEOPEN_MASK	(1 << 7)

#घोषणा NCT6683_REG_CR_BEEP		0xe0
#घोषणा NCT6683_CR_BEEP_MASK		(1 << 6)

अटल स्थिर अक्षर *स्थिर nct6683_mon_label[] = अणु
	शून्य,	/* disabled */
	"Local",
	"Diode 0 (curr)",
	"Diode 1 (curr)",
	"Diode 2 (curr)",
	"Diode 0 (volt)",
	"Diode 1 (volt)",
	"Diode 2 (volt)",
	"Thermistor 14",
	"Thermistor 15",
	"Thermistor 16",
	"Thermistor 0",
	"Thermistor 1",
	"Thermistor 2",
	"Thermistor 3",
	"Thermistor 4",
	"Thermistor 5",		/* 0x10 */
	"Thermistor 6",
	"Thermistor 7",
	"Thermistor 8",
	"Thermistor 9",
	"Thermistor 10",
	"Thermistor 11",
	"Thermistor 12",
	"Thermistor 13",
	शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य,
	"PECI 0.0",		/* 0x20 */
	"PECI 1.0",
	"PECI 2.0",
	"PECI 3.0",
	"PECI 0.1",
	"PECI 1.1",
	"PECI 2.1",
	"PECI 3.1",
	"PECI DIMM 0",
	"PECI DIMM 1",
	"PECI DIMM 2",
	"PECI DIMM 3",
	शून्य, शून्य, शून्य, शून्य,
	"PCH CPU",		/* 0x30 */
	"PCH CHIP",
	"PCH CHIP CPU MAX",
	"PCH MCH",
	"PCH DIMM 0",
	"PCH DIMM 1",
	"PCH DIMM 2",
	"PCH DIMM 3",
	"SMBus 0",
	"SMBus 1",
	"SMBus 2",
	"SMBus 3",
	"SMBus 4",
	"SMBus 5",
	"DIMM 0",
	"DIMM 1",
	"DIMM 2",		/* 0x40 */
	"DIMM 3",
	"AMD TSI Addr 90h",
	"AMD TSI Addr 92h",
	"AMD TSI Addr 94h",
	"AMD TSI Addr 96h",
	"AMD TSI Addr 98h",
	"AMD TSI Addr 9ah",
	"AMD TSI Addr 9ch",
	"AMD TSI Addr 9dh",
	शून्य, शून्य, शून्य, शून्य, शून्य, शून्य,
	"Virtual 0",		/* 0x50 */
	"Virtual 1",
	"Virtual 2",
	"Virtual 3",
	"Virtual 4",
	"Virtual 5",
	"Virtual 6",
	"Virtual 7",
	शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य,
	"VCC",			/* 0x60 voltage sensors */
	"VSB",
	"AVSB",
	"VTT",
	"VBAT",
	"VREF",
	"VIN0",
	"VIN1",
	"VIN2",
	"VIN3",
	"VIN4",
	"VIN5",
	"VIN6",
	"VIN7",
	"VIN8",
	"VIN9",
	"VIN10",
	"VIN11",
	"VIN12",
	"VIN13",
	"VIN14",
	"VIN15",
	"VIN16",
पूर्ण;

#घोषणा NUM_MON_LABELS		ARRAY_SIZE(nct6683_mon_label)
#घोषणा MON_VOLTAGE_START	0x60

/* ------------------------------------------------------- */

काष्ठा nct6683_data अणु
	पूर्णांक addr;		/* IO base of EC space */
	पूर्णांक sioreg;		/* SIO रेजिस्टर */
	क्रमागत kinds kind;
	u16 customer_id;

	काष्ठा device *hwmon_dev;
	स्थिर काष्ठा attribute_group *groups[6];

	पूर्णांक temp_num;			/* number of temperature attributes */
	u8 temp_index[NCT6683_NUM_REG_MON];
	u8 temp_src[NCT6683_NUM_REG_MON];

	u8 in_num;			/* number of voltage attributes */
	u8 in_index[NCT6683_NUM_REG_MON];
	u8 in_src[NCT6683_NUM_REG_MON];

	काष्ठा mutex update_lock;	/* used to protect sensor updates */
	bool valid;			/* true अगर following fields are valid */
	अचिन्हित दीर्घ last_updated;	/* In jअगरfies */

	/* Voltage attribute values */
	u8 in[3][NCT6683_NUM_REG_MON];	/* [0]=in, [1]=in_max, [2]=in_min */

	/* Temperature attribute values */
	s16 temp_in[NCT6683_NUM_REG_MON];
	s8 temp[4][NCT6683_NUM_REG_MON];/* [0]=min, [1]=max, [2]=hyst,
					 * [3]=crit
					 */

	/* Fan attribute values */
	अचिन्हित पूर्णांक rpm[NCT6683_NUM_REG_FAN];
	u16 fan_min[NCT6683_NUM_REG_FAN];
	u8 fanin_cfg[NCT6683_NUM_REG_FAN];
	u8 fanout_cfg[NCT6683_NUM_REG_FAN];
	u16 have_fan;			/* some fan inमाला_दो can be disabled */

	u8 have_pwm;
	u8 pwm[NCT6683_NUM_REG_PWM];

#अगर_घोषित CONFIG_PM
	/* Remember extra रेजिस्टर values over suspend/resume */
	u8 hwm_cfg;
#पूर्ण_अगर
पूर्ण;

काष्ठा nct6683_sio_data अणु
	पूर्णांक sioreg;
	क्रमागत kinds kind;
पूर्ण;

काष्ठा sensor_device_ढाँचा अणु
	काष्ठा device_attribute dev_attr;
	जोड़ अणु
		काष्ठा अणु
			u8 nr;
			u8 index;
		पूर्ण s;
		पूर्णांक index;
	पूर्ण u;
	bool s2;	/* true अगर both index and nr are used */
पूर्ण;

काष्ठा sensor_device_attr_u अणु
	जोड़ अणु
		काष्ठा sensor_device_attribute a1;
		काष्ठा sensor_device_attribute_2 a2;
	पूर्ण u;
	अक्षर name[32];
पूर्ण;

#घोषणा __TEMPLATE_ATTR(_ढाँचा, _mode, _show, _store) अणु	\
	.attr = अणु.name = _ढाँचा, .mode = _mode पूर्ण,		\
	.show	= _show,					\
	.store	= _store,					\
पूर्ण

#घोषणा SENSOR_DEVICE_TEMPLATE(_ढाँचा, _mode, _show, _store, _index)	\
	अणु .dev_attr = __TEMPLATE_ATTR(_ढाँचा, _mode, _show, _store),	\
	  .u.index = _index,						\
	  .s2 = false पूर्ण

#घोषणा SENSOR_DEVICE_TEMPLATE_2(_ढाँचा, _mode, _show, _store,	\
				 _nr, _index)				\
	अणु .dev_attr = __TEMPLATE_ATTR(_ढाँचा, _mode, _show, _store),	\
	  .u.s.index = _index,						\
	  .u.s.nr = _nr,						\
	  .s2 = true पूर्ण

#घोषणा SENSOR_TEMPLATE(_name, _ढाँचा, _mode, _show, _store, _index)	\
अटल काष्ठा sensor_device_ढाँचा sensor_dev_ढाँचा_##_name	\
	= SENSOR_DEVICE_TEMPLATE(_ढाँचा, _mode, _show, _store,	\
				 _index)

#घोषणा SENSOR_TEMPLATE_2(_name, _ढाँचा, _mode, _show, _store,	\
			  _nr, _index)					\
अटल काष्ठा sensor_device_ढाँचा sensor_dev_ढाँचा_##_name	\
	= SENSOR_DEVICE_TEMPLATE_2(_ढाँचा, _mode, _show, _store,	\
				 _nr, _index)

काष्ठा sensor_ढाँचा_group अणु
	काष्ठा sensor_device_ढाँचा **ढाँचाs;
	umode_t (*is_visible)(काष्ठा kobject *, काष्ठा attribute *, पूर्णांक);
	पूर्णांक base;
पूर्ण;

अटल काष्ठा attribute_group *
nct6683_create_attr_group(काष्ठा device *dev,
			  स्थिर काष्ठा sensor_ढाँचा_group *tg,
			  पूर्णांक repeat)
अणु
	काष्ठा sensor_device_attribute_2 *a2;
	काष्ठा sensor_device_attribute *a;
	काष्ठा sensor_device_ढाँचा **t;
	काष्ठा sensor_device_attr_u *su;
	काष्ठा attribute_group *group;
	काष्ठा attribute **attrs;
	पूर्णांक i, j, count;

	अगर (repeat <= 0)
		वापस ERR_PTR(-EINVAL);

	t = tg->ढाँचाs;
	क्रम (count = 0; *t; t++, count++)
		;

	अगर (count == 0)
		वापस ERR_PTR(-EINVAL);

	group = devm_kzalloc(dev, माप(*group), GFP_KERNEL);
	अगर (group == शून्य)
		वापस ERR_PTR(-ENOMEM);

	attrs = devm_kसुस्मृति(dev, repeat * count + 1, माप(*attrs),
			     GFP_KERNEL);
	अगर (attrs == शून्य)
		वापस ERR_PTR(-ENOMEM);

	su = devm_kzalloc(dev, array3_size(repeat, count, माप(*su)),
			  GFP_KERNEL);
	अगर (su == शून्य)
		वापस ERR_PTR(-ENOMEM);

	group->attrs = attrs;
	group->is_visible = tg->is_visible;

	क्रम (i = 0; i < repeat; i++) अणु
		t = tg->ढाँचाs;
		क्रम (j = 0; *t != शून्य; j++) अणु
			snम_लिखो(su->name, माप(su->name),
				 (*t)->dev_attr.attr.name, tg->base + i);
			अगर ((*t)->s2) अणु
				a2 = &su->u.a2;
				sysfs_attr_init(&a2->dev_attr.attr);
				a2->dev_attr.attr.name = su->name;
				a2->nr = (*t)->u.s.nr + i;
				a2->index = (*t)->u.s.index;
				a2->dev_attr.attr.mode =
				  (*t)->dev_attr.attr.mode;
				a2->dev_attr.show = (*t)->dev_attr.show;
				a2->dev_attr.store = (*t)->dev_attr.store;
				*attrs = &a2->dev_attr.attr;
			पूर्ण अन्यथा अणु
				a = &su->u.a1;
				sysfs_attr_init(&a->dev_attr.attr);
				a->dev_attr.attr.name = su->name;
				a->index = (*t)->u.index + i;
				a->dev_attr.attr.mode =
				  (*t)->dev_attr.attr.mode;
				a->dev_attr.show = (*t)->dev_attr.show;
				a->dev_attr.store = (*t)->dev_attr.store;
				*attrs = &a->dev_attr.attr;
			पूर्ण
			attrs++;
			su++;
			t++;
		पूर्ण
	पूर्ण

	वापस group;
पूर्ण

/* LSB is 16 mV, except क्रम the following sources, where it is 32 mV */
#घोषणा MON_SRC_VCC	0x60
#घोषणा MON_SRC_VSB	0x61
#घोषणा MON_SRC_AVSB	0x62
#घोषणा MON_SRC_VBAT	0x64

अटल अंतरभूत दीर्घ in_from_reg(u16 reg, u8 src)
अणु
	पूर्णांक scale = 16;

	अगर (src == MON_SRC_VCC || src == MON_SRC_VSB || src == MON_SRC_AVSB ||
	    src == MON_SRC_VBAT)
		scale <<= 1;
	वापस reg * scale;
पूर्ण

अटल u16 nct6683_पढ़ो(काष्ठा nct6683_data *data, u16 reg)
अणु
	पूर्णांक res;

	outb_p(0xff, data->addr + EC_PAGE_REG);		/* unlock */
	outb_p(reg >> 8, data->addr + EC_PAGE_REG);
	outb_p(reg & 0xff, data->addr + EC_INDEX_REG);
	res = inb_p(data->addr + EC_DATA_REG);
	वापस res;
पूर्ण

अटल u16 nct6683_पढ़ो16(काष्ठा nct6683_data *data, u16 reg)
अणु
	वापस (nct6683_पढ़ो(data, reg) << 8) | nct6683_पढ़ो(data, reg + 1);
पूर्ण

अटल व्योम nct6683_ग_लिखो(काष्ठा nct6683_data *data, u16 reg, u16 value)
अणु
	outb_p(0xff, data->addr + EC_PAGE_REG);		/* unlock */
	outb_p(reg >> 8, data->addr + EC_PAGE_REG);
	outb_p(reg & 0xff, data->addr + EC_INDEX_REG);
	outb_p(value & 0xff, data->addr + EC_DATA_REG);
पूर्ण

अटल पूर्णांक get_in_reg(काष्ठा nct6683_data *data, पूर्णांक nr, पूर्णांक index)
अणु
	पूर्णांक ch = data->in_index[index];
	पूर्णांक reg = -EINVAL;

	चयन (nr) अणु
	हाल 0:
		reg = NCT6683_REG_MON(ch);
		अवरोध;
	हाल 1:
		अगर (data->customer_id != NCT6683_CUSTOMER_ID_INTEL)
			reg = NCT6683_REG_MON_LOW(ch);
		अवरोध;
	हाल 2:
		अगर (data->customer_id != NCT6683_CUSTOMER_ID_INTEL)
			reg = NCT6683_REG_MON_HIGH(ch);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस reg;
पूर्ण

अटल पूर्णांक get_temp_reg(काष्ठा nct6683_data *data, पूर्णांक nr, पूर्णांक index)
अणु
	पूर्णांक ch = data->temp_index[index];
	पूर्णांक reg = -EINVAL;

	चयन (data->customer_id) अणु
	हाल NCT6683_CUSTOMER_ID_INTEL:
		चयन (nr) अणु
		शेष:
		हाल 1:	/* max */
			reg = NCT6683_REG_INTEL_TEMP_MAX(ch);
			अवरोध;
		हाल 3:	/* crit */
			reg = NCT6683_REG_INTEL_TEMP_CRIT(ch);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल NCT6683_CUSTOMER_ID_MITAC:
	शेष:
		चयन (nr) अणु
		शेष:
		हाल 0:	/* min */
			reg = NCT6683_REG_MON_LOW(ch);
			अवरोध;
		हाल 1:	/* max */
			reg = NCT6683_REG_TEMP_MAX(ch);
			अवरोध;
		हाल 2:	/* hyst */
			reg = NCT6683_REG_TEMP_HYST(ch);
			अवरोध;
		हाल 3:	/* crit */
			reg = NCT6683_REG_MON_HIGH(ch);
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण
	वापस reg;
पूर्ण

अटल व्योम nct6683_update_pwm(काष्ठा device *dev)
अणु
	काष्ठा nct6683_data *data = dev_get_drvdata(dev);
	पूर्णांक i;

	क्रम (i = 0; i < NCT6683_NUM_REG_PWM; i++) अणु
		अगर (!(data->have_pwm & (1 << i)))
			जारी;
		data->pwm[i] = nct6683_पढ़ो(data, NCT6683_REG_PWM(i));
	पूर्ण
पूर्ण

अटल काष्ठा nct6683_data *nct6683_update_device(काष्ठा device *dev)
अणु
	काष्ठा nct6683_data *data = dev_get_drvdata(dev);
	पूर्णांक i, j;

	mutex_lock(&data->update_lock);

	अगर (समय_after(jअगरfies, data->last_updated + HZ) || !data->valid) अणु
		/* Measured voltages and limits */
		क्रम (i = 0; i < data->in_num; i++) अणु
			क्रम (j = 0; j < 3; j++) अणु
				पूर्णांक reg = get_in_reg(data, j, i);

				अगर (reg >= 0)
					data->in[j][i] =
						nct6683_पढ़ो(data, reg);
			पूर्ण
		पूर्ण

		/* Measured temperatures and limits */
		क्रम (i = 0; i < data->temp_num; i++) अणु
			u8 ch = data->temp_index[i];

			data->temp_in[i] = nct6683_पढ़ो16(data,
							  NCT6683_REG_MON(ch));
			क्रम (j = 0; j < 4; j++) अणु
				पूर्णांक reg = get_temp_reg(data, j, i);

				अगर (reg >= 0)
					data->temp[j][i] =
						nct6683_पढ़ो(data, reg);
			पूर्ण
		पूर्ण

		/* Measured fan speeds and limits */
		क्रम (i = 0; i < ARRAY_SIZE(data->rpm); i++) अणु
			अगर (!(data->have_fan & (1 << i)))
				जारी;

			data->rpm[i] = nct6683_पढ़ो16(data,
						NCT6683_REG_FAN_RPM(i));
			data->fan_min[i] = nct6683_पढ़ो16(data,
						NCT6683_REG_FAN_MIN(i));
		पूर्ण

		nct6683_update_pwm(dev);

		data->last_updated = jअगरfies;
		data->valid = true;
	पूर्ण

	mutex_unlock(&data->update_lock);
	वापस data;
पूर्ण

/*
 * Sysfs callback functions
 */
अटल sमाप_प्रकार
show_in_label(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sattr = to_sensor_dev_attr(attr);
	काष्ठा nct6683_data *data = nct6683_update_device(dev);
	पूर्णांक nr = sattr->index;

	वापस प्र_लिखो(buf, "%s\n", nct6683_mon_label[data->in_src[nr]]);
पूर्ण

अटल sमाप_प्रकार
show_in_reg(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	काष्ठा nct6683_data *data = nct6683_update_device(dev);
	पूर्णांक index = sattr->index;
	पूर्णांक nr = sattr->nr;

	वापस प्र_लिखो(buf, "%ld\n",
		       in_from_reg(data->in[index][nr], data->in_index[index]));
पूर्ण

अटल umode_t nct6683_in_is_visible(काष्ठा kobject *kobj,
				     काष्ठा attribute *attr, पूर्णांक index)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा nct6683_data *data = dev_get_drvdata(dev);
	पूर्णांक nr = index % 4;	/* attribute */

	/*
	 * Voltage limits exist क्रम Intel boards,
	 * but रेजिस्टर location and encoding is unknown
	 */
	अगर ((nr == 2 || nr == 3) &&
	    data->customer_id == NCT6683_CUSTOMER_ID_INTEL)
		वापस 0;

	वापस attr->mode;
पूर्ण

SENSOR_TEMPLATE(in_label, "in%d_label", S_IRUGO, show_in_label, शून्य, 0);
SENSOR_TEMPLATE_2(in_input, "in%d_input", S_IRUGO, show_in_reg, शून्य, 0, 0);
SENSOR_TEMPLATE_2(in_min, "in%d_min", S_IRUGO, show_in_reg, शून्य, 0, 1);
SENSOR_TEMPLATE_2(in_max, "in%d_max", S_IRUGO, show_in_reg, शून्य, 0, 2);

अटल काष्ठा sensor_device_ढाँचा *nct6683_attributes_in_ढाँचा[] = अणु
	&sensor_dev_ढाँचा_in_label,
	&sensor_dev_ढाँचा_in_input,
	&sensor_dev_ढाँचा_in_min,
	&sensor_dev_ढाँचा_in_max,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा sensor_ढाँचा_group nct6683_in_ढाँचा_group = अणु
	.ढाँचाs = nct6683_attributes_in_ढाँचा,
	.is_visible = nct6683_in_is_visible,
पूर्ण;

अटल sमाप_प्रकार
show_fan(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sattr = to_sensor_dev_attr(attr);
	काष्ठा nct6683_data *data = nct6683_update_device(dev);

	वापस प्र_लिखो(buf, "%d\n", data->rpm[sattr->index]);
पूर्ण

अटल sमाप_प्रकार
show_fan_min(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nct6683_data *data = nct6683_update_device(dev);
	काष्ठा sensor_device_attribute *sattr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sattr->index;

	वापस प्र_लिखो(buf, "%d\n", data->fan_min[nr]);
पूर्ण

अटल sमाप_प्रकार
show_fan_pulses(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sattr = to_sensor_dev_attr(attr);
	काष्ठा nct6683_data *data = nct6683_update_device(dev);

	वापस प्र_लिखो(buf, "%d\n",
		       ((data->fanin_cfg[sattr->index] >> 5) & 0x03) + 1);
पूर्ण

अटल umode_t nct6683_fan_is_visible(काष्ठा kobject *kobj,
				      काष्ठा attribute *attr, पूर्णांक index)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा nct6683_data *data = dev_get_drvdata(dev);
	पूर्णांक fan = index / 3;	/* fan index */
	पूर्णांक nr = index % 3;	/* attribute index */

	अगर (!(data->have_fan & (1 << fan)))
		वापस 0;

	/*
	 * Intel may have minimum fan speed limits,
	 * but रेजिस्टर location and encoding are unknown.
	 */
	अगर (nr == 2 && data->customer_id == NCT6683_CUSTOMER_ID_INTEL)
		वापस 0;

	वापस attr->mode;
पूर्ण

SENSOR_TEMPLATE(fan_input, "fan%d_input", S_IRUGO, show_fan, शून्य, 0);
SENSOR_TEMPLATE(fan_pulses, "fan%d_pulses", S_IRUGO, show_fan_pulses, शून्य, 0);
SENSOR_TEMPLATE(fan_min, "fan%d_min", S_IRUGO, show_fan_min, शून्य, 0);

/*
 * nct6683_fan_is_visible uses the index पूर्णांकo the following array
 * to determine अगर attributes should be created or not.
 * Any change in order or content must be matched.
 */
अटल काष्ठा sensor_device_ढाँचा *nct6683_attributes_fan_ढाँचा[] = अणु
	&sensor_dev_ढाँचा_fan_input,
	&sensor_dev_ढाँचा_fan_pulses,
	&sensor_dev_ढाँचा_fan_min,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा sensor_ढाँचा_group nct6683_fan_ढाँचा_group = अणु
	.ढाँचाs = nct6683_attributes_fan_ढाँचा,
	.is_visible = nct6683_fan_is_visible,
	.base = 1,
पूर्ण;

अटल sमाप_प्रकार
show_temp_label(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sattr = to_sensor_dev_attr(attr);
	काष्ठा nct6683_data *data = nct6683_update_device(dev);
	पूर्णांक nr = sattr->index;

	वापस प्र_लिखो(buf, "%s\n", nct6683_mon_label[data->temp_src[nr]]);
पूर्ण

अटल sमाप_प्रकार
show_temp8(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	काष्ठा nct6683_data *data = nct6683_update_device(dev);
	पूर्णांक index = sattr->index;
	पूर्णांक nr = sattr->nr;

	वापस प्र_लिखो(buf, "%d\n", data->temp[index][nr] * 1000);
पूर्ण

अटल sमाप_प्रकार
show_temp_hyst(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sattr = to_sensor_dev_attr(attr);
	काष्ठा nct6683_data *data = nct6683_update_device(dev);
	पूर्णांक nr = sattr->index;
	पूर्णांक temp = data->temp[1][nr] - data->temp[2][nr];

	वापस प्र_लिखो(buf, "%d\n", temp * 1000);
पूर्ण

अटल sमाप_प्रकार
show_temp16(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sattr = to_sensor_dev_attr(attr);
	काष्ठा nct6683_data *data = nct6683_update_device(dev);
	पूर्णांक index = sattr->index;

	वापस प्र_लिखो(buf, "%d\n", (data->temp_in[index] / 128) * 500);
पूर्ण

/*
 * Temperature sensor type is determined by temperature source
 * and can not be modअगरied.
 * 0x02..0x07: Thermal diode
 * 0x08..0x18: Thermistor
 * 0x20..0x2b: Intel PECI
 * 0x42..0x49: AMD TSI
 * Others are unspecअगरied (not visible)
 */

अटल पूर्णांक get_temp_type(u8 src)
अणु
	अगर (src >= 0x02 && src <= 0x07)
		वापस 3;	/* thermal diode */
	अन्यथा अगर (src >= 0x08 && src <= 0x18)
		वापस 4;	/* thermistor */
	अन्यथा अगर (src >= 0x20 && src <= 0x2b)
		वापस 6;	/* PECI */
	अन्यथा अगर (src >= 0x42 && src <= 0x49)
		वापस 5;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार
show_temp_type(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nct6683_data *data = nct6683_update_device(dev);
	काष्ठा sensor_device_attribute *sattr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sattr->index;
	वापस प्र_लिखो(buf, "%d\n", get_temp_type(data->temp_src[nr]));
पूर्ण

अटल umode_t nct6683_temp_is_visible(काष्ठा kobject *kobj,
				       काष्ठा attribute *attr, पूर्णांक index)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा nct6683_data *data = dev_get_drvdata(dev);
	पूर्णांक temp = index / 7;	/* temp index */
	पूर्णांक nr = index % 7;	/* attribute index */

	/*
	 * Intel करोes not have low temperature limits or temperature hysteresis
	 * रेजिस्टरs, or at least रेजिस्टर location and encoding is unknown.
	 */
	अगर ((nr == 2 || nr == 4) &&
	    data->customer_id == NCT6683_CUSTOMER_ID_INTEL)
		वापस 0;

	अगर (nr == 6 && get_temp_type(data->temp_src[temp]) == 0)
		वापस 0;				/* type */

	वापस attr->mode;
पूर्ण

SENSOR_TEMPLATE(temp_input, "temp%d_input", S_IRUGO, show_temp16, शून्य, 0);
SENSOR_TEMPLATE(temp_label, "temp%d_label", S_IRUGO, show_temp_label, शून्य, 0);
SENSOR_TEMPLATE_2(temp_min, "temp%d_min", S_IRUGO, show_temp8, शून्य, 0, 0);
SENSOR_TEMPLATE_2(temp_max, "temp%d_max", S_IRUGO, show_temp8, शून्य, 0, 1);
SENSOR_TEMPLATE(temp_max_hyst, "temp%d_max_hyst", S_IRUGO, show_temp_hyst, शून्य,
		0);
SENSOR_TEMPLATE_2(temp_crit, "temp%d_crit", S_IRUGO, show_temp8, शून्य, 0, 3);
SENSOR_TEMPLATE(temp_type, "temp%d_type", S_IRUGO, show_temp_type, शून्य, 0);

/*
 * nct6683_temp_is_visible uses the index पूर्णांकo the following array
 * to determine अगर attributes should be created or not.
 * Any change in order or content must be matched.
 */
अटल काष्ठा sensor_device_ढाँचा *nct6683_attributes_temp_ढाँचा[] = अणु
	&sensor_dev_ढाँचा_temp_input,
	&sensor_dev_ढाँचा_temp_label,
	&sensor_dev_ढाँचा_temp_min,		/* 2 */
	&sensor_dev_ढाँचा_temp_max,		/* 3 */
	&sensor_dev_ढाँचा_temp_max_hyst,	/* 4 */
	&sensor_dev_ढाँचा_temp_crit,		/* 5 */
	&sensor_dev_ढाँचा_temp_type,		/* 6 */
	शून्य
पूर्ण;

अटल स्थिर काष्ठा sensor_ढाँचा_group nct6683_temp_ढाँचा_group = अणु
	.ढाँचाs = nct6683_attributes_temp_ढाँचा,
	.is_visible = nct6683_temp_is_visible,
	.base = 1,
पूर्ण;

अटल sमाप_प्रकार
show_pwm(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nct6683_data *data = nct6683_update_device(dev);
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	पूर्णांक index = sattr->index;

	वापस प्र_लिखो(buf, "%d\n", data->pwm[index]);
पूर्ण

अटल sमाप_प्रकार
store_pwm(काष्ठा device *dev, काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
	  माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	काष्ठा nct6683_data *data = dev_get_drvdata(dev);
	पूर्णांक index = sattr->index;
	अचिन्हित दीर्घ val;

	अगर (kम_से_अदीर्घ(buf, 10, &val) || val > 255)
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	nct6683_ग_लिखो(data, NCT6683_REG_FAN_CFG_CTRL, NCT6683_FAN_CFG_REQ);
	usleep_range(1000, 2000);
	nct6683_ग_लिखो(data, NCT6683_REG_PWM_WRITE(index), val);
	nct6683_ग_लिखो(data, NCT6683_REG_FAN_CFG_CTRL, NCT6683_FAN_CFG_DONE);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

SENSOR_TEMPLATE(pwm, "pwm%d", S_IRUGO, show_pwm, store_pwm, 0);

अटल umode_t nct6683_pwm_is_visible(काष्ठा kobject *kobj,
				      काष्ठा attribute *attr, पूर्णांक index)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा nct6683_data *data = dev_get_drvdata(dev);
	पूर्णांक pwm = index;	/* pwm index */

	अगर (!(data->have_pwm & (1 << pwm)))
		वापस 0;

	/* Only update pwm values क्रम Mitac boards */
	अगर (data->customer_id == NCT6683_CUSTOMER_ID_MITAC)
		वापस attr->mode | S_IWUSR;

	वापस attr->mode;
पूर्ण

अटल काष्ठा sensor_device_ढाँचा *nct6683_attributes_pwm_ढाँचा[] = अणु
	&sensor_dev_ढाँचा_pwm,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा sensor_ढाँचा_group nct6683_pwm_ढाँचा_group = अणु
	.ढाँचाs = nct6683_attributes_pwm_ढाँचा,
	.is_visible = nct6683_pwm_is_visible,
	.base = 1,
पूर्ण;

अटल sमाप_प्रकार
beep_enable_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nct6683_data *data = dev_get_drvdata(dev);
	पूर्णांक ret;
	u8 reg;

	mutex_lock(&data->update_lock);

	ret = superio_enter(data->sioreg);
	अगर (ret)
		जाओ error;
	superio_select(data->sioreg, NCT6683_LD_HWM);
	reg = superio_inb(data->sioreg, NCT6683_REG_CR_BEEP);
	superio_निकास(data->sioreg);

	mutex_unlock(&data->update_lock);

	वापस प्र_लिखो(buf, "%u\n", !!(reg & NCT6683_CR_BEEP_MASK));

error:
	mutex_unlock(&data->update_lock);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार
beep_enable_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा nct6683_data *data = dev_get_drvdata(dev);
	अचिन्हित दीर्घ val;
	u8 reg;
	पूर्णांक ret;

	अगर (kम_से_अदीर्घ(buf, 10, &val) || (val != 0 && val != 1))
		वापस -EINVAL;

	mutex_lock(&data->update_lock);

	ret = superio_enter(data->sioreg);
	अगर (ret) अणु
		count = ret;
		जाओ error;
	पूर्ण

	superio_select(data->sioreg, NCT6683_LD_HWM);
	reg = superio_inb(data->sioreg, NCT6683_REG_CR_BEEP);
	अगर (val)
		reg |= NCT6683_CR_BEEP_MASK;
	अन्यथा
		reg &= ~NCT6683_CR_BEEP_MASK;
	superio_outb(data->sioreg, NCT6683_REG_CR_BEEP, reg);
	superio_निकास(data->sioreg);
error:
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

/* Case खोलो detection */

अटल sमाप_प्रकार
पूर्णांकrusion0_alarm_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		      अक्षर *buf)
अणु
	काष्ठा nct6683_data *data = dev_get_drvdata(dev);
	पूर्णांक ret;
	u8 reg;

	mutex_lock(&data->update_lock);

	ret = superio_enter(data->sioreg);
	अगर (ret)
		जाओ error;
	superio_select(data->sioreg, NCT6683_LD_ACPI);
	reg = superio_inb(data->sioreg, NCT6683_REG_CR_CASEOPEN);
	superio_निकास(data->sioreg);

	mutex_unlock(&data->update_lock);

	वापस प्र_लिखो(buf, "%u\n", !(reg & NCT6683_CR_CASEOPEN_MASK));

error:
	mutex_unlock(&data->update_lock);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार
पूर्णांकrusion0_alarm_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा nct6683_data *data = dev_get_drvdata(dev);
	अचिन्हित दीर्घ val;
	u8 reg;
	पूर्णांक ret;

	अगर (kम_से_अदीर्घ(buf, 10, &val) || val != 0)
		वापस -EINVAL;

	mutex_lock(&data->update_lock);

	/*
	 * Use CR रेजिस्टरs to clear हालखोलो status.
	 * Caseखोलो is activ low, clear by writing 1 पूर्णांकo the रेजिस्टर.
	 */

	ret = superio_enter(data->sioreg);
	अगर (ret) अणु
		count = ret;
		जाओ error;
	पूर्ण

	superio_select(data->sioreg, NCT6683_LD_ACPI);
	reg = superio_inb(data->sioreg, NCT6683_REG_CR_CASEOPEN);
	reg |= NCT6683_CR_CASEOPEN_MASK;
	superio_outb(data->sioreg, NCT6683_REG_CR_CASEOPEN, reg);
	reg &= ~NCT6683_CR_CASEOPEN_MASK;
	superio_outb(data->sioreg, NCT6683_REG_CR_CASEOPEN, reg);
	superio_निकास(data->sioreg);

	data->valid = false;	/* Force cache refresh */
error:
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(पूर्णांकrusion0_alarm);
अटल DEVICE_ATTR_RW(beep_enable);

अटल काष्ठा attribute *nct6683_attributes_other[] = अणु
	&dev_attr_पूर्णांकrusion0_alarm.attr,
	&dev_attr_beep_enable.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group nct6683_group_other = अणु
	.attrs = nct6683_attributes_other,
पूर्ण;

/* Get the monitoring functions started */
अटल अंतरभूत व्योम nct6683_init_device(काष्ठा nct6683_data *data)
अणु
	u8 पंचांगp;

	/* Start hardware monitoring अगर needed */
	पंचांगp = nct6683_पढ़ो(data, NCT6683_HWM_CFG);
	अगर (!(पंचांगp & 0x80))
		nct6683_ग_लिखो(data, NCT6683_HWM_CFG, पंचांगp | 0x80);
पूर्ण

/*
 * There are a total of 24 fan inमाला_दो. Each can be configured as input
 * or as output. A maximum of 16 inमाला_दो and 8 outमाला_दो is configurable.
 */
अटल व्योम
nct6683_setup_fans(काष्ठा nct6683_data *data)
अणु
	पूर्णांक i;
	u8 reg;

	क्रम (i = 0; i < NCT6683_NUM_REG_FAN; i++) अणु
		reg = nct6683_पढ़ो(data, NCT6683_REG_FANIN_CFG(i));
		अगर (reg & 0x80)
			data->have_fan |= 1 << i;
		data->fanin_cfg[i] = reg;
	पूर्ण
	क्रम (i = 0; i < NCT6683_NUM_REG_PWM; i++) अणु
		reg = nct6683_पढ़ो(data, NCT6683_REG_FANOUT_CFG(i));
		अगर (reg & 0x80)
			data->have_pwm |= 1 << i;
		data->fanout_cfg[i] = reg;
	पूर्ण
पूर्ण

/*
 * Translation from monitoring रेजिस्टर to temperature and voltage attributes
 * ==========================================================================
 *
 * There are a total of 32 monitoring रेजिस्टरs. Each can be asचिन्हित to either
 * a temperature or voltage monitoring source.
 * NCT6683_REG_MON_CFG(x) defines assignment क्रम each monitoring source.
 *
 * Temperature and voltage attribute mapping is determined by walking through
 * the NCT6683_REG_MON_CFG रेजिस्टरs. If the asचिन्हित source is
 * a temperature, temp_index[n] is set to the monitor रेजिस्टर index, and
 * temp_src[n] is set to the temperature source. If the asचिन्हित source is
 * a voltage, the respective values are stored in in_index[] and in_src[],
 * respectively.
 */

अटल व्योम nct6683_setup_sensors(काष्ठा nct6683_data *data)
अणु
	u8 reg;
	पूर्णांक i;

	data->temp_num = 0;
	data->in_num = 0;
	क्रम (i = 0; i < NCT6683_NUM_REG_MON; i++) अणु
		reg = nct6683_पढ़ो(data, NCT6683_REG_MON_CFG(i)) & 0x7f;
		/* Ignore invalid assignments */
		अगर (reg >= NUM_MON_LABELS)
			जारी;
		/* Skip अगर disabled or reserved */
		अगर (nct6683_mon_label[reg] == शून्य)
			जारी;
		अगर (reg < MON_VOLTAGE_START) अणु
			data->temp_index[data->temp_num] = i;
			data->temp_src[data->temp_num] = reg;
			data->temp_num++;
		पूर्ण अन्यथा अणु
			data->in_index[data->in_num] = i;
			data->in_src[data->in_num] = reg;
			data->in_num++;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक nct6683_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा nct6683_sio_data *sio_data = dev->platक्रमm_data;
	काष्ठा attribute_group *group;
	काष्ठा nct6683_data *data;
	काष्ठा device *hwmon_dev;
	काष्ठा resource *res;
	पूर्णांक groups = 0;
	अक्षर build[16];

	res = platक्रमm_get_resource(pdev, IORESOURCE_IO, 0);
	अगर (!devm_request_region(dev, res->start, IOREGION_LENGTH, DRVNAME))
		वापस -EBUSY;

	data = devm_kzalloc(dev, माप(काष्ठा nct6683_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->kind = sio_data->kind;
	data->sioreg = sio_data->sioreg;
	data->addr = res->start;
	mutex_init(&data->update_lock);
	platक्रमm_set_drvdata(pdev, data);

	data->customer_id = nct6683_पढ़ो16(data, NCT6683_REG_CUSTOMER_ID);

	/* By शेष only instantiate driver अगर the customer ID is known */
	चयन (data->customer_id) अणु
	हाल NCT6683_CUSTOMER_ID_INTEL:
		अवरोध;
	हाल NCT6683_CUSTOMER_ID_MITAC:
		अवरोध;
	हाल NCT6683_CUSTOMER_ID_MSI:
		अवरोध;
	हाल NCT6683_CUSTOMER_ID_ASROCK:
		अवरोध;
	शेष:
		अगर (!क्रमce)
			वापस -ENODEV;
	पूर्ण

	nct6683_init_device(data);
	nct6683_setup_fans(data);
	nct6683_setup_sensors(data);

	/* Register sysfs hooks */

	अगर (data->have_pwm) अणु
		group = nct6683_create_attr_group(dev,
						  &nct6683_pwm_ढाँचा_group,
						  fls(data->have_pwm));
		अगर (IS_ERR(group))
			वापस PTR_ERR(group);
		data->groups[groups++] = group;
	पूर्ण

	अगर (data->in_num) अणु
		group = nct6683_create_attr_group(dev,
						  &nct6683_in_ढाँचा_group,
						  data->in_num);
		अगर (IS_ERR(group))
			वापस PTR_ERR(group);
		data->groups[groups++] = group;
	पूर्ण

	अगर (data->have_fan) अणु
		group = nct6683_create_attr_group(dev,
						  &nct6683_fan_ढाँचा_group,
						  fls(data->have_fan));
		अगर (IS_ERR(group))
			वापस PTR_ERR(group);
		data->groups[groups++] = group;
	पूर्ण

	अगर (data->temp_num) अणु
		group = nct6683_create_attr_group(dev,
						  &nct6683_temp_ढाँचा_group,
						  data->temp_num);
		अगर (IS_ERR(group))
			वापस PTR_ERR(group);
		data->groups[groups++] = group;
	पूर्ण
	data->groups[groups++] = &nct6683_group_other;

	अगर (data->customer_id == NCT6683_CUSTOMER_ID_INTEL)
		scnम_लिखो(build, माप(build), "%02x/%02x/%02x",
			  nct6683_पढ़ो(data, NCT6683_REG_BUILD_MONTH),
			  nct6683_पढ़ो(data, NCT6683_REG_BUILD_DAY),
			  nct6683_पढ़ो(data, NCT6683_REG_BUILD_YEAR));
	अन्यथा
		scnम_लिखो(build, माप(build), "%02d/%02d/%02d",
			  nct6683_पढ़ो(data, NCT6683_REG_BUILD_MONTH),
			  nct6683_पढ़ो(data, NCT6683_REG_BUILD_DAY),
			  nct6683_पढ़ो(data, NCT6683_REG_BUILD_YEAR));

	dev_info(dev, "%s EC firmware version %d.%d build %s\n",
		 nct6683_chip_names[data->kind],
		 nct6683_पढ़ो(data, NCT6683_REG_VERSION_HI),
		 nct6683_पढ़ो(data, NCT6683_REG_VERSION_LO),
		 build);

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev,
			nct6683_device_names[data->kind], data, data->groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक nct6683_suspend(काष्ठा device *dev)
अणु
	काष्ठा nct6683_data *data = nct6683_update_device(dev);

	mutex_lock(&data->update_lock);
	data->hwm_cfg = nct6683_पढ़ो(data, NCT6683_HWM_CFG);
	mutex_unlock(&data->update_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक nct6683_resume(काष्ठा device *dev)
अणु
	काष्ठा nct6683_data *data = dev_get_drvdata(dev);

	mutex_lock(&data->update_lock);

	nct6683_ग_लिखो(data, NCT6683_HWM_CFG, data->hwm_cfg);

	/* Force re-पढ़ोing all values */
	data->valid = false;
	mutex_unlock(&data->update_lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops nct6683_dev_pm_ops = अणु
	.suspend = nct6683_suspend,
	.resume = nct6683_resume,
	.मुक्तze = nct6683_suspend,
	.restore = nct6683_resume,
पूर्ण;

#घोषणा NCT6683_DEV_PM_OPS	(&nct6683_dev_pm_ops)
#अन्यथा
#घोषणा NCT6683_DEV_PM_OPS	शून्य
#पूर्ण_अगर /* CONFIG_PM */

अटल काष्ठा platक्रमm_driver nct6683_driver = अणु
	.driver = अणु
		.name	= DRVNAME,
		.pm	= NCT6683_DEV_PM_OPS,
	पूर्ण,
	.probe		= nct6683_probe,
पूर्ण;

अटल पूर्णांक __init nct6683_find(पूर्णांक sioaddr, काष्ठा nct6683_sio_data *sio_data)
अणु
	पूर्णांक addr;
	u16 val;
	पूर्णांक err;

	err = superio_enter(sioaddr);
	अगर (err)
		वापस err;

	val = (superio_inb(sioaddr, SIO_REG_DEVID) << 8)
	       | superio_inb(sioaddr, SIO_REG_DEVID + 1);

	चयन (val & SIO_ID_MASK) अणु
	हाल SIO_NCT6683_ID:
		sio_data->kind = nct6683;
		अवरोध;
	हाल SIO_NCT6686_ID:
		sio_data->kind = nct6686;
		अवरोध;
	हाल SIO_NCT6687_ID:
		sio_data->kind = nct6687;
		अवरोध;
	शेष:
		अगर (val != 0xffff)
			pr_debug("unsupported chip ID: 0x%04x\n", val);
		जाओ fail;
	पूर्ण

	/* We have a known chip, find the HWM I/O address */
	superio_select(sioaddr, NCT6683_LD_HWM);
	val = (superio_inb(sioaddr, SIO_REG_ADDR) << 8)
	    | superio_inb(sioaddr, SIO_REG_ADDR + 1);
	addr = val & IOREGION_ALIGNMENT;
	अगर (addr == 0) अणु
		pr_err("EC base I/O port unconfigured\n");
		जाओ fail;
	पूर्ण

	/* Activate logical device अगर needed */
	val = superio_inb(sioaddr, SIO_REG_ENABLE);
	अगर (!(val & 0x01)) अणु
		pr_warn("Forcibly enabling EC access. Data may be unusable.\n");
		superio_outb(sioaddr, SIO_REG_ENABLE, val | 0x01);
	पूर्ण

	superio_निकास(sioaddr);
	pr_info("Found %s or compatible chip at %#x:%#x\n",
		nct6683_chip_names[sio_data->kind], sioaddr, addr);
	sio_data->sioreg = sioaddr;

	वापस addr;

fail:
	superio_निकास(sioaddr);
	वापस -ENODEV;
पूर्ण

/*
 * when Super-I/O functions move to a separate file, the Super-I/O
 * bus will manage the lअगरeसमय of the device and this module will only keep
 * track of the nct6683 driver. But since we use platक्रमm_device_alloc(), we
 * must keep track of the device
 */
अटल काष्ठा platक्रमm_device *pdev[2];

अटल पूर्णांक __init sensors_nct6683_init(व्योम)
अणु
	काष्ठा nct6683_sio_data sio_data;
	पूर्णांक sioaddr[2] = अणु 0x2e, 0x4e पूर्ण;
	काष्ठा resource res;
	bool found = false;
	पूर्णांक address;
	पूर्णांक i, err;

	err = platक्रमm_driver_रेजिस्टर(&nct6683_driver);
	अगर (err)
		वापस err;

	/*
	 * initialize sio_data->kind and sio_data->sioreg.
	 *
	 * when Super-I/O functions move to a separate file, the Super-I/O
	 * driver will probe 0x2e and 0x4e and स्वतः-detect the presence of a
	 * nct6683 hardware monitor, and call probe()
	 */
	क्रम (i = 0; i < ARRAY_SIZE(pdev); i++) अणु
		address = nct6683_find(sioaddr[i], &sio_data);
		अगर (address <= 0)
			जारी;

		found = true;

		pdev[i] = platक्रमm_device_alloc(DRVNAME, address);
		अगर (!pdev[i]) अणु
			err = -ENOMEM;
			जाओ निकास_device_unरेजिस्टर;
		पूर्ण

		err = platक्रमm_device_add_data(pdev[i], &sio_data,
					       माप(काष्ठा nct6683_sio_data));
		अगर (err)
			जाओ निकास_device_put;

		स_रखो(&res, 0, माप(res));
		res.name = DRVNAME;
		res.start = address + IOREGION_OFFSET;
		res.end = address + IOREGION_OFFSET + IOREGION_LENGTH - 1;
		res.flags = IORESOURCE_IO;

		err = acpi_check_resource_conflict(&res);
		अगर (err) अणु
			platक्रमm_device_put(pdev[i]);
			pdev[i] = शून्य;
			जारी;
		पूर्ण

		err = platक्रमm_device_add_resources(pdev[i], &res, 1);
		अगर (err)
			जाओ निकास_device_put;

		/* platक्रमm_device_add calls probe() */
		err = platक्रमm_device_add(pdev[i]);
		अगर (err)
			जाओ निकास_device_put;
	पूर्ण
	अगर (!found) अणु
		err = -ENODEV;
		जाओ निकास_unरेजिस्टर;
	पूर्ण

	वापस 0;

निकास_device_put:
	platक्रमm_device_put(pdev[i]);
निकास_device_unरेजिस्टर:
	जबतक (--i >= 0) अणु
		अगर (pdev[i])
			platक्रमm_device_unरेजिस्टर(pdev[i]);
	पूर्ण
निकास_unरेजिस्टर:
	platक्रमm_driver_unरेजिस्टर(&nct6683_driver);
	वापस err;
पूर्ण

अटल व्योम __निकास sensors_nct6683_निकास(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(pdev); i++) अणु
		अगर (pdev[i])
			platक्रमm_device_unरेजिस्टर(pdev[i]);
	पूर्ण
	platक्रमm_driver_unरेजिस्टर(&nct6683_driver);
पूर्ण

MODULE_AUTHOR("Guenter Roeck <linux@roeck-us.net>");
MODULE_DESCRIPTION("NCT6683D driver");
MODULE_LICENSE("GPL");

module_init(sensors_nct6683_init);
module_निकास(sensors_nct6683_निकास);
