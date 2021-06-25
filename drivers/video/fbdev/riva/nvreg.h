<शैली गुरु>
/* $XConsortium: nvreg.h /मुख्य/2 1996/10/28 05:13:41 kaleb $ */
/*
 * Copyright 1996-1997  David J. McKay
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * DAVID J. MCKAY BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
 * OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/* $XFree86: xc/programs/Xserver/hw/xमुक्त86/vga256/drivers/nv/nvreg.h,v 3.2.2.1 1998/01/18 10:35:36 hohndel Exp $ */

#अगर_अघोषित __NVREG_H_
#घोषणा __NVREG_H_

/* Little macro to स्थिरruct biपंचांगask क्रम contiguous ranges of bits */
#घोषणा BITMASK(t,b) (((अचिन्हित)(1U << (((t)-(b)+1)))-1)  << (b))
#घोषणा MASKEXPAND(mask) BITMASK(1?mask,0?mask)

/* Macro to set specअगरic bitfields (mask has to be a macro x:y) ! */
#घोषणा SetBF(mask,value) ((value) << (0?mask))
#घोषणा GetBF(var,mask) (((अचिन्हित)((var) & MASKEXPAND(mask))) >> (0?mask) )

#घोषणा MaskAndSetBF(var,mask,value) (var)=(((var)&(~MASKEXPAND(mask)) \
                                             | SetBF(mask,value)))

#घोषणा DEVICE_BASE(device) (0?NV##_##device)
#घोषणा DEVICE_SIZE(device) ((1?NV##_##device) - DEVICE_BASE(device)+1)

