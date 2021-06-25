<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_घोषित CONFIG_FB_WMT_GE_ROPS

बाह्य व्योम wmt_ge_fillrect(काष्ठा fb_info *info,
			    स्थिर काष्ठा fb_fillrect *rect);
बाह्य व्योम wmt_ge_copyarea(काष्ठा fb_info *info,
			    स्थिर काष्ठा fb_copyarea *area);
बाह्य पूर्णांक wmt_ge_sync(काष्ठा fb_info *info);

#अन्यथा

अटल अंतरभूत पूर्णांक wmt_ge_sync(काष्ठा fb_info *p)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम wmt_ge_fillrect(काष्ठा fb_info *p,
				    स्थिर काष्ठा fb_fillrect *rect)
अणु
	sys_fillrect(p, rect);
पूर्ण

अटल अंतरभूत व्योम wmt_ge_copyarea(काष्ठा fb_info *p,
				     स्थिर काष्ठा fb_copyarea *area)
अणु
	sys_copyarea(p, area);
पूर्ण

#पूर्ण_अगर
