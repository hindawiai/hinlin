<शैली गुरु>
/*
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 *   redistributing this file, you may करो so under either license.
 *
 *   GPL LICENSE SUMMARY
 *
 *   Copyright (C) 2015 EMC Corporation. All Rights Reserved.
 *   Copyright (C) 2016 T-Platक्रमms. All Rights Reserved.
 *
 *   This program is मुक्त software; you can redistribute it and/or modअगरy
 *   it under the terms of version 2 of the GNU General Public License as
 *   published by the Free Software Foundation.
 *
 *   This program is distributed in the hope that it will be useful, but
 *   WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *   General Public License क्रम more details.
 *
 *   BSD LICENSE
 *
 *   Copyright (C) 2015 EMC Corporation. All Rights Reserved.
 *   Copyright (C) 2016 T-Platक्रमms. All Rights Reserved.
 *
 *   Redistribution and use in source and binary क्रमms, with or without
 *   modअगरication, are permitted provided that the following conditions
 *   are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary क्रमm must reproduce the above copy
 *       notice, this list of conditions and the following disclaimer in
 *       the करोcumentation and/or other materials provided with the
 *       distribution.
 *     * Neither the name of Intel Corporation nor the names of its
 *       contributors may be used to enकरोrse or promote products derived
 *       from this software without specअगरic prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * PCIe NTB Linux driver
 *
 * Contact Inक्रमmation:
 * Allen Hubbe <Allen.Hubbe@emc.com>
 */

#अगर_अघोषित _NTB_H_
#घोषणा _NTB_H_

#समावेश <linux/completion.h>
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>

काष्ठा ntb_client;
काष्ठा ntb_dev;
काष्ठा ntb_msi;
काष्ठा pci_dev;

/**
 * क्रमागत ntb_topo - NTB connection topology
 * @NTB_TOPO_NONE:	Topology is unknown or invalid.
 * @NTB_TOPO_PRI:	On primary side of local ntb.
 * @NTB_TOPO_SEC:	On secondary side of remote ntb.
 * @NTB_TOPO_B2B_USD:	On primary side of local ntb upstream of remote ntb.
 * @NTB_TOPO_B2B_DSD:	On primary side of local ntb करोwnstream of remote ntb.
 * @NTB_TOPO_SWITCH:	Connected via a चयन which supports ntb.
 * @NTB_TOPO_CROSSLINK: Connected via two symmetric चयनecs
 */
क्रमागत ntb_topo अणु
	NTB_TOPO_NONE = -1,
	NTB_TOPO_PRI,
	NTB_TOPO_SEC,
	NTB_TOPO_B2B_USD,
	NTB_TOPO_B2B_DSD,
	NTB_TOPO_SWITCH,
	NTB_TOPO_CROSSLINK,
पूर्ण;

अटल अंतरभूत पूर्णांक ntb_topo_is_b2b(क्रमागत ntb_topo topo)
अणु
	चयन ((पूर्णांक)topo) अणु
	हाल NTB_TOPO_B2B_USD:
	हाल NTB_TOPO_B2B_DSD:
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत अक्षर *ntb_topo_string(क्रमागत ntb_topo topo)
अणु
	चयन (topo) अणु
	हाल NTB_TOPO_NONE:		वापस "NTB_TOPO_NONE";
	हाल NTB_TOPO_PRI:		वापस "NTB_TOPO_PRI";
	हाल NTB_TOPO_SEC:		वापस "NTB_TOPO_SEC";
	हाल NTB_TOPO_B2B_USD:		वापस "NTB_TOPO_B2B_USD";
	हाल NTB_TOPO_B2B_DSD:		वापस "NTB_TOPO_B2B_DSD";
	हाल NTB_TOPO_SWITCH:		वापस "NTB_TOPO_SWITCH";
	हाल NTB_TOPO_CROSSLINK:	वापस "NTB_TOPO_CROSSLINK";
	पूर्ण
	वापस "NTB_TOPO_INVALID";
पूर्ण

/**
 * क्रमागत ntb_speed - NTB link training speed
 * @NTB_SPEED_AUTO:	Request the max supported speed.
 * @NTB_SPEED_NONE:	Link is not trained to any speed.
 * @NTB_SPEED_GEN1:	Link is trained to gen1 speed.
 * @NTB_SPEED_GEN2:	Link is trained to gen2 speed.
 * @NTB_SPEED_GEN3:	Link is trained to gen3 speed.
 * @NTB_SPEED_GEN4:	Link is trained to gen4 speed.
 */
क्रमागत ntb_speed अणु
	NTB_SPEED_AUTO = -1,
	NTB_SPEED_NONE = 0,
	NTB_SPEED_GEN1 = 1,
	NTB_SPEED_GEN2 = 2,
	NTB_SPEED_GEN3 = 3,
	NTB_SPEED_GEN4 = 4
पूर्ण;

/**
 * क्रमागत ntb_width - NTB link training width
 * @NTB_WIDTH_AUTO:	Request the max supported width.
 * @NTB_WIDTH_NONE:	Link is not trained to any width.
 * @NTB_WIDTH_1:	Link is trained to 1 lane width.
 * @NTB_WIDTH_2:	Link is trained to 2 lane width.
 * @NTB_WIDTH_4:	Link is trained to 4 lane width.
 * @NTB_WIDTH_8:	Link is trained to 8 lane width.
 * @NTB_WIDTH_12:	Link is trained to 12 lane width.
 * @NTB_WIDTH_16:	Link is trained to 16 lane width.
 * @NTB_WIDTH_32:	Link is trained to 32 lane width.
 */
क्रमागत ntb_width अणु
	NTB_WIDTH_AUTO = -1,
	NTB_WIDTH_NONE = 0,
	NTB_WIDTH_1 = 1,
	NTB_WIDTH_2 = 2,
	NTB_WIDTH_4 = 4,
	NTB_WIDTH_8 = 8,
	NTB_WIDTH_12 = 12,
	NTB_WIDTH_16 = 16,
	NTB_WIDTH_32 = 32,
पूर्ण;

/**
 * क्रमागत ntb_शेष_port - NTB शेष port number
 * @NTB_PORT_PRI_USD:	Default port of the NTB_TOPO_PRI/NTB_TOPO_B2B_USD
 *			topologies
 * @NTB_PORT_SEC_DSD:	Default port of the NTB_TOPO_SEC/NTB_TOPO_B2B_DSD
 *			topologies
 */
क्रमागत ntb_शेष_port अणु
	NTB_PORT_PRI_USD,
	NTB_PORT_SEC_DSD
पूर्ण;
#घोषणा NTB_DEF_PEER_CNT	(1)
#घोषणा NTB_DEF_PEER_IDX	(0)

/**
 * काष्ठा ntb_client_ops - ntb client operations
 * @probe:		Notअगरy client of a new device.
 * @हटाओ:		Notअगरy client to हटाओ a device.
 */
काष्ठा ntb_client_ops अणु
	पूर्णांक (*probe)(काष्ठा ntb_client *client, काष्ठा ntb_dev *ntb);
	व्योम (*हटाओ)(काष्ठा ntb_client *client, काष्ठा ntb_dev *ntb);
पूर्ण;

अटल अंतरभूत पूर्णांक ntb_client_ops_is_valid(स्थिर काष्ठा ntb_client_ops *ops)
अणु
	/* commented callbacks are not required: */
	वापस
		ops->probe			&&
		ops->हटाओ			&&
		1;
पूर्ण

/**
 * काष्ठा ntb_ctx_ops - ntb driver context operations
 * @link_event:		See ntb_link_event().
 * @db_event:		See ntb_db_event().
 * @msg_event:		See ntb_msg_event().
 */
काष्ठा ntb_ctx_ops अणु
	व्योम (*link_event)(व्योम *ctx);
	व्योम (*db_event)(व्योम *ctx, पूर्णांक db_vector);
	व्योम (*msg_event)(व्योम *ctx);
पूर्ण;

अटल अंतरभूत पूर्णांक ntb_ctx_ops_is_valid(स्थिर काष्ठा ntb_ctx_ops *ops)
अणु
	/* commented callbacks are not required: */
	वापस
		/* ops->link_event		&& */
		/* ops->db_event		&& */
		/* ops->msg_event		&& */
		1;
पूर्ण

