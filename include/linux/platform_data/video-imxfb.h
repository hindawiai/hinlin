<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * This काष्ठाure describes the machine which we are running on.
 */
#अगर_अघोषित __MACH_IMXFB_H__
#घोषणा __MACH_IMXFB_H__

#समावेश <linux/fb.h>

#घोषणा PCR_TFT		(1 << 31)
#घोषणा PCR_COLOR	(1 << 30)
#घोषणा PCR_PBSIZ_1	(0 << 28)
#घोषणा PCR_PBSIZ_2	(1 << 28)
#घोषणा PCR_PBSIZ_4	(2 << 28)
#घोषणा PCR_PBSIZ_8	(3 << 28)
#घोषणा PCR_BPIX_1	(0 << 25)
#घोषणा PCR_BPIX_2	(1 << 25)
#घोषणा PCR_BPIX_4	(2 << 25)
#घोषणा PCR_BPIX_8	(3 << 25)
#घोषणा PCR_BPIX_12	(4 << 25)
#घोषणा PCR_BPIX_16	(5 << 25)
#घोषणा PCR_BPIX_18	(6 << 25)
#घोषणा PCR_PIXPOL	(1 << 24)
#घोषणा PCR_FLMPOL	(1 << 23)
#घोषणा PCR_LPPOL	(1 << 22)
#घोषणा PCR_CLKPOL	(1 << 21)
#घोषणा PCR_OEPOL	(1 << 20)
#घोषणा PCR_SCLKIDLE	(1 << 19)
#घोषणा PCR_END_SEL	(1 << 18)
#घोषणा PCR_END_BYTE_SWAP (1 << 17)
#घोषणा PCR_REV_VS	(1 << 16)
#घोषणा PCR_ACD_SEL	(1 << 15)
#घोषणा PCR_ACD(x)	(((x) & 0x7f) << 8)
#घोषणा PCR_SCLK_SEL	(1 << 7)
#घोषणा PCR_SHARP	(1 << 6)
#घोषणा PCR_PCD(x)	((x) & 0x3f)

#घोषणा PWMR_CLS(x)	(((x) & 0x1ff) << 16)
#घोषणा PWMR_LDMSK	(1 << 15)
#घोषणा PWMR_SCR1	(1 << 10)
#घोषणा PWMR_SCR0	(1 << 9)
#घोषणा PWMR_CC_EN	(1 << 8)
#घोषणा PWMR_PW(x)	((x) & 0xff)

#घोषणा LSCR1_PS_RISE_DELAY(x)    (((x) & 0x7f) << 26)
#घोषणा LSCR1_CLS_RISE_DELAY(x)   (((x) & 0x3f) << 16)
#घोषणा LSCR1_REV_TOGGLE_DELAY(x) (((x) & 0xf) << 8)
#घोषणा LSCR1_GRAY2(x)            (((x) & 0xf) << 4)
#घोषणा LSCR1_GRAY1(x)            (((x) & 0xf))

काष्ठा imx_fb_videomode अणु
	काष्ठा fb_videomode mode;
	u32 pcr;
	bool aus_mode;
	अचिन्हित अक्षर	bpp;
पूर्ण;

काष्ठा imx_fb_platक्रमm_data अणु
	काष्ठा imx_fb_videomode *mode;
	पूर्णांक		num_modes;

	u_पूर्णांक		pwmr;
	u_पूर्णांक		lscr1;
	u_पूर्णांक		dmacr;

	पूर्णांक (*init)(काष्ठा platक्रमm_device *);
	व्योम (*निकास)(काष्ठा platक्रमm_device *);
पूर्ण;

#पूर्ण_अगर /* अगरndef __MACH_IMXFB_H__ */
