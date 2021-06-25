<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2012-2015, 2017, 2021, The Linux Foundation. All rights reserved.
 */
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/spmi.h>

/* PMIC Arbiter configuration रेजिस्टरs */
#घोषणा PMIC_ARB_VERSION		0x0000
#घोषणा PMIC_ARB_VERSION_V2_MIN		0x20010000
#घोषणा PMIC_ARB_VERSION_V3_MIN		0x30000000
#घोषणा PMIC_ARB_VERSION_V5_MIN		0x50000000
#घोषणा PMIC_ARB_INT_EN			0x0004

/* PMIC Arbiter channel रेजिस्टरs offsets */
#घोषणा PMIC_ARB_CMD			0x00
#घोषणा PMIC_ARB_CONFIG			0x04
#घोषणा PMIC_ARB_STATUS			0x08
#घोषणा PMIC_ARB_WDATA0			0x10
#घोषणा PMIC_ARB_WDATA1			0x14
#घोषणा PMIC_ARB_RDATA0			0x18
#घोषणा PMIC_ARB_RDATA1			0x1C

/* Mapping Table */
#घोषणा SPMI_MAPPING_TABLE_REG(N)	(0x0B00 + (4 * (N)))
#घोषणा SPMI_MAPPING_BIT_INDEX(X)	(((X) >> 18) & 0xF)
#घोषणा SPMI_MAPPING_BIT_IS_0_FLAG(X)	(((X) >> 17) & 0x1)
#घोषणा SPMI_MAPPING_BIT_IS_0_RESULT(X)	(((X) >> 9) & 0xFF)
#घोषणा SPMI_MAPPING_BIT_IS_1_FLAG(X)	(((X) >> 8) & 0x1)
#घोषणा SPMI_MAPPING_BIT_IS_1_RESULT(X)	(((X) >> 0) & 0xFF)

#घोषणा SPMI_MAPPING_TABLE_TREE_DEPTH	16	/* Maximum of 16-bits */
#घोषणा PMIC_ARB_MAX_PPID		BIT(12) /* PPID is 12bit */
#घोषणा PMIC_ARB_APID_VALID		BIT(15)
#घोषणा PMIC_ARB_CHAN_IS_IRQ_OWNER(reg)	((reg) & BIT(24))
#घोषणा INVALID_EE				0xFF

/* Ownership Table */
#घोषणा SPMI_OWNERSHIP_TABLE_REG(N)	(0x0700 + (4 * (N)))
#घोषणा SPMI_OWNERSHIP_PERIPH2OWNER(X)	((X) & 0x7)

/* Channel Status fields */
क्रमागत pmic_arb_chnl_status अणु
	PMIC_ARB_STATUS_DONE	= BIT(0),
	PMIC_ARB_STATUS_FAILURE	= BIT(1),
	PMIC_ARB_STATUS_DENIED	= BIT(2),
	PMIC_ARB_STATUS_DROPPED	= BIT(3),
पूर्ण;

/* Command रेजिस्टर fields */
#घोषणा PMIC_ARB_CMD_MAX_BYTE_COUNT	8

/* Command Opcodes */
क्रमागत pmic_arb_cmd_op_code अणु
	PMIC_ARB_OP_EXT_WRITEL = 0,
	PMIC_ARB_OP_EXT_READL = 1,
	PMIC_ARB_OP_EXT_WRITE = 2,
	PMIC_ARB_OP_RESET = 3,
	PMIC_ARB_OP_SLEEP = 4,
	PMIC_ARB_OP_SHUTDOWN = 5,
	PMIC_ARB_OP_WAKEUP = 6,
	PMIC_ARB_OP_AUTHENTICATE = 7,
	PMIC_ARB_OP_MSTR_READ = 8,
	PMIC_ARB_OP_MSTR_WRITE = 9,
	PMIC_ARB_OP_EXT_READ = 13,
	PMIC_ARB_OP_WRITE = 14,
	PMIC_ARB_OP_READ = 15,
	PMIC_ARB_OP_ZERO_WRITE = 16,
पूर्ण;

/*
 * PMIC arbiter version 5 uses dअगरferent रेजिस्टर offsets क्रम पढ़ो/ग_लिखो vs
 * observer channels.
 */
क्रमागत pmic_arb_channel अणु
	PMIC_ARB_CHANNEL_RW,
	PMIC_ARB_CHANNEL_OBS,
पूर्ण;

/* Maximum number of support PMIC peripherals */
#घोषणा PMIC_ARB_MAX_PERIPHS		512
#घोषणा PMIC_ARB_TIMEOUT_US		100
#घोषणा PMIC_ARB_MAX_TRANS_BYTES	(8)

#घोषणा PMIC_ARB_APID_MASK		0xFF
#घोषणा PMIC_ARB_PPID_MASK		0xFFF

/* पूर्णांकerrupt enable bit */
#घोषणा SPMI_PIC_ACC_ENABLE_BIT		BIT(0)

#घोषणा spec_to_hwirq(slave_id, periph_id, irq_id, apid) \
	((((slave_id) & 0xF)   << 28) | \
	(((periph_id) & 0xFF)  << 20) | \
	(((irq_id)    & 0x7)   << 16) | \
	(((apid)      & 0x1FF) << 0))

#घोषणा hwirq_to_sid(hwirq)  (((hwirq) >> 28) & 0xF)
#घोषणा hwirq_to_per(hwirq)  (((hwirq) >> 20) & 0xFF)
#घोषणा hwirq_to_irq(hwirq)  (((hwirq) >> 16) & 0x7)
#घोषणा hwirq_to_apid(hwirq) (((hwirq) >> 0)  & 0x1FF)

काष्ठा pmic_arb_ver_ops;

काष्ठा apid_data अणु
	u16		ppid;
	u8		ग_लिखो_ee;
	u8		irq_ee;
पूर्ण;

/**
 * spmi_pmic_arb - SPMI PMIC Arbiter object
 *
 * @rd_base:		on v1 "core", on v2 "observer" रेजिस्टर base off DT.
 * @wr_base:		on v1 "core", on v2 "chnls"    रेजिस्टर base off DT.
 * @पूर्णांकr:		address of the SPMI पूर्णांकerrupt control रेजिस्टरs.
 * @cnfg:		address of the PMIC Arbiter configuration रेजिस्टरs.
 * @lock:		lock to synchronize accesses.
 * @channel:		execution environment channel to use क्रम accesses.
 * @irq:		PMIC ARB पूर्णांकerrupt.
 * @ee:			the current Execution Environment
 * @min_apid:		minimum APID (used क्रम bounding IRQ search)
 * @max_apid:		maximum APID
 * @mapping_table:	in-memory copy of PPID -> APID mapping table.
 * @करोमुख्य:		irq करोमुख्य object क्रम PMIC IRQ करोमुख्य
 * @spmic:		SPMI controller object
 * @ver_ops:		version dependent operations.
 * @ppid_to_apid	in-memory copy of PPID -> APID mapping table.
 */
काष्ठा spmi_pmic_arb अणु
	व्योम __iomem		*rd_base;
	व्योम __iomem		*wr_base;
	व्योम __iomem		*पूर्णांकr;
	व्योम __iomem		*cnfg;
	व्योम __iomem		*core;
	resource_माप_प्रकार		core_size;
	raw_spinlock_t		lock;
	u8			channel;
	पूर्णांक			irq;
	u8			ee;
	u16			min_apid;
	u16			max_apid;
	u32			*mapping_table;
	DECLARE_BITMAP(mapping_table_valid, PMIC_ARB_MAX_PERIPHS);
	काष्ठा irq_करोमुख्य	*करोमुख्य;
	काष्ठा spmi_controller	*spmic;
	स्थिर काष्ठा pmic_arb_ver_ops *ver_ops;
	u16			*ppid_to_apid;
	u16			last_apid;
	काष्ठा apid_data	apid_data[PMIC_ARB_MAX_PERIPHS];
पूर्ण;

