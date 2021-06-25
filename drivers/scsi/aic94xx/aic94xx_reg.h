<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Aic94xx SAS/SATA driver hardware रेजिस्टरs definitions.
 *
 * Copyright (C) 2005 Adaptec, Inc.  All rights reserved.
 * Copyright (C) 2005 Luben Tuikov <luben_tuikov@adaptec.com>
 */

#अगर_अघोषित _AIC94XX_REG_H_
#घोषणा _AIC94XX_REG_H_

#समावेश <यंत्र/पन.स>
#समावेश "aic94xx_hwi.h"

/* Values */
#घोषणा AIC9410_DEV_REV_B0            0x8

/* MBAR0, SWA, SWB, SWC, पूर्णांकernal memory space addresses */
#घोषणा REG_BASE_ADDR                 0xB8000000
#घोषणा REG_BASE_ADDR_CSEQCIO         0xB8002000
#घोषणा REG_BASE_ADDR_EXSI            0xB8042800

#घोषणा MBAR0_SWA_SIZE                0x58
बाह्य  u32    MBAR0_SWB_SIZE;
#घोषणा MBAR0_SWC_SIZE                0x8

/* MBAR1, poपूर्णांकs to On Chip Memory */
#घोषणा OCM_BASE_ADDR                 0xA0000000
#घोषणा OCM_MAX_SIZE                  0x20000

/* Smallest address possible to reference */
#घोषणा ALL_BASE_ADDR                 OCM_BASE_ADDR

/* PCI configuration space रेजिस्टरs */
#घोषणा PCI_IOBAR_OFFSET              4

#घोषणा PCI_CONF_MBAR1                0x6C
#घोषणा PCI_CONF_MBAR0_SWA            0x70
#घोषणा PCI_CONF_MBAR0_SWB            0x74
#घोषणा PCI_CONF_MBAR0_SWC            0x78
#घोषणा PCI_CONF_MBAR_KEY             0x7C
#घोषणा PCI_CONF_FLSH_BAR             0xB8

#समावेश "aic94xx_reg_def.h"

u8  asd_पढ़ो_reg_byte(काष्ठा asd_ha_काष्ठा *asd_ha, u32 reg);
u16 asd_पढ़ो_reg_word(काष्ठा asd_ha_काष्ठा *asd_ha, u32 reg);
u32 asd_पढ़ो_reg_dword(काष्ठा asd_ha_काष्ठा *asd_ha, u32 reg);

व्योम asd_ग_लिखो_reg_byte(काष्ठा asd_ha_काष्ठा *asd_ha, u32 reg, u8 val);
व्योम asd_ग_लिखो_reg_word(काष्ठा asd_ha_काष्ठा *asd_ha, u32 reg, u16 val);
व्योम asd_ग_लिखो_reg_dword(काष्ठा asd_ha_काष्ठा *asd_ha, u32 reg, u32 val);

व्योम asd_पढ़ो_reg_string(काष्ठा asd_ha_काष्ठा *asd_ha, व्योम *dst,
			 u32 offs, पूर्णांक count);
व्योम asd_ग_लिखो_reg_string(काष्ठा asd_ha_काष्ठा *asd_ha, व्योम *src,
			  u32 offs, पूर्णांक count);

#घोषणा ASD_READ_OCM(type, ord, S)                                    \
अटल अंतरभूत type asd_पढ़ो_ocm_##ord (काष्ठा asd_ha_काष्ठा *asd_ha,  \
					 u32 offs)                    \
अणु                                                                     \
	काष्ठा asd_ha_addrspace *io_handle = &asd_ha->io_handle[1];   \
	type val = पढ़ो##S (io_handle->addr + (अचिन्हित दीर्घ) offs);  \
	rmb();                                                        \
	वापस val;                                                   \
पूर्ण

ASD_READ_OCM(u8, byte, b);
ASD_READ_OCM(u16,word, w);
ASD_READ_OCM(u32,dword,l);

#घोषणा ASD_WRITE_OCM(type, ord, S)                                    \
अटल अंतरभूत व्योम asd_ग_लिखो_ocm_##ord (काष्ठा asd_ha_काष्ठा *asd_ha,  \
					 u32 offs, type val)          \
अणु                                                                     \
	काष्ठा asd_ha_addrspace *io_handle = &asd_ha->io_handle[1];   \
	ग_लिखो##S (val, io_handle->addr + (अचिन्हित दीर्घ) offs);       \
	वापस;                                                       \
पूर्ण

ASD_WRITE_OCM(u8, byte, b);
ASD_WRITE_OCM(u16,word, w);
ASD_WRITE_OCM(u32,dword,l);

#घोषणा ASD_DDBSITE_READ(type, ord)                                        \
अटल अंतरभूत type asd_ddbsite_पढ़ो_##ord (काष्ठा asd_ha_काष्ठा *asd_ha,   \
					   u16 ddb_site_no,                \
					   u16 offs)                       \
