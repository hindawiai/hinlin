<शैली गुरु>
/***************************************************************************\
|*                                                                           *|
|*       Copyright 1993-1999 NVIDIA, Corporation.  All rights reserved.      *|
|*                                                                           *|
|*     NOTICE TO USER:   The source code  is copyrighted under  U.S. and     *|
|*     पूर्णांकernational laws.  Users and possessors of this source code are     *|
|*     hereby granted a nonexclusive,  royalty-मुक्त copyright license to     *|
|*     use this code in inभागidual and commercial software.                  *|
|*                                                                           *|
|*     Any use of this source code must include,  in the user करोcumenta-     *|
|*     tion and  पूर्णांकernal comments to the code,  notices to the end user     *|
|*     as follows:                                                           *|
|*                                                                           *|
|*       Copyright 1993-1999 NVIDIA, Corporation.  All rights reserved.      *|
|*                                                                           *|
|*     NVIDIA, CORPORATION MAKES NO REPRESENTATION ABOUT THE SUITABILITY     *|
|*     OF  THIS SOURCE  CODE  FOR ANY PURPOSE.  IT IS  PROVIDED  "AS IS"     *|
|*     WITHOUT EXPRESS OR IMPLIED WARRANTY OF ANY KIND.  NVIDIA, CORPOR-     *|
|*     ATION DISCLAIMS ALL WARRANTIES  WITH REGARD  TO THIS SOURCE CODE,     *|
|*     INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY, NONINFRINGE-     *|
|*     MENT,  AND FITNESS  FOR A PARTICULAR PURPOSE.   IN NO EVENT SHALL     *|
|*     NVIDIA, CORPORATION  BE LIABLE FOR ANY SPECIAL,  INसूचीECT,  INCI-     *|
|*     DENTAL, OR CONSEQUENTIAL DAMAGES,  OR ANY DAMAGES  WHATSOEVER RE-     *|
|*     SULTING FROM LOSS OF USE,  DATA OR PROFITS,  WHETHER IN AN ACTION     *|
|*     OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,  ARISING OUT OF     *|
|*     OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOURCE CODE.     *|
|*                                                                           *|
|*     U.S. Government  End  Users.   This source code  is a "commercial     *|
|*     item,"  as that  term is  defined at  48 C.F.R. 2.101 (OCT 1995),     *|
|*     consisting  of "commercial  computer  software"  and  "commercial     *|
|*     computer  software  करोcumentation,"  as such  terms  are  used in     *|
|*     48 C.F.R. 12.212 (SEPT 1995)  and is provided to the U.S. Govern-     *|
|*     ment only as  a commercial end item.   Consistent with  48 C.F.R.     *|
|*     12.212 and  48 C.F.R. 227.7202-1 through  227.7202-4 (JUNE 1995),     *|
|*     all U.S. Government End Users  acquire the source code  with only     *|
|*     those rights set क्रमth herein.                                        *|
|*                                                                           *|
\***************************************************************************/

/*
 * GPL licensing note -- nVidia is allowing a liberal पूर्णांकerpretation of
 * the करोcumentation restriction above, to merely say that this nVidia's
 * copyright and disclaimer should be included with all code derived
 * from this source.  -- Jeff Garzik <jgarzik@pobox.com>, 01/Nov/99 
 */

/* $XFree86: xc/programs/Xserver/hw/xमुक्त86/drivers/nv/riva_hw.h,v 1.21 2002/10/14 18:22:46 mvojkovi Exp $ */
#अगर_अघोषित __RIVA_HW_H__
#घोषणा __RIVA_HW_H__
#घोषणा RIVA_SW_VERSION 0x00010003

#अगर_अघोषित Bool
प्रकार पूर्णांक Bool;
#पूर्ण_अगर

#अगर_अघोषित TRUE
#घोषणा TRUE 1
#पूर्ण_अगर
#अगर_अघोषित FALSE
#घोषणा FALSE 0
#पूर्ण_अगर
#अगर_अघोषित शून्य
#घोषणा शून्य 0
#पूर्ण_अगर

/*
 * Typedefs to क्रमce certain sized values.
 */
प्रकार अचिन्हित अक्षर  U008;
प्रकार अचिन्हित लघु U016;
प्रकार अचिन्हित पूर्णांक   U032;

/*
 * HW access macros.
 */
#समावेश <यंत्र/पन.स>

