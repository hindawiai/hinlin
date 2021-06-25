<शैली गुरु>
/*
 * Telecom Clock driver क्रम Intel NetStructure(पंचांग) MPCBL0010
 *
 * Copyright (C) 2005 Kontron Canada
 *
 * All rights reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or
 * NON INFRINGEMENT.  See the GNU General Public License क्रम more
 * details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * Send feedback to <sebastien.bouअक्षरd@ca.kontron.com> and the current
 * Maपूर्णांकainer  <mark.gross@पूर्णांकel.com>
 *
 * Description : This is the TELECOM CLOCK module driver क्रम the ATCA
 * MPCBL0010 ATCA computer.
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>	/* prपूर्णांकk() */
#समावेश <linux/fs.h>		/* everything... */
#समावेश <linux/त्रुटिसं.स>	/* error codes */
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/ioport.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mutex.h>
#समावेश <linux/समयr.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/device.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <यंत्र/पन.स>		/* inb/outb */
#समावेश <linux/uaccess.h>

MODULE_AUTHOR("Sebastien Bouchard <sebastien.bouchard@ca.kontron.com>");
MODULE_LICENSE("GPL");

/*Hardware Reset of the PLL */
#घोषणा RESET_ON	0x00
#घोषणा RESET_OFF	0x01

/* MODE SELECT */
#घोषणा NORMAL_MODE 	0x00
#घोषणा HOLDOVER_MODE	0x10
#घोषणा FREERUN_MODE	0x20

/* FILTER SELECT */
#घोषणा FILTER_6HZ	0x04
#घोषणा FILTER_12HZ	0x00

/* SELECT REFERENCE FREQUENCY */
#घोषणा REF_CLK1_8kHz		0x00
#घोषणा REF_CLK2_19_44MHz	0x02

/* Select primary or secondary redundant घड़ी */
#घोषणा PRIMARY_CLOCK	0x00
#घोषणा SECONDARY_CLOCK	0x01

/* CLOCK TRANSMISSION DEFINE */
#घोषणा CLK_8kHz	0xff
#घोषणा CLK_16_384MHz	0xfb

#घोषणा CLK_1_544MHz	0x00
#घोषणा CLK_2_048MHz	0x01
#घोषणा CLK_4_096MHz	0x02
#घोषणा CLK_6_312MHz	0x03
#घोषणा CLK_8_192MHz	0x04
#घोषणा CLK_19_440MHz	0x06

#घोषणा CLK_8_592MHz	0x08
#घोषणा CLK_11_184MHz	0x09
#घोषणा CLK_34_368MHz	0x0b
#घोषणा CLK_44_736MHz	0x0a

/* RECEIVED REFERENCE */
#घोषणा AMC_B1 0
#घोषणा AMC_B2 1

/* HARDWARE SWITCHING DEFINE */
#घोषणा HW_ENABLE	0x80
#घोषणा HW_DISABLE	0x00

/* HARDWARE SWITCHING MODE DEFINE */
#घोषणा PLL_HOLDOVER	0x40
#घोषणा LOST_CLOCK	0x00

/* ALARMS DEFINE */
#घोषणा UNLOCK_MASK	0x10
#घोषणा HOLDOVER_MASK	0x20
#घोषणा SEC_LOST_MASK	0x40
#घोषणा PRI_LOST_MASK	0x80

/* INTERRUPT CAUSE DEFINE */

#घोषणा PRI_LOS_01_MASK		0x01
#घोषणा PRI_LOS_10_MASK		0x02

#घोषणा SEC_LOS_01_MASK		0x04
#घोषणा SEC_LOS_10_MASK		0x08

#घोषणा HOLDOVER_01_MASK	0x10
#घोषणा HOLDOVER_10_MASK	0x20

#घोषणा UNLOCK_01_MASK		0x40
#घोषणा UNLOCK_10_MASK		0x80

काष्ठा tlclk_alarms अणु
	__u32 lost_घड़ीs;
	__u32 lost_primary_घड़ी;
	__u32 lost_secondary_घड़ी;
	__u32 primary_घड़ी_back;
	__u32 secondary_घड़ी_back;
	__u32 चयनover_primary;
	__u32 चयनover_secondary;
	__u32 pll_holकरोver;
	__u32 pll_end_holकरोver;
	__u32 pll_lost_sync;
	__u32 pll_sync;
