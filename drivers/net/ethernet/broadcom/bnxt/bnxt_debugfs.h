<शैली गुरु>
/* Broadcom NetXtreme-C/E network driver.
 *
 * Copyright (c) 2017-2018 Broadcom Limited
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 */

#समावेश "bnxt_hsi.h"
#समावेश "bnxt.h"

#अगर_घोषित CONFIG_DEBUG_FS
व्योम bnxt_debug_init(व्योम);
व्योम bnxt_debug_निकास(व्योम);
व्योम bnxt_debug_dev_init(काष्ठा bnxt *bp);
व्योम bnxt_debug_dev_निकास(काष्ठा bnxt *bp);
#अन्यथा
अटल अंतरभूत व्योम bnxt_debug_init(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम bnxt_debug_निकास(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम bnxt_debug_dev_init(काष्ठा bnxt *bp) अणुपूर्ण
अटल अंतरभूत व्योम bnxt_debug_dev_निकास(काष्ठा bnxt *bp) अणुपूर्ण
#पूर्ण_अगर
