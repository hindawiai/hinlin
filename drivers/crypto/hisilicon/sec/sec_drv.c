<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम the HiSilicon SEC units found on Hip06 Hip07
 *
 * Copyright (c) 2016-2017 HiSilicon Limited.
 */
#समावेश <linux/acpi.h>
#समावेश <linux/atomic.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-direction.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/पन.स>
#समावेश <linux/iommu.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqवापस.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश "sec_drv.h"

#घोषणा SEC_QUEUE_AR_FROCE_ALLOC			0
#घोषणा SEC_QUEUE_AR_FROCE_NOALLOC			1
#घोषणा SEC_QUEUE_AR_FROCE_DIS				2

#घोषणा SEC_QUEUE_AW_FROCE_ALLOC			0
#घोषणा SEC_QUEUE_AW_FROCE_NOALLOC			1
#घोषणा SEC_QUEUE_AW_FROCE_DIS				2

/* SEC_ALGSUB रेजिस्टरs */
#घोषणा SEC_ALGSUB_CLK_EN_REG				0x03b8
#घोषणा SEC_ALGSUB_CLK_DIS_REG				0x03bc
#घोषणा SEC_ALGSUB_CLK_ST_REG				0x535c
#घोषणा SEC_ALGSUB_RST_REQ_REG				0x0aa8
#घोषणा SEC_ALGSUB_RST_DREQ_REG				0x0aac
#घोषणा SEC_ALGSUB_RST_ST_REG				0x5a54
#घोषणा   SEC_ALGSUB_RST_ST_IS_RST			BIT(0)

#घोषणा SEC_ALGSUB_BUILD_RST_REQ_REG			0x0ab8
#घोषणा SEC_ALGSUB_BUILD_RST_DREQ_REG			0x0abc
#घोषणा SEC_ALGSUB_BUILD_RST_ST_REG			0x5a5c
#घोषणा   SEC_ALGSUB_BUILD_RST_ST_IS_RST		BIT(0)

#घोषणा SEC_SAA_BASE					0x00001000UL

/* SEC_SAA रेजिस्टरs */
#घोषणा SEC_SAA_CTRL_REG(x)	((x) * SEC_SAA_ADDR_SIZE)
#घोषणा   SEC_SAA_CTRL_GET_QM_EN			BIT(0)

#घोषणा SEC_ST_INTMSK1_REG				0x0200
#घोषणा SEC_ST_RINT1_REG				0x0400
#घोषणा SEC_ST_INTSTS1_REG				0x0600
#घोषणा SEC_BD_MNG_STAT_REG				0x0800
#घोषणा SEC_PARSING_STAT_REG				0x0804
#घोषणा SEC_LOAD_TIME_OUT_CNT_REG			0x0808
#घोषणा SEC_CORE_WORK_TIME_OUT_CNT_REG			0x080c
#घोषणा SEC_BACK_TIME_OUT_CNT_REG			0x0810
#घोषणा SEC_BD1_PARSING_RD_TIME_OUT_CNT_REG		0x0814
#घोषणा SEC_BD1_PARSING_WR_TIME_OUT_CNT_REG		0x0818
#घोषणा SEC_BD2_PARSING_RD_TIME_OUT_CNT_REG		0x081c
#घोषणा SEC_BD2_PARSING_WR_TIME_OUT_CNT_REG		0x0820
#घोषणा SEC_SAA_ACC_REG					0x083c
#घोषणा SEC_BD_NUM_CNT_IN_SEC_REG			0x0858
#घोषणा SEC_LOAD_WORK_TIME_CNT_REG			0x0860
#घोषणा SEC_CORE_WORK_WORK_TIME_CNT_REG			0x0864
#घोषणा SEC_BACK_WORK_TIME_CNT_REG			0x0868
#घोषणा SEC_SAA_IDLE_TIME_CNT_REG			0x086c
#घोषणा SEC_SAA_CLK_CNT_REG				0x0870

/* SEC_COMMON रेजिस्टरs */
#घोषणा SEC_CLK_EN_REG					0x0000
#घोषणा SEC_CTRL_REG					0x0004

#घोषणा SEC_COMMON_CNT_CLR_CE_REG			0x0008
#घोषणा   SEC_COMMON_CNT_CLR_CE_CLEAR			BIT(0)
#घोषणा   SEC_COMMON_CNT_CLR_CE_SNAP_EN			BIT(1)

#घोषणा SEC_SECURE_CTRL_REG				0x000c
#घोषणा SEC_AXI_CACHE_CFG_REG				0x0010
#घोषणा SEC_AXI_QOS_CFG_REG				0x0014
#घोषणा SEC_IPV4_MASK_TABLE_REG				0x0020
#घोषणा SEC_IPV6_MASK_TABLE_X_REG(x)	(0x0024 + (x) * 4)
#घोषणा SEC_FSM_MAX_CNT_REG				0x0064

#घोषणा SEC_CTRL2_REG					0x0068
#घोषणा   SEC_CTRL2_DATA_AXI_RD_OTSD_CFG_M		GENMASK(3, 0)
#घोषणा   SEC_CTRL2_DATA_AXI_RD_OTSD_CFG_S		0
#घोषणा   SEC_CTRL2_DATA_AXI_WR_OTSD_CFG_M		GENMASK(6, 4)
#घोषणा   SEC_CTRL2_DATA_AXI_WR_OTSD_CFG_S		4
#घोषणा   SEC_CTRL2_CLK_GATE_EN				BIT(7)
#घोषणा   SEC_CTRL2_ENDIAN_BD				BIT(8)
#घोषणा   SEC_CTRL2_ENDIAN_BD_TYPE			BIT(9)

#घोषणा SEC_CNT_PRECISION_CFG_REG			0x006c
#घोषणा SEC_DEBUG_BD_CFG_REG				0x0070
#घोषणा   SEC_DEBUG_BD_CFG_WB_NORMAL			BIT(0)
#घोषणा   SEC_DEBUG_BD_CFG_WB_EN			BIT(1)

#घोषणा SEC_Q_SIGHT_SEL					0x0074
#घोषणा SEC_Q_SIGHT_HIS_CLR				0x0078
#घोषणा SEC_Q_VMID_CFG_REG(q)		(0x0100 + (q) * 4)
#घोषणा SEC_Q_WEIGHT_CFG_REG(q)		(0x200 + (q) * 4)
#घोषणा SEC_STAT_CLR_REG				0x0a00
#घोषणा SEC_SAA_IDLE_CNT_CLR_REG			0x0a04
#घोषणा SEC_QM_CPL_Q_IDBUF_DFX_CFG_REG			0x0b00
#घोषणा SEC_QM_CPL_Q_IDBUF_DFX_RESULT_REG		0x0b04
#घोषणा SEC_QM_BD_DFX_CFG_REG				0x0b08
#घोषणा SEC_QM_BD_DFX_RESULT_REG			0x0b0c
#घोषणा SEC_QM_BDID_DFX_RESULT_REG			0x0b10
#घोषणा SEC_QM_BD_DFIFO_STATUS_REG			0x0b14
#घोषणा SEC_QM_BD_DFX_CFG2_REG				0x0b1c
#घोषणा SEC_QM_BD_DFX_RESULT2_REG			0x0b20
#घोषणा SEC_QM_BD_IDFIFO_STATUS_REG			0x0b18
#घोषणा SEC_QM_BD_DFIFO_STATUS2_REG			0x0b28
#घोषणा SEC_QM_BD_IDFIFO_STATUS2_REG			0x0b2c