#घोषणा NV_WR08(p,i,d)  (__raw_ग_लिखोb((d), (व्योम __iomem *)(p) + (i)))
#घोषणा NV_RD08(p,i)    (__raw_पढ़ोb((व्योम __iomem *)(p) + (i)))
#घोषणा NV_WR16(p,i,d)  (__raw_ग_लिखोw((d), (व्योम __iomem *)(p) + (i)))
#घोषणा NV_RD16(p,i)    (__raw_पढ़ोw((व्योम __iomem *)(p) + (i)))
#घोषणा NV_WR32(p,i,d)  (__raw_ग_लिखोl((d), (व्योम __iomem *)(p) + (i)))
#घोषणा NV_RD32(p,i)    (__raw_पढ़ोl((व्योम __iomem *)(p) + (i)))

#घोषणा VGA_WR08(p,i,d) (ग_लिखोb((d), (व्योम __iomem *)(p) + (i)))
#घोषणा VGA_RD08(p,i)   (पढ़ोb((व्योम __iomem *)(p) + (i)))

/*
 * Define dअगरferent architectures.
 */
#घोषणा NV_ARCH_03  0x03
#घोषणा NV_ARCH_04  0x04
#घोषणा NV_ARCH_10  0x10
#घोषणा NV_ARCH_20  0x20
#घोषणा NV_ARCH_30  0x30
#घोषणा NV_ARCH_40  0x40

/***************************************************************************\
*                                                                           *
*                             FIFO रेजिस्टरs.                               *
*                                                                           *
\***************************************************************************/

/*
 * Raster OPeration. Winकरोws style ROP3.
 */
प्रकार अस्थिर काष्ठा
अणु
    U032 reserved00[4];
#अगर_घोषित __BIG_ENDIAN
    U032 FअगरoFree;
#अन्यथा
    U016 FअगरoFree;
    U016 Nop;
#पूर्ण_अगर
    U032 reserved01[0x0BB];
    U032 Rop3;
पूर्ण RivaRop;
/*
 * 8X8 Monochrome pattern.
 */
प्रकार अस्थिर काष्ठा
अणु
    U032 reserved00[4];
#अगर_घोषित __BIG_ENDIAN
    U032 FअगरoFree;
#अन्यथा
    U016 FअगरoFree;
    U016 Nop;
#पूर्ण_अगर
    U032 reserved01[0x0BD];
    U032 Shape;
    U032 reserved03[0x001];
    U032 Color0;
    U032 Color1;
    U032 Monochrome[2];
पूर्ण RivaPattern;
/*
 * Scissor clip rectangle.
 */
प्रकार अस्थिर काष्ठा
अणु
    U032 reserved00[4];
#अगर_घोषित __BIG_ENDIAN
    U032 FअगरoFree;
#अन्यथा
    U016 FअगरoFree;
    U016 Nop;
#पूर्ण_अगर
    U032 reserved01[0x0BB];
    U032 TopLeft;
    U032 WidthHeight;
पूर्ण RivaClip;
/*
 * 2D filled rectangle.
 */
प्रकार अस्थिर काष्ठा
अणु
    U032 reserved00[4];
#अगर_घोषित __BIG_ENDIAN
    U032 FअगरoFree;
#अन्यथा
    U016 FअगरoFree;
    U016 Nop[1];
#पूर्ण_अगर
    U032 reserved01[0x0BC];
    U032 Color;
    U032 reserved03[0x03E];
    U032 TopLeft;
    U032 WidthHeight;
पूर्ण RivaRectangle;
/*
 * 2D screen-screen BLT.
 */
प्रकार अस्थिर काष्ठा
अणु
    U032 reserved00[4];
#अगर_घोषित __BIG_ENDIAN
    U032 FअगरoFree;
#अन्यथा
    U016 FअगरoFree;
    U016 Nop;
#पूर्ण_अगर
    U032 reserved01[0x0BB];
    U032 TopLeftSrc;
    U032 TopLeftDst;
    U032 WidthHeight;
पूर्ण RivaScreenBlt;
/*
 * 2D pixel BLT.
 */
प्रकार अस्थिर काष्ठा
अणु
    U032 reserved00[4];
#अगर_घोषित __BIG_ENDIAN
    U032 FअगरoFree;
#अन्यथा
    U016 FअगरoFree;
    U016 Nop[1];
