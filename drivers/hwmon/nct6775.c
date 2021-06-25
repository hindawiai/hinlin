<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * nct6775 - Driver क्रम the hardware monitoring functionality of
 *	       Nuvoton NCT677x Super-I/O chips
 *
 * Copyright (C) 2012  Guenter Roeck <linux@roeck-us.net>
 *
 * Derived from w83627ehf driver
 * Copyright (C) 2005-2012  Jean Delvare <jdelvare@suse.de>
 * Copyright (C) 2006  Yuan Mu (Winbond),
 *		       Ruकरोlf Marek <r.marek@assembler.cz>
 *		       David Hubbard <david.c.hubbard@gmail.com>
 *		       Daniel J Blueman <daniel.blueman@gmail.com>
 * Copyright (C) 2010  Sheng-Yuan Huang (Nuvoton) (PS00)
 *
 * Shamelessly ripped from the w83627hf driver
 * Copyright (C) 2003  Mark Studebaker
 *
 * Supports the following chips:
 *
 * Chip        #vin    #fan    #pwm    #temp  chip IDs       man ID
 * nct6106d     9      3       3       6+3    0xc450 0xc1    0x5ca3
 * nct6116d     9      5       5       3+3    0xd280 0xc1    0x5ca3
 * nct6775f     9      4       3       6+3    0xb470 0xc1    0x5ca3
 * nct6776f     9      5       3       6+3    0xc330 0xc1    0x5ca3
 * nct6779d    15      5       5       2+6    0xc560 0xc1    0x5ca3
 * nct6791d    15      6       6       2+6    0xc800 0xc1    0x5ca3
 * nct6792d    15      6       6       2+6    0xc910 0xc1    0x5ca3
 * nct6793d    15      6       6       2+6    0xd120 0xc1    0x5ca3
 * nct6795d    14      6       6       2+6    0xd350 0xc1    0x5ca3
 * nct6796d    14      7       7       2+6    0xd420 0xc1    0x5ca3
 * nct6797d    14      7       7       2+6    0xd450 0xc1    0x5ca3
 *                                           (0xd451)
 * nct6798d    14      7       7       2+6    0xd428 0xc1    0x5ca3
 *                                           (0xd429)
 *
 * #temp lists the number of monitored temperature sources (first value) plus
 * the number of directly connectable temperature sensors (second value).
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
#समावेश <linux/bitops.h>
#समावेश <linux/dmi.h>
#समावेश <linux/पन.स>
#समावेश <linux/nospec.h>
#समावेश "lm75.h"

#घोषणा USE_ALTERNATE

क्रमागत kinds अणु nct6106, nct6116, nct6775, nct6776, nct6779, nct6791, nct6792,
	     nct6793, nct6795, nct6796, nct6797, nct6798 पूर्ण;

/* used to set data->name = nct6775_device_names[data->sio_kind] */
अटल स्थिर अक्षर * स्थिर nct6775_device_names[] = अणु
	"nct6106",
	"nct6116",
	"nct6775",
	"nct6776",
	"nct6779",
	"nct6791",
	"nct6792",
	"nct6793",
	"nct6795",
	"nct6796",
	"nct6797",
	"nct6798",
पूर्ण;

अटल स्थिर अक्षर * स्थिर nct6775_sio_names[] __initस्थिर = अणु
	"NCT6106D",
	"NCT6116D",
	"NCT6775F",
	"NCT6776D/F",
	"NCT6779D",
	"NCT6791D",
	"NCT6792D",
	"NCT6793D",
	"NCT6795D",
	"NCT6796D",
	"NCT6797D",
	"NCT6798D",
पूर्ण;

अटल अचिन्हित लघु क्रमce_id;
module_param(क्रमce_id, uलघु, 0);
MODULE_PARM_DESC(क्रमce_id, "Override the detected device ID");

अटल अचिन्हित लघु fan_debounce;
module_param(fan_debounce, uलघु, 0);
MODULE_PARM_DESC(fan_debounce, "Enable debouncing for fan RPM signal");

#घोषणा DRVNAME "nct6775"

/*
 * Super-I/O स्थिरants and functions
 */

#घोषणा NCT6775_LD_ACPI		0x0a
#घोषणा NCT6775_LD_HWM		0x0b
#घोषणा NCT6775_LD_VID		0x0d
#घोषणा NCT6775_LD_12		0x12

#घोषणा SIO_REG_LDSEL		0x07	/* Logical device select */
#घोषणा SIO_REG_DEVID		0x20	/* Device ID (2 bytes) */
#घोषणा SIO_REG_ENABLE		0x30	/* Logical device enable */
#घोषणा SIO_REG_ADDR		0x60	/* Logical device address (2 bytes) */

#घोषणा SIO_NCT6106_ID		0xc450
#घोषणा SIO_NCT6116_ID		0xd280
#घोषणा SIO_NCT6775_ID		0xb470
#घोषणा SIO_NCT6776_ID		0xc330
#घोषणा SIO_NCT6779_ID		0xc560
#घोषणा SIO_NCT6791_ID		0xc800
#घोषणा SIO_NCT6792_ID		0xc910
#घोषणा SIO_NCT6793_ID		0xd120
#घोषणा SIO_NCT6795_ID		0xd350
#घोषणा SIO_NCT6796_ID		0xd420
#घोषणा SIO_NCT6797_ID		0xd450
#घोषणा SIO_NCT6798_ID		0xd428
#घोषणा SIO_ID_MASK		0xFFF8

क्रमागत pwm_enable अणु off, manual, thermal_cruise, speed_cruise, sf3, sf4 पूर्ण;

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
#घोषणा IOREGION_OFFSET		5
#घोषणा IOREGION_LENGTH		2
#घोषणा ADDR_REG_OFFSET		0
#घोषणा DATA_REG_OFFSET		1

#घोषणा NCT6775_REG_BANK	0x4E
#घोषणा NCT6775_REG_CONFIG	0x40

/*
 * Not currently used:
 * REG_MAN_ID has the value 0x5ca3 क्रम all supported chips.
 * REG_CHIP_ID == 0x88/0xa1/0xc1 depending on chip model.
 * REG_MAN_ID is at port 0x4f
 * REG_CHIP_ID is at port 0x58
 */

#घोषणा NUM_TEMP	10	/* Max number of temp attribute sets w/ limits*/
#घोषणा NUM_TEMP_FIXED	6	/* Max number of fixed temp attribute sets */

#घोषणा NUM_REG_ALARM	7	/* Max number of alarm रेजिस्टरs */
#घोषणा NUM_REG_BEEP	5	/* Max number of beep रेजिस्टरs */

#घोषणा NUM_FAN		7

/* Common and NCT6775 specअगरic data */

/* Voltage min/max रेजिस्टरs क्रम nr=7..14 are in bank 5 */

अटल स्थिर u16 NCT6775_REG_IN_MAX[] = अणु
	0x2b, 0x2d, 0x2f, 0x31, 0x33, 0x35, 0x37, 0x554, 0x556, 0x558, 0x55a,
	0x55c, 0x55e, 0x560, 0x562 पूर्ण;
अटल स्थिर u16 NCT6775_REG_IN_MIN[] = अणु
	0x2c, 0x2e, 0x30, 0x32, 0x34, 0x36, 0x38, 0x555, 0x557, 0x559, 0x55b,
	0x55d, 0x55f, 0x561, 0x563 पूर्ण;
अटल स्थिर u16 NCT6775_REG_IN[] = अणु
	0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x550, 0x551, 0x552
पूर्ण;

#घोषणा NCT6775_REG_VBAT		0x5D
#घोषणा NCT6775_REG_DIODE		0x5E
#घोषणा NCT6775_DIODE_MASK		0x02

#घोषणा NCT6775_REG_FANDIV1		0x506
#घोषणा NCT6775_REG_FANDIV2		0x507

#घोषणा NCT6775_REG_CR_FAN_DEBOUNCE	0xf0

अटल स्थिर u16 NCT6775_REG_ALARM[NUM_REG_ALARM] = अणु 0x459, 0x45A, 0x45B पूर्ण;

/* 0..15 voltages, 16..23 fans, 24..29 temperatures, 30..31 पूर्णांकrusion */

अटल स्थिर s8 NCT6775_ALARM_BITS[] = अणु
	0, 1, 2, 3, 8, 21, 20, 16,	/* in0.. in7 */
	17, -1, -1, -1, -1, -1, -1,	/* in8..in14 */
	-1,				/* unused */
	6, 7, 11, -1, -1,		/* fan1..fan5 */
	-1, -1, -1,			/* unused */
	4, 5, 13, -1, -1, -1,		/* temp1..temp6 */
	12, -1 पूर्ण;			/* पूर्णांकrusion0, पूर्णांकrusion1 */

#घोषणा FAN_ALARM_BASE		16
#घोषणा TEMP_ALARM_BASE		24
#घोषणा INTRUSION_ALARM_BASE	30

अटल स्थिर u16 NCT6775_REG_BEEP[NUM_REG_BEEP] = अणु 0x56, 0x57, 0x453, 0x4e पूर्ण;

/*
 * 0..14 voltages, 15 global beep enable, 16..23 fans, 24..29 temperatures,
 * 30..31 पूर्णांकrusion
 */
अटल स्थिर s8 NCT6775_BEEP_BITS[] = अणु
	0, 1, 2, 3, 8, 9, 10, 16,	/* in0.. in7 */
	17, -1, -1, -1, -1, -1, -1,	/* in8..in14 */
	21,				/* global beep enable */
	6, 7, 11, 28, -1,		/* fan1..fan5 */
	-1, -1, -1,			/* unused */
	4, 5, 13, -1, -1, -1,		/* temp1..temp6 */
	12, -1 पूर्ण;			/* पूर्णांकrusion0, पूर्णांकrusion1 */

#घोषणा BEEP_ENABLE_BASE		15

अटल स्थिर u8 NCT6775_REG_CR_CASEOPEN_CLR[] = अणु 0xe6, 0xee पूर्ण;
अटल स्थिर u8 NCT6775_CR_CASEOPEN_CLR_MASK[] = अणु 0x20, 0x01 पूर्ण;

/* DC or PWM output fan configuration */
अटल स्थिर u8 NCT6775_REG_PWM_MODE[] = अणु 0x04, 0x04, 0x12 पूर्ण;
अटल स्थिर u8 NCT6775_PWM_MODE_MASK[] = अणु 0x01, 0x02, 0x01 पूर्ण;

/* Advanced Fan control, some values are common क्रम all fans */

अटल स्थिर u16 NCT6775_REG_TARGET[] = अणु
	0x101, 0x201, 0x301, 0x801, 0x901, 0xa01, 0xb01 पूर्ण;
अटल स्थिर u16 NCT6775_REG_FAN_MODE[] = अणु
	0x102, 0x202, 0x302, 0x802, 0x902, 0xa02, 0xb02 पूर्ण;
अटल स्थिर u16 NCT6775_REG_FAN_STEP_DOWN_TIME[] = अणु
	0x103, 0x203, 0x303, 0x803, 0x903, 0xa03, 0xb03 पूर्ण;
अटल स्थिर u16 NCT6775_REG_FAN_STEP_UP_TIME[] = अणु
	0x104, 0x204, 0x304, 0x804, 0x904, 0xa04, 0xb04 पूर्ण;
अटल स्थिर u16 NCT6775_REG_FAN_STOP_OUTPUT[] = अणु
	0x105, 0x205, 0x305, 0x805, 0x905, 0xa05, 0xb05 पूर्ण;
अटल स्थिर u16 NCT6775_REG_FAN_START_OUTPUT[] = अणु
	0x106, 0x206, 0x306, 0x806, 0x906, 0xa06, 0xb06 पूर्ण;
अटल स्थिर u16 NCT6775_REG_FAN_MAX_OUTPUT[] = अणु 0x10a, 0x20a, 0x30a पूर्ण;
अटल स्थिर u16 NCT6775_REG_FAN_STEP_OUTPUT[] = अणु 0x10b, 0x20b, 0x30b पूर्ण;

अटल स्थिर u16 NCT6775_REG_FAN_STOP_TIME[] = अणु
	0x107, 0x207, 0x307, 0x807, 0x907, 0xa07, 0xb07 पूर्ण;
अटल स्थिर u16 NCT6775_REG_PWM[] = अणु
	0x109, 0x209, 0x309, 0x809, 0x909, 0xa09, 0xb09 पूर्ण;
अटल स्थिर u16 NCT6775_REG_PWM_READ[] = अणु
	0x01, 0x03, 0x11, 0x13, 0x15, 0xa09, 0xb09 पूर्ण;

अटल स्थिर u16 NCT6775_REG_FAN[] = अणु 0x630, 0x632, 0x634, 0x636, 0x638 पूर्ण;
अटल स्थिर u16 NCT6775_REG_FAN_MIN[] = अणु 0x3b, 0x3c, 0x3d पूर्ण;
अटल स्थिर u16 NCT6775_REG_FAN_PULSES[NUM_FAN] = अणु
	0x641, 0x642, 0x643, 0x644 पूर्ण;
अटल स्थिर u16 NCT6775_FAN_PULSE_SHIFT[NUM_FAN] = अणु पूर्ण;

अटल स्थिर u16 NCT6775_REG_TEMP[] = अणु
	0x27, 0x150, 0x250, 0x62b, 0x62c, 0x62d पूर्ण;

अटल स्थिर u16 NCT6775_REG_TEMP_MON[] = अणु 0x73, 0x75, 0x77 पूर्ण;

अटल स्थिर u16 NCT6775_REG_TEMP_CONFIG[ARRAY_SIZE(NCT6775_REG_TEMP)] = अणु
	0, 0x152, 0x252, 0x628, 0x629, 0x62A पूर्ण;
अटल स्थिर u16 NCT6775_REG_TEMP_HYST[ARRAY_SIZE(NCT6775_REG_TEMP)] = अणु
	0x3a, 0x153, 0x253, 0x673, 0x678, 0x67D पूर्ण;
अटल स्थिर u16 NCT6775_REG_TEMP_OVER[ARRAY_SIZE(NCT6775_REG_TEMP)] = अणु
	0x39, 0x155, 0x255, 0x672, 0x677, 0x67C पूर्ण;

अटल स्थिर u16 NCT6775_REG_TEMP_SOURCE[ARRAY_SIZE(NCT6775_REG_TEMP)] = अणु
	0x621, 0x622, 0x623, 0x624, 0x625, 0x626 पूर्ण;

अटल स्थिर u16 NCT6775_REG_TEMP_SEL[] = अणु
	0x100, 0x200, 0x300, 0x800, 0x900, 0xa00, 0xb00 पूर्ण;

अटल स्थिर u16 NCT6775_REG_WEIGHT_TEMP_SEL[] = अणु
	0x139, 0x239, 0x339, 0x839, 0x939, 0xa39 पूर्ण;
अटल स्थिर u16 NCT6775_REG_WEIGHT_TEMP_STEP[] = अणु
	0x13a, 0x23a, 0x33a, 0x83a, 0x93a, 0xa3a पूर्ण;
अटल स्थिर u16 NCT6775_REG_WEIGHT_TEMP_STEP_TOL[] = अणु
	0x13b, 0x23b, 0x33b, 0x83b, 0x93b, 0xa3b पूर्ण;
अटल स्थिर u16 NCT6775_REG_WEIGHT_DUTY_STEP[] = अणु
	0x13c, 0x23c, 0x33c, 0x83c, 0x93c, 0xa3c पूर्ण;
अटल स्थिर u16 NCT6775_REG_WEIGHT_TEMP_BASE[] = अणु
	0x13d, 0x23d, 0x33d, 0x83d, 0x93d, 0xa3d पूर्ण;

अटल स्थिर u16 NCT6775_REG_TEMP_OFFSET[] = अणु 0x454, 0x455, 0x456 पूर्ण;

अटल स्थिर u16 NCT6775_REG_AUTO_TEMP[] = अणु
	0x121, 0x221, 0x321, 0x821, 0x921, 0xa21, 0xb21 पूर्ण;
अटल स्थिर u16 NCT6775_REG_AUTO_PWM[] = अणु
	0x127, 0x227, 0x327, 0x827, 0x927, 0xa27, 0xb27 पूर्ण;

#घोषणा NCT6775_AUTO_TEMP(data, nr, p)	((data)->REG_AUTO_TEMP[nr] + (p))
#घोषणा NCT6775_AUTO_PWM(data, nr, p)	((data)->REG_AUTO_PWM[nr] + (p))

अटल स्थिर u16 NCT6775_REG_CRITICAL_ENAB[] = अणु 0x134, 0x234, 0x334 पूर्ण;

अटल स्थिर u16 NCT6775_REG_CRITICAL_TEMP[] = अणु
	0x135, 0x235, 0x335, 0x835, 0x935, 0xa35, 0xb35 पूर्ण;
अटल स्थिर u16 NCT6775_REG_CRITICAL_TEMP_TOLERANCE[] = अणु
	0x138, 0x238, 0x338, 0x838, 0x938, 0xa38, 0xb38 पूर्ण;

अटल स्थिर अक्षर *स्थिर nct6775_temp_label[] = अणु
	"",
	"SYSTIN",
	"CPUTIN",
	"AUXTIN",
	"AMD SB-TSI",
	"PECI Agent 0",
	"PECI Agent 1",
	"PECI Agent 2",
	"PECI Agent 3",
	"PECI Agent 4",
	"PECI Agent 5",
	"PECI Agent 6",
	"PECI Agent 7",
	"PCH_CHIP_CPU_MAX_TEMP",
	"PCH_CHIP_TEMP",
	"PCH_CPU_TEMP",
	"PCH_MCH_TEMP",
	"PCH_DIM0_TEMP",
	"PCH_DIM1_TEMP",
	"PCH_DIM2_TEMP",
	"PCH_DIM3_TEMP"
पूर्ण;

#घोषणा NCT6775_TEMP_MASK	0x001ffffe
#घोषणा NCT6775_VIRT_TEMP_MASK	0x00000000

अटल स्थिर u16 NCT6775_REG_TEMP_ALTERNATE[32] = अणु
	[13] = 0x661,
	[14] = 0x662,
	[15] = 0x664,
पूर्ण;

अटल स्थिर u16 NCT6775_REG_TEMP_CRIT[32] = अणु
	[4] = 0xa00,
	[5] = 0xa01,
	[6] = 0xa02,
	[7] = 0xa03,
	[8] = 0xa04,
	[9] = 0xa05,
	[10] = 0xa06,
	[11] = 0xa07
पूर्ण;

/* NCT6776 specअगरic data */

/* STEP_UP_TIME and STEP_DOWN_TIME regs are swapped क्रम all chips but NCT6775 */
#घोषणा NCT6776_REG_FAN_STEP_UP_TIME NCT6775_REG_FAN_STEP_DOWN_TIME
#घोषणा NCT6776_REG_FAN_STEP_DOWN_TIME NCT6775_REG_FAN_STEP_UP_TIME

अटल स्थिर s8 NCT6776_ALARM_BITS[] = अणु
	0, 1, 2, 3, 8, 21, 20, 16,	/* in0.. in7 */
	17, -1, -1, -1, -1, -1, -1,	/* in8..in14 */
	-1,				/* unused */
	6, 7, 11, 10, 23,		/* fan1..fan5 */
	-1, -1, -1,			/* unused */
	4, 5, 13, -1, -1, -1,		/* temp1..temp6 */
	12, 9 पूर्ण;			/* पूर्णांकrusion0, पूर्णांकrusion1 */

अटल स्थिर u16 NCT6776_REG_BEEP[NUM_REG_BEEP] = अणु 0xb2, 0xb3, 0xb4, 0xb5 पूर्ण;

अटल स्थिर s8 NCT6776_BEEP_BITS[] = अणु
	0, 1, 2, 3, 4, 5, 6, 7,		/* in0.. in7 */
	8, -1, -1, -1, -1, -1, -1,	/* in8..in14 */
	24,				/* global beep enable */
	25, 26, 27, 28, 29,		/* fan1..fan5 */
	-1, -1, -1,			/* unused */
	16, 17, 18, 19, 20, 21,		/* temp1..temp6 */
	30, 31 पूर्ण;			/* पूर्णांकrusion0, पूर्णांकrusion1 */

अटल स्थिर u16 NCT6776_REG_TOLERANCE_H[] = अणु
	0x10c, 0x20c, 0x30c, 0x80c, 0x90c, 0xa0c, 0xb0c पूर्ण;

अटल स्थिर u8 NCT6776_REG_PWM_MODE[] = अणु 0x04, 0, 0, 0, 0, 0 पूर्ण;
अटल स्थिर u8 NCT6776_PWM_MODE_MASK[] = अणु 0x01, 0, 0, 0, 0, 0 पूर्ण;

अटल स्थिर u16 NCT6776_REG_FAN_MIN[] = अणु
	0x63a, 0x63c, 0x63e, 0x640, 0x642, 0x64a, 0x64c पूर्ण;
अटल स्थिर u16 NCT6776_REG_FAN_PULSES[NUM_FAN] = अणु
	0x644, 0x645, 0x646, 0x647, 0x648, 0x649 पूर्ण;

अटल स्थिर u16 NCT6776_REG_WEIGHT_DUTY_BASE[] = अणु
	0x13e, 0x23e, 0x33e, 0x83e, 0x93e, 0xa3e पूर्ण;

अटल स्थिर u16 NCT6776_REG_TEMP_CONFIG[ARRAY_SIZE(NCT6775_REG_TEMP)] = अणु
	0x18, 0x152, 0x252, 0x628, 0x629, 0x62A पूर्ण;

अटल स्थिर अक्षर *स्थिर nct6776_temp_label[] = अणु
	"",
	"SYSTIN",
	"CPUTIN",
	"AUXTIN",
	"SMBUSMASTER 0",
	"SMBUSMASTER 1",
	"SMBUSMASTER 2",
	"SMBUSMASTER 3",
	"SMBUSMASTER 4",
	"SMBUSMASTER 5",
	"SMBUSMASTER 6",
	"SMBUSMASTER 7",
	"PECI Agent 0",
	"PECI Agent 1",
	"PCH_CHIP_CPU_MAX_TEMP",
	"PCH_CHIP_TEMP",
	"PCH_CPU_TEMP",
	"PCH_MCH_TEMP",
	"PCH_DIM0_TEMP",
	"PCH_DIM1_TEMP",
	"PCH_DIM2_TEMP",
	"PCH_DIM3_TEMP",
	"BYTE_TEMP"
पूर्ण;

#घोषणा NCT6776_TEMP_MASK	0x007ffffe
#घोषणा NCT6776_VIRT_TEMP_MASK	0x00000000

अटल स्थिर u16 NCT6776_REG_TEMP_ALTERNATE[32] = अणु
	[14] = 0x401,
	[15] = 0x402,
	[16] = 0x404,
पूर्ण;

अटल स्थिर u16 NCT6776_REG_TEMP_CRIT[32] = अणु
	[11] = 0x709,
	[12] = 0x70a,
पूर्ण;

/* NCT6779 specअगरic data */

अटल स्थिर u16 NCT6779_REG_IN[] = अणु
	0x480, 0x481, 0x482, 0x483, 0x484, 0x485, 0x486, 0x487,
	0x488, 0x489, 0x48a, 0x48b, 0x48c, 0x48d, 0x48e पूर्ण;

अटल स्थिर u16 NCT6779_REG_ALARM[NUM_REG_ALARM] = अणु
	0x459, 0x45A, 0x45B, 0x568 पूर्ण;

अटल स्थिर s8 NCT6779_ALARM_BITS[] = अणु
	0, 1, 2, 3, 8, 21, 20, 16,	/* in0.. in7 */
	17, 24, 25, 26, 27, 28, 29,	/* in8..in14 */
	-1,				/* unused */
	6, 7, 11, 10, 23,		/* fan1..fan5 */
	-1, -1, -1,			/* unused */
	4, 5, 13, -1, -1, -1,		/* temp1..temp6 */
	12, 9 पूर्ण;			/* पूर्णांकrusion0, पूर्णांकrusion1 */

अटल स्थिर s8 NCT6779_BEEP_BITS[] = अणु
	0, 1, 2, 3, 4, 5, 6, 7,		/* in0.. in7 */
	8, 9, 10, 11, 12, 13, 14,	/* in8..in14 */
	24,				/* global beep enable */
	25, 26, 27, 28, 29,		/* fan1..fan5 */
	-1, -1, -1,			/* unused */
	16, 17, -1, -1, -1, -1,		/* temp1..temp6 */
	30, 31 पूर्ण;			/* पूर्णांकrusion0, पूर्णांकrusion1 */

अटल स्थिर u16 NCT6779_REG_FAN[] = अणु
	0x4c0, 0x4c2, 0x4c4, 0x4c6, 0x4c8, 0x4ca, 0x4ce पूर्ण;
अटल स्थिर u16 NCT6779_REG_FAN_PULSES[NUM_FAN] = अणु
	0x644, 0x645, 0x646, 0x647, 0x648, 0x649, 0x64f पूर्ण;

अटल स्थिर u16 NCT6779_REG_CRITICAL_PWM_ENABLE[] = अणु
	0x136, 0x236, 0x336, 0x836, 0x936, 0xa36, 0xb36 पूर्ण;
#घोषणा NCT6779_CRITICAL_PWM_ENABLE_MASK	0x01
अटल स्थिर u16 NCT6779_REG_CRITICAL_PWM[] = अणु
	0x137, 0x237, 0x337, 0x837, 0x937, 0xa37, 0xb37 पूर्ण;

अटल स्थिर u16 NCT6779_REG_TEMP[] = अणु 0x27, 0x150 पूर्ण;
अटल स्थिर u16 NCT6779_REG_TEMP_MON[] = अणु 0x73, 0x75, 0x77, 0x79, 0x7b पूर्ण;
अटल स्थिर u16 NCT6779_REG_TEMP_CONFIG[ARRAY_SIZE(NCT6779_REG_TEMP)] = अणु
	0x18, 0x152 पूर्ण;
अटल स्थिर u16 NCT6779_REG_TEMP_HYST[ARRAY_SIZE(NCT6779_REG_TEMP)] = अणु
	0x3a, 0x153 पूर्ण;
