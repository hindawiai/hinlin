<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR BSD-3-Clause)
// Copyright(c) 2015-17 Intel Corporation.

/*
 * Cadence SoundWire Master module
 * Used by Master driver
 */

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/soundwire/sdw_रेजिस्टरs.h>
#समावेश <linux/soundwire/sdw.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <linux/workqueue.h>
#समावेश "bus.h"
#समावेश "cadence_master.h"

अटल पूर्णांक पूर्णांकerrupt_mask;
module_param_named(cnds_mcp_पूर्णांक_mask, पूर्णांकerrupt_mask, पूर्णांक, 0444);
MODULE_PARM_DESC(cdns_mcp_पूर्णांक_mask, "Cadence MCP IntMask");

#घोषणा CDNS_MCP_CONFIG				0x0

#घोषणा CDNS_MCP_CONFIG_MCMD_RETRY		GENMASK(27, 24)
#घोषणा CDNS_MCP_CONFIG_MPREQ_DELAY		GENMASK(20, 16)
#घोषणा CDNS_MCP_CONFIG_MMASTER			BIT(7)
#घोषणा CDNS_MCP_CONFIG_BUS_REL			BIT(6)
#घोषणा CDNS_MCP_CONFIG_SNIFFER			BIT(5)
#घोषणा CDNS_MCP_CONFIG_SSPMOD			BIT(4)
#घोषणा CDNS_MCP_CONFIG_CMD			BIT(3)
#घोषणा CDNS_MCP_CONFIG_OP			GENMASK(2, 0)
#घोषणा CDNS_MCP_CONFIG_OP_NORMAL		0

#घोषणा CDNS_MCP_CONTROL			0x4

#घोषणा CDNS_MCP_CONTROL_RST_DELAY		GENMASK(10, 8)
#घोषणा CDNS_MCP_CONTROL_CMD_RST		BIT(7)
#घोषणा CDNS_MCP_CONTROL_SOFT_RST		BIT(6)
#घोषणा CDNS_MCP_CONTROL_SW_RST			BIT(5)
#घोषणा CDNS_MCP_CONTROL_HW_RST			BIT(4)
#घोषणा CDNS_MCP_CONTROL_CLK_PAUSE		BIT(3)
#घोषणा CDNS_MCP_CONTROL_CLK_STOP_CLR		BIT(2)
#घोषणा CDNS_MCP_CONTROL_CMD_ACCEPT		BIT(1)
#घोषणा CDNS_MCP_CONTROL_BLOCK_WAKEUP		BIT(0)

#घोषणा CDNS_MCP_CMDCTRL			0x8

#घोषणा CDNS_MCP_CMDCTRL_INSERT_PARITY_ERR	BIT(2)

#घोषणा CDNS_MCP_SSPSTAT			0xC
#घोषणा CDNS_MCP_FRAME_SHAPE			0x10
#घोषणा CDNS_MCP_FRAME_SHAPE_INIT		0x14
#घोषणा CDNS_MCP_FRAME_SHAPE_COL_MASK		GENMASK(2, 0)
#घोषणा CDNS_MCP_FRAME_SHAPE_ROW_MASK		GENMASK(7, 3)

#घोषणा CDNS_MCP_CONFIG_UPDATE			0x18
#घोषणा CDNS_MCP_CONFIG_UPDATE_BIT		BIT(0)

#घोषणा CDNS_MCP_PHYCTRL			0x1C
#घोषणा CDNS_MCP_SSP_CTRL0			0x20
#घोषणा CDNS_MCP_SSP_CTRL1			0x28
#घोषणा CDNS_MCP_CLK_CTRL0			0x30
#घोषणा CDNS_MCP_CLK_CTRL1			0x38
#घोषणा CDNS_MCP_CLK_MCLKD_MASK		GENMASK(7, 0)

#घोषणा CDNS_MCP_STAT				0x40

#घोषणा CDNS_MCP_STAT_ACTIVE_BANK		BIT(20)
#घोषणा CDNS_MCP_STAT_CLK_STOP			BIT(16)

#घोषणा CDNS_MCP_INTSTAT			0x44
#घोषणा CDNS_MCP_INTMASK			0x48

#घोषणा CDNS_MCP_INT_IRQ			BIT(31)
#घोषणा CDNS_MCP_INT_RESERVED1			GENMASK(30, 17)
#घोषणा CDNS_MCP_INT_WAKEUP			BIT(16)
#घोषणा CDNS_MCP_INT_SLAVE_RSVD			BIT(15)
#घोषणा CDNS_MCP_INT_SLAVE_ALERT		BIT(14)
#घोषणा CDNS_MCP_INT_SLAVE_ATTACH		BIT(13)
#घोषणा CDNS_MCP_INT_SLAVE_NATTACH		BIT(12)
#घोषणा CDNS_MCP_INT_SLAVE_MASK			GENMASK(15, 12)
#घोषणा CDNS_MCP_INT_DPINT			BIT(11)
#घोषणा CDNS_MCP_INT_CTRL_CLASH			BIT(10)
#घोषणा CDNS_MCP_INT_DATA_CLASH			BIT(9)
#घोषणा CDNS_MCP_INT_PARITY			BIT(8)
#घोषणा CDNS_MCP_INT_CMD_ERR			BIT(7)
#घोषणा CDNS_MCP_INT_RESERVED2			GENMASK(6, 4)
#घोषणा CDNS_MCP_INT_RX_NE			BIT(3)
#घोषणा CDNS_MCP_INT_RX_WL			BIT(2)
#घोषणा CDNS_MCP_INT_TXE			BIT(1)
#घोषणा CDNS_MCP_INT_TXF			BIT(0)
#घोषणा CDNS_MCP_INT_RESERVED (CDNS_MCP_INT_RESERVED1 | CDNS_MCP_INT_RESERVED2)

#घोषणा CDNS_MCP_INTSET				0x4C

#घोषणा CDNS_MCP_SLAVE_STAT			0x50
#घोषणा CDNS_MCP_SLAVE_STAT_MASK		GENMASK(1, 0)

#घोषणा CDNS_MCP_SLAVE_INTSTAT0			0x54
#घोषणा CDNS_MCP_SLAVE_INTSTAT1			0x58
#घोषणा CDNS_MCP_SLAVE_INTSTAT_NPRESENT		BIT(0)
#घोषणा CDNS_MCP_SLAVE_INTSTAT_ATTACHED		BIT(1)
#घोषणा CDNS_MCP_SLAVE_INTSTAT_ALERT		BIT(2)
#घोषणा CDNS_MCP_SLAVE_INTSTAT_RESERVED		BIT(3)
#घोषणा CDNS_MCP_SLAVE_STATUS_BITS		GENMASK(3, 0)
#घोषणा CDNS_MCP_SLAVE_STATUS_NUM		4

#घोषणा CDNS_MCP_SLAVE_INTMASK0			0x5C
#घोषणा CDNS_MCP_SLAVE_INTMASK1			0x60

#घोषणा CDNS_MCP_SLAVE_INTMASK0_MASK		GENMASK(31, 0)
#घोषणा CDNS_MCP_SLAVE_INTMASK1_MASK		GENMASK(15, 0)

#घोषणा CDNS_MCP_PORT_INTSTAT			0x64
#घोषणा CDNS_MCP_PDI_STAT			0x6C

#घोषणा CDNS_MCP_FIFOLEVEL			0x78
#घोषणा CDNS_MCP_FIFOSTAT			0x7C
#घोषणा CDNS_MCP_RX_FIFO_AVAIL			GENMASK(5, 0)

#घोषणा CDNS_MCP_CMD_BASE			0x80
#घोषणा CDNS_MCP_RESP_BASE			0x80
#घोषणा CDNS_MCP_CMD_LEN			0x20
#घोषणा CDNS_MCP_CMD_WORD_LEN			0x4

#घोषणा CDNS_MCP_CMD_SSP_TAG			BIT(31)
#घोषणा CDNS_MCP_CMD_COMMAND			GENMASK(30, 28)
#घोषणा CDNS_MCP_CMD_DEV_ADDR			GENMASK(27, 24)
#घोषणा CDNS_MCP_CMD_REG_ADDR			GENMASK(23, 8)
#घोषणा CDNS_MCP_CMD_REG_DATA			GENMASK(7, 0)

#घोषणा CDNS_MCP_CMD_READ			2
#घोषणा CDNS_MCP_CMD_WRITE			3

#घोषणा CDNS_MCP_RESP_RDATA			GENMASK(15, 8)
#घोषणा CDNS_MCP_RESP_ACK			BIT(0)
#घोषणा CDNS_MCP_RESP_NACK			BIT(1)

#घोषणा CDNS_DP_SIZE				128

#घोषणा CDNS_DPN_B0_CONFIG(n)			(0x100 + CDNS_DP_SIZE * (n))
#घोषणा CDNS_DPN_B0_CH_EN(n)			(0x104 + CDNS_DP_SIZE * (n))
#घोषणा CDNS_DPN_B0_SAMPLE_CTRL(n)		(0x108 + CDNS_DP_SIZE * (n))
#घोषणा CDNS_DPN_B0_OFFSET_CTRL(n)		(0x10C + CDNS_DP_SIZE * (n))
#घोषणा CDNS_DPN_B0_HCTRL(n)			(0x110 + CDNS_DP_SIZE * (n))
#घोषणा CDNS_DPN_B0_ASYNC_CTRL(n)		(0x114 + CDNS_DP_SIZE * (n))

