<शैली गुरु>
/*
 * This file is part of the Chelsio T4 PCI-E SR-IOV Virtual Function Ethernet
 * driver क्रम Linux.
 *
 * Copyright (c) 2009-2010 Chelsio Communications, Inc. All rights reserved.
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

#समावेश <linux/ethtool.h>
#समावेश <linux/pci.h>

#समावेश "t4vf_common.h"
#समावेश "t4vf_defs.h"

#समावेश "../cxgb4/t4_regs.h"
#समावेश "../cxgb4/t4_values.h"
#समावेश "../cxgb4/t4fw_api.h"

/*
 * Wait क्रम the device to become पढ़ोy (signअगरied by our "who am I" रेजिस्टर
 * वापसing a value other than all 1's).  Return an error if it doesn't
 * become पढ़ोy ...
 */
पूर्णांक t4vf_रुको_dev_पढ़ोy(काष्ठा adapter *adapter)
अणु
	स्थिर u32 whoami = T4VF_PL_BASE_ADDR + PL_VF_WHOAMI;
	स्थिर u32 notपढ़ोy1 = 0xffffffff;
	स्थिर u32 notपढ़ोy2 = 0xeeeeeeee;
	u32 val;

	val = t4_पढ़ो_reg(adapter, whoami);
	अगर (val != notपढ़ोy1 && val != notपढ़ोy2)
		वापस 0;
	msleep(500);
	val = t4_पढ़ो_reg(adapter, whoami);
	अगर (val != notपढ़ोy1 && val != notपढ़ोy2)
		वापस 0;
	अन्यथा
		वापस -EIO;
पूर्ण

/*
 * Get the reply to a mailbox command and store it in @rpl in big-endian order
 * (since the firmware data काष्ठाures are specअगरied in a big-endian layout).
 */
अटल व्योम get_mbox_rpl(काष्ठा adapter *adapter, __be64 *rpl, पूर्णांक size,
			 u32 mbox_data)
अणु
	क्रम ( ; size; size -= 8, mbox_data += 8)
		*rpl++ = cpu_to_be64(t4_पढ़ो_reg64(adapter, mbox_data));
पूर्ण

/**
 *	t4vf_record_mbox - record a Firmware Mailbox Command/Reply in the log
 *	@adapter: the adapter
 *	@cmd: the Firmware Mailbox Command or Reply
 *	@size: command length in bytes
 *	@access: the समय (ms) needed to access the Firmware Mailbox
 *	@execute: the समय (ms) the command spent being executed
 */
अटल व्योम t4vf_record_mbox(काष्ठा adapter *adapter, स्थिर __be64 *cmd,
			     पूर्णांक size, पूर्णांक access, पूर्णांक execute)
अणु
	काष्ठा mbox_cmd_log *log = adapter->mbox_log;
	काष्ठा mbox_cmd *entry;
	पूर्णांक i;

	entry = mbox_cmd_log_entry(log, log->cursor++);
	अगर (log->cursor == log->size)
		log->cursor = 0;

	क्रम (i = 0; i < size / 8; i++)
		entry->cmd[i] = be64_to_cpu(cmd[i]);
	जबतक (i < MBOX_LEN / 8)
		entry->cmd[i++] = 0;
	entry->बारtamp = jअगरfies;
	entry->seqno = log->seqno++;
	entry->access = access;
	entry->execute = execute;
पूर्ण

/**
 *	t4vf_wr_mbox_core - send a command to FW through the mailbox
 *	@adapter: the adapter
 *	@cmd: the command to ग_लिखो
 *	@size: command length in bytes
 *	@rpl: where to optionally store the reply
 *	@sleep_ok: अगर true we may sleep जबतक aरुकोing command completion
 *
 *	Sends the given command to FW through the mailbox and रुकोs क्रम the
 *	FW to execute the command.  If @rpl is not %शून्य it is used to store
 *	the FW's reply to the command.  The command and its optional reply
 *	are of the same length.  FW can take up to 500 ms to respond.
 *	@sleep_ok determines whether we may sleep जबतक aरुकोing the response.
 *	If sleeping is allowed we use progressive backoff otherwise we spin.
 *
 *	The वापस value is 0 on success or a negative त्रुटि_सं on failure.  A
 *	failure can happen either because we are not able to execute the
 *	command or FW executes it but संकेतs an error.  In the latter हाल
 *	the वापस value is the error code indicated by FW (negated).
 */
पूर्णांक t4vf_wr_mbox_core(काष्ठा adapter *adapter, स्थिर व्योम *cmd, पूर्णांक size,
		      व्योम *rpl, bool sleep_ok)
अणु
	अटल स्थिर पूर्णांक delay[] = अणु
		1, 1, 3, 5, 10, 10, 20, 50, 100
	पूर्ण;

	u16 access = 0, execute = 0;
	u32 v, mbox_data;
	पूर्णांक i, ms, delay_idx, ret;
	स्थिर __be64 *p;
	u32 mbox_ctl = T4VF_CIM_BASE_ADDR + CIM_VF_EXT_MAILBOX_CTRL;
	u32 cmd_op = FW_CMD_OP_G(be32_to_cpu(((काष्ठा fw_cmd_hdr *)cmd)->hi));
	__be64 cmd_rpl[MBOX_LEN / 8];
	काष्ठा mbox_list entry;

	/* In T6, mailbox size is changed to 128 bytes to aव्योम
	 * invalidating the entire prefetch buffer.
	 */
	अगर (CHELSIO_CHIP_VERSION(adapter->params.chip) <= CHELSIO_T5)
		mbox_data = T4VF_MBDATA_BASE_ADDR;
	अन्यथा
		mbox_data = T6VF_MBDATA_BASE_ADDR;

	/*
	 * Commands must be multiples of 16 bytes in length and may not be
	 * larger than the size of the Mailbox Data रेजिस्टर array.
	 */
	अगर ((size % 16) != 0 ||
	    size > NUM_CIM_VF_MAILBOX_DATA_INSTANCES * 4)
		वापस -EINVAL;

	/* Queue ourselves onto the mailbox access list.  When our entry is at
	 * the front of the list, we have rights to access the mailbox.  So we
	 * रुको [क्रम a जबतक] till we're at the front [or bail out with an
	 * EBUSY] ...
	 */
	spin_lock(&adapter->mbox_lock);
	list_add_tail(&entry.list, &adapter->mlist.list);
	spin_unlock(&adapter->mbox_lock);

	delay_idx = 0;
	ms = delay[0];

	क्रम (i = 0; ; i += ms) अणु
		/* If we've रुकोed too दीर्घ, वापस a busy indication.  This
		 * really ought to be based on our initial position in the
		 * mailbox access list but this is a start.  We very rearely
		 * contend on access to the mailbox ...
		 */
		अगर (i > FW_CMD_MAX_TIMEOUT) अणु
			spin_lock(&adapter->mbox_lock);
			list_del(&entry.list);
			spin_unlock(&adapter->mbox_lock);
			ret = -EBUSY;
			t4vf_record_mbox(adapter, cmd, size, access, ret);
			वापस ret;
		पूर्ण

		/* If we're at the head, अवरोध out and start the mailbox
		 * protocol.
		 */
		अगर (list_first_entry(&adapter->mlist.list, काष्ठा mbox_list,
				     list) == &entry)
			अवरोध;

		/* Delay क्रम a bit beक्रमe checking again ... */
		अगर (sleep_ok) अणु
			ms = delay[delay_idx];  /* last element may repeat */
			अगर (delay_idx < ARRAY_SIZE(delay) - 1)
				delay_idx++;
			msleep(ms);
		पूर्ण अन्यथा अणु
			mdelay(ms);
		पूर्ण
	पूर्ण

	/*
	 * Loop trying to get ownership of the mailbox.  Return an error
	 * अगर we can't gain ownership.
	 */
	v = MBOWNER_G(t4_पढ़ो_reg(adapter, mbox_ctl));
	क्रम (i = 0; v == MBOX_OWNER_NONE && i < 3; i++)
		v = MBOWNER_G(t4_पढ़ो_reg(adapter, mbox_ctl));
	अगर (v != MBOX_OWNER_DRV) अणु
		spin_lock(&adapter->mbox_lock);
		list_del(&entry.list);
		spin_unlock(&adapter->mbox_lock);
		ret = (v == MBOX_OWNER_FW) ? -EBUSY : -ETIMEDOUT;
		t4vf_record_mbox(adapter, cmd, size, access, ret);
		वापस ret;
	पूर्ण

	/*
	 * Write the command array पूर्णांकo the Mailbox Data रेजिस्टर array and
	 * transfer ownership of the mailbox to the firmware.
	 *
	 * For the VFs, the Mailbox Data "registers" are actually backed by
	 * T4's "MA" पूर्णांकerface rather than PL Registers (as is the हाल क्रम
	 * the PFs).  Because these are in dअगरferent coherency करोमुख्यs, the
	 * ग_लिखो to the VF's PL-रेजिस्टर-backed Mailbox Control can race in
	 * front of the ग_लिखोs to the MA-backed VF Mailbox Data "registers".
	 * So we need to करो a पढ़ो-back on at least one byte of the VF Mailbox
	 * Data रेजिस्टरs beक्रमe करोing the ग_लिखो to the VF Mailbox Control
	 * रेजिस्टर.
	 */
	अगर (cmd_op != FW_VI_STATS_CMD)
		t4vf_record_mbox(adapter, cmd, size, access, 0);
	क्रम (i = 0, p = cmd; i < size; i += 8)
		t4_ग_लिखो_reg64(adapter, mbox_data + i, be64_to_cpu(*p++));
	t4_पढ़ो_reg(adapter, mbox_data);         /* flush ग_लिखो */

	t4_ग_लिखो_reg(adapter, mbox_ctl,
		     MBMSGVALID_F | MBOWNER_V(MBOX_OWNER_FW));
	t4_पढ़ो_reg(adapter, mbox_ctl);          /* flush ग_लिखो */

	/*
	 * Spin रुकोing क्रम firmware to acknowledge processing our command.
	 */
	delay_idx = 0;
	ms = delay[0];

	क्रम (i = 0; i < FW_CMD_MAX_TIMEOUT; i += ms) अणु
		अगर (sleep_ok) अणु
			ms = delay[delay_idx];
			अगर (delay_idx < ARRAY_SIZE(delay) - 1)
				delay_idx++;
			msleep(ms);
		पूर्ण अन्यथा
			mdelay(ms);

		/*
		 * If we're the owner, see अगर this is the reply we wanted.
		 */
		v = t4_पढ़ो_reg(adapter, mbox_ctl);
		अगर (MBOWNER_G(v) == MBOX_OWNER_DRV) अणु
			/*
			 * If the Message Valid bit isn't on, revoke ownership
			 * of the mailbox and जारी रुकोing क्रम our reply.
			 */
			अगर ((v & MBMSGVALID_F) == 0) अणु
				t4_ग_लिखो_reg(adapter, mbox_ctl,
					     MBOWNER_V(MBOX_OWNER_NONE));
				जारी;
			पूर्ण

			/*
			 * We now have our reply.  Extract the command वापस
			 * value, copy the reply back to our caller's buffer
			 * (अगर specअगरied) and revoke ownership of the mailbox.
			 * We वापस the (negated) firmware command वापस
			 * code (this depends on FW_SUCCESS == 0).
			 */
			get_mbox_rpl(adapter, cmd_rpl, size, mbox_data);

			/* वापस value in low-order little-endian word */
			v = be64_to_cpu(cmd_rpl[0]);

			अगर (rpl) अणु
				/* request bit in high-order BE word */
				WARN_ON((be32_to_cpu(*(स्थिर __be32 *)cmd)
					 & FW_CMD_REQUEST_F) == 0);
				स_नकल(rpl, cmd_rpl, size);
				WARN_ON((be32_to_cpu(*(__be32 *)rpl)
					 & FW_CMD_REQUEST_F) != 0);
			पूर्ण
			t4_ग_लिखो_reg(adapter, mbox_ctl,
				     MBOWNER_V(MBOX_OWNER_NONE));
			execute = i + ms;
			अगर (cmd_op != FW_VI_STATS_CMD)
				t4vf_record_mbox(adapter, cmd_rpl, size, access,
						 execute);
			spin_lock(&adapter->mbox_lock);
			list_del(&entry.list);
			spin_unlock(&adapter->mbox_lock);
			वापस -FW_CMD_RETVAL_G(v);
		पूर्ण
	पूर्ण

	/* We समयd out.  Return the error ... */
	ret = -ETIMEDOUT;
	t4vf_record_mbox(adapter, cmd, size, access, ret);
	spin_lock(&adapter->mbox_lock);
	list_del(&entry.list);
	spin_unlock(&adapter->mbox_lock);
	वापस ret;
पूर्ण

/* In the Physical Function Driver Common Code, the ADVERT_MASK is used to
 * mask out bits in the Advertised Port Capabilities which are managed via
 * separate controls, like Pause Frames and Forward Error Correction.  In the
 * Virtual Function Common Code, since we never perक्रमm L1 Configuration on
 * the Link, the only things we really need to filter out are things which
 * we decode and report separately like Speed.
 */