#पूर्ण_अगर
    U032 reserved01[0x0BC];
    U032 TopLeft;
    U032 WidthHeight;
    U032 WidthHeightIn;
    U032 reserved02[0x03C];
    U032 Pixels;
पूर्ण RivaPixmap;
/*
 * Filled rectangle combined with monochrome expand.  Useful क्रम glyphs.
 */
प्रकार अस्थिर काष्ठा
अणु
    U032 reserved00[4];
#अगर_घोषित __BIG_ENDIAN
    U032 FअगरoFree;
#अन्यथा
    U016 FअगरoFree;
    U016 Nop;
#पूर्ण_अगर
    U032 reserved01[0x0BB];
    U032 reserved03[(0x040)-1];
    U032 Color1A;
    काष्ठा
    अणु
        U032 TopLeft;
        U032 WidthHeight;
    पूर्ण UnclippedRectangle[64];
    U032 reserved04[(0x080)-3];
    काष्ठा
    अणु
        U032 TopLeft;
        U032 BottomRight;
    पूर्ण ClipB;
    U032 Color1B;
    काष्ठा
    अणु
        U032 TopLeft;
        U032 BottomRight;
    पूर्ण ClippedRectangle[64];
    U032 reserved05[(0x080)-5];
    काष्ठा
    अणु
        U032 TopLeft;
        U032 BottomRight;
    पूर्ण ClipC;
    U032 Color1C;
    U032 WidthHeightC;
    U032 Poपूर्णांकC;
    U032 MonochromeData1C;
    U032 reserved06[(0x080)+121];
    काष्ठा
    अणु
        U032 TopLeft;
        U032 BottomRight;
    पूर्ण ClipD;
    U032 Color1D;
    U032 WidthHeightInD;
    U032 WidthHeightOutD;
    U032 Poपूर्णांकD;
    U032 MonochromeData1D;
    U032 reserved07[(0x080)+120];
    काष्ठा
    अणु
        U032 TopLeft;
        U032 BottomRight;
    पूर्ण ClipE;
    U032 Color0E;
    U032 Color1E;
    U032 WidthHeightInE;
    U032 WidthHeightOutE;
    U032 Poपूर्णांकE;
    U032 MonochromeData01E;
पूर्ण RivaBiपंचांगap;
/*
 * 3D textured, Z buffered triangle.
 */
प्रकार अस्थिर काष्ठा
अणु
    U032 reserved00[4];
#अगर_घोषित __BIG_ENDIAN
    U032 FअगरoFree;
#अन्यथा
    U016 FअगरoFree;
    U016 Nop;
#पूर्ण_अगर
    U032 reserved01[0x0BC];
    U032 TextureOffset;
    U032 TextureFormat;
    U032 TextureFilter;
    U032 FogColor;
/* This is a problem on LynxOS */
#अगर_घोषित Control
#अघोषित Control
#पूर्ण_अगर
    U032 Control;
    U032 AlphaTest;
    U032 reserved02[0x339];
    U032 FogAndIndex;
    U032 Color;
    भग्न ScreenX;
    भग्न ScreenY;
    भग्न ScreenZ;
    भग्न EyeM;
    भग्न TextureS;
    भग्न TextureT;
पूर्ण RivaTexturedTriangle03;
प्रकार अस्थिर काष्ठा
अणु
    U032 reserved00[4];
#अगर_घोषित __BIG_ENDIAN
    U032 FअगरoFree;
#अन्यथा
    U016 FअगरoFree;
    U016 Nop;
#पूर्ण_अगर
    U032 reserved01[0x0BB];
    U032 ColorKey;
    U032 TextureOffset;
    U032 TextureFormat;
    U032 TextureFilter;
    U032 Blend;
/* This is a problem on LynxOS */
#अगर_घोषित Control
#अघोषित Control
#पूर्ण_अगर
    U032 Control;
    U032 FogColor;
    U032 reserved02[0x39];
    काष्ठा
    अणु
        भग्न ScreenX;
        भग्न ScreenY;
        भग्न ScreenZ;
        भग्न EyeM;
        U032 Color;
        U032 Specular;
        भग्न TextureS;
        भग्न TextureT;
    पूर्ण Vertex[16];
    U032 DrawTriangle3D;
पूर्ण RivaTexturedTriangle05;
/*
 * 2D line.
 */
प्रकार अस्थिर काष्ठा
अणु
    U032 reserved00[4];
