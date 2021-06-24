<शैली गुरु>
/*
** atarikb.h -- This header contains the prototypes of functions of
**              the पूर्णांकelligent keyboard of the Atari needed by the
**              mouse and joystick drivers.
**
** Copyright 1994 by Robert de Vries
**
** This file is subject to the terms and conditions of the GNU General Public
** License.  See the file COPYING in the मुख्य directory of this archive
** क्रम more details.
**
** Created: 20 Feb 1994 by Robert de Vries
*/

#अगर_अघोषित _LINUX_ATARIKB_H
#घोषणा _LINUX_ATARIKB_H

व्योम ikbd_ग_लिखो(स्थिर अक्षर *, पूर्णांक);
व्योम ikbd_mouse_button_action(पूर्णांक mode);
व्योम ikbd_mouse_rel_pos(व्योम);
व्योम ikbd_mouse_असल_pos(पूर्णांक xmax, पूर्णांक ymax);
व्योम ikbd_mouse_kbd_mode(पूर्णांक dx, पूर्णांक dy);
व्योम ikbd_mouse_thresh(पूर्णांक x, पूर्णांक y);
व्योम ikbd_mouse_scale(पूर्णांक x, पूर्णांक y);
व्योम ikbd_mouse_pos_get(पूर्णांक *x, पूर्णांक *y);
व्योम ikbd_mouse_pos_set(पूर्णांक x, पूर्णांक y);
व्योम ikbd_mouse_y0_bot(व्योम);
व्योम ikbd_mouse_y0_top(व्योम);
व्योम ikbd_mouse_disable(व्योम);
व्योम ikbd_joystick_event_on(व्योम);
व्योम ikbd_joystick_event_off(व्योम);
व्योम ikbd_joystick_get_state(व्योम);
व्योम ikbd_joystick_disable(व्योम);

/* Hook क्रम MIDI serial driver */
बाह्य व्योम (*atari_MIDI_पूर्णांकerrupt_hook) (व्योम);
/* Hook क्रम keyboard inputdev  driver */
बाह्य व्योम (*atari_input_keyboard_पूर्णांकerrupt_hook) (अचिन्हित अक्षर, अक्षर);
/* Hook क्रम mouse inputdev  driver */
बाह्य व्योम (*atari_input_mouse_पूर्णांकerrupt_hook) (अक्षर *);

पूर्णांक atari_keyb_init(व्योम);

#पूर्ण_अगर /* _LINUX_ATARIKB_H */
