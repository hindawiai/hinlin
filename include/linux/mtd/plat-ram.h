<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* linux/include/linux/mtd/plat-ram.h
 *
 * (c) 2004 Simtec Electronics
 *	http://www.simtec.co.uk/products/SWLINUX/
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * Generic platक्रमm device based RAM map
 */

#अगर_अघोषित __LINUX_MTD_PLATRAM_H
#घोषणा __LINUX_MTD_PLATRAM_H __खाता__

#घोषणा PLATRAM_RO (0)
#घोषणा PLATRAM_RW (1)

काष्ठा platdata_mtd_ram अणु
	स्थिर अक्षर		*mapname;
	स्थिर अक्षर * स्थिर      *map_probes;
	स्थिर अक्षर * स्थिर      *probes;
	काष्ठा mtd_partition	*partitions;
	पूर्णांक			 nr_partitions;
	पूर्णांक			 bankwidth;

	/* control callbacks */

	व्योम	(*set_rw)(काष्ठा device *dev, पूर्णांक to);
पूर्ण;

#पूर्ण_अगर /* __LINUX_MTD_PLATRAM_H */
