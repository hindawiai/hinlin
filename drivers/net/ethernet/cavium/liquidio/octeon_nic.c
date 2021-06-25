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
#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश "liquidio_common.h"
#समावेश "octeon_droq.h"
#समावेश "octeon_iq.h"
#समावेश "response_manager.h"
#समावेश "octeon_device.h"
#समावेश "octeon_nic.h"
#समावेश "octeon_main.h"

व्योम *
octeon_alloc_soft_command_resp(काष्ठा octeon_device    *oct,
			       जोड़ octeon_instr_64B *cmd,
			       u32		       rdatasize)
अणु
	काष्ठा octeon_soft_command *sc;
	काष्ठा octeon_instr_ih3  *ih3;
	काष्ठा octeon_instr_ih2  *ih2;
	काष्ठा octeon_instr_irh *irh;
	काष्ठा octeon_instr_rdp *rdp;

	sc = (काष्ठा octeon_soft_command *)
		octeon_alloc_soft_command(oct, 0, rdatasize, 0);

	अगर (!sc)
		वापस शून्य;

	/* Copy existing command काष्ठाure पूर्णांकo the soft command */
	स_नकल(&sc->cmd, cmd, माप(जोड़ octeon_instr_64B));

	/* Add in the response related fields. Opcode and Param are alपढ़ोy
	 * there.
	 */
	अगर (OCTEON_CN23XX_PF(oct) || OCTEON_CN23XX_VF(oct)) अणु
		ih3      = (काष्ठा octeon_instr_ih3 *)&sc->cmd.cmd3.ih3;
		rdp     = (काष्ठा octeon_instr_rdp *)&sc->cmd.cmd3.rdp;
		irh     = (काष्ठा octeon_instr_irh *)&sc->cmd.cmd3.irh;
		/*pkiih3 + irh + ossp[0] + ossp[1] + rdp + rptr = 40 bytes */
		ih3->fsz = LIO_SOFTCMDRESP_IH3;
	पूर्ण अन्यथा अणु
		ih2      = (काष्ठा octeon_instr_ih2 *)&sc->cmd.cmd2.ih2;
		rdp     = (काष्ठा octeon_instr_rdp *)&sc->cmd.cmd2.rdp;
		irh     = (काष्ठा octeon_instr_irh *)&sc->cmd.cmd2.irh;
		/* irh + ossp[0] + ossp[1] + rdp + rptr = 40 bytes */
		ih2->fsz = LIO_SOFTCMDRESP_IH2;
	पूर्ण

	irh->rflag = 1; /* a response is required */

	rdp->pcie_port = oct->pcie_port;
	rdp->rlen      = rdatasize;

	*sc->status_word = COMPLETION_WORD_INIT;

	अगर (OCTEON_CN23XX_PF(oct) || OCTEON_CN23XX_VF(oct))
		sc->cmd.cmd3.rptr =  sc->dmarptr;
	अन्यथा
		sc->cmd.cmd2.rptr =  sc->dmarptr;

	sc->expiry_समय = jअगरfies + msecs_to_jअगरfies(LIO_SC_MAX_TMO_MS);

	वापस sc;
पूर्ण

पूर्णांक octnet_send_nic_data_pkt(काष्ठा octeon_device *oct,
			     काष्ठा octnic_data_pkt *ndata,
			     पूर्णांक xmit_more)
अणु
	पूर्णांक ring_करोorbell = !xmit_more;

	वापस octeon_send_command(oct, ndata->q_no, ring_करोorbell, &ndata->cmd,
				   ndata->buf, ndata->datasize,
				   ndata->reqtype);
पूर्ण

अटल अंतरभूत काष्ठा octeon_soft_command
*octnic_alloc_ctrl_pkt_sc(काष्ठा octeon_device *oct,
			  काष्ठा octnic_ctrl_pkt *nctrl)
