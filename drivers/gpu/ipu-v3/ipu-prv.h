<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (c) 2010 Sascha Hauer <s.hauer@pengutronix.de>
 * Copyright (C) 2005-2009 Freescale Semiconductor, Inc.
 */
#अगर_अघोषित __IPU_PRV_H__
#घोषणा __IPU_PRV_H__

काष्ठा ipu_soc;

#समावेश <linux/types.h>
#समावेश <linux/device.h>
#समावेश <linux/clk.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <video/imx-ipu-v3.h>

#घोषणा IPU_MCU_T_DEFAULT	8
#घोषणा IPU_CM_IDMAC_REG_OFS	0x00008000
#घोषणा IPU_CM_IC_REG_OFS	0x00020000
#घोषणा IPU_CM_IRT_REG_OFS	0x00028000
#घोषणा IPU_CM_CSI0_REG_OFS	0x00030000
#घोषणा IPU_CM_CSI1_REG_OFS	0x00038000
#घोषणा IPU_CM_SMFC_REG_OFS	0x00050000
#घोषणा IPU_CM_DC_REG_OFS	0x00058000
#घोषणा IPU_CM_DMFC_REG_OFS	0x00060000

/* Register addresses */
/* IPU Common रेजिस्टरs */
#घोषणा IPU_CM_REG(offset)	(offset)

#घोषणा IPU_CONF			IPU_CM_REG(0)

#घोषणा IPU_SRM_PRI1			IPU_CM_REG(0x00a0)
#घोषणा IPU_SRM_PRI2			IPU_CM_REG(0x00a4)
#घोषणा IPU_FS_PROC_FLOW1		IPU_CM_REG(0x00a8)
#घोषणा IPU_FS_PROC_FLOW2		IPU_CM_REG(0x00ac)
#घोषणा IPU_FS_PROC_FLOW3		IPU_CM_REG(0x00b0)
#घोषणा IPU_FS_DISP_FLOW1		IPU_CM_REG(0x00b4)
#घोषणा IPU_FS_DISP_FLOW2		IPU_CM_REG(0x00b8)
#घोषणा IPU_SKIP			IPU_CM_REG(0x00bc)
#घोषणा IPU_DISP_ALT_CONF		IPU_CM_REG(0x00c0)
#घोषणा IPU_DISP_GEN			IPU_CM_REG(0x00c4)
#घोषणा IPU_DISP_ALT1			IPU_CM_REG(0x00c8)
#घोषणा IPU_DISP_ALT2			IPU_CM_REG(0x00cc)
#घोषणा IPU_DISP_ALT3			IPU_CM_REG(0x00d0)
#घोषणा IPU_DISP_ALT4			IPU_CM_REG(0x00d4)
#घोषणा IPU_SNOOP			IPU_CM_REG(0x00d8)
#घोषणा IPU_MEM_RST			IPU_CM_REG(0x00dc)
#घोषणा IPU_PM				IPU_CM_REG(0x00e0)
#घोषणा IPU_GPR				IPU_CM_REG(0x00e4)
#घोषणा IPU_CHA_DB_MODE_SEL(ch)		IPU_CM_REG(0x0150 + 4 * ((ch) / 32))
#घोषणा IPU_ALT_CHA_DB_MODE_SEL(ch)	IPU_CM_REG(0x0168 + 4 * ((ch) / 32))
#घोषणा IPU_CHA_CUR_BUF(ch)		IPU_CM_REG(0x023C + 4 * ((ch) / 32))
#घोषणा IPU_ALT_CUR_BUF0		IPU_CM_REG(0x0244)
#घोषणा IPU_ALT_CUR_BUF1		IPU_CM_REG(0x0248)
#घोषणा IPU_SRM_STAT			IPU_CM_REG(0x024C)
#घोषणा IPU_PROC_TASK_STAT		IPU_CM_REG(0x0250)
#घोषणा IPU_DISP_TASK_STAT		IPU_CM_REG(0x0254)
#घोषणा IPU_CHA_BUF0_RDY(ch)		IPU_CM_REG(0x0268 + 4 * ((ch) / 32))
#घोषणा IPU_CHA_BUF1_RDY(ch)		IPU_CM_REG(0x0270 + 4 * ((ch) / 32))
#घोषणा IPU_CHA_BUF2_RDY(ch)		IPU_CM_REG(0x0288 + 4 * ((ch) / 32))
#घोषणा IPU_ALT_CHA_BUF0_RDY(ch)	IPU_CM_REG(0x0278 + 4 * ((ch) / 32))
#घोषणा IPU_ALT_CHA_BUF1_RDY(ch)	IPU_CM_REG(0x0280 + 4 * ((ch) / 32))

