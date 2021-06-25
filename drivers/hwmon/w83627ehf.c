<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  w83627ehf - Driver क्रम the hardware monitoring functionality of
 *		the Winbond W83627EHF Super-I/O chip
 *  Copyright (C) 2005-2012  Jean Delvare <jdelvare@suse.de>
 *  Copyright (C) 2006  Yuan Mu (Winbond),
 *			Ruकरोlf Marek <r.marek@assembler.cz>
 *			David Hubbard <david.c.hubbard@gmail.com>
 *			Daniel J Blueman <daniel.blueman@gmail.com>
 *  Copyright (C) 2010  Sheng-Yuan Huang (Nuvoton) (PS00)
 *
 *  Shamelessly ripped from the w83627hf driver
 *  Copyright (C) 2003  Mark Studebaker
 *
 *  Thanks to Leon Moonen, Steve Clअगरfe and Grant Coady क्रम their help
 *  in testing and debugging this driver.
 *
 *  This driver also supports the W83627EHG, which is the lead-मुक्त
 *  version of the W83627EHF.
 *
 *  Supports the following chips:
 *
 *  Chip        #vin    #fan    #pwm    #temp  chip IDs       man ID
 *  w83627ehf   10      5       4       3      0x8850 0x88    0x5ca3
 *					       0x8860 0xa1
 *  w83627dhg    9      5       4       3      0xa020 0xc1    0x5ca3
 *  w83627dhg-p  9      5       4       3      0xb070 0xc1    0x5ca3
 *  w83627uhg    8      2       2       3      0xa230 0xc1    0x5ca3
 *  w83667hg     9      5       3       3      0xa510 0xc1    0x5ca3
 *  w83667hg-b   9      5       3       4      0xb350 0xc1    0x5ca3
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
#समावेश <linux/acpi.h>
#समावेश <linux/पन.स>
#समावेश "lm75.h"

क्रमागत kinds अणु
	w83627ehf, w83627dhg, w83627dhg_p, w83627uhg,
	w83667hg, w83667hg_b,
पूर्ण;

/* used to set data->name = w83627ehf_device_names[data->sio_kind] */
अटल स्थिर अक्षर * स्थिर w83627ehf_device_names[] = अणु
	"w83627ehf",
	"w83627dhg",
	"w83627dhg",
	"w83627uhg",
	"w83667hg",
	"w83667hg",
पूर्ण;

अटल अचिन्हित लघु क्रमce_id;
module_param(क्रमce_id, uलघु, 0);
MODULE_PARM_DESC(क्रमce_id, "Override the detected device ID");

#घोषणा DRVNAME "w83627ehf"

/*
 * Super-I/O स्थिरants and functions
 */

#घोषणा W83627EHF_LD_HWM	0x0b
#घोषणा W83667HG_LD_VID		0x0d

#घोषणा SIO_REG_LDSEL		0x07	/* Logical device select */
#घोषणा SIO_REG_DEVID		0x20	/* Device ID (2 bytes) */
#घोषणा SIO_REG_EN_VRM10	0x2C	/* GPIO3, GPIO4 selection */
#घोषणा SIO_REG_ENABLE		0x30	/* Logical device enable */
#घोषणा SIO_REG_ADDR		0x60	/* Logical device address (2 bytes) */
#घोषणा SIO_REG_VID_CTRL	0xF0	/* VID control */
#घोषणा SIO_REG_VID_DATA	0xF1	/* VID data */

#घोषणा SIO_W83627EHF_ID	0x8850
#घोषणा SIO_W83627EHG_ID	0x8860
#घोषणा SIO_W83627DHG_ID	0xa020
#घोषणा SIO_W83627DHG_P_ID	0xb070
#घोषणा SIO_W83627UHG_ID	0xa230
#घोषणा SIO_W83667HG_ID		0xa510
#घोषणा SIO_W83667HG_B_ID	0xb350
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
#घोषणा IOREGION_OFFSET		5
#घोषणा IOREGION_LENGTH		2
#घोषणा ADDR_REG_OFFSET		0
#घोषणा DATA_REG_OFFSET		1

#घोषणा W83627EHF_REG_BANK		0x4E
#घोषणा W83627EHF_REG_CONFIG		0x40

/*
 * Not currently used:
 * REG_MAN_ID has the value 0x5ca3 क्रम all supported chips.
 * REG_CHIP_ID == 0x88/0xa1/0xc1 depending on chip model.
 * REG_MAN_ID is at port 0x4f
 * REG_CHIP_ID is at port 0x58
 */

अटल स्थिर u16 W83627EHF_REG_FAN[] = अणु 0x28, 0x29, 0x2a, 0x3f, 0x553 पूर्ण;
अटल स्थिर u16 W83627EHF_REG_FAN_MIN[] = अणु 0x3b, 0x3c, 0x3d, 0x3e, 0x55c पूर्ण;

/* The W83627EHF रेजिस्टरs क्रम nr=7,8,9 are in bank 5 */
#घोषणा W83627EHF_REG_IN_MAX(nr)	((nr < 7) ? (0x2b + (nr) * 2) : \
					 (0x554 + (((nr) - 7) * 2)))
#घोषणा W83627EHF_REG_IN_MIN(nr)	((nr < 7) ? (0x2c + (nr) * 2) : \
					 (0x555 + (((nr) - 7) * 2)))
#घोषणा W83627EHF_REG_IN(nr)		((nr < 7) ? (0x20 + (nr)) : \
					 (0x550 + (nr) - 7))

अटल स्थिर u16 W83627EHF_REG_TEMP[] = अणु 0x27, 0x150, 0x250, 0x7e पूर्ण;
अटल स्थिर u16 W83627EHF_REG_TEMP_HYST[] = अणु 0x3a, 0x153, 0x253, 0 पूर्ण;
अटल स्थिर u16 W83627EHF_REG_TEMP_OVER[] = अणु 0x39, 0x155, 0x255, 0 पूर्ण;
अटल स्थिर u16 W83627EHF_REG_TEMP_CONFIG[] = अणु 0, 0x152, 0x252, 0 पूर्ण;

/* Fan घड़ी भागiders are spपढ़ो over the following five रेजिस्टरs */
#घोषणा W83627EHF_REG_FANDIV1		0x47
#घोषणा W83627EHF_REG_FANDIV2		0x4B
#घोषणा W83627EHF_REG_VBAT		0x5D
#घोषणा W83627EHF_REG_DIODE		0x59
#घोषणा W83627EHF_REG_SMI_OVT		0x4C

#घोषणा W83627EHF_REG_ALARM1		0x459
#घोषणा W83627EHF_REG_ALARM2		0x45A
#घोषणा W83627EHF_REG_ALARM3		0x45B

#घोषणा W83627EHF_REG_CASEOPEN_DET	0x42 /* SMI STATUS #2 */
#घोषणा W83627EHF_REG_CASEOPEN_CLR	0x46 /* SMI MASK #3 */

/* SmartFan रेजिस्टरs */
#घोषणा W83627EHF_REG_FAN_STEPUP_TIME 0x0f
#घोषणा W83627EHF_REG_FAN_STEPDOWN_TIME 0x0e

/* DC or PWM output fan configuration */
अटल स्थिर u8 W83627EHF_REG_PWM_ENABLE[] = अणु
	0x04,			/* SYS FAN0 output mode and PWM mode */
	0x04,			/* CPU FAN0 output mode and PWM mode */
	0x12,			/* AUX FAN mode */
	0x62,			/* CPU FAN1 mode */
पूर्ण;

अटल स्थिर u8 W83627EHF_PWM_MODE_SHIFT[] = अणु 0, 1, 0, 6 पूर्ण;
अटल स्थिर u8 W83627EHF_PWM_ENABLE_SHIFT[] = अणु 2, 4, 1, 4 पूर्ण;

/* FAN Duty Cycle, be used to control */
अटल स्थिर u16 W83627EHF_REG_PWM[] = अणु 0x01, 0x03, 0x11, 0x61 पूर्ण;
अटल स्थिर u16 W83627EHF_REG_TARGET[] = अणु 0x05, 0x06, 0x13, 0x63 पूर्ण;
अटल स्थिर u8 W83627EHF_REG_TOLERANCE[] = अणु 0x07, 0x07, 0x14, 0x62 पूर्ण;

/* Advanced Fan control, some values are common क्रम all fans */
अटल स्थिर u16 W83627EHF_REG_FAN_START_OUTPUT[] = अणु 0x0a, 0x0b, 0x16, 0x65 पूर्ण;
अटल स्थिर u16 W83627EHF_REG_FAN_STOP_OUTPUT[] = अणु 0x08, 0x09, 0x15, 0x64 पूर्ण;
अटल स्थिर u16 W83627EHF_REG_FAN_STOP_TIME[] = अणु 0x0c, 0x0d, 0x17, 0x66 पूर्ण;

अटल स्थिर u16 W83627EHF_REG_FAN_MAX_OUTPUT_COMMON[]
						= अणु 0xff, 0x67, 0xff, 0x69 पूर्ण;
अटल स्थिर u16 W83627EHF_REG_FAN_STEP_OUTPUT_COMMON[]
						= अणु 0xff, 0x68, 0xff, 0x6a पूर्ण;

अटल स्थिर u16 W83627EHF_REG_FAN_MAX_OUTPUT_W83667_B[] = अणु 0x67, 0x69, 0x6b पूर्ण;
अटल स्थिर u16 W83627EHF_REG_FAN_STEP_OUTPUT_W83667_B[]
						= अणु 0x68, 0x6a, 0x6c पूर्ण;

अटल स्थिर u16 W83627EHF_REG_TEMP_OFFSET[] = अणु 0x454, 0x455, 0x456 पूर्ण;

अटल स्थिर अक्षर *स्थिर w83667hg_b_temp_label[] = अणु
	"SYSTIN",
	"CPUTIN",
	"AUXTIN",
	"AMDTSI",
	"PECI Agent 1",
	"PECI Agent 2",
	"PECI Agent 3",
	"PECI Agent 4"
पूर्ण;

#घोषणा NUM_REG_TEMP	ARRAY_SIZE(W83627EHF_REG_TEMP)

अटल पूर्णांक is_word_sized(u16 reg)
अणु
	वापस ((((reg & 0xff00) == 0x100
	      || (reg & 0xff00) == 0x200)
	     && ((reg & 0x00ff) == 0x50
	      || (reg & 0x00ff) == 0x53
	      || (reg & 0x00ff) == 0x55))
	     || (reg & 0xfff0) == 0x630
	     || reg == 0x640 || reg == 0x642
	     || ((reg & 0xfff0) == 0x650
		 && (reg & 0x000f) >= 0x06)
	     || reg == 0x73 || reg == 0x75 || reg == 0x77
		);
पूर्ण

/*
 * Conversions
 */

/* 1 is PWM mode, output in ms */
अटल अंतरभूत अचिन्हित पूर्णांक step_समय_from_reg(u8 reg, u8 mode)
अणु
	वापस mode ? 100 * reg : 400 * reg;
पूर्ण

अटल अंतरभूत u8 step_समय_प्रकारo_reg(अचिन्हित पूर्णांक msec, u8 mode)
अणु
	वापस clamp_val((mode ? (msec + 50) / 100 : (msec + 200) / 400),
			 1, 255);
पूर्ण

अटल अचिन्हित पूर्णांक fan_from_reg8(u16 reg, अचिन्हित पूर्णांक भागreg)
अणु
	अगर (reg == 0 || reg == 255)
		वापस 0;
	वापस 1350000U / (reg << भागreg);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक
भाग_from_reg(u8 reg)
अणु
	वापस 1 << reg;
पूर्ण

