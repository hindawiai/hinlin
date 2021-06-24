<शैली गुरु>
/*
 *  linux/drivers/video/kyro/kryo.h
 *
 *  Copyright (C) 2002 STMicroelectronics
 *  Copyright (C) 2004 Paul Mundt
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

#अगर_अघोषित _KYRO_H
#घोषणा _KYRO_H

काष्ठा kyrofb_info अणु
	व्योम __iomem *regbase;

	u32 palette[16];
	u32 HTot;	/* Hor Total Time    */
	u32 HFP;	/* Hor Front Porch   */
	u32 HST;	/* Hor Sync Time     */
	u32 HBP;	/* Hor Back Porch    */
	s32 HSP;		/* Hor Sync Polarity */
	u32 VTot;	/* Ver Total Time    */
	u32 VFP;	/* Ver Front Porch   */
	u32 VST;	/* Ver Sync Time     */
	u32 VBP;	/* Ver Back Porch    */
	s32 VSP;		/* Ver Sync Polarity */
	u32 XRES;	/* X Resolution      */
	u32 YRES;	/* Y Resolution      */
	u32 VFREQ;	/* Ver Frequency     */
	u32 PIXCLK;	/* Pixel Clock       */
	u32 HCLK;	/* Hor Clock         */

	/* Useful to hold depth here क्रम Linux */
	u8 PIXDEPTH;

	पूर्णांक wc_cookie;
पूर्ण;

बाह्य पूर्णांक kyro_dev_init(व्योम);
बाह्य व्योम kyro_dev_reset(व्योम);

बाह्य अचिन्हित अक्षर *kyro_dev_physical_fb_ptr(व्योम);
बाह्य अचिन्हित अक्षर *kyro_dev_भव_fb_ptr(व्योम);
बाह्य व्योम *kyro_dev_physical_regs_ptr(व्योम);
बाह्य व्योम *kyro_dev_भव_regs_ptr(व्योम);
बाह्य अचिन्हित पूर्णांक kyro_dev_fb_size(व्योम);
बाह्य अचिन्हित पूर्णांक kyro_dev_regs_size(व्योम);

बाह्य u32 kyro_dev_overlay_offset(व्योम);

/*
 * benedict.gaster@superh.com
 * Added the follow IOCTLS क्रम the creation of overlay services...
 */
#घोषणा KYRO_IOC_MAGIC 'k'

#घोषणा KYRO_IOCTL_OVERLAY_CREATE       _IO(KYRO_IOC_MAGIC, 0)
#घोषणा KYRO_IOCTL_OVERLAY_VIEWPORT_SET _IO(KYRO_IOC_MAGIC, 1)
#घोषणा KYRO_IOCTL_SET_VIDEO_MODE       _IO(KYRO_IOC_MAGIC, 2)
#घोषणा KYRO_IOCTL_UVSTRIDE             _IO(KYRO_IOC_MAGIC, 3)
#घोषणा KYRO_IOCTL_OVERLAY_OFFSET       _IO(KYRO_IOC_MAGIC, 4)
#घोषणा KYRO_IOCTL_STRIDE               _IO(KYRO_IOC_MAGIC, 5)

/*
 * The follow 3 काष्ठाures are used to pass data from user space पूर्णांकo the kernel
 * क्रम the creation of overlay surfaces and setting the video mode.
 */
प्रकार काष्ठा _OVERLAY_CREATE अणु
	u32 ulWidth;
	u32 ulHeight;
	पूर्णांक bLinear;
पूर्ण overlay_create;

प्रकार काष्ठा _OVERLAY_VIEWPORT_SET अणु
	u32 xOrgin;
	u32 yOrgin;
	u32 xSize;
	u32 ySize;
पूर्ण overlay_viewport_set;

प्रकार काष्ठा _SET_VIDEO_MODE अणु
	u32 ulWidth;
	u32 ulHeight;
	u32 ulScan;
	u8 displayDepth;
	पूर्णांक bLinear;
पूर्ण set_video_mode;

#पूर्ण_अगर /* _KYRO_H */
