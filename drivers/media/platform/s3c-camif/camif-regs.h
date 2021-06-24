<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Register definition file क्रम s3c24xx/s3c64xx SoC CAMIF driver
 *
 * Copyright (C) 2012 Sylwester Nawrocki <sylvester.nawrocki@gmail.com>
 * Copyright (C) 2012 Tomasz Figa <tomasz.figa@gmail.com>
*/

#अगर_अघोषित CAMIF_REGS_H_
#घोषणा CAMIF_REGS_H_

#समावेश <linux/bitops.h>

#समावेश "camif-core.h"
#समावेश <media/drv-पूर्णांकf/s3c_camअगर.h>

/*
 * The id argument indicates the processing path:
 * id = 0 - codec (FIMC C), 1 - preview (FIMC P).
 */

/* Camera input क्रमmat */
#घोषणा S3C_CAMIF_REG_CISRCFMT			0x00
#घोषणा  CISRCFMT_ITU601_8BIT			BIT(31)
#घोषणा  CISRCFMT_ITU656_8BIT			(0 << 31)
#घोषणा  CISRCFMT_ORDER422_YCBYCR		(0 << 14)
#घोषणा  CISRCFMT_ORDER422_YCRYCB		(1 << 14)
#घोषणा  CISRCFMT_ORDER422_CBYCRY		(2 << 14)
#घोषणा  CISRCFMT_ORDER422_CRYCBY		(3 << 14)
#घोषणा  CISRCFMT_ORDER422_MASK			(3 << 14)
#घोषणा  CISRCFMT_SIZE_CAM_MASK			(0x1fff << 16 | 0x1fff)

/* Winकरोw offset */
#घोषणा S3C_CAMIF_REG_CIWDOFST			0x04
#घोषणा  CIWDOFST_WINOFSEN			BIT(31)
#घोषणा  CIWDOFST_CLROVCOFIY			BIT(30)
#घोषणा  CIWDOFST_CLROVRLB_PR			BIT(28)
/* #घोषणा  CIWDOFST_CLROVPRFIY			BIT(27) */
#घोषणा  CIWDOFST_CLROVCOFICB			BIT(15)
#घोषणा  CIWDOFST_CLROVCOFICR			BIT(14)
#घोषणा  CIWDOFST_CLROVPRFICB			BIT(13)
#घोषणा  CIWDOFST_CLROVPRFICR			BIT(12)
#घोषणा  CIWDOFST_OFST_MASK			(0x7ff << 16 | 0x7ff)

/* Winकरोw offset 2 */
#घोषणा S3C_CAMIF_REG_CIWDOFST2			0x14
#घोषणा  CIWDOFST2_OFST2_MASK			(0xfff << 16 | 0xfff)

/* Global control */
#घोषणा S3C_CAMIF_REG_CIGCTRL			0x08
#घोषणा  CIGCTRL_SWRST				BIT(31)
#घोषणा  CIGCTRL_CAMRST				BIT(30)
#घोषणा  CIGCTRL_TESTPATTERN_NORMAL		(0 << 27)
#घोषणा  CIGCTRL_TESTPATTERN_COLOR_BAR		(1 << 27)
#घोषणा  CIGCTRL_TESTPATTERN_HOR_INC		(2 << 27)
#घोषणा  CIGCTRL_TESTPATTERN_VER_INC		(3 << 27)
#घोषणा  CIGCTRL_TESTPATTERN_MASK		(3 << 27)
#घोषणा  CIGCTRL_INVPOLPCLK			BIT(26)
#घोषणा  CIGCTRL_INVPOLVSYNC			BIT(25)
#घोषणा  CIGCTRL_INVPOLHREF			BIT(24)
#घोषणा  CIGCTRL_IRQ_OVFEN			BIT(22)
#घोषणा  CIGCTRL_HREF_MASK			BIT(21)
#घोषणा  CIGCTRL_IRQ_LEVEL			BIT(20)
/* IRQ_CLR_C, IRQ_CLR_P */
#घोषणा  CIGCTRL_IRQ_CLR(id)			BIT(19 - (id))
#घोषणा  CIGCTRL_FIELDMODE			BIT(2)
#घोषणा  CIGCTRL_INVPOLFIELD			BIT(1)
#घोषणा  CIGCTRL_CAM_INTERLACE			BIT(0)

