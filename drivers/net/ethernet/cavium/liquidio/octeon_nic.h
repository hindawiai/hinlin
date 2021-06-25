<शैली गुरु>
/**********************************************************************
 * Author: Cavium, Inc.
 *
 * Contact: support@cavium.com
 *          Please include "LiquidIO" in the subject.
 *
 * Copyright (c) 2003-2016 Cavium, Inc.
 *
 * This file is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License, Version 2, as
 * published by the Free Software Foundation.
 *
 * This file is distributed in the hope that it will be useful, but
 * AS-IS and WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE, TITLE, or
 * NONINFRINGEMENT.  See the GNU General Public License क्रम more
 * details.
 **********************************************************************/

/*!  \पile octeon_nic.h
 *   \मrief Host NIC Driver: Routine to send network data &
 *   control packet to Octeon.
 */

#अगर_अघोषित __OCTEON_NIC_H__
#घोषणा  __OCTEON_NIC_H__

/* Maximum number of 8-byte words can be sent in a NIC control message.
 */
#घोषणा  MAX_NCTRL_UDD  32

प्रकार व्योम (*octnic_ctrl_pkt_cb_fn_t) (व्योम *);

/* Structure of control inक्रमmation passed by the NIC module to the OSI
 * layer when sending control commands to Octeon device software.
 */
काष्ठा octnic_ctrl_pkt अणु
	/** Command to be passed to the Octeon device software. */
	जोड़ octnet_cmd ncmd;

	/** Send buffer  */
	व्योम *data;
	u64 dmadata;

	/** Response buffer */
	व्योम *rdata;
	u64 dmardata;

	/** Additional data that may be needed by some commands. */
	u64 udd[MAX_NCTRL_UDD];

	/** Input queue to use to send this command. */
	u64 iq_no;

	/** The network device that issued the control command. */
	u64 netpndev;

	/** Callback function called when the command has been fetched */
	octnic_ctrl_pkt_cb_fn_t cb_fn;

	u32 sc_status;
पूर्ण;

#घोषणा MAX_UDD_SIZE(nctrl) (माप((nctrl)->udd))

/** Structure of data inक्रमmation passed by the NIC module to the OSI
 * layer when क्रमwarding data to Octeon device software.
 */
काष्ठा octnic_data_pkt अणु
	/** Poपूर्णांकer to inक्रमmation मुख्यtained by NIC module क्रम this packet. The
	 *  OSI layer passes this as-is to the driver.
	 */
	व्योम *buf;

	/** Type of buffer passed in "buf" above. */
	u32 reqtype;

	/** Total data bytes to be transferred in this command. */
	u32 datasize;

	/** Command to be passed to the Octeon device software. */
	जोड़ octeon_instr_64B cmd;

	/** Input queue to use to send this command. */
	u32 q_no;

पूर्ण;

/** Structure passed by NIC module to OSI layer to prepare a command to send
 * network data to Octeon.
 */
जोड़ octnic_cmd_setup अणु
	काष्ठा अणु
		u32 iq_no:8;
		u32 gather:1;
		u32 बारtamp:1;
		u32 ip_csum:1;
		u32 transport_csum:1;
		u32 tnl_csum:1;
		u32 rsvd:19;

		जोड़ अणु
			u32 datasize;
			u32 gatherptrs;
		पूर्ण u;
	पूर्ण s;

	u64 u64;

पूर्ण;

अटल अंतरभूत पूर्णांक octnet_iq_is_full(काष्ठा octeon_device *oct, u32 q_no)
अणु
	वापस ((u32)atomic_पढ़ो(&oct->instr_queue[q_no]->instr_pending)
		>= (oct->instr_queue[q_no]->max_count - 2));
पूर्ण

अटल अंतरभूत व्योम
octnet_prepare_pci_cmd_o2(काष्ठा octeon_device *oct,
			  जोड़ octeon_instr_64B *cmd,
			  जोड़ octnic_cmd_setup *setup, u32 tag)
अणु
	काष्ठा octeon_instr_ih2 *ih2;
	काष्ठा octeon_instr_irh *irh;
	जोड़ octnic_packet_params packet_params;
	पूर्णांक port;

	स_रखो(cmd, 0, माप(जोड़ octeon_instr_64B));

	ih2 = (काष्ठा octeon_instr_ih2 *)&cmd->cmd2.ih2;

	/* assume that rflag is cleared so thereक्रमe front data will only have
	 * irh and ossp[0], ossp[1] क्रम a total of 32 bytes
	 */
	ih2->fsz = LIO_PCICMD_O2;

	ih2->tagtype = ORDERED_TAG;
	ih2->grp = DEFAULT_POW_GRP;

	port = (पूर्णांक)oct->instr_queue[setup->s.iq_no]->txpciq.s.port;

	अगर (tag)
		ih2->tag = tag;
	अन्यथा
		ih2->tag = LIO_DATA(port);

	ih2->raw = 1;
	ih2->qos = (port & 3) + 4;	/* map qos based on पूर्णांकerface */

	अगर (!setup->s.gather) अणु
		ih2->dlengsz = setup->s.u.datasize;
	पूर्ण अन्यथा अणु
		ih2->gather = 1;
		ih2->dlengsz = setup->s.u.gatherptrs;
	पूर्ण

	irh = (काष्ठा octeon_instr_irh *)&cmd->cmd2.irh;

	irh->opcode = OPCODE_NIC;
	irh->subcode = OPCODE_NIC_NW_DATA;

	packet_params.u32 = 0;

	packet_params.s.ip_csum = setup->s.ip_csum;
	packet_params.s.transport_csum = setup->s.transport_csum;
	packet_params.s.tnl_csum = setup->s.tnl_csum;
	packet_params.s.tsflag = setup->s.बारtamp;

	irh->ossp = packet_params.u32;