/**
 * pmic_arb_ver: version dependent functionality.
 *
 * @ver_str:		version string.
 * @ppid_to_apid:	finds the apid क्रम a given ppid.
 * @non_data_cmd:	on v1 issues an spmi non-data command.
 *			on v2 no HW support, वापसs -EOPNOTSUPP.
 * @offset:		on v1 offset of per-ee channel.
 *			on v2 offset of per-ee and per-ppid channel.
 * @fmt_cmd:		क्रमmats a GENI/SPMI command.
 * @owner_acc_status:	on v1 address of PMIC_ARB_SPMI_PIC_OWNERm_ACC_STATUSn
 *			on v2 address of SPMI_PIC_OWNERm_ACC_STATUSn.
 * @acc_enable:		on v1 address of PMIC_ARB_SPMI_PIC_ACC_ENABLEn
 *			on v2 address of SPMI_PIC_ACC_ENABLEn.
 * @irq_status:		on v1 address of PMIC_ARB_SPMI_PIC_IRQ_STATUSn
 *			on v2 address of SPMI_PIC_IRQ_STATUSn.
 * @irq_clear:		on v1 address of PMIC_ARB_SPMI_PIC_IRQ_CLEARn
 *			on v2 address of SPMI_PIC_IRQ_CLEARn.
 * @apid_map_offset:	offset of PMIC_ARB_REG_CHNLn
 */
काष्ठा pmic_arb_ver_ops अणु
	स्थिर अक्षर *ver_str;
	पूर्णांक (*ppid_to_apid)(काष्ठा spmi_pmic_arb *pmic_arb, u16 ppid);
	/* spmi commands (पढ़ो_cmd, ग_लिखो_cmd, cmd) functionality */
	पूर्णांक (*offset)(काष्ठा spmi_pmic_arb *pmic_arb, u8 sid, u16 addr,
			क्रमागत pmic_arb_channel ch_type);
	u32 (*fmt_cmd)(u8 opc, u8 sid, u16 addr, u8 bc);
	पूर्णांक (*non_data_cmd)(काष्ठा spmi_controller *ctrl, u8 opc, u8 sid);
	/* Interrupts controller functionality (offset of PIC रेजिस्टरs) */
	व्योम __iomem *(*owner_acc_status)(काष्ठा spmi_pmic_arb *pmic_arb, u8 m,
					  u16 n);
	व्योम __iomem *(*acc_enable)(काष्ठा spmi_pmic_arb *pmic_arb, u16 n);
	व्योम __iomem *(*irq_status)(काष्ठा spmi_pmic_arb *pmic_arb, u16 n);
	व्योम __iomem *(*irq_clear)(काष्ठा spmi_pmic_arb *pmic_arb, u16 n);
	u32 (*apid_map_offset)(u16 n);
पूर्ण;

अटल अंतरभूत व्योम pmic_arb_base_ग_लिखो(काष्ठा spmi_pmic_arb *pmic_arb,
				       u32 offset, u32 val)
अणु
	ग_लिखोl_relaxed(val, pmic_arb->wr_base + offset);
पूर्ण

अटल अंतरभूत व्योम pmic_arb_set_rd_cmd(काष्ठा spmi_pmic_arb *pmic_arb,
				       u32 offset, u32 val)
अणु
	ग_लिखोl_relaxed(val, pmic_arb->rd_base + offset);
पूर्ण

/**
 * pmic_arb_पढ़ो_data: पढ़ोs pmic-arb's रेजिस्टर and copy 1..4 bytes to buf
 * @bc:		byte count -1. range: 0..3
 * @reg:	रेजिस्टर's address
 * @buf:	output parameter, length must be bc + 1
 */
अटल व्योम
pmic_arb_पढ़ो_data(काष्ठा spmi_pmic_arb *pmic_arb, u8 *buf, u32 reg, u8 bc)
अणु
	u32 data = __raw_पढ़ोl(pmic_arb->rd_base + reg);

	स_नकल(buf, &data, (bc & 3) + 1);
पूर्ण

/**
 * pmic_arb_ग_लिखो_data: ग_लिखो 1..4 bytes from buf to pmic-arb's रेजिस्टर
 * @bc:		byte-count -1. range: 0..3.
 * @reg:	रेजिस्टर's address.
 * @buf:	buffer to ग_लिखो. length must be bc + 1.
 */
अटल व्योम pmic_arb_ग_लिखो_data(काष्ठा spmi_pmic_arb *pmic_arb, स्थिर u8 *buf,
				u32 reg, u8 bc)
अणु
	u32 data = 0;

	स_नकल(&data, buf, (bc & 3) + 1);
	__raw_ग_लिखोl(data, pmic_arb->wr_base + reg);
पूर्ण

अटल पूर्णांक pmic_arb_रुको_क्रम_करोne(काष्ठा spmi_controller *ctrl,
				  व्योम __iomem *base, u8 sid, u16 addr,
				  क्रमागत pmic_arb_channel ch_type)
अणु
	काष्ठा spmi_pmic_arb *pmic_arb = spmi_controller_get_drvdata(ctrl);
	u32 status = 0;
	u32 समयout = PMIC_ARB_TIMEOUT_US;
	u32 offset;
	पूर्णांक rc;

	rc = pmic_arb->ver_ops->offset(pmic_arb, sid, addr, ch_type);
	अगर (rc < 0)
		वापस rc;

	offset = rc;
	offset += PMIC_ARB_STATUS;

	जबतक (समयout--) अणु
		status = पढ़ोl_relaxed(base + offset);

		अगर (status & PMIC_ARB_STATUS_DONE) अणु
			अगर (status & PMIC_ARB_STATUS_DENIED) अणु
				dev_err(&ctrl->dev, "%s: transaction denied (0x%x)\n",
					__func__, status);
				वापस -EPERM;
			पूर्ण

			अगर (status & PMIC_ARB_STATUS_FAILURE) अणु
				dev_err(&ctrl->dev, "%s: transaction failed (0x%x)\n",
					__func__, status);
				वापस -EIO;
			पूर्ण

			अगर (status & PMIC_ARB_STATUS_DROPPED) अणु
				dev_err(&ctrl->dev, "%s: transaction dropped (0x%x)\n",
					__func__, status);
				वापस -EIO;
			पूर्ण

			वापस 0;
		पूर्ण
		udelay(1);
	पूर्ण

	dev_err(&ctrl->dev, "%s: timeout, status 0x%x\n",
		__func__, status);
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक
pmic_arb_non_data_cmd_v1(काष्ठा spmi_controller *ctrl, u8 opc, u8 sid)
अणु
	काष्ठा spmi_pmic_arb *pmic_arb = spmi_controller_get_drvdata(ctrl);
	अचिन्हित दीर्घ flags;
	u32 cmd;
	पूर्णांक rc;
	u32 offset;

	rc = pmic_arb->ver_ops->offset(pmic_arb, sid, 0, PMIC_ARB_CHANNEL_RW);
	अगर (rc < 0)
		वापस rc;

	offset = rc;
	cmd = ((opc | 0x40) << 27) | ((sid & 0xf) << 20);

	raw_spin_lock_irqsave(&pmic_arb->lock, flags);
	pmic_arb_base_ग_लिखो(pmic_arb, offset + PMIC_ARB_CMD, cmd);
	rc = pmic_arb_रुको_क्रम_करोne(ctrl, pmic_arb->wr_base, sid, 0,
				    PMIC_ARB_CHANNEL_RW);
	raw_spin_unlock_irqrestore(&pmic_arb->lock, flags);

	वापस rc;
पूर्ण

अटल पूर्णांक
pmic_arb_non_data_cmd_v2(काष्ठा spmi_controller *ctrl, u8 opc, u8 sid)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

