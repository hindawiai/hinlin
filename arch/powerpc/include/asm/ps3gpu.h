<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  PS3 GPU declarations.
 *
 *  Copyright 2009 Sony Corporation
 */

#अगर_अघोषित _ASM_POWERPC_PS3GPU_H
#घोषणा _ASM_POWERPC_PS3GPU_H

#समावेश <linux/mutex.h>

#समावेश <यंत्र/lv1call.h>


#घोषणा L1GPU_CONTEXT_ATTRIBUTE_DISPLAY_SYNC	0x101
#घोषणा L1GPU_CONTEXT_ATTRIBUTE_DISPLAY_FLIP	0x102

#घोषणा L1GPU_CONTEXT_ATTRIBUTE_FB_SETUP	0x600
#घोषणा L1GPU_CONTEXT_ATTRIBUTE_FB_BLIT		0x601
#घोषणा L1GPU_CONTEXT_ATTRIBUTE_FB_BLIT_SYNC	0x602
#घोषणा L1GPU_CONTEXT_ATTRIBUTE_FB_CLOSE	0x603

#घोषणा L1GPU_FB_BLIT_WAIT_FOR_COMPLETION	(1ULL << 32)

#घोषणा L1GPU_DISPLAY_SYNC_HSYNC		1
#घोषणा L1GPU_DISPLAY_SYNC_VSYNC		2


/* mutex synchronizing GPU accesses and video mode changes */
बाह्य काष्ठा mutex ps3_gpu_mutex;


अटल अंतरभूत पूर्णांक lv1_gpu_display_sync(u64 context_handle, u64 head,
				       u64 ddr_offset)
अणु
	वापस lv1_gpu_context_attribute(context_handle,
					 L1GPU_CONTEXT_ATTRIBUTE_DISPLAY_SYNC,
					 head, ddr_offset, 0, 0);
पूर्ण

अटल अंतरभूत पूर्णांक lv1_gpu_display_flip(u64 context_handle, u64 head,
				       u64 ddr_offset)
अणु
	वापस lv1_gpu_context_attribute(context_handle,
					 L1GPU_CONTEXT_ATTRIBUTE_DISPLAY_FLIP,
					 head, ddr_offset, 0, 0);
पूर्ण

अटल अंतरभूत पूर्णांक lv1_gpu_fb_setup(u64 context_handle, u64 xdr_lpar,
				   u64 xdr_size, u64 ioअगर_offset)
अणु
	वापस lv1_gpu_context_attribute(context_handle,
					 L1GPU_CONTEXT_ATTRIBUTE_FB_SETUP,
					 xdr_lpar, xdr_size, ioअगर_offset, 0);
पूर्ण

अटल अंतरभूत पूर्णांक lv1_gpu_fb_blit(u64 context_handle, u64 ddr_offset,
				  u64 ioअगर_offset, u64 sync_width, u64 pitch)
अणु
	वापस lv1_gpu_context_attribute(context_handle,
					 L1GPU_CONTEXT_ATTRIBUTE_FB_BLIT,
					 ddr_offset, ioअगर_offset, sync_width,
					 pitch);
पूर्ण

अटल अंतरभूत पूर्णांक lv1_gpu_fb_बंद(u64 context_handle)
अणु
	वापस lv1_gpu_context_attribute(context_handle,
					 L1GPU_CONTEXT_ATTRIBUTE_FB_CLOSE, 0,
					 0, 0, 0);
पूर्ण

#पूर्ण_अगर /* _ASM_POWERPC_PS3GPU_H */
