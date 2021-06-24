<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/fb.h>
#समावेश <linux/ioport.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/console.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/screen_info.h>

#समावेश "sm750.h"
#समावेश "sm750_accel.h"
अटल अंतरभूत व्योम ग_लिखो_dpr(काष्ठा lynx_accel *accel, पूर्णांक offset, u32 regValue)
अणु
	ग_लिखोl(regValue, accel->dprBase + offset);
पूर्ण

अटल अंतरभूत u32 पढ़ो_dpr(काष्ठा lynx_accel *accel, पूर्णांक offset)
अणु
	वापस पढ़ोl(accel->dprBase + offset);
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_dpPort(काष्ठा lynx_accel *accel, u32 data)
अणु
	ग_लिखोl(data, accel->dpPortBase);
पूर्ण

व्योम sm750_hw_de_init(काष्ठा lynx_accel *accel)
अणु
	/* setup 2d engine रेजिस्टरs */
	u32 reg, clr;

	ग_लिखो_dpr(accel, DE_MASKS, 0xFFFFFFFF);

	/* dpr1c */
	reg =  0x3;

	clr = DE_STRETCH_FORMAT_PATTERN_XY |
	      DE_STRETCH_FORMAT_PATTERN_Y_MASK |
	      DE_STRETCH_FORMAT_PATTERN_X_MASK |
	      DE_STRETCH_FORMAT_ADDRESSING_MASK |
	      DE_STRETCH_FORMAT_SOURCE_HEIGHT_MASK;

	/* DE_STRETCH bpp क्रमmat need be initialized in setMode routine */
	ग_लिखो_dpr(accel, DE_STRETCH_FORMAT,
		  (पढ़ो_dpr(accel, DE_STRETCH_FORMAT) & ~clr) | reg);

	/* disable clipping and transparent */
	ग_लिखो_dpr(accel, DE_CLIP_TL, 0); /* dpr2c */
	ग_लिखो_dpr(accel, DE_CLIP_BR, 0); /* dpr30 */

	ग_लिखो_dpr(accel, DE_COLOR_COMPARE_MASK, 0); /* dpr24 */
	ग_लिखो_dpr(accel, DE_COLOR_COMPARE, 0);

	clr = DE_CONTROL_TRANSPARENCY | DE_CONTROL_TRANSPARENCY_MATCH |
		DE_CONTROL_TRANSPARENCY_SELECT;

	/* dpr0c */
	ग_लिखो_dpr(accel, DE_CONTROL, पढ़ो_dpr(accel, DE_CONTROL) & ~clr);
पूर्ण

/*
 * set2dक्रमmat only be called from seपंचांगode functions
 * but अगर you need dual framebuffer driver,need call set2dक्रमmat
 * every समय you use 2d function
 */

व्योम sm750_hw_set2dक्रमmat(काष्ठा lynx_accel *accel, पूर्णांक fmt)
अणु
	u32 reg;

	/* fmt=0,1,2 क्रम 8,16,32,bpp on sm718/750/502 */
	reg = पढ़ो_dpr(accel, DE_STRETCH_FORMAT);
	reg &= ~DE_STRETCH_FORMAT_PIXEL_FORMAT_MASK;
	reg |= ((fmt << DE_STRETCH_FORMAT_PIXEL_FORMAT_SHIFT) &
		DE_STRETCH_FORMAT_PIXEL_FORMAT_MASK);
	ग_लिखो_dpr(accel, DE_STRETCH_FORMAT, reg);
पूर्ण

पूर्णांक sm750_hw_fillrect(काष्ठा lynx_accel *accel,
		      u32 base, u32 pitch, u32 Bpp,
		      u32 x, u32 y, u32 width, u32 height,
		      u32 color, u32 rop)
