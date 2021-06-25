<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2021 Sअगरive.
 */

#अगर_अघोषित __ASM_ALTERNATIVE_H
#घोषणा __ASM_ALTERNATIVE_H

#घोषणा ERRATA_STRING_LENGTH_MAX 32

#समावेश <यंत्र/alternative-macros.h>

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/मानकघोष.स>
#समावेश <यंत्र/hwcap.h>

व्योम __init apply_boot_alternatives(व्योम);

काष्ठा alt_entry अणु
	व्योम *old_ptr;		 /* address of original instruciton or data  */
	व्योम *alt_ptr;		 /* address of replacement inकाष्ठाion or data */
	अचिन्हित दीर्घ venकरोr_id; /* cpu venकरोr id */
	अचिन्हित दीर्घ alt_len;   /* The replacement size */
	अचिन्हित पूर्णांक errata_id;  /* The errata id */
पूर्ण __packed;

काष्ठा errata_checkfunc_id अणु
	अचिन्हित दीर्घ venकरोr_id;
	bool (*func)(काष्ठा alt_entry *alt);
पूर्ण;

व्योम sअगरive_errata_patch_func(काष्ठा alt_entry *begin, काष्ठा alt_entry *end,
			      अचिन्हित दीर्घ archid, अचिन्हित दीर्घ impid);

#पूर्ण_अगर
#पूर्ण_अगर
