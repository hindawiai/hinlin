<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright तऊ 1999-2010 David Woodhouse <dwmw2@infradead.org> et al.
 */

#अगर_अघोषित __MTD_MTD_H__
#घोषणा __MTD_MTD_H__

#समावेश <linux/types.h>
#समावेश <linux/uपन.स>
#समावेश <linux/list.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/device.h>
#समावेश <linux/of.h>
#समावेश <linux/nvmem-provider.h>

#समावेश <mtd/mtd-abi.h>

#समावेश <यंत्र/भाग64.h>

#घोषणा MTD_FAIL_ADDR_UNKNOWN -1LL

काष्ठा mtd_info;

/*
 * If the erase fails, fail_addr might indicate exactly which block failed. If
 * fail_addr = MTD_FAIL_ADDR_UNKNOWN, the failure was not at the device level
 * or was not specअगरic to any particular block.
 */
काष्ठा erase_info अणु
	uपूर्णांक64_t addr;
	uपूर्णांक64_t len;
	uपूर्णांक64_t fail_addr;
पूर्ण;

काष्ठा mtd_erase_region_info अणु
	uपूर्णांक64_t offset;		/* At which this region starts, from the beginning of the MTD */
	uपूर्णांक32_t erasesize;		/* For this region */
	uपूर्णांक32_t numblocks;		/* Number of blocks of erasesize in this region */
	अचिन्हित दीर्घ *lockmap;		/* If keeping biपंचांगap of locks */
पूर्ण;

/**
 * काष्ठा mtd_oob_ops - oob operation opeअक्रमs
 * @mode:	operation mode
 *
 * @len:	number of data bytes to ग_लिखो/पढ़ो
 *
 * @retlen:	number of data bytes written/पढ़ो
 *
 * @ooblen:	number of oob bytes to ग_लिखो/पढ़ो
 * @oobretlen:	number of oob bytes written/पढ़ो
 * @ooboffs:	offset of oob data in the oob area (only relevant when
 *		mode = MTD_OPS_PLACE_OOB or MTD_OPS_RAW)
 * @datbuf:	data buffer - अगर शून्य only oob data are पढ़ो/written
 * @oobbuf:	oob data buffer
 *
 * Note, some MTD drivers करो not allow you to ग_लिखो more than one OOB area at
 * one go. If you try to करो that on such an MTD device, -EINVAL will be
 * वापसed. If you want to make your implementation portable on all kind of MTD
 * devices you should split the ग_लिखो request पूर्णांकo several sub-requests when the
 * request crosses a page boundary.
 */
काष्ठा mtd_oob_ops अणु
	अचिन्हित पूर्णांक	mode;
	माप_प्रकार		len;
	माप_प्रकार		retlen;
	माप_प्रकार		ooblen;
	माप_प्रकार		oobretlen;
	uपूर्णांक32_t	ooboffs;
	uपूर्णांक8_t		*datbuf;
	uपूर्णांक8_t		*oobbuf;
पूर्ण;

#घोषणा MTD_MAX_OOBFREE_ENTRIES_LARGE	32
#घोषणा MTD_MAX_ECCPOS_ENTRIES_LARGE	640
/**
 * काष्ठा mtd_oob_region - oob region definition
 * @offset: region offset
 * @length: region length
 *
 * This काष्ठाure describes a region of the OOB area, and is used
 * to retrieve ECC or मुक्त bytes sections.
 * Each section is defined by an offset within the OOB area and a
 * length.
 */
काष्ठा mtd_oob_region अणु
	u32 offset;
	u32 length;
पूर्ण;

/*
 * काष्ठा mtd_ooblayout_ops - न_अंकD OOB layout operations
 * @ecc: function वापसing an ECC region in the OOB area.
 *	 Should वापस -दुस्फल अगर %section exceeds the total number of
 *	 ECC sections.
 * @मुक्त: function वापसing a मुक्त region in the OOB area.
 *	  Should वापस -दुस्फल अगर %section exceeds the total number of
 *	  मुक्त sections.
 */
काष्ठा mtd_ooblayout_ops अणु
	पूर्णांक (*ecc)(काष्ठा mtd_info *mtd, पूर्णांक section,
		   काष्ठा mtd_oob_region *oobecc);
	पूर्णांक (*मुक्त)(काष्ठा mtd_info *mtd, पूर्णांक section,
		    काष्ठा mtd_oob_region *oobमुक्त);
