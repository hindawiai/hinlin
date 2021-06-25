<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright (C) 2016 Freescale Semiconductor, Inc.
 * Copyright 2017-2020 NXP
 *
 * Header file containing the खुला API क्रम the System Controller (SC)
 * Resource Management (RM) function. This includes functions क्रम
 * partitioning resources, pads, and memory regions.
 *
 * RM_SVC (SVC) Resource Management Service
 *
 * Module क्रम the Resource Management (RM) service.
 */

#अगर_अघोषित _SC_RM_API_H
#घोषणा _SC_RM_API_H

#समावेश <linux/firmware/imx/sci.h>

/*
 * This type is used to indicate RPC RM function calls.
 */
क्रमागत imx_sc_rm_func अणु
	IMX_SC_RM_FUNC_UNKNOWN = 0,
	IMX_SC_RM_FUNC_PARTITION_ALLOC = 1,
	IMX_SC_RM_FUNC_SET_CONFIDENTIAL = 31,
	IMX_SC_RM_FUNC_PARTITION_FREE = 2,
	IMX_SC_RM_FUNC_GET_DID = 26,
	IMX_SC_RM_FUNC_PARTITION_STATIC = 3,
	IMX_SC_RM_FUNC_PARTITION_LOCK = 4,
	IMX_SC_RM_FUNC_GET_PARTITION = 5,
	IMX_SC_RM_FUNC_SET_PARENT = 6,
	IMX_SC_RM_FUNC_MOVE_ALL = 7,
	IMX_SC_RM_FUNC_ASSIGN_RESOURCE = 8,
	IMX_SC_RM_FUNC_SET_RESOURCE_MOVABLE = 9,
	IMX_SC_RM_FUNC_SET_SUBSYS_RSRC_MOVABLE = 28,
	IMX_SC_RM_FUNC_SET_MASTER_ATTRIBUTES = 10,
	IMX_SC_RM_FUNC_SET_MASTER_SID = 11,
	IMX_SC_RM_FUNC_SET_PERIPHERAL_PERMISSIONS = 12,
	IMX_SC_RM_FUNC_IS_RESOURCE_OWNED = 13,
	IMX_SC_RM_FUNC_GET_RESOURCE_OWNER = 33,
	IMX_SC_RM_FUNC_IS_RESOURCE_MASTER = 14,
	IMX_SC_RM_FUNC_IS_RESOURCE_PERIPHERAL = 15,
	IMX_SC_RM_FUNC_GET_RESOURCE_INFO = 16,
	IMX_SC_RM_FUNC_MEMREG_ALLOC = 17,
	IMX_SC_RM_FUNC_MEMREG_SPLIT = 29,
	IMX_SC_RM_FUNC_MEMREG_FRAG = 32,
	IMX_SC_RM_FUNC_MEMREG_FREE = 18,
	IMX_SC_RM_FUNC_FIND_MEMREG = 30,
	IMX_SC_RM_FUNC_ASSIGN_MEMREG = 19,
	IMX_SC_RM_FUNC_SET_MEMREG_PERMISSIONS = 20,
	IMX_SC_RM_FUNC_IS_MEMREG_OWNED = 21,
	IMX_SC_RM_FUNC_GET_MEMREG_INFO = 22,
	IMX_SC_RM_FUNC_ASSIGN_PAD = 23,
	IMX_SC_RM_FUNC_SET_PAD_MOVABLE = 24,
	IMX_SC_RM_FUNC_IS_PAD_OWNED = 25,
	IMX_SC_RM_FUNC_DUMP = 27,
पूर्ण;

#अगर IS_ENABLED(CONFIG_IMX_SCU)
bool imx_sc_rm_is_resource_owned(काष्ठा imx_sc_ipc *ipc, u16 resource);
#अन्यथा
अटल अंतरभूत bool
imx_sc_rm_is_resource_owned(काष्ठा imx_sc_ipc *ipc, u16 resource)
अणु
	वापस true;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर
