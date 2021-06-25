<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) ST-Ericsson SA 2010
 *
 * Author: Mattias Wallin <mattias.wallin@stericsson.com> क्रम ST-Ericsson.
 */
/*
 * AB8500 रेजिस्टर access
 * ======================
 *
 * पढ़ो:
 * # echo BANK  >  <debugfs>/ab8500/रेजिस्टर-bank
 * # echo ADDR  >  <debugfs>/ab8500/रेजिस्टर-address
 * # cat <debugfs>/ab8500/रेजिस्टर-value
 *
 * ग_लिखो:
 * # echo BANK  >  <debugfs>/ab8500/रेजिस्टर-bank
 * # echo ADDR  >  <debugfs>/ab8500/रेजिस्टर-address
 * # echo VALUE >  <debugfs>/ab8500/रेजिस्टर-value
 *
 * पढ़ो all रेजिस्टरs from a bank:
 * # echo BANK  >  <debugfs>/ab8500/रेजिस्टर-bank
 * # cat <debugfs>/ab8500/all-bank-रेजिस्टर
 *
 * BANK   target AB8500 रेजिस्टर bank
 * ADDR   target AB8500 रेजिस्टर address
 * VALUE  decimal or 0x-prefixed hexadecimal
 *
 *
 * User Space notअगरication on AB8500 IRQ
 * =====================================
 *
 * Allows user space entity to be notअगरied when target AB8500 IRQ occurs.
 * When subscribed, a sysfs entry is created in ab8500.i2c platक्रमm device.
 * One can pool this file to get target IRQ occurence inक्रमmation.
 *
 * subscribe to an AB8500 IRQ:
 * # echo IRQ  >  <debugfs>/ab8500/irq-subscribe
 *
 * unsubscribe from an AB8500 IRQ:
 * # echo IRQ  >  <debugfs>/ab8500/irq-unsubscribe
 *
 *
 * AB8500 रेजिस्टर क्रमmated पढ़ो/ग_लिखो access
 * ==========================================
 *
 * Read:  पढ़ो data, data>>SHIFT, data&=MASK, output data
 *        [0xABCDEF98] shअगरt=12 mask=0xFFF => 0x00000CDE
 * Write: पढ़ो data, data &= ~(MASK<<SHIFT), data |= (VALUE<<SHIFT), ग_लिखो data
 *        [0xABCDEF98] shअगरt=12 mask=0xFFF value=0x123 => [0xAB123F98]
 *
 * Usage:
 * # echo "CMD [OPTIONS] BANK ADRESS [VALUE]" > $debugfs/ab8500/hwreg
 *
 * CMD      पढ़ो      पढ़ो access
 *          ग_लिखो     ग_लिखो access
 *
 * BANK     target reg bank
 * ADDRESS  target reg address
 * VALUE    (ग_लिखो) value to be updated
 *
 * OPTIONS
 *  -d|-dec            (पढ़ो) output in decimal
 *  -h|-hexa           (पढ़ो) output in 0x-hexa (शेष)
 *  -l|-w|-b           32bit (शेष), 16bit or 8bit reg access
 *  -m|-mask MASK      0x-hexa mask (शेष 0xFFFFFFFF)
 *  -s|-shअगरt SHIFT    bit shअगरt value (पढ़ो:left, ग_लिखो:right)
 *  -o|-offset OFFSET  address offset to add to ADDRESS value
 *
 * Warning: bit shअगरt operation is applied to bit-mask.
 * Warning: bit shअगरt direction depends on पढ़ो or right command.
 */

#समावेश <linux/seq_file.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kobject.h>
#समावेश <linux/slab.h>
#समावेश <linux/irq.h>

#समावेश <linux/mfd/abx500.h>
#समावेश <linux/mfd/abx500/ab8500.h>

#अगर_घोषित CONFIG_DEBUG_FS
#समावेश <linux/माला.स>
#समावेश <linux/प्रकार.स>
#पूर्ण_अगर

अटल u32 debug_bank;
अटल u32 debug_address;

अटल पूर्णांक irq_ab8500;
अटल पूर्णांक irq_first;
अटल पूर्णांक irq_last;
अटल u32 *irq_count;
अटल पूर्णांक num_irqs;

अटल काष्ठा device_attribute **dev_attr;
अटल अक्षर **event_name;

/**
 * काष्ठा ab8500_reg_range
 * @first: the first address of the range
 * @last: the last address of the range
 * @perm: access permissions क्रम the range
 */
काष्ठा ab8500_reg_range अणु
	u8 first;
	u8 last;
	u8 perm;
पूर्ण;

/**
 * काष्ठा ab8500_prcmu_ranges
 * @num_ranges: the number of ranges in the list
 * @bankid: bank identअगरier
 * @range: the list of रेजिस्टर ranges
 */
काष्ठा ab8500_prcmu_ranges अणु
	u8 num_ranges;
	u8 bankid;
	स्थिर काष्ठा ab8500_reg_range *range;
पूर्ण;

/* hwreg- "mask" and "shift" entries ressources */
काष्ठा hwreg_cfg अणु
	u32  bank;      /* target bank */
	अचिन्हित दीर्घ addr;      /* target address */
	uपूर्णांक fmt;       /* क्रमmat */
	अचिन्हित दीर्घ mask; /* पढ़ो/ग_लिखो mask, applied beक्रमe any bit shअगरt */
	दीर्घ shअगरt;     /* bit shअगरt (पढ़ो:right shअगरt, ग_लिखो:left shअगरt */
पूर्ण;
/* fmt bit #0: 0=hexa, 1=dec */
#घोषणा REG_FMT_DEC(c) ((c)->fmt & 0x1)
#घोषणा REG_FMT_HEX(c) (!REG_FMT_DEC(c))

अटल काष्ठा hwreg_cfg hwreg_cfg = अणु
	.addr = 0,			/* शेष: invalid phys addr */
	.fmt = 0,			/* शेष: 32bit access, hex output */
	.mask = 0xFFFFFFFF,	/* शेष: no mask */
	.shअगरt = 0,			/* शेष: no bit shअगरt */
पूर्ण;

#घोषणा AB8500_NAME_STRING "ab8500"
#घोषणा AB8500_NUM_BANKS AB8500_DEBUG_FIELD_LAST

#घोषणा AB8500_REV_REG 0x80

अटल काष्ठा ab8500_prcmu_ranges *debug_ranges;

