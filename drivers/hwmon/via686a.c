<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * via686a.c - Part of lm_sensors, Linux kernel modules
 *	       क्रम hardware monitoring
 *
 * Copyright (c) 1998 - 2002  Froकरो Looijaard <froकरोl@dds.nl>,
 *			      Kyथघsti Mथअlkki <kmalkki@cc.hut.fi>,
 *			      Mark Studebaker <mdsxyz123@yahoo.com>,
 *			      and Bob Dougherty <bobd@stanक्रमd.edu>
 *
 * (Some conversion-factor data were contributed by Jonathan Teh Soon Yew
 * <j.teh@iname.com> and Alex van Kaam <darkside@chello.nl>.)
 */

/*
 * Supports the Via VT82C686A, VT82C686B south bridges.
 * Reports all as a 686A.
 * Warning - only supports a single device.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/mutex.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/acpi.h>
#समावेश <linux/पन.स>

/*
 * If क्रमce_addr is set to anything dअगरferent from 0, we क्रमcibly enable
 * the device at the given address.
 */
अटल अचिन्हित लघु क्रमce_addr;
module_param(क्रमce_addr, uलघु, 0);
MODULE_PARM_DESC(क्रमce_addr,
		 "Initialize the base address of the sensors");

अटल काष्ठा platक्रमm_device *pdev;

/*
 * The Via 686a southbridge has a LM78-like chip पूर्णांकegrated on the same IC.
 * This driver is a customized copy of lm78.c
 */

/* Many VIA686A स्थिरants specअगरied below */

/* Length of ISA address segment */
#घोषणा VIA686A_EXTENT		0x80
#घोषणा VIA686A_BASE_REG	0x70
#घोषणा VIA686A_ENABLE_REG	0x74

/* The VIA686A रेजिस्टरs */
/* ins numbered 0-4 */
#घोषणा VIA686A_REG_IN_MAX(nr)	(0x2b + ((nr) * 2))
#घोषणा VIA686A_REG_IN_MIN(nr)	(0x2c + ((nr) * 2))
#घोषणा VIA686A_REG_IN(nr)	(0x22 + (nr))

/* fans numbered 1-2 */
#घोषणा VIA686A_REG_FAN_MIN(nr)	(0x3a + (nr))
#घोषणा VIA686A_REG_FAN(nr)	(0x28 + (nr))

/* temps numbered 1-3 */
अटल स्थिर u8 VIA686A_REG_TEMP[]	= अणु 0x20, 0x21, 0x1f पूर्ण;
अटल स्थिर u8 VIA686A_REG_TEMP_OVER[]	= अणु 0x39, 0x3d, 0x1d पूर्ण;
अटल स्थिर u8 VIA686A_REG_TEMP_HYST[]	= अणु 0x3a, 0x3e, 0x1e पूर्ण;
/* bits 7-6 */
#घोषणा VIA686A_REG_TEMP_LOW1	0x4b
/* 2 = bits 5-4, 3 = bits 7-6 */
#घोषणा VIA686A_REG_TEMP_LOW23	0x49

#घोषणा VIA686A_REG_ALARM1	0x41
#घोषणा VIA686A_REG_ALARM2	0x42
#घोषणा VIA686A_REG_FANDIV	0x47
#घोषणा VIA686A_REG_CONFIG	0x40
/*
 * The following रेजिस्टर sets temp पूर्णांकerrupt mode (bits 1-0 क्रम temp1,
 * 3-2 क्रम temp2, 5-4 क्रम temp3).  Modes are:
 * 00 पूर्णांकerrupt stays as दीर्घ as value is out-of-range
 * 01 पूर्णांकerrupt is cleared once रेजिस्टर is पढ़ो (शेष)
 * 10 comparator mode- like 00, but ignores hysteresis
 * 11 same as 00
 */
#घोषणा VIA686A_REG_TEMP_MODE		0x4b
/* We'll just assume that you want to set all 3 simultaneously: */
#घोषणा VIA686A_TEMP_MODE_MASK		0x3F
#घोषणा VIA686A_TEMP_MODE_CONTINUOUS	0x00

/*
 * Conversions. Limit checking is only करोne on the TO_REG
 * variants.
 *
 ******** VOLTAGE CONVERSIONS (Bob Dougherty) ********
 * From HWMon.cpp (Copyright 1998-2000 Jonathan Teh Soon Yew):
 * voltagefactor[0]=1.25/2628; (2628/1.25=2102.4)   // Vccp
 * voltagefactor[1]=1.25/2628; (2628/1.25=2102.4)   // +2.5V
 * voltagefactor[2]=1.67/2628; (2628/1.67=1573.7)   // +3.3V
 * voltagefactor[3]=2.6/2628;  (2628/2.60=1010.8)   // +5V
 * voltagefactor[4]=6.3/2628;  (2628/6.30=417.14)   // +12V
 * in[i]=(data[i+2]*25.0+133)*voltagefactor[i];
 * That is:
 * volts = (25*regVal+133)*factor
 * regVal = (volts/factor-133)/25
 * (These conversions were contributed by Jonathan Teh Soon Yew
 * <j.teh@iname.com>)
 */
