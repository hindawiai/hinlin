<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित BCM63XX_TIMER_H_
#घोषणा BCM63XX_TIMER_H_

पूर्णांक bcm63xx_समयr_रेजिस्टर(पूर्णांक id, व्योम (*callback)(व्योम *data), व्योम *data);
व्योम bcm63xx_समयr_unरेजिस्टर(पूर्णांक id);
पूर्णांक bcm63xx_समयr_set(पूर्णांक id, पूर्णांक monotonic, अचिन्हित पूर्णांक countकरोwn_us);
पूर्णांक bcm63xx_समयr_enable(पूर्णांक id);
पूर्णांक bcm63xx_समयr_disable(पूर्णांक id);
अचिन्हित पूर्णांक bcm63xx_समयr_countकरोwn(अचिन्हित पूर्णांक countकरोwn_us);

#पूर्ण_अगर /* !BCM63XX_TIMER_H_ */
