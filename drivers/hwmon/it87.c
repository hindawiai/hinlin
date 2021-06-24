<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  it87.c - Part of lm_sensors, Linux kernel modules क्रम hardware
 *           monitoring.
 *
 *  The IT8705F is an LPC-based Super I/O part that contains UARTs, a
 *  parallel port, an IR port, a MIDI port, a floppy controller, etc., in
 *  addition to an Environment Controller (Enhanced Hardware Monitor and
 *  Fan Controller)
 *
 *  This driver supports only the Environment Controller in the IT8705F and
 *  similar parts.  The other devices are supported by dअगरferent drivers.
 *
 *  Supports: IT8603E  Super I/O chip w/LPC पूर्णांकerface
 *            IT8620E  Super I/O chip w/LPC पूर्णांकerface
 *            IT8622E  Super I/O chip w/LPC पूर्णांकerface
 *            IT8623E  Super I/O chip w/LPC पूर्णांकerface
 *            IT8628E  Super I/O chip w/LPC पूर्णांकerface
 *            IT8705F  Super I/O chip w/LPC पूर्णांकerface
 *            IT8712F  Super I/O chip w/LPC पूर्णांकerface
 *            IT8716F  Super I/O chip w/LPC पूर्णांकerface
 *            IT8718F  Super I/O chip w/LPC पूर्णांकerface
 *            IT8720F  Super I/O chip w/LPC पूर्णांकerface
 *            IT8721F  Super I/O chip w/LPC पूर्णांकerface
 *            IT8726F  Super I/O chip w/LPC पूर्णांकerface
 *            IT8728F  Super I/O chip w/LPC पूर्णांकerface
 *            IT8732F  Super I/O chip w/LPC पूर्णांकerface
 *            IT8758E  Super I/O chip w/LPC पूर्णांकerface
 *            IT8771E  Super I/O chip w/LPC पूर्णांकerface
 *            IT8772E  Super I/O chip w/LPC पूर्णांकerface
 *            IT8781F  Super I/O chip w/LPC पूर्णांकerface
 *            IT8782F  Super I/O chip w/LPC पूर्णांकerface
 *            IT8783E/F Super I/O chip w/LPC पूर्णांकerface
 *            IT8786E  Super I/O chip w/LPC पूर्णांकerface
 *            IT8790E  Super I/O chip w/LPC पूर्णांकerface
 *            IT8792E  Super I/O chip w/LPC पूर्णांकerface
 *            Sis950   A clone of the IT8705F
 *
 *  Copyright (C) 2001 Chris Gauthron
 *  Copyright (C) 2005-2010 Jean Delvare <jdelvare@suse.de>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/bitops.h>
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
#समावेश <linux/sysfs.h>
#समावेश <linux/माला.स>
#समावेश <linux/dmi.h>
#समावेश <linux/acpi.h>
#समावेश <linux/पन.स>

#घोषणा DRVNAME "it87"

क्रमागत chips अणु it87, it8712, it8716, it8718, it8720, it8721, it8728, it8732,
	     it8771, it8772, it8781, it8782, it8783, it8786, it8790,
	     it8792, it8603, it8620, it8622, it8628 पूर्ण;

अटल अचिन्हित लघु क्रमce_id;
module_param(क्रमce_id, uलघु, 0);
MODULE_PARM_DESC(क्रमce_id, "Override the detected device ID");

अटल काष्ठा platक्रमm_device *it87_pdev[2];

#घोषणा	REG_2E	0x2e	/* The रेजिस्टर to पढ़ो/ग_लिखो */
#घोषणा	REG_4E	0x4e	/* Secondary रेजिस्टर to पढ़ो/ग_लिखो */

#घोषणा	DEV	0x07	/* Register: Logical device select */
#घोषणा PME	0x04	/* The device with the fan रेजिस्टरs in it */

/* The device with the IT8718F/IT8720F VID value in it */
#घोषणा GPIO	0x07

#घोषणा	DEVID	0x20	/* Register: Device ID */
#घोषणा	DEVREV	0x22	/* Register: Device Revision */

अटल अंतरभूत पूर्णांक superio_inb(पूर्णांक ioreg, पूर्णांक reg)
अणु
	outb(reg, ioreg);
	वापस inb(ioreg + 1);
पूर्ण

अटल अंतरभूत व्योम superio_outb(पूर्णांक ioreg, पूर्णांक reg, पूर्णांक val)
अणु
	outb(reg, ioreg);
	outb(val, ioreg + 1);
पूर्ण

अटल पूर्णांक superio_inw(पूर्णांक ioreg, पूर्णांक reg)
अणु
	पूर्णांक val;

	outb(reg++, ioreg);
	val = inb(ioreg + 1) << 8;
	outb(reg, ioreg);
	val |= inb(ioreg + 1);
	वापस val;
पूर्ण

अटल अंतरभूत व्योम superio_select(पूर्णांक ioreg, पूर्णांक ldn)
अणु
	outb(DEV, ioreg);
	outb(ldn, ioreg + 1);
पूर्ण

अटल अंतरभूत पूर्णांक superio_enter(पूर्णांक ioreg)
अणु
	/*
	 * Try to reserve ioreg and ioreg + 1 क्रम exclusive access.
	 */
	अगर (!request_muxed_region(ioreg, 2, DRVNAME))
		वापस -EBUSY;

	outb(0x87, ioreg);
	outb(0x01, ioreg);
	outb(0x55, ioreg);
	outb(ioreg == REG_4E ? 0xaa : 0x55, ioreg);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम superio_निकास(पूर्णांक ioreg)
अणु
	outb(0x02, ioreg);
	outb(0x02, ioreg + 1);
	release_region(ioreg, 2);
पूर्ण

/* Logical device 4 रेजिस्टरs */
#घोषणा IT8712F_DEVID 0x8712
#घोषणा IT8705F_DEVID 0x8705
#घोषणा IT8716F_DEVID 0x8716
#घोषणा IT8718F_DEVID 0x8718
#घोषणा IT8720F_DEVID 0x8720
#घोषणा IT8721F_DEVID 0x8721
#घोषणा IT8726F_DEVID 0x8726
#घोषणा IT8728F_DEVID 0x8728
#घोषणा IT8732F_DEVID 0x8732
#घोषणा IT8792E_DEVID 0x8733
#घोषणा IT8771E_DEVID 0x8771
#घोषणा IT8772E_DEVID 0x8772
#घोषणा IT8781F_DEVID 0x8781
#घोषणा IT8782F_DEVID 0x8782
#घोषणा IT8783E_DEVID 0x8783
#घोषणा IT8786E_DEVID 0x8786
#घोषणा IT8790E_DEVID 0x8790
#घोषणा IT8603E_DEVID 0x8603
#घोषणा IT8620E_DEVID 0x8620
#घोषणा IT8622E_DEVID 0x8622
#घोषणा IT8623E_DEVID 0x8623
#घोषणा IT8628E_DEVID 0x8628
#घोषणा IT87_ACT_REG  0x30
#घोषणा IT87_BASE_REG 0x60

/* Logical device 7 रेजिस्टरs (IT8712F and later) */
#घोषणा IT87_SIO_GPIO1_REG	0x25
#घोषणा IT87_SIO_GPIO2_REG	0x26
#घोषणा IT87_SIO_GPIO3_REG	0x27
#घोषणा IT87_SIO_GPIO4_REG	0x28
#घोषणा IT87_SIO_GPIO5_REG	0x29
#घोषणा IT87_SIO_PINX1_REG	0x2a	/* Pin selection */
#घोषणा IT87_SIO_PINX2_REG	0x2c	/* Pin selection */
#घोषणा IT87_SIO_SPI_REG	0xef	/* SPI function pin select */
#घोषणा IT87_SIO_VID_REG	0xfc	/* VID value */
#घोषणा IT87_SIO_BEEP_PIN_REG	0xf6	/* Beep pin mapping */

/* Update battery voltage after every पढ़ोing अगर true */
अटल bool update_vbat;

/* Not all BIOSes properly configure the PWM रेजिस्टरs */
अटल bool fix_pwm_polarity;

/* Many IT87 स्थिरants specअगरied below */

/* Length of ISA address segment */
#घोषणा IT87_EXTENT 8

/* Length of ISA address segment क्रम Environmental Controller */
#घोषणा IT87_EC_EXTENT 2

/* Offset of EC रेजिस्टरs from ISA base address */
#घोषणा IT87_EC_OFFSET 5

/* Where are the ISA address/data रेजिस्टरs relative to the EC base address */
#घोषणा IT87_ADDR_REG_OFFSET 0
#घोषणा IT87_DATA_REG_OFFSET 1

/*----- The IT87 रेजिस्टरs -----*/

#घोषणा IT87_REG_CONFIG        0x00

#घोषणा IT87_REG_ALARM1        0x01
#घोषणा IT87_REG_ALARM2        0x02
#घोषणा IT87_REG_ALARM3        0x03

/*
 * The IT8718F and IT8720F have the VID value in a dअगरferent रेजिस्टर, in
 * Super-I/O configuration space.
 */
#घोषणा IT87_REG_VID           0x0a
/*
 * The IT8705F and IT8712F earlier than revision 0x08 use रेजिस्टर 0x0b
 * क्रम fan भागisors. Later IT8712F revisions must use 16-bit tachometer
 * mode.
 */
#घोषणा IT87_REG_FAN_DIV       0x0b
#घोषणा IT87_REG_FAN_16BIT     0x0c

/*
 * Monitors:
 * - up to 13 voltage (0 to 7, battery, avcc, 10 to 12)
 * - up to 6 temp (1 to 6)
 * - up to 6 fan (1 to 6)
 */

अटल स्थिर u8 IT87_REG_FAN[]         = अणु 0x0d, 0x0e, 0x0f, 0x80, 0x82, 0x4c पूर्ण;
अटल स्थिर u8 IT87_REG_FAN_MIN[]     = अणु 0x10, 0x11, 0x12, 0x84, 0x86, 0x4e पूर्ण;
अटल स्थिर u8 IT87_REG_FANX[]        = अणु 0x18, 0x19, 0x1a, 0x81, 0x83, 0x4d पूर्ण;
अटल स्थिर u8 IT87_REG_FANX_MIN[]    = अणु 0x1b, 0x1c, 0x1d, 0x85, 0x87, 0x4f पूर्ण;
अटल स्थिर u8 IT87_REG_TEMP_OFFSET[] = अणु 0x56, 0x57, 0x59 पूर्ण;

#घोषणा IT87_REG_FAN_MAIN_CTRL 0x13
#घोषणा IT87_REG_FAN_CTL       0x14
अटल स्थिर u8 IT87_REG_PWM[]         = अणु 0x15, 0x16, 0x17, 0x7f, 0xa7, 0xaf पूर्ण;
अटल स्थिर u8 IT87_REG_PWM_DUTY[]    = अणु 0x63, 0x6b, 0x73, 0x7b, 0xa3, 0xab पूर्ण;

अटल स्थिर u8 IT87_REG_VIN[]	= अणु 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26,
				    0x27, 0x28, 0x2f, 0x2c, 0x2d, 0x2e पूर्ण;

#घोषणा IT87_REG_TEMP(nr)      (0x29 + (nr))

#घोषणा IT87_REG_VIN_MAX(nr)   (0x30 + (nr) * 2)
#घोषणा IT87_REG_VIN_MIN(nr)   (0x31 + (nr) * 2)
#घोषणा IT87_REG_TEMP_HIGH(nr) (0x40 + (nr) * 2)
#घोषणा IT87_REG_TEMP_LOW(nr)  (0x41 + (nr) * 2)

#घोषणा IT87_REG_VIN_ENABLE    0x50
#घोषणा IT87_REG_TEMP_ENABLE   0x51
#घोषणा IT87_REG_TEMP_EXTRA    0x55
#घोषणा IT87_REG_BEEP_ENABLE   0x5c

#घोषणा IT87_REG_CHIPID        0x58

अटल स्थिर u8 IT87_REG_AUTO_BASE[] = अणु 0x60, 0x68, 0x70, 0x78, 0xa0, 0xa8 पूर्ण;

#घोषणा IT87_REG_AUTO_TEMP(nr, i) (IT87_REG_AUTO_BASE[nr] + (i))
#घोषणा IT87_REG_AUTO_PWM(nr, i)  (IT87_REG_AUTO_BASE[nr] + 5 + (i))

#घोषणा IT87_REG_TEMP456_ENABLE	0x77

#घोषणा NUM_VIN			ARRAY_SIZE(IT87_REG_VIN)
#घोषणा NUM_VIN_LIMIT		8
#घोषणा NUM_TEMP		6
#घोषणा NUM_TEMP_OFFSET		ARRAY_SIZE(IT87_REG_TEMP_OFFSET)
#घोषणा NUM_TEMP_LIMIT		3
#घोषणा NUM_FAN			ARRAY_SIZE(IT87_REG_FAN)
#घोषणा NUM_FAN_DIV		3
#घोषणा NUM_PWM			ARRAY_SIZE(IT87_REG_PWM)
#घोषणा NUM_AUTO_PWM		ARRAY_SIZE(IT87_REG_PWM)

काष्ठा it87_devices अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर * स्थिर suffix;
	u32 features;
	u8 peci_mask;
	u8 old_peci_mask;
पूर्ण;

#घोषणा FEAT_12MV_ADC		BIT(0)
#घोषणा FEAT_NEWER_AUTOPWM	BIT(1)
#घोषणा FEAT_OLD_AUTOPWM	BIT(2)
#घोषणा FEAT_16BIT_FANS		BIT(3)
#घोषणा FEAT_TEMP_OFFSET	BIT(4)
#घोषणा FEAT_TEMP_PECI		BIT(5)
#घोषणा FEAT_TEMP_OLD_PECI	BIT(6)
#घोषणा FEAT_FAN16_CONFIG	BIT(7)	/* Need to enable 16-bit fans */
#घोषणा FEAT_FIVE_FANS		BIT(8)	/* Supports five fans */
#घोषणा FEAT_VID		BIT(9)	/* Set अगर chip supports VID */
#घोषणा FEAT_IN7_INTERNAL	BIT(10)	/* Set अगर in7 is पूर्णांकernal */
#घोषणा FEAT_SIX_FANS		BIT(11)	/* Supports six fans */
#घोषणा FEAT_10_9MV_ADC		BIT(12)
#घोषणा FEAT_AVCC3		BIT(13)	/* Chip supports in9/AVCC3 */
#घोषणा FEAT_FIVE_PWM		BIT(14)	/* Chip supports 5 pwm chn */
#घोषणा FEAT_SIX_PWM		BIT(15)	/* Chip supports 6 pwm chn */
#घोषणा FEAT_PWM_FREQ2		BIT(16)	/* Separate pwm freq 2 */
#घोषणा FEAT_SIX_TEMP		BIT(17)	/* Up to 6 temp sensors */
#घोषणा FEAT_VIN3_5V		BIT(18)	/* VIN3 connected to +5V */

अटल स्थिर काष्ठा it87_devices it87_devices[] = अणु
	[it87] = अणु
		.name = "it87",
		.suffix = "F",
		.features = FEAT_OLD_AUTOPWM,	/* may need to overग_लिखो */
	पूर्ण,
	[it8712] = अणु
		.name = "it8712",
		.suffix = "F",
		.features = FEAT_OLD_AUTOPWM | FEAT_VID,
						/* may need to overग_लिखो */
	पूर्ण,
	[it8716] = अणु
		.name = "it8716",
		.suffix = "F",
		.features = FEAT_16BIT_FANS | FEAT_TEMP_OFFSET | FEAT_VID
		  | FEAT_FAN16_CONFIG | FEAT_FIVE_FANS | FEAT_PWM_FREQ2,
	पूर्ण,
	[it8718] = अणु
		.name = "it8718",
		.suffix = "F",
		.features = FEAT_16BIT_FANS | FEAT_TEMP_OFFSET | FEAT_VID
		  | FEAT_TEMP_OLD_PECI | FEAT_FAN16_CONFIG | FEAT_FIVE_FANS
		  | FEAT_PWM_FREQ2,
		.old_peci_mask = 0x4,
	पूर्ण,
	[it8720] = अणु
		.name = "it8720",
		.suffix = "F",
		.features = FEAT_16BIT_FANS | FEAT_TEMP_OFFSET | FEAT_VID
		  | FEAT_TEMP_OLD_PECI | FEAT_FAN16_CONFIG | FEAT_FIVE_FANS
		  | FEAT_PWM_FREQ2,
		.old_peci_mask = 0x4,
	पूर्ण,
	[it8721] = अणु
		.name = "it8721",
		.suffix = "F",
		.features = FEAT_NEWER_AUTOPWM | FEAT_12MV_ADC | FEAT_16BIT_FANS
		  | FEAT_TEMP_OFFSET | FEAT_TEMP_OLD_PECI | FEAT_TEMP_PECI
		  | FEAT_FAN16_CONFIG | FEAT_FIVE_FANS | FEAT_IN7_INTERNAL
		  | FEAT_PWM_FREQ2,
		.peci_mask = 0x05,
		.old_peci_mask = 0x02,	/* Actually reports PCH */
	पूर्ण,
	[it8728] = अणु
		.name = "it8728",
		.suffix = "F",
		.features = FEAT_NEWER_AUTOPWM | FEAT_12MV_ADC | FEAT_16BIT_FANS
		  | FEAT_TEMP_OFFSET | FEAT_TEMP_PECI | FEAT_FIVE_FANS
		  | FEAT_IN7_INTERNAL | FEAT_PWM_FREQ2,
		.peci_mask = 0x07,
	पूर्ण,
	[it8732] = अणु
		.name = "it8732",
		.suffix = "F",
		.features = FEAT_NEWER_AUTOPWM | FEAT_16BIT_FANS
		  | FEAT_TEMP_OFFSET | FEAT_TEMP_OLD_PECI | FEAT_TEMP_PECI
		  | FEAT_10_9MV_ADC | FEAT_IN7_INTERNAL,
		.peci_mask = 0x07,
		.old_peci_mask = 0x02,	/* Actually reports PCH */
	पूर्ण,
	[it8771] = अणु
		.name = "it8771",
		.suffix = "E",
		.features = FEAT_NEWER_AUTOPWM | FEAT_12MV_ADC | FEAT_16BIT_FANS
		  | FEAT_TEMP_OFFSET | FEAT_TEMP_PECI | FEAT_IN7_INTERNAL
		  | FEAT_PWM_FREQ2,
				/* PECI: guesswork */
				/* 12mV ADC (OHM) */
				/* 16 bit fans (OHM) */
				/* three fans, always 16 bit (guesswork) */
		.peci_mask = 0x07,
	पूर्ण,
	[it8772] = अणु
		.name = "it8772",
		.suffix = "E",
		.features = FEAT_NEWER_AUTOPWM | FEAT_12MV_ADC | FEAT_16BIT_FANS
		  | FEAT_TEMP_OFFSET | FEAT_TEMP_PECI | FEAT_IN7_INTERNAL
		  | FEAT_PWM_FREQ2,
				/* PECI (coreboot) */
				/* 12mV ADC (HWSensors4, OHM) */
				/* 16 bit fans (HWSensors4, OHM) */
				/* three fans, always 16 bit (datasheet) */
		.peci_mask = 0x07,
	पूर्ण,
	[it8781] = अणु
		.name = "it8781",
		.suffix = "F",
		.features = FEAT_16BIT_FANS | FEAT_TEMP_OFFSET
		  | FEAT_TEMP_OLD_PECI | FEAT_FAN16_CONFIG | FEAT_PWM_FREQ2,
		.old_peci_mask = 0x4,
	पूर्ण,
	[it8782] = अणु
		.name = "it8782",
		.suffix = "F",
		.features = FEAT_16BIT_FANS | FEAT_TEMP_OFFSET
		  | FEAT_TEMP_OLD_PECI | FEAT_FAN16_CONFIG | FEAT_PWM_FREQ2,
		.old_peci_mask = 0x4,
	पूर्ण,
	[it8783] = अणु
		.name = "it8783",
		.suffix = "E/F",
		.features = FEAT_16BIT_FANS | FEAT_TEMP_OFFSET
		  | FEAT_TEMP_OLD_PECI | FEAT_FAN16_CONFIG | FEAT_PWM_FREQ2,
		.old_peci_mask = 0x4,
	पूर्ण,
	[it8786] = अणु
		.name = "it8786",
		.suffix = "E",
		.features = FEAT_NEWER_AUTOPWM | FEAT_12MV_ADC | FEAT_16BIT_FANS
		  | FEAT_TEMP_OFFSET | FEAT_TEMP_PECI | FEAT_IN7_INTERNAL
		  | FEAT_PWM_FREQ2,
		.peci_mask = 0x07,
	पूर्ण,
	[it8790] = अणु
		.name = "it8790",
		.suffix = "E",
		.features = FEAT_NEWER_AUTOPWM | FEAT_12MV_ADC | FEAT_16BIT_FANS
		  | FEAT_TEMP_OFFSET | FEAT_TEMP_PECI | FEAT_IN7_INTERNAL
		  | FEAT_PWM_FREQ2,
		.peci_mask = 0x07,
	पूर्ण,
	[it8792] = अणु
		.name = "it8792",
		.suffix = "E",
		.features = FEAT_NEWER_AUTOPWM | FEAT_16BIT_FANS
		  | FEAT_TEMP_OFFSET | FEAT_TEMP_OLD_PECI | FEAT_TEMP_PECI
		  | FEAT_10_9MV_ADC | FEAT_IN7_INTERNAL,
		.peci_mask = 0x07,
		.old_peci_mask = 0x02,	/* Actually reports PCH */
	पूर्ण,
	[it8603] = अणु
		.name = "it8603",
		.suffix = "E",
		.features = FEAT_NEWER_AUTOPWM | FEAT_12MV_ADC | FEAT_16BIT_FANS
		  | FEAT_TEMP_OFFSET | FEAT_TEMP_PECI | FEAT_IN7_INTERNAL
		  | FEAT_AVCC3 | FEAT_PWM_FREQ2,
		.peci_mask = 0x07,
	पूर्ण,
	[it8620] = अणु
		.name = "it8620",
		.suffix = "E",
		.features = FEAT_NEWER_AUTOPWM | FEAT_12MV_ADC | FEAT_16BIT_FANS
		  | FEAT_TEMP_OFFSET | FEAT_TEMP_PECI | FEAT_SIX_FANS
		  | FEAT_IN7_INTERNAL | FEAT_SIX_PWM | FEAT_PWM_FREQ2
		  | FEAT_SIX_TEMP | FEAT_VIN3_5V,
		.peci_mask = 0x07,
	पूर्ण,
	[it8622] = अणु
		.name = "it8622",
		.suffix = "E",
		.features = FEAT_NEWER_AUTOPWM | FEAT_12MV_ADC | FEAT_16BIT_FANS
		  | FEAT_TEMP_OFFSET | FEAT_TEMP_PECI | FEAT_FIVE_FANS
		  | FEAT_FIVE_PWM | FEAT_IN7_INTERNAL | FEAT_PWM_FREQ2
		  | FEAT_AVCC3 | FEAT_VIN3_5V,
		.peci_mask = 0x07,
	पूर्ण,
	[it8628] = अणु
		.name = "it8628",
		.suffix = "E",
		.features = FEAT_NEWER_AUTOPWM | FEAT_12MV_ADC | FEAT_16BIT_FANS
		  | FEAT_TEMP_OFFSET | FEAT_TEMP_PECI | FEAT_SIX_FANS
		  | FEAT_IN7_INTERNAL | FEAT_SIX_PWM | FEAT_PWM_FREQ2
		  | FEAT_SIX_TEMP | FEAT_VIN3_5V,
		.peci_mask = 0x07,
	पूर्ण,
