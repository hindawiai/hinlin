<शैली गुरु>
/*
 * This file is part of the Chelsio FCoE driver क्रम Linux.
 *
 * Copyright (c) 2008-2012 Chelsio Communications, Inc. All rights reserved.
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

#समावेश <linux/delay.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/माला.स>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_transport_fc.h>

#समावेश "csio_hw.h"
#समावेश "csio_lnode.h"
#समावेश "csio_rnode.h"
#समावेश "csio_mb.h"
#समावेश "csio_wr.h"

#घोषणा csio_mb_is_host_owner(__owner)		((__owner) == CSIO_MBOWNER_PL)

/* MB Command/Response Helpers */
/*
 * csio_mb_fw_retval - FW वापस value from a mailbox response.
 * @mbp: Mailbox काष्ठाure
 *
 */
क्रमागत fw_retval
csio_mb_fw_retval(काष्ठा csio_mb *mbp)
अणु
	काष्ठा fw_cmd_hdr *hdr;

	hdr = (काष्ठा fw_cmd_hdr *)(mbp->mb);

	वापस FW_CMD_RETVAL_G(ntohl(hdr->lo));
पूर्ण

/*
 * csio_mb_hello - FW HELLO command helper
 * @hw: The HW काष्ठाure
 * @mbp: Mailbox काष्ठाure
 * @m_mbox: Master mailbox number, अगर any.
 * @a_mbox: Mailbox number क्रम asycn notअगरications.
 * @master: Device mastership.
 * @cbfn: Callback, अगर any.
 *
 */
व्योम
csio_mb_hello(काष्ठा csio_hw *hw, काष्ठा csio_mb *mbp, uपूर्णांक32_t पंचांगo,
	      uपूर्णांक32_t m_mbox, uपूर्णांक32_t a_mbox, क्रमागत csio_dev_master master,
	      व्योम (*cbfn) (काष्ठा csio_hw *, काष्ठा csio_mb *))
अणु
	काष्ठा fw_hello_cmd *cmdp = (काष्ठा fw_hello_cmd *)(mbp->mb);

	CSIO_INIT_MBP(mbp, cmdp, पंचांगo, hw, cbfn, 1);

	cmdp->op_to_ग_लिखो = htonl(FW_CMD_OP_V(FW_HELLO_CMD) |
				       FW_CMD_REQUEST_F | FW_CMD_WRITE_F);
	cmdp->retval_len16 = htonl(FW_CMD_LEN16_V(माप(*cmdp) / 16));
	cmdp->err_to_clearinit = htonl(
		FW_HELLO_CMD_MASTERDIS_V(master == CSIO_MASTER_CANT)	|
		FW_HELLO_CMD_MASTERFORCE_V(master == CSIO_MASTER_MUST)	|
		FW_HELLO_CMD_MBMASTER_V(master == CSIO_MASTER_MUST ?
				m_mbox : FW_HELLO_CMD_MBMASTER_M)	|
		FW_HELLO_CMD_MBASYNCNOT_V(a_mbox) |
		FW_HELLO_CMD_STAGE_V(fw_hello_cmd_stage_os) |
		FW_HELLO_CMD_CLEARINIT_F);

पूर्ण

/*
 * csio_mb_process_hello_rsp - FW HELLO response processing helper
 * @hw: The HW काष्ठाure
 * @mbp: Mailbox काष्ठाure
 * @retval: Mailbox वापस value from Firmware
 * @state: State that the function is in.
 * @mpfn: Master pfn
 *
 */
व्योम
csio_mb_process_hello_rsp(काष्ठा csio_hw *hw, काष्ठा csio_mb *mbp,
			  क्रमागत fw_retval *retval, क्रमागत csio_dev_state *state,
			  uपूर्णांक8_t *mpfn)
अणु
	काष्ठा fw_hello_cmd *rsp = (काष्ठा fw_hello_cmd *)(mbp->mb);
	uपूर्णांक32_t value;

	*retval = FW_CMD_RETVAL_G(ntohl(rsp->retval_len16));

	अगर (*retval == FW_SUCCESS) अणु
		hw->fwrev = ntohl(rsp->fwrev);

		value = ntohl(rsp->err_to_clearinit);
		*mpfn = FW_HELLO_CMD_MBMASTER_G(value);

		अगर (value & FW_HELLO_CMD_INIT_F)
			*state = CSIO_DEV_STATE_INIT;
		अन्यथा अगर (value & FW_HELLO_CMD_ERR_F)
			*state = CSIO_DEV_STATE_ERR;
		अन्यथा
			*state = CSIO_DEV_STATE_UNINIT;
	पूर्ण
पूर्ण

/*
 * csio_mb_bye - FW BYE command helper
 * @hw: The HW काष्ठाure
 * @mbp: Mailbox काष्ठाure
 * @cbfn: Callback, अगर any.
 *
 */
व्योम
csio_mb_bye(काष्ठा csio_hw *hw, काष्ठा csio_mb *mbp, uपूर्णांक32_t पंचांगo,
	    व्योम (*cbfn) (काष्ठा csio_hw *, काष्ठा csio_mb *))
अणु
	काष्ठा fw_bye_cmd *cmdp = (काष्ठा fw_bye_cmd *)(mbp->mb);

	CSIO_INIT_MBP(mbp, cmdp, पंचांगo, hw, cbfn, 1);

	cmdp->op_to_ग_लिखो = htonl(FW_CMD_OP_V(FW_BYE_CMD) |
				       FW_CMD_REQUEST_F | FW_CMD_WRITE_F);
	cmdp->retval_len16 = htonl(FW_CMD_LEN16_V(माप(*cmdp) / 16));

पूर्ण

/*
 * csio_mb_reset - FW RESET command helper
 * @hw: The HW काष्ठाure
 * @mbp: Mailbox काष्ठाure
 * @reset: Type of reset.
 * @cbfn: Callback, अगर any.
 *
 */
व्योम
csio_mb_reset(काष्ठा csio_hw *hw, काष्ठा csio_mb *mbp, uपूर्णांक32_t पंचांगo,
	      पूर्णांक reset, पूर्णांक halt,
	      व्योम (*cbfn) (काष्ठा csio_hw *, काष्ठा csio_mb *))
अणु
	काष्ठा fw_reset_cmd *cmdp = (काष्ठा fw_reset_cmd *)(mbp->mb);

	CSIO_INIT_MBP(mbp, cmdp, पंचांगo, hw, cbfn, 1);

	cmdp->op_to_ग_लिखो = htonl(FW_CMD_OP_V(FW_RESET_CMD) |
				  FW_CMD_REQUEST_F | FW_CMD_WRITE_F);
	cmdp->retval_len16 = htonl(FW_CMD_LEN16_V(माप(*cmdp) / 16));
	cmdp->val = htonl(reset);
	cmdp->halt_pkd = htonl(halt);

पूर्ण

/*
 * csio_mb_params - FW PARAMS command helper
 * @hw: The HW काष्ठाure
 * @mbp: Mailbox काष्ठाure
 * @पंचांगo: Command समयout.
 * @pf: PF number.
 * @vf: VF number.
 * @nparams: Number of parameters
 * @params: Parameter mnemonic array.
 * @val: Parameter value array.
 * @wr: Write/Read PARAMS.
 * @cbfn: Callback, अगर any.
 *
 */
व्योम
csio_mb_params(काष्ठा csio_hw *hw, काष्ठा csio_mb *mbp, uपूर्णांक32_t पंचांगo,
	       अचिन्हित पूर्णांक pf, अचिन्हित पूर्णांक vf, अचिन्हित पूर्णांक nparams,
	       स्थिर u32 *params, u32 *val, bool wr,
	       व्योम (*cbfn)(काष्ठा csio_hw *, काष्ठा csio_mb *))
अणु
	uपूर्णांक32_t i;
	uपूर्णांक32_t temp_params = 0, temp_val = 0;
	काष्ठा fw_params_cmd *cmdp = (काष्ठा fw_params_cmd *)(mbp->mb);
	__be32 *p = &cmdp->param[0].mnem;

	CSIO_INIT_MBP(mbp, cmdp, पंचांगo, hw, cbfn, 1);

	cmdp->op_to_vfn = htonl(FW_CMD_OP_V(FW_PARAMS_CMD)		|
				FW_CMD_REQUEST_F			|
				(wr ? FW_CMD_WRITE_F : FW_CMD_READ_F)	|
				FW_PARAMS_CMD_PFN_V(pf)			|
				FW_PARAMS_CMD_VFN_V(vf));
	cmdp->retval_len16 = htonl(FW_CMD_LEN16_V(माप(*cmdp) / 16));

	/* Write Params */
	अगर (wr) अणु
		जबतक (nparams--) अणु
			temp_params = *params++;
			temp_val = *val++;

			*p++ = htonl(temp_params);
			*p++ = htonl(temp_val);
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < nparams; i++, p += 2) अणु
			temp_params = *params++;
			*p = htonl(temp_params);
		पूर्ण
	पूर्ण

पूर्ण

/*
 * csio_mb_process_पढ़ो_params_rsp - FW PARAMS response processing helper
 * @hw: The HW काष्ठाure
 * @mbp: Mailbox काष्ठाure
 * @retval: Mailbox वापस value from Firmware
 * @nparams: Number of parameters
 * @val: Parameter value array.
 *
 */
व्योम
csio_mb_process_पढ़ो_params_rsp(काष्ठा csio_hw *hw, काष्ठा csio_mb *mbp,
			   क्रमागत fw_retval *retval, अचिन्हित पूर्णांक nparams,
			   u32 *val)
अणु
	काष्ठा fw_params_cmd *rsp = (काष्ठा fw_params_cmd *)(mbp->mb);
	uपूर्णांक32_t i;
	__be32 *p = &rsp->param[0].val;

	*retval = FW_CMD_RETVAL_G(ntohl(rsp->retval_len16));

	अगर (*retval == FW_SUCCESS)
		क्रम (i = 0; i < nparams; i++, p += 2)
			*val++ = ntohl(*p);
पूर्ण

/*
 * csio_mb_ldst - FW LDST command
 * @hw: The HW काष्ठाure
 * @mbp: Mailbox काष्ठाure
 * @पंचांगo: समयout
 * @reg: रेजिस्टर
 *
 */
