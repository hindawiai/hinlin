<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_KEYBOARD_H
#घोषणा __LINUX_KEYBOARD_H

#समावेश <uapi/linux/keyboard.h>

काष्ठा notअगरier_block;
बाह्य अचिन्हित लघु *key_maps[MAX_NR_KEYMAPS];
बाह्य अचिन्हित लघु plain_map[NR_KEYS];

काष्ठा keyboard_notअगरier_param अणु
	काष्ठा vc_data *vc;	/* VC on which the keyboard press was करोne */
	पूर्णांक करोwn;		/* Pressure of the key? */
	पूर्णांक shअगरt;		/* Current shअगरt mask */
	पूर्णांक ledstate;		/* Current led state */
	अचिन्हित पूर्णांक value;	/* keycode, unicode value or keysym */
पूर्ण;

बाह्य पूर्णांक रेजिस्टर_keyboard_notअगरier(काष्ठा notअगरier_block *nb);
बाह्य पूर्णांक unरेजिस्टर_keyboard_notअगरier(काष्ठा notअगरier_block *nb);
#पूर्ण_अगर
