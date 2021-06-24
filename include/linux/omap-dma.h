<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_OMAP_DMA_H
#घोषणा __LINUX_OMAP_DMA_H
/*
 *  Legacy OMAP DMA handling defines and functions
 *
 *  NOTE: Do not use these any दीर्घer.
 *
 *  Use the generic dmaengine functions as defined in
 *  include/linux/dmaengine.h.
 *
 *  Copyright (C) 2003 Nokia Corporation
 *  Author: Juha Yrjथघlथअ <juha.yrjola@nokia.com>
 *
 */

#समावेश <linux/platक्रमm_device.h>

#घोषणा INT_DMA_LCD			(NR_IRQS_LEGACY + 25)

#घोषणा OMAP1_DMA_TOUT_IRQ		(1 << 0)
#घोषणा OMAP_DMA_DROP_IRQ		(1 << 1)
#घोषणा OMAP_DMA_HALF_IRQ		(1 << 2)
#घोषणा OMAP_DMA_FRAME_IRQ		(1 << 3)
#घोषणा OMAP_DMA_LAST_IRQ		(1 << 4)
#घोषणा OMAP_DMA_BLOCK_IRQ		(1 << 5)
#घोषणा OMAP1_DMA_SYNC_IRQ		(1 << 6)
#घोषणा OMAP2_DMA_PKT_IRQ		(1 << 7)
#घोषणा OMAP2_DMA_TRANS_ERR_IRQ		(1 << 8)
#घोषणा OMAP2_DMA_SECURE_ERR_IRQ	(1 << 9)
#घोषणा OMAP2_DMA_SUPERVISOR_ERR_IRQ	(1 << 10)
#घोषणा OMAP2_DMA_MISALIGNED_ERR_IRQ	(1 << 11)

#घोषणा OMAP_DMA_CCR_EN			(1 << 7)
#घोषणा OMAP_DMA_CCR_RD_ACTIVE		(1 << 9)
#घोषणा OMAP_DMA_CCR_WR_ACTIVE		(1 << 10)
#घोषणा OMAP_DMA_CCR_SEL_SRC_DST_SYNC	(1 << 24)
#घोषणा OMAP_DMA_CCR_BUFFERING_DISABLE	(1 << 25)

#घोषणा OMAP_DMA_DATA_TYPE_S8		0x00
#घोषणा OMAP_DMA_DATA_TYPE_S16		0x01
#घोषणा OMAP_DMA_DATA_TYPE_S32		0x02

#घोषणा OMAP_DMA_SYNC_ELEMENT		0x00
#घोषणा OMAP_DMA_SYNC_FRAME		0x01
#घोषणा OMAP_DMA_SYNC_BLOCK		0x02
#घोषणा OMAP_DMA_SYNC_PACKET		0x03

#घोषणा OMAP_DMA_DST_SYNC_PREFETCH	0x02
#घोषणा OMAP_DMA_SRC_SYNC		0x01
#घोषणा OMAP_DMA_DST_SYNC		0x00

#घोषणा OMAP_DMA_PORT_EMIFF		0x00
#घोषणा OMAP_DMA_PORT_EMIFS		0x01
#घोषणा OMAP_DMA_PORT_OCP_T1		0x02
#घोषणा OMAP_DMA_PORT_TIPB		0x03
#घोषणा OMAP_DMA_PORT_OCP_T2		0x04
#घोषणा OMAP_DMA_PORT_MPUI		0x05

#घोषणा OMAP_DMA_AMODE_CONSTANT		0x00
#घोषणा OMAP_DMA_AMODE_POST_INC		0x01
#घोषणा OMAP_DMA_AMODE_SINGLE_IDX	0x02
#घोषणा OMAP_DMA_AMODE_DOUBLE_IDX	0x03

#घोषणा DMA_DEFAULT_FIFO_DEPTH		0x10
#घोषणा DMA_DEFAULT_ARB_RATE		0x01
/* Pass THREAD_RESERVE ORed with THREAD_FIFO क्रम tparams */
#घोषणा DMA_THREAD_RESERVE_NORM		(0x00 << 12) /* Def */
#घोषणा DMA_THREAD_RESERVE_ONET		(0x01 << 12)
#घोषणा DMA_THREAD_RESERVE_TWOT		(0x02 << 12)
#घोषणा DMA_THREAD_RESERVE_THREET	(0x03 << 12)
#घोषणा DMA_THREAD_FIFO_NONE		(0x00 << 14) /* Def */
#घोषणा DMA_THREAD_FIFO_75		(0x01 << 14)
#घोषणा DMA_THREAD_FIFO_25		(0x02 << 14)
#घोषणा DMA_THREAD_FIFO_50		(0x03 << 14)