/* This is where we will have to have conditional compilation */
#घोषणा DEVICE_ACCESS(device,reg) \
  nvCONTROL[(NV_##device##_##reg)/4]

#घोषणा DEVICE_WRITE(device,reg,value) DEVICE_ACCESS(device,reg)=(value)
#घोषणा DEVICE_READ(device,reg)        DEVICE_ACCESS(device,reg)
#घोषणा DEVICE_PRINT(device,reg) \
  ErrorF("NV_"#device"_"#reg"=#%08lx\n",DEVICE_ACCESS(device,reg))
#घोषणा DEVICE_DEF(device,mask,value) \
  SetBF(NV_##device##_##mask,NV_##device##_##mask##_##value)
#घोषणा DEVICE_VALUE(device,mask,value) SetBF(NV_##device##_##mask,value)
#घोषणा DEVICE_MASK(device,mask) MASKEXPAND(NV_##device##_##mask)

#घोषणा PDAC_Write(reg,value)           DEVICE_WRITE(PDAC,reg,value)
#घोषणा PDAC_Read(reg)                  DEVICE_READ(PDAC,reg)
#घोषणा PDAC_Prपूर्णांक(reg)                 DEVICE_PRINT(PDAC,reg)
#घोषणा PDAC_Def(mask,value)            DEVICE_DEF(PDAC,mask,value)
#घोषणा PDAC_Val(mask,value)            DEVICE_VALUE(PDAC,mask,value)
#घोषणा PDAC_Mask(mask)                 DEVICE_MASK(PDAC,mask)

#घोषणा PFB_Write(reg,value)            DEVICE_WRITE(PFB,reg,value)
#घोषणा PFB_Read(reg)                   DEVICE_READ(PFB,reg)
#घोषणा PFB_Prपूर्णांक(reg)                  DEVICE_PRINT(PFB,reg)
#घोषणा PFB_Def(mask,value)             DEVICE_DEF(PFB,mask,value)
#घोषणा PFB_Val(mask,value)             DEVICE_VALUE(PFB,mask,value)
#घोषणा PFB_Mask(mask)                  DEVICE_MASK(PFB,mask)

#घोषणा PRM_Write(reg,value)            DEVICE_WRITE(PRM,reg,value)
#घोषणा PRM_Read(reg)                   DEVICE_READ(PRM,reg)
#घोषणा PRM_Prपूर्णांक(reg)                  DEVICE_PRINT(PRM,reg)
#घोषणा PRM_Def(mask,value)             DEVICE_DEF(PRM,mask,value)
#घोषणा PRM_Val(mask,value)             DEVICE_VALUE(PRM,mask,value)
#घोषणा PRM_Mask(mask)                  DEVICE_MASK(PRM,mask)

#घोषणा PGRAPH_Write(reg,value)         DEVICE_WRITE(PGRAPH,reg,value)
#घोषणा PGRAPH_Read(reg)                DEVICE_READ(PGRAPH,reg)
#घोषणा PGRAPH_Prपूर्णांक(reg)               DEVICE_PRINT(PGRAPH,reg)
#घोषणा PGRAPH_Def(mask,value)          DEVICE_DEF(PGRAPH,mask,value)
#घोषणा PGRAPH_Val(mask,value)          DEVICE_VALUE(PGRAPH,mask,value)
#घोषणा PGRAPH_Mask(mask)               DEVICE_MASK(PGRAPH,mask)

#घोषणा PDMA_Write(reg,value)           DEVICE_WRITE(PDMA,reg,value)
#घोषणा PDMA_Read(reg)                  DEVICE_READ(PDMA,reg)
#घोषणा PDMA_Prपूर्णांक(reg)                 DEVICE_PRINT(PDMA,reg)
#घोषणा PDMA_Def(mask,value)            DEVICE_DEF(PDMA,mask,value)
#घोषणा PDMA_Val(mask,value)            DEVICE_VALUE(PDMA,mask,value)
#घोषणा PDMA_Mask(mask)                 DEVICE_MASK(PDMA,mask)

#घोषणा PTIMER_Write(reg,value)         DEVICE_WRITE(PTIMER,reg,value)
#घोषणा PTIMER_Read(reg)                DEVICE_READ(PTIMER,reg)
#घोषणा PTIMER_Prपूर्णांक(reg)               DEVICE_PRINT(PTIMER,reg)
#घोषणा PTIMER_Def(mask,value)          DEVICE_DEF(PTIMER,mask,value)
#घोषणा PTIMER_Val(mask,value)          DEVICE_VALUE(PTIEMR,mask,value)
#घोषणा PTIMER_Mask(mask)               DEVICE_MASK(PTIMER,mask)

#घोषणा PEXTDEV_Write(reg,value)         DEVICE_WRITE(PEXTDEV,reg,value)
#घोषणा PEXTDEV_Read(reg)                DEVICE_READ(PEXTDEV,reg)
#घोषणा PEXTDEV_Prपूर्णांक(reg)               DEVICE_PRINT(PEXTDEV,reg)
#घोषणा PEXTDEV_Def(mask,value)          DEVICE_DEF(PEXTDEV,mask,value)
#घोषणा PEXTDEV_Val(mask,value)          DEVICE_VALUE(PEXTDEV,mask,value)
#घोषणा PEXTDEV_Mask(mask)               DEVICE_MASK(PEXTDEV,mask)

#घोषणा PFIFO_Write(reg,value)          DEVICE_WRITE(PFIFO,reg,value)
#घोषणा PFIFO_Read(reg)                 DEVICE_READ(PFIFO,reg)
#घोषणा PFIFO_Prपूर्णांक(reg)                DEVICE_PRINT(PFIFO,reg)
#घोषणा PFIFO_Def(mask,value)           DEVICE_DEF(PFIFO,mask,value)
#घोषणा PFIFO_Val(mask,value)           DEVICE_VALUE(PFIFO,mask,value)
#घोषणा PFIFO_Mask(mask)                DEVICE_MASK(PFIFO,mask)

#घोषणा PRAM_Write(reg,value)           DEVICE_WRITE(PRAM,reg,value)
#घोषणा PRAM_Read(reg)                  DEVICE_READ(PRAM,reg)
#घोषणा PRAM_Prपूर्णांक(reg)                 DEVICE_PRINT(PRAM,reg)
#घोषणा PRAM_Def(mask,value)            DEVICE_DEF(PRAM,mask,value)
#घोषणा PRAM_Val(mask,value)            DEVICE_VALUE(PRAM,mask,value)
#घोषणा PRAM_Mask(mask)                 DEVICE_MASK(PRAM,mask)

#घोषणा PRAMFC_Write(reg,value)         DEVICE_WRITE(PRAMFC,reg,value)
#घोषणा PRAMFC_Read(reg)                DEVICE_READ(PRAMFC,reg)
#घोषणा PRAMFC_Prपूर्णांक(reg)               DEVICE_PRINT(PRAMFC,reg)
#घोषणा PRAMFC_Def(mask,value)          DEVICE_DEF(PRAMFC,mask,value)
#घोषणा PRAMFC_Val(mask,value)          DEVICE_VALUE(PRAMFC,mask,value)
#घोषणा PRAMFC_Mask(mask)               DEVICE_MASK(PRAMFC,mask)

#घोषणा PMC_Write(reg,value)            DEVICE_WRITE(PMC,reg,value)
#घोषणा PMC_Read(reg)                   DEVICE_READ(PMC,reg)
#घोषणा PMC_Prपूर्णांक(reg)                  DEVICE_PRINT(PMC,reg)
#घोषणा PMC_Def(mask,value)             DEVICE_DEF(PMC,mask,value)
#घोषणा PMC_Val(mask,value)             DEVICE_VALUE(PMC,mask,value)
#घोषणा PMC_Mask(mask)                  DEVICE_MASK(PMC,mask)

#घोषणा PMC_Write(reg,value)            DEVICE_WRITE(PMC,reg,value)
#घोषणा PMC_Read(reg)                   DEVICE_READ(PMC,reg)
#घोषणा PMC_Prपूर्णांक(reg)                  DEVICE_PRINT(PMC,reg)
#घोषणा PMC_Def(mask,value)             DEVICE_DEF(PMC,mask,value)
#घोषणा PMC_Val(mask,value)             DEVICE_VALUE(PMC,mask,value)
#घोषणा PMC_Mask(mask)                  DEVICE_MASK(PMC,mask)


#घोषणा PBUS_Write(reg,value)         DEVICE_WRITE(PBUS,reg,value)
#घोषणा PBUS_Read(reg)                DEVICE_READ(PBUS,reg)
#घोषणा PBUS_Prपूर्णांक(reg)               DEVICE_PRINT(PBUS,reg)
#घोषणा PBUS_Def(mask,value)          DEVICE_DEF(PBUS,mask,value)
#घोषणा PBUS_Val(mask,value)          DEVICE_VALUE(PBUS,mask,value)
#घोषणा PBUS_Mask(mask)               DEVICE_MASK(PBUS,mask)


#घोषणा PRAMDAC_Write(reg,value)         DEVICE_WRITE(PRAMDAC,reg,value)
#घोषणा PRAMDAC_Read(reg)                DEVICE_READ(PRAMDAC,reg)
#घोषणा PRAMDAC_Prपूर्णांक(reg)               DEVICE_PRINT(PRAMDAC,reg)
#घोषणा PRAMDAC_Def(mask,value)          DEVICE_DEF(PRAMDAC,mask,value)
#घोषणा PRAMDAC_Val(mask,value)          DEVICE_VALUE(PRAMDAC,mask,value)
#घोषणा PRAMDAC_Mask(mask)               DEVICE_MASK(PRAMDAC,mask)


#घोषणा PDAC_ReadExt(reg) \
  ((PDAC_Write(INDEX_LO,(NV_PDAC_EXT_##reg) & 0xff)),\
  (PDAC_Write(INDEX_HI,((NV_PDAC_EXT_##reg) >> 8) & 0xff)),\
  (PDAC_Read(INDEX_DATA)))

#घोषणा PDAC_WriteExt(reg,value)\
  ((PDAC_Write(INDEX_LO,(NV_PDAC_EXT_##reg) & 0xff)),\
  (PDAC_Write(INDEX_HI,((NV_PDAC_EXT_##reg) >> 8) & 0xff)),\
  (PDAC_Write(INDEX_DATA,(value))))

#घोषणा CRTC_Write(index,value) outb((index), 0x3d4); outb(value, 0x3d5)
#घोषणा CRTC_Read(index) (outb(index, 0x3d4),inb(0x3d5))

#घोषणा PCRTC_Write(index,value) CRTC_Write(NV_PCRTC_##index,value)
#घोषणा PCRTC_Read(index) CRTC_Read(NV_PCRTC_##index)

#घोषणा PCRTC_Def(mask,value)          DEVICE_DEF(PCRTC,mask,value)
#घोषणा PCRTC_Val(mask,value)          DEVICE_VALUE(PCRTC,mask,value)
#घोषणा PCRTC_Mask(mask)               DEVICE_MASK(PCRTC,mask)

#घोषणा SR_Write(index,value) outb(0x3c4,(index));outb(0x3c5,value)
#घोषणा SR_Read(index) (outb(0x3c4,index),inb(0x3c5))

बाह्य अस्थिर अचिन्हित  *nvCONTROL;

प्रकार क्रमागत अणुNV1,NV3,NV4,NumNVChipsपूर्ण NVChipType;

NVChipType GetChipType(व्योम);

#पूर्ण_अगर