अटल काष्ठा ab8500_prcmu_ranges ab8500_debug_ranges[AB8500_NUM_BANKS] = अणु
	[AB8500_M_FSM_RANK] = अणु
		.num_ranges = 0,
		.range = शून्य,
	पूर्ण,
	[AB8500_SYS_CTRL1_BLOCK] = अणु
		.num_ranges = 3,
		.range = (काष्ठा ab8500_reg_range[]) अणु
			अणु
				.first = 0x00,
				.last = 0x02,
			पूर्ण,
			अणु
				.first = 0x42,
				.last = 0x42,
			पूर्ण,
			अणु
				.first = 0x80,
				.last = 0x81,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[AB8500_SYS_CTRL2_BLOCK] = अणु
		.num_ranges = 4,
		.range = (काष्ठा ab8500_reg_range[]) अणु
			अणु
				.first = 0x00,
				.last = 0x0D,
			पूर्ण,
			अणु
				.first = 0x0F,
				.last = 0x17,
			पूर्ण,
			अणु
				.first = 0x30,
				.last = 0x30,
			पूर्ण,
			अणु
				.first = 0x32,
				.last = 0x33,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[AB8500_REGU_CTRL1] = अणु
		.num_ranges = 3,
		.range = (काष्ठा ab8500_reg_range[]) अणु
			अणु
				.first = 0x00,
				.last = 0x00,
			पूर्ण,
			अणु
				.first = 0x03,
				.last = 0x10,
			पूर्ण,
			अणु
				.first = 0x80,
				.last = 0x84,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[AB8500_REGU_CTRL2] = अणु
		.num_ranges = 5,
		.range = (काष्ठा ab8500_reg_range[]) अणु
			अणु
				.first = 0x00,
				.last = 0x15,
			पूर्ण,
			अणु
				.first = 0x17,
				.last = 0x19,
			पूर्ण,
			अणु
				.first = 0x1B,
				.last = 0x1D,
			पूर्ण,
			अणु
				.first = 0x1F,
				.last = 0x22,
			पूर्ण,
			अणु
				.first = 0x40,
				.last = 0x44,
			पूर्ण,
			/*
			 * 0x80-0x8B are SIM रेजिस्टरs and should
			 * not be accessed from here
			 */
		पूर्ण,
	पूर्ण,
	[AB8500_USB] = अणु
		.num_ranges = 2,
		.range = (काष्ठा ab8500_reg_range[]) अणु
			अणु
				.first = 0x80,
				.last = 0x83,
			पूर्ण,
			अणु
				.first = 0x87,
				.last = 0x8A,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[AB8500_TVOUT] = अणु
		.num_ranges = 9,
		.range = (काष्ठा ab8500_reg_range[]) अणु
			अणु
				.first = 0x00,
				.last = 0x12,
			पूर्ण,
			अणु
				.first = 0x15,
				.last = 0x17,
			पूर्ण,
			अणु
				.first = 0x19,
				.last = 0x21,
			पूर्ण,
			अणु
				.first = 0x27,
				.last = 0x2C,
			पूर्ण,
			अणु
				.first = 0x41,
				.last = 0x41,
			पूर्ण,
			अणु
				.first = 0x45,
				.last = 0x5B,
			पूर्ण,
			अणु
				.first = 0x5D,
				.last = 0x5D,
			पूर्ण,
			अणु
				.first = 0x69,
				.last = 0x69,
			पूर्ण,
			अणु
				.first = 0x80,
				.last = 0x81,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[AB8500_DBI] = अणु
		.num_ranges = 0,
		.range = शून्य,
	पूर्ण,
	[AB8500_ECI_AV_ACC] = अणु
		.num_ranges = 1,
		.range = (काष्ठा ab8500_reg_range[]) अणु
			अणु
				.first = 0x80,
				.last = 0x82,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[AB8500_RESERVED] = अणु
		.num_ranges = 0,
		.range = शून्य,
	पूर्ण,
	[AB8500_GPADC] = अणु
		.num_ranges = 1,
		.range = (काष्ठा ab8500_reg_range[]) अणु
			अणु
				.first = 0x00,
				.last = 0x08,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[AB8500_CHARGER] = अणु
		.num_ranges = 9,
		.range = (काष्ठा ab8500_reg_range[]) अणु
			अणु
				.first = 0x00,
				.last = 0x03,
			पूर्ण,
			अणु
				.first = 0x05,
				.last = 0x05,
			पूर्ण,
			अणु
				.first = 0x40,
				.last = 0x40,
			पूर्ण,
			अणु
				.first = 0x42,
				.last = 0x42,
			पूर्ण,
			अणु
				.first = 0x44,
				.last = 0x44,
			पूर्ण,
			अणु
				.first = 0x50,
				.last = 0x55,
			पूर्ण,
			अणु
				.first = 0x80,
				.last = 0x82,
			पूर्ण,
			अणु
				.first = 0xC0,
				.last = 0xC2,
			पूर्ण,
			अणु
				.first = 0xf5,
				.last = 0xf6,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[AB8500_GAS_GAUGE] = अणु
		.num_ranges = 3,
		.range = (काष्ठा ab8500_reg_range[]) अणु
			अणु
				.first = 0x00,
				.last = 0x00,
			पूर्ण,
			अणु
				.first = 0x07,
				.last = 0x0A,
			पूर्ण,
			अणु
				.first = 0x10,
				.last = 0x14,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[AB8500_AUDIO] = अणु
		.num_ranges = 1,
		.range = (काष्ठा ab8500_reg_range[]) अणु
			अणु
				.first = 0x00,
				.last = 0x6F,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[AB8500_INTERRUPT] = अणु
		.num_ranges = 0,
		.range = शून्य,
	पूर्ण,
	[AB8500_RTC] = अणु
		.num_ranges = 1,
		.range = (काष्ठा ab8500_reg_range[]) अणु
			अणु
				.first = 0x00,
				.last = 0x0F,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[AB8500_MISC] = अणु
		.num_ranges = 8,
		.range = (काष्ठा ab8500_reg_range[]) अणु
			अणु
				.first = 0x00,
				.last = 0x05,
			पूर्ण,
			अणु
				.first = 0x10,
				.last = 0x15,
			पूर्ण,
			अणु
				.first = 0x20,
				.last = 0x25,
			पूर्ण,
			अणु
				.first = 0x30,
				.last = 0x35,
			पूर्ण,
			अणु
				.first = 0x40,
				.last = 0x45,
			पूर्ण,
			अणु
				.first = 0x50,
				.last = 0x50,
			पूर्ण,
			अणु
				.first = 0x60,
				.last = 0x67,
			पूर्ण,
			अणु
				.first = 0x80,
				.last = 0x80,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[AB8500_DEVELOPMENT] = अणु
		.num_ranges = 1,
		.range = (काष्ठा ab8500_reg_range[]) अणु
			अणु
				.first = 0x00,
				.last = 0x00,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[AB8500_DEBUG] = अणु
		.num_ranges = 1,
		.range = (काष्ठा ab8500_reg_range[]) अणु
			अणु
				.first = 0x05,
				.last = 0x07,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[AB8500_PROD_TEST] = अणु
		.num_ranges = 0,
		.range = शून्य,
	पूर्ण,
	[AB8500_STE_TEST] = अणु
		.num_ranges = 0,
		.range = शून्य,
	पूर्ण,
	[AB8500_OTP_EMUL] = अणु
		.num_ranges = 1,
		.range = (काष्ठा ab8500_reg_range[]) अणु
			अणु
				.first = 0x01,
				.last = 0x0F,
			पूर्ण,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा ab8500_prcmu_ranges ab8505_debug_ranges[AB8500_NUM_BANKS] = अणु
	[0x0] = अणु
		.num_ranges = 0,
		.range = शून्य,
	पूर्ण,
	[AB8500_SYS_CTRL1_BLOCK] = अणु
		.num_ranges = 5,
		.range = (काष्ठा ab8500_reg_range[]) अणु
			अणु
				.first = 0x00,
				.last = 0x04,
			पूर्ण,
			अणु
				.first = 0x42,
				.last = 0x42,
			पूर्ण,
			अणु
				.first = 0x52,
				.last = 0x52,
			पूर्ण,
			अणु
				.first = 0x54,
				.last = 0x57,
			पूर्ण,
			अणु
				.first = 0x80,
				.last = 0x83,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[AB8500_SYS_CTRL2_BLOCK] = अणु
		.num_ranges = 5,
		.range = (काष्ठा ab8500_reg_range[]) अणु
			अणु
				.first = 0x00,
				.last = 0x0D,
			पूर्ण,
			अणु
				.first = 0x0F,
				.last = 0x17,
			पूर्ण,
			अणु
				.first = 0x20,
				.last = 0x20,
			पूर्ण,
			अणु
				.first = 0x30,
				.last = 0x30,
			पूर्ण,
			अणु
				.first = 0x32,
				.last = 0x3A,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[AB8500_REGU_CTRL1] = अणु
		.num_ranges = 3,
		.range = (काष्ठा ab8500_reg_range[]) अणु
			अणु
				.first = 0x00,
				.last = 0x00,
			पूर्ण,
			अणु
				.first = 0x03,
				.last = 0x11,
			पूर्ण,
			अणु
				.first = 0x80,
				.last = 0x86,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[AB8500_REGU_CTRL2] = अणु
		.num_ranges = 6,
		.range = (काष्ठा ab8500_reg_range[]) अणु
			अणु
				.first = 0x00,
				.last = 0x06,
			पूर्ण,
			अणु
				.first = 0x08,
				.last = 0x15,
			पूर्ण,
			अणु
				.first = 0x17,
				.last = 0x19,
			पूर्ण,
			अणु
				.first = 0x1B,
				.last = 0x1D,
			पूर्ण,
			अणु
				.first = 0x1F,
				.last = 0x30,
			पूर्ण,
			अणु
				.first = 0x40,
				.last = 0x48,
			पूर्ण,
			/*
			 * 0x80-0x8B are SIM रेजिस्टरs and should
			 * not be accessed from here
			 */
		पूर्ण,
	पूर्ण,
	[AB8500_USB] = अणु
		.num_ranges = 3,
		.range = (काष्ठा ab8500_reg_range[]) अणु
			अणु
				.first = 0x80,
				.last = 0x83,
			पूर्ण,
			अणु
				.first = 0x87,
				.last = 0x8A,
			पूर्ण,
			अणु
				.first = 0x91,
				.last = 0x94,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[AB8500_TVOUT] = अणु
		.num_ranges = 0,
		.range = शून्य,
	पूर्ण,
	[AB8500_DBI] = अणु
		.num_ranges = 0,
		.range = शून्य,
	पूर्ण,
	[AB8500_ECI_AV_ACC] = अणु
		.num_ranges = 1,
		.range = (काष्ठा ab8500_reg_range[]) अणु
			अणु
				.first = 0x80,
				.last = 0x82,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[AB8500_RESERVED] = अणु
		.num_ranges = 0,
		.range = शून्य,
	पूर्ण,
	[AB8500_GPADC] = अणु
		.num_ranges = 1,
		.range = (काष्ठा ab8500_reg_range[]) अणु
			अणु
				.first = 0x00,
				.last = 0x08,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[AB8500_CHARGER] = अणु
		.num_ranges = 9,
		.range = (काष्ठा ab8500_reg_range[]) अणु
			अणु
				.first = 0x02,
				.last = 0x03,
			पूर्ण,
			अणु
				.first = 0x05,
				.last = 0x05,
			पूर्ण,
			अणु
				.first = 0x40,
				.last = 0x44,
			पूर्ण,
			अणु
				.first = 0x50,
				.last = 0x57,
			पूर्ण,
			अणु
				.first = 0x60,
				.last = 0x60,
			पूर्ण,
			अणु
				.first = 0xA0,
				.last = 0xA7,
			पूर्ण,
			अणु
				.first = 0xAF,
				.last = 0xB2,
			पूर्ण,
			अणु
				.first = 0xC0,
				.last = 0xC2,
			पूर्ण,
			अणु
				.first = 0xF5,
				.last = 0xF5,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[AB8500_GAS_GAUGE] = अणु
		.num_ranges = 3,
		.range = (काष्ठा ab8500_reg_range[]) अणु
			अणु
				.first = 0x00,
				.last = 0x00,
			पूर्ण,
			अणु
				.first = 0x07,
				.last = 0x0A,
			पूर्ण,
			अणु
				.first = 0x10,
				.last = 0x14,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[AB8500_AUDIO] = अणु
		.num_ranges = 1,
		.range = (काष्ठा ab8500_reg_range[]) अणु
			अणु
				.first = 0x00,
				.last = 0x83,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[AB8500_INTERRUPT] = अणु
		.num_ranges = 11,
		.range = (काष्ठा ab8500_reg_range[]) अणु
			अणु
				.first = 0x00,
				.last = 0x04,
			पूर्ण,
			अणु
				.first = 0x06,
				.last = 0x07,
			पूर्ण,
			अणु
				.first = 0x09,
				.last = 0x09,
			पूर्ण,
			अणु
				.first = 0x0B,
				.last = 0x0C,
			पूर्ण,
			अणु
				.first = 0x12,
				.last = 0x15,
			पूर्ण,
			अणु
				.first = 0x18,
				.last = 0x18,
			पूर्ण,
			/* Latch रेजिस्टरs should not be पढ़ो here */
			अणु
				.first = 0x40,
				.last = 0x44,
			पूर्ण,
			अणु
				.first = 0x46,
				.last = 0x49,
			पूर्ण,
			अणु
				.first = 0x4B,
				.last = 0x4D,
			पूर्ण,
			अणु
				.first = 0x52,
				.last = 0x55,
			पूर्ण,
			अणु
				.first = 0x58,
				.last = 0x58,
			पूर्ण,
			/* LatchHier रेजिस्टरs should not be पढ़ो here */
		पूर्ण,
	पूर्ण,
	[AB8500_RTC] = अणु
		.num_ranges = 2,
		.range = (काष्ठा ab8500_reg_range[]) अणु
			अणु
				.first = 0x00,
				.last = 0x14,
			पूर्ण,
			अणु
				.first = 0x16,
				.last = 0x17,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[AB8500_MISC] = अणु
		.num_ranges = 8,
		.range = (काष्ठा ab8500_reg_range[]) अणु
			अणु
				.first = 0x00,
				.last = 0x06,
			पूर्ण,
			अणु
				.first = 0x10,
				.last = 0x16,
			पूर्ण,
			अणु
				.first = 0x20,
				.last = 0x26,
			पूर्ण,
			अणु
				.first = 0x30,
				.last = 0x36,
			पूर्ण,
			अणु
				.first = 0x40,
				.last = 0x46,
			पूर्ण,
			अणु
				.first = 0x50,
				.last = 0x50,
			पूर्ण,
			अणु
				.first = 0x60,
				.last = 0x6B,
			पूर्ण,
			अणु
				.first = 0x80,
				.last = 0x82,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[AB8500_DEVELOPMENT] = अणु
		.num_ranges = 2,
		.range = (काष्ठा ab8500_reg_range[]) अणु
			अणु
				.first = 0x00,
				.last = 0x00,
			पूर्ण,
			अणु
				.first = 0x05,
				.last = 0x05,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[AB8500_DEBUG] = अणु
		.num_ranges = 1,
		.range = (काष्ठा ab8500_reg_range[]) अणु
			अणु
				.first = 0x05,
				.last = 0x07,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[AB8500_PROD_TEST] = अणु
		.num_ranges = 0,
		.range = शून्य,
	पूर्ण,
	[AB8500_STE_TEST] = अणु
		.num_ranges = 0,
		.range = शून्य,
	पूर्ण,
	[AB8500_OTP_EMUL] = अणु
		.num_ranges = 1,
		.range = (काष्ठा ab8500_reg_range[]) अणु
			अणु
				.first = 0x01,
				.last = 0x15,
			पूर्ण,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा ab8500_prcmu_ranges ab8540_debug_ranges[AB8500_NUM_BANKS] = अणु
	[AB8500_M_FSM_RANK] = अणु
		.num_ranges = 1,
		.range = (काष्ठा ab8500_reg_range[]) अणु
			अणु
				.first = 0x00,
				.last = 0x0B,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[AB8500_SYS_CTRL1_BLOCK] = अणु
		.num_ranges = 6,
		.range = (काष्ठा ab8500_reg_range[]) अणु
			अणु
				.first = 0x00,
				.last = 0x04,
			पूर्ण,
			अणु
				.first = 0x42,
				.last = 0x42,
			पूर्ण,
			अणु
				.first = 0x50,
				.last = 0x54,
			पूर्ण,
			अणु
				.first = 0x57,
				.last = 0x57,
			पूर्ण,
			अणु
				.first = 0x80,
				.last = 0x83,
			पूर्ण,
			अणु
				.first = 0x90,
				.last = 0x90,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[AB8500_SYS_CTRL2_BLOCK] = अणु
		.num_ranges = 5,
		.range = (काष्ठा ab8500_reg_range[]) अणु
			अणु
				.first = 0x00,
				.last = 0x0D,
			पूर्ण,
			अणु
				.first = 0x0F,
				.last = 0x10,
			पूर्ण,
			अणु
				.first = 0x20,
				.last = 0x21,
			पूर्ण,
			अणु
				.first = 0x32,
				.last = 0x3C,
			पूर्ण,
			अणु
				.first = 0x40,
				.last = 0x42,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[AB8500_REGU_CTRL1] = अणु
		.num_ranges = 4,
		.range = (काष्ठा ab8500_reg_range[]) अणु
			अणु
				.first = 0x03,
				.last = 0x15,
			पूर्ण,
			अणु
				.first = 0x20,
				.last = 0x20,
			पूर्ण,
			अणु
				.first = 0x80,
				.last = 0x85,
			पूर्ण,
			अणु
				.first = 0x87,
				.last = 0x88,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[AB8500_REGU_CTRL2] = अणु
		.num_ranges = 8,
		.range = (काष्ठा ab8500_reg_range[]) अणु
			अणु
				.first = 0x00,
				.last = 0x06,
			पूर्ण,
			अणु
				.first = 0x08,
				.last = 0x15,
			पूर्ण,
			अणु
				.first = 0x17,
				.last = 0x19,
			पूर्ण,
			अणु
				.first = 0x1B,
				.last = 0x1D,
			पूर्ण,
			अणु
				.first = 0x1F,
				.last = 0x2F,
			पूर्ण,
			अणु
				.first = 0x31,
				.last = 0x3A,
			पूर्ण,
			अणु
				.first = 0x43,
				.last = 0x44,
			पूर्ण,
			अणु
				.first = 0x48,
				.last = 0x49,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[AB8500_USB] = अणु
		.num_ranges = 3,
		.range = (काष्ठा ab8500_reg_range[]) अणु
			अणु
				.first = 0x80,
				.last = 0x83,
			पूर्ण,
			अणु
				.first = 0x87,
				.last = 0x8A,
			पूर्ण,
			अणु
				.first = 0x91,
				.last = 0x94,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[AB8500_TVOUT] = अणु
		.num_ranges = 0,
		.range = शून्य
	पूर्ण,
	[AB8500_DBI] = अणु
		.num_ranges = 4,
		.range = (काष्ठा ab8500_reg_range[]) अणु
			अणु
				.first = 0x00,
				.last = 0x07,
			पूर्ण,
			अणु
				.first = 0x10,
				.last = 0x11,
			पूर्ण,
			अणु
				.first = 0x20,
				.last = 0x21,
			पूर्ण,
			अणु
				.first = 0x30,
				.last = 0x43,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[AB8500_ECI_AV_ACC] = अणु
		.num_ranges = 2,
		.range = (काष्ठा ab8500_reg_range[]) अणु
			अणु
				.first = 0x00,
				.last = 0x03,
			पूर्ण,
			अणु
				.first = 0x80,
				.last = 0x82,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[AB8500_RESERVED] = अणु
		.num_ranges = 0,
		.range = शून्य,
	पूर्ण,
	[AB8500_GPADC] = अणु
		.num_ranges = 4,
		.range = (काष्ठा ab8500_reg_range[]) अणु
			अणु
				.first = 0x00,
				.last = 0x01,
			पूर्ण,
			अणु
				.first = 0x04,
				.last = 0x06,
			पूर्ण,
			अणु
				.first = 0x09,
				.last = 0x0A,
			पूर्ण,
			अणु
				.first = 0x10,
				.last = 0x14,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[AB8500_CHARGER] = अणु
		.num_ranges = 10,
		.range = (काष्ठा ab8500_reg_range[]) अणु
			अणु
				.first = 0x00,
				.last = 0x00,
			पूर्ण,
			अणु
				.first = 0x02,
				.last = 0x05,
			पूर्ण,
			अणु
				.first = 0x40,
				.last = 0x44,
			पूर्ण,
			अणु
				.first = 0x50,
				.last = 0x57,
			पूर्ण,
			अणु
				.first = 0x60,
				.last = 0x60,
			पूर्ण,
			अणु
				.first = 0x70,
				.last = 0x70,
			पूर्ण,
			अणु
				.first = 0xA0,
				.last = 0xA9,
			पूर्ण,
			अणु
				.first = 0xAF,
				.last = 0xB2,
			पूर्ण,
			अणु
				.first = 0xC0,
				.last = 0xC6,
			पूर्ण,
			अणु
				.first = 0xF5,
				.last = 0xF5,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[AB8500_GAS_GAUGE] = अणु
		.num_ranges = 3,
		.range = (काष्ठा ab8500_reg_range[]) अणु
			अणु
				.first = 0x00,
				.last = 0x00,
			पूर्ण,
			अणु
				.first = 0x07,
				.last = 0x0A,
			पूर्ण,
			अणु
				.first = 0x10,
				.last = 0x14,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[AB8500_AUDIO] = अणु
		.num_ranges = 1,
		.range = (काष्ठा ab8500_reg_range[]) अणु
			अणु
				.first = 0x00,
				.last = 0x9f,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[AB8500_INTERRUPT] = अणु
		.num_ranges = 6,
		.range = (काष्ठा ab8500_reg_range[]) अणु
			अणु
				.first = 0x00,
				.last = 0x05,
			पूर्ण,
			अणु
				.first = 0x0B,
				.last = 0x0D,
			पूर्ण,
			अणु
				.first = 0x12,
				.last = 0x20,
			पूर्ण,
			/* Latch रेजिस्टरs should not be पढ़ो here */
			अणु
				.first = 0x40,
				.last = 0x45,
			पूर्ण,
			अणु
				.first = 0x4B,
				.last = 0x4D,
			पूर्ण,
			अणु
				.first = 0x52,
				.last = 0x60,
			पूर्ण,
			/* LatchHier रेजिस्टरs should not be पढ़ो here */
		पूर्ण,
	पूर्ण,
	[AB8500_RTC] = अणु
		.num_ranges = 3,
		.range = (काष्ठा ab8500_reg_range[]) अणु
			अणु
				.first = 0x00,
				.last = 0x07,
			पूर्ण,
			अणु
				.first = 0x0B,
				.last = 0x18,
			पूर्ण,
			अणु
				.first = 0x20,
				.last = 0x25,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[AB8500_MISC] = अणु
		.num_ranges = 9,
		.range = (काष्ठा ab8500_reg_range[]) अणु
			अणु
				.first = 0x00,
				.last = 0x06,
			पूर्ण,
			अणु
				.first = 0x10,
				.last = 0x16,
			पूर्ण,
			अणु
				.first = 0x20,
				.last = 0x26,
			पूर्ण,
			अणु
				.first = 0x30,
				.last = 0x36,
			पूर्ण,
			अणु
				.first = 0x40,
				.last = 0x49,
			पूर्ण,
			अणु
				.first = 0x50,
				.last = 0x50,
			पूर्ण,
			अणु
				.first = 0x60,
				.last = 0x6B,
			पूर्ण,
			अणु
				.first = 0x70,
				.last = 0x74,
			पूर्ण,
			अणु
				.first = 0x80,
				.last = 0x82,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[AB8500_DEVELOPMENT] = अणु
		.num_ranges = 3,
		.range = (काष्ठा ab8500_reg_range[]) अणु
			अणु
				.first = 0x00,
				.last = 0x01,
			पूर्ण,
			अणु
				.first = 0x06,
				.last = 0x06,
			पूर्ण,
			अणु
				.first = 0x10,
				.last = 0x21,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[AB8500_DEBUG] = अणु
		.num_ranges = 3,
		.range = (काष्ठा ab8500_reg_range[]) अणु
			अणु
				.first = 0x01,
				.last = 0x0C,
			पूर्ण,
			अणु
				.first = 0x0E,
				.last = 0x11,
			पूर्ण,
			अणु
				.first = 0x80,
				.last = 0x81,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[AB8500_PROD_TEST] = अणु
		.num_ranges = 0,
		.range = शून्य,
	पूर्ण,
	[AB8500_STE_TEST] = अणु
		.num_ranges = 0,
		.range = शून्य,
	पूर्ण,
	[AB8500_OTP_EMUL] = अणु
		.num_ranges = 1,
		.range = (काष्ठा ab8500_reg_range[]) अणु
			अणु
				.first = 0x00,
				.last = 0x3F,
			पूर्ण,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल irqवापस_t ab8500_debug_handler(पूर्णांक irq, व्योम *data)