#घोषणा CDNS_DPN_B1_CONFIG(n)			(0x118 + CDNS_DP_SIZE * (n))
#घोषणा CDNS_DPN_B1_CH_EN(n)			(0x11C + CDNS_DP_SIZE * (n))
#घोषणा CDNS_DPN_B1_SAMPLE_CTRL(n)		(0x120 + CDNS_DP_SIZE * (n))
#घोषणा CDNS_DPN_B1_OFFSET_CTRL(n)		(0x124 + CDNS_DP_SIZE * (n))
#घोषणा CDNS_DPN_B1_HCTRL(n)			(0x128 + CDNS_DP_SIZE * (n))
#घोषणा CDNS_DPN_B1_ASYNC_CTRL(n)		(0x12C + CDNS_DP_SIZE * (n))

#घोषणा CDNS_DPN_CONFIG_BPM			BIT(18)
#घोषणा CDNS_DPN_CONFIG_BGC			GENMASK(17, 16)
#घोषणा CDNS_DPN_CONFIG_WL			GENMASK(12, 8)
#घोषणा CDNS_DPN_CONFIG_PORT_DAT		GENMASK(3, 2)
#घोषणा CDNS_DPN_CONFIG_PORT_FLOW		GENMASK(1, 0)

#घोषणा CDNS_DPN_SAMPLE_CTRL_SI			GENMASK(15, 0)

#घोषणा CDNS_DPN_OFFSET_CTRL_1			GENMASK(7, 0)
#घोषणा CDNS_DPN_OFFSET_CTRL_2			GENMASK(15, 8)

#घोषणा CDNS_DPN_HCTRL_HSTOP			GENMASK(3, 0)
#घोषणा CDNS_DPN_HCTRL_HSTART			GENMASK(7, 4)
#घोषणा CDNS_DPN_HCTRL_LCTRL			GENMASK(10, 8)

#घोषणा CDNS_PORTCTRL				0x130
#घोषणा CDNS_PORTCTRL_TEST_FAILED		BIT(1)
#घोषणा CDNS_PORTCTRL_सूचीN			BIT(7)
#घोषणा CDNS_PORTCTRL_BANK_INVERT		BIT(8)

#घोषणा CDNS_PORT_OFFSET			0x80

#घोषणा CDNS_PDI_CONFIG(n)			(0x1100 + (n) * 16)

#घोषणा CDNS_PDI_CONFIG_SOFT_RESET		BIT(24)
#घोषणा CDNS_PDI_CONFIG_CHANNEL			GENMASK(15, 8)
#घोषणा CDNS_PDI_CONFIG_PORT			GENMASK(4, 0)

/* Driver शेषs */
#घोषणा CDNS_TX_TIMEOUT				500

#घोषणा CDNS_SCP_RX_FIFOLEVEL			0x2

/*
 * रेजिस्टर accessor helpers
 */
अटल अंतरभूत u32 cdns_पढ़ोl(काष्ठा sdw_cdns *cdns, पूर्णांक offset)
अणु
	वापस पढ़ोl(cdns->रेजिस्टरs + offset);
पूर्ण

अटल अंतरभूत व्योम cdns_ग_लिखोl(काष्ठा sdw_cdns *cdns, पूर्णांक offset, u32 value)
अणु
	ग_लिखोl(value, cdns->रेजिस्टरs + offset);
पूर्ण

अटल अंतरभूत व्योम cdns_updatel(काष्ठा sdw_cdns *cdns,
				पूर्णांक offset, u32 mask, u32 val)
अणु
	u32 पंचांगp;

	पंचांगp = cdns_पढ़ोl(cdns, offset);
	पंचांगp = (पंचांगp & ~mask) | val;
	cdns_ग_लिखोl(cdns, offset, पंचांगp);
पूर्ण

अटल पूर्णांक cdns_set_रुको(काष्ठा sdw_cdns *cdns, पूर्णांक offset, u32 mask, u32 value)
अणु
	पूर्णांक समयout = 10;
	u32 reg_पढ़ो;

	/* Wait क्रम bit to be set */
	करो अणु
		reg_पढ़ो = पढ़ोl(cdns->रेजिस्टरs + offset);
		अगर ((reg_पढ़ो & mask) == value)
			वापस 0;

		समयout--;
		usleep_range(50, 100);
	पूर्ण जबतक (समयout != 0);

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक cdns_clear_bit(काष्ठा sdw_cdns *cdns, पूर्णांक offset, u32 value)
अणु
	ग_लिखोl(value, cdns->रेजिस्टरs + offset);

	/* Wait क्रम bit to be self cleared */
	वापस cdns_set_रुको(cdns, offset, value, 0);
पूर्ण

/*
 * all changes to the MCP_CONFIG, MCP_CONTROL, MCP_CMDCTRL and MCP_PHYCTRL
 * need to be confirmed with a ग_लिखो to MCP_CONFIG_UPDATE
 */
अटल पूर्णांक cdns_config_update(काष्ठा sdw_cdns *cdns)
अणु
	पूर्णांक ret;

	अगर (sdw_cdns_is_घड़ी_stop(cdns)) अणु
		dev_err(cdns->dev, "Cannot program MCP_CONFIG_UPDATE in ClockStopMode\n");
		वापस -EINVAL;
	पूर्ण

	ret = cdns_clear_bit(cdns, CDNS_MCP_CONFIG_UPDATE,
			     CDNS_MCP_CONFIG_UPDATE_BIT);
	अगर (ret < 0)
		dev_err(cdns->dev, "Config update timedout\n");

	वापस ret;
पूर्ण

/*
 * debugfs
 */
#अगर_घोषित CONFIG_DEBUG_FS

#घोषणा RD_BUF (2 * PAGE_SIZE)

अटल sमाप_प्रकार cdns_प्र_लिखो(काष्ठा sdw_cdns *cdns,
			    अक्षर *buf, माप_प्रकार pos, अचिन्हित पूर्णांक reg)
अणु
	वापस scnम_लिखो(buf + pos, RD_BUF - pos,
			 "%4x\t%8x\n", reg, cdns_पढ़ोl(cdns, reg));
पूर्ण