#अगर_घोषित __BIG_ENDIAN
    U032 FअगरoFree;
#अन्यथा
    U016 FअगरoFree;
    U016 Nop[1];
#पूर्ण_अगर
    U032 reserved01[0x0BC];
    U032 Color;             /* source color               0304-0307*/
    U032 Reserved02[0x03e];
    काष्ठा अणु                /* start aliased methods in array   0400-    */
        U032 poपूर्णांक0;        /* y_x S16_S16 in pixels            0-   3*/
        U032 poपूर्णांक1;        /* y_x S16_S16 in pixels            4-   7*/
    पूर्ण Lin[16];              /* end of aliased methods in array      -047f*/
    काष्ठा अणु                /* start aliased methods in array   0480-    */
        U032 poपूर्णांक0X;       /* in pixels, 0 at left                0-   3*/
        U032 poपूर्णांक0Y;       /* in pixels, 0 at top                 4-   7*/
        U032 poपूर्णांक1X;       /* in pixels, 0 at left                8-   b*/
        U032 poपूर्णांक1Y;       /* in pixels, 0 at top                 c-   f*/
    पूर्ण Lin32[8];             /* end of aliased methods in array      -04ff*/
    U032 PolyLin[32];       /* y_x S16_S16 in pixels         0500-057f*/
    काष्ठा अणु                /* start aliased methods in array   0580-    */
        U032 x;             /* in pixels, 0 at left                0-   3*/
        U032 y;             /* in pixels, 0 at top                 4-   7*/
    पूर्ण PolyLin32[16];        /* end of aliased methods in array      -05ff*/
    काष्ठा अणु                /* start aliased methods in array   0600-    */
        U032 color;         /* source color                     0-   3*/
        U032 poपूर्णांक;         /* y_x S16_S16 in pixels            4-   7*/
    पूर्ण ColorPolyLin[16];     /* end of aliased methods in array      -067f*/
पूर्ण RivaLine;
/*
 * 2D/3D surfaces
 */
प्रकार अस्थिर काष्ठा
अणु
    U032 reserved00[4];
#अगर_घोषित __BIG_ENDIAN
    U032 FअगरoFree;
#अन्यथा
    U016 FअगरoFree;
    U016 Nop;
#पूर्ण_अगर
    U032 reserved01[0x0BE];
    U032 Offset;
पूर्ण RivaSurface;
प्रकार अस्थिर काष्ठा
अणु
    U032 reserved00[4];
#अगर_घोषित __BIG_ENDIAN
    U032 FअगरoFree;
#अन्यथा
    U016 FअगरoFree;
    U016 Nop;
#पूर्ण_अगर
    U032 reserved01[0x0BD];
    U032 Pitch;
    U032 RenderBufferOffset;
    U032 ZBufferOffset;
पूर्ण RivaSurface3D;
    
/***************************************************************************\
*                                                                           *
*                        Virtualized RIVA H/W पूर्णांकerface.                    *
*                                                                           *
\***************************************************************************/

#घोषणा FP_ENABLE  1
#घोषणा FP_DITHER  2

काष्ठा _riva_hw_inst;
काष्ठा _riva_hw_state;
/*
 * Virtialized chip पूर्णांकerface. Makes RIVA 128 and TNT look alike.
 */