#घोषणा SEC_HASH_IPV4_MASK				0xfff00000
#घोषणा SEC_MAX_SAA_NUM					0xa
#घोषणा SEC_SAA_ADDR_SIZE				0x1000

#घोषणा SEC_Q_INIT_REG					0x0
#घोषणा   SEC_Q_INIT_WO_STAT_CLEAR			0x2
#घोषणा   SEC_Q_INIT_AND_STAT_CLEAR			0x3

#घोषणा SEC_Q_CFG_REG					0x8
#घोषणा   SEC_Q_CFG_REORDER				BIT(0)

#घोषणा SEC_Q_PROC_NUM_CFG_REG				0x10
#घोषणा SEC_QUEUE_ENB_REG				0x18

#घोषणा SEC_Q_DEPTH_CFG_REG				0x50
#घोषणा   SEC_Q_DEPTH_CFG_DEPTH_M			GENMASK(11, 0)
#घोषणा   SEC_Q_DEPTH_CFG_DEPTH_S			0

#घोषणा SEC_Q_BASE_HADDR_REG				0x54
#घोषणा SEC_Q_BASE_LADDR_REG				0x58
#घोषणा SEC_Q_WR_PTR_REG				0x5c
#घोषणा SEC_Q_OUTORDER_BASE_HADDR_REG			0x60
#घोषणा SEC_Q_OUTORDER_BASE_LADDR_REG			0x64
#घोषणा SEC_Q_OUTORDER_RD_PTR_REG			0x68
#घोषणा SEC_Q_OT_TH_REG					0x6c

#घोषणा SEC_Q_ARUSER_CFG_REG				0x70
#घोषणा   SEC_Q_ARUSER_CFG_FA				BIT(0)
#घोषणा   SEC_Q_ARUSER_CFG_FNA				BIT(1)
#घोषणा   SEC_Q_ARUSER_CFG_RINVLD			BIT(2)
#घोषणा   SEC_Q_ARUSER_CFG_PKG				BIT(3)

#घोषणा SEC_Q_AWUSER_CFG_REG				0x74
#घोषणा   SEC_Q_AWUSER_CFG_FA				BIT(0)
#घोषणा   SEC_Q_AWUSER_CFG_FNA				BIT(1)
#घोषणा   SEC_Q_AWUSER_CFG_PKG				BIT(2)

#घोषणा SEC_Q_ERR_BASE_HADDR_REG			0x7c
#घोषणा SEC_Q_ERR_BASE_LADDR_REG			0x80
#घोषणा SEC_Q_CFG_VF_NUM_REG				0x84
#घोषणा SEC_Q_SOFT_PROC_PTR_REG				0x88
#घोषणा SEC_Q_FAIL_INT_MSK_REG				0x300
#घोषणा SEC_Q_FLOW_INT_MKS_REG				0x304
#घोषणा SEC_Q_FAIL_RINT_REG				0x400
#घोषणा SEC_Q_FLOW_RINT_REG				0x404
#घोषणा SEC_Q_FAIL_INT_STATUS_REG			0x500
#घोषणा SEC_Q_FLOW_INT_STATUS_REG			0x504
#घोषणा SEC_Q_STATUS_REG				0x600
#घोषणा SEC_Q_RD_PTR_REG				0x604
#घोषणा SEC_Q_PRO_PTR_REG				0x608
#घोषणा SEC_Q_OUTORDER_WR_PTR_REG			0x60c
#घोषणा SEC_Q_OT_CNT_STATUS_REG				0x610
#घोषणा SEC_Q_INORDER_BD_NUM_ST_REG			0x650
#घोषणा SEC_Q_INORDER_GET_FLAG_ST_REG			0x654
#घोषणा SEC_Q_INORDER_ADD_FLAG_ST_REG			0x658
#घोषणा SEC_Q_INORDER_TASK_INT_NUM_LEFT_ST_REG		0x65c
#घोषणा SEC_Q_RD_DONE_PTR_REG				0x660
#घोषणा SEC_Q_CPL_Q_BD_NUM_ST_REG			0x700
#घोषणा SEC_Q_CPL_Q_PTR_ST_REG				0x704
#घोषणा SEC_Q_CPL_Q_H_ADDR_ST_REG			0x708
#घोषणा SEC_Q_CPL_Q_L_ADDR_ST_REG			0x70c
#घोषणा SEC_Q_CPL_TASK_INT_NUM_LEFT_ST_REG		0x710
#घोषणा SEC_Q_WRR_ID_CHECK_REG				0x714
#घोषणा SEC_Q_CPLQ_FULL_CHECK_REG			0x718
#घोषणा SEC_Q_SUCCESS_BD_CNT_REG			0x800
#घोषणा SEC_Q_FAIL_BD_CNT_REG				0x804
#घोषणा SEC_Q_GET_BD_CNT_REG				0x808
#घोषणा SEC_Q_IVLD_CNT_REG				0x80c
#घोषणा SEC_Q_BD_PROC_GET_CNT_REG			0x810
#घोषणा SEC_Q_BD_PROC_DONE_CNT_REG			0x814
#घोषणा SEC_Q_LAT_CLR_REG				0x850
#घोषणा SEC_Q_PKT_LAT_MAX_REG				0x854
#घोषणा SEC_Q_PKT_LAT_AVG_REG				0x858
#घोषणा SEC_Q_PKT_LAT_MIN_REG				0x85c
#घोषणा SEC_Q_ID_CLR_CFG_REG				0x900
#घोषणा SEC_Q_1ST_BD_ERR_ID_REG				0x904
#घोषणा SEC_Q_1ST_AUTH_FAIL_ID_REG			0x908
#घोषणा SEC_Q_1ST_RD_ERR_ID_REG				0x90c
#घोषणा SEC_Q_1ST_ECC2_ERR_ID_REG			0x910
#घोषणा SEC_Q_1ST_IVLD_ID_REG				0x914
#घोषणा SEC_Q_1ST_BD_WR_ERR_ID_REG			0x918
#घोषणा SEC_Q_1ST_ERR_BD_WR_ERR_ID_REG			0x91c
#घोषणा SEC_Q_1ST_BD_MAC_WR_ERR_ID_REG			0x920

काष्ठा sec_debug_bd_info अणु
#घोषणा SEC_DEBUG_BD_INFO_SOFT_ERR_CHECK_M	GENMASK(22, 0)
	u32 soft_err_check;
#घोषणा SEC_DEBUG_BD_INFO_HARD_ERR_CHECK_M	GENMASK(9, 0)
	u32 hard_err_check;
	u32 icv_mac1st_word;
#घोषणा SEC_DEBUG_BD_INFO_GET_ID_M		GENMASK(19, 0)
	u32 sec_get_id;
	/* W4---W15 */
	u32 reserv_left[12];
पूर्ण;