#घोषणा ADVERT_MASK (FW_PORT_CAP32_SPEED_V(FW_PORT_CAP32_SPEED_M) | \
		     FW_PORT_CAP32_802_3_PAUSE | \
		     FW_PORT_CAP32_802_3_ASM_सूची | \
		     FW_PORT_CAP32_FEC_V(FW_PORT_CAP32_FEC_M) | \
		     FW_PORT_CAP32_ANEG)

/**
 *	fwcaps16_to_caps32 - convert 16-bit Port Capabilities to 32-bits
 *	@caps16: a 16-bit Port Capabilities value
 *
 *	Returns the equivalent 32-bit Port Capabilities value.
 */
अटल fw_port_cap32_t fwcaps16_to_caps32(fw_port_cap16_t caps16)
अणु
	fw_port_cap32_t caps32 = 0;

	#घोषणा CAP16_TO_CAP32(__cap) \
		करो अणु \
			अगर (caps16 & FW_PORT_CAP_##__cap) \
				caps32 |= FW_PORT_CAP32_##__cap; \
		पूर्ण जबतक (0)

	CAP16_TO_CAP32(SPEED_100M);
	CAP16_TO_CAP32(SPEED_1G);
	CAP16_TO_CAP32(SPEED_25G);
	CAP16_TO_CAP32(SPEED_10G);
	CAP16_TO_CAP32(SPEED_40G);
	CAP16_TO_CAP32(SPEED_100G);
	CAP16_TO_CAP32(FC_RX);
	CAP16_TO_CAP32(FC_TX);
	CAP16_TO_CAP32(ANEG);
	CAP16_TO_CAP32(MDIAUTO);
	CAP16_TO_CAP32(MDISTRAIGHT);
	CAP16_TO_CAP32(FEC_RS);
	CAP16_TO_CAP32(FEC_BASER_RS);
	CAP16_TO_CAP32(802_3_PAUSE);
	CAP16_TO_CAP32(802_3_ASM_सूची);

	#अघोषित CAP16_TO_CAP32

	वापस caps32;
पूर्ण

/* Translate Firmware Pause specअगरication to Common Code */
अटल अंतरभूत क्रमागत cc_छोड़ो fwcap_to_cc_छोड़ो(fw_port_cap32_t fw_छोड़ो)
अणु
	क्रमागत cc_छोड़ो cc_छोड़ो = 0;

	अगर (fw_छोड़ो & FW_PORT_CAP32_FC_RX)
		cc_छोड़ो |= PAUSE_RX;
	अगर (fw_छोड़ो & FW_PORT_CAP32_FC_TX)
		cc_छोड़ो |= PAUSE_TX;

	वापस cc_छोड़ो;
पूर्ण

/* Translate Firmware Forward Error Correction specअगरication to Common Code */
अटल अंतरभूत क्रमागत cc_fec fwcap_to_cc_fec(fw_port_cap32_t fw_fec)
अणु
	क्रमागत cc_fec cc_fec = 0;

	अगर (fw_fec & FW_PORT_CAP32_FEC_RS)
		cc_fec |= FEC_RS;
	अगर (fw_fec & FW_PORT_CAP32_FEC_BASER_RS)
		cc_fec |= FEC_BASER_RS;

	वापस cc_fec;
पूर्ण

/* Return the highest speed set in the port capabilities, in Mb/s. */
अटल अचिन्हित पूर्णांक fwcap_to_speed(fw_port_cap32_t caps)
अणु
	#घोषणा TEST_SPEED_RETURN(__caps_speed, __speed) \
		करो अणु \
			अगर (caps & FW_PORT_CAP32_SPEED_##__caps_speed) \
				वापस __speed; \
		पूर्ण जबतक (0)

	TEST_SPEED_RETURN(400G, 400000);
	TEST_SPEED_RETURN(200G, 200000);
	TEST_SPEED_RETURN(100G, 100000);
	TEST_SPEED_RETURN(50G,   50000);
	TEST_SPEED_RETURN(40G,   40000);
	TEST_SPEED_RETURN(25G,   25000);
	TEST_SPEED_RETURN(10G,   10000);
	TEST_SPEED_RETURN(1G,     1000);
	TEST_SPEED_RETURN(100M,    100);

	#अघोषित TEST_SPEED_RETURN

	वापस 0;
पूर्ण

/**
 *      fwcap_to_fwspeed - वापस highest speed in Port Capabilities
 *      @acaps: advertised Port Capabilities
 *
 *      Get the highest speed क्रम the port from the advertised Port
 *      Capabilities.  It will be either the highest speed from the list of
 *      speeds or whatever user has set using ethtool.
 */
अटल fw_port_cap32_t fwcap_to_fwspeed(fw_port_cap32_t acaps)
अणु
	#घोषणा TEST_SPEED_RETURN(__caps_speed) \
		करो अणु \
			अगर (acaps & FW_PORT_CAP32_SPEED_##__caps_speed) \
				वापस FW_PORT_CAP32_SPEED_##__caps_speed; \
		पूर्ण जबतक (0)

	TEST_SPEED_RETURN(400G);
	TEST_SPEED_RETURN(200G);
	TEST_SPEED_RETURN(100G);
	TEST_SPEED_RETURN(50G);
	TEST_SPEED_RETURN(40G);
	TEST_SPEED_RETURN(25G);
	TEST_SPEED_RETURN(10G);
	TEST_SPEED_RETURN(1G);
	TEST_SPEED_RETURN(100M);

	#अघोषित TEST_SPEED_RETURN
	वापस 0;
पूर्ण

/*
 *	init_link_config - initialize a link's SW state
 *	@lc: काष्ठाure holding the link state
 *	@pcaps: link Port Capabilities
 *	@acaps: link current Advertised Port Capabilities
 *
 *	Initializes the SW state मुख्यtained क्रम each link, including the link's
 *	capabilities and शेष speed/flow-control/स्वतःnegotiation settings.
 */
अटल व्योम init_link_config(काष्ठा link_config *lc,
			     fw_port_cap32_t pcaps,
			     fw_port_cap32_t acaps)
अणु
	lc->pcaps = pcaps;
	lc->lpacaps = 0;
	lc->speed_caps = 0;
	lc->speed = 0;
	lc->requested_fc = lc->fc = PAUSE_RX | PAUSE_TX;

	/* For Forward Error Control, we शेष to whatever the Firmware
	 * tells us the Link is currently advertising.
	 */
	lc->स्वतः_fec = fwcap_to_cc_fec(acaps);
	lc->requested_fec = FEC_AUTO;
	lc->fec = lc->स्वतः_fec;

	/* If the Port is capable of Auto-Negtotiation, initialize it as
	 * "enabled" and copy over all of the Physical Port Capabilities
	 * to the Advertised Port Capabilities.  Otherwise mark it as
	 * Auto-Negotiate disabled and select the highest supported speed
	 * क्रम the link.  Note parallel काष्ठाure in t4_link_l1cfg_core()
	 * and t4_handle_get_port_info().
	 */
	अगर (lc->pcaps & FW_PORT_CAP32_ANEG) अणु
		lc->acaps = acaps & ADVERT_MASK;
		lc->स्वतःneg = AUTONEG_ENABLE;
		lc->requested_fc |= PAUSE_AUTONEG;
	पूर्ण अन्यथा अणु
		lc->acaps = 0;
		lc->स्वतःneg = AUTONEG_DISABLE;
		lc->speed_caps = fwcap_to_fwspeed(acaps);
	पूर्ण
पूर्ण

/**
 *	t4vf_port_init - initialize port hardware/software state
 *	@adapter: the adapter
 *	@pidx: the adapter port index
 */
पूर्णांक t4vf_port_init(काष्ठा adapter *adapter, पूर्णांक pidx)
अणु
	काष्ठा port_info *pi = adap2pinfo(adapter, pidx);
	अचिन्हित पूर्णांक fw_caps = adapter->params.fw_caps_support;
	काष्ठा fw_vi_cmd vi_cmd, vi_rpl;
	काष्ठा fw_port_cmd port_cmd, port_rpl;
	क्रमागत fw_port_type port_type;
	पूर्णांक mdio_addr;
	fw_port_cap32_t pcaps, acaps;
	पूर्णांक ret;

	/* If we haven't yet determined whether we're talking to Firmware
	 * which knows the new 32-bit Port Capabilities, it's समय to find
	 * out now.  This will also tell new Firmware to send us Port Status
	 * Updates using the new 32-bit Port Capabilities version of the
	 * Port Inक्रमmation message.
	 */
	अगर (fw_caps == FW_CAPS_UNKNOWN) अणु
		u32 param, val;

		param = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_PFVF) |
			 FW_PARAMS_PARAM_X_V(FW_PARAMS_PARAM_PFVF_PORT_CAPS32));
		val = 1;
		ret = t4vf_set_params(adapter, 1, &param, &val);
		fw_caps = (ret == 0 ? FW_CAPS32 : FW_CAPS16);
		adapter->params.fw_caps_support = fw_caps;
	पूर्ण

	/*
	 * Execute a VI Read command to get our Virtual Interface inक्रमmation
	 * like MAC address, etc.
	 */
	स_रखो(&vi_cmd, 0, माप(vi_cmd));
	vi_cmd.op_to_vfn = cpu_to_be32(FW_CMD_OP_V(FW_VI_CMD) |
				       FW_CMD_REQUEST_F |
				       FW_CMD_READ_F);
	vi_cmd.alloc_to_len16 = cpu_to_be32(FW_LEN16(vi_cmd));
	vi_cmd.type_viid = cpu_to_be16(FW_VI_CMD_VIID_V(pi->viid));
	ret = t4vf_wr_mbox(adapter, &vi_cmd, माप(vi_cmd), &vi_rpl);
	अगर (ret != FW_SUCCESS)
		वापस ret;

	BUG_ON(pi->port_id != FW_VI_CMD_PORTID_G(vi_rpl.portid_pkd));
	pi->rss_size = FW_VI_CMD_RSSSIZE_G(be16_to_cpu(vi_rpl.rsssize_pkd));
	t4_os_set_hw_addr(adapter, pidx, vi_rpl.mac);

	/*
	 * If we करोn't have read access to our port information, we're करोne
	 * now.  Otherwise, execute a PORT Read command to get it ...
	 */
	अगर (!(adapter->params.vfres.r_caps & FW_CMD_CAP_PORT))
		वापस 0;

	स_रखो(&port_cmd, 0, माप(port_cmd));
	port_cmd.op_to_portid = cpu_to_be32(FW_CMD_OP_V(FW_PORT_CMD) |
					    FW_CMD_REQUEST_F |
					    FW_CMD_READ_F |
					    FW_PORT_CMD_PORTID_V(pi->port_id));
	port_cmd.action_to_len16 = cpu_to_be32(
		FW_PORT_CMD_ACTION_V(fw_caps == FW_CAPS16
				     ? FW_PORT_ACTION_GET_PORT_INFO
				     : FW_PORT_ACTION_GET_PORT_INFO32) |
		FW_LEN16(port_cmd));
	ret = t4vf_wr_mbox(adapter, &port_cmd, माप(port_cmd), &port_rpl);
	अगर (ret != FW_SUCCESS)
		वापस ret;

	/* Extract the various fields from the Port Inक्रमmation message. */
	अगर (fw_caps == FW_CAPS16) अणु
		u32 lstatus = be32_to_cpu(port_rpl.u.info.lstatus_to_modtype);

		port_type = FW_PORT_CMD_PTYPE_G(lstatus);
		mdio_addr = ((lstatus & FW_PORT_CMD_MDIOCAP_F)
			     ? FW_PORT_CMD_MDIOADDR_G(lstatus)
			     : -1);
		pcaps = fwcaps16_to_caps32(be16_to_cpu(port_rpl.u.info.pcap));
		acaps = fwcaps16_to_caps32(be16_to_cpu(port_rpl.u.info.acap));
	पूर्ण अन्यथा अणु
		u32 lstatus32 =
			   be32_to_cpu(port_rpl.u.info32.lstatus32_to_cbllen32);

		port_type = FW_PORT_CMD_PORTTYPE32_G(lstatus32);
		mdio_addr = ((lstatus32 & FW_PORT_CMD_MDIOCAP32_F)
			     ? FW_PORT_CMD_MDIOADDR32_G(lstatus32)
			     : -1);
		pcaps = be32_to_cpu(port_rpl.u.info32.pcaps32);
		acaps = be32_to_cpu(port_rpl.u.info32.acaps32);
	पूर्ण

	pi->port_type = port_type;
	pi->mdio_addr = mdio_addr;
	pi->mod_type = FW_PORT_MOD_TYPE_NA;

	init_link_config(&pi->link_cfg, pcaps, acaps);
	वापस 0;
पूर्ण

/**
 *      t4vf_fw_reset - issue a reset to FW
 *      @adapter: the adapter
 *
 *	Issues a reset command to FW.  For a Physical Function this would
 *	result in the Firmware resetting all of its state.  For a Virtual
 *	Function this just resets the state associated with the VF.
 */
पूर्णांक t4vf_fw_reset(काष्ठा adapter *adapter)
अणु
	काष्ठा fw_reset_cmd cmd;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.op_to_ग_लिखो = cpu_to_be32(FW_CMD_OP_V(FW_RESET_CMD) |
				      FW_CMD_WRITE_F);
	cmd.retval_len16 = cpu_to_be32(FW_LEN16(cmd));
	वापस t4vf_wr_mbox(adapter, &cmd, माप(cmd), शून्य);
पूर्ण

/**
 *	t4vf_query_params - query FW or device parameters
 *	@adapter: the adapter
 *	@nparams: the number of parameters
 *	@params: the parameter names
 *	@vals: the parameter values
 *
 *	Reads the values of firmware or device parameters.  Up to 7 parameters
 *	can be queried at once.
 */
अटल पूर्णांक t4vf_query_params(काष्ठा adapter *adapter, अचिन्हित पूर्णांक nparams,
			     स्थिर u32 *params, u32 *vals)
अणु
	पूर्णांक i, ret;
	काष्ठा fw_params_cmd cmd, rpl;
	काष्ठा fw_params_param *p;
	माप_प्रकार len16;

	अगर (nparams > 7)
		वापस -EINVAL;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.op_to_vfn = cpu_to_be32(FW_CMD_OP_V(FW_PARAMS_CMD) |
				    FW_CMD_REQUEST_F |
				    FW_CMD_READ_F);
	len16 = DIV_ROUND_UP(दुरत्व(काष्ठा fw_params_cmd,
				      param[nparams].mnem), 16);
	cmd.retval_len16 = cpu_to_be32(FW_CMD_LEN16_V(len16));
	क्रम (i = 0, p = &cmd.param[0]; i < nparams; i++, p++)
		p->mnem = htonl(*params++);

	ret = t4vf_wr_mbox(adapter, &cmd, माप(cmd), &rpl);
	अगर (ret == 0)
		क्रम (i = 0, p = &rpl.param[0]; i < nparams; i++, p++)
			*vals++ = be32_to_cpu(p->val);
	वापस ret;
पूर्ण

/**
 *	t4vf_set_params - sets FW or device parameters
 *	@adapter: the adapter
 *	@nparams: the number of parameters
 *	@params: the parameter names
 *	@vals: the parameter values
 *
 *	Sets the values of firmware or device parameters.  Up to 7 parameters
 *	can be specअगरied at once.
 */
पूर्णांक t4vf_set_params(काष्ठा adapter *adapter, अचिन्हित पूर्णांक nparams,
		    स्थिर u32 *params, स्थिर u32 *vals)
अणु
	पूर्णांक i;
	काष्ठा fw_params_cmd cmd;
	काष्ठा fw_params_param *p;
	माप_प्रकार len16;

	अगर (nparams > 7)
		वापस -EINVAL;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.op_to_vfn = cpu_to_be32(FW_CMD_OP_V(FW_PARAMS_CMD) |
				    FW_CMD_REQUEST_F |
				    FW_CMD_WRITE_F);
	len16 = DIV_ROUND_UP(दुरत्व(काष्ठा fw_params_cmd,
				      param[nparams]), 16);
	cmd.retval_len16 = cpu_to_be32(FW_CMD_LEN16_V(len16));
	क्रम (i = 0, p = &cmd.param[0]; i < nparams; i++, p++) अणु
		p->mnem = cpu_to_be32(*params++);
		p->val = cpu_to_be32(*vals++);
	पूर्ण

	वापस t4vf_wr_mbox(adapter, &cmd, माप(cmd), शून्य);
पूर्ण

/**
 *	t4vf_fl_pkt_align - वापस the fl packet alignment
 *	@adapter: the adapter
 *
 *	T4 has a single field to specअगरy the packing and padding boundary.
 *	T5 onwards has separate fields क्रम this and hence the alignment क्रम
 *	next packet offset is maximum of these two.  And T6 changes the
 *	Ingress Padding Boundary Shअगरt, so it's all a mess and it's best
 *	अगर we put this in low-level Common Code ...
 *
 */
पूर्णांक t4vf_fl_pkt_align(काष्ठा adapter *adapter)
अणु
	u32 sge_control, sge_control2;
	अचिन्हित पूर्णांक ingpadboundary, ingpackboundary, fl_align, ingpad_shअगरt;

	sge_control = adapter->params.sge.sge_control;

	/* T4 uses a single control field to specअगरy both the PCIe Padding and
	 * Packing Boundary.  T5 पूर्णांकroduced the ability to specअगरy these
	 * separately.  The actual Ingress Packet Data alignment boundary
	 * within Packed Buffer Mode is the maximum of these two
	 * specअगरications.  (Note that it makes no real practical sense to
	 * have the Pading Boudary be larger than the Packing Boundary but you
	 * could set the chip up that way and, in fact, legacy T4 code would
	 * end करोing this because it would initialize the Padding Boundary and
	 * leave the Packing Boundary initialized to 0 (16 bytes).)
	 * Padding Boundary values in T6 starts from 8B,
	 * where as it is 32B क्रम T4 and T5.
	 */
	अगर (CHELSIO_CHIP_VERSION(adapter->params.chip) <= CHELSIO_T5)
		ingpad_shअगरt = INGPADBOUNDARY_SHIFT_X;
	अन्यथा
		ingpad_shअगरt = T6_INGPADBOUNDARY_SHIFT_X;

	ingpadboundary = 1 << (INGPADBOUNDARY_G(sge_control) + ingpad_shअगरt);

	fl_align = ingpadboundary;
	अगर (!is_t4(adapter->params.chip)) अणु
		/* T5 has a dअगरferent पूर्णांकerpretation of one of the PCIe Packing
		 * Boundary values.
		 */
		sge_control2 = adapter->params.sge.sge_control2;
		ingpackboundary = INGPACKBOUNDARY_G(sge_control2);
		अगर (ingpackboundary == INGPACKBOUNDARY_16B_X)
			ingpackboundary = 16;
		अन्यथा
			ingpackboundary = 1 << (ingpackboundary +
						INGPACKBOUNDARY_SHIFT_X);

		fl_align = max(ingpadboundary, ingpackboundary);
	पूर्ण
	वापस fl_align;
पूर्ण

/**
 *	t4vf_bar2_sge_qregs - वापस BAR2 SGE Queue रेजिस्टर inक्रमmation
 *	@adapter: the adapter
 *	@qid: the Queue ID
 *	@qtype: the Ingress or Egress type क्रम @qid
 *	@pbar2_qoffset: BAR2 Queue Offset
 *	@pbar2_qid: BAR2 Queue ID or 0 क्रम Queue ID inferred SGE Queues
 *
 *	Returns the BAR2 SGE Queue Registers inक्रमmation associated with the
 *	indicated Absolute Queue ID.  These are passed back in वापस value
 *	poपूर्णांकers.  @qtype should be T4_BAR2_QTYPE_EGRESS क्रम Egress Queue
 *	and T4_BAR2_QTYPE_INGRESS क्रम Ingress Queues.
 *
 *	This may वापस an error which indicates that BAR2 SGE Queue
 *	रेजिस्टरs aren't available.  If an error is not वापसed, then the
 *	following values are वापसed:
 *
 *	  *@pbar2_qoffset: the BAR2 Offset of the @qid Registers
 *	  *@pbar2_qid: the BAR2 SGE Queue ID or 0 of @qid
 *
 *	If the वापसed BAR2 Queue ID is 0, then BAR2 SGE रेजिस्टरs which
 *	require the "Inferred Queue ID" ability may be used.  E.g. the
 *	Write Combining Doorbell Buffer. If the BAR2 Queue ID is not 0,
 *	then these "Inferred Queue ID" रेजिस्टर may not be used.
 */
पूर्णांक t4vf_bar2_sge_qregs(काष्ठा adapter *adapter,
			अचिन्हित पूर्णांक qid,
			क्रमागत t4_bar2_qtype qtype,
			u64 *pbar2_qoffset,
			अचिन्हित पूर्णांक *pbar2_qid)
अणु
	अचिन्हित पूर्णांक page_shअगरt, page_size, qpp_shअगरt, qpp_mask;
	u64 bar2_page_offset, bar2_qoffset;
	अचिन्हित पूर्णांक bar2_qid, bar2_qid_offset, bar2_qinferred;

	/* T4 करोesn't support BAR2 SGE Queue रेजिस्टरs.
	 */
	अगर (is_t4(adapter->params.chip))
		वापस -EINVAL;

	/* Get our SGE Page Size parameters.
	 */
	page_shअगरt = adapter->params.sge.sge_vf_hps + 10;
	page_size = 1 << page_shअगरt;

	/* Get the right Queues per Page parameters क्रम our Queue.
	 */
	qpp_shअगरt = (qtype == T4_BAR2_QTYPE_EGRESS
		     ? adapter->params.sge.sge_vf_eq_qpp
		     : adapter->params.sge.sge_vf_iq_qpp);
	qpp_mask = (1 << qpp_shअगरt) - 1;

	/* Calculate the basics of the BAR2 SGE Queue रेजिस्टर area:
	 *  o The BAR2 page the Queue रेजिस्टरs will be in.
	 *  o The BAR2 Queue ID.
	 *  o The BAR2 Queue ID Offset पूर्णांकo the BAR2 page.
	 */
	bar2_page_offset = ((u64)(qid >> qpp_shअगरt) << page_shअगरt);
	bar2_qid = qid & qpp_mask;
	bar2_qid_offset = bar2_qid * SGE_UDB_SIZE;

	/* If the BAR2 Queue ID Offset is less than the Page Size, then the
	 * hardware will infer the Absolute Queue ID simply from the ग_लिखोs to
	 * the BAR2 Queue ID Offset within the BAR2 Page (and we need to use a
	 * BAR2 Queue ID of 0 क्रम those ग_लिखोs).  Otherwise, we'll simply
	 * ग_लिखो to the first BAR2 SGE Queue Area within the BAR2 Page with
	 * the BAR2 Queue ID and the hardware will infer the Absolute Queue ID
	 * from the BAR2 Page and BAR2 Queue ID.
	 *
	 * One important censequence of this is that some BAR2 SGE रेजिस्टरs
	 * have a "Queue ID" field and we can ग_लिखो the BAR2 SGE Queue ID
	 * there.  But other रेजिस्टरs synthesize the SGE Queue ID purely
	 * from the ग_लिखोs to the रेजिस्टरs -- the Write Combined Doorbell
	 * Buffer is a good example.  These BAR2 SGE Registers are only
	 * available क्रम those BAR2 SGE Register areas where the SGE Absolute
	 * Queue ID can be inferred from simple ग_लिखोs.
	 */
	bar2_qoffset = bar2_page_offset;
	bar2_qinferred = (bar2_qid_offset < page_size);
	अगर (bar2_qinferred) अणु
		bar2_qoffset += bar2_qid_offset;
		bar2_qid = 0;
	पूर्ण

	*pbar2_qoffset = bar2_qoffset;
	*pbar2_qid = bar2_qid;
	वापस 0;
पूर्ण

अचिन्हित पूर्णांक t4vf_get_pf_from_vf(काष्ठा adapter *adapter)
अणु
	u32 whoami;

	whoami = t4_पढ़ो_reg(adapter, T4VF_PL_BASE_ADDR + PL_VF_WHOAMI_A);
	वापस (CHELSIO_CHIP_VERSION(adapter->params.chip) <= CHELSIO_T5 ?
			SOURCEPF_G(whoami) : T6_SOURCEPF_G(whoami));
पूर्ण

/**
 *	t4vf_get_sge_params - retrieve adapter Scatter gather Engine parameters
 *	@adapter: the adapter
 *
 *	Retrieves various core SGE parameters in the क्रमm of hardware SGE
 *	रेजिस्टर values.  The caller is responsible क्रम decoding these as
 *	needed.  The SGE parameters are stored in @adapter->params.sge.
 */
पूर्णांक t4vf_get_sge_params(काष्ठा adapter *adapter)
अणु
	काष्ठा sge_params *sge_params = &adapter->params.sge;
	u32 params[7], vals[7];
	पूर्णांक v;

	params[0] = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_REG) |
		     FW_PARAMS_PARAM_XYZ_V(SGE_CONTROL_A));
	params[1] = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_REG) |
		     FW_PARAMS_PARAM_XYZ_V(SGE_HOST_PAGE_SIZE_A));
	params[2] = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_REG) |
		     FW_PARAMS_PARAM_XYZ_V(SGE_FL_BUFFER_SIZE0_A));
	params[3] = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_REG) |
		     FW_PARAMS_PARAM_XYZ_V(SGE_FL_BUFFER_SIZE1_A));
	params[4] = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_REG) |
		     FW_PARAMS_PARAM_XYZ_V(SGE_TIMER_VALUE_0_AND_1_A));
	params[5] = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_REG) |
		     FW_PARAMS_PARAM_XYZ_V(SGE_TIMER_VALUE_2_AND_3_A));
	params[6] = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_REG) |
		     FW_PARAMS_PARAM_XYZ_V(SGE_TIMER_VALUE_4_AND_5_A));
	v = t4vf_query_params(adapter, 7, params, vals);
	अगर (v)
		वापस v;
	sge_params->sge_control = vals[0];
	sge_params->sge_host_page_size = vals[1];
	sge_params->sge_fl_buffer_size[0] = vals[2];
	sge_params->sge_fl_buffer_size[1] = vals[3];
	sge_params->sge_समयr_value_0_and_1 = vals[4];
	sge_params->sge_समयr_value_2_and_3 = vals[5];
	sge_params->sge_समयr_value_4_and_5 = vals[6];

	/* T4 uses a single control field to specअगरy both the PCIe Padding and
	 * Packing Boundary.  T5 पूर्णांकroduced the ability to specअगरy these
	 * separately with the Padding Boundary in SGE_CONTROL and and Packing
	 * Boundary in SGE_CONTROL2.  So क्रम T5 and later we need to grab
	 * SGE_CONTROL in order to determine how ingress packet data will be
	 * laid out in Packed Buffer Mode.  Unक्रमtunately, older versions of
	 * the firmware won't let us retrieve SGE_CONTROL2 so अगर we get a
	 * failure grabbing it we throw an error since we can't figure out the
	 * right value.
	 */
	अगर (!is_t4(adapter->params.chip)) अणु
		params[0] = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_REG) |
			     FW_PARAMS_PARAM_XYZ_V(SGE_CONTROL2_A));
		v = t4vf_query_params(adapter, 1, params, vals);
		अगर (v != FW_SUCCESS) अणु
			dev_err(adapter->pdev_dev,
				"Unable to get SGE Control2; "
				"probably old firmware.\n");
			वापस v;
		पूर्ण
		sge_params->sge_control2 = vals[0];
	पूर्ण

	params[0] = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_REG) |
		     FW_PARAMS_PARAM_XYZ_V(SGE_INGRESS_RX_THRESHOLD_A));
	params[1] = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_REG) |
		     FW_PARAMS_PARAM_XYZ_V(SGE_CONM_CTRL_A));
	v = t4vf_query_params(adapter, 2, params, vals);
	अगर (v)
		वापस v;
	sge_params->sge_ingress_rx_threshold = vals[0];
	sge_params->sge_congestion_control = vals[1];

	/* For T5 and later we want to use the new BAR2 Doorbells.
	 * Unक्रमtunately, older firmware didn't allow the this रेजिस्टर to be
	 * पढ़ो.
	 */
	अगर (!is_t4(adapter->params.chip)) अणु
		अचिन्हित पूर्णांक pf, s_hps, s_qpp;

		params[0] = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_REG) |
			     FW_PARAMS_PARAM_XYZ_V(
				     SGE_EGRESS_QUEUES_PER_PAGE_VF_A));
		params[1] = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_REG) |
			     FW_PARAMS_PARAM_XYZ_V(
				     SGE_INGRESS_QUEUES_PER_PAGE_VF_A));
		v = t4vf_query_params(adapter, 2, params, vals);
		अगर (v != FW_SUCCESS) अणु
			dev_warn(adapter->pdev_dev,
				 "Unable to get VF SGE Queues/Page; "
				 "probably old firmware.\n");
			वापस v;
		पूर्ण
		sge_params->sge_egress_queues_per_page = vals[0];
		sge_params->sge_ingress_queues_per_page = vals[1];

		/* We need the Queues/Page क्रम our VF.  This is based on the
		 * PF from which we're instantiated and is indexed in the
		 * रेजिस्टर we just पढ़ो. Do it once here so other code in
		 * the driver can just use it.
		 */
		pf = t4vf_get_pf_from_vf(adapter);
		s_hps = (HOSTPAGESIZEPF0_S +
			 (HOSTPAGESIZEPF1_S - HOSTPAGESIZEPF0_S) * pf);
		sge_params->sge_vf_hps =
			((sge_params->sge_host_page_size >> s_hps)
			 & HOSTPAGESIZEPF0_M);

		s_qpp = (QUEUESPERPAGEPF0_S +
			 (QUEUESPERPAGEPF1_S - QUEUESPERPAGEPF0_S) * pf);
		sge_params->sge_vf_eq_qpp =
			((sge_params->sge_egress_queues_per_page >> s_qpp)
			 & QUEUESPERPAGEPF0_M);
		sge_params->sge_vf_iq_qpp =
			((sge_params->sge_ingress_queues_per_page >> s_qpp)
			 & QUEUESPERPAGEPF0_M);
	पूर्ण

	वापस 0;
