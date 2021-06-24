<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/arch/m68k/sun3x/समय.c
 *
 *  Sun3x-specअगरic समय handling
 */

#समावेश <linux/types.h>
#समावेश <linux/kd.h>
#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/rtc.h>
#समावेश <linux/bcd.h>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/sun3x.h>
#समावेश <यंत्र/sun3पूर्णांकs.h>

#समावेश "time.h"

#घोषणा M_CONTROL 0xf8
#घोषणा M_SEC     0xf9
#घोषणा M_MIN     0xfa
#घोषणा M_HOUR    0xfb
#घोषणा M_DAY     0xfc
#घोषणा M_DATE    0xfd
#घोषणा M_MONTH   0xfe
#घोषणा M_YEAR    0xff

#घोषणा C_WRITE   0x80
#घोषणा C_READ    0x40
#घोषणा C_SIGN    0x20
#घोषणा C_CALIB   0x1f

पूर्णांक sun3x_hwclk(पूर्णांक set, काष्ठा rtc_समय *t)
अणु
	अस्थिर काष्ठा mostek_dt *h =
		(काष्ठा mostek_dt *)(SUN3X_EEPROM+M_CONTROL);
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);

	अगर(set) अणु
		h->csr |= C_WRITE;
		h->sec = bin2bcd(t->पंचांग_sec);
		h->min = bin2bcd(t->पंचांग_min);
		h->hour = bin2bcd(t->पंचांग_hour);
		h->wday = bin2bcd(t->पंचांग_wday);
		h->mday = bin2bcd(t->पंचांग_mday);
		h->month = bin2bcd(t->पंचांग_mon + 1);
		h->year = bin2bcd(t->पंचांग_year % 100);
		h->csr &= ~C_WRITE;
	पूर्ण अन्यथा अणु
		h->csr |= C_READ;
		t->पंचांग_sec = bcd2bin(h->sec);
		t->पंचांग_min = bcd2bin(h->min);
		t->पंचांग_hour = bcd2bin(h->hour);
		t->पंचांग_wday = bcd2bin(h->wday);
		t->पंचांग_mday = bcd2bin(h->mday);
		t->पंचांग_mon = bcd2bin(h->month) - 1;
		t->पंचांग_year = bcd2bin(h->year);
		h->csr &= ~C_READ;
		अगर (t->पंचांग_year < 70)
			t->पंचांग_year += 100;
	पूर्ण

	local_irq_restore(flags);

	वापस 0;
पूर्ण

#अगर 0
अटल irqवापस_t sun3x_समयr_tick(पूर्णांक irq, व्योम *dev_id)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	/* Clear the pending पूर्णांकerrupt - pulse the enable line low */
	disable_irq(5);
	enable_irq(5);
	legacy_समयr_tick(1);
	local_irq_restore(flags);

	वापस IRQ_HANDLED;
पूर्ण
#पूर्ण_अगर

व्योम __init sun3x_sched_init(व्योम)
अणु

	sun3_disable_पूर्णांकerrupts();


    /* Pulse enable low to get the घड़ी started */
	sun3_disable_irq(5);
	sun3_enable_irq(5);
	sun3_enable_पूर्णांकerrupts();
पूर्ण