अणु
	अक्षर buf[16];
	काष्ठा kobject *kobj = (काष्ठा kobject *)data;
	अचिन्हित पूर्णांक irq_abb = irq - irq_first;

	अगर (irq_abb < num_irqs)
		irq_count[irq_abb]++;
	/*
	 * This makes it possible to use poll क्रम events (EPOLLPRI | EPOLLERR)
	 * from userspace on sysfs file named <irq-nr>
	 */
	प्र_लिखो(buf, "%d", irq);
	sysfs_notअगरy(kobj, शून्य, buf);

	वापस IRQ_HANDLED;
पूर्ण

/* Prपूर्णांकs to seq_file or log_buf */
अटल पूर्णांक ab8500_रेजिस्टरs_prपूर्णांक(काष्ठा device *dev, u32 bank,
				  काष्ठा seq_file *s)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < debug_ranges[bank].num_ranges; i++) अणु
		u32 reg;

		क्रम (reg = debug_ranges[bank].range[i].first;
			reg <= debug_ranges[bank].range[i].last;
			reg++) अणु
			u8 value;
			पूर्णांक err;

			err = abx500_get_रेजिस्टर_पूर्णांकerruptible(dev,
				(u8)bank, (u8)reg, &value);
			अगर (err < 0) अणु
				dev_err(dev, "ab->read fail %d\n", err);
				वापस err;
			पूर्ण

			अगर (s) अणु
				seq_म_लिखो(s, "  [0x%02X/0x%02X]: 0x%02X\n",
					   bank, reg, value);
				/*
				 * Error is not वापसed here since
				 * the output is wanted in any हाल
				 */
				अगर (seq_has_overflowed(s))
					वापस 0;
			पूर्ण अन्यथा अणु
				dev_info(dev, " [0x%02X/0x%02X]: 0x%02X\n",
					 bank, reg, value);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ab8500_bank_रेजिस्टरs_show(काष्ठा seq_file *s, व्योम *p)
