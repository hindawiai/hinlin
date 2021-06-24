<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * camss-vfe-170.c
 *
 * Qualcomm MSM Camera Subप्रणाली - VFE (Video Front End) Module v170
 *
 * Copyright (C) 2020-2021 Linaro Ltd.
 */

#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>

#समावेश "camss.h"
#समावेश "camss-vfe.h"

#घोषणा VFE_HW_VERSION				(0x000)

#घोषणा VFE_GLOBAL_RESET_CMD			(0x018)
#घोषणा		GLOBAL_RESET_CMD_CORE		BIT(0)
#घोषणा		GLOBAL_RESET_CMD_CAMIF		BIT(1)
#घोषणा		GLOBAL_RESET_CMD_BUS		BIT(2)
#घोषणा		GLOBAL_RESET_CMD_BUS_BDG	BIT(3)
#घोषणा		GLOBAL_RESET_CMD_REGISTER	BIT(4)
#घोषणा		GLOBAL_RESET_CMD_PM		BIT(5)
#घोषणा		GLOBAL_RESET_CMD_BUS_MISR	BIT(6)
#घोषणा		GLOBAL_RESET_CMD_TESTGEN	BIT(7)
#घोषणा		GLOBAL_RESET_CMD_DSP		BIT(8)
#घोषणा		GLOBAL_RESET_CMD_IDLE_CGC	BIT(9)
#घोषणा		GLOBAL_RESET_CMD_RDI0		BIT(10)
#घोषणा		GLOBAL_RESET_CMD_RDI1		BIT(11)
#घोषणा		GLOBAL_RESET_CMD_RDI2		BIT(12)
#घोषणा		GLOBAL_RESET_CMD_RDI3		BIT(13)
#घोषणा		GLOBAL_RESET_CMD_VFE_DOMAIN	BIT(30)
#घोषणा		GLOBAL_RESET_CMD_RESET_BYPASS	BIT(31)

#घोषणा VFE_CORE_CFG				(0x050)
#घोषणा		CFG_PIXEL_PATTERN_YCBYCR	(0x4)
#घोषणा		CFG_PIXEL_PATTERN_YCRYCB	(0x5)
#घोषणा		CFG_PIXEL_PATTERN_CBYCRY	(0x6)
#घोषणा		CFG_PIXEL_PATTERN_CRYCBY	(0x7)
#घोषणा		CFG_COMPOSITE_REG_UPDATE_EN	BIT(4)

#घोषणा VFE_IRQ_CMD				(0x058)
#घोषणा		CMD_GLOBAL_CLEAR		BIT(0)

#घोषणा VFE_IRQ_MASK_0					(0x05c)
#घोषणा		MASK_0_CAMIF_SOF			BIT(0)
#घोषणा		MASK_0_CAMIF_खातापूर्ण			BIT(1)
#घोषणा		MASK_0_RDI_REG_UPDATE(n)		BIT((n) + 5)
#घोषणा		MASK_0_IMAGE_MASTER_n_PING_PONG(n)	BIT((n) + 8)
#घोषणा		MASK_0_IMAGE_COMPOSITE_DONE_n(n)	BIT((n) + 25)
#घोषणा		MASK_0_RESET_ACK			BIT(31)

#घोषणा VFE_IRQ_MASK_1					(0x060)
#घोषणा		MASK_1_CAMIF_ERROR			BIT(0)
#घोषणा		MASK_1_VIOLATION			BIT(7)
#घोषणा		MASK_1_BUS_BDG_HALT_ACK			BIT(8)
#घोषणा		MASK_1_IMAGE_MASTER_n_BUS_OVERFLOW(n)	BIT((n) + 9)
#घोषणा		MASK_1_RDI_SOF(n)			BIT((n) + 29)

#घोषणा VFE_IRQ_CLEAR_0					(0x064)
#घोषणा VFE_IRQ_CLEAR_1					(0x068)

#घोषणा VFE_IRQ_STATUS_0				(0x06c)
#घोषणा		STATUS_0_CAMIF_SOF			BIT(0)
#घोषणा		STATUS_0_RDI_REG_UPDATE(n)		BIT((n) + 5)
#घोषणा		STATUS_0_IMAGE_MASTER_PING_PONG(n)	BIT((n) + 8)
#घोषणा		STATUS_0_IMAGE_COMPOSITE_DONE(n)	BIT((n) + 25)
#घोषणा		STATUS_0_RESET_ACK			BIT(31)

#घोषणा VFE_IRQ_STATUS_1				(0x070)
#घोषणा		STATUS_1_VIOLATION			BIT(7)
#घोषणा		STATUS_1_BUS_BDG_HALT_ACK		BIT(8)
#घोषणा		STATUS_1_RDI_SOF(n)			BIT((n) + 27)