काष्ठा sec_out_bd_info	अणु
#घोषणा SEC_OUT_BD_INFO_Q_ID_M			GENMASK(11, 0)
#घोषणा SEC_OUT_BD_INFO_ECC_2BIT_ERR		BIT(14)
	u16 data;
पूर्ण;

#घोषणा SEC_MAX_DEVICES				8
अटल काष्ठा sec_dev_info *sec_devices[SEC_MAX_DEVICES];
अटल DEFINE_MUTEX(sec_id_lock);

अटल पूर्णांक sec_queue_map_io(काष्ठा sec_queue *queue)
अणु
	काष्ठा device *dev = queue->dev_info->dev;
	काष्ठा resource *res;

	res = platक्रमm_get_resource(to_platक्रमm_device(dev),
				    IORESOURCE_MEM,
				    2 + queue->queue_id);
	अगर (!res) अणु
		dev_err(dev, "Failed to get queue %u memory resource\n",
			queue->queue_id);
		वापस -ENOMEM;
	पूर्ण
	queue->regs = ioremap(res->start, resource_size(res));
	अगर (!queue->regs)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम sec_queue_unmap_io(काष्ठा sec_queue *queue)
अणु
	 iounmap(queue->regs);
पूर्ण

अटल पूर्णांक sec_queue_ar_pkgattr(काष्ठा sec_queue *queue, u32 ar_pkg)
अणु
	व्योम __iomem *addr = queue->regs +  SEC_Q_ARUSER_CFG_REG;
	u32 regval;

	regval = पढ़ोl_relaxed(addr);
	अगर (ar_pkg)
		regval |= SEC_Q_ARUSER_CFG_PKG;
	अन्यथा
		regval &= ~SEC_Q_ARUSER_CFG_PKG;
	ग_लिखोl_relaxed(regval, addr);

	वापस 0;
पूर्ण

अटल पूर्णांक sec_queue_aw_pkgattr(काष्ठा sec_queue *queue, u32 aw_pkg)
अणु
	व्योम __iomem *addr = queue->regs + SEC_Q_AWUSER_CFG_REG;
	u32 regval;

	regval = पढ़ोl_relaxed(addr);
	regval |= SEC_Q_AWUSER_CFG_PKG;
	ग_लिखोl_relaxed(regval, addr);

	वापस 0;
पूर्ण

अटल पूर्णांक sec_clk_en(काष्ठा sec_dev_info *info)
अणु
	व्योम __iomem *base = info->regs[SEC_COMMON];
	u32 i = 0;

	ग_लिखोl_relaxed(0x7, base + SEC_ALGSUB_CLK_EN_REG);
	करो अणु
		usleep_range(1000, 10000);
		अगर ((पढ़ोl_relaxed(base + SEC_ALGSUB_CLK_ST_REG) & 0x7) == 0x7)
			वापस 0;
		i++;
	पूर्ण जबतक (i < 10);
	dev_err(info->dev, "sec clock enable fail!\n");

	वापस -EIO;
पूर्ण

अटल पूर्णांक sec_clk_dis(काष्ठा sec_dev_info *info)
अणु
	व्योम __iomem *base = info->regs[SEC_COMMON];
	u32 i = 0;

	ग_लिखोl_relaxed(0x7, base + SEC_ALGSUB_CLK_DIS_REG);
	करो अणु
		usleep_range(1000, 10000);
		अगर ((पढ़ोl_relaxed(base + SEC_ALGSUB_CLK_ST_REG) & 0x7) == 0)
			वापस 0;
		i++;
	पूर्ण जबतक (i < 10);
	dev_err(info->dev, "sec clock disable fail!\n");

	वापस -EIO;
पूर्ण

अटल पूर्णांक sec_reset_whole_module(काष्ठा sec_dev_info *info)
अणु
	व्योम __iomem *base = info->regs[SEC_COMMON];
	bool is_reset, b_is_reset;
	u32 i = 0;

	ग_लिखोl_relaxed(1, base + SEC_ALGSUB_RST_REQ_REG);
	ग_लिखोl_relaxed(1, base + SEC_ALGSUB_BUILD_RST_REQ_REG);
	जबतक (1) अणु
		usleep_range(1000, 10000);
		is_reset = पढ़ोl_relaxed(base + SEC_ALGSUB_RST_ST_REG) &
			SEC_ALGSUB_RST_ST_IS_RST;
		b_is_reset = पढ़ोl_relaxed(base + SEC_ALGSUB_BUILD_RST_ST_REG) &
			SEC_ALGSUB_BUILD_RST_ST_IS_RST;
		अगर (is_reset && b_is_reset)
			अवरोध;
		i++;
		अगर (i > 10) अणु
			dev_err(info->dev, "Reset req failed\n");
			वापस -EIO;
		पूर्ण
	पूर्ण

	i = 0;
	ग_लिखोl_relaxed(1, base + SEC_ALGSUB_RST_DREQ_REG);
	ग_लिखोl_relaxed(1, base + SEC_ALGSUB_BUILD_RST_DREQ_REG);
	जबतक (1) अणु
		usleep_range(1000, 10000);
		is_reset = पढ़ोl_relaxed(base + SEC_ALGSUB_RST_ST_REG) &
			SEC_ALGSUB_RST_ST_IS_RST;
		b_is_reset = पढ़ोl_relaxed(base + SEC_ALGSUB_BUILD_RST_ST_REG) &
			SEC_ALGSUB_BUILD_RST_ST_IS_RST;
		अगर (!is_reset && !b_is_reset)
			अवरोध;

		i++;
		अगर (i > 10) अणु
			dev_err(info->dev, "Reset dreq failed\n");
			वापस -EIO;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sec_bd_endian_little(काष्ठा sec_dev_info *info)
अणु
	व्योम __iomem *addr = info->regs[SEC_SAA] + SEC_CTRL2_REG;
	u32 regval;

	regval = पढ़ोl_relaxed(addr);
	regval &= ~(SEC_CTRL2_ENDIAN_BD | SEC_CTRL2_ENDIAN_BD_TYPE);
	ग_लिखोl_relaxed(regval, addr);
पूर्ण

/*
 * sec_cache_config - configure optimum cache placement
 */
अटल व्योम sec_cache_config(काष्ठा sec_dev_info *info)
अणु
	काष्ठा iommu_करोमुख्य *करोमुख्य;
	व्योम __iomem *addr = info->regs[SEC_SAA] + SEC_CTRL_REG;

	करोमुख्य = iommu_get_करोमुख्य_क्रम_dev(info->dev);

	/* Check that translation is occurring */
	अगर (करोमुख्य && (करोमुख्य->type & __IOMMU_DOMAIN_PAGING))
		ग_लिखोl_relaxed(0x44cf9e, addr);
	अन्यथा
		ग_लिखोl_relaxed(0x4cfd9, addr);
पूर्ण

अटल व्योम sec_data_axiwr_otsd_cfg(काष्ठा sec_dev_info *info, u32 cfg)
अणु
	व्योम __iomem *addr = info->regs[SEC_SAA] + SEC_CTRL2_REG;
	u32 regval;

	regval = पढ़ोl_relaxed(addr);
	regval &= ~SEC_CTRL2_DATA_AXI_WR_OTSD_CFG_M;
	regval |= (cfg << SEC_CTRL2_DATA_AXI_WR_OTSD_CFG_S) &
		SEC_CTRL2_DATA_AXI_WR_OTSD_CFG_M;
	ग_लिखोl_relaxed(regval, addr);
