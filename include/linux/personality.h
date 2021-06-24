<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_PERSONALITY_H
#घोषणा _LINUX_PERSONALITY_H

#समावेश <uapi/linux/personality.h>

/*
 * Return the base personality without flags.
 */
#घोषणा personality(pers)	(pers & PER_MASK)

/*
 * Change personality of the currently running process.
 */
#घोषणा set_personality(pers)	(current->personality = (pers))

#पूर्ण_अगर /* _LINUX_PERSONALITY_H */