/*
 * Some of the voltage inमाला_दो have पूर्णांकernal scaling, the tables below
 * contain 8 (the ADC LSB in mV) * scaling factor * 100
 */
अटल स्थिर u16 scale_in_common[10] = अणु
	800, 800, 1600, 1600, 800, 800, 800, 1600, 1600, 800
पूर्ण;
अटल स्थिर u16 scale_in_w83627uhg[9] = अणु
	800, 800, 3328, 3424, 800, 800, 0, 3328, 3400
पूर्ण;

अटल अंतरभूत दीर्घ in_from_reg(u8 reg, u8 nr, स्थिर u16 *scale_in)
अणु
	वापस DIV_ROUND_CLOSEST(reg * scale_in[nr], 100);
पूर्ण

अटल अंतरभूत u8 in_to_reg(u32 val, u8 nr, स्थिर u16 *scale_in)
अणु
	वापस clamp_val(DIV_ROUND_CLOSEST(val * 100, scale_in[nr]), 0, 255);
पूर्ण

/*
 * Data काष्ठाures and manipulation thereof
 */

काष्ठा w83627ehf_data अणु
	पूर्णांक addr;	/* IO base of hw monitor block */
	स्थिर अक्षर *name;

	काष्ठा mutex lock;

	u16 reg_temp[NUM_REG_TEMP];
	u16 reg_temp_over[NUM_REG_TEMP];
	u16 reg_temp_hyst[NUM_REG_TEMP];
	u16 reg_temp_config[NUM_REG_TEMP];
	u8 temp_src[NUM_REG_TEMP];
	स्थिर अक्षर * स्थिर *temp_label;

	स्थिर u16 *REG_FAN_MAX_OUTPUT;
	स्थिर u16 *REG_FAN_STEP_OUTPUT;
	स्थिर u16 *scale_in;

	काष्ठा mutex update_lock;
	अक्षर valid;		/* !=0 अगर following fields are valid */
	अचिन्हित दीर्घ last_updated;	/* In jअगरfies */

	/* Register values */
	u8 bank;		/* current रेजिस्टर bank */
	u8 in_num;		/* number of in inमाला_दो we have */
	u8 in[10];		/* Register value */
	u8 in_max[10];		/* Register value */
	u8 in_min[10];		/* Register value */
	अचिन्हित पूर्णांक rpm[5];
	u16 fan_min[5];
	u8 fan_भाग[5];
	u8 has_fan;		/* some fan inमाला_दो can be disabled */
	u8 has_fan_min;		/* some fans करोn't have min रेजिस्टर */
	u8 temp_type[3];
	s8 temp_offset[3];
	s16 temp[9];
	s16 temp_max[9];
	s16 temp_max_hyst[9];
	u32 alarms;
	u8 हालखोलो;

	u8 pwm_mode[4]; /* 0->DC variable voltage, 1->PWM variable duty cycle */
	u8 pwm_enable[4]; /* 1->manual
			   * 2->thermal cruise mode (also called SmartFan I)
			   * 3->fan speed cruise mode
			   * 4->variable thermal cruise (also called
			   * SmartFan III)
			   * 5->enhanced variable thermal cruise (also called
			   * SmartFan IV)
			   */
	u8 pwm_enable_orig[4];	/* original value of pwm_enable */
	u8 pwm_num;		/* number of pwm */
	u8 pwm[4];
	u8 target_temp[4];
	u8 tolerance[4];

	u8 fan_start_output[4]; /* minimum fan speed when spinning up */
	u8 fan_stop_output[4]; /* minimum fan speed when spinning करोwn */
	u8 fan_stop_समय[4]; /* समय at minimum beक्रमe disabling fan */
	u8 fan_max_output[4]; /* maximum fan speed */
	u8 fan_step_output[4]; /* rate of change output value */

	u8 vid;
	u8 vrm;

	u16 have_temp;
	u16 have_temp_offset;
	u8 in6_skip:1;
	u8 temp3_val_only:1;
	u8 have_vid:1;

#अगर_घोषित CONFIG_PM
	/* Remember extra रेजिस्टर values over suspend/resume */
	u8 vbat;
	u8 fanभाग1;
	u8 fanभाग2;
#पूर्ण_अगर
पूर्ण;

काष्ठा w83627ehf_sio_data अणु
	पूर्णांक sioreg;
	क्रमागत kinds kind;
पूर्ण;

/*
 * On older chips, only रेजिस्टरs 0x50-0x5f are banked.
 * On more recent chips, all रेजिस्टरs are banked.
 * Assume that is the हाल and set the bank number क्रम each access.
 * Cache the bank number so it only needs to be set अगर it changes.
 */
अटल अंतरभूत व्योम w83627ehf_set_bank(काष्ठा w83627ehf_data *data, u16 reg)
अणु
	u8 bank = reg >> 8;
	अगर (data->bank != bank) अणु
		outb_p(W83627EHF_REG_BANK, data->addr + ADDR_REG_OFFSET);
		outb_p(bank, data->addr + DATA_REG_OFFSET);
		data->bank = bank;
	पूर्ण
पूर्ण

अटल u16 w83627ehf_पढ़ो_value(काष्ठा w83627ehf_data *data, u16 reg)
अणु
	पूर्णांक res, word_sized = is_word_sized(reg);

	mutex_lock(&data->lock);

	w83627ehf_set_bank(data, reg);
	outb_p(reg & 0xff, data->addr + ADDR_REG_OFFSET);
	res = inb_p(data->addr + DATA_REG_OFFSET);
	अगर (word_sized) अणु
		outb_p((reg & 0xff) + 1,
		       data->addr + ADDR_REG_OFFSET);
		res = (res << 8) + inb_p(data->addr + DATA_REG_OFFSET);
	पूर्ण

	mutex_unlock(&data->lock);
	वापस res;
पूर्ण

अटल पूर्णांक w83627ehf_ग_लिखो_value(काष्ठा w83627ehf_data *data, u16 reg,
				 u16 value)
अणु
	पूर्णांक word_sized = is_word_sized(reg);

	mutex_lock(&data->lock);

	w83627ehf_set_bank(data, reg);
	outb_p(reg & 0xff, data->addr + ADDR_REG_OFFSET);
	अगर (word_sized) अणु
		outb_p(value >> 8, data->addr + DATA_REG_OFFSET);
		outb_p((reg & 0xff) + 1,
		       data->addr + ADDR_REG_OFFSET);
	पूर्ण
	outb_p(value & 0xff, data->addr + DATA_REG_OFFSET);

	mutex_unlock(&data->lock);
	वापस 0;
पूर्ण

/* We left-align 8-bit temperature values to make the code simpler */
अटल u16 w83627ehf_पढ़ो_temp(काष्ठा w83627ehf_data *data, u16 reg)
अणु
	u16 res;

	res = w83627ehf_पढ़ो_value(data, reg);
	अगर (!is_word_sized(reg))
		res <<= 8;

	वापस res;
पूर्ण

अटल पूर्णांक w83627ehf_ग_लिखो_temp(काष्ठा w83627ehf_data *data, u16 reg,
				       u16 value)
अणु
	अगर (!is_word_sized(reg))
		value >>= 8;
	वापस w83627ehf_ग_लिखो_value(data, reg, value);
पूर्ण

/* This function assumes that the caller holds data->update_lock */
अटल व्योम w83627ehf_ग_लिखो_fan_भाग(काष्ठा w83627ehf_data *data, पूर्णांक nr)
अणु
	u8 reg;

	चयन (nr) अणु
	हाल 0:
		reg = (w83627ehf_पढ़ो_value(data, W83627EHF_REG_FANDIV1) & 0xcf)
		    | ((data->fan_भाग[0] & 0x03) << 4);
		/* fan5 input control bit is ग_लिखो only, compute the value */
		reg |= (data->has_fan & (1 << 4)) ? 1 : 0;
		w83627ehf_ग_लिखो_value(data, W83627EHF_REG_FANDIV1, reg);
		reg = (w83627ehf_पढ़ो_value(data, W83627EHF_REG_VBAT) & 0xdf)
		    | ((data->fan_भाग[0] & 0x04) << 3);
		w83627ehf_ग_लिखो_value(data, W83627EHF_REG_VBAT, reg);
		अवरोध;
	हाल 1:
		reg = (w83627ehf_पढ़ो_value(data, W83627EHF_REG_FANDIV1) & 0x3f)
		    | ((data->fan_भाग[1] & 0x03) << 6);
		/* fan5 input control bit is ग_लिखो only, compute the value */
		reg |= (data->has_fan & (1 << 4)) ? 1 : 0;
		w83627ehf_ग_लिखो_value(data, W83627EHF_REG_FANDIV1, reg);
		reg = (w83627ehf_पढ़ो_value(data, W83627EHF_REG_VBAT) & 0xbf)
		    | ((data->fan_भाग[1] & 0x04) << 4);
		w83627ehf_ग_लिखो_value(data, W83627EHF_REG_VBAT, reg);
		अवरोध;
	हाल 2:
		reg = (w83627ehf_पढ़ो_value(data, W83627EHF_REG_FANDIV2) & 0x3f)
		    | ((data->fan_भाग[2] & 0x03) << 6);
		w83627ehf_ग_लिखो_value(data, W83627EHF_REG_FANDIV2, reg);
		reg = (w83627ehf_पढ़ो_value(data, W83627EHF_REG_VBAT) & 0x7f)
		    | ((data->fan_भाग[2] & 0x04) << 5);
		w83627ehf_ग_लिखो_value(data, W83627EHF_REG_VBAT, reg);
		अवरोध;
	हाल 3:
		reg = (w83627ehf_पढ़ो_value(data, W83627EHF_REG_DIODE) & 0xfc)
		    | (data->fan_भाग[3] & 0x03);
		w83627ehf_ग_लिखो_value(data, W83627EHF_REG_DIODE, reg);
		reg = (w83627ehf_पढ़ो_value(data, W83627EHF_REG_SMI_OVT) & 0x7f)
		    | ((data->fan_भाग[3] & 0x04) << 5);
		w83627ehf_ग_लिखो_value(data, W83627EHF_REG_SMI_OVT, reg);
		अवरोध;
	हाल 4:
		reg = (w83627ehf_पढ़ो_value(data, W83627EHF_REG_DIODE) & 0x73)
		    | ((data->fan_भाग[4] & 0x03) << 2)
		    | ((data->fan_भाग[4] & 0x04) << 5);
		w83627ehf_ग_लिखो_value(data, W83627EHF_REG_DIODE, reg);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम w83627ehf_update_fan_भाग(काष्ठा w83627ehf_data *data)
अणु
	पूर्णांक i;

	i = w83627ehf_पढ़ो_value(data, W83627EHF_REG_FANDIV1);
	data->fan_भाग[0] = (i >> 4) & 0x03;
	data->fan_भाग[1] = (i >> 6) & 0x03;
	i = w83627ehf_पढ़ो_value(data, W83627EHF_REG_FANDIV2);
	data->fan_भाग[2] = (i >> 6) & 0x03;
	i = w83627ehf_पढ़ो_value(data, W83627EHF_REG_VBAT);
	data->fan_भाग[0] |= (i >> 3) & 0x04;
	data->fan_भाग[1] |= (i >> 4) & 0x04;
	data->fan_भाग[2] |= (i >> 5) & 0x04;
	अगर (data->has_fan & ((1 << 3) | (1 << 4))) अणु
		i = w83627ehf_पढ़ो_value(data, W83627EHF_REG_DIODE);
		data->fan_भाग[3] = i & 0x03;
		data->fan_भाग[4] = ((i >> 2) & 0x03)
				 | ((i >> 5) & 0x04);
	पूर्ण
	अगर (data->has_fan & (1 << 3)) अणु
		i = w83627ehf_पढ़ो_value(data, W83627EHF_REG_SMI_OVT);
		data->fan_भाग[3] |= (i >> 5) & 0x04;
	पूर्ण
