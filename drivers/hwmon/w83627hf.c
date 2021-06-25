<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * w83627hf.c - Part of lm_sensors, Linux kernel modules क्रम hardware
 *		monitoring
 * Copyright (c) 1998 - 2003  Froकरो Looijaard <froकरोl@dds.nl>,
 *			      Philip Edelbrock <phil@netroedge.com>,
 *			      and Mark Studebaker <mdsxyz123@yahoo.com>
 * Ported to 2.6 by Bernhard C. Schrenk <clemy@clemy.org>
 * Copyright (c) 2007 - 1012  Jean Delvare <jdelvare@suse.de>
 */

/*
 * Supports following chips:
 *
 * Chip		#vin	#fanin	#pwm	#temp	wchipid	vendid	i2c	ISA
 * w83627hf	9	3	2	3	0x20	0x5ca3	no	yes(LPC)
 * w83627thf	7	3	3	3	0x90	0x5ca3	no	yes(LPC)
 * w83637hf	7	3	3	3	0x80	0x5ca3	no	yes(LPC)
 * w83687thf	7	3	3	3	0x90	0x5ca3	no	yes(LPC)
 * w83697hf	8	2	2	2	0x60	0x5ca3	no	yes(LPC)
 *
 * For other winbond chips, and क्रम i2c support in the above chips,
 * use w83781d.c.
 *
 * Note: स्वतःmatic ("cruise") fan control क्रम 697, 637 & 627thf not
 * supported yet.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/hwmon-vid.h>
#समावेश <linux/err.h>
#समावेश <linux/mutex.h>
#समावेश <linux/ioport.h>
#समावेश <linux/acpi.h>
#समावेश <linux/पन.स>
#समावेश "lm75.h"

अटल काष्ठा platक्रमm_device *pdev;

#घोषणा DRVNAME "w83627hf"
क्रमागत chips अणु w83627hf, w83627thf, w83697hf, w83637hf, w83687thf पूर्ण;

काष्ठा w83627hf_sio_data अणु
	क्रमागत chips type;
	पूर्णांक sioaddr;
पूर्ण;

अटल u8 क्रमce_i2c = 0x1f;
module_param(क्रमce_i2c, byte, 0);
MODULE_PARM_DESC(क्रमce_i2c,
		 "Initialize the i2c address of the sensors");

अटल bool init = 1;
module_param(init, bool, 0);
MODULE_PARM_DESC(init, "Set to zero to bypass chip initialization");

अटल अचिन्हित लघु क्रमce_id;
module_param(क्रमce_id, uलघु, 0);
MODULE_PARM_DESC(क्रमce_id, "Override the detected device ID");

/* modअगरied from kernel/include/traps.c */
#घोषणा DEV			0x07 /* Register: Logical device select */

/* logical device numbers क्रम superio_select (below) */
#घोषणा W83627HF_LD_FDC		0x00
#घोषणा W83627HF_LD_PRT		0x01
#घोषणा W83627HF_LD_UART1	0x02
#घोषणा W83627HF_LD_UART2	0x03
#घोषणा W83627HF_LD_KBC		0x05
#घोषणा W83627HF_LD_CIR		0x06 /* w83627hf only */
#घोषणा W83627HF_LD_GAME	0x07
#घोषणा W83627HF_LD_MIDI	0x07
#घोषणा W83627HF_LD_GPIO1	0x07
#घोषणा W83627HF_LD_GPIO5	0x07 /* w83627thf only */
#घोषणा W83627HF_LD_GPIO2	0x08
#घोषणा W83627HF_LD_GPIO3	0x09
#घोषणा W83627HF_LD_GPIO4	0x09 /* w83627thf only */
#घोषणा W83627HF_LD_ACPI	0x0a
#घोषणा W83627HF_LD_HWM		0x0b

#घोषणा DEVID			0x20 /* Register: Device ID */

#घोषणा W83627THF_GPIO5_EN	0x30 /* w83627thf only */
#घोषणा W83627THF_GPIO5_IOSR	0xf3 /* w83627thf only */
#घोषणा W83627THF_GPIO5_DR	0xf4 /* w83627thf only */

#घोषणा W83687THF_VID_EN	0x29 /* w83687thf only */
#घोषणा W83687THF_VID_CFG	0xF0 /* w83687thf only */
#घोषणा W83687THF_VID_DATA	0xF1 /* w83687thf only */

अटल अंतरभूत व्योम
superio_outb(काष्ठा w83627hf_sio_data *sio, पूर्णांक reg, पूर्णांक val)
अणु
	outb(reg, sio->sioaddr);
	outb(val, sio->sioaddr + 1);
पूर्ण

अटल अंतरभूत पूर्णांक
superio_inb(काष्ठा w83627hf_sio_data *sio, पूर्णांक reg)
अणु
	outb(reg, sio->sioaddr);
	वापस inb(sio->sioaddr + 1);
पूर्ण

अटल अंतरभूत व्योम
superio_select(काष्ठा w83627hf_sio_data *sio, पूर्णांक ld)
अणु
	outb(DEV, sio->sioaddr);
	outb(ld,  sio->sioaddr + 1);
पूर्ण

अटल अंतरभूत पूर्णांक
superio_enter(काष्ठा w83627hf_sio_data *sio)
अणु
	अगर (!request_muxed_region(sio->sioaddr, 2, DRVNAME))
		वापस -EBUSY;

	outb(0x87, sio->sioaddr);
	outb(0x87, sio->sioaddr);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
superio_निकास(काष्ठा w83627hf_sio_data *sio)
अणु
	outb(0xAA, sio->sioaddr);
	release_region(sio->sioaddr, 2);
पूर्ण

#घोषणा W627_DEVID 0x52
#घोषणा W627THF_DEVID 0x82
#घोषणा W697_DEVID 0x60
#घोषणा W637_DEVID 0x70
#घोषणा W687THF_DEVID 0x85
#घोषणा WINB_ACT_REG 0x30
#घोषणा WINB_BASE_REG 0x60
/* Constants specअगरied below */

/* Alignment of the base address */
#घोषणा WINB_ALIGNMENT		~7

/* Offset & size of I/O region we are पूर्णांकerested in */
#घोषणा WINB_REGION_OFFSET	5
#घोषणा WINB_REGION_SIZE	2

/* Where are the sensors address/data रेजिस्टरs relative to the region offset */
#घोषणा W83781D_ADDR_REG_OFFSET 0
#घोषणा W83781D_DATA_REG_OFFSET 1

/* The W83781D रेजिस्टरs */
/* The W83782D रेजिस्टरs क्रम nr=7,8 are in bank 5 */
#घोषणा W83781D_REG_IN_MAX(nr) ((nr < 7) ? (0x2b + (nr) * 2) : \
					   (0x554 + (((nr) - 7) * 2)))
#घोषणा W83781D_REG_IN_MIN(nr) ((nr < 7) ? (0x2c + (nr) * 2) : \
					   (0x555 + (((nr) - 7) * 2)))
#घोषणा W83781D_REG_IN(nr)     ((nr < 7) ? (0x20 + (nr)) : \
					   (0x550 + (nr) - 7))

/* nr:0-2 क्रम fans:1-3 */
#घोषणा W83627HF_REG_FAN_MIN(nr)	(0x3b + (nr))
#घोषणा W83627HF_REG_FAN(nr)		(0x28 + (nr))

#घोषणा W83627HF_REG_TEMP2_CONFIG 0x152
#घोषणा W83627HF_REG_TEMP3_CONFIG 0x252
/* these are zero-based, unlike config स्थिरants above */
अटल स्थिर u16 w83627hf_reg_temp[]		= अणु 0x27, 0x150, 0x250 पूर्ण;
अटल स्थिर u16 w83627hf_reg_temp_hyst[]	= अणु 0x3A, 0x153, 0x253 पूर्ण;
अटल स्थिर u16 w83627hf_reg_temp_over[]	= अणु 0x39, 0x155, 0x255 पूर्ण;

#घोषणा W83781D_REG_BANK 0x4E

#घोषणा W83781D_REG_CONFIG 0x40
#घोषणा W83781D_REG_ALARM1 0x459
#घोषणा W83781D_REG_ALARM2 0x45A
#घोषणा W83781D_REG_ALARM3 0x45B

#घोषणा W83781D_REG_BEEP_CONFIG 0x4D
#घोषणा W83781D_REG_BEEP_INTS1 0x56
#घोषणा W83781D_REG_BEEP_INTS2 0x57
#घोषणा W83781D_REG_BEEP_INTS3 0x453

#घोषणा W83781D_REG_VID_FANDIV 0x47

#घोषणा W83781D_REG_CHIPID 0x49
#घोषणा W83781D_REG_WCHIPID 0x58
#घोषणा W83781D_REG_CHIPMAN 0x4F
#घोषणा W83781D_REG_PIN 0x4B

#घोषणा W83781D_REG_VBAT 0x5D

#घोषणा W83627HF_REG_PWM1 0x5A
#घोषणा W83627HF_REG_PWM2 0x5B

अटल स्थिर u8 W83627THF_REG_PWM_ENABLE[] = अणु
	0x04,		/* FAN 1 mode */
	0x04,		/* FAN 2 mode */
	0x12,		/* FAN AUX mode */
पूर्ण;
अटल स्थिर u8 W83627THF_PWM_ENABLE_SHIFT[] = अणु 2, 4, 1 पूर्ण;

#घोषणा W83627THF_REG_PWM1		0x01	/* 697HF/637HF/687THF too */
#घोषणा W83627THF_REG_PWM2		0x03	/* 697HF/637HF/687THF too */
#घोषणा W83627THF_REG_PWM3		0x11	/* 637HF/687THF too */

#घोषणा W83627THF_REG_VRM_OVT_CFG 	0x18	/* 637HF/687THF too */

अटल स्थिर u8 regpwm_627hf[] = अणु W83627HF_REG_PWM1, W83627HF_REG_PWM2 पूर्ण;
अटल स्थिर u8 regpwm[] = अणु W83627THF_REG_PWM1, W83627THF_REG_PWM2,
                             W83627THF_REG_PWM3 पूर्ण;
