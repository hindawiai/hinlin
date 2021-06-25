<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// Copyright 2018 IBM Corp
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
#समावेश <linux/regmap.h>
#समावेश <linux/firmware.h>
#समावेश <linux/gpio/aspeed.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of_address.h>
#समावेश <linux/genभाग.स>

#समावेश "fsi-master.h"
#समावेश "cf-fsi-fw.h"

#घोषणा FW_खाता_NAME	"cf-fsi-fw.bin"

/* Common SCU based coprocessor control रेजिस्टरs */
#घोषणा SCU_COPRO_CTRL			0x100
#घोषणा   SCU_COPRO_RESET			0x00000002
#घोषणा   SCU_COPRO_CLK_EN			0x00000001

/* AST2500 specअगरic ones */
#घोषणा SCU_2500_COPRO_SEG0		0x104
#घोषणा SCU_2500_COPRO_SEG1		0x108
#घोषणा SCU_2500_COPRO_SEG2		0x10c
#घोषणा SCU_2500_COPRO_SEG3		0x110
#घोषणा SCU_2500_COPRO_SEG4		0x114
#घोषणा SCU_2500_COPRO_SEG5		0x118
#घोषणा SCU_2500_COPRO_SEG6		0x11c
#घोषणा SCU_2500_COPRO_SEG7		0x120
#घोषणा SCU_2500_COPRO_SEG8		0x124
#घोषणा   SCU_2500_COPRO_SEG_SWAP		0x00000001
#घोषणा SCU_2500_COPRO_CACHE_CTL	0x128
#घोषणा   SCU_2500_COPRO_CACHE_EN		0x00000001
#घोषणा   SCU_2500_COPRO_SEG0_CACHE_EN		0x00000002
#घोषणा   SCU_2500_COPRO_SEG1_CACHE_EN		0x00000004
#घोषणा   SCU_2500_COPRO_SEG2_CACHE_EN		0x00000008
#घोषणा   SCU_2500_COPRO_SEG3_CACHE_EN		0x00000010
#घोषणा   SCU_2500_COPRO_SEG4_CACHE_EN		0x00000020
#घोषणा   SCU_2500_COPRO_SEG5_CACHE_EN		0x00000040
#घोषणा   SCU_2500_COPRO_SEG6_CACHE_EN		0x00000080
#घोषणा   SCU_2500_COPRO_SEG7_CACHE_EN		0x00000100
#घोषणा   SCU_2500_COPRO_SEG8_CACHE_EN		0x00000200

#घोषणा SCU_2400_COPRO_SEG0		0x104
#घोषणा SCU_2400_COPRO_SEG2		0x108
#घोषणा SCU_2400_COPRO_SEG4		0x10c
#घोषणा SCU_2400_COPRO_SEG6		0x110
#घोषणा SCU_2400_COPRO_SEG8		0x114
#घोषणा   SCU_2400_COPRO_SEG_SWAP		0x80000000
#घोषणा SCU_2400_COPRO_CACHE_CTL	0x118
#घोषणा   SCU_2400_COPRO_CACHE_EN		0x00000001
#घोषणा   SCU_2400_COPRO_SEG0_CACHE_EN		0x00000002
#घोषणा   SCU_2400_COPRO_SEG2_CACHE_EN		0x00000004
#घोषणा   SCU_2400_COPRO_SEG4_CACHE_EN		0x00000008
#घोषणा   SCU_2400_COPRO_SEG6_CACHE_EN		0x00000010
#घोषणा   SCU_2400_COPRO_SEG8_CACHE_EN		0x00000020

/* CVIC रेजिस्टरs */
#घोषणा CVIC_EN_REG			0x10
#घोषणा CVIC_TRIG_REG			0x18

/*
 * System रेजिस्टर base address (needed क्रम configuring the
 * coldfire maps)
 */
#घोषणा SYSREG_BASE			0x1e600000

/* Amount of SRAM required */
#घोषणा SRAM_SIZE			0x1000

#घोषणा LAST_ADDR_INVALID		0x1

काष्ठा fsi_master_acf अणु
	काष्ठा fsi_master	master;
	काष्ठा device		*dev;
	काष्ठा regmap		*scu;
	काष्ठा mutex		lock;	/* mutex क्रम command ordering */
	काष्ठा gpio_desc	*gpio_clk;
	काष्ठा gpio_desc	*gpio_data;
	काष्ठा gpio_desc	*gpio_trans;	/* Voltage translator */
	काष्ठा gpio_desc	*gpio_enable;	/* FSI enable */
	काष्ठा gpio_desc	*gpio_mux;	/* Mux control */
	uपूर्णांक16_t		gpio_clk_vreg;
	uपूर्णांक16_t		gpio_clk_dreg;
	uपूर्णांक16_t       		gpio_dat_vreg;
	uपूर्णांक16_t       		gpio_dat_dreg;
	uपूर्णांक16_t       		gpio_tra_vreg;
	uपूर्णांक16_t       		gpio_tra_dreg;
	uपूर्णांक8_t			gpio_clk_bit;
	uपूर्णांक8_t			gpio_dat_bit;
	uपूर्णांक8_t			gpio_tra_bit;
	uपूर्णांक32_t		cf_mem_addr;
	माप_प्रकार			cf_mem_size;
	व्योम __iomem		*cf_mem;
	व्योम __iomem		*cvic;
	काष्ठा gen_pool		*sram_pool;
	व्योम __iomem		*sram;
	bool			is_ast2500;
	bool			बाह्यal_mode;
	bool			trace_enabled;
	uपूर्णांक32_t		last_addr;
	uपूर्णांक8_t			t_send_delay;
	uपूर्णांक8_t			t_echo_delay;
	uपूर्णांक32_t		cvic_sw_irq;
पूर्ण;
#घोषणा to_fsi_master_acf(m) container_of(m, काष्ठा fsi_master_acf, master)

काष्ठा fsi_msg अणु
	uपूर्णांक64_t	msg;
	uपूर्णांक8_t		bits;
पूर्ण;

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/fsi_master_ast_cf.h>

अटल व्योम msg_push_bits(काष्ठा fsi_msg *msg, uपूर्णांक64_t data, पूर्णांक bits)
अणु
	msg->msg <<= bits;
	msg->msg |= data & ((1ull << bits) - 1);
	msg->bits += bits;
पूर्ण

अटल व्योम msg_push_crc(काष्ठा fsi_msg *msg)
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

अटल व्योम msg_finish_cmd(काष्ठा fsi_msg *cmd)
अणु
	/* Left align message */
	cmd->msg <<= (64 - cmd->bits);