अणु
	u32 deCtrl;

	अगर (accel->de_रुको() != 0) अणु
		/*
		 * पूर्णांक समय रुको and always busy,seems hardware
		 * got something error
		 */
		pr_debug("De engine always busy\n");
		वापस -1;
	पूर्ण

	ग_लिखो_dpr(accel, DE_WINDOW_DESTINATION_BASE, base); /* dpr40 */
	ग_लिखो_dpr(accel, DE_PITCH,
		  ((pitch / Bpp << DE_PITCH_DESTINATION_SHIFT) &
		   DE_PITCH_DESTINATION_MASK) |
		  (pitch / Bpp & DE_PITCH_SOURCE_MASK)); /* dpr10 */

	ग_लिखो_dpr(accel, DE_WINDOW_WIDTH,
		  ((pitch / Bpp << DE_WINDOW_WIDTH_DST_SHIFT) &
		   DE_WINDOW_WIDTH_DST_MASK) |
		   (pitch / Bpp & DE_WINDOW_WIDTH_SRC_MASK)); /* dpr44 */

	ग_लिखो_dpr(accel, DE_FOREGROUND, color); /* DPR14 */

	ग_लिखो_dpr(accel, DE_DESTINATION,
		  ((x << DE_DESTINATION_X_SHIFT) & DE_DESTINATION_X_MASK) |
		  (y & DE_DESTINATION_Y_MASK)); /* dpr4 */

	ग_लिखो_dpr(accel, DE_DIMENSION,
		  ((width << DE_DIMENSION_X_SHIFT) & DE_DIMENSION_X_MASK) |
		  (height & DE_DIMENSION_Y_ET_MASK)); /* dpr8 */

	deCtrl = DE_CONTROL_STATUS | DE_CONTROL_LAST_PIXEL |
		DE_CONTROL_COMMAND_RECTANGLE_FILL | DE_CONTROL_ROP_SELECT |
		(rop & DE_CONTROL_ROP_MASK); /* dpr0xc */

	ग_लिखो_dpr(accel, DE_CONTROL, deCtrl);
	वापस 0;
पूर्ण

/**
 * sm750_hm_copyarea
 * @sBase: Address of source: offset in frame buffer
 * @sPitch: Pitch value of source surface in BYTE
 * @sx: Starting x coordinate of source surface
 * @sy: Starting y coordinate of source surface
 * @dBase: Address of destination: offset in frame buffer
 * @dPitch: Pitch value of destination surface in BYTE
 * @Bpp: Color depth of destination surface
 * @dx: Starting x coordinate of destination surface
 * @dy: Starting y coordinate of destination surface
 * @width: width of rectangle in pixel value
 * @height: height of rectangle in pixel value
 * @rop2: ROP value
 */
पूर्णांक sm750_hw_copyarea(काष्ठा lynx_accel *accel,
		      अचिन्हित पूर्णांक sBase, अचिन्हित पूर्णांक sPitch,
		      अचिन्हित पूर्णांक sx, अचिन्हित पूर्णांक sy,
		      अचिन्हित पूर्णांक dBase, अचिन्हित पूर्णांक dPitch,
		      अचिन्हित पूर्णांक Bpp, अचिन्हित पूर्णांक dx, अचिन्हित पूर्णांक dy,
		      अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height,
		      अचिन्हित पूर्णांक rop2)