#घोषणा VFE_VIOLATION_STATUS			(0x07c)

#घोषणा VFE_CAMIF_CMD				(0x478)
#घोषणा		CMD_CLEAR_CAMIF_STATUS		BIT(2)

#घोषणा VFE_CAMIF_CFG				(0x47c)
#घोषणा		CFG_VSYNC_SYNC_EDGE		(0)
#घोषणा			VSYNC_ACTIVE_HIGH	(0)
#घोषणा			VSYNC_ACTIVE_LOW	(1)
#घोषणा		CFG_HSYNC_SYNC_EDGE		(1)
#घोषणा			HSYNC_ACTIVE_HIGH	(0)
#घोषणा			HSYNC_ACTIVE_LOW	(1)
#घोषणा		CFG_VFE_SUBSAMPLE_ENABLE	BIT(4)
#घोषणा		CFG_BUS_SUBSAMPLE_ENABLE	BIT(5)
#घोषणा		CFG_VFE_OUTPUT_EN		BIT(6)
#घोषणा		CFG_BUS_OUTPUT_EN		BIT(7)
#घोषणा		CFG_BINNING_EN			BIT(9)
#घोषणा		CFG_FRAME_BASED_EN		BIT(10)
#घोषणा		CFG_RAW_CROP_EN			BIT(22)

#घोषणा VFE_REG_UPDATE_CMD			(0x4ac)
#घोषणा		REG_UPDATE_RDI(n)		BIT(1 + (n))

#घोषणा VFE_BUS_IRQ_MASK(n)		(0x2044 + (n) * 4)
#घोषणा VFE_BUS_IRQ_CLEAR(n)		(0x2050 + (n) * 4)
#घोषणा VFE_BUS_IRQ_STATUS(n)		(0x205c + (n) * 4)
#घोषणा		STATUS0_COMP_RESET_DONE		BIT(0)
#घोषणा		STATUS0_COMP_REG_UPDATE0_DONE	BIT(1)
#घोषणा		STATUS0_COMP_REG_UPDATE1_DONE	BIT(2)
#घोषणा		STATUS0_COMP_REG_UPDATE2_DONE	BIT(3)
#घोषणा		STATUS0_COMP_REG_UPDATE3_DONE	BIT(4)
#घोषणा		STATUS0_COMP_REG_UPDATE_DONE(n)	BIT((n) + 1)
#घोषणा		STATUS0_COMP0_BUF_DONE		BIT(5)
#घोषणा		STATUS0_COMP1_BUF_DONE		BIT(6)
#घोषणा		STATUS0_COMP2_BUF_DONE		BIT(7)
#घोषणा		STATUS0_COMP3_BUF_DONE		BIT(8)
#घोषणा		STATUS0_COMP4_BUF_DONE		BIT(9)
#घोषणा		STATUS0_COMP5_BUF_DONE		BIT(10)
#घोषणा		STATUS0_COMP_BUF_DONE(n)	BIT((n) + 5)
#घोषणा		STATUS0_COMP_ERROR		BIT(11)
#घोषणा		STATUS0_COMP_OVERWRITE		BIT(12)
#घोषणा		STATUS0_OVERFLOW		BIT(13)
#घोषणा		STATUS0_VIOLATION		BIT(14)
/* WM_CLIENT_BUF_DONE defined क्रम buffers 0:19 */
#घोषणा		STATUS1_WM_CLIENT_BUF_DONE(n)		BIT(n)
#घोषणा		STATUS1_EARLY_DONE			BIT(24)
#घोषणा		STATUS2_DUAL_COMP0_BUF_DONE		BIT(0)
#घोषणा		STATUS2_DUAL_COMP1_BUF_DONE		BIT(1)
#घोषणा		STATUS2_DUAL_COMP2_BUF_DONE		BIT(2)
#घोषणा		STATUS2_DUAL_COMP3_BUF_DONE		BIT(3)
#घोषणा		STATUS2_DUAL_COMP4_BUF_DONE		BIT(4)
#घोषणा		STATUS2_DUAL_COMP5_BUF_DONE		BIT(5)
#घोषणा		STATUS2_DUAL_COMP_BUF_DONE(n)		BIT(n)
#घोषणा		STATUS2_DUAL_COMP_ERROR			BIT(6)
#घोषणा		STATUS2_DUAL_COMP_OVERWRITE		BIT(7)

#घोषणा VFE_BUS_IRQ_CLEAR_GLOBAL		(0x2068)