पूर्ण

अटल व्योम sec_data_axird_otsd_cfg(काष्ठा sec_dev_info *info, u32 cfg)
अणु
	व्योम __iomem *addr = info->regs[SEC_SAA] + SEC_CTRL2_REG;
	u32 regval;

	regval = पढ़ोl_relaxed(addr);
	regval &= ~SEC_CTRL2_DATA_AXI_RD_OTSD_CFG_M;
	regval |= (cfg << SEC_CTRL2_DATA_AXI_RD_OTSD_CFG_S) &
		SEC_CTRL2_DATA_AXI_RD_OTSD_CFG_M;
	ग_लिखोl_relaxed(regval, addr);
पूर्ण

अटल व्योम sec_clk_gate_en(काष्ठा sec_dev_info *info, bool clkgate)
अणु
	व्योम __iomem *addr = info->regs[SEC_SAA] + SEC_CTRL2_REG;
	u32 regval;

	regval = पढ़ोl_relaxed(addr);
	अगर (clkgate)
		regval |= SEC_CTRL2_CLK_GATE_EN;
	अन्यथा
		regval &= ~SEC_CTRL2_CLK_GATE_EN;
	ग_लिखोl_relaxed(regval, addr);
पूर्ण

अटल व्योम sec_comm_cnt_cfg(काष्ठा sec_dev_info *info, bool clr_ce)
अणु
	व्योम __iomem *addr = info->regs[SEC_SAA] + SEC_COMMON_CNT_CLR_CE_REG;
	u32 regval;

	regval = पढ़ोl_relaxed(addr);
	अगर (clr_ce)
		regval |= SEC_COMMON_CNT_CLR_CE_CLEAR;
	अन्यथा
		regval &= ~SEC_COMMON_CNT_CLR_CE_CLEAR;
	ग_लिखोl_relaxed(regval, addr);
पूर्ण

अटल व्योम sec_commsnap_en(काष्ठा sec_dev_info *info, bool snap_en)
अणु
	व्योम __iomem *addr = info->regs[SEC_SAA] + SEC_COMMON_CNT_CLR_CE_REG;
	u32 regval;

	regval = पढ़ोl_relaxed(addr);
	अगर (snap_en)
		regval |= SEC_COMMON_CNT_CLR_CE_SNAP_EN;
	अन्यथा
		regval &= ~SEC_COMMON_CNT_CLR_CE_SNAP_EN;
	ग_लिखोl_relaxed(regval, addr);
पूर्ण

अटल व्योम sec_ipv6_hashmask(काष्ठा sec_dev_info *info, u32 hash_mask[])
अणु
	व्योम __iomem *base = info->regs[SEC_SAA];
	पूर्णांक i;

	क्रम (i = 0; i < 10; i++)
		ग_लिखोl_relaxed(hash_mask[0],
			       base + SEC_IPV6_MASK_TABLE_X_REG(i));
पूर्ण

अटल पूर्णांक sec_ipv4_hashmask(काष्ठा sec_dev_info *info, u32 hash_mask)
अणु
	अगर (hash_mask & SEC_HASH_IPV4_MASK) अणु
		dev_err(info->dev, "Sec Ipv4 Hash Mask Input Error!\n ");
		वापस -EINVAL;
	पूर्ण

	ग_लिखोl_relaxed(hash_mask,
		       info->regs[SEC_SAA] + SEC_IPV4_MASK_TABLE_REG);

	वापस 0;
पूर्ण

अटल व्योम sec_set_dbg_bd_cfg(काष्ठा sec_dev_info *info, u32 cfg)
अणु
	व्योम __iomem *addr = info->regs[SEC_SAA] + SEC_DEBUG_BD_CFG_REG;
	u32 regval;

	regval = पढ़ोl_relaxed(addr);
	/* Always disable ग_लिखो back of normal bd */
	regval &= ~SEC_DEBUG_BD_CFG_WB_NORMAL;

	अगर (cfg)
		regval &= ~SEC_DEBUG_BD_CFG_WB_EN;
	अन्यथा
		regval |= SEC_DEBUG_BD_CFG_WB_EN;

	ग_लिखोl_relaxed(regval, addr);
पूर्ण

अटल व्योम sec_saa_getqm_en(काष्ठा sec_dev_info *info, u32 saa_indx, u32 en)
अणु
	व्योम __iomem *addr = info->regs[SEC_SAA] + SEC_SAA_BASE +
		SEC_SAA_CTRL_REG(saa_indx);
	u32 regval;

	regval = पढ़ोl_relaxed(addr);
	अगर (en)
		regval |= SEC_SAA_CTRL_GET_QM_EN;
	अन्यथा
		regval &= ~SEC_SAA_CTRL_GET_QM_EN;
	ग_लिखोl_relaxed(regval, addr);
पूर्ण

अटल व्योम sec_saa_पूर्णांक_mask(काष्ठा sec_dev_info *info, u32 saa_indx,
			     u32 saa_पूर्णांक_mask)
अणु
	ग_लिखोl_relaxed(saa_पूर्णांक_mask,
		       info->regs[SEC_SAA] + SEC_SAA_BASE + SEC_ST_INTMSK1_REG +
		       saa_indx * SEC_SAA_ADDR_SIZE);
पूर्ण

अटल व्योम sec_streamid(काष्ठा sec_dev_info *info, पूर्णांक i)
अणु
	#घोषणा SEC_SID 0x600
	#घोषणा SEC_VMID 0

	ग_लिखोl_relaxed((SEC_VMID | ((SEC_SID & 0xffff) << 8)),
		       info->regs[SEC_SAA] + SEC_Q_VMID_CFG_REG(i));
पूर्ण

अटल व्योम sec_queue_ar_alloc(काष्ठा sec_queue *queue, u32 alloc)
अणु
	व्योम __iomem *addr = queue->regs + SEC_Q_ARUSER_CFG_REG;
	u32 regval;

	regval = पढ़ोl_relaxed(addr);
	अगर (alloc == SEC_QUEUE_AR_FROCE_ALLOC) अणु
		regval |= SEC_Q_ARUSER_CFG_FA;
		regval &= ~SEC_Q_ARUSER_CFG_FNA;
	पूर्ण अन्यथा अणु
		regval &= ~SEC_Q_ARUSER_CFG_FA;
		regval |= SEC_Q_ARUSER_CFG_FNA;
	पूर्ण

	ग_लिखोl_relaxed(regval, addr);
पूर्ण

अटल व्योम sec_queue_aw_alloc(काष्ठा sec_queue *queue, u32 alloc)
अणु
	व्योम __iomem *addr = queue->regs + SEC_Q_AWUSER_CFG_REG;
	u32 regval;

	regval = पढ़ोl_relaxed(addr);
	अगर (alloc == SEC_QUEUE_AW_FROCE_ALLOC) अणु
		regval |= SEC_Q_AWUSER_CFG_FA;
		regval &= ~SEC_Q_AWUSER_CFG_FNA;
	पूर्ण अन्यथा अणु
		regval &= ~SEC_Q_AWUSER_CFG_FA;
		regval |= SEC_Q_AWUSER_CFG_FNA;
	पूर्ण

	ग_लिखोl_relaxed(regval, addr);
