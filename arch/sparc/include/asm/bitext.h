<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * bitext.h: Bit string operations on the sparc, specअगरic to architecture.
 *
 * Copyright 2002 Pete Zaitcev <zaitcev@yahoo.com>
 */

#अगर_अघोषित _SPARC_BITEXT_H
#घोषणा _SPARC_BITEXT_H

#समावेश <linux/spinlock.h>

काष्ठा bit_map अणु
	spinlock_t lock;
	अचिन्हित दीर्घ *map;
	पूर्णांक size;
	पूर्णांक used;
	पूर्णांक last_off;
	पूर्णांक last_size;
	पूर्णांक first_मुक्त;
	पूर्णांक num_colors;
पूर्ण;

पूर्णांक bit_map_string_get(काष्ठा bit_map *t, पूर्णांक len, पूर्णांक align);
व्योम bit_map_clear(काष्ठा bit_map *t, पूर्णांक offset, पूर्णांक len);
व्योम bit_map_init(काष्ठा bit_map *t, अचिन्हित दीर्घ *map, पूर्णांक size);

#पूर्ण_अगर /* defined(_SPARC_BITEXT_H) */
