<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Lightning Mountain centralized DMA controller driver
 *
 * Copyright (c) 2016 - 2020 Intel Corporation.
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/err.h>
#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/of_dma.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset.h>

#समावेश "../dmaengine.h"
#समावेश "../virt-dma.h"

#घोषणा DRIVER_NAME			"lgm-dma"

#घोषणा DMA_ID				0x0008
#घोषणा DMA_ID_REV			GENMASK(7, 0)
#घोषणा DMA_ID_PNR			GENMASK(19, 16)
#घोषणा DMA_ID_CHNR			GENMASK(26, 20)
#घोषणा DMA_ID_DW_128B			BIT(27)
#घोषणा DMA_ID_AW_36B			BIT(28)
#घोषणा DMA_VER32			0x32
#घोषणा DMA_VER31			0x31
#घोषणा DMA_VER22			0x0A

#घोषणा DMA_CTRL			0x0010
#घोषणा DMA_CTRL_RST			BIT(0)
#घोषणा DMA_CTRL_DSRAM_PATH		BIT(1)
#घोषणा DMA_CTRL_DBURST_WR		BIT(3)
#घोषणा DMA_CTRL_VLD_DF_ACK		BIT(4)
#घोषणा DMA_CTRL_CH_FL			BIT(6)
#घोषणा DMA_CTRL_DS_FOD			BIT(7)
#घोषणा DMA_CTRL_DRB			BIT(8)
#घोषणा DMA_CTRL_ENBE			BIT(9)
#घोषणा DMA_CTRL_DESC_TMOUT_CNT_V31	GENMASK(27, 16)
#घोषणा DMA_CTRL_DESC_TMOUT_EN_V31	BIT(30)
#घोषणा DMA_CTRL_PKTARB			BIT(31)

#घोषणा DMA_CPOLL			0x0014
#घोषणा DMA_CPOLL_CNT			GENMASK(15, 4)
#घोषणा DMA_CPOLL_EN			BIT(31)

#घोषणा DMA_CS				0x0018
#घोषणा DMA_CS_MASK			GENMASK(5, 0)

#घोषणा DMA_CCTRL			0x001C
#घोषणा DMA_CCTRL_ON			BIT(0)
#घोषणा DMA_CCTRL_RST			BIT(1)
#घोषणा DMA_CCTRL_CH_POLL_EN		BIT(2)
#घोषणा DMA_CCTRL_CH_ABC		BIT(3) /* Adaptive Burst Chop */
#घोषणा DMA_CDBA_MSB			GENMASK(7, 4)
#घोषणा DMA_CCTRL_सूची_TX		BIT(8)
#घोषणा DMA_CCTRL_CLASS			GENMASK(11, 9)
#घोषणा DMA_CCTRL_CLASSH		GENMASK(19, 18)
#घोषणा DMA_CCTRL_WR_NP_EN		BIT(21)
#घोषणा DMA_CCTRL_PDEN			BIT(23)
#घोषणा DMA_MAX_CLASS			(SZ_32 - 1)

#घोषणा DMA_CDBA			0x0020
#घोषणा DMA_CDLEN			0x0024
#घोषणा DMA_CIS				0x0028
#घोषणा DMA_CIE				0x002C
#घोषणा DMA_CI_EOP			BIT(1)
#घोषणा DMA_CI_DUR			BIT(2)
#घोषणा DMA_CI_DESCPT			BIT(3)
#घोषणा DMA_CI_CHOFF			BIT(4)
#घोषणा DMA_CI_RDERR			BIT(5)
#घोषणा DMA_CI_ALL							\
	(DMA_CI_EOP | DMA_CI_DUR | DMA_CI_DESCPT | DMA_CI_CHOFF | DMA_CI_RDERR)

#घोषणा DMA_PS				0x0040
#घोषणा DMA_PCTRL			0x0044
#घोषणा DMA_PCTRL_RXBL16		BIT(0)
#घोषणा DMA_PCTRL_TXBL16		BIT(1)
#घोषणा DMA_PCTRL_RXBL			GENMASK(3, 2)
#घोषणा DMA_PCTRL_RXBL_8		3
#घोषणा DMA_PCTRL_TXBL			GENMASK(5, 4)
#घोषणा DMA_PCTRL_TXBL_8		3
#घोषणा DMA_PCTRL_PDEN			BIT(6)
#घोषणा DMA_PCTRL_RXBL32		BIT(7)
#घोषणा DMA_PCTRL_RXENDI		GENMASK(9, 8)
#घोषणा DMA_PCTRL_TXENDI		GENMASK(11, 10)
#घोषणा DMA_PCTRL_TXBL32		BIT(15)
#घोषणा DMA_PCTRL_MEM_FLUSH		BIT(16)

#घोषणा DMA_IRNEN1			0x00E8
#घोषणा DMA_IRNCR1			0x00EC
#घोषणा DMA_IRNEN			0x00F4
#घोषणा DMA_IRNCR			0x00F8
#घोषणा DMA_C_DP_TICK			0x100
#घोषणा DMA_C_DP_TICK_TIKNARB		GENMASK(15, 0)
#घोषणा DMA_C_DP_TICK_TIKARB		GENMASK(31, 16)

#घोषणा DMA_C_HDRM			0x110
/*
 * If header mode is set in DMA descriptor,
 *   If bit 30 is disabled, HDR_LEN must be configured according to channel
 *     requirement.
 *   If bit 30 is enabled(checksum with heade mode), HDR_LEN has no need to
 *     be configured. It will enable check sum क्रम चयन
 * If header mode is not set in DMA descriptor,
 *   This रेजिस्टर setting करोesn't matter
 */
#घोषणा DMA_C_HDRM_HDR_SUM		BIT(30)

#घोषणा DMA_C_BOFF			0x120
#घोषणा DMA_C_BOFF_BOF_LEN		GENMASK(7, 0)
#घोषणा DMA_C_BOFF_EN			BIT(31)

#घोषणा DMA_ORRC			0x190
#घोषणा DMA_ORRC_ORRCNT			GENMASK(8, 4)
#घोषणा DMA_ORRC_EN			BIT(31)

#घोषणा DMA_C_ENDIAN			0x200
#घोषणा DMA_C_END_DATAENDI		GENMASK(1, 0)
#घोषणा DMA_C_END_DE_EN			BIT(7)
#घोषणा DMA_C_END_DESENDI		GENMASK(9, 8)
#घोषणा DMA_C_END_DES_EN		BIT(16)

/* DMA controller capability */
#घोषणा DMA_ADDR_36BIT			BIT(0)
#घोषणा DMA_DATA_128BIT			BIT(1)
#घोषणा DMA_CHAN_FLOW_CTL		BIT(2)
#घोषणा DMA_DESC_FOD			BIT(3)
#घोषणा DMA_DESC_IN_SRAM		BIT(4)
#घोषणा DMA_EN_BYTE_EN			BIT(5)
#घोषणा DMA_DBURST_WR			BIT(6)
#घोषणा DMA_VALID_DESC_FETCH_ACK	BIT(7)
#घोषणा DMA_DFT_DRB			BIT(8)

#घोषणा DMA_ORRC_MAX_CNT		(SZ_32 - 1)
#घोषणा DMA_DFT_POLL_CNT		SZ_4
#घोषणा DMA_DFT_BURST_V22		SZ_2
#घोषणा DMA_BURSTL_8DW			SZ_8
#घोषणा DMA_BURSTL_16DW			SZ_16
#घोषणा DMA_BURSTL_32DW			SZ_32
#घोषणा DMA_DFT_BURST			DMA_BURSTL_16DW
#घोषणा DMA_MAX_DESC_NUM		(SZ_8K - 1)
#घोषणा DMA_CHAN_BOFF_MAX		(SZ_256 - 1)
#घोषणा DMA_DFT_ENDIAN			0

#घोषणा DMA_DFT_DESC_TCNT		50
#घोषणा DMA_HDR_LEN_MAX			(SZ_16K - 1)

/* DMA flags */
#घोषणा DMA_TX_CH			BIT(0)
#घोषणा DMA_RX_CH			BIT(1)
#घोषणा DEVICE_ALLOC_DESC		BIT(2)
#घोषणा CHAN_IN_USE			BIT(3)
#घोषणा DMA_HW_DESC			BIT(4)

/* Descriptor fields */
#घोषणा DESC_DATA_LEN			GENMASK(15, 0)
#घोषणा DESC_BYTE_OFF			GENMASK(25, 23)
#घोषणा DESC_EOP			BIT(28)
#घोषणा DESC_SOP			BIT(29)
#घोषणा DESC_C				BIT(30)
#घोषणा DESC_OWN			BIT(31)