पूर्ण

अटल व्योम w83627ehf_update_pwm(काष्ठा w83627ehf_data *data)
अणु
	पूर्णांक i;
	पूर्णांक pwmcfg = 0, tolerance = 0; /* shut up the compiler */

	क्रम (i = 0; i < data->pwm_num; i++) अणु
		अगर (!(data->has_fan & (1 << i)))
			जारी;

		/* pwmcfg, tolerance mapped क्रम i=0, i=1 to same reg */
		अगर (i != 1) अणु
			pwmcfg = w83627ehf_पढ़ो_value(data,
					W83627EHF_REG_PWM_ENABLE[i]);
			tolerance = w83627ehf_पढ़ो_value(data,
					W83627EHF_REG_TOLERANCE[i]);
		पूर्ण
		data->pwm_mode[i] =
			((pwmcfg >> W83627EHF_PWM_MODE_SHIFT[i]) & 1) ? 0 : 1;
		data->pwm_enable[i] = ((pwmcfg >> W83627EHF_PWM_ENABLE_SHIFT[i])
				       & 3) + 1;
		data->pwm[i] = w83627ehf_पढ़ो_value(data, W83627EHF_REG_PWM[i]);

		data->tolerance[i] = (tolerance >> (i == 1 ? 4 : 0)) & 0x0f;
	पूर्ण
पूर्ण

अटल काष्ठा w83627ehf_data *w83627ehf_update_device(काष्ठा device *dev)
अणु
	काष्ठा w83627ehf_data *data = dev_get_drvdata(dev);
	पूर्णांक i;

	mutex_lock(&data->update_lock);

	अगर (समय_after(jअगरfies, data->last_updated + HZ + HZ/2)
	 || !data->valid) अणु
		/* Fan घड़ी भागiders */
		w83627ehf_update_fan_भाग(data);

		/* Measured voltages and limits */
		क्रम (i = 0; i < data->in_num; i++) अणु
			अगर ((i == 6) && data->in6_skip)
				जारी;

			data->in[i] = w83627ehf_पढ़ो_value(data,
				      W83627EHF_REG_IN(i));
			data->in_min[i] = w83627ehf_पढ़ो_value(data,
					  W83627EHF_REG_IN_MIN(i));
			data->in_max[i] = w83627ehf_पढ़ो_value(data,
					  W83627EHF_REG_IN_MAX(i));
		पूर्ण

		/* Measured fan speeds and limits */
		क्रम (i = 0; i < 5; i++) अणु
			u16 reg;

			अगर (!(data->has_fan & (1 << i)))
				जारी;

			reg = w83627ehf_पढ़ो_value(data, W83627EHF_REG_FAN[i]);
			data->rpm[i] = fan_from_reg8(reg, data->fan_भाग[i]);

			अगर (data->has_fan_min & (1 << i))
				data->fan_min[i] = w83627ehf_पढ़ो_value(data,
					   W83627EHF_REG_FAN_MIN[i]);

			/*
			 * If we failed to measure the fan speed and घड़ी
			 * भागider can be increased, let's try that क्रम next
			 * समय
			 */
			अगर (reg >= 0xff && data->fan_भाग[i] < 0x07) अणु
				dev_dbg(dev,
					"Increasing fan%d clock divider from %u to %u\n",
					i + 1, भाग_from_reg(data->fan_भाग[i]),
					भाग_from_reg(data->fan_भाग[i] + 1));
				data->fan_भाग[i]++;
				w83627ehf_ग_लिखो_fan_भाग(data, i);
				/* Preserve min limit अगर possible */
				अगर ((data->has_fan_min & (1 << i))
				 && data->fan_min[i] >= 2
				 && data->fan_min[i] != 255)
					w83627ehf_ग_लिखो_value(data,
						W83627EHF_REG_FAN_MIN[i],
						(data->fan_min[i] /= 2));
			पूर्ण
		पूर्ण

		w83627ehf_update_pwm(data);

		क्रम (i = 0; i < data->pwm_num; i++) अणु
			अगर (!(data->has_fan & (1 << i)))
				जारी;

			data->fan_start_output[i] =
			  w83627ehf_पढ़ो_value(data,
					     W83627EHF_REG_FAN_START_OUTPUT[i]);
			data->fan_stop_output[i] =
			  w83627ehf_पढ़ो_value(data,
					     W83627EHF_REG_FAN_STOP_OUTPUT[i]);
			data->fan_stop_समय[i] =
			  w83627ehf_पढ़ो_value(data,
					       W83627EHF_REG_FAN_STOP_TIME[i]);

			अगर (data->REG_FAN_MAX_OUTPUT &&
			    data->REG_FAN_MAX_OUTPUT[i] != 0xff)
				data->fan_max_output[i] =
				  w83627ehf_पढ़ो_value(data,
						data->REG_FAN_MAX_OUTPUT[i]);

			अगर (data->REG_FAN_STEP_OUTPUT &&
			    data->REG_FAN_STEP_OUTPUT[i] != 0xff)
				data->fan_step_output[i] =
				  w83627ehf_पढ़ो_value(data,
						data->REG_FAN_STEP_OUTPUT[i]);

			data->target_temp[i] =
				w83627ehf_पढ़ो_value(data,
					W83627EHF_REG_TARGET[i]) &
					(data->pwm_mode[i] == 1 ? 0x7f : 0xff);
		पूर्ण

		/* Measured temperatures and limits */
		क्रम (i = 0; i < NUM_REG_TEMP; i++) अणु
			अगर (!(data->have_temp & (1 << i)))
				जारी;
			data->temp[i] = w83627ehf_पढ़ो_temp(data,
						data->reg_temp[i]);
			अगर (data->reg_temp_over[i])
				data->temp_max[i]
				  = w83627ehf_पढ़ो_temp(data,
						data->reg_temp_over[i]);
			अगर (data->reg_temp_hyst[i])
				data->temp_max_hyst[i]
				  = w83627ehf_पढ़ो_temp(data,
						data->reg_temp_hyst[i]);
			अगर (i > 2)
				जारी;
			अगर (data->have_temp_offset & (1 << i))
				data->temp_offset[i]
				  = w83627ehf_पढ़ो_value(data,
						W83627EHF_REG_TEMP_OFFSET[i]);
		पूर्ण

		data->alarms = w83627ehf_पढ़ो_value(data,
					W83627EHF_REG_ALARM1) |
			       (w83627ehf_पढ़ो_value(data,
					W83627EHF_REG_ALARM2) << 8) |
			       (w83627ehf_पढ़ो_value(data,
					W83627EHF_REG_ALARM3) << 16);

		data->हालखोलो = w83627ehf_पढ़ो_value(data,
						W83627EHF_REG_CASEOPEN_DET);

		data->last_updated = jअगरfies;
		data->valid = 1;
	पूर्ण

	mutex_unlock(&data->update_lock);
	वापस data;
पूर्ण

#घोषणा store_in_reg(REG, reg) \
अटल पूर्णांक \
store_in_##reg(काष्ठा device *dev, काष्ठा w83627ehf_data *data, पूर्णांक channel, \
	       दीर्घ val) \
अणु \
	अगर (val < 0) \
		वापस -EINVAL; \
	mutex_lock(&data->update_lock); \
	data->in_##reg[channel] = in_to_reg(val, channel, data->scale_in); \
	w83627ehf_ग_लिखो_value(data, W83627EHF_REG_IN_##REG(channel), \
			      data->in_##reg[channel]); \
	mutex_unlock(&data->update_lock); \
	वापस 0; \
पूर्ण

store_in_reg(MIN, min)
store_in_reg(MAX, max)

अटल पूर्णांक
store_fan_min(काष्ठा device *dev, काष्ठा w83627ehf_data *data, पूर्णांक channel,
	      दीर्घ val)
अणु
	अचिन्हित पूर्णांक reg;
	u8 new_भाग;

	अगर (val < 0)
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	अगर (!val) अणु
		/* No min limit, alarm disabled */
		data->fan_min[channel] = 255;
		new_भाग = data->fan_भाग[channel]; /* No change */
		dev_info(dev, "fan%u low limit and alarm disabled\n",
			 channel + 1);
	पूर्ण अन्यथा अगर ((reg = 1350000U / val) >= 128 * 255) अणु
		/*
		 * Speed below this value cannot possibly be represented,
		 * even with the highest भागider (128)
		 */
		data->fan_min[channel] = 254;
		new_भाग = 7; /* 128 == (1 << 7) */
		dev_warn(dev,
			 "fan%u low limit %lu below minimum %u, set to minimum\n",
			 channel + 1, val, fan_from_reg8(254, 7));
	पूर्ण अन्यथा अगर (!reg) अणु
		/*
		 * Speed above this value cannot possibly be represented,
		 * even with the lowest भागider (1)
		 */
		data->fan_min[channel] = 1;
		new_भाग = 0; /* 1 == (1 << 0) */
		dev_warn(dev,
			 "fan%u low limit %lu above maximum %u, set to maximum\n",
			 channel + 1, val, fan_from_reg8(1, 0));
	पूर्ण अन्यथा अणु
		/*
		 * Automatically pick the best भागider, i.e. the one such
		 * that the min limit will correspond to a रेजिस्टर value
		 * in the 96..192 range
		 */
		new_भाग = 0;
		जबतक (reg > 192 && new_भाग < 7) अणु
			reg >>= 1;
			new_भाग++;
		पूर्ण
		data->fan_min[channel] = reg;
	पूर्ण

	/*
	 * Write both the fan घड़ी भागider (अगर it changed) and the new
	 * fan min (unconditionally)
	 */
	अगर (new_भाग != data->fan_भाग[channel]) अणु
		dev_dbg(dev, "fan%u clock divider changed from %u to %u\n",
			channel + 1, भाग_from_reg(data->fan_भाग[channel]),
			भाग_from_reg(new_भाग));
		data->fan_भाग[channel] = new_भाग;
		w83627ehf_ग_लिखो_fan_भाग(data, channel);
		/* Give the chip समय to sample a new speed value */
		data->last_updated = jअगरfies;
	पूर्ण

	w83627ehf_ग_लिखो_value(data, W83627EHF_REG_FAN_MIN[channel],
			      data->fan_min[channel]);
	mutex_unlock(&data->update_lock);

	वापस 0;
पूर्ण

#घोषणा store_temp_reg(addr, reg) \
अटल पूर्णांक \
store_##reg(काष्ठा device *dev, काष्ठा w83627ehf_data *data, पूर्णांक channel, \
	    दीर्घ val) \
अणु \
	mutex_lock(&data->update_lock); \
	data->reg[channel] = LM75_TEMP_TO_REG(val); \
	w83627ehf_ग_लिखो_temp(data, data->addr[channel], data->reg[channel]); \
	mutex_unlock(&data->update_lock); \
	वापस 0; \
पूर्ण
store_temp_reg(reg_temp_over, temp_max);
store_temp_reg(reg_temp_hyst, temp_max_hyst);

अटल पूर्णांक
store_temp_offset(काष्ठा device *dev, काष्ठा w83627ehf_data *data, पूर्णांक channel,
		  दीर्घ val)
