<शैली गुरु>
/*
 * Copyright (c) 2017 Mellanox Technologies. All rights reserved.
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
 *
 */

#अगर_अघोषित MLX5_FPGA_SDK_H
#घोषणा MLX5_FPGA_SDK_H

#समावेश <linux/types.h>
#समावेश <linux/dma-direction.h>

/**
 * DOC: Innova SDK
 * This header defines the in-kernel API क्रम Innova FPGA client drivers.
 */
#घोषणा SBU_QP_QUEUE_SIZE 8
#घोषणा MLX5_FPGA_CMD_TIMEOUT_MSEC (60 * 1000)

/**
 * क्रमागत mlx5_fpga_access_type - Enumerated the dअगरferent methods possible क्रम
 * accessing the device memory address space
 *
 * @MLX5_FPGA_ACCESS_TYPE_I2C: Use the slow CX-FPGA I2C bus
 * @MLX5_FPGA_ACCESS_TYPE_DONTCARE: Use the fastest available method
 */
क्रमागत mlx5_fpga_access_type अणु
	MLX5_FPGA_ACCESS_TYPE_I2C = 0x0,
	MLX5_FPGA_ACCESS_TYPE_DONTCARE = 0x0,
पूर्ण;

काष्ठा mlx5_fpga_conn;
काष्ठा mlx5_fpga_device;

/**
 * काष्ठा mlx5_fpga_dma_entry - A scatter-gather DMA entry
 */
काष्ठा mlx5_fpga_dma_entry अणु
	/** @data: Virtual address poपूर्णांकer to the data */
	व्योम *data;
	/** @size: Size in bytes of the data */
	अचिन्हित पूर्णांक size;
	/** @dma_addr: Private member. Physical DMA-mapped address of the data */
	dma_addr_t dma_addr;
पूर्ण;

/**
 * काष्ठा mlx5_fpga_dma_buf - A packet buffer
 * May contain up to 2 scatter-gather data entries
 */
काष्ठा mlx5_fpga_dma_buf अणु
	/** @dma_dir: DMA direction */
	क्रमागत dma_data_direction dma_dir;
	/** @sg: Scatter-gather entries poपूर्णांकing to the data in memory */
	काष्ठा mlx5_fpga_dma_entry sg[2];
	/** @list: Item in SQ backlog, क्रम TX packets */
	काष्ठा list_head list;
	/**
	 * @complete: Completion routine, क्रम TX packets
	 * @conn: FPGA Connection this packet was sent to
	 * @fdev: FPGA device this packet was sent to
	 * @buf: The packet buffer
	 * @status: 0 अगर successful, or an error code otherwise
	 */
	व्योम (*complete)(काष्ठा mlx5_fpga_conn *conn,
			 काष्ठा mlx5_fpga_device *fdev,
			 काष्ठा mlx5_fpga_dma_buf *buf, u8 status);
पूर्ण;

/**
 * काष्ठा mlx5_fpga_conn_attr - FPGA connection attributes
 * Describes the attributes of a connection
 */
काष्ठा mlx5_fpga_conn_attr अणु
	/** @tx_size: Size of connection TX queue, in packets */
	अचिन्हित पूर्णांक tx_size;
	/** @rx_size: Size of connection RX queue, in packets */
	अचिन्हित पूर्णांक rx_size;
	/**
	 * @recv_cb: Callback function which is called क्रम received packets
	 * @cb_arg: The value provided in mlx5_fpga_conn_attr.cb_arg
	 * @buf: A buffer containing a received packet
	 *
	 * buf is guaranteed to only contain a single scatter-gather entry.
	 * The size of the actual packet received is specअगरied in buf.sg[0].size
	 * When this callback वापसs, the packet buffer may be re-used क्रम
	 * subsequent receives.
	 */
	व्योम (*recv_cb)(व्योम *cb_arg, काष्ठा mlx5_fpga_dma_buf *buf);
	/** @cb_arg: A context to be passed to recv_cb callback */
	व्योम *cb_arg;
पूर्ण;

/**
 * mlx5_fpga_sbu_conn_create() - Initialize a new FPGA SBU connection
 * @fdev: The FPGA device
 * @attr: Attributes of the new connection
 *
 * Sets up a new FPGA SBU connection with the specअगरied attributes.
 * The receive callback function may be called क्रम incoming messages even
 * beक्रमe this function वापसs.
 *
 * The caller must eventually destroy the connection by calling
 * mlx5_fpga_sbu_conn_destroy.
 *
 * Return: A new connection, or ERR_PTR() error value otherwise.
 */
