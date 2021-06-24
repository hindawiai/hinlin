<शैली गुरु>
/*
 *  linux/drivers/video/kyro/STG4000OverlayDevice.c
 *
 *  Copyright (C) 2000 Imagination Technologies Ltd
 *  Copyright (C) 2002 STMicroelectronics
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>

#समावेश "STG4000Reg.h"
#समावेश "STG4000Interface.h"

/* HW Defines */

#घोषणा STG4000_NO_SCALING    0x800
#घोषणा STG4000_NO_DECIMATION 0xFFFFFFFF

/* Primary surface */
#घोषणा STG4000_PRIM_NUM_PIX   5
#घोषणा STG4000_PRIM_ALIGN     4
#घोषणा STG4000_PRIM_ADDR_BITS 20

#घोषणा STG4000_PRIM_MIN_WIDTH  640
#घोषणा STG4000_PRIM_MAX_WIDTH  1600
#घोषणा STG4000_PRIM_MIN_HEIGHT 480
#घोषणा STG4000_PRIM_MAX_HEIGHT 1200

/* Overlay surface */
#घोषणा STG4000_OVRL_NUM_PIX   4
#घोषणा STG4000_OVRL_ALIGN     2
#घोषणा STG4000_OVRL_ADDR_BITS 20
#घोषणा STG4000_OVRL_NUM_MODES 5

#घोषणा STG4000_OVRL_MIN_WIDTH  0
#घोषणा STG4000_OVRL_MAX_WIDTH  720
#घोषणा STG4000_OVRL_MIN_HEIGHT 0
#घोषणा STG4000_OVRL_MAX_HEIGHT 576

/* Decimation and Scaling */
अटल u32 adwDecim8[33] = अणु
	    0xffffffff, 0xfffeffff, 0xffdffbff, 0xfefefeff, 0xfdf7efbf,
	    0xfbdf7bdf, 0xf7bbddef, 0xeeeeeeef, 0xeeddbb77, 0xedb76db7,
	    0xdb6db6db, 0xdb5b5b5b, 0xdab5ad6b, 0xd5ab55ab, 0xd555aaab,
	    0xaaaaaaab, 0xaaaa5555, 0xaa952a55, 0xa94a5295, 0xa5252525,
	    0xa4924925, 0x92491249, 0x91224489, 0x91111111, 0x90884211,
	    0x88410821, 0x88102041, 0x81010101, 0x80800801, 0x80010001,
	    0x80000001, 0x00000001, 0x00000000
पूर्ण;

प्रकार काष्ठा _OVRL_SRC_DEST अणु
	/*clipped on-screen pixel position of overlay */
	u32 ulDstX1;
	u32 ulDstY1;
	u32 ulDstX2;
	u32 ulDstY2;

	/*clipped pixel pos of source data within buffer thses need to be 128 bit word aligned */
	u32 ulSrcX1;
	u32 ulSrcY1;
	u32 ulSrcX2;
	u32 ulSrcY2;

	/* on-screen pixel position of overlay */
	s32 lDstX1;
	s32 lDstY1;
	s32 lDstX2;
	s32 lDstY2;
पूर्ण OVRL_SRC_DEST;

अटल u32 ovlWidth, ovlHeight, ovlStride;
अटल पूर्णांक ovlLinear;