#घोषणा DMA_CHAN_RST			1
#घोषणा DMA_MAX_SIZE			(BIT(16) - 1)
#घोषणा MAX_LOWER_CHANS			32
#घोषणा MASK_LOWER_CHANS		GENMASK(4, 0)
#घोषणा DMA_OWN				1
#घोषणा HIGH_4_BITS			GENMASK(3, 0)
#घोषणा DMA_DFT_DESC_NUM		1
#घोषणा DMA_PKT_DROP_DIS		0

क्रमागत ldma_chan_on_off अणु
	DMA_CH_OFF = 0,
	DMA_CH_ON = 1,
पूर्ण;

क्रमागत अणु
	DMA_TYPE_TX = 0,
	DMA_TYPE_RX,
	DMA_TYPE_MCPY,
पूर्ण;

काष्ठा ldma_dev;
काष्ठा ldma_port;

काष्ठा ldma_chan अणु
	काष्ठा virt_dma_chan	vchan;
	काष्ठा ldma_port	*port; /* back poपूर्णांकer */
	अक्षर			name[8]; /* Channel name */
	पूर्णांक			nr; /* Channel id in hardware */
	u32			flags; /* central way or channel based way */
	क्रमागत ldma_chan_on_off	onoff;
	dma_addr_t		desc_phys;
	व्योम			*desc_base; /* Virtual address */
	u32			desc_cnt; /* Number of descriptors */
	पूर्णांक			rst;
	u32			hdrm_len;
	bool			hdrm_csum;
	u32			boff_len;
	u32			data_endian;
	u32			desc_endian;
	bool			pden;
	bool			desc_rx_np;
	bool			data_endian_en;
	bool			desc_endian_en;
	bool			abc_en;
	bool			desc_init;
	काष्ठा dma_pool		*desc_pool; /* Descriptors pool */
	u32			desc_num;
	काष्ठा dw2_desc_sw	*ds;
	काष्ठा work_काष्ठा	work;
	काष्ठा dma_slave_config config;
पूर्ण;

काष्ठा ldma_port अणु
	काष्ठा ldma_dev		*ldev; /* back poपूर्णांकer */
	u32			portid;
	u32			rxbl;
	u32			txbl;
	u32			rxendi;
	u32			txendi;
	u32			pkt_drop;
पूर्ण;

/* Instance specअगरic data */
काष्ठा ldma_inst_data अणु
	bool			desc_in_sram;
	bool			chan_fc;
	bool			desc_fod; /* Fetch On Demand */
	bool			valid_desc_fetch_ack;
	u32			orrc; /* Outstanding पढ़ो count */
	स्थिर अक्षर		*name;
	u32			type;
पूर्ण;

काष्ठा ldma_dev अणु
	काष्ठा device		*dev;
	व्योम __iomem		*base;
	काष्ठा reset_control	*rst;
	काष्ठा clk		*core_clk;
	काष्ठा dma_device	dma_dev;
	u32			ver;
	पूर्णांक			irq;
	काष्ठा ldma_port	*ports;
	काष्ठा ldma_chan	*chans; /* channel list on this DMA or port */
	spinlock_t		dev_lock; /* Controller रेजिस्टर exclusive */
	u32			chan_nrs;
	u32			port_nrs;
	u32			channels_mask;
	u32			flags;
	u32			pollcnt;
	स्थिर काष्ठा ldma_inst_data *inst;
	काष्ठा workqueue_काष्ठा	*wq;
पूर्ण;

काष्ठा dw2_desc अणु
	u32 field;
	u32 addr;
पूर्ण __packed __aligned(8);

काष्ठा dw2_desc_sw अणु
	काष्ठा virt_dma_desc	vdesc;
	काष्ठा ldma_chan	*chan;
	dma_addr_t		desc_phys;
	माप_प्रकार			desc_cnt;
	माप_प्रकार			size;
	काष्ठा dw2_desc		*desc_hw;
पूर्ण;

अटल अंतरभूत व्योम
ldma_update_bits(काष्ठा ldma_dev *d, u32 mask, u32 val, u32 ofs)
अणु
	u32 old_val, new_val;

	old_val = पढ़ोl(d->base +  ofs);
	new_val = (old_val & ~mask) | (val & mask);

	अगर (new_val != old_val)
		ग_लिखोl(new_val, d->base + ofs);
पूर्ण

अटल अंतरभूत काष्ठा ldma_chan *to_ldma_chan(काष्ठा dma_chan *chan)
अणु
	वापस container_of(chan, काष्ठा ldma_chan, vchan.chan);
पूर्ण

अटल अंतरभूत काष्ठा ldma_dev *to_ldma_dev(काष्ठा dma_device *dma_dev)
अणु
	वापस container_of(dma_dev, काष्ठा ldma_dev, dma_dev);
पूर्ण

अटल अंतरभूत काष्ठा dw2_desc_sw *to_lgm_dma_desc(काष्ठा virt_dma_desc *vdesc)
अणु
	वापस container_of(vdesc, काष्ठा dw2_desc_sw, vdesc);
पूर्ण

अटल अंतरभूत bool ldma_chan_tx(काष्ठा ldma_chan *c)
अणु
	वापस !!(c->flags & DMA_TX_CH);
पूर्ण

अटल अंतरभूत bool ldma_chan_is_hw_desc(काष्ठा ldma_chan *c)
अणु
	वापस !!(c->flags & DMA_HW_DESC);
पूर्ण

अटल व्योम ldma_dev_reset(काष्ठा ldma_dev *d)

अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&d->dev_lock, flags);
	ldma_update_bits(d, DMA_CTRL_RST, DMA_CTRL_RST, DMA_CTRL);
	spin_unlock_irqrestore(&d->dev_lock, flags);
पूर्ण

अटल व्योम ldma_dev_pkt_arb_cfg(काष्ठा ldma_dev *d, bool enable)
अणु
	अचिन्हित दीर्घ flags;
	u32 mask = DMA_CTRL_PKTARB;
	u32 val = enable ? DMA_CTRL_PKTARB : 0;

	spin_lock_irqsave(&d->dev_lock, flags);
	ldma_update_bits(d, mask, val, DMA_CTRL);
	spin_unlock_irqrestore(&d->dev_lock, flags);
पूर्ण

अटल व्योम ldma_dev_sram_desc_cfg(काष्ठा ldma_dev *d, bool enable)
अणु
	अचिन्हित दीर्घ flags;
	u32 mask = DMA_CTRL_DSRAM_PATH;
	u32 val = enable ? DMA_CTRL_DSRAM_PATH : 0;

	spin_lock_irqsave(&d->dev_lock, flags);
	ldma_update_bits(d, mask, val, DMA_CTRL);
	spin_unlock_irqrestore(&d->dev_lock, flags);
पूर्ण

अटल व्योम ldma_dev_chan_flow_ctl_cfg(काष्ठा ldma_dev *d, bool enable)
अणु
	अचिन्हित दीर्घ flags;
	u32 mask, val;

	अगर (d->inst->type != DMA_TYPE_TX)
		वापस;

	mask = DMA_CTRL_CH_FL;
	val = enable ? DMA_CTRL_CH_FL : 0;

	spin_lock_irqsave(&d->dev_lock, flags);
	ldma_update_bits(d, mask, val, DMA_CTRL);
	spin_unlock_irqrestore(&d->dev_lock, flags);
पूर्ण

अटल व्योम ldma_dev_global_polling_enable(काष्ठा ldma_dev *d)
अणु
	अचिन्हित दीर्घ flags;
	u32 mask = DMA_CPOLL_EN | DMA_CPOLL_CNT;
	u32 val = DMA_CPOLL_EN;

	val |= FIELD_PREP(DMA_CPOLL_CNT, d->pollcnt);

	spin_lock_irqsave(&d->dev_lock, flags);
	ldma_update_bits(d, mask, val, DMA_CPOLL);
	spin_unlock_irqrestore(&d->dev_lock, flags);
पूर्ण

अटल व्योम ldma_dev_desc_fetch_on_demand_cfg(काष्ठा ldma_dev *d, bool enable)
अणु
	अचिन्हित दीर्घ flags;
	u32 mask, val;

	अगर (d->inst->type == DMA_TYPE_MCPY)
		वापस;

	mask = DMA_CTRL_DS_FOD;
	val = enable ? DMA_CTRL_DS_FOD : 0;

	spin_lock_irqsave(&d->dev_lock, flags);
	ldma_update_bits(d, mask, val, DMA_CTRL);
	spin_unlock_irqrestore(&d->dev_lock, flags);
पूर्ण

अटल व्योम ldma_dev_byte_enable_cfg(काष्ठा ldma_dev *d, bool enable)
अणु
	अचिन्हित दीर्घ flags;
	u32 mask = DMA_CTRL_ENBE;
	u32 val = enable ? DMA_CTRL_ENBE : 0;

	spin_lock_irqsave(&d->dev_lock, flags);
	ldma_update_bits(d, mask, val, DMA_CTRL);
	spin_unlock_irqrestore(&d->dev_lock, flags);