व्योम
csio_mb_ldst(काष्ठा csio_hw *hw, काष्ठा csio_mb *mbp, uपूर्णांक32_t पंचांगo, पूर्णांक reg)
अणु
	काष्ठा fw_ldst_cmd *ldst_cmd = (काष्ठा fw_ldst_cmd *)(mbp->mb);
	CSIO_INIT_MBP(mbp, ldst_cmd, पंचांगo, hw, शून्य, 1);

	/*
	 * Conकाष्ठा and send the Firmware LDST Command to retrieve the
	 * specअगरied PCI-E Configuration Space रेजिस्टर.
	 */
	ldst_cmd->op_to_addrspace =
			htonl(FW_CMD_OP_V(FW_LDST_CMD)	|
			FW_CMD_REQUEST_F			|
			FW_CMD_READ_F			|
			FW_LDST_CMD_ADDRSPACE_V(FW_LDST_ADDRSPC_FUNC_PCIE));
	ldst_cmd->cycles_to_len16 = htonl(FW_LEN16(काष्ठा fw_ldst_cmd));
	ldst_cmd->u.pcie.select_naccess = FW_LDST_CMD_NACCESS_V(1);
	ldst_cmd->u.pcie.ctrl_to_fn =
		(FW_LDST_CMD_LC_F | FW_LDST_CMD_FN_V(hw->pfn));
	ldst_cmd->u.pcie.r = (uपूर्णांक8_t)reg;
पूर्ण

/*
 *
 * csio_mb_caps_config - FW Read/Write Capabilities command helper
 * @hw: The HW काष्ठाure
 * @mbp: Mailbox काष्ठाure
 * @wr: Write अगर 1, Read अगर 0
 * @init: Turn on initiator mode.
 * @tgt: Turn on target mode.
 * @cofld:  If 1, Control Offload क्रम FCoE
 * @cbfn: Callback, अगर any.
 *
 * This helper assumes that cmdp has MB payload from a previous CAPS
 * पढ़ो command.
 */
व्योम
csio_mb_caps_config(काष्ठा csio_hw *hw, काष्ठा csio_mb *mbp, uपूर्णांक32_t पंचांगo,
		    bool wr, bool init, bool tgt, bool cofld,
		    व्योम (*cbfn) (काष्ठा csio_hw *, काष्ठा csio_mb *))
अणु
	काष्ठा fw_caps_config_cmd *cmdp =
				(काष्ठा fw_caps_config_cmd *)(mbp->mb);

	CSIO_INIT_MBP(mbp, cmdp, पंचांगo, hw, cbfn, wr ? 0 : 1);

	cmdp->op_to_ग_लिखो = htonl(FW_CMD_OP_V(FW_CAPS_CONFIG_CMD) |
				  FW_CMD_REQUEST_F		|
				  (wr ? FW_CMD_WRITE_F : FW_CMD_READ_F));
	cmdp->cfvalid_to_len16 = htonl(FW_CMD_LEN16_V(माप(*cmdp) / 16));

	/* Read config */
	अगर (!wr)
		वापस;

	/* Write config */
	cmdp->fcoecaps = 0;

	अगर (cofld)
		cmdp->fcoecaps |= htons(FW_CAPS_CONFIG_FCOE_CTRL_OFLD);
	अगर (init)
		cmdp->fcoecaps |= htons(FW_CAPS_CONFIG_FCOE_INITIATOR);
	अगर (tgt)
		cmdp->fcoecaps |= htons(FW_CAPS_CONFIG_FCOE_TARGET);
पूर्ण

/*
 * csio_mb_port- FW PORT command helper
 * @hw: The HW काष्ठाure
 * @mbp: Mailbox काष्ठाure
 * @पंचांगo: COmmand समयout
 * @portid: Port ID to get/set info
 * @wr: Write/Read PORT inक्रमmation.
 * @fc: Flow control
 * @caps: Port capabilites to set.
 * @cbfn: Callback, अगर any.
 *
 */
व्योम
csio_mb_port(काष्ठा csio_hw *hw, काष्ठा csio_mb *mbp, uपूर्णांक32_t पंचांगo,
	     u8 portid, bool wr, uपूर्णांक32_t fc, uपूर्णांक16_t fw_caps,
	     व्योम (*cbfn) (काष्ठा csio_hw *, काष्ठा csio_mb *))
अणु
	काष्ठा fw_port_cmd *cmdp = (काष्ठा fw_port_cmd *)(mbp->mb);

	CSIO_INIT_MBP(mbp, cmdp, पंचांगo, hw, cbfn,  1);

	cmdp->op_to_portid = htonl(FW_CMD_OP_V(FW_PORT_CMD)		|
				   FW_CMD_REQUEST_F			|
				   (wr ? FW_CMD_EXEC_F : FW_CMD_READ_F)	|
				   FW_PORT_CMD_PORTID_V(portid));
	अगर (!wr) अणु
		cmdp->action_to_len16 = htonl(
			FW_PORT_CMD_ACTION_V(fw_caps == FW_CAPS16
			? FW_PORT_ACTION_GET_PORT_INFO
			: FW_PORT_ACTION_GET_PORT_INFO32) |
			FW_CMD_LEN16_V(माप(*cmdp) / 16));
		वापस;
	पूर्ण

	/* Set port */
	cmdp->action_to_len16 = htonl(
			FW_PORT_CMD_ACTION_V(fw_caps == FW_CAPS16
			? FW_PORT_ACTION_L1_CFG
			: FW_PORT_ACTION_L1_CFG32) |
			FW_CMD_LEN16_V(माप(*cmdp) / 16));

	अगर (fw_caps == FW_CAPS16)
		cmdp->u.l1cfg.rcap = cpu_to_be32(fwcaps32_to_caps16(fc));
	अन्यथा
		cmdp->u.l1cfg32.rcap32 = cpu_to_be32(fc);
पूर्ण

/*
 * csio_mb_process_पढ़ो_port_rsp - FW PORT command response processing helper
 * @hw: The HW काष्ठाure
 * @mbp: Mailbox काष्ठाure
 * @retval: Mailbox वापस value from Firmware
 * @caps: port capabilities
 *
 */
व्योम
csio_mb_process_पढ़ो_port_rsp(काष्ठा csio_hw *hw, काष्ठा csio_mb *mbp,
			 क्रमागत fw_retval *retval, uपूर्णांक16_t fw_caps,
			 u32 *pcaps, u32 *acaps)
अणु
	काष्ठा fw_port_cmd *rsp = (काष्ठा fw_port_cmd *)(mbp->mb);

	*retval = FW_CMD_RETVAL_G(ntohl(rsp->action_to_len16));

	अगर (*retval == FW_SUCCESS) अणु
		अगर (fw_caps == FW_CAPS16) अणु
			*pcaps = fwcaps16_to_caps32(ntohs(rsp->u.info.pcap));
			*acaps = fwcaps16_to_caps32(ntohs(rsp->u.info.acap));
		पूर्ण अन्यथा अणु
			*pcaps = be32_to_cpu(rsp->u.info32.pcaps32);
			*acaps = be32_to_cpu(rsp->u.info32.acaps32);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * csio_mb_initialize - FW INITIALIZE command helper
 * @hw: The HW काष्ठाure
 * @mbp: Mailbox काष्ठाure
 * @पंचांगo: COmmand समयout
 * @cbfn: Callback, अगर any.
 *
 */
व्योम
csio_mb_initialize(काष्ठा csio_hw *hw, काष्ठा csio_mb *mbp, uपूर्णांक32_t पंचांगo,
		   व्योम (*cbfn) (काष्ठा csio_hw *, काष्ठा csio_mb *))
अणु
	काष्ठा fw_initialize_cmd *cmdp = (काष्ठा fw_initialize_cmd *)(mbp->mb);

	CSIO_INIT_MBP(mbp, cmdp, पंचांगo, hw, cbfn, 1);

	cmdp->op_to_ग_लिखो = htonl(FW_CMD_OP_V(FW_INITIALIZE_CMD)	|
				  FW_CMD_REQUEST_F | FW_CMD_WRITE_F);
	cmdp->retval_len16 = htonl(FW_CMD_LEN16_V(माप(*cmdp) / 16));

पूर्ण

/*
 * csio_mb_iq_alloc - Initializes the mailbox to allocate an
 *				Ingress DMA queue in the firmware.
 *
 * @hw: The hw काष्ठाure
 * @mbp: Mailbox काष्ठाure to initialize
 * @priv: Private object
 * @mb_पंचांगo: Mailbox समय-out period (in ms).
 * @iq_params: Ingress queue params needed क्रम allocation.
 * @cbfn: The call-back function
 *
 *
 */
अटल व्योम
csio_mb_iq_alloc(काष्ठा csio_hw *hw, काष्ठा csio_mb *mbp, व्योम *priv,
		 uपूर्णांक32_t mb_पंचांगo, काष्ठा csio_iq_params *iq_params,
		 व्योम (*cbfn) (काष्ठा csio_hw *, काष्ठा csio_mb *))
अणु
	काष्ठा fw_iq_cmd *cmdp = (काष्ठा fw_iq_cmd *)(mbp->mb);

	CSIO_INIT_MBP(mbp, cmdp, mb_पंचांगo, priv, cbfn, 1);

	cmdp->op_to_vfn = htonl(FW_CMD_OP_V(FW_IQ_CMD)		|
				FW_CMD_REQUEST_F | FW_CMD_EXEC_F	|
				FW_IQ_CMD_PFN_V(iq_params->pfn)	|
				FW_IQ_CMD_VFN_V(iq_params->vfn));

	cmdp->alloc_to_len16 = htonl(FW_IQ_CMD_ALLOC_F		|
				FW_CMD_LEN16_V(माप(*cmdp) / 16));

	cmdp->type_to_iqandstindex = htonl(
				FW_IQ_CMD_VIID_V(iq_params->viid)	|
				FW_IQ_CMD_TYPE_V(iq_params->type)	|
				FW_IQ_CMD_IQASYNCH_V(iq_params->iqasynch));

	cmdp->fl0size = htons(iq_params->fl0size);
	cmdp->fl0size = htons(iq_params->fl1size);

पूर्ण /* csio_mb_iq_alloc */

