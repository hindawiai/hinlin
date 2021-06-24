<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __MMU_H
#घोषणा __MMU_H

/*
 * Type क्रम a context number.  We declare it अस्थिर to ensure proper
 * ordering when it's accessed outside of spinlock'd critical sections
 * (e.g., as करोne in activate_mm() and init_new_context()).
 */
प्रकार अस्थिर अचिन्हित दीर्घ mm_context_t;

प्रकार अचिन्हित दीर्घ nv_mm_context_t;

#पूर्ण_अगर
