<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * VRFB Rotation Engine
 *
 * Copyright (C) 2009 Nokia Corporation
 * Author: Tomi Valkeinen <tomi.valkeinen@nokia.com>
 */

#अगर_अघोषित __OMAP_VRFB_H__
#घोषणा __OMAP_VRFB_H__

#घोषणा OMAP_VRFB_LINE_LEN 2048

काष्ठा vrfb अणु
	u8 context;
	व्योम __iomem *vaddr[4];
	अचिन्हित दीर्घ paddr[4];
	u16 xres;
	u16 yres;
	u16 xoffset;
	u16 yoffset;
	u8 bytespp;
	bool yuv_mode;
पूर्ण;

#अगर_घोषित CONFIG_OMAP2_VRFB
बाह्य bool omap_vrfb_supported(व्योम);
बाह्य पूर्णांक omap_vrfb_request_ctx(काष्ठा vrfb *vrfb);
बाह्य व्योम omap_vrfb_release_ctx(काष्ठा vrfb *vrfb);
बाह्य व्योम omap_vrfb_adjust_size(u16 *width, u16 *height,
		u8 bytespp);
बाह्य u32 omap_vrfb_min_phys_size(u16 width, u16 height, u8 bytespp);
बाह्य u16 omap_vrfb_max_height(u32 phys_size, u16 width, u8 bytespp);
बाह्य व्योम omap_vrfb_setup(काष्ठा vrfb *vrfb, अचिन्हित दीर्घ paddr,
		u16 width, u16 height,
		अचिन्हित bytespp, bool yuv_mode);
बाह्य पूर्णांक omap_vrfb_map_angle(काष्ठा vrfb *vrfb, u16 height, u8 rot);
बाह्य व्योम omap_vrfb_restore_context(व्योम);

#अन्यथा
अटल अंतरभूत bool omap_vrfb_supported(व्योम) अणु वापस false; पूर्ण
अटल अंतरभूत पूर्णांक omap_vrfb_request_ctx(काष्ठा vrfb *vrfb) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम omap_vrfb_release_ctx(काष्ठा vrfb *vrfb) अणुपूर्ण
अटल अंतरभूत व्योम omap_vrfb_adjust_size(u16 *width, u16 *height,
		u8 bytespp) अणुपूर्ण
अटल अंतरभूत u32 omap_vrfb_min_phys_size(u16 width, u16 height, u8 bytespp)
		अणु वापस 0; पूर्ण
अटल अंतरभूत u16 omap_vrfb_max_height(u32 phys_size, u16 width, u8 bytespp)
		अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम omap_vrfb_setup(काष्ठा vrfb *vrfb, अचिन्हित दीर्घ paddr,
		u16 width, u16 height, अचिन्हित bytespp, bool yuv_mode) अणुपूर्ण
अटल अंतरभूत पूर्णांक omap_vrfb_map_angle(काष्ठा vrfb *vrfb, u16 height, u8 rot)
		अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम omap_vrfb_restore_context(व्योम) अणुपूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* __VRFB_H */