/**
 * काष्ठा ntb_dev_ops - ntb device operations
 * @port_number:	See ntb_port_number().
 * @peer_port_count:	See ntb_peer_port_count().
 * @peer_port_number:	See ntb_peer_port_number().
 * @peer_port_idx:	See ntb_peer_port_idx().
 * @link_is_up:		See ntb_link_is_up().
 * @link_enable:	See ntb_link_enable().
 * @link_disable:	See ntb_link_disable().
 * @mw_count:		See ntb_mw_count().
 * @mw_get_align:	See ntb_mw_get_align().
 * @mw_set_trans:	See ntb_mw_set_trans().
 * @mw_clear_trans:	See ntb_mw_clear_trans().
 * @peer_mw_count:	See ntb_peer_mw_count().
 * @peer_mw_get_addr:	See ntb_peer_mw_get_addr().
 * @peer_mw_set_trans:	See ntb_peer_mw_set_trans().
 * @peer_mw_clear_trans:See ntb_peer_mw_clear_trans().
 * @db_is_unsafe:	See ntb_db_is_unsafe().
 * @db_valid_mask:	See ntb_db_valid_mask().
 * @db_vector_count:	See ntb_db_vector_count().
 * @db_vector_mask:	See ntb_db_vector_mask().
 * @db_पढ़ो:		See ntb_db_पढ़ो().
 * @db_set:		See ntb_db_set().
 * @db_clear:		See ntb_db_clear().
 * @db_पढ़ो_mask:	See ntb_db_पढ़ो_mask().
 * @db_set_mask:	See ntb_db_set_mask().
 * @db_clear_mask:	See ntb_db_clear_mask().
 * @peer_db_addr:	See ntb_peer_db_addr().
 * @peer_db_पढ़ो:	See ntb_peer_db_पढ़ो().
 * @peer_db_set:	See ntb_peer_db_set().
 * @peer_db_clear:	See ntb_peer_db_clear().
 * @peer_db_पढ़ो_mask:	See ntb_peer_db_पढ़ो_mask().
 * @peer_db_set_mask:	See ntb_peer_db_set_mask().
 * @peer_db_clear_mask:	See ntb_peer_db_clear_mask().
 * @spad_is_unsafe:	See ntb_spad_is_unsafe().
 * @spad_count:		See ntb_spad_count().
 * @spad_पढ़ो:		See ntb_spad_पढ़ो().
 * @spad_ग_लिखो:		See ntb_spad_ग_लिखो().
 * @peer_spad_addr:	See ntb_peer_spad_addr().
 * @peer_spad_पढ़ो:	See ntb_peer_spad_पढ़ो().
 * @peer_spad_ग_लिखो:	See ntb_peer_spad_ग_लिखो().
 * @msg_count:		See ntb_msg_count().
 * @msg_inbits:		See ntb_msg_inbits().
 * @msg_outbits:	See ntb_msg_outbits().
 * @msg_पढ़ो_sts:	See ntb_msg_पढ़ो_sts().
 * @msg_clear_sts:	See ntb_msg_clear_sts().
 * @msg_set_mask:	See ntb_msg_set_mask().
 * @msg_clear_mask:	See ntb_msg_clear_mask().
 * @msg_पढ़ो:		See ntb_msg_पढ़ो().
 * @peer_msg_ग_लिखो:	See ntb_peer_msg_ग_लिखो().
 */
काष्ठा ntb_dev_ops अणु
	पूर्णांक (*port_number)(काष्ठा ntb_dev *ntb);
	पूर्णांक (*peer_port_count)(काष्ठा ntb_dev *ntb);
	पूर्णांक (*peer_port_number)(काष्ठा ntb_dev *ntb, पूर्णांक pidx);
	पूर्णांक (*peer_port_idx)(काष्ठा ntb_dev *ntb, पूर्णांक port);

	u64 (*link_is_up)(काष्ठा ntb_dev *ntb,
			  क्रमागत ntb_speed *speed, क्रमागत ntb_width *width);
	पूर्णांक (*link_enable)(काष्ठा ntb_dev *ntb,
			   क्रमागत ntb_speed max_speed, क्रमागत ntb_width max_width);
	पूर्णांक (*link_disable)(काष्ठा ntb_dev *ntb);

	पूर्णांक (*mw_count)(काष्ठा ntb_dev *ntb, पूर्णांक pidx);
	पूर्णांक (*mw_get_align)(काष्ठा ntb_dev *ntb, पूर्णांक pidx, पूर्णांक widx,
			    resource_माप_प्रकार *addr_align,
			    resource_माप_प्रकार *size_align,
			    resource_माप_प्रकार *size_max);
	पूर्णांक (*mw_set_trans)(काष्ठा ntb_dev *ntb, पूर्णांक pidx, पूर्णांक widx,
			    dma_addr_t addr, resource_माप_प्रकार size);
	पूर्णांक (*mw_clear_trans)(काष्ठा ntb_dev *ntb, पूर्णांक pidx, पूर्णांक widx);
	पूर्णांक (*peer_mw_count)(काष्ठा ntb_dev *ntb);
	पूर्णांक (*peer_mw_get_addr)(काष्ठा ntb_dev *ntb, पूर्णांक widx,
				phys_addr_t *base, resource_माप_प्रकार *size);
	पूर्णांक (*peer_mw_set_trans)(काष्ठा ntb_dev *ntb, पूर्णांक pidx, पूर्णांक widx,
				 u64 addr, resource_माप_प्रकार size);
	पूर्णांक (*peer_mw_clear_trans)(काष्ठा ntb_dev *ntb, पूर्णांक pidx, पूर्णांक widx);

	पूर्णांक (*db_is_unsafe)(काष्ठा ntb_dev *ntb);
	u64 (*db_valid_mask)(काष्ठा ntb_dev *ntb);
	पूर्णांक (*db_vector_count)(काष्ठा ntb_dev *ntb);
	u64 (*db_vector_mask)(काष्ठा ntb_dev *ntb, पूर्णांक db_vector);

	u64 (*db_पढ़ो)(काष्ठा ntb_dev *ntb);
	पूर्णांक (*db_set)(काष्ठा ntb_dev *ntb, u64 db_bits);
	पूर्णांक (*db_clear)(काष्ठा ntb_dev *ntb, u64 db_bits);

	u64 (*db_पढ़ो_mask)(काष्ठा ntb_dev *ntb);
	पूर्णांक (*db_set_mask)(काष्ठा ntb_dev *ntb, u64 db_bits);
	पूर्णांक (*db_clear_mask)(काष्ठा ntb_dev *ntb, u64 db_bits);

	पूर्णांक (*peer_db_addr)(काष्ठा ntb_dev *ntb,
			    phys_addr_t *db_addr, resource_माप_प्रकार *db_size,
				u64 *db_data, पूर्णांक db_bit);
	u64 (*peer_db_पढ़ो)(काष्ठा ntb_dev *ntb);
	पूर्णांक (*peer_db_set)(काष्ठा ntb_dev *ntb, u64 db_bits);
	पूर्णांक (*peer_db_clear)(काष्ठा ntb_dev *ntb, u64 db_bits);

	u64 (*peer_db_पढ़ो_mask)(काष्ठा ntb_dev *ntb);
	पूर्णांक (*peer_db_set_mask)(काष्ठा ntb_dev *ntb, u64 db_bits);
	पूर्णांक (*peer_db_clear_mask)(काष्ठा ntb_dev *ntb, u64 db_bits);

	पूर्णांक (*spad_is_unsafe)(काष्ठा ntb_dev *ntb);
	पूर्णांक (*spad_count)(काष्ठा ntb_dev *ntb);

	u32 (*spad_पढ़ो)(काष्ठा ntb_dev *ntb, पूर्णांक sidx);
	पूर्णांक (*spad_ग_लिखो)(काष्ठा ntb_dev *ntb, पूर्णांक sidx, u32 val);

	पूर्णांक (*peer_spad_addr)(काष्ठा ntb_dev *ntb, पूर्णांक pidx, पूर्णांक sidx,
			      phys_addr_t *spad_addr);
	u32 (*peer_spad_पढ़ो)(काष्ठा ntb_dev *ntb, पूर्णांक pidx, पूर्णांक sidx);
	पूर्णांक (*peer_spad_ग_लिखो)(काष्ठा ntb_dev *ntb, पूर्णांक pidx, पूर्णांक sidx,
			       u32 val);

	पूर्णांक (*msg_count)(काष्ठा ntb_dev *ntb);
	u64 (*msg_inbits)(काष्ठा ntb_dev *ntb);
	u64 (*msg_outbits)(काष्ठा ntb_dev *ntb);
	u64 (*msg_पढ़ो_sts)(काष्ठा ntb_dev *ntb);
	पूर्णांक (*msg_clear_sts)(काष्ठा ntb_dev *ntb, u64 sts_bits);
	पूर्णांक (*msg_set_mask)(काष्ठा ntb_dev *ntb, u64 mask_bits);
	पूर्णांक (*msg_clear_mask)(काष्ठा ntb_dev *ntb, u64 mask_bits);
	u32 (*msg_पढ़ो)(काष्ठा ntb_dev *ntb, पूर्णांक *pidx, पूर्णांक midx);
	पूर्णांक (*peer_msg_ग_लिखो)(काष्ठा ntb_dev *ntb, पूर्णांक pidx, पूर्णांक midx, u32 msg);
पूर्ण;