अटल पूर्णांक cdns_reg_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा sdw_cdns *cdns = s->निजी;
	अक्षर *buf;
	sमाप_प्रकार ret;
	पूर्णांक num_ports;
	पूर्णांक i, j;

	buf = kzalloc(RD_BUF, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	ret = scnम_लिखो(buf, RD_BUF, "Register  Value\n");
	ret += scnम_लिखो(buf + ret, RD_BUF - ret, "\nMCP Registers\n");
	/* 8 MCP रेजिस्टरs */
	क्रम (i = CDNS_MCP_CONFIG; i <= CDNS_MCP_PHYCTRL; i += माप(u32))
		ret += cdns_प्र_लिखो(cdns, buf, ret, i);

	ret += scnम_लिखो(buf + ret, RD_BUF - ret,
			 "\nStatus & Intr Registers\n");
	/* 13 Status & Intr रेजिस्टरs (offsets 0x70 and 0x74 not defined) */
	क्रम (i = CDNS_MCP_STAT; i <=  CDNS_MCP_FIFOSTAT; i += माप(u32))
		ret += cdns_प्र_लिखो(cdns, buf, ret, i);

	ret += scnम_लिखो(buf + ret, RD_BUF - ret,
			 "\nSSP & Clk ctrl Registers\n");
	ret += cdns_प्र_लिखो(cdns, buf, ret, CDNS_MCP_SSP_CTRL0);
	ret += cdns_प्र_लिखो(cdns, buf, ret, CDNS_MCP_SSP_CTRL1);
	ret += cdns_प्र_लिखो(cdns, buf, ret, CDNS_MCP_CLK_CTRL0);
	ret += cdns_प्र_लिखो(cdns, buf, ret, CDNS_MCP_CLK_CTRL1);

	ret += scnम_लिखो(buf + ret, RD_BUF - ret,
			 "\nDPn B0 Registers\n");

	num_ports = cdns->num_ports;

	क्रम (i = 0; i < num_ports; i++) अणु
		ret += scnम_लिखो(buf + ret, RD_BUF - ret,
				 "\nDP-%d\n", i);
		क्रम (j = CDNS_DPN_B0_CONFIG(i);
		     j < CDNS_DPN_B0_ASYNC_CTRL(i); j += माप(u32))
			ret += cdns_प्र_लिखो(cdns, buf, ret, j);
	पूर्ण

	ret += scnम_लिखो(buf + ret, RD_BUF - ret,
			 "\nDPn B1 Registers\n");
	क्रम (i = 0; i < num_ports; i++) अणु
		ret += scnम_लिखो(buf + ret, RD_BUF - ret,
				 "\nDP-%d\n", i);

		क्रम (j = CDNS_DPN_B1_CONFIG(i);
		     j < CDNS_DPN_B1_ASYNC_CTRL(i); j += माप(u32))
			ret += cdns_प्र_लिखो(cdns, buf, ret, j);
	पूर्ण

	ret += scnम_लिखो(buf + ret, RD_BUF - ret,
			 "\nDPn Control Registers\n");
	क्रम (i = 0; i < num_ports; i++)
		ret += cdns_प्र_लिखो(cdns, buf, ret,
				CDNS_PORTCTRL + i * CDNS_PORT_OFFSET);

	ret += scnम_लिखो(buf + ret, RD_BUF - ret,
			 "\nPDIn Config Registers\n");

	/* number of PDI and ports is पूर्णांकerchangeable */
	क्रम (i = 0; i < num_ports; i++)
		ret += cdns_प्र_लिखो(cdns, buf, ret, CDNS_PDI_CONFIG(i));

	seq_म_लिखो(s, "%s", buf);
	kमुक्त(buf);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(cdns_reg);

अटल पूर्णांक cdns_hw_reset(व्योम *data, u64 value)
अणु
	काष्ठा sdw_cdns *cdns = data;
	पूर्णांक ret;

	अगर (value != 1)
		वापस -EINVAL;

	/* Userspace changed the hardware state behind the kernel's back */
	add_taपूर्णांक(TAINT_USER, LOCKDEP_STILL_OK);

	ret = sdw_cdns_निकास_reset(cdns);

	dev_dbg(cdns->dev, "link hw_reset done: %d\n", ret);

	वापस ret;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(cdns_hw_reset_fops, शून्य, cdns_hw_reset, "%llu\n");

अटल पूर्णांक cdns_parity_error_injection(व्योम *data, u64 value)
अणु
	काष्ठा sdw_cdns *cdns = data;
	काष्ठा sdw_bus *bus;
	पूर्णांक ret;

	अगर (value != 1)
		वापस -EINVAL;

	bus = &cdns->bus;

	/*
	 * Resume Master device. If this results in a bus reset, the
	 * Slave devices will re-attach and be re-क्रमागतerated.
	 */
	ret = pm_runसमय_get_sync(bus->dev);
	अगर (ret < 0 && ret != -EACCES) अणु
		dev_err_ratelimited(cdns->dev,
				    "pm_runtime_get_sync failed in %s, ret %d\n",
				    __func__, ret);
		pm_runसमय_put_noidle(bus->dev);
		वापस ret;
	पूर्ण

	/*
	 * रुको दीर्घ enough क्रम Slave(s) to be in steady state. This
	 * करोes not need to be super precise.
	 */
	msleep(200);

	/*
	 * Take the bus lock here to make sure that any bus transactions
	 * will be queued जबतक we inject a parity error on a dummy पढ़ो
	 */
	mutex_lock(&bus->bus_lock);

	/* program hardware to inject parity error */
	cdns_updatel(cdns, CDNS_MCP_CMDCTRL,
		     CDNS_MCP_CMDCTRL_INSERT_PARITY_ERR,
		     CDNS_MCP_CMDCTRL_INSERT_PARITY_ERR);

	/* commit changes */
	cdns_updatel(cdns, CDNS_MCP_CONFIG_UPDATE,
		     CDNS_MCP_CONFIG_UPDATE_BIT,
		     CDNS_MCP_CONFIG_UPDATE_BIT);

	/* करो a broadcast dummy पढ़ो to aव्योम bus clashes */
	ret = sdw_bपढ़ो_no_pm_unlocked(&cdns->bus, 0xf, SDW_SCP_DEVID_0);
	dev_info(cdns->dev, "parity error injection, read: %d\n", ret);

	/* program hardware to disable parity error */
	cdns_updatel(cdns, CDNS_MCP_CMDCTRL,
		     CDNS_MCP_CMDCTRL_INSERT_PARITY_ERR,
		     0);

	/* commit changes */
	cdns_updatel(cdns, CDNS_MCP_CONFIG_UPDATE,
		     CDNS_MCP_CONFIG_UPDATE_BIT,
		     CDNS_MCP_CONFIG_UPDATE_BIT);

	/* Continue bus operation with parity error injection disabled */
	mutex_unlock(&bus->bus_lock);

	/* Userspace changed the hardware state behind the kernel's back */
	add_taपूर्णांक(TAINT_USER, LOCKDEP_STILL_OK);

	/*
	 * allow Master device to enter pm_runसमय suspend. This may
	 * also result in Slave devices suspending.
	 */
	pm_runसमय_mark_last_busy(bus->dev);
	pm_runसमय_put_स्वतःsuspend(bus->dev);

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(cdns_parity_error_fops, शून्य,
			 cdns_parity_error_injection, "%llu\n");

/**
 * sdw_cdns_debugfs_init() - Cadence debugfs init
 * @cdns: Cadence instance
 * @root: debugfs root
 */
व्योम sdw_cdns_debugfs_init(काष्ठा sdw_cdns *cdns, काष्ठा dentry *root)
अणु
	debugfs_create_file("cdns-registers", 0400, root, cdns, &cdns_reg_fops);

	debugfs_create_file("cdns-hw-reset", 0200, root, cdns,
			    &cdns_hw_reset_fops);

	debugfs_create_file("cdns-parity-error-injection", 0200, root, cdns,
			    &cdns_parity_error_fops);
पूर्ण
EXPORT_SYMBOL_GPL(sdw_cdns_debugfs_init);

#पूर्ण_अगर /* CONFIG_DEBUG_FS */

/*
 * IO Calls
 */
अटल क्रमागत sdw_command_response
cdns_fill_msg_resp(काष्ठा sdw_cdns *cdns,
		   काष्ठा sdw_msg *msg, पूर्णांक count, पूर्णांक offset)
अणु
	पूर्णांक nack = 0, no_ack = 0;
	पूर्णांक i;

	/* check message response */
	क्रम (i = 0; i < count; i++) अणु
		अगर (!(cdns->response_buf[i] & CDNS_MCP_RESP_ACK)) अणु
			no_ack = 1;
			dev_vdbg(cdns->dev, "Msg Ack not received, cmd %d\n", i);
		पूर्ण
		अगर (cdns->response_buf[i] & CDNS_MCP_RESP_NACK) अणु
			nack = 1;
			dev_err_ratelimited(cdns->dev, "Msg NACK received, cmd %d\n", i);
		पूर्ण
	पूर्ण

	अगर (nack) अणु
		dev_err_ratelimited(cdns->dev, "Msg NACKed for Slave %d\n", msg->dev_num);
		वापस SDW_CMD_FAIL;
	पूर्ण

	अगर (no_ack) अणु
		dev_dbg_ratelimited(cdns->dev, "Msg ignored for Slave %d\n", msg->dev_num);
		वापस SDW_CMD_IGNORED;
	पूर्ण

	/* fill response */
	क्रम (i = 0; i < count; i++)
		msg->buf[i + offset] = FIELD_GET(CDNS_MCP_RESP_RDATA, cdns->response_buf[i]);

	वापस SDW_CMD_OK;
पूर्ण

अटल क्रमागत sdw_command_response
_cdns_xfer_msg(काष्ठा sdw_cdns *cdns, काष्ठा sdw_msg *msg, पूर्णांक cmd,
	       पूर्णांक offset, पूर्णांक count, bool defer)
अणु
	अचिन्हित दीर्घ समय;
	u32 base, i, data;
	u16 addr;

	/* Program the watermark level क्रम RX FIFO */
	अगर (cdns->msg_count != count) अणु
		cdns_ग_लिखोl(cdns, CDNS_MCP_FIFOLEVEL, count);
		cdns->msg_count = count;
	पूर्ण

	base = CDNS_MCP_CMD_BASE;
	addr = msg->addr;

	क्रम (i = 0; i < count; i++) अणु
		data = FIELD_PREP(CDNS_MCP_CMD_DEV_ADDR, msg->dev_num);
		data |= FIELD_PREP(CDNS_MCP_CMD_COMMAND, cmd);
		data |= FIELD_PREP(CDNS_MCP_CMD_REG_ADDR, addr);
		addr++;

		अगर (msg->flags == SDW_MSG_FLAG_WRITE)
			data |= msg->buf[i + offset];

		data |= FIELD_PREP(CDNS_MCP_CMD_SSP_TAG, msg->ssp_sync);
		cdns_ग_लिखोl(cdns, base, data);
		base += CDNS_MCP_CMD_WORD_LEN;
	पूर्ण

	अगर (defer)
		वापस SDW_CMD_OK;

	/* रुको क्रम समयout or response */
	समय = रुको_क्रम_completion_समयout(&cdns->tx_complete,
					   msecs_to_jअगरfies(CDNS_TX_TIMEOUT));
	अगर (!समय) अणु
		dev_err(cdns->dev, "IO transfer timed out, cmd %d device %d addr %x len %d\n",
			cmd, msg->dev_num, msg->addr, msg->len);
		msg->len = 0;
		वापस SDW_CMD_TIMEOUT;
	पूर्ण

	वापस cdns_fill_msg_resp(cdns, msg, count, offset);
पूर्ण

अटल क्रमागत sdw_command_response
cdns_program_scp_addr(काष्ठा sdw_cdns *cdns, काष्ठा sdw_msg *msg)
अणु
	पूर्णांक nack = 0, no_ack = 0;
	अचिन्हित दीर्घ समय;
	u32 data[2], base;
	पूर्णांक i;

	/* Program the watermark level क्रम RX FIFO */
	अगर (cdns->msg_count != CDNS_SCP_RX_FIFOLEVEL) अणु
		cdns_ग_लिखोl(cdns, CDNS_MCP_FIFOLEVEL, CDNS_SCP_RX_FIFOLEVEL);
		cdns->msg_count = CDNS_SCP_RX_FIFOLEVEL;
	पूर्ण

	data[0] = FIELD_PREP(CDNS_MCP_CMD_DEV_ADDR, msg->dev_num);
	data[0] |= FIELD_PREP(CDNS_MCP_CMD_COMMAND, 0x3);
	data[1] = data[0];

	data[0] |= FIELD_PREP(CDNS_MCP_CMD_REG_ADDR, SDW_SCP_ADDRPAGE1);
	data[1] |= FIELD_PREP(CDNS_MCP_CMD_REG_ADDR, SDW_SCP_ADDRPAGE2);

	data[0] |= msg->addr_page1;
	data[1] |= msg->addr_page2;

	base = CDNS_MCP_CMD_BASE;
	cdns_ग_लिखोl(cdns, base, data[0]);
	base += CDNS_MCP_CMD_WORD_LEN;
	cdns_ग_लिखोl(cdns, base, data[1]);

	समय = रुको_क्रम_completion_समयout(&cdns->tx_complete,
					   msecs_to_jअगरfies(CDNS_TX_TIMEOUT));
	अगर (!समय) अणु
		dev_err(cdns->dev, "SCP Msg trf timed out\n");
		msg->len = 0;
		वापस SDW_CMD_TIMEOUT;
	पूर्ण

	/* check response the ग_लिखोs */
	क्रम (i = 0; i < 2; i++) अणु
		अगर (!(cdns->response_buf[i] & CDNS_MCP_RESP_ACK)) अणु
			no_ack = 1;
			dev_err(cdns->dev, "Program SCP Ack not received\n");
			अगर (cdns->response_buf[i] & CDNS_MCP_RESP_NACK) अणु
				nack = 1;
				dev_err(cdns->dev, "Program SCP NACK received\n");
			पूर्ण
		पूर्ण
	पूर्ण

	/* For NACK, NO ack, करोn't वापस err अगर we are in Broadcast mode */
	अगर (nack) अणु
		dev_err_ratelimited(cdns->dev,
				    "SCP_addrpage NACKed for Slave %d\n", msg->dev_num);
		वापस SDW_CMD_FAIL;
	पूर्ण

	अगर (no_ack) अणु
		dev_dbg_ratelimited(cdns->dev,
				    "SCP_addrpage ignored for Slave %d\n", msg->dev_num);
		वापस SDW_CMD_IGNORED;
	पूर्ण

	वापस SDW_CMD_OK;
पूर्ण

अटल पूर्णांक cdns_prep_msg(काष्ठा sdw_cdns *cdns, काष्ठा sdw_msg *msg, पूर्णांक *cmd)
अणु
	पूर्णांक ret;

	अगर (msg->page) अणु
		ret = cdns_program_scp_addr(cdns, msg);
		अगर (ret) अणु
			msg->len = 0;
			वापस ret;
		पूर्ण
	पूर्ण

	चयन (msg->flags) अणु
	हाल SDW_MSG_FLAG_READ:
		*cmd = CDNS_MCP_CMD_READ;
		अवरोध;

	हाल SDW_MSG_FLAG_WRITE:
		*cmd = CDNS_MCP_CMD_WRITE;
		अवरोध;

	शेष:
		dev_err(cdns->dev, "Invalid msg cmd: %d\n", msg->flags);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

क्रमागत sdw_command_response
cdns_xfer_msg(काष्ठा sdw_bus *bus, काष्ठा sdw_msg *msg)
अणु
	काष्ठा sdw_cdns *cdns = bus_to_cdns(bus);
	पूर्णांक cmd = 0, ret, i;

	ret = cdns_prep_msg(cdns, msg, &cmd);
	अगर (ret)
		वापस SDW_CMD_FAIL_OTHER;

	क्रम (i = 0; i < msg->len / CDNS_MCP_CMD_LEN; i++) अणु
		ret = _cdns_xfer_msg(cdns, msg, cmd, i * CDNS_MCP_CMD_LEN,
				     CDNS_MCP_CMD_LEN, false);
		अगर (ret < 0)
			जाओ निकास;
	पूर्ण

	अगर (!(msg->len % CDNS_MCP_CMD_LEN))
		जाओ निकास;

	ret = _cdns_xfer_msg(cdns, msg, cmd, i * CDNS_MCP_CMD_LEN,
			     msg->len % CDNS_MCP_CMD_LEN, false);

निकास:
	वापस ret;
पूर्ण
EXPORT_SYMBOL(cdns_xfer_msg);

क्रमागत sdw_command_response
cdns_xfer_msg_defer(काष्ठा sdw_bus *bus,
		    काष्ठा sdw_msg *msg, काष्ठा sdw_defer *defer)
अणु
	काष्ठा sdw_cdns *cdns = bus_to_cdns(bus);
	पूर्णांक cmd = 0, ret;

	/* क्रम defer only 1 message is supported */
	अगर (msg->len > 1)
		वापस -ENOTSUPP;

	ret = cdns_prep_msg(cdns, msg, &cmd);
	अगर (ret)
		वापस SDW_CMD_FAIL_OTHER;

	cdns->defer = defer;
	cdns->defer->length = msg->len;

	वापस _cdns_xfer_msg(cdns, msg, cmd, 0, msg->len, true);
पूर्ण
EXPORT_SYMBOL(cdns_xfer_msg_defer);

क्रमागत sdw_command_response
cdns_reset_page_addr(काष्ठा sdw_bus *bus, अचिन्हित पूर्णांक dev_num)
अणु
	काष्ठा sdw_cdns *cdns = bus_to_cdns(bus);
	काष्ठा sdw_msg msg;

	/* Create dummy message with valid device number */
	स_रखो(&msg, 0, माप(msg));
	msg.dev_num = dev_num;

	वापस cdns_program_scp_addr(cdns, &msg);
पूर्ण
EXPORT_SYMBOL(cdns_reset_page_addr);

/*
 * IRQ handling
 */

अटल व्योम cdns_पढ़ो_response(काष्ठा sdw_cdns *cdns)
अणु
	u32 num_resp, cmd_base;
	पूर्णांक i;

	num_resp = cdns_पढ़ोl(cdns, CDNS_MCP_FIFOSTAT);
	num_resp &= CDNS_MCP_RX_FIFO_AVAIL;

	cmd_base = CDNS_MCP_CMD_BASE;

	क्रम (i = 0; i < num_resp; i++) अणु
		cdns->response_buf[i] = cdns_पढ़ोl(cdns, cmd_base);
		cmd_base += CDNS_MCP_CMD_WORD_LEN;
	पूर्ण
पूर्ण

अटल पूर्णांक cdns_update_slave_status(काष्ठा sdw_cdns *cdns,
				    u64 slave_पूर्णांकstat)
अणु
	क्रमागत sdw_slave_status status[SDW_MAX_DEVICES + 1];
	bool is_slave = false;
	u32 mask;
	पूर्णांक i, set_status;

	स_रखो(status, 0, माप(status));

	क्रम (i = 0; i <= SDW_MAX_DEVICES; i++) अणु
		mask = (slave_पूर्णांकstat >> (i * CDNS_MCP_SLAVE_STATUS_NUM)) &
			CDNS_MCP_SLAVE_STATUS_BITS;
		अगर (!mask)
			जारी;

		is_slave = true;
		set_status = 0;

		अगर (mask & CDNS_MCP_SLAVE_INTSTAT_RESERVED) अणु
			status[i] = SDW_SLAVE_RESERVED;
			set_status++;
		पूर्ण

		अगर (mask & CDNS_MCP_SLAVE_INTSTAT_ATTACHED) अणु
			status[i] = SDW_SLAVE_ATTACHED;
			set_status++;
		पूर्ण

		अगर (mask & CDNS_MCP_SLAVE_INTSTAT_ALERT) अणु
			status[i] = SDW_SLAVE_ALERT;
			set_status++;
		पूर्ण

		अगर (mask & CDNS_MCP_SLAVE_INTSTAT_NPRESENT) अणु
			status[i] = SDW_SLAVE_UNATTACHED;
			set_status++;
		पूर्ण

		/* first check अगर Slave reported multiple status */
		अगर (set_status > 1) अणु
			u32 val;

			dev_warn_ratelimited(cdns->dev,
					     "Slave %d reported multiple Status: %d\n",
					     i, mask);

			/* check latest status extracted from PING commands */
			val = cdns_पढ़ोl(cdns, CDNS_MCP_SLAVE_STAT);
			val >>= (i * 2);

			चयन (val & 0x3) अणु
			हाल 0:
				status[i] = SDW_SLAVE_UNATTACHED;
				अवरोध;
			हाल 1:
				status[i] = SDW_SLAVE_ATTACHED;
				अवरोध;
			हाल 2:
				status[i] = SDW_SLAVE_ALERT;
				अवरोध;
			हाल 3:
			शेष:
				status[i] = SDW_SLAVE_RESERVED;
				अवरोध;
			पूर्ण

			dev_warn_ratelimited(cdns->dev,
					     "Slave %d status updated to %d\n",
					     i, status[i]);

		पूर्ण
	पूर्ण

	अगर (is_slave)
		वापस sdw_handle_slave_status(&cdns->bus, status);

	वापस 0;
पूर्ण

/**
 * sdw_cdns_irq() - Cadence पूर्णांकerrupt handler
 * @irq: irq number
 * @dev_id: irq context
 */
irqवापस_t sdw_cdns_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sdw_cdns *cdns = dev_id;
	u32 पूर्णांक_status;
	पूर्णांक ret = IRQ_HANDLED;

	/* Check अगर the link is up */
	अगर (!cdns->link_up)
		वापस IRQ_NONE;

	पूर्णांक_status = cdns_पढ़ोl(cdns, CDNS_MCP_INTSTAT);

	/* check क्रम reserved values पढ़ो as zero */
	अगर (पूर्णांक_status & CDNS_MCP_INT_RESERVED)
		वापस IRQ_NONE;

	अगर (!(पूर्णांक_status & CDNS_MCP_INT_IRQ))
		वापस IRQ_NONE;

	अगर (पूर्णांक_status & CDNS_MCP_INT_RX_WL) अणु
		cdns_पढ़ो_response(cdns);

		अगर (cdns->defer) अणु
			cdns_fill_msg_resp(cdns, cdns->defer->msg,
					   cdns->defer->length, 0);
			complete(&cdns->defer->complete);
			cdns->defer = शून्य;
		पूर्ण अन्यथा अणु
			complete(&cdns->tx_complete);
		पूर्ण
	पूर्ण

	अगर (पूर्णांक_status & CDNS_MCP_INT_PARITY) अणु
		/* Parity error detected by Master */
		dev_err_ratelimited(cdns->dev, "Parity error\n");
	पूर्ण

	अगर (पूर्णांक_status & CDNS_MCP_INT_CTRL_CLASH) अणु
		/* Slave is driving bit slot during control word */
		dev_err_ratelimited(cdns->dev, "Bus clash for control word\n");
	पूर्ण

	अगर (पूर्णांक_status & CDNS_MCP_INT_DATA_CLASH) अणु
		/*
		 * Multiple slaves trying to drive bit slot, or issue with
		 * ownership of data bits or Slave gone bonkers
		 */
		dev_err_ratelimited(cdns->dev, "Bus clash for data word\n");
	पूर्ण

	अगर (cdns->bus.params.m_data_mode != SDW_PORT_DATA_MODE_NORMAL &&
	    पूर्णांक_status & CDNS_MCP_INT_DPINT) अणु
		u32 port_पूर्णांकstat;

		/* just log which ports report an error */
		port_पूर्णांकstat = cdns_पढ़ोl(cdns, CDNS_MCP_PORT_INTSTAT);
		dev_err_ratelimited(cdns->dev, "DP interrupt: PortIntStat %8x\n",
				    port_पूर्णांकstat);

		/* clear status w/ ग_लिखो1 */
		cdns_ग_लिखोl(cdns, CDNS_MCP_PORT_INTSTAT, port_पूर्णांकstat);
	पूर्ण

	अगर (पूर्णांक_status & CDNS_MCP_INT_SLAVE_MASK) अणु
		/* Mask the Slave पूर्णांकerrupt and wake thपढ़ो */
		cdns_updatel(cdns, CDNS_MCP_INTMASK,
			     CDNS_MCP_INT_SLAVE_MASK, 0);

		पूर्णांक_status &= ~CDNS_MCP_INT_SLAVE_MASK;

		/*
		 * Deal with possible race condition between पूर्णांकerrupt
		 * handling and disabling पूर्णांकerrupts on suspend.
		 *
		 * If the master is in the process of disabling
		 * पूर्णांकerrupts, करोn't schedule a workqueue
		 */
		अगर (cdns->पूर्णांकerrupt_enabled)
			schedule_work(&cdns->work);
	पूर्ण

	cdns_ग_लिखोl(cdns, CDNS_MCP_INTSTAT, पूर्णांक_status);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(sdw_cdns_irq);

/**
 * cdns_update_slave_status_work - update slave status in a work since we will need to handle
 * other पूर्णांकerrupts eg. CDNS_MCP_INT_RX_WL during the update slave
 * process.
 * @work: cdns worker thपढ़ो
 */
अटल व्योम cdns_update_slave_status_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sdw_cdns *cdns =
		container_of(work, काष्ठा sdw_cdns, work);
	u32 slave0, slave1;
	u64 slave_पूर्णांकstat;

	slave0 = cdns_पढ़ोl(cdns, CDNS_MCP_SLAVE_INTSTAT0);
	slave1 = cdns_पढ़ोl(cdns, CDNS_MCP_SLAVE_INTSTAT1);

	/* combine the two status */
	slave_पूर्णांकstat = ((u64)slave1 << 32) | slave0;

	dev_dbg_ratelimited(cdns->dev, "Slave status change: 0x%llx\n", slave_पूर्णांकstat);

	cdns_update_slave_status(cdns, slave_पूर्णांकstat);
	cdns_ग_लिखोl(cdns, CDNS_MCP_SLAVE_INTSTAT0, slave0);
	cdns_ग_लिखोl(cdns, CDNS_MCP_SLAVE_INTSTAT1, slave1);

	/* clear and unmask Slave पूर्णांकerrupt now */
	cdns_ग_लिखोl(cdns, CDNS_MCP_INTSTAT, CDNS_MCP_INT_SLAVE_MASK);
	cdns_updatel(cdns, CDNS_MCP_INTMASK,
		     CDNS_MCP_INT_SLAVE_MASK, CDNS_MCP_INT_SLAVE_MASK);

पूर्ण

/*
 * init routines
 */

/**
 * sdw_cdns_निकास_reset() - Program reset parameters and start bus operations
 * @cdns: Cadence instance
 */
पूर्णांक sdw_cdns_निकास_reset(काष्ठा sdw_cdns *cdns)
अणु
	/* program maximum length reset to be safe */
	cdns_updatel(cdns, CDNS_MCP_CONTROL,
		     CDNS_MCP_CONTROL_RST_DELAY,
		     CDNS_MCP_CONTROL_RST_DELAY);

	/* use hardware generated reset */
	cdns_updatel(cdns, CDNS_MCP_CONTROL,
		     CDNS_MCP_CONTROL_HW_RST,
		     CDNS_MCP_CONTROL_HW_RST);

	/* commit changes */
	cdns_updatel(cdns, CDNS_MCP_CONFIG_UPDATE,
		     CDNS_MCP_CONFIG_UPDATE_BIT,
		     CDNS_MCP_CONFIG_UPDATE_BIT);

	/* करोn't रुको here */
	वापस 0;

पूर्ण
EXPORT_SYMBOL(sdw_cdns_निकास_reset);

/**
 * cdns_enable_slave_पूर्णांकerrupts() - Enable SDW slave पूर्णांकerrupts
 * @cdns: Cadence instance
 * @state: boolean क्रम true/false
 */
अटल व्योम cdns_enable_slave_पूर्णांकerrupts(काष्ठा sdw_cdns *cdns, bool state)
अणु
	u32 mask;

	mask = cdns_पढ़ोl(cdns, CDNS_MCP_INTMASK);
	अगर (state)
		mask |= CDNS_MCP_INT_SLAVE_MASK;
	अन्यथा
		mask &= ~CDNS_MCP_INT_SLAVE_MASK;

	cdns_ग_लिखोl(cdns, CDNS_MCP_INTMASK, mask);
पूर्ण

/**
 * sdw_cdns_enable_पूर्णांकerrupt() - Enable SDW पूर्णांकerrupts
 * @cdns: Cadence instance
 * @state: True अगर we are trying to enable पूर्णांकerrupt.
 */
पूर्णांक sdw_cdns_enable_पूर्णांकerrupt(काष्ठा sdw_cdns *cdns, bool state)
अणु
	u32 slave_पूर्णांकmask0 = 0;
	u32 slave_पूर्णांकmask1 = 0;
	u32 mask = 0;

	अगर (!state)
		जाओ update_masks;

	slave_पूर्णांकmask0 = CDNS_MCP_SLAVE_INTMASK0_MASK;
	slave_पूर्णांकmask1 = CDNS_MCP_SLAVE_INTMASK1_MASK;

	/* enable detection of all slave state changes */
	mask = CDNS_MCP_INT_SLAVE_MASK;

	/* enable detection of bus issues */
	mask |= CDNS_MCP_INT_CTRL_CLASH | CDNS_MCP_INT_DATA_CLASH |
		CDNS_MCP_INT_PARITY;

	/* port पूर्णांकerrupt limited to test modes क्रम now */
	अगर (cdns->bus.params.m_data_mode != SDW_PORT_DATA_MODE_NORMAL)
		mask |= CDNS_MCP_INT_DPINT;

	/* enable detection of RX fअगरo level */
	mask |= CDNS_MCP_INT_RX_WL;

	/*
	 * CDNS_MCP_INT_IRQ needs to be set otherwise all previous
	 * settings are irrelevant
	 */
	mask |= CDNS_MCP_INT_IRQ;

	अगर (पूर्णांकerrupt_mask) /* parameter override */
		mask = पूर्णांकerrupt_mask;

update_masks:
	/* clear slave पूर्णांकerrupt status beक्रमe enabling पूर्णांकerrupt */
	अगर (state) अणु
		u32 slave_state;

		slave_state = cdns_पढ़ोl(cdns, CDNS_MCP_SLAVE_INTSTAT0);
		cdns_ग_लिखोl(cdns, CDNS_MCP_SLAVE_INTSTAT0, slave_state);
		slave_state = cdns_पढ़ोl(cdns, CDNS_MCP_SLAVE_INTSTAT1);
		cdns_ग_लिखोl(cdns, CDNS_MCP_SLAVE_INTSTAT1, slave_state);
	पूर्ण
	cdns->पूर्णांकerrupt_enabled = state;

	/*
	 * Complete any on-going status updates beक्रमe updating masks,
	 * and cancel queued status updates.
	 *
	 * There could be a race with a new पूर्णांकerrupt thrown beक्रमe
	 * the 3 mask updates below are complete, so in the पूर्णांकerrupt
	 * we use the 'interrupt_enabled' status to prevent new work
	 * from being queued.
	 */
	अगर (!state)
		cancel_work_sync(&cdns->work);

	cdns_ग_लिखोl(cdns, CDNS_MCP_SLAVE_INTMASK0, slave_पूर्णांकmask0);
	cdns_ग_लिखोl(cdns, CDNS_MCP_SLAVE_INTMASK1, slave_पूर्णांकmask1);
	cdns_ग_लिखोl(cdns, CDNS_MCP_INTMASK, mask);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(sdw_cdns_enable_पूर्णांकerrupt);

अटल पूर्णांक cdns_allocate_pdi(काष्ठा sdw_cdns *cdns,
			     काष्ठा sdw_cdns_pdi **stream,
			     u32 num, u32 pdi_offset)
अणु
	काष्ठा sdw_cdns_pdi *pdi;
	पूर्णांक i;

	अगर (!num)
		वापस 0;

	pdi = devm_kसुस्मृति(cdns->dev, num, माप(*pdi), GFP_KERNEL);
	अगर (!pdi)
		वापस -ENOMEM;

	क्रम (i = 0; i < num; i++) अणु
		pdi[i].num = i + pdi_offset;
	पूर्ण

	*stream = pdi;
	वापस 0;
पूर्ण

/**
 * sdw_cdns_pdi_init() - PDI initialization routine
 *
 * @cdns: Cadence instance
 * @config: Stream configurations
 */
पूर्णांक sdw_cdns_pdi_init(काष्ठा sdw_cdns *cdns,
		      काष्ठा sdw_cdns_stream_config config)
अणु
	काष्ठा sdw_cdns_streams *stream;
	पूर्णांक offset;
	पूर्णांक ret;

	cdns->pcm.num_bd = config.pcm_bd;
	cdns->pcm.num_in = config.pcm_in;
	cdns->pcm.num_out = config.pcm_out;
	cdns->pdm.num_bd = config.pdm_bd;
	cdns->pdm.num_in = config.pdm_in;
	cdns->pdm.num_out = config.pdm_out;

	/* Allocate PDIs क्रम PCMs */
	stream = &cdns->pcm;

	/* we allocate PDI0 and PDI1 which are used क्रम Bulk */
	offset = 0;

	ret = cdns_allocate_pdi(cdns, &stream->bd,
				stream->num_bd, offset);
	अगर (ret)
		वापस ret;

	offset += stream->num_bd;

	ret = cdns_allocate_pdi(cdns, &stream->in,
				stream->num_in, offset);
	अगर (ret)
		वापस ret;

	offset += stream->num_in;

	ret = cdns_allocate_pdi(cdns, &stream->out,
				stream->num_out, offset);
	अगर (ret)
		वापस ret;

	/* Update total number of PCM PDIs */
	stream->num_pdi = stream->num_bd + stream->num_in + stream->num_out;
	cdns->num_ports = stream->num_pdi;

	/* Allocate PDIs क्रम PDMs */
	stream = &cdns->pdm;
	ret = cdns_allocate_pdi(cdns, &stream->bd,
				stream->num_bd, offset);
	अगर (ret)
		वापस ret;

	offset += stream->num_bd;

	ret = cdns_allocate_pdi(cdns, &stream->in,
				stream->num_in, offset);
	अगर (ret)
		वापस ret;

	offset += stream->num_in;

	ret = cdns_allocate_pdi(cdns, &stream->out,
				stream->num_out, offset);

	अगर (ret)
		वापस ret;

	/* Update total number of PDM PDIs */
	stream->num_pdi = stream->num_bd + stream->num_in + stream->num_out;
	cdns->num_ports += stream->num_pdi;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(sdw_cdns_pdi_init);

अटल u32 cdns_set_initial_frame_shape(पूर्णांक n_rows, पूर्णांक n_cols)
अणु
	u32 val;
	पूर्णांक c;
	पूर्णांक r;

	r = sdw_find_row_index(n_rows);
	c = sdw_find_col_index(n_cols);

	val = FIELD_PREP(CDNS_MCP_FRAME_SHAPE_ROW_MASK, r);
	val |= FIELD_PREP(CDNS_MCP_FRAME_SHAPE_COL_MASK, c);

	वापस val;
पूर्ण

अटल व्योम cdns_init_घड़ी_ctrl(काष्ठा sdw_cdns *cdns)
अणु
	काष्ठा sdw_bus *bus = &cdns->bus;
	काष्ठा sdw_master_prop *prop = &bus->prop;
	u32 val;
	u32 ssp_पूर्णांकerval;
	पूर्णांक भागider;

	/* Set घड़ी भागider */
	भागider	= (prop->mclk_freq / prop->max_clk_freq) - 1;

	cdns_updatel(cdns, CDNS_MCP_CLK_CTRL0,
		     CDNS_MCP_CLK_MCLKD_MASK, भागider);
	cdns_updatel(cdns, CDNS_MCP_CLK_CTRL1,
		     CDNS_MCP_CLK_MCLKD_MASK, भागider);

	/*
	 * Frame shape changes after initialization have to be करोne
	 * with the bank चयन mechanism
	 */
	val = cdns_set_initial_frame_shape(prop->शेष_row,
					   prop->शेष_col);
	cdns_ग_लिखोl(cdns, CDNS_MCP_FRAME_SHAPE_INIT, val);

	/* Set SSP पूर्णांकerval to शेष value */
	ssp_पूर्णांकerval = prop->शेष_frame_rate / SDW_CADENCE_GSYNC_HZ;
	cdns_ग_लिखोl(cdns, CDNS_MCP_SSP_CTRL0, ssp_पूर्णांकerval);
	cdns_ग_लिखोl(cdns, CDNS_MCP_SSP_CTRL1, ssp_पूर्णांकerval);
पूर्ण

/**
 * sdw_cdns_init() - Cadence initialization
 * @cdns: Cadence instance
 */
पूर्णांक sdw_cdns_init(काष्ठा sdw_cdns *cdns)
अणु
	u32 val;

	cdns_init_घड़ी_ctrl(cdns);

	/* reset msg_count to शेष value of FIFOLEVEL */
	cdns->msg_count = cdns_पढ़ोl(cdns, CDNS_MCP_FIFOLEVEL);

	/* flush command FIFOs */
	cdns_updatel(cdns, CDNS_MCP_CONTROL, CDNS_MCP_CONTROL_CMD_RST,
		     CDNS_MCP_CONTROL_CMD_RST);

	/* Set cmd accept mode */
	cdns_updatel(cdns, CDNS_MCP_CONTROL, CDNS_MCP_CONTROL_CMD_ACCEPT,
		     CDNS_MCP_CONTROL_CMD_ACCEPT);

	/* Configure mcp config */
	val = cdns_पढ़ोl(cdns, CDNS_MCP_CONFIG);

	/* enable bus operations with घड़ी and data */
	val &= ~CDNS_MCP_CONFIG_OP;
	val |= CDNS_MCP_CONFIG_OP_NORMAL;

	/* Set cmd mode क्रम Tx and Rx cmds */
	val &= ~CDNS_MCP_CONFIG_CMD;

	/* Disable snअगरfer mode */
	val &= ~CDNS_MCP_CONFIG_SNIFFER;

	/* Disable स्वतः bus release */
	val &= ~CDNS_MCP_CONFIG_BUS_REL;

	अगर (cdns->bus.multi_link)
		/* Set Multi-master mode to take gsync पूर्णांकo account */
		val |= CDNS_MCP_CONFIG_MMASTER;

	/* leave frame delay to hardware शेष of 0x1F */

	/* leave command retry to hardware शेष of 0 */

	cdns_ग_लिखोl(cdns, CDNS_MCP_CONFIG, val);

	/* changes will be committed later */
	वापस 0;
पूर्ण
EXPORT_SYMBOL(sdw_cdns_init);

पूर्णांक cdns_bus_conf(काष्ठा sdw_bus *bus, काष्ठा sdw_bus_params *params)
अणु
	काष्ठा sdw_master_prop *prop = &bus->prop;
	काष्ठा sdw_cdns *cdns = bus_to_cdns(bus);
	पूर्णांक mcp_clkctrl_off;
	पूर्णांक भागider;

	अगर (!params->curr_dr_freq) अणु
		dev_err(cdns->dev, "NULL curr_dr_freq\n");
		वापस -EINVAL;
	पूर्ण

	भागider	= prop->mclk_freq * SDW_DOUBLE_RATE_FACTOR /
		params->curr_dr_freq;
	भागider--; /* भागider is 1/(N+1) */

	अगर (params->next_bank)
		mcp_clkctrl_off = CDNS_MCP_CLK_CTRL1;
	अन्यथा
		mcp_clkctrl_off = CDNS_MCP_CLK_CTRL0;

	cdns_updatel(cdns, mcp_clkctrl_off, CDNS_MCP_CLK_MCLKD_MASK, भागider);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(cdns_bus_conf);

अटल पूर्णांक cdns_port_params(काष्ठा sdw_bus *bus,
			    काष्ठा sdw_port_params *p_params, अचिन्हित पूर्णांक bank)
अणु
	काष्ठा sdw_cdns *cdns = bus_to_cdns(bus);
	पूर्णांक dpn_config = 0, dpn_config_off;

	अगर (bank)
		dpn_config_off = CDNS_DPN_B1_CONFIG(p_params->num);
	अन्यथा
		dpn_config_off = CDNS_DPN_B0_CONFIG(p_params->num);

	dpn_config = cdns_पढ़ोl(cdns, dpn_config_off);

	u32p_replace_bits(&dpn_config, (p_params->bps - 1), CDNS_DPN_CONFIG_WL);
	u32p_replace_bits(&dpn_config, p_params->flow_mode, CDNS_DPN_CONFIG_PORT_FLOW);
	u32p_replace_bits(&dpn_config, p_params->data_mode, CDNS_DPN_CONFIG_PORT_DAT);

	cdns_ग_लिखोl(cdns, dpn_config_off, dpn_config);

	वापस 0;
पूर्ण

अटल पूर्णांक cdns_transport_params(काष्ठा sdw_bus *bus,
				 काष्ठा sdw_transport_params *t_params,
				 क्रमागत sdw_reg_bank bank)
अणु
	काष्ठा sdw_cdns *cdns = bus_to_cdns(bus);
	पूर्णांक dpn_offsetctrl = 0, dpn_offsetctrl_off;
	पूर्णांक dpn_config = 0, dpn_config_off;
	पूर्णांक dpn_hctrl = 0, dpn_hctrl_off;
	पूर्णांक num = t_params->port_num;
	पूर्णांक dpn_samplectrl_off;

	/*
	 * Note: Only full data port is supported on the Master side क्रम
	 * both PCM and PDM ports.
	 */

	अगर (bank) अणु
		dpn_config_off = CDNS_DPN_B1_CONFIG(num);
		dpn_samplectrl_off = CDNS_DPN_B1_SAMPLE_CTRL(num);
		dpn_hctrl_off = CDNS_DPN_B1_HCTRL(num);
		dpn_offsetctrl_off = CDNS_DPN_B1_OFFSET_CTRL(num);
	पूर्ण अन्यथा अणु
		dpn_config_off = CDNS_DPN_B0_CONFIG(num);
		dpn_samplectrl_off = CDNS_DPN_B0_SAMPLE_CTRL(num);
		dpn_hctrl_off = CDNS_DPN_B0_HCTRL(num);
		dpn_offsetctrl_off = CDNS_DPN_B0_OFFSET_CTRL(num);
	पूर्ण

	dpn_config = cdns_पढ़ोl(cdns, dpn_config_off);
	u32p_replace_bits(&dpn_config, t_params->blk_grp_ctrl, CDNS_DPN_CONFIG_BGC);
	u32p_replace_bits(&dpn_config, t_params->blk_pkg_mode, CDNS_DPN_CONFIG_BPM);
	cdns_ग_लिखोl(cdns, dpn_config_off, dpn_config);

	u32p_replace_bits(&dpn_offsetctrl, t_params->offset1, CDNS_DPN_OFFSET_CTRL_1);
	u32p_replace_bits(&dpn_offsetctrl, t_params->offset2, CDNS_DPN_OFFSET_CTRL_2);
	cdns_ग_लिखोl(cdns, dpn_offsetctrl_off,  dpn_offsetctrl);

	u32p_replace_bits(&dpn_hctrl, t_params->hstart, CDNS_DPN_HCTRL_HSTART);
	u32p_replace_bits(&dpn_hctrl, t_params->hstop, CDNS_DPN_HCTRL_HSTOP);
	u32p_replace_bits(&dpn_hctrl, t_params->lane_ctrl, CDNS_DPN_HCTRL_LCTRL);

	cdns_ग_लिखोl(cdns, dpn_hctrl_off, dpn_hctrl);
	cdns_ग_लिखोl(cdns, dpn_samplectrl_off, (t_params->sample_पूर्णांकerval - 1));

	वापस 0;
पूर्ण

अटल पूर्णांक cdns_port_enable(काष्ठा sdw_bus *bus,
			    काष्ठा sdw_enable_ch *enable_ch, अचिन्हित पूर्णांक bank)
अणु
	काष्ठा sdw_cdns *cdns = bus_to_cdns(bus);
	पूर्णांक dpn_chnen_off, ch_mask;

	अगर (bank)
		dpn_chnen_off = CDNS_DPN_B1_CH_EN(enable_ch->port_num);
	अन्यथा
		dpn_chnen_off = CDNS_DPN_B0_CH_EN(enable_ch->port_num);

	ch_mask = enable_ch->ch_mask * enable_ch->enable;
	cdns_ग_लिखोl(cdns, dpn_chnen_off, ch_mask);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा sdw_master_port_ops cdns_port_ops = अणु
	.dpn_set_port_params = cdns_port_params,
	.dpn_set_port_transport_params = cdns_transport_params,
	.dpn_port_enable_ch = cdns_port_enable,
पूर्ण;

/**
 * sdw_cdns_is_घड़ी_stop: Check घड़ी status
 *
 * @cdns: Cadence instance
 */
bool sdw_cdns_is_घड़ी_stop(काष्ठा sdw_cdns *cdns)
अणु
	वापस !!(cdns_पढ़ोl(cdns, CDNS_MCP_STAT) & CDNS_MCP_STAT_CLK_STOP);
पूर्ण
EXPORT_SYMBOL(sdw_cdns_is_घड़ी_stop);

/**
 * sdw_cdns_घड़ी_stop: Cadence घड़ी stop configuration routine
 *
 * @cdns: Cadence instance
 * @block_wake: prevent wakes अगर required by the platक्रमm
 */
पूर्णांक sdw_cdns_घड़ी_stop(काष्ठा sdw_cdns *cdns, bool block_wake)
अणु
	bool slave_present = false;
	काष्ठा sdw_slave *slave;
	पूर्णांक ret;

	/* Check suspend status */
	अगर (sdw_cdns_is_घड़ी_stop(cdns)) अणु
		dev_dbg(cdns->dev, "Clock is already stopped\n");
		वापस 0;
	पूर्ण

	/*
	 * Beक्रमe entering घड़ी stop we mask the Slave
	 * पूर्णांकerrupts. This helps aव्योम having to deal with e.g. a
	 * Slave becoming UNATTACHED जबतक the घड़ी is being stopped
	 */
	cdns_enable_slave_पूर्णांकerrupts(cdns, false);

	/*
	 * For specअगरic platक्रमms, it is required to be able to put
	 * master पूर्णांकo a state in which it ignores wake-up trials
	 * in घड़ी stop state
	 */
	अगर (block_wake)
		cdns_updatel(cdns, CDNS_MCP_CONTROL,
			     CDNS_MCP_CONTROL_BLOCK_WAKEUP,
			     CDNS_MCP_CONTROL_BLOCK_WAKEUP);

	list_क्रम_each_entry(slave, &cdns->bus.slaves, node) अणु
		अगर (slave->status == SDW_SLAVE_ATTACHED ||
		    slave->status == SDW_SLAVE_ALERT) अणु
			slave_present = true;
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * This CMD_ACCEPT should be used when there are no devices
	 * attached on the link when entering घड़ी stop mode. If this is
	 * not set and there is a broadcast ग_लिखो then the command ignored
	 * will be treated as a failure
	 */
	अगर (!slave_present)
		cdns_updatel(cdns, CDNS_MCP_CONTROL,
			     CDNS_MCP_CONTROL_CMD_ACCEPT,
			     CDNS_MCP_CONTROL_CMD_ACCEPT);
	अन्यथा
		cdns_updatel(cdns, CDNS_MCP_CONTROL,
			     CDNS_MCP_CONTROL_CMD_ACCEPT, 0);

	/* commit changes */
	ret = cdns_config_update(cdns);
	अगर (ret < 0) अणु
		dev_err(cdns->dev, "%s: config_update failed\n", __func__);
		वापस ret;
	पूर्ण

	/* Prepare slaves क्रम घड़ी stop */
	अगर (slave_present) अणु
		ret = sdw_bus_prep_clk_stop(&cdns->bus);
		अगर (ret < 0 && ret != -ENODATA) अणु
			dev_err(cdns->dev, "prepare clock stop failed %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	/*
	 * Enter घड़ी stop mode and only report errors अगर there are
	 * Slave devices present (ALERT or ATTACHED)
	 */
	ret = sdw_bus_clk_stop(&cdns->bus);
	अगर (ret < 0 && slave_present && ret != -ENODATA) अणु
		dev_err(cdns->dev, "bus clock stop failed %d\n", ret);
		वापस ret;
	पूर्ण

	ret = cdns_set_रुको(cdns, CDNS_MCP_STAT,
			    CDNS_MCP_STAT_CLK_STOP,
			    CDNS_MCP_STAT_CLK_STOP);
	अगर (ret < 0)
		dev_err(cdns->dev, "Clock stop failed %d\n", ret);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(sdw_cdns_घड़ी_stop);

/**
 * sdw_cdns_घड़ी_restart: Cadence PM घड़ी restart configuration routine
 *
 * @cdns: Cadence instance
 * @bus_reset: context may be lost जबतक in low घातer modes and the bus
 * may require a Severe Reset and re-क्रमागतeration after a wake.
 */
पूर्णांक sdw_cdns_घड़ी_restart(काष्ठा sdw_cdns *cdns, bool bus_reset)
अणु
	पूर्णांक ret;

	/* unmask Slave पूर्णांकerrupts that were masked when stopping the घड़ी */
	cdns_enable_slave_पूर्णांकerrupts(cdns, true);

	ret = cdns_clear_bit(cdns, CDNS_MCP_CONTROL,
			     CDNS_MCP_CONTROL_CLK_STOP_CLR);
	अगर (ret < 0) अणु
		dev_err(cdns->dev, "Couldn't exit from clock stop\n");
		वापस ret;
	पूर्ण

	ret = cdns_set_रुको(cdns, CDNS_MCP_STAT, CDNS_MCP_STAT_CLK_STOP, 0);
	अगर (ret < 0) अणु
		dev_err(cdns->dev, "clock stop exit failed %d\n", ret);
		वापस ret;
	पूर्ण

	cdns_updatel(cdns, CDNS_MCP_CONTROL,
		     CDNS_MCP_CONTROL_BLOCK_WAKEUP, 0);

	/*
	 * clear CMD_ACCEPT so that the command ignored
	 * will be treated as a failure during a broadcast ग_लिखो
	 */
	cdns_updatel(cdns, CDNS_MCP_CONTROL, CDNS_MCP_CONTROL_CMD_ACCEPT, 0);

	अगर (!bus_reset) अणु

		/* enable bus operations with घड़ी and data */
		cdns_updatel(cdns, CDNS_MCP_CONFIG,
			     CDNS_MCP_CONFIG_OP,
			     CDNS_MCP_CONFIG_OP_NORMAL);

		ret = cdns_config_update(cdns);
		अगर (ret < 0) अणु
			dev_err(cdns->dev, "%s: config_update failed\n", __func__);
			वापस ret;
		पूर्ण

		ret = sdw_bus_निकास_clk_stop(&cdns->bus);
		अगर (ret < 0)
			dev_err(cdns->dev, "bus failed to exit clock stop %d\n", ret);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(sdw_cdns_घड़ी_restart);

/**
 * sdw_cdns_probe() - Cadence probe routine
 * @cdns: Cadence instance
 */
पूर्णांक sdw_cdns_probe(काष्ठा sdw_cdns *cdns)
अणु
	init_completion(&cdns->tx_complete);
	cdns->bus.port_ops = &cdns_port_ops;

	INIT_WORK(&cdns->work, cdns_update_slave_status_work);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(sdw_cdns_probe);

पूर्णांक cdns_set_sdw_stream(काष्ठा snd_soc_dai *dai,
			व्योम *stream, bool pcm, पूर्णांक direction)
अणु
	काष्ठा sdw_cdns *cdns = snd_soc_dai_get_drvdata(dai);
	काष्ठा sdw_cdns_dma_data *dma;

	अगर (stream) अणु
		/* first paranoia check */
		अगर (direction == SNDRV_PCM_STREAM_PLAYBACK)
			dma = dai->playback_dma_data;
		अन्यथा
			dma = dai->capture_dma_data;

		अगर (dma) अणु
			dev_err(dai->dev,
				"dma_data already allocated for dai %s\n",
				dai->name);
			वापस -EINVAL;
		पूर्ण

		/* allocate and set dma info */
		dma = kzalloc(माप(*dma), GFP_KERNEL);
		अगर (!dma)
			वापस -ENOMEM;

		अगर (pcm)
			dma->stream_type = SDW_STREAM_PCM;
		अन्यथा
			dma->stream_type = SDW_STREAM_PDM;

		dma->bus = &cdns->bus;
		dma->link_id = cdns->instance;

		dma->stream = stream;

		अगर (direction == SNDRV_PCM_STREAM_PLAYBACK)
			dai->playback_dma_data = dma;
		अन्यथा
			dai->capture_dma_data = dma;
	पूर्ण अन्यथा अणु
		/* क्रम शून्य stream we release allocated dma_data */
		अगर (direction == SNDRV_PCM_STREAM_PLAYBACK) अणु
			kमुक्त(dai->playback_dma_data);
			dai->playback_dma_data = शून्य;
		पूर्ण अन्यथा अणु
			kमुक्त(dai->capture_dma_data);
			dai->capture_dma_data = शून्य;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(cdns_set_sdw_stream);

/**
 * cdns_find_pdi() - Find a मुक्त PDI
 *
 * @cdns: Cadence instance
 * @offset: Starting offset
 * @num: Number of PDIs
 * @pdi: PDI instances
 * @dai_id: DAI id
 *
 * Find a PDI क्रम a given PDI array. The PDI num and dai_id are
 * expected to match, वापस शून्य otherwise.
 */
अटल काष्ठा sdw_cdns_pdi *cdns_find_pdi(काष्ठा sdw_cdns *cdns,
					  अचिन्हित पूर्णांक offset,
					  अचिन्हित पूर्णांक num,
					  काष्ठा sdw_cdns_pdi *pdi,
					  पूर्णांक dai_id)
अणु
	पूर्णांक i;

	क्रम (i = offset; i < offset + num; i++)
		अगर (pdi[i].num == dai_id)
			वापस &pdi[i];

	वापस शून्य;
पूर्ण

/**
 * sdw_cdns_config_stream: Configure a stream
 *
 * @cdns: Cadence instance
 * @ch: Channel count
 * @dir: Data direction
 * @pdi: PDI to be used
 */
व्योम sdw_cdns_config_stream(काष्ठा sdw_cdns *cdns,
			    u32 ch, u32 dir, काष्ठा sdw_cdns_pdi *pdi)
अणु
	u32 offset, val = 0;

	अगर (dir == SDW_DATA_सूची_RX) अणु
		val = CDNS_PORTCTRL_सूचीN;

		अगर (cdns->bus.params.m_data_mode != SDW_PORT_DATA_MODE_NORMAL)
			val |= CDNS_PORTCTRL_TEST_FAILED;
	पूर्ण
	offset = CDNS_PORTCTRL + pdi->num * CDNS_PORT_OFFSET;
	cdns_updatel(cdns, offset,
		     CDNS_PORTCTRL_सूचीN | CDNS_PORTCTRL_TEST_FAILED,
		     val);

	val = pdi->num;
	val |= CDNS_PDI_CONFIG_SOFT_RESET;
	val |= FIELD_PREP(CDNS_PDI_CONFIG_CHANNEL, (1 << ch) - 1);
	cdns_ग_लिखोl(cdns, CDNS_PDI_CONFIG(pdi->num), val);
पूर्ण
EXPORT_SYMBOL(sdw_cdns_config_stream);

/**
 * sdw_cdns_alloc_pdi() - Allocate a PDI
 *
 * @cdns: Cadence instance
 * @stream: Stream to be allocated
 * @ch: Channel count
 * @dir: Data direction
 * @dai_id: DAI id
 */
काष्ठा sdw_cdns_pdi *sdw_cdns_alloc_pdi(काष्ठा sdw_cdns *cdns,
					काष्ठा sdw_cdns_streams *stream,
					u32 ch, u32 dir, पूर्णांक dai_id)
अणु
	काष्ठा sdw_cdns_pdi *pdi = शून्य;

	अगर (dir == SDW_DATA_सूची_RX)
		pdi = cdns_find_pdi(cdns, 0, stream->num_in, stream->in,
				    dai_id);
	अन्यथा
		pdi = cdns_find_pdi(cdns, 0, stream->num_out, stream->out,
				    dai_id);

	/* check अगर we found a PDI, अन्यथा find in bi-directional */
	अगर (!pdi)
		pdi = cdns_find_pdi(cdns, 2, stream->num_bd, stream->bd,
				    dai_id);

	अगर (pdi) अणु
		pdi->l_ch_num = 0;
		pdi->h_ch_num = ch - 1;
		pdi->dir = dir;
		pdi->ch_count = ch;
	पूर्ण

	वापस pdi;
पूर्ण
EXPORT_SYMBOL(sdw_cdns_alloc_pdi);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("Cadence Soundwire Library");