अणु
	काष्ठा device *dev = s->निजी;
	u32 bank = debug_bank;

	seq_माला_दो(s, AB8500_NAME_STRING " register values:\n");

	seq_म_लिखो(s, " bank 0x%02X:\n", bank);

	वापस ab8500_रेजिस्टरs_prपूर्णांक(dev, bank, s);
पूर्ण

DEFINE_SHOW_ATTRIBUTE(ab8500_bank_रेजिस्टरs);

अटल पूर्णांक ab8500_prपूर्णांक_all_banks(काष्ठा seq_file *s, व्योम *p)
अणु
	काष्ठा device *dev = s->निजी;
	अचिन्हित पूर्णांक i;

	seq_माला_दो(s, AB8500_NAME_STRING " register values:\n");

	क्रम (i = 0; i < AB8500_NUM_BANKS; i++) अणु
		पूर्णांक err;

		seq_म_लिखो(s, " bank 0x%02X:\n", i);
		err = ab8500_रेजिस्टरs_prपूर्णांक(dev, i, s);
		अगर (err)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

/* Dump रेजिस्टरs to kernel log */
व्योम ab8500_dump_all_banks(काष्ठा device *dev)
अणु
	अचिन्हित पूर्णांक i;

	dev_info(dev, "ab8500 register values:\n");

	क्रम (i = 1; i < AB8500_NUM_BANKS; i++) अणु
		dev_info(dev, " bank 0x%02X:\n", i);
		ab8500_रेजिस्टरs_prपूर्णांक(dev, i, शून्य);
	पूर्ण