अटल अंतरभूत पूर्णांक ntb_dev_ops_is_valid(स्थिर काष्ठा ntb_dev_ops *ops)
अणु
	/* commented callbacks are not required: */
	वापस
		/* Port operations are required क्रम multiport devices */
		!ops->peer_port_count == !ops->port_number	&&
		!ops->peer_port_number == !ops->port_number	&&
		!ops->peer_port_idx == !ops->port_number	&&

		/* Link operations are required */
		ops->link_is_up				&&
		ops->link_enable			&&
		ops->link_disable			&&

		/* One or both MW पूर्णांकerfaces should be developed */
		ops->mw_count				&&
		ops->mw_get_align			&&
		(ops->mw_set_trans			||
		 ops->peer_mw_set_trans)		&&
		/* ops->mw_clear_trans			&& */
		ops->peer_mw_count			&&
		ops->peer_mw_get_addr			&&
		/* ops->peer_mw_clear_trans		&& */

		/* Doorbell operations are mostly required */
		/* ops->db_is_unsafe			&& */
		ops->db_valid_mask			&&
		/* both set, or both unset */
		(!ops->db_vector_count == !ops->db_vector_mask)	&&
		ops->db_पढ़ो				&&
		/* ops->db_set				&& */
		ops->db_clear				&&
		/* ops->db_पढ़ो_mask			&& */
		ops->db_set_mask			&&
		ops->db_clear_mask			&&
		/* ops->peer_db_addr			&& */
		/* ops->peer_db_पढ़ो			&& */
		ops->peer_db_set			&&
		/* ops->peer_db_clear			&& */
		/* ops->peer_db_पढ़ो_mask		&& */
		/* ops->peer_db_set_mask		&& */
		/* ops->peer_db_clear_mask		&& */

		/* Scrachpads पूर्णांकerface is optional */
		/* !ops->spad_is_unsafe == !ops->spad_count	&& */
		!ops->spad_पढ़ो == !ops->spad_count		&&
		!ops->spad_ग_लिखो == !ops->spad_count		&&
		/* !ops->peer_spad_addr == !ops->spad_count	&& */
		/* !ops->peer_spad_पढ़ो == !ops->spad_count	&& */
		!ops->peer_spad_ग_लिखो == !ops->spad_count	&&

		/* Messaging पूर्णांकerface is optional */
		!ops->msg_inbits == !ops->msg_count		&&
		!ops->msg_outbits == !ops->msg_count		&&
		!ops->msg_पढ़ो_sts == !ops->msg_count		&&
		!ops->msg_clear_sts == !ops->msg_count		&&
		/* !ops->msg_set_mask == !ops->msg_count	&& */
		/* !ops->msg_clear_mask == !ops->msg_count	&& */
		!ops->msg_पढ़ो == !ops->msg_count		&&
		!ops->peer_msg_ग_लिखो == !ops->msg_count		&&
		1;
पूर्ण

/**
 * काष्ठा ntb_client - client पूर्णांकerested in ntb devices
 * @drv:		Linux driver object.
 * @ops:		See &ntb_client_ops.
 */
काष्ठा ntb_client अणु
	काष्ठा device_driver		drv;
	स्थिर काष्ठा ntb_client_ops	ops;
पूर्ण;
#घोषणा drv_ntb_client(__drv) container_of((__drv), काष्ठा ntb_client, drv)

/**
 * काष्ठा ntb_dev - ntb device
 * @dev:		Linux device object.
 * @pdev:		PCI device entry of the ntb.
 * @topo:		Detected topology of the ntb.
 * @ops:		See &ntb_dev_ops.
 * @ctx:		See &ntb_ctx_ops.
 * @ctx_ops:		See &ntb_ctx_ops.
 */
काष्ठा ntb_dev अणु
	काष्ठा device			dev;
	काष्ठा pci_dev			*pdev;
	क्रमागत ntb_topo			topo;
	स्थिर काष्ठा ntb_dev_ops	*ops;
	व्योम				*ctx;
	स्थिर काष्ठा ntb_ctx_ops	*ctx_ops;

	/* निजी: */

	/* synchronize setting, clearing, and calling ctx_ops */
	spinlock_t			ctx_lock;
	/* block unरेजिस्टर until device is fully released */
	काष्ठा completion		released;

#अगर_घोषित CONFIG_NTB_MSI
	काष्ठा ntb_msi *msi;
#पूर्ण_अगर
पूर्ण;
#घोषणा dev_ntb(__dev) container_of((__dev), काष्ठा ntb_dev, dev)

/**
 * ntb_रेजिस्टर_client() - रेजिस्टर a client क्रम पूर्णांकerest in ntb devices
 * @client:	Client context.
 *
 * The client will be added to the list of clients पूर्णांकerested in ntb devices.
 * The client will be notअगरied of any ntb devices that are not alपढ़ोy
 * associated with a client, or अगर ntb devices are रेजिस्टरed later.
 *
 * Return: Zero अगर the client is रेजिस्टरed, otherwise an error number.
 */
#घोषणा ntb_रेजिस्टर_client(client) \
	__ntb_रेजिस्टर_client((client), THIS_MODULE, KBUILD_MODNAME)

पूर्णांक __ntb_रेजिस्टर_client(काष्ठा ntb_client *client, काष्ठा module *mod,
			  स्थिर अक्षर *mod_name);

/**
 * ntb_unरेजिस्टर_client() - unरेजिस्टर a client क्रम पूर्णांकerest in ntb devices
 * @client:	Client context.
 *
 * The client will be हटाओd from the list of clients पूर्णांकerested in ntb
 * devices.  If any ntb devices are associated with the client, the client will
 * be notअगरied to हटाओ those devices.
 */
व्योम ntb_unरेजिस्टर_client(काष्ठा ntb_client *client);

#घोषणा module_ntb_client(__ntb_client) \
	module_driver(__ntb_client, ntb_रेजिस्टर_client, \
			ntb_unरेजिस्टर_client)

/**
 * ntb_रेजिस्टर_device() - रेजिस्टर a ntb device
 * @ntb:	NTB device context.
 *
 * The device will be added to the list of ntb devices.  If any clients are
 * पूर्णांकerested in ntb devices, each client will be notअगरied of the ntb device,
 * until at most one client accepts the device.
 *
 * Return: Zero अगर the device is रेजिस्टरed, otherwise an error number.
 */
पूर्णांक ntb_रेजिस्टर_device(काष्ठा ntb_dev *ntb);

/**
 * ntb_unरेजिस्टर_device() - unरेजिस्टर a ntb device
 * @ntb:	NTB device context.
 *
 * The device will be हटाओd from the list of ntb devices.  If the ntb device
 * is associated with a client, the client will be notअगरied to हटाओ the
 * device.
 */
व्योम ntb_unरेजिस्टर_device(काष्ठा ntb_dev *ntb);

/**
 * ntb_set_ctx() - associate a driver context with an ntb device
 * @ntb:	NTB device context.
 * @ctx:	Driver context.
 * @ctx_ops:	Driver context operations.
 *
 * Associate a driver context and operations with a ntb device.  The context is
 * provided by the client driver, and the driver may associate a dअगरferent
 * context with each ntb device.
 *
 * Return: Zero अगर the context is associated, otherwise an error number.
 */
पूर्णांक ntb_set_ctx(काष्ठा ntb_dev *ntb, व्योम *ctx,
		स्थिर काष्ठा ntb_ctx_ops *ctx_ops);

/**
 * ntb_clear_ctx() - disassociate any driver context from an ntb device
 * @ntb:	NTB device context.
 *
 * Clear any association that may exist between a driver context and the ntb
 * device.
 */
व्योम ntb_clear_ctx(काष्ठा ntb_dev *ntb);

/**
 * ntb_link_event() - notअगरy driver context of a change in link status
 * @ntb:	NTB device context.
 *
 * Notअगरy the driver context that the link status may have changed.  The driver
 * should call ntb_link_is_up() to get the current status.
 */
व्योम ntb_link_event(काष्ठा ntb_dev *ntb);

/**
 * ntb_db_event() - notअगरy driver context of a करोorbell event
 * @ntb:	NTB device context.
 * @vector:	Interrupt vector number.
 *
 * Notअगरy the driver context of a करोorbell event.  If hardware supports
 * multiple पूर्णांकerrupt vectors क्रम करोorbells, the vector number indicates which
 * vector received the पूर्णांकerrupt.  The vector number is relative to the first
 * vector used क्रम करोorbells, starting at zero, and must be less than
 * ntb_db_vector_count().  The driver may call ntb_db_पढ़ो() to check which
 * करोorbell bits need service, and ntb_db_vector_mask() to determine which of
 * those bits are associated with the vector number.
 */
व्योम ntb_db_event(काष्ठा ntb_dev *ntb, पूर्णांक vector);

/**
 * ntb_msg_event() - notअगरy driver context of a message event
 * @ntb:	NTB device context.
 *
 * Notअगरy the driver context of a message event.  If hardware supports
 * message रेजिस्टरs, this event indicates, that a new message arrived in
 * some incoming message रेजिस्टर or last sent message couldn't be delivered.
 * The events can be masked/unmasked by the methods ntb_msg_set_mask() and
 * ntb_msg_clear_mask().
 */
व्योम ntb_msg_event(काष्ठा ntb_dev *ntb);

/**
 * ntb_शेष_port_number() - get the शेष local port number
 * @ntb:	NTB device context.
 *
 * If hardware driver करोesn't specअगरy port_number() callback method, the NTB
 * is considered with just two ports. So this method वापसs शेष local
 * port number in compliance with topology.
 *
 * NOTE Don't call this method directly. The ntb_port_number() function should
 * be used instead.
 *
 * Return: the शेष local port number
 */
पूर्णांक ntb_शेष_port_number(काष्ठा ntb_dev *ntb);

/**
 * ntb_शेष_port_count() - get the शेष number of peer device ports
 * @ntb:	NTB device context.
 *
 * By शेष hardware driver supports just one peer device.
 *
 * NOTE Don't call this method directly. The ntb_peer_port_count() function
 * should be used instead.
 *
 * Return: the शेष number of peer ports
 */
