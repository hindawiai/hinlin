<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _PVCLOCK_GTOD_H
#घोषणा _PVCLOCK_GTOD_H

#समावेश <linux/notअगरier.h>

/*
 * The pvघड़ी gtod notअगरier is called when the प्रणाली समय is updated
 * and is used to keep guest समय synchronized with host समय.
 *
 * The 'action' parameter in the notअगरier function is false (0), or
 * true (non-zero) अगर प्रणाली समय was stepped.
 */
बाह्य पूर्णांक pvघड़ी_gtod_रेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb);
बाह्य पूर्णांक pvघड़ी_gtod_unरेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb);

#पूर्ण_अगर /* _PVCLOCK_GTOD_H */
