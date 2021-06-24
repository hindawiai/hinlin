<शैली गुरु>
/*
 *  linux/drivers/video/kyro/STG4000VTG.c
 *
 *  Copyright (C) 2002 STMicroelectronics
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/types.h>
#समावेश <video/kyro.h>

#समावेश "STG4000Reg.h"
#समावेश "STG4000Interface.h"

व्योम DisableVGA(अस्थिर STG4000REG __iomem *pSTGReg)
अणु
	u32 पंचांगp;
	अस्थिर u32 count = 0, i;

	/* Reset the VGA रेजिस्टरs */
	पंचांगp = STG_READ_REG(SoftwareReset);
	CLEAR_BIT(8);
	STG_WRITE_REG(SoftwareReset, पंचांगp);

	/* Just क्रम Delay */
	क्रम (i = 0; i < 1000; i++) अणु
		count++;
	पूर्ण

	/* Pull-out the VGA रेजिस्टरs from reset */
	पंचांगp = STG_READ_REG(SoftwareReset);
	पंचांगp |= SET_BIT(8);
	STG_WRITE_REG(SoftwareReset, पंचांगp);
पूर्ण

व्योम StopVTG(अस्थिर STG4000REG __iomem *pSTGReg)
अणु
	u32 पंचांगp = 0;

	/* Stop Ver and Hor Sync Generator */
	पंचांगp = (STG_READ_REG(DACSyncCtrl)) | SET_BIT(0) | SET_BIT(2);
	CLEAR_BIT(31);
	STG_WRITE_REG(DACSyncCtrl, पंचांगp);
पूर्ण

व्योम StartVTG(अस्थिर STG4000REG __iomem *pSTGReg)
अणु
	u32 पंचांगp = 0;

	/* Start Ver and Hor Sync Generator */
	पंचांगp = ((STG_READ_REG(DACSyncCtrl)) | SET_BIT(31));
	CLEAR_BIT(0);
	CLEAR_BIT(2);
	STG_WRITE_REG(DACSyncCtrl, पंचांगp);
पूर्ण

व्योम SetupVTG(अस्थिर STG4000REG __iomem *pSTGReg,
	      स्थिर काष्ठा kyrofb_info * pTiming)