/*
 * csio_mb_iq_ग_लिखो - Initializes the mailbox क्रम writing पूर्णांकo an
 *				Ingress DMA Queue.
 *
 * @hw: The HW काष्ठाure
 * @mbp: Mailbox काष्ठाure to initialize
 * @priv: Private object
 * @mb_पंचांगo: Mailbox समय-out period (in ms).
 * @cascaded_req: TRUE - अगर this request is casहालd with iq-alloc request.
 * @iq_params: Ingress queue params needed क्रम writing.
 * @cbfn: The call-back function
 *
 * NOTE: We OR relevant bits with cmdp->XXX, instead of just equating,
 * because this IQ ग_लिखो request can be cascaded with a previous
 * IQ alloc request, and we करोnt want to over-ग_लिखो the bits set by
 * that request. This logic will work even in a non-cascaded हाल, since the
 * cmdp काष्ठाure is zeroed out by CSIO_INIT_MBP.
 */
अटल व्योम
csio_mb_iq_ग_लिखो(काष्ठा csio_hw *hw, काष्ठा csio_mb *mbp, व्योम *priv,
		 uपूर्णांक32_t mb_पंचांगo, bool cascaded_req,
		 काष्ठा csio_iq_params *iq_params,
		 व्योम (*cbfn) (काष्ठा csio_hw *, काष्ठा csio_mb *))
अणु
	काष्ठा fw_iq_cmd *cmdp = (काष्ठा fw_iq_cmd *)(mbp->mb);

	uपूर्णांक32_t iq_start_stop = (iq_params->iq_start)	?
					FW_IQ_CMD_IQSTART_F :
					FW_IQ_CMD_IQSTOP_F;
	पूर्णांक relaxed = !(hw->flags & CSIO_HWF_ROOT_NO_RELAXED_ORDERING);

	/*
	 * If this IQ ग_लिखो is cascaded with IQ alloc request, करो not
	 * re-initialize with 0's.
	 *
	 */
	अगर (!cascaded_req)
		CSIO_INIT_MBP(mbp, cmdp, mb_पंचांगo, priv, cbfn, 1);

	cmdp->op_to_vfn |= htonl(FW_CMD_OP_V(FW_IQ_CMD)		|
				FW_CMD_REQUEST_F | FW_CMD_WRITE_F	|
				FW_IQ_CMD_PFN_V(iq_params->pfn)	|
				FW_IQ_CMD_VFN_V(iq_params->vfn));
	cmdp->alloc_to_len16 |= htonl(iq_start_stop |
				FW_CMD_LEN16_V(माप(*cmdp) / 16));
	cmdp->iqid |= htons(iq_params->iqid);
	cmdp->fl0id |= htons(iq_params->fl0id);
	cmdp->fl1id |= htons(iq_params->fl1id);
	cmdp->type_to_iqandstindex |= htonl(
			FW_IQ_CMD_IQANDST_V(iq_params->iqandst)	|
			FW_IQ_CMD_IQANUS_V(iq_params->iqanus)	|
			FW_IQ_CMD_IQANUD_V(iq_params->iqanud)	|
			FW_IQ_CMD_IQANDSTINDEX_V(iq_params->iqandstindex));
	cmdp->iqdroprss_to_iqesize |= htons(
			FW_IQ_CMD_IQPCIECH_V(iq_params->iqpciech)	|
			FW_IQ_CMD_IQDCAEN_V(iq_params->iqdcaen)		|
			FW_IQ_CMD_IQDCACPU_V(iq_params->iqdcacpu)	|
			FW_IQ_CMD_IQINTCNTTHRESH_V(iq_params->iqपूर्णांकcntthresh) |
			FW_IQ_CMD_IQCPRIO_V(iq_params->iqcprio)		|
			FW_IQ_CMD_IQESIZE_V(iq_params->iqesize));

	cmdp->iqsize |= htons(iq_params->iqsize);
	cmdp->iqaddr |= cpu_to_be64(iq_params->iqaddr);

	अगर (iq_params->type == 0) अणु
		cmdp->iqns_to_fl0congen |= htonl(
			FW_IQ_CMD_IQFLINTIQHSEN_V(iq_params->iqflपूर्णांकiqhsen)|
			FW_IQ_CMD_IQFLINTCONGEN_V(iq_params->iqflपूर्णांकcongen));
	पूर्ण

	अगर (iq_params->fl0size && iq_params->fl0addr &&
	    (iq_params->fl0id != 0xFFFF)) अणु

		cmdp->iqns_to_fl0congen |= htonl(
			FW_IQ_CMD_FL0HOSTFCMODE_V(iq_params->fl0hostfcmode)|
			FW_IQ_CMD_FL0CPRIO_V(iq_params->fl0cprio)	|
			FW_IQ_CMD_FL0FETCHRO_V(relaxed)			|
			FW_IQ_CMD_FL0DATARO_V(relaxed)			|
			FW_IQ_CMD_FL0PADEN_V(iq_params->fl0paden)	|
			FW_IQ_CMD_FL0PACKEN_V(iq_params->fl0packen));
		cmdp->fl0dcaen_to_fl0cidxfthresh |= htons(
			FW_IQ_CMD_FL0DCAEN_V(iq_params->fl0dcaen)	|
			FW_IQ_CMD_FL0DCACPU_V(iq_params->fl0dcacpu)	|
			FW_IQ_CMD_FL0FBMIN_V(iq_params->fl0fbmin)	|
			FW_IQ_CMD_FL0FBMAX_V(iq_params->fl0fbmax)	|
			FW_IQ_CMD_FL0CIDXFTHRESH_V(iq_params->fl0cidxfthresh));
		cmdp->fl0size |= htons(iq_params->fl0size);
		cmdp->fl0addr |= cpu_to_be64(iq_params->fl0addr);
	पूर्ण
पूर्ण /* csio_mb_iq_ग_लिखो */

/*
 * csio_mb_iq_alloc_ग_लिखो - Initializes the mailbox क्रम allocating an
 *				Ingress DMA Queue.
 *
 * @hw: The HW काष्ठाure
 * @mbp: Mailbox काष्ठाure to initialize
 * @priv: Private data.
 * @mb_पंचांगo: Mailbox समय-out period (in ms).
 * @iq_params: Ingress queue params needed क्रम allocation & writing.
 * @cbfn: The call-back function
 *
 *
 */
व्योम
csio_mb_iq_alloc_ग_लिखो(काष्ठा csio_hw *hw, काष्ठा csio_mb *mbp, व्योम *priv,
		       uपूर्णांक32_t mb_पंचांगo, काष्ठा csio_iq_params *iq_params,
		       व्योम (*cbfn) (काष्ठा csio_hw *, काष्ठा csio_mb *))
अणु
	csio_mb_iq_alloc(hw, mbp, priv, mb_पंचांगo, iq_params, cbfn);
	csio_mb_iq_ग_लिखो(hw, mbp, priv, mb_पंचांगo, true, iq_params, cbfn);
पूर्ण /* csio_mb_iq_alloc_ग_लिखो */

/*
 * csio_mb_iq_alloc_ग_लिखो_rsp - Process the allocation & writing
 *				of ingress DMA queue mailbox's response.
 *
 * @hw: The HW काष्ठाure.
 * @mbp: Mailbox काष्ठाure to initialize.
 * @retval: Firmware वापस value.
 * @iq_params: Ingress queue parameters, after allocation and ग_लिखो.
 *
 */
व्योम
csio_mb_iq_alloc_ग_लिखो_rsp(काष्ठा csio_hw *hw, काष्ठा csio_mb *mbp,
			   क्रमागत fw_retval *ret_val,
			   काष्ठा csio_iq_params *iq_params)
अणु
	काष्ठा fw_iq_cmd *rsp = (काष्ठा fw_iq_cmd *)(mbp->mb);

	*ret_val = FW_CMD_RETVAL_G(ntohl(rsp->alloc_to_len16));
	अगर (*ret_val == FW_SUCCESS) अणु
		iq_params->physiqid = ntohs(rsp->physiqid);
		iq_params->iqid = ntohs(rsp->iqid);
		iq_params->fl0id = ntohs(rsp->fl0id);
		iq_params->fl1id = ntohs(rsp->fl1id);
	पूर्ण अन्यथा अणु
		iq_params->physiqid = iq_params->iqid =
		iq_params->fl0id = iq_params->fl1id = 0;
	पूर्ण
पूर्ण /* csio_mb_iq_alloc_ग_लिखो_rsp */

/*
 * csio_mb_iq_मुक्त - Initializes the mailbox क्रम मुक्तing a
 *				specअगरied Ingress DMA Queue.
 *
 * @hw: The HW काष्ठाure
 * @mbp: Mailbox काष्ठाure to initialize
 * @priv: Private data
 * @mb_पंचांगo: Mailbox समय-out period (in ms).
 * @iq_params: Parameters of ingress queue, that is to be मुक्तd.
 * @cbfn: The call-back function
 *
 *
 */
व्योम
csio_mb_iq_मुक्त(काष्ठा csio_hw *hw, काष्ठा csio_mb *mbp, व्योम *priv,
		uपूर्णांक32_t mb_पंचांगo, काष्ठा csio_iq_params *iq_params,
		व्योम (*cbfn) (काष्ठा csio_hw *, काष्ठा csio_mb *))
अणु
	काष्ठा fw_iq_cmd *cmdp = (काष्ठा fw_iq_cmd *)(mbp->mb);

	CSIO_INIT_MBP(mbp, cmdp, mb_पंचांगo, priv, cbfn, 1);

	cmdp->op_to_vfn = htonl(FW_CMD_OP_V(FW_IQ_CMD)		|
				FW_CMD_REQUEST_F | FW_CMD_EXEC_F	|
				FW_IQ_CMD_PFN_V(iq_params->pfn)	|
				FW_IQ_CMD_VFN_V(iq_params->vfn));
	cmdp->alloc_to_len16 = htonl(FW_IQ_CMD_FREE_F		|
				FW_CMD_LEN16_V(माप(*cmdp) / 16));
	cmdp->type_to_iqandstindex = htonl(FW_IQ_CMD_TYPE_V(iq_params->type));

	cmdp->iqid = htons(iq_params->iqid);
	cmdp->fl0id = htons(iq_params->fl0id);
	cmdp->fl1id = htons(iq_params->fl1id);