अणु
	val = clamp_val(DIV_ROUND_CLOSEST(val, 1000), -128, 127);

	mutex_lock(&data->update_lock);
	data->temp_offset[channel] = val;
	w83627ehf_ग_लिखो_value(data, W83627EHF_REG_TEMP_OFFSET[channel], val);
	mutex_unlock(&data->update_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक
store_pwm_mode(काष्ठा device *dev, काष्ठा w83627ehf_data *data, पूर्णांक channel,
	       दीर्घ val)
अणु
	u16 reg;

	अगर (val < 0 || val > 1)
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	reg = w83627ehf_पढ़ो_value(data, W83627EHF_REG_PWM_ENABLE[channel]);
	data->pwm_mode[channel] = val;
	reg &= ~(1 << W83627EHF_PWM_MODE_SHIFT[channel]);
	अगर (!val)
		reg |= 1 << W83627EHF_PWM_MODE_SHIFT[channel];
	w83627ehf_ग_लिखो_value(data, W83627EHF_REG_PWM_ENABLE[channel], reg);
	mutex_unlock(&data->update_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक
store_pwm(काष्ठा device *dev, काष्ठा w83627ehf_data *data, पूर्णांक channel,
	  दीर्घ val)
अणु
	val = clamp_val(val, 0, 255);

	mutex_lock(&data->update_lock);
	data->pwm[channel] = val;
	w83627ehf_ग_लिखो_value(data, W83627EHF_REG_PWM[channel], val);
	mutex_unlock(&data->update_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक
store_pwm_enable(काष्ठा device *dev, काष्ठा w83627ehf_data *data, पूर्णांक channel,
		 दीर्घ val)
अणु
	u16 reg;

	अगर (!val || val < 0 ||
	    (val > 4 && val != data->pwm_enable_orig[channel]))
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	data->pwm_enable[channel] = val;
	reg = w83627ehf_पढ़ो_value(data,
				   W83627EHF_REG_PWM_ENABLE[channel]);
	reg &= ~(0x03 << W83627EHF_PWM_ENABLE_SHIFT[channel]);
	reg |= (val - 1) << W83627EHF_PWM_ENABLE_SHIFT[channel];
	w83627ehf_ग_लिखो_value(data, W83627EHF_REG_PWM_ENABLE[channel],
			      reg);
	mutex_unlock(&data->update_lock);
	वापस 0;
पूर्ण

#घोषणा show_tol_temp(reg) \
अटल sमाप_प्रकार show_##reg(काष्ठा device *dev, काष्ठा device_attribute *attr, \
				अक्षर *buf) \
अणु \
	काष्ठा w83627ehf_data *data = w83627ehf_update_device(dev->parent); \
	काष्ठा sensor_device_attribute *sensor_attr = \
		to_sensor_dev_attr(attr); \
	पूर्णांक nr = sensor_attr->index; \
	वापस प्र_लिखो(buf, "%d\n", data->reg[nr] * 1000); \
पूर्ण

show_tol_temp(tolerance)
show_tol_temp(target_temp)

अटल sमाप_प्रकार
store_target_temp(काष्ठा device *dev, काष्ठा device_attribute *attr,
			स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा w83627ehf_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err < 0)
		वापस err;

	val = clamp_val(DIV_ROUND_CLOSEST(val, 1000), 0, 127);

	mutex_lock(&data->update_lock);
	data->target_temp[nr] = val;
	w83627ehf_ग_लिखो_value(data, W83627EHF_REG_TARGET[nr], val);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार
store_tolerance(काष्ठा device *dev, काष्ठा device_attribute *attr,
			स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा w83627ehf_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	u16 reg;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err < 0)
		वापस err;

	/* Limit the temp to 0C - 15C */
	val = clamp_val(DIV_ROUND_CLOSEST(val, 1000), 0, 15);

	mutex_lock(&data->update_lock);
	reg = w83627ehf_पढ़ो_value(data, W83627EHF_REG_TOLERANCE[nr]);
	अगर (nr == 1)
		reg = (reg & 0x0f) | (val << 4);
	अन्यथा
		reg = (reg & 0xf0) | val;
	w83627ehf_ग_लिखो_value(data, W83627EHF_REG_TOLERANCE[nr], reg);
	data->tolerance[nr] = val;
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR(pwm1_target, 0644, show_target_temp,
	    store_target_temp, 0);
अटल SENSOR_DEVICE_ATTR(pwm2_target, 0644, show_target_temp,
	    store_target_temp, 1);
अटल SENSOR_DEVICE_ATTR(pwm3_target, 0644, show_target_temp,
	    store_target_temp, 2);
अटल SENSOR_DEVICE_ATTR(pwm4_target, 0644, show_target_temp,
	    store_target_temp, 3);

अटल SENSOR_DEVICE_ATTR(pwm1_tolerance, 0644, show_tolerance,
	    store_tolerance, 0);
अटल SENSOR_DEVICE_ATTR(pwm2_tolerance, 0644, show_tolerance,
	    store_tolerance, 1);
अटल SENSOR_DEVICE_ATTR(pwm3_tolerance, 0644, show_tolerance,
	    store_tolerance, 2);
अटल SENSOR_DEVICE_ATTR(pwm4_tolerance, 0644, show_tolerance,
	    store_tolerance, 3);

/* Smart Fan रेजिस्टरs */

#घोषणा fan_functions(reg, REG) \
अटल sमाप_प्रकार show_##reg(काष्ठा device *dev, काष्ठा device_attribute *attr, \
		       अक्षर *buf) \
अणु \
	काष्ठा w83627ehf_data *data = w83627ehf_update_device(dev->parent); \
	काष्ठा sensor_device_attribute *sensor_attr = \
		to_sensor_dev_attr(attr); \
	पूर्णांक nr = sensor_attr->index; \
	वापस प्र_लिखो(buf, "%d\n", data->reg[nr]); \
पूर्ण \
अटल sमाप_प्रकार \
store_##reg(काष्ठा device *dev, काष्ठा device_attribute *attr, \
			    स्थिर अक्षर *buf, माप_प्रकार count) \
अणु \
	काष्ठा w83627ehf_data *data = dev_get_drvdata(dev); \
	काष्ठा sensor_device_attribute *sensor_attr = \
		to_sensor_dev_attr(attr); \
	पूर्णांक nr = sensor_attr->index; \
	अचिन्हित दीर्घ val; \
	पूर्णांक err; \
	err = kम_से_अदीर्घ(buf, 10, &val); \
	अगर (err < 0) \
		वापस err; \
	val = clamp_val(val, 1, 255); \
	mutex_lock(&data->update_lock); \
	data->reg[nr] = val; \
	w83627ehf_ग_लिखो_value(data, REG[nr], val); \
	mutex_unlock(&data->update_lock); \
	वापस count; \
पूर्ण

fan_functions(fan_start_output, W83627EHF_REG_FAN_START_OUTPUT)
fan_functions(fan_stop_output, W83627EHF_REG_FAN_STOP_OUTPUT)
fan_functions(fan_max_output, data->REG_FAN_MAX_OUTPUT)
fan_functions(fan_step_output, data->REG_FAN_STEP_OUTPUT)

#घोषणा fan_समय_functions(reg, REG) \
अटल sमाप_प्रकार show_##reg(काष्ठा device *dev, काष्ठा device_attribute *attr, \
				अक्षर *buf) \
अणु \
	काष्ठा w83627ehf_data *data = w83627ehf_update_device(dev->parent); \
	काष्ठा sensor_device_attribute *sensor_attr = \
		to_sensor_dev_attr(attr); \
	पूर्णांक nr = sensor_attr->index; \
	वापस प्र_लिखो(buf, "%d\n", \
			step_समय_from_reg(data->reg[nr], \
					   data->pwm_mode[nr])); \
पूर्ण \
\
अटल sमाप_प्रकार \
store_##reg(काष्ठा device *dev, काष्ठा device_attribute *attr, \
			स्थिर अक्षर *buf, माप_प्रकार count) \
अणु \
	काष्ठा w83627ehf_data *data = dev_get_drvdata(dev); \
	काष्ठा sensor_device_attribute *sensor_attr = \
		to_sensor_dev_attr(attr); \
	पूर्णांक nr = sensor_attr->index; \
	अचिन्हित दीर्घ val; \
	पूर्णांक err; \
	err = kम_से_अदीर्घ(buf, 10, &val); \
	अगर (err < 0) \
		वापस err; \
	val = step_समय_प्रकारo_reg(val, data->pwm_mode[nr]); \
	mutex_lock(&data->update_lock); \
	data->reg[nr] = val; \
	w83627ehf_ग_लिखो_value(data, REG[nr], val); \
	mutex_unlock(&data->update_lock); \
	वापस count; \
पूर्ण \

fan_समय_functions(fan_stop_समय, W83627EHF_REG_FAN_STOP_TIME)

अटल SENSOR_DEVICE_ATTR(pwm4_stop_समय, 0644, show_fan_stop_समय,
	    store_fan_stop_समय, 3);
अटल SENSOR_DEVICE_ATTR(pwm4_start_output, 0644, show_fan_start_output,
	    store_fan_start_output, 3);
अटल SENSOR_DEVICE_ATTR(pwm4_stop_output, 0644, show_fan_stop_output,
	    store_fan_stop_output, 3);
अटल SENSOR_DEVICE_ATTR(pwm4_max_output, 0644, show_fan_max_output,
	    store_fan_max_output, 3);
अटल SENSOR_DEVICE_ATTR(pwm4_step_output, 0644, show_fan_step_output,
	    store_fan_step_output, 3);

अटल SENSOR_DEVICE_ATTR(pwm3_stop_समय, 0644, show_fan_stop_समय,
	    store_fan_stop_समय, 2);
अटल SENSOR_DEVICE_ATTR(pwm3_start_output, 0644, show_fan_start_output,
	    store_fan_start_output, 2);
अटल SENSOR_DEVICE_ATTR(pwm3_stop_output, 0644, show_fan_stop_output,
		    store_fan_stop_output, 2);

अटल SENSOR_DEVICE_ATTR(pwm1_stop_समय, 0644, show_fan_stop_समय,
	    store_fan_stop_समय, 0);
अटल SENSOR_DEVICE_ATTR(pwm2_stop_समय, 0644, show_fan_stop_समय,
	    store_fan_stop_समय, 1);
अटल SENSOR_DEVICE_ATTR(pwm1_start_output, 0644, show_fan_start_output,
	    store_fan_start_output, 0);
अटल SENSOR_DEVICE_ATTR(pwm2_start_output, 0644, show_fan_start_output,
	    store_fan_start_output, 1);
अटल SENSOR_DEVICE_ATTR(pwm1_stop_output, 0644, show_fan_stop_output,
	    store_fan_stop_output, 0);
अटल SENSOR_DEVICE_ATTR(pwm2_stop_output, 0644, show_fan_stop_output,
	    store_fan_stop_output, 1);


/*
 * pwm1 and pwm3 करोn't support max and step settings on all chips.
 * Need to check support जबतक generating/removing attribute files.
 */
अटल SENSOR_DEVICE_ATTR(pwm1_max_output, 0644, show_fan_max_output,
	    store_fan_max_output, 0);
अटल SENSOR_DEVICE_ATTR(pwm1_step_output, 0644, show_fan_step_output,
	    store_fan_step_output, 0);
अटल SENSOR_DEVICE_ATTR(pwm2_max_output, 0644, show_fan_max_output,
	    store_fan_max_output, 1);
अटल SENSOR_DEVICE_ATTR(pwm2_step_output, 0644, show_fan_step_output,
	    store_fan_step_output, 1);
अटल SENSOR_DEVICE_ATTR(pwm3_max_output, 0644, show_fan_max_output,
	    store_fan_max_output, 2);
अटल SENSOR_DEVICE_ATTR(pwm3_step_output, 0644, show_fan_step_output,
	    store_fan_step_output, 2);

अटल sमाप_प्रकार
cpu0_vid_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा w83627ehf_data *data = dev_get_drvdata(dev);
	वापस प्र_लिखो(buf, "%d\n", vid_from_reg(data->vid, data->vrm));
पूर्ण
DEVICE_ATTR_RO(cpu0_vid);


