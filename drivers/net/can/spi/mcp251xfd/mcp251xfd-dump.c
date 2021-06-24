<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// mcp251xfd - Microchip MCP251xFD Family CAN controller driver
//
// Copyright (c) 2020, 2021 Pengutronix,
//               Marc Kleine-Budde <kernel@pengutronix.de>
// Copyright (C) 2015-2018 Etnaviv Project
//

#समावेश <linux/devcoredump.h>

#समावेश "mcp251xfd.h"
#समावेश "mcp251xfd-dump.h"

काष्ठा mcp251xfd_dump_iter अणु
	व्योम *start;
	काष्ठा mcp251xfd_dump_object_header *hdr;
	व्योम *data;
पूर्ण;

काष्ठा mcp251xfd_dump_reg_space अणु
	u16 base;
	u16 size;
पूर्ण;

काष्ठा mcp251xfd_dump_ring अणु
	क्रमागत mcp251xfd_dump_object_ring_key key;
	u32 val;
पूर्ण;

अटल स्थिर काष्ठा mcp251xfd_dump_reg_space mcp251xfd_dump_reg_space[] = अणु
	अणु
		.base = MCP251XFD_REG_CON,
		.size = MCP251XFD_REG_FLTOBJ(32) - MCP251XFD_REG_CON,
	पूर्ण, अणु
		.base = MCP251XFD_RAM_START,
		.size = MCP251XFD_RAM_SIZE,
	पूर्ण, अणु
		.base = MCP251XFD_REG_OSC,
		.size = MCP251XFD_REG_DEVID - MCP251XFD_REG_OSC,
	पूर्ण,
पूर्ण;

अटल व्योम mcp251xfd_dump_header(काष्ठा mcp251xfd_dump_iter *iter,
				  क्रमागत mcp251xfd_dump_object_type object_type,
				  स्थिर व्योम *data_end)
अणु
	काष्ठा mcp251xfd_dump_object_header *hdr = iter->hdr;
	अचिन्हित पूर्णांक len;

	len = data_end - iter->data;
	अगर (!len)
		वापस;

	hdr->magic = cpu_to_le32(MCP251XFD_DUMP_MAGIC);
	hdr->type = cpu_to_le32(object_type);
	hdr->offset = cpu_to_le32(iter->data - iter->start);
	hdr->len = cpu_to_le32(len);

	iter->hdr++;
	iter->data += len;
पूर्ण

अटल व्योम mcp251xfd_dump_रेजिस्टरs(स्थिर काष्ठा mcp251xfd_priv *priv,
				     काष्ठा mcp251xfd_dump_iter *iter)
अणु
	स्थिर पूर्णांक val_bytes = regmap_get_val_bytes(priv->map_rx);
	काष्ठा mcp251xfd_dump_object_reg *reg = iter->data;
	अचिन्हित पूर्णांक i, j;
	पूर्णांक err;

	क्रम (i = 0; i < ARRAY_SIZE(mcp251xfd_dump_reg_space); i++) अणु
		स्थिर काष्ठा mcp251xfd_dump_reg_space *reg_space;
		व्योम *buf;

		reg_space = &mcp251xfd_dump_reg_space[i];

		buf = kदो_स्मृति(reg_space->size, GFP_KERNEL);
		अगर (!buf)
			जाओ out;

		err = regmap_bulk_पढ़ो(priv->map_reg, reg_space->base,
				       buf, reg_space->size / val_bytes);
		अगर (err) अणु
			kमुक्त(buf);
			जारी;
		पूर्ण

		क्रम (j = 0; j < reg_space->size; j += माप(u32), reg++) अणु
			reg->reg = cpu_to_le32(reg_space->base + j);
			reg->val = cpu_to_le32p(buf + j);
		पूर्ण

		kमुक्त(buf);
	पूर्ण

 out:
	mcp251xfd_dump_header(iter, MCP251XFD_DUMP_OBJECT_TYPE_REG, reg);
पूर्ण

अटल व्योम mcp251xfd_dump_ring(काष्ठा mcp251xfd_dump_iter *iter,
				क्रमागत mcp251xfd_dump_object_type object_type,
				स्थिर काष्ठा mcp251xfd_dump_ring *dump_ring,
				अचिन्हित पूर्णांक len)
