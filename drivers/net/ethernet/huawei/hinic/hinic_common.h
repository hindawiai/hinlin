<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Huawei HiNIC PCI Express Linux driver
 * Copyright(c) 2017 Huawei Technologies Co., Ltd
 */

#अगर_अघोषित HINIC_COMMON_H
#घोषणा HINIC_COMMON_H

#समावेश <linux/types.h>

#घोषणा UPPER_8_BITS(data)      (((data) >> 8) & 0xFF)
#घोषणा LOWER_8_BITS(data)      ((data) & 0xFF)

काष्ठा hinic_sge अणु
	u32             hi_addr;
	u32             lo_addr;
	u32             len;
पूर्ण;

व्योम hinic_cpu_to_be32(व्योम *data, पूर्णांक len);

व्योम hinic_be32_to_cpu(व्योम *data, पूर्णांक len);

व्योम hinic_set_sge(काष्ठा hinic_sge *sge, dma_addr_t addr, पूर्णांक len);

dma_addr_t hinic_sge_to_dma(काष्ठा hinic_sge *sge);

#पूर्ण_अगर