/* Case खोलो detection */
अटल पूर्णांक
clear_हालखोलो(काष्ठा device *dev, काष्ठा w83627ehf_data *data, पूर्णांक channel,
	       दीर्घ val)
अणु
	स्थिर u16 mask = 0x80;
	u16 reg;

	अगर (val != 0 || channel != 0)
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	reg = w83627ehf_पढ़ो_value(data, W83627EHF_REG_CASEOPEN_CLR);
	w83627ehf_ग_लिखो_value(data, W83627EHF_REG_CASEOPEN_CLR, reg | mask);
	w83627ehf_ग_लिखो_value(data, W83627EHF_REG_CASEOPEN_CLR, reg & ~mask);
	data->valid = 0;	/* Force cache refresh */
	mutex_unlock(&data->update_lock);

	वापस 0;
पूर्ण

अटल umode_t w83627ehf_attrs_visible(काष्ठा kobject *kobj,
				       काष्ठा attribute *a, पूर्णांक n)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा w83627ehf_data *data = dev_get_drvdata(dev);
	काष्ठा device_attribute *devattr;
	काष्ठा sensor_device_attribute *sda;

	devattr = container_of(a, काष्ठा device_attribute, attr);

	/* Not sensor */
	अगर (devattr->show == cpu0_vid_show && data->have_vid)
		वापस a->mode;

	sda = (काष्ठा sensor_device_attribute *)devattr;

	अगर (sda->index < 2 &&
		(devattr->show == show_fan_stop_समय ||
		 devattr->show == show_fan_start_output ||
		 devattr->show == show_fan_stop_output))
		वापस a->mode;

	अगर (sda->index < 3 &&
		(devattr->show == show_fan_max_output ||
		 devattr->show == show_fan_step_output) &&
		data->REG_FAN_STEP_OUTPUT &&
		data->REG_FAN_STEP_OUTPUT[sda->index] != 0xff)
		वापस a->mode;

	/* अगर fan3 and fan4 are enabled create the files क्रम them */
	अगर (sda->index == 2 &&
		(data->has_fan & (1 << 2)) && data->pwm_num >= 3 &&
		(devattr->show == show_fan_stop_समय ||
		 devattr->show == show_fan_start_output ||
		 devattr->show == show_fan_stop_output))
		वापस a->mode;

	अगर (sda->index == 3 &&
		(data->has_fan & (1 << 3)) && data->pwm_num >= 4 &&
		(devattr->show == show_fan_stop_समय ||
		 devattr->show == show_fan_start_output ||
		 devattr->show == show_fan_stop_output ||
		 devattr->show == show_fan_max_output ||
		 devattr->show == show_fan_step_output))
		वापस a->mode;

	अगर ((devattr->show == show_target_temp ||
	    devattr->show == show_tolerance) &&
	    (data->has_fan & (1 << sda->index)) &&
	    sda->index < data->pwm_num)
		वापस a->mode;

	वापस 0;
पूर्ण

/* These groups handle non-standard attributes used in this device */
अटल काष्ठा attribute *w83627ehf_attrs[] = अणु

	&sensor_dev_attr_pwm1_stop_समय.dev_attr.attr,
	&sensor_dev_attr_pwm1_start_output.dev_attr.attr,
	&sensor_dev_attr_pwm1_stop_output.dev_attr.attr,
	&sensor_dev_attr_pwm1_max_output.dev_attr.attr,
	&sensor_dev_attr_pwm1_step_output.dev_attr.attr,
	&sensor_dev_attr_pwm1_target.dev_attr.attr,
	&sensor_dev_attr_pwm1_tolerance.dev_attr.attr,

	&sensor_dev_attr_pwm2_stop_समय.dev_attr.attr,
	&sensor_dev_attr_pwm2_start_output.dev_attr.attr,
	&sensor_dev_attr_pwm2_stop_output.dev_attr.attr,
	&sensor_dev_attr_pwm2_max_output.dev_attr.attr,
	&sensor_dev_attr_pwm2_step_output.dev_attr.attr,
	&sensor_dev_attr_pwm2_target.dev_attr.attr,
	&sensor_dev_attr_pwm2_tolerance.dev_attr.attr,

	&sensor_dev_attr_pwm3_stop_समय.dev_attr.attr,
	&sensor_dev_attr_pwm3_start_output.dev_attr.attr,
	&sensor_dev_attr_pwm3_stop_output.dev_attr.attr,
	&sensor_dev_attr_pwm3_max_output.dev_attr.attr,
	&sensor_dev_attr_pwm3_step_output.dev_attr.attr,
	&sensor_dev_attr_pwm3_target.dev_attr.attr,
	&sensor_dev_attr_pwm3_tolerance.dev_attr.attr,

	&sensor_dev_attr_pwm4_stop_समय.dev_attr.attr,
	&sensor_dev_attr_pwm4_start_output.dev_attr.attr,
	&sensor_dev_attr_pwm4_stop_output.dev_attr.attr,
	&sensor_dev_attr_pwm4_max_output.dev_attr.attr,
	&sensor_dev_attr_pwm4_step_output.dev_attr.attr,
	&sensor_dev_attr_pwm4_target.dev_attr.attr,
	&sensor_dev_attr_pwm4_tolerance.dev_attr.attr,

	&dev_attr_cpu0_vid.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group w83627ehf_group = अणु
	.attrs = w83627ehf_attrs,
	.is_visible = w83627ehf_attrs_visible,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *w83627ehf_groups[] = अणु
	&w83627ehf_group,
	शून्य
पूर्ण;

/*
 * Driver and device management
 */

/* Get the monitoring functions started */
अटल अंतरभूत व्योम w83627ehf_init_device(काष्ठा w83627ehf_data *data,
						   क्रमागत kinds kind)
अणु
	पूर्णांक i;
	u8 पंचांगp, diode;

	/* Start monitoring is needed */
	पंचांगp = w83627ehf_पढ़ो_value(data, W83627EHF_REG_CONFIG);
	अगर (!(पंचांगp & 0x01))
		w83627ehf_ग_लिखो_value(data, W83627EHF_REG_CONFIG,
				      पंचांगp | 0x01);

	/* Enable temperature sensors अगर needed */
	क्रम (i = 0; i < NUM_REG_TEMP; i++) अणु
		अगर (!(data->have_temp & (1 << i)))
			जारी;
		अगर (!data->reg_temp_config[i])
			जारी;
		पंचांगp = w83627ehf_पढ़ो_value(data,
					   data->reg_temp_config[i]);
		अगर (पंचांगp & 0x01)
			w83627ehf_ग_लिखो_value(data,
					      data->reg_temp_config[i],
					      पंचांगp & 0xfe);
	पूर्ण

	/* Enable VBAT monitoring अगर needed */
	पंचांगp = w83627ehf_पढ़ो_value(data, W83627EHF_REG_VBAT);
	अगर (!(पंचांगp & 0x01))
		w83627ehf_ग_लिखो_value(data, W83627EHF_REG_VBAT, पंचांगp | 0x01);

	/* Get thermal sensor types */
	चयन (kind) अणु
	हाल w83627ehf:
		diode = w83627ehf_पढ़ो_value(data, W83627EHF_REG_DIODE);
		अवरोध;
	हाल w83627uhg:
		diode = 0x00;
		अवरोध;
	शेष:
		diode = 0x70;
	पूर्ण
	क्रम (i = 0; i < 3; i++) अणु
		स्थिर अक्षर *label = शून्य;

		अगर (data->temp_label)
			label = data->temp_label[data->temp_src[i]];

		/* Digital source overrides analog type */
		अगर (label && म_भेदन(label, "PECI", 4) == 0)
			data->temp_type[i] = 6;
		अन्यथा अगर (label && म_भेदन(label, "AMD", 3) == 0)
			data->temp_type[i] = 5;
		अन्यथा अगर ((पंचांगp & (0x02 << i)))
			data->temp_type[i] = (diode & (0x10 << i)) ? 1 : 3;
		अन्यथा
			data->temp_type[i] = 4; /* thermistor */
	पूर्ण
पूर्ण

अटल व्योम
w83627ehf_set_temp_reg_ehf(काष्ठा w83627ehf_data *data, पूर्णांक n_temp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < n_temp; i++) अणु
		data->reg_temp[i] = W83627EHF_REG_TEMP[i];
		data->reg_temp_over[i] = W83627EHF_REG_TEMP_OVER[i];
		data->reg_temp_hyst[i] = W83627EHF_REG_TEMP_HYST[i];
		data->reg_temp_config[i] = W83627EHF_REG_TEMP_CONFIG[i];
	पूर्ण
पूर्ण

अटल व्योम
w83627ehf_check_fan_inमाला_दो(स्थिर काष्ठा w83627ehf_sio_data *sio_data,
			   काष्ठा w83627ehf_data *data)
अणु
	पूर्णांक fan3pin, fan4pin, fan5pin, regval;

	/* The W83627UHG is simple, only two fan inमाला_दो, no config */
	अगर (sio_data->kind == w83627uhg) अणु
		data->has_fan = 0x03; /* fan1 and fan2 */
		data->has_fan_min = 0x03;
		वापस;
	पूर्ण

	/* fan4 and fan5 share some pins with the GPIO and serial flash */
	अगर (sio_data->kind == w83667hg || sio_data->kind == w83667hg_b) अणु
		fan3pin = 1;
		fan4pin = superio_inb(sio_data->sioreg, 0x27) & 0x40;
		fan5pin = superio_inb(sio_data->sioreg, 0x27) & 0x20;
	पूर्ण अन्यथा अणु
		fan3pin = 1;
		fan4pin = !(superio_inb(sio_data->sioreg, 0x29) & 0x06);
		fan5pin = !(superio_inb(sio_data->sioreg, 0x24) & 0x02);
	पूर्ण

	data->has_fan = data->has_fan_min = 0x03; /* fan1 and fan2 */
	data->has_fan |= (fan3pin << 2);
	data->has_fan_min |= (fan3pin << 2);

	/*
	 * It looks like fan4 and fan5 pins can be alternatively used
	 * as fan on/off चयनes, but fan5 control is ग_लिखो only :/
	 * We assume that अगर the serial पूर्णांकerface is disabled, designers
	 * connected fan5 as input unless they are emitting log 1, which
	 * is not the शेष.
	 */
	regval = w83627ehf_पढ़ो_value(data, W83627EHF_REG_FANDIV1);
	अगर ((regval & (1 << 2)) && fan4pin) अणु
		data->has_fan |= (1 << 3);
		data->has_fan_min |= (1 << 3);
	पूर्ण
	अगर (!(regval & (1 << 1)) && fan5pin) अणु
		data->has_fan |= (1 << 4);
		data->has_fan_min |= (1 << 4);
	पूर्ण
पूर्ण

अटल umode_t
w83627ehf_is_visible(स्थिर व्योम *drvdata, क्रमागत hwmon_sensor_types type,
		     u32 attr, पूर्णांक channel)
