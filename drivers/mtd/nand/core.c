<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2017 Free Electrons
 *
 * Authors:
 *	Boris Brezillon <boris.brezillon@मुक्त-electrons.com>
 *	Peter Pan <peterpanकरोng@micron.com>
 */

#घोषणा pr_fmt(fmt)	"nand: " fmt

#समावेश <linux/module.h>
#समावेश <linux/mtd/nand.h>

/**
 * nanddev_isbad() - Check अगर a block is bad
 * @nand: न_अंकD device
 * @pos: position poपूर्णांकing to the block we want to check
 *
 * Return: true अगर the block is bad, false otherwise.
 */
bool nanddev_isbad(काष्ठा nand_device *nand, स्थिर काष्ठा nand_pos *pos)
अणु
	अगर (nanddev_bbt_is_initialized(nand)) अणु
		अचिन्हित पूर्णांक entry;
		पूर्णांक status;

		entry = nanddev_bbt_pos_to_entry(nand, pos);
		status = nanddev_bbt_get_block_status(nand, entry);
		/* Lazy block status retrieval */
		अगर (status == न_अंकD_BBT_BLOCK_STATUS_UNKNOWN) अणु
			अगर (nand->ops->isbad(nand, pos))
				status = न_अंकD_BBT_BLOCK_FACTORY_BAD;
			अन्यथा
				status = न_अंकD_BBT_BLOCK_GOOD;

			nanddev_bbt_set_block_status(nand, entry, status);
		पूर्ण

		अगर (status == न_अंकD_BBT_BLOCK_WORN ||
		    status == न_अंकD_BBT_BLOCK_FACTORY_BAD)
			वापस true;

		वापस false;
	पूर्ण

	वापस nand->ops->isbad(nand, pos);
पूर्ण
EXPORT_SYMBOL_GPL(nanddev_isbad);

/**
 * nanddev_markbad() - Mark a block as bad
 * @nand: न_अंकD device
 * @pos: position of the block to mark bad
 *
 * Mark a block bad. This function is updating the BBT अगर available and
 * calls the low-level markbad hook (nand->ops->markbad()).
 *
 * Return: 0 in हाल of success, a negative error code otherwise.
 */
पूर्णांक nanddev_markbad(काष्ठा nand_device *nand, स्थिर काष्ठा nand_pos *pos)
अणु
	काष्ठा mtd_info *mtd = nanddev_to_mtd(nand);
	अचिन्हित पूर्णांक entry;
	पूर्णांक ret = 0;

	अगर (nanddev_isbad(nand, pos))
		वापस 0;

	ret = nand->ops->markbad(nand, pos);
	अगर (ret)
		pr_warn("failed to write BBM to block @%llx (err = %d)\n",
			nanddev_pos_to_offs(nand, pos), ret);

	अगर (!nanddev_bbt_is_initialized(nand))
		जाओ out;

	entry = nanddev_bbt_pos_to_entry(nand, pos);
	ret = nanddev_bbt_set_block_status(nand, entry, न_अंकD_BBT_BLOCK_WORN);
	अगर (ret)
		जाओ out;

	ret = nanddev_bbt_update(nand);

out:
	अगर (!ret)
		mtd->ecc_stats.badblocks++;

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(nanddev_markbad);

/**
 * nanddev_isreserved() - Check whether an eraseblock is reserved or not
 * @nand: न_अंकD device
 * @pos: न_अंकD position to test
 *
 * Checks whether the eraseblock poपूर्णांकed by @pos is reserved or not.
 *
 * Return: true अगर the eraseblock is reserved, false otherwise.
 */
bool nanddev_isreserved(काष्ठा nand_device *nand, स्थिर काष्ठा nand_pos *pos)
अणु
	अचिन्हित पूर्णांक entry;
	पूर्णांक status;

	अगर (!nanddev_bbt_is_initialized(nand))
		वापस false;

	/* Return info from the table */
	entry = nanddev_bbt_pos_to_entry(nand, pos);
	status = nanddev_bbt_get_block_status(nand, entry);
	वापस status == न_अंकD_BBT_BLOCK_RESERVED;
पूर्ण
EXPORT_SYMBOL_GPL(nanddev_isreserved);

/**
 * nanddev_erase() - Erase a न_अंकD portion
 * @nand: न_अंकD device
 * @pos: position of the block to erase
 *
 * Erases the block अगर it's not bad.
 *
 * Return: 0 in हाल of success, a negative error code otherwise.
 */
पूर्णांक nanddev_erase(काष्ठा nand_device *nand, स्थिर काष्ठा nand_pos *pos)
अणु
	अगर (nanddev_isbad(nand, pos) || nanddev_isreserved(nand, pos)) अणु
		pr_warn("attempt to erase a bad/reserved block @%llx\n",
			nanddev_pos_to_offs(nand, pos));
		वापस -EIO;
	पूर्ण

	वापस nand->ops->erase(nand, pos);
पूर्ण
EXPORT_SYMBOL_GPL(nanddev_erase);