पूर्ण;

/**
 * काष्ठा mtd_pairing_info - page pairing inक्रमmation
 *
 * @pair: pair id
 * @group: group id
 *
 * The term "pair" is used here, even though TLC न_अंकDs might group pages by 3
 * (3 bits in a single cell). A pair should regroup all pages that are sharing
 * the same cell. Pairs are then indexed in ascending order.
 *
 * @group is defining the position of a page in a given pair. It can also be
 * seen as the bit position in the cell: page attached to bit 0 beदीर्घs to
 * group 0, page attached to bit 1 beदीर्घs to group 1, etc.
 *
 * Example:
 * The H27UCG8T2BTR-BC datasheet describes the following pairing scheme:
 *
 *		group-0		group-1
 *
 *  pair-0	page-0		page-4
 *  pair-1	page-1		page-5
 *  pair-2	page-2		page-8
 *  ...
 *  pair-127	page-251	page-255
 *
 *
 * Note that the "group" and "pair" terms were extracted from Samsung and
 * Hynix datasheets, and might be referenced under other names in other
 * datasheets (Micron is describing this concept as "shared pages").
 */
काष्ठा mtd_pairing_info अणु
	पूर्णांक pair;
	पूर्णांक group;
पूर्ण;

/**
 * काष्ठा mtd_pairing_scheme - page pairing scheme description
 *
 * @ngroups: number of groups. Should be related to the number of bits
 *	     per cell.
 * @get_info: converts a ग_लिखो-unit (page number within an erase block) पूर्णांकo
 *	      mtd_pairing inक्रमmation (pair + group). This function should
 *	      fill the info parameter based on the wunit index or वापस
 *	      -EINVAL अगर the wunit parameter is invalid.
 * @get_wunit: converts pairing inक्रमmation पूर्णांकo a ग_लिखो-unit (page) number.
 *	       This function should वापस the wunit index poपूर्णांकed by the
 *	       pairing inक्रमmation described in the info argument. It should
 *	       वापस -EINVAL, अगर there's no wunit corresponding to the
 *	       passed pairing inक्रमmation.
 *
 * See mtd_pairing_info करोcumentation क्रम a detailed explanation of the
 * pair and group concepts.
 *
 * The mtd_pairing_scheme काष्ठाure provides a generic solution to represent
 * न_अंकD page pairing scheme. Instead of exposing two big tables to करो the
 * ग_लिखो-unit <-> (pair + group) conversions, we ask the MTD drivers to
 * implement the ->get_info() and ->get_wunit() functions.
 *
 * MTD users will then be able to query these inक्रमmation by using the
 * mtd_pairing_info_to_wunit() and mtd_wunit_to_pairing_info() helpers.
 *
 * @ngroups is here to help MTD users iterating over all the pages in a
 * given pair. This value can be retrieved by MTD users using the
 * mtd_pairing_groups() helper.
 *
 * Examples are given in the mtd_pairing_info_to_wunit() and
 * mtd_wunit_to_pairing_info() करोcumentation.
 */
काष्ठा mtd_pairing_scheme अणु
	पूर्णांक ngroups;
	पूर्णांक (*get_info)(काष्ठा mtd_info *mtd, पूर्णांक wunit,
			काष्ठा mtd_pairing_info *info);
	पूर्णांक (*get_wunit)(काष्ठा mtd_info *mtd,
			 स्थिर काष्ठा mtd_pairing_info *info);
पूर्ण;

काष्ठा module;	/* only needed क्रम owner field in mtd_info */

/**
 * काष्ठा mtd_debug_info - debugging inक्रमmation क्रम an MTD device.
 *
 * @dfs_dir: direntry object of the MTD device debugfs directory
 */
काष्ठा mtd_debug_info अणु
	काष्ठा dentry *dfs_dir;

	स्थिर अक्षर *partname;
	स्थिर अक्षर *partid;
पूर्ण;

/**
 * काष्ठा mtd_part - MTD partition specअगरic fields
 *
 * @node: list node used to add an MTD partition to the parent partition list
 * @offset: offset of the partition relatively to the parent offset
 * @size: partition size. Should be equal to mtd->size unless
 *	  MTD_SLC_ON_MLC_EMULATION is set
 * @flags: original flags (beक्रमe the mtdpart logic decided to tweak them based
 *	   on flash स्थिरraपूर्णांकs, like eraseblock/pagesize alignment)
 *
 * This काष्ठा is embedded in mtd_info and contains partition-specअगरic
 * properties/fields.
 */