पूर्ण

/**
 *	t4vf_get_vpd_params - retrieve device VPD paremeters
 *	@adapter: the adapter
 *
 *	Retrives various device Vital Product Data parameters.  The parameters
 *	are stored in @adapter->params.vpd.
 */
पूर्णांक t4vf_get_vpd_params(काष्ठा adapter *adapter)
अणु
	काष्ठा vpd_params *vpd_params = &adapter->params.vpd;
	u32 params[7], vals[7];
	पूर्णांक v;

	params[0] = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_DEV) |
		     FW_PARAMS_PARAM_X_V(FW_PARAMS_PARAM_DEV_CCLK));
	v = t4vf_query_params(adapter, 1, params, vals);
	अगर (v)
		वापस v;
	vpd_params->cclk = vals[0];

	वापस 0;
पूर्ण

/**
 *	t4vf_get_dev_params - retrieve device paremeters
 *	@adapter: the adapter
 *
 *	Retrives various device parameters.  The parameters are stored in
 *	@adapter->params.dev.
 */
पूर्णांक t4vf_get_dev_params(काष्ठा adapter *adapter)
अणु
	काष्ठा dev_params *dev_params = &adapter->params.dev;
	u32 params[7], vals[7];
	पूर्णांक v;

	params[0] = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_DEV) |
		     FW_PARAMS_PARAM_X_V(FW_PARAMS_PARAM_DEV_FWREV));
	params[1] = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_DEV) |
		     FW_PARAMS_PARAM_X_V(FW_PARAMS_PARAM_DEV_TPREV));
	v = t4vf_query_params(adapter, 2, params, vals);
	अगर (v)
		वापस v;
	dev_params->fwrev = vals[0];
	dev_params->tprev = vals[1];

	वापस 0;
