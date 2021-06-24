<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __MATROXFB_CRTC2_H__
#घोषणा __MATROXFB_CRTC2_H__

#समावेश <linux/ioctl.h>
#समावेश "matroxfb_base.h"

काष्ठा matroxfb_dh_fb_info अणु
	काष्ठा fb_info		fbcon;
	पूर्णांक			fbcon_रेजिस्टरed;
	पूर्णांक                     initialized;

	काष्ठा matrox_fb_info*	primary_dev;

	काष्ठा अणु
		अचिन्हित दीर्घ	base;	/* physical */
		vaddr_t		vbase;	/* भव */
		अचिन्हित पूर्णांक	len;
		अचिन्हित पूर्णांक	len_usable;
		अचिन्हित पूर्णांक	len_maximum;
		अचिन्हित पूर्णांक 	offbase;
		अचिन्हित पूर्णांक	borrowed;
			      पूर्ण video;
	काष्ठा अणु
		अचिन्हित दीर्घ	base;
		vaddr_t		vbase;
		अचिन्हित पूर्णांक	len;
			      पूर्ण mmio;

	अचिन्हित पूर्णांक		पूर्णांकerlaced:1;

	u_पूर्णांक32_t cmap[16];
पूर्ण;

#पूर्ण_अगर /* __MATROXFB_CRTC2_H__ */
