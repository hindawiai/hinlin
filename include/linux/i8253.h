<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 *  Machine specअगरic IO port address definition क्रम generic.
 *  Written by Osamu Tomita <tomita@cinet.co.jp>
 */
#अगर_अघोषित __LINUX_I8253_H
#घोषणा __LINUX_I8253_H

#समावेश <linux/param.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/समयx.h>

/* i8253A PIT रेजिस्टरs */
#घोषणा PIT_MODE	0x43
#घोषणा PIT_CH0		0x40
#घोषणा PIT_CH2		0x42

#घोषणा PIT_LATCH	((PIT_TICK_RATE + HZ/2) / HZ)

बाह्य raw_spinlock_t i8253_lock;
बाह्य bool i8253_clear_counter_on_shutकरोwn;
बाह्य काष्ठा घड़ी_event_device i8253_घड़ीevent;
बाह्य व्योम घड़ीevent_i8253_init(bool oneshot);

बाह्य व्योम setup_pit_समयr(व्योम);

#पूर्ण_अगर /* __LINUX_I8253_H */