#घोषणा W836X7HF_REG_PWM(type, nr) (((type) == w83627hf) ? \
				    regpwm_627hf[nr] : regpwm[nr])

#घोषणा W83627HF_REG_PWM_FREQ		0x5C	/* Only क्रम the 627HF */

#घोषणा W83637HF_REG_PWM_FREQ1		0x00	/* 697HF/687THF too */
#घोषणा W83637HF_REG_PWM_FREQ2		0x02	/* 697HF/687THF too */
#घोषणा W83637HF_REG_PWM_FREQ3		0x10	/* 687THF too */

अटल स्थिर u8 W83637HF_REG_PWM_FREQ[] = अणु W83637HF_REG_PWM_FREQ1,
					W83637HF_REG_PWM_FREQ2,
					W83637HF_REG_PWM_FREQ3 पूर्ण;

#घोषणा W83627HF_BASE_PWM_FREQ	46870

#घोषणा W83781D_REG_I2C_ADDR 0x48
#घोषणा W83781D_REG_I2C_SUBADDR 0x4A

/* Sensor selection */
#घोषणा W83781D_REG_SCFG1 0x5D
अटल स्थिर u8 BIT_SCFG1[] = अणु 0x02, 0x04, 0x08 पूर्ण;
#घोषणा W83781D_REG_SCFG2 0x59
अटल स्थिर u8 BIT_SCFG2[] = अणु 0x10, 0x20, 0x40 पूर्ण;
#घोषणा W83781D_DEFAULT_BETA 3435

/*
 * Conversions. Limit checking is only करोne on the TO_REG
 * variants. Note that you should be a bit careful with which arguments
 * these macros are called: arguments may be evaluated more than once.
 * Fixing this is just not worth it.
 */
#घोषणा IN_TO_REG(val)  (clamp_val((((val) + 8) / 16), 0, 255))
#घोषणा IN_FROM_REG(val) ((val) * 16)

अटल अंतरभूत u8 FAN_TO_REG(दीर्घ rpm, पूर्णांक भाग)
अणु
	अगर (rpm == 0)
		वापस 255;
	rpm = clamp_val(rpm, 1, 1000000);
	वापस clamp_val((1350000 + rpm * भाग / 2) / (rpm * भाग), 1, 254);
पूर्ण

#घोषणा TEMP_MIN (-128000)
#घोषणा TEMP_MAX ( 127000)

/*
 * TEMP: 0.001C/bit (-128C to +127C)
 * REG: 1C/bit, two's complement
 */
अटल u8 TEMP_TO_REG(दीर्घ temp)
अणु
	पूर्णांक ntemp = clamp_val(temp, TEMP_MIN, TEMP_MAX);
	ntemp += (ntemp < 0 ? -500 : 500);
	वापस (u8)(ntemp / 1000);
पूर्ण

अटल पूर्णांक TEMP_FROM_REG(u8 reg)
अणु
        वापस (s8)reg * 1000;
पूर्ण

#घोषणा FAN_FROM_REG(val,भाग) ((val)==0?-1:(val)==255?0:1350000/((val)*(भाग)))

#घोषणा PWM_TO_REG(val) (clamp_val((val), 0, 255))

अटल अंतरभूत अचिन्हित दीर्घ pwm_freq_from_reg_627hf(u8 reg)
अणु
	अचिन्हित दीर्घ freq;
	freq = W83627HF_BASE_PWM_FREQ >> reg;
	वापस freq;
पूर्ण
अटल अंतरभूत u8 pwm_freq_to_reg_627hf(अचिन्हित दीर्घ val)
अणु
	u8 i;
	/*
	 * Only 5 भागiders (1 2 4 8 16)
	 * Search क्रम the nearest available frequency
	 */
	क्रम (i = 0; i < 4; i++) अणु
		अगर (val > (((W83627HF_BASE_PWM_FREQ >> i) +
			    (W83627HF_BASE_PWM_FREQ >> (i+1))) / 2))
			अवरोध;
	पूर्ण
	वापस i;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ pwm_freq_from_reg(u8 reg)
अणु
	/* Clock bit 8 -> 180 kHz or 24 MHz */
	अचिन्हित दीर्घ घड़ी = (reg & 0x80) ? 180000UL : 24000000UL;

	reg &= 0x7f;
	/* This should not happen but anyway... */
	अगर (reg == 0)
		reg++;
	वापस घड़ी / (reg << 8);
पूर्ण
अटल अंतरभूत u8 pwm_freq_to_reg(अचिन्हित दीर्घ val)
अणु
	/* Minimum भागider value is 0x01 and maximum is 0x7F */
	अगर (val >= 93750)	/* The highest we can करो */
		वापस 0x01;
	अगर (val >= 720)	/* Use 24 MHz घड़ी */
		वापस 24000000UL / (val << 8);
	अगर (val < 6)		/* The lowest we can करो */
		वापस 0xFF;
	अन्यथा			/* Use 180 kHz घड़ी */
		वापस 0x80 | (180000UL / (val << 8));
पूर्ण

#घोषणा BEEP_MASK_FROM_REG(val)		((val) & 0xff7fff)
#घोषणा BEEP_MASK_TO_REG(val)		((val) & 0xff7fff)

#घोषणा DIV_FROM_REG(val) (1 << (val))

अटल अंतरभूत u8 DIV_TO_REG(दीर्घ val)
अणु
	पूर्णांक i;
	val = clamp_val(val, 1, 128) >> 1;
	क्रम (i = 0; i < 7; i++) अणु
		अगर (val == 0)
			अवरोध;
		val >>= 1;
	पूर्ण
	वापस (u8)i;
पूर्ण

/*
 * For each रेजिस्टरed chip, we need to keep some data in memory.
 * The काष्ठाure is dynamically allocated.
 */
काष्ठा w83627hf_data अणु
	अचिन्हित लघु addr;
	स्थिर अक्षर *name;
	काष्ठा device *hwmon_dev;
	काष्ठा mutex lock;
	क्रमागत chips type;

	काष्ठा mutex update_lock;
	अक्षर valid;		/* !=0 अगर following fields are valid */
	अचिन्हित दीर्घ last_updated;	/* In jअगरfies */

	u8 in[9];		/* Register value */
	u8 in_max[9];		/* Register value */
	u8 in_min[9];		/* Register value */
	u8 fan[3];		/* Register value */
	u8 fan_min[3];		/* Register value */
	u16 temp[3];		/* Register value */
	u16 temp_max[3];	/* Register value */
	u16 temp_max_hyst[3];	/* Register value */
	u8 fan_भाग[3];		/* Register encoding, shअगरted right */
	u8 vid;			/* Register encoding, combined */
	u32 alarms;		/* Register encoding, combined */
	u32 beep_mask;		/* Register encoding, combined */
	u8 pwm[3];		/* Register value */
	u8 pwm_enable[3];	/* 1 = manual
				 * 2 = thermal cruise (also called SmartFan I)
				 * 3 = fan speed cruise
				 */
	u8 pwm_freq[3];		/* Register value */
	u16 sens[3];		/* 1 = pentium diode; 2 = 3904 diode;
				 * 4 = thermistor
				 */
	u8 vrm;
	u8 vrm_ovt;		/* Register value, 627THF/637HF/687THF only */

#अगर_घोषित CONFIG_PM
	/* Remember extra रेजिस्टर values over suspend/resume */
	u8 scfg1;
	u8 scfg2;
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक w83627hf_probe(काष्ठा platक्रमm_device *pdev);
अटल पूर्णांक w83627hf_हटाओ(काष्ठा platक्रमm_device *pdev);

अटल पूर्णांक w83627hf_पढ़ो_value(काष्ठा w83627hf_data *data, u16 reg);
अटल पूर्णांक w83627hf_ग_लिखो_value(काष्ठा w83627hf_data *data, u16 reg, u16 value);
अटल व्योम w83627hf_update_fan_भाग(काष्ठा w83627hf_data *data);
अटल काष्ठा w83627hf_data *w83627hf_update_device(काष्ठा device *dev);
अटल व्योम w83627hf_init_device(काष्ठा platक्रमm_device *pdev);

