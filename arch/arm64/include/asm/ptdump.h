<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2014 ARM Ltd.
 */
#अगर_अघोषित __ASM_PTDUMP_H
#घोषणा __ASM_PTDUMP_H

#अगर_घोषित CONFIG_PTDUMP_CORE

#समावेश <linux/mm_types.h>
#समावेश <linux/seq_file.h>

काष्ठा addr_marker अणु
	अचिन्हित दीर्घ start_address;
	अक्षर *name;
पूर्ण;

काष्ठा ptdump_info अणु
	काष्ठा mm_काष्ठा		*mm;
	स्थिर काष्ठा addr_marker	*markers;
	अचिन्हित दीर्घ			base_addr;
पूर्ण;

व्योम ptdump_walk(काष्ठा seq_file *s, काष्ठा ptdump_info *info);
#अगर_घोषित CONFIG_PTDUMP_DEBUGFS
व्योम __init ptdump_debugfs_रेजिस्टर(काष्ठा ptdump_info *info, स्थिर अक्षर *name);
#अन्यथा
अटल अंतरभूत व्योम ptdump_debugfs_रेजिस्टर(काष्ठा ptdump_info *info,
					   स्थिर अक्षर *name) अणु पूर्ण
#पूर्ण_अगर
व्योम ptdump_check_wx(व्योम);
#पूर्ण_अगर /* CONFIG_PTDUMP_CORE */

#अगर_घोषित CONFIG_DEBUG_WX
#घोषणा debug_checkwx()	ptdump_check_wx()
#अन्यथा
#घोषणा debug_checkwx()	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_PTDUMP_H */