पूर्ण /* csio_mb_iq_मुक्त */

/*
 * csio_mb_eq_ofld_alloc - Initializes the mailbox क्रम allocating
 *				an offload-egress queue.
 *
 * @hw: The HW  काष्ठाure
 * @mbp: Mailbox काष्ठाure to initialize
 * @priv: Private data
 * @mb_पंचांगo: Mailbox समय-out period (in ms).
 * @eq_ofld_params: (Offload) Egress queue parameters.
 * @cbfn: The call-back function
 *
 *
 */
अटल व्योम
csio_mb_eq_ofld_alloc(काष्ठा csio_hw *hw, काष्ठा csio_mb *mbp, व्योम *priv,
		uपूर्णांक32_t mb_पंचांगo, काष्ठा csio_eq_params *eq_ofld_params,
		व्योम (*cbfn) (काष्ठा csio_hw *, काष्ठा csio_mb *))
अणु
	काष्ठा fw_eq_ofld_cmd *cmdp = (काष्ठा fw_eq_ofld_cmd *)(mbp->mb);

	CSIO_INIT_MBP(mbp, cmdp, mb_पंचांगo, priv, cbfn, 1);
	cmdp->op_to_vfn = htonl(FW_CMD_OP_V(FW_EQ_OFLD_CMD)		|
				FW_CMD_REQUEST_F | FW_CMD_EXEC_F	|
				FW_EQ_OFLD_CMD_PFN_V(eq_ofld_params->pfn) |
				FW_EQ_OFLD_CMD_VFN_V(eq_ofld_params->vfn));
	cmdp->alloc_to_len16 = htonl(FW_EQ_OFLD_CMD_ALLOC_F	|
				FW_CMD_LEN16_V(माप(*cmdp) / 16));

पूर्ण /* csio_mb_eq_ofld_alloc */

/*
 * csio_mb_eq_ofld_ग_लिखो - Initializes the mailbox क्रम writing
 *				an alloacted offload-egress queue.
 *
 * @hw: The HW काष्ठाure
 * @mbp: Mailbox काष्ठाure to initialize
 * @priv: Private data
 * @mb_पंचांगo: Mailbox समय-out period (in ms).
 * @cascaded_req: TRUE - अगर this request is casहालd with Eq-alloc request.
 * @eq_ofld_params: (Offload) Egress queue parameters.
 * @cbfn: The call-back function
 *
 *
 * NOTE: We OR relevant bits with cmdp->XXX, instead of just equating,
 * because this EQ ग_लिखो request can be cascaded with a previous
 * EQ alloc request, and we करोnt want to over-ग_लिखो the bits set by
 * that request. This logic will work even in a non-cascaded हाल, since the
 * cmdp काष्ठाure is zeroed out by CSIO_INIT_MBP.
 */
अटल व्योम
csio_mb_eq_ofld_ग_लिखो(काष्ठा csio_hw *hw, काष्ठा csio_mb *mbp, व्योम *priv,
		      uपूर्णांक32_t mb_पंचांगo, bool cascaded_req,
		      काष्ठा csio_eq_params *eq_ofld_params,
		      व्योम (*cbfn) (काष्ठा csio_hw *, काष्ठा csio_mb *))
अणु
	काष्ठा fw_eq_ofld_cmd *cmdp = (काष्ठा fw_eq_ofld_cmd *)(mbp->mb);

	uपूर्णांक32_t eq_start_stop = (eq_ofld_params->eqstart)	?
				FW_EQ_OFLD_CMD_EQSTART_F :
				FW_EQ_OFLD_CMD_EQSTOP_F;

	/*
	 * If this EQ ग_लिखो is cascaded with EQ alloc request, करो not
	 * re-initialize with 0's.
	 *
	 */
	अगर (!cascaded_req)
		CSIO_INIT_MBP(mbp, cmdp, mb_पंचांगo, priv, cbfn, 1);

	cmdp->op_to_vfn |= htonl(FW_CMD_OP_V(FW_EQ_OFLD_CMD)	|
				FW_CMD_REQUEST_F | FW_CMD_WRITE_F	|
				FW_EQ_OFLD_CMD_PFN_V(eq_ofld_params->pfn) |
				FW_EQ_OFLD_CMD_VFN_V(eq_ofld_params->vfn));
	cmdp->alloc_to_len16 |= htonl(eq_start_stop		|
				      FW_CMD_LEN16_V(माप(*cmdp) / 16));

	cmdp->eqid_pkd |= htonl(FW_EQ_OFLD_CMD_EQID_V(eq_ofld_params->eqid));

	cmdp->fetchszm_to_iqid |= htonl(
		FW_EQ_OFLD_CMD_HOSTFCMODE_V(eq_ofld_params->hostfcmode)	|
		FW_EQ_OFLD_CMD_CPRIO_V(eq_ofld_params->cprio)		|
		FW_EQ_OFLD_CMD_PCIECHN_V(eq_ofld_params->pciechn)	|
		FW_EQ_OFLD_CMD_IQID_V(eq_ofld_params->iqid));

	cmdp->dcaen_to_eqsize |= htonl(
		FW_EQ_OFLD_CMD_DCAEN_V(eq_ofld_params->dcaen)		|
		FW_EQ_OFLD_CMD_DCACPU_V(eq_ofld_params->dcacpu)		|
		FW_EQ_OFLD_CMD_FBMIN_V(eq_ofld_params->fbmin)		|
		FW_EQ_OFLD_CMD_FBMAX_V(eq_ofld_params->fbmax)		|
		FW_EQ_OFLD_CMD_CIDXFTHRESHO_V(eq_ofld_params->cidxfthresho) |
		FW_EQ_OFLD_CMD_CIDXFTHRESH_V(eq_ofld_params->cidxfthresh) |
		FW_EQ_OFLD_CMD_EQSIZE_V(eq_ofld_params->eqsize));

	cmdp->eqaddr |= cpu_to_be64(eq_ofld_params->eqaddr);

पूर्ण /* csio_mb_eq_ofld_ग_लिखो */

/*
 * csio_mb_eq_ofld_alloc_ग_लिखो - Initializes the mailbox क्रम allocation
 *				writing पूर्णांकo an Engress DMA Queue.
 *
 * @hw: The HW काष्ठाure
 * @mbp: Mailbox काष्ठाure to initialize
 * @priv: Private data.
 * @mb_पंचांगo: Mailbox समय-out period (in ms).
 * @eq_ofld_params: (Offload) Egress queue parameters.
 * @cbfn: The call-back function
 *
 *
 */
व्योम
csio_mb_eq_ofld_alloc_ग_लिखो(काष्ठा csio_hw *hw, काष्ठा csio_mb *mbp,
			    व्योम *priv, uपूर्णांक32_t mb_पंचांगo,
			    काष्ठा csio_eq_params *eq_ofld_params,
			    व्योम (*cbfn) (काष्ठा csio_hw *, काष्ठा csio_mb *))
अणु
	csio_mb_eq_ofld_alloc(hw, mbp, priv, mb_पंचांगo, eq_ofld_params, cbfn);
	csio_mb_eq_ofld_ग_लिखो(hw, mbp, priv, mb_पंचांगo, true,
			      eq_ofld_params, cbfn);
पूर्ण /* csio_mb_eq_ofld_alloc_ग_लिखो */

/*
 * csio_mb_eq_ofld_alloc_ग_लिखो_rsp - Process the allocation
 *				& ग_लिखो egress DMA queue mailbox's response.
 *
 * @hw: The HW काष्ठाure.
 * @mbp: Mailbox काष्ठाure to initialize.
 * @retval: Firmware वापस value.
 * @eq_ofld_params: (Offload) Egress queue parameters.
 *
 */
व्योम
csio_mb_eq_ofld_alloc_ग_लिखो_rsp(काष्ठा csio_hw *hw,
				काष्ठा csio_mb *mbp, क्रमागत fw_retval *ret_val,
				काष्ठा csio_eq_params *eq_ofld_params)
अणु
	काष्ठा fw_eq_ofld_cmd *rsp = (काष्ठा fw_eq_ofld_cmd *)(mbp->mb);

	*ret_val = FW_CMD_RETVAL_G(ntohl(rsp->alloc_to_len16));

	अगर (*ret_val == FW_SUCCESS) अणु
		eq_ofld_params->eqid = FW_EQ_OFLD_CMD_EQID_G(
						ntohl(rsp->eqid_pkd));
		eq_ofld_params->physeqid = FW_EQ_OFLD_CMD_PHYSEQID_G(
						ntohl(rsp->physeqid_pkd));
	पूर्ण अन्यथा
		eq_ofld_params->eqid = 0;

पूर्ण /* csio_mb_eq_ofld_alloc_ग_लिखो_rsp */

/*
 * csio_mb_eq_ofld_मुक्त - Initializes the mailbox क्रम मुक्तing a
 *				specअगरied Engress DMA Queue.
 *
 * @hw: The HW काष्ठाure
 * @mbp: Mailbox काष्ठाure to initialize
 * @priv: Private data area.
 * @mb_पंचांगo: Mailbox समय-out period (in ms).
 * @eq_ofld_params: (Offload) Egress queue parameters, that is to be मुक्तd.
 * @cbfn: The call-back function
 *
 *
 */
व्योम
csio_mb_eq_ofld_मुक्त(काष्ठा csio_hw *hw, काष्ठा csio_mb *mbp, व्योम *priv,
		     uपूर्णांक32_t mb_पंचांगo, काष्ठा csio_eq_params *eq_ofld_params,
		     व्योम (*cbfn) (काष्ठा csio_hw *, काष्ठा csio_mb *))
अणु
	काष्ठा fw_eq_ofld_cmd *cmdp = (काष्ठा fw_eq_ofld_cmd *)(mbp->mb);

	CSIO_INIT_MBP(mbp, cmdp, mb_पंचांगo, priv, cbfn, 1);

	cmdp->op_to_vfn = htonl(FW_CMD_OP_V(FW_EQ_OFLD_CMD)	|
				FW_CMD_REQUEST_F | FW_CMD_EXEC_F	|
				FW_EQ_OFLD_CMD_PFN_V(eq_ofld_params->pfn) |
				FW_EQ_OFLD_CMD_VFN_V(eq_ofld_params->vfn));
	cmdp->alloc_to_len16 = htonl(FW_EQ_OFLD_CMD_FREE_F |
				FW_CMD_LEN16_V(माप(*cmdp) / 16));
	cmdp->eqid_pkd = htonl(FW_EQ_OFLD_CMD_EQID_V(eq_ofld_params->eqid));