/* Non-data command */
अटल पूर्णांक pmic_arb_cmd(काष्ठा spmi_controller *ctrl, u8 opc, u8 sid)
अणु
	काष्ठा spmi_pmic_arb *pmic_arb = spmi_controller_get_drvdata(ctrl);

	dev_dbg(&ctrl->dev, "cmd op:0x%x sid:%d\n", opc, sid);

	/* Check क्रम valid non-data command */
	अगर (opc < SPMI_CMD_RESET || opc > SPMI_CMD_WAKEUP)
		वापस -EINVAL;

	वापस pmic_arb->ver_ops->non_data_cmd(ctrl, opc, sid);
पूर्ण

अटल पूर्णांक pmic_arb_पढ़ो_cmd(काष्ठा spmi_controller *ctrl, u8 opc, u8 sid,
			     u16 addr, u8 *buf, माप_प्रकार len)
अणु
	काष्ठा spmi_pmic_arb *pmic_arb = spmi_controller_get_drvdata(ctrl);
	अचिन्हित दीर्घ flags;
	u8 bc = len - 1;
	u32 cmd;
	पूर्णांक rc;
	u32 offset;

	rc = pmic_arb->ver_ops->offset(pmic_arb, sid, addr,
				       PMIC_ARB_CHANNEL_OBS);
	अगर (rc < 0)
		वापस rc;

	offset = rc;
	अगर (bc >= PMIC_ARB_MAX_TRANS_BYTES) अणु
		dev_err(&ctrl->dev, "pmic-arb supports 1..%d bytes per trans, but:%zu requested",
			PMIC_ARB_MAX_TRANS_BYTES, len);
		वापस  -EINVAL;
	पूर्ण

	/* Check the opcode */
	अगर (opc >= 0x60 && opc <= 0x7F)
		opc = PMIC_ARB_OP_READ;
	अन्यथा अगर (opc >= 0x20 && opc <= 0x2F)
		opc = PMIC_ARB_OP_EXT_READ;
	अन्यथा अगर (opc >= 0x38 && opc <= 0x3F)
		opc = PMIC_ARB_OP_EXT_READL;
	अन्यथा
		वापस -EINVAL;

	cmd = pmic_arb->ver_ops->fmt_cmd(opc, sid, addr, bc);

	raw_spin_lock_irqsave(&pmic_arb->lock, flags);
	pmic_arb_set_rd_cmd(pmic_arb, offset + PMIC_ARB_CMD, cmd);
	rc = pmic_arb_रुको_क्रम_करोne(ctrl, pmic_arb->rd_base, sid, addr,
				    PMIC_ARB_CHANNEL_OBS);
	अगर (rc)
		जाओ करोne;

	pmic_arb_पढ़ो_data(pmic_arb, buf, offset + PMIC_ARB_RDATA0,
		     min_t(u8, bc, 3));

	अगर (bc > 3)
		pmic_arb_पढ़ो_data(pmic_arb, buf + 4, offset + PMIC_ARB_RDATA1,
					bc - 4);

करोne:
	raw_spin_unlock_irqrestore(&pmic_arb->lock, flags);
	वापस rc;
पूर्ण

अटल पूर्णांक pmic_arb_ग_लिखो_cmd(काष्ठा spmi_controller *ctrl, u8 opc, u8 sid,
			u16 addr, स्थिर u8 *buf, माप_प्रकार len)
अणु
	काष्ठा spmi_pmic_arb *pmic_arb = spmi_controller_get_drvdata(ctrl);
	अचिन्हित दीर्घ flags;
	u8 bc = len - 1;
	u32 cmd;
	पूर्णांक rc;
	u32 offset;

	rc = pmic_arb->ver_ops->offset(pmic_arb, sid, addr,
					PMIC_ARB_CHANNEL_RW);
	अगर (rc < 0)
		वापस rc;

	offset = rc;
	अगर (bc >= PMIC_ARB_MAX_TRANS_BYTES) अणु
		dev_err(&ctrl->dev, "pmic-arb supports 1..%d bytes per trans, but:%zu requested",
			PMIC_ARB_MAX_TRANS_BYTES, len);
		वापस  -EINVAL;
	पूर्ण

	/* Check the opcode */
	अगर (opc >= 0x40 && opc <= 0x5F)
		opc = PMIC_ARB_OP_WRITE;
	अन्यथा अगर (opc <= 0x0F)
		opc = PMIC_ARB_OP_EXT_WRITE;
	अन्यथा अगर (opc >= 0x30 && opc <= 0x37)
		opc = PMIC_ARB_OP_EXT_WRITEL;
	अन्यथा अगर (opc >= 0x80)
		opc = PMIC_ARB_OP_ZERO_WRITE;
	अन्यथा
		वापस -EINVAL;

	cmd = pmic_arb->ver_ops->fmt_cmd(opc, sid, addr, bc);

	/* Write data to FIFOs */
	raw_spin_lock_irqsave(&pmic_arb->lock, flags);
	pmic_arb_ग_लिखो_data(pmic_arb, buf, offset + PMIC_ARB_WDATA0,
				min_t(u8, bc, 3));
	अगर (bc > 3)
		pmic_arb_ग_लिखो_data(pmic_arb, buf + 4, offset + PMIC_ARB_WDATA1,
					bc - 4);

	/* Start the transaction */
	pmic_arb_base_ग_लिखो(pmic_arb, offset + PMIC_ARB_CMD, cmd);
	rc = pmic_arb_रुको_क्रम_करोne(ctrl, pmic_arb->wr_base, sid, addr,
				    PMIC_ARB_CHANNEL_RW);
	raw_spin_unlock_irqrestore(&pmic_arb->lock, flags);

	वापस rc;
पूर्ण

क्रमागत qpnpपूर्णांक_regs अणु
	QPNPINT_REG_RT_STS		= 0x10,
	QPNPINT_REG_SET_TYPE		= 0x11,
	QPNPINT_REG_POLARITY_HIGH	= 0x12,
	QPNPINT_REG_POLARITY_LOW	= 0x13,
	QPNPINT_REG_LATCHED_CLR		= 0x14,
	QPNPINT_REG_EN_SET		= 0x15,
	QPNPINT_REG_EN_CLR		= 0x16,
	QPNPINT_REG_LATCHED_STS		= 0x18,
पूर्ण;

काष्ठा spmi_pmic_arb_qpnpपूर्णांक_type अणु
	u8 type; /* 1 -> edge */
	u8 polarity_high;
	u8 polarity_low;
पूर्ण __packed;

/* Simplअगरied accessor functions क्रम irqchip callbacks */
अटल व्योम qpnpपूर्णांक_spmi_ग_लिखो(काष्ठा irq_data *d, u8 reg, व्योम *buf,
			       माप_प्रकार len)
अणु
	काष्ठा spmi_pmic_arb *pmic_arb = irq_data_get_irq_chip_data(d);
	u8 sid = hwirq_to_sid(d->hwirq);
	u8 per = hwirq_to_per(d->hwirq);

	अगर (pmic_arb_ग_लिखो_cmd(pmic_arb->spmic, SPMI_CMD_EXT_WRITEL, sid,
			       (per << 8) + reg, buf, len))
		dev_err_ratelimited(&pmic_arb->spmic->dev, "failed irqchip transaction on %x\n",
				    d->irq);
पूर्ण

अटल व्योम qpnpपूर्णांक_spmi_पढ़ो(काष्ठा irq_data *d, u8 reg, व्योम *buf, माप_प्रकार len)
अणु
	काष्ठा spmi_pmic_arb *pmic_arb = irq_data_get_irq_chip_data(d);
	u8 sid = hwirq_to_sid(d->hwirq);
	u8 per = hwirq_to_per(d->hwirq);

	अगर (pmic_arb_पढ़ो_cmd(pmic_arb->spmic, SPMI_CMD_EXT_READL, sid,
			      (per << 8) + reg, buf, len))
		dev_err_ratelimited(&pmic_arb->spmic->dev, "failed irqchip transaction on %x\n",
				    d->irq);
पूर्ण

