<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * SharpSL न_अंकD support
 *
 * Copyright (C) 2008 Dmitry Baryshkov
 */

#अगर_अघोषित _MTD_SHARPSL_H
#घोषणा _MTD_SHARPSL_H

#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/mtd/partitions.h>

काष्ठा sharpsl_nand_platक्रमm_data अणु
	काष्ठा nand_bbt_descr	*badblock_pattern;
	स्थिर काष्ठा mtd_ooblayout_ops *ecc_layout;
	काष्ठा mtd_partition	*partitions;
	अचिन्हित पूर्णांक		nr_partitions;
	स्थिर अक्षर *स्थिर	*part_parsers;
पूर्ण;

#पूर्ण_अगर /* _MTD_SHARPSL_H */