अटल अंतरभूत u8 IN_TO_REG(दीर्घ val, पूर्णांक in_num)
अणु
	/*
	 * To aव्योम भग्नing poपूर्णांक, we multiply स्थिरants by 10 (100 क्रम +12V).
	 * Rounding is करोne (120500 is actually 133000 - 12500).
	 * Remember that val is expressed in 0.001V/bit, which is why we भागide
	 * by an additional 10000 (100000 क्रम +12V): 1000 क्रम val and 10 (100)
	 * क्रम the स्थिरants.
	 */
	अगर (in_num <= 1)
		वापस (u8) clamp_val((val * 21024 - 1205000) / 250000, 0, 255);
	अन्यथा अगर (in_num == 2)
		वापस (u8) clamp_val((val * 15737 - 1205000) / 250000, 0, 255);
	अन्यथा अगर (in_num == 3)
		वापस (u8) clamp_val((val * 10108 - 1205000) / 250000, 0, 255);
	अन्यथा
		वापस (u8) clamp_val((val * 41714 - 12050000) / 2500000, 0,
				      255);
पूर्ण

अटल अंतरभूत दीर्घ IN_FROM_REG(u8 val, पूर्णांक in_num)
अणु
	/*
	 * To aव्योम भग्नing poपूर्णांक, we multiply स्थिरants by 10 (100 क्रम +12V).
	 * We also multiply them by 1000 because we want 0.001V/bit क्रम the
	 * output value. Rounding is करोne.
	 */
	अगर (in_num <= 1)
		वापस (दीर्घ) ((250000 * val + 1330000 + 21024 / 2) / 21024);
	अन्यथा अगर (in_num == 2)
		वापस (दीर्घ) ((250000 * val + 1330000 + 15737 / 2) / 15737);
	अन्यथा अगर (in_num == 3)
		वापस (दीर्घ) ((250000 * val + 1330000 + 10108 / 2) / 10108);
	अन्यथा
		वापस (दीर्घ) ((2500000 * val + 13300000 + 41714 / 2) / 41714);
पूर्ण

/********* FAN RPM CONVERSIONS ********/
/*
 * Higher रेजिस्टर values = slower fans (the fan's strobe gates a counter).
 * But this chip saturates back at 0, not at 255 like all the other chips.
 * So, 0 means 0 RPM
 */
अटल अंतरभूत u8 FAN_TO_REG(दीर्घ rpm, पूर्णांक भाग)
अणु
	अगर (rpm == 0)
		वापस 0;
	rpm = clamp_val(rpm, 1, 1000000);
	वापस clamp_val((1350000 + rpm * भाग / 2) / (rpm * भाग), 1, 255);
पूर्ण

#घोषणा FAN_FROM_REG(val, भाग) ((val) == 0 ? 0 : (val) == 255 ? 0 : 1350000 / \
				((val) * (भाग)))

/******** TEMP CONVERSIONS (Bob Dougherty) *********/
/*
 * linear fits from HWMon.cpp (Copyright 1998-2000 Jonathan Teh Soon Yew)
 *	अगर(temp<169)
 *		वापस द्विगुन(temp)*0.427-32.08;
 *	अन्यथा अगर(temp>=169 && temp<=202)
 *		वापस द्विगुन(temp)*0.582-58.16;
 *	अन्यथा
 *		वापस द्विगुन(temp)*0.924-127.33;
 *
 * A fअगरth-order polynomial fits the unofficial data (provided by Alex van
 * Kaam <darkside@chello.nl>) a bit better.  It also give more reasonable
 * numbers on my machine (ie. they agree with what my BIOS tells me).
 * Here's the fअगरth-order fit to the 8-bit data:
 * temp = 1.625093e-10*val^5 - 1.001632e-07*val^4 + 2.457653e-05*val^3 -
 *	2.967619e-03*val^2 + 2.175144e-01*val - 7.090067e+0.
 *
 * (2000-10-25- RFD: thanks to Uwe Andersen <uandersen@mayah.com> क्रम
 * finding my typos in this क्रमmula!)
 *
 * Alas, none of the elegant function-fit solutions will work because we
 * aren't allowed to use भग्नing poपूर्णांक in the kernel and करोing it with
 * पूर्णांकegers करोesn't provide enough precision.  So we'll करो boring old
 * look-up table stuff.  The unofficial data (see below) have effectively
 * 7-bit resolution (they are rounded to the nearest degree).  I'm assuming
 * that the transfer function of the device is monotonic and smooth, so a
 * smooth function fit to the data will allow us to get better precision.
 * I used the 5th-order poly fit described above and solved क्रम
 * VIA रेजिस्टर values 0-255.  I *10 beक्रमe rounding, so we get tenth-degree
 * precision.  (I could have करोne all 1024 values क्रम our 10-bit पढ़ोings,
 * but the function is very linear in the useful range (0-80 deg C), so
 * we'll just use linear पूर्णांकerpolation क्रम 10-bit पढ़ोings.)  So, temp_lut
 * is the temp at via रेजिस्टर values 0-255:
 */
