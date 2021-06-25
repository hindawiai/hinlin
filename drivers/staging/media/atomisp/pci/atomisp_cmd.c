<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम Medअगरield PNW Camera Imaging ISP subप्रणाली.
 *
 * Copyright (c) 2010 Intel Corporation. All Rights Reserved.
 *
 * Copyright (c) 2010 Silicon Hive www.siliconhive.com.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version
 * 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 *
 */
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/firmware.h>
#समावेश <linux/pci.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/समयr.h>

#समावेश <यंत्र/iosf_mbi.h>

#समावेश <media/v4l2-event.h>
#समावेश <media/videobuf-vदो_स्मृति.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश "atomisp_trace_event.h"

#समावेश "atomisp_cmd.h"
#समावेश "atomisp_common.h"
#समावेश "atomisp_fops.h"
#समावेश "atomisp_internal.h"
#समावेश "atomisp_ioctl.h"
#समावेश "atomisp-regs.h"
#समावेश "atomisp_tables.h"
#समावेश "atomisp_acc.h"
#समावेश "atomisp_compat.h"
#समावेश "atomisp_subdev.h"
#समावेश "atomisp_dfs_tables.h"

#समावेश <hmm/hmm.h>

#समावेश "sh_css_hrt.h"
#समावेश "sh_css_defs.h"
#समावेश "system_global.h"
#समावेश "sh_css_internal.h"
#समावेश "sh_css_sp.h"
#समावेश "gp_device.h"
#समावेश "device_access.h"
#समावेश "irq.h"

#समावेश "ia_css_types.h"
#समावेश "ia_css_stream.h"
#समावेश "ia_css_debug.h"
#समावेश "bits.h"

/* We should never need to run the flash क्रम more than 2 frames.
 * At 15fps this means 133ms. We set the समयout a bit दीर्घer.
 * Each flash driver is supposed to set its own समयout, but
 * just in हाल someone अन्यथा changed the समयout, we set it
 * here to make sure we करोn't damage the flash hardware. */
#घोषणा FLASH_TIMEOUT 800 /* ms */

जोड़ host अणु
	काष्ठा अणु
		व्योम *kernel_ptr;
		व्योम __user *user_ptr;
		पूर्णांक size;
	पूर्ण scalar;
	काष्ठा अणु
		व्योम *hmm_ptr;
	पूर्ण ptr;
पूर्ण;

/*
 * get sensor:dis71430/ov2720 related info from v4l2_subdev->priv data field.
 * subdev->priv is set in mrst.c
 */
काष्ठा camera_mipi_info *atomisp_to_sensor_mipi_info(काष्ठा v4l2_subdev *sd)
अणु
	वापस (काष्ठा camera_mipi_info *)v4l2_get_subdev_hostdata(sd);
पूर्ण

/*
 * get काष्ठा atomisp_video_pipe from v4l2 video_device
 */
काष्ठा atomisp_video_pipe *atomisp_to_video_pipe(काष्ठा video_device *dev)
अणु
	वापस (काष्ठा atomisp_video_pipe *)
	       container_of(dev, काष्ठा atomisp_video_pipe, vdev);
पूर्ण

/*
 * get काष्ठा atomisp_acc_pipe from v4l2 video_device
 */
काष्ठा atomisp_acc_pipe *atomisp_to_acc_pipe(काष्ठा video_device *dev)
अणु
	वापस (काष्ठा atomisp_acc_pipe *)
	       container_of(dev, काष्ठा atomisp_acc_pipe, vdev);
पूर्ण

अटल अचिन्हित लघु atomisp_get_sensor_fps(काष्ठा atomisp_sub_device *asd)
अणु
	काष्ठा v4l2_subdev_frame_पूर्णांकerval fi = अणु 0 पूर्ण;
	काष्ठा atomisp_device *isp = asd->isp;

	अचिन्हित लघु fps = 0;
	पूर्णांक ret;

	ret = v4l2_subdev_call(isp->inमाला_दो[asd->input_curr].camera,
			       video, g_frame_पूर्णांकerval, &fi);

	अगर (!ret && fi.पूर्णांकerval.numerator)
		fps = fi.पूर्णांकerval.denominator / fi.पूर्णांकerval.numerator;

	वापस fps;
पूर्ण

/*
 * DFS progress is shown as follows:
 * 1. Target frequency is calculated according to FPS/Resolution/ISP running
 *    mode.
 * 2. Ratio is calculated using क्रमmula: 2 * HPLL / target frequency - 1
 *    with proper rounding.
 * 3. Set ratio to ISPFREQ40, 1 to FREQVALID and ISPFREQGUAR40
 *    to 200MHz in ISPSSPM1.
 * 4. Wait क्रम FREQVALID to be cleared by P-Unit.
 * 5. Wait क्रम field ISPFREQSTAT40 in ISPSSPM1 turn to ratio set in 3.
 */
अटल पूर्णांक ग_लिखो_target_freq_to_hw(काष्ठा atomisp_device *isp,
				   अचिन्हित पूर्णांक new_freq)
अणु
	अचिन्हित पूर्णांक ratio, समयout, guar_ratio;
	u32 isp_sspm1 = 0;
	पूर्णांक i;

	अगर (!isp->hpll_freq) अणु
		dev_err(isp->dev, "failed to get hpll_freq. no change to freq\n");
		वापस -EINVAL;
	पूर्ण

	iosf_mbi_पढ़ो(BT_MBI_UNIT_PMC, MBI_REG_READ, ISPSSPM1, &isp_sspm1);
	अगर (isp_sspm1 & ISP_FREQ_VALID_MASK) अणु
		dev_dbg(isp->dev, "clearing ISPSSPM1 valid bit.\n");
		iosf_mbi_ग_लिखो(BT_MBI_UNIT_PMC, MBI_REG_WRITE, ISPSSPM1,
			       isp_sspm1 & ~(1 << ISP_FREQ_VALID_OFFSET));
	पूर्ण

	ratio = (2 * isp->hpll_freq + new_freq / 2) / new_freq - 1;
	guar_ratio = (2 * isp->hpll_freq + 200 / 2) / 200 - 1;

	iosf_mbi_पढ़ो(BT_MBI_UNIT_PMC, MBI_REG_READ, ISPSSPM1, &isp_sspm1);
	isp_sspm1 &= ~(0x1F << ISP_REQ_FREQ_OFFSET);

	क्रम (i = 0; i < ISP_DFS_TRY_TIMES; i++) अणु
		iosf_mbi_ग_लिखो(BT_MBI_UNIT_PMC, MBI_REG_WRITE, ISPSSPM1,
			       isp_sspm1
			       | ratio << ISP_REQ_FREQ_OFFSET
			       | 1 << ISP_FREQ_VALID_OFFSET
			       | guar_ratio << ISP_REQ_GUAR_FREQ_OFFSET);

		iosf_mbi_पढ़ो(BT_MBI_UNIT_PMC, MBI_REG_READ, ISPSSPM1, &isp_sspm1);
		समयout = 20;
		जबतक ((isp_sspm1 & ISP_FREQ_VALID_MASK) && समयout) अणु
			iosf_mbi_पढ़ो(BT_MBI_UNIT_PMC, MBI_REG_READ, ISPSSPM1, &isp_sspm1);
			dev_dbg(isp->dev, "waiting for ISPSSPM1 valid bit to be 0.\n");
			udelay(100);
			समयout--;
		पूर्ण

		अगर (समयout != 0)
			अवरोध;
	पूर्ण

	अगर (समयout == 0) अणु
		dev_err(isp->dev, "DFS failed due to HW error.\n");
		वापस -EINVAL;
	पूर्ण

	iosf_mbi_पढ़ो(BT_MBI_UNIT_PMC, MBI_REG_READ, ISPSSPM1, &isp_sspm1);
	समयout = 10;
	जबतक (((isp_sspm1 >> ISP_FREQ_STAT_OFFSET) != ratio) && समयout) अणु
		iosf_mbi_पढ़ो(BT_MBI_UNIT_PMC, MBI_REG_READ, ISPSSPM1, &isp_sspm1);
		dev_dbg(isp->dev, "waiting for ISPSSPM1 status bit to be 0x%x.\n",
			new_freq);
		udelay(100);
		समयout--;
	पूर्ण
	अगर (समयout == 0) अणु
		dev_err(isp->dev, "DFS target freq is rejected by HW.\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक atomisp_freq_scaling(काष्ठा atomisp_device *isp,
			 क्रमागत atomisp_dfs_mode mode,
			 bool क्रमce)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(isp->dev);
	/* FIXME! Only use subdev[0] status yet */
	काष्ठा atomisp_sub_device *asd = &isp->asd[0];
	स्थिर काष्ठा atomisp_dfs_config *dfs;
	अचिन्हित पूर्णांक new_freq;
	काष्ठा atomisp_freq_scaling_rule curr_rules;
	पूर्णांक i, ret;
	अचिन्हित लघु fps = 0;

	अगर (isp->sw_contex.घातer_state != ATOM_ISP_POWER_UP) अणु
		dev_err(isp->dev, "DFS cannot proceed due to no power.\n");
		वापस -EINVAL;
	पूर्ण

	अगर ((pdev->device & ATOMISP_PCI_DEVICE_SOC_MASK) ==
	    ATOMISP_PCI_DEVICE_SOC_CHT && ATOMISP_USE_YUVPP(asd))
		isp->dfs = &dfs_config_cht_soc;

	dfs = isp->dfs;

	अगर (dfs->lowest_freq == 0 || dfs->max_freq_at_vmin == 0 ||
	    dfs->highest_freq == 0 || dfs->dfs_table_size == 0 ||
	    !dfs->dfs_table) अणु
		dev_err(isp->dev, "DFS configuration is invalid.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (mode == ATOMISP_DFS_MODE_LOW) अणु
		new_freq = dfs->lowest_freq;
		जाओ करोne;
	पूर्ण

	अगर (mode == ATOMISP_DFS_MODE_MAX) अणु
		new_freq = dfs->highest_freq;
		जाओ करोne;
	पूर्ण

	fps = atomisp_get_sensor_fps(asd);
	अगर (fps == 0) अणु
		dev_info(isp->dev,
			 "Sensor didn't report FPS. Using DFS max mode.\n");
		new_freq = dfs->highest_freq;
		जाओ करोne;
	पूर्ण

	curr_rules.width = asd->fmt[asd->capture_pad].fmt.width;
	curr_rules.height = asd->fmt[asd->capture_pad].fmt.height;
	curr_rules.fps = fps;
	curr_rules.run_mode = asd->run_mode->val;
	/*
	 * For continuous mode, we need to make the capture setting applied
	 * since preview mode, because there is no chance to करो this when
	 * starting image capture.
	 */
	अगर (asd->continuous_mode->val) अणु
		अगर (asd->run_mode->val == ATOMISP_RUN_MODE_VIDEO)
			curr_rules.run_mode = ATOMISP_RUN_MODE_SDV;
		अन्यथा
			curr_rules.run_mode =
			    ATOMISP_RUN_MODE_CONTINUOUS_CAPTURE;
	पूर्ण

	/* search क्रम the target frequency by looping freq rules*/
	क्रम (i = 0; i < dfs->dfs_table_size; i++) अणु
		अगर (curr_rules.width != dfs->dfs_table[i].width &&
		    dfs->dfs_table[i].width != ISP_FREQ_RULE_ANY)
			जारी;
		अगर (curr_rules.height != dfs->dfs_table[i].height &&
		    dfs->dfs_table[i].height != ISP_FREQ_RULE_ANY)
			जारी;
		अगर (curr_rules.fps != dfs->dfs_table[i].fps &&
		    dfs->dfs_table[i].fps != ISP_FREQ_RULE_ANY)
			जारी;
		अगर (curr_rules.run_mode != dfs->dfs_table[i].run_mode &&
		    dfs->dfs_table[i].run_mode != ISP_FREQ_RULE_ANY)
			जारी;
		अवरोध;
	पूर्ण

	अगर (i == dfs->dfs_table_size)
		new_freq = dfs->max_freq_at_vmin;
	अन्यथा
		new_freq = dfs->dfs_table[i].isp_freq;

करोne:
	dev_dbg(isp->dev, "DFS target frequency=%d.\n", new_freq);

	अगर ((new_freq == isp->sw_contex.running_freq) && !क्रमce)
		वापस 0;

	dev_dbg(isp->dev, "Programming DFS frequency to %d\n", new_freq);

	ret = ग_लिखो_target_freq_to_hw(isp, new_freq);
	अगर (!ret) अणु
		isp->sw_contex.running_freq = new_freq;
		trace_ipu_pstate(new_freq, -1);
	पूर्ण
	वापस ret;
पूर्ण

/*
 * reset and restore ISP
 */
पूर्णांक atomisp_reset(काष्ठा atomisp_device *isp)
अणु
	/* Reset ISP by घातer-cycling it */
	पूर्णांक ret = 0;

	dev_dbg(isp->dev, "%s\n", __func__);
	atomisp_css_suspend(isp);
	ret = atomisp_runसमय_suspend(isp->dev);
	अगर (ret < 0)
		dev_err(isp->dev, "atomisp_runtime_suspend failed, %d\n", ret);
	ret = atomisp_mrfld_घातer_करोwn(isp);
	अगर (ret < 0) अणु
		dev_err(isp->dev, "can not disable ISP power\n");
	पूर्ण अन्यथा अणु
		ret = atomisp_mrfld_घातer_up(isp);
		अगर (ret < 0)
			dev_err(isp->dev, "can not enable ISP power\n");
		ret = atomisp_runसमय_resume(isp->dev);
		अगर (ret < 0)
			dev_err(isp->dev, "atomisp_runtime_resume failed, %d\n", ret);
	पूर्ण
	ret = atomisp_css_resume(isp);
	अगर (ret)
		isp->isp_fatal_error = true;

	वापस ret;
पूर्ण

/*
 * पूर्णांकerrupt disable functions
 */
अटल व्योम disable_isp_irq(क्रमागत hrt_isp_css_irq irq)
अणु
	irq_disable_channel(IRQ0_ID, irq);

	अगर (irq != hrt_isp_css_irq_sp)
		वापस;

	cnd_sp_irq_enable(SP0_ID, false);
पूर्ण

/*
 * पूर्णांकerrupt clean function
 */
अटल व्योम clear_isp_irq(क्रमागत hrt_isp_css_irq irq)
अणु
	irq_clear_all(IRQ0_ID);
पूर्ण

व्योम atomisp_msi_irq_init(काष्ठा atomisp_device *isp)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(isp->dev);
	u32 msg32;
	u16 msg16;

	pci_पढ़ो_config_dword(pdev, PCI_MSI_CAPID, &msg32);
	msg32 |= 1 << MSI_ENABLE_BIT;
	pci_ग_लिखो_config_dword(pdev, PCI_MSI_CAPID, msg32);

	msg32 = (1 << INTR_IER) | (1 << INTR_IIR);
	pci_ग_लिखो_config_dword(pdev, PCI_INTERRUPT_CTRL, msg32);

	pci_पढ़ो_config_word(pdev, PCI_COMMAND, &msg16);
	msg16 |= (PCI_COMMAND_MEMORY | PCI_COMMAND_MASTER |
		  PCI_COMMAND_INTX_DISABLE);
	pci_ग_लिखो_config_word(pdev, PCI_COMMAND, msg16);
पूर्ण

व्योम atomisp_msi_irq_uninit(काष्ठा atomisp_device *isp)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(isp->dev);
	u32 msg32;
	u16 msg16;

	pci_पढ़ो_config_dword(pdev, PCI_MSI_CAPID, &msg32);
	msg32 &=  ~(1 << MSI_ENABLE_BIT);
	pci_ग_लिखो_config_dword(pdev, PCI_MSI_CAPID, msg32);

	msg32 = 0x0;
	pci_ग_लिखो_config_dword(pdev, PCI_INTERRUPT_CTRL, msg32);

	pci_पढ़ो_config_word(pdev, PCI_COMMAND, &msg16);
	msg16 &= ~(PCI_COMMAND_MASTER);
	pci_ग_लिखो_config_word(pdev, PCI_COMMAND, msg16);
पूर्ण

अटल व्योम atomisp_sof_event(काष्ठा atomisp_sub_device *asd)
अणु
	काष्ठा v4l2_event event = अणु0पूर्ण;

	event.type = V4L2_EVENT_FRAME_SYNC;
	event.u.frame_sync.frame_sequence = atomic_पढ़ो(&asd->sof_count);

	v4l2_event_queue(asd->subdev.devnode, &event);
पूर्ण

व्योम atomisp_eof_event(काष्ठा atomisp_sub_device *asd, uपूर्णांक8_t exp_id)
अणु
	काष्ठा v4l2_event event = अणु0पूर्ण;

	event.type = V4L2_EVENT_FRAME_END;
	event.u.frame_sync.frame_sequence = exp_id;

	v4l2_event_queue(asd->subdev.devnode, &event);
पूर्ण

अटल व्योम atomisp_3a_stats_पढ़ोy_event(काष्ठा atomisp_sub_device *asd,
	uपूर्णांक8_t exp_id)
अणु
	काष्ठा v4l2_event event = अणु0पूर्ण;

	event.type = V4L2_EVENT_ATOMISP_3A_STATS_READY;
	event.u.frame_sync.frame_sequence = exp_id;

	v4l2_event_queue(asd->subdev.devnode, &event);
पूर्ण

अटल व्योम atomisp_metadata_पढ़ोy_event(काष्ठा atomisp_sub_device *asd,
	क्रमागत atomisp_metadata_type md_type)
अणु
	काष्ठा v4l2_event event = अणु0पूर्ण;

	event.type = V4L2_EVENT_ATOMISP_METADATA_READY;
	event.u.data[0] = md_type;

	v4l2_event_queue(asd->subdev.devnode, &event);
पूर्ण

अटल व्योम atomisp_reset_event(काष्ठा atomisp_sub_device *asd)
अणु
	काष्ठा v4l2_event event = अणु0पूर्ण;

	event.type = V4L2_EVENT_ATOMISP_CSS_RESET;

	v4l2_event_queue(asd->subdev.devnode, &event);
पूर्ण

अटल व्योम prपूर्णांक_csi_rx_errors(क्रमागत mipi_port_id port,
				काष्ठा atomisp_device *isp)
अणु
	u32 infos = 0;

	atomisp_css_rx_get_irq_info(port, &infos);

	dev_err(isp->dev, "CSI Receiver port %d errors:\n", port);
	अगर (infos & IA_CSS_RX_IRQ_INFO_BUFFER_OVERRUN)
		dev_err(isp->dev, "  buffer overrun");
	अगर (infos & IA_CSS_RX_IRQ_INFO_ERR_SOT)
		dev_err(isp->dev, "  start-of-transmission error");
	अगर (infos & IA_CSS_RX_IRQ_INFO_ERR_SOT_SYNC)
		dev_err(isp->dev, "  start-of-transmission sync error");
	अगर (infos & IA_CSS_RX_IRQ_INFO_ERR_CONTROL)
		dev_err(isp->dev, "  control error");
	अगर (infos & IA_CSS_RX_IRQ_INFO_ERR_ECC_DOUBLE)
		dev_err(isp->dev, "  2 or more ECC errors");
	अगर (infos & IA_CSS_RX_IRQ_INFO_ERR_CRC)
		dev_err(isp->dev, "  CRC mismatch");
	अगर (infos & IA_CSS_RX_IRQ_INFO_ERR_UNKNOWN_ID)
		dev_err(isp->dev, "  unknown error");
	अगर (infos & IA_CSS_RX_IRQ_INFO_ERR_FRAME_SYNC)
		dev_err(isp->dev, "  frame sync error");
	अगर (infos & IA_CSS_RX_IRQ_INFO_ERR_FRAME_DATA)
		dev_err(isp->dev, "  frame data error");
	अगर (infos & IA_CSS_RX_IRQ_INFO_ERR_DATA_TIMEOUT)
		dev_err(isp->dev, "  data timeout");
	अगर (infos & IA_CSS_RX_IRQ_INFO_ERR_UNKNOWN_ESC)
		dev_err(isp->dev, "  unknown escape command entry");
	अगर (infos & IA_CSS_RX_IRQ_INFO_ERR_LINE_SYNC)
		dev_err(isp->dev, "  line sync error");
पूर्ण

/* Clear irq reg */
अटल व्योम clear_irq_reg(काष्ठा atomisp_device *isp)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(isp->dev);
	u32 msg_ret;

	pci_पढ़ो_config_dword(pdev, PCI_INTERRUPT_CTRL, &msg_ret);
	msg_ret |= 1 << INTR_IIR;
	pci_ग_लिखो_config_dword(pdev, PCI_INTERRUPT_CTRL, msg_ret);
पूर्ण

अटल काष्ठा atomisp_sub_device *
__get_asd_from_port(काष्ठा atomisp_device *isp, क्रमागत mipi_port_id port)
अणु
	पूर्णांक i;

	/* Check which isp subdev to send eof */
	क्रम (i = 0; i < isp->num_of_streams; i++) अणु
		काष्ठा atomisp_sub_device *asd = &isp->asd[i];
		काष्ठा camera_mipi_info *mipi_info;

		mipi_info = atomisp_to_sensor_mipi_info(
				isp->inमाला_दो[asd->input_curr].camera);

		अगर (asd->streaming == ATOMISP_DEVICE_STREAMING_ENABLED &&
		    __get_mipi_port(isp, mipi_info->port) == port) अणु
			वापस asd;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

/* पूर्णांकerrupt handling function*/
irqवापस_t atomisp_isr(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा atomisp_device *isp = (काष्ठा atomisp_device *)dev;
	काष्ठा atomisp_sub_device *asd;
	काष्ठा atomisp_css_event eof_event;
	अचिन्हित पूर्णांक irq_infos = 0;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	spin_lock_irqsave(&isp->lock, flags);
	अगर (isp->sw_contex.घातer_state != ATOM_ISP_POWER_UP ||
	    !isp->css_initialized) अणु
		spin_unlock_irqrestore(&isp->lock, flags);
		वापस IRQ_HANDLED;
	पूर्ण
	err = atomisp_css_irq_translate(isp, &irq_infos);
	अगर (err) अणु
		spin_unlock_irqrestore(&isp->lock, flags);
		वापस IRQ_NONE;
	पूर्ण

	clear_irq_reg(isp);

	अगर (!atomisp_streaming_count(isp) && !atomisp_is_acc_enabled(isp))
		जाओ out_nowake;

	क्रम (i = 0; i < isp->num_of_streams; i++) अणु
		asd = &isp->asd[i];

		अगर (asd->streaming != ATOMISP_DEVICE_STREAMING_ENABLED)
			जारी;
		/*
		 * Current SOF only support one stream, so the SOF only valid
		 * either solely one stream is running
		 */
		अगर (irq_infos & IA_CSS_IRQ_INFO_CSS_RECEIVER_SOF) अणु
			atomic_inc(&asd->sof_count);
			atomisp_sof_event(asd);

			/* If sequence_temp and sequence are the same
			 * there where no frames lost so we can increase
			 * sequence_temp.
			 * If not then processing of frame is still in progress
			 * and driver needs to keep old sequence_temp value.
			 * NOTE: There is assumption here that ISP will not
			 * start processing next frame from sensor beक्रमe old
			 * one is completely करोne. */
			अगर (atomic_पढ़ो(&asd->sequence) == atomic_पढ़ो(
				&asd->sequence_temp))
				atomic_set(&asd->sequence_temp,
					   atomic_पढ़ो(&asd->sof_count));
		पूर्ण
		अगर (irq_infos & IA_CSS_IRQ_INFO_EVENTS_READY)
			atomic_set(&asd->sequence,
				   atomic_पढ़ो(&asd->sequence_temp));
	पूर्ण

	अगर (irq_infos & IA_CSS_IRQ_INFO_CSS_RECEIVER_SOF) अणु
		dev_dbg_ratelimited(isp->dev,
				    "irq:0x%x (SOF)\n",
				    irq_infos);
		irq_infos &= ~IA_CSS_IRQ_INFO_CSS_RECEIVER_SOF;
	पूर्ण

	अगर ((irq_infos & IA_CSS_IRQ_INFO_INPUT_SYSTEM_ERROR) ||
	    (irq_infos & IA_CSS_IRQ_INFO_IF_ERROR)) अणु
		/* handle mipi receiver error */
		u32 rx_infos;
		क्रमागत mipi_port_id port;

		क्रम (port = MIPI_PORT0_ID; port <= MIPI_PORT2_ID;
		     port++) अणु
			prपूर्णांक_csi_rx_errors(port, isp);
			atomisp_css_rx_get_irq_info(port, &rx_infos);
			atomisp_css_rx_clear_irq_info(port, rx_infos);
		पूर्ण
	पूर्ण

	अगर (irq_infos & IA_CSS_IRQ_INFO_ISYS_EVENTS_READY) अणु
		जबतक (ia_css_dequeue_isys_event(&eof_event.event) ==
		       0) अणु
			/* खातापूर्ण Event करोes not have the css_pipe वापसed */
			asd = __get_asd_from_port(isp, eof_event.event.port);
			अगर (!asd) अणु
				dev_err(isp->dev, "%s: ISYS event, but no subdev.event:%d",
					__func__, eof_event.event.type);
				जारी;
			पूर्ण

			atomisp_eof_event(asd, eof_event.event.exp_id);
			dev_dbg_ratelimited(isp->dev,
					    "%s ISYS event: EOF exp_id %d, asd %d\n",
					    __func__, eof_event.event.exp_id,
					    asd->index);
		पूर्ण

		irq_infos &= ~IA_CSS_IRQ_INFO_ISYS_EVENTS_READY;
		अगर (irq_infos == 0)
			जाओ out_nowake;
	पूर्ण

	spin_unlock_irqrestore(&isp->lock, flags);

	dev_dbg_ratelimited(isp->dev, "irq:0x%x (unhandled)\n", irq_infos);

	वापस IRQ_WAKE_THREAD;

out_nowake:
	spin_unlock_irqrestore(&isp->lock, flags);

	अगर (irq_infos)
		dev_dbg_ratelimited(isp->dev, "irq:0x%x (ignored, as not streaming anymore)\n",
				    irq_infos);

	वापस IRQ_HANDLED;
पूर्ण

व्योम atomisp_clear_css_buffer_counters(काष्ठा atomisp_sub_device *asd)
अणु
	पूर्णांक i;

	स_रखो(asd->s3a_bufs_in_css, 0, माप(asd->s3a_bufs_in_css));
	क्रम (i = 0; i < ATOMISP_INPUT_STREAM_NUM; i++)
		स_रखो(asd->metadata_bufs_in_css[i], 0,
		       माप(asd->metadata_bufs_in_css[i]));
	asd->dis_bufs_in_css = 0;
	asd->video_out_capture.buffers_in_css = 0;
	asd->video_out_vf.buffers_in_css = 0;
	asd->video_out_preview.buffers_in_css = 0;
	asd->video_out_video_capture.buffers_in_css = 0;
पूर्ण

/* ISP2400 */
bool atomisp_buffers_queued(काष्ठा atomisp_sub_device *asd)
अणु
	वापस asd->video_out_capture.buffers_in_css ||
	       asd->video_out_vf.buffers_in_css ||
	       asd->video_out_preview.buffers_in_css ||
	       asd->video_out_video_capture.buffers_in_css;
पूर्ण

/* ISP2401 */
bool atomisp_buffers_queued_pipe(काष्ठा atomisp_video_pipe *pipe)
अणु
	वापस pipe->buffers_in_css ? true : false;
पूर्ण

/* 0x100000 is the start of dmem inside SP */
#घोषणा SP_DMEM_BASE	0x100000

व्योम dump_sp_dmem(काष्ठा atomisp_device *isp, अचिन्हित पूर्णांक addr,
		  अचिन्हित पूर्णांक size)
अणु
	अचिन्हित पूर्णांक data = 0;
	अचिन्हित पूर्णांक size32 = DIV_ROUND_UP(size, माप(u32));

	dev_dbg(isp->dev, "atomisp mmio base: %p\n", isp->base);
	dev_dbg(isp->dev, "%s, addr:0x%x, size: %d, size32: %d\n", __func__,
		addr, size, size32);
	अगर (size32 * 4 + addr > 0x4000) अणु
		dev_err(isp->dev, "illegal size (%d) or addr (0x%x)\n",
			size32, addr);
		वापस;
	पूर्ण
	addr += SP_DMEM_BASE;
	addr &= 0x003FFFFF;
	करो अणु
		data = पढ़ोl(isp->base + addr);
		dev_dbg(isp->dev, "%s, \t [0x%x]:0x%x\n", __func__, addr, data);
		addr += माप(u32);
	पूर्ण जबतक (--size32);
पूर्ण

अटल काष्ठा videobuf_buffer *atomisp_css_frame_to_vbuf(
    काष्ठा atomisp_video_pipe *pipe, काष्ठा ia_css_frame *frame)
अणु
	काष्ठा videobuf_vदो_स्मृति_memory *vm_mem;
	काष्ठा ia_css_frame *handle;
	पूर्णांक i;

	क्रम (i = 0; pipe->capq.bufs[i]; i++) अणु
		vm_mem = pipe->capq.bufs[i]->priv;
		handle = vm_mem->vaddr;
		अगर (handle && handle->data == frame->data)
			वापस pipe->capq.bufs[i];
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम atomisp_flush_video_pipe(काष्ठा atomisp_sub_device *asd,
				     काष्ठा atomisp_video_pipe *pipe)
अणु
	अचिन्हित दीर्घ irqflags;
	पूर्णांक i;

	अगर (!pipe->users)
		वापस;

	क्रम (i = 0; pipe->capq.bufs[i]; i++) अणु
		spin_lock_irqsave(&pipe->irq_lock, irqflags);
		अगर (pipe->capq.bufs[i]->state == VIDEOBUF_ACTIVE ||
		    pipe->capq.bufs[i]->state == VIDEOBUF_QUEUED) अणु
			pipe->capq.bufs[i]->ts = kसमय_get_ns();
			pipe->capq.bufs[i]->field_count =
			    atomic_पढ़ो(&asd->sequence) << 1;
			dev_dbg(asd->isp->dev, "release buffers on device %s\n",
				pipe->vdev.name);
			अगर (pipe->capq.bufs[i]->state == VIDEOBUF_QUEUED)
				list_del_init(&pipe->capq.bufs[i]->queue);
			pipe->capq.bufs[i]->state = VIDEOBUF_ERROR;
			wake_up(&pipe->capq.bufs[i]->करोne);
		पूर्ण
		spin_unlock_irqrestore(&pipe->irq_lock, irqflags);
	पूर्ण
पूर्ण

/* Returns queued buffers back to video-core */
व्योम atomisp_flush_bufs_and_wakeup(काष्ठा atomisp_sub_device *asd)
अणु
	atomisp_flush_video_pipe(asd, &asd->video_out_capture);
	atomisp_flush_video_pipe(asd, &asd->video_out_vf);
	atomisp_flush_video_pipe(asd, &asd->video_out_preview);
	atomisp_flush_video_pipe(asd, &asd->video_out_video_capture);
पूर्ण

/* clean out the parameters that did not apply */
व्योम atomisp_flush_params_queue(काष्ठा atomisp_video_pipe *pipe)
अणु
	काष्ठा atomisp_css_params_with_list *param;

	जबतक (!list_empty(&pipe->per_frame_params)) अणु
		param = list_entry(pipe->per_frame_params.next,
				   काष्ठा atomisp_css_params_with_list, list);
		list_del(&param->list);
		atomisp_मुक्त_css_parameters(&param->params);
		kvमुक्त(param);
	पूर्ण
पूर्ण

/* Re-queue per-frame parameters */
अटल व्योम atomisp_recover_params_queue(काष्ठा atomisp_video_pipe *pipe)
अणु
	काष्ठा atomisp_css_params_with_list *param;
	पूर्णांक i;

	क्रम (i = 0; i < VIDEO_MAX_FRAME; i++) अणु
		param = pipe->frame_params[i];
		अगर (param)
			list_add_tail(&param->list, &pipe->per_frame_params);
		pipe->frame_params[i] = शून्य;
	पूर्ण
	atomisp_handle_parameter_and_buffer(pipe);
पूर्ण

/* find atomisp_video_pipe with css pipe id, buffer type and atomisp run_mode */
अटल काष्ठा atomisp_video_pipe *__atomisp_get_pipe(
    काष्ठा atomisp_sub_device *asd,
    क्रमागत atomisp_input_stream_id stream_id,
    क्रमागत ia_css_pipe_id css_pipe_id,
    क्रमागत ia_css_buffer_type buf_type)
अणु
	काष्ठा atomisp_device *isp = asd->isp;

	अगर (css_pipe_id == IA_CSS_PIPE_ID_COPY &&
	    isp->inमाला_दो[asd->input_curr].camera_caps->
	    sensor[asd->sensor_curr].stream_num > 1) अणु
		चयन (stream_id) अणु
		हाल ATOMISP_INPUT_STREAM_PREVIEW:
			वापस &asd->video_out_preview;
		हाल ATOMISP_INPUT_STREAM_POSTVIEW:
			वापस &asd->video_out_vf;
		हाल ATOMISP_INPUT_STREAM_VIDEO:
			वापस &asd->video_out_video_capture;
		हाल ATOMISP_INPUT_STREAM_CAPTURE:
		शेष:
			वापस &asd->video_out_capture;
		पूर्ण
	पूर्ण

	/* video is same in online as in continuouscapture mode */
	अगर (asd->vfpp->val == ATOMISP_VFPP_DISABLE_LOWLAT) अणु
		/*
		 * Disable vf_pp and run CSS in still capture mode. In this
		 * mode, CSS करोes not cause extra latency with buffering, but
		 * scaling is not available.
		 */
		वापस &asd->video_out_capture;
	पूर्ण अन्यथा अगर (asd->vfpp->val == ATOMISP_VFPP_DISABLE_SCALER) अणु
		/*
		 * Disable vf_pp and run CSS in video mode. This allows using
		 * ISP scaling but it has one frame delay due to CSS पूर्णांकernal
		 * buffering.
		 */
		वापस &asd->video_out_video_capture;
	पूर्ण अन्यथा अगर (css_pipe_id == IA_CSS_PIPE_ID_YUVPP) अणु
		/*
		 * to SOC camera, yuvpp pipe is run क्रम capture/video/SDV/ZSL.
		 */
		अगर (asd->continuous_mode->val) अणु
			अगर (asd->run_mode->val == ATOMISP_RUN_MODE_VIDEO) अणु
				/* SDV हाल */
				चयन (buf_type) अणु
				हाल IA_CSS_BUFFER_TYPE_SEC_OUTPUT_FRAME:
					वापस &asd->video_out_video_capture;
				हाल IA_CSS_BUFFER_TYPE_SEC_VF_OUTPUT_FRAME:
					वापस &asd->video_out_preview;
				हाल IA_CSS_BUFFER_TYPE_OUTPUT_FRAME:
					वापस &asd->video_out_capture;
				शेष:
					वापस &asd->video_out_vf;
				पूर्ण
			पूर्ण अन्यथा अगर (asd->run_mode->val == ATOMISP_RUN_MODE_PREVIEW) अणु
				/* ZSL हाल */
				चयन (buf_type) अणु
				हाल IA_CSS_BUFFER_TYPE_SEC_OUTPUT_FRAME:
					वापस &asd->video_out_preview;
				हाल IA_CSS_BUFFER_TYPE_OUTPUT_FRAME:
					वापस &asd->video_out_capture;
				शेष:
					वापस &asd->video_out_vf;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अगर (buf_type == IA_CSS_BUFFER_TYPE_OUTPUT_FRAME) अणु
			चयन (asd->run_mode->val) अणु
			हाल ATOMISP_RUN_MODE_VIDEO:
				वापस &asd->video_out_video_capture;
			हाल ATOMISP_RUN_MODE_PREVIEW:
				वापस &asd->video_out_preview;
			शेष:
				वापस &asd->video_out_capture;
			पूर्ण
		पूर्ण अन्यथा अगर (buf_type == IA_CSS_BUFFER_TYPE_VF_OUTPUT_FRAME) अणु
			अगर (asd->run_mode->val == ATOMISP_RUN_MODE_VIDEO)
				वापस &asd->video_out_preview;
			अन्यथा
				वापस &asd->video_out_vf;
		पूर्ण
	पूर्ण अन्यथा अगर (asd->run_mode->val == ATOMISP_RUN_MODE_VIDEO) अणु
		/* For online video or SDV video pipe. */
		अगर (css_pipe_id == IA_CSS_PIPE_ID_VIDEO ||
		    css_pipe_id == IA_CSS_PIPE_ID_COPY) अणु
			अगर (buf_type == IA_CSS_BUFFER_TYPE_OUTPUT_FRAME)
				वापस &asd->video_out_video_capture;
			वापस &asd->video_out_preview;
		पूर्ण
	पूर्ण अन्यथा अगर (asd->run_mode->val == ATOMISP_RUN_MODE_PREVIEW) अणु
		/* For online preview or ZSL preview pipe. */
		अगर (css_pipe_id == IA_CSS_PIPE_ID_PREVIEW ||
		    css_pipe_id == IA_CSS_PIPE_ID_COPY)
			वापस &asd->video_out_preview;
	पूर्ण
	/* For capture pipe. */
	अगर (buf_type == IA_CSS_BUFFER_TYPE_VF_OUTPUT_FRAME)
		वापस &asd->video_out_vf;
	वापस &asd->video_out_capture;
पूर्ण

क्रमागत atomisp_metadata_type
atomisp_get_metadata_type(काष्ठा atomisp_sub_device *asd,
			  क्रमागत ia_css_pipe_id pipe_id)
अणु
	अगर (!asd->continuous_mode->val)
		वापस ATOMISP_MAIN_METADATA;

	अगर (pipe_id == IA_CSS_PIPE_ID_CAPTURE) /* online capture pipe */
		वापस ATOMISP_SEC_METADATA;
	अन्यथा
		वापस ATOMISP_MAIN_METADATA;
पूर्ण

व्योम atomisp_buf_करोne(काष्ठा atomisp_sub_device *asd, पूर्णांक error,
		      क्रमागत ia_css_buffer_type buf_type,
		      क्रमागत ia_css_pipe_id css_pipe_id,
		      bool q_buffers, क्रमागत atomisp_input_stream_id stream_id)
अणु
	काष्ठा videobuf_buffer *vb = शून्य;
	काष्ठा atomisp_video_pipe *pipe = शून्य;
	काष्ठा atomisp_css_buffer buffer;
	bool requeue = false;
	पूर्णांक err;
	अचिन्हित दीर्घ irqflags;
	काष्ठा ia_css_frame *frame = शून्य;
	काष्ठा atomisp_s3a_buf *s3a_buf = शून्य, *_s3a_buf_पंचांगp;
	काष्ठा atomisp_dis_buf *dis_buf = शून्य, *_dis_buf_पंचांगp;
	काष्ठा atomisp_metadata_buf *md_buf = शून्य, *_md_buf_पंचांगp;
	क्रमागत atomisp_metadata_type md_type;
	काष्ठा atomisp_device *isp = asd->isp;
	काष्ठा v4l2_control ctrl;
	bool reset_wdt_समयr = false;

	अगर (
	    buf_type != IA_CSS_BUFFER_TYPE_METADATA &&
	    buf_type != IA_CSS_BUFFER_TYPE_3A_STATISTICS &&
	    buf_type != IA_CSS_BUFFER_TYPE_DIS_STATISTICS &&
	    buf_type != IA_CSS_BUFFER_TYPE_OUTPUT_FRAME &&
	    buf_type != IA_CSS_BUFFER_TYPE_SEC_OUTPUT_FRAME &&
	    buf_type != IA_CSS_BUFFER_TYPE_RAW_OUTPUT_FRAME &&
	    buf_type != IA_CSS_BUFFER_TYPE_SEC_VF_OUTPUT_FRAME &&
	    buf_type != IA_CSS_BUFFER_TYPE_VF_OUTPUT_FRAME) अणु
		dev_err(isp->dev, "%s, unsupported buffer type: %d\n",
			__func__, buf_type);
		वापस;
	पूर्ण

	स_रखो(&buffer, 0, माप(काष्ठा atomisp_css_buffer));
	buffer.css_buffer.type = buf_type;
	err = atomisp_css_dequeue_buffer(asd, stream_id, css_pipe_id,
					 buf_type, &buffer);
	अगर (err) अणु
		dev_err(isp->dev,
			"atomisp_css_dequeue_buffer failed: 0x%x\n", err);
		वापस;
	पूर्ण

	/* need to know the atomisp pipe क्रम frame buffers */
	pipe = __atomisp_get_pipe(asd, stream_id, css_pipe_id, buf_type);
	अगर (!pipe) अणु
		dev_err(isp->dev, "error getting atomisp pipe\n");
		वापस;
	पूर्ण

	चयन (buf_type) अणु
	हाल IA_CSS_BUFFER_TYPE_3A_STATISTICS:
		list_क्रम_each_entry_safe(s3a_buf, _s3a_buf_पंचांगp,
					 &asd->s3a_stats_in_css, list) अणु
			अगर (s3a_buf->s3a_data ==
			    buffer.css_buffer.data.stats_3a) अणु
				list_del_init(&s3a_buf->list);
				list_add_tail(&s3a_buf->list,
					      &asd->s3a_stats_पढ़ोy);
				अवरोध;
			पूर्ण
		पूर्ण

		asd->s3a_bufs_in_css[css_pipe_id]--;
		atomisp_3a_stats_पढ़ोy_event(asd, buffer.css_buffer.exp_id);
		dev_dbg(isp->dev, "%s: s3a stat with exp_id %d is ready\n",
			__func__, s3a_buf->s3a_data->exp_id);
		अवरोध;
	हाल IA_CSS_BUFFER_TYPE_METADATA:
		अगर (error)
			अवरोध;

		md_type = atomisp_get_metadata_type(asd, css_pipe_id);
		list_क्रम_each_entry_safe(md_buf, _md_buf_पंचांगp,
					 &asd->metadata_in_css[md_type], list) अणु
			अगर (md_buf->metadata ==
			    buffer.css_buffer.data.metadata) अणु
				list_del_init(&md_buf->list);
				list_add_tail(&md_buf->list,
					      &asd->metadata_पढ़ोy[md_type]);
				अवरोध;
			पूर्ण
		पूर्ण
		asd->metadata_bufs_in_css[stream_id][css_pipe_id]--;
		atomisp_metadata_पढ़ोy_event(asd, md_type);
		dev_dbg(isp->dev, "%s: metadata with exp_id %d is ready\n",
			__func__, md_buf->metadata->exp_id);
		अवरोध;
	हाल IA_CSS_BUFFER_TYPE_DIS_STATISTICS:
		list_क्रम_each_entry_safe(dis_buf, _dis_buf_पंचांगp,
					 &asd->dis_stats_in_css, list) अणु
			अगर (dis_buf->dis_data ==
			    buffer.css_buffer.data.stats_dvs) अणु
				spin_lock_irqsave(&asd->dis_stats_lock,
						  irqflags);
				list_del_init(&dis_buf->list);
				list_add(&dis_buf->list, &asd->dis_stats);
				asd->params.dis_proj_data_valid = true;
				spin_unlock_irqrestore(&asd->dis_stats_lock,
						       irqflags);
				अवरोध;
			पूर्ण
		पूर्ण
		asd->dis_bufs_in_css--;
		dev_dbg(isp->dev, "%s: dis stat with exp_id %d is ready\n",
			__func__, dis_buf->dis_data->exp_id);
		अवरोध;
	हाल IA_CSS_BUFFER_TYPE_VF_OUTPUT_FRAME:
	हाल IA_CSS_BUFFER_TYPE_SEC_VF_OUTPUT_FRAME:
		अगर (IS_ISP2401)
			reset_wdt_समयr = true;

		pipe->buffers_in_css--;
		frame = buffer.css_buffer.data.frame;
		अगर (!frame) अणु
			WARN_ON(1);
			अवरोध;
		पूर्ण
		अगर (!frame->valid)
			error = true;

		/* FIXME:
		 * YUVPP करोesn't set postview exp_id correctlly in SDV mode.
		 * This is a WORKAROUND to set exp_id. see HSDES-1503911606.
		 */
		अगर (IS_BYT && buf_type == IA_CSS_BUFFER_TYPE_SEC_VF_OUTPUT_FRAME &&
		    asd->continuous_mode->val && ATOMISP_USE_YUVPP(asd))
			frame->exp_id = (asd->postview_exp_id++) %
					(ATOMISP_MAX_EXP_ID + 1);

		dev_dbg(isp->dev, "%s: vf frame with exp_id %d is ready\n",
			__func__, frame->exp_id);
		अगर (asd->params.flash_state == ATOMISP_FLASH_ONGOING) अणु
			अगर (frame->flash_state
			    == IA_CSS_FRAME_FLASH_STATE_PARTIAL)
				dev_dbg(isp->dev, "%s thumb partially flashed\n",
					__func__);
			अन्यथा अगर (frame->flash_state
				 == IA_CSS_FRAME_FLASH_STATE_FULL)
				dev_dbg(isp->dev, "%s thumb completely flashed\n",
					__func__);
			अन्यथा
				dev_dbg(isp->dev, "%s thumb no flash in this frame\n",
					__func__);
		पूर्ण
		vb = atomisp_css_frame_to_vbuf(pipe, frame);
		WARN_ON(!vb);
		अगर (vb)
			pipe->frame_config_id[vb->i] = frame->isp_config_id;
		अगर (css_pipe_id == IA_CSS_PIPE_ID_CAPTURE &&
		    asd->pending_capture_request > 0) अणु
			err = atomisp_css_offline_capture_configure(asd,
				asd->params.offline_parm.num_captures,
				asd->params.offline_parm.skip_frames,
				asd->params.offline_parm.offset);

			asd->pending_capture_request--;

			अगर (IS_ISP2401)
				asd->re_trigger_capture = false;

			dev_dbg(isp->dev, "Trigger capture again for new buffer. err=%d\n",
				err);
		पूर्ण अन्यथा अगर (IS_ISP2401) अणु
			asd->re_trigger_capture = true;
		पूर्ण
		अवरोध;
	हाल IA_CSS_BUFFER_TYPE_OUTPUT_FRAME:
	हाल IA_CSS_BUFFER_TYPE_SEC_OUTPUT_FRAME:
		अगर (IS_ISP2401)
			reset_wdt_समयr = true;

		pipe->buffers_in_css--;
		frame = buffer.css_buffer.data.frame;
		अगर (!frame) अणु
			WARN_ON(1);
			अवरोध;
		पूर्ण

		अगर (!frame->valid)
			error = true;

		/* FIXME:
		 * YUVPP करोesn't set preview exp_id correctlly in ZSL mode.
		 * This is a WORKAROUND to set exp_id. see HSDES-1503911606.
		 */
		अगर (IS_BYT && buf_type == IA_CSS_BUFFER_TYPE_SEC_OUTPUT_FRAME &&
		    asd->continuous_mode->val && ATOMISP_USE_YUVPP(asd))
			frame->exp_id = (asd->preview_exp_id++) %
					(ATOMISP_MAX_EXP_ID + 1);

		dev_dbg(isp->dev, "%s: main frame with exp_id %d is ready\n",
			__func__, frame->exp_id);
		vb = atomisp_css_frame_to_vbuf(pipe, frame);
		अगर (!vb) अणु
			WARN_ON(1);
			अवरोध;
		पूर्ण

		/* मुक्त the parameters */
		अगर (pipe->frame_params[vb->i]) अणु
			अगर (asd->params.dvs_6axis ==
			    pipe->frame_params[vb->i]->params.dvs_6axis)
				asd->params.dvs_6axis = शून्य;
			atomisp_मुक्त_css_parameters(
			    &pipe->frame_params[vb->i]->params);
			kvमुक्त(pipe->frame_params[vb->i]);
			pipe->frame_params[vb->i] = शून्य;
		पूर्ण

		pipe->frame_config_id[vb->i] = frame->isp_config_id;
		ctrl.id = V4L2_CID_FLASH_MODE;
		अगर (asd->params.flash_state == ATOMISP_FLASH_ONGOING) अणु
			अगर (frame->flash_state
			    == IA_CSS_FRAME_FLASH_STATE_PARTIAL) अणु
				asd->frame_status[vb->i] =
				    ATOMISP_FRAME_STATUS_FLASH_PARTIAL;
				dev_dbg(isp->dev, "%s partially flashed\n",
					__func__);
			पूर्ण अन्यथा अगर (frame->flash_state
				   == IA_CSS_FRAME_FLASH_STATE_FULL) अणु
				asd->frame_status[vb->i] =
				    ATOMISP_FRAME_STATUS_FLASH_EXPOSED;
				asd->params.num_flash_frames--;
				dev_dbg(isp->dev, "%s completely flashed\n",
					__func__);
			पूर्ण अन्यथा अणु
				asd->frame_status[vb->i] =
				    ATOMISP_FRAME_STATUS_OK;
				dev_dbg(isp->dev,
					"%s no flash in this frame\n",
					__func__);
			पूर्ण

			/* Check अगर flashing sequence is करोne */
			अगर (asd->frame_status[vb->i] ==
			    ATOMISP_FRAME_STATUS_FLASH_EXPOSED)
				asd->params.flash_state = ATOMISP_FLASH_DONE;
		पूर्ण अन्यथा अगर (isp->flash) अणु
			अगर (v4l2_g_ctrl(isp->flash->ctrl_handler, &ctrl) ==
			    0 && ctrl.value == ATOMISP_FLASH_MODE_TORCH) अणु
				ctrl.id = V4L2_CID_FLASH_TORCH_INTENSITY;
				अगर (v4l2_g_ctrl(isp->flash->ctrl_handler, &ctrl)
				    == 0 && ctrl.value > 0) अणु
					asd->frame_status[vb->i] =
					    ATOMISP_FRAME_STATUS_FLASH_EXPOSED;
				पूर्ण अन्यथा अणु
					asd->frame_status[vb->i] =
					    ATOMISP_FRAME_STATUS_OK;
				पूर्ण
			पूर्ण अन्यथा
				asd->frame_status[vb->i] =
				    ATOMISP_FRAME_STATUS_OK;
		पूर्ण अन्यथा अणु
			asd->frame_status[vb->i] = ATOMISP_FRAME_STATUS_OK;
		पूर्ण

		asd->params.last_frame_status = asd->frame_status[vb->i];

		अगर (asd->continuous_mode->val) अणु
			अगर (css_pipe_id == IA_CSS_PIPE_ID_PREVIEW ||
			    css_pipe_id == IA_CSS_PIPE_ID_VIDEO) अणु
				asd->latest_preview_exp_id = frame->exp_id;
			पूर्ण अन्यथा अगर (css_pipe_id ==
				   IA_CSS_PIPE_ID_CAPTURE) अणु
				अगर (asd->run_mode->val ==
				    ATOMISP_RUN_MODE_VIDEO)
					dev_dbg(isp->dev, "SDV capture raw buffer id: %u\n",
						frame->exp_id);
				अन्यथा
					dev_dbg(isp->dev, "ZSL capture raw buffer id: %u\n",
						frame->exp_id);
			पूर्ण
		पूर्ण
		/*
		 * Only after enabled the raw buffer lock
		 * and in continuous mode.
		 * in preview/video pipe, each buffer will
		 * be locked स्वतःmatically, so record it here.
		 */
		अगर (((css_pipe_id == IA_CSS_PIPE_ID_PREVIEW) ||
		     (css_pipe_id == IA_CSS_PIPE_ID_VIDEO)) &&
		    asd->enable_raw_buffer_lock->val &&
		    asd->continuous_mode->val) अणु
			atomisp_set_raw_buffer_biपंचांगap(asd, frame->exp_id);
			WARN_ON(frame->exp_id > ATOMISP_MAX_EXP_ID);
		पूर्ण

		अगर (asd->params.css_update_params_needed) अणु
			atomisp_apply_css_parameters(asd,
						     &asd->params.css_param);
			अगर (asd->params.css_param.update_flag.dz_config)
				asd->params.config.dz_config = &asd->params.css_param.dz_config;
			/* New global dvs 6axis config should be blocked
			 * here अगर there's a buffer with per-frame parameters
			 * pending in CSS frame buffer queue.
			 * This is to aviod zooming vibration since global
			 * parameters take effect immediately जबतक
			 * per-frame parameters are taken after previous
			 * buffers in CSS got processed.
			 */
			अगर (asd->params.dvs_6axis)
				atomisp_css_set_dvs_6axis(asd,
							  asd->params.dvs_6axis);
			अन्यथा
				asd->params.css_update_params_needed = false;
			/* The update flag should not be cleaned here
			 * since it is still going to be used to make up
			 * following per-frame parameters.
			 * This will पूर्णांकroduce more copy work since each
			 * समय when updating global parameters, the whole
			 * parameter set are applied.
			 * FIXME: A new set of parameter copy functions can
			 * be added to make up per-frame parameters based on
			 * solid काष्ठाures stored in asd->params.css_param
			 * instead of using shaकरोw poपूर्णांकers in update flag.
			 */
			atomisp_css_update_isp_params(asd);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	अगर (vb) अणु
		vb->ts = kसमय_get_ns();
		vb->field_count = atomic_पढ़ो(&asd->sequence) << 1;
		/*mark videobuffer करोne क्रम dequeue*/
		spin_lock_irqsave(&pipe->irq_lock, irqflags);
		vb->state = !error ? VIDEOBUF_DONE : VIDEOBUF_ERROR;
		spin_unlock_irqrestore(&pipe->irq_lock, irqflags);

		/*
		 * Frame capture करोne, wake up any process block on
		 * current active buffer
		 * possibly hold by videobuf_dqbuf()
		 */
		wake_up(&vb->करोne);
	पूर्ण
	अगर (IS_ISP2401)
		atomic_set(&pipe->wdt_count, 0);

	/*
	 * Requeue should only be करोne क्रम 3a and dis buffers.
	 * Queue/dequeue order will change अगर driver recycles image buffers.
	 */
	अगर (requeue) अणु
		err = atomisp_css_queue_buffer(asd,
					       stream_id, css_pipe_id,
					       buf_type, &buffer);
		अगर (err)
			dev_err(isp->dev, "%s, q to css fails: %d\n",
				__func__, err);
		वापस;
	पूर्ण
	अगर (!error && q_buffers)
		atomisp_qbuffers_to_css(asd);

	अगर (IS_ISP2401) अणु
		/* If there are no buffers queued then
		* delete wdt समयr. */
		अगर (asd->streaming != ATOMISP_DEVICE_STREAMING_ENABLED)
			वापस;
		अगर (!atomisp_buffers_queued_pipe(pipe))
			atomisp_wdt_stop_pipe(pipe, false);
		अन्यथा अगर (reset_wdt_समयr)
			/* SOF irq should not reset wdt समयr. */
			atomisp_wdt_refresh_pipe(pipe,
						ATOMISP_WDT_KEEP_CURRENT_DELAY);
	पूर्ण
पूर्ण

व्योम atomisp_delayed_init_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा atomisp_sub_device *asd = container_of(work,
					 काष्ठा atomisp_sub_device,
					 delayed_init_work);
	/*
	 * to SOC camera, use yuvpp pipe and no support continuous mode.
	 */
	अगर (!ATOMISP_USE_YUVPP(asd)) अणु
		काष्ठा v4l2_event event = अणु0पूर्ण;
		काष्ठा ia_css_stream *stream;

		stream = asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL].stream;


		अगर (ia_css_alloc_continuous_frame_reमुख्य(stream))
			वापस;

		ia_css_update_continuous_frames(stream);

		event.type = V4L2_EVENT_ATOMISP_RAW_BUFFERS_ALLOC_DONE;
		v4l2_event_queue(asd->subdev.devnode, &event);
	पूर्ण

	/* संकेत streamon after delayed init is करोne */
	asd->delayed_init = ATOMISP_DELAYED_INIT_DONE;
	complete(&asd->init_करोne);
पूर्ण

अटल व्योम __atomisp_css_recover(काष्ठा atomisp_device *isp, bool isp_समयout)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(isp->dev);
	क्रमागत ia_css_pipe_id css_pipe_id;
	bool stream_restart[MAX_STREAM_NUM] = अणु0पूर्ण;
	bool depth_mode = false;
	पूर्णांक i, ret, depth_cnt = 0;

	अगर (!isp->sw_contex.file_input)
		atomisp_css_irq_enable(isp,
				       IA_CSS_IRQ_INFO_CSS_RECEIVER_SOF, false);

	BUG_ON(isp->num_of_streams > MAX_STREAM_NUM);

	क्रम (i = 0; i < isp->num_of_streams; i++) अणु
		काष्ठा atomisp_sub_device *asd = &isp->asd[i];
		काष्ठा ia_css_pipeline *acc_pipeline;
		काष्ठा ia_css_pipe *acc_pipe = शून्य;

		अगर (asd->streaming != ATOMISP_DEVICE_STREAMING_ENABLED &&
		    !asd->stream_prepared)
			जारी;

		/*
		* AtomISP::रुकोStageUpdate is blocked when WDT happens.
		* By calling acc_करोne() क्रम all loaded fw_handles,
		* HAL will be unblocked.
		*/
		acc_pipe = asd->stream_env[i].pipes[IA_CSS_PIPE_ID_ACC];
		अगर (acc_pipe) अणु
			acc_pipeline = ia_css_pipe_get_pipeline(acc_pipe);
			अगर (acc_pipeline) अणु
				काष्ठा ia_css_pipeline_stage *stage;

				क्रम (stage = acc_pipeline->stages; stage;
				     stage = stage->next) अणु
					स्थिर काष्ठा ia_css_fw_info *fw;

					fw = stage->firmware;
					atomisp_acc_करोne(asd, fw->handle);
				पूर्ण
			पूर्ण
		पूर्ण

		depth_cnt++;

		अगर (asd->delayed_init == ATOMISP_DELAYED_INIT_QUEUED)
			cancel_work_sync(&asd->delayed_init_work);

		complete(&asd->init_करोne);
		asd->delayed_init = ATOMISP_DELAYED_INIT_NOT_QUEUED;

		stream_restart[asd->index] = true;

		asd->streaming = ATOMISP_DEVICE_STREAMING_STOPPING;

		/* stream off sensor */
		ret = v4l2_subdev_call(
			  isp->inमाला_दो[asd->input_curr].
			  camera, video, s_stream, 0);
		अगर (ret)
			dev_warn(isp->dev,
				 "can't stop streaming on sensor!\n");

		atomisp_acc_unload_extensions(asd);

		atomisp_clear_css_buffer_counters(asd);

		css_pipe_id = atomisp_get_css_pipe_id(asd);
		atomisp_css_stop(asd, css_pipe_id, true);

		asd->streaming = ATOMISP_DEVICE_STREAMING_DISABLED;

		asd->preview_exp_id = 1;
		asd->postview_exp_id = 1;
		/* notअगरy HAL the CSS reset */
		dev_dbg(isp->dev,
			"send reset event to %s\n", asd->subdev.devnode->name);
		atomisp_reset_event(asd);
	पूर्ण

	/* clear irq */
	disable_isp_irq(hrt_isp_css_irq_sp);
	clear_isp_irq(hrt_isp_css_irq_sp);

	/* Set the SRSE to 3 beक्रमe resetting */
	pci_ग_लिखो_config_dword(pdev, PCI_I_CONTROL,
			       isp->saved_regs.i_control | MRFLD_PCI_I_CONTROL_SRSE_RESET_MASK);

	/* reset ISP and restore its state */
	isp->isp_समयout = true;
	atomisp_reset(isp);
	isp->isp_समयout = false;

	अगर (!isp_समयout) अणु
		क्रम (i = 0; i < isp->num_of_streams; i++) अणु
			अगर (isp->asd[i].depth_mode->val)
				वापस;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < isp->num_of_streams; i++) अणु
		काष्ठा atomisp_sub_device *asd = &isp->asd[i];

		अगर (!stream_restart[i])
			जारी;

		अगर (isp->inमाला_दो[asd->input_curr].type != खाता_INPUT)
			atomisp_css_input_set_mode(asd,
						   IA_CSS_INPUT_MODE_BUFFERED_SENSOR);

		css_pipe_id = atomisp_get_css_pipe_id(asd);
		अगर (atomisp_css_start(asd, css_pipe_id, true))
			dev_warn(isp->dev,
				 "start SP failed, so do not set streaming to be enable!\n");
		अन्यथा
			asd->streaming = ATOMISP_DEVICE_STREAMING_ENABLED;

		atomisp_csi2_configure(asd);
	पूर्ण

	अगर (!isp->sw_contex.file_input) अणु
		atomisp_css_irq_enable(isp, IA_CSS_IRQ_INFO_CSS_RECEIVER_SOF,
				       atomisp_css_valid_sof(isp));

		अगर (atomisp_freq_scaling(isp, ATOMISP_DFS_MODE_AUTO, true) < 0)
			dev_dbg(isp->dev, "DFS auto failed while recovering!\n");
	पूर्ण अन्यथा अणु
		अगर (atomisp_freq_scaling(isp, ATOMISP_DFS_MODE_MAX, true) < 0)
			dev_dbg(isp->dev, "DFS max failed while recovering!\n");
	पूर्ण

	क्रम (i = 0; i < isp->num_of_streams; i++) अणु
		काष्ठा atomisp_sub_device *asd;

		asd = &isp->asd[i];

		अगर (!stream_restart[i])
			जारी;

		अगर (asd->continuous_mode->val &&
		    asd->delayed_init == ATOMISP_DELAYED_INIT_NOT_QUEUED) अणु
			reinit_completion(&asd->init_करोne);
			asd->delayed_init = ATOMISP_DELAYED_INIT_QUEUED;
			queue_work(asd->delayed_init_workq,
				   &asd->delayed_init_work);
		पूर्ण
		/*
		 * dequeueing buffers is not needed. CSS will recycle
		 * buffers that it has.
		 */
		atomisp_flush_bufs_and_wakeup(asd);

		/* Requeue unprocessed per-frame parameters. */
		atomisp_recover_params_queue(&asd->video_out_capture);
		atomisp_recover_params_queue(&asd->video_out_preview);
		atomisp_recover_params_queue(&asd->video_out_video_capture);

		अगर ((asd->depth_mode->val) &&
		    (depth_cnt == ATOMISP_DEPTH_SENSOR_STREAMON_COUNT)) अणु
			depth_mode = true;
			जारी;
		पूर्ण

		ret = v4l2_subdev_call(
			  isp->inमाला_दो[asd->input_curr].camera, video,
			  s_stream, 1);
		अगर (ret)
			dev_warn(isp->dev,
				 "can't start streaming on sensor!\n");
	पूर्ण

	अगर (depth_mode) अणु
		अगर (atomisp_stream_on_master_slave_sensor(isp, true))
			dev_warn(isp->dev,
				 "master slave sensor stream on failed!\n");
	पूर्ण