अणु
	स्थिर काष्ठा w83627ehf_data *data = drvdata;

	चयन (type) अणु
	हाल hwmon_temp:
		/* channel 0.., name 1.. */
		अगर (!(data->have_temp & (1 << channel)))
			वापस 0;
		अगर (attr == hwmon_temp_input)
			वापस 0444;
		अगर (attr == hwmon_temp_label) अणु
			अगर (data->temp_label)
				वापस 0444;
			वापस 0;
		पूर्ण
		अगर (channel == 2 && data->temp3_val_only)
			वापस 0;
		अगर (attr == hwmon_temp_max) अणु
			अगर (data->reg_temp_over[channel])
				वापस 0644;
			अन्यथा
				वापस 0;
		पूर्ण
		अगर (attr == hwmon_temp_max_hyst) अणु
			अगर (data->reg_temp_hyst[channel])
				वापस 0644;
			अन्यथा
				वापस 0;
		पूर्ण
		अगर (channel > 2)
			वापस 0;
		अगर (attr == hwmon_temp_alarm || attr == hwmon_temp_type)
			वापस 0444;
		अगर (attr == hwmon_temp_offset) अणु
			अगर (data->have_temp_offset & (1 << channel))
				वापस 0644;
			अन्यथा
				वापस 0;
		पूर्ण
		अवरोध;

	हाल hwmon_fan:
		/* channel 0.., name 1.. */
		अगर (!(data->has_fan & (1 << channel)))
			वापस 0;
		अगर (attr == hwmon_fan_input || attr == hwmon_fan_alarm)
			वापस 0444;
		अगर (attr == hwmon_fan_भाग) अणु
			वापस 0444;
		पूर्ण
		अगर (attr == hwmon_fan_min) अणु
			अगर (data->has_fan_min & (1 << channel))
				वापस 0644;
			अन्यथा
				वापस 0;
		पूर्ण
		अवरोध;

	हाल hwmon_in:
		/* channel 0.., name 0.. */
		अगर (channel >= data->in_num)
			वापस 0;
		अगर (channel == 6 && data->in6_skip)
			वापस 0;
		अगर (attr == hwmon_in_alarm || attr == hwmon_in_input)
			वापस 0444;
		अगर (attr == hwmon_in_min || attr == hwmon_in_max)
			वापस 0644;
		अवरोध;

	हाल hwmon_pwm:
		/* channel 0.., name 1.. */
		अगर (!(data->has_fan & (1 << channel)) ||
		    channel >= data->pwm_num)
			वापस 0;
		अगर (attr == hwmon_pwm_mode || attr == hwmon_pwm_enable ||
		    attr == hwmon_pwm_input)
			वापस 0644;
		अवरोध;

	हाल hwmon_पूर्णांकrusion:
		वापस 0644;

	शेष: /* Shouldn't happen */
		वापस 0;
	पूर्ण

	वापस 0; /* Shouldn't happen */
पूर्ण

अटल पूर्णांक
w83627ehf_करो_पढ़ो_temp(काष्ठा w83627ehf_data *data, u32 attr,
		       पूर्णांक channel, दीर्घ *val)
अणु
	चयन (attr) अणु
	हाल hwmon_temp_input:
		*val = LM75_TEMP_FROM_REG(data->temp[channel]);
		वापस 0;
	हाल hwmon_temp_max:
		*val = LM75_TEMP_FROM_REG(data->temp_max[channel]);
		वापस 0;
	हाल hwmon_temp_max_hyst:
		*val = LM75_TEMP_FROM_REG(data->temp_max_hyst[channel]);
		वापस 0;
	हाल hwmon_temp_offset:
		*val = data->temp_offset[channel] * 1000;
		वापस 0;
	हाल hwmon_temp_type:
		*val = (पूर्णांक)data->temp_type[channel];
		वापस 0;
	हाल hwmon_temp_alarm:
		अगर (channel < 3) अणु
			पूर्णांक bit[] = अणु 4, 5, 13 पूर्ण;
			*val = (data->alarms >> bit[channel]) & 1;
			वापस 0;
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक
w83627ehf_करो_पढ़ो_in(काष्ठा w83627ehf_data *data, u32 attr,
		     पूर्णांक channel, दीर्घ *val)
अणु
	चयन (attr) अणु
	हाल hwmon_in_input:
		*val = in_from_reg(data->in[channel], channel, data->scale_in);
		वापस 0;
	हाल hwmon_in_min:
		*val = in_from_reg(data->in_min[channel], channel,
				   data->scale_in);
		वापस 0;
	हाल hwmon_in_max:
		*val = in_from_reg(data->in_max[channel], channel,
				   data->scale_in);
		वापस 0;
	हाल hwmon_in_alarm:
		अगर (channel < 10) अणु
			पूर्णांक bit[] = अणु 0, 1, 2, 3, 8, 21, 20, 16, 17, 19 पूर्ण;
			*val = (data->alarms >> bit[channel]) & 1;
			वापस 0;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक
w83627ehf_करो_पढ़ो_fan(काष्ठा w83627ehf_data *data, u32 attr,
		      पूर्णांक channel, दीर्घ *val)
अणु
	चयन (attr) अणु
	हाल hwmon_fan_input:
		*val = data->rpm[channel];
		वापस 0;
	हाल hwmon_fan_min:
		*val = fan_from_reg8(data->fan_min[channel],
				     data->fan_भाग[channel]);
		वापस 0;
	हाल hwmon_fan_भाग:
		*val = भाग_from_reg(data->fan_भाग[channel]);
		वापस 0;
	हाल hwmon_fan_alarm:
		अगर (channel < 5) अणु
			पूर्णांक bit[] = अणु 6, 7, 11, 10, 23 पूर्ण;
			*val = (data->alarms >> bit[channel]) & 1;
			वापस 0;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक
w83627ehf_करो_पढ़ो_pwm(काष्ठा w83627ehf_data *data, u32 attr,
		      पूर्णांक channel, दीर्घ *val)
अणु
	चयन (attr) अणु
	हाल hwmon_pwm_input:
		*val = data->pwm[channel];
		वापस 0;
	हाल hwmon_pwm_enable:
		*val = data->pwm_enable[channel];
		वापस 0;
	हाल hwmon_pwm_mode:
		*val = data->pwm_enable[channel];
		वापस 0;
	शेष:
		अवरोध;
	पूर्ण
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक
w83627ehf_करो_पढ़ो_पूर्णांकrusion(काष्ठा w83627ehf_data *data, u32 attr,
			    पूर्णांक channel, दीर्घ *val)
अणु
	अगर (attr != hwmon_पूर्णांकrusion_alarm || channel != 0)
		वापस -EOPNOTSUPP; /* shouldn't happen */

	*val = !!(data->हालखोलो & 0x10);
	वापस 0;
पूर्ण

अटल पूर्णांक
w83627ehf_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			u32 attr, पूर्णांक channel, दीर्घ *val)
अणु
	काष्ठा w83627ehf_data *data = w83627ehf_update_device(dev->parent);

	चयन (type) अणु
	हाल hwmon_fan:
		वापस w83627ehf_करो_पढ़ो_fan(data, attr, channel, val);

	हाल hwmon_in:
		वापस w83627ehf_करो_पढ़ो_in(data, attr, channel, val);

	हाल hwmon_pwm:
		वापस w83627ehf_करो_पढ़ो_pwm(data, attr, channel, val);

	हाल hwmon_temp:
		वापस w83627ehf_करो_पढ़ो_temp(data, attr, channel, val);

	हाल hwmon_पूर्णांकrusion:
		वापस w83627ehf_करो_पढ़ो_पूर्णांकrusion(data, attr, channel, val);

	शेष:
		अवरोध;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक
w83627ehf_पढ़ो_string(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
		      u32 attr, पूर्णांक channel, स्थिर अक्षर **str)
अणु
	काष्ठा w83627ehf_data *data = dev_get_drvdata(dev);

	चयन (type) अणु
	हाल hwmon_temp:
		अगर (attr == hwmon_temp_label) अणु
			*str = data->temp_label[data->temp_src[channel]];
			वापस 0;
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
	/* Nothing अन्यथा should be पढ़ो as a string */
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक
w83627ehf_ग_लिखो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			u32 attr, पूर्णांक channel, दीर्घ val)
अणु
	काष्ठा w83627ehf_data *data = dev_get_drvdata(dev);

	अगर (type == hwmon_in && attr == hwmon_in_min)
		वापस store_in_min(dev, data, channel, val);
	अगर (type == hwmon_in && attr == hwmon_in_max)
		वापस store_in_max(dev, data, channel, val);

	अगर (type == hwmon_fan && attr == hwmon_fan_min)
		वापस store_fan_min(dev, data, channel, val);

	अगर (type == hwmon_temp && attr == hwmon_temp_max)
		वापस store_temp_max(dev, data, channel, val);
	अगर (type == hwmon_temp && attr == hwmon_temp_max_hyst)
		वापस store_temp_max_hyst(dev, data, channel, val);
	अगर (type == hwmon_temp && attr == hwmon_temp_offset)
		वापस store_temp_offset(dev, data, channel, val);

	अगर (type == hwmon_pwm && attr == hwmon_pwm_mode)
		वापस store_pwm_mode(dev, data, channel, val);
	अगर (type == hwmon_pwm && attr == hwmon_pwm_enable)
		वापस store_pwm_enable(dev, data, channel, val);
	अगर (type == hwmon_pwm && attr == hwmon_pwm_input)
		वापस store_pwm(dev, data, channel, val);

	अगर (type == hwmon_पूर्णांकrusion && attr == hwmon_पूर्णांकrusion_alarm)
		वापस clear_हालखोलो(dev, data, channel, val);

	वापस -EOPNOTSUPP;
पूर्ण

अटल स्थिर काष्ठा hwmon_ops w83627ehf_ops = अणु
	.is_visible = w83627ehf_is_visible,
	.पढ़ो = w83627ehf_पढ़ो,
	.पढ़ो_string = w83627ehf_पढ़ो_string,
	.ग_लिखो = w83627ehf_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info *w83627ehf_info[] = अणु
	HWMON_CHANNEL_INFO(fan,
		HWMON_F_ALARM | HWMON_F_DIV | HWMON_F_INPUT | HWMON_F_MIN,
		HWMON_F_ALARM | HWMON_F_DIV | HWMON_F_INPUT | HWMON_F_MIN,
		HWMON_F_ALARM | HWMON_F_DIV | HWMON_F_INPUT | HWMON_F_MIN,
		HWMON_F_ALARM | HWMON_F_DIV | HWMON_F_INPUT | HWMON_F_MIN,
		HWMON_F_ALARM | HWMON_F_DIV | HWMON_F_INPUT | HWMON_F_MIN),
	HWMON_CHANNEL_INFO(in,
		HWMON_I_ALARM | HWMON_I_INPUT | HWMON_I_MAX | HWMON_I_MIN,
		HWMON_I_ALARM | HWMON_I_INPUT | HWMON_I_MAX | HWMON_I_MIN,
		HWMON_I_ALARM | HWMON_I_INPUT | HWMON_I_MAX | HWMON_I_MIN,
		HWMON_I_ALARM | HWMON_I_INPUT | HWMON_I_MAX | HWMON_I_MIN,
		HWMON_I_ALARM | HWMON_I_INPUT | HWMON_I_MAX | HWMON_I_MIN,
		HWMON_I_ALARM | HWMON_I_INPUT | HWMON_I_MAX | HWMON_I_MIN,
		HWMON_I_ALARM | HWMON_I_INPUT | HWMON_I_MAX | HWMON_I_MIN,
		HWMON_I_ALARM | HWMON_I_INPUT | HWMON_I_MAX | HWMON_I_MIN,
		HWMON_I_ALARM | HWMON_I_INPUT | HWMON_I_MAX | HWMON_I_MIN,
		HWMON_I_ALARM | HWMON_I_INPUT | HWMON_I_MAX | HWMON_I_MIN),
	HWMON_CHANNEL_INFO(pwm,
		HWMON_PWM_ENABLE | HWMON_PWM_INPUT | HWMON_PWM_MODE,
		HWMON_PWM_ENABLE | HWMON_PWM_INPUT | HWMON_PWM_MODE,
		HWMON_PWM_ENABLE | HWMON_PWM_INPUT | HWMON_PWM_MODE,
		HWMON_PWM_ENABLE | HWMON_PWM_INPUT | HWMON_PWM_MODE),
	HWMON_CHANNEL_INFO(temp,
		HWMON_T_ALARM | HWMON_T_INPUT | HWMON_T_LABEL | HWMON_T_MAX |
			HWMON_T_MAX_HYST | HWMON_T_OFFSET | HWMON_T_TYPE,
		HWMON_T_ALARM | HWMON_T_INPUT | HWMON_T_LABEL | HWMON_T_MAX |
			HWMON_T_MAX_HYST | HWMON_T_OFFSET | HWMON_T_TYPE,
		HWMON_T_ALARM | HWMON_T_INPUT | HWMON_T_LABEL | HWMON_T_MAX |
			HWMON_T_MAX_HYST | HWMON_T_OFFSET | HWMON_T_TYPE,
		HWMON_T_ALARM | HWMON_T_INPUT | HWMON_T_LABEL | HWMON_T_MAX |
			HWMON_T_MAX_HYST | HWMON_T_OFFSET | HWMON_T_TYPE,
		HWMON_T_ALARM | HWMON_T_INPUT | HWMON_T_LABEL | HWMON_T_MAX |
			HWMON_T_MAX_HYST | HWMON_T_OFFSET | HWMON_T_TYPE,
		HWMON_T_ALARM | HWMON_T_INPUT | HWMON_T_LABEL | HWMON_T_MAX |
			HWMON_T_MAX_HYST | HWMON_T_OFFSET | HWMON_T_TYPE,
		HWMON_T_ALARM | HWMON_T_INPUT | HWMON_T_LABEL | HWMON_T_MAX |
			HWMON_T_MAX_HYST | HWMON_T_OFFSET | HWMON_T_TYPE,
		HWMON_T_ALARM | HWMON_T_INPUT | HWMON_T_LABEL | HWMON_T_MAX |
			HWMON_T_MAX_HYST | HWMON_T_OFFSET | HWMON_T_TYPE,
		HWMON_T_ALARM | HWMON_T_INPUT | HWMON_T_LABEL | HWMON_T_MAX |
			HWMON_T_MAX_HYST | HWMON_T_OFFSET | HWMON_T_TYPE),
	HWMON_CHANNEL_INFO(पूर्णांकrusion,
		HWMON_INTRUSION_ALARM),
	शून्य
