<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  Copyright तऊ 2000-2010 David Woodhouse <dwmw2@infradead.org>
 *			  Steven J. Hill <sjhill@realitydiluted.com>
 *			  Thomas Gleixner <tglx@linutronix.de>
 *
 * Contains all platक्रमm न_अंकD related definitions.
 */

#अगर_अघोषित __LINUX_MTD_PLATन_अंकD_H
#घोषणा __LINUX_MTD_PLATन_अंकD_H

#समावेश <linux/mtd/partitions.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/platक्रमm_device.h>

/**
 * काष्ठा platक्रमm_nand_chip - chip level device काष्ठाure
 * @nr_chips: max. number of chips to scan क्रम
 * @chip_offset: chip number offset
 * @nr_partitions: number of partitions poपूर्णांकed to by partitions (or zero)
 * @partitions: mtd partition list
 * @chip_delay: R/B delay value in us
 * @options: Option flags, e.g. 16bit buswidth
 * @bbt_options: BBT option flags, e.g. न_अंकD_BBT_USE_FLASH
 * @part_probe_types: शून्य-terminated array of probe types
 */
काष्ठा platक्रमm_nand_chip अणु
	पूर्णांक nr_chips;
	पूर्णांक chip_offset;
	पूर्णांक nr_partitions;
	काष्ठा mtd_partition *partitions;
	पूर्णांक chip_delay;
	अचिन्हित पूर्णांक options;
	अचिन्हित पूर्णांक bbt_options;
	स्थिर अक्षर **part_probe_types;
पूर्ण;

/**
 * काष्ठा platक्रमm_nand_ctrl - controller level device काष्ठाure
 * @probe: platक्रमm specअगरic function to probe/setup hardware
 * @हटाओ: platक्रमm specअगरic function to हटाओ/tearकरोwn hardware
 * @dev_पढ़ोy: platक्रमm specअगरic function to पढ़ो पढ़ोy/busy pin
 * @select_chip: platक्रमm specअगरic chip select function
 * @cmd_ctrl: platक्रमm specअगरic function क्रम controlling
 *	      ALE/CLE/nCE. Also used to ग_लिखो command and address
 * @ग_लिखो_buf: platक्रमm specअगरic function क्रम ग_लिखो buffer
 * @पढ़ो_buf: platक्रमm specअगरic function क्रम पढ़ो buffer
 * @priv: निजी data to transport driver specअगरic settings
 *
 * All fields are optional and depend on the hardware driver requirements
 */
काष्ठा platक्रमm_nand_ctrl अणु
	पूर्णांक (*probe)(काष्ठा platक्रमm_device *pdev);
	व्योम (*हटाओ)(काष्ठा platक्रमm_device *pdev);
	पूर्णांक (*dev_पढ़ोy)(काष्ठा nand_chip *chip);
	व्योम (*select_chip)(काष्ठा nand_chip *chip, पूर्णांक cs);
	व्योम (*cmd_ctrl)(काष्ठा nand_chip *chip, पूर्णांक dat, अचिन्हित पूर्णांक ctrl);
	व्योम (*ग_लिखो_buf)(काष्ठा nand_chip *chip, स्थिर uपूर्णांक8_t *buf, पूर्णांक len);
	व्योम (*पढ़ो_buf)(काष्ठा nand_chip *chip, uपूर्णांक8_t *buf, पूर्णांक len);
	व्योम *priv;
पूर्ण;

/**
 * काष्ठा platक्रमm_nand_data - container काष्ठाure क्रम platक्रमm-specअगरic data
 * @chip: chip level chip काष्ठाure
 * @ctrl: controller level device काष्ठाure
 */
काष्ठा platक्रमm_nand_data अणु
	काष्ठा platक्रमm_nand_chip chip;
	काष्ठा platक्रमm_nand_ctrl ctrl;
पूर्ण;

#पूर्ण_अगर /* __LINUX_MTD_PLATन_अंकD_H */