पूर्ण

व्योम atomisp_wdt_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा atomisp_device *isp = container_of(work, काष्ठा atomisp_device,
				     wdt_work);
	पूर्णांक i;
	अचिन्हित पूर्णांक pipe_wdt_cnt[MAX_STREAM_NUM][4] = अणु अणु0पूर्ण पूर्ण;
	bool css_recover = false;

	rt_mutex_lock(&isp->mutex);
	अगर (!atomisp_streaming_count(isp)) अणु
		atomic_set(&isp->wdt_work_queued, 0);
		rt_mutex_unlock(&isp->mutex);
		वापस;
	पूर्ण

	अगर (!IS_ISP2401) अणु
		dev_err(isp->dev, "timeout %d of %d\n",
			atomic_पढ़ो(&isp->wdt_count) + 1,
			ATOMISP_ISP_MAX_TIMEOUT_COUNT);

		अगर (atomic_inc_वापस(&isp->wdt_count) < ATOMISP_ISP_MAX_TIMEOUT_COUNT)
			css_recover = true;
	पूर्ण अन्यथा अणु
		css_recover = true;

		क्रम (i = 0; i < isp->num_of_streams; i++) अणु
			काष्ठा atomisp_sub_device *asd = &isp->asd[i];

			pipe_wdt_cnt[i][0] +=
			    atomic_पढ़ो(&asd->video_out_capture.wdt_count);
			pipe_wdt_cnt[i][1] +=
			    atomic_पढ़ो(&asd->video_out_vf.wdt_count);
			pipe_wdt_cnt[i][2] +=
			    atomic_पढ़ो(&asd->video_out_preview.wdt_count);
			pipe_wdt_cnt[i][3] +=
			    atomic_पढ़ो(&asd->video_out_video_capture.wdt_count);
			css_recover =
			    (pipe_wdt_cnt[i][0] <= ATOMISP_ISP_MAX_TIMEOUT_COUNT &&
			    pipe_wdt_cnt[i][1] <= ATOMISP_ISP_MAX_TIMEOUT_COUNT &&
			    pipe_wdt_cnt[i][2] <= ATOMISP_ISP_MAX_TIMEOUT_COUNT &&
			    pipe_wdt_cnt[i][3] <= ATOMISP_ISP_MAX_TIMEOUT_COUNT)
			    ? true : false;
			dev_err(isp->dev,
				"pipe on asd%d timeout cnt: (%d, %d, %d, %d) of %d, recover = %d\n",
				asd->index, pipe_wdt_cnt[i][0], pipe_wdt_cnt[i][1],
				pipe_wdt_cnt[i][2], pipe_wdt_cnt[i][3],
				ATOMISP_ISP_MAX_TIMEOUT_COUNT, css_recover);
		पूर्ण
	पूर्ण

	अगर (css_recover) अणु
		ia_css_debug_dump_sp_sw_debug_info();
		ia_css_debug_dump_debug_info(__func__);
		क्रम (i = 0; i < isp->num_of_streams; i++) अणु
			काष्ठा atomisp_sub_device *asd = &isp->asd[i];

			अगर (asd->streaming != ATOMISP_DEVICE_STREAMING_ENABLED)
				जारी;
			dev_err(isp->dev, "%s, vdev %s buffers in css: %d\n",
				__func__,
				asd->video_out_capture.vdev.name,
				asd->video_out_capture.
				buffers_in_css);
			dev_err(isp->dev,
				"%s, vdev %s buffers in css: %d\n",
				__func__,
				asd->video_out_vf.vdev.name,
				asd->video_out_vf.
				buffers_in_css);
			dev_err(isp->dev,
				"%s, vdev %s buffers in css: %d\n",
				__func__,
				asd->video_out_preview.vdev.name,
				asd->video_out_preview.
				buffers_in_css);
			dev_err(isp->dev,
				"%s, vdev %s buffers in css: %d\n",
				__func__,
				asd->video_out_video_capture.vdev.name,
				asd->video_out_video_capture.
				buffers_in_css);
			dev_err(isp->dev,
				"%s, s3a buffers in css preview pipe:%d\n",
				__func__,
				asd->s3a_bufs_in_css[IA_CSS_PIPE_ID_PREVIEW]);
			dev_err(isp->dev,
				"%s, s3a buffers in css capture pipe:%d\n",
				__func__,
				asd->s3a_bufs_in_css[IA_CSS_PIPE_ID_CAPTURE]);
			dev_err(isp->dev,
				"%s, s3a buffers in css video pipe:%d\n",
				__func__,
				asd->s3a_bufs_in_css[IA_CSS_PIPE_ID_VIDEO]);
			dev_err(isp->dev,
				"%s, dis buffers in css: %d\n",
				__func__, asd->dis_bufs_in_css);
			dev_err(isp->dev,
				"%s, metadata buffers in css preview pipe:%d\n",
				__func__,
				asd->metadata_bufs_in_css
				[ATOMISP_INPUT_STREAM_GENERAL]
				[IA_CSS_PIPE_ID_PREVIEW]);
			dev_err(isp->dev,
				"%s, metadata buffers in css capture pipe:%d\n",
				__func__,
				asd->metadata_bufs_in_css
				[ATOMISP_INPUT_STREAM_GENERAL]
				[IA_CSS_PIPE_ID_CAPTURE]);
			dev_err(isp->dev,
				"%s, metadata buffers in css video pipe:%d\n",
				__func__,
				asd->metadata_bufs_in_css
				[ATOMISP_INPUT_STREAM_GENERAL]
				[IA_CSS_PIPE_ID_VIDEO]);
			अगर (asd->enable_raw_buffer_lock->val) अणु
				अचिन्हित पूर्णांक j;

				dev_err(isp->dev, "%s, raw_buffer_locked_count %d\n",
					__func__, asd->raw_buffer_locked_count);
				क्रम (j = 0; j <= ATOMISP_MAX_EXP_ID / 32; j++)
					dev_err(isp->dev, "%s, raw_buffer_bitmap[%d]: 0x%x\n",
						__func__, j,
						asd->raw_buffer_biपंचांगap[j]);
			पूर्ण
		पूर्ण

		/*sh_css_dump_sp_state();*/
		/*sh_css_dump_isp_state();*/
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < isp->num_of_streams; i++) अणु
			काष्ठा atomisp_sub_device *asd = &isp->asd[i];

			अगर (asd->streaming ==
			    ATOMISP_DEVICE_STREAMING_ENABLED) अणु
				atomisp_clear_css_buffer_counters(asd);
				atomisp_flush_bufs_and_wakeup(asd);
				complete(&asd->init_करोne);
			पूर्ण
			अगर (IS_ISP2401)
				atomisp_wdt_stop(asd, false);
		पूर्ण

		अगर (!IS_ISP2401) अणु
			atomic_set(&isp->wdt_count, 0);
		पूर्ण अन्यथा अणु
			isp->isp_fatal_error = true;
			atomic_set(&isp->wdt_work_queued, 0);

			rt_mutex_unlock(&isp->mutex);
			वापस;
		पूर्ण
	पूर्ण

	__atomisp_css_recover(isp, true);
	अगर (IS_ISP2401) अणु
		क्रम (i = 0; i < isp->num_of_streams; i++) अणु
			काष्ठा atomisp_sub_device *asd = &isp->asd[i];

			अगर (asd->streaming != ATOMISP_DEVICE_STREAMING_ENABLED)
				जारी;

			atomisp_wdt_refresh(asd,
					    isp->sw_contex.file_input ?
					    ATOMISP_ISP_खाता_TIMEOUT_DURATION :
					    ATOMISP_ISP_TIMEOUT_DURATION);
		पूर्ण
	पूर्ण

	dev_err(isp->dev, "timeout recovery handling done\n");
	atomic_set(&isp->wdt_work_queued, 0);

	rt_mutex_unlock(&isp->mutex);
