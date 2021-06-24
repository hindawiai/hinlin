<शैली गुरु>
/*
 * HP i8042 SDC + MSM-58321 BBRTC driver.
 *
 * Copyright (c) 2001 Brian S. Julin
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer,
 *    without modअगरication.
 * 2. The name of the author may not be used to enकरोrse or promote products
 *    derived from this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL").
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR
 * ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 *
 * References:
 * System Device Controller Microprocessor Firmware Theory of Operation
 *      क्रम Part Number 1820-4784 Revision B.  Dwg No. A-1820-4784-2
 * efirtc.c by Stephane Eranian/Hewlett Packard
 *
 */

#समावेश <linux/hp_sdc.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/समय.स>
#समावेश <linux/miscdevice.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/poll.h>
#समावेश <linux/rtc.h>
#समावेश <linux/mutex.h>
#समावेश <linux/semaphore.h>

MODULE_AUTHOR("Brian S. Julin <bri@calyx.com>");
MODULE_DESCRIPTION("HP i8042 SDC + MSM-58321 RTC Driver");
MODULE_LICENSE("Dual BSD/GPL");

#घोषणा RTC_VERSION "1.10d"

अटल अचिन्हित दीर्घ epoch = 2000;

अटल काष्ठा semaphore i8042tregs;

अटल व्योम hp_sdc_rtc_isr (पूर्णांक irq, व्योम *dev_id, 
			    uपूर्णांक8_t status, uपूर्णांक8_t data) 
अणु
	वापस;
पूर्ण

अटल पूर्णांक hp_sdc_rtc_करो_पढ़ो_bbrtc (काष्ठा rtc_समय *rtcपंचांग)
अणु
	काष्ठा semaphore tsem;
	hp_sdc_transaction t;
	uपूर्णांक8_t tseq[91];
	पूर्णांक i;
	
	i = 0;
	जबतक (i < 91) अणु
		tseq[i++] = HP_SDC_ACT_DATAREG |
			HP_SDC_ACT_POSTCMD | HP_SDC_ACT_DATAIN;
		tseq[i++] = 0x01;			/* ग_लिखो i8042[0x70] */
	  	tseq[i]   = i / 7;			/* BBRTC reg address */
		i++;
		tseq[i++] = HP_SDC_CMD_DO_RTCR;		/* Trigger command   */
		tseq[i++] = 2;		/* expect 1 stat/dat pair back.   */
		i++; i++;               /* buffer क्रम stat/dat pair       */
	पूर्ण
	tseq[84] |= HP_SDC_ACT_SEMAPHORE;
	t.endidx =		91;
	t.seq =			tseq;
	t.act.semaphore =	&tsem;
	sema_init(&tsem, 0);
	
	अगर (hp_sdc_enqueue_transaction(&t)) वापस -1;
	
	/* Put ourselves to sleep क्रम results. */
	अगर (WARN_ON(करोwn_पूर्णांकerruptible(&tsem)))
		वापस -1;
	
	/* Check क्रम nonpresence of BBRTC */
	अगर (!((tseq[83] | tseq[90] | tseq[69] | tseq[76] |
	       tseq[55] | tseq[62] | tseq[34] | tseq[41] |
	       tseq[20] | tseq[27] | tseq[6]  | tseq[13]) & 0x0f))
		वापस -1;

	स_रखो(rtcपंचांग, 0, माप(काष्ठा rtc_समय));
	rtcपंचांग->पंचांग_year = (tseq[83] & 0x0f) + (tseq[90] & 0x0f) * 10;
	rtcपंचांग->पंचांग_mon  = (tseq[69] & 0x0f) + (tseq[76] & 0x0f) * 10;
	rtcपंचांग->पंचांग_mday = (tseq[55] & 0x0f) + (tseq[62] & 0x0f) * 10;
	rtcपंचांग->पंचांग_wday = (tseq[48] & 0x0f);
	rtcपंचांग->पंचांग_hour = (tseq[34] & 0x0f) + (tseq[41] & 0x0f) * 10;
	rtcपंचांग->पंचांग_min  = (tseq[20] & 0x0f) + (tseq[27] & 0x0f) * 10;
	rtcपंचांग->पंचांग_sec  = (tseq[6]  & 0x0f) + (tseq[13] & 0x0f) * 10;
	
	वापस 0;
पूर्ण

अटल पूर्णांक hp_sdc_rtc_पढ़ो_bbrtc (काष्ठा rtc_समय *rtcपंचांग)
अणु
	काष्ठा rtc_समय पंचांग, पंचांग_last;
	पूर्णांक i = 0;

	/* MSM-58321 has no पढ़ो latch, so must पढ़ो twice and compare. */

	अगर (hp_sdc_rtc_करो_पढ़ो_bbrtc(&पंचांग_last)) वापस -1;
	अगर (hp_sdc_rtc_करो_पढ़ो_bbrtc(&पंचांग)) वापस -1;

	जबतक (स_भेद(&पंचांग, &पंचांग_last, माप(काष्ठा rtc_समय))) अणु
		अगर (i++ > 4) वापस -1;
		स_नकल(&पंचांग_last, &पंचांग, माप(काष्ठा rtc_समय));
		अगर (hp_sdc_rtc_करो_पढ़ो_bbrtc(&पंचांग)) वापस -1;
	पूर्ण

	स_नकल(rtcपंचांग, &पंचांग, माप(काष्ठा rtc_समय));

	वापस 0;
पूर्ण


अटल पूर्णांक64_t hp_sdc_rtc_पढ़ो_i8042समयr (uपूर्णांक8_t loadcmd, पूर्णांक numreg)
अणु
	hp_sdc_transaction t;
	uपूर्णांक8_t tseq[26] = अणु
		HP_SDC_ACT_PRECMD | HP_SDC_ACT_POSTCMD | HP_SDC_ACT_DATAIN,
		0,
		HP_SDC_CMD_READ_T1, 2, 0, 0,
		HP_SDC_ACT_POSTCMD | HP_SDC_ACT_DATAIN, 
		HP_SDC_CMD_READ_T2, 2, 0, 0,
		HP_SDC_ACT_POSTCMD | HP_SDC_ACT_DATAIN, 
		HP_SDC_CMD_READ_T3, 2, 0, 0,
		HP_SDC_ACT_POSTCMD | HP_SDC_ACT_DATAIN, 
		HP_SDC_CMD_READ_T4, 2, 0, 0,
		HP_SDC_ACT_POSTCMD | HP_SDC_ACT_DATAIN, 
		HP_SDC_CMD_READ_T5, 2, 0, 0
	पूर्ण;

	t.endidx = numreg * 5;

	tseq[1] = loadcmd;
	tseq[t.endidx - 4] |= HP_SDC_ACT_SEMAPHORE; /* numreg assumed > 1 */

	t.seq =			tseq;
	t.act.semaphore =	&i8042tregs;

	/* Sleep अगर output regs in use. */
	अगर (WARN_ON(करोwn_पूर्णांकerruptible(&i8042tregs)))
		वापस -1;

	अगर (hp_sdc_enqueue_transaction(&t)) अणु
		up(&i8042tregs);
		वापस -1;
	पूर्ण
	
	/* Sleep until results come back. */
	अगर (WARN_ON(करोwn_पूर्णांकerruptible(&i8042tregs)))
		वापस -1;

	up(&i8042tregs);

	वापस (tseq[5] | 
		((uपूर्णांक64_t)(tseq[10]) << 8)  | ((uपूर्णांक64_t)(tseq[15]) << 16) |
		((uपूर्णांक64_t)(tseq[20]) << 24) | ((uपूर्णांक64_t)(tseq[25]) << 32));
पूर्ण


/* Read the i8042 real-समय घड़ी */
अटल अंतरभूत पूर्णांक hp_sdc_rtc_पढ़ो_rt(काष्ठा बारpec64 *res) अणु
	पूर्णांक64_t raw;
	uपूर्णांक32_t tenms; 
	अचिन्हित पूर्णांक days;

	raw = hp_sdc_rtc_पढ़ो_i8042समयr(HP_SDC_CMD_LOAD_RT, 5);
	अगर (raw < 0) वापस -1;

	tenms = (uपूर्णांक32_t)raw & 0xffffff;
	days  = (अचिन्हित पूर्णांक)(raw >> 24) & 0xffff;

	res->tv_nsec = (दीर्घ)(tenms % 100) * 10000 * 1000;
	res->tv_sec =  (tenms / 100) + (समय64_t)days * 86400;

	वापस 0;
पूर्ण


/* Read the i8042 fast handshake समयr */
अटल अंतरभूत पूर्णांक hp_sdc_rtc_पढ़ो_fhs(काष्ठा बारpec64 *res) अणु
	पूर्णांक64_t raw;
	अचिन्हित पूर्णांक tenms;

	raw = hp_sdc_rtc_पढ़ो_i8042समयr(HP_SDC_CMD_LOAD_FHS, 2);
	अगर (raw < 0) वापस -1;

	tenms = (अचिन्हित पूर्णांक)raw & 0xffff;

	res->tv_nsec = (दीर्घ)(tenms % 100) * 10000 * 1000;
	res->tv_sec  = (समय64_t)(tenms / 100);

	वापस 0;
पूर्ण


/* Read the i8042 match समयr (a.k.a. alarm) */
अटल अंतरभूत पूर्णांक hp_sdc_rtc_पढ़ो_mt(काष्ठा बारpec64 *res) अणु
	पूर्णांक64_t raw;	
	uपूर्णांक32_t tenms; 

	raw = hp_sdc_rtc_पढ़ो_i8042समयr(HP_SDC_CMD_LOAD_MT, 3);
	अगर (raw < 0) वापस -1;

	tenms = (uपूर्णांक32_t)raw & 0xffffff;

	res->tv_nsec = (दीर्घ)(tenms % 100) * 10000 * 1000;
	res->tv_sec  = (समय64_t)(tenms / 100);

	वापस 0;
पूर्ण


/* Read the i8042 delay समयr */
अटल अंतरभूत पूर्णांक hp_sdc_rtc_पढ़ो_dt(काष्ठा बारpec64 *res) अणु
	पूर्णांक64_t raw;
	uपूर्णांक32_t tenms;

	raw = hp_sdc_rtc_पढ़ो_i8042समयr(HP_SDC_CMD_LOAD_DT, 3);
	अगर (raw < 0) वापस -1;

	tenms = (uपूर्णांक32_t)raw & 0xffffff;

	res->tv_nsec = (दीर्घ)(tenms % 100) * 10000 * 1000;
	res->tv_sec  = (समय64_t)(tenms / 100);

	वापस 0;
पूर्ण


/* Read the i8042 cycle समयr (a.k.a. periodic) */
अटल अंतरभूत पूर्णांक hp_sdc_rtc_पढ़ो_ct(काष्ठा बारpec64 *res) अणु
	पूर्णांक64_t raw;
	uपूर्णांक32_t tenms;

	raw = hp_sdc_rtc_पढ़ो_i8042समयr(HP_SDC_CMD_LOAD_CT, 3);
	अगर (raw < 0) वापस -1;

	tenms = (uपूर्णांक32_t)raw & 0xffffff;

	res->tv_nsec = (दीर्घ)(tenms % 100) * 10000 * 1000;
	res->tv_sec  = (समय64_t)(tenms / 100);

	वापस 0;
पूर्ण

अटल पूर्णांक hp_sdc_rtc_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
#घोषणा YN(bit) ("no")
#घोषणा NY(bit) ("yes")
        काष्ठा rtc_समय पंचांग;
	काष्ठा बारpec64 tv;

	स_रखो(&पंचांग, 0, माप(काष्ठा rtc_समय));

	अगर (hp_sdc_rtc_पढ़ो_bbrtc(&पंचांग)) अणु
		seq_माला_दो(m, "BBRTC\t\t: READ FAILED!\n");
	पूर्ण अन्यथा अणु
		seq_म_लिखो(m,
			     "rtc_time\t: %ptRt\n"
			     "rtc_date\t: %ptRd\n"
			     "rtc_epoch\t: %04lu\n",
			     &पंचांग, &पंचांग, epoch);
	पूर्ण

	अगर (hp_sdc_rtc_पढ़ो_rt(&tv)) अणु
		seq_माला_दो(m, "i8042 rtc\t: READ FAILED!\n");
	पूर्ण अन्यथा अणु
		seq_म_लिखो(m, "i8042 rtc\t: %lld.%02ld seconds\n",
			     (s64)tv.tv_sec, (दीर्घ)tv.tv_nsec/1000000L);
	पूर्ण

	अगर (hp_sdc_rtc_पढ़ो_fhs(&tv)) अणु
		seq_माला_दो(m, "handshake\t: READ FAILED!\n");
	पूर्ण अन्यथा अणु
		seq_म_लिखो(m, "handshake\t: %lld.%02ld seconds\n",
			     (s64)tv.tv_sec, (दीर्घ)tv.tv_nsec/1000000L);
	पूर्ण

	अगर (hp_sdc_rtc_पढ़ो_mt(&tv)) अणु
		seq_माला_दो(m, "alarm\t\t: READ FAILED!\n");
	पूर्ण अन्यथा अणु
		seq_म_लिखो(m, "alarm\t\t: %lld.%02ld seconds\n",
			     (s64)tv.tv_sec, (दीर्घ)tv.tv_nsec/1000000L);
	पूर्ण

	अगर (hp_sdc_rtc_पढ़ो_dt(&tv)) अणु
		seq_माला_दो(m, "delay\t\t: READ FAILED!\n");
	पूर्ण अन्यथा अणु
		seq_म_लिखो(m, "delay\t\t: %lld.%02ld seconds\n",
			     (s64)tv.tv_sec, (दीर्घ)tv.tv_nsec/1000000L);
	पूर्ण

	अगर (hp_sdc_rtc_पढ़ो_ct(&tv)) अणु
		seq_माला_दो(m, "periodic\t: READ FAILED!\n");
	पूर्ण अन्यथा अणु
		seq_म_लिखो(m, "periodic\t: %lld.%02ld seconds\n",
			     (s64)tv.tv_sec, (दीर्घ)tv.tv_nsec/1000000L);
	पूर्ण

        seq_म_लिखो(m,
                     "DST_enable\t: %s\n"
                     "BCD\t\t: %s\n"
                     "24hr\t\t: %s\n"
                     "square_wave\t: %s\n"
                     "alarm_IRQ\t: %s\n"
                     "update_IRQ\t: %s\n"
                     "periodic_IRQ\t: %s\n"
		     "periodic_freq\t: %ld\n"
                     "batt_status\t: %s\n",
                     YN(RTC_DST_EN),
                     NY(RTC_DM_BINARY),
                     YN(RTC_24H),
                     YN(RTC_SQWE),
                     YN(RTC_AIE),
                     YN(RTC_UIE),
                     YN(RTC_PIE),
                     1UL,
                     1 ? "okay" : "dead");

        वापस 0;
#अघोषित YN
#अघोषित NY
पूर्ण

अटल पूर्णांक __init hp_sdc_rtc_init(व्योम)
अणु
	पूर्णांक ret;

#अगर_घोषित __mc68000__
	अगर (!MACH_IS_HP300)
		वापस -ENODEV;
#पूर्ण_अगर

	sema_init(&i8042tregs, 1);

	अगर ((ret = hp_sdc_request_समयr_irq(&hp_sdc_rtc_isr)))
		वापस ret;

        proc_create_single("driver/rtc", 0, शून्य, hp_sdc_rtc_proc_show);

	prपूर्णांकk(KERN_INFO "HP i8042 SDC + MSM-58321 RTC support loaded "
			 "(RTC v " RTC_VERSION ")\n");

	वापस 0;
पूर्ण

अटल व्योम __निकास hp_sdc_rtc_निकास(व्योम)
अणु
	हटाओ_proc_entry ("driver/rtc", शून्य);
	hp_sdc_release_समयr_irq(hp_sdc_rtc_isr);
        prपूर्णांकk(KERN_INFO "HP i8042 SDC + MSM-58321 RTC support unloaded\n");
पूर्ण

module_init(hp_sdc_rtc_init);
module_निकास(hp_sdc_rtc_निकास);