/* DMA4_OCP_SYSCONFIG bits */
#घोषणा DMA_SYSCONFIG_MIDLEMODE_MASK		(3 << 12)
#घोषणा DMA_SYSCONFIG_CLOCKACTIVITY_MASK	(3 << 8)
#घोषणा DMA_SYSCONFIG_EMUFREE			(1 << 5)
#घोषणा DMA_SYSCONFIG_SIDLEMODE_MASK		(3 << 3)
#घोषणा DMA_SYSCONFIG_SOFTRESET			(1 << 2)
#घोषणा DMA_SYSCONFIG_AUTOIDLE			(1 << 0)

#घोषणा DMA_SYSCONFIG_MIDLEMODE(n)		((n) << 12)
#घोषणा DMA_SYSCONFIG_SIDLEMODE(n)		((n) << 3)

#घोषणा DMA_IDLEMODE_SMARTIDLE			0x2
#घोषणा DMA_IDLEMODE_NO_IDLE			0x1
#घोषणा DMA_IDLEMODE_FORCE_IDLE			0x0

/* Chaining modes*/
#अगर_अघोषित CONFIG_ARCH_OMAP1
#घोषणा OMAP_DMA_STATIC_CHAIN		0x1
#घोषणा OMAP_DMA_DYNAMIC_CHAIN		0x2
#घोषणा OMAP_DMA_CHAIN_ACTIVE		0x1
#घोषणा OMAP_DMA_CHAIN_INACTIVE		0x0
#पूर्ण_अगर

#घोषणा DMA_CH_PRIO_HIGH		0x1
#घोषणा DMA_CH_PRIO_LOW			0x0 /* Def */

/* Errata handling */
#घोषणा IS_DMA_ERRATA(id)		(errata & (id))
#घोषणा SET_DMA_ERRATA(id)		(errata |= (id))

#घोषणा DMA_ERRATA_IFRAME_BUFFERING	BIT(0x0)
#घोषणा DMA_ERRATA_PARALLEL_CHANNELS	BIT(0x1)
#घोषणा DMA_ERRATA_i378			BIT(0x2)
#घोषणा DMA_ERRATA_i541			BIT(0x3)
#घोषणा DMA_ERRATA_i88			BIT(0x4)
#घोषणा DMA_ERRATA_3_3			BIT(0x5)
#घोषणा DMA_ROMCODE_BUG			BIT(0x6)

/* Attributes क्रम OMAP DMA Contrller */
#घोषणा DMA_LINKED_LCH			BIT(0x0)
#घोषणा GLOBAL_PRIORITY			BIT(0x1)
#घोषणा RESERVE_CHANNEL			BIT(0x2)
#घोषणा IS_CSSA_32			BIT(0x3)
#घोषणा IS_CDSA_32			BIT(0x4)
#घोषणा IS_RW_PRIORITY			BIT(0x5)
#घोषणा ENABLE_1510_MODE		BIT(0x6)
#घोषणा SRC_PORT			BIT(0x7)
#घोषणा DST_PORT			BIT(0x8)
#घोषणा SRC_INDEX			BIT(0x9)
#घोषणा DST_INDEX			BIT(0xa)
#घोषणा IS_BURST_ONLY4			BIT(0xb)
#घोषणा CLEAR_CSR_ON_READ		BIT(0xc)
#घोषणा IS_WORD_16			BIT(0xd)
#घोषणा ENABLE_16XX_MODE		BIT(0xe)
#घोषणा HS_CHANNELS_RESERVED		BIT(0xf)

/* Defines क्रम DMA Capabilities */
#घोषणा DMA_HAS_TRANSPARENT_CAPS	(0x1 << 18)
#घोषणा DMA_HAS_CONSTANT_FILL_CAPS	(0x1 << 19)
#घोषणा DMA_HAS_DESCRIPTOR_CAPS		(0x3 << 20)

क्रमागत omap_reg_offsets अणु

GCR,		GSCR,		GRST1,		HW_ID,
PCH2_ID,	PCH0_ID,	PCH1_ID,	PCHG_ID,
PCHD_ID,	CAPS_0,		CAPS_1,		CAPS_2,
CAPS_3,		CAPS_4,		PCH2_SR,	PCH0_SR,
PCH1_SR,	PCHD_SR,	REVISION,	IRQSTATUS_L0,
IRQSTATUS_L1,	IRQSTATUS_L2,	IRQSTATUS_L3,	IRQENABLE_L0,
IRQENABLE_L1,	IRQENABLE_L2,	IRQENABLE_L3,	SYSSTATUS,
OCP_SYSCONFIG,

/* omap1+ specअगरic */
CPC, CCR2, LCH_CTRL,

/* Common रेजिस्टरs क्रम all omap's */
CSDP,		CCR,		CICR,		CSR,
CEN,		CFN,		CSFI,		CSEI,
CSAC,		CDAC,		CDEI,
CDFI,		CLNK_CTRL,