अणु                                                                          \
	asd_ग_लिखो_reg_word(asd_ha, ALTCIOADR, MnDDB_SITE + offs);          \
	asd_ग_लिखो_reg_word(asd_ha, ADDBPTR, ddb_site_no);                  \
	वापस asd_पढ़ो_reg_##ord (asd_ha, CTXACCESS);                     \
पूर्ण

ASD_DDBSITE_READ(u32, dword);
ASD_DDBSITE_READ(u16, word);

अटल अंतरभूत u8 asd_ddbsite_पढ़ो_byte(काष्ठा asd_ha_काष्ठा *asd_ha,
				       u16 ddb_site_no,
				       u16 offs)
अणु
	अगर (offs & 1)
		वापस asd_ddbsite_पढ़ो_word(asd_ha, ddb_site_no,
					     offs & ~1) >> 8;
	अन्यथा
		वापस asd_ddbsite_पढ़ो_word(asd_ha, ddb_site_no,
					     offs) & 0xFF;
पूर्ण


#घोषणा ASD_DDBSITE_WRITE(type, ord)                                       \
अटल अंतरभूत व्योम asd_ddbsite_ग_लिखो_##ord (काष्ठा asd_ha_काष्ठा *asd_ha,  \
					u16 ddb_site_no,                   \
					u16 offs, type val)                \
अणु                                                                          \
	asd_ग_लिखो_reg_word(asd_ha, ALTCIOADR, MnDDB_SITE + offs);          \
	asd_ग_लिखो_reg_word(asd_ha, ADDBPTR, ddb_site_no);                  \
	asd_ग_लिखो_reg_##ord (asd_ha, CTXACCESS, val);                      \
पूर्ण

ASD_DDBSITE_WRITE(u32, dword);
ASD_DDBSITE_WRITE(u16, word);

अटल अंतरभूत व्योम asd_ddbsite_ग_लिखो_byte(काष्ठा asd_ha_काष्ठा *asd_ha,
					  u16 ddb_site_no,
					  u16 offs, u8 val)
अणु
	u16 base = offs & ~1;
	u16 rval = asd_ddbsite_पढ़ो_word(asd_ha, ddb_site_no, base);
	अगर (offs & 1)
		rval = (val << 8) | (rval & 0xFF);
	अन्यथा
		rval = (rval & 0xFF00) | val;
	asd_ddbsite_ग_लिखो_word(asd_ha, ddb_site_no, base, rval);
पूर्ण


#घोषणा ASD_SCBSITE_READ(type, ord)                                        \
अटल अंतरभूत type asd_scbsite_पढ़ो_##ord (काष्ठा asd_ha_काष्ठा *asd_ha,   \
					   u16 scb_site_no,                \
					   u16 offs)                       \
अणु                                                                          \
	asd_ग_लिखो_reg_word(asd_ha, ALTCIOADR, MnSCB_SITE + offs);          \
	asd_ग_लिखो_reg_word(asd_ha, ASCBPTR, scb_site_no);                  \
	वापस asd_पढ़ो_reg_##ord (asd_ha, CTXACCESS);                     \
पूर्ण

ASD_SCBSITE_READ(u32, dword);
ASD_SCBSITE_READ(u16, word);

अटल अंतरभूत u8 asd_scbsite_पढ़ो_byte(काष्ठा asd_ha_काष्ठा *asd_ha,
				       u16 scb_site_no,
				       u16 offs)
अणु
	अगर (offs & 1)
		वापस asd_scbsite_पढ़ो_word(asd_ha, scb_site_no,
					     offs & ~1) >> 8;
	अन्यथा
		वापस asd_scbsite_पढ़ो_word(asd_ha, scb_site_no,
					     offs) & 0xFF;
पूर्ण


#घोषणा ASD_SCBSITE_WRITE(type, ord)                                       \
अटल अंतरभूत व्योम asd_scbsite_ग_लिखो_##ord (काष्ठा asd_ha_काष्ठा *asd_ha,  \
					u16 scb_site_no,                   \
					u16 offs, type val)                \
अणु                                                                          \
	asd_ग_लिखो_reg_word(asd_ha, ALTCIOADR, MnSCB_SITE + offs);          \
	asd_ग_लिखो_reg_word(asd_ha, ASCBPTR, scb_site_no);                  \
	asd_ग_लिखो_reg_##ord (asd_ha, CTXACCESS, val);                      \
पूर्ण

ASD_SCBSITE_WRITE(u32, dword);
ASD_SCBSITE_WRITE(u16, word);

अटल अंतरभूत व्योम asd_scbsite_ग_लिखो_byte(काष्ठा asd_ha_काष्ठा *asd_ha,
					  u16 scb_site_no,
					  u16 offs, u8 val)
अणु
	u16 base = offs & ~1;
	u16 rval = asd_scbsite_पढ़ो_word(asd_ha, scb_site_no, base);
	अगर (offs & 1)
		rval = (val << 8) | (rval & 0xFF);
	अन्यथा
		rval = (rval & 0xFF00) | val;
	asd_scbsite_ग_लिखो_word(asd_ha, scb_site_no, base, rval);