अटल व्योम cleanup_irq(काष्ठा spmi_pmic_arb *pmic_arb, u16 apid, पूर्णांक id)
अणु
	u16 ppid = pmic_arb->apid_data[apid].ppid;
	u8 sid = ppid >> 8;
	u8 per = ppid & 0xFF;
	u8 irq_mask = BIT(id);

	ग_लिखोl_relaxed(irq_mask, pmic_arb->ver_ops->irq_clear(pmic_arb, apid));

	अगर (pmic_arb_ग_लिखो_cmd(pmic_arb->spmic, SPMI_CMD_EXT_WRITEL, sid,
			(per << 8) + QPNPINT_REG_LATCHED_CLR, &irq_mask, 1))
		dev_err_ratelimited(&pmic_arb->spmic->dev, "failed to ack irq_mask = 0x%x for ppid = %x\n",
				irq_mask, ppid);

	अगर (pmic_arb_ग_लिखो_cmd(pmic_arb->spmic, SPMI_CMD_EXT_WRITEL, sid,
			       (per << 8) + QPNPINT_REG_EN_CLR, &irq_mask, 1))
		dev_err_ratelimited(&pmic_arb->spmic->dev, "failed to ack irq_mask = 0x%x for ppid = %x\n",
				irq_mask, ppid);
पूर्ण

अटल व्योम periph_पूर्णांकerrupt(काष्ठा spmi_pmic_arb *pmic_arb, u16 apid)
अणु
	अचिन्हित पूर्णांक irq;
	u32 status, id;
	u8 sid = (pmic_arb->apid_data[apid].ppid >> 8) & 0xF;
	u8 per = pmic_arb->apid_data[apid].ppid & 0xFF;

	status = पढ़ोl_relaxed(pmic_arb->ver_ops->irq_status(pmic_arb, apid));
	जबतक (status) अणु
		id = ffs(status) - 1;
		status &= ~BIT(id);
		irq = irq_find_mapping(pmic_arb->करोमुख्य,
					spec_to_hwirq(sid, per, id, apid));
		अगर (irq == 0) अणु
			cleanup_irq(pmic_arb, apid, id);
			जारी;
		पूर्ण
		generic_handle_irq(irq);
	पूर्ण
पूर्ण

अटल व्योम pmic_arb_chained_irq(काष्ठा irq_desc *desc)
अणु
	काष्ठा spmi_pmic_arb *pmic_arb = irq_desc_get_handler_data(desc);
	स्थिर काष्ठा pmic_arb_ver_ops *ver_ops = pmic_arb->ver_ops;
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	पूर्णांक first = pmic_arb->min_apid >> 5;
	पूर्णांक last = pmic_arb->max_apid >> 5;
	u8 ee = pmic_arb->ee;
	u32 status, enable;
	पूर्णांक i, id, apid;

	chained_irq_enter(chip, desc);

	क्रम (i = first; i <= last; ++i) अणु
		status = पढ़ोl_relaxed(
				ver_ops->owner_acc_status(pmic_arb, ee, i));
		जबतक (status) अणु
			id = ffs(status) - 1;
			status &= ~BIT(id);
			apid = id + i * 32;
			enable = पढ़ोl_relaxed(
					ver_ops->acc_enable(pmic_arb, apid));
			अगर (enable & SPMI_PIC_ACC_ENABLE_BIT)
				periph_पूर्णांकerrupt(pmic_arb, apid);
		पूर्ण
	पूर्ण

	chained_irq_निकास(chip, desc);
पूर्ण

अटल व्योम qpnpपूर्णांक_irq_ack(काष्ठा irq_data *d)
अणु
	काष्ठा spmi_pmic_arb *pmic_arb = irq_data_get_irq_chip_data(d);
	u8 irq = hwirq_to_irq(d->hwirq);
	u16 apid = hwirq_to_apid(d->hwirq);
	u8 data;

	ग_लिखोl_relaxed(BIT(irq), pmic_arb->ver_ops->irq_clear(pmic_arb, apid));

	data = BIT(irq);
	qpnpपूर्णांक_spmi_ग_लिखो(d, QPNPINT_REG_LATCHED_CLR, &data, 1);
पूर्ण

अटल व्योम qpnpपूर्णांक_irq_mask(काष्ठा irq_data *d)
अणु
	u8 irq = hwirq_to_irq(d->hwirq);
	u8 data = BIT(irq);

	qpnpपूर्णांक_spmi_ग_लिखो(d, QPNPINT_REG_EN_CLR, &data, 1);
पूर्ण

अटल व्योम qpnpपूर्णांक_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा spmi_pmic_arb *pmic_arb = irq_data_get_irq_chip_data(d);
	स्थिर काष्ठा pmic_arb_ver_ops *ver_ops = pmic_arb->ver_ops;
	u8 irq = hwirq_to_irq(d->hwirq);
	u16 apid = hwirq_to_apid(d->hwirq);
	u8 buf[2];

	ग_लिखोl_relaxed(SPMI_PIC_ACC_ENABLE_BIT,
			ver_ops->acc_enable(pmic_arb, apid));

	qpnpपूर्णांक_spmi_पढ़ो(d, QPNPINT_REG_EN_SET, &buf[0], 1);
	अगर (!(buf[0] & BIT(irq))) अणु
		/*
		 * Since the पूर्णांकerrupt is currently disabled, ग_लिखो to both the
		 * LATCHED_CLR and EN_SET रेजिस्टरs so that a spurious पूर्णांकerrupt
		 * cannot be triggered when the पूर्णांकerrupt is enabled
		 */
		buf[0] = BIT(irq);
		buf[1] = BIT(irq);
		qpnpपूर्णांक_spmi_ग_लिखो(d, QPNPINT_REG_LATCHED_CLR, &buf, 2);
	पूर्ण
पूर्ण

अटल पूर्णांक qpnpपूर्णांक_irq_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक flow_type)
अणु
	काष्ठा spmi_pmic_arb_qpnpपूर्णांक_type type;
	irq_flow_handler_t flow_handler;
	u8 irq = hwirq_to_irq(d->hwirq);

	qpnpपूर्णांक_spmi_पढ़ो(d, QPNPINT_REG_SET_TYPE, &type, माप(type));

	अगर (flow_type & (IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING)) अणु
		type.type |= BIT(irq);
		अगर (flow_type & IRQF_TRIGGER_RISING)
			type.polarity_high |= BIT(irq);
		अगर (flow_type & IRQF_TRIGGER_FALLING)
			type.polarity_low  |= BIT(irq);

		flow_handler = handle_edge_irq;
	पूर्ण अन्यथा अणु
		अगर ((flow_type & (IRQF_TRIGGER_HIGH)) &&
		    (flow_type & (IRQF_TRIGGER_LOW)))
			वापस -EINVAL;

		type.type &= ~BIT(irq); /* level trig */
		अगर (flow_type & IRQF_TRIGGER_HIGH)
			type.polarity_high |= BIT(irq);
		अन्यथा
			type.polarity_low  |= BIT(irq);

		flow_handler = handle_level_irq;
	पूर्ण

	qpnpपूर्णांक_spmi_ग_लिखो(d, QPNPINT_REG_SET_TYPE, &type, माप(type));
	irq_set_handler_locked(d, flow_handler);

	वापस 0;
पूर्ण

अटल पूर्णांक qpnpपूर्णांक_irq_set_wake(काष्ठा irq_data *d, अचिन्हित पूर्णांक on)
अणु
	काष्ठा spmi_pmic_arb *pmic_arb = irq_data_get_irq_chip_data(d);

	वापस irq_set_irq_wake(pmic_arb->irq, on);
पूर्ण

अटल पूर्णांक qpnpपूर्णांक_get_irqchip_state(काष्ठा irq_data *d,
				     क्रमागत irqchip_irq_state which,
				     bool *state)
अणु
	u8 irq = hwirq_to_irq(d->hwirq);
	u8 status = 0;

	अगर (which != IRQCHIP_STATE_LINE_LEVEL)
		वापस -EINVAL;

	qpnpपूर्णांक_spmi_पढ़ो(d, QPNPINT_REG_RT_STS, &status, 1);
	*state = !!(status & BIT(irq));

	वापस 0;
पूर्ण

अटल पूर्णांक qpnpपूर्णांक_irq_करोमुख्य_activate(काष्ठा irq_करोमुख्य *करोमुख्य,
				       काष्ठा irq_data *d, bool reserve)
अणु
	काष्ठा spmi_pmic_arb *pmic_arb = irq_data_get_irq_chip_data(d);
	u16 periph = hwirq_to_per(d->hwirq);
	u16 apid = hwirq_to_apid(d->hwirq);
	u16 sid = hwirq_to_sid(d->hwirq);
	u16 irq = hwirq_to_irq(d->hwirq);

	अगर (pmic_arb->apid_data[apid].irq_ee != pmic_arb->ee) अणु
		dev_err(&pmic_arb->spmic->dev, "failed to xlate sid = %#x, periph = %#x, irq = %u: ee=%u but owner=%u\n",
			sid, periph, irq, pmic_arb->ee,
			pmic_arb->apid_data[apid].irq_ee);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा irq_chip pmic_arb_irqchip = अणु
	.name		= "pmic_arb",
	.irq_ack	= qpnpपूर्णांक_irq_ack,
	.irq_mask	= qpnpपूर्णांक_irq_mask,
	.irq_unmask	= qpnpपूर्णांक_irq_unmask,
	.irq_set_type	= qpnpपूर्णांक_irq_set_type,
	.irq_set_wake	= qpnpपूर्णांक_irq_set_wake,
	.irq_get_irqchip_state	= qpnpपूर्णांक_get_irqchip_state,
	.flags		= IRQCHIP_MASK_ON_SUSPEND,
पूर्ण;

अटल पूर्णांक qpnpपूर्णांक_irq_करोमुख्य_translate(काष्ठा irq_करोमुख्य *d,
					काष्ठा irq_fwspec *fwspec,
					अचिन्हित दीर्घ *out_hwirq,
					अचिन्हित पूर्णांक *out_type)
अणु
	काष्ठा spmi_pmic_arb *pmic_arb = d->host_data;
	u32 *पूर्णांकspec = fwspec->param;
	u16 apid, ppid;
	पूर्णांक rc;

	dev_dbg(&pmic_arb->spmic->dev, "intspec[0] 0x%1x intspec[1] 0x%02x intspec[2] 0x%02x\n",
		पूर्णांकspec[0], पूर्णांकspec[1], पूर्णांकspec[2]);

	अगर (irq_करोमुख्य_get_of_node(d) != pmic_arb->spmic->dev.of_node)
		वापस -EINVAL;
	अगर (fwspec->param_count != 4)
		वापस -EINVAL;
	अगर (पूर्णांकspec[0] > 0xF || पूर्णांकspec[1] > 0xFF || पूर्णांकspec[2] > 0x7)
		वापस -EINVAL;

	ppid = पूर्णांकspec[0] << 8 | पूर्णांकspec[1];
	rc = pmic_arb->ver_ops->ppid_to_apid(pmic_arb, ppid);
	अगर (rc < 0) अणु
		dev_err(&pmic_arb->spmic->dev, "failed to xlate sid = %#x, periph = %#x, irq = %u rc = %d\n",
		पूर्णांकspec[0], पूर्णांकspec[1], पूर्णांकspec[2], rc);
		वापस rc;
	पूर्ण

	apid = rc;
	/* Keep track of अणुmax,minपूर्ण_apid क्रम bounding search during पूर्णांकerrupt */
	अगर (apid > pmic_arb->max_apid)
		pmic_arb->max_apid = apid;
	अगर (apid < pmic_arb->min_apid)
		pmic_arb->min_apid = apid;

	*out_hwirq = spec_to_hwirq(पूर्णांकspec[0], पूर्णांकspec[1], पूर्णांकspec[2], apid);
	*out_type  = पूर्णांकspec[3] & IRQ_TYPE_SENSE_MASK;

	dev_dbg(&pmic_arb->spmic->dev, "out_hwirq = %lu\n", *out_hwirq);

	वापस 0;
पूर्ण

अटल काष्ठा lock_class_key qpnpपूर्णांक_irq_lock_class, qpnpपूर्णांक_irq_request_class;

अटल व्योम qpnpपूर्णांक_irq_करोमुख्य_map(काष्ठा spmi_pmic_arb *pmic_arb,
				   काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
				   irq_hw_number_t hwirq, अचिन्हित पूर्णांक type)
अणु
	irq_flow_handler_t handler;

	dev_dbg(&pmic_arb->spmic->dev, "virq = %u, hwirq = %lu, type = %u\n",
		virq, hwirq, type);

	अगर (type & IRQ_TYPE_EDGE_BOTH)
		handler = handle_edge_irq;
	अन्यथा
		handler = handle_level_irq;


	irq_set_lockdep_class(virq, &qpnpपूर्णांक_irq_lock_class,
			      &qpnpपूर्णांक_irq_request_class);
	irq_करोमुख्य_set_info(करोमुख्य, virq, hwirq, &pmic_arb_irqchip, pmic_arb,
			    handler, शून्य, शून्य);
पूर्ण

अटल पूर्णांक qpnpपूर्णांक_irq_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य,
				    अचिन्हित पूर्णांक virq, अचिन्हित पूर्णांक nr_irqs,
				    व्योम *data)
अणु
	काष्ठा spmi_pmic_arb *pmic_arb = करोमुख्य->host_data;
	काष्ठा irq_fwspec *fwspec = data;
	irq_hw_number_t hwirq;
	अचिन्हित पूर्णांक type;
	पूर्णांक ret, i;

	ret = qpnpपूर्णांक_irq_करोमुख्य_translate(करोमुख्य, fwspec, &hwirq, &type);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < nr_irqs; i++)
		qpnpपूर्णांक_irq_करोमुख्य_map(pmic_arb, करोमुख्य, virq + i, hwirq + i,
				       type);

	वापस 0;
पूर्ण

अटल पूर्णांक pmic_arb_ppid_to_apid_v1(काष्ठा spmi_pmic_arb *pmic_arb, u16 ppid)
अणु
	u32 *mapping_table = pmic_arb->mapping_table;
	पूर्णांक index = 0, i;
	u16 apid_valid;
	u16 apid;
	u32 data;

	apid_valid = pmic_arb->ppid_to_apid[ppid];
	अगर (apid_valid & PMIC_ARB_APID_VALID) अणु
		apid = apid_valid & ~PMIC_ARB_APID_VALID;
		वापस apid;
	पूर्ण

	क्रम (i = 0; i < SPMI_MAPPING_TABLE_TREE_DEPTH; ++i) अणु
		अगर (!test_and_set_bit(index, pmic_arb->mapping_table_valid))
			mapping_table[index] = पढ़ोl_relaxed(pmic_arb->cnfg +
						SPMI_MAPPING_TABLE_REG(index));

		data = mapping_table[index];

		अगर (ppid & BIT(SPMI_MAPPING_BIT_INDEX(data))) अणु
			अगर (SPMI_MAPPING_BIT_IS_1_FLAG(data)) अणु
				index = SPMI_MAPPING_BIT_IS_1_RESULT(data);
			पूर्ण अन्यथा अणु
				apid = SPMI_MAPPING_BIT_IS_1_RESULT(data);
				pmic_arb->ppid_to_apid[ppid]
					= apid | PMIC_ARB_APID_VALID;
				pmic_arb->apid_data[apid].ppid = ppid;
				वापस apid;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (SPMI_MAPPING_BIT_IS_0_FLAG(data)) अणु
				index = SPMI_MAPPING_BIT_IS_0_RESULT(data);
			पूर्ण अन्यथा अणु
				apid = SPMI_MAPPING_BIT_IS_0_RESULT(data);
				pmic_arb->ppid_to_apid[ppid]
					= apid | PMIC_ARB_APID_VALID;
				pmic_arb->apid_data[apid].ppid = ppid;
				वापस apid;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस -ENODEV;