पूर्ण

व्योम atomisp_css_flush(काष्ठा atomisp_device *isp)
अणु
	पूर्णांक i;

	अगर (!atomisp_streaming_count(isp))
		वापस;

	/* Disable wdt */
	क्रम (i = 0; i < isp->num_of_streams; i++) अणु
		काष्ठा atomisp_sub_device *asd = &isp->asd[i];

		atomisp_wdt_stop(asd, true);
	पूर्ण

	/* Start recover */
	__atomisp_css_recover(isp, false);
	/* Restore wdt */
	क्रम (i = 0; i < isp->num_of_streams; i++) अणु
		काष्ठा atomisp_sub_device *asd = &isp->asd[i];

		अगर (asd->streaming !=
		    ATOMISP_DEVICE_STREAMING_ENABLED)
			जारी;

		atomisp_wdt_refresh(asd,
				    isp->sw_contex.file_input ?
				    ATOMISP_ISP_खाता_TIMEOUT_DURATION :
				    ATOMISP_ISP_TIMEOUT_DURATION);
	पूर्ण
	dev_dbg(isp->dev, "atomisp css flush done\n");
पूर्ण

व्योम atomisp_wdt(काष्ठा समयr_list *t)
अणु
	काष्ठा atomisp_sub_device *asd;
	काष्ठा atomisp_device *isp;

	अगर (!IS_ISP2401) अणु
		asd = from_समयr(asd, t, wdt);
		isp = asd->isp;
	पूर्ण अन्यथा अणु
		काष्ठा atomisp_video_pipe *pipe = from_समयr(pipe, t, wdt);

		asd = pipe->asd;
		isp = asd->isp;

		atomic_inc(&pipe->wdt_count);
		dev_warn(isp->dev,
			"[WARNING]asd %d pipe %s ISP timeout %d!\n",
			asd->index, pipe->vdev.name,
			atomic_पढ़ो(&pipe->wdt_count));
	पूर्ण

	अगर (atomic_पढ़ो(&isp->wdt_work_queued)) अणु
		dev_dbg(isp->dev, "ISP watchdog was put into workqueue\n");
		वापस;
	पूर्ण
	atomic_set(&isp->wdt_work_queued, 1);
	queue_work(isp->wdt_work_queue, &isp->wdt_work);
पूर्ण

/* ISP2400 */
व्योम atomisp_wdt_start(काष्ठा atomisp_sub_device *asd)
अणु
	atomisp_wdt_refresh(asd, ATOMISP_ISP_TIMEOUT_DURATION);
पूर्ण

/* ISP2401 */
व्योम atomisp_wdt_refresh_pipe(काष्ठा atomisp_video_pipe *pipe,
			      अचिन्हित पूर्णांक delay)
अणु
	अचिन्हित दीर्घ next;

	अगर (delay != ATOMISP_WDT_KEEP_CURRENT_DELAY)
		pipe->wdt_duration = delay;

	next = jअगरfies + pipe->wdt_duration;

	/* Override next अगर it has been pushed beyon the "next" समय */
	अगर (atomisp_is_wdt_running(pipe) && समय_after(pipe->wdt_expires, next))
		next = pipe->wdt_expires;

	pipe->wdt_expires = next;

	अगर (atomisp_is_wdt_running(pipe))
		dev_dbg(pipe->asd->isp->dev, "WDT will hit after %d ms (%s)\n",
			((पूर्णांक)(next - jअगरfies) * 1000 / HZ), pipe->vdev.name);
	अन्यथा
		dev_dbg(pipe->asd->isp->dev, "WDT starts with %d ms period (%s)\n",
			((पूर्णांक)(next - jअगरfies) * 1000 / HZ), pipe->vdev.name);

	mod_समयr(&pipe->wdt, next);
पूर्ण

व्योम atomisp_wdt_refresh(काष्ठा atomisp_sub_device *asd, अचिन्हित पूर्णांक delay)
अणु
	अगर (!IS_ISP2401) अणु
		अचिन्हित दीर्घ next;

		अगर (delay != ATOMISP_WDT_KEEP_CURRENT_DELAY)
			asd->wdt_duration = delay;

		next = jअगरfies + asd->wdt_duration;

		/* Override next अगर it has been pushed beyon the "next" समय */
		अगर (atomisp_is_wdt_running(asd) && समय_after(asd->wdt_expires, next))
			next = asd->wdt_expires;

		asd->wdt_expires = next;

		अगर (atomisp_is_wdt_running(asd))
			dev_dbg(asd->isp->dev, "WDT will hit after %d ms\n",
				((पूर्णांक)(next - jअगरfies) * 1000 / HZ));
		अन्यथा
			dev_dbg(asd->isp->dev, "WDT starts with %d ms period\n",
				((पूर्णांक)(next - jअगरfies) * 1000 / HZ));

		mod_समयr(&asd->wdt, next);
		atomic_set(&asd->isp->wdt_count, 0);
	पूर्ण अन्यथा अणु
		dev_dbg(asd->isp->dev, "WDT refresh all:\n");
		अगर (atomisp_is_wdt_running(&asd->video_out_capture))
			atomisp_wdt_refresh_pipe(&asd->video_out_capture, delay);
		अगर (atomisp_is_wdt_running(&asd->video_out_preview))
			atomisp_wdt_refresh_pipe(&asd->video_out_preview, delay);
		अगर (atomisp_is_wdt_running(&asd->video_out_vf))
			atomisp_wdt_refresh_pipe(&asd->video_out_vf, delay);
		अगर (atomisp_is_wdt_running(&asd->video_out_video_capture))
			atomisp_wdt_refresh_pipe(&asd->video_out_video_capture, delay);
	पूर्ण
पूर्ण

/* ISP2401 */
व्योम atomisp_wdt_stop_pipe(काष्ठा atomisp_video_pipe *pipe, bool sync)
अणु
	अगर (!atomisp_is_wdt_running(pipe))
		वापस;

	dev_dbg(pipe->asd->isp->dev,
		"WDT stop asd %d (%s)\n", pipe->asd->index, pipe->vdev.name);

	अगर (sync) अणु
		del_समयr_sync(&pipe->wdt);
		cancel_work_sync(&pipe->asd->isp->wdt_work);
	पूर्ण अन्यथा अणु
		del_समयr(&pipe->wdt);
	पूर्ण
पूर्ण

/* ISP 2401 */
व्योम atomisp_wdt_start_pipe(काष्ठा atomisp_video_pipe *pipe)
अणु
	atomisp_wdt_refresh_pipe(pipe, ATOMISP_ISP_TIMEOUT_DURATION);
पूर्ण

व्योम atomisp_wdt_stop(काष्ठा atomisp_sub_device *asd, bool sync)
अणु
	dev_dbg(asd->isp->dev, "WDT stop:\n");

	अगर (!IS_ISP2401) अणु
		अगर (sync) अणु
			del_समयr_sync(&asd->wdt);
			cancel_work_sync(&asd->isp->wdt_work);
		पूर्ण अन्यथा अणु
			del_समयr(&asd->wdt);
		पूर्ण
	पूर्ण अन्यथा अणु
		atomisp_wdt_stop_pipe(&asd->video_out_capture, sync);
		atomisp_wdt_stop_pipe(&asd->video_out_preview, sync);
		atomisp_wdt_stop_pipe(&asd->video_out_vf, sync);
		atomisp_wdt_stop_pipe(&asd->video_out_video_capture, sync);
	पूर्ण
पूर्ण

व्योम atomisp_setup_flash(काष्ठा atomisp_sub_device *asd)
अणु
	काष्ठा atomisp_device *isp = asd->isp;
	काष्ठा v4l2_control ctrl;

	अगर (!isp->flash)
		वापस;

	अगर (asd->params.flash_state != ATOMISP_FLASH_REQUESTED &&
	    asd->params.flash_state != ATOMISP_FLASH_DONE)
		वापस;

	अगर (asd->params.num_flash_frames) अणु
		/* make sure the समयout is set beक्रमe setting flash mode */
		ctrl.id = V4L2_CID_FLASH_TIMEOUT;
		ctrl.value = FLASH_TIMEOUT;

		अगर (v4l2_s_ctrl(शून्य, isp->flash->ctrl_handler, &ctrl)) अणु
			dev_err(isp->dev, "flash timeout configure failed\n");
			वापस;
		पूर्ण

		ia_css_stream_request_flash(asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL].stream);

		asd->params.flash_state = ATOMISP_FLASH_ONGOING;
	पूर्ण अन्यथा अणु
		asd->params.flash_state = ATOMISP_FLASH_IDLE;
	पूर्ण
पूर्ण

irqवापस_t atomisp_isr_thपढ़ो(पूर्णांक irq, व्योम *isp_ptr)
अणु
	काष्ठा atomisp_device *isp = isp_ptr;
	अचिन्हित दीर्घ flags;
	bool frame_करोne_found[MAX_STREAM_NUM] = अणु0पूर्ण;
	bool css_pipe_करोne[MAX_STREAM_NUM] = अणु0पूर्ण;
	अचिन्हित पूर्णांक i;
	काष्ठा atomisp_sub_device *asd;

	dev_dbg(isp->dev, ">%s\n", __func__);

	spin_lock_irqsave(&isp->lock, flags);

	अगर (!atomisp_streaming_count(isp) && !atomisp_is_acc_enabled(isp)) अणु
		spin_unlock_irqrestore(&isp->lock, flags);
		वापस IRQ_HANDLED;
	पूर्ण

	spin_unlock_irqrestore(&isp->lock, flags);

	/*
	 * The standard CSS2.0 API tells the following calling sequence of
	 * dequeue पढ़ोy buffers:
	 * जबतक (ia_css_dequeue_event(...)) अणु
	 *	चयन (event.type) अणु
	 *	...
	 *	ia_css_pipe_dequeue_buffer()
	 *	पूर्ण
	 * पूर्ण
	 * That is, dequeue event and buffer are one after another.
	 *
	 * But the following implementation is to first deuque all the event
	 * to a FIFO, then process the event in the FIFO.
	 * This will not have issue in single stream mode, but it करो have some
	 * issue in multiple stream हाल. The issue is that
	 * ia_css_pipe_dequeue_buffer() will not वापस the corrent buffer in
	 * a specअगरic pipe.
	 *
	 * This is due to ia_css_pipe_dequeue_buffer() करोes not take the
	 * ia_css_pipe parameter.
	 *
	 * So:
	 * For CSS2.0: we change the way to not dequeue all the event at one
	 * समय, instead, dequue one and process one, then another
	 */
	rt_mutex_lock(&isp->mutex);
	अगर (atomisp_css_isr_thपढ़ो(isp, frame_करोne_found, css_pipe_करोne))
		जाओ out;

	क्रम (i = 0; i < isp->num_of_streams; i++) अणु
		asd = &isp->asd[i];
		अगर (asd->streaming != ATOMISP_DEVICE_STREAMING_ENABLED)
			जारी;
		atomisp_setup_flash(asd);
	पूर्ण
out:
	rt_mutex_unlock(&isp->mutex);
	क्रम (i = 0; i < isp->num_of_streams; i++) अणु
		asd = &isp->asd[i];
		अगर (asd->streaming == ATOMISP_DEVICE_STREAMING_ENABLED
		    && css_pipe_करोne[asd->index]
		    && isp->sw_contex.file_input)
			v4l2_subdev_call(isp->inमाला_दो[asd->input_curr].camera,
					 video, s_stream, 1);
		/* FIXME! FIX ACC implementation */
		अगर (asd->acc.pipeline && css_pipe_करोne[asd->index])
			atomisp_css_acc_करोne(asd);
	पूर्ण
	dev_dbg(isp->dev, "<%s\n", __func__);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * utils क्रम buffer allocation/मुक्त
 */

पूर्णांक atomisp_get_frame_pgnr(काष्ठा atomisp_device *isp,
			   स्थिर काष्ठा ia_css_frame *frame, u32 *p_pgnr)
अणु
	अगर (!frame) अणु
		dev_err(isp->dev, "%s: NULL frame pointer ERROR.\n", __func__);
		वापस -EINVAL;
	पूर्ण

	*p_pgnr = DIV_ROUND_UP(frame->data_bytes, PAGE_SIZE);
	वापस 0;
पूर्ण

/*
 * Get पूर्णांकernal fmt according to V4L2 fmt
 */
अटल क्रमागत ia_css_frame_क्रमmat
v4l2_fmt_to_sh_fmt(u32 fmt)
अणु
	चयन (fmt) अणु
	हाल V4L2_PIX_FMT_YUV420:
				वापस IA_CSS_FRAME_FORMAT_YUV420;
	हाल V4L2_PIX_FMT_YVU420:
		वापस IA_CSS_FRAME_FORMAT_YV12;
	हाल V4L2_PIX_FMT_YUV422P:
		वापस IA_CSS_FRAME_FORMAT_YUV422;
	हाल V4L2_PIX_FMT_YUV444:
		वापस IA_CSS_FRAME_FORMAT_YUV444;
	हाल V4L2_PIX_FMT_NV12:
		वापस IA_CSS_FRAME_FORMAT_NV12;
	हाल V4L2_PIX_FMT_NV21:
		वापस IA_CSS_FRAME_FORMAT_NV21;
	हाल V4L2_PIX_FMT_NV16:
		वापस IA_CSS_FRAME_FORMAT_NV16;
	हाल V4L2_PIX_FMT_NV61:
		वापस IA_CSS_FRAME_FORMAT_NV61;
	हाल V4L2_PIX_FMT_UYVY:
		वापस IA_CSS_FRAME_FORMAT_UYVY;
	हाल V4L2_PIX_FMT_YUYV:
		वापस IA_CSS_FRAME_FORMAT_YUYV;
	हाल V4L2_PIX_FMT_RGB24:
		वापस IA_CSS_FRAME_FORMAT_PLANAR_RGB888;
	हाल V4L2_PIX_FMT_RGB32:
		वापस IA_CSS_FRAME_FORMAT_RGBA888;
	हाल V4L2_PIX_FMT_RGB565:
		वापस IA_CSS_FRAME_FORMAT_RGB565;
	हाल V4L2_PIX_FMT_JPEG:
	हाल V4L2_PIX_FMT_CUSTOM_M10MO_RAW:
		वापस IA_CSS_FRAME_FORMAT_BINARY_8;
	हाल V4L2_PIX_FMT_SBGGR16:
	हाल V4L2_PIX_FMT_SBGGR10:
	हाल V4L2_PIX_FMT_SGBRG10:
	हाल V4L2_PIX_FMT_SGRBG10:
	हाल V4L2_PIX_FMT_SRGGB10:
	हाल V4L2_PIX_FMT_SBGGR12:
	हाल V4L2_PIX_FMT_SGBRG12:
	हाल V4L2_PIX_FMT_SGRBG12:
	हाल V4L2_PIX_FMT_SRGGB12:
	हाल V4L2_PIX_FMT_SBGGR8:
	हाल V4L2_PIX_FMT_SGBRG8:
	हाल V4L2_PIX_FMT_SGRBG8:
	हाल V4L2_PIX_FMT_SRGGB8:
		वापस IA_CSS_FRAME_FORMAT_RAW;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/*
 * raw क्रमmat match between SH क्रमmat and V4L2 क्रमmat
 */
अटल पूर्णांक raw_output_क्रमmat_match_input(u32 input, u32 output)
अणु
	अगर ((input == ATOMISP_INPUT_FORMAT_RAW_12) &&
	    ((output == V4L2_PIX_FMT_SRGGB12) ||
	     (output == V4L2_PIX_FMT_SGRBG12) ||
	     (output == V4L2_PIX_FMT_SBGGR12) ||
	     (output == V4L2_PIX_FMT_SGBRG12)))
		वापस 0;

	अगर ((input == ATOMISP_INPUT_FORMAT_RAW_10) &&
	    ((output == V4L2_PIX_FMT_SRGGB10) ||
	     (output == V4L2_PIX_FMT_SGRBG10) ||
	     (output == V4L2_PIX_FMT_SBGGR10) ||
	     (output == V4L2_PIX_FMT_SGBRG10)))
		वापस 0;

	अगर ((input == ATOMISP_INPUT_FORMAT_RAW_8) &&
	    ((output == V4L2_PIX_FMT_SRGGB8) ||
	     (output == V4L2_PIX_FMT_SGRBG8) ||
	     (output == V4L2_PIX_FMT_SBGGR8) ||
	     (output == V4L2_PIX_FMT_SGBRG8)))
		वापस 0;

	अगर ((input == ATOMISP_INPUT_FORMAT_RAW_16) && (output == V4L2_PIX_FMT_SBGGR16))
		वापस 0;

	वापस -EINVAL;
पूर्ण

अटल u32 get_pixel_depth(u32 pixelक्रमmat)
अणु
	चयन (pixelक्रमmat) अणु
	हाल V4L2_PIX_FMT_YUV420:
	हाल V4L2_PIX_FMT_NV12:
	हाल V4L2_PIX_FMT_NV21:
	हाल V4L2_PIX_FMT_YVU420:
		वापस 12;
	हाल V4L2_PIX_FMT_YUV422P:
	हाल V4L2_PIX_FMT_YUYV:
	हाल V4L2_PIX_FMT_UYVY:
	हाल V4L2_PIX_FMT_NV16:
	हाल V4L2_PIX_FMT_NV61:
	हाल V4L2_PIX_FMT_RGB565:
	हाल V4L2_PIX_FMT_SBGGR16:
	हाल V4L2_PIX_FMT_SBGGR12:
	हाल V4L2_PIX_FMT_SGBRG12:
	हाल V4L2_PIX_FMT_SGRBG12:
	हाल V4L2_PIX_FMT_SRGGB12:
	हाल V4L2_PIX_FMT_SBGGR10:
	हाल V4L2_PIX_FMT_SGBRG10:
	हाल V4L2_PIX_FMT_SGRBG10:
	हाल V4L2_PIX_FMT_SRGGB10:
		वापस 16;
	हाल V4L2_PIX_FMT_RGB24:
	हाल V4L2_PIX_FMT_YUV444:
		वापस 24;
	हाल V4L2_PIX_FMT_RGB32:
		वापस 32;
	हाल V4L2_PIX_FMT_JPEG:
	हाल V4L2_PIX_FMT_CUSTOM_M10MO_RAW:
	हाल V4L2_PIX_FMT_SBGGR8:
	हाल V4L2_PIX_FMT_SGBRG8:
	हाल V4L2_PIX_FMT_SGRBG8:
	हाल V4L2_PIX_FMT_SRGGB8:
		वापस 8;
	शेष:
		वापस 8 * 2;	/* raw type now */
	पूर्ण
पूर्ण

bool atomisp_is_mbuscode_raw(uपूर्णांक32_t code)
अणु
	वापस code >= 0x3000 && code < 0x4000;
पूर्ण

/*
 * ISP features control function
 */

/*
 * Set ISP capture mode based on current settings
 */
अटल व्योम atomisp_update_capture_mode(काष्ठा atomisp_sub_device *asd)
अणु
	अगर (asd->params.gdc_cac_en)
		atomisp_css_capture_set_mode(asd, IA_CSS_CAPTURE_MODE_ADVANCED);
	अन्यथा अगर (asd->params.low_light)
		atomisp_css_capture_set_mode(asd, IA_CSS_CAPTURE_MODE_LOW_LIGHT);
	अन्यथा अगर (asd->video_out_capture.sh_fmt == IA_CSS_FRAME_FORMAT_RAW)
		atomisp_css_capture_set_mode(asd, IA_CSS_CAPTURE_MODE_RAW);
	अन्यथा
		atomisp_css_capture_set_mode(asd, IA_CSS_CAPTURE_MODE_PRIMARY);
पूर्ण

/* ISP2401 */
पूर्णांक atomisp_set_sensor_runmode(काष्ठा atomisp_sub_device *asd,
			       काष्ठा atomisp_s_runmode *runmode)
अणु
	काष्ठा atomisp_device *isp = asd->isp;
	काष्ठा v4l2_ctrl *c;
	पूर्णांक ret = 0;

	अगर (!(runmode && (runmode->mode & RUNMODE_MASK)))
		वापस -EINVAL;

	mutex_lock(asd->ctrl_handler.lock);
	c = v4l2_ctrl_find(isp->inमाला_दो[asd->input_curr].camera->ctrl_handler,
			   V4L2_CID_RUN_MODE);

	अगर (c)
		ret = v4l2_ctrl_s_ctrl(c, runmode->mode);

	mutex_unlock(asd->ctrl_handler.lock);
	वापस ret;
पूर्ण

/*
 * Function to enable/disable lens geometry distortion correction (GDC) and
 * chromatic aberration correction (CAC)
 */
पूर्णांक atomisp_gdc_cac(काष्ठा atomisp_sub_device *asd, पूर्णांक flag,
		    __s32 *value)
अणु
	अगर (flag == 0) अणु
		*value = asd->params.gdc_cac_en;
		वापस 0;
	पूर्ण

	asd->params.gdc_cac_en = !!*value;
	अगर (asd->params.gdc_cac_en) अणु
		asd->params.config.morph_table = asd->params.css_param.morph_table;
	पूर्ण अन्यथा अणु
		asd->params.config.morph_table = शून्य;
	पूर्ण
	asd->params.css_update_params_needed = true;
	atomisp_update_capture_mode(asd);
	वापस 0;
पूर्ण

/*
 * Function to enable/disable low light mode including ANR
 */
पूर्णांक atomisp_low_light(काष्ठा atomisp_sub_device *asd, पूर्णांक flag,
		      __s32 *value)
अणु
	अगर (flag == 0) अणु
		*value = asd->params.low_light;
		वापस 0;
	पूर्ण

	asd->params.low_light = (*value != 0);
	atomisp_update_capture_mode(asd);
	वापस 0;
पूर्ण

/*
 * Function to enable/disable extra noise reduction (XNR) in low light
 * condition
 */
पूर्णांक atomisp_xnr(काष्ठा atomisp_sub_device *asd, पूर्णांक flag,
		पूर्णांक *xnr_enable)
अणु
	अगर (flag == 0) अणु
		*xnr_enable = asd->params.xnr_en;
		वापस 0;
	पूर्ण

	atomisp_css_capture_enable_xnr(asd, !!*xnr_enable);

	वापस 0;
पूर्ण

/*
 * Function to configure bayer noise reduction
 */
पूर्णांक atomisp_nr(काष्ठा atomisp_sub_device *asd, पूर्णांक flag,
	       काष्ठा atomisp_nr_config *arg)
अणु
	अगर (flag == 0) अणु
		/* Get nr config from current setup */
		अगर (atomisp_css_get_nr_config(asd, arg))
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		/* Set nr config to isp parameters */
		स_नकल(&asd->params.css_param.nr_config, arg,
		       माप(काष्ठा ia_css_nr_config));
		asd->params.config.nr_config = &asd->params.css_param.nr_config;
		asd->params.css_update_params_needed = true;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Function to configure temporal noise reduction (TNR)
 */
पूर्णांक atomisp_tnr(काष्ठा atomisp_sub_device *asd, पूर्णांक flag,
		काष्ठा atomisp_tnr_config *config)
अणु
	/* Get tnr config from current setup */
	अगर (flag == 0) अणु
		/* Get tnr config from current setup */
		अगर (atomisp_css_get_tnr_config(asd, config))
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		/* Set tnr config to isp parameters */
		स_नकल(&asd->params.css_param.tnr_config, config,
		       माप(काष्ठा ia_css_tnr_config));
		asd->params.config.tnr_config = &asd->params.css_param.tnr_config;
		asd->params.css_update_params_needed = true;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Function to configure black level compensation
 */
पूर्णांक atomisp_black_level(काष्ठा atomisp_sub_device *asd, पूर्णांक flag,
			काष्ठा atomisp_ob_config *config)
अणु
	अगर (flag == 0) अणु
		/* Get ob config from current setup */
		अगर (atomisp_css_get_ob_config(asd, config))
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		/* Set ob config to isp parameters */
		स_नकल(&asd->params.css_param.ob_config, config,
		       माप(काष्ठा ia_css_ob_config));
		asd->params.config.ob_config = &asd->params.css_param.ob_config;
		asd->params.css_update_params_needed = true;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Function to configure edge enhancement
 */
पूर्णांक atomisp_ee(काष्ठा atomisp_sub_device *asd, पूर्णांक flag,
	       काष्ठा atomisp_ee_config *config)
अणु
	अगर (flag == 0) अणु
		/* Get ee config from current setup */
		अगर (atomisp_css_get_ee_config(asd, config))
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		/* Set ee config to isp parameters */
		स_नकल(&asd->params.css_param.ee_config, config,
		       माप(asd->params.css_param.ee_config));
		asd->params.config.ee_config = &asd->params.css_param.ee_config;
		asd->params.css_update_params_needed = true;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Function to update Gamma table क्रम gamma, brightness and contrast config
 */
पूर्णांक atomisp_gamma(काष्ठा atomisp_sub_device *asd, पूर्णांक flag,
		  काष्ठा atomisp_gamma_table *config)
अणु
	अगर (flag == 0) अणु
		/* Get gamma table from current setup */
		अगर (atomisp_css_get_gamma_table(asd, config))
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		/* Set gamma table to isp parameters */
		स_नकल(&asd->params.css_param.gamma_table, config,
		       माप(asd->params.css_param.gamma_table));
		asd->params.config.gamma_table = &asd->params.css_param.gamma_table;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Function to update Ctc table क्रम Chroma Enhancement
 */
पूर्णांक atomisp_ctc(काष्ठा atomisp_sub_device *asd, पूर्णांक flag,
		काष्ठा atomisp_ctc_table *config)
अणु
	अगर (flag == 0) अणु
		/* Get ctc table from current setup */
		अगर (atomisp_css_get_ctc_table(asd, config))
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		/* Set ctc table to isp parameters */
		स_नकल(&asd->params.css_param.ctc_table, config,
		       माप(asd->params.css_param.ctc_table));
		atomisp_css_set_ctc_table(asd, &asd->params.css_param.ctc_table);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Function to update gamma correction parameters
 */
पूर्णांक atomisp_gamma_correction(काष्ठा atomisp_sub_device *asd, पूर्णांक flag,
			     काष्ठा atomisp_gc_config *config)
अणु
	अगर (flag == 0) अणु
		/* Get gamma correction params from current setup */
		अगर (atomisp_css_get_gc_config(asd, config))
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		/* Set gamma correction params to isp parameters */
		स_नकल(&asd->params.css_param.gc_config, config,
		       माप(asd->params.css_param.gc_config));
		asd->params.config.gc_config = &asd->params.css_param.gc_config;
		asd->params.css_update_params_needed = true;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Function to update narrow gamma flag
 */
पूर्णांक atomisp_क्रमmats(काष्ठा atomisp_sub_device *asd, पूर्णांक flag,
		    काष्ठा atomisp_क्रमmats_config *config)
अणु
	अगर (flag == 0) अणु
		/* Get narrow gamma flag from current setup */
		अगर (atomisp_css_get_क्रमmats_config(asd, config))
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		/* Set narrow gamma flag to isp parameters */
		स_नकल(&asd->params.css_param.क्रमmats_config, config,
		       माप(asd->params.css_param.क्रमmats_config));
		asd->params.config.क्रमmats_config = &asd->params.css_param.क्रमmats_config;
	पूर्ण

	वापस 0;
पूर्ण

व्योम atomisp_मुक्त_पूर्णांकernal_buffers(काष्ठा atomisp_sub_device *asd)
अणु
	atomisp_मुक्त_css_parameters(&asd->params.css_param);

	अगर (asd->raw_output_frame) अणु
		ia_css_frame_मुक्त(asd->raw_output_frame);
		asd->raw_output_frame = शून्य;
	पूर्ण
पूर्ण

अटल व्योम atomisp_update_grid_info(काष्ठा atomisp_sub_device *asd,
				     क्रमागत ia_css_pipe_id pipe_id,
				     पूर्णांक source_pad)
अणु
	काष्ठा atomisp_device *isp = asd->isp;
	पूर्णांक err;
	u16 stream_id = atomisp_source_pad_to_stream_id(asd, source_pad);

	अगर (atomisp_css_get_grid_info(asd, pipe_id, source_pad))
		वापस;

	/* We must मुक्त all buffers because they no दीर्घer match
	   the grid size. */
	atomisp_css_मुक्त_stat_buffers(asd);

	err = atomisp_alloc_css_stat_bufs(asd, stream_id);
	अगर (err) अणु
		dev_err(isp->dev, "stat_buf allocate error\n");
		जाओ err;
	पूर्ण

	अगर (atomisp_alloc_3a_output_buf(asd)) अणु
		/* Failure क्रम 3A buffers करोes not influence DIS buffers */
		अगर (asd->params.s3a_output_bytes != 0) अणु
			/* For SOC sensor happens s3a_output_bytes == 0,
			 * using अगर condition to exclude false error log */
			dev_err(isp->dev, "Failed to allocate memory for 3A statistics\n");
		पूर्ण
		जाओ err;
	पूर्ण

	अगर (atomisp_alloc_dis_coef_buf(asd)) अणु
		dev_err(isp->dev,
			"Failed to allocate memory for DIS statistics\n");
		जाओ err;
	पूर्ण

	अगर (atomisp_alloc_metadata_output_buf(asd)) अणु
		dev_err(isp->dev, "Failed to allocate memory for metadata\n");
		जाओ err;
	पूर्ण

	वापस;

err:
	atomisp_css_मुक्त_stat_buffers(asd);
	वापस;
पूर्ण

अटल व्योम atomisp_curr_user_grid_info(काष्ठा atomisp_sub_device *asd,
					काष्ठा atomisp_grid_info *info)
अणु
	स_नकल(info, &asd->params.curr_grid_info.s3a_grid,
	       माप(काष्ठा ia_css_3a_grid_info));
पूर्ण

पूर्णांक atomisp_compare_grid(काष्ठा atomisp_sub_device *asd,
			 काष्ठा atomisp_grid_info *atomgrid)
अणु
	काष्ठा atomisp_grid_info पंचांगp = अणु0पूर्ण;

	atomisp_curr_user_grid_info(asd, &पंचांगp);
	वापस स_भेद(atomgrid, &पंचांगp, माप(पंचांगp));
पूर्ण

/*
 * Function to update Gdc table क्रम gdc
 */
पूर्णांक atomisp_gdc_cac_table(काष्ठा atomisp_sub_device *asd, पूर्णांक flag,
			  काष्ठा atomisp_morph_table *config)
अणु
	पूर्णांक ret;
	पूर्णांक i;
	काष्ठा atomisp_device *isp = asd->isp;

	अगर (flag == 0) अणु
		/* Get gdc table from current setup */
		काष्ठा ia_css_morph_table tab = अणु0पूर्ण;

		atomisp_css_get_morph_table(asd, &tab);

		config->width = tab.width;
		config->height = tab.height;

		क्रम (i = 0; i < IA_CSS_MORPH_TABLE_NUM_PLANES; i++) अणु
			ret = copy_to_user(config->coordinates_x[i],
					   tab.coordinates_x[i], tab.height *
					   tab.width * माप(*tab.coordinates_x[i]));
			अगर (ret) अणु
				dev_err(isp->dev,
					"Failed to copy to User for x\n");
				वापस -EFAULT;
			पूर्ण
			ret = copy_to_user(config->coordinates_y[i],
					   tab.coordinates_y[i], tab.height *
					   tab.width * माप(*tab.coordinates_y[i]));
			अगर (ret) अणु
				dev_err(isp->dev,
					"Failed to copy to User for y\n");
				वापस -EFAULT;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा ia_css_morph_table *tab =
			    asd->params.css_param.morph_table;

		/* मुक्त first अगर we have one */
		अगर (tab) अणु
			atomisp_css_morph_table_मुक्त(tab);
			asd->params.css_param.morph_table = शून्य;
		पूर्ण

		/* allocate new one */
		tab = atomisp_css_morph_table_allocate(config->width,
						       config->height);

		अगर (!tab) अणु
			dev_err(isp->dev, "out of memory\n");
			वापस -EINVAL;
		पूर्ण

		क्रम (i = 0; i < IA_CSS_MORPH_TABLE_NUM_PLANES; i++) अणु
			ret = copy_from_user(tab->coordinates_x[i],
					     config->coordinates_x[i],
					     config->height * config->width *
					     माप(*config->coordinates_x[i]));
			अगर (ret) अणु
				dev_err(isp->dev,
					"Failed to copy from User for x, ret %d\n",
					ret);
				atomisp_css_morph_table_मुक्त(tab);
				वापस -EFAULT;
			पूर्ण
			ret = copy_from_user(tab->coordinates_y[i],
					     config->coordinates_y[i],
					     config->height * config->width *
					     माप(*config->coordinates_y[i]));
			अगर (ret) अणु
				dev_err(isp->dev,
					"Failed to copy from User for y, ret is %d\n",
					ret);
				atomisp_css_morph_table_मुक्त(tab);
				वापस -EFAULT;
			पूर्ण
		पूर्ण
		asd->params.css_param.morph_table = tab;
		अगर (asd->params.gdc_cac_en)
			asd->params.config.morph_table = tab;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक atomisp_macc_table(काष्ठा atomisp_sub_device *asd, पूर्णांक flag,
		       काष्ठा atomisp_macc_config *config)
अणु
	काष्ठा ia_css_macc_table *macc_table;

	चयन (config->color_effect) अणु
	हाल V4L2_COLORFX_NONE:
		macc_table = &asd->params.css_param.macc_table;
		अवरोध;
	हाल V4L2_COLORFX_SKY_BLUE:
		macc_table = &blue_macc_table;
		अवरोध;
	हाल V4L2_COLORFX_GRASS_GREEN:
		macc_table = &green_macc_table;
		अवरोध;
	हाल V4L2_COLORFX_SKIN_WHITEN_LOW:
		macc_table = &skin_low_macc_table;
		अवरोध;
	हाल V4L2_COLORFX_SKIN_WHITEN:
		macc_table = &skin_medium_macc_table;
		अवरोध;
	हाल V4L2_COLORFX_SKIN_WHITEN_HIGH:
		macc_table = &skin_high_macc_table;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (flag == 0) अणु
		/* Get macc table from current setup */
		स_नकल(&config->table, macc_table,
		       माप(काष्ठा ia_css_macc_table));
	पूर्ण अन्यथा अणु
		स_नकल(macc_table, &config->table,
		       माप(काष्ठा ia_css_macc_table));
		अगर (config->color_effect == asd->params.color_effect)
			asd->params.config.macc_table = macc_table;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक atomisp_set_dis_vector(काष्ठा atomisp_sub_device *asd,
			   काष्ठा atomisp_dis_vector *vector)
