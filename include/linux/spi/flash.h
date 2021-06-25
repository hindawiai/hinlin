<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित LINUX_SPI_FLASH_H
#घोषणा LINUX_SPI_FLASH_H

काष्ठा mtd_partition;

/**
 * काष्ठा flash_platक्रमm_data: board-specअगरic flash data
 * @name: optional flash device name (eg, as used with mtdparts=)
 * @parts: optional array of mtd_partitions क्रम अटल partitioning
 * @nr_parts: number of mtd_partitions क्रम अटल partitioning
 * @type: optional flash device type (e.g. m25p80 vs m25p64), क्रम use
 *	with chips that can't be queried क्रम JEDEC or other IDs
 *
 * Board init code (in arch/.../mach-xxx/board-yyy.c files) can
 * provide inक्रमmation about SPI flash parts (such as DataFlash) to
 * help set up the device and its appropriate शेष partitioning.
 *
 * Note that क्रम DataFlash, sizes क्रम pages, blocks, and sectors are
 * rarely घातers of two; and partitions should be sector-aligned.
 */
काष्ठा flash_platक्रमm_data अणु
	अक्षर		*name;
	काष्ठा mtd_partition *parts;
	अचिन्हित पूर्णांक	nr_parts;

	अक्षर		*type;

	/* we'll likely add more ... use JEDEC IDs, etc */
पूर्ण;

#पूर्ण_अगर
