<शैली गुरु>
/*
 *  linux/drivers/video/kyro/STG4000Interface.h
 *
 *  Copyright (C) 2002 STMicroelectronics
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

#अगर_अघोषित _STG4000INTERFACE_H
#घोषणा _STG4000INTERFACE_H

#समावेश <linux/pci.h>
#समावेश <video/kyro.h>

/*
 * Ramdac Setup
 */
बाह्य पूर्णांक InitialiseRamdac(अस्थिर STG4000REG __iomem *pSTGReg, u32 displayDepth,
			    u32 displayWidth, u32 displayHeight,
			    s32 HSyncPolarity, s32 VSyncPolarity,
			    u32 *pixelClock);

बाह्य व्योम DisableRamdacOutput(अस्थिर STG4000REG __iomem *pSTGReg);
बाह्य व्योम EnableRamdacOutput(अस्थिर STG4000REG __iomem *pSTGReg);

/*
 * Timing generator setup
 */
बाह्य व्योम DisableVGA(अस्थिर STG4000REG __iomem *pSTGReg);
बाह्य व्योम StopVTG(अस्थिर STG4000REG __iomem *pSTGReg);
बाह्य व्योम StartVTG(अस्थिर STG4000REG __iomem *pSTGReg);
बाह्य व्योम SetupVTG(अस्थिर STG4000REG __iomem *pSTGReg,
		     स्थिर काष्ठा kyrofb_info * pTiming);

बाह्य u32 ProgramClock(u32 refClock, u32 coreClock, u32 *FOut, u32 *ROut, u32 *POut);
बाह्य पूर्णांक SetCoreClockPLL(अस्थिर STG4000REG __iomem *pSTGReg, काष्ठा pci_dev *pDev);

/*
 * Overlay setup
 */
बाह्य व्योम ResetOverlayRegisters(अस्थिर STG4000REG __iomem *pSTGReg);

बाह्य पूर्णांक CreateOverlaySurface(अस्थिर STG4000REG __iomem *pSTGReg,
				u32 ulWidth, u32 ulHeight,
				पूर्णांक bLinear,
				u32 ulOverlayOffset,
				u32 * retStride, u32 * retUVStride);

बाह्य पूर्णांक SetOverlayBlendMode(अस्थिर STG4000REG __iomem *pSTGReg,
			       OVRL_BLEND_MODE mode,
			       u32 ulAlpha, u32 ulColorKey);

बाह्य पूर्णांक SetOverlayViewPort(अस्थिर STG4000REG __iomem *pSTGReg,
			      u32 left, u32 top,
			      u32 right, u32 bottom);

बाह्य व्योम EnableOverlayPlane(अस्थिर STG4000REG __iomem *pSTGReg);

#पूर्ण_अगर /* _STG4000INTERFACE_H */