अटल स्थिर u16 NCT6779_REG_TEMP_OVER[ARRAY_SIZE(NCT6779_REG_TEMP)] = अणु
	0x39, 0x155 पूर्ण;

अटल स्थिर u16 NCT6779_REG_TEMP_OFFSET[] = अणु
	0x454, 0x455, 0x456, 0x44a, 0x44b, 0x44c पूर्ण;

अटल स्थिर अक्षर *स्थिर nct6779_temp_label[] = अणु
	"",
	"SYSTIN",
	"CPUTIN",
	"AUXTIN0",
	"AUXTIN1",
	"AUXTIN2",
	"AUXTIN3",
	"",
	"SMBUSMASTER 0",
	"SMBUSMASTER 1",
	"SMBUSMASTER 2",
	"SMBUSMASTER 3",
	"SMBUSMASTER 4",
	"SMBUSMASTER 5",
	"SMBUSMASTER 6",
	"SMBUSMASTER 7",
	"PECI Agent 0",
	"PECI Agent 1",
	"PCH_CHIP_CPU_MAX_TEMP",
	"PCH_CHIP_TEMP",
	"PCH_CPU_TEMP",
	"PCH_MCH_TEMP",
	"PCH_DIM0_TEMP",
	"PCH_DIM1_TEMP",
	"PCH_DIM2_TEMP",
	"PCH_DIM3_TEMP",
	"BYTE_TEMP",
	"",
	"",
	"",
	"",
	"Virtual_TEMP"
पूर्ण;

#घोषणा NCT6779_TEMP_MASK	0x07ffff7e
#घोषणा NCT6779_VIRT_TEMP_MASK	0x00000000
#घोषणा NCT6791_TEMP_MASK	0x87ffff7e
#घोषणा NCT6791_VIRT_TEMP_MASK	0x80000000

अटल स्थिर u16 NCT6779_REG_TEMP_ALTERNATE[32]
	= अणु 0x490, 0x491, 0x492, 0x493, 0x494, 0x495, 0, 0,
	    0, 0, 0, 0, 0, 0, 0, 0,
	    0, 0x400, 0x401, 0x402, 0x404, 0x405, 0x406, 0x407,
	    0x408, 0 पूर्ण;

अटल स्थिर u16 NCT6779_REG_TEMP_CRIT[32] = अणु
	[15] = 0x709,
	[16] = 0x70a,
पूर्ण;

/* NCT6791 specअगरic data */

#घोषणा NCT6791_REG_HM_IO_SPACE_LOCK_ENABLE	0x28

अटल स्थिर u16 NCT6791_REG_WEIGHT_TEMP_SEL[NUM_FAN] = अणु 0, 0x239 पूर्ण;
अटल स्थिर u16 NCT6791_REG_WEIGHT_TEMP_STEP[NUM_FAN] = अणु 0, 0x23a पूर्ण;
अटल स्थिर u16 NCT6791_REG_WEIGHT_TEMP_STEP_TOL[NUM_FAN] = अणु 0, 0x23b पूर्ण;
अटल स्थिर u16 NCT6791_REG_WEIGHT_DUTY_STEP[NUM_FAN] = अणु 0, 0x23c पूर्ण;
अटल स्थिर u16 NCT6791_REG_WEIGHT_TEMP_BASE[NUM_FAN] = अणु 0, 0x23d पूर्ण;
अटल स्थिर u16 NCT6791_REG_WEIGHT_DUTY_BASE[NUM_FAN] = अणु 0, 0x23e पूर्ण;

अटल स्थिर u16 NCT6791_REG_ALARM[NUM_REG_ALARM] = अणु
	0x459, 0x45A, 0x45B, 0x568, 0x45D पूर्ण;

अटल स्थिर s8 NCT6791_ALARM_BITS[] = अणु
	0, 1, 2, 3, 8, 21, 20, 16,	/* in0.. in7 */
	17, 24, 25, 26, 27, 28, 29,	/* in8..in14 */
	-1,				/* unused */
	6, 7, 11, 10, 23, 33,		/* fan1..fan6 */
	-1, -1,				/* unused */
	4, 5, 13, -1, -1, -1,		/* temp1..temp6 */
	12, 9 पूर्ण;			/* पूर्णांकrusion0, पूर्णांकrusion1 */

/* NCT6792/NCT6793 specअगरic data */

अटल स्थिर u16 NCT6792_REG_TEMP_MON[] = अणु
	0x73, 0x75, 0x77, 0x79, 0x7b, 0x7d पूर्ण;
अटल स्थिर u16 NCT6792_REG_BEEP[NUM_REG_BEEP] = अणु
	0xb2, 0xb3, 0xb4, 0xb5, 0xbf पूर्ण;

अटल स्थिर अक्षर *स्थिर nct6792_temp_label[] = अणु
	"",
	"SYSTIN",
	"CPUTIN",
	"AUXTIN0",
	"AUXTIN1",
	"AUXTIN2",
	"AUXTIN3",
	"",
	"SMBUSMASTER 0",
	"SMBUSMASTER 1",
	"SMBUSMASTER 2",
	"SMBUSMASTER 3",
	"SMBUSMASTER 4",
	"SMBUSMASTER 5",
	"SMBUSMASTER 6",
	"SMBUSMASTER 7",
	"PECI Agent 0",
	"PECI Agent 1",
	"PCH_CHIP_CPU_MAX_TEMP",
	"PCH_CHIP_TEMP",
	"PCH_CPU_TEMP",
	"PCH_MCH_TEMP",
	"PCH_DIM0_TEMP",
	"PCH_DIM1_TEMP",
	"PCH_DIM2_TEMP",
	"PCH_DIM3_TEMP",
	"BYTE_TEMP",
	"PECI Agent 0 Calibration",
	"PECI Agent 1 Calibration",
	"",
	"",
	"Virtual_TEMP"
पूर्ण;

#घोषणा NCT6792_TEMP_MASK	0x9fffff7e
#घोषणा NCT6792_VIRT_TEMP_MASK	0x80000000

अटल स्थिर अक्षर *स्थिर nct6793_temp_label[] = अणु
	"",
	"SYSTIN",
	"CPUTIN",
	"AUXTIN0",
	"AUXTIN1",
	"AUXTIN2",
	"AUXTIN3",
	"",
	"SMBUSMASTER 0",
	"SMBUSMASTER 1",
	"",
	"",
	"",
	"",
	"",
	"",
	"PECI Agent 0",
	"PECI Agent 1",
	"PCH_CHIP_CPU_MAX_TEMP",
	"PCH_CHIP_TEMP",
	"PCH_CPU_TEMP",
	"PCH_MCH_TEMP",
	"Agent0 Dimm0 ",
	"Agent0 Dimm1",
	"Agent1 Dimm0",
	"Agent1 Dimm1",
	"BYTE_TEMP0",
	"BYTE_TEMP1",
	"PECI Agent 0 Calibration",
	"PECI Agent 1 Calibration",
	"",
	"Virtual_TEMP"
पूर्ण;

#घोषणा NCT6793_TEMP_MASK	0xbfff037e
#घोषणा NCT6793_VIRT_TEMP_MASK	0x80000000

अटल स्थिर अक्षर *स्थिर nct6795_temp_label[] = अणु
	"",
	"SYSTIN",
	"CPUTIN",
	"AUXTIN0",
	"AUXTIN1",
	"AUXTIN2",
	"AUXTIN3",
	"",
	"SMBUSMASTER 0",
	"SMBUSMASTER 1",
	"SMBUSMASTER 2",
	"SMBUSMASTER 3",
	"SMBUSMASTER 4",
	"SMBUSMASTER 5",
	"SMBUSMASTER 6",
	"SMBUSMASTER 7",
	"PECI Agent 0",
	"PECI Agent 1",
	"PCH_CHIP_CPU_MAX_TEMP",
	"PCH_CHIP_TEMP",
	"PCH_CPU_TEMP",
	"PCH_MCH_TEMP",
	"Agent0 Dimm0",
	"Agent0 Dimm1",
	"Agent1 Dimm0",
	"Agent1 Dimm1",
	"BYTE_TEMP0",
	"BYTE_TEMP1",
	"PECI Agent 0 Calibration",
	"PECI Agent 1 Calibration",
	"",
	"Virtual_TEMP"
पूर्ण;

#घोषणा NCT6795_TEMP_MASK	0xbfffff7e
#घोषणा NCT6795_VIRT_TEMP_MASK	0x80000000

अटल स्थिर अक्षर *स्थिर nct6796_temp_label[] = अणु
	"",
	"SYSTIN",
	"CPUTIN",
	"AUXTIN0",
	"AUXTIN1",
	"AUXTIN2",
	"AUXTIN3",
	"AUXTIN4",
	"SMBUSMASTER 0",
	"SMBUSMASTER 1",
	"Virtual_TEMP",
	"Virtual_TEMP",
	"",
	"",
	"",
	"",
	"PECI Agent 0",
	"PECI Agent 1",
	"PCH_CHIP_CPU_MAX_TEMP",
	"PCH_CHIP_TEMP",
	"PCH_CPU_TEMP",
	"PCH_MCH_TEMP",
	"Agent0 Dimm0",
	"Agent0 Dimm1",
	"Agent1 Dimm0",
	"Agent1 Dimm1",
	"BYTE_TEMP0",
	"BYTE_TEMP1",
	"PECI Agent 0 Calibration",
	"PECI Agent 1 Calibration",
	"",
	"Virtual_TEMP"
पूर्ण;

#घोषणा NCT6796_TEMP_MASK	0xbfff0ffe
#घोषणा NCT6796_VIRT_TEMP_MASK	0x80000c00

अटल स्थिर अक्षर *स्थिर nct6798_temp_label[] = अणु
	"",
	"SYSTIN",
	"CPUTIN",
	"AUXTIN0",
	"AUXTIN1",
	"AUXTIN2",
	"AUXTIN3",
	"AUXTIN4",
	"SMBUSMASTER 0",
	"SMBUSMASTER 1",
	"Virtual_TEMP",
	"Virtual_TEMP",
	"",
	"",
	"",
	"",
	"PECI Agent 0",
	"PECI Agent 1",
	"PCH_CHIP_CPU_MAX_TEMP",
	"PCH_CHIP_TEMP",
	"PCH_CPU_TEMP",
	"PCH_MCH_TEMP",
	"Agent0 Dimm0",
	"Agent0 Dimm1",
	"Agent1 Dimm0",
	"Agent1 Dimm1",
	"BYTE_TEMP0",
	"BYTE_TEMP1",
	"PECI Agent 0 Calibration",	/* unकरोcumented */
	"PECI Agent 1 Calibration",	/* unकरोcumented */
	"",
	"Virtual_TEMP"
पूर्ण;

#घोषणा NCT6798_TEMP_MASK	0xbfff0ffe
#घोषणा NCT6798_VIRT_TEMP_MASK	0x80000c00

/* NCT6102D/NCT6106D specअगरic data */

#घोषणा NCT6106_REG_VBAT	0x318
#घोषणा NCT6106_REG_DIODE	0x319
#घोषणा NCT6106_DIODE_MASK	0x01

अटल स्थिर u16 NCT6106_REG_IN_MAX[] = अणु
	0x90, 0x92, 0x94, 0x96, 0x98, 0x9a, 0x9e, 0xa0, 0xa2 पूर्ण;
अटल स्थिर u16 NCT6106_REG_IN_MIN[] = अणु
	0x91, 0x93, 0x95, 0x97, 0x99, 0x9b, 0x9f, 0xa1, 0xa3 पूर्ण;
अटल स्थिर u16 NCT6106_REG_IN[] = अणु
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x07, 0x08, 0x09 पूर्ण;

अटल स्थिर u16 NCT6106_REG_TEMP[] = अणु 0x10, 0x11, 0x12, 0x13, 0x14, 0x15 पूर्ण;
अटल स्थिर u16 NCT6106_REG_TEMP_MON[] = अणु 0x18, 0x19, 0x1a पूर्ण;
अटल स्थिर u16 NCT6106_REG_TEMP_HYST[] = अणु
	0xc3, 0xc7, 0xcb, 0xcf, 0xd3, 0xd7 पूर्ण;
अटल स्थिर u16 NCT6106_REG_TEMP_OVER[] = अणु
	0xc2, 0xc6, 0xca, 0xce, 0xd2, 0xd6 पूर्ण;
अटल स्थिर u16 NCT6106_REG_TEMP_CRIT_L[] = अणु
	0xc0, 0xc4, 0xc8, 0xcc, 0xd0, 0xd4 पूर्ण;
अटल स्थिर u16 NCT6106_REG_TEMP_CRIT_H[] = अणु
	0xc1, 0xc5, 0xc9, 0xcf, 0xd1, 0xd5 पूर्ण;
अटल स्थिर u16 NCT6106_REG_TEMP_OFFSET[] = अणु 0x311, 0x312, 0x313 पूर्ण;
अटल स्थिर u16 NCT6106_REG_TEMP_CONFIG[] = अणु
	0xb7, 0xb8, 0xb9, 0xba, 0xbb, 0xbc पूर्ण;

अटल स्थिर u16 NCT6106_REG_FAN[] = अणु 0x20, 0x22, 0x24 पूर्ण;
अटल स्थिर u16 NCT6106_REG_FAN_MIN[] = अणु 0xe0, 0xe2, 0xe4 पूर्ण;
अटल स्थिर u16 NCT6106_REG_FAN_PULSES[] = अणु 0xf6, 0xf6, 0xf6 पूर्ण;
अटल स्थिर u16 NCT6106_FAN_PULSE_SHIFT[] = अणु 0, 2, 4 पूर्ण;

अटल स्थिर u8 NCT6106_REG_PWM_MODE[] = अणु 0xf3, 0xf3, 0xf3 पूर्ण;
अटल स्थिर u8 NCT6106_PWM_MODE_MASK[] = अणु 0x01, 0x02, 0x04 पूर्ण;
अटल स्थिर u16 NCT6106_REG_PWM_READ[] = अणु 0x4a, 0x4b, 0x4c पूर्ण;
अटल स्थिर u16 NCT6106_REG_FAN_MODE[] = अणु 0x113, 0x123, 0x133 पूर्ण;
अटल स्थिर u16 NCT6106_REG_TEMP_SOURCE[] = अणु
	0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xb5 पूर्ण;

अटल स्थिर u16 NCT6106_REG_CRITICAL_TEMP[] = अणु 0x11a, 0x12a, 0x13a पूर्ण;
अटल स्थिर u16 NCT6106_REG_CRITICAL_TEMP_TOLERANCE[] = अणु
	0x11b, 0x12b, 0x13b पूर्ण;

अटल स्थिर u16 NCT6106_REG_CRITICAL_PWM_ENABLE[] = अणु 0x11c, 0x12c, 0x13c पूर्ण;
#घोषणा NCT6106_CRITICAL_PWM_ENABLE_MASK	0x10
अटल स्थिर u16 NCT6106_REG_CRITICAL_PWM[] = अणु 0x11d, 0x12d, 0x13d पूर्ण;

अटल स्थिर u16 NCT6106_REG_FAN_STEP_UP_TIME[] = अणु 0x114, 0x124, 0x134 पूर्ण;
अटल स्थिर u16 NCT6106_REG_FAN_STEP_DOWN_TIME[] = अणु 0x115, 0x125, 0x135 पूर्ण;
अटल स्थिर u16 NCT6106_REG_FAN_STOP_OUTPUT[] = अणु 0x116, 0x126, 0x136 पूर्ण;
अटल स्थिर u16 NCT6106_REG_FAN_START_OUTPUT[] = अणु 0x117, 0x127, 0x137 पूर्ण;
अटल स्थिर u16 NCT6106_REG_FAN_STOP_TIME[] = अणु 0x118, 0x128, 0x138 पूर्ण;
अटल स्थिर u16 NCT6106_REG_TOLERANCE_H[] = अणु 0x112, 0x122, 0x132 पूर्ण;

अटल स्थिर u16 NCT6106_REG_TARGET[] = अणु 0x111, 0x121, 0x131 पूर्ण;

अटल स्थिर u16 NCT6106_REG_WEIGHT_TEMP_SEL[] = अणु 0x168, 0x178, 0x188 पूर्ण;
अटल स्थिर u16 NCT6106_REG_WEIGHT_TEMP_STEP[] = अणु 0x169, 0x179, 0x189 पूर्ण;
अटल स्थिर u16 NCT6106_REG_WEIGHT_TEMP_STEP_TOL[] = अणु 0x16a, 0x17a, 0x18a पूर्ण;
अटल स्थिर u16 NCT6106_REG_WEIGHT_DUTY_STEP[] = अणु 0x16b, 0x17b, 0x18b पूर्ण;
अटल स्थिर u16 NCT6106_REG_WEIGHT_TEMP_BASE[] = अणु 0x16c, 0x17c, 0x18c पूर्ण;
अटल स्थिर u16 NCT6106_REG_WEIGHT_DUTY_BASE[] = अणु 0x16d, 0x17d, 0x18d पूर्ण;

अटल स्थिर u16 NCT6106_REG_AUTO_TEMP[] = अणु 0x160, 0x170, 0x180 पूर्ण;
अटल स्थिर u16 NCT6106_REG_AUTO_PWM[] = अणु 0x164, 0x174, 0x184 पूर्ण;

अटल स्थिर u16 NCT6106_REG_ALARM[NUM_REG_ALARM] = अणु
	0x77, 0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7d पूर्ण;

अटल स्थिर s8 NCT6106_ALARM_BITS[] = अणु
	0, 1, 2, 3, 4, 5, 7, 8,		/* in0.. in7 */
	9, -1, -1, -1, -1, -1, -1,	/* in8..in14 */
	-1,				/* unused */
	32, 33, 34, -1, -1,		/* fan1..fan5 */
	-1, -1, -1,			/* unused */
	16, 17, 18, 19, 20, 21,		/* temp1..temp6 */
	48, -1				/* पूर्णांकrusion0, पूर्णांकrusion1 */
पूर्ण;

अटल स्थिर u16 NCT6106_REG_BEEP[NUM_REG_BEEP] = अणु
	0x3c0, 0x3c1, 0x3c2, 0x3c3, 0x3c4 पूर्ण;

अटल स्थिर s8 NCT6106_BEEP_BITS[] = अणु
	0, 1, 2, 3, 4, 5, 7, 8,		/* in0.. in7 */
	9, 10, 11, 12, -1, -1, -1,	/* in8..in14 */
	32,				/* global beep enable */
	24, 25, 26, 27, 28,		/* fan1..fan5 */
	-1, -1, -1,			/* unused */
	16, 17, 18, 19, 20, 21,		/* temp1..temp6 */
	34, -1				/* पूर्णांकrusion0, पूर्णांकrusion1 */
पूर्ण;

अटल स्थिर u16 NCT6106_REG_TEMP_ALTERNATE[32] = अणु
	[14] = 0x51,
	[15] = 0x52,
	[16] = 0x54,
पूर्ण;

अटल स्थिर u16 NCT6106_REG_TEMP_CRIT[32] = अणु
	[11] = 0x204,
	[12] = 0x205,
पूर्ण;

/* NCT6112D/NCT6114D/NCT6116D specअगरic data */

अटल स्थिर u16 NCT6116_REG_FAN[] = अणु 0x20, 0x22, 0x24, 0x26, 0x28 पूर्ण;
अटल स्थिर u16 NCT6116_REG_FAN_MIN[] = अणु 0xe0, 0xe2, 0xe4, 0xe6, 0xe8 पूर्ण;
अटल स्थिर u16 NCT6116_REG_FAN_PULSES[] = अणु 0xf6, 0xf6, 0xf6, 0xf6, 0xf5 पूर्ण;
अटल स्थिर u16 NCT6116_FAN_PULSE_SHIFT[] = अणु 0, 2, 4, 6, 6 पूर्ण;

अटल स्थिर u16 NCT6116_REG_PWM[] = अणु 0x119, 0x129, 0x139, 0x199, 0x1a9 पूर्ण;
अटल स्थिर u16 NCT6116_REG_FAN_MODE[] = अणु 0x113, 0x123, 0x133, 0x193, 0x1a3 पूर्ण;
अटल स्थिर u16 NCT6116_REG_TEMP_SEL[] = अणु 0x110, 0x120, 0x130, 0x190, 0x1a0 पूर्ण;
अटल स्थिर u16 NCT6116_REG_TEMP_SOURCE[] = अणु
	0xb0, 0xb1, 0xb2 पूर्ण;

अटल स्थिर u16 NCT6116_REG_CRITICAL_TEMP[] = अणु
	0x11a, 0x12a, 0x13a, 0x19a, 0x1aa पूर्ण;
अटल स्थिर u16 NCT6116_REG_CRITICAL_TEMP_TOLERANCE[] = अणु
	0x11b, 0x12b, 0x13b, 0x19b, 0x1ab पूर्ण;

अटल स्थिर u16 NCT6116_REG_CRITICAL_PWM_ENABLE[] = अणु
	0x11c, 0x12c, 0x13c, 0x19c, 0x1ac पूर्ण;
अटल स्थिर u16 NCT6116_REG_CRITICAL_PWM[] = अणु
	0x11d, 0x12d, 0x13d, 0x19d, 0x1ad पूर्ण;

अटल स्थिर u16 NCT6116_REG_FAN_STEP_UP_TIME[] = अणु
	0x114, 0x124, 0x134, 0x194, 0x1a4 पूर्ण;
अटल स्थिर u16 NCT6116_REG_FAN_STEP_DOWN_TIME[] = अणु
	0x115, 0x125, 0x135, 0x195, 0x1a5 पूर्ण;
अटल स्थिर u16 NCT6116_REG_FAN_STOP_OUTPUT[] = अणु
	0x116, 0x126, 0x136, 0x196, 0x1a6 पूर्ण;
अटल स्थिर u16 NCT6116_REG_FAN_START_OUTPUT[] = अणु
	0x117, 0x127, 0x137, 0x197, 0x1a7 पूर्ण;
अटल स्थिर u16 NCT6116_REG_FAN_STOP_TIME[] = अणु
	0x118, 0x128, 0x138, 0x198, 0x1a8 पूर्ण;
अटल स्थिर u16 NCT6116_REG_TOLERANCE_H[] = अणु
	0x112, 0x122, 0x132, 0x192, 0x1a2 पूर्ण;

अटल स्थिर u16 NCT6116_REG_TARGET[] = अणु
	0x111, 0x121, 0x131, 0x191, 0x1a1 पूर्ण;

अटल स्थिर u16 NCT6116_REG_AUTO_TEMP[] = अणु
	0x160, 0x170, 0x180, 0x1d0, 0x1e0 पूर्ण;
अटल स्थिर u16 NCT6116_REG_AUTO_PWM[] = अणु
	0x164, 0x174, 0x184, 0x1d4, 0x1e4 पूर्ण;

अटल स्थिर s8 NCT6116_ALARM_BITS[] = अणु
	0, 1, 2, 3, 4, 5, 7, 8,		/* in0.. in7 */
	9, -1, -1, -1, -1, -1, -1,	/* in8..in9 */
	-1,				/* unused */
	32, 33, 34, 35, 36,		/* fan1..fan5 */
	-1, -1, -1,			/* unused */
	16, 17, 18, -1, -1, -1,		/* temp1..temp6 */
	48, -1				/* पूर्णांकrusion0, पूर्णांकrusion1 */
पूर्ण;

अटल स्थिर s8 NCT6116_BEEP_BITS[] = अणु
	0, 1, 2, 3, 4, 5, 7, 8,		/* in0.. in7 */
	9, 10, 11, 12, -1, -1, -1,	/* in8..in14 */
	32,				/* global beep enable */
	24, 25, 26, 27, 28,		/* fan1..fan5 */
	-1, -1, -1,			/* unused */
	16, 17, 18, -1, -1, -1,		/* temp1..temp6 */
	34, -1				/* पूर्णांकrusion0, पूर्णांकrusion1 */
पूर्ण;

अटल क्रमागत pwm_enable reg_to_pwm_enable(पूर्णांक pwm, पूर्णांक mode)
अणु
	अगर (mode == 0 && pwm == 255)
		वापस off;
	वापस mode + 1;
पूर्ण

अटल पूर्णांक pwm_enable_to_reg(क्रमागत pwm_enable mode)
अणु
	अगर (mode == off)
		वापस 0;
	वापस mode - 1;
पूर्ण

/*
 * Conversions
 */

/* 1 is DC mode, output in ms */
अटल अचिन्हित पूर्णांक step_समय_from_reg(u8 reg, u8 mode)
अणु
	वापस mode ? 400 * reg : 100 * reg;
पूर्ण

अटल u8 step_समय_प्रकारo_reg(अचिन्हित पूर्णांक msec, u8 mode)
अणु
	वापस clamp_val((mode ? (msec + 200) / 400 :
					(msec + 50) / 100), 1, 255);
पूर्ण

अटल अचिन्हित पूर्णांक fan_from_reg8(u16 reg, अचिन्हित पूर्णांक भागreg)
अणु
	अगर (reg == 0 || reg == 255)
		वापस 0;
	वापस 1350000U / (reg << भागreg);
पूर्ण

अटल अचिन्हित पूर्णांक fan_from_reg13(u16 reg, अचिन्हित पूर्णांक भागreg)
अणु
	अगर ((reg & 0xff1f) == 0xff1f)
		वापस 0;

	reg = (reg & 0x1f) | ((reg & 0xff00) >> 3);

	अगर (reg == 0)
		वापस 0;

	वापस 1350000U / reg;
पूर्ण

अटल अचिन्हित पूर्णांक fan_from_reg16(u16 reg, अचिन्हित पूर्णांक भागreg)
अणु
	अगर (reg == 0 || reg == 0xffff)
		वापस 0;

	/*
	 * Even though the रेजिस्टरs are 16 bit wide, the fan भागisor
	 * still applies.
	 */
	वापस 1350000U / (reg << भागreg);
पूर्ण

अटल अचिन्हित पूर्णांक fan_from_reg_rpm(u16 reg, अचिन्हित पूर्णांक भागreg)
अणु
	वापस reg;