काष्ठा mlx5_fpga_conn *
mlx5_fpga_sbu_conn_create(काष्ठा mlx5_fpga_device *fdev,
			  काष्ठा mlx5_fpga_conn_attr *attr);

/**
 * mlx5_fpga_sbu_conn_destroy() - Destroy an FPGA SBU connection
 * @conn: The FPGA SBU connection to destroy
 *
 * Cleans up an FPGA SBU connection which was previously created with
 * mlx5_fpga_sbu_conn_create.
 */
व्योम mlx5_fpga_sbu_conn_destroy(काष्ठा mlx5_fpga_conn *conn);

/**
 * mlx5_fpga_sbu_conn_sendmsg() - Queue the transmission of a packet
 * @conn: An FPGA SBU connection
 * @buf: The packet buffer
 *
 * Queues a packet क्रम transmission over an FPGA SBU connection.
 * The buffer should not be modअगरied or मुक्तd until completion.
 * Upon completion, the buf's complete() callback is invoked, indicating the
 * success or error status of the transmission.
 *
 * Return: 0 अगर successful, or an error value otherwise.
 */
पूर्णांक mlx5_fpga_sbu_conn_sendmsg(काष्ठा mlx5_fpga_conn *conn,
			       काष्ठा mlx5_fpga_dma_buf *buf);

/**
 * mlx5_fpga_mem_पढ़ो() - Read from FPGA memory address space
 * @fdev: The FPGA device
 * @size: Size of chunk to पढ़ो, in bytes
 * @addr: Starting address to पढ़ो from, in FPGA address space
 * @buf: Buffer to पढ़ो पूर्णांकo
 * @access_type: Method क्रम पढ़ोing
 *
 * Reads from the specअगरied address पूर्णांकo the specअगरied buffer.
 * The address may poपूर्णांक to configuration space or to DDR.
 * Large पढ़ोs may be perक्रमmed पूर्णांकernally as several non-atomic operations.
 * This function may sleep, so should not be called from atomic contexts.
 *
 * Return: 0 अगर successful, or an error value otherwise.
 */
पूर्णांक mlx5_fpga_mem_पढ़ो(काष्ठा mlx5_fpga_device *fdev, माप_प्रकार size, u64 addr,
		       व्योम *buf, क्रमागत mlx5_fpga_access_type access_type);

/**
 * mlx5_fpga_mem_ग_लिखो() - Write to FPGA memory address space
 * @fdev: The FPGA device
 * @size: Size of chunk to ग_लिखो, in bytes
 * @addr: Starting address to ग_लिखो to, in FPGA address space
 * @buf: Buffer which contains data to ग_लिखो
 * @access_type: Method क्रम writing
 *
 * Writes the specअगरied buffer data to FPGA memory at the specअगरied address.
 * The address may poपूर्णांक to configuration space or to DDR.
 * Large ग_लिखोs may be perक्रमmed पूर्णांकernally as several non-atomic operations.
 * This function may sleep, so should not be called from atomic contexts.
 *
 * Return: 0 अगर successful, or an error value otherwise.
 */
पूर्णांक mlx5_fpga_mem_ग_लिखो(काष्ठा mlx5_fpga_device *fdev, माप_प्रकार size, u64 addr,
			व्योम *buf, क्रमागत mlx5_fpga_access_type access_type);

/**
 * mlx5_fpga_get_sbu_caps() - Read the SBU capabilities
 * @fdev: The FPGA device
 * @size: Size of the buffer to पढ़ो पूर्णांकo
 * @buf: Buffer to पढ़ो the capabilities पूर्णांकo
 *
 * Reads the FPGA SBU capabilities पूर्णांकo the specअगरied buffer.
 * The क्रमmat of the capabilities buffer is SBU-dependent.
 *
 * Return: 0 अगर successful
 *         -EINVAL अगर the buffer is not large enough to contain SBU caps
 *         or any other error value otherwise.
 */
पूर्णांक mlx5_fpga_get_sbu_caps(काष्ठा mlx5_fpga_device *fdev, पूर्णांक size, व्योम *buf);

#पूर्ण_अगर /* MLX5_FPGA_SDK_H */
