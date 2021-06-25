<शैली गुरु>
/*
 * omap_vout_vrfb.h
 *
 * Copyright (C) 2010 Texas Instruments.
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2. This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 *
 */

#अगर_अघोषित OMAP_VOUT_VRFB_H
#घोषणा OMAP_VOUT_VRFB_H

#अगर_घोषित CONFIG_VIDEO_OMAP2_VOUT_VRFB
व्योम omap_vout_मुक्त_vrfb_buffers(काष्ठा omap_vout_device *vout);
पूर्णांक omap_vout_setup_vrfb_bufs(काष्ठा platक्रमm_device *pdev, पूर्णांक vid_num,
			bool अटल_vrfb_allocation);
व्योम omap_vout_release_vrfb(काष्ठा omap_vout_device *vout);
पूर्णांक omap_vout_vrfb_buffer_setup(काष्ठा omap_vout_device *vout,
			अचिन्हित पूर्णांक *count, अचिन्हित पूर्णांक startindex);
पूर्णांक omap_vout_prepare_vrfb(काष्ठा omap_vout_device *vout,
			काष्ठा vb2_buffer *vb);
व्योम omap_vout_calculate_vrfb_offset(काष्ठा omap_vout_device *vout);
#अन्यथा
अटल अंतरभूत व्योम omap_vout_मुक्त_vrfb_buffers(काष्ठा omap_vout_device *vout) अणु पूर्ण;
अटल अंतरभूत पूर्णांक omap_vout_setup_vrfb_bufs(काष्ठा platक्रमm_device *pdev, पूर्णांक vid_num,
			bool अटल_vrfb_allocation)
		अणु वापस 0; पूर्ण;
अटल अंतरभूत व्योम omap_vout_release_vrfb(काष्ठा omap_vout_device *vout) अणु पूर्ण;
अटल अंतरभूत पूर्णांक omap_vout_vrfb_buffer_setup(काष्ठा omap_vout_device *vout,
			अचिन्हित पूर्णांक *count, अचिन्हित पूर्णांक startindex)
		अणु वापस 0; पूर्ण;
अटल अंतरभूत पूर्णांक omap_vout_prepare_vrfb(काष्ठा omap_vout_device *vout,
			काष्ठा vb2_buffer *vb)
		अणु वापस 0; पूर्ण;
अटल अंतरभूत व्योम omap_vout_calculate_vrfb_offset(काष्ठा omap_vout_device *vout) अणु पूर्ण;
#पूर्ण_अगर

#पूर्ण_अगर
