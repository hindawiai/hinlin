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
 * svga3d_caps.h --
 *
 *       Definitions क्रम SVGA3D hardware capabilities.  Capabilities
 *       are used to query क्रम optional rendering features during
 *       driver initialization. The capability data is stored as very
 *       basic key/value dictionary within the "FIFO register" memory
 *       area at the beginning of BAR2.
 *
 *       Note that these definitions are only क्रम 3D capabilities.
 *       The SVGA device also has "device capabilities" and "FIFO
 *       capabilities", which are non-3D-specअगरic and are stored as
 *       bitfields rather than key/value pairs.
 */

#अगर_अघोषित _SVGA3D_CAPS_H_
#घोषणा _SVGA3D_CAPS_H_

#घोषणा INCLUDE_ALLOW_MODULE
#घोषणा INCLUDE_ALLOW_USERLEVEL

#समावेश "includeCheck.h"

#समावेश "svga_reg.h"

#घोषणा SVGA_FIFO_3D_CAPS_SIZE   (SVGA_FIFO_3D_CAPS_LAST - \
                                  SVGA_FIFO_3D_CAPS + 1)


/*
 * SVGA3dCapsRecordType
 *
 *    Record types that can be found in the caps block.
 *    Related record types are grouped together numerically so that
 *    SVGA3dCaps_FindRecord() can be applied on a range of record
 *    types.
 */

प्रकार क्रमागत अणु
   SVGA3DCAPS_RECORD_UNKNOWN        = 0,
   SVGA3DCAPS_RECORD_DEVCAPS_MIN    = 0x100,
   SVGA3DCAPS_RECORD_DEVCAPS        = 0x100,
   SVGA3DCAPS_RECORD_DEVCAPS_MAX    = 0x1ff,
पूर्ण SVGA3dCapsRecordType;


/*
 * SVGA3dCapsRecordHeader
 *
 *    Header field leading each caps block record. Contains the offset (in
 *    रेजिस्टर words, NOT bytes) to the next caps block record (or the end
 *    of caps block records which will be a zero word) and the record type
 *    as defined above.
 */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCapsRecordHeader अणु
   uपूर्णांक32 length;
   SVGA3dCapsRecordType type;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCapsRecordHeader;


/*
 * SVGA3dCapsRecord
 *
 *    Caps block record; "data" is a placeholder क्रम the actual data काष्ठाure
 *    contained within the record;
 */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCapsRecord अणु
   SVGA3dCapsRecordHeader header;
   uपूर्णांक32 data[1];
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCapsRecord;


प्रकार uपूर्णांक32 SVGA3dCapPair[2];

#पूर्ण_अगर
