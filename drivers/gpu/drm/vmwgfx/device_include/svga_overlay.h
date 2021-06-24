<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR MIT */
/**********************************************************
 * Copyright 2007-2015 VMware, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person
 * obtaining a copy of this software and associated करोcumentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modअगरy, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 **********************************************************/

/*
 * svga_overlay.h --
 *
 *    Definitions क्रम video-overlay support.
 */

#अगर_अघोषित _SVGA_OVERLAY_H_
#घोषणा _SVGA_OVERLAY_H_

#समावेश "svga_reg.h"

/*
 * Video क्रमmats we support
 */

#घोषणा VMWARE_FOURCC_YV12 0x32315659 /* 'Y' 'V' '1' '2' */
#घोषणा VMWARE_FOURCC_YUY2 0x32595559 /* 'Y' 'U' 'Y' '2' */
#घोषणा VMWARE_FOURCC_UYVY 0x59565955 /* 'U' 'Y' 'V' 'Y' */

प्रकार क्रमागत अणु
   SVGA_OVERLAY_FORMAT_INVALID = 0,
   SVGA_OVERLAY_FORMAT_YV12 = VMWARE_FOURCC_YV12,
   SVGA_OVERLAY_FORMAT_YUY2 = VMWARE_FOURCC_YUY2,
   SVGA_OVERLAY_FORMAT_UYVY = VMWARE_FOURCC_UYVY,
पूर्ण SVGAOverlayFormat;

#घोषणा SVGA_VIDEO_COLORKEY_MASK             0x00ffffff

#घोषणा SVGA_ESCAPE_VMWARE_VIDEO             0x00020000

#घोषणा SVGA_ESCAPE_VMWARE_VIDEO_SET_REGS    0x00020001
        /* FIFO escape layout:
         * Type, Stream Id, (Register Id, Value) pairs */

#घोषणा SVGA_ESCAPE_VMWARE_VIDEO_FLUSH       0x00020002
        /* FIFO escape layout:
         * Type, Stream Id */

प्रकार
काष्ठा SVGAEscapeVideoSetRegs अणु
   काष्ठा अणु
      uपूर्णांक32 cmdType;
      uपूर्णांक32 streamId;
   पूर्ण header;

   /* May include zero or more items. */
   काष्ठा अणु
      uपूर्णांक32 रेजिस्टरId;
      uपूर्णांक32 value;
   पूर्ण items[1];
पूर्ण SVGAEscapeVideoSetRegs;

प्रकार
काष्ठा SVGAEscapeVideoFlush अणु
   uपूर्णांक32 cmdType;
   uपूर्णांक32 streamId;
पूर्ण SVGAEscapeVideoFlush;


/*
 * Struct definitions क्रम the video overlay commands built on
 * SVGAFअगरoCmdEscape.
 */
प्रकार
काष्ठा अणु
   uपूर्णांक32 command;
   uपूर्णांक32 overlay;
पूर्ण SVGAFअगरoEscapeCmdVideoBase;

प्रकार
काष्ठा अणु
   SVGAFअगरoEscapeCmdVideoBase videoCmd;
पूर्ण SVGAFअगरoEscapeCmdVideoFlush;

प्रकार
काष्ठा अणु
   SVGAFअगरoEscapeCmdVideoBase videoCmd;
   काष्ठा अणु
      uपूर्णांक32 regId;
      uपूर्णांक32 value;
   पूर्ण items[1];
पूर्ण SVGAFअगरoEscapeCmdVideoSetRegs;

प्रकार
काष्ठा अणु
   SVGAFअगरoEscapeCmdVideoBase videoCmd;
   काष्ठा अणु
      uपूर्णांक32 regId;
      uपूर्णांक32 value;
   पूर्ण items[SVGA_VIDEO_NUM_REGS];
पूर्ण SVGAFअगरoEscapeCmdVideoSetAllRegs;


/*
 *----------------------------------------------------------------------
 *
 * VMwareVideoGetAttributes --
 *
 *      Computes the size, pitches and offsets क्रम YUV frames.
 *
 * Results:
 *      TRUE on success; otherwise FALSE on failure.
 *
 * Side effects:
 *      Pitches and offsets क्रम the given YUV frame are put in 'pitches'
 *      and 'offsets' respectively. They are both optional though.
 *
 *----------------------------------------------------------------------
 */

अटल अंतरभूत bool
VMwareVideoGetAttributes(स्थिर SVGAOverlayFormat क्रमmat,    /* IN */
                         uपूर्णांक32 *width,                     /* IN / OUT */
                         uपूर्णांक32 *height,                    /* IN / OUT */
                         uपूर्णांक32 *size,                      /* OUT */
                         uपूर्णांक32 *pitches,                   /* OUT (optional) */
                         uपूर्णांक32 *offsets)                   /* OUT (optional) */
अणु
    पूर्णांक पंचांगp;

    *width = (*width + 1) & ~1;

    अगर (offsets) अणु
        offsets[0] = 0;
    पूर्ण

    चयन (क्रमmat) अणु
    हाल VMWARE_FOURCC_YV12:
       *height = (*height + 1) & ~1;
       *size = (*width) * (*height);

       अगर (pitches) अणु
          pitches[0] = *width;
       पूर्ण

       अगर (offsets) अणु
          offsets[1] = *size;
       पूर्ण

       पंचांगp = *width >> 1;

       अगर (pitches) अणु
          pitches[1] = pitches[2] = पंचांगp;
       पूर्ण

       पंचांगp *= (*height >> 1);
       *size += पंचांगp;

       अगर (offsets) अणु
          offsets[2] = *size;
       पूर्ण

       *size += पंचांगp;
       अवरोध;

    हाल VMWARE_FOURCC_YUY2:
    हाल VMWARE_FOURCC_UYVY:
       *size = *width * 2;

       अगर (pitches) अणु
          pitches[0] = *size;
       पूर्ण

       *size *= *height;
       अवरोध;

    शेष:
       वापस false;
    पूर्ण

    वापस true;
पूर्ण

#पूर्ण_अगर /* _SVGA_OVERLAY_H_ */