काष्ठा mtd_part अणु
	काष्ठा list_head node;
	u64 offset;
	u64 size;
	u32 flags;
पूर्ण;

/**
 * काष्ठा mtd_master - MTD master specअगरic fields
 *
 * @partitions_lock: lock protecting accesses to the partition list. Protects
 *		     not only the master partition list, but also all
 *		     sub-partitions.
 * @suspended: et to 1 when the device is suspended, 0 otherwise
 *
 * This काष्ठा is embedded in mtd_info and contains master-specअगरic
 * properties/fields. The master is the root MTD device from the MTD partition
 * poपूर्णांक of view.
 */
काष्ठा mtd_master अणु
	काष्ठा mutex partitions_lock;
	काष्ठा mutex chrdev_lock;
	अचिन्हित पूर्णांक suspended : 1;
पूर्ण;

काष्ठा mtd_info अणु
	u_अक्षर type;
	uपूर्णांक32_t flags;
	uपूर्णांक64_t size;	 // Total size of the MTD

	/* "Major" erase size क्रम the device. Naथ/ve users may take this
	 * to be the only erase size available, or may use the more detailed
	 * inक्रमmation below अगर they desire
	 */
	uपूर्णांक32_t erasesize;
	/* Minimal writable flash unit size. In हाल of NOR flash it is 1 (even
	 * though inभागidual bits can be cleared), in हाल of न_अंकD flash it is
	 * one न_अंकD page (or half, or one-fourths of it), in हाल of ECC-ed NOR
	 * it is of ECC block size, etc. It is illegal to have ग_लिखोsize = 0.
	 * Any driver रेजिस्टरing a काष्ठा mtd_info must ensure a ग_लिखोsize of
	 * 1 or larger.
	 */
	uपूर्णांक32_t ग_लिखोsize;

	/*
	 * Size of the ग_लिखो buffer used by the MTD. MTD devices having a ग_लिखो
	 * buffer can ग_लिखो multiple ग_लिखोsize chunks at a समय. E.g. जबतक
	 * writing 4 * ग_लिखोsize bytes to a device with 2 * ग_लिखोsize bytes
	 * buffer the MTD driver can (but करोesn't have to) करो 2 ग_लिखोsize
	 * operations, but not 4. Currently, all न_अंकDs have ग_लिखोbufsize
	 * equivalent to ग_लिखोsize (न_अंकD page size). Some NOR flashes करो have
	 * ग_लिखोbufsize greater than ग_लिखोsize.
	 */
	uपूर्णांक32_t ग_लिखोbufsize;

	uपूर्णांक32_t oobsize;   // Amount of OOB data per block (e.g. 16)
	uपूर्णांक32_t oobavail;  // Available OOB bytes per block

	/*
	 * If erasesize is a घातer of 2 then the shअगरt is stored in
	 * erasesize_shअगरt otherwise erasesize_shअगरt is zero. Ditto ग_लिखोsize.
	 */
	अचिन्हित पूर्णांक erasesize_shअगरt;
	अचिन्हित पूर्णांक ग_लिखोsize_shअगरt;
	/* Masks based on erasesize_shअगरt and ग_लिखोsize_shअगरt */
	अचिन्हित पूर्णांक erasesize_mask;
	अचिन्हित पूर्णांक ग_लिखोsize_mask;

	/*
	 * पढ़ो ops वापस -EUCLEAN अगर max number of bitflips corrected on any
	 * one region comprising an ecc step equals or exceeds this value.
	 * Settable by driver, अन्यथा शेषs to ecc_strength.  User can override
	 * in sysfs.  N.B. The meaning of the -EUCLEAN वापस code has changed;
	 * see Documentation/ABI/testing/sysfs-class-mtd क्रम more detail.
	 */
	अचिन्हित पूर्णांक bitflip_threshold;

	/* Kernel-only stuff starts here. */
	स्थिर अक्षर *name;
	पूर्णांक index;

	/* OOB layout description */
	स्थिर काष्ठा mtd_ooblayout_ops *ooblayout;

	/* न_अंकD pairing scheme, only provided क्रम MLC/TLC न_अंकDs */
	स्थिर काष्ठा mtd_pairing_scheme *pairing;

	/* the ecc step size. */
	अचिन्हित पूर्णांक ecc_step_size;

	/* max number of correctible bit errors per ecc step */
	अचिन्हित पूर्णांक ecc_strength;

	/* Data क्रम variable erase regions. If numeraseregions is zero,
	 * it means that the whole device has erasesize as given above.
	 */
	पूर्णांक numeraseregions;
	काष्ठा mtd_erase_region_info *eraseregions;

	/*
	 * Do not call via these poपूर्णांकers, use corresponding mtd_*()
	 * wrappers instead.
	 */
	पूर्णांक (*_erase) (काष्ठा mtd_info *mtd, काष्ठा erase_info *instr);
	पूर्णांक (*_poपूर्णांक) (काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len,
		       माप_प्रकार *retlen, व्योम **virt, resource_माप_प्रकार *phys);
	पूर्णांक (*_unpoपूर्णांक) (काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len);
	पूर्णांक (*_पढ़ो) (काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len,
		      माप_प्रकार *retlen, u_अक्षर *buf);
	पूर्णांक (*_ग_लिखो) (काष्ठा mtd_info *mtd, loff_t to, माप_प्रकार len,
		       माप_प्रकार *retlen, स्थिर u_अक्षर *buf);
	पूर्णांक (*_panic_ग_लिखो) (काष्ठा mtd_info *mtd, loff_t to, माप_प्रकार len,
			     माप_प्रकार *retlen, स्थिर u_अक्षर *buf);
	पूर्णांक (*_पढ़ो_oob) (काष्ठा mtd_info *mtd, loff_t from,
			  काष्ठा mtd_oob_ops *ops);
	पूर्णांक (*_ग_लिखो_oob) (काष्ठा mtd_info *mtd, loff_t to,
			   काष्ठा mtd_oob_ops *ops);
	पूर्णांक (*_get_fact_prot_info) (काष्ठा mtd_info *mtd, माप_प्रकार len,
				    माप_प्रकार *retlen, काष्ठा otp_info *buf);
	पूर्णांक (*_पढ़ो_fact_prot_reg) (काष्ठा mtd_info *mtd, loff_t from,
				    माप_प्रकार len, माप_प्रकार *retlen, u_अक्षर *buf);
	पूर्णांक (*_get_user_prot_info) (काष्ठा mtd_info *mtd, माप_प्रकार len,
				    माप_प्रकार *retlen, काष्ठा otp_info *buf);
	पूर्णांक (*_पढ़ो_user_prot_reg) (काष्ठा mtd_info *mtd, loff_t from,
				    माप_प्रकार len, माप_प्रकार *retlen, u_अक्षर *buf);
	पूर्णांक (*_ग_लिखो_user_prot_reg) (काष्ठा mtd_info *mtd, loff_t to,
				     माप_प्रकार len, माप_प्रकार *retlen,
				     स्थिर u_अक्षर *buf);
	पूर्णांक (*_lock_user_prot_reg) (काष्ठा mtd_info *mtd, loff_t from,
				    माप_प्रकार len);
	पूर्णांक (*_erase_user_prot_reg) (काष्ठा mtd_info *mtd, loff_t from,
				     माप_प्रकार len);
	पूर्णांक (*_ग_लिखोv) (काष्ठा mtd_info *mtd, स्थिर काष्ठा kvec *vecs,
			अचिन्हित दीर्घ count, loff_t to, माप_प्रकार *retlen);
	व्योम (*_sync) (काष्ठा mtd_info *mtd);
	पूर्णांक (*_lock) (काष्ठा mtd_info *mtd, loff_t ofs, uपूर्णांक64_t len);
	पूर्णांक (*_unlock) (काष्ठा mtd_info *mtd, loff_t ofs, uपूर्णांक64_t len);
	पूर्णांक (*_is_locked) (काष्ठा mtd_info *mtd, loff_t ofs, uपूर्णांक64_t len);
	पूर्णांक (*_block_isreserved) (काष्ठा mtd_info *mtd, loff_t ofs);
	पूर्णांक (*_block_isbad) (काष्ठा mtd_info *mtd, loff_t ofs);
	पूर्णांक (*_block_markbad) (काष्ठा mtd_info *mtd, loff_t ofs);
	पूर्णांक (*_max_bad_blocks) (काष्ठा mtd_info *mtd, loff_t ofs, माप_प्रकार len);
	पूर्णांक (*_suspend) (काष्ठा mtd_info *mtd);
	व्योम (*_resume) (काष्ठा mtd_info *mtd);
	व्योम (*_reboot) (काष्ठा mtd_info *mtd);
	/*
	 * If the driver is something smart, like UBI, it may need to मुख्यtain
	 * its own reference counting. The below functions are only क्रम driver.
	 */
	पूर्णांक (*_get_device) (काष्ठा mtd_info *mtd);
	व्योम (*_put_device) (काष्ठा mtd_info *mtd);

	/*
	 * flag indicates a panic ग_लिखो, low level drivers can take appropriate
	 * action अगर required to ensure ग_लिखोs go through
	 */
	bool oops_panic_ग_लिखो;

	काष्ठा notअगरier_block reboot_notअगरier;  /* शेष mode beक्रमe reboot */

	/* ECC status inक्रमmation */
	काष्ठा mtd_ecc_stats ecc_stats;
	/* Subpage shअगरt (न_अंकD) */
	पूर्णांक subpage_sft;

	व्योम *priv;

	काष्ठा module *owner;
	काष्ठा device dev;
	पूर्णांक usecount;
	काष्ठा mtd_debug_info dbg;
	काष्ठा nvmem_device *nvmem;

	/*
	 * Parent device from the MTD partition poपूर्णांक of view.
	 *
	 * MTD masters करो not have any parent, MTD partitions करो. The parent
	 * MTD device can itself be a partition.
	 */
	काष्ठा mtd_info *parent;

	/* List of partitions attached to this MTD device */
	काष्ठा list_head partitions;

	जोड़ अणु
		काष्ठा mtd_part part;
		काष्ठा mtd_master master;
	पूर्ण;
