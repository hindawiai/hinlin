<शैली गुरु>
/*
 * Copyright (c) 2018, Mellanox Technologies. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#समावेश "port_buffer.h"

पूर्णांक mlx5e_port_query_buffer(काष्ठा mlx5e_priv *priv,
			    काष्ठा mlx5e_port_buffer *port_buffer)
अणु
	u16 port_buff_cell_sz = priv->dcbx.port_buff_cell_sz;
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	पूर्णांक sz = MLX5_ST_SZ_BYTES(pbmc_reg);
	u32 total_used = 0;
	व्योम *buffer;
	व्योम *out;
	पूर्णांक err;
	पूर्णांक i;

	out = kzalloc(sz, GFP_KERNEL);
	अगर (!out)
		वापस -ENOMEM;

	err = mlx5e_port_query_pbmc(mdev, out);
	अगर (err)
		जाओ out;

	क्रम (i = 0; i < MLX5E_MAX_BUFFER; i++) अणु
		buffer = MLX5_ADDR_OF(pbmc_reg, out, buffer[i]);
		port_buffer->buffer[i].lossy =
			MLX5_GET(bufferx_reg, buffer, lossy);
		port_buffer->buffer[i].epsb =
			MLX5_GET(bufferx_reg, buffer, epsb);
		port_buffer->buffer[i].size =
			MLX5_GET(bufferx_reg, buffer, size) * port_buff_cell_sz;
		port_buffer->buffer[i].xon =
			MLX5_GET(bufferx_reg, buffer, xon_threshold) * port_buff_cell_sz;
		port_buffer->buffer[i].xoff =
			MLX5_GET(bufferx_reg, buffer, xoff_threshold) * port_buff_cell_sz;
		total_used += port_buffer->buffer[i].size;

		mlx5e_dbg(HW, priv, "buffer %d: size=%d, xon=%d, xoff=%d, epsb=%d, lossy=%d\n", i,
			  port_buffer->buffer[i].size,
			  port_buffer->buffer[i].xon,
			  port_buffer->buffer[i].xoff,
			  port_buffer->buffer[i].epsb,
			  port_buffer->buffer[i].lossy);
	पूर्ण

	port_buffer->port_buffer_size =
		MLX5_GET(pbmc_reg, out, port_buffer_size) * port_buff_cell_sz;
	port_buffer->spare_buffer_size =
		port_buffer->port_buffer_size - total_used;

	mlx5e_dbg(HW, priv, "total buffer size=%d, spare buffer size=%d\n",
		  port_buffer->port_buffer_size,
		  port_buffer->spare_buffer_size);
out:
	kमुक्त(out);
	वापस err;
पूर्ण

अटल पूर्णांक port_set_buffer(काष्ठा mlx5e_priv *priv,
			   काष्ठा mlx5e_port_buffer *port_buffer)
अणु
	u16 port_buff_cell_sz = priv->dcbx.port_buff_cell_sz;
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	पूर्णांक sz = MLX5_ST_SZ_BYTES(pbmc_reg);
	व्योम *in;
	पूर्णांक err;
	पूर्णांक i;

	in = kzalloc(sz, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	err = mlx5e_port_query_pbmc(mdev, in);
	अगर (err)
		जाओ out;

	क्रम (i = 0; i < MLX5E_MAX_BUFFER; i++) अणु
		व्योम *buffer = MLX5_ADDR_OF(pbmc_reg, in, buffer[i]);
		u64 size = port_buffer->buffer[i].size;
		u64 xoff = port_buffer->buffer[i].xoff;
		u64 xon = port_buffer->buffer[i].xon;

		करो_भाग(size, port_buff_cell_sz);
		करो_भाग(xoff, port_buff_cell_sz);
		करो_भाग(xon, port_buff_cell_sz);
		MLX5_SET(bufferx_reg, buffer, size, size);
		MLX5_SET(bufferx_reg, buffer, lossy, port_buffer->buffer[i].lossy);
		MLX5_SET(bufferx_reg, buffer, xoff_threshold, xoff);
		MLX5_SET(bufferx_reg, buffer, xon_threshold, xon);
	पूर्ण

	err = mlx5e_port_set_pbmc(mdev, in);
out:
	kमुक्त(in);
	वापस err;
पूर्ण

/* xoff = ((301+2.16 * len [m]) * speed [Gbps] + 2.72 MTU [B])
 * minimum speed value is 40Gbps
 */
