<शैली गुरु>
/*
 * arch/m68k/sun3/पूर्णांकersil.c
 *
 * basic routines क्रम accessing the पूर्णांकersil घड़ी within the sun3 machines
 *
 * started 11/12/1999 Sam Creasey
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/rtc.h>

#समावेश <यंत्र/त्रुटिसं.स>
#समावेश <यंत्र/पूर्णांकersil.h>
#समावेश <यंत्र/machdep.h>


/* bits to set क्रम start/run of the पूर्णांकersil */
#घोषणा STOP_VAL (INTERSIL_STOP | INTERSIL_INT_ENABLE | INTERSIL_24H_MODE)
#घोषणा START_VAL (INTERSIL_RUN | INTERSIL_INT_ENABLE | INTERSIL_24H_MODE)

/* get/set hwघड़ी */

पूर्णांक sun3_hwclk(पूर्णांक set, काष्ठा rtc_समय *t)
अणु
	अस्थिर काष्ठा पूर्णांकersil_dt *todपूर्णांकersil;
	अचिन्हित दीर्घ flags;

        todपूर्णांकersil = (काष्ठा पूर्णांकersil_dt *) &पूर्णांकersil_घड़ी->counter;

	local_irq_save(flags);

	पूर्णांकersil_घड़ी->cmd_reg = STOP_VAL;

	/* set or पढ़ो the घड़ी */
	अगर(set) अणु
		todपूर्णांकersil->csec = 0;
		todपूर्णांकersil->hour = t->पंचांग_hour;
		todपूर्णांकersil->minute = t->पंचांग_min;
		todपूर्णांकersil->second = t->पंचांग_sec;
		todपूर्णांकersil->month = t->पंचांग_mon + 1;
		todपूर्णांकersil->day = t->पंचांग_mday;
		todपूर्णांकersil->year = (t->पंचांग_year - 68) % 100;
		todपूर्णांकersil->weekday = t->पंचांग_wday;
	पूर्ण अन्यथा अणु
		/* पढ़ो घड़ी */
		t->पंचांग_sec = todपूर्णांकersil->csec;
		t->पंचांग_hour = todपूर्णांकersil->hour;
		t->पंचांग_min = todपूर्णांकersil->minute;
		t->पंचांग_sec = todपूर्णांकersil->second;
		t->पंचांग_mon = todपूर्णांकersil->month - 1;
		t->पंचांग_mday = todपूर्णांकersil->day;
		t->पंचांग_year = todपूर्णांकersil->year + 68;
		t->पंचांग_wday = todपूर्णांकersil->weekday;
		अगर (t->पंचांग_year < 70)
			t->पंचांग_year += 100;
	पूर्ण

	पूर्णांकersil_घड़ी->cmd_reg = START_VAL;

	local_irq_restore(flags);

	वापस 0;

पूर्ण

