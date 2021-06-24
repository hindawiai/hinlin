<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * OpenRISC Linux
 *
 * Copyright (C) 2010-2011 Jonas Bonn <jonas@southpole.se>
 */

#अगर_अघोषित __ASM_OPENRISC_FFS_H
#घोषणा __ASM_OPENRISC_FFS_H

#अगर_घोषित CONFIG_OPENRISC_HAVE_INST_FF1

अटल अंतरभूत पूर्णांक ffs(पूर्णांक x)
अणु
	पूर्णांक ret;

	__यंत्र__ ("l.ff1 %0,%1"
		 : "=r" (ret)
		 : "r" (x));

	वापस ret;
पूर्ण

#अन्यथा
#समावेश <यंत्र-generic/bitops/ffs.h>
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_OPENRISC_FFS_H */