पूर्ण;

अटल अंतरभूत काष्ठा mtd_info *mtd_get_master(काष्ठा mtd_info *mtd)
अणु
	जबतक (mtd->parent)
		mtd = mtd->parent;

	वापस mtd;
पूर्ण

अटल अंतरभूत u64 mtd_get_master_ofs(काष्ठा mtd_info *mtd, u64 ofs)
अणु
	जबतक (mtd->parent) अणु
		ofs += mtd->part.offset;
		mtd = mtd->parent;
	पूर्ण

	वापस ofs;
पूर्ण

अटल अंतरभूत bool mtd_is_partition(स्थिर काष्ठा mtd_info *mtd)
अणु
	वापस mtd->parent;
पूर्ण

अटल अंतरभूत bool mtd_has_partitions(स्थिर काष्ठा mtd_info *mtd)
अणु
	वापस !list_empty(&mtd->partitions);
पूर्ण

पूर्णांक mtd_ooblayout_ecc(काष्ठा mtd_info *mtd, पूर्णांक section,
		      काष्ठा mtd_oob_region *oobecc);
पूर्णांक mtd_ooblayout_find_eccregion(काष्ठा mtd_info *mtd, पूर्णांक eccbyte,
				 पूर्णांक *section,
				 काष्ठा mtd_oob_region *oobregion);
