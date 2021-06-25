<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Secure boot definitions
 *
 * Copyright (C) 2019 IBM Corporation
 * Author: Nayna Jain
 */
#अगर_अघोषित _ASM_POWER_SECURE_BOOT_H
#घोषणा _ASM_POWER_SECURE_BOOT_H

#अगर_घोषित CONFIG_PPC_SECURE_BOOT

bool is_ppc_secureboot_enabled(व्योम);
bool is_ppc_trustedboot_enabled(व्योम);

#अन्यथा

अटल अंतरभूत bool is_ppc_secureboot_enabled(व्योम)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool is_ppc_trustedboot_enabled(व्योम)
अणु
	वापस false;
पूर्ण

#पूर्ण_अगर
#पूर्ण_अगर