/* Y DMA output frame start address. n = 0..3. */
#घोषणा S3C_CAMIF_REG_CIYSA(id, n)		(0x18 + (id) * 0x54 + (n) * 4)
/* Cb plane output DMA start address. n = 0..3. Only codec path. */
#घोषणा S3C_CAMIF_REG_CICBSA(id, n)		(0x28 + (id) * 0x54 + (n) * 4)
/* Cr plane output DMA start address. n = 0..3. Only codec path. */
#घोषणा S3C_CAMIF_REG_CICRSA(id, n)		(0x38 + (id) * 0x54 + (n) * 4)

/* CICOTRGFMT, CIPRTRGFMT - Target क्रमmat */
#घोषणा S3C_CAMIF_REG_CITRGFMT(id, _offs)	(0x48 + (id) * (0x34 + (_offs)))
#घोषणा  CITRGFMT_IN422				BIT(31) /* only क्रम s3c24xx */
#घोषणा  CITRGFMT_OUT422			BIT(30) /* only क्रम s3c24xx */
#घोषणा  CITRGFMT_OUTFORMAT_YCBCR420		(0 << 29) /* only क्रम s3c6410 */
#घोषणा  CITRGFMT_OUTFORMAT_YCBCR422		(1 << 29) /* only क्रम s3c6410 */
#घोषणा  CITRGFMT_OUTFORMAT_YCBCR422I		(2 << 29) /* only क्रम s3c6410 */
#घोषणा  CITRGFMT_OUTFORMAT_RGB			(3 << 29) /* only क्रम s3c6410 */
#घोषणा  CITRGFMT_OUTFORMAT_MASK		(3 << 29) /* only क्रम s3c6410 */
#घोषणा  CITRGFMT_TARGETHSIZE(x)		((x) << 16)
#घोषणा  CITRGFMT_FLIP_NORMAL			(0 << 14)
#घोषणा  CITRGFMT_FLIP_X_MIRROR			(1 << 14)
#घोषणा  CITRGFMT_FLIP_Y_MIRROR			(2 << 14)
#घोषणा  CITRGFMT_FLIP_180			(3 << 14)
#घोषणा  CITRGFMT_FLIP_MASK			(3 << 14)
/* Preview path only */
#घोषणा  CITRGFMT_ROT90_PR			BIT(13)
#घोषणा  CITRGFMT_TARGETVSIZE(x)		((x) << 0)
#घोषणा  CITRGFMT_TARGETSIZE_MASK		((0x1fff << 16) | 0x1fff)

/* CICOCTRL, CIPRCTRL. Output DMA control. */
#घोषणा S3C_CAMIF_REG_CICTRL(id, _offs)		(0x4c + (id) * (0x34 + (_offs)))
#घोषणा  CICTRL_BURST_MASK			(0xfffff << 4)
/* xBURSTn - 5-bits width */
#घोषणा  CICTRL_YBURST1(x)			((x) << 19)
#घोषणा  CICTRL_YBURST2(x)			((x) << 14)
#घोषणा  CICTRL_RGBBURST1(x)			((x) << 19)
#घोषणा  CICTRL_RGBBURST2(x)			((x) << 14)
#घोषणा  CICTRL_CBURST1(x)			((x) << 9)
#घोषणा  CICTRL_CBURST2(x)			((x) << 4)
#घोषणा  CICTRL_LASTIRQ_ENABLE			BIT(2)
#घोषणा  CICTRL_ORDER422_MASK			(3 << 0)

/* CICOSCPRERATIO, CIPRSCPRERATIO. Pre-scaler control 1. */
#घोषणा S3C_CAMIF_REG_CISCPRERATIO(id, _offs)	(0x50 + (id) * (0x34 + (_offs)))

/* CICOSCPREDST, CIPRSCPREDST. Pre-scaler control 2. */
#घोषणा S3C_CAMIF_REG_CISCPREDST(id, _offs)	(0x54 + (id) * (0x34 + (_offs)))

