<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _ARCH_X86_KERNEL_SYSFB_H
#घोषणा _ARCH_X86_KERNEL_SYSFB_H

/*
 * Generic System Framebuffers on x86
 * Copyright (c) 2012-2013 David Herrmann <dh.herrmann@gmail.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_data/simplefb.h>
#समावेश <linux/screen_info.h>

क्रमागत अणु
	M_I17,		/* 17-Inch iMac */
	M_I20,		/* 20-Inch iMac */
	M_I20_SR,	/* 20-Inch iMac (Santa Rosa) */
	M_I24,		/* 24-Inch iMac */
	M_I24_8_1,	/* 24-Inch iMac, 8,1th gen */
	M_I24_10_1,	/* 24-Inch iMac, 10,1th gen */
	M_I27_11_1,	/* 27-Inch iMac, 11,1th gen */
	M_MINI,		/* Mac Mini */
	M_MINI_3_1,	/* Mac Mini, 3,1th gen */
	M_MINI_4_1,	/* Mac Mini, 4,1th gen */
	M_MB,		/* MacBook */
	M_MB_2,		/* MacBook, 2nd rev. */
	M_MB_3,		/* MacBook, 3rd rev. */
	M_MB_5_1,	/* MacBook, 5th rev. */
	M_MB_6_1,	/* MacBook, 6th rev. */
	M_MB_7_1,	/* MacBook, 7th rev. */
	M_MB_SR,	/* MacBook, 2nd gen, (Santa Rosa) */
	M_MBA,		/* MacBook Air */
	M_MBA_3,	/* Macbook Air, 3rd rev */
	M_MBP,		/* MacBook Pro */
	M_MBP_2,	/* MacBook Pro 2nd gen */
	M_MBP_2_2,	/* MacBook Pro 2,2nd gen */
	M_MBP_SR,	/* MacBook Pro (Santa Rosa) */
	M_MBP_4,	/* MacBook Pro, 4th gen */
	M_MBP_5_1,	/* MacBook Pro, 5,1th gen */
	M_MBP_5_2,	/* MacBook Pro, 5,2th gen */
	M_MBP_5_3,	/* MacBook Pro, 5,3rd gen */
	M_MBP_6_1,	/* MacBook Pro, 6,1th gen */
	M_MBP_6_2,	/* MacBook Pro, 6,2th gen */
	M_MBP_7_1,	/* MacBook Pro, 7,1th gen */
	M_MBP_8_2,	/* MacBook Pro, 8,2nd gen */
	M_UNKNOWN	/* placeholder */
पूर्ण;

काष्ठा efअगरb_dmi_info अणु
	अक्षर *optname;
	अचिन्हित दीर्घ base;
	पूर्णांक stride;
	पूर्णांक width;
	पूर्णांक height;
	पूर्णांक flags;
पूर्ण;

#अगर_घोषित CONFIG_EFI

बाह्य काष्ठा efअगरb_dmi_info efअगरb_dmi_list[];
व्योम sysfb_apply_efi_quirks(व्योम);

#अन्यथा /* CONFIG_EFI */

अटल अंतरभूत व्योम sysfb_apply_efi_quirks(व्योम)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_EFI */

#अगर_घोषित CONFIG_X86_SYSFB

bool parse_mode(स्थिर काष्ठा screen_info *si,
		काष्ठा simplefb_platक्रमm_data *mode);
पूर्णांक create_simplefb(स्थिर काष्ठा screen_info *si,
		    स्थिर काष्ठा simplefb_platक्रमm_data *mode);

#अन्यथा /* CONFIG_X86_SYSFB */

अटल अंतरभूत bool parse_mode(स्थिर काष्ठा screen_info *si,
			      काष्ठा simplefb_platक्रमm_data *mode)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक create_simplefb(स्थिर काष्ठा screen_info *si,
				  स्थिर काष्ठा simplefb_platक्रमm_data *mode)
अणु
	वापस -EINVAL;
पूर्ण

#पूर्ण_अगर /* CONFIG_X86_SYSFB */

#पूर्ण_अगर /* _ARCH_X86_KERNEL_SYSFB_H */
