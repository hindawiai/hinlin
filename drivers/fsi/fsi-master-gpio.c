<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * A FSI master controller, using a simple GPIO bit-banging पूर्णांकerface
 */

#समावेश <linux/crc4.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/fsi.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/पन.स>
#समावेश <linux/irqflags.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश "fsi-master.h"

#घोषणा	FSI_GPIO_STD_DLY	1	/* Standard pin delay in nS */
#घोषणा LAST_ADDR_INVALID		0x1

काष्ठा fsi_master_gpio अणु
	काष्ठा fsi_master	master;
	काष्ठा device		*dev;
	काष्ठा mutex		cmd_lock;	/* mutex क्रम command ordering */
	काष्ठा gpio_desc	*gpio_clk;
	काष्ठा gpio_desc	*gpio_data;
	काष्ठा gpio_desc	*gpio_trans;	/* Voltage translator */
	काष्ठा gpio_desc	*gpio_enable;	/* FSI enable */
	काष्ठा gpio_desc	*gpio_mux;	/* Mux control */
	bool			बाह्यal_mode;
	bool			no_delays;
	uपूर्णांक32_t		last_addr;
	uपूर्णांक8_t			t_send_delay;
	uपूर्णांक8_t			t_echo_delay;
पूर्ण;

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/fsi_master_gpपन.स>

#घोषणा to_fsi_master_gpio(m) container_of(m, काष्ठा fsi_master_gpio, master)

काष्ठा fsi_gpio_msg अणु
	uपूर्णांक64_t	msg;
	uपूर्णांक8_t		bits;
पूर्ण;

अटल व्योम घड़ी_प्रकारoggle(काष्ठा fsi_master_gpio *master, पूर्णांक count)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < count; i++) अणु
		अगर (!master->no_delays)
			ndelay(FSI_GPIO_STD_DLY);
		gpiod_set_value(master->gpio_clk, 0);
		अगर (!master->no_delays)
			ndelay(FSI_GPIO_STD_DLY);
		gpiod_set_value(master->gpio_clk, 1);
	पूर्ण
पूर्ण

अटल पूर्णांक sda_घड़ी_in(काष्ठा fsi_master_gpio *master)
अणु
	पूर्णांक in;

	अगर (!master->no_delays)
		ndelay(FSI_GPIO_STD_DLY);
	gpiod_set_value(master->gpio_clk, 0);

	/* Dummy पढ़ो to feed the synchronizers */
	gpiod_get_value(master->gpio_data);

	/* Actual data पढ़ो */
	in = gpiod_get_value(master->gpio_data);
	अगर (!master->no_delays)
		ndelay(FSI_GPIO_STD_DLY);
	gpiod_set_value(master->gpio_clk, 1);
	वापस in ? 1 : 0;
पूर्ण

अटल व्योम sda_out(काष्ठा fsi_master_gpio *master, पूर्णांक value)
अणु
	gpiod_set_value(master->gpio_data, value);
पूर्ण

अटल व्योम set_sda_input(काष्ठा fsi_master_gpio *master)
अणु
	gpiod_direction_input(master->gpio_data);
	gpiod_set_value(master->gpio_trans, 0);
पूर्ण

अटल व्योम set_sda_output(काष्ठा fsi_master_gpio *master, पूर्णांक value)
अणु
	gpiod_set_value(master->gpio_trans, 1);
	gpiod_direction_output(master->gpio_data, value);
पूर्ण

अटल व्योम घड़ी_zeros(काष्ठा fsi_master_gpio *master, पूर्णांक count)
अणु
	trace_fsi_master_gpio_घड़ी_zeros(master, count);
	set_sda_output(master, 1);
	घड़ी_प्रकारoggle(master, count);
पूर्ण

अटल व्योम echo_delay(काष्ठा fsi_master_gpio *master)
अणु
	घड़ी_zeros(master, master->t_echo_delay);
पूर्ण


अटल व्योम serial_in(काष्ठा fsi_master_gpio *master, काष्ठा fsi_gpio_msg *msg,
			uपूर्णांक8_t num_bits)
अणु
	uपूर्णांक8_t bit, in_bit;

	set_sda_input(master);

	क्रम (bit = 0; bit < num_bits; bit++) अणु
		in_bit = sda_घड़ी_in(master);
		msg->msg <<= 1;
		msg->msg |= ~in_bit & 0x1;	/* Data is active low */
	पूर्ण
	msg->bits += num_bits;

	trace_fsi_master_gpio_in(master, num_bits, msg->msg);
पूर्ण

अटल व्योम serial_out(काष्ठा fsi_master_gpio *master,
			स्थिर काष्ठा fsi_gpio_msg *cmd)
अणु
	uपूर्णांक8_t bit;
	uपूर्णांक64_t msg = ~cmd->msg;	/* Data is active low */
	uपूर्णांक64_t sda_mask = 0x1ULL << (cmd->bits - 1);
	uपूर्णांक64_t last_bit = ~0;
	पूर्णांक next_bit;

	trace_fsi_master_gpio_out(master, cmd->bits, cmd->msg);

	अगर (!cmd->bits) अणु
		dev_warn(master->dev, "trying to output 0 bits\n");
		वापस;
	पूर्ण
	set_sda_output(master, 0);

	/* Send the start bit */
	sda_out(master, 0);
	घड़ी_प्रकारoggle(master, 1);

	/* Send the message */
	क्रम (bit = 0; bit < cmd->bits; bit++) अणु
		next_bit = (msg & sda_mask) >> (cmd->bits - 1);
		अगर (last_bit ^ next_bit) अणु
			sda_out(master, next_bit);
			last_bit = next_bit;
		पूर्ण
		घड़ी_प्रकारoggle(master, 1);
		msg <<= 1;
	पूर्ण
पूर्ण

अटल व्योम msg_push_bits(काष्ठा fsi_gpio_msg *msg, uपूर्णांक64_t data, पूर्णांक bits)
अणु
	msg->msg <<= bits;
	msg->msg |= data & ((1ull << bits) - 1);
	msg->bits += bits;
पूर्ण

अटल व्योम msg_push_crc(काष्ठा fsi_gpio_msg *msg)
अणु
	uपूर्णांक8_t crc;
	पूर्णांक top;

	top = msg->bits & 0x3;

	/* start bit, and any non-aligned top bits */
	crc = crc4(0, 1 << top | msg->msg >> (msg->bits - top), top + 1);

	/* aligned bits */
	crc = crc4(crc, msg->msg, msg->bits - top);

	msg_push_bits(msg, crc, 4);
पूर्ण

अटल bool check_same_address(काष्ठा fsi_master_gpio *master, पूर्णांक id,
		uपूर्णांक32_t addr)
अणु
	/* this will also handle LAST_ADDR_INVALID */
	वापस master->last_addr == (((id & 0x3) << 21) | (addr & ~0x3));
पूर्ण

अटल bool check_relative_address(काष्ठा fsi_master_gpio *master, पूर्णांक id,
		uपूर्णांक32_t addr, uपूर्णांक32_t *rel_addrp)
अणु
	uपूर्णांक32_t last_addr = master->last_addr;
	पूर्णांक32_t rel_addr;

	अगर (last_addr == LAST_ADDR_INVALID)
		वापस false;

	/* We may be in 23-bit addressing mode, which uses the id as the
	 * top two address bits. So, अगर we're referencing a dअगरferent ID,
	 * use असलolute addresses.
	 */
	अगर (((last_addr >> 21) & 0x3) != id)
		वापस false;

	/* हटाओ the top two bits from any 23-bit addressing */
	last_addr &= (1 << 21) - 1;

	/* We know that the addresses are limited to 21 bits, so this won't
	 * overflow the चिन्हित rel_addr */
	rel_addr = addr - last_addr;
	अगर (rel_addr > 255 || rel_addr < -256)
		वापस false;

	*rel_addrp = (uपूर्णांक32_t)rel_addr;

	वापस true;
पूर्ण

अटल व्योम last_address_update(काष्ठा fsi_master_gpio *master,
		पूर्णांक id, bool valid, uपूर्णांक32_t addr)