पूर्ण

अटल व्योम ldma_dev_orrc_cfg(काष्ठा ldma_dev *d)
अणु
	अचिन्हित दीर्घ flags;
	u32 val = 0;
	u32 mask;

	अगर (d->inst->type == DMA_TYPE_RX)
		वापस;

	mask = DMA_ORRC_EN | DMA_ORRC_ORRCNT;
	अगर (d->inst->orrc > 0 && d->inst->orrc <= DMA_ORRC_MAX_CNT)
		val = DMA_ORRC_EN | FIELD_PREP(DMA_ORRC_ORRCNT, d->inst->orrc);

	spin_lock_irqsave(&d->dev_lock, flags);
	ldma_update_bits(d, mask, val, DMA_ORRC);
	spin_unlock_irqrestore(&d->dev_lock, flags);
पूर्ण

अटल व्योम ldma_dev_df_tout_cfg(काष्ठा ldma_dev *d, bool enable, पूर्णांक tcnt)
अणु
	u32 mask = DMA_CTRL_DESC_TMOUT_CNT_V31;
	अचिन्हित दीर्घ flags;
	u32 val;

	अगर (enable)
		val = DMA_CTRL_DESC_TMOUT_EN_V31 | FIELD_PREP(DMA_CTRL_DESC_TMOUT_CNT_V31, tcnt);
	अन्यथा
		val = 0;

	spin_lock_irqsave(&d->dev_lock, flags);
	ldma_update_bits(d, mask, val, DMA_CTRL);
	spin_unlock_irqrestore(&d->dev_lock, flags);
पूर्ण

अटल व्योम ldma_dev_dburst_wr_cfg(काष्ठा ldma_dev *d, bool enable)
अणु
	अचिन्हित दीर्घ flags;
	u32 mask, val;

	अगर (d->inst->type != DMA_TYPE_RX && d->inst->type != DMA_TYPE_MCPY)
		वापस;

	mask = DMA_CTRL_DBURST_WR;
	val = enable ? DMA_CTRL_DBURST_WR : 0;

	spin_lock_irqsave(&d->dev_lock, flags);
	ldma_update_bits(d, mask, val, DMA_CTRL);
	spin_unlock_irqrestore(&d->dev_lock, flags);
पूर्ण

अटल व्योम ldma_dev_vld_fetch_ack_cfg(काष्ठा ldma_dev *d, bool enable)
अणु
	अचिन्हित दीर्घ flags;
	u32 mask, val;

	अगर (d->inst->type != DMA_TYPE_TX)
		वापस;

	mask = DMA_CTRL_VLD_DF_ACK;
	val = enable ? DMA_CTRL_VLD_DF_ACK : 0;

	spin_lock_irqsave(&d->dev_lock, flags);
	ldma_update_bits(d, mask, val, DMA_CTRL);
	spin_unlock_irqrestore(&d->dev_lock, flags);
पूर्ण

अटल व्योम ldma_dev_drb_cfg(काष्ठा ldma_dev *d, पूर्णांक enable)
अणु
	अचिन्हित दीर्घ flags;
	u32 mask = DMA_CTRL_DRB;
	u32 val = enable ? DMA_CTRL_DRB : 0;

	spin_lock_irqsave(&d->dev_lock, flags);
	ldma_update_bits(d, mask, val, DMA_CTRL);
	spin_unlock_irqrestore(&d->dev_lock, flags);
पूर्ण

अटल पूर्णांक ldma_dev_cfg(काष्ठा ldma_dev *d)
अणु
	bool enable;

	ldma_dev_pkt_arb_cfg(d, true);
	ldma_dev_global_polling_enable(d);

	enable = !!(d->flags & DMA_DFT_DRB);
	ldma_dev_drb_cfg(d, enable);

	enable = !!(d->flags & DMA_EN_BYTE_EN);
	ldma_dev_byte_enable_cfg(d, enable);

	enable = !!(d->flags & DMA_CHAN_FLOW_CTL);
	ldma_dev_chan_flow_ctl_cfg(d, enable);

	enable = !!(d->flags & DMA_DESC_FOD);
	ldma_dev_desc_fetch_on_demand_cfg(d, enable);

	enable = !!(d->flags & DMA_DESC_IN_SRAM);
	ldma_dev_sram_desc_cfg(d, enable);

	enable = !!(d->flags & DMA_DBURST_WR);
	ldma_dev_dburst_wr_cfg(d, enable);

	enable = !!(d->flags & DMA_VALID_DESC_FETCH_ACK);
	ldma_dev_vld_fetch_ack_cfg(d, enable);

	अगर (d->ver > DMA_VER22) अणु
		ldma_dev_orrc_cfg(d);
		ldma_dev_df_tout_cfg(d, true, DMA_DFT_DESC_TCNT);
	पूर्ण

	dev_dbg(d->dev, "%s Controller 0x%08x configuration done\n",
		d->inst->name, पढ़ोl(d->base + DMA_CTRL));

	वापस 0;
पूर्ण

अटल पूर्णांक ldma_chan_cctrl_cfg(काष्ठा ldma_chan *c, u32 val)
अणु
	काष्ठा ldma_dev *d = to_ldma_dev(c->vchan.chan.device);
	u32 class_low, class_high;
	अचिन्हित दीर्घ flags;
	u32 reg;

	spin_lock_irqsave(&d->dev_lock, flags);
	ldma_update_bits(d, DMA_CS_MASK, c->nr, DMA_CS);
	reg = पढ़ोl(d->base + DMA_CCTRL);
	/* Read from hardware */
	अगर (reg & DMA_CCTRL_सूची_TX)
		c->flags |= DMA_TX_CH;
	अन्यथा
		c->flags |= DMA_RX_CH;

	/* Keep the class value unchanged */
	class_low = FIELD_GET(DMA_CCTRL_CLASS, reg);
	class_high = FIELD_GET(DMA_CCTRL_CLASSH, reg);
	val &= ~DMA_CCTRL_CLASS;
	val |= FIELD_PREP(DMA_CCTRL_CLASS, class_low);
	val &= ~DMA_CCTRL_CLASSH;
	val |= FIELD_PREP(DMA_CCTRL_CLASSH, class_high);
	ग_लिखोl(val, d->base + DMA_CCTRL);
	spin_unlock_irqrestore(&d->dev_lock, flags);

	वापस 0;
पूर्ण

अटल व्योम ldma_chan_irq_init(काष्ठा ldma_chan *c)
अणु
	काष्ठा ldma_dev *d = to_ldma_dev(c->vchan.chan.device);
	अचिन्हित दीर्घ flags;
	u32 enofs, crofs;
	u32 cn_bit;

	अगर (c->nr < MAX_LOWER_CHANS) अणु
		enofs = DMA_IRNEN;
		crofs = DMA_IRNCR;
	पूर्ण अन्यथा अणु
		enofs = DMA_IRNEN1;
		crofs = DMA_IRNCR1;
	पूर्ण

	cn_bit = BIT(c->nr & MASK_LOWER_CHANS);
	spin_lock_irqsave(&d->dev_lock, flags);
	ldma_update_bits(d, DMA_CS_MASK, c->nr, DMA_CS);

	/* Clear all पूर्णांकerrupts and disabled it */
	ग_लिखोl(0, d->base + DMA_CIE);
	ग_लिखोl(DMA_CI_ALL, d->base + DMA_CIS);

	ldma_update_bits(d, cn_bit, 0, enofs);
	ग_लिखोl(cn_bit, d->base + crofs);
	spin_unlock_irqrestore(&d->dev_lock, flags);
पूर्ण

अटल व्योम ldma_chan_set_class(काष्ठा ldma_chan *c, u32 val)
अणु
	काष्ठा ldma_dev *d = to_ldma_dev(c->vchan.chan.device);
	u32 class_val;

	अगर (d->inst->type == DMA_TYPE_MCPY || val > DMA_MAX_CLASS)
		वापस;

	/* 3 bits low */
	class_val = FIELD_PREP(DMA_CCTRL_CLASS, val & 0x7);
	/* 2 bits high */
	class_val |= FIELD_PREP(DMA_CCTRL_CLASSH, (val >> 3) & 0x3);

	ldma_update_bits(d, DMA_CS_MASK, c->nr, DMA_CS);
	ldma_update_bits(d, DMA_CCTRL_CLASS | DMA_CCTRL_CLASSH, class_val,
			 DMA_CCTRL);
पूर्ण

