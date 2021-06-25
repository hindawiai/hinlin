<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * NVIDIA Tegra xHCI host controller driver
 *
 * Copyright (C) 2014 NVIDIA Corporation
 * Copyright (C) 2014 Google, Inc.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/firmware.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/phy/tegra/xusb.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/reset.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb/otg.h>
#समावेश <linux/usb/phy.h>
#समावेश <linux/usb/role.h>
#समावेश <soc/tegra/pmc.h>

#समावेश "xhci.h"

#घोषणा TEGRA_XHCI_SS_HIGH_SPEED 120000000
#घोषणा TEGRA_XHCI_SS_LOW_SPEED   12000000

/* FPCI CFG रेजिस्टरs */
#घोषणा XUSB_CFG_1				0x004
#घोषणा  XUSB_IO_SPACE_EN			BIT(0)
#घोषणा  XUSB_MEM_SPACE_EN			BIT(1)
#घोषणा  XUSB_BUS_MASTER_EN			BIT(2)
#घोषणा XUSB_CFG_4				0x010
#घोषणा  XUSB_BASE_ADDR_SHIFT			15
#घोषणा  XUSB_BASE_ADDR_MASK			0x1ffff
#घोषणा XUSB_CFG_16				0x040
#घोषणा XUSB_CFG_24				0x060
#घोषणा XUSB_CFG_AXI_CFG			0x0f8
#घोषणा XUSB_CFG_ARU_C11_CSBRANGE		0x41c
#घोषणा XUSB_CFG_ARU_CONTEXT			0x43c
#घोषणा XUSB_CFG_ARU_CONTEXT_HS_PLS		0x478
#घोषणा XUSB_CFG_ARU_CONTEXT_FS_PLS		0x47c
#घोषणा XUSB_CFG_ARU_CONTEXT_HSFS_SPEED		0x480
#घोषणा XUSB_CFG_ARU_CONTEXT_HSFS_PP		0x484
#घोषणा XUSB_CFG_CSB_BASE_ADDR			0x800

/* FPCI mailbox रेजिस्टरs */
/* XUSB_CFG_ARU_MBOX_CMD */
#घोषणा  MBOX_DEST_FALC				BIT(27)
#घोषणा  MBOX_DEST_PME				BIT(28)
#घोषणा  MBOX_DEST_SMI				BIT(29)
#घोषणा  MBOX_DEST_XHCI				BIT(30)
#घोषणा  MBOX_INT_EN				BIT(31)
/* XUSB_CFG_ARU_MBOX_DATA_IN and XUSB_CFG_ARU_MBOX_DATA_OUT */
#घोषणा  CMD_DATA_SHIFT				0
#घोषणा  CMD_DATA_MASK				0xffffff
#घोषणा  CMD_TYPE_SHIFT				24
#घोषणा  CMD_TYPE_MASK				0xff
/* XUSB_CFG_ARU_MBOX_OWNER */
#घोषणा  MBOX_OWNER_NONE			0
#घोषणा  MBOX_OWNER_FW				1
#घोषणा  MBOX_OWNER_SW				2
#घोषणा XUSB_CFG_ARU_SMI_INTR			0x428
#घोषणा  MBOX_SMI_INTR_FW_HANG			BIT(1)
#घोषणा  MBOX_SMI_INTR_EN			BIT(3)

/* IPFS रेजिस्टरs */
#घोषणा IPFS_XUSB_HOST_MSI_BAR_SZ_0		0x0c0
#घोषणा IPFS_XUSB_HOST_MSI_AXI_BAR_ST_0		0x0c4
#घोषणा IPFS_XUSB_HOST_MSI_FPCI_BAR_ST_0	0x0c8
#घोषणा IPFS_XUSB_HOST_MSI_VEC0_0		0x100
#घोषणा IPFS_XUSB_HOST_MSI_EN_VEC0_0		0x140
#घोषणा IPFS_XUSB_HOST_CONFIGURATION_0		0x180
#घोषणा  IPFS_EN_FPCI				BIT(0)
#घोषणा IPFS_XUSB_HOST_FPCI_ERROR_MASKS_0	0x184
#घोषणा IPFS_XUSB_HOST_INTR_MASK_0		0x188
#घोषणा  IPFS_IP_INT_MASK			BIT(16)
#घोषणा IPFS_XUSB_HOST_INTR_ENABLE_0		0x198
#घोषणा IPFS_XUSB_HOST_UFPCI_CONFIG_0		0x19c
#घोषणा IPFS_XUSB_HOST_CLKGATE_HYSTERESIS_0	0x1bc
#घोषणा IPFS_XUSB_HOST_MCCIF_FIFOCTRL_0		0x1dc

#घोषणा CSB_PAGE_SELECT_MASK			0x7fffff
#घोषणा CSB_PAGE_SELECT_SHIFT			9
#घोषणा CSB_PAGE_OFFSET_MASK			0x1ff
#घोषणा CSB_PAGE_SELECT(addr)	((addr) >> (CSB_PAGE_SELECT_SHIFT) &	\
				 CSB_PAGE_SELECT_MASK)
#घोषणा CSB_PAGE_OFFSET(addr)	((addr) & CSB_PAGE_OFFSET_MASK)

/* Falcon CSB रेजिस्टरs */
#घोषणा XUSB_FALC_CPUCTL			0x100
#घोषणा  CPUCTL_STARTCPU			BIT(1)
#घोषणा  CPUCTL_STATE_HALTED			BIT(4)
#घोषणा  CPUCTL_STATE_STOPPED			BIT(5)
#घोषणा XUSB_FALC_BOOTVEC			0x104
#घोषणा XUSB_FALC_DMACTL			0x10c
#घोषणा XUSB_FALC_IMFILLRNG1			0x154
#घोषणा  IMFILLRNG1_TAG_MASK			0xffff
#घोषणा  IMFILLRNG1_TAG_LO_SHIFT		0
#घोषणा  IMFILLRNG1_TAG_HI_SHIFT		16
#घोषणा XUSB_FALC_IMFILLCTL			0x158

/* MP CSB रेजिस्टरs */
#घोषणा XUSB_CSB_MP_ILOAD_ATTR			0x101a00
#घोषणा XUSB_CSB_MP_ILOAD_BASE_LO		0x101a04
#घोषणा XUSB_CSB_MP_ILOAD_BASE_HI		0x101a08
#घोषणा XUSB_CSB_MP_L2IMEMOP_SIZE		0x101a10
#घोषणा  L2IMEMOP_SIZE_SRC_OFFSET_SHIFT		8
#घोषणा  L2IMEMOP_SIZE_SRC_OFFSET_MASK		0x3ff
#घोषणा  L2IMEMOP_SIZE_SRC_COUNT_SHIFT		24
#घोषणा  L2IMEMOP_SIZE_SRC_COUNT_MASK		0xff
#घोषणा XUSB_CSB_MP_L2IMEMOP_TRIG		0x101a14
#घोषणा  L2IMEMOP_ACTION_SHIFT			24
#घोषणा  L2IMEMOP_INVALIDATE_ALL		(0x40 << L2IMEMOP_ACTION_SHIFT)
#घोषणा  L2IMEMOP_LOAD_LOCKED_RESULT		(0x11 << L2IMEMOP_ACTION_SHIFT)
#घोषणा XUSB_CSB_MEMPOOL_L2IMEMOP_RESULT	0x101a18
#घोषणा  L2IMEMOP_RESULT_VLD			BIT(31)
#घोषणा XUSB_CSB_MP_APMAP			0x10181c
#घोषणा  APMAP_BOOTPATH				BIT(31)

#घोषणा IMEM_BLOCK_SIZE				256

काष्ठा tegra_xusb_fw_header अणु
	__le32 boot_loadaddr_in_imem;
	__le32 boot_codedfi_offset;
	__le32 boot_codetag;
	__le32 boot_codesize;
	__le32 phys_memaddr;
	__le16 reqphys_memsize;
	__le16 alloc_phys_memsize;
	__le32 rodata_img_offset;
	__le32 rodata_section_start;
	__le32 rodata_section_end;
	__le32 मुख्य_fnaddr;
	__le32 fwimg_cksum;
	__le32 fwimg_created_समय;
	__le32 imem_resident_start;
	__le32 imem_resident_end;
	__le32 idirect_start;
	__le32 idirect_end;
	__le32 l2_imem_start;
	__le32 l2_imem_end;
	__le32 version_id;
	u8 init_ddirect;
	u8 reserved[3];
	__le32 phys_addr_log_buffer;
	__le32 total_log_entries;
	__le32 dequeue_ptr;
	__le32 dummy_var[2];
	__le32 fwimg_len;
	u8 magic[8];
	__le32 ss_low_घातer_entry_समयout;
	u8 num_hsic_port;
	u8 padding[139]; /* Pad to 256 bytes */
पूर्ण;

काष्ठा tegra_xusb_phy_type अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक num;
पूर्ण;

काष्ठा tegra_xusb_mbox_regs अणु
	u16 cmd;
	u16 data_in;
	u16 data_out;
	u16 owner;
पूर्ण;

काष्ठा tegra_xusb_context_soc अणु
	काष्ठा अणु
		स्थिर अचिन्हित पूर्णांक *offsets;
		अचिन्हित पूर्णांक num_offsets;
	पूर्ण ipfs;

	काष्ठा अणु
		स्थिर अचिन्हित पूर्णांक *offsets;
		अचिन्हित पूर्णांक num_offsets;
	पूर्ण fpci;
पूर्ण;

काष्ठा tegra_xusb_soc अणु
	स्थिर अक्षर *firmware;
	स्थिर अक्षर * स्थिर *supply_names;
	अचिन्हित पूर्णांक num_supplies;
	स्थिर काष्ठा tegra_xusb_phy_type *phy_types;
	अचिन्हित पूर्णांक num_types;
	स्थिर काष्ठा tegra_xusb_context_soc *context;

	काष्ठा अणु
		काष्ठा अणु
			अचिन्हित पूर्णांक offset;
			अचिन्हित पूर्णांक count;
		पूर्ण usb2, ulpi, hsic, usb3;
	पूर्ण ports;

	काष्ठा tegra_xusb_mbox_regs mbox;

	bool scale_ss_घड़ी;
	bool has_ipfs;
	bool lpm_support;
	bool otg_reset_sspi;
पूर्ण;

काष्ठा tegra_xusb_context अणु
	u32 *ipfs;
	u32 *fpci;
पूर्ण;