अणु
	अगर (!valid)
		master->last_addr = LAST_ADDR_INVALID;
	अन्यथा
		master->last_addr = ((id & 0x3) << 21) | (addr & ~0x3);
पूर्ण

/*
 * Encode an Absolute/Relative/Same Address command
 */
अटल व्योम build_ar_command(काष्ठा fsi_master_gpio *master,
		काष्ठा fsi_gpio_msg *cmd, uपूर्णांक8_t id,
		uपूर्णांक32_t addr, माप_प्रकार size, स्थिर व्योम *data)
अणु
	पूर्णांक i, addr_bits, opcode_bits;
	bool ग_लिखो = !!data;
	uपूर्णांक8_t ds, opcode;
	uपूर्णांक32_t rel_addr;

	cmd->bits = 0;
	cmd->msg = 0;

	/* we have 21 bits of address max */
	addr &= ((1 << 21) - 1);

	/* cmd opcodes are variable length - SAME_AR is only two bits */
	opcode_bits = 3;

	अगर (check_same_address(master, id, addr)) अणु
		/* we still address the byte offset within the word */
		addr_bits = 2;
		opcode_bits = 2;
		opcode = FSI_CMD_SAME_AR;
		trace_fsi_master_gpio_cmd_same_addr(master);

	पूर्ण अन्यथा अगर (check_relative_address(master, id, addr, &rel_addr)) अणु
		/* 8 bits plus sign */
		addr_bits = 9;
		addr = rel_addr;
		opcode = FSI_CMD_REL_AR;
		trace_fsi_master_gpio_cmd_rel_addr(master, rel_addr);

	पूर्ण अन्यथा अणु
		addr_bits = 21;
		opcode = FSI_CMD_ABS_AR;
		trace_fsi_master_gpio_cmd_असल_addr(master, addr);
	पूर्ण

	/*
	 * The पढ़ो/ग_लिखो size is encoded in the lower bits of the address
	 * (as it must be naturally-aligned), and the following ds bit.
	 *
	 *	size	addr:1	addr:0	ds
	 *	1	x	x	0
	 *	2	x	0	1
	 *	4	0	1	1
	 *
	 */
	ds = size > 1 ? 1 : 0;
	addr &= ~(size - 1);
	अगर (size == 4)
		addr |= 1;

	msg_push_bits(cmd, id, 2);
	msg_push_bits(cmd, opcode, opcode_bits);
	msg_push_bits(cmd, ग_लिखो ? 0 : 1, 1);
	msg_push_bits(cmd, addr, addr_bits);
	msg_push_bits(cmd, ds, 1);
	क्रम (i = 0; ग_लिखो && i < size; i++)
		msg_push_bits(cmd, ((uपूर्णांक8_t *)data)[i], 8);

	msg_push_crc(cmd);
पूर्ण

अटल व्योम build_dpoll_command(काष्ठा fsi_gpio_msg *cmd, uपूर्णांक8_t slave_id)
अणु
	cmd->bits = 0;
	cmd->msg = 0;

	msg_push_bits(cmd, slave_id, 2);
	msg_push_bits(cmd, FSI_CMD_DPOLL, 3);
	msg_push_crc(cmd);
पूर्ण

अटल व्योम build_epoll_command(काष्ठा fsi_gpio_msg *cmd, uपूर्णांक8_t slave_id)
अणु
	cmd->bits = 0;
	cmd->msg = 0;

	msg_push_bits(cmd, slave_id, 2);
	msg_push_bits(cmd, FSI_CMD_EPOLL, 3);
	msg_push_crc(cmd);
पूर्ण

अटल व्योम build_term_command(काष्ठा fsi_gpio_msg *cmd, uपूर्णांक8_t slave_id)
अणु
	cmd->bits = 0;
	cmd->msg = 0;

	msg_push_bits(cmd, slave_id, 2);
	msg_push_bits(cmd, FSI_CMD_TERM, 6);
	msg_push_crc(cmd);
पूर्ण