पूर्ण;

अटल स्थिर काष्ठा hwmon_chip_info w83627ehf_chip_info = अणु
	.ops = &w83627ehf_ops,
	.info = w83627ehf_info,
पूर्ण;

अटल पूर्णांक w83627ehf_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा w83627ehf_sio_data *sio_data = dev_get_platdata(dev);
	काष्ठा w83627ehf_data *data;
	काष्ठा resource *res;
	u8 en_vrm10;
	पूर्णांक i, err = 0;
	काष्ठा device *hwmon_dev;

	res = platक्रमm_get_resource(pdev, IORESOURCE_IO, 0);
	अगर (!request_region(res->start, IOREGION_LENGTH, DRVNAME)) अणु
		err = -EBUSY;
		dev_err(dev, "Failed to request region 0x%lx-0x%lx\n",
			(अचिन्हित दीर्घ)res->start,
			(अचिन्हित दीर्घ)res->start + IOREGION_LENGTH - 1);
		जाओ निकास;
	पूर्ण

	data = devm_kzalloc(&pdev->dev, माप(काष्ठा w83627ehf_data),
			    GFP_KERNEL);
	अगर (!data) अणु
		err = -ENOMEM;
		जाओ निकास_release;
	पूर्ण

	data->addr = res->start;
	mutex_init(&data->lock);
	mutex_init(&data->update_lock);
	data->name = w83627ehf_device_names[sio_data->kind];
	data->bank = 0xff;		/* Force initial bank selection */
	platक्रमm_set_drvdata(pdev, data);

	/* 627EHG and 627EHF have 10 voltage inमाला_दो; 627DHG and 667HG have 9 */
	data->in_num = (sio_data->kind == w83627ehf) ? 10 : 9;
	/* 667HG has 3 pwms, and 627UHG has only 2 */
	चयन (sio_data->kind) अणु
	शेष:
		data->pwm_num = 4;
		अवरोध;
	हाल w83667hg:
	हाल w83667hg_b:
		data->pwm_num = 3;
		अवरोध;
	हाल w83627uhg:
		data->pwm_num = 2;
		अवरोध;
	पूर्ण

	/* Default to 3 temperature inमाला_दो, code below will adjust as needed */
	data->have_temp = 0x07;

	/* Deal with temperature रेजिस्टर setup first. */
	अगर (sio_data->kind == w83667hg_b) अणु
		u8 reg;

		w83627ehf_set_temp_reg_ehf(data, 4);

		/*
		 * Temperature sources are selected with bank 0, रेजिस्टरs 0x49
		 * and 0x4a.
		 */
		reg = w83627ehf_पढ़ो_value(data, 0x4a);
		data->temp_src[0] = reg >> 5;
		reg = w83627ehf_पढ़ो_value(data, 0x49);
		data->temp_src[1] = reg & 0x07;
		data->temp_src[2] = (reg >> 4) & 0x07;

		/*
		 * W83667HG-B has another temperature रेजिस्टर at 0x7e.
		 * The temperature source is selected with रेजिस्टर 0x7d.
		 * Support it अगर the source dअगरfers from alपढ़ोy reported
		 * sources.
		 */
		reg = w83627ehf_पढ़ो_value(data, 0x7d);
		reg &= 0x07;
		अगर (reg != data->temp_src[0] && reg != data->temp_src[1]
		    && reg != data->temp_src[2]) अणु
			data->temp_src[3] = reg;
			data->have_temp |= 1 << 3;
		पूर्ण

		/*
		 * Chip supports either AUXTIN or VIN3. Try to find out which
		 * one.
		 */
		reg = w83627ehf_पढ़ो_value(data, W83627EHF_REG_TEMP_CONFIG[2]);
		अगर (data->temp_src[2] == 2 && (reg & 0x01))
			data->have_temp &= ~(1 << 2);

		अगर ((data->temp_src[2] == 2 && (data->have_temp & (1 << 2)))
		    || (data->temp_src[3] == 2 && (data->have_temp & (1 << 3))))
			data->in6_skip = 1;

		data->temp_label = w83667hg_b_temp_label;
		data->have_temp_offset = data->have_temp & 0x07;
		क्रम (i = 0; i < 3; i++) अणु
			अगर (data->temp_src[i] > 2)
				data->have_temp_offset &= ~(1 << i);
		पूर्ण
	पूर्ण अन्यथा अगर (sio_data->kind == w83627uhg) अणु
		u8 reg;

		w83627ehf_set_temp_reg_ehf(data, 3);

		/*
		 * Temperature sources क्रम temp2 and temp3 are selected with
		 * bank 0, रेजिस्टरs 0x49 and 0x4a.
		 */
		data->temp_src[0] = 0;	/* SYSTIN */
		reg = w83627ehf_पढ़ो_value(data, 0x49) & 0x07;
		/* Adjust to have the same mapping as other source रेजिस्टरs */
		अगर (reg == 0)
			data->temp_src[1] = 1;
		अन्यथा अगर (reg >= 2 && reg <= 5)
			data->temp_src[1] = reg + 2;
		अन्यथा	/* should never happen */
			data->have_temp &= ~(1 << 1);
		reg = w83627ehf_पढ़ो_value(data, 0x4a);
		data->temp_src[2] = reg >> 5;

		/*
		 * Skip temp3 अगर source is invalid or the same as temp1
		 * or temp2.
		 */
		अगर (data->temp_src[2] == 2 || data->temp_src[2] == 3 ||
		    data->temp_src[2] == data->temp_src[0] ||
		    ((data->have_temp & (1 << 1)) &&
		     data->temp_src[2] == data->temp_src[1]))
			data->have_temp &= ~(1 << 2);
		अन्यथा
			data->temp3_val_only = 1;	/* No limit regs */

		data->in6_skip = 1;			/* No VIN3 */

		data->temp_label = w83667hg_b_temp_label;
		data->have_temp_offset = data->have_temp & 0x03;
		क्रम (i = 0; i < 3; i++) अणु
			अगर (data->temp_src[i] > 1)
				data->have_temp_offset &= ~(1 << i);
		पूर्ण
	पूर्ण अन्यथा अणु
		w83627ehf_set_temp_reg_ehf(data, 3);

		/* Temperature sources are fixed */

		अगर (sio_data->kind == w83667hg) अणु
			u8 reg;

			/*
			 * Chip supports either AUXTIN or VIN3. Try to find
			 * out which one.
			 */
			reg = w83627ehf_पढ़ो_value(data,
						W83627EHF_REG_TEMP_CONFIG[2]);
			अगर (reg & 0x01)
				data->have_temp &= ~(1 << 2);
			अन्यथा
				data->in6_skip = 1;
		पूर्ण
		data->have_temp_offset = data->have_temp & 0x07;
	पूर्ण

	अगर (sio_data->kind == w83667hg_b) अणु
		data->REG_FAN_MAX_OUTPUT =
		  W83627EHF_REG_FAN_MAX_OUTPUT_W83667_B;
		data->REG_FAN_STEP_OUTPUT =
		  W83627EHF_REG_FAN_STEP_OUTPUT_W83667_B;
	पूर्ण अन्यथा अणु
		data->REG_FAN_MAX_OUTPUT =
		  W83627EHF_REG_FAN_MAX_OUTPUT_COMMON;
		data->REG_FAN_STEP_OUTPUT =
		  W83627EHF_REG_FAN_STEP_OUTPUT_COMMON;
	पूर्ण

	/* Setup input voltage scaling factors */
	अगर (sio_data->kind == w83627uhg)
		data->scale_in = scale_in_w83627uhg;
	अन्यथा
		data->scale_in = scale_in_common;

	/* Initialize the chip */
	w83627ehf_init_device(data, sio_data->kind);

	data->vrm = vid_which_vrm();

	err = superio_enter(sio_data->sioreg);
	अगर (err)
		जाओ निकास_release;

	/* Read VID value */
	अगर (sio_data->kind == w83667hg || sio_data->kind == w83667hg_b) अणु
		/*
		 * W83667HG has dअगरferent pins क्रम VID input and output, so
		 * we can get the VID input values directly at logical device D
		 * 0xe3.
		 */
		superio_select(sio_data->sioreg, W83667HG_LD_VID);
		data->vid = superio_inb(sio_data->sioreg, 0xe3);
		data->have_vid = true;
	पूर्ण अन्यथा अगर (sio_data->kind != w83627uhg) अणु
		superio_select(sio_data->sioreg, W83627EHF_LD_HWM);
		अगर (superio_inb(sio_data->sioreg, SIO_REG_VID_CTRL) & 0x80) अणु
			/*
			 * Set VID input sensibility अगर needed. In theory the
			 * BIOS should have set it, but in practice it's not
			 * always the हाल. We only करो it क्रम the W83627EHF/EHG
			 * because the W83627DHG is more complex in this
			 * respect.
			 */
			अगर (sio_data->kind == w83627ehf) अणु
				en_vrm10 = superio_inb(sio_data->sioreg,
						       SIO_REG_EN_VRM10);
				अगर ((en_vrm10 & 0x08) && data->vrm == 90) अणु
					dev_warn(dev,
						 "Setting VID input voltage to TTL\n");
					superio_outb(sio_data->sioreg,
						     SIO_REG_EN_VRM10,
						     en_vrm10 & ~0x08);
				पूर्ण अन्यथा अगर (!(en_vrm10 & 0x08)
					   && data->vrm == 100) अणु
					dev_warn(dev,
						 "Setting VID input voltage to VRM10\n");
					superio_outb(sio_data->sioreg,
						     SIO_REG_EN_VRM10,
						     en_vrm10 | 0x08);
				पूर्ण
			पूर्ण

			data->vid = superio_inb(sio_data->sioreg,
						SIO_REG_VID_DATA);
			अगर (sio_data->kind == w83627ehf) /* 6 VID pins only */
				data->vid &= 0x3f;
			data->have_vid = true;
		पूर्ण अन्यथा अणु
			dev_info(dev,
				 "VID pins in output mode, CPU VID not available\n");
		पूर्ण
	पूर्ण

	w83627ehf_check_fan_inमाला_दो(sio_data, data);

	superio_निकास(sio_data->sioreg);

	/* Read fan घड़ी भागiders immediately */
	w83627ehf_update_fan_भाग(data);

	/* Read pwm data to save original values */
	w83627ehf_update_pwm(data);
	क्रम (i = 0; i < data->pwm_num; i++)
		data->pwm_enable_orig[i] = data->pwm_enable[i];

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_info(&pdev->dev,
							 data->name,
							 data,
							 &w83627ehf_chip_info,
							 w83627ehf_groups);
	अगर (IS_ERR(hwmon_dev)) अणु
		err = PTR_ERR(hwmon_dev);
		जाओ निकास_release;
	पूर्ण

	वापस 0;