अटल स्थिर s16 temp_lut[] = अणु
	-709, -688, -667, -646, -627, -607, -589, -570, -553, -536, -519,
	-503, -487, -471, -456, -442, -428, -414, -400, -387, -375,
	-362, -350, -339, -327, -316, -305, -295, -285, -275, -265,
	-255, -246, -237, -229, -220, -212, -204, -196, -188, -180,
	-173, -166, -159, -152, -145, -139, -132, -126, -120, -114,
	-108, -102, -96, -91, -85, -80, -74, -69, -64, -59, -54, -49,
	-44, -39, -34, -29, -25, -20, -15, -11, -6, -2, 3, 7, 12, 16,
	20, 25, 29, 33, 37, 42, 46, 50, 54, 59, 63, 67, 71, 75, 79, 84,
	88, 92, 96, 100, 104, 109, 113, 117, 121, 125, 130, 134, 138,
	142, 146, 151, 155, 159, 163, 168, 172, 176, 181, 185, 189,
	193, 198, 202, 206, 211, 215, 219, 224, 228, 232, 237, 241,
	245, 250, 254, 259, 263, 267, 272, 276, 281, 285, 290, 294,
	299, 303, 307, 312, 316, 321, 325, 330, 334, 339, 344, 348,
	353, 357, 362, 366, 371, 376, 380, 385, 390, 395, 399, 404,
	409, 414, 419, 423, 428, 433, 438, 443, 449, 454, 459, 464,
	469, 475, 480, 486, 491, 497, 502, 508, 514, 520, 526, 532,
	538, 544, 551, 557, 564, 571, 578, 584, 592, 599, 606, 614,
	621, 629, 637, 645, 654, 662, 671, 680, 689, 698, 708, 718,
	728, 738, 749, 759, 770, 782, 793, 805, 818, 830, 843, 856,
	870, 883, 898, 912, 927, 943, 958, 975, 991, 1008, 1026, 1044,
	1062, 1081, 1101, 1121, 1141, 1162, 1184, 1206, 1229, 1252,
	1276, 1301, 1326, 1352, 1378, 1406, 1434, 1462
पूर्ण;

/*
 * the original LUT values from Alex van Kaam <darkside@chello.nl>
 * (क्रम via रेजिस्टर values 12-240):
 * अणु-50,-49,-47,-45,-43,-41,-39,-38,-37,-35,-34,-33,-32,-31,
 * -30,-29,-28,-27,-26,-25,-24,-24,-23,-22,-21,-20,-20,-19,-18,-17,-17,-16,-15,
 * -15,-14,-14,-13,-12,-12,-11,-11,-10,-9,-9,-8,-8,-7,-7,-6,-6,-5,-5,-4,-4,-3,
 * -3,-2,-2,-1,-1,0,0,1,1,1,3,3,3,4,4,4,5,5,5,6,6,7,7,8,8,9,9,9,10,10,11,11,12,
 * 12,12,13,13,13,14,14,15,15,16,16,16,17,17,18,18,19,19,20,20,21,21,21,22,22,
 * 22,23,23,24,24,25,25,26,26,26,27,27,27,28,28,29,29,30,30,30,31,31,32,32,33,
 * 33,34,34,35,35,35,36,36,37,37,38,38,39,39,40,40,41,41,42,42,43,43,44,44,45,
 * 45,46,46,47,48,48,49,49,50,51,51,52,52,53,53,54,55,55,56,57,57,58,59,59,60,
 * 61,62,62,63,64,65,66,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,83,84,
 * 85,86,88,89,91,92,94,96,97,99,101,103,105,107,109,110पूर्ण;
 *
 *
 * Here's the reverse LUT.  I got it by करोing a 6-th order poly fit (needed
 * an extra term क्रम a good fit to these inverse data!) and then
 * solving क्रम each temp value from -50 to 110 (the useable range क्रम
 * this chip).  Here's the fit:
 * viaRegVal = -1.160370e-10*val^6 +3.193693e-08*val^5 - 1.464447e-06*val^4
 * - 2.525453e-04*val^3 + 1.424593e-02*val^2 + 2.148941e+00*val +7.275808e+01)
 * Note that n=161:
 */
अटल स्थिर u8 via_lut[] = अणु
	12, 12, 13, 14, 14, 15, 16, 16, 17, 18, 18, 19, 20, 20, 21, 22, 23,
	23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 35, 36, 37, 39, 40,
	41, 43, 45, 46, 48, 49, 51, 53, 55, 57, 59, 60, 62, 64, 66,
	69, 71, 73, 75, 77, 79, 82, 84, 86, 88, 91, 93, 95, 98, 100,
	103, 105, 107, 110, 112, 115, 117, 119, 122, 124, 126, 129,
	131, 134, 136, 138, 140, 143, 145, 147, 150, 152, 154, 156,
	158, 160, 162, 164, 166, 168, 170, 172, 174, 176, 178, 180,
	182, 183, 185, 187, 188, 190, 192, 193, 195, 196, 198, 199,
	200, 202, 203, 205, 206, 207, 208, 209, 210, 211, 212, 213,
	214, 215, 216, 217, 218, 219, 220, 221, 222, 222, 223, 224,
	225, 226, 226, 227, 228, 228, 229, 230, 230, 231, 232, 232,
	233, 233, 234, 235, 235, 236, 236, 237, 237, 238, 238, 239,
	239, 240
पूर्ण;

/*
 * Converting temps to (8-bit) hyst and over रेजिस्टरs
 * No पूर्णांकerpolation here.
 * The +50 is because the temps start at -50
 */
अटल अंतरभूत u8 TEMP_TO_REG(दीर्घ val)
अणु
	वापस via_lut[val <= -50000 ? 0 : val >= 110000 ? 160 :
		      (val < 0 ? val - 500 : val + 500) / 1000 + 50];
पूर्ण

/* क्रम 8-bit temperature hyst and over रेजिस्टरs */
#घोषणा TEMP_FROM_REG(val)	((दीर्घ)temp_lut[val] * 100)