पूर्णांक ntb_शेष_peer_port_count(काष्ठा ntb_dev *ntb);

/**
 * ntb_शेष_peer_port_number() - get the शेष peer port by given index
 * @ntb:	NTB device context.
 * @idx:	Peer port index (should not dअगरfer from zero).
 *
 * By शेष hardware driver supports just one peer device, so this method
 * shall वापस the corresponding value from क्रमागत ntb_शेष_port.
 *
 * NOTE Don't call this method directly. The ntb_peer_port_number() function
 * should be used instead.
 *
 * Return: the peer device port or negative value indicating an error
 */
पूर्णांक ntb_शेष_peer_port_number(काष्ठा ntb_dev *ntb, पूर्णांक pidx);

/**
 * ntb_शेष_peer_port_idx() - get the शेष peer device port index by
 *				 given port number
 * @ntb:	NTB device context.
 * @port:	Peer port number (should be one of क्रमागत ntb_शेष_port).
 *
 * By शेष hardware driver supports just one peer device, so जबतक
 * specअगरied port-argument indicates peer port from क्रमागत ntb_शेष_port,
 * the वापस value shall be zero.
 *
 * NOTE Don't call this method directly. The ntb_peer_port_idx() function
 * should be used instead.
 *
 * Return: the peer port index or negative value indicating an error
 */
पूर्णांक ntb_शेष_peer_port_idx(काष्ठा ntb_dev *ntb, पूर्णांक port);

/**
 * ntb_port_number() - get the local port number
 * @ntb:	NTB device context.
 *
 * Hardware must support at least simple two-ports ntb connection
 *
 * Return: the local port number
 */
अटल अंतरभूत पूर्णांक ntb_port_number(काष्ठा ntb_dev *ntb)
अणु
	अगर (!ntb->ops->port_number)
		वापस ntb_शेष_port_number(ntb);

	वापस ntb->ops->port_number(ntb);
पूर्ण
/**
 * ntb_peer_port_count() - get the number of peer device ports
 * @ntb:	NTB device context.
 *
 * Hardware may support an access to memory of several remote करोमुख्यs
 * over multi-port NTB devices. This method वापसs the number of peers,
 * local device can have shared memory with.
 *
 * Return: the number of peer ports
 */
अटल अंतरभूत पूर्णांक ntb_peer_port_count(काष्ठा ntb_dev *ntb)
अणु
	अगर (!ntb->ops->peer_port_count)
		वापस ntb_शेष_peer_port_count(ntb);

	वापस ntb->ops->peer_port_count(ntb);
पूर्ण

/**
 * ntb_peer_port_number() - get the peer port by given index
 * @ntb:	NTB device context.
 * @pidx:	Peer port index.
 *
 * Peer ports are continuously क्रमागतerated by NTB API logic, so this method
 * lets to retrieve port real number by its index.
 *
 * Return: the peer device port or negative value indicating an error
 */
अटल अंतरभूत पूर्णांक ntb_peer_port_number(काष्ठा ntb_dev *ntb, पूर्णांक pidx)
अणु
	अगर (!ntb->ops->peer_port_number)
		वापस ntb_शेष_peer_port_number(ntb, pidx);

	वापस ntb->ops->peer_port_number(ntb, pidx);
पूर्ण

/**
 * ntb_logical_port_number() - get the logical port number of the local port
 * @ntb:	NTB device context.
 *
 * The Logical Port Number is defined to be a unique number क्रम each
 * port starting from zero through to the number of ports minus one.
 * This is in contrast to the Port Number where each port can be asचिन्हित
 * any unique physical number by the hardware.
 *
 * The logical port number is useful क्रम calculating the resource indexes
 * used by peers.
 *
 * Return: the logical port number or negative value indicating an error
 */
अटल अंतरभूत पूर्णांक ntb_logical_port_number(काष्ठा ntb_dev *ntb)
अणु
	पूर्णांक lport = ntb_port_number(ntb);
	पूर्णांक pidx;

	अगर (lport < 0)
		वापस lport;

	क्रम (pidx = 0; pidx < ntb_peer_port_count(ntb); pidx++)
		अगर (lport <= ntb_peer_port_number(ntb, pidx))
			वापस pidx;

	वापस pidx;
पूर्ण

/**
 * ntb_peer_logical_port_number() - get the logical peer port by given index
 * @ntb:	NTB device context.
 * @pidx:	Peer port index.
 *
 * The Logical Port Number is defined to be a unique number क्रम each
 * port starting from zero through to the number of ports minus one.
 * This is in contrast to the Port Number where each port can be asचिन्हित
 * any unique physical number by the hardware.
 *
 * The logical port number is useful क्रम calculating the resource indexes
 * used by peers.
 *
 * Return: the peer's logical port number or negative value indicating an error
 */
अटल अंतरभूत पूर्णांक ntb_peer_logical_port_number(काष्ठा ntb_dev *ntb, पूर्णांक pidx)
अणु
	अगर (ntb_peer_port_number(ntb, pidx) < ntb_port_number(ntb))
		वापस pidx;
	अन्यथा
		वापस pidx + 1;
पूर्ण

/**
 * ntb_peer_port_idx() - get the peer device port index by given port number
 * @ntb:	NTB device context.
 * @port:	Peer port number.
 *
 * Inverse operation of ntb_peer_port_number(), so one can get port index
 * by specअगरied port number.
 *
 * Return: the peer port index or negative value indicating an error
 */
अटल अंतरभूत पूर्णांक ntb_peer_port_idx(काष्ठा ntb_dev *ntb, पूर्णांक port)
अणु
	अगर (!ntb->ops->peer_port_idx)
		वापस ntb_शेष_peer_port_idx(ntb, port);

	वापस ntb->ops->peer_port_idx(ntb, port);
पूर्ण

/**
 * ntb_link_is_up() - get the current ntb link state
 * @ntb:	NTB device context.
 * @speed:	OUT - The link speed expressed as PCIe generation number.
 * @width:	OUT - The link width expressed as the number of PCIe lanes.
 *
 * Get the current state of the ntb link.  It is recommended to query the link
 * state once after every link event.  It is safe to query the link state in
 * the context of the link event callback.
 *
 * Return: bitfield of indexed ports link state: bit is set/cleared अगर the
 *         link is up/करोwn respectively.
 */
अटल अंतरभूत u64 ntb_link_is_up(काष्ठा ntb_dev *ntb,
				 क्रमागत ntb_speed *speed, क्रमागत ntb_width *width)
अणु
	वापस ntb->ops->link_is_up(ntb, speed, width);
पूर्ण

/**
 * ntb_link_enable() - enable the local port ntb connection
 * @ntb:	NTB device context.
 * @max_speed:	The maximum link speed expressed as PCIe generation number.
 * @max_width:	The maximum link width expressed as the number of PCIe lanes.
 *
 * Enable the NTB/PCIe link on the local or remote (क्रम bridge-to-bridge
 * topology) side of the bridge. If it's supported the ntb device should train
 * the link to its maximum speed and width, or the requested speed and width,
 * whichever is smaller. Some hardware करोesn't support PCIe link training, so
 * the last two arguments will be ignored then.
 *
 * Return: Zero on success, otherwise an error number.
 */
अटल अंतरभूत पूर्णांक ntb_link_enable(काष्ठा ntb_dev *ntb,
				  क्रमागत ntb_speed max_speed,
				  क्रमागत ntb_width max_width)
अणु
	वापस ntb->ops->link_enable(ntb, max_speed, max_width);
पूर्ण

/**
 * ntb_link_disable() - disable the local port ntb connection
 * @ntb:	NTB device context.
 *
 * Disable the link on the local or remote (क्रम b2b topology) of the ntb.
 * The ntb device should disable the link.  Returning from this call must
 * indicate that a barrier has passed, though with no more ग_लिखोs may pass in
 * either direction across the link, except अगर this call वापसs an error
 * number.
 *
 * Return: Zero on success, otherwise an error number.
 */
अटल अंतरभूत पूर्णांक ntb_link_disable(काष्ठा ntb_dev *ntb)
अणु
	वापस ntb->ops->link_disable(ntb);
पूर्ण

/**
 * ntb_mw_count() - get the number of inbound memory winकरोws, which could
 *                  be created क्रम a specअगरied peer device
 * @ntb:	NTB device context.
 * @pidx:	Port index of peer device.
 *
 * Hardware and topology may support a dअगरferent number of memory winकरोws.
 * Moreover dअगरferent peer devices can support dअगरferent number of memory
 * winकरोws. Simply speaking this method वापसs the number of possible inbound
 * memory winकरोws to share with specअगरied peer device. Note: this may वापस
 * zero अगर the link is not up yet.
 *
 * Return: the number of memory winकरोws.
 */
अटल अंतरभूत पूर्णांक ntb_mw_count(काष्ठा ntb_dev *ntb, पूर्णांक pidx)
अणु
	वापस ntb->ops->mw_count(ntb, pidx);
पूर्ण