अणु
	काष्ठा octeon_soft_command *sc = शून्य;
	u8 *data;
	u32 rdatasize;
	u32 uddsize = 0, datasize = 0;

	uddsize = (u32)(nctrl->ncmd.s.more * 8);

	datasize = OCTNET_CMD_SIZE + uddsize;
	rdatasize = 16;

	sc = (काष्ठा octeon_soft_command *)
		octeon_alloc_soft_command(oct, datasize, rdatasize, 0);

	अगर (!sc)
		वापस शून्य;

	data = (u8 *)sc->virtdptr;

	स_नकल(data, &nctrl->ncmd, OCTNET_CMD_SIZE);

	octeon_swap_8B_data((u64 *)data, (OCTNET_CMD_SIZE >> 3));

	अगर (uddsize) अणु
		/* Endian-Swap क्रम UDD should have been करोne by caller. */
		स_नकल(data + OCTNET_CMD_SIZE, nctrl->udd, uddsize);
	पूर्ण

	sc->iq_no = (u32)nctrl->iq_no;

	octeon_prepare_soft_command(oct, sc, OPCODE_NIC, OPCODE_NIC_CMD,
				    0, 0, 0);

	init_completion(&sc->complete);
	sc->sc_status = OCTEON_REQUEST_PENDING;

	वापस sc;
पूर्ण

पूर्णांक
octnet_send_nic_ctrl_pkt(काष्ठा octeon_device *oct,
			 काष्ठा octnic_ctrl_pkt *nctrl)
अणु
	पूर्णांक retval;
	काष्ठा octeon_soft_command *sc = शून्य;

	spin_lock_bh(&oct->cmd_resp_wqlock);
	/* Allow only rx ctrl command to stop traffic on the chip
	 * during offline operations
	 */
	अगर ((oct->cmd_resp_state == OCT_DRV_OFFLINE) &&
	    (nctrl->ncmd.s.cmd != OCTNET_CMD_RX_CTL)) अणु
		spin_unlock_bh(&oct->cmd_resp_wqlock);
		dev_err(&oct->pci_dev->dev,
			"%s cmd:%d not processed since driver offline\n",
			__func__, nctrl->ncmd.s.cmd);
		वापस -1;
	पूर्ण

	sc = octnic_alloc_ctrl_pkt_sc(oct, nctrl);
	अगर (!sc) अणु
		dev_err(&oct->pci_dev->dev, "%s soft command alloc failed\n",
			__func__);
		spin_unlock_bh(&oct->cmd_resp_wqlock);
		वापस -1;
	पूर्ण

	retval = octeon_send_soft_command(oct, sc);
	अगर (retval == IQ_SEND_FAILED) अणु
		octeon_मुक्त_soft_command(oct, sc);
		dev_err(&oct->pci_dev->dev, "%s pf_num:%d soft command:%d send failed status: %x\n",
			__func__, oct->pf_num, nctrl->ncmd.s.cmd, retval);
		spin_unlock_bh(&oct->cmd_resp_wqlock);
		वापस -1;
	पूर्ण

	spin_unlock_bh(&oct->cmd_resp_wqlock);

	अगर (nctrl->ncmd.s.cmdgroup == 0) अणु
		चयन (nctrl->ncmd.s.cmd) अणु
			/* caller holds lock, can not sleep */
		हाल OCTNET_CMD_CHANGE_DEVFLAGS:
		हाल OCTNET_CMD_SET_MULTI_LIST:
		हाल OCTNET_CMD_SET_UC_LIST:
			WRITE_ONCE(sc->caller_is_करोne, true);
			वापस retval;
		पूर्ण
	पूर्ण

	retval = रुको_क्रम_sc_completion_समयout(oct, sc, 0);
	अगर (retval)
		वापस (retval);

	nctrl->sc_status = sc->sc_status;
	retval = nctrl->sc_status;
	अगर (nctrl->cb_fn)
		nctrl->cb_fn(nctrl);

	WRITE_ONCE(sc->caller_is_करोne, true);

	वापस retval;
पूर्ण