/* CICOSCCTRL, CIPRSCCTRL. Main scaler control. */
#घोषणा S3C_CAMIF_REG_CISCCTRL(id, _offs)	(0x58 + (id) * (0x34 + (_offs)))
#घोषणा  CISCCTRL_SCALERBYPASS			BIT(31)
/* s3c244x preview path only, s3c64xx both */
#घोषणा  CIPRSCCTRL_SAMPLE			BIT(31)
/* 0 - 16-bit RGB, 1 - 24-bit RGB */
#घोषणा  CIPRSCCTRL_RGB_FORMAT_24BIT		BIT(30) /* only क्रम s3c244x */
#घोषणा  CIPRSCCTRL_SCALEUP_H			BIT(29) /* only क्रम s3c244x */
#घोषणा  CIPRSCCTRL_SCALEUP_V			BIT(28) /* only क्रम s3c244x */
/* s3c64xx */
#घोषणा  CISCCTRL_SCALEUP_H			BIT(30)
#घोषणा  CISCCTRL_SCALEUP_V			BIT(29)
#घोषणा  CISCCTRL_SCALEUP_MASK			(0x3 << 29)
#घोषणा  CISCCTRL_CSCR2Y_WIDE			BIT(28)
#घोषणा  CISCCTRL_CSCY2R_WIDE			BIT(27)
#घोषणा  CISCCTRL_LCDPATHEN_FIFO		BIT(26)
#घोषणा  CISCCTRL_INTERLACE			BIT(25)
#घोषणा  CISCCTRL_SCALERSTART			BIT(15)
#घोषणा  CISCCTRL_INRGB_FMT_RGB565		(0 << 13)
#घोषणा  CISCCTRL_INRGB_FMT_RGB666		(1 << 13)
#घोषणा  CISCCTRL_INRGB_FMT_RGB888		(2 << 13)
#घोषणा  CISCCTRL_INRGB_FMT_MASK		(3 << 13)
#घोषणा  CISCCTRL_OUTRGB_FMT_RGB565		(0 << 11)
#घोषणा  CISCCTRL_OUTRGB_FMT_RGB666		(1 << 11)
#घोषणा  CISCCTRL_OUTRGB_FMT_RGB888		(2 << 11)
#घोषणा  CISCCTRL_OUTRGB_FMT_MASK		(3 << 11)
#घोषणा  CISCCTRL_EXTRGB_EXTENSION		BIT(10)
#घोषणा  CISCCTRL_ONE2ONE			BIT(9)
#घोषणा  CISCCTRL_MAIN_RATIO_MASK		(0x1ff << 16 | 0x1ff)

/* CICOTAREA, CIPRTAREA. Target area क्रम DMA (Hsize x Vsize). */
#घोषणा S3C_CAMIF_REG_CITAREA(id, _offs)	(0x5c + (id) * (0x34 + (_offs)))
#घोषणा CITAREA_MASK				0xfffffff

/* Codec (id = 0) or preview (id = 1) path status. */
#घोषणा S3C_CAMIF_REG_CISTATUS(id, _offs)	(0x64 + (id) * (0x34 + (_offs)))
#घोषणा  CISTATUS_OVFIY_STATUS			BIT(31)
#घोषणा  CISTATUS_OVFICB_STATUS			BIT(30)
#घोषणा  CISTATUS_OVFICR_STATUS			BIT(29)
#घोषणा  CISTATUS_OVF_MASK			(0x7 << 29)
#घोषणा  CIPRSTATUS_OVF_MASK			(0x3 << 30)
#घोषणा  CISTATUS_VSYNC_STATUS			BIT(28)
#घोषणा  CISTATUS_FRAMECNT_MASK			(3 << 26)
#घोषणा  CISTATUS_FRAMECNT(__reg)		(((__reg) >> 26) & 0x3)
#घोषणा  CISTATUS_WINOFSTEN_STATUS		BIT(25)
#घोषणा  CISTATUS_IMGCPTEN_STATUS		BIT(22)
#घोषणा  CISTATUS_IMGCPTENSC_STATUS		BIT(21)
#घोषणा  CISTATUS_VSYNC_A_STATUS		BIT(20)
#घोषणा  CISTATUS_FRAMEEND_STATUS		BIT(19) /* 17 on s3c64xx */