पूर्ण

अटल व्योम sec_queue_reorder(काष्ठा sec_queue *queue, bool reorder)
अणु
	व्योम __iomem *base = queue->regs;
	u32 regval;

	regval = पढ़ोl_relaxed(base + SEC_Q_CFG_REG);
	अगर (reorder)
		regval |= SEC_Q_CFG_REORDER;
	अन्यथा
		regval &= ~SEC_Q_CFG_REORDER;
	ग_लिखोl_relaxed(regval, base + SEC_Q_CFG_REG);
पूर्ण

अटल व्योम sec_queue_depth(काष्ठा sec_queue *queue, u32 depth)
अणु
	व्योम __iomem *addr = queue->regs + SEC_Q_DEPTH_CFG_REG;
	u32 regval;

	regval = पढ़ोl_relaxed(addr);
	regval &= ~SEC_Q_DEPTH_CFG_DEPTH_M;
	regval |= (depth << SEC_Q_DEPTH_CFG_DEPTH_S) & SEC_Q_DEPTH_CFG_DEPTH_M;

	ग_लिखोl_relaxed(regval, addr);
पूर्ण

अटल व्योम sec_queue_cmdbase_addr(काष्ठा sec_queue *queue, u64 addr)
अणु
	ग_लिखोl_relaxed(upper_32_bits(addr), queue->regs + SEC_Q_BASE_HADDR_REG);
	ग_लिखोl_relaxed(lower_32_bits(addr), queue->regs + SEC_Q_BASE_LADDR_REG);
पूर्ण

अटल व्योम sec_queue_outorder_addr(काष्ठा sec_queue *queue, u64 addr)
अणु
	ग_लिखोl_relaxed(upper_32_bits(addr),
		       queue->regs + SEC_Q_OUTORDER_BASE_HADDR_REG);
	ग_लिखोl_relaxed(lower_32_bits(addr),
		       queue->regs + SEC_Q_OUTORDER_BASE_LADDR_REG);
पूर्ण

अटल व्योम sec_queue_errbase_addr(काष्ठा sec_queue *queue, u64 addr)
अणु
	ग_लिखोl_relaxed(upper_32_bits(addr),
		       queue->regs + SEC_Q_ERR_BASE_HADDR_REG);
	ग_लिखोl_relaxed(lower_32_bits(addr),
		       queue->regs + SEC_Q_ERR_BASE_LADDR_REG);
पूर्ण

अटल व्योम sec_queue_irq_disable(काष्ठा sec_queue *queue)
अणु
	ग_लिखोl_relaxed((u32)~0, queue->regs + SEC_Q_FLOW_INT_MKS_REG);
पूर्ण

अटल व्योम sec_queue_irq_enable(काष्ठा sec_queue *queue)
अणु
	ग_लिखोl_relaxed(0, queue->regs + SEC_Q_FLOW_INT_MKS_REG);
पूर्ण

अटल व्योम sec_queue_abn_irq_disable(काष्ठा sec_queue *queue)
अणु
	ग_लिखोl_relaxed((u32)~0, queue->regs + SEC_Q_FAIL_INT_MSK_REG);
पूर्ण

अटल व्योम sec_queue_stop(काष्ठा sec_queue *queue)
अणु
	disable_irq(queue->task_irq);
	sec_queue_irq_disable(queue);
	ग_लिखोl_relaxed(0x0, queue->regs + SEC_QUEUE_ENB_REG);
पूर्ण

अटल व्योम sec_queue_start(काष्ठा sec_queue *queue)
अणु
	sec_queue_irq_enable(queue);
	enable_irq(queue->task_irq);
	queue->expected = 0;
	ग_लिखोl_relaxed(SEC_Q_INIT_AND_STAT_CLEAR, queue->regs + SEC_Q_INIT_REG);
	ग_लिखोl_relaxed(0x1, queue->regs + SEC_QUEUE_ENB_REG);
पूर्ण

अटल काष्ठा sec_queue *sec_alloc_queue(काष्ठा sec_dev_info *info)
अणु
	पूर्णांक i;

	mutex_lock(&info->dev_lock);

	/* Get the first idle queue in SEC device */
	क्रम (i = 0; i < SEC_Q_NUM; i++)
		अगर (!info->queues[i].in_use) अणु
			info->queues[i].in_use = true;
			info->queues_in_use++;
			mutex_unlock(&info->dev_lock);

			वापस &info->queues[i];
		पूर्ण
	mutex_unlock(&info->dev_lock);

	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल पूर्णांक sec_queue_मुक्त(काष्ठा sec_queue *queue)
अणु
	काष्ठा sec_dev_info *info = queue->dev_info;

	अगर (queue->queue_id >= SEC_Q_NUM) अणु
		dev_err(info->dev, "No queue %u\n", queue->queue_id);
		वापस -ENODEV;
	पूर्ण

	अगर (!queue->in_use) अणु
		dev_err(info->dev, "Queue %u is idle\n", queue->queue_id);
		वापस -ENODEV;
	पूर्ण

	mutex_lock(&info->dev_lock);
	queue->in_use = false;
	info->queues_in_use--;
	mutex_unlock(&info->dev_lock);

	वापस 0;
पूर्ण

अटल irqवापस_t sec_isr_handle_th(पूर्णांक irq, व्योम *q)
अणु
	sec_queue_irq_disable(q);
	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल irqवापस_t sec_isr_handle(पूर्णांक irq, व्योम *q)
अणु
	काष्ठा sec_queue *queue = q;
	काष्ठा sec_queue_ring_cmd *msg_ring = &queue->ring_cmd;
	काष्ठा sec_queue_ring_cq *cq_ring = &queue->ring_cq;
	काष्ठा sec_out_bd_info *outorder_msg;
	काष्ठा sec_bd_info *msg;
	u32 ooo_पढ़ो, ooo_ग_लिखो;
	व्योम __iomem *base = queue->regs;
	पूर्णांक q_id;

	ooo_पढ़ो = पढ़ोl(base + SEC_Q_OUTORDER_RD_PTR_REG);
	ooo_ग_लिखो = पढ़ोl(base + SEC_Q_OUTORDER_WR_PTR_REG);
	outorder_msg = cq_ring->vaddr + ooo_पढ़ो;
	q_id = outorder_msg->data & SEC_OUT_BD_INFO_Q_ID_M;
	msg = msg_ring->vaddr + q_id;

	जबतक ((ooo_ग_लिखो != ooo_पढ़ो) && msg->w0 & SEC_BD_W0_DONE) अणु
		/*
		 * Must be beक्रमe callback otherwise blocks adding other chained
		 * elements
		 */
		set_bit(q_id, queue->unprocessed);
		अगर (q_id == queue->expected)
			जबतक (test_bit(queue->expected, queue->unprocessed)) अणु
				clear_bit(queue->expected, queue->unprocessed);
				msg = msg_ring->vaddr + queue->expected;
				msg->w0 &= ~SEC_BD_W0_DONE;
				msg_ring->callback(msg,
						queue->shaकरोw[queue->expected]);
				queue->shaकरोw[queue->expected] = शून्य;
				queue->expected = (queue->expected + 1) %
					SEC_QUEUE_LEN;
				atomic_dec(&msg_ring->used);
			पूर्ण

		ooo_पढ़ो = (ooo_पढ़ो + 1) % SEC_QUEUE_LEN;
		ग_लिखोl(ooo_पढ़ो, base + SEC_Q_OUTORDER_RD_PTR_REG);
		ooo_ग_लिखो = पढ़ोl(base + SEC_Q_OUTORDER_WR_PTR_REG);
		outorder_msg = cq_ring->vaddr + ooo_पढ़ो;
		q_id = outorder_msg->data & SEC_OUT_BD_INFO_Q_ID_M;
		msg = msg_ring->vaddr + q_id;
	पूर्ण

	sec_queue_irq_enable(queue);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक sec_queue_irq_init(काष्ठा sec_queue *queue)
