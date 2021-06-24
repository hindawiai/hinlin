<शैली गुरु>
/*-*- linux-c -*-
 *  linux/drivers/video/i810fb_मुख्य.h -- Intel 810 frame buffer device 
 *                                       मुख्य header file
 *
 *      Copyright (C) 2001 Antonino Daplas<adaplas@pol.net>
 *      All Rights Reserved      
 *
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License. See the file COPYING in the मुख्य directory of this archive क्रम
 *  more details.
 */

#अगर_अघोषित __I810_MAIN_H__
#घोषणा __I810_MAIN_H__

/* Video Timings */
बाह्य व्योम round_off_xres         (u32 *xres);
बाह्य व्योम round_off_yres         (u32 *xres, u32 *yres);
बाह्य u32 i810_get_watermark      (स्थिर काष्ठा fb_var_screeninfo *var,
			            काष्ठा i810fb_par *par);
बाह्य व्योम i810fb_encode_रेजिस्टरs(स्थिर काष्ठा fb_var_screeninfo *var,
				    काष्ठा i810fb_par *par, u32 xres, u32 yres);
बाह्य व्योम i810fb_fill_var_timings(काष्ठा fb_var_screeninfo *var);
				    
/* Accelerated Functions */
बाह्य व्योम i810fb_fillrect (काष्ठा fb_info *p, 
			     स्थिर काष्ठा fb_fillrect *rect);
बाह्य व्योम i810fb_copyarea (काष्ठा fb_info *p, 
			     स्थिर काष्ठा fb_copyarea *region);
बाह्य व्योम i810fb_imageblit(काष्ठा fb_info *p, स्थिर काष्ठा fb_image *image);
बाह्य पूर्णांक  i810fb_sync     (काष्ठा fb_info *p);

बाह्य व्योम i810fb_init_ringbuffer(काष्ठा fb_info *info);
बाह्य व्योम i810fb_load_front     (u32 offset, काष्ठा fb_info *info);

#अगर_घोषित CONFIG_FB_I810_I2C
/* I2C */
बाह्य पूर्णांक i810_probe_i2c_connector(काष्ठा fb_info *info, u8 **out_edid,
				    पूर्णांक conn);
बाह्य व्योम i810_create_i2c_busses(काष्ठा i810fb_par *par);
बाह्य व्योम i810_delete_i2c_busses(काष्ठा i810fb_par *par);
#अन्यथा
अटल अंतरभूत पूर्णांक i810_probe_i2c_connector(काष्ठा fb_info *info, u8 **out_edid,
				    पूर्णांक conn)
अणु
	वापस 1;
पूर्ण
अटल अंतरभूत व्योम i810_create_i2c_busses(काष्ठा i810fb_par *par) अणु पूर्ण
अटल अंतरभूत व्योम i810_delete_i2c_busses(काष्ठा i810fb_par *par) अणु पूर्ण
#पूर्ण_अगर

/* Conditionals */
#अगर_घोषित CONFIG_X86
अटल अंतरभूत व्योम flush_cache(व्योम)
अणु
	यंत्र अस्थिर ("wbinvd":::"memory");
पूर्ण
#अन्यथा
#घोषणा flush_cache() करो अणु पूर्ण जबतक(0)
#पूर्ण_अगर 

#अगर_घोषित CONFIG_FB_I810_GTF
#घोषणा IS_DVT (0)
#अन्यथा
#घोषणा IS_DVT (1)
#पूर्ण_अगर

#पूर्ण_अगर /* __I810_MAIN_H__ */