अटल पूर्णांक ldma_chan_on(काष्ठा ldma_chan *c)
अणु
	काष्ठा ldma_dev *d = to_ldma_dev(c->vchan.chan.device);
	अचिन्हित दीर्घ flags;

	/* If descriptors not configured, not allow to turn on channel */
	अगर (WARN_ON(!c->desc_init))
		वापस -EINVAL;

	spin_lock_irqsave(&d->dev_lock, flags);
	ldma_update_bits(d, DMA_CS_MASK, c->nr, DMA_CS);
	ldma_update_bits(d, DMA_CCTRL_ON, DMA_CCTRL_ON, DMA_CCTRL);
	spin_unlock_irqrestore(&d->dev_lock, flags);

	c->onoff = DMA_CH_ON;

	वापस 0;
पूर्ण

अटल पूर्णांक ldma_chan_off(काष्ठा ldma_chan *c)
अणु
	काष्ठा ldma_dev *d = to_ldma_dev(c->vchan.chan.device);
	अचिन्हित दीर्घ flags;
	u32 val;
	पूर्णांक ret;

	spin_lock_irqsave(&d->dev_lock, flags);
	ldma_update_bits(d, DMA_CS_MASK, c->nr, DMA_CS);
	ldma_update_bits(d, DMA_CCTRL_ON, 0, DMA_CCTRL);
	spin_unlock_irqrestore(&d->dev_lock, flags);

	ret = पढ़ोl_poll_समयout_atomic(d->base + DMA_CCTRL, val,
					!(val & DMA_CCTRL_ON), 0, 10000);
	अगर (ret)
		वापस ret;

	c->onoff = DMA_CH_OFF;

	वापस 0;
पूर्ण

अटल व्योम ldma_chan_desc_hw_cfg(काष्ठा ldma_chan *c, dma_addr_t desc_base,
				  पूर्णांक desc_num)
अणु
	काष्ठा ldma_dev *d = to_ldma_dev(c->vchan.chan.device);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&d->dev_lock, flags);
	ldma_update_bits(d, DMA_CS_MASK, c->nr, DMA_CS);
	ग_लिखोl(lower_32_bits(desc_base), d->base + DMA_CDBA);

	/* Higher 4 bits of 36 bit addressing */
	अगर (IS_ENABLED(CONFIG_64BIT)) अणु
		u32 hi = upper_32_bits(desc_base) & HIGH_4_BITS;

		ldma_update_bits(d, DMA_CDBA_MSB,
				 FIELD_PREP(DMA_CDBA_MSB, hi), DMA_CCTRL);
	पूर्ण
	ग_लिखोl(desc_num, d->base + DMA_CDLEN);
	spin_unlock_irqrestore(&d->dev_lock, flags);

	c->desc_init = true;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
ldma_chan_desc_cfg(काष्ठा dma_chan *chan, dma_addr_t desc_base, पूर्णांक desc_num)
अणु
	काष्ठा ldma_chan *c = to_ldma_chan(chan);
	काष्ठा ldma_dev *d = to_ldma_dev(c->vchan.chan.device);
	काष्ठा dma_async_tx_descriptor *tx;
	काष्ठा dw2_desc_sw *ds;

	अगर (!desc_num) अणु
		dev_err(d->dev, "Channel %d must allocate descriptor first\n",
			c->nr);
		वापस शून्य;
	पूर्ण

	अगर (desc_num > DMA_MAX_DESC_NUM) अणु
		dev_err(d->dev, "Channel %d descriptor number out of range %d\n",
			c->nr, desc_num);
		वापस शून्य;
	पूर्ण

	ldma_chan_desc_hw_cfg(c, desc_base, desc_num);

	c->flags |= DMA_HW_DESC;
	c->desc_cnt = desc_num;
	c->desc_phys = desc_base;

	ds = kzalloc(माप(*ds), GFP_NOWAIT);
	अगर (!ds)
		वापस शून्य;

	tx = &ds->vdesc.tx;
	dma_async_tx_descriptor_init(tx, chan);

	वापस tx;
पूर्ण

अटल पूर्णांक ldma_chan_reset(काष्ठा ldma_chan *c)
अणु
	काष्ठा ldma_dev *d = to_ldma_dev(c->vchan.chan.device);
	अचिन्हित दीर्घ flags;
	u32 val;
	पूर्णांक ret;

	ret = ldma_chan_off(c);
	अगर (ret)
		वापस ret;

	spin_lock_irqsave(&d->dev_lock, flags);
	ldma_update_bits(d, DMA_CS_MASK, c->nr, DMA_CS);
	ldma_update_bits(d, DMA_CCTRL_RST, DMA_CCTRL_RST, DMA_CCTRL);
	spin_unlock_irqrestore(&d->dev_lock, flags);

	ret = पढ़ोl_poll_समयout_atomic(d->base + DMA_CCTRL, val,
					!(val & DMA_CCTRL_RST), 0, 10000);
	अगर (ret)
		वापस ret;

	c->rst = 1;
	c->desc_init = false;

	वापस 0;
पूर्ण

अटल व्योम ldma_chan_byte_offset_cfg(काष्ठा ldma_chan *c, u32 boff_len)
अणु
	काष्ठा ldma_dev *d = to_ldma_dev(c->vchan.chan.device);
	u32 mask = DMA_C_BOFF_EN | DMA_C_BOFF_BOF_LEN;
	u32 val;

	अगर (boff_len > 0 && boff_len <= DMA_CHAN_BOFF_MAX)
		val = FIELD_PREP(DMA_C_BOFF_BOF_LEN, boff_len) | DMA_C_BOFF_EN;
	अन्यथा
		val = 0;

	ldma_update_bits(d, DMA_CS_MASK, c->nr, DMA_CS);
	ldma_update_bits(d, mask, val, DMA_C_BOFF);
पूर्ण

अटल व्योम ldma_chan_data_endian_cfg(काष्ठा ldma_chan *c, bool enable,
				      u32 endian_type)
अणु
	काष्ठा ldma_dev *d = to_ldma_dev(c->vchan.chan.device);
	u32 mask = DMA_C_END_DE_EN | DMA_C_END_DATAENDI;
	u32 val;

	अगर (enable)
		val = DMA_C_END_DE_EN | FIELD_PREP(DMA_C_END_DATAENDI, endian_type);
	अन्यथा
		val = 0;

	ldma_update_bits(d, DMA_CS_MASK, c->nr, DMA_CS);
	ldma_update_bits(d, mask, val, DMA_C_ENDIAN);
पूर्ण

अटल व्योम ldma_chan_desc_endian_cfg(काष्ठा ldma_chan *c, bool enable,
				      u32 endian_type)
अणु
	काष्ठा ldma_dev *d = to_ldma_dev(c->vchan.chan.device);
	u32 mask = DMA_C_END_DES_EN | DMA_C_END_DESENDI;
	u32 val;

	अगर (enable)
		val = DMA_C_END_DES_EN | FIELD_PREP(DMA_C_END_DESENDI, endian_type);
	अन्यथा
		val = 0;

	ldma_update_bits(d, DMA_CS_MASK, c->nr, DMA_CS);
	ldma_update_bits(d, mask, val, DMA_C_ENDIAN);
पूर्ण

अटल व्योम ldma_chan_hdr_mode_cfg(काष्ठा ldma_chan *c, u32 hdr_len, bool csum)
अणु
	काष्ठा ldma_dev *d = to_ldma_dev(c->vchan.chan.device);
	u32 mask, val;

	/* NB, csum disabled, hdr length must be provided */
	अगर (!csum && (!hdr_len || hdr_len > DMA_HDR_LEN_MAX))
		वापस;

	mask = DMA_C_HDRM_HDR_SUM;
	val = DMA_C_HDRM_HDR_SUM;

	अगर (!csum && hdr_len)
		val = hdr_len;

	ldma_update_bits(d, DMA_CS_MASK, c->nr, DMA_CS);
	ldma_update_bits(d, mask, val, DMA_C_HDRM);
पूर्ण

अटल व्योम ldma_chan_rxwr_np_cfg(काष्ठा ldma_chan *c, bool enable)
अणु
	काष्ठा ldma_dev *d = to_ldma_dev(c->vchan.chan.device);
	u32 mask, val;

	/* Only valid क्रम RX channel */
	अगर (ldma_chan_tx(c))
		वापस;

	mask = DMA_CCTRL_WR_NP_EN;
	val = enable ? DMA_CCTRL_WR_NP_EN : 0;

	ldma_update_bits(d, DMA_CS_MASK, c->nr, DMA_CS);
	ldma_update_bits(d, mask, val, DMA_CCTRL);
पूर्ण

अटल व्योम ldma_chan_abc_cfg(काष्ठा ldma_chan *c, bool enable)
अणु
	काष्ठा ldma_dev *d = to_ldma_dev(c->vchan.chan.device);
	u32 mask, val;

	अगर (d->ver < DMA_VER32 || ldma_chan_tx(c))
		वापस;

	mask = DMA_CCTRL_CH_ABC;
	val = enable ? DMA_CCTRL_CH_ABC : 0;

	ldma_update_bits(d, DMA_CS_MASK, c->nr, DMA_CS);
	ldma_update_bits(d, mask, val, DMA_CCTRL);
