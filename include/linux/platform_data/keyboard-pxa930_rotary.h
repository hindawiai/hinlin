<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_ARCH_PXA930_ROTARY_H
#घोषणा __ASM_ARCH_PXA930_ROTARY_H

/* NOTE:
 *
 * rotary can be either पूर्णांकerpreted as a ralative input event (e.g.
 * REL_WHEEL or REL_HWHEEL) or a specअगरic key event (e.g. UP/DOWN
 * or LEFT/RIGHT), depending on अगर up_key & करोwn_key are asचिन्हित
 * or rel_code is asचिन्हित a non-zero value. When all are non-zero,
 * up_key and करोwn_key will be preferred.
 */
काष्ठा pxa930_rotary_platक्रमm_data अणु
	पूर्णांक	up_key;
	पूर्णांक	करोwn_key;
	पूर्णांक	rel_code;
पूर्ण;

व्योम __init pxa930_set_rotarykey_info(काष्ठा pxa930_rotary_platक्रमm_data *info);

#पूर्ण_अगर /* __ASM_ARCH_PXA930_ROTARY_H */
