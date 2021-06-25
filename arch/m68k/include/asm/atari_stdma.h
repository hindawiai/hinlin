<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित _atari_stdma_h
#घोषणा _atari_stdma_h


#समावेश <linux/पूर्णांकerrupt.h>


/***************************** Prototypes *****************************/

पूर्णांक stdma_try_lock(irq_handler_t, व्योम *);
व्योम stdma_lock(irq_handler_t handler, व्योम *data);
व्योम stdma_release( व्योम );
पूर्णांक stdma_islocked( व्योम );
पूर्णांक stdma_is_locked_by(irq_handler_t);
व्योम stdma_init( व्योम );

/************************* End of Prototypes **************************/



#पूर्ण_अगर  /* _atari_stdma_h */