पूर्ण /* csio_mb_eq_ofld_मुक्त */

/*
 * csio_ग_लिखो_fcoe_link_cond_init_mb - Initialize Mailbox to ग_लिखो FCoE link
 *				 condition.
 *
 * @ln: The Lnode काष्ठाure
 * @mbp: Mailbox काष्ठाure to initialize
 * @mb_पंचांगo: Mailbox समय-out period (in ms).
 * @cbfn: The call back function.
 *
 *
 */
व्योम
csio_ग_लिखो_fcoe_link_cond_init_mb(काष्ठा csio_lnode *ln, काष्ठा csio_mb *mbp,
			uपूर्णांक32_t mb_पंचांगo, uपूर्णांक8_t port_id, uपूर्णांक32_t sub_opcode,
			uपूर्णांक8_t cos, bool link_status, uपूर्णांक32_t fcfi,
			व्योम (*cbfn) (काष्ठा csio_hw *, काष्ठा csio_mb *))
अणु
	काष्ठा fw_fcoe_link_cmd *cmdp =
				(काष्ठा fw_fcoe_link_cmd *)(mbp->mb);

	CSIO_INIT_MBP(mbp, cmdp, mb_पंचांगo, ln, cbfn, 1);

	cmdp->op_to_portid = htonl((
			FW_CMD_OP_V(FW_FCOE_LINK_CMD)		|
			FW_CMD_REQUEST_F				|
			FW_CMD_WRITE_F				|
			FW_FCOE_LINK_CMD_PORTID(port_id)));
	cmdp->sub_opcode_fcfi = htonl(
			FW_FCOE_LINK_CMD_SUB_OPCODE(sub_opcode)	|
			FW_FCOE_LINK_CMD_FCFI(fcfi));
	cmdp->lstatus = link_status;
	cmdp->retval_len16 = htonl(FW_CMD_LEN16_V(माप(*cmdp) / 16));

पूर्ण /* csio_ग_लिखो_fcoe_link_cond_init_mb */

/*
 * csio_fcoe_पढ़ो_res_info_init_mb - Initializes the mailbox क्रम पढ़ोing FCoE
 *				resource inक्रमmation(FW_GET_RES_INFO_CMD).
 *
 * @hw: The HW काष्ठाure
 * @mbp: Mailbox काष्ठाure to initialize
 * @mb_पंचांगo: Mailbox समय-out period (in ms).
 * @cbfn: The call-back function
 *
 *
 */
व्योम
csio_fcoe_पढ़ो_res_info_init_mb(काष्ठा csio_hw *hw, काष्ठा csio_mb *mbp,
			uपूर्णांक32_t mb_पंचांगo,
			व्योम (*cbfn) (काष्ठा csio_hw *, काष्ठा csio_mb *))
अणु
	काष्ठा fw_fcoe_res_info_cmd *cmdp =
			(काष्ठा fw_fcoe_res_info_cmd *)(mbp->mb);

	CSIO_INIT_MBP(mbp, cmdp, mb_पंचांगo, hw, cbfn, 1);

	cmdp->op_to_पढ़ो = htonl((FW_CMD_OP_V(FW_FCOE_RES_INFO_CMD)	|
				  FW_CMD_REQUEST_F			|
				  FW_CMD_READ_F));

	cmdp->retval_len16 = htonl(FW_CMD_LEN16_V(माप(*cmdp) / 16));

पूर्ण /* csio_fcoe_पढ़ो_res_info_init_mb */

/*
 * csio_fcoe_vnp_alloc_init_mb - Initializes the mailbox क्रम allocating VNP
 *				in the firmware (FW_FCOE_VNP_CMD).
 *
 * @ln: The Lnode काष्ठाure.
 * @mbp: Mailbox काष्ठाure to initialize.
 * @mb_पंचांगo: Mailbox समय-out period (in ms).
 * @fcfi: FCF Index.
 * @vnpi: vnpi
 * @iqid: iqid
 * @vnport_wwnn: vnport WWNN
 * @vnport_wwpn: vnport WWPN
 * @cbfn: The call-back function.
 *
 *
 */
व्योम
csio_fcoe_vnp_alloc_init_mb(काष्ठा csio_lnode *ln, काष्ठा csio_mb *mbp,
		uपूर्णांक32_t mb_पंचांगo, uपूर्णांक32_t fcfi, uपूर्णांक32_t vnpi, uपूर्णांक16_t iqid,
		uपूर्णांक8_t vnport_wwnn[8],	uपूर्णांक8_t vnport_wwpn[8],
		व्योम (*cbfn) (काष्ठा csio_hw *, काष्ठा csio_mb *))
अणु
	काष्ठा fw_fcoe_vnp_cmd *cmdp =
			(काष्ठा fw_fcoe_vnp_cmd *)(mbp->mb);

	CSIO_INIT_MBP(mbp, cmdp, mb_पंचांगo, ln, cbfn, 1);

	cmdp->op_to_fcfi = htonl((FW_CMD_OP_V(FW_FCOE_VNP_CMD)		|
				  FW_CMD_REQUEST_F			|
				  FW_CMD_EXEC_F				|
				  FW_FCOE_VNP_CMD_FCFI(fcfi)));

	cmdp->alloc_to_len16 = htonl(FW_FCOE_VNP_CMD_ALLOC		|
				     FW_CMD_LEN16_V(माप(*cmdp) / 16));

	cmdp->gen_wwn_to_vnpi = htonl(FW_FCOE_VNP_CMD_VNPI(vnpi));

	cmdp->iqid = htons(iqid);

	अगर (!wwn_to_u64(vnport_wwnn) && !wwn_to_u64(vnport_wwpn))
		cmdp->gen_wwn_to_vnpi |= htonl(FW_FCOE_VNP_CMD_GEN_WWN);

	अगर (vnport_wwnn)
		स_नकल(cmdp->vnport_wwnn, vnport_wwnn, 8);
	अगर (vnport_wwpn)
		स_नकल(cmdp->vnport_wwpn, vnport_wwpn, 8);

पूर्ण /* csio_fcoe_vnp_alloc_init_mb */

/*
 * csio_fcoe_vnp_पढ़ो_init_mb - Prepares VNP पढ़ो cmd.
 * @ln: The Lnode काष्ठाure.
 * @mbp: Mailbox काष्ठाure to initialize.
 * @mb_पंचांगo: Mailbox समय-out period (in ms).
 * @fcfi: FCF Index.
 * @vnpi: vnpi
 * @cbfn: The call-back handler.
 */
व्योम
csio_fcoe_vnp_पढ़ो_init_mb(काष्ठा csio_lnode *ln, काष्ठा csio_mb *mbp,
		uपूर्णांक32_t mb_पंचांगo, uपूर्णांक32_t fcfi, uपूर्णांक32_t vnpi,
		व्योम (*cbfn) (काष्ठा csio_hw *, काष्ठा csio_mb *))
अणु
	काष्ठा fw_fcoe_vnp_cmd *cmdp =
			(काष्ठा fw_fcoe_vnp_cmd *)(mbp->mb);

	CSIO_INIT_MBP(mbp, cmdp, mb_पंचांगo, ln, cbfn, 1);
	cmdp->op_to_fcfi = htonl(FW_CMD_OP_V(FW_FCOE_VNP_CMD)	|
				 FW_CMD_REQUEST_F			|
				 FW_CMD_READ_F			|
				 FW_FCOE_VNP_CMD_FCFI(fcfi));
	cmdp->alloc_to_len16 = htonl(FW_CMD_LEN16_V(माप(*cmdp) / 16));
	cmdp->gen_wwn_to_vnpi = htonl(FW_FCOE_VNP_CMD_VNPI(vnpi));
पूर्ण

/*
 * csio_fcoe_vnp_मुक्त_init_mb - Initializes the mailbox क्रम मुक्तing an
 *			alloacted VNP in the firmware (FW_FCOE_VNP_CMD).
 *
 * @ln: The Lnode काष्ठाure.
 * @mbp: Mailbox काष्ठाure to initialize.
 * @mb_पंचांगo: Mailbox समय-out period (in ms).
 * @fcfi: FCF flow id
 * @vnpi: VNP flow id
 * @cbfn: The call-back function.
 * Return: None
 */
व्योम
csio_fcoe_vnp_मुक्त_init_mb(काष्ठा csio_lnode *ln, काष्ठा csio_mb *mbp,
		uपूर्णांक32_t mb_पंचांगo, uपूर्णांक32_t fcfi, uपूर्णांक32_t vnpi,
		व्योम (*cbfn) (काष्ठा csio_hw *, काष्ठा csio_mb *))
अणु
	काष्ठा fw_fcoe_vnp_cmd *cmdp =
			(काष्ठा fw_fcoe_vnp_cmd *)(mbp->mb);

	CSIO_INIT_MBP(mbp, cmdp, mb_पंचांगo, ln, cbfn, 1);

	cmdp->op_to_fcfi = htonl(FW_CMD_OP_V(FW_FCOE_VNP_CMD)	|
				 FW_CMD_REQUEST_F			|
				 FW_CMD_EXEC_F			|
				 FW_FCOE_VNP_CMD_FCFI(fcfi));
	cmdp->alloc_to_len16 = htonl(FW_FCOE_VNP_CMD_FREE	|
				     FW_CMD_LEN16_V(माप(*cmdp) / 16));
	cmdp->gen_wwn_to_vnpi = htonl(FW_FCOE_VNP_CMD_VNPI(vnpi));
पूर्ण

/*
 * csio_fcoe_पढ़ो_fcf_init_mb - Initializes the mailbox to पढ़ो the
 *				FCF records.
 *
 * @ln: The Lnode काष्ठाure
 * @mbp: Mailbox काष्ठाure to initialize
 * @mb_पंचांगo: Mailbox समय-out period (in ms).
 * @fcf_params: FC-Forwarder parameters.
 * @cbfn: The call-back function
 *
 *
 */
