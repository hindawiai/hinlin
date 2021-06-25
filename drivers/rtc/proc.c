<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * RTC subप्रणाली, proc पूर्णांकerface
 *
 * Copyright (C) 2005-06 Tower Technologies
 * Author: Alessandro Zummo <a.zummo@towertech.it>
 *
 * based on arch/arm/common/rtस_समय.c
 */

#समावेश <linux/module.h>
#समावेश <linux/rtc.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>

#समावेश "rtc-core.h"

#घोषणा NAME_SIZE	10

#अगर defined(CONFIG_RTC_HCTOSYS_DEVICE)
अटल bool is_rtc_hctosys(काष्ठा rtc_device *rtc)
अणु
	पूर्णांक size;
	अक्षर name[NAME_SIZE];

	size = scnम_लिखो(name, NAME_SIZE, "rtc%d", rtc->id);
	अगर (size > NAME_SIZE)
		वापस false;

	वापस !म_भेदन(name, CONFIG_RTC_HCTOSYS_DEVICE, NAME_SIZE);
पूर्ण
#अन्यथा
अटल bool is_rtc_hctosys(काष्ठा rtc_device *rtc)
अणु
	वापस (rtc->id == 0);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक rtc_proc_show(काष्ठा seq_file *seq, व्योम *offset)
अणु
	पूर्णांक err;
	काष्ठा rtc_device *rtc = seq->निजी;
	स्थिर काष्ठा rtc_class_ops *ops = rtc->ops;
	काष्ठा rtc_wkalrm alrm;
	काष्ठा rtc_समय पंचांग;

	err = rtc_पढ़ो_समय(rtc, &पंचांग);
	अगर (err == 0) अणु
		seq_म_लिखो(seq,
			   "rtc_time\t: %ptRt\n"
			   "rtc_date\t: %ptRd\n",
			   &पंचांग, &पंचांग);
	पूर्ण

	err = rtc_पढ़ो_alarm(rtc, &alrm);
	अगर (err == 0) अणु
		seq_म_लिखो(seq, "alrm_time\t: %ptRt\n", &alrm.समय);
		seq_म_लिखो(seq, "alrm_date\t: %ptRd\n", &alrm.समय);
		seq_म_लिखो(seq, "alarm_IRQ\t: %s\n",
			   alrm.enabled ? "yes" : "no");
		seq_म_लिखो(seq, "alrm_pending\t: %s\n",
			   alrm.pending ? "yes" : "no");
		seq_म_लिखो(seq, "update IRQ enabled\t: %s\n",
			   (rtc->uie_rtस_समयr.enabled) ? "yes" : "no");
		seq_म_लिखो(seq, "periodic IRQ enabled\t: %s\n",
			   (rtc->pie_enabled) ? "yes" : "no");
		seq_म_लिखो(seq, "periodic IRQ frequency\t: %d\n",
			   rtc->irq_freq);
		seq_म_लिखो(seq, "max user IRQ frequency\t: %d\n",
			   rtc->max_user_freq);
	पूर्ण

	seq_म_लिखो(seq, "24hr\t\t: yes\n");

	अगर (ops->proc)
		ops->proc(rtc->dev.parent, seq);

	वापस 0;
पूर्ण

व्योम rtc_proc_add_device(काष्ठा rtc_device *rtc)
अणु
	अगर (is_rtc_hctosys(rtc))
		proc_create_single_data("driver/rtc", 0, शून्य, rtc_proc_show,
					rtc);
पूर्ण

व्योम rtc_proc_del_device(काष्ठा rtc_device *rtc)
अणु
	अगर (is_rtc_hctosys(rtc))
		हटाओ_proc_entry("driver/rtc", शून्य);
पूर्ण