पूर्ण;

#घोषणा has_16bit_fans(data)	((data)->features & FEAT_16BIT_FANS)
#घोषणा has_12mv_adc(data)	((data)->features & FEAT_12MV_ADC)
#घोषणा has_10_9mv_adc(data)	((data)->features & FEAT_10_9MV_ADC)
#घोषणा has_newer_स्वतःpwm(data)	((data)->features & FEAT_NEWER_AUTOPWM)
#घोषणा has_old_स्वतःpwm(data)	((data)->features & FEAT_OLD_AUTOPWM)
#घोषणा has_temp_offset(data)	((data)->features & FEAT_TEMP_OFFSET)
#घोषणा has_temp_peci(data, nr)	(((data)->features & FEAT_TEMP_PECI) && \
				 ((data)->peci_mask & BIT(nr)))
#घोषणा has_temp_old_peci(data, nr) \
				(((data)->features & FEAT_TEMP_OLD_PECI) && \
				 ((data)->old_peci_mask & BIT(nr)))
#घोषणा has_fan16_config(data)	((data)->features & FEAT_FAN16_CONFIG)
#घोषणा has_five_fans(data)	((data)->features & (FEAT_FIVE_FANS | \
						     FEAT_SIX_FANS))
#घोषणा has_vid(data)		((data)->features & FEAT_VID)
#घोषणा has_in7_पूर्णांकernal(data)	((data)->features & FEAT_IN7_INTERNAL)
#घोषणा has_six_fans(data)	((data)->features & FEAT_SIX_FANS)
#घोषणा has_avcc3(data)		((data)->features & FEAT_AVCC3)
#घोषणा has_five_pwm(data)	((data)->features & (FEAT_FIVE_PWM \
						     | FEAT_SIX_PWM))
#घोषणा has_six_pwm(data)	((data)->features & FEAT_SIX_PWM)
#घोषणा has_pwm_freq2(data)	((data)->features & FEAT_PWM_FREQ2)
#घोषणा has_six_temp(data)	((data)->features & FEAT_SIX_TEMP)
#घोषणा has_vin3_5v(data)	((data)->features & FEAT_VIN3_5V)

काष्ठा it87_sio_data अणु
	पूर्णांक sioaddr;
	क्रमागत chips type;
	/* Values पढ़ो from Super-I/O config space */
	u8 revision;
	u8 vid_value;
	u8 beep_pin;
	u8 पूर्णांकernal;	/* Internal sensors can be labeled */
	bool need_in7_reroute;
	/* Features skipped based on config or DMI */
	u16 skip_in;
	u8 skip_vid;
	u8 skip_fan;
	u8 skip_pwm;
	u8 skip_temp;
पूर्ण;

/*
 * For each रेजिस्टरed chip, we need to keep some data in memory.
 * The काष्ठाure is dynamically allocated.
 */
काष्ठा it87_data अणु
	स्थिर काष्ठा attribute_group *groups[7];
	पूर्णांक sioaddr;
	क्रमागत chips type;
	u32 features;
	u8 peci_mask;
	u8 old_peci_mask;

	अचिन्हित लघु addr;
	स्थिर अक्षर *name;
	काष्ठा mutex update_lock;
	अक्षर valid;		/* !=0 अगर following fields are valid */
	अचिन्हित दीर्घ last_updated;	/* In jअगरfies */

	u16 in_scaled;		/* Internal voltage sensors are scaled */
	u16 in_पूर्णांकernal;	/* Bitfield, पूर्णांकernal sensors (क्रम labels) */
	u16 has_in;		/* Bitfield, voltage sensors enabled */
	u8 in[NUM_VIN][3];		/* [nr][0]=in, [1]=min, [2]=max */
	bool need_in7_reroute;
	u8 has_fan;		/* Bitfield, fans enabled */
	u16 fan[NUM_FAN][2];	/* Register values, [nr][0]=fan, [1]=min */
	u8 has_temp;		/* Bitfield, temp sensors enabled */
	s8 temp[NUM_TEMP][4];	/* [nr][0]=temp, [1]=min, [2]=max, [3]=offset */
	u8 sensor;		/* Register value (IT87_REG_TEMP_ENABLE) */
	u8 extra;		/* Register value (IT87_REG_TEMP_EXTRA) */
	u8 fan_भाग[NUM_FAN_DIV];/* Register encoding, shअगरted right */
	bool has_vid;		/* True अगर VID supported */
	u8 vid;			/* Register encoding, combined */
	u8 vrm;
	u32 alarms;		/* Register encoding, combined */
	bool has_beep;		/* true अगर beep supported */
	u8 beeps;		/* Register encoding */
	u8 fan_मुख्य_ctrl;	/* Register value */
	u8 fan_ctl;		/* Register value */

	/*
	 * The following 3 arrays correspond to the same रेजिस्टरs up to
	 * the IT8720F. The meaning of bits 6-0 depends on the value of bit
	 * 7, and we want to preserve settings on mode changes, so we have
	 * to track all values separately.
	 * Starting with the IT8721F, the manual PWM duty cycles are stored
	 * in separate रेजिस्टरs (8-bit values), so the separate tracking
	 * is no दीर्घer needed, but it is still करोne to keep the driver
	 * simple.
	 */
	u8 has_pwm;		/* Bitfield, pwm control enabled */
	u8 pwm_ctrl[NUM_PWM];	/* Register value */
	u8 pwm_duty[NUM_PWM];	/* Manual PWM value set by user */
	u8 pwm_temp_map[NUM_PWM];/* PWM to temp. chan. mapping (bits 1-0) */

	/* Automatic fan speed control रेजिस्टरs */
	u8 स्वतः_pwm[NUM_AUTO_PWM][4];	/* [nr][3] is hard-coded */
	s8 स्वतः_temp[NUM_AUTO_PWM][5];	/* [nr][0] is poपूर्णांक1_temp_hyst */
पूर्ण;

अटल पूर्णांक adc_lsb(स्थिर काष्ठा it87_data *data, पूर्णांक nr)
अणु
	पूर्णांक lsb;

	अगर (has_12mv_adc(data))
		lsb = 120;
	अन्यथा अगर (has_10_9mv_adc(data))
		lsb = 109;
	अन्यथा
		lsb = 160;
	अगर (data->in_scaled & BIT(nr))
		lsb <<= 1;
	वापस lsb;
पूर्ण

अटल u8 in_to_reg(स्थिर काष्ठा it87_data *data, पूर्णांक nr, दीर्घ val)
अणु
	val = DIV_ROUND_CLOSEST(val * 10, adc_lsb(data, nr));
	वापस clamp_val(val, 0, 255);
पूर्ण

अटल पूर्णांक in_from_reg(स्थिर काष्ठा it87_data *data, पूर्णांक nr, पूर्णांक val)
अणु
	वापस DIV_ROUND_CLOSEST(val * adc_lsb(data, nr), 10);
पूर्ण

अटल अंतरभूत u8 FAN_TO_REG(दीर्घ rpm, पूर्णांक भाग)
अणु
	अगर (rpm == 0)
		वापस 255;
	rpm = clamp_val(rpm, 1, 1000000);
	वापस clamp_val((1350000 + rpm * भाग / 2) / (rpm * भाग), 1, 254);
पूर्ण

अटल अंतरभूत u16 FAN16_TO_REG(दीर्घ rpm)
अणु
	अगर (rpm == 0)
		वापस 0xffff;
	वापस clamp_val((1350000 + rpm) / (rpm * 2), 1, 0xfffe);
पूर्ण

#घोषणा FAN_FROM_REG(val, भाग) ((val) == 0 ? -1 : (val) == 255 ? 0 : \
				1350000 / ((val) * (भाग)))
/* The भागider is fixed to 2 in 16-bit mode */
#घोषणा FAN16_FROM_REG(val) ((val) == 0 ? -1 : (val) == 0xffff ? 0 : \
			     1350000 / ((val) * 2))

#घोषणा TEMP_TO_REG(val) (clamp_val(((val) < 0 ? (((val) - 500) / 1000) : \
				    ((val) + 500) / 1000), -128, 127))
#घोषणा TEMP_FROM_REG(val) ((val) * 1000)

अटल u8 pwm_to_reg(स्थिर काष्ठा it87_data *data, दीर्घ val)
अणु
	अगर (has_newer_स्वतःpwm(data))
		वापस val;
	अन्यथा
		वापस val >> 1;
पूर्ण

अटल पूर्णांक pwm_from_reg(स्थिर काष्ठा it87_data *data, u8 reg)
अणु
	अगर (has_newer_स्वतःpwm(data))
		वापस reg;
	अन्यथा
		वापस (reg & 0x7f) << 1;
पूर्ण

अटल पूर्णांक DIV_TO_REG(पूर्णांक val)
अणु
	पूर्णांक answer = 0;

	जबतक (answer < 7 && (val >>= 1))
		answer++;
	वापस answer;
पूर्ण

#घोषणा DIV_FROM_REG(val) BIT(val)

/*
 * PWM base frequencies. The frequency has to be भागided by either 128 or 256,
 * depending on the chip type, to calculate the actual PWM frequency.
 *
 * Some of the chip datasheets suggest a base frequency of 51 kHz instead
 * of 750 kHz क्रम the slowest base frequency, resulting in a PWM frequency
 * of 200 Hz. Someबार both PWM frequency select रेजिस्टरs are affected,
 * someबार just one. It is unknown अगर this is a datasheet error or real,
 * so this is ignored क्रम now.
 */
अटल स्थिर अचिन्हित पूर्णांक pwm_freq[8] = अणु
	48000000,
	24000000,
	12000000,
	8000000,
	6000000,
	3000000,
	1500000,
	750000,
पूर्ण;

/*
 * Must be called with data->update_lock held, except during initialization.
 * We ignore the IT87 BUSY flag at this moment - it could lead to deadlocks,
 * would slow करोwn the IT87 access and should not be necessary.
 */
अटल पूर्णांक it87_पढ़ो_value(काष्ठा it87_data *data, u8 reg)
अणु
	outb_p(reg, data->addr + IT87_ADDR_REG_OFFSET);
	वापस inb_p(data->addr + IT87_DATA_REG_OFFSET);
पूर्ण

/*
 * Must be called with data->update_lock held, except during initialization.
 * We ignore the IT87 BUSY flag at this moment - it could lead to deadlocks,
 * would slow करोwn the IT87 access and should not be necessary.
 */
अटल व्योम it87_ग_लिखो_value(काष्ठा it87_data *data, u8 reg, u8 value)
अणु
	outb_p(reg, data->addr + IT87_ADDR_REG_OFFSET);
	outb_p(value, data->addr + IT87_DATA_REG_OFFSET);
पूर्ण

अटल व्योम it87_update_pwm_ctrl(काष्ठा it87_data *data, पूर्णांक nr)
अणु
	data->pwm_ctrl[nr] = it87_पढ़ो_value(data, IT87_REG_PWM[nr]);
	अगर (has_newer_स्वतःpwm(data)) अणु
		data->pwm_temp_map[nr] = data->pwm_ctrl[nr] & 0x03;
		data->pwm_duty[nr] = it87_पढ़ो_value(data,
						     IT87_REG_PWM_DUTY[nr]);
	पूर्ण अन्यथा अणु
		अगर (data->pwm_ctrl[nr] & 0x80)	/* Automatic mode */
			data->pwm_temp_map[nr] = data->pwm_ctrl[nr] & 0x03;
		अन्यथा				/* Manual mode */
			data->pwm_duty[nr] = data->pwm_ctrl[nr] & 0x7f;
	पूर्ण

	अगर (has_old_स्वतःpwm(data)) अणु
		पूर्णांक i;

		क्रम (i = 0; i < 5 ; i++)
			data->स्वतः_temp[nr][i] = it87_पढ़ो_value(data,
						IT87_REG_AUTO_TEMP(nr, i));
		क्रम (i = 0; i < 3 ; i++)
			data->स्वतः_pwm[nr][i] = it87_पढ़ो_value(data,
						IT87_REG_AUTO_PWM(nr, i));
	पूर्ण अन्यथा अगर (has_newer_स्वतःpwm(data)) अणु
		पूर्णांक i;

		/*
		 * 0: temperature hysteresis (base + 5)
		 * 1: fan off temperature (base + 0)
		 * 2: fan start temperature (base + 1)
		 * 3: fan max temperature (base + 2)
		 */
		data->स्वतः_temp[nr][0] =
			it87_पढ़ो_value(data, IT87_REG_AUTO_TEMP(nr, 5));

		क्रम (i = 0; i < 3 ; i++)
			data->स्वतः_temp[nr][i + 1] =
				it87_पढ़ो_value(data,
						IT87_REG_AUTO_TEMP(nr, i));
		/*
		 * 0: start pwm value (base + 3)
		 * 1: pwm slope (base + 4, 1/8th pwm)
		 */
		data->स्वतः_pwm[nr][0] =
			it87_पढ़ो_value(data, IT87_REG_AUTO_TEMP(nr, 3));
		data->स्वतः_pwm[nr][1] =
			it87_पढ़ो_value(data, IT87_REG_AUTO_TEMP(nr, 4));
	पूर्ण
पूर्ण