पूर्ण;
/* Telecom घड़ी I/O रेजिस्टर definition */
#घोषणा TLCLK_BASE 0xa08
#घोषणा TLCLK_REG0 TLCLK_BASE
#घोषणा TLCLK_REG1 (TLCLK_BASE+1)
#घोषणा TLCLK_REG2 (TLCLK_BASE+2)
#घोषणा TLCLK_REG3 (TLCLK_BASE+3)
#घोषणा TLCLK_REG4 (TLCLK_BASE+4)
#घोषणा TLCLK_REG5 (TLCLK_BASE+5)
#घोषणा TLCLK_REG6 (TLCLK_BASE+6)
#घोषणा TLCLK_REG7 (TLCLK_BASE+7)

#घोषणा SET_PORT_BITS(port, mask, val) outb(((inb(port) & mask) | val), port)

/* 0 = Dynamic allocation of the major device number */
#घोषणा TLCLK_MAJOR 0

/* sysfs पूर्णांकerface definition:
Upon loading the driver will create a sysfs directory under
/sys/devices/platक्रमm/telco_घड़ी.

This directory exports the following पूर्णांकerfaces.  There operation is
करोcumented in the MCPBL0010 TPS under the Telecom Clock API section, 11.4.
alarms				:
current_ref			:
received_ref_clk3a		:
received_ref_clk3b		:
enable_clk3a_output		:
enable_clk3b_output		:
enable_clka0_output		:
enable_clka1_output		:
enable_clkb0_output		:
enable_clkb1_output		:
filter_select			:
hardware_चयनing		:
hardware_चयनing_mode		:
telघड़ी_version		:
mode_select			:
refalign			:
reset				:
select_amcb1_transmit_घड़ी	:
select_amcb2_transmit_घड़ी	:
select_redundant_घड़ी		:
select_ref_frequency		:

All sysfs पूर्णांकerfaces are पूर्णांकegers in hex क्रमmat, i.e echo 99 > refalign
has the same effect as echo 0x99 > refalign.
*/

अटल अचिन्हित पूर्णांक telclk_पूर्णांकerrupt;

अटल पूर्णांक पूर्णांक_events;		/* Event that generate a पूर्णांकerrupt */
अटल पूर्णांक got_event;		/* अगर events processing have been करोne */

अटल व्योम चयनover_समयout(काष्ठा समयr_list *t);
अटल काष्ठा समयr_list चयनover_समयr;
अटल अचिन्हित दीर्घ tlclk_समयr_data;

अटल काष्ठा tlclk_alarms *alarm_events;

अटल DEFINE_SPINLOCK(event_lock);

अटल पूर्णांक tlclk_major = TLCLK_MAJOR;

अटल irqवापस_t tlclk_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);

अटल DECLARE_WAIT_QUEUE_HEAD(wq);

अटल अचिन्हित दीर्घ useflags;
अटल DEFINE_MUTEX(tlclk_mutex);

अटल पूर्णांक tlclk_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	पूर्णांक result;

	mutex_lock(&tlclk_mutex);
	अगर (test_and_set_bit(0, &useflags)) अणु
		result = -EBUSY;
		/* this legacy device is always one per प्रणाली and it करोesn't
		 * know how to handle multiple concurrent clients.
		 */
		जाओ out;
	पूर्ण

	/* Make sure there is no पूर्णांकerrupt pending जबतक
	 * initialising पूर्णांकerrupt handler */
	inb(TLCLK_REG6);

	/* This device is wired through the FPGA IO space of the ATCA blade
	 * we can't share this IRQ */
	result = request_irq(telclk_पूर्णांकerrupt, &tlclk_पूर्णांकerrupt,
			     0, "telco_clock", tlclk_पूर्णांकerrupt);
	अगर (result == -EBUSY)
		prपूर्णांकk(KERN_ERR "tlclk: Interrupt can't be reserved.\n");
	अन्यथा
		inb(TLCLK_REG6);	/* Clear पूर्णांकerrupt events */

out:
	mutex_unlock(&tlclk_mutex);
	वापस result;
पूर्ण

अटल पूर्णांक tlclk_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	मुक्त_irq(telclk_पूर्णांकerrupt, tlclk_पूर्णांकerrupt);
	clear_bit(0, &useflags);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार tlclk_पढ़ो(काष्ठा file *filp, अक्षर __user *buf, माप_प्रकार count,
		loff_t *f_pos)