काष्ठा tegra_xusb अणु
	काष्ठा device *dev;
	व्योम __iomem *regs;
	काष्ठा usb_hcd *hcd;

	काष्ठा mutex lock;

	पूर्णांक xhci_irq;
	पूर्णांक mbox_irq;

	व्योम __iomem *ipfs_base;
	व्योम __iomem *fpci_base;

	स्थिर काष्ठा tegra_xusb_soc *soc;

	काष्ठा regulator_bulk_data *supplies;

	काष्ठा tegra_xusb_padctl *padctl;

	काष्ठा clk *host_clk;
	काष्ठा clk *falcon_clk;
	काष्ठा clk *ss_clk;
	काष्ठा clk *ss_src_clk;
	काष्ठा clk *hs_src_clk;
	काष्ठा clk *fs_src_clk;
	काष्ठा clk *pll_u_480m;
	काष्ठा clk *clk_m;
	काष्ठा clk *pll_e;

	काष्ठा reset_control *host_rst;
	काष्ठा reset_control *ss_rst;

	काष्ठा device *genpd_dev_host;
	काष्ठा device *genpd_dev_ss;
	काष्ठा device_link *genpd_dl_host;
	काष्ठा device_link *genpd_dl_ss;

	काष्ठा phy **phys;
	अचिन्हित पूर्णांक num_phys;

	काष्ठा usb_phy **usbphy;
	अचिन्हित पूर्णांक num_usb_phys;
	पूर्णांक otg_usb2_port;
	पूर्णांक otg_usb3_port;
	bool host_mode;
	काष्ठा notअगरier_block id_nb;
	काष्ठा work_काष्ठा id_work;

	/* Firmware loading related */
	काष्ठा अणु
		माप_प्रकार size;
		व्योम *virt;
		dma_addr_t phys;
	पूर्ण fw;

	काष्ठा tegra_xusb_context context;
पूर्ण;

अटल काष्ठा hc_driver __पढ़ो_mostly tegra_xhci_hc_driver;

अटल अंतरभूत u32 fpci_पढ़ोl(काष्ठा tegra_xusb *tegra, अचिन्हित पूर्णांक offset)
अणु
	वापस पढ़ोl(tegra->fpci_base + offset);
पूर्ण

अटल अंतरभूत व्योम fpci_ग_लिखोl(काष्ठा tegra_xusb *tegra, u32 value,
			       अचिन्हित पूर्णांक offset)
अणु
	ग_लिखोl(value, tegra->fpci_base + offset);
पूर्ण

अटल अंतरभूत u32 ipfs_पढ़ोl(काष्ठा tegra_xusb *tegra, अचिन्हित पूर्णांक offset)
अणु
	वापस पढ़ोl(tegra->ipfs_base + offset);
पूर्ण

अटल अंतरभूत व्योम ipfs_ग_लिखोl(काष्ठा tegra_xusb *tegra, u32 value,
			       अचिन्हित पूर्णांक offset)
अणु
	ग_लिखोl(value, tegra->ipfs_base + offset);
पूर्ण

अटल u32 csb_पढ़ोl(काष्ठा tegra_xusb *tegra, अचिन्हित पूर्णांक offset)
अणु
	u32 page = CSB_PAGE_SELECT(offset);
	u32 ofs = CSB_PAGE_OFFSET(offset);

	fpci_ग_लिखोl(tegra, page, XUSB_CFG_ARU_C11_CSBRANGE);

	वापस fpci_पढ़ोl(tegra, XUSB_CFG_CSB_BASE_ADDR + ofs);
पूर्ण

अटल व्योम csb_ग_लिखोl(काष्ठा tegra_xusb *tegra, u32 value,
		       अचिन्हित पूर्णांक offset)
अणु
	u32 page = CSB_PAGE_SELECT(offset);
	u32 ofs = CSB_PAGE_OFFSET(offset);

	fpci_ग_लिखोl(tegra, page, XUSB_CFG_ARU_C11_CSBRANGE);
	fpci_ग_लिखोl(tegra, value, XUSB_CFG_CSB_BASE_ADDR + ofs);
पूर्ण

अटल पूर्णांक tegra_xusb_set_ss_clk(काष्ठा tegra_xusb *tegra,
				 अचिन्हित दीर्घ rate)
अणु
	अचिन्हित दीर्घ new_parent_rate, old_parent_rate;
	काष्ठा clk *clk = tegra->ss_src_clk;
	अचिन्हित पूर्णांक भाग;
	पूर्णांक err;

	अगर (clk_get_rate(clk) == rate)
		वापस 0;

	चयन (rate) अणु
	हाल TEGRA_XHCI_SS_HIGH_SPEED:
		/*
		 * Reparent to PLLU_480M. Set भागider first to aव्योम
		 * overघड़ीing.
		 */
		old_parent_rate = clk_get_rate(clk_get_parent(clk));
		new_parent_rate = clk_get_rate(tegra->pll_u_480m);
		भाग = new_parent_rate / rate;

		err = clk_set_rate(clk, old_parent_rate / भाग);
		अगर (err)
			वापस err;

		err = clk_set_parent(clk, tegra->pll_u_480m);
		अगर (err)
			वापस err;

		/*
		 * The rate should alपढ़ोy be correct, but set it again just
		 * to be sure.
		 */
		err = clk_set_rate(clk, rate);
		अगर (err)
			वापस err;

		अवरोध;

	हाल TEGRA_XHCI_SS_LOW_SPEED:
		/* Reparent to CLK_M */
		err = clk_set_parent(clk, tegra->clk_m);
		अगर (err)
			वापस err;

		err = clk_set_rate(clk, rate);
		अगर (err)
			वापस err;

		अवरोध;

	शेष:
		dev_err(tegra->dev, "Invalid SS rate: %lu Hz\n", rate);
		वापस -EINVAL;
	पूर्ण

	अगर (clk_get_rate(clk) != rate) अणु
		dev_err(tegra->dev, "SS clock doesn't match requested rate\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ extract_field(u32 value, अचिन्हित पूर्णांक start,
				   अचिन्हित पूर्णांक count)
अणु
	वापस (value >> start) & ((1 << count) - 1);
पूर्ण

/* Command requests from the firmware */
क्रमागत tegra_xusb_mbox_cmd अणु
	MBOX_CMD_MSG_ENABLED = 1,
	MBOX_CMD_INC_FALC_CLOCK,
	MBOX_CMD_DEC_FALC_CLOCK,
	MBOX_CMD_INC_SSPI_CLOCK,
	MBOX_CMD_DEC_SSPI_CLOCK,
	MBOX_CMD_SET_BW, /* no ACK/NAK required */
	MBOX_CMD_SET_SS_PWR_GATING,
	MBOX_CMD_SET_SS_PWR_UNGATING,
	MBOX_CMD_SAVE_DFE_CTLE_CTX,
	MBOX_CMD_AIRPLANE_MODE_ENABLED, /* unused */
	MBOX_CMD_AIRPLANE_MODE_DISABLED, /* unused */
	MBOX_CMD_START_HSIC_IDLE,
	MBOX_CMD_STOP_HSIC_IDLE,
	MBOX_CMD_DBC_WAKE_STACK, /* unused */
	MBOX_CMD_HSIC_PRETEND_CONNECT,
	MBOX_CMD_RESET_SSPI,
	MBOX_CMD_DISABLE_SS_LFPS_DETECTION,
	MBOX_CMD_ENABLE_SS_LFPS_DETECTION,

	MBOX_CMD_MAX,

	/* Response message to above commands */
	MBOX_CMD_ACK = 128,
	MBOX_CMD_NAK
पूर्ण;

काष्ठा tegra_xusb_mbox_msg अणु
	u32 cmd;
	u32 data;
पूर्ण;

अटल अंतरभूत u32 tegra_xusb_mbox_pack(स्थिर काष्ठा tegra_xusb_mbox_msg *msg)
अणु
	वापस (msg->cmd & CMD_TYPE_MASK) << CMD_TYPE_SHIFT |
	       (msg->data & CMD_DATA_MASK) << CMD_DATA_SHIFT;
पूर्ण
अटल अंतरभूत व्योम tegra_xusb_mbox_unpack(काष्ठा tegra_xusb_mbox_msg *msg,
					  u32 value)
अणु
	msg->cmd = (value >> CMD_TYPE_SHIFT) & CMD_TYPE_MASK;
	msg->data = (value >> CMD_DATA_SHIFT) & CMD_DATA_MASK;
पूर्ण

अटल bool tegra_xusb_mbox_cmd_requires_ack(क्रमागत tegra_xusb_mbox_cmd cmd)
अणु
	चयन (cmd) अणु
	हाल MBOX_CMD_SET_BW:
	हाल MBOX_CMD_ACK:
	हाल MBOX_CMD_NAK:
		वापस false;

	शेष:
		वापस true;
	पूर्ण
पूर्ण

अटल पूर्णांक tegra_xusb_mbox_send(काष्ठा tegra_xusb *tegra,
				स्थिर काष्ठा tegra_xusb_mbox_msg *msg)
अणु
	bool रुको_क्रम_idle = false;
	u32 value;

	/*
	 * Acquire the mailbox. The firmware still owns the mailbox क्रम
	 * ACK/NAK messages.
	 */
	अगर (!(msg->cmd == MBOX_CMD_ACK || msg->cmd == MBOX_CMD_NAK)) अणु
		value = fpci_पढ़ोl(tegra, tegra->soc->mbox.owner);
		अगर (value != MBOX_OWNER_NONE) अणु
			dev_err(tegra->dev, "mailbox is busy\n");
			वापस -EBUSY;
		पूर्ण

		fpci_ग_लिखोl(tegra, MBOX_OWNER_SW, tegra->soc->mbox.owner);

		value = fpci_पढ़ोl(tegra, tegra->soc->mbox.owner);
		अगर (value != MBOX_OWNER_SW) अणु
			dev_err(tegra->dev, "failed to acquire mailbox\n");
			वापस -EBUSY;
		पूर्ण

		रुको_क्रम_idle = true;
	पूर्ण

	value = tegra_xusb_mbox_pack(msg);
	fpci_ग_लिखोl(tegra, value, tegra->soc->mbox.data_in);

	value = fpci_पढ़ोl(tegra, tegra->soc->mbox.cmd);
	value |= MBOX_INT_EN | MBOX_DEST_FALC;
	fpci_ग_लिखोl(tegra, value, tegra->soc->mbox.cmd);

	अगर (रुको_क्रम_idle) अणु
		अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(250);

		जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
			value = fpci_पढ़ोl(tegra, tegra->soc->mbox.owner);
			अगर (value == MBOX_OWNER_NONE)
				अवरोध;

			usleep_range(10, 20);
		पूर्ण

		अगर (समय_after(jअगरfies, समयout))
			value = fpci_पढ़ोl(tegra, tegra->soc->mbox.owner);

		अगर (value != MBOX_OWNER_NONE)
			वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल irqवापस_t tegra_xusb_mbox_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा tegra_xusb *tegra = data;
	u32 value;

	/* clear mailbox पूर्णांकerrupts */
	value = fpci_पढ़ोl(tegra, XUSB_CFG_ARU_SMI_INTR);
	fpci_ग_लिखोl(tegra, value, XUSB_CFG_ARU_SMI_INTR);

	अगर (value & MBOX_SMI_INTR_FW_HANG)
		dev_err(tegra->dev, "controller firmware hang\n");

	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल व्योम tegra_xusb_mbox_handle(काष्ठा tegra_xusb *tegra,
				   स्थिर काष्ठा tegra_xusb_mbox_msg *msg)
अणु
	काष्ठा tegra_xusb_padctl *padctl = tegra->padctl;
	स्थिर काष्ठा tegra_xusb_soc *soc = tegra->soc;
	काष्ठा device *dev = tegra->dev;
	काष्ठा tegra_xusb_mbox_msg rsp;
	अचिन्हित दीर्घ mask;
	अचिन्हित पूर्णांक port;
	bool idle, enable;
	पूर्णांक err = 0;

	स_रखो(&rsp, 0, माप(rsp));

	चयन (msg->cmd) अणु
	हाल MBOX_CMD_INC_FALC_CLOCK:
	हाल MBOX_CMD_DEC_FALC_CLOCK:
		rsp.data = clk_get_rate(tegra->falcon_clk) / 1000;
		अगर (rsp.data != msg->data)
			rsp.cmd = MBOX_CMD_NAK;
		अन्यथा
			rsp.cmd = MBOX_CMD_ACK;

		अवरोध;

	हाल MBOX_CMD_INC_SSPI_CLOCK:
	हाल MBOX_CMD_DEC_SSPI_CLOCK:
		अगर (tegra->soc->scale_ss_घड़ी) अणु
			err = tegra_xusb_set_ss_clk(tegra, msg->data * 1000);
			अगर (err < 0)
				rsp.cmd = MBOX_CMD_NAK;
			अन्यथा
				rsp.cmd = MBOX_CMD_ACK;

			rsp.data = clk_get_rate(tegra->ss_src_clk) / 1000;
		पूर्ण अन्यथा अणु
			rsp.cmd = MBOX_CMD_ACK;
			rsp.data = msg->data;
		पूर्ण

		अवरोध;

	हाल MBOX_CMD_SET_BW:
		/*
		 * TODO: Request bandwidth once EMC scaling is supported.
		 * Ignore क्रम now since ACK/NAK is not required क्रम SET_BW
		 * messages.
		 */
		अवरोध;

	हाल MBOX_CMD_SAVE_DFE_CTLE_CTX:
		err = tegra_xusb_padctl_usb3_save_context(padctl, msg->data);
		अगर (err < 0) अणु
			dev_err(dev, "failed to save context for USB3#%u: %d\n",
				msg->data, err);
			rsp.cmd = MBOX_CMD_NAK;
		पूर्ण अन्यथा अणु
			rsp.cmd = MBOX_CMD_ACK;
		पूर्ण

		rsp.data = msg->data;
		अवरोध;

	हाल MBOX_CMD_START_HSIC_IDLE:
	हाल MBOX_CMD_STOP_HSIC_IDLE:
		अगर (msg->cmd == MBOX_CMD_STOP_HSIC_IDLE)
			idle = false;
		अन्यथा
			idle = true;

		mask = extract_field(msg->data, 1 + soc->ports.hsic.offset,
				     soc->ports.hsic.count);

		क्रम_each_set_bit(port, &mask, 32) अणु
			err = tegra_xusb_padctl_hsic_set_idle(padctl, port,
							      idle);
			अगर (err < 0)
				अवरोध;
		पूर्ण

		अगर (err < 0) अणु
			dev_err(dev, "failed to set HSIC#%u %s: %d\n", port,
				idle ? "idle" : "busy", err);
			rsp.cmd = MBOX_CMD_NAK;
		पूर्ण अन्यथा अणु
			rsp.cmd = MBOX_CMD_ACK;
		पूर्ण

		rsp.data = msg->data;
		अवरोध;

	हाल MBOX_CMD_DISABLE_SS_LFPS_DETECTION:
	हाल MBOX_CMD_ENABLE_SS_LFPS_DETECTION:
		अगर (msg->cmd == MBOX_CMD_DISABLE_SS_LFPS_DETECTION)
			enable = false;
		अन्यथा
			enable = true;

		mask = extract_field(msg->data, 1 + soc->ports.usb3.offset,
				     soc->ports.usb3.count);

		क्रम_each_set_bit(port, &mask, soc->ports.usb3.count) अणु
			err = tegra_xusb_padctl_usb3_set_lfps_detect(padctl,
								     port,
								     enable);
			अगर (err < 0)
				अवरोध;

			/*
			 * रुको 500us क्रम LFPS detector to be disabled beक्रमe
			 * sending ACK
			 */
			अगर (!enable)
				usleep_range(500, 1000);
		पूर्ण

		अगर (err < 0) अणु
			dev_err(dev,
				"failed to %s LFPS detection on USB3#%u: %d\n",
				enable ? "enable" : "disable", port, err);
			rsp.cmd = MBOX_CMD_NAK;
		पूर्ण अन्यथा अणु
			rsp.cmd = MBOX_CMD_ACK;
		पूर्ण

		rsp.data = msg->data;
		अवरोध;

	शेष:
		dev_warn(dev, "unknown message: %#x\n", msg->cmd);
		अवरोध;
	पूर्ण

	अगर (rsp.cmd) अणु
		स्थिर अक्षर *cmd = (rsp.cmd == MBOX_CMD_ACK) ? "ACK" : "NAK";

		err = tegra_xusb_mbox_send(tegra, &rsp);
		अगर (err < 0)
			dev_err(dev, "failed to send %s: %d\n", cmd, err);
	पूर्ण
पूर्ण

अटल irqवापस_t tegra_xusb_mbox_thपढ़ो(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा tegra_xusb *tegra = data;
	काष्ठा tegra_xusb_mbox_msg msg;
	u32 value;

	mutex_lock(&tegra->lock);

	value = fpci_पढ़ोl(tegra, tegra->soc->mbox.data_out);
	tegra_xusb_mbox_unpack(&msg, value);

	value = fpci_पढ़ोl(tegra, tegra->soc->mbox.cmd);
	value &= ~MBOX_DEST_SMI;
	fpci_ग_लिखोl(tegra, value, tegra->soc->mbox.cmd);

	/* clear mailbox owner अगर no ACK/NAK is required */
	अगर (!tegra_xusb_mbox_cmd_requires_ack(msg.cmd))
		fpci_ग_लिखोl(tegra, MBOX_OWNER_NONE, tegra->soc->mbox.owner);

	tegra_xusb_mbox_handle(tegra, &msg);

	mutex_unlock(&tegra->lock);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम tegra_xusb_config(काष्ठा tegra_xusb *tegra)
अणु
	u32 regs = tegra->hcd->rsrc_start;
	u32 value;

	अगर (tegra->soc->has_ipfs) अणु
		value = ipfs_पढ़ोl(tegra, IPFS_XUSB_HOST_CONFIGURATION_0);
		value |= IPFS_EN_FPCI;
		ipfs_ग_लिखोl(tegra, value, IPFS_XUSB_HOST_CONFIGURATION_0);

		usleep_range(10, 20);
	पूर्ण

	/* Program BAR0 space */
	value = fpci_पढ़ोl(tegra, XUSB_CFG_4);
	value &= ~(XUSB_BASE_ADDR_MASK << XUSB_BASE_ADDR_SHIFT);
	value |= regs & (XUSB_BASE_ADDR_MASK << XUSB_BASE_ADDR_SHIFT);
	fpci_ग_लिखोl(tegra, value, XUSB_CFG_4);

	usleep_range(100, 200);

	/* Enable bus master */
	value = fpci_पढ़ोl(tegra, XUSB_CFG_1);
	value |= XUSB_IO_SPACE_EN | XUSB_MEM_SPACE_EN | XUSB_BUS_MASTER_EN;
	fpci_ग_लिखोl(tegra, value, XUSB_CFG_1);

	अगर (tegra->soc->has_ipfs) अणु
		/* Enable पूर्णांकerrupt निश्चितion */
		value = ipfs_पढ़ोl(tegra, IPFS_XUSB_HOST_INTR_MASK_0);
		value |= IPFS_IP_INT_MASK;
		ipfs_ग_लिखोl(tegra, value, IPFS_XUSB_HOST_INTR_MASK_0);

		/* Set hysteresis */
		ipfs_ग_लिखोl(tegra, 0x80, IPFS_XUSB_HOST_CLKGATE_HYSTERESIS_0);
	पूर्ण
पूर्ण

अटल पूर्णांक tegra_xusb_clk_enable(काष्ठा tegra_xusb *tegra)
अणु
	पूर्णांक err;

	err = clk_prepare_enable(tegra->pll_e);
	अगर (err < 0)
		वापस err;

	err = clk_prepare_enable(tegra->host_clk);
	अगर (err < 0)
		जाओ disable_plle;

	err = clk_prepare_enable(tegra->ss_clk);
	अगर (err < 0)
		जाओ disable_host;

	err = clk_prepare_enable(tegra->falcon_clk);
	अगर (err < 0)
		जाओ disable_ss;

	err = clk_prepare_enable(tegra->fs_src_clk);
	अगर (err < 0)
		जाओ disable_falc;

	err = clk_prepare_enable(tegra->hs_src_clk);
	अगर (err < 0)
		जाओ disable_fs_src;

	अगर (tegra->soc->scale_ss_घड़ी) अणु
		err = tegra_xusb_set_ss_clk(tegra, TEGRA_XHCI_SS_HIGH_SPEED);
		अगर (err < 0)
			जाओ disable_hs_src;
	पूर्ण

	वापस 0;

disable_hs_src:
	clk_disable_unprepare(tegra->hs_src_clk);
disable_fs_src:
	clk_disable_unprepare(tegra->fs_src_clk);
disable_falc:
	clk_disable_unprepare(tegra->falcon_clk);
disable_ss:
	clk_disable_unprepare(tegra->ss_clk);
disable_host:
	clk_disable_unprepare(tegra->host_clk);
disable_plle:
	clk_disable_unprepare(tegra->pll_e);
	वापस err;
पूर्ण

अटल व्योम tegra_xusb_clk_disable(काष्ठा tegra_xusb *tegra)
अणु
	clk_disable_unprepare(tegra->pll_e);
	clk_disable_unprepare(tegra->host_clk);
	clk_disable_unprepare(tegra->ss_clk);
	clk_disable_unprepare(tegra->falcon_clk);
	clk_disable_unprepare(tegra->fs_src_clk);
	clk_disable_unprepare(tegra->hs_src_clk);
पूर्ण

अटल पूर्णांक tegra_xusb_phy_enable(काष्ठा tegra_xusb *tegra)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	क्रम (i = 0; i < tegra->num_phys; i++) अणु
		err = phy_init(tegra->phys[i]);
		अगर (err)
			जाओ disable_phy;

		err = phy_घातer_on(tegra->phys[i]);
		अगर (err) अणु
			phy_निकास(tegra->phys[i]);
			जाओ disable_phy;
		पूर्ण
	पूर्ण

	वापस 0;

disable_phy:
	जबतक (i--) अणु
		phy_घातer_off(tegra->phys[i]);
		phy_निकास(tegra->phys[i]);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम tegra_xusb_phy_disable(काष्ठा tegra_xusb *tegra)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < tegra->num_phys; i++) अणु
		phy_घातer_off(tegra->phys[i]);
		phy_निकास(tegra->phys[i]);
	पूर्ण