#घोषणा IPU_INT_CTRL(n)		IPU_CM_REG(0x003C + 4 * (n))
#घोषणा IPU_INT_STAT(n)		IPU_CM_REG(0x0200 + 4 * (n))

/* SRM_PRI2 */
#घोषणा DP_S_SRM_MODE_MASK		(0x3 << 3)
#घोषणा DP_S_SRM_MODE_NOW		(0x3 << 3)
#घोषणा DP_S_SRM_MODE_NEXT_FRAME	(0x1 << 3)

/* FS_PROC_FLOW1 */
#घोषणा FS_PRPENC_ROT_SRC_SEL_MASK	(0xf << 0)
#घोषणा FS_PRPENC_ROT_SRC_SEL_ENC		(0x7 << 0)
#घोषणा FS_PRPVF_ROT_SRC_SEL_MASK	(0xf << 8)
#घोषणा FS_PRPVF_ROT_SRC_SEL_VF			(0x8 << 8)
#घोषणा FS_PP_SRC_SEL_MASK		(0xf << 12)
#घोषणा FS_PP_ROT_SRC_SEL_MASK		(0xf << 16)
#घोषणा FS_PP_ROT_SRC_SEL_PP			(0x5 << 16)
#घोषणा FS_VDI1_SRC_SEL_MASK		(0x3 << 20)
#घोषणा FS_VDI3_SRC_SEL_MASK		(0x3 << 20)
#घोषणा FS_PRP_SRC_SEL_MASK		(0xf << 24)
#घोषणा FS_VDI_SRC_SEL_MASK		(0x3 << 28)
#घोषणा FS_VDI_SRC_SEL_CSI_सूचीECT		(0x1 << 28)
#घोषणा FS_VDI_SRC_SEL_VDOA			(0x2 << 28)

/* FS_PROC_FLOW2 */
#घोषणा FS_PRP_ENC_DEST_SEL_MASK	(0xf << 0)
#घोषणा FS_PRP_ENC_DEST_SEL_IRT_ENC		(0x1 << 0)
#घोषणा FS_PRPVF_DEST_SEL_MASK		(0xf << 4)
#घोषणा FS_PRPVF_DEST_SEL_IRT_VF		(0x1 << 4)
#घोषणा FS_PRPVF_ROT_DEST_SEL_MASK	(0xf << 8)
#घोषणा FS_PP_DEST_SEL_MASK		(0xf << 12)
#घोषणा FS_PP_DEST_SEL_IRT_PP			(0x3 << 12)
#घोषणा FS_PP_ROT_DEST_SEL_MASK		(0xf << 16)
#घोषणा FS_PRPENC_ROT_DEST_SEL_MASK	(0xf << 20)
#घोषणा FS_PRP_DEST_SEL_MASK		(0xf << 24)

#घोषणा IPU_DI0_COUNTER_RELEASE			(1 << 24)
#घोषणा IPU_DI1_COUNTER_RELEASE			(1 << 25)

#घोषणा IPU_IDMAC_REG(offset)	(offset)

#घोषणा IDMAC_CONF			IPU_IDMAC_REG(0x0000)
#घोषणा IDMAC_CHA_EN(ch)		IPU_IDMAC_REG(0x0004 + 4 * ((ch) / 32))
#घोषणा IDMAC_SEP_ALPHA			IPU_IDMAC_REG(0x000c)
#घोषणा IDMAC_ALT_SEP_ALPHA		IPU_IDMAC_REG(0x0010)
#घोषणा IDMAC_CHA_PRI(ch)		IPU_IDMAC_REG(0x0014 + 4 * ((ch) / 32))
#घोषणा IDMAC_WM_EN(ch)			IPU_IDMAC_REG(0x001c + 4 * ((ch) / 32))
#घोषणा IDMAC_CH_LOCK_EN_1		IPU_IDMAC_REG(0x0024)
#घोषणा IDMAC_CH_LOCK_EN_2		IPU_IDMAC_REG(0x0028)
#घोषणा IDMAC_SUB_ADDR_0		IPU_IDMAC_REG(0x002c)
#घोषणा IDMAC_SUB_ADDR_1		IPU_IDMAC_REG(0x0030)
#घोषणा IDMAC_SUB_ADDR_2		IPU_IDMAC_REG(0x0034)
#घोषणा IDMAC_BAND_EN(ch)		IPU_IDMAC_REG(0x0040 + 4 * ((ch) / 32))
#घोषणा IDMAC_CHA_BUSY(ch)		IPU_IDMAC_REG(0x0100 + 4 * ((ch) / 32))