/*
 * Note: callers rely specअगरically on this वापसing -EAGAIN क्रम
 * a CRC error detected in the response. Use other error code
 * क्रम other situations. It will be converted to something अन्यथा
 * higher up the stack beक्रमe it reaches userspace.
 */
अटल पूर्णांक पढ़ो_one_response(काष्ठा fsi_master_gpio *master,
		uपूर्णांक8_t data_size, काष्ठा fsi_gpio_msg *msgp, uपूर्णांक8_t *tagp)
अणु
	काष्ठा fsi_gpio_msg msg;
	अचिन्हित दीर्घ flags;
	uपूर्णांक32_t crc;
	uपूर्णांक8_t tag;
	पूर्णांक i;

	local_irq_save(flags);

	/* रुको क्रम the start bit */
	क्रम (i = 0; i < FSI_MASTER_MTOE_COUNT; i++) अणु
		msg.bits = 0;
		msg.msg = 0;
		serial_in(master, &msg, 1);
		अगर (msg.msg)
			अवरोध;
	पूर्ण
	अगर (i == FSI_MASTER_MTOE_COUNT) अणु
		dev_dbg(master->dev,
			"Master time out waiting for response\n");
		local_irq_restore(flags);
		वापस -ETIMEDOUT;
	पूर्ण

	msg.bits = 0;
	msg.msg = 0;

	/* Read slave ID & response tag */
	serial_in(master, &msg, 4);

	tag = msg.msg & 0x3;

	/* If we have an ACK and we're expecting data, घड़ी the data in too */
	अगर (tag == FSI_RESP_ACK && data_size)
		serial_in(master, &msg, data_size * 8);

	/* पढ़ो CRC */
	serial_in(master, &msg, FSI_CRC_SIZE);

	local_irq_restore(flags);

	/* we have a whole message now; check CRC */
	crc = crc4(0, 1, 1);
	crc = crc4(crc, msg.msg, msg.bits);
	अगर (crc) अणु
		/* Check अगर it's all 1's, that probably means the host is off */
		अगर (((~msg.msg) & ((1ull << msg.bits) - 1)) == 0)
			वापस -ENODEV;
		dev_dbg(master->dev, "ERR response CRC msg: 0x%016llx (%d bits)\n",
			msg.msg, msg.bits);
		वापस -EAGAIN;
	पूर्ण

	अगर (msgp)
		*msgp = msg;
	अगर (tagp)
		*tagp = tag;

	वापस 0;
पूर्ण

अटल पूर्णांक issue_term(काष्ठा fsi_master_gpio *master, uपूर्णांक8_t slave)
अणु
	काष्ठा fsi_gpio_msg cmd;
	अचिन्हित दीर्घ flags;
	uपूर्णांक8_t tag;
	पूर्णांक rc;

	build_term_command(&cmd, slave);

	local_irq_save(flags);
	serial_out(master, &cmd);
	echo_delay(master);
	local_irq_restore(flags);

	rc = पढ़ो_one_response(master, 0, शून्य, &tag);
	अगर (rc < 0) अणु
		dev_err(master->dev,
				"TERM failed; lost communication with slave\n");
		वापस -EIO;
	पूर्ण अन्यथा अगर (tag != FSI_RESP_ACK) अणु
		dev_err(master->dev, "TERM failed; response %d\n", tag);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक poll_क्रम_response(काष्ठा fsi_master_gpio *master,
		uपूर्णांक8_t slave, uपूर्णांक8_t size, व्योम *data)
अणु
	काष्ठा fsi_gpio_msg response, cmd;
	पूर्णांक busy_count = 0, rc, i;
	अचिन्हित दीर्घ flags;
	uपूर्णांक8_t tag;
	uपूर्णांक8_t *data_byte = data;
	पूर्णांक crc_err_retries = 0;