पूर्ण

/**
 *	t4vf_get_rss_glb_config - retrieve adapter RSS Global Configuration
 *	@adapter: the adapter
 *
 *	Retrieves global RSS mode and parameters with which we have to live
 *	and stores them in the @adapter's RSS parameters.
 */
पूर्णांक t4vf_get_rss_glb_config(काष्ठा adapter *adapter)
अणु
	काष्ठा rss_params *rss = &adapter->params.rss;
	काष्ठा fw_rss_glb_config_cmd cmd, rpl;
	पूर्णांक v;

	/*
	 * Execute an RSS Global Configuration पढ़ो command to retrieve
	 * our RSS configuration.
	 */
	स_रखो(&cmd, 0, माप(cmd));
	cmd.op_to_ग_लिखो = cpu_to_be32(FW_CMD_OP_V(FW_RSS_GLB_CONFIG_CMD) |
				      FW_CMD_REQUEST_F |
				      FW_CMD_READ_F);
	cmd.retval_len16 = cpu_to_be32(FW_LEN16(cmd));
	v = t4vf_wr_mbox(adapter, &cmd, माप(cmd), &rpl);
	अगर (v)
		वापस v;

	/*
	 * Transate the big-endian RSS Global Configuration पूर्णांकo our
	 * cpu-endian क्रमmat based on the RSS mode.  We also करो first level
	 * filtering at this poपूर्णांक to weed out modes which करोn't support
	 * VF Drivers ...
	 */
	rss->mode = FW_RSS_GLB_CONFIG_CMD_MODE_G(
			be32_to_cpu(rpl.u.manual.mode_pkd));
	चयन (rss->mode) अणु
	हाल FW_RSS_GLB_CONFIG_CMD_MODE_BASICVIRTUAL: अणु
		u32 word = be32_to_cpu(
				rpl.u.basicभव.synmapen_to_hashtoeplitz);

		rss->u.basicभव.synmapen =
			((word & FW_RSS_GLB_CONFIG_CMD_SYNMAPEN_F) != 0);
		rss->u.basicभव.syn4tupenipv6 =
			((word & FW_RSS_GLB_CONFIG_CMD_SYN4TUPENIPV6_F) != 0);
		rss->u.basicभव.syn2tupenipv6 =
			((word & FW_RSS_GLB_CONFIG_CMD_SYN2TUPENIPV6_F) != 0);
		rss->u.basicभव.syn4tupenipv4 =
			((word & FW_RSS_GLB_CONFIG_CMD_SYN4TUPENIPV4_F) != 0);
		rss->u.basicभव.syn2tupenipv4 =
			((word & FW_RSS_GLB_CONFIG_CMD_SYN2TUPENIPV4_F) != 0);

		rss->u.basicभव.ofdmapen =
			((word & FW_RSS_GLB_CONFIG_CMD_OFDMAPEN_F) != 0);

		rss->u.basicभव.tnlmapen =
			((word & FW_RSS_GLB_CONFIG_CMD_TNLMAPEN_F) != 0);
		rss->u.basicभव.tnlalllookup =
			((word  & FW_RSS_GLB_CONFIG_CMD_TNLALLLKP_F) != 0);

		rss->u.basicभव.hashtoeplitz =
			((word & FW_RSS_GLB_CONFIG_CMD_HASHTOEPLITZ_F) != 0);

		/* we need at least Tunnel Map Enable to be set */
		अगर (!rss->u.basicभव.tnlmapen)
			वापस -EINVAL;
		अवरोध;
	पूर्ण

	शेष:
		/* all unknown/unsupported RSS modes result in an error */
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *	t4vf_get_vfres - retrieve VF resource limits
 *	@adapter: the adapter
 *
 *	Retrieves configured resource limits and capabilities क्रम a भव
 *	function.  The results are stored in @adapter->vfres.
 */
पूर्णांक t4vf_get_vfres(काष्ठा adapter *adapter)
अणु
	काष्ठा vf_resources *vfres = &adapter->params.vfres;
	काष्ठा fw_pfvf_cmd cmd, rpl;
	पूर्णांक v;
	u32 word;

	/*
	 * Execute PFVF Read command to get VF resource limits; bail out early
	 * with error on command failure.
	 */
	स_रखो(&cmd, 0, माप(cmd));
	cmd.op_to_vfn = cpu_to_be32(FW_CMD_OP_V(FW_PFVF_CMD) |
				    FW_CMD_REQUEST_F |
				    FW_CMD_READ_F);
	cmd.retval_len16 = cpu_to_be32(FW_LEN16(cmd));
	v = t4vf_wr_mbox(adapter, &cmd, माप(cmd), &rpl);
	अगर (v)
		वापस v;

	/*
	 * Extract VF resource limits and वापस success.
	 */
	word = be32_to_cpu(rpl.niqflपूर्णांक_niq);
	vfres->niqflपूर्णांक = FW_PFVF_CMD_NIQFLINT_G(word);
	vfres->niq = FW_PFVF_CMD_NIQ_G(word);

	word = be32_to_cpu(rpl.type_to_neq);
	vfres->neq = FW_PFVF_CMD_NEQ_G(word);
	vfres->pmask = FW_PFVF_CMD_PMASK_G(word);

	word = be32_to_cpu(rpl.tc_to_nexactf);
	vfres->tc = FW_PFVF_CMD_TC_G(word);
	vfres->nvi = FW_PFVF_CMD_NVI_G(word);
	vfres->nexactf = FW_PFVF_CMD_NEXACTF_G(word);

	word = be32_to_cpu(rpl.r_caps_to_nethctrl);
	vfres->r_caps = FW_PFVF_CMD_R_CAPS_G(word);
	vfres->wx_caps = FW_PFVF_CMD_WX_CAPS_G(word);
	vfres->nethctrl = FW_PFVF_CMD_NETHCTRL_G(word);

	वापस 0;
पूर्ण

/**
 *	t4vf_पढ़ो_rss_vi_config - पढ़ो a VI's RSS configuration
 *	@adapter: the adapter
 *	@viid: Virtual Interface ID
 *	@config: poपूर्णांकer to host-native VI RSS Configuration buffer
 *
 *	Reads the Virtual Interface's RSS configuration inक्रमmation and
 *	translates it पूर्णांकo CPU-native क्रमmat.
 */
पूर्णांक t4vf_पढ़ो_rss_vi_config(काष्ठा adapter *adapter, अचिन्हित पूर्णांक viid,
			    जोड़ rss_vi_config *config)