पूर्ण

अटल पूर्णांक ldma_port_cfg(काष्ठा ldma_port *p)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा ldma_dev *d;
	u32 reg;

	d = p->ldev;
	reg = FIELD_PREP(DMA_PCTRL_TXENDI, p->txendi);
	reg |= FIELD_PREP(DMA_PCTRL_RXENDI, p->rxendi);

	अगर (d->ver == DMA_VER22) अणु
		reg |= FIELD_PREP(DMA_PCTRL_TXBL, p->txbl);
		reg |= FIELD_PREP(DMA_PCTRL_RXBL, p->rxbl);
	पूर्ण अन्यथा अणु
		reg |= FIELD_PREP(DMA_PCTRL_PDEN, p->pkt_drop);

		अगर (p->txbl == DMA_BURSTL_32DW)
			reg |= DMA_PCTRL_TXBL32;
		अन्यथा अगर (p->txbl == DMA_BURSTL_16DW)
			reg |= DMA_PCTRL_TXBL16;
		अन्यथा
			reg |= FIELD_PREP(DMA_PCTRL_TXBL, DMA_PCTRL_TXBL_8);

		अगर (p->rxbl == DMA_BURSTL_32DW)
			reg |= DMA_PCTRL_RXBL32;
		अन्यथा अगर (p->rxbl == DMA_BURSTL_16DW)
			reg |= DMA_PCTRL_RXBL16;
		अन्यथा
			reg |= FIELD_PREP(DMA_PCTRL_RXBL, DMA_PCTRL_RXBL_8);
	पूर्ण

	spin_lock_irqsave(&d->dev_lock, flags);
	ग_लिखोl(p->portid, d->base + DMA_PS);
	ग_लिखोl(reg, d->base + DMA_PCTRL);
	spin_unlock_irqrestore(&d->dev_lock, flags);

	reg = पढ़ोl(d->base + DMA_PCTRL); /* पढ़ो back */
	dev_dbg(d->dev, "Port Control 0x%08x configuration done\n", reg);

	वापस 0;
पूर्ण

अटल पूर्णांक ldma_chan_cfg(काष्ठा ldma_chan *c)
अणु
	काष्ठा ldma_dev *d = to_ldma_dev(c->vchan.chan.device);
	अचिन्हित दीर्घ flags;
	u32 reg;

	reg = c->pden ? DMA_CCTRL_PDEN : 0;
	reg |= c->onoff ? DMA_CCTRL_ON : 0;
	reg |= c->rst ? DMA_CCTRL_RST : 0;

	ldma_chan_cctrl_cfg(c, reg);
	ldma_chan_irq_init(c);

	अगर (d->ver <= DMA_VER22)
		वापस 0;

	spin_lock_irqsave(&d->dev_lock, flags);
	ldma_chan_set_class(c, c->nr);
	ldma_chan_byte_offset_cfg(c, c->boff_len);
	ldma_chan_data_endian_cfg(c, c->data_endian_en, c->data_endian);
	ldma_chan_desc_endian_cfg(c, c->desc_endian_en, c->desc_endian);
	ldma_chan_hdr_mode_cfg(c, c->hdrm_len, c->hdrm_csum);
	ldma_chan_rxwr_np_cfg(c, c->desc_rx_np);
	ldma_chan_abc_cfg(c, c->abc_en);
	spin_unlock_irqrestore(&d->dev_lock, flags);

	अगर (ldma_chan_is_hw_desc(c))
		ldma_chan_desc_hw_cfg(c, c->desc_phys, c->desc_cnt);

	वापस 0;
पूर्ण

अटल व्योम ldma_dev_init(काष्ठा ldma_dev *d)
अणु
	अचिन्हित दीर्घ ch_mask = (अचिन्हित दीर्घ)d->channels_mask;
	काष्ठा ldma_port *p;
	काष्ठा ldma_chan *c;
	पूर्णांक i;
	u32 j;

	spin_lock_init(&d->dev_lock);
	ldma_dev_reset(d);
	ldma_dev_cfg(d);

	/* DMA port initialization */
	क्रम (i = 0; i < d->port_nrs; i++) अणु
		p = &d->ports[i];
		ldma_port_cfg(p);
	पूर्ण

	/* DMA channel initialization */
	क्रम_each_set_bit(j, &ch_mask, d->chan_nrs) अणु
		c = &d->chans[j];
		ldma_chan_cfg(c);
	पूर्ण
पूर्ण

अटल पूर्णांक ldma_cfg_init(काष्ठा ldma_dev *d)
अणु
	काष्ठा fwnode_handle *fwnode = dev_fwnode(d->dev);
	काष्ठा ldma_port *p;
	पूर्णांक i;

	अगर (fwnode_property_पढ़ो_bool(fwnode, "intel,dma-byte-en"))
		d->flags |= DMA_EN_BYTE_EN;

	अगर (fwnode_property_पढ़ो_bool(fwnode, "intel,dma-dburst-wr"))
		d->flags |= DMA_DBURST_WR;

	अगर (fwnode_property_पढ़ो_bool(fwnode, "intel,dma-drb"))
		d->flags |= DMA_DFT_DRB;

	अगर (fwnode_property_पढ़ो_u32(fwnode, "intel,dma-poll-cnt",
				     &d->pollcnt))
		d->pollcnt = DMA_DFT_POLL_CNT;

	अगर (d->inst->chan_fc)
		d->flags |= DMA_CHAN_FLOW_CTL;

	अगर (d->inst->desc_fod)
		d->flags |= DMA_DESC_FOD;

	अगर (d->inst->desc_in_sram)
		d->flags |= DMA_DESC_IN_SRAM;

	अगर (d->inst->valid_desc_fetch_ack)
		d->flags |= DMA_VALID_DESC_FETCH_ACK;

	अगर (d->ver > DMA_VER22) अणु
		अगर (!d->port_nrs)
			वापस -EINVAL;

		क्रम (i = 0; i < d->port_nrs; i++) अणु
			p = &d->ports[i];
			p->rxendi = DMA_DFT_ENDIAN;
			p->txendi = DMA_DFT_ENDIAN;
			p->rxbl = DMA_DFT_BURST;
			p->txbl = DMA_DFT_BURST;
			p->pkt_drop = DMA_PKT_DROP_DIS;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dma_मुक्त_desc_resource(काष्ठा virt_dma_desc *vdesc)
अणु
	काष्ठा dw2_desc_sw *ds = to_lgm_dma_desc(vdesc);
	काष्ठा ldma_chan *c = ds->chan;

	dma_pool_मुक्त(c->desc_pool, ds->desc_hw, ds->desc_phys);
	kमुक्त(ds);
पूर्ण

अटल काष्ठा dw2_desc_sw *
dma_alloc_desc_resource(पूर्णांक num, काष्ठा ldma_chan *c)
अणु
	काष्ठा device *dev = c->vchan.chan.device->dev;
	काष्ठा dw2_desc_sw *ds;

	अगर (num > c->desc_num) अणु
		dev_err(dev, "sg num %d exceed max %d\n", num, c->desc_num);
		वापस शून्य;
	पूर्ण

	ds = kzalloc(माप(*ds), GFP_NOWAIT);
	अगर (!ds)
		वापस शून्य;

	ds->chan = c;
	ds->desc_hw = dma_pool_zalloc(c->desc_pool, GFP_ATOMIC,
				      &ds->desc_phys);
	अगर (!ds->desc_hw) अणु
		dev_dbg(dev, "out of memory for link descriptor\n");
		kमुक्त(ds);
		वापस शून्य;
	पूर्ण
	ds->desc_cnt = num;

	वापस ds;
पूर्ण

अटल व्योम ldma_chan_irq_en(काष्ठा ldma_chan *c)
अणु
	काष्ठा ldma_dev *d = to_ldma_dev(c->vchan.chan.device);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&d->dev_lock, flags);
	ग_लिखोl(c->nr, d->base + DMA_CS);
	ग_लिखोl(DMA_CI_EOP, d->base + DMA_CIE);
	ग_लिखोl(BIT(c->nr), d->base + DMA_IRNEN);
	spin_unlock_irqrestore(&d->dev_lock, flags);
पूर्ण

