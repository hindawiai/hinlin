<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2017 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched/types.h>

#समावेश <media/cec-pin.h>
#समावेश "cec-pin-priv.h"

काष्ठा cec_error_inj_cmd अणु
	अचिन्हित पूर्णांक mode_offset;
	पूर्णांक arg_idx;
	स्थिर अक्षर *cmd;
पूर्ण;

अटल स्थिर काष्ठा cec_error_inj_cmd cec_error_inj_cmds[] = अणु
	अणु CEC_ERROR_INJ_RX_NACK_OFFSET, -1, "rx-nack" पूर्ण,
	अणु CEC_ERROR_INJ_RX_LOW_DRIVE_OFFSET,
	  CEC_ERROR_INJ_RX_LOW_DRIVE_ARG_IDX, "rx-low-drive" पूर्ण,
	अणु CEC_ERROR_INJ_RX_ADD_BYTE_OFFSET, -1, "rx-add-byte" पूर्ण,
	अणु CEC_ERROR_INJ_RX_REMOVE_BYTE_OFFSET, -1, "rx-remove-byte" पूर्ण,
	अणु CEC_ERROR_INJ_RX_ARB_LOST_OFFSET,
	  CEC_ERROR_INJ_RX_ARB_LOST_ARG_IDX, "rx-arb-lost" पूर्ण,

	अणु CEC_ERROR_INJ_TX_NO_EOM_OFFSET, -1, "tx-no-eom" पूर्ण,
	अणु CEC_ERROR_INJ_TX_EARLY_EOM_OFFSET, -1, "tx-early-eom" पूर्ण,
	अणु CEC_ERROR_INJ_TX_ADD_BYTES_OFFSET,
	  CEC_ERROR_INJ_TX_ADD_BYTES_ARG_IDX, "tx-add-bytes" पूर्ण,
	अणु CEC_ERROR_INJ_TX_REMOVE_BYTE_OFFSET, -1, "tx-remove-byte" पूर्ण,
	अणु CEC_ERROR_INJ_TX_SHORT_BIT_OFFSET,
	  CEC_ERROR_INJ_TX_SHORT_BIT_ARG_IDX, "tx-short-bit" पूर्ण,
	अणु CEC_ERROR_INJ_TX_LONG_BIT_OFFSET,
	  CEC_ERROR_INJ_TX_LONG_BIT_ARG_IDX, "tx-long-bit" पूर्ण,
	अणु CEC_ERROR_INJ_TX_CUSTOM_BIT_OFFSET,
	  CEC_ERROR_INJ_TX_CUSTOM_BIT_ARG_IDX, "tx-custom-bit" पूर्ण,
	अणु CEC_ERROR_INJ_TX_SHORT_START_OFFSET, -1, "tx-short-start" पूर्ण,
	अणु CEC_ERROR_INJ_TX_LONG_START_OFFSET, -1, "tx-long-start" पूर्ण,
	अणु CEC_ERROR_INJ_TX_CUSTOM_START_OFFSET, -1, "tx-custom-start" पूर्ण,
	अणु CEC_ERROR_INJ_TX_LAST_BIT_OFFSET,
	  CEC_ERROR_INJ_TX_LAST_BIT_ARG_IDX, "tx-last-bit" पूर्ण,
	अणु CEC_ERROR_INJ_TX_LOW_DRIVE_OFFSET,
	  CEC_ERROR_INJ_TX_LOW_DRIVE_ARG_IDX, "tx-low-drive" पूर्ण,
	अणु 0, -1, शून्य पूर्ण
पूर्ण;

u16 cec_pin_rx_error_inj(काष्ठा cec_pin *pin)
अणु
	u16 cmd = CEC_ERROR_INJ_OP_ANY;

	/* Only when 18 bits have been received करो we have a valid cmd */
	अगर (!(pin->error_inj[cmd] & CEC_ERROR_INJ_RX_MASK) &&
	    pin->rx_bit >= 18)
		cmd = pin->rx_msg.msg[1];
	वापस (pin->error_inj[cmd] & CEC_ERROR_INJ_RX_MASK) ? cmd :
		CEC_ERROR_INJ_OP_ANY;
पूर्ण

u16 cec_pin_tx_error_inj(काष्ठा cec_pin *pin)
अणु
	u16 cmd = CEC_ERROR_INJ_OP_ANY;

	अगर (!(pin->error_inj[cmd] & CEC_ERROR_INJ_TX_MASK) &&
	    pin->tx_msg.len > 1)
		cmd = pin->tx_msg.msg[1];
	वापस (pin->error_inj[cmd] & CEC_ERROR_INJ_TX_MASK) ? cmd :
		CEC_ERROR_INJ_OP_ANY;
पूर्ण