व्योम
csio_fcoe_पढ़ो_fcf_init_mb(काष्ठा csio_lnode *ln, काष्ठा csio_mb *mbp,
		uपूर्णांक32_t mb_पंचांगo, uपूर्णांक32_t portid, uपूर्णांक32_t fcfi,
		व्योम (*cbfn) (काष्ठा csio_hw *, काष्ठा csio_mb *))
अणु
	काष्ठा fw_fcoe_fcf_cmd *cmdp =
			(काष्ठा fw_fcoe_fcf_cmd *)(mbp->mb);

	CSIO_INIT_MBP(mbp, cmdp, mb_पंचांगo, ln, cbfn, 1);

	cmdp->op_to_fcfi = htonl(FW_CMD_OP_V(FW_FCOE_FCF_CMD)	|
				 FW_CMD_REQUEST_F			|
				 FW_CMD_READ_F			|
				 FW_FCOE_FCF_CMD_FCFI(fcfi));
	cmdp->retval_len16 = htonl(FW_CMD_LEN16_V(माप(*cmdp) / 16));

पूर्ण /* csio_fcoe_पढ़ो_fcf_init_mb */

व्योम
csio_fcoe_पढ़ो_portparams_init_mb(काष्ठा csio_hw *hw, काष्ठा csio_mb *mbp,
				uपूर्णांक32_t mb_पंचांगo,
				काष्ठा fw_fcoe_port_cmd_params *portparams,
				व्योम (*cbfn)(काष्ठा csio_hw *,
					     काष्ठा csio_mb *))
अणु
	काष्ठा fw_fcoe_stats_cmd *cmdp = (काष्ठा fw_fcoe_stats_cmd *)(mbp->mb);

	CSIO_INIT_MBP(mbp, cmdp, mb_पंचांगo, hw, cbfn, 1);
	mbp->mb_size = 64;

	cmdp->op_to_flowid = htonl(FW_CMD_OP_V(FW_FCOE_STATS_CMD)         |
				   FW_CMD_REQUEST_F | FW_CMD_READ_F);
	cmdp->मुक्त_to_len16 = htonl(FW_CMD_LEN16_V(CSIO_MAX_MB_SIZE/16));

	cmdp->u.ctl.nstats_port = FW_FCOE_STATS_CMD_NSTATS(portparams->nstats) |
				  FW_FCOE_STATS_CMD_PORT(portparams->portid);

	cmdp->u.ctl.port_valid_ix = FW_FCOE_STATS_CMD_IX(portparams->idx)    |
				    FW_FCOE_STATS_CMD_PORT_VALID;

पूर्ण /* csio_fcoe_पढ़ो_portparams_init_mb */

व्योम
csio_mb_process_portparams_rsp(काष्ठा csio_hw *hw,
				काष्ठा csio_mb *mbp,
				क्रमागत fw_retval *retval,
				काष्ठा fw_fcoe_port_cmd_params *portparams,
				काष्ठा fw_fcoe_port_stats *portstats)
अणु
	काष्ठा fw_fcoe_stats_cmd *rsp = (काष्ठा fw_fcoe_stats_cmd *)(mbp->mb);
	काष्ठा fw_fcoe_port_stats stats;
	uपूर्णांक8_t *src;
	uपूर्णांक8_t *dst;

	*retval = FW_CMD_RETVAL_G(ntohl(rsp->मुक्त_to_len16));

	स_रखो(&stats, 0, माप(काष्ठा fw_fcoe_port_stats));

	अगर (*retval == FW_SUCCESS) अणु
		dst = (uपूर्णांक8_t *)(&stats) + ((portparams->idx - 1) * 8);
		src = (uपूर्णांक8_t *)rsp + (CSIO_STATS_OFFSET * 8);
		स_नकल(dst, src, (portparams->nstats * 8));
		अगर (portparams->idx == 1) अणु
			/* Get the first 6 flits from the Mailbox */
			portstats->tx_bcast_bytes = stats.tx_bcast_bytes;
			portstats->tx_bcast_frames = stats.tx_bcast_frames;
			portstats->tx_mcast_bytes = stats.tx_mcast_bytes;
			portstats->tx_mcast_frames = stats.tx_mcast_frames;
			portstats->tx_ucast_bytes = stats.tx_ucast_bytes;
			portstats->tx_ucast_frames = stats.tx_ucast_frames;
		पूर्ण
		अगर (portparams->idx == 7) अणु
			/* Get the second 6 flits from the Mailbox */
			portstats->tx_drop_frames = stats.tx_drop_frames;
			portstats->tx_offload_bytes = stats.tx_offload_bytes;
			portstats->tx_offload_frames = stats.tx_offload_frames;
#अगर 0
			portstats->rx_pf_bytes = stats.rx_pf_bytes;
			portstats->rx_pf_frames	= stats.rx_pf_frames;
#पूर्ण_अगर
			portstats->rx_bcast_bytes = stats.rx_bcast_bytes;
			portstats->rx_bcast_frames = stats.rx_bcast_frames;
			portstats->rx_mcast_bytes = stats.rx_mcast_bytes;
		पूर्ण
		अगर (portparams->idx == 13) अणु
			/* Get the last 4 flits from the Mailbox */
			portstats->rx_mcast_frames = stats.rx_mcast_frames;
			portstats->rx_ucast_bytes = stats.rx_ucast_bytes;
			portstats->rx_ucast_frames = stats.rx_ucast_frames;
			portstats->rx_err_frames = stats.rx_err_frames;
		पूर्ण
	पूर्ण
पूर्ण

/* Entry poपूर्णांकs/APIs क्रम MB module					     */
/*
 * csio_mb_पूर्णांकr_enable - Enable Interrupts from mailboxes.
 * @hw: The HW काष्ठाure
 *
 * Enables CIM पूर्णांकerrupt bit in appropriate INT_ENABLE रेजिस्टरs.
 */
व्योम
csio_mb_पूर्णांकr_enable(काष्ठा csio_hw *hw)
अणु
	csio_wr_reg32(hw, MBMSGRDYINTEN_F, MYPF_REG(CIM_PF_HOST_INT_ENABLE_A));
	csio_rd_reg32(hw, MYPF_REG(CIM_PF_HOST_INT_ENABLE_A));
पूर्ण

/*
 * csio_mb_पूर्णांकr_disable - Disable Interrupts from mailboxes.
 * @hw: The HW काष्ठाure
 *
 * Disable bit in HostInterruptEnable CIM रेजिस्टर.
 */
व्योम
csio_mb_पूर्णांकr_disable(काष्ठा csio_hw *hw)
अणु
	csio_wr_reg32(hw, MBMSGRDYINTEN_V(0),
		      MYPF_REG(CIM_PF_HOST_INT_ENABLE_A));
	csio_rd_reg32(hw, MYPF_REG(CIM_PF_HOST_INT_ENABLE_A));
पूर्ण

अटल व्योम
csio_mb_dump_fw_dbg(काष्ठा csio_hw *hw, __be64 *cmd)
अणु
	काष्ठा fw_debug_cmd *dbg = (काष्ठा fw_debug_cmd *)cmd;

	अगर ((FW_DEBUG_CMD_TYPE_G(ntohl(dbg->op_type))) == 1) अणु
		csio_info(hw, "FW print message:\n");
		csio_info(hw, "\tdebug->dprtstridx = %d\n",
			    ntohs(dbg->u.prt.dprtstridx));
		csio_info(hw, "\tdebug->dprtstrparam0 = 0x%x\n",
			    ntohl(dbg->u.prt.dprtstrparam0));
		csio_info(hw, "\tdebug->dprtstrparam1 = 0x%x\n",
			    ntohl(dbg->u.prt.dprtstrparam1));
		csio_info(hw, "\tdebug->dprtstrparam2 = 0x%x\n",
			    ntohl(dbg->u.prt.dprtstrparam2));
		csio_info(hw, "\tdebug->dprtstrparam3 = 0x%x\n",
			    ntohl(dbg->u.prt.dprtstrparam3));
	पूर्ण अन्यथा अणु
		/* This is a FW निश्चितion */
		csio_fatal(hw, "FW assertion at %.16s:%u, val0 %#x, val1 %#x\n",
			    dbg->u.निश्चित.filename_0_7,
			    ntohl(dbg->u.निश्चित.line),
			    ntohl(dbg->u.निश्चित.x),
			    ntohl(dbg->u.निश्चित.y));
	पूर्ण
पूर्ण

अटल व्योम
csio_mb_debug_cmd_handler(काष्ठा csio_hw *hw)
अणु
	पूर्णांक i;
	__be64 cmd[CSIO_MB_MAX_REGS];
	uपूर्णांक32_t ctl_reg = PF_REG(hw->pfn, CIM_PF_MAILBOX_CTRL_A);
	uपूर्णांक32_t data_reg = PF_REG(hw->pfn, CIM_PF_MAILBOX_DATA_A);
	पूर्णांक size = माप(काष्ठा fw_debug_cmd);

	/* Copy mailbox data */
	क्रम (i = 0; i < size; i += 8)
		cmd[i / 8] = cpu_to_be64(csio_rd_reg64(hw, data_reg + i));

	csio_mb_dump_fw_dbg(hw, cmd);

	/* Notअगरy FW of mailbox by setting owner as UP */
	csio_wr_reg32(hw, MBMSGVALID_F | MBINTREQ_F |
		      MBOWNER_V(CSIO_MBOWNER_FW), ctl_reg);

	csio_rd_reg32(hw, ctl_reg);
	wmb();
पूर्ण

/*
 * csio_mb_issue - generic routine क्रम issuing Mailbox commands.
 * @hw: The HW काष्ठाure
 * @mbp: Mailbox command to issue
 *
 *  Caller should hold hw lock across this call.
 */
