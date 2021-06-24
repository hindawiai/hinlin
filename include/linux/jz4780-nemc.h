<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * JZ4780 न_अंकD/बाह्यal memory controller (NEMC)
 *
 * Copyright (c) 2015 Imagination Technologies
 * Author: Alex Smith <alex@alex-smith.me.uk>
 */

#अगर_अघोषित __LINUX_JZ4780_NEMC_H__
#घोषणा __LINUX_JZ4780_NEMC_H__

#समावेश <linux/types.h>

काष्ठा device;

/*
 * Number of NEMC banks. Note that there are actually 6, but they are numbered
 * from 1.
 */
#घोषणा JZ4780_NEMC_NUM_BANKS	7

/**
 * क्रमागत jz4780_nemc_bank_type - device types which can be connected to a bank
 * @JZ4780_NEMC_BANK_SRAM: SRAM
 * @JZ4780_NEMC_BANK_न_अंकD: न_अंकD
 */
क्रमागत jz4780_nemc_bank_type अणु
	JZ4780_NEMC_BANK_SRAM,
	JZ4780_NEMC_BANK_न_अंकD,
पूर्ण;

बाह्य अचिन्हित पूर्णांक jz4780_nemc_num_banks(काष्ठा device *dev);

बाह्य व्योम jz4780_nemc_set_type(काष्ठा device *dev, अचिन्हित पूर्णांक bank,
				 क्रमागत jz4780_nemc_bank_type type);
बाह्य व्योम jz4780_nemc_निश्चित(काष्ठा device *dev, अचिन्हित पूर्णांक bank,
			       bool निश्चित);

#पूर्ण_अगर /* __LINUX_JZ4780_NEMC_H__ */
