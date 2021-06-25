<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) STMicroelectronics SA 2015
 * Authors: Yannick Fertre <yannick.fertre@st.com>
 *          Hugues Fruchet <hugues.fruchet@st.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#अगर_घोषित CONFIG_VIDEO_STI_HVA_DEBUGFS
#समावेश <linux/seq_file.h>
#पूर्ण_अगर

#समावेश "hva.h"
#समावेश "hva-hw.h"

/* HVA रेजिस्टर offsets */
#घोषणा HVA_HIF_REG_RST                 0x0100U
#घोषणा HVA_HIF_REG_RST_ACK             0x0104U
#घोषणा HVA_HIF_REG_MIF_CFG             0x0108U
#घोषणा HVA_HIF_REG_HEC_MIF_CFG         0x010CU
#घोषणा HVA_HIF_REG_CFL                 0x0110U
#घोषणा HVA_HIF_FIFO_CMD                0x0114U
#घोषणा HVA_HIF_FIFO_STS                0x0118U
#घोषणा HVA_HIF_REG_SFL                 0x011CU
#घोषणा HVA_HIF_REG_IT_ACK              0x0120U
#घोषणा HVA_HIF_REG_ERR_IT_ACK          0x0124U
#घोषणा HVA_HIF_REG_LMI_ERR             0x0128U
#घोषणा HVA_HIF_REG_EMI_ERR             0x012CU
#घोषणा HVA_HIF_REG_HEC_MIF_ERR         0x0130U
#घोषणा HVA_HIF_REG_HEC_STS             0x0134U
#घोषणा HVA_HIF_REG_HVC_STS             0x0138U
#घोषणा HVA_HIF_REG_HJE_STS             0x013CU
#घोषणा HVA_HIF_REG_CNT                 0x0140U
#घोषणा HVA_HIF_REG_HEC_CHKSYN_DIS      0x0144U
#घोषणा HVA_HIF_REG_CLK_GATING          0x0148U
#घोषणा HVA_HIF_REG_VERSION             0x014CU
#घोषणा HVA_HIF_REG_BSM                 0x0150U

/* define value क्रम version id रेजिस्टर (HVA_HIF_REG_VERSION) */
#घोषणा VERSION_ID_MASK	0x0000FFFF

/* define values क्रम BSM रेजिस्टर (HVA_HIF_REG_BSM) */
#घोषणा BSM_CFG_VAL1	0x0003F000
#घोषणा BSM_CFG_VAL2	0x003F0000

/* define values क्रम memory पूर्णांकerface रेजिस्टर (HVA_HIF_REG_MIF_CFG) */
#घोषणा MIF_CFG_VAL1	0x04460446
#घोषणा MIF_CFG_VAL2	0x04460806
#घोषणा MIF_CFG_VAL3	0x00000000

/* define value क्रम HEC memory पूर्णांकerface रेजिस्टर (HVA_HIF_REG_MIF_CFG) */
#घोषणा HEC_MIF_CFG_VAL	0x000000C4

/*  Bits definition क्रम घड़ी gating रेजिस्टर (HVA_HIF_REG_CLK_GATING) */
#घोषणा CLK_GATING_HVC	BIT(0)
#घोषणा CLK_GATING_HEC	BIT(1)
#घोषणा CLK_GATING_HJE	BIT(2)

/* fix hva घड़ी rate */
#घोषणा CLK_RATE		300000000

/* fix delay क्रम pmrunसमय */
#घोषणा AUTOSUSPEND_DELAY_MS	3

/*
 * hw encode error values
 * NO_ERROR: Success, Task OK
 * H264_BITSTREAM_OVERSIZE: VECH264 Bitstream size > bitstream buffer
 * H264_FRAME_SKIPPED: VECH264 Frame skipped (refers to CPB Buffer Size)
 * H264_SLICE_LIMIT_SIZE: VECH264 MB > slice limit size
 * H264_MAX_SLICE_NUMBER: VECH264 max slice number reached
 * H264_SLICE_READY: VECH264 Slice पढ़ोy
 * TASK_LIST_FULL: HVA/FPC task list full
		   (discard latest transक्रमm command)
 * UNKNOWN_COMMAND: Transक्रमm command not known by HVA/FPC
 * WRONG_CODEC_OR_RESOLUTION: Wrong Codec or Resolution Selection
 * NO_INT_COMPLETION: Time-out on पूर्णांकerrupt completion
 * LMI_ERR: Local Memory Interface Error
 * EMI_ERR: External Memory Interface Error
 * HECMI_ERR: HEC Memory Interface Error
 */