/* Channel specअगरic रेजिस्टरs */
CSSA,		CDSA,		COLOR,
CCEN,		CCFN,

/* omap3630 and omap4 specअगरic */
CDP,		CNDP,		CCDN,

पूर्ण;

क्रमागत omap_dma_burst_mode अणु
	OMAP_DMA_DATA_BURST_DIS = 0,
	OMAP_DMA_DATA_BURST_4,
	OMAP_DMA_DATA_BURST_8,
	OMAP_DMA_DATA_BURST_16,
पूर्ण;

क्रमागत end_type अणु
	OMAP_DMA_LITTLE_ENDIAN = 0,
	OMAP_DMA_BIG_ENDIAN
पूर्ण;

क्रमागत omap_dma_color_mode अणु
	OMAP_DMA_COLOR_DIS = 0,
	OMAP_DMA_CONSTANT_FILL,
	OMAP_DMA_TRANSPARENT_COPY
पूर्ण;

क्रमागत omap_dma_ग_लिखो_mode अणु
	OMAP_DMA_WRITE_NON_POSTED = 0,
	OMAP_DMA_WRITE_POSTED,
	OMAP_DMA_WRITE_LAST_NON_POSTED
पूर्ण;

क्रमागत omap_dma_channel_mode अणु
	OMAP_DMA_LCH_2D = 0,
	OMAP_DMA_LCH_G,
	OMAP_DMA_LCH_P,
	OMAP_DMA_LCH_PD
पूर्ण;

काष्ठा omap_dma_channel_params अणु
	पूर्णांक data_type;		/* data type 8,16,32 */
	पूर्णांक elem_count;		/* number of elements in a frame */
	पूर्णांक frame_count;	/* number of frames in a element */

	पूर्णांक src_port;		/* Only on OMAP1 REVISIT: Is this needed? */
	पूर्णांक src_amode;		/* स्थिरant, post increment, indexed,
					द्विगुन indexed */
	अचिन्हित दीर्घ src_start;	/* source address : physical */
	पूर्णांक src_ei;		/* source element index */
	पूर्णांक src_fi;		/* source frame index */

	पूर्णांक dst_port;		/* Only on OMAP1 REVISIT: Is this needed? */
	पूर्णांक dst_amode;		/* स्थिरant, post increment, indexed,
					द्विगुन indexed */
	अचिन्हित दीर्घ dst_start;	/* source address : physical */
	पूर्णांक dst_ei;		/* source element index */
	पूर्णांक dst_fi;		/* source frame index */

	पूर्णांक trigger;		/* trigger attached अगर the channel is
					synchronized */
	पूर्णांक sync_mode;		/* sycn on element, frame , block or packet */
	पूर्णांक src_or_dst_synch;	/* source synch(1) or destination synch(0) */

	पूर्णांक ie;			/* पूर्णांकerrupt enabled */

	अचिन्हित अक्षर पढ़ो_prio;/* पढ़ो priority */
	अचिन्हित अक्षर ग_लिखो_prio;/* ग_लिखो priority */

#अगर_अघोषित CONFIG_ARCH_OMAP1
	क्रमागत omap_dma_burst_mode burst_mode; /* Burst mode 4/8/16 words */
#पूर्ण_अगर
पूर्ण;

काष्ठा omap_dma_lch अणु
	पूर्णांक next_lch;
	पूर्णांक dev_id;
	u16 saved_csr;
	u16 enabled_irqs;
	स्थिर अक्षर *dev_name;
	व्योम (*callback)(पूर्णांक lch, u16 ch_status, व्योम *data);
	व्योम *data;
	दीर्घ flags;
	पूर्णांक state;
	पूर्णांक chain_id;
	पूर्णांक status;
पूर्ण;

काष्ठा omap_dma_dev_attr अणु
	u32 dev_caps;
	u16 lch_count;
	u16 chan_count;
पूर्ण;

क्रमागत अणु
	OMAP_DMA_REG_NONE,
	OMAP_DMA_REG_16BIT,
	OMAP_DMA_REG_2X16BIT,
	OMAP_DMA_REG_32BIT,
पूर्ण;

काष्ठा omap_dma_reg अणु
	u16	offset;
	u8	stride;
	u8	type;
पूर्ण;

#घोषणा SDMA_FILTER_PARAM(hw_req)	((पूर्णांक[]) अणु (hw_req) पूर्ण)
काष्ठा dma_slave_map;

/* System DMA platक्रमm data काष्ठाure */
काष्ठा omap_प्रणाली_dma_plat_info अणु
	स्थिर काष्ठा omap_dma_reg *reg_map;
	अचिन्हित channel_stride;
	काष्ठा omap_dma_dev_attr *dma_attr;
	u32 errata;
	व्योम (*show_dma_caps)(व्योम);
	व्योम (*clear_lch_regs)(पूर्णांक lch);
	व्योम (*clear_dma)(पूर्णांक lch);
	व्योम (*dma_ग_लिखो)(u32 val, पूर्णांक reg, पूर्णांक lch);
	u32 (*dma_पढ़ो)(पूर्णांक reg, पूर्णांक lch);

	स्थिर काष्ठा dma_slave_map *slave_map;
	पूर्णांक slavecnt;
