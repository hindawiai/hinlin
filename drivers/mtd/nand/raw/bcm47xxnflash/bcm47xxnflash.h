<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __BCM47XXNFLASH_H
#घोषणा __BCM47XXNFLASH_H

#अगर_अघोषित pr_fmt
#घोषणा pr_fmt(fmt)		KBUILD_MODNAME ": " fmt
#पूर्ण_अगर

#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/rawnand.h>

काष्ठा bcm47xxnflash अणु
	काष्ठा bcma_drv_cc *cc;

	काष्ठा nand_chip nand_chip;

	अचिन्हित curr_command;
	पूर्णांक curr_page_addr;
	पूर्णांक curr_column;

	u8 id_data[8];
पूर्ण;

पूर्णांक bcm47xxnflash_ops_bcm4706_init(काष्ठा bcm47xxnflash *b47n);

#पूर्ण_अगर /* BCM47XXNFLASH */
