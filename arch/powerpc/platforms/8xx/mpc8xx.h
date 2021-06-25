<शैली गुरु>
/*
 * Prototypes, etc. क्रम the Freescale MPC8xx embedded cpu chips
 * May need to be cleaned as the port goes on ...
 *
 * Copyright (C) 2008 Jochen Friedrich <jochen@scram.de>
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2. This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 */
#अगर_अघोषित __MPC8xx_H
#घोषणा __MPC8xx_H

बाह्य व्योम __noवापस mpc8xx_restart(अक्षर *cmd);
बाह्य व्योम mpc8xx_calibrate_decr(व्योम);
बाह्य पूर्णांक mpc8xx_set_rtc_समय(काष्ठा rtc_समय *पंचांग);
बाह्य व्योम mpc8xx_get_rtc_समय(काष्ठा rtc_समय *पंचांग);
बाह्य व्योम mpc8xx_pics_init(व्योम);
बाह्य अचिन्हित पूर्णांक mpc8xx_get_irq(व्योम);

#पूर्ण_अगर /* __MPC8xx_H */