अणु
	काष्ठा fw_rss_vi_config_cmd cmd, rpl;
	पूर्णांक v;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.op_to_viid = cpu_to_be32(FW_CMD_OP_V(FW_RSS_VI_CONFIG_CMD) |
				     FW_CMD_REQUEST_F |
				     FW_CMD_READ_F |
				     FW_RSS_VI_CONFIG_CMD_VIID(viid));
	cmd.retval_len16 = cpu_to_be32(FW_LEN16(cmd));
	v = t4vf_wr_mbox(adapter, &cmd, माप(cmd), &rpl);
	अगर (v)
		वापस v;

	चयन (adapter->params.rss.mode) अणु
	हाल FW_RSS_GLB_CONFIG_CMD_MODE_BASICVIRTUAL: अणु
		u32 word = be32_to_cpu(rpl.u.basicभव.शेषq_to_udpen);

		config->basicभव.ip6fourtupen =
			((word & FW_RSS_VI_CONFIG_CMD_IP6FOURTUPEN_F) != 0);
		config->basicभव.ip6twotupen =
			((word & FW_RSS_VI_CONFIG_CMD_IP6TWOTUPEN_F) != 0);
		config->basicभव.ip4fourtupen =
			((word & FW_RSS_VI_CONFIG_CMD_IP4FOURTUPEN_F) != 0);
		config->basicभव.ip4twotupen =
			((word & FW_RSS_VI_CONFIG_CMD_IP4TWOTUPEN_F) != 0);
		config->basicभव.udpen =
			((word & FW_RSS_VI_CONFIG_CMD_UDPEN_F) != 0);
		config->basicभव.शेषq =
			FW_RSS_VI_CONFIG_CMD_DEFAULTQ_G(word);
		अवरोध;
	पूर्ण

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *	t4vf_ग_लिखो_rss_vi_config - ग_लिखो a VI's RSS configuration
 *	@adapter: the adapter
 *	@viid: Virtual Interface ID
 *	@config: poपूर्णांकer to host-native VI RSS Configuration buffer
 *
 *	Write the Virtual Interface's RSS configuration inक्रमmation
 *	(translating it पूर्णांकo firmware-native क्रमmat beक्रमe writing).
 */
पूर्णांक t4vf_ग_लिखो_rss_vi_config(काष्ठा adapter *adapter, अचिन्हित पूर्णांक viid,
			     जोड़ rss_vi_config *config)
अणु
	काष्ठा fw_rss_vi_config_cmd cmd, rpl;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.op_to_viid = cpu_to_be32(FW_CMD_OP_V(FW_RSS_VI_CONFIG_CMD) |
				     FW_CMD_REQUEST_F |
				     FW_CMD_WRITE_F |
				     FW_RSS_VI_CONFIG_CMD_VIID(viid));
	cmd.retval_len16 = cpu_to_be32(FW_LEN16(cmd));
	चयन (adapter->params.rss.mode) अणु
	हाल FW_RSS_GLB_CONFIG_CMD_MODE_BASICVIRTUAL: अणु
		u32 word = 0;

		अगर (config->basicभव.ip6fourtupen)
			word |= FW_RSS_VI_CONFIG_CMD_IP6FOURTUPEN_F;
		अगर (config->basicभव.ip6twotupen)
			word |= FW_RSS_VI_CONFIG_CMD_IP6TWOTUPEN_F;
		अगर (config->basicभव.ip4fourtupen)
			word |= FW_RSS_VI_CONFIG_CMD_IP4FOURTUPEN_F;
		अगर (config->basicभव.ip4twotupen)
			word |= FW_RSS_VI_CONFIG_CMD_IP4TWOTUPEN_F;
		अगर (config->basicभव.udpen)
			word |= FW_RSS_VI_CONFIG_CMD_UDPEN_F;
		word |= FW_RSS_VI_CONFIG_CMD_DEFAULTQ_V(
				config->basicभव.शेषq);
		cmd.u.basicभव.शेषq_to_udpen = cpu_to_be32(word);
		अवरोध;
	पूर्ण

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस t4vf_wr_mbox(adapter, &cmd, माप(cmd), &rpl);
पूर्ण

/**
 *	t4vf_config_rss_range - configure a portion of the RSS mapping table
 *	@adapter: the adapter
 *	@viid: Virtual Interface of RSS Table Slice
 *	@start: starting entry in the table to ग_लिखो
 *	@n: how many table entries to ग_लिखो
 *	@rspq: values क्रम the "Response Queue" (Ingress Queue) lookup table
 *	@nrspq: number of values in @rspq
 *
 *	Programs the selected part of the VI's RSS mapping table with the
 *	provided values.  If @nrspq < @n the supplied values are used repeatedly
 *	until the full table range is populated.
 *
 *	The caller must ensure the values in @rspq are in the range 0..1023.
 */
पूर्णांक t4vf_config_rss_range(काष्ठा adapter *adapter, अचिन्हित पूर्णांक viid,
			  पूर्णांक start, पूर्णांक n, स्थिर u16 *rspq, पूर्णांक nrspq)
अणु
	स्थिर u16 *rsp = rspq;
	स्थिर u16 *rsp_end = rspq+nrspq;
	काष्ठा fw_rss_ind_tbl_cmd cmd;

	/*
	 * Initialize firmware command ढाँचा to ग_लिखो the RSS table.
	 */
	स_रखो(&cmd, 0, माप(cmd));
	cmd.op_to_viid = cpu_to_be32(FW_CMD_OP_V(FW_RSS_IND_TBL_CMD) |
				     FW_CMD_REQUEST_F |
				     FW_CMD_WRITE_F |
				     FW_RSS_IND_TBL_CMD_VIID_V(viid));
	cmd.retval_len16 = cpu_to_be32(FW_LEN16(cmd));

	/*
	 * Each firmware RSS command can accommodate up to 32 RSS Ingress
	 * Queue Identअगरiers.  These Ingress Queue IDs are packed three to
	 * a 32-bit word as 10-bit values with the upper reमुख्यing 2 bits
	 * reserved.
	 */
	जबतक (n > 0) अणु
		__be32 *qp = &cmd.iq0_to_iq2;
		पूर्णांक nq = min(n, 32);
		पूर्णांक ret;

		/*
		 * Set up the firmware RSS command header to send the next
		 * "nq" Ingress Queue IDs to the firmware.
		 */
		cmd.niqid = cpu_to_be16(nq);
		cmd.startidx = cpu_to_be16(start);

		/*
		 * "nq" more करोne क्रम the start of the next loop.
		 */
		start += nq;
		n -= nq;

		/*
		 * While there are still Ingress Queue IDs to stuff पूर्णांकo the
		 * current firmware RSS command, retrieve them from the
		 * Ingress Queue ID array and insert them पूर्णांकo the command.
		 */
		जबतक (nq > 0) अणु
			/*
			 * Grab up to the next 3 Ingress Queue IDs (wrapping
			 * around the Ingress Queue ID array अगर necessary) and
			 * insert them पूर्णांकo the firmware RSS command at the
			 * current 3-tuple position within the commad.
			 */
			u16 qbuf[3];
			u16 *qbp = qbuf;
			पूर्णांक nqbuf = min(3, nq);

			nq -= nqbuf;
			qbuf[0] = qbuf[1] = qbuf[2] = 0;
			जबतक (nqbuf) अणु
				nqbuf--;
				*qbp++ = *rsp++;
				अगर (rsp >= rsp_end)
					rsp = rspq;
			पूर्ण
			*qp++ = cpu_to_be32(FW_RSS_IND_TBL_CMD_IQ0_V(qbuf[0]) |
					    FW_RSS_IND_TBL_CMD_IQ1_V(qbuf[1]) |
					    FW_RSS_IND_TBL_CMD_IQ2_V(qbuf[2]));
		पूर्ण

		/*
		 * Send this portion of the RRS table update to the firmware;
		 * bail out on any errors.
		 */
		ret = t4vf_wr_mbox(adapter, &cmd, माप(cmd), शून्य);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

/**
 *	t4vf_alloc_vi - allocate a भव पूर्णांकerface on a port
 *	@adapter: the adapter
 *	@port_id: physical port associated with the VI
 *
 *	Allocate a new Virtual Interface and bind it to the indicated
 *	physical port.  Return the new Virtual Interface Identअगरier on
 *	success, or a [negative] error number on failure.
 */
पूर्णांक t4vf_alloc_vi(काष्ठा adapter *adapter, पूर्णांक port_id)
अणु
	काष्ठा fw_vi_cmd cmd, rpl;
	पूर्णांक v;

	/*
	 * Execute a VI command to allocate Virtual Interface and वापस its
	 * VIID.
	 */
	स_रखो(&cmd, 0, माप(cmd));
	cmd.op_to_vfn = cpu_to_be32(FW_CMD_OP_V(FW_VI_CMD) |
				    FW_CMD_REQUEST_F |
				    FW_CMD_WRITE_F |
				    FW_CMD_EXEC_F);
	cmd.alloc_to_len16 = cpu_to_be32(FW_LEN16(cmd) |
					 FW_VI_CMD_ALLOC_F);
	cmd.portid_pkd = FW_VI_CMD_PORTID_V(port_id);
	v = t4vf_wr_mbox(adapter, &cmd, माप(cmd), &rpl);
	अगर (v)
		वापस v;

	वापस FW_VI_CMD_VIID_G(be16_to_cpu(rpl.type_viid));
पूर्ण

/**
 *	t4vf_मुक्त_vi -- मुक्त a भव पूर्णांकerface
 *	@adapter: the adapter
 *	@viid: the भव पूर्णांकerface identअगरier
 *
 *	Free a previously allocated Virtual Interface.  Return an error on
 *	failure.
 */
पूर्णांक t4vf_मुक्त_vi(काष्ठा adapter *adapter, पूर्णांक viid)
अणु
	काष्ठा fw_vi_cmd cmd;

	/*
	 * Execute a VI command to मुक्त the Virtual Interface.
	 */
	स_रखो(&cmd, 0, माप(cmd));
	cmd.op_to_vfn = cpu_to_be32(FW_CMD_OP_V(FW_VI_CMD) |
				    FW_CMD_REQUEST_F |
				    FW_CMD_EXEC_F);
	cmd.alloc_to_len16 = cpu_to_be32(FW_LEN16(cmd) |
					 FW_VI_CMD_FREE_F);
	cmd.type_viid = cpu_to_be16(FW_VI_CMD_VIID_V(viid));
	वापस t4vf_wr_mbox(adapter, &cmd, माप(cmd), शून्य);
पूर्ण

/**
 *	t4vf_enable_vi - enable/disable a भव पूर्णांकerface
 *	@adapter: the adapter
 *	@viid: the Virtual Interface ID
 *	@rx_en: 1=enable Rx, 0=disable Rx
 *	@tx_en: 1=enable Tx, 0=disable Tx
 *
 *	Enables/disables a भव पूर्णांकerface.
 */
पूर्णांक t4vf_enable_vi(काष्ठा adapter *adapter, अचिन्हित पूर्णांक viid,
		   bool rx_en, bool tx_en)
अणु
	काष्ठा fw_vi_enable_cmd cmd;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.op_to_viid = cpu_to_be32(FW_CMD_OP_V(FW_VI_ENABLE_CMD) |
				     FW_CMD_REQUEST_F |
				     FW_CMD_EXEC_F |
				     FW_VI_ENABLE_CMD_VIID_V(viid));
	cmd.ien_to_len16 = cpu_to_be32(FW_VI_ENABLE_CMD_IEN_V(rx_en) |
				       FW_VI_ENABLE_CMD_EEN_V(tx_en) |
				       FW_LEN16(cmd));
	वापस t4vf_wr_mbox(adapter, &cmd, माप(cmd), शून्य);
पूर्ण

/**
 *	t4vf_enable_pi - enable/disable a Port's भव पूर्णांकerface
 *	@adapter: the adapter
 *	@pi: the Port Inक्रमmation काष्ठाure
 *	@rx_en: 1=enable Rx, 0=disable Rx
 *	@tx_en: 1=enable Tx, 0=disable Tx
 *
 *	Enables/disables a Port's भव पूर्णांकerface.  If the Virtual
 *	Interface enable/disable operation is successful, we notअगरy the
 *	OS-specअगरic code of a potential Link Status change via the OS Contract
 *	API t4vf_os_link_changed().
 */
पूर्णांक t4vf_enable_pi(काष्ठा adapter *adapter, काष्ठा port_info *pi,
		   bool rx_en, bool tx_en)
अणु
	पूर्णांक ret = t4vf_enable_vi(adapter, pi->viid, rx_en, tx_en);

	अगर (ret)
		वापस ret;
	t4vf_os_link_changed(adapter, pi->pidx,
			     rx_en && tx_en && pi->link_cfg.link_ok);
	वापस 0;
पूर्ण

/**
 *	t4vf_identअगरy_port - identअगरy a VI's port by blinking its LED
 *	@adapter: the adapter
 *	@viid: the Virtual Interface ID
 *	@nblinks: how many बार to blink LED at 2.5 Hz
 *
 *	Identअगरies a VI's port by blinking its LED.
 */
पूर्णांक t4vf_identअगरy_port(काष्ठा adapter *adapter, अचिन्हित पूर्णांक viid,
		       अचिन्हित पूर्णांक nblinks)