प्रकार काष्ठा _riva_hw_inst
अणु
    /*
     * Chip specअगरic settings.
     */
    U032 Architecture;
    U032 Version;
    U032 Chipset;
    U032 CrystalFreqKHz;
    U032 RamAmountKBytes;
    U032 MaxVClockFreqKHz;
    U032 RamBandwidthKBytesPerSec;
    U032 EnableIRQ;
    U032 IO;
    U032 VBlankBit;
    U032 FअगरoFreeCount;
    U032 FअगरoEmptyCount;
    U032 CursorStart;
    U032 flatPanel;
    Bool twoHeads;
    /*
     * Non-FIFO रेजिस्टरs.
     */
    अस्थिर U032 __iomem *PCRTC0;
    अस्थिर U032 __iomem *PCRTC;
    अस्थिर U032 __iomem *PRAMDAC0;
    अस्थिर U032 __iomem *PFB;
    अस्थिर U032 __iomem *PFIFO;
    अस्थिर U032 __iomem *PGRAPH;
    अस्थिर U032 __iomem *PEXTDEV;
    अस्थिर U032 __iomem *PTIMER;
    अस्थिर U032 __iomem *PMC;
    अस्थिर U032 __iomem *PRAMIN;
    अस्थिर U032 __iomem *FIFO;
    अस्थिर U032 __iomem *CURSOR;
    अस्थिर U008 __iomem *PCIO0;
    अस्थिर U008 __iomem *PCIO;
    अस्थिर U008 __iomem *PVIO;
    अस्थिर U008 __iomem *PDIO0;
    अस्थिर U008 __iomem *PDIO;
    अस्थिर U032 __iomem *PRAMDAC;
    /*
     * Common chip functions.
     */
    पूर्णांक  (*Busy)(काष्ठा _riva_hw_inst *);
    व्योम (*LoadStateExt)(काष्ठा _riva_hw_inst *,काष्ठा _riva_hw_state *);
    व्योम (*UnloadStateExt)(काष्ठा _riva_hw_inst *,काष्ठा _riva_hw_state *);
    व्योम (*SetStartAddress)(काष्ठा _riva_hw_inst *,U032);
    व्योम (*SetSurfaces2D)(काष्ठा _riva_hw_inst *,U032,U032);
    व्योम (*SetSurfaces3D)(काष्ठा _riva_hw_inst *,U032,U032);
    पूर्णांक  (*ShowHideCursor)(काष्ठा _riva_hw_inst *,पूर्णांक);
    व्योम (*LockUnlock)(काष्ठा _riva_hw_inst *, पूर्णांक);
    /*
     * Current extended mode settings.
     */
    काष्ठा _riva_hw_state *CurrentState;
    /*
     * FIFO रेजिस्टरs.
     */
    RivaRop                 __iomem *Rop;
    RivaPattern             __iomem *Patt;
    RivaClip                __iomem *Clip;
    RivaPixmap              __iomem *Pixmap;
    RivaScreenBlt           __iomem *Blt;
    RivaBiपंचांगap              __iomem *Biपंचांगap;
    RivaLine                __iomem *Line;
    RivaTexturedTriangle03  __iomem *Tri03;
    RivaTexturedTriangle05  __iomem *Tri05;
पूर्ण RIVA_HW_INST;
/*
 * Extended mode state inक्रमmation.
 */
प्रकार काष्ठा _riva_hw_state
अणु
    U032 bpp;
    U032 width;
    U032 height;
    U032 पूर्णांकerlace;
    U032 repaपूर्णांक0;
    U032 repaपूर्णांक1;
    U032 screen;
    U032 scale;
    U032 dither;
    U032 extra;
    U032 pixel;
    U032 horiz;
    U032 arbitration0;
    U032 arbitration1;
    U032 vpll;
    U032 vpll2;
    U032 pllsel;
    U032 general;
    U032 crtcOwner;
    U032 head; 
    U032 head2; 
    U032 config;
    U032 cursorConfig;	
    U032 cursor0;
    U032 cursor1;
    U032 cursor2;
    U032 offset0;
    U032 offset1;
    U032 offset2;
    U032 offset3;
    U032 pitch0;
    U032 pitch1;
    U032 pitch2;
    U032 pitch3;
पूर्ण RIVA_HW_STATE;

/*
 * function prototypes
 */

बाह्य पूर्णांक CalcStateExt
(
    RIVA_HW_INST  *chip,
    RIVA_HW_STATE *state,
    काष्ठा pci_dev *pdev,
    पूर्णांक            bpp,
    पूर्णांक            width,
    पूर्णांक            hDisplaySize,
    पूर्णांक            height,
    पूर्णांक            करोtClock
);

/*
 * External routines.
 */
पूर्णांक RivaGetConfig(RIVA_HW_INST *chip, काष्ठा pci_dev *pdev, अचिन्हित पूर्णांक c);
/*
 * FIFO Free Count. Should attempt to yield processor अगर RIVA is busy.
 */

#घोषणा RIVA_FIFO_FREE(hwinst,hwptr,cnt)                            \
अणु                                                                   \
    जबतक ((hwinst).FअगरoFreeCount < (cnt)) अणु                        \
	mb();mb();						    \
        (hwinst).FअगरoFreeCount = NV_RD32(&(hwinst).hwptr->FअगरoFree, 0) >> 2;     \
    पूर्ण								    \
    (hwinst).FअगरoFreeCount -= (cnt);                                \
पूर्ण
#पूर्ण_अगर /* __RIVA_HW_H__ */