पूर्ण

अटल पूर्णांक tegra_xusb_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा tegra_xusb *tegra = dev_get_drvdata(dev);

	regulator_bulk_disable(tegra->soc->num_supplies, tegra->supplies);
	tegra_xusb_clk_disable(tegra);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_xusb_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा tegra_xusb *tegra = dev_get_drvdata(dev);
	पूर्णांक err;

	err = tegra_xusb_clk_enable(tegra);
	अगर (err) अणु
		dev_err(dev, "failed to enable clocks: %d\n", err);
		वापस err;
	पूर्ण

	err = regulator_bulk_enable(tegra->soc->num_supplies, tegra->supplies);
	अगर (err) अणु
		dev_err(dev, "failed to enable regulators: %d\n", err);
		जाओ disable_clk;
	पूर्ण

	वापस 0;

disable_clk:
	tegra_xusb_clk_disable(tegra);
	वापस err;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक tegra_xusb_init_context(काष्ठा tegra_xusb *tegra)
अणु
	स्थिर काष्ठा tegra_xusb_context_soc *soc = tegra->soc->context;

	tegra->context.ipfs = devm_kसुस्मृति(tegra->dev, soc->ipfs.num_offsets,
					   माप(u32), GFP_KERNEL);
	अगर (!tegra->context.ipfs)
		वापस -ENOMEM;

	tegra->context.fpci = devm_kसुस्मृति(tegra->dev, soc->fpci.num_offsets,
					   माप(u32), GFP_KERNEL);
	अगर (!tegra->context.fpci)
		वापस -ENOMEM;

	वापस 0;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक tegra_xusb_init_context(काष्ठा tegra_xusb *tegra)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक tegra_xusb_request_firmware(काष्ठा tegra_xusb *tegra)
अणु
	काष्ठा tegra_xusb_fw_header *header;
	स्थिर काष्ठा firmware *fw;
	पूर्णांक err;

	err = request_firmware(&fw, tegra->soc->firmware, tegra->dev);
	अगर (err < 0) अणु
		dev_err(tegra->dev, "failed to request firmware: %d\n", err);
		वापस err;
	पूर्ण

	/* Load Falcon controller with its firmware. */
	header = (काष्ठा tegra_xusb_fw_header *)fw->data;
	tegra->fw.size = le32_to_cpu(header->fwimg_len);

	tegra->fw.virt = dma_alloc_coherent(tegra->dev, tegra->fw.size,
					    &tegra->fw.phys, GFP_KERNEL);
	अगर (!tegra->fw.virt) अणु
		dev_err(tegra->dev, "failed to allocate memory for firmware\n");
		release_firmware(fw);
		वापस -ENOMEM;
	पूर्ण

	header = (काष्ठा tegra_xusb_fw_header *)tegra->fw.virt;
	स_नकल(tegra->fw.virt, fw->data, tegra->fw.size);
	release_firmware(fw);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_xusb_load_firmware(काष्ठा tegra_xusb *tegra)
अणु
	अचिन्हित पूर्णांक code_tag_blocks, code_size_blocks, code_blocks;
	काष्ठा xhci_cap_regs __iomem *cap = tegra->regs;
	काष्ठा tegra_xusb_fw_header *header;
	काष्ठा device *dev = tegra->dev;
	काष्ठा xhci_op_regs __iomem *op;
	अचिन्हित दीर्घ समयout;
	समय64_t बारtamp;
	काष्ठा पंचांग समय;
	u64 address;
	u32 value;
	पूर्णांक err;

	header = (काष्ठा tegra_xusb_fw_header *)tegra->fw.virt;
	op = tegra->regs + HC_LENGTH(पढ़ोl(&cap->hc_capbase));

	अगर (csb_पढ़ोl(tegra, XUSB_CSB_MP_ILOAD_BASE_LO) != 0) अणु
		dev_info(dev, "Firmware already loaded, Falcon state %#x\n",
			 csb_पढ़ोl(tegra, XUSB_FALC_CPUCTL));
		वापस 0;
	पूर्ण

	/* Program the size of DFI पूर्णांकo ILOAD_ATTR. */
	csb_ग_लिखोl(tegra, tegra->fw.size, XUSB_CSB_MP_ILOAD_ATTR);

	/*
	 * Boot code of the firmware पढ़ोs the ILOAD_BASE रेजिस्टरs
	 * to get to the start of the DFI in प्रणाली memory.
	 */
	address = tegra->fw.phys + माप(*header);
	csb_ग_लिखोl(tegra, address >> 32, XUSB_CSB_MP_ILOAD_BASE_HI);
	csb_ग_लिखोl(tegra, address, XUSB_CSB_MP_ILOAD_BASE_LO);

	/* Set BOOTPATH to 1 in APMAP. */
	csb_ग_लिखोl(tegra, APMAP_BOOTPATH, XUSB_CSB_MP_APMAP);

	/* Invalidate L2IMEM. */
	csb_ग_लिखोl(tegra, L2IMEMOP_INVALIDATE_ALL, XUSB_CSB_MP_L2IMEMOP_TRIG);

	/*
	 * Initiate fetch of bootcode from प्रणाली memory पूर्णांकo L2IMEM.
	 * Program bootcode location and size in प्रणाली memory.
	 */
	code_tag_blocks = DIV_ROUND_UP(le32_to_cpu(header->boot_codetag),
				       IMEM_BLOCK_SIZE);
	code_size_blocks = DIV_ROUND_UP(le32_to_cpu(header->boot_codesize),
					IMEM_BLOCK_SIZE);
	code_blocks = code_tag_blocks + code_size_blocks;

	value = ((code_tag_blocks & L2IMEMOP_SIZE_SRC_OFFSET_MASK) <<
			L2IMEMOP_SIZE_SRC_OFFSET_SHIFT) |
		((code_size_blocks & L2IMEMOP_SIZE_SRC_COUNT_MASK) <<
			L2IMEMOP_SIZE_SRC_COUNT_SHIFT);
	csb_ग_लिखोl(tegra, value, XUSB_CSB_MP_L2IMEMOP_SIZE);

	/* Trigger L2IMEM load operation. */
	csb_ग_लिखोl(tegra, L2IMEMOP_LOAD_LOCKED_RESULT,
		   XUSB_CSB_MP_L2IMEMOP_TRIG);

	/* Setup Falcon स्वतः-fill. */
	csb_ग_लिखोl(tegra, code_size_blocks, XUSB_FALC_IMFILLCTL);

	value = ((code_tag_blocks & IMFILLRNG1_TAG_MASK) <<
			IMFILLRNG1_TAG_LO_SHIFT) |
		((code_blocks & IMFILLRNG1_TAG_MASK) <<
			IMFILLRNG1_TAG_HI_SHIFT);
	csb_ग_लिखोl(tegra, value, XUSB_FALC_IMFILLRNG1);

	csb_ग_लिखोl(tegra, 0, XUSB_FALC_DMACTL);

	/* रुको क्रम RESULT_VLD to get set */
#घोषणा tegra_csb_पढ़ोl(offset) csb_पढ़ोl(tegra, offset)
	err = पढ़ोx_poll_समयout(tegra_csb_पढ़ोl,
				 XUSB_CSB_MEMPOOL_L2IMEMOP_RESULT, value,
				 value & L2IMEMOP_RESULT_VLD, 100, 10000);
	अगर (err < 0) अणु
		dev_err(dev, "DMA controller not ready %#010x\n", value);
		वापस err;
	पूर्ण
#अघोषित tegra_csb_पढ़ोl

	csb_ग_लिखोl(tegra, le32_to_cpu(header->boot_codetag),
		   XUSB_FALC_BOOTVEC);

	/* Boot Falcon CPU and रुको क्रम USBSTS_CNR to get cleared. */
	csb_ग_लिखोl(tegra, CPUCTL_STARTCPU, XUSB_FALC_CPUCTL);

	समयout = jअगरfies + msecs_to_jअगरfies(200);

	करो अणु
		value = पढ़ोl(&op->status);
		अगर ((value & STS_CNR) == 0)
			अवरोध;

		usleep_range(1000, 2000);
	पूर्ण जबतक (समय_is_after_jअगरfies(समयout));

	value = पढ़ोl(&op->status);
	अगर (value & STS_CNR) अणु
		value = csb_पढ़ोl(tegra, XUSB_FALC_CPUCTL);
		dev_err(dev, "XHCI controller not read: %#010x\n", value);
		वापस -EIO;
	पूर्ण

	बारtamp = le32_to_cpu(header->fwimg_created_समय);
	समय64_to_पंचांग(बारtamp, 0, &समय);

	dev_info(dev, "Firmware timestamp: %ld-%02d-%02d %02d:%02d:%02d UTC\n",
		 समय.पंचांग_year + 1900, समय.पंचांग_mon + 1, समय.पंचांग_mday,
		 समय.पंचांग_hour, समय.पंचांग_min, समय.पंचांग_sec);

	वापस 0;
पूर्ण

अटल व्योम tegra_xusb_घातerकरोमुख्य_हटाओ(काष्ठा device *dev,
					  काष्ठा tegra_xusb *tegra)
अणु
	अगर (tegra->genpd_dl_ss)
		device_link_del(tegra->genpd_dl_ss);
	अगर (tegra->genpd_dl_host)
		device_link_del(tegra->genpd_dl_host);
	अगर (!IS_ERR_OR_शून्य(tegra->genpd_dev_ss))
		dev_pm_करोमुख्य_detach(tegra->genpd_dev_ss, true);
	अगर (!IS_ERR_OR_शून्य(tegra->genpd_dev_host))
		dev_pm_करोमुख्य_detach(tegra->genpd_dev_host, true);
