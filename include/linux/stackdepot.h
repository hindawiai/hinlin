<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * A generic stack depot implementation
 *
 * Author: Alexander Potapenko <glider@google.com>
 * Copyright (C) 2016 Google, Inc.
 *
 * Based on code by Dmitry Chernenkov.
 */

#अगर_अघोषित _LINUX_STACKDEPOT_H
#घोषणा _LINUX_STACKDEPOT_H

प्रकार u32 depot_stack_handle_t;

depot_stack_handle_t stack_depot_save(अचिन्हित दीर्घ *entries,
				      अचिन्हित पूर्णांक nr_entries, gfp_t gfp_flags);

अचिन्हित पूर्णांक stack_depot_fetch(depot_stack_handle_t handle,
			       अचिन्हित दीर्घ **entries);

अचिन्हित पूर्णांक filter_irq_stacks(अचिन्हित दीर्घ *entries, अचिन्हित पूर्णांक nr_entries);

#अगर_घोषित CONFIG_STACKDEPOT
पूर्णांक stack_depot_init(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक stack_depot_init(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर	/* CONFIG_STACKDEPOT */

#पूर्ण_अगर
