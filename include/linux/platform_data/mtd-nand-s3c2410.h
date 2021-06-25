<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2004 Simtec Electronics
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * S3C2410 - न_अंकD device controller platक्रमm_device info
*/

#अगर_अघोषित __MTD_न_अंकD_S3C2410_H
#घोषणा __MTD_न_अंकD_S3C2410_H

#समावेश <linux/mtd/rawnand.h>

/**
 * काष्ठा s3c2410_nand_set - define a set of one or more nand chips
 * @flash_bbt: 		Openmoko u-boot can create a Bad Block Table
 *			Setting this flag will allow the kernel to
 *			look क्रम it at boot समय and also skip the न_अंकD
 *			scan.
 * @options:		Default value to set पूर्णांकo 'struct nand_chip' options.
 * @nr_chips:		Number of chips in this set
 * @nr_partitions:	Number of partitions poपूर्णांकed to by @partitions
 * @name:		Name of set (optional)
 * @nr_map:		Map क्रम low-layer logical to physical chip numbers (option)
 * @partitions:		The mtd partition list
 *
 * define a set of one or more nand chips रेजिस्टरed with an unique mtd. Also
 * allows to pass flag to the underlying न_अंकD layer. 'disable_ecc' will trigger
 * a warning at boot समय.
 */
काष्ठा s3c2410_nand_set अणु
	अचिन्हित पूर्णांक		flash_bbt:1;

	अचिन्हित पूर्णांक		options;
	पूर्णांक			nr_chips;
	पूर्णांक			nr_partitions;
	अक्षर			*name;
	पूर्णांक			*nr_map;
	काष्ठा mtd_partition	*partitions;
	काष्ठा device_node	*of_node;
पूर्ण;

काष्ठा s3c2410_platक्रमm_nand अणु
	/* timing inक्रमmation क्रम controller, all बार in nanoseconds */

	पूर्णांक	tacls;	/* समय क्रम active CLE/ALE to nWE/nOE */
	पूर्णांक	twrph0;	/* active समय क्रम nWE/nOE */
	पूर्णांक	twrph1;	/* समय क्रम release CLE/ALE from nWE/nOE inactive */

	अचिन्हित पूर्णांक	ignore_unset_ecc:1;

	क्रमागत nand_ecc_engine_type engine_type;

	पूर्णांक			nr_sets;
	काष्ठा s3c2410_nand_set *sets;

	व्योम			(*select_chip)(काष्ठा s3c2410_nand_set *,
					       पूर्णांक chip);
पूर्ण;

/**
 * s3c_nand_set_platdata() - रेजिस्टर न_अंकD platक्रमm data.
 * @nand: The न_अंकD platक्रमm data to रेजिस्टर with s3c_device_nand.
 *
 * This function copies the given न_अंकD platक्रमm data, @nand and रेजिस्टरs
 * it with the s3c_device_nand. This allows @nand to be __initdata.
*/
बाह्य व्योम s3c_nand_set_platdata(काष्ठा s3c2410_platक्रमm_nand *nand);

#पूर्ण_अगर /*__MTD_न_अंकD_S3C2410_H */