व्योम ResetOverlayRegisters(अस्थिर STG4000REG __iomem *pSTGReg)
अणु
	u32 पंचांगp;

	/* Set Overlay address to शेष */
	पंचांगp = STG_READ_REG(DACOverlayAddr);
	CLEAR_BITS_FRM_TO(0, 20);
	CLEAR_BIT(31);
	STG_WRITE_REG(DACOverlayAddr, पंचांगp);

	/* Set Overlay U address */
	पंचांगp = STG_READ_REG(DACOverlayUAddr);
	CLEAR_BITS_FRM_TO(0, 20);
	STG_WRITE_REG(DACOverlayUAddr, पंचांगp);

	/* Set Overlay V address */
	पंचांगp = STG_READ_REG(DACOverlayVAddr);
	CLEAR_BITS_FRM_TO(0, 20);
	STG_WRITE_REG(DACOverlayVAddr, पंचांगp);

	/* Set Overlay Size */
	पंचांगp = STG_READ_REG(DACOverlaySize);
	CLEAR_BITS_FRM_TO(0, 10);
	CLEAR_BITS_FRM_TO(12, 31);
	STG_WRITE_REG(DACOverlaySize, पंचांगp);

	/* Set Overlay Vt Decimation */
	पंचांगp = STG4000_NO_DECIMATION;
	STG_WRITE_REG(DACOverlayVtDec, पंचांगp);

	/* Set Overlay क्रमmat to शेष value */
	पंचांगp = STG_READ_REG(DACPixelFormat);
	CLEAR_BITS_FRM_TO(4, 7);
	CLEAR_BITS_FRM_TO(16, 22);
	STG_WRITE_REG(DACPixelFormat, पंचांगp);

	/* Set Vertical scaling to शेष */
	पंचांगp = STG_READ_REG(DACVerticalScal);
	CLEAR_BITS_FRM_TO(0, 11);
	CLEAR_BITS_FRM_TO(16, 22);
	पंचांगp |= STG4000_NO_SCALING;	/* Set to no scaling */
	STG_WRITE_REG(DACVerticalScal, पंचांगp);

	/* Set Horizontal Scaling to शेष */
	पंचांगp = STG_READ_REG(DACHorizontalScal);
	CLEAR_BITS_FRM_TO(0, 11);
	CLEAR_BITS_FRM_TO(16, 17);
	पंचांगp |= STG4000_NO_SCALING;	/* Set to no scaling */
	STG_WRITE_REG(DACHorizontalScal, पंचांगp);

	/* Set Blend mode to Alpha Blend */
	/* ????? SG 08/11/2001 Surely this isn't the alpha blend mode,
	   hopefully its overग_लिखो
	 */
	पंचांगp = STG_READ_REG(DACBlendCtrl);
	CLEAR_BITS_FRM_TO(0, 30);
	पंचांगp = (GRAPHICS_MODE << 28);
	STG_WRITE_REG(DACBlendCtrl, पंचांगp);

पूर्ण

पूर्णांक CreateOverlaySurface(अस्थिर STG4000REG __iomem *pSTGReg,
			 u32 inWidth,
			 u32 inHeight,
			 पूर्णांक bLinear,
			 u32 ulOverlayOffset,
			 u32 * retStride, u32 * retUVStride)