retry:
	rc = पढ़ो_one_response(master, size, &response, &tag);

	/* Handle retries on CRC errors */
	अगर (rc == -EAGAIN) अणु
		/* Too many retries ? */
		अगर (crc_err_retries++ > FSI_CRC_ERR_RETRIES) अणु
			/*
			 * Pass it up as a -EIO otherwise upper level will retry
			 * the whole command which isn't what we want here.
			 */
			rc = -EIO;
			जाओ fail;
		पूर्ण
		dev_dbg(master->dev,
			 "CRC error retry %d\n", crc_err_retries);
		trace_fsi_master_gpio_crc_rsp_error(master);
		build_epoll_command(&cmd, slave);
		local_irq_save(flags);
		घड़ी_zeros(master, FSI_MASTER_EPOLL_CLOCKS);
		serial_out(master, &cmd);
		echo_delay(master);
		local_irq_restore(flags);
		जाओ retry;
	पूर्ण अन्यथा अगर (rc)
		जाओ fail;

	चयन (tag) अणु
	हाल FSI_RESP_ACK:
		अगर (size && data) अणु
			uपूर्णांक64_t val = response.msg;
			/* clear crc & mask */
			val >>= 4;
			val &= (1ull << (size * 8)) - 1;

			क्रम (i = 0; i < size; i++) अणु
				data_byte[size-i-1] = val;
				val >>= 8;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल FSI_RESP_BUSY:
		/*
		 * Its necessary to घड़ी slave beक्रमe issuing
		 * d-poll, not indicated in the hardware protocol
		 * spec. < 20 घड़ीs causes slave to hang, 21 ok.
		 */
		अगर (busy_count++ < FSI_MASTER_MAX_BUSY) अणु
			build_dpoll_command(&cmd, slave);
			local_irq_save(flags);
			घड़ी_zeros(master, FSI_MASTER_DPOLL_CLOCKS);
			serial_out(master, &cmd);
			echo_delay(master);
			local_irq_restore(flags);
			जाओ retry;
		पूर्ण
		dev_warn(master->dev,
			"ERR slave is stuck in busy state, issuing TERM\n");
		local_irq_save(flags);
		घड़ी_zeros(master, FSI_MASTER_DPOLL_CLOCKS);
		local_irq_restore(flags);
		issue_term(master, slave);
		rc = -EIO;
		अवरोध;

	हाल FSI_RESP_ERRA:
		dev_dbg(master->dev, "ERRA received: 0x%x\n", (पूर्णांक)response.msg);
		rc = -EIO;
		अवरोध;
	हाल FSI_RESP_ERRC:
		dev_dbg(master->dev, "ERRC received: 0x%x\n", (पूर्णांक)response.msg);
		trace_fsi_master_gpio_crc_cmd_error(master);
		rc = -EAGAIN;
		अवरोध;
	पूर्ण

	अगर (busy_count > 0)
		trace_fsi_master_gpio_poll_response_busy(master, busy_count);
 fail:
	/*
	 * tSendDelay घड़ीs, aव्योमs संकेत reflections when चयनing
	 * from receive of response back to send of data.
	 */
	local_irq_save(flags);
	घड़ी_zeros(master, master->t_send_delay);
	local_irq_restore(flags);

	वापस rc;
पूर्ण

अटल पूर्णांक send_request(काष्ठा fsi_master_gpio *master,
		काष्ठा fsi_gpio_msg *cmd)
अणु
	अचिन्हित दीर्घ flags;

	अगर (master->बाह्यal_mode)
		वापस -EBUSY;

	local_irq_save(flags);
	serial_out(master, cmd);
	echo_delay(master);
	local_irq_restore(flags);

	वापस 0;
पूर्ण

अटल पूर्णांक fsi_master_gpio_xfer(काष्ठा fsi_master_gpio *master, uपूर्णांक8_t slave,
		काष्ठा fsi_gpio_msg *cmd, माप_प्रकार resp_len, व्योम *resp)
अणु
	पूर्णांक rc = -EAGAIN, retries = 0;

	जबतक ((retries++) < FSI_CRC_ERR_RETRIES) अणु
		rc = send_request(master, cmd);
		अगर (rc)
			अवरोध;
		rc = poll_क्रम_response(master, slave, resp_len, resp);
		अगर (rc != -EAGAIN)
			अवरोध;
		rc = -EIO;
		dev_warn(master->dev, "ECRC retry %d\n", retries);

		/* Pace it a bit beक्रमe retry */
		msleep(1);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक fsi_master_gpio_पढ़ो(काष्ठा fsi_master *_master, पूर्णांक link,
		uपूर्णांक8_t id, uपूर्णांक32_t addr, व्योम *val, माप_प्रकार size)
