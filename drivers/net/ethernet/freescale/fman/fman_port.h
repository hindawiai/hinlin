<शैली गुरु>
/*
 * Copyright 2008 - 2015 Freescale Semiconductor Inc.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary क्रमm must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       करोcumentation and/or other materials provided with the distribution.
 *     * Neither the name of Freescale Semiconductor nor the
 *       names of its contributors may be used to enकरोrse or promote products
 *       derived from this software without specअगरic prior written permission.
 *
 *
 * ALTERNATIVELY, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") as published by the Free Software
 * Foundation, either version 2 of that License or (at your option) any
 * later version.
 *
 * THIS SOFTWARE IS PROVIDED BY Freescale Semiconductor ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Freescale Semiconductor BE LIABLE FOR ANY
 * सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#अगर_अघोषित __FMAN_PORT_H
#घोषणा __FMAN_PORT_H

#समावेश "fman.h"

/* FM Port API
 * The FM uses a general module called "port" to represent a Tx port (MAC),
 * an Rx port (MAC).
 * The number of ports in an FM varies between SOCs.
 * The SW driver manages these ports as sub-modules of the FM,i.e. after an
 * FM is initialized, its ports may be initialized and operated upon.
 * The port is initialized aware of its type, but other functions on a port
 * may be indअगरferent to its type. When necessary, the driver verअगरies
 * coherence and वापसs error अगर applicable.
 * On initialization, user specअगरies the port type and it's index (relative
 * to the port's type) - always starting at 0.
 */

/* FM Frame error */
/* Frame Descriptor errors */
/* Not क्रम Rx-Port! Unsupported Format */
#घोषणा FM_PORT_FRM_ERR_UNSUPPORTED_FORMAT	FM_FD_ERR_UNSUPPORTED_FORMAT
/* Not क्रम Rx-Port! Length Error */
#घोषणा FM_PORT_FRM_ERR_LENGTH			FM_FD_ERR_LENGTH
/* DMA Data error */
#घोषणा FM_PORT_FRM_ERR_DMA			FM_FD_ERR_DMA
/* non Frame-Manager error; probably come from SEC that was chained to FM */
#घोषणा FM_PORT_FRM_ERR_NON_FM			FM_FD_RX_STATUS_ERR_NON_FM
 /* IPR error */
#घोषणा FM_PORT_FRM_ERR_IPRE			(FM_FD_ERR_IPR & ~FM_FD_IPR)
/* IPR non-consistent-sp */
#घोषणा FM_PORT_FRM_ERR_IPR_NCSP		(FM_FD_ERR_IPR_NCSP &	\
						~FM_FD_IPR)

/* Rx FIFO overflow, FCS error, code error, running disparity
 * error (SGMII and TBI modes), FIFO parity error.
 * PHY Sequence error, PHY error control अक्षरacter detected.
 */
#घोषणा FM_PORT_FRM_ERR_PHYSICAL                FM_FD_ERR_PHYSICAL
/* Frame too दीर्घ OR Frame size exceeds max_length_frame  */
#घोषणा FM_PORT_FRM_ERR_SIZE                    FM_FD_ERR_SIZE
/* indicates a classअगरier "drop" operation */
#घोषणा FM_PORT_FRM_ERR_CLS_DISCARD             FM_FD_ERR_CLS_DISCARD
/* Extract Out of Frame */
#घोषणा FM_PORT_FRM_ERR_EXTRACTION              FM_FD_ERR_EXTRACTION
/* No Scheme Selected */
#घोषणा FM_PORT_FRM_ERR_NO_SCHEME               FM_FD_ERR_NO_SCHEME
/* Keysize Overflow */
#घोषणा FM_PORT_FRM_ERR_KEYSIZE_OVERFLOW        FM_FD_ERR_KEYSIZE_OVERFLOW
/* Frame color is red */
#घोषणा FM_PORT_FRM_ERR_COLOR_RED               FM_FD_ERR_COLOR_RED
/* Frame color is yellow */
#घोषणा FM_PORT_FRM_ERR_COLOR_YELLOW            FM_FD_ERR_COLOR_YELLOW
/* Parser Time out Exceed */
#घोषणा FM_PORT_FRM_ERR_PRS_TIMEOUT             FM_FD_ERR_PRS_TIMEOUT
/* Invalid Soft Parser inकाष्ठाion */
#घोषणा FM_PORT_FRM_ERR_PRS_ILL_INSTRUCT        FM_FD_ERR_PRS_ILL_INSTRUCT
/* Header error was identअगरied during parsing */
#घोषणा FM_PORT_FRM_ERR_PRS_HDR_ERR             FM_FD_ERR_PRS_HDR_ERR
/* Frame parsed beyind 256 first bytes */
#घोषणा FM_PORT_FRM_ERR_BLOCK_LIMIT_EXCEEDED    FM_FD_ERR_BLOCK_LIMIT_EXCEEDED
/* FPM Frame Processing Timeout Exceeded */
#घोषणा FM_PORT_FRM_ERR_PROCESS_TIMEOUT         0x00000001