अणु
	u32 पंचांगp;
	u32 ulStride;

	अगर (inWidth > STG4000_OVRL_MAX_WIDTH ||
	    inHeight > STG4000_OVRL_MAX_HEIGHT) अणु
		वापस -EINVAL;
	पूर्ण

	/* Stride in 16 byte words - 16Bpp */
	अगर (bLinear) अणु
		/* Format is 16bits so num 16 byte words is width/8 */
		अगर ((inWidth & 0x7) == 0) अणु	/* inWidth % 8 */
			ulStride = (inWidth / 8);
		पूर्ण अन्यथा अणु
			/* Round up to next 16byte boundary */
			ulStride = ((inWidth + 8) / 8);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Y component is 8bits so num 16 byte words is width/16 */
		अगर ((inWidth & 0xf) == 0) अणु	/* inWidth % 16 */
			ulStride = (inWidth / 16);
		पूर्ण अन्यथा अणु
			/* Round up to next 16byte boundary */
			ulStride = ((inWidth + 16) / 16);
		पूर्ण
	पूर्ण


	/* Set Overlay address and Format mode */
	पंचांगp = STG_READ_REG(DACOverlayAddr);
	CLEAR_BITS_FRM_TO(0, 20);
	अगर (bLinear) अणु
		CLEAR_BIT(31);	/* Overlay क्रमmat to Linear */
	पूर्ण अन्यथा अणु
		पंचांगp |= SET_BIT(31);	/* Overlay क्रमmat to Planer */
	पूर्ण

	/* Only bits 24:4 of the Overlay address */
	पंचांगp |= (ulOverlayOffset >> 4);
	STG_WRITE_REG(DACOverlayAddr, पंचांगp);

	अगर (!bLinear) अणु
		u32 uvSize =
		    (inWidth & 0x1) ? (inWidth + 1 / 2) : (inWidth / 2);
		u32 uvStride;
		u32 ulOffset;
		/* Y component is 8bits so num 32 byte words is width/32 */
		अगर ((uvSize & 0xf) == 0) अणु	/* inWidth % 16 */
			uvStride = (uvSize / 16);
		पूर्ण अन्यथा अणु
			/* Round up to next 32byte boundary */
			uvStride = ((uvSize + 16) / 16);
		पूर्ण

		ulOffset = ulOverlayOffset + (inHeight * (ulStride * 16));
		/* Align U,V data to 32byte boundary */
		अगर ((ulOffset & 0x1f) != 0)
			ulOffset = (ulOffset + 32L) & 0xffffffE0L;

		पंचांगp = STG_READ_REG(DACOverlayUAddr);
		CLEAR_BITS_FRM_TO(0, 20);
		पंचांगp |= (ulOffset >> 4);
		STG_WRITE_REG(DACOverlayUAddr, पंचांगp);

		ulOffset += (inHeight / 2) * (uvStride * 16);
		/* Align U,V data to 32byte boundary */
		अगर ((ulOffset & 0x1f) != 0)
			ulOffset = (ulOffset + 32L) & 0xffffffE0L;

		पंचांगp = STG_READ_REG(DACOverlayVAddr);
		CLEAR_BITS_FRM_TO(0, 20);
		पंचांगp |= (ulOffset >> 4);
		STG_WRITE_REG(DACOverlayVAddr, पंचांगp);

		*retUVStride = uvStride * 16;
	पूर्ण


	/* Set Overlay YUV pixel क्रमmat
	 * Make sure that LUT not used - ??????
	 */
	पंचांगp = STG_READ_REG(DACPixelFormat);
	/* Only support Planer or UYVY linear क्रमmats */
	CLEAR_BITS_FRM_TO(4, 9);
	STG_WRITE_REG(DACPixelFormat, पंचांगp);

	ovlWidth = inWidth;
	ovlHeight = inHeight;
	ovlStride = ulStride;
	ovlLinear = bLinear;
	*retStride = ulStride << 4;	/* In bytes */

	वापस 0;
पूर्ण

पूर्णांक SetOverlayBlendMode(अस्थिर STG4000REG __iomem *pSTGReg,
			OVRL_BLEND_MODE mode,
			u32 ulAlpha, u32 ulColorKey)
अणु
	u32 पंचांगp;

	पंचांगp = STG_READ_REG(DACBlendCtrl);
	CLEAR_BITS_FRM_TO(28, 30);
	पंचांगp |= (mode << 28);

	चयन (mode) अणु
	हाल COLOR_KEY:
		CLEAR_BITS_FRM_TO(0, 23);
		पंचांगp |= (ulColorKey & 0x00FFFFFF);
		अवरोध;

	हाल GLOBAL_ALPHA:
		CLEAR_BITS_FRM_TO(24, 27);
		पंचांगp |= ((ulAlpha & 0xF) << 24);
		अवरोध;

	हाल CK_PIXEL_ALPHA:
		CLEAR_BITS_FRM_TO(0, 23);
		पंचांगp |= (ulColorKey & 0x00FFFFFF);
		अवरोध;

	हाल CK_GLOBAL_ALPHA:
		CLEAR_BITS_FRM_TO(0, 23);
		पंचांगp |= (ulColorKey & 0x00FFFFFF);
		CLEAR_BITS_FRM_TO(24, 27);
		पंचांगp |= ((ulAlpha & 0xF) << 24);
		अवरोध;

	हाल GRAPHICS_MODE:
	हाल PER_PIXEL_ALPHA:
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	STG_WRITE_REG(DACBlendCtrl, पंचांगp);

	वापस 0;
पूर्ण

व्योम EnableOverlayPlane(अस्थिर STG4000REG __iomem *pSTGReg)
अणु
	u32 पंचांगp;
	/* Enable Overlay */
	पंचांगp = STG_READ_REG(DACPixelFormat);
	पंचांगp |= SET_BIT(7);
	STG_WRITE_REG(DACPixelFormat, पंचांगp);

	/* Set video stream control */
	पंचांगp = STG_READ_REG(DACStreamCtrl);
	पंचांगp |= SET_BIT(1);	/* video stream */
	STG_WRITE_REG(DACStreamCtrl, पंचांगp);