/* क्रम 10-bit temperature पढ़ोings */
अटल अंतरभूत दीर्घ TEMP_FROM_REG10(u16 val)
अणु
	u16 eight_bits = val >> 2;
	u16 two_bits = val & 3;

	/* no पूर्णांकerpolation क्रम these */
	अगर (two_bits == 0 || eight_bits == 255)
		वापस TEMP_FROM_REG(eight_bits);

	/* करो some linear पूर्णांकerpolation */
	वापस (temp_lut[eight_bits] * (4 - two_bits) +
		temp_lut[eight_bits + 1] * two_bits) * 25;
पूर्ण

#घोषणा DIV_FROM_REG(val) (1 << (val))
#घोषणा DIV_TO_REG(val) ((val) == 8 ? 3 : (val) == 4 ? 2 : (val) == 1 ? 0 : 1)

/*
 * For each रेजिस्टरed chip, we need to keep some data in memory.
 * The काष्ठाure is dynamically allocated.
 */
काष्ठा via686a_data अणु
	अचिन्हित लघु addr;
	स्थिर अक्षर *name;
	काष्ठा device *hwmon_dev;
	काष्ठा mutex update_lock;
	अक्षर valid;		/* !=0 अगर following fields are valid */
	अचिन्हित दीर्घ last_updated;	/* In jअगरfies */

	u8 in[5];		/* Register value */
	u8 in_max[5];		/* Register value */
	u8 in_min[5];		/* Register value */
	u8 fan[2];		/* Register value */
	u8 fan_min[2];		/* Register value */
	u16 temp[3];		/* Register value 10 bit */
	u8 temp_over[3];	/* Register value */
	u8 temp_hyst[3];	/* Register value */
	u8 fan_भाग[2];		/* Register encoding, shअगरted right */
	u16 alarms;		/* Register encoding, combined */
पूर्ण;

अटल काष्ठा pci_dev *s_bridge;	/* poपूर्णांकer to the (only) via686a */

अटल पूर्णांक via686a_probe(काष्ठा platक्रमm_device *pdev);
अटल पूर्णांक via686a_हटाओ(काष्ठा platक्रमm_device *pdev);

अटल अंतरभूत पूर्णांक via686a_पढ़ो_value(काष्ठा via686a_data *data, u8 reg)
अणु
	वापस inb_p(data->addr + reg);
पूर्ण

अटल अंतरभूत व्योम via686a_ग_लिखो_value(काष्ठा via686a_data *data, u8 reg,
				       u8 value)
अणु
	outb_p(value, data->addr + reg);
पूर्ण

अटल काष्ठा via686a_data *via686a_update_device(काष्ठा device *dev);
अटल व्योम via686a_init_device(काष्ठा via686a_data *data);

/* following are the sysfs callback functions */