पूर्ण

अटल पूर्णांक ab8500_all_banks_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा seq_file *s;
	पूर्णांक err;

	err = single_खोलो(file, ab8500_prपूर्णांक_all_banks, inode->i_निजी);
	अगर (!err) अणु
		/* Default buf size in seq_पढ़ो is not enough */
		s = (काष्ठा seq_file *)file->निजी_data;
		s->size = (PAGE_SIZE * 2);
		s->buf = kदो_स्मृति(s->size, GFP_KERNEL);
		अगर (!s->buf) अणु
			single_release(inode, file);
			err = -ENOMEM;
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

अटल स्थिर काष्ठा file_operations ab8500_all_banks_fops = अणु
	.खोलो = ab8500_all_banks_खोलो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = single_release,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक ab8500_bank_prपूर्णांक(काष्ठा seq_file *s, व्योम *p)
अणु
	seq_म_लिखो(s, "0x%02X\n", debug_bank);
	वापस 0;
पूर्ण

अटल पूर्णांक ab8500_bank_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, ab8500_bank_prपूर्णांक, inode->i_निजी);
पूर्ण

अटल sमाप_प्रकार ab8500_bank_ग_लिखो(काष्ठा file *file,
	स्थिर अक्षर __user *user_buf,
	माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा device *dev = ((काष्ठा seq_file *)(file->निजी_data))->निजी;
	अचिन्हित दीर्घ user_bank;
	पूर्णांक err;

	err = kम_से_अदीर्घ_from_user(user_buf, count, 0, &user_bank);
	अगर (err)
		वापस err;

	अगर (user_bank >= AB8500_NUM_BANKS) अणु
		dev_err(dev, "debugfs error input > number of banks\n");
		वापस -EINVAL;
	पूर्ण

	debug_bank = user_bank;

	वापस count;
पूर्ण

अटल पूर्णांक ab8500_address_prपूर्णांक(काष्ठा seq_file *s, व्योम *p)
अणु
	seq_म_लिखो(s, "0x%02X\n", debug_address);
	वापस 0;
पूर्ण

अटल पूर्णांक ab8500_address_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, ab8500_address_prपूर्णांक, inode->i_निजी);
पूर्ण

अटल sमाप_प्रकार ab8500_address_ग_लिखो(काष्ठा file *file,
				    स्थिर अक्षर __user *user_buf,
				    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा device *dev = ((काष्ठा seq_file *)(file->निजी_data))->निजी;
	अचिन्हित दीर्घ user_address;
	पूर्णांक err;

	err = kम_से_अदीर्घ_from_user(user_buf, count, 0, &user_address);
	अगर (err)
		वापस err;

	अगर (user_address > 0xff) अणु
		dev_err(dev, "debugfs error input > 0xff\n");
		वापस -EINVAL;
	पूर्ण
	debug_address = user_address;

	वापस count;
पूर्ण

अटल पूर्णांक ab8500_val_prपूर्णांक(काष्ठा seq_file *s, व्योम *p)
अणु
	काष्ठा device *dev = s->निजी;
	पूर्णांक ret;
	u8 regvalue;

	ret = abx500_get_रेजिस्टर_पूर्णांकerruptible(dev,
		(u8)debug_bank, (u8)debug_address, &regvalue);
	अगर (ret < 0) अणु
		dev_err(dev, "abx500_get_reg fail %d, %d\n",
			ret, __LINE__);
		वापस -EINVAL;
	पूर्ण
	seq_म_लिखो(s, "0x%02X\n", regvalue);

	वापस 0;
पूर्ण

अटल पूर्णांक ab8500_val_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, ab8500_val_prपूर्णांक, inode->i_निजी);
पूर्ण

