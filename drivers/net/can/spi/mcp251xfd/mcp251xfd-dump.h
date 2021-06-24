<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * mcp251xfd - Microchip MCP251xFD Family CAN controller driver
 *
 * Copyright (c) 2019, 2020, 2021 Pengutronix,
 *               Marc Kleine-Budde <kernel@pengutronix.de>
 */

#अगर_अघोषित _MCP251XFD_DUMP_H
#घोषणा _MCP251XFD_DUMP_H

#घोषणा MCP251XFD_DUMP_MAGIC 0x1825434d

क्रमागत mcp251xfd_dump_object_type अणु
	MCP251XFD_DUMP_OBJECT_TYPE_REG,
	MCP251XFD_DUMP_OBJECT_TYPE_TEF,
	MCP251XFD_DUMP_OBJECT_TYPE_RX,
	MCP251XFD_DUMP_OBJECT_TYPE_TX,
	MCP251XFD_DUMP_OBJECT_TYPE_END = -1,
पूर्ण;

क्रमागत mcp251xfd_dump_object_ring_key अणु
	MCP251XFD_DUMP_OBJECT_RING_KEY_HEAD,
	MCP251XFD_DUMP_OBJECT_RING_KEY_TAIL,
	MCP251XFD_DUMP_OBJECT_RING_KEY_BASE,
	MCP251XFD_DUMP_OBJECT_RING_KEY_NR,
	MCP251XFD_DUMP_OBJECT_RING_KEY_FIFO_NR,
	MCP251XFD_DUMP_OBJECT_RING_KEY_OBJ_NUM,
	MCP251XFD_DUMP_OBJECT_RING_KEY_OBJ_SIZE,
	__MCP251XFD_DUMP_OBJECT_RING_KEY_MAX,
पूर्ण;

काष्ठा mcp251xfd_dump_object_header अणु
	__le32 magic;
	__le32 type;
	__le32 offset;
	__le32 len;
पूर्ण;

काष्ठा mcp251xfd_dump_object_reg अणु
	__le32 reg;
	__le32 val;
पूर्ण;

#पूर्ण_अगर