/**
 * ntb_mw_get_align() - get the restriction parameters of inbound memory winकरोw
 * @ntb:	NTB device context.
 * @pidx:	Port index of peer device.
 * @widx:	Memory winकरोw index.
 * @addr_align:	OUT - the base alignment क्रम translating the memory winकरोw
 * @size_align:	OUT - the size alignment क्रम translating the memory winकरोw
 * @size_max:	OUT - the maximum size of the memory winकरोw
 *
 * Get the alignments of an inbound memory winकरोw with specअगरied index.
 * शून्य may be given क्रम any output parameter अगर the value is not needed.
 * The alignment and size parameters may be used क्रम allocation of proper
 * shared memory. Note: this must only be called when the link is up.
 *
 * Return: Zero on success, otherwise a negative error number.
 */
अटल अंतरभूत पूर्णांक ntb_mw_get_align(काष्ठा ntb_dev *ntb, पूर्णांक pidx, पूर्णांक widx,
				   resource_माप_प्रकार *addr_align,
				   resource_माप_प्रकार *size_align,
				   resource_माप_प्रकार *size_max)
अणु
	अगर (!(ntb_link_is_up(ntb, शून्य, शून्य) & BIT_ULL(pidx)))
		वापस -ENOTCONN;

	वापस ntb->ops->mw_get_align(ntb, pidx, widx, addr_align, size_align,
				      size_max);
पूर्ण

/**
 * ntb_mw_set_trans() - set the translation of an inbound memory winकरोw
 * @ntb:	NTB device context.
 * @pidx:	Port index of peer device.
 * @widx:	Memory winकरोw index.
 * @addr:	The dma address of local memory to expose to the peer.
 * @size:	The size of the local memory to expose to the peer.
 *
 * Set the translation of a memory winकरोw.  The peer may access local memory
 * through the winकरोw starting at the address, up to the size.  The address
 * and size must be aligned in compliance with restrictions of
 * ntb_mw_get_align(). The region size should not exceed the size_max parameter
 * of that method.
 *
 * This method may not be implemented due to the hardware specअगरic memory
 * winकरोws पूर्णांकerface.
 *
 * Return: Zero on success, otherwise an error number.
 */
अटल अंतरभूत पूर्णांक ntb_mw_set_trans(काष्ठा ntb_dev *ntb, पूर्णांक pidx, पूर्णांक widx,
				   dma_addr_t addr, resource_माप_प्रकार size)
अणु
	अगर (!ntb->ops->mw_set_trans)
		वापस 0;

	वापस ntb->ops->mw_set_trans(ntb, pidx, widx, addr, size);
पूर्ण

/**
 * ntb_mw_clear_trans() - clear the translation address of an inbound memory
 *                        winकरोw
 * @ntb:	NTB device context.
 * @pidx:	Port index of peer device.
 * @widx:	Memory winकरोw index.
 *
 * Clear the translation of an inbound memory winकरोw.  The peer may no दीर्घer
 * access local memory through the winकरोw.
 *
 * Return: Zero on success, otherwise an error number.
 */
अटल अंतरभूत पूर्णांक ntb_mw_clear_trans(काष्ठा ntb_dev *ntb, पूर्णांक pidx, पूर्णांक widx)
अणु
	अगर (!ntb->ops->mw_clear_trans)
		वापस ntb_mw_set_trans(ntb, pidx, widx, 0, 0);

	वापस ntb->ops->mw_clear_trans(ntb, pidx, widx);
पूर्ण

/**
 * ntb_peer_mw_count() - get the number of outbound memory winकरोws, which could
 *                       be mapped to access a shared memory
 * @ntb:	NTB device context.
 *
 * Hardware and topology may support a dअगरferent number of memory winकरोws.
 * This method वापसs the number of outbound memory winकरोws supported by
 * local device.
 *
 * Return: the number of memory winकरोws.
 */
अटल अंतरभूत पूर्णांक ntb_peer_mw_count(काष्ठा ntb_dev *ntb)
अणु
	वापस ntb->ops->peer_mw_count(ntb);
पूर्ण

/**
 * ntb_peer_mw_get_addr() - get map address of an outbound memory winकरोw
 * @ntb:	NTB device context.
 * @widx:	Memory winकरोw index (within ntb_peer_mw_count() वापस value).
 * @base:	OUT - the base address of mapping region.
 * @size:	OUT - the size of mapping region.
 *
 * Get base and size of memory region to map.  शून्य may be given क्रम any output
 * parameter अगर the value is not needed.  The base and size may be used क्रम
 * mapping the memory winकरोw, to access the peer memory.
 *
 * Return: Zero on success, otherwise a negative error number.
 */
अटल अंतरभूत पूर्णांक ntb_peer_mw_get_addr(काष्ठा ntb_dev *ntb, पूर्णांक widx,
				      phys_addr_t *base, resource_माप_प्रकार *size)
अणु
	वापस ntb->ops->peer_mw_get_addr(ntb, widx, base, size);
पूर्ण

/**
 * ntb_peer_mw_set_trans() - set a translation address of a memory winकरोw
 *                           retrieved from a peer device
 * @ntb:	NTB device context.
 * @pidx:	Port index of peer device the translation address received from.
 * @widx:	Memory winकरोw index.
 * @addr:	The dma address of the shared memory to access.
 * @size:	The size of the shared memory to access.
 *
 * Set the translation of an outbound memory winकरोw.  The local device may
 * access shared memory allocated by a peer device sent the address.
 *
 * This method may not be implemented due to the hardware specअगरic memory
 * winकरोws पूर्णांकerface, so a translation address can be only set on the side,
 * where shared memory (inbound memory winकरोws) is allocated.
 *
 * Return: Zero on success, otherwise an error number.
 */
अटल अंतरभूत पूर्णांक ntb_peer_mw_set_trans(काष्ठा ntb_dev *ntb, पूर्णांक pidx, पूर्णांक widx,
					u64 addr, resource_माप_प्रकार size)
अणु
	अगर (!ntb->ops->peer_mw_set_trans)
		वापस 0;

	वापस ntb->ops->peer_mw_set_trans(ntb, pidx, widx, addr, size);
पूर्ण

/**
 * ntb_peer_mw_clear_trans() - clear the translation address of an outbound
 *                             memory winकरोw
 * @ntb:	NTB device context.
 * @pidx:	Port index of peer device.
 * @widx:	Memory winकरोw index.
 *
 * Clear the translation of a outbound memory winकरोw.  The local device may no
 * दीर्घer access a shared memory through the winकरोw.
 *
 * This method may not be implemented due to the hardware specअगरic memory
 * winकरोws पूर्णांकerface.
 *
 * Return: Zero on success, otherwise an error number.
 */
अटल अंतरभूत पूर्णांक ntb_peer_mw_clear_trans(काष्ठा ntb_dev *ntb, पूर्णांक pidx,
					  पूर्णांक widx)
अणु
	अगर (!ntb->ops->peer_mw_clear_trans)
		वापस ntb_peer_mw_set_trans(ntb, pidx, widx, 0, 0);

	वापस ntb->ops->peer_mw_clear_trans(ntb, pidx, widx);
पूर्ण

/**
 * ntb_db_is_unsafe() - check अगर it is safe to use hardware करोorbell
 * @ntb:	NTB device context.
 *
 * It is possible क्रम some ntb hardware to be affected by errata.  Hardware
 * drivers can advise clients to aव्योम using करोorbells.  Clients may ignore
 * this advice, though caution is recommended.
 *
 * Return: Zero अगर it is safe to use करोorbells, or One अगर it is not safe.
 */
अटल अंतरभूत पूर्णांक ntb_db_is_unsafe(काष्ठा ntb_dev *ntb)
अणु
	अगर (!ntb->ops->db_is_unsafe)
		वापस 0;

	वापस ntb->ops->db_is_unsafe(ntb);
पूर्ण

/**
 * ntb_db_valid_mask() - get a mask of करोorbell bits supported by the ntb
 * @ntb:	NTB device context.
 *
 * Hardware may support dअगरferent number or arrangement of करोorbell bits.
 *
 * Return: A mask of करोorbell bits supported by the ntb.
 */
अटल अंतरभूत u64 ntb_db_valid_mask(काष्ठा ntb_dev *ntb)
अणु
	वापस ntb->ops->db_valid_mask(ntb);
पूर्ण

/**
 * ntb_db_vector_count() - get the number of करोorbell पूर्णांकerrupt vectors
 * @ntb:	NTB device context.
 *
 * Hardware may support dअगरferent number of पूर्णांकerrupt vectors.
 *
 * Return: The number of करोorbell पूर्णांकerrupt vectors.
 */
अटल अंतरभूत पूर्णांक ntb_db_vector_count(काष्ठा ntb_dev *ntb)
अणु
	अगर (!ntb->ops->db_vector_count)
		वापस 1;

	वापस ntb->ops->db_vector_count(ntb);
पूर्ण

/**
 * ntb_db_vector_mask() - get a mask of करोorbell bits serviced by a vector
 * @ntb:	NTB device context.
 * @vector:	Doorbell vector number.
 *
 * Each पूर्णांकerrupt vector may have a dअगरferent number or arrangement of bits.
 *
 * Return: A mask of करोorbell bits serviced by a vector.
 */
अटल अंतरभूत u64 ntb_db_vector_mask(काष्ठा ntb_dev *ntb, पूर्णांक vector)
अणु
	अगर (!ntb->ops->db_vector_mask)
		वापस ntb_db_valid_mask(ntb);

	वापस ntb->ops->db_vector_mask(ntb, vector);
पूर्ण