#घोषणा VFE_BUS_WM_DEBUG_STATUS_CFG		(0x226c)
#घोषणा		DEBUG_STATUS_CFG_STATUS0(n)	BIT(n)
#घोषणा		DEBUG_STATUS_CFG_STATUS1(n)	BIT(8 + (n))

#घोषणा VFE_BUS_WM_ADDR_SYNC_FRAME_HEADER	(0x2080)

#घोषणा VFE_BUS_WM_ADDR_SYNC_NO_SYNC		(0x2084)
#घोषणा		BUS_VER2_MAX_CLIENTS (24)
#घोषणा		WM_ADDR_NO_SYNC_DEFAULT_VAL \
				((1 << BUS_VER2_MAX_CLIENTS) - 1)

#घोषणा VFE_BUS_WM_CGC_OVERRIDE			(0x200c)
#घोषणा		WM_CGC_OVERRIDE_ALL		(0xFFFFF)

#घोषणा VFE_BUS_WM_TEST_BUS_CTRL		(0x211c)

#घोषणा VFE_BUS_WM_STATUS0(n)			(0x2200 + (n) * 0x100)
#घोषणा VFE_BUS_WM_STATUS1(n)			(0x2204 + (n) * 0x100)
#घोषणा VFE_BUS_WM_CFG(n)			(0x2208 + (n) * 0x100)
#घोषणा		WM_CFG_EN			(0)
#घोषणा		WM_CFG_MODE			(1)
#घोषणा			MODE_QCOM_PLAIN	(0)
#घोषणा			MODE_MIPI_RAW	(1)
#घोषणा		WM_CFG_VIRTUALFRAME		(2)
#घोषणा VFE_BUS_WM_HEADER_ADDR(n)		(0x220c + (n) * 0x100)
#घोषणा VFE_BUS_WM_HEADER_CFG(n)		(0x2210 + (n) * 0x100)
#घोषणा VFE_BUS_WM_IMAGE_ADDR(n)		(0x2214 + (n) * 0x100)
#घोषणा VFE_BUS_WM_IMAGE_ADDR_OFFSET(n)		(0x2218 + (n) * 0x100)
#घोषणा VFE_BUS_WM_BUFFER_WIDTH_CFG(n)		(0x221c + (n) * 0x100)
#घोषणा		WM_BUFFER_DEFAULT_WIDTH		(0xFF01)

#घोषणा VFE_BUS_WM_BUFFER_HEIGHT_CFG(n)		(0x2220 + (n) * 0x100)
#घोषणा VFE_BUS_WM_PACKER_CFG(n)		(0x2224 + (n) * 0x100)

#घोषणा VFE_BUS_WM_STRIDE(n)			(0x2228 + (n) * 0x100)
#घोषणा		WM_STRIDE_DEFAULT_STRIDE	(0xFF01)

#घोषणा VFE_BUS_WM_IRQ_SUBSAMPLE_PERIOD(n)	(0x2248 + (n) * 0x100)
#घोषणा VFE_BUS_WM_IRQ_SUBSAMPLE_PATTERN(n)	(0x224c + (n) * 0x100)
#घोषणा VFE_BUS_WM_FRAMEDROP_PERIOD(n)		(0x2250 + (n) * 0x100)
#घोषणा VFE_BUS_WM_FRAMEDROP_PATTERN(n)		(0x2254 + (n) * 0x100)
#घोषणा VFE_BUS_WM_FRAME_INC(n)			(0x2258 + (n) * 0x100)
#घोषणा VFE_BUS_WM_BURST_LIMIT(n)		(0x225c + (n) * 0x100)

अटल व्योम vfe_hw_version_पढ़ो(काष्ठा vfe_device *vfe, काष्ठा device *dev)
अणु
	u32 hw_version = पढ़ोl_relaxed(vfe->base + VFE_HW_VERSION);

	u32 gen = (hw_version >> 28) & 0xF;
	u32 rev = (hw_version >> 16) & 0xFFF;
	u32 step = hw_version & 0xFFFF;

	dev_err(dev, "VFE HW Version = %u.%u.%u\n", gen, rev, step);
पूर्ण

अटल अंतरभूत व्योम vfe_reg_clr(काष्ठा vfe_device *vfe, u32 reg, u32 clr_bits)
अणु
	u32 bits = पढ़ोl_relaxed(vfe->base + reg);

	ग_लिखोl_relaxed(bits & ~clr_bits, vfe->base + reg);
पूर्ण

अटल अंतरभूत व्योम vfe_reg_set(काष्ठा vfe_device *vfe, u32 reg, u32 set_bits)
अणु
	u32 bits = पढ़ोl_relaxed(vfe->base + reg);

	ग_लिखोl_relaxed(bits | set_bits, vfe->base + reg);
