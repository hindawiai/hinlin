<शैली गुरु>
/***************************************************************************\
|*                                                                           *|
|*       Copyright 1993-2003 NVIDIA, Corporation.  All rights reserved.      *|
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
 * GPL Licensing Note - According to Mark Vojkovich, author of the Xorg/
 * XFree86 'nv' driver, this source code is provided under MIT-style licensing
 * where the source code is provided "as is" without warranty of any kind.
 * The only usage restriction is क्रम the copyright notices to be retained
 * whenever code is used.
 *
 * Antonino Daplas <adaplas@pol.net> 2005-03-11
 */

#अगर_अघोषित __NV_LOCAL_H__
#घोषणा __NV_LOCAL_H__

/*
 * This file includes any environment or machine specअगरic values to access the
 * HW.  Put all affected includes, typdefs, etc. here so the riva_hw.* files
 * can stay generic in nature.
 */

/*
 * HW access macros.  These assume memory-mapped I/O, and not normal I/O space.
 */
#घोषणा NV_WR08(p,i,d)  (__raw_ग_लिखोb((d), (व्योम __iomem *)(p) + (i)))
#घोषणा NV_RD08(p,i)    (__raw_पढ़ोb((व्योम __iomem *)(p) + (i)))
#घोषणा NV_WR16(p,i,d)  (__raw_ग_लिखोw((d), (व्योम __iomem *)(p) + (i)))
#घोषणा NV_RD16(p,i)    (__raw_पढ़ोw((व्योम __iomem *)(p) + (i)))
#घोषणा NV_WR32(p,i,d)  (__raw_ग_लिखोl((d), (व्योम __iomem *)(p) + (i)))
#घोषणा NV_RD32(p,i)    (__raw_पढ़ोl((व्योम __iomem *)(p) + (i)))

/* VGA I/O is now always करोne through MMIO */
#घोषणा VGA_WR08(p,i,d) (ग_लिखोb((d), (व्योम __iomem *)(p) + (i)))
#घोषणा VGA_RD08(p,i)   (पढ़ोb((व्योम __iomem *)(p) + (i)))

#घोषणा NVDmaNext(par, data) \
     NV_WR32(&(par)->dmaBase[(par)->dmaCurrent++], 0, (data))

#घोषणा NVDmaStart(info, par, tag, size) अणु    \
     अगर((par)->dmaFree <= (size))             \
        NVDmaWait(info, size);                \
     NVDmaNext(par, ((size) << 18) | (tag));  \
     (par)->dmaFree -= ((size) + 1);          \
पूर्ण

#अगर defined(__i386__)
#घोषणा _NV_FENCE() outb(0, 0x3D0);
#अन्यथा
#घोषणा _NV_FENCE() mb();
#पूर्ण_अगर

#घोषणा WRITE_PUT(par, data) अणु                   \
  _NV_FENCE()                                    \
  NV_RD08((par)->FbStart, 0);                    \
  NV_WR32(&(par)->FIFO[0x0010], 0, (data) << 2); \
  mb();                                          \
पूर्ण

#घोषणा READ_GET(par) (NV_RD32(&(par)->FIFO[0x0011], 0) >> 2)

#अगर_घोषित __LITTLE_ENDIAN

#समावेश <linux/bitrev.h>

#घोषणा reverse_order(l)        \
करो अणु                            \
	u8 *a = (u8 *)(l);      \
	a[0] = bitrev8(a[0]);   \
	a[1] = bitrev8(a[1]);   \
	a[2] = bitrev8(a[2]);   \
	a[3] = bitrev8(a[3]);   \
पूर्ण जबतक(0)
#अन्यथा
#घोषणा reverse_order(l) करो अणु पूर्ण जबतक(0)
#पूर्ण_अगर                          /* __LITTLE_ENDIAN */

#पूर्ण_अगर				/* __NV_LOCAL_H__ */