पूर्ण;

#अगर_घोषित CONFIG_ARCH_OMAP2PLUS
#घोषणा dma_omap2plus()	1
#अन्यथा
#घोषणा dma_omap2plus()	0
#पूर्ण_अगर
#घोषणा dma_omap1()	(!dma_omap2plus())
#घोषणा __dma_omap15xx(d) (dma_omap1() && (d)->dev_caps & ENABLE_1510_MODE)
#घोषणा __dma_omap16xx(d) (dma_omap1() && (d)->dev_caps & ENABLE_16XX_MODE)
#घोषणा dma_omap15xx()	__dma_omap15xx(d)
#घोषणा dma_omap16xx()	__dma_omap16xx(d)

#अगर defined(CONFIG_ARCH_OMAP)
बाह्य काष्ठा omap_प्रणाली_dma_plat_info *omap_get_plat_info(व्योम);

बाह्य व्योम omap_set_dma_priority(पूर्णांक lch, पूर्णांक dst_port, पूर्णांक priority);
बाह्य पूर्णांक omap_request_dma(पूर्णांक dev_id, स्थिर अक्षर *dev_name,
			व्योम (*callback)(पूर्णांक lch, u16 ch_status, व्योम *data),
			व्योम *data, पूर्णांक *dma_ch);
बाह्य व्योम omap_disable_dma_irq(पूर्णांक ch, u16 irq_bits);
बाह्य व्योम omap_मुक्त_dma(पूर्णांक ch);
बाह्य व्योम omap_start_dma(पूर्णांक lch);
बाह्य व्योम omap_stop_dma(पूर्णांक lch);
बाह्य व्योम omap_set_dma_transfer_params(पूर्णांक lch, पूर्णांक data_type,
					 पूर्णांक elem_count, पूर्णांक frame_count,
					 पूर्णांक sync_mode,
					 पूर्णांक dma_trigger, पूर्णांक src_or_dst_synch);
बाह्य व्योम omap_set_dma_channel_mode(पूर्णांक lch, क्रमागत omap_dma_channel_mode mode);

बाह्य व्योम omap_set_dma_src_params(पूर्णांक lch, पूर्णांक src_port, पूर्णांक src_amode,
				    अचिन्हित दीर्घ src_start,
				    पूर्णांक src_ei, पूर्णांक src_fi);
बाह्य व्योम omap_set_dma_src_data_pack(पूर्णांक lch, पूर्णांक enable);
बाह्य व्योम omap_set_dma_src_burst_mode(पूर्णांक lch,
					क्रमागत omap_dma_burst_mode burst_mode);

बाह्य व्योम omap_set_dma_dest_params(पूर्णांक lch, पूर्णांक dest_port, पूर्णांक dest_amode,
				     अचिन्हित दीर्घ dest_start,
				     पूर्णांक dst_ei, पूर्णांक dst_fi);
बाह्य व्योम omap_set_dma_dest_data_pack(पूर्णांक lch, पूर्णांक enable);
बाह्य व्योम omap_set_dma_dest_burst_mode(पूर्णांक lch,
					 क्रमागत omap_dma_burst_mode burst_mode);

बाह्य dma_addr_t omap_get_dma_src_pos(पूर्णांक lch);
बाह्य dma_addr_t omap_get_dma_dst_pos(पूर्णांक lch);
बाह्य पूर्णांक omap_get_dma_active_status(पूर्णांक lch);
बाह्य पूर्णांक omap_dma_running(व्योम);

#अगर defined(CONFIG_ARCH_OMAP1) && IS_ENABLED(CONFIG_FB_OMAP)
#समावेश <mach/lcd_dma.h>
#अन्यथा
अटल अंतरभूत पूर्णांक omap_lcd_dma_running(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अन्यथा /* CONFIG_ARCH_OMAP */

अटल अंतरभूत काष्ठा omap_प्रणाली_dma_plat_info *omap_get_plat_info(व्योम)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक omap_request_dma(पूर्णांक dev_id, स्थिर अक्षर *dev_name,
			व्योम (*callback)(पूर्णांक lch, u16 ch_status, व्योम *data),
			व्योम *data, पूर्णांक *dma_ch)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत व्योम omap_मुक्त_dma(पूर्णांक ch) अणु पूर्ण

#पूर्ण_अगर /* CONFIG_ARCH_OMAP */

#पूर्ण_अगर /* __LINUX_OMAP_DMA_H */
