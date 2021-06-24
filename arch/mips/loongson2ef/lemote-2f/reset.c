<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Board-specअगरic reboot/shutकरोwn routines
 *
 * Copyright (c) 2009 Philippe Vachon <philippe@cowpig.ca>
 *
 * Copyright (C) 2009 Lemote Inc.
 * Author: Wu Zhangjin, wuzhangjin@gmail.com
 */

#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/bootinfo.h>

#समावेश <loongson.h>

#समावेश <cs5536/cs5536.h>
#समावेश "ec_kb3310b.h"

अटल व्योम reset_cpu(व्योम)
अणु
	/*
	 * reset cpu to full speed, this is needed when enabling cpu frequency
	 * scalling
	 */
	ग_लिखोl(पढ़ोl(LOONGSON_CHIPCFG) | 0x7, LOONGSON_CHIPCFG);
पूर्ण

/* reset support क्रम fuloong2f */

अटल व्योम fl2f_reboot(व्योम)
अणु
	reset_cpu();

	/* send a reset संकेत to south bridge.
	 *
	 * NOTE: अगर enable "Power Management" in kernel, rtl8169 will not reset
	 * normally with this reset operation and it will not work in PMON, but
	 * you can type halt command and then reboot, seems the hardware reset
	 * logic not work normally.
	 */
	अणु
		u32 hi, lo;
		_rdmsr(DIVIL_MSR_REG(DIVIL_SOFT_RESET), &hi, &lo);
		lo |= 0x00000001;
		_wrmsr(DIVIL_MSR_REG(DIVIL_SOFT_RESET), hi, lo);
	पूर्ण
पूर्ण

अटल व्योम fl2f_shutकरोwn(व्योम)
अणु
	u32 hi, lo, val;
	पूर्णांक gpio_base;

	/* get gpio base */
	_rdmsr(DIVIL_MSR_REG(DIVIL_LBAR_GPIO), &hi, &lo);
	gpio_base = lo & 0xff00;

	/* make cs5536 gpio13 output enable */
	val = inl(gpio_base + GPIOL_OUT_EN);
	val &= ~(1 << (16 + 13));
	val |= (1 << 13);
	outl(val, gpio_base + GPIOL_OUT_EN);
	mmiowb();
	/* make cs5536 gpio13 output low level voltage. */
	val = inl(gpio_base + GPIOL_OUT_VAL) & ~(1 << (13));
	val |= (1 << (16 + 13));
	outl(val, gpio_base + GPIOL_OUT_VAL);
	mmiowb();
पूर्ण

/* reset support क्रम yeeloong2f and mengloong2f notebook */

अटल व्योम ml2f_reboot(व्योम)
अणु
	reset_cpu();

	/* sending an reset संकेत to EC(embedded controller) */
	ec_ग_लिखो(REG_RESET, BIT_RESET_ON);
पूर्ण

#घोषणा yl2f89_reboot ml2f_reboot

/* mengदीर्घ(7inches) laptop has dअगरferent shutकरोwn logic from 8.9inches */
#घोषणा EC_SHUTDOWN_IO_PORT_HIGH 0xff2d
#घोषणा EC_SHUTDOWN_IO_PORT_LOW	 0xff2e
#घोषणा EC_SHUTDOWN_IO_PORT_DATA 0xff2f
#घोषणा REG_SHUTDOWN_HIGH	 0xFC
#घोषणा REG_SHUTDOWN_LOW	 0x29
#घोषणा BIT_SHUTDOWN_ON		 (1 << 1)

अटल व्योम ml2f_shutकरोwn(व्योम)
अणु
	u8 val;
	u64 i;

	outb(REG_SHUTDOWN_HIGH, EC_SHUTDOWN_IO_PORT_HIGH);
	outb(REG_SHUTDOWN_LOW, EC_SHUTDOWN_IO_PORT_LOW);
	mmiowb();
	val = inb(EC_SHUTDOWN_IO_PORT_DATA);
	outb(val & (~BIT_SHUTDOWN_ON), EC_SHUTDOWN_IO_PORT_DATA);
	mmiowb();
	/* need enough रुको here... how many microseconds needs? */
	क्रम (i = 0; i < 0x10000; i++)
		delay();
	outb(val | BIT_SHUTDOWN_ON, EC_SHUTDOWN_IO_PORT_DATA);
	mmiowb();
पूर्ण

अटल व्योम yl2f89_shutकरोwn(व्योम)
अणु
	/* cpu-gpio0 output low */
	LOONGSON_GPIODATA &= ~0x00000001;
	/* cpu-gpio0 as output */
	LOONGSON_GPIOIE &= ~0x00000001;
पूर्ण

व्योम mach_prepare_reboot(व्योम)
अणु
	चयन (mips_machtype) अणु
	हाल MACH_LEMOTE_FL2F:
	हाल MACH_LEMOTE_NAS:
	हाल MACH_LEMOTE_LL2F:
		fl2f_reboot();
		अवरोध;
	हाल MACH_LEMOTE_ML2F7:
		ml2f_reboot();
		अवरोध;
	हाल MACH_LEMOTE_YL2F89:
		yl2f89_reboot();
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

व्योम mach_prepare_shutकरोwn(व्योम)
अणु
	चयन (mips_machtype) अणु
	हाल MACH_LEMOTE_FL2F:
	हाल MACH_LEMOTE_NAS:
	हाल MACH_LEMOTE_LL2F:
		fl2f_shutकरोwn();
		अवरोध;
	हाल MACH_LEMOTE_ML2F7:
		ml2f_shutकरोwn();
		अवरोध;
	हाल MACH_LEMOTE_YL2F89:
		yl2f89_shutकरोwn();
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण
