<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/समय.स>
#समावेश <linux/समयr.h>
#समावेश <linux/init.h>
#समावेश <linux/rtc.h>
#समावेश <linux/delay.h>
#समावेश <linux/ratelimit.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/rtas.h>
#समावेश <यंत्र/समय.स>


#घोषणा MAX_RTC_WAIT 5000	/* 5 sec */
#घोषणा RTAS_CLOCK_BUSY (-2)
समय64_t __init rtas_get_boot_समय(व्योम)
अणु
	पूर्णांक ret[8];
	पूर्णांक error;
	अचिन्हित पूर्णांक रुको_समय;
	u64 max_रुको_tb;

	max_रुको_tb = get_tb() + tb_ticks_per_usec * 1000 * MAX_RTC_WAIT;
	करो अणु
		error = rtas_call(rtas_token("get-time-of-day"), 0, 8, ret);

		रुको_समय = rtas_busy_delay_समय(error);
		अगर (रुको_समय) अणु
			/* This is boot समय so we spin. */
			udelay(रुको_समय*1000);
		पूर्ण
	पूर्ण जबतक (रुको_समय && (get_tb() < max_रुको_tb));

	अगर (error != 0) अणु
		prपूर्णांकk_ratelimited(KERN_WARNING
				   "error: reading the clock failed (%d)\n",
				   error);
		वापस 0;
	पूर्ण

	वापस स_गढ़ो64(ret[0], ret[1], ret[2], ret[3], ret[4], ret[5]);
पूर्ण

/* NOTE: get_rtc_समय will get an error अगर executed in पूर्णांकerrupt context
 * and अगर a delay is needed to पढ़ो the घड़ी.  In this हाल we just
 * silently वापस without updating rtc_पंचांग.
 */
व्योम rtas_get_rtc_समय(काष्ठा rtc_समय *rtc_पंचांग)
अणु
        पूर्णांक ret[8];
	पूर्णांक error;
	अचिन्हित पूर्णांक रुको_समय;
	u64 max_रुको_tb;

	max_रुको_tb = get_tb() + tb_ticks_per_usec * 1000 * MAX_RTC_WAIT;
	करो अणु
		error = rtas_call(rtas_token("get-time-of-day"), 0, 8, ret);

		रुको_समय = rtas_busy_delay_समय(error);
		अगर (रुको_समय) अणु
			अगर (in_पूर्णांकerrupt()) अणु
				स_रखो(rtc_पंचांग, 0, माप(काष्ठा rtc_समय));
				prपूर्णांकk_ratelimited(KERN_WARNING
						   "error: reading clock "
						   "would delay interrupt\n");
				वापस;	/* delay not allowed */
			पूर्ण
			msleep(रुको_समय);
		पूर्ण
	पूर्ण जबतक (रुको_समय && (get_tb() < max_रुको_tb));

	अगर (error != 0) अणु
		prपूर्णांकk_ratelimited(KERN_WARNING
				   "error: reading the clock failed (%d)\n",
				   error);
		वापस;
        पूर्ण

	rtc_पंचांग->पंचांग_sec = ret[5];
	rtc_पंचांग->पंचांग_min = ret[4];
	rtc_पंचांग->पंचांग_hour = ret[3];
	rtc_पंचांग->पंचांग_mday = ret[2];
	rtc_पंचांग->पंचांग_mon = ret[1] - 1;
	rtc_पंचांग->पंचांग_year = ret[0] - 1900;
पूर्ण

पूर्णांक rtas_set_rtc_समय(काष्ठा rtc_समय *पंचांग)
अणु
	पूर्णांक error, रुको_समय;
	u64 max_रुको_tb;

	max_रुको_tb = get_tb() + tb_ticks_per_usec * 1000 * MAX_RTC_WAIT;
	करो अणु
	        error = rtas_call(rtas_token("set-time-of-day"), 7, 1, शून्य,
				  पंचांग->पंचांग_year + 1900, पंचांग->पंचांग_mon + 1,
				  पंचांग->पंचांग_mday, पंचांग->पंचांग_hour, पंचांग->पंचांग_min,
				  पंचांग->पंचांग_sec, 0);

		रुको_समय = rtas_busy_delay_समय(error);
		अगर (रुको_समय) अणु
			अगर (in_पूर्णांकerrupt())
				वापस 1;	/* probably decrementer */
			msleep(रुको_समय);
		पूर्ण
	पूर्ण जबतक (रुको_समय && (get_tb() < max_रुको_tb));

	अगर (error != 0)
		prपूर्णांकk_ratelimited(KERN_WARNING
				   "error: setting the clock failed (%d)\n",
				   error);

        वापस 0;
पूर्ण