bool cec_pin_error_inj_parse_line(काष्ठा cec_adapter *adap, अक्षर *line)
अणु
	अटल स्थिर अक्षर *delims = " \t\r";
	काष्ठा cec_pin *pin = adap->pin;
	अचिन्हित पूर्णांक i;
	bool has_pos = false;
	अक्षर *p = line;
	अक्षर *token;
	अक्षर *comma;
	u64 *error;
	u8 *args;
	bool has_op;
	u8 op;
	u8 mode;
	u8 pos;

	p = skip_spaces(p);
	token = strsep(&p, delims);
	अगर (!म_भेद(token, "clear")) अणु
		स_रखो(pin->error_inj, 0, माप(pin->error_inj));
		pin->rx_toggle = pin->tx_toggle = false;
		pin->tx_ignore_nack_until_eom = false;
		pin->tx_custom_pulse = false;
		pin->tx_custom_low_usecs = CEC_TIM_CUSTOM_DEFAULT;
		pin->tx_custom_high_usecs = CEC_TIM_CUSTOM_DEFAULT;
		वापस true;
	पूर्ण
	अगर (!म_भेद(token, "rx-clear")) अणु
		क्रम (i = 0; i <= CEC_ERROR_INJ_OP_ANY; i++)
			pin->error_inj[i] &= ~CEC_ERROR_INJ_RX_MASK;
		pin->rx_toggle = false;
		वापस true;
	पूर्ण
	अगर (!म_भेद(token, "tx-clear")) अणु
		क्रम (i = 0; i <= CEC_ERROR_INJ_OP_ANY; i++)
			pin->error_inj[i] &= ~CEC_ERROR_INJ_TX_MASK;
		pin->tx_toggle = false;
		pin->tx_ignore_nack_until_eom = false;
		pin->tx_custom_pulse = false;
		pin->tx_custom_low_usecs = CEC_TIM_CUSTOM_DEFAULT;
		pin->tx_custom_high_usecs = CEC_TIM_CUSTOM_DEFAULT;
		वापस true;
	पूर्ण
	अगर (!म_भेद(token, "tx-ignore-nack-until-eom")) अणु
		pin->tx_ignore_nack_until_eom = true;
		वापस true;
	पूर्ण
	अगर (!म_भेद(token, "tx-custom-pulse")) अणु
		pin->tx_custom_pulse = true;
		cec_pin_start_समयr(pin);
		वापस true;
	पूर्ण
	अगर (!p)
		वापस false;

	p = skip_spaces(p);
	अगर (!म_भेद(token, "tx-custom-low-usecs")) अणु
		u32 usecs;

		अगर (kstrtou32(p, 0, &usecs) || usecs > 10000000)
			वापस false;
		pin->tx_custom_low_usecs = usecs;
		वापस true;
	पूर्ण
	अगर (!म_भेद(token, "tx-custom-high-usecs")) अणु
		u32 usecs;

		अगर (kstrtou32(p, 0, &usecs) || usecs > 10000000)
			वापस false;
		pin->tx_custom_high_usecs = usecs;
		वापस true;
	पूर्ण

	comma = म_अक्षर(token, ',');
	अगर (comma)
		*comma++ = '\0';
	अगर (!म_भेद(token, "any")) अणु
		has_op = false;
		error = pin->error_inj + CEC_ERROR_INJ_OP_ANY;
		args = pin->error_inj_args[CEC_ERROR_INJ_OP_ANY];
	पूर्ण अन्यथा अगर (!kstrtou8(token, 0, &op)) अणु
		has_op = true;
		error = pin->error_inj + op;
		args = pin->error_inj_args[op];
	पूर्ण अन्यथा अणु
		वापस false;
	पूर्ण

	mode = CEC_ERROR_INJ_MODE_ONCE;
	अगर (comma) अणु
		अगर (!म_भेद(comma, "off"))
			mode = CEC_ERROR_INJ_MODE_OFF;
		अन्यथा अगर (!म_भेद(comma, "once"))
			mode = CEC_ERROR_INJ_MODE_ONCE;
		अन्यथा अगर (!म_भेद(comma, "always"))
			mode = CEC_ERROR_INJ_MODE_ALWAYS;
		अन्यथा अगर (!म_भेद(comma, "toggle"))
			mode = CEC_ERROR_INJ_MODE_TOGGLE;
		अन्यथा
			वापस false;
	पूर्ण

	token = strsep(&p, delims);
	अगर (p) अणु
		p = skip_spaces(p);
		has_pos = !kstrtou8(p, 0, &pos);
	पूर्ण

	अगर (!म_भेद(token, "clear")) अणु
		*error = 0;
		वापस true;
	पूर्ण
	अगर (!म_भेद(token, "rx-clear")) अणु
		*error &= ~CEC_ERROR_INJ_RX_MASK;
		वापस true;
	पूर्ण
	अगर (!म_भेद(token, "tx-clear")) अणु
		*error &= ~CEC_ERROR_INJ_TX_MASK;
		वापस true;
	पूर्ण

	क्रम (i = 0; cec_error_inj_cmds[i].cmd; i++) अणु
		स्थिर अक्षर *cmd = cec_error_inj_cmds[i].cmd;
		अचिन्हित पूर्णांक mode_offset;
		u64 mode_mask;
		पूर्णांक arg_idx;
		bool is_bit_pos = true;

		अगर (म_भेद(token, cmd))
			जारी;

		mode_offset = cec_error_inj_cmds[i].mode_offset;
		mode_mask = CEC_ERROR_INJ_MODE_MASK << mode_offset;
		arg_idx = cec_error_inj_cmds[i].arg_idx;

		अगर (mode_offset == CEC_ERROR_INJ_RX_ARB_LOST_OFFSET) अणु
			अगर (has_op)
				वापस false;
			अगर (!has_pos)
				pos = 0x0f;
			is_bit_pos = false;
		पूर्ण अन्यथा अगर (mode_offset == CEC_ERROR_INJ_TX_ADD_BYTES_OFFSET) अणु
			अगर (!has_pos || !pos)
				वापस false;
			is_bit_pos = false;
		पूर्ण

		अगर (arg_idx >= 0 && is_bit_pos) अणु
			अगर (!has_pos || pos >= 160)
				वापस false;
			अगर (has_op && pos < 10 + 8)
				वापस false;
			/* Invalid bit position may not be the Ack bit */
			अगर ((mode_offset == CEC_ERROR_INJ_TX_SHORT_BIT_OFFSET ||
			     mode_offset == CEC_ERROR_INJ_TX_LONG_BIT_OFFSET ||
			     mode_offset == CEC_ERROR_INJ_TX_CUSTOM_BIT_OFFSET) &&
			    (pos % 10) == 9)
				वापस false;
		पूर्ण
		*error &= ~mode_mask;
		*error |= (u64)mode << mode_offset;
		अगर (arg_idx >= 0)
			args[arg_idx] = pos;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम cec_pin_show_cmd(काष्ठा seq_file *sf, u32 cmd, u8 mode)
