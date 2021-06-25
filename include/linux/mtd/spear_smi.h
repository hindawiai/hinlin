<शैली गुरु>
/*
 * Copyright तऊ 2010 ST Microelectronics
 * Shiraz Hashim <shiraz.linux.kernel@gmail.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#अगर_अघोषित __MTD_SPEAR_SMI_H
#घोषणा __MTD_SPEAR_SMI_H

#समावेश <linux/types.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>

/* max possible slots क्रम serial-nor flash chip in the SMI controller */
#घोषणा MAX_NUM_FLASH_CHIP	4

/* macro to define partitions क्रम flash devices */
#घोषणा DEFINE_PARTS(n, of, s)		\
अणु					\
	.name = n,			\
	.offset = of,			\
	.size = s,			\
पूर्ण

/**
 * काष्ठा spear_smi_flash_info - platक्रमm काष्ठाure क्रम passing flash
 * inक्रमmation
 *
 * name: name of the serial nor flash क्रम identअगरication
 * mem_base: the memory base on which the flash is mapped
 * size: size of the flash in bytes
 * partitions: parition details
 * nr_partitions: number of partitions
 * fast_mode: whether flash supports fast mode
 */

काष्ठा spear_smi_flash_info अणु
	अक्षर *name;
	अचिन्हित दीर्घ mem_base;
	अचिन्हित दीर्घ size;
	काष्ठा mtd_partition *partitions;
	पूर्णांक nr_partitions;
	u8 fast_mode;
पूर्ण;

/**
 * काष्ठा spear_smi_plat_data - platक्रमm काष्ठाure क्रम configuring smi
 *
 * clk_rate: clk rate at which SMI must operate
 * num_flashes: number of flashes present on board
 * board_flash_info: specअगरic details of each flash present on board
 */
काष्ठा spear_smi_plat_data अणु
	अचिन्हित दीर्घ clk_rate;
	पूर्णांक num_flashes;
	काष्ठा spear_smi_flash_info *board_flash_info;
	काष्ठा device_node *np[MAX_NUM_FLASH_CHIP];
पूर्ण;

#पूर्ण_अगर /* __MTD_SPEAR_SMI_H */
