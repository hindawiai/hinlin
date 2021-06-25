<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __MATROXFB_MISC_H__
#घोषणा __MATROXFB_MISC_H__

#समावेश "matroxfb_base.h"

/* also क्रम modules */
पूर्णांक matroxfb_PLL_calcघड़ी(स्थिर काष्ठा matrox_pll_features* pll, अचिन्हित पूर्णांक freq, अचिन्हित पूर्णांक fmax,
	अचिन्हित पूर्णांक* in, अचिन्हित पूर्णांक* feed, अचिन्हित पूर्णांक* post);
अटल अंतरभूत पूर्णांक PLL_calcघड़ी(स्थिर काष्ठा matrox_fb_info *minfo,
				अचिन्हित पूर्णांक freq, अचिन्हित पूर्णांक fmax,
				अचिन्हित पूर्णांक *in, अचिन्हित पूर्णांक *feed,
				अचिन्हित पूर्णांक *post)
अणु
	वापस matroxfb_PLL_calcघड़ी(&minfo->features.pll, freq, fmax, in, feed, post);
पूर्ण

पूर्णांक matroxfb_vgaHWinit(काष्ठा matrox_fb_info *minfo, काष्ठा my_timming* m);
व्योम matroxfb_vgaHWrestore(काष्ठा matrox_fb_info *minfo);
व्योम matroxfb_पढ़ो_pins(काष्ठा matrox_fb_info *minfo);

#पूर्ण_अगर	/* __MATROXFB_MISC_H__ */