पूर्ण

/* v1 offset per ee */
अटल पूर्णांक pmic_arb_offset_v1(काष्ठा spmi_pmic_arb *pmic_arb, u8 sid, u16 addr,
			क्रमागत pmic_arb_channel ch_type)
अणु
	वापस 0x800 + 0x80 * pmic_arb->channel;
पूर्ण

अटल u16 pmic_arb_find_apid(काष्ठा spmi_pmic_arb *pmic_arb, u16 ppid)
अणु
	काष्ठा apid_data *apidd = &pmic_arb->apid_data[pmic_arb->last_apid];
	u32 regval, offset;
	u16 id, apid;

	क्रम (apid = pmic_arb->last_apid; ; apid++, apidd++) अणु
		offset = pmic_arb->ver_ops->apid_map_offset(apid);
		अगर (offset >= pmic_arb->core_size)
			अवरोध;

		regval = पढ़ोl_relaxed(pmic_arb->cnfg +
				      SPMI_OWNERSHIP_TABLE_REG(apid));
		apidd->irq_ee = SPMI_OWNERSHIP_PERIPH2OWNER(regval);
		apidd->ग_लिखो_ee = apidd->irq_ee;

		regval = पढ़ोl_relaxed(pmic_arb->core + offset);
		अगर (!regval)
			जारी;

		id = (regval >> 8) & PMIC_ARB_PPID_MASK;
		pmic_arb->ppid_to_apid[id] = apid | PMIC_ARB_APID_VALID;
		apidd->ppid = id;
		अगर (id == ppid) अणु
			apid |= PMIC_ARB_APID_VALID;
			अवरोध;
		पूर्ण
	पूर्ण
	pmic_arb->last_apid = apid & ~PMIC_ARB_APID_VALID;

	वापस apid;
पूर्ण

अटल पूर्णांक pmic_arb_ppid_to_apid_v2(काष्ठा spmi_pmic_arb *pmic_arb, u16 ppid)
अणु
	u16 apid_valid;

	apid_valid = pmic_arb->ppid_to_apid[ppid];
	अगर (!(apid_valid & PMIC_ARB_APID_VALID))
		apid_valid = pmic_arb_find_apid(pmic_arb, ppid);
	अगर (!(apid_valid & PMIC_ARB_APID_VALID))
		वापस -ENODEV;

	वापस apid_valid & ~PMIC_ARB_APID_VALID;
पूर्ण

अटल पूर्णांक pmic_arb_पढ़ो_apid_map_v5(काष्ठा spmi_pmic_arb *pmic_arb)
अणु
	काष्ठा apid_data *apidd = pmic_arb->apid_data;
	काष्ठा apid_data *prev_apidd;
	u16 i, apid, ppid;
	bool valid, is_irq_ee;
	u32 regval, offset;

	/*
	 * In order to allow multiple EEs to ग_लिखो to a single PPID in arbiter
	 * version 5, there is more than one APID mapped to each PPID.
	 * The owner field क्रम each of these mappings specअगरies the EE which is
	 * allowed to ग_लिखो to the APID.  The owner of the last (highest) APID
	 * क्रम a given PPID will receive पूर्णांकerrupts from the PPID.
	 */
	क्रम (i = 0; ; i++, apidd++) अणु
		offset = pmic_arb->ver_ops->apid_map_offset(i);
		अगर (offset >= pmic_arb->core_size)
			अवरोध;

		regval = पढ़ोl_relaxed(pmic_arb->core + offset);
		अगर (!regval)
			जारी;
		ppid = (regval >> 8) & PMIC_ARB_PPID_MASK;
		is_irq_ee = PMIC_ARB_CHAN_IS_IRQ_OWNER(regval);

		regval = पढ़ोl_relaxed(pmic_arb->cnfg +
				      SPMI_OWNERSHIP_TABLE_REG(i));
		apidd->ग_लिखो_ee = SPMI_OWNERSHIP_PERIPH2OWNER(regval);

		apidd->irq_ee = is_irq_ee ? apidd->ग_लिखो_ee : INVALID_EE;

		valid = pmic_arb->ppid_to_apid[ppid] & PMIC_ARB_APID_VALID;
		apid = pmic_arb->ppid_to_apid[ppid] & ~PMIC_ARB_APID_VALID;
		prev_apidd = &pmic_arb->apid_data[apid];

		अगर (valid && is_irq_ee &&
				prev_apidd->ग_लिखो_ee == pmic_arb->ee) अणु
			/*
			 * Duplicate PPID mapping after the one क्रम this EE;
			 * override the irq owner
			 */
			prev_apidd->irq_ee = apidd->irq_ee;
		पूर्ण अन्यथा अगर (!valid || is_irq_ee) अणु
			/* First PPID mapping or duplicate क्रम another EE */
			pmic_arb->ppid_to_apid[ppid] = i | PMIC_ARB_APID_VALID;
		पूर्ण

		apidd->ppid = ppid;
		pmic_arb->last_apid = i;
	पूर्ण

	/* Dump the mapping table क्रम debug purposes. */
	dev_dbg(&pmic_arb->spmic->dev, "PPID APID Write-EE IRQ-EE\n");
	क्रम (ppid = 0; ppid < PMIC_ARB_MAX_PPID; ppid++) अणु
		apid = pmic_arb->ppid_to_apid[ppid];
		अगर (apid & PMIC_ARB_APID_VALID) अणु
			apid &= ~PMIC_ARB_APID_VALID;
			apidd = &pmic_arb->apid_data[apid];
			dev_dbg(&pmic_arb->spmic->dev, "%#03X %3u %2u %2u\n",
			      ppid, apid, apidd->ग_लिखो_ee, apidd->irq_ee);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pmic_arb_ppid_to_apid_v5(काष्ठा spmi_pmic_arb *pmic_arb, u16 ppid)
अणु
	अगर (!(pmic_arb->ppid_to_apid[ppid] & PMIC_ARB_APID_VALID))
		वापस -ENODEV;

	वापस pmic_arb->ppid_to_apid[ppid] & ~PMIC_ARB_APID_VALID;
पूर्ण

/* v2 offset per ppid and per ee */
अटल पूर्णांक pmic_arb_offset_v2(काष्ठा spmi_pmic_arb *pmic_arb, u8 sid, u16 addr,
			   क्रमागत pmic_arb_channel ch_type)
अणु
	u16 apid;
	u16 ppid;
	पूर्णांक rc;

	ppid = sid << 8 | ((addr >> 8) & 0xFF);
	rc = pmic_arb_ppid_to_apid_v2(pmic_arb, ppid);
	अगर (rc < 0)
		वापस rc;

	apid = rc;
	वापस 0x1000 * pmic_arb->ee + 0x8000 * apid;
पूर्ण

/*
 * v5 offset per ee and per apid क्रम observer channels and per apid क्रम
 * पढ़ो/ग_लिखो channels.
 */
अटल पूर्णांक pmic_arb_offset_v5(काष्ठा spmi_pmic_arb *pmic_arb, u8 sid, u16 addr,
			   क्रमागत pmic_arb_channel ch_type)
अणु
	u16 apid;
	पूर्णांक rc;
	u32 offset = 0;
	u16 ppid = (sid << 8) | (addr >> 8);

	rc = pmic_arb_ppid_to_apid_v5(pmic_arb, ppid);
	अगर (rc < 0)
		वापस rc;

	apid = rc;
	चयन (ch_type) अणु
	हाल PMIC_ARB_CHANNEL_OBS:
		offset = 0x10000 * pmic_arb->ee + 0x80 * apid;
		अवरोध;
	हाल PMIC_ARB_CHANNEL_RW:
		offset = 0x10000 * apid;
		अवरोध;
	पूर्ण

	वापस offset;
पूर्ण

अटल u32 pmic_arb_fmt_cmd_v1(u8 opc, u8 sid, u16 addr, u8 bc)
अणु
	वापस (opc << 27) | ((sid & 0xf) << 20) | (addr << 4) | (bc & 0x7);