काष्ठा fman_port;

/* A काष्ठाure क्रम additional Rx port parameters */
काष्ठा fman_port_rx_params अणु
	u32 err_fqid;			/* Error Queue Id. */
	u32 dflt_fqid;			/* Default Queue Id. */
	u32 pcd_base_fqid;		/* PCD base Queue Id. */
	u32 pcd_fqs_count;		/* Number of PCD FQs. */

	/* Which बाह्यal buffer pools are used
	 * (up to FMAN_PORT_MAX_EXT_POOLS_NUM), and their sizes.
	 */
	काष्ठा fman_ext_pools ext_buf_pools;
पूर्ण;

/* A काष्ठाure क्रम additional non-Rx port parameters */
काष्ठा fman_port_non_rx_params अणु
	/* Error Queue Id. */
	u32 err_fqid;
	/* For Tx - Default Confirmation queue, 0 means no Tx confirmation
	 * क्रम processed frames. For OP port - शेष Rx queue.
	 */
	u32 dflt_fqid;
पूर्ण;

/* A जोड़ क्रम additional parameters depending on port type */
जोड़ fman_port_specअगरic_params अणु
	/* Rx port parameters काष्ठाure */
	काष्ठा fman_port_rx_params rx_params;
	/* Non-Rx port parameters काष्ठाure */
	काष्ठा fman_port_non_rx_params non_rx_params;
पूर्ण;

/* A काष्ठाure representing FM initialization parameters */
काष्ठा fman_port_params अणु
	/* Virtual Address of memory mapped FM Port रेजिस्टरs. */
	व्योम *fm;
	जोड़ fman_port_specअगरic_params specअगरic_params;
	/* Additional parameters depending on port type. */
पूर्ण;

पूर्णांक fman_port_config(काष्ठा fman_port *port, काष्ठा fman_port_params *params);

व्योम fman_port_use_kg_hash(काष्ठा fman_port *port, bool enable);

पूर्णांक fman_port_init(काष्ठा fman_port *port);

पूर्णांक fman_port_cfg_buf_prefix_content(काष्ठा fman_port *port,
				     काष्ठा fman_buffer_prefix_content
				     *buffer_prefix_content);

पूर्णांक fman_port_disable(काष्ठा fman_port *port);

पूर्णांक fman_port_enable(काष्ठा fman_port *port);

u32 fman_port_get_qman_channel_id(काष्ठा fman_port *port);

पूर्णांक fman_port_get_hash_result_offset(काष्ठा fman_port *port, u32 *offset);

पूर्णांक fman_port_get_tstamp(काष्ठा fman_port *port, स्थिर व्योम *data, u64 *tstamp);

काष्ठा fman_port *fman_port_bind(काष्ठा device *dev);

काष्ठा device *fman_port_get_device(काष्ठा fman_port *port);

#पूर्ण_अगर /* __FMAN_PORT_H */