अणु
	काष्ठा mcp251xfd_dump_object_reg *reg = iter->data;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < len; i++, reg++) अणु
		reg->reg = cpu_to_le32(dump_ring[i].key);
		reg->val = cpu_to_le32(dump_ring[i].val);
	पूर्ण

	mcp251xfd_dump_header(iter, object_type, reg);
पूर्ण

अटल व्योम mcp251xfd_dump_tef_ring(स्थिर काष्ठा mcp251xfd_priv *priv,
				    काष्ठा mcp251xfd_dump_iter *iter)
अणु
	स्थिर काष्ठा mcp251xfd_tef_ring *tef = priv->tef;
	स्थिर काष्ठा mcp251xfd_tx_ring *tx = priv->tx;
	स्थिर काष्ठा mcp251xfd_dump_ring dump_ring[] = अणु
		अणु
			.key = MCP251XFD_DUMP_OBJECT_RING_KEY_HEAD,
			.val = tef->head,
		पूर्ण, अणु
			.key = MCP251XFD_DUMP_OBJECT_RING_KEY_TAIL,
			.val = tef->tail,
		पूर्ण, अणु
			.key = MCP251XFD_DUMP_OBJECT_RING_KEY_BASE,
			.val = 0,
		पूर्ण, अणु
			.key = MCP251XFD_DUMP_OBJECT_RING_KEY_NR,
			.val = 0,
		पूर्ण, अणु
			.key = MCP251XFD_DUMP_OBJECT_RING_KEY_FIFO_NR,
			.val = 0,
		पूर्ण, अणु
			.key = MCP251XFD_DUMP_OBJECT_RING_KEY_OBJ_NUM,
			.val = tx->obj_num,
		पूर्ण, अणु
			.key = MCP251XFD_DUMP_OBJECT_RING_KEY_OBJ_SIZE,
			.val = माप(काष्ठा mcp251xfd_hw_tef_obj),
		पूर्ण,
	पूर्ण;

	mcp251xfd_dump_ring(iter, MCP251XFD_DUMP_OBJECT_TYPE_TEF,
			    dump_ring, ARRAY_SIZE(dump_ring));
पूर्ण

अटल व्योम mcp251xfd_dump_rx_ring_one(स्थिर काष्ठा mcp251xfd_priv *priv,
				       काष्ठा mcp251xfd_dump_iter *iter,
				       स्थिर काष्ठा mcp251xfd_rx_ring *rx)
अणु
	स्थिर काष्ठा mcp251xfd_dump_ring dump_ring[] = अणु
		अणु
			.key = MCP251XFD_DUMP_OBJECT_RING_KEY_HEAD,
			.val = rx->head,
		पूर्ण, अणु
			.key = MCP251XFD_DUMP_OBJECT_RING_KEY_TAIL,
			.val = rx->tail,
		पूर्ण, अणु
			.key = MCP251XFD_DUMP_OBJECT_RING_KEY_BASE,
			.val = rx->base,
		पूर्ण, अणु
			.key = MCP251XFD_DUMP_OBJECT_RING_KEY_NR,
			.val = rx->nr,
		पूर्ण, अणु
			.key = MCP251XFD_DUMP_OBJECT_RING_KEY_FIFO_NR,
			.val = rx->fअगरo_nr,
		पूर्ण, अणु
			.key = MCP251XFD_DUMP_OBJECT_RING_KEY_OBJ_NUM,
			.val = rx->obj_num,
		पूर्ण, अणु
			.key = MCP251XFD_DUMP_OBJECT_RING_KEY_OBJ_SIZE,
			.val = rx->obj_size,
		पूर्ण,
	पूर्ण;

	mcp251xfd_dump_ring(iter, MCP251XFD_DUMP_OBJECT_TYPE_RX,
			    dump_ring, ARRAY_SIZE(dump_ring));
पूर्ण

अटल व्योम mcp251xfd_dump_rx_ring(स्थिर काष्ठा mcp251xfd_priv *priv,
				   काष्ठा mcp251xfd_dump_iter *iter)
अणु
	काष्ठा mcp251xfd_rx_ring *rx_ring;
	अचिन्हित पूर्णांक i;

	mcp251xfd_क्रम_each_rx_ring(priv, rx_ring, i)
		mcp251xfd_dump_rx_ring_one(priv, iter, rx_ring);
पूर्ण

अटल व्योम mcp251xfd_dump_tx_ring(स्थिर काष्ठा mcp251xfd_priv *priv,
				   काष्ठा mcp251xfd_dump_iter *iter)