अणु
	अचिन्हित पूर्णांक nDirection, de_ctrl;

	nDirection = LEFT_TO_RIGHT;
	/* Direction of ROP2 operation: 1 = Left to Right, (-1) = Right to Left */
	de_ctrl = 0;

	/* If source and destination are the same surface, need to check क्रम overlay हालs */
	अगर (sBase == dBase && sPitch == dPitch) अणु
		/* Determine direction of operation */
		अगर (sy < dy) अणु
			/*  +----------+
			 *  |S         |
			 *  |   +----------+
			 *  |   |      |   |
			 *  |   |      |   |
			 *  +---|------+   |
			 *	|         D|
			 *	+----------+
			 */

			nDirection = BOTTOM_TO_TOP;
		पूर्ण अन्यथा अगर (sy > dy) अणु
			/*  +----------+
			 *  |D         |
			 *  |   +----------+
			 *  |   |      |   |
			 *  |   |      |   |
			 *  +---|------+   |
			 *	|         S|
			 *	+----------+
			 */

			nDirection = TOP_TO_BOTTOM;
		पूर्ण अन्यथा अणु
			/* sy == dy */

			अगर (sx <= dx) अणु
				/* +------+---+------+
				 * |S     |   |     D|
				 * |      |   |      |
				 * |      |   |      |
				 * |      |   |      |
				 * +------+---+------+
				 */

				nDirection = RIGHT_TO_LEFT;
			पूर्ण अन्यथा अणु
			/* sx > dx */

				/* +------+---+------+
				 * |D     |   |     S|
				 * |      |   |      |
				 * |      |   |      |
				 * |      |   |      |
				 * +------+---+------+
				 */

				nDirection = LEFT_TO_RIGHT;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर ((nDirection == BOTTOM_TO_TOP) || (nDirection == RIGHT_TO_LEFT)) अणु
		sx += width - 1;
		sy += height - 1;
		dx += width - 1;
		dy += height - 1;
	पूर्ण

	/*
	 * Note:
	 * DE_FOREGROUND and DE_BACKGROUND are करोn't care.
	 * DE_COLOR_COMPARE and DE_COLOR_COMPARE_MAKS
	 * are set by set deSetTransparency().
	 */

	/*
	 * 2D Source Base.
	 * It is an address offset (128 bit aligned)
	 * from the beginning of frame buffer.
	 */
	ग_लिखो_dpr(accel, DE_WINDOW_SOURCE_BASE, sBase); /* dpr40 */

	/*
	 * 2D Destination Base.
	 * It is an address offset (128 bit aligned)
	 * from the beginning of frame buffer.
	 */
	ग_लिखो_dpr(accel, DE_WINDOW_DESTINATION_BASE, dBase); /* dpr44 */

	/*
	 * Program pitch (distance between the 1st poपूर्णांकs of two adjacent lines).
	 * Note that input pitch is BYTE value, but the 2D Pitch रेजिस्टर uses
	 * pixel values. Need Byte to pixel conversion.
	 */
	ग_लिखो_dpr(accel, DE_PITCH,
		  ((dPitch / Bpp << DE_PITCH_DESTINATION_SHIFT) &
		   DE_PITCH_DESTINATION_MASK) |
		  (sPitch / Bpp & DE_PITCH_SOURCE_MASK)); /* dpr10 */

	/*
	 * Screen Winकरोw width in Pixels.
	 * 2D engine uses this value to calculate the linear address in frame buffer
	 * क्रम a given poपूर्णांक.
	 */
	ग_लिखो_dpr(accel, DE_WINDOW_WIDTH,
		  ((dPitch / Bpp << DE_WINDOW_WIDTH_DST_SHIFT) &
		   DE_WINDOW_WIDTH_DST_MASK) |
		  (sPitch / Bpp & DE_WINDOW_WIDTH_SRC_MASK)); /* dpr3c */

	अगर (accel->de_रुको() != 0)
		वापस -1;

	ग_लिखो_dpr(accel, DE_SOURCE,
		  ((sx << DE_SOURCE_X_K1_SHIFT) & DE_SOURCE_X_K1_MASK) |
		  (sy & DE_SOURCE_Y_K2_MASK)); /* dpr0 */
	ग_लिखो_dpr(accel, DE_DESTINATION,
		  ((dx << DE_DESTINATION_X_SHIFT) & DE_DESTINATION_X_MASK) |
		  (dy & DE_DESTINATION_Y_MASK)); /* dpr04 */
	ग_लिखो_dpr(accel, DE_DIMENSION,
		  ((width << DE_DIMENSION_X_SHIFT) & DE_DIMENSION_X_MASK) |
		  (height & DE_DIMENSION_Y_ET_MASK)); /* dpr08 */

	de_ctrl = (rop2 & DE_CONTROL_ROP_MASK) | DE_CONTROL_ROP_SELECT |
		((nDirection == RIGHT_TO_LEFT) ? DE_CONTROL_सूचीECTION : 0) |
		DE_CONTROL_COMMAND_BITBLT | DE_CONTROL_STATUS;
	ग_लिखो_dpr(accel, DE_CONTROL, de_ctrl); /* dpr0c */

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक deGetTransparency(काष्ठा lynx_accel *accel)
अणु
	अचिन्हित पूर्णांक de_ctrl;

	de_ctrl = पढ़ो_dpr(accel, DE_CONTROL);

	de_ctrl &= (DE_CONTROL_TRANSPARENCY_MATCH |
		    DE_CONTROL_TRANSPARENCY_SELECT | DE_CONTROL_TRANSPARENCY);

	वापस de_ctrl;
पूर्ण

/**
 * sm750_hw_imageblit
 * @pSrcbuf: poपूर्णांकer to start of source buffer in प्रणाली memory
 * @srcDelta: Pitch value (in bytes) of the source buffer, +ive means top करोwn
 *	      and -ive mean button up
 * @startBit: Mono data can start at any bit in a byte, this value should be
 *	      0 to 7
 * @dBase: Address of destination: offset in frame buffer
 * @dPitch: Pitch value of destination surface in BYTE
 * @bytePerPixel: Color depth of destination surface
 * @dx: Starting x coordinate of destination surface
 * @dy: Starting y coordinate of destination surface
 * @width: width of rectangle in pixel value
 * @height: height of rectangle in pixel value
 * @fColor: Foreground color (corresponding to a 1 in the monochrome data
 * @bColor: Background color (corresponding to a 0 in the monochrome data
 * @rop2: ROP value
 */
पूर्णांक sm750_hw_imageblit(काष्ठा lynx_accel *accel, स्थिर अक्षर *pSrcbuf,
		       u32 srcDelta, u32 startBit, u32 dBase, u32 dPitch,
		       u32 bytePerPixel, u32 dx, u32 dy, u32 width,
		       u32 height, u32 fColor, u32 bColor, u32 rop2)
अणु
	अचिन्हित पूर्णांक ulBytesPerScan;
	अचिन्हित पूर्णांक ul4BytesPerScan;
	अचिन्हित पूर्णांक ulBytesReमुख्य;
	अचिन्हित पूर्णांक de_ctrl = 0;
	अचिन्हित अक्षर ajReमुख्य[4];
	पूर्णांक i, j;

	startBit &= 7; /* Just make sure the start bit is within legal range */
	ulBytesPerScan = (width + startBit + 7) / 8;
	ul4BytesPerScan = ulBytesPerScan & ~3;
	ulBytesReमुख्य = ulBytesPerScan & 3;

	अगर (accel->de_रुको() != 0)
		वापस -1;

	/*
	 * 2D Source Base.
	 * Use 0 क्रम HOST Blt.
	 */
	ग_लिखो_dpr(accel, DE_WINDOW_SOURCE_BASE, 0);

	/* 2D Destination Base.
	 * It is an address offset (128 bit aligned)
	 * from the beginning of frame buffer.
	 */
	ग_लिखो_dpr(accel, DE_WINDOW_DESTINATION_BASE, dBase);

	/*
	 * Program pitch (distance between the 1st poपूर्णांकs of two adjacent
	 * lines). Note that input pitch is BYTE value, but the 2D Pitch
	 * रेजिस्टर uses pixel values. Need Byte to pixel conversion.
	 */
	ग_लिखो_dpr(accel, DE_PITCH,
		  ((dPitch / bytePerPixel << DE_PITCH_DESTINATION_SHIFT) &
		   DE_PITCH_DESTINATION_MASK) |
		  (dPitch / bytePerPixel & DE_PITCH_SOURCE_MASK)); /* dpr10 */

	/*
	 * Screen Winकरोw width in Pixels.
	 * 2D engine uses this value to calculate the linear address
	 * in frame buffer क्रम a given poपूर्णांक.
	 */
	ग_लिखो_dpr(accel, DE_WINDOW_WIDTH,
		  ((dPitch / bytePerPixel << DE_WINDOW_WIDTH_DST_SHIFT) &
		   DE_WINDOW_WIDTH_DST_MASK) |
		  (dPitch / bytePerPixel & DE_WINDOW_WIDTH_SRC_MASK));

	 /*
	  * Note: For 2D Source in Host Write, only X_K1_MONO field is needed,
	  * and Y_K2 field is not used.
	  * For mono biपंचांगap, use startBit क्रम X_K1.
	  */
	ग_लिखो_dpr(accel, DE_SOURCE,
		  (startBit << DE_SOURCE_X_K1_SHIFT) &
		  DE_SOURCE_X_K1_MONO_MASK); /* dpr00 */

	ग_लिखो_dpr(accel, DE_DESTINATION,
		  ((dx << DE_DESTINATION_X_SHIFT) & DE_DESTINATION_X_MASK) |
		  (dy & DE_DESTINATION_Y_MASK)); /* dpr04 */

	ग_लिखो_dpr(accel, DE_DIMENSION,
		  ((width << DE_DIMENSION_X_SHIFT) & DE_DIMENSION_X_MASK) |
		  (height & DE_DIMENSION_Y_ET_MASK)); /* dpr08 */

	ग_लिखो_dpr(accel, DE_FOREGROUND, fColor);
	ग_लिखो_dpr(accel, DE_BACKGROUND, bColor);

	de_ctrl = (rop2 & DE_CONTROL_ROP_MASK) |
		DE_CONTROL_ROP_SELECT | DE_CONTROL_COMMAND_HOST_WRITE |
		DE_CONTROL_HOST | DE_CONTROL_STATUS;

	ग_लिखो_dpr(accel, DE_CONTROL, de_ctrl | deGetTransparency(accel));

	/* Write MONO data (line by line) to 2D Engine data port */
	क्रम (i = 0; i < height; i++) अणु
		/* For each line, send the data in chunks of 4 bytes */
		क्रम (j = 0; j < (ul4BytesPerScan / 4); j++)
			ग_लिखो_dpPort(accel, *(अचिन्हित पूर्णांक *)(pSrcbuf + (j * 4)));

		अगर (ulBytesReमुख्य) अणु
			स_नकल(ajReमुख्य, pSrcbuf + ul4BytesPerScan,
			       ulBytesReमुख्य);
			ग_लिखो_dpPort(accel, *(अचिन्हित पूर्णांक *)ajReमुख्य);
		पूर्ण

		pSrcbuf += srcDelta;
	पूर्ण

	वापस 0;
पूर्ण

