<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  arch/arm/include/यंत्र/mach/flash.h
 *
 *  Copyright (C) 2003 Russell King, All Rights Reserved.
 */
#अगर_अघोषित ASMARM_MACH_FLASH_H
#घोषणा ASMARM_MACH_FLASH_H

काष्ठा mtd_partition;
काष्ठा mtd_info;

/*
 * map_name:	the map probe function name
 * name:	flash device name (eg, as used with mtdparts=)
 * width:	width of mapped device
 * init:	method called at driver/device initialisation
 * निकास:	method called at driver/device removal
 * set_vpp:	method called to enable or disable VPP
 * mmcontrol:	method called to enable or disable Sync. Burst Read in Oneन_अंकD
 * parts:	optional array of mtd_partitions क्रम अटल partitioning
 * nr_parts:	number of mtd_partitions क्रम अटल partitioning
 */
काष्ठा flash_platक्रमm_data अणु
	स्थिर अक्षर	*map_name;
	स्थिर अक्षर	*name;
	अचिन्हित पूर्णांक	width;
	पूर्णांक		(*init)(व्योम);
	व्योम		(*निकास)(व्योम);
	व्योम		(*set_vpp)(पूर्णांक on);
	व्योम		(*mmcontrol)(काष्ठा mtd_info *mtd, पूर्णांक sync_पढ़ो);
	काष्ठा mtd_partition *parts;
	अचिन्हित पूर्णांक	nr_parts;
पूर्ण;

#पूर्ण_अगर
