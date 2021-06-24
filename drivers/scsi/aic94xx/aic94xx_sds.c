<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Aic94xx SAS/SATA driver access to shared data काष्ठाures and memory
 * maps.
 *
 * Copyright (C) 2005 Adaptec, Inc.  All rights reserved.
 * Copyright (C) 2005 Luben Tuikov <luben_tuikov@adaptec.com>
 */

#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>

#समावेश "aic94xx.h"
#समावेश "aic94xx_reg.h"
#समावेश "aic94xx_sds.h"

/* ---------- OCM stuff ---------- */

काष्ठा asd_ocm_dir_ent अणु
	u8 type;
	u8 offs[3];
	u8 _r1;
	u8 size[3];
पूर्ण __attribute__ ((packed));

काष्ठा asd_ocm_dir अणु
	अक्षर sig[2];
	u8   _r1[2];
	u8   major;          /* 0 */
	u8   minor;          /* 0 */
	u8   _r2;
	u8   num_de;
	काष्ठा asd_ocm_dir_ent entry[15];
पूर्ण __attribute__ ((packed));

#घोषणा	OCM_DE_OCM_सूची			0x00
#घोषणा	OCM_DE_WIN_DRVR			0x01
#घोषणा	OCM_DE_BIOS_CHIM		0x02
#घोषणा	OCM_DE_RAID_ENGN		0x03
#घोषणा	OCM_DE_BIOS_INTL		0x04
#घोषणा	OCM_DE_BIOS_CHIM_OSM		0x05
#घोषणा	OCM_DE_BIOS_CHIM_DYNAMIC	0x06
#घोषणा	OCM_DE_ADDC2C_RES0		0x07
#घोषणा	OCM_DE_ADDC2C_RES1		0x08
#घोषणा	OCM_DE_ADDC2C_RES2		0x09
#घोषणा	OCM_DE_ADDC2C_RES3		0x0A

#घोषणा OCM_INIT_सूची_ENTRIES	5
/***************************************************************************
*  OCM directory शेष
***************************************************************************/
अटल काष्ठा asd_ocm_dir OCMDirInit =
अणु
	.sig = अणु0x4D, 0x4Fपूर्ण,	/* signature */
	.num_de = OCM_INIT_सूची_ENTRIES,	/* no. of directory entries */
पूर्ण;

/***************************************************************************
*  OCM directory Entries शेष
***************************************************************************/
अटल काष्ठा asd_ocm_dir_ent OCMDirEntriesInit[OCM_INIT_सूची_ENTRIES] =
अणु
	अणु
		.type = (OCM_DE_ADDC2C_RES0),	/* Entry type  */
		.offs = अणु128पूर्ण,			/* Offset */
		.size = अणु0, 4पूर्ण,			/* size */
	पूर्ण,
	अणु
		.type = (OCM_DE_ADDC2C_RES1),	/* Entry type  */
		.offs = अणु128, 4पूर्ण,		/* Offset */
		.size = अणु0, 4पूर्ण,			/* size */
	पूर्ण,
	अणु
		.type = (OCM_DE_ADDC2C_RES2),	/* Entry type  */
		.offs = अणु128, 8पूर्ण,		/* Offset */
		.size = अणु0, 4पूर्ण,			/* size */
	पूर्ण,
	अणु
		.type = (OCM_DE_ADDC2C_RES3),	/* Entry type  */
		.offs = अणु128, 12पूर्ण,		/* Offset */
		.size = अणु0, 4पूर्ण,			/* size */
	पूर्ण,
	अणु
		.type = (OCM_DE_WIN_DRVR),	/* Entry type  */
		.offs = अणु128, 16पूर्ण,		/* Offset */
		.size = अणु128, 235, 1पूर्ण,		/* size */
	पूर्ण,
पूर्ण;

काष्ठा asd_bios_chim_काष्ठा अणु
	अक्षर sig[4];
	u8   major;          /* 1 */
	u8   minor;          /* 0 */
	u8   bios_major;
	u8   bios_minor;
	__le32  bios_build;
	u8   flags;
	u8   pci_slot;
	__le16  ue_num;
	__le16  ue_size;
	u8  _r[14];
	/* The unit element array is right here.
	 */
पूर्ण __attribute__ ((packed));

/**
 * asd_पढ़ो_ocm_seg - पढ़ो an on chip memory (OCM) segment
 * @asd_ha: poपूर्णांकer to the host adapter काष्ठाure
 * @buffer: where to ग_लिखो the पढ़ो data
 * @offs: offset पूर्णांकo OCM where to पढ़ो from
 * @size: how many bytes to पढ़ो
 *
 * Return the number of bytes not पढ़ो. Return 0 on success.
 */
अटल पूर्णांक asd_पढ़ो_ocm_seg(काष्ठा asd_ha_काष्ठा *asd_ha, व्योम *buffer,
			    u32 offs, पूर्णांक size)
अणु
	u8 *p = buffer;
	अगर (unlikely(asd_ha->iospace))
		asd_पढ़ो_reg_string(asd_ha, buffer, offs+OCM_BASE_ADDR, size);
	अन्यथा अणु
		क्रम ( ; size > 0; size--, offs++, p++)
			*p = asd_पढ़ो_ocm_byte(asd_ha, offs);
	पूर्ण
	वापस size;
पूर्ण

अटल पूर्णांक asd_पढ़ो_ocm_dir(काष्ठा asd_ha_काष्ठा *asd_ha,
			    काष्ठा asd_ocm_dir *dir, u32 offs)
अणु
	पूर्णांक err = asd_पढ़ो_ocm_seg(asd_ha, dir, offs, माप(*dir));
	अगर (err) अणु
		ASD_DPRINTK("couldn't read ocm segment\n");
		वापस err;
	पूर्ण

	अगर (dir->sig[0] != 'M' || dir->sig[1] != 'O') अणु
		ASD_DPRINTK("no valid dir signature(%c%c) at start of OCM\n",
			    dir->sig[0], dir->sig[1]);
		वापस -ENOENT;
	पूर्ण
	अगर (dir->major != 0) अणु
		asd_prपूर्णांकk("unsupported major version of ocm dir:0x%x\n",
			   dir->major);
		वापस -ENOENT;
	पूर्ण
	dir->num_de &= 0xf;
	वापस 0;
पूर्ण

/**
 * asd_ग_लिखो_ocm_seg - ग_लिखो an on chip memory (OCM) segment
 * @asd_ha: poपूर्णांकer to the host adapter काष्ठाure
 * @buffer: where to पढ़ो the ग_लिखो data
 * @offs: offset पूर्णांकo OCM to ग_लिखो to
 * @size: how many bytes to ग_लिखो
 *
 * Return the number of bytes not written. Return 0 on success.
 */
अटल व्योम asd_ग_लिखो_ocm_seg(काष्ठा asd_ha_काष्ठा *asd_ha, व्योम *buffer,
			    u32 offs, पूर्णांक size)
अणु
	u8 *p = buffer;
	अगर (unlikely(asd_ha->iospace))
		asd_ग_लिखो_reg_string(asd_ha, buffer, offs+OCM_BASE_ADDR, size);
	अन्यथा अणु
		क्रम ( ; size > 0; size--, offs++, p++)
			asd_ग_लिखो_ocm_byte(asd_ha, offs, *p);
	पूर्ण
	वापस;
पूर्ण

#घोषणा THREE_TO_NUM(X) ((X)[0] | ((X)[1] << 8) | ((X)[2] << 16))

