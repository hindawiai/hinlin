<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2020 MediaTek Inc.
 * Author: Yong Wu <yong.wu@mediatek.com>
 */
#अगर_अघोषित __DT_BINDINGS_MEMORY_MTK_MEMORY_PORT_H_
#घोषणा __DT_BINDINGS_MEMORY_MTK_MEMORY_PORT_H_

#घोषणा MTK_LARB_NR_MAX			32

#घोषणा MTK_M4U_ID(larb, port)		(((larb) << 5) | (port))
#घोषणा MTK_M4U_TO_LARB(id)		(((id) >> 5) & 0x1f)
#घोषणा MTK_M4U_TO_PORT(id)		((id) & 0x1f)

#पूर्ण_अगर