#घोषणा IPU_NUM_IRQS	(32 * 15)

क्रमागत ipu_modules अणु
	IPU_CONF_CSI0_EN		= (1 << 0),
	IPU_CONF_CSI1_EN		= (1 << 1),
	IPU_CONF_IC_EN			= (1 << 2),
	IPU_CONF_ROT_EN			= (1 << 3),
	IPU_CONF_ISP_EN			= (1 << 4),
	IPU_CONF_DP_EN			= (1 << 5),
	IPU_CONF_DI0_EN			= (1 << 6),
	IPU_CONF_DI1_EN			= (1 << 7),
	IPU_CONF_SMFC_EN		= (1 << 8),
	IPU_CONF_DC_EN			= (1 << 9),
	IPU_CONF_DMFC_EN		= (1 << 10),

	IPU_CONF_VDI_EN			= (1 << 12),

	IPU_CONF_IDMAC_DIS		= (1 << 22),

	IPU_CONF_IC_DMFC_SEL		= (1 << 25),
	IPU_CONF_IC_DMFC_SYNC		= (1 << 26),
	IPU_CONF_VDI_DMFC_SYNC		= (1 << 27),

	IPU_CONF_CSI0_DATA_SOURCE	= (1 << 28),
	IPU_CONF_CSI1_DATA_SOURCE	= (1 << 29),
	IPU_CONF_IC_INPUT		= (1 << 30),
	IPU_CONF_CSI_SEL		= (1 << 31),
पूर्ण;

काष्ठा ipuv3_channel अणु
	अचिन्हित पूर्णांक num;
	काष्ठा ipu_soc *ipu;
	काष्ठा list_head list;
पूर्ण;

काष्ठा ipu_cpmem;
काष्ठा ipu_csi;
काष्ठा ipu_dc_priv;
काष्ठा ipu_dmfc_priv;
काष्ठा ipu_di;
काष्ठा ipu_ic_priv;
काष्ठा ipu_vdi;
काष्ठा ipu_image_convert_priv;
काष्ठा ipu_smfc_priv;
काष्ठा ipu_pre;
काष्ठा ipu_prg;

काष्ठा ipu_devtype;

काष्ठा ipu_soc अणु
	काष्ठा device		*dev;
	स्थिर काष्ठा ipu_devtype	*devtype;
	क्रमागत ipuv3_type		ipu_type;
	spinlock_t		lock;
	काष्ठा mutex		channel_lock;
	काष्ठा list_head	channels;

	व्योम __iomem		*cm_reg;
	व्योम __iomem		*idmac_reg;

	पूर्णांक			id;
	पूर्णांक			usecount;

	काष्ठा clk		*clk;

	पूर्णांक			irq_sync;
	पूर्णांक			irq_err;
	काष्ठा irq_करोमुख्य	*करोमुख्य;

	काष्ठा ipu_cpmem	*cpmem_priv;
	काष्ठा ipu_dc_priv	*dc_priv;
	काष्ठा ipu_dp_priv	*dp_priv;
	काष्ठा ipu_dmfc_priv	*dmfc_priv;
	काष्ठा ipu_di		*di_priv[2];
	काष्ठा ipu_csi		*csi_priv[2];
	काष्ठा ipu_ic_priv	*ic_priv;
	काष्ठा ipu_vdi          *vdi_priv;
	काष्ठा ipu_image_convert_priv *image_convert_priv;
	काष्ठा ipu_smfc_priv	*smfc_priv;
	काष्ठा ipu_prg		*prg_priv;
पूर्ण;

अटल अंतरभूत u32 ipu_idmac_पढ़ो(काष्ठा ipu_soc *ipu, अचिन्हित offset)
अणु
	वापस पढ़ोl(ipu->idmac_reg + offset);
पूर्ण

अटल अंतरभूत व्योम ipu_idmac_ग_लिखो(काष्ठा ipu_soc *ipu, u32 value,
				   अचिन्हित offset)
अणु
	ग_लिखोl(value, ipu->idmac_reg + offset);
पूर्ण

व्योम ipu_srm_dp_update(काष्ठा ipu_soc *ipu, bool sync);