अटल पूर्णांक asd_find_dir_entry(काष्ठा asd_ocm_dir *dir, u8 type,
			      u32 *offs, u32 *size)
अणु
	पूर्णांक i;
	काष्ठा asd_ocm_dir_ent *ent;

	क्रम (i = 0; i < dir->num_de; i++) अणु
		अगर (dir->entry[i].type == type)
			अवरोध;
	पूर्ण
	अगर (i >= dir->num_de)
		वापस -ENOENT;
	ent = &dir->entry[i];
	*offs = (u32) THREE_TO_NUM(ent->offs);
	*size = (u32) THREE_TO_NUM(ent->size);
	वापस 0;
पूर्ण

#घोषणा OCM_BIOS_CHIM_DE  2
#घोषणा BC_BIOS_PRESENT   1

अटल पूर्णांक asd_get_bios_chim(काष्ठा asd_ha_काष्ठा *asd_ha,
			     काष्ठा asd_ocm_dir *dir)
अणु
	पूर्णांक err;
	काष्ठा asd_bios_chim_काष्ठा *bc_काष्ठा;
	u32 offs, size;

	err = asd_find_dir_entry(dir, OCM_BIOS_CHIM_DE, &offs, &size);
	अगर (err) अणु
		ASD_DPRINTK("couldn't find BIOS_CHIM dir ent\n");
		जाओ out;
	पूर्ण
	err = -ENOMEM;
	bc_काष्ठा = kदो_स्मृति(माप(*bc_काष्ठा), GFP_KERNEL);
	अगर (!bc_काष्ठा) अणु
		asd_prपूर्णांकk("no memory for bios_chim struct\n");
		जाओ out;
	पूर्ण
	err = asd_पढ़ो_ocm_seg(asd_ha, (व्योम *)bc_काष्ठा, offs,
			       माप(*bc_काष्ठा));
	अगर (err) अणु
		ASD_DPRINTK("couldn't read ocm segment\n");
		जाओ out2;
	पूर्ण
	अगर (म_भेदन(bc_काष्ठा->sig, "SOIB", 4)
	    && म_भेदन(bc_काष्ठा->sig, "IPSA", 4)) अणु
		ASD_DPRINTK("BIOS_CHIM entry has no valid sig(%c%c%c%c)\n",
			    bc_काष्ठा->sig[0], bc_काष्ठा->sig[1],
			    bc_काष्ठा->sig[2], bc_काष्ठा->sig[3]);
		err = -ENOENT;
		जाओ out2;
	पूर्ण
	अगर (bc_काष्ठा->major != 1) अणु
		asd_prपूर्णांकk("BIOS_CHIM unsupported major version:0x%x\n",
			   bc_काष्ठा->major);
		err = -ENOENT;
		जाओ out2;
	पूर्ण
	अगर (bc_काष्ठा->flags & BC_BIOS_PRESENT) अणु
		asd_ha->hw_prof.bios.present = 1;
		asd_ha->hw_prof.bios.maj = bc_काष्ठा->bios_major;
		asd_ha->hw_prof.bios.min = bc_काष्ठा->bios_minor;
		asd_ha->hw_prof.bios.bld = le32_to_cpu(bc_काष्ठा->bios_build);
		ASD_DPRINTK("BIOS present (%d,%d), %d\n",
			    asd_ha->hw_prof.bios.maj,
			    asd_ha->hw_prof.bios.min,
			    asd_ha->hw_prof.bios.bld);
	पूर्ण
	asd_ha->hw_prof.ue.num = le16_to_cpu(bc_काष्ठा->ue_num);
	asd_ha->hw_prof.ue.size= le16_to_cpu(bc_काष्ठा->ue_size);
	ASD_DPRINTK("ue num:%d, ue size:%d\n", asd_ha->hw_prof.ue.num,
		    asd_ha->hw_prof.ue.size);
	size = asd_ha->hw_prof.ue.num * asd_ha->hw_prof.ue.size;
	अगर (size > 0) अणु
		err = -ENOMEM;
		asd_ha->hw_prof.ue.area = kदो_स्मृति(size, GFP_KERNEL);
		अगर (!asd_ha->hw_prof.ue.area)
			जाओ out2;
		err = asd_पढ़ो_ocm_seg(asd_ha, (व्योम *)asd_ha->hw_prof.ue.area,
				       offs + माप(*bc_काष्ठा), size);
		अगर (err) अणु
			kमुक्त(asd_ha->hw_prof.ue.area);
			asd_ha->hw_prof.ue.area = शून्य;
			asd_ha->hw_prof.ue.num  = 0;
			asd_ha->hw_prof.ue.size = 0;
			ASD_DPRINTK("couldn't read ue entries(%d)\n", err);
		पूर्ण
	पूर्ण
out2:
	kमुक्त(bc_काष्ठा);
out:
	वापस err;
पूर्ण

