<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __UM_DELAY_H
#घोषणा __UM_DELAY_H
#समावेश <यंत्र-generic/delay.h>
#समावेश <linux/समय-पूर्णांकernal.h>

अटल अंतरभूत व्योम um_ndelay(अचिन्हित दीर्घ nsecs)
अणु
	अगर (समय_प्रकारravel_mode == TT_MODE_INFCPU ||
	    समय_प्रकारravel_mode == TT_MODE_EXTERNAL) अणु
		समय_प्रकारravel_ndelay(nsecs);
		वापस;
	पूर्ण
	ndelay(nsecs);
पूर्ण
#अघोषित ndelay
#घोषणा ndelay um_ndelay

अटल अंतरभूत व्योम um_udelay(अचिन्हित दीर्घ usecs)
अणु
	अगर (समय_प्रकारravel_mode == TT_MODE_INFCPU ||
	    समय_प्रकारravel_mode == TT_MODE_EXTERNAL) अणु
		समय_प्रकारravel_ndelay(1000 * usecs);
		वापस;
	पूर्ण
	udelay(usecs);
पूर्ण
#अघोषित udelay
#घोषणा udelay um_udelay
#पूर्ण_अगर /* __UM_DELAY_H */