पूर्ण

अटल पूर्णांक tegra_xusb_घातerकरोमुख्य_init(काष्ठा device *dev,
				       काष्ठा tegra_xusb *tegra)
अणु
	पूर्णांक err;

	tegra->genpd_dev_host = dev_pm_करोमुख्य_attach_by_name(dev, "xusb_host");
	अगर (IS_ERR(tegra->genpd_dev_host)) अणु
		err = PTR_ERR(tegra->genpd_dev_host);
		dev_err(dev, "failed to get host pm-domain: %d\n", err);
		वापस err;
	पूर्ण

	tegra->genpd_dev_ss = dev_pm_करोमुख्य_attach_by_name(dev, "xusb_ss");
	अगर (IS_ERR(tegra->genpd_dev_ss)) अणु
		err = PTR_ERR(tegra->genpd_dev_ss);
		dev_err(dev, "failed to get superspeed pm-domain: %d\n", err);
		वापस err;
	पूर्ण

	tegra->genpd_dl_host = device_link_add(dev, tegra->genpd_dev_host,
					       DL_FLAG_PM_RUNTIME |
					       DL_FLAG_STATELESS);
	अगर (!tegra->genpd_dl_host) अणु
		dev_err(dev, "adding host device link failed!\n");
		वापस -ENODEV;
	पूर्ण

	tegra->genpd_dl_ss = device_link_add(dev, tegra->genpd_dev_ss,
					     DL_FLAG_PM_RUNTIME |
					     DL_FLAG_STATELESS);
	अगर (!tegra->genpd_dl_ss) अणु
		dev_err(dev, "adding superspeed device link failed!\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __tegra_xusb_enable_firmware_messages(काष्ठा tegra_xusb *tegra)
अणु
	काष्ठा tegra_xusb_mbox_msg msg;
	पूर्णांक err;

	/* Enable firmware messages from controller. */
	msg.cmd = MBOX_CMD_MSG_ENABLED;
	msg.data = 0;

	err = tegra_xusb_mbox_send(tegra, &msg);
	अगर (err < 0)
		dev_err(tegra->dev, "failed to enable messages: %d\n", err);

	वापस err;
पूर्ण

अटल पूर्णांक tegra_xusb_enable_firmware_messages(काष्ठा tegra_xusb *tegra)
अणु
	पूर्णांक err;

	mutex_lock(&tegra->lock);
	err = __tegra_xusb_enable_firmware_messages(tegra);
	mutex_unlock(&tegra->lock);

	वापस err;
पूर्ण

अटल व्योम tegra_xhci_set_port_घातer(काष्ठा tegra_xusb *tegra, bool मुख्य,
						 bool set)
अणु
	काष्ठा xhci_hcd *xhci = hcd_to_xhci(tegra->hcd);
	काष्ठा usb_hcd *hcd = मुख्य ?  xhci->मुख्य_hcd : xhci->shared_hcd;
	अचिन्हित पूर्णांक रुको = (!मुख्य && !set) ? 1000 : 10;
	u16 typeReq = set ? SetPortFeature : ClearPortFeature;
	u16 wIndex = मुख्य ? tegra->otg_usb2_port + 1 : tegra->otg_usb3_port + 1;
	u32 status;
	u32 stat_घातer = मुख्य ? USB_PORT_STAT_POWER : USB_SS_PORT_STAT_POWER;
	u32 status_val = set ? stat_घातer : 0;

	dev_dbg(tegra->dev, "%s():%s %s port power\n", __func__,
		set ? "set" : "clear", मुख्य ? "HS" : "SS");

	hcd->driver->hub_control(hcd, typeReq, USB_PORT_FEAT_POWER, wIndex,
				 शून्य, 0);

	करो अणु
		tegra_xhci_hc_driver.hub_control(hcd, GetPortStatus, 0, wIndex,
					(अक्षर *) &status, माप(status));
		अगर (status_val == (status & stat_घातer))
			अवरोध;

		अगर (!मुख्य && !set)
			usleep_range(600, 700);
		अन्यथा
			usleep_range(10, 20);
	पूर्ण जबतक (--रुको > 0);

	अगर (status_val != (status & stat_घातer))
		dev_info(tegra->dev, "failed to %s %s PP %d\n",
						set ? "set" : "clear",
						मुख्य ? "HS" : "SS", status);
पूर्ण

अटल काष्ठा phy *tegra_xusb_get_phy(काष्ठा tegra_xusb *tegra, अक्षर *name,
								पूर्णांक port)
अणु
	अचिन्हित पूर्णांक i, phy_count = 0;

	क्रम (i = 0; i < tegra->soc->num_types; i++) अणु
		अगर (!म_भेदन(tegra->soc->phy_types[i].name, name,
							    म_माप(name)))
			वापस tegra->phys[phy_count+port];

		phy_count += tegra->soc->phy_types[i].num;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम tegra_xhci_id_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tegra_xusb *tegra = container_of(work, काष्ठा tegra_xusb,
						id_work);
	काष्ठा xhci_hcd *xhci = hcd_to_xhci(tegra->hcd);
	काष्ठा tegra_xusb_mbox_msg msg;
	काष्ठा phy *phy = tegra_xusb_get_phy(tegra, "usb2",
						    tegra->otg_usb2_port);
	u32 status;
	पूर्णांक ret;

	dev_dbg(tegra->dev, "host mode %s\n", tegra->host_mode ? "on" : "off");

	mutex_lock(&tegra->lock);

	अगर (tegra->host_mode)
		phy_set_mode_ext(phy, PHY_MODE_USB_OTG, USB_ROLE_HOST);
	अन्यथा
		phy_set_mode_ext(phy, PHY_MODE_USB_OTG, USB_ROLE_NONE);

	mutex_unlock(&tegra->lock);

	अगर (tegra->host_mode) अणु
		/* चयन to host mode */
		अगर (tegra->otg_usb3_port >= 0) अणु
			अगर (tegra->soc->otg_reset_sspi) अणु
				/* set PP=0 */
				tegra_xhci_hc_driver.hub_control(
					xhci->shared_hcd, GetPortStatus,
					0, tegra->otg_usb3_port+1,
					(अक्षर *) &status, माप(status));
				अगर (status & USB_SS_PORT_STAT_POWER)
					tegra_xhci_set_port_घातer(tegra, false,
								  false);

				/* reset OTG port SSPI */
				msg.cmd = MBOX_CMD_RESET_SSPI;
				msg.data = tegra->otg_usb3_port+1;

				ret = tegra_xusb_mbox_send(tegra, &msg);
				अगर (ret < 0) अणु
					dev_info(tegra->dev,
						"failed to RESET_SSPI %d\n",
						ret);
				पूर्ण
			पूर्ण

			tegra_xhci_set_port_घातer(tegra, false, true);
		पूर्ण

		tegra_xhci_set_port_घातer(tegra, true, true);

	पूर्ण अन्यथा अणु
		अगर (tegra->otg_usb3_port >= 0)
			tegra_xhci_set_port_घातer(tegra, false, false);

		tegra_xhci_set_port_घातer(tegra, true, false);
	पूर्ण
पूर्ण

अटल पूर्णांक tegra_xusb_get_usb2_port(काष्ठा tegra_xusb *tegra,
					      काष्ठा usb_phy *usbphy)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < tegra->num_usb_phys; i++) अणु
		अगर (tegra->usbphy[i] && usbphy == tegra->usbphy[i])
			वापस i;
	पूर्ण

	वापस -1;
पूर्ण