अणु
	काष्ठा fsi_master_gpio *master = to_fsi_master_gpio(_master);
	काष्ठा fsi_gpio_msg cmd;
	पूर्णांक rc;

	अगर (link != 0)
		वापस -ENODEV;

	mutex_lock(&master->cmd_lock);
	build_ar_command(master, &cmd, id, addr, size, शून्य);
	rc = fsi_master_gpio_xfer(master, id, &cmd, size, val);
	last_address_update(master, id, rc == 0, addr);
	mutex_unlock(&master->cmd_lock);

	वापस rc;
पूर्ण

अटल पूर्णांक fsi_master_gpio_ग_लिखो(काष्ठा fsi_master *_master, पूर्णांक link,
		uपूर्णांक8_t id, uपूर्णांक32_t addr, स्थिर व्योम *val, माप_प्रकार size)
अणु
	काष्ठा fsi_master_gpio *master = to_fsi_master_gpio(_master);
	काष्ठा fsi_gpio_msg cmd;
	पूर्णांक rc;

	अगर (link != 0)
		वापस -ENODEV;

	mutex_lock(&master->cmd_lock);
	build_ar_command(master, &cmd, id, addr, size, val);
	rc = fsi_master_gpio_xfer(master, id, &cmd, 0, शून्य);
	last_address_update(master, id, rc == 0, addr);
	mutex_unlock(&master->cmd_lock);

	वापस rc;
पूर्ण

अटल पूर्णांक fsi_master_gpio_term(काष्ठा fsi_master *_master,
		पूर्णांक link, uपूर्णांक8_t id)
अणु
	काष्ठा fsi_master_gpio *master = to_fsi_master_gpio(_master);
	काष्ठा fsi_gpio_msg cmd;
	पूर्णांक rc;

	अगर (link != 0)
		वापस -ENODEV;

	mutex_lock(&master->cmd_lock);
	build_term_command(&cmd, id);
	rc = fsi_master_gpio_xfer(master, id, &cmd, 0, शून्य);
	last_address_update(master, id, false, 0);
	mutex_unlock(&master->cmd_lock);

	वापस rc;
पूर्ण

अटल पूर्णांक fsi_master_gpio_अवरोध(काष्ठा fsi_master *_master, पूर्णांक link)
अणु
	काष्ठा fsi_master_gpio *master = to_fsi_master_gpio(_master);
	अचिन्हित दीर्घ flags;

	अगर (link != 0)
		वापस -ENODEV;

	trace_fsi_master_gpio_अवरोध(master);

	mutex_lock(&master->cmd_lock);
	अगर (master->बाह्यal_mode) अणु
		mutex_unlock(&master->cmd_lock);
		वापस -EBUSY;
	पूर्ण

	local_irq_save(flags);

	set_sda_output(master, 1);
	sda_out(master, 1);
	घड़ी_प्रकारoggle(master, FSI_PRE_BREAK_CLOCKS);
	sda_out(master, 0);
	घड़ी_प्रकारoggle(master, FSI_BREAK_CLOCKS);
	echo_delay(master);
	sda_out(master, 1);
	घड़ी_प्रकारoggle(master, FSI_POST_BREAK_CLOCKS);

	local_irq_restore(flags);

	last_address_update(master, 0, false, 0);
	mutex_unlock(&master->cmd_lock);

	/* Wait क्रम logic reset to take effect */
	udelay(200);

	वापस 0;
पूर्ण

अटल व्योम fsi_master_gpio_init(काष्ठा fsi_master_gpio *master)
अणु
	अचिन्हित दीर्घ flags;

	gpiod_direction_output(master->gpio_mux, 1);
	gpiod_direction_output(master->gpio_trans, 1);
	gpiod_direction_output(master->gpio_enable, 1);
	gpiod_direction_output(master->gpio_clk, 1);
	gpiod_direction_output(master->gpio_data, 1);

	/* toकरो: evaluate अगर घड़ीs can be reduced */
	local_irq_save(flags);
	घड़ी_zeros(master, FSI_INIT_CLOCKS);
	local_irq_restore(flags);