पूर्णांक mtd_ooblayout_get_eccbytes(काष्ठा mtd_info *mtd, u8 *eccbuf,
			       स्थिर u8 *oobbuf, पूर्णांक start, पूर्णांक nbytes);
पूर्णांक mtd_ooblayout_set_eccbytes(काष्ठा mtd_info *mtd, स्थिर u8 *eccbuf,
			       u8 *oobbuf, पूर्णांक start, पूर्णांक nbytes);
पूर्णांक mtd_ooblayout_मुक्त(काष्ठा mtd_info *mtd, पूर्णांक section,
		       काष्ठा mtd_oob_region *oobमुक्त);
पूर्णांक mtd_ooblayout_get_databytes(काष्ठा mtd_info *mtd, u8 *databuf,
				स्थिर u8 *oobbuf, पूर्णांक start, पूर्णांक nbytes);
पूर्णांक mtd_ooblayout_set_databytes(काष्ठा mtd_info *mtd, स्थिर u8 *databuf,
				u8 *oobbuf, पूर्णांक start, पूर्णांक nbytes);
पूर्णांक mtd_ooblayout_count_मुक्तbytes(काष्ठा mtd_info *mtd);
पूर्णांक mtd_ooblayout_count_eccbytes(काष्ठा mtd_info *mtd);

अटल अंतरभूत व्योम mtd_set_ooblayout(काष्ठा mtd_info *mtd,
				     स्थिर काष्ठा mtd_ooblayout_ops *ooblayout)
अणु
	mtd->ooblayout = ooblayout;
पूर्ण