अणु
	काष्ठा sec_dev_info *info = queue->dev_info;
	पूर्णांक irq = queue->task_irq;
	पूर्णांक ret;

	ret = request_thपढ़ोed_irq(irq, sec_isr_handle_th, sec_isr_handle,
				   IRQF_TRIGGER_RISING, queue->name, queue);
	अगर (ret) अणु
		dev_err(info->dev, "request irq(%d) failed %d\n", irq, ret);
		वापस ret;
	पूर्ण
	disable_irq(irq);

	वापस 0;
पूर्ण

अटल पूर्णांक sec_queue_irq_uninit(काष्ठा sec_queue *queue)
अणु
	मुक्त_irq(queue->task_irq, queue);

	वापस 0;
पूर्ण

अटल काष्ठा sec_dev_info *sec_device_get(व्योम)
अणु
	काष्ठा sec_dev_info *sec_dev = शून्य;
	काष्ठा sec_dev_info *this_sec_dev;
	पूर्णांक least_busy_n = SEC_Q_NUM + 1;
	पूर्णांक i;

	/* Find which one is least busy and use that first */
	क्रम (i = 0; i < SEC_MAX_DEVICES; i++) अणु
		this_sec_dev = sec_devices[i];
		अगर (this_sec_dev &&
		    this_sec_dev->queues_in_use < least_busy_n) अणु
			least_busy_n = this_sec_dev->queues_in_use;
			sec_dev = this_sec_dev;
		पूर्ण
	पूर्ण

	वापस sec_dev;
पूर्ण

अटल काष्ठा sec_queue *sec_queue_alloc_start(काष्ठा sec_dev_info *info)
अणु
	काष्ठा sec_queue *queue;

	queue = sec_alloc_queue(info);
	अगर (IS_ERR(queue)) अणु
		dev_err(info->dev, "alloc sec queue failed! %ld\n",
			PTR_ERR(queue));
		वापस queue;
	पूर्ण

	sec_queue_start(queue);

	वापस queue;
पूर्ण

/**
 * sec_queue_alloc_start_safe - get a hw queue from appropriate instance
 *
 * This function करोes extremely simplistic load balancing. It करोes not take पूर्णांकo
 * account NUMA locality of the accelerator, or which cpu has requested the
 * queue.  Future work may focus on optimizing this in order to improve full
 * machine throughput.
 */
काष्ठा sec_queue *sec_queue_alloc_start_safe(व्योम)
अणु
	काष्ठा sec_dev_info *info;
	काष्ठा sec_queue *queue = ERR_PTR(-ENODEV);

	mutex_lock(&sec_id_lock);
	info = sec_device_get();
	अगर (!info)
		जाओ unlock;

	queue = sec_queue_alloc_start(info);

unlock:
	mutex_unlock(&sec_id_lock);

	वापस queue;
पूर्ण

/**
 * sec_queue_stop_release() - मुक्त up a hw queue क्रम reuse
 * @queue: The queue we are करोne with.
 *
 * This will stop the current queue, terminanting any transactions
 * that are inflight an वापस it to the pool of available hw queuess
 */
पूर्णांक sec_queue_stop_release(काष्ठा sec_queue *queue)
अणु
	काष्ठा device *dev = queue->dev_info->dev;
	पूर्णांक ret;

	sec_queue_stop(queue);

	ret = sec_queue_मुक्त(queue);
	अगर (ret)
		dev_err(dev, "Releasing queue failed %d\n", ret);

	वापस ret;
पूर्ण

/**
 * sec_queue_empty() - Is this hardware queue currently empty.
 * @queue: The queue to test
 *
 * We need to know अगर we have an empty queue क्रम some of the chaining modes
 * as अगर it is not empty we may need to hold the message in a software queue
 * until the hw queue is drained.
 */
bool sec_queue_empty(काष्ठा sec_queue *queue)
अणु
	काष्ठा sec_queue_ring_cmd *msg_ring = &queue->ring_cmd;

	वापस !atomic_पढ़ो(&msg_ring->used);
पूर्ण

/**
 * sec_queue_send() - queue up a single operation in the hw queue
 * @queue: The queue in which to put the message
 * @msg: The message
 * @ctx: Context to be put in the shaकरोw array and passed back to cb on result.
 *
 * This function will वापस -EAGAIN अगर the queue is currently full.
 */
पूर्णांक sec_queue_send(काष्ठा sec_queue *queue, काष्ठा sec_bd_info *msg, व्योम *ctx)
अणु
	काष्ठा sec_queue_ring_cmd *msg_ring = &queue->ring_cmd;
	व्योम __iomem *base = queue->regs;
	u32 ग_लिखो, पढ़ो;

	mutex_lock(&msg_ring->lock);
	पढ़ो = पढ़ोl(base + SEC_Q_RD_PTR_REG);
	ग_लिखो = पढ़ोl(base + SEC_Q_WR_PTR_REG);
	अगर (ग_लिखो == पढ़ो && atomic_पढ़ो(&msg_ring->used) == SEC_QUEUE_LEN) अणु
		mutex_unlock(&msg_ring->lock);
		वापस -EAGAIN;
	पूर्ण
	स_नकल(msg_ring->vaddr + ग_लिखो, msg, माप(*msg));
	queue->shaकरोw[ग_लिखो] = ctx;
	ग_लिखो = (ग_लिखो + 1) % SEC_QUEUE_LEN;

	/* Ensure content updated beक्रमe queue advance */
	wmb();
	ग_लिखोl(ग_लिखो, base + SEC_Q_WR_PTR_REG);

	atomic_inc(&msg_ring->used);
	mutex_unlock(&msg_ring->lock);

	वापस 0;
पूर्ण

bool sec_queue_can_enqueue(काष्ठा sec_queue *queue, पूर्णांक num)
अणु
	काष्ठा sec_queue_ring_cmd *msg_ring = &queue->ring_cmd;

	वापस SEC_QUEUE_LEN - atomic_पढ़ो(&msg_ring->used) >= num;
पूर्ण