अणु
	काष्ठा fw_vi_enable_cmd cmd;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.op_to_viid = cpu_to_be32(FW_CMD_OP_V(FW_VI_ENABLE_CMD) |
				     FW_CMD_REQUEST_F |
				     FW_CMD_EXEC_F |
				     FW_VI_ENABLE_CMD_VIID_V(viid));
	cmd.ien_to_len16 = cpu_to_be32(FW_VI_ENABLE_CMD_LED_F |
				       FW_LEN16(cmd));
	cmd.blinkdur = cpu_to_be16(nblinks);
	वापस t4vf_wr_mbox(adapter, &cmd, माप(cmd), शून्य);
पूर्ण

/**
 *	t4vf_set_rxmode - set Rx properties of a भव पूर्णांकerface
 *	@adapter: the adapter
 *	@viid: the VI id
 *	@mtu: the new MTU or -1 क्रम no change
 *	@promisc: 1 to enable promiscuous mode, 0 to disable it, -1 no change
 *	@all_multi: 1 to enable all-multi mode, 0 to disable it, -1 no change
 *	@bcast: 1 to enable broadcast Rx, 0 to disable it, -1 no change
 *	@vlanex: 1 to enable hardware VLAN Tag extraction, 0 to disable it,
 *		-1 no change
 *	@sleep_ok: call is allowed to sleep
 *
 *	Sets Rx properties of a भव पूर्णांकerface.
 */
पूर्णांक t4vf_set_rxmode(काष्ठा adapter *adapter, अचिन्हित पूर्णांक viid,
		    पूर्णांक mtu, पूर्णांक promisc, पूर्णांक all_multi, पूर्णांक bcast, पूर्णांक vlanex,
		    bool sleep_ok)
अणु
	काष्ठा fw_vi_rxmode_cmd cmd;

	/* convert to FW values */
	अगर (mtu < 0)
		mtu = FW_VI_RXMODE_CMD_MTU_M;
	अगर (promisc < 0)
		promisc = FW_VI_RXMODE_CMD_PROMISCEN_M;
	अगर (all_multi < 0)
		all_multi = FW_VI_RXMODE_CMD_ALLMULTIEN_M;
	अगर (bcast < 0)
		bcast = FW_VI_RXMODE_CMD_BROADCASTEN_M;
	अगर (vlanex < 0)
		vlanex = FW_VI_RXMODE_CMD_VLANEXEN_M;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.op_to_viid = cpu_to_be32(FW_CMD_OP_V(FW_VI_RXMODE_CMD) |
				     FW_CMD_REQUEST_F |
				     FW_CMD_WRITE_F |
				     FW_VI_RXMODE_CMD_VIID_V(viid));
	cmd.retval_len16 = cpu_to_be32(FW_LEN16(cmd));
	cmd.mtu_to_vlanexen =
		cpu_to_be32(FW_VI_RXMODE_CMD_MTU_V(mtu) |
			    FW_VI_RXMODE_CMD_PROMISCEN_V(promisc) |
			    FW_VI_RXMODE_CMD_ALLMULTIEN_V(all_multi) |
			    FW_VI_RXMODE_CMD_BROADCASTEN_V(bcast) |
			    FW_VI_RXMODE_CMD_VLANEXEN_V(vlanex));
	वापस t4vf_wr_mbox_core(adapter, &cmd, माप(cmd), शून्य, sleep_ok);
पूर्ण

/**
 *	t4vf_alloc_mac_filt - allocates exact-match filters क्रम MAC addresses
 *	@adapter: the adapter
 *	@viid: the Virtual Interface Identअगरier
 *	@मुक्त: अगर true any existing filters क्रम this VI id are first हटाओd
 *	@naddr: the number of MAC addresses to allocate filters क्रम (up to 7)
 *	@addr: the MAC address(es)
 *	@idx: where to store the index of each allocated filter
 *	@hash: poपूर्णांकer to hash address filter biपंचांगap
 *	@sleep_ok: call is allowed to sleep
 *
 *	Allocates an exact-match filter क्रम each of the supplied addresses and
 *	sets it to the corresponding address.  If @idx is not %शून्य it should
 *	have at least @naddr entries, each of which will be set to the index of
 *	the filter allocated क्रम the corresponding MAC address.  If a filter
 *	could not be allocated क्रम an address its index is set to 0xffff.
 *	If @hash is not %शून्य addresses that fail to allocate an exact filter
 *	are hashed and update the hash filter biपंचांगap poपूर्णांकed at by @hash.
 *
 *	Returns a negative error number or the number of filters allocated.
 */
पूर्णांक t4vf_alloc_mac_filt(काष्ठा adapter *adapter, अचिन्हित पूर्णांक viid, bool मुक्त,
			अचिन्हित पूर्णांक naddr, स्थिर u8 **addr, u16 *idx,
			u64 *hash, bool sleep_ok)
अणु
	पूर्णांक offset, ret = 0;
	अचिन्हित nfilters = 0;
	अचिन्हित पूर्णांक rem = naddr;
	काष्ठा fw_vi_mac_cmd cmd, rpl;
	अचिन्हित पूर्णांक max_naddr = adapter->params.arch.mps_tcam_size;

	अगर (naddr > max_naddr)
		वापस -EINVAL;

	क्रम (offset = 0; offset < naddr; /**/) अणु
		अचिन्हित पूर्णांक fw_naddr = (rem < ARRAY_SIZE(cmd.u.exact)
					 ? rem
					 : ARRAY_SIZE(cmd.u.exact));
		माप_प्रकार len16 = DIV_ROUND_UP(दुरत्व(काष्ठा fw_vi_mac_cmd,
						     u.exact[fw_naddr]), 16);
		काष्ठा fw_vi_mac_exact *p;
		पूर्णांक i;

		स_रखो(&cmd, 0, माप(cmd));
		cmd.op_to_viid = cpu_to_be32(FW_CMD_OP_V(FW_VI_MAC_CMD) |
					     FW_CMD_REQUEST_F |
					     FW_CMD_WRITE_F |
					     (मुक्त ? FW_CMD_EXEC_F : 0) |
					     FW_VI_MAC_CMD_VIID_V(viid));
		cmd.मुक्तmacs_to_len16 =
			cpu_to_be32(FW_VI_MAC_CMD_FREEMACS_V(मुक्त) |
				    FW_CMD_LEN16_V(len16));

		क्रम (i = 0, p = cmd.u.exact; i < fw_naddr; i++, p++) अणु
			p->valid_to_idx = cpu_to_be16(
				FW_VI_MAC_CMD_VALID_F |
				FW_VI_MAC_CMD_IDX_V(FW_VI_MAC_ADD_MAC));
			स_नकल(p->macaddr, addr[offset+i], माप(p->macaddr));
		पूर्ण


		ret = t4vf_wr_mbox_core(adapter, &cmd, माप(cmd), &rpl,
					sleep_ok);
		अगर (ret && ret != -ENOMEM)
			अवरोध;

		क्रम (i = 0, p = rpl.u.exact; i < fw_naddr; i++, p++) अणु
			u16 index = FW_VI_MAC_CMD_IDX_G(
				be16_to_cpu(p->valid_to_idx));

			अगर (idx)
				idx[offset+i] =
					(index >= max_naddr
					 ? 0xffff
					 : index);
			अगर (index < max_naddr)
				nfilters++;
			अन्यथा अगर (hash)
				*hash |= (1ULL << hash_mac_addr(addr[offset+i]));
		पूर्ण

		मुक्त = false;
		offset += fw_naddr;
		rem -= fw_naddr;
	पूर्ण

	/*
	 * If there were no errors or we merely ran out of room in our MAC
	 * address arena, वापस the number of filters actually written.
	 */
	अगर (ret == 0 || ret == -ENOMEM)
		ret = nfilters;
	वापस ret;
पूर्ण

/**
 *	t4vf_मुक्त_mac_filt - मुक्तs exact-match filters of given MAC addresses
 *	@adapter: the adapter
 *	@viid: the VI id
 *	@naddr: the number of MAC addresses to allocate filters क्रम (up to 7)
 *	@addr: the MAC address(es)
 *	@sleep_ok: call is allowed to sleep
 *
 *	Frees the exact-match filter क्रम each of the supplied addresses
 *
 *	Returns a negative error number or the number of filters मुक्तd.
 */
पूर्णांक t4vf_मुक्त_mac_filt(काष्ठा adapter *adapter, अचिन्हित पूर्णांक viid,
		       अचिन्हित पूर्णांक naddr, स्थिर u8 **addr, bool sleep_ok)
अणु
	पूर्णांक offset, ret = 0;
	काष्ठा fw_vi_mac_cmd cmd;
	अचिन्हित पूर्णांक nfilters = 0;
	अचिन्हित पूर्णांक max_naddr = adapter->params.arch.mps_tcam_size;
	अचिन्हित पूर्णांक rem = naddr;

	अगर (naddr > max_naddr)
		वापस -EINVAL;

	क्रम (offset = 0; offset < (पूर्णांक)naddr ; /**/) अणु
		अचिन्हित पूर्णांक fw_naddr = (rem < ARRAY_SIZE(cmd.u.exact) ?
					 rem : ARRAY_SIZE(cmd.u.exact));
		माप_प्रकार len16 = DIV_ROUND_UP(दुरत्व(काष्ठा fw_vi_mac_cmd,
						     u.exact[fw_naddr]), 16);
		काष्ठा fw_vi_mac_exact *p;
		पूर्णांक i;

		स_रखो(&cmd, 0, माप(cmd));
		cmd.op_to_viid = cpu_to_be32(FW_CMD_OP_V(FW_VI_MAC_CMD) |
				     FW_CMD_REQUEST_F |
				     FW_CMD_WRITE_F |
				     FW_CMD_EXEC_V(0) |
				     FW_VI_MAC_CMD_VIID_V(viid));
		cmd.मुक्तmacs_to_len16 =
				cpu_to_be32(FW_VI_MAC_CMD_FREEMACS_V(0) |
					    FW_CMD_LEN16_V(len16));

		क्रम (i = 0, p = cmd.u.exact; i < (पूर्णांक)fw_naddr; i++, p++) अणु
			p->valid_to_idx = cpu_to_be16(
				FW_VI_MAC_CMD_VALID_F |
				FW_VI_MAC_CMD_IDX_V(FW_VI_MAC_MAC_BASED_FREE));
			स_नकल(p->macaddr, addr[offset+i], माप(p->macaddr));
		पूर्ण

		ret = t4vf_wr_mbox_core(adapter, &cmd, माप(cmd), &cmd,
					sleep_ok);
		अगर (ret)
			अवरोध;

		क्रम (i = 0, p = cmd.u.exact; i < fw_naddr; i++, p++) अणु
			u16 index = FW_VI_MAC_CMD_IDX_G(
						be16_to_cpu(p->valid_to_idx));

			अगर (index < max_naddr)
				nfilters++;
		पूर्ण

		offset += fw_naddr;
		rem -= fw_naddr;
	पूर्ण

	अगर (ret == 0)
		ret = nfilters;
	वापस ret;
पूर्ण

/**
 *	t4vf_change_mac - modअगरies the exact-match filter क्रम a MAC address
 *	@adapter: the adapter
 *	@viid: the Virtual Interface ID
 *	@idx: index of existing filter क्रम old value of MAC address, or -1
 *	@addr: the new MAC address value
 *	@persist: अगर idx < 0, the new MAC allocation should be persistent
 *
 *	Modअगरies an exact-match filter and sets it to the new MAC address.
 *	Note that in general it is not possible to modअगरy the value of a given
 *	filter so the generic way to modअगरy an address filter is to मुक्त the
 *	one being used by the old address value and allocate a new filter क्रम
 *	the new address value.  @idx can be -1 अगर the address is a new
 *	addition.
 *
 *	Returns a negative error number or the index of the filter with the new
 *	MAC value.
 */
पूर्णांक t4vf_change_mac(काष्ठा adapter *adapter, अचिन्हित पूर्णांक viid,
		    पूर्णांक idx, स्थिर u8 *addr, bool persist)
अणु
	पूर्णांक ret;
	काष्ठा fw_vi_mac_cmd cmd, rpl;
	काष्ठा fw_vi_mac_exact *p = &cmd.u.exact[0];
	माप_प्रकार len16 = DIV_ROUND_UP(दुरत्व(काष्ठा fw_vi_mac_cmd,
					     u.exact[1]), 16);
	अचिन्हित पूर्णांक max_mac_addr = adapter->params.arch.mps_tcam_size;

	/*
	 * If this is a new allocation, determine whether it should be
	 * persistent (across a "freemacs" operation) or not.
	 */
	अगर (idx < 0)
		idx = persist ? FW_VI_MAC_ADD_PERSIST_MAC : FW_VI_MAC_ADD_MAC;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.op_to_viid = cpu_to_be32(FW_CMD_OP_V(FW_VI_MAC_CMD) |
				     FW_CMD_REQUEST_F |
				     FW_CMD_WRITE_F |
				     FW_VI_MAC_CMD_VIID_V(viid));
	cmd.मुक्तmacs_to_len16 = cpu_to_be32(FW_CMD_LEN16_V(len16));
	p->valid_to_idx = cpu_to_be16(FW_VI_MAC_CMD_VALID_F |
				      FW_VI_MAC_CMD_IDX_V(idx));
	स_नकल(p->macaddr, addr, माप(p->macaddr));

	ret = t4vf_wr_mbox(adapter, &cmd, माप(cmd), &rpl);
	अगर (ret == 0) अणु
		p = &rpl.u.exact[0];
		ret = FW_VI_MAC_CMD_IDX_G(be16_to_cpu(p->valid_to_idx));
		अगर (ret >= max_mac_addr)
			ret = -ENOMEM;
	पूर्ण
	वापस ret;