पूर्ण

अटल व्योम fsi_master_gpio_init_बाह्यal(काष्ठा fsi_master_gpio *master)
अणु
	gpiod_direction_output(master->gpio_mux, 0);
	gpiod_direction_output(master->gpio_trans, 0);
	gpiod_direction_output(master->gpio_enable, 1);
	gpiod_direction_input(master->gpio_clk);
	gpiod_direction_input(master->gpio_data);
पूर्ण

अटल पूर्णांक fsi_master_gpio_link_enable(काष्ठा fsi_master *_master, पूर्णांक link,
				       bool enable)
अणु
	काष्ठा fsi_master_gpio *master = to_fsi_master_gpio(_master);
	पूर्णांक rc = -EBUSY;

	अगर (link != 0)
		वापस -ENODEV;

	mutex_lock(&master->cmd_lock);
	अगर (!master->बाह्यal_mode) अणु
		gpiod_set_value(master->gpio_enable, enable ? 1 : 0);
		rc = 0;
	पूर्ण
	mutex_unlock(&master->cmd_lock);

	वापस rc;
पूर्ण

अटल पूर्णांक fsi_master_gpio_link_config(काष्ठा fsi_master *_master, पूर्णांक link,
				       u8 t_send_delay, u8 t_echo_delay)
अणु
	काष्ठा fsi_master_gpio *master = to_fsi_master_gpio(_master);

	अगर (link != 0)
		वापस -ENODEV;

	mutex_lock(&master->cmd_lock);
	master->t_send_delay = t_send_delay;
	master->t_echo_delay = t_echo_delay;
	mutex_unlock(&master->cmd_lock);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार बाह्यal_mode_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fsi_master_gpio *master = dev_get_drvdata(dev);

	वापस snम_लिखो(buf, PAGE_SIZE - 1, "%u\n",
			master->बाह्यal_mode ? 1 : 0);
पूर्ण

अटल sमाप_प्रकार बाह्यal_mode_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा fsi_master_gpio *master = dev_get_drvdata(dev);
	अचिन्हित दीर्घ val;
	bool बाह्यal_mode;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 0, &val);
	अगर (err)
		वापस err;

	बाह्यal_mode = !!val;

	mutex_lock(&master->cmd_lock);

	अगर (बाह्यal_mode == master->बाह्यal_mode) अणु
		mutex_unlock(&master->cmd_lock);
		वापस count;
	पूर्ण

	master->बाह्यal_mode = बाह्यal_mode;
	अगर (master->बाह्यal_mode)
		fsi_master_gpio_init_बाह्यal(master);
	अन्यथा
		fsi_master_gpio_init(master);

	mutex_unlock(&master->cmd_lock);

	fsi_master_rescan(&master->master);

	वापस count;
पूर्ण

अटल DEVICE_ATTR(बाह्यal_mode, 0664,
		बाह्यal_mode_show, बाह्यal_mode_store);

अटल व्योम fsi_master_gpio_release(काष्ठा device *dev)
अणु
	काष्ठा fsi_master_gpio *master = to_fsi_master_gpio(dev_to_fsi_master(dev));

	of_node_put(dev_of_node(master->dev));

	kमुक्त(master);
पूर्ण

