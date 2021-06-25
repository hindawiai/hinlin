<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2014 Texas Instruments, Inc.
 *	Santosh Shilimkar <santosh.shilimkar@ti.com>
 */
#अगर_अघोषित __MEMORY_H
#घोषणा __MEMORY_H

#घोषणा KEYSTONE_LOW_PHYS_START		0x80000000ULL
#घोषणा KEYSTONE_LOW_PHYS_SIZE		0x80000000ULL /* 2G */
#घोषणा KEYSTONE_LOW_PHYS_END		(KEYSTONE_LOW_PHYS_START + \
					 KEYSTONE_LOW_PHYS_SIZE - 1)

#घोषणा KEYSTONE_HIGH_PHYS_START	0x800000000ULL
#घोषणा KEYSTONE_HIGH_PHYS_SIZE		0x400000000ULL	/* 16G */
#घोषणा KEYSTONE_HIGH_PHYS_END		(KEYSTONE_HIGH_PHYS_START + \
					 KEYSTONE_HIGH_PHYS_SIZE - 1)
#पूर्ण_अगर /* __MEMORY_H */