अणु
	atomisp_css_video_set_dis_vector(asd, vector);

	asd->params.dis_proj_data_valid = false;
	asd->params.css_update_params_needed = true;
	वापस 0;
पूर्ण

/*
 * Function to set/get image stablization statistics
 */
पूर्णांक atomisp_get_dis_stat(काष्ठा atomisp_sub_device *asd,
			 काष्ठा atomisp_dis_statistics *stats)
अणु
	वापस atomisp_css_get_dis_stat(asd, stats);
पूर्ण

/*
 * Function  set camrea_prefiles.xml current sensor pixel array size
 */
पूर्णांक atomisp_set_array_res(काष्ठा atomisp_sub_device *asd,
			  काष्ठा atomisp_resolution  *config)
अणु
	dev_dbg(asd->isp->dev, ">%s start\n", __func__);
	अगर (!config) अणु
		dev_err(asd->isp->dev, "Set sensor array size is not valid\n");
		वापस -EINVAL;
	पूर्ण

	asd->sensor_array_res.width = config->width;
	asd->sensor_array_res.height = config->height;
	वापस 0;
पूर्ण

/*
 * Function to get DVS2 BQ resolution settings
 */
पूर्णांक atomisp_get_dvs2_bq_resolutions(काष्ठा atomisp_sub_device *asd,
				    काष्ठा atomisp_dvs2_bq_resolutions *bq_res)
अणु
	काष्ठा ia_css_pipe_config *pipe_cfg = शून्य;
	काष्ठा ia_css_stream_config *stream_cfg = शून्य;
	काष्ठा ia_css_stream_input_config *input_config = शून्य;

	काष्ठा ia_css_stream *stream =
		    asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL].stream;
	अगर (!stream) अणु
		dev_warn(asd->isp->dev, "stream is not created");
		वापस -EAGAIN;
	पूर्ण

	pipe_cfg = &asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL]
		   .pipe_configs[IA_CSS_PIPE_ID_VIDEO];
	stream_cfg = &asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL]
		     .stream_config;
	input_config = &stream_cfg->input_config;

	अगर (!bq_res)
		वापस -EINVAL;

	/* the GDC output resolution */
	bq_res->output_bq.width_bq = pipe_cfg->output_info[0].res.width / 2;
	bq_res->output_bq.height_bq = pipe_cfg->output_info[0].res.height / 2;

	bq_res->envelope_bq.width_bq = 0;
	bq_res->envelope_bq.height_bq = 0;
	/* the GDC input resolution */
	अगर (!asd->continuous_mode->val) अणु
		bq_res->source_bq.width_bq = bq_res->output_bq.width_bq +
					     pipe_cfg->dvs_envelope.width / 2;
		bq_res->source_bq.height_bq = bq_res->output_bq.height_bq +
					      pipe_cfg->dvs_envelope.height / 2;
		/*
		 * Bad pixels caused by spatial filter processing
		 * ISP filter resolution should be given by CSS/FW, but क्रम now
		 * there is not such API to query, and it is fixed value, so
		 * hardcoded here.
		 */
		bq_res->ispfilter_bq.width_bq = 12 / 2;
		bq_res->ispfilter_bq.height_bq = 12 / 2;
		/* spatial filter shअगरt, always 4 pixels */
		bq_res->gdc_shअगरt_bq.width_bq = 4 / 2;
		bq_res->gdc_shअगरt_bq.height_bq = 4 / 2;

		अगर (asd->params.video_dis_en) अणु
			bq_res->envelope_bq.width_bq = pipe_cfg->dvs_envelope.width
						       / 2 - bq_res->ispfilter_bq.width_bq;
			bq_res->envelope_bq.height_bq = pipe_cfg->dvs_envelope.height
							/ 2 - bq_res->ispfilter_bq.height_bq;
		पूर्ण
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक w_padding;
		अचिन्हित पूर्णांक gdc_effective_input = 0;

		/* For GDC:
		 * gdc_effective_input = effective_input + envelope
		 *
		 * From the comment and क्रमmula in BZ1786,
		 * we see the source_bq should be:
		 * effective_input / bayer_ds_ratio
		 */
		bq_res->source_bq.width_bq =
		    (input_config->effective_res.width *
		     pipe_cfg->bayer_ds_out_res.width /
		     input_config->effective_res.width + 1) / 2;
		bq_res->source_bq.height_bq =
		    (input_config->effective_res.height *
		     pipe_cfg->bayer_ds_out_res.height /
		     input_config->effective_res.height + 1) / 2;

		अगर (!asd->params.video_dis_en) अणु
			/*
			 * We adjust the ispfilter_bq to:
			 * ispfilter_bq = 128/BDS
			 * we still need firmware team to provide an offical
			 * क्रमmula क्रम SDV.
			 */
			bq_res->ispfilter_bq.width_bq = 128 *
							pipe_cfg->bayer_ds_out_res.width /
							input_config->effective_res.width / 2;
			bq_res->ispfilter_bq.height_bq = 128 *
							 pipe_cfg->bayer_ds_out_res.width /
							 input_config->effective_res.width / 2;

			अगर (IS_HWREVISION(asd->isp, ATOMISP_HW_REVISION_ISP2401)) अणु
				/* No additional left padding क्रम ISYS2401 */
				bq_res->gdc_shअगरt_bq.width_bq = 4 / 2;
				bq_res->gdc_shअगरt_bq.height_bq = 4 / 2;
			पूर्ण अन्यथा अणु
				/*
				 * For the w_padding and gdc_shअगरt_bq cacluation
				 * Please see the BZ 1786 and 4358 क्रम more info.
				 * Just test that this क्रमmula can work now,
				 * but we still have no offical क्रमmula.
				 *
				 * w_padding = उच्चमानing(gdc_effective_input
				 *             /128, 1) * 128 - effective_width
				 * gdc_shअगरt_bq = w_padding/BDS/2 + ispfilter_bq/2
				 */
				gdc_effective_input =
				    input_config->effective_res.width +
				    pipe_cfg->dvs_envelope.width;
				w_padding = roundup(gdc_effective_input, 128) -
					    input_config->effective_res.width;
				w_padding = w_padding *
					    pipe_cfg->bayer_ds_out_res.width /
					    input_config->effective_res.width + 1;
				w_padding = roundup(w_padding / 2, 1);

				bq_res->gdc_shअगरt_bq.width_bq = bq_res->ispfilter_bq.width_bq / 2
								+ w_padding;
				bq_res->gdc_shअगरt_bq.height_bq = 4 / 2;
			पूर्ण
		पूर्ण अन्यथा अणु
			अचिन्हित पूर्णांक dvs_w, dvs_h, dvs_w_max, dvs_h_max;

			bq_res->ispfilter_bq.width_bq = 8 / 2;
			bq_res->ispfilter_bq.height_bq = 8 / 2;

			अगर (IS_HWREVISION(asd->isp, ATOMISP_HW_REVISION_ISP2401)) अणु
				/* No additional left padding क्रम ISYS2401 */
				bq_res->gdc_shअगरt_bq.width_bq = 4 / 2;
				bq_res->gdc_shअगरt_bq.height_bq = 4 / 2;
			पूर्ण अन्यथा अणु
				w_padding =
				    roundup(input_config->effective_res.width, 128) -
				    input_config->effective_res.width;
				अगर (w_padding < 12)
					w_padding = 12;
				bq_res->gdc_shअगरt_bq.width_bq = 4 / 2 +
								((w_padding - 12) *
								 pipe_cfg->bayer_ds_out_res.width /
								 input_config->effective_res.width + 1) / 2;
				bq_res->gdc_shअगरt_bq.height_bq = 4 / 2;
			पूर्ण

			dvs_w = pipe_cfg->bayer_ds_out_res.width -
				pipe_cfg->output_info[0].res.width;
			dvs_h = pipe_cfg->bayer_ds_out_res.height -
				pipe_cfg->output_info[0].res.height;
			dvs_w_max = roundकरोwn(
					pipe_cfg->output_info[0].res.width / 5,
					ATOM_ISP_STEP_WIDTH);
			dvs_h_max = roundकरोwn(
					pipe_cfg->output_info[0].res.height / 5,
					ATOM_ISP_STEP_HEIGHT);
			bq_res->envelope_bq.width_bq =
			    min((dvs_w / 2), (dvs_w_max / 2)) -
			    bq_res->ispfilter_bq.width_bq;
			bq_res->envelope_bq.height_bq =
			    min((dvs_h / 2), (dvs_h_max / 2)) -
			    bq_res->ispfilter_bq.height_bq;
		पूर्ण
	पूर्ण

	dev_dbg(asd->isp->dev,
		"source_bq.width_bq %d, source_bq.height_bq %d,\nispfilter_bq.width_bq %d, ispfilter_bq.height_bq %d,\ngdc_shift_bq.width_bq %d, gdc_shift_bq.height_bq %d,\nenvelope_bq.width_bq %d, envelope_bq.height_bq %d,\noutput_bq.width_bq %d, output_bq.height_bq %d\n",
		bq_res->source_bq.width_bq, bq_res->source_bq.height_bq,
		bq_res->ispfilter_bq.width_bq, bq_res->ispfilter_bq.height_bq,
		bq_res->gdc_shअगरt_bq.width_bq, bq_res->gdc_shअगरt_bq.height_bq,
		bq_res->envelope_bq.width_bq, bq_res->envelope_bq.height_bq,
		bq_res->output_bq.width_bq, bq_res->output_bq.height_bq);

	वापस 0;
पूर्ण

पूर्णांक atomisp_set_dis_coefs(काष्ठा atomisp_sub_device *asd,
			  काष्ठा atomisp_dis_coefficients *coefs)
अणु
	वापस atomisp_css_set_dis_coefs(asd, coefs);
पूर्ण

/*
 * Function to set/get 3A stat from isp
 */
पूर्णांक atomisp_3a_stat(काष्ठा atomisp_sub_device *asd, पूर्णांक flag,
		    काष्ठा atomisp_3a_statistics *config)
अणु
	काष्ठा atomisp_device *isp = asd->isp;
	काष्ठा atomisp_s3a_buf *s3a_buf;
	अचिन्हित दीर्घ ret;

	अगर (flag != 0)
		वापस -EINVAL;

	/* sanity check to aव्योम writing पूर्णांकo unallocated memory. */
	अगर (asd->params.s3a_output_bytes == 0)
		वापस -EINVAL;

	अगर (atomisp_compare_grid(asd, &config->grid_info) != 0) अणु
		/* If the grid info in the argument dअगरfers from the current
		   grid info, we tell the caller to reset the grid size and
		   try again. */
		वापस -EAGAIN;
	पूर्ण

	अगर (list_empty(&asd->s3a_stats_पढ़ोy)) अणु
		dev_err(isp->dev, "3a statistics is not valid.\n");
		वापस -EAGAIN;
	पूर्ण

	s3a_buf = list_entry(asd->s3a_stats_पढ़ोy.next,
			     काष्ठा atomisp_s3a_buf, list);
	अगर (s3a_buf->s3a_map)
		ia_css_translate_3a_statistics(
		    asd->params.s3a_user_stat, s3a_buf->s3a_map);
	अन्यथा
		ia_css_get_3a_statistics(asd->params.s3a_user_stat,
					 s3a_buf->s3a_data);

	config->exp_id = s3a_buf->s3a_data->exp_id;
	config->isp_config_id = s3a_buf->s3a_data->isp_config_id;

	ret = copy_to_user(config->data, asd->params.s3a_user_stat->data,
			   asd->params.s3a_output_bytes);
	अगर (ret) अणु
		dev_err(isp->dev, "copy to user failed: copied %lu bytes\n",
			ret);
		वापस -EFAULT;
	पूर्ण

	/* Move to मुक्त buffer list */
	list_del_init(&s3a_buf->list);
	list_add_tail(&s3a_buf->list, &asd->s3a_stats);
	dev_dbg(isp->dev, "%s: finish getting exp_id %d 3a stat, isp_config_id %d\n",
		__func__,
		config->exp_id, config->isp_config_id);
	वापस 0;
पूर्ण

पूर्णांक atomisp_get_metadata(काष्ठा atomisp_sub_device *asd, पूर्णांक flag,
			 काष्ठा atomisp_metadata *md)
अणु
	काष्ठा atomisp_device *isp = asd->isp;
	काष्ठा ia_css_stream_info *stream_info;
	काष्ठा camera_mipi_info *mipi_info;
	काष्ठा atomisp_metadata_buf *md_buf;
	क्रमागत atomisp_metadata_type md_type = ATOMISP_MAIN_METADATA;
	पूर्णांक ret, i;

	अगर (flag != 0)
		वापस -EINVAL;

	stream_info = &asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL].
		      stream_info;

	/* We always वापस the resolution and stride even अगर there is
	 * no valid metadata. This allows the caller to get the inक्रमmation
	 * needed to allocate user-space buffers. */
	md->width  = stream_info->metadata_info.resolution.width;
	md->height = stream_info->metadata_info.resolution.height;
	md->stride = stream_info->metadata_info.stride;

	/* sanity check to aव्योम writing पूर्णांकo unallocated memory.
	 * This करोes not वापस an error because it is a valid way
	 * क्रम applications to detect that metadata is not enabled. */
	अगर (md->width == 0 || md->height == 0 || !md->data)
		वापस 0;

	/* This is करोne in the atomisp_buf_करोne() */
	अगर (list_empty(&asd->metadata_पढ़ोy[md_type])) अणु
		dev_warn(isp->dev, "Metadata queue is empty now!\n");
		वापस -EAGAIN;
	पूर्ण

	mipi_info = atomisp_to_sensor_mipi_info(
			isp->inमाला_दो[asd->input_curr].camera);
	अगर (!mipi_info)
		वापस -EINVAL;

	अगर (mipi_info->metadata_effective_width) अणु
		क्रम (i = 0; i < md->height; i++)
			md->effective_width[i] =
			    mipi_info->metadata_effective_width[i];
	पूर्ण

	md_buf = list_entry(asd->metadata_पढ़ोy[md_type].next,
			    काष्ठा atomisp_metadata_buf, list);
	md->exp_id = md_buf->metadata->exp_id;
	अगर (md_buf->md_vptr) अणु
		ret = copy_to_user(md->data,
				   md_buf->md_vptr,
				   stream_info->metadata_info.size);
	पूर्ण अन्यथा अणु
		hmm_load(md_buf->metadata->address,
			 asd->params.metadata_user[md_type],
			 stream_info->metadata_info.size);

		ret = copy_to_user(md->data,
				   asd->params.metadata_user[md_type],
				   stream_info->metadata_info.size);
	पूर्ण
	अगर (ret) अणु
		dev_err(isp->dev, "copy to user failed: copied %d bytes\n",
			ret);
		वापस -EFAULT;
	पूर्ण

	list_del_init(&md_buf->list);
	list_add_tail(&md_buf->list, &asd->metadata[md_type]);

	dev_dbg(isp->dev, "%s: HAL de-queued metadata type %d with exp_id %d\n",
		__func__, md_type, md->exp_id);
	वापस 0;
पूर्ण

पूर्णांक atomisp_get_metadata_by_type(काष्ठा atomisp_sub_device *asd, पूर्णांक flag,
				 काष्ठा atomisp_metadata_with_type *md)
अणु
	काष्ठा atomisp_device *isp = asd->isp;
	काष्ठा ia_css_stream_info *stream_info;
	काष्ठा camera_mipi_info *mipi_info;
	काष्ठा atomisp_metadata_buf *md_buf;
	क्रमागत atomisp_metadata_type md_type;
	पूर्णांक ret, i;

	अगर (flag != 0)
		वापस -EINVAL;

	stream_info = &asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL].
		      stream_info;

	/* We always वापस the resolution and stride even अगर there is
	 * no valid metadata. This allows the caller to get the inक्रमmation
	 * needed to allocate user-space buffers. */
	md->width  = stream_info->metadata_info.resolution.width;
	md->height = stream_info->metadata_info.resolution.height;
	md->stride = stream_info->metadata_info.stride;

	/* sanity check to aव्योम writing पूर्णांकo unallocated memory.
	 * This करोes not वापस an error because it is a valid way
	 * क्रम applications to detect that metadata is not enabled. */
	अगर (md->width == 0 || md->height == 0 || !md->data)
		वापस 0;

	md_type = md->type;
	अगर (md_type < 0 || md_type >= ATOMISP_METADATA_TYPE_NUM)
		वापस -EINVAL;

	/* This is करोne in the atomisp_buf_करोne() */
	अगर (list_empty(&asd->metadata_पढ़ोy[md_type])) अणु
		dev_warn(isp->dev, "Metadata queue is empty now!\n");
		वापस -EAGAIN;
	पूर्ण

	mipi_info = atomisp_to_sensor_mipi_info(
			isp->inमाला_दो[asd->input_curr].camera);
	अगर (!mipi_info)
		वापस -EINVAL;

	अगर (mipi_info->metadata_effective_width) अणु
		क्रम (i = 0; i < md->height; i++)
			md->effective_width[i] =
			    mipi_info->metadata_effective_width[i];
	पूर्ण

	md_buf = list_entry(asd->metadata_पढ़ोy[md_type].next,
			    काष्ठा atomisp_metadata_buf, list);
	md->exp_id = md_buf->metadata->exp_id;
	अगर (md_buf->md_vptr) अणु
		ret = copy_to_user(md->data,
				   md_buf->md_vptr,
				   stream_info->metadata_info.size);
	पूर्ण अन्यथा अणु
		hmm_load(md_buf->metadata->address,
			 asd->params.metadata_user[md_type],
			 stream_info->metadata_info.size);

		ret = copy_to_user(md->data,
				   asd->params.metadata_user[md_type],
				   stream_info->metadata_info.size);
	पूर्ण
	अगर (ret) अणु
		dev_err(isp->dev, "copy to user failed: copied %d bytes\n",
			ret);
		वापस -EFAULT;
	पूर्ण अन्यथा अणु
		list_del_init(&md_buf->list);
		list_add_tail(&md_buf->list, &asd->metadata[md_type]);
	पूर्ण
	dev_dbg(isp->dev, "%s: HAL de-queued metadata type %d with exp_id %d\n",
		__func__, md_type, md->exp_id);
	वापस 0;
पूर्ण

/*
 * Function to calculate real zoom region क्रम every pipe
 */
पूर्णांक atomisp_calculate_real_zoom_region(काष्ठा atomisp_sub_device *asd,
				       काष्ठा ia_css_dz_config   *dz_config,
				       क्रमागत ia_css_pipe_id css_pipe_id)

अणु
	काष्ठा atomisp_stream_env *stream_env =
		    &asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL];
	काष्ठा atomisp_resolution  eff_res, out_res;
	पूर्णांक w_offset, h_offset;

	स_रखो(&eff_res, 0, माप(eff_res));
	स_रखो(&out_res, 0, माप(out_res));

	अगर (dz_config->dx || dz_config->dy)
		वापस 0;

	अगर (css_pipe_id != IA_CSS_PIPE_ID_PREVIEW
	    && css_pipe_id != IA_CSS_PIPE_ID_CAPTURE) अणु
		dev_err(asd->isp->dev, "%s the set pipe no support crop region"
			, __func__);
		वापस -EINVAL;
	पूर्ण

	eff_res.width =
	    stream_env->stream_config.input_config.effective_res.width;
	eff_res.height =
	    stream_env->stream_config.input_config.effective_res.height;
	अगर (eff_res.width == 0 || eff_res.height == 0) अणु
		dev_err(asd->isp->dev, "%s err effective resolution"
			, __func__);
		वापस -EINVAL;
	पूर्ण

	अगर (dz_config->zoom_region.resolution.width
	    == asd->sensor_array_res.width
	    || dz_config->zoom_region.resolution.height
	    == asd->sensor_array_res.height) अणु
		/*no need crop region*/
		dz_config->zoom_region.origin.x = 0;
		dz_config->zoom_region.origin.y = 0;
		dz_config->zoom_region.resolution.width = eff_res.width;
		dz_config->zoom_region.resolution.height = eff_res.height;
		वापस 0;
	पूर्ण

	/* FIXME:
	 * This is not the correct implementation with Google's definition, due
	 * to firmware limitation.
	 * map real crop region base on above calculating base max crop region.
	 */

	अगर (!IS_ISP2401) अणु
		dz_config->zoom_region.origin.x = dz_config->zoom_region.origin.x
						  * eff_res.width
						  / asd->sensor_array_res.width;
		dz_config->zoom_region.origin.y = dz_config->zoom_region.origin.y
						  * eff_res.height
						  / asd->sensor_array_res.height;
		dz_config->zoom_region.resolution.width = dz_config->zoom_region.resolution.width
							  * eff_res.width
							  / asd->sensor_array_res.width;
		dz_config->zoom_region.resolution.height = dz_config->zoom_region.resolution.height
							  * eff_res.height
							  / asd->sensor_array_res.height;
		/*
		 * Set same ratio of crop region resolution and current pipe output
		 * resolution
		 */
		out_res.width = stream_env->pipe_configs[css_pipe_id].output_info[0].res.width;
		out_res.height = stream_env->pipe_configs[css_pipe_id].output_info[0].res.height;
		अगर (out_res.width == 0 || out_res.height == 0) अणु
			dev_err(asd->isp->dev, "%s err current pipe output resolution"
				, __func__);
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		out_res.width = stream_env->pipe_configs[css_pipe_id].output_info[0].res.width;
		out_res.height = stream_env->pipe_configs[css_pipe_id].output_info[0].res.height;
		अगर (out_res.width == 0 || out_res.height == 0) अणु
			dev_err(asd->isp->dev, "%s err current pipe output resolution"
				, __func__);
			वापस -EINVAL;
		पूर्ण

		अगर (asd->sensor_array_res.width * out_res.height
		    < out_res.width * asd->sensor_array_res.height) अणु
			h_offset = asd->sensor_array_res.height
				   - asd->sensor_array_res.width
				   * out_res.height / out_res.width;
			h_offset = h_offset / 2;
			अगर (dz_config->zoom_region.origin.y < h_offset)
				dz_config->zoom_region.origin.y = 0;
			अन्यथा
				dz_config->zoom_region.origin.y = dz_config->zoom_region.origin.y - h_offset;
			w_offset = 0;
		पूर्ण अन्यथा अणु
			w_offset = asd->sensor_array_res.width
				   - asd->sensor_array_res.height
				   * out_res.width / out_res.height;
			w_offset = w_offset / 2;
			अगर (dz_config->zoom_region.origin.x < w_offset)
				dz_config->zoom_region.origin.x = 0;
			अन्यथा
				dz_config->zoom_region.origin.x = dz_config->zoom_region.origin.x - w_offset;
			h_offset = 0;
		पूर्ण
		dz_config->zoom_region.origin.x = dz_config->zoom_region.origin.x
						  * eff_res.width
						  / (asd->sensor_array_res.width - 2 * w_offset);
		dz_config->zoom_region.origin.y = dz_config->zoom_region.origin.y
						  * eff_res.height
						  / (asd->sensor_array_res.height - 2 * h_offset);
		dz_config->zoom_region.resolution.width = dz_config->zoom_region.resolution.width
						  * eff_res.width
						  / (asd->sensor_array_res.width - 2 * w_offset);
		dz_config->zoom_region.resolution.height = dz_config->zoom_region.resolution.height
						  * eff_res.height
						  / (asd->sensor_array_res.height - 2 * h_offset);
	पूर्ण

	अगर (out_res.width * dz_config->zoom_region.resolution.height
	    > dz_config->zoom_region.resolution.width * out_res.height) अणु
		dz_config->zoom_region.resolution.height =
		    dz_config->zoom_region.resolution.width
		    * out_res.height / out_res.width;
	पूर्ण अन्यथा अणु
		dz_config->zoom_region.resolution.width =
		    dz_config->zoom_region.resolution.height
		    * out_res.width / out_res.height;
	पूर्ण
	dev_dbg(asd->isp->dev,
		"%s crop region:(%d,%d),(%d,%d) eff_res(%d, %d) array_size(%d,%d) out_res(%d, %d)\n",
		__func__, dz_config->zoom_region.origin.x,
		dz_config->zoom_region.origin.y,
		dz_config->zoom_region.resolution.width,
		dz_config->zoom_region.resolution.height,
		eff_res.width, eff_res.height,
		asd->sensor_array_res.width,
		asd->sensor_array_res.height,
		out_res.width, out_res.height);

	अगर ((dz_config->zoom_region.origin.x +
	     dz_config->zoom_region.resolution.width
	     > eff_res.width) ||
	    (dz_config->zoom_region.origin.y +
	     dz_config->zoom_region.resolution.height
	     > eff_res.height))
		वापस -EINVAL;

	वापस 0;
पूर्ण

/*
 * Function to check the zoom region whether is effective
 */
अटल bool atomisp_check_zoom_region(
    काष्ठा atomisp_sub_device *asd,
    काष्ठा ia_css_dz_config *dz_config)
अणु
	काष्ठा atomisp_resolution  config;
	bool flag = false;
	अचिन्हित पूर्णांक w, h;

	स_रखो(&config, 0, माप(काष्ठा atomisp_resolution));

	अगर (dz_config->dx && dz_config->dy)
		वापस true;

	config.width = asd->sensor_array_res.width;
	config.height = asd->sensor_array_res.height;
	w = dz_config->zoom_region.origin.x +
	    dz_config->zoom_region.resolution.width;
	h = dz_config->zoom_region.origin.y +
	    dz_config->zoom_region.resolution.height;

	अगर ((w <= config.width) && (h <= config.height) && w > 0 && h > 0)
		flag = true;
	अन्यथा
		/* setting error zoom region */
		dev_err(asd->isp->dev,
			"%s zoom region ERROR:dz_config:(%d,%d),(%d,%d)array_res(%d, %d)\n",
			__func__, dz_config->zoom_region.origin.x,
			dz_config->zoom_region.origin.y,
			dz_config->zoom_region.resolution.width,
			dz_config->zoom_region.resolution.height,
			config.width, config.height);

	वापस flag;
पूर्ण

व्योम atomisp_apply_css_parameters(
    काष्ठा atomisp_sub_device *asd,
    काष्ठा atomisp_css_params *css_param)
अणु
	अगर (css_param->update_flag.wb_config)
		asd->params.config.wb_config = &css_param->wb_config;

	अगर (css_param->update_flag.ob_config)
		asd->params.config.ob_config = &css_param->ob_config;

	अगर (css_param->update_flag.dp_config)
		asd->params.config.dp_config = &css_param->dp_config;

	अगर (css_param->update_flag.nr_config)
		asd->params.config.nr_config = &css_param->nr_config;

	अगर (css_param->update_flag.ee_config)
		asd->params.config.ee_config = &css_param->ee_config;

	अगर (css_param->update_flag.tnr_config)
		asd->params.config.tnr_config = &css_param->tnr_config;

	अगर (css_param->update_flag.a3a_config)
		asd->params.config.s3a_config = &css_param->s3a_config;

	अगर (css_param->update_flag.ctc_config)
		asd->params.config.ctc_config = &css_param->ctc_config;

	अगर (css_param->update_flag.cnr_config)
		asd->params.config.cnr_config = &css_param->cnr_config;

	अगर (css_param->update_flag.ecd_config)
		asd->params.config.ecd_config = &css_param->ecd_config;

	अगर (css_param->update_flag.ynr_config)
		asd->params.config.ynr_config = &css_param->ynr_config;

	अगर (css_param->update_flag.fc_config)
		asd->params.config.fc_config = &css_param->fc_config;

	अगर (css_param->update_flag.macc_config)
		asd->params.config.macc_config = &css_param->macc_config;

	अगर (css_param->update_flag.aa_config)
		asd->params.config.aa_config = &css_param->aa_config;

	अगर (css_param->update_flag.anr_config)
		asd->params.config.anr_config = &css_param->anr_config;

	अगर (css_param->update_flag.xnr_config)
		asd->params.config.xnr_config = &css_param->xnr_config;

	अगर (css_param->update_flag.yuv2rgb_cc_config)
		asd->params.config.yuv2rgb_cc_config = &css_param->yuv2rgb_cc_config;

	अगर (css_param->update_flag.rgb2yuv_cc_config)
		asd->params.config.rgb2yuv_cc_config = &css_param->rgb2yuv_cc_config;

	अगर (css_param->update_flag.macc_table)
		asd->params.config.macc_table = &css_param->macc_table;

	अगर (css_param->update_flag.xnr_table)
		asd->params.config.xnr_table = &css_param->xnr_table;

	अगर (css_param->update_flag.r_gamma_table)
		asd->params.config.r_gamma_table = &css_param->r_gamma_table;

	अगर (css_param->update_flag.g_gamma_table)
		asd->params.config.g_gamma_table = &css_param->g_gamma_table;

	अगर (css_param->update_flag.b_gamma_table)
		asd->params.config.b_gamma_table = &css_param->b_gamma_table;

	अगर (css_param->update_flag.anr_thres)
		atomisp_css_set_anr_thres(asd, &css_param->anr_thres);

	अगर (css_param->update_flag.shading_table)
		asd->params.config.shading_table = css_param->shading_table;

	अगर (css_param->update_flag.morph_table && asd->params.gdc_cac_en)
		asd->params.config.morph_table = css_param->morph_table;

	अगर (css_param->update_flag.dvs2_coefs) अणु
		काष्ठा ia_css_dvs_grid_info *dvs_grid_info =
		    atomisp_css_get_dvs_grid_info(
			&asd->params.curr_grid_info);

		अगर (dvs_grid_info && dvs_grid_info->enable)
			atomisp_css_set_dvs2_coefs(asd, css_param->dvs2_coeff);
	पूर्ण

	अगर (css_param->update_flag.dvs_6axis_config)
		atomisp_css_set_dvs_6axis(asd, css_param->dvs_6axis);

	atomisp_css_set_isp_config_id(asd, css_param->isp_config_id);
	/*
	 * These configurations are on used by ISP1.x, not क्रम ISP2.x,
	 * so करो not handle them. see comments of ia_css_isp_config.
	 * 1 cc_config
	 * 2 ce_config
	 * 3 de_config
	 * 4 gc_config
	 * 5 gamma_table
	 * 6 ctc_table
	 * 7 dvs_coefs
	 */
पूर्ण

अटल अचिन्हित पूर्णांक दीर्घ copy_from_compatible(व्योम *to, स्थिर व्योम *from,
	अचिन्हित दीर्घ n, bool from_user)
अणु
	अगर (from_user)
		वापस copy_from_user(to, (व्योम __user *)from, n);
	अन्यथा
		स_नकल(to, from, n);
	वापस 0;
पूर्ण

पूर्णांक atomisp_cp_general_isp_parameters(काष्ठा atomisp_sub_device *asd,
				      काष्ठा atomisp_parameters *arg,
				      काष्ठा atomisp_css_params *css_param,
				      bool from_user)
