<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Lemote loongson2f family machines' specअगरic suspend support
 *
 *  Copyright (C) 2009 Lemote Inc.
 *  Author: Wu Zhangjin <wuzhangjin@gmail.com>
 */

#समावेश <linux/suspend.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pm.h>
#समावेश <linux/i8042.h>
#समावेश <linux/export.h>

#समावेश <यंत्र/i8259.h>
#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/bootinfo.h>

#समावेश <loongson.h>

#समावेश <cs5536/cs5536_mfgpt.h>
#समावेश "ec_kb3310b.h"

#घोषणा I8042_KBD_IRQ		1
#घोषणा I8042_CTR_KBDINT	0x01
#घोषणा I8042_CTR_KBDDIS	0x10

अटल अचिन्हित अक्षर i8042_ctr;

अटल पूर्णांक i8042_enable_kbd_port(व्योम)
अणु
	अगर (i8042_command(&i8042_ctr, I8042_CMD_CTL_RCTR)) अणु
		pr_err("i8042.c: Can't read CTR while enabling i8042 kbd port."
		       "\n");
		वापस -EIO;
	पूर्ण

	i8042_ctr &= ~I8042_CTR_KBDDIS;
	i8042_ctr |= I8042_CTR_KBDINT;

	अगर (i8042_command(&i8042_ctr, I8042_CMD_CTL_WCTR)) अणु
		i8042_ctr &= ~I8042_CTR_KBDINT;
		i8042_ctr |= I8042_CTR_KBDDIS;
		pr_err("i8042.c: Failed to enable KBD port.\n");

		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

व्योम setup_wakeup_events(व्योम)
अणु
	पूर्णांक irq_mask;

	चयन (mips_machtype) अणु
	हाल MACH_LEMOTE_ML2F7:
	हाल MACH_LEMOTE_YL2F89:
		/* खोलो the keyboard irq in i8259A */
		outb((0xff & ~(1 << I8042_KBD_IRQ)), PIC_MASTER_IMR);
		irq_mask = inb(PIC_MASTER_IMR);

		/* enable keyboard port */
		i8042_enable_kbd_port();

		/* Wakeup CPU via SCI lid खोलो event */
		outb(irq_mask & ~(1 << PIC_CASCADE_IR), PIC_MASTER_IMR);
		inb(PIC_MASTER_IMR);
		outb(0xff & ~(1 << (SCI_IRQ_NUM - 8)), PIC_SLAVE_IMR);
		inb(PIC_SLAVE_IMR);

		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल काष्ठा delayed_work lid_task;
अटल पूर्णांक initialized;
/* yeeloong_report_lid_status will be implemented in yeeloong_laptop.c */
sci_handler yeeloong_report_lid_status;
EXPORT_SYMBOL(yeeloong_report_lid_status);
अटल व्योम yeeloong_lid_update_task(काष्ठा work_काष्ठा *work)
अणु
	अगर (yeeloong_report_lid_status)
		yeeloong_report_lid_status(BIT_LID_DETECT_ON);
पूर्ण

पूर्णांक wakeup_loongson(व्योम)
अणु
	पूर्णांक irq;

	/* query the पूर्णांकerrupt number */
	irq = mach_i8259_irq();
	अगर (irq < 0)
		वापस 0;

	prपूर्णांकk(KERN_INFO "%s: irq = %d\n", __func__, irq);

	अगर (irq == I8042_KBD_IRQ)
		वापस 1;
	अन्यथा अगर (irq == SCI_IRQ_NUM) अणु
		पूर्णांक ret, sci_event;
		/* query the event number */
		ret = ec_query_seq(CMD_GET_EVENT_NUM);
		अगर (ret < 0)
			वापस 0;
		sci_event = ec_get_event_num();
		अगर (sci_event < 0)
			वापस 0;
		अगर (sci_event == EVENT_LID) अणु
			पूर्णांक lid_status;
			/* check the LID status */
			lid_status = ec_पढ़ो(REG_LID_DETECT);
			/* wakeup cpu when people खोलो the LID */
			अगर (lid_status == BIT_LID_DETECT_ON) अणु
				/* If we call it directly here, the WARNING
				 * will be sent out by getnsसमयofday
				 * via "WARN_ON(timekeeping_suspended);"
				 * because we can not schedule in suspend mode.
				 */
				अगर (initialized == 0) अणु
					INIT_DELAYED_WORK(&lid_task,
						yeeloong_lid_update_task);
					initialized = 1;
				पूर्ण
				schedule_delayed_work(&lid_task, 1);
				वापस 1;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

व्योम __weak mach_suspend(व्योम)
अणु
	disable_mfgpt0_counter();
पूर्ण

व्योम __weak mach_resume(व्योम)
अणु
	enable_mfgpt0_counter();
पूर्ण