अटल काष्ठा it87_data *it87_update_device(काष्ठा device *dev)
अणु
	काष्ठा it87_data *data = dev_get_drvdata(dev);
	पूर्णांक i;

	mutex_lock(&data->update_lock);

	अगर (समय_after(jअगरfies, data->last_updated + HZ + HZ / 2) ||
	    !data->valid) अणु
		अगर (update_vbat) अणु
			/*
			 * Cleared after each update, so reenable.  Value
			 * वापसed by this पढ़ो will be previous value
			 */
			it87_ग_लिखो_value(data, IT87_REG_CONFIG,
				it87_पढ़ो_value(data, IT87_REG_CONFIG) | 0x40);
		पूर्ण
		क्रम (i = 0; i < NUM_VIN; i++) अणु
			अगर (!(data->has_in & BIT(i)))
				जारी;

			data->in[i][0] =
				it87_पढ़ो_value(data, IT87_REG_VIN[i]);

			/* VBAT and AVCC करोn't have limit रेजिस्टरs */
			अगर (i >= NUM_VIN_LIMIT)
				जारी;

			data->in[i][1] =
				it87_पढ़ो_value(data, IT87_REG_VIN_MIN(i));
			data->in[i][2] =
				it87_पढ़ो_value(data, IT87_REG_VIN_MAX(i));
		पूर्ण

		क्रम (i = 0; i < NUM_FAN; i++) अणु
			/* Skip disabled fans */
			अगर (!(data->has_fan & BIT(i)))
				जारी;

			data->fan[i][1] =
				it87_पढ़ो_value(data, IT87_REG_FAN_MIN[i]);
			data->fan[i][0] = it87_पढ़ो_value(data,
				       IT87_REG_FAN[i]);
			/* Add high byte अगर in 16-bit mode */
			अगर (has_16bit_fans(data)) अणु
				data->fan[i][0] |= it87_पढ़ो_value(data,
						IT87_REG_FANX[i]) << 8;
				data->fan[i][1] |= it87_पढ़ो_value(data,
						IT87_REG_FANX_MIN[i]) << 8;
			पूर्ण
		पूर्ण
		क्रम (i = 0; i < NUM_TEMP; i++) अणु
			अगर (!(data->has_temp & BIT(i)))
				जारी;
			data->temp[i][0] =
				it87_पढ़ो_value(data, IT87_REG_TEMP(i));

			अगर (has_temp_offset(data) && i < NUM_TEMP_OFFSET)
				data->temp[i][3] =
				  it87_पढ़ो_value(data,
						  IT87_REG_TEMP_OFFSET[i]);

			अगर (i >= NUM_TEMP_LIMIT)
				जारी;

			data->temp[i][1] =
				it87_पढ़ो_value(data, IT87_REG_TEMP_LOW(i));
			data->temp[i][2] =
				it87_पढ़ो_value(data, IT87_REG_TEMP_HIGH(i));
		पूर्ण

		/* Newer chips करोn't have घड़ी भागiders */
		अगर ((data->has_fan & 0x07) && !has_16bit_fans(data)) अणु
			i = it87_पढ़ो_value(data, IT87_REG_FAN_DIV);
			data->fan_भाग[0] = i & 0x07;
			data->fan_भाग[1] = (i >> 3) & 0x07;
			data->fan_भाग[2] = (i & 0x40) ? 3 : 1;
		पूर्ण

		data->alarms =
			it87_पढ़ो_value(data, IT87_REG_ALARM1) |
			(it87_पढ़ो_value(data, IT87_REG_ALARM2) << 8) |
			(it87_पढ़ो_value(data, IT87_REG_ALARM3) << 16);
		data->beeps = it87_पढ़ो_value(data, IT87_REG_BEEP_ENABLE);

		data->fan_मुख्य_ctrl = it87_पढ़ो_value(data,
				IT87_REG_FAN_MAIN_CTRL);
		data->fan_ctl = it87_पढ़ो_value(data, IT87_REG_FAN_CTL);
		क्रम (i = 0; i < NUM_PWM; i++) अणु
			अगर (!(data->has_pwm & BIT(i)))
				जारी;
			it87_update_pwm_ctrl(data, i);
		पूर्ण

		data->sensor = it87_पढ़ो_value(data, IT87_REG_TEMP_ENABLE);
		data->extra = it87_पढ़ो_value(data, IT87_REG_TEMP_EXTRA);
		/*
		 * The IT8705F करोes not have VID capability.
		 * The IT8718F and later करोn't use IT87_REG_VID क्रम the
		 * same purpose.
		 */
		अगर (data->type == it8712 || data->type == it8716) अणु
			data->vid = it87_पढ़ो_value(data, IT87_REG_VID);
			/*
			 * The older IT8712F revisions had only 5 VID pins,
			 * but we assume it is always safe to पढ़ो 6 bits.
			 */
			data->vid &= 0x3f;
		पूर्ण
		data->last_updated = jअगरfies;
		data->valid = 1;
	पूर्ण

	mutex_unlock(&data->update_lock);

	वापस data;
पूर्ण