अणु
	काष्ठा atomisp_parameters *cur_config = &css_param->update_flag;

	अगर (!arg || !asd || !css_param)
		वापस -EINVAL;

	अगर (arg->wb_config && (from_user || !cur_config->wb_config)) अणु
		अगर (copy_from_compatible(&css_param->wb_config, arg->wb_config,
					 माप(काष्ठा ia_css_wb_config),
					 from_user))
			वापस -EFAULT;
		css_param->update_flag.wb_config =
		    (काष्ठा atomisp_wb_config *)&css_param->wb_config;
	पूर्ण

	अगर (arg->ob_config && (from_user || !cur_config->ob_config)) अणु
		अगर (copy_from_compatible(&css_param->ob_config, arg->ob_config,
					 माप(काष्ठा ia_css_ob_config),
					 from_user))
			वापस -EFAULT;
		css_param->update_flag.ob_config =
		    (काष्ठा atomisp_ob_config *)&css_param->ob_config;
	पूर्ण

	अगर (arg->dp_config && (from_user || !cur_config->dp_config)) अणु
		अगर (copy_from_compatible(&css_param->dp_config, arg->dp_config,
					 माप(काष्ठा ia_css_dp_config),
					 from_user))
			वापस -EFAULT;
		css_param->update_flag.dp_config =
		    (काष्ठा atomisp_dp_config *)&css_param->dp_config;
	पूर्ण

	अगर (asd->run_mode->val != ATOMISP_RUN_MODE_VIDEO) अणु
		अगर (arg->dz_config && (from_user || !cur_config->dz_config)) अणु
			अगर (copy_from_compatible(&css_param->dz_config,
						 arg->dz_config,
						 माप(काष्ठा ia_css_dz_config),
						 from_user))
				वापस -EFAULT;
			अगर (!atomisp_check_zoom_region(asd,
						       &css_param->dz_config)) अणु
				dev_err(asd->isp->dev, "crop region error!");
				वापस -EINVAL;
			पूर्ण
			css_param->update_flag.dz_config =
			    (काष्ठा atomisp_dz_config *)
			    &css_param->dz_config;
		पूर्ण
	पूर्ण

	अगर (arg->nr_config && (from_user || !cur_config->nr_config)) अणु
		अगर (copy_from_compatible(&css_param->nr_config, arg->nr_config,
					 माप(काष्ठा ia_css_nr_config),
					 from_user))
			वापस -EFAULT;
		css_param->update_flag.nr_config =
		    (काष्ठा atomisp_nr_config *)&css_param->nr_config;
	पूर्ण

	अगर (arg->ee_config && (from_user || !cur_config->ee_config)) अणु
		अगर (copy_from_compatible(&css_param->ee_config, arg->ee_config,
					 माप(काष्ठा ia_css_ee_config),
					 from_user))
			वापस -EFAULT;
		css_param->update_flag.ee_config =
		    (काष्ठा atomisp_ee_config *)&css_param->ee_config;
	पूर्ण

	अगर (arg->tnr_config && (from_user || !cur_config->tnr_config)) अणु
		अगर (copy_from_compatible(&css_param->tnr_config,
					 arg->tnr_config,
					 माप(काष्ठा ia_css_tnr_config),
					 from_user))
			वापस -EFAULT;
		css_param->update_flag.tnr_config =
		    (काष्ठा atomisp_tnr_config *)
		    &css_param->tnr_config;
	पूर्ण

	अगर (arg->a3a_config && (from_user || !cur_config->a3a_config)) अणु
		अगर (copy_from_compatible(&css_param->s3a_config,
					 arg->a3a_config,
					 माप(काष्ठा ia_css_3a_config),
					 from_user))
			वापस -EFAULT;
		css_param->update_flag.a3a_config =
		    (काष्ठा atomisp_3a_config *)&css_param->s3a_config;
	पूर्ण

	अगर (arg->ctc_config && (from_user || !cur_config->ctc_config)) अणु
		अगर (copy_from_compatible(&css_param->ctc_config,
					 arg->ctc_config,
					 माप(काष्ठा ia_css_ctc_config),
					 from_user))
			वापस -EFAULT;
		css_param->update_flag.ctc_config =
		    (काष्ठा atomisp_ctc_config *)
		    &css_param->ctc_config;
	पूर्ण

	अगर (arg->cnr_config && (from_user || !cur_config->cnr_config)) अणु
		अगर (copy_from_compatible(&css_param->cnr_config,
					 arg->cnr_config,
					 माप(काष्ठा ia_css_cnr_config),
					 from_user))
			वापस -EFAULT;
		css_param->update_flag.cnr_config =
		    (काष्ठा atomisp_cnr_config *)
		    &css_param->cnr_config;
	पूर्ण

	अगर (arg->ecd_config && (from_user || !cur_config->ecd_config)) अणु
		अगर (copy_from_compatible(&css_param->ecd_config,
					 arg->ecd_config,
					 माप(काष्ठा ia_css_ecd_config),
					 from_user))
			वापस -EFAULT;
		css_param->update_flag.ecd_config =
		    (काष्ठा atomisp_ecd_config *)
		    &css_param->ecd_config;
	पूर्ण

	अगर (arg->ynr_config && (from_user || !cur_config->ynr_config)) अणु
		अगर (copy_from_compatible(&css_param->ynr_config,
					 arg->ynr_config,
					 माप(काष्ठा ia_css_ynr_config),
					 from_user))
			वापस -EFAULT;
		css_param->update_flag.ynr_config =
		    (काष्ठा atomisp_ynr_config *)
		    &css_param->ynr_config;
	पूर्ण

	अगर (arg->fc_config && (from_user || !cur_config->fc_config)) अणु
		अगर (copy_from_compatible(&css_param->fc_config,
					 arg->fc_config,
					 माप(काष्ठा ia_css_fc_config),
					 from_user))
			वापस -EFAULT;
		css_param->update_flag.fc_config =
		    (काष्ठा atomisp_fc_config *)&css_param->fc_config;
	पूर्ण

	अगर (arg->macc_config && (from_user || !cur_config->macc_config)) अणु
		अगर (copy_from_compatible(&css_param->macc_config,
					 arg->macc_config,
					 माप(काष्ठा ia_css_macc_config),
					 from_user))
			वापस -EFAULT;
		css_param->update_flag.macc_config =
		    (काष्ठा atomisp_macc_config *)
		    &css_param->macc_config;
	पूर्ण

	अगर (arg->aa_config && (from_user || !cur_config->aa_config)) अणु
		अगर (copy_from_compatible(&css_param->aa_config, arg->aa_config,
					 माप(काष्ठा ia_css_aa_config),
					 from_user))
			वापस -EFAULT;
		css_param->update_flag.aa_config =
		    (काष्ठा atomisp_aa_config *)&css_param->aa_config;
	पूर्ण

	अगर (arg->anr_config && (from_user || !cur_config->anr_config)) अणु
		अगर (copy_from_compatible(&css_param->anr_config,
					 arg->anr_config,
					 माप(काष्ठा ia_css_anr_config),
					 from_user))
			वापस -EFAULT;
		css_param->update_flag.anr_config =
		    (काष्ठा atomisp_anr_config *)
		    &css_param->anr_config;
	पूर्ण

	अगर (arg->xnr_config && (from_user || !cur_config->xnr_config)) अणु
		अगर (copy_from_compatible(&css_param->xnr_config,
					 arg->xnr_config,
					 माप(काष्ठा ia_css_xnr_config),
					 from_user))
			वापस -EFAULT;
		css_param->update_flag.xnr_config =
		    (काष्ठा atomisp_xnr_config *)
		    &css_param->xnr_config;
	पूर्ण

	अगर (arg->yuv2rgb_cc_config &&
	    (from_user || !cur_config->yuv2rgb_cc_config)) अणु
		अगर (copy_from_compatible(&css_param->yuv2rgb_cc_config,
					 arg->yuv2rgb_cc_config,
					 माप(काष्ठा ia_css_cc_config),
					 from_user))
			वापस -EFAULT;
		css_param->update_flag.yuv2rgb_cc_config =
		    (काष्ठा atomisp_cc_config *)
		    &css_param->yuv2rgb_cc_config;
	पूर्ण

	अगर (arg->rgb2yuv_cc_config &&
	    (from_user || !cur_config->rgb2yuv_cc_config)) अणु
		अगर (copy_from_compatible(&css_param->rgb2yuv_cc_config,
					 arg->rgb2yuv_cc_config,
					 माप(काष्ठा ia_css_cc_config),
					 from_user))
			वापस -EFAULT;
		css_param->update_flag.rgb2yuv_cc_config =
		    (काष्ठा atomisp_cc_config *)
		    &css_param->rgb2yuv_cc_config;
	पूर्ण

	अगर (arg->macc_table && (from_user || !cur_config->macc_table)) अणु
		अगर (copy_from_compatible(&css_param->macc_table,
					 arg->macc_table,
					 माप(काष्ठा ia_css_macc_table),
					 from_user))
			वापस -EFAULT;
		css_param->update_flag.macc_table =
		    (काष्ठा atomisp_macc_table *)
		    &css_param->macc_table;
	पूर्ण

	अगर (arg->xnr_table && (from_user || !cur_config->xnr_table)) अणु
		अगर (copy_from_compatible(&css_param->xnr_table,
					 arg->xnr_table,
					 माप(काष्ठा ia_css_xnr_table),
					 from_user))
			वापस -EFAULT;
		css_param->update_flag.xnr_table =
		    (काष्ठा atomisp_xnr_table *)&css_param->xnr_table;
	पूर्ण

	अगर (arg->r_gamma_table && (from_user || !cur_config->r_gamma_table)) अणु
		अगर (copy_from_compatible(&css_param->r_gamma_table,
					 arg->r_gamma_table,
					 माप(काष्ठा ia_css_rgb_gamma_table),
					 from_user))
			वापस -EFAULT;
		css_param->update_flag.r_gamma_table =
		    (काष्ठा atomisp_rgb_gamma_table *)
		    &css_param->r_gamma_table;
	पूर्ण

	अगर (arg->g_gamma_table && (from_user || !cur_config->g_gamma_table)) अणु
		अगर (copy_from_compatible(&css_param->g_gamma_table,
					 arg->g_gamma_table,
					 माप(काष्ठा ia_css_rgb_gamma_table),
					 from_user))
			वापस -EFAULT;
		css_param->update_flag.g_gamma_table =
		    (काष्ठा atomisp_rgb_gamma_table *)
		    &css_param->g_gamma_table;
	पूर्ण

	अगर (arg->b_gamma_table && (from_user || !cur_config->b_gamma_table)) अणु
		अगर (copy_from_compatible(&css_param->b_gamma_table,
					 arg->b_gamma_table,
					 माप(काष्ठा ia_css_rgb_gamma_table),
					 from_user))
			वापस -EFAULT;
		css_param->update_flag.b_gamma_table =
		    (काष्ठा atomisp_rgb_gamma_table *)
		    &css_param->b_gamma_table;
	पूर्ण

	अगर (arg->anr_thres && (from_user || !cur_config->anr_thres)) अणु
		अगर (copy_from_compatible(&css_param->anr_thres, arg->anr_thres,
					 माप(काष्ठा ia_css_anr_thres),
					 from_user))
			वापस -EFAULT;
		css_param->update_flag.anr_thres =
		    (काष्ठा atomisp_anr_thres *)&css_param->anr_thres;
	पूर्ण

	अगर (from_user)
		css_param->isp_config_id = arg->isp_config_id;
	/*
	 * These configurations are on used by ISP1.x, not क्रम ISP2.x,
	 * so करो not handle them. see comments of ia_css_isp_config.
	 * 1 cc_config
	 * 2 ce_config
	 * 3 de_config
	 * 4 gc_config
	 * 5 gamma_table
	 * 6 ctc_table
	 * 7 dvs_coefs
	 */
	वापस 0;
पूर्ण

पूर्णांक atomisp_cp_lsc_table(काष्ठा atomisp_sub_device *asd,
			 काष्ठा atomisp_shading_table *source_st,
			 काष्ठा atomisp_css_params *css_param,
			 bool from_user)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक len_table;
	काष्ठा ia_css_shading_table *shading_table;
	काष्ठा ia_css_shading_table *old_table;
	काष्ठा atomisp_shading_table *st, dest_st;

	अगर (!source_st)
		वापस 0;

	अगर (!css_param)
		वापस -EINVAL;

	अगर (!from_user && css_param->update_flag.shading_table)
		वापस 0;

	अगर (IS_ISP2401) अणु
		अगर (copy_from_compatible(&dest_st, source_st,
					माप(काष्ठा atomisp_shading_table),
					from_user)) अणु
			dev_err(asd->isp->dev, "copy shading table failed!");
			वापस -EFAULT;
		पूर्ण
		st = &dest_st;
	पूर्ण अन्यथा अणु
		st = source_st;
	पूर्ण

	old_table = css_param->shading_table;

	/* user config is to disable the shading table. */
	अगर (!st->enable) अणु
		/* Generate a minimum table with enable = 0. */
		shading_table = atomisp_css_shading_table_alloc(1, 1);
		अगर (!shading_table)
			वापस -ENOMEM;
		shading_table->enable = 0;
		जाओ set_lsc;
	पूर्ण

	/* Setting a new table. Validate first - all tables must be set */
	क्रम (i = 0; i < ATOMISP_NUM_SC_COLORS; i++) अणु
		अगर (!st->data[i]) अणु
			dev_err(asd->isp->dev, "shading table validate failed");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* Shading table size per color */
	अगर (!IS_ISP2401) अणु
		अगर (st->width > ISP2400_SH_CSS_MAX_SCTBL_WIDTH_PER_COLOR ||
		    st->height > ISP2400_SH_CSS_MAX_SCTBL_HEIGHT_PER_COLOR) अणु
			dev_err(asd->isp->dev, "shading table w/h validate failed!");
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (st->width > ISP2401_SH_CSS_MAX_SCTBL_WIDTH_PER_COLOR ||
		    st->height > ISP2401_SH_CSS_MAX_SCTBL_HEIGHT_PER_COLOR) अणु
			dev_err(asd->isp->dev, "shading table w/h validate failed!");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	shading_table = atomisp_css_shading_table_alloc(st->width, st->height);
	अगर (!shading_table)
		वापस -ENOMEM;

	len_table = st->width * st->height * ATOMISP_SC_TYPE_SIZE;
	क्रम (i = 0; i < ATOMISP_NUM_SC_COLORS; i++) अणु
		अगर (copy_from_compatible(shading_table->data[i],
					 st->data[i], len_table, from_user)) अणु
			atomisp_css_shading_table_मुक्त(shading_table);
			वापस -EFAULT;
		पूर्ण
	पूर्ण
	shading_table->sensor_width = st->sensor_width;
	shading_table->sensor_height = st->sensor_height;
	shading_table->fraction_bits = st->fraction_bits;
	shading_table->enable = st->enable;

	/* No need to update shading table अगर it is the same */
	अगर (old_table &&
	    old_table->sensor_width == shading_table->sensor_width &&
	    old_table->sensor_height == shading_table->sensor_height &&
	    old_table->width == shading_table->width &&
	    old_table->height == shading_table->height &&
	    old_table->fraction_bits == shading_table->fraction_bits &&
	    old_table->enable == shading_table->enable) अणु
		bool data_is_same = true;

		क्रम (i = 0; i < ATOMISP_NUM_SC_COLORS; i++) अणु
			अगर (स_भेद(shading_table->data[i], old_table->data[i],
				   len_table) != 0) अणु
				data_is_same = false;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (data_is_same) अणु
			atomisp_css_shading_table_मुक्त(shading_table);
			वापस 0;
		पूर्ण
	पूर्ण

set_lsc:
	/* set LSC to CSS */
	css_param->shading_table = shading_table;
	css_param->update_flag.shading_table = (काष्ठा atomisp_shading_table *)shading_table;
	asd->params.sc_en = shading_table;

	अगर (old_table)
		atomisp_css_shading_table_मुक्त(old_table);

	वापस 0;
पूर्ण

पूर्णांक atomisp_css_cp_dvs2_coefs(काष्ठा atomisp_sub_device *asd,
			      काष्ठा ia_css_dvs2_coefficients *coefs,
			      काष्ठा atomisp_css_params *css_param,
			      bool from_user)
अणु
	काष्ठा ia_css_dvs_grid_info *cur =
	    atomisp_css_get_dvs_grid_info(&asd->params.curr_grid_info);
	पूर्णांक dvs_hor_coef_bytes, dvs_ver_coef_bytes;
	काष्ठा ia_css_dvs2_coefficients dvs2_coefs;

	अगर (!coefs || !cur)
		वापस 0;

	अगर (!from_user && css_param->update_flag.dvs2_coefs)
		वापस 0;

	अगर (!IS_ISP2401) अणु
		अगर (माप(*cur) != माप(coefs->grid) ||
		    स_भेद(&coefs->grid, cur, माप(coefs->grid))) अणु
			dev_err(asd->isp->dev, "dvs grid mis-match!\n");
			/* If the grid info in the argument dअगरfers from the current
			grid info, we tell the caller to reset the grid size and
			try again. */
			वापस -EAGAIN;
		पूर्ण

		अगर (!coefs->hor_coefs.odd_real ||
		    !coefs->hor_coefs.odd_imag ||
		    !coefs->hor_coefs.even_real ||
		    !coefs->hor_coefs.even_imag ||
		    !coefs->ver_coefs.odd_real ||
		    !coefs->ver_coefs.odd_imag ||
		    !coefs->ver_coefs.even_real ||
		    !coefs->ver_coefs.even_imag)
			वापस -EINVAL;

		अगर (!css_param->dvs2_coeff) अणु
			/* DIS coefficients. */
			css_param->dvs2_coeff = ia_css_dvs2_coefficients_allocate(cur);
			अगर (!css_param->dvs2_coeff)
				वापस -ENOMEM;
		पूर्ण

		dvs_hor_coef_bytes = asd->params.dvs_hor_coef_bytes;
		dvs_ver_coef_bytes = asd->params.dvs_ver_coef_bytes;
		अगर (copy_from_compatible(css_param->dvs2_coeff->hor_coefs.odd_real,
					coefs->hor_coefs.odd_real, dvs_hor_coef_bytes, from_user) ||
		    copy_from_compatible(css_param->dvs2_coeff->hor_coefs.odd_imag,
					coefs->hor_coefs.odd_imag, dvs_hor_coef_bytes, from_user) ||
		    copy_from_compatible(css_param->dvs2_coeff->hor_coefs.even_real,
					coefs->hor_coefs.even_real, dvs_hor_coef_bytes, from_user) ||
		    copy_from_compatible(css_param->dvs2_coeff->hor_coefs.even_imag,
					coefs->hor_coefs.even_imag, dvs_hor_coef_bytes, from_user) ||
		    copy_from_compatible(css_param->dvs2_coeff->ver_coefs.odd_real,
					coefs->ver_coefs.odd_real, dvs_ver_coef_bytes, from_user) ||
		    copy_from_compatible(css_param->dvs2_coeff->ver_coefs.odd_imag,
					coefs->ver_coefs.odd_imag, dvs_ver_coef_bytes, from_user) ||
		    copy_from_compatible(css_param->dvs2_coeff->ver_coefs.even_real,
					coefs->ver_coefs.even_real, dvs_ver_coef_bytes, from_user) ||
		    copy_from_compatible(css_param->dvs2_coeff->ver_coefs.even_imag,
					coefs->ver_coefs.even_imag, dvs_ver_coef_bytes, from_user)) अणु
			ia_css_dvs2_coefficients_मुक्त(css_param->dvs2_coeff);
			css_param->dvs2_coeff = शून्य;
			वापस -EFAULT;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (copy_from_compatible(&dvs2_coefs, coefs,
					माप(काष्ठा ia_css_dvs2_coefficients),
					from_user)) अणु
			dev_err(asd->isp->dev, "copy dvs2 coef failed");
			वापस -EFAULT;
		पूर्ण

		अगर (माप(*cur) != माप(dvs2_coefs.grid) ||
		    स_भेद(&dvs2_coefs.grid, cur, माप(dvs2_coefs.grid))) अणु
			dev_err(asd->isp->dev, "dvs grid mis-match!\n");
			/* If the grid info in the argument dअगरfers from the current
			grid info, we tell the caller to reset the grid size and
			try again. */
			वापस -EAGAIN;
		पूर्ण

		अगर (!dvs2_coefs.hor_coefs.odd_real ||
		    !dvs2_coefs.hor_coefs.odd_imag ||
		    !dvs2_coefs.hor_coefs.even_real ||
		    !dvs2_coefs.hor_coefs.even_imag ||
		    !dvs2_coefs.ver_coefs.odd_real ||
		    !dvs2_coefs.ver_coefs.odd_imag ||
		    !dvs2_coefs.ver_coefs.even_real ||
		    !dvs2_coefs.ver_coefs.even_imag)
			वापस -EINVAL;

		अगर (!css_param->dvs2_coeff) अणु
			/* DIS coefficients. */
			css_param->dvs2_coeff = ia_css_dvs2_coefficients_allocate(cur);
			अगर (!css_param->dvs2_coeff)
				वापस -ENOMEM;
		पूर्ण

		dvs_hor_coef_bytes = asd->params.dvs_hor_coef_bytes;
		dvs_ver_coef_bytes = asd->params.dvs_ver_coef_bytes;
		अगर (copy_from_compatible(css_param->dvs2_coeff->hor_coefs.odd_real,
					dvs2_coefs.hor_coefs.odd_real, dvs_hor_coef_bytes, from_user) ||
		    copy_from_compatible(css_param->dvs2_coeff->hor_coefs.odd_imag,
					dvs2_coefs.hor_coefs.odd_imag, dvs_hor_coef_bytes, from_user) ||
		    copy_from_compatible(css_param->dvs2_coeff->hor_coefs.even_real,
					dvs2_coefs.hor_coefs.even_real, dvs_hor_coef_bytes, from_user) ||
		    copy_from_compatible(css_param->dvs2_coeff->hor_coefs.even_imag,
					dvs2_coefs.hor_coefs.even_imag, dvs_hor_coef_bytes, from_user) ||
		    copy_from_compatible(css_param->dvs2_coeff->ver_coefs.odd_real,
					dvs2_coefs.ver_coefs.odd_real, dvs_ver_coef_bytes, from_user) ||
		    copy_from_compatible(css_param->dvs2_coeff->ver_coefs.odd_imag,
					dvs2_coefs.ver_coefs.odd_imag, dvs_ver_coef_bytes, from_user) ||
		    copy_from_compatible(css_param->dvs2_coeff->ver_coefs.even_real,
					dvs2_coefs.ver_coefs.even_real, dvs_ver_coef_bytes, from_user) ||
		    copy_from_compatible(css_param->dvs2_coeff->ver_coefs.even_imag,
					dvs2_coefs.ver_coefs.even_imag, dvs_ver_coef_bytes, from_user)) अणु
			ia_css_dvs2_coefficients_मुक्त(css_param->dvs2_coeff);
			css_param->dvs2_coeff = शून्य;
			वापस -EFAULT;
		पूर्ण
	पूर्ण

	css_param->update_flag.dvs2_coefs =
	    (काष्ठा atomisp_dis_coefficients *)css_param->dvs2_coeff;
	वापस 0;
पूर्ण

पूर्णांक atomisp_cp_dvs_6axis_config(काष्ठा atomisp_sub_device *asd,
				काष्ठा atomisp_dvs_6axis_config *source_6axis_config,
				काष्ठा atomisp_css_params *css_param,
				bool from_user)
अणु
	काष्ठा ia_css_dvs_6axis_config *dvs_6axis_config;
	काष्ठा ia_css_dvs_6axis_config *old_6axis_config;
	काष्ठा ia_css_stream *stream =
		    asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL].stream;
	काष्ठा ia_css_dvs_grid_info *dvs_grid_info =
	    atomisp_css_get_dvs_grid_info(&asd->params.curr_grid_info);
	पूर्णांक ret = -EFAULT;

	अगर (!stream) अणु
		dev_err(asd->isp->dev, "%s: internal error!", __func__);
		वापस -EINVAL;
	पूर्ण

	अगर (!source_6axis_config || !dvs_grid_info)
		वापस 0;

	अगर (!dvs_grid_info->enable)
		वापस 0;

	अगर (!from_user && css_param->update_flag.dvs_6axis_config)
		वापस 0;

	/* check whether need to पुनः_स्मृतिate क्रम 6 axis config */
	old_6axis_config = css_param->dvs_6axis;
	dvs_6axis_config = old_6axis_config;

	अगर (IS_ISP2401) अणु
		काष्ठा ia_css_dvs_6axis_config t_6axis_config;

		अगर (copy_from_compatible(&t_6axis_config, source_6axis_config,
					माप(काष्ठा atomisp_dvs_6axis_config),
					from_user)) अणु
			dev_err(asd->isp->dev, "copy morph table failed!");
			वापस -EFAULT;
		पूर्ण

		अगर (old_6axis_config &&
		    (old_6axis_config->width_y != t_6axis_config.width_y ||
		    old_6axis_config->height_y != t_6axis_config.height_y ||
		    old_6axis_config->width_uv != t_6axis_config.width_uv ||
		    old_6axis_config->height_uv != t_6axis_config.height_uv)) अणु
			ia_css_dvs2_6axis_config_मुक्त(css_param->dvs_6axis);
			css_param->dvs_6axis = शून्य;

			dvs_6axis_config = ia_css_dvs2_6axis_config_allocate(stream);
			अगर (!dvs_6axis_config)
				वापस -ENOMEM;
		पूर्ण अन्यथा अगर (!dvs_6axis_config) अणु
			dvs_6axis_config = ia_css_dvs2_6axis_config_allocate(stream);
			अगर (!dvs_6axis_config)
				वापस -ENOMEM;
		पूर्ण

		dvs_6axis_config->exp_id = t_6axis_config.exp_id;

		अगर (copy_from_compatible(dvs_6axis_config->xcoords_y,
					t_6axis_config.xcoords_y,
					t_6axis_config.width_y *
					t_6axis_config.height_y *
					माप(*dvs_6axis_config->xcoords_y),
					from_user))
			जाओ error;
		अगर (copy_from_compatible(dvs_6axis_config->ycoords_y,
					t_6axis_config.ycoords_y,
					t_6axis_config.width_y *
					t_6axis_config.height_y *
					माप(*dvs_6axis_config->ycoords_y),
					from_user))
			जाओ error;
		अगर (copy_from_compatible(dvs_6axis_config->xcoords_uv,
					t_6axis_config.xcoords_uv,
					t_6axis_config.width_uv *
					t_6axis_config.height_uv *
					माप(*dvs_6axis_config->xcoords_uv),
					from_user))
			जाओ error;
		अगर (copy_from_compatible(dvs_6axis_config->ycoords_uv,
					t_6axis_config.ycoords_uv,
					t_6axis_config.width_uv *
					t_6axis_config.height_uv *
					माप(*dvs_6axis_config->ycoords_uv),
					from_user))
			जाओ error;
	पूर्ण अन्यथा अणु
		अगर (old_6axis_config &&
		    (old_6axis_config->width_y != source_6axis_config->width_y ||
		    old_6axis_config->height_y != source_6axis_config->height_y ||
		    old_6axis_config->width_uv != source_6axis_config->width_uv ||
		    old_6axis_config->height_uv != source_6axis_config->height_uv)) अणु
			ia_css_dvs2_6axis_config_मुक्त(css_param->dvs_6axis);
			css_param->dvs_6axis = शून्य;

			dvs_6axis_config = ia_css_dvs2_6axis_config_allocate(stream);
			अगर (!dvs_6axis_config)
				वापस -ENOMEM;
		पूर्ण अन्यथा अगर (!dvs_6axis_config) अणु
			dvs_6axis_config = ia_css_dvs2_6axis_config_allocate(stream);
			अगर (!dvs_6axis_config)
				वापस -ENOMEM;
		पूर्ण

		dvs_6axis_config->exp_id = source_6axis_config->exp_id;

		अगर (copy_from_compatible(dvs_6axis_config->xcoords_y,
					source_6axis_config->xcoords_y,
					source_6axis_config->width_y *
					source_6axis_config->height_y *
					माप(*source_6axis_config->xcoords_y),
					from_user))
			जाओ error;
		अगर (copy_from_compatible(dvs_6axis_config->ycoords_y,
					source_6axis_config->ycoords_y,
					source_6axis_config->width_y *
					source_6axis_config->height_y *
					माप(*source_6axis_config->ycoords_y),
					from_user))
			जाओ error;
		अगर (copy_from_compatible(dvs_6axis_config->xcoords_uv,
					source_6axis_config->xcoords_uv,
					source_6axis_config->width_uv *
					source_6axis_config->height_uv *
					माप(*source_6axis_config->xcoords_uv),
					from_user))
			जाओ error;
		अगर (copy_from_compatible(dvs_6axis_config->ycoords_uv,
					source_6axis_config->ycoords_uv,
					source_6axis_config->width_uv *
					source_6axis_config->height_uv *
					माप(*source_6axis_config->ycoords_uv),
					from_user))
			जाओ error;
	पूर्ण
	css_param->dvs_6axis = dvs_6axis_config;
	css_param->update_flag.dvs_6axis_config =
	    (काष्ठा atomisp_dvs_6axis_config *)dvs_6axis_config;
	वापस 0;

error:
	अगर (dvs_6axis_config)
		ia_css_dvs2_6axis_config_मुक्त(dvs_6axis_config);
	वापस ret;
पूर्ण

पूर्णांक atomisp_cp_morph_table(काष्ठा atomisp_sub_device *asd,
			   काष्ठा atomisp_morph_table *source_morph_table,
			   काष्ठा atomisp_css_params *css_param,
			   bool from_user)
अणु
	पूर्णांक ret = -EFAULT;
	अचिन्हित पूर्णांक i;
	काष्ठा ia_css_morph_table *morph_table;
	काष्ठा ia_css_morph_table *old_morph_table;

	अगर (!source_morph_table)
		वापस 0;

	अगर (!from_user && css_param->update_flag.morph_table)
		वापस 0;

	old_morph_table = css_param->morph_table;

	अगर (IS_ISP2401) अणु
		काष्ठा ia_css_morph_table mtbl;

		अगर (copy_from_compatible(&mtbl, source_morph_table,
				माप(काष्ठा atomisp_morph_table),
				from_user)) अणु
			dev_err(asd->isp->dev, "copy morph table failed!");
			वापस -EFAULT;
		पूर्ण

		morph_table = atomisp_css_morph_table_allocate(
				mtbl.width,
				mtbl.height);
		अगर (!morph_table)
			वापस -ENOMEM;

		क्रम (i = 0; i < IA_CSS_MORPH_TABLE_NUM_PLANES; i++) अणु
			अगर (copy_from_compatible(morph_table->coordinates_x[i],
						(__क्रमce व्योम *)source_morph_table->coordinates_x[i],
						mtbl.height * mtbl.width *
						माप(*morph_table->coordinates_x[i]),
						from_user))
				जाओ error;

			अगर (copy_from_compatible(morph_table->coordinates_y[i],
						(__क्रमce व्योम *)source_morph_table->coordinates_y[i],
						mtbl.height * mtbl.width *
						माप(*morph_table->coordinates_y[i]),
						from_user))
				जाओ error;
		पूर्ण
	पूर्ण अन्यथा अणु
		morph_table = atomisp_css_morph_table_allocate(
				source_morph_table->width,
				source_morph_table->height);
		अगर (!morph_table)
			वापस -ENOMEM;

		क्रम (i = 0; i < IA_CSS_MORPH_TABLE_NUM_PLANES; i++) अणु
			अगर (copy_from_compatible(morph_table->coordinates_x[i],
						(__क्रमce व्योम *)source_morph_table->coordinates_x[i],
						source_morph_table->height * source_morph_table->width *
						माप(*source_morph_table->coordinates_x[i]),
						from_user))
				जाओ error;

			अगर (copy_from_compatible(morph_table->coordinates_y[i],
						(__क्रमce व्योम *)source_morph_table->coordinates_y[i],
						source_morph_table->height * source_morph_table->width *
						माप(*source_morph_table->coordinates_y[i]),
						from_user))
				जाओ error;
		पूर्ण
	पूर्ण

	css_param->morph_table = morph_table;
	अगर (old_morph_table)
		atomisp_css_morph_table_मुक्त(old_morph_table);
	css_param->update_flag.morph_table =
	    (काष्ठा atomisp_morph_table *)morph_table;
	वापस 0;

error:
	अगर (morph_table)
		atomisp_css_morph_table_मुक्त(morph_table);
	वापस ret;
पूर्ण

पूर्णांक atomisp_makeup_css_parameters(काष्ठा atomisp_sub_device *asd,
				  काष्ठा atomisp_parameters *arg,
				  काष्ठा atomisp_css_params *css_param)
अणु
	पूर्णांक ret;

	ret = atomisp_cp_general_isp_parameters(asd, arg, css_param, false);
	अगर (ret)
		वापस ret;
	ret = atomisp_cp_lsc_table(asd, arg->shading_table, css_param, false);
	अगर (ret)
		वापस ret;
	ret = atomisp_cp_morph_table(asd, arg->morph_table, css_param, false);
	अगर (ret)
		वापस ret;
	ret = atomisp_css_cp_dvs2_coefs(asd,
					(काष्ठा ia_css_dvs2_coefficients *)arg->dvs2_coefs,
					css_param, false);
	अगर (ret)
		वापस ret;
	ret = atomisp_cp_dvs_6axis_config(asd, arg->dvs_6axis_config,
					  css_param, false);
	वापस ret;
पूर्ण

व्योम atomisp_मुक्त_css_parameters(काष्ठा atomisp_css_params *css_param)
अणु
	अगर (css_param->dvs_6axis) अणु
		ia_css_dvs2_6axis_config_मुक्त(css_param->dvs_6axis);
		css_param->dvs_6axis = शून्य;
	पूर्ण
	अगर (css_param->dvs2_coeff) अणु
		ia_css_dvs2_coefficients_मुक्त(css_param->dvs2_coeff);
		css_param->dvs2_coeff = शून्य;
	पूर्ण
	अगर (css_param->shading_table) अणु
		ia_css_shading_table_मुक्त(css_param->shading_table);
		css_param->shading_table = शून्य;
	पूर्ण
	अगर (css_param->morph_table) अणु
		ia_css_morph_table_मुक्त(css_param->morph_table);
		css_param->morph_table = शून्य;
	पूर्ण
पूर्ण

/*
 * Check parameter queue list and buffer queue list to find out अगर matched items
 * and then set parameter to CSS and enqueue buffer to CSS.
 * Of course, अगर the buffer in buffer रुकोing list is not bound to a per-frame
 * parameter, it will be enqueued पूर्णांकo CSS as दीर्घ as the per-frame setting
 * buffers beक्रमe it get enqueued.
 */
व्योम atomisp_handle_parameter_and_buffer(काष्ठा atomisp_video_pipe *pipe)
अणु
	काष्ठा atomisp_sub_device *asd = pipe->asd;
	काष्ठा videobuf_buffer *vb = शून्य, *vb_पंचांगp;
	काष्ठा atomisp_css_params_with_list *param = शून्य, *param_पंचांगp;
	काष्ठा videobuf_vदो_स्मृति_memory *vm_mem = शून्य;
	अचिन्हित दीर्घ irqflags;
	bool need_to_enqueue_buffer = false;

	अगर (atomisp_is_vf_pipe(pipe))
		वापस;

	/*
	 * CSS/FW requires set parameter and enqueue buffer happen after ISP
	 * is streamon.
	 */
	अगर (asd->streaming != ATOMISP_DEVICE_STREAMING_ENABLED)
		वापस;

	अगर (list_empty(&pipe->per_frame_params) ||
	    list_empty(&pipe->buffers_रुकोing_क्रम_param))
		वापस;

	list_क्रम_each_entry_safe(vb, vb_पंचांगp,
				 &pipe->buffers_रुकोing_क्रम_param, queue) अणु
		अगर (pipe->frame_request_config_id[vb->i]) अणु
			list_क्रम_each_entry_safe(param, param_पंचांगp,
						 &pipe->per_frame_params, list) अणु
				अगर (pipe->frame_request_config_id[vb->i] !=
				    param->params.isp_config_id)
					जारी;

				list_del(&param->list);
				list_del(&vb->queue);
				/*
				 * clear the request config id as the buffer
				 * will be handled and enqueued पूर्णांकo CSS soon
				 */
				pipe->frame_request_config_id[vb->i] = 0;
				pipe->frame_params[vb->i] = param;
				vm_mem = vb->priv;
				BUG_ON(!vm_mem);
				अवरोध;
			पूर्ण

			अगर (vm_mem) अणु
				spin_lock_irqsave(&pipe->irq_lock, irqflags);
				list_add_tail(&vb->queue, &pipe->activeq);
				spin_unlock_irqrestore(&pipe->irq_lock, irqflags);
				vm_mem = शून्य;
				need_to_enqueue_buffer = true;
			पूर्ण अन्यथा अणु
				/* The is the end, stop further loop */
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			list_del(&vb->queue);
			pipe->frame_params[vb->i] = शून्य;
			spin_lock_irqsave(&pipe->irq_lock, irqflags);
			list_add_tail(&vb->queue, &pipe->activeq);
			spin_unlock_irqrestore(&pipe->irq_lock, irqflags);
			need_to_enqueue_buffer = true;
		पूर्ण
	पूर्ण

	अगर (!need_to_enqueue_buffer)
		वापस;

	atomisp_qbuffers_to_css(asd);

	अगर (!IS_ISP2401) अणु
		अगर (!atomisp_is_wdt_running(asd) && atomisp_buffers_queued(asd))
			atomisp_wdt_start(asd);
	पूर्ण अन्यथा अणु
		अगर (atomisp_buffers_queued_pipe(pipe)) अणु
			अगर (!atomisp_is_wdt_running(pipe))
				atomisp_wdt_start_pipe(pipe);
			अन्यथा
				atomisp_wdt_refresh_pipe(pipe,
							ATOMISP_WDT_KEEP_CURRENT_DELAY);
		पूर्ण
	पूर्ण
पूर्ण

/*
* Function to configure ISP parameters
*/
पूर्णांक atomisp_set_parameters(काष्ठा video_device *vdev,
			   काष्ठा atomisp_parameters *arg)