अटल sमाप_प्रकार ab8500_val_ग_लिखो(काष्ठा file *file,
				स्थिर अक्षर __user *user_buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा device *dev = ((काष्ठा seq_file *)(file->निजी_data))->निजी;
	अचिन्हित दीर्घ user_val;
	पूर्णांक err;

	err = kम_से_अदीर्घ_from_user(user_buf, count, 0, &user_val);
	अगर (err)
		वापस err;

	अगर (user_val > 0xff) अणु
		dev_err(dev, "debugfs error input > 0xff\n");
		वापस -EINVAL;
	पूर्ण
	err = abx500_set_रेजिस्टर_पूर्णांकerruptible(dev,
		(u8)debug_bank, debug_address, (u8)user_val);
	अगर (err < 0) अणु
		pr_err("abx500_set_reg failed %d, %d", err, __LINE__);
		वापस -EINVAL;
	पूर्ण

	वापस count;
पूर्ण

/*
 * Interrupt status
 */
अटल u32 num_पूर्णांकerrupts[AB8500_MAX_NR_IRQS];
अटल u32 num_wake_पूर्णांकerrupts[AB8500_MAX_NR_IRQS];
अटल पूर्णांक num_पूर्णांकerrupt_lines;

व्योम ab8500_debug_रेजिस्टर_पूर्णांकerrupt(पूर्णांक line)
अणु
	अगर (line < num_पूर्णांकerrupt_lines)
		num_पूर्णांकerrupts[line]++;
पूर्ण

अटल पूर्णांक ab8500_पूर्णांकerrupts_show(काष्ठा seq_file *s, व्योम *p)
अणु
	पूर्णांक line;

	seq_माला_दो(s, "name: number: irq: number of: wake:\n");

	क्रम (line = 0; line < num_पूर्णांकerrupt_lines; line++) अणु
		seq_म_लिखो(s, "%3i:  %4i %6i %4i\n",
			   line,
			   line + irq_first,
			   num_पूर्णांकerrupts[line],
			   num_wake_पूर्णांकerrupts[line]);
	पूर्ण

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(ab8500_पूर्णांकerrupts);

/*
 * - HWREG DB8500 क्रमmated routines
 */
अटल पूर्णांक ab8500_hwreg_prपूर्णांक(काष्ठा seq_file *s, व्योम *d)
अणु
	काष्ठा device *dev = s->निजी;
	पूर्णांक ret;
	u8 regvalue;

	ret = abx500_get_रेजिस्टर_पूर्णांकerruptible(dev,
		(u8)hwreg_cfg.bank, (u8)hwreg_cfg.addr, &regvalue);
	अगर (ret < 0) अणु
		dev_err(dev, "abx500_get_reg fail %d, %d\n",
			ret, __LINE__);
		वापस -EINVAL;
	पूर्ण

	अगर (hwreg_cfg.shअगरt >= 0)
		regvalue >>= hwreg_cfg.shअगरt;
	अन्यथा
		regvalue <<= -hwreg_cfg.shअगरt;
	regvalue &= hwreg_cfg.mask;

	अगर (REG_FMT_DEC(&hwreg_cfg))
		seq_म_लिखो(s, "%d\n", regvalue);
	अन्यथा
		seq_म_लिखो(s, "0x%02X\n", regvalue);
	वापस 0;
पूर्ण

अटल पूर्णांक ab8500_hwreg_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, ab8500_hwreg_prपूर्णांक, inode->i_निजी);
पूर्ण

#घोषणा AB8500_SUPPLY_CONTROL_CONFIG_1 0x01
#घोषणा AB8500_SUPPLY_CONTROL_REG 0x00
#घोषणा AB8500_FIRST_SIM_REG 0x80
#घोषणा AB8500_LAST_SIM_REG 0x8B
#घोषणा AB8505_LAST_SIM_REG 0x8C

अटल पूर्णांक ab8500_modem_show(काष्ठा seq_file *s, व्योम *p)
अणु
	काष्ठा device *dev = s->निजी;
	काष्ठा ab8500 *ab8500;
	पूर्णांक err;
	u8 value;
	u8 orig_value;
	u32 bank = AB8500_REGU_CTRL2;
	u32 last_sim_reg = AB8500_LAST_SIM_REG;
	u32 reg;

	ab8500 = dev_get_drvdata(dev->parent);
	dev_warn(dev, "WARNING! This operation can interfer with modem side\n"
		"and should only be done with care\n");

	err = abx500_get_रेजिस्टर_पूर्णांकerruptible(dev,
		AB8500_REGU_CTRL1, AB8500_SUPPLY_CONTROL_REG, &orig_value);
	अगर (err < 0)
		जाओ report_पढ़ो_failure;

	/* Config 1 will allow APE side to पढ़ो SIM रेजिस्टरs */
	err = abx500_set_रेजिस्टर_पूर्णांकerruptible(dev,
		AB8500_REGU_CTRL1, AB8500_SUPPLY_CONTROL_REG,
		AB8500_SUPPLY_CONTROL_CONFIG_1);
	अगर (err < 0)
		जाओ report_ग_लिखो_failure;

	seq_म_लिखो(s, " bank 0x%02X:\n", bank);

	अगर (is_ab9540(ab8500) || is_ab8505(ab8500))
		last_sim_reg = AB8505_LAST_SIM_REG;

	क्रम (reg = AB8500_FIRST_SIM_REG; reg <= last_sim_reg; reg++) अणु
		err = abx500_get_रेजिस्टर_पूर्णांकerruptible(dev,
			bank, reg, &value);
		अगर (err < 0)
			जाओ report_पढ़ो_failure;

		seq_म_लिखो(s, "  [0x%02X/0x%02X]: 0x%02X\n", bank, reg, value);
	पूर्ण
	err = abx500_set_रेजिस्टर_पूर्णांकerruptible(dev,
		AB8500_REGU_CTRL1, AB8500_SUPPLY_CONTROL_REG, orig_value);
	अगर (err < 0)
		जाओ report_ग_लिखो_failure;

	वापस 0;

report_पढ़ो_failure:
	dev_err(dev, "ab->read fail %d\n", err);
	वापस err;

report_ग_लिखो_failure:
	dev_err(dev, "ab->write fail %d\n", err);
	वापस err;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(ab8500_modem);

/*
 * वापस length of an ASCII numerical value, 0 is string is not a
 * numerical value.
 * string shall start at value 1st अक्षर.
 * string can be tailed with \0 or space or newline अक्षरs only.
 * value can be decimal or hexadecimal (prefixed 0x or 0X).
 */
अटल पूर्णांक strval_len(अक्षर *b)
अणु
	अक्षर *s = b;

	अगर ((*s == '0') && ((*(s+1) == 'x') || (*(s+1) == 'X'))) अणु
		s += 2;
		क्रम (; *s && (*s != ' ') && (*s != '\n'); s++) अणु
			अगर (!है_षष्ठादशक(*s))
				वापस 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (*s == '-')
			s++;
		क्रम (; *s && (*s != ' ') && (*s != '\n'); s++) अणु
			अगर (!है_अंक(*s))
				वापस 0;
		पूर्ण
	पूर्ण
	वापस (पूर्णांक) (s-b);
पूर्ण

/*
 * parse hwreg input data.
 * update global hwreg_cfg only अगर input data syntax is ok.
 */
अटल sमाप_प्रकार hwreg_common_ग_लिखो(अक्षर *b, काष्ठा hwreg_cfg *cfg,
		काष्ठा device *dev)