पूर्णांक ipu_module_enable(काष्ठा ipu_soc *ipu, u32 mask);
पूर्णांक ipu_module_disable(काष्ठा ipu_soc *ipu, u32 mask);

bool ipu_idmac_channel_busy(काष्ठा ipu_soc *ipu, अचिन्हित पूर्णांक chno);

पूर्णांक ipu_csi_init(काष्ठा ipu_soc *ipu, काष्ठा device *dev, पूर्णांक id,
		 अचिन्हित दीर्घ base, u32 module, काष्ठा clk *clk_ipu);
व्योम ipu_csi_निकास(काष्ठा ipu_soc *ipu, पूर्णांक id);

पूर्णांक ipu_ic_init(काष्ठा ipu_soc *ipu, काष्ठा device *dev,
		अचिन्हित दीर्घ base, अचिन्हित दीर्घ tpmem_base);
व्योम ipu_ic_निकास(काष्ठा ipu_soc *ipu);

पूर्णांक ipu_vdi_init(काष्ठा ipu_soc *ipu, काष्ठा device *dev,
		 अचिन्हित दीर्घ base, u32 module);
व्योम ipu_vdi_निकास(काष्ठा ipu_soc *ipu);

पूर्णांक ipu_image_convert_init(काष्ठा ipu_soc *ipu, काष्ठा device *dev);
व्योम ipu_image_convert_निकास(काष्ठा ipu_soc *ipu);

पूर्णांक ipu_di_init(काष्ठा ipu_soc *ipu, काष्ठा device *dev, पूर्णांक id,
		अचिन्हित दीर्घ base, u32 module, काष्ठा clk *ipu_clk);
व्योम ipu_di_निकास(काष्ठा ipu_soc *ipu, पूर्णांक id);

पूर्णांक ipu_dmfc_init(काष्ठा ipu_soc *ipu, काष्ठा device *dev, अचिन्हित दीर्घ base,
		काष्ठा clk *ipu_clk);
व्योम ipu_dmfc_निकास(काष्ठा ipu_soc *ipu);

पूर्णांक ipu_dp_init(काष्ठा ipu_soc *ipu, काष्ठा device *dev, अचिन्हित दीर्घ base);
व्योम ipu_dp_निकास(काष्ठा ipu_soc *ipu);

पूर्णांक ipu_dc_init(काष्ठा ipu_soc *ipu, काष्ठा device *dev, अचिन्हित दीर्घ base,
		अचिन्हित दीर्घ ढाँचा_base);
व्योम ipu_dc_निकास(काष्ठा ipu_soc *ipu);

पूर्णांक ipu_cpmem_init(काष्ठा ipu_soc *ipu, काष्ठा device *dev, अचिन्हित दीर्घ base);
व्योम ipu_cpmem_निकास(काष्ठा ipu_soc *ipu);

पूर्णांक ipu_smfc_init(काष्ठा ipu_soc *ipu, काष्ठा device *dev, अचिन्हित दीर्घ base);
व्योम ipu_smfc_निकास(काष्ठा ipu_soc *ipu);

काष्ठा ipu_pre *ipu_pre_lookup_by_phandle(काष्ठा device *dev, स्थिर अक्षर *name,
					  पूर्णांक index);
पूर्णांक ipu_pre_get_available_count(व्योम);
पूर्णांक ipu_pre_get(काष्ठा ipu_pre *pre);
व्योम ipu_pre_put(काष्ठा ipu_pre *pre);
u32 ipu_pre_get_baddr(काष्ठा ipu_pre *pre);
व्योम ipu_pre_configure(काष्ठा ipu_pre *pre, अचिन्हित पूर्णांक width,
		       अचिन्हित पूर्णांक height, अचिन्हित पूर्णांक stride, u32 क्रमmat,
		       uपूर्णांक64_t modअगरier, अचिन्हित पूर्णांक bufaddr);
व्योम ipu_pre_update(काष्ठा ipu_pre *pre, अचिन्हित पूर्णांक bufaddr);
bool ipu_pre_update_pending(काष्ठा ipu_pre *pre);

काष्ठा ipu_prg *ipu_prg_lookup_by_phandle(काष्ठा device *dev, स्थिर अक्षर *name,
					  पूर्णांक ipu_id);

बाह्य काष्ठा platक्रमm_driver ipu_pre_drv;
बाह्य काष्ठा platक्रमm_driver ipu_prg_drv;

#पूर्ण_अगर				/* __IPU_PRV_H__ */