/* Image capture enable */
#घोषणा S3C_CAMIF_REG_CIIMGCPT(_offs)		(0xa0 + (_offs))
#घोषणा  CIIMGCPT_IMGCPTEN			BIT(31)
#घोषणा  CIIMGCPT_IMGCPTEN_SC(id)		BIT(30 - (id))
/* Frame control: 1 - one-shot, 0 - मुक्त run */
#घोषणा  CIIMGCPT_CPT_FREN_ENABLE(id)		BIT(25 - (id))
#घोषणा  CIIMGCPT_CPT_FRMOD_ENABLE		(0 << 18)
#घोषणा  CIIMGCPT_CPT_FRMOD_CNT			BIT(18)

/* Capture sequence */
#घोषणा S3C_CAMIF_REG_CICPTSEQ			0xc4

/* Image effects */
#घोषणा S3C_CAMIF_REG_CIIMGEFF(_offs)		(0xb0 + (_offs))
#घोषणा  CIIMGEFF_IE_ENABLE(id)			BIT(30 + (id))
#घोषणा  CIIMGEFF_IE_ENABLE_MASK		(3 << 30)
/* Image effect: 1 - after scaler, 0 - beक्रमe scaler */
#घोषणा  CIIMGEFF_IE_AFTER_SC			BIT(29)
#घोषणा  CIIMGEFF_FIN_MASK			(7 << 26)
#घोषणा  CIIMGEFF_FIN_BYPASS			(0 << 26)
#घोषणा  CIIMGEFF_FIN_ARBITRARY			(1 << 26)
#घोषणा  CIIMGEFF_FIN_NEGATIVE			(2 << 26)
#घोषणा  CIIMGEFF_FIN_ARTFREEZE			(3 << 26)
#घोषणा  CIIMGEFF_FIN_EMBOSSING			(4 << 26)
#घोषणा  CIIMGEFF_FIN_SILHOUETTE		(5 << 26)
#घोषणा  CIIMGEFF_PAT_CBCR_MASK			((0xff << 13) | 0xff)
#घोषणा  CIIMGEFF_PAT_CB(x)			((x) << 13)
#घोषणा  CIIMGEFF_PAT_CR(x)			(x)

/* MSCOY0SA, MSPRY0SA. Y/Cb/Cr frame start address क्रम input DMA. */
#घोषणा S3C_CAMIF_REG_MSY0SA(id)		(0xd4 + ((id) * 0x2c))
#घोषणा S3C_CAMIF_REG_MSCB0SA(id)		(0xd8 + ((id) * 0x2c))
#घोषणा S3C_CAMIF_REG_MSCR0SA(id)		(0xdc + ((id) * 0x2c))

/* MSCOY0END, MSCOY0END. Y/Cb/Cr frame end address क्रम input DMA. */
#घोषणा S3C_CAMIF_REG_MSY0END(id)		(0xe0 + ((id) * 0x2c))
#घोषणा S3C_CAMIF_REG_MSCB0END(id)		(0xe4 + ((id) * 0x2c))
#घोषणा S3C_CAMIF_REG_MSCR0END(id)		(0xe8 + ((id) * 0x2c))

/* MSPRYOFF, MSPRYOFF. Y/Cb/Cr offset. n: 0 - codec, 1 - preview. */
#घोषणा S3C_CAMIF_REG_MSYOFF(id)		(0x118 + ((id) * 0x2c))
#घोषणा S3C_CAMIF_REG_MSCBOFF(id)		(0x11c + ((id) * 0x2c))
#घोषणा S3C_CAMIF_REG_MSCROFF(id)		(0x120 + ((id) * 0x2c))

/* Real input DMA data size. n = 0 - codec, 1 - preview. */
#घोषणा S3C_CAMIF_REG_MSWIDTH(id)		(0xf8 + (id) * 0x2c)
#घोषणा  AUTOLOAD_ENABLE			BIT(31)
#घोषणा  ADDR_CH_DIS				BIT(30)
#घोषणा  MSHEIGHT(x)				(((x) & 0x3ff) << 16)
#घोषणा  MSWIDTH(x)				((x) & 0x3ff)