/* 7 voltage sensors */
अटल sमाप_प्रकार in_show(काष्ठा device *dev, काष्ठा device_attribute *da,
		       अक्षर *buf) अणु
	काष्ठा via686a_data *data = via686a_update_device(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	पूर्णांक nr = attr->index;
	वापस प्र_लिखो(buf, "%ld\n", IN_FROM_REG(data->in[nr], nr));
पूर्ण

अटल sमाप_प्रकार in_min_show(काष्ठा device *dev, काष्ठा device_attribute *da,
			   अक्षर *buf) अणु
	काष्ठा via686a_data *data = via686a_update_device(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	पूर्णांक nr = attr->index;
	वापस प्र_लिखो(buf, "%ld\n", IN_FROM_REG(data->in_min[nr], nr));
पूर्ण

अटल sमाप_प्रकार in_max_show(काष्ठा device *dev, काष्ठा device_attribute *da,
			   अक्षर *buf) अणु
	काष्ठा via686a_data *data = via686a_update_device(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	पूर्णांक nr = attr->index;
	वापस प्र_लिखो(buf, "%ld\n", IN_FROM_REG(data->in_max[nr], nr));
पूर्ण

अटल sमाप_प्रकार in_min_store(काष्ठा device *dev, काष्ठा device_attribute *da,
			    स्थिर अक्षर *buf, माप_प्रकार count) अणु
	काष्ठा via686a_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	पूर्णांक nr = attr->index;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->in_min[nr] = IN_TO_REG(val, nr);
	via686a_ग_लिखो_value(data, VIA686A_REG_IN_MIN(nr),
			data->in_min[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण
अटल sमाप_प्रकार in_max_store(काष्ठा device *dev, काष्ठा device_attribute *da,
			    स्थिर अक्षर *buf, माप_प्रकार count) अणु
	काष्ठा via686a_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	पूर्णांक nr = attr->index;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->in_max[nr] = IN_TO_REG(val, nr);
	via686a_ग_लिखो_value(data, VIA686A_REG_IN_MAX(nr),
			data->in_max[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(in0_input, in, 0);
अटल SENSOR_DEVICE_ATTR_RW(in0_min, in_min, 0);
अटल SENSOR_DEVICE_ATTR_RW(in0_max, in_max, 0);
अटल SENSOR_DEVICE_ATTR_RO(in1_input, in, 1);
अटल SENSOR_DEVICE_ATTR_RW(in1_min, in_min, 1);
अटल SENSOR_DEVICE_ATTR_RW(in1_max, in_max, 1);
अटल SENSOR_DEVICE_ATTR_RO(in2_input, in, 2);
अटल SENSOR_DEVICE_ATTR_RW(in2_min, in_min, 2);
अटल SENSOR_DEVICE_ATTR_RW(in2_max, in_max, 2);
अटल SENSOR_DEVICE_ATTR_RO(in3_input, in, 3);
अटल SENSOR_DEVICE_ATTR_RW(in3_min, in_min, 3);
अटल SENSOR_DEVICE_ATTR_RW(in3_max, in_max, 3);
अटल SENSOR_DEVICE_ATTR_RO(in4_input, in, 4);
अटल SENSOR_DEVICE_ATTR_RW(in4_min, in_min, 4);
अटल SENSOR_DEVICE_ATTR_RW(in4_max, in_max, 4);

/* 3 temperatures */
अटल sमाप_प्रकार temp_show(काष्ठा device *dev, काष्ठा device_attribute *da,
			 अक्षर *buf) अणु
	काष्ठा via686a_data *data = via686a_update_device(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	पूर्णांक nr = attr->index;
	वापस प्र_लिखो(buf, "%ld\n", TEMP_FROM_REG10(data->temp[nr]));
पूर्ण
अटल sमाप_प्रकार temp_over_show(काष्ठा device *dev, काष्ठा device_attribute *da,
			      अक्षर *buf) अणु
	काष्ठा via686a_data *data = via686a_update_device(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	पूर्णांक nr = attr->index;
	वापस प्र_लिखो(buf, "%ld\n", TEMP_FROM_REG(data->temp_over[nr]));
पूर्ण
अटल sमाप_प्रकार temp_hyst_show(काष्ठा device *dev, काष्ठा device_attribute *da,
			      अक्षर *buf) अणु
	काष्ठा via686a_data *data = via686a_update_device(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	पूर्णांक nr = attr->index;
	वापस प्र_लिखो(buf, "%ld\n", TEMP_FROM_REG(data->temp_hyst[nr]));
पूर्ण
अटल sमाप_प्रकार temp_over_store(काष्ठा device *dev,
			       काष्ठा device_attribute *da, स्थिर अक्षर *buf,
			       माप_प्रकार count) अणु
	काष्ठा via686a_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	पूर्णांक nr = attr->index;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->temp_over[nr] = TEMP_TO_REG(val);
	via686a_ग_लिखो_value(data, VIA686A_REG_TEMP_OVER[nr],
			    data->temp_over[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण
अटल sमाप_प्रकार temp_hyst_store(काष्ठा device *dev,
			       काष्ठा device_attribute *da, स्थिर अक्षर *buf,
			       माप_प्रकार count) अणु
	काष्ठा via686a_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	पूर्णांक nr = attr->index;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->temp_hyst[nr] = TEMP_TO_REG(val);
	via686a_ग_लिखो_value(data, VIA686A_REG_TEMP_HYST[nr],
			    data->temp_hyst[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(temp1_input, temp, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp1_max, temp_over, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp1_max_hyst, temp_hyst, 0);
अटल SENSOR_DEVICE_ATTR_RO(temp2_input, temp, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp2_max, temp_over, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp2_max_hyst, temp_hyst, 1);
अटल SENSOR_DEVICE_ATTR_RO(temp3_input, temp, 2);
अटल SENSOR_DEVICE_ATTR_RW(temp3_max, temp_over, 2);
अटल SENSOR_DEVICE_ATTR_RW(temp3_max_hyst, temp_hyst, 2);

/* 2 Fans */
अटल sमाप_प्रकार fan_show(काष्ठा device *dev, काष्ठा device_attribute *da,
			अक्षर *buf) अणु
	काष्ठा via686a_data *data = via686a_update_device(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	पूर्णांक nr = attr->index;
	वापस प्र_लिखो(buf, "%d\n", FAN_FROM_REG(data->fan[nr],
				DIV_FROM_REG(data->fan_भाग[nr])));
पूर्ण
अटल sमाप_प्रकार fan_min_show(काष्ठा device *dev, काष्ठा device_attribute *da,
			    अक्षर *buf) अणु
	काष्ठा via686a_data *data = via686a_update_device(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	पूर्णांक nr = attr->index;
	वापस प्र_लिखो(buf, "%d\n",
		FAN_FROM_REG(data->fan_min[nr],
			     DIV_FROM_REG(data->fan_भाग[nr])));
पूर्ण
अटल sमाप_प्रकार fan_भाग_show(काष्ठा device *dev, काष्ठा device_attribute *da,
			    अक्षर *buf) अणु
	काष्ठा via686a_data *data = via686a_update_device(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	पूर्णांक nr = attr->index;
	वापस प्र_लिखो(buf, "%d\n", DIV_FROM_REG(data->fan_भाग[nr]));
पूर्ण
अटल sमाप_प्रकार fan_min_store(काष्ठा device *dev, काष्ठा device_attribute *da,
			     स्थिर अक्षर *buf, माप_प्रकार count) अणु
	काष्ठा via686a_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	पूर्णांक nr = attr->index;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->fan_min[nr] = FAN_TO_REG(val, DIV_FROM_REG(data->fan_भाग[nr]));
	via686a_ग_लिखो_value(data, VIA686A_REG_FAN_MIN(nr+1), data->fan_min[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण
अटल sमाप_प्रकार fan_भाग_store(काष्ठा device *dev, काष्ठा device_attribute *da,
			     स्थिर अक्षर *buf, माप_प्रकार count) अणु
	काष्ठा via686a_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	पूर्णांक nr = attr->index;
	पूर्णांक old;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	old = via686a_पढ़ो_value(data, VIA686A_REG_FANDIV);
	data->fan_भाग[nr] = DIV_TO_REG(val);
	old = (old & 0x0f) | (data->fan_भाग[1] << 6) | (data->fan_भाग[0] << 4);
	via686a_ग_लिखो_value(data, VIA686A_REG_FANDIV, old);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(fan1_input, fan, 0);
अटल SENSOR_DEVICE_ATTR_RW(fan1_min, fan_min, 0);
अटल SENSOR_DEVICE_ATTR_RW(fan1_भाग, fan_भाग, 0);
अटल SENSOR_DEVICE_ATTR_RO(fan2_input, fan, 1);
अटल SENSOR_DEVICE_ATTR_RW(fan2_min, fan_min, 1);
अटल SENSOR_DEVICE_ATTR_RW(fan2_भाग, fan_भाग, 1);

/* Alarms */
अटल sमाप_प्रकार alarms_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा via686a_data *data = via686a_update_device(dev);
	वापस प्र_लिखो(buf, "%u\n", data->alarms);
पूर्ण

अटल DEVICE_ATTR_RO(alarms);

अटल sमाप_प्रकार alarm_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	पूर्णांक bitnr = to_sensor_dev_attr(attr)->index;
	काष्ठा via686a_data *data = via686a_update_device(dev);
	वापस प्र_लिखो(buf, "%u\n", (data->alarms >> bitnr) & 1);
पूर्ण
अटल SENSOR_DEVICE_ATTR_RO(in0_alarm, alarm, 0);
अटल SENSOR_DEVICE_ATTR_RO(in1_alarm, alarm, 1);
अटल SENSOR_DEVICE_ATTR_RO(in2_alarm, alarm, 2);
अटल SENSOR_DEVICE_ATTR_RO(in3_alarm, alarm, 3);
अटल SENSOR_DEVICE_ATTR_RO(in4_alarm, alarm, 8);
अटल SENSOR_DEVICE_ATTR_RO(temp1_alarm, alarm, 4);
अटल SENSOR_DEVICE_ATTR_RO(temp2_alarm, alarm, 11);
अटल SENSOR_DEVICE_ATTR_RO(temp3_alarm, alarm, 15);
अटल SENSOR_DEVICE_ATTR_RO(fan1_alarm, alarm, 6);
अटल SENSOR_DEVICE_ATTR_RO(fan2_alarm, alarm, 7);

अटल sमाप_प्रकार name_show(काष्ठा device *dev, काष्ठा device_attribute
			 *devattr, अक्षर *buf)
अणु
	काष्ठा via686a_data *data = dev_get_drvdata(dev);
	वापस प्र_लिखो(buf, "%s\n", data->name);
पूर्ण
अटल DEVICE_ATTR_RO(name);

अटल काष्ठा attribute *via686a_attributes[] = अणु
	&sensor_dev_attr_in0_input.dev_attr.attr,
	&sensor_dev_attr_in1_input.dev_attr.attr,
	&sensor_dev_attr_in2_input.dev_attr.attr,
	&sensor_dev_attr_in3_input.dev_attr.attr,
	&sensor_dev_attr_in4_input.dev_attr.attr,
	&sensor_dev_attr_in0_min.dev_attr.attr,
	&sensor_dev_attr_in1_min.dev_attr.attr,
	&sensor_dev_attr_in2_min.dev_attr.attr,
	&sensor_dev_attr_in3_min.dev_attr.attr,
	&sensor_dev_attr_in4_min.dev_attr.attr,
	&sensor_dev_attr_in0_max.dev_attr.attr,
	&sensor_dev_attr_in1_max.dev_attr.attr,
	&sensor_dev_attr_in2_max.dev_attr.attr,
	&sensor_dev_attr_in3_max.dev_attr.attr,
	&sensor_dev_attr_in4_max.dev_attr.attr,
	&sensor_dev_attr_in0_alarm.dev_attr.attr,
	&sensor_dev_attr_in1_alarm.dev_attr.attr,
	&sensor_dev_attr_in2_alarm.dev_attr.attr,
	&sensor_dev_attr_in3_alarm.dev_attr.attr,
	&sensor_dev_attr_in4_alarm.dev_attr.attr,

	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_temp2_input.dev_attr.attr,
	&sensor_dev_attr_temp3_input.dev_attr.attr,
	&sensor_dev_attr_temp1_max.dev_attr.attr,
	&sensor_dev_attr_temp2_max.dev_attr.attr,
	&sensor_dev_attr_temp3_max.dev_attr.attr,
	&sensor_dev_attr_temp1_max_hyst.dev_attr.attr,
	&sensor_dev_attr_temp2_max_hyst.dev_attr.attr,
	&sensor_dev_attr_temp3_max_hyst.dev_attr.attr,
	&sensor_dev_attr_temp1_alarm.dev_attr.attr,
	&sensor_dev_attr_temp2_alarm.dev_attr.attr,
	&sensor_dev_attr_temp3_alarm.dev_attr.attr,

	&sensor_dev_attr_fan1_input.dev_attr.attr,
	&sensor_dev_attr_fan2_input.dev_attr.attr,
	&sensor_dev_attr_fan1_min.dev_attr.attr,
	&sensor_dev_attr_fan2_min.dev_attr.attr,
	&sensor_dev_attr_fan1_भाग.dev_attr.attr,
	&sensor_dev_attr_fan2_भाग.dev_attr.attr,
	&sensor_dev_attr_fan1_alarm.dev_attr.attr,
	&sensor_dev_attr_fan2_alarm.dev_attr.attr,

	&dev_attr_alarms.attr,
	&dev_attr_name.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group via686a_group = अणु
	.attrs = via686a_attributes,
पूर्ण;

अटल काष्ठा platक्रमm_driver via686a_driver = अणु
	.driver = अणु
		.name	= "via686a",
	पूर्ण,
	.probe		= via686a_probe,
	.हटाओ		= via686a_हटाओ,
पूर्ण;

/* This is called when the module is loaded */
अटल पूर्णांक via686a_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा via686a_data *data;
	काष्ठा resource *res;
	पूर्णांक err;

	/* Reserve the ISA region */
	res = platक्रमm_get_resource(pdev, IORESOURCE_IO, 0);
	अगर (!devm_request_region(&pdev->dev, res->start, VIA686A_EXTENT,
				 via686a_driver.driver.name)) अणु
		dev_err(&pdev->dev, "Region 0x%lx-0x%lx already in use!\n",
			(अचिन्हित दीर्घ)res->start, (अचिन्हित दीर्घ)res->end);
		वापस -ENODEV;
	पूर्ण

	data = devm_kzalloc(&pdev->dev, माप(काष्ठा via686a_data),
			    GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, data);
	data->addr = res->start;
	data->name = "via686a";
	mutex_init(&data->update_lock);

	/* Initialize the VIA686A chip */
	via686a_init_device(data);

	/* Register sysfs hooks */
	err = sysfs_create_group(&pdev->dev.kobj, &via686a_group);
	अगर (err)
		वापस err;

	data->hwmon_dev = hwmon_device_रेजिस्टर(&pdev->dev);
	अगर (IS_ERR(data->hwmon_dev)) अणु
		err = PTR_ERR(data->hwmon_dev);
		जाओ निकास_हटाओ_files;
	पूर्ण

	वापस 0;

निकास_हटाओ_files:
	sysfs_हटाओ_group(&pdev->dev.kobj, &via686a_group);
	वापस err;
पूर्ण

अटल पूर्णांक via686a_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा via686a_data *data = platक्रमm_get_drvdata(pdev);

	hwmon_device_unरेजिस्टर(data->hwmon_dev);
	sysfs_हटाओ_group(&pdev->dev.kobj, &via686a_group);

	वापस 0;
पूर्ण

अटल व्योम via686a_update_fan_भाग(काष्ठा via686a_data *data)
अणु
	पूर्णांक reg = via686a_पढ़ो_value(data, VIA686A_REG_FANDIV);
	data->fan_भाग[0] = (reg >> 4) & 0x03;
	data->fan_भाग[1] = reg >> 6;
पूर्ण

अटल व्योम via686a_init_device(काष्ठा via686a_data *data)
अणु
	u8 reg;

	/* Start monitoring */
	reg = via686a_पढ़ो_value(data, VIA686A_REG_CONFIG);
	via686a_ग_लिखो_value(data, VIA686A_REG_CONFIG, (reg | 0x01) & 0x7F);

	/* Configure temp पूर्णांकerrupt mode क्रम continuous-पूर्णांकerrupt operation */
	reg = via686a_पढ़ो_value(data, VIA686A_REG_TEMP_MODE);
	via686a_ग_लिखो_value(data, VIA686A_REG_TEMP_MODE,
			    (reg & ~VIA686A_TEMP_MODE_MASK)
			    | VIA686A_TEMP_MODE_CONTINUOUS);

	/* Pre-पढ़ो fan घड़ी भागisor values */
	via686a_update_fan_भाग(data);
पूर्ण

अटल काष्ठा via686a_data *via686a_update_device(काष्ठा device *dev)
अणु
	काष्ठा via686a_data *data = dev_get_drvdata(dev);
	पूर्णांक i;

	mutex_lock(&data->update_lock);

	अगर (समय_after(jअगरfies, data->last_updated + HZ + HZ / 2)
	    || !data->valid) अणु
		क्रम (i = 0; i <= 4; i++) अणु
			data->in[i] =
			    via686a_पढ़ो_value(data, VIA686A_REG_IN(i));
			data->in_min[i] = via686a_पढ़ो_value(data,
							     VIA686A_REG_IN_MIN
							     (i));
			data->in_max[i] =
			    via686a_पढ़ो_value(data, VIA686A_REG_IN_MAX(i));
		पूर्ण
		क्रम (i = 1; i <= 2; i++) अणु
			data->fan[i - 1] =
			    via686a_पढ़ो_value(data, VIA686A_REG_FAN(i));
			data->fan_min[i - 1] = via686a_पढ़ो_value(data,
						     VIA686A_REG_FAN_MIN(i));
		पूर्ण
		क्रम (i = 0; i <= 2; i++) अणु
			data->temp[i] = via686a_पढ़ो_value(data,
						 VIA686A_REG_TEMP[i]) << 2;
			data->temp_over[i] =
			    via686a_पढ़ो_value(data,
					       VIA686A_REG_TEMP_OVER[i]);
			data->temp_hyst[i] =
			    via686a_पढ़ो_value(data,
					       VIA686A_REG_TEMP_HYST[i]);
		पूर्ण
		/*
		 * add in lower 2 bits
		 * temp1 uses bits 7-6 of VIA686A_REG_TEMP_LOW1
		 * temp2 uses bits 5-4 of VIA686A_REG_TEMP_LOW23
		 * temp3 uses bits 7-6 of VIA686A_REG_TEMP_LOW23
		 */
		data->temp[0] |= (via686a_पढ़ो_value(data,
						     VIA686A_REG_TEMP_LOW1)
				  & 0xc0) >> 6;
		data->temp[1] |=
		    (via686a_पढ़ो_value(data, VIA686A_REG_TEMP_LOW23) &
		     0x30) >> 4;
		data->temp[2] |=
		    (via686a_पढ़ो_value(data, VIA686A_REG_TEMP_LOW23) &
		     0xc0) >> 6;

		via686a_update_fan_भाग(data);
		data->alarms =
		    via686a_पढ़ो_value(data,
				       VIA686A_REG_ALARM1) |
		    (via686a_पढ़ो_value(data, VIA686A_REG_ALARM2) << 8);
		data->last_updated = jअगरfies;
		data->valid = 1;
	पूर्ण

	mutex_unlock(&data->update_lock);

	वापस data;
पूर्ण

अटल स्थिर काष्ठा pci_device_id via686a_pci_ids[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_82C686_4) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, via686a_pci_ids);

अटल पूर्णांक via686a_device_add(अचिन्हित लघु address)
अणु
	काष्ठा resource res = अणु
		.start	= address,
		.end	= address + VIA686A_EXTENT - 1,
		.name	= "via686a",
		.flags	= IORESOURCE_IO,
	पूर्ण;
	पूर्णांक err;

	err = acpi_check_resource_conflict(&res);
	अगर (err)
		जाओ निकास;

	pdev = platक्रमm_device_alloc("via686a", address);
	अगर (!pdev) अणु
		err = -ENOMEM;
		pr_err("Device allocation failed\n");
		जाओ निकास;
	पूर्ण

	err = platक्रमm_device_add_resources(pdev, &res, 1);
	अगर (err) अणु
		pr_err("Device resource addition failed (%d)\n", err);
		जाओ निकास_device_put;
	पूर्ण

	err = platक्रमm_device_add(pdev);
	अगर (err) अणु
		pr_err("Device addition failed (%d)\n", err);
		जाओ निकास_device_put;
	पूर्ण

	वापस 0;

निकास_device_put:
	platक्रमm_device_put(pdev);
निकास:
	वापस err;
पूर्ण

अटल पूर्णांक via686a_pci_probe(काष्ठा pci_dev *dev,
				       स्थिर काष्ठा pci_device_id *id)
अणु
	u16 address, val;

	अगर (क्रमce_addr) अणु
		address = क्रमce_addr & ~(VIA686A_EXTENT - 1);
		dev_warn(&dev->dev, "Forcing ISA address 0x%x\n", address);
		अगर (PCIBIOS_SUCCESSFUL !=
		    pci_ग_लिखो_config_word(dev, VIA686A_BASE_REG, address | 1))
			वापस -ENODEV;
	पूर्ण
	अगर (PCIBIOS_SUCCESSFUL !=
	    pci_पढ़ो_config_word(dev, VIA686A_BASE_REG, &val))
		वापस -ENODEV;

	address = val & ~(VIA686A_EXTENT - 1);
	अगर (address == 0) अणु
		dev_err(&dev->dev,
			"base address not set - upgrade BIOS or use force_addr=0xaddr\n");
		वापस -ENODEV;
	पूर्ण

	अगर (PCIBIOS_SUCCESSFUL !=
	    pci_पढ़ो_config_word(dev, VIA686A_ENABLE_REG, &val))
		वापस -ENODEV;
	अगर (!(val & 0x0001)) अणु
		अगर (!क्रमce_addr) अणु
			dev_warn(&dev->dev,
				 "Sensors disabled, enable with force_addr=0x%x\n",
				 address);
			वापस -ENODEV;
		पूर्ण

		dev_warn(&dev->dev, "Enabling sensors\n");
		अगर (PCIBIOS_SUCCESSFUL !=
		    pci_ग_लिखो_config_word(dev, VIA686A_ENABLE_REG,
					  val | 0x0001))
			वापस -ENODEV;
	पूर्ण

	अगर (platक्रमm_driver_रेजिस्टर(&via686a_driver))
		जाओ निकास;

	/* Sets global pdev as a side effect */
	अगर (via686a_device_add(address))
		जाओ निकास_unरेजिस्टर;

	/*
	 * Always वापस failure here.  This is to allow other drivers to bind
	 * to this pci device.  We करोn't really want to have control over the
	 * pci device, we only wanted to पढ़ो as few रेजिस्टर values from it.
	 */
	s_bridge = pci_dev_get(dev);
	वापस -ENODEV;

निकास_unरेजिस्टर:
	platक्रमm_driver_unरेजिस्टर(&via686a_driver);
निकास:
	वापस -ENODEV;
पूर्ण

अटल काष्ठा pci_driver via686a_pci_driver = अणु
	.name		= "via686a",
	.id_table	= via686a_pci_ids,
	.probe		= via686a_pci_probe,
पूर्ण;

अटल पूर्णांक __init sm_via686a_init(व्योम)
अणु
	वापस pci_रेजिस्टर_driver(&via686a_pci_driver);
पूर्ण

अटल व्योम __निकास sm_via686a_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&via686a_pci_driver);
	अगर (s_bridge != शून्य) अणु
		platक्रमm_device_unरेजिस्टर(pdev);
		platक्रमm_driver_unरेजिस्टर(&via686a_driver);
		pci_dev_put(s_bridge);
		s_bridge = शून्य;
	पूर्ण
पूर्ण

MODULE_AUTHOR("Kyथघsti Mथअlkki <kmalkki@cc.hut.fi>, "
	      "Mark Studebaker <mdsxyz123@yahoo.com> "
	      "and Bob Dougherty <bobd@stanford.edu>");
MODULE_DESCRIPTION("VIA 686A Sensor device");
MODULE_LICENSE("GPL");

module_init(sm_via686a_init);
module_निकास(sm_via686a_निकास);