पूर्ण

अटल u32 Overlap(u32 ulBits, u32 ulPattern)
अणु
	u32 ulCount = 0;

	जबतक (ulBits) अणु
		अगर (!(ulPattern & 1))
			ulCount++;
		ulBits--;
		ulPattern = ulPattern >> 1;
	पूर्ण

	वापस ulCount;

पूर्ण

पूर्णांक SetOverlayViewPort(अस्थिर STG4000REG __iomem *pSTGReg,
		       u32 left, u32 top,
		       u32 right, u32 bottom)
अणु
	OVRL_SRC_DEST srcDest;

	u32 ulSrcTop, ulSrcBottom;
	u32 ulSrc, ulDest;
	u32 ulFxScale, ulFxOffset;
	u32 ulHeight, ulWidth;
	u32 ulPattern;
	u32 ulDecimate, ulDecimated;
	u32 ulApplied;
	u32 ulDacXScale, ulDacYScale;
	u32 ulScale;
	u32 ulLeft, ulRight;
	u32 ulSrcLeft, ulSrcRight;
	u32 ulScaleLeft;
	u32 ulhDecim;
	u32 ulsVal;
	u32 ulVertDecFactor;
	पूर्णांक bResult;
	u32 ulClipOff = 0;
	u32 ulBits = 0;
	u32 ulsAdd = 0;
	u32 पंचांगp, ulStride;
	u32 ulExcessPixels, ulClip, ulExtraLines;


	srcDest.ulSrcX1 = 0;
	srcDest.ulSrcY1 = 0;
	srcDest.ulSrcX2 = ovlWidth - 1;
	srcDest.ulSrcY2 = ovlHeight - 1;

	srcDest.ulDstX1 = left;
	srcDest.ulDstY1 = top;
	srcDest.ulDstX2 = right;
	srcDest.ulDstY2 = bottom;

	srcDest.lDstX1 = srcDest.ulDstX1;
	srcDest.lDstY1 = srcDest.ulDstY1;
	srcDest.lDstX2 = srcDest.ulDstX2;
	srcDest.lDstY2 = srcDest.ulDstY2;

    /************* Vertical decimation/scaling ******************/

	/* Get Src Top and Bottom */
	ulSrcTop = srcDest.ulSrcY1;
	ulSrcBottom = srcDest.ulSrcY2;

	ulSrc = ulSrcBottom - ulSrcTop;
	ulDest = srcDest.lDstY2 - srcDest.lDstY1;	/* on-screen overlay */

	अगर (ulSrc <= 1)
		वापस -EINVAL;

	/* First work out the position we are to display as offset from the
	 * source of the buffer
	 */
	ulFxScale = (ulDest << 11) / ulSrc;	/* fixed poपूर्णांक scale factor */
	ulFxOffset = (srcDest.lDstY2 - srcDest.ulDstY2) << 11;

	ulSrcBottom = ulSrcBottom - (ulFxOffset / ulFxScale);
	ulSrc = ulSrcBottom - ulSrcTop;
	ulHeight = ulSrc;

	ulDest = srcDest.ulDstY2 - (srcDest.ulDstY1 - 1);
	ulPattern = adwDecim8[ulBits];

	/* At this poपूर्णांक ulSrc represents the input decimator */
	अगर (ulSrc > ulDest) अणु
		ulDecimate = ulSrc - ulDest;
		ulBits = 0;
		ulApplied = ulSrc / 32;

		जबतक (((ulBits * ulApplied) +
			Overlap((ulSrc % 32),
				adwDecim8[ulBits])) < ulDecimate)
			ulBits++;

		ulPattern = adwDecim8[ulBits];
		ulDecimated =
		    (ulBits * ulApplied) + Overlap((ulSrc % 32),
						   ulPattern);
		ulSrc = ulSrc - ulDecimated;	/* the number number of lines that will go पूर्णांकo the scaler */
	पूर्ण

	अगर (ulBits && (ulBits != 32)) अणु
		ulVertDecFactor = (63 - ulBits) / (32 - ulBits);	/* vertical decimation factor scaled up to nearest पूर्णांकeger */
	पूर्ण अन्यथा अणु
		ulVertDecFactor = 1;
	पूर्ण

	ulDacYScale = ((ulSrc - 1) * 2048) / (ulDest + 1);

	पंचांगp = STG_READ_REG(DACOverlayVtDec);	/* Decimation */
	CLEAR_BITS_FRM_TO(0, 31);
	पंचांगp = ulPattern;
	STG_WRITE_REG(DACOverlayVtDec, पंचांगp);

	/***************** Horizontal decimation/scaling ***************************/

	/*
	 * Now we handle the horizontal हाल, this is a simplअगरied version of
	 * the vertical हाल in that we decimate by factors of 2.  as we are
	 * working in words we should always be able to decimate by these
	 * factors.  as we always have to have a buffer which is aligned to a
	 * whole number of 128 bit words, we must align the left side to the
	 * lowest to the next lowest 128 bit boundary, and the right hand edge
	 * to the next larमाला_लो boundary, (in a similar way to how we didi it in
	 * PMX1) as the left and right hand edges are aligned to these
	 * boundaries normally this only becomes an issue when we are chopping
	 * of one of the sides We shall work out vertical stuff first
	 */
	ulSrc = srcDest.ulSrcX2 - srcDest.ulSrcX1;
	ulDest = srcDest.lDstX2 - srcDest.lDstX1;