अटल अंतरभूत व्योम mtd_set_pairing_scheme(काष्ठा mtd_info *mtd,
				स्थिर काष्ठा mtd_pairing_scheme *pairing)
अणु
	mtd->pairing = pairing;
पूर्ण

अटल अंतरभूत व्योम mtd_set_of_node(काष्ठा mtd_info *mtd,
				   काष्ठा device_node *np)
अणु
	mtd->dev.of_node = np;
	अगर (!mtd->name)
		of_property_पढ़ो_string(np, "label", &mtd->name);
पूर्ण

अटल अंतरभूत काष्ठा device_node *mtd_get_of_node(काष्ठा mtd_info *mtd)
अणु
	वापस dev_of_node(&mtd->dev);
पूर्ण

अटल अंतरभूत u32 mtd_oobavail(काष्ठा mtd_info *mtd, काष्ठा mtd_oob_ops *ops)
अणु
	वापस ops->mode == MTD_OPS_AUTO_OOB ? mtd->oobavail : mtd->oobsize;
पूर्ण

अटल अंतरभूत पूर्णांक mtd_max_bad_blocks(काष्ठा mtd_info *mtd,
				     loff_t ofs, माप_प्रकार len)
अणु
	काष्ठा mtd_info *master = mtd_get_master(mtd);

	अगर (!master->_max_bad_blocks)
		वापस -ENOTSUPP;

	अगर (mtd->size < (len + ofs) || ofs < 0)
		वापस -EINVAL;

	वापस master->_max_bad_blocks(master, mtd_get_master_ofs(mtd, ofs),
				       len);
पूर्ण

पूर्णांक mtd_wunit_to_pairing_info(काष्ठा mtd_info *mtd, पूर्णांक wunit,
			      काष्ठा mtd_pairing_info *info);
पूर्णांक mtd_pairing_info_to_wunit(काष्ठा mtd_info *mtd,
			      स्थिर काष्ठा mtd_pairing_info *info);
पूर्णांक mtd_pairing_groups(काष्ठा mtd_info *mtd);
पूर्णांक mtd_erase(काष्ठा mtd_info *mtd, काष्ठा erase_info *instr);
पूर्णांक mtd_poपूर्णांक(काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len, माप_प्रकार *retlen,
	      व्योम **virt, resource_माप_प्रकार *phys);
पूर्णांक mtd_unpoपूर्णांक(काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len);
अचिन्हित दीर्घ mtd_get_unmapped_area(काष्ठा mtd_info *mtd, अचिन्हित दीर्घ len,
				    अचिन्हित दीर्घ offset, अचिन्हित दीर्घ flags);
पूर्णांक mtd_पढ़ो(काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len, माप_प्रकार *retlen,
	     u_अक्षर *buf);
पूर्णांक mtd_ग_लिखो(काष्ठा mtd_info *mtd, loff_t to, माप_प्रकार len, माप_प्रकार *retlen,
	      स्थिर u_अक्षर *buf);
पूर्णांक mtd_panic_ग_लिखो(काष्ठा mtd_info *mtd, loff_t to, माप_प्रकार len, माप_प्रकार *retlen,
		    स्थिर u_अक्षर *buf);

पूर्णांक mtd_पढ़ो_oob(काष्ठा mtd_info *mtd, loff_t from, काष्ठा mtd_oob_ops *ops);
पूर्णांक mtd_ग_लिखो_oob(काष्ठा mtd_info *mtd, loff_t to, काष्ठा mtd_oob_ops *ops);

पूर्णांक mtd_get_fact_prot_info(काष्ठा mtd_info *mtd, माप_प्रकार len, माप_प्रकार *retlen,
			   काष्ठा otp_info *buf);
पूर्णांक mtd_पढ़ो_fact_prot_reg(काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len,
			   माप_प्रकार *retlen, u_अक्षर *buf);
पूर्णांक mtd_get_user_prot_info(काष्ठा mtd_info *mtd, माप_प्रकार len, माप_प्रकार *retlen,
			   काष्ठा otp_info *buf);
पूर्णांक mtd_पढ़ो_user_prot_reg(काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len,
			   माप_प्रकार *retlen, u_अक्षर *buf);
पूर्णांक mtd_ग_लिखो_user_prot_reg(काष्ठा mtd_info *mtd, loff_t to, माप_प्रकार len,
			    माप_प्रकार *retlen, स्थिर u_अक्षर *buf);