पूर्ण

/**
 *	t4vf_set_addr_hash - program the MAC inexact-match hash filter
 *	@adapter: the adapter
 *	@viid: the Virtual Interface Identअगरier
 *	@ucast: whether the hash filter should also match unicast addresses
 *	@vec: the value to be written to the hash filter
 *	@sleep_ok: call is allowed to sleep
 *
 *	Sets the 64-bit inexact-match hash filter क्रम a भव पूर्णांकerface.
 */
पूर्णांक t4vf_set_addr_hash(काष्ठा adapter *adapter, अचिन्हित पूर्णांक viid,
		       bool ucast, u64 vec, bool sleep_ok)
अणु
	काष्ठा fw_vi_mac_cmd cmd;
	माप_प्रकार len16 = DIV_ROUND_UP(दुरत्व(काष्ठा fw_vi_mac_cmd,
					     u.exact[0]), 16);

	स_रखो(&cmd, 0, माप(cmd));
	cmd.op_to_viid = cpu_to_be32(FW_CMD_OP_V(FW_VI_MAC_CMD) |
				     FW_CMD_REQUEST_F |
				     FW_CMD_WRITE_F |
				     FW_VI_ENABLE_CMD_VIID_V(viid));
	cmd.मुक्तmacs_to_len16 = cpu_to_be32(FW_VI_MAC_CMD_HASHVECEN_F |
					    FW_VI_MAC_CMD_HASHUNIEN_V(ucast) |
					    FW_CMD_LEN16_V(len16));
	cmd.u.hash.hashvec = cpu_to_be64(vec);
	वापस t4vf_wr_mbox_core(adapter, &cmd, माप(cmd), शून्य, sleep_ok);
पूर्ण

/**
 *	t4vf_get_port_stats - collect "port" statistics
 *	@adapter: the adapter
 *	@pidx: the port index
 *	@s: the stats काष्ठाure to fill
 *
 *	Collect statistics क्रम the "port"'s Virtual Interface.
 */
पूर्णांक t4vf_get_port_stats(काष्ठा adapter *adapter, पूर्णांक pidx,
			काष्ठा t4vf_port_stats *s)
अणु
	काष्ठा port_info *pi = adap2pinfo(adapter, pidx);
	काष्ठा fw_vi_stats_vf fwstats;
	अचिन्हित पूर्णांक rem = VI_VF_NUM_STATS;
	__be64 *fwsp = (__be64 *)&fwstats;

	/*
	 * Grab the Virtual Interface statistics a chunk at a समय via mailbox
	 * commands.  We could use a Work Request and get all of them at once
	 * but that's an asynchronous पूर्णांकerface which is awkward to use.
	 */
	जबतक (rem) अणु
		अचिन्हित पूर्णांक ix = VI_VF_NUM_STATS - rem;
		अचिन्हित पूर्णांक nstats = min(6U, rem);
		काष्ठा fw_vi_stats_cmd cmd, rpl;
		माप_प्रकार len = (दुरत्व(काष्ठा fw_vi_stats_cmd, u) +
			      माप(काष्ठा fw_vi_stats_ctl));
		माप_प्रकार len16 = DIV_ROUND_UP(len, 16);
		पूर्णांक ret;

		स_रखो(&cmd, 0, माप(cmd));
		cmd.op_to_viid = cpu_to_be32(FW_CMD_OP_V(FW_VI_STATS_CMD) |
					     FW_VI_STATS_CMD_VIID_V(pi->viid) |
					     FW_CMD_REQUEST_F |
					     FW_CMD_READ_F);
		cmd.retval_len16 = cpu_to_be32(FW_CMD_LEN16_V(len16));
		cmd.u.ctl.nstats_ix =
			cpu_to_be16(FW_VI_STATS_CMD_IX_V(ix) |
				    FW_VI_STATS_CMD_NSTATS_V(nstats));
		ret = t4vf_wr_mbox_ns(adapter, &cmd, len, &rpl);
		अगर (ret)
			वापस ret;

		स_नकल(fwsp, &rpl.u.ctl.stat0, माप(__be64) * nstats);

		rem -= nstats;
		fwsp += nstats;
	पूर्ण

	/*
	 * Translate firmware statistics पूर्णांकo host native statistics.
	 */
	s->tx_bcast_bytes = be64_to_cpu(fwstats.tx_bcast_bytes);
	s->tx_bcast_frames = be64_to_cpu(fwstats.tx_bcast_frames);
	s->tx_mcast_bytes = be64_to_cpu(fwstats.tx_mcast_bytes);
	s->tx_mcast_frames = be64_to_cpu(fwstats.tx_mcast_frames);
	s->tx_ucast_bytes = be64_to_cpu(fwstats.tx_ucast_bytes);
	s->tx_ucast_frames = be64_to_cpu(fwstats.tx_ucast_frames);
	s->tx_drop_frames = be64_to_cpu(fwstats.tx_drop_frames);
	s->tx_offload_bytes = be64_to_cpu(fwstats.tx_offload_bytes);
	s->tx_offload_frames = be64_to_cpu(fwstats.tx_offload_frames);

	s->rx_bcast_bytes = be64_to_cpu(fwstats.rx_bcast_bytes);
	s->rx_bcast_frames = be64_to_cpu(fwstats.rx_bcast_frames);
	s->rx_mcast_bytes = be64_to_cpu(fwstats.rx_mcast_bytes);
	s->rx_mcast_frames = be64_to_cpu(fwstats.rx_mcast_frames);
	s->rx_ucast_bytes = be64_to_cpu(fwstats.rx_ucast_bytes);
	s->rx_ucast_frames = be64_to_cpu(fwstats.rx_ucast_frames);

	s->rx_err_frames = be64_to_cpu(fwstats.rx_err_frames);

	वापस 0;
पूर्ण

/**
 *	t4vf_iq_मुक्त - मुक्त an ingress queue and its मुक्त lists
 *	@adapter: the adapter
 *	@iqtype: the ingress queue type (FW_IQ_TYPE_FL_INT_CAP, etc.)
 *	@iqid: ingress queue ID
 *	@fl0id: FL0 queue ID or 0xffff अगर no attached FL0
 *	@fl1id: FL1 queue ID or 0xffff अगर no attached FL1
 *
 *	Frees an ingress queue and its associated मुक्त lists, अगर any.
 */
पूर्णांक t4vf_iq_मुक्त(काष्ठा adapter *adapter, अचिन्हित पूर्णांक iqtype,
		 अचिन्हित पूर्णांक iqid, अचिन्हित पूर्णांक fl0id, अचिन्हित पूर्णांक fl1id)
अणु
	काष्ठा fw_iq_cmd cmd;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.op_to_vfn = cpu_to_be32(FW_CMD_OP_V(FW_IQ_CMD) |
				    FW_CMD_REQUEST_F |
				    FW_CMD_EXEC_F);
	cmd.alloc_to_len16 = cpu_to_be32(FW_IQ_CMD_FREE_F |
					 FW_LEN16(cmd));
	cmd.type_to_iqandstindex =
		cpu_to_be32(FW_IQ_CMD_TYPE_V(iqtype));

	cmd.iqid = cpu_to_be16(iqid);
	cmd.fl0id = cpu_to_be16(fl0id);
	cmd.fl1id = cpu_to_be16(fl1id);
	वापस t4vf_wr_mbox(adapter, &cmd, माप(cmd), शून्य);
पूर्ण

/**
 *	t4vf_eth_eq_मुक्त - मुक्त an Ethernet egress queue
 *	@adapter: the adapter
 *	@eqid: egress queue ID
 *
 *	Frees an Ethernet egress queue.
 */
पूर्णांक t4vf_eth_eq_मुक्त(काष्ठा adapter *adapter, अचिन्हित पूर्णांक eqid)
अणु
	काष्ठा fw_eq_eth_cmd cmd;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.op_to_vfn = cpu_to_be32(FW_CMD_OP_V(FW_EQ_ETH_CMD) |
				    FW_CMD_REQUEST_F |
				    FW_CMD_EXEC_F);
	cmd.alloc_to_len16 = cpu_to_be32(FW_EQ_ETH_CMD_FREE_F |
					 FW_LEN16(cmd));
	cmd.eqid_pkd = cpu_to_be32(FW_EQ_ETH_CMD_EQID_V(eqid));
	वापस t4vf_wr_mbox(adapter, &cmd, माप(cmd), शून्य);
पूर्ण

/**
 *	t4vf_link_करोwn_rc_str - वापस a string क्रम a Link Down Reason Code
 *	@link_करोwn_rc: Link Down Reason Code
 *
 *	Returns a string representation of the Link Down Reason Code.
 */
अटल स्थिर अक्षर *t4vf_link_करोwn_rc_str(अचिन्हित अक्षर link_करोwn_rc)
अणु
	अटल स्थिर अक्षर * स्थिर reason[] = अणु
		"Link Down",
		"Remote Fault",
		"Auto-negotiation Failure",
		"Reserved",
		"Insufficient Airflow",
		"Unable To Determine Reason",
		"No RX Signal Detected",
		"Reserved",
	पूर्ण;

	अगर (link_करोwn_rc >= ARRAY_SIZE(reason))
		वापस "Bad Reason Code";

	वापस reason[link_करोwn_rc];
पूर्ण

/**
 *	t4vf_handle_get_port_info - process a FW reply message
 *	@pi: the port info
 *	@cmd: start of the FW message
 *
 *	Processes a GET_PORT_INFO FW reply message.
 */
अटल व्योम t4vf_handle_get_port_info(काष्ठा port_info *pi,
				      स्थिर काष्ठा fw_port_cmd *cmd)