पूर्णांक
csio_mb_issue(काष्ठा csio_hw *hw, काष्ठा csio_mb *mbp)
अणु
	uपूर्णांक32_t owner, ctl;
	पूर्णांक i;
	uपूर्णांक32_t ii;
	__be64 *cmd = mbp->mb;
	__be64 hdr;
	काष्ठा csio_mbm	*mbm = &hw->mbm;
	uपूर्णांक32_t ctl_reg = PF_REG(hw->pfn, CIM_PF_MAILBOX_CTRL_A);
	uपूर्णांक32_t data_reg = PF_REG(hw->pfn, CIM_PF_MAILBOX_DATA_A);
	पूर्णांक size = mbp->mb_size;
	पूर्णांक rv = -EINVAL;
	काष्ठा fw_cmd_hdr *fw_hdr;

	/* Determine mode */
	अगर (mbp->mb_cbfn == शून्य) अणु
		/* Need to issue/get results in the same context */
		अगर (mbp->पंचांगo < CSIO_MB_POLL_FREQ) अणु
			csio_err(hw, "Invalid tmo: 0x%x\n", mbp->पंचांगo);
			जाओ error_out;
		पूर्ण
	पूर्ण अन्यथा अगर (!csio_is_host_पूर्णांकr_enabled(hw) ||
		   !csio_is_hw_पूर्णांकr_enabled(hw)) अणु
		csio_err(hw, "Cannot issue mailbox in interrupt mode 0x%x\n",
			 *((uपूर्णांक8_t *)mbp->mb));
		जाओ error_out;
	पूर्ण

	अगर (mbm->mcurrent != शून्य) अणु
		/* Queue mbox cmd, अगर another mbox cmd is active */
		अगर (mbp->mb_cbfn == शून्य) अणु
			rv = -EBUSY;
			csio_dbg(hw, "Couldn't own Mailbox %x op:0x%x\n",
				    hw->pfn, *((uपूर्णांक8_t *)mbp->mb));

			जाओ error_out;
		पूर्ण अन्यथा अणु
			list_add_tail(&mbp->list, &mbm->req_q);
			CSIO_INC_STATS(mbm, n_activeq);

			वापस 0;
		पूर्ण
	पूर्ण

	/* Now get ownership of mailbox */
	owner = MBOWNER_G(csio_rd_reg32(hw, ctl_reg));

	अगर (!csio_mb_is_host_owner(owner)) अणु

		क्रम (i = 0; (owner == CSIO_MBOWNER_NONE) && (i < 3); i++)
			owner = MBOWNER_G(csio_rd_reg32(hw, ctl_reg));
		/*
		 * Mailbox unavailable. In immediate mode, fail the command.
		 * In other modes, enqueue the request.
		 */
		अगर (!csio_mb_is_host_owner(owner)) अणु
			अगर (mbp->mb_cbfn == शून्य) अणु
				rv = owner ? -EBUSY : -ETIMEDOUT;

				csio_dbg(hw,
					 "Couldn't own Mailbox %x op:0x%x "
					 "owner:%x\n",
					 hw->pfn, *((uपूर्णांक8_t *)mbp->mb), owner);
				जाओ error_out;
			पूर्ण अन्यथा अणु
				अगर (mbm->mcurrent == शून्य) अणु
					csio_err(hw,
						 "Couldn't own Mailbox %x "
						 "op:0x%x owner:%x\n",
						 hw->pfn, *((uपूर्णांक8_t *)mbp->mb),
						 owner);
					csio_err(hw,
						 "No outstanding driver"
						 " mailbox as well\n");
					जाओ error_out;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	/* Mailbox is available, copy mailbox data पूर्णांकo it */
	क्रम (i = 0; i < size; i += 8) अणु
		csio_wr_reg64(hw, be64_to_cpu(*cmd), data_reg + i);
		cmd++;
	पूर्ण

	CSIO_DUMP_MB(hw, hw->pfn, data_reg);

	/* Start completion समयrs in non-immediate modes and notअगरy FW */
	अगर (mbp->mb_cbfn != शून्य) अणु
		mbm->mcurrent = mbp;
		mod_समयr(&mbm->समयr, jअगरfies + msecs_to_jअगरfies(mbp->पंचांगo));
		csio_wr_reg32(hw, MBMSGVALID_F | MBINTREQ_F |
			      MBOWNER_V(CSIO_MBOWNER_FW), ctl_reg);
	पूर्ण अन्यथा
		csio_wr_reg32(hw, MBMSGVALID_F | MBOWNER_V(CSIO_MBOWNER_FW),
			      ctl_reg);

	/* Flush posted ग_लिखोs */
	csio_rd_reg32(hw, ctl_reg);
	wmb();

	CSIO_INC_STATS(mbm, n_req);

	अगर (mbp->mb_cbfn)
		वापस 0;

	/* Poll क्रम completion in immediate mode */
	cmd = mbp->mb;

	क्रम (ii = 0; ii < mbp->पंचांगo; ii += CSIO_MB_POLL_FREQ) अणु
		mdelay(CSIO_MB_POLL_FREQ);

		/* Check क्रम response */
		ctl = csio_rd_reg32(hw, ctl_reg);
		अगर (csio_mb_is_host_owner(MBOWNER_G(ctl))) अणु

			अगर (!(ctl & MBMSGVALID_F)) अणु
				csio_wr_reg32(hw, 0, ctl_reg);
				जारी;
			पूर्ण

			CSIO_DUMP_MB(hw, hw->pfn, data_reg);

			hdr = cpu_to_be64(csio_rd_reg64(hw, data_reg));
			fw_hdr = (काष्ठा fw_cmd_hdr *)&hdr;

			चयन (FW_CMD_OP_G(ntohl(fw_hdr->hi))) अणु
			हाल FW_DEBUG_CMD:
				csio_mb_debug_cmd_handler(hw);
				जारी;
			पूर्ण

			/* Copy response */
			क्रम (i = 0; i < size; i += 8)
				*cmd++ = cpu_to_be64(csio_rd_reg64
							  (hw, data_reg + i));
			csio_wr_reg32(hw, 0, ctl_reg);

			अगर (csio_mb_fw_retval(mbp) != FW_SUCCESS)
				CSIO_INC_STATS(mbm, n_err);

			CSIO_INC_STATS(mbm, n_rsp);
			वापस 0;
		पूर्ण
	पूर्ण

	CSIO_INC_STATS(mbm, n_पंचांगo);

	csio_err(hw, "Mailbox %x op:0x%x timed out!\n",
		 hw->pfn, *((uपूर्णांक8_t *)cmd));

	वापस -ETIMEDOUT;

error_out:
	CSIO_INC_STATS(mbm, n_err);
	वापस rv;
पूर्ण

/*
 * csio_mb_completions - Completion handler क्रम Mailbox commands
 * @hw: The HW काष्ठाure
 * @cbfn_q: Completion queue.
 *
 */
व्योम
csio_mb_completions(काष्ठा csio_hw *hw, काष्ठा list_head *cbfn_q)
अणु
	काष्ठा csio_mb *mbp;
	काष्ठा csio_mbm *mbm = &hw->mbm;
	क्रमागत fw_retval rv;

	जबतक (!list_empty(cbfn_q)) अणु
		mbp = list_first_entry(cbfn_q, काष्ठा csio_mb, list);
		list_del_init(&mbp->list);

		rv = csio_mb_fw_retval(mbp);
		अगर ((rv != FW_SUCCESS) && (rv != FW_HOSTERROR))
			CSIO_INC_STATS(mbm, n_err);
		अन्यथा अगर (rv != FW_HOSTERROR)
			CSIO_INC_STATS(mbm, n_rsp);

		अगर (mbp->mb_cbfn)
			mbp->mb_cbfn(hw, mbp);
	पूर्ण
पूर्ण

अटल व्योम
csio_mb_porपंचांगod_changed(काष्ठा csio_hw *hw, uपूर्णांक8_t port_id)
अणु
	अटल अक्षर *mod_str[] = अणु
		शून्य, "LR", "SR", "ER", "TWINAX", "active TWINAX", "LRM"
	पूर्ण;

	काष्ठा csio_pport *port = &hw->pport[port_id];

	अगर (port->mod_type == FW_PORT_MOD_TYPE_NONE)
		csio_info(hw, "Port:%d - port module unplugged\n", port_id);
	अन्यथा अगर (port->mod_type < ARRAY_SIZE(mod_str))
		csio_info(hw, "Port:%d - %s port module inserted\n", port_id,
			  mod_str[port->mod_type]);
	अन्यथा अगर (port->mod_type == FW_PORT_MOD_TYPE_NOTSUPPORTED)
		csio_info(hw,
			  "Port:%d - unsupported optical port module "
			  "inserted\n", port_id);
	अन्यथा अगर (port->mod_type == FW_PORT_MOD_TYPE_UNKNOWN)
		csio_info(hw,
			  "Port:%d - unknown port module inserted, forcing "
			  "TWINAX\n", port_id);
	अन्यथा अगर (port->mod_type == FW_PORT_MOD_TYPE_ERROR)
		csio_info(hw, "Port:%d - transceiver module error\n", port_id);
	अन्यथा
		csio_info(hw, "Port:%d - unknown module type %d inserted\n",
			  port_id, port->mod_type);
पूर्ण

पूर्णांक
csio_mb_fwevt_handler(काष्ठा csio_hw *hw, __be64 *cmd)
अणु
	uपूर्णांक8_t opcode = *(uपूर्णांक8_t *)cmd;
	काष्ठा fw_port_cmd *pcmd;
	uपूर्णांक8_t port_id;
	uपूर्णांक32_t link_status;
	uपूर्णांक16_t action;
	uपूर्णांक8_t mod_type;
	fw_port_cap32_t linkattr;

	अगर (opcode == FW_PORT_CMD) अणु
		pcmd = (काष्ठा fw_port_cmd *)cmd;
		port_id = FW_PORT_CMD_PORTID_G(
				ntohl(pcmd->op_to_portid));
		action = FW_PORT_CMD_ACTION_G(
				ntohl(pcmd->action_to_len16));
		अगर (action != FW_PORT_ACTION_GET_PORT_INFO &&
		    action != FW_PORT_ACTION_GET_PORT_INFO32) अणु
			csio_err(hw, "Unhandled FW_PORT_CMD action: %u\n",
				action);
			वापस -EINVAL;
		पूर्ण

		अगर (action == FW_PORT_ACTION_GET_PORT_INFO) अणु
			link_status = ntohl(pcmd->u.info.lstatus_to_modtype);
			mod_type = FW_PORT_CMD_MODTYPE_G(link_status);
			linkattr = lstatus_to_fwcap(link_status);

			hw->pport[port_id].link_status =
				FW_PORT_CMD_LSTATUS_G(link_status);
		पूर्ण अन्यथा अणु
			link_status =
				ntohl(pcmd->u.info32.lstatus32_to_cbllen32);
			mod_type = FW_PORT_CMD_MODTYPE32_G(link_status);
			linkattr = ntohl(pcmd->u.info32.linkattr32);

			hw->pport[port_id].link_status =
				FW_PORT_CMD_LSTATUS32_G(link_status);
		पूर्ण

		hw->pport[port_id].link_speed = fwcap_to_fwspeed(linkattr);

		csio_info(hw, "Port:%x - LINK %s\n", port_id,
			hw->pport[port_id].link_status ? "UP" : "DOWN");

		अगर (mod_type != hw->pport[port_id].mod_type) अणु
			hw->pport[port_id].mod_type = mod_type;
			csio_mb_porपंचांगod_changed(hw, port_id);
		पूर्ण
	पूर्ण अन्यथा अगर (opcode == FW_DEBUG_CMD) अणु
		csio_mb_dump_fw_dbg(hw, cmd);
	पूर्ण अन्यथा अणु
		csio_dbg(hw, "Gen MB can't handle op:0x%x on evtq.\n", opcode);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * csio_mb_isr_handler - Handle mailboxes related पूर्णांकerrupts.
 * @hw: The HW काष्ठाure
 *
 * Called from the ISR to handle Mailbox related पूर्णांकerrupts.
 * HW Lock should be held across this call.
 */