पूर्ण

अटल u32 pmic_arb_fmt_cmd_v2(u8 opc, u8 sid, u16 addr, u8 bc)
अणु
	वापस (opc << 27) | ((addr & 0xff) << 4) | (bc & 0x7);
पूर्ण

अटल व्योम __iomem *
pmic_arb_owner_acc_status_v1(काष्ठा spmi_pmic_arb *pmic_arb, u8 m, u16 n)
अणु
	वापस pmic_arb->पूर्णांकr + 0x20 * m + 0x4 * n;
पूर्ण

अटल व्योम __iomem *
pmic_arb_owner_acc_status_v2(काष्ठा spmi_pmic_arb *pmic_arb, u8 m, u16 n)
अणु
	वापस pmic_arb->पूर्णांकr + 0x100000 + 0x1000 * m + 0x4 * n;
पूर्ण

अटल व्योम __iomem *
pmic_arb_owner_acc_status_v3(काष्ठा spmi_pmic_arb *pmic_arb, u8 m, u16 n)
अणु
	वापस pmic_arb->पूर्णांकr + 0x200000 + 0x1000 * m + 0x4 * n;
पूर्ण

अटल व्योम __iomem *
pmic_arb_owner_acc_status_v5(काष्ठा spmi_pmic_arb *pmic_arb, u8 m, u16 n)
अणु
	वापस pmic_arb->पूर्णांकr + 0x10000 * m + 0x4 * n;
पूर्ण

अटल व्योम __iomem *
pmic_arb_acc_enable_v1(काष्ठा spmi_pmic_arb *pmic_arb, u16 n)
अणु
	वापस pmic_arb->पूर्णांकr + 0x200 + 0x4 * n;
पूर्ण

अटल व्योम __iomem *
pmic_arb_acc_enable_v2(काष्ठा spmi_pmic_arb *pmic_arb, u16 n)
अणु
	वापस pmic_arb->पूर्णांकr + 0x1000 * n;
पूर्ण

अटल व्योम __iomem *
pmic_arb_acc_enable_v5(काष्ठा spmi_pmic_arb *pmic_arb, u16 n)
अणु
	वापस pmic_arb->wr_base + 0x100 + 0x10000 * n;
पूर्ण

अटल व्योम __iomem *
pmic_arb_irq_status_v1(काष्ठा spmi_pmic_arb *pmic_arb, u16 n)
अणु
	वापस pmic_arb->पूर्णांकr + 0x600 + 0x4 * n;
पूर्ण

अटल व्योम __iomem *
pmic_arb_irq_status_v2(काष्ठा spmi_pmic_arb *pmic_arb, u16 n)
अणु
	वापस pmic_arb->पूर्णांकr + 0x4 + 0x1000 * n;
पूर्ण

अटल व्योम __iomem *
pmic_arb_irq_status_v5(काष्ठा spmi_pmic_arb *pmic_arb, u16 n)
अणु
	वापस pmic_arb->wr_base + 0x104 + 0x10000 * n;
पूर्ण

अटल व्योम __iomem *
pmic_arb_irq_clear_v1(काष्ठा spmi_pmic_arb *pmic_arb, u16 n)
अणु
	वापस pmic_arb->पूर्णांकr + 0xA00 + 0x4 * n;
पूर्ण

अटल व्योम __iomem *
pmic_arb_irq_clear_v2(काष्ठा spmi_pmic_arb *pmic_arb, u16 n)
अणु
	वापस pmic_arb->पूर्णांकr + 0x8 + 0x1000 * n;
पूर्ण

अटल व्योम __iomem *
pmic_arb_irq_clear_v5(काष्ठा spmi_pmic_arb *pmic_arb, u16 n)
अणु
	वापस pmic_arb->wr_base + 0x108 + 0x10000 * n;
पूर्ण

अटल u32 pmic_arb_apid_map_offset_v2(u16 n)
अणु
	वापस 0x800 + 0x4 * n;
पूर्ण

अटल u32 pmic_arb_apid_map_offset_v5(u16 n)
अणु
	वापस 0x900 + 0x4 * n;
पूर्ण

अटल स्थिर काष्ठा pmic_arb_ver_ops pmic_arb_v1 = अणु
	.ver_str		= "v1",
	.ppid_to_apid		= pmic_arb_ppid_to_apid_v1,
	.non_data_cmd		= pmic_arb_non_data_cmd_v1,
	.offset			= pmic_arb_offset_v1,
	.fmt_cmd		= pmic_arb_fmt_cmd_v1,
	.owner_acc_status	= pmic_arb_owner_acc_status_v1,
	.acc_enable		= pmic_arb_acc_enable_v1,
	.irq_status		= pmic_arb_irq_status_v1,
	.irq_clear		= pmic_arb_irq_clear_v1,
	.apid_map_offset	= pmic_arb_apid_map_offset_v2,
पूर्ण;

अटल स्थिर काष्ठा pmic_arb_ver_ops pmic_arb_v2 = अणु
	.ver_str		= "v2",
	.ppid_to_apid		= pmic_arb_ppid_to_apid_v2,
	.non_data_cmd		= pmic_arb_non_data_cmd_v2,
	.offset			= pmic_arb_offset_v2,
	.fmt_cmd		= pmic_arb_fmt_cmd_v2,
	.owner_acc_status	= pmic_arb_owner_acc_status_v2,
	.acc_enable		= pmic_arb_acc_enable_v2,
	.irq_status		= pmic_arb_irq_status_v2,
	.irq_clear		= pmic_arb_irq_clear_v2,
	.apid_map_offset	= pmic_arb_apid_map_offset_v2,
पूर्ण;

अटल स्थिर काष्ठा pmic_arb_ver_ops pmic_arb_v3 = अणु
	.ver_str		= "v3",
	.ppid_to_apid		= pmic_arb_ppid_to_apid_v2,
	.non_data_cmd		= pmic_arb_non_data_cmd_v2,
	.offset			= pmic_arb_offset_v2,
	.fmt_cmd		= pmic_arb_fmt_cmd_v2,
	.owner_acc_status	= pmic_arb_owner_acc_status_v3,
	.acc_enable		= pmic_arb_acc_enable_v2,
	.irq_status		= pmic_arb_irq_status_v2,
	.irq_clear		= pmic_arb_irq_clear_v2,
	.apid_map_offset	= pmic_arb_apid_map_offset_v2,
पूर्ण;

अटल स्थिर काष्ठा pmic_arb_ver_ops pmic_arb_v5 = अणु
	.ver_str		= "v5",
	.ppid_to_apid		= pmic_arb_ppid_to_apid_v5,
	.non_data_cmd		= pmic_arb_non_data_cmd_v2,
	.offset			= pmic_arb_offset_v5,
	.fmt_cmd		= pmic_arb_fmt_cmd_v2,
	.owner_acc_status	= pmic_arb_owner_acc_status_v5,
	.acc_enable		= pmic_arb_acc_enable_v5,
	.irq_status		= pmic_arb_irq_status_v5,
	.irq_clear		= pmic_arb_irq_clear_v5,
	.apid_map_offset	= pmic_arb_apid_map_offset_v5,
पूर्ण;

अटल स्थिर काष्ठा irq_करोमुख्य_ops pmic_arb_irq_करोमुख्य_ops = अणु
	.activate = qpnpपूर्णांक_irq_करोमुख्य_activate,
	.alloc = qpnpपूर्णांक_irq_करोमुख्य_alloc,
	.मुक्त = irq_करोमुख्य_मुक्त_irqs_common,
	.translate = qpnpपूर्णांक_irq_करोमुख्य_translate,
पूर्ण;

