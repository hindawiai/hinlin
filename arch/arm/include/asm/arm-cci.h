<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * arch/arm/include/यंत्र/arm-cci.h
 *
 * Copyright (C) 2015 ARM Ltd.
 */

#अगर_अघोषित __ASM_ARM_CCI_H
#घोषणा __ASM_ARM_CCI_H

#अगर_घोषित CONFIG_MCPM
#समावेश <यंत्र/mcpm.h>

/*
 * We करोn't have a reliable way of detecting whether,
 * अगर we have access to secure-only रेजिस्टरs, unless
 * mcpm is रेजिस्टरed.
 */
अटल अंतरभूत bool platक्रमm_has_secure_cci_access(व्योम)
अणु
	वापस mcpm_is_available();
पूर्ण

#अन्यथा
अटल अंतरभूत bool platक्रमm_has_secure_cci_access(व्योम)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
