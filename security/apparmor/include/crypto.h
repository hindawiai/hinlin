<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * AppArmor security module
 *
 * This file contains AppArmor policy loading पूर्णांकerface function definitions.
 *
 * Copyright 2013 Canonical Ltd.
 */

#अगर_अघोषित __APPARMOR_CRYPTO_H
#घोषणा __APPARMOR_CRYPTO_H

#समावेश "policy.h"

#अगर_घोषित CONFIG_SECURITY_APPARMOR_HASH
अचिन्हित पूर्णांक aa_hash_size(व्योम);
अक्षर *aa_calc_hash(व्योम *data, माप_प्रकार len);
पूर्णांक aa_calc_profile_hash(काष्ठा aa_profile *profile, u32 version, व्योम *start,
			 माप_प्रकार len);
#अन्यथा
अटल अंतरभूत अक्षर *aa_calc_hash(व्योम *data, माप_प्रकार len)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत पूर्णांक aa_calc_profile_hash(काष्ठा aa_profile *profile, u32 version,
				       व्योम *start, माप_प्रकार len)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक aa_hash_size(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __APPARMOR_CRYPTO_H */