पूर्ण

अटल व्योम vfe_global_reset(काष्ठा vfe_device *vfe)
अणु
	u32 reset_bits = GLOBAL_RESET_CMD_CORE		|
			 GLOBAL_RESET_CMD_CAMIF		|
			 GLOBAL_RESET_CMD_BUS		|
			 GLOBAL_RESET_CMD_BUS_BDG	|
			 GLOBAL_RESET_CMD_REGISTER	|
			 GLOBAL_RESET_CMD_TESTGEN	|
			 GLOBAL_RESET_CMD_DSP		|
			 GLOBAL_RESET_CMD_IDLE_CGC	|
			 GLOBAL_RESET_CMD_RDI0		|
			 GLOBAL_RESET_CMD_RDI1		|
			 GLOBAL_RESET_CMD_RDI2;

	ग_लिखोl_relaxed(BIT(31), vfe->base + VFE_IRQ_MASK_0);

	/* Make sure IRQ mask has been written beक्रमe resetting */
	wmb();

	ग_लिखोl_relaxed(reset_bits, vfe->base + VFE_GLOBAL_RESET_CMD);
पूर्ण

अटल व्योम vfe_wm_start(काष्ठा vfe_device *vfe, u8 wm, काष्ठा vfe_line *line)
अणु
	u32 val;

	/*Set Debug Registers*/
	val = DEBUG_STATUS_CFG_STATUS0(1) |
	      DEBUG_STATUS_CFG_STATUS0(7);
	ग_लिखोl_relaxed(val, vfe->base + VFE_BUS_WM_DEBUG_STATUS_CFG);

	/* BUS_WM_INPUT_IF_ADDR_SYNC_FRAME_HEADER */
	ग_लिखोl_relaxed(0, vfe->base + VFE_BUS_WM_ADDR_SYNC_FRAME_HEADER);

	/* no घड़ी gating at bus input */
	val = WM_CGC_OVERRIDE_ALL;
	ग_लिखोl_relaxed(val, vfe->base + VFE_BUS_WM_CGC_OVERRIDE);

	ग_लिखोl_relaxed(0x0, vfe->base + VFE_BUS_WM_TEST_BUS_CTRL);

	/* अगर addr_no_sync has शेष value then config the addr no sync reg */
	val = WM_ADDR_NO_SYNC_DEFAULT_VAL;
	ग_लिखोl_relaxed(val, vfe->base + VFE_BUS_WM_ADDR_SYNC_NO_SYNC);

	ग_लिखोl_relaxed(0xf, vfe->base + VFE_BUS_WM_BURST_LIMIT(wm));

	val = WM_BUFFER_DEFAULT_WIDTH;
	ग_लिखोl_relaxed(val, vfe->base + VFE_BUS_WM_BUFFER_WIDTH_CFG(wm));

	val = 0;
	ग_लिखोl_relaxed(val, vfe->base + VFE_BUS_WM_BUFFER_HEIGHT_CFG(wm));

	val = 0;
	ग_लिखोl_relaxed(val, vfe->base + VFE_BUS_WM_PACKER_CFG(wm)); // XXX 1 क्रम PLAIN8?

	/* Configure stride क्रम RDIs */
	val = WM_STRIDE_DEFAULT_STRIDE;
	ग_लिखोl_relaxed(val, vfe->base + VFE_BUS_WM_STRIDE(wm));

	/* Enable WM */
	val = 1 << WM_CFG_EN |
	      MODE_MIPI_RAW << WM_CFG_MODE;
	ग_लिखोl_relaxed(val, vfe->base + VFE_BUS_WM_CFG(wm));
पूर्ण

अटल व्योम vfe_wm_stop(काष्ठा vfe_device *vfe, u8 wm)
अणु
	/* Disable WM */
	ग_लिखोl_relaxed(0, vfe->base + VFE_BUS_WM_CFG(wm));
पूर्ण

अटल व्योम vfe_wm_update(काष्ठा vfe_device *vfe, u8 wm, u32 addr,
			  काष्ठा vfe_line *line)
अणु
	काष्ठा v4l2_pix_क्रमmat_mplane *pix =
		&line->video_out.active_fmt.fmt.pix_mp;
	u32 stride = pix->plane_fmt[0].bytesperline;

	ग_लिखोl_relaxed(addr, vfe->base + VFE_BUS_WM_IMAGE_ADDR(wm));
	ग_लिखोl_relaxed(stride * pix->height, vfe->base + VFE_BUS_WM_FRAME_INC(wm));
पूर्ण