अटल पूर्णांक spmi_pmic_arb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spmi_pmic_arb *pmic_arb;
	काष्ठा spmi_controller *ctrl;
	काष्ठा resource *res;
	व्योम __iomem *core;
	u32 *mapping_table;
	u32 channel, ee, hw_ver;
	पूर्णांक err;

	ctrl = spmi_controller_alloc(&pdev->dev, माप(*pmic_arb));
	अगर (!ctrl)
		वापस -ENOMEM;

	pmic_arb = spmi_controller_get_drvdata(ctrl);
	pmic_arb->spmic = ctrl;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "core");
	core = devm_ioremap_resource(&ctrl->dev, res);
	अगर (IS_ERR(core)) अणु
		err = PTR_ERR(core);
		जाओ err_put_ctrl;
	पूर्ण

	pmic_arb->core_size = resource_size(res);

	pmic_arb->ppid_to_apid = devm_kसुस्मृति(&ctrl->dev, PMIC_ARB_MAX_PPID,
					      माप(*pmic_arb->ppid_to_apid),
					      GFP_KERNEL);
	अगर (!pmic_arb->ppid_to_apid) अणु
		err = -ENOMEM;
		जाओ err_put_ctrl;
	पूर्ण

	hw_ver = पढ़ोl_relaxed(core + PMIC_ARB_VERSION);

	अगर (hw_ver < PMIC_ARB_VERSION_V2_MIN) अणु
		pmic_arb->ver_ops = &pmic_arb_v1;
		pmic_arb->wr_base = core;
		pmic_arb->rd_base = core;
	पूर्ण अन्यथा अणु
		pmic_arb->core = core;

		अगर (hw_ver < PMIC_ARB_VERSION_V3_MIN)
			pmic_arb->ver_ops = &pmic_arb_v2;
		अन्यथा अगर (hw_ver < PMIC_ARB_VERSION_V5_MIN)
			pmic_arb->ver_ops = &pmic_arb_v3;
		अन्यथा
			pmic_arb->ver_ops = &pmic_arb_v5;

		res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM,
						   "obsrvr");
		pmic_arb->rd_base = devm_ioremap_resource(&ctrl->dev, res);
		अगर (IS_ERR(pmic_arb->rd_base)) अणु
			err = PTR_ERR(pmic_arb->rd_base);
			जाओ err_put_ctrl;
		पूर्ण

		res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM,
						   "chnls");
		pmic_arb->wr_base = devm_ioremap_resource(&ctrl->dev, res);
		अगर (IS_ERR(pmic_arb->wr_base)) अणु
			err = PTR_ERR(pmic_arb->wr_base);
			जाओ err_put_ctrl;
		पूर्ण
	पूर्ण

	dev_info(&ctrl->dev, "PMIC arbiter version %s (0x%x)\n",
		 pmic_arb->ver_ops->ver_str, hw_ver);

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "intr");
	pmic_arb->पूर्णांकr = devm_ioremap_resource(&ctrl->dev, res);
	अगर (IS_ERR(pmic_arb->पूर्णांकr)) अणु
		err = PTR_ERR(pmic_arb->पूर्णांकr);
		जाओ err_put_ctrl;
	पूर्ण

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "cnfg");
	pmic_arb->cnfg = devm_ioremap_resource(&ctrl->dev, res);
	अगर (IS_ERR(pmic_arb->cnfg)) अणु
		err = PTR_ERR(pmic_arb->cnfg);
		जाओ err_put_ctrl;
	पूर्ण

	pmic_arb->irq = platक्रमm_get_irq_byname(pdev, "periph_irq");
	अगर (pmic_arb->irq < 0) अणु
		err = pmic_arb->irq;
		जाओ err_put_ctrl;
	पूर्ण

	err = of_property_पढ़ो_u32(pdev->dev.of_node, "qcom,channel", &channel);
	अगर (err) अणु
		dev_err(&pdev->dev, "channel unspecified.\n");
		जाओ err_put_ctrl;
	पूर्ण

	अगर (channel > 5) अणु
		dev_err(&pdev->dev, "invalid channel (%u) specified.\n",
			channel);
		err = -EINVAL;
		जाओ err_put_ctrl;
	पूर्ण

	pmic_arb->channel = channel;

	err = of_property_पढ़ो_u32(pdev->dev.of_node, "qcom,ee", &ee);
	अगर (err) अणु
		dev_err(&pdev->dev, "EE unspecified.\n");
		जाओ err_put_ctrl;
	पूर्ण

	अगर (ee > 5) अणु
		dev_err(&pdev->dev, "invalid EE (%u) specified\n", ee);
		err = -EINVAL;
		जाओ err_put_ctrl;
	पूर्ण

	pmic_arb->ee = ee;
	mapping_table = devm_kसुस्मृति(&ctrl->dev, PMIC_ARB_MAX_PERIPHS,
					माप(*mapping_table), GFP_KERNEL);
	अगर (!mapping_table) अणु
		err = -ENOMEM;
		जाओ err_put_ctrl;
	पूर्ण

	pmic_arb->mapping_table = mapping_table;
	/* Initialize max_apid/min_apid to the opposite bounds, during
	 * the irq करोमुख्य translation, we are sure to update these */
	pmic_arb->max_apid = 0;
	pmic_arb->min_apid = PMIC_ARB_MAX_PERIPHS - 1;

	platक्रमm_set_drvdata(pdev, ctrl);
	raw_spin_lock_init(&pmic_arb->lock);

	ctrl->cmd = pmic_arb_cmd;
	ctrl->पढ़ो_cmd = pmic_arb_पढ़ो_cmd;
	ctrl->ग_लिखो_cmd = pmic_arb_ग_लिखो_cmd;

	अगर (hw_ver >= PMIC_ARB_VERSION_V5_MIN) अणु
		err = pmic_arb_पढ़ो_apid_map_v5(pmic_arb);
		अगर (err) अणु
			dev_err(&pdev->dev, "could not read APID->PPID mapping table, rc= %d\n",
				err);
			जाओ err_put_ctrl;
		पूर्ण
	पूर्ण

	dev_dbg(&pdev->dev, "adding irq domain\n");
	pmic_arb->करोमुख्य = irq_करोमुख्य_add_tree(pdev->dev.of_node,
					 &pmic_arb_irq_करोमुख्य_ops, pmic_arb);
	अगर (!pmic_arb->करोमुख्य) अणु
		dev_err(&pdev->dev, "unable to create irq_domain\n");
		err = -ENOMEM;
		जाओ err_put_ctrl;
	पूर्ण

	irq_set_chained_handler_and_data(pmic_arb->irq, pmic_arb_chained_irq,
					pmic_arb);
	err = spmi_controller_add(ctrl);
	अगर (err)
		जाओ err_करोमुख्य_हटाओ;

	वापस 0;

err_करोमुख्य_हटाओ:
	irq_set_chained_handler_and_data(pmic_arb->irq, शून्य, शून्य);
	irq_करोमुख्य_हटाओ(pmic_arb->करोमुख्य);
err_put_ctrl:
	spmi_controller_put(ctrl);
	वापस err;
पूर्ण

अटल पूर्णांक spmi_pmic_arb_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spmi_controller *ctrl = platक्रमm_get_drvdata(pdev);
	काष्ठा spmi_pmic_arb *pmic_arb = spmi_controller_get_drvdata(ctrl);
	spmi_controller_हटाओ(ctrl);
	irq_set_chained_handler_and_data(pmic_arb->irq, शून्य, शून्य);
	irq_करोमुख्य_हटाओ(pmic_arb->करोमुख्य);
	spmi_controller_put(ctrl);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id spmi_pmic_arb_match_table[] = अणु
	अणु .compatible = "qcom,spmi-pmic-arb", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, spmi_pmic_arb_match_table);

अटल काष्ठा platक्रमm_driver spmi_pmic_arb_driver = अणु
	.probe		= spmi_pmic_arb_probe,
	.हटाओ		= spmi_pmic_arb_हटाओ,
	.driver		= अणु
		.name	= "spmi_pmic_arb",
		.of_match_table = spmi_pmic_arb_match_table,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(spmi_pmic_arb_driver);

MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:spmi_pmic_arb");
