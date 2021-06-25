<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2017 Free Electrons
 *
 * Authors:
 *	Boris Brezillon <boris.brezillon@मुक्त-electrons.com>
 *	Peter Pan <peterpanकरोng@micron.com>
 */

#घोषणा pr_fmt(fmt)	"nand-bbt: " fmt

#समावेश <linux/mtd/nand.h>
#समावेश <linux/slab.h>

/**
 * nanddev_bbt_init() - Initialize the BBT (Bad Block Table)
 * @nand: न_अंकD device
 *
 * Initialize the in-memory BBT.
 *
 * Return: 0 in हाल of success, a negative error code otherwise.
 */
पूर्णांक nanddev_bbt_init(काष्ठा nand_device *nand)
अणु
	अचिन्हित पूर्णांक bits_per_block = fls(न_अंकD_BBT_BLOCK_NUM_STATUS);
	अचिन्हित पूर्णांक nblocks = nanddev_neraseblocks(nand);
	अचिन्हित पूर्णांक nwords = DIV_ROUND_UP(nblocks * bits_per_block,
					   BITS_PER_LONG);

	nand->bbt.cache = kसुस्मृति(nwords, माप(*nand->bbt.cache),
				  GFP_KERNEL);
	अगर (!nand->bbt.cache)
		वापस -ENOMEM;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nanddev_bbt_init);

/**
 * nanddev_bbt_cleanup() - Cleanup the BBT (Bad Block Table)
 * @nand: न_अंकD device
 *
 * Unकरोes what has been करोne in nanddev_bbt_init()
 */
व्योम nanddev_bbt_cleanup(काष्ठा nand_device *nand)
अणु
	kमुक्त(nand->bbt.cache);
पूर्ण
EXPORT_SYMBOL_GPL(nanddev_bbt_cleanup);

/**
 * nanddev_bbt_update() - Update a BBT
 * @nand: nand device
 *
 * Update the BBT. Currently a NOP function since on-flash bbt is not yet
 * supported.
 *
 * Return: 0 in हाल of success, a negative error code otherwise.
 */
पूर्णांक nanddev_bbt_update(काष्ठा nand_device *nand)
अणु
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nanddev_bbt_update);

/**
 * nanddev_bbt_get_block_status() - Return the status of an eraseblock
 * @nand: nand device
 * @entry: the BBT entry
 *
 * Return: a positive number nand_bbt_block_status status or -%दुस्फल अगर @entry
 *	   is bigger than the BBT size.
 */
पूर्णांक nanddev_bbt_get_block_status(स्थिर काष्ठा nand_device *nand,
				 अचिन्हित पूर्णांक entry)
अणु
	अचिन्हित पूर्णांक bits_per_block = fls(न_अंकD_BBT_BLOCK_NUM_STATUS);
	अचिन्हित दीर्घ *pos = nand->bbt.cache +
			     ((entry * bits_per_block) / BITS_PER_LONG);
	अचिन्हित पूर्णांक offs = (entry * bits_per_block) % BITS_PER_LONG;
	अचिन्हित दीर्घ status;

	अगर (entry >= nanddev_neraseblocks(nand))
		वापस -दुस्फल;

	status = pos[0] >> offs;
	अगर (bits_per_block + offs > BITS_PER_LONG)
		status |= pos[1] << (BITS_PER_LONG - offs);

	वापस status & GENMASK(bits_per_block - 1, 0);
पूर्ण
EXPORT_SYMBOL_GPL(nanddev_bbt_get_block_status);

/**
 * nanddev_bbt_set_block_status() - Update the status of an eraseblock in the
 *				    in-memory BBT
 * @nand: nand device
 * @entry: the BBT entry to update
 * @status: the new status
 *
 * Update an entry of the in-memory BBT. If you want to push the updated BBT
 * the न_अंकD you should call nanddev_bbt_update().
 *
 * Return: 0 in हाल of success or -%दुस्फल अगर @entry is bigger than the BBT
 *	   size.
 */
पूर्णांक nanddev_bbt_set_block_status(काष्ठा nand_device *nand, अचिन्हित पूर्णांक entry,
				 क्रमागत nand_bbt_block_status status)
अणु
	अचिन्हित पूर्णांक bits_per_block = fls(न_अंकD_BBT_BLOCK_NUM_STATUS);
	अचिन्हित दीर्घ *pos = nand->bbt.cache +
			     ((entry * bits_per_block) / BITS_PER_LONG);
	अचिन्हित पूर्णांक offs = (entry * bits_per_block) % BITS_PER_LONG;
	अचिन्हित दीर्घ val = status & GENMASK(bits_per_block - 1, 0);

	अगर (entry >= nanddev_neraseblocks(nand))
		वापस -दुस्फल;

	pos[0] &= ~GENMASK(offs + bits_per_block - 1, offs);
	pos[0] |= val << offs;

	अगर (bits_per_block + offs > BITS_PER_LONG) अणु
		अचिन्हित पूर्णांक rbits = bits_per_block + offs - BITS_PER_LONG;

		pos[1] &= ~GENMASK(rbits - 1, 0);
		pos[1] |= val >> rbits;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nanddev_bbt_set_block_status);