अटल पूर्णांक fsi_master_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fsi_master_gpio *master;
	काष्ठा gpio_desc *gpio;
	पूर्णांक rc;

	master = kzalloc(माप(*master), GFP_KERNEL);
	अगर (!master)
		वापस -ENOMEM;

	master->dev = &pdev->dev;
	master->master.dev.parent = master->dev;
	master->master.dev.of_node = of_node_get(dev_of_node(master->dev));
	master->master.dev.release = fsi_master_gpio_release;
	master->last_addr = LAST_ADDR_INVALID;

	gpio = devm_gpiod_get(&pdev->dev, "clock", 0);
	अगर (IS_ERR(gpio)) अणु
		dev_err(&pdev->dev, "failed to get clock gpio\n");
		rc = PTR_ERR(gpio);
		जाओ err_मुक्त;
	पूर्ण
	master->gpio_clk = gpio;

	gpio = devm_gpiod_get(&pdev->dev, "data", 0);
	अगर (IS_ERR(gpio)) अणु
		dev_err(&pdev->dev, "failed to get data gpio\n");
		rc = PTR_ERR(gpio);
		जाओ err_मुक्त;
	पूर्ण
	master->gpio_data = gpio;

	/* Optional GPIOs */
	gpio = devm_gpiod_get_optional(&pdev->dev, "trans", 0);
	अगर (IS_ERR(gpio)) अणु
		dev_err(&pdev->dev, "failed to get trans gpio\n");
		rc = PTR_ERR(gpio);
		जाओ err_मुक्त;
	पूर्ण
	master->gpio_trans = gpio;

	gpio = devm_gpiod_get_optional(&pdev->dev, "enable", 0);
	अगर (IS_ERR(gpio)) अणु
		dev_err(&pdev->dev, "failed to get enable gpio\n");
		rc = PTR_ERR(gpio);
		जाओ err_मुक्त;
	पूर्ण
	master->gpio_enable = gpio;

	gpio = devm_gpiod_get_optional(&pdev->dev, "mux", 0);
	अगर (IS_ERR(gpio)) अणु
		dev_err(&pdev->dev, "failed to get mux gpio\n");
		rc = PTR_ERR(gpio);
		जाओ err_मुक्त;
	पूर्ण
	master->gpio_mux = gpio;

	/*
	 * Check अगर GPIO block is slow enought that no extra delays
	 * are necessary. This improves perक्रमmance on ast2500 by
	 * an order of magnitude.
	 */
	master->no_delays = device_property_present(&pdev->dev, "no-gpio-delays");

	/* Default FSI command delays */
	master->t_send_delay = FSI_SEND_DELAY_CLOCKS;
	master->t_echo_delay = FSI_ECHO_DELAY_CLOCKS;

	master->master.n_links = 1;
	master->master.flags = FSI_MASTER_FLAG_SWCLOCK;
	master->master.पढ़ो = fsi_master_gpio_पढ़ो;
	master->master.ग_लिखो = fsi_master_gpio_ग_लिखो;
	master->master.term = fsi_master_gpio_term;
	master->master.send_अवरोध = fsi_master_gpio_अवरोध;
	master->master.link_enable = fsi_master_gpio_link_enable;
	master->master.link_config = fsi_master_gpio_link_config;
	platक्रमm_set_drvdata(pdev, master);
	mutex_init(&master->cmd_lock);

	fsi_master_gpio_init(master);

	rc = device_create_file(&pdev->dev, &dev_attr_बाह्यal_mode);
	अगर (rc)
		जाओ err_मुक्त;

	rc = fsi_master_रेजिस्टर(&master->master);
	अगर (rc) अणु
		device_हटाओ_file(&pdev->dev, &dev_attr_बाह्यal_mode);
		put_device(&master->master.dev);
		वापस rc;
	पूर्ण
	वापस 0;
 err_मुक्त:
	kमुक्त(master);
	वापस rc;
पूर्ण



अटल पूर्णांक fsi_master_gpio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fsi_master_gpio *master = platक्रमm_get_drvdata(pdev);

	device_हटाओ_file(&pdev->dev, &dev_attr_बाह्यal_mode);

	fsi_master_unरेजिस्टर(&master->master);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id fsi_master_gpio_match[] = अणु
	अणु .compatible = "fsi-master-gpio" पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver fsi_master_gpio_driver = अणु
	.driver = अणु
		.name		= "fsi-master-gpio",
		.of_match_table	= fsi_master_gpio_match,
	पूर्ण,
	.probe	= fsi_master_gpio_probe,
	.हटाओ = fsi_master_gpio_हटाओ,
पूर्ण;

module_platक्रमm_driver(fsi_master_gpio_driver);
MODULE_LICENSE("GPL");
