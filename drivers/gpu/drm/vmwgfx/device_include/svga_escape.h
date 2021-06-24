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
 * svga_escape.h --
 *
 *    Definitions क्रम our own (venकरोr-specअगरic) SVGA Escape commands.
 */

#अगर_अघोषित _SVGA_ESCAPE_H_
#घोषणा _SVGA_ESCAPE_H_


/*
 * Namespace IDs क्रम the escape command
 */

#घोषणा SVGA_ESCAPE_NSID_VMWARE 0x00000000
#घोषणा SVGA_ESCAPE_NSID_DEVEL  0xFFFFFFFF


/*
 * Within SVGA_ESCAPE_NSID_VMWARE, we multiplex commands according to
 * the first DWORD of escape data (after the nsID and size). As a
 * guideline we're using the high word and low word as a major and
 * minor command number, respectively.
 *
 * Major command number allocation:
 *
 *   0000: Reserved
 *   0001: SVGA_ESCAPE_VMWARE_LOG (svga_binary_logger.h)
 *   0002: SVGA_ESCAPE_VMWARE_VIDEO (svga_overlay.h)
 *   0003: SVGA_ESCAPE_VMWARE_HINT (svga_escape.h)
 */

#घोषणा SVGA_ESCAPE_VMWARE_MAJOR_MASK  0xFFFF0000


/*
 * SVGA Hपूर्णांक commands.
 *
 * These escapes let the SVGA driver provide optional inक्रमmation to
 * he host about the state of the guest or guest applications. The
 * host can use these hपूर्णांकs to make user पूर्णांकerface or perक्रमmance
 * decisions.
 *
 * Notes:
 *
 *   - SVGA_ESCAPE_VMWARE_HINT_FULLSCREEN is deprecated क्रम guests
 *     that use the SVGA Screen Object extension. Instead of sending
 *     this escape, use the SVGA_SCREEN_FULLSCREEN_HINT flag on your
 *     Screen Object.
 */

#घोषणा SVGA_ESCAPE_VMWARE_HINT               0x00030000
#घोषणा SVGA_ESCAPE_VMWARE_HINT_FULLSCREEN    0x00030001  /* Deprecated */

प्रकार
काष्ठा अणु
   uपूर्णांक32 command;
   uपूर्णांक32 fullscreen;
   काष्ठा अणु
      पूर्णांक32 x, y;
   पूर्ण monitorPosition;
पूर्ण SVGAEscapeHपूर्णांकFullscreen;

#पूर्ण_अगर /* _SVGA_ESCAPE_H_ */
