<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  cx18 पूर्णांकerrupt handling
 *
 *  Copyright (C) 2007  Hans Verkuil <hverkuil@xs4all.nl>
 *  Copyright (C) 2008  Andy Walls <awalls@md.metrocast.net>
 */

#समावेश "cx18-driver.h"
#समावेश "cx18-io.h"
#समावेश "cx18-irq.h"
#समावेश "cx18-mailbox.h"
#समावेश "cx18-scb.h"

अटल व्योम xpu_ack(काष्ठा cx18 *cx, u32 sw2)
अणु
	अगर (sw2 & IRQ_CPU_TO_EPU_ACK)
		wake_up(&cx->mb_cpu_रुकोq);
	अगर (sw2 & IRQ_APU_TO_EPU_ACK)
		wake_up(&cx->mb_apu_रुकोq);
पूर्ण

अटल व्योम epu_cmd(काष्ठा cx18 *cx, u32 sw1)
अणु
	अगर (sw1 & IRQ_CPU_TO_EPU)
		cx18_api_epu_cmd_irq(cx, CPU);
	अगर (sw1 & IRQ_APU_TO_EPU)
		cx18_api_epu_cmd_irq(cx, APU);
पूर्ण

irqवापस_t cx18_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा cx18 *cx = (काष्ठा cx18 *)dev_id;
	u32 sw1, sw2, hw2;

	sw1 = cx18_पढ़ो_reg(cx, SW1_INT_STATUS) & cx->sw1_irq_mask;
	sw2 = cx18_पढ़ो_reg(cx, SW2_INT_STATUS) & cx->sw2_irq_mask;
	hw2 = cx18_पढ़ो_reg(cx, HW2_INT_CLR_STATUS) & cx->hw2_irq_mask;

	अगर (sw1)
		cx18_ग_लिखो_reg_expect(cx, sw1, SW1_INT_STATUS, ~sw1, sw1);
	अगर (sw2)
		cx18_ग_लिखो_reg_expect(cx, sw2, SW2_INT_STATUS, ~sw2, sw2);
	अगर (hw2)
		cx18_ग_लिखो_reg_expect(cx, hw2, HW2_INT_CLR_STATUS, ~hw2, hw2);

	अगर (sw1 || sw2 || hw2)
		CX18_DEBUG_HI_IRQ("received interrupts SW1: %x	SW2: %x  HW2: %x\n",
				  sw1, sw2, hw2);

	/*
	 * SW1 responses have to happen first.  The sending XPU बार out the
	 * incoming mailboxes on us rather rapidly.
	 */
	अगर (sw1)
		epu_cmd(cx, sw1);

	/* To करो: पूर्णांकerrupt-based I2C handling
	अगर (hw2 & (HW2_I2C1_INT|HW2_I2C2_INT)) अणु
	पूर्ण
	*/

	अगर (sw2)
		xpu_ack(cx, sw2);

	वापस (sw1 || sw2 || hw2) ? IRQ_HANDLED : IRQ_NONE;
पूर्ण