पूर्णांक mtd_lock_user_prot_reg(काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len);
पूर्णांक mtd_erase_user_prot_reg(काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len);

पूर्णांक mtd_ग_लिखोv(काष्ठा mtd_info *mtd, स्थिर काष्ठा kvec *vecs,
	       अचिन्हित दीर्घ count, loff_t to, माप_प्रकार *retlen);

अटल अंतरभूत व्योम mtd_sync(काष्ठा mtd_info *mtd)
अणु
	काष्ठा mtd_info *master = mtd_get_master(mtd);

	अगर (master->_sync)
		master->_sync(master);
पूर्ण

पूर्णांक mtd_lock(काष्ठा mtd_info *mtd, loff_t ofs, uपूर्णांक64_t len);
पूर्णांक mtd_unlock(काष्ठा mtd_info *mtd, loff_t ofs, uपूर्णांक64_t len);
पूर्णांक mtd_is_locked(काष्ठा mtd_info *mtd, loff_t ofs, uपूर्णांक64_t len);
पूर्णांक mtd_block_isreserved(काष्ठा mtd_info *mtd, loff_t ofs);
पूर्णांक mtd_block_isbad(काष्ठा mtd_info *mtd, loff_t ofs);
पूर्णांक mtd_block_markbad(काष्ठा mtd_info *mtd, loff_t ofs);

अटल अंतरभूत पूर्णांक mtd_suspend(काष्ठा mtd_info *mtd)
अणु
	काष्ठा mtd_info *master = mtd_get_master(mtd);
	पूर्णांक ret;

	अगर (master->master.suspended)
		वापस 0;

	ret = master->_suspend ? master->_suspend(master) : 0;
	अगर (ret)
		वापस ret;

	master->master.suspended = 1;
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम mtd_resume(काष्ठा mtd_info *mtd)
अणु
	काष्ठा mtd_info *master = mtd_get_master(mtd);

	अगर (!master->master.suspended)
		वापस;

	अगर (master->_resume)
		master->_resume(master);

	master->master.suspended = 0;
पूर्ण

अटल अंतरभूत uपूर्णांक32_t mtd_भाग_by_eb(uपूर्णांक64_t sz, काष्ठा mtd_info *mtd)
अणु
	अगर (mtd->erasesize_shअगरt)
		वापस sz >> mtd->erasesize_shअगरt;
	करो_भाग(sz, mtd->erasesize);
	वापस sz;
पूर्ण

अटल अंतरभूत uपूर्णांक32_t mtd_mod_by_eb(uपूर्णांक64_t sz, काष्ठा mtd_info *mtd)
अणु
	अगर (mtd->erasesize_shअगरt)
		वापस sz & mtd->erasesize_mask;
	वापस करो_भाग(sz, mtd->erasesize);
पूर्ण

/**
 * mtd_align_erase_req - Adjust an erase request to align things on eraseblock
 *			 boundaries.
 * @mtd: the MTD device this erase request applies on
 * @req: the erase request to adjust
 *
 * This function will adjust @req->addr and @req->len to align them on
 * @mtd->erasesize. Of course we expect @mtd->erasesize to be != 0.
 */
अटल अंतरभूत व्योम mtd_align_erase_req(काष्ठा mtd_info *mtd,
				       काष्ठा erase_info *req)
अणु
	u32 mod;

	अगर (WARN_ON(!mtd->erasesize))
		वापस;

	mod = mtd_mod_by_eb(req->addr, mtd);
	अगर (mod) अणु
		req->addr -= mod;
		req->len += mod;
	पूर्ण

	mod = mtd_mod_by_eb(req->addr + req->len, mtd);
	अगर (mod)
		req->len += mtd->erasesize - mod;
पूर्ण

अटल अंतरभूत uपूर्णांक32_t mtd_भाग_by_ws(uपूर्णांक64_t sz, काष्ठा mtd_info *mtd)
अणु
	अगर (mtd->ग_लिखोsize_shअगरt)
		वापस sz >> mtd->ग_लिखोsize_shअगरt;
	करो_भाग(sz, mtd->ग_लिखोsize);
	वापस sz;
पूर्ण

अटल अंतरभूत uपूर्णांक32_t mtd_mod_by_ws(uपूर्णांक64_t sz, काष्ठा mtd_info *mtd)
अणु
	अगर (mtd->ग_लिखोsize_shअगरt)
		वापस sz & mtd->ग_लिखोsize_mask;
	वापस करो_भाग(sz, mtd->ग_लिखोsize);