अटल व्योम ldma_issue_pending(काष्ठा dma_chan *chan)
अणु
	काष्ठा ldma_chan *c = to_ldma_chan(chan);
	काष्ठा ldma_dev *d = to_ldma_dev(c->vchan.chan.device);
	अचिन्हित दीर्घ flags;

	अगर (d->ver == DMA_VER22) अणु
		spin_lock_irqsave(&c->vchan.lock, flags);
		अगर (vchan_issue_pending(&c->vchan)) अणु
			काष्ठा virt_dma_desc *vdesc;

			/* Get the next descriptor */
			vdesc = vchan_next_desc(&c->vchan);
			अगर (!vdesc) अणु
				c->ds = शून्य;
				spin_unlock_irqrestore(&c->vchan.lock, flags);
				वापस;
			पूर्ण
			list_del(&vdesc->node);
			c->ds = to_lgm_dma_desc(vdesc);
			ldma_chan_desc_hw_cfg(c, c->ds->desc_phys, c->ds->desc_cnt);
			ldma_chan_irq_en(c);
		पूर्ण
		spin_unlock_irqrestore(&c->vchan.lock, flags);
	पूर्ण
	ldma_chan_on(c);
पूर्ण

अटल व्योम ldma_synchronize(काष्ठा dma_chan *chan)
अणु
	काष्ठा ldma_chan *c = to_ldma_chan(chan);

	/*
	 * clear any pending work अगर any. In that
	 * हाल the resource needs to be मुक्त here.
	 */
	cancel_work_sync(&c->work);
	vchan_synchronize(&c->vchan);
	अगर (c->ds)
		dma_मुक्त_desc_resource(&c->ds->vdesc);
पूर्ण

अटल पूर्णांक ldma_terminate_all(काष्ठा dma_chan *chan)
अणु
	काष्ठा ldma_chan *c = to_ldma_chan(chan);
	अचिन्हित दीर्घ flags;
	LIST_HEAD(head);

	spin_lock_irqsave(&c->vchan.lock, flags);
	vchan_get_all_descriptors(&c->vchan, &head);
	spin_unlock_irqrestore(&c->vchan.lock, flags);
	vchan_dma_desc_मुक्त_list(&c->vchan, &head);

	वापस ldma_chan_reset(c);
पूर्ण

अटल पूर्णांक ldma_resume_chan(काष्ठा dma_chan *chan)
अणु
	काष्ठा ldma_chan *c = to_ldma_chan(chan);

	ldma_chan_on(c);

	वापस 0;
पूर्ण

अटल पूर्णांक ldma_छोड़ो_chan(काष्ठा dma_chan *chan)
अणु
	काष्ठा ldma_chan *c = to_ldma_chan(chan);

	वापस ldma_chan_off(c);
पूर्ण

अटल क्रमागत dma_status
ldma_tx_status(काष्ठा dma_chan *chan, dma_cookie_t cookie,
	       काष्ठा dma_tx_state *txstate)
अणु
	काष्ठा ldma_chan *c = to_ldma_chan(chan);
	काष्ठा ldma_dev *d = to_ldma_dev(c->vchan.chan.device);
	क्रमागत dma_status status = DMA_COMPLETE;

	अगर (d->ver == DMA_VER22)
		status = dma_cookie_status(chan, cookie, txstate);

	वापस status;
पूर्ण

अटल व्योम dma_chan_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा ldma_chan *c = data;
	काष्ठा ldma_dev *d = to_ldma_dev(c->vchan.chan.device);
	u32 stat;

	/* Disable channel पूर्णांकerrupts  */
	ग_लिखोl(c->nr, d->base + DMA_CS);
	stat = पढ़ोl(d->base + DMA_CIS);
	अगर (!stat)
		वापस;

	ग_लिखोl(पढ़ोl(d->base + DMA_CIE) & ~DMA_CI_ALL, d->base + DMA_CIE);
	ग_लिखोl(stat, d->base + DMA_CIS);
	queue_work(d->wq, &c->work);
पूर्ण

अटल irqवापस_t dma_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ldma_dev *d = dev_id;
	काष्ठा ldma_chan *c;
	अचिन्हित दीर्घ irncr;
	u32 cid;

	irncr = पढ़ोl(d->base + DMA_IRNCR);
	अगर (!irncr) अणु
		dev_err(d->dev, "dummy interrupt\n");
		वापस IRQ_NONE;
	पूर्ण

	क्रम_each_set_bit(cid, &irncr, d->chan_nrs) अणु
		/* Mask */
		ग_लिखोl(पढ़ोl(d->base + DMA_IRNEN) & ~BIT(cid), d->base + DMA_IRNEN);
		/* Ack */
		ग_लिखोl(पढ़ोl(d->base + DMA_IRNCR) | BIT(cid), d->base + DMA_IRNCR);

		c = &d->chans[cid];
		dma_chan_irq(irq, c);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम prep_slave_burst_len(काष्ठा ldma_chan *c)
अणु
	काष्ठा ldma_port *p = c->port;
	काष्ठा dma_slave_config *cfg = &c->config;

	अगर (cfg->dst_maxburst)
		cfg->src_maxburst = cfg->dst_maxburst;

	/* TX and RX has the same burst length */
	p->txbl = ilog2(cfg->src_maxburst);
	p->rxbl = p->txbl;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
ldma_prep_slave_sg(काष्ठा dma_chan *chan, काष्ठा scatterlist *sgl,
		   अचिन्हित पूर्णांक sglen, क्रमागत dma_transfer_direction dir,
		   अचिन्हित दीर्घ flags, व्योम *context)
अणु
	काष्ठा ldma_chan *c = to_ldma_chan(chan);
	काष्ठा ldma_dev *d = to_ldma_dev(c->vchan.chan.device);
	माप_प्रकार len, avail, total = 0;
	काष्ठा dw2_desc *hw_ds;
	काष्ठा dw2_desc_sw *ds;
	काष्ठा scatterlist *sg;
	पूर्णांक num = sglen, i;
	dma_addr_t addr;

	अगर (!sgl)
		वापस शून्य;

	अगर (d->ver > DMA_VER22)
		वापस ldma_chan_desc_cfg(chan, sgl->dma_address, sglen);

	क्रम_each_sg(sgl, sg, sglen, i) अणु
		avail = sg_dma_len(sg);
		अगर (avail > DMA_MAX_SIZE)
			num += DIV_ROUND_UP(avail, DMA_MAX_SIZE) - 1;
	पूर्ण

	ds = dma_alloc_desc_resource(num, c);
	अगर (!ds)
		वापस शून्य;

	c->ds = ds;

	num = 0;
	/* sop and eop has to be handled nicely */
	क्रम_each_sg(sgl, sg, sglen, i) अणु
		addr = sg_dma_address(sg);
		avail = sg_dma_len(sg);
		total += avail;

		करो अणु
			len = min_t(माप_प्रकार, avail, DMA_MAX_SIZE);

			hw_ds = &ds->desc_hw[num];
			चयन (sglen) अणु
			हाल 1:
				hw_ds->field &= ~DESC_SOP;
				hw_ds->field |= FIELD_PREP(DESC_SOP, 1);

				hw_ds->field &= ~DESC_EOP;
				hw_ds->field |= FIELD_PREP(DESC_EOP, 1);
				अवरोध;
			शेष:
				अगर (num == 0) अणु
					hw_ds->field &= ~DESC_SOP;
					hw_ds->field |= FIELD_PREP(DESC_SOP, 1);

					hw_ds->field &= ~DESC_EOP;
					hw_ds->field |= FIELD_PREP(DESC_EOP, 0);
				पूर्ण अन्यथा अगर (num == (sglen - 1)) अणु
					hw_ds->field &= ~DESC_SOP;
					hw_ds->field |= FIELD_PREP(DESC_SOP, 0);
					hw_ds->field &= ~DESC_EOP;
					hw_ds->field |= FIELD_PREP(DESC_EOP, 1);
				पूर्ण अन्यथा अणु
					hw_ds->field &= ~DESC_SOP;
					hw_ds->field |= FIELD_PREP(DESC_SOP, 0);

					hw_ds->field &= ~DESC_EOP;
					hw_ds->field |= FIELD_PREP(DESC_EOP, 0);
				पूर्ण
				अवरोध;
			पूर्ण
			/* Only 32 bit address supported */
			hw_ds->addr = (u32)addr;

			hw_ds->field &= ~DESC_DATA_LEN;
			hw_ds->field |= FIELD_PREP(DESC_DATA_LEN, len);

			hw_ds->field &= ~DESC_C;
			hw_ds->field |= FIELD_PREP(DESC_C, 0);

			hw_ds->field &= ~DESC_BYTE_OFF;
			hw_ds->field |= FIELD_PREP(DESC_BYTE_OFF, addr & 0x3);

			/* Ensure data पढ़ोy beक्रमe ownership change */
			wmb();
			hw_ds->field &= ~DESC_OWN;
			hw_ds->field |= FIELD_PREP(DESC_OWN, DMA_OWN);

			/* Ensure ownership changed beक्रमe moving क्रमward */
			wmb();
			num++;
			addr += len;
			avail -= len;
		पूर्ण जबतक (avail);
	पूर्ण

	ds->size = total;
	prep_slave_burst_len(c);

	वापस vchan_tx_prep(&c->vchan, &ds->vdesc, DMA_CTRL_ACK);
पूर्ण

