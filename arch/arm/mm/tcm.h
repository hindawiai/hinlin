<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2008-2009 ST-Ericsson AB
 * TCM memory handling क्रम ARM प्रणालीs
 *
 * Author: Linus Walleij <linus.walleij@stericsson.com>
 * Author: Rickard Andersson <rickard.andersson@stericsson.com>
 */

#अगर_घोषित CONFIG_HAVE_TCM
व्योम __init tcm_init(व्योम);
#अन्यथा
/* No TCM support, just blank अंतरभूतs to be optimized out */
अटल अंतरभूत व्योम tcm_init(व्योम)
अणु
पूर्ण
#पूर्ण_अगर