निकास_release:
	release_region(res->start, IOREGION_LENGTH);
निकास:
	वापस err;
पूर्ण

अटल पूर्णांक w83627ehf_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा w83627ehf_data *data = platक्रमm_get_drvdata(pdev);

	release_region(data->addr, IOREGION_LENGTH);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक w83627ehf_suspend(काष्ठा device *dev)
अणु
	काष्ठा w83627ehf_data *data = w83627ehf_update_device(dev);

	mutex_lock(&data->update_lock);
	data->vbat = w83627ehf_पढ़ो_value(data, W83627EHF_REG_VBAT);
	mutex_unlock(&data->update_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक w83627ehf_resume(काष्ठा device *dev)
अणु
	काष्ठा w83627ehf_data *data = dev_get_drvdata(dev);
	पूर्णांक i;

	mutex_lock(&data->update_lock);
	data->bank = 0xff;		/* Force initial bank selection */

	/* Restore limits */
	क्रम (i = 0; i < data->in_num; i++) अणु
		अगर ((i == 6) && data->in6_skip)
			जारी;

		w83627ehf_ग_लिखो_value(data, W83627EHF_REG_IN_MIN(i),
				      data->in_min[i]);
		w83627ehf_ग_लिखो_value(data, W83627EHF_REG_IN_MAX(i),
				      data->in_max[i]);
	पूर्ण

	क्रम (i = 0; i < 5; i++) अणु
		अगर (!(data->has_fan_min & (1 << i)))
			जारी;

		w83627ehf_ग_लिखो_value(data, W83627EHF_REG_FAN_MIN[i],
				      data->fan_min[i]);
	पूर्ण

	क्रम (i = 0; i < NUM_REG_TEMP; i++) अणु
		अगर (!(data->have_temp & (1 << i)))
			जारी;

		अगर (data->reg_temp_over[i])
			w83627ehf_ग_लिखो_temp(data, data->reg_temp_over[i],
					     data->temp_max[i]);
		अगर (data->reg_temp_hyst[i])
			w83627ehf_ग_लिखो_temp(data, data->reg_temp_hyst[i],
					     data->temp_max_hyst[i]);
		अगर (i > 2)
			जारी;
		अगर (data->have_temp_offset & (1 << i))
			w83627ehf_ग_लिखो_value(data,
					      W83627EHF_REG_TEMP_OFFSET[i],
					      data->temp_offset[i]);
	पूर्ण

	/* Restore other settings */
	w83627ehf_ग_लिखो_value(data, W83627EHF_REG_VBAT, data->vbat);

	/* Force re-पढ़ोing all values */
	data->valid = 0;
	mutex_unlock(&data->update_lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops w83627ehf_dev_pm_ops = अणु
	.suspend = w83627ehf_suspend,
	.resume = w83627ehf_resume,
	.मुक्तze = w83627ehf_suspend,
	.restore = w83627ehf_resume,
पूर्ण;

#घोषणा W83627EHF_DEV_PM_OPS	(&w83627ehf_dev_pm_ops)
#अन्यथा
#घोषणा W83627EHF_DEV_PM_OPS	शून्य
#पूर्ण_अगर /* CONFIG_PM */

अटल काष्ठा platक्रमm_driver w83627ehf_driver = अणु
	.driver = अणु
		.name	= DRVNAME,
		.pm	= W83627EHF_DEV_PM_OPS,
	पूर्ण,
	.probe		= w83627ehf_probe,
	.हटाओ		= w83627ehf_हटाओ,
पूर्ण;

/* w83627ehf_find() looks क्रम a '627 in the Super-I/O config space */
अटल पूर्णांक __init w83627ehf_find(पूर्णांक sioaddr, अचिन्हित लघु *addr,
				 काष्ठा w83627ehf_sio_data *sio_data)
अणु
	अटल स्थिर अक्षर sio_name_W83627EHF[] __initस्थिर = "W83627EHF";
	अटल स्थिर अक्षर sio_name_W83627EHG[] __initस्थिर = "W83627EHG";
	अटल स्थिर अक्षर sio_name_W83627DHG[] __initस्थिर = "W83627DHG";
	अटल स्थिर अक्षर sio_name_W83627DHG_P[] __initस्थिर = "W83627DHG-P";
	अटल स्थिर अक्षर sio_name_W83627UHG[] __initस्थिर = "W83627UHG";
	अटल स्थिर अक्षर sio_name_W83667HG[] __initस्थिर = "W83667HG";
	अटल स्थिर अक्षर sio_name_W83667HG_B[] __initस्थिर = "W83667HG-B";

	u16 val;
	स्थिर अक्षर *sio_name;
	पूर्णांक err;

	err = superio_enter(sioaddr);
	अगर (err)
		वापस err;

	अगर (क्रमce_id)
		val = क्रमce_id;
	अन्यथा
		val = (superio_inb(sioaddr, SIO_REG_DEVID) << 8)
		    | superio_inb(sioaddr, SIO_REG_DEVID + 1);
	चयन (val & SIO_ID_MASK) अणु
	हाल SIO_W83627EHF_ID:
		sio_data->kind = w83627ehf;
		sio_name = sio_name_W83627EHF;
		अवरोध;
	हाल SIO_W83627EHG_ID:
		sio_data->kind = w83627ehf;
		sio_name = sio_name_W83627EHG;
		अवरोध;
	हाल SIO_W83627DHG_ID:
		sio_data->kind = w83627dhg;
		sio_name = sio_name_W83627DHG;
		अवरोध;
	हाल SIO_W83627DHG_P_ID:
		sio_data->kind = w83627dhg_p;
		sio_name = sio_name_W83627DHG_P;
		अवरोध;
	हाल SIO_W83627UHG_ID:
		sio_data->kind = w83627uhg;
		sio_name = sio_name_W83627UHG;
		अवरोध;
	हाल SIO_W83667HG_ID:
		sio_data->kind = w83667hg;
		sio_name = sio_name_W83667HG;
		अवरोध;
	हाल SIO_W83667HG_B_ID:
		sio_data->kind = w83667hg_b;
		sio_name = sio_name_W83667HG_B;
		अवरोध;
	शेष:
		अगर (val != 0xffff)
			pr_debug("unsupported chip ID: 0x%04x\n", val);
		superio_निकास(sioaddr);
		वापस -ENODEV;
	पूर्ण

	/* We have a known chip, find the HWM I/O address */
	superio_select(sioaddr, W83627EHF_LD_HWM);
	val = (superio_inb(sioaddr, SIO_REG_ADDR) << 8)
	    | superio_inb(sioaddr, SIO_REG_ADDR + 1);
	*addr = val & IOREGION_ALIGNMENT;
	अगर (*addr == 0) अणु
		pr_err("Refusing to enable a Super-I/O device with a base I/O port 0\n");
		superio_निकास(sioaddr);
		वापस -ENODEV;
	पूर्ण

	/* Activate logical device अगर needed */
	val = superio_inb(sioaddr, SIO_REG_ENABLE);
	अगर (!(val & 0x01)) अणु
		pr_warn("Forcibly enabling Super-I/O. Sensor is probably unusable.\n");
		superio_outb(sioaddr, SIO_REG_ENABLE, val | 0x01);
	पूर्ण

	superio_निकास(sioaddr);
	pr_info("Found %s chip at %#x\n", sio_name, *addr);
	sio_data->sioreg = sioaddr;

	वापस 0;
पूर्ण

/*
 * when Super-I/O functions move to a separate file, the Super-I/O
 * bus will manage the lअगरeसमय of the device and this module will only keep
 * track of the w83627ehf driver. But since we platक्रमm_device_alloc(), we
 * must keep track of the device
 */
अटल काष्ठा platक्रमm_device *pdev;

अटल पूर्णांक __init sensors_w83627ehf_init(व्योम)
अणु
	पूर्णांक err;
	अचिन्हित लघु address;
	काष्ठा resource res;
	काष्ठा w83627ehf_sio_data sio_data;

	/*
	 * initialize sio_data->kind and sio_data->sioreg.
	 *
	 * when Super-I/O functions move to a separate file, the Super-I/O
	 * driver will probe 0x2e and 0x4e and स्वतः-detect the presence of a
	 * w83627ehf hardware monitor, and call probe()
	 */
	अगर (w83627ehf_find(0x2e, &address, &sio_data) &&
	    w83627ehf_find(0x4e, &address, &sio_data))
		वापस -ENODEV;

	err = platक्रमm_driver_रेजिस्टर(&w83627ehf_driver);
	अगर (err)
		जाओ निकास;

	pdev = platक्रमm_device_alloc(DRVNAME, address);
	अगर (!pdev) अणु
		err = -ENOMEM;
		pr_err("Device allocation failed\n");
		जाओ निकास_unरेजिस्टर;
	पूर्ण

	err = platक्रमm_device_add_data(pdev, &sio_data,
				       माप(काष्ठा w83627ehf_sio_data));
	अगर (err) अणु
		pr_err("Platform data allocation failed\n");
		जाओ निकास_device_put;
	पूर्ण

	स_रखो(&res, 0, माप(res));
	res.name = DRVNAME;
	res.start = address + IOREGION_OFFSET;
	res.end = address + IOREGION_OFFSET + IOREGION_LENGTH - 1;
	res.flags = IORESOURCE_IO;

	err = acpi_check_resource_conflict(&res);
	अगर (err)
		जाओ निकास_device_put;

	err = platक्रमm_device_add_resources(pdev, &res, 1);
	अगर (err) अणु
		pr_err("Device resource addition failed (%d)\n", err);
		जाओ निकास_device_put;
	पूर्ण

	/* platक्रमm_device_add calls probe() */
	err = platक्रमm_device_add(pdev);
	अगर (err) अणु
		pr_err("Device addition failed (%d)\n", err);
		जाओ निकास_device_put;
	पूर्ण

	वापस 0;

निकास_device_put:
	platक्रमm_device_put(pdev);
निकास_unरेजिस्टर:
	platक्रमm_driver_unरेजिस्टर(&w83627ehf_driver);
निकास:
	वापस err;
पूर्ण

अटल व्योम __निकास sensors_w83627ehf_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(pdev);
	platक्रमm_driver_unरेजिस्टर(&w83627ehf_driver);
पूर्ण

MODULE_AUTHOR("Jean Delvare <jdelvare@suse.de>");
MODULE_DESCRIPTION("W83627EHF driver");
MODULE_LICENSE("GPL");

module_init(sensors_w83627ehf_init);
module_निकास(sensors_w83627ehf_निकास);
