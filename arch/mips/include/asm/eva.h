<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2014, Imagination Technologies Ltd.
 *
 * EVA functions क्रम generic code
 */

#अगर_अघोषित _ASM_EVA_H
#घोषणा _ASM_EVA_H

#समावेश <kernel-entry-init.h>

#अगर_घोषित __ASSEMBLY__

#अगर_घोषित CONFIG_EVA

/*
 * EVA early init code
 *
 * Platक्रमms must define their own 'platform_eva_init' macro in
 * their kernel-entry-init.h header. This macro usually करोes the
 * platक्रमm specअगरic configuration of the segmentation रेजिस्टरs,
 * and it is normally called from assembly code.
 *
 */

.macro eva_init
platक्रमm_eva_init
.endm

#अन्यथा

.macro eva_init
.endm

#पूर्ण_अगर /* CONFIG_EVA */

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर
