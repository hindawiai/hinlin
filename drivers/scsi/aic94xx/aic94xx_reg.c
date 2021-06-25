<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Aic94xx SAS/SATA driver रेजिस्टर access.
 *
 * Copyright (C) 2005 Adaptec, Inc.  All rights reserved.
 * Copyright (C) 2005 Luben Tuikov <luben_tuikov@adaptec.com>
 */

#समावेश <linux/pci.h>
#समावेश "aic94xx_reg.h"
#समावेश "aic94xx.h"

/* Writing to device address space.
 * Offset comes beक्रमe value to remind that the operation of
 * this function is *offs = val.
 */
अटल व्योम asd_ग_लिखो_byte(काष्ठा asd_ha_काष्ठा *asd_ha,
			   अचिन्हित दीर्घ offs, u8 val)
अणु
	अगर (unlikely(asd_ha->iospace))
		outb(val,
		     (अचिन्हित दीर्घ)asd_ha->io_handle[0].addr + (offs & 0xFF));
	अन्यथा
		ग_लिखोb(val, asd_ha->io_handle[0].addr + offs);
	wmb();
पूर्ण

अटल व्योम asd_ग_लिखो_word(काष्ठा asd_ha_काष्ठा *asd_ha,
			   अचिन्हित दीर्घ offs, u16 val)
अणु
	अगर (unlikely(asd_ha->iospace))
		outw(val,
		     (अचिन्हित दीर्घ)asd_ha->io_handle[0].addr + (offs & 0xFF));
	अन्यथा
		ग_लिखोw(val, asd_ha->io_handle[0].addr + offs);
	wmb();
पूर्ण

अटल व्योम asd_ग_लिखो_dword(काष्ठा asd_ha_काष्ठा *asd_ha,
			    अचिन्हित दीर्घ offs, u32 val)
अणु
	अगर (unlikely(asd_ha->iospace))
		outl(val,
		     (अचिन्हित दीर्घ)asd_ha->io_handle[0].addr + (offs & 0xFF));
	अन्यथा
		ग_लिखोl(val, asd_ha->io_handle[0].addr + offs);
	wmb();
पूर्ण

/* Reading from device address space.
 */
अटल u8 asd_पढ़ो_byte(काष्ठा asd_ha_काष्ठा *asd_ha, अचिन्हित दीर्घ offs)
अणु
	u8 val;
	अगर (unlikely(asd_ha->iospace))
		val = inb((अचिन्हित दीर्घ) asd_ha->io_handle[0].addr
			  + (offs & 0xFF));
	अन्यथा
		val = पढ़ोb(asd_ha->io_handle[0].addr + offs);
	rmb();
	वापस val;
पूर्ण

अटल u16 asd_पढ़ो_word(काष्ठा asd_ha_काष्ठा *asd_ha,
			 अचिन्हित दीर्घ offs)
अणु
	u16 val;
	अगर (unlikely(asd_ha->iospace))
		val = inw((अचिन्हित दीर्घ)asd_ha->io_handle[0].addr
			  + (offs & 0xFF));
	अन्यथा
		val = पढ़ोw(asd_ha->io_handle[0].addr + offs);
	rmb();
	वापस val;
पूर्ण

अटल u32 asd_पढ़ो_dword(काष्ठा asd_ha_काष्ठा *asd_ha,
			  अचिन्हित दीर्घ offs)
अणु
	u32 val;
	अगर (unlikely(asd_ha->iospace))
		val = inl((अचिन्हित दीर्घ) asd_ha->io_handle[0].addr
			  + (offs & 0xFF));
	अन्यथा
		val = पढ़ोl(asd_ha->io_handle[0].addr + offs);
	rmb();
	वापस val;
पूर्ण

अटल अंतरभूत u32 asd_mem_offs_swa(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत u32 asd_mem_offs_swc(व्योम)
अणु
	वापस asd_mem_offs_swa() + MBAR0_SWA_SIZE;
पूर्ण

अटल अंतरभूत u32 asd_mem_offs_swb(व्योम)
अणु
	वापस asd_mem_offs_swc() + MBAR0_SWC_SIZE + 0x20;
पूर्ण

/* We know that the रेजिस्टर wanted is in the range
 * of the sliding winकरोw.
 */
#घोषणा ASD_READ_SW(ww, type, ord)					\
अटल type asd_पढ़ो_##ww##_##ord(काष्ठा asd_ha_काष्ठा *asd_ha,		\
				   u32 reg)				\
अणु									\
	काष्ठा asd_ha_addrspace *io_handle = &asd_ha->io_handle[0];	\
	u32 map_offs = (reg - io_handle->ww##_base) + asd_mem_offs_##ww();\
	वापस asd_पढ़ो_##ord(asd_ha, (अचिन्हित दीर्घ)map_offs);	\
पूर्ण

#घोषणा ASD_WRITE_SW(ww, type, ord)					\
अटल व्योम asd_ग_लिखो_##ww##_##ord(काष्ठा asd_ha_काष्ठा *asd_ha,	\
				    u32 reg, type val)			\
अणु									\
	काष्ठा asd_ha_addrspace *io_handle = &asd_ha->io_handle[0];	\
	u32 map_offs = (reg - io_handle->ww##_base) + asd_mem_offs_##ww();\
	asd_ग_लिखो_##ord(asd_ha, (अचिन्हित दीर्घ)map_offs, val);		\
पूर्ण

ASD_READ_SW(swa, u8,  byte);
ASD_READ_SW(swa, u16, word);
ASD_READ_SW(swa, u32, dword);

ASD_READ_SW(swb, u8,  byte);
ASD_READ_SW(swb, u16, word);
ASD_READ_SW(swb, u32, dword);

ASD_READ_SW(swc, u8,  byte);
ASD_READ_SW(swc, u16, word);
ASD_READ_SW(swc, u32, dword);

ASD_WRITE_SW(swa, u8,  byte);
ASD_WRITE_SW(swa, u16, word);
ASD_WRITE_SW(swa, u32, dword);

ASD_WRITE_SW(swb, u8,  byte);
ASD_WRITE_SW(swb, u16, word);
ASD_WRITE_SW(swb, u32, dword);

ASD_WRITE_SW(swc, u8,  byte);
ASD_WRITE_SW(swc, u16, word);
ASD_WRITE_SW(swc, u32, dword);

/*
 * A word about sliding winकरोws:
 * MBAR0 is भागided पूर्णांकo sliding winकरोws A, C and B, in that order.
 * SWA starts at offset 0 of MBAR0, up to 0x57, with size 0x58 bytes.
 * SWC starts at offset 0x58 of MBAR0, up to 0x60, with size 0x8 bytes.
 * From 0x60 to 0x7F, we have a copy of PCI config space 0x60-0x7F.
 * SWB starts at offset 0x80 of MBAR0 and extends to the end of MBAR0.
 * See asd_init_sw() in aic94xx_hwi.c
 *
 * We map the most common रेजिस्टरs we'd access of the पूर्णांकernal 4GB
 * host adapter memory space.  If a रेजिस्टर/पूर्णांकernal memory location
 * is wanted which is not mapped, we slide SWB, by paging it,
 * see asd_move_swb() in aic94xx_reg.c.
 */

/**
 * asd_move_swb -- move sliding winकरोw B
 * @asd_ha: poपूर्णांकer to host adapter काष्ठाure
 * @reg: रेजिस्टर desired to be within range of the new winकरोw
 */
अटल व्योम asd_move_swb(काष्ठा asd_ha_काष्ठा *asd_ha, u32 reg)
अणु
	u32 base = reg & ~(MBAR0_SWB_SIZE-1);
	pci_ग_लिखो_config_dword(asd_ha->pcidev, PCI_CONF_MBAR0_SWB, base);
	asd_ha->io_handle[0].swb_base = base;
पूर्ण

अटल व्योम __asd_ग_लिखो_reg_byte(काष्ठा asd_ha_काष्ठा *asd_ha, u32 reg, u8 val)
अणु
	काष्ठा asd_ha_addrspace *io_handle=&asd_ha->io_handle[0];
	BUG_ON(reg >= 0xC0000000 || reg < ALL_BASE_ADDR);
	अगर (io_handle->swa_base <= reg
	    && reg < io_handle->swa_base + MBAR0_SWA_SIZE)
		asd_ग_लिखो_swa_byte (asd_ha, reg,val);
	अन्यथा अगर (io_handle->swb_base <= reg
		 && reg < io_handle->swb_base + MBAR0_SWB_SIZE)
		asd_ग_लिखो_swb_byte (asd_ha, reg, val);
	अन्यथा अगर (io_handle->swc_base <= reg
		 && reg < io_handle->swc_base + MBAR0_SWC_SIZE)
		asd_ग_लिखो_swc_byte (asd_ha, reg, val);
	अन्यथा अणु
		/* Ok, we have to move SWB */
		asd_move_swb(asd_ha, reg);
		asd_ग_लिखो_swb_byte (asd_ha, reg, val);
	पूर्ण
पूर्ण

#घोषणा ASD_WRITE_REG(type, ord)                                  \
व्योम asd_ग_लिखो_reg_##ord (काष्ठा asd_ha_काष्ठा *asd_ha, u32 reg, type val)\
अणु                                                                 \
	काष्ठा asd_ha_addrspace *io_handle=&asd_ha->io_handle[0]; \
	अचिन्हित दीर्घ flags;                                      \
	BUG_ON(reg >= 0xC0000000 || reg < ALL_BASE_ADDR);         \
	spin_lock_irqsave(&asd_ha->iolock, flags);                \
	अगर (io_handle->swa_base <= reg                            \
	    && reg < io_handle->swa_base + MBAR0_SWA_SIZE)        \
		asd_ग_लिखो_swa_##ord (asd_ha, reg,val);            \
	अन्यथा अगर (io_handle->swb_base <= reg                       \
		 && reg < io_handle->swb_base + MBAR0_SWB_SIZE)   \
		asd_ग_लिखो_swb_##ord (asd_ha, reg, val);           \
	अन्यथा अगर (io_handle->swc_base <= reg                       \
		 && reg < io_handle->swc_base + MBAR0_SWC_SIZE)   \
		asd_ग_लिखो_swc_##ord (asd_ha, reg, val);           \
	अन्यथा अणु                                                    \
		/* Ok, we have to move SWB */                     \
		asd_move_swb(asd_ha, reg);                        \
		asd_ग_लिखो_swb_##ord (asd_ha, reg, val);           \
	पूर्ण                                                         \
	spin_unlock_irqrestore(&asd_ha->iolock, flags);           \
पूर्ण

ASD_WRITE_REG(u8, byte);
ASD_WRITE_REG(u16,word);
ASD_WRITE_REG(u32,dword);

अटल u8 __asd_पढ़ो_reg_byte(काष्ठा asd_ha_काष्ठा *asd_ha, u32 reg)
अणु
	काष्ठा asd_ha_addrspace *io_handle=&asd_ha->io_handle[0];
	u8 val;
	BUG_ON(reg >= 0xC0000000 || reg < ALL_BASE_ADDR);
	अगर (io_handle->swa_base <= reg
	    && reg < io_handle->swa_base + MBAR0_SWA_SIZE)
		val = asd_पढ़ो_swa_byte (asd_ha, reg);
	अन्यथा अगर (io_handle->swb_base <= reg
		 && reg < io_handle->swb_base + MBAR0_SWB_SIZE)
		val = asd_पढ़ो_swb_byte (asd_ha, reg);
	अन्यथा अगर (io_handle->swc_base <= reg
		 && reg < io_handle->swc_base + MBAR0_SWC_SIZE)
		val = asd_पढ़ो_swc_byte (asd_ha, reg);
	अन्यथा अणु
		/* Ok, we have to move SWB */
		asd_move_swb(asd_ha, reg);
		val = asd_पढ़ो_swb_byte (asd_ha, reg);
	पूर्ण
	वापस val;
पूर्ण

#घोषणा ASD_READ_REG(type, ord)                                   \
type asd_पढ़ो_reg_##ord (काष्ठा asd_ha_काष्ठा *asd_ha, u32 reg)   \
अणु                                                                 \
	काष्ठा asd_ha_addrspace *io_handle=&asd_ha->io_handle[0]; \
	type val;                                                 \
	अचिन्हित दीर्घ flags;                                      \
	BUG_ON(reg >= 0xC0000000 || reg < ALL_BASE_ADDR);         \
	spin_lock_irqsave(&asd_ha->iolock, flags);                \
	अगर (io_handle->swa_base <= reg                            \
	    && reg < io_handle->swa_base + MBAR0_SWA_SIZE)        \
		val = asd_पढ़ो_swa_##ord (asd_ha, reg);           \
	अन्यथा अगर (io_handle->swb_base <= reg                       \
		 && reg < io_handle->swb_base + MBAR0_SWB_SIZE)   \
		val = asd_पढ़ो_swb_##ord (asd_ha, reg);           \
	अन्यथा अगर (io_handle->swc_base <= reg                       \
		 && reg < io_handle->swc_base + MBAR0_SWC_SIZE)   \
		val = asd_पढ़ो_swc_##ord (asd_ha, reg);           \
	अन्यथा अणु                                                    \
		/* Ok, we have to move SWB */                     \
		asd_move_swb(asd_ha, reg);                        \
		val = asd_पढ़ो_swb_##ord (asd_ha, reg);           \
	पूर्ण                                                         \
	spin_unlock_irqrestore(&asd_ha->iolock, flags);           \
	वापस val;                                               \
पूर्ण

ASD_READ_REG(u8, byte);
ASD_READ_REG(u16,word);
ASD_READ_REG(u32,dword);

/**
 * asd_पढ़ो_reg_string -- पढ़ो a string of bytes from io space memory
 * @asd_ha: poपूर्णांकer to host adapter काष्ठाure
 * @dst: poपूर्णांकer to a destination buffer where data will be written to
 * @offs: start offset (रेजिस्टर) to पढ़ो from
 * @count: number of bytes to पढ़ो
 */
व्योम asd_पढ़ो_reg_string(काष्ठा asd_ha_काष्ठा *asd_ha, व्योम *dst,
			 u32 offs, पूर्णांक count)
अणु
	u8 *p = dst;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&asd_ha->iolock, flags);
	क्रम ( ; count > 0; count--, offs++, p++)
		*p = __asd_पढ़ो_reg_byte(asd_ha, offs);
	spin_unlock_irqrestore(&asd_ha->iolock, flags);
पूर्ण

/**
 * asd_ग_लिखो_reg_string -- ग_लिखो a string of bytes to io space memory
 * @asd_ha: poपूर्णांकer to host adapter काष्ठाure
 * @src: poपूर्णांकer to source buffer where data will be पढ़ो from
 * @offs: start offset (रेजिस्टर) to ग_लिखो to
 * @count: number of bytes to ग_लिखो
 */
व्योम asd_ग_लिखो_reg_string(काष्ठा asd_ha_काष्ठा *asd_ha, व्योम *src,
			  u32 offs, पूर्णांक count)
अणु
	u8 *p = src;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&asd_ha->iolock, flags);
	क्रम ( ; count > 0; count--, offs++, p++)
		__asd_ग_लिखो_reg_byte(asd_ha, offs, *p);
	spin_unlock_irqrestore(&asd_ha->iolock, flags);
पूर्ण