/**
 * ntb_db_पढ़ो() - पढ़ो the local करोorbell रेजिस्टर
 * @ntb:	NTB device context.
 *
 * Read the local करोorbell रेजिस्टर, and वापस the bits that are set.
 *
 * Return: The bits currently set in the local करोorbell रेजिस्टर.
 */
अटल अंतरभूत u64 ntb_db_पढ़ो(काष्ठा ntb_dev *ntb)
अणु
	वापस ntb->ops->db_पढ़ो(ntb);
पूर्ण

/**
 * ntb_db_set() - set bits in the local करोorbell रेजिस्टर
 * @ntb:	NTB device context.
 * @db_bits:	Doorbell bits to set.
 *
 * Set bits in the local करोorbell रेजिस्टर, which may generate a local करोorbell
 * पूर्णांकerrupt.  Bits that were alपढ़ोy set must reमुख्य set.
 *
 * This is unusual, and hardware may not support it.
 *
 * Return: Zero on success, otherwise an error number.
 */
अटल अंतरभूत पूर्णांक ntb_db_set(काष्ठा ntb_dev *ntb, u64 db_bits)
अणु
	अगर (!ntb->ops->db_set)
		वापस -EINVAL;

	वापस ntb->ops->db_set(ntb, db_bits);
पूर्ण

/**
 * ntb_db_clear() - clear bits in the local करोorbell रेजिस्टर
 * @ntb:	NTB device context.
 * @db_bits:	Doorbell bits to clear.
 *
 * Clear bits in the local करोorbell रेजिस्टर, arming the bits क्रम the next
 * करोorbell.
 *
 * Return: Zero on success, otherwise an error number.
 */
अटल अंतरभूत पूर्णांक ntb_db_clear(काष्ठा ntb_dev *ntb, u64 db_bits)
अणु
	वापस ntb->ops->db_clear(ntb, db_bits);
पूर्ण

/**
 * ntb_db_पढ़ो_mask() - पढ़ो the local करोorbell mask
 * @ntb:	NTB device context.
 *
 * Read the local करोorbell mask रेजिस्टर, and वापस the bits that are set.
 *
 * This is unusual, though hardware is likely to support it.
 *
 * Return: The bits currently set in the local करोorbell mask रेजिस्टर.
 */
अटल अंतरभूत u64 ntb_db_पढ़ो_mask(काष्ठा ntb_dev *ntb)
अणु
	अगर (!ntb->ops->db_पढ़ो_mask)
		वापस 0;

	वापस ntb->ops->db_पढ़ो_mask(ntb);
पूर्ण

/**
 * ntb_db_set_mask() - set bits in the local करोorbell mask
 * @ntb:	NTB device context.
 * @db_bits:	Doorbell mask bits to set.
 *
 * Set bits in the local करोorbell mask रेजिस्टर, preventing करोorbell पूर्णांकerrupts
 * from being generated क्रम those करोorbell bits.  Bits that were alपढ़ोy set
 * must reमुख्य set.
 *
 * Return: Zero on success, otherwise an error number.
 */
अटल अंतरभूत पूर्णांक ntb_db_set_mask(काष्ठा ntb_dev *ntb, u64 db_bits)
अणु
	वापस ntb->ops->db_set_mask(ntb, db_bits);
पूर्ण

/**
 * ntb_db_clear_mask() - clear bits in the local करोorbell mask
 * @ntb:	NTB device context.
 * @db_bits:	Doorbell bits to clear.
 *
 * Clear bits in the local करोorbell mask रेजिस्टर, allowing करोorbell पूर्णांकerrupts
 * from being generated क्रम those करोorbell bits.  If a करोorbell bit is alपढ़ोy
 * set at the समय the mask is cleared, and the corresponding mask bit is
 * changed from set to clear, then the ntb driver must ensure that
 * ntb_db_event() is called.  If the hardware करोes not generate the पूर्णांकerrupt
 * on clearing the mask bit, then the driver must call ntb_db_event() anyway.
 *
 * Return: Zero on success, otherwise an error number.
 */
अटल अंतरभूत पूर्णांक ntb_db_clear_mask(काष्ठा ntb_dev *ntb, u64 db_bits)
अणु
	वापस ntb->ops->db_clear_mask(ntb, db_bits);
पूर्ण

/**
 * ntb_peer_db_addr() - address and size of the peer करोorbell रेजिस्टर
 * @ntb:	NTB device context.
 * @db_addr:	OUT - The address of the peer करोorbell रेजिस्टर.
 * @db_size:	OUT - The number of bytes to ग_लिखो the peer करोorbell रेजिस्टर.
 * @db_data:	OUT - The data of peer करोorbell रेजिस्टर
 * @db_bit:		करोor bell bit number
 *
 * Return the address of the peer करोorbell रेजिस्टर.  This may be used, क्रम
 * example, by drivers that offload memory copy operations to a dma engine.
 * The drivers may wish to ring the peer करोorbell at the completion of memory
 * copy operations.  For efficiency, and to simplअगरy ordering of operations
 * between the dma memory copies and the ringing करोorbell, the driver may
 * append one additional dma memory copy with the करोorbell रेजिस्टर as the
 * destination, after the memory copy operations.
 *
 * Return: Zero on success, otherwise an error number.
 */
अटल अंतरभूत पूर्णांक ntb_peer_db_addr(काष्ठा ntb_dev *ntb,
				   phys_addr_t *db_addr,
				   resource_माप_प्रकार *db_size,
				   u64 *db_data, पूर्णांक db_bit)
अणु
	अगर (!ntb->ops->peer_db_addr)
		वापस -EINVAL;

	वापस ntb->ops->peer_db_addr(ntb, db_addr, db_size, db_data, db_bit);
पूर्ण

/**
 * ntb_peer_db_पढ़ो() - पढ़ो the peer करोorbell रेजिस्टर
 * @ntb:	NTB device context.
 *
 * Read the peer करोorbell रेजिस्टर, and वापस the bits that are set.
 *
 * This is unusual, and hardware may not support it.
 *
 * Return: The bits currently set in the peer करोorbell रेजिस्टर.
 */
अटल अंतरभूत u64 ntb_peer_db_पढ़ो(काष्ठा ntb_dev *ntb)
अणु
	अगर (!ntb->ops->peer_db_पढ़ो)
		वापस 0;

	वापस ntb->ops->peer_db_पढ़ो(ntb);
पूर्ण

/**
 * ntb_peer_db_set() - set bits in the peer करोorbell रेजिस्टर
 * @ntb:	NTB device context.
 * @db_bits:	Doorbell bits to set.
 *
 * Set bits in the peer करोorbell रेजिस्टर, which may generate a peer करोorbell
 * पूर्णांकerrupt.  Bits that were alपढ़ोy set must reमुख्य set.
 *
 * Return: Zero on success, otherwise an error number.
 */
अटल अंतरभूत पूर्णांक ntb_peer_db_set(काष्ठा ntb_dev *ntb, u64 db_bits)
अणु
	वापस ntb->ops->peer_db_set(ntb, db_bits);
पूर्ण

/**
 * ntb_peer_db_clear() - clear bits in the peer करोorbell रेजिस्टर
 * @ntb:	NTB device context.
 * @db_bits:	Doorbell bits to clear.
 *
 * Clear bits in the peer करोorbell रेजिस्टर, arming the bits क्रम the next
 * करोorbell.
 *
 * This is unusual, and hardware may not support it.
 *
 * Return: Zero on success, otherwise an error number.
 */
अटल अंतरभूत पूर्णांक ntb_peer_db_clear(काष्ठा ntb_dev *ntb, u64 db_bits)
अणु
	अगर (!ntb->ops->db_clear)
		वापस -EINVAL;

	वापस ntb->ops->peer_db_clear(ntb, db_bits);
पूर्ण

/**
 * ntb_peer_db_पढ़ो_mask() - पढ़ो the peer करोorbell mask
 * @ntb:	NTB device context.
 *
 * Read the peer करोorbell mask रेजिस्टर, and वापस the bits that are set.
 *
 * This is unusual, and hardware may not support it.
 *
 * Return: The bits currently set in the peer करोorbell mask रेजिस्टर.
 */
अटल अंतरभूत u64 ntb_peer_db_पढ़ो_mask(काष्ठा ntb_dev *ntb)
अणु
	अगर (!ntb->ops->db_पढ़ो_mask)
		वापस 0;

	वापस ntb->ops->peer_db_पढ़ो_mask(ntb);
पूर्ण

/**
 * ntb_peer_db_set_mask() - set bits in the peer करोorbell mask
 * @ntb:	NTB device context.
 * @db_bits:	Doorbell mask bits to set.
 *
 * Set bits in the peer करोorbell mask रेजिस्टर, preventing करोorbell पूर्णांकerrupts
 * from being generated क्रम those करोorbell bits.  Bits that were alपढ़ोy set
 * must reमुख्य set.
 *
 * This is unusual, and hardware may not support it.
 *
 * Return: Zero on success, otherwise an error number.
 */
अटल अंतरभूत पूर्णांक ntb_peer_db_set_mask(काष्ठा ntb_dev *ntb, u64 db_bits)
अणु
	अगर (!ntb->ops->db_set_mask)
		वापस -EINVAL;

	वापस ntb->ops->peer_db_set_mask(ntb, db_bits);
पूर्ण

/**
 * ntb_peer_db_clear_mask() - clear bits in the peer करोorbell mask
 * @ntb:	NTB device context.
 * @db_bits:	Doorbell bits to clear.
 *
 * Clear bits in the peer करोorbell mask रेजिस्टर, allowing करोorbell पूर्णांकerrupts
 * from being generated क्रम those करोorbell bits.  If the hardware करोes not
 * generate the पूर्णांकerrupt on clearing the mask bit, then the driver should not
 * implement this function!
 *
 * This is unusual, and hardware may not support it.
 *
 * Return: Zero on success, otherwise an error number.
 */
अटल अंतरभूत पूर्णांक ntb_peer_db_clear_mask(काष्ठा ntb_dev *ntb, u64 db_bits)
अणु
	अगर (!ntb->ops->db_clear_mask)
		वापस -EINVAL;

	वापस ntb->ops->peer_db_clear_mask(ntb, db_bits);
पूर्ण

/**
 * ntb_spad_is_unsafe() - check अगर it is safe to use the hardware scratchpads
 * @ntb:	NTB device context.
 *
 * It is possible क्रम some ntb hardware to be affected by errata.  Hardware
 * drivers can advise clients to aव्योम using scratchpads.  Clients may ignore
 * this advice, though caution is recommended.
 *
 * Return: Zero अगर it is safe to use scratchpads, or One अगर it is not safe.
 */
अटल अंतरभूत पूर्णांक ntb_spad_is_unsafe(काष्ठा ntb_dev *ntb)
अणु
	अगर (!ntb->ops->spad_is_unsafe)
		वापस 0;

	वापस ntb->ops->spad_is_unsafe(ntb);
पूर्ण

/**
 * ntb_spad_count() - get the number of scratchpads
 * @ntb:	NTB device context.
 *
 * Hardware and topology may support a dअगरferent number of scratchpads.
 * Although it must be the same क्रम all ports per NTB device.
 *
 * Return: the number of scratchpads.
 */
अटल अंतरभूत पूर्णांक ntb_spad_count(काष्ठा ntb_dev *ntb)
अणु
	अगर (!ntb->ops->spad_count)
		वापस 0;

	वापस ntb->ops->spad_count(ntb);
पूर्ण

/**
 * ntb_spad_पढ़ो() - पढ़ो the local scratchpad रेजिस्टर
 * @ntb:	NTB device context.
 * @sidx:	Scratchpad index.
 *
 * Read the local scratchpad रेजिस्टर, and वापस the value.
 *
 * Return: The value of the local scratchpad रेजिस्टर.
 */
अटल अंतरभूत u32 ntb_spad_पढ़ो(काष्ठा ntb_dev *ntb, पूर्णांक sidx)
अणु
	अगर (!ntb->ops->spad_पढ़ो)
		वापस ~(u32)0;

	वापस ntb->ops->spad_पढ़ो(ntb, sidx);
पूर्ण

/**
 * ntb_spad_ग_लिखो() - ग_लिखो the local scratchpad रेजिस्टर
 * @ntb:	NTB device context.
 * @sidx:	Scratchpad index.
 * @val:	Scratchpad value.
 *
 * Write the value to the local scratchpad रेजिस्टर.
 *
 * Return: Zero on success, otherwise an error number.
 */
अटल अंतरभूत पूर्णांक ntb_spad_ग_लिखो(काष्ठा ntb_dev *ntb, पूर्णांक sidx, u32 val)
अणु
	अगर (!ntb->ops->spad_ग_लिखो)
		वापस -EINVAL;

	वापस ntb->ops->spad_ग_लिखो(ntb, sidx, val);
पूर्ण

/**
 * ntb_peer_spad_addr() - address of the peer scratchpad रेजिस्टर
 * @ntb:	NTB device context.
 * @pidx:	Port index of peer device.
 * @sidx:	Scratchpad index.
 * @spad_addr:	OUT - The address of the peer scratchpad रेजिस्टर.
 *
 * Return the address of the peer scratchpad रेजिस्टर.  This may be used, क्रम
 * example, by drivers that offload memory copy operations to a dma engine.
 *
 * Return: Zero on success, otherwise an error number.
 */
अटल अंतरभूत पूर्णांक ntb_peer_spad_addr(काष्ठा ntb_dev *ntb, पूर्णांक pidx, पूर्णांक sidx,
				     phys_addr_t *spad_addr)
अणु
	अगर (!ntb->ops->peer_spad_addr)
		वापस -EINVAL;

	वापस ntb->ops->peer_spad_addr(ntb, pidx, sidx, spad_addr);
पूर्ण

/**
 * ntb_peer_spad_पढ़ो() - पढ़ो the peer scratchpad रेजिस्टर
 * @ntb:	NTB device context.
 * @pidx:	Port index of peer device.
 * @sidx:	Scratchpad index.
 *
 * Read the peer scratchpad रेजिस्टर, and वापस the value.
 *
 * Return: The value of the peer scratchpad रेजिस्टर.
 */
अटल अंतरभूत u32 ntb_peer_spad_पढ़ो(काष्ठा ntb_dev *ntb, पूर्णांक pidx, पूर्णांक sidx)
अणु
	अगर (!ntb->ops->peer_spad_पढ़ो)
		वापस ~(u32)0;

	वापस ntb->ops->peer_spad_पढ़ो(ntb, pidx, sidx);
पूर्ण

/**
 * ntb_peer_spad_ग_लिखो() - ग_लिखो the peer scratchpad रेजिस्टर
 * @ntb:	NTB device context.
 * @pidx:	Port index of peer device.
 * @sidx:	Scratchpad index.
 * @val:	Scratchpad value.
 *
 * Write the value to the peer scratchpad रेजिस्टर.
 *
 * Return: Zero on success, otherwise an error number.
 */
अटल अंतरभूत पूर्णांक ntb_peer_spad_ग_लिखो(काष्ठा ntb_dev *ntb, पूर्णांक pidx, पूर्णांक sidx,
				      u32 val)
अणु
	अगर (!ntb->ops->peer_spad_ग_लिखो)
		वापस -EINVAL;

	वापस ntb->ops->peer_spad_ग_लिखो(ntb, pidx, sidx, val);
पूर्ण

/**
 * ntb_msg_count() - get the number of message रेजिस्टरs
 * @ntb:	NTB device context.
 *
 * Hardware may support a dअगरferent number of message रेजिस्टरs.
 *
 * Return: the number of message रेजिस्टरs.
 */
अटल अंतरभूत पूर्णांक ntb_msg_count(काष्ठा ntb_dev *ntb)
अणु
	अगर (!ntb->ops->msg_count)
		वापस 0;

	वापस ntb->ops->msg_count(ntb);
पूर्ण

/**
 * ntb_msg_inbits() - get a bitfield of inbound message रेजिस्टरs status
 * @ntb:	NTB device context.
 *
 * The method वापसs the bitfield of status and mask रेजिस्टरs, which related
 * to inbound message रेजिस्टरs.
 *
 * Return: bitfield of inbound message रेजिस्टरs.
 */
अटल अंतरभूत u64 ntb_msg_inbits(काष्ठा ntb_dev *ntb)
अणु
	अगर (!ntb->ops->msg_inbits)
		वापस 0;

	वापस ntb->ops->msg_inbits(ntb);
पूर्ण

/**
 * ntb_msg_outbits() - get a bitfield of outbound message रेजिस्टरs status
 * @ntb:	NTB device context.
 *
 * The method वापसs the bitfield of status and mask रेजिस्टरs, which related
 * to outbound message रेजिस्टरs.
 *
 * Return: bitfield of outbound message रेजिस्टरs.
 */
अटल अंतरभूत u64 ntb_msg_outbits(काष्ठा ntb_dev *ntb)
अणु
	अगर (!ntb->ops->msg_outbits)
		वापस 0;

	वापस ntb->ops->msg_outbits(ntb);
पूर्ण

/**
 * ntb_msg_पढ़ो_sts() - पढ़ो the message रेजिस्टरs status
 * @ntb:	NTB device context.
 *
 * Read the status of message रेजिस्टर. Inbound and outbound message रेजिस्टरs
 * related bits can be filtered by masks retrieved from ntb_msg_inbits() and
 * ntb_msg_outbits().
 *
 * Return: status bits of message रेजिस्टरs
 */
अटल अंतरभूत u64 ntb_msg_पढ़ो_sts(काष्ठा ntb_dev *ntb)
अणु
	अगर (!ntb->ops->msg_पढ़ो_sts)
		वापस 0;

	वापस ntb->ops->msg_पढ़ो_sts(ntb);
पूर्ण

/**
 * ntb_msg_clear_sts() - clear status bits of message रेजिस्टरs
 * @ntb:	NTB device context.
 * @sts_bits:	Status bits to clear.
 *
 * Clear bits in the status रेजिस्टर.
 *
 * Return: Zero on success, otherwise a negative error number.
 */
अटल अंतरभूत पूर्णांक ntb_msg_clear_sts(काष्ठा ntb_dev *ntb, u64 sts_bits)
अणु
	अगर (!ntb->ops->msg_clear_sts)
		वापस -EINVAL;

	वापस ntb->ops->msg_clear_sts(ntb, sts_bits);
पूर्ण