/* Input DMA control. n = 0 - codec, 1 - preview */
#घोषणा S3C_CAMIF_REG_MSCTRL(id)		(0xfc + (id) * 0x2c)
#घोषणा  MSCTRL_ORDER422_M_YCBYCR		(0 << 4)
#घोषणा  MSCTRL_ORDER422_M_YCRYCB		(1 << 4)
#घोषणा  MSCTRL_ORDER422_M_CBYCRY		(2 << 4)
#घोषणा  MSCTRL_ORDER422_M_CRYCBY		(3 << 4)
/* 0 - camera, 1 - DMA */
#घोषणा  MSCTRL_SEL_DMA_CAM			BIT(3)
#घोषणा  MSCTRL_INFORMAT_M_YCBCR420		(0 << 1)
#घोषणा  MSCTRL_INFORMAT_M_YCBCR422		(1 << 1)
#घोषणा  MSCTRL_INFORMAT_M_YCBCR422I		(2 << 1)
#घोषणा  MSCTRL_INFORMAT_M_RGB			(3 << 1)
#घोषणा  MSCTRL_ENVID_M				BIT(0)

/* CICOSCOSY, CIPRSCOSY. Scan line Y/Cb/Cr offset. */
#घोषणा S3C_CAMIF_REG_CISSY(id)			(0x12c + (id) * 0x0c)
#घोषणा S3C_CAMIF_REG_CISSCB(id)		(0x130 + (id) * 0x0c)
#घोषणा S3C_CAMIF_REG_CISSCR(id)		(0x134 + (id) * 0x0c)
#घोषणा S3C_CISS_OFFS_INITIAL(x)		((x) << 16)
#घोषणा S3C_CISS_OFFS_LINE(x)			((x) << 0)

/* ------------------------------------------------------------------ */

व्योम camअगर_hw_reset(काष्ठा camअगर_dev *camअगर);
व्योम camअगर_hw_clear_pending_irq(काष्ठा camअगर_vp *vp);
व्योम camअगर_hw_clear_fअगरo_overflow(काष्ठा camअगर_vp *vp);
व्योम camअगर_hw_set_lastirq(काष्ठा camअगर_vp *vp, पूर्णांक enable);
व्योम camअगर_hw_set_input_path(काष्ठा camअगर_vp *vp);
व्योम camअगर_hw_enable_scaler(काष्ठा camअगर_vp *vp, bool on);
व्योम camअगर_hw_enable_capture(काष्ठा camअगर_vp *vp);
व्योम camअगर_hw_disable_capture(काष्ठा camअगर_vp *vp);
व्योम camअगर_hw_set_camera_bus(काष्ठा camअगर_dev *camअगर);
व्योम camअगर_hw_set_source_क्रमmat(काष्ठा camअगर_dev *camअगर);
व्योम camअगर_hw_set_camera_crop(काष्ठा camअगर_dev *camअगर);
व्योम camअगर_hw_set_scaler(काष्ठा camअगर_vp *vp);
व्योम camअगर_hw_set_flip(काष्ठा camअगर_vp *vp);
व्योम camअगर_hw_set_output_dma(काष्ठा camअगर_vp *vp);
व्योम camअगर_hw_set_target_क्रमmat(काष्ठा camअगर_vp *vp);
व्योम camअगर_hw_set_test_pattern(काष्ठा camअगर_dev *camअगर, अचिन्हित पूर्णांक pattern);
व्योम camअगर_hw_set_effect(काष्ठा camअगर_dev *camअगर, अचिन्हित पूर्णांक effect,
			अचिन्हित पूर्णांक cr, अचिन्हित पूर्णांक cb);
व्योम camअगर_hw_set_output_addr(काष्ठा camअगर_vp *vp, काष्ठा camअगर_addr *paddr,
			      पूर्णांक index);
व्योम camअगर_hw_dump_regs(काष्ठा camअगर_dev *camअगर, स्थिर अक्षर *label);

अटल अंतरभूत u32 camअगर_hw_get_status(काष्ठा camअगर_vp *vp)
अणु
	वापस पढ़ोl(vp->camअगर->io_base + S3C_CAMIF_REG_CISTATUS(vp->id,
								vp->offset));
पूर्ण

#पूर्ण_अगर /* CAMIF_REGS_H_ */