अटल पूर्णांक
ldma_slave_config(काष्ठा dma_chan *chan, काष्ठा dma_slave_config *cfg)
अणु
	काष्ठा ldma_chan *c = to_ldma_chan(chan);

	स_नकल(&c->config, cfg, माप(c->config));

	वापस 0;
पूर्ण

अटल पूर्णांक ldma_alloc_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा ldma_chan *c = to_ldma_chan(chan);
	काष्ठा ldma_dev *d = to_ldma_dev(c->vchan.chan.device);
	काष्ठा device *dev = c->vchan.chan.device->dev;
	माप_प्रकार	desc_sz;

	अगर (d->ver > DMA_VER22) अणु
		c->flags |= CHAN_IN_USE;
		वापस 0;
	पूर्ण

	अगर (c->desc_pool)
		वापस c->desc_num;

	desc_sz = c->desc_num * माप(काष्ठा dw2_desc);
	c->desc_pool = dma_pool_create(c->name, dev, desc_sz,
				       __alignof__(काष्ठा dw2_desc), 0);

	अगर (!c->desc_pool) अणु
		dev_err(dev, "unable to allocate descriptor pool\n");
		वापस -ENOMEM;
	पूर्ण

	वापस c->desc_num;
पूर्ण

अटल व्योम ldma_मुक्त_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा ldma_chan *c = to_ldma_chan(chan);
	काष्ठा ldma_dev *d = to_ldma_dev(c->vchan.chan.device);

	अगर (d->ver == DMA_VER22) अणु
		dma_pool_destroy(c->desc_pool);
		c->desc_pool = शून्य;
		vchan_मुक्त_chan_resources(to_virt_chan(chan));
		ldma_chan_reset(c);
	पूर्ण अन्यथा अणु
		c->flags &= ~CHAN_IN_USE;
	पूर्ण
पूर्ण

अटल व्योम dma_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ldma_chan *c = container_of(work, काष्ठा ldma_chan, work);
	काष्ठा dma_async_tx_descriptor *tx = &c->ds->vdesc.tx;
	काष्ठा virt_dma_chan *vc = &c->vchan;
	काष्ठा dmaengine_desc_callback cb;
	काष्ठा virt_dma_desc *vd, *_vd;
	अचिन्हित दीर्घ flags;
	LIST_HEAD(head);

	spin_lock_irqsave(&c->vchan.lock, flags);
	list_splice_tail_init(&vc->desc_completed, &head);
	spin_unlock_irqrestore(&c->vchan.lock, flags);
	dmaengine_desc_get_callback(tx, &cb);
	dma_cookie_complete(tx);
	dmaengine_desc_callback_invoke(&cb, शून्य);

	list_क्रम_each_entry_safe(vd, _vd, &head, node) अणु
		dmaengine_desc_get_callback(tx, &cb);
		dma_cookie_complete(tx);
		list_del(&vd->node);
		dmaengine_desc_callback_invoke(&cb, शून्य);

		vchan_vdesc_fini(vd);
	पूर्ण
	c->ds = शून्य;
पूर्ण

अटल व्योम
update_burst_len_v22(काष्ठा ldma_chan *c, काष्ठा ldma_port *p, u32 burst)
अणु
	अगर (ldma_chan_tx(c))
		p->txbl = ilog2(burst);
	अन्यथा
		p->rxbl = ilog2(burst);
पूर्ण

अटल व्योम
update_burst_len_v3X(काष्ठा ldma_chan *c, काष्ठा ldma_port *p, u32 burst)
अणु
	अगर (ldma_chan_tx(c))
		p->txbl = burst;
	अन्यथा
		p->rxbl = burst;
पूर्ण

अटल पूर्णांक
update_client_configs(काष्ठा of_dma *ofdma, काष्ठा of_phandle_args *spec)
अणु
	काष्ठा ldma_dev *d = ofdma->of_dma_data;
	u32 chan_id =  spec->args[0];
	u32 port_id =  spec->args[1];
	u32 burst = spec->args[2];
	काष्ठा ldma_port *p;
	काष्ठा ldma_chan *c;

	अगर (chan_id >= d->chan_nrs || port_id >= d->port_nrs)
		वापस 0;

	p = &d->ports[port_id];
	c = &d->chans[chan_id];
	c->port = p;

	अगर (d->ver == DMA_VER22)
		update_burst_len_v22(c, p, burst);
	अन्यथा
		update_burst_len_v3X(c, p, burst);

	ldma_port_cfg(p);

	वापस 1;
पूर्ण

अटल काष्ठा dma_chan *ldma_xlate(काष्ठा of_phandle_args *spec,
				   काष्ठा of_dma *ofdma)
अणु
	काष्ठा ldma_dev *d = ofdma->of_dma_data;
	u32 chan_id =  spec->args[0];
	पूर्णांक ret;

	अगर (!spec->args_count)
		वापस शून्य;

	/* अगर args_count is 1 driver use शेष settings */
	अगर (spec->args_count > 1) अणु
		ret = update_client_configs(ofdma, spec);
		अगर (!ret)
			वापस शून्य;
	पूर्ण

	वापस dma_get_slave_channel(&d->chans[chan_id].vchan.chan);
पूर्ण

अटल व्योम ldma_dma_init_v22(पूर्णांक i, काष्ठा ldma_dev *d)
अणु
	काष्ठा ldma_chan *c;

	c = &d->chans[i];
	c->nr = i; /* Real channel number */
	c->rst = DMA_CHAN_RST;
	c->desc_num = DMA_DFT_DESC_NUM;
	snम_लिखो(c->name, माप(c->name), "chan%d", c->nr);
	INIT_WORK(&c->work, dma_work);
	c->vchan.desc_मुक्त = dma_मुक्त_desc_resource;
	vchan_init(&c->vchan, &d->dma_dev);
पूर्ण

अटल व्योम ldma_dma_init_v3X(पूर्णांक i, काष्ठा ldma_dev *d)
अणु
	काष्ठा ldma_chan *c;

	c = &d->chans[i];
	c->data_endian = DMA_DFT_ENDIAN;
	c->desc_endian = DMA_DFT_ENDIAN;
	c->data_endian_en = false;
	c->desc_endian_en = false;
	c->desc_rx_np = false;
	c->flags |= DEVICE_ALLOC_DESC;
	c->onoff = DMA_CH_OFF;
	c->rst = DMA_CHAN_RST;
	c->abc_en = true;
	c->hdrm_csum = false;
	c->boff_len = 0;
	c->nr = i;
	c->vchan.desc_मुक्त = dma_मुक्त_desc_resource;
	vchan_init(&c->vchan, &d->dma_dev);
पूर्ण

