<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  linux/include/यंत्र/setup.h
 *
 *  Copyright (C) 1997-1999 Russell King
 *
 *  Structure passed to kernel to tell it about the
 *  hardware it's running on.  See Documentation/arm/setup.rst
 *  क्रम more info.
 */
#अगर_अघोषित __ASMARM_SETUP_H
#घोषणा __ASMARM_SETUP_H

#समावेश <uapi/यंत्र/setup.h>


#घोषणा __tag __used __section(".taglist.init")
#घोषणा __tagtable(tag, fn) \
अटल स्थिर काष्ठा tagtable __tagtable_##fn __tag = अणु tag, fn पूर्ण

बाह्य पूर्णांक arm_add_memory(u64 start, u64 size);
बाह्य व्योम early_prपूर्णांक(स्थिर अक्षर *str, ...);
बाह्य व्योम dump_machine_table(व्योम);

#अगर_घोषित CONFIG_ATAGS_PROC
बाह्य व्योम save_atags(स्थिर काष्ठा tag *tags);
#अन्यथा
अटल अंतरभूत व्योम save_atags(स्थिर काष्ठा tag *tags) अणु पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