अणु
	अगर (cmd == CEC_ERROR_INJ_OP_ANY)
		seq_माला_दो(sf, "any,");
	अन्यथा
		seq_म_लिखो(sf, "0x%02x,", cmd);
	चयन (mode) अणु
	हाल CEC_ERROR_INJ_MODE_ONCE:
		seq_माला_दो(sf, "once ");
		अवरोध;
	हाल CEC_ERROR_INJ_MODE_ALWAYS:
		seq_माला_दो(sf, "always ");
		अवरोध;
	हाल CEC_ERROR_INJ_MODE_TOGGLE:
		seq_माला_दो(sf, "toggle ");
		अवरोध;
	शेष:
		seq_माला_दो(sf, "off ");
		अवरोध;
	पूर्ण
पूर्ण

पूर्णांक cec_pin_error_inj_show(काष्ठा cec_adapter *adap, काष्ठा seq_file *sf)
अणु
	काष्ठा cec_pin *pin = adap->pin;
	अचिन्हित पूर्णांक i, j;

	seq_माला_दो(sf, "# Clear error injections:\n");
	seq_माला_दो(sf, "#   clear          clear all rx and tx error injections\n");
	seq_माला_दो(sf, "#   rx-clear       clear all rx error injections\n");
	seq_माला_दो(sf, "#   tx-clear       clear all tx error injections\n");
	seq_माला_दो(sf, "#   <op> clear     clear all rx and tx error injections for <op>\n");
	seq_माला_दो(sf, "#   <op> rx-clear  clear all rx error injections for <op>\n");
	seq_माला_दो(sf, "#   <op> tx-clear  clear all tx error injections for <op>\n");
	seq_माला_दो(sf, "#\n");
	seq_माला_दो(sf, "# RX error injection:\n");
	seq_माला_दो(sf, "#   <op>[,<mode>] rx-nack              NACK the message instead of sending an ACK\n");
	seq_माला_दो(sf, "#   <op>[,<mode>] rx-low-drive <bit>   force a low-drive condition at this bit position\n");
	seq_माला_दो(sf, "#   <op>[,<mode>] rx-add-byte          add a spurious byte to the received CEC message\n");
	seq_माला_दो(sf, "#   <op>[,<mode>] rx-remove-byte       remove the last byte from the received CEC message\n");
	seq_माला_दो(sf, "#    any[,<mode>] rx-arb-lost [<poll>] generate a POLL message to trigger an arbitration lost\n");
	seq_माला_दो(sf, "#\n");
	seq_माला_दो(sf, "# TX error injection settings:\n");
	seq_माला_दो(sf, "#   tx-ignore-nack-until-eom           ignore early NACKs until EOM\n");
	seq_माला_दो(sf, "#   tx-custom-low-usecs <usecs>        define the 'low' time for the custom pulse\n");
	seq_माला_दो(sf, "#   tx-custom-high-usecs <usecs>       define the 'high' time for the custom pulse\n");
	seq_माला_दो(sf, "#   tx-custom-pulse                    transmit the custom pulse once the bus is idle\n");
	seq_माला_दो(sf, "#\n");
	seq_माला_दो(sf, "# TX error injection:\n");
	seq_माला_दो(sf, "#   <op>[,<mode>] tx-no-eom            don't set the EOM bit\n");
	seq_माला_दो(sf, "#   <op>[,<mode>] tx-early-eom         set the EOM bit one byte too soon\n");
	seq_माला_दो(sf, "#   <op>[,<mode>] tx-add-bytes <num>   append <num> (1-255) spurious bytes to the message\n");
	seq_माला_दो(sf, "#   <op>[,<mode>] tx-remove-byte       drop the last byte from the message\n");
	seq_माला_दो(sf, "#   <op>[,<mode>] tx-short-bit <bit>   make this bit shorter than allowed\n");
	seq_माला_दो(sf, "#   <op>[,<mode>] tx-long-bit <bit>    make this bit longer than allowed\n");
	seq_माला_दो(sf, "#   <op>[,<mode>] tx-custom-bit <bit>  send the custom pulse instead of this bit\n");
	seq_माला_दो(sf, "#   <op>[,<mode>] tx-short-start       send a start pulse that's too short\n");
	seq_माला_दो(sf, "#   <op>[,<mode>] tx-long-start        send a start pulse that's too long\n");
	seq_माला_दो(sf, "#   <op>[,<mode>] tx-custom-start      send the custom pulse instead of the start pulse\n");
	seq_माला_दो(sf, "#   <op>[,<mode>] tx-last-bit <bit>    stop sending after this bit\n");
	seq_माला_दो(sf, "#   <op>[,<mode>] tx-low-drive <bit>   force a low-drive condition at this bit position\n");
	seq_माला_दो(sf, "#\n");
	seq_माला_दो(sf, "# <op>       CEC message opcode (0-255) or 'any'\n");
	seq_माला_दो(sf, "# <mode>     'once' (default), 'always', 'toggle' or 'off'\n");
	seq_माला_दो(sf, "# <bit>      CEC message bit (0-159)\n");
	seq_माला_दो(sf, "#            10 bits per 'byte': bits 0-7: data, bit 8: EOM, bit 9: ACK\n");
	seq_माला_दो(sf, "# <poll>     CEC poll message used to test arbitration lost (0x00-0xff, default 0x0f)\n");
	seq_माला_दो(sf, "# <usecs>    microseconds (0-10000000, default 1000)\n");

	seq_माला_दो(sf, "\nclear\n");

	क्रम (i = 0; i < ARRAY_SIZE(pin->error_inj); i++) अणु
		u64 e = pin->error_inj[i];

		क्रम (j = 0; cec_error_inj_cmds[j].cmd; j++) अणु
			स्थिर अक्षर *cmd = cec_error_inj_cmds[j].cmd;
			अचिन्हित पूर्णांक mode;
			अचिन्हित पूर्णांक mode_offset;
			पूर्णांक arg_idx;

			mode_offset = cec_error_inj_cmds[j].mode_offset;
			arg_idx = cec_error_inj_cmds[j].arg_idx;
			mode = (e >> mode_offset) & CEC_ERROR_INJ_MODE_MASK;
			अगर (!mode)
				जारी;
			cec_pin_show_cmd(sf, i, mode);
			seq_माला_दो(sf, cmd);
			अगर (arg_idx >= 0)
				seq_म_लिखो(sf, " %u",
					   pin->error_inj_args[i][arg_idx]);
			seq_माला_दो(sf, "\n");
		पूर्ण
	पूर्ण

	अगर (pin->tx_ignore_nack_until_eom)
		seq_माला_दो(sf, "tx-ignore-nack-until-eom\n");
	अगर (pin->tx_custom_pulse)
		seq_माला_दो(sf, "tx-custom-pulse\n");
	अगर (pin->tx_custom_low_usecs != CEC_TIM_CUSTOM_DEFAULT)
		seq_म_लिखो(sf, "tx-custom-low-usecs %u\n",
			   pin->tx_custom_low_usecs);
	अगर (pin->tx_custom_high_usecs != CEC_TIM_CUSTOM_DEFAULT)
		seq_म_लिखो(sf, "tx-custom-high-usecs %u\n",
			   pin->tx_custom_high_usecs);
	वापस 0;
पूर्ण