अटल पूर्णांक ldma_init_v22(काष्ठा ldma_dev *d, काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;

	ret = device_property_पढ़ो_u32(d->dev, "dma-channels", &d->chan_nrs);
	अगर (ret < 0) अणु
		dev_err(d->dev, "unable to read dma-channels property\n");
		वापस ret;
	पूर्ण

	d->irq = platक्रमm_get_irq(pdev, 0);
	अगर (d->irq < 0)
		वापस d->irq;

	ret = devm_request_irq(&pdev->dev, d->irq, dma_पूर्णांकerrupt, 0,
			       DRIVER_NAME, d);
	अगर (ret)
		वापस ret;

	d->wq = alloc_ordered_workqueue("dma_wq", WQ_MEM_RECLAIM |
			WQ_HIGHPRI);
	अगर (!d->wq)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम ldma_clk_disable(व्योम *data)
अणु
	काष्ठा ldma_dev *d = data;

	clk_disable_unprepare(d->core_clk);
	reset_control_निश्चित(d->rst);
पूर्ण

अटल स्थिर काष्ठा ldma_inst_data dma0 = अणु
	.name = "dma0",
	.chan_fc = false,
	.desc_fod = false,
	.desc_in_sram = false,
	.valid_desc_fetch_ack = false,
पूर्ण;

अटल स्थिर काष्ठा ldma_inst_data dma2tx = अणु
	.name = "dma2tx",
	.type = DMA_TYPE_TX,
	.orrc = 16,
	.chan_fc = true,
	.desc_fod = true,
	.desc_in_sram = true,
	.valid_desc_fetch_ack = true,
पूर्ण;

अटल स्थिर काष्ठा ldma_inst_data dma1rx = अणु
	.name = "dma1rx",
	.type = DMA_TYPE_RX,
	.orrc = 16,
	.chan_fc = false,
	.desc_fod = true,
	.desc_in_sram = true,
	.valid_desc_fetch_ack = false,
पूर्ण;

अटल स्थिर काष्ठा ldma_inst_data dma1tx = अणु
	.name = "dma1tx",
	.type = DMA_TYPE_TX,
	.orrc = 16,
	.chan_fc = true,
	.desc_fod = true,
	.desc_in_sram = true,
	.valid_desc_fetch_ack = true,
पूर्ण;

अटल स्थिर काष्ठा ldma_inst_data dma0tx = अणु
	.name = "dma0tx",
	.type = DMA_TYPE_TX,
	.orrc = 16,
	.chan_fc = true,
	.desc_fod = true,
	.desc_in_sram = true,
	.valid_desc_fetch_ack = true,
पूर्ण;

अटल स्थिर काष्ठा ldma_inst_data dma3 = अणु
	.name = "dma3",
	.type = DMA_TYPE_MCPY,
	.orrc = 16,
	.chan_fc = false,
	.desc_fod = false,
	.desc_in_sram = true,
	.valid_desc_fetch_ack = false,
पूर्ण;

अटल स्थिर काष्ठा ldma_inst_data toe_dma30 = अणु
	.name = "toe_dma30",
	.type = DMA_TYPE_MCPY,
	.orrc = 16,
	.chan_fc = false,
	.desc_fod = false,
	.desc_in_sram = true,
	.valid_desc_fetch_ack = true,
पूर्ण;

अटल स्थिर काष्ठा ldma_inst_data toe_dma31 = अणु
	.name = "toe_dma31",
	.type = DMA_TYPE_MCPY,
	.orrc = 16,
	.chan_fc = false,
	.desc_fod = false,
	.desc_in_sram = true,
	.valid_desc_fetch_ack = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id पूर्णांकel_ldma_match[] = अणु
	अणु .compatible = "intel,lgm-cdma", .data = &dma0पूर्ण,
	अणु .compatible = "intel,lgm-dma2tx", .data = &dma2txपूर्ण,
	अणु .compatible = "intel,lgm-dma1rx", .data = &dma1rxपूर्ण,
	अणु .compatible = "intel,lgm-dma1tx", .data = &dma1txपूर्ण,
	अणु .compatible = "intel,lgm-dma0tx", .data = &dma0txपूर्ण,
	अणु .compatible = "intel,lgm-dma3", .data = &dma3पूर्ण,
	अणु .compatible = "intel,lgm-toe-dma30", .data = &toe_dma30पूर्ण,
	अणु .compatible = "intel,lgm-toe-dma31", .data = &toe_dma31पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक पूर्णांकel_ldma_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा dma_device *dma_dev;
	अचिन्हित दीर्घ ch_mask;
	काष्ठा ldma_chan *c;
	काष्ठा ldma_port *p;
	काष्ठा ldma_dev *d;
	u32 id, bitn = 32, j;
	पूर्णांक i, ret;

	d = devm_kzalloc(dev, माप(*d), GFP_KERNEL);
	अगर (!d)
		वापस -ENOMEM;

	/* Link controller to platक्रमm device */
	d->dev = &pdev->dev;

	d->inst = device_get_match_data(dev);
	अगर (!d->inst) अणु
		dev_err(dev, "No device match found\n");
		वापस -ENODEV;
	पूर्ण

	d->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(d->base))
		वापस PTR_ERR(d->base);

	/* Power up and reset the dma engine, some DMAs always on?? */
	d->core_clk = devm_clk_get_optional(dev, शून्य);
	अगर (IS_ERR(d->core_clk))
		वापस PTR_ERR(d->core_clk);
	clk_prepare_enable(d->core_clk);

	d->rst = devm_reset_control_get_optional(dev, शून्य);
	अगर (IS_ERR(d->rst))
		वापस PTR_ERR(d->rst);
	reset_control_deनिश्चित(d->rst);

	ret = devm_add_action_or_reset(dev, ldma_clk_disable, d);
	अगर (ret) अणु
		dev_err(dev, "Failed to devm_add_action_or_reset, %d\n", ret);
		वापस ret;
	पूर्ण

	id = पढ़ोl(d->base + DMA_ID);
	d->chan_nrs = FIELD_GET(DMA_ID_CHNR, id);
	d->port_nrs = FIELD_GET(DMA_ID_PNR, id);
	d->ver = FIELD_GET(DMA_ID_REV, id);

	अगर (id & DMA_ID_AW_36B)
		d->flags |= DMA_ADDR_36BIT;

	अगर (IS_ENABLED(CONFIG_64BIT) && (id & DMA_ID_AW_36B))
		bitn = 36;

	अगर (id & DMA_ID_DW_128B)
		d->flags |= DMA_DATA_128BIT;

	ret = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(bitn));
	अगर (ret) अणु
		dev_err(dev, "No usable DMA configuration\n");
		वापस ret;
	पूर्ण

	अगर (d->ver == DMA_VER22) अणु
		ret = ldma_init_v22(d, pdev);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = device_property_पढ़ो_u32(dev, "dma-channel-mask", &d->channels_mask);
	अगर (ret < 0)
		d->channels_mask = GENMASK(d->chan_nrs - 1, 0);

	dma_dev = &d->dma_dev;

	dma_cap_zero(dma_dev->cap_mask);
	dma_cap_set(DMA_SLAVE, dma_dev->cap_mask);

	/* Channel initializations */
	INIT_LIST_HEAD(&dma_dev->channels);

	/* Port Initializations */
	d->ports = devm_kसुस्मृति(dev, d->port_nrs, माप(*p), GFP_KERNEL);
	अगर (!d->ports)
		वापस -ENOMEM;

	/* Channels Initializations */
	d->chans = devm_kसुस्मृति(d->dev, d->chan_nrs, माप(*c), GFP_KERNEL);
	अगर (!d->chans)
		वापस -ENOMEM;

	क्रम (i = 0; i < d->port_nrs; i++) अणु
		p = &d->ports[i];
		p->portid = i;
		p->ldev = d;
	पूर्ण

	ret = ldma_cfg_init(d);
	अगर (ret)
		वापस ret;

	dma_dev->dev = &pdev->dev;

	ch_mask = (अचिन्हित दीर्घ)d->channels_mask;
	क्रम_each_set_bit(j, &ch_mask, d->chan_nrs) अणु
		अगर (d->ver == DMA_VER22)
			ldma_dma_init_v22(j, d);
		अन्यथा
			ldma_dma_init_v3X(j, d);
	पूर्ण

	dma_dev->device_alloc_chan_resources = ldma_alloc_chan_resources;
	dma_dev->device_मुक्त_chan_resources = ldma_मुक्त_chan_resources;
	dma_dev->device_terminate_all = ldma_terminate_all;
	dma_dev->device_issue_pending = ldma_issue_pending;
	dma_dev->device_tx_status = ldma_tx_status;
	dma_dev->device_resume = ldma_resume_chan;
	dma_dev->device_छोड़ो = ldma_छोड़ो_chan;
	dma_dev->device_prep_slave_sg = ldma_prep_slave_sg;

	अगर (d->ver == DMA_VER22) अणु
		dma_dev->device_config = ldma_slave_config;
		dma_dev->device_synchronize = ldma_synchronize;
		dma_dev->src_addr_widths = BIT(DMA_SLAVE_BUSWIDTH_4_BYTES);
		dma_dev->dst_addr_widths = BIT(DMA_SLAVE_BUSWIDTH_4_BYTES);
		dma_dev->directions = BIT(DMA_MEM_TO_DEV) |
				      BIT(DMA_DEV_TO_MEM);
		dma_dev->residue_granularity =
					DMA_RESIDUE_GRANULARITY_DESCRIPTOR;
	पूर्ण

	platक्रमm_set_drvdata(pdev, d);

	ldma_dev_init(d);

	ret = dma_async_device_रेजिस्टर(dma_dev);
	अगर (ret) अणु
		dev_err(dev, "Failed to register slave DMA engine device\n");
		वापस ret;
	पूर्ण

	ret = of_dma_controller_रेजिस्टर(pdev->dev.of_node, ldma_xlate, d);
	अगर (ret) अणु
		dev_err(dev, "Failed to register of DMA controller\n");
		dma_async_device_unरेजिस्टर(dma_dev);
		वापस ret;
	पूर्ण

	dev_info(dev, "Init done - rev: %x, ports: %d channels: %d\n", d->ver,
		 d->port_nrs, d->chan_nrs);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver पूर्णांकel_ldma_driver = अणु
	.probe = पूर्णांकel_ldma_probe,
	.driver = अणु
		.name = DRIVER_NAME,
		.of_match_table = पूर्णांकel_ldma_match,
	पूर्ण,
पूर्ण;

/*
 * Perक्रमm this driver as device_initcall to make sure initialization happens
 * beक्रमe its DMA clients of some are platक्रमm specअगरic and also to provide
 * रेजिस्टरed DMA channels and DMA capabilities to clients beक्रमe their
 * initialization.
 */
अटल पूर्णांक __init पूर्णांकel_ldma_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&पूर्णांकel_ldma_driver);
पूर्ण

device_initcall(पूर्णांकel_ldma_init);