#अगर_घोषित _OLDCODE
	ulLeft = srcDest.ulDstX1;
	ulRight = srcDest.ulDstX2;
#अन्यथा
	अगर (srcDest.ulDstX1 > 2) अणु
		ulLeft = srcDest.ulDstX1 + 2;
		ulRight = srcDest.ulDstX2 + 1;
	पूर्ण अन्यथा अणु
		ulLeft = srcDest.ulDstX1;
		ulRight = srcDest.ulDstX2 + 1;
	पूर्ण
#पूर्ण_अगर
	/* first work out the position we are to display as offset from the source of the buffer */
	bResult = 1;

	करो अणु
		अगर (ulDest == 0)
			वापस -EINVAL;

		/* source pixels per dest pixel <<11 */
		ulFxScale = ((ulSrc - 1) << 11) / (ulDest);

		/* then number of destination pixels out we are */
		ulFxOffset = ulFxScale * ((srcDest.ulDstX1 - srcDest.lDstX1) + ulClipOff);
		ulFxOffset >>= 11;

		/* this replaces the code which was making a decision as to use either ulFxOffset or ulSrcX1 */
		ulSrcLeft = srcDest.ulSrcX1 + ulFxOffset;

		/* then number of destination pixels out we are */
		ulFxOffset = ulFxScale * (srcDest.lDstX2 - srcDest.ulDstX2);
		ulFxOffset >>= 11;

		ulSrcRight = srcDest.ulSrcX2 - ulFxOffset;

		/*
		 * we must align these to our 128 bit boundaries. we shall
		 * round करोwn the pixel pos to the nearest 8 pixels.
		 */
		ulScaleLeft = ulSrcLeft;

		/* shअगरt fxscale until it is in the range of the scaler */
		ulhDecim = 0;
		ulScale = (((ulSrcRight - ulSrcLeft) - 1) << (11 - ulhDecim)) / (ulRight - ulLeft + 2);

		जबतक (ulScale > 0x800) अणु
			ulhDecim++;
			ulScale = (((ulSrcRight - ulSrcLeft) - 1) << (11 - ulhDecim)) / (ulRight - ulLeft + 2);
		पूर्ण

		/*
		 * to try and get the best values We first try and use
		 * src/dwdest क्रम the scale factor, then we move onto src-1
		 *
		 * we want to check to see अगर we will need to clip data, अगर so
		 * then we should clip our source so that we करोn't need to
		 */
		अगर (!ovlLinear) अणु
			ulSrcLeft &= ~0x1f;

			/*
			 * we must align the right hand edge to the next 32
			 * pixel` boundary, must be on a 256 boundary so u, and
			 * v are 128 bit aligned
			 */
			ulSrcRight = (ulSrcRight + 0x1f) & ~0x1f;
		पूर्ण अन्यथा अणु
			ulSrcLeft &= ~0x7;

			/*
			 * we must align the right hand edge to the next
			 * 8pixel` boundary
			 */
			ulSrcRight = (ulSrcRight + 0x7) & ~0x7;
		पूर्ण

		/* this is the input size line store needs to cope with */
		ulWidth = ulSrcRight - ulSrcLeft;

		/*
		 * use unclipped value to work out scale factror this is the
		 * scale factor we want we shall now work out the horizonal
		 * decimation and scaling
		 */
		ulsVal = ((ulWidth / 8) >> ulhDecim);

		अगर ((ulWidth != (ulsVal << ulhDecim) * 8))
			ulsAdd = 1;

		/* input pixels to scaler; */
		ulSrc = ulWidth >> ulhDecim;

		अगर (ulSrc <= 2)
			वापस -EINVAL;

		ulExcessPixels = ((((ulScaleLeft - ulSrcLeft)) << (11 - ulhDecim)) / ulScale);

		ulClip = (ulSrc << 11) / ulScale;
		ulClip -= (ulRight - ulLeft);
		ulClip += ulExcessPixels;

		अगर (ulClip)
			ulClip--;

		/* We may need to करो more here अगर we really have a HW rev < 5 */
	पूर्ण जबतक (!bResult);

	ulExtraLines = (1 << ulhDecim) * ulVertDecFactor;
	ulExtraLines += 64;
	ulHeight += ulExtraLines;

	ulDacXScale = ulScale;


	पंचांगp = STG_READ_REG(DACVerticalScal);
	CLEAR_BITS_FRM_TO(0, 11);
	CLEAR_BITS_FRM_TO(16, 22);	/* Vertical Scaling */

	/* Calculate new output line stride, this is always the number of 422
	   words in the line buffer, so it करोesn't matter अगर the
	   mode is 420. Then set the vertical scale रेजिस्टर.
	 */
	ulStride = (ulWidth >> (ulhDecim + 3)) + ulsAdd;
	पंचांगp |= ((ulStride << 16) | (ulDacYScale));	/* DAC_LS_CTRL = stride */
	STG_WRITE_REG(DACVerticalScal, पंचांगp);

	/* Now set up the overlay size using the modअगरied width and height
	   from decimate and scaling calculations
	 */
	पंचांगp = STG_READ_REG(DACOverlaySize);
	CLEAR_BITS_FRM_TO(0, 10);
	CLEAR_BITS_FRM_TO(12, 31);

	अगर (ovlLinear) अणु
		पंचांगp |=
		    (ovlStride | ((ulHeight + 1) << 12) |
		     (((ulWidth / 8) - 1) << 23));
	पूर्ण अन्यथा अणु
		पंचांगp |=
		    (ovlStride | ((ulHeight + 1) << 12) |
		     (((ulWidth / 32) - 1) << 23));
	पूर्ण

	STG_WRITE_REG(DACOverlaySize, पंचांगp);

	/* Set Video Winकरोw Start */
	पंचांगp = ((ulLeft << 16)) | (srcDest.ulDstY1);
	STG_WRITE_REG(DACVidWinStart, पंचांगp);

	/* Set Video Winकरोw End */
	पंचांगp = ((ulRight) << 16) | (srcDest.ulDstY2);
	STG_WRITE_REG(DACVidWinEnd, पंचांगp);

	/* Finally set up the rest of the overlay regs in the order
	   करोne in the IMG driver
	 */
	पंचांगp = STG_READ_REG(DACPixelFormat);
	पंचांगp = ((ulExcessPixels << 16) | पंचांगp) & 0x7fffffff;
	STG_WRITE_REG(DACPixelFormat, पंचांगp);

	पंचांगp = STG_READ_REG(DACHorizontalScal);
	CLEAR_BITS_FRM_TO(0, 11);
	CLEAR_BITS_FRM_TO(16, 17);
	पंचांगp |= ((ulhDecim << 16) | (ulDacXScale));
	STG_WRITE_REG(DACHorizontalScal, पंचांगp);

	वापस 0;
पूर्ण