अटल व्योम vfe_reg_update(काष्ठा vfe_device *vfe, क्रमागत vfe_line_id line_id)
अणु
	vfe->reg_update |= REG_UPDATE_RDI(line_id);

	/* Enक्रमce ordering between previous reg ग_लिखोs and reg update */
	wmb();

	ग_लिखोl_relaxed(vfe->reg_update, vfe->base + VFE_REG_UPDATE_CMD);

	/* Enक्रमce ordering between reg update and subsequent reg ग_लिखोs */
	wmb();
पूर्ण

अटल अंतरभूत व्योम vfe_reg_update_clear(काष्ठा vfe_device *vfe,
					क्रमागत vfe_line_id line_id)
अणु
	vfe->reg_update &= ~REG_UPDATE_RDI(line_id);
पूर्ण

अटल व्योम vfe_enable_irq_common(काष्ठा vfe_device *vfe)
अणु
	vfe_reg_set(vfe, VFE_IRQ_MASK_0, ~0u);
	vfe_reg_set(vfe, VFE_IRQ_MASK_1, ~0u);

	ग_लिखोl_relaxed(~0u, vfe->base + VFE_BUS_IRQ_MASK(0));
	ग_लिखोl_relaxed(~0u, vfe->base + VFE_BUS_IRQ_MASK(1));
	ग_लिखोl_relaxed(~0u, vfe->base + VFE_BUS_IRQ_MASK(2));
पूर्ण

अटल व्योम vfe_isr_halt_ack(काष्ठा vfe_device *vfe)
अणु
	complete(&vfe->halt_complete);
पूर्ण

अटल व्योम vfe_isr_पढ़ो(काष्ठा vfe_device *vfe, u32 *status0, u32 *status1)
अणु
	*status0 = पढ़ोl_relaxed(vfe->base + VFE_IRQ_STATUS_0);
	*status1 = पढ़ोl_relaxed(vfe->base + VFE_IRQ_STATUS_1);

	ग_लिखोl_relaxed(*status0, vfe->base + VFE_IRQ_CLEAR_0);
	ग_लिखोl_relaxed(*status1, vfe->base + VFE_IRQ_CLEAR_1);

	/* Enक्रमce ordering between IRQ Clear and Global IRQ Clear */
	wmb();
	ग_लिखोl_relaxed(CMD_GLOBAL_CLEAR, vfe->base + VFE_IRQ_CMD);
पूर्ण

अटल व्योम vfe_violation_पढ़ो(काष्ठा vfe_device *vfe)
अणु
	u32 violation = पढ़ोl_relaxed(vfe->base + VFE_VIOLATION_STATUS);

	pr_err_ratelimited("VFE: violation = 0x%08x\n", violation);
पूर्ण

/*
 * vfe_isr - VFE module पूर्णांकerrupt handler
 * @irq: Interrupt line
 * @dev: VFE device
 *
 * Return IRQ_HANDLED on success
 */