अणु
	अगर (count < माप(काष्ठा tlclk_alarms))
		वापस -EIO;
	अगर (mutex_lock_पूर्णांकerruptible(&tlclk_mutex))
		वापस -EINTR;


	रुको_event_पूर्णांकerruptible(wq, got_event);
	अगर (copy_to_user(buf, alarm_events, माप(काष्ठा tlclk_alarms))) अणु
		mutex_unlock(&tlclk_mutex);
		वापस -EFAULT;
	पूर्ण

	स_रखो(alarm_events, 0, माप(काष्ठा tlclk_alarms));
	got_event = 0;

	mutex_unlock(&tlclk_mutex);
	वापस  माप(काष्ठा tlclk_alarms);
पूर्ण

अटल स्थिर काष्ठा file_operations tlclk_fops = अणु
	.पढ़ो = tlclk_पढ़ो,
	.खोलो = tlclk_खोलो,
	.release = tlclk_release,
	.llseek = noop_llseek,

पूर्ण;

अटल काष्ठा miscdevice tlclk_miscdev = अणु
	.minor = MISC_DYNAMIC_MINOR,
	.name = "telco_clock",
	.fops = &tlclk_fops,
पूर्ण;

अटल sमाप_प्रकार show_current_ref(काष्ठा device *d,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अचिन्हित दीर्घ ret_val;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&event_lock, flags);
	ret_val = ((inb(TLCLK_REG1) & 0x08) >> 3);
	spin_unlock_irqrestore(&event_lock, flags);

	वापस प्र_लिखो(buf, "0x%lX\n", ret_val);
पूर्ण

अटल DEVICE_ATTR(current_ref, S_IRUGO, show_current_ref, शून्य);


अटल sमाप_प्रकार show_telघड़ी_version(काष्ठा device *d,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अचिन्हित दीर्घ ret_val;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&event_lock, flags);
	ret_val = inb(TLCLK_REG5);
	spin_unlock_irqrestore(&event_lock, flags);

	वापस प्र_लिखो(buf, "0x%lX\n", ret_val);
पूर्ण

अटल DEVICE_ATTR(telघड़ी_version, S_IRUGO,
		show_telघड़ी_version, शून्य);

अटल sमाप_प्रकार show_alarms(काष्ठा device *d,
		काष्ठा device_attribute *attr,  अक्षर *buf)
अणु
	अचिन्हित दीर्घ ret_val;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&event_lock, flags);
	ret_val = (inb(TLCLK_REG2) & 0xf0);
	spin_unlock_irqrestore(&event_lock, flags);

	वापस प्र_लिखो(buf, "0x%lX\n", ret_val);
पूर्ण

अटल DEVICE_ATTR(alarms, S_IRUGO, show_alarms, शून्य);

