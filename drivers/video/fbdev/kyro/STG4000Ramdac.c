<शैली गुरु>
/*
 *  linux/drivers/video/kyro/STG4000Ramdac.c
 *
 *  Copyright (C) 2002 STMicroelectronics
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <video/kyro.h>

#समावेश "STG4000Reg.h"
#समावेश "STG4000Interface.h"

अटल u32 STG_PIXEL_BUS_WIDTH = 128;	/* 128 bit bus width      */
अटल u32 REF_CLOCK = 14318;

पूर्णांक InitialiseRamdac(अस्थिर STG4000REG __iomem * pSTGReg,
		     u32 displayDepth,
		     u32 displayWidth,
		     u32 displayHeight,
		     s32 HSyncPolarity,
		     s32 VSyncPolarity, u32 * pixelClock)
अणु
	u32 पंचांगp = 0;
	u32 F = 0, R = 0, P = 0;
	u32 stride = 0;
	u32 ulPभाग = 0;
	u32 physicalPixelDepth = 0;
	/* Make sure DAC is in Reset */
	पंचांगp = STG_READ_REG(SoftwareReset);

	अगर (पंचांगp & 0x1) अणु
		CLEAR_BIT(1);
		STG_WRITE_REG(SoftwareReset, पंचांगp);
	पूर्ण

	/* Set Pixel Format */
	पंचांगp = STG_READ_REG(DACPixelFormat);
	CLEAR_BITS_FRM_TO(0, 2);

	/* Set LUT not used from 16bpp to 32 bpp ??? */
	CLEAR_BITS_FRM_TO(8, 9);

	चयन (displayDepth) अणु
	हाल 16:
		अणु
			physicalPixelDepth = 16;
			पंचांगp |= _16BPP;
			अवरोध;
		पूर्ण
	हाल 32:
		अणु
			/* Set क्रम 32 bits per pixel */
			physicalPixelDepth = 32;
			पंचांगp |= _32BPP;
			अवरोध;
		पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण

	STG_WRITE_REG(DACPixelFormat, पंचांगp);

	/* Workout Bus transfer bandwidth according to pixel क्रमmat */
	ulPभाग = STG_PIXEL_BUS_WIDTH / physicalPixelDepth;

	/* Get Screen Stride in pixels */
	stride = displayWidth;

	/* Set Primary size info */
	पंचांगp = STG_READ_REG(DACPrimSize);
	CLEAR_BITS_FRM_TO(0, 10);
	CLEAR_BITS_FRM_TO(12, 31);
	पंचांगp |=
	    ((((displayHeight - 1) << 12) | (((displayWidth / ulPभाग) -
					      1) << 23))
	     | (stride / ulPभाग));
	STG_WRITE_REG(DACPrimSize, पंचांगp);


	/* Set Pixel Clock */
	*pixelClock = ProgramClock(REF_CLOCK, *pixelClock, &F, &R, &P);

	/* Set DAC PLL Mode */
	पंचांगp = STG_READ_REG(DACPLLMode);
	CLEAR_BITS_FRM_TO(0, 15);
	/* पंचांगp |= ((P-1) | ((F-2) << 2) | ((R-2) << 11)); */
	पंचांगp |= ((P) | ((F - 2) << 2) | ((R - 2) << 11));
	STG_WRITE_REG(DACPLLMode, पंचांगp);

	/* Set Prim Address */
	पंचांगp = STG_READ_REG(DACPrimAddress);
	CLEAR_BITS_FRM_TO(0, 20);
	CLEAR_BITS_FRM_TO(20, 31);
	STG_WRITE_REG(DACPrimAddress, पंचांगp);

	/* Set Cursor details with HW Cursor disabled */
	पंचांगp = STG_READ_REG(DACCursorCtrl);
	पंचांगp &= ~SET_BIT(31);
	STG_WRITE_REG(DACCursorCtrl, पंचांगp);

	पंचांगp = STG_READ_REG(DACCursorAddr);
	CLEAR_BITS_FRM_TO(0, 20);
	STG_WRITE_REG(DACCursorAddr, पंचांगp);

	/* Set Video Winकरोw */
	पंचांगp = STG_READ_REG(DACVidWinStart);
	CLEAR_BITS_FRM_TO(0, 10);
	CLEAR_BITS_FRM_TO(16, 26);
	STG_WRITE_REG(DACVidWinStart, पंचांगp);

	पंचांगp = STG_READ_REG(DACVidWinEnd);
	CLEAR_BITS_FRM_TO(0, 10);
	CLEAR_BITS_FRM_TO(16, 26);
	STG_WRITE_REG(DACVidWinEnd, पंचांगp);

	/* Set DAC Border Color to शेष */
	पंचांगp = STG_READ_REG(DACBorderColor);
	CLEAR_BITS_FRM_TO(0, 23);
	STG_WRITE_REG(DACBorderColor, पंचांगp);

	/* Set Graphics and Overlay Burst Control */
	STG_WRITE_REG(DACBurstCtrl, 0x0404);

	/* Set CRC Trigger to शेष */
	पंचांगp = STG_READ_REG(DACCrcTrigger);
	CLEAR_BIT(0);
	STG_WRITE_REG(DACCrcTrigger, पंचांगp);

	/* Set Video Port Control to शेष */
	पंचांगp = STG_READ_REG(DigVidPortCtrl);
	CLEAR_BIT(8);
	CLEAR_BITS_FRM_TO(16, 27);
	CLEAR_BITS_FRM_TO(1, 3);
	CLEAR_BITS_FRM_TO(10, 11);
	STG_WRITE_REG(DigVidPortCtrl, पंचांगp);

	वापस 0;
पूर्ण

/* Ramdac control, turning output to the screen on and off */
व्योम DisableRamdacOutput(अस्थिर STG4000REG __iomem * pSTGReg)
अणु
	u32 पंचांगp;

	/* Disable DAC क्रम Graphics Stream Control */
	पंचांगp = (STG_READ_REG(DACStreamCtrl)) & ~SET_BIT(0);
	STG_WRITE_REG(DACStreamCtrl, पंचांगp);
पूर्ण

व्योम EnableRamdacOutput(अस्थिर STG4000REG __iomem * pSTGReg)
अणु
	u32 पंचांगp;

	/* Enable DAC क्रम Graphics Stream Control */
	पंचांगp = (STG_READ_REG(DACStreamCtrl)) | SET_BIT(0);
	STG_WRITE_REG(DACStreamCtrl, पंचांगp);
पूर्ण