अटल व्योम sec_queue_hw_init(काष्ठा sec_queue *queue)
अणु
	sec_queue_ar_alloc(queue, SEC_QUEUE_AR_FROCE_NOALLOC);
	sec_queue_aw_alloc(queue, SEC_QUEUE_AR_FROCE_NOALLOC);
	sec_queue_ar_pkgattr(queue, 1);
	sec_queue_aw_pkgattr(queue, 1);

	/* Enable out of order queue */
	sec_queue_reorder(queue, true);

	/* Interrupt after a single complete element */
	ग_लिखोl_relaxed(1, queue->regs + SEC_Q_PROC_NUM_CFG_REG);

	sec_queue_depth(queue, SEC_QUEUE_LEN - 1);

	sec_queue_cmdbase_addr(queue, queue->ring_cmd.paddr);

	sec_queue_outorder_addr(queue, queue->ring_cq.paddr);

	sec_queue_errbase_addr(queue, queue->ring_db.paddr);

	ग_लिखोl_relaxed(0x100, queue->regs + SEC_Q_OT_TH_REG);

	sec_queue_abn_irq_disable(queue);
	sec_queue_irq_disable(queue);
	ग_लिखोl_relaxed(SEC_Q_INIT_AND_STAT_CLEAR, queue->regs + SEC_Q_INIT_REG);
पूर्ण

अटल पूर्णांक sec_hw_init(काष्ठा sec_dev_info *info)
अणु
	काष्ठा iommu_करोमुख्य *करोमुख्य;
	u32 sec_ipv4_mask = 0;
	u32 sec_ipv6_mask[10] = अणुपूर्ण;
	u32 i, ret;

	करोमुख्य = iommu_get_करोमुख्य_क्रम_dev(info->dev);

	/*
	 * Enable all available processing unit घड़ीs.
	 * Only the first cluster is usable with translations.
	 */
	अगर (करोमुख्य && (करोमुख्य->type & __IOMMU_DOMAIN_PAGING))
		info->num_saas = 5;

	अन्यथा
		info->num_saas = 10;

	ग_लिखोl_relaxed(GENMASK(info->num_saas - 1, 0),
		       info->regs[SEC_SAA] + SEC_CLK_EN_REG);

	/* 32 bit little endian */
	sec_bd_endian_little(info);

	sec_cache_config(info);

	/* Data axi port ग_लिखो and पढ़ो outstanding config as per datasheet */
	sec_data_axiwr_otsd_cfg(info, 0x7);
	sec_data_axird_otsd_cfg(info, 0x7);

	/* Enable घड़ी gating */
	sec_clk_gate_en(info, true);

	/* Set CNT_CYC रेजिस्टर not पढ़ो clear */
	sec_comm_cnt_cfg(info, false);

	/* Enable CNT_CYC */
	sec_commsnap_en(info, false);

	ग_लिखोl_relaxed((u32)~0, info->regs[SEC_SAA] + SEC_FSM_MAX_CNT_REG);

	ret = sec_ipv4_hashmask(info, sec_ipv4_mask);
	अगर (ret) अणु
		dev_err(info->dev, "Failed to set ipv4 hashmask %d\n", ret);
		वापस -EIO;
	पूर्ण

	sec_ipv6_hashmask(info, sec_ipv6_mask);

	/*  करो not use debug bd */
	sec_set_dbg_bd_cfg(info, 0);

	अगर (करोमुख्य && (करोमुख्य->type & __IOMMU_DOMAIN_PAGING)) अणु
		क्रम (i = 0; i < SEC_Q_NUM; i++) अणु
			sec_streamid(info, i);
			/* Same QoS क्रम all queues */
			ग_लिखोl_relaxed(0x3f,
				       info->regs[SEC_SAA] +
				       SEC_Q_WEIGHT_CFG_REG(i));
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < info->num_saas; i++) अणु
		sec_saa_getqm_en(info, i, 1);
		sec_saa_पूर्णांक_mask(info, i, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sec_hw_निकास(काष्ठा sec_dev_info *info)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < SEC_MAX_SAA_NUM; i++) अणु
		sec_saa_पूर्णांक_mask(info, i, (u32)~0);
		sec_saa_getqm_en(info, i, 0);
	पूर्ण
पूर्ण

अटल व्योम sec_queue_base_init(काष्ठा sec_dev_info *info,
				काष्ठा sec_queue *queue, पूर्णांक queue_id)
अणु
	queue->dev_info = info;
	queue->queue_id = queue_id;
	snम_लिखो(queue->name, माप(queue->name),
		 "%s_%d", dev_name(info->dev), queue->queue_id);
पूर्ण