अटल sमाप_प्रकार store_received_ref_clk3a(काष्ठा device *d,
		 काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ पंचांगp;
	अचिन्हित अक्षर val;
	अचिन्हित दीर्घ flags;

	माला_पूछो(buf, "%lX", &पंचांगp);
	dev_dbg(d, ": tmp = 0x%lX\n", पंचांगp);

	val = (अचिन्हित अक्षर)पंचांगp;
	spin_lock_irqsave(&event_lock, flags);
	SET_PORT_BITS(TLCLK_REG1, 0xef, val);
	spin_unlock_irqrestore(&event_lock, flags);

	वापस strnlen(buf, count);
पूर्ण

अटल DEVICE_ATTR(received_ref_clk3a, (S_IWUSR|S_IWGRP), शून्य,
		store_received_ref_clk3a);


अटल sमाप_प्रकार store_received_ref_clk3b(काष्ठा device *d,
		 काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ पंचांगp;
	अचिन्हित अक्षर val;
	अचिन्हित दीर्घ flags;

	माला_पूछो(buf, "%lX", &पंचांगp);
	dev_dbg(d, ": tmp = 0x%lX\n", पंचांगp);

	val = (अचिन्हित अक्षर)पंचांगp;
	spin_lock_irqsave(&event_lock, flags);
	SET_PORT_BITS(TLCLK_REG1, 0xdf, val << 1);
	spin_unlock_irqrestore(&event_lock, flags);

	वापस strnlen(buf, count);
पूर्ण

अटल DEVICE_ATTR(received_ref_clk3b, (S_IWUSR|S_IWGRP), शून्य,
		store_received_ref_clk3b);


अटल sमाप_प्रकार store_enable_clk3b_output(काष्ठा device *d,
		 काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ पंचांगp;
	अचिन्हित अक्षर val;
	अचिन्हित दीर्घ flags;

	माला_पूछो(buf, "%lX", &पंचांगp);
	dev_dbg(d, ": tmp = 0x%lX\n", पंचांगp);

	val = (अचिन्हित अक्षर)पंचांगp;
	spin_lock_irqsave(&event_lock, flags);
	SET_PORT_BITS(TLCLK_REG3, 0x7f, val << 7);
	spin_unlock_irqrestore(&event_lock, flags);

	वापस strnlen(buf, count);
पूर्ण

अटल DEVICE_ATTR(enable_clk3b_output, (S_IWUSR|S_IWGRP), शून्य,
		store_enable_clk3b_output);

अटल sमाप_प्रकार store_enable_clk3a_output(काष्ठा device *d,
		 काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ पंचांगp;
	अचिन्हित अक्षर val;

	माला_पूछो(buf, "%lX", &पंचांगp);
	dev_dbg(d, "tmp = 0x%lX\n", पंचांगp);

	val = (अचिन्हित अक्षर)पंचांगp;
	spin_lock_irqsave(&event_lock, flags);
	SET_PORT_BITS(TLCLK_REG3, 0xbf, val << 6);
	spin_unlock_irqrestore(&event_lock, flags);

	वापस strnlen(buf, count);
पूर्ण

अटल DEVICE_ATTR(enable_clk3a_output, (S_IWUSR|S_IWGRP), शून्य,
		store_enable_clk3a_output);

अटल sमाप_प्रकार store_enable_clkb1_output(काष्ठा device *d,
		 काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ पंचांगp;
	अचिन्हित अक्षर val;

	माला_पूछो(buf, "%lX", &पंचांगp);
	dev_dbg(d, "tmp = 0x%lX\n", पंचांगp);

	val = (अचिन्हित अक्षर)पंचांगp;
	spin_lock_irqsave(&event_lock, flags);
	SET_PORT_BITS(TLCLK_REG2, 0xf7, val << 3);
	spin_unlock_irqrestore(&event_lock, flags);

	वापस strnlen(buf, count);
पूर्ण

अटल DEVICE_ATTR(enable_clkb1_output, (S_IWUSR|S_IWGRP), शून्य,
		store_enable_clkb1_output);


अटल sमाप_प्रकार store_enable_clka1_output(काष्ठा device *d,
		 काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ पंचांगp;
	अचिन्हित अक्षर val;

	माला_पूछो(buf, "%lX", &पंचांगp);
	dev_dbg(d, "tmp = 0x%lX\n", पंचांगp);

	val = (अचिन्हित अक्षर)पंचांगp;
	spin_lock_irqsave(&event_lock, flags);
	SET_PORT_BITS(TLCLK_REG2, 0xfb, val << 2);
	spin_unlock_irqrestore(&event_lock, flags);

	वापस strnlen(buf, count);
पूर्ण

अटल DEVICE_ATTR(enable_clka1_output, (S_IWUSR|S_IWGRP), शून्य,
		store_enable_clka1_output);

अटल sमाप_प्रकार store_enable_clkb0_output(काष्ठा device *d,
		 काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ पंचांगp;
	अचिन्हित अक्षर val;

	माला_पूछो(buf, "%lX", &पंचांगp);
	dev_dbg(d, "tmp = 0x%lX\n", पंचांगp);

	val = (अचिन्हित अक्षर)पंचांगp;
	spin_lock_irqsave(&event_lock, flags);
	SET_PORT_BITS(TLCLK_REG2, 0xfd, val << 1);
	spin_unlock_irqrestore(&event_lock, flags);

	वापस strnlen(buf, count);
पूर्ण

अटल DEVICE_ATTR(enable_clkb0_output, (S_IWUSR|S_IWGRP), शून्य,
		store_enable_clkb0_output);

अटल sमाप_प्रकार store_enable_clka0_output(काष्ठा device *d,
		 काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ पंचांगp;
	अचिन्हित अक्षर val;

	माला_पूछो(buf, "%lX", &पंचांगp);
	dev_dbg(d, "tmp = 0x%lX\n", पंचांगp);

	val = (अचिन्हित अक्षर)पंचांगp;
	spin_lock_irqsave(&event_lock, flags);
	SET_PORT_BITS(TLCLK_REG2, 0xfe, val);
	spin_unlock_irqrestore(&event_lock, flags);

	वापस strnlen(buf, count);
पूर्ण

अटल DEVICE_ATTR(enable_clka0_output, (S_IWUSR|S_IWGRP), शून्य,
		store_enable_clka0_output);

अटल sमाप_प्रकार store_select_amcb2_transmit_घड़ी(काष्ठा device *d,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ पंचांगp;
	अचिन्हित अक्षर val;

	माला_पूछो(buf, "%lX", &पंचांगp);
	dev_dbg(d, "tmp = 0x%lX\n", पंचांगp);

	val = (अचिन्हित अक्षर)पंचांगp;
	spin_lock_irqsave(&event_lock, flags);
	अगर ((val == CLK_8kHz) || (val == CLK_16_384MHz)) अणु
		SET_PORT_BITS(TLCLK_REG3, 0xc7, 0x28);
		SET_PORT_BITS(TLCLK_REG1, 0xfb, ~val);
	पूर्ण अन्यथा अगर (val >= CLK_8_592MHz) अणु
		SET_PORT_BITS(TLCLK_REG3, 0xc7, 0x38);
		चयन (val) अणु
		हाल CLK_8_592MHz:
			SET_PORT_BITS(TLCLK_REG0, 0xfc, 2);
			अवरोध;
		हाल CLK_11_184MHz:
			SET_PORT_BITS(TLCLK_REG0, 0xfc, 0);
			अवरोध;
		हाल CLK_34_368MHz:
			SET_PORT_BITS(TLCLK_REG0, 0xfc, 3);
			अवरोध;
		हाल CLK_44_736MHz:
			SET_PORT_BITS(TLCLK_REG0, 0xfc, 1);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		SET_PORT_BITS(TLCLK_REG3, 0xc7, val << 3);
	पूर्ण
	spin_unlock_irqrestore(&event_lock, flags);

	वापस strnlen(buf, count);
पूर्ण

अटल DEVICE_ATTR(select_amcb2_transmit_घड़ी, (S_IWUSR|S_IWGRP), शून्य,
	store_select_amcb2_transmit_घड़ी);

अटल sमाप_प्रकार store_select_amcb1_transmit_घड़ी(काष्ठा device *d,
		 काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ पंचांगp;
	अचिन्हित अक्षर val;
	अचिन्हित दीर्घ flags;

	माला_पूछो(buf, "%lX", &पंचांगp);
	dev_dbg(d, "tmp = 0x%lX\n", पंचांगp);

	val = (अचिन्हित अक्षर)पंचांगp;
	spin_lock_irqsave(&event_lock, flags);
	अगर ((val == CLK_8kHz) || (val == CLK_16_384MHz)) अणु
		SET_PORT_BITS(TLCLK_REG3, 0xf8, 0x5);
		SET_PORT_BITS(TLCLK_REG1, 0xfb, ~val);
	पूर्ण अन्यथा अगर (val >= CLK_8_592MHz) अणु
		SET_PORT_BITS(TLCLK_REG3, 0xf8, 0x7);
		चयन (val) अणु
		हाल CLK_8_592MHz:
			SET_PORT_BITS(TLCLK_REG0, 0xfc, 2);
			अवरोध;
		हाल CLK_11_184MHz:
			SET_PORT_BITS(TLCLK_REG0, 0xfc, 0);
			अवरोध;
		हाल CLK_34_368MHz:
			SET_PORT_BITS(TLCLK_REG0, 0xfc, 3);
			अवरोध;
		हाल CLK_44_736MHz:
			SET_PORT_BITS(TLCLK_REG0, 0xfc, 1);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		SET_PORT_BITS(TLCLK_REG3, 0xf8, val);
	पूर्ण
	spin_unlock_irqrestore(&event_lock, flags);

	वापस strnlen(buf, count);
पूर्ण

अटल DEVICE_ATTR(select_amcb1_transmit_घड़ी, (S_IWUSR|S_IWGRP), शून्य,
		store_select_amcb1_transmit_घड़ी);

अटल sमाप_प्रकार store_select_redundant_घड़ी(काष्ठा device *d,
		 काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ पंचांगp;
	अचिन्हित अक्षर val;
	अचिन्हित दीर्घ flags;

	माला_पूछो(buf, "%lX", &पंचांगp);
	dev_dbg(d, "tmp = 0x%lX\n", पंचांगp);

	val = (अचिन्हित अक्षर)पंचांगp;
	spin_lock_irqsave(&event_lock, flags);
	SET_PORT_BITS(TLCLK_REG1, 0xfe, val);
	spin_unlock_irqrestore(&event_lock, flags);

	वापस strnlen(buf, count);
पूर्ण

अटल DEVICE_ATTR(select_redundant_घड़ी, (S_IWUSR|S_IWGRP), शून्य,
		store_select_redundant_घड़ी);

अटल sमाप_प्रकार store_select_ref_frequency(काष्ठा device *d,
		 काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ पंचांगp;
	अचिन्हित अक्षर val;
	अचिन्हित दीर्घ flags;

	माला_पूछो(buf, "%lX", &पंचांगp);
	dev_dbg(d, "tmp = 0x%lX\n", पंचांगp);

	val = (अचिन्हित अक्षर)पंचांगp;
	spin_lock_irqsave(&event_lock, flags);
	SET_PORT_BITS(TLCLK_REG1, 0xfd, val);
	spin_unlock_irqrestore(&event_lock, flags);

	वापस strnlen(buf, count);
पूर्ण

अटल DEVICE_ATTR(select_ref_frequency, (S_IWUSR|S_IWGRP), शून्य,
		store_select_ref_frequency);

अटल sमाप_प्रकार store_filter_select(काष्ठा device *d,
		 काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ पंचांगp;
	अचिन्हित अक्षर val;
	अचिन्हित दीर्घ flags;

	माला_पूछो(buf, "%lX", &पंचांगp);
	dev_dbg(d, "tmp = 0x%lX\n", पंचांगp);

	val = (अचिन्हित अक्षर)पंचांगp;
	spin_lock_irqsave(&event_lock, flags);
	SET_PORT_BITS(TLCLK_REG0, 0xfb, val);
	spin_unlock_irqrestore(&event_lock, flags);

	वापस strnlen(buf, count);
पूर्ण

अटल DEVICE_ATTR(filter_select, (S_IWUSR|S_IWGRP), शून्य, store_filter_select);

अटल sमाप_प्रकार store_hardware_चयनing_mode(काष्ठा device *d,
		 काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ पंचांगp;
	अचिन्हित अक्षर val;
	अचिन्हित दीर्घ flags;

	माला_पूछो(buf, "%lX", &पंचांगp);
	dev_dbg(d, "tmp = 0x%lX\n", पंचांगp);

	val = (अचिन्हित अक्षर)पंचांगp;
	spin_lock_irqsave(&event_lock, flags);
	SET_PORT_BITS(TLCLK_REG0, 0xbf, val);
	spin_unlock_irqrestore(&event_lock, flags);

	वापस strnlen(buf, count);
पूर्ण

अटल DEVICE_ATTR(hardware_चयनing_mode, (S_IWUSR|S_IWGRP), शून्य,
		store_hardware_चयनing_mode);

अटल sमाप_प्रकार store_hardware_चयनing(काष्ठा device *d,
		 काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ पंचांगp;
	अचिन्हित अक्षर val;
	अचिन्हित दीर्घ flags;

	माला_पूछो(buf, "%lX", &पंचांगp);
	dev_dbg(d, "tmp = 0x%lX\n", पंचांगp);

	val = (अचिन्हित अक्षर)पंचांगp;
	spin_lock_irqsave(&event_lock, flags);
	SET_PORT_BITS(TLCLK_REG0, 0x7f, val);
	spin_unlock_irqrestore(&event_lock, flags);

	वापस strnlen(buf, count);
पूर्ण

अटल DEVICE_ATTR(hardware_चयनing, (S_IWUSR|S_IWGRP), शून्य,
		store_hardware_चयनing);

अटल sमाप_प्रकार store_refalign (काष्ठा device *d,
		 काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ पंचांगp;
	अचिन्हित दीर्घ flags;

	माला_पूछो(buf, "%lX", &पंचांगp);
	dev_dbg(d, "tmp = 0x%lX\n", पंचांगp);
	spin_lock_irqsave(&event_lock, flags);
	SET_PORT_BITS(TLCLK_REG0, 0xf7, 0);
	SET_PORT_BITS(TLCLK_REG0, 0xf7, 0x08);
	SET_PORT_BITS(TLCLK_REG0, 0xf7, 0);
	spin_unlock_irqrestore(&event_lock, flags);

	वापस strnlen(buf, count);
पूर्ण

अटल DEVICE_ATTR(refalign, (S_IWUSR|S_IWGRP), शून्य, store_refalign);

अटल sमाप_प्रकार store_mode_select (काष्ठा device *d,
		 काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ पंचांगp;
	अचिन्हित अक्षर val;
	अचिन्हित दीर्घ flags;

	माला_पूछो(buf, "%lX", &पंचांगp);
	dev_dbg(d, "tmp = 0x%lX\n", पंचांगp);

	val = (अचिन्हित अक्षर)पंचांगp;
	spin_lock_irqsave(&event_lock, flags);
	SET_PORT_BITS(TLCLK_REG0, 0xcf, val);
	spin_unlock_irqrestore(&event_lock, flags);

	वापस strnlen(buf, count);
पूर्ण

अटल DEVICE_ATTR(mode_select, (S_IWUSR|S_IWGRP), शून्य, store_mode_select);

अटल sमाप_प्रकार store_reset (काष्ठा device *d,
		 काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ पंचांगp;
	अचिन्हित अक्षर val;
	अचिन्हित दीर्घ flags;

	माला_पूछो(buf, "%lX", &पंचांगp);
	dev_dbg(d, "tmp = 0x%lX\n", पंचांगp);

	val = (अचिन्हित अक्षर)पंचांगp;
	spin_lock_irqsave(&event_lock, flags);
	SET_PORT_BITS(TLCLK_REG4, 0xfd, val);
	spin_unlock_irqrestore(&event_lock, flags);

	वापस strnlen(buf, count);
पूर्ण

अटल DEVICE_ATTR(reset, (S_IWUSR|S_IWGRP), शून्य, store_reset);

अटल काष्ठा attribute *tlclk_sysfs_entries[] = अणु
	&dev_attr_current_ref.attr,
	&dev_attr_telघड़ी_version.attr,
	&dev_attr_alarms.attr,
	&dev_attr_received_ref_clk3a.attr,
	&dev_attr_received_ref_clk3b.attr,
	&dev_attr_enable_clk3a_output.attr,
	&dev_attr_enable_clk3b_output.attr,
	&dev_attr_enable_clkb1_output.attr,
	&dev_attr_enable_clka1_output.attr,
	&dev_attr_enable_clkb0_output.attr,
	&dev_attr_enable_clka0_output.attr,
	&dev_attr_select_amcb1_transmit_घड़ी.attr,
	&dev_attr_select_amcb2_transmit_घड़ी.attr,
	&dev_attr_select_redundant_घड़ी.attr,
	&dev_attr_select_ref_frequency.attr,
	&dev_attr_filter_select.attr,
	&dev_attr_hardware_चयनing_mode.attr,
	&dev_attr_hardware_चयनing.attr,
	&dev_attr_refalign.attr,
	&dev_attr_mode_select.attr,
	&dev_attr_reset.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group tlclk_attribute_group = अणु
	.name = शून्य,		/* put in device directory */
	.attrs = tlclk_sysfs_entries,
पूर्ण;

अटल काष्ठा platक्रमm_device *tlclk_device;

अटल पूर्णांक __init tlclk_init(व्योम)
अणु
	पूर्णांक ret;

	telclk_पूर्णांकerrupt = (inb(TLCLK_REG7) & 0x0f);

	alarm_events = kzalloc( माप(काष्ठा tlclk_alarms), GFP_KERNEL);
	अगर (!alarm_events) अणु
		ret = -ENOMEM;
		जाओ out1;
	पूर्ण

	ret = रेजिस्टर_chrdev(tlclk_major, "telco_clock", &tlclk_fops);
	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_ERR "tlclk: can't get major %d.\n", tlclk_major);
		kमुक्त(alarm_events);
		वापस ret;
	पूर्ण
	tlclk_major = ret;

	/* Read telecom घड़ी IRQ number (Set by BIOS) */
	अगर (!request_region(TLCLK_BASE, 8, "telco_clock")) अणु
		prपूर्णांकk(KERN_ERR "tlclk: request_region 0x%X failed.\n",
			TLCLK_BASE);
		ret = -EBUSY;
		जाओ out2;
	पूर्ण

	अगर (0x0F == telclk_पूर्णांकerrupt ) अणु /* not MCPBL0010 ? */
		prपूर्णांकk(KERN_ERR "telclk_interrupt = 0x%x non-mcpbl0010 hw.\n",
			telclk_पूर्णांकerrupt);
		ret = -ENXIO;
		जाओ out3;
	पूर्ण

	समयr_setup(&चयनover_समयr, चयनover_समयout, 0);

	ret = misc_रेजिस्टर(&tlclk_miscdev);
	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_ERR "tlclk: misc_register returns %d.\n", ret);
		जाओ out3;
	पूर्ण

	tlclk_device = platक्रमm_device_रेजिस्टर_simple("telco_clock",
				-1, शून्य, 0);
	अगर (IS_ERR(tlclk_device)) अणु
		prपूर्णांकk(KERN_ERR "tlclk: platform_device_register failed.\n");
		ret = PTR_ERR(tlclk_device);
		जाओ out4;
	पूर्ण

	ret = sysfs_create_group(&tlclk_device->dev.kobj,
			&tlclk_attribute_group);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "tlclk: failed to create sysfs device attributes.\n");
		जाओ out5;
	पूर्ण

	वापस 0;
out5:
	platक्रमm_device_unरेजिस्टर(tlclk_device);
out4:
	misc_deरेजिस्टर(&tlclk_miscdev);
out3:
	release_region(TLCLK_BASE, 8);
out2:
	kमुक्त(alarm_events);
	unरेजिस्टर_chrdev(tlclk_major, "telco_clock");
out1:
	वापस ret;
पूर्ण

अटल व्योम __निकास tlclk_cleanup(व्योम)
अणु
	sysfs_हटाओ_group(&tlclk_device->dev.kobj, &tlclk_attribute_group);
	platक्रमm_device_unरेजिस्टर(tlclk_device);
	misc_deरेजिस्टर(&tlclk_miscdev);
	unरेजिस्टर_chrdev(tlclk_major, "telco_clock");

	release_region(TLCLK_BASE, 8);
	del_समयr_sync(&चयनover_समयr);
	kमुक्त(alarm_events);

पूर्ण

अटल व्योम चयनover_समयout(काष्ठा समयr_list *unused)
अणु
	अचिन्हित दीर्घ flags = tlclk_समयr_data;

	अगर ((flags & 1)) अणु
		अगर ((inb(TLCLK_REG1) & 0x08) != (flags & 0x08))
			alarm_events->चयनover_primary++;
	पूर्ण अन्यथा अणु
		अगर ((inb(TLCLK_REG1) & 0x08) != (flags & 0x08))
			alarm_events->चयनover_secondary++;
	पूर्ण

	/* Alarm processing is करोne, wake up पढ़ो task */
	del_समयr(&चयनover_समयr);
	got_event = 1;
	wake_up(&wq);
पूर्ण

अटल irqवापस_t tlclk_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&event_lock, flags);
	/* Read and clear पूर्णांकerrupt events */
	पूर्णांक_events = inb(TLCLK_REG6);

	/* Primary_Los changed from 0 to 1 ? */
	अगर (पूर्णांक_events & PRI_LOS_01_MASK) अणु
		अगर (inb(TLCLK_REG2) & SEC_LOST_MASK)
			alarm_events->lost_घड़ीs++;
		अन्यथा
			alarm_events->lost_primary_घड़ी++;
	पूर्ण

	/* Primary_Los changed from 1 to 0 ? */
	अगर (पूर्णांक_events & PRI_LOS_10_MASK) अणु
		alarm_events->primary_घड़ी_back++;
		SET_PORT_BITS(TLCLK_REG1, 0xFE, 1);
	पूर्ण
	/* Secondary_Los changed from 0 to 1 ? */
	अगर (पूर्णांक_events & SEC_LOS_01_MASK) अणु
		अगर (inb(TLCLK_REG2) & PRI_LOST_MASK)
			alarm_events->lost_घड़ीs++;
		अन्यथा
			alarm_events->lost_secondary_घड़ी++;
	पूर्ण
	/* Secondary_Los changed from 1 to 0 ? */
	अगर (पूर्णांक_events & SEC_LOS_10_MASK) अणु
		alarm_events->secondary_घड़ी_back++;
		SET_PORT_BITS(TLCLK_REG1, 0xFE, 0);
	पूर्ण
	अगर (पूर्णांक_events & HOLDOVER_10_MASK)
		alarm_events->pll_end_holकरोver++;

	अगर (पूर्णांक_events & UNLOCK_01_MASK)
		alarm_events->pll_lost_sync++;

	अगर (पूर्णांक_events & UNLOCK_10_MASK)
		alarm_events->pll_sync++;

	/* Holकरोver changed from 0 to 1 ? */
	अगर (पूर्णांक_events & HOLDOVER_01_MASK) अणु
		alarm_events->pll_holकरोver++;

		/* TIMEOUT in ~10ms */
		चयनover_समयr.expires = jअगरfies + msecs_to_jअगरfies(10);
		tlclk_समयr_data = inb(TLCLK_REG1);
		mod_समयr(&चयनover_समयr, चयनover_समयr.expires);
	पूर्ण अन्यथा अणु
		got_event = 1;
		wake_up(&wq);
	पूर्ण
	spin_unlock_irqrestore(&event_lock, flags);

	वापस IRQ_HANDLED;
पूर्ण

module_init(tlclk_init);
module_निकास(tlclk_cleanup);