पूर्ण

अटल bool check_same_address(काष्ठा fsi_master_acf *master, पूर्णांक id,
			       uपूर्णांक32_t addr)
अणु
	/* this will also handle LAST_ADDR_INVALID */
	वापस master->last_addr == (((id & 0x3) << 21) | (addr & ~0x3));
पूर्ण

अटल bool check_relative_address(काष्ठा fsi_master_acf *master, पूर्णांक id,
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

अटल व्योम last_address_update(काष्ठा fsi_master_acf *master,
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
अटल व्योम build_ar_command(काष्ठा fsi_master_acf *master,
			     काष्ठा fsi_msg *cmd, uपूर्णांक8_t id,
			     uपूर्णांक32_t addr, माप_प्रकार size,
			     स्थिर व्योम *data)
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
		trace_fsi_master_acf_cmd_same_addr(master);

	पूर्ण अन्यथा अगर (check_relative_address(master, id, addr, &rel_addr)) अणु
		/* 8 bits plus sign */
		addr_bits = 9;
		addr = rel_addr;
		opcode = FSI_CMD_REL_AR;
		trace_fsi_master_acf_cmd_rel_addr(master, rel_addr);

	पूर्ण अन्यथा अणु
		addr_bits = 21;
		opcode = FSI_CMD_ABS_AR;
		trace_fsi_master_acf_cmd_असल_addr(master, addr);
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
	msg_finish_cmd(cmd);
पूर्ण

अटल व्योम build_dpoll_command(काष्ठा fsi_msg *cmd, uपूर्णांक8_t slave_id)
अणु
	cmd->bits = 0;
	cmd->msg = 0;

	msg_push_bits(cmd, slave_id, 2);
	msg_push_bits(cmd, FSI_CMD_DPOLL, 3);
	msg_push_crc(cmd);
	msg_finish_cmd(cmd);
पूर्ण

अटल व्योम build_epoll_command(काष्ठा fsi_msg *cmd, uपूर्णांक8_t slave_id)
अणु
	cmd->bits = 0;
	cmd->msg = 0;

	msg_push_bits(cmd, slave_id, 2);
	msg_push_bits(cmd, FSI_CMD_EPOLL, 3);
	msg_push_crc(cmd);
	msg_finish_cmd(cmd);
पूर्ण

अटल व्योम build_term_command(काष्ठा fsi_msg *cmd, uपूर्णांक8_t slave_id)
अणु
	cmd->bits = 0;
	cmd->msg = 0;

	msg_push_bits(cmd, slave_id, 2);
	msg_push_bits(cmd, FSI_CMD_TERM, 6);
	msg_push_crc(cmd);
	msg_finish_cmd(cmd);
पूर्ण

अटल पूर्णांक करो_copro_command(काष्ठा fsi_master_acf *master, uपूर्णांक32_t op)
अणु
	uपूर्णांक32_t समयout = 10000000;
	uपूर्णांक8_t stat;

	trace_fsi_master_acf_copro_command(master, op);

	/* Send command */
	ioग_लिखो32be(op, master->sram + CMD_STAT_REG);

	/* Ring करोorbell अगर any */
	अगर (master->cvic)
		ioग_लिखो32(0x2, master->cvic + CVIC_TRIG_REG);

	/* Wait क्रम status to indicate completion (or error) */
	करो अणु
		अगर (समयout-- == 0) अणु
			dev_warn(master->dev,
				 "Timeout waiting for coprocessor completion\n");
			वापस -ETIMEDOUT;
		पूर्ण
		stat = ioपढ़ो8(master->sram + CMD_STAT_REG);
	पूर्ण जबतक(stat < STAT_COMPLETE || stat == 0xff);

	अगर (stat == STAT_COMPLETE)
		वापस 0;
	चयन(stat) अणु
	हाल STAT_ERR_INVAL_CMD:
		वापस -EINVAL;
	हाल STAT_ERR_INVAL_IRQ:
		वापस -EIO;
	हाल STAT_ERR_MTOE:
		वापस -ESHUTDOWN;
	पूर्ण
	वापस -ENXIO;
पूर्ण

अटल पूर्णांक घड़ी_zeros(काष्ठा fsi_master_acf *master, पूर्णांक count)
अणु
	जबतक (count) अणु
		पूर्णांक rc, lcnt = min(count, 255);

		rc = करो_copro_command(master,
				      CMD_IDLE_CLOCKS | (lcnt << CMD_REG_CLEN_SHIFT));
		अगर (rc)
			वापस rc;
		count -= lcnt;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक send_request(काष्ठा fsi_master_acf *master, काष्ठा fsi_msg *cmd,
			अचिन्हित पूर्णांक resp_bits)
अणु
	uपूर्णांक32_t op;

	trace_fsi_master_acf_send_request(master, cmd, resp_bits);

	/* Store message पूर्णांकo SRAM */
	ioग_लिखो32be((cmd->msg >> 32), master->sram + CMD_DATA);
	ioग_लिखो32be((cmd->msg & 0xffffffff), master->sram + CMD_DATA + 4);

	op = CMD_COMMAND;
	op |= cmd->bits << CMD_REG_CLEN_SHIFT;
	अगर (resp_bits)
		op |= resp_bits << CMD_REG_RLEN_SHIFT;

	वापस करो_copro_command(master, op);
पूर्ण

अटल पूर्णांक पढ़ो_copro_response(काष्ठा fsi_master_acf *master, uपूर्णांक8_t size,
			       uपूर्णांक32_t *response, u8 *tag)
अणु
	uपूर्णांक8_t rtag = ioपढ़ो8(master->sram + STAT_RTAG) & 0xf;
	uपूर्णांक8_t rcrc = ioपढ़ो8(master->sram + STAT_RCRC) & 0xf;
	uपूर्णांक32_t rdata = 0;
	uपूर्णांक32_t crc;
	uपूर्णांक8_t ack;

	*tag = ack = rtag & 3;

	/* we have a whole message now; check CRC */
	crc = crc4(0, 1, 1);
	crc = crc4(crc, rtag, 4);
	अगर (ack == FSI_RESP_ACK && size) अणु
		rdata = ioपढ़ो32be(master->sram + RSP_DATA);
		crc = crc4(crc, rdata, size);
		अगर (response)
			*response = rdata;
	पूर्ण
	crc = crc4(crc, rcrc, 4);

	trace_fsi_master_acf_copro_response(master, rtag, rcrc, rdata, crc == 0);

	अगर (crc) अणु
		/*
		 * Check अगर it's all 1's or all 0's, that probably means
		 * the host is off
		 */
		अगर ((rtag == 0xf && rcrc == 0xf) || (rtag == 0 && rcrc == 0))
			वापस -ENODEV;
		dev_dbg(master->dev, "Bad response CRC !\n");
		वापस -EAGAIN;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक send_term(काष्ठा fsi_master_acf *master, uपूर्णांक8_t slave)
अणु
	काष्ठा fsi_msg cmd;
	uपूर्णांक8_t tag;
	पूर्णांक rc;

	build_term_command(&cmd, slave);

	rc = send_request(master, &cmd, 0);
	अगर (rc) अणु
		dev_warn(master->dev, "Error %d sending term\n", rc);
		वापस rc;
	पूर्ण

	rc = पढ़ो_copro_response(master, 0, शून्य, &tag);
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

अटल व्योम dump_ucode_trace(काष्ठा fsi_master_acf *master)
अणु
	अक्षर trbuf[52];
	अक्षर *p;
	पूर्णांक i;

	dev_dbg(master->dev,
		"CMDSTAT:%08x RTAG=%02x RCRC=%02x RDATA=%02x #INT=%08x\n",
		ioपढ़ो32be(master->sram + CMD_STAT_REG),
		ioपढ़ो8(master->sram + STAT_RTAG),
		ioपढ़ो8(master->sram + STAT_RCRC),
		ioपढ़ो32be(master->sram + RSP_DATA),
		ioपढ़ो32be(master->sram + INT_CNT));

	क्रम (i = 0; i < 512; i++) अणु
		uपूर्णांक8_t v;
		अगर ((i % 16) == 0)
			p = trbuf;
		v = ioपढ़ो8(master->sram + TRACEBUF + i);
		p += प्र_लिखो(p, "%02x ", v);
		अगर (((i % 16) == 15) || v == TR_END)
			dev_dbg(master->dev, "%s\n", trbuf);
		अगर (v == TR_END)
			अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक handle_response(काष्ठा fsi_master_acf *master,
			   uपूर्णांक8_t slave, uपूर्णांक8_t size, व्योम *data)
अणु
	पूर्णांक busy_count = 0, rc;
	पूर्णांक crc_err_retries = 0;
	काष्ठा fsi_msg cmd;
	uपूर्णांक32_t response;
	uपूर्णांक8_t tag;
retry:
	rc = पढ़ो_copro_response(master, size, &response, &tag);

	/* Handle retries on CRC errors */
	अगर (rc == -EAGAIN) अणु
		/* Too many retries ? */
		अगर (crc_err_retries++ > FSI_CRC_ERR_RETRIES) अणु
			/*
			 * Pass it up as a -EIO otherwise upper level will retry
			 * the whole command which isn't what we want here.
			 */
			rc = -EIO;
			जाओ bail;
		पूर्ण
		trace_fsi_master_acf_crc_rsp_error(master, crc_err_retries);
		अगर (master->trace_enabled)
			dump_ucode_trace(master);
		rc = घड़ी_zeros(master, FSI_MASTER_EPOLL_CLOCKS);
		अगर (rc) अणु
			dev_warn(master->dev,
				 "Error %d clocking zeros for E_POLL\n", rc);
			वापस rc;
		पूर्ण
		build_epoll_command(&cmd, slave);
		rc = send_request(master, &cmd, size);
		अगर (rc) अणु
			dev_warn(master->dev, "Error %d sending E_POLL\n", rc);
			वापस -EIO;
		पूर्ण
		जाओ retry;
	पूर्ण
	अगर (rc)
		वापस rc;

	चयन (tag) अणु
	हाल FSI_RESP_ACK:
		अगर (size && data) अणु
			अगर (size == 32)
				*(__be32 *)data = cpu_to_be32(response);
			अन्यथा अगर (size == 16)
				*(__be16 *)data = cpu_to_be16(response);
			अन्यथा
				*(u8 *)data = response;
		पूर्ण
		अवरोध;
	हाल FSI_RESP_BUSY:
		/*
		 * Its necessary to घड़ी slave beक्रमe issuing
		 * d-poll, not indicated in the hardware protocol
		 * spec. < 20 घड़ीs causes slave to hang, 21 ok.
		 */
		dev_dbg(master->dev, "Busy, retrying...\n");
		अगर (master->trace_enabled)
			dump_ucode_trace(master);
		rc = घड़ी_zeros(master, FSI_MASTER_DPOLL_CLOCKS);
		अगर (rc) अणु
			dev_warn(master->dev,
				 "Error %d clocking zeros for D_POLL\n", rc);
			अवरोध;
		पूर्ण
		अगर (busy_count++ < FSI_MASTER_MAX_BUSY) अणु
			build_dpoll_command(&cmd, slave);
			rc = send_request(master, &cmd, size);
			अगर (rc) अणु
				dev_warn(master->dev, "Error %d sending D_POLL\n", rc);
				अवरोध;
			पूर्ण
			जाओ retry;
		पूर्ण
		dev_dbg(master->dev,
			"ERR slave is stuck in busy state, issuing TERM\n");
		send_term(master, slave);
		rc = -EIO;
		अवरोध;

	हाल FSI_RESP_ERRA:
		dev_dbg(master->dev, "ERRA received\n");
		अगर (master->trace_enabled)
			dump_ucode_trace(master);
		rc = -EIO;
		अवरोध;
	हाल FSI_RESP_ERRC:
		dev_dbg(master->dev, "ERRC received\n");
		अगर (master->trace_enabled)
			dump_ucode_trace(master);
		rc = -EAGAIN;
		अवरोध;
	पूर्ण
 bail:
	अगर (busy_count > 0) अणु
		trace_fsi_master_acf_poll_response_busy(master, busy_count);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक fsi_master_acf_xfer(काष्ठा fsi_master_acf *master, uपूर्णांक8_t slave,
			       काष्ठा fsi_msg *cmd, माप_प्रकार resp_len, व्योम *resp)
अणु
	पूर्णांक rc = -EAGAIN, retries = 0;

	resp_len <<= 3;
	जबतक ((retries++) < FSI_CRC_ERR_RETRIES) अणु
		rc = send_request(master, cmd, resp_len);
		अगर (rc) अणु
			अगर (rc != -ESHUTDOWN)
				dev_warn(master->dev, "Error %d sending command\n", rc);
			अवरोध;
		पूर्ण
		rc = handle_response(master, slave, resp_len, resp);
		अगर (rc != -EAGAIN)
			अवरोध;
		rc = -EIO;
		dev_dbg(master->dev, "ECRC retry %d\n", retries);

		/* Pace it a bit beक्रमe retry */
		msleep(1);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक fsi_master_acf_पढ़ो(काष्ठा fsi_master *_master, पूर्णांक link,
			       uपूर्णांक8_t id, uपूर्णांक32_t addr, व्योम *val,
			       माप_प्रकार size)
अणु
	काष्ठा fsi_master_acf *master = to_fsi_master_acf(_master);
	काष्ठा fsi_msg cmd;
	पूर्णांक rc;

	अगर (link != 0)
		वापस -ENODEV;

	mutex_lock(&master->lock);
	dev_dbg(master->dev, "read id %d addr %x size %zd\n", id, addr, size);
	build_ar_command(master, &cmd, id, addr, size, शून्य);
	rc = fsi_master_acf_xfer(master, id, &cmd, size, val);
	last_address_update(master, id, rc == 0, addr);
	अगर (rc)
		dev_dbg(master->dev, "read id %d addr 0x%08x err: %d\n",
			id, addr, rc);
	mutex_unlock(&master->lock);

	वापस rc;
पूर्ण

अटल पूर्णांक fsi_master_acf_ग_लिखो(काष्ठा fsi_master *_master, पूर्णांक link,
				uपूर्णांक8_t id, uपूर्णांक32_t addr, स्थिर व्योम *val,
				माप_प्रकार size)
अणु
	काष्ठा fsi_master_acf *master = to_fsi_master_acf(_master);
	काष्ठा fsi_msg cmd;
	पूर्णांक rc;

	अगर (link != 0)
		वापस -ENODEV;

	mutex_lock(&master->lock);
	build_ar_command(master, &cmd, id, addr, size, val);
	dev_dbg(master->dev, "write id %d addr %x size %zd raw_data: %08x\n",
		id, addr, size, *(uपूर्णांक32_t *)val);
	rc = fsi_master_acf_xfer(master, id, &cmd, 0, शून्य);
	last_address_update(master, id, rc == 0, addr);
	अगर (rc)
		dev_dbg(master->dev, "write id %d addr 0x%08x err: %d\n",
			id, addr, rc);
	mutex_unlock(&master->lock);

	वापस rc;
पूर्ण

अटल पूर्णांक fsi_master_acf_term(काष्ठा fsi_master *_master,
			       पूर्णांक link, uपूर्णांक8_t id)
अणु
	काष्ठा fsi_master_acf *master = to_fsi_master_acf(_master);
	काष्ठा fsi_msg cmd;
	पूर्णांक rc;

	अगर (link != 0)
		वापस -ENODEV;

	mutex_lock(&master->lock);
	build_term_command(&cmd, id);
	dev_dbg(master->dev, "term id %d\n", id);
	rc = fsi_master_acf_xfer(master, id, &cmd, 0, शून्य);
	last_address_update(master, id, false, 0);
	mutex_unlock(&master->lock);

	वापस rc;
पूर्ण

अटल पूर्णांक fsi_master_acf_अवरोध(काष्ठा fsi_master *_master, पूर्णांक link)
अणु
	काष्ठा fsi_master_acf *master = to_fsi_master_acf(_master);
	पूर्णांक rc;

	अगर (link != 0)
		वापस -ENODEV;

	mutex_lock(&master->lock);
	अगर (master->बाह्यal_mode) अणु
		mutex_unlock(&master->lock);
		वापस -EBUSY;
	पूर्ण
	dev_dbg(master->dev, "sending BREAK\n");
	rc = करो_copro_command(master, CMD_BREAK);
	last_address_update(master, 0, false, 0);
	mutex_unlock(&master->lock);

	/* Wait क्रम logic reset to take effect */
	udelay(200);

	वापस rc;
पूर्ण

अटल व्योम reset_cf(काष्ठा fsi_master_acf *master)
अणु
	regmap_ग_लिखो(master->scu, SCU_COPRO_CTRL, SCU_COPRO_RESET);
	usleep_range(20,20);
	regmap_ग_लिखो(master->scu, SCU_COPRO_CTRL, 0);
	usleep_range(20,20);
पूर्ण

अटल व्योम start_cf(काष्ठा fsi_master_acf *master)
अणु
	regmap_ग_लिखो(master->scu, SCU_COPRO_CTRL, SCU_COPRO_CLK_EN);
पूर्ण

अटल व्योम setup_ast2500_cf_maps(काष्ठा fsi_master_acf *master)
अणु
	/*
	 * Note about byteswap setting: the bus is wired backwards,
	 * so setting the byteswap bit actually makes the ColdFire
	 * work "normally" क्रम a BE processor, ie, put the MSB in
	 * the lowest address byte.
	 *
	 * We thus need to set the bit क्रम our मुख्य memory which
	 * contains our program code. We create two mappings क्रम
	 * the रेजिस्टर, one with each setting.
	 *
	 * Segments 2 and 3 has a "swapped" mapping (BE)
	 * and 6 and 7 have a non-swapped mapping (LE) which allows
	 * us to aव्योम byteswapping रेजिस्टर accesses since the
	 * रेजिस्टरs are all LE.
	 */

	/* Setup segment 0 to our memory region */
	regmap_ग_लिखो(master->scu, SCU_2500_COPRO_SEG0, master->cf_mem_addr |
		     SCU_2500_COPRO_SEG_SWAP);

	/* Segments 2 and 3 to sysregs with byteswap (क्रम SRAM) */
	regmap_ग_लिखो(master->scu, SCU_2500_COPRO_SEG2, SYSREG_BASE |
		     SCU_2500_COPRO_SEG_SWAP);
	regmap_ग_लिखो(master->scu, SCU_2500_COPRO_SEG3, SYSREG_BASE | 0x100000 |
		     SCU_2500_COPRO_SEG_SWAP);

	/* And segment 6 and 7 to sysregs no byteswap */
	regmap_ग_लिखो(master->scu, SCU_2500_COPRO_SEG6, SYSREG_BASE);
	regmap_ग_लिखो(master->scu, SCU_2500_COPRO_SEG7, SYSREG_BASE | 0x100000);

	/* Memory cachable, regs and SRAM not cachable */
	regmap_ग_लिखो(master->scu, SCU_2500_COPRO_CACHE_CTL,
		     SCU_2500_COPRO_SEG0_CACHE_EN | SCU_2500_COPRO_CACHE_EN);
पूर्ण

अटल व्योम setup_ast2400_cf_maps(काष्ठा fsi_master_acf *master)
अणु
	/* Setup segment 0 to our memory region */
	regmap_ग_लिखो(master->scu, SCU_2400_COPRO_SEG0, master->cf_mem_addr |
		     SCU_2400_COPRO_SEG_SWAP);

	/* Segments 2 to sysregs with byteswap (क्रम SRAM) */
	regmap_ग_लिखो(master->scu, SCU_2400_COPRO_SEG2, SYSREG_BASE |
		     SCU_2400_COPRO_SEG_SWAP);

	/* And segment 6 to sysregs no byteswap */
	regmap_ग_लिखो(master->scu, SCU_2400_COPRO_SEG6, SYSREG_BASE);

	/* Memory cachable, regs and SRAM not cachable */
	regmap_ग_लिखो(master->scu, SCU_2400_COPRO_CACHE_CTL,
		     SCU_2400_COPRO_SEG0_CACHE_EN | SCU_2400_COPRO_CACHE_EN);
पूर्ण

अटल व्योम setup_common_fw_config(काष्ठा fsi_master_acf *master,
				   व्योम __iomem *base)
अणु
	ioग_लिखो16be(master->gpio_clk_vreg, base + HDR_CLOCK_GPIO_VADDR);
	ioग_लिखो16be(master->gpio_clk_dreg, base + HDR_CLOCK_GPIO_DADDR);
	ioग_लिखो16be(master->gpio_dat_vreg, base + HDR_DATA_GPIO_VADDR);
	ioग_लिखो16be(master->gpio_dat_dreg, base + HDR_DATA_GPIO_DADDR);
	ioग_लिखो16be(master->gpio_tra_vreg, base + HDR_TRANS_GPIO_VADDR);
	ioग_लिखो16be(master->gpio_tra_dreg, base + HDR_TRANS_GPIO_DADDR);
	ioग_लिखो8(master->gpio_clk_bit, base + HDR_CLOCK_GPIO_BIT);
	ioग_लिखो8(master->gpio_dat_bit, base + HDR_DATA_GPIO_BIT);
	ioग_लिखो8(master->gpio_tra_bit, base + HDR_TRANS_GPIO_BIT);
पूर्ण

अटल व्योम setup_ast2500_fw_config(काष्ठा fsi_master_acf *master)
अणु
	व्योम __iomem *base = master->cf_mem + HDR_OFFSET;

	setup_common_fw_config(master, base);
	ioग_लिखो32be(FW_CONTROL_USE_STOP, base + HDR_FW_CONTROL);
पूर्ण

अटल व्योम setup_ast2400_fw_config(काष्ठा fsi_master_acf *master)
अणु
	व्योम __iomem *base = master->cf_mem + HDR_OFFSET;

	setup_common_fw_config(master, base);
	ioग_लिखो32be(FW_CONTROL_CONT_CLOCK|FW_CONTROL_DUMMY_RD, base + HDR_FW_CONTROL);
पूर्ण

अटल पूर्णांक setup_gpios_क्रम_copro(काष्ठा fsi_master_acf *master)
अणु

	पूर्णांक rc;

	/* This aren't under ColdFire control, just set them up appropriately */
	gpiod_direction_output(master->gpio_mux, 1);
	gpiod_direction_output(master->gpio_enable, 1);

	/* Those are under ColdFire control, let it configure them */
	rc = aspeed_gpio_copro_grab_gpio(master->gpio_clk, &master->gpio_clk_vreg,
					 &master->gpio_clk_dreg, &master->gpio_clk_bit);
	अगर (rc) अणु
		dev_err(master->dev, "failed to assign clock gpio to coprocessor\n");
		वापस rc;
	पूर्ण
	rc = aspeed_gpio_copro_grab_gpio(master->gpio_data, &master->gpio_dat_vreg,
					 &master->gpio_dat_dreg, &master->gpio_dat_bit);
	अगर (rc) अणु
		dev_err(master->dev, "failed to assign data gpio to coprocessor\n");
		aspeed_gpio_copro_release_gpio(master->gpio_clk);
		वापस rc;
	पूर्ण
	rc = aspeed_gpio_copro_grab_gpio(master->gpio_trans, &master->gpio_tra_vreg,
					 &master->gpio_tra_dreg, &master->gpio_tra_bit);
	अगर (rc) अणु
		dev_err(master->dev, "failed to assign trans gpio to coprocessor\n");
		aspeed_gpio_copro_release_gpio(master->gpio_clk);
		aspeed_gpio_copro_release_gpio(master->gpio_data);
		वापस rc;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम release_copro_gpios(काष्ठा fsi_master_acf *master)
अणु
	aspeed_gpio_copro_release_gpio(master->gpio_clk);
	aspeed_gpio_copro_release_gpio(master->gpio_data);
	aspeed_gpio_copro_release_gpio(master->gpio_trans);
पूर्ण

अटल पूर्णांक load_copro_firmware(काष्ठा fsi_master_acf *master)
अणु
	स्थिर काष्ठा firmware *fw;
	uपूर्णांक16_t sig = 0, wanted_sig;
	स्थिर u8 *data;
	माप_प्रकार size = 0;
	पूर्णांक rc;

	/* Get the binary */
	rc = request_firmware(&fw, FW_खाता_NAME, master->dev);
	अगर (rc) अणु
		dev_err(
			master->dev, "Error %d to load firmware '%s' !\n",
			rc, FW_खाता_NAME);
		वापस rc;
	पूर्ण

	/* Which image करो we want ? (shared vs. split घड़ी/data GPIOs) */
	अगर (master->gpio_clk_vreg == master->gpio_dat_vreg)
		wanted_sig = SYS_SIG_SHARED;
	अन्यथा
		wanted_sig = SYS_SIG_SPLIT;
	dev_dbg(master->dev, "Looking for image sig %04x\n", wanted_sig);

	/* Try to find it */
	क्रम (data = fw->data; data < (fw->data + fw->size);) अणु
		sig = be16_to_cpup((__be16 *)(data + HDR_OFFSET + HDR_SYS_SIG));
		size = be32_to_cpup((__be32 *)(data + HDR_OFFSET + HDR_FW_SIZE));
		अगर (sig == wanted_sig)
			अवरोध;
		data += size;
	पूर्ण
	अगर (sig != wanted_sig) अणु
		dev_err(master->dev, "Failed to locate image sig %04x in FW blob\n",
			wanted_sig);
		rc = -ENODEV;
		जाओ release_fw;
	पूर्ण
	अगर (size > master->cf_mem_size) अणु
		dev_err(master->dev, "FW size (%zd) bigger than memory reserve (%zd)\n",
			fw->size, master->cf_mem_size);
		rc = -ENOMEM;
	पूर्ण अन्यथा अणु
		स_नकल_toio(master->cf_mem, data, size);
	पूर्ण

release_fw:
	release_firmware(fw);
	वापस rc;
पूर्ण

अटल पूर्णांक check_firmware_image(काष्ठा fsi_master_acf *master)
अणु
	uपूर्णांक32_t fw_vers, fw_api, fw_options;

	fw_vers = ioपढ़ो16be(master->cf_mem + HDR_OFFSET + HDR_FW_VERS);
	fw_api = ioपढ़ो16be(master->cf_mem + HDR_OFFSET + HDR_API_VERS);
	fw_options = ioपढ़ो32be(master->cf_mem + HDR_OFFSET + HDR_FW_OPTIONS);
	master->trace_enabled = !!(fw_options & FW_OPTION_TRACE_EN);

	/* Check version and signature */
	dev_info(master->dev, "ColdFire initialized, firmware v%d API v%d.%d (trace %s)\n",
		 fw_vers, fw_api >> 8, fw_api & 0xff,
		 master->trace_enabled ? "enabled" : "disabled");

	अगर ((fw_api >> 8) != API_VERSION_MAJ) अणु
		dev_err(master->dev, "Unsupported coprocessor API version !\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक copro_enable_sw_irq(काष्ठा fsi_master_acf *master)
अणु
	पूर्णांक समयout;
	uपूर्णांक32_t val;

	/*
	 * Enable coprocessor पूर्णांकerrupt input. I've had problems getting the
	 * value to stick, so try in a loop
	 */
	क्रम (समयout = 0; समयout < 10; समयout++) अणु
		ioग_लिखो32(0x2, master->cvic + CVIC_EN_REG);
		val = ioपढ़ो32(master->cvic + CVIC_EN_REG);
		अगर (val & 2)
			अवरोध;
		msleep(1);
	पूर्ण
	अगर (!(val & 2)) अणु
		dev_err(master->dev, "Failed to enable coprocessor interrupt !\n");
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक fsi_master_acf_setup(काष्ठा fsi_master_acf *master)
अणु
	पूर्णांक समयout, rc;
	uपूर्णांक32_t val;

	/* Make sure the ColdFire is stopped  */
	reset_cf(master);

	/*
	 * Clear SRAM. This needs to happen beक्रमe we setup the GPIOs
	 * as we might start trying to arbitrate as soon as that happens.
	 */
	स_रखो_io(master->sram, 0, SRAM_SIZE);

	/* Configure GPIOs */
	rc = setup_gpios_क्रम_copro(master);
	अगर (rc)
		वापस rc;

	/* Load the firmware पूर्णांकo the reserved memory */
	rc = load_copro_firmware(master);
	अगर (rc)
		वापस rc;

	/* Read signature and check versions */
	rc = check_firmware_image(master);
	अगर (rc)
		वापस rc;

	/* Setup coldfire memory map */
	अगर (master->is_ast2500) अणु
		setup_ast2500_cf_maps(master);
		setup_ast2500_fw_config(master);
	पूर्ण अन्यथा अणु
		setup_ast2400_cf_maps(master);
		setup_ast2400_fw_config(master);
	पूर्ण

	/* Start the ColdFire */
	start_cf(master);

	/* Wait क्रम status रेजिस्टर to indicate command completion
	 * which संकेतs the initialization is complete
	 */
	क्रम (समयout = 0; समयout < 10; समयout++) अणु
		val = ioपढ़ो8(master->sram + CF_STARTED);
		अगर (val)
			अवरोध;
		msleep(1);
	पूर्ण
	अगर (!val) अणु
		dev_err(master->dev, "Coprocessor startup timeout !\n");
		rc = -ENODEV;
		जाओ err;
	पूर्ण

	/* Configure echo & send delay */
	ioग_लिखो8(master->t_send_delay, master->sram + SEND_DLY_REG);
	ioग_लिखो8(master->t_echo_delay, master->sram + ECHO_DLY_REG);

	/* Enable SW पूर्णांकerrupt to copro अगर any */
	अगर (master->cvic) अणु
		rc = copro_enable_sw_irq(master);
		अगर (rc)
			जाओ err;
	पूर्ण
	वापस 0;
 err:
	/* An error occurred, करोn't leave the coprocessor running */
	reset_cf(master);

	/* Release the GPIOs */
	release_copro_gpios(master);

	वापस rc;
पूर्ण


अटल व्योम fsi_master_acf_terminate(काष्ठा fsi_master_acf *master)
अणु
	अचिन्हित दीर्घ flags;

	/*
	 * A GPIO arbitration requestion could come in जबतक this is
	 * happening. To aव्योम problems, we disable पूर्णांकerrupts so it
	 * cannot preempt us on this CPU
	 */

	local_irq_save(flags);

	/* Stop the coprocessor */
	reset_cf(master);

	/* We mark the copro not-started */
	ioग_लिखो32(0, master->sram + CF_STARTED);

	/* We mark the ARB रेजिस्टर as having given up arbitration to
	 * deal with a potential race with the arbitration request
	 */
	ioग_लिखो8(ARB_ARM_ACK, master->sram + ARB_REG);

	local_irq_restore(flags);

	/* Return the GPIOs to the ARM */
	release_copro_gpios(master);
पूर्ण

अटल व्योम fsi_master_acf_setup_बाह्यal(काष्ठा fsi_master_acf *master)
अणु
	/* Setup GPIOs क्रम बाह्यal FSI master (FSP box) */
	gpiod_direction_output(master->gpio_mux, 0);
	gpiod_direction_output(master->gpio_trans, 0);
	gpiod_direction_output(master->gpio_enable, 1);
	gpiod_direction_input(master->gpio_clk);
	gpiod_direction_input(master->gpio_data);
पूर्ण

अटल पूर्णांक fsi_master_acf_link_enable(काष्ठा fsi_master *_master, पूर्णांक link,
				      bool enable)
अणु
	काष्ठा fsi_master_acf *master = to_fsi_master_acf(_master);
	पूर्णांक rc = -EBUSY;

	अगर (link != 0)
		वापस -ENODEV;

	mutex_lock(&master->lock);
	अगर (!master->बाह्यal_mode) अणु
		gpiod_set_value(master->gpio_enable, enable ? 1 : 0);
		rc = 0;
	पूर्ण
	mutex_unlock(&master->lock);

	वापस rc;
पूर्ण

अटल पूर्णांक fsi_master_acf_link_config(काष्ठा fsi_master *_master, पूर्णांक link,
				      u8 t_send_delay, u8 t_echo_delay)
अणु
	काष्ठा fsi_master_acf *master = to_fsi_master_acf(_master);

	अगर (link != 0)
		वापस -ENODEV;

	mutex_lock(&master->lock);
	master->t_send_delay = t_send_delay;
	master->t_echo_delay = t_echo_delay;
	dev_dbg(master->dev, "Changing delays: send=%d echo=%d\n",
		t_send_delay, t_echo_delay);
	ioग_लिखो8(master->t_send_delay, master->sram + SEND_DLY_REG);
	ioग_लिखो8(master->t_echo_delay, master->sram + ECHO_DLY_REG);
	mutex_unlock(&master->lock);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार बाह्यal_mode_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fsi_master_acf *master = dev_get_drvdata(dev);

	वापस snम_लिखो(buf, PAGE_SIZE - 1, "%u\n",
			master->बाह्यal_mode ? 1 : 0);
पूर्ण

अटल sमाप_प्रकार बाह्यal_mode_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा fsi_master_acf *master = dev_get_drvdata(dev);
	अचिन्हित दीर्घ val;
	bool बाह्यal_mode;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 0, &val);
	अगर (err)
		वापस err;

	बाह्यal_mode = !!val;

	mutex_lock(&master->lock);

	अगर (बाह्यal_mode == master->बाह्यal_mode) अणु
		mutex_unlock(&master->lock);
		वापस count;
	पूर्ण

	master->बाह्यal_mode = बाह्यal_mode;
	अगर (master->बाह्यal_mode) अणु
		fsi_master_acf_terminate(master);
		fsi_master_acf_setup_बाह्यal(master);
	पूर्ण अन्यथा
		fsi_master_acf_setup(master);

	mutex_unlock(&master->lock);

	fsi_master_rescan(&master->master);

	वापस count;
पूर्ण

अटल DEVICE_ATTR(बाह्यal_mode, 0664,
		बाह्यal_mode_show, बाह्यal_mode_store);

अटल पूर्णांक fsi_master_acf_gpio_request(व्योम *data)
अणु
	काष्ठा fsi_master_acf *master = data;
	पूर्णांक समयout;
	u8 val;

	/* Note: This करोesn't require holding out mutex */

	/* Write reqest */
	ioग_लिखो8(ARB_ARM_REQ, master->sram + ARB_REG);

	/*
	 * There is a race (which करोes happen at boot समय) when we get an
	 * arbitration request as we are either about to or just starting
	 * the coprocessor.
	 *
	 * To handle it, we first check अगर we are running. If not yet we
	 * check whether the copro is started in the SCU.
	 *
	 * If it's not started, we can basically just assume we have arbitration
	 * and वापस. Otherwise, we रुको normally expecting क्रम the arbitration
	 * to eventually complete.
	 */
	अगर (ioपढ़ो32(master->sram + CF_STARTED) == 0) अणु
		अचिन्हित पूर्णांक reg = 0;

		regmap_पढ़ो(master->scu, SCU_COPRO_CTRL, &reg);
		अगर (!(reg & SCU_COPRO_CLK_EN))
			वापस 0;
	पूर्ण

	/* Ring करोorbell अगर any */
	अगर (master->cvic)
		ioग_लिखो32(0x2, master->cvic + CVIC_TRIG_REG);

	क्रम (समयout = 0; समयout < 10000; समयout++) अणु
		val = ioपढ़ो8(master->sram + ARB_REG);
		अगर (val != ARB_ARM_REQ)
			अवरोध;
		udelay(1);
	पूर्ण

	/* If it failed, override anyway */
	अगर (val != ARB_ARM_ACK)
		dev_warn(master->dev, "GPIO request arbitration timeout\n");

	वापस 0;
पूर्ण

अटल पूर्णांक fsi_master_acf_gpio_release(व्योम *data)
अणु
	काष्ठा fsi_master_acf *master = data;

	/* Write release */
	ioग_लिखो8(0, master->sram + ARB_REG);

	/* Ring करोorbell अगर any */
	अगर (master->cvic)
		ioग_लिखो32(0x2, master->cvic + CVIC_TRIG_REG);

	वापस 0;
पूर्ण

अटल व्योम fsi_master_acf_release(काष्ठा device *dev)
अणु
	काष्ठा fsi_master_acf *master = to_fsi_master_acf(dev_to_fsi_master(dev));

	/* Cleanup, stop coprocessor */
	mutex_lock(&master->lock);
	fsi_master_acf_terminate(master);
	aspeed_gpio_copro_set_ops(शून्य, शून्य);
	mutex_unlock(&master->lock);

	/* Free resources */
	gen_pool_मुक्त(master->sram_pool, (अचिन्हित दीर्घ)master->sram, SRAM_SIZE);
	of_node_put(dev_of_node(master->dev));

	kमुक्त(master);
पूर्ण

अटल स्थिर काष्ठा aspeed_gpio_copro_ops fsi_master_acf_gpio_ops = अणु
	.request_access = fsi_master_acf_gpio_request,
	.release_access = fsi_master_acf_gpio_release,
पूर्ण;

अटल पूर्णांक fsi_master_acf_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np, *mnode = dev_of_node(&pdev->dev);
	काष्ठा genpool_data_fixed gpdf;
	काष्ठा fsi_master_acf *master;
	काष्ठा gpio_desc *gpio;
	काष्ठा resource res;
	uपूर्णांक32_t cf_mem_align;
	पूर्णांक rc;

	master = kzalloc(माप(*master), GFP_KERNEL);
	अगर (!master)
		वापस -ENOMEM;

	master->dev = &pdev->dev;
	master->master.dev.parent = master->dev;
	master->last_addr = LAST_ADDR_INVALID;

	/* AST2400 vs. AST2500 */
	master->is_ast2500 = of_device_is_compatible(mnode, "aspeed,ast2500-cf-fsi-master");

	/* Grab the SCU, we'll need to access it to configure the coprocessor */
	अगर (master->is_ast2500)
		master->scu = syscon_regmap_lookup_by_compatible("aspeed,ast2500-scu");
	अन्यथा
		master->scu = syscon_regmap_lookup_by_compatible("aspeed,ast2400-scu");
	अगर (IS_ERR(master->scu)) अणु
		dev_err(&pdev->dev, "failed to find SCU regmap\n");
		rc = PTR_ERR(master->scu);
		जाओ err_मुक्त;
	पूर्ण

	/* Grab all the GPIOs we need */
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

	/* Grab the reserved memory region (use DMA API instead ?) */
	np = of_parse_phandle(mnode, "memory-region", 0);
	अगर (!np) अणु
		dev_err(&pdev->dev, "Didn't find reserved memory\n");
		rc = -EINVAL;
		जाओ err_मुक्त;
	पूर्ण
	rc = of_address_to_resource(np, 0, &res);
	of_node_put(np);
	अगर (rc) अणु
		dev_err(&pdev->dev, "Couldn't address to resource for reserved memory\n");
		rc = -ENOMEM;
		जाओ err_मुक्त;
	पूर्ण
	master->cf_mem_size = resource_size(&res);
	master->cf_mem_addr = (uपूर्णांक32_t)res.start;
	cf_mem_align = master->is_ast2500 ? 0x00100000 : 0x00200000;
	अगर (master->cf_mem_addr & (cf_mem_align - 1)) अणु
		dev_err(&pdev->dev, "Reserved memory has insufficient alignment\n");
		rc = -ENOMEM;
		जाओ err_मुक्त;
	पूर्ण
	master->cf_mem = devm_ioremap_resource(&pdev->dev, &res);
 	अगर (IS_ERR(master->cf_mem)) अणु
		rc = PTR_ERR(master->cf_mem);
		dev_err(&pdev->dev, "Error %d mapping coldfire memory\n", rc);
 		जाओ err_मुक्त;
	पूर्ण
	dev_dbg(&pdev->dev, "DRAM allocation @%x\n", master->cf_mem_addr);

	/* AST2500 has a SW पूर्णांकerrupt to the coprocessor */
	अगर (master->is_ast2500) अणु
		/* Grab the CVIC (ColdFire पूर्णांकerrupts controller) */
		np = of_parse_phandle(mnode, "aspeed,cvic", 0);
		अगर (!np) अणु
			dev_err(&pdev->dev, "Didn't find CVIC\n");
			rc = -EINVAL;
			जाओ err_मुक्त;
		पूर्ण
		master->cvic = devm_of_iomap(&pdev->dev, np, 0, शून्य);
		अगर (IS_ERR(master->cvic)) अणु
			rc = PTR_ERR(master->cvic);
			dev_err(&pdev->dev, "Error %d mapping CVIC\n", rc);
			जाओ err_मुक्त;
		पूर्ण
		rc = of_property_पढ़ो_u32(np, "copro-sw-interrupts",
					  &master->cvic_sw_irq);
		अगर (rc) अणु
			dev_err(&pdev->dev, "Can't find coprocessor SW interrupt\n");
			जाओ err_मुक्त;
		पूर्ण
	पूर्ण

	/* Grab the SRAM */
	master->sram_pool = of_gen_pool_get(dev_of_node(&pdev->dev), "aspeed,sram", 0);
	अगर (!master->sram_pool) अणु
		rc = -ENODEV;
		dev_err(&pdev->dev, "Can't find sram pool\n");
		जाओ err_मुक्त;
	पूर्ण

	/* Current microcode only deals with fixed location in SRAM */
	gpdf.offset = 0;
	master->sram = (व्योम __iomem *)gen_pool_alloc_algo(master->sram_pool, SRAM_SIZE,
							   gen_pool_fixed_alloc, &gpdf);
	अगर (!master->sram) अणु
		rc = -ENOMEM;
		dev_err(&pdev->dev, "Failed to allocate sram from pool\n");
		जाओ err_मुक्त;
	पूर्ण
	dev_dbg(&pdev->dev, "SRAM allocation @%lx\n",
		(अचिन्हित दीर्घ)gen_pool_virt_to_phys(master->sram_pool,
						     (अचिन्हित दीर्घ)master->sram));

	/*
	 * Hookup with the GPIO driver क्रम arbitration of GPIO banks
	 * ownership.
	 */
	aspeed_gpio_copro_set_ops(&fsi_master_acf_gpio_ops, master);

	/* Default FSI command delays */
	master->t_send_delay = FSI_SEND_DELAY_CLOCKS;
	master->t_echo_delay = FSI_ECHO_DELAY_CLOCKS;
	master->master.n_links = 1;
	अगर (master->is_ast2500)
		master->master.flags = FSI_MASTER_FLAG_SWCLOCK;
	master->master.पढ़ो = fsi_master_acf_पढ़ो;
	master->master.ग_लिखो = fsi_master_acf_ग_लिखो;
	master->master.term = fsi_master_acf_term;
	master->master.send_अवरोध = fsi_master_acf_अवरोध;
	master->master.link_enable = fsi_master_acf_link_enable;
	master->master.link_config = fsi_master_acf_link_config;
	master->master.dev.of_node = of_node_get(dev_of_node(master->dev));
	master->master.dev.release = fsi_master_acf_release;
	platक्रमm_set_drvdata(pdev, master);
	mutex_init(&master->lock);

	mutex_lock(&master->lock);
	rc = fsi_master_acf_setup(master);
	mutex_unlock(&master->lock);
	अगर (rc)
		जाओ release_of_dev;

	rc = device_create_file(&pdev->dev, &dev_attr_बाह्यal_mode);
	अगर (rc)
		जाओ stop_copro;

	rc = fsi_master_रेजिस्टर(&master->master);
	अगर (!rc)
		वापस 0;

	device_हटाओ_file(master->dev, &dev_attr_बाह्यal_mode);
	put_device(&master->master.dev);
	वापस rc;

 stop_copro:
	fsi_master_acf_terminate(master);
 release_of_dev:
	aspeed_gpio_copro_set_ops(शून्य, शून्य);
	gen_pool_मुक्त(master->sram_pool, (अचिन्हित दीर्घ)master->sram, SRAM_SIZE);
	of_node_put(dev_of_node(master->dev));
 err_मुक्त:
	kमुक्त(master);
	वापस rc;
पूर्ण


अटल पूर्णांक fsi_master_acf_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fsi_master_acf *master = platक्रमm_get_drvdata(pdev);

	device_हटाओ_file(master->dev, &dev_attr_बाह्यal_mode);

	fsi_master_unरेजिस्टर(&master->master);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id fsi_master_acf_match[] = अणु
	अणु .compatible = "aspeed,ast2400-cf-fsi-master" पूर्ण,
	अणु .compatible = "aspeed,ast2500-cf-fsi-master" पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver fsi_master_acf = अणु
	.driver = अणु
		.name		= "fsi-master-acf",
		.of_match_table	= fsi_master_acf_match,
	पूर्ण,
	.probe	= fsi_master_acf_probe,
	.हटाओ = fsi_master_acf_हटाओ,
पूर्ण;

module_platक्रमm_driver(fsi_master_acf);
MODULE_LICENSE("GPL");