अणु
	uपूर्णांक ग_लिखो, val = 0;
	u8  regvalue;
	पूर्णांक ret;
	काष्ठा hwreg_cfg loc = अणु
		.bank = 0,          /* शेष: invalid phys addr */
		.addr = 0,          /* शेष: invalid phys addr */
		.fmt = 0,           /* शेष: 32bit access, hex output */
		.mask = 0xFFFFFFFF, /* शेष: no mask */
		.shअगरt = 0,         /* शेष: no bit shअगरt */
	पूर्ण;

	/* पढ़ो or ग_लिखो ? */
	अगर (!म_भेदन(b, "read ", 5)) अणु
		ग_लिखो = 0;
		b += 5;
	पूर्ण अन्यथा अगर (!म_भेदन(b, "write ", 6)) अणु
		ग_लिखो = 1;
		b += 6;
	पूर्ण अन्यथा
		वापस -EINVAL;

	/* OPTIONS -l|-w|-b -s -m -o */
	जबतक ((*b == ' ') || (*b == '-')) अणु
		अगर (*(b-1) != ' ') अणु
			b++;
			जारी;
		पूर्ण
		अगर ((!म_भेदन(b, "-d ", 3)) ||
				(!म_भेदन(b, "-dec ", 5))) अणु
			b += (*(b+2) == ' ') ? 3 : 5;
			loc.fmt |= (1<<0);
		पूर्ण अन्यथा अगर ((!म_भेदन(b, "-h ", 3)) ||
				(!म_भेदन(b, "-hex ", 5))) अणु
			b += (*(b+2) == ' ') ? 3 : 5;
			loc.fmt &= ~(1<<0);
		पूर्ण अन्यथा अगर ((!म_भेदन(b, "-m ", 3)) ||
				(!म_भेदन(b, "-mask ", 6))) अणु
			b += (*(b+2) == ' ') ? 3 : 6;
			अगर (strval_len(b) == 0)
				वापस -EINVAL;
			ret = kम_से_अदीर्घ(b, 0, &loc.mask);
			अगर (ret)
				वापस ret;
		पूर्ण अन्यथा अगर ((!म_भेदन(b, "-s ", 3)) ||
				(!म_भेदन(b, "-shift ", 7))) अणु
			b += (*(b+2) == ' ') ? 3 : 7;
			अगर (strval_len(b) == 0)
				वापस -EINVAL;
			ret = kम_से_दीर्घ(b, 0, &loc.shअगरt);
			अगर (ret)
				वापस ret;
		पूर्ण अन्यथा अणु
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	/* get arg BANK and ADDRESS */
	अगर (strval_len(b) == 0)
		वापस -EINVAL;
	ret = kstrtouपूर्णांक(b, 0, &loc.bank);
	अगर (ret)
		वापस ret;
	जबतक (*b == ' ')
		b++;
	अगर (strval_len(b) == 0)
		वापस -EINVAL;
	ret = kम_से_अदीर्घ(b, 0, &loc.addr);
	अगर (ret)
		वापस ret;

	अगर (ग_लिखो) अणु
		जबतक (*b == ' ')
			b++;
		अगर (strval_len(b) == 0)
			वापस -EINVAL;
		ret = kstrtouपूर्णांक(b, 0, &val);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* args are ok, update target cfg (मुख्यly क्रम पढ़ो) */
	*cfg = loc;

#अगर_घोषित ABB_HWREG_DEBUG
	pr_warn("HWREG request: %s, %s,\n", (ग_लिखो) ? "write" : "read",
		REG_FMT_DEC(cfg) ? "decimal" : "hexa");
	pr_warn("  addr=0x%08X, mask=0x%X, shift=%d" "value=0x%X\n",
		cfg->addr, cfg->mask, cfg->shअगरt, val);