अणु
	काष्ठा atomisp_video_pipe *pipe = atomisp_to_video_pipe(vdev);
	काष्ठा atomisp_sub_device *asd = pipe->asd;
	काष्ठा atomisp_css_params_with_list *param = शून्य;
	काष्ठा atomisp_css_params *css_param = &asd->params.css_param;
	पूर्णांक ret;

	अगर (!asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL].stream) अणु
		dev_err(asd->isp->dev, "%s: internal error!\n", __func__);
		वापस -EINVAL;
	पूर्ण

	dev_dbg(asd->isp->dev,
		"%s: set parameter(per_frame_setting %d) for asd%d with isp_config_id %d of %s\n",
		__func__, arg->per_frame_setting, asd->index,
		arg->isp_config_id, vdev->name);

	अगर (IS_ISP2401) अणु
		अगर (atomisp_is_vf_pipe(pipe) && arg->per_frame_setting) अणु
			dev_err(asd->isp->dev, "%s: vf pipe not support per_frame_setting",
				__func__);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (arg->per_frame_setting && !atomisp_is_vf_pipe(pipe)) अणु
		/*
		 * Per-frame setting enabled, we allocate a new parameter
		 * buffer to cache the parameters and only when frame buffers
		 * are पढ़ोy, the parameters will be set to CSS.
		 * per-frame setting only works क्रम the मुख्य output frame.
		 */
		param = kvzalloc(माप(*param), GFP_KERNEL);
		अगर (!param) अणु
			dev_err(asd->isp->dev, "%s: failed to alloc params buffer\n",
				__func__);
			वापस -ENOMEM;
		पूर्ण
		css_param = &param->params;
	पूर्ण

	ret = atomisp_cp_general_isp_parameters(asd, arg, css_param, true);
	अगर (ret)
		जाओ apply_parameter_failed;

	ret = atomisp_cp_lsc_table(asd, arg->shading_table, css_param, true);
	अगर (ret)
		जाओ apply_parameter_failed;

	ret = atomisp_cp_morph_table(asd, arg->morph_table, css_param, true);
	अगर (ret)
		जाओ apply_parameter_failed;

	ret = atomisp_css_cp_dvs2_coefs(asd,
					(काष्ठा ia_css_dvs2_coefficients *)arg->dvs2_coefs,
					css_param, true);
	अगर (ret)
		जाओ apply_parameter_failed;

	ret = atomisp_cp_dvs_6axis_config(asd, arg->dvs_6axis_config,
					  css_param, true);
	अगर (ret)
		जाओ apply_parameter_failed;

	अगर (!(arg->per_frame_setting && !atomisp_is_vf_pipe(pipe))) अणु
		/* indicate to CSS that we have parameters to be updated */
		asd->params.css_update_params_needed = true;
	पूर्ण अन्यथा अणु
		list_add_tail(&param->list, &pipe->per_frame_params);
		atomisp_handle_parameter_and_buffer(pipe);
	पूर्ण

	वापस 0;

apply_parameter_failed:
	अगर (css_param)
		atomisp_मुक्त_css_parameters(css_param);
	kvमुक्त(param);

	वापस ret;
पूर्ण

/*
 * Function to set/get isp parameters to isp
 */
पूर्णांक atomisp_param(काष्ठा atomisp_sub_device *asd, पूर्णांक flag,
		  काष्ठा atomisp_parm *config)
अणु
	काष्ठा ia_css_pipe_config *vp_cfg =
		    &asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL].
		    pipe_configs[IA_CSS_PIPE_ID_VIDEO];

	/* Read parameter क्रम 3A binary info */
	अगर (flag == 0) अणु
		काष्ठा ia_css_dvs_grid_info *dvs_grid_info =
		    atomisp_css_get_dvs_grid_info(
			&asd->params.curr_grid_info);

		atomisp_curr_user_grid_info(asd, &config->info);

		/* We always वापस the resolution and stride even अगर there is
		 * no valid metadata. This allows the caller to get the
		 * inक्रमmation needed to allocate user-space buffers. */
		config->metadata_config.metadata_height = asd->
			stream_env[ATOMISP_INPUT_STREAM_GENERAL].stream_info.
			metadata_info.resolution.height;
		config->metadata_config.metadata_stride = asd->
			stream_env[ATOMISP_INPUT_STREAM_GENERAL].stream_info.
			metadata_info.stride;

		/* update dvs grid info */
		अगर (dvs_grid_info)
			स_नकल(&config->dvs_grid,
			       dvs_grid_info,
			       माप(काष्ठा ia_css_dvs_grid_info));

		अगर (asd->run_mode->val != ATOMISP_RUN_MODE_VIDEO) अणु
			config->dvs_envelop.width = 0;
			config->dvs_envelop.height = 0;
			वापस 0;
		पूर्ण

		/* update dvs envelop info */
		अगर (!asd->continuous_mode->val) अणु
			config->dvs_envelop.width = vp_cfg->dvs_envelope.width;
			config->dvs_envelop.height =
			    vp_cfg->dvs_envelope.height;
		पूर्ण अन्यथा अणु
			अचिन्हित पूर्णांक dvs_w, dvs_h, dvs_w_max, dvs_h_max;

			dvs_w = vp_cfg->bayer_ds_out_res.width -
				vp_cfg->output_info[0].res.width;
			dvs_h = vp_cfg->bayer_ds_out_res.height -
				vp_cfg->output_info[0].res.height;
			dvs_w_max = roundकरोwn(
					vp_cfg->output_info[0].res.width / 5,
					ATOM_ISP_STEP_WIDTH);
			dvs_h_max = roundकरोwn(
					vp_cfg->output_info[0].res.height / 5,
					ATOM_ISP_STEP_HEIGHT);

			config->dvs_envelop.width = min(dvs_w, dvs_w_max);
			config->dvs_envelop.height = min(dvs_h, dvs_h_max);
		पूर्ण

		वापस 0;
	पूर्ण

	स_नकल(&asd->params.css_param.wb_config, &config->wb_config,
	       माप(काष्ठा ia_css_wb_config));
	स_नकल(&asd->params.css_param.ob_config, &config->ob_config,
	       माप(काष्ठा ia_css_ob_config));
	स_नकल(&asd->params.css_param.dp_config, &config->dp_config,
	       माप(काष्ठा ia_css_dp_config));
	स_नकल(&asd->params.css_param.de_config, &config->de_config,
	       माप(काष्ठा ia_css_de_config));
	स_नकल(&asd->params.css_param.dz_config, &config->dz_config,
	       माप(काष्ठा ia_css_dz_config));
	स_नकल(&asd->params.css_param.ce_config, &config->ce_config,
	       माप(काष्ठा ia_css_ce_config));
	स_नकल(&asd->params.css_param.nr_config, &config->nr_config,
	       माप(काष्ठा ia_css_nr_config));
	स_नकल(&asd->params.css_param.ee_config, &config->ee_config,
	       माप(काष्ठा ia_css_ee_config));
	स_नकल(&asd->params.css_param.tnr_config, &config->tnr_config,
	       माप(काष्ठा ia_css_tnr_config));

	अगर (asd->params.color_effect == V4L2_COLORFX_NEGATIVE) अणु
		asd->params.css_param.cc_config.matrix[3] = -config->cc_config.matrix[3];
		asd->params.css_param.cc_config.matrix[4] = -config->cc_config.matrix[4];
		asd->params.css_param.cc_config.matrix[5] = -config->cc_config.matrix[5];
		asd->params.css_param.cc_config.matrix[6] = -config->cc_config.matrix[6];
		asd->params.css_param.cc_config.matrix[7] = -config->cc_config.matrix[7];
		asd->params.css_param.cc_config.matrix[8] = -config->cc_config.matrix[8];
	पूर्ण

	अगर (asd->params.color_effect != V4L2_COLORFX_SEPIA &&
	    asd->params.color_effect != V4L2_COLORFX_BW) अणु
		स_नकल(&asd->params.css_param.cc_config, &config->cc_config,
		       माप(काष्ठा ia_css_cc_config));
		asd->params.config.cc_config = &asd->params.css_param.cc_config;
	पूर्ण

	asd->params.config.wb_config = &asd->params.css_param.wb_config;
	asd->params.config.ob_config = &asd->params.css_param.ob_config;
	asd->params.config.de_config = &asd->params.css_param.de_config;
	asd->params.config.dz_config = &asd->params.css_param.dz_config;
	asd->params.config.ce_config = &asd->params.css_param.ce_config;
	asd->params.config.dp_config = &asd->params.css_param.dp_config;
	asd->params.config.nr_config = &asd->params.css_param.nr_config;
	asd->params.config.ee_config = &asd->params.css_param.ee_config;
	asd->params.config.tnr_config = &asd->params.css_param.tnr_config;
	asd->params.css_update_params_needed = true;

	वापस 0;
पूर्ण

/*
 * Function to configure color effect of the image
 */
पूर्णांक atomisp_color_effect(काष्ठा atomisp_sub_device *asd, पूर्णांक flag,
			 __s32 *effect)
अणु
	काष्ठा ia_css_cc_config *cc_config = शून्य;
	काष्ठा ia_css_macc_table *macc_table = शून्य;
	काष्ठा ia_css_ctc_table *ctc_table = शून्य;
	पूर्णांक ret = 0;
	काष्ठा v4l2_control control;
	काष्ठा atomisp_device *isp = asd->isp;

	अगर (flag == 0) अणु
		*effect = asd->params.color_effect;
		वापस 0;
	पूर्ण

	control.id = V4L2_CID_COLORFX;
	control.value = *effect;
	ret =
	    v4l2_s_ctrl(शून्य, isp->inमाला_दो[asd->input_curr].camera->ctrl_handler,
			&control);
	/*
	 * अगर set color effect to sensor successfully, वापस
	 * 0 directly.
	 */
	अगर (!ret) अणु
		asd->params.color_effect = (u32)*effect;
		वापस 0;
	पूर्ण

	अगर (*effect == asd->params.color_effect)
		वापस 0;

	/*
	 * isp_subdev->params.macc_en should be set to false.
	 */
	asd->params.macc_en = false;

	चयन (*effect) अणु
	हाल V4L2_COLORFX_NONE:
		macc_table = &asd->params.css_param.macc_table;
		asd->params.macc_en = true;
		अवरोध;
	हाल V4L2_COLORFX_SEPIA:
		cc_config = &sepia_cc_config;
		अवरोध;
	हाल V4L2_COLORFX_NEGATIVE:
		cc_config = &nega_cc_config;
		अवरोध;
	हाल V4L2_COLORFX_BW:
		cc_config = &mono_cc_config;
		अवरोध;
	हाल V4L2_COLORFX_SKY_BLUE:
		macc_table = &blue_macc_table;
		asd->params.macc_en = true;
		अवरोध;
	हाल V4L2_COLORFX_GRASS_GREEN:
		macc_table = &green_macc_table;
		asd->params.macc_en = true;
		अवरोध;
	हाल V4L2_COLORFX_SKIN_WHITEN_LOW:
		macc_table = &skin_low_macc_table;
		asd->params.macc_en = true;
		अवरोध;
	हाल V4L2_COLORFX_SKIN_WHITEN:
		macc_table = &skin_medium_macc_table;
		asd->params.macc_en = true;
		अवरोध;
	हाल V4L2_COLORFX_SKIN_WHITEN_HIGH:
		macc_table = &skin_high_macc_table;
		asd->params.macc_en = true;
		अवरोध;
	हाल V4L2_COLORFX_VIVID:
		ctc_table = &vivid_ctc_table;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	atomisp_update_capture_mode(asd);

	अगर (cc_config)
		asd->params.config.cc_config = cc_config;
	अगर (macc_table)
		asd->params.config.macc_table = macc_table;
	अगर (ctc_table)
		atomisp_css_set_ctc_table(asd, ctc_table);
	asd->params.color_effect = (u32)*effect;
	asd->params.css_update_params_needed = true;
	वापस 0;
पूर्ण

/*
 * Function to configure bad pixel correction
 */
पूर्णांक atomisp_bad_pixel(काष्ठा atomisp_sub_device *asd, पूर्णांक flag,
		      __s32 *value)
अणु
	अगर (flag == 0) अणु
		*value = asd->params.bad_pixel_en;
		वापस 0;
	पूर्ण
	asd->params.bad_pixel_en = !!*value;

	वापस 0;
पूर्ण

/*
 * Function to configure bad pixel correction params
 */
पूर्णांक atomisp_bad_pixel_param(काष्ठा atomisp_sub_device *asd, पूर्णांक flag,
			    काष्ठा atomisp_dp_config *config)
अणु
	अगर (flag == 0) अणु
		/* Get bad pixel from current setup */
		अगर (atomisp_css_get_dp_config(asd, config))
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		/* Set bad pixel to isp parameters */
		स_नकल(&asd->params.css_param.dp_config, config,
		       माप(asd->params.css_param.dp_config));
		asd->params.config.dp_config = &asd->params.css_param.dp_config;
		asd->params.css_update_params_needed = true;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Function to enable/disable video image stablization
 */
पूर्णांक atomisp_video_stable(काष्ठा atomisp_sub_device *asd, पूर्णांक flag,
			 __s32 *value)
अणु
	अगर (flag == 0)
		*value = asd->params.video_dis_en;
	अन्यथा
		asd->params.video_dis_en = !!*value;

	वापस 0;
पूर्ण

/*
 * Function to configure fixed pattern noise
 */
पूर्णांक atomisp_fixed_pattern(काष्ठा atomisp_sub_device *asd, पूर्णांक flag,
			  __s32 *value)
अणु
	अगर (flag == 0) अणु
		*value = asd->params.fpn_en;
		वापस 0;
	पूर्ण

	अगर (*value == 0) अणु
		asd->params.fpn_en = false;
		वापस 0;
	पूर्ण

	/* Add function to get black from from sensor with shutter off */
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक
atomisp_bytesperline_to_padded_width(अचिन्हित पूर्णांक bytesperline,
				     क्रमागत ia_css_frame_क्रमmat क्रमmat)
अणु
	चयन (क्रमmat) अणु
	हाल IA_CSS_FRAME_FORMAT_UYVY:
	हाल IA_CSS_FRAME_FORMAT_YUYV:
	हाल IA_CSS_FRAME_FORMAT_RAW:
	हाल IA_CSS_FRAME_FORMAT_RGB565:
		वापस bytesperline / 2;
	हाल IA_CSS_FRAME_FORMAT_RGBA888:
		वापस bytesperline / 4;
	/* The following हालs could be हटाओd, but we leave them
	   in to करोcument the क्रमmats that are included. */
	हाल IA_CSS_FRAME_FORMAT_NV11:
	हाल IA_CSS_FRAME_FORMAT_NV12:
	हाल IA_CSS_FRAME_FORMAT_NV16:
	हाल IA_CSS_FRAME_FORMAT_NV21:
	हाल IA_CSS_FRAME_FORMAT_NV61:
	हाल IA_CSS_FRAME_FORMAT_YV12:
	हाल IA_CSS_FRAME_FORMAT_YV16:
	हाल IA_CSS_FRAME_FORMAT_YUV420:
	हाल IA_CSS_FRAME_FORMAT_YUV420_16:
	हाल IA_CSS_FRAME_FORMAT_YUV422:
	हाल IA_CSS_FRAME_FORMAT_YUV422_16:
	हाल IA_CSS_FRAME_FORMAT_YUV444:
	हाल IA_CSS_FRAME_FORMAT_YUV_LINE:
	हाल IA_CSS_FRAME_FORMAT_PLANAR_RGB888:
	हाल IA_CSS_FRAME_FORMAT_QPLANE6:
	हाल IA_CSS_FRAME_FORMAT_BINARY_8:
	शेष:
		वापस bytesperline;
	पूर्ण
पूर्ण

अटल पूर्णांक
atomisp_v4l2_framebuffer_to_css_frame(स्थिर काष्ठा v4l2_framebuffer *arg,
				      काष्ठा ia_css_frame **result)
अणु
	काष्ठा ia_css_frame *res = शून्य;
	अचिन्हित पूर्णांक padded_width;
	क्रमागत ia_css_frame_क्रमmat sh_क्रमmat;
	अक्षर *पंचांगp_buf = शून्य;
	पूर्णांक ret = 0;

	sh_क्रमmat = v4l2_fmt_to_sh_fmt(arg->fmt.pixelक्रमmat);
	padded_width = atomisp_bytesperline_to_padded_width(
			   arg->fmt.bytesperline, sh_क्रमmat);

	/* Note: the padded width on an ia_css_frame is in elements, not in
	   bytes. The RAW frame we use here should always be a 16bit RAW
	   frame. This is why we bytesperline/2 is equal to the padded with */
	अगर (ia_css_frame_allocate(&res, arg->fmt.width, arg->fmt.height,
				       sh_क्रमmat, padded_width, 0)) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	पंचांगp_buf = vदो_स्मृति(arg->fmt.sizeimage);
	अगर (!पंचांगp_buf) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण
	अगर (copy_from_user(पंचांगp_buf, (व्योम __user __क्रमce *)arg->base,
			   arg->fmt.sizeimage)) अणु
		ret = -EFAULT;
		जाओ err;
	पूर्ण

	अगर (hmm_store(res->data, पंचांगp_buf, arg->fmt.sizeimage)) अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

err:
	अगर (ret && res)
		ia_css_frame_मुक्त(res);
	vमुक्त(पंचांगp_buf);
	अगर (ret == 0)
		*result = res;
	वापस ret;
पूर्ण

/*
 * Function to configure fixed pattern noise table
 */
पूर्णांक atomisp_fixed_pattern_table(काष्ठा atomisp_sub_device *asd,
				काष्ठा v4l2_framebuffer *arg)
अणु
	काष्ठा ia_css_frame *raw_black_frame = शून्य;
	पूर्णांक ret;

	अगर (!arg)
		वापस -EINVAL;

	ret = atomisp_v4l2_framebuffer_to_css_frame(arg, &raw_black_frame);
	अगर (ret)
		वापस ret;

	अगर (sh_css_set_black_frame(asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL].stream,
				   raw_black_frame) != 0)
		वापस -ENOMEM;

	ia_css_frame_मुक्त(raw_black_frame);
	वापस ret;
पूर्ण

/*
 * Function to configure false color correction
 */
पूर्णांक atomisp_false_color(काष्ठा atomisp_sub_device *asd, पूर्णांक flag,
			__s32 *value)
अणु
	/* Get nr config from current setup */
	अगर (flag == 0) अणु
		*value = asd->params.false_color;
		वापस 0;
	पूर्ण

	/* Set nr config to isp parameters */
	अगर (*value) अणु
		asd->params.config.de_config = शून्य;
	पूर्ण अन्यथा अणु
		asd->params.css_param.de_config.pixelnoise = 0;
		asd->params.config.de_config = &asd->params.css_param.de_config;
	पूर्ण
	asd->params.css_update_params_needed = true;
	asd->params.false_color = *value;
	वापस 0;
पूर्ण

/*
 * Function to configure bad pixel correction params
 */
पूर्णांक atomisp_false_color_param(काष्ठा atomisp_sub_device *asd, पूर्णांक flag,
			      काष्ठा atomisp_de_config *config)
अणु
	अगर (flag == 0) अणु
		/* Get false color from current setup */
		अगर (atomisp_css_get_de_config(asd, config))
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		/* Set false color to isp parameters */
		स_नकल(&asd->params.css_param.de_config, config,
		       माप(asd->params.css_param.de_config));
		asd->params.config.de_config = &asd->params.css_param.de_config;
		asd->params.css_update_params_needed = true;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Function to configure white balance params
 */
पूर्णांक atomisp_white_balance_param(काष्ठा atomisp_sub_device *asd, पूर्णांक flag,
				काष्ठा atomisp_wb_config *config)
अणु
	अगर (flag == 0) अणु
		/* Get white balance from current setup */
		अगर (atomisp_css_get_wb_config(asd, config))
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		/* Set white balance to isp parameters */
		स_नकल(&asd->params.css_param.wb_config, config,
		       माप(asd->params.css_param.wb_config));
		asd->params.config.wb_config = &asd->params.css_param.wb_config;
		asd->params.css_update_params_needed = true;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक atomisp_3a_config_param(काष्ठा atomisp_sub_device *asd, पूर्णांक flag,
			    काष्ठा atomisp_3a_config *config)
अणु
	काष्ठा atomisp_device *isp = asd->isp;

	dev_dbg(isp->dev, ">%s %d\n", __func__, flag);

	अगर (flag == 0) अणु
		/* Get white balance from current setup */
		अगर (atomisp_css_get_3a_config(asd, config))
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		/* Set white balance to isp parameters */
		स_नकल(&asd->params.css_param.s3a_config, config,
		       माप(asd->params.css_param.s3a_config));
		asd->params.config.s3a_config = &asd->params.css_param.s3a_config;
		asd->params.css_update_params_needed = true;
	पूर्ण

	dev_dbg(isp->dev, "<%s %d\n", __func__, flag);
	वापस 0;
पूर्ण

/*
 * Function to setup digital zoom
 */
पूर्णांक atomisp_digital_zoom(काष्ठा atomisp_sub_device *asd, पूर्णांक flag,
			 __s32 *value)
अणु
	u32 zoom;
	काष्ठा atomisp_device *isp = asd->isp;

	अचिन्हित पूर्णांक max_zoom = MRFLD_MAX_ZOOM_FACTOR;

	अगर (flag == 0) अणु
		atomisp_css_get_zoom_factor(asd, &zoom);
		*value = max_zoom - zoom;
	पूर्ण अन्यथा अणु
		अगर (*value < 0)
			वापस -EINVAL;

		zoom = max_zoom - min_t(u32, max_zoom - 1, *value);
		atomisp_css_set_zoom_factor(asd, zoom);

		dev_dbg(isp->dev, "%s, zoom: %d\n", __func__, zoom);
		asd->params.css_update_params_needed = true;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Function to get sensor specअगरic info क्रम current resolution,
 * which will be used क्रम स्वतः exposure conversion.
 */
पूर्णांक atomisp_get_sensor_mode_data(काष्ठा atomisp_sub_device *asd,
				 काष्ठा atomisp_sensor_mode_data *config)
अणु
	काष्ठा camera_mipi_info *mipi_info;
	काष्ठा atomisp_device *isp = asd->isp;

	mipi_info = atomisp_to_sensor_mipi_info(
			isp->inमाला_दो[asd->input_curr].camera);
	अगर (!mipi_info)
		वापस -EINVAL;

	स_नकल(config, &mipi_info->data, माप(*config));
	वापस 0;
पूर्ण