अणु
	fw_port_cap32_t pcaps, acaps, lpacaps, linkattr;
	काष्ठा link_config *lc = &pi->link_cfg;
	काष्ठा adapter *adapter = pi->adapter;
	अचिन्हित पूर्णांक speed, fc, fec, adv_fc;
	क्रमागत fw_port_module_type mod_type;
	पूर्णांक action, link_ok, linkdnrc;
	क्रमागत fw_port_type port_type;

	/* Extract the various fields from the Port Inक्रमmation message. */
	action = FW_PORT_CMD_ACTION_G(be32_to_cpu(cmd->action_to_len16));
	चयन (action) अणु
	हाल FW_PORT_ACTION_GET_PORT_INFO: अणु
		u32 lstatus = be32_to_cpu(cmd->u.info.lstatus_to_modtype);

		link_ok = (lstatus & FW_PORT_CMD_LSTATUS_F) != 0;
		linkdnrc = FW_PORT_CMD_LINKDNRC_G(lstatus);
		port_type = FW_PORT_CMD_PTYPE_G(lstatus);
		mod_type = FW_PORT_CMD_MODTYPE_G(lstatus);
		pcaps = fwcaps16_to_caps32(be16_to_cpu(cmd->u.info.pcap));
		acaps = fwcaps16_to_caps32(be16_to_cpu(cmd->u.info.acap));
		lpacaps = fwcaps16_to_caps32(be16_to_cpu(cmd->u.info.lpacap));

		/* Unक्रमtunately the क्रमmat of the Link Status in the old
		 * 16-bit Port Inक्रमmation message isn't the same as the
		 * 16-bit Port Capabilities bitfield used everywhere अन्यथा ...
		 */
		linkattr = 0;
		अगर (lstatus & FW_PORT_CMD_RXPAUSE_F)
			linkattr |= FW_PORT_CAP32_FC_RX;
		अगर (lstatus & FW_PORT_CMD_TXPAUSE_F)
			linkattr |= FW_PORT_CAP32_FC_TX;
		अगर (lstatus & FW_PORT_CMD_LSPEED_V(FW_PORT_CAP_SPEED_100M))
			linkattr |= FW_PORT_CAP32_SPEED_100M;
		अगर (lstatus & FW_PORT_CMD_LSPEED_V(FW_PORT_CAP_SPEED_1G))
			linkattr |= FW_PORT_CAP32_SPEED_1G;
		अगर (lstatus & FW_PORT_CMD_LSPEED_V(FW_PORT_CAP_SPEED_10G))
			linkattr |= FW_PORT_CAP32_SPEED_10G;
		अगर (lstatus & FW_PORT_CMD_LSPEED_V(FW_PORT_CAP_SPEED_25G))
			linkattr |= FW_PORT_CAP32_SPEED_25G;
		अगर (lstatus & FW_PORT_CMD_LSPEED_V(FW_PORT_CAP_SPEED_40G))
			linkattr |= FW_PORT_CAP32_SPEED_40G;
		अगर (lstatus & FW_PORT_CMD_LSPEED_V(FW_PORT_CAP_SPEED_100G))
			linkattr |= FW_PORT_CAP32_SPEED_100G;

		अवरोध;
	पूर्ण

	हाल FW_PORT_ACTION_GET_PORT_INFO32: अणु
		u32 lstatus32;

		lstatus32 = be32_to_cpu(cmd->u.info32.lstatus32_to_cbllen32);
		link_ok = (lstatus32 & FW_PORT_CMD_LSTATUS32_F) != 0;
		linkdnrc = FW_PORT_CMD_LINKDNRC32_G(lstatus32);
		port_type = FW_PORT_CMD_PORTTYPE32_G(lstatus32);
		mod_type = FW_PORT_CMD_MODTYPE32_G(lstatus32);
		pcaps = be32_to_cpu(cmd->u.info32.pcaps32);
		acaps = be32_to_cpu(cmd->u.info32.acaps32);
		lpacaps = be32_to_cpu(cmd->u.info32.lpacaps32);
		linkattr = be32_to_cpu(cmd->u.info32.linkattr32);
		अवरोध;
	पूर्ण

	शेष:
		dev_err(adapter->pdev_dev, "Handle Port Information: Bad Command/Action %#x\n",
			be32_to_cpu(cmd->action_to_len16));
		वापस;
	पूर्ण

	fec = fwcap_to_cc_fec(acaps);
	adv_fc = fwcap_to_cc_छोड़ो(acaps);
	fc = fwcap_to_cc_छोड़ो(linkattr);
	speed = fwcap_to_speed(linkattr);

	अगर (mod_type != pi->mod_type) अणु
		/* When a new Transceiver Module is inserted, the Firmware
		 * will examine any Forward Error Correction parameters
		 * present in the Transceiver Module i2c EPROM and determine
		 * the supported and recommended FEC settings from those
		 * based on IEEE 802.3 standards.  We always record the
		 * IEEE 802.3 recommended "automatic" settings.
		 */
		lc->स्वतः_fec = fec;

		/* Some versions of the early T6 Firmware "cheated" when
		 * handling dअगरferent Transceiver Modules by changing the
		 * underlaying Port Type reported to the Host Drivers.  As
		 * such we need to capture whatever Port Type the Firmware
		 * sends us and record it in हाल it's dअगरferent from what we
		 * were told earlier.  Unक्रमtunately, since Firmware is
		 * क्रमever, we'll need to keep this code here क्रमever, but in
		 * later T6 Firmware it should just be an assignment of the
		 * same value alपढ़ोy recorded.
		 */
		pi->port_type = port_type;

		pi->mod_type = mod_type;
		t4vf_os_porपंचांगod_changed(adapter, pi->pidx);
	पूर्ण

	अगर (link_ok != lc->link_ok || speed != lc->speed ||
	    fc != lc->fc || adv_fc != lc->advertised_fc ||
	    fec != lc->fec) अणु
		/* something changed */
		अगर (!link_ok && lc->link_ok) अणु
			lc->link_करोwn_rc = linkdnrc;
			dev_warn_ratelimited(adapter->pdev_dev,
					     "Port %d link down, reason: %s\n",
					     pi->port_id,
					     t4vf_link_करोwn_rc_str(linkdnrc));
		पूर्ण
		lc->link_ok = link_ok;
		lc->speed = speed;
		lc->advertised_fc = adv_fc;
		lc->fc = fc;
		lc->fec = fec;

		lc->pcaps = pcaps;
		lc->lpacaps = lpacaps;
		lc->acaps = acaps & ADVERT_MASK;

		/* If we're not physically capable of Auto-Negotiation, note
		 * this as Auto-Negotiation disabled.  Otherwise, we track
		 * what Auto-Negotiation settings we have.  Note parallel
		 * काष्ठाure in init_link_config().
		 */
		अगर (!(lc->pcaps & FW_PORT_CAP32_ANEG)) अणु
			lc->स्वतःneg = AUTONEG_DISABLE;
		पूर्ण अन्यथा अगर (lc->acaps & FW_PORT_CAP32_ANEG) अणु
			lc->स्वतःneg = AUTONEG_ENABLE;
		पूर्ण अन्यथा अणु
			/* When Autoneg is disabled, user needs to set
			 * single speed.
			 * Similar to cxgb4_ethtool.c: set_link_ksettings
			 */
			lc->acaps = 0;
			lc->speed_caps = fwcap_to_speed(acaps);
			lc->स्वतःneg = AUTONEG_DISABLE;
		पूर्ण

		t4vf_os_link_changed(adapter, pi->pidx, link_ok);
	पूर्ण
पूर्ण

/**
 *	t4vf_update_port_info - retrieve and update port inक्रमmation अगर changed
 *	@pi: the port_info
 *
 *	We issue a Get Port Inक्रमmation Command to the Firmware and, अगर
 *	successful, we check to see अगर anything is dअगरferent from what we
 *	last recorded and update things accordingly.
 */
पूर्णांक t4vf_update_port_info(काष्ठा port_info *pi)
अणु
	अचिन्हित पूर्णांक fw_caps = pi->adapter->params.fw_caps_support;
	काष्ठा fw_port_cmd port_cmd;
	पूर्णांक ret;

	स_रखो(&port_cmd, 0, माप(port_cmd));
	port_cmd.op_to_portid = cpu_to_be32(FW_CMD_OP_V(FW_PORT_CMD) |
					    FW_CMD_REQUEST_F | FW_CMD_READ_F |
					    FW_PORT_CMD_PORTID_V(pi->port_id));
	port_cmd.action_to_len16 = cpu_to_be32(
		FW_PORT_CMD_ACTION_V(fw_caps == FW_CAPS16
				     ? FW_PORT_ACTION_GET_PORT_INFO
				     : FW_PORT_ACTION_GET_PORT_INFO32) |
		FW_LEN16(port_cmd));
	ret = t4vf_wr_mbox(pi->adapter, &port_cmd, माप(port_cmd),
			   &port_cmd);
	अगर (ret)
		वापस ret;
	t4vf_handle_get_port_info(pi, &port_cmd);
	वापस 0;
पूर्ण

/**
 *	t4vf_handle_fw_rpl - process a firmware reply message
 *	@adapter: the adapter
 *	@rpl: start of the firmware message
 *
 *	Processes a firmware message, such as link state change messages.
 */
पूर्णांक t4vf_handle_fw_rpl(काष्ठा adapter *adapter, स्थिर __be64 *rpl)
अणु
	स्थिर काष्ठा fw_cmd_hdr *cmd_hdr = (स्थिर काष्ठा fw_cmd_hdr *)rpl;
	u8 opcode = FW_CMD_OP_G(be32_to_cpu(cmd_hdr->hi));

	चयन (opcode) अणु
	हाल FW_PORT_CMD: अणु
		/*
		 * Link/module state change message.
		 */
		स्थिर काष्ठा fw_port_cmd *port_cmd =
			(स्थिर काष्ठा fw_port_cmd *)rpl;
		पूर्णांक action = FW_PORT_CMD_ACTION_G(
			be32_to_cpu(port_cmd->action_to_len16));
		पूर्णांक port_id, pidx;

		अगर (action != FW_PORT_ACTION_GET_PORT_INFO &&
		    action != FW_PORT_ACTION_GET_PORT_INFO32) अणु
			dev_err(adapter->pdev_dev,
				"Unknown firmware PORT reply action %x\n",
				action);
			अवरोध;
		पूर्ण

		port_id = FW_PORT_CMD_PORTID_G(
			be32_to_cpu(port_cmd->op_to_portid));
		क्रम_each_port(adapter, pidx) अणु
			काष्ठा port_info *pi = adap2pinfo(adapter, pidx);

			अगर (pi->port_id != port_id)
				जारी;
			t4vf_handle_get_port_info(pi, port_cmd);
		पूर्ण
		अवरोध;
	पूर्ण

	शेष:
		dev_err(adapter->pdev_dev, "Unknown firmware reply %X\n",
			opcode);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक t4vf_prep_adapter(काष्ठा adapter *adapter)
अणु
	पूर्णांक err;
	अचिन्हित पूर्णांक chipid;

	/* Wait क्रम the device to become पढ़ोy beक्रमe proceeding ...
	 */
	err = t4vf_रुको_dev_पढ़ोy(adapter);
	अगर (err)
		वापस err;

	/* Default port and घड़ी क्रम debugging in हाल we can't reach
	 * firmware.
	 */
	adapter->params.nports = 1;
	adapter->params.vfres.pmask = 1;
	adapter->params.vpd.cclk = 50000;

	adapter->params.chip = 0;
	चयन (CHELSIO_PCI_ID_VER(adapter->pdev->device)) अणु
	हाल CHELSIO_T4:
		adapter->params.chip |= CHELSIO_CHIP_CODE(CHELSIO_T4, 0);
		adapter->params.arch.sge_fl_db = DBPRIO_F;
		adapter->params.arch.mps_tcam_size =
				NUM_MPS_CLS_SRAM_L_INSTANCES;
		अवरोध;

	हाल CHELSIO_T5:
		chipid = REV_G(t4_पढ़ो_reg(adapter, PL_VF_REV_A));
		adapter->params.chip |= CHELSIO_CHIP_CODE(CHELSIO_T5, chipid);
		adapter->params.arch.sge_fl_db = DBPRIO_F | DBTYPE_F;
		adapter->params.arch.mps_tcam_size =
				NUM_MPS_T5_CLS_SRAM_L_INSTANCES;
		अवरोध;

	हाल CHELSIO_T6:
		chipid = REV_G(t4_पढ़ो_reg(adapter, PL_VF_REV_A));
		adapter->params.chip |= CHELSIO_CHIP_CODE(CHELSIO_T6, chipid);
		adapter->params.arch.sge_fl_db = 0;
		adapter->params.arch.mps_tcam_size =
				NUM_MPS_T5_CLS_SRAM_L_INSTANCES;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *	t4vf_get_vf_mac_acl - Get the MAC address to be set to
 *			      the VI of this VF.
 *	@adapter: The adapter
 *	@port: The port associated with vf
 *	@naddr: the number of ACL MAC addresses वापसed in addr
 *	@addr: Placeholder क्रम MAC addresses
 *
 *	Find the MAC address to be set to the VF's VI. The requested MAC address
 *	is from the host OS via callback in the PF driver.
 */
पूर्णांक t4vf_get_vf_mac_acl(काष्ठा adapter *adapter, अचिन्हित पूर्णांक port,
			अचिन्हित पूर्णांक *naddr, u8 *addr)
अणु
	काष्ठा fw_acl_mac_cmd cmd;
	पूर्णांक ret;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.op_to_vfn = cpu_to_be32(FW_CMD_OP_V(FW_ACL_MAC_CMD) |
				    FW_CMD_REQUEST_F |
				    FW_CMD_READ_F);
	cmd.en_to_len16 = cpu_to_be32((अचिन्हित पूर्णांक)FW_LEN16(cmd));
	ret = t4vf_wr_mbox(adapter, &cmd, माप(cmd), &cmd);
	अगर (ret)
		वापस ret;

	अगर (cmd.nmac < *naddr)
		*naddr = cmd.nmac;

	चयन (port) अणु
	हाल 3:
		स_नकल(addr, cmd.macaddr3, माप(cmd.macaddr3));
		अवरोध;
	हाल 2:
		स_नकल(addr, cmd.macaddr2, माप(cmd.macaddr2));
		अवरोध;
	हाल 1:
		स_नकल(addr, cmd.macaddr1, माप(cmd.macaddr1));
		अवरोध;
	हाल 0:
		स_नकल(addr, cmd.macaddr0, माप(cmd.macaddr0));
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/**
 *	t4vf_get_vf_vlan_acl - Get the VLAN ID to be set to
 *                             the VI of this VF.
 *	@adapter: The adapter
 *
 *	Find the VLAN ID to be set to the VF's VI. The requested VLAN ID
 *	is from the host OS via callback in the PF driver.
 */
पूर्णांक t4vf_get_vf_vlan_acl(काष्ठा adapter *adapter)
अणु
	काष्ठा fw_acl_vlan_cmd cmd;
	पूर्णांक vlan = 0;
	पूर्णांक ret = 0;

	cmd.op_to_vfn = htonl(FW_CMD_OP_V(FW_ACL_VLAN_CMD) |
			      FW_CMD_REQUEST_F | FW_CMD_READ_F);

	/* Note: Do not enable the ACL */
	cmd.en_to_len16 = cpu_to_be32((अचिन्हित पूर्णांक)FW_LEN16(cmd));

	ret = t4vf_wr_mbox(adapter, &cmd, माप(cmd), &cmd);

	अगर (!ret)
		vlan = be16_to_cpu(cmd.vlanid[0]);

	वापस vlan;
पूर्ण
