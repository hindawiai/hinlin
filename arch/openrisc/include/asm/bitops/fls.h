<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * OpenRISC Linux
 *
 * Copyright (C) 2010-2011 Jonas Bonn <jonas@southpole.se>
 */

#अगर_अघोषित __ASM_OPENRISC_FLS_H
#घोषणा __ASM_OPENRISC_FLS_H


#अगर_घोषित CONFIG_OPENRISC_HAVE_INST_FL1

अटल अंतरभूत पूर्णांक fls(अचिन्हित पूर्णांक x)
अणु
	पूर्णांक ret;

	__यंत्र__ ("l.fl1 %0,%1"
		 : "=r" (ret)
		 : "r" (x));

	वापस ret;
पूर्ण

#अन्यथा
#समावेश <यंत्र-generic/bitops/fls.h>
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_OPENRISC_FLS_H */