अटल u32 calculate_xoff(काष्ठा mlx5e_priv *priv, अचिन्हित पूर्णांक mtu)
अणु
	u32 speed;
	u32 xoff;
	पूर्णांक err;

	err = mlx5e_port_linkspeed(priv->mdev, &speed);
	अगर (err)
		speed = SPEED_40000;
	speed = max_t(u32, speed, SPEED_40000);

	xoff = (301 + 216 * priv->dcbx.cable_len / 100) * speed / 1000 + 272 * mtu / 100;

	mlx5e_dbg(HW, priv, "%s: xoff=%d\n", __func__, xoff);
	वापस xoff;
पूर्ण

अटल पूर्णांक update_xoff_threshold(काष्ठा mlx5e_port_buffer *port_buffer,
				 u32 xoff, अचिन्हित पूर्णांक max_mtu, u16 port_buff_cell_sz)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MLX5E_MAX_BUFFER; i++) अणु
		अगर (port_buffer->buffer[i].lossy) अणु
			port_buffer->buffer[i].xoff = 0;
			port_buffer->buffer[i].xon  = 0;
			जारी;
		पूर्ण

		अगर (port_buffer->buffer[i].size <
		    (xoff + max_mtu + port_buff_cell_sz)) अणु
			pr_err("buffer_size[%d]=%d is not enough for lossless buffer\n",
			       i, port_buffer->buffer[i].size);
			वापस -ENOMEM;
		पूर्ण

		port_buffer->buffer[i].xoff = port_buffer->buffer[i].size - xoff;
		port_buffer->buffer[i].xon  =
			port_buffer->buffer[i].xoff - max_mtu;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *	update_buffer_lossy	- Update buffer configuration based on pfc
 *	@max_mtu: netdev's max_mtu
 *	@pfc_en: <input> current pfc configuration
 *	@buffer: <input> current prio to buffer mapping
 *	@xoff:   <input> xoff value
 *	@port_buff_cell_sz: <input> port buffer cell_size
 *	@port_buffer: <output> port receive buffer configuration
 *	@change: <output>
 *
 *	Update buffer configuration based on pfc configuration and
 *	priority to buffer mapping.
 *	Buffer's lossy bit is changed to:
 *		lossless अगर there is at least one PFC enabled priority
 *		mapped to this buffer lossy अगर all priorities mapped to
 *		this buffer are PFC disabled
 *
 *	@वापस: 0 अगर no error,
 *	sets change to true अगर buffer configuration was modअगरied.
 */
अटल पूर्णांक update_buffer_lossy(अचिन्हित पूर्णांक max_mtu,
			       u8 pfc_en, u8 *buffer, u32 xoff, u16 port_buff_cell_sz,
			       काष्ठा mlx5e_port_buffer *port_buffer,
			       bool *change)
अणु
	bool changed = false;
	u8 lossy_count;
	u8 prio_count;
	u8 lossy;
	पूर्णांक prio;
	पूर्णांक err;
	पूर्णांक i;

	क्रम (i = 0; i < MLX5E_MAX_BUFFER; i++) अणु
		prio_count = 0;
		lossy_count = 0;

		क्रम (prio = 0; prio < MLX5E_MAX_PRIORITY; prio++) अणु
			अगर (buffer[prio] != i)
				जारी;

			prio_count++;
			lossy_count += !(pfc_en & (1 << prio));
		पूर्ण

		अगर (lossy_count == prio_count)
			lossy = 1;
		अन्यथा /* lossy_count < prio_count */
			lossy = 0;

		अगर (lossy != port_buffer->buffer[i].lossy) अणु
			port_buffer->buffer[i].lossy = lossy;
			changed = true;
		पूर्ण
	पूर्ण

	अगर (changed) अणु
		err = update_xoff_threshold(port_buffer, xoff, max_mtu, port_buff_cell_sz);
		अगर (err)
			वापस err;

		*change = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fill_pfc_en(काष्ठा mlx5_core_dev *mdev, u8 *pfc_en)
