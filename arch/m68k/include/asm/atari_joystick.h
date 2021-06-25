<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_ATARI_JOYSTICK_H
#घोषणा _LINUX_ATARI_JOYSTICK_H

/*
 * linux/include/linux/atari_joystick.h
 * header file क्रम Atari Joystick driver
 * by Robert de Vries (robert@and.nl) on 19Jul93
 */

व्योम atari_joystick_पूर्णांकerrupt(अक्षर*);
पूर्णांक atari_joystick_init(व्योम);
बाह्य पूर्णांक atari_mouse_buttons;

काष्ठा joystick_status अणु
	अक्षर		fire;
	अक्षर		dir;
	पूर्णांक		पढ़ोy;
	पूर्णांक		active;
	रुको_queue_head_t रुको;
पूर्ण;

#पूर्ण_अगर