अणु
	स्थिर काष्ठा mcp251xfd_tx_ring *tx = priv->tx;
	स्थिर काष्ठा mcp251xfd_dump_ring dump_ring[] = अणु
		अणु
			.key = MCP251XFD_DUMP_OBJECT_RING_KEY_HEAD,
			.val = tx->head,
		पूर्ण, अणु
			.key = MCP251XFD_DUMP_OBJECT_RING_KEY_TAIL,
			.val = tx->tail,
		पूर्ण, अणु
			.key = MCP251XFD_DUMP_OBJECT_RING_KEY_BASE,
			.val = tx->base,
		पूर्ण, अणु
			.key = MCP251XFD_DUMP_OBJECT_RING_KEY_NR,
			.val = 0,
		पूर्ण, अणु
			.key = MCP251XFD_DUMP_OBJECT_RING_KEY_FIFO_NR,
			.val = MCP251XFD_TX_FIFO,
		पूर्ण, अणु
			.key = MCP251XFD_DUMP_OBJECT_RING_KEY_OBJ_NUM,
			.val = tx->obj_num,
		पूर्ण, अणु
			.key = MCP251XFD_DUMP_OBJECT_RING_KEY_OBJ_SIZE,
			.val = tx->obj_size,
		पूर्ण,
	पूर्ण;

	mcp251xfd_dump_ring(iter, MCP251XFD_DUMP_OBJECT_TYPE_TX,
			    dump_ring, ARRAY_SIZE(dump_ring));
पूर्ण

अटल व्योम mcp251xfd_dump_end(स्थिर काष्ठा mcp251xfd_priv *priv,
			       काष्ठा mcp251xfd_dump_iter *iter)
अणु
	काष्ठा mcp251xfd_dump_object_header *hdr = iter->hdr;

	hdr->magic = cpu_to_le32(MCP251XFD_DUMP_MAGIC);
	hdr->type = cpu_to_le32(MCP251XFD_DUMP_OBJECT_TYPE_END);
	hdr->offset = cpu_to_le32(0);
	hdr->len = cpu_to_le32(0);

	/* provoke शून्य poपूर्णांकer access, अगर used after END object */
	iter->hdr = शून्य;
पूर्ण

व्योम mcp251xfd_dump(स्थिर काष्ठा mcp251xfd_priv *priv)
अणु
	काष्ठा mcp251xfd_dump_iter iter;
	अचिन्हित पूर्णांक rings_num, obj_num;
	अचिन्हित पूर्णांक file_size = 0;
	अचिन्हित पूर्णांक i;

	/* रेजिस्टर space + end marker */
	obj_num = 2;

	/* रेजिस्टर space */
	क्रम (i = 0; i < ARRAY_SIZE(mcp251xfd_dump_reg_space); i++)
		file_size += mcp251xfd_dump_reg_space[i].size / माप(u32) *
			माप(काष्ठा mcp251xfd_dump_object_reg);

	/* TEF ring, RX ring, TX rings */
	rings_num = 1 + priv->rx_ring_num + 1;
	obj_num += rings_num;
	file_size += rings_num * __MCP251XFD_DUMP_OBJECT_RING_KEY_MAX  *
		माप(काष्ठा mcp251xfd_dump_object_reg);

	/* size of the headers */
	file_size += माप(*iter.hdr) * obj_num;

	/* allocate the file in vदो_स्मृति memory, it's likely to be big */
	iter.start = __vदो_स्मृति(file_size, GFP_KERNEL | __GFP_NOWARN |
			       __GFP_ZERO | __GFP_NORETRY);
	अगर (!iter.start) अणु
		netdev_warn(priv->ndev, "Failed to allocate devcoredump file.\n");
		वापस;
	पूर्ण

	/* poपूर्णांक the data member after the headers */
	iter.hdr = iter.start;
	iter.data = &iter.hdr[obj_num];

	mcp251xfd_dump_रेजिस्टरs(priv, &iter);
	mcp251xfd_dump_tef_ring(priv, &iter);
	mcp251xfd_dump_rx_ring(priv, &iter);
	mcp251xfd_dump_tx_ring(priv, &iter);
	mcp251xfd_dump_end(priv, &iter);

	dev_coredumpv(&priv->spi->dev, iter.start,
		      iter.data - iter.start, GFP_KERNEL);
पूर्ण
