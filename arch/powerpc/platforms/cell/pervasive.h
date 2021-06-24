<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Cell Pervasive Monitor and Debug पूर्णांकerface and HW काष्ठाures
 *
 * (C) Copyright IBM Corporation 2005
 *
 * Authors: Maximino Aguilar (maguilar@us.ibm.com)
 *          David J. Erb (djerb@us.ibm.com)
 */


#अगर_अघोषित PERVASIVE_H
#घोषणा PERVASIVE_H

बाह्य व्योम cbe_pervasive_init(व्योम);

#अगर_घोषित CONFIG_PPC_IBM_CELL_RESETBUTTON
बाह्य पूर्णांक cbe_sysreset_hack(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक cbe_sysreset_hack(व्योम)
अणु
	वापस 1;
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_IBM_CELL_RESETBUTTON */

#पूर्ण_अगर