पूर्णांक
csio_mb_isr_handler(काष्ठा csio_hw *hw)
अणु
	काष्ठा csio_mbm		*mbm = &hw->mbm;
	काष्ठा csio_mb		*mbp =  mbm->mcurrent;
	__be64			*cmd;
	uपूर्णांक32_t		ctl, cim_cause, pl_cause;
	पूर्णांक			i;
	uपूर्णांक32_t	ctl_reg = PF_REG(hw->pfn, CIM_PF_MAILBOX_CTRL_A);
	uपूर्णांक32_t	data_reg = PF_REG(hw->pfn, CIM_PF_MAILBOX_DATA_A);
	पूर्णांक			size;
	__be64			hdr;
	काष्ठा fw_cmd_hdr	*fw_hdr;

	pl_cause = csio_rd_reg32(hw, MYPF_REG(PL_PF_INT_CAUSE_A));
	cim_cause = csio_rd_reg32(hw, MYPF_REG(CIM_PF_HOST_INT_CAUSE_A));

	अगर (!(pl_cause & PFCIM_F) || !(cim_cause & MBMSGRDYINT_F)) अणु
		CSIO_INC_STATS(hw, n_mbपूर्णांक_unexp);
		वापस -EINVAL;
	पूर्ण

	/*
	 * The cause रेजिस्टरs below HAVE to be cleared in the SAME
	 * order as below: The low level cause रेजिस्टर followed by
	 * the upper level cause रेजिस्टर. In other words, CIM-cause
	 * first followed by PL-Cause next.
	 */
	csio_wr_reg32(hw, MBMSGRDYINT_F, MYPF_REG(CIM_PF_HOST_INT_CAUSE_A));
	csio_wr_reg32(hw, PFCIM_F, MYPF_REG(PL_PF_INT_CAUSE_A));

	ctl = csio_rd_reg32(hw, ctl_reg);

	अगर (csio_mb_is_host_owner(MBOWNER_G(ctl))) अणु

		CSIO_DUMP_MB(hw, hw->pfn, data_reg);

		अगर (!(ctl & MBMSGVALID_F)) अणु
			csio_warn(hw,
				  "Stray mailbox interrupt recvd,"
				  " mailbox data not valid\n");
			csio_wr_reg32(hw, 0, ctl_reg);
			/* Flush */
			csio_rd_reg32(hw, ctl_reg);
			वापस -EINVAL;
		पूर्ण

		hdr = cpu_to_be64(csio_rd_reg64(hw, data_reg));
		fw_hdr = (काष्ठा fw_cmd_hdr *)&hdr;

		चयन (FW_CMD_OP_G(ntohl(fw_hdr->hi))) अणु
		हाल FW_DEBUG_CMD:
			csio_mb_debug_cmd_handler(hw);
			वापस -EINVAL;
#अगर 0
		हाल FW_ERROR_CMD:
		हाल FW_INITIALIZE_CMD: /* When we are not master */
#पूर्ण_अगर
		पूर्ण

		CSIO_ASSERT(mbp != शून्य);

		cmd = mbp->mb;
		size = mbp->mb_size;
		/* Get response */
		क्रम (i = 0; i < size; i += 8)
			*cmd++ = cpu_to_be64(csio_rd_reg64
						  (hw, data_reg + i));

		csio_wr_reg32(hw, 0, ctl_reg);
		/* Flush */
		csio_rd_reg32(hw, ctl_reg);

		mbm->mcurrent = शून्य;

		/* Add completion to tail of cbfn queue */
		list_add_tail(&mbp->list, &mbm->cbfn_q);
		CSIO_INC_STATS(mbm, n_cbfnq);

		/*
		 * Enqueue event to EventQ. Events processing happens
		 * in Event worker thपढ़ो context
		 */
		अगर (csio_enqueue_evt(hw, CSIO_EVT_MBX, mbp, माप(mbp)))
			CSIO_INC_STATS(hw, n_evt_drop);

		वापस 0;

	पूर्ण अन्यथा अणु
		/*
		 * We can get here अगर mailbox MSIX vector is shared,
		 * or in INTx हाल. Or a stray पूर्णांकerrupt.
		 */
		csio_dbg(hw, "Host not owner, no mailbox interrupt\n");
		CSIO_INC_STATS(hw, n_पूर्णांक_stray);
		वापस -EINVAL;
	पूर्ण
पूर्ण

/*
 * csio_mb_पंचांगo_handler - Timeout handler
 * @hw: The HW काष्ठाure
 *
 */
काष्ठा csio_mb *
csio_mb_पंचांगo_handler(काष्ठा csio_hw *hw)
अणु
	काष्ठा csio_mbm *mbm = &hw->mbm;
	काष्ठा csio_mb *mbp =  mbm->mcurrent;
	काष्ठा fw_cmd_hdr *fw_hdr;

	/*
	 * Could be a race b/w the completion handler and the समयr
	 * and the completion handler won that race.
	 */
	अगर (mbp == शून्य) अणु
		CSIO_DB_ASSERT(0);
		वापस शून्य;
	पूर्ण

	fw_hdr = (काष्ठा fw_cmd_hdr *)(mbp->mb);

	csio_dbg(hw, "Mailbox num:%x op:0x%x timed out\n", hw->pfn,
		    FW_CMD_OP_G(ntohl(fw_hdr->hi)));

	mbm->mcurrent = शून्य;
	CSIO_INC_STATS(mbm, n_पंचांगo);
	fw_hdr->lo = htonl(FW_CMD_RETVAL_V(FW_ETIMEDOUT));

	वापस mbp;
पूर्ण

/*
 * csio_mb_cancel_all - Cancel all रुकोing commands.
 * @hw: The HW काष्ठाure
 * @cbfn_q: The callback queue.
 *
 * Caller should hold hw lock across this call.
 */
व्योम
csio_mb_cancel_all(काष्ठा csio_hw *hw, काष्ठा list_head *cbfn_q)
अणु
	काष्ठा csio_mb *mbp;
	काष्ठा csio_mbm *mbm = &hw->mbm;
	काष्ठा fw_cmd_hdr *hdr;
	काष्ठा list_head *पंचांगp;

	अगर (mbm->mcurrent) अणु
		mbp = mbm->mcurrent;

		/* Stop mailbox completion समयr */
		del_समयr_sync(&mbm->समयr);

		/* Add completion to tail of cbfn queue */
		list_add_tail(&mbp->list, cbfn_q);
		mbm->mcurrent = शून्य;
	पूर्ण

	अगर (!list_empty(&mbm->req_q)) अणु
		list_splice_tail_init(&mbm->req_q, cbfn_q);
		mbm->stats.n_activeq = 0;
	पूर्ण

	अगर (!list_empty(&mbm->cbfn_q)) अणु
		list_splice_tail_init(&mbm->cbfn_q, cbfn_q);
		mbm->stats.n_cbfnq = 0;
	पूर्ण

	अगर (list_empty(cbfn_q))
		वापस;

	list_क्रम_each(पंचांगp, cbfn_q) अणु
		mbp = (काष्ठा csio_mb *)पंचांगp;
		hdr = (काष्ठा fw_cmd_hdr *)(mbp->mb);

		csio_dbg(hw, "Cancelling pending mailbox num %x op:%x\n",
			    hw->pfn, FW_CMD_OP_G(ntohl(hdr->hi)));

		CSIO_INC_STATS(mbm, n_cancel);
		hdr->lo = htonl(FW_CMD_RETVAL_V(FW_HOSTERROR));
	पूर्ण
पूर्ण

/*
 * csio_mbm_init - Initialize Mailbox module
 * @mbm: Mailbox module
 * @hw: The HW काष्ठाure
 * @समयr: Timing function क्रम पूर्णांकerrupting mailboxes
 *
 * Initialize समयr and the request/response queues.
 */
पूर्णांक
csio_mbm_init(काष्ठा csio_mbm *mbm, काष्ठा csio_hw *hw,
	      व्योम (*समयr_fn)(काष्ठा समयr_list *))
अणु
	mbm->hw = hw;
	समयr_setup(&mbm->समयr, समयr_fn, 0);

	INIT_LIST_HEAD(&mbm->req_q);
	INIT_LIST_HEAD(&mbm->cbfn_q);
	csio_set_mb_पूर्णांकr_idx(mbm, -1);

	वापस 0;
पूर्ण

/*
 * csio_mbm_निकास - Uninitialize mailbox module
 * @mbm: Mailbox module
 *
 * Stop समयr.
 */
व्योम
csio_mbm_निकास(काष्ठा csio_mbm *mbm)
अणु
	del_समयr_sync(&mbm->समयr);

	CSIO_DB_ASSERT(mbm->mcurrent == शून्य);
	CSIO_DB_ASSERT(list_empty(&mbm->req_q));
	CSIO_DB_ASSERT(list_empty(&mbm->cbfn_q));
पूर्ण