/**
 * nanddev_mtd_erase() - Generic mtd->_erase() implementation क्रम न_अंकD devices
 * @mtd: MTD device
 * @einfo: erase request
 *
 * This is a simple mtd->_erase() implementation iterating over all blocks
 * concerned by @einfo and calling nand->ops->erase() on each of them.
 *
 * Note that mtd->_erase should not be directly asचिन्हित to this helper,
 * because there's no locking here. न_अंकD specialized layers should instead
 * implement there own wrapper around nanddev_mtd_erase() taking the
 * appropriate lock beक्रमe calling nanddev_mtd_erase().
 *
 * Return: 0 in हाल of success, a negative error code otherwise.
 */
पूर्णांक nanddev_mtd_erase(काष्ठा mtd_info *mtd, काष्ठा erase_info *einfo)
अणु
	काष्ठा nand_device *nand = mtd_to_nanddev(mtd);
	काष्ठा nand_pos pos, last;
	पूर्णांक ret;

	nanddev_offs_to_pos(nand, einfo->addr, &pos);
	nanddev_offs_to_pos(nand, einfo->addr + einfo->len - 1, &last);
	जबतक (nanddev_pos_cmp(&pos, &last) <= 0) अणु
		ret = nanddev_erase(nand, &pos);
		अगर (ret) अणु
			einfo->fail_addr = nanddev_pos_to_offs(nand, &pos);

			वापस ret;
		पूर्ण

		nanddev_pos_next_eraseblock(nand, &pos);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nanddev_mtd_erase);

/**
 * nanddev_mtd_max_bad_blocks() - Get the maximum number of bad eraseblock on
 *				  a specअगरic region of the न_अंकD device
 * @mtd: MTD device
 * @offs: offset of the न_अंकD region
 * @len: length of the न_अंकD region
 *
 * Default implementation क्रम mtd->_max_bad_blocks(). Only works अगर
 * nand->memorg.max_bad_eraseblocks_per_lun is > 0.
 *
 * Return: a positive number encoding the maximum number of eraseblocks on a
 * portion of memory, a negative error code otherwise.
 */
पूर्णांक nanddev_mtd_max_bad_blocks(काष्ठा mtd_info *mtd, loff_t offs, माप_प्रकार len)
अणु
	काष्ठा nand_device *nand = mtd_to_nanddev(mtd);
	काष्ठा nand_pos pos, end;
	अचिन्हित पूर्णांक max_bb = 0;

	अगर (!nand->memorg.max_bad_eraseblocks_per_lun)
		वापस -ENOTSUPP;

	nanddev_offs_to_pos(nand, offs, &pos);
	nanddev_offs_to_pos(nand, offs + len, &end);

	क्रम (nanddev_offs_to_pos(nand, offs, &pos);
	     nanddev_pos_cmp(&pos, &end) < 0;
	     nanddev_pos_next_lun(nand, &pos))
		max_bb += nand->memorg.max_bad_eraseblocks_per_lun;

	वापस max_bb;
पूर्ण
EXPORT_SYMBOL_GPL(nanddev_mtd_max_bad_blocks);

/**
 * nanddev_get_ecc_engine() - Find and get a suitable ECC engine
 * @nand: न_अंकD device
 */
अटल पूर्णांक nanddev_get_ecc_engine(काष्ठा nand_device *nand)
अणु
	पूर्णांक engine_type;

	/* Read the user desires in terms of ECC engine/configuration */
	of_get_nand_ecc_user_config(nand);

	engine_type = nand->ecc.user_conf.engine_type;
	अगर (engine_type == न_अंकD_ECC_ENGINE_TYPE_INVALID)
		engine_type = nand->ecc.शेषs.engine_type;

	चयन (engine_type) अणु
	हाल न_अंकD_ECC_ENGINE_TYPE_NONE:
		वापस 0;
	हाल न_अंकD_ECC_ENGINE_TYPE_SOFT:
		nand->ecc.engine = nand_ecc_get_sw_engine(nand);
		अवरोध;
	हाल न_अंकD_ECC_ENGINE_TYPE_ON_DIE:
		nand->ecc.engine = nand_ecc_get_on_die_hw_engine(nand);
		अवरोध;
	हाल न_अंकD_ECC_ENGINE_TYPE_ON_HOST:
		pr_err("On-host hardware ECC engines not supported yet\n");
		अवरोध;
	शेष:
		pr_err("Missing ECC engine type\n");
	पूर्ण

	अगर (!nand->ecc.engine)
		वापस  -EINVAL;

	वापस 0;
पूर्ण

/**
 * nanddev_put_ecc_engine() - Dettach and put the in-use ECC engine
 * @nand: न_अंकD device
 */
अटल पूर्णांक nanddev_put_ecc_engine(काष्ठा nand_device *nand)
अणु
	चयन (nand->ecc.ctx.conf.engine_type) अणु
	हाल न_अंकD_ECC_ENGINE_TYPE_ON_HOST:
		pr_err("On-host hardware ECC engines not supported yet\n");
		अवरोध;
	हाल न_अंकD_ECC_ENGINE_TYPE_NONE:
	हाल न_अंकD_ECC_ENGINE_TYPE_SOFT:
	हाल न_अंकD_ECC_ENGINE_TYPE_ON_DIE:
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * nanddev_find_ecc_configuration() - Find a suitable ECC configuration
 * @nand: न_अंकD device
 */