अणु
	u32 g_rx_छोड़ो, g_tx_छोड़ो;
	पूर्णांक err;

	err = mlx5_query_port_छोड़ो(mdev, &g_rx_छोड़ो, &g_tx_छोड़ो);
	अगर (err)
		वापस err;

	/* If global छोड़ो enabled, set all active buffers to lossless.
	 * Otherwise, check PFC setting.
	 */
	अगर (g_rx_छोड़ो || g_tx_छोड़ो)
		*pfc_en = 0xff;
	अन्यथा
		err = mlx5_query_port_pfc(mdev, pfc_en, शून्य);

	वापस err;
पूर्ण

#घोषणा MINIMUM_MAX_MTU 9216
पूर्णांक mlx5e_port_manual_buffer_config(काष्ठा mlx5e_priv *priv,
				    u32 change, अचिन्हित पूर्णांक mtu,
				    काष्ठा ieee_pfc *pfc,
				    u32 *buffer_size,
				    u8 *prio2buffer)
अणु
	u16 port_buff_cell_sz = priv->dcbx.port_buff_cell_sz;
	काष्ठा mlx5e_port_buffer port_buffer;
	u32 xoff = calculate_xoff(priv, mtu);
	bool update_prio2buffer = false;
	u8 buffer[MLX5E_MAX_PRIORITY];
	bool update_buffer = false;
	अचिन्हित पूर्णांक max_mtu;
	u32 total_used = 0;
	u8 curr_pfc_en;
	पूर्णांक err;
	पूर्णांक i;

	mlx5e_dbg(HW, priv, "%s: change=%x\n", __func__, change);
	max_mtu = max_t(अचिन्हित पूर्णांक, priv->netdev->max_mtu, MINIMUM_MAX_MTU);

	err = mlx5e_port_query_buffer(priv, &port_buffer);
	अगर (err)
		वापस err;

	अगर (change & MLX5E_PORT_BUFFER_CABLE_LEN) अणु
		update_buffer = true;
		err = update_xoff_threshold(&port_buffer, xoff, max_mtu, port_buff_cell_sz);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (change & MLX5E_PORT_BUFFER_PFC) अणु
		err = mlx5e_port_query_priority2buffer(priv->mdev, buffer);
		अगर (err)
			वापस err;

		err = update_buffer_lossy(max_mtu, pfc->pfc_en, buffer, xoff, port_buff_cell_sz,
					  &port_buffer, &update_buffer);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (change & MLX5E_PORT_BUFFER_PRIO2BUFFER) अणु
		update_prio2buffer = true;
		err = fill_pfc_en(priv->mdev, &curr_pfc_en);
		अगर (err)
			वापस err;

		err = update_buffer_lossy(max_mtu, curr_pfc_en, prio2buffer, port_buff_cell_sz,
					  xoff, &port_buffer, &update_buffer);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (change & MLX5E_PORT_BUFFER_SIZE) अणु
		क्रम (i = 0; i < MLX5E_MAX_BUFFER; i++) अणु
			mlx5e_dbg(HW, priv, "%s: buffer[%d]=%d\n", __func__, i, buffer_size[i]);
			अगर (!port_buffer.buffer[i].lossy && !buffer_size[i]) अणु
				mlx5e_dbg(HW, priv, "%s: lossless buffer[%d] size cannot be zero\n",
					  __func__, i);
				वापस -EINVAL;
			पूर्ण

			port_buffer.buffer[i].size = buffer_size[i];
			total_used += buffer_size[i];
		पूर्ण

		mlx5e_dbg(HW, priv, "%s: total buffer requested=%d\n", __func__, total_used);

		अगर (total_used > port_buffer.port_buffer_size)
			वापस -EINVAL;

		update_buffer = true;
		err = update_xoff_threshold(&port_buffer, xoff, max_mtu, port_buff_cell_sz);
		अगर (err)
			वापस err;
	पूर्ण

	/* Need to update buffer configuration अगर xoff value is changed */
	अगर (!update_buffer && xoff != priv->dcbx.xoff) अणु
		update_buffer = true;
		err = update_xoff_threshold(&port_buffer, xoff, max_mtu, port_buff_cell_sz);
		अगर (err)
			वापस err;
	पूर्ण
	priv->dcbx.xoff = xoff;

	/* Apply the settings */
	अगर (update_buffer) अणु
		err = port_set_buffer(priv, &port_buffer);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (update_prio2buffer)
		err = mlx5e_port_set_priority2buffer(priv->mdev, prio2buffer);

	वापस err;
पूर्ण