पूर्ण

अटल अंतरभूत व्योम
octnet_prepare_pci_cmd_o3(काष्ठा octeon_device *oct,
			  जोड़ octeon_instr_64B *cmd,
			  जोड़ octnic_cmd_setup *setup, u32 tag)
अणु
	काष्ठा octeon_instr_irh *irh;
	काष्ठा octeon_instr_ih3     *ih3;
	काष्ठा octeon_instr_pki_ih3 *pki_ih3;
	जोड़ octnic_packet_params packet_params;
	पूर्णांक port;

	स_रखो(cmd, 0, माप(जोड़ octeon_instr_64B));

	ih3 = (काष्ठा octeon_instr_ih3 *)&cmd->cmd3.ih3;
	pki_ih3 = (काष्ठा octeon_instr_pki_ih3 *)&cmd->cmd3.pki_ih3;

	/* assume that rflag is cleared so thereक्रमe front data will only have
	 * irh and ossp[1] and ossp[2] क्रम a total of 24 bytes
	 */
	ih3->pkind       = oct->instr_queue[setup->s.iq_no]->txpciq.s.pkind;
	/*PKI IH*/
	ih3->fsz = LIO_PCICMD_O3;

	अगर (!setup->s.gather) अणु
		ih3->dlengsz = setup->s.u.datasize;
	पूर्ण अन्यथा अणु
		ih3->gather = 1;
		ih3->dlengsz = setup->s.u.gatherptrs;
	पूर्ण

	pki_ih3->w       = 1;
	pki_ih3->raw     = 1;
	pki_ih3->utag    = 1;
	pki_ih3->utt     = 1;
	pki_ih3->uqpg    = oct->instr_queue[setup->s.iq_no]->txpciq.s.use_qpg;

	port = (पूर्णांक)oct->instr_queue[setup->s.iq_no]->txpciq.s.port;

	अगर (tag)
		pki_ih3->tag = tag;
	अन्यथा
		pki_ih3->tag     = LIO_DATA(port);

	pki_ih3->tagtype = ORDERED_TAG;
	pki_ih3->qpg     = oct->instr_queue[setup->s.iq_no]->txpciq.s.qpg;
	pki_ih3->pm      = 0x7; /*0x7 - meant क्रम Parse nothing, unपूर्णांकerpreted*/
	pki_ih3->sl      = 8;   /* sl will be माप(pki_ih3)*/

	irh = (काष्ठा octeon_instr_irh *)&cmd->cmd3.irh;

	irh->opcode = OPCODE_NIC;
	irh->subcode = OPCODE_NIC_NW_DATA;

	packet_params.u32 = 0;

	packet_params.s.ip_csum = setup->s.ip_csum;
	packet_params.s.transport_csum = setup->s.transport_csum;
	packet_params.s.tnl_csum = setup->s.tnl_csum;
	packet_params.s.tsflag = setup->s.बारtamp;

	irh->ossp = packet_params.u32;
पूर्ण

/** Utility function to prepare a 64B NIC inकाष्ठाion based on a setup command
 * @param cmd - poपूर्णांकer to inकाष्ठाion to be filled in.
 * @param setup - poपूर्णांकer to the setup काष्ठाure
 * @param q_no - which queue क्रम back pressure
 *
 * Assumes the cmd inकाष्ठाion is pre-allocated, but no fields are filled in.
 */
अटल अंतरभूत व्योम
octnet_prepare_pci_cmd(काष्ठा octeon_device *oct, जोड़ octeon_instr_64B *cmd,
		       जोड़ octnic_cmd_setup *setup, u32 tag)
अणु
	अगर (OCTEON_CN6XXX(oct))
		octnet_prepare_pci_cmd_o2(oct, cmd, setup, tag);
	अन्यथा
		octnet_prepare_pci_cmd_o3(oct, cmd, setup, tag);
पूर्ण

/** Allocate and a soft command with space क्रम a response immediately following
 * the commnad.
 * @param oct - octeon device poपूर्णांकer
 * @param cmd - poपूर्णांकer to the command काष्ठाure, pre-filled क्रम everything
 * except the response.
 * @param rdatasize - size in bytes of the response.
 *
 * @वापसs poपूर्णांकer to allocated buffer with command copied पूर्णांकo it, and
 * response space immediately following.
 */
व्योम *
octeon_alloc_soft_command_resp(काष्ठा octeon_device    *oct,
			       जोड़ octeon_instr_64B *cmd,
			       u32		       rdatasize);

/** Send a NIC data packet to the device
 * @param oct - octeon device poपूर्णांकer
 * @param ndata - control काष्ठाure with queueing, and buffer inक्रमmation
 *
 * @वापसs IQ_FAILED अगर it failed to add to the input queue. IQ_STOP अगर it the
 * queue should be stopped, and IQ_SEND_OK अगर it sent okay.
 */
पूर्णांक octnet_send_nic_data_pkt(काष्ठा octeon_device *oct,
			     काष्ठा octnic_data_pkt *ndata,
			     पूर्णांक xmit_more);

/** Send a NIC control packet to the device
 * @param oct - octeon device poपूर्णांकer
 * @param nctrl - control काष्ठाure with command, timout, and callback info
 * @वापसs IQ_FAILED अगर it failed to add to the input queue. IQ_STOP अगर it the
 * queue should be stopped, and IQ_SEND_OK अगर it sent okay.
 */
पूर्णांक
octnet_send_nic_ctrl_pkt(काष्ठा octeon_device *oct,
			 काष्ठा octnic_ctrl_pkt *nctrl);

#पूर्ण_अगर