अटल पूर्णांक sec_map_io(काष्ठा sec_dev_info *info, काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	पूर्णांक i;

	क्रम (i = 0; i < SEC_NUM_ADDR_REGIONS; i++) अणु
		res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, i);

		अगर (!res) अणु
			dev_err(info->dev, "Memory resource %d not found\n", i);
			वापस -EINVAL;
		पूर्ण

		info->regs[i] = devm_ioremap(info->dev, res->start,
					     resource_size(res));
		अगर (!info->regs[i]) अणु
			dev_err(info->dev,
				"Memory resource %d could not be remapped\n",
				i);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sec_base_init(काष्ठा sec_dev_info *info,
			 काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;

	ret = sec_map_io(info, pdev);
	अगर (ret)
		वापस ret;

	ret = sec_clk_en(info);
	अगर (ret)
		वापस ret;

	ret = sec_reset_whole_module(info);
	अगर (ret)
		जाओ sec_clk_disable;

	ret = sec_hw_init(info);
	अगर (ret)
		जाओ sec_clk_disable;

	वापस 0;

sec_clk_disable:
	sec_clk_dis(info);

	वापस ret;
पूर्ण

अटल व्योम sec_base_निकास(काष्ठा sec_dev_info *info)
अणु
	sec_hw_निकास(info);
	sec_clk_dis(info);
पूर्ण

#घोषणा SEC_Q_CMD_SIZE \
	round_up(SEC_QUEUE_LEN * माप(काष्ठा sec_bd_info), PAGE_SIZE)
#घोषणा SEC_Q_CQ_SIZE \
	round_up(SEC_QUEUE_LEN * माप(काष्ठा sec_out_bd_info), PAGE_SIZE)
#घोषणा SEC_Q_DB_SIZE \
	round_up(SEC_QUEUE_LEN * माप(काष्ठा sec_debug_bd_info), PAGE_SIZE)

अटल पूर्णांक sec_queue_res_cfg(काष्ठा sec_queue *queue)
अणु
	काष्ठा device *dev = queue->dev_info->dev;
	काष्ठा sec_queue_ring_cmd *ring_cmd = &queue->ring_cmd;
	काष्ठा sec_queue_ring_cq *ring_cq = &queue->ring_cq;
	काष्ठा sec_queue_ring_db *ring_db = &queue->ring_db;
	पूर्णांक ret;

	ring_cmd->vaddr = dma_alloc_coherent(dev, SEC_Q_CMD_SIZE,
					     &ring_cmd->paddr, GFP_KERNEL);
	अगर (!ring_cmd->vaddr)
		वापस -ENOMEM;

	atomic_set(&ring_cmd->used, 0);
	mutex_init(&ring_cmd->lock);
	ring_cmd->callback = sec_alg_callback;

	ring_cq->vaddr = dma_alloc_coherent(dev, SEC_Q_CQ_SIZE,
					    &ring_cq->paddr, GFP_KERNEL);
	अगर (!ring_cq->vaddr) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_ring_cmd;
	पूर्ण

	ring_db->vaddr = dma_alloc_coherent(dev, SEC_Q_DB_SIZE,
					    &ring_db->paddr, GFP_KERNEL);
	अगर (!ring_db->vaddr) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_ring_cq;
	पूर्ण
	queue->task_irq = platक्रमm_get_irq(to_platक्रमm_device(dev),
					   queue->queue_id * 2 + 1);
	अगर (queue->task_irq <= 0) अणु
		ret = -EINVAL;
		जाओ err_मुक्त_ring_db;
	पूर्ण

	वापस 0;

err_मुक्त_ring_db:
	dma_मुक्त_coherent(dev, SEC_Q_DB_SIZE, queue->ring_db.vaddr,
			  queue->ring_db.paddr);
err_मुक्त_ring_cq:
	dma_मुक्त_coherent(dev, SEC_Q_CQ_SIZE, queue->ring_cq.vaddr,
			  queue->ring_cq.paddr);
err_मुक्त_ring_cmd:
	dma_मुक्त_coherent(dev, SEC_Q_CMD_SIZE, queue->ring_cmd.vaddr,
			  queue->ring_cmd.paddr);

	वापस ret;
पूर्ण

अटल व्योम sec_queue_मुक्त_ring_pages(काष्ठा sec_queue *queue)
अणु
	काष्ठा device *dev = queue->dev_info->dev;

	dma_मुक्त_coherent(dev, SEC_Q_DB_SIZE, queue->ring_db.vaddr,
			  queue->ring_db.paddr);
	dma_मुक्त_coherent(dev, SEC_Q_CQ_SIZE, queue->ring_cq.vaddr,
			  queue->ring_cq.paddr);
	dma_मुक्त_coherent(dev, SEC_Q_CMD_SIZE, queue->ring_cmd.vaddr,
			  queue->ring_cmd.paddr);
पूर्ण

अटल पूर्णांक sec_queue_config(काष्ठा sec_dev_info *info, काष्ठा sec_queue *queue,
			    पूर्णांक queue_id)
अणु
	पूर्णांक ret;

	sec_queue_base_init(info, queue, queue_id);

	ret = sec_queue_res_cfg(queue);
	अगर (ret)
		वापस ret;

	ret = sec_queue_map_io(queue);
	अगर (ret) अणु
		dev_err(info->dev, "Queue map failed %d\n", ret);
		sec_queue_मुक्त_ring_pages(queue);
		वापस ret;
	पूर्ण

	sec_queue_hw_init(queue);

	वापस 0;
पूर्ण

अटल व्योम sec_queue_unconfig(काष्ठा sec_dev_info *info,
			       काष्ठा sec_queue *queue)
अणु
	sec_queue_unmap_io(queue);
	sec_queue_मुक्त_ring_pages(queue);
पूर्ण

अटल पूर्णांक sec_id_alloc(काष्ठा sec_dev_info *info)
अणु
	पूर्णांक ret = 0;
	पूर्णांक i;

	mutex_lock(&sec_id_lock);

	क्रम (i = 0; i < SEC_MAX_DEVICES; i++)
		अगर (!sec_devices[i])
			अवरोध;
	अगर (i == SEC_MAX_DEVICES) अणु
		ret = -ENOMEM;
		जाओ unlock;
	पूर्ण
	info->sec_id = i;
	sec_devices[info->sec_id] = info;

unlock:
	mutex_unlock(&sec_id_lock);

	वापस ret;
पूर्ण

अटल व्योम sec_id_मुक्त(काष्ठा sec_dev_info *info)
अणु
	mutex_lock(&sec_id_lock);
	sec_devices[info->sec_id] = शून्य;
	mutex_unlock(&sec_id_lock);
पूर्ण

अटल पूर्णांक sec_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sec_dev_info *info;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक i, j;
	पूर्णांक ret;

	ret = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(64));
	अगर (ret) अणु
		dev_err(dev, "Failed to set 64 bit dma mask %d", ret);
		वापस -ENODEV;
	पूर्ण

	info = devm_kzalloc(dev, (माप(*info)), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	info->dev = dev;
	mutex_init(&info->dev_lock);

	info->hw_sgl_pool = dmam_pool_create("sgl", dev,
					     माप(काष्ठा sec_hw_sgl), 64, 0);
	अगर (!info->hw_sgl_pool) अणु
		dev_err(dev, "Failed to create sec sgl dma pool\n");
		वापस -ENOMEM;
	पूर्ण

	ret = sec_base_init(info, pdev);
	अगर (ret) अणु
		dev_err(dev, "Base initialization fail! %d\n", ret);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < SEC_Q_NUM; i++) अणु
		ret = sec_queue_config(info, &info->queues[i], i);
		अगर (ret)
			जाओ queues_unconfig;

		ret = sec_queue_irq_init(&info->queues[i]);
		अगर (ret) अणु
			sec_queue_unconfig(info, &info->queues[i]);
			जाओ queues_unconfig;
		पूर्ण
	पूर्ण

	ret = sec_algs_रेजिस्टर();
	अगर (ret) अणु
		dev_err(dev, "Failed to register algorithms with crypto %d\n",
			ret);
		जाओ queues_unconfig;
	पूर्ण

	platक्रमm_set_drvdata(pdev, info);

	ret = sec_id_alloc(info);
	अगर (ret)
		जाओ algs_unरेजिस्टर;

	वापस 0;

algs_unरेजिस्टर:
	sec_algs_unरेजिस्टर();
queues_unconfig:
	क्रम (j = i - 1; j >= 0; j--) अणु
		sec_queue_irq_uninit(&info->queues[j]);
		sec_queue_unconfig(info, &info->queues[j]);
	पूर्ण
	sec_base_निकास(info);

	वापस ret;
पूर्ण

अटल पूर्णांक sec_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sec_dev_info *info = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	/* Unexpose as soon as possible, reuse during हटाओ is fine */
	sec_id_मुक्त(info);

	sec_algs_unरेजिस्टर();

	क्रम (i = 0; i < SEC_Q_NUM; i++) अणु
		sec_queue_irq_uninit(&info->queues[i]);
		sec_queue_unconfig(info, &info->queues[i]);
	पूर्ण

	sec_base_निकास(info);

	वापस 0;
पूर्ण

अटल स्थिर __maybe_unused काष्ठा of_device_id sec_match[] = अणु
	अणु .compatible = "hisilicon,hip06-sec" पूर्ण,
	अणु .compatible = "hisilicon,hip07-sec" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sec_match);

अटल स्थिर __maybe_unused काष्ठा acpi_device_id sec_acpi_match[] = अणु
	अणु "HISI02C1", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, sec_acpi_match);

अटल काष्ठा platक्रमm_driver sec_driver = अणु
	.probe = sec_probe,
	.हटाओ = sec_हटाओ,
	.driver = अणु
		.name = "hisi_sec_platform_driver",
		.of_match_table = sec_match,
		.acpi_match_table = ACPI_PTR(sec_acpi_match),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sec_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("HiSilicon Security Accelerators");
MODULE_AUTHOR("Zaibo Xu <xuzaibo@huawei.com");
MODULE_AUTHOR("Jonathan Cameron <jonathan.cameron@huawei.com>");