पूर्ण

अटल अंतरभूत पूर्णांक mtd_wunit_per_eb(काष्ठा mtd_info *mtd)
अणु
	काष्ठा mtd_info *master = mtd_get_master(mtd);

	वापस master->erasesize / mtd->ग_लिखोsize;
पूर्ण

अटल अंतरभूत पूर्णांक mtd_offset_to_wunit(काष्ठा mtd_info *mtd, loff_t offs)
अणु
	वापस mtd_भाग_by_ws(mtd_mod_by_eb(offs, mtd), mtd);
पूर्ण

अटल अंतरभूत loff_t mtd_wunit_to_offset(काष्ठा mtd_info *mtd, loff_t base,
					 पूर्णांक wunit)
अणु
	वापस base + (wunit * mtd->ग_लिखोsize);
पूर्ण


अटल अंतरभूत पूर्णांक mtd_has_oob(स्थिर काष्ठा mtd_info *mtd)
अणु
	काष्ठा mtd_info *master = mtd_get_master((काष्ठा mtd_info *)mtd);

	वापस master->_पढ़ो_oob && master->_ग_लिखो_oob;
पूर्ण

अटल अंतरभूत पूर्णांक mtd_type_is_nand(स्थिर काष्ठा mtd_info *mtd)
अणु
	वापस mtd->type == MTD_न_अंकDFLASH || mtd->type == MTD_MLCन_अंकDFLASH;
पूर्ण

अटल अंतरभूत पूर्णांक mtd_can_have_bb(स्थिर काष्ठा mtd_info *mtd)
अणु
	काष्ठा mtd_info *master = mtd_get_master((काष्ठा mtd_info *)mtd);

	वापस !!master->_block_isbad;
पूर्ण

	/* Kernel-side ioctl definitions */

काष्ठा mtd_partition;
काष्ठा mtd_part_parser_data;

बाह्य पूर्णांक mtd_device_parse_रेजिस्टर(काष्ठा mtd_info *mtd,
				     स्थिर अक्षर * स्थिर *part_probe_types,
				     काष्ठा mtd_part_parser_data *parser_data,
				     स्थिर काष्ठा mtd_partition *defparts,
				     पूर्णांक defnr_parts);
#घोषणा mtd_device_रेजिस्टर(master, parts, nr_parts)	\
	mtd_device_parse_रेजिस्टर(master, शून्य, शून्य, parts, nr_parts)
बाह्य पूर्णांक mtd_device_unरेजिस्टर(काष्ठा mtd_info *master);
बाह्य काष्ठा mtd_info *get_mtd_device(काष्ठा mtd_info *mtd, पूर्णांक num);
बाह्य पूर्णांक __get_mtd_device(काष्ठा mtd_info *mtd);
बाह्य व्योम __put_mtd_device(काष्ठा mtd_info *mtd);
बाह्य काष्ठा mtd_info *get_mtd_device_nm(स्थिर अक्षर *name);
बाह्य व्योम put_mtd_device(काष्ठा mtd_info *mtd);


काष्ठा mtd_notअगरier अणु
	व्योम (*add)(काष्ठा mtd_info *mtd);
	व्योम (*हटाओ)(काष्ठा mtd_info *mtd);
	काष्ठा list_head list;
पूर्ण;


बाह्य व्योम रेजिस्टर_mtd_user (काष्ठा mtd_notअगरier *new);
बाह्य पूर्णांक unरेजिस्टर_mtd_user (काष्ठा mtd_notअगरier *old);
व्योम *mtd_kदो_स्मृति_up_to(स्थिर काष्ठा mtd_info *mtd, माप_प्रकार *size);

अटल अंतरभूत पूर्णांक mtd_is_bitflip(पूर्णांक err) अणु
	वापस err == -EUCLEAN;
पूर्ण

अटल अंतरभूत पूर्णांक mtd_is_eccerr(पूर्णांक err) अणु
	वापस err == -EBADMSG;
पूर्ण

अटल अंतरभूत पूर्णांक mtd_is_bitflip_or_eccerr(पूर्णांक err) अणु
	वापस mtd_is_bitflip(err) || mtd_is_eccerr(err);
पूर्ण

अचिन्हित mtd_mmap_capabilities(काष्ठा mtd_info *mtd);

#पूर्ण_अगर /* __MTD_MTD_H__ */