अटल पूर्णांक nanddev_find_ecc_configuration(काष्ठा nand_device *nand)
अणु
	पूर्णांक ret;

	अगर (!nand->ecc.engine)
		वापस -ENOTSUPP;

	ret = nand_ecc_init_ctx(nand);
	अगर (ret)
		वापस ret;

	अगर (!nand_ecc_is_strong_enough(nand))
		pr_warn("WARNING: %s: the ECC used on your system is too weak compared to the one required by the NAND chip\n",
			nand->mtd.name);

	वापस 0;
पूर्ण

/**
 * nanddev_ecc_engine_init() - Initialize an ECC engine क्रम the chip
 * @nand: न_अंकD device
 */
पूर्णांक nanddev_ecc_engine_init(काष्ठा nand_device *nand)
अणु
	पूर्णांक ret;

	/* Look क्रम the ECC engine to use */
	ret = nanddev_get_ecc_engine(nand);
	अगर (ret) अणु
		pr_err("No ECC engine found\n");
		वापस ret;
	पूर्ण

	/* No ECC engine requested */
	अगर (!nand->ecc.engine)
		वापस 0;

	/* Configure the engine: balance user input and chip requirements */
	ret = nanddev_find_ecc_configuration(nand);
	अगर (ret) अणु
		pr_err("No suitable ECC configuration\n");
		nanddev_put_ecc_engine(nand);

		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nanddev_ecc_engine_init);

/**
 * nanddev_ecc_engine_cleanup() - Cleanup ECC engine initializations
 * @nand: न_अंकD device
 */
व्योम nanddev_ecc_engine_cleanup(काष्ठा nand_device *nand)
अणु
	अगर (nand->ecc.engine)
		nand_ecc_cleanup_ctx(nand);

	nanddev_put_ecc_engine(nand);
पूर्ण
EXPORT_SYMBOL_GPL(nanddev_ecc_engine_cleanup);

/**
 * nanddev_init() - Initialize a न_अंकD device
 * @nand: न_अंकD device
 * @ops: न_अंकD device operations
 * @owner: न_अंकD device owner
 *
 * Initializes a न_अंकD device object. Consistency checks are करोne on @ops and
 * @nand->memorg. Also takes care of initializing the BBT.
 *
 * Return: 0 in हाल of success, a negative error code otherwise.
 */
पूर्णांक nanddev_init(काष्ठा nand_device *nand, स्थिर काष्ठा nand_ops *ops,
		 काष्ठा module *owner)
अणु
	काष्ठा mtd_info *mtd = nanddev_to_mtd(nand);
	काष्ठा nand_memory_organization *memorg = nanddev_get_memorg(nand);

	अगर (!nand || !ops)
		वापस -EINVAL;

	अगर (!ops->erase || !ops->markbad || !ops->isbad)
		वापस -EINVAL;

	अगर (!memorg->bits_per_cell || !memorg->pagesize ||
	    !memorg->pages_per_eraseblock || !memorg->eraseblocks_per_lun ||
	    !memorg->planes_per_lun || !memorg->luns_per_target ||
	    !memorg->ntarमाला_लो)
		वापस -EINVAL;

	nand->rowconv.eraseblock_addr_shअगरt =
					fls(memorg->pages_per_eraseblock - 1);
	nand->rowconv.lun_addr_shअगरt = fls(memorg->eraseblocks_per_lun - 1) +
				       nand->rowconv.eraseblock_addr_shअगरt;

	nand->ops = ops;

	mtd->type = memorg->bits_per_cell == 1 ?
		    MTD_न_अंकDFLASH : MTD_MLCन_अंकDFLASH;
	mtd->flags = MTD_CAP_न_अंकDFLASH;
	mtd->erasesize = memorg->pagesize * memorg->pages_per_eraseblock;
	mtd->ग_लिखोsize = memorg->pagesize;
	mtd->ग_लिखोbufsize = memorg->pagesize;
	mtd->oobsize = memorg->oobsize;
	mtd->size = nanddev_size(nand);
	mtd->owner = owner;

	वापस nanddev_bbt_init(nand);
पूर्ण
EXPORT_SYMBOL_GPL(nanddev_init);

/**
 * nanddev_cleanup() - Release resources allocated in nanddev_init()
 * @nand: न_अंकD device
 *
 * Basically unकरोes what has been करोne in nanddev_init().
 */
व्योम nanddev_cleanup(काष्ठा nand_device *nand)
अणु
	अगर (nanddev_bbt_is_initialized(nand))
		nanddev_bbt_cleanup(nand);
पूर्ण
EXPORT_SYMBOL_GPL(nanddev_cleanup);

MODULE_DESCRIPTION("Generic NAND framework");
MODULE_AUTHOR("Boris Brezillon <boris.brezillon@free-electrons.com>");
MODULE_LICENSE("GPL v2");