#पूर्ण_अगर

	अगर (!ग_लिखो)
		वापस 0;

	ret = abx500_get_रेजिस्टर_पूर्णांकerruptible(dev,
			(u8)cfg->bank, (u8)cfg->addr, &regvalue);
	अगर (ret < 0) अणु
		dev_err(dev, "abx500_get_reg fail %d, %d\n",
			ret, __LINE__);
		वापस -EINVAL;
	पूर्ण

	अगर (cfg->shअगरt >= 0) अणु
		regvalue &= ~(cfg->mask << (cfg->shअगरt));
		val = (val & cfg->mask) << (cfg->shअगरt);
	पूर्ण अन्यथा अणु
		regvalue &= ~(cfg->mask >> (-cfg->shअगरt));
		val = (val & cfg->mask) >> (-cfg->shअगरt);
	पूर्ण
	val = val | regvalue;

	ret = abx500_set_रेजिस्टर_पूर्णांकerruptible(dev,
			(u8)cfg->bank, (u8)cfg->addr, (u8)val);
	अगर (ret < 0) अणु
		pr_err("abx500_set_reg failed %d, %d", ret, __LINE__);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार ab8500_hwreg_ग_लिखो(काष्ठा file *file,
	स्थिर अक्षर __user *user_buf, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा device *dev = ((काष्ठा seq_file *)(file->निजी_data))->निजी;
	अक्षर buf[128];
	पूर्णांक buf_size, ret;

	/* Get userspace string and assure termination */
	buf_size = min((पूर्णांक)count, (पूर्णांक)(माप(buf)-1));
	अगर (copy_from_user(buf, user_buf, buf_size))
		वापस -EFAULT;
	buf[buf_size] = 0;

	/* get args and process */
	ret = hwreg_common_ग_लिखो(buf, &hwreg_cfg, dev);
	वापस (ret) ? ret : buf_size;
पूर्ण

/*
 * - irq subscribe/unsubscribe stuff
 */
अटल पूर्णांक ab8500_subscribe_unsubscribe_prपूर्णांक(काष्ठा seq_file *s, व्योम *p)
अणु
	seq_म_लिखो(s, "%d\n", irq_first);

	वापस 0;
पूर्ण

अटल पूर्णांक ab8500_subscribe_unsubscribe_खोलो(काष्ठा inode *inode,
					     काष्ठा file *file)
अणु
	वापस single_खोलो(file, ab8500_subscribe_unsubscribe_prपूर्णांक,
		inode->i_निजी);
पूर्ण

/*
 * Userspace should use poll() on this file. When an event occur
 * the blocking poll will be released.
 */
अटल sमाप_प्रकार show_irq(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अचिन्हित दीर्घ name;
	अचिन्हित पूर्णांक irq_index;
	पूर्णांक err;

	err = kम_से_अदीर्घ(attr->attr.name, 0, &name);
	अगर (err)
		वापस err;

	irq_index = name - irq_first;
	अगर (irq_index >= num_irqs)
		वापस -EINVAL;

	वापस प्र_लिखो(buf, "%u\n", irq_count[irq_index]);
पूर्ण

अटल sमाप_प्रकार ab8500_subscribe_ग_लिखो(काष्ठा file *file,
				      स्थिर अक्षर __user *user_buf,
				      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा device *dev = ((काष्ठा seq_file *)(file->निजी_data))->निजी;
	अचिन्हित दीर्घ user_val;
	पूर्णांक err;
	अचिन्हित पूर्णांक irq_index;

	err = kम_से_अदीर्घ_from_user(user_buf, count, 0, &user_val);
	अगर (err)
		वापस err;

	अगर (user_val < irq_first) अणु
		dev_err(dev, "debugfs error input < %d\n", irq_first);
		वापस -EINVAL;
	पूर्ण
	अगर (user_val > irq_last) अणु
		dev_err(dev, "debugfs error input > %d\n", irq_last);
		वापस -EINVAL;
	पूर्ण

	irq_index = user_val - irq_first;
	अगर (irq_index >= num_irqs)
		वापस -EINVAL;

	/*
	 * This will create a sysfs file named <irq-nr> which userspace can
	 * use to select or poll and get the AB8500 events
	 */
	dev_attr[irq_index] = kदो_स्मृति(माप(काष्ठा device_attribute),
		GFP_KERNEL);
	अगर (!dev_attr[irq_index])
		वापस -ENOMEM;

	event_name[irq_index] = kaप्र_लिखो(GFP_KERNEL, "%lu", user_val);
	अगर (!event_name[irq_index])
		वापस -ENOMEM;

	dev_attr[irq_index]->show = show_irq;
	dev_attr[irq_index]->store = शून्य;
	dev_attr[irq_index]->attr.name = event_name[irq_index];
	dev_attr[irq_index]->attr.mode = S_IRUGO;
	err = sysfs_create_file(&dev->kobj, &dev_attr[irq_index]->attr);
	अगर (err < 0) अणु
		pr_info("sysfs_create_file failed %d\n", err);
		वापस err;
	पूर्ण

	err = request_thपढ़ोed_irq(user_val, शून्य, ab8500_debug_handler,
				   IRQF_SHARED | IRQF_NO_SUSPEND | IRQF_ONESHOT,
				   "ab8500-debug", &dev->kobj);
	अगर (err < 0) अणु
		pr_info("request_threaded_irq failed %d, %lu\n",
			err, user_val);
		sysfs_हटाओ_file(&dev->kobj, &dev_attr[irq_index]->attr);
		वापस err;
	पूर्ण

	वापस count;
पूर्ण

अटल sमाप_प्रकार ab8500_unsubscribe_ग_लिखो(काष्ठा file *file,
					स्थिर अक्षर __user *user_buf,
					माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा device *dev = ((काष्ठा seq_file *)(file->निजी_data))->निजी;
	अचिन्हित दीर्घ user_val;
	पूर्णांक err;
	अचिन्हित पूर्णांक irq_index;

	err = kम_से_अदीर्घ_from_user(user_buf, count, 0, &user_val);
	अगर (err)
		वापस err;

	अगर (user_val < irq_first) अणु
		dev_err(dev, "debugfs error input < %d\n", irq_first);
		वापस -EINVAL;
	पूर्ण
	अगर (user_val > irq_last) अणु
		dev_err(dev, "debugfs error input > %d\n", irq_last);
		वापस -EINVAL;
	पूर्ण

	irq_index = user_val - irq_first;
	अगर (irq_index >= num_irqs)
		वापस -EINVAL;

	/* Set irq count to 0 when unsubscribe */
	irq_count[irq_index] = 0;

	अगर (dev_attr[irq_index])
		sysfs_हटाओ_file(&dev->kobj, &dev_attr[irq_index]->attr);


	मुक्त_irq(user_val, &dev->kobj);
	kमुक्त(event_name[irq_index]);
	kमुक्त(dev_attr[irq_index]);

	वापस count;
पूर्ण

/*
 * - several debugfs nodes fops
 */

अटल स्थिर काष्ठा file_operations ab8500_bank_fops = अणु
	.खोलो = ab8500_bank_खोलो,
	.ग_लिखो = ab8500_bank_ग_लिखो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = single_release,
	.owner = THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा file_operations ab8500_address_fops = अणु
	.खोलो = ab8500_address_खोलो,
	.ग_लिखो = ab8500_address_ग_लिखो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = single_release,
	.owner = THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा file_operations ab8500_val_fops = अणु
	.खोलो = ab8500_val_खोलो,
	.ग_लिखो = ab8500_val_ग_लिखो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = single_release,
	.owner = THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा file_operations ab8500_subscribe_fops = अणु
	.खोलो = ab8500_subscribe_unsubscribe_खोलो,
	.ग_लिखो = ab8500_subscribe_ग_लिखो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = single_release,
	.owner = THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा file_operations ab8500_unsubscribe_fops = अणु
	.खोलो = ab8500_subscribe_unsubscribe_खोलो,
	.ग_लिखो = ab8500_unsubscribe_ग_लिखो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = single_release,
	.owner = THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा file_operations ab8500_hwreg_fops = अणु
	.खोलो = ab8500_hwreg_खोलो,
	.ग_लिखो = ab8500_hwreg_ग_लिखो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = single_release,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक ab8500_debug_probe(काष्ठा platक्रमm_device *plf)
अणु
	काष्ठा dentry *ab8500_dir;
	काष्ठा ab8500 *ab8500;
	काष्ठा resource *res;

	debug_bank = AB8500_MISC;
	debug_address = AB8500_REV_REG & 0x00FF;

	ab8500 = dev_get_drvdata(plf->dev.parent);
	num_irqs = ab8500->mask_size;

	irq_count = devm_kसुस्मृति(&plf->dev,
				 num_irqs, माप(*irq_count), GFP_KERNEL);
	अगर (!irq_count)
		वापस -ENOMEM;

	dev_attr = devm_kसुस्मृति(&plf->dev,
				num_irqs, माप(*dev_attr), GFP_KERNEL);
	अगर (!dev_attr)
		वापस -ENOMEM;

	event_name = devm_kसुस्मृति(&plf->dev,
				  num_irqs, माप(*event_name), GFP_KERNEL);
	अगर (!event_name)
		वापस -ENOMEM;

	res = platक्रमm_get_resource_byname(plf, 0, "IRQ_AB8500");
	अगर (!res) अणु
		dev_err(&plf->dev, "AB8500 irq not found, err %d\n", irq_first);
		वापस -ENXIO;
	पूर्ण
	irq_ab8500 = res->start;

	irq_first = platक्रमm_get_irq_byname(plf, "IRQ_FIRST");
	अगर (irq_first < 0)
		वापस irq_first;

	irq_last = platक्रमm_get_irq_byname(plf, "IRQ_LAST");
	अगर (irq_last < 0)
		वापस irq_last;

	ab8500_dir = debugfs_create_dir(AB8500_NAME_STRING, शून्य);

	debugfs_create_file("all-bank-registers", S_IRUGO, ab8500_dir,
			    &plf->dev, &ab8500_bank_रेजिस्टरs_fops);
	debugfs_create_file("all-banks", S_IRUGO, ab8500_dir,
			    &plf->dev, &ab8500_all_banks_fops);
	debugfs_create_file("register-bank", (S_IRUGO | S_IWUSR | S_IWGRP),
			    ab8500_dir, &plf->dev, &ab8500_bank_fops);
	debugfs_create_file("register-address", (S_IRUGO | S_IWUSR | S_IWGRP),
			    ab8500_dir, &plf->dev, &ab8500_address_fops);
	debugfs_create_file("register-value", (S_IRUGO | S_IWUSR | S_IWGRP),
			    ab8500_dir, &plf->dev, &ab8500_val_fops);
	debugfs_create_file("irq-subscribe", (S_IRUGO | S_IWUSR | S_IWGRP),
			    ab8500_dir, &plf->dev, &ab8500_subscribe_fops);

	अगर (is_ab8500(ab8500)) अणु
		debug_ranges = ab8500_debug_ranges;
		num_पूर्णांकerrupt_lines = AB8500_NR_IRQS;
	पूर्ण अन्यथा अगर (is_ab8505(ab8500)) अणु
		debug_ranges = ab8505_debug_ranges;
		num_पूर्णांकerrupt_lines = AB8505_NR_IRQS;
	पूर्ण अन्यथा अगर (is_ab9540(ab8500)) अणु
		debug_ranges = ab8505_debug_ranges;
		num_पूर्णांकerrupt_lines = AB9540_NR_IRQS;
	पूर्ण अन्यथा अगर (is_ab8540(ab8500)) अणु
		debug_ranges = ab8540_debug_ranges;
		num_पूर्णांकerrupt_lines = AB8540_NR_IRQS;
	पूर्ण

	debugfs_create_file("interrupts", (S_IRUGO), ab8500_dir, &plf->dev,
			    &ab8500_पूर्णांकerrupts_fops);
	debugfs_create_file("irq-unsubscribe", (S_IRUGO | S_IWUSR | S_IWGRP),
			    ab8500_dir, &plf->dev, &ab8500_unsubscribe_fops);
	debugfs_create_file("hwreg", (S_IRUGO | S_IWUSR | S_IWGRP), ab8500_dir,
			    &plf->dev, &ab8500_hwreg_fops);
	debugfs_create_file("all-modem-registers", (S_IRUGO | S_IWUSR | S_IWGRP),
			    ab8500_dir, &plf->dev, &ab8500_modem_fops);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ab8500_debug_driver = अणु
	.driver = अणु
		.name = "ab8500-debug",
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe  = ab8500_debug_probe,
पूर्ण;

अटल पूर्णांक __init ab8500_debug_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&ab8500_debug_driver);
पूर्ण
subsys_initcall(ab8500_debug_init);