अटल पूर्णांक tegra_xhci_id_notअगरy(काष्ठा notअगरier_block *nb,
					 अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा tegra_xusb *tegra = container_of(nb, काष्ठा tegra_xusb,
						    id_nb);
	काष्ठा usb_phy *usbphy = (काष्ठा usb_phy *)data;

	dev_dbg(tegra->dev, "%s(): action is %d", __func__, usbphy->last_event);

	अगर ((tegra->host_mode && usbphy->last_event == USB_EVENT_ID) ||
		(!tegra->host_mode && usbphy->last_event != USB_EVENT_ID)) अणु
		dev_dbg(tegra->dev, "Same role(%d) received. Ignore",
			tegra->host_mode);
		वापस NOTIFY_OK;
	पूर्ण

	tegra->otg_usb2_port = tegra_xusb_get_usb2_port(tegra, usbphy);
	tegra->otg_usb3_port = tegra_xusb_padctl_get_usb3_companion(
							tegra->padctl,
							tegra->otg_usb2_port);

	tegra->host_mode = (usbphy->last_event == USB_EVENT_ID) ? true : false;

	schedule_work(&tegra->id_work);

	वापस NOTIFY_OK;
पूर्ण

अटल पूर्णांक tegra_xusb_init_usb_phy(काष्ठा tegra_xusb *tegra)
अणु
	अचिन्हित पूर्णांक i;

	tegra->usbphy = devm_kसुस्मृति(tegra->dev, tegra->num_usb_phys,
				   माप(*tegra->usbphy), GFP_KERNEL);
	अगर (!tegra->usbphy)
		वापस -ENOMEM;

	INIT_WORK(&tegra->id_work, tegra_xhci_id_work);
	tegra->id_nb.notअगरier_call = tegra_xhci_id_notअगरy;
	tegra->otg_usb2_port = -EINVAL;
	tegra->otg_usb3_port = -EINVAL;

	क्रम (i = 0; i < tegra->num_usb_phys; i++) अणु
		काष्ठा phy *phy = tegra_xusb_get_phy(tegra, "usb2", i);

		अगर (!phy)
			जारी;

		tegra->usbphy[i] = devm_usb_get_phy_by_node(tegra->dev,
							phy->dev.of_node,
							&tegra->id_nb);
		अगर (!IS_ERR(tegra->usbphy[i])) अणु
			dev_dbg(tegra->dev, "usbphy-%d registered", i);
			otg_set_host(tegra->usbphy[i]->otg, &tegra->hcd->self);
		पूर्ण अन्यथा अणु
			/*
			 * usb-phy is optional, जारी अगर its not available.
			 */
			tegra->usbphy[i] = शून्य;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम tegra_xusb_deinit_usb_phy(काष्ठा tegra_xusb *tegra)
अणु
	अचिन्हित पूर्णांक i;

	cancel_work_sync(&tegra->id_work);

	क्रम (i = 0; i < tegra->num_usb_phys; i++)
		अगर (tegra->usbphy[i])
			otg_set_host(tegra->usbphy[i]->otg, शून्य);
पूर्ण

अटल पूर्णांक tegra_xusb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra_xusb *tegra;
	काष्ठा resource *regs;
	काष्ठा xhci_hcd *xhci;
	अचिन्हित पूर्णांक i, j, k;
	काष्ठा phy *phy;
	पूर्णांक err;

	BUILD_BUG_ON(माप(काष्ठा tegra_xusb_fw_header) != 256);

	tegra = devm_kzalloc(&pdev->dev, माप(*tegra), GFP_KERNEL);
	अगर (!tegra)
		वापस -ENOMEM;

	tegra->soc = of_device_get_match_data(&pdev->dev);
	mutex_init(&tegra->lock);
	tegra->dev = &pdev->dev;

	err = tegra_xusb_init_context(tegra);
	अगर (err < 0)
		वापस err;

	regs = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	tegra->regs = devm_ioremap_resource(&pdev->dev, regs);
	अगर (IS_ERR(tegra->regs))
		वापस PTR_ERR(tegra->regs);

	tegra->fpci_base = devm_platक्रमm_ioremap_resource(pdev, 1);
	अगर (IS_ERR(tegra->fpci_base))
		वापस PTR_ERR(tegra->fpci_base);

	अगर (tegra->soc->has_ipfs) अणु
		tegra->ipfs_base = devm_platक्रमm_ioremap_resource(pdev, 2);
		अगर (IS_ERR(tegra->ipfs_base))
			वापस PTR_ERR(tegra->ipfs_base);
	पूर्ण

	tegra->xhci_irq = platक्रमm_get_irq(pdev, 0);
	अगर (tegra->xhci_irq < 0)
		वापस tegra->xhci_irq;

	tegra->mbox_irq = platक्रमm_get_irq(pdev, 1);
	अगर (tegra->mbox_irq < 0)
		वापस tegra->mbox_irq;

	tegra->padctl = tegra_xusb_padctl_get(&pdev->dev);
	अगर (IS_ERR(tegra->padctl))
		वापस PTR_ERR(tegra->padctl);

	tegra->host_clk = devm_clk_get(&pdev->dev, "xusb_host");
	अगर (IS_ERR(tegra->host_clk)) अणु
		err = PTR_ERR(tegra->host_clk);
		dev_err(&pdev->dev, "failed to get xusb_host: %d\n", err);
		जाओ put_padctl;
	पूर्ण

	tegra->falcon_clk = devm_clk_get(&pdev->dev, "xusb_falcon_src");
	अगर (IS_ERR(tegra->falcon_clk)) अणु
		err = PTR_ERR(tegra->falcon_clk);
		dev_err(&pdev->dev, "failed to get xusb_falcon_src: %d\n", err);
		जाओ put_padctl;
	पूर्ण

	tegra->ss_clk = devm_clk_get(&pdev->dev, "xusb_ss");
	अगर (IS_ERR(tegra->ss_clk)) अणु
		err = PTR_ERR(tegra->ss_clk);
		dev_err(&pdev->dev, "failed to get xusb_ss: %d\n", err);
		जाओ put_padctl;
	पूर्ण

	tegra->ss_src_clk = devm_clk_get(&pdev->dev, "xusb_ss_src");
	अगर (IS_ERR(tegra->ss_src_clk)) अणु
		err = PTR_ERR(tegra->ss_src_clk);
		dev_err(&pdev->dev, "failed to get xusb_ss_src: %d\n", err);
		जाओ put_padctl;
	पूर्ण

	tegra->hs_src_clk = devm_clk_get(&pdev->dev, "xusb_hs_src");
	अगर (IS_ERR(tegra->hs_src_clk)) अणु
		err = PTR_ERR(tegra->hs_src_clk);
		dev_err(&pdev->dev, "failed to get xusb_hs_src: %d\n", err);
		जाओ put_padctl;
	पूर्ण

	tegra->fs_src_clk = devm_clk_get(&pdev->dev, "xusb_fs_src");
	अगर (IS_ERR(tegra->fs_src_clk)) अणु
		err = PTR_ERR(tegra->fs_src_clk);
		dev_err(&pdev->dev, "failed to get xusb_fs_src: %d\n", err);
		जाओ put_padctl;
	पूर्ण

	tegra->pll_u_480m = devm_clk_get(&pdev->dev, "pll_u_480m");
	अगर (IS_ERR(tegra->pll_u_480m)) अणु
		err = PTR_ERR(tegra->pll_u_480m);
		dev_err(&pdev->dev, "failed to get pll_u_480m: %d\n", err);
		जाओ put_padctl;
	पूर्ण

	tegra->clk_m = devm_clk_get(&pdev->dev, "clk_m");
	अगर (IS_ERR(tegra->clk_m)) अणु
		err = PTR_ERR(tegra->clk_m);
		dev_err(&pdev->dev, "failed to get clk_m: %d\n", err);
		जाओ put_padctl;
	पूर्ण

	tegra->pll_e = devm_clk_get(&pdev->dev, "pll_e");
	अगर (IS_ERR(tegra->pll_e)) अणु
		err = PTR_ERR(tegra->pll_e);
		dev_err(&pdev->dev, "failed to get pll_e: %d\n", err);
		जाओ put_padctl;
	पूर्ण

	अगर (!of_property_पढ़ो_bool(pdev->dev.of_node, "power-domains")) अणु
		tegra->host_rst = devm_reset_control_get(&pdev->dev,
							 "xusb_host");
		अगर (IS_ERR(tegra->host_rst)) अणु
			err = PTR_ERR(tegra->host_rst);
			dev_err(&pdev->dev,
				"failed to get xusb_host reset: %d\n", err);
			जाओ put_padctl;
		पूर्ण

		tegra->ss_rst = devm_reset_control_get(&pdev->dev, "xusb_ss");
		अगर (IS_ERR(tegra->ss_rst)) अणु
			err = PTR_ERR(tegra->ss_rst);
			dev_err(&pdev->dev, "failed to get xusb_ss reset: %d\n",
				err);
			जाओ put_padctl;
		पूर्ण

		err = tegra_घातergate_sequence_घातer_up(TEGRA_POWERGATE_XUSBA,
							tegra->ss_clk,
							tegra->ss_rst);
		अगर (err) अणु
			dev_err(&pdev->dev,
				"failed to enable XUSBA domain: %d\n", err);
			जाओ put_padctl;
		पूर्ण

		err = tegra_घातergate_sequence_घातer_up(TEGRA_POWERGATE_XUSBC,
							tegra->host_clk,
							tegra->host_rst);
		अगर (err) अणु
			tegra_घातergate_घातer_off(TEGRA_POWERGATE_XUSBA);
			dev_err(&pdev->dev,
				"failed to enable XUSBC domain: %d\n", err);
			जाओ put_padctl;
		पूर्ण
	पूर्ण अन्यथा अणु
		err = tegra_xusb_घातerकरोमुख्य_init(&pdev->dev, tegra);
		अगर (err)
			जाओ put_घातerकरोमुख्यs;
	पूर्ण

	tegra->supplies = devm_kसुस्मृति(&pdev->dev, tegra->soc->num_supplies,
				       माप(*tegra->supplies), GFP_KERNEL);
	अगर (!tegra->supplies) अणु
		err = -ENOMEM;
		जाओ put_घातerकरोमुख्यs;
	पूर्ण

	regulator_bulk_set_supply_names(tegra->supplies,
					tegra->soc->supply_names,
					tegra->soc->num_supplies);

	err = devm_regulator_bulk_get(&pdev->dev, tegra->soc->num_supplies,
				      tegra->supplies);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to get regulators: %d\n", err);
		जाओ put_घातerकरोमुख्यs;
	पूर्ण

	क्रम (i = 0; i < tegra->soc->num_types; i++) अणु
		अगर (!म_भेदन(tegra->soc->phy_types[i].name, "usb2", 4))
			tegra->num_usb_phys = tegra->soc->phy_types[i].num;
		tegra->num_phys += tegra->soc->phy_types[i].num;
	पूर्ण

	tegra->phys = devm_kसुस्मृति(&pdev->dev, tegra->num_phys,
				   माप(*tegra->phys), GFP_KERNEL);
	अगर (!tegra->phys) अणु
		err = -ENOMEM;
		जाओ put_घातerकरोमुख्यs;
	पूर्ण

	क्रम (i = 0, k = 0; i < tegra->soc->num_types; i++) अणु
		अक्षर prop[8];

		क्रम (j = 0; j < tegra->soc->phy_types[i].num; j++) अणु
			snम_लिखो(prop, माप(prop), "%s-%d",
				 tegra->soc->phy_types[i].name, j);

			phy = devm_phy_optional_get(&pdev->dev, prop);
			अगर (IS_ERR(phy)) अणु
				dev_err(&pdev->dev,
					"failed to get PHY %s: %ld\n", prop,
					PTR_ERR(phy));
				err = PTR_ERR(phy);
				जाओ put_घातerकरोमुख्यs;
			पूर्ण

			tegra->phys[k++] = phy;
		पूर्ण
	पूर्ण

	tegra->hcd = usb_create_hcd(&tegra_xhci_hc_driver, &pdev->dev,
				    dev_name(&pdev->dev));
	अगर (!tegra->hcd) अणु
		err = -ENOMEM;
		जाओ put_घातerकरोमुख्यs;
	पूर्ण

	tegra->hcd->regs = tegra->regs;
	tegra->hcd->rsrc_start = regs->start;
	tegra->hcd->rsrc_len = resource_size(regs);

	/*
	 * This must happen after usb_create_hcd(), because usb_create_hcd()
	 * will overग_लिखो the drvdata of the device with the hcd it creates.
	 */
	platक्रमm_set_drvdata(pdev, tegra);

	err = tegra_xusb_phy_enable(tegra);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to enable PHYs: %d\n", err);
		जाओ put_hcd;
	पूर्ण

	/*
	 * The XUSB Falcon microcontroller can only address 40 bits, so set
	 * the DMA mask accordingly.
	 */
	err = dma_set_mask_and_coherent(tegra->dev, DMA_BIT_MASK(40));
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to set DMA mask: %d\n", err);
		जाओ disable_phy;
	पूर्ण

	err = tegra_xusb_request_firmware(tegra);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to request firmware: %d\n", err);
		जाओ disable_phy;
	पूर्ण

	pm_runसमय_enable(&pdev->dev);

	अगर (!pm_runसमय_enabled(&pdev->dev))
		err = tegra_xusb_runसमय_resume(&pdev->dev);
	अन्यथा
		err = pm_runसमय_get_sync(&pdev->dev);

	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to enable device: %d\n", err);
		जाओ मुक्त_firmware;
	पूर्ण

	tegra_xusb_config(tegra);

	err = tegra_xusb_load_firmware(tegra);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to load firmware: %d\n", err);
		जाओ put_rpm;
	पूर्ण

	err = usb_add_hcd(tegra->hcd, tegra->xhci_irq, IRQF_SHARED);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to add USB HCD: %d\n", err);
		जाओ put_rpm;
	पूर्ण

	device_wakeup_enable(tegra->hcd->self.controller);

	xhci = hcd_to_xhci(tegra->hcd);

	xhci->shared_hcd = usb_create_shared_hcd(&tegra_xhci_hc_driver,
						 &pdev->dev,
						 dev_name(&pdev->dev),
						 tegra->hcd);
	अगर (!xhci->shared_hcd) अणु
		dev_err(&pdev->dev, "failed to create shared HCD\n");
		err = -ENOMEM;
		जाओ हटाओ_usb2;
	पूर्ण

	err = usb_add_hcd(xhci->shared_hcd, tegra->xhci_irq, IRQF_SHARED);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to add shared HCD: %d\n", err);
		जाओ put_usb3;
	पूर्ण

	err = tegra_xusb_enable_firmware_messages(tegra);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to enable messages: %d\n", err);
		जाओ हटाओ_usb3;
	पूर्ण

	err = devm_request_thपढ़ोed_irq(&pdev->dev, tegra->mbox_irq,
					tegra_xusb_mbox_irq,
					tegra_xusb_mbox_thपढ़ो, 0,
					dev_name(&pdev->dev), tegra);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to request IRQ: %d\n", err);
		जाओ हटाओ_usb3;
	पूर्ण

	err = tegra_xusb_init_usb_phy(tegra);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to init USB PHY: %d\n", err);
		जाओ हटाओ_usb3;
	पूर्ण

	वापस 0;

हटाओ_usb3:
	usb_हटाओ_hcd(xhci->shared_hcd);
put_usb3:
	usb_put_hcd(xhci->shared_hcd);
हटाओ_usb2:
	usb_हटाओ_hcd(tegra->hcd);
put_rpm:
	अगर (!pm_runसमय_status_suspended(&pdev->dev))
		tegra_xusb_runसमय_suspend(&pdev->dev);
put_hcd:
	usb_put_hcd(tegra->hcd);
मुक्त_firmware:
	dma_मुक्त_coherent(&pdev->dev, tegra->fw.size, tegra->fw.virt,
			  tegra->fw.phys);
disable_phy:
	tegra_xusb_phy_disable(tegra);
	pm_runसमय_disable(&pdev->dev);
put_घातerकरोमुख्यs:
	अगर (!of_property_पढ़ो_bool(pdev->dev.of_node, "power-domains")) अणु
		tegra_घातergate_घातer_off(TEGRA_POWERGATE_XUSBC);
		tegra_घातergate_घातer_off(TEGRA_POWERGATE_XUSBA);
	पूर्ण अन्यथा अणु
		tegra_xusb_घातerकरोमुख्य_हटाओ(&pdev->dev, tegra);
	पूर्ण
put_padctl:
	tegra_xusb_padctl_put(tegra->padctl);
	वापस err;
पूर्ण

अटल पूर्णांक tegra_xusb_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra_xusb *tegra = platक्रमm_get_drvdata(pdev);
	काष्ठा xhci_hcd *xhci = hcd_to_xhci(tegra->hcd);

	tegra_xusb_deinit_usb_phy(tegra);

	usb_हटाओ_hcd(xhci->shared_hcd);
	usb_put_hcd(xhci->shared_hcd);
	xhci->shared_hcd = शून्य;
	usb_हटाओ_hcd(tegra->hcd);
	usb_put_hcd(tegra->hcd);

	dma_मुक्त_coherent(&pdev->dev, tegra->fw.size, tegra->fw.virt,
			  tegra->fw.phys);

	pm_runसमय_put_sync(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);

	अगर (!of_property_पढ़ो_bool(pdev->dev.of_node, "power-domains")) अणु
		tegra_घातergate_घातer_off(TEGRA_POWERGATE_XUSBC);
		tegra_घातergate_घातer_off(TEGRA_POWERGATE_XUSBA);
	पूर्ण अन्यथा अणु
		tegra_xusb_घातerकरोमुख्य_हटाओ(&pdev->dev, tegra);
	पूर्ण

	tegra_xusb_phy_disable(tegra);

	tegra_xusb_padctl_put(tegra->padctl);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल bool xhci_hub_ports_suspended(काष्ठा xhci_hub *hub)
अणु
	काष्ठा device *dev = hub->hcd->self.controller;
	bool status = true;
	अचिन्हित पूर्णांक i;
	u32 value;

	क्रम (i = 0; i < hub->num_ports; i++) अणु
		value = पढ़ोl(hub->ports[i]->addr);
		अगर ((value & PORT_PE) == 0)
			जारी;

		अगर ((value & PORT_PLS_MASK) != XDEV_U3) अणु
			dev_info(dev, "%u-%u isn't suspended: %#010x\n",
				 hub->hcd->self.busnum, i + 1, value);
			status = false;
		पूर्ण
	पूर्ण

	वापस status;
पूर्ण

अटल पूर्णांक tegra_xusb_check_ports(काष्ठा tegra_xusb *tegra)
अणु
	काष्ठा xhci_hcd *xhci = hcd_to_xhci(tegra->hcd);
	अचिन्हित दीर्घ flags;
	पूर्णांक err = 0;

	spin_lock_irqsave(&xhci->lock, flags);

	अगर (!xhci_hub_ports_suspended(&xhci->usb2_rhub) ||
	    !xhci_hub_ports_suspended(&xhci->usb3_rhub))
		err = -EBUSY;

	spin_unlock_irqrestore(&xhci->lock, flags);

	वापस err;
पूर्ण

अटल व्योम tegra_xusb_save_context(काष्ठा tegra_xusb *tegra)
अणु
	स्थिर काष्ठा tegra_xusb_context_soc *soc = tegra->soc->context;
	काष्ठा tegra_xusb_context *ctx = &tegra->context;
	अचिन्हित पूर्णांक i;

	अगर (soc->ipfs.num_offsets > 0) अणु
		क्रम (i = 0; i < soc->ipfs.num_offsets; i++)
			ctx->ipfs[i] = ipfs_पढ़ोl(tegra, soc->ipfs.offsets[i]);
	पूर्ण

	अगर (soc->fpci.num_offsets > 0) अणु
		क्रम (i = 0; i < soc->fpci.num_offsets; i++)
			ctx->fpci[i] = fpci_पढ़ोl(tegra, soc->fpci.offsets[i]);
	पूर्ण
पूर्ण

अटल व्योम tegra_xusb_restore_context(काष्ठा tegra_xusb *tegra)
अणु
	स्थिर काष्ठा tegra_xusb_context_soc *soc = tegra->soc->context;
	काष्ठा tegra_xusb_context *ctx = &tegra->context;
	अचिन्हित पूर्णांक i;

	अगर (soc->fpci.num_offsets > 0) अणु
		क्रम (i = 0; i < soc->fpci.num_offsets; i++)
			fpci_ग_लिखोl(tegra, ctx->fpci[i], soc->fpci.offsets[i]);
	पूर्ण

	अगर (soc->ipfs.num_offsets > 0) अणु
		क्रम (i = 0; i < soc->ipfs.num_offsets; i++)
			ipfs_ग_लिखोl(tegra, ctx->ipfs[i], soc->ipfs.offsets[i]);
	पूर्ण
पूर्ण

अटल पूर्णांक tegra_xusb_enter_elpg(काष्ठा tegra_xusb *tegra, bool wakeup)
अणु
	काष्ठा xhci_hcd *xhci = hcd_to_xhci(tegra->hcd);
	पूर्णांक err;

	err = tegra_xusb_check_ports(tegra);
	अगर (err < 0) अणु
		dev_err(tegra->dev, "not all ports suspended: %d\n", err);
		वापस err;
	पूर्ण

	err = xhci_suspend(xhci, wakeup);
	अगर (err < 0) अणु
		dev_err(tegra->dev, "failed to suspend XHCI: %d\n", err);
		वापस err;
	पूर्ण

	tegra_xusb_save_context(tegra);
	tegra_xusb_phy_disable(tegra);
	tegra_xusb_clk_disable(tegra);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_xusb_निकास_elpg(काष्ठा tegra_xusb *tegra, bool wakeup)
अणु
	काष्ठा xhci_hcd *xhci = hcd_to_xhci(tegra->hcd);
	पूर्णांक err;

	err = tegra_xusb_clk_enable(tegra);
	अगर (err < 0) अणु
		dev_err(tegra->dev, "failed to enable clocks: %d\n", err);
		वापस err;
	पूर्ण

	err = tegra_xusb_phy_enable(tegra);
	अगर (err < 0) अणु
		dev_err(tegra->dev, "failed to enable PHYs: %d\n", err);
		जाओ disable_clk;
	पूर्ण

	tegra_xusb_config(tegra);
	tegra_xusb_restore_context(tegra);

	err = tegra_xusb_load_firmware(tegra);
	अगर (err < 0) अणु
		dev_err(tegra->dev, "failed to load firmware: %d\n", err);
		जाओ disable_phy;
	पूर्ण

	err = __tegra_xusb_enable_firmware_messages(tegra);
	अगर (err < 0) अणु
		dev_err(tegra->dev, "failed to enable messages: %d\n", err);
		जाओ disable_phy;
	पूर्ण

	err = xhci_resume(xhci, true);
	अगर (err < 0) अणु
		dev_err(tegra->dev, "failed to resume XHCI: %d\n", err);
		जाओ disable_phy;
	पूर्ण

	वापस 0;

disable_phy:
	tegra_xusb_phy_disable(tegra);
disable_clk:
	tegra_xusb_clk_disable(tegra);
	वापस err;
पूर्ण

अटल पूर्णांक tegra_xusb_suspend(काष्ठा device *dev)
अणु
	काष्ठा tegra_xusb *tegra = dev_get_drvdata(dev);
	bool wakeup = device_may_wakeup(dev);
	पूर्णांक err;

	synchronize_irq(tegra->mbox_irq);

	mutex_lock(&tegra->lock);
	err = tegra_xusb_enter_elpg(tegra, wakeup);
	mutex_unlock(&tegra->lock);

	वापस err;
पूर्ण

अटल पूर्णांक tegra_xusb_resume(काष्ठा device *dev)
अणु
	काष्ठा tegra_xusb *tegra = dev_get_drvdata(dev);
	bool wakeup = device_may_wakeup(dev);
	पूर्णांक err;

	mutex_lock(&tegra->lock);
	err = tegra_xusb_निकास_elpg(tegra, wakeup);
	mutex_unlock(&tegra->lock);

	वापस err;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops tegra_xusb_pm_ops = अणु
	SET_RUNTIME_PM_OPS(tegra_xusb_runसमय_suspend,
			   tegra_xusb_runसमय_resume, शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(tegra_xusb_suspend, tegra_xusb_resume)
पूर्ण;

अटल स्थिर अक्षर * स्थिर tegra124_supply_names[] = अणु
	"avddio-pex",
	"dvddio-pex",
	"avdd-usb",
	"hvdd-usb-ss",
पूर्ण;

अटल स्थिर काष्ठा tegra_xusb_phy_type tegra124_phy_types[] = अणु
	अणु .name = "usb3", .num = 2, पूर्ण,
	अणु .name = "usb2", .num = 3, पूर्ण,
	अणु .name = "hsic", .num = 2, पूर्ण,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक tegra124_xusb_context_ipfs[] = अणु
	IPFS_XUSB_HOST_MSI_BAR_SZ_0,
	IPFS_XUSB_HOST_MSI_AXI_BAR_ST_0,
	IPFS_XUSB_HOST_MSI_FPCI_BAR_ST_0,
	IPFS_XUSB_HOST_MSI_VEC0_0,
	IPFS_XUSB_HOST_MSI_EN_VEC0_0,
	IPFS_XUSB_HOST_FPCI_ERROR_MASKS_0,
	IPFS_XUSB_HOST_INTR_MASK_0,
	IPFS_XUSB_HOST_INTR_ENABLE_0,
	IPFS_XUSB_HOST_UFPCI_CONFIG_0,
	IPFS_XUSB_HOST_CLKGATE_HYSTERESIS_0,
	IPFS_XUSB_HOST_MCCIF_FIFOCTRL_0,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक tegra124_xusb_context_fpci[] = अणु
	XUSB_CFG_ARU_CONTEXT_HS_PLS,
	XUSB_CFG_ARU_CONTEXT_FS_PLS,
	XUSB_CFG_ARU_CONTEXT_HSFS_SPEED,
	XUSB_CFG_ARU_CONTEXT_HSFS_PP,
	XUSB_CFG_ARU_CONTEXT,
	XUSB_CFG_AXI_CFG,
	XUSB_CFG_24,
	XUSB_CFG_16,
पूर्ण;

अटल स्थिर काष्ठा tegra_xusb_context_soc tegra124_xusb_context = अणु
	.ipfs = अणु
		.num_offsets = ARRAY_SIZE(tegra124_xusb_context_ipfs),
		.offsets = tegra124_xusb_context_ipfs,
	पूर्ण,
	.fpci = अणु
		.num_offsets = ARRAY_SIZE(tegra124_xusb_context_fpci),
		.offsets = tegra124_xusb_context_fpci,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा tegra_xusb_soc tegra124_soc = अणु
	.firmware = "nvidia/tegra124/xusb.bin",
	.supply_names = tegra124_supply_names,
	.num_supplies = ARRAY_SIZE(tegra124_supply_names),
	.phy_types = tegra124_phy_types,
	.num_types = ARRAY_SIZE(tegra124_phy_types),
	.context = &tegra124_xusb_context,
	.ports = अणु
		.usb2 = अणु .offset = 4, .count = 4, पूर्ण,
		.hsic = अणु .offset = 6, .count = 2, पूर्ण,
		.usb3 = अणु .offset = 0, .count = 2, पूर्ण,
	पूर्ण,
	.scale_ss_घड़ी = true,
	.has_ipfs = true,
	.otg_reset_sspi = false,
	.mbox = अणु
		.cmd = 0xe4,
		.data_in = 0xe8,
		.data_out = 0xec,
		.owner = 0xf0,
	पूर्ण,
पूर्ण;
MODULE_FIRMWARE("nvidia/tegra124/xusb.bin");

अटल स्थिर अक्षर * स्थिर tegra210_supply_names[] = अणु
	"dvddio-pex",
	"hvddio-pex",
	"avdd-usb",
पूर्ण;

अटल स्थिर काष्ठा tegra_xusb_phy_type tegra210_phy_types[] = अणु
	अणु .name = "usb3", .num = 4, पूर्ण,
	अणु .name = "usb2", .num = 4, पूर्ण,
	अणु .name = "hsic", .num = 1, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा tegra_xusb_soc tegra210_soc = अणु
	.firmware = "nvidia/tegra210/xusb.bin",
	.supply_names = tegra210_supply_names,
	.num_supplies = ARRAY_SIZE(tegra210_supply_names),
	.phy_types = tegra210_phy_types,
	.num_types = ARRAY_SIZE(tegra210_phy_types),
	.context = &tegra124_xusb_context,
	.ports = अणु
		.usb2 = अणु .offset = 4, .count = 4, पूर्ण,
		.hsic = अणु .offset = 8, .count = 1, पूर्ण,
		.usb3 = अणु .offset = 0, .count = 4, पूर्ण,
	पूर्ण,
	.scale_ss_घड़ी = false,
	.has_ipfs = true,
	.otg_reset_sspi = true,
	.mbox = अणु
		.cmd = 0xe4,
		.data_in = 0xe8,
		.data_out = 0xec,
		.owner = 0xf0,
	पूर्ण,
पूर्ण;
MODULE_FIRMWARE("nvidia/tegra210/xusb.bin");

अटल स्थिर अक्षर * स्थिर tegra186_supply_names[] = अणु
पूर्ण;
MODULE_FIRMWARE("nvidia/tegra186/xusb.bin");

अटल स्थिर काष्ठा tegra_xusb_phy_type tegra186_phy_types[] = अणु
	अणु .name = "usb3", .num = 3, पूर्ण,
	अणु .name = "usb2", .num = 3, पूर्ण,
	अणु .name = "hsic", .num = 1, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा tegra_xusb_context_soc tegra186_xusb_context = अणु
	.fpci = अणु
		.num_offsets = ARRAY_SIZE(tegra124_xusb_context_fpci),
		.offsets = tegra124_xusb_context_fpci,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा tegra_xusb_soc tegra186_soc = अणु
	.firmware = "nvidia/tegra186/xusb.bin",
	.supply_names = tegra186_supply_names,
	.num_supplies = ARRAY_SIZE(tegra186_supply_names),
	.phy_types = tegra186_phy_types,
	.num_types = ARRAY_SIZE(tegra186_phy_types),
	.context = &tegra186_xusb_context,
	.ports = अणु
		.usb3 = अणु .offset = 0, .count = 3, पूर्ण,
		.usb2 = अणु .offset = 3, .count = 3, पूर्ण,
		.hsic = अणु .offset = 6, .count = 1, पूर्ण,
	पूर्ण,
	.scale_ss_घड़ी = false,
	.has_ipfs = false,
	.otg_reset_sspi = false,
	.mbox = अणु
		.cmd = 0xe4,
		.data_in = 0xe8,
		.data_out = 0xec,
		.owner = 0xf0,
	पूर्ण,
	.lpm_support = true,
पूर्ण;

अटल स्थिर अक्षर * स्थिर tegra194_supply_names[] = अणु
पूर्ण;

अटल स्थिर काष्ठा tegra_xusb_phy_type tegra194_phy_types[] = अणु
	अणु .name = "usb3", .num = 4, पूर्ण,
	अणु .name = "usb2", .num = 4, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा tegra_xusb_soc tegra194_soc = अणु
	.firmware = "nvidia/tegra194/xusb.bin",
	.supply_names = tegra194_supply_names,
	.num_supplies = ARRAY_SIZE(tegra194_supply_names),
	.phy_types = tegra194_phy_types,
	.num_types = ARRAY_SIZE(tegra194_phy_types),
	.context = &tegra186_xusb_context,
	.ports = अणु
		.usb3 = अणु .offset = 0, .count = 4, पूर्ण,
		.usb2 = अणु .offset = 4, .count = 4, पूर्ण,
	पूर्ण,
	.scale_ss_घड़ी = false,
	.has_ipfs = false,
	.otg_reset_sspi = false,
	.mbox = अणु
		.cmd = 0x68,
		.data_in = 0x6c,
		.data_out = 0x70,
		.owner = 0x74,
	पूर्ण,
	.lpm_support = true,
पूर्ण;
MODULE_FIRMWARE("nvidia/tegra194/xusb.bin");

अटल स्थिर काष्ठा of_device_id tegra_xusb_of_match[] = अणु
	अणु .compatible = "nvidia,tegra124-xusb", .data = &tegra124_soc पूर्ण,
	अणु .compatible = "nvidia,tegra210-xusb", .data = &tegra210_soc पूर्ण,
	अणु .compatible = "nvidia,tegra186-xusb", .data = &tegra186_soc पूर्ण,
	अणु .compatible = "nvidia,tegra194-xusb", .data = &tegra194_soc पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, tegra_xusb_of_match);

अटल काष्ठा platक्रमm_driver tegra_xusb_driver = अणु
	.probe = tegra_xusb_probe,
	.हटाओ = tegra_xusb_हटाओ,
	.driver = अणु
		.name = "tegra-xusb",
		.pm = &tegra_xusb_pm_ops,
		.of_match_table = tegra_xusb_of_match,
	पूर्ण,
पूर्ण;

अटल व्योम tegra_xhci_quirks(काष्ठा device *dev, काष्ठा xhci_hcd *xhci)
अणु
	काष्ठा tegra_xusb *tegra = dev_get_drvdata(dev);

	xhci->quirks |= XHCI_PLAT;
	अगर (tegra && tegra->soc->lpm_support)
		xhci->quirks |= XHCI_LPM_SUPPORT;
पूर्ण

अटल पूर्णांक tegra_xhci_setup(काष्ठा usb_hcd *hcd)
अणु
	वापस xhci_gen_setup(hcd, tegra_xhci_quirks);
पूर्ण

अटल स्थिर काष्ठा xhci_driver_overrides tegra_xhci_overrides __initस्थिर = अणु
	.reset = tegra_xhci_setup,
पूर्ण;

अटल पूर्णांक __init tegra_xusb_init(व्योम)
अणु
	xhci_init_driver(&tegra_xhci_hc_driver, &tegra_xhci_overrides);

	वापस platक्रमm_driver_रेजिस्टर(&tegra_xusb_driver);
पूर्ण
module_init(tegra_xusb_init);

अटल व्योम __निकास tegra_xusb_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&tegra_xusb_driver);
पूर्ण
module_निकास(tegra_xusb_निकास);

MODULE_AUTHOR("Andrew Bresticker <abrestic@chromium.org>");
MODULE_DESCRIPTION("NVIDIA Tegra XUSB xHCI host-controller driver");
MODULE_LICENSE("GPL v2");