अटल व्योम
asd_hwi_initialize_ocm_dir (काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	पूर्णांक i;

	/* Zero OCM */
	क्रम (i = 0; i < OCM_MAX_SIZE; i += 4)
		asd_ग_लिखो_ocm_dword(asd_ha, i, 0);

	/* Write Dir */
	asd_ग_लिखो_ocm_seg(asd_ha, &OCMDirInit, 0,
			  माप(काष्ठा asd_ocm_dir));

	/* Write Dir Entries */
	क्रम (i = 0; i < OCM_INIT_सूची_ENTRIES; i++)
		asd_ग_लिखो_ocm_seg(asd_ha, &OCMDirEntriesInit[i],
				  माप(काष्ठा asd_ocm_dir) +
				  (i * माप(काष्ठा asd_ocm_dir_ent))
				  , माप(काष्ठा asd_ocm_dir_ent));

पूर्ण

अटल पूर्णांक
asd_hwi_check_ocm_access (काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	काष्ठा pci_dev *pcidev = asd_ha->pcidev;
	u32 reg;
	पूर्णांक err = 0;
	u32 v;

	/* check अगर OCM has been initialized by BIOS */
	reg = asd_पढ़ो_reg_dword(asd_ha, EXSICNFGR);

	अगर (!(reg & OCMINITIALIZED)) अणु
		err = pci_पढ़ो_config_dword(pcidev, PCIC_INTRPT_STAT, &v);
		अगर (err) अणु
			asd_prपूर्णांकk("couldn't access PCIC_INTRPT_STAT of %s\n",
					pci_name(pcidev));
			जाओ out;
		पूर्ण

		prपूर्णांकk(KERN_INFO "OCM is not initialized by BIOS,"
		       "reinitialize it and ignore it, current IntrptStatus"
		       "is 0x%x\n", v);

		अगर (v)
			err = pci_ग_लिखो_config_dword(pcidev,
						     PCIC_INTRPT_STAT, v);
		अगर (err) अणु
			asd_prपूर्णांकk("couldn't write PCIC_INTRPT_STAT of %s\n",
					pci_name(pcidev));
			जाओ out;
		पूर्ण

		asd_hwi_initialize_ocm_dir(asd_ha);

	पूर्ण
out:
	वापस err;
पूर्ण

/**
 * asd_पढ़ो_ocm - पढ़ो on chip memory (OCM)
 * @asd_ha: poपूर्णांकer to the host adapter काष्ठाure
 */
पूर्णांक asd_पढ़ो_ocm(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	पूर्णांक err;
	काष्ठा asd_ocm_dir *dir;

	अगर (asd_hwi_check_ocm_access(asd_ha))
		वापस -1;

	dir = kदो_स्मृति(माप(*dir), GFP_KERNEL);
	अगर (!dir) अणु
		asd_prपूर्णांकk("no memory for ocm dir\n");
		वापस -ENOMEM;
	पूर्ण

	err = asd_पढ़ो_ocm_dir(asd_ha, dir, 0);
	अगर (err)
		जाओ out;

	err = asd_get_bios_chim(asd_ha, dir);
out:
	kमुक्त(dir);
	वापस err;
पूर्ण

/* ---------- FLASH stuff ---------- */

#घोषणा FLASH_RESET			0xF0

#घोषणा ASD_FLASH_SIZE                  0x200000
#घोषणा FLASH_सूची_COOKIE                "*** ADAPTEC FLASH DIRECTORY *** "
#घोषणा FLASH_NEXT_ENTRY_OFFS		0x2000
#घोषणा FLASH_MAX_सूची_ENTRIES		32

#घोषणा FLASH_DE_TYPE_MASK              0x3FFFFFFF
#घोषणा FLASH_DE_MS                     0x120
#घोषणा FLASH_DE_CTRL_A_USER            0xE0

काष्ठा asd_flash_de अणु
	__le32   type;
	__le32   offs;
	__le32   pad_size;
	__le32   image_size;
	__le32   chksum;
	u8       _r[12];
	u8       version[32];
पूर्ण __attribute__ ((packed));

काष्ठा asd_flash_dir अणु
	u8    cookie[32];
	__le32   rev;		  /* 2 */
	__le32   chksum;
	__le32   chksum_antiकरोte;
	__le32   bld;
	u8    bld_id[32];	  /* build id data */
	u8    ver_data[32];	  /* date and समय of build */
	__le32   ae_mask;
	__le32   v_mask;
	__le32   oc_mask;
	u8    _r[20];
	काष्ठा asd_flash_de dir_entry[FLASH_MAX_सूची_ENTRIES];
पूर्ण __attribute__ ((packed));

काष्ठा asd_manuf_sec अणु
	अक्षर  sig[2];		  /* 'S', 'M' */
	u16   offs_next;
	u8    maj;           /* 0 */
	u8    min;           /* 0 */
	u16   chksum;
	u16   size;
	u8    _r[6];
	u8    sas_addr[SAS_ADDR_SIZE];
	u8    pcba_sn[ASD_PCBA_SN_SIZE];
	/* Here start the other segments */
	u8    linked_list[];
पूर्ण __attribute__ ((packed));

काष्ठा asd_manuf_phy_desc अणु
	u8    state;         /* low 4 bits */
#घोषणा MS_PHY_STATE_ENABLED    0
#घोषणा MS_PHY_STATE_REPORTED   1
#घोषणा MS_PHY_STATE_HIDDEN     2
	u8    phy_id;
	u16   _r;
	u8    phy_control_0; /* mode 5 reg 0x160 */
	u8    phy_control_1; /* mode 5 reg 0x161 */
	u8    phy_control_2; /* mode 5 reg 0x162 */
	u8    phy_control_3; /* mode 5 reg 0x163 */
पूर्ण __attribute__ ((packed));

काष्ठा asd_manuf_phy_param अणु
	अक्षर  sig[2];		  /* 'P', 'M' */
	u16   next;
	u8    maj;           /* 0 */
	u8    min;           /* 2 */
	u8    num_phy_desc;  /* 8 */
	u8    phy_desc_size; /* 8 */
	u8    _r[3];
	u8    usage_model_id;
	u32   _r2;
	काष्ठा asd_manuf_phy_desc phy_desc[ASD_MAX_PHYS];
पूर्ण __attribute__ ((packed));

#अगर 0
अटल स्थिर अक्षर *asd_sb_type[] = अणु
	"unknown",
	"SGPIO",
	[2 ... 0x7F] = "unknown",
	[0x80] = "ADPT_I2C",
	[0x81 ... 0xFF] = "VENDOR_UNIQUExx"
पूर्ण;
#पूर्ण_अगर

काष्ठा asd_ms_sb_desc अणु
	u8    type;
	u8    node_desc_index;
	u8    conn_desc_index;
	u8    _recvd[];
पूर्ण __attribute__ ((packed));

#अगर 0
अटल स्थिर अक्षर *asd_conn_type[] = अणु
	[0 ... 7] = "unknown",
	"SFF8470",
	"SFF8482",
	"SFF8484",
	[0x80] = "PCIX_DAUGHTER0",
	[0x81] = "SAS_DAUGHTER0",
	[0x82 ... 0xFF] = "VENDOR_UNIQUExx"
पूर्ण;

अटल स्थिर अक्षर *asd_conn_location[] = अणु
	"unknown",
	"internal",
	"external",
	"board_to_board",
पूर्ण;
#पूर्ण_अगर

काष्ठा asd_ms_conn_desc अणु
	u8    type;
	u8    location;
	u8    num_sideband_desc;
	u8    size_sideband_desc;
	u32   _resvd;
	u8    name[16];
	काष्ठा asd_ms_sb_desc sb_desc[];
पूर्ण __attribute__ ((packed));

काष्ठा asd_nd_phy_desc अणु
	u8    vp_attch_type;
	u8    attch_specअगरic[];
पूर्ण __attribute__ ((packed));

#अगर 0
अटल स्थिर अक्षर *asd_node_type[] = अणु
	"IOP",
	"IO_CONTROLLER",
	"EXPANDER",
	"PORT_MULTIPLIER",
	"PORT_MULTIPLEXER",
	"MULTI_DROP_I2C_BUS",
पूर्ण;
#पूर्ण_अगर

काष्ठा asd_ms_node_desc अणु
	u8    type;
	u8    num_phy_desc;
	u8    size_phy_desc;
	u8    _resvd;
	u8    name[16];
	काष्ठा asd_nd_phy_desc phy_desc[];
पूर्ण __attribute__ ((packed));

काष्ठा asd_ms_conn_map अणु
	अक्षर  sig[2];		  /* 'M', 'C' */
	__le16 next;
	u8    maj;		  /* 0 */
	u8    min;		  /* 0 */
	__le16 cm_size;		  /* size of this काष्ठा */
	u8    num_conn;
	u8    conn_size;
	u8    num_nodes;
	u8    usage_model_id;
	u32   _resvd;
	काष्ठा asd_ms_conn_desc conn_desc[0];
	काष्ठा asd_ms_node_desc node_desc[];
पूर्ण __attribute__ ((packed));

काष्ठा asd_ctrla_phy_entry अणु
	u8    sas_addr[SAS_ADDR_SIZE];
	u8    sas_link_rates;  /* max in hi bits, min in low bits */
	u8    flags;
	u8    sata_link_rates;
	u8    _r[5];
पूर्ण __attribute__ ((packed));

काष्ठा asd_ctrla_phy_settings अणु
	u8    id0;		  /* P'h'y */
	u8    _r;
	u16   next;
	u8    num_phys;	      /* number of PHYs in the PCI function */
	u8    _r2[3];
	काष्ठा asd_ctrla_phy_entry phy_ent[ASD_MAX_PHYS];
पूर्ण __attribute__ ((packed));

काष्ठा asd_ll_el अणु
	u8   id0;
	u8   id1;
	__le16  next;
	u8   something_here[];
पूर्ण __attribute__ ((packed));

अटल पूर्णांक asd_poll_flash(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	पूर्णांक c;
	u8 d;

	क्रम (c = 5000; c > 0; c--) अणु
		d  = asd_पढ़ो_reg_byte(asd_ha, asd_ha->hw_prof.flash.bar);
		d ^= asd_पढ़ो_reg_byte(asd_ha, asd_ha->hw_prof.flash.bar);
		अगर (!d)
			वापस 0;
		udelay(5);
	पूर्ण
	वापस -ENOENT;
पूर्ण

अटल पूर्णांक asd_reset_flash(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	पूर्णांक err;

	err = asd_poll_flash(asd_ha);
	अगर (err)
		वापस err;
	asd_ग_लिखो_reg_byte(asd_ha, asd_ha->hw_prof.flash.bar, FLASH_RESET);
	err = asd_poll_flash(asd_ha);

	वापस err;
पूर्ण

अटल पूर्णांक asd_पढ़ो_flash_seg(काष्ठा asd_ha_काष्ठा *asd_ha,
			      व्योम *buffer, u32 offs, पूर्णांक size)
अणु
	asd_पढ़ो_reg_string(asd_ha, buffer, asd_ha->hw_prof.flash.bar+offs,
			    size);
	वापस 0;
पूर्ण

/**
 * asd_find_flash_dir - finds and पढ़ोs the flash directory
 * @asd_ha: poपूर्णांकer to the host adapter काष्ठाure
 * @flash_dir: poपूर्णांकer to flash directory काष्ठाure
 *
 * If found, the flash directory segment will be copied to
 * @flash_dir.  Return 1 अगर found, 0 अगर not.
 */
अटल पूर्णांक asd_find_flash_dir(काष्ठा asd_ha_काष्ठा *asd_ha,
			      काष्ठा asd_flash_dir *flash_dir)
अणु
	u32 v;
	क्रम (v = 0; v < ASD_FLASH_SIZE; v += FLASH_NEXT_ENTRY_OFFS) अणु
		asd_पढ़ो_flash_seg(asd_ha, flash_dir, v,
				   माप(FLASH_सूची_COOKIE)-1);
		अगर (स_भेद(flash_dir->cookie, FLASH_सूची_COOKIE,
			   माप(FLASH_सूची_COOKIE)-1) == 0) अणु
			asd_ha->hw_prof.flash.dir_offs = v;
			asd_पढ़ो_flash_seg(asd_ha, flash_dir, v,
					   माप(*flash_dir));
			वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक asd_flash_getid(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	पूर्णांक err = 0;
	u32 reg;

	reg = asd_पढ़ो_reg_dword(asd_ha, EXSICNFGR);

	अगर (pci_पढ़ो_config_dword(asd_ha->pcidev, PCI_CONF_FLSH_BAR,
				  &asd_ha->hw_prof.flash.bar)) अणु
		asd_prपूर्णांकk("couldn't read PCI_CONF_FLSH_BAR of %s\n",
			   pci_name(asd_ha->pcidev));
		वापस -ENOENT;
	पूर्ण
	asd_ha->hw_prof.flash.present = 1;
	asd_ha->hw_prof.flash.wide = reg & FLASHW ? 1 : 0;
	err = asd_reset_flash(asd_ha);
	अगर (err) अणु
		ASD_DPRINTK("couldn't reset flash(%d)\n", err);
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल u16 asd_calc_flash_chksum(u16 *p, पूर्णांक size)
अणु
	u16 chksum = 0;

	जबतक (size-- > 0)
		chksum += *p++;

	वापस chksum;
पूर्ण


अटल पूर्णांक asd_find_flash_de(काष्ठा asd_flash_dir *flash_dir, u32 entry_type,
			     u32 *offs, u32 *size)
अणु
	पूर्णांक i;
	काष्ठा asd_flash_de *de;

	क्रम (i = 0; i < FLASH_MAX_सूची_ENTRIES; i++) अणु
		u32 type = le32_to_cpu(flash_dir->dir_entry[i].type);

		type &= FLASH_DE_TYPE_MASK;
		अगर (type == entry_type)
			अवरोध;
	पूर्ण
	अगर (i >= FLASH_MAX_सूची_ENTRIES)
		वापस -ENOENT;
	de = &flash_dir->dir_entry[i];
	*offs = le32_to_cpu(de->offs);
	*size = le32_to_cpu(de->pad_size);
	वापस 0;
पूर्ण

अटल पूर्णांक asd_validate_ms(काष्ठा asd_manuf_sec *ms)
अणु
	अगर (ms->sig[0] != 'S' || ms->sig[1] != 'M') अणु
		ASD_DPRINTK("manuf sec: no valid sig(%c%c)\n",
			    ms->sig[0], ms->sig[1]);
		वापस -ENOENT;
	पूर्ण
	अगर (ms->maj != 0) अणु
		asd_prपूर्णांकk("unsupported manuf. sector. major version:%x\n",
			   ms->maj);
		वापस -ENOENT;
	पूर्ण
	ms->offs_next = le16_to_cpu((__क्रमce __le16) ms->offs_next);
	ms->chksum = le16_to_cpu((__क्रमce __le16) ms->chksum);
	ms->size = le16_to_cpu((__क्रमce __le16) ms->size);

	अगर (asd_calc_flash_chksum((u16 *)ms, ms->size/2)) अणु
		asd_prपूर्णांकk("failed manuf sector checksum\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक asd_ms_get_sas_addr(काष्ठा asd_ha_काष्ठा *asd_ha,
			       काष्ठा asd_manuf_sec *ms)
अणु
	स_नकल(asd_ha->hw_prof.sas_addr, ms->sas_addr, SAS_ADDR_SIZE);
	वापस 0;
पूर्ण

अटल पूर्णांक asd_ms_get_pcba_sn(काष्ठा asd_ha_काष्ठा *asd_ha,
			      काष्ठा asd_manuf_sec *ms)
अणु
	स_नकल(asd_ha->hw_prof.pcba_sn, ms->pcba_sn, ASD_PCBA_SN_SIZE);
	asd_ha->hw_prof.pcba_sn[ASD_PCBA_SN_SIZE] = '\0';
	वापस 0;
पूर्ण

/**
 * asd_find_ll_by_id - find a linked list entry by its id
 * @start: व्योम poपूर्णांकer to the first element in the linked list
 * @id0: the first byte of the id  (offs 0)
 * @id1: the second byte of the id (offs 1)
 *
 * @start has to be the _base_ element start, since the
 * linked list entries's offset is from this poपूर्णांकer.
 * Some linked list entries use only the first id, in which हाल
 * you can pass 0xFF क्रम the second.
 */
अटल व्योम *asd_find_ll_by_id(व्योम * स्थिर start, स्थिर u8 id0, स्थिर u8 id1)
अणु
	काष्ठा asd_ll_el *el = start;

	करो अणु
		चयन (id1) अणु
		शेष:
			अगर (el->id1 == id1)
		हाल 0xFF:
				अगर (el->id0 == id0)
					वापस el;
		पूर्ण
		el = start + le16_to_cpu(el->next);
	पूर्ण जबतक (el != start);

	वापस शून्य;
पूर्ण

/**
 * asd_ms_get_phy_params - get phy parameters from the manufacturing sector
 * @asd_ha: poपूर्णांकer to the host adapter काष्ठाure
 * @manuf_sec: poपूर्णांकer to the manufacturing sector
 *
 * The manufacturing sector contans also the linked list of sub-segments,
 * since when it was पढ़ो, its size was taken from the flash directory,
 * not from the काष्ठाure size.
 *
 * HIDDEN phys करो not count in the total count.  REPORTED phys cannot
 * be enabled but are reported and counted towards the total.
 * ENABLED phys are enabled by शेष and count towards the total.
 * The असलolute total phy number is ASD_MAX_PHYS.  hw_prof->num_phys
 * merely specअगरies the number of phys the host adapter decided to
 * report.  E.g., it is possible क्रम phys 0, 1 and 2 to be HIDDEN,
 * phys 3, 4 and 5 to be REPORTED and phys 6 and 7 to be ENABLED.
 * In this हाल ASD_MAX_PHYS is 8, hw_prof->num_phys is 5, and only 2
 * are actually enabled (enabled by शेष, max number of phys
 * enableable in this हाल).
 */
अटल पूर्णांक asd_ms_get_phy_params(काष्ठा asd_ha_काष्ठा *asd_ha,
				 काष्ठा asd_manuf_sec *manuf_sec)
अणु
	पूर्णांक i;
	पूर्णांक en_phys = 0;
	पूर्णांक rep_phys = 0;
	काष्ठा asd_manuf_phy_param *phy_param;
	काष्ठा asd_manuf_phy_param dflt_phy_param;

	phy_param = asd_find_ll_by_id(manuf_sec, 'P', 'M');
	अगर (!phy_param) अणु
		ASD_DPRINTK("ms: no phy parameters found\n");
		ASD_DPRINTK("ms: Creating default phy parameters\n");
		dflt_phy_param.sig[0] = 'P';
		dflt_phy_param.sig[1] = 'M';
		dflt_phy_param.maj = 0;
		dflt_phy_param.min = 2;
		dflt_phy_param.num_phy_desc = 8;
		dflt_phy_param.phy_desc_size = माप(काष्ठा asd_manuf_phy_desc);
		क्रम (i =0; i < ASD_MAX_PHYS; i++) अणु
			dflt_phy_param.phy_desc[i].state = 0;
			dflt_phy_param.phy_desc[i].phy_id = i;
			dflt_phy_param.phy_desc[i].phy_control_0 = 0xf6;
			dflt_phy_param.phy_desc[i].phy_control_1 = 0x10;
			dflt_phy_param.phy_desc[i].phy_control_2 = 0x43;
			dflt_phy_param.phy_desc[i].phy_control_3 = 0xeb;
		पूर्ण

		phy_param = &dflt_phy_param;

	पूर्ण

	अगर (phy_param->maj != 0) अणु
		asd_prपूर्णांकk("unsupported manuf. phy param major version:0x%x\n",
			   phy_param->maj);
		वापस -ENOENT;
	पूर्ण

	ASD_DPRINTK("ms: num_phy_desc: %d\n", phy_param->num_phy_desc);
	asd_ha->hw_prof.enabled_phys = 0;
	क्रम (i = 0; i < phy_param->num_phy_desc; i++) अणु
		काष्ठा asd_manuf_phy_desc *pd = &phy_param->phy_desc[i];
		चयन (pd->state & 0xF) अणु
		हाल MS_PHY_STATE_HIDDEN:
			ASD_DPRINTK("ms: phy%d: HIDDEN\n", i);
			जारी;
		हाल MS_PHY_STATE_REPORTED:
			ASD_DPRINTK("ms: phy%d: REPORTED\n", i);
			asd_ha->hw_prof.enabled_phys &= ~(1 << i);
			rep_phys++;
			जारी;
		हाल MS_PHY_STATE_ENABLED:
			ASD_DPRINTK("ms: phy%d: ENABLED\n", i);
			asd_ha->hw_prof.enabled_phys |= (1 << i);
			en_phys++;
			अवरोध;
		पूर्ण
		asd_ha->hw_prof.phy_desc[i].phy_control_0 = pd->phy_control_0;
		asd_ha->hw_prof.phy_desc[i].phy_control_1 = pd->phy_control_1;
		asd_ha->hw_prof.phy_desc[i].phy_control_2 = pd->phy_control_2;
		asd_ha->hw_prof.phy_desc[i].phy_control_3 = pd->phy_control_3;
	पूर्ण
	asd_ha->hw_prof.max_phys = rep_phys + en_phys;
	asd_ha->hw_prof.num_phys = en_phys;
	ASD_DPRINTK("ms: max_phys:0x%x, num_phys:0x%x\n",
		    asd_ha->hw_prof.max_phys, asd_ha->hw_prof.num_phys);
	ASD_DPRINTK("ms: enabled_phys:0x%x\n", asd_ha->hw_prof.enabled_phys);
	वापस 0;
पूर्ण

अटल पूर्णांक asd_ms_get_connector_map(काष्ठा asd_ha_काष्ठा *asd_ha,
				    काष्ठा asd_manuf_sec *manuf_sec)
अणु
	काष्ठा asd_ms_conn_map *cm;

	cm = asd_find_ll_by_id(manuf_sec, 'M', 'C');
	अगर (!cm) अणु
		ASD_DPRINTK("ms: no connector map found\n");
		वापस 0;
	पूर्ण

	अगर (cm->maj != 0) अणु
		ASD_DPRINTK("ms: unsupported: connector map major version 0x%x"
			    "\n", cm->maj);
		वापस -ENOENT;
	पूर्ण

	/* XXX */

	वापस 0;
पूर्ण


/**
 * asd_process_ms - find and extract inक्रमmation from the manufacturing sector
 * @asd_ha: poपूर्णांकer to the host adapter काष्ठाure
 * @flash_dir: poपूर्णांकer to the flash directory
 */
अटल पूर्णांक asd_process_ms(काष्ठा asd_ha_काष्ठा *asd_ha,
			  काष्ठा asd_flash_dir *flash_dir)
अणु
	पूर्णांक err;
	काष्ठा asd_manuf_sec *manuf_sec;
	u32 offs, size;

	err = asd_find_flash_de(flash_dir, FLASH_DE_MS, &offs, &size);
	अगर (err) अणु
		ASD_DPRINTK("Couldn't find the manuf. sector\n");
		जाओ out;
	पूर्ण

	अगर (size == 0)
		जाओ out;

	err = -ENOMEM;
	manuf_sec = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!manuf_sec) अणु
		ASD_DPRINTK("no mem for manuf sector\n");
		जाओ out;
	पूर्ण

	err = asd_पढ़ो_flash_seg(asd_ha, (व्योम *)manuf_sec, offs, size);
	अगर (err) अणु
		ASD_DPRINTK("couldn't read manuf sector at 0x%x, size 0x%x\n",
			    offs, size);
		जाओ out2;
	पूर्ण

	err = asd_validate_ms(manuf_sec);
	अगर (err) अणु
		ASD_DPRINTK("couldn't validate manuf sector\n");
		जाओ out2;
	पूर्ण

	err = asd_ms_get_sas_addr(asd_ha, manuf_sec);
	अगर (err) अणु
		ASD_DPRINTK("couldn't read the SAS_ADDR\n");
		जाओ out2;
	पूर्ण
	ASD_DPRINTK("manuf sect SAS_ADDR %llx\n",
		    SAS_ADDR(asd_ha->hw_prof.sas_addr));

	err = asd_ms_get_pcba_sn(asd_ha, manuf_sec);
	अगर (err) अणु
		ASD_DPRINTK("couldn't read the PCBA SN\n");
		जाओ out2;
	पूर्ण
	ASD_DPRINTK("manuf sect PCBA SN %s\n", asd_ha->hw_prof.pcba_sn);

	err = asd_ms_get_phy_params(asd_ha, manuf_sec);
	अगर (err) अणु
		ASD_DPRINTK("ms: couldn't get phy parameters\n");
		जाओ out2;
	पूर्ण

	err = asd_ms_get_connector_map(asd_ha, manuf_sec);
	अगर (err) अणु
		ASD_DPRINTK("ms: couldn't get connector map\n");
		जाओ out2;
	पूर्ण

out2:
	kमुक्त(manuf_sec);
out:
	वापस err;
पूर्ण

अटल पूर्णांक asd_process_ctrla_phy_settings(काष्ठा asd_ha_काष्ठा *asd_ha,
					  काष्ठा asd_ctrla_phy_settings *ps)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < ps->num_phys; i++) अणु
		काष्ठा asd_ctrla_phy_entry *pe = &ps->phy_ent[i];

		अगर (!PHY_ENABLED(asd_ha, i))
			जारी;
		अगर (*(u64 *)pe->sas_addr == 0) अणु
			asd_ha->hw_prof.enabled_phys &= ~(1 << i);
			जारी;
		पूर्ण
		/* This is the SAS address which should be sent in IDENTIFY. */
		स_नकल(asd_ha->hw_prof.phy_desc[i].sas_addr, pe->sas_addr,
		       SAS_ADDR_SIZE);
		asd_ha->hw_prof.phy_desc[i].max_sas_lrate =
			(pe->sas_link_rates & 0xF0) >> 4;
		asd_ha->hw_prof.phy_desc[i].min_sas_lrate =
			(pe->sas_link_rates & 0x0F);
		asd_ha->hw_prof.phy_desc[i].max_sata_lrate =
			(pe->sata_link_rates & 0xF0) >> 4;
		asd_ha->hw_prof.phy_desc[i].min_sata_lrate =
			(pe->sata_link_rates & 0x0F);
		asd_ha->hw_prof.phy_desc[i].flags = pe->flags;
		ASD_DPRINTK("ctrla: phy%d: sas_addr: %llx, sas rate:0x%x-0x%x,"
			    " sata rate:0x%x-0x%x, flags:0x%x\n",
			    i,
			    SAS_ADDR(asd_ha->hw_prof.phy_desc[i].sas_addr),
			    asd_ha->hw_prof.phy_desc[i].max_sas_lrate,
			    asd_ha->hw_prof.phy_desc[i].min_sas_lrate,
			    asd_ha->hw_prof.phy_desc[i].max_sata_lrate,
			    asd_ha->hw_prof.phy_desc[i].min_sata_lrate,
			    asd_ha->hw_prof.phy_desc[i].flags);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * asd_process_ctrl_a_user - process CTRL-A user settings
 * @asd_ha: poपूर्णांकer to the host adapter काष्ठाure
 * @flash_dir: poपूर्णांकer to the flash directory
 */
अटल पूर्णांक asd_process_ctrl_a_user(काष्ठा asd_ha_काष्ठा *asd_ha,
				   काष्ठा asd_flash_dir *flash_dir)
अणु
	पूर्णांक err, i;
	u32 offs, size;
	काष्ठा asd_ll_el *el = शून्य;
	काष्ठा asd_ctrla_phy_settings *ps;
	काष्ठा asd_ctrla_phy_settings dflt_ps;

	err = asd_find_flash_de(flash_dir, FLASH_DE_CTRL_A_USER, &offs, &size);
	अगर (err) अणु
		ASD_DPRINTK("couldn't find CTRL-A user settings section\n");
		ASD_DPRINTK("Creating default CTRL-A user settings section\n");

		dflt_ps.id0 = 'h';
		dflt_ps.num_phys = 8;
		क्रम (i =0; i < ASD_MAX_PHYS; i++) अणु
			स_नकल(dflt_ps.phy_ent[i].sas_addr,
			       asd_ha->hw_prof.sas_addr, SAS_ADDR_SIZE);
			dflt_ps.phy_ent[i].sas_link_rates = 0x98;
			dflt_ps.phy_ent[i].flags = 0x0;
			dflt_ps.phy_ent[i].sata_link_rates = 0x0;
		पूर्ण

		size = माप(काष्ठा asd_ctrla_phy_settings);
		ps = &dflt_ps;
		जाओ out_process;
	पूर्ण

	अगर (size == 0)
		जाओ out;

	err = -ENOMEM;
	el = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!el) अणु
		ASD_DPRINTK("no mem for ctrla user settings section\n");
		जाओ out;
	पूर्ण

	err = asd_पढ़ो_flash_seg(asd_ha, (व्योम *)el, offs, size);
	अगर (err) अणु
		ASD_DPRINTK("couldn't read ctrla phy settings section\n");
		जाओ out2;
	पूर्ण

	err = -ENOENT;
	ps = asd_find_ll_by_id(el, 'h', 0xFF);
	अगर (!ps) अणु
		ASD_DPRINTK("couldn't find ctrla phy settings struct\n");
		जाओ out2;
	पूर्ण
out_process:
	err = asd_process_ctrla_phy_settings(asd_ha, ps);
	अगर (err) अणु
		ASD_DPRINTK("couldn't process ctrla phy settings\n");
		जाओ out2;
	पूर्ण
out2:
	kमुक्त(el);
out:
	वापस err;
पूर्ण

/**
 * asd_पढ़ो_flash - पढ़ो flash memory
 * @asd_ha: poपूर्णांकer to the host adapter काष्ठाure
 */
पूर्णांक asd_पढ़ो_flash(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	पूर्णांक err;
	काष्ठा asd_flash_dir *flash_dir;

	err = asd_flash_getid(asd_ha);
	अगर (err)
		वापस err;

	flash_dir = kदो_स्मृति(माप(*flash_dir), GFP_KERNEL);
	अगर (!flash_dir)
		वापस -ENOMEM;

	err = -ENOENT;
	अगर (!asd_find_flash_dir(asd_ha, flash_dir)) अणु
		ASD_DPRINTK("couldn't find flash directory\n");
		जाओ out;
	पूर्ण

	अगर (le32_to_cpu(flash_dir->rev) != 2) अणु
		asd_prपूर्णांकk("unsupported flash dir version:0x%x\n",
			   le32_to_cpu(flash_dir->rev));
		जाओ out;
	पूर्ण

	err = asd_process_ms(asd_ha, flash_dir);
	अगर (err) अणु
		ASD_DPRINTK("couldn't process manuf sector settings\n");
		जाओ out;
	पूर्ण

	err = asd_process_ctrl_a_user(asd_ha, flash_dir);
	अगर (err) अणु
		ASD_DPRINTK("couldn't process CTRL-A user settings\n");
		जाओ out;
	पूर्ण

out:
	kमुक्त(flash_dir);
	वापस err;
पूर्ण

/**
 * asd_verअगरy_flash_seg - verअगरy data with flash memory
 * @asd_ha: poपूर्णांकer to the host adapter काष्ठाure
 * @src: poपूर्णांकer to the source data to be verअगरied
 * @dest_offset: offset from flash memory
 * @bytes_to_verअगरy: total bytes to verअगरy
 */
पूर्णांक asd_verअगरy_flash_seg(काष्ठा asd_ha_काष्ठा *asd_ha,
			 स्थिर व्योम *src, u32 dest_offset, u32 bytes_to_verअगरy)
अणु
	स्थिर u8 *src_buf;
	u8 flash_अक्षर;
	पूर्णांक err;
	u32 nv_offset, reg, i;

	reg = asd_ha->hw_prof.flash.bar;
	src_buf = शून्य;

	err = FLASH_OK;
	nv_offset = dest_offset;
	src_buf = (स्थिर u8 *)src;
	क्रम (i = 0; i < bytes_to_verअगरy; i++) अणु
		flash_अक्षर = asd_पढ़ो_reg_byte(asd_ha, reg + nv_offset + i);
		अगर (flash_अक्षर != src_buf[i]) अणु
			err = FAIL_VERIFY;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

/**
 * asd_ग_लिखो_flash_seg - ग_लिखो data पूर्णांकo flash memory
 * @asd_ha: poपूर्णांकer to the host adapter काष्ठाure
 * @src: poपूर्णांकer to the source data to be written
 * @dest_offset: offset from flash memory
 * @bytes_to_ग_लिखो: total bytes to ग_लिखो
 */
पूर्णांक asd_ग_लिखो_flash_seg(काष्ठा asd_ha_काष्ठा *asd_ha,
			स्थिर व्योम *src, u32 dest_offset, u32 bytes_to_ग_लिखो)
अणु
	स्थिर u8 *src_buf;
	u32 nv_offset, reg, i;
	पूर्णांक err;

	reg = asd_ha->hw_prof.flash.bar;
	src_buf = शून्य;

	err = asd_check_flash_type(asd_ha);
	अगर (err) अणु
		ASD_DPRINTK("couldn't find the type of flash. err=%d\n", err);
		वापस err;
	पूर्ण

	nv_offset = dest_offset;
	err = asd_erase_nv_sector(asd_ha, nv_offset, bytes_to_ग_लिखो);
	अगर (err) अणु
		ASD_DPRINTK("Erase failed at offset:0x%x\n",
			nv_offset);
		वापस err;
	पूर्ण

	err = asd_reset_flash(asd_ha);
	अगर (err) अणु
		ASD_DPRINTK("couldn't reset flash. err=%d\n", err);
		वापस err;
	पूर्ण

	src_buf = (स्थिर u8 *)src;
	क्रम (i = 0; i < bytes_to_ग_लिखो; i++) अणु
		/* Setup program command sequence */
		चयन (asd_ha->hw_prof.flash.method) अणु
		हाल FLASH_METHOD_A:
		अणु
			asd_ग_लिखो_reg_byte(asd_ha,
					(reg + 0xAAA), 0xAA);
			asd_ग_लिखो_reg_byte(asd_ha,
					(reg + 0x555), 0x55);
			asd_ग_लिखो_reg_byte(asd_ha,
					(reg + 0xAAA), 0xA0);
			asd_ग_लिखो_reg_byte(asd_ha,
					(reg + nv_offset + i),
					(*(src_buf + i)));
			अवरोध;
		पूर्ण
		हाल FLASH_METHOD_B:
		अणु
			asd_ग_लिखो_reg_byte(asd_ha,
					(reg + 0x555), 0xAA);
			asd_ग_लिखो_reg_byte(asd_ha,
					(reg + 0x2AA), 0x55);
			asd_ग_लिखो_reg_byte(asd_ha,
					(reg + 0x555), 0xA0);
			asd_ग_लिखो_reg_byte(asd_ha,
					(reg + nv_offset + i),
					(*(src_buf + i)));
			अवरोध;
		पूर्ण
		शेष:
			अवरोध;
		पूर्ण
		अगर (asd_chk_ग_लिखो_status(asd_ha,
				(nv_offset + i), 0) != 0) अणु
			ASD_DPRINTK("aicx: Write failed at offset:0x%x\n",
				reg + nv_offset + i);
			वापस FAIL_WRITE_FLASH;
		पूर्ण
	पूर्ण

	err = asd_reset_flash(asd_ha);
	अगर (err) अणु
		ASD_DPRINTK("couldn't reset flash. err=%d\n", err);
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक asd_chk_ग_लिखो_status(काष्ठा asd_ha_काष्ठा *asd_ha,
	 u32 sector_addr, u8 erase_flag)
अणु
	u32 reg;
	u32 loop_cnt;
	u8  nv_data1, nv_data2;
	u8  toggle_bit1;

	/*
	 * Read from DQ2 requires sector address
	 * जबतक it's करोnt care क्रम DQ6
	 */
	reg = asd_ha->hw_prof.flash.bar;

	क्रम (loop_cnt = 0; loop_cnt < 50000; loop_cnt++) अणु
		nv_data1 = asd_पढ़ो_reg_byte(asd_ha, reg);
		nv_data2 = asd_पढ़ो_reg_byte(asd_ha, reg);

		toggle_bit1 = ((nv_data1 & FLASH_STATUS_BIT_MASK_DQ6)
				 ^ (nv_data2 & FLASH_STATUS_BIT_MASK_DQ6));

		अगर (toggle_bit1 == 0) अणु
			वापस 0;
		पूर्ण अन्यथा अणु
			अगर (nv_data2 & FLASH_STATUS_BIT_MASK_DQ5) अणु
				nv_data1 = asd_पढ़ो_reg_byte(asd_ha,
								reg);
				nv_data2 = asd_पढ़ो_reg_byte(asd_ha,
								reg);
				toggle_bit1 =
				((nv_data1 & FLASH_STATUS_BIT_MASK_DQ6)
				^ (nv_data2 & FLASH_STATUS_BIT_MASK_DQ6));

				अगर (toggle_bit1 == 0)
					वापस 0;
			पूर्ण
		पूर्ण

		/*
		 * ERASE is a sector-by-sector operation and requires
		 * more समय to finish जबतक WRITE is byte-byte-byte
		 * operation and takes lesser समय to finish.
		 *
		 * For some strange reason a reduced ERASE delay gives dअगरferent
		 * behaviour across dअगरferent spirit boards. Hence we set
		 * a optimum balance of 50mus क्रम ERASE which works well
		 * across all boards.
		 */
		अगर (erase_flag) अणु
			udelay(FLASH_STATUS_ERASE_DELAY_COUNT);
		पूर्ण अन्यथा अणु
			udelay(FLASH_STATUS_WRITE_DELAY_COUNT);
		पूर्ण
	पूर्ण
	वापस -1;
पूर्ण

/**
 * asd_erase_nv_sector - Erase the flash memory sectors.
 * @asd_ha: poपूर्णांकer to the host adapter काष्ठाure
 * @flash_addr: poपूर्णांकer to offset from flash memory
 * @size: total bytes to erase.
 */
पूर्णांक asd_erase_nv_sector(काष्ठा asd_ha_काष्ठा *asd_ha, u32 flash_addr, u32 size)
अणु
	u32 reg;
	u32 sector_addr;

	reg = asd_ha->hw_prof.flash.bar;

	/* sector staring address */
	sector_addr = flash_addr & FLASH_SECTOR_SIZE_MASK;

	/*
	 * Erasing an flash sector needs to be करोne in six consecutive
	 * ग_लिखो cyles.
	 */
	जबतक (sector_addr < flash_addr+size) अणु
		चयन (asd_ha->hw_prof.flash.method) अणु
		हाल FLASH_METHOD_A:
			asd_ग_लिखो_reg_byte(asd_ha, (reg + 0xAAA), 0xAA);
			asd_ग_लिखो_reg_byte(asd_ha, (reg + 0x555), 0x55);
			asd_ग_लिखो_reg_byte(asd_ha, (reg + 0xAAA), 0x80);
			asd_ग_लिखो_reg_byte(asd_ha, (reg + 0xAAA), 0xAA);
			asd_ग_लिखो_reg_byte(asd_ha, (reg + 0x555), 0x55);
			asd_ग_लिखो_reg_byte(asd_ha, (reg + sector_addr), 0x30);
			अवरोध;
		हाल FLASH_METHOD_B:
			asd_ग_लिखो_reg_byte(asd_ha, (reg + 0x555), 0xAA);
			asd_ग_लिखो_reg_byte(asd_ha, (reg + 0x2AA), 0x55);
			asd_ग_लिखो_reg_byte(asd_ha, (reg + 0x555), 0x80);
			asd_ग_लिखो_reg_byte(asd_ha, (reg + 0x555), 0xAA);
			asd_ग_लिखो_reg_byte(asd_ha, (reg + 0x2AA), 0x55);
			asd_ग_लिखो_reg_byte(asd_ha, (reg + sector_addr), 0x30);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		अगर (asd_chk_ग_लिखो_status(asd_ha, sector_addr, 1) != 0)
			वापस FAIL_ERASE_FLASH;

		sector_addr += FLASH_SECTOR_SIZE;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक asd_check_flash_type(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	u8 manuf_id;
	u8 dev_id;
	u8 sec_prot;
	u32 inc;
	u32 reg;
	पूर्णांक err;

	/* get Flash memory base address */
	reg = asd_ha->hw_prof.flash.bar;

	/* Determine flash info */
	err = asd_reset_flash(asd_ha);
	अगर (err) अणु
		ASD_DPRINTK("couldn't reset flash. err=%d\n", err);
		वापस err;
	पूर्ण

	asd_ha->hw_prof.flash.method = FLASH_METHOD_UNKNOWN;
	asd_ha->hw_prof.flash.manuf = FLASH_MANUF_ID_UNKNOWN;
	asd_ha->hw_prof.flash.dev_id = FLASH_DEV_ID_UNKNOWN;

	/* Get flash info. This would most likely be AMD Am29LV family flash.
	 * First try the sequence क्रम word mode.  It is the same as क्रम
	 * 008B (byte mode only), 160B (word mode) and 800D (word mode).
	 */
	inc = asd_ha->hw_prof.flash.wide ? 2 : 1;
	asd_ग_लिखो_reg_byte(asd_ha, reg + 0xAAA, 0xAA);
	asd_ग_लिखो_reg_byte(asd_ha, reg + 0x555, 0x55);
	asd_ग_लिखो_reg_byte(asd_ha, reg + 0xAAA, 0x90);
	manuf_id = asd_पढ़ो_reg_byte(asd_ha, reg);
	dev_id = asd_पढ़ो_reg_byte(asd_ha, reg + inc);
	sec_prot = asd_पढ़ो_reg_byte(asd_ha, reg + inc + inc);
	/* Get out of स्वतःselect mode. */
	err = asd_reset_flash(asd_ha);
	अगर (err) अणु
		ASD_DPRINTK("couldn't reset flash. err=%d\n", err);
		वापस err;
	पूर्ण
	ASD_DPRINTK("Flash MethodA manuf_id(0x%x) dev_id(0x%x) "
		"sec_prot(0x%x)\n", manuf_id, dev_id, sec_prot);
	err = asd_reset_flash(asd_ha);
	अगर (err != 0)
		वापस err;

	चयन (manuf_id) अणु
	हाल FLASH_MANUF_ID_AMD:
		चयन (sec_prot) अणु
		हाल FLASH_DEV_ID_AM29LV800DT:
		हाल FLASH_DEV_ID_AM29LV640MT:
		हाल FLASH_DEV_ID_AM29F800B:
			asd_ha->hw_prof.flash.method = FLASH_METHOD_A;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल FLASH_MANUF_ID_ST:
		चयन (sec_prot) अणु
		हाल FLASH_DEV_ID_STM29W800DT:
		हाल FLASH_DEV_ID_STM29LV640:
			asd_ha->hw_prof.flash.method = FLASH_METHOD_A;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल FLASH_MANUF_ID_FUJITSU:
		चयन (sec_prot) अणु
		हाल FLASH_DEV_ID_MBM29LV800TE:
		हाल FLASH_DEV_ID_MBM29DL800TA:
			asd_ha->hw_prof.flash.method = FLASH_METHOD_A;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल FLASH_MANUF_ID_MACRONIX:
		चयन (sec_prot) अणु
		हाल FLASH_DEV_ID_MX29LV800BT:
			asd_ha->hw_prof.flash.method = FLASH_METHOD_A;
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण

	अगर (asd_ha->hw_prof.flash.method == FLASH_METHOD_UNKNOWN) अणु
		err = asd_reset_flash(asd_ha);
		अगर (err) अणु
			ASD_DPRINTK("couldn't reset flash. err=%d\n", err);
			वापस err;
		पूर्ण

		/* Issue Unlock sequence क्रम AM29LV008BT */
		asd_ग_लिखो_reg_byte(asd_ha, (reg + 0x555), 0xAA);
		asd_ग_लिखो_reg_byte(asd_ha, (reg + 0x2AA), 0x55);
		asd_ग_लिखो_reg_byte(asd_ha, (reg + 0x555), 0x90);
		manuf_id = asd_पढ़ो_reg_byte(asd_ha, reg);
		dev_id = asd_पढ़ो_reg_byte(asd_ha, reg + inc);
		sec_prot = asd_पढ़ो_reg_byte(asd_ha, reg + inc + inc);

		ASD_DPRINTK("Flash MethodB manuf_id(0x%x) dev_id(0x%x) sec_prot"
			"(0x%x)\n", manuf_id, dev_id, sec_prot);

		err = asd_reset_flash(asd_ha);
		अगर (err != 0) अणु
			ASD_DPRINTK("couldn't reset flash. err=%d\n", err);
			वापस err;
		पूर्ण

		चयन (manuf_id) अणु
		हाल FLASH_MANUF_ID_AMD:
			चयन (dev_id) अणु
			हाल FLASH_DEV_ID_AM29LV008BT:
				asd_ha->hw_prof.flash.method = FLASH_METHOD_B;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
			अवरोध;
		हाल FLASH_MANUF_ID_ST:
			चयन (dev_id) अणु
			हाल FLASH_DEV_ID_STM29008:
				asd_ha->hw_prof.flash.method = FLASH_METHOD_B;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
			अवरोध;
		हाल FLASH_MANUF_ID_FUJITSU:
			चयन (dev_id) अणु
			हाल FLASH_DEV_ID_MBM29LV008TA:
				asd_ha->hw_prof.flash.method = FLASH_METHOD_B;
				अवरोध;
			पूर्ण
			अवरोध;
		हाल FLASH_MANUF_ID_INTEL:
			चयन (dev_id) अणु
			हाल FLASH_DEV_ID_I28LV00TAT:
				asd_ha->hw_prof.flash.method = FLASH_METHOD_B;
				अवरोध;
			पूर्ण
			अवरोध;
		हाल FLASH_MANUF_ID_MACRONIX:
			चयन (dev_id) अणु
			हाल FLASH_DEV_ID_I28LV00TAT:
				asd_ha->hw_prof.flash.method = FLASH_METHOD_B;
				अवरोध;
			पूर्ण
			अवरोध;
		शेष:
			वापस FAIL_FIND_FLASH_ID;
		पूर्ण
	पूर्ण

	अगर (asd_ha->hw_prof.flash.method == FLASH_METHOD_UNKNOWN)
	      वापस FAIL_FIND_FLASH_ID;

	asd_ha->hw_prof.flash.manuf = manuf_id;
	asd_ha->hw_prof.flash.dev_id = dev_id;
	asd_ha->hw_prof.flash.sec_prot = sec_prot;
	वापस 0;
पूर्ण