क्रमागत hva_hw_error अणु
	NO_ERROR = 0x0,
	H264_BITSTREAM_OVERSIZE = 0x2,
	H264_FRAME_SKIPPED = 0x4,
	H264_SLICE_LIMIT_SIZE = 0x5,
	H264_MAX_SLICE_NUMBER = 0x7,
	H264_SLICE_READY = 0x8,
	TASK_LIST_FULL = 0xF0,
	UNKNOWN_COMMAND = 0xF1,
	WRONG_CODEC_OR_RESOLUTION = 0xF4,
	NO_INT_COMPLETION = 0x100,
	LMI_ERR = 0x101,
	EMI_ERR = 0x102,
	HECMI_ERR = 0x103,
पूर्ण;

अटल irqवापस_t hva_hw_its_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा hva_dev *hva = data;

	/* पढ़ो status रेजिस्टरs */
	hva->sts_reg = पढ़ोl_relaxed(hva->regs + HVA_HIF_FIFO_STS);
	hva->sfl_reg = पढ़ोl_relaxed(hva->regs + HVA_HIF_REG_SFL);

	/* acknowledge पूर्णांकerruption */
	ग_लिखोl_relaxed(0x1, hva->regs + HVA_HIF_REG_IT_ACK);

	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल irqवापस_t hva_hw_its_irq_thपढ़ो(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा hva_dev *hva = arg;
	काष्ठा device *dev = hva_to_dev(hva);
	u32 status = hva->sts_reg & 0xFF;
	u8 ctx_id = 0;
	काष्ठा hva_ctx *ctx = शून्य;

	dev_dbg(dev, "%s     %s: status: 0x%02x fifo level: 0x%02x\n",
		HVA_PREFIX, __func__, hva->sts_reg & 0xFF, hva->sfl_reg & 0xF);

	/*
	 * status: task_id[31:16] client_id[15:8] status[7:0]
	 * the context identअगरier is retrieved from the client identअगरier
	 */
	ctx_id = (hva->sts_reg & 0xFF00) >> 8;
	अगर (ctx_id >= HVA_MAX_INSTANCES) अणु
		dev_err(dev, "%s     %s: bad context identifier: %d\n",
			ctx->name, __func__, ctx_id);
		ctx->hw_err = true;
		जाओ out;
	पूर्ण

	ctx = hva->instances[ctx_id];
	अगर (!ctx)
		जाओ out;

	चयन (status) अणु
	हाल NO_ERROR:
		dev_dbg(dev, "%s     %s: no error\n",
			ctx->name, __func__);
		ctx->hw_err = false;
		अवरोध;
	हाल H264_SLICE_READY:
		dev_dbg(dev, "%s     %s: h264 slice ready\n",
			ctx->name, __func__);
		ctx->hw_err = false;
		अवरोध;
	हाल H264_FRAME_SKIPPED:
		dev_dbg(dev, "%s     %s: h264 frame skipped\n",
			ctx->name, __func__);
		ctx->hw_err = false;
		अवरोध;
	हाल H264_BITSTREAM_OVERSIZE:
		dev_err(dev, "%s     %s:h264 bitstream oversize\n",
			ctx->name, __func__);
		ctx->hw_err = true;
		अवरोध;
	हाल H264_SLICE_LIMIT_SIZE:
		dev_err(dev, "%s     %s: h264 slice limit size is reached\n",
			ctx->name, __func__);
		ctx->hw_err = true;
		अवरोध;
	हाल H264_MAX_SLICE_NUMBER:
		dev_err(dev, "%s     %s: h264 max slice number is reached\n",
			ctx->name, __func__);
		ctx->hw_err = true;
		अवरोध;
	हाल TASK_LIST_FULL:
		dev_err(dev, "%s     %s:task list full\n",
			ctx->name, __func__);
		ctx->hw_err = true;
		अवरोध;
	हाल UNKNOWN_COMMAND:
		dev_err(dev, "%s     %s: command not known\n",
			ctx->name, __func__);
		ctx->hw_err = true;
		अवरोध;
	हाल WRONG_CODEC_OR_RESOLUTION:
		dev_err(dev, "%s     %s: wrong codec or resolution\n",
			ctx->name, __func__);
		ctx->hw_err = true;
		अवरोध;
	शेष:
		dev_err(dev, "%s     %s: status not recognized\n",
			ctx->name, __func__);
		ctx->hw_err = true;
		अवरोध;
	पूर्ण
out:
	complete(&hva->पूर्णांकerrupt);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t hva_hw_err_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा hva_dev *hva = data;

	/* पढ़ो status रेजिस्टरs */
	hva->sts_reg = पढ़ोl_relaxed(hva->regs + HVA_HIF_FIFO_STS);
	hva->sfl_reg = पढ़ोl_relaxed(hva->regs + HVA_HIF_REG_SFL);

	/* पढ़ो error रेजिस्टरs */
	hva->lmi_err_reg = पढ़ोl_relaxed(hva->regs + HVA_HIF_REG_LMI_ERR);
	hva->emi_err_reg = पढ़ोl_relaxed(hva->regs + HVA_HIF_REG_EMI_ERR);
	hva->hec_mअगर_err_reg = पढ़ोl_relaxed(hva->regs +
					     HVA_HIF_REG_HEC_MIF_ERR);

	/* acknowledge पूर्णांकerruption */
	ग_लिखोl_relaxed(0x1, hva->regs + HVA_HIF_REG_IT_ACK);

	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल irqवापस_t hva_hw_err_irq_thपढ़ो(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा hva_dev *hva = arg;
	काष्ठा device *dev = hva_to_dev(hva);
	u8 ctx_id = 0;
	काष्ठा hva_ctx *ctx;

	dev_dbg(dev, "%s     status: 0x%02x fifo level: 0x%02x\n",
		HVA_PREFIX, hva->sts_reg & 0xFF, hva->sfl_reg & 0xF);

	/*
	 * status: task_id[31:16] client_id[15:8] status[7:0]
	 * the context identअगरier is retrieved from the client identअगरier
	 */
	ctx_id = (hva->sts_reg & 0xFF00) >> 8;
	अगर (ctx_id >= HVA_MAX_INSTANCES) अणु
		dev_err(dev, "%s     bad context identifier: %d\n", HVA_PREFIX,
			ctx_id);
		जाओ out;
	पूर्ण

	ctx = hva->instances[ctx_id];
	अगर (!ctx)
		जाओ out;

	अगर (hva->lmi_err_reg) अणु
		dev_err(dev, "%s     local memory interface error: 0x%08x\n",
			ctx->name, hva->lmi_err_reg);
		ctx->hw_err = true;
	पूर्ण

	अगर (hva->emi_err_reg) अणु
		dev_err(dev, "%s     external memory interface error: 0x%08x\n",
			ctx->name, hva->emi_err_reg);
		ctx->hw_err = true;
	पूर्ण

	अगर (hva->hec_mअगर_err_reg) अणु
		dev_err(dev, "%s     hec memory interface error: 0x%08x\n",
			ctx->name, hva->hec_mअगर_err_reg);
		ctx->hw_err = true;
	पूर्ण
out:
	complete(&hva->पूर्णांकerrupt);

	वापस IRQ_HANDLED;
पूर्ण

अटल अचिन्हित दीर्घ पूर्णांक hva_hw_get_ip_version(काष्ठा hva_dev *hva)
अणु
	काष्ठा device *dev = hva_to_dev(hva);
	अचिन्हित दीर्घ पूर्णांक version;

	अगर (pm_runसमय_get_sync(dev) < 0) अणु
		dev_err(dev, "%s     failed to get pm_runtime\n", HVA_PREFIX);
		pm_runसमय_put_noidle(dev);
		mutex_unlock(&hva->protect_mutex);
		वापस -EFAULT;
	पूर्ण

	version = पढ़ोl_relaxed(hva->regs + HVA_HIF_REG_VERSION) &
				VERSION_ID_MASK;

	pm_runसमय_put_स्वतःsuspend(dev);

	चयन (version) अणु
	हाल HVA_VERSION_V400:
		dev_dbg(dev, "%s     IP hardware version 0x%lx\n",
			HVA_PREFIX, version);
		अवरोध;
	शेष:
		dev_err(dev, "%s     unknown IP hardware version 0x%lx\n",
			HVA_PREFIX, version);
		version = HVA_VERSION_UNKNOWN;
		अवरोध;
	पूर्ण

	वापस version;
पूर्ण

पूर्णांक hva_hw_probe(काष्ठा platक्रमm_device *pdev, काष्ठा hva_dev *hva)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *regs;
	काष्ठा resource *esram;
	पूर्णांक ret;

	WARN_ON(!hva);

	/* get memory क्रम रेजिस्टरs */
	regs = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	hva->regs = devm_ioremap_resource(dev, regs);
	अगर (IS_ERR(hva->regs)) अणु
		dev_err(dev, "%s     failed to get regs\n", HVA_PREFIX);
		वापस PTR_ERR(hva->regs);
	पूर्ण

	/* get memory क्रम esram */
	esram = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	अगर (!esram) अणु
		dev_err(dev, "%s     failed to get esram\n", HVA_PREFIX);
		वापस -ENODEV;
	पूर्ण
	hva->esram_addr = esram->start;
	hva->esram_size = resource_size(esram);

	dev_info(dev, "%s     esram reserved for address: 0x%x size:%d\n",
		 HVA_PREFIX, hva->esram_addr, hva->esram_size);

	/* get घड़ी resource */
	hva->clk = devm_clk_get(dev, "clk_hva");
	अगर (IS_ERR(hva->clk)) अणु
		dev_err(dev, "%s     failed to get clock\n", HVA_PREFIX);
		वापस PTR_ERR(hva->clk);
	पूर्ण

	ret = clk_prepare(hva->clk);
	अगर (ret < 0) अणु
		dev_err(dev, "%s     failed to prepare clock\n", HVA_PREFIX);
		hva->clk = ERR_PTR(-EINVAL);
		वापस ret;
	पूर्ण

	/* get status पूर्णांकerruption resource */
	ret  = platक्रमm_get_irq(pdev, 0);
	अगर (ret < 0)
		जाओ err_clk;
	hva->irq_its = ret;

	ret = devm_request_thपढ़ोed_irq(dev, hva->irq_its, hva_hw_its_पूर्णांकerrupt,
					hva_hw_its_irq_thपढ़ो,
					IRQF_ONESHOT,
					"hva_its_irq", hva);
	अगर (ret) अणु
		dev_err(dev, "%s     failed to install status IRQ 0x%x\n",
			HVA_PREFIX, hva->irq_its);
		जाओ err_clk;
	पूर्ण
	disable_irq(hva->irq_its);

	/* get error पूर्णांकerruption resource */
	ret = platक्रमm_get_irq(pdev, 1);
	अगर (ret < 0)
		जाओ err_clk;
	hva->irq_err = ret;

	ret = devm_request_thपढ़ोed_irq(dev, hva->irq_err, hva_hw_err_पूर्णांकerrupt,
					hva_hw_err_irq_thपढ़ो,
					IRQF_ONESHOT,
					"hva_err_irq", hva);
	अगर (ret) अणु
		dev_err(dev, "%s     failed to install error IRQ 0x%x\n",
			HVA_PREFIX, hva->irq_err);
		जाओ err_clk;
	पूर्ण
	disable_irq(hva->irq_err);

	/* initialise protection mutex */
	mutex_init(&hva->protect_mutex);

	/* initialise completion संकेत */
	init_completion(&hva->पूर्णांकerrupt);

	/* initialise runसमय घातer management */
	pm_runसमय_set_स्वतःsuspend_delay(dev, AUTOSUSPEND_DELAY_MS);
	pm_runसमय_use_स्वतःsuspend(dev);
	pm_runसमय_set_suspended(dev);
	pm_runसमय_enable(dev);

	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0) अणु
		dev_err(dev, "%s     failed to set PM\n", HVA_PREFIX);
		जाओ err_pm;
	पूर्ण

	/* check IP hardware version */
	hva->ip_version = hva_hw_get_ip_version(hva);

	अगर (hva->ip_version == HVA_VERSION_UNKNOWN) अणु
		ret = -EINVAL;
		जाओ err_pm;
	पूर्ण

	dev_info(dev, "%s     found hva device (version 0x%lx)\n", HVA_PREFIX,
		 hva->ip_version);

	वापस 0;

err_pm:
	pm_runसमय_put(dev);
err_clk:
	अगर (hva->clk)
		clk_unprepare(hva->clk);

	वापस ret;
पूर्ण

व्योम hva_hw_हटाओ(काष्ठा hva_dev *hva)
अणु
	काष्ठा device *dev = hva_to_dev(hva);

	disable_irq(hva->irq_its);
	disable_irq(hva->irq_err);

	pm_runसमय_put_स्वतःsuspend(dev);
	pm_runसमय_disable(dev);
पूर्ण

पूर्णांक hva_hw_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा hva_dev *hva = dev_get_drvdata(dev);

	clk_disable_unprepare(hva->clk);

	वापस 0;
पूर्ण

पूर्णांक hva_hw_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा hva_dev *hva = dev_get_drvdata(dev);

	अगर (clk_prepare_enable(hva->clk)) अणु
		dev_err(hva->dev, "%s     failed to prepare hva clk\n",
			HVA_PREFIX);
		वापस -EINVAL;
	पूर्ण

	अगर (clk_set_rate(hva->clk, CLK_RATE)) अणु
		dev_err(dev, "%s     failed to set clock frequency\n",
			HVA_PREFIX);
		clk_disable_unprepare(hva->clk);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक hva_hw_execute_task(काष्ठा hva_ctx *ctx, क्रमागत hva_hw_cmd_type cmd,
			काष्ठा hva_buffer *task)
अणु
	काष्ठा hva_dev *hva = ctx_to_hdev(ctx);
	काष्ठा device *dev = hva_to_dev(hva);
	u8 client_id = ctx->id;
	पूर्णांक ret;
	u32 reg = 0;

	mutex_lock(&hva->protect_mutex);

	/* enable irqs */
	enable_irq(hva->irq_its);
	enable_irq(hva->irq_err);

	अगर (pm_runसमय_get_sync(dev) < 0) अणु
		dev_err(dev, "%s     failed to get pm_runtime\n", ctx->name);
		ctx->sys_errors++;
		ret = -EFAULT;
		जाओ out;
	पूर्ण

	reg = पढ़ोl_relaxed(hva->regs + HVA_HIF_REG_CLK_GATING);
	चयन (cmd) अणु
	हाल H264_ENC:
		reg |= CLK_GATING_HVC;
		अवरोध;
	शेष:
		dev_dbg(dev, "%s     unknown command 0x%x\n", ctx->name, cmd);
		ctx->encode_errors++;
		ret = -EFAULT;
		जाओ out;
	पूर्ण
	ग_लिखोl_relaxed(reg, hva->regs + HVA_HIF_REG_CLK_GATING);

	dev_dbg(dev, "%s     %s: write configuration registers\n", ctx->name,
		__func__);

	/* byte swap config */
	ग_लिखोl_relaxed(BSM_CFG_VAL1, hva->regs + HVA_HIF_REG_BSM);

	/* define Max Opcode Size and Max Message Size क्रम LMI and EMI */
	ग_लिखोl_relaxed(MIF_CFG_VAL3, hva->regs + HVA_HIF_REG_MIF_CFG);
	ग_लिखोl_relaxed(HEC_MIF_CFG_VAL, hva->regs + HVA_HIF_REG_HEC_MIF_CFG);

	/*
	 * command FIFO: task_id[31:16] client_id[15:8] command_type[7:0]
	 * the context identअगरier is provided as client identअगरier to the
	 * hardware, and is retrieved in the पूर्णांकerrupt functions from the
	 * status रेजिस्टर
	 */
	dev_dbg(dev, "%s     %s: send task (cmd: %d, task_desc: %pad)\n",
		ctx->name, __func__, cmd + (client_id << 8), &task->paddr);
	ग_लिखोl_relaxed(cmd + (client_id << 8), hva->regs + HVA_HIF_FIFO_CMD);
	ग_लिखोl_relaxed(task->paddr, hva->regs + HVA_HIF_FIFO_CMD);

	अगर (!रुको_क्रम_completion_समयout(&hva->पूर्णांकerrupt,
					 msecs_to_jअगरfies(2000))) अणु
		dev_err(dev, "%s     %s: time out on completion\n", ctx->name,
			__func__);
		ctx->encode_errors++;
		ret = -EFAULT;
		जाओ out;
	पूर्ण

	/* get encoding status */
	ret = ctx->hw_err ? -EFAULT : 0;

	ctx->encode_errors += ctx->hw_err ? 1 : 0;

out:
	disable_irq(hva->irq_its);
	disable_irq(hva->irq_err);

	चयन (cmd) अणु
	हाल H264_ENC:
		reg &= ~CLK_GATING_HVC;
		ग_लिखोl_relaxed(reg, hva->regs + HVA_HIF_REG_CLK_GATING);
		अवरोध;
	शेष:
		dev_dbg(dev, "%s     unknown command 0x%x\n", ctx->name, cmd);
	पूर्ण

	pm_runसमय_put_स्वतःsuspend(dev);
	mutex_unlock(&hva->protect_mutex);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_VIDEO_STI_HVA_DEBUGFS
#घोषणा DUMP(reg) seq_म_लिखो(s, "%-30s: 0x%08X\n",\
			     #reg, पढ़ोl_relaxed(hva->regs + reg))

व्योम hva_hw_dump_regs(काष्ठा hva_dev *hva, काष्ठा seq_file *s)
अणु
	काष्ठा device *dev = hva_to_dev(hva);

	mutex_lock(&hva->protect_mutex);

	अगर (pm_runसमय_get_sync(dev) < 0) अणु
		seq_माला_दो(s, "Cannot wake up IP\n");
		pm_runसमय_put_noidle(dev);
		mutex_unlock(&hva->protect_mutex);
		वापस;
	पूर्ण

	seq_म_लिखो(s, "Registers:\nReg @ = 0x%p\n", hva->regs);

	DUMP(HVA_HIF_REG_RST);
	DUMP(HVA_HIF_REG_RST_ACK);
	DUMP(HVA_HIF_REG_MIF_CFG);
	DUMP(HVA_HIF_REG_HEC_MIF_CFG);
	DUMP(HVA_HIF_REG_CFL);
	DUMP(HVA_HIF_REG_SFL);
	DUMP(HVA_HIF_REG_LMI_ERR);
	DUMP(HVA_HIF_REG_EMI_ERR);
	DUMP(HVA_HIF_REG_HEC_MIF_ERR);
	DUMP(HVA_HIF_REG_HEC_STS);
	DUMP(HVA_HIF_REG_HVC_STS);
	DUMP(HVA_HIF_REG_HJE_STS);
	DUMP(HVA_HIF_REG_CNT);
	DUMP(HVA_HIF_REG_HEC_CHKSYN_DIS);
	DUMP(HVA_HIF_REG_CLK_GATING);
	DUMP(HVA_HIF_REG_VERSION);

	pm_runसमय_put_स्वतःsuspend(dev);
	mutex_unlock(&hva->protect_mutex);
पूर्ण
#पूर्ण_अगर