/**
 * ntb_msg_set_mask() - set mask of message रेजिस्टर status bits
 * @ntb:	NTB device context.
 * @mask_bits:	Mask bits.
 *
 * Mask the message रेजिस्टरs status bits from raising the message event.
 *
 * Return: Zero on success, otherwise a negative error number.
 */
अटल अंतरभूत पूर्णांक ntb_msg_set_mask(काष्ठा ntb_dev *ntb, u64 mask_bits)
अणु
	अगर (!ntb->ops->msg_set_mask)
		वापस -EINVAL;

	वापस ntb->ops->msg_set_mask(ntb, mask_bits);
पूर्ण

/**
 * ntb_msg_clear_mask() - clear message रेजिस्टरs mask
 * @ntb:	NTB device context.
 * @mask_bits:	Mask bits to clear.
 *
 * Clear bits in the message events mask रेजिस्टर.
 *
 * Return: Zero on success, otherwise a negative error number.
 */
अटल अंतरभूत पूर्णांक ntb_msg_clear_mask(काष्ठा ntb_dev *ntb, u64 mask_bits)
अणु
	अगर (!ntb->ops->msg_clear_mask)
		वापस -EINVAL;

	वापस ntb->ops->msg_clear_mask(ntb, mask_bits);
पूर्ण

/**
 * ntb_msg_पढ़ो() - पढ़ो inbound message रेजिस्टर with specअगरied index
 * @ntb:	NTB device context.
 * @pidx:	OUT - Port index of peer device a message retrieved from
 * @midx:	Message रेजिस्टर index
 *
 * Read data from the specअगरied message रेजिस्टर. Source port index of a
 * message is retrieved as well.
 *
 * Return: The value of the inbound message रेजिस्टर.
 */
अटल अंतरभूत u32 ntb_msg_पढ़ो(काष्ठा ntb_dev *ntb, पूर्णांक *pidx, पूर्णांक midx)
अणु
	अगर (!ntb->ops->msg_पढ़ो)
		वापस ~(u32)0;

	वापस ntb->ops->msg_पढ़ो(ntb, pidx, midx);
पूर्ण

/**
 * ntb_peer_msg_ग_लिखो() - ग_लिखो data to the specअगरied peer message रेजिस्टर
 * @ntb:	NTB device context.
 * @pidx:	Port index of peer device a message being sent to
 * @midx:	Message रेजिस्टर index
 * @msg:	Data to send
 *
 * Send data to a specअगरied peer device using the defined message रेजिस्टर.
 * Message event can be उठाओd अगर the midx रेजिस्टरs isn't empty जबतक
 * calling this method and the corresponding पूर्णांकerrupt isn't masked.
 *
 * Return: Zero on success, otherwise a negative error number.
 */
अटल अंतरभूत पूर्णांक ntb_peer_msg_ग_लिखो(काष्ठा ntb_dev *ntb, पूर्णांक pidx, पूर्णांक midx,
				     u32 msg)
अणु
	अगर (!ntb->ops->peer_msg_ग_लिखो)
		वापस -EINVAL;

	वापस ntb->ops->peer_msg_ग_लिखो(ntb, pidx, midx, msg);
पूर्ण

/**
 * ntb_peer_resource_idx() - get a resource index क्रम a given peer idx
 * @ntb:	NTB device context.
 * @pidx:	Peer port index.
 *
 * When स्थिरructing a graph of peers, each remote peer must use a dअगरferent
 * resource index (mw, करोorbell, etc) to communicate with each other
 * peer.
 *
 * In a two peer प्रणाली, this function should always वापस 0 such that
 * resource 0 poपूर्णांकs to the remote peer on both ports.
 *
 * In a 5 peer प्रणाली, this function will वापस the following matrix
 *
 * pidx \ port    0    1    2    3    4
 * 0              0    0    1    2    3
 * 1              0    1    1    2    3
 * 2              0    1    2    2    3
 * 3              0    1    2    3    3
 *
 * For example, अगर this function is used to program peer's memory
 * winकरोws, port 0 will program MW 0 on all it's peers to poपूर्णांक to itself.
 * port 1 will program MW 0 in port 0 to poपूर्णांक to itself and MW 1 on all
 * other ports. etc.
 *
 * For the legacy two host हाल, ntb_port_number() and ntb_peer_port_number()
 * both वापस zero and thereक्रमe this function will always वापस zero.
 * So MW 0 on each host would be programmed to poपूर्णांक to the other host.
 *
 * Return: the resource index to use क्रम that peer.
 */
अटल अंतरभूत पूर्णांक ntb_peer_resource_idx(काष्ठा ntb_dev *ntb, पूर्णांक pidx)
अणु
	पूर्णांक local_port, peer_port;

	अगर (pidx >= ntb_peer_port_count(ntb))
		वापस -EINVAL;

	local_port = ntb_logical_port_number(ntb);
	peer_port = ntb_peer_logical_port_number(ntb, pidx);

	अगर (peer_port < local_port)
		वापस local_port - 1;
	अन्यथा
		वापस local_port;
पूर्ण

/**
 * ntb_peer_highest_mw_idx() - get a memory winकरोw index क्रम a given peer idx
 *	using the highest index memory winकरोws first
 *
 * @ntb:	NTB device context.
 * @pidx:	Peer port index.
 *
 * Like ntb_peer_resource_idx(), except it वापसs indexes starting with
 * last memory winकरोw index.
 *
 * Return: the resource index to use क्रम that peer.
 */
अटल अंतरभूत पूर्णांक ntb_peer_highest_mw_idx(काष्ठा ntb_dev *ntb, पूर्णांक pidx)
अणु
	पूर्णांक ret;

	ret = ntb_peer_resource_idx(ntb, pidx);
	अगर (ret < 0)
		वापस ret;

	वापस ntb_mw_count(ntb, pidx) - ret - 1;
पूर्ण

काष्ठा ntb_msi_desc अणु
	u32 addr_offset;
	u32 data;
पूर्ण;

#अगर_घोषित CONFIG_NTB_MSI

पूर्णांक ntb_msi_init(काष्ठा ntb_dev *ntb, व्योम (*desc_changed)(व्योम *ctx));
पूर्णांक ntb_msi_setup_mws(काष्ठा ntb_dev *ntb);
व्योम ntb_msi_clear_mws(काष्ठा ntb_dev *ntb);
पूर्णांक ntbm_msi_request_thपढ़ोed_irq(काष्ठा ntb_dev *ntb, irq_handler_t handler,
				  irq_handler_t thपढ़ो_fn,
				  स्थिर अक्षर *name, व्योम *dev_id,
				  काष्ठा ntb_msi_desc *msi_desc);
व्योम ntbm_msi_मुक्त_irq(काष्ठा ntb_dev *ntb, अचिन्हित पूर्णांक irq, व्योम *dev_id);
पूर्णांक ntb_msi_peer_trigger(काष्ठा ntb_dev *ntb, पूर्णांक peer,
			 काष्ठा ntb_msi_desc *desc);
पूर्णांक ntb_msi_peer_addr(काष्ठा ntb_dev *ntb, पूर्णांक peer,
		      काष्ठा ntb_msi_desc *desc,
		      phys_addr_t *msi_addr);

#अन्यथा /* not CONFIG_NTB_MSI */

अटल अंतरभूत पूर्णांक ntb_msi_init(काष्ठा ntb_dev *ntb,
			       व्योम (*desc_changed)(व्योम *ctx))
अणु
	वापस -EOPNOTSUPP;
पूर्ण
अटल अंतरभूत पूर्णांक ntb_msi_setup_mws(काष्ठा ntb_dev *ntb)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
अटल अंतरभूत व्योम ntb_msi_clear_mws(काष्ठा ntb_dev *ntb) अणुपूर्ण
अटल अंतरभूत पूर्णांक ntbm_msi_request_thपढ़ोed_irq(काष्ठा ntb_dev *ntb,
						irq_handler_t handler,
						irq_handler_t thपढ़ो_fn,
						स्थिर अक्षर *name, व्योम *dev_id,
						काष्ठा ntb_msi_desc *msi_desc)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
अटल अंतरभूत व्योम ntbm_msi_मुक्त_irq(काष्ठा ntb_dev *ntb, अचिन्हित पूर्णांक irq,
				     व्योम *dev_id) अणुपूर्ण
अटल अंतरभूत पूर्णांक ntb_msi_peer_trigger(काष्ठा ntb_dev *ntb, पूर्णांक peer,
				       काष्ठा ntb_msi_desc *desc)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
अटल अंतरभूत पूर्णांक ntb_msi_peer_addr(काष्ठा ntb_dev *ntb, पूर्णांक peer,
				    काष्ठा ntb_msi_desc *desc,
				    phys_addr_t *msi_addr)
अणु
	वापस -EOPNOTSUPP;

पूर्ण

#पूर्ण_अगर /* CONFIG_NTB_MSI */

अटल अंतरभूत पूर्णांक ntbm_msi_request_irq(काष्ठा ntb_dev *ntb,
				       irq_handler_t handler,
				       स्थिर अक्षर *name, व्योम *dev_id,
				       काष्ठा ntb_msi_desc *msi_desc)
अणु
	वापस ntbm_msi_request_thपढ़ोed_irq(ntb, handler, शून्य, name,
					     dev_id, msi_desc);
पूर्ण

#पूर्ण_अगर