अणु
	u32 पंचांगp = 0;
	u32 margins = 0;
	u32 ulBorder;
	u32 xRes = pTiming->XRES;
	u32 yRes = pTiming->YRES;

	/* Horizontal */
	u32 HAddrTime, HRightBorder, HLeftBorder;
	u32 HBackPorcStrt, HFrontPorchStrt, HTotal,
	    HLeftBorderStrt, HRightBorderStrt, HDisplayStrt;

	/* Vertical */
	u32 VDisplayStrt, VBottomBorder, VTopBorder;
	u32 VBackPorchStrt, VTotal, VTopBorderStrt,
	    VFrontPorchStrt, VBottomBorderStrt, VAddrTime;

	/* Need to calculate the right border */
	अगर ((xRes == 640) && (yRes == 480)) अणु
		अगर ((pTiming->VFREQ == 60) || (pTiming->VFREQ == 72)) अणु
			margins = 8;
		पूर्ण
	पूर्ण

	/* Work out the Border */
	ulBorder =
	    (pTiming->HTot -
	     (pTiming->HST + (pTiming->HBP - margins) + xRes +
	      (pTiming->HFP - margins))) >> 1;

	/* Border the same क्रम Vertical and Horizontal */
	VBottomBorder = HLeftBorder = VTopBorder = HRightBorder = ulBorder;

    /************ Get Timing values क्रम Horizontal ******************/
	HAddrTime = xRes;
	HBackPorcStrt = pTiming->HST;
	HTotal = pTiming->HTot;
	HDisplayStrt =
	    pTiming->HST + (pTiming->HBP - margins) + HLeftBorder;
	HLeftBorderStrt = HDisplayStrt - HLeftBorder;
	HFrontPorchStrt =
	    pTiming->HST + (pTiming->HBP - margins) + HLeftBorder +
	    HAddrTime + HRightBorder;
	HRightBorderStrt = HFrontPorchStrt - HRightBorder;

    /************ Get Timing values क्रम Vertical ******************/
	VAddrTime = yRes;
	VBackPorchStrt = pTiming->VST;
	VTotal = pTiming->VTot;
	VDisplayStrt =
	    pTiming->VST + (pTiming->VBP - margins) + VTopBorder;
	VTopBorderStrt = VDisplayStrt - VTopBorder;
	VFrontPorchStrt =
	    pTiming->VST + (pTiming->VBP - margins) + VTopBorder +
	    VAddrTime + VBottomBorder;
	VBottomBorderStrt = VFrontPorchStrt - VBottomBorder;

	/* Set Hor Timing 1, 2, 3 */
	पंचांगp = STG_READ_REG(DACHorTim1);
	CLEAR_BITS_FRM_TO(0, 11);
	CLEAR_BITS_FRM_TO(16, 27);
	पंचांगp |= (HTotal) | (HBackPorcStrt << 16);
	STG_WRITE_REG(DACHorTim1, पंचांगp);

	पंचांगp = STG_READ_REG(DACHorTim2);
	CLEAR_BITS_FRM_TO(0, 11);
	CLEAR_BITS_FRM_TO(16, 27);
	पंचांगp |= (HDisplayStrt << 16) | HLeftBorderStrt;
	STG_WRITE_REG(DACHorTim2, पंचांगp);

	पंचांगp = STG_READ_REG(DACHorTim3);
	CLEAR_BITS_FRM_TO(0, 11);
	CLEAR_BITS_FRM_TO(16, 27);
	पंचांगp |= (HFrontPorchStrt << 16) | HRightBorderStrt;
	STG_WRITE_REG(DACHorTim3, पंचांगp);

	/* Set Ver Timing 1, 2, 3 */
	पंचांगp = STG_READ_REG(DACVerTim1);
	CLEAR_BITS_FRM_TO(0, 11);
	CLEAR_BITS_FRM_TO(16, 27);
	पंचांगp |= (VBackPorchStrt << 16) | (VTotal);
	STG_WRITE_REG(DACVerTim1, पंचांगp);

	पंचांगp = STG_READ_REG(DACVerTim2);
	CLEAR_BITS_FRM_TO(0, 11);
	CLEAR_BITS_FRM_TO(16, 27);
	पंचांगp |= (VDisplayStrt << 16) | VTopBorderStrt;
	STG_WRITE_REG(DACVerTim2, पंचांगp);

	पंचांगp = STG_READ_REG(DACVerTim3);
	CLEAR_BITS_FRM_TO(0, 11);
	CLEAR_BITS_FRM_TO(16, 27);
	पंचांगp |= (VFrontPorchStrt << 16) | VBottomBorderStrt;
	STG_WRITE_REG(DACVerTim3, पंचांगp);

	/* Set Verical and Horizontal Polarity */
	पंचांगp = STG_READ_REG(DACSyncCtrl) | SET_BIT(3) | SET_BIT(1);

	अगर ((pTiming->HSP > 0) && (pTiming->VSP < 0)) अणु	/* +hsync -vsync */
		पंचांगp &= ~0x8;
	पूर्ण अन्यथा अगर ((pTiming->HSP < 0) && (pTiming->VSP > 0)) अणु	/* -hsync +vsync */
		पंचांगp &= ~0x2;
	पूर्ण अन्यथा अगर ((pTiming->HSP < 0) && (pTiming->VSP < 0)) अणु	/* -hsync -vsync */
		पंचांगp &= ~0xA;
	पूर्ण अन्यथा अगर ((pTiming->HSP > 0) && (pTiming->VSP > 0)) अणु	/* +hsync -vsync */
		पंचांगp &= ~0x0;
	पूर्ण

	STG_WRITE_REG(DACSyncCtrl, पंचांगp);
पूर्ण
