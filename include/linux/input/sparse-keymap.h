<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित _SPARSE_KEYMAP_H
#घोषणा _SPARSE_KEYMAP_H

/*
 * Copyright (c) 2009 Dmitry Torokhov
 */

#घोषणा KE_END		0	/* Indicates end of keymap */
#घोषणा KE_KEY		1	/* Ordinary key/button */
#घोषणा KE_SW		2	/* Switch (predetermined value) */
#घोषणा KE_VSW		3	/* Switch (value supplied at runसमय) */
#घोषणा KE_IGNORE	4	/* Known entry that should be ignored */
#घोषणा KE_LAST		KE_IGNORE

/**
 * काष्ठा key_entry - keymap entry क्रम use in sparse keymap
 * @type: Type of the key entry (KE_KEY, KE_SW, KE_VSW, KE_END);
 *	drivers are allowed to extend the list with their own
 *	निजी definitions.
 * @code: Device-specअगरic data identअगरying the button/चयन
 * @keycode: KEY_* code asचिन्हित to a key/button
 * @sw: काष्ठा with code/value used by KE_SW and KE_VSW
 * @sw.code: SW_* code asचिन्हित to a चयन
 * @sw.value: Value that should be sent in an input even when KE_SW
 *	चयन is toggled. KE_VSW चयनes ignore this field and
 *	expect driver to supply value क्रम the event.
 *
 * This काष्ठाure defines an entry in a sparse keymap used by some
 * input devices क्रम which traditional table-based approach is not
 * suitable.
 */
काष्ठा key_entry अणु
	पूर्णांक type;		/* See KE_* above */
	u32 code;
	जोड़ अणु
		u16 keycode;		/* For KE_KEY */
		काष्ठा अणु		/* For KE_SW, KE_VSW */
			u8 code;
			u8 value;	/* For KE_SW, ignored by KE_VSW */
		पूर्ण sw;
	पूर्ण;
पूर्ण;

काष्ठा key_entry *sparse_keymap_entry_from_scancode(काष्ठा input_dev *dev,
						    अचिन्हित पूर्णांक code);
काष्ठा key_entry *sparse_keymap_entry_from_keycode(काष्ठा input_dev *dev,
						   अचिन्हित पूर्णांक code);
पूर्णांक sparse_keymap_setup(काष्ठा input_dev *dev,
			स्थिर काष्ठा key_entry *keymap,
			पूर्णांक (*setup)(काष्ठा input_dev *, काष्ठा key_entry *));

व्योम sparse_keymap_report_entry(काष्ठा input_dev *dev, स्थिर काष्ठा key_entry *ke,
				अचिन्हित पूर्णांक value, bool स्वतःrelease);

bool sparse_keymap_report_event(काष्ठा input_dev *dev, अचिन्हित पूर्णांक code,
				अचिन्हित पूर्णांक value, bool स्वतःrelease);

#पूर्ण_अगर /* _SPARSE_KEYMAP_H */