पूर्ण

/**
 * asd_ddbsite_update_word -- atomically update a word in a ddb site
 * @asd_ha: poपूर्णांकer to host adapter काष्ठाure
 * @ddb_site_no: the DDB site number
 * @offs: the offset पूर्णांकo the DDB
 * @oldval: old value found in that offset
 * @newval: the new value to replace it
 *
 * This function is used when the sequencers are running and we need to
 * update a DDB site atomically without expensive pausing and upausing
 * of the sequencers and accessing the DDB site through the CIO bus.
 *
 * Return 0 on success; -EFAULT on parity error; -EAGAIN अगर the old value
 * is dअगरferent than the current value at that offset.
 */
अटल अंतरभूत पूर्णांक asd_ddbsite_update_word(काष्ठा asd_ha_काष्ठा *asd_ha,
					  u16 ddb_site_no, u16 offs,
					  u16 oldval, u16 newval)
अणु
	u8  करोne;
	u16 oval = asd_ddbsite_पढ़ो_word(asd_ha, ddb_site_no, offs);
	अगर (oval != oldval)
		वापस -EAGAIN;
	asd_ग_लिखो_reg_word(asd_ha, AOLDDATA, oldval);
	asd_ग_लिखो_reg_word(asd_ha, ANEWDATA, newval);
	करो अणु
		करोne = asd_पढ़ो_reg_byte(asd_ha, ATOMICSTATCTL);
	पूर्ण जबतक (!(करोne & ATOMICDONE));
	अगर (करोne & ATOMICERR)
		वापस -EFAULT;	  /* parity error */
	अन्यथा अगर (करोne & ATOMICWIN)
		वापस 0;	  /* success */
	अन्यथा
		वापस -EAGAIN;	  /* oldval dअगरferent than current value */
पूर्ण

अटल अंतरभूत पूर्णांक asd_ddbsite_update_byte(काष्ठा asd_ha_काष्ठा *asd_ha,
					  u16 ddb_site_no, u16 offs,
					  u8 _oldval, u8 _newval)
अणु
	u16 base = offs & ~1;
	u16 oval;
	u16 nval = asd_ddbsite_पढ़ो_word(asd_ha, ddb_site_no, base);
	अगर (offs & 1) अणु
		अगर ((nval >> 8) != _oldval)
			वापस -EAGAIN;
		nval = (_newval << 8) | (nval & 0xFF);
		oval = (_oldval << 8) | (nval & 0xFF);
	पूर्ण अन्यथा अणु
		अगर ((nval & 0xFF) != _oldval)
			वापस -EAGAIN;
		nval = (nval & 0xFF00) | _newval;
		oval = (nval & 0xFF00) | _oldval;
	पूर्ण
	वापस asd_ddbsite_update_word(asd_ha, ddb_site_no, base, oval, nval);
पूर्ण

अटल अंतरभूत व्योम asd_ग_लिखो_reg_addr(काष्ठा asd_ha_काष्ठा *asd_ha, u32 reg,
				      dma_addr_t dma_handle)
अणु
	asd_ग_लिखो_reg_dword(asd_ha, reg,   ASD_BUSADDR_LO(dma_handle));
	asd_ग_लिखो_reg_dword(asd_ha, reg+4, ASD_BUSADDR_HI(dma_handle));
पूर्ण

अटल अंतरभूत u32 asd_get_cmdctx_size(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	/* DCHREVISION वापसs 0, possibly broken */
	u32 ctxmemsize = asd_पढ़ो_reg_dword(asd_ha, LmMnINT(0,0)) & CTXMEMSIZE;
	वापस ctxmemsize ? 65536 : 32768;
पूर्ण

अटल अंतरभूत u32 asd_get_devctx_size(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	u32 ctxmemsize = asd_पढ़ो_reg_dword(asd_ha, LmMnINT(0,0)) & CTXMEMSIZE;
	वापस ctxmemsize ? 8192 : 4096;
पूर्ण

अटल अंतरभूत व्योम asd_disable_पूर्णांकs(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	asd_ग_लिखो_reg_dword(asd_ha, CHIMINTEN, RST_CHIMINTEN);
पूर्ण

अटल अंतरभूत व्योम asd_enable_पूर्णांकs(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	/* Enable COM SAS पूर्णांकerrupt on errors, COMSTAT */
	asd_ग_लिखो_reg_dword(asd_ha, COMSTATEN,
			    EN_CSBUFPERR | EN_CSERR | EN_OVLYERR);
	/* Enable DCH SAS CFIFTOERR */
	asd_ग_लिखो_reg_dword(asd_ha, DCHSTATUS, EN_CFIFTOERR);
	/* Enable Host Device पूर्णांकerrupts */
	asd_ग_लिखो_reg_dword(asd_ha, CHIMINTEN, SET_CHIMINTEN);
पूर्ण

#पूर्ण_अगर