पूर्ण

अटल u16 fan_to_reg(u32 fan, अचिन्हित पूर्णांक भागreg)
अणु
	अगर (!fan)
		वापस 0;

	वापस (1350000U / fan) >> भागreg;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक
भाग_from_reg(u8 reg)
अणु
	वापस BIT(reg);
पूर्ण

/*
 * Some of the voltage inमाला_दो have पूर्णांकernal scaling, the tables below
 * contain 8 (the ADC LSB in mV) * scaling factor * 100
 */
अटल स्थिर u16 scale_in[15] = अणु
	800, 800, 1600, 1600, 800, 800, 800, 1600, 1600, 800, 800, 800, 800,
	800, 800
पूर्ण;

अटल अंतरभूत दीर्घ in_from_reg(u8 reg, u8 nr)
अणु
	वापस DIV_ROUND_CLOSEST(reg * scale_in[nr], 100);
पूर्ण

अटल अंतरभूत u8 in_to_reg(u32 val, u8 nr)
अणु
	वापस clamp_val(DIV_ROUND_CLOSEST(val * 100, scale_in[nr]), 0, 255);
पूर्ण

/*
 * Data काष्ठाures and manipulation thereof
 */

काष्ठा nct6775_data अणु
	पूर्णांक addr;	/* IO base of hw monitor block */
	पूर्णांक sioreg;	/* SIO रेजिस्टर address */
	क्रमागत kinds kind;
	स्थिर अक्षर *name;

	स्थिर काष्ठा attribute_group *groups[6];

	u16 reg_temp[5][NUM_TEMP]; /* 0=temp, 1=temp_over, 2=temp_hyst,
				    * 3=temp_crit, 4=temp_lcrit
				    */
	u8 temp_src[NUM_TEMP];
	u16 reg_temp_config[NUM_TEMP];
	स्थिर अक्षर * स्थिर *temp_label;
	u32 temp_mask;
	u32 virt_temp_mask;

	u16 REG_CONFIG;
	u16 REG_VBAT;
	u16 REG_DIODE;
	u8 DIODE_MASK;

	स्थिर s8 *ALARM_BITS;
	स्थिर s8 *BEEP_BITS;

	स्थिर u16 *REG_VIN;
	स्थिर u16 *REG_IN_MINMAX[2];

	स्थिर u16 *REG_TARGET;
	स्थिर u16 *REG_FAN;
	स्थिर u16 *REG_FAN_MODE;
	स्थिर u16 *REG_FAN_MIN;
	स्थिर u16 *REG_FAN_PULSES;
	स्थिर u16 *FAN_PULSE_SHIFT;
	स्थिर u16 *REG_FAN_TIME[3];

	स्थिर u16 *REG_TOLERANCE_H;

	स्थिर u8 *REG_PWM_MODE;
	स्थिर u8 *PWM_MODE_MASK;

	स्थिर u16 *REG_PWM[7];	/* [0]=pwm, [1]=pwm_start, [2]=pwm_न्यूनमान,
				 * [3]=pwm_max, [4]=pwm_step,
				 * [5]=weight_duty_step, [6]=weight_duty_base
				 */
	स्थिर u16 *REG_PWM_READ;

	स्थिर u16 *REG_CRITICAL_PWM_ENABLE;
	u8 CRITICAL_PWM_ENABLE_MASK;
	स्थिर u16 *REG_CRITICAL_PWM;

	स्थिर u16 *REG_AUTO_TEMP;
	स्थिर u16 *REG_AUTO_PWM;

	स्थिर u16 *REG_CRITICAL_TEMP;
	स्थिर u16 *REG_CRITICAL_TEMP_TOLERANCE;

	स्थिर u16 *REG_TEMP_SOURCE;	/* temp रेजिस्टर sources */
	स्थिर u16 *REG_TEMP_SEL;
	स्थिर u16 *REG_WEIGHT_TEMP_SEL;
	स्थिर u16 *REG_WEIGHT_TEMP[3];	/* 0=base, 1=tolerance, 2=step */

	स्थिर u16 *REG_TEMP_OFFSET;

	स्थिर u16 *REG_ALARM;
	स्थिर u16 *REG_BEEP;

	अचिन्हित पूर्णांक (*fan_from_reg)(u16 reg, अचिन्हित पूर्णांक भागreg);
	अचिन्हित पूर्णांक (*fan_from_reg_min)(u16 reg, अचिन्हित पूर्णांक भागreg);

	काष्ठा mutex update_lock;
	bool valid;		/* true अगर following fields are valid */
	अचिन्हित दीर्घ last_updated;	/* In jअगरfies */

	/* Register values */
	u8 bank;		/* current रेजिस्टर bank */
	u8 in_num;		/* number of in inमाला_दो we have */
	u8 in[15][3];		/* [0]=in, [1]=in_max, [2]=in_min */
	अचिन्हित पूर्णांक rpm[NUM_FAN];
	u16 fan_min[NUM_FAN];
	u8 fan_pulses[NUM_FAN];
	u8 fan_भाग[NUM_FAN];
	u8 has_pwm;
	u8 has_fan;		/* some fan inमाला_दो can be disabled */
	u8 has_fan_min;		/* some fans करोn't have min रेजिस्टर */
	bool has_fan_भाग;

	u8 num_temp_alarms;	/* 2, 3, or 6 */
	u8 num_temp_beeps;	/* 2, 3, or 6 */
	u8 temp_fixed_num;	/* 3 or 6 */
	u8 temp_type[NUM_TEMP_FIXED];
	s8 temp_offset[NUM_TEMP_FIXED];
	s16 temp[5][NUM_TEMP]; /* 0=temp, 1=temp_over, 2=temp_hyst,
				* 3=temp_crit, 4=temp_lcrit */
	u64 alarms;
	u64 beeps;

	u8 pwm_num;	/* number of pwm */
	u8 pwm_mode[NUM_FAN];	/* 0->DC variable voltage,
				 * 1->PWM variable duty cycle
				 */
	क्रमागत pwm_enable pwm_enable[NUM_FAN];
			/* 0->off
			 * 1->manual
			 * 2->thermal cruise mode (also called SmartFan I)
			 * 3->fan speed cruise mode
			 * 4->SmartFan III
			 * 5->enhanced variable thermal cruise (SmartFan IV)
			 */
	u8 pwm[7][NUM_FAN];	/* [0]=pwm, [1]=pwm_start, [2]=pwm_न्यूनमान,
				 * [3]=pwm_max, [4]=pwm_step,
				 * [5]=weight_duty_step, [6]=weight_duty_base
				 */

	u8 target_temp[NUM_FAN];
	u8 target_temp_mask;
	u32 target_speed[NUM_FAN];
	u32 target_speed_tolerance[NUM_FAN];
	u8 speed_tolerance_limit;

	u8 temp_tolerance[2][NUM_FAN];
	u8 tolerance_mask;

	u8 fan_समय[3][NUM_FAN]; /* 0 = stop_समय, 1 = step_up, 2 = step_करोwn */

	/* Automatic fan speed control रेजिस्टरs */
	पूर्णांक स्वतः_pwm_num;
	u8 स्वतः_pwm[NUM_FAN][7];
	u8 स्वतः_temp[NUM_FAN][7];
	u8 pwm_temp_sel[NUM_FAN];
	u8 pwm_weight_temp_sel[NUM_FAN];
	u8 weight_temp[3][NUM_FAN];	/* 0->temp_step, 1->temp_step_tol,
					 * 2->temp_base
					 */

	u8 vid;
	u8 vrm;

	bool have_vid;

	u16 have_temp;
	u16 have_temp_fixed;
	u16 have_in;

	/* Remember extra रेजिस्टर values over suspend/resume */
	u8 vbat;
	u8 fanभाग1;
	u8 fanभाग2;
	u8 sio_reg_enable;
पूर्ण;

काष्ठा nct6775_sio_data अणु
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
nct6775_create_attr_group(काष्ठा device *dev,
			  स्थिर काष्ठा sensor_ढाँचा_group *tg,
			  पूर्णांक repeat)
अणु
	काष्ठा attribute_group *group;
	काष्ठा sensor_device_attr_u *su;
	काष्ठा sensor_device_attribute *a;
	काष्ठा sensor_device_attribute_2 *a2;
	काष्ठा attribute **attrs;
	काष्ठा sensor_device_ढाँचा **t;
	पूर्णांक i, count;

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
		जबतक (*t != शून्य) अणु
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

अटल bool is_word_sized(काष्ठा nct6775_data *data, u16 reg)
अणु
	चयन (data->kind) अणु
	हाल nct6106:
		वापस reg == 0x20 || reg == 0x22 || reg == 0x24 ||
		  reg == 0xe0 || reg == 0xe2 || reg == 0xe4 ||
		  reg == 0x111 || reg == 0x121 || reg == 0x131;
	हाल nct6116:
		वापस reg == 0x20 || reg == 0x22 || reg == 0x24 ||
		  reg == 0x26 || reg == 0x28 || reg == 0xe0 || reg == 0xe2 ||
		  reg == 0xe4 || reg == 0xe6 || reg == 0xe8 || reg == 0x111 ||
		  reg == 0x121 || reg == 0x131 || reg == 0x191 || reg == 0x1a1;
	हाल nct6775:
		वापस (((reg & 0xff00) == 0x100 ||
		    (reg & 0xff00) == 0x200) &&
		   ((reg & 0x00ff) == 0x50 ||
		    (reg & 0x00ff) == 0x53 ||
		    (reg & 0x00ff) == 0x55)) ||
		  (reg & 0xfff0) == 0x630 ||
		  reg == 0x640 || reg == 0x642 ||
		  reg == 0x662 ||
		  ((reg & 0xfff0) == 0x650 && (reg & 0x000f) >= 0x06) ||
		  reg == 0x73 || reg == 0x75 || reg == 0x77;
	हाल nct6776:
		वापस (((reg & 0xff00) == 0x100 ||
		    (reg & 0xff00) == 0x200) &&
		   ((reg & 0x00ff) == 0x50 ||
		    (reg & 0x00ff) == 0x53 ||
		    (reg & 0x00ff) == 0x55)) ||
		  (reg & 0xfff0) == 0x630 ||
		  reg == 0x402 ||
		  reg == 0x640 || reg == 0x642 ||
		  ((reg & 0xfff0) == 0x650 && (reg & 0x000f) >= 0x06) ||
		  reg == 0x73 || reg == 0x75 || reg == 0x77;
	हाल nct6779:
	हाल nct6791:
	हाल nct6792:
	हाल nct6793:
	हाल nct6795:
	हाल nct6796:
	हाल nct6797:
	हाल nct6798:
		वापस reg == 0x150 || reg == 0x153 || reg == 0x155 ||
		  (reg & 0xfff0) == 0x4c0 ||
		  reg == 0x402 ||
		  reg == 0x63a || reg == 0x63c || reg == 0x63e ||
		  reg == 0x640 || reg == 0x642 || reg == 0x64a ||
		  reg == 0x64c ||
		  reg == 0x73 || reg == 0x75 || reg == 0x77 || reg == 0x79 ||
		  reg == 0x7b || reg == 0x7d;
	पूर्ण
	वापस false;
पूर्ण

/*
 * On older chips, only रेजिस्टरs 0x50-0x5f are banked.
 * On more recent chips, all रेजिस्टरs are banked.
 * Assume that is the हाल and set the bank number क्रम each access.
 * Cache the bank number so it only needs to be set अगर it changes.
 */
अटल अंतरभूत व्योम nct6775_set_bank(काष्ठा nct6775_data *data, u16 reg)
अणु
	u8 bank = reg >> 8;

	अगर (data->bank != bank) अणु
		outb_p(NCT6775_REG_BANK, data->addr + ADDR_REG_OFFSET);
		outb_p(bank, data->addr + DATA_REG_OFFSET);
		data->bank = bank;
	पूर्ण
पूर्ण

अटल u16 nct6775_पढ़ो_value(काष्ठा nct6775_data *data, u16 reg)
अणु
	पूर्णांक res, word_sized = is_word_sized(data, reg);

	nct6775_set_bank(data, reg);
	outb_p(reg & 0xff, data->addr + ADDR_REG_OFFSET);
	res = inb_p(data->addr + DATA_REG_OFFSET);
	अगर (word_sized) अणु
		outb_p((reg & 0xff) + 1,
		       data->addr + ADDR_REG_OFFSET);
		res = (res << 8) + inb_p(data->addr + DATA_REG_OFFSET);
	पूर्ण
	वापस res;
पूर्ण

अटल पूर्णांक nct6775_ग_लिखो_value(काष्ठा nct6775_data *data, u16 reg, u16 value)
अणु
	पूर्णांक word_sized = is_word_sized(data, reg);

	nct6775_set_bank(data, reg);
	outb_p(reg & 0xff, data->addr + ADDR_REG_OFFSET);
	अगर (word_sized) अणु
		outb_p(value >> 8, data->addr + DATA_REG_OFFSET);
		outb_p((reg & 0xff) + 1,
		       data->addr + ADDR_REG_OFFSET);
	पूर्ण
	outb_p(value & 0xff, data->addr + DATA_REG_OFFSET);
	वापस 0;
पूर्ण

/* We left-align 8-bit temperature values to make the code simpler */
अटल u16 nct6775_पढ़ो_temp(काष्ठा nct6775_data *data, u16 reg)
अणु
	u16 res;

	res = nct6775_पढ़ो_value(data, reg);
	अगर (!is_word_sized(data, reg))
		res <<= 8;

	वापस res;
पूर्ण

अटल पूर्णांक nct6775_ग_लिखो_temp(काष्ठा nct6775_data *data, u16 reg, u16 value)
अणु
	अगर (!is_word_sized(data, reg))
		value >>= 8;
	वापस nct6775_ग_लिखो_value(data, reg, value);
पूर्ण

/* This function assumes that the caller holds data->update_lock */
अटल व्योम nct6775_ग_लिखो_fan_भाग(काष्ठा nct6775_data *data, पूर्णांक nr)
अणु
	u8 reg;

	चयन (nr) अणु
	हाल 0:
		reg = (nct6775_पढ़ो_value(data, NCT6775_REG_FANDIV1) & 0x70)
		    | (data->fan_भाग[0] & 0x7);
		nct6775_ग_लिखो_value(data, NCT6775_REG_FANDIV1, reg);
		अवरोध;
	हाल 1:
		reg = (nct6775_पढ़ो_value(data, NCT6775_REG_FANDIV1) & 0x7)
		    | ((data->fan_भाग[1] << 4) & 0x70);
		nct6775_ग_लिखो_value(data, NCT6775_REG_FANDIV1, reg);
		अवरोध;
	हाल 2:
		reg = (nct6775_पढ़ो_value(data, NCT6775_REG_FANDIV2) & 0x70)
		    | (data->fan_भाग[2] & 0x7);
		nct6775_ग_लिखो_value(data, NCT6775_REG_FANDIV2, reg);
		अवरोध;
	हाल 3:
		reg = (nct6775_पढ़ो_value(data, NCT6775_REG_FANDIV2) & 0x7)
		    | ((data->fan_भाग[3] << 4) & 0x70);
		nct6775_ग_लिखो_value(data, NCT6775_REG_FANDIV2, reg);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम nct6775_ग_लिखो_fan_भाग_common(काष्ठा nct6775_data *data, पूर्णांक nr)
अणु
	अगर (data->kind == nct6775)
		nct6775_ग_लिखो_fan_भाग(data, nr);
पूर्ण

अटल व्योम nct6775_update_fan_भाग(काष्ठा nct6775_data *data)
अणु
	u8 i;

	i = nct6775_पढ़ो_value(data, NCT6775_REG_FANDIV1);
	data->fan_भाग[0] = i & 0x7;
	data->fan_भाग[1] = (i & 0x70) >> 4;
	i = nct6775_पढ़ो_value(data, NCT6775_REG_FANDIV2);
	data->fan_भाग[2] = i & 0x7;
	अगर (data->has_fan & BIT(3))
		data->fan_भाग[3] = (i & 0x70) >> 4;
पूर्ण

अटल व्योम nct6775_update_fan_भाग_common(काष्ठा nct6775_data *data)
अणु
	अगर (data->kind == nct6775)
		nct6775_update_fan_भाग(data);
पूर्ण

अटल व्योम nct6775_init_fan_भाग(काष्ठा nct6775_data *data)
अणु
	पूर्णांक i;

	nct6775_update_fan_भाग_common(data);
	/*
	 * For all fans, start with highest भागider value अगर the भागider
	 * रेजिस्टर is not initialized. This ensures that we get a
	 * पढ़ोing from the fan count रेजिस्टर, even अगर it is not optimal.
	 * We'll compute a better भागider later on.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(data->fan_भाग); i++) अणु
		अगर (!(data->has_fan & BIT(i)))
			जारी;
		अगर (data->fan_भाग[i] == 0) अणु
			data->fan_भाग[i] = 7;
			nct6775_ग_लिखो_fan_भाग_common(data, i);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम nct6775_init_fan_common(काष्ठा device *dev,
				    काष्ठा nct6775_data *data)
अणु
	पूर्णांक i;
	u8 reg;

	अगर (data->has_fan_भाग)
		nct6775_init_fan_भाग(data);

	/*
	 * If fan_min is not set (0), set it to 0xff to disable it. This
	 * prevents the unnecessary warning when fanX_min is reported as 0.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(data->fan_min); i++) अणु
		अगर (data->has_fan_min & BIT(i)) अणु
			reg = nct6775_पढ़ो_value(data, data->REG_FAN_MIN[i]);
			अगर (!reg)
				nct6775_ग_लिखो_value(data, data->REG_FAN_MIN[i],
						    data->has_fan_भाग ? 0xff
								      : 0xff1f);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम nct6775_select_fan_भाग(काष्ठा device *dev,
				   काष्ठा nct6775_data *data, पूर्णांक nr, u16 reg)
अणु
	u8 fan_भाग = data->fan_भाग[nr];
	u16 fan_min;

	अगर (!data->has_fan_भाग)
		वापस;

	/*
	 * If we failed to measure the fan speed, or the reported value is not
	 * in the optimal range, and the घड़ी भागider can be modअगरied,
	 * let's try that क्रम next समय.
	 */
	अगर (reg == 0x00 && fan_भाग < 0x07)
		fan_भाग++;
	अन्यथा अगर (reg != 0x00 && reg < 0x30 && fan_भाग > 0)
		fan_भाग--;

	अगर (fan_भाग != data->fan_भाग[nr]) अणु
		dev_dbg(dev, "Modifying fan%d clock divider from %u to %u\n",
			nr + 1, भाग_from_reg(data->fan_भाग[nr]),
			भाग_from_reg(fan_भाग));

		/* Preserve min limit अगर possible */
		अगर (data->has_fan_min & BIT(nr)) अणु
			fan_min = data->fan_min[nr];
			अगर (fan_भाग > data->fan_भाग[nr]) अणु
				अगर (fan_min != 255 && fan_min > 1)
					fan_min >>= 1;
			पूर्ण अन्यथा अणु
				अगर (fan_min != 255) अणु
					fan_min <<= 1;
					अगर (fan_min > 254)
						fan_min = 254;
				पूर्ण
			पूर्ण
			अगर (fan_min != data->fan_min[nr]) अणु
				data->fan_min[nr] = fan_min;
				nct6775_ग_लिखो_value(data, data->REG_FAN_MIN[nr],
						    fan_min);
			पूर्ण
		पूर्ण
		data->fan_भाग[nr] = fan_भाग;
		nct6775_ग_लिखो_fan_भाग_common(data, nr);
	पूर्ण
पूर्ण

अटल व्योम nct6775_update_pwm(काष्ठा device *dev)
अणु
	काष्ठा nct6775_data *data = dev_get_drvdata(dev);
	पूर्णांक i, j;
	पूर्णांक fanmodecfg, reg;
	bool duty_is_dc;

	क्रम (i = 0; i < data->pwm_num; i++) अणु
		अगर (!(data->has_pwm & BIT(i)))
			जारी;

		duty_is_dc = data->REG_PWM_MODE[i] &&
		  (nct6775_पढ़ो_value(data, data->REG_PWM_MODE[i])
		   & data->PWM_MODE_MASK[i]);
		data->pwm_mode[i] = !duty_is_dc;

		fanmodecfg = nct6775_पढ़ो_value(data, data->REG_FAN_MODE[i]);
		क्रम (j = 0; j < ARRAY_SIZE(data->REG_PWM); j++) अणु
			अगर (data->REG_PWM[j] && data->REG_PWM[j][i]) अणु
				data->pwm[j][i]
				  = nct6775_पढ़ो_value(data,
						       data->REG_PWM[j][i]);
			पूर्ण
		पूर्ण

		data->pwm_enable[i] = reg_to_pwm_enable(data->pwm[0][i],
							(fanmodecfg >> 4) & 7);

		अगर (!data->temp_tolerance[0][i] ||
		    data->pwm_enable[i] != speed_cruise)
			data->temp_tolerance[0][i] = fanmodecfg & 0x0f;
		अगर (!data->target_speed_tolerance[i] ||
		    data->pwm_enable[i] == speed_cruise) अणु
			u8 t = fanmodecfg & 0x0f;

			अगर (data->REG_TOLERANCE_H) अणु
				t |= (nct6775_पढ़ो_value(data,
				      data->REG_TOLERANCE_H[i]) & 0x70) >> 1;
			पूर्ण
			data->target_speed_tolerance[i] = t;
		पूर्ण

		data->temp_tolerance[1][i] =
			nct6775_पढ़ो_value(data,
					data->REG_CRITICAL_TEMP_TOLERANCE[i]);

		reg = nct6775_पढ़ो_value(data, data->REG_TEMP_SEL[i]);
		data->pwm_temp_sel[i] = reg & 0x1f;
		/* If fan can stop, report न्यूनमान as 0 */
		अगर (reg & 0x80)
			data->pwm[2][i] = 0;

		अगर (!data->REG_WEIGHT_TEMP_SEL[i])
			जारी;

		reg = nct6775_पढ़ो_value(data, data->REG_WEIGHT_TEMP_SEL[i]);
		data->pwm_weight_temp_sel[i] = reg & 0x1f;
		/* If weight is disabled, report weight source as 0 */
		अगर (!(reg & 0x80))
			data->pwm_weight_temp_sel[i] = 0;

		/* Weight temp data */
		क्रम (j = 0; j < ARRAY_SIZE(data->weight_temp); j++) अणु
			data->weight_temp[j][i]
			  = nct6775_पढ़ो_value(data,
					       data->REG_WEIGHT_TEMP[j][i]);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम nct6775_update_pwm_limits(काष्ठा device *dev)
अणु
	काष्ठा nct6775_data *data = dev_get_drvdata(dev);
	पूर्णांक i, j;
	u8 reg;
	u16 reg_t;

	क्रम (i = 0; i < data->pwm_num; i++) अणु
		अगर (!(data->has_pwm & BIT(i)))
			जारी;

		क्रम (j = 0; j < ARRAY_SIZE(data->fan_समय); j++) अणु
			data->fan_समय[j][i] =
			  nct6775_पढ़ो_value(data, data->REG_FAN_TIME[j][i]);
		पूर्ण

		reg_t = nct6775_पढ़ो_value(data, data->REG_TARGET[i]);
		/* Update only in matching mode or अगर never updated */
		अगर (!data->target_temp[i] ||
		    data->pwm_enable[i] == thermal_cruise)
			data->target_temp[i] = reg_t & data->target_temp_mask;
		अगर (!data->target_speed[i] ||
		    data->pwm_enable[i] == speed_cruise) अणु
			अगर (data->REG_TOLERANCE_H) अणु
				reg_t |= (nct6775_पढ़ो_value(data,
					data->REG_TOLERANCE_H[i]) & 0x0f) << 8;
			पूर्ण
			data->target_speed[i] = reg_t;
		पूर्ण

		क्रम (j = 0; j < data->स्वतः_pwm_num; j++) अणु
			data->स्वतः_pwm[i][j] =
			  nct6775_पढ़ो_value(data,
					     NCT6775_AUTO_PWM(data, i, j));
			data->स्वतः_temp[i][j] =
			  nct6775_पढ़ो_value(data,
					     NCT6775_AUTO_TEMP(data, i, j));
		पूर्ण

		/* critical स्वतः_pwm temperature data */
		data->स्वतः_temp[i][data->स्वतः_pwm_num] =
			nct6775_पढ़ो_value(data, data->REG_CRITICAL_TEMP[i]);

		चयन (data->kind) अणु
		हाल nct6775:
			reg = nct6775_पढ़ो_value(data,
						 NCT6775_REG_CRITICAL_ENAB[i]);
			data->स्वतः_pwm[i][data->स्वतः_pwm_num] =
						(reg & 0x02) ? 0xff : 0x00;
			अवरोध;
		हाल nct6776:
			data->स्वतः_pwm[i][data->स्वतः_pwm_num] = 0xff;
			अवरोध;
		हाल nct6106:
		हाल nct6116:
		हाल nct6779:
		हाल nct6791:
		हाल nct6792:
		हाल nct6793:
		हाल nct6795:
		हाल nct6796:
		हाल nct6797:
		हाल nct6798:
			reg = nct6775_पढ़ो_value(data,
					data->REG_CRITICAL_PWM_ENABLE[i]);
			अगर (reg & data->CRITICAL_PWM_ENABLE_MASK)
				reg = nct6775_पढ़ो_value(data,
					data->REG_CRITICAL_PWM[i]);
			अन्यथा
				reg = 0xff;
			data->स्वतः_pwm[i][data->स्वतः_pwm_num] = reg;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा nct6775_data *nct6775_update_device(काष्ठा device *dev)