अटल irqवापस_t vfe_isr(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा vfe_device *vfe = dev;
	u32 status0, status1, vfe_bus_status[3];
	पूर्णांक i, wm;

	status0 = पढ़ोl_relaxed(vfe->base + VFE_IRQ_STATUS_0);
	status1 = पढ़ोl_relaxed(vfe->base + VFE_IRQ_STATUS_1);

	ग_लिखोl_relaxed(status0, vfe->base + VFE_IRQ_CLEAR_0);
	ग_लिखोl_relaxed(status1, vfe->base + VFE_IRQ_CLEAR_1);

	क्रम (i = VFE_LINE_RDI0; i <= VFE_LINE_RDI2; i++) अणु
		vfe_bus_status[i] = पढ़ोl_relaxed(vfe->base + VFE_BUS_IRQ_STATUS(i));
		ग_लिखोl_relaxed(vfe_bus_status[i], vfe->base + VFE_BUS_IRQ_CLEAR(i));
	पूर्ण

	/* Enक्रमce ordering between IRQ पढ़ोing and पूर्णांकerpretation */
	wmb();

	ग_लिखोl_relaxed(CMD_GLOBAL_CLEAR, vfe->base + VFE_IRQ_CMD);
	ग_लिखोl_relaxed(1, vfe->base + VFE_BUS_IRQ_CLEAR_GLOBAL);

	अगर (status0 & STATUS_0_RESET_ACK)
		vfe->isr_ops.reset_ack(vfe);

	क्रम (i = VFE_LINE_RDI0; i <= VFE_LINE_RDI2; i++)
		अगर (status0 & STATUS_0_RDI_REG_UPDATE(i))
			vfe->isr_ops.reg_update(vfe, i);

	क्रम (i = VFE_LINE_RDI0; i <= VFE_LINE_RDI2; i++)
		अगर (status0 & STATUS_1_RDI_SOF(i))
			vfe->isr_ops.sof(vfe, i);

	क्रम (i = 0; i < MSM_VFE_COMPOSITE_IRQ_NUM; i++)
		अगर (vfe_bus_status[0] & STATUS0_COMP_BUF_DONE(i))
			vfe->isr_ops.comp_करोne(vfe, i);

	क्रम (wm = 0; wm < MSM_VFE_IMAGE_MASTERS_NUM; wm++)
		अगर (status0 & BIT(9))
			अगर (vfe_bus_status[1] & STATUS1_WM_CLIENT_BUF_DONE(wm))
				vfe->isr_ops.wm_करोne(vfe, wm);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * vfe_halt - Trigger halt on VFE module and रुको to complete
 * @vfe: VFE device
 *
 * Return 0 on success or a negative error code otherwise
 */
अटल पूर्णांक vfe_halt(काष्ठा vfe_device *vfe)
अणु
	अचिन्हित दीर्घ समय;

	reinit_completion(&vfe->halt_complete);

	समय = रुको_क्रम_completion_समयout(&vfe->halt_complete,
					   msecs_to_jअगरfies(VFE_HALT_TIMEOUT_MS));
	अगर (!समय) अणु
		dev_err(vfe->camss->dev, "VFE halt timeout\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vfe_get_output(काष्ठा vfe_line *line)
अणु
	काष्ठा vfe_device *vfe = to_vfe(line);
	काष्ठा vfe_output *output;
	अचिन्हित दीर्घ flags;
	पूर्णांक wm_idx;

	spin_lock_irqsave(&vfe->output_lock, flags);

	output = &line->output;
	अगर (output->state != VFE_OUTPUT_OFF) अणु
		dev_err(vfe->camss->dev, "Output is running\n");
		जाओ error;
	पूर्ण

	output->wm_num = 1;

	wm_idx = vfe_reserve_wm(vfe, line->id);
	अगर (wm_idx < 0) अणु
		dev_err(vfe->camss->dev, "Can not reserve wm\n");
		जाओ error_get_wm;
	पूर्ण
	output->wm_idx[0] = wm_idx;

	output->drop_update_idx = 0;

	spin_unlock_irqrestore(&vfe->output_lock, flags);

	वापस 0;

error_get_wm:
	vfe_release_wm(vfe, output->wm_idx[0]);
	output->state = VFE_OUTPUT_OFF;
error:
	spin_unlock_irqrestore(&vfe->output_lock, flags);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक vfe_enable_output(काष्ठा vfe_line *line)
अणु
	काष्ठा vfe_device *vfe = to_vfe(line);
	काष्ठा vfe_output *output = &line->output;
	स्थिर काष्ठा vfe_hw_ops *ops = vfe->ops;
	काष्ठा media_entity *sensor;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक frame_skip = 0;
	अचिन्हित पूर्णांक i;

	sensor = camss_find_sensor(&line->subdev.entity);
	अगर (sensor) अणु
		काष्ठा v4l2_subdev *subdev = media_entity_to_v4l2_subdev(sensor);

		v4l2_subdev_call(subdev, sensor, g_skip_frames, &frame_skip);
		/* Max frame skip is 29 frames */
		अगर (frame_skip > VFE_FRAME_DROP_VAL - 1)
			frame_skip = VFE_FRAME_DROP_VAL - 1;
	पूर्ण

	spin_lock_irqsave(&vfe->output_lock, flags);

	ops->reg_update_clear(vfe, line->id);

	अगर (output->state != VFE_OUTPUT_OFF) अणु
		dev_err(vfe->camss->dev, "Output is not in reserved state %d\n",
			output->state);
		spin_unlock_irqrestore(&vfe->output_lock, flags);
		वापस -EINVAL;
	पूर्ण

	WARN_ON(output->gen2.active_num);

	output->state = VFE_OUTPUT_ON;

	output->sequence = 0;
	output->रुको_reg_update = 0;
	reinit_completion(&output->reg_update);

	vfe_wm_start(vfe, output->wm_idx[0], line);

	क्रम (i = 0; i < 2; i++) अणु
		output->buf[i] = vfe_buf_get_pending(output);
		अगर (!output->buf[i])
			अवरोध;
		output->gen2.active_num++;
		vfe_wm_update(vfe, output->wm_idx[0], output->buf[i]->addr[0], line);
	पूर्ण

	ops->reg_update(vfe, line->id);

	spin_unlock_irqrestore(&vfe->output_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक vfe_disable_output(काष्ठा vfe_line *line)
अणु
	काष्ठा vfe_device *vfe = to_vfe(line);
	काष्ठा vfe_output *output = &line->output;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i;
	bool करोne;
	पूर्णांक समयout = 0;

	करो अणु
		spin_lock_irqsave(&vfe->output_lock, flags);
		करोne = !output->gen2.active_num;
		spin_unlock_irqrestore(&vfe->output_lock, flags);
		usleep_range(10000, 20000);

		अगर (समयout++ == 100) अणु
			dev_err(vfe->camss->dev, "VFE idle timeout - resetting\n");
			vfe_reset(vfe);
			output->gen2.active_num = 0;
			वापस 0;
		पूर्ण
	पूर्ण जबतक (!करोne);

	spin_lock_irqsave(&vfe->output_lock, flags);
	क्रम (i = 0; i < output->wm_num; i++)
		vfe_wm_stop(vfe, output->wm_idx[i]);
	spin_unlock_irqrestore(&vfe->output_lock, flags);

	वापस 0;
पूर्ण

/*
 * vfe_enable - Enable streaming on VFE line
 * @line: VFE line
 *
 * Return 0 on success or a negative error code otherwise
 */
अटल पूर्णांक vfe_enable(काष्ठा vfe_line *line)
अणु
	काष्ठा vfe_device *vfe = to_vfe(line);
	पूर्णांक ret;

	mutex_lock(&vfe->stream_lock);

	अगर (!vfe->stream_count)
		vfe_enable_irq_common(vfe);

	vfe->stream_count++;

	mutex_unlock(&vfe->stream_lock);

	ret = vfe_get_output(line);
	अगर (ret < 0)
		जाओ error_get_output;

	ret = vfe_enable_output(line);
	अगर (ret < 0)
		जाओ error_enable_output;

	vfe->was_streaming = 1;

	वापस 0;

error_enable_output:
	vfe_put_output(line);

error_get_output:
	mutex_lock(&vfe->stream_lock);

	vfe->stream_count--;

	mutex_unlock(&vfe->stream_lock);

	वापस ret;
पूर्ण

/*
 * vfe_disable - Disable streaming on VFE line
 * @line: VFE line
 *
 * Return 0 on success or a negative error code otherwise
 */
अटल पूर्णांक vfe_disable(काष्ठा vfe_line *line)
अणु
	काष्ठा vfe_device *vfe = to_vfe(line);

	vfe_disable_output(line);

	vfe_put_output(line);

	mutex_lock(&vfe->stream_lock);

	vfe->stream_count--;

	mutex_unlock(&vfe->stream_lock);

	वापस 0;
पूर्ण

/*
 * vfe_isr_sof - Process start of frame पूर्णांकerrupt
 * @vfe: VFE Device
 * @line_id: VFE line
 */
अटल व्योम vfe_isr_sof(काष्ठा vfe_device *vfe, क्रमागत vfe_line_id line_id)
अणु
	/* nop */
पूर्ण

/*
 * vfe_isr_reg_update - Process reg update पूर्णांकerrupt
 * @vfe: VFE Device
 * @line_id: VFE line
 */
अटल व्योम vfe_isr_reg_update(काष्ठा vfe_device *vfe, क्रमागत vfe_line_id line_id)
अणु
	काष्ठा vfe_output *output;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&vfe->output_lock, flags);
	vfe->ops->reg_update_clear(vfe, line_id);

	output = &vfe->line[line_id].output;

	अगर (output->रुको_reg_update) अणु
		output->रुको_reg_update = 0;
		complete(&output->reg_update);
	पूर्ण

	spin_unlock_irqrestore(&vfe->output_lock, flags);
पूर्ण

/*
 * vfe_isr_wm_करोne - Process ग_लिखो master करोne पूर्णांकerrupt
 * @vfe: VFE Device
 * @wm: Write master id
 */
अटल व्योम vfe_isr_wm_करोne(काष्ठा vfe_device *vfe, u8 wm)
अणु
	काष्ठा vfe_line *line = &vfe->line[vfe->wm_output_map[wm]];
	काष्ठा camss_buffer *पढ़ोy_buf;
	काष्ठा vfe_output *output;
	अचिन्हित दीर्घ flags;
	u32 index;
	u64 ts = kसमय_get_ns();

	spin_lock_irqsave(&vfe->output_lock, flags);

	अगर (vfe->wm_output_map[wm] == VFE_LINE_NONE) अणु
		dev_err_ratelimited(vfe->camss->dev,
				    "Received wm done for unmapped index\n");
		जाओ out_unlock;
	पूर्ण
	output = &vfe->line[vfe->wm_output_map[wm]].output;

	पढ़ोy_buf = output->buf[0];
	अगर (!पढ़ोy_buf) अणु
		dev_err_ratelimited(vfe->camss->dev,
				    "Missing ready buf %d!\n", output->state);
		जाओ out_unlock;
	पूर्ण

	पढ़ोy_buf->vb.vb2_buf.बारtamp = ts;
	पढ़ोy_buf->vb.sequence = output->sequence++;

	index = 0;
	output->buf[0] = output->buf[1];
	अगर (output->buf[0])
		index = 1;

	output->buf[index] = vfe_buf_get_pending(output);

	अगर (output->buf[index])
		vfe_wm_update(vfe, output->wm_idx[0], output->buf[index]->addr[0], line);
	अन्यथा
		output->gen2.active_num--;

	spin_unlock_irqrestore(&vfe->output_lock, flags);

	vb2_buffer_करोne(&पढ़ोy_buf->vb.vb2_buf, VB2_BUF_STATE_DONE);

	वापस;

out_unlock:
	spin_unlock_irqrestore(&vfe->output_lock, flags);
पूर्ण

/*
 * vfe_pm_करोमुख्य_off - Disable घातer करोमुख्यs specअगरic to this VFE.
 * @vfe: VFE Device
 */
अटल व्योम vfe_pm_करोमुख्य_off(काष्ठा vfe_device *vfe)
अणु
	/* nop */
पूर्ण

/*
 * vfe_pm_करोमुख्य_on - Enable घातer करोमुख्यs specअगरic to this VFE.
 * @vfe: VFE Device
 */
अटल पूर्णांक vfe_pm_करोमुख्य_on(काष्ठा vfe_device *vfe)
अणु
	वापस 0;
पूर्ण

/*
 * vfe_queue_buffer - Add empty buffer
 * @vid: Video device काष्ठाure
 * @buf: Buffer to be enqueued
 *
 * Add an empty buffer - depending on the current number of buffers it will be
 * put in pending buffer queue or directly given to the hardware to be filled.
 *
 * Return 0 on success or a negative error code otherwise
 */
अटल पूर्णांक vfe_queue_buffer(काष्ठा camss_video *vid,
			    काष्ठा camss_buffer *buf)
अणु
	काष्ठा vfe_line *line = container_of(vid, काष्ठा vfe_line, video_out);
	काष्ठा vfe_device *vfe = to_vfe(line);
	काष्ठा vfe_output *output;
	अचिन्हित दीर्घ flags;

	output = &line->output;

	spin_lock_irqsave(&vfe->output_lock, flags);

	अगर (output->state == VFE_OUTPUT_ON && output->gen2.active_num < 2) अणु
		output->buf[output->gen2.active_num++] = buf;
		vfe_wm_update(vfe, output->wm_idx[0], buf->addr[0], line);
	पूर्ण अन्यथा अणु
		vfe_buf_add_pending(output, buf);
	पूर्ण

	spin_unlock_irqrestore(&vfe->output_lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा vfe_isr_ops vfe_isr_ops_170 = अणु
	.reset_ack = vfe_isr_reset_ack,
	.halt_ack = vfe_isr_halt_ack,
	.reg_update = vfe_isr_reg_update,
	.sof = vfe_isr_sof,
	.comp_करोne = vfe_isr_comp_करोne,
	.wm_करोne = vfe_isr_wm_करोne,
पूर्ण;

अटल स्थिर काष्ठा camss_video_ops vfe_video_ops_170 = अणु
	.queue_buffer = vfe_queue_buffer,
	.flush_buffers = vfe_flush_buffers,
पूर्ण;

अटल व्योम vfe_subdev_init(काष्ठा device *dev, काष्ठा vfe_device *vfe)
अणु
	vfe->isr_ops = vfe_isr_ops_170;
	vfe->video_ops = vfe_video_ops_170;

	vfe->line_num = VFE_LINE_NUM_GEN2;
पूर्ण

स्थिर काष्ठा vfe_hw_ops vfe_ops_170 = अणु
	.global_reset = vfe_global_reset,
	.hw_version_पढ़ो = vfe_hw_version_पढ़ो,
	.isr_पढ़ो = vfe_isr_पढ़ो,
	.isr = vfe_isr,
	.pm_करोमुख्य_off = vfe_pm_करोमुख्य_off,
	.pm_करोमुख्य_on = vfe_pm_करोमुख्य_on,
	.reg_update_clear = vfe_reg_update_clear,
	.reg_update = vfe_reg_update,
	.subdev_init = vfe_subdev_init,
	.vfe_disable = vfe_disable,
	.vfe_enable = vfe_enable,
	.vfe_halt = vfe_halt,
	.violation_पढ़ो = vfe_violation_पढ़ो,
पूर्ण;