#अगर_घोषित CONFIG_PM
अटल पूर्णांक w83627hf_suspend(काष्ठा device *dev)
अणु
	काष्ठा w83627hf_data *data = w83627hf_update_device(dev);

	mutex_lock(&data->update_lock);
	data->scfg1 = w83627hf_पढ़ो_value(data, W83781D_REG_SCFG1);
	data->scfg2 = w83627hf_पढ़ो_value(data, W83781D_REG_SCFG2);
	mutex_unlock(&data->update_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक w83627hf_resume(काष्ठा device *dev)
अणु
	काष्ठा w83627hf_data *data = dev_get_drvdata(dev);
	पूर्णांक i, num_temps = (data->type == w83697hf) ? 2 : 3;

	/* Restore limits */
	mutex_lock(&data->update_lock);
	क्रम (i = 0; i <= 8; i++) अणु
		/* skip missing sensors */
		अगर (((data->type == w83697hf) && (i == 1)) ||
		    ((data->type != w83627hf && data->type != w83697hf)
		    && (i == 5 || i == 6)))
			जारी;
		w83627hf_ग_लिखो_value(data, W83781D_REG_IN_MAX(i),
				     data->in_max[i]);
		w83627hf_ग_लिखो_value(data, W83781D_REG_IN_MIN(i),
				     data->in_min[i]);
	पूर्ण
	क्रम (i = 0; i <= 2; i++)
		w83627hf_ग_लिखो_value(data, W83627HF_REG_FAN_MIN(i),
				     data->fan_min[i]);
	क्रम (i = 0; i < num_temps; i++) अणु
		w83627hf_ग_लिखो_value(data, w83627hf_reg_temp_over[i],
				     data->temp_max[i]);
		w83627hf_ग_लिखो_value(data, w83627hf_reg_temp_hyst[i],
				     data->temp_max_hyst[i]);
	पूर्ण

	/* Fixup BIOS bugs */
	अगर (data->type == w83627thf || data->type == w83637hf ||
	    data->type == w83687thf)
		w83627hf_ग_लिखो_value(data, W83627THF_REG_VRM_OVT_CFG,
				     data->vrm_ovt);
	w83627hf_ग_लिखो_value(data, W83781D_REG_SCFG1, data->scfg1);
	w83627hf_ग_लिखो_value(data, W83781D_REG_SCFG2, data->scfg2);

	/* Force re-पढ़ोing all values */
	data->valid = 0;
	mutex_unlock(&data->update_lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops w83627hf_dev_pm_ops = अणु
	.suspend = w83627hf_suspend,
	.resume = w83627hf_resume,
पूर्ण;

#घोषणा W83627HF_DEV_PM_OPS	(&w83627hf_dev_pm_ops)
#अन्यथा
#घोषणा W83627HF_DEV_PM_OPS	शून्य
#पूर्ण_अगर /* CONFIG_PM */

अटल काष्ठा platक्रमm_driver w83627hf_driver = अणु
	.driver = अणु
		.name	= DRVNAME,
		.pm	= W83627HF_DEV_PM_OPS,
	पूर्ण,
	.probe		= w83627hf_probe,
	.हटाओ		= w83627hf_हटाओ,
पूर्ण;

अटल sमाप_प्रकार
in_input_show(काष्ठा device *dev, काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(devattr)->index;
	काष्ठा w83627hf_data *data = w83627hf_update_device(dev);
	वापस प्र_लिखो(buf, "%ld\n", (दीर्घ)IN_FROM_REG(data->in[nr]));
पूर्ण
अटल sमाप_प्रकार
in_min_show(काष्ठा device *dev, काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(devattr)->index;
	काष्ठा w83627hf_data *data = w83627hf_update_device(dev);
	वापस प्र_लिखो(buf, "%ld\n", (दीर्घ)IN_FROM_REG(data->in_min[nr]));
पूर्ण
अटल sमाप_प्रकार
in_max_show(काष्ठा device *dev, काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(devattr)->index;
	काष्ठा w83627hf_data *data = w83627hf_update_device(dev);
	वापस प्र_लिखो(buf, "%ld\n", (दीर्घ)IN_FROM_REG(data->in_max[nr]));
पूर्ण
अटल sमाप_प्रकार
in_min_store(काष्ठा device *dev, काष्ठा device_attribute *devattr,
	     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक nr = to_sensor_dev_attr(devattr)->index;
	काष्ठा w83627hf_data *data = dev_get_drvdata(dev);
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->in_min[nr] = IN_TO_REG(val);
	w83627hf_ग_लिखो_value(data, W83781D_REG_IN_MIN(nr), data->in_min[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण
अटल sमाप_प्रकार
in_max_store(काष्ठा device *dev, काष्ठा device_attribute *devattr,
	     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक nr = to_sensor_dev_attr(devattr)->index;
	काष्ठा w83627hf_data *data = dev_get_drvdata(dev);
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->in_max[nr] = IN_TO_REG(val);
	w83627hf_ग_लिखो_value(data, W83781D_REG_IN_MAX(nr), data->in_max[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(in1_input, in_input, 1);
अटल SENSOR_DEVICE_ATTR_RW(in1_min, in_min, 1);
अटल SENSOR_DEVICE_ATTR_RW(in1_max, in_max, 1);
अटल SENSOR_DEVICE_ATTR_RO(in2_input, in_input, 2);
अटल SENSOR_DEVICE_ATTR_RW(in2_min, in_min, 2);
अटल SENSOR_DEVICE_ATTR_RW(in2_max, in_max, 2);
अटल SENSOR_DEVICE_ATTR_RO(in3_input, in_input, 3);
अटल SENSOR_DEVICE_ATTR_RW(in3_min, in_min, 3);
अटल SENSOR_DEVICE_ATTR_RW(in3_max, in_max, 3);
अटल SENSOR_DEVICE_ATTR_RO(in4_input, in_input, 4);
अटल SENSOR_DEVICE_ATTR_RW(in4_min, in_min, 4);
अटल SENSOR_DEVICE_ATTR_RW(in4_max, in_max, 4);
अटल SENSOR_DEVICE_ATTR_RO(in5_input, in_input, 5);
अटल SENSOR_DEVICE_ATTR_RW(in5_min, in_min, 5);
अटल SENSOR_DEVICE_ATTR_RW(in5_max, in_max, 5);
अटल SENSOR_DEVICE_ATTR_RO(in6_input, in_input, 6);
अटल SENSOR_DEVICE_ATTR_RW(in6_min, in_min, 6);
अटल SENSOR_DEVICE_ATTR_RW(in6_max, in_max, 6);
अटल SENSOR_DEVICE_ATTR_RO(in7_input, in_input, 7);
अटल SENSOR_DEVICE_ATTR_RW(in7_min, in_min, 7);
अटल SENSOR_DEVICE_ATTR_RW(in7_max, in_max, 7);
अटल SENSOR_DEVICE_ATTR_RO(in8_input, in_input, 8);
अटल SENSOR_DEVICE_ATTR_RW(in8_min, in_min, 8);
अटल SENSOR_DEVICE_ATTR_RW(in8_max, in_max, 8);

/* use a dअगरferent set of functions क्रम in0 */
अटल sमाप_प्रकार show_in_0(काष्ठा w83627hf_data *data, अक्षर *buf, u8 reg)
अणु
	दीर्घ in0;

	अगर ((data->vrm_ovt & 0x01) &&
		(w83627thf == data->type || w83637hf == data->type
		 || w83687thf == data->type))

		/* use VRM9 calculation */
		in0 = (दीर्घ)((reg * 488 + 70000 + 50) / 100);
	अन्यथा
		/* use VRM8 (standard) calculation */
		in0 = (दीर्घ)IN_FROM_REG(reg);

	वापस प्र_लिखो(buf,"%ld\n", in0);
पूर्ण

अटल sमाप_प्रकार in0_input_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा w83627hf_data *data = w83627hf_update_device(dev);
	वापस show_in_0(data, buf, data->in[0]);
पूर्ण

अटल sमाप_प्रकार in0_min_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा w83627hf_data *data = w83627hf_update_device(dev);
	वापस show_in_0(data, buf, data->in_min[0]);
पूर्ण

अटल sमाप_प्रकार in0_max_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा w83627hf_data *data = w83627hf_update_device(dev);
	वापस show_in_0(data, buf, data->in_max[0]);
पूर्ण

अटल sमाप_प्रकार in0_min_store(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			     माप_प्रकार count)
अणु
	काष्ठा w83627hf_data *data = dev_get_drvdata(dev);
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	
	अगर ((data->vrm_ovt & 0x01) &&
		(w83627thf == data->type || w83637hf == data->type
		 || w83687thf == data->type))

		/* use VRM9 calculation */
		data->in_min[0] =
			clamp_val(((val * 100) - 70000 + 244) / 488, 0, 255);
	अन्यथा
		/* use VRM8 (standard) calculation */
		data->in_min[0] = IN_TO_REG(val);

	w83627hf_ग_लिखो_value(data, W83781D_REG_IN_MIN(0), data->in_min[0]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार in0_max_store(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			     माप_प्रकार count)
अणु
	काष्ठा w83627hf_data *data = dev_get_drvdata(dev);
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);

	अगर ((data->vrm_ovt & 0x01) &&
		(w83627thf == data->type || w83637hf == data->type
		 || w83687thf == data->type))
		
		/* use VRM9 calculation */
		data->in_max[0] =
			clamp_val(((val * 100) - 70000 + 244) / 488, 0, 255);
	अन्यथा
		/* use VRM8 (standard) calculation */
		data->in_max[0] = IN_TO_REG(val);

	w83627hf_ग_लिखो_value(data, W83781D_REG_IN_MAX(0), data->in_max[0]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल DEVICE_ATTR_RO(in0_input);
अटल DEVICE_ATTR_RW(in0_min);
अटल DEVICE_ATTR_RW(in0_max);

अटल sमाप_प्रकार
fan_input_show(काष्ठा device *dev, काष्ठा device_attribute *devattr,
	       अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(devattr)->index;
	काष्ठा w83627hf_data *data = w83627hf_update_device(dev);
	वापस प्र_लिखो(buf, "%ld\n", FAN_FROM_REG(data->fan[nr],
				(दीर्घ)DIV_FROM_REG(data->fan_भाग[nr])));
पूर्ण
अटल sमाप_प्रकार
fan_min_show(काष्ठा device *dev, काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(devattr)->index;
	काष्ठा w83627hf_data *data = w83627hf_update_device(dev);
	वापस प्र_लिखो(buf, "%ld\n", FAN_FROM_REG(data->fan_min[nr],
				(दीर्घ)DIV_FROM_REG(data->fan_भाग[nr])));
पूर्ण
अटल sमाप_प्रकार
fan_min_store(काष्ठा device *dev, काष्ठा device_attribute *devattr,
	      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक nr = to_sensor_dev_attr(devattr)->index;
	काष्ठा w83627hf_data *data = dev_get_drvdata(dev);
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->fan_min[nr] = FAN_TO_REG(val, DIV_FROM_REG(data->fan_भाग[nr]));
	w83627hf_ग_लिखो_value(data, W83627HF_REG_FAN_MIN(nr),
			     data->fan_min[nr]);

	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(fan1_input, fan_input, 0);
अटल SENSOR_DEVICE_ATTR_RW(fan1_min, fan_min, 0);
अटल SENSOR_DEVICE_ATTR_RO(fan2_input, fan_input, 1);
अटल SENSOR_DEVICE_ATTR_RW(fan2_min, fan_min, 1);
अटल SENSOR_DEVICE_ATTR_RO(fan3_input, fan_input, 2);
अटल SENSOR_DEVICE_ATTR_RW(fan3_min, fan_min, 2);

अटल sमाप_प्रकार
temp_show(काष्ठा device *dev, काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(devattr)->index;
	काष्ठा w83627hf_data *data = w83627hf_update_device(dev);

	u16 पंचांगp = data->temp[nr];
	वापस प्र_लिखो(buf, "%ld\n", (nr) ? (दीर्घ) LM75_TEMP_FROM_REG(पंचांगp)
					  : (दीर्घ) TEMP_FROM_REG(पंचांगp));
पूर्ण

अटल sमाप_प्रकार
temp_max_show(काष्ठा device *dev, काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(devattr)->index;
	काष्ठा w83627hf_data *data = w83627hf_update_device(dev);

	u16 पंचांगp = data->temp_max[nr];
	वापस प्र_लिखो(buf, "%ld\n", (nr) ? (दीर्घ) LM75_TEMP_FROM_REG(पंचांगp)
					  : (दीर्घ) TEMP_FROM_REG(पंचांगp));
पूर्ण

अटल sमाप_प्रकार
temp_max_hyst_show(काष्ठा device *dev, काष्ठा device_attribute *devattr,
		   अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(devattr)->index;
	काष्ठा w83627hf_data *data = w83627hf_update_device(dev);

	u16 पंचांगp = data->temp_max_hyst[nr];
	वापस प्र_लिखो(buf, "%ld\n", (nr) ? (दीर्घ) LM75_TEMP_FROM_REG(पंचांगp)
					  : (दीर्घ) TEMP_FROM_REG(पंचांगp));
पूर्ण

अटल sमाप_प्रकार
temp_max_store(काष्ठा device *dev, काष्ठा device_attribute *devattr,
	       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक nr = to_sensor_dev_attr(devattr)->index;
	काष्ठा w83627hf_data *data = dev_get_drvdata(dev);
	u16 पंचांगp;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	पंचांगp = (nr) ? LM75_TEMP_TO_REG(val) : TEMP_TO_REG(val);
	mutex_lock(&data->update_lock);
	data->temp_max[nr] = पंचांगp;
	w83627hf_ग_लिखो_value(data, w83627hf_reg_temp_over[nr], पंचांगp);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार
temp_max_hyst_store(काष्ठा device *dev, काष्ठा device_attribute *devattr,
		    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक nr = to_sensor_dev_attr(devattr)->index;
	काष्ठा w83627hf_data *data = dev_get_drvdata(dev);
	u16 पंचांगp;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	पंचांगp = (nr) ? LM75_TEMP_TO_REG(val) : TEMP_TO_REG(val);
	mutex_lock(&data->update_lock);
	data->temp_max_hyst[nr] = पंचांगp;
	w83627hf_ग_लिखो_value(data, w83627hf_reg_temp_hyst[nr], पंचांगp);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(temp1_input, temp, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp1_max, temp_max, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp1_max_hyst, temp_max_hyst, 0);
अटल SENSOR_DEVICE_ATTR_RO(temp2_input, temp, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp2_max, temp_max, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp2_max_hyst, temp_max_hyst, 1);
अटल SENSOR_DEVICE_ATTR_RO(temp3_input, temp, 2);
अटल SENSOR_DEVICE_ATTR_RW(temp3_max, temp_max, 2);
अटल SENSOR_DEVICE_ATTR_RW(temp3_max_hyst, temp_max_hyst, 2);

अटल sमाप_प्रकार
cpu0_vid_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा w83627hf_data *data = w83627hf_update_device(dev);
	वापस प्र_लिखो(buf, "%ld\n", (दीर्घ) vid_from_reg(data->vid, data->vrm));
पूर्ण
अटल DEVICE_ATTR_RO(cpu0_vid);

अटल sमाप_प्रकार
vrm_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा w83627hf_data *data = dev_get_drvdata(dev);
	वापस प्र_लिखो(buf, "%ld\n", (दीर्घ) data->vrm);
पूर्ण
अटल sमाप_प्रकार
vrm_store(काष्ठा device *dev, काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
	  माप_प्रकार count)
अणु
	काष्ठा w83627hf_data *data = dev_get_drvdata(dev);
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	अगर (val > 255)
		वापस -EINVAL;
	data->vrm = val;

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(vrm);

अटल sमाप_प्रकार
alarms_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा w83627hf_data *data = w83627hf_update_device(dev);
	वापस प्र_लिखो(buf, "%ld\n", (दीर्घ) data->alarms);
पूर्ण
अटल DEVICE_ATTR_RO(alarms);

अटल sमाप_प्रकार
alarm_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा w83627hf_data *data = w83627hf_update_device(dev);
	पूर्णांक bitnr = to_sensor_dev_attr(attr)->index;
	वापस प्र_लिखो(buf, "%u\n", (data->alarms >> bitnr) & 1);
पूर्ण
अटल SENSOR_DEVICE_ATTR_RO(in0_alarm, alarm, 0);
अटल SENSOR_DEVICE_ATTR_RO(in1_alarm, alarm, 1);
अटल SENSOR_DEVICE_ATTR_RO(in2_alarm, alarm, 2);
अटल SENSOR_DEVICE_ATTR_RO(in3_alarm, alarm, 3);
अटल SENSOR_DEVICE_ATTR_RO(in4_alarm, alarm, 8);
अटल SENSOR_DEVICE_ATTR_RO(in5_alarm, alarm, 9);
अटल SENSOR_DEVICE_ATTR_RO(in6_alarm, alarm, 10);
अटल SENSOR_DEVICE_ATTR_RO(in7_alarm, alarm, 16);
अटल SENSOR_DEVICE_ATTR_RO(in8_alarm, alarm, 17);
अटल SENSOR_DEVICE_ATTR_RO(fan1_alarm, alarm, 6);
अटल SENSOR_DEVICE_ATTR_RO(fan2_alarm, alarm, 7);
अटल SENSOR_DEVICE_ATTR_RO(fan3_alarm, alarm, 11);
अटल SENSOR_DEVICE_ATTR_RO(temp1_alarm, alarm, 4);
अटल SENSOR_DEVICE_ATTR_RO(temp2_alarm, alarm, 5);
अटल SENSOR_DEVICE_ATTR_RO(temp3_alarm, alarm, 13);

अटल sमाप_प्रकार
beep_mask_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा w83627hf_data *data = w83627hf_update_device(dev);
	वापस प्र_लिखो(buf, "%ld\n",
		      (दीर्घ)BEEP_MASK_FROM_REG(data->beep_mask));
पूर्ण

अटल sमाप_प्रकार
beep_mask_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा w83627hf_data *data = dev_get_drvdata(dev);
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);

	/* preserve beep enable */
	data->beep_mask = (data->beep_mask & 0x8000)
			| BEEP_MASK_TO_REG(val);
	w83627hf_ग_लिखो_value(data, W83781D_REG_BEEP_INTS1,
			    data->beep_mask & 0xff);
	w83627hf_ग_लिखो_value(data, W83781D_REG_BEEP_INTS3,
			    ((data->beep_mask) >> 16) & 0xff);
	w83627hf_ग_लिखो_value(data, W83781D_REG_BEEP_INTS2,
			    (data->beep_mask >> 8) & 0xff);

	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(beep_mask);

अटल sमाप_प्रकार
beep_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा w83627hf_data *data = w83627hf_update_device(dev);
	पूर्णांक bitnr = to_sensor_dev_attr(attr)->index;
	वापस प्र_लिखो(buf, "%u\n", (data->beep_mask >> bitnr) & 1);
पूर्ण

अटल sमाप_प्रकार
beep_store(काष्ठा device *dev, काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
	   माप_प्रकार count)
अणु
	काष्ठा w83627hf_data *data = dev_get_drvdata(dev);
	पूर्णांक bitnr = to_sensor_dev_attr(attr)->index;
	u8 reg;
	अचिन्हित दीर्घ bit;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &bit);
	अगर (err)
		वापस err;

	अगर (bit & ~1)
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	अगर (bit)
		data->beep_mask |= (1 << bitnr);
	अन्यथा
		data->beep_mask &= ~(1 << bitnr);

	अगर (bitnr < 8) अणु
		reg = w83627hf_पढ़ो_value(data, W83781D_REG_BEEP_INTS1);
		अगर (bit)
			reg |= (1 << bitnr);
		अन्यथा
			reg &= ~(1 << bitnr);
		w83627hf_ग_लिखो_value(data, W83781D_REG_BEEP_INTS1, reg);
	पूर्ण अन्यथा अगर (bitnr < 16) अणु
		reg = w83627hf_पढ़ो_value(data, W83781D_REG_BEEP_INTS2);
		अगर (bit)
			reg |= (1 << (bitnr - 8));
		अन्यथा
			reg &= ~(1 << (bitnr - 8));
		w83627hf_ग_लिखो_value(data, W83781D_REG_BEEP_INTS2, reg);
	पूर्ण अन्यथा अणु
		reg = w83627hf_पढ़ो_value(data, W83781D_REG_BEEP_INTS3);
		अगर (bit)
			reg |= (1 << (bitnr - 16));
		अन्यथा
			reg &= ~(1 << (bitnr - 16));
		w83627hf_ग_लिखो_value(data, W83781D_REG_BEEP_INTS3, reg);
	पूर्ण
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RW(in0_beep, beep, 0);
अटल SENSOR_DEVICE_ATTR_RW(in1_beep, beep, 1);
अटल SENSOR_DEVICE_ATTR_RW(in2_beep, beep, 2);
अटल SENSOR_DEVICE_ATTR_RW(in3_beep, beep, 3);
अटल SENSOR_DEVICE_ATTR_RW(in4_beep, beep, 8);
अटल SENSOR_DEVICE_ATTR_RW(in5_beep, beep, 9);
अटल SENSOR_DEVICE_ATTR_RW(in6_beep, beep, 10);
अटल SENSOR_DEVICE_ATTR_RW(in7_beep, beep, 16);
अटल SENSOR_DEVICE_ATTR_RW(in8_beep, beep, 17);
अटल SENSOR_DEVICE_ATTR_RW(fan1_beep, beep, 6);
अटल SENSOR_DEVICE_ATTR_RW(fan2_beep, beep, 7);
अटल SENSOR_DEVICE_ATTR_RW(fan3_beep, beep, 11);
अटल SENSOR_DEVICE_ATTR_RW(temp1_beep, beep, 4);
अटल SENSOR_DEVICE_ATTR_RW(temp2_beep, beep, 5);
अटल SENSOR_DEVICE_ATTR_RW(temp3_beep, beep, 13);
अटल SENSOR_DEVICE_ATTR_RW(beep_enable, beep, 15);

अटल sमाप_प्रकार
fan_भाग_show(काष्ठा device *dev, काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(devattr)->index;
	काष्ठा w83627hf_data *data = w83627hf_update_device(dev);
	वापस प्र_लिखो(buf, "%ld\n",
		       (दीर्घ) DIV_FROM_REG(data->fan_भाग[nr]));
पूर्ण
/*
 * Note: we save and restore the fan minimum here, because its value is
 * determined in part by the fan भागisor.  This follows the principle of
 * least surprise; the user करोesn't expect the fan minimum to change just
 * because the भागisor changed.
 */
अटल sमाप_प्रकार
fan_भाग_store(काष्ठा device *dev, काष्ठा device_attribute *devattr,
	      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक nr = to_sensor_dev_attr(devattr)->index;
	काष्ठा w83627hf_data *data = dev_get_drvdata(dev);
	अचिन्हित दीर्घ min;
	u8 reg;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);

	/* Save fan_min */
	min = FAN_FROM_REG(data->fan_min[nr],
			   DIV_FROM_REG(data->fan_भाग[nr]));

	data->fan_भाग[nr] = DIV_TO_REG(val);

	reg = (w83627hf_पढ़ो_value(data, nr==2 ? W83781D_REG_PIN : W83781D_REG_VID_FANDIV)
	       & (nr==0 ? 0xcf : 0x3f))
	    | ((data->fan_भाग[nr] & 0x03) << (nr==0 ? 4 : 6));
	w83627hf_ग_लिखो_value(data, nr==2 ? W83781D_REG_PIN : W83781D_REG_VID_FANDIV, reg);

	reg = (w83627hf_पढ़ो_value(data, W83781D_REG_VBAT)
	       & ~(1 << (5 + nr)))
	    | ((data->fan_भाग[nr] & 0x04) << (3 + nr));
	w83627hf_ग_लिखो_value(data, W83781D_REG_VBAT, reg);

	/* Restore fan_min */
	data->fan_min[nr] = FAN_TO_REG(min, DIV_FROM_REG(data->fan_भाग[nr]));
	w83627hf_ग_लिखो_value(data, W83627HF_REG_FAN_MIN(nr), data->fan_min[nr]);

	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RW(fan1_भाग, fan_भाग, 0);
अटल SENSOR_DEVICE_ATTR_RW(fan2_भाग, fan_भाग, 1);
अटल SENSOR_DEVICE_ATTR_RW(fan3_भाग, fan_भाग, 2);

अटल sमाप_प्रकार
pwm_show(काष्ठा device *dev, काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(devattr)->index;
	काष्ठा w83627hf_data *data = w83627hf_update_device(dev);
	वापस प्र_लिखो(buf, "%ld\n", (दीर्घ) data->pwm[nr]);
पूर्ण

अटल sमाप_प्रकार
pwm_store(काष्ठा device *dev, काष्ठा device_attribute *devattr,
	  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक nr = to_sensor_dev_attr(devattr)->index;
	काष्ठा w83627hf_data *data = dev_get_drvdata(dev);
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);

	अगर (data->type == w83627thf) अणु
		/* bits 0-3 are reserved  in 627THF */
		data->pwm[nr] = PWM_TO_REG(val) & 0xf0;
		w83627hf_ग_लिखो_value(data,
				     W836X7HF_REG_PWM(data->type, nr),
				     data->pwm[nr] |
				     (w83627hf_पढ़ो_value(data,
				     W836X7HF_REG_PWM(data->type, nr)) & 0x0f));
	पूर्ण अन्यथा अणु
		data->pwm[nr] = PWM_TO_REG(val);
		w83627hf_ग_लिखो_value(data,
				     W836X7HF_REG_PWM(data->type, nr),
				     data->pwm[nr]);
	पूर्ण

	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RW(pwm1, pwm, 0);
अटल SENSOR_DEVICE_ATTR_RW(pwm2, pwm, 1);
अटल SENSOR_DEVICE_ATTR_RW(pwm3, pwm, 2);

अटल sमाप_प्रकार
pwm_enable_show(काष्ठा device *dev, काष्ठा device_attribute *devattr,
		अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(devattr)->index;
	काष्ठा w83627hf_data *data = w83627hf_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", data->pwm_enable[nr]);
पूर्ण

अटल sमाप_प्रकार
pwm_enable_store(काष्ठा device *dev, काष्ठा device_attribute *devattr,
		 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक nr = to_sensor_dev_attr(devattr)->index;
	काष्ठा w83627hf_data *data = dev_get_drvdata(dev);
	u8 reg;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	अगर (!val || val > 3)	/* modes 1, 2 and 3 are supported */
		वापस -EINVAL;
	mutex_lock(&data->update_lock);
	data->pwm_enable[nr] = val;
	reg = w83627hf_पढ़ो_value(data, W83627THF_REG_PWM_ENABLE[nr]);
	reg &= ~(0x03 << W83627THF_PWM_ENABLE_SHIFT[nr]);
	reg |= (val - 1) << W83627THF_PWM_ENABLE_SHIFT[nr];
	w83627hf_ग_लिखो_value(data, W83627THF_REG_PWM_ENABLE[nr], reg);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RW(pwm1_enable, pwm_enable, 0);
अटल SENSOR_DEVICE_ATTR_RW(pwm2_enable, pwm_enable, 1);
अटल SENSOR_DEVICE_ATTR_RW(pwm3_enable, pwm_enable, 2);

अटल sमाप_प्रकार
pwm_freq_show(काष्ठा device *dev, काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(devattr)->index;
	काष्ठा w83627hf_data *data = w83627hf_update_device(dev);
	अगर (data->type == w83627hf)
		वापस प्र_लिखो(buf, "%ld\n",
			pwm_freq_from_reg_627hf(data->pwm_freq[nr]));
	अन्यथा
		वापस प्र_लिखो(buf, "%ld\n",
			pwm_freq_from_reg(data->pwm_freq[nr]));
पूर्ण

अटल sमाप_प्रकार
pwm_freq_store(काष्ठा device *dev, काष्ठा device_attribute *devattr,
	       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक nr = to_sensor_dev_attr(devattr)->index;
	काष्ठा w83627hf_data *data = dev_get_drvdata(dev);
	अटल स्थिर u8 mask[]=अणु0xF8, 0x8Fपूर्ण;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);

	अगर (data->type == w83627hf) अणु
		data->pwm_freq[nr] = pwm_freq_to_reg_627hf(val);
		w83627hf_ग_लिखो_value(data, W83627HF_REG_PWM_FREQ,
				(data->pwm_freq[nr] << (nr*4)) |
				(w83627hf_पढ़ो_value(data,
				W83627HF_REG_PWM_FREQ) & mask[nr]));
	पूर्ण अन्यथा अणु
		data->pwm_freq[nr] = pwm_freq_to_reg(val);
		w83627hf_ग_लिखो_value(data, W83637HF_REG_PWM_FREQ[nr],
				data->pwm_freq[nr]);
	पूर्ण

	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RW(pwm1_freq, pwm_freq, 0);
अटल SENSOR_DEVICE_ATTR_RW(pwm2_freq, pwm_freq, 1);
अटल SENSOR_DEVICE_ATTR_RW(pwm3_freq, pwm_freq, 2);

अटल sमाप_प्रकार
temp_type_show(काष्ठा device *dev, काष्ठा device_attribute *devattr,
	       अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(devattr)->index;
	काष्ठा w83627hf_data *data = w83627hf_update_device(dev);
	वापस प्र_लिखो(buf, "%ld\n", (दीर्घ) data->sens[nr]);
पूर्ण

अटल sमाप_प्रकार
temp_type_store(काष्ठा device *dev, काष्ठा device_attribute *devattr,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक nr = to_sensor_dev_attr(devattr)->index;
	काष्ठा w83627hf_data *data = dev_get_drvdata(dev);
	अचिन्हित दीर्घ val;
	u32 पंचांगp;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);

	चयन (val) अणु
	हाल 1:		/* PII/Celeron diode */
		पंचांगp = w83627hf_पढ़ो_value(data, W83781D_REG_SCFG1);
		w83627hf_ग_लिखो_value(data, W83781D_REG_SCFG1,
				    पंचांगp | BIT_SCFG1[nr]);
		पंचांगp = w83627hf_पढ़ो_value(data, W83781D_REG_SCFG2);
		w83627hf_ग_लिखो_value(data, W83781D_REG_SCFG2,
				    पंचांगp | BIT_SCFG2[nr]);
		data->sens[nr] = val;
		अवरोध;
	हाल 2:		/* 3904 */
		पंचांगp = w83627hf_पढ़ो_value(data, W83781D_REG_SCFG1);
		w83627hf_ग_लिखो_value(data, W83781D_REG_SCFG1,
				    पंचांगp | BIT_SCFG1[nr]);
		पंचांगp = w83627hf_पढ़ो_value(data, W83781D_REG_SCFG2);
		w83627hf_ग_लिखो_value(data, W83781D_REG_SCFG2,
				    पंचांगp & ~BIT_SCFG2[nr]);
		data->sens[nr] = val;
		अवरोध;
	हाल W83781D_DEFAULT_BETA:
		dev_warn(dev, "Sensor type %d is deprecated, please use 4 "
			 "instead\n", W83781D_DEFAULT_BETA);
		fallthrough;
	हाल 4:		/* thermistor */
		पंचांगp = w83627hf_पढ़ो_value(data, W83781D_REG_SCFG1);
		w83627hf_ग_लिखो_value(data, W83781D_REG_SCFG1,
				    पंचांगp & ~BIT_SCFG1[nr]);
		data->sens[nr] = val;
		अवरोध;
	शेष:
		dev_err(dev,
		       "Invalid sensor type %ld; must be 1, 2, or 4\n",
		       (दीर्घ) val);
		अवरोध;
	पूर्ण

	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RW(temp1_type, temp_type, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp2_type, temp_type, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp3_type, temp_type, 2);

अटल sमाप_प्रकार
name_show(काष्ठा device *dev, काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा w83627hf_data *data = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%s\n", data->name);
पूर्ण
अटल DEVICE_ATTR_RO(name);

अटल पूर्णांक __init w83627hf_find(पूर्णांक sioaddr, अचिन्हित लघु *addr,
				काष्ठा w83627hf_sio_data *sio_data)
अणु
	पूर्णांक err;
	u16 val;

	अटल __initस्थिर अक्षर *स्थिर names[] = अणु
		"W83627HF",
		"W83627THF",
		"W83697HF",
		"W83637HF",
		"W83687THF",
	पूर्ण;

	sio_data->sioaddr = sioaddr;
	err = superio_enter(sio_data);
	अगर (err)
		वापस err;

	err = -ENODEV;
	val = क्रमce_id ? क्रमce_id : superio_inb(sio_data, DEVID);
	चयन (val) अणु
	हाल W627_DEVID:
		sio_data->type = w83627hf;
		अवरोध;
	हाल W627THF_DEVID:
		sio_data->type = w83627thf;
		अवरोध;
	हाल W697_DEVID:
		sio_data->type = w83697hf;
		अवरोध;
	हाल W637_DEVID:
		sio_data->type = w83637hf;
		अवरोध;
	हाल W687THF_DEVID:
		sio_data->type = w83687thf;
		अवरोध;
	हाल 0xff:	/* No device at all */
		जाओ निकास;
	शेष:
		pr_debug(DRVNAME ": Unsupported chip (DEVID=0x%02x)\n", val);
		जाओ निकास;
	पूर्ण

	superio_select(sio_data, W83627HF_LD_HWM);
	val = (superio_inb(sio_data, WINB_BASE_REG) << 8) |
	       superio_inb(sio_data, WINB_BASE_REG + 1);
	*addr = val & WINB_ALIGNMENT;
	अगर (*addr == 0) अणु
		pr_warn("Base address not set, skipping\n");
		जाओ निकास;
	पूर्ण

	val = superio_inb(sio_data, WINB_ACT_REG);
	अगर (!(val & 0x01)) अणु
		pr_warn("Enabling HWM logical device\n");
		superio_outb(sio_data, WINB_ACT_REG, val | 0x01);
	पूर्ण

	err = 0;
	pr_info(DRVNAME ": Found %s chip at %#x\n",
		names[sio_data->type], *addr);

 निकास:
	superio_निकास(sio_data);
	वापस err;
पूर्ण

#घोषणा VIN_UNIT_ATTRS(_X_)	\
	&sensor_dev_attr_in##_X_##_input.dev_attr.attr,		\
	&sensor_dev_attr_in##_X_##_min.dev_attr.attr,		\
	&sensor_dev_attr_in##_X_##_max.dev_attr.attr,		\
	&sensor_dev_attr_in##_X_##_alarm.dev_attr.attr,		\
	&sensor_dev_attr_in##_X_##_beep.dev_attr.attr

#घोषणा FAN_UNIT_ATTRS(_X_)	\
	&sensor_dev_attr_fan##_X_##_input.dev_attr.attr,	\
	&sensor_dev_attr_fan##_X_##_min.dev_attr.attr,		\
	&sensor_dev_attr_fan##_X_##_भाग.dev_attr.attr,		\
	&sensor_dev_attr_fan##_X_##_alarm.dev_attr.attr,	\
	&sensor_dev_attr_fan##_X_##_beep.dev_attr.attr

#घोषणा TEMP_UNIT_ATTRS(_X_)	\
	&sensor_dev_attr_temp##_X_##_input.dev_attr.attr,	\
	&sensor_dev_attr_temp##_X_##_max.dev_attr.attr,		\
	&sensor_dev_attr_temp##_X_##_max_hyst.dev_attr.attr,	\
	&sensor_dev_attr_temp##_X_##_type.dev_attr.attr,	\
	&sensor_dev_attr_temp##_X_##_alarm.dev_attr.attr,	\
	&sensor_dev_attr_temp##_X_##_beep.dev_attr.attr

अटल काष्ठा attribute *w83627hf_attributes[] = अणु
	&dev_attr_in0_input.attr,
	&dev_attr_in0_min.attr,
	&dev_attr_in0_max.attr,
	&sensor_dev_attr_in0_alarm.dev_attr.attr,
	&sensor_dev_attr_in0_beep.dev_attr.attr,
	VIN_UNIT_ATTRS(2),
	VIN_UNIT_ATTRS(3),
	VIN_UNIT_ATTRS(4),
	VIN_UNIT_ATTRS(7),
	VIN_UNIT_ATTRS(8),

	FAN_UNIT_ATTRS(1),
	FAN_UNIT_ATTRS(2),

	TEMP_UNIT_ATTRS(1),
	TEMP_UNIT_ATTRS(2),

	&dev_attr_alarms.attr,
	&sensor_dev_attr_beep_enable.dev_attr.attr,
	&dev_attr_beep_mask.attr,

	&sensor_dev_attr_pwm1.dev_attr.attr,
	&sensor_dev_attr_pwm2.dev_attr.attr,
	&dev_attr_name.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group w83627hf_group = अणु
	.attrs = w83627hf_attributes,
पूर्ण;

अटल काष्ठा attribute *w83627hf_attributes_opt[] = अणु
	VIN_UNIT_ATTRS(1),
	VIN_UNIT_ATTRS(5),
	VIN_UNIT_ATTRS(6),

	FAN_UNIT_ATTRS(3),
	TEMP_UNIT_ATTRS(3),
	&sensor_dev_attr_pwm3.dev_attr.attr,

	&sensor_dev_attr_pwm1_freq.dev_attr.attr,
	&sensor_dev_attr_pwm2_freq.dev_attr.attr,
	&sensor_dev_attr_pwm3_freq.dev_attr.attr,

	&sensor_dev_attr_pwm1_enable.dev_attr.attr,
	&sensor_dev_attr_pwm2_enable.dev_attr.attr,
	&sensor_dev_attr_pwm3_enable.dev_attr.attr,

	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group w83627hf_group_opt = अणु
	.attrs = w83627hf_attributes_opt,
पूर्ण;

अटल पूर्णांक w83627hf_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा w83627hf_sio_data *sio_data = dev_get_platdata(dev);
	काष्ठा w83627hf_data *data;
	काष्ठा resource *res;
	पूर्णांक err, i;

	अटल स्थिर अक्षर *names[] = अणु
		"w83627hf",
		"w83627thf",
		"w83697hf",
		"w83637hf",
		"w83687thf",
	पूर्ण;

	res = platक्रमm_get_resource(pdev, IORESOURCE_IO, 0);
	अगर (!devm_request_region(dev, res->start, WINB_REGION_SIZE, DRVNAME)) अणु
		dev_err(dev, "Failed to request region 0x%lx-0x%lx\n",
			(अचिन्हित दीर्घ)res->start,
			(अचिन्हित दीर्घ)(res->start + WINB_REGION_SIZE - 1));
		वापस -EBUSY;
	पूर्ण

	data = devm_kzalloc(dev, माप(काष्ठा w83627hf_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->addr = res->start;
	data->type = sio_data->type;
	data->name = names[sio_data->type];
	mutex_init(&data->lock);
	mutex_init(&data->update_lock);
	platक्रमm_set_drvdata(pdev, data);

	/* Initialize the chip */
	w83627hf_init_device(pdev);

	/* A few vars need to be filled upon startup */
	क्रम (i = 0; i <= 2; i++)
		data->fan_min[i] = w83627hf_पढ़ो_value(
					data, W83627HF_REG_FAN_MIN(i));
	w83627hf_update_fan_भाग(data);

	/* Register common device attributes */
	err = sysfs_create_group(&dev->kobj, &w83627hf_group);
	अगर (err)
		वापस err;

	/* Register chip-specअगरic device attributes */
	अगर (data->type == w83627hf || data->type == w83697hf)
		अगर ((err = device_create_file(dev,
				&sensor_dev_attr_in5_input.dev_attr))
		 || (err = device_create_file(dev,
				&sensor_dev_attr_in5_min.dev_attr))
		 || (err = device_create_file(dev,
				&sensor_dev_attr_in5_max.dev_attr))
		 || (err = device_create_file(dev,
				&sensor_dev_attr_in5_alarm.dev_attr))
		 || (err = device_create_file(dev,
				&sensor_dev_attr_in5_beep.dev_attr))
		 || (err = device_create_file(dev,
				&sensor_dev_attr_in6_input.dev_attr))
		 || (err = device_create_file(dev,
				&sensor_dev_attr_in6_min.dev_attr))
		 || (err = device_create_file(dev,
				&sensor_dev_attr_in6_max.dev_attr))
		 || (err = device_create_file(dev,
				&sensor_dev_attr_in6_alarm.dev_attr))
		 || (err = device_create_file(dev,
				&sensor_dev_attr_in6_beep.dev_attr))
		 || (err = device_create_file(dev,
				&sensor_dev_attr_pwm1_freq.dev_attr))
		 || (err = device_create_file(dev,
				&sensor_dev_attr_pwm2_freq.dev_attr)))
			जाओ error;

	अगर (data->type != w83697hf)
		अगर ((err = device_create_file(dev,
				&sensor_dev_attr_in1_input.dev_attr))
		 || (err = device_create_file(dev,
				&sensor_dev_attr_in1_min.dev_attr))
		 || (err = device_create_file(dev,
				&sensor_dev_attr_in1_max.dev_attr))
		 || (err = device_create_file(dev,
				&sensor_dev_attr_in1_alarm.dev_attr))
		 || (err = device_create_file(dev,
				&sensor_dev_attr_in1_beep.dev_attr))
		 || (err = device_create_file(dev,
				&sensor_dev_attr_fan3_input.dev_attr))
		 || (err = device_create_file(dev,
				&sensor_dev_attr_fan3_min.dev_attr))
		 || (err = device_create_file(dev,
				&sensor_dev_attr_fan3_भाग.dev_attr))
		 || (err = device_create_file(dev,
				&sensor_dev_attr_fan3_alarm.dev_attr))
		 || (err = device_create_file(dev,
				&sensor_dev_attr_fan3_beep.dev_attr))
		 || (err = device_create_file(dev,
				&sensor_dev_attr_temp3_input.dev_attr))
		 || (err = device_create_file(dev,
				&sensor_dev_attr_temp3_max.dev_attr))
		 || (err = device_create_file(dev,
				&sensor_dev_attr_temp3_max_hyst.dev_attr))
		 || (err = device_create_file(dev,
				&sensor_dev_attr_temp3_alarm.dev_attr))
		 || (err = device_create_file(dev,
				&sensor_dev_attr_temp3_beep.dev_attr))
		 || (err = device_create_file(dev,
				&sensor_dev_attr_temp3_type.dev_attr)))
			जाओ error;

	अगर (data->type != w83697hf && data->vid != 0xff) अणु
		/* Convert VID to voltage based on VRM */
		data->vrm = vid_which_vrm();

		अगर ((err = device_create_file(dev, &dev_attr_cpu0_vid))
		 || (err = device_create_file(dev, &dev_attr_vrm)))
			जाओ error;
	पूर्ण

	अगर (data->type == w83627thf || data->type == w83637hf
	    || data->type == w83687thf) अणु
		err = device_create_file(dev, &sensor_dev_attr_pwm3.dev_attr);
		अगर (err)
			जाओ error;
	पूर्ण

	अगर (data->type == w83637hf || data->type == w83687thf)
		अगर ((err = device_create_file(dev,
				&sensor_dev_attr_pwm1_freq.dev_attr))
		 || (err = device_create_file(dev,
				&sensor_dev_attr_pwm2_freq.dev_attr))
		 || (err = device_create_file(dev,
				&sensor_dev_attr_pwm3_freq.dev_attr)))
			जाओ error;

	अगर (data->type != w83627hf)
		अगर ((err = device_create_file(dev,
				&sensor_dev_attr_pwm1_enable.dev_attr))
		 || (err = device_create_file(dev,
				&sensor_dev_attr_pwm2_enable.dev_attr)))
			जाओ error;

	अगर (data->type == w83627thf || data->type == w83637hf
	    || data->type == w83687thf) अणु
		err = device_create_file(dev,
					 &sensor_dev_attr_pwm3_enable.dev_attr);
		अगर (err)
			जाओ error;
	पूर्ण

	data->hwmon_dev = hwmon_device_रेजिस्टर(dev);
	अगर (IS_ERR(data->hwmon_dev)) अणु
		err = PTR_ERR(data->hwmon_dev);
		जाओ error;
	पूर्ण

	वापस 0;

 error:
	sysfs_हटाओ_group(&dev->kobj, &w83627hf_group);
	sysfs_हटाओ_group(&dev->kobj, &w83627hf_group_opt);
	वापस err;
पूर्ण

अटल पूर्णांक w83627hf_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा w83627hf_data *data = platक्रमm_get_drvdata(pdev);

	hwmon_device_unरेजिस्टर(data->hwmon_dev);

	sysfs_हटाओ_group(&pdev->dev.kobj, &w83627hf_group);
	sysfs_हटाओ_group(&pdev->dev.kobj, &w83627hf_group_opt);

	वापस 0;
पूर्ण

/* Registers 0x50-0x5f are banked */
अटल अंतरभूत व्योम w83627hf_set_bank(काष्ठा w83627hf_data *data, u16 reg)
अणु
	अगर ((reg & 0x00f0) == 0x50) अणु
		outb_p(W83781D_REG_BANK, data->addr + W83781D_ADDR_REG_OFFSET);
		outb_p(reg >> 8, data->addr + W83781D_DATA_REG_OFFSET);
	पूर्ण
पूर्ण

/* Not strictly necessary, but play it safe क्रम now */
अटल अंतरभूत व्योम w83627hf_reset_bank(काष्ठा w83627hf_data *data, u16 reg)
अणु
	अगर (reg & 0xff00) अणु
		outb_p(W83781D_REG_BANK, data->addr + W83781D_ADDR_REG_OFFSET);
		outb_p(0, data->addr + W83781D_DATA_REG_OFFSET);
	पूर्ण
पूर्ण

अटल पूर्णांक w83627hf_पढ़ो_value(काष्ठा w83627hf_data *data, u16 reg)
अणु
	पूर्णांक res, word_sized;

	mutex_lock(&data->lock);
	word_sized = (((reg & 0xff00) == 0x100)
		   || ((reg & 0xff00) == 0x200))
		  && (((reg & 0x00ff) == 0x50)
		   || ((reg & 0x00ff) == 0x53)
		   || ((reg & 0x00ff) == 0x55));
	w83627hf_set_bank(data, reg);
	outb_p(reg & 0xff, data->addr + W83781D_ADDR_REG_OFFSET);
	res = inb_p(data->addr + W83781D_DATA_REG_OFFSET);
	अगर (word_sized) अणु
		outb_p((reg & 0xff) + 1,
		       data->addr + W83781D_ADDR_REG_OFFSET);
		res =
		    (res << 8) + inb_p(data->addr +
				       W83781D_DATA_REG_OFFSET);
	पूर्ण
	w83627hf_reset_bank(data, reg);
	mutex_unlock(&data->lock);
	वापस res;
पूर्ण

अटल पूर्णांक w83627thf_पढ़ो_gpio5(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा w83627hf_sio_data *sio_data = dev_get_platdata(&pdev->dev);
	पूर्णांक res = 0xff, sel;

	अगर (superio_enter(sio_data)) अणु
		/*
		 * Some other driver reserved the address space क्रम itself.
		 * We करोn't want to fail driver instantiation because of that,
		 * so display a warning and keep going.
		 */
		dev_warn(&pdev->dev,
			 "Can not read VID data: Failed to enable SuperIO access\n");
		वापस res;
	पूर्ण

	superio_select(sio_data, W83627HF_LD_GPIO5);

	res = 0xff;

	/* Make sure these GPIO pins are enabled */
	अगर (!(superio_inb(sio_data, W83627THF_GPIO5_EN) & (1<<3))) अणु
		dev_dbg(&pdev->dev, "GPIO5 disabled, no VID function\n");
		जाओ निकास;
	पूर्ण

	/*
	 * Make sure the pins are configured क्रम input
	 * There must be at least five (VRM 9), and possibly 6 (VRM 10)
	 */
	sel = superio_inb(sio_data, W83627THF_GPIO5_IOSR) & 0x3f;
	अगर ((sel & 0x1f) != 0x1f) अणु
		dev_dbg(&pdev->dev, "GPIO5 not configured for VID "
			"function\n");
		जाओ निकास;
	पूर्ण

	dev_info(&pdev->dev, "Reading VID from GPIO5\n");
	res = superio_inb(sio_data, W83627THF_GPIO5_DR) & sel;

निकास:
	superio_निकास(sio_data);
	वापस res;
पूर्ण

अटल पूर्णांक w83687thf_पढ़ो_vid(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा w83627hf_sio_data *sio_data = dev_get_platdata(&pdev->dev);
	पूर्णांक res = 0xff;

	अगर (superio_enter(sio_data)) अणु
		/*
		 * Some other driver reserved the address space क्रम itself.
		 * We करोn't want to fail driver instantiation because of that,
		 * so display a warning and keep going.
		 */
		dev_warn(&pdev->dev,
			 "Can not read VID data: Failed to enable SuperIO access\n");
		वापस res;
	पूर्ण

	superio_select(sio_data, W83627HF_LD_HWM);

	/* Make sure these GPIO pins are enabled */
	अगर (!(superio_inb(sio_data, W83687THF_VID_EN) & (1 << 2))) अणु
		dev_dbg(&pdev->dev, "VID disabled, no VID function\n");
		जाओ निकास;
	पूर्ण

	/* Make sure the pins are configured क्रम input */
	अगर (!(superio_inb(sio_data, W83687THF_VID_CFG) & (1 << 4))) अणु
		dev_dbg(&pdev->dev, "VID configured as output, "
			"no VID function\n");
		जाओ निकास;
	पूर्ण

	res = superio_inb(sio_data, W83687THF_VID_DATA) & 0x3f;

निकास:
	superio_निकास(sio_data);
	वापस res;
पूर्ण

अटल पूर्णांक w83627hf_ग_लिखो_value(काष्ठा w83627hf_data *data, u16 reg, u16 value)
अणु
	पूर्णांक word_sized;

	mutex_lock(&data->lock);
	word_sized = (((reg & 0xff00) == 0x100)
		   || ((reg & 0xff00) == 0x200))
		  && (((reg & 0x00ff) == 0x53)
		   || ((reg & 0x00ff) == 0x55));
	w83627hf_set_bank(data, reg);
	outb_p(reg & 0xff, data->addr + W83781D_ADDR_REG_OFFSET);
	अगर (word_sized) अणु
		outb_p(value >> 8,
		       data->addr + W83781D_DATA_REG_OFFSET);
		outb_p((reg & 0xff) + 1,
		       data->addr + W83781D_ADDR_REG_OFFSET);
	पूर्ण
	outb_p(value & 0xff,
	       data->addr + W83781D_DATA_REG_OFFSET);
	w83627hf_reset_bank(data, reg);
	mutex_unlock(&data->lock);
	वापस 0;
पूर्ण

अटल व्योम w83627hf_init_device(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा w83627hf_data *data = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;
	क्रमागत chips type = data->type;
	u8 पंचांगp;

	/* Minimize conflicts with other winbond i2c-only clients...  */
	/* disable i2c subclients... how to disable मुख्य i2c client?? */
	/* क्रमce i2c address to relatively uncommon address */
	अगर (type == w83627hf) अणु
		w83627hf_ग_लिखो_value(data, W83781D_REG_I2C_SUBADDR, 0x89);
		w83627hf_ग_लिखो_value(data, W83781D_REG_I2C_ADDR, क्रमce_i2c);
	पूर्ण

	/* Read VID only once */
	अगर (type == w83627hf || type == w83637hf) अणु
		पूर्णांक lo = w83627hf_पढ़ो_value(data, W83781D_REG_VID_FANDIV);
		पूर्णांक hi = w83627hf_पढ़ो_value(data, W83781D_REG_CHIPID);
		data->vid = (lo & 0x0f) | ((hi & 0x01) << 4);
	पूर्ण अन्यथा अगर (type == w83627thf) अणु
		data->vid = w83627thf_पढ़ो_gpio5(pdev);
	पूर्ण अन्यथा अगर (type == w83687thf) अणु
		data->vid = w83687thf_पढ़ो_vid(pdev);
	पूर्ण

	/* Read VRM & OVT Config only once */
	अगर (type == w83627thf || type == w83637hf || type == w83687thf) अणु
		data->vrm_ovt = 
			w83627hf_पढ़ो_value(data, W83627THF_REG_VRM_OVT_CFG);
	पूर्ण

	पंचांगp = w83627hf_पढ़ो_value(data, W83781D_REG_SCFG1);
	क्रम (i = 1; i <= 3; i++) अणु
		अगर (!(पंचांगp & BIT_SCFG1[i - 1])) अणु
			data->sens[i - 1] = 4;
		पूर्ण अन्यथा अणु
			अगर (w83627hf_पढ़ो_value
			    (data,
			     W83781D_REG_SCFG2) & BIT_SCFG2[i - 1])
				data->sens[i - 1] = 1;
			अन्यथा
				data->sens[i - 1] = 2;
		पूर्ण
		अगर ((type == w83697hf) && (i == 2))
			अवरोध;
	पूर्ण

	अगर(init) अणु
		/* Enable temp2 */
		पंचांगp = w83627hf_पढ़ो_value(data, W83627HF_REG_TEMP2_CONFIG);
		अगर (पंचांगp & 0x01) अणु
			dev_warn(&pdev->dev, "Enabling temp2, readings "
				 "might not make sense\n");
			w83627hf_ग_लिखो_value(data, W83627HF_REG_TEMP2_CONFIG,
				पंचांगp & 0xfe);
		पूर्ण

		/* Enable temp3 */
		अगर (type != w83697hf) अणु
			पंचांगp = w83627hf_पढ़ो_value(data,
				W83627HF_REG_TEMP3_CONFIG);
			अगर (पंचांगp & 0x01) अणु
				dev_warn(&pdev->dev, "Enabling temp3, "
					 "readings might not make sense\n");
				w83627hf_ग_लिखो_value(data,
					W83627HF_REG_TEMP3_CONFIG, पंचांगp & 0xfe);
			पूर्ण
		पूर्ण
	पूर्ण

	/* Start monitoring */
	w83627hf_ग_लिखो_value(data, W83781D_REG_CONFIG,
			    (w83627hf_पढ़ो_value(data,
						W83781D_REG_CONFIG) & 0xf7)
			    | 0x01);

	/* Enable VBAT monitoring अगर needed */
	पंचांगp = w83627hf_पढ़ो_value(data, W83781D_REG_VBAT);
	अगर (!(पंचांगp & 0x01))
		w83627hf_ग_लिखो_value(data, W83781D_REG_VBAT, पंचांगp | 0x01);
पूर्ण

अटल व्योम w83627hf_update_fan_भाग(काष्ठा w83627hf_data *data)
अणु
	पूर्णांक reg;

	reg = w83627hf_पढ़ो_value(data, W83781D_REG_VID_FANDIV);
	data->fan_भाग[0] = (reg >> 4) & 0x03;
	data->fan_भाग[1] = (reg >> 6) & 0x03;
	अगर (data->type != w83697hf) अणु
		data->fan_भाग[2] = (w83627hf_पढ़ो_value(data,
				       W83781D_REG_PIN) >> 6) & 0x03;
	पूर्ण
	reg = w83627hf_पढ़ो_value(data, W83781D_REG_VBAT);
	data->fan_भाग[0] |= (reg >> 3) & 0x04;
	data->fan_भाग[1] |= (reg >> 4) & 0x04;
	अगर (data->type != w83697hf)
		data->fan_भाग[2] |= (reg >> 5) & 0x04;
पूर्ण

अटल काष्ठा w83627hf_data *w83627hf_update_device(काष्ठा device *dev)
अणु
	काष्ठा w83627hf_data *data = dev_get_drvdata(dev);
	पूर्णांक i, num_temps = (data->type == w83697hf) ? 2 : 3;
	पूर्णांक num_pwms = (data->type == w83697hf) ? 2 : 3;

	mutex_lock(&data->update_lock);

	अगर (समय_after(jअगरfies, data->last_updated + HZ + HZ / 2)
	    || !data->valid) अणु
		क्रम (i = 0; i <= 8; i++) अणु
			/* skip missing sensors */
			अगर (((data->type == w83697hf) && (i == 1)) ||
			    ((data->type != w83627hf && data->type != w83697hf)
			    && (i == 5 || i == 6)))
				जारी;
			data->in[i] =
			    w83627hf_पढ़ो_value(data, W83781D_REG_IN(i));
			data->in_min[i] =
			    w83627hf_पढ़ो_value(data,
					       W83781D_REG_IN_MIN(i));
			data->in_max[i] =
			    w83627hf_पढ़ो_value(data,
					       W83781D_REG_IN_MAX(i));
		पूर्ण
		क्रम (i = 0; i <= 2; i++) अणु
			data->fan[i] =
			    w83627hf_पढ़ो_value(data, W83627HF_REG_FAN(i));
			data->fan_min[i] =
			    w83627hf_पढ़ो_value(data,
					       W83627HF_REG_FAN_MIN(i));
		पूर्ण
		क्रम (i = 0; i <= 2; i++) अणु
			u8 पंचांगp = w83627hf_पढ़ो_value(data,
				W836X7HF_REG_PWM(data->type, i));
 			/* bits 0-3 are reserved  in 627THF */
 			अगर (data->type == w83627thf)
				पंचांगp &= 0xf0;
			data->pwm[i] = पंचांगp;
			अगर (i == 1 &&
			    (data->type == w83627hf || data->type == w83697hf))
				अवरोध;
		पूर्ण
		अगर (data->type == w83627hf) अणु
				u8 पंचांगp = w83627hf_पढ़ो_value(data,
						W83627HF_REG_PWM_FREQ);
				data->pwm_freq[0] = पंचांगp & 0x07;
				data->pwm_freq[1] = (पंचांगp >> 4) & 0x07;
		पूर्ण अन्यथा अगर (data->type != w83627thf) अणु
			क्रम (i = 1; i <= 3; i++) अणु
				data->pwm_freq[i - 1] =
					w83627hf_पढ़ो_value(data,
						W83637HF_REG_PWM_FREQ[i - 1]);
				अगर (i == 2 && (data->type == w83697hf))
					अवरोध;
			पूर्ण
		पूर्ण
		अगर (data->type != w83627hf) अणु
			क्रम (i = 0; i < num_pwms; i++) अणु
				u8 पंचांगp = w83627hf_पढ़ो_value(data,
					W83627THF_REG_PWM_ENABLE[i]);
				data->pwm_enable[i] =
					((पंचांगp >> W83627THF_PWM_ENABLE_SHIFT[i])
					& 0x03) + 1;
			पूर्ण
		पूर्ण
		क्रम (i = 0; i < num_temps; i++) अणु
			data->temp[i] = w83627hf_पढ़ो_value(
						data, w83627hf_reg_temp[i]);
			data->temp_max[i] = w83627hf_पढ़ो_value(
						data, w83627hf_reg_temp_over[i]);
			data->temp_max_hyst[i] = w83627hf_पढ़ो_value(
						data, w83627hf_reg_temp_hyst[i]);
		पूर्ण

		w83627hf_update_fan_भाग(data);

		data->alarms =
		    w83627hf_पढ़ो_value(data, W83781D_REG_ALARM1) |
		    (w83627hf_पढ़ो_value(data, W83781D_REG_ALARM2) << 8) |
		    (w83627hf_पढ़ो_value(data, W83781D_REG_ALARM3) << 16);
		i = w83627hf_पढ़ो_value(data, W83781D_REG_BEEP_INTS2);
		data->beep_mask = (i << 8) |
		    w83627hf_पढ़ो_value(data, W83781D_REG_BEEP_INTS1) |
		    w83627hf_पढ़ो_value(data, W83781D_REG_BEEP_INTS3) << 16;
		data->last_updated = jअगरfies;
		data->valid = 1;
	पूर्ण

	mutex_unlock(&data->update_lock);

	वापस data;
पूर्ण

अटल पूर्णांक __init w83627hf_device_add(अचिन्हित लघु address,
				      स्थिर काष्ठा w83627hf_sio_data *sio_data)
अणु
	काष्ठा resource res = अणु
		.start	= address + WINB_REGION_OFFSET,
		.end	= address + WINB_REGION_OFFSET + WINB_REGION_SIZE - 1,
		.name	= DRVNAME,
		.flags	= IORESOURCE_IO,
	पूर्ण;
	पूर्णांक err;

	err = acpi_check_resource_conflict(&res);
	अगर (err)
		जाओ निकास;

	pdev = platक्रमm_device_alloc(DRVNAME, address);
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

	err = platक्रमm_device_add_data(pdev, sio_data,
				       माप(काष्ठा w83627hf_sio_data));
	अगर (err) अणु
		pr_err("Platform data allocation failed\n");
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

अटल पूर्णांक __init sensors_w83627hf_init(व्योम)
अणु
	पूर्णांक err;
	अचिन्हित लघु address;
	काष्ठा w83627hf_sio_data sio_data;

	अगर (w83627hf_find(0x2e, &address, &sio_data)
	 && w83627hf_find(0x4e, &address, &sio_data))
		वापस -ENODEV;

	err = platक्रमm_driver_रेजिस्टर(&w83627hf_driver);
	अगर (err)
		जाओ निकास;

	/* Sets global pdev as a side effect */
	err = w83627hf_device_add(address, &sio_data);
	अगर (err)
		जाओ निकास_driver;

	वापस 0;

निकास_driver:
	platक्रमm_driver_unरेजिस्टर(&w83627hf_driver);
निकास:
	वापस err;
पूर्ण

अटल व्योम __निकास sensors_w83627hf_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(pdev);
	platक्रमm_driver_unरेजिस्टर(&w83627hf_driver);
पूर्ण

MODULE_AUTHOR("Frodo Looijaard <frodol@dds.nl>, "
	      "Philip Edelbrock <phil@netroedge.com>, "
	      "and Mark Studebaker <mdsxyz123@yahoo.com>");
MODULE_DESCRIPTION("W83627HF driver");
MODULE_LICENSE("GPL");

module_init(sensors_w83627hf_init);
module_निकास(sensors_w83627hf_निकास);
