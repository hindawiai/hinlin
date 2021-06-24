<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVIF_CL0046_H__
#घोषणा __NVIF_CL0046_H__

#घोषणा NV04_DISP_NTFY_VBLANK                                              0x00
#घोषणा NV04_DISP_NTFY_CONN                                                0x01

काष्ठा nv04_disp_mthd_v0 अणु
	__u8  version;
#घोषणा NV04_DISP_SCANOUTPOS                                               0x00
	__u8  method;
	__u8  head;
	__u8  pad03[5];
पूर्ण;

काष्ठा nv04_disp_scanoutpos_v0 अणु
	__u8  version;
	__u8  pad01[7];
	__s64 समय[2];
	__u16 vblanks;
	__u16 vblanke;
	__u16 vtotal;
	__u16 vline;
	__u16 hblanks;
	__u16 hblanke;
	__u16 htotal;
	__u16 hline;
पूर्ण;
#पूर्ण_अगर