अटल sमाप_प्रकार show_in(काष्ठा device *dev, काष्ठा device_attribute *attr,
		       अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	काष्ठा it87_data *data = it87_update_device(dev);
	पूर्णांक index = sattr->index;
	पूर्णांक nr = sattr->nr;

	वापस प्र_लिखो(buf, "%d\n", in_from_reg(data, nr, data->in[nr][index]));
पूर्ण

अटल sमाप_प्रकार set_in(काष्ठा device *dev, काष्ठा device_attribute *attr,
		      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	काष्ठा it87_data *data = dev_get_drvdata(dev);
	पूर्णांक index = sattr->index;
	पूर्णांक nr = sattr->nr;
	अचिन्हित दीर्घ val;

	अगर (kम_से_अदीर्घ(buf, 10, &val) < 0)
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	data->in[nr][index] = in_to_reg(data, nr, val);
	it87_ग_लिखो_value(data,
			 index == 1 ? IT87_REG_VIN_MIN(nr)
				    : IT87_REG_VIN_MAX(nr),
			 data->in[nr][index]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_2(in0_input, S_IRUGO, show_in, शून्य, 0, 0);
अटल SENSOR_DEVICE_ATTR_2(in0_min, S_IRUGO | S_IWUSR, show_in, set_in,
			    0, 1);
अटल SENSOR_DEVICE_ATTR_2(in0_max, S_IRUGO | S_IWUSR, show_in, set_in,
			    0, 2);

अटल SENSOR_DEVICE_ATTR_2(in1_input, S_IRUGO, show_in, शून्य, 1, 0);
अटल SENSOR_DEVICE_ATTR_2(in1_min, S_IRUGO | S_IWUSR, show_in, set_in,
			    1, 1);
अटल SENSOR_DEVICE_ATTR_2(in1_max, S_IRUGO | S_IWUSR, show_in, set_in,
			    1, 2);

अटल SENSOR_DEVICE_ATTR_2(in2_input, S_IRUGO, show_in, शून्य, 2, 0);
अटल SENSOR_DEVICE_ATTR_2(in2_min, S_IRUGO | S_IWUSR, show_in, set_in,
			    2, 1);
अटल SENSOR_DEVICE_ATTR_2(in2_max, S_IRUGO | S_IWUSR, show_in, set_in,
			    2, 2);

अटल SENSOR_DEVICE_ATTR_2(in3_input, S_IRUGO, show_in, शून्य, 3, 0);
अटल SENSOR_DEVICE_ATTR_2(in3_min, S_IRUGO | S_IWUSR, show_in, set_in,
			    3, 1);
अटल SENSOR_DEVICE_ATTR_2(in3_max, S_IRUGO | S_IWUSR, show_in, set_in,
			    3, 2);

अटल SENSOR_DEVICE_ATTR_2(in4_input, S_IRUGO, show_in, शून्य, 4, 0);
अटल SENSOR_DEVICE_ATTR_2(in4_min, S_IRUGO | S_IWUSR, show_in, set_in,
			    4, 1);
अटल SENSOR_DEVICE_ATTR_2(in4_max, S_IRUGO | S_IWUSR, show_in, set_in,
			    4, 2);

अटल SENSOR_DEVICE_ATTR_2(in5_input, S_IRUGO, show_in, शून्य, 5, 0);
अटल SENSOR_DEVICE_ATTR_2(in5_min, S_IRUGO | S_IWUSR, show_in, set_in,
			    5, 1);
अटल SENSOR_DEVICE_ATTR_2(in5_max, S_IRUGO | S_IWUSR, show_in, set_in,
			    5, 2);

अटल SENSOR_DEVICE_ATTR_2(in6_input, S_IRUGO, show_in, शून्य, 6, 0);
अटल SENSOR_DEVICE_ATTR_2(in6_min, S_IRUGO | S_IWUSR, show_in, set_in,
			    6, 1);
अटल SENSOR_DEVICE_ATTR_2(in6_max, S_IRUGO | S_IWUSR, show_in, set_in,
			    6, 2);

अटल SENSOR_DEVICE_ATTR_2(in7_input, S_IRUGO, show_in, शून्य, 7, 0);
अटल SENSOR_DEVICE_ATTR_2(in7_min, S_IRUGO | S_IWUSR, show_in, set_in,
			    7, 1);
अटल SENSOR_DEVICE_ATTR_2(in7_max, S_IRUGO | S_IWUSR, show_in, set_in,
			    7, 2);

अटल SENSOR_DEVICE_ATTR_2(in8_input, S_IRUGO, show_in, शून्य, 8, 0);
अटल SENSOR_DEVICE_ATTR_2(in9_input, S_IRUGO, show_in, शून्य, 9, 0);
अटल SENSOR_DEVICE_ATTR_2(in10_input, S_IRUGO, show_in, शून्य, 10, 0);
अटल SENSOR_DEVICE_ATTR_2(in11_input, S_IRUGO, show_in, शून्य, 11, 0);
अटल SENSOR_DEVICE_ATTR_2(in12_input, S_IRUGO, show_in, शून्य, 12, 0);

/* Up to 6 temperatures */
अटल sमाप_प्रकार show_temp(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sattr->nr;
	पूर्णांक index = sattr->index;
	काष्ठा it87_data *data = it87_update_device(dev);

	वापस प्र_लिखो(buf, "%d\n", TEMP_FROM_REG(data->temp[nr][index]));
पूर्ण

अटल sमाप_प्रकार set_temp(काष्ठा device *dev, काष्ठा device_attribute *attr,
			स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sattr->nr;
	पूर्णांक index = sattr->index;
	काष्ठा it87_data *data = dev_get_drvdata(dev);
	दीर्घ val;
	u8 reg, regval;

	अगर (kम_से_दीर्घ(buf, 10, &val) < 0)
		वापस -EINVAL;

	mutex_lock(&data->update_lock);

	चयन (index) अणु
	शेष:
	हाल 1:
		reg = IT87_REG_TEMP_LOW(nr);
		अवरोध;
	हाल 2:
		reg = IT87_REG_TEMP_HIGH(nr);
		अवरोध;
	हाल 3:
		regval = it87_पढ़ो_value(data, IT87_REG_BEEP_ENABLE);
		अगर (!(regval & 0x80)) अणु
			regval |= 0x80;
			it87_ग_लिखो_value(data, IT87_REG_BEEP_ENABLE, regval);
		पूर्ण
		data->valid = 0;
		reg = IT87_REG_TEMP_OFFSET[nr];
		अवरोध;
	पूर्ण

	data->temp[nr][index] = TEMP_TO_REG(val);
	it87_ग_लिखो_value(data, reg, data->temp[nr][index]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_2(temp1_input, S_IRUGO, show_temp, शून्य, 0, 0);
अटल SENSOR_DEVICE_ATTR_2(temp1_min, S_IRUGO | S_IWUSR, show_temp, set_temp,
			    0, 1);
अटल SENSOR_DEVICE_ATTR_2(temp1_max, S_IRUGO | S_IWUSR, show_temp, set_temp,
			    0, 2);
अटल SENSOR_DEVICE_ATTR_2(temp1_offset, S_IRUGO | S_IWUSR, show_temp,
			    set_temp, 0, 3);
अटल SENSOR_DEVICE_ATTR_2(temp2_input, S_IRUGO, show_temp, शून्य, 1, 0);
अटल SENSOR_DEVICE_ATTR_2(temp2_min, S_IRUGO | S_IWUSR, show_temp, set_temp,
			    1, 1);
अटल SENSOR_DEVICE_ATTR_2(temp2_max, S_IRUGO | S_IWUSR, show_temp, set_temp,
			    1, 2);
अटल SENSOR_DEVICE_ATTR_2(temp2_offset, S_IRUGO | S_IWUSR, show_temp,
			    set_temp, 1, 3);
अटल SENSOR_DEVICE_ATTR_2(temp3_input, S_IRUGO, show_temp, शून्य, 2, 0);
अटल SENSOR_DEVICE_ATTR_2(temp3_min, S_IRUGO | S_IWUSR, show_temp, set_temp,
			    2, 1);
अटल SENSOR_DEVICE_ATTR_2(temp3_max, S_IRUGO | S_IWUSR, show_temp, set_temp,
			    2, 2);
अटल SENSOR_DEVICE_ATTR_2(temp3_offset, S_IRUGO | S_IWUSR, show_temp,
			    set_temp, 2, 3);
अटल SENSOR_DEVICE_ATTR_2(temp4_input, S_IRUGO, show_temp, शून्य, 3, 0);
अटल SENSOR_DEVICE_ATTR_2(temp5_input, S_IRUGO, show_temp, शून्य, 4, 0);
अटल SENSOR_DEVICE_ATTR_2(temp6_input, S_IRUGO, show_temp, शून्य, 5, 0);

अटल sमाप_प्रकार show_temp_type(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा it87_data *data = it87_update_device(dev);
	u8 reg = data->sensor;	    /* In हाल value is updated जबतक used */
	u8 extra = data->extra;

	अगर ((has_temp_peci(data, nr) && (reg >> 6 == nr + 1)) ||
	    (has_temp_old_peci(data, nr) && (extra & 0x80)))
		वापस प्र_लिखो(buf, "6\n");  /* Intel PECI */
	अगर (reg & (1 << nr))
		वापस प्र_लिखो(buf, "3\n");  /* thermal diode */
	अगर (reg & (8 << nr))
		वापस प्र_लिखो(buf, "4\n");  /* thermistor */
	वापस प्र_लिखो(buf, "0\n");      /* disabled */
पूर्ण

अटल sमाप_प्रकार set_temp_type(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;

	काष्ठा it87_data *data = dev_get_drvdata(dev);
	दीर्घ val;
	u8 reg, extra;

	अगर (kम_से_दीर्घ(buf, 10, &val) < 0)
		वापस -EINVAL;

	reg = it87_पढ़ो_value(data, IT87_REG_TEMP_ENABLE);
	reg &= ~(1 << nr);
	reg &= ~(8 << nr);
	अगर (has_temp_peci(data, nr) && (reg >> 6 == nr + 1 || val == 6))
		reg &= 0x3f;
	extra = it87_पढ़ो_value(data, IT87_REG_TEMP_EXTRA);
	अगर (has_temp_old_peci(data, nr) && ((extra & 0x80) || val == 6))
		extra &= 0x7f;
	अगर (val == 2) अणु	/* backwards compatibility */
		dev_warn(dev,
			 "Sensor type 2 is deprecated, please use 4 instead\n");
		val = 4;
	पूर्ण
	/* 3 = thermal diode; 4 = thermistor; 6 = Intel PECI; 0 = disabled */
	अगर (val == 3)
		reg |= 1 << nr;
	अन्यथा अगर (val == 4)
		reg |= 8 << nr;
	अन्यथा अगर (has_temp_peci(data, nr) && val == 6)
		reg |= (nr + 1) << 6;
	अन्यथा अगर (has_temp_old_peci(data, nr) && val == 6)
		extra |= 0x80;
	अन्यथा अगर (val != 0)
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	data->sensor = reg;
	data->extra = extra;
	it87_ग_लिखो_value(data, IT87_REG_TEMP_ENABLE, data->sensor);
	अगर (has_temp_old_peci(data, nr))
		it87_ग_लिखो_value(data, IT87_REG_TEMP_EXTRA, data->extra);
	data->valid = 0;	/* Force cache refresh */
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR(temp1_type, S_IRUGO | S_IWUSR, show_temp_type,
			  set_temp_type, 0);
अटल SENSOR_DEVICE_ATTR(temp2_type, S_IRUGO | S_IWUSR, show_temp_type,
			  set_temp_type, 1);
अटल SENSOR_DEVICE_ATTR(temp3_type, S_IRUGO | S_IWUSR, show_temp_type,
			  set_temp_type, 2);

/* 6 Fans */

अटल पूर्णांक pwm_mode(स्थिर काष्ठा it87_data *data, पूर्णांक nr)
अणु
	अगर (data->type != it8603 && nr < 3 && !(data->fan_मुख्य_ctrl & BIT(nr)))
		वापस 0;				/* Full speed */
	अगर (data->pwm_ctrl[nr] & 0x80)
		वापस 2;				/* Automatic mode */
	अगर ((data->type == it8603 || nr >= 3) &&
	    data->pwm_duty[nr] == pwm_to_reg(data, 0xff))
		वापस 0;			/* Full speed */

	वापस 1;				/* Manual mode */
पूर्ण

अटल sमाप_प्रकार show_fan(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sattr->nr;
	पूर्णांक index = sattr->index;
	पूर्णांक speed;
	काष्ठा it87_data *data = it87_update_device(dev);

	speed = has_16bit_fans(data) ?
		FAN16_FROM_REG(data->fan[nr][index]) :
		FAN_FROM_REG(data->fan[nr][index],
			     DIV_FROM_REG(data->fan_भाग[nr]));
	वापस प्र_लिखो(buf, "%d\n", speed);
पूर्ण

अटल sमाप_प्रकार show_fan_भाग(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	काष्ठा it87_data *data = it87_update_device(dev);
	पूर्णांक nr = sensor_attr->index;

	वापस प्र_लिखो(buf, "%lu\n", DIV_FROM_REG(data->fan_भाग[nr]));
पूर्ण

अटल sमाप_प्रकार show_pwm_enable(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	काष्ठा it87_data *data = it87_update_device(dev);
	पूर्णांक nr = sensor_attr->index;

	वापस प्र_लिखो(buf, "%d\n", pwm_mode(data, nr));
पूर्ण

अटल sमाप_प्रकार show_pwm(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	काष्ठा it87_data *data = it87_update_device(dev);
	पूर्णांक nr = sensor_attr->index;

	वापस प्र_लिखो(buf, "%d\n",
		       pwm_from_reg(data, data->pwm_duty[nr]));
पूर्ण

अटल sमाप_प्रकार show_pwm_freq(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	काष्ठा it87_data *data = it87_update_device(dev);
	पूर्णांक nr = sensor_attr->index;
	अचिन्हित पूर्णांक freq;
	पूर्णांक index;

	अगर (has_pwm_freq2(data) && nr == 1)
		index = (data->extra >> 4) & 0x07;
	अन्यथा
		index = (data->fan_ctl >> 4) & 0x07;

	freq = pwm_freq[index] / (has_newer_स्वतःpwm(data) ? 256 : 128);

	वापस प्र_लिखो(buf, "%u\n", freq);
पूर्ण

अटल sमाप_प्रकार set_fan(काष्ठा device *dev, काष्ठा device_attribute *attr,
		       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sattr->nr;
	पूर्णांक index = sattr->index;

	काष्ठा it87_data *data = dev_get_drvdata(dev);
	दीर्घ val;
	u8 reg;

	अगर (kम_से_दीर्घ(buf, 10, &val) < 0)
		वापस -EINVAL;

	mutex_lock(&data->update_lock);

	अगर (has_16bit_fans(data)) अणु
		data->fan[nr][index] = FAN16_TO_REG(val);
		it87_ग_लिखो_value(data, IT87_REG_FAN_MIN[nr],
				 data->fan[nr][index] & 0xff);
		it87_ग_लिखो_value(data, IT87_REG_FANX_MIN[nr],
				 data->fan[nr][index] >> 8);
	पूर्ण अन्यथा अणु
		reg = it87_पढ़ो_value(data, IT87_REG_FAN_DIV);
		चयन (nr) अणु
		हाल 0:
			data->fan_भाग[nr] = reg & 0x07;
			अवरोध;
		हाल 1:
			data->fan_भाग[nr] = (reg >> 3) & 0x07;
			अवरोध;
		हाल 2:
			data->fan_भाग[nr] = (reg & 0x40) ? 3 : 1;
			अवरोध;
		पूर्ण
		data->fan[nr][index] =
		  FAN_TO_REG(val, DIV_FROM_REG(data->fan_भाग[nr]));
		it87_ग_लिखो_value(data, IT87_REG_FAN_MIN[nr],
				 data->fan[nr][index]);
	पूर्ण

	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार set_fan_भाग(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	काष्ठा it87_data *data = dev_get_drvdata(dev);
	पूर्णांक nr = sensor_attr->index;
	अचिन्हित दीर्घ val;
	पूर्णांक min;
	u8 old;

	अगर (kम_से_अदीर्घ(buf, 10, &val) < 0)
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	old = it87_पढ़ो_value(data, IT87_REG_FAN_DIV);

	/* Save fan min limit */
	min = FAN_FROM_REG(data->fan[nr][1], DIV_FROM_REG(data->fan_भाग[nr]));

	चयन (nr) अणु
	हाल 0:
	हाल 1:
		data->fan_भाग[nr] = DIV_TO_REG(val);
		अवरोध;
	हाल 2:
		अगर (val < 8)
			data->fan_भाग[nr] = 1;
		अन्यथा
			data->fan_भाग[nr] = 3;
	पूर्ण
	val = old & 0x80;
	val |= (data->fan_भाग[0] & 0x07);
	val |= (data->fan_भाग[1] & 0x07) << 3;
	अगर (data->fan_भाग[2] == 3)
		val |= 0x1 << 6;
	it87_ग_लिखो_value(data, IT87_REG_FAN_DIV, val);

	/* Restore fan min limit */
	data->fan[nr][1] = FAN_TO_REG(min, DIV_FROM_REG(data->fan_भाग[nr]));
	it87_ग_लिखो_value(data, IT87_REG_FAN_MIN[nr], data->fan[nr][1]);

	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

/* Returns 0 अगर OK, -EINVAL otherwise */
अटल पूर्णांक check_trip_poपूर्णांकs(काष्ठा device *dev, पूर्णांक nr)
अणु
	स्थिर काष्ठा it87_data *data = dev_get_drvdata(dev);
	पूर्णांक i, err = 0;

	अगर (has_old_स्वतःpwm(data)) अणु
		क्रम (i = 0; i < 3; i++) अणु
			अगर (data->स्वतः_temp[nr][i] > data->स्वतः_temp[nr][i + 1])
				err = -EINVAL;
		पूर्ण
		क्रम (i = 0; i < 2; i++) अणु
			अगर (data->स्वतः_pwm[nr][i] > data->स्वतः_pwm[nr][i + 1])
				err = -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अगर (has_newer_स्वतःpwm(data)) अणु
		क्रम (i = 1; i < 3; i++) अणु
			अगर (data->स्वतः_temp[nr][i] > data->स्वतः_temp[nr][i + 1])
				err = -EINVAL;
		पूर्ण
	पूर्ण

	अगर (err) अणु
		dev_err(dev,
			"Inconsistent trip points, not switching to automatic mode\n");
		dev_err(dev, "Adjust the trip points and try again\n");
	पूर्ण
	वापस err;
पूर्ण

अटल sमाप_प्रकार set_pwm_enable(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	काष्ठा it87_data *data = dev_get_drvdata(dev);
	पूर्णांक nr = sensor_attr->index;
	दीर्घ val;

	अगर (kम_से_दीर्घ(buf, 10, &val) < 0 || val < 0 || val > 2)
		वापस -EINVAL;

	/* Check trip poपूर्णांकs beक्रमe चयनing to स्वतःmatic mode */
	अगर (val == 2) अणु
		अगर (check_trip_poपूर्णांकs(dev, nr) < 0)
			वापस -EINVAL;
	पूर्ण

	mutex_lock(&data->update_lock);

	अगर (val == 0) अणु
		अगर (nr < 3 && data->type != it8603) अणु
			पूर्णांक पंचांगp;
			/* make sure the fan is on when in on/off mode */
			पंचांगp = it87_पढ़ो_value(data, IT87_REG_FAN_CTL);
			it87_ग_लिखो_value(data, IT87_REG_FAN_CTL, पंचांगp | BIT(nr));
			/* set on/off mode */
			data->fan_मुख्य_ctrl &= ~BIT(nr);
			it87_ग_लिखो_value(data, IT87_REG_FAN_MAIN_CTRL,
					 data->fan_मुख्य_ctrl);
		पूर्ण अन्यथा अणु
			u8 ctrl;

			/* No on/off mode, set maximum pwm value */
			data->pwm_duty[nr] = pwm_to_reg(data, 0xff);
			it87_ग_लिखो_value(data, IT87_REG_PWM_DUTY[nr],
					 data->pwm_duty[nr]);
			/* and set manual mode */
			अगर (has_newer_स्वतःpwm(data)) अणु
				ctrl = (data->pwm_ctrl[nr] & 0x7c) |
					data->pwm_temp_map[nr];
			पूर्ण अन्यथा अणु
				ctrl = data->pwm_duty[nr];
			पूर्ण
			data->pwm_ctrl[nr] = ctrl;
			it87_ग_लिखो_value(data, IT87_REG_PWM[nr], ctrl);
		पूर्ण
	पूर्ण अन्यथा अणु
		u8 ctrl;

		अगर (has_newer_स्वतःpwm(data)) अणु
			ctrl = (data->pwm_ctrl[nr] & 0x7c) |
				data->pwm_temp_map[nr];
			अगर (val != 1)
				ctrl |= 0x80;
		पूर्ण अन्यथा अणु
			ctrl = (val == 1 ? data->pwm_duty[nr] : 0x80);
		पूर्ण
		data->pwm_ctrl[nr] = ctrl;
		it87_ग_लिखो_value(data, IT87_REG_PWM[nr], ctrl);

		अगर (data->type != it8603 && nr < 3) अणु
			/* set SmartGuardian mode */
			data->fan_मुख्य_ctrl |= BIT(nr);
			it87_ग_लिखो_value(data, IT87_REG_FAN_MAIN_CTRL,
					 data->fan_मुख्य_ctrl);
		पूर्ण
	पूर्ण

	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार set_pwm(काष्ठा device *dev, काष्ठा device_attribute *attr,
		       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	काष्ठा it87_data *data = dev_get_drvdata(dev);
	पूर्णांक nr = sensor_attr->index;
	दीर्घ val;

	अगर (kम_से_दीर्घ(buf, 10, &val) < 0 || val < 0 || val > 255)
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	it87_update_pwm_ctrl(data, nr);
	अगर (has_newer_स्वतःpwm(data)) अणु
		/*
		 * If we are in स्वतःmatic mode, the PWM duty cycle रेजिस्टर
		 * is पढ़ो-only so we can't ग_लिखो the value.
		 */
		अगर (data->pwm_ctrl[nr] & 0x80) अणु
			mutex_unlock(&data->update_lock);
			वापस -EBUSY;
		पूर्ण
		data->pwm_duty[nr] = pwm_to_reg(data, val);
		it87_ग_लिखो_value(data, IT87_REG_PWM_DUTY[nr],
				 data->pwm_duty[nr]);
	पूर्ण अन्यथा अणु
		data->pwm_duty[nr] = pwm_to_reg(data, val);
		/*
		 * If we are in manual mode, ग_लिखो the duty cycle immediately;
		 * otherwise, just store it क्रम later use.
		 */
		अगर (!(data->pwm_ctrl[nr] & 0x80)) अणु
			data->pwm_ctrl[nr] = data->pwm_duty[nr];
			it87_ग_लिखो_value(data, IT87_REG_PWM[nr],
					 data->pwm_ctrl[nr]);
		पूर्ण
	पूर्ण
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार set_pwm_freq(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	काष्ठा it87_data *data = dev_get_drvdata(dev);
	पूर्णांक nr = sensor_attr->index;
	अचिन्हित दीर्घ val;
	पूर्णांक i;

	अगर (kम_से_अदीर्घ(buf, 10, &val) < 0)
		वापस -EINVAL;

	val = clamp_val(val, 0, 1000000);
	val *= has_newer_स्वतःpwm(data) ? 256 : 128;

	/* Search क्रम the nearest available frequency */
	क्रम (i = 0; i < 7; i++) अणु
		अगर (val > (pwm_freq[i] + pwm_freq[i + 1]) / 2)
			अवरोध;
	पूर्ण

	mutex_lock(&data->update_lock);
	अगर (nr == 0) अणु
		data->fan_ctl = it87_पढ़ो_value(data, IT87_REG_FAN_CTL) & 0x8f;
		data->fan_ctl |= i << 4;
		it87_ग_लिखो_value(data, IT87_REG_FAN_CTL, data->fan_ctl);
	पूर्ण अन्यथा अणु
		data->extra = it87_पढ़ो_value(data, IT87_REG_TEMP_EXTRA) & 0x8f;
		data->extra |= i << 4;
		it87_ग_लिखो_value(data, IT87_REG_TEMP_EXTRA, data->extra);
	पूर्ण
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार show_pwm_temp_map(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	काष्ठा it87_data *data = it87_update_device(dev);
	पूर्णांक nr = sensor_attr->index;
	पूर्णांक map;

	map = data->pwm_temp_map[nr];
	अगर (map >= 3)
		map = 0;	/* Should never happen */
	अगर (nr >= 3)		/* pwm channels 3..6 map to temp4..6 */
		map += 3;

	वापस प्र_लिखो(buf, "%d\n", (पूर्णांक)BIT(map));
पूर्ण

अटल sमाप_प्रकार set_pwm_temp_map(काष्ठा device *dev,
				काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
				माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	काष्ठा it87_data *data = dev_get_drvdata(dev);
	पूर्णांक nr = sensor_attr->index;
	दीर्घ val;
	u8 reg;

	अगर (kम_से_दीर्घ(buf, 10, &val) < 0)
		वापस -EINVAL;

	अगर (nr >= 3)
		val -= 3;

	चयन (val) अणु
	हाल BIT(0):
		reg = 0x00;
		अवरोध;
	हाल BIT(1):
		reg = 0x01;
		अवरोध;
	हाल BIT(2):
		reg = 0x02;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&data->update_lock);
	it87_update_pwm_ctrl(data, nr);
	data->pwm_temp_map[nr] = reg;
	/*
	 * If we are in स्वतःmatic mode, ग_लिखो the temp mapping immediately;
	 * otherwise, just store it क्रम later use.
	 */
	अगर (data->pwm_ctrl[nr] & 0x80) अणु
		data->pwm_ctrl[nr] = (data->pwm_ctrl[nr] & 0xfc) |
						data->pwm_temp_map[nr];
		it87_ग_लिखो_value(data, IT87_REG_PWM[nr], data->pwm_ctrl[nr]);
	पूर्ण
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार show_स्वतः_pwm(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा it87_data *data = it87_update_device(dev);
	काष्ठा sensor_device_attribute_2 *sensor_attr =
			to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sensor_attr->nr;
	पूर्णांक poपूर्णांक = sensor_attr->index;

	वापस प्र_लिखो(buf, "%d\n",
		       pwm_from_reg(data, data->स्वतः_pwm[nr][poपूर्णांक]));
पूर्ण

अटल sमाप_प्रकार set_स्वतः_pwm(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा it87_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute_2 *sensor_attr =
			to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sensor_attr->nr;
	पूर्णांक poपूर्णांक = sensor_attr->index;
	पूर्णांक regaddr;
	दीर्घ val;

	अगर (kम_से_दीर्घ(buf, 10, &val) < 0 || val < 0 || val > 255)
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	data->स्वतः_pwm[nr][poपूर्णांक] = pwm_to_reg(data, val);
	अगर (has_newer_स्वतःpwm(data))
		regaddr = IT87_REG_AUTO_TEMP(nr, 3);
	अन्यथा
		regaddr = IT87_REG_AUTO_PWM(nr, poपूर्णांक);
	it87_ग_लिखो_value(data, regaddr, data->स्वतः_pwm[nr][poपूर्णांक]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार show_स्वतः_pwm_slope(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा it87_data *data = it87_update_device(dev);
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;

	वापस प्र_लिखो(buf, "%d\n", data->स्वतः_pwm[nr][1] & 0x7f);
पूर्ण

अटल sमाप_प्रकार set_स्वतः_pwm_slope(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा it87_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	अचिन्हित दीर्घ val;

	अगर (kम_से_अदीर्घ(buf, 10, &val) < 0 || val > 127)
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	data->स्वतः_pwm[nr][1] = (data->स्वतः_pwm[nr][1] & 0x80) | val;
	it87_ग_लिखो_value(data, IT87_REG_AUTO_TEMP(nr, 4),
			 data->स्वतः_pwm[nr][1]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार show_स्वतः_temp(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा it87_data *data = it87_update_device(dev);
	काष्ठा sensor_device_attribute_2 *sensor_attr =
			to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sensor_attr->nr;
	पूर्णांक poपूर्णांक = sensor_attr->index;
	पूर्णांक reg;

	अगर (has_old_स्वतःpwm(data) || poपूर्णांक)
		reg = data->स्वतः_temp[nr][poपूर्णांक];
	अन्यथा
		reg = data->स्वतः_temp[nr][1] - (data->स्वतः_temp[nr][0] & 0x1f);

	वापस प्र_लिखो(buf, "%d\n", TEMP_FROM_REG(reg));
पूर्ण

अटल sमाप_प्रकार set_स्वतः_temp(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा it87_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute_2 *sensor_attr =
			to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sensor_attr->nr;
	पूर्णांक poपूर्णांक = sensor_attr->index;
	दीर्घ val;
	पूर्णांक reg;

	अगर (kम_से_दीर्घ(buf, 10, &val) < 0 || val < -128000 || val > 127000)
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	अगर (has_newer_स्वतःpwm(data) && !poपूर्णांक) अणु
		reg = data->स्वतः_temp[nr][1] - TEMP_TO_REG(val);
		reg = clamp_val(reg, 0, 0x1f) | (data->स्वतः_temp[nr][0] & 0xe0);
		data->स्वतः_temp[nr][0] = reg;
		it87_ग_लिखो_value(data, IT87_REG_AUTO_TEMP(nr, 5), reg);
	पूर्ण अन्यथा अणु
		reg = TEMP_TO_REG(val);
		data->स्वतः_temp[nr][poपूर्णांक] = reg;
		अगर (has_newer_स्वतःpwm(data))
			poपूर्णांक--;
		it87_ग_लिखो_value(data, IT87_REG_AUTO_TEMP(nr, poपूर्णांक), reg);
	पूर्ण
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_2(fan1_input, S_IRUGO, show_fan, शून्य, 0, 0);
अटल SENSOR_DEVICE_ATTR_2(fan1_min, S_IRUGO | S_IWUSR, show_fan, set_fan,
			    0, 1);
अटल SENSOR_DEVICE_ATTR(fan1_भाग, S_IRUGO | S_IWUSR, show_fan_भाग,
			  set_fan_भाग, 0);

अटल SENSOR_DEVICE_ATTR_2(fan2_input, S_IRUGO, show_fan, शून्य, 1, 0);
अटल SENSOR_DEVICE_ATTR_2(fan2_min, S_IRUGO | S_IWUSR, show_fan, set_fan,
			    1, 1);
अटल SENSOR_DEVICE_ATTR(fan2_भाग, S_IRUGO | S_IWUSR, show_fan_भाग,
			  set_fan_भाग, 1);

अटल SENSOR_DEVICE_ATTR_2(fan3_input, S_IRUGO, show_fan, शून्य, 2, 0);
अटल SENSOR_DEVICE_ATTR_2(fan3_min, S_IRUGO | S_IWUSR, show_fan, set_fan,
			    2, 1);
अटल SENSOR_DEVICE_ATTR(fan3_भाग, S_IRUGO | S_IWUSR, show_fan_भाग,
			  set_fan_भाग, 2);

अटल SENSOR_DEVICE_ATTR_2(fan4_input, S_IRUGO, show_fan, शून्य, 3, 0);
अटल SENSOR_DEVICE_ATTR_2(fan4_min, S_IRUGO | S_IWUSR, show_fan, set_fan,
			    3, 1);

अटल SENSOR_DEVICE_ATTR_2(fan5_input, S_IRUGO, show_fan, शून्य, 4, 0);
अटल SENSOR_DEVICE_ATTR_2(fan5_min, S_IRUGO | S_IWUSR, show_fan, set_fan,
			    4, 1);

अटल SENSOR_DEVICE_ATTR_2(fan6_input, S_IRUGO, show_fan, शून्य, 5, 0);
अटल SENSOR_DEVICE_ATTR_2(fan6_min, S_IRUGO | S_IWUSR, show_fan, set_fan,
			    5, 1);

अटल SENSOR_DEVICE_ATTR(pwm1_enable, S_IRUGO | S_IWUSR,
			  show_pwm_enable, set_pwm_enable, 0);
अटल SENSOR_DEVICE_ATTR(pwm1, S_IRUGO | S_IWUSR, show_pwm, set_pwm, 0);
अटल SENSOR_DEVICE_ATTR(pwm1_freq, S_IRUGO | S_IWUSR, show_pwm_freq,
			  set_pwm_freq, 0);
अटल SENSOR_DEVICE_ATTR(pwm1_स्वतः_channels_temp, S_IRUGO,
			  show_pwm_temp_map, set_pwm_temp_map, 0);
अटल SENSOR_DEVICE_ATTR_2(pwm1_स्वतः_poपूर्णांक1_pwm, S_IRUGO | S_IWUSR,
			    show_स्वतः_pwm, set_स्वतः_pwm, 0, 0);
अटल SENSOR_DEVICE_ATTR_2(pwm1_स्वतः_poपूर्णांक2_pwm, S_IRUGO | S_IWUSR,
			    show_स्वतः_pwm, set_स्वतः_pwm, 0, 1);
अटल SENSOR_DEVICE_ATTR_2(pwm1_स्वतः_poपूर्णांक3_pwm, S_IRUGO | S_IWUSR,
			    show_स्वतः_pwm, set_स्वतः_pwm, 0, 2);
अटल SENSOR_DEVICE_ATTR_2(pwm1_स्वतः_poपूर्णांक4_pwm, S_IRUGO,
			    show_स्वतः_pwm, शून्य, 0, 3);
अटल SENSOR_DEVICE_ATTR_2(pwm1_स्वतः_poपूर्णांक1_temp, S_IRUGO | S_IWUSR,
			    show_स्वतः_temp, set_स्वतः_temp, 0, 1);
अटल SENSOR_DEVICE_ATTR_2(pwm1_स्वतः_poपूर्णांक1_temp_hyst, S_IRUGO | S_IWUSR,
			    show_स्वतः_temp, set_स्वतः_temp, 0, 0);
अटल SENSOR_DEVICE_ATTR_2(pwm1_स्वतः_poपूर्णांक2_temp, S_IRUGO | S_IWUSR,
			    show_स्वतः_temp, set_स्वतः_temp, 0, 2);
अटल SENSOR_DEVICE_ATTR_2(pwm1_स्वतः_poपूर्णांक3_temp, S_IRUGO | S_IWUSR,
			    show_स्वतः_temp, set_स्वतः_temp, 0, 3);
अटल SENSOR_DEVICE_ATTR_2(pwm1_स्वतः_poपूर्णांक4_temp, S_IRUGO | S_IWUSR,
			    show_स्वतः_temp, set_स्वतः_temp, 0, 4);
अटल SENSOR_DEVICE_ATTR_2(pwm1_स्वतः_start, S_IRUGO | S_IWUSR,
			    show_स्वतः_pwm, set_स्वतः_pwm, 0, 0);
अटल SENSOR_DEVICE_ATTR(pwm1_स्वतः_slope, S_IRUGO | S_IWUSR,
			  show_स्वतः_pwm_slope, set_स्वतः_pwm_slope, 0);

अटल SENSOR_DEVICE_ATTR(pwm2_enable, S_IRUGO | S_IWUSR,
			  show_pwm_enable, set_pwm_enable, 1);
अटल SENSOR_DEVICE_ATTR(pwm2, S_IRUGO | S_IWUSR, show_pwm, set_pwm, 1);
अटल SENSOR_DEVICE_ATTR(pwm2_freq, S_IRUGO, show_pwm_freq, set_pwm_freq, 1);
अटल SENSOR_DEVICE_ATTR(pwm2_स्वतः_channels_temp, S_IRUGO,
			  show_pwm_temp_map, set_pwm_temp_map, 1);
अटल SENSOR_DEVICE_ATTR_2(pwm2_स्वतः_poपूर्णांक1_pwm, S_IRUGO | S_IWUSR,
			    show_स्वतः_pwm, set_स्वतः_pwm, 1, 0);
अटल SENSOR_DEVICE_ATTR_2(pwm2_स्वतः_poपूर्णांक2_pwm, S_IRUGO | S_IWUSR,
			    show_स्वतः_pwm, set_स्वतः_pwm, 1, 1);
अटल SENSOR_DEVICE_ATTR_2(pwm2_स्वतः_poपूर्णांक3_pwm, S_IRUGO | S_IWUSR,
			    show_स्वतः_pwm, set_स्वतः_pwm, 1, 2);
अटल SENSOR_DEVICE_ATTR_2(pwm2_स्वतः_poपूर्णांक4_pwm, S_IRUGO,
			    show_स्वतः_pwm, शून्य, 1, 3);
अटल SENSOR_DEVICE_ATTR_2(pwm2_स्वतः_poपूर्णांक1_temp, S_IRUGO | S_IWUSR,
			    show_स्वतः_temp, set_स्वतः_temp, 1, 1);
अटल SENSOR_DEVICE_ATTR_2(pwm2_स्वतः_poपूर्णांक1_temp_hyst, S_IRUGO | S_IWUSR,
			    show_स्वतः_temp, set_स्वतः_temp, 1, 0);
अटल SENSOR_DEVICE_ATTR_2(pwm2_स्वतः_poपूर्णांक2_temp, S_IRUGO | S_IWUSR,
			    show_स्वतः_temp, set_स्वतः_temp, 1, 2);
अटल SENSOR_DEVICE_ATTR_2(pwm2_स्वतः_poपूर्णांक3_temp, S_IRUGO | S_IWUSR,
			    show_स्वतः_temp, set_स्वतः_temp, 1, 3);
अटल SENSOR_DEVICE_ATTR_2(pwm2_स्वतः_poपूर्णांक4_temp, S_IRUGO | S_IWUSR,
			    show_स्वतः_temp, set_स्वतः_temp, 1, 4);
अटल SENSOR_DEVICE_ATTR_2(pwm2_स्वतः_start, S_IRUGO | S_IWUSR,
			    show_स्वतः_pwm, set_स्वतः_pwm, 1, 0);
अटल SENSOR_DEVICE_ATTR(pwm2_स्वतः_slope, S_IRUGO | S_IWUSR,
			  show_स्वतः_pwm_slope, set_स्वतः_pwm_slope, 1);

अटल SENSOR_DEVICE_ATTR(pwm3_enable, S_IRUGO | S_IWUSR,
			  show_pwm_enable, set_pwm_enable, 2);
अटल SENSOR_DEVICE_ATTR(pwm3, S_IRUGO | S_IWUSR, show_pwm, set_pwm, 2);
अटल SENSOR_DEVICE_ATTR(pwm3_freq, S_IRUGO, show_pwm_freq, शून्य, 2);
अटल SENSOR_DEVICE_ATTR(pwm3_स्वतः_channels_temp, S_IRUGO,
			  show_pwm_temp_map, set_pwm_temp_map, 2);
अटल SENSOR_DEVICE_ATTR_2(pwm3_स्वतः_poपूर्णांक1_pwm, S_IRUGO | S_IWUSR,
			    show_स्वतः_pwm, set_स्वतः_pwm, 2, 0);
अटल SENSOR_DEVICE_ATTR_2(pwm3_स्वतः_poपूर्णांक2_pwm, S_IRUGO | S_IWUSR,
			    show_स्वतः_pwm, set_स्वतः_pwm, 2, 1);
अटल SENSOR_DEVICE_ATTR_2(pwm3_स्वतः_poपूर्णांक3_pwm, S_IRUGO | S_IWUSR,
			    show_स्वतः_pwm, set_स्वतः_pwm, 2, 2);
अटल SENSOR_DEVICE_ATTR_2(pwm3_स्वतः_poपूर्णांक4_pwm, S_IRUGO,
			    show_स्वतः_pwm, शून्य, 2, 3);
अटल SENSOR_DEVICE_ATTR_2(pwm3_स्वतः_poपूर्णांक1_temp, S_IRUGO | S_IWUSR,
			    show_स्वतः_temp, set_स्वतः_temp, 2, 1);
अटल SENSOR_DEVICE_ATTR_2(pwm3_स्वतः_poपूर्णांक1_temp_hyst, S_IRUGO | S_IWUSR,
			    show_स्वतः_temp, set_स्वतः_temp, 2, 0);
अटल SENSOR_DEVICE_ATTR_2(pwm3_स्वतः_poपूर्णांक2_temp, S_IRUGO | S_IWUSR,
			    show_स्वतः_temp, set_स्वतः_temp, 2, 2);
अटल SENSOR_DEVICE_ATTR_2(pwm3_स्वतः_poपूर्णांक3_temp, S_IRUGO | S_IWUSR,
			    show_स्वतः_temp, set_स्वतः_temp, 2, 3);
अटल SENSOR_DEVICE_ATTR_2(pwm3_स्वतः_poपूर्णांक4_temp, S_IRUGO | S_IWUSR,
			    show_स्वतः_temp, set_स्वतः_temp, 2, 4);
अटल SENSOR_DEVICE_ATTR_2(pwm3_स्वतः_start, S_IRUGO | S_IWUSR,
			    show_स्वतः_pwm, set_स्वतः_pwm, 2, 0);
अटल SENSOR_DEVICE_ATTR(pwm3_स्वतः_slope, S_IRUGO | S_IWUSR,
			  show_स्वतः_pwm_slope, set_स्वतः_pwm_slope, 2);

अटल SENSOR_DEVICE_ATTR(pwm4_enable, S_IRUGO | S_IWUSR,
			  show_pwm_enable, set_pwm_enable, 3);
अटल SENSOR_DEVICE_ATTR(pwm4, S_IRUGO | S_IWUSR, show_pwm, set_pwm, 3);
अटल SENSOR_DEVICE_ATTR(pwm4_freq, S_IRUGO, show_pwm_freq, शून्य, 3);
अटल SENSOR_DEVICE_ATTR(pwm4_स्वतः_channels_temp, S_IRUGO,
			  show_pwm_temp_map, set_pwm_temp_map, 3);
अटल SENSOR_DEVICE_ATTR_2(pwm4_स्वतः_poपूर्णांक1_temp, S_IRUGO | S_IWUSR,
			    show_स्वतः_temp, set_स्वतः_temp, 2, 1);
अटल SENSOR_DEVICE_ATTR_2(pwm4_स्वतः_poपूर्णांक1_temp_hyst, S_IRUGO | S_IWUSR,
			    show_स्वतः_temp, set_स्वतः_temp, 2, 0);
अटल SENSOR_DEVICE_ATTR_2(pwm4_स्वतः_poपूर्णांक2_temp, S_IRUGO | S_IWUSR,
			    show_स्वतः_temp, set_स्वतः_temp, 2, 2);
अटल SENSOR_DEVICE_ATTR_2(pwm4_स्वतः_poपूर्णांक3_temp, S_IRUGO | S_IWUSR,
			    show_स्वतः_temp, set_स्वतः_temp, 2, 3);
अटल SENSOR_DEVICE_ATTR_2(pwm4_स्वतः_start, S_IRUGO | S_IWUSR,
			    show_स्वतः_pwm, set_स्वतः_pwm, 3, 0);
अटल SENSOR_DEVICE_ATTR(pwm4_स्वतः_slope, S_IRUGO | S_IWUSR,
			  show_स्वतः_pwm_slope, set_स्वतः_pwm_slope, 3);

अटल SENSOR_DEVICE_ATTR(pwm5_enable, S_IRUGO | S_IWUSR,
			  show_pwm_enable, set_pwm_enable, 4);
अटल SENSOR_DEVICE_ATTR(pwm5, S_IRUGO | S_IWUSR, show_pwm, set_pwm, 4);
अटल SENSOR_DEVICE_ATTR(pwm5_freq, S_IRUGO, show_pwm_freq, शून्य, 4);
अटल SENSOR_DEVICE_ATTR(pwm5_स्वतः_channels_temp, S_IRUGO,
			  show_pwm_temp_map, set_pwm_temp_map, 4);
अटल SENSOR_DEVICE_ATTR_2(pwm5_स्वतः_poपूर्णांक1_temp, S_IRUGO | S_IWUSR,
			    show_स्वतः_temp, set_स्वतः_temp, 2, 1);
अटल SENSOR_DEVICE_ATTR_2(pwm5_स्वतः_poपूर्णांक1_temp_hyst, S_IRUGO | S_IWUSR,
			    show_स्वतः_temp, set_स्वतः_temp, 2, 0);
अटल SENSOR_DEVICE_ATTR_2(pwm5_स्वतः_poपूर्णांक2_temp, S_IRUGO | S_IWUSR,
			    show_स्वतः_temp, set_स्वतः_temp, 2, 2);
अटल SENSOR_DEVICE_ATTR_2(pwm5_स्वतः_poपूर्णांक3_temp, S_IRUGO | S_IWUSR,
			    show_स्वतः_temp, set_स्वतः_temp, 2, 3);
अटल SENSOR_DEVICE_ATTR_2(pwm5_स्वतः_start, S_IRUGO | S_IWUSR,
			    show_स्वतः_pwm, set_स्वतः_pwm, 4, 0);
अटल SENSOR_DEVICE_ATTR(pwm5_स्वतः_slope, S_IRUGO | S_IWUSR,
			  show_स्वतः_pwm_slope, set_स्वतः_pwm_slope, 4);

अटल SENSOR_DEVICE_ATTR(pwm6_enable, S_IRUGO | S_IWUSR,
			  show_pwm_enable, set_pwm_enable, 5);
अटल SENSOR_DEVICE_ATTR(pwm6, S_IRUGO | S_IWUSR, show_pwm, set_pwm, 5);
अटल SENSOR_DEVICE_ATTR(pwm6_freq, S_IRUGO, show_pwm_freq, शून्य, 5);
अटल SENSOR_DEVICE_ATTR(pwm6_स्वतः_channels_temp, S_IRUGO,
			  show_pwm_temp_map, set_pwm_temp_map, 5);
अटल SENSOR_DEVICE_ATTR_2(pwm6_स्वतः_poपूर्णांक1_temp, S_IRUGO | S_IWUSR,
			    show_स्वतः_temp, set_स्वतः_temp, 2, 1);
अटल SENSOR_DEVICE_ATTR_2(pwm6_स्वतः_poपूर्णांक1_temp_hyst, S_IRUGO | S_IWUSR,
			    show_स्वतः_temp, set_स्वतः_temp, 2, 0);
अटल SENSOR_DEVICE_ATTR_2(pwm6_स्वतः_poपूर्णांक2_temp, S_IRUGO | S_IWUSR,
			    show_स्वतः_temp, set_स्वतः_temp, 2, 2);
अटल SENSOR_DEVICE_ATTR_2(pwm6_स्वतः_poपूर्णांक3_temp, S_IRUGO | S_IWUSR,
			    show_स्वतः_temp, set_स्वतः_temp, 2, 3);
अटल SENSOR_DEVICE_ATTR_2(pwm6_स्वतः_start, S_IRUGO | S_IWUSR,
			    show_स्वतः_pwm, set_स्वतः_pwm, 5, 0);
अटल SENSOR_DEVICE_ATTR(pwm6_स्वतः_slope, S_IRUGO | S_IWUSR,
			  show_स्वतः_pwm_slope, set_स्वतः_pwm_slope, 5);

/* Alarms */
अटल sमाप_प्रकार alarms_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा it87_data *data = it87_update_device(dev);

	वापस प्र_लिखो(buf, "%u\n", data->alarms);
पूर्ण
अटल DEVICE_ATTR_RO(alarms);

अटल sमाप_प्रकार show_alarm(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा it87_data *data = it87_update_device(dev);
	पूर्णांक bitnr = to_sensor_dev_attr(attr)->index;

	वापस प्र_लिखो(buf, "%u\n", (data->alarms >> bitnr) & 1);
पूर्ण

अटल sमाप_प्रकार clear_पूर्णांकrusion(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			       माप_प्रकार count)
अणु
	काष्ठा it87_data *data = dev_get_drvdata(dev);
	पूर्णांक config;
	दीर्घ val;

	अगर (kम_से_दीर्घ(buf, 10, &val) < 0 || val != 0)
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	config = it87_पढ़ो_value(data, IT87_REG_CONFIG);
	अगर (config < 0) अणु
		count = config;
	पूर्ण अन्यथा अणु
		config |= BIT(5);
		it87_ग_लिखो_value(data, IT87_REG_CONFIG, config);
		/* Invalidate cache to क्रमce re-पढ़ो */
		data->valid = 0;
	पूर्ण
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR(in0_alarm, S_IRUGO, show_alarm, शून्य, 8);
अटल SENSOR_DEVICE_ATTR(in1_alarm, S_IRUGO, show_alarm, शून्य, 9);
अटल SENSOR_DEVICE_ATTR(in2_alarm, S_IRUGO, show_alarm, शून्य, 10);
अटल SENSOR_DEVICE_ATTR(in3_alarm, S_IRUGO, show_alarm, शून्य, 11);
अटल SENSOR_DEVICE_ATTR(in4_alarm, S_IRUGO, show_alarm, शून्य, 12);
अटल SENSOR_DEVICE_ATTR(in5_alarm, S_IRUGO, show_alarm, शून्य, 13);
अटल SENSOR_DEVICE_ATTR(in6_alarm, S_IRUGO, show_alarm, शून्य, 14);
अटल SENSOR_DEVICE_ATTR(in7_alarm, S_IRUGO, show_alarm, शून्य, 15);
अटल SENSOR_DEVICE_ATTR(fan1_alarm, S_IRUGO, show_alarm, शून्य, 0);
अटल SENSOR_DEVICE_ATTR(fan2_alarm, S_IRUGO, show_alarm, शून्य, 1);
अटल SENSOR_DEVICE_ATTR(fan3_alarm, S_IRUGO, show_alarm, शून्य, 2);
अटल SENSOR_DEVICE_ATTR(fan4_alarm, S_IRUGO, show_alarm, शून्य, 3);
अटल SENSOR_DEVICE_ATTR(fan5_alarm, S_IRUGO, show_alarm, शून्य, 6);
अटल SENSOR_DEVICE_ATTR(fan6_alarm, S_IRUGO, show_alarm, शून्य, 7);
अटल SENSOR_DEVICE_ATTR(temp1_alarm, S_IRUGO, show_alarm, शून्य, 16);
अटल SENSOR_DEVICE_ATTR(temp2_alarm, S_IRUGO, show_alarm, शून्य, 17);
अटल SENSOR_DEVICE_ATTR(temp3_alarm, S_IRUGO, show_alarm, शून्य, 18);
अटल SENSOR_DEVICE_ATTR(पूर्णांकrusion0_alarm, S_IRUGO | S_IWUSR,
			  show_alarm, clear_पूर्णांकrusion, 4);

अटल sमाप_प्रकार show_beep(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा it87_data *data = it87_update_device(dev);
	पूर्णांक bitnr = to_sensor_dev_attr(attr)->index;

	वापस प्र_लिखो(buf, "%u\n", (data->beeps >> bitnr) & 1);
पूर्ण

अटल sमाप_प्रकार set_beep(काष्ठा device *dev, काष्ठा device_attribute *attr,
			स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक bitnr = to_sensor_dev_attr(attr)->index;
	काष्ठा it87_data *data = dev_get_drvdata(dev);
	दीर्घ val;

	अगर (kम_से_दीर्घ(buf, 10, &val) < 0 || (val != 0 && val != 1))
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	data->beeps = it87_पढ़ो_value(data, IT87_REG_BEEP_ENABLE);
	अगर (val)
		data->beeps |= BIT(bitnr);
	अन्यथा
		data->beeps &= ~BIT(bitnr);
	it87_ग_लिखो_value(data, IT87_REG_BEEP_ENABLE, data->beeps);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR(in0_beep, S_IRUGO | S_IWUSR,
			  show_beep, set_beep, 1);
अटल SENSOR_DEVICE_ATTR(in1_beep, S_IRUGO, show_beep, शून्य, 1);
अटल SENSOR_DEVICE_ATTR(in2_beep, S_IRUGO, show_beep, शून्य, 1);
अटल SENSOR_DEVICE_ATTR(in3_beep, S_IRUGO, show_beep, शून्य, 1);
अटल SENSOR_DEVICE_ATTR(in4_beep, S_IRUGO, show_beep, शून्य, 1);
अटल SENSOR_DEVICE_ATTR(in5_beep, S_IRUGO, show_beep, शून्य, 1);
अटल SENSOR_DEVICE_ATTR(in6_beep, S_IRUGO, show_beep, शून्य, 1);
अटल SENSOR_DEVICE_ATTR(in7_beep, S_IRUGO, show_beep, शून्य, 1);
/* fanX_beep writability is set later */
अटल SENSOR_DEVICE_ATTR(fan1_beep, S_IRUGO, show_beep, set_beep, 0);
अटल SENSOR_DEVICE_ATTR(fan2_beep, S_IRUGO, show_beep, set_beep, 0);
अटल SENSOR_DEVICE_ATTR(fan3_beep, S_IRUGO, show_beep, set_beep, 0);
अटल SENSOR_DEVICE_ATTR(fan4_beep, S_IRUGO, show_beep, set_beep, 0);
अटल SENSOR_DEVICE_ATTR(fan5_beep, S_IRUGO, show_beep, set_beep, 0);
अटल SENSOR_DEVICE_ATTR(fan6_beep, S_IRUGO, show_beep, set_beep, 0);
अटल SENSOR_DEVICE_ATTR(temp1_beep, S_IRUGO | S_IWUSR,
			  show_beep, set_beep, 2);
अटल SENSOR_DEVICE_ATTR(temp2_beep, S_IRUGO, show_beep, शून्य, 2);
अटल SENSOR_DEVICE_ATTR(temp3_beep, S_IRUGO, show_beep, शून्य, 2);

अटल sमाप_प्रकार vrm_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा it87_data *data = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%u\n", data->vrm);
पूर्ण

अटल sमाप_प्रकार vrm_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा it87_data *data = dev_get_drvdata(dev);
	अचिन्हित दीर्घ val;

	अगर (kम_से_अदीर्घ(buf, 10, &val) < 0)
		वापस -EINVAL;

	data->vrm = val;

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(vrm);

अटल sमाप_प्रकार cpu0_vid_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा it87_data *data = it87_update_device(dev);

	वापस प्र_लिखो(buf, "%ld\n", (दीर्घ)vid_from_reg(data->vid, data->vrm));
पूर्ण
अटल DEVICE_ATTR_RO(cpu0_vid);

अटल sमाप_प्रकार show_label(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	अटल स्थिर अक्षर * स्थिर labels[] = अणु
		"+5V",
		"5VSB",
		"Vbat",
		"AVCC",
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर labels_it8721[] = अणु
		"+3.3V",
		"3VSB",
		"Vbat",
		"+3.3V",
	पूर्ण;
	काष्ठा it87_data *data = dev_get_drvdata(dev);
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	स्थिर अक्षर *label;

	अगर (has_vin3_5v(data) && nr == 0)
		label = labels[0];
	अन्यथा अगर (has_12mv_adc(data) || has_10_9mv_adc(data))
		label = labels_it8721[nr];
	अन्यथा
		label = labels[nr];

	वापस प्र_लिखो(buf, "%s\n", label);
पूर्ण
अटल SENSOR_DEVICE_ATTR(in3_label, S_IRUGO, show_label, शून्य, 0);
अटल SENSOR_DEVICE_ATTR(in7_label, S_IRUGO, show_label, शून्य, 1);
अटल SENSOR_DEVICE_ATTR(in8_label, S_IRUGO, show_label, शून्य, 2);
/* AVCC3 */
अटल SENSOR_DEVICE_ATTR(in9_label, S_IRUGO, show_label, शून्य, 3);

अटल umode_t it87_in_is_visible(काष्ठा kobject *kobj,
				  काष्ठा attribute *attr, पूर्णांक index)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा it87_data *data = dev_get_drvdata(dev);
	पूर्णांक i = index / 5;	/* voltage index */
	पूर्णांक a = index % 5;	/* attribute index */

	अगर (index >= 40) अणु	/* in8 and higher only have input attributes */
		i = index - 40 + 8;
		a = 0;
	पूर्ण

	अगर (!(data->has_in & BIT(i)))
		वापस 0;

	अगर (a == 4 && !data->has_beep)
		वापस 0;

	वापस attr->mode;
पूर्ण

अटल काष्ठा attribute *it87_attributes_in[] = अणु
	&sensor_dev_attr_in0_input.dev_attr.attr,
	&sensor_dev_attr_in0_min.dev_attr.attr,
	&sensor_dev_attr_in0_max.dev_attr.attr,
	&sensor_dev_attr_in0_alarm.dev_attr.attr,
	&sensor_dev_attr_in0_beep.dev_attr.attr,	/* 4 */

	&sensor_dev_attr_in1_input.dev_attr.attr,
	&sensor_dev_attr_in1_min.dev_attr.attr,
	&sensor_dev_attr_in1_max.dev_attr.attr,
	&sensor_dev_attr_in1_alarm.dev_attr.attr,
	&sensor_dev_attr_in1_beep.dev_attr.attr,	/* 9 */

	&sensor_dev_attr_in2_input.dev_attr.attr,
	&sensor_dev_attr_in2_min.dev_attr.attr,
	&sensor_dev_attr_in2_max.dev_attr.attr,
	&sensor_dev_attr_in2_alarm.dev_attr.attr,
	&sensor_dev_attr_in2_beep.dev_attr.attr,	/* 14 */

	&sensor_dev_attr_in3_input.dev_attr.attr,
	&sensor_dev_attr_in3_min.dev_attr.attr,
	&sensor_dev_attr_in3_max.dev_attr.attr,
	&sensor_dev_attr_in3_alarm.dev_attr.attr,
	&sensor_dev_attr_in3_beep.dev_attr.attr,	/* 19 */

	&sensor_dev_attr_in4_input.dev_attr.attr,
	&sensor_dev_attr_in4_min.dev_attr.attr,
	&sensor_dev_attr_in4_max.dev_attr.attr,
	&sensor_dev_attr_in4_alarm.dev_attr.attr,
	&sensor_dev_attr_in4_beep.dev_attr.attr,	/* 24 */

	&sensor_dev_attr_in5_input.dev_attr.attr,
	&sensor_dev_attr_in5_min.dev_attr.attr,
	&sensor_dev_attr_in5_max.dev_attr.attr,
	&sensor_dev_attr_in5_alarm.dev_attr.attr,
	&sensor_dev_attr_in5_beep.dev_attr.attr,	/* 29 */

	&sensor_dev_attr_in6_input.dev_attr.attr,
	&sensor_dev_attr_in6_min.dev_attr.attr,
	&sensor_dev_attr_in6_max.dev_attr.attr,
	&sensor_dev_attr_in6_alarm.dev_attr.attr,
	&sensor_dev_attr_in6_beep.dev_attr.attr,	/* 34 */

	&sensor_dev_attr_in7_input.dev_attr.attr,
	&sensor_dev_attr_in7_min.dev_attr.attr,
	&sensor_dev_attr_in7_max.dev_attr.attr,
	&sensor_dev_attr_in7_alarm.dev_attr.attr,
	&sensor_dev_attr_in7_beep.dev_attr.attr,	/* 39 */

	&sensor_dev_attr_in8_input.dev_attr.attr,	/* 40 */
	&sensor_dev_attr_in9_input.dev_attr.attr,
	&sensor_dev_attr_in10_input.dev_attr.attr,
	&sensor_dev_attr_in11_input.dev_attr.attr,
	&sensor_dev_attr_in12_input.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group it87_group_in = अणु
	.attrs = it87_attributes_in,
	.is_visible = it87_in_is_visible,
पूर्ण;

अटल umode_t it87_temp_is_visible(काष्ठा kobject *kobj,
				    काष्ठा attribute *attr, पूर्णांक index)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा it87_data *data = dev_get_drvdata(dev);
	पूर्णांक i = index / 7;	/* temperature index */
	पूर्णांक a = index % 7;	/* attribute index */

	अगर (index >= 21) अणु
		i = index - 21 + 3;
		a = 0;
	पूर्ण

	अगर (!(data->has_temp & BIT(i)))
		वापस 0;

	अगर (a == 5 && !has_temp_offset(data))
		वापस 0;

	अगर (a == 6 && !data->has_beep)
		वापस 0;

	वापस attr->mode;
पूर्ण

अटल काष्ठा attribute *it87_attributes_temp[] = अणु
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_temp1_max.dev_attr.attr,
	&sensor_dev_attr_temp1_min.dev_attr.attr,
	&sensor_dev_attr_temp1_type.dev_attr.attr,
	&sensor_dev_attr_temp1_alarm.dev_attr.attr,
	&sensor_dev_attr_temp1_offset.dev_attr.attr,	/* 5 */
	&sensor_dev_attr_temp1_beep.dev_attr.attr,	/* 6 */

	&sensor_dev_attr_temp2_input.dev_attr.attr,	/* 7 */
	&sensor_dev_attr_temp2_max.dev_attr.attr,
	&sensor_dev_attr_temp2_min.dev_attr.attr,
	&sensor_dev_attr_temp2_type.dev_attr.attr,
	&sensor_dev_attr_temp2_alarm.dev_attr.attr,
	&sensor_dev_attr_temp2_offset.dev_attr.attr,
	&sensor_dev_attr_temp2_beep.dev_attr.attr,

	&sensor_dev_attr_temp3_input.dev_attr.attr,	/* 14 */
	&sensor_dev_attr_temp3_max.dev_attr.attr,
	&sensor_dev_attr_temp3_min.dev_attr.attr,
	&sensor_dev_attr_temp3_type.dev_attr.attr,
	&sensor_dev_attr_temp3_alarm.dev_attr.attr,
	&sensor_dev_attr_temp3_offset.dev_attr.attr,
	&sensor_dev_attr_temp3_beep.dev_attr.attr,

	&sensor_dev_attr_temp4_input.dev_attr.attr,	/* 21 */
	&sensor_dev_attr_temp5_input.dev_attr.attr,
	&sensor_dev_attr_temp6_input.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group it87_group_temp = अणु
	.attrs = it87_attributes_temp,
	.is_visible = it87_temp_is_visible,
पूर्ण;

अटल umode_t it87_is_visible(काष्ठा kobject *kobj,
			       काष्ठा attribute *attr, पूर्णांक index)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा it87_data *data = dev_get_drvdata(dev);

	अगर ((index == 2 || index == 3) && !data->has_vid)
		वापस 0;

	अगर (index > 3 && !(data->in_पूर्णांकernal & BIT(index - 4)))
		वापस 0;

	वापस attr->mode;
पूर्ण

अटल काष्ठा attribute *it87_attributes[] = अणु
	&dev_attr_alarms.attr,
	&sensor_dev_attr_पूर्णांकrusion0_alarm.dev_attr.attr,
	&dev_attr_vrm.attr,				/* 2 */
	&dev_attr_cpu0_vid.attr,			/* 3 */
	&sensor_dev_attr_in3_label.dev_attr.attr,	/* 4 .. 7 */
	&sensor_dev_attr_in7_label.dev_attr.attr,
	&sensor_dev_attr_in8_label.dev_attr.attr,
	&sensor_dev_attr_in9_label.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group it87_group = अणु
	.attrs = it87_attributes,
	.is_visible = it87_is_visible,
पूर्ण;

अटल umode_t it87_fan_is_visible(काष्ठा kobject *kobj,
				   काष्ठा attribute *attr, पूर्णांक index)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा it87_data *data = dev_get_drvdata(dev);
	पूर्णांक i = index / 5;	/* fan index */
	पूर्णांक a = index % 5;	/* attribute index */

	अगर (index >= 15) अणु	/* fan 4..6 करोn't have भागisor attributes */
		i = (index - 15) / 4 + 3;
		a = (index - 15) % 4;
	पूर्ण

	अगर (!(data->has_fan & BIT(i)))
		वापस 0;

	अगर (a == 3) अणु				/* beep */
		अगर (!data->has_beep)
			वापस 0;
		/* first fan beep attribute is writable */
		अगर (i == __ffs(data->has_fan))
			वापस attr->mode | S_IWUSR;
	पूर्ण

	अगर (a == 4 && has_16bit_fans(data))	/* भागisor */
		वापस 0;

	वापस attr->mode;
पूर्ण

अटल काष्ठा attribute *it87_attributes_fan[] = अणु
	&sensor_dev_attr_fan1_input.dev_attr.attr,
	&sensor_dev_attr_fan1_min.dev_attr.attr,
	&sensor_dev_attr_fan1_alarm.dev_attr.attr,
	&sensor_dev_attr_fan1_beep.dev_attr.attr,	/* 3 */
	&sensor_dev_attr_fan1_भाग.dev_attr.attr,	/* 4 */

	&sensor_dev_attr_fan2_input.dev_attr.attr,
	&sensor_dev_attr_fan2_min.dev_attr.attr,
	&sensor_dev_attr_fan2_alarm.dev_attr.attr,
	&sensor_dev_attr_fan2_beep.dev_attr.attr,
	&sensor_dev_attr_fan2_भाग.dev_attr.attr,	/* 9 */

	&sensor_dev_attr_fan3_input.dev_attr.attr,
	&sensor_dev_attr_fan3_min.dev_attr.attr,
	&sensor_dev_attr_fan3_alarm.dev_attr.attr,
	&sensor_dev_attr_fan3_beep.dev_attr.attr,
	&sensor_dev_attr_fan3_भाग.dev_attr.attr,	/* 14 */

	&sensor_dev_attr_fan4_input.dev_attr.attr,	/* 15 */
	&sensor_dev_attr_fan4_min.dev_attr.attr,
	&sensor_dev_attr_fan4_alarm.dev_attr.attr,
	&sensor_dev_attr_fan4_beep.dev_attr.attr,

	&sensor_dev_attr_fan5_input.dev_attr.attr,	/* 19 */
	&sensor_dev_attr_fan5_min.dev_attr.attr,
	&sensor_dev_attr_fan5_alarm.dev_attr.attr,
	&sensor_dev_attr_fan5_beep.dev_attr.attr,

	&sensor_dev_attr_fan6_input.dev_attr.attr,	/* 23 */
	&sensor_dev_attr_fan6_min.dev_attr.attr,
	&sensor_dev_attr_fan6_alarm.dev_attr.attr,
	&sensor_dev_attr_fan6_beep.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group it87_group_fan = अणु
	.attrs = it87_attributes_fan,
	.is_visible = it87_fan_is_visible,
पूर्ण;

अटल umode_t it87_pwm_is_visible(काष्ठा kobject *kobj,
				   काष्ठा attribute *attr, पूर्णांक index)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा it87_data *data = dev_get_drvdata(dev);
	पूर्णांक i = index / 4;	/* pwm index */
	पूर्णांक a = index % 4;	/* attribute index */

	अगर (!(data->has_pwm & BIT(i)))
		वापस 0;

	/* pwmX_स्वतः_channels_temp is only writable अगर स्वतः pwm is supported */
	अगर (a == 3 && (has_old_स्वतःpwm(data) || has_newer_स्वतःpwm(data)))
		वापस attr->mode | S_IWUSR;

	/* pwm2_freq is writable अगर there are two pwm frequency selects */
	अगर (has_pwm_freq2(data) && i == 1 && a == 2)
		वापस attr->mode | S_IWUSR;

	वापस attr->mode;
पूर्ण

अटल काष्ठा attribute *it87_attributes_pwm[] = अणु
	&sensor_dev_attr_pwm1_enable.dev_attr.attr,
	&sensor_dev_attr_pwm1.dev_attr.attr,
	&sensor_dev_attr_pwm1_freq.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_channels_temp.dev_attr.attr,

	&sensor_dev_attr_pwm2_enable.dev_attr.attr,
	&sensor_dev_attr_pwm2.dev_attr.attr,
	&sensor_dev_attr_pwm2_freq.dev_attr.attr,
	&sensor_dev_attr_pwm2_स्वतः_channels_temp.dev_attr.attr,

	&sensor_dev_attr_pwm3_enable.dev_attr.attr,
	&sensor_dev_attr_pwm3.dev_attr.attr,
	&sensor_dev_attr_pwm3_freq.dev_attr.attr,
	&sensor_dev_attr_pwm3_स्वतः_channels_temp.dev_attr.attr,

	&sensor_dev_attr_pwm4_enable.dev_attr.attr,
	&sensor_dev_attr_pwm4.dev_attr.attr,
	&sensor_dev_attr_pwm4_freq.dev_attr.attr,
	&sensor_dev_attr_pwm4_स्वतः_channels_temp.dev_attr.attr,

	&sensor_dev_attr_pwm5_enable.dev_attr.attr,
	&sensor_dev_attr_pwm5.dev_attr.attr,
	&sensor_dev_attr_pwm5_freq.dev_attr.attr,
	&sensor_dev_attr_pwm5_स्वतः_channels_temp.dev_attr.attr,

	&sensor_dev_attr_pwm6_enable.dev_attr.attr,
	&sensor_dev_attr_pwm6.dev_attr.attr,
	&sensor_dev_attr_pwm6_freq.dev_attr.attr,
	&sensor_dev_attr_pwm6_स्वतः_channels_temp.dev_attr.attr,

	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group it87_group_pwm = अणु
	.attrs = it87_attributes_pwm,
	.is_visible = it87_pwm_is_visible,
पूर्ण;

अटल umode_t it87_स्वतः_pwm_is_visible(काष्ठा kobject *kobj,
					काष्ठा attribute *attr, पूर्णांक index)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा it87_data *data = dev_get_drvdata(dev);
	पूर्णांक i = index / 11;	/* pwm index */
	पूर्णांक a = index % 11;	/* attribute index */

	अगर (index >= 33) अणु	/* pwm 4..6 */
		i = (index - 33) / 6 + 3;
		a = (index - 33) % 6 + 4;
	पूर्ण

	अगर (!(data->has_pwm & BIT(i)))
		वापस 0;

	अगर (has_newer_स्वतःpwm(data)) अणु
		अगर (a < 4)	/* no स्वतः poपूर्णांक pwm */
			वापस 0;
		अगर (a == 8)	/* no स्वतः_poपूर्णांक4 */
			वापस 0;
	पूर्ण
	अगर (has_old_स्वतःpwm(data)) अणु
		अगर (a >= 9)	/* no pwm_स्वतः_start, pwm_स्वतः_slope */
			वापस 0;
	पूर्ण

	वापस attr->mode;
पूर्ण

अटल काष्ठा attribute *it87_attributes_स्वतः_pwm[] = अणु
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक1_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक2_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक3_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक4_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक1_temp.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक1_temp_hyst.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक2_temp.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक3_temp.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक4_temp.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_start.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_slope.dev_attr.attr,

	&sensor_dev_attr_pwm2_स्वतः_poपूर्णांक1_pwm.dev_attr.attr,	/* 11 */
	&sensor_dev_attr_pwm2_स्वतः_poपूर्णांक2_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm2_स्वतः_poपूर्णांक3_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm2_स्वतः_poपूर्णांक4_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm2_स्वतः_poपूर्णांक1_temp.dev_attr.attr,
	&sensor_dev_attr_pwm2_स्वतः_poपूर्णांक1_temp_hyst.dev_attr.attr,
	&sensor_dev_attr_pwm2_स्वतः_poपूर्णांक2_temp.dev_attr.attr,
	&sensor_dev_attr_pwm2_स्वतः_poपूर्णांक3_temp.dev_attr.attr,
	&sensor_dev_attr_pwm2_स्वतः_poपूर्णांक4_temp.dev_attr.attr,
	&sensor_dev_attr_pwm2_स्वतः_start.dev_attr.attr,
	&sensor_dev_attr_pwm2_स्वतः_slope.dev_attr.attr,

	&sensor_dev_attr_pwm3_स्वतः_poपूर्णांक1_pwm.dev_attr.attr,	/* 22 */
	&sensor_dev_attr_pwm3_स्वतः_poपूर्णांक2_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm3_स्वतः_poपूर्णांक3_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm3_स्वतः_poपूर्णांक4_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm3_स्वतः_poपूर्णांक1_temp.dev_attr.attr,
	&sensor_dev_attr_pwm3_स्वतः_poपूर्णांक1_temp_hyst.dev_attr.attr,
	&sensor_dev_attr_pwm3_स्वतः_poपूर्णांक2_temp.dev_attr.attr,
	&sensor_dev_attr_pwm3_स्वतः_poपूर्णांक3_temp.dev_attr.attr,
	&sensor_dev_attr_pwm3_स्वतः_poपूर्णांक4_temp.dev_attr.attr,
	&sensor_dev_attr_pwm3_स्वतः_start.dev_attr.attr,
	&sensor_dev_attr_pwm3_स्वतः_slope.dev_attr.attr,

	&sensor_dev_attr_pwm4_स्वतः_poपूर्णांक1_temp.dev_attr.attr,	/* 33 */
	&sensor_dev_attr_pwm4_स्वतः_poपूर्णांक1_temp_hyst.dev_attr.attr,
	&sensor_dev_attr_pwm4_स्वतः_poपूर्णांक2_temp.dev_attr.attr,
	&sensor_dev_attr_pwm4_स्वतः_poपूर्णांक3_temp.dev_attr.attr,
	&sensor_dev_attr_pwm4_स्वतः_start.dev_attr.attr,
	&sensor_dev_attr_pwm4_स्वतः_slope.dev_attr.attr,

	&sensor_dev_attr_pwm5_स्वतः_poपूर्णांक1_temp.dev_attr.attr,
	&sensor_dev_attr_pwm5_स्वतः_poपूर्णांक1_temp_hyst.dev_attr.attr,
	&sensor_dev_attr_pwm5_स्वतः_poपूर्णांक2_temp.dev_attr.attr,
	&sensor_dev_attr_pwm5_स्वतः_poपूर्णांक3_temp.dev_attr.attr,
	&sensor_dev_attr_pwm5_स्वतः_start.dev_attr.attr,
	&sensor_dev_attr_pwm5_स्वतः_slope.dev_attr.attr,

	&sensor_dev_attr_pwm6_स्वतः_poपूर्णांक1_temp.dev_attr.attr,
	&sensor_dev_attr_pwm6_स्वतः_poपूर्णांक1_temp_hyst.dev_attr.attr,
	&sensor_dev_attr_pwm6_स्वतः_poपूर्णांक2_temp.dev_attr.attr,
	&sensor_dev_attr_pwm6_स्वतः_poपूर्णांक3_temp.dev_attr.attr,
	&sensor_dev_attr_pwm6_स्वतः_start.dev_attr.attr,
	&sensor_dev_attr_pwm6_स्वतः_slope.dev_attr.attr,

	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group it87_group_स्वतः_pwm = अणु
	.attrs = it87_attributes_स्वतः_pwm,
	.is_visible = it87_स्वतः_pwm_is_visible,
पूर्ण;

/* SuperIO detection - will change isa_address अगर a chip is found */
अटल पूर्णांक __init it87_find(पूर्णांक sioaddr, अचिन्हित लघु *address,
			    काष्ठा it87_sio_data *sio_data)
अणु
	पूर्णांक err;
	u16 chip_type;
	स्थिर अक्षर *board_venकरोr, *board_name;
	स्थिर काष्ठा it87_devices *config;

	err = superio_enter(sioaddr);
	अगर (err)
		वापस err;

	err = -ENODEV;
	chip_type = क्रमce_id ? क्रमce_id : superio_inw(sioaddr, DEVID);

	चयन (chip_type) अणु
	हाल IT8705F_DEVID:
		sio_data->type = it87;
		अवरोध;
	हाल IT8712F_DEVID:
		sio_data->type = it8712;
		अवरोध;
	हाल IT8716F_DEVID:
	हाल IT8726F_DEVID:
		sio_data->type = it8716;
		अवरोध;
	हाल IT8718F_DEVID:
		sio_data->type = it8718;
		अवरोध;
	हाल IT8720F_DEVID:
		sio_data->type = it8720;
		अवरोध;
	हाल IT8721F_DEVID:
		sio_data->type = it8721;
		अवरोध;
	हाल IT8728F_DEVID:
		sio_data->type = it8728;
		अवरोध;
	हाल IT8732F_DEVID:
		sio_data->type = it8732;
		अवरोध;
	हाल IT8792E_DEVID:
		sio_data->type = it8792;
		अवरोध;
	हाल IT8771E_DEVID:
		sio_data->type = it8771;
		अवरोध;
	हाल IT8772E_DEVID:
		sio_data->type = it8772;
		अवरोध;
	हाल IT8781F_DEVID:
		sio_data->type = it8781;
		अवरोध;
	हाल IT8782F_DEVID:
		sio_data->type = it8782;
		अवरोध;
	हाल IT8783E_DEVID:
		sio_data->type = it8783;
		अवरोध;
	हाल IT8786E_DEVID:
		sio_data->type = it8786;
		अवरोध;
	हाल IT8790E_DEVID:
		sio_data->type = it8790;
		अवरोध;
	हाल IT8603E_DEVID:
	हाल IT8623E_DEVID:
		sio_data->type = it8603;
		अवरोध;
	हाल IT8620E_DEVID:
		sio_data->type = it8620;
		अवरोध;
	हाल IT8622E_DEVID:
		sio_data->type = it8622;
		अवरोध;
	हाल IT8628E_DEVID:
		sio_data->type = it8628;
		अवरोध;
	हाल 0xffff:	/* No device at all */
		जाओ निकास;
	शेष:
		pr_debug("Unsupported chip (DEVID=0x%x)\n", chip_type);
		जाओ निकास;
	पूर्ण

	superio_select(sioaddr, PME);
	अगर (!(superio_inb(sioaddr, IT87_ACT_REG) & 0x01)) अणु
		pr_info("Device not activated, skipping\n");
		जाओ निकास;
	पूर्ण

	*address = superio_inw(sioaddr, IT87_BASE_REG) & ~(IT87_EXTENT - 1);
	अगर (*address == 0) अणु
		pr_info("Base address not set, skipping\n");
		जाओ निकास;
	पूर्ण

	err = 0;
	sio_data->sioaddr = sioaddr;
	sio_data->revision = superio_inb(sioaddr, DEVREV) & 0x0f;
	pr_info("Found IT%04x%s chip at 0x%x, revision %d\n", chip_type,
		it87_devices[sio_data->type].suffix,
		*address, sio_data->revision);

	config = &it87_devices[sio_data->type];

	/* in7 (VSB or VCCH5V) is always पूर्णांकernal on some chips */
	अगर (has_in7_पूर्णांकernal(config))
		sio_data->पूर्णांकernal |= BIT(1);

	/* in8 (Vbat) is always पूर्णांकernal */
	sio_data->पूर्णांकernal |= BIT(2);

	/* in9 (AVCC3), always पूर्णांकernal अगर supported */
	अगर (has_avcc3(config))
		sio_data->पूर्णांकernal |= BIT(3); /* in9 is AVCC */
	अन्यथा
		sio_data->skip_in |= BIT(9);

	अगर (!has_five_pwm(config))
		sio_data->skip_pwm |= BIT(3) | BIT(4) | BIT(5);
	अन्यथा अगर (!has_six_pwm(config))
		sio_data->skip_pwm |= BIT(5);

	अगर (!has_vid(config))
		sio_data->skip_vid = 1;

	/* Read GPIO config and VID value from LDN 7 (GPIO) */
	अगर (sio_data->type == it87) अणु
		/* The IT8705F has a dअगरferent LD number क्रम GPIO */
		superio_select(sioaddr, 5);
		sio_data->beep_pin = superio_inb(sioaddr,
						 IT87_SIO_BEEP_PIN_REG) & 0x3f;
	पूर्ण अन्यथा अगर (sio_data->type == it8783) अणु
		पूर्णांक reg25, reg27, reg2a, reg2c, regef;

		superio_select(sioaddr, GPIO);

		reg25 = superio_inb(sioaddr, IT87_SIO_GPIO1_REG);
		reg27 = superio_inb(sioaddr, IT87_SIO_GPIO3_REG);
		reg2a = superio_inb(sioaddr, IT87_SIO_PINX1_REG);
		reg2c = superio_inb(sioaddr, IT87_SIO_PINX2_REG);
		regef = superio_inb(sioaddr, IT87_SIO_SPI_REG);

		/* Check अगर fan3 is there or not */
		अगर ((reg27 & BIT(0)) || !(reg2c & BIT(2)))
			sio_data->skip_fan |= BIT(2);
		अगर ((reg25 & BIT(4)) ||
		    (!(reg2a & BIT(1)) && (regef & BIT(0))))
			sio_data->skip_pwm |= BIT(2);

		/* Check अगर fan2 is there or not */
		अगर (reg27 & BIT(7))
			sio_data->skip_fan |= BIT(1);
		अगर (reg27 & BIT(3))
			sio_data->skip_pwm |= BIT(1);

		/* VIN5 */
		अगर ((reg27 & BIT(0)) || (reg2c & BIT(2)))
			sio_data->skip_in |= BIT(5); /* No VIN5 */

		/* VIN6 */
		अगर (reg27 & BIT(1))
			sio_data->skip_in |= BIT(6); /* No VIN6 */

		/*
		 * VIN7
		 * Does not depend on bit 2 of Reg2C, contrary to datasheet.
		 */
		अगर (reg27 & BIT(2)) अणु
			/*
			 * The data sheet is a bit unclear regarding the
			 * पूर्णांकernal voltage भागider क्रम VCCH5V. It says
			 * "This bit enables and चयनes VIN7 (pin 91) to the
			 * पूर्णांकernal voltage भागider क्रम VCCH5V".
			 * This is dअगरferent to other chips, where the पूर्णांकernal
			 * voltage भागider would connect VIN7 to an पूर्णांकernal
			 * voltage source. Maybe that is the हाल here as well.
			 *
			 * Since we करोn't know क्रम sure, re-route it अगर that is
			 * not the हाल, and ask the user to report अगर the
			 * resulting voltage is sane.
			 */
			अगर (!(reg2c & BIT(1))) अणु
				reg2c |= BIT(1);
				superio_outb(sioaddr, IT87_SIO_PINX2_REG,
					     reg2c);
				sio_data->need_in7_reroute = true;
				pr_notice("Routing internal VCCH5V to in7.\n");
			पूर्ण
			pr_notice("in7 routed to internal voltage divider, with external pin disabled.\n");
			pr_notice("Please report if it displays a reasonable voltage.\n");
		पूर्ण

		अगर (reg2c & BIT(0))
			sio_data->पूर्णांकernal |= BIT(0);
		अगर (reg2c & BIT(1))
			sio_data->पूर्णांकernal |= BIT(1);

		sio_data->beep_pin = superio_inb(sioaddr,
						 IT87_SIO_BEEP_PIN_REG) & 0x3f;
	पूर्ण अन्यथा अगर (sio_data->type == it8603) अणु
		पूर्णांक reg27, reg29;

		superio_select(sioaddr, GPIO);

		reg27 = superio_inb(sioaddr, IT87_SIO_GPIO3_REG);

		/* Check अगर fan3 is there or not */
		अगर (reg27 & BIT(6))
			sio_data->skip_pwm |= BIT(2);
		अगर (reg27 & BIT(7))
			sio_data->skip_fan |= BIT(2);

		/* Check अगर fan2 is there or not */
		reg29 = superio_inb(sioaddr, IT87_SIO_GPIO5_REG);
		अगर (reg29 & BIT(1))
			sio_data->skip_pwm |= BIT(1);
		अगर (reg29 & BIT(2))
			sio_data->skip_fan |= BIT(1);

		sio_data->skip_in |= BIT(5); /* No VIN5 */
		sio_data->skip_in |= BIT(6); /* No VIN6 */

		sio_data->beep_pin = superio_inb(sioaddr,
						 IT87_SIO_BEEP_PIN_REG) & 0x3f;
	पूर्ण अन्यथा अगर (sio_data->type == it8620 || sio_data->type == it8628) अणु
		पूर्णांक reg;

		superio_select(sioaddr, GPIO);

		/* Check क्रम pwm5 */
		reg = superio_inb(sioaddr, IT87_SIO_GPIO1_REG);
		अगर (reg & BIT(6))
			sio_data->skip_pwm |= BIT(4);

		/* Check क्रम fan4, fan5 */
		reg = superio_inb(sioaddr, IT87_SIO_GPIO2_REG);
		अगर (!(reg & BIT(5)))
			sio_data->skip_fan |= BIT(3);
		अगर (!(reg & BIT(4)))
			sio_data->skip_fan |= BIT(4);

		/* Check क्रम pwm3, fan3 */
		reg = superio_inb(sioaddr, IT87_SIO_GPIO3_REG);
		अगर (reg & BIT(6))
			sio_data->skip_pwm |= BIT(2);
		अगर (reg & BIT(7))
			sio_data->skip_fan |= BIT(2);

		/* Check क्रम pwm4 */
		reg = superio_inb(sioaddr, IT87_SIO_GPIO4_REG);
		अगर (reg & BIT(2))
			sio_data->skip_pwm |= BIT(3);

		/* Check क्रम pwm2, fan2 */
		reg = superio_inb(sioaddr, IT87_SIO_GPIO5_REG);
		अगर (reg & BIT(1))
			sio_data->skip_pwm |= BIT(1);
		अगर (reg & BIT(2))
			sio_data->skip_fan |= BIT(1);
		/* Check क्रम pwm6, fan6 */
		अगर (!(reg & BIT(7))) अणु
			sio_data->skip_pwm |= BIT(5);
			sio_data->skip_fan |= BIT(5);
		पूर्ण

		/* Check अगर AVCC is on VIN3 */
		reg = superio_inb(sioaddr, IT87_SIO_PINX2_REG);
		अगर (reg & BIT(0))
			sio_data->पूर्णांकernal |= BIT(0);
		अन्यथा
			sio_data->skip_in |= BIT(9);

		sio_data->beep_pin = superio_inb(sioaddr,
						 IT87_SIO_BEEP_PIN_REG) & 0x3f;
	पूर्ण अन्यथा अगर (sio_data->type == it8622) अणु
		पूर्णांक reg;

		superio_select(sioaddr, GPIO);

		/* Check क्रम pwm4, fan4 */
		reg = superio_inb(sioaddr, IT87_SIO_GPIO1_REG);
		अगर (reg & BIT(6))
			sio_data->skip_fan |= BIT(3);
		अगर (reg & BIT(5))
			sio_data->skip_pwm |= BIT(3);

		/* Check क्रम pwm3, fan3, pwm5, fan5 */
		reg = superio_inb(sioaddr, IT87_SIO_GPIO3_REG);
		अगर (reg & BIT(6))
			sio_data->skip_pwm |= BIT(2);
		अगर (reg & BIT(7))
			sio_data->skip_fan |= BIT(2);
		अगर (reg & BIT(3))
			sio_data->skip_pwm |= BIT(4);
		अगर (reg & BIT(1))
			sio_data->skip_fan |= BIT(4);

		/* Check क्रम pwm2, fan2 */
		reg = superio_inb(sioaddr, IT87_SIO_GPIO5_REG);
		अगर (reg & BIT(1))
			sio_data->skip_pwm |= BIT(1);
		अगर (reg & BIT(2))
			sio_data->skip_fan |= BIT(1);

		/* Check क्रम AVCC */
		reg = superio_inb(sioaddr, IT87_SIO_PINX2_REG);
		अगर (!(reg & BIT(0)))
			sio_data->skip_in |= BIT(9);

		sio_data->beep_pin = superio_inb(sioaddr,
						 IT87_SIO_BEEP_PIN_REG) & 0x3f;
	पूर्ण अन्यथा अणु
		पूर्णांक reg;
		bool uart6;

		superio_select(sioaddr, GPIO);

		/* Check क्रम fan4, fan5 */
		अगर (has_five_fans(config)) अणु
			reg = superio_inb(sioaddr, IT87_SIO_GPIO2_REG);
			चयन (sio_data->type) अणु
			हाल it8718:
				अगर (reg & BIT(5))
					sio_data->skip_fan |= BIT(3);
				अगर (reg & BIT(4))
					sio_data->skip_fan |= BIT(4);
				अवरोध;
			हाल it8720:
			हाल it8721:
			हाल it8728:
				अगर (!(reg & BIT(5)))
					sio_data->skip_fan |= BIT(3);
				अगर (!(reg & BIT(4)))
					sio_data->skip_fan |= BIT(4);
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण

		reg = superio_inb(sioaddr, IT87_SIO_GPIO3_REG);
		अगर (!sio_data->skip_vid) अणु
			/* We need at least 4 VID pins */
			अगर (reg & 0x0f) अणु
				pr_info("VID is disabled (pins used for GPIO)\n");
				sio_data->skip_vid = 1;
			पूर्ण
		पूर्ण

		/* Check अगर fan3 is there or not */
		अगर (reg & BIT(6))
			sio_data->skip_pwm |= BIT(2);
		अगर (reg & BIT(7))
			sio_data->skip_fan |= BIT(2);

		/* Check अगर fan2 is there or not */
		reg = superio_inb(sioaddr, IT87_SIO_GPIO5_REG);
		अगर (reg & BIT(1))
			sio_data->skip_pwm |= BIT(1);
		अगर (reg & BIT(2))
			sio_data->skip_fan |= BIT(1);

		अगर ((sio_data->type == it8718 || sio_data->type == it8720) &&
		    !(sio_data->skip_vid))
			sio_data->vid_value = superio_inb(sioaddr,
							  IT87_SIO_VID_REG);

		reg = superio_inb(sioaddr, IT87_SIO_PINX2_REG);

		uart6 = sio_data->type == it8782 && (reg & BIT(2));

		/*
		 * The IT8720F has no VIN7 pin, so VCCH5V should always be
		 * routed पूर्णांकernally to VIN7 with an पूर्णांकernal भागider.
		 * Curiously, there still is a configuration bit to control
		 * this, which means it can be set incorrectly. And even
		 * more curiously, many boards out there are improperly
		 * configured, even though the IT8720F datasheet claims
		 * that the पूर्णांकernal routing of VCCH5V to VIN7 is the शेष
		 * setting. So we क्रमce the पूर्णांकernal routing in this हाल.
		 *
		 * On IT8782F, VIN7 is multiplexed with one of the UART6 pins.
		 * If UART6 is enabled, re-route VIN7 to the पूर्णांकernal भागider
		 * अगर that is not alपढ़ोy the हाल.
		 */
		अगर ((sio_data->type == it8720 || uart6) && !(reg & BIT(1))) अणु
			reg |= BIT(1);
			superio_outb(sioaddr, IT87_SIO_PINX2_REG, reg);
			sio_data->need_in7_reroute = true;
			pr_notice("Routing internal VCCH5V to in7\n");
		पूर्ण
		अगर (reg & BIT(0))
			sio_data->पूर्णांकernal |= BIT(0);
		अगर (reg & BIT(1))
			sio_data->पूर्णांकernal |= BIT(1);

		/*
		 * On IT8782F, UART6 pins overlap with VIN5, VIN6, and VIN7.
		 * While VIN7 can be routed to the पूर्णांकernal voltage भागider,
		 * VIN5 and VIN6 are not available अगर UART6 is enabled.
		 *
		 * Also, temp3 is not available अगर UART6 is enabled and TEMPIN3
		 * is the temperature source. Since we can not पढ़ो the
		 * temperature source here, skip_temp is preliminary.
		 */
		अगर (uart6) अणु
			sio_data->skip_in |= BIT(5) | BIT(6);
			sio_data->skip_temp |= BIT(2);
		पूर्ण

		sio_data->beep_pin = superio_inb(sioaddr,
						 IT87_SIO_BEEP_PIN_REG) & 0x3f;
	पूर्ण
	अगर (sio_data->beep_pin)
		pr_info("Beeping is supported\n");

	/* Disable specअगरic features based on DMI strings */
	board_venकरोr = dmi_get_प्रणाली_info(DMI_BOARD_VENDOR);
	board_name = dmi_get_प्रणाली_info(DMI_BOARD_NAME);
	अगर (board_venकरोr && board_name) अणु
		अगर (म_भेद(board_venकरोr, "nVIDIA") == 0 &&
		    म_भेद(board_name, "FN68PT") == 0) अणु
			/*
			 * On the Shuttle SN68PT, FAN_CTL2 is apparently not
			 * connected to a fan, but to something अन्यथा. One user
			 * has reported instant प्रणाली घातer-off when changing
			 * the PWM2 duty cycle, so we disable it.
			 * I use the board name string as the trigger in हाल
			 * the same board is ever used in other प्रणालीs.
			 */
			pr_info("Disabling pwm2 due to hardware constraints\n");
			sio_data->skip_pwm = BIT(1);
		पूर्ण
	पूर्ण

निकास:
	superio_निकास(sioaddr);
	वापस err;
पूर्ण

/*
 * Some chips seem to have शेष value 0xff क्रम all limit
 * रेजिस्टरs. For low voltage limits it makes no sense and triggers
 * alarms, so change to 0 instead. For high temperature limits, it
 * means -1 degree C, which surprisingly करोesn't trigger an alarm,
 * but is still confusing, so change to 127 degrees C.
 */
अटल व्योम it87_check_limit_regs(काष्ठा it87_data *data)
अणु
	पूर्णांक i, reg;

	क्रम (i = 0; i < NUM_VIN_LIMIT; i++) अणु
		reg = it87_पढ़ो_value(data, IT87_REG_VIN_MIN(i));
		अगर (reg == 0xff)
			it87_ग_लिखो_value(data, IT87_REG_VIN_MIN(i), 0);
	पूर्ण
	क्रम (i = 0; i < NUM_TEMP_LIMIT; i++) अणु
		reg = it87_पढ़ो_value(data, IT87_REG_TEMP_HIGH(i));
		अगर (reg == 0xff)
			it87_ग_लिखो_value(data, IT87_REG_TEMP_HIGH(i), 127);
	पूर्ण
पूर्ण

/* Check अगर voltage monitors are reset manually or by some reason */
अटल व्योम it87_check_voltage_monitors_reset(काष्ठा it87_data *data)
अणु
	पूर्णांक reg;

	reg = it87_पढ़ो_value(data, IT87_REG_VIN_ENABLE);
	अगर ((reg & 0xff) == 0) अणु
		/* Enable all voltage monitors */
		it87_ग_लिखो_value(data, IT87_REG_VIN_ENABLE, 0xff);
	पूर्ण
पूर्ण

/* Check अगर tachometers are reset manually or by some reason */
अटल व्योम it87_check_tachometers_reset(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा it87_sio_data *sio_data = dev_get_platdata(&pdev->dev);
	काष्ठा it87_data *data = platक्रमm_get_drvdata(pdev);
	u8 mask, fan_मुख्य_ctrl;

	mask = 0x70 & ~(sio_data->skip_fan << 4);
	fan_मुख्य_ctrl = it87_पढ़ो_value(data, IT87_REG_FAN_MAIN_CTRL);
	अगर ((fan_मुख्य_ctrl & mask) == 0) अणु
		/* Enable all fan tachometers */
		fan_मुख्य_ctrl |= mask;
		it87_ग_लिखो_value(data, IT87_REG_FAN_MAIN_CTRL,
				 fan_मुख्य_ctrl);
	पूर्ण
पूर्ण

/* Set tachometers to 16-bit mode अगर needed */
अटल व्योम it87_check_tachometers_16bit_mode(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा it87_data *data = platक्रमm_get_drvdata(pdev);
	पूर्णांक reg;

	अगर (!has_fan16_config(data))
		वापस;

	reg = it87_पढ़ो_value(data, IT87_REG_FAN_16BIT);
	अगर (~reg & 0x07 & data->has_fan) अणु
		dev_dbg(&pdev->dev,
			"Setting fan1-3 to 16-bit mode\n");
		it87_ग_लिखो_value(data, IT87_REG_FAN_16BIT,
				 reg | 0x07);
	पूर्ण
पूर्ण

अटल व्योम it87_start_monitoring(काष्ठा it87_data *data)
अणु
	it87_ग_लिखो_value(data, IT87_REG_CONFIG,
			 (it87_पढ़ो_value(data, IT87_REG_CONFIG) & 0x3e)
			 | (update_vbat ? 0x41 : 0x01));
पूर्ण

/* Called when we have found a new IT87. */
अटल व्योम it87_init_device(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा it87_sio_data *sio_data = dev_get_platdata(&pdev->dev);
	काष्ठा it87_data *data = platक्रमm_get_drvdata(pdev);
	पूर्णांक पंचांगp, i;

	/*
	 * For each PWM channel:
	 * - If it is in स्वतःmatic mode, setting to manual mode should set
	 *   the fan to full speed by शेष.
	 * - If it is in manual mode, we need a mapping to temperature
	 *   channels to use when later setting to स्वतःmatic mode later.
	 *   Use a 1:1 mapping by शेष (we are clueless.)
	 * In both हालs, the value can (and should) be changed by the user
	 * prior to चयनing to a dअगरferent mode.
	 * Note that this is no दीर्घer needed क्रम the IT8721F and later, as
	 * these have separate रेजिस्टरs क्रम the temperature mapping and the
	 * manual duty cycle.
	 */
	क्रम (i = 0; i < NUM_AUTO_PWM; i++) अणु
		data->pwm_temp_map[i] = i;
		data->pwm_duty[i] = 0x7f;	/* Full speed */
		data->स्वतः_pwm[i][3] = 0x7f;	/* Full speed, hard-coded */
	पूर्ण

	it87_check_limit_regs(data);

	/*
	 * Temperature channels are not क्रमcibly enabled, as they can be
	 * set to two dअगरferent sensor types and we can't guess which one
	 * is correct क्रम a given प्रणाली. These channels can be enabled at
	 * run-समय through the tempअणु1-3पूर्ण_type sysfs accessors अगर needed.
	 */

	it87_check_voltage_monitors_reset(data);

	it87_check_tachometers_reset(pdev);

	data->fan_मुख्य_ctrl = it87_पढ़ो_value(data, IT87_REG_FAN_MAIN_CTRL);
	data->has_fan = (data->fan_मुख्य_ctrl >> 4) & 0x07;

	it87_check_tachometers_16bit_mode(pdev);

	/* Check क्रम additional fans */
	अगर (has_five_fans(data)) अणु
		पंचांगp = it87_पढ़ो_value(data, IT87_REG_FAN_16BIT);

		अगर (पंचांगp & BIT(4))
			data->has_fan |= BIT(3); /* fan4 enabled */
		अगर (पंचांगp & BIT(5))
			data->has_fan |= BIT(4); /* fan5 enabled */
		अगर (has_six_fans(data) && (पंचांगp & BIT(2)))
			data->has_fan |= BIT(5); /* fan6 enabled */
	पूर्ण

	/* Fan input pins may be used क्रम alternative functions */
	data->has_fan &= ~sio_data->skip_fan;

	/* Check अगर pwm5, pwm6 are enabled */
	अगर (has_six_pwm(data)) अणु
		/* The following code may be IT8620E specअगरic */
		पंचांगp = it87_पढ़ो_value(data, IT87_REG_FAN_DIV);
		अगर ((पंचांगp & 0xc0) == 0xc0)
			sio_data->skip_pwm |= BIT(4);
		अगर (!(पंचांगp & BIT(3)))
			sio_data->skip_pwm |= BIT(5);
	पूर्ण

	it87_start_monitoring(data);
पूर्ण

/* Return 1 अगर and only अगर the PWM पूर्णांकerface is safe to use */
अटल पूर्णांक it87_check_pwm(काष्ठा device *dev)
अणु
	काष्ठा it87_data *data = dev_get_drvdata(dev);
	/*
	 * Some BIOSes fail to correctly configure the IT87 fans. All fans off
	 * and polarity set to active low is sign that this is the हाल so we
	 * disable pwm control to protect the user.
	 */
	पूर्णांक पंचांगp = it87_पढ़ो_value(data, IT87_REG_FAN_CTL);

	अगर ((पंचांगp & 0x87) == 0) अणु
		अगर (fix_pwm_polarity) अणु
			/*
			 * The user asks us to attempt a chip reconfiguration.
			 * This means चयनing to active high polarity and
			 * inverting all fan speed values.
			 */
			पूर्णांक i;
			u8 pwm[3];

			क्रम (i = 0; i < ARRAY_SIZE(pwm); i++)
				pwm[i] = it87_पढ़ो_value(data,
							 IT87_REG_PWM[i]);

			/*
			 * If any fan is in स्वतःmatic pwm mode, the polarity
			 * might be correct, as suspicious as it seems, so we
			 * better करोn't change anything (but still disable the
			 * PWM पूर्णांकerface).
			 */
			अगर (!((pwm[0] | pwm[1] | pwm[2]) & 0x80)) अणु
				dev_info(dev,
					 "Reconfiguring PWM to active high polarity\n");
				it87_ग_लिखो_value(data, IT87_REG_FAN_CTL,
						 पंचांगp | 0x87);
				क्रम (i = 0; i < 3; i++)
					it87_ग_लिखो_value(data,
							 IT87_REG_PWM[i],
							 0x7f & ~pwm[i]);
				वापस 1;
			पूर्ण

			dev_info(dev,
				 "PWM configuration is too broken to be fixed\n");
		पूर्ण

		वापस 0;
	पूर्ण अन्यथा अगर (fix_pwm_polarity) अणु
		dev_info(dev,
			 "PWM configuration looks sane, won't touch\n");
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक it87_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा it87_data *data;
	काष्ठा resource *res;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा it87_sio_data *sio_data = dev_get_platdata(dev);
	पूर्णांक enable_pwm_पूर्णांकerface;
	काष्ठा device *hwmon_dev;

	res = platक्रमm_get_resource(pdev, IORESOURCE_IO, 0);
	अगर (!devm_request_region(&pdev->dev, res->start, IT87_EC_EXTENT,
				 DRVNAME)) अणु
		dev_err(dev, "Failed to request region 0x%lx-0x%lx\n",
			(अचिन्हित दीर्घ)res->start,
			(अचिन्हित दीर्घ)(res->start + IT87_EC_EXTENT - 1));
		वापस -EBUSY;
	पूर्ण

	data = devm_kzalloc(&pdev->dev, माप(काष्ठा it87_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->addr = res->start;
	data->sioaddr = sio_data->sioaddr;
	data->type = sio_data->type;
	data->features = it87_devices[sio_data->type].features;
	data->peci_mask = it87_devices[sio_data->type].peci_mask;
	data->old_peci_mask = it87_devices[sio_data->type].old_peci_mask;
	/*
	 * IT8705F Datasheet 0.4.1, 3h == Version G.
	 * IT8712F Datasheet 0.9.1, section 8.3.5 indicates 8h == Version J.
	 * These are the first revisions with 16-bit tachometer support.
	 */
	चयन (data->type) अणु
	हाल it87:
		अगर (sio_data->revision >= 0x03) अणु
			data->features &= ~FEAT_OLD_AUTOPWM;
			data->features |= FEAT_FAN16_CONFIG | FEAT_16BIT_FANS;
		पूर्ण
		अवरोध;
	हाल it8712:
		अगर (sio_data->revision >= 0x08) अणु
			data->features &= ~FEAT_OLD_AUTOPWM;
			data->features |= FEAT_FAN16_CONFIG | FEAT_16BIT_FANS |
					  FEAT_FIVE_FANS;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* Now, we करो the reमुख्यing detection. */
	अगर ((it87_पढ़ो_value(data, IT87_REG_CONFIG) & 0x80) ||
	    it87_पढ़ो_value(data, IT87_REG_CHIPID) != 0x90)
		वापस -ENODEV;

	platक्रमm_set_drvdata(pdev, data);

	mutex_init(&data->update_lock);

	/* Check PWM configuration */
	enable_pwm_पूर्णांकerface = it87_check_pwm(dev);
	अगर (!enable_pwm_पूर्णांकerface)
		dev_info(dev,
			 "Detected broken BIOS defaults, disabling PWM interface\n");

	/* Starting with IT8721F, we handle scaling of पूर्णांकernal voltages */
	अगर (has_12mv_adc(data)) अणु
		अगर (sio_data->पूर्णांकernal & BIT(0))
			data->in_scaled |= BIT(3);	/* in3 is AVCC */
		अगर (sio_data->पूर्णांकernal & BIT(1))
			data->in_scaled |= BIT(7);	/* in7 is VSB */
		अगर (sio_data->पूर्णांकernal & BIT(2))
			data->in_scaled |= BIT(8);	/* in8 is Vbat */
		अगर (sio_data->पूर्णांकernal & BIT(3))
			data->in_scaled |= BIT(9);	/* in9 is AVCC */
	पूर्ण अन्यथा अगर (sio_data->type == it8781 || sio_data->type == it8782 ||
		   sio_data->type == it8783) अणु
		अगर (sio_data->पूर्णांकernal & BIT(0))
			data->in_scaled |= BIT(3);	/* in3 is VCC5V */
		अगर (sio_data->पूर्णांकernal & BIT(1))
			data->in_scaled |= BIT(7);	/* in7 is VCCH5V */
	पूर्ण

	data->has_temp = 0x07;
	अगर (sio_data->skip_temp & BIT(2)) अणु
		अगर (sio_data->type == it8782 &&
		    !(it87_पढ़ो_value(data, IT87_REG_TEMP_EXTRA) & 0x80))
			data->has_temp &= ~BIT(2);
	पूर्ण

	data->in_पूर्णांकernal = sio_data->पूर्णांकernal;
	data->need_in7_reroute = sio_data->need_in7_reroute;
	data->has_in = 0x3ff & ~sio_data->skip_in;

	अगर (has_six_temp(data)) अणु
		u8 reg = it87_पढ़ो_value(data, IT87_REG_TEMP456_ENABLE);

		/* Check क्रम additional temperature sensors */
		अगर ((reg & 0x03) >= 0x02)
			data->has_temp |= BIT(3);
		अगर (((reg >> 2) & 0x03) >= 0x02)
			data->has_temp |= BIT(4);
		अगर (((reg >> 4) & 0x03) >= 0x02)
			data->has_temp |= BIT(5);

		/* Check क्रम additional voltage sensors */
		अगर ((reg & 0x03) == 0x01)
			data->has_in |= BIT(10);
		अगर (((reg >> 2) & 0x03) == 0x01)
			data->has_in |= BIT(11);
		अगर (((reg >> 4) & 0x03) == 0x01)
			data->has_in |= BIT(12);
	पूर्ण

	data->has_beep = !!sio_data->beep_pin;

	/* Initialize the IT87 chip */
	it87_init_device(pdev);

	अगर (!sio_data->skip_vid) अणु
		data->has_vid = true;
		data->vrm = vid_which_vrm();
		/* VID पढ़ोing from Super-I/O config space अगर available */
		data->vid = sio_data->vid_value;
	पूर्ण

	/* Prepare क्रम sysfs hooks */
	data->groups[0] = &it87_group;
	data->groups[1] = &it87_group_in;
	data->groups[2] = &it87_group_temp;
	data->groups[3] = &it87_group_fan;

	अगर (enable_pwm_पूर्णांकerface) अणु
		data->has_pwm = BIT(ARRAY_SIZE(IT87_REG_PWM)) - 1;
		data->has_pwm &= ~sio_data->skip_pwm;

		data->groups[4] = &it87_group_pwm;
		अगर (has_old_स्वतःpwm(data) || has_newer_स्वतःpwm(data))
			data->groups[5] = &it87_group_स्वतः_pwm;
	पूर्ण

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev,
					it87_devices[sio_data->type].name,
					data, data->groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल व्योम __maybe_unused it87_resume_sio(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा it87_data *data = dev_get_drvdata(&pdev->dev);
	पूर्णांक err;
	पूर्णांक reg2c;

	अगर (!data->need_in7_reroute)
		वापस;

	err = superio_enter(data->sioaddr);
	अगर (err) अणु
		dev_warn(&pdev->dev,
			 "Unable to enter Super I/O to reroute in7 (%d)",
			 err);
		वापस;
	पूर्ण

	superio_select(data->sioaddr, GPIO);

	reg2c = superio_inb(data->sioaddr, IT87_SIO_PINX2_REG);
	अगर (!(reg2c & BIT(1))) अणु
		dev_dbg(&pdev->dev,
			"Routing internal VCCH5V to in7 again");

		reg2c |= BIT(1);
		superio_outb(data->sioaddr, IT87_SIO_PINX2_REG,
			     reg2c);
	पूर्ण

	superio_निकास(data->sioaddr);
पूर्ण

अटल पूर्णांक __maybe_unused it87_resume(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा it87_data *data = dev_get_drvdata(dev);

	it87_resume_sio(pdev);

	mutex_lock(&data->update_lock);

	it87_check_pwm(dev);
	it87_check_limit_regs(data);
	it87_check_voltage_monitors_reset(data);
	it87_check_tachometers_reset(pdev);
	it87_check_tachometers_16bit_mode(pdev);

	it87_start_monitoring(data);

	/* क्रमce update */
	data->valid = 0;

	mutex_unlock(&data->update_lock);

	it87_update_device(dev);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(it87_dev_pm_ops, शून्य, it87_resume);

अटल काष्ठा platक्रमm_driver it87_driver = अणु
	.driver = अणु
		.name	= DRVNAME,
		.pm     = &it87_dev_pm_ops,
	पूर्ण,
	.probe	= it87_probe,
पूर्ण;

अटल पूर्णांक __init it87_device_add(पूर्णांक index, अचिन्हित लघु address,
				  स्थिर काष्ठा it87_sio_data *sio_data)
अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा resource res = अणु
		.start	= address + IT87_EC_OFFSET,
		.end	= address + IT87_EC_OFFSET + IT87_EC_EXTENT - 1,
		.name	= DRVNAME,
		.flags	= IORESOURCE_IO,
	पूर्ण;
	पूर्णांक err;

	err = acpi_check_resource_conflict(&res);
	अगर (err)
		वापस err;

	pdev = platक्रमm_device_alloc(DRVNAME, address);
	अगर (!pdev)
		वापस -ENOMEM;

	err = platक्रमm_device_add_resources(pdev, &res, 1);
	अगर (err) अणु
		pr_err("Device resource addition failed (%d)\n", err);
		जाओ निकास_device_put;
	पूर्ण

	err = platक्रमm_device_add_data(pdev, sio_data,
				       माप(काष्ठा it87_sio_data));
	अगर (err) अणु
		pr_err("Platform data allocation failed\n");
		जाओ निकास_device_put;
	पूर्ण

	err = platक्रमm_device_add(pdev);
	अगर (err) अणु
		pr_err("Device addition failed (%d)\n", err);
		जाओ निकास_device_put;
	पूर्ण

	it87_pdev[index] = pdev;
	वापस 0;

निकास_device_put:
	platक्रमm_device_put(pdev);
	वापस err;
पूर्ण

अटल पूर्णांक __init sm_it87_init(व्योम)
अणु
	पूर्णांक sioaddr[2] = अणु REG_2E, REG_4E पूर्ण;
	काष्ठा it87_sio_data sio_data;
	अचिन्हित लघु isa_address[2];
	bool found = false;
	पूर्णांक i, err;

	err = platक्रमm_driver_रेजिस्टर(&it87_driver);
	अगर (err)
		वापस err;

	क्रम (i = 0; i < ARRAY_SIZE(sioaddr); i++) अणु
		स_रखो(&sio_data, 0, माप(काष्ठा it87_sio_data));
		isa_address[i] = 0;
		err = it87_find(sioaddr[i], &isa_address[i], &sio_data);
		अगर (err || isa_address[i] == 0)
			जारी;
		/*
		 * Don't रेजिस्टर second chip अगर its ISA address matches
		 * the first chip's ISA address.
		 */
		अगर (i && isa_address[i] == isa_address[0])
			अवरोध;

		err = it87_device_add(i, isa_address[i], &sio_data);
		अगर (err)
			जाओ निकास_dev_unरेजिस्टर;

		found = true;

		/*
		 * IT8705F may respond on both SIO addresses.
		 * Stop probing after finding one.
		 */
		अगर (sio_data.type == it87)
			अवरोध;
	पूर्ण

	अगर (!found) अणु
		err = -ENODEV;
		जाओ निकास_unरेजिस्टर;
	पूर्ण
	वापस 0;

निकास_dev_unरेजिस्टर:
	/* शून्य check handled by platक्रमm_device_unरेजिस्टर */
	platक्रमm_device_unरेजिस्टर(it87_pdev[0]);
निकास_unरेजिस्टर:
	platक्रमm_driver_unरेजिस्टर(&it87_driver);
	वापस err;
पूर्ण

अटल व्योम __निकास sm_it87_निकास(व्योम)
अणु
	/* शून्य check handled by platक्रमm_device_unरेजिस्टर */
	platक्रमm_device_unरेजिस्टर(it87_pdev[1]);
	platक्रमm_device_unरेजिस्टर(it87_pdev[0]);
	platक्रमm_driver_unरेजिस्टर(&it87_driver);
पूर्ण

MODULE_AUTHOR("Chris Gauthron, Jean Delvare <jdelvare@suse.de>");
MODULE_DESCRIPTION("IT8705F/IT871xF/IT872xF hardware monitoring driver");
module_param(update_vbat, bool, 0);
MODULE_PARM_DESC(update_vbat, "Update vbat if set else return powerup value");
module_param(fix_pwm_polarity, bool, 0);
MODULE_PARM_DESC(fix_pwm_polarity,
		 "Force PWM polarity to active high (DANGEROUS)");
MODULE_LICENSE("GPL");

module_init(sm_it87_init);
module_निकास(sm_it87_निकास);