अणु
	काष्ठा nct6775_data *data = dev_get_drvdata(dev);
	पूर्णांक i, j;

	mutex_lock(&data->update_lock);

	अगर (समय_after(jअगरfies, data->last_updated + HZ + HZ / 2)
	    || !data->valid) अणु
		/* Fan घड़ी भागiders */
		nct6775_update_fan_भाग_common(data);

		/* Measured voltages and limits */
		क्रम (i = 0; i < data->in_num; i++) अणु
			अगर (!(data->have_in & BIT(i)))
				जारी;

			data->in[i][0] = nct6775_पढ़ो_value(data,
							    data->REG_VIN[i]);
			data->in[i][1] = nct6775_पढ़ो_value(data,
					  data->REG_IN_MINMAX[0][i]);
			data->in[i][2] = nct6775_पढ़ो_value(data,
					  data->REG_IN_MINMAX[1][i]);
		पूर्ण

		/* Measured fan speeds and limits */
		क्रम (i = 0; i < ARRAY_SIZE(data->rpm); i++) अणु
			u16 reg;

			अगर (!(data->has_fan & BIT(i)))
				जारी;

			reg = nct6775_पढ़ो_value(data, data->REG_FAN[i]);
			data->rpm[i] = data->fan_from_reg(reg,
							  data->fan_भाग[i]);

			अगर (data->has_fan_min & BIT(i))
				data->fan_min[i] = nct6775_पढ़ो_value(data,
					   data->REG_FAN_MIN[i]);

			अगर (data->REG_FAN_PULSES[i]) अणु
				data->fan_pulses[i] =
				  (nct6775_पढ़ो_value(data,
						      data->REG_FAN_PULSES[i])
				   >> data->FAN_PULSE_SHIFT[i]) & 0x03;
			पूर्ण

			nct6775_select_fan_भाग(dev, data, i, reg);
		पूर्ण

		nct6775_update_pwm(dev);
		nct6775_update_pwm_limits(dev);

		/* Measured temperatures and limits */
		क्रम (i = 0; i < NUM_TEMP; i++) अणु
			अगर (!(data->have_temp & BIT(i)))
				जारी;
			क्रम (j = 0; j < ARRAY_SIZE(data->reg_temp); j++) अणु
				अगर (data->reg_temp[j][i])
					data->temp[j][i]
					  = nct6775_पढ़ो_temp(data,
						data->reg_temp[j][i]);
			पूर्ण
			अगर (i >= NUM_TEMP_FIXED ||
			    !(data->have_temp_fixed & BIT(i)))
				जारी;
			data->temp_offset[i]
			  = nct6775_पढ़ो_value(data, data->REG_TEMP_OFFSET[i]);
		पूर्ण

		data->alarms = 0;
		क्रम (i = 0; i < NUM_REG_ALARM; i++) अणु
			u8 alarm;

			अगर (!data->REG_ALARM[i])
				जारी;
			alarm = nct6775_पढ़ो_value(data, data->REG_ALARM[i]);
			data->alarms |= ((u64)alarm) << (i << 3);
		पूर्ण

		data->beeps = 0;
		क्रम (i = 0; i < NUM_REG_BEEP; i++) अणु
			u8 beep;

			अगर (!data->REG_BEEP[i])
				जारी;
			beep = nct6775_पढ़ो_value(data, data->REG_BEEP[i]);
			data->beeps |= ((u64)beep) << (i << 3);
		पूर्ण

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
show_in_reg(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nct6775_data *data = nct6775_update_device(dev);
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	पूर्णांक index = sattr->index;
	पूर्णांक nr = sattr->nr;

	वापस प्र_लिखो(buf, "%ld\n", in_from_reg(data->in[nr][index], nr));
पूर्ण

अटल sमाप_प्रकार
store_in_reg(काष्ठा device *dev, काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
	     माप_प्रकार count)
अणु
	काष्ठा nct6775_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	पूर्णांक index = sattr->index;
	पूर्णांक nr = sattr->nr;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err < 0)
		वापस err;
	mutex_lock(&data->update_lock);
	data->in[nr][index] = in_to_reg(val, nr);
	nct6775_ग_लिखो_value(data, data->REG_IN_MINMAX[index - 1][nr],
			    data->in[nr][index]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार
show_alarm(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nct6775_data *data = nct6775_update_device(dev);
	काष्ठा sensor_device_attribute *sattr = to_sensor_dev_attr(attr);
	पूर्णांक nr = data->ALARM_BITS[sattr->index];

	वापस प्र_लिखो(buf, "%u\n",
		       (अचिन्हित पूर्णांक)((data->alarms >> nr) & 0x01));
पूर्ण

अटल पूर्णांक find_temp_source(काष्ठा nct6775_data *data, पूर्णांक index, पूर्णांक count)
अणु
	पूर्णांक source = data->temp_src[index];
	पूर्णांक nr;

	क्रम (nr = 0; nr < count; nr++) अणु
		पूर्णांक src;

		src = nct6775_पढ़ो_value(data,
					 data->REG_TEMP_SOURCE[nr]) & 0x1f;
		अगर (src == source)
			वापस nr;
	पूर्ण
	वापस -ENODEV;
पूर्ण

अटल sमाप_प्रकार
show_temp_alarm(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sattr = to_sensor_dev_attr(attr);
	काष्ठा nct6775_data *data = nct6775_update_device(dev);
	अचिन्हित पूर्णांक alarm = 0;
	पूर्णांक nr;

	/*
	 * For temperatures, there is no fixed mapping from रेजिस्टरs to alarm
	 * bits. Alarm bits are determined by the temperature source mapping.
	 */
	nr = find_temp_source(data, sattr->index, data->num_temp_alarms);
	अगर (nr >= 0) अणु
		पूर्णांक bit = data->ALARM_BITS[nr + TEMP_ALARM_BASE];

		alarm = (data->alarms >> bit) & 0x01;
	पूर्ण
	वापस प्र_लिखो(buf, "%u\n", alarm);
पूर्ण

अटल sमाप_प्रकार
show_beep(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sattr = to_sensor_dev_attr(attr);
	काष्ठा nct6775_data *data = nct6775_update_device(dev);
	पूर्णांक nr = data->BEEP_BITS[sattr->index];

	वापस प्र_लिखो(buf, "%u\n",
		       (अचिन्हित पूर्णांक)((data->beeps >> nr) & 0x01));
पूर्ण

अटल sमाप_प्रकार
store_beep(काष्ठा device *dev, काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
	   माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	काष्ठा nct6775_data *data = dev_get_drvdata(dev);
	पूर्णांक nr = data->BEEP_BITS[sattr->index];
	पूर्णांक regindex = nr >> 3;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err < 0)
		वापस err;
	अगर (val > 1)
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	अगर (val)
		data->beeps |= (1ULL << nr);
	अन्यथा
		data->beeps &= ~(1ULL << nr);
	nct6775_ग_लिखो_value(data, data->REG_BEEP[regindex],
			    (data->beeps >> (regindex << 3)) & 0xff);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार
show_temp_beep(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sattr = to_sensor_dev_attr(attr);
	काष्ठा nct6775_data *data = nct6775_update_device(dev);
	अचिन्हित पूर्णांक beep = 0;
	पूर्णांक nr;

	/*
	 * For temperatures, there is no fixed mapping from रेजिस्टरs to beep
	 * enable bits. Beep enable bits are determined by the temperature
	 * source mapping.
	 */
	nr = find_temp_source(data, sattr->index, data->num_temp_beeps);
	अगर (nr >= 0) अणु
		पूर्णांक bit = data->BEEP_BITS[nr + TEMP_ALARM_BASE];

		beep = (data->beeps >> bit) & 0x01;
	पूर्ण
	वापस प्र_लिखो(buf, "%u\n", beep);
पूर्ण

अटल sमाप_प्रकार
store_temp_beep(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	काष्ठा nct6775_data *data = dev_get_drvdata(dev);
	पूर्णांक nr, bit, regindex;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err < 0)
		वापस err;
	अगर (val > 1)
		वापस -EINVAL;

	nr = find_temp_source(data, sattr->index, data->num_temp_beeps);
	अगर (nr < 0)
		वापस nr;

	bit = data->BEEP_BITS[nr + TEMP_ALARM_BASE];
	regindex = bit >> 3;

	mutex_lock(&data->update_lock);
	अगर (val)
		data->beeps |= (1ULL << bit);
	अन्यथा
		data->beeps &= ~(1ULL << bit);
	nct6775_ग_लिखो_value(data, data->REG_BEEP[regindex],
			    (data->beeps >> (regindex << 3)) & 0xff);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल umode_t nct6775_in_is_visible(काष्ठा kobject *kobj,
				     काष्ठा attribute *attr, पूर्णांक index)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा nct6775_data *data = dev_get_drvdata(dev);
	पूर्णांक in = index / 5;	/* voltage index */

	अगर (!(data->have_in & BIT(in)))
		वापस 0;

	वापस attr->mode;
पूर्ण

SENSOR_TEMPLATE_2(in_input, "in%d_input", S_IRUGO, show_in_reg, शून्य, 0, 0);
SENSOR_TEMPLATE(in_alarm, "in%d_alarm", S_IRUGO, show_alarm, शून्य, 0);
SENSOR_TEMPLATE(in_beep, "in%d_beep", S_IWUSR | S_IRUGO, show_beep, store_beep,
		0);
SENSOR_TEMPLATE_2(in_min, "in%d_min", S_IWUSR | S_IRUGO, show_in_reg,
		  store_in_reg, 0, 1);
SENSOR_TEMPLATE_2(in_max, "in%d_max", S_IWUSR | S_IRUGO, show_in_reg,
		  store_in_reg, 0, 2);

/*
 * nct6775_in_is_visible uses the index पूर्णांकo the following array
 * to determine अगर attributes should be created or not.
 * Any change in order or content must be matched.
 */
अटल काष्ठा sensor_device_ढाँचा *nct6775_attributes_in_ढाँचा[] = अणु
	&sensor_dev_ढाँचा_in_input,
	&sensor_dev_ढाँचा_in_alarm,
	&sensor_dev_ढाँचा_in_beep,
	&sensor_dev_ढाँचा_in_min,
	&sensor_dev_ढाँचा_in_max,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा sensor_ढाँचा_group nct6775_in_ढाँचा_group = अणु
	.ढाँचाs = nct6775_attributes_in_ढाँचा,
	.is_visible = nct6775_in_is_visible,
पूर्ण;

अटल sमाप_प्रकार
show_fan(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nct6775_data *data = nct6775_update_device(dev);
	काष्ठा sensor_device_attribute *sattr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sattr->index;

	वापस प्र_लिखो(buf, "%d\n", data->rpm[nr]);
पूर्ण

अटल sमाप_प्रकार
show_fan_min(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nct6775_data *data = nct6775_update_device(dev);
	काष्ठा sensor_device_attribute *sattr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sattr->index;

	वापस प्र_लिखो(buf, "%d\n",
		       data->fan_from_reg_min(data->fan_min[nr],
					      data->fan_भाग[nr]));
पूर्ण

अटल sमाप_प्रकार
show_fan_भाग(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nct6775_data *data = nct6775_update_device(dev);
	काष्ठा sensor_device_attribute *sattr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sattr->index;

	वापस प्र_लिखो(buf, "%u\n", भाग_from_reg(data->fan_भाग[nr]));
पूर्ण

अटल sमाप_प्रकार
store_fan_min(काष्ठा device *dev, काष्ठा device_attribute *attr,
	      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा nct6775_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute *sattr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sattr->index;
	अचिन्हित दीर्घ val;
	अचिन्हित पूर्णांक reg;
	u8 new_भाग;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err < 0)
		वापस err;

	mutex_lock(&data->update_lock);
	अगर (!data->has_fan_भाग) अणु
		/* NCT6776F or NCT6779D; we know this is a 13 bit रेजिस्टर */
		अगर (!val) अणु
			val = 0xff1f;
		पूर्ण अन्यथा अणु
			अगर (val > 1350000U)
				val = 135000U;
			val = 1350000U / val;
			val = (val & 0x1f) | ((val << 3) & 0xff00);
		पूर्ण
		data->fan_min[nr] = val;
		जाओ ग_लिखो_min;	/* Leave fan भागider alone */
	पूर्ण
	अगर (!val) अणु
		/* No min limit, alarm disabled */
		data->fan_min[nr] = 255;
		new_भाग = data->fan_भाग[nr]; /* No change */
		dev_info(dev, "fan%u low limit and alarm disabled\n", nr + 1);
		जाओ ग_लिखो_भाग;
	पूर्ण
	reg = 1350000U / val;
	अगर (reg >= 128 * 255) अणु
		/*
		 * Speed below this value cannot possibly be represented,
		 * even with the highest भागider (128)
		 */
		data->fan_min[nr] = 254;
		new_भाग = 7; /* 128 == BIT(7) */
		dev_warn(dev,
			 "fan%u low limit %lu below minimum %u, set to minimum\n",
			 nr + 1, val, data->fan_from_reg_min(254, 7));
	पूर्ण अन्यथा अगर (!reg) अणु
		/*
		 * Speed above this value cannot possibly be represented,
		 * even with the lowest भागider (1)
		 */
		data->fan_min[nr] = 1;
		new_भाग = 0; /* 1 == BIT(0) */
		dev_warn(dev,
			 "fan%u low limit %lu above maximum %u, set to maximum\n",
			 nr + 1, val, data->fan_from_reg_min(1, 0));
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
		data->fan_min[nr] = reg;
	पूर्ण

ग_लिखो_भाग:
	/*
	 * Write both the fan घड़ी भागider (अगर it changed) and the new
	 * fan min (unconditionally)
	 */
	अगर (new_भाग != data->fan_भाग[nr]) अणु
		dev_dbg(dev, "fan%u clock divider changed from %u to %u\n",
			nr + 1, भाग_from_reg(data->fan_भाग[nr]),
			भाग_from_reg(new_भाग));
		data->fan_भाग[nr] = new_भाग;
		nct6775_ग_लिखो_fan_भाग_common(data, nr);
		/* Give the chip समय to sample a new speed value */
		data->last_updated = jअगरfies;
	पूर्ण

ग_लिखो_min:
	nct6775_ग_लिखो_value(data, data->REG_FAN_MIN[nr], data->fan_min[nr]);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार
show_fan_pulses(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nct6775_data *data = nct6775_update_device(dev);
	काष्ठा sensor_device_attribute *sattr = to_sensor_dev_attr(attr);
	पूर्णांक p = data->fan_pulses[sattr->index];

	वापस प्र_लिखो(buf, "%d\n", p ? : 4);
पूर्ण

अटल sमाप_प्रकार
store_fan_pulses(काष्ठा device *dev, काष्ठा device_attribute *attr,
		 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा nct6775_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute *sattr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sattr->index;
	अचिन्हित दीर्घ val;
	पूर्णांक err;
	u8 reg;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err < 0)
		वापस err;

	अगर (val > 4)
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	data->fan_pulses[nr] = val & 3;
	reg = nct6775_पढ़ो_value(data, data->REG_FAN_PULSES[nr]);
	reg &= ~(0x03 << data->FAN_PULSE_SHIFT[nr]);
	reg |= (val & 3) << data->FAN_PULSE_SHIFT[nr];
	nct6775_ग_लिखो_value(data, data->REG_FAN_PULSES[nr], reg);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल umode_t nct6775_fan_is_visible(काष्ठा kobject *kobj,
				      काष्ठा attribute *attr, पूर्णांक index)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा nct6775_data *data = dev_get_drvdata(dev);
	पूर्णांक fan = index / 6;	/* fan index */
	पूर्णांक nr = index % 6;	/* attribute index */

	अगर (!(data->has_fan & BIT(fan)))
		वापस 0;

	अगर (nr == 1 && data->ALARM_BITS[FAN_ALARM_BASE + fan] == -1)
		वापस 0;
	अगर (nr == 2 && data->BEEP_BITS[FAN_ALARM_BASE + fan] == -1)
		वापस 0;
	अगर (nr == 3 && !data->REG_FAN_PULSES[fan])
		वापस 0;
	अगर (nr == 4 && !(data->has_fan_min & BIT(fan)))
		वापस 0;
	अगर (nr == 5 && data->kind != nct6775)
		वापस 0;

	वापस attr->mode;
पूर्ण

SENSOR_TEMPLATE(fan_input, "fan%d_input", S_IRUGO, show_fan, शून्य, 0);
SENSOR_TEMPLATE(fan_alarm, "fan%d_alarm", S_IRUGO, show_alarm, शून्य,
		FAN_ALARM_BASE);
SENSOR_TEMPLATE(fan_beep, "fan%d_beep", S_IWUSR | S_IRUGO, show_beep,
		store_beep, FAN_ALARM_BASE);
SENSOR_TEMPLATE(fan_pulses, "fan%d_pulses", S_IWUSR | S_IRUGO, show_fan_pulses,
		store_fan_pulses, 0);
SENSOR_TEMPLATE(fan_min, "fan%d_min", S_IWUSR | S_IRUGO, show_fan_min,
		store_fan_min, 0);
SENSOR_TEMPLATE(fan_भाग, "fan%d_div", S_IRUGO, show_fan_भाग, शून्य, 0);

/*
 * nct6775_fan_is_visible uses the index पूर्णांकo the following array
 * to determine अगर attributes should be created or not.
 * Any change in order or content must be matched.
 */
अटल काष्ठा sensor_device_ढाँचा *nct6775_attributes_fan_ढाँचा[] = अणु
	&sensor_dev_ढाँचा_fan_input,
	&sensor_dev_ढाँचा_fan_alarm,	/* 1 */
	&sensor_dev_ढाँचा_fan_beep,	/* 2 */
	&sensor_dev_ढाँचा_fan_pulses,
	&sensor_dev_ढाँचा_fan_min,	/* 4 */
	&sensor_dev_ढाँचा_fan_भाग,	/* 5 */
	शून्य
पूर्ण;

अटल स्थिर काष्ठा sensor_ढाँचा_group nct6775_fan_ढाँचा_group = अणु
	.ढाँचाs = nct6775_attributes_fan_ढाँचा,
	.is_visible = nct6775_fan_is_visible,
	.base = 1,
पूर्ण;

अटल sमाप_प्रकार
show_temp_label(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nct6775_data *data = nct6775_update_device(dev);
	काष्ठा sensor_device_attribute *sattr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sattr->index;

	वापस प्र_लिखो(buf, "%s\n", data->temp_label[data->temp_src[nr]]);
पूर्ण

अटल sमाप_प्रकार
show_temp(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nct6775_data *data = nct6775_update_device(dev);
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sattr->nr;
	पूर्णांक index = sattr->index;

	वापस प्र_लिखो(buf, "%d\n", LM75_TEMP_FROM_REG(data->temp[index][nr]));
पूर्ण

अटल sमाप_प्रकार
store_temp(काष्ठा device *dev, काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
	   माप_प्रकार count)
अणु
	काष्ठा nct6775_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sattr->nr;
	पूर्णांक index = sattr->index;
	पूर्णांक err;
	दीर्घ val;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err < 0)
		वापस err;

	mutex_lock(&data->update_lock);
	data->temp[index][nr] = LM75_TEMP_TO_REG(val);
	nct6775_ग_लिखो_temp(data, data->reg_temp[index][nr],
			   data->temp[index][nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार
show_temp_offset(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nct6775_data *data = nct6775_update_device(dev);
	काष्ठा sensor_device_attribute *sattr = to_sensor_dev_attr(attr);

	वापस प्र_लिखो(buf, "%d\n", data->temp_offset[sattr->index] * 1000);
पूर्ण

अटल sमाप_प्रकार
store_temp_offset(काष्ठा device *dev, काष्ठा device_attribute *attr,
		  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा nct6775_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute *sattr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sattr->index;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err < 0)
		वापस err;

	val = clamp_val(DIV_ROUND_CLOSEST(val, 1000), -128, 127);

	mutex_lock(&data->update_lock);
	data->temp_offset[nr] = val;
	nct6775_ग_लिखो_value(data, data->REG_TEMP_OFFSET[nr], val);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार
show_temp_type(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nct6775_data *data = nct6775_update_device(dev);
	काष्ठा sensor_device_attribute *sattr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sattr->index;

	वापस प्र_लिखो(buf, "%d\n", (पूर्णांक)data->temp_type[nr]);
पूर्ण

अटल sमाप_प्रकार
store_temp_type(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा nct6775_data *data = nct6775_update_device(dev);
	काष्ठा sensor_device_attribute *sattr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sattr->index;
	अचिन्हित दीर्घ val;
	पूर्णांक err;
	u8 vbat, diode, vbit, dbit;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err < 0)
		वापस err;

	अगर (val != 1 && val != 3 && val != 4)
		वापस -EINVAL;

	mutex_lock(&data->update_lock);

	data->temp_type[nr] = val;
	vbit = 0x02 << nr;
	dbit = data->DIODE_MASK << nr;
	vbat = nct6775_पढ़ो_value(data, data->REG_VBAT) & ~vbit;
	diode = nct6775_पढ़ो_value(data, data->REG_DIODE) & ~dbit;
	चयन (val) अणु
	हाल 1:	/* CPU diode (diode, current mode) */
		vbat |= vbit;
		diode |= dbit;
		अवरोध;
	हाल 3: /* diode, voltage mode */
		vbat |= dbit;
		अवरोध;
	हाल 4:	/* thermistor */
		अवरोध;
	पूर्ण
	nct6775_ग_लिखो_value(data, data->REG_VBAT, vbat);
	nct6775_ग_लिखो_value(data, data->REG_DIODE, diode);

	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल umode_t nct6775_temp_is_visible(काष्ठा kobject *kobj,
				       काष्ठा attribute *attr, पूर्णांक index)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा nct6775_data *data = dev_get_drvdata(dev);
	पूर्णांक temp = index / 10;	/* temp index */
	पूर्णांक nr = index % 10;	/* attribute index */

	अगर (!(data->have_temp & BIT(temp)))
		वापस 0;

	अगर (nr == 1 && !data->temp_label)
		वापस 0;

	अगर (nr == 2 && find_temp_source(data, temp, data->num_temp_alarms) < 0)
		वापस 0;				/* alarm */

	अगर (nr == 3 && find_temp_source(data, temp, data->num_temp_beeps) < 0)
		वापस 0;				/* beep */

	अगर (nr == 4 && !data->reg_temp[1][temp])	/* max */
		वापस 0;

	अगर (nr == 5 && !data->reg_temp[2][temp])	/* max_hyst */
		वापस 0;

	अगर (nr == 6 && !data->reg_temp[3][temp])	/* crit */
		वापस 0;

	अगर (nr == 7 && !data->reg_temp[4][temp])	/* lcrit */
		वापस 0;

	/* offset and type only apply to fixed sensors */
	अगर (nr > 7 && !(data->have_temp_fixed & BIT(temp)))
		वापस 0;

	वापस attr->mode;
पूर्ण

SENSOR_TEMPLATE_2(temp_input, "temp%d_input", S_IRUGO, show_temp, शून्य, 0, 0);
SENSOR_TEMPLATE(temp_label, "temp%d_label", S_IRUGO, show_temp_label, शून्य, 0);
SENSOR_TEMPLATE_2(temp_max, "temp%d_max", S_IRUGO | S_IWUSR, show_temp,
		  store_temp, 0, 1);
SENSOR_TEMPLATE_2(temp_max_hyst, "temp%d_max_hyst", S_IRUGO | S_IWUSR,
		  show_temp, store_temp, 0, 2);
SENSOR_TEMPLATE_2(temp_crit, "temp%d_crit", S_IRUGO | S_IWUSR, show_temp,
		  store_temp, 0, 3);
SENSOR_TEMPLATE_2(temp_lcrit, "temp%d_lcrit", S_IRUGO | S_IWUSR, show_temp,
		  store_temp, 0, 4);
SENSOR_TEMPLATE(temp_offset, "temp%d_offset", S_IRUGO | S_IWUSR,
		show_temp_offset, store_temp_offset, 0);
SENSOR_TEMPLATE(temp_type, "temp%d_type", S_IRUGO | S_IWUSR, show_temp_type,
		store_temp_type, 0);
SENSOR_TEMPLATE(temp_alarm, "temp%d_alarm", S_IRUGO, show_temp_alarm, शून्य, 0);
SENSOR_TEMPLATE(temp_beep, "temp%d_beep", S_IRUGO | S_IWUSR, show_temp_beep,
		store_temp_beep, 0);

/*
 * nct6775_temp_is_visible uses the index पूर्णांकo the following array
 * to determine अगर attributes should be created or not.
 * Any change in order or content must be matched.
 */
अटल काष्ठा sensor_device_ढाँचा *nct6775_attributes_temp_ढाँचा[] = अणु
	&sensor_dev_ढाँचा_temp_input,
	&sensor_dev_ढाँचा_temp_label,
	&sensor_dev_ढाँचा_temp_alarm,	/* 2 */
	&sensor_dev_ढाँचा_temp_beep,		/* 3 */
	&sensor_dev_ढाँचा_temp_max,		/* 4 */
	&sensor_dev_ढाँचा_temp_max_hyst,	/* 5 */
	&sensor_dev_ढाँचा_temp_crit,		/* 6 */
	&sensor_dev_ढाँचा_temp_lcrit,	/* 7 */
	&sensor_dev_ढाँचा_temp_offset,	/* 8 */
	&sensor_dev_ढाँचा_temp_type,		/* 9 */
	शून्य
पूर्ण;

अटल स्थिर काष्ठा sensor_ढाँचा_group nct6775_temp_ढाँचा_group = अणु
	.ढाँचाs = nct6775_attributes_temp_ढाँचा,
	.is_visible = nct6775_temp_is_visible,
	.base = 1,
पूर्ण;

अटल sमाप_प्रकार
show_pwm_mode(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nct6775_data *data = nct6775_update_device(dev);
	काष्ठा sensor_device_attribute *sattr = to_sensor_dev_attr(attr);

	वापस प्र_लिखो(buf, "%d\n", data->pwm_mode[sattr->index]);
पूर्ण

अटल sमाप_प्रकार
store_pwm_mode(काष्ठा device *dev, काष्ठा device_attribute *attr,
	       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा nct6775_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute *sattr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sattr->index;
	अचिन्हित दीर्घ val;
	पूर्णांक err;
	u8 reg;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err < 0)
		वापस err;

	अगर (val > 1)
		वापस -EINVAL;

	/* Setting DC mode (0) is not supported क्रम all chips/channels */
	अगर (data->REG_PWM_MODE[nr] == 0) अणु
		अगर (!val)
			वापस -EINVAL;
		वापस count;
	पूर्ण

	mutex_lock(&data->update_lock);
	data->pwm_mode[nr] = val;
	reg = nct6775_पढ़ो_value(data, data->REG_PWM_MODE[nr]);
	reg &= ~data->PWM_MODE_MASK[nr];
	अगर (!val)
		reg |= data->PWM_MODE_MASK[nr];
	nct6775_ग_लिखो_value(data, data->REG_PWM_MODE[nr], reg);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार
show_pwm(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nct6775_data *data = nct6775_update_device(dev);
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sattr->nr;
	पूर्णांक index = sattr->index;
	पूर्णांक pwm;

	/*
	 * For स्वतःmatic fan control modes, show current pwm पढ़ोings.
	 * Otherwise, show the configured value.
	 */
	अगर (index == 0 && data->pwm_enable[nr] > manual)
		pwm = nct6775_पढ़ो_value(data, data->REG_PWM_READ[nr]);
	अन्यथा
		pwm = data->pwm[index][nr];

	वापस प्र_लिखो(buf, "%d\n", pwm);
पूर्ण

अटल sमाप_प्रकार
store_pwm(काष्ठा device *dev, काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
	  माप_प्रकार count)
अणु
	काष्ठा nct6775_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sattr->nr;
	पूर्णांक index = sattr->index;
	अचिन्हित दीर्घ val;
	पूर्णांक minval[7] = अणु 0, 1, 1, data->pwm[2][nr], 0, 0, 0 पूर्ण;
	पूर्णांक maxval[7]
	  = अणु 255, 255, data->pwm[3][nr] ? : 255, 255, 255, 255, 255 पूर्ण;
	पूर्णांक err;
	u8 reg;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err < 0)
		वापस err;
	val = clamp_val(val, minval[index], maxval[index]);

	mutex_lock(&data->update_lock);
	data->pwm[index][nr] = val;
	nct6775_ग_लिखो_value(data, data->REG_PWM[index][nr], val);
	अगर (index == 2)	अणु /* न्यूनमान: disable अगर val == 0 */
		reg = nct6775_पढ़ो_value(data, data->REG_TEMP_SEL[nr]);
		reg &= 0x7f;
		अगर (val)
			reg |= 0x80;
		nct6775_ग_लिखो_value(data, data->REG_TEMP_SEL[nr], reg);
	पूर्ण
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

/* Returns 0 अगर OK, -EINVAL otherwise */
अटल पूर्णांक check_trip_poपूर्णांकs(काष्ठा nct6775_data *data, पूर्णांक nr)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < data->स्वतः_pwm_num - 1; i++) अणु
		अगर (data->स्वतः_temp[nr][i] > data->स्वतः_temp[nr][i + 1])
			वापस -EINVAL;
	पूर्ण
	क्रम (i = 0; i < data->स्वतः_pwm_num - 1; i++) अणु
		अगर (data->स्वतः_pwm[nr][i] > data->स्वतः_pwm[nr][i + 1])
			वापस -EINVAL;
	पूर्ण
	/* validate critical temperature and pwm अगर enabled (pwm > 0) */
	अगर (data->स्वतः_pwm[nr][data->स्वतः_pwm_num]) अणु
		अगर (data->स्वतः_temp[nr][data->स्वतः_pwm_num - 1] >
				data->स्वतः_temp[nr][data->स्वतः_pwm_num] ||
		    data->स्वतः_pwm[nr][data->स्वतः_pwm_num - 1] >
				data->स्वतः_pwm[nr][data->स्वतः_pwm_num])
			वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम pwm_update_रेजिस्टरs(काष्ठा nct6775_data *data, पूर्णांक nr)
अणु
	u8 reg;

	चयन (data->pwm_enable[nr]) अणु
	हाल off:
	हाल manual:
		अवरोध;
	हाल speed_cruise:
		reg = nct6775_पढ़ो_value(data, data->REG_FAN_MODE[nr]);
		reg = (reg & ~data->tolerance_mask) |
		  (data->target_speed_tolerance[nr] & data->tolerance_mask);
		nct6775_ग_लिखो_value(data, data->REG_FAN_MODE[nr], reg);
		nct6775_ग_लिखो_value(data, data->REG_TARGET[nr],
				    data->target_speed[nr] & 0xff);
		अगर (data->REG_TOLERANCE_H) अणु
			reg = (data->target_speed[nr] >> 8) & 0x0f;
			reg |= (data->target_speed_tolerance[nr] & 0x38) << 1;
			nct6775_ग_लिखो_value(data,
					    data->REG_TOLERANCE_H[nr],
					    reg);
		पूर्ण
		अवरोध;
	हाल thermal_cruise:
		nct6775_ग_लिखो_value(data, data->REG_TARGET[nr],
				    data->target_temp[nr]);
		fallthrough;
	शेष:
		reg = nct6775_पढ़ो_value(data, data->REG_FAN_MODE[nr]);
		reg = (reg & ~data->tolerance_mask) |
		  data->temp_tolerance[0][nr];
		nct6775_ग_लिखो_value(data, data->REG_FAN_MODE[nr], reg);
		अवरोध;
	पूर्ण
पूर्ण

अटल sमाप_प्रकार
show_pwm_enable(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nct6775_data *data = nct6775_update_device(dev);
	काष्ठा sensor_device_attribute *sattr = to_sensor_dev_attr(attr);

	वापस प्र_लिखो(buf, "%d\n", data->pwm_enable[sattr->index]);
पूर्ण

अटल sमाप_प्रकार
store_pwm_enable(काष्ठा device *dev, काष्ठा device_attribute *attr,
		 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा nct6775_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute *sattr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sattr->index;
	अचिन्हित दीर्घ val;
	पूर्णांक err;
	u16 reg;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err < 0)
		वापस err;

	अगर (val > sf4)
		वापस -EINVAL;

	अगर (val == sf3 && data->kind != nct6775)
		वापस -EINVAL;

	अगर (val == sf4 && check_trip_poपूर्णांकs(data, nr)) अणु
		dev_err(dev, "Inconsistent trip points, not switching to SmartFan IV mode\n");
		dev_err(dev, "Adjust trip points and try again\n");
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&data->update_lock);
	data->pwm_enable[nr] = val;
	अगर (val == off) अणु
		/*
		 * turn off pwm control: select manual mode, set pwm to maximum
		 */
		data->pwm[0][nr] = 255;
		nct6775_ग_लिखो_value(data, data->REG_PWM[0][nr], 255);
	पूर्ण
	pwm_update_रेजिस्टरs(data, nr);
	reg = nct6775_पढ़ो_value(data, data->REG_FAN_MODE[nr]);
	reg &= 0x0f;
	reg |= pwm_enable_to_reg(val) << 4;
	nct6775_ग_लिखो_value(data, data->REG_FAN_MODE[nr], reg);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार
show_pwm_temp_sel_common(काष्ठा nct6775_data *data, अक्षर *buf, पूर्णांक src)
अणु
	पूर्णांक i, sel = 0;

	क्रम (i = 0; i < NUM_TEMP; i++) अणु
		अगर (!(data->have_temp & BIT(i)))
			जारी;
		अगर (src == data->temp_src[i]) अणु
			sel = i + 1;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस प्र_लिखो(buf, "%d\n", sel);
पूर्ण

अटल sमाप_प्रकार
show_pwm_temp_sel(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nct6775_data *data = nct6775_update_device(dev);
	काष्ठा sensor_device_attribute *sattr = to_sensor_dev_attr(attr);
	पूर्णांक index = sattr->index;

	वापस show_pwm_temp_sel_common(data, buf, data->pwm_temp_sel[index]);
पूर्ण

अटल sमाप_प्रकार
store_pwm_temp_sel(काष्ठा device *dev, काष्ठा device_attribute *attr,
		   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा nct6775_data *data = nct6775_update_device(dev);
	काष्ठा sensor_device_attribute *sattr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sattr->index;
	अचिन्हित दीर्घ val;
	पूर्णांक err, reg, src;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err < 0)
		वापस err;
	अगर (val == 0 || val > NUM_TEMP)
		वापस -EINVAL;
	अगर (!(data->have_temp & BIT(val - 1)) || !data->temp_src[val - 1])
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	src = data->temp_src[val - 1];
	data->pwm_temp_sel[nr] = src;
	reg = nct6775_पढ़ो_value(data, data->REG_TEMP_SEL[nr]);
	reg &= 0xe0;
	reg |= src;
	nct6775_ग_लिखो_value(data, data->REG_TEMP_SEL[nr], reg);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार
show_pwm_weight_temp_sel(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा nct6775_data *data = nct6775_update_device(dev);
	काष्ठा sensor_device_attribute *sattr = to_sensor_dev_attr(attr);
	पूर्णांक index = sattr->index;

	वापस show_pwm_temp_sel_common(data, buf,
					data->pwm_weight_temp_sel[index]);
पूर्ण

अटल sमाप_प्रकार
store_pwm_weight_temp_sel(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा nct6775_data *data = nct6775_update_device(dev);
	काष्ठा sensor_device_attribute *sattr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sattr->index;
	अचिन्हित दीर्घ val;
	पूर्णांक err, reg, src;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err < 0)
		वापस err;
	अगर (val > NUM_TEMP)
		वापस -EINVAL;
	val = array_index_nospec(val, NUM_TEMP + 1);
	अगर (val && (!(data->have_temp & BIT(val - 1)) ||
		    !data->temp_src[val - 1]))
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	अगर (val) अणु
		src = data->temp_src[val - 1];
		data->pwm_weight_temp_sel[nr] = src;
		reg = nct6775_पढ़ो_value(data, data->REG_WEIGHT_TEMP_SEL[nr]);
		reg &= 0xe0;
		reg |= (src | 0x80);
		nct6775_ग_लिखो_value(data, data->REG_WEIGHT_TEMP_SEL[nr], reg);
	पूर्ण अन्यथा अणु
		data->pwm_weight_temp_sel[nr] = 0;
		reg = nct6775_पढ़ो_value(data, data->REG_WEIGHT_TEMP_SEL[nr]);
		reg &= 0x7f;
		nct6775_ग_लिखो_value(data, data->REG_WEIGHT_TEMP_SEL[nr], reg);
	पूर्ण
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार
show_target_temp(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nct6775_data *data = nct6775_update_device(dev);
	काष्ठा sensor_device_attribute *sattr = to_sensor_dev_attr(attr);

	वापस प्र_लिखो(buf, "%d\n", data->target_temp[sattr->index] * 1000);
पूर्ण

अटल sमाप_प्रकार
store_target_temp(काष्ठा device *dev, काष्ठा device_attribute *attr,
		  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा nct6775_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute *sattr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sattr->index;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err < 0)
		वापस err;

	val = clamp_val(DIV_ROUND_CLOSEST(val, 1000), 0,
			data->target_temp_mask);

	mutex_lock(&data->update_lock);
	data->target_temp[nr] = val;
	pwm_update_रेजिस्टरs(data, nr);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार
show_target_speed(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nct6775_data *data = nct6775_update_device(dev);
	काष्ठा sensor_device_attribute *sattr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sattr->index;

	वापस प्र_लिखो(buf, "%d\n",
		       fan_from_reg16(data->target_speed[nr],
				      data->fan_भाग[nr]));
पूर्ण

अटल sमाप_प्रकार
store_target_speed(काष्ठा device *dev, काष्ठा device_attribute *attr,
		   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा nct6775_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute *sattr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sattr->index;
	अचिन्हित दीर्घ val;
	पूर्णांक err;
	u16 speed;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err < 0)
		वापस err;

	val = clamp_val(val, 0, 1350000U);
	speed = fan_to_reg(val, data->fan_भाग[nr]);

	mutex_lock(&data->update_lock);
	data->target_speed[nr] = speed;
	pwm_update_रेजिस्टरs(data, nr);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार
show_temp_tolerance(काष्ठा device *dev, काष्ठा device_attribute *attr,
		    अक्षर *buf)
अणु
	काष्ठा nct6775_data *data = nct6775_update_device(dev);
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sattr->nr;
	पूर्णांक index = sattr->index;

	वापस प्र_लिखो(buf, "%d\n", data->temp_tolerance[index][nr] * 1000);
पूर्ण

अटल sमाप_प्रकार
store_temp_tolerance(काष्ठा device *dev, काष्ठा device_attribute *attr,
		     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा nct6775_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sattr->nr;
	पूर्णांक index = sattr->index;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err < 0)
		वापस err;

	/* Limit tolerance as needed */
	val = clamp_val(DIV_ROUND_CLOSEST(val, 1000), 0, data->tolerance_mask);

	mutex_lock(&data->update_lock);
	data->temp_tolerance[index][nr] = val;
	अगर (index)
		pwm_update_रेजिस्टरs(data, nr);
	अन्यथा
		nct6775_ग_लिखो_value(data,
				    data->REG_CRITICAL_TEMP_TOLERANCE[nr],
				    val);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

/*
 * Fan speed tolerance is a tricky beast, since the associated रेजिस्टर is
 * a tick counter, but the value is reported and configured as rpm.
 * Compute resulting low and high rpm values and report the dअगरference.
 * A fan speed tolerance only makes sense अगर a fan target speed has been
 * configured, so only display values other than 0 अगर that is the हाल.
 */
अटल sमाप_प्रकार
show_speed_tolerance(काष्ठा device *dev, काष्ठा device_attribute *attr,
		     अक्षर *buf)
अणु
	काष्ठा nct6775_data *data = nct6775_update_device(dev);
	काष्ठा sensor_device_attribute *sattr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sattr->index;
	पूर्णांक target = data->target_speed[nr];
	पूर्णांक tolerance = 0;

	अगर (target) अणु
		पूर्णांक low = target - data->target_speed_tolerance[nr];
		पूर्णांक high = target + data->target_speed_tolerance[nr];

		अगर (low <= 0)
			low = 1;
		अगर (high > 0xffff)
			high = 0xffff;
		अगर (high < low)
			high = low;

		tolerance = (fan_from_reg16(low, data->fan_भाग[nr])
			     - fan_from_reg16(high, data->fan_भाग[nr])) / 2;
	पूर्ण

	वापस प्र_लिखो(buf, "%d\n", tolerance);
पूर्ण

अटल sमाप_प्रकार
store_speed_tolerance(काष्ठा device *dev, काष्ठा device_attribute *attr,
		      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा nct6775_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute *sattr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sattr->index;
	अचिन्हित दीर्घ val;
	पूर्णांक err;
	पूर्णांक low, high;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err < 0)
		वापस err;

	high = fan_from_reg16(data->target_speed[nr],
			      data->fan_भाग[nr]) + val;
	low = fan_from_reg16(data->target_speed[nr],
			     data->fan_भाग[nr]) - val;
	अगर (low <= 0)
		low = 1;
	अगर (high < low)
		high = low;

	val = (fan_to_reg(low, data->fan_भाग[nr]) -
	       fan_to_reg(high, data->fan_भाग[nr])) / 2;

	/* Limit tolerance as needed */
	val = clamp_val(val, 0, data->speed_tolerance_limit);

	mutex_lock(&data->update_lock);
	data->target_speed_tolerance[nr] = val;
	pwm_update_रेजिस्टरs(data, nr);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

SENSOR_TEMPLATE_2(pwm, "pwm%d", S_IWUSR | S_IRUGO, show_pwm, store_pwm, 0, 0);
SENSOR_TEMPLATE(pwm_mode, "pwm%d_mode", S_IWUSR | S_IRUGO, show_pwm_mode,
		store_pwm_mode, 0);
SENSOR_TEMPLATE(pwm_enable, "pwm%d_enable", S_IWUSR | S_IRUGO, show_pwm_enable,
		store_pwm_enable, 0);
SENSOR_TEMPLATE(pwm_temp_sel, "pwm%d_temp_sel", S_IWUSR | S_IRUGO,
		show_pwm_temp_sel, store_pwm_temp_sel, 0);
SENSOR_TEMPLATE(pwm_target_temp, "pwm%d_target_temp", S_IWUSR | S_IRUGO,
		show_target_temp, store_target_temp, 0);
SENSOR_TEMPLATE(fan_target, "fan%d_target", S_IWUSR | S_IRUGO,
		show_target_speed, store_target_speed, 0);
SENSOR_TEMPLATE(fan_tolerance, "fan%d_tolerance", S_IWUSR | S_IRUGO,
		show_speed_tolerance, store_speed_tolerance, 0);

/* Smart Fan रेजिस्टरs */

अटल sमाप_प्रकार
show_weight_temp(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nct6775_data *data = nct6775_update_device(dev);
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sattr->nr;
	पूर्णांक index = sattr->index;

	वापस प्र_लिखो(buf, "%d\n", data->weight_temp[index][nr] * 1000);
पूर्ण

अटल sमाप_प्रकार
store_weight_temp(काष्ठा device *dev, काष्ठा device_attribute *attr,
		  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा nct6775_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sattr->nr;
	पूर्णांक index = sattr->index;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err < 0)
		वापस err;

	val = clamp_val(DIV_ROUND_CLOSEST(val, 1000), 0, 255);

	mutex_lock(&data->update_lock);
	data->weight_temp[index][nr] = val;
	nct6775_ग_लिखो_value(data, data->REG_WEIGHT_TEMP[index][nr], val);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

SENSOR_TEMPLATE(pwm_weight_temp_sel, "pwm%d_weight_temp_sel", S_IWUSR | S_IRUGO,
		  show_pwm_weight_temp_sel, store_pwm_weight_temp_sel, 0);
SENSOR_TEMPLATE_2(pwm_weight_temp_step, "pwm%d_weight_temp_step",
		  S_IWUSR | S_IRUGO, show_weight_temp, store_weight_temp, 0, 0);
SENSOR_TEMPLATE_2(pwm_weight_temp_step_tol, "pwm%d_weight_temp_step_tol",
		  S_IWUSR | S_IRUGO, show_weight_temp, store_weight_temp, 0, 1);
SENSOR_TEMPLATE_2(pwm_weight_temp_step_base, "pwm%d_weight_temp_step_base",
		  S_IWUSR | S_IRUGO, show_weight_temp, store_weight_temp, 0, 2);
SENSOR_TEMPLATE_2(pwm_weight_duty_step, "pwm%d_weight_duty_step",
		  S_IWUSR | S_IRUGO, show_pwm, store_pwm, 0, 5);
SENSOR_TEMPLATE_2(pwm_weight_duty_base, "pwm%d_weight_duty_base",
		  S_IWUSR | S_IRUGO, show_pwm, store_pwm, 0, 6);

अटल sमाप_प्रकार
show_fan_समय(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nct6775_data *data = nct6775_update_device(dev);
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sattr->nr;
	पूर्णांक index = sattr->index;

	वापस प्र_लिखो(buf, "%d\n",
		       step_समय_from_reg(data->fan_समय[index][nr],
					  data->pwm_mode[nr]));
पूर्ण

अटल sमाप_प्रकार
store_fan_समय(काष्ठा device *dev, काष्ठा device_attribute *attr,
	       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा nct6775_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sattr->nr;
	पूर्णांक index = sattr->index;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err < 0)
		वापस err;

	val = step_समय_प्रकारo_reg(val, data->pwm_mode[nr]);
	mutex_lock(&data->update_lock);
	data->fan_समय[index][nr] = val;
	nct6775_ग_लिखो_value(data, data->REG_FAN_TIME[index][nr], val);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार
show_स्वतः_pwm(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nct6775_data *data = nct6775_update_device(dev);
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);

	वापस प्र_लिखो(buf, "%d\n", data->स्वतः_pwm[sattr->nr][sattr->index]);
पूर्ण

अटल sमाप_प्रकार
store_स्वतः_pwm(काष्ठा device *dev, काष्ठा device_attribute *attr,
	       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा nct6775_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sattr->nr;
	पूर्णांक poपूर्णांक = sattr->index;
	अचिन्हित दीर्घ val;
	पूर्णांक err;
	u8 reg;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err < 0)
		वापस err;
	अगर (val > 255)
		वापस -EINVAL;

	अगर (poपूर्णांक == data->स्वतः_pwm_num) अणु
		अगर (data->kind != nct6775 && !val)
			वापस -EINVAL;
		अगर (data->kind != nct6779 && val)
			val = 0xff;
	पूर्ण

	mutex_lock(&data->update_lock);
	data->स्वतः_pwm[nr][poपूर्णांक] = val;
	अगर (poपूर्णांक < data->स्वतः_pwm_num) अणु
		nct6775_ग_लिखो_value(data,
				    NCT6775_AUTO_PWM(data, nr, poपूर्णांक),
				    data->स्वतः_pwm[nr][poपूर्णांक]);
	पूर्ण अन्यथा अणु
		चयन (data->kind) अणु
		हाल nct6775:
			/* disable अगर needed (pwm == 0) */
			reg = nct6775_पढ़ो_value(data,
						 NCT6775_REG_CRITICAL_ENAB[nr]);
			अगर (val)
				reg |= 0x02;
			अन्यथा
				reg &= ~0x02;
			nct6775_ग_लिखो_value(data, NCT6775_REG_CRITICAL_ENAB[nr],
					    reg);
			अवरोध;
		हाल nct6776:
			अवरोध; /* always enabled, nothing to करो */
		हाल nct6106:
		हाल nct6116:
		हाल nct6779:
		हाल nct6791:
		हाल nct6792:
		हाल nct6793:
		हाल nct6795:
		हाल nct6796:
		हाल nct6797:
		हाल nct6798:
			nct6775_ग_लिखो_value(data, data->REG_CRITICAL_PWM[nr],
					    val);
			reg = nct6775_पढ़ो_value(data,
					data->REG_CRITICAL_PWM_ENABLE[nr]);
			अगर (val == 255)
				reg &= ~data->CRITICAL_PWM_ENABLE_MASK;
			अन्यथा
				reg |= data->CRITICAL_PWM_ENABLE_MASK;
			nct6775_ग_लिखो_value(data,
					    data->REG_CRITICAL_PWM_ENABLE[nr],
					    reg);
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार
show_स्वतः_temp(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nct6775_data *data = nct6775_update_device(dev);
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sattr->nr;
	पूर्णांक poपूर्णांक = sattr->index;

	/*
	 * We करोn't know क्रम sure अगर the temperature is चिन्हित or अचिन्हित.
	 * Assume it is अचिन्हित.
	 */
	वापस प्र_लिखो(buf, "%d\n", data->स्वतः_temp[nr][poपूर्णांक] * 1000);
पूर्ण

अटल sमाप_प्रकार
store_स्वतः_temp(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा nct6775_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sattr->nr;
	पूर्णांक poपूर्णांक = sattr->index;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;
	अगर (val > 255000)
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	data->स्वतः_temp[nr][poपूर्णांक] = DIV_ROUND_CLOSEST(val, 1000);
	अगर (poपूर्णांक < data->स्वतः_pwm_num) अणु
		nct6775_ग_लिखो_value(data,
				    NCT6775_AUTO_TEMP(data, nr, poपूर्णांक),
				    data->स्वतः_temp[nr][poपूर्णांक]);
	पूर्ण अन्यथा अणु
		nct6775_ग_लिखो_value(data, data->REG_CRITICAL_TEMP[nr],
				    data->स्वतः_temp[nr][poपूर्णांक]);
	पूर्ण
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल umode_t nct6775_pwm_is_visible(काष्ठा kobject *kobj,
				      काष्ठा attribute *attr, पूर्णांक index)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा nct6775_data *data = dev_get_drvdata(dev);
	पूर्णांक pwm = index / 36;	/* pwm index */
	पूर्णांक nr = index % 36;	/* attribute index */

	अगर (!(data->has_pwm & BIT(pwm)))
		वापस 0;

	अगर ((nr >= 14 && nr <= 18) || nr == 21)   /* weight */
		अगर (!data->REG_WEIGHT_TEMP_SEL[pwm])
			वापस 0;
	अगर (nr == 19 && data->REG_PWM[3] == शून्य) /* pwm_max */
		वापस 0;
	अगर (nr == 20 && data->REG_PWM[4] == शून्य) /* pwm_step */
		वापस 0;
	अगर (nr == 21 && data->REG_PWM[6] == शून्य) /* weight_duty_base */
		वापस 0;

	अगर (nr >= 22 && nr <= 35) अणु		/* स्वतः poपूर्णांक */
		पूर्णांक api = (nr - 22) / 2;	/* स्वतः poपूर्णांक index */

		अगर (api > data->स्वतः_pwm_num)
			वापस 0;
	पूर्ण
	वापस attr->mode;
पूर्ण

SENSOR_TEMPLATE_2(pwm_stop_समय, "pwm%d_stop_time", S_IWUSR | S_IRUGO,
		  show_fan_समय, store_fan_समय, 0, 0);
SENSOR_TEMPLATE_2(pwm_step_up_समय, "pwm%d_step_up_time", S_IWUSR | S_IRUGO,
		  show_fan_समय, store_fan_समय, 0, 1);
SENSOR_TEMPLATE_2(pwm_step_करोwn_समय, "pwm%d_step_down_time", S_IWUSR | S_IRUGO,
		  show_fan_समय, store_fan_समय, 0, 2);
SENSOR_TEMPLATE_2(pwm_start, "pwm%d_start", S_IWUSR | S_IRUGO, show_pwm,
		  store_pwm, 0, 1);
SENSOR_TEMPLATE_2(pwm_न्यूनमान, "pwm%d_floor", S_IWUSR | S_IRUGO, show_pwm,
		  store_pwm, 0, 2);
SENSOR_TEMPLATE_2(pwm_temp_tolerance, "pwm%d_temp_tolerance", S_IWUSR | S_IRUGO,
		  show_temp_tolerance, store_temp_tolerance, 0, 0);
SENSOR_TEMPLATE_2(pwm_crit_temp_tolerance, "pwm%d_crit_temp_tolerance",
		  S_IWUSR | S_IRUGO, show_temp_tolerance, store_temp_tolerance,
		  0, 1);

SENSOR_TEMPLATE_2(pwm_max, "pwm%d_max", S_IWUSR | S_IRUGO, show_pwm, store_pwm,
		  0, 3);

SENSOR_TEMPLATE_2(pwm_step, "pwm%d_step", S_IWUSR | S_IRUGO, show_pwm,
		  store_pwm, 0, 4);

SENSOR_TEMPLATE_2(pwm_स्वतः_poपूर्णांक1_pwm, "pwm%d_auto_point1_pwm",
		  S_IWUSR | S_IRUGO, show_स्वतः_pwm, store_स्वतः_pwm, 0, 0);
SENSOR_TEMPLATE_2(pwm_स्वतः_poपूर्णांक1_temp, "pwm%d_auto_point1_temp",
		  S_IWUSR | S_IRUGO, show_स्वतः_temp, store_स्वतः_temp, 0, 0);

SENSOR_TEMPLATE_2(pwm_स्वतः_poपूर्णांक2_pwm, "pwm%d_auto_point2_pwm",
		  S_IWUSR | S_IRUGO, show_स्वतः_pwm, store_स्वतः_pwm, 0, 1);
SENSOR_TEMPLATE_2(pwm_स्वतः_poपूर्णांक2_temp, "pwm%d_auto_point2_temp",
		  S_IWUSR | S_IRUGO, show_स्वतः_temp, store_स्वतः_temp, 0, 1);

SENSOR_TEMPLATE_2(pwm_स्वतः_poपूर्णांक3_pwm, "pwm%d_auto_point3_pwm",
		  S_IWUSR | S_IRUGO, show_स्वतः_pwm, store_स्वतः_pwm, 0, 2);
SENSOR_TEMPLATE_2(pwm_स्वतः_poपूर्णांक3_temp, "pwm%d_auto_point3_temp",
		  S_IWUSR | S_IRUGO, show_स्वतः_temp, store_स्वतः_temp, 0, 2);

SENSOR_TEMPLATE_2(pwm_स्वतः_poपूर्णांक4_pwm, "pwm%d_auto_point4_pwm",
		  S_IWUSR | S_IRUGO, show_स्वतः_pwm, store_स्वतः_pwm, 0, 3);
SENSOR_TEMPLATE_2(pwm_स्वतः_poपूर्णांक4_temp, "pwm%d_auto_point4_temp",
		  S_IWUSR | S_IRUGO, show_स्वतः_temp, store_स्वतः_temp, 0, 3);

SENSOR_TEMPLATE_2(pwm_स्वतः_poपूर्णांक5_pwm, "pwm%d_auto_point5_pwm",
		  S_IWUSR | S_IRUGO, show_स्वतः_pwm, store_स्वतः_pwm, 0, 4);
SENSOR_TEMPLATE_2(pwm_स्वतः_poपूर्णांक5_temp, "pwm%d_auto_point5_temp",
		  S_IWUSR | S_IRUGO, show_स्वतः_temp, store_स्वतः_temp, 0, 4);

SENSOR_TEMPLATE_2(pwm_स्वतः_poपूर्णांक6_pwm, "pwm%d_auto_point6_pwm",
		  S_IWUSR | S_IRUGO, show_स्वतः_pwm, store_स्वतः_pwm, 0, 5);
SENSOR_TEMPLATE_2(pwm_स्वतः_poपूर्णांक6_temp, "pwm%d_auto_point6_temp",
		  S_IWUSR | S_IRUGO, show_स्वतः_temp, store_स्वतः_temp, 0, 5);

SENSOR_TEMPLATE_2(pwm_स्वतः_poपूर्णांक7_pwm, "pwm%d_auto_point7_pwm",
		  S_IWUSR | S_IRUGO, show_स्वतः_pwm, store_स्वतः_pwm, 0, 6);
SENSOR_TEMPLATE_2(pwm_स्वतः_poपूर्णांक7_temp, "pwm%d_auto_point7_temp",
		  S_IWUSR | S_IRUGO, show_स्वतः_temp, store_स्वतः_temp, 0, 6);

/*
 * nct6775_pwm_is_visible uses the index पूर्णांकo the following array
 * to determine अगर attributes should be created or not.
 * Any change in order or content must be matched.
 */
अटल काष्ठा sensor_device_ढाँचा *nct6775_attributes_pwm_ढाँचा[] = अणु
	&sensor_dev_ढाँचा_pwm,
	&sensor_dev_ढाँचा_pwm_mode,
	&sensor_dev_ढाँचा_pwm_enable,
	&sensor_dev_ढाँचा_pwm_temp_sel,
	&sensor_dev_ढाँचा_pwm_temp_tolerance,
	&sensor_dev_ढाँचा_pwm_crit_temp_tolerance,
	&sensor_dev_ढाँचा_pwm_target_temp,
	&sensor_dev_ढाँचा_fan_target,
	&sensor_dev_ढाँचा_fan_tolerance,
	&sensor_dev_ढाँचा_pwm_stop_समय,
	&sensor_dev_ढाँचा_pwm_step_up_समय,
	&sensor_dev_ढाँचा_pwm_step_करोwn_समय,
	&sensor_dev_ढाँचा_pwm_start,
	&sensor_dev_ढाँचा_pwm_न्यूनमान,
	&sensor_dev_ढाँचा_pwm_weight_temp_sel,	/* 14 */
	&sensor_dev_ढाँचा_pwm_weight_temp_step,
	&sensor_dev_ढाँचा_pwm_weight_temp_step_tol,
	&sensor_dev_ढाँचा_pwm_weight_temp_step_base,
	&sensor_dev_ढाँचा_pwm_weight_duty_step,	/* 18 */
	&sensor_dev_ढाँचा_pwm_max,			/* 19 */
	&sensor_dev_ढाँचा_pwm_step,			/* 20 */
	&sensor_dev_ढाँचा_pwm_weight_duty_base,	/* 21 */
	&sensor_dev_ढाँचा_pwm_स्वतः_poपूर्णांक1_pwm,	/* 22 */
	&sensor_dev_ढाँचा_pwm_स्वतः_poपूर्णांक1_temp,
	&sensor_dev_ढाँचा_pwm_स्वतः_poपूर्णांक2_pwm,
	&sensor_dev_ढाँचा_pwm_स्वतः_poपूर्णांक2_temp,
	&sensor_dev_ढाँचा_pwm_स्वतः_poपूर्णांक3_pwm,
	&sensor_dev_ढाँचा_pwm_स्वतः_poपूर्णांक3_temp,
	&sensor_dev_ढाँचा_pwm_स्वतः_poपूर्णांक4_pwm,
	&sensor_dev_ढाँचा_pwm_स्वतः_poपूर्णांक4_temp,
	&sensor_dev_ढाँचा_pwm_स्वतः_poपूर्णांक5_pwm,
	&sensor_dev_ढाँचा_pwm_स्वतः_poपूर्णांक5_temp,
	&sensor_dev_ढाँचा_pwm_स्वतः_poपूर्णांक6_pwm,
	&sensor_dev_ढाँचा_pwm_स्वतः_poपूर्णांक6_temp,
	&sensor_dev_ढाँचा_pwm_स्वतः_poपूर्णांक7_pwm,
	&sensor_dev_ढाँचा_pwm_स्वतः_poपूर्णांक7_temp,	/* 35 */

	शून्य
पूर्ण;

अटल स्थिर काष्ठा sensor_ढाँचा_group nct6775_pwm_ढाँचा_group = अणु
	.ढाँचाs = nct6775_attributes_pwm_ढाँचा,
	.is_visible = nct6775_pwm_is_visible,
	.base = 1,
पूर्ण;

अटल sमाप_प्रकार
cpu0_vid_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nct6775_data *data = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n", vid_from_reg(data->vid, data->vrm));
पूर्ण

अटल DEVICE_ATTR_RO(cpu0_vid);

/* Case खोलो detection */

अटल sमाप_प्रकार
clear_हालखोलो(काष्ठा device *dev, काष्ठा device_attribute *attr,
	       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा nct6775_data *data = dev_get_drvdata(dev);
	पूर्णांक nr = to_sensor_dev_attr(attr)->index - INTRUSION_ALARM_BASE;
	अचिन्हित दीर्घ val;
	u8 reg;
	पूर्णांक ret;

	अगर (kम_से_अदीर्घ(buf, 10, &val) || val != 0)
		वापस -EINVAL;

	mutex_lock(&data->update_lock);

	/*
	 * Use CR रेजिस्टरs to clear हालखोलो status.
	 * The CR रेजिस्टरs are the same क्रम all chips, and not all chips
	 * support clearing the हालखोलो status through "regular" रेजिस्टरs.
	 */
	ret = superio_enter(data->sioreg);
	अगर (ret) अणु
		count = ret;
		जाओ error;
	पूर्ण

	superio_select(data->sioreg, NCT6775_LD_ACPI);
	reg = superio_inb(data->sioreg, NCT6775_REG_CR_CASEOPEN_CLR[nr]);
	reg |= NCT6775_CR_CASEOPEN_CLR_MASK[nr];
	superio_outb(data->sioreg, NCT6775_REG_CR_CASEOPEN_CLR[nr], reg);
	reg &= ~NCT6775_CR_CASEOPEN_CLR_MASK[nr];
	superio_outb(data->sioreg, NCT6775_REG_CR_CASEOPEN_CLR[nr], reg);
	superio_निकास(data->sioreg);

	data->valid = false;	/* Force cache refresh */
error:
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR(पूर्णांकrusion0_alarm, S_IWUSR | S_IRUGO, show_alarm,
			  clear_हालखोलो, INTRUSION_ALARM_BASE);
अटल SENSOR_DEVICE_ATTR(पूर्णांकrusion1_alarm, S_IWUSR | S_IRUGO, show_alarm,
			  clear_हालखोलो, INTRUSION_ALARM_BASE + 1);
अटल SENSOR_DEVICE_ATTR(पूर्णांकrusion0_beep, S_IWUSR | S_IRUGO, show_beep,
			  store_beep, INTRUSION_ALARM_BASE);
अटल SENSOR_DEVICE_ATTR(पूर्णांकrusion1_beep, S_IWUSR | S_IRUGO, show_beep,
			  store_beep, INTRUSION_ALARM_BASE + 1);
अटल SENSOR_DEVICE_ATTR(beep_enable, S_IWUSR | S_IRUGO, show_beep,
			  store_beep, BEEP_ENABLE_BASE);

अटल umode_t nct6775_other_is_visible(काष्ठा kobject *kobj,
					काष्ठा attribute *attr, पूर्णांक index)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा nct6775_data *data = dev_get_drvdata(dev);

	अगर (index == 0 && !data->have_vid)
		वापस 0;

	अगर (index == 1 || index == 2) अणु
		अगर (data->ALARM_BITS[INTRUSION_ALARM_BASE + index - 1] < 0)
			वापस 0;
	पूर्ण

	अगर (index == 3 || index == 4) अणु
		अगर (data->BEEP_BITS[INTRUSION_ALARM_BASE + index - 3] < 0)
			वापस 0;
	पूर्ण

	वापस attr->mode;
पूर्ण

/*
 * nct6775_other_is_visible uses the index पूर्णांकo the following array
 * to determine अगर attributes should be created or not.
 * Any change in order or content must be matched.
 */
अटल काष्ठा attribute *nct6775_attributes_other[] = अणु
	&dev_attr_cpu0_vid.attr,				/* 0 */
	&sensor_dev_attr_पूर्णांकrusion0_alarm.dev_attr.attr,	/* 1 */
	&sensor_dev_attr_पूर्णांकrusion1_alarm.dev_attr.attr,	/* 2 */
	&sensor_dev_attr_पूर्णांकrusion0_beep.dev_attr.attr,		/* 3 */
	&sensor_dev_attr_पूर्णांकrusion1_beep.dev_attr.attr,		/* 4 */
	&sensor_dev_attr_beep_enable.dev_attr.attr,		/* 5 */

	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group nct6775_group_other = अणु
	.attrs = nct6775_attributes_other,
	.is_visible = nct6775_other_is_visible,
पूर्ण;

अटल अंतरभूत व्योम nct6775_init_device(काष्ठा nct6775_data *data)
अणु
	पूर्णांक i;
	u8 पंचांगp, diode;

	/* Start monitoring अगर needed */
	अगर (data->REG_CONFIG) अणु
		पंचांगp = nct6775_पढ़ो_value(data, data->REG_CONFIG);
		अगर (!(पंचांगp & 0x01))
			nct6775_ग_लिखो_value(data, data->REG_CONFIG, पंचांगp | 0x01);
	पूर्ण

	/* Enable temperature sensors अगर needed */
	क्रम (i = 0; i < NUM_TEMP; i++) अणु
		अगर (!(data->have_temp & BIT(i)))
			जारी;
		अगर (!data->reg_temp_config[i])
			जारी;
		पंचांगp = nct6775_पढ़ो_value(data, data->reg_temp_config[i]);
		अगर (पंचांगp & 0x01)
			nct6775_ग_लिखो_value(data, data->reg_temp_config[i],
					    पंचांगp & 0xfe);
	पूर्ण

	/* Enable VBAT monitoring अगर needed */
	पंचांगp = nct6775_पढ़ो_value(data, data->REG_VBAT);
	अगर (!(पंचांगp & 0x01))
		nct6775_ग_लिखो_value(data, data->REG_VBAT, पंचांगp | 0x01);

	diode = nct6775_पढ़ो_value(data, data->REG_DIODE);

	क्रम (i = 0; i < data->temp_fixed_num; i++) अणु
		अगर (!(data->have_temp_fixed & BIT(i)))
			जारी;
		अगर ((पंचांगp & (data->DIODE_MASK << i)))	/* diode */
			data->temp_type[i]
			  = 3 - ((diode >> i) & data->DIODE_MASK);
		अन्यथा				/* thermistor */
			data->temp_type[i] = 4;
	पूर्ण
पूर्ण

अटल व्योम
nct6775_check_fan_inमाला_दो(काष्ठा nct6775_data *data)
अणु
	bool fan3pin = false, fan4pin = false, fan4min = false;
	bool fan5pin = false, fan6pin = false, fan7pin = false;
	bool pwm3pin = false, pwm4pin = false, pwm5pin = false;
	bool pwm6pin = false, pwm7pin = false;
	पूर्णांक sioreg = data->sioreg;

	/* Store SIO_REG_ENABLE क्रम use during resume */
	superio_select(sioreg, NCT6775_LD_HWM);
	data->sio_reg_enable = superio_inb(sioreg, SIO_REG_ENABLE);

	/* fan4 and fan5 share some pins with the GPIO and serial flash */
	अगर (data->kind == nct6775) अणु
		पूर्णांक cr2c = superio_inb(sioreg, 0x2c);

		fan3pin = cr2c & BIT(6);
		pwm3pin = cr2c & BIT(7);

		/* On NCT6775, fan4 shares pins with the fdc पूर्णांकerface */
		fan4pin = !(superio_inb(sioreg, 0x2A) & 0x80);
	पूर्ण अन्यथा अगर (data->kind == nct6776) अणु
		bool gpok = superio_inb(sioreg, 0x27) & 0x80;
		स्थिर अक्षर *board_venकरोr, *board_name;

		board_venकरोr = dmi_get_प्रणाली_info(DMI_BOARD_VENDOR);
		board_name = dmi_get_प्रणाली_info(DMI_BOARD_NAME);

		अगर (board_name && board_venकरोr &&
		    !म_भेद(board_venकरोr, "ASRock")) अणु
			/*
			 * Auxiliary fan monitoring is not enabled on ASRock
			 * Z77 Pro4-M अगर booted in UEFI Ultra-FastBoot mode.
			 * Observed with BIOS version 2.00.
			 */
			अगर (!म_भेद(board_name, "Z77 Pro4-M")) अणु
				अगर ((data->sio_reg_enable & 0xe0) != 0xe0) अणु
					data->sio_reg_enable |= 0xe0;
					superio_outb(sioreg, SIO_REG_ENABLE,
						     data->sio_reg_enable);
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (data->sio_reg_enable & 0x80)
			fan3pin = gpok;
		अन्यथा
			fan3pin = !(superio_inb(sioreg, 0x24) & 0x40);

		अगर (data->sio_reg_enable & 0x40)
			fan4pin = gpok;
		अन्यथा
			fan4pin = superio_inb(sioreg, 0x1C) & 0x01;

		अगर (data->sio_reg_enable & 0x20)
			fan5pin = gpok;
		अन्यथा
			fan5pin = superio_inb(sioreg, 0x1C) & 0x02;

		fan4min = fan4pin;
		pwm3pin = fan3pin;
	पूर्ण अन्यथा अगर (data->kind == nct6106) अणु
		पूर्णांक cr24 = superio_inb(sioreg, 0x24);

		fan3pin = !(cr24 & 0x80);
		pwm3pin = cr24 & 0x08;
	पूर्ण अन्यथा अगर (data->kind == nct6116) अणु
		पूर्णांक cr1a = superio_inb(sioreg, 0x1a);
		पूर्णांक cr1b = superio_inb(sioreg, 0x1b);
		पूर्णांक cr24 = superio_inb(sioreg, 0x24);
		पूर्णांक cr2a = superio_inb(sioreg, 0x2a);
		पूर्णांक cr2b = superio_inb(sioreg, 0x2b);
		पूर्णांक cr2f = superio_inb(sioreg, 0x2f);

		fan3pin = !(cr2b & 0x10);
		fan4pin = (cr2b & 0x80) ||			// pin 1(2)
			(!(cr2f & 0x10) && (cr1a & 0x04));	// pin 65(66)
		fan5pin = (cr2b & 0x80) ||			// pin 126(127)
			(!(cr1b & 0x03) && (cr2a & 0x02));	// pin 94(96)

		pwm3pin = fan3pin && (cr24 & 0x08);
		pwm4pin = fan4pin;
		pwm5pin = fan5pin;
	पूर्ण अन्यथा अणु
		/*
		 * NCT6779D, NCT6791D, NCT6792D, NCT6793D, NCT6795D, NCT6796D,
		 * NCT6797D, NCT6798D
		 */
		पूर्णांक cr1a = superio_inb(sioreg, 0x1a);
		पूर्णांक cr1b = superio_inb(sioreg, 0x1b);
		पूर्णांक cr1c = superio_inb(sioreg, 0x1c);
		पूर्णांक cr1d = superio_inb(sioreg, 0x1d);
		पूर्णांक cr2a = superio_inb(sioreg, 0x2a);
		पूर्णांक cr2b = superio_inb(sioreg, 0x2b);
		पूर्णांक cr2d = superio_inb(sioreg, 0x2d);
		पूर्णांक cr2f = superio_inb(sioreg, 0x2f);
		bool dsw_en = cr2f & BIT(3);
		bool ddr4_en = cr2f & BIT(4);
		पूर्णांक cre0;
		पूर्णांक creb;
		पूर्णांक cred;

		superio_select(sioreg, NCT6775_LD_12);
		cre0 = superio_inb(sioreg, 0xe0);
		creb = superio_inb(sioreg, 0xeb);
		cred = superio_inb(sioreg, 0xed);

		fan3pin = !(cr1c & BIT(5));
		fan4pin = !(cr1c & BIT(6));
		fan5pin = !(cr1c & BIT(7));

		pwm3pin = !(cr1c & BIT(0));
		pwm4pin = !(cr1c & BIT(1));
		pwm5pin = !(cr1c & BIT(2));

		चयन (data->kind) अणु
		हाल nct6791:
			fan6pin = cr2d & BIT(1);
			pwm6pin = cr2d & BIT(0);
			अवरोध;
		हाल nct6792:
			fan6pin = !dsw_en && (cr2d & BIT(1));
			pwm6pin = !dsw_en && (cr2d & BIT(0));
			अवरोध;
		हाल nct6793:
			fan5pin |= cr1b & BIT(5);
			fan5pin |= creb & BIT(5);

			fan6pin = !dsw_en && (cr2d & BIT(1));
			fan6pin |= creb & BIT(3);

			pwm5pin |= cr2d & BIT(7);
			pwm5pin |= (creb & BIT(4)) && !(cr2a & BIT(0));

			pwm6pin = !dsw_en && (cr2d & BIT(0));
			pwm6pin |= creb & BIT(2);
			अवरोध;
		हाल nct6795:
			fan5pin |= cr1b & BIT(5);
			fan5pin |= creb & BIT(5);

			fan6pin = (cr2a & BIT(4)) &&
					(!dsw_en || (cred & BIT(4)));
			fan6pin |= creb & BIT(3);

			pwm5pin |= cr2d & BIT(7);
			pwm5pin |= (creb & BIT(4)) && !(cr2a & BIT(0));

			pwm6pin = (cr2a & BIT(3)) && (cred & BIT(2));
			pwm6pin |= creb & BIT(2);
			अवरोध;
		हाल nct6796:
			fan5pin |= cr1b & BIT(5);
			fan5pin |= (cre0 & BIT(3)) && !(cr1b & BIT(0));
			fan5pin |= creb & BIT(5);

			fan6pin = (cr2a & BIT(4)) &&
					(!dsw_en || (cred & BIT(4)));
			fan6pin |= creb & BIT(3);

			fan7pin = !(cr2b & BIT(2));

			pwm5pin |= cr2d & BIT(7);
			pwm5pin |= (cre0 & BIT(4)) && !(cr1b & BIT(0));
			pwm5pin |= (creb & BIT(4)) && !(cr2a & BIT(0));

			pwm6pin = (cr2a & BIT(3)) && (cred & BIT(2));
			pwm6pin |= creb & BIT(2);

			pwm7pin = !(cr1d & (BIT(2) | BIT(3)));
			अवरोध;
		हाल nct6797:
			fan5pin |= !ddr4_en && (cr1b & BIT(5));
			fan5pin |= creb & BIT(5);

			fan6pin = cr2a & BIT(4);
			fan6pin |= creb & BIT(3);

			fan7pin = cr1a & BIT(1);

			pwm5pin |= (creb & BIT(4)) && !(cr2a & BIT(0));
			pwm5pin |= !ddr4_en && (cr2d & BIT(7));

			pwm6pin = creb & BIT(2);
			pwm6pin |= cred & BIT(2);

			pwm7pin = cr1d & BIT(4);
			अवरोध;
		हाल nct6798:
			fan6pin = !(cr1b & BIT(0)) && (cre0 & BIT(3));
			fan6pin |= cr2a & BIT(4);
			fan6pin |= creb & BIT(5);

			fan7pin = cr1b & BIT(5);
			fan7pin |= !(cr2b & BIT(2));
			fan7pin |= creb & BIT(3);

			pwm6pin = !(cr1b & BIT(0)) && (cre0 & BIT(4));
			pwm6pin |= !(cred & BIT(2)) && (cr2a & BIT(3));
			pwm6pin |= (creb & BIT(4)) && !(cr2a & BIT(0));

			pwm7pin = !(cr1d & (BIT(2) | BIT(3)));
			pwm7pin |= cr2d & BIT(7);
			pwm7pin |= creb & BIT(2);
			अवरोध;
		शेष:	/* NCT6779D */
			अवरोध;
		पूर्ण

		fan4min = fan4pin;
	पूर्ण

	/* fan 1 and 2 (0x03) are always present */
	data->has_fan = 0x03 | (fan3pin << 2) | (fan4pin << 3) |
		(fan5pin << 4) | (fan6pin << 5) | (fan7pin << 6);
	data->has_fan_min = 0x03 | (fan3pin << 2) | (fan4min << 3) |
		(fan5pin << 4) | (fan6pin << 5) | (fan7pin << 6);
	data->has_pwm = 0x03 | (pwm3pin << 2) | (pwm4pin << 3) |
		(pwm5pin << 4) | (pwm6pin << 5) | (pwm7pin << 6);
पूर्ण

अटल व्योम add_temp_sensors(काष्ठा nct6775_data *data, स्थिर u16 *regp,
			     पूर्णांक *available, पूर्णांक *mask)
अणु
	पूर्णांक i;
	u8 src;

	क्रम (i = 0; i < data->pwm_num && *available; i++) अणु
		पूर्णांक index;

		अगर (!regp[i])
			जारी;
		src = nct6775_पढ़ो_value(data, regp[i]);
		src &= 0x1f;
		अगर (!src || (*mask & BIT(src)))
			जारी;
		अगर (!(data->temp_mask & BIT(src)))
			जारी;

		index = __ffs(*available);
		nct6775_ग_लिखो_value(data, data->REG_TEMP_SOURCE[index], src);
		*available &= ~BIT(index);
		*mask |= BIT(src);
	पूर्ण
पूर्ण

अटल पूर्णांक nct6775_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा nct6775_sio_data *sio_data = dev_get_platdata(dev);
	काष्ठा nct6775_data *data;
	काष्ठा resource *res;
	पूर्णांक i, s, err = 0;
	पूर्णांक src, mask, available;
	स्थिर u16 *reg_temp, *reg_temp_over, *reg_temp_hyst, *reg_temp_config;
	स्थिर u16 *reg_temp_mon, *reg_temp_alternate, *reg_temp_crit;
	स्थिर u16 *reg_temp_crit_l = शून्य, *reg_temp_crit_h = शून्य;
	पूर्णांक num_reg_temp, num_reg_temp_mon;
	u8 cr2a;
	काष्ठा attribute_group *group;
	काष्ठा device *hwmon_dev;
	पूर्णांक num_attr_groups = 0;

	res = platक्रमm_get_resource(pdev, IORESOURCE_IO, 0);
	अगर (!devm_request_region(&pdev->dev, res->start, IOREGION_LENGTH,
				 DRVNAME))
		वापस -EBUSY;

	data = devm_kzalloc(&pdev->dev, माप(काष्ठा nct6775_data),
			    GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->kind = sio_data->kind;
	data->sioreg = sio_data->sioreg;
	data->addr = res->start;
	mutex_init(&data->update_lock);
	data->name = nct6775_device_names[data->kind];
	data->bank = 0xff;		/* Force initial bank selection */
	platक्रमm_set_drvdata(pdev, data);

	चयन (data->kind) अणु
	हाल nct6106:
		data->in_num = 9;
		data->pwm_num = 3;
		data->स्वतः_pwm_num = 4;
		data->temp_fixed_num = 3;
		data->num_temp_alarms = 6;
		data->num_temp_beeps = 6;

		data->fan_from_reg = fan_from_reg13;
		data->fan_from_reg_min = fan_from_reg13;

		data->temp_label = nct6776_temp_label;
		data->temp_mask = NCT6776_TEMP_MASK;
		data->virt_temp_mask = NCT6776_VIRT_TEMP_MASK;

		data->REG_VBAT = NCT6106_REG_VBAT;
		data->REG_DIODE = NCT6106_REG_DIODE;
		data->DIODE_MASK = NCT6106_DIODE_MASK;
		data->REG_VIN = NCT6106_REG_IN;
		data->REG_IN_MINMAX[0] = NCT6106_REG_IN_MIN;
		data->REG_IN_MINMAX[1] = NCT6106_REG_IN_MAX;
		data->REG_TARGET = NCT6106_REG_TARGET;
		data->REG_FAN = NCT6106_REG_FAN;
		data->REG_FAN_MODE = NCT6106_REG_FAN_MODE;
		data->REG_FAN_MIN = NCT6106_REG_FAN_MIN;
		data->REG_FAN_PULSES = NCT6106_REG_FAN_PULSES;
		data->FAN_PULSE_SHIFT = NCT6106_FAN_PULSE_SHIFT;
		data->REG_FAN_TIME[0] = NCT6106_REG_FAN_STOP_TIME;
		data->REG_FAN_TIME[1] = NCT6106_REG_FAN_STEP_UP_TIME;
		data->REG_FAN_TIME[2] = NCT6106_REG_FAN_STEP_DOWN_TIME;
		data->REG_TOLERANCE_H = NCT6106_REG_TOLERANCE_H;
		data->REG_PWM[0] = NCT6116_REG_PWM;
		data->REG_PWM[1] = NCT6106_REG_FAN_START_OUTPUT;
		data->REG_PWM[2] = NCT6106_REG_FAN_STOP_OUTPUT;
		data->REG_PWM[5] = NCT6106_REG_WEIGHT_DUTY_STEP;
		data->REG_PWM[6] = NCT6106_REG_WEIGHT_DUTY_BASE;
		data->REG_PWM_READ = NCT6106_REG_PWM_READ;
		data->REG_PWM_MODE = NCT6106_REG_PWM_MODE;
		data->PWM_MODE_MASK = NCT6106_PWM_MODE_MASK;
		data->REG_AUTO_TEMP = NCT6106_REG_AUTO_TEMP;
		data->REG_AUTO_PWM = NCT6106_REG_AUTO_PWM;
		data->REG_CRITICAL_TEMP = NCT6106_REG_CRITICAL_TEMP;
		data->REG_CRITICAL_TEMP_TOLERANCE
		  = NCT6106_REG_CRITICAL_TEMP_TOLERANCE;
		data->REG_CRITICAL_PWM_ENABLE = NCT6106_REG_CRITICAL_PWM_ENABLE;
		data->CRITICAL_PWM_ENABLE_MASK
		  = NCT6106_CRITICAL_PWM_ENABLE_MASK;
		data->REG_CRITICAL_PWM = NCT6106_REG_CRITICAL_PWM;
		data->REG_TEMP_OFFSET = NCT6106_REG_TEMP_OFFSET;
		data->REG_TEMP_SOURCE = NCT6106_REG_TEMP_SOURCE;
		data->REG_TEMP_SEL = NCT6116_REG_TEMP_SEL;
		data->REG_WEIGHT_TEMP_SEL = NCT6106_REG_WEIGHT_TEMP_SEL;
		data->REG_WEIGHT_TEMP[0] = NCT6106_REG_WEIGHT_TEMP_STEP;
		data->REG_WEIGHT_TEMP[1] = NCT6106_REG_WEIGHT_TEMP_STEP_TOL;
		data->REG_WEIGHT_TEMP[2] = NCT6106_REG_WEIGHT_TEMP_BASE;
		data->REG_ALARM = NCT6106_REG_ALARM;
		data->ALARM_BITS = NCT6106_ALARM_BITS;
		data->REG_BEEP = NCT6106_REG_BEEP;
		data->BEEP_BITS = NCT6106_BEEP_BITS;

		reg_temp = NCT6106_REG_TEMP;
		reg_temp_mon = NCT6106_REG_TEMP_MON;
		num_reg_temp = ARRAY_SIZE(NCT6106_REG_TEMP);
		num_reg_temp_mon = ARRAY_SIZE(NCT6106_REG_TEMP_MON);
		reg_temp_over = NCT6106_REG_TEMP_OVER;
		reg_temp_hyst = NCT6106_REG_TEMP_HYST;
		reg_temp_config = NCT6106_REG_TEMP_CONFIG;
		reg_temp_alternate = NCT6106_REG_TEMP_ALTERNATE;
		reg_temp_crit = NCT6106_REG_TEMP_CRIT;
		reg_temp_crit_l = NCT6106_REG_TEMP_CRIT_L;
		reg_temp_crit_h = NCT6106_REG_TEMP_CRIT_H;

		अवरोध;
	हाल nct6116:
		data->in_num = 9;
		data->pwm_num = 3;
		data->स्वतः_pwm_num = 4;
		data->temp_fixed_num = 3;
		data->num_temp_alarms = 3;
		data->num_temp_beeps = 3;

		data->fan_from_reg = fan_from_reg13;
		data->fan_from_reg_min = fan_from_reg13;

		data->temp_label = nct6776_temp_label;
		data->temp_mask = NCT6776_TEMP_MASK;
		data->virt_temp_mask = NCT6776_VIRT_TEMP_MASK;

		data->REG_VBAT = NCT6106_REG_VBAT;
		data->REG_DIODE = NCT6106_REG_DIODE;
		data->DIODE_MASK = NCT6106_DIODE_MASK;
		data->REG_VIN = NCT6106_REG_IN;
		data->REG_IN_MINMAX[0] = NCT6106_REG_IN_MIN;
		data->REG_IN_MINMAX[1] = NCT6106_REG_IN_MAX;
		data->REG_TARGET = NCT6116_REG_TARGET;
		data->REG_FAN = NCT6116_REG_FAN;
		data->REG_FAN_MODE = NCT6116_REG_FAN_MODE;
		data->REG_FAN_MIN = NCT6116_REG_FAN_MIN;
		data->REG_FAN_PULSES = NCT6116_REG_FAN_PULSES;
		data->FAN_PULSE_SHIFT = NCT6116_FAN_PULSE_SHIFT;
		data->REG_FAN_TIME[0] = NCT6116_REG_FAN_STOP_TIME;
		data->REG_FAN_TIME[1] = NCT6116_REG_FAN_STEP_UP_TIME;
		data->REG_FAN_TIME[2] = NCT6116_REG_FAN_STEP_DOWN_TIME;
		data->REG_TOLERANCE_H = NCT6116_REG_TOLERANCE_H;
		data->REG_PWM[0] = NCT6116_REG_PWM;
		data->REG_PWM[1] = NCT6116_REG_FAN_START_OUTPUT;
		data->REG_PWM[2] = NCT6116_REG_FAN_STOP_OUTPUT;
		data->REG_PWM[5] = NCT6106_REG_WEIGHT_DUTY_STEP;
		data->REG_PWM[6] = NCT6106_REG_WEIGHT_DUTY_BASE;
		data->REG_PWM_READ = NCT6106_REG_PWM_READ;
		data->REG_PWM_MODE = NCT6106_REG_PWM_MODE;
		data->PWM_MODE_MASK = NCT6106_PWM_MODE_MASK;
		data->REG_AUTO_TEMP = NCT6116_REG_AUTO_TEMP;
		data->REG_AUTO_PWM = NCT6116_REG_AUTO_PWM;
		data->REG_CRITICAL_TEMP = NCT6116_REG_CRITICAL_TEMP;
		data->REG_CRITICAL_TEMP_TOLERANCE
		  = NCT6116_REG_CRITICAL_TEMP_TOLERANCE;
		data->REG_CRITICAL_PWM_ENABLE = NCT6116_REG_CRITICAL_PWM_ENABLE;
		data->CRITICAL_PWM_ENABLE_MASK
		  = NCT6106_CRITICAL_PWM_ENABLE_MASK;
		data->REG_CRITICAL_PWM = NCT6116_REG_CRITICAL_PWM;
		data->REG_TEMP_OFFSET = NCT6106_REG_TEMP_OFFSET;
		data->REG_TEMP_SOURCE = NCT6116_REG_TEMP_SOURCE;
		data->REG_TEMP_SEL = NCT6116_REG_TEMP_SEL;
		data->REG_WEIGHT_TEMP_SEL = NCT6106_REG_WEIGHT_TEMP_SEL;
		data->REG_WEIGHT_TEMP[0] = NCT6106_REG_WEIGHT_TEMP_STEP;
		data->REG_WEIGHT_TEMP[1] = NCT6106_REG_WEIGHT_TEMP_STEP_TOL;
		data->REG_WEIGHT_TEMP[2] = NCT6106_REG_WEIGHT_TEMP_BASE;
		data->REG_ALARM = NCT6106_REG_ALARM;
		data->ALARM_BITS = NCT6116_ALARM_BITS;
		data->REG_BEEP = NCT6106_REG_BEEP;
		data->BEEP_BITS = NCT6116_BEEP_BITS;

		reg_temp = NCT6106_REG_TEMP;
		reg_temp_mon = NCT6106_REG_TEMP_MON;
		num_reg_temp = ARRAY_SIZE(NCT6106_REG_TEMP);
		num_reg_temp_mon = ARRAY_SIZE(NCT6106_REG_TEMP_MON);
		reg_temp_over = NCT6106_REG_TEMP_OVER;
		reg_temp_hyst = NCT6106_REG_TEMP_HYST;
		reg_temp_config = NCT6106_REG_TEMP_CONFIG;
		reg_temp_alternate = NCT6106_REG_TEMP_ALTERNATE;
		reg_temp_crit = NCT6106_REG_TEMP_CRIT;
		reg_temp_crit_l = NCT6106_REG_TEMP_CRIT_L;
		reg_temp_crit_h = NCT6106_REG_TEMP_CRIT_H;

		अवरोध;
	हाल nct6775:
		data->in_num = 9;
		data->pwm_num = 3;
		data->स्वतः_pwm_num = 6;
		data->has_fan_भाग = true;
		data->temp_fixed_num = 3;
		data->num_temp_alarms = 3;
		data->num_temp_beeps = 3;

		data->ALARM_BITS = NCT6775_ALARM_BITS;
		data->BEEP_BITS = NCT6775_BEEP_BITS;

		data->fan_from_reg = fan_from_reg16;
		data->fan_from_reg_min = fan_from_reg8;
		data->target_temp_mask = 0x7f;
		data->tolerance_mask = 0x0f;
		data->speed_tolerance_limit = 15;

		data->temp_label = nct6775_temp_label;
		data->temp_mask = NCT6775_TEMP_MASK;
		data->virt_temp_mask = NCT6775_VIRT_TEMP_MASK;

		data->REG_CONFIG = NCT6775_REG_CONFIG;
		data->REG_VBAT = NCT6775_REG_VBAT;
		data->REG_DIODE = NCT6775_REG_DIODE;
		data->DIODE_MASK = NCT6775_DIODE_MASK;
		data->REG_VIN = NCT6775_REG_IN;
		data->REG_IN_MINMAX[0] = NCT6775_REG_IN_MIN;
		data->REG_IN_MINMAX[1] = NCT6775_REG_IN_MAX;
		data->REG_TARGET = NCT6775_REG_TARGET;
		data->REG_FAN = NCT6775_REG_FAN;
		data->REG_FAN_MODE = NCT6775_REG_FAN_MODE;
		data->REG_FAN_MIN = NCT6775_REG_FAN_MIN;
		data->REG_FAN_PULSES = NCT6775_REG_FAN_PULSES;
		data->FAN_PULSE_SHIFT = NCT6775_FAN_PULSE_SHIFT;
		data->REG_FAN_TIME[0] = NCT6775_REG_FAN_STOP_TIME;
		data->REG_FAN_TIME[1] = NCT6775_REG_FAN_STEP_UP_TIME;
		data->REG_FAN_TIME[2] = NCT6775_REG_FAN_STEP_DOWN_TIME;
		data->REG_PWM[0] = NCT6775_REG_PWM;
		data->REG_PWM[1] = NCT6775_REG_FAN_START_OUTPUT;
		data->REG_PWM[2] = NCT6775_REG_FAN_STOP_OUTPUT;
		data->REG_PWM[3] = NCT6775_REG_FAN_MAX_OUTPUT;
		data->REG_PWM[4] = NCT6775_REG_FAN_STEP_OUTPUT;
		data->REG_PWM[5] = NCT6775_REG_WEIGHT_DUTY_STEP;
		data->REG_PWM_READ = NCT6775_REG_PWM_READ;
		data->REG_PWM_MODE = NCT6775_REG_PWM_MODE;
		data->PWM_MODE_MASK = NCT6775_PWM_MODE_MASK;
		data->REG_AUTO_TEMP = NCT6775_REG_AUTO_TEMP;
		data->REG_AUTO_PWM = NCT6775_REG_AUTO_PWM;
		data->REG_CRITICAL_TEMP = NCT6775_REG_CRITICAL_TEMP;
		data->REG_CRITICAL_TEMP_TOLERANCE
		  = NCT6775_REG_CRITICAL_TEMP_TOLERANCE;
		data->REG_TEMP_OFFSET = NCT6775_REG_TEMP_OFFSET;
		data->REG_TEMP_SOURCE = NCT6775_REG_TEMP_SOURCE;
		data->REG_TEMP_SEL = NCT6775_REG_TEMP_SEL;
		data->REG_WEIGHT_TEMP_SEL = NCT6775_REG_WEIGHT_TEMP_SEL;
		data->REG_WEIGHT_TEMP[0] = NCT6775_REG_WEIGHT_TEMP_STEP;
		data->REG_WEIGHT_TEMP[1] = NCT6775_REG_WEIGHT_TEMP_STEP_TOL;
		data->REG_WEIGHT_TEMP[2] = NCT6775_REG_WEIGHT_TEMP_BASE;
		data->REG_ALARM = NCT6775_REG_ALARM;
		data->REG_BEEP = NCT6775_REG_BEEP;

		reg_temp = NCT6775_REG_TEMP;
		reg_temp_mon = NCT6775_REG_TEMP_MON;
		num_reg_temp = ARRAY_SIZE(NCT6775_REG_TEMP);
		num_reg_temp_mon = ARRAY_SIZE(NCT6775_REG_TEMP_MON);
		reg_temp_over = NCT6775_REG_TEMP_OVER;
		reg_temp_hyst = NCT6775_REG_TEMP_HYST;
		reg_temp_config = NCT6775_REG_TEMP_CONFIG;
		reg_temp_alternate = NCT6775_REG_TEMP_ALTERNATE;
		reg_temp_crit = NCT6775_REG_TEMP_CRIT;

		अवरोध;
	हाल nct6776:
		data->in_num = 9;
		data->pwm_num = 3;
		data->स्वतः_pwm_num = 4;
		data->has_fan_भाग = false;
		data->temp_fixed_num = 3;
		data->num_temp_alarms = 3;
		data->num_temp_beeps = 6;

		data->ALARM_BITS = NCT6776_ALARM_BITS;
		data->BEEP_BITS = NCT6776_BEEP_BITS;

		data->fan_from_reg = fan_from_reg13;
		data->fan_from_reg_min = fan_from_reg13;
		data->target_temp_mask = 0xff;
		data->tolerance_mask = 0x07;
		data->speed_tolerance_limit = 63;

		data->temp_label = nct6776_temp_label;
		data->temp_mask = NCT6776_TEMP_MASK;
		data->virt_temp_mask = NCT6776_VIRT_TEMP_MASK;

		data->REG_CONFIG = NCT6775_REG_CONFIG;
		data->REG_VBAT = NCT6775_REG_VBAT;
		data->REG_DIODE = NCT6775_REG_DIODE;
		data->DIODE_MASK = NCT6775_DIODE_MASK;
		data->REG_VIN = NCT6775_REG_IN;
		data->REG_IN_MINMAX[0] = NCT6775_REG_IN_MIN;
		data->REG_IN_MINMAX[1] = NCT6775_REG_IN_MAX;
		data->REG_TARGET = NCT6775_REG_TARGET;
		data->REG_FAN = NCT6775_REG_FAN;
		data->REG_FAN_MODE = NCT6775_REG_FAN_MODE;
		data->REG_FAN_MIN = NCT6776_REG_FAN_MIN;
		data->REG_FAN_PULSES = NCT6776_REG_FAN_PULSES;
		data->FAN_PULSE_SHIFT = NCT6775_FAN_PULSE_SHIFT;
		data->REG_FAN_TIME[0] = NCT6775_REG_FAN_STOP_TIME;
		data->REG_FAN_TIME[1] = NCT6776_REG_FAN_STEP_UP_TIME;
		data->REG_FAN_TIME[2] = NCT6776_REG_FAN_STEP_DOWN_TIME;
		data->REG_TOLERANCE_H = NCT6776_REG_TOLERANCE_H;
		data->REG_PWM[0] = NCT6775_REG_PWM;
		data->REG_PWM[1] = NCT6775_REG_FAN_START_OUTPUT;
		data->REG_PWM[2] = NCT6775_REG_FAN_STOP_OUTPUT;
		data->REG_PWM[5] = NCT6775_REG_WEIGHT_DUTY_STEP;
		data->REG_PWM[6] = NCT6776_REG_WEIGHT_DUTY_BASE;
		data->REG_PWM_READ = NCT6775_REG_PWM_READ;
		data->REG_PWM_MODE = NCT6776_REG_PWM_MODE;
		data->PWM_MODE_MASK = NCT6776_PWM_MODE_MASK;
		data->REG_AUTO_TEMP = NCT6775_REG_AUTO_TEMP;
		data->REG_AUTO_PWM = NCT6775_REG_AUTO_PWM;
		data->REG_CRITICAL_TEMP = NCT6775_REG_CRITICAL_TEMP;
		data->REG_CRITICAL_TEMP_TOLERANCE
		  = NCT6775_REG_CRITICAL_TEMP_TOLERANCE;
		data->REG_TEMP_OFFSET = NCT6775_REG_TEMP_OFFSET;
		data->REG_TEMP_SOURCE = NCT6775_REG_TEMP_SOURCE;
		data->REG_TEMP_SEL = NCT6775_REG_TEMP_SEL;
		data->REG_WEIGHT_TEMP_SEL = NCT6775_REG_WEIGHT_TEMP_SEL;
		data->REG_WEIGHT_TEMP[0] = NCT6775_REG_WEIGHT_TEMP_STEP;
		data->REG_WEIGHT_TEMP[1] = NCT6775_REG_WEIGHT_TEMP_STEP_TOL;
		data->REG_WEIGHT_TEMP[2] = NCT6775_REG_WEIGHT_TEMP_BASE;
		data->REG_ALARM = NCT6775_REG_ALARM;
		data->REG_BEEP = NCT6776_REG_BEEP;

		reg_temp = NCT6775_REG_TEMP;
		reg_temp_mon = NCT6775_REG_TEMP_MON;
		num_reg_temp = ARRAY_SIZE(NCT6775_REG_TEMP);
		num_reg_temp_mon = ARRAY_SIZE(NCT6775_REG_TEMP_MON);
		reg_temp_over = NCT6775_REG_TEMP_OVER;
		reg_temp_hyst = NCT6775_REG_TEMP_HYST;
		reg_temp_config = NCT6776_REG_TEMP_CONFIG;
		reg_temp_alternate = NCT6776_REG_TEMP_ALTERNATE;
		reg_temp_crit = NCT6776_REG_TEMP_CRIT;

		अवरोध;
	हाल nct6779:
		data->in_num = 15;
		data->pwm_num = 5;
		data->स्वतः_pwm_num = 4;
		data->has_fan_भाग = false;
		data->temp_fixed_num = 6;
		data->num_temp_alarms = 2;
		data->num_temp_beeps = 2;

		data->ALARM_BITS = NCT6779_ALARM_BITS;
		data->BEEP_BITS = NCT6779_BEEP_BITS;

		data->fan_from_reg = fan_from_reg_rpm;
		data->fan_from_reg_min = fan_from_reg13;
		data->target_temp_mask = 0xff;
		data->tolerance_mask = 0x07;
		data->speed_tolerance_limit = 63;

		data->temp_label = nct6779_temp_label;
		data->temp_mask = NCT6779_TEMP_MASK;
		data->virt_temp_mask = NCT6779_VIRT_TEMP_MASK;

		data->REG_CONFIG = NCT6775_REG_CONFIG;
		data->REG_VBAT = NCT6775_REG_VBAT;
		data->REG_DIODE = NCT6775_REG_DIODE;
		data->DIODE_MASK = NCT6775_DIODE_MASK;
		data->REG_VIN = NCT6779_REG_IN;
		data->REG_IN_MINMAX[0] = NCT6775_REG_IN_MIN;
		data->REG_IN_MINMAX[1] = NCT6775_REG_IN_MAX;
		data->REG_TARGET = NCT6775_REG_TARGET;
		data->REG_FAN = NCT6779_REG_FAN;
		data->REG_FAN_MODE = NCT6775_REG_FAN_MODE;
		data->REG_FAN_MIN = NCT6776_REG_FAN_MIN;
		data->REG_FAN_PULSES = NCT6779_REG_FAN_PULSES;
		data->FAN_PULSE_SHIFT = NCT6775_FAN_PULSE_SHIFT;
		data->REG_FAN_TIME[0] = NCT6775_REG_FAN_STOP_TIME;
		data->REG_FAN_TIME[1] = NCT6776_REG_FAN_STEP_UP_TIME;
		data->REG_FAN_TIME[2] = NCT6776_REG_FAN_STEP_DOWN_TIME;
		data->REG_TOLERANCE_H = NCT6776_REG_TOLERANCE_H;
		data->REG_PWM[0] = NCT6775_REG_PWM;
		data->REG_PWM[1] = NCT6775_REG_FAN_START_OUTPUT;
		data->REG_PWM[2] = NCT6775_REG_FAN_STOP_OUTPUT;
		data->REG_PWM[5] = NCT6775_REG_WEIGHT_DUTY_STEP;
		data->REG_PWM[6] = NCT6776_REG_WEIGHT_DUTY_BASE;
		data->REG_PWM_READ = NCT6775_REG_PWM_READ;
		data->REG_PWM_MODE = NCT6776_REG_PWM_MODE;
		data->PWM_MODE_MASK = NCT6776_PWM_MODE_MASK;
		data->REG_AUTO_TEMP = NCT6775_REG_AUTO_TEMP;
		data->REG_AUTO_PWM = NCT6775_REG_AUTO_PWM;
		data->REG_CRITICAL_TEMP = NCT6775_REG_CRITICAL_TEMP;
		data->REG_CRITICAL_TEMP_TOLERANCE
		  = NCT6775_REG_CRITICAL_TEMP_TOLERANCE;
		data->REG_CRITICAL_PWM_ENABLE = NCT6779_REG_CRITICAL_PWM_ENABLE;
		data->CRITICAL_PWM_ENABLE_MASK
		  = NCT6779_CRITICAL_PWM_ENABLE_MASK;
		data->REG_CRITICAL_PWM = NCT6779_REG_CRITICAL_PWM;
		data->REG_TEMP_OFFSET = NCT6779_REG_TEMP_OFFSET;
		data->REG_TEMP_SOURCE = NCT6775_REG_TEMP_SOURCE;
		data->REG_TEMP_SEL = NCT6775_REG_TEMP_SEL;
		data->REG_WEIGHT_TEMP_SEL = NCT6775_REG_WEIGHT_TEMP_SEL;
		data->REG_WEIGHT_TEMP[0] = NCT6775_REG_WEIGHT_TEMP_STEP;
		data->REG_WEIGHT_TEMP[1] = NCT6775_REG_WEIGHT_TEMP_STEP_TOL;
		data->REG_WEIGHT_TEMP[2] = NCT6775_REG_WEIGHT_TEMP_BASE;
		data->REG_ALARM = NCT6779_REG_ALARM;
		data->REG_BEEP = NCT6776_REG_BEEP;

		reg_temp = NCT6779_REG_TEMP;
		reg_temp_mon = NCT6779_REG_TEMP_MON;
		num_reg_temp = ARRAY_SIZE(NCT6779_REG_TEMP);
		num_reg_temp_mon = ARRAY_SIZE(NCT6779_REG_TEMP_MON);
		reg_temp_over = NCT6779_REG_TEMP_OVER;
		reg_temp_hyst = NCT6779_REG_TEMP_HYST;
		reg_temp_config = NCT6779_REG_TEMP_CONFIG;
		reg_temp_alternate = NCT6779_REG_TEMP_ALTERNATE;
		reg_temp_crit = NCT6779_REG_TEMP_CRIT;

		अवरोध;
	हाल nct6791:
	हाल nct6792:
	हाल nct6793:
	हाल nct6795:
	हाल nct6796:
	हाल nct6797:
	हाल nct6798:
		data->in_num = 15;
		data->pwm_num = (data->kind == nct6796 ||
				 data->kind == nct6797 ||
				 data->kind == nct6798) ? 7 : 6;
		data->स्वतः_pwm_num = 4;
		data->has_fan_भाग = false;
		data->temp_fixed_num = 6;
		data->num_temp_alarms = 2;
		data->num_temp_beeps = 2;

		data->ALARM_BITS = NCT6791_ALARM_BITS;
		data->BEEP_BITS = NCT6779_BEEP_BITS;

		data->fan_from_reg = fan_from_reg_rpm;
		data->fan_from_reg_min = fan_from_reg13;
		data->target_temp_mask = 0xff;
		data->tolerance_mask = 0x07;
		data->speed_tolerance_limit = 63;

		चयन (data->kind) अणु
		शेष:
		हाल nct6791:
			data->temp_label = nct6779_temp_label;
			data->temp_mask = NCT6791_TEMP_MASK;
			data->virt_temp_mask = NCT6791_VIRT_TEMP_MASK;
			अवरोध;
		हाल nct6792:
			data->temp_label = nct6792_temp_label;
			data->temp_mask = NCT6792_TEMP_MASK;
			data->virt_temp_mask = NCT6792_VIRT_TEMP_MASK;
			अवरोध;
		हाल nct6793:
			data->temp_label = nct6793_temp_label;
			data->temp_mask = NCT6793_TEMP_MASK;
			data->virt_temp_mask = NCT6793_VIRT_TEMP_MASK;
			अवरोध;
		हाल nct6795:
		हाल nct6797:
			data->temp_label = nct6795_temp_label;
			data->temp_mask = NCT6795_TEMP_MASK;
			data->virt_temp_mask = NCT6795_VIRT_TEMP_MASK;
			अवरोध;
		हाल nct6796:
			data->temp_label = nct6796_temp_label;
			data->temp_mask = NCT6796_TEMP_MASK;
			data->virt_temp_mask = NCT6796_VIRT_TEMP_MASK;
			अवरोध;
		हाल nct6798:
			data->temp_label = nct6798_temp_label;
			data->temp_mask = NCT6798_TEMP_MASK;
			data->virt_temp_mask = NCT6798_VIRT_TEMP_MASK;
			अवरोध;
		पूर्ण

		data->REG_CONFIG = NCT6775_REG_CONFIG;
		data->REG_VBAT = NCT6775_REG_VBAT;
		data->REG_DIODE = NCT6775_REG_DIODE;
		data->DIODE_MASK = NCT6775_DIODE_MASK;
		data->REG_VIN = NCT6779_REG_IN;
		data->REG_IN_MINMAX[0] = NCT6775_REG_IN_MIN;
		data->REG_IN_MINMAX[1] = NCT6775_REG_IN_MAX;
		data->REG_TARGET = NCT6775_REG_TARGET;
		data->REG_FAN = NCT6779_REG_FAN;
		data->REG_FAN_MODE = NCT6775_REG_FAN_MODE;
		data->REG_FAN_MIN = NCT6776_REG_FAN_MIN;
		data->REG_FAN_PULSES = NCT6779_REG_FAN_PULSES;
		data->FAN_PULSE_SHIFT = NCT6775_FAN_PULSE_SHIFT;
		data->REG_FAN_TIME[0] = NCT6775_REG_FAN_STOP_TIME;
		data->REG_FAN_TIME[1] = NCT6776_REG_FAN_STEP_UP_TIME;
		data->REG_FAN_TIME[2] = NCT6776_REG_FAN_STEP_DOWN_TIME;
		data->REG_TOLERANCE_H = NCT6776_REG_TOLERANCE_H;
		data->REG_PWM[0] = NCT6775_REG_PWM;
		data->REG_PWM[1] = NCT6775_REG_FAN_START_OUTPUT;
		data->REG_PWM[2] = NCT6775_REG_FAN_STOP_OUTPUT;
		data->REG_PWM[5] = NCT6791_REG_WEIGHT_DUTY_STEP;
		data->REG_PWM[6] = NCT6791_REG_WEIGHT_DUTY_BASE;
		data->REG_PWM_READ = NCT6775_REG_PWM_READ;
		data->REG_PWM_MODE = NCT6776_REG_PWM_MODE;
		data->PWM_MODE_MASK = NCT6776_PWM_MODE_MASK;
		data->REG_AUTO_TEMP = NCT6775_REG_AUTO_TEMP;
		data->REG_AUTO_PWM = NCT6775_REG_AUTO_PWM;
		data->REG_CRITICAL_TEMP = NCT6775_REG_CRITICAL_TEMP;
		data->REG_CRITICAL_TEMP_TOLERANCE
		  = NCT6775_REG_CRITICAL_TEMP_TOLERANCE;
		data->REG_CRITICAL_PWM_ENABLE = NCT6779_REG_CRITICAL_PWM_ENABLE;
		data->CRITICAL_PWM_ENABLE_MASK
		  = NCT6779_CRITICAL_PWM_ENABLE_MASK;
		data->REG_CRITICAL_PWM = NCT6779_REG_CRITICAL_PWM;
		data->REG_TEMP_OFFSET = NCT6779_REG_TEMP_OFFSET;
		data->REG_TEMP_SOURCE = NCT6775_REG_TEMP_SOURCE;
		data->REG_TEMP_SEL = NCT6775_REG_TEMP_SEL;
		data->REG_WEIGHT_TEMP_SEL = NCT6791_REG_WEIGHT_TEMP_SEL;
		data->REG_WEIGHT_TEMP[0] = NCT6791_REG_WEIGHT_TEMP_STEP;
		data->REG_WEIGHT_TEMP[1] = NCT6791_REG_WEIGHT_TEMP_STEP_TOL;
		data->REG_WEIGHT_TEMP[2] = NCT6791_REG_WEIGHT_TEMP_BASE;
		data->REG_ALARM = NCT6791_REG_ALARM;
		अगर (data->kind == nct6791)
			data->REG_BEEP = NCT6776_REG_BEEP;
		अन्यथा
			data->REG_BEEP = NCT6792_REG_BEEP;

		reg_temp = NCT6779_REG_TEMP;
		num_reg_temp = ARRAY_SIZE(NCT6779_REG_TEMP);
		अगर (data->kind == nct6791) अणु
			reg_temp_mon = NCT6779_REG_TEMP_MON;
			num_reg_temp_mon = ARRAY_SIZE(NCT6779_REG_TEMP_MON);
		पूर्ण अन्यथा अणु
			reg_temp_mon = NCT6792_REG_TEMP_MON;
			num_reg_temp_mon = ARRAY_SIZE(NCT6792_REG_TEMP_MON);
		पूर्ण
		reg_temp_over = NCT6779_REG_TEMP_OVER;
		reg_temp_hyst = NCT6779_REG_TEMP_HYST;
		reg_temp_config = NCT6779_REG_TEMP_CONFIG;
		reg_temp_alternate = NCT6779_REG_TEMP_ALTERNATE;
		reg_temp_crit = NCT6779_REG_TEMP_CRIT;

		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण
	data->have_in = BIT(data->in_num) - 1;
	data->have_temp = 0;

	/*
	 * On some boards, not all available temperature sources are monitored,
	 * even though some of the monitoring रेजिस्टरs are unused.
	 * Get list of unused monitoring रेजिस्टरs, then detect अगर any fan
	 * controls are configured to use unmonitored temperature sources.
	 * If so, assign the unmonitored temperature sources to available
	 * monitoring रेजिस्टरs.
	 */
	mask = 0;
	available = 0;
	क्रम (i = 0; i < num_reg_temp; i++) अणु
		अगर (reg_temp[i] == 0)
			जारी;

		src = nct6775_पढ़ो_value(data, data->REG_TEMP_SOURCE[i]) & 0x1f;
		अगर (!src || (mask & BIT(src)))
			available |= BIT(i);

		mask |= BIT(src);
	पूर्ण

	/*
	 * Now find unmonitored temperature रेजिस्टरs and enable monitoring
	 * अगर additional monitoring रेजिस्टरs are available.
	 */
	add_temp_sensors(data, data->REG_TEMP_SEL, &available, &mask);
	add_temp_sensors(data, data->REG_WEIGHT_TEMP_SEL, &available, &mask);

	mask = 0;
	s = NUM_TEMP_FIXED;	/* First dynamic temperature attribute */
	क्रम (i = 0; i < num_reg_temp; i++) अणु
		अगर (reg_temp[i] == 0)
			जारी;

		src = nct6775_पढ़ो_value(data, data->REG_TEMP_SOURCE[i]) & 0x1f;
		अगर (!src || (mask & BIT(src)))
			जारी;

		अगर (!(data->temp_mask & BIT(src))) अणु
			dev_info(dev,
				 "Invalid temperature source %d at index %d, source register 0x%x, temp register 0x%x\n",
				 src, i, data->REG_TEMP_SOURCE[i], reg_temp[i]);
			जारी;
		पूर्ण

		mask |= BIT(src);

		/* Use fixed index क्रम SYSTIN(1), CPUTIN(2), AUXTIN(3) */
		अगर (src <= data->temp_fixed_num) अणु
			data->have_temp |= BIT(src - 1);
			data->have_temp_fixed |= BIT(src - 1);
			data->reg_temp[0][src - 1] = reg_temp[i];
			data->reg_temp[1][src - 1] = reg_temp_over[i];
			data->reg_temp[2][src - 1] = reg_temp_hyst[i];
			अगर (reg_temp_crit_h && reg_temp_crit_h[i])
				data->reg_temp[3][src - 1] = reg_temp_crit_h[i];
			अन्यथा अगर (reg_temp_crit[src - 1])
				data->reg_temp[3][src - 1]
				  = reg_temp_crit[src - 1];
			अगर (reg_temp_crit_l && reg_temp_crit_l[i])
				data->reg_temp[4][src - 1] = reg_temp_crit_l[i];
			data->reg_temp_config[src - 1] = reg_temp_config[i];
			data->temp_src[src - 1] = src;
			जारी;
		पूर्ण

		अगर (s >= NUM_TEMP)
			जारी;

		/* Use dynamic index क्रम other sources */
		data->have_temp |= BIT(s);
		data->reg_temp[0][s] = reg_temp[i];
		data->reg_temp[1][s] = reg_temp_over[i];
		data->reg_temp[2][s] = reg_temp_hyst[i];
		data->reg_temp_config[s] = reg_temp_config[i];
		अगर (reg_temp_crit_h && reg_temp_crit_h[i])
			data->reg_temp[3][s] = reg_temp_crit_h[i];
		अन्यथा अगर (reg_temp_crit[src - 1])
			data->reg_temp[3][s] = reg_temp_crit[src - 1];
		अगर (reg_temp_crit_l && reg_temp_crit_l[i])
			data->reg_temp[4][s] = reg_temp_crit_l[i];

		data->temp_src[s] = src;
		s++;
	पूर्ण

	/*
	 * Repeat with temperatures used क्रम fan control.
	 * This set of रेजिस्टरs करोes not support limits.
	 */
	क्रम (i = 0; i < num_reg_temp_mon; i++) अणु
		अगर (reg_temp_mon[i] == 0)
			जारी;

		src = nct6775_पढ़ो_value(data, data->REG_TEMP_SEL[i]) & 0x1f;
		अगर (!src)
			जारी;

		अगर (!(data->temp_mask & BIT(src))) अणु
			dev_info(dev,
				 "Invalid temperature source %d at index %d, source register 0x%x, temp register 0x%x\n",
				 src, i, data->REG_TEMP_SEL[i],
				 reg_temp_mon[i]);
			जारी;
		पूर्ण

		/*
		 * For भव temperature sources, the 'virtual' temperature
		 * क्रम each fan reflects a dअगरferent temperature, and there
		 * are no duplicates.
		 */
		अगर (!(data->virt_temp_mask & BIT(src))) अणु
			अगर (mask & BIT(src))
				जारी;
			mask |= BIT(src);
		पूर्ण

		/* Use fixed index क्रम SYSTIN(1), CPUTIN(2), AUXTIN(3) */
		अगर (src <= data->temp_fixed_num) अणु
			अगर (data->have_temp & BIT(src - 1))
				जारी;
			data->have_temp |= BIT(src - 1);
			data->have_temp_fixed |= BIT(src - 1);
			data->reg_temp[0][src - 1] = reg_temp_mon[i];
			data->temp_src[src - 1] = src;
			जारी;
		पूर्ण

		अगर (s >= NUM_TEMP)
			जारी;

		/* Use dynamic index क्रम other sources */
		data->have_temp |= BIT(s);
		data->reg_temp[0][s] = reg_temp_mon[i];
		data->temp_src[s] = src;
		s++;
	पूर्ण

#अगर_घोषित USE_ALTERNATE
	/*
	 * Go through the list of alternate temp रेजिस्टरs and enable
	 * अगर possible.
	 * The temperature is alपढ़ोy monitored अगर the respective bit in <mask>
	 * is set.
	 */
	क्रम (i = 0; i < 31; i++) अणु
		अगर (!(data->temp_mask & BIT(i + 1)))
			जारी;
		अगर (!reg_temp_alternate[i])
			जारी;
		अगर (mask & BIT(i + 1))
			जारी;
		अगर (i < data->temp_fixed_num) अणु
			अगर (data->have_temp & BIT(i))
				जारी;
			data->have_temp |= BIT(i);
			data->have_temp_fixed |= BIT(i);
			data->reg_temp[0][i] = reg_temp_alternate[i];
			अगर (i < num_reg_temp) अणु
				data->reg_temp[1][i] = reg_temp_over[i];
				data->reg_temp[2][i] = reg_temp_hyst[i];
			पूर्ण
			data->temp_src[i] = i + 1;
			जारी;
		पूर्ण

		अगर (s >= NUM_TEMP)	/* Abort अगर no more space */
			अवरोध;

		data->have_temp |= BIT(s);
		data->reg_temp[0][s] = reg_temp_alternate[i];
		data->temp_src[s] = i + 1;
		s++;
	पूर्ण
#पूर्ण_अगर /* USE_ALTERNATE */

	/* Initialize the chip */
	nct6775_init_device(data);

	err = superio_enter(sio_data->sioreg);
	अगर (err)
		वापस err;

	cr2a = superio_inb(sio_data->sioreg, 0x2a);
	चयन (data->kind) अणु
	हाल nct6775:
		data->have_vid = (cr2a & 0x40);
		अवरोध;
	हाल nct6776:
		data->have_vid = (cr2a & 0x60) == 0x40;
		अवरोध;
	हाल nct6106:
	हाल nct6116:
	हाल nct6779:
	हाल nct6791:
	हाल nct6792:
	हाल nct6793:
	हाल nct6795:
	हाल nct6796:
	हाल nct6797:
	हाल nct6798:
		अवरोध;
	पूर्ण

	/*
	 * Read VID value
	 * We can get the VID input values directly at logical device D 0xe3.
	 */
	अगर (data->have_vid) अणु
		superio_select(sio_data->sioreg, NCT6775_LD_VID);
		data->vid = superio_inb(sio_data->sioreg, 0xe3);
		data->vrm = vid_which_vrm();
	पूर्ण

	अगर (fan_debounce) अणु
		u8 पंचांगp;

		superio_select(sio_data->sioreg, NCT6775_LD_HWM);
		पंचांगp = superio_inb(sio_data->sioreg,
				  NCT6775_REG_CR_FAN_DEBOUNCE);
		चयन (data->kind) अणु
		हाल nct6106:
		हाल nct6116:
			पंचांगp |= 0xe0;
			अवरोध;
		हाल nct6775:
			पंचांगp |= 0x1e;
			अवरोध;
		हाल nct6776:
		हाल nct6779:
			पंचांगp |= 0x3e;
			अवरोध;
		हाल nct6791:
		हाल nct6792:
		हाल nct6793:
		हाल nct6795:
		हाल nct6796:
		हाल nct6797:
		हाल nct6798:
			पंचांगp |= 0x7e;
			अवरोध;
		पूर्ण
		superio_outb(sio_data->sioreg, NCT6775_REG_CR_FAN_DEBOUNCE,
			     पंचांगp);
		dev_info(&pdev->dev, "Enabled fan debounce for chip %s\n",
			 data->name);
	पूर्ण

	nct6775_check_fan_inमाला_दो(data);

	superio_निकास(sio_data->sioreg);

	/* Read fan घड़ी भागiders immediately */
	nct6775_init_fan_common(dev, data);

	/* Register sysfs hooks */
	group = nct6775_create_attr_group(dev, &nct6775_pwm_ढाँचा_group,
					  data->pwm_num);
	अगर (IS_ERR(group))
		वापस PTR_ERR(group);

	data->groups[num_attr_groups++] = group;

	group = nct6775_create_attr_group(dev, &nct6775_in_ढाँचा_group,
					  fls(data->have_in));
	अगर (IS_ERR(group))
		वापस PTR_ERR(group);

	data->groups[num_attr_groups++] = group;

	group = nct6775_create_attr_group(dev, &nct6775_fan_ढाँचा_group,
					  fls(data->has_fan));
	अगर (IS_ERR(group))
		वापस PTR_ERR(group);

	data->groups[num_attr_groups++] = group;

	group = nct6775_create_attr_group(dev, &nct6775_temp_ढाँचा_group,
					  fls(data->have_temp));
	अगर (IS_ERR(group))
		वापस PTR_ERR(group);

	data->groups[num_attr_groups++] = group;
	data->groups[num_attr_groups++] = &nct6775_group_other;

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev, data->name,
							   data, data->groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल व्योम nct6791_enable_io_mapping(पूर्णांक sioaddr)
अणु
	पूर्णांक val;

	val = superio_inb(sioaddr, NCT6791_REG_HM_IO_SPACE_LOCK_ENABLE);
	अगर (val & 0x10) अणु
		pr_info("Enabling hardware monitor logical device mappings.\n");
		superio_outb(sioaddr, NCT6791_REG_HM_IO_SPACE_LOCK_ENABLE,
			     val & ~0x10);
	पूर्ण
पूर्ण

अटल पूर्णांक __maybe_unused nct6775_suspend(काष्ठा device *dev)
अणु
	काष्ठा nct6775_data *data = nct6775_update_device(dev);

	mutex_lock(&data->update_lock);
	data->vbat = nct6775_पढ़ो_value(data, data->REG_VBAT);
	अगर (data->kind == nct6775) अणु
		data->fanभाग1 = nct6775_पढ़ो_value(data, NCT6775_REG_FANDIV1);
		data->fanभाग2 = nct6775_पढ़ो_value(data, NCT6775_REG_FANDIV2);
	पूर्ण
	mutex_unlock(&data->update_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused nct6775_resume(काष्ठा device *dev)
अणु
	काष्ठा nct6775_data *data = dev_get_drvdata(dev);
	पूर्णांक sioreg = data->sioreg;
	पूर्णांक i, j, err = 0;
	u8 reg;

	mutex_lock(&data->update_lock);
	data->bank = 0xff;		/* Force initial bank selection */

	err = superio_enter(sioreg);
	अगर (err)
		जाओ पात;

	superio_select(sioreg, NCT6775_LD_HWM);
	reg = superio_inb(sioreg, SIO_REG_ENABLE);
	अगर (reg != data->sio_reg_enable)
		superio_outb(sioreg, SIO_REG_ENABLE, data->sio_reg_enable);

	अगर (data->kind == nct6791 || data->kind == nct6792 ||
	    data->kind == nct6793 || data->kind == nct6795 ||
	    data->kind == nct6796 || data->kind == nct6797 ||
	    data->kind == nct6798)
		nct6791_enable_io_mapping(sioreg);

	superio_निकास(sioreg);

	/* Restore limits */
	क्रम (i = 0; i < data->in_num; i++) अणु
		अगर (!(data->have_in & BIT(i)))
			जारी;

		nct6775_ग_लिखो_value(data, data->REG_IN_MINMAX[0][i],
				    data->in[i][1]);
		nct6775_ग_लिखो_value(data, data->REG_IN_MINMAX[1][i],
				    data->in[i][2]);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(data->fan_min); i++) अणु
		अगर (!(data->has_fan_min & BIT(i)))
			जारी;

		nct6775_ग_लिखो_value(data, data->REG_FAN_MIN[i],
				    data->fan_min[i]);
	पूर्ण

	क्रम (i = 0; i < NUM_TEMP; i++) अणु
		अगर (!(data->have_temp & BIT(i)))
			जारी;

		क्रम (j = 1; j < ARRAY_SIZE(data->reg_temp); j++)
			अगर (data->reg_temp[j][i])
				nct6775_ग_लिखो_temp(data, data->reg_temp[j][i],
						   data->temp[j][i]);
	पूर्ण

	/* Restore other settings */
	nct6775_ग_लिखो_value(data, data->REG_VBAT, data->vbat);
	अगर (data->kind == nct6775) अणु
		nct6775_ग_लिखो_value(data, NCT6775_REG_FANDIV1, data->fanभाग1);
		nct6775_ग_लिखो_value(data, NCT6775_REG_FANDIV2, data->fanभाग2);
	पूर्ण

पात:
	/* Force re-पढ़ोing all values */
	data->valid = false;
	mutex_unlock(&data->update_lock);

	वापस err;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(nct6775_dev_pm_ops, nct6775_suspend, nct6775_resume);

अटल काष्ठा platक्रमm_driver nct6775_driver = अणु
	.driver = अणु
		.name	= DRVNAME,
		.pm	= &nct6775_dev_pm_ops,
	पूर्ण,
	.probe		= nct6775_probe,
पूर्ण;

/* nct6775_find() looks क्रम a '627 in the Super-I/O config space */
अटल पूर्णांक __init nct6775_find(पूर्णांक sioaddr, काष्ठा nct6775_sio_data *sio_data)
अणु
	u16 val;
	पूर्णांक err;
	पूर्णांक addr;

	err = superio_enter(sioaddr);
	अगर (err)
		वापस err;

	val = (superio_inb(sioaddr, SIO_REG_DEVID) << 8) |
		superio_inb(sioaddr, SIO_REG_DEVID + 1);
	अगर (क्रमce_id && val != 0xffff)
		val = क्रमce_id;

	चयन (val & SIO_ID_MASK) अणु
	हाल SIO_NCT6106_ID:
		sio_data->kind = nct6106;
		अवरोध;
	हाल SIO_NCT6116_ID:
		sio_data->kind = nct6116;
		अवरोध;
	हाल SIO_NCT6775_ID:
		sio_data->kind = nct6775;
		अवरोध;
	हाल SIO_NCT6776_ID:
		sio_data->kind = nct6776;
		अवरोध;
	हाल SIO_NCT6779_ID:
		sio_data->kind = nct6779;
		अवरोध;
	हाल SIO_NCT6791_ID:
		sio_data->kind = nct6791;
		अवरोध;
	हाल SIO_NCT6792_ID:
		sio_data->kind = nct6792;
		अवरोध;
	हाल SIO_NCT6793_ID:
		sio_data->kind = nct6793;
		अवरोध;
	हाल SIO_NCT6795_ID:
		sio_data->kind = nct6795;
		अवरोध;
	हाल SIO_NCT6796_ID:
		sio_data->kind = nct6796;
		अवरोध;
	हाल SIO_NCT6797_ID:
		sio_data->kind = nct6797;
		अवरोध;
	हाल SIO_NCT6798_ID:
		sio_data->kind = nct6798;
		अवरोध;
	शेष:
		अगर (val != 0xffff)
			pr_debug("unsupported chip ID: 0x%04x\n", val);
		superio_निकास(sioaddr);
		वापस -ENODEV;
	पूर्ण

	/* We have a known chip, find the HWM I/O address */
	superio_select(sioaddr, NCT6775_LD_HWM);
	val = (superio_inb(sioaddr, SIO_REG_ADDR) << 8)
	    | superio_inb(sioaddr, SIO_REG_ADDR + 1);
	addr = val & IOREGION_ALIGNMENT;
	अगर (addr == 0) अणु
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

	अगर (sio_data->kind == nct6791 || sio_data->kind == nct6792 ||
	    sio_data->kind == nct6793 || sio_data->kind == nct6795 ||
	    sio_data->kind == nct6796 || sio_data->kind == nct6797 ||
	    sio_data->kind == nct6798)
		nct6791_enable_io_mapping(sioaddr);

	superio_निकास(sioaddr);
	pr_info("Found %s or compatible chip at %#x:%#x\n",
		nct6775_sio_names[sio_data->kind], sioaddr, addr);
	sio_data->sioreg = sioaddr;

	वापस addr;
पूर्ण

/*
 * when Super-I/O functions move to a separate file, the Super-I/O
 * bus will manage the lअगरeसमय of the device and this module will only keep
 * track of the nct6775 driver. But since we use platक्रमm_device_alloc(), we
 * must keep track of the device
 */
अटल काष्ठा platक्रमm_device *pdev[2];

अटल पूर्णांक __init sensors_nct6775_init(व्योम)
अणु
	पूर्णांक i, err;
	bool found = false;
	पूर्णांक address;
	काष्ठा resource res;
	काष्ठा nct6775_sio_data sio_data;
	पूर्णांक sioaddr[2] = अणु 0x2e, 0x4e पूर्ण;

	err = platक्रमm_driver_रेजिस्टर(&nct6775_driver);
	अगर (err)
		वापस err;

	/*
	 * initialize sio_data->kind and sio_data->sioreg.
	 *
	 * when Super-I/O functions move to a separate file, the Super-I/O
	 * driver will probe 0x2e and 0x4e and स्वतः-detect the presence of a
	 * nct6775 hardware monitor, and call probe()
	 */
	क्रम (i = 0; i < ARRAY_SIZE(pdev); i++) अणु
		address = nct6775_find(sioaddr[i], &sio_data);
		अगर (address <= 0)
			जारी;

		found = true;

		pdev[i] = platक्रमm_device_alloc(DRVNAME, address);
		अगर (!pdev[i]) अणु
			err = -ENOMEM;
			जाओ निकास_device_unरेजिस्टर;
		पूर्ण

		err = platक्रमm_device_add_data(pdev[i], &sio_data,
					       माप(काष्ठा nct6775_sio_data));
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
	platक्रमm_driver_unरेजिस्टर(&nct6775_driver);
	वापस err;
पूर्ण

अटल व्योम __निकास sensors_nct6775_निकास(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(pdev); i++) अणु
		अगर (pdev[i])
			platक्रमm_device_unरेजिस्टर(pdev[i]);
	पूर्ण
	platक्रमm_driver_unरेजिस्टर(&nct6775_driver);
पूर्ण

MODULE_AUTHOR("Guenter Roeck <linux@roeck-us.net>");
MODULE_DESCRIPTION("Driver for NCT6775F and compatible chips");
MODULE_LICENSE("GPL");

module_init(sensors_nct6775_init);
module_निकास(sensors_nct6775_निकास);
