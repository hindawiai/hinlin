<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * drivers/video/geode/geodefb.h
 *   -- Geode framebuffer driver
 *
 * Copyright (C) 2005 Arcom Control Systems Ltd.
 */
#अगर_अघोषित __GEODEFB_H__
#घोषणा __GEODEFB_H__

काष्ठा geodefb_info;

काष्ठा geode_dc_ops अणु
	व्योम (*set_mode)(काष्ठा fb_info *);
	व्योम (*set_palette_reg)(काष्ठा fb_info *, अचिन्हित, अचिन्हित, अचिन्हित, अचिन्हित);
पूर्ण;

काष्ठा geode_vid_ops अणु
	व्योम (*set_dclk)(काष्ठा fb_info *);
	व्योम (*configure_display)(काष्ठा fb_info *);
	पूर्णांक  (*blank_display)(काष्ठा fb_info *, पूर्णांक blank_mode);
पूर्ण;

काष्ठा geodefb_par अणु
	पूर्णांक enable_crt;
	पूर्णांक panel_x; /* dimensions of an attached flat panel, non-zero => enable panel */
	पूर्णांक panel_y;
	व्योम __iomem *dc_regs;
	व्योम __iomem *vid_regs;
	स्थिर काष्ठा geode_dc_ops  *dc_ops;
	स्थिर काष्ठा geode_vid_ops *vid_ops;
पूर्ण;

#पूर्ण_अगर /* !__GEODEFB_H__ */