पूर्णांक atomisp_get_fmt(काष्ठा video_device *vdev, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा atomisp_video_pipe *pipe = atomisp_to_video_pipe(vdev);

	f->fmt.pix = pipe->pix;

	वापस 0;
पूर्ण

अटल व्योम __atomisp_update_stream_env(काष्ठा atomisp_sub_device *asd,
					u16 stream_index, काष्ठा atomisp_input_stream_info *stream_info)
अणु
	पूर्णांक i;

	/* assign भव channel id वापस from sensor driver query */
	asd->stream_env[stream_index].ch_id = stream_info->ch_id;
	asd->stream_env[stream_index].isys_configs = stream_info->isys_configs;
	क्रम (i = 0; i < stream_info->isys_configs; i++) अणु
		asd->stream_env[stream_index].isys_info[i].input_क्रमmat =
		    stream_info->isys_info[i].input_क्रमmat;
		asd->stream_env[stream_index].isys_info[i].width =
		    stream_info->isys_info[i].width;
		asd->stream_env[stream_index].isys_info[i].height =
		    stream_info->isys_info[i].height;
	पूर्ण
पूर्ण

अटल व्योम __atomisp_init_stream_info(u16 stream_index,
				       काष्ठा atomisp_input_stream_info *stream_info)
अणु
	पूर्णांक i;

	stream_info->enable = 1;
	stream_info->stream = stream_index;
	stream_info->ch_id = 0;
	stream_info->isys_configs = 0;
	क्रम (i = 0; i < MAX_STREAMS_PER_CHANNEL; i++) अणु
		stream_info->isys_info[i].input_क्रमmat = 0;
		stream_info->isys_info[i].width = 0;
		stream_info->isys_info[i].height = 0;
	पूर्ण
पूर्ण

/* This function looks up the बंदst available resolution. */
पूर्णांक atomisp_try_fmt(काष्ठा video_device *vdev, काष्ठा v4l2_pix_क्रमmat *f,
		    bool *res_overflow)
अणु
	काष्ठा atomisp_device *isp = video_get_drvdata(vdev);
	काष्ठा atomisp_sub_device *asd = atomisp_to_video_pipe(vdev)->asd;
	काष्ठा v4l2_subdev_pad_config pad_cfg;
	काष्ठा v4l2_subdev_क्रमmat क्रमmat = अणु
		.which = V4L2_SUBDEV_FORMAT_TRY,
	पूर्ण;

	काष्ठा v4l2_mbus_framefmt *snr_mbus_fmt = &क्रमmat.क्रमmat;
	स्थिर काष्ठा atomisp_क्रमmat_bridge *fmt;
	काष्ठा atomisp_input_stream_info *stream_info =
	    (काष्ठा atomisp_input_stream_info *)snr_mbus_fmt->reserved;
	u16 stream_index;
	पूर्णांक source_pad = atomisp_subdev_source_pad(vdev);
	पूर्णांक ret;

	अगर (!isp->inमाला_दो[asd->input_curr].camera)
		वापस -EINVAL;

	stream_index = atomisp_source_pad_to_stream_id(asd, source_pad);
	fmt = atomisp_get_क्रमmat_bridge(f->pixelक्रमmat);
	अगर (!fmt) अणु
		dev_err(isp->dev, "unsupported pixelformat!\n");
		fmt = atomisp_output_fmts;
	पूर्ण

	अगर (f->width <= 0 || f->height <= 0)
		वापस -EINVAL;

	snr_mbus_fmt->code = fmt->mbus_code;
	snr_mbus_fmt->width = f->width;
	snr_mbus_fmt->height = f->height;

	__atomisp_init_stream_info(stream_index, stream_info);

	dev_dbg(isp->dev, "try_mbus_fmt: asking for %ux%u\n",
		snr_mbus_fmt->width, snr_mbus_fmt->height);

	ret = v4l2_subdev_call(isp->inमाला_दो[asd->input_curr].camera,
			       pad, set_fmt, &pad_cfg, &क्रमmat);
	अगर (ret)
		वापस ret;

	dev_dbg(isp->dev, "try_mbus_fmt: got %ux%u\n",
		snr_mbus_fmt->width, snr_mbus_fmt->height);

	fmt = atomisp_get_क्रमmat_bridge_from_mbus(snr_mbus_fmt->code);
	अगर (!fmt) अणु
		dev_err(isp->dev, "unknown sensor format 0x%8.8x\n",
			snr_mbus_fmt->code);
		वापस -EINVAL;
	पूर्ण

	f->pixelक्रमmat = fmt->pixelक्रमmat;

	/*
	 * If the क्रमmat is jpeg or custom RAW, then the width and height will
	 * not satisfy the normal atomisp requirements and no need to check
	 * the below conditions. So just assign to what is being वापसed from
	 * the sensor driver.
	 */
	अगर (f->pixelक्रमmat == V4L2_PIX_FMT_JPEG ||
	    f->pixelक्रमmat == V4L2_PIX_FMT_CUSTOM_M10MO_RAW) अणु
		f->width = snr_mbus_fmt->width;
		f->height = snr_mbus_fmt->height;
		वापस 0;
	पूर्ण

	अगर (snr_mbus_fmt->width < f->width
	    && snr_mbus_fmt->height < f->height) अणु
		f->width = snr_mbus_fmt->width;
		f->height = snr_mbus_fmt->height;
		/* Set the flag when resolution requested is
		 * beyond the max value supported by sensor
		 */
		अगर (res_overflow)
			*res_overflow = true;
	पूर्ण

	/* app vs isp */
	f->width = roundकरोwn(clamp_t(u32, f->width, ATOM_ISP_MIN_WIDTH,
				     ATOM_ISP_MAX_WIDTH), ATOM_ISP_STEP_WIDTH);
	f->height = roundकरोwn(clamp_t(u32, f->height, ATOM_ISP_MIN_HEIGHT,
				      ATOM_ISP_MAX_HEIGHT), ATOM_ISP_STEP_HEIGHT);

	वापस 0;
पूर्ण

अटल पूर्णांक
atomisp_try_fmt_file(काष्ठा atomisp_device *isp, काष्ठा v4l2_क्रमmat *f)
अणु
	u32 width = f->fmt.pix.width;
	u32 height = f->fmt.pix.height;
	u32 pixelक्रमmat = f->fmt.pix.pixelक्रमmat;
	क्रमागत v4l2_field field = f->fmt.pix.field;
	u32 depth;

	अगर (!atomisp_get_क्रमmat_bridge(pixelक्रमmat)) अणु
		dev_err(isp->dev, "Wrong output pixelformat\n");
		वापस -EINVAL;
	पूर्ण

	depth = get_pixel_depth(pixelक्रमmat);

	अगर (field == V4L2_FIELD_ANY)
		field = V4L2_FIELD_NONE;
	अन्यथा अगर (field != V4L2_FIELD_NONE) अणु
		dev_err(isp->dev, "Wrong output field\n");
		वापस -EINVAL;
	पूर्ण

	f->fmt.pix.field = field;
	f->fmt.pix.width = clamp_t(u32,
				   roundकरोwn(width, (u32)ATOM_ISP_STEP_WIDTH),
				   ATOM_ISP_MIN_WIDTH, ATOM_ISP_MAX_WIDTH);
	f->fmt.pix.height = clamp_t(u32, roundकरोwn(height,
				    (u32)ATOM_ISP_STEP_HEIGHT),
				    ATOM_ISP_MIN_HEIGHT, ATOM_ISP_MAX_HEIGHT);
	f->fmt.pix.bytesperline = (width * depth) >> 3;

	वापस 0;
पूर्ण

क्रमागत mipi_port_id __get_mipi_port(काष्ठा atomisp_device *isp,
				  क्रमागत atomisp_camera_port port)
अणु
	चयन (port) अणु
	हाल ATOMISP_CAMERA_PORT_PRIMARY:
		वापस MIPI_PORT0_ID;
	हाल ATOMISP_CAMERA_PORT_SECONDARY:
		वापस MIPI_PORT1_ID;
	हाल ATOMISP_CAMERA_PORT_TERTIARY:
		अगर (MIPI_PORT1_ID + 1 != N_MIPI_PORT_ID)
			वापस MIPI_PORT1_ID + 1;
		fallthrough;
	शेष:
		dev_err(isp->dev, "unsupported port: %d\n", port);
		वापस MIPI_PORT0_ID;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक atomisp_set_sensor_mipi_to_isp(
    काष्ठा atomisp_sub_device *asd,
    क्रमागत atomisp_input_stream_id stream_id,
    काष्ठा camera_mipi_info *mipi_info)
अणु
	काष्ठा v4l2_control ctrl;
	काष्ठा atomisp_device *isp = asd->isp;
	स्थिर काष्ठा atomisp_in_fmt_conv *fc;
	पूर्णांक mipi_freq = 0;
	अचिन्हित पूर्णांक input_क्रमmat, bayer_order;

	ctrl.id = V4L2_CID_LINK_FREQ;
	अगर (v4l2_g_ctrl
	    (isp->inमाला_दो[asd->input_curr].camera->ctrl_handler, &ctrl) == 0)
		mipi_freq = ctrl.value;

	अगर (asd->stream_env[stream_id].isys_configs == 1) अणु
		input_क्रमmat =
		    asd->stream_env[stream_id].isys_info[0].input_क्रमmat;
		atomisp_css_isys_set_क्रमmat(asd, stream_id,
					    input_क्रमmat, IA_CSS_STREAM_DEFAULT_ISYS_STREAM_IDX);
	पूर्ण अन्यथा अगर (asd->stream_env[stream_id].isys_configs == 2) अणु
		atomisp_css_isys_two_stream_cfg_update_stream1(
		    asd, stream_id,
		    asd->stream_env[stream_id].isys_info[0].input_क्रमmat,
		    asd->stream_env[stream_id].isys_info[0].width,
		    asd->stream_env[stream_id].isys_info[0].height);

		atomisp_css_isys_two_stream_cfg_update_stream2(
		    asd, stream_id,
		    asd->stream_env[stream_id].isys_info[1].input_क्रमmat,
		    asd->stream_env[stream_id].isys_info[1].width,
		    asd->stream_env[stream_id].isys_info[1].height);
	पूर्ण

	/* Compatibility क्रम sensors which provide no media bus code
	 * in s_mbus_framefmt() nor support pad क्रमmats. */
	अगर (mipi_info->input_क्रमmat != -1) अणु
		bayer_order = mipi_info->raw_bayer_order;

		/* Input stream config is still needs configured */
		/* TODO: Check अगर this is necessary */
		fc = atomisp_find_in_fmt_conv_by_atomisp_in_fmt(
			 mipi_info->input_क्रमmat);
		अगर (!fc)
			वापस -EINVAL;
		input_क्रमmat = fc->atomisp_in_fmt;
	पूर्ण अन्यथा अणु
		काष्ठा v4l2_mbus_framefmt *sink;

		sink = atomisp_subdev_get_ffmt(&asd->subdev, शून्य,
					       V4L2_SUBDEV_FORMAT_ACTIVE,
					       ATOMISP_SUBDEV_PAD_SINK);
		fc = atomisp_find_in_fmt_conv(sink->code);
		अगर (!fc)
			वापस -EINVAL;
		input_क्रमmat = fc->atomisp_in_fmt;
		bayer_order = fc->bayer_order;
	पूर्ण

	atomisp_css_input_set_क्रमmat(asd, stream_id, input_क्रमmat);
	atomisp_css_input_set_bayer_order(asd, stream_id, bayer_order);

	fc = atomisp_find_in_fmt_conv_by_atomisp_in_fmt(
		 mipi_info->metadata_क्रमmat);
	अगर (!fc)
		वापस -EINVAL;
	input_क्रमmat = fc->atomisp_in_fmt;
	atomisp_css_input_configure_port(asd,
					 __get_mipi_port(asd->isp, mipi_info->port),
					 mipi_info->num_lanes,
					 0xffff4, mipi_freq,
					 input_क्रमmat,
					 mipi_info->metadata_width,
					 mipi_info->metadata_height);
	वापस 0;
पूर्ण

अटल पूर्णांक __enable_continuous_mode(काष्ठा atomisp_sub_device *asd,
				    bool enable)
अणु
	काष्ठा atomisp_device *isp = asd->isp;

	dev_dbg(isp->dev,
		"continuous mode %d, raw buffers %d, stop preview %d\n",
		enable, asd->continuous_raw_buffer_size->val,
		!asd->continuous_viewfinder->val);

	अगर (!IS_ISP2401)
		atomisp_css_capture_set_mode(asd, IA_CSS_CAPTURE_MODE_PRIMARY);
	अन्यथा
		atomisp_update_capture_mode(asd);

	/* in हाल of ANR, क्रमce capture pipe to offline mode */
	atomisp_css_capture_enable_online(asd, ATOMISP_INPUT_STREAM_GENERAL,
					  asd->params.low_light ? false : !enable);
	atomisp_css_preview_enable_online(asd, ATOMISP_INPUT_STREAM_GENERAL,
					  !enable);
	atomisp_css_enable_continuous(asd, enable);
	atomisp_css_enable_cvf(asd, asd->continuous_viewfinder->val);

	atomisp_css_continuous_set_num_raw_frames(asd,
		asd->continuous_raw_buffer_size->val);

	अगर (!enable) अणु
		atomisp_css_enable_raw_binning(asd, false);
		atomisp_css_input_set_two_pixels_per_घड़ी(asd, false);
	पूर्ण

	अगर (isp->inमाला_दो[asd->input_curr].type != खाता_INPUT)
		atomisp_css_input_set_mode(asd, IA_CSS_INPUT_MODE_BUFFERED_SENSOR);

	वापस atomisp_update_run_mode(asd);
पूर्ण

अटल पूर्णांक configure_pp_input_nop(काष्ठा atomisp_sub_device *asd,
				  अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक configure_output_nop(काष्ठा atomisp_sub_device *asd,
				अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height,
				अचिन्हित पूर्णांक min_width,
				क्रमागत ia_css_frame_क्रमmat sh_fmt)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक get_frame_info_nop(काष्ठा atomisp_sub_device *asd,
			      काष्ठा ia_css_frame_info *finfo)
अणु
	वापस 0;
पूर्ण

/*
 * Resets CSS parameters that depend on input resolution.
 *
 * Update params like CSS RAW binning, 2ppc mode and pp_input
 * which depend on input size, but are not स्वतःmatically
 * handled in CSS when the input resolution is changed.
 */
अटल पूर्णांक css_input_resolution_changed(काष्ठा atomisp_sub_device *asd,
					काष्ठा v4l2_mbus_framefmt *ffmt)
अणु
	काष्ठा atomisp_metadata_buf *md_buf = शून्य, *_md_buf;
	अचिन्हित पूर्णांक i;

	dev_dbg(asd->isp->dev, "css_input_resolution_changed to %ux%u\n",
		ffmt->width, ffmt->height);

#अगर defined(ISP2401_NEW_INPUT_SYSTEM)
	atomisp_css_input_set_two_pixels_per_घड़ी(asd, false);
#अन्यथा
	atomisp_css_input_set_two_pixels_per_घड़ी(asd, true);
#पूर्ण_अगर
	अगर (asd->continuous_mode->val) अणु
		/* Note क्रम all checks: ffmt includes pad_w+pad_h */
		अगर (asd->run_mode->val == ATOMISP_RUN_MODE_VIDEO ||
		    (ffmt->width >= 2048 || ffmt->height >= 1536)) अणु
			/*
			 * For preview pipe, enable only अगर resolution
			 * is >= 3M क्रम ISP2400.
			 */
			atomisp_css_enable_raw_binning(asd, true);
		पूर्ण
	पूर्ण
	/*
	 * If sensor input changed, which means metadata resolution changed
	 * together. Release all metadata buffers here to let it re-allocated
	 * next समय in reqbufs.
	 */
	क्रम (i = 0; i < ATOMISP_METADATA_TYPE_NUM; i++) अणु
		list_क्रम_each_entry_safe(md_buf, _md_buf, &asd->metadata[i],
					 list) अणु
			atomisp_css_मुक्त_metadata_buffer(md_buf);
			list_del(&md_buf->list);
			kमुक्त(md_buf);
		पूर्ण
	पूर्ण
	वापस 0;

	/*
	 * TODO: atomisp_css_preview_configure_pp_input() not
	 *       reset due to CSS bug tracked as PSI BZ 115124
	 */
पूर्ण

अटल पूर्णांक atomisp_set_fmt_to_isp(काष्ठा video_device *vdev,
				  काष्ठा ia_css_frame_info *output_info,
				  काष्ठा ia_css_frame_info *raw_output_info,
				  काष्ठा v4l2_pix_क्रमmat *pix,
				  अचिन्हित पूर्णांक source_pad)
अणु
	काष्ठा camera_mipi_info *mipi_info;
	काष्ठा atomisp_device *isp = video_get_drvdata(vdev);
	काष्ठा atomisp_sub_device *asd = atomisp_to_video_pipe(vdev)->asd;
	स्थिर काष्ठा atomisp_क्रमmat_bridge *क्रमmat;
	काष्ठा v4l2_rect *isp_sink_crop;
	क्रमागत ia_css_pipe_id pipe_id;
	काष्ठा v4l2_subdev_fh fh;
	पूर्णांक (*configure_output)(काष्ठा atomisp_sub_device *asd,
				अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height,
				अचिन्हित पूर्णांक min_width,
				क्रमागत ia_css_frame_क्रमmat sh_fmt) =
				    configure_output_nop;
	पूर्णांक (*get_frame_info)(काष्ठा atomisp_sub_device *asd,
			      काष्ठा ia_css_frame_info *finfo) =
				  get_frame_info_nop;
	पूर्णांक (*configure_pp_input)(काष्ठा atomisp_sub_device *asd,
				  अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height) =
				      configure_pp_input_nop;
	u16 stream_index = atomisp_source_pad_to_stream_id(asd, source_pad);
	स्थिर काष्ठा atomisp_in_fmt_conv *fc;
	पूर्णांक ret, i;

	v4l2_fh_init(&fh.vfh, vdev);

	isp_sink_crop = atomisp_subdev_get_rect(
			    &asd->subdev, शून्य, V4L2_SUBDEV_FORMAT_ACTIVE,
			    ATOMISP_SUBDEV_PAD_SINK, V4L2_SEL_TGT_CROP);

	क्रमmat = atomisp_get_क्रमmat_bridge(pix->pixelक्रमmat);
	अगर (!क्रमmat)
		वापस -EINVAL;

	अगर (isp->inमाला_दो[asd->input_curr].type != TEST_PATTERN &&
	    isp->inमाला_दो[asd->input_curr].type != खाता_INPUT) अणु
		mipi_info = atomisp_to_sensor_mipi_info(
				isp->inमाला_दो[asd->input_curr].camera);
		अगर (!mipi_info) अणु
			dev_err(isp->dev, "mipi_info is NULL\n");
			वापस -EINVAL;
		पूर्ण
		अगर (atomisp_set_sensor_mipi_to_isp(asd, stream_index,
						   mipi_info))
			वापस -EINVAL;
		fc = atomisp_find_in_fmt_conv_by_atomisp_in_fmt(
			 mipi_info->input_क्रमmat);
		अगर (!fc)
			fc = atomisp_find_in_fmt_conv(
				 atomisp_subdev_get_ffmt(&asd->subdev,
							 शून्य, V4L2_SUBDEV_FORMAT_ACTIVE,
							 ATOMISP_SUBDEV_PAD_SINK)->code);
		अगर (!fc)
			वापस -EINVAL;
		अगर (क्रमmat->sh_fmt == IA_CSS_FRAME_FORMAT_RAW &&
		    raw_output_क्रमmat_match_input(fc->atomisp_in_fmt,
						  pix->pixelक्रमmat))
			वापस -EINVAL;
	पूर्ण

	/*
	 * Configure viewfinder also when vfpp is disabled: the
	 * CSS still requires viewfinder configuration.
	 */
	अगर (asd->fmt_स्वतः->val ||
	    asd->vfpp->val != ATOMISP_VFPP_ENABLE) अणु
		काष्ठा v4l2_rect vf_size = अणु0पूर्ण;
		काष्ठा v4l2_mbus_framefmt vf_ffmt = अणु0पूर्ण;

		अगर (pix->width < 640 || pix->height < 480) अणु
			vf_size.width = pix->width;
			vf_size.height = pix->height;
		पूर्ण अन्यथा अणु
			vf_size.width = 640;
			vf_size.height = 480;
		पूर्ण

		/* FIXME: proper क्रमmat name क्रम this one. See
		   atomisp_output_fmts[] in atomisp_v4l2.c */
		vf_ffmt.code = V4L2_MBUS_FMT_CUSTOM_YUV420;

		atomisp_subdev_set_selection(&asd->subdev, fh.pad,
					     V4L2_SUBDEV_FORMAT_ACTIVE,
					     ATOMISP_SUBDEV_PAD_SOURCE_VF,
					     V4L2_SEL_TGT_COMPOSE, 0, &vf_size);
		atomisp_subdev_set_ffmt(&asd->subdev, fh.pad,
					V4L2_SUBDEV_FORMAT_ACTIVE,
					ATOMISP_SUBDEV_PAD_SOURCE_VF, &vf_ffmt);
		asd->video_out_vf.sh_fmt = IA_CSS_FRAME_FORMAT_NV12;

		अगर (asd->vfpp->val == ATOMISP_VFPP_DISABLE_SCALER) अणु
			atomisp_css_video_configure_viewfinder(asd,
							       vf_size.width, vf_size.height, 0,
							       asd->video_out_vf.sh_fmt);
		पूर्ण अन्यथा अगर (asd->run_mode->val == ATOMISP_RUN_MODE_VIDEO) अणु
			अगर (source_pad == ATOMISP_SUBDEV_PAD_SOURCE_PREVIEW ||
			    source_pad == ATOMISP_SUBDEV_PAD_SOURCE_VIDEO)
				atomisp_css_video_configure_viewfinder(asd,
								       vf_size.width, vf_size.height, 0,
								       asd->video_out_vf.sh_fmt);
			अन्यथा
				atomisp_css_capture_configure_viewfinder(asd,
					vf_size.width, vf_size.height, 0,
					asd->video_out_vf.sh_fmt);
		पूर्ण अन्यथा अगर (source_pad != ATOMISP_SUBDEV_PAD_SOURCE_PREVIEW ||
			   asd->vfpp->val == ATOMISP_VFPP_DISABLE_LOWLAT) अणु
			atomisp_css_capture_configure_viewfinder(asd,
				vf_size.width, vf_size.height, 0,
				asd->video_out_vf.sh_fmt);
		पूर्ण
	पूर्ण

	अगर (asd->continuous_mode->val) अणु
		ret = __enable_continuous_mode(asd, true);
		अगर (ret)
			वापस -EINVAL;
	पूर्ण

	atomisp_css_input_set_mode(asd, IA_CSS_INPUT_MODE_BUFFERED_SENSOR);

	क्रम (i = 0; i < IA_CSS_PIPE_ID_NUM; i++)
		asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL].pipe_extra_configs[i].disable_vf_pp = asd->vfpp->val != ATOMISP_VFPP_ENABLE;

	/* ISP2401 new input प्रणाली need to use copy pipe */
	अगर (asd->copy_mode) अणु
		pipe_id = IA_CSS_PIPE_ID_COPY;
		atomisp_css_capture_enable_online(asd, stream_index, false);
	पूर्ण अन्यथा अगर (asd->vfpp->val == ATOMISP_VFPP_DISABLE_SCALER) अणु
		/* video same in continuouscapture and online modes */
		configure_output = atomisp_css_video_configure_output;
		get_frame_info = atomisp_css_video_get_output_frame_info;
		pipe_id = IA_CSS_PIPE_ID_VIDEO;
	पूर्ण अन्यथा अगर (asd->run_mode->val == ATOMISP_RUN_MODE_VIDEO) अणु
		अगर (!asd->continuous_mode->val) अणु
			configure_output = atomisp_css_video_configure_output;
			get_frame_info =
			    atomisp_css_video_get_output_frame_info;
			pipe_id = IA_CSS_PIPE_ID_VIDEO;
		पूर्ण अन्यथा अणु
			अगर (source_pad == ATOMISP_SUBDEV_PAD_SOURCE_PREVIEW ||
			    source_pad == ATOMISP_SUBDEV_PAD_SOURCE_VIDEO) अणु
				configure_output =
				    atomisp_css_video_configure_output;
				get_frame_info =
				    atomisp_css_video_get_output_frame_info;
				configure_pp_input =
				    atomisp_css_video_configure_pp_input;
				pipe_id = IA_CSS_PIPE_ID_VIDEO;
			पूर्ण अन्यथा अणु
				configure_output =
				    atomisp_css_capture_configure_output;
				get_frame_info =
				    atomisp_css_capture_get_output_frame_info;
				configure_pp_input =
				    atomisp_css_capture_configure_pp_input;
				pipe_id = IA_CSS_PIPE_ID_CAPTURE;

				atomisp_update_capture_mode(asd);
				atomisp_css_capture_enable_online(asd, stream_index, false);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (source_pad == ATOMISP_SUBDEV_PAD_SOURCE_PREVIEW) अणु
		configure_output = atomisp_css_preview_configure_output;
		get_frame_info = atomisp_css_preview_get_output_frame_info;
		configure_pp_input = atomisp_css_preview_configure_pp_input;
		pipe_id = IA_CSS_PIPE_ID_PREVIEW;
	पूर्ण अन्यथा अणु
		/* CSS करोesn't support low light mode on SOC cameras, so disable
		 * it. FIXME: अगर this is करोne अन्यथाwhere, it gives corrupted
		 * colors पूर्णांकo thumbnail image.
		 */
		अगर (isp->inमाला_दो[asd->input_curr].type == SOC_CAMERA)
			asd->params.low_light = false;

		अगर (क्रमmat->sh_fmt == IA_CSS_FRAME_FORMAT_RAW) अणु
			atomisp_css_capture_set_mode(asd, IA_CSS_CAPTURE_MODE_RAW);
			atomisp_css_enable_dz(asd, false);
		पूर्ण अन्यथा अणु
			atomisp_update_capture_mode(asd);
		पूर्ण

		अगर (!asd->continuous_mode->val)
			/* in हाल of ANR, क्रमce capture pipe to offline mode */
			atomisp_css_capture_enable_online(asd, stream_index,
							  asd->params.low_light ?
							  false : asd->params.online_process);

		configure_output = atomisp_css_capture_configure_output;
		get_frame_info = atomisp_css_capture_get_output_frame_info;
		configure_pp_input = atomisp_css_capture_configure_pp_input;
		pipe_id = IA_CSS_PIPE_ID_CAPTURE;

		अगर (!asd->params.online_process &&
		    !asd->continuous_mode->val) अणु
			ret = atomisp_css_capture_get_output_raw_frame_info(asd,
				raw_output_info);
			अगर (ret)
				वापस ret;
		पूर्ण
		अगर (!asd->continuous_mode->val && asd->run_mode->val
		    != ATOMISP_RUN_MODE_STILL_CAPTURE) अणु
			dev_err(isp->dev,
				"Need to set the running mode first\n");
			asd->run_mode->val = ATOMISP_RUN_MODE_STILL_CAPTURE;
		पूर्ण
	पूर्ण

	/*
	 * to SOC camera, use yuvpp pipe.
	 */
	अगर (ATOMISP_USE_YUVPP(asd))
		pipe_id = IA_CSS_PIPE_ID_YUVPP;

	अगर (asd->copy_mode)
		ret = atomisp_css_copy_configure_output(asd, stream_index,
							pix->width, pix->height,
							क्रमmat->planar ? pix->bytesperline :
							pix->bytesperline * 8 / क्रमmat->depth,
							क्रमmat->sh_fmt);
	अन्यथा
		ret = configure_output(asd, pix->width, pix->height,
				       क्रमmat->planar ? pix->bytesperline :
				       pix->bytesperline * 8 / क्रमmat->depth,
				       क्रमmat->sh_fmt);
	अगर (ret) अणु
		dev_err(isp->dev, "configure_output %ux%u, format %8.8x\n",
			pix->width, pix->height, क्रमmat->sh_fmt);
		वापस -EINVAL;
	पूर्ण

	ret = configure_pp_input(asd, isp_sink_crop->width, isp_sink_crop->height);
	अगर (ret) अणु
		dev_err(isp->dev, "configure_pp_input %ux%u\n",
			isp_sink_crop->width,
			isp_sink_crop->height);
		वापस -EINVAL;
	पूर्ण
	अगर (asd->copy_mode)
		ret = atomisp_css_copy_get_output_frame_info(asd, stream_index,
			output_info);
	अन्यथा
		ret = get_frame_info(asd, output_info);
	अगर (ret) अणु
		dev_err(isp->dev, "get_frame_info %ux%u (padded to %u)\n",
			pix->width, pix->height, pix->bytesperline);
		वापस -EINVAL;
	पूर्ण

	atomisp_update_grid_info(asd, pipe_id, source_pad);

	/* Free the raw_dump buffer first */
	ia_css_frame_मुक्त(asd->raw_output_frame);
	asd->raw_output_frame = शून्य;

	अगर (!asd->continuous_mode->val &&
	    !asd->params.online_process && !isp->sw_contex.file_input &&
	    ia_css_frame_allocate_from_info(&asd->raw_output_frame,
		    raw_output_info))
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम atomisp_get_dis_envelop(काष्ठा atomisp_sub_device *asd,
				    अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height,
				    अचिन्हित पूर्णांक *dvs_env_w, अचिन्हित पूर्णांक *dvs_env_h)
अणु
	काष्ठा atomisp_device *isp = asd->isp;

	/* अगर subdev type is SOC camera,we करो not need to set DVS */
	अगर (isp->inमाला_दो[asd->input_curr].type == SOC_CAMERA)
		asd->params.video_dis_en = false;

	अगर (asd->params.video_dis_en &&
	    asd->run_mode->val == ATOMISP_RUN_MODE_VIDEO) अणु
		/* envelope is 20% of the output resolution */
		/*
		 * dvs envelope cannot be round up.
		 * it would cause ISP समयout and color चयन issue
		 */
		*dvs_env_w = roundकरोwn(width / 5, ATOM_ISP_STEP_WIDTH);
		*dvs_env_h = roundकरोwn(height / 5, ATOM_ISP_STEP_HEIGHT);
	पूर्ण

	asd->params.dis_proj_data_valid = false;
	asd->params.css_update_params_needed = true;
पूर्ण

अटल व्योम atomisp_check_copy_mode(काष्ठा atomisp_sub_device *asd,
				    पूर्णांक source_pad, काष्ठा v4l2_pix_क्रमmat *f)
अणु
#अगर defined(ISP2401_NEW_INPUT_SYSTEM)
	काष्ठा v4l2_mbus_framefmt *sink, *src;

	sink = atomisp_subdev_get_ffmt(&asd->subdev, शून्य,
				       V4L2_SUBDEV_FORMAT_ACTIVE, ATOMISP_SUBDEV_PAD_SINK);
	src = atomisp_subdev_get_ffmt(&asd->subdev, शून्य,
				      V4L2_SUBDEV_FORMAT_ACTIVE, source_pad);

	अगर ((sink->code == src->code &&
	     sink->width == f->width &&
	     sink->height == f->height) ||
	    ((asd->isp->inमाला_दो[asd->input_curr].type == SOC_CAMERA) &&
	     (asd->isp->inमाला_दो[asd->input_curr].camera_caps->
	      sensor[asd->sensor_curr].stream_num > 1)))
		asd->copy_mode = true;
	अन्यथा
#पूर्ण_अगर
		/* Only used क्रम the new input प्रणाली */
		asd->copy_mode = false;

	dev_dbg(asd->isp->dev, "copy_mode: %d\n", asd->copy_mode);
पूर्ण

अटल पूर्णांक atomisp_set_fmt_to_snr(काष्ठा video_device *vdev,
				  काष्ठा v4l2_pix_क्रमmat *f, अचिन्हित पूर्णांक pixelक्रमmat,
				  अचिन्हित पूर्णांक padding_w, अचिन्हित पूर्णांक padding_h,
				  अचिन्हित पूर्णांक dvs_env_w, अचिन्हित पूर्णांक dvs_env_h)
अणु
	काष्ठा atomisp_sub_device *asd = atomisp_to_video_pipe(vdev)->asd;
	स्थिर काष्ठा atomisp_क्रमmat_bridge *क्रमmat;
	काष्ठा v4l2_subdev_pad_config pad_cfg;
	काष्ठा v4l2_subdev_क्रमmat vक्रमmat = अणु
		.which = V4L2_SUBDEV_FORMAT_TRY,
	पूर्ण;
	काष्ठा v4l2_mbus_framefmt *ffmt = &vक्रमmat.क्रमmat;
	काष्ठा v4l2_mbus_framefmt *req_ffmt;
	काष्ठा atomisp_device *isp = asd->isp;
	काष्ठा atomisp_input_stream_info *stream_info =
	    (काष्ठा atomisp_input_stream_info *)ffmt->reserved;
	u16 stream_index = ATOMISP_INPUT_STREAM_GENERAL;
	पूर्णांक source_pad = atomisp_subdev_source_pad(vdev);
	काष्ठा v4l2_subdev_fh fh;
	पूर्णांक ret;

	v4l2_fh_init(&fh.vfh, vdev);

	stream_index = atomisp_source_pad_to_stream_id(asd, source_pad);

	क्रमmat = atomisp_get_क्रमmat_bridge(pixelक्रमmat);
	अगर (!क्रमmat)
		वापस -EINVAL;

	v4l2_fill_mbus_क्रमmat(ffmt, f, क्रमmat->mbus_code);
	ffmt->height += padding_h + dvs_env_h;
	ffmt->width += padding_w + dvs_env_w;

	dev_dbg(isp->dev, "s_mbus_fmt: ask %ux%u (padding %ux%u, dvs %ux%u)\n",
		ffmt->width, ffmt->height, padding_w, padding_h,
		dvs_env_w, dvs_env_h);

	__atomisp_init_stream_info(stream_index, stream_info);

	req_ffmt = ffmt;

	/* Disable dvs अगर resolution can't be supported by sensor */
	अगर (asd->params.video_dis_en &&
	    source_pad == ATOMISP_SUBDEV_PAD_SOURCE_VIDEO) अणु
		vक्रमmat.which = V4L2_SUBDEV_FORMAT_TRY;
		ret = v4l2_subdev_call(isp->inमाला_दो[asd->input_curr].camera,
				       pad, set_fmt, &pad_cfg, &vक्रमmat);
		अगर (ret)
			वापस ret;
		अगर (ffmt->width < req_ffmt->width ||
		    ffmt->height < req_ffmt->height) अणु
			req_ffmt->height -= dvs_env_h;
			req_ffmt->width -= dvs_env_w;
			ffmt = req_ffmt;
			dev_warn(isp->dev,
				 "can not enable video dis due to sensor limitation.");
			asd->params.video_dis_en = false;
		पूर्ण
	पूर्ण
	dev_dbg(isp->dev, "sensor width: %d, height: %d\n",
		ffmt->width, ffmt->height);
	vक्रमmat.which = V4L2_SUBDEV_FORMAT_ACTIVE;
	ret = v4l2_subdev_call(isp->inमाला_दो[asd->input_curr].camera, pad,
			       set_fmt, शून्य, &vक्रमmat);
	अगर (ret)
		वापस ret;

	__atomisp_update_stream_env(asd, stream_index, stream_info);

	dev_dbg(isp->dev, "sensor width: %d, height: %d\n",
		ffmt->width, ffmt->height);

	अगर (ffmt->width < ATOM_ISP_STEP_WIDTH ||
	    ffmt->height < ATOM_ISP_STEP_HEIGHT)
		वापस -EINVAL;

	अगर (asd->params.video_dis_en &&
	    source_pad == ATOMISP_SUBDEV_PAD_SOURCE_VIDEO &&
	    (ffmt->width < req_ffmt->width || ffmt->height < req_ffmt->height)) अणु
		dev_warn(isp->dev,
			 "can not enable video dis due to sensor limitation.");
		asd->params.video_dis_en = false;
	पूर्ण

	atomisp_subdev_set_ffmt(&asd->subdev, fh.pad,
				V4L2_SUBDEV_FORMAT_ACTIVE,
				ATOMISP_SUBDEV_PAD_SINK, ffmt);

	वापस css_input_resolution_changed(asd, ffmt);
पूर्ण

पूर्णांक atomisp_set_fmt(काष्ठा video_device *vdev, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा atomisp_device *isp = video_get_drvdata(vdev);
	काष्ठा atomisp_video_pipe *pipe = atomisp_to_video_pipe(vdev);
	काष्ठा atomisp_sub_device *asd = pipe->asd;
	स्थिर काष्ठा atomisp_क्रमmat_bridge *क्रमmat_bridge;
	स्थिर काष्ठा atomisp_क्रमmat_bridge *snr_क्रमmat_bridge;
	काष्ठा ia_css_frame_info output_info, raw_output_info;
	काष्ठा v4l2_pix_क्रमmat snr_fmt = f->fmt.pix;
	काष्ठा v4l2_pix_क्रमmat backup_fmt = snr_fmt, s_fmt;
	अचिन्हित पूर्णांक dvs_env_w = 0, dvs_env_h = 0;
	अचिन्हित पूर्णांक padding_w = pad_w, padding_h = pad_h;
	bool res_overflow = false, crop_needs_override = false;
	काष्ठा v4l2_mbus_framefmt *isp_sink_fmt;
	काष्ठा v4l2_mbus_framefmt isp_source_fmt = अणु0पूर्ण;
	काष्ठा v4l2_rect isp_sink_crop;
	u16 source_pad = atomisp_subdev_source_pad(vdev);
	काष्ठा v4l2_subdev_fh fh;
	पूर्णांक ret;

	अगर (source_pad >= ATOMISP_SUBDEV_PADS_NUM)
		वापस -EINVAL;

	अगर (asd->streaming == ATOMISP_DEVICE_STREAMING_ENABLED) अणु
		dev_warn(isp->dev, "ISP does not support set format while at streaming!\n");
		वापस -EBUSY;
	पूर्ण

	dev_dbg(isp->dev,
		"setting resolution %ux%u on pad %u for asd%d, bytesperline %u\n",
		f->fmt.pix.width, f->fmt.pix.height, source_pad,
		asd->index, f->fmt.pix.bytesperline);

	v4l2_fh_init(&fh.vfh, vdev);

	क्रमmat_bridge = atomisp_get_क्रमmat_bridge(f->fmt.pix.pixelक्रमmat);
	अगर (!क्रमmat_bridge)
		वापस -EINVAL;

	pipe->sh_fmt = क्रमmat_bridge->sh_fmt;
	pipe->pix.pixelक्रमmat = f->fmt.pix.pixelक्रमmat;

	अगर (source_pad == ATOMISP_SUBDEV_PAD_SOURCE_VF ||
	    (source_pad == ATOMISP_SUBDEV_PAD_SOURCE_PREVIEW
	     && asd->run_mode->val == ATOMISP_RUN_MODE_VIDEO)) अणु
		अगर (asd->fmt_स्वतः->val) अणु
			काष्ठा v4l2_rect *capture_comp;
			काष्ठा v4l2_rect r = अणु0पूर्ण;

			r.width = f->fmt.pix.width;
			r.height = f->fmt.pix.height;

			अगर (source_pad == ATOMISP_SUBDEV_PAD_SOURCE_PREVIEW)
				capture_comp = atomisp_subdev_get_rect(
						   &asd->subdev, शून्य,
						   V4L2_SUBDEV_FORMAT_ACTIVE,
						   ATOMISP_SUBDEV_PAD_SOURCE_VIDEO,
						   V4L2_SEL_TGT_COMPOSE);
			अन्यथा
				capture_comp = atomisp_subdev_get_rect(
						   &asd->subdev, शून्य,
						   V4L2_SUBDEV_FORMAT_ACTIVE,
						   ATOMISP_SUBDEV_PAD_SOURCE_CAPTURE,
						   V4L2_SEL_TGT_COMPOSE);

			अगर (capture_comp->width < r.width
			    || capture_comp->height < r.height) अणु
				r.width = capture_comp->width;
				r.height = capture_comp->height;
			पूर्ण

			atomisp_subdev_set_selection(
			    &asd->subdev, fh.pad,
			    V4L2_SUBDEV_FORMAT_ACTIVE, source_pad,
			    V4L2_SEL_TGT_COMPOSE, 0, &r);

			f->fmt.pix.width = r.width;
			f->fmt.pix.height = r.height;
		पूर्ण

		अगर (source_pad == ATOMISP_SUBDEV_PAD_SOURCE_PREVIEW &&
		    (asd->isp->inमाला_दो[asd->input_curr].type == SOC_CAMERA) &&
		    (asd->isp->inमाला_दो[asd->input_curr].camera_caps->
		     sensor[asd->sensor_curr].stream_num > 1)) अणु
			/* For M10MO outputing YUV preview images. */
			u16 video_index =
			    atomisp_source_pad_to_stream_id(asd,
							    ATOMISP_SUBDEV_PAD_SOURCE_VIDEO);

			ret = atomisp_css_copy_get_output_frame_info(asd,
				video_index, &output_info);
			अगर (ret) अणु
				dev_err(isp->dev,
					"copy_get_output_frame_info ret %i", ret);
				वापस -EINVAL;
			पूर्ण
			अगर (!asd->yuvpp_mode) अणु
				/*
				 * If viewfinder was configured पूर्णांकo copy_mode,
				 * we चयन to using yuvpp pipe instead.
				 */
				asd->yuvpp_mode = true;
				ret = atomisp_css_copy_configure_output(
					  asd, video_index, 0, 0, 0, 0);
				अगर (ret) अणु
					dev_err(isp->dev,
						"failed to disable copy pipe");
					वापस -EINVAL;
				पूर्ण
				ret = atomisp_css_yuvpp_configure_output(
					  asd, video_index,
					  output_info.res.width,
					  output_info.res.height,
					  output_info.padded_width,
					  output_info.क्रमmat);
				अगर (ret) अणु
					dev_err(isp->dev,
						"failed to set up yuvpp pipe\n");
					वापस -EINVAL;
				पूर्ण
				atomisp_css_video_enable_online(asd, false);
				atomisp_css_preview_enable_online(asd,
								  ATOMISP_INPUT_STREAM_GENERAL, false);
			पूर्ण
			atomisp_css_yuvpp_configure_viewfinder(asd, video_index,
							       f->fmt.pix.width, f->fmt.pix.height,
							       क्रमmat_bridge->planar ? f->fmt.pix.bytesperline
							       : f->fmt.pix.bytesperline * 8
							       / क्रमmat_bridge->depth, क्रमmat_bridge->sh_fmt);
			atomisp_css_yuvpp_get_viewfinder_frame_info(
			    asd, video_index, &output_info);
		पूर्ण अन्यथा अगर (source_pad == ATOMISP_SUBDEV_PAD_SOURCE_PREVIEW) अणु
			atomisp_css_video_configure_viewfinder(asd,
							       f->fmt.pix.width, f->fmt.pix.height,
							       क्रमmat_bridge->planar ? f->fmt.pix.bytesperline
							       : f->fmt.pix.bytesperline * 8
							       / क्रमmat_bridge->depth,	क्रमmat_bridge->sh_fmt);
			atomisp_css_video_get_viewfinder_frame_info(asd,
				&output_info);
			asd->copy_mode = false;
		पूर्ण अन्यथा अणु
			atomisp_css_capture_configure_viewfinder(asd,
				f->fmt.pix.width, f->fmt.pix.height,
				क्रमmat_bridge->planar ? f->fmt.pix.bytesperline
				: f->fmt.pix.bytesperline * 8
				/ क्रमmat_bridge->depth,	क्रमmat_bridge->sh_fmt);
			atomisp_css_capture_get_viewfinder_frame_info(asd,
				&output_info);
			asd->copy_mode = false;
		पूर्ण

		जाओ करोne;
	पूर्ण
	/*
	 * Check whether मुख्य resolution configured smaller
	 * than snapshot resolution. If so, क्रमce मुख्य resolution
	 * to be the same as snapshot resolution
	 */
	अगर (source_pad == ATOMISP_SUBDEV_PAD_SOURCE_CAPTURE) अणु
		काष्ठा v4l2_rect *r;

		r = atomisp_subdev_get_rect(
			&asd->subdev, शून्य,
			V4L2_SUBDEV_FORMAT_ACTIVE,
			ATOMISP_SUBDEV_PAD_SOURCE_VF, V4L2_SEL_TGT_COMPOSE);

		अगर (r->width && r->height
		    && (r->width > f->fmt.pix.width
			|| r->height > f->fmt.pix.height))
			dev_warn(isp->dev,
				 "Main Resolution config smaller then Vf Resolution. Force to be equal with Vf Resolution.");
	पूर्ण

	/* Pipeline configuration करोne through subdevs. Bail out now. */
	अगर (!asd->fmt_स्वतः->val)
		जाओ set_fmt_to_isp;

	/* get sensor resolution and क्रमmat */
	ret = atomisp_try_fmt(vdev, &snr_fmt, &res_overflow);
	अगर (ret) अणु
		dev_warn(isp->dev, "Try format failed with error %d\n", ret);
		वापस ret;
	पूर्ण
	f->fmt.pix.width = snr_fmt.width;
	f->fmt.pix.height = snr_fmt.height;

	snr_क्रमmat_bridge = atomisp_get_क्रमmat_bridge(snr_fmt.pixelक्रमmat);
	अगर (!snr_क्रमmat_bridge) अणु
		dev_warn(isp->dev, "Can't find bridge format\n");
		वापस -EINVAL;
	पूर्ण

	atomisp_subdev_get_ffmt(&asd->subdev, शून्य,
				V4L2_SUBDEV_FORMAT_ACTIVE,
				ATOMISP_SUBDEV_PAD_SINK)->code =
				    snr_क्रमmat_bridge->mbus_code;

	isp_sink_fmt = atomisp_subdev_get_ffmt(&asd->subdev, शून्य,
						V4L2_SUBDEV_FORMAT_ACTIVE,
						ATOMISP_SUBDEV_PAD_SINK);

	isp_source_fmt.code = क्रमmat_bridge->mbus_code;
	atomisp_subdev_set_ffmt(&asd->subdev, fh.pad,
				V4L2_SUBDEV_FORMAT_ACTIVE,
				source_pad, &isp_source_fmt);

	अगर (!atomisp_subdev_क्रमmat_conversion(asd, source_pad)) अणु
		padding_w = 0;
		padding_h = 0;
	पूर्ण अन्यथा अगर (IS_BYT) अणु
		padding_w = 12;
		padding_h = 12;
	पूर्ण

	/* स्थिरruct resolution supported by isp */
	अगर (res_overflow && !asd->continuous_mode->val) अणु
		f->fmt.pix.width = roundकरोwn(
				       clamp_t(u32, f->fmt.pix.width - padding_w,
					       ATOM_ISP_MIN_WIDTH,
					       ATOM_ISP_MAX_WIDTH), ATOM_ISP_STEP_WIDTH);
		f->fmt.pix.height = roundकरोwn(
					clamp_t(u32, f->fmt.pix.height - padding_h,
						ATOM_ISP_MIN_HEIGHT,
						ATOM_ISP_MAX_HEIGHT), ATOM_ISP_STEP_HEIGHT);
	पूर्ण

	atomisp_get_dis_envelop(asd, f->fmt.pix.width, f->fmt.pix.height,
				&dvs_env_w, &dvs_env_h);

	अगर (asd->continuous_mode->val) अणु
		काष्ठा v4l2_rect *r;

		r = atomisp_subdev_get_rect(
			&asd->subdev, शून्य,
			V4L2_SUBDEV_FORMAT_ACTIVE,
			ATOMISP_SUBDEV_PAD_SOURCE_CAPTURE,
			V4L2_SEL_TGT_COMPOSE);
		/*
		 * The ATOMISP_SUBDEV_PAD_SOURCE_CAPTURE should get resolutions
		 * properly set otherwise, it should not be the capture_pad.
		 */
		अगर (r->width && r->height)
			asd->capture_pad = ATOMISP_SUBDEV_PAD_SOURCE_CAPTURE;
		अन्यथा
			asd->capture_pad = source_pad;
	पूर्ण अन्यथा अणु
		asd->capture_pad = source_pad;
	पूर्ण
	/*
	 * set क्रमmat info to sensor
	 * In continuous mode, resolution is set only अगर it is higher than
	 * existing value. This because preview pipe will be configured after
	 * capture pipe and usually has lower resolution than capture pipe.
	 */
	अगर (!asd->continuous_mode->val ||
	    isp_sink_fmt->width < (f->fmt.pix.width + padding_w + dvs_env_w) ||
	    isp_sink_fmt->height < (f->fmt.pix.height + padding_h +
				    dvs_env_h)) अणु
		/*
		 * For jpeg or custom raw क्रमmat the sensor will वापस स्थिरant
		 * width and height. Because we alपढ़ोy had quried try_mbus_fmt,
		 * f->fmt.pix.width and f->fmt.pix.height has been changed to
		 * this fixed width and height. So we cannot select the correct
		 * resolution with that inक्रमmation. So use the original width
		 * and height जबतक set_mbus_fmt() so actual resolutions are
		 * being used in जबतक set media bus क्रमmat.
		 */
		s_fmt = f->fmt.pix;
		अगर (f->fmt.pix.pixelक्रमmat == V4L2_PIX_FMT_JPEG ||
		    f->fmt.pix.pixelक्रमmat == V4L2_PIX_FMT_CUSTOM_M10MO_RAW) अणु
			s_fmt.width = backup_fmt.width;
			s_fmt.height = backup_fmt.height;
		पूर्ण
		ret = atomisp_set_fmt_to_snr(vdev, &s_fmt,
					     f->fmt.pix.pixelक्रमmat, padding_w,
					     padding_h, dvs_env_w, dvs_env_h);
		अगर (ret) अणु
			dev_warn(isp->dev,
				 "Set format to sensor failed with %d\n", ret);
			वापस -EINVAL;
		पूर्ण

		atomisp_csi_lane_config(isp);
		crop_needs_override = true;
	पूर्ण

	atomisp_check_copy_mode(asd, source_pad, &backup_fmt);
	asd->yuvpp_mode = false;			/* Reset variable */

	isp_sink_crop = *atomisp_subdev_get_rect(&asd->subdev, शून्य,
			V4L2_SUBDEV_FORMAT_ACTIVE,
			ATOMISP_SUBDEV_PAD_SINK,
			V4L2_SEL_TGT_CROP);

	/* Try to enable YUV करोwnscaling अगर ISP input is 10 % (either
	 * width or height) bigger than the desired result. */
	अगर (isp_sink_crop.width * 9 / 10 < f->fmt.pix.width ||
	    isp_sink_crop.height * 9 / 10 < f->fmt.pix.height ||
	    (atomisp_subdev_क्रमmat_conversion(asd, source_pad) &&
	     ((asd->run_mode->val == ATOMISP_RUN_MODE_VIDEO &&
	       !asd->continuous_mode->val) ||
	      asd->vfpp->val == ATOMISP_VFPP_DISABLE_SCALER))) अणु
		/* क्रम continuous mode, preview size might be smaller than
		 * still capture size. अगर preview size still needs crop,
		 * pick the larger one between crop size of preview and
		 * still capture.
		 */
		अगर (asd->continuous_mode->val
		    && source_pad == ATOMISP_SUBDEV_PAD_SOURCE_PREVIEW
		    && !crop_needs_override) अणु
			isp_sink_crop.width =
			    max_t(अचिन्हित पूर्णांक, f->fmt.pix.width,
				  isp_sink_crop.width);
			isp_sink_crop.height =
			    max_t(अचिन्हित पूर्णांक, f->fmt.pix.height,
				  isp_sink_crop.height);
		पूर्ण अन्यथा अणु
			isp_sink_crop.width = f->fmt.pix.width;
			isp_sink_crop.height = f->fmt.pix.height;
		पूर्ण

		atomisp_subdev_set_selection(&asd->subdev, fh.pad,
					     V4L2_SUBDEV_FORMAT_ACTIVE,
					     ATOMISP_SUBDEV_PAD_SINK,
					     V4L2_SEL_TGT_CROP,
					     V4L2_SEL_FLAG_KEEP_CONFIG,
					     &isp_sink_crop);
		atomisp_subdev_set_selection(&asd->subdev, fh.pad,
					     V4L2_SUBDEV_FORMAT_ACTIVE,
					     source_pad, V4L2_SEL_TGT_COMPOSE,
					     0, &isp_sink_crop);
	पूर्ण अन्यथा अगर (IS_MOFD) अणु
		काष्ठा v4l2_rect मुख्य_compose = अणु0पूर्ण;

		मुख्य_compose.width = isp_sink_crop.width;
		मुख्य_compose.height =
		    DIV_ROUND_UP(मुख्य_compose.width * f->fmt.pix.height,
				 f->fmt.pix.width);
		अगर (मुख्य_compose.height > isp_sink_crop.height) अणु
			मुख्य_compose.height = isp_sink_crop.height;
			मुख्य_compose.width =
			    DIV_ROUND_UP(मुख्य_compose.height *
					 f->fmt.pix.width,
					 f->fmt.pix.height);
		पूर्ण

		atomisp_subdev_set_selection(&asd->subdev, fh.pad,
					     V4L2_SUBDEV_FORMAT_ACTIVE,
					     source_pad,
					     V4L2_SEL_TGT_COMPOSE, 0,
					     &मुख्य_compose);
	पूर्ण अन्यथा अणु
		काष्ठा v4l2_rect sink_crop = अणु0पूर्ण;
		काष्ठा v4l2_rect मुख्य_compose = अणु0पूर्ण;

		मुख्य_compose.width = f->fmt.pix.width;
		मुख्य_compose.height = f->fmt.pix.height;

		/* WORKAROUND: this override is universally enabled in
		 * GMIN to work around a CTS failures (GMINL-539)
		 * which appears to be related by a hardware
		 * perक्रमmance limitation.  It's unclear why this
		 * particular code triggers the issue. */
		अगर (!IS_ISP2401 || crop_needs_override) अणु
			अगर (isp_sink_crop.width * मुख्य_compose.height >
			    isp_sink_crop.height * मुख्य_compose.width) अणु
				sink_crop.height = isp_sink_crop.height;
				sink_crop.width = DIV_NEAREST_STEP(
						      sink_crop.height *
						      f->fmt.pix.width,
						      f->fmt.pix.height,
						      ATOM_ISP_STEP_WIDTH);
			पूर्ण अन्यथा अणु
				sink_crop.width = isp_sink_crop.width;
				sink_crop.height = DIV_NEAREST_STEP(
						       sink_crop.width *
						       f->fmt.pix.height,
						       f->fmt.pix.width,
						       ATOM_ISP_STEP_HEIGHT);
			पूर्ण
			atomisp_subdev_set_selection(&asd->subdev, fh.pad,
						     V4L2_SUBDEV_FORMAT_ACTIVE,
						     ATOMISP_SUBDEV_PAD_SINK,
						     V4L2_SEL_TGT_CROP,
						     V4L2_SEL_FLAG_KEEP_CONFIG,
						     &sink_crop);
		पूर्ण
		atomisp_subdev_set_selection(&asd->subdev, fh.pad,
					     V4L2_SUBDEV_FORMAT_ACTIVE,
					     source_pad,
					     V4L2_SEL_TGT_COMPOSE, 0,
					     &मुख्य_compose);
	पूर्ण

set_fmt_to_isp:
	ret = atomisp_set_fmt_to_isp(vdev, &output_info, &raw_output_info,
				     &f->fmt.pix, source_pad);
	अगर (ret) अणु
		dev_warn(isp->dev, "Can't set format on ISP. Error %d\n", ret);
		वापस -EINVAL;
	पूर्ण
करोne:
	pipe->pix.width = f->fmt.pix.width;
	pipe->pix.height = f->fmt.pix.height;
	pipe->pix.pixelक्रमmat = f->fmt.pix.pixelक्रमmat;
	अगर (क्रमmat_bridge->planar) अणु
		pipe->pix.bytesperline = output_info.padded_width;
		pipe->pix.sizeimage = PAGE_ALIGN(f->fmt.pix.height *
						 DIV_ROUND_UP(क्रमmat_bridge->depth *
							 output_info.padded_width, 8));
	पूर्ण अन्यथा अणु
		pipe->pix.bytesperline =
		    DIV_ROUND_UP(क्रमmat_bridge->depth *
				 output_info.padded_width, 8);
		pipe->pix.sizeimage =
		    PAGE_ALIGN(f->fmt.pix.height * pipe->pix.bytesperline);
	पूर्ण
	dev_dbg(isp->dev, "%s: image size: %d, %d bytes per line\n",
		__func__, pipe->pix.sizeimage, pipe->pix.bytesperline);

	अगर (f->fmt.pix.field == V4L2_FIELD_ANY)
		f->fmt.pix.field = V4L2_FIELD_NONE;
	pipe->pix.field = f->fmt.pix.field;

	f->fmt.pix = pipe->pix;
	f->fmt.pix.priv = PAGE_ALIGN(pipe->pix.width *
				     pipe->pix.height * 2);

	pipe->capq.field = f->fmt.pix.field;

	/*
	 * If in video 480P हाल, no GFX throttle
	 */
	अगर (asd->run_mode->val == ATOMISP_SUBDEV_PAD_SOURCE_VIDEO &&
	    f->fmt.pix.width == 720 && f->fmt.pix.height == 480)
		isp->need_gfx_throttle = false;
	अन्यथा
		isp->need_gfx_throttle = true;

	वापस 0;
पूर्ण

पूर्णांक atomisp_set_fmt_file(काष्ठा video_device *vdev, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा atomisp_device *isp = video_get_drvdata(vdev);
	काष्ठा atomisp_video_pipe *pipe = atomisp_to_video_pipe(vdev);
	काष्ठा atomisp_sub_device *asd = pipe->asd;
	काष्ठा v4l2_mbus_framefmt ffmt = अणु0पूर्ण;
	स्थिर काष्ठा atomisp_क्रमmat_bridge *क्रमmat_bridge;
	काष्ठा v4l2_subdev_fh fh;
	पूर्णांक ret;

	v4l2_fh_init(&fh.vfh, vdev);

	dev_dbg(isp->dev, "setting fmt %ux%u 0x%x for file inject\n",
		f->fmt.pix.width, f->fmt.pix.height, f->fmt.pix.pixelक्रमmat);
	ret = atomisp_try_fmt_file(isp, f);
	अगर (ret) अणु
		dev_err(isp->dev, "atomisp_try_fmt_file err: %d\n", ret);
		वापस ret;
	पूर्ण

	क्रमmat_bridge = atomisp_get_क्रमmat_bridge(f->fmt.pix.pixelक्रमmat);
	अगर (!क्रमmat_bridge) अणु
		dev_dbg(isp->dev, "atomisp_get_format_bridge err! fmt:0x%x\n",
			f->fmt.pix.pixelक्रमmat);
		वापस -EINVAL;
	पूर्ण

	pipe->pix = f->fmt.pix;
	atomisp_css_input_set_mode(asd, IA_CSS_INPUT_MODE_FIFO);
	atomisp_css_input_configure_port(asd,
					 __get_mipi_port(isp, ATOMISP_CAMERA_PORT_PRIMARY), 2, 0xffff4,
					 0, 0, 0, 0);
	ffmt.width = f->fmt.pix.width;
	ffmt.height = f->fmt.pix.height;
	ffmt.code = क्रमmat_bridge->mbus_code;

	atomisp_subdev_set_ffmt(&asd->subdev, fh.pad, V4L2_SUBDEV_FORMAT_ACTIVE,
				ATOMISP_SUBDEV_PAD_SINK, &ffmt);

	वापस 0;
पूर्ण

पूर्णांक atomisp_set_shading_table(काष्ठा atomisp_sub_device *asd,
			      काष्ठा atomisp_shading_table *user_shading_table)
अणु
	काष्ठा ia_css_shading_table *shading_table;
	काष्ठा ia_css_shading_table *मुक्त_table;
	अचिन्हित पूर्णांक len_table;
	पूर्णांक i;
	पूर्णांक ret = 0;

	अगर (!user_shading_table)
		वापस -EINVAL;

	अगर (!user_shading_table->enable) अणु
		asd->params.config.shading_table = शून्य;
		asd->params.sc_en = false;
		वापस 0;
	पूर्ण

	/* If enabling, all tables must be set */
	क्रम (i = 0; i < ATOMISP_NUM_SC_COLORS; i++) अणु
		अगर (!user_shading_table->data[i])
			वापस -EINVAL;
	पूर्ण

	/* Shading table size per color */
	अगर (!IS_ISP2401) अणु
		अगर (user_shading_table->width > ISP2400_SH_CSS_MAX_SCTBL_WIDTH_PER_COLOR ||
		    user_shading_table->height > ISP2400_SH_CSS_MAX_SCTBL_HEIGHT_PER_COLOR)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		अगर (user_shading_table->width > ISP2401_SH_CSS_MAX_SCTBL_WIDTH_PER_COLOR ||
		    user_shading_table->height > ISP2401_SH_CSS_MAX_SCTBL_HEIGHT_PER_COLOR)
			वापस -EINVAL;
	पूर्ण

	shading_table = atomisp_css_shading_table_alloc(
			    user_shading_table->width, user_shading_table->height);
	अगर (!shading_table)
		वापस -ENOMEM;

	len_table = user_shading_table->width * user_shading_table->height *
		    ATOMISP_SC_TYPE_SIZE;
	क्रम (i = 0; i < ATOMISP_NUM_SC_COLORS; i++) अणु
		ret = copy_from_user(shading_table->data[i],
				     (व्योम __user *)user_shading_table->data[i],
				     len_table);
		अगर (ret) अणु
			मुक्त_table = shading_table;
			ret = -EFAULT;
			जाओ out;
		पूर्ण
	पूर्ण
	shading_table->sensor_width = user_shading_table->sensor_width;
	shading_table->sensor_height = user_shading_table->sensor_height;
	shading_table->fraction_bits = user_shading_table->fraction_bits;

	मुक्त_table = asd->params.css_param.shading_table;
	asd->params.css_param.shading_table = shading_table;
	asd->params.config.shading_table = shading_table;
	asd->params.sc_en = true;

out:
	अगर (मुक्त_table)
		atomisp_css_shading_table_मुक्त(मुक्त_table);

	वापस ret;
पूर्ण

/*Turn off ISP dphy */
पूर्णांक atomisp_ospm_dphy_करोwn(काष्ठा atomisp_device *isp)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(isp->dev);
	अचिन्हित दीर्घ flags;
	u32 reg;

	dev_dbg(isp->dev, "%s\n", __func__);

	/* अगर ISP समयout, we can क्रमce घातerकरोwn */
	अगर (isp->isp_समयout)
		जाओ करोne;

	अगर (!atomisp_dev_users(isp))
		जाओ करोne;

	spin_lock_irqsave(&isp->lock, flags);
	isp->sw_contex.घातer_state = ATOM_ISP_POWER_DOWN;
	spin_unlock_irqrestore(&isp->lock, flags);
करोne:
	/*
	 * MRFLD IUNIT DPHY is located in an always-घातer-on island
	 * MRFLD HW design need all CSI ports are disabled beक्रमe
	 * घातering करोwn the IUNIT.
	 */
	pci_पढ़ो_config_dword(pdev, MRFLD_PCI_CSI_CONTROL, &reg);
	reg |= MRFLD_ALL_CSI_PORTS_OFF_MASK;
	pci_ग_लिखो_config_dword(pdev, MRFLD_PCI_CSI_CONTROL, reg);
	वापस 0;
पूर्ण

/*Turn on ISP dphy */
पूर्णांक atomisp_ospm_dphy_up(काष्ठा atomisp_device *isp)
अणु
	अचिन्हित दीर्घ flags;

	dev_dbg(isp->dev, "%s\n", __func__);

	spin_lock_irqsave(&isp->lock, flags);
	isp->sw_contex.घातer_state = ATOM_ISP_POWER_UP;
	spin_unlock_irqrestore(&isp->lock, flags);

	वापस 0;
पूर्ण

पूर्णांक atomisp_exअगर_makernote(काष्ठा atomisp_sub_device *asd,
			   काष्ठा atomisp_makernote_info *config)
अणु
	काष्ठा v4l2_control ctrl;
	काष्ठा atomisp_device *isp = asd->isp;

	ctrl.id = V4L2_CID_FOCAL_ABSOLUTE;
	अगर (v4l2_g_ctrl
	    (isp->inमाला_दो[asd->input_curr].camera->ctrl_handler, &ctrl)) अणु
		dev_warn(isp->dev, "failed to g_ctrl for focal length\n");
		वापस -EINVAL;
	पूर्ण अन्यथा अणु
		config->focal_length = ctrl.value;
	पूर्ण

	ctrl.id = V4L2_CID_FNUMBER_ABSOLUTE;
	अगर (v4l2_g_ctrl
	    (isp->inमाला_दो[asd->input_curr].camera->ctrl_handler, &ctrl)) अणु
		dev_warn(isp->dev, "failed to g_ctrl for f-number\n");
		वापस -EINVAL;
	पूर्ण अन्यथा अणु
		config->f_number_curr = ctrl.value;
	पूर्ण

	ctrl.id = V4L2_CID_FNUMBER_RANGE;
	अगर (v4l2_g_ctrl
	    (isp->inमाला_दो[asd->input_curr].camera->ctrl_handler, &ctrl)) अणु
		dev_warn(isp->dev, "failed to g_ctrl for f number range\n");
		वापस -EINVAL;
	पूर्ण अन्यथा अणु
		config->f_number_range = ctrl.value;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक atomisp_offline_capture_configure(काष्ठा atomisp_sub_device *asd,
				      काष्ठा atomisp_cont_capture_conf *cvf_config)
अणु
	काष्ठा v4l2_ctrl *c;

	/*
	* In हाल of M10MO ZSL capture हाल, we need to issue a separate
	* capture request to M10MO which will output captured jpeg image
	*/
	c = v4l2_ctrl_find(
		asd->isp->inमाला_दो[asd->input_curr].camera->ctrl_handler,
		V4L2_CID_START_ZSL_CAPTURE);
	अगर (c) अणु
		पूर्णांक ret;

		dev_dbg(asd->isp->dev, "%s trigger ZSL capture request\n",
			__func__);
		/* TODO: use the cvf_config */
		ret = v4l2_ctrl_s_ctrl(c, 1);
		अगर (ret)
			वापस ret;

		वापस v4l2_ctrl_s_ctrl(c, 0);
	पूर्ण

	asd->params.offline_parm = *cvf_config;

	अगर (asd->params.offline_parm.num_captures) अणु
		अगर (asd->streaming == ATOMISP_DEVICE_STREAMING_DISABLED) अणु
			अचिन्हित पूर्णांक init_raw_num;

			अगर (asd->enable_raw_buffer_lock->val) अणु
				init_raw_num =
				    ATOMISP_CSS2_NUM_OFFLINE_INIT_CONTINUOUS_FRAMES_LOCK_EN;
				अगर (asd->run_mode->val == ATOMISP_RUN_MODE_VIDEO &&
				    asd->params.video_dis_en)
					init_raw_num +=
					    ATOMISP_CSS2_NUM_DVS_FRAME_DELAY;
			पूर्ण अन्यथा अणु
				init_raw_num =
				    ATOMISP_CSS2_NUM_OFFLINE_INIT_CONTINUOUS_FRAMES;
			पूर्ण

			/* TODO: this can be हटाओd once user-space
			 *       has been updated to use control API */
			asd->continuous_raw_buffer_size->val =
			    max_t(पूर्णांक,
				  asd->continuous_raw_buffer_size->val,
				  asd->params.offline_parm.
				  num_captures + init_raw_num);
			asd->continuous_raw_buffer_size->val =
			    min_t(पूर्णांक, ATOMISP_CONT_RAW_FRAMES,
				  asd->continuous_raw_buffer_size->val);
		पूर्ण
		asd->continuous_mode->val = true;
	पूर्ण अन्यथा अणु
		asd->continuous_mode->val = false;
		__enable_continuous_mode(asd, false);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * set स्वतः exposure metering winकरोw to camera sensor
 */
पूर्णांक atomisp_s_ae_winकरोw(काष्ठा atomisp_sub_device *asd,
			काष्ठा atomisp_ae_winकरोw *arg)
अणु
	काष्ठा atomisp_device *isp = asd->isp;
	/* Coverity CID 298071 - initialzize काष्ठा */
	काष्ठा v4l2_subdev_selection sel = अणु 0 पूर्ण;

	sel.r.left = arg->x_left;
	sel.r.top = arg->y_top;
	sel.r.width = arg->x_right - arg->x_left + 1;
	sel.r.height = arg->y_bottom - arg->y_top + 1;

	अगर (v4l2_subdev_call(isp->inमाला_दो[asd->input_curr].camera,
			     pad, set_selection, शून्य, &sel)) अणु
		dev_err(isp->dev, "failed to call sensor set_selection.\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक atomisp_flash_enable(काष्ठा atomisp_sub_device *asd, पूर्णांक num_frames)
अणु
	काष्ठा atomisp_device *isp = asd->isp;

	अगर (num_frames < 0) अणु
		dev_dbg(isp->dev, "%s ERROR: num_frames: %d\n", __func__,
			num_frames);
		वापस -EINVAL;
	पूर्ण
	/* a requested flash is still in progress. */
	अगर (num_frames && asd->params.flash_state != ATOMISP_FLASH_IDLE) अणु
		dev_dbg(isp->dev, "%s flash busy: %d frames left: %d\n",
			__func__, asd->params.flash_state,
			asd->params.num_flash_frames);
		वापस -EBUSY;
	पूर्ण

	asd->params.num_flash_frames = num_frames;
	asd->params.flash_state = ATOMISP_FLASH_REQUESTED;
	वापस 0;
पूर्ण

पूर्णांक atomisp_source_pad_to_stream_id(काष्ठा atomisp_sub_device *asd,
				    uपूर्णांक16_t source_pad)
अणु
	पूर्णांक stream_id;
	काष्ठा atomisp_device *isp = asd->isp;

	अगर (isp->inमाला_दो[asd->input_curr].camera_caps->
	    sensor[asd->sensor_curr].stream_num == 1)
		वापस ATOMISP_INPUT_STREAM_GENERAL;

	चयन (source_pad) अणु
	हाल ATOMISP_SUBDEV_PAD_SOURCE_CAPTURE:
		stream_id = ATOMISP_INPUT_STREAM_CAPTURE;
		अवरोध;
	हाल ATOMISP_SUBDEV_PAD_SOURCE_VF:
		stream_id = ATOMISP_INPUT_STREAM_POSTVIEW;
		अवरोध;
	हाल ATOMISP_SUBDEV_PAD_SOURCE_PREVIEW:
		stream_id = ATOMISP_INPUT_STREAM_PREVIEW;
		अवरोध;
	हाल ATOMISP_SUBDEV_PAD_SOURCE_VIDEO:
		stream_id = ATOMISP_INPUT_STREAM_VIDEO;
		अवरोध;
	शेष:
		stream_id = ATOMISP_INPUT_STREAM_GENERAL;
	पूर्ण

	वापस stream_id;
पूर्ण

bool atomisp_is_vf_pipe(काष्ठा atomisp_video_pipe *pipe)
अणु
	काष्ठा atomisp_sub_device *asd = pipe->asd;

	अगर (pipe == &asd->video_out_vf)
		वापस true;

	अगर (asd->run_mode->val == ATOMISP_RUN_MODE_VIDEO &&
	    pipe == &asd->video_out_preview)
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक __checking_exp_id(काष्ठा atomisp_sub_device *asd, पूर्णांक exp_id)
अणु
	काष्ठा atomisp_device *isp = asd->isp;

	अगर (!asd->enable_raw_buffer_lock->val) अणु
		dev_warn(isp->dev, "%s Raw Buffer Lock is disable.\n", __func__);
		वापस -EINVAL;
	पूर्ण
	अगर (asd->streaming != ATOMISP_DEVICE_STREAMING_ENABLED) अणु
		dev_err(isp->dev, "%s streaming %d invalid exp_id %d.\n",
			__func__, exp_id, asd->streaming);
		वापस -EINVAL;
	पूर्ण
	अगर ((exp_id > ATOMISP_MAX_EXP_ID) || (exp_id <= 0)) अणु
		dev_err(isp->dev, "%s exp_id %d invalid.\n", __func__, exp_id);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

व्योम atomisp_init_raw_buffer_biपंचांगap(काष्ठा atomisp_sub_device *asd)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&asd->raw_buffer_biपंचांगap_lock, flags);
	स_रखो(asd->raw_buffer_biपंचांगap, 0, माप(asd->raw_buffer_biपंचांगap));
	asd->raw_buffer_locked_count = 0;
	spin_unlock_irqrestore(&asd->raw_buffer_biपंचांगap_lock, flags);
पूर्ण

पूर्णांक atomisp_set_raw_buffer_biपंचांगap(काष्ठा atomisp_sub_device *asd, पूर्णांक exp_id)
अणु
	पूर्णांक *biपंचांगap, bit;
	अचिन्हित दीर्घ flags;

	अगर (__checking_exp_id(asd, exp_id))
		वापस -EINVAL;

	biपंचांगap = asd->raw_buffer_biपंचांगap + exp_id / 32;
	bit = exp_id % 32;
	spin_lock_irqsave(&asd->raw_buffer_biपंचांगap_lock, flags);
	(*biपंचांगap) |= (1 << bit);
	asd->raw_buffer_locked_count++;
	spin_unlock_irqrestore(&asd->raw_buffer_biपंचांगap_lock, flags);

	dev_dbg(asd->isp->dev, "%s: exp_id %d,  raw_buffer_locked_count %d\n",
		__func__, exp_id, asd->raw_buffer_locked_count);

	/* Check अगर the raw buffer after next is still locked!!! */
	exp_id += 2;
	अगर (exp_id > ATOMISP_MAX_EXP_ID)
		exp_id -= ATOMISP_MAX_EXP_ID;
	biपंचांगap = asd->raw_buffer_biपंचांगap + exp_id / 32;
	bit = exp_id % 32;
	अगर ((*biपंचांगap) & (1 << bit)) अणु
		पूर्णांक ret;

		/* WORKAROUND unlock the raw buffer compulsively */
		ret = atomisp_css_exp_id_unlock(asd, exp_id);
		अगर (ret) अणु
			dev_err(asd->isp->dev,
				"%s exp_id is wrapping back to %d but force unlock failed,, err %d.\n",
				__func__, exp_id, ret);
			वापस ret;
		पूर्ण

		spin_lock_irqsave(&asd->raw_buffer_biपंचांगap_lock, flags);
		(*biपंचांगap) &= ~(1 << bit);
		asd->raw_buffer_locked_count--;
		spin_unlock_irqrestore(&asd->raw_buffer_biपंचांगap_lock, flags);
		dev_warn(asd->isp->dev,
			 "%s exp_id is wrapping back to %d but it is still locked so force unlock it, raw_buffer_locked_count %d\n",
			 __func__, exp_id, asd->raw_buffer_locked_count);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __is_raw_buffer_locked(काष्ठा atomisp_sub_device *asd, पूर्णांक exp_id)
अणु
	पूर्णांक *biपंचांगap, bit;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (__checking_exp_id(asd, exp_id))
		वापस -EINVAL;

	biपंचांगap = asd->raw_buffer_biपंचांगap + exp_id / 32;
	bit = exp_id % 32;
	spin_lock_irqsave(&asd->raw_buffer_biपंचांगap_lock, flags);
	ret = ((*biपंचांगap) & (1 << bit));
	spin_unlock_irqrestore(&asd->raw_buffer_biपंचांगap_lock, flags);
	वापस !ret;
पूर्ण

अटल पूर्णांक __clear_raw_buffer_biपंचांगap(काष्ठा atomisp_sub_device *asd, पूर्णांक exp_id)
अणु
	पूर्णांक *biपंचांगap, bit;
	अचिन्हित दीर्घ flags;

	अगर (__is_raw_buffer_locked(asd, exp_id))
		वापस -EINVAL;

	biपंचांगap = asd->raw_buffer_biपंचांगap + exp_id / 32;
	bit = exp_id % 32;
	spin_lock_irqsave(&asd->raw_buffer_biपंचांगap_lock, flags);
	(*biपंचांगap) &= ~(1 << bit);
	asd->raw_buffer_locked_count--;
	spin_unlock_irqrestore(&asd->raw_buffer_biपंचांगap_lock, flags);

	dev_dbg(asd->isp->dev, "%s: exp_id %d,  raw_buffer_locked_count %d\n",
		__func__, exp_id, asd->raw_buffer_locked_count);
	वापस 0;
पूर्ण

पूर्णांक atomisp_exp_id_capture(काष्ठा atomisp_sub_device *asd, पूर्णांक *exp_id)
अणु
	काष्ठा atomisp_device *isp = asd->isp;
	पूर्णांक value = *exp_id;
	पूर्णांक ret;

	ret = __is_raw_buffer_locked(asd, value);
	अगर (ret) अणु
		dev_err(isp->dev, "%s exp_id %d invalid %d.\n", __func__, value, ret);
		वापस -EINVAL;
	पूर्ण

	dev_dbg(isp->dev, "%s exp_id %d\n", __func__, value);
	ret = atomisp_css_exp_id_capture(asd, value);
	अगर (ret) अणु
		dev_err(isp->dev, "%s exp_id %d failed.\n", __func__, value);
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक atomisp_exp_id_unlock(काष्ठा atomisp_sub_device *asd, पूर्णांक *exp_id)
अणु
	काष्ठा atomisp_device *isp = asd->isp;
	पूर्णांक value = *exp_id;
	पूर्णांक ret;

	ret = __clear_raw_buffer_biपंचांगap(asd, value);
	अगर (ret) अणु
		dev_err(isp->dev, "%s exp_id %d invalid %d.\n", __func__, value, ret);
		वापस -EINVAL;
	पूर्ण

	dev_dbg(isp->dev, "%s exp_id %d\n", __func__, value);
	ret = atomisp_css_exp_id_unlock(asd, value);
	अगर (ret)
		dev_err(isp->dev, "%s exp_id %d failed, err %d.\n",
			__func__, value, ret);

	वापस ret;
पूर्ण

पूर्णांक atomisp_enable_dz_capt_pipe(काष्ठा atomisp_sub_device *asd,
				अचिन्हित पूर्णांक *enable)
अणु
	bool value;

	अगर (!enable)
		वापस -EINVAL;

	value = *enable > 0;

	atomisp_en_dz_capt_pipe(asd, value);

	वापस 0;
पूर्ण

पूर्णांक atomisp_inject_a_fake_event(काष्ठा atomisp_sub_device *asd, पूर्णांक *event)
अणु
	अगर (!event || asd->streaming != ATOMISP_DEVICE_STREAMING_ENABLED)
		वापस -EINVAL;

	dev_dbg(asd->isp->dev, "%s: trying to inject a fake event 0x%x\n",
		__func__, *event);

	चयन (*event) अणु
	हाल V4L2_EVENT_FRAME_SYNC:
		atomisp_sof_event(asd);
		अवरोध;
	हाल V4L2_EVENT_FRAME_END:
		atomisp_eof_event(asd, 0);
		अवरोध;
	हाल V4L2_EVENT_ATOMISP_3A_STATS_READY:
		atomisp_3a_stats_पढ़ोy_event(asd, 0);
		अवरोध;
	हाल V4L2_EVENT_ATOMISP_METADATA_READY:
		atomisp_metadata_पढ़ोy_event(asd, 0);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक atomisp_get_pipe_id(काष्ठा atomisp_video_pipe *pipe)
अणु
	काष्ठा atomisp_sub_device *asd = pipe->asd;

	अगर (ATOMISP_USE_YUVPP(asd))
		वापस IA_CSS_PIPE_ID_YUVPP;
	अन्यथा अगर (asd->vfpp->val == ATOMISP_VFPP_DISABLE_SCALER)
		वापस IA_CSS_PIPE_ID_VIDEO;
	अन्यथा अगर (asd->vfpp->val == ATOMISP_VFPP_DISABLE_LOWLAT)
		वापस IA_CSS_PIPE_ID_CAPTURE;
	अन्यथा अगर (pipe == &asd->video_out_video_capture)
		वापस IA_CSS_PIPE_ID_VIDEO;
	अन्यथा अगर (pipe == &asd->video_out_vf)
		वापस IA_CSS_PIPE_ID_CAPTURE;
	अन्यथा अगर (pipe == &asd->video_out_preview) अणु
		अगर (asd->run_mode->val == ATOMISP_RUN_MODE_VIDEO)
			वापस IA_CSS_PIPE_ID_VIDEO;
		अन्यथा
			वापस IA_CSS_PIPE_ID_PREVIEW;
	पूर्ण अन्यथा अगर (pipe == &asd->video_out_capture) अणु
		अगर (asd->copy_mode)
			वापस IA_CSS_PIPE_ID_COPY;
		अन्यथा
			वापस IA_CSS_PIPE_ID_CAPTURE;
	पूर्ण

	/* fail through */
	dev_warn(asd->isp->dev, "%s failed to find proper pipe\n",
		 __func__);
	वापस IA_CSS_PIPE_ID_CAPTURE;
पूर्ण

पूर्णांक atomisp_get_invalid_frame_num(काष्ठा video_device *vdev,
				  पूर्णांक *invalid_frame_num)
अणु
	काष्ठा atomisp_video_pipe *pipe = atomisp_to_video_pipe(vdev);
	काष्ठा atomisp_sub_device *asd = pipe->asd;
	क्रमागत ia_css_pipe_id pipe_id;
	काष्ठा ia_css_pipe_info p_info;
	पूर्णांक ret;

	अगर (asd->isp->inमाला_दो[asd->input_curr].camera_caps->
	    sensor[asd->sensor_curr].stream_num > 1) अणु
		/* External ISP */
		*invalid_frame_num = 0;
		वापस 0;
	पूर्ण

	pipe_id = atomisp_get_pipe_id(pipe);
	अगर (!asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL].pipes[pipe_id]) अणु
		dev_warn(asd->isp->dev,
			 "%s pipe %d has not been created yet, do SET_FMT first!\n",
			 __func__, pipe_id);
		वापस -EINVAL;
	पूर्ण

	ret = ia_css_pipe_get_info(
		  asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL]
		  .pipes[pipe_id], &p_info);
	अगर (!ret) अणु
		*invalid_frame_num = p_info.num_invalid_frames;
		वापस 0;
	पूर्ण अन्यथा अणु
		dev_warn(asd->isp->dev, "%s get pipe infor failed %d\n",
			 __func__, ret);
		वापस -EINVAL;
	पूर्ण
पूर्ण
